/********************************************************************20**

     Name:    MME NAS Security Module

     Type:    C Source file

     Desc:    This file contains ue application message routing
              source code

     File:    ue_app_sec.c

     Sid:     ue_app_sec.c@@/main/1 - Thu Nov 17 19:35:38 2011

     Prg:     sk
*********************************************************************21*/


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
#include "ue_app_sec.h"
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
#include "ue_app_sec.x"
#include "ue_alg_intf.x"


/*Private NAS Seq Handling Functions*/
PRIVATE U16 ueAppEstimatedSeqNmb ARGS((UeAppNasSeqNmb *currSeqNmb,
                                       U8             rcvdNmb));

PRIVATE U16 ueAppGetSeqNmb ARGS((UeAppNasSeqNmb *currSeqNmb));

PRIVATE S16 ueAppIsVldSeqNmb ARGS((UeAppNasSeqNmb *currSeqNmb,
                                   U8             rcvdNmb));

PRIVATE S16 ueAppIncSeqNmb ARGS((UeAppNasSeqNmb *currSeqNmb));

PRIVATE S16 ueAppSetSeqNmb ARGS((UeAppNasSeqNmb *currSeqNmb,
                                 U8             rcvdNmb));


/*Private Utility Functions*/
PRIVATE S16 ueAppGetSecHdr ARGS((UeAppMsg     *srcMsg,
                                 UeAppSecHdr  *secHdr));

PRIVATE S16 ueAppGetEncBuf ARGS((UeAppMsg *srcMsg,
                                 U8       hdrType,
                                 U8       **msg,
                                 U16      *msgLen));

PRIVATE S16 ueAppGetIntBuf ARGS((UeAppMsg *srcMsg,
                                 U8       hdrType,
                                 U8       **msg,
                                 U16      *msgLen));

PRIVATE S16 ueAppCmpUplnkSrvReqSec ARGS((UeAppSecCtxtCb *secCtx,
                                         UeAppMsg       *srcMsg,
                                         UeAppMsg       *dstMsg));

/*Raw MAC Calculation and Ciphering Interface*/
PRIVATE S16 ueAppCalcMac ARGS((UeAppSecCtxtCb *secCtx,
                              U32            seqNmb,
                              U8             dir,
                              U8             bearer,
                              U8             *msg,
                              U16            msgLen,
                              U32            *mac));
PRIVATE S16 ueAppEncMsg ARGS((UeAppSecCtxtCb *secCtx,
                             U32            seqNmb,
                             U8             dir,
                             U8             bearer,
                             U8             *msg,
                             U16            msgLen));


/*Function Pointer Declarations*/
typedef Void (*UeAppEncFnP)(U8 *key, U32 count, U8 dir, U8 bearer,
                            U8 *msg, U16 len);

typedef U32 (*UeAppIntFnP)(U8 *key, U32 count, U8 dir, U8 bearer,
                           U8 *msg, U16 len);

typedef Void (*UeAppKeyFnP)(U8 *key, U16 keyLen, U8 *s, U16 sLen,
                            U8 *output, U16 outputLen);


/*Global Function Pointers Initialization*/
UeAppEncFnP ueAppEncFnP[UE_APP_ENC_MAX_ALG] =
                          {&ueAppEncNullAlg, 
                           &ueAppEncSnow3GAlg, 
                           &ueAppEncAESAlg, 
                           NULLP,
                           NULLP, 
                           NULLP, 
                           NULLP};

UeAppIntFnP ueAppIntFnP[UE_APP_INT_MAX_ALG] =
                          {&ueAppIntNullAlg, 
                           &ueAppIntSnow3GAlg, 
                           &ueAppIntAESAlg, 
                           NULLP,
                           NULLP, 
                           NULLP, 
                           NULLP};

UeAppKeyFnP ueAppKeyFnP = &ueAppKeyGenAlg;

/********************************************************************
 *
 *       Fun:   ueAppSecHexDump
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
PUBLIC Void ueAppSecHexDump
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
PUBLIC Void ueAppSecHexDump(mod, name, file, line, fun, buf, len)
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
   printf(" [%s] [%s:%d:%s] [HEX_DUMP]: %s[Len(%d bytes)]\n", mod, file, line, fun, name, len);
   printf(" [%s] [%s:%d:%s] [HEX_DUMP] [", mod, file, line, fun);
   for(cnt = 0; cnt < len; cnt++) 
   { 
      if((cnt != 0) &&(0 == cnt%16))
      { 
         printf(" ]\n [%s] [%s:%d:%s] [HEX_DUMP] [", mod, file, line, fun);
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

/********************************************************************
 *
 *       Fun:   ueAppEstimatedSeqNmb
 *       
 *       Desc:  This function estimates sequence number based 
 *              on received sequence number
 *       
 *       Ret:   Estimated Seq Number
 *       
 *       Notes: 
 *              
 *       File:  
 ********************************************************************/  
#ifdef ANSI
PRIVATE U16 ueAppEstimatedSeqNmb
(
UeAppNasSeqNmb *currSeqNmb, 
U8             rcvdNmb
)
#else
PRIVATE U16 ueAppEstimatedSeqNmb(currSeqNmb, rcvdNmb)
UeAppNasSeqNmb *currSeqNmb;
U8              rcvdNmb;
#endif

{
   UE_APP_SEC_TRC2(ueAppEstimatedSeqNmb)

      if(rcvdNmb >= currSeqNmb->seqNmb)
      {
         RETVALUE((currSeqNmb->ovrflwCnt << 8) | rcvdNmb);
      }

   /* We are at the edge roll over */
   if(currSeqNmb->seqNmb >= 250 ) /* 16 Seq Num Margin */
   {
      if(rcvdNmb <= 6)
      {
         RETVALUE(((currSeqNmb->ovrflwCnt+1) << 8) | rcvdNmb);
      } 
   }

   RETVALUE((currSeqNmb->ovrflwCnt << 8) | rcvdNmb);
}

/********************************************************************
 *
 *       Fun:   ueAppGetSeqNmb
 *       
 *       Desc:  This function gives 2-Bytes length sequence number
 *       
 *       Ret:   Seq Number
 *       
 *       Notes: None
 *              
 *       File:  
 *******************************************************************/
#ifdef ANSI
PRIVATE U16 ueAppGetSeqNmb
(
UeAppNasSeqNmb *currSeqNmb
)
#else
PRIVATE U16 ueAppGetSeqNmb(currSeqNmb)
UeAppNasSeqNmb *currSeqNmb;
#endif
{
   UE_APP_SEC_TRC2(ueAppGetSeqNmb)
      RETVALUE(((currSeqNmb->ovrflwCnt) <<8) | currSeqNmb->seqNmb); 
}


/********************************************************************
 *
 *       Fun:   ueAppIsVldSeqNmb
 *       
 *       Desc:  Validates the received seq number w.r.t to current
 *              sequence number
 *       
 *       Ret:   ROK
 *              RFAILED
 *       
 *       Notes: None
 *******************************************************************/              
#ifdef ANSI
PRIVATE S16 ueAppIsVldSeqNmb
(
UeAppNasSeqNmb *currSeqNmb, 
U8             rcvdNmb
)
#else
S16 ueAppIsVldSeqNmb(currSeqNmb, rcvdNmb)
(
UeAppNasSeqNmb *currSeqNmb; 
U8             rcvdNmb;
)
#endif
{
   UE_APP_SEC_TRC2(ueAppIsVldSeqNmb)

      if(ueAppGetSeqNmb(currSeqNmb) > ueAppEstimatedSeqNmb(currSeqNmb, rcvdNmb))
      {
         printf("\nueAppGetSeqNmb(currSeqNmb):%d\n",ueAppGetSeqNmb(currSeqNmb));
         printf("\nueAppEstimatedSeqNmb(currSeqNmb, rcvdNmb):%d\n", ueAppEstimatedSeqNmb(currSeqNmb, rcvdNmb));
         RETVALUE(RFAILED);
      }
      else
      {
         RETVALUE(ROK);
      }
}

/********************************************************************
 *
 *       Fun:   ueAppIncSeqNmb
 *       
 *       Desc:  Increments the sequence number
 *       
 *       Ret:   ROK
 *       
 *       Notes: None
 *******************************************************************/              
#ifdef ANSI
PRIVATE S16 ueAppIncSeqNmb
(
UeAppNasSeqNmb *currSeqNmb
)
#else
PRIVATE S16 ueAppIncSeqNmb(currSeqNmb)
UeAppNasSeqNmb *currSeqNmb;
#endif
{
   UE_APP_SEC_TRC2(ueAppIncSeqNmb)

      if(currSeqNmb->seqNmb == 255)
      { 
         currSeqNmb->ovrflwCnt++;
         currSeqNmb->seqNmb = 0;
      }
      else
      {
         currSeqNmb->seqNmb++;
      }
   RETVALUE(ROK);
}


/********************************************************************
 *
 *       Fun:   ueAppSetSeqNmb
 *       
 *       Desc:  Set the current sequence number based on received 
 *              sequence number
 *       
 *       Ret:   ROK
 *       
 *       Notes: None
 ********************************************************************/
#ifdef ANSI
PRIVATE S16 ueAppSetSeqNmb
(
UeAppNasSeqNmb *currSeqNmb, 
U8              rcvdNmb
)
#else
PRIVATE S16 ueAppSetSeqNmb(currSeqNmb, rcvdNmb)
UeAppNasSeqNmb *currSeqNmb; 
U8              rcvdNmb;
#endif
{
   S16 count = 0;

   UE_APP_SEC_TRC2(ueAppSetSeqNmb)

      count = ueAppEstimatedSeqNmb(currSeqNmb, rcvdNmb);

   currSeqNmb->ovrflwCnt = count >> 8;
   currSeqNmb->seqNmb = count & 0xFF;
   RETVALUE(ROK);
}


/********************************************************************
 *
 *       Fun:   ueAppCmpUplnkSec
 *       
 *       Desc:  Cipher and Integrity protect outgoing 
 *              NAS message at UE
 *       
 *       Ret:   ROK
 *              RFAILED
 *       
 *       Notes: None
 *******************************************************************/
#ifdef ANSI
PUBLIC S16 ueAppCmpUplnkSec
(
UeAppSecCtxtCb *secCtx, 
U8             hdrType, 
UeAppMsg       *srcMsg, 
UeAppMsg       *dstMsg
)
#else
PUBLIC S16 ueAppCmpUplnkSec(secCtx, hdrType, srcMsg, dstMsg)
UeAppSecCtxtCb *secCtx; 
U8             hdrType; 
UeAppMsg       *srcMsg; 
UeAppMsg       *dstMsg;
#endif
{
   PRIVATE U8   msg[1000] = {'\0'};
   U16          msgLen    = 0;      
   U8           bId       = 0;
   U8           dir       = 0;
   U32          seqNmb    = 0;
   U32          mac       = 0;
   S16          ret       = ROK;

   UE_APP_SEC_TRC1(ueAppCmpUplnkSec)

   if(UE_APP_SEC_HT_PLAIN_NAS_MSG == hdrType)
   {
      UE_APP_SEC_PRNT_ERR(("Plain NAS Message Is Received"));
      RETVALUE(RFAILED);
   }

   /*Service Request Is Special Case*/
   if(UE_APP_SEC_HT_SER_REQ == hdrType)
   {
      UE_APP_SEC_PRNT_ERR(("NAS Message With Service Request \
               Header Type Received"));
      ret = ueAppCmpUplnkSrvReqSec(secCtx, srcMsg, dstMsg);
      RETVALUE(ret);
   }

   /* Make a copy of original plain msg buffer */
   cmMemcpy(&msg[6], srcMsg->val, srcMsg->len);
   msgLen = srcMsg->len;

   seqNmb = ueAppGetSeqNmb(&secCtx->ulSeqNmb);

   /* preserve last used count*/
   secCtx->lstUsdCnt = seqNmb;

   if((UE_APP_SEC_HT_INT_PRTD_ENC == hdrType) ||
         (UE_APP_SEC_HT_INT_PRTD_ENC_NEW_SEC_CTXT == hdrType))
   {
      ret = ueAppEncMsg(secCtx, seqNmb, dir, bId, &msg[6], msgLen);

      if(ROK != ret)
      {
         UE_APP_SEC_PRNT_ERR(("Message Encryption Failed"));
         RETVALUE(RFAILED);
      }
   }

   msg[5] = (U8)(seqNmb & 0xff);
   msgLen++;
   /* Calculate mac for encrypted message */
   ret = ueAppCalcMac(secCtx, seqNmb, dir, bId, &msg[5], msgLen, &mac);
   if(ROK != ret) 
   {
      UE_APP_SEC_PRNT_ERR(("Mac Calculation Failed"));
      RETVALUE(RFAILED);
   }

   msg[0] = ((hdrType & 0x0f) << 4) | CM_EMM_PD;
   msg[1] = (U8)((mac>>24) & 0xff);
   msg[2] = (U8)((mac>>16) & 0xff);
   msg[3] = (U8)((mac>>8) & 0xff);
   msg[4] = (U8)((mac) & 0xff);

   msgLen = msgLen + 5;

   dstMsg->val = &msg[0];
   dstMsg->len = msgLen;

   ueAppIncSeqNmb(&secCtx->ulSeqNmb);

   RETVALUE(ROK);
}

/********************************************************************
 *
 *       Fun:   ueAppVldDwnlnkSec
 *       
 *       Desc:  Validate(Integrity check and decipher) incoming 
 *              NAS message at UE
 *       
 *       Ret:   ROK
 *              RFAILED
 *       
 *       Notes: None
 *******************************************************************/
#ifdef ANSI
PUBLIC S16 ueAppVldDwnlnkSec
(
UeAppSecCtxtCb *secCtx, 
UeAppMsg       *srcMsg, 
UeAppMsg       *dstMsg
)
#else
PUBLIC S16 ueAppVldDwnlnkSec(secCtx, srcMsg, dstMsg)
UeAppSecCtxtCb *secCtx, 
UeAppMsg       *srcMsg, 
UeAppMsg       *dstMsg
#endif
{
   UeAppSecHdr  secHdr;
   U8           *msg         = NULLP;
   U16          msgLen       = 0;      
   U8           bId          = 0;
   U8           dir          = 1;
   U32          seqNmb       = 0;
   U32          mac          = 0;
   S16          ret          = ROK;
   U8           calcmac[4];
   U8           rcvdmac[4];
   PRIVATE  U8  dstBuf[1000] = {'\0'};

   UE_APP_SEC_TRC1(ueAppVldDwnlnkSec)
   /* Get nas security header */
   ueAppGetSecHdr(srcMsg , &secHdr);

   if(UE_APP_SEC_HT_PLAIN_NAS_MSG == secHdr.hdrType)
   {
      UE_APP_SEC_PRNT_ERR(("Plain Nas Message Received"));
      RETVALUE(RFAILED);
   }

   if(RFAILED == ueAppIsVldSeqNmb(&secCtx->dlSeqNmb, secHdr.seqNmb))
   {
      UE_APP_SEC_PRNT_ERR(("Invalid Sequnce Number"));
      RETVALUE(RFAILED);
   }

   /* Adjust pointer pointing to seq num*/
   ueAppGetIntBuf(srcMsg, secHdr.hdrType, &msg, &msgLen);

   /* Get estimation of uplink seq num*/
   seqNmb = ueAppEstimatedSeqNmb(&secCtx->dlSeqNmb, secHdr.seqNmb);

   /* Calculate mac for received message */
   ret = ueAppCalcMac(secCtx, seqNmb, dir, bId, msg, msgLen, &mac);
   if(ROK != ret)
   {
      UE_APP_SEC_PRNT_ERR(("MAC Calculation Failed"));
      RETVALUE(RFAILED);
   }
   calcmac[0]= (mac & 0xff000000)>>24;
   calcmac[1]= (mac & 0x00ff0000)>>16;
   calcmac[2]= (mac & 0x0000ff00)>>8;
   calcmac[3]= mac & 0x000000ff;
   cmMemcpy(rcvdmac, srcMsg->val+1, 4);
   if(0 != cmMemcmp(calcmac, rcvdmac, 4))
   {
      UE_APP_SEC_PRNT_ERR(("MAC Verification Failed"));
      RETVALUE(RFAILED);
   }

   if((UE_APP_SEC_HT_INT_PRTD_ENC == secHdr.hdrType) ||
         (UE_APP_SEC_HT_INT_PRTD_ENC_NEW_SEC_CTXT == secHdr.hdrType))
   {
      ueAppGetEncBuf(srcMsg, secHdr.hdrType, &msg, &msgLen);

      dstMsg->val = &dstBuf[0]; /*Static memory pointer*/
      /* Make a copy of original encrypted plain msg buffer */
      cmMemcpy(dstMsg->val, msg, msgLen);
      dstMsg->len = msgLen;

      ret = ueAppEncMsg(secCtx, seqNmb, dir, bId, dstMsg->val, dstMsg->len);
      if(ROK != ret)
      {
         /* TODO: Dealloc mem dstMsg->val */
         UE_APP_SEC_PRNT_ERR(("Message Decryption Failed"));
         RETVALUE(RFAILED);
      }
   }

   ueAppSetSeqNmb(&secCtx->dlSeqNmb, secHdr.seqNmb);
   ueAppIncSeqNmb(&secCtx->dlSeqNmb);

   RETVALUE(ROK);
}


/********************************************************************
 *
 *       Fun:   ueAppCmpUplnkSrvReqSec
 *       
 *       Desc:  Cipher and Integrity protect outgoing 
 *              Service Request NAS message at UE
 *       
 *       Ret:   ROK
 *              RFAILED
 *       
 *       Notes: None
 *******************************************************************/
#ifdef ANSI
PRIVATE S16 ueAppCmpUplnkSrvReqSec
(
UeAppSecCtxtCb *secCtx,
UeAppMsg       *srcMsg,
UeAppMsg       *dstMsg
)
#else
PRIVATE S16 ueAppCmpUplnkSrvReqSec(secCtx, srcMsg, dstMsg)
UeAppSecCtxtCb *secCtx;
UeAppMsg       *srcMsg;
UeAppMsg       *dstMsg;
#endif
{
   PRIVATE U8   msg[10] = {'\0'};
   U8           msgLen  = 0;
   U8           bId     = 0;
   U8           dir     = 0;
   U32          seqNmb  = 0;
   U32          mac     = 0;
   S16          ret     = ROK;

   UE_APP_SEC_TRC2(ueAppCmpUplnkSrvReqSec)

   seqNmb = ueAppGetSeqNmb(&secCtx->ulSeqNmb);

   /* preserve last used count*/
   secCtx->lstUsdCnt = seqNmb;

   msg[0] = ((UE_APP_SEC_HT_SER_REQ << 4) & 0xF0) | CM_EMM_PD;
   msg[1] = (((secCtx->ksi & 0x07) << 5) & 0x70) | (seqNmb & 0x1F);
   msgLen+=2;

   /* Calculate mac for encrypted message */
   ret = ueAppCalcMac(secCtx, seqNmb, dir, bId, msg, msgLen, &mac);
   if(ROK != ret)
   {
      UE_APP_SEC_PRNT_ERR(("Invalid Sequnce Number"));
      RETVALUE(RFAILED);
   }
   /*Last 2 bytes of MAC is Short MAC*/
   msg[2] = (U8)((mac>>8) & 0xFF);
   msg[3] = (U8)((mac) & 0xFF);
   msgLen+=2;

   dstMsg->val = &msg[0]; /*Static memory pointer*/
   cmMemcpy(dstMsg->val, msg, msgLen);
   dstMsg->len = msgLen;

   ueAppIncSeqNmb(&secCtx->ulSeqNmb);

   RETVALUE(ROK);
}
/********************************************************************
 *
 *       Fun:   ueAppCalcMac
 *       
 *       Desc:  Calculates MAC
 *       
 *       Ret:   ROK
 *              RFAILED
 *       
 *       Notes: None
 *******************************************************************/
#ifdef ANSI
PRIVATE S16 ueAppCalcMac
(
UeAppSecCtxtCb *secCtx, 
U32            seqNmb, 
U8             dir, 
U8             bearer, 
U8             *msg, 
U16            msgLen, 
U32            *mac
)
#else
PRIVATE S16 ueAppCalcMac(secCtx, seqNmb, dir, bearer, msg, msgLen, mac)
UeAppSecCtxtCb *secCtx;
U32            seqNmb; 
U8             dir;
U8             bearer; 
U8             *msg;
U16            msgLen; 
U32            *mac;
#endif
{
   UE_APP_SEC_TRC2(ueAppCalcMac)
   if((secCtx->intAlg >= UE_APP_EIA_MAX) || (NULLP == ueAppIntFnP[secCtx->intAlg]))  
   {
      RETVALUE(RFAILED);
   }
   UE_APP_SEC_PRNT_HEX("IntKey", secCtx->intKey, UE_APP_SZ_NAS_INT_KEY);
#if 1
   UE_APP_SEC_PRNT_INFO(("Seq Nmb:%x", seqNmb));
#endif
   UE_APP_SEC_PRNT_INFO(("Dir:%x", dir));
   UE_APP_SEC_PRNT_INFO(("Bearer:%x", bearer));
   UE_APP_SEC_PRNT_HEX("Message", msg, msgLen);

   *mac = ueAppIntFnP[secCtx->intAlg](secCtx->intKey, seqNmb, dir, bearer, msg, msgLen);
#if 1
   UE_APP_SEC_PRNT_INFO(("Mac:%x", *mac));
#endif
   RETVALUE(ROK);
}

/********************************************************************
 *
 *       Fun:   ueAppEncMsg
 *       
 *       Desc:  Encrypt the message 
 *       
 *       Ret:   ROK
 *              RFAILED
 *       
 *       Notes: None
 *******************************************************************/
#ifdef ANSI
PRIVATE S16 ueAppEncMsg
(
UeAppSecCtxtCb *secCtx, 
U32            seqNmb, 
U8             dir, 
U8             bearer, 
U8             *msg, 
U16            msgLen
)
#else
PRIVATE S16 ueAppEncMsg(secCtx, seqNmb, dir, bearer, msg, msgLen)
UeAppSecCtxtCb *secCtx; 
U32            seqNmb;
U8             dir;
U8             bearer; 
U8             *msg;
U16            msgLen;
#endif
{
   UE_APP_SEC_TRC2(ueAppEncMsg)

   if((secCtx->encAlg >= UE_APP_EEA_MAX) || (NULLP == ueAppEncFnP[secCtx->encAlg]))
   {
      /*UE_APP_DBG_ERROR((UE_APP_PRNTBUF, "Enc Alg Not Supported(%d)", secCtx->intAlg));*/
      RETVALUE(RFAILED);
   }

   UE_APP_SEC_PRNT_HEX("EncKey", secCtx->encKey, UE_APP_SZ_NAS_ENC_KEY);
#if 1
   UE_APP_SEC_PRNT_INFO(("Seq Nmb:%x", seqNmb));
#endif
   UE_APP_SEC_PRNT_INFO(("Dir:%x", dir));
   UE_APP_SEC_PRNT_INFO(("Bearer:%x", bearer));
   UE_APP_SEC_PRNT_HEX("Message", msg, msgLen);

   ueAppEncFnP[secCtx->encAlg](secCtx->encKey, seqNmb, dir, bearer, msg, msgLen);

   UE_APP_SEC_PRNT_HEX("Enc Message", msg, msgLen);

   RETVALUE(ROK);
}

/********************************************************************
 *
 *       Fun:   ueAppGenerateNasKey
 *       
 *       Desc:  Generate NAS encryption and integrity keys 
 *              
 *       
 *       Ret:   ROK
 *              RFAILED
 *       
 *       Notes: None
 *******************************************************************/
#ifdef ANSI
S16 ueAppGenerateNasKey
(
UeAppSecCtxtCb *secCtx
)
#else
S16 ueAppGenerateNasKey(secCtx)
UeAppSecCtxtCb *secCtx;
#endif
{
   U8 s[7] = {'\0'};

   UE_APP_SEC_TRC2(ueAppGenerateNasKey)

   if(NULLP == ueAppKeyFnP)
   {
      RETVALUE(RFAILED);
   }

   /*NAS INT Key Gen*/ 
   s[0]= 0x15;
   s[1]= 0x02;
   s[2]= 0;
   s[3]= 1;
   s[4]= secCtx->intAlg;
   s[5]= 0;
   s[6]= 1;


   UE_APP_SEC_PRNT_HEX("Kasme Key", secCtx->kasme, UE_APP_SZ_KASME_KEY);
   UE_APP_SEC_PRNT_HEX("S Key", s, 7);

   ueAppKeyFnP(secCtx->kasme, UE_APP_SZ_KASME_KEY, s, 7, 
         secCtx->intKey, UE_APP_SZ_NAS_INT_KEY);

   UE_APP_SEC_PRNT_HEX("Int Key", secCtx->intKey, UE_APP_SZ_NAS_INT_KEY);

   /*NAS ENC Key Gen*/
   s[0]= 0x15;
   s[1]= 0x01;
   s[2]= 0;
   s[3]= 1;
   s[4]= secCtx->encAlg;
   s[5]= 0;
   s[6]= 1;

   UE_APP_SEC_PRNT_HEX("Kasme Key", secCtx->kasme, UE_APP_SZ_KASME_KEY);
   UE_APP_SEC_PRNT_HEX("S Key", s, 7);

   ueAppKeyFnP(secCtx->kasme, UE_APP_SZ_KASME_KEY, s, 7, 
         secCtx->encKey, UE_APP_SZ_NAS_ENC_KEY);

   UE_APP_SEC_PRNT_HEX("Enc Key", secCtx->encKey, UE_APP_SZ_NAS_ENC_KEY);

   RETVALUE(ROK);
}


/********************************************************************
 *
 *       Fun:   ueAppGenerateEnbKey
 *       
 *       Desc:  Generates ENB Keys
 *       
 *       Ret:   ROK
 *              RFAILED
 *       
 *       Notes: None
 *******************************************************************/
#ifdef ANSI
PUBLIC S16 ueAppGenerateEnbKey
(
UeAppSecCtxtCb *secCtx,
U32            count
)
#else
PUBLIC S16 ueAppGenerateEnbKey(secCtx, count)
UeAppSecCtxtCb *secCtx;
U32            count;
#endif
{
   U8 s[7] = {'\0'};

   UE_APP_SEC_TRC2(ueAppGenerateEnbKey)

   if(NULLP == ueAppKeyFnP)
   {
      RETVALUE(RFAILED);
   }

   s[0]= 0x11;
   s[1]= count &0xFF;
   s[2]= ((count>>8) &0xFF);
   s[3]= ((count>>16) &0xFF);
   s[4]= ((count>>24) &0xFF);
   s[5]= 0;
   s[6]= 4;

   UE_APP_SEC_PRNT_HEX("Kasme Key", secCtx->kasme, UE_APP_SZ_KASME_KEY);
   UE_APP_SEC_PRNT_HEX("S Key", s, 7);
   ueAppKeyFnP(secCtx->kasme, UE_APP_SZ_KASME_KEY, s, 7, 
         secCtx->enbKey, UE_APP_SZ_ENB_KEY);

   UE_APP_SEC_PRNT_HEX("S Key", secCtx->enbKey, UE_APP_SZ_ENB_KEY);
   RETVALUE(ROK);
}


#ifdef ANSI
PRIVATE S16 ueAppGetSecHdr
(
UeAppMsg     *srcMsg,
UeAppSecHdr  *secHdr
)
#else
PRIVATE S16 ueAppGetSecHdr()
UeAppMsg     *srcMsg;
UeAppSecHdr  *secHdr;
#endif
{
   UE_APP_SEC_TRC2(ueAppGetSecHdr)

   secHdr->pd = srcMsg->val[0] & 0x0f;
   secHdr->hdrType = (srcMsg->val[0] & 0xf0) >> 4;
   secHdr->mac = srcMsg->val[1];
   secHdr->mac = (secHdr->mac <<8) | srcMsg->val[2];
   secHdr->mac = (secHdr->mac <<8) | srcMsg->val[3];
   secHdr->mac = (secHdr->mac <<8) | srcMsg->val[4];
   secHdr->seqNmb = srcMsg->val[5]; 

   RETVALUE(ROK);
}

#ifdef ANSI
PRIVATE S16 ueAppGetIntBuf
(
UeAppMsg *srcMsg, 
U8       hdrType,
U8       **msg,
U16      *msgLen
)
#else
PRIVATE S16 ueAppGetIntBuf(srcMsg, hdrType, msg, msgLen)
UeAppMsg *srcMsg;
U8       hdrType;
U8       **msg;
U16      *msgLen;
#endif
{
   UE_APP_SEC_TRC2(ueAppGetIntBuf)

   *msg = (srcMsg->val) +
      (1 /*(pd+hdrType)*/+
       4 /*mac*/);
   *msgLen = srcMsg->len -
      (1 /*(pd+hdrType)*/+
       4 /*mac*/);

   UNUSED(hdrType);
   RETVALUE(ROK);
}

#ifdef ANSI
PRIVATE S16 ueAppGetEncBuf
(
UeAppMsg *srcMsg, 
U8       hdrType, 
U8       **msg, 
U16      *msgLen
)
#else
PRIVATE S16 ueAppGetEncBuf(srcMsg, hdrType, msg, msgLen)
UeAppMsg *srcMsg; 
U8       hdrType; 
U8       **msg;
U16      *msgLen;
#endif
{
   UE_APP_SEC_TRC2(ueAppGetEncBuf)

   *msg = (srcMsg->val) +
      (1 /*(pd+hdrType)*/+
       4 /*mac*/+
       1 /*seqNmb*/);
   *msgLen = srcMsg->len -
      (1 /*(pd+hdrType)*/+
       4 /*mac*/+
       1 /*seqNmb*/);

   UNUSED(hdrType);
   RETVALUE(ROK);
}
