/* Header include files (.h)                                  */
#include "envopt.h"        /* Environment options             */
#include "envdep.h"        /* Environment dependent           */
#include "envind.h"        /* Environment independent         */
#include "gen.h"           /* General                         */
#include "ssi.h"           /* System services */
#include "ss_queue.h"      /* System services interface       */
#include "ss_mem.h"        /* System services interface       */
#include "cm5.h"           /* Common timer library            */
#include "cm_llist.h"      /* Common linked list library      */
#include "cm_hash.h"       /* Common hash library             */
#include "cm_tkns.h"       /* Common tokens                   */
#include "cm_mblk.h"       /* Common memory allocation        */
#include "cm_inet.h"       /* Common socket library           */
#include "cm_pasn.h"       /* Common ASN.1 library            */
#include "ue_aes_mode.h"
#include "ue_usim_auth.h"

/* header/extern include files (.x)                           */
#include "gen.x"           /* General layer                   */
#include "ssi.x"           /* System services interface       */
#include "ss_queue.x"      /* System services interface       */
#include "ss_task.x"       /* System services interface       */
#include "ss_msg.x"        /* System services interface       */
#include "ss_mem.x"        /* System services interface       */
#include "cm5.x"           /* Common timer module             */
#include "cm_lib.x"        /* Common library function         */
#include "cm_llist.x"      /* Common link list library        */
#include "cm_hash.x"       /* Common hash list library        */
#include "ue_alg_intf.x"
#include "ue_aes_mode.x"

/*All external security library include */ 
#include "ext_common.h"
#include "auth_alg.h"
#include "hmacsha256.h"
#include "snow3g_f8f9.h"

extern u8 OP[16];
/**********************************************************************/
/*                 Encryption Alg Interface Fnc's                     */
/**********************************************************************/

#ifdef ANSI
Void ueAppEncSnow3GAlg
(
U8    *key, 
U32    count, 
U8     dir, 
U8     bearer, 
U8    *msg, 
U16    len
)
#else
Void ueAppEncSnow3GAlg(key, count, dir, bearer, msg, len)
(
U8    *key;
U32    count; 
U8     dir;
U8     bearer; 
U8    *msg;
U16    len;
)
#endif
{
   /* Calling Snow-3G encode function */
   f8Snow3g(key, count, bearer, dir, msg, len*8);

   RETVOID;
}

#ifdef ANSI
Void ueAppEncNullAlg
(
U8    *key, 
U32    count, 
U8     dir, 
U8     bearer, 
U8    *msg, 
U16    len
)
#else
Void ueAppEncNullAlg(key, count, dir, bearer, msg, len)
(
U8     *key; 
U32     count; 
U8      dir; 
U8      bearer; 
U8     *msg; 
U16     len;
)
#endif
{
   UNUSED(key);
   UNUSED(count);
   UNUSED(dir);
   UNUSED(bearer);
   UNUSED(msg);
   UNUSED(len);
   /*No encoding of message */
   RETVOID;
}

#ifdef ANSI
Void ueAppEncAESAlg
(
U8    *key,
U32    count,
U8     dir,
U8     bearer,
U8    *msg,
U16    len
)
#else
Void ueAppEncAESAlg(key, count, dir, bearer, msg, len)
(
U8     *key;
U32     count;
U8      dir;
U8      bearer;
U8     *msg;
U16     len;
)
#endif
{
   U8 T1[16] = {0};
   /* prepare the input */
   T1[0] = (count >> 24) & 0xff;
   T1[1] = (count >> 16) & 0xff;
   T1[2] = (count >> 8) & 0xff;
   T1[3] = (count) & 0xff;
   T1[4] = (bearer << 3) & 0xf1;
   T1[4] = T1[4] | ((dir << 2 ) & 0x04);
   /* Call CTR algorithm */
   ueAESCTR(key, 128, T1, 128, msg, len*8);
   RETVOID;
}


/**********************************************************************/
/*                 Integrity Alg Interface Fnc's                      */
/**********************************************************************/
/* Integrity Alg */

#ifdef ANSI
U32  ueAppIntSnow3GAlg
(
U8     *key, 
U32     count, 
U8      dir, 
U8      bearer, 
U8     *msg, 
U16     len
)
#else
U32  ueAppIntSnow3GAlg(key, count, dir, bearer, msg, len)
U8     *key; 
U32     count; 
U8      dir;
U8      bearer; 
U8     *msg; 
U16     len;
#endif
{
   U32 mac;
   /* Calling Snow-3G integrity function */
   mac = f9Snow3g(key, count, bearer, dir, msg, len*8);
   RETVALUE(mac);
}

#ifdef ANSI
U32  ueAppIntNullAlg
(
U8     *key, 
U32     count, 
U8      dir, 
U8      bearer, 
U8     *msg, 
U16     len
)
#else
U32  ueAppIntNullAlg(key, count, dir, bearer, msg, len)
U8     *key; 
U32     count; 
U8      dir;
U8      bearer; 
U8     *msg; 
U16     len;
#endif
{
   UNUSED(key);
   UNUSED(count);
   UNUSED(dir);
   UNUSED(bearer);
   UNUSED(msg);
   UNUSED(len);
   /* mac is zero */
   RETVALUE(0);
}

#ifdef ANSI
U32  ueAppIntAESAlg
(
U8     *key,
U32     count,
U8      dir,
U8      bearer,
U8     *msg,
U16     len
)
#else
U32  ueAppIntAESAlg(key, count, dir, bearer, msg, len)
U8     *key;
U32     count;
U8      dir;
U8      bearer;
U8     *msg;
U16     len;
#endif
{
   U8 M[UE_AES_MAX_MSG_SIZE]    = {0};
   U8 mac[4]                    = {0};

   /* Preparation */
   M[0] = (count >> 24) & 0xff;
   M[1] = (count >> 16) & 0xff;
   M[2] = (count >> 8) & 0xff;
   M[3] = (count) & 0xff;
   M[4] = (bearer << 3) & 0xf1;
   M[4] = M[4] | ((dir << 2 ) & 0x04);
   cmMemcpy(&M[8], msg, len);

   /* Call CMAC algorithm */
   ueAESCMAC(key,128, M, (len+8)*8, mac, 4);

   RETVALUE( mac[0] << 24 |
         mac[1] << 16 |
         mac[2] << 8  |
         mac[3]);
}
/**********************************************************************/
/*                 Key Gen Alg Interface Fnc's                        */
/**********************************************************************/

#ifdef ANSI
Void ueAppKeyGenAlg
(
U8    *key, 
U16   keyLen,
U8    *s,
U16   sLen, 
U8    *output, 
U16   outputLen
)
#else
Void ueAppKeyGenAlg(key, keyLen, s, sLen, output, outPutLen)
U8    *key;
U16   keyLen;
U8    *s;
U16   sLen;
U8    *output;
U16   outputLen;
#endif
{
   U8 digest[512] = {0};

   /* start of hmacsha-256 interface dependent code */
   hmacsha256Param sp;
   hmacsha256Setup (&sp, (const byte*) key, (size_t) keyLen*8);
   hmacsha256Update(&sp, (const byte*) s, (size_t) sLen);
   hmacsha256Digest(&sp, (byte*) digest);
   /* end of hmacsha-256 interface dependent code */
   if(outputLen <= 32)
   {
      cmMemcpy(output, digest + (32 - outputLen), outputLen);
   }
}

/**********************************************************************/
/*                 Authentication Alg Interface Fnc's                 */
/**********************************************************************/
#if ANSI
PUBLIC Void ueUsimAuthF2345
(
U8    *k, 
U8    *op, 
U8    *rnd, 
U8    *res, 
U8    *ck, 
U8    *ik, 
U8    *ak
)
#else
PUBLIC Void ueUsimAuthF2345(k, op, rnd, res, ck, ik, ak)
U8    *k; 
U8    *op; 
U8    *rnd; 
U8    *res; 
U8    *ck; 
U8    *ik; 
U8    *ak;
#endif
{
   cmMemcpy(OP, op, 16);
   f2345(k, rnd, res, ck, ik, ak);
   RETVOID;
}

#ifdef ANSI
PUBLIC Void ueUsimAuthF1
(
U8    *k, 
U8    *op, 
U8    *rnd, 
U8    *sqn, 
U8    *amf, 
U8    *mac
)
#else
PUBLIC Void ueUsimAuthF1(k, op, rnd, sqn, amf, mac)
U8    *k; 
U8    *op; 
U8    *rnd; 
U8    *sqn; 
U8    *amf; 
U8    *mac;
#endif
{
   cmMemcpy(OP, op, 16);
   f1(k, rnd, sqn, amf, mac);
   RETVOID;
}

#ifdef ANSI
PUBLIC Void ueUsimAuthF1Star
(
U8    *k, 
U8    *op, 
U8    *rnd, 
U8    *sqn, 
U8    *amf, 
U8    *mac
)
#else
PUBLIC Void ueUsimAuthF1Star(k, op, rnd, sqn, amf, mac)
U8    *k; 
U8    *op; 
U8    *rnd; 
U8    *sqn; 
U8    *amf; 
U8    *mac;
#endif
{
   cmMemcpy(OP, op, 16);
   f1star(k, rnd, sqn, amf, mac);
   RETVOID;
}

#ifdef ANSI
PUBLIC Void ueUsimAuthF5Star
(
U8    *k, 
U8    *op, 
U8    *rnd, 
U8    *ak
)
#else
PUBLIC Void ueUsimAuthF5Star(k, op, rnd, ak)
U8    *k;
U8    *op; 
U8    *rnd; 
U8    *ak;
#endif
{
   cmMemcpy(OP, op, 16);
   f5star(k, rnd, ak);
   RETVOID;
}


#if ANSI
PUBLIC Void ueUsimXorAuthMac
(
U8    *k, 
U8    *rnd, 
U8    *sqn, 
U8    *amf, 
U8    *mac
)
#else
PUBLIC Void ueUsimXorAuthMac(k, rnd, sqn, amf, mac)
U8    *k; 
U8    *rnd; 
U8    *sqn; 
U8    *amf; 
U8    *mac;
#endif
{
   U8    cdOut[8];

   /* cdOut */
   USIM_AUTN_GET_CDOUT(sqn, amf, cdOut);
   /* mac */
   USIM_AUTN_GET_MAC(k, rnd, cdOut, mac);
}


#if ANSI
PUBLIC Void ueUsimXorAuthVectors
(
U8    *k, 
U8    *rnd, 
U8    *res, 
U8    *ck, 
U8    *ik, 
U8    *ak
)
#else
PUBLIC Void ueUsimXorAuthVectors(k, rnd, res, ck, ik, ak)
U8    *k; 
U8    *rnd; 
U8    *res; 
U8    *ck; 
U8    *ik; 
U8    *ak;
#endif
{
   /* ak */
   USIM_AUTN_GET_AK(k, rnd, ak);
   /* ck and res */
   USIM_AUTN_GET_CK_N_RES(k, rnd, ck, res);
   /* ik */
   USIM_AUTN_GET_IK(k, rnd, ik);
}
