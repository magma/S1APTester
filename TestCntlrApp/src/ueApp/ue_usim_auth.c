
/********************************************************************20**

     Name:    HSS Authentication Module

     Type:    C Source file

     Desc:    This file contains HSS authentication
              source code

     File:    ue_usim_auth.c

     Sid:     ue_usim_auth.c@@/main/1 - Thu Nov 17 19:35:38 2011

     Prg:     sk
*********************************************************************21*/

/* Header include files (.h)                                  */
#include <stdlib.h>
#include <math.h>
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
#include "ue_usim_auth.h"
#include "ue_emm.h"

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
#include "ue_usim_auth.x"

/********************************************************************
 *
 *       Fun:   ueUsimAuthcHexDump
 *       
 *       Desc:  Prints hex valuse of buffer 
 *       
 *       Ret:  None 
 *       
 *       Notes: 
 *              
 *       File:  
 ********************************************************************/
#ifdef ANSI
PUBLIC Void ueUsimAuthHexDump
(
S8    *mod,
S8    *name,
S8    *file,
U16   line,
S8    *fun,
U8    *buf,
U16   len
)
#else
PUBLIC Void ueUsimAuthHexDump(mod, name, file, line, fun, buf, len)
(
S8    *mod;
S8    *name;
S8    *file;
U16   line;
S8    *fun;
U8    *buf;
U16   len;
)
#endif
{
   U16 cnt = 0;
   printf(" [%s] [%s:%d:%s] [HEX_DUMP]: %s[Len(%d bytes)]:\n", mod, file, line, fun, name, len);
   printf(" [");
   for(cnt = 0; cnt < len; cnt++)
   {
      if((cnt != 0) &&(0 == cnt%16))
      {
         printf(" ]\n [");
      }
      else if((cnt != 0) &&(0 == cnt%8))
      {
         printf("  ");
      }
      else if((cnt != 0) &&(0 == cnt%4))
      {
         printf(" ");
      }
      printf(" %02x", buf[cnt]);
   }
   printf(" ]\n");
}


#ifndef SQN_ALGO_TS33102
/********************************************************************
 *
 *       Fun:   ueUsimUpdSeqNmb 
 *       
 *       Desc:  This function updates sequence number based 
 *              on received sequence number
 *       
 *       Ret:   None
 *       
 *       Notes: Table based sequnce number maintainence is pending 
 *              
 *       File:  
 ********************************************************************/
#ifdef ANSI
PRIVATE Void ueUsimUpdSeqNmb
(
UeUsimUeAuthInfo *ueInfo, 
U8              *seq
)
#else
PRIVATE Void ueUsimUpdSeqNmb(ueInfo, seq)
UeUsimUeAuthInfo *ueInfo; 
U8              *seq;
#endif
{
   UE_USIM_AUTH_TRC2(ueUsimUpdSeqNmb)

   /*TODO:Table Based Implementation*/
   cmMemcpy(ueInfo->seqNmb, seq, UE_USIM_SEQ_NMB_SIZE);

   RETVOID;
}
#endif


#ifndef SQN_ALGO_TS33102
/********************************************************************
 *
 *       Fun:   ueUsimIncSeqNmb
 *       
 *       Desc:  This function increments sequence number by one 
 *       
 *       Ret:   None
 *       
 *       Notes:  
 *              
 *       File:  
 ********************************************************************/
#ifdef ANSI
PRIVATE Void ueUsimIncSeqNmb
(
U8    *seqNmb
)
#else
PRIVATE Void ueUsimIncSeqNmb(seqNmb)
U8    *seqNmb;
#endif
{
   U8 ind = 0;
   U8 bits = 0;
   Bool inc = FALSE;
   S16 indx = 0;

   UE_USIM_AUTH_TRC2(ueUsimIncSeqNmb)

   ind  = seqNmb[UE_USIM_SEQ_NMB_SIZE - 1] & 0x1F;
   bits = (seqNmb[UE_USIM_SEQ_NMB_SIZE - 1] & 0xe0) >> 5;

   ind = (ind+1)%32;
   if (0x07 == bits)
   {
      bits = 0;
      inc = TRUE;
   }
   else
   {
      bits++;
   }
   seqNmb[UE_USIM_SEQ_NMB_SIZE - 1] = (bits << 5) | ind; 

   for (indx = UE_USIM_SEQ_NMB_SIZE - 2; (indx >= 0) && (TRUE == inc); indx--)
   {
      if (0xFF == seqNmb[indx])
      {
         seqNmb[indx] = 0;
      }
      else
      {
         seqNmb[indx]++;
         inc = FALSE; 
      }
   }
   RETVOID;
}
#endif

/********************************************************************
 *
 *       Fun:   ueUsimVldSeqNmb
 *       
 *       Desc:  This function validates received sequence vs 
 *              current sequence number 
 *       
 *       Ret:   None
 *       
 *       Notes:  
 *              
 *       File:  
 ********************************************************************/
#ifdef ANSI
PRIVATE S16 ueUsimVldSeqNmb
(
UeUsimUeAuthInfo *ueInfo, 
UeSQN            sqnRcvd,
UeSQN            maxSqnRcvd
)
#else
PRIVATE S16 ueUsimVldSeqNmb(ueInfo, sqnRcvd)
UeUsimUeAuthInfo *ueInfo; 
U8               *sqnRcvd; 
#endif
{
#ifdef SQN_ALGO_TS33102
   U64 seqRcvd, seqStored, seqMs;
   S64 seqDiff = 0;
   U8  indx = 0, seqIndx = 0, indxMs = 0,seqIndx1 = 0;
   
   ueUsimGetSeqIndx(sqnRcvd.sqn, &seqRcvd, &indx);
   if(maxSqnRcvd.pres == TRUE)
   {
      ueUsimGetSeqIndx(maxSqnRcvd.sqn, &seqMs, &seqIndx1);
      cmMemcpy(ueInfo->seqNmb[seqIndx1],maxSqnRcvd.sqn, UE_USIM_SEQ_NMB_SIZE);
   }
   

#if 1
      /* Geting the largest seq number from stored seq numbers. */
      ueUsimFndHighestSQNIndx(ueInfo, &seqIndx);
      ueUsimGetSeqIndx(ueInfo->seqNmb[seqIndx], &seqMs, &indxMs);
   seqDiff = seqRcvd - seqMs;
   if((seqDiff) <= pow(2, UE_USIM_TWOS_EXPONENT_FOR_DELTA))
   {
      if(sqnRcvd.pres == TRUE)
      {
         cmMemcpy(ueInfo->seqNmb[indx], sqnRcvd.sqn, UE_USIM_SEQ_NMB_SIZE);
      }
      ueUsimGetSeqIndx(ueInfo->seqNmb[indx], &seqStored, &indx);
      seqDiff = seqMs - seqRcvd;

      if(seqDiff < UE_USIM_AGE_LIMIT)
      {
         if(seqRcvd <= seqStored)
         {
            RETVALUE(RFAILED);
         }
         else
         {
            cmMemcpy(ueInfo->seqNmb[indx], sqnRcvd.sqn, UE_USIM_SEQ_NMB_SIZE);
            RETVALUE(ROK);
         }
      }
      else
      {
         RETVALUE(RFAILED);
      }
   }
   else
   {
      RETVALUE(RFAILED);
   }
#else
   if((seqRcvd - seqStored) < pow(2, UE_USIM_TWOS_EXPONENT_FOR_DELTA))
   {
      cmMemcpy(ueInfo->seqNmb[indx], sqnRcvd, UE_USIM_SEQ_NMB_SIZE);
      RETVALUE(ROK);
   }
   else
      RETVALUE(RFAILED);
#endif
#else
   /*TODO:Table Based Implementation*/
   U8  seqExpected[UE_USIM_SEQ_NMB_SIZE];

   UE_USIM_AUTH_TRC2(ueUsimVldSeqNmb)

   cmMemcpy(seqExpected, ueInfo->seqNmb, UE_USIM_SEQ_NMB_SIZE);
   ueUsimIncSeqNmb(seqExpected);
   if (0 != cmMemcmp(sqnRcvd.sqn, seqExpected, UE_USIM_SEQ_NMB_SIZE))
   {
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
#endif
}

/********************************************************************
 *
 *       Fun:   ueUsimGenKasme
 *       
 *       Desc:  This function generates KASME 
 *       
 *       Ret:   None
 *       
 *       Notes:  
 *              
 *       File:  
 ********************************************************************/
#ifdef ANSI
PRIVATE S16 ueUsimGenKasme
(
U8           *ck,
U8           *ik,
U8           *ak,
U8           *seqNmb, 
U8           *plmn,
U8           *kasme
)
#else
PRIVATE S16 ueUsimGenKasme(ck, ik, ak, seqNmb, plmn, kasme)
U8           *ck,
U8           *ik,
U8           *ak,
U8           *seqNmb, 
U8           *plmn,
U8           *kasme
#endif
{

   U8 key[UE_USIM_IK_SIZE + UE_USIM_CK_SIZE];
   U8 s[14];
   UE_USIM_AUTH_TRC2(ueUsimGenKasme)

   s[0] = 0x10;
   s[1] = plmn[0];
   s[2] = plmn[1];
   s[3] = plmn[2];
   s[4] = 0x00;
   s[5] = 0x03;
   s[6] = seqNmb[0] ^ ak[0];
   s[7] = seqNmb[1] ^ ak[1];
   s[8] = seqNmb[2] ^ ak[2];
   s[9] = seqNmb[3] ^ ak[3];
   s[10] = seqNmb[4] ^ ak[4];
   s[11] = seqNmb[5] ^ ak[5];
   s[12] = 0x00;
   s[13] = 0x06;

   cmMemcpy(key, ck, UE_USIM_CK_SIZE);
   memcpy((key + UE_USIM_CK_SIZE), ik, UE_USIM_IK_SIZE);

   UE_USIM_AUTH_PRNT_HEX("Key(ck||ik)", key, UE_USIM_IK_SIZE + UE_USIM_CK_SIZE);
   UE_USIM_AUTH_PRNT_HEX("S", s, 14);

   /*Generates Sequence Number*/   
   ueAppKeyGenAlg(key, UE_USIM_IK_SIZE + UE_USIM_CK_SIZE,
                  s, 14, kasme, UE_KASME_SIZE);

   UE_USIM_AUTH_PRNT_HEX("Kasme", kasme, UE_KASME_SIZE);

   RETVALUE(ROK);
}

/********************************************************************
 *
 *       Fun:   ueUsimGenAuthVec
 *       
 *       Desc:  This function generates Authentication Vector At HSS
 *       
 *       Ret:   None
 *       
 *       Notes:  
 *              
 *       File:  
 ********************************************************************/
#ifdef SQN_ALGO_TS33102
#ifdef ANSI
PUBLIC S16  ueUsimGenAuthVec
(
UeUsimUeAuthInfo     *ueInfo, 
UeUsimAuthVec        *authVec, 
U8                  *plmn,
U8                  *recvdSQN
)
#else
PUBLIC S16  ueUsimGenAuthVec(ueInfo, authVec, plmn, recvdSQN)
UeUsimUeAuthInfo     *ueInfo;
UeUsimAuthVec        *authVec; 
U8                  *plmn;
U8                  *recvdSQN;
#endif
#else /*SQN_ALGO_TS33102 */
#ifdef ANSI
PUBLIC S16  ueUsimGenAuthVec
(
UeUsimUeAuthInfo     *ueInfo, 
UeUsimAuthVec        *authVec, 
U8                  *plmn
)
#else
PUBLIC S16  ueUsimGenAuthVec(ueInfo, authVec, plmn)
UeUsimUeAuthInfo     *ueInfo;
UeUsimAuthVec        *authVec; 
U8                  *plmn;
#endif
#endif /*SQN_ALGO_TS33102 */
{
#ifndef SQN_ALGO_TS33102
   U32 rndNmb = 0;
   U8  indx = 0;
   U8 seqXorAk[UE_USIM_SEQ_NMB_SIZE];
   U8 amf[2] = {0, 0};
   U8 mac[UE_USIM_MAC_SIZE];
   UE_USIM_AUTH_TRC1(ueUsimGenAuthVec)
#ifndef SQN_ALGO_TS33102
   /*Increment Sequence Number For Next Use*/
   ueUsimIncSeqNmb(ueInfo->seqNmb);
#endif
   /*Generate Random Number*/
   for(indx = 0; indx < UE_RAND_SIZE/4; indx = indx + 4)
   {
      rndNmb = rand();  /*stdlib defined call*/
      authVec->vec.rndNmb[indx + 0] = (rndNmb >> 24) & 0xff;
      authVec->vec.rndNmb[indx + 1] = (rndNmb >> 16) & 0xff;
      authVec->vec.rndNmb[indx + 2] = (rndNmb >> 8) & 0xff;
      authVec->vec.rndNmb[indx + 3] = rndNmb & 0xff;
   }

   /*Auth Algorithm Interface Functions*/
   /*Generates RES, CK, IK and AK*/

   UE_USIM_AUTH_PRNT_HEX("Shared Key", ueInfo->sharedKey, 
                         UE_USIM_SHARED_KEY_SIZE);
   UE_USIM_AUTH_PRNT_HEX("OP Key", ueInfo->opKey,
                         UE_USIM_OP_KEY_SIZE);
   UE_USIM_AUTH_PRNT_HEX("Rand", authVec->vec.rndNmb,
                         UE_RAND_SIZE);

   ueUsimAuthF2345(ueInfo->sharedKey,  ueInfo->opKey, 
                   authVec->vec.rndNmb , authVec->vec.xres, 
                   authVec->ck, authVec->ik, authVec->ak);

   UE_USIM_AUTH_PRNT_HEX("XRes", authVec->vec.xres,
                         UE_RES_SIZE);

   UE_USIM_AUTH_PRNT_HEX("CK", authVec->ck,
                         UE_USIM_CK_SIZE);
   UE_USIM_AUTH_PRNT_HEX("IK", authVec->ik,
                         UE_USIM_IK_SIZE);

   UE_USIM_AUTH_PRNT_HEX("AK", authVec->ak,
                         UE_USIM_AK_SIZE);

   /*Auth Algorithm Interface Functions*/
   /*Generates MAC*/
#ifdef SQN_ALGO_TS33102
   ueUsimAuthF1(ueInfo->sharedKey, ueInfo->opKey, 
               authVec->vec.rndNmb, recvdSQN, amf, mac);
#else
   ueUsimAuthF1(ueInfo->sharedKey, ueInfo->opKey, 
               authVec->vec.rndNmb, ueInfo->seqNmb, amf, mac);
#endif

   UE_USIM_AUTH_PRNT_HEX("Mac", mac,
                            UE_USIM_MAC_SIZE);
   /*Construct AUTN*/
   for(indx = 0; indx < UE_USIM_SEQ_NMB_SIZE; indx++)
   {
      seqXorAk[indx] = ueInfo->seqNmb[indx] ^ authVec->ak[indx];
      authVec->vec.autn[indx] = seqXorAk[indx];
   }
   authVec->vec.autn[UE_USIM_SEQ_NMB_SIZE] = amf[0];
   authVec->vec.autn[UE_USIM_SEQ_NMB_SIZE+1] = amf[1];
   for(indx = 0; indx < UE_USIM_MAC_SIZE; indx++)
   {
      authVec->vec.autn[indx + UE_USIM_SEQ_NMB_SIZE + 2] = mac[indx];
   }

   UE_USIM_AUTH_PRNT_HEX("Autn", authVec->vec.autn,
         UE_AUTN_SIZE);

   /*Generate KASME*/
   ueUsimGenKasme(authVec->ck, authVec->ik, authVec->ak, 
                 ueInfo->seqNmb, plmn, authVec->vec.kasme);

#endif     
   RETVALUE(ROK);
}

/********************************************************************
 *
 *       Fun:   ueUsimPrcsSyncFlr
 *       
 *       Desc:  This function process the AUTS, validates the UE and generates 
 *              Authentiction Vector 
 *       
 *       Ret:   None
 *       
 *       Notes:     
 *              
 *       File:  
 ********************************************************************/
#ifdef ANSI
PUBLIC S16  ueUsimPrcsSyncFlr
(
UeUsimUeAuthInfo   *ueInfo, 
U8                *auts, 
U8                *rnd, 
UeUsimAuthVec      *authVec, 
U8                *plmn
)
#else
PUBLIC S16 ueUsimPrcsSyncFlr(ueInfo, auts, rnd, authVec, plmn)
UeUsimUeAuthInfo   *ueInfo;
U8                *auts; 
U8                *rnd; 
UeUsimAuthVec      *authVec; 
U8                *plmn;
#endif
{
#ifndef SQN_ALGO_TS33102  
/* This function is not required - to be removed */
   U8 indx = 0;
   U8 ak[UE_USIM_AK_SIZE];
   U8 sqnMS[UE_USIM_SEQ_NMB_SIZE];
   U8 macRcvd[UE_USIM_MAC_SIZE];
   U8 macCalc[UE_USIM_MAC_SIZE];
   U8 amf[2]={0, 0};

   UE_USIM_AUTH_TRC1(ueUsimPrcsSyncFlr)

   /*Generates AK*/

   UE_USIM_AUTH_PRNT_HEX("Shared Key", ueInfo->sharedKey, 
                         UE_USIM_SHARED_KEY_SIZE);
   UE_USIM_AUTH_PRNT_HEX("OP Key", ueInfo->opKey,
                         UE_USIM_OP_KEY_SIZE);
   UE_USIM_AUTH_PRNT_HEX("Rand", rnd,
                         UE_RAND_SIZE);

   ueUsimAuthF5Star(ueInfo->sharedKey,
                    ueInfo->opKey, rnd, ak) ; 

   UE_USIM_AUTH_PRNT_HEX("AK", ak,
                         UE_USIM_AK_SIZE);

   UE_USIM_AUTH_PRNT_HEX("Auts", auts,
                         UE_AUTS_SIZE);
   /*Construct UEs Seq Num*/
   for(indx = 0; indx < UE_USIM_SEQ_NMB_SIZE; indx++)
   {
      sqnMS[indx] = auts[indx] ^ ak[indx];
   }

   /*Extract MAC Received From UE*/
   for(indx = UE_USIM_SEQ_NMB_SIZE; indx < UE_AUTS_SIZE; indx++)
   {
      macRcvd[indx - UE_USIM_SEQ_NMB_SIZE] = auts[indx];
   }

   UE_USIM_AUTH_PRNT_HEX("Rcvd Mac", macRcvd,
                         UE_USIM_MAC_SIZE);

   UE_USIM_AUTH_PRNT_HEX("MS Seq Num", sqnMS,
                            UE_USIM_SEQ_NMB_SIZE);
   /*Generate MAC*/
   ueUsimAuthF1Star(ueInfo->sharedKey, ueInfo->opKey,  
               rnd, sqnMS, amf, macCalc); 

   UE_USIM_AUTH_PRNT_HEX("Calc Mac", macCalc,
                            UE_USIM_MAC_SIZE);
    
   /*Received MAC And Calculated MAC Should Match*/
   if(0 == cmMemcmp(macCalc, macRcvd, UE_USIM_MAC_SIZE))
   {
      /*Update UE's Sequence Number*/
      ueUsimUpdSeqNmb(ueInfo, sqnMS);
   }  
   else
   {
      /* MAC Failure: Illegal UE */
      RETVALUE(RFAILED);
   }

   /* Gen new set of authentication vector */ 
   ueUsimGenAuthVec(ueInfo, authVec, plmn);
#endif
   RETVALUE(ROK);
}


#if ANSI
PUBLIC Void ueUsimGenAuthVect
(
U8    *k,
U8    *rnd, 
U8    *res, 
U8    *ck, 
U8    *ik, 
U8    *ak
)
#else
PUBLIC Void ueUsimGenAuthVect(k, rnd, res, ck, ik, ak)
U8    *k; 
U8    *rnd; 
U8    *res; 
U8    *ck; 
U8    *ik; 
U8    *ak;
#endif
{
   VB_HSS_AUTN_GET_AK(k, rnd, ak);
   VB_HSS_AUTN_GET_CK(k, rnd, ck);
   VB_HSS_AUTN_GET_IK(k, rnd, ik);
   VB_HSS_AUTN_GET_RES(k, rnd, res);
   RETVOID;
}

PUBLIC Void ueUsimCalcAndStoreAuthKeys
(
 UeUsimUeAuthInfo *ueInfo,
 UeUsimAuthKeys* authKeys,
 U8*             res,
 U8*             autn,
 U8*             rnd
)
{
   U8 indx = 0;

   UE_USIM_AUTH_TRC1(ueUsimCalcAndStoreAuthKeys)
   UE_USIM_AUTH_PRNT_HEX("Shared Key", ueInfo->sharedKey,\
         UE_USIM_SHARED_KEY_SIZE);
   UE_USIM_AUTH_PRNT_HEX("OP Key", ueInfo->opKey, UE_USIM_OP_KEY_SIZE);
   UE_USIM_AUTH_PRNT_HEX("Rand", rnd, UE_RAND_SIZE);

   if (ueInfo->authAlg == UE_APP_AUTH_XOR)
   {
      ueUsimXorAuthVectors(ueInfo->sharedKey, rnd, res, authKeys->ck,
            authKeys->ik, authKeys->ak);
   }
   else
   {
      ueUsimAuthF2345(ueInfo->sharedKey, ueInfo->opKey, rnd, res, authKeys->ck,
            authKeys->ik, authKeys->ak);
   }

   /*Extract Info From AUTN*/
   for (indx = 0; indx < UE_USIM_SEQ_NMB_SIZE; indx++)
   {
      authKeys->sqnRcvd[indx] = autn[indx] ^ authKeys->ak[indx];  
   } 

   UE_USIM_AUTH_PRNT_HEX("Autn Received from MME",autn,
         UE_AUTN_SIZE);
   UE_USIM_AUTH_PRNT_HEX("Seq Rcvd from MME", authKeys->sqnRcvd, UE_USIM_SEQ_NMB_SIZE);

   cmMemcpy(authKeys->autn, autn, CM_EMM_MAX_AUTN);
   cmMemcpy(authKeys->rnd, rnd, CM_EMM_MAX_RAND);
   RETVOID;
}

PUBLIC Void ueUsimCalcAuthKeys
(
 UeUsimUeAuthInfo *ueInfo,
 UeUsimAuthKeys* authKeys,
 U8*             res,
 U8*             autn,
 U8*             rnd,
 U8*             ak,
 U8*             ck,
 U8*             ik
)
{
   U8 indx = 0;

   UE_USIM_AUTH_TRC1(ueUsimCalAuthKeys)
   UE_USIM_AUTH_PRNT_HEX("Shared Key", ueInfo->sharedKey,\
         UE_USIM_SHARED_KEY_SIZE);
   UE_USIM_AUTH_PRNT_HEX("OP Key", ueInfo->opKey, UE_USIM_OP_KEY_SIZE);
   UE_USIM_AUTH_PRNT_HEX("Rand", rnd, UE_RAND_SIZE);

   if (ueInfo->authAlg == UE_APP_AUTH_XOR)
   {
      ueUsimXorAuthVectors(ueInfo->sharedKey, rnd, res, authKeys->ck,
            authKeys->ik, authKeys->ak);
   }
   else
   {
      ueUsimAuthF2345(ueInfo->sharedKey, ueInfo->opKey, rnd, res, authKeys->ck,
            authKeys->ik, authKeys->ak);
   }

   /*Extract Info From AUTN*/
   for (indx = 0; indx < UE_USIM_SEQ_NMB_SIZE; indx++)
   {
      authKeys->sqnRcvd[indx] = autn[indx] ^ authKeys->ak[indx];  
   } 

   UE_USIM_AUTH_PRNT_HEX("Autn Received from MME",autn,
         UE_AUTN_SIZE);
   UE_USIM_AUTH_PRNT_HEX("Seq Rcvd from MME", authKeys->sqnRcvd, UE_USIM_SEQ_NMB_SIZE);

   cmMemcpy(authKeys->autn, autn, CM_EMM_MAX_AUTN);
   cmMemcpy(authKeys->rnd, rnd, CM_EMM_MAX_RAND);
   RETVOID;
}
/********************************************************************
 *
 *       Fun:   ueUsimGenAuthRsp
 *       
 *       Desc:  This function generates Auth RES and KASME or AUTS
 *       
 *       Ret:   ROK
 *              RFAILED
 *       
 *       Notes:     
 *              
 *       File:  
 ********************************************************************/
#ifdef ANSI
PUBLIC S16 ueUsimGenAuthRsp
(
UeUsimUeAuthInfo *ueInfo, 
UeUsimAuthKeys  *authKeys,
UeSQN            sqnRcvd,
U8              *plmn,
U8              *res, 
U8              *kasme,
U8              *cause, 
U8              *auts,
UeSQN           maxSqnRcvd
)
#else
PUBLIC S16 ueUsimGenAuthRsp(ueInfo, authKeys, sqnRcvd, plmn, res, kasme, cause,
      auts)
UeUsimUeAuthInfo *ueInfo;
UeUsimAuthKeys  *authKeys,
U8              *sqnRcvd,
U8              *plmn;
U8              *res; 
U8              *kasme,
U8              *cause; 
U8              *auts;
#endif
{
   U8 macRcvd[UE_USIM_MAC_SIZE];
   U8 macCalc[UE_USIM_MAC_SIZE];
   U8 amf[2];
   U8 indx = 0;
#ifdef SQN_ALGO_TS33102
   U8 seqIndx;
#endif

   UE_USIM_AUTH_TRC1(ueUsimGenAuthRsp)

   amf[0] = authKeys->autn[UE_USIM_SEQ_NMB_SIZE];
   amf[1] = authKeys->autn[UE_USIM_SEQ_NMB_SIZE + 1];

   for (indx = UE_USIM_SEQ_NMB_SIZE + 2; indx < UE_AUTN_SIZE; indx++)
   {
      macRcvd[(indx - UE_USIM_SEQ_NMB_SIZE - 2)] = authKeys->autn[indx];  
   }

   if (ROK != ueUsimVldSeqNmb(ueInfo, sqnRcvd,maxSqnRcvd))
   {
      *cause = UE_APP_USIM_SYNC_FAILURE;
      /* AMF is Zero for sync failure case */
      amf[0] = 0;
      amf[1] = 0;

      /*Generates AK*/
      ueUsimAuthF5Star(ueInfo->sharedKey, ueInfo->opKey, authKeys->rnd,
            authKeys->ak); 

#ifdef SQN_ALGO_TS33102
      ueUsimFndHighestSQNIndx(ueInfo, &seqIndx);

      ueUsimAuthF1Star(ueInfo->sharedKey, ueInfo->opKey, authKeys->rnd,
            ueInfo->seqNmb[seqIndx], amf, macCalc);
      /*Generates MAC*/
      ueUsimAuthF1Star(ueInfo->sharedKey, ueInfo->opKey, authKeys->rnd,
            ueInfo->seqNmb[seqIndx], amf, macCalc);
      
      UE_USIM_AUTH_PRNT_HEX("Seq USED TO GENERATE AUTS FOR SYNC FAIL RSP",\
            ueInfo->seqNmb[seqIndx], UE_USIM_SEQ_NMB_SIZE);
      /*Construct AUTS*/
      for (indx = 0; indx < UE_USIM_SEQ_NMB_SIZE; indx++) 
      {
         auts[indx] = ueInfo->seqNmb[seqIndx][indx] ^ authKeys->ak[indx];
      }

#else
      /*Generates MAC*/
      ueUsimAuthF1Star(ueInfo->sharedKey, ueInfo->opKey, authKeys->rnd,
            ueInfo->seqNmb, amf, macCalc);

      /*Construct AUTS*/
      for (indx = 0; indx < UE_USIM_SEQ_NMB_SIZE; indx++) 
      {
         auts[indx] = ueInfo->seqNmb[indx] ^ authKeys->ak[indx];
      }
      UE_USIM_AUTH_PRNT_HEX("Seq USED TO GENERATE AUTS FOR SYNC FAIL RSP",\
            ueInfo->seqNmb[indx], UE_USIM_SEQ_NMB_SIZE)
#endif

      for (indx = 0; indx < UE_USIM_MAC_SIZE; indx++) 
      {
         auts[UE_USIM_SEQ_NMB_SIZE + indx] = macCalc[indx];
      }
      UE_USIM_AUTH_PRNT_HEX("Auts Genarated for sync failure",auts,
            UE_AUTS_SIZE);
      RETVALUE(RFAILED);
   }

   /*Calculate MAC Based On Rcvd Info*/
   if (ueInfo->authAlg == UE_APP_AUTH_XOR)
   {
      ueUsimXorAuthMac(ueInfo->sharedKey, authKeys->rnd, sqnRcvd.sqn,
            amf, macCalc);
   }
   else
   {
      ueUsimAuthF1(ueInfo->sharedKey, ueInfo->opKey, authKeys->rnd,
            sqnRcvd.sqn, amf, macCalc);
   }

   if (0 != cmMemcmp(macRcvd, macCalc, UE_USIM_MAC_SIZE))
   {
      UE_USIM_AUTH_PRNT_HEX("MAC RCVD", macRcvd, UE_USIM_MAC_SIZE);
      UE_USIM_AUTH_PRNT_HEX("MAC CALC", macCalc, UE_USIM_MAC_SIZE);

      *cause = UE_APP_USIM_MAC_FAILURE;
      RETVALUE(RFAILED);
   }

   /*Generate KASME*/
   ueUsimGenKasme(authKeys->ck, authKeys->ik, authKeys->ak, sqnRcvd.sqn,
         plmn, kasme);

   /*Update The UE's Sqn Number For Future Use*/
#ifndef SQN_ALGO_TS33102
   ueUsimUpdSeqNmb(ueInfo, sqnRcvd.sqn);
#endif

   RETVALUE(ROK);
}


/********************************************************************
 *
 *       Fun:   ueUsimGenAuthRspTst
 *       
 *       Desc:  This function generates Auth RES and KASME or AUTS
 *       
 *       Ret:   ROK
 *              RFAILED
 *       
 *       Notes:     
 *              
 *       File:  
 ********************************************************************/
#ifdef ANSI
PUBLIC S16 ueUsimGenAuthRspTst
(
UeUsimUeAuthInfo *ueInfo, 
U8              *autn, 
U8              *rnd, 
U8              *plmn,
U8              *res, 
U8              *kasme,
U8              *cause, 
U8              *auts
)
#else
PUBLIC S16 ueUsimGenAuthRspTst(ueInfo, autn, rnd, plmn, res, kasme, cause, auts)
UeUsimUeAuthInfo *ueInfo;
U8              *autn; 
U8              *rnd; 
U8              *plmn;
U8              *res; 
U8              *kasme,
U8              *cause; 
U8              *auts;
#endif
{
   U8 ak[UE_USIM_AK_SIZE];
   U8 ck[UE_USIM_CK_SIZE];
   U8 ik[UE_USIM_IK_SIZE];

   UE_USIM_AUTH_TRC1(ueUsimGenAuthRsp)

   UE_USIM_AUTH_PRNT_HEX("Shared Key", ueInfo->sharedKey,
                         UE_USIM_SHARED_KEY_SIZE);
   UE_USIM_AUTH_PRNT_HEX("OP Key", ueInfo->opKey, UE_USIM_OP_KEY_SIZE);
   UE_USIM_AUTH_PRNT_HEX("Rand", rnd, UE_RAND_SIZE);

   /* Implements Test Algorithms for authentication and security */
   ueUsimGenAuthVect(ueInfo->sharedKey, rnd, res, ck, ik, ak);

   RETVALUE(ROK);
}

#ifdef SQN_ALGO_TS33102 
/********************************************************************
 *
 *       Fun:   ueUsimGetSeqIndx
 *       
 *       Desc:  This function extracts SEQ and IND from SQN       
 *       
 *       Ret:   ROK
 *              RFAILED
 *       
 *       Notes:     
 *              
 *       File:  
 ********************************************************************/
PUBLIC Void ueUsimGetSeqIndx(U8 *sqn, U64 *seq, U8 *indx)
{
   UE_USIM_AUTH_TRC1(ueUsimGetSeqIndx)

   *seq = (U64) sqn[0] << 40;
   *seq |= (U64)sqn[1] << 32; 
   *seq |= (U64)sqn[2] << 24; 
   *seq |= (U64)sqn[3] << 16; 
   *seq |= (U64)sqn[4] << 8; 
   *seq |= (U64)sqn[5] ;
   *indx = (U64)sqn[5]&0x1F;
   *seq = *seq >> 5;
}

/********************************************************************
 *
 *       Fun:   ueUsimGetSqn
 *       
 *       Desc:  This function generates SQN from SEQ and IND       
 *       
 *       Ret:   ROK
 *              RFAILED
 *       
 *       Notes:     
 *              
 *       File:  
 ********************************************************************/
PUBLIC Void ueUsimGetSqn(U8 *sqn, U64 seq, U8 ind)
{
   U64 tmpseq;
   char indx = 0;

   UE_USIM_AUTH_TRC1(ueUsimGetSqn)

   tmpseq = seq;
   tmpseq = tmpseq << 5;
   indx = ind & 0x1f;
   tmpseq |= (U64)indx;
   sqn[0] =  (U8)((U64)(tmpseq & 0x0000ff0000000000)>>40);
   sqn[1] =  (U8)((U64)(tmpseq & 0x000000ff00000000)>>32);
   sqn[2] =  (U8)((U64)(tmpseq & 0x00000000ff000000)>>24);
   sqn[3] =  (U8)((U64)(tmpseq & 0x0000000000ff0000)>>16);
   sqn[4] =  (U8)((U64)(tmpseq & 0x000000000000ff00)>>8);
   sqn[5] =  (U8)(tmpseq & 0x00000000000000ff);

   UE_USIM_AUTH_PRNT_HEX("SQN:", sqn , UE_USIM_SEQ_NMB_SIZE);
}

/********************************************************************
 *
 *       Fun:   ueUsimFndHighestSQNIndx
 *       
 *       Desc:  This function finds the index of the highest SEQ in SQN table
 *       
 *       Ret:   ROK
 *              RFAILED
 *       
 *       Notes:     
 *              
 *       File:  
 ********************************************************************/
PUBLIC Void ueUsimFndHighestSQNIndx(UeUsimUeAuthInfo *ueInfo, U8 * retIndx)
{
   U8 indx, currIndx;
   U64 seq = 0;
   U64 maxSeq = 0;

   UE_USIM_AUTH_TRC1(ueUsimFndHighestSQNIndx)

   for (indx = 0; indx < UE_USIM_SEQ_NMB_INDX ; indx++)
   {
      ueUsimGetSeqIndx(ueInfo->seqNmb[indx], &seq, &currIndx);
      if (seq > maxSeq)
      {
         maxSeq = seq;
         *retIndx = currIndx;
      }
   }
   UE_USIM_AUTH_PRNT_HEX("Highest SQN:", ueInfo->seqNmb[*retIndx],
                         UE_USIM_SEQ_NMB_SIZE);
}
#endif
