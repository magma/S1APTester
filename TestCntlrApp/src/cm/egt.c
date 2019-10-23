
/********************************************************************20**

     Name:     Upper interface for eGTP - EGT

     Type:     C source file

     Desc:     C source code for common packing and un-packing
               functions for upper interface.

     File:     egt.c

     Sid:      egt.c@@/main/14 - Wed Jun  5 16:46:20 2013

     Prg:      kc

*********************************************************************21*/


/***********************************************************************
 *
 *     This software may be combined with the following TRILLIUM
 *     software:
 *
 *     part no.                      description
 *     --------    ----------------------------------------------
 *
 *
 ***********************************************************************/

/***********************************************************************
 *        H E A D E R  I N C L U D E  F I L E S (.h)                   *
 ***********************************************************************/
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* General */
#include "ssi.h"           /* System Services */
#include "cm_tkns.h"       /* common tokens */
#include "cm_hash.h"       /* common structs 1 */
#include "cm_mblk.h"       /* common memory */
#include "cm_llist.h"      /* cm link list */
#include "cm5.h"           /* common structs 3 */
#include "cm_inet.h"       /* common tokens  */
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport */
#include "cm_dns.h"        /* common transport */
#include "egt.h"           /* GTP Upper Interface */
#include "eg.h"           /* GTP Upper Interface */
#include "eg_util.h"       /* GTP Utility Module */


/***********************************************************************
 *     H E A D E R / E X T E R N   I N C L U D E  F I L E S (.h)       *
 ***********************************************************************/
#include "gen.x"           /* General */
#include "ssi.x"           /* System Services */
#include "cm_tkns.x"       /* common tokens */
#include "cm_hash.x"       /* common structs 1 */
#include "cm_lib.x"        /* common library */
#include "cm_mblk.x"       /* common memory */
#include "cm_llist.x"      /* cm link list */
#include "cm5.x"           /* common structs 3 */
#include "cm_inet.x"       /* common transport */
#include "cm_tpt.x"        /* common transport */
#include "cm_dns.x"        /* common transport */
#include "egt.x"           /* GTP Upper Interface */
#include "eg_util.x"       /* GTP Utility Module */


#if (defined(LCEGT) || defined(LWLCEGT))

#ifdef ANSI
PUBLIC S16 cmPkEgtBndReq
(
Pst* pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 cmPkEgtBndReq(pst, suId, spId)
Pst* pst;
SuId suId;
SpId spId;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkEgtBndReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RETVALUE(RFAILED);
   }
   CMCHKPKLOG(SPkS16,spId, mBuf, EEGT001, pst);
   CMCHKPKLOG(SPkS16,suId, mBuf, EEGT002, pst);
   pst->event = (Event) EVTEGTBNDREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkEgtBndReq
(
EgtBndReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgtBndReq(func, pst, mBuf)
EgtBndReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   SpId spId;
   
   TRC3(cmUnpkEgtBndReq)
   CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, EEGT003, pst);
   CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, EEGT004, pst);
   
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, spId));
}

#ifdef ANSI
PUBLIC S16 cmPkEgtBndCfm
(
Pst * pst,
SuId suId,
U8 status
)
#else
PUBLIC S16 cmPkEgtBndCfm(pst, suId, status)
Pst * pst;
SuId suId;
U8 status;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkEgtBndCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RETVALUE(RFAILED);
   }
   CMCHKPKLOG(SPkU8,status,mBuf,EEGT005,pst);
   CMCHKPKLOG(SPkS16,suId, mBuf, EEGT006, pst);
   pst->event = (Event) EVTEGTBNDCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkEgtBndCfm
(
EgtBndCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgtBndCfm(func, pst, mBuf)
EgtBndCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   U8 status;
   
   TRC3(cmUnpkEgtBndCfm)

   CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, EEGT007, pst);
   CMCHKUNPKLOG(SUnpkU8, &status, mBuf, EEGT008, pst);
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, status));
}

#ifdef ANSI
PUBLIC S16 cmPkEgtUbndReq
(
Pst * pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 cmPkEgtUbndReq(pst, spId, reason)
Pst * pst;
SpId spId;
Reason reason;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkEgtUbndReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RETVALUE(RFAILED);
   }
   CMCHKPKLOG(SPkS16,reason, mBuf, EEGT009, pst);
   CMCHKPKLOG(SPkS16,spId, mBuf, EEGT010, pst);
   pst->event = (Event) EVTEGTUBNDREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkEgtUbndReq
(
EgtUbndReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgtUbndReq(func, pst, mBuf)
EgtUbndReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   Reason reason;
   
   TRC3(cmUnpkEgtUbndReq)

   CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, EEGT011, pst);
   CMCHKUNPKLOG(SUnpkS16, &reason, mBuf, EEGT012, pst);
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, reason));
}

#ifdef EGTP_C
#ifdef ANSI
PUBLIC S16 cmPkEgtSigReq
(
Pst * pst,
SpId spId,
CmTptAddr * localAddr,
CmTptAddr * remAddr,
TknU32 lclTeid,
TknU32 transId,
TknU8 crtFlag,
TmrCfg t3,
EgMsg * egMsg
)
#else
PUBLIC S16 cmPkEgtSigReq(pst, spId, localAddr, remAddr, lclTeid, transId, crtFlag, t3, egMsg)
Pst * pst;
SpId spId;
CmTptAddr * localAddr;
CmTptAddr * remAddr;
TknU32 lclTeid;
TknU32 transId;
TknU8 crtFlag;
TmrCfg t3;
EgMsg * egMsg;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkEgtSigReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RETVALUE(RFAILED);
   }
   if (pst->selector == EGT_SEL_LC) {
      CMCHKPKLOG(cmPkEgMsg,egMsg, mBuf, EEGT013, pst);
   }
   else if (pst->selector == EGT_SEL_LWLC) {
      CMCHKPKLOG(cmPkPtr,((PTR)egMsg), mBuf, EEGT014, pst);
   }
   CMCHKPKLOG(cmPkTmrCfg,(&t3), mBuf, EEGT015, pst);
   CMCHKPKLOG(cmPkTknU8,(&crtFlag), mBuf, EEGT016, pst);
   CMCHKPKLOG(cmPkTknU32,(&transId), mBuf, EEGT017, pst);
   CMCHKPKLOG(cmPkTknU32,(&lclTeid), mBuf, EEGT018, pst);
   CMCHKPKLOG(cmPkCmTptAddr,remAddr, mBuf, EEGT019, pst);
   CMCHKPKLOG(cmPkCmTptAddr, localAddr, mBuf, EEGT020, pst);
   CMCHKPKLOG(SPkS16, spId, mBuf, EEGT021, pst);
   if (pst->selector != EGT_SEL_LWLC) {
      EGDEALLOC(egMsg, mBuf, TRUE);
   }
   pst->event = (Event) EVTEGTSIGREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkEgtSigReq
(
EgtSigReq func,
Pst *pst,
Buffer *mBuf,
Mem    *memInfo
)
#else
PUBLIC S16 cmUnpkEgtSigReq(func, pst, mBuf,memInfo)
EgtSigReq func;
Pst *pst;
Buffer *mBuf;
Mem    *memInfo;
#endif
{
   SpId spId;
   CmTptAddr localAddr;
   CmTptAddr remAddr;
   TknU32 lclTeid;
   TknU32 transId;
   TknU8 crtFlag;
   TmrCfg t3;
   EgMsg *egMsg = NULLP;
   
   TRC3(cmUnpkEgtSigReq)
   
   cmMemset((U8 *) &localAddr, 0, sizeof(CmTptAddr));
   cmMemset((U8 *) &remAddr, 0, sizeof(CmTptAddr)); 
   cmMemset((U8 *)&lclTeid, 0 , sizeof(TknU32));
   cmMemset((U8 *)&transId, 0 , sizeof(TknU32));
   cmMemset((U8 *)&crtFlag, 0 , sizeof(TknU8));
   cmMemset((U8 *)&t3, 0 , sizeof(TmrCfg));

   CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, EEGT022, pst);
   CMCHKUNPKLOG(cmUnpkCmTptAddr, &localAddr, mBuf, EEGT023, pst);
   CMCHKUNPKLOG(cmUnpkCmTptAddr, &remAddr, mBuf, EEGT024, pst);
   CMCHKUNPKLOG(cmUnpkTknU32, &lclTeid, mBuf, EEGT025, pst);
   CMCHKUNPKLOG(cmUnpkTknU32, &transId, mBuf, EEGT026, pst);
   CMCHKUNPKLOG(cmUnpkTknU8, &crtFlag, mBuf, EEGT027, pst);
   CMCHKUNPKLOG(cmUnpkTmrCfg, &t3, mBuf, EEGT028, pst);
   if (pst->selector != EGT_SEL_LWLC) {
      if ((EgUtilAllocGmMsg(&egMsg, memInfo)) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector == EGT_SEL_LWLC) {
      CMCHKUNPKLOG(cmUnpkPtr, ((PTR *)&egMsg), mBuf, EEGT029, pst);
   }
   else if (pst->selector == EGT_SEL_LC) 
      if (cmUnpkEgMsg(egMsg, mBuf) != ROK) {
      EGDEALLOC(egMsg, mBuf, FALSE);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, &localAddr, &remAddr, lclTeid, transId, crtFlag, t3, egMsg));
}

#ifdef ANSI
PUBLIC S16 cmPkEgtSigInd
(
Pst * pst,
SuId suId,
CmTptAddr * localAddr,
CmTptAddr * remAddr,
TknU32 lclTeid,
EgMsg * egMsg
)
#else
PUBLIC S16 cmPkEgtSigInd(pst, suId, localAddr, remAddr, lclTeid, egMsg)
Pst * pst;
SuId suId;
CmTptAddr * localAddr;
CmTptAddr * remAddr;
TknU32 lclTeid;
EgMsg * egMsg;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkEgtSigInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RETVALUE(RFAILED);
   }
   if (pst->selector == EGT_SEL_LC) {
      CMCHKPKLOG(cmPkEgMsg, egMsg, mBuf, EEGT030, pst);
   }
   else if (pst->selector == EGT_SEL_LWLC) {
      CMCHKPKLOG(cmPkPtr, ((PTR)egMsg), mBuf, EEGT031, pst);
   }
   CMCHKPKLOG(cmPkTknU32,(&lclTeid), mBuf, EEGT032, pst);
   CMCHKPKLOG(cmPkCmTptAddr,(remAddr), mBuf, EEGT033, pst);
   CMCHKPKLOG(cmPkCmTptAddr,(localAddr), mBuf, EEGT034, pst);
   CMCHKPKLOG(SPkS16,(suId), mBuf, EEGT035, pst);
   if (pst->selector != EGT_SEL_LWLC) {
      EGDEALLOC(egMsg, mBuf, TRUE);
   }
   pst->event = (Event) EVTEGTSIGIND;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkEgtSigInd
(
EgtSigInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgtSigInd(func, pst, mBuf)
EgtSigInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   CmTptAddr localAddr;
   CmTptAddr remAddr;
   TknU32 lclTeid;
   EgMsg *egMsg = NULLP;
   /* temporary memory information for packing the EGTP message */
   Mem       memInfo;
   
   TRC3(cmUnpkEgtSigInd)

   memInfo.region = pst->region;
   memInfo.pool = pst->pool;

   cmMemset((U8 *) &localAddr, 0, sizeof(CmTptAddr));
   cmMemset((U8 *) &remAddr, 0, sizeof(CmTptAddr)); 
   cmMemset((U8 *)&lclTeid, 0 , sizeof(TknU32));
 
   CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, EEGT036, pst);
   CMCHKUNPKLOG(cmUnpkCmTptAddr, &localAddr, mBuf, EEGT037, pst);
   CMCHKUNPKLOG(cmUnpkCmTptAddr, &remAddr, mBuf, EEGT038, pst);
   CMCHKUNPKLOG(cmUnpkTknU32, &lclTeid, mBuf, EEGT039, pst);
   if (pst->selector != EGT_SEL_LWLC) {
      if ((EgUtilAllocGmMsg(&egMsg, &memInfo)) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector == EGT_SEL_LWLC) {
      CMCHKUNPKLOG(cmUnpkPtr,((PTR *)&egMsg), mBuf, EEGT040, pst);
   }
   else if (pst->selector == EGT_SEL_LC) 
      if (cmUnpkEgMsg(egMsg, mBuf) != ROK) {
      EGDEALLOC(egMsg, mBuf, FALSE);
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, &localAddr, &remAddr, lclTeid, egMsg));
}

#ifdef ANSI
PUBLIC S16 cmPkEgtSigRsp
(
Pst * pst,
SpId spId,
TknU32 lclTeid,
EgMsg * egMsg
)
#else
PUBLIC S16 cmPkEgtSigRsp(pst, spId, lclTeid, egMsg)
Pst * pst;
SpId spId;
TknU32 lclTeid;
EgMsg * egMsg;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkEgtSigRsp)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RETVALUE(RFAILED);
   }
   if (pst->selector == EGT_SEL_LC) {
      CMCHKPKLOG(cmPkEgMsg, egMsg, mBuf, EEGT041, pst);
   }
   else if (pst->selector == EGT_SEL_LWLC) {
      CMCHKPKLOG(cmPkPtr, ((PTR)egMsg), mBuf, EEGT042, pst);
   }
   CMCHKPKLOG(cmPkTknU32, (&lclTeid), mBuf, EEGT043, pst);
   CMCHKPKLOG(SPkS16, spId, mBuf, EEGT044, pst);
   if (pst->selector != EGT_SEL_LWLC) {
      EGDEALLOC(egMsg, mBuf, TRUE);
   }
   pst->event = (Event) EVTEGTSIGRSP;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkEgtSigRsp
(
EgtSigRsp func,
Pst *pst,
Buffer *mBuf,
Mem    *memInfo
)
#else
PUBLIC S16 cmUnpkEgtSigRsp(func, pst, mBuf,memInfo)
EgtSigRsp func;
Pst *pst;
Buffer *mBuf;
Mem    *memInfo;
#endif
{
   SpId spId;
   TknU32 lclTeid;
   EgMsg *egMsg = NULLP;

   TRC3(cmUnpkEgtSigRsp)

 
   CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, EEGT045, pst);
   CMCHKUNPKLOG(cmUnpkTknU32, &lclTeid, mBuf, EEGT046, pst);
   if (pst->selector != EGT_SEL_LWLC) {
      if ((EgUtilAllocGmMsg(&egMsg, memInfo)) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector == EGT_SEL_LWLC) {
      CMCHKUNPKLOG(cmUnpkPtr,((PTR *)&egMsg), mBuf, EEGT047, pst);
   }
   else if (pst->selector == EGT_SEL_LC) 
      if (cmUnpkEgMsg(egMsg, mBuf) != ROK) {
      EGDEALLOC(egMsg, mBuf, FALSE);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, lclTeid, egMsg));
}

#ifdef ANSI
PUBLIC S16 cmPkEgtSigCfm
(
Pst * pst,
SuId suId,
CmTptAddr * localAddr,
CmTptAddr * remAddr,
TknU32 transId,
TknU32 lclTeid,
EgMsg * egMsg
)
#else
PUBLIC S16 cmPkEgtSigCfm(pst, suId, localAddr, remAddr, transId, lclTeid, egMsg)
Pst * pst;
SuId suId;
CmTptAddr * localAddr;
CmTptAddr * remAddr;
TknU32 transId;
TknU32 lclTeid;
EgMsg * egMsg;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkEgtSigCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RETVALUE(RFAILED);
   }
   if (pst->selector == EGT_SEL_LC) {
      CMCHKPKLOG(cmPkEgMsg, egMsg, mBuf, EEGT048, pst);
   }
   else if (pst->selector == EGT_SEL_LWLC) {
      CMCHKPKLOG(cmPkPtr, ((PTR)egMsg), mBuf, EEGT049, pst);
   }
   CMCHKPKLOG(cmPkTknU32, (&lclTeid), mBuf, EEGT050, pst);
   CMCHKPKLOG(cmPkTknU32, (&transId), mBuf, EEGT051, pst);
   CMCHKPKLOG(cmPkCmTptAddr, remAddr, mBuf, EEGT052, pst);
   CMCHKPKLOG(cmPkCmTptAddr, localAddr, mBuf, EEGT053, pst);
   CMCHKPKLOG(SPkS16, suId, mBuf, EEGT054, pst);

   if (pst->selector != EGT_SEL_LWLC) {
      EGDEALLOC(egMsg, mBuf, TRUE);
   }
   pst->event = (Event) EVTEGTSIGCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkEgtSigCfm
(
EgtSigCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgtSigCfm(func, pst, mBuf)
EgtSigCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   CmTptAddr localAddr;
   CmTptAddr remAddr;
   TknU32 transId;
   TknU32 lclTeid;
   EgMsg *egMsg = NULLP;
   /* temporary memory information for packing the EGTP message */
   Mem       memInfo;

   TRC3(cmUnpkEgtSigCfm)

   memInfo.region = pst->region;
   memInfo.pool = pst->pool;

   cmMemset((U8 *)&localAddr, 0, sizeof(CmTptAddr));
   cmMemset((U8 *)&remAddr, 0, sizeof(CmTptAddr)); 
   cmMemset((U8 *)&lclTeid, 0 , sizeof(TknU32));
   cmMemset((U8 *)&transId, 0 , sizeof(TknU32));


   CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, EEGT055, pst);
   CMCHKUNPKLOG(cmUnpkCmTptAddr, &localAddr, mBuf, EEGT056, pst);
   CMCHKUNPKLOG(cmUnpkCmTptAddr, &remAddr, mBuf, EEGT057, pst);
   CMCHKUNPKLOG(cmUnpkTknU32, &transId, mBuf, EEGT058, pst);
   CMCHKUNPKLOG(cmUnpkTknU32, &lclTeid, mBuf, EEGT059, pst);
   if (pst->selector != EGT_SEL_LWLC) {
      if ((EgUtilAllocGmMsg(&egMsg, &memInfo)) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector == EGT_SEL_LWLC) {
      CMCHKUNPKLOG(cmUnpkPtr, (PTR *)&egMsg, mBuf, EEGT060, pst);
   }
   else if (pst->selector == EGT_SEL_LC) 
      if (cmUnpkEgMsg(egMsg, mBuf) != ROK) {
      EGDEALLOC(egMsg, mBuf, FALSE);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, &localAddr, &remAddr, transId, lclTeid, egMsg));
}

#ifdef ANSI
PUBLIC S16 cmPkEgtLclDelReq
(
Pst * pst,
SpId spId,
U32 transId,
U32 teid
)
#else
PUBLIC S16 cmPkEgtLclDelReq(pst, spId, transId, teid)
Pst * pst;
SpId spId;
U32 transId;
U32 teid;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkEgtLclDelReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RETVALUE(RFAILED);
   }
   CMCHKPKLOG(SPkU32, teid, mBuf, EEGT061, pst);
   CMCHKPKLOG(SPkU32, transId, mBuf, EEGT062, pst);
   CMCHKPKLOG(SPkS16, spId, mBuf, EEGT063, pst);
   pst->event = (Event) EVTEGTLCLDELREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkEgtLclDelReq
(
EgtLclDelReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgtLclDelReq(func, pst, mBuf)
EgtLclDelReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   U32 transId;
   U32 teid;
   
   TRC3(cmUnpkEgtLclDelReq)

   CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, EEGT064, pst);
   CMCHKUNPKLOG(SUnpkU32, &transId, mBuf, EEGT065, pst);
   CMCHKUNPKLOG(SUnpkU32, &teid, mBuf, EEGT066, pst);
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, transId, teid));
}

#ifdef ANSI
PUBLIC S16 cmPkEgtLclDelCfm
(
Pst * pst,
SuId suId,
U32 transId,
U32 teid,
CmStatus status
)
#else
PUBLIC S16 cmPkEgtLclDelCfm(pst, suId, transId, teid, status)
Pst * pst;
SuId suId;
U32 transId;
U32 teid;
CmStatus status;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkEgtLclDelCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RETVALUE(RFAILED);
   }
   CMCHKPKLOG(cmPkCmStatus, (&status), mBuf, EEGT067, pst);
   CMCHKPKLOG(SPkU32, teid, mBuf, EEGT068, pst);
   CMCHKPKLOG(SPkU32, transId, mBuf, EEGT069, pst);
   CMCHKPKLOG(SPkS16, suId, mBuf, EEGT070, pst);

   pst->event = (Event) EVTEGTLCLDELCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkEgtLclDelCfm
(
EgtLclDelCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgtLclDelCfm(func, pst, mBuf)
EgtLclDelCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   U32 transId;
   U32 teid;
   CmStatus status;
   
   TRC3(cmUnpkEgtLclDelCfm)

   CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, EEGT071, pst);
   CMCHKUNPKLOG(SUnpkU32, &transId, mBuf, EEGT072, pst);
   CMCHKUNPKLOG(SUnpkU32, &teid, mBuf, EEGT073, pst);
   CMCHKUNPKLOG(cmUnpkCmStatus, &status, mBuf, EEGT074, pst);
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, transId, teid, status));
}

/* egt_c_001.main_3  EGTP_C Path management functionality */
#ifdef EGTP_C_PTH_MGT
#ifdef ANSI
PUBLIC S16 cmPkEgtTunnModReq
(
Pst * pst,
SuId suId,
U32 transId,
U32 teid,
CmTptAddr oldDstIpAddr,
CmTptAddr newDstIpAddr
)
#else
PUBLIC S16 cmPkEgtTunnModReq(pst, suId, transId, teid, oldDstIpAddr, newDstIpAddr)
Pst * pst;
SuId suId;
U32 transId;
U32 teid;
CmTptAddr oldDstIpAddr;
CmTptAddr newDstIpAddr;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkEgtTunnModReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RETVALUE(RFAILED);
   }
   CMCHKPKLOG(cmPkCmTptAddr,&newDstIpAddr, mBuf, EEGT019, pst);
   CMCHKPKLOG(cmPkCmTptAddr,&oldDstIpAddr, mBuf, EEGT019, pst);
   CMCHKPKLOG(SPkU32, teid, mBuf, EEGT068, pst);
   CMCHKPKLOG(SPkU32, transId, mBuf, EEGT069, pst);
   CMCHKPKLOG(SPkS16, suId, mBuf, EEGT070, pst);

   pst->event = (Event) EVTEGTTUNNMODREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmPkEgtTunnModCfm
(
Pst * pst,
SuId suId,
U32 transId,
U32 teid,
CmTptAddr oldDstIpAddr,
CmTptAddr newDstIpAddr,
CmStatus status
)
#else
PUBLIC S16 cmPkEgtTunnModCfm(pst, suId, transId, teid, oldDstIpAddr, newDstIpAddr,status)
Pst * pst;
SuId suId;
U32 transId;
U32 teid;
CmTptAddr oldDstIpAddr;
CmTptAddr newDstIpAddr;
CmStatus status;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkEgtTunnModCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RETVALUE(RFAILED);
   }
   CMCHKPKLOG(cmPkCmStatus, (&status), mBuf, EEGT067, pst);
   CMCHKPKLOG(cmPkCmTptAddr,&newDstIpAddr, mBuf, EEGT019, pst);
   CMCHKPKLOG(cmPkCmTptAddr,&oldDstIpAddr, mBuf, EEGT019, pst);
   CMCHKPKLOG(SPkU32, teid, mBuf, EEGT068, pst);
   CMCHKPKLOG(SPkU32, transId, mBuf, EEGT069, pst);
   CMCHKPKLOG(SPkS16, suId, mBuf, EEGT070, pst);

   pst->event = (Event) EVTEGTTUNNMODCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkEgtTunnModCfm
(
EgtTunnModCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgtTunnModCfm(func, pst, mBuf)
EgtTunnModCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   U32 transId;
   U32 teid;
   CmStatus status;
   CmTptAddr oldDstIpAddr, newDstIpAddr;
   
   TRC3(cmUnpkEgtTunnModCfm)

   CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, EEGT071, pst);
   CMCHKUNPKLOG(SUnpkU32, &transId, mBuf, EEGT072, pst);
   CMCHKUNPKLOG(SUnpkU32, &teid, mBuf, EEGT073, pst);
   CMCHKUNPK(cmUnpkCmTptAddr,   &oldDstIpAddr, mBuf);
   CMCHKUNPK(cmUnpkCmTptAddr,   &newDstIpAddr, mBuf);
   CMCHKUNPKLOG(cmUnpkCmStatus, &status, mBuf, EEGT074, pst);
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, transId, teid, oldDstIpAddr, newDstIpAddr, status));
}

#ifdef ANSI
PUBLIC S16 cmUnpkEgtTunnModReq
(
EgtTunnModReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgtTunnModReq(func, pst, mBuf)
EgtTunnModReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   U32 transId;
   U32 teid;
   CmTptAddr oldDstIpAddr, newDstIpAddr;
   
   TRC3(cmUnpkEgtTunnModCfm)

   CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, EEGT071, pst);
   CMCHKUNPKLOG(SUnpkU32, &transId, mBuf, EEGT072, pst);
   CMCHKUNPKLOG(SUnpkU32, &teid, mBuf, EEGT073, pst);
   CMCHKUNPK(cmUnpkCmTptAddr,   &oldDstIpAddr, mBuf);
   CMCHKUNPK(cmUnpkCmTptAddr,   &newDstIpAddr, mBuf);
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, transId, teid, oldDstIpAddr, newDstIpAddr));
}
#endif

#ifdef ANSI
PUBLIC S16 cmPkEgtStaInd
(
Pst * pst,
SuId suId,
U8 eventType,
EgPathStatus * status
)
#else
PUBLIC S16 cmPkEgtStaInd(pst, suId, eventType, status)
Pst * pst;
SuId suId;
U8 eventType;
EgPathStatus * status;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkEgtStaInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RETVALUE(RFAILED);
   }
   if (pst->selector == EGT_SEL_LC) {
      if (cmPkEgPathStatus(status, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == EGT_SEL_LWLC) {
      if (cmPkPtr((PTR)status, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (SPkU8(eventType, mBuf) != ROK) {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(suId, mBuf) != ROK) {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != EGT_SEL_LWLC) {
      if (SPutSBuf(pst->region, pst->pool, (Data *)status, sizeof(EgPathStatus)) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   pst->event = (Event) EVTEGTSTAIND;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkEgtStaInd
(
EgtStaInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgtStaInd(func, pst, mBuf)
EgtStaInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   U8 eventType;
   EgPathStatus status;
   
   TRC3(cmUnpkEgtStaInd)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      /*-- egt_c_001.main_9: free memory in case of failure --*/
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SUnpkU8(&eventType, mBuf) != ROK) {
      /*-- egt_c_001.main_9: free memory in case of failure --*/
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
      if (cmUnpkEgPathStatus(&status, mBuf) != ROK) {
      /*-- egt_c_001.main_9: free memory in case of failure --*/
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, eventType, &status));
}

#ifdef ANSI
PUBLIC S16 cmPkEgtStaReq
(
Pst * pst,
SpId spId,
U8 eventType,
EgPathInfo * pathinfo
)
#else
PUBLIC S16 cmPkEgtStaReq(pst, spId, eventType, pathinfo)
Pst * pst;
SpId spId;
U8 eventType;
EgPathInfo * pathinfo;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkEgtStaReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RETVALUE(RFAILED);
   }
   CMCHKPKLOG(cmPkEgPathInfo, pathinfo, mBuf, EEGT075, pst);
   CMCHKPKLOG(SPkU8, eventType, mBuf, EEGT076, pst);
   CMCHKPKLOG(SPkS16, spId, mBuf, EEGT077, pst);

   pst->event = (Event) EVTEGTSTAREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkEgtStaReq
(
EgtStaReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgtStaReq(func, pst, mBuf)
EgtStaReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   U8 eventType;
   EgPathInfo pathinfo;
   
   TRC3(cmUnpkEgtStaReq)

   cmMemset((U8 *) &pathinfo, 0, sizeof(EgPathInfo));
   CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, EEGT078, pst);
   CMCHKUNPKLOG(SUnpkU8, &eventType, mBuf, EEGT079, pst);
   CMCHKUNPKLOG(cmUnpkEgPathInfo, &pathinfo, mBuf, EEGT080, pst);
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, eventType, &pathinfo));
}

#ifdef ANSI
PUBLIC S16 cmPkEgtStaCfm
(
Pst * pst,
SuId suId,
U8 eventType,
EgPathInfo * pathInfo,
CmStatus status
)
#else
PUBLIC S16 cmPkEgtStaCfm(pst, suId, eventType, pathInfo, status)
Pst * pst;
SuId suId;
U8 eventType;
EgPathInfo * pathInfo;
CmStatus status;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkEgtStaCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RETVALUE(RFAILED);
   }
   CMCHKPKLOG(cmPkCmStatus, (&status), mBuf, EEGT081, pst);
   CMCHKPKLOG(cmPkEgPathInfo, pathInfo, mBuf, EEGT082, pst);
   CMCHKPKLOG(SPkU8, (eventType), mBuf, EEGT083, pst);
   CMCHKPKLOG(SPkS16, suId, mBuf, EEGT084, pst);

   pst->event = (Event) EVTEGTSTACFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkEgtStaCfm
(
EgtStaCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgtStaCfm(func, pst, mBuf)
EgtStaCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   U8 eventType;
   EgPathInfo pathInfo;
   CmStatus status;
   
   cmMemset((U8 *) &pathInfo, 0, sizeof(EgPathInfo));
   TRC3(cmUnpkEgtStaCfm)

   CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, EEGT085, pst);
   CMCHKUNPKLOG(SUnpkU8, &eventType, mBuf, EEGT086, pst);
   CMCHKUNPKLOG(cmUnpkEgPathInfo, &pathInfo, mBuf, EEGT087, pst);
   CMCHKUNPKLOG(cmUnpkCmStatus, &status, mBuf, EEGT088, pst);
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, eventType, &pathInfo, status));
}

#ifdef ANSI
PUBLIC S16 cmPkEgtErrInd
(
Pst * pst,
SuId suId,
EgErrEvnt * errEvnt
)
#else
PUBLIC S16 cmPkEgtErrInd(pst, suId, errEvnt)
Pst * pst;
SuId suId;
EgErrEvnt * errEvnt;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkEgtErrInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      RETVALUE(RFAILED);
   }
   CMCHKPKLOG(cmPkEgErrEvnt, errEvnt, mBuf, EEGT089, pst);
   CMCHKPKLOG(SPkS16, suId, mBuf, EEGT090, pst);
   pst->event = (Event) EVTEGTERRIND;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkEgtErrInd
(
EgtErrInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgtErrInd(func, pst, mBuf)
EgtErrInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   EgErrEvnt errEvnt;
   
   TRC3(cmUnpkEgtErrInd)
 
   cmMemset((U8 *) &errEvnt, 0, sizeof(EgErrEvnt));
   CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, EEGT091, pst);
   CMCHKUNPKLOG(cmUnpkEgErrEvnt, &errEvnt, mBuf, EEGT092, pst);
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, &errEvnt));
}


/***********************************************************
*
*     Func : cmPkEgMsgHdr
*
*
*     Desc : _egMsgHdr 
   @brief eGTP Message Header
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgMsgHdr
(
EgMsgHdr *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgMsgHdr(param, mBuf)
EgMsgHdr *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgMsgHdr);

   /*egt_c_001.main_12: Pack  piggyback bit*/
#ifdef EG_PIGGYBACK_SUPP
   CMCHKPK(SPkU8, param->pMsgPres, mBuf);
#endif
   CMCHKPK(SPkU32, param->seqNumber, mBuf);
   CMCHKPK(SPkU32, param->teid, mBuf);
   CMCHKPK(SPkU16, param->length, mBuf);
   CMCHKPK(SPkU8, param->msgType, mBuf);
   CMCHKPK(SPkU8, param->teidPres, mBuf);
   CMCHKPK(SPkU8, param->version, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgMsgHdr
*
*
*     Desc : _egMsgHdr 
   @brief eGTP Message Header
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgMsgHdr
(
EgMsgHdr *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgMsgHdr(param, mBuf)
EgMsgHdr *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgMsgHdr);

   CMCHKUNPK(SUnpkU8, &param->version, mBuf);
   CMCHKUNPK(SUnpkU8, &param->teidPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->msgType, mBuf);
   CMCHKUNPK(SUnpkU16, &param->length, mBuf);
   CMCHKUNPK(SUnpkU32, &param->teid, mBuf);
   CMCHKUNPK(SUnpkU32, &param->seqNumber, mBuf);
   /*egt_c_001.main_12:Unpack pMsgPres*/
#ifdef EG_PIGGYBACK_SUPP
   CMCHKUNPK(SUnpkU8, &param->pMsgPres, mBuf);
#endif
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkEgDatStr4
*
*
*     Desc : String -- max 4 byte length
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgDatStr4
(
EgDatStr4 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgDatStr4(param, mBuf)
EgDatStr4 *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkEgDatStr4);

   CMCHKPK(SPkU16, param->spare1, mBuf);
   for (i=param->length-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->val[i], mBuf);
   }
   CMCHKPK(SPkU16, param->length, mBuf);
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmUnpkEgDatStr4
*
*
*     Desc : String -- max 4 byte length
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgDatStr4
(
EgDatStr4 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgDatStr4(param, mBuf)
EgDatStr4 *param;
Buffer *mBuf;
#endif
{

   U32 i;
   TRC3(cmUnpkEgDatStr4);

   CMCHKUNPK(SUnpkU16, &param->length, mBuf);
   for (i=0; i<param->length; i++) {
      CMCHKUNPK(SUnpkU8, &param->val[i], mBuf);
   }
   CMCHKUNPK(SUnpkU16, &param->spare1, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkEgDatStr8
*
*
*     Desc : String -- max 8 byte length
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgDatStr8
(
EgDatStr8 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgDatStr8(param, mBuf)
EgDatStr8 *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkEgDatStr8);


#ifdef ALIGN_64BIT
   CMCHKPK(SPkU32, param->spare2, mBuf);

#endif
   CMCHKPK(SPkU16, param->spare1, mBuf);
   for (i=param->length-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->val[i], mBuf);
   }
   CMCHKPK(SPkU16, param->length, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgDatStr8
*
*
*     Desc : String -- max 8 byte length
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgDatStr8
(
EgDatStr8 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgDatStr8(param, mBuf)
EgDatStr8 *param;
Buffer *mBuf;
#endif
{

   U32 i;
   TRC3(cmUnpkEgDatStr8);

   CMCHKUNPK(SUnpkU16, &param->length, mBuf);
   for (i=0; i<param->length; i++) {
      CMCHKUNPK(SUnpkU8, &param->val[i], mBuf);
   }
   CMCHKUNPK(SUnpkU16, &param->spare1, mBuf);

#ifdef ALIGN_64BIT
   CMCHKUNPK(SUnpkU32, &param->spare2, mBuf);

#endif
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkEgDatStr16
*
*
*     Desc : String -- max 16 byte length
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgDatStr16
(
EgDatStr16 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgDatStr16(param, mBuf)
EgDatStr16 *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkEgDatStr16);


#ifdef ALIGN_64BIT
   CMCHKPK(SPkU32, param->spare2, mBuf);

#endif
   CMCHKPK(SPkU16, param->spare1, mBuf);
   for (i=param->length-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->val[i], mBuf);
   }
   CMCHKPK(SPkU16, param->length, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgDatStr16
*
*
*     Desc : String -- max 16 byte length
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgDatStr16
(
EgDatStr16 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgDatStr16(param, mBuf)
EgDatStr16 *param;
Buffer *mBuf;
#endif
{

   U32 i;
   TRC3(cmUnpkEgDatStr16);

   CMCHKUNPK(SUnpkU16, &param->length, mBuf);
   for (i=0; i<param->length; i++) {
      CMCHKUNPK(SUnpkU8, &param->val[i], mBuf);
   }
   CMCHKUNPK(SUnpkU16, &param->spare1, mBuf);

#ifdef ALIGN_64BIT
   CMCHKUNPK(SUnpkU32, &param->spare2, mBuf);

#endif
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkEgDatStr32
*
*
*     Desc : String -- max 32 byte length
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgDatStr32
(
EgDatStr32 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgDatStr32(param, mBuf)
EgDatStr32 *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkEgDatStr32);


#ifdef ALIGN_64BIT
   CMCHKPK(SPkU32, param->spare2, mBuf);

#endif
   CMCHKPK(SPkU16, param->spare1, mBuf);
   for (i=param->length-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->val[i], mBuf);
   }
   CMCHKPK(SPkU16, param->length, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgDatStr32
*
*
*     Desc : String -- max 32 byte length
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgDatStr32
(
EgDatStr32 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgDatStr32(param, mBuf)
EgDatStr32 *param;
Buffer *mBuf;
#endif
{

   U32 i;
   TRC3(cmUnpkEgDatStr32);

   CMCHKUNPK(SUnpkU16, &param->length, mBuf);
   for (i=0; i<param->length; i++) {
      CMCHKUNPK(SUnpkU8, &param->val[i], mBuf);
   }
   CMCHKUNPK(SUnpkU16, &param->spare1, mBuf);

#ifdef ALIGN_64BIT
   CMCHKUNPK(SUnpkU32, &param->spare2, mBuf);

#endif
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkEgDatStr64
*
*
*     Desc : String -- max 64 byte length
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgDatStr64
(
EgDatStr64 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgDatStr64(param, mBuf)
EgDatStr64 *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkEgDatStr64);


#ifdef ALIGN_64BIT
   CMCHKPK(SPkU32, param->spare2, mBuf);

#endif
   CMCHKPK(SPkU16, param->spare1, mBuf);
   for (i=param->length-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->val[i], mBuf);
   }
   CMCHKPK(SPkU16, param->length, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgDatStr64
*
*
*     Desc : String -- max 64 byte length
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgDatStr64
(
EgDatStr64 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgDatStr64(param, mBuf)
EgDatStr64 *param;
Buffer *mBuf;
#endif
{

   U32 i;
   TRC3(cmUnpkEgDatStr64);

   CMCHKUNPK(SUnpkU16, &param->length, mBuf);
   for (i=0; i<param->length; i++) {
      CMCHKUNPK(SUnpkU8, &param->val[i], mBuf);
   }
   CMCHKUNPK(SUnpkU16, &param->spare1, mBuf);

#ifdef ALIGN_64BIT
   CMCHKUNPK(SUnpkU32, &param->spare2, mBuf);

#endif
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkEgDatStr
*
*
*     Desc : String to hold max length
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgDatStr
(
EgDatStr *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgDatStr(param, mBuf)
EgDatStr *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkEgDatStr);


#ifdef ALIGN_64BIT
   CMCHKPK(SPkU32, param->spare2, mBuf);

#endif
   CMCHKPK(SPkU16, param->spare1, mBuf);
   for (i=param->length-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->val[i], mBuf);
   }
   CMCHKPK(SPkU16, param->length, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgDatStr
*
*
*     Desc : String to hold max length
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgDatStr
(
EgDatStr *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgDatStr(param, mBuf)
EgDatStr *param;
Buffer *mBuf;
#endif
{

   U32 i;
   TRC3(cmUnpkEgDatStr);

   CMCHKUNPK(SUnpkU16, &param->length, mBuf);
   for (i=0; i<param->length; i++) {
      CMCHKUNPK(SUnpkU8, &param->val[i], mBuf);
   }
   CMCHKUNPK(SUnpkU16, &param->spare1, mBuf);

#ifdef ALIGN_64BIT
   CMCHKUNPK(SUnpkU32, &param->spare2, mBuf);

#endif
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkEgCause
*
*
*     Desc : Cause including an embedded "offending IE"
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgCause
(
EgCause *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgCause(param, mBuf)
EgCause *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgCause);


   CMCHKPK(SPkU8, param->ieInst, mBuf);
   CMCHKPK(SPkU16, param->ieLength, mBuf);
   CMCHKPK(SPkU8, param->ieType, mBuf);
   CMCHKPK(SPkU8, param->ieCS, mBuf);
   CMCHKPK(SPkU8, param->causeVal, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgCause
*
*
*     Desc : Cause including an embedded "offending IE"
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgCause
(
EgCause *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgCause(param, mBuf)
EgCause *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgCause);

   CMCHKUNPK(SUnpkU8, &param->causeVal, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ieCS, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ieType, mBuf);
   CMCHKUNPK(SUnpkU16, &param->ieLength, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ieInst, mBuf);
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmPkEgAMBR
*
*
*     Desc : ABMR
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgAMBR
(
EgAMBR *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgAMBR(param, mBuf)
EgAMBR *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkEgAMBR);

   CMCHKPK(SPkU32, param->uplAPNAMBR, mBuf);
   CMCHKPK(SPkU32, param->dnlAPNAMBR, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgAMBR
*
*
*     Desc : AMBR
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgAMBR
(
EgAMBR *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgAMBR(param, mBuf)
EgAMBR *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkEgAMBR);

   CMCHKUNPK(SUnpkU32, &param->dnlAPNAMBR, mBuf);
   CMCHKUNPK(SUnpkU32, &param->uplAPNAMBR, mBuf);
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmPkEgGrouped
*
*
*     Desc : Grouped
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgGrouped
(
EgGrouped *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgGrouped(param, mBuf)
EgGrouped *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkEgGrouped);
   /* no need to pack the pointer, 
    * since memory will be allocated for each IE while unpacking */

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgGrouped
*
*
*     Desc : Grouped
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgGrouped
(
EgGrouped *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgGrouped(param, mBuf)
EgGrouped *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkEgGrouped);
   /* memory for the pointer will be allocated for each IE */

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkEgIndication
*
*
*     Desc : Indication
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgIndication
(
EgIndication *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgIndication(param, mBuf)
EgIndication *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgIndication);

   CMCHKPK(SPkU8, param->isCFSIPres, mBuf);
   CMCHKPK(SPkU8, param->isCRSIPres, mBuf);
   CMCHKPK(SPkU8, param->isPPres, mBuf);
   CMCHKPK(SPkU8, param->isPTPres, mBuf);
   CMCHKPK(SPkU8, param->isSIPres, mBuf);
   CMCHKPK(SPkU8, param->isMSVPres, mBuf);
   CMCHKPK(SPkU8, param->isDAFPres, mBuf);
   CMCHKPK(SPkU8, param->isDTFPres, mBuf);
   CMCHKPK(SPkU8, param->isHIPres, mBuf);
   CMCHKPK(SPkU8, param->isDFIPres, mBuf);
   CMCHKPK(SPkU8, param->isOIPres, mBuf);
   CMCHKPK(SPkU8, param->isISRSIPres, mBuf);
   CMCHKPK(SPkU8, param->isISRAIPres, mBuf);
   CMCHKPK(SPkU8, param->isSGWCIPres, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgIndication
*
*
*     Desc : Indication
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgIndication
(
EgIndication *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgIndication(param, mBuf)
EgIndication *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgIndication);

   CMCHKUNPK(SUnpkU8, &param->isSGWCIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isISRAIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isISRSIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isOIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isDFIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isHIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isDTFPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isDAFPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isMSVPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isSIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isPTPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isPPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isCRSIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isCFSIPres, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkEgDatBoth
*
*
*     Desc : PDN address
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgDatBoth
(
EgDatBoth *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgDatBoth(param, mBuf)
EgDatBoth *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkEgDatBoth);

   /*--  egt_c_001.main_9: corrected byte packing for PAA IE --*/
   for (i=15; i >= 0; i--) {
      CMCHKPK(SPkU8, param->pdnIpv6Addr[i], mBuf);
   }
   for (i=3; i >= 0; i--) {
      CMCHKPK(SPkU8, param->pdnIpv4Addr[i], mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgDatBoth
*
*
*     Desc : PDN address
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgDatBoth
(
EgDatBoth *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgDatBoth(param, mBuf)
EgDatBoth *param;
Buffer *mBuf;
#endif
{

   U32 i;
   TRC3(cmUnpkEgDatBoth);

   /*--  egt_c_001.main_9: corrected byte unpacking for PAA IE --*/
   for (i=0; i<4; i++) {
      CMCHKUNPK(SUnpkU8, &param->pdnIpv4Addr[i], mBuf);
   }
   for (i=0; i<16; i++) {
      CMCHKUNPK(SUnpkU8, &param->pdnIpv6Addr[i], mBuf);
   }
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkEgPaa
*
*
*     Desc : PDN Address Allocation
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgPaa
(
EgPaa *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgPaa(param, mBuf)
EgPaa *param;
Buffer *mBuf;
#endif
{

   U32 i;

   TRC3(cmPkEgPaa);

   /*--  egt_c_001.main_9: corrected byte packing for PAA IE --*/
   switch(param->pdnType) {
      case EG_PAA_IPV4:
         for (i=0; i<4; i++) {
            CMCHKPK(SPkU8, param->u.pdnIpv4Addr[i], mBuf);
         }
         break;
      case EG_PAA_IPV6:
         for (i=0; i<16; i++) {
            CMCHKPK(SPkU8, param->u.pdnIpv6Addr[i], mBuf);
         }
         break;
      case EG_PAA_BOTH:
         CMCHKPK(cmPkEgDatBoth, &param->u.pdnBoth, mBuf);
         break;
      default :
         RETVALUE(RFAILED);
   }
 
   CMCHKPK(SPkU8, param->pdnPrefix, mBuf);
   CMCHKPK(SPkU8, param->pdnType, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgPaa
*
*
*     Desc : PDN Address Allocation
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgPaa
(
EgPaa *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgPaa(param, mBuf)
EgPaa *param;
Buffer *mBuf;
#endif
{

   U8 i=0;
   TRC3(cmUnpkEgPaa);

   CMCHKUNPK(SUnpkU8, &param->pdnType, mBuf);
   CMCHKUNPK(SUnpkU8, &param->pdnPrefix, mBuf);

   /*--  egt_c_001.main_9: corrected byte unpacking for PAA IE --*/
   switch(param->pdnType) {
      case EG_PAA_IPV4:
         for (i=0; i<4; i++) {
            CMCHKUNPK(SUnpkU8, &param->u.pdnIpv4Addr[3 - i], mBuf);
         }
         break;
      case EG_PAA_IPV6:
         for (i=0; i<16; i++) {
            CMCHKUNPK(SUnpkU8, &param->u.pdnIpv6Addr[15 - i], mBuf);
         }
         break;
      case EG_PAA_BOTH:
         CMCHKUNPK(cmUnpkEgDatBoth, &param->u.pdnBoth, mBuf);
         break;
      default :
         RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkEgFlowQos
*
*
*     Desc : Flow QoS
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgFlowQos
(
EgFlowQos *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgFlowQos(param, mBuf)
EgFlowQos *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgFlowQos);

   CMCHKPK(cmPkEgDatStr8, &param->dnGBR, mBuf);
   CMCHKPK(cmPkEgDatStr8, &param->upGBR, mBuf);
   CMCHKPK(cmPkEgDatStr8, &param->dnMBR, mBuf);
   CMCHKPK(cmPkEgDatStr8, &param->upMBR, mBuf);
   CMCHKPK(SPkU8, param->qci, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgFlowQos
*
*
*     Desc : Flow QoS
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgFlowQos
(
EgFlowQos *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgFlowQos(param, mBuf)
EgFlowQos *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgFlowQos);

   CMCHKUNPK(SUnpkU8, &param->qci, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr8, &param->upMBR, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr8, &param->dnMBR, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr8, &param->upGBR, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr8, &param->dnGBR, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkEgBearQos
*
*
*     Desc : Bearer QOS
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgBearQos
(
EgBearQos *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgBearQos(param, mBuf)
EgBearQos *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgBearQos);

   CMCHKPK(cmPkEgDatStr8, &param->dnGBR, mBuf);
   CMCHKPK(cmPkEgDatStr8, &param->upGBR, mBuf);
   CMCHKPK(cmPkEgDatStr8, &param->dnMBR, mBuf);
   CMCHKPK(cmPkEgDatStr8, &param->upMBR, mBuf);
   CMCHKPK(SPkU8, param->qci, mBuf);
   CMCHKPK(SPkU8, param->prityLvl, mBuf);
   CMCHKPK(SPkU8, param->isPCIPres, mBuf);
   CMCHKPK(SPkU8, param->isPVIPres, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgBearQos
*
*
*     Desc : Bearer QOS
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgBearQos
(
EgBearQos *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgBearQos(param, mBuf)
EgBearQos *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgBearQos);

   CMCHKUNPK(SUnpkU8, &param->isPVIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isPCIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->prityLvl, mBuf);
   CMCHKUNPK(SUnpkU8, &param->qci, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr8, &param->upMBR, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr8, &param->dnMBR, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr8, &param->upGBR, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr8, &param->dnGBR, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkEgSNetwork
*
*
*     Desc : Serving Network
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgSNetwork
(
EgSNetwork *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgSNetwork(param, mBuf)
EgSNetwork *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgSNetwork);

   CMCHKPK(SPkU8, param->mncDigit3, mBuf);
   CMCHKPK(SPkU8, param->mncDigit2, mBuf);
   CMCHKPK(SPkU8, param->mncDigit1, mBuf);
   CMCHKPK(SPkU8, param->mccDigit3, mBuf);
   CMCHKPK(SPkU8, param->mccDigit2, mBuf);
   CMCHKPK(SPkU8, param->mccDigit1, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgSNetwork
*
*
*     Desc : Serving Network
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgSNetwork
(
EgSNetwork *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgSNetwork(param, mBuf)
EgSNetwork *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgSNetwork);

   CMCHKUNPK(SUnpkU8, &param->mccDigit1, mBuf);
   CMCHKUNPK(SUnpkU8, &param->mccDigit2, mBuf);
   CMCHKUNPK(SUnpkU8, &param->mccDigit3, mBuf);
   CMCHKUNPK(SUnpkU8, &param->mncDigit1, mBuf);
   CMCHKUNPK(SUnpkU8, &param->mncDigit2, mBuf);
   CMCHKUNPK(SUnpkU8, &param->mncDigit3, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkEgCGI
*
*
*     Desc : Cell Global Identifier
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgCGI
(
EgCGI *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgCGI(param, mBuf)
EgCGI *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgCGI);

   CMCHKPK(SPkU16, param->ci, mBuf);
   CMCHKPK(SPkU16, param->lac, mBuf);
   CMCHKPK(cmPkEgSNetwork, &param->sNwk, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgCGI
*
*
*     Desc : Cell Global Identifier
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgCGI
(
EgCGI *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgCGI(param, mBuf)
EgCGI *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgCGI);

   CMCHKUNPK(cmUnpkEgSNetwork, &param->sNwk, mBuf);
   CMCHKUNPK(SUnpkU16, &param->lac, mBuf);
   CMCHKUNPK(SUnpkU16, &param->ci, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkEgSAI
*
*
*     Desc : Service Area Identifier
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgSAI
(
EgSAI *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgSAI(param, mBuf)
EgSAI *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgSAI);

   CMCHKPK(SPkU16, param->sac, mBuf);
   CMCHKPK(SPkU16, param->lac, mBuf);
   CMCHKPK(cmPkEgSNetwork, &param->sNwk, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgSAI
*
*
*     Desc : Service Area Identifier
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgSAI
(
EgSAI *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgSAI(param, mBuf)
EgSAI *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgSAI);

   CMCHKUNPK(cmUnpkEgSNetwork, &param->sNwk, mBuf);
   CMCHKUNPK(SUnpkU16, &param->lac, mBuf);
   CMCHKUNPK(SUnpkU16, &param->sac, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkEgRAI
*
*
*     Desc : Routing Area Identity
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgRAI
(
EgRAI *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgRAI(param, mBuf)
EgRAI *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgRAI);

   CMCHKPK(SPkU16, param->rac, mBuf);
   CMCHKPK(SPkU16, param->lac, mBuf);
   CMCHKPK(cmPkEgSNetwork, &param->sNwk, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgRAI
*
*
*     Desc : Routing Area Identity
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgRAI
(
EgRAI *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgRAI(param, mBuf)
EgRAI *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgRAI);

   CMCHKUNPK(cmUnpkEgSNetwork, &param->sNwk, mBuf);
   CMCHKUNPK(SUnpkU16, &param->lac, mBuf);
   CMCHKUNPK(SUnpkU16, &param->rac, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkEgTAI
*
*
*     Desc : Tracking Area Identifier
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgTAI
(
EgTAI *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgTAI(param, mBuf)
EgTAI *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgTAI);

   CMCHKPK(SPkU16, param->tac, mBuf);
   CMCHKPK(cmPkEgSNetwork, &param->sNwk, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgTAI
*
*
*     Desc : Tracking Area Identifier
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgTAI
(
EgTAI *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgTAI(param, mBuf)
EgTAI *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgTAI);

   CMCHKUNPK(cmUnpkEgSNetwork, &param->sNwk, mBuf);
   CMCHKUNPK(SUnpkU16, &param->tac, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkEgECGI
*
*
*     Desc : E-UTRAN Cell Global Identifier
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgECGI
(
EgECGI *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgECGI(param, mBuf)
EgECGI *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgECGI);

   CMCHKPK(SPkU32, param->ecId, mBuf);
   CMCHKPK(cmPkEgSNetwork, &param->sNwk, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgECGI
*
*
*     Desc : E-UTRAN Cell Global Identifier
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgECGI
(
EgECGI *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgECGI(param, mBuf)
EgECGI *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgECGI);

   CMCHKUNPK(cmUnpkEgSNetwork, &param->sNwk, mBuf);
   CMCHKUNPK(SUnpkU32, &param->ecId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkEgUli
*
*
*     Desc : User Location Info
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgUli
(
EgUli *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgUli(param, mBuf)
EgUli *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgUli);

   CMCHKPK(cmPkEgECGI, &param->ecgi, mBuf);
   CMCHKPK(cmPkEgTAI, &param->tai, mBuf);
   CMCHKPK(cmPkEgRAI, &param->rai, mBuf);
   CMCHKPK(cmPkEgSAI, &param->sai, mBuf);
   CMCHKPK(cmPkEgCGI, &param->cgi, mBuf);
   CMCHKPK(SPkU8, param->isECGIPres, mBuf);
   CMCHKPK(SPkU8, param->isTAIPres, mBuf);
   CMCHKPK(SPkU8, param->isRAIPres, mBuf);
   CMCHKPK(SPkU8, param->isSAIPres, mBuf);
   CMCHKPK(SPkU8, param->isCGIPres, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgUli
*
*
*     Desc : User Location Info
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgUli
(
EgUli *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgUli(param, mBuf)
EgUli *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgUli);

   CMCHKUNPK(SUnpkU8, &param->isCGIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isSAIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isRAIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isTAIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isECGIPres, mBuf);
   CMCHKUNPK(cmUnpkEgCGI, &param->cgi, mBuf);
   CMCHKUNPK(cmUnpkEgSAI, &param->sai, mBuf);
   CMCHKUNPK(cmUnpkEgRAI, &param->rai, mBuf);
   CMCHKUNPK(cmUnpkEgTAI, &param->tai, mBuf);
   CMCHKUNPK(cmUnpkEgECGI, &param->ecgi, mBuf);
   RETVALUE(ROK);
}







/***********************************************************
*
*     Func : cmPkEgFTeid
*
*
*     Desc : Fully Qualified TEID (F-TEID)
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgFTeid
(
EgFTeid *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgFTeid(param, mBuf)
EgFTeid *param;
Buffer *mBuf;
#endif
{
   S32 i;

   TRC3(cmPkEgFTeid);

   switch(param->isIPv4Pres) {
      case TRUE:
         /* egt_c_001.main_4 : correcting loop index */  
         for (i=4-1; i >= 0; i--) {
            CMCHKPK(SPkU8, param->u.ip4Addr[i], mBuf);
         }
         break;

      case FALSE:
         /* egt_c_001.main_4 : correcting loop index */  
         for (i=16-1; i >= 0; i--) {
            CMCHKPK(SPkU8, param->u.ipv6Address[i], mBuf);
         }
         break;
      default :
         RETVALUE(RFAILED);
   }

   CMCHKPK(SPkU32, param->teid, mBuf);
   CMCHKPK(SPkU8, param->intfType, mBuf);
   CMCHKPK(SPkU8, param->isIPv6Pres, mBuf);
   CMCHKPK(SPkU8, param->isIPv4Pres, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgFTeid
*
*
*     Desc : Fully Qualified TEID (F-TEID)
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgFTeid
(
EgFTeid *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgFTeid(param, mBuf)
EgFTeid *param;
Buffer *mBuf;
#endif
{
   U32 i;

   TRC3(cmUnpkEgFTeid);

   CMCHKUNPK(SUnpkU8, &param->isIPv4Pres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isIPv6Pres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->intfType, mBuf);
   CMCHKUNPK(SUnpkU32, &param->teid, mBuf);

   switch(param->isIPv4Pres) {
      case TRUE:
         /* egt_c_001.main_4 : correcting loop index */  
         for (i=0; i<4; i++) {
            CMCHKUNPK(SUnpkU8, &param->u.ip4Addr[i], mBuf);
         }
         break;
      case FALSE:
         /* egt_c_001.main_4 : correcting loop index */  
         for (i=0; i<16; i++) {
            CMCHKUNPK(SUnpkU8, &param->u.ipv6Address[i], mBuf);
         }
         break;
      default :
         RETVALUE(RFAILED);
      }

   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkEgGblCnId
*
*
*     Desc : Global CN-Id
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgGblCnId
(
EgGblCnId *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgGblCnId(param, mBuf)
EgGblCnId *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgGblCnId);

   CMCHKPK(cmPkEgDatStr4, &param->cnId, mBuf);
   CMCHKPK(cmPkEgSNetwork, &param->sNwk, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgGblCnId
*
*
*     Desc : Global CN-Id
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgGblCnId
(
EgGblCnId *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgGblCnId(param, mBuf)
EgGblCnId *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgGblCnId);

   CMCHKUNPK(cmUnpkEgSNetwork, &param->sNwk, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr4, &param->cnId, mBuf);
   RETVALUE(ROK);
}
#if 0

/***********************************************************
*
*     Func : cmPkEgBearIdList
*
*
*     Desc : Bearer ID List
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgBearIdList
(
EgBearIdList *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgBearIdList(param, mBuf)
EgBearIdList *param;
Buffer *mBuf;
#endif
{
   S32 i = 0;
   TRC3(cmPkEgBearIdList);

   for (i = param->nmbBearer-1; i >= 0; i--)
   {
      CMCHKPK(SPkU8, param->bearId[i], mBuf);
   }

   CMCHKPK(SPkU8, param->nmbBearer, mBuf);

   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmUnpkEgBearIdList
*
*
*     Desc : Bearer ID List
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgBearIdList
(
EgBearIdList *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgBearIdList(param, mBuf)
EgBearIdList *param;
Buffer *mBuf;
#endif
{
   U32 i = 0;
   TRC3(cmUnpkEgBearIdList);

   CMCHKUNPK(SUnpkU8, &param->nmbBearer, mBuf);

   for (i = 0; i < param->nmbBearer; i++)
   {
      CMCHKUNPK(SUnpkU8, &param->bearId[i], mBuf);
   }

   RETVALUE(ROK);
}
#endif /* 0 */

/***********************************************************
*
*     Func : cmPkEgCsid
*
*     Desc : Csid
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgCsid
(
EgCsid *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgCsid(param, mBuf)
EgCsid *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkEgCsid);

   CMCHKPK(SPkU8, param->nodeIdType, mBuf);
   CMCHKPK(SPkU8, param->noOfCSIDs, mBuf);
   CMCHKPK(cmPkEgDatStr16, &param->nodeId, mBuf);
   CMCHKPK(cmPkEgDatStr16,  &param->csid, mBuf);

   RETVALUE(ROK);
} /* end of cmPkEgCsid */


/***********************************************************
*
*     Func : cmUnpkEgCsid
*
*
*     Desc : Csid
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgCsid
(
EgCsid *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgCsid(param, mBuf)
EgCsid *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkEgCsid);

   CMCHKUNPK(cmUnpkEgDatStr16,  &param->csid, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr16, &param->nodeId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->noOfCSIDs, mBuf);
   CMCHKUNPK(SUnpkU8, &param->nodeIdType, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkEgCsid */


/***********************************************************
*
*     Func : cmPkEgIpAddr
*
*     Desc : IP Address
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgIpAddr
(
EgIpAddr *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgIpAddr(param, mBuf)
EgIpAddr *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkEgIpAddr);

   switch (param->type)
   {
      case CM_IPV4ADDR_TYPE:
      {
         CMCHKPK(SPkU32,     param->u.ipv4, mBuf);
         break;
      } /* end of case CM_IPV4ADDR_TYPE */

#ifdef EG_IPV6_SUPPORTED
      case CM_IPV6ADDR_TYPE:
      {
         U8 cnt = 0;

         for (; cnt < 16; cnt++)
         {
            CMCHKPK(SPkU8,   param->u.ipv6[cnt], mBuf);
         } /* end of loop */

         break;
      } /* end of case CM_IPV6ADDR_TYPE */
#endif /* EG_IPV6_SUPPORTED */

      default:
      {
         RETVALUE(RFAILED);
      } /* end of case default */
   } /* end of switch case */

   CMCHKPK(SPkU8, param->type, mBuf);

   RETVALUE(ROK);
} /* end of cmPkEgIpAddr */


/***********************************************************
*
*     Func : cmUnpkEgIpAddr
*
*
*     Desc : IP address
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgIpAddr
(
EgIpAddr *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgIpAddr(param, mBuf)
EgIpAddr *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkEgIpAddr);

   CMCHKUNPK(SUnpkU8, &param->type, mBuf);

   switch (param->type)
   {
      case CM_IPV4ADDR_TYPE:
      {
         CMCHKUNPK(SUnpkU32,      &param->u.ipv4, mBuf);
         break;
      } /* end of case CM_IPV4ADDR_TYPE */

#ifdef EG_IPV6_SUPPORTED
      case CM_IPV6ADDR_TYPE:
      {
         S8 cnt = 15;

         for (; cnt >= 0; cnt--)
         {
            CMCHKUNPK(SUnpkU8,    &param->u.ipv6[cnt], mBuf);
         } /* end of loop */

         break;
      } /* end of case CM_IPV6ADDR_TYPE */
#endif /* EG_IPV6_SUPPORTED */

      default:
      {
         RETVALUE(RFAILED);
      } /* end of case default */
   } /* end of switch case */

   RETVALUE(ROK);
} /* end of cmUnpkEgIpAddr */


/***********************************************************
*
*     Func : cmPkEgPduNum
*
*
*     Desc : PDU Numbers
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgPduNum
(
EgPduNum *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgPduNum(param, mBuf)
EgPduNum *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkEgPduNum);

   CMCHKPK(SPkU16, param->RNPduNo, mBuf);
   CMCHKPK(SPkU16, param->SNPduNo, mBuf);
   CMCHKPK(SPkU16, param->upLinkSeqNo, mBuf);
   CMCHKPK(SPkU16, param->dnLinkSeqNo, mBuf);
   CMCHKPK(SPkU8, param->nsapi, mBuf);
   RETVALUE(ROK);
} /* end of cmPkEgPduNum */



/***********************************************************
*
*     Func : cmUnpkEgPduNum
*
*
*     Desc : PDU Numbers
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgPduNum
(
EgPduNum *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgPduNum(param, mBuf)
EgPduNum *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkEgPduNum);

   CMCHKUNPK(SUnpkU8, &param->nsapi, mBuf);
   CMCHKUNPK(SUnpkU16, &param->dnLinkSeqNo, mBuf);
   CMCHKUNPK(SUnpkU16, &param->upLinkSeqNo, mBuf);
   CMCHKUNPK(SUnpkU16, &param->SNPduNo, mBuf);
   CMCHKUNPK(SUnpkU16, &param->RNPduNo, mBuf);
   RETVALUE(ROK);
} /* end of cmUnpkEgPduNum */

/***********************************************************
*
*     Func : cmPkEgTimeZone
*
*
*     Desc : Time Zone
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgTimeZone
(
EgTimeZone *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgTimeZone(param, mBuf)
EgTimeZone *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkEgTimeZone);

   CMCHKPK(SPkU8, param->timezone, mBuf);
   CMCHKPK(SPkU8, param->dayLiteSavTime, mBuf);
   RETVALUE(ROK);
} /* end of cmPkEgTimeZone */



/***********************************************************
*
*     Func : cmUnpkEgTimeZone
*
*
*     Desc : Time Zone
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgTimeZone
(
EgTimeZone *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgTimeZone(param, mBuf)
EgTimeZone *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkEgTimeZone);

   CMCHKUNPK(SUnpkU8, &param->dayLiteSavTime, mBuf);
   CMCHKUNPK(SUnpkU8, &param->timezone, mBuf);
   RETVALUE(ROK);
} /* end of cmUnpkEgTimeZone */

/***********************************************************
*
*     Func : cmPkEgTraceRef
*
*
*     Desc : Trace Reference
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgTraceRef
(
EgTraceRef *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgTraceRef(param, mBuf)
EgTraceRef *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkEgTraceRef);

   CMCHKPK(cmPkEgSNetwork, &param->sNwk, mBuf);
   CMCHKPK(SPkU32, param->trcId, mBuf);
   RETVALUE(ROK);
} /* end of cmPkEgTraceRef */



/***********************************************************
*
*     Func : cmUnpkEgTraceRef
*
*
*     Desc : Trace Reference
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgTraceRef
(
EgTraceRef *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgTraceRef(param, mBuf)
EgTraceRef *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkEgTraceRef);

   CMCHKUNPK(SUnpkU32, &param->trcId, mBuf);
   CMCHKUNPK(cmUnpkEgSNetwork, &param->sNwk, mBuf);
   RETVALUE(ROK);
} /* end of cmUnpkEgTraceRef */


/***********************************************************
*
*     Func : cmPkEgAuthQt
*
*
*     Desc : PDU Numbers
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgAuthQt
(
EgAuthQt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgAuthQt(param, mBuf)
EgAuthQt *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkEgAuthQt);

   CMCHKPK(cmPkEgDatStr16, &param->rand, mBuf);
   CMCHKPK(SPkU8,          param->xresLen, mBuf);
   CMCHKPK(cmPkEgDatStr16, &param->xres, mBuf);
   CMCHKPK(cmPkEgDatStr16, &param->ck, mBuf);
   CMCHKPK(cmPkEgDatStr16, &param->ik, mBuf);
   CMCHKPK(SPkU8,          param->autnLen, mBuf);
   CMCHKPK(cmPkEgDatStr16, &param->autn, mBuf);

   RETVALUE(ROK);
} /* end of cmPkEgAuthQt */



/***********************************************************
*
*     Func : cmUnpkEgAuthQt
*
*
*     Desc : PDU Numbers
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgAuthQt
(
EgAuthQt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgAuthQt(param, mBuf)
EgAuthQt *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkEgAuthQt);

   CMCHKUNPK(cmUnpkEgDatStr16, &param->autn, mBuf);
   CMCHKUNPK(SUnpkU8,          &param->autnLen, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr16, &param->ik, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr16, &param->ck, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr16, &param->xres, mBuf);
   CMCHKUNPK(SUnpkU8,          &param->xresLen, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr16, &param->rand, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkEgAuthQt */


/***********************************************************
*
*     Func : cmPkEgAuthQuadrup
*
*
*     Desc : PDU Numbers
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgAuthQuadrup
(
EgAuthQuadruplet *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgAuthQuadrup(param, mBuf)
EgAuthQuadruplet *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkEgAuthQuadrup);

   CMCHKPK(cmPkEgDatStr16, &param->rand, mBuf);
   CMCHKPK(SPkU8,          param->xresLen, mBuf);
   CMCHKPK(cmPkEgDatStr16, &param->xres, mBuf);
   CMCHKPK(SPkU8,          param->autnLen, mBuf);
   CMCHKPK(cmPkEgDatStr16, &param->autn, mBuf);
   CMCHKPK(cmPkEgDatStr32, &param->kasme, mBuf);

   RETVALUE(ROK);
} /* end of cmPkEgAuthQuadrup */


/***********************************************************
*
*     Func : cmUnpkEgAuthQuadrup
*
*
*     Desc : PDU Numbers
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgAuthQuadrup
(
EgAuthQuadruplet *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgAuthQuadrup(param, mBuf)
EgAuthQuadruplet *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkEgAuthQuadrup);

   CMCHKUNPK(cmUnpkEgDatStr32, &param->kasme, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr16, &param->autn, mBuf);
   CMCHKUNPK(SUnpkU8,          &param->autnLen, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr16, &param->xres, mBuf);
   CMCHKUNPK(SUnpkU8,          &param->xresLen, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr16, &param->rand, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkEgAuthQuadrup */


/***********************************************************
*
*     Func : cmPkEgGsmKeyT
*
*     Desc : MM  Context GSM Key Triplet
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgGsmKeyT
(
EgGSMKeyT *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgGsmKeyT(param, mBuf)
EgGSMKeyT *param;
Buffer *mBuf;
#endif
{
   U8 cnt = 0,cnt1 = 0;

   TRC3(cmPkEgGsmKeyT);

   CMCHKPK(SPkU8, param->secMode, mBuf);
   CMCHKPK(SPkU8, param->isDRXIPres, mBuf);
   CMCHKPK(SPkU8, param->cksn, mBuf);
   CMCHKPK(SPkU8, param->isUAMBRIPres, mBuf);
   CMCHKPK(SPkU8, param->isSAMBRIPres, mBuf);
   CMCHKPK(SPkU8, param->usedCipher, mBuf);

   for (cnt = 0; cnt < 8; cnt++)
   {
      CMCHKPK(SPkU8, param->kc[cnt], mBuf);
   } /* end of loop */

   for (cnt = 0;cnt < param->nmbTrip ; cnt++)
   {
      for(cnt1 = 0; cnt1 <= 7; cnt1 ++)
      {
        CMCHKPK(SPkU8, param->authTrip[cnt].kc[cnt1], mBuf);
      }
      for(cnt1 = 0; cnt1 <= 3; cnt1 ++)
      {
        CMCHKPK(SPkU8, param->authTrip[cnt].sres[cnt1], mBuf);
      }
      for(cnt1 = 0; cnt1 <= 15; cnt1 ++)
      {
        CMCHKPK(SPkU8, param->authTrip[cnt].rand[cnt1], mBuf);
      }
   } /* end of loop */

   CMCHKPK(SPkU8, param->nmbTrip, mBuf);

   for (cnt = 0; cnt < 2; cnt++)
   {
      CMCHKPK(SPkU8, param->drxParam[cnt], mBuf);
   } /* end of loop */

   CMCHKPK(SPkU32, param->upSubsUEAMBR, mBuf);
   CMCHKPK(SPkU32, param->dnSubsUEAMBR, mBuf);
   CMCHKPK(SPkU32, param->upUsedUEAMBR, mBuf);
   CMCHKPK(SPkU32, param->dnUsedUEAMBR, mBuf);

   CMCHKPK(cmPkEgDatStr16, &param->ueNtwrkCapb, mBuf);
   CMCHKPK(cmPkEgDatStr16, &param->msNtwrkCapb, mBuf);
   CMCHKPK(cmPkEgDatStr16, &param->meId, mBuf);

   CMCHKPK(SPkU8, param->isUNA, mBuf);
   CMCHKPK(SPkU8, param->isGENA, mBuf);
   CMCHKPK(SPkU8, param->isGANA, mBuf);
   CMCHKPK(SPkU8, param->isINA, mBuf);
   CMCHKPK(SPkU8, param->isENA, mBuf);
   CMCHKPK(SPkU8, param->isHNNA, mBuf);
#ifdef EG_REL_930
   CMCHKPK(SPkU8, param->vDomPrefUEUsageLen, mBuf);
   CMCHKPK(SPkU8, param->vDomPref, mBuf);
   CMCHKPK(SPkU8, param->ueUsageSett, mBuf);
#endif /* EG_REL_930 */

   RETVALUE(ROK);
} /* end of cmPkEgGsmKeyT */


/***********************************************************
*
*     Func : cmUnpkEgGsmKeyT
*
*     Desc : MM  Context GSM Key Triplet
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgGsmKeyT
(
EgGSMKeyT *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgGsmKeyT(param, mBuf)
EgGSMKeyT *param;
Buffer *mBuf;
#endif
{
   S16 cnt = 0,cnt1 = 0;

   TRC3(cmUnpkEgGsmKeyT);
#ifdef EG_REL_930
   CMCHKUNPK(SUnpkU8, &param->ueUsageSett, mBuf);
   CMCHKUNPK(SUnpkU8, &param->vDomPref, mBuf);
   CMCHKUNPK(SUnpkU8, &param->vDomPrefUEUsageLen, mBuf);
#endif /* EG_REL_930 */


   CMCHKUNPK(SUnpkU8, &param->isHNNA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isENA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isINA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isGANA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isGENA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isUNA, mBuf);

   CMCHKUNPK(cmUnpkEgDatStr16, &param->meId, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr16, &param->msNtwrkCapb, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr16, &param->ueNtwrkCapb, mBuf);

   CMCHKUNPK(SUnpkU32, &param->dnUsedUEAMBR, mBuf);
   CMCHKUNPK(SUnpkU32, &param->upUsedUEAMBR, mBuf);
   CMCHKUNPK(SUnpkU32, &param->dnSubsUEAMBR, mBuf);
   CMCHKUNPK(SUnpkU32, &param->upSubsUEAMBR, mBuf);

   for (cnt = 1; cnt >= 0; cnt--)
   {
      CMCHKUNPK(SUnpkU8, &param->drxParam[cnt], mBuf);
   } /* end of loop */

   CMCHKUNPK(SUnpkU8, &param->nmbTrip, mBuf);

   for (cnt = param->nmbTrip - 1; cnt >= 0; cnt--)
   {
      for(cnt1 = 7; cnt1 >= 0; cnt1 --)
      {
        CMCHKUNPK(SUnpkU8, &param->authTrip[cnt].kc[cnt1], mBuf);
      }
      for(cnt1 = 3; cnt1 >= 0; cnt1 --)
      {
        CMCHKUNPK(SUnpkU8, &param->authTrip[cnt].sres[cnt1], mBuf);
      }
      for(cnt1 = 15; cnt1 >= 0; cnt1 --)
      {
        CMCHKUNPK(SUnpkU8, &param->authTrip[cnt].rand[cnt1], mBuf);
      }
   } /* end of loop */

   for (cnt = 7; cnt >= 0; cnt--)
   {
      CMCHKUNPK(SUnpkU8, &param->kc[cnt], mBuf);
   } /* end of loop */

   CMCHKUNPK(SUnpkU8, &param->usedCipher, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isSAMBRIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isUAMBRIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->cksn, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isDRXIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->secMode, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkEgGsmKeyT */


/***********************************************************
*
*     Func : cmPkEgUMTSKeyUCQt
*
*     Desc : MM  Context UMTS Key Used Cipher Quintuplets
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgUMTSKeyUCQt
(
EgUMTSKeyUCQt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgUMTSKeyUCQt(param, mBuf)
EgUMTSKeyUCQt *param;
Buffer *mBuf;
#endif
{
   S16 cnt = 0;

   TRC3(cmPkEgUMTSKeyUCQt);

   CMCHKPK(SPkU8, param->secMode, mBuf);
   CMCHKPK(SPkU8, param->isDRXIPres, mBuf);
   CMCHKPK(SPkU8, param->cksn, mBuf);
   CMCHKPK(SPkU8, param->isUAMBRIPres, mBuf);
   CMCHKPK(SPkU8, param->isSAMBRIPres, mBuf);
   CMCHKPK(SPkU8, param->usedCipher, mBuf);
   CMCHKPK(cmPkEgDatStr16, &param->ck, mBuf);
   CMCHKPK(cmPkEgDatStr16, &param->ik, mBuf);

   for(cnt = 0 ;cnt < param->nmbQuin; cnt++)
   {
     cmPkEgAuthQt(&param->authQuin[cnt], mBuf);
   }

   CMCHKPK(SPkU8, param->nmbQuin, mBuf);

   for (cnt = 0; cnt < 2; cnt++)
   {
      CMCHKPK(SPkU8, param->drxParam[cnt], mBuf);
   } /* end of loop */

   CMCHKPK(SPkU32, param->upSubsUEAMBR, mBuf);
   CMCHKPK(SPkU32, param->dnSubsUEAMBR, mBuf);
   CMCHKPK(SPkU32, param->upUsedUEAMBR, mBuf);
   CMCHKPK(SPkU32, param->dnUsedUEAMBR, mBuf);

   CMCHKPK(cmPkEgDatStr16, &param->ueNtwrkCapb, mBuf);
   CMCHKPK(cmPkEgDatStr16, &param->msNtwrkCapb, mBuf);
   CMCHKPK(cmPkEgDatStr16, &param->meId, mBuf);

   CMCHKPK(SPkU8, param->isUNA, mBuf);
   CMCHKPK(SPkU8, param->isGENA, mBuf);
   CMCHKPK(SPkU8, param->isGANA, mBuf);
   CMCHKPK(SPkU8, param->isINA, mBuf);
   CMCHKPK(SPkU8, param->isENA, mBuf);
   CMCHKPK(SPkU8, param->isHNNA, mBuf);
#ifdef EG_REL_930
   CMCHKPK(SPkU8, param->vDomPrefUEUsageLen, mBuf);
   CMCHKPK(SPkU8, param->vDomPref, mBuf);
   CMCHKPK(SPkU8, param->ueUsageSett, mBuf);
#endif /* EG_REL_930 */
   RETVALUE(ROK);
} /* end of cmPkEgUMTSKeyUCQt */


/***********************************************************
*
*     Func : cmUnpkEgUMTSKeyUCQt
*
*     Desc : MM  Context GSM Key Triplet
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgUMTSKeyUCQt
(
EgUMTSKeyUCQt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgUMTSKeyUCQt(param, mBuf)
EgUMTSKeyUCQt *param;
Buffer *mBuf;
#endif
{
   /*egt_c_001.main_11 :Klocwork fix,modified S16 to U8*/
   S32 cnt = 0;

   TRC3(cmUnpkEgUMTSKeyUCQt);
#ifdef EG_REL_930
   CMCHKUNPK(SUnpkU8, &param->ueUsageSett, mBuf);
   CMCHKUNPK(SUnpkU8, &param->vDomPref, mBuf);
   CMCHKUNPK(SUnpkU8, &param->vDomPrefUEUsageLen, mBuf);
#endif /* EG_REL_930 */

   CMCHKUNPK(SUnpkU8, &param->isHNNA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isENA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isINA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isGANA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isGENA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isUNA, mBuf);

   CMCHKUNPK(cmUnpkEgDatStr16, &param->meId, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr16, &param->msNtwrkCapb, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr16, &param->ueNtwrkCapb, mBuf);

   CMCHKUNPK(SUnpkU32, &param->dnUsedUEAMBR, mBuf);
   CMCHKUNPK(SUnpkU32, &param->upUsedUEAMBR, mBuf);
   CMCHKUNPK(SUnpkU32, &param->dnSubsUEAMBR, mBuf);
   CMCHKUNPK(SUnpkU32, &param->upSubsUEAMBR, mBuf);

   for (cnt = 1; cnt >= 0; cnt--)
   {
      CMCHKUNPK(SUnpkU8, &param->drxParam[cnt], mBuf);
   } /* end of loop */

   CMCHKUNPK(SUnpkU8, &param->nmbQuin, mBuf);

   for( cnt = param->nmbQuin-1;cnt >= 0; cnt--)
   {
      cmUnpkEgAuthQt(&param->authQuin[cnt], mBuf);
   }

   CMCHKUNPK(cmUnpkEgDatStr16, &param->ik, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr16, &param->ck, mBuf);
   CMCHKUNPK(SUnpkU8, &param->usedCipher, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isSAMBRIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isUAMBRIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->cksn, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isDRXIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->secMode, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkEgUMTSKeyUCQt */


/***********************************************************
*
*     Func : cmPkEgGSMKeyUCQt
*
*     Desc : MM GSM Key Used Cipher Quintuplets
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgGSMKeyUCQt
(
EgGSMKeyUCQt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgGSMKeyUCQt(param, mBuf)
EgGSMKeyUCQt *param;
Buffer *mBuf;
#endif
{
   S16 cnt = 0;

   TRC3(cmPkEgGSMKeyUCQt);

   CMCHKPK(SPkU8, param->secMode, mBuf);
   CMCHKPK(SPkU8, param->isDRXIPres, mBuf);
   CMCHKPK(SPkU8, param->cksn, mBuf);
   CMCHKPK(SPkU8, param->isUAMBRIPres, mBuf);
   CMCHKPK(SPkU8, param->isSAMBRIPres, mBuf);
   CMCHKPK(SPkU8, param->usedCipher, mBuf);

   for (cnt = 0; cnt < 8; cnt++)
   {
      CMCHKPK(SPkU8, param->kc[cnt], mBuf);
   } /* end of loop */

   for(cnt = 0;cnt < param->nmbQuin; cnt++)
   {
     cmPkEgAuthQt(&param->authQuin[cnt], mBuf);
   }

   CMCHKPK(SPkU8, param->nmbQuin, mBuf);

   for (cnt = 0; cnt < 2; cnt++)
   {
      CMCHKPK(SPkU8, param->drxParam[cnt], mBuf);
   } /* end of loop */


   CMCHKPK(SPkU32, param->upSubsUEAMBR, mBuf);
   CMCHKPK(SPkU32, param->dnSubsUEAMBR, mBuf);
   CMCHKPK(SPkU32, param->upUsedUEAMBR, mBuf);
   CMCHKPK(SPkU32, param->dnUsedUEAMBR, mBuf);

   CMCHKPK(cmPkEgDatStr16, &param->ueNtwrkCapb, mBuf);
   CMCHKPK(cmPkEgDatStr16, &param->msNtwrkCapb, mBuf);
   CMCHKPK(cmPkEgDatStr16, &param->meId, mBuf);

   CMCHKPK(SPkU8, param->isUNA, mBuf);
   CMCHKPK(SPkU8, param->isGENA, mBuf);
   CMCHKPK(SPkU8, param->isGANA, mBuf);
   CMCHKPK(SPkU8, param->isINA, mBuf);
   CMCHKPK(SPkU8, param->isENA, mBuf);
   CMCHKPK(SPkU8, param->isHNNA, mBuf);
#ifdef EG_REL_930
   CMCHKPK(SPkU8, param->vDomPrefUEUsageLen, mBuf);
   CMCHKPK(SPkU8, param->vDomPref, mBuf);
   CMCHKPK(SPkU8, param->ueUsageSett, mBuf);
#endif /* EG_REL_930 */
   RETVALUE(ROK);
} /* end of cmPkEgGSMKeyUCQt */


/***********************************************************
*
*     Func : cmUnpkEgGSMKeyUCQt
*
*     Desc : MM GSM Key Used Cipher Quintuplets
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgGSMKeyUCQt
(
EgGSMKeyUCQt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgGSMKeyUCQt(param, mBuf)
EgGSMKeyUCQt *param;
Buffer *mBuf;
#endif
{
   /* egt_c_001.main_11 :Klocwork fix,modified S16 to U8*/
   S32 cnt = 0;

   TRC3(cmUnpkEgGSMKeyUCQt);
#ifdef EG_REL_930
   CMCHKUNPK(SUnpkU8, &param->ueUsageSett, mBuf);
   CMCHKUNPK(SUnpkU8, &param->vDomPref, mBuf);
   CMCHKUNPK(SUnpkU8, &param->vDomPrefUEUsageLen, mBuf);
#endif /* EG_REL_930 */

   CMCHKUNPK(SUnpkU8, &param->isHNNA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isENA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isINA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isGANA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isGENA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isUNA, mBuf);

   CMCHKUNPK(cmUnpkEgDatStr16, &param->meId, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr16, &param->msNtwrkCapb, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr16, &param->ueNtwrkCapb, mBuf);

   CMCHKUNPK(SUnpkU32, &param->dnUsedUEAMBR, mBuf);
   CMCHKUNPK(SUnpkU32, &param->upUsedUEAMBR, mBuf);
   CMCHKUNPK(SUnpkU32, &param->dnSubsUEAMBR, mBuf);
   CMCHKUNPK(SUnpkU32, &param->upSubsUEAMBR, mBuf);

   for (cnt = 1; cnt >= 0; cnt--)
   {
      CMCHKUNPK(SUnpkU8, &param->drxParam[cnt], mBuf);
   } /* end of loop */

   CMCHKUNPK(SUnpkU8, &param->nmbQuin, mBuf);
   for(cnt = param->nmbQuin-1; cnt >= 0; cnt--)
   {
     cmUnpkEgAuthQt(&param->authQuin[cnt], mBuf);
   }

   for (cnt = 7; cnt >= 0; cnt--)
   {
      CMCHKUNPK(SUnpkU8, &param->kc[cnt], mBuf);
   } /* end of loop */

   CMCHKUNPK(SUnpkU8, &param->usedCipher, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isSAMBRIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isUAMBRIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->cksn, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isDRXIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->secMode, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkEgGSMKeyUCQt */


/***********************************************************
*
*     Func : cmPkEgUMTSKeyQt
*
*     Desc : MM  Context UMTS Key Quintuplets
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgUMTSKeyQt
(
EgUMTSKeyQt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgUMTSKeyQt(param, mBuf)
EgUMTSKeyQt *param;
Buffer *mBuf;
#endif
{
   S16 cnt = 0;

   TRC3(cmPkEgUMTSKeyQt);

   CMCHKPK(SPkU8, param->secMode, mBuf);
   CMCHKPK(SPkU8, param->isDRXIPres, mBuf);
   CMCHKPK(SPkU8, param->ksi, mBuf);
   CMCHKPK(SPkU8, param->isUAMBRIPres, mBuf);
   CMCHKPK(SPkU8, param->isSAMBRIPres, mBuf);
   CMCHKPK(cmPkEgDatStr16, &param->ck, mBuf);
   CMCHKPK(cmPkEgDatStr16, &param->ik, mBuf);

   for(cnt = 0;cnt < param->nmbQuin; cnt++)
   {
     cmPkEgAuthQt(&param->authQuin[cnt], mBuf);
   }
   CMCHKPK(SPkU8, param->nmbQuin, mBuf);

   for (cnt = 0; cnt < 2; cnt++)
   {
      CMCHKPK(SPkU8, param->drxParam[cnt], mBuf);
   } /* end of loop */

   CMCHKPK(SPkU32, param->upSubsUEAMBR, mBuf);
   CMCHKPK(SPkU32, param->dnSubsUEAMBR, mBuf);
   CMCHKPK(SPkU32, param->upUsedUEAMBR, mBuf);
   CMCHKPK(SPkU32, param->dnUsedUEAMBR, mBuf);

   CMCHKPK(cmPkEgDatStr16, &param->ueNtwrkCapb, mBuf);
   CMCHKPK(cmPkEgDatStr16, &param->msNtwrkCapb, mBuf);
   CMCHKPK(cmPkEgDatStr16, &param->meId, mBuf);

   CMCHKPK(SPkU8, param->isUNA, mBuf);
   CMCHKPK(SPkU8, param->isGENA, mBuf);
   CMCHKPK(SPkU8, param->isGANA, mBuf);
   CMCHKPK(SPkU8, param->isINA, mBuf);
   CMCHKPK(SPkU8, param->isENA, mBuf);
   CMCHKPK(SPkU8, param->isHNNA, mBuf);
#ifdef EG_REL_930
   CMCHKPK(SPkU8, param->vDomPrefUEUsageLen, mBuf);
   CMCHKPK(SPkU8, param->vDomPref, mBuf);
   CMCHKPK(SPkU8, param->ueUsageSett, mBuf);
#endif /* EG_REL_930 */
   RETVALUE(ROK);
} /* end of cmPkEgUMTSKeyQt */


/***********************************************************
*
*     Func : cmUnpkEgUMTSKeyQt
*
*     Desc : MM  Context UMTS Key Quintuplets
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgUMTSKeyQt
(
EgUMTSKeyQt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgUMTSKeyQt(param, mBuf)
EgUMTSKeyQt *param;
Buffer *mBuf;
#endif
{
   /*egt_c_001.main_11 :Klocwork fix,modified S16 to U8*/
   S32 cnt = 0;

   TRC3(cmUnpkEgUMTSKeyQt);
#ifdef EG_REL_930
   CMCHKUNPK(SUnpkU8, &param->ueUsageSett, mBuf);
   CMCHKUNPK(SUnpkU8, &param->vDomPref, mBuf);
   CMCHKUNPK(SUnpkU8, &param->vDomPrefUEUsageLen, mBuf);
#endif /* EG_REL_930 */


   CMCHKUNPK(SUnpkU8, &param->isHNNA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isENA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isINA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isGANA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isGENA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isUNA, mBuf);

   CMCHKUNPK(cmUnpkEgDatStr16, &param->meId, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr16, &param->msNtwrkCapb, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr16, &param->ueNtwrkCapb, mBuf);

   CMCHKUNPK(SUnpkU32, &param->dnUsedUEAMBR, mBuf);
   CMCHKUNPK(SUnpkU32, &param->upUsedUEAMBR, mBuf);
   CMCHKUNPK(SUnpkU32, &param->dnSubsUEAMBR, mBuf);
   CMCHKUNPK(SUnpkU32, &param->upSubsUEAMBR, mBuf);

   for (cnt = 1; cnt >= 0; cnt--)
   {
      CMCHKUNPK(SUnpkU8, &param->drxParam[cnt], mBuf);
   } /* end of loop */

   CMCHKUNPK(SUnpkU8, &param->nmbQuin, mBuf);
   for (cnt = param->nmbQuin-1; cnt >= 0; cnt--)
   {
     cmUnpkEgAuthQt(&param->authQuin[cnt], mBuf);
   }

   CMCHKUNPK(cmUnpkEgDatStr16, &param->ik, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr16, &param->ck, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isSAMBRIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isUAMBRIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ksi, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isDRXIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->secMode, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkEgUMTSKeyQt */


/***********************************************************
*
*     Func : cmPkEgESecCxtQdQt
*
*     Desc : MM  Context EPS Security Context Quadruplets Quintuplets
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgESecCxtQdQt
(
EgESecCxtQdQt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgESecCxtQdQt(param, mBuf)
EgESecCxtQdQt *param;
Buffer *mBuf;
#endif
{
   S16 cnt = 0;

   TRC3(cmPkEgESecCxtQdQt);

   CMCHKPK(SPkU8, param->secMode, mBuf);
   CMCHKPK(SPkU8, param->isNHIPres, mBuf);
   CMCHKPK(SPkU8, param->isDRXIPres, mBuf);
   CMCHKPK(SPkU8, param->ksi, mBuf);
   CMCHKPK(SPkU8, param->isUAMBRIPres, mBuf);
   CMCHKPK(SPkU8, param->isOCSIPres, mBuf);
   CMCHKPK(SPkU8, param->isSAMBRIPres, mBuf);
   CMCHKPK(SPkU8, param->nasProtAlgo, mBuf);
   CMCHKPK(SPkU8, param->usedNasCipher, mBuf);
   CMCHKPK(SPkU32, param->nasDlCount, mBuf);
   CMCHKPK(SPkU32, param->nasUlCount, mBuf);
   CMCHKPK(cmPkEgDatStr32, &param->kasme, mBuf);

   for(cnt = 0; cnt < param->nmbQuadru; cnt++)
   {
     cmPkEgAuthQuadrup(&param->authQuadru[cnt], mBuf);
   }
   for(cnt = 0; cnt < param->nmbQuin; cnt++)
   {
     cmPkEgAuthQt(&param->authQuin[cnt], mBuf);
   }
   CMCHKPK(SPkU8, param->nmbQuadru, mBuf);
   CMCHKPK(SPkU8, param->nmbQuin, mBuf);

   for (cnt = 0; cnt < 2; cnt++)
   {
      CMCHKPK(SPkU8, param->drxParam[cnt], mBuf);
   } /* end of loop */

   for (cnt = 0; cnt < 32; cnt++)
   {
      CMCHKPK(SPkU8, param->nxtHop[cnt], mBuf);
   } /* end of loop */

   CMCHKPK(SPkU8, param->ncc, mBuf);
   CMCHKPK(SPkU32, param->upSubsUEAMBR, mBuf);
   CMCHKPK(SPkU32, param->dnSubsUEAMBR, mBuf);
   CMCHKPK(SPkU32, param->upUsedUEAMBR, mBuf);
   CMCHKPK(SPkU32, param->dnUsedUEAMBR, mBuf);

   CMCHKPK(cmPkEgDatStr16, &param->ueNtwrkCapb, mBuf);
   CMCHKPK(cmPkEgDatStr16, &param->msNtwrkCapb, mBuf);
   CMCHKPK(cmPkEgDatStr16, &param->meId, mBuf);

   CMCHKPK(SPkU8, param->isUNA, mBuf);
   CMCHKPK(SPkU8, param->isGENA, mBuf);
   CMCHKPK(SPkU8, param->isGANA, mBuf);
   CMCHKPK(SPkU8, param->isINA, mBuf);
   CMCHKPK(SPkU8, param->isENA, mBuf);
   CMCHKPK(SPkU8, param->isHNNA, mBuf);

   CMCHKPK(SPkU8, param->nccOld, mBuf);
   CMCHKPK(SPkU8, param->ksiOld, mBuf);
   CMCHKPK(SPkU8, param->isNHIOldPres, mBuf);
   CMCHKPK(cmPkEgDatStr32, &param->kasmeOld, mBuf);

   for (cnt = 0; cnt < 32; cnt++)
   {
      CMCHKPK(SPkU8, param->nxtHopOld[cnt], mBuf);
   } /* end of loop */
#ifdef EG_REL_930
   CMCHKPK(SPkU8, param->vDomPrefUEUsageLen, mBuf);
   CMCHKPK(SPkU8, param->vDomPref, mBuf);
   CMCHKPK(SPkU8, param->ueUsageSett, mBuf);
#endif /* EG_REL_930 */
   RETVALUE(ROK);
} /* end of cmPkEgESecCxtQdQt */


/***********************************************************
*
*     Func : cmUnpkEgESecCxtQdQt
*
*     Desc : MM  Context EPS Security Context Quadruplets Quintuplets
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgESecCxtQdQt
(
EgESecCxtQdQt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgESecCxtQdQt(param, mBuf)
EgESecCxtQdQt *param;
Buffer *mBuf;
#endif
{
   /*egt_c_001.main_11 :Klocwork fix,modified S16 to U8*/
   S32 cnt = 0;

   TRC3(cmUnpkEgESecCxtQdQt);
#ifdef EG_REL_930
   CMCHKUNPK(SUnpkU8, &param->ueUsageSett, mBuf);
   CMCHKUNPK(SUnpkU8, &param->vDomPref, mBuf);
   CMCHKUNPK(SUnpkU8, &param->vDomPrefUEUsageLen, mBuf);
#endif /* EG_REL_930 */


   for (cnt = 31; cnt >= 0; cnt--)
   {
      CMCHKUNPK(SUnpkU8, &param->nxtHopOld[cnt], mBuf);
   } /* end of loop */

   CMCHKUNPK(cmUnpkEgDatStr32, &param->kasmeOld, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isNHIOldPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ksiOld, mBuf);
   CMCHKUNPK(SUnpkU8, &param->nccOld, mBuf);

   CMCHKUNPK(SUnpkU8, &param->isHNNA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isENA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isINA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isGANA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isGENA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isUNA, mBuf);

   CMCHKUNPK(cmUnpkEgDatStr16, &param->meId, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr16, &param->msNtwrkCapb, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr16, &param->ueNtwrkCapb, mBuf);

   CMCHKUNPK(SUnpkU32, &param->dnUsedUEAMBR, mBuf);
   CMCHKUNPK(SUnpkU32, &param->upUsedUEAMBR, mBuf);
   CMCHKUNPK(SUnpkU32, &param->dnSubsUEAMBR, mBuf);
   CMCHKUNPK(SUnpkU32, &param->upSubsUEAMBR, mBuf);

   CMCHKUNPK(SUnpkU8, &param->ncc, mBuf);
   for (cnt = 31; cnt >= 0; cnt--)
   {
      CMCHKUNPK(SUnpkU8, &param->nxtHop[cnt], mBuf);
   } /* end of loop */

   for (cnt = 1; cnt >= 0; cnt--)
   {
      CMCHKUNPK(SUnpkU8, &param->drxParam[cnt], mBuf);
   } /* end of loop */

   CMCHKUNPK(SUnpkU8, &param->nmbQuin, mBuf);
   CMCHKUNPK(SUnpkU8, &param->nmbQuadru, mBuf);

   for(cnt = param->nmbQuin-1; cnt >= 0;cnt--)
   {
     cmUnpkEgAuthQt(&param->authQuin[cnt], mBuf);
   }
   for(cnt = param->nmbQuadru-1; cnt >= 0; cnt--)
   {
     cmUnpkEgAuthQuadrup(&param->authQuadru[cnt], mBuf);
   }

   CMCHKUNPK(cmUnpkEgDatStr32, &param->kasme, mBuf);
   CMCHKUNPK(SUnpkU32, &param->nasUlCount, mBuf);
   CMCHKUNPK(SUnpkU32, &param->nasDlCount, mBuf);
   CMCHKUNPK(SUnpkU8, &param->usedNasCipher, mBuf);
   CMCHKUNPK(SUnpkU8, &param->nasProtAlgo, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isSAMBRIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isOCSIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isUAMBRIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ksi, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isDRXIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isNHIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->secMode, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkEgESecCxtQdQt */


/***********************************************************
*
*     Func : cmPkEgUMTSKeyQdQt
*
*     Desc : MM Context UMTS Key Quadruplets Quintuplets
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgUMTSKeyQdQt
(
EgUMTSKeyQdQt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgUMTSKeyQdQt(param, mBuf)
EgUMTSKeyQdQt *param;
Buffer *mBuf;
#endif
{
   S16 cnt = 0;

   TRC3(cmPkEgUMTSKeyQdQt);

   CMCHKPK(SPkU8, param->secMode, mBuf);
   CMCHKPK(SPkU8, param->isDRXIPres, mBuf);
   CMCHKPK(SPkU8, param->ksi, mBuf);
   CMCHKPK(SPkU8, param->isUAMBRIPres, mBuf);
   CMCHKPK(SPkU8, param->isSAMBRIPres, mBuf);
   CMCHKPK(cmPkEgDatStr16, &param->ck, mBuf);
   CMCHKPK(cmPkEgDatStr16, &param->ik, mBuf);

   for(cnt = 0; cnt < param->nmbQuadru; cnt++)
   {
     cmPkEgAuthQuadrup(&param->authQuadru[cnt], mBuf);
   }
   for(cnt = 0; cnt < param->nmbQuin; cnt++)
   {
     cmPkEgAuthQt(&param->authQuin[cnt], mBuf);
   }
   CMCHKPK(SPkU8, param->nmbQuadru, mBuf);
   CMCHKPK(SPkU8, param->nmbQuin, mBuf);

   for (cnt = 0; cnt < 2; cnt++)
   {
      CMCHKPK(SPkU8, param->drxParam[cnt], mBuf);
   } /* end of loop */

   CMCHKPK(SPkU32, param->upSubsUEAMBR, mBuf);
   CMCHKPK(SPkU32, param->dnSubsUEAMBR, mBuf);
   CMCHKPK(SPkU32, param->upUsedUEAMBR, mBuf);
   CMCHKPK(SPkU32, param->dnUsedUEAMBR, mBuf);

   CMCHKPK(cmPkEgDatStr16, &param->ueNtwrkCapb, mBuf);
   CMCHKPK(cmPkEgDatStr16, &param->msNtwrkCapb, mBuf);
   CMCHKPK(cmPkEgDatStr16, &param->meId, mBuf);

   CMCHKPK(SPkU8, param->isUNA, mBuf);
   CMCHKPK(SPkU8, param->isGENA, mBuf);
   CMCHKPK(SPkU8, param->isGANA, mBuf);
   CMCHKPK(SPkU8, param->isINA, mBuf);
   CMCHKPK(SPkU8, param->isENA, mBuf);
   CMCHKPK(SPkU8, param->isHNNA, mBuf);
#ifdef EG_REL_930
   CMCHKPK(SPkU8, param->vDomPrefUEUsageLen, mBuf);
   CMCHKPK(SPkU8, param->vDomPref, mBuf);
   CMCHKPK(SPkU8, param->ueUsageSett, mBuf);
#endif /* EG_REL_930 */
   RETVALUE(ROK);
} /* end of cmPkEgUMTSKeyQdQt */


/***********************************************************
*
*     Func : cmUnpkEgUMTSKeyQdQt
*
*     Desc : MM  Context UMTS Key Quadruplets Quintuplets
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgUMTSKeyQdQt
(
EgUMTSKeyQdQt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgUMTSKeyQdQt(param, mBuf)
EgUMTSKeyQdQt *param;
Buffer *mBuf;
#endif
{
   /* egt_c_001.main_11 :Klocwork fix,modified S16 to U8*/
   S32 cnt = 0;

   TRC3(cmUnpkEgUMTSKeyQdQt);

#ifdef EG_REL_930
   CMCHKUNPK(SUnpkU8, &param->ueUsageSett, mBuf);
   CMCHKUNPK(SUnpkU8, &param->vDomPref, mBuf);
   CMCHKUNPK(SUnpkU8, &param->vDomPrefUEUsageLen, mBuf);
#endif /* EG_REL_930 */

   CMCHKUNPK(SUnpkU8, &param->isHNNA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isENA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isINA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isGANA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isGENA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isUNA, mBuf);

   CMCHKUNPK(cmUnpkEgDatStr16, &param->meId, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr16, &param->msNtwrkCapb, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr16, &param->ueNtwrkCapb, mBuf);

   CMCHKUNPK(SUnpkU32, &param->dnUsedUEAMBR, mBuf);
   CMCHKUNPK(SUnpkU32, &param->upUsedUEAMBR, mBuf);
   CMCHKUNPK(SUnpkU32, &param->dnSubsUEAMBR, mBuf);
   CMCHKUNPK(SUnpkU32, &param->upSubsUEAMBR, mBuf);

   for (cnt = 1; cnt >= 0; cnt--)
   {
      CMCHKUNPK(SUnpkU8, &param->drxParam[cnt], mBuf);
   } /* end of loop */

   CMCHKUNPK(SUnpkU8, &param->nmbQuin, mBuf);
   CMCHKUNPK(SUnpkU8, &param->nmbQuadru, mBuf);
   for(cnt = param->nmbQuin-1; cnt >= 0; cnt--)
   {
      cmUnpkEgAuthQt(&param->authQuin[cnt], mBuf);
   }
   for(cnt = param->nmbQuadru-1; cnt >= 0; cnt--)
   {
      cmUnpkEgAuthQuadrup(&param->authQuadru[cnt], mBuf);
   }

   CMCHKUNPK(cmUnpkEgDatStr16, &param->ik, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr16, &param->ck, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isSAMBRIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isUAMBRIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ksi, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isDRXIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->secMode, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkEgUMTSKeyQdQt */


/***********************************************************
*
*     Func : cmPkEgFCause
*
*     Desc : MM Context FCause
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgFCause
(
EgFCause *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgFCause(param, mBuf)
EgFCause *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkEgFCause);

   CMCHKPK(SPkU8,  param->causeType, mBuf);
   CMCHKPK(SPkU16, param->cause, mBuf);

   RETVALUE(ROK);
} /* end of cmPkEgFCause */


/***********************************************************
*
*     Func : cmUnpkEgFCause
*
*     Desc : MM  Context FCause
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgFCause
(
EgFCause *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgFCause(param, mBuf)
EgFCause *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkEgFCause);

   CMCHKUNPK(SUnpkU16,  &param->cause, mBuf);
   CMCHKUNPK(SUnpkU8,   &param->causeType, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkEgFCause */


/***********************************************************
*
*     Func : cmPkEgS103PDF
*
*     Desc : MM Context S103PDF
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgS103PDF
(
EgS103PDF *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgS103PDF(param, mBuf)
EgS103PDF *param;
Buffer *mBuf;
#endif
{
   U8 i;
   TRC3(cmPkEgS103PDF);


   CMCHKPK(SPkU8, param->hsgwAddrLen, mBuf);
   cmPkEgIpAddr(&param->hsgwAddr, mBuf);
   CMCHKPK(SPkU32, param->greKey, mBuf);
   for(i=0;i<param->ebiNumber && param->ebiNumber < EG_MAX_NMB_BEARER;i++)
   {
     CMCHKPK(SPkU8, param->ebi[i], mBuf);
   }
   CMCHKPK(SPkU8,  param->ebiNumber, mBuf);

   RETVALUE(ROK);
} /* end of cmPkEgS103PDF */


/***********************************************************
*
*     Func : cmUnpkEgS103PDF
*
*     Desc : MM  Context S103PDF
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgS103PDF
(
EgS103PDF *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgS103PDF(param, mBuf)
EgS103PDF *param;
Buffer *mBuf;
#endif
{
   /*egt_c_001.main_11 :Klocwork fix,modified to S32*/
   S32 i;
   TRC3(cmUnpkEgS103PDF);

   CMCHKUNPK(SUnpkU8,  &param->ebiNumber, mBuf);
   for(i=param->ebiNumber-1;i>=0 ;i--)
   {
     CMCHKUNPK(SUnpkU8, (param->ebi+i), mBuf);
   }
   CMCHKUNPK(SUnpkU32,  &param->greKey, mBuf);
   cmUnpkEgIpAddr(&param->hsgwAddr, mBuf);
   CMCHKUNPK(SUnpkU8, &param->hsgwAddrLen, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkEgS103PDF */


/***********************************************************
*
*     Func : cmPkEgS1UDF
*
*     Desc : MM Context S1UDF
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgS1UDF
(
EgS1UDF *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgS1UDF(param, mBuf)
EgS1UDF *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkEgS1UDF);

   CMCHKPK(SPkU8,          param->ebi, mBuf);
   cmPkEgIpAddr(&param->sgwAddr, mBuf);
   CMCHKPK(SPkU32,         param->sgwS1UTEID, mBuf);

   RETVALUE(ROK);
} /* end of cmPkEgS1UDF */


/***********************************************************
*
*     Func : cmUnpkEgS1UDF
*
*     Desc : MM  Context S1UDF
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgS1UDF
(
EgS1UDF *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgS1UDF(param, mBuf)
EgS1UDF *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkEgS1UDF);

   CMCHKUNPK(SUnpkU32,         &param->sgwS1UTEID, mBuf);
   cmUnpkEgIpAddr(&param->sgwAddr, mBuf);
   CMCHKUNPK(SUnpkU8,          &param->ebi, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkEgS1UDF */


/***********************************************************
*
*     Func : cmPkEgCrm
*
*
*     Desc : PDU Numbers
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgCrm
(
EgCrm  *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgCrm(param, mBuf)
EgCrm  *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkEgCrm);

   CMCHKPK(SPkU8,          param->crmType, mBuf);
   CMCHKPK(cmPkEgDatStr,   &param->crm, mBuf);

   RETVALUE(ROK);
} /* end of cmPkEgCrm */


/***********************************************************
*
*     Func : cmUnpkEgCrm
*
*
*     Desc : PDU Numbers
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgCrm
(
EgCrm  *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgCrm(param, mBuf)
EgCrm  *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkEgCrm);

   CMCHKUNPK(cmUnpkEgDatStr,   &param->crm, mBuf);
   CMCHKUNPK(SUnpkU8,          &param->crmType, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkEgCrm */


/***********************************************************
*
*     Func : cmPkEgGuti
*
*
*     Desc : PDU Numbers
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgGuti
(
EgGuti  *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgGuti(param, mBuf)
EgGuti  *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkEgGuti);

   CMCHKPK(cmPkEgSNetwork, &param->sNwk, mBuf);
   CMCHKPK(SPkU16,         param->mmeGrpId, mBuf);
   CMCHKPK(SPkU8,          param->mmeCode, mBuf);
   CMCHKPK(SPkU32,         param->mTmsi, mBuf);

   RETVALUE(ROK);
} /* end of cmPkEgGuti */


/***********************************************************
*
*     Func : cmUnpkEgGuti
*
*
*     Desc : PDU Numbers
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgGuti
(
EgGuti  *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgGuti(param, mBuf)
EgGuti  *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkEgGuti);

   CMCHKUNPK(SUnpkU32,         &param->mTmsi, mBuf);
   CMCHKUNPK(SUnpkU8,          &param->mmeCode, mBuf);
   CMCHKUNPK(SUnpkU16,         &param->mmeGrpId, mBuf);
   CMCHKUNPK(cmUnpkEgSNetwork, &param->sNwk, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkEgGuti */


/***********************************************************
*
*     Func : cmPkEgFContainer
*
*
*     Desc : Fully Qualified Container (F-Container)
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgFContainer
(
EgFContainer *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgFContainer(param, mBuf)
EgFContainer *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkEgFContainer);

   CMCHKPK(cmPkEgDatStr32, &param->fContainer, mBuf);
   CMCHKPK(SPkU8, param->containerType, mBuf);
   RETVALUE(ROK);
} /* end of cmPkEgFContainer */


/***********************************************************
*
*     Func : cmUnpkEgFContainer
*
*
*     Desc : Fully Qualified Container (F-Container)
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgFContainer
(
EgFContainer *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgFContainer(param, mBuf)
EgFContainer *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkEgFContainer);

   CMCHKUNPK(SUnpkU8, &param->containerType, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr32, &param->fContainer, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkEgFContainer */



/***********************************************************
*
*     Func : cmPkEgTargetId
*
*
*     Desc : Target Identification
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgTargetId
(
EgTargetId *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgTargetId(param, mBuf)
EgTargetId *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkEgTargetId);

   CMCHKPK(cmPkEgDatStr8, &param->targetId, mBuf);
   CMCHKPK(SPkU8, param->targetType, mBuf);
   RETVALUE(ROK);
} /* end of cmPkEgTargetId */



/***********************************************************
*
*     Func : cmUnpkEgTargetId
*
*
*     Desc : Target Identification
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgTargetId
(
EgTargetId *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgTargetId(param, mBuf)
EgTargetId *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkEgTargetId);

   CMCHKUNPK(SUnpkU8, &param->targetType, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr8, &param->targetId, mBuf);
   RETVALUE(ROK);
} /* end of cmUnpkEgTargetId */


/***********************************************************
*
*     Func : cmPkEgPktFlowId
*
*
*     Desc : Packet Flow ID
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgPktFlowId
(
EgPktFlowId *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgPktFlowId(param, mBuf)
EgPktFlowId *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkEgPktFlowId);

   CMCHKPK(SPkU8, param->pktFlowId, mBuf);
   CMCHKPK(SPkU8, param->ebi, mBuf);
   RETVALUE(ROK);
} /* end of cmPkEgPktFlowId */



/***********************************************************
*
*     Func : cmUnpkEgPktFlowId
*
*
*     Desc : Packet Flow ID
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgPktFlowId
(
EgPktFlowId *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgPktFlowId(param, mBuf)
EgPktFlowId *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkEgPktFlowId);

   CMCHKUNPK(SUnpkU8, &param->ebi, mBuf);
   CMCHKUNPK(SUnpkU8, &param->pktFlowId, mBuf);
   RETVALUE(ROK);
} /* end of cmUnpkEgPktFlowId */

/***********************************************************
*
*     Func : cmPkEgRABCntxt
*
*
*     Desc : RAB Context
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgRABCntxt
(
EgRABCntxt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgRABCntxt(param, mBuf)
EgRABCntxt *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkEgRABCntxt);

   CMCHKPK(SPkU8, param->nsapi, mBuf);
   CMCHKPK(SPkU16, param->dnlEgUSeqNo, mBuf);
   CMCHKPK(SPkU16, param->uplEgUSeqNo, mBuf);
   CMCHKPK(SPkU16, param->dnlPdcpSeqNo, mBuf);
   CMCHKPK(SPkU16, param->uplPdcpSeqNo, mBuf);
   RETVALUE(ROK);
} /* end of cmPkEgRABCntxt */



/***********************************************************
*
*     Func : cmUnpkEgRABCntxt
*
*
*     Desc : RAB Context
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgRABCntxt
(
EgRABCntxt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgRABCntxt(param, mBuf)
EgRABCntxt *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkEgRABCntxt);

   CMCHKUNPK(SUnpkU16, &param->uplPdcpSeqNo, mBuf);
   CMCHKUNPK(SUnpkU16, &param->dnlPdcpSeqNo, mBuf);
   CMCHKUNPK(SUnpkU16, &param->uplEgUSeqNo, mBuf);
   CMCHKUNPK(SUnpkU16, &param->dnlEgUSeqNo, mBuf);
   CMCHKUNPK(SUnpkU8, &param->nsapi, mBuf);
   RETVALUE(ROK);
} /* end of cmUnpkEgRABCntxt */


/***********************************************************
*
*     Func : cmPkEgSrcId
*
*
*     Desc : Cell Identification
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgSrcId
(
EgSrcId *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgSrcId(param, mBuf)
EgSrcId *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkEgSrcId);

   CMCHKPK(cmPkEgDatStr16, &param->sourceId, mBuf);
   CMCHKPK(SPkU8, param->sourceType, mBuf);
   CMCHKPK(cmPkEgDatStr8, &param->targetCellId, mBuf);
   RETVALUE(ROK);
} /* end of cmPkEgSrcId */



/***********************************************************
*
*     Func : cmUnpkEgSrcId
*
*
*     Desc : Cell Identification
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgSrcId
(
EgSrcId *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgSrcId(param, mBuf)
EgSrcId *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkEgSrcId);

   CMCHKUNPK(cmUnpkEgDatStr8, &param->targetCellId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->sourceType, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr16, &param->sourceId, mBuf);
   RETVALUE(ROK);
} /* end of cmUnpkEgSrcId */



/***********************************************************
*
*     Func : cmPkEgTrcInfo
*
*
*     Desc : Trace Information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgTrcInfo
(
EgTrcInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgTrcInfo(param, mBuf)
EgTrcInfo *param;
Buffer *mBuf;
#endif
{
   U8 cnt;

   TRC3(cmPkEgTrcInfo);

   cmPkEgIpAddr(&param->trcColEntAddr, mBuf);
/* egt_c_001.main_11 - Added for S2B and S2B */   
#if defined(EG_S2B_SUPP) || defined(EG_S2A_SUPP)
   for (cnt=0;cnt < EGT_MAX_INTF;cnt++)
   {
      CMCHKPK(SPkU8, param->lstOfIntfs[cnt], mBuf);
   }
#else
   CMCHKPK(SPkU16, param->lstOfIntfs, mBuf);
#endif
   CMCHKPK(SPkU8, param->sesnTrcDep, mBuf);
   CMCHKPK(SPkU16, param->lstNETypes, mBuf);
   for (cnt = 0; cnt < 9; cnt++)
   {
     CMCHKPK(SPkU8, param->trigEvnts[cnt], mBuf);
   }
   CMCHKPK(SPkU32, param->trcId, mBuf);
   CMCHKPK(cmPkEgSNetwork, &param->sNwk, mBuf);
   RETVALUE(ROK);
} /* end of cmPkEgTrcInfo */



/***********************************************************
*
*     Func : cmUnpkEgTrcInfo
*
*
*     Desc : Trace Information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgTrcInfo
(
EgTrcInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgTrcInfo(param, mBuf)
EgTrcInfo *param;
Buffer *mBuf;
#endif
{
   S8 cnt;

   TRC3(cmUnpkEgTrcInfo);

   CMCHKUNPK(cmUnpkEgSNetwork, &param->sNwk, mBuf);
   CMCHKUNPK(SUnpkU32, &param->trcId, mBuf);
   for (cnt = 8; cnt >= 0; cnt--)
   {
     CMCHKUNPK(SUnpkU8, (param->trigEvnts+cnt), mBuf);
   }
   CMCHKUNPK(SUnpkU16, &param->lstNETypes, mBuf);
   CMCHKUNPK(SUnpkU8, &param->sesnTrcDep, mBuf);
/* egt_c_001.main_11 - Added for S2B and S2B */   
#if defined(EG_S2B_SUPP) || defined(EG_S2A_SUPP)
   for (cnt = EGT_MAX_INTF; cnt > 0; cnt--)
   {
     CMCHKUNPK(SUnpkU8, (param->lstOfIntfs+cnt), mBuf);
   }
#else
   CMCHKUNPK(SUnpkU16, &param->lstOfIntfs, mBuf);
#endif
   cmUnpkEgIpAddr(&param->trcColEntAddr, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkEgTrcInfo */



/***********************************************************
*
*     Func : cmPkEgBearFlags
*
*
*     Desc : Bearer Flags
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgBearFlags
(
EgBearFlags *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgBearFlags(param, mBuf)
EgBearFlags *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkEgBearFlags);

   CMCHKPK(SPkU8, param->isVBPres, mBuf);
   CMCHKPK(SPkU8, param->isPPCPres, mBuf);

   RETVALUE(ROK);
} /* end of cmPkEgBearFlags */



/***********************************************************
*
*     Func : cmUnpkEgBearFlags
*
*
*     Desc : Bearer Flags
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgBearFlags
(
EgBearFlags *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgBearFlags(param, mBuf)
EgBearFlags *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkEgBearFlags);

   CMCHKUNPK(SUnpkU8, &param->isPPCPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isVBPres, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkEgBearFlags */
#ifdef EG_REL_930
/***********************************************************
*
*     Func : cmPkEgMBMSIPMCastDist
*
*
*     Desc : Pack MBMS IP Mulitcast Distribution
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgMBMSIPMCastDist
(
EgMBMSIPMCastDist *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgMBMSIPMCastDist(param, mBuf)
EgMBMSIPMCastDist *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkEgMBMSIPMCastDist);

   CMCHKPK(SPkU32, param->cteidDat, mBuf); /**< Common Tunnel Endpoint Identifier Data */
   cmPkEgIpAddr(&param->ipMCastDistAddr, mBuf);
   cmPkEgIpAddr(&param->ipMCastSrcAddr, mBuf);
   CMCHKPK(SPkU8, param->mbmsHCInd, mBuf);

   RETVALUE(ROK);
} /* end of cmPkEgMBMSIPMCastDist */

/***********************************************************
*
*     Func : cmUnpkEgMBMSIPMCastDist
*
*
*     Desc : Unpack MBMS IP Mulitcast Distribution
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgMBMSIPMCastDist
(
EgMBMSIPMCastDist *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgMBMSIPMCastDist(param, mBuf)
EgMBMSIPMCastDist *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkEgMBMSIPMCastDist);

   CMCHKUNPK(SUnpkU8, &param->mbmsHCInd, mBuf);
   cmUnpkEgIpAddr(&param->ipMCastSrcAddr, mBuf);
   cmUnpkEgIpAddr(&param->ipMCastDistAddr, mBuf);
   CMCHKUNPK(SUnpkU32, &param->cteidDat, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkEgMBMSIPMCastDist*/

/***********************************************************
*
*     Func : cmPkEgUCI
*
*
*     Desc : Pack  User CSG Information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgUCI
(
EgUCI *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgUCI(param, mBuf)
EgUCI *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkEgUCI);

   cmPkEgSNetwork(&param->sNwk, mBuf);     /**< Serving Network */
   CMCHKPK(SPkU32, param->csgId, mBuf); 
   CMCHKPK(SPkU8, param->accMode, mBuf);
   CMCHKPK(SPkU8, param->isLCSGPres, mBuf);
   CMCHKPK(SPkU8, param->isCMIPres, mBuf);

   RETVALUE(ROK);
} /* end of cmPkEgUCI*/

/***********************************************************
*
*     Func : cmUnpkEgUCI
*
*
*     Desc : Unpack User CSG Information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgUCI
(
EgUCI *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgUCI(param, mBuf)
EgUCI *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkEgUCI);

   CMCHKUNPK(SUnpkU8, &param->isCMIPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isLCSGPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->accMode, mBuf);
   CMCHKUNPK(SUnpkU32, &param->csgId, mBuf); 
   cmUnpkEgSNetwork(&param->sNwk, mBuf);     /**< Serving Network */

   RETVALUE(ROK);
} /* end of cmUnpkEgUCI */

/***********************************************************
*
*     Func : cmPkEgCSGInfoRepAct
*
*
*     Desc : Pack  CSG Information Reporting Action
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgCSGInfoRepAct
(
EgCSGInfoRepAct *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgCSGInfoRepAct(param, mBuf)
EgCSGInfoRepAct *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkEgCSGInfoRepAct);

   CMCHKPK(SPkU8, param->isUCICSGPres, mBuf);
   CMCHKPK(SPkU8, param->isUCISHCPres, mBuf);
   CMCHKPK(SPkU8, param->isUCIUHCPres, mBuf);

   RETVALUE(ROK);
} /* end of cmPkEgCSGInfoRepAct */

/***********************************************************
*
*     Func : cmUnpkEgCSGInfoRepAct
*
*
*     Desc : Unpack User CSG Information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgCSGInfoRepAct
(
EgCSGInfoRepAct *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgCSGInfoRepAct(param, mBuf)
EgCSGInfoRepAct *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkEgCSGInfoRepAct);

   CMCHKUNPK(SUnpkU8, &param->isUCIUHCPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isUCISHCPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isUCICSGPres, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkEgCSGInfoRepAct */

#endif /* EG_REL_930 */





/*
*
*    Fun:     cmPkEgIeList
*
*    Desc:    pack the IE list into buffer
*
*    Ret:     ROK  -ok
*             Return value of sub methods
*
*    Notes:   The packing of the IE list will be done as shown
*             the following manner.
*
* ----------------------------------------------------------------
* |   1   |   2   |   3   |   4   |  5    |  6    |   7   |   8  |
* ----------------------------------------------------------------
*             |                               |
*            -------------------------------- |
*             |   2.1   |   2.2   |   2.3   | |
*            -------------------------------- |
*                                           --------------------------------
*                                            |   6.1   |   6.2   |   6.3   |
*                                           --------------------------------
*                                                           |
*                                                      --------------------------
*                                                       |   6.2.1   |   6.2.2   |
*                                                      --------------------------
*
*             As shown in the above example, the main IE list (level zero) is having
*             2, 6 are grouped IEs and at level one 6.2 is again a grouped IE
*             which is having two elements 6.2.1 and 6.2.2
*             The packing of the IE list will start from the last of the list
*             at any level.  If any of the node is a grouped IE, then the child
*             list will be packed first after which the grouped IE will be packed.
*
*             NOTE: The value in () is the count of the IE list
*
*             Step 1:  IE 8 is not grouped so pack into buffer.
*             ---------
*             |   8   |
*             ---------
*
*             Step 2:  IE 7 is not grouped so pack into buffer.
*             ------------------
*             |   8   |    7   |
*             ------------------
*
*             Step 3:  IE 6 is grouped so pack the child IE list first
*
*                 Step 3.1:  IE 6.3 is not a grouped IE so pack into buffer
*             -----------------------------
*             |   8   |    7   |    6.3   |
*             -----------------------------
*
*                 Step 3.2:  IE 6.2 is again a grouped IE so pack the child
*                            IE list
*
*                     Step 3.2.1:  IE 6.2.2 is not a grouped IE so pack into buffer
*             ------------------------------------------
*             |   8   |    7   |    6.3   |    6.2.2   |
*             ------------------------------------------
*
*                     Step 3.2.2:  IE 6.2.1 is not a grouped IE so pack into buffer
*             -------------------------------------------------------
*             |   8   |    7   |    6.3   |    6.2.2   |    6.2.1   |
*             -------------------------------------------------------
*
*                 Step 3.3:  Since IE 6.2 is a grouped IE so pack into buffer
*             -----------------------------------------------------------------------------
*             |   8   |    7   |    6.3   |    6.2.2   |    6.2.1   |    (2)   |    6.2   |
*             -----------------------------------------------------------------------------
*
*                 Step 3.4:  IE 6.1 is not a grouped IE so pack into buffer
*             -----------------------------------------------------------------------------
*             |   8   |    7   |    6.3   |    6.2.2   |    6.2.1   |    (2)   |    6.2   |
*             -----------------------------------------------------------------------------
*             |   6.1   |
*             -----------
*
*             Step 5:  Since IE 6 is a grouped IE pack into buffer.
*             -----------------------------------------------------------------------------
*             |   8   |    7   |    6.3   |    6.2.2   |    6.2.1   |    (2)   |    6.2   |
*             -----------------------------------------------------------------------------
*             |   6.1   |   (3)   |   6   |
*             -----------------------------
*
*             Step 5:  IE 5 is not grouped so pack into buffer.
*             -----------------------------------------------------------------------------
*             |   8   |    7   |    6.3   |    6.2.2   |    6.2.1   |    (2)   |    6.2   |
*             -----------------------------------------------------------------------------
*             |   6.1   |   (3)   |   6   |   5   |
*             -------------------------------------
*
*             Step 6:  IE 4 is not grouped so pack into buffer.
*             -----------------------------------------------------------------------------
*             |   8   |    7   |    6.3   |    6.2.2   |    6.2.1   |    (2)   |    6.2   |
*             -----------------------------------------------------------------------------
*             |   6.1   |   (3)   |   6   |   5   |   4   |
*             ---------------------------------------------
*
*             Step 6:  IE 3 is not grouped so pack into buffer.
*             -----------------------------------------------------------------------------
*             |   8   |    7   |    6.3   |    6.2.2   |    6.2.1   |    (2)   |    6.2   |
*             -----------------------------------------------------------------------------
*             |   6.1   |   (3)   |   6   |   5   |   4   |   3   |
*             -----------------------------------------------------
*
*             Step 7:  IE 2 is again a grouped IE so pack the
*                      child IE list
*
*                 Step 7.1:  IE 2.3 is not a grouped IE so pack into buffer
*             -----------------------------------------------------------------------------
*             |   8   |    7   |    6.3   |    6.2.2   |    6.2.1   |    (2)   |    6.2   |
*             -----------------------------------------------------------------------------
*             |   6.1   |   (3)   |   6   |   5   |   4   |   3   |    2.3   |
*             ----------------------------------------------------------------
*
*                 Step 7.2:  IE 2.2 is not a grouped IE so pack into buffer
*             -----------------------------------------------------------------------------
*             |   8   |    7   |    6.3   |    6.2.2   |    6.2.1   |    (2)   |    6.2   |
*             -----------------------------------------------------------------------------
*             |   6.1   |   (3)   |   6   |   5   |   4   |   3   |    2.3   |    2.2   |
*             ---------------------------------------------------------------------------
*
*                 Step 7.3:  IE 2.1 is not a grouped IE so pack into buffer
*             -----------------------------------------------------------------------------
*             |   8   |    7   |    6.3   |    6.2.2   |    6.2.1   |    (2)   |    6.2   |
*             -----------------------------------------------------------------------------
*             |   6.1   |   (3)   |   6   |   5   |   4   |   3   |    2.3   |    2.2   |
*             ---------------------------------------------------------------------------
*             |    2.1   |
*             ------------
*
*             Step 9:  Since IE 2 is a grouped IE pack into buffer.
*             -----------------------------------------------------------------------------
*             |   8   |    7   |    6.3   |    6.2.2   |    6.2.1   |    (2)   |    6.2   |
*             -----------------------------------------------------------------------------
*             |   6.1   |   (3)   |   6   |   5   |   4   |   3   |    2.3   |    2.2   |
*             ---------------------------------------------------------------------------
*             |    2.1   |   (3)   |   2   |
*             ------------------------------
*
*             Step 10:  IE 1 is not a grouped IE pack into buffer.
*             -----------------------------------------------------------------------------
*             |   8   |    7   |    6.3   |    6.2.2   |    6.2.1   |    (2)   |    6.2   |
*             -----------------------------------------------------------------------------
*             |   6.1   |   (3)   |   6   |   5   |   4   |   3   |    2.3   |    2.2   |
*             ---------------------------------------------------------------------------
*             |    2.1   |   (3)   |   2   |   1   |   (8)   |
*             ------------------------------------------------
*
*    File:    egt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkEgIeList
(
CmLListCp   *param,  /* the ie list to be packed */
Buffer      *mBuf        /* to hold the packed buffer */
)
#else
PUBLIC S16 cmPkEgIeList(param, mBuf)
CmLListCp   *param;  /* the ie list to be packed */
Buffer      *mBuf;       /* to hold the packed buffer */
#endif
{
   /* this is used to hold the temporary node address */
   CmLList *node = NULLP;

   /* this is used to hold the temporary IE */
   EgIe *egIe = NULLP;

   /* in a loop pack the IEs from last to the first.
    * This is because to preserve the position of IEs
    * in the packed buffer.  So while unpacking the
    * first IE in the list will be unpacked first.
    */
   for (egIe = (EgIe* ) CM_LLIST_LAST_NODE(param, node);
        egIe != NULLP;
        egIe = (EgIe* ) CM_LLIST_PREV_NODE(param, node))
   {
      /* if the IE type is grouped, then call the same API
       * recursively so that the list inside the grouped IE
       * will be packed first to preserve the grouped IE
       * information in the packed buffer.
       */
      if (egIe->dataType == EG_GROUPED)
      {
         if (cmPkEgIeList(&egIe->t.grouped.gIeList, mBuf) != ROK) 
            RETVALUE(RFAILED);
      } /* end of if the IE type is grouped */

      /* pack the IE (if grouped, after packing the child IEs) */
      CMCHKPK(cmPkEgIe, egIe, mBuf);
   } /* end of loop to pack all the IEs */

   /* pack the number of IEs in the list at last so that
    * the count will be un packed at first while unpacking
    * and the buffer will be unpacked based on the count
    * only.
    */
   CMCHKPK(SPkU32, param->count, mBuf);

   /* return success */
   RETVALUE(ROK);
} /*end of cmPkEgIeList */



/*
*
*    Fun:     cmUnpkEgIeList
*
*    Desc:    Unpack the IE list from buffer
*
*    Ret:     ROK  -ok
*             Return value of sub methods
*
*    Notes:   The unpacking of the IE list will be done as shown
*             the following manner.  If the packed buffer seems to
*             be as shown, then unpacking will be done as specified
*             in the below steps:
*
*             -----------------------------------------------------------------------------
*             |   8   |    7   |    6.3   |    6.2.2   |    6.2.1   |    (2)   |    6.2   |
*             -----------------------------------------------------------------------------
*             |   6.1   |   (3)   |   6   |   5   |   4   |   3   |    2.3   |    2.2   |
*             ---------------------------------------------------------------------------
*             |    2.1   |   (3)   |   2   |   1   |   (8)   |
*             ------------------------------------------------
*
*             Step 1:  Unpack the count of IEs in the IE list.
*                      In a loop unpack 8 IEs.
*
*                 Step 1.1:  Unpack IE 1, since it is not a grouped IE,
*                            append into IE list at level zero
* ---------
* |   1   |
* ---------
*
*                 Step 1.2:  Unpack IE 2, since it is a grouped IE, unpack
*                            the 3 child IEs from the buffer.
* -----------------
* |   1   |   2   |
* -----------------
*
*                     Step 1.2.1:  Unpack IE 2.1, since it is not a grouped IE
*                                  append to the list at level one
* -----------------
* |   1   |   2   |
* -----------------
*             |
*            ------------
*             |   2.1   |
*            ------------
*
*                     Step 1.2.2:  Unpack IE 2.2, since it is not a grouped IE
*                                  append to the list at level one
* -----------------
* |   1   |   2   |
* -----------------
*             |
*            ----------------------
*             |   2.1   |   2.2   |
*            ----------------------
*
*                     Step 1.2.3:  Unpack IE 2.3, since it is not a grouped IE
*                                  append to the list at level one
* -----------------
* |   1   |   2   |
* -----------------
*             |
*            --------------------------------
*             |   2.1   |   2.2   |   2.3   |
*            --------------------------------
*
*                 Step 1.3:  Unpack IE 3, since it is not a grouped IE
*                            append to the list at level zero
* -------------------------
* |   1   |   2   |   3   |
* -------------------------
*             |
*            --------------------------------
*             |   2.1   |   2.2   |   2.3   |
*            --------------------------------
*
*                 Step 1.4:  Unpack IE 4, since it is not a grouped IE
*                            append to the list at level zero
* ---------------------------------
* |   1   |   2   |   3   |   4   |
* ---------------------------------
*             |
*            --------------------------------
*             |   2.1   |   2.2   |   2.3   |
*            --------------------------------
*
*                 Step 1.5:  Unpack IE 5, since it is not a grouped IE
*                            append to the list at level zero
* -----------------------------------------
* |   1   |   2   |   3   |   4   |   5   |
* -----------------------------------------
*             |
*            --------------------------------
*             |   2.1   |   2.2   |   2.3   |
*            --------------------------------
*
*                 Step 1.6:  Unpack IE 6, and since it is a grouped IE
*                            unpack the remaining 3 child IEs from buffer
* -------------------------------------------------
* |   1   |   2   |   3   |   4   |  5    |  6    |
* -------------------------------------------------
*             |
*            --------------------------------
*             |   2.1   |   2.2   |   2.3   |
*            --------------------------------
*
*                     Step 1.6.1:  Unpack IE 6.1, since it is not a grouped IE
*                                  append to the list at level one
* -------------------------------------------------
* |   1   |   2   |   3   |   4   |  5    |  6    |
* -------------------------------------------------
*             |                               |
*            -------------------------------- |
*             |   2.1   |   2.2   |   2.3   | |
*            -------------------------------- |
*                                           ------------
*                                            |   6.1   |
*                                           ------------
*
*                     Step 1.6.2:  Unpack IE 6.2, since it is a grouped IE
*                                  unpack the 2 child IEs from buffer
* -------------------------------------------------
* |   1   |   2   |   3   |   4   |  5    |  6    |
* -------------------------------------------------
*             |                               |
*            -------------------------------- |
*             |   2.1   |   2.2   |   2.3   | |
*            -------------------------------- |
*                                           ----------------------
*                                            |   6.1   |   6.2   |
*                                           ----------------------
*
*                         Step 1.6.2.1:  Unpack IE 6.2.1, since it is not a grouped IE
*                                        append to IE list at level 2.
* -------------------------------------------------
* |   1   |   2   |   3   |   4   |  5    |  6    |
* -------------------------------------------------
*             |                               |
*            -------------------------------- |
*             |   2.1   |   2.2   |   2.3   | |
*            -------------------------------- |
*                                           ----------------------
*                                            |   6.1   |   6.2   |
*                                           ----------------------
*                                                           |
*                                                      --------------
*                                                       |   6.2.1   |
*                                                      --------------
*
*                         Step 1.6.2.2:  Unpack IE 6.2.2, since it is not a grouped IE
*                                        append to IE list at level 2.
* -------------------------------------------------
* |   1   |   2   |   3   |   4   |  5    |  6    |
* -------------------------------------------------
*             |                               |
*            -------------------------------- |
*             |   2.1   |   2.2   |   2.3   | |
*            -------------------------------- |
*                                           ----------------------
*                                            |   6.1   |   6.2   |
*                                           ----------------------
*                                                           |
*                                                      --------------------------
*                                                       |   6.2.1   |   6.2.1   |
*                                                      --------------------------
*
*                     Step 1.6.3:  Unpack IE 6.3, since it is not a grouped IE
*                                  append to IE list at level 1
* -------------------------------------------------
* |   1   |   2   |   3   |   4   |  5    |  6    |
* -------------------------------------------------
*             |                               |
*            -------------------------------- |
*             |   2.1   |   2.2   |   2.3   | |
*            -------------------------------- |
*                                           --------------------------------
*                                            |   6.1   |   6.2   |   6.3   |
*                                           --------------------------------
*                                                           |
*                                                      --------------------------
*                                                       |   6.2.1   |   6.2.2   |
*                                                      --------------------------
*
*                 Step 1.7:  Unpack IE 7, and since it is not a grouped IE
*                            append to IE list at level 0.
* ---------------------------------------------------------
* |   1   |   2   |   3   |   4   |  5    |  6    |   7   |
* ---------------------------------------------------------
*             |                               |
*            -------------------------------- |
*             |   2.1   |   2.2   |   2.3   | |
*            -------------------------------- |
*                                           --------------------------------
*                                            |   6.1   |   6.2   |   6.3   |
*                                           --------------------------------
*                                                           |
*                                                      --------------------------
*                                                       |   6.2.1   |   6.2.2   |
*                                                      --------------------------
*
*                 Step 1.8:  Unpack IE 8, and since it is not a grouped IE
*                            append to IE list at level 0.
* ----------------------------------------------------------------
* |   1   |   2   |   3   |   4   |  5    |  6    |   7   |   8  |
* ----------------------------------------------------------------
*             |                               |
*            -------------------------------- |
*             |   2.1   |   2.2   |   2.3   | |
*            -------------------------------- |
*                                           --------------------------------
*                                            |   6.1   |   6.2   |   6.3   |
*                                           --------------------------------
*                                                           |
*                                                      --------------------------
*                                                       |   6.2.1   |   6.2.2   |
*                                                      --------------------------
*
*    File:    egt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkEgIeList
(
CmLListCp   *param,  /* to hold the unpacked ie list */
Buffer      *mBuf,       /* the packed buffer */
CmMemListCp *memCp       /* the memory list cp to allocate memory for IEs */
)
#else
PUBLIC S16 cmUnpkEgIeList(param, mBuf, memCp)
CmLListCp   *param;  /* to hold the unpacked ie list */
Buffer      *mBuf;       /* the packed buffer */
CmMemListCp *memCp;      /* the memory list cp to allocate memory for IEs */
#endif
{
   /* this is used to hold the temporary IE */
   EgIe *egIe = NULLP;

   /* this is used to hold the temporary count of the IE list */
   U32 listCount = 0;

   TRC3(cmUnpkEgIeList)

   /* pack the number of IEs in the list at last so that
    * the count will be un packed at first while unpacking
    * and the buffer will be unpacked based on the count
    * only.
    */
   CMCHKUNPK(SUnpkU32, &listCount, mBuf);

   /* in a loop unpack the number of IEs from the buffer */
   for (; listCount > 0; listCount--)
   {
      /* allocate memory for the IE structure from
       * the global control block
       */
      if (cmGetMem(memCp, sizeof(EgIe), (Ptr* )&egIe) != ROK)
      {
         RETVALUE(EGT_ERR_MEM_ALLOC_FAILED);
      } /* end of if allocating memory for the ie fails */

      /* initialize the node address of the new IE */
      egIe->node.node = (PTR) egIe;

      /* unpack the IE from buffer */
      if (cmUnpkEgIe(egIe, mBuf) != ROK) 
         RETVALUE(RFAILED);

      /* append the IE to the tail of the list */
      cmLListAdd2Tail(param, &egIe->node);

      /* if the IE type is grouped, then call the same API
       * recursively so that the list inside the grouped IE
       * also will be unpacked
       */
      if (egIe->dataType == EG_GROUPED)
      {
         if (cmUnpkEgIeList(&egIe->t.grouped.gIeList, mBuf, memCp) != ROK) 
         {
            RETVALUE(RFAILED);
         } /* end of if Unpacking the IE list fails */
      } /* end of if the IE type is grouped */
   } /* end of loop to pack all the IEs */

   /* return success */
   RETVALUE(ROK);
} /*end of cmUnpkEgIeList */



/***********************************************************
*
*     Func : cmPkEgMsg
*
*
*     Desc : _egMsg 
   @brief eGTP Message Structure
   Refer to EgIe for types of IE
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgMsg
(
EgMsg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgMsg(param, mBuf)
EgMsg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgMsg);

   CMCHKPK(cmPkEgIeList, &param->egIeList, mBuf);
   CMCHKPK(cmPkEgMsgHdr, &param->msgHdr, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgMsg
*
*
*     Desc : _egMsg 
   @brief eGTP Message Structure
   Refer to EgIe for types of IE
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgMsg
(
EgMsg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgMsg(param, mBuf)
EgMsg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgMsg);

   CMCHKUNPK(cmUnpkEgMsgHdr, &param->msgHdr, mBuf);
   if (cmUnpkEgIeList (&param->egIeList, mBuf, &param->memCp) != ROK)
   {
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}




/***********************************************************
*
*     Func : cmPkEgIe
*
*
*     Desc : _egIe 
   @brief Information Element Structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgIe
(
EgIe *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgIe(param, mBuf)
EgIe *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgIe);

   switch(param->dataType) {

     case EG_PVT_EXTN:
         CMCHKPK(cmPkEgPvtExt, &param->t.pvtExt, mBuf);
         break;
      case EG_BEARER_FLAG:
         CMCHKPK(cmPkEgBearFlags, &param->t.bearFlags, mBuf);
         break;
      case EG_TRC_INFO:
         CMCHKPK(cmPkEgTrcInfo, &param->t.trcInfo, mBuf);
         break;
      case EG_FTEID:
         CMCHKPK(cmPkEgFTeid, &param->t.fTeid, mBuf);
         break;
      case EG_ULI_DATA:
         CMCHKPK(cmPkEgUli, &param->t.uli, mBuf);
         break;
      case EG_SNETWORK:
         CMCHKPK(cmPkEgSNetwork, &param->t.sNwk, mBuf);
         break;
      case EG_FQOS:
         CMCHKPK(cmPkEgFlowQos, &param->t.fQos, mBuf);
         break;
      case EG_BQOS_IEDATA:
         CMCHKPK(cmPkEgBearQos, &param->t.bQos, mBuf);
         break;
      case EG_PAA_IEDATA:
         CMCHKPK(cmPkEgPaa, &param->t.paa, mBuf);
         break;
      case EG_INDICATION:
         CMCHKPK(cmPkEgIndication, &param->t.indication, mBuf);
         break;
      case EG_CAUSE:
         CMCHKPK(cmPkEgCause, &param->t.cause, mBuf);
         break;
      case EG_AMBR:
         CMCHKPK(cmPkEgAMBR, &param->t.ambr, mBuf);
         break;
      case EG_GROUPED:
       CMCHKPK(cmPkEgGrouped, &param->t.grouped, mBuf);
         break;
      case EG_STRING_MAX:
         CMCHKPK(cmPkEgDatStr, &param->t.valStr, mBuf);
         break;
      case EG_STRING_132:
         CMCHKPK(cmPkEgDatStr132, &param->t.valStr132, mBuf);
         break;
      case EG_STRING_32:
         CMCHKPK(cmPkEgDatStr32, &param->t.valStr32, mBuf);
         break;
      case EG_STRING_16:
         CMCHKPK(cmPkEgDatStr16, &param->t.valStr16, mBuf);
         break;
      case EG_STRING_8:
         CMCHKPK(cmPkEgDatStr8, &param->t.valStr8, mBuf);
         break;
      case EG_UNSIGNED_32:
         CMCHKPK(SPkU32, param->t.valUnSgnd32, mBuf);
         break;
      case EG_UNSIGNED_16:
         CMCHKPK(SPkU16, param->t.valUnSgnd16, mBuf);
         break;
      case EG_UNSIGNED_8:
         CMCHKPK(SPkU8, param->t.valUnSgnd8, mBuf);
         break;
      case EG_GLOBAL_CNID:
         CMCHKPK(cmPkEgGblCnId, &param->t.gblCnId, mBuf);
         break;
      case EG_PDUNUM:
         CMCHKPK(cmPkEgPduNum, &param->t.pduNum, mBuf);
         break;
      case EG_AUTH_QUIN:
         CMCHKPK(cmPkEgAuthQt, &param->t.authQt, mBuf);
         break;
      case EG_AUTH_QUAD:
         CMCHKPK(cmPkEgAuthQuadrup, &param->t.quadruplet, mBuf);
         break;
      case EG_CMP_REQ:
         CMCHKPK(cmPkEgCrm, &param->t.crm, mBuf);
         break;
      case EG_GUTI:
         CMCHKPK(cmPkEgGuti, &param->t.guti, mBuf);
         break;
      case EG_F_CONT:
         CMCHKPK(cmPkEgFContainer, &param->t.fContainer, mBuf);
         break;
      case EG_TRGTID:
         CMCHKPK(cmPkEgTargetId, &param->t.targetId, mBuf);
         break;
      case EG_PKTFLOWID:
         CMCHKPK(cmPkEgPktFlowId, &param->t.pktFlowId, mBuf);
         break;
      case EG_SRCID:
         CMCHKPK(cmPkEgSrcId, &param->t.srcId, mBuf);
         break;
      case EG_PDN_CONN_SET_ID:
         CMCHKPK(cmPkEgCsid, &param->t.csid, mBuf);
         break;
      case EG_IP_ADDR:
         CMCHKPK(cmPkEgIpAddr, &param->t.ipAddr, mBuf);
         break;
      case EG_GSM_KEY_TRIP:
         CMCHKPK(cmPkEgGsmKeyT, &param->t.gsmKeyT, mBuf);
         break;
      case EG_UMTS_KEY_CIPH_QUIN:
         CMCHKPK(cmPkEgUMTSKeyUCQt, &param->t.umtsKeyUCQt, mBuf);
         break;
      case EG_GSM_KEY_CIPH_QUIN:
         CMCHKPK(cmPkEgGSMKeyUCQt, &param->t.gsmKeyUCQt, mBuf);
         break;
      case EG_UMTS_KEY_QUIN:
         CMCHKPK(cmPkEgUMTSKeyQt, &param->t.umtsKeyQt, mBuf);
         break;
      case EG_EPS_SEC_QUAD_QUIN:
         CMCHKPK(cmPkEgESecCxtQdQt, &param->t.eSecCxtQdQt, mBuf);
         break;
      case EG_UMTS_KEY_QUAD_QUIN:
         CMCHKPK(cmPkEgUMTSKeyQdQt, &param->t.umtsKeyQdQt, mBuf);
         break;
      case EG_F_CAUSE:
         CMCHKPK(cmPkEgFCause, &param->t.fCause, mBuf);
         break;
      case EG_S103_PDN_FW_INFO:
         CMCHKPK(cmPkEgS103PDF, &param->t.s103PDF, mBuf);
         break;
      case EG_S1U_DATA_FW:
         CMCHKPK(cmPkEgS1UDF, &param->t.s1UDF, mBuf);
         break;
      case EG_UE_TIME_ZONE:
         CMCHKPK(cmPkEgTimeZone, &param->t.timeZone, mBuf);
         break;
      case EG_TRACE_REF:
         CMCHKPK(cmPkEgTraceRef, &param->t.trcRef, mBuf);
         break;
      case EG_RAB_CONTEXT:
         CMCHKPK(cmPkEgRABCntxt, &param->t.rabCntxt, mBuf);
         break;
#ifdef EG_REL_930
      case  EG_MBMS_IPMCAST_DIST:
         CMCHKPK(cmPkEgMBMSIPMCastDist, &param->t.mbmsIPMCastDist, mBuf);
         break;
      case  EG_UCI:
         CMCHKPK(cmPkEgUCI, &param->t.uci, mBuf);
         break;
      case  EG_CSG_INFO_REP_ACT:
         CMCHKPK(cmPkEgCSGInfoRepAct, &param->t.csgInfoReqAct, mBuf);
         break;
#endif /* EG_REL_930 */
      default :
         RETVALUE(RFAILED);
   }

   CMCHKPK(SPkU8, param->dataType, mBuf);
   CMCHKPK(SPkU8, param->ieInst, mBuf);
   CMCHKPK(SPkU8, param->ieType, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgIe
*
*
*     Desc : _egIe 
   @brief Information Element Structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgIe
(
EgIe *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgIe(param, mBuf)
EgIe *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgIe);

   CMCHKUNPK(SUnpkU8, &param->ieType, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ieInst, mBuf);
   CMCHKUNPK(SUnpkU8, &param->dataType, mBuf);

   switch(param->dataType)
   {
      case EG_UNSIGNED_8: 
         CMCHKUNPK(SUnpkU8, &param->t.valUnSgnd8, mBuf);
         break;
      case EG_UNSIGNED_16:
         CMCHKUNPK(SUnpkU16, &param->t.valUnSgnd16, mBuf);
         break;
      case EG_UNSIGNED_32:
         CMCHKUNPK(SUnpkU32, &param->t.valUnSgnd32, mBuf);
         break;
      case EG_STRING_8:
         CMCHKUNPK(cmUnpkEgDatStr8, &param->t.valStr8, mBuf);
         break;
      case EG_STRING_16:
         CMCHKUNPK(cmUnpkEgDatStr16, &param->t.valStr16, mBuf);
         break;
      case EG_STRING_32:
         CMCHKUNPK(cmUnpkEgDatStr32, &param->t.valStr32, mBuf);
         break;
      case EG_STRING_132:
         CMCHKUNPK(cmUnpkEgDatStr132, &param->t.valStr132, mBuf);
         break;
      case EG_STRING_MAX:
         CMCHKUNPK(cmUnpkEgDatStr, &param->t.valStr, mBuf);
         break;
      case EG_GROUPED:
         CMCHKUNPK(cmUnpkEgGrouped, &param->t.grouped, mBuf); 
         break;
      case EG_CAUSE:
         CMCHKUNPK(cmUnpkEgCause, &param->t.cause, mBuf);
         break;
      case EG_AMBR:
         CMCHKUNPK(cmUnpkEgAMBR, &param->t.ambr, mBuf);
         break;
      case EG_INDICATION:
         CMCHKUNPK(cmUnpkEgIndication, &param->t.indication, mBuf);
         break;
      case EG_PAA_IEDATA:
         CMCHKUNPK(cmUnpkEgPaa, &param->t.paa, mBuf);
         break;
      case EG_BQOS_IEDATA:
         CMCHKUNPK(cmUnpkEgBearQos, &param->t.bQos, mBuf);
         break;
      case EG_FQOS:
         CMCHKUNPK(cmUnpkEgFlowQos, &param->t.fQos, mBuf);
         break;
      case EG_SNETWORK:
         CMCHKUNPK(cmUnpkEgSNetwork, &param->t.sNwk, mBuf);
         break;
      case EG_ULI_DATA:
         CMCHKUNPK(cmUnpkEgUli, &param->t.uli, mBuf);
         break;
      case EG_FTEID:
         CMCHKUNPK(cmUnpkEgFTeid, &param->t.fTeid, mBuf);
         break;
      case EG_TRC_INFO:
         CMCHKUNPK(cmUnpkEgTrcInfo, &param->t.trcInfo, mBuf);
         break;
      case EG_BEARER_FLAG:
         CMCHKUNPK(cmUnpkEgBearFlags, &param->t.bearFlags, mBuf);
         break;
      case EG_PVT_EXTN:
         CMCHKUNPK(cmUnpkEgPvtExt, &param->t.pvtExt, mBuf);
         break;
      case EG_GLOBAL_CNID:
         CMCHKUNPK(cmUnpkEgGblCnId, &param->t.gblCnId, mBuf);
         break;
/* #ifdef EGTP_C_PHASE2 */
       case EG_PDUNUM:
         CMCHKUNPK(cmUnpkEgPduNum, &param->t.pduNum, mBuf);
         break;
      case EG_AUTH_QUIN:
         CMCHKUNPK(cmUnpkEgAuthQt, &param->t.authQt, mBuf);
         break;
      case EG_AUTH_QUAD:
         CMCHKUNPK(cmUnpkEgAuthQuadrup, &param->t.quadruplet, mBuf);
         break;
      case EG_CMP_REQ:
         CMCHKUNPK(cmUnpkEgCrm, &param->t.crm, mBuf);
         break;
      case EG_GUTI:
         CMCHKUNPK(cmUnpkEgGuti, &param->t.guti, mBuf);
         break;
      case EG_F_CONT:
         CMCHKUNPK(cmUnpkEgFContainer, &param->t.fContainer, mBuf);
         break;
      case EG_TRGTID:
         CMCHKUNPK(cmUnpkEgTargetId, &param->t.targetId, mBuf);
         break;
      case EG_PKTFLOWID:
         CMCHKUNPK(cmUnpkEgPktFlowId, &param->t.pktFlowId, mBuf);
         break;
      case EG_SRCID:
         CMCHKUNPK(cmUnpkEgSrcId, &param->t.srcId, mBuf);
         break;
      case EG_PDN_CONN_SET_ID:
         CMCHKUNPK(cmUnpkEgCsid, &param->t.csid, mBuf);
         break;
      case EG_IP_ADDR:
         CMCHKUNPK(cmUnpkEgIpAddr, &param->t.ipAddr, mBuf);
         break;
      case EG_GSM_KEY_TRIP:
         CMCHKUNPK(cmUnpkEgGsmKeyT, &param->t.gsmKeyT, mBuf);
         break;
      case EG_UMTS_KEY_CIPH_QUIN:
         CMCHKUNPK(cmUnpkEgUMTSKeyUCQt, &param->t.umtsKeyUCQt, mBuf);
         break;
      case EG_GSM_KEY_CIPH_QUIN:
         CMCHKUNPK(cmUnpkEgGSMKeyUCQt, &param->t.gsmKeyUCQt, mBuf);
         break;
      case EG_UMTS_KEY_QUIN:
         CMCHKUNPK(cmUnpkEgUMTSKeyQt, &param->t.umtsKeyQt, mBuf);
         break;
      case EG_EPS_SEC_QUAD_QUIN:
         CMCHKUNPK(cmUnpkEgESecCxtQdQt, &param->t.eSecCxtQdQt, mBuf);
         break;
      case EG_UMTS_KEY_QUAD_QUIN:
         CMCHKUNPK(cmUnpkEgUMTSKeyQdQt, &param->t.umtsKeyQdQt, mBuf);
         break;
      case EG_F_CAUSE:
         CMCHKUNPK(cmUnpkEgFCause, &param->t.fCause, mBuf);
         break;
      case EG_S103_PDN_FW_INFO:
         CMCHKUNPK(cmUnpkEgS103PDF, &param->t.s103PDF, mBuf);
         break;
      case EG_S1U_DATA_FW:
         CMCHKUNPK(cmUnpkEgS1UDF, &param->t.s1UDF, mBuf);
         break;
      case EG_UE_TIME_ZONE:
         CMCHKUNPK(cmUnpkEgTimeZone, &param->t.timeZone, mBuf);
         break;
      case EG_TRACE_REF:
         CMCHKUNPK(cmUnpkEgTraceRef, &param->t.trcRef, mBuf);
         break;
      case EG_RAB_CONTEXT:
         CMCHKUNPK(cmUnpkEgRABCntxt, &param->t.rabCntxt, mBuf);
         break;
/*#endif *//* EGTP_C_PHASE2 */
#ifdef EG_REL_930
      case  EG_MBMS_IPMCAST_DIST:
         CMCHKUNPK(cmUnpkEgMBMSIPMCastDist, &param->t.mbmsIPMCastDist, mBuf);
         break;
      case  EG_UCI:
         CMCHKUNPK(cmUnpkEgUCI, &param->t.uci, mBuf);
         break;
      case  EG_CSG_INFO_REP_ACT:
         CMCHKUNPK(cmUnpkEgCSGInfoRepAct, &param->t.csgInfoReqAct, mBuf);
         break;
#endif /* EG_REL_930 */

      default:
         RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}







/***********************************************************
*
*     Func : cmPkEgPathInfo
*
*
*     Desc : _egPathInfo
   @brief Event Structure for pathinfo
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgPathInfo
(
EgPathInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgPathInfo(param, mBuf)
EgPathInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgPathInfo);

   switch(param->staType) {
      case EGT_STATYPE_PATH:
         CMCHKPK(cmPkCmTptAddr, &param->u.localAddr, mBuf);
         break;
      case EGT_STATYPE_TUNNEL:
         CMCHKPK(SPkU32, param->u.teid, mBuf);
         break;
      default :
         RETVALUE(RFAILED);
   }

   switch(param->staType) {
      case EGT_STATYPE_TUNNEL:
         CMCHKPK(SPkU8, (U8)param->s.tunState, mBuf);
         break;
      case EGT_STATYPE_PATH:
         CMCHKPK(cmPkTknU8, &param->s.pathState, mBuf);
         break;
      default :
         RETVALUE(RFAILED);
   }

   CMCHKPK(SPkU8, param->staType, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgPathInfo
*
*
*     Desc : _egPathInfo
   @brief Event Structure for pathinfo
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgPathInfo
(
EgPathInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgPathInfo(param, mBuf)
EgPathInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgPathInfo);

   CMCHKUNPK(SUnpkU8, &param->staType, mBuf);

      switch(param->staType) {
      case EGT_STATYPE_PATH:
         CMCHKUNPK(cmUnpkTknU8, &param->s.pathState, mBuf);
         break;
      case EGT_STATYPE_TUNNEL:
         CMCHKUNPK(SUnpkU8, (U8 *)&param->s.tunState, mBuf);
         break;
      default :
         RETVALUE(RFAILED);
   }

   switch(param->staType) {
      case EGT_STATYPE_PATH:
         CMCHKUNPK(cmUnpkCmTptAddr, &param->u.localAddr, mBuf);
         break;
      case EGT_STATYPE_TUNNEL:
         CMCHKUNPK(SUnpkU32, &param->u.teid, mBuf);
         break;
      default :
         RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkEgPathStatus
*
*
*     Desc : _egPathStatus
   @brief Event Structure pathStatus
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgPathStatus
(
EgPathStatus *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgPathStatus(param, mBuf)
EgPathStatus *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgPathStatus);

   CMCHKPK(cmPkTknStr, &param->dgn, mBuf);
   CMCHKPK(cmPkTknU8, &param->message, mBuf);
   CMCHKPK(cmPkTknU32, &param->seqNum, mBuf);
   CMCHKPK(SPkU8, param->cause, mBuf);
   CMCHKPK(cmPkEgPathInfo, &param->pathInfo, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgPathStatus
*
*
*     Desc : _egPathStatus
   @brief Event Structure pathStatus
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgPathStatus
(
EgPathStatus *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgPathStatus(param, mBuf)
EgPathStatus *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgPathStatus);

   CMCHKUNPK(cmUnpkEgPathInfo, &param->pathInfo, mBuf);
   CMCHKUNPK(SUnpkU8, &param->cause, mBuf);
   CMCHKUNPK(cmUnpkTknU32, &param->seqNum, mBuf);
   CMCHKUNPK(cmUnpkTknU8, &param->message, mBuf);
   CMCHKUNPK(cmUnpkTknStr, &param->dgn, mBuf);
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkEgErrEvnt
*
*
*     Desc : _egErrEvnt
   @brief Event Structure ErrEvnt
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgErrEvnt
(
EgErrEvnt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgErrEvnt(param, mBuf)
EgErrEvnt *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgErrEvnt);

   CMCHKPK(SPkU8, param->failedMsgType, mBuf);
   CMCHKPK(SPkU8, param->failedIeType, mBuf);
   CMCHKPK(SPkU8, param->failedIeInst, mBuf);
   CMCHKPK(SPkU8, (U8)param->errCause, mBuf);
   CMCHKPK(SPkU32, param->seqNo, mBuf);
   CMCHKPK(SPkU8, param->intfType, mBuf);
   CMCHKPK(cmPkCmTptAddr, &param->remAddr, mBuf);
   CMCHKPK(SPkU32, param->remTeid, mBuf);
   CMCHKPK(SPkU32, param->transId, mBuf);
   CMCHKPK(SPkU32, param->localTeid, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgErrEvnt
*
*
*     Desc : _egErrEvnt
   @brief Event Structure ErrEvnt
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgErrEvnt
(
EgErrEvnt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgErrEvnt(param, mBuf)
EgErrEvnt *param;
Buffer *mBuf;
#endif
{
   U8   errCause = 0;
   TRC3(cmUnpkEgErrEvnt);

   CMCHKUNPK(SUnpkU32, &param->localTeid, mBuf);
   CMCHKUNPK(SUnpkU32, &param->transId, mBuf);
   CMCHKUNPK(SUnpkU32, &param->remTeid, mBuf);
   CMCHKUNPK(cmUnpkCmTptAddr, &param->remAddr, mBuf);
   CMCHKUNPK(SUnpkU8, &param->intfType, mBuf);
   CMCHKUNPK(SUnpkU32, &param->seqNo, mBuf);
   CMCHKUNPK(SUnpkU8, &errCause, mBuf);
   param->errCause = (EgtErrType)errCause;
   CMCHKUNPK(SUnpkU8, &param->failedIeInst, mBuf);
   CMCHKUNPK(SUnpkU8, &param->failedIeType, mBuf);
   CMCHKUNPK(SUnpkU8, &param->failedMsgType, mBuf);
   RETVALUE(ROK);
}

#endif /* EGTP_C */


/***********************************************************
*
*     Func : cmPkEgPvtExt
*
*
*     Desc : Private Extension
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgPvtExt
(
EgPvtExt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgPvtExt(param, mBuf)
EgPvtExt *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgPvtExt);

   CMCHKPK(cmPkEgDatStr132, &param->propVal, mBuf);
   CMCHKPK(SPkU16, param->entId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgPvtExt
*
*
*     Desc : Private Extension
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgPvtExt
(
EgPvtExt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgPvtExt(param, mBuf)
EgPvtExt *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgPvtExt);

   CMCHKUNPK(SUnpkU16, &param->entId, mBuf);
   CMCHKUNPK(cmUnpkEgDatStr132, &param->propVal, mBuf);
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkEgDatStr132
*
*
*     Desc : String -- max 132 byte length
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgDatStr132
(
EgDatStr132 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgDatStr132(param, mBuf)
EgDatStr132 *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkEgDatStr132);


#ifdef ALIGN_64BIT
   CMCHKPK(SPkU32, param->spare2, mBuf);

#endif
   CMCHKPK(SPkU16, param->spare1, mBuf);
   for (i=param->length-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->val[i], mBuf);
   }
   CMCHKPK(SPkU16, param->length, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkEgDatStr132
*
*
*     Desc : String -- max 132 byte length
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgDatStr132
(
EgDatStr132 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgDatStr132(param, mBuf)
EgDatStr132 *param;
Buffer *mBuf;
#endif
{

   U32 i;
   TRC3(cmUnpkEgDatStr132);

   CMCHKUNPK(SUnpkU16, &param->length, mBuf);
   for (i=0; i<param->length; i++) {
      CMCHKUNPK(SUnpkU8, &param->val[i], mBuf);
   }
   CMCHKUNPK(SUnpkU16, &param->spare1, mBuf);

#ifdef ALIGN_64BIT
   CMCHKUNPK(SUnpkU32, &param->spare2, mBuf);

#endif
   RETVALUE(ROK);
}


/* egt_c_001.main_1    1. Egtpu release changes */
#ifdef EGTP_U

/***********************************************************
*
*     Func   : cmPkEgtEguDatReq
*
*     Desc   : EgtEguDatReq
*              @brief Packing of primitive EgtEguDatReq
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgtEguDatReq
(
Pst                 *pst,              
SpId                spId,              
EgtUEvnt            *egtUEvnt          
)
#else
PUBLIC S16 cmPkEgtEguDatReq(pst, spId, egtUEvnt)
Pst                 *pst;              
SpId                spId;              
EgtUEvnt            *egtUEvnt;         
#endif
{
   Buffer *mBuf = NULLP;

   TRC3(cmPkEgtEguDatReq);

   /* allocate memory for the buffer */
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
                "cmPkEgtEguDatReq: Allocating memory for buffer failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

      RETVALUE(RFAILED);
   } /* end of if allocating memory fails */
   egtUEvnt->event = EVTEGTUDATREQ;

   /* in case of loose coupling pack the whole event */
   if (pst->selector == EGT_SEL_LC)
   {
      CMCHKPKLOG(cmPkEgtUEvnt, egtUEvnt, mBuf, EEGTXXX, pst);
   
      SPutSBuf(pst->region, pst->pool, (Data *) egtUEvnt,\
                      (Size) (sizeof(EgtUEvnt)));
   } /* end of if selector is loosely coupled */

   /* in case of lightweight loose coupling pack only the pointer */
   else if (pst->selector == EGT_SEL_LWLC)
   {
      CMCHKPKLOG(cmPkPtr, ( (PTR)egtUEvnt), mBuf, EEGTXXX, pst);
   } /* end of if selector is lightweight loosely coupled */

   CMCHKPKLOG(cmPkSpId, spId, mBuf, EEGTXXX, pst);

   pst->event = EVTEGTUDATREQ;

   RETVALUE(SPstTsk(pst, mBuf));
} /* end of cmPkEgtEguDatReq */


/***********************************************************
*
*     Func   : cmUnpkEgtEguDatReq
*
*     Desc   : EgtEguDatReq
*              @brief Unpacking of primitive EgtEguDatReq
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgtEguDatReq
(
EgtEguDatReq        func,             
Pst                 *pst,              
Buffer              *mBuf,
Mem                 *memInfo              
)
#else
PUBLIC S16 cmUnpkEgtEguDatReq(func, pst, mBuf, memInfo)
EgtEguDatReq        func;             
Pst                 *pst;              
Buffer              *mBuf;
Mem                 * memInfo;            
#endif
{
   SpId      spId = 0;
   EgtUEvnt  *egtUEvnt = NULLP;
   S16       retValue = ROK;

   TRC3(cmUnpkEgtEguDatReq);


   CMCHKUNPKLOG(cmUnpkSpId, &spId, mBuf, EEGTXXX, pst);

   /* in case of loose coupling pack the whole event */
   if (pst->selector == EGT_SEL_LC)
   {
      if ( (retValue = SGetSBuf(memInfo->region, memInfo->pool, (Data **)&egtUEvnt, sizeof(EgtUEvnt))) != ROK)
      {
         SPutMsg(mBuf); 
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
               "cmUnpkEgtEguDatReq: Allocating memory for message failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

         RETVALUE(RFAILED);
      } /* end of if allocating memory fails */

      cmMemset( (U8 *)egtUEvnt, 0, sizeof(EgtUEvnt));

      if((retValue = cmUnpkEgtUEvnt((egtUEvnt), mBuf, pst)) != ROK )
      {

         SPutMsg(mBuf); 
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
               "cmUnpkEgtEguDatReq: Allocating memory for message failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(RFAILED);
      } /* end of if allocating memory fails */
   } /* end of if selector is loosely coupled */

   /* in case of lightweight loose coupling pack only the pointer */
   else if (pst->selector == EGT_SEL_LWLC)
   {
      CMCHKUNPKLOG(cmUnpkPtr, ( (PTR *)&egtUEvnt), mBuf, EEGTXXX, pst);
   } /* end of if selector is lightweight loosely coupled */

   /* after unpacking all the elements, release the buffer memory */
   SPutMsg(mBuf);

   /* call the function after unpacking */
   RETVALUE( (*func)(pst, spId, egtUEvnt));
} /* end of cmUnpkEgtEguDatReq */


/***********************************************************
*
*     Func   : cmPkEgtEguDatInd
*
*     Desc   : EgtEguDatInd
*              @brief Packing of primitive EgtEguDatInd
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgtEguDatInd
(
Pst                 *pst,            
SuId                suId,            
EgtUEvnt            *egtUEvnt        
)
#else
PUBLIC S16 cmPkEgtEguDatInd(pst, suId, egtUEvnt)
Pst                 *pst;           
SuId                suId;          
EgtUEvnt            *egtUEvnt;    
#endif
{
   Buffer *mBuf = NULLP;

   TRC3(cmPkEgtEguDatInd);

   /* allocate memory for the buffer */
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
                "cmPkEgtEguDatInd: Allocating memory for buffer failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

      RETVALUE(RFAILED);
   } /* end of if allocating memory fails */

   egtUEvnt->event = EVTEGTUDATIND;
   /* in case of loose coupling pack the whole event */
   if (pst->selector == EGT_SEL_LC)
   {
      CMCHKPKLOG(cmPkEgtUEvnt, egtUEvnt, mBuf, EEGTXXX, pst);
      SPutSBuf(pst->region, pst->pool, (Data* )egtUEvnt,
                        (sizeof(EgtUEvnt)));

   } /* end of if selector is loosely coupled */

   /* in case of lightweight loose coupling pack only the pointer */
   else if (pst->selector == EGT_SEL_LWLC)
   {
      CMCHKPKLOG(cmPkPtr, ( (PTR)egtUEvnt), mBuf, EEGTXXX, pst);
   } /* end of if selector is lightweight loosely coupled */

   CMCHKPKLOG(cmPkSuId, suId, mBuf, EEGTXXX, pst);

   pst->event = EVTEGTUDATIND;

   RETVALUE(SPstTsk(pst, mBuf));
} /* end of cmPkEgtEguDatInd */


/***********************************************************
*
*     Func   : cmUnpkEgtEguDatInd
*
*     Desc   : EgtEguDatInd
*              @brief Unpacking of primitive EgtEguDatInd
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgtEguDatInd
(
EgtEguDatInd        func,         
Pst                 *pst,        
Buffer              *mBuf       
)
#else
PUBLIC S16 cmUnpkEgtEguDatInd(func, pst, mBuf)
EgtEguDatInd        func;     
Pst                 *pst;      
Buffer              *mBuf;   
#endif
{
   SuId      suId = 0;
   EgtUEvnt  *egtUEvnt= NULLP;
   Mem       memInfo;
   S16       retValue = 0;

   TRC3(cmUnpkEgtEguDatInd);

   cmMemset( (U8 *)&memInfo, 0, sizeof(Mem));

   memInfo.region = pst->region;
   memInfo.pool = pst->pool;

   /* in case of loose coupling pack the whole event */
   if (pst->selector == EGT_SEL_LC)
   {
      if ( (retValue = SGetSBuf(memInfo.region, memInfo.pool, (Data **)&egtUEvnt, sizeof(EgtUEvnt))) != ROK)
      {
         SPutMsg(mBuf); 
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
               "cmUnpkEgtEguDatInd: Allocating memory for message failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

         RETVALUE(RFAILED);
      } /* end of if allocating memory fails */

      cmMemset( (U8 *)egtUEvnt, 0, sizeof(EgtUEvnt));

      CMCHKUNPKLOG(cmUnpkSuId, &suId, mBuf, EEGTXXX, pst);

      if((retValue = cmUnpkEgtUEvnt((egtUEvnt), mBuf, pst)) != ROK )
      {

         SPutMsg(mBuf); 
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
               "cmUnpkEgtEguDatInd: Allocating memory for message failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(RFAILED);
      } /* end of if allocating memory fails */
   } /* end of if selector is loosely coupled */

   /* in case of lightweight loose coupling pack only the pointer */
   else if (pst->selector == EGT_SEL_LWLC)
   {
      /* egt_c_001.main_4: CNE_DATA_TEST - Unpacking the suId*/
      CMCHKUNPKLOG(cmUnpkSuId, &suId, mBuf, EEGTXXX, pst);
      CMCHKUNPKLOG(cmUnpkPtr, ( (PTR *)&egtUEvnt), mBuf, EEGTXXX, pst);
   } /* end of if selector is lightweight loosely coupled */

   /* after unpacking all the elements, release the buffer memory */
   SPutMsg(mBuf);

   /* call the function after unpacking */
   RETVALUE( (*func)(pst, suId, egtUEvnt));
} /* end of cmUnpkEgtEguDatInd */


/***********************************************************
*
*     Func   : cmPkEgtEguLclTnlMgmtReq
*
*     Desc   : EgtEguLclTnlMgmtReq
*              @brief Packing of primitive EgtEguLclTnlMgmtReq
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgtEguLclTnlMgmtReq
(
Pst                 *pst,         
SpId                spId,        
EgtUEvnt            *egtUEvnt   
)
#else
PUBLIC S16 cmPkEgtEguLclTnlMgmtReq(pst, spId, egtUEvnt)
Pst                 *pst;       
SpId                spId;      
EgtUEvnt            *egtUEvnt;
#endif
{
   Buffer *mBuf = NULLP;

   TRC3(cmPkEgtEguLclTnlMgmtReq);

   /* allocate memory for the buffer */
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
                "cmPkEgtEguLclTnlMgmtReq: Allocating memory for buffer failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

      RETVALUE(RFAILED);
   } /* end of if allocating memory fails */

   egtUEvnt->event = EVTEGTULCLTNLMGMTREQ;
   /* in case of loose coupling pack the whole event */
   if (pst->selector == EGT_SEL_LC)
   {
      CMCHKPKLOG(cmPkEgtUEvnt, egtUEvnt, mBuf, EEGTXXX, pst);
      SPutSBuf(pst->region, pst->pool, (Data* )egtUEvnt,
                        (sizeof(EgtUEvnt)));
   } /* end of if selectr is loosely coupled */

   /* in case of lightweight loose coupling pack only the pointer */
   else if (pst->selector == EGT_SEL_LWLC)
   {
      CMCHKPKLOG(cmPkPtr, ( (PTR)egtUEvnt), mBuf, EEGTXXX, pst);
   } /* end of if selector is lightweight loosely coupled */

   CMCHKPKLOG(cmPkSpId, spId, mBuf, EEGTXXX, pst);

   pst->event = EVTEGTULCLTNLMGMTREQ;

   RETVALUE(SPstTsk(pst, mBuf));
} /* end of cmPkEgtEguLclTnlMgmtReq */


/***********************************************************
*
*     Func   : cmUnpkEgtEguLclTnlMgmtReq
*
*     Desc   : EgtEguLclTnlMgmtReq
*              @brief Unpacking of primitive EgtEguLclTnlMgmtReq
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgtEguLclTnlMgmtReq
(
EgtEguLclTnlMgmtReq func,         
Pst                 *pst,        
Buffer              *mBuf,
Mem                 *memInfo
)
#else
PUBLIC S16 cmUnpkEgtEguLclTnlMgmtReq(func, pst, mBuf, memInfo)
EgtEguLclTnlMgmtReq func;        
Pst                 *pst;       
Buffer              *mBuf;     
Mem                 *memInfo;
#endif
{
   SpId      spId = 0;
   EgtUEvnt  *egtUEvnt = NULLP;
   S16       retValue = 0;

   TRC3(cmUnpkEgtEguLclTnlMgmtReq);

   CMCHKUNPKLOG(cmUnpkSpId, &spId, mBuf, EEGTXXX, pst);

   /* in case of loose coupling pack the whole event */
   if (pst->selector == EGT_SEL_LC)
   {
      if ((retValue = SGetSBuf(memInfo->region, memInfo->pool, (Data **)&egtUEvnt, sizeof(EgtUEvnt))) != ROK)
      {
         /*-- egt_c_001.main_10: free memory in case of Error --*/
         SPutMsg(mBuf); 
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                   __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
                   "cmUnpkEgtEguLclTnlMgmtReq(): Allocating memory for buffer failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

           RETVALUE(retValue);
      }

      cmMemset( (U8 *)egtUEvnt, 0, sizeof(EgtUEvnt));
      if((retValue = cmUnpkEgtUEvnt((egtUEvnt), mBuf, pst)) != ROK )
      {
         SPutMsg(mBuf); 
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                      __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
                      "cmUnpkEgtEguLclTnlMgmtReq: Allocating memory for message failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(RFAILED);
      } /* end of if allocating memory fails */
   } /* end of if selector is loosely coupled */

   /* in case of lightweight loose coupling pack only the pointer */
   else if (pst->selector == EGT_SEL_LWLC)
   {
      CMCHKUNPKLOG(cmUnpkPtr, ( (PTR *)&egtUEvnt), mBuf, EEGTXXX, pst);
   } /* end of if selector is lightweight loosely coupled */

   /* after unpacking all the elements, release the buffer memory */
   SPutMsg(mBuf);

   /* call the function after unpacking */
   RETVALUE( (*func)(pst, spId, egtUEvnt));
} /* end of cmUnpkEgtEguLclTnlMgmtReq */


/***********************************************************
*
*     Func   : cmPkEgtEguLclTnlMgmtCfm
*
*     Desc   : EgtEguLclTnlMgmtCfm
*              @brief Packing of primitive EgtEguLclTnlMgmtCfm
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgtEguLclTnlMgmtCfm
(
Pst                 *pst,       
SuId                suId,      
EgtUEvnt            *egtUEvnt 
)
#else
PUBLIC S16 cmPkEgtEguLclTnlMgmtCfm(pst, suId, egtUEvnt)
Pst                 *pst;           
SuId                suId;          
EgtUEvnt            *egtUEvnt;    
#endif
{
   Buffer *mBuf = NULLP;

   TRC3(cmPkEgtEguLclTnlMgmtCfm);

   /* allocate memory for the buffer */
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
                "cmPkEgtEguLclTnlMgmtCfm: Allocating memory for buffer failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

      RETVALUE(RFAILED);
   } /* end of if allocating memory fails */

   egtUEvnt->event = EVTEGTULCLTNLMGMTCFM;
   /* in case of loose coupling pack the whole event */
   if (pst->selector == EGT_SEL_LC)
   {
      CMCHKPKLOG(cmPkEgtUEvnt, egtUEvnt, mBuf, EEGTXXX, pst);
      SPutSBuf(pst->region, pst->pool, (Data* )egtUEvnt,
                        (sizeof(EgtUEvnt)));
   } /* end of if selector is loosely coupled */

   /* in case of lightweight loose coupling pack only the pointer */
   else if (pst->selector == EGT_SEL_LWLC)
   {
      CMCHKPKLOG(cmPkPtr, ( (PTR)egtUEvnt), mBuf, EEGTXXX, pst);
   } /* end of if selector is lightweight loosely coupled */

   CMCHKPKLOG(cmPkSuId, suId, mBuf, EEGTXXX, pst);

   pst->event = EVTEGTULCLTNLMGMTCFM;

   RETVALUE(SPstTsk(pst, mBuf));
} /* end of cmPkEgtEguLclTnlMgmtCfm */


/***********************************************************
*
*     Func   : cmUnpkEgtEguLclTnlMgmtCfm
*
*     Desc   : EgtEguLclTnlMgmtCfm
*              @brief Unpacking of primitive EgtEguLclTnlMgmtCfm
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgtEguLclTnlMgmtCfm
(
EgtEguLclTnlMgmtCfm func,         
Pst                 *pst,        
Buffer              *mBuf       
)
#else
PUBLIC S16 cmUnpkEgtEguLclTnlMgmtCfm(func, pst, mBuf)
EgtEguLclTnlMgmtCfm func;         
Pst                 *pst;        
Buffer              *mBuf;      
#endif
{
   SuId      suId = 0;
   EgtUEvnt  *egtUEvnt = NULLP;
   Mem       memInfo;
   S16       retValue = 0;

   TRC3(cmUnpkEgtEguLclTnlMgmtCfm);

   cmMemset( (U8 *)&memInfo, 0, sizeof(Mem));

   memInfo.region = pst->region;
   memInfo.pool = pst->pool;

   CMCHKUNPKLOG(cmUnpkSuId, &suId, mBuf, EEGTXXX, pst);

   /* in case of loose coupling pack the whole event */
   if (pst->selector == EGT_SEL_LC)
   {
      if ((retValue = SGetSBuf(memInfo.region, memInfo.pool, (Data **)&egtUEvnt, sizeof(EgtUEvnt))) != ROK)
      {
         /*-- egt_c_001.main_10: free memory in case of Error --*/
         SPutMsg(mBuf); 
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
                "cmUnpkEgtEguLclTnlMgmtCfm() : Allocating memory for buffer failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

           RETVALUE(retValue);
      }

      cmMemset( (U8 *)egtUEvnt, 0, sizeof(EgtUEvnt));
      if((retValue = cmUnpkEgtUEvnt((egtUEvnt), mBuf, pst)) != ROK )
      {

         SPutMsg(mBuf); 
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                      __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
                      "cmUnpkEgtEguLclTnlMgmtCfm: Allocating memory for message failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(RFAILED);
      } /* end of if allocating memory fails */
   } /* end of if selector is loosely coupled */

   /* in case of lightweight loose coupling pack only the pointer */
   else if (pst->selector == EGT_SEL_LWLC)
   {
      CMCHKUNPKLOG(cmUnpkPtr, ( (PTR *)&egtUEvnt), mBuf, EEGTXXX, pst);
   } /* end of if selector is lightweight loosely coupled */

   /* after unpacking all the elements, release the buffer memory */
   SPutMsg(mBuf);

   /* call the function after unpacking */
   RETVALUE( (*func)(pst, suId, egtUEvnt));
} /* end of cmUnpkEgtEguLclTnlMgmtCfm */


/***********************************************************
*
*     Func   : cmPkEgtEguStaReq
*
*     Desc   : EgtEguStaReq
*              @brief Packing of primitive EgtEguStaReq
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgtEguStaReq
(
Pst                 *pst,          
SpId                spId,         
EgtUEvnt            *egtUEvnt    
)
#else
PUBLIC S16 cmPkEgtEguStaReq(pst, spId, egtUEvnt)
Pst                 *pst;         
SpId                spId;        
EgtUEvnt            *egtUEvnt;  
#endif
{
   Buffer *mBuf = NULLP;

   TRC3(cmPkEgtEguStaReq);

   /* allocate memory for the buffer */
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
                "cmPkEgtEguStaReq: Allocating memory for buffer failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

      RETVALUE(RFAILED);
   } /* end of if allocating memory fails */

   egtUEvnt->event = EVTEGTUSTAREQ;
   /* in case of loose coupling pack the whole event */
   if (pst->selector == EGT_SEL_LC)
   {
      CMCHKPKLOG(cmPkEgtUEvnt, egtUEvnt, mBuf, EEGTXXX, pst);
      SPutSBuf(pst->region, pst->pool, (Data* )egtUEvnt,
                        (sizeof(EgtUEvnt)));
   } /* end of if selector is loosely coupled */

   /* in case of lightweight loose coupling pack only the pointer */
   else if (pst->selector == EGT_SEL_LWLC)
   {
      CMCHKPKLOG(cmPkPtr, ( (PTR)egtUEvnt), mBuf, EEGTXXX, pst);
   } /* end of if selector is lightweight loosely coupled */

   CMCHKPKLOG(cmPkSpId, spId, mBuf, EEGTXXX, pst);

   pst->event = EVTEGTUSTAREQ;

   RETVALUE(SPstTsk(pst, mBuf));
} /* end of cmPkEgtEguStaReq */


/***********************************************************
*
*     Func   : cmUnpkEgtEguStaReq
*
*     Desc   : EgtEguStaReq
*              @brief Unpacking of primitive EgtEguStaReq
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgtEguStaReq
(
EgtEguStaReq        func,          
Pst                 *pst,         
Buffer              *mBuf,     
Mem                 *memInfo
)
#else
PUBLIC S16 cmUnpkEgtEguStaReq(func, pst, mBuf, memInfo)
EgtEguStaReq        func;         
Pst                 *pst;        
Buffer              *mBuf;      
Mem                 *memInfo
#endif
{
   SpId      spId = 0;
   EgtUEvnt  *egtUEvnt = NULLP;
   S16       retValue = 0;

   TRC3(cmUnpkEgtEguStaReq);

   CMCHKUNPKLOG(cmUnpkSpId, &spId, mBuf, EEGTXXX, pst);

   /* in case of loose coupling pack the whole event */
   if (pst->selector == EGT_SEL_LC)
   {
      if ((retValue = SGetSBuf(memInfo->region, memInfo->pool, (Data **)&egtUEvnt, sizeof(EgtUEvnt))) != ROK)
      {
         SPutMsg(mBuf); 
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
                "cmUnpkEgtEguStaReq() : Allocating memory for buffer failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

           RETVALUE(retValue);
      }

      cmMemset( (U8 *)egtUEvnt, 0, sizeof(EgtUEvnt));
      if((retValue = cmUnpkEgtUEvnt((egtUEvnt), mBuf, pst)) != ROK )
      {

         SPutMsg(mBuf); 
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                      __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
                      "cmUnpkEgtEguStaReq: Allocating memory for message failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(RFAILED);
      } /* end of if allocating memory fails */
   } /* end of if selector is loosely coupled */

   /* in case of lightweight loose coupling pack only the pointer */
   else if (pst->selector == EGT_SEL_LWLC)
   {
      CMCHKUNPKLOG(cmUnpkPtr, ( (PTR *)&egtUEvnt), mBuf, EEGTXXX, pst);
   } /* end of if selector is lightweight loosely coupled */

   /* after unpacking all the elements, release the buffer memory */
   SPutMsg(mBuf);

   /* call the function after unpacking */
   RETVALUE( (*func)(pst, spId, egtUEvnt));
} /* end of cmUnpkEgtEguStaReq */


/***********************************************************
*
*     Func   : cmPkEgtEguStaCfm
*
*     Desc   : EgtEguStaCfm
*              @brief Packing of primitive EgtEguStaCfm
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgtEguStaCfm
(
Pst                 *pst,          
SuId                suId,         
EgtUEvnt            *egtUEvnt    
)
#else
PUBLIC S16 cmPkEgtEguStaCfm(pst, suId, egtUEvnt)
Pst                 *pst;       
SuId                suId;      
EgtUEvnt            *egtUEvnt;  
#endif
{
   Buffer *mBuf = NULLP;

   TRC3(cmPkEgtEguStaCfm);

   /* allocate memory for the buffer */
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
                "cmPkEgtEguStaCfm: Allocating memory for buffer failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

      RETVALUE(RFAILED);
   } /* end of if allocating memory fails */

   egtUEvnt->event = EVTEGTUSTACFM;
   /* in case of loose coupling pack the whole event */
   if (pst->selector == EGT_SEL_LC)
   {
      CMCHKPKLOG(cmPkEgtUEvnt, egtUEvnt, mBuf, EEGTXXX, pst);
      SPutSBuf(pst->region, pst->pool, (Data* )egtUEvnt,
                        (sizeof(EgtUEvnt)));
   } /* end of if selector is loosely coupled */

   /* in case of lightweight loose coupling pack only the pointer */
   else if (pst->selector == EGT_SEL_LWLC)
   {
      CMCHKPKLOG(cmPkPtr, ( (PTR)egtUEvnt), mBuf, EEGTXXX, pst);
   } /* end of if selector is lightweight loosely coupled */

   CMCHKPKLOG(cmPkSuId, suId, mBuf, EEGTXXX, pst);

   pst->event = EVTEGTUSTACFM;

   RETVALUE(SPstTsk(pst, mBuf));
} /* end of cmPkEgtEguStaCfm */


/***********************************************************
*
*     Func   : cmUnpkEgtEguStaCfm
*
*     Desc   : EgtEguStaCfm
*              @brief Unpacking of primitive EgtEguStaCfm
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgtEguStaCfm
(
EgtEguStaCfm        func,          
Pst                 *pst,         
Buffer              *mBuf        
)
#else
PUBLIC S16 cmUnpkEgtEguStaCfm(func, pst, mBuf)
EgtEguStaCfm        func;           
Pst                 *pst;          
Buffer              *mBuf;        
#endif
{
   SuId      suId = 0;
   EgtUEvnt  *egtUEvnt = NULLP;
   Mem       memInfo;
   S16       retValue = 0;

   TRC3(cmUnpkEgtEguStaCfm);

   cmMemset( (U8 *)&memInfo, 0, sizeof(Mem));

   memInfo.region = pst->region;
   memInfo.pool = pst->pool;

   CMCHKUNPKLOG(cmUnpkSuId, &suId, mBuf, EEGTXXX, pst);

   /* in case of loose coupling pack the whole event */
   if (pst->selector == EGT_SEL_LC)
   {
      if ((retValue = SGetSBuf(memInfo.region, memInfo.pool, (Data **)&egtUEvnt, sizeof(EgtUEvnt))) != ROK)
      {
         
         /*-- egt_c_001.main_9: free memory in case of Error --*/
         SPutMsg(mBuf); 
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
                "cmUnpkEgtEguStaCfm() : Allocating memory for buffer failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

           RETVALUE(retValue);
      }

      cmMemset( (U8 *)egtUEvnt, 0, sizeof(EgtUEvnt));

      if((retValue = cmUnpkEgtUEvnt((egtUEvnt), mBuf, pst)) != ROK )
      {

         SPutMsg(mBuf); 
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                      __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
                      "cmUnpkEgtEguStaCfm: Allocating memory for message failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(RFAILED);
      } /* end of if allocating memory fails */
   } /* end of if selector is loosely coupled */

   /* in case of lightweight loose coupling pack only the pointer */
   else if (pst->selector == EGT_SEL_LWLC)
   {
      CMCHKUNPKLOG(cmUnpkPtr, ( (PTR *)&egtUEvnt), mBuf, EEGTXXX, pst);
   } /* end of if selector is lightweight loosely coupled */

   /* after unpacking all the elements, release the buffer memory */
   SPutMsg(mBuf);

   /* call the function after unpacking */
   RETVALUE( (*func)(pst, suId, egtUEvnt));
} /* end of cmUnpkEgtEguStaCfm */


/***********************************************************
*
*     Func   : cmPkEgtEguUStaInd
*
*     Desc   : EgtEguUStaInd
*              @brief Packing of primitive EgtEguUStaInd
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgtEguUStaInd
(
Pst                 *pst,             
SuId                suId,            
EgtUEvnt            *egtUEvnt       
)
#else
PUBLIC S16 cmPkEgtEguUStaInd(pst, suId, egtUEvnt)
Pst                 *pst;            
SuId                suId;           
EgtUEvnt            *egtUEvnt;     
#endif
{
   Buffer *mBuf = NULLP;

   TRC3(cmPkEgtEguUStaInd);

   /* allocate memory for the buffer */
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
                "cmPkEgtEguUStaInd: Allocating memory for buffer failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

      RETVALUE(RFAILED);
   } /* end of if allocating memory fails */

   egtUEvnt->event = EVTEGTUUSTAIND;
   /* in case of loose coupling pack the whole event */
   if (pst->selector == EGT_SEL_LC)
   {
      CMCHKPKLOG(cmPkEgtUEvnt, egtUEvnt, mBuf, EEGTXXX, pst);
      SPutSBuf(pst->region, pst->pool, (Data* )egtUEvnt,
                        (sizeof(EgtUEvnt)));
   } /* end of if selector is loosely coupled */

   /* in case of lightweight loose coupling pack only the pointer */
   else if (pst->selector == EGT_SEL_LWLC)
   {
      CMCHKPKLOG(cmPkPtr, ( (PTR)egtUEvnt), mBuf, EEGTXXX, pst);
   } /* end of if selector is lightweight loosely coupled */

   CMCHKPKLOG(cmPkSuId, suId, mBuf, EEGTXXX, pst);

   pst->event = EVTEGTUUSTAIND;

   RETVALUE(SPstTsk(pst, mBuf));
} /* end of cmPkEgtEguUStaInd */


/***********************************************************
*
*     Func   : cmUnpkEgtEguUStaInd
*
*     Desc   : EgtEguUStaInd
*              @brief Unpacking of primitive EgtEguUStaInd
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgtEguUStaInd
(
EgtEguUStaInd       func,         
Pst                 *pst,        
Buffer              *mBuf       
)
#else
PUBLIC S16 cmUnpkEgtEguUStaInd(func, pst, mBuf)
EgtEguUStaInd       func;         
Pst                 *pst;        
Buffer              *mBuf;      
#endif
{
   SuId      suId = 0;
   EgtUEvnt  *egtUEvnt = NULLP;
   Mem       memInfo;
   S16       retValue = 0;

   TRC3(cmUnpkEgtEguUStaInd);

   cmMemset( (U8 *)&memInfo, 0, sizeof(Mem));

   memInfo.region = pst->region;
   memInfo.pool = pst->pool;

   CMCHKUNPKLOG(cmUnpkSuId, &suId, mBuf, EEGTXXX, pst);

   /* in case of loose coupling pack the whole event */
   if (pst->selector == EGT_SEL_LC)
   {
      if ((retValue = SGetSBuf(memInfo.region, memInfo.pool, (Data **)&egtUEvnt, sizeof(EgtUEvnt))) != ROK)
      {
         /*-- egt_c_001.main_9: free memory in case of Error --*/
         SPutMsg(mBuf); 
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
                "cmUnpkEgtEguUStaInd() : Allocating memory for buffer failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

           RETVALUE(retValue);
      }

      cmMemset( (U8 *)egtUEvnt, 0, sizeof(EgtUEvnt));

      if((retValue = cmUnpkEgtUEvnt((egtUEvnt), mBuf, pst)) != ROK )
      {

         SPutMsg(mBuf); 
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                      __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
                      "cmUnpkEgtEguUStaInd: Allocating memory for message failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(RFAILED);
      } /* end of if selector is loosely coupled */
   }

   /* in case of lightweight loose coupling pack only the pointer */
   else if (pst->selector == EGT_SEL_LWLC)
   {
      CMCHKUNPKLOG(cmUnpkPtr, ( (PTR *)&egtUEvnt), mBuf, EEGTXXX, pst);
   } /* end of if selector is lightweight loosely coupled */

   /* after unpacking all the elements, release the buffer memory */
   SPutMsg(mBuf);

   /* call the function after unpacking */
   RETVALUE( (*func)(pst, suId, egtUEvnt));
} /* end of cmUnpkEgtEguUStaInd */


/***********************************************************
*
*     Func   : cmPkEgtEguErrInd
*
*     Desc   : EgtEguErrInd
*              @brief Packing of primitive EgtEguErrInd
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgtEguErrInd
(
Pst                 *pst,           
SuId                suId,          
EgtUEvnt            *egtUEvnt     
)
#else
PUBLIC S16 cmPkEgtEguErrInd(pst, suId, egtUEvnt)
Pst                 *pst;          
SuId                suId;         
EgtUEvnt            *egtUEvnt;   
#endif
{
   Buffer *mBuf = NULLP;

   TRC3(cmPkEgtEguErrInd);

   /* allocate memory for the buffer */
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
                "cmPkEgtEguErrInd: Allocating memory for buffer failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

      RETVALUE(RFAILED);
   } /* end of if allocating memory fails */

   egtUEvnt->event = EVTEGTUERRIND;
   /* in case of loose coupling pack the whole event */
   if (pst->selector == EGT_SEL_LC)
   {
      CMCHKPKLOG(cmPkEgtUEvnt, egtUEvnt, mBuf, EEGTXXX, pst);
      SPutSBuf(pst->region, pst->pool, (Data* )egtUEvnt,
                        (sizeof(EgtUEvnt)));
   } /* end of if selector is loosely coupled */

   /* in case of lightweight loose coupling pack only the pointer */
   else if (pst->selector == EGT_SEL_LWLC)
   {
      CMCHKPKLOG(cmPkPtr, ( (PTR)egtUEvnt), mBuf, EEGTXXX, pst);
   } /* end of if selector is lightweight loosely coupled */

   CMCHKPKLOG(cmPkSuId, suId, mBuf, EEGTXXX, pst);

   pst->event = EVTEGTUERRIND;

   RETVALUE(SPstTsk(pst, mBuf));
} /* end of cmPkEgtEguErrInd */


/***********************************************************
*
*     Func   : cmUnpkEgtEguErrInd
*
*     Desc   : EgtEguErrInd
*              @brief Unpacking of primitive EgtEguErrInd
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgtEguErrInd
(
EgtEguErrInd        func,       
Pst                 *pst,      
Buffer              *mBuf     
)
#else
PUBLIC S16 cmUnpkEgtEguErrInd(func, pst, mBuf)
EgtEguErrInd        func;       
Pst                 *pst;      
Buffer              *mBuf;    
#endif
{
   SuId      suId = 0;
   EgtUEvnt  *egtUEvnt = NULLP;
   Mem       memInfo;
   S16       retValue = 0;

   TRC3(cmUnpkEgtEguErrInd);

   cmMemset( (U8 *)&memInfo, 0, sizeof(Mem));

   /* in case of loose coupling pack the whole event */
   if (pst->selector == EGT_SEL_LC)
   {
      /*-- egt_c_001.main_9: assign region & pool before memory allocation
       *  so that allocation is done properly --*/
      memInfo.region = pst->region;
      memInfo.pool = pst->pool;

      /* nk -- added a memory failure check */
      if ( (retValue = SGetSBuf(memInfo.region, memInfo.pool, (Data **)&egtUEvnt, sizeof(EgtUEvnt))) != ROK)
      {
         SPutMsg(mBuf); 
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
               "cmUnpkEgtEguErrInd: Allocating memory for message failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

         RETVALUE(RFAILED);
      } /* end of if allocating memory fails */

      cmMemset( (U8 *)egtUEvnt, 0, sizeof(EgtUEvnt));

      CMCHKUNPKLOG(cmUnpkSuId, &suId, mBuf, EEGTXXX, pst);

      if((retValue = cmUnpkEgtUEvnt((egtUEvnt), mBuf, pst)) != ROK )
      {

         SPutMsg(mBuf); 
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
               "cmUnpkEgtEguErrInd: Allocating memory for message failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(RFAILED);
      }
   } /* end of if selector is loosely coupled */

   /* in case of lightweight loose coupling pack only the pointer */
   else if (pst->selector == EGT_SEL_LWLC)
   {
      CMCHKUNPKLOG(cmUnpkPtr, ( (PTR *)&egtUEvnt), mBuf, EEGTXXX, pst);
   } /* end of if selector is lightweight loosely coupled */

   /* after unpacking all the elements, release the buffer memory */
   SPutMsg(mBuf);

   /* call the function after unpacking */
   RETVALUE( (*func)(pst, suId, egtUEvnt));
} /* end of cmUnpkEgtEguErrInd */


/***********************************************************
*
*     Func   : cmPkEgUExtHdr
*
*     Desc   : EgUExtHdr
*              @brief Packing of structure EgUExtHdr
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgUExtHdr
(
EgUExtHdr           *pkStruct,    
Buffer              *mBuf        
)
#else
PUBLIC S16 cmPkEgUExtHdr(pkStruct, mBuf)
EgUExtHdr           *pkStruct;     
Buffer              *mBuf;        
#endif
{
   TRC3(cmPkEgUExtHdr);

   CMCHKPK(cmPkTknU16, &pkStruct->udpPort, mBuf);
   CMCHKPK(cmPkTknU16, &pkStruct->pdcpNmb, mBuf);

   RETVALUE(ROK);
} /* end of cmPkEgUExtHdr */


/***********************************************************
*
*     Func   : cmUnpkEgUExtHdr
*
*     Desc   : EgUExtHdr
*              @brief Unpacking of structure EgUExtHdr
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgUExtHdr
(
EgUExtHdr           *unpkStruct,   
Buffer              *mBuf         
)
#else
PUBLIC S16 cmUnpkEgUExtHdr(unpkStruct, mBuf)
EgUExtHdr           *unpkStruct;   
Buffer              *mBuf;        
#endif
{
   TRC3(cmUnpkEgUExtHdr);

   CMCHKUNPK(cmUnpkTknU16, &unpkStruct->pdcpNmb, mBuf);
   CMCHKUNPK(cmUnpkTknU16, &unpkStruct->udpPort, mBuf);

   /* return success */
   RETVALUE(ROK);
} /* end of cmUnpkEgUExtHdr */


/***********************************************************
*
*     Func   : cmPkEgUMsgHdr
*
*     Desc   : EgUMsgHdr
*              @brief Packing of structure EgUMsgHdr
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgUMsgHdr
(
EgUMsgHdr           *pkStruct,       
Buffer              *mBuf           
)
#else
PUBLIC S16 cmPkEgUMsgHdr(pkStruct, mBuf)
EgUMsgHdr           *pkStruct;     
Buffer              *mBuf;        
#endif
{
   TRC3(cmPkEgUMsgHdr);

   CMCHKPK(cmPkTknU8,     &pkStruct->nPduNmb, mBuf);
   /*-- egt_c_001.main_8: handle packing for 32 bit Seq Num --*/
   CMCHKPK(cmPkTknU32,    &pkStruct->seqNumber, mBuf);
   CMCHKPK(cmPkEgUExtHdr, &pkStruct->extHdr, mBuf);
   CMCHKPK(SPkU32,        pkStruct->teId, mBuf);
   CMCHKPK(SPkU8,         pkStruct->msgType, mBuf);

   RETVALUE(ROK);
} /* end of cmPkEgUMsgHdr */


/***********************************************************
*
*     Func   : cmUnpkEgUMsgHdr
*
*     Desc   : EgUMsgHdr
*              @brief Unpacking of structure EgUMsgHdr
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgUMsgHdr
(
EgUMsgHdr           *unpkStruct,    
Buffer              *mBuf          
)
#else
PUBLIC S16 cmUnpkEgUMsgHdr(unpkStruct,mBuf)
EgUMsgHdr           *unpkStruct;  
Buffer              *mBuf;       
#endif
{
   TRC3(cmUnpkEgUMsgHdr);

   CMCHKUNPK(SUnpkU8,         &unpkStruct->msgType, mBuf);
   CMCHKUNPK(SUnpkU32,        &unpkStruct->teId, mBuf);
   CMCHKUNPK(cmUnpkEgUExtHdr, &unpkStruct->extHdr, mBuf);
   /*-- egt_c_001.main_8: handle packing for 32 bit Seq Num --*/
   CMCHKUNPK(cmUnpkTknU32,    &unpkStruct->seqNumber, mBuf);
   CMCHKUNPK(cmUnpkTknU8,     &unpkStruct->nPduNmb, mBuf);

   /* return success */
   RETVALUE(ROK);
} /* end of cmUnpkEgUMsgHdr */



/*
*
*    Fun:     cmPkEgIeList
*
*    Desc:    pack the IE list into buffer
*
*    Ret:     ROK  -ok
*             Return value of sub methods
*
*    Notes:   The packing of the IE list will be done as shown
*             the following manner.
*
* ----------------------------------------------------------------
* |   1   |   2   |   3   |   4   |  5    |  6    |   7   |   8  |
* ----------------------------------------------------------------
*             |                               |
*            -------------------------------- |
*             |   2.1   |   2.2   |   2.3   | |
*            -------------------------------- |
*                                           --------------------------------
*                                            |   6.1   |   6.2   |   6.3   |
*                                           --------------------------------
*                                                           |
*                                                      --------------------------
*                                                       |   6.2.1   |   6.2.2   |
*                                                      --------------------------
*
*             As shown in the above example, the main IE list (level zero) is having
*             2, 6 are grouped IEs and at level one 6.2 is again a grouped IE
*             which is having two elements 6.2.1 and 6.2.2
*             The packing of the IE list will start from the last of the list
*             at any level.  If any of the node is a grouped IE, then the child
*             list will be packed first after which the grouped IE will be packed.
*
*             NOTE: The value in () is the count of the IE list
*
*             Step 1:  IE 8 is not grouped so pack into buffer.
*             ---------
*             |   8   |
*             ---------
*
*             Step 2:  IE 7 is not grouped so pack into buffer.
*             ------------------
*             |   8   |    7   |
*             ------------------
*
*             Step 3:  IE 6 is grouped so pack the child IE list first
*
*                 Step 3.1:  IE 6.3 is not a grouped IE so pack into buffer
*             -----------------------------
*             |   8   |    7   |    6.3   |
*             -----------------------------
*
*                 Step 3.2:  IE 6.2 is again a grouped IE so pack the child
*                            IE list
*
*                     Step 3.2.1:  IE 6.2.2 is not a grouped IE so pack into buffer
*             ------------------------------------------
*             |   8   |    7   |    6.3   |    6.2.2   |
*             ------------------------------------------
*
*                     Step 3.2.2:  IE 6.2.1 is not a grouped IE so pack into buffer
*             -------------------------------------------------------
*             |   8   |    7   |    6.3   |    6.2.2   |    6.2.1   |
*             -------------------------------------------------------
*
*                 Step 3.3:  Since IE 6.2 is a grouped IE so pack into buffer
*             -----------------------------------------------------------------------------
*             |   8   |    7   |    6.3   |    6.2.2   |    6.2.1   |    (2)   |    6.2   |
*             -----------------------------------------------------------------------------
*
*                 Step 3.4:  IE 6.1 is not a grouped IE so pack into buffer
*             -----------------------------------------------------------------------------
*             |   8   |    7   |    6.3   |    6.2.2   |    6.2.1   |    (2)   |    6.2   |
*             -----------------------------------------------------------------------------
*             |   6.1   |
*             -----------
*
*             Step 5:  Since IE 6 is a grouped IE pack into buffer.
*             -----------------------------------------------------------------------------
*             |   8   |    7   |    6.3   |    6.2.2   |    6.2.1   |    (2)   |    6.2   |
*             -----------------------------------------------------------------------------
*             |   6.1   |   (3)   |   6   |
*             -----------------------------
*
*             Step 5:  IE 5 is not grouped so pack into buffer.
*             -----------------------------------------------------------------------------
*             |   8   |    7   |    6.3   |    6.2.2   |    6.2.1   |    (2)   |    6.2   |
*             -----------------------------------------------------------------------------
*             |   6.1   |   (3)   |   6   |   5   |
*             -------------------------------------
*
*             Step 6:  IE 4 is not grouped so pack into buffer.
*             -----------------------------------------------------------------------------
*             |   8   |    7   |    6.3   |    6.2.2   |    6.2.1   |    (2)   |    6.2   |
*             -----------------------------------------------------------------------------
*             |   6.1   |   (3)   |   6   |   5   |   4   |
*             ---------------------------------------------
*
*             Step 6:  IE 3 is not grouped so pack into buffer.
*             -----------------------------------------------------------------------------
*             |   8   |    7   |    6.3   |    6.2.2   |    6.2.1   |    (2)   |    6.2   |
*             -----------------------------------------------------------------------------
*             |   6.1   |   (3)   |   6   |   5   |   4   |   3   |
*             -----------------------------------------------------
*
*             Step 7:  IE 2 is again a grouped IE so pack the
*                      child IE list
*
*                 Step 7.1:  IE 2.3 is not a grouped IE so pack into buffer
*             -----------------------------------------------------------------------------
*             |   8   |    7   |    6.3   |    6.2.2   |    6.2.1   |    (2)   |    6.2   |
*             -----------------------------------------------------------------------------
*             |   6.1   |   (3)   |   6   |   5   |   4   |   3   |    2.3   |
*             ----------------------------------------------------------------
*
*                 Step 7.2:  IE 2.2 is not a grouped IE so pack into buffer
*             -----------------------------------------------------------------------------
*             |   8   |    7   |    6.3   |    6.2.2   |    6.2.1   |    (2)   |    6.2   |
*             -----------------------------------------------------------------------------
*             |   6.1   |   (3)   |   6   |   5   |   4   |   3   |    2.3   |    2.2   |
*             ---------------------------------------------------------------------------
*
*                 Step 7.3:  IE 2.1 is not a grouped IE so pack into buffer
*             -----------------------------------------------------------------------------
*             |   8   |    7   |    6.3   |    6.2.2   |    6.2.1   |    (2)   |    6.2   |
*             -----------------------------------------------------------------------------
*             |   6.1   |   (3)   |   6   |   5   |   4   |   3   |    2.3   |    2.2   |
*             ---------------------------------------------------------------------------
*             |    2.1   |
*             ------------
*
*             Step 9:  Since IE 2 is a grouped IE pack into buffer.
*             -----------------------------------------------------------------------------
*             |   8   |    7   |    6.3   |    6.2.2   |    6.2.1   |    (2)   |    6.2   |
*             -----------------------------------------------------------------------------
*             |   6.1   |   (3)   |   6   |   5   |   4   |   3   |    2.3   |    2.2   |
*             ---------------------------------------------------------------------------
*             |    2.1   |   (3)   |   2   |
*             ------------------------------
*
*             Step 10:  IE 1 is not a grouped IE pack into buffer.
*             -----------------------------------------------------------------------------
*             |   8   |    7   |    6.3   |    6.2.2   |    6.2.1   |    (2)   |    6.2   |
*             -----------------------------------------------------------------------------
*             |   6.1   |   (3)   |   6   |   5   |   4   |   3   |    2.3   |    2.2   |
*             ---------------------------------------------------------------------------
*             |    2.1   |   (3)   |   2   |   1   |   (8)   |
*             ------------------------------------------------
*
*    File:    egt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkEgUIeList
(
CmLListCp   *param, 
Buffer      *mBuf, 
CmMemListCp *memCp
)
#else
PUBLIC S16 cmPkEgUIeList(param, mBuf, memCp)
CmLListCp   *param;
Buffer      *mBuf;  
CmMemListCp *memCp;
#endif
{
   /* this is used to hold the temporary node address */
   CmLList *node = NULLP;

   /* this is used to hold the temporary IE */
   EgUIe *egIe = NULLP;

   /* in a loop pack the IEs from last to the first.
    * This is because to preserve the position of IEs
    * in the packed buffer.  So while unpacking the
    * first IE in the list will be unpacked first.
    */
   for (egIe = (EgUIe* ) CM_LLIST_LAST_NODE(param, node);
        egIe != NULLP;
        egIe = (EgUIe* ) CM_LLIST_PREV_NODE(param, node))
   {
      /* pack the IE (if grouped, after packing the child IEs) */
      CMCHKPK(cmPkEgUIe, egIe, mBuf);
   } /* end of loop to pack all the IEs */

   /* pack the number of IEs in the list at last so that
    * the count will be un packed at first while unpacking
    * and the buffer will be unpacked based on the count
    * only.
    */
   CMCHKPK(SPkU32, param->count, mBuf);

   /* return success */
   RETVALUE(ROK);
} /*end of cmPkEgUIeList */



/*
*
*    Fun:     cmUnpkEgIeList
*
*    Desc:    Unpack the IE list from buffer
*
*    Ret:     ROK  -ok
*             Return value of sub methods
*
*    Notes:   The unpacking of the IE list will be done as shown
*             the following manner.  If the packed buffer seems to
*             be as shown, then unpacking will be done as specified
*             in the below steps:
*
*             -----------------------------------------------------------------------------
*             |   8   |    7   |    6.3   |    6.2.2   |    6.2.1   |    (2)   |    6.2   |
*             -----------------------------------------------------------------------------
*             |   6.1   |   (3)   |   6   |   5   |   4   |   3   |    2.3   |    2.2   |
*             ---------------------------------------------------------------------------
*             |    2.1   |   (3)   |   2   |   1   |   (8)   |
*             ------------------------------------------------
*
*             Step 1:  Unpack the count of IEs in the IE list.
*                      In a loop unpack 8 IEs.
*
*                 Step 1.1:  Unpack IE 1, since it is not a grouped IE,
*                            append into IE list at level zero
* ---------
* |   1   |
* ---------
*
*                 Step 1.2:  Unpack IE 2, since it is a grouped IE, unpack
*                            the 3 child IEs from the buffer.
* -----------------
* |   1   |   2   |
* -----------------
*
*                     Step 1.2.1:  Unpack IE 2.1, since it is not a grouped IE
*                                  append to the list at level one
* -----------------
* |   1   |   2   |
* -----------------
*             |
*            ------------
*             |   2.1   |
*            ------------
*
*                     Step 1.2.2:  Unpack IE 2.2, since it is not a grouped IE
*                                  append to the list at level one
* -----------------
* |   1   |   2   |
* -----------------
*             |
*            ----------------------
*             |   2.1   |   2.2   |
*            ----------------------
*
*                     Step 1.2.3:  Unpack IE 2.3, since it is not a grouped IE
*                                  append to the list at level one
* -----------------
* |   1   |   2   |
* -----------------
*             |
*            --------------------------------
*             |   2.1   |   2.2   |   2.3   |
*            --------------------------------
*
*                 Step 1.3:  Unpack IE 3, since it is not a grouped IE
*                            append to the list at level zero
* -------------------------
* |   1   |   2   |   3   |
* -------------------------
*             |
*            --------------------------------
*             |   2.1   |   2.2   |   2.3   |
*            --------------------------------
*
*                 Step 1.4:  Unpack IE 4, since it is not a grouped IE
*                            append to the list at level zero
* ---------------------------------
* |   1   |   2   |   3   |   4   |
* ---------------------------------
*             |
*            --------------------------------
*             |   2.1   |   2.2   |   2.3   |
*            --------------------------------
*
*                 Step 1.5:  Unpack IE 5, since it is not a grouped IE
*                            append to the list at level zero
* -----------------------------------------
* |   1   |   2   |   3   |   4   |   5   |
* -----------------------------------------
*             |
*            --------------------------------
*             |   2.1   |   2.2   |   2.3   |
*            --------------------------------
*
*                 Step 1.6:  Unpack IE 6, and since it is a grouped IE
*                            unpack the remaining 3 child IEs from buffer
* -------------------------------------------------
* |   1   |   2   |   3   |   4   |  5    |  6    |
* -------------------------------------------------
*             |
*            --------------------------------
*             |   2.1   |   2.2   |   2.3   |
*            --------------------------------
*
*                     Step 1.6.1:  Unpack IE 6.1, since it is not a grouped IE
*                                  append to the list at level one
* -------------------------------------------------
* |   1   |   2   |   3   |   4   |  5    |  6    |
* -------------------------------------------------
*             |                               |
*            -------------------------------- |
*             |   2.1   |   2.2   |   2.3   | |
*            -------------------------------- |
*                                           ------------
*                                            |   6.1   |
*                                           ------------
*
*                     Step 1.6.2:  Unpack IE 6.2, since it is a grouped IE
*                                  unpack the 2 child IEs from buffer
* -------------------------------------------------
* |   1   |   2   |   3   |   4   |  5    |  6    |
* -------------------------------------------------
*             |                               |
*            -------------------------------- |
*             |   2.1   |   2.2   |   2.3   | |
*            -------------------------------- |
*                                           ----------------------
*                                            |   6.1   |   6.2   |
*                                           ----------------------
*
*                         Step 1.6.2.1:  Unpack IE 6.2.1, since it is not a grouped IE
*                                        append to IE list at level 2.
* -------------------------------------------------
* |   1   |   2   |   3   |   4   |  5    |  6    |
* -------------------------------------------------
*             |                               |
*            -------------------------------- |
*             |   2.1   |   2.2   |   2.3   | |
*            -------------------------------- |
*                                           ----------------------
*                                            |   6.1   |   6.2   |
*                                           ----------------------
*                                                           |
*                                                      --------------
*                                                       |   6.2.1   |
*                                                      --------------
*
*                         Step 1.6.2.2:  Unpack IE 6.2.2, since it is not a grouped IE
*                                        append to IE list at level 2.
* -------------------------------------------------
* |   1   |   2   |   3   |   4   |  5    |  6    |
* -------------------------------------------------
*             |                               |
*            -------------------------------- |
*             |   2.1   |   2.2   |   2.3   | |
*            -------------------------------- |
*                                           ----------------------
*                                            |   6.1   |   6.2   |
*                                           ----------------------
*                                                           |
*                                                      --------------------------
*                                                       |   6.2.1   |   6.2.1   |
*                                                      --------------------------
*
*                     Step 1.6.3:  Unpack IE 6.3, since it is not a grouped IE
*                                  append to IE list at level 1
* -------------------------------------------------
* |   1   |   2   |   3   |   4   |  5    |  6    |
* -------------------------------------------------
*             |                               |
*            -------------------------------- |
*             |   2.1   |   2.2   |   2.3   | |
*            -------------------------------- |
*                                           --------------------------------
*                                            |   6.1   |   6.2   |   6.3   |
*                                           --------------------------------
*                                                           |
*                                                      --------------------------
*                                                       |   6.2.1   |   6.2.2   |
*                                                      --------------------------
*
*                 Step 1.7:  Unpack IE 7, and since it is not a grouped IE
*                            append to IE list at level 0.
* ---------------------------------------------------------
* |   1   |   2   |   3   |   4   |  5    |  6    |   7   |
* ---------------------------------------------------------
*             |                               |
*            -------------------------------- |
*             |   2.1   |   2.2   |   2.3   | |
*            -------------------------------- |
*                                           --------------------------------
*                                            |   6.1   |   6.2   |   6.3   |
*                                           --------------------------------
*                                                           |
*                                                      --------------------------
*                                                       |   6.2.1   |   6.2.2   |
*                                                      --------------------------
*
*                 Step 1.8:  Unpack IE 8, and since it is not a grouped IE
*                            append to IE list at level 0.
* ----------------------------------------------------------------
* |   1   |   2   |   3   |   4   |  5    |  6    |   7   |   8  |
* ----------------------------------------------------------------
*             |                               |
*            -------------------------------- |
*             |   2.1   |   2.2   |   2.3   | |
*            -------------------------------- |
*                                           --------------------------------
*                                            |   6.1   |   6.2   |   6.3   |
*                                           --------------------------------
*                                                           |
*                                                      --------------------------
*                                                       |   6.2.1   |   6.2.2   |
*                                                      --------------------------
*
*    File:    egt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkEgUIeList
(
CmLListCp   *param,  
Buffer      *mBuf,  
CmMemListCp *memCp 
)
#else
PUBLIC S16 cmUnpkEgUIeList(param, mBuf, memCp)
CmLListCp   *param;  
Buffer      *mBuf;  
CmMemListCp *memCp; 
#endif
{
   /* this is used to hold the temporary IE */
   EgUIe *egIe = NULLP;

   /* this is used to hold the temporary count of the IE list */
   U32 listCount = 0;

   TRC3(cmUnpkEgUIeList)

   /* pack the number of IEs in the list at last so that
    * the count will be un packed at first while unpacking
    * and the buffer will be unpacked based on the count
    * only.
    */
   CMCHKUNPK(SUnpkU32, &listCount, mBuf);

   /* in a loop unpack the number of IEs from the buffer */
   for (; listCount > 0; listCount--)
   {
      /* allocate memory for the IE structure from
       * the global control block
       */
      if (cmGetMem(memCp, sizeof(EgUIe), (Ptr* )&egIe) != ROK)
      {
         RETVALUE(EGT_ERR_MEM_ALLOC_FAILED);
      } /* end of if allocating memory for the ie fails */

      /* initialize the node address of the new IE */
      egIe->node.node = (PTR) egIe;

      /* unpack the IE from buffer */
      if (cmUnpkEgUIe(egIe, mBuf) != ROK) 
         RETVALUE(RFAILED);

      /* append the IE to the tail of the list */
      cmLListAdd2Tail(param, &egIe->node);

   } /* end of loop to pack all the IEs */

   /* return success */
   RETVALUE(ROK);
} /*end of cmUnpkEgIeList */


/***********************************************************
*
*     Func   : cmPkEgUMsg
*
*     Desc   : EgUMsg
*              @brief Packing of structure EgUMsg
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgUMsg
(
EgUMsg              *pkStruct,      
Buffer              *mBuf          
)
#else
PUBLIC S16 cmPkEgUMsg(pkStruct, mBuf)
EgUMsg              *pkStruct;      
Buffer              *mBuf;         
#endif
{
   S16      retValue = 0;
   TRC3(cmPkEgUMsg);

   switch (pkStruct->msgHdr.msgType)
   {
      case EGT_GTPU_MSG_GPDU:
      {
         MsgLen tpduLen = 0;

         /* get the T-PDU length */
         SFndLenMsg(pkStruct->u.mBuf, &tpduLen);

         /* in case of G-PDU append the buffer to the mBuf */
         if (SCatMsg(mBuf, pkStruct->u.mBuf, M2M1) != ROK)
         {
#if (ERRCLASS & ERRCLS_ADD_RES)
            SLogError(ENTNC, INSTNC, ENTNC,
                      __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
                      "cmPkEgUMsg: Packing the T-PDU failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

            RETVALUE(RFAILED);
         } /* end of if packing fails */

         /* pack the length of T-PDU appended */
         CMCHKPK(cmPkMsgLen, tpduLen, mBuf);

         break;
      } /* end of case G-PDU */

      default:
      {
         if ( (retValue = cmPkEgUIeList(&pkStruct->u.egIeList, mBuf, &pkStruct->memCp)) != ROK)
         {
#if (ERRCLASS & ERRCLS_ADD_RES)
            SLogError(ENTNC, INSTNC, ENTNC,
                      __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
                      "cmPkEgUMsg: Packing the IE List failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

            RETVALUE(RFAILED);
         } /* end of if packing fails */

         break;
      } /* end of case default */
   } /* end of switch case */

   CMCHKPK(cmPkEgUMsgHdr, &pkStruct->msgHdr, mBuf);
   CMCHKPK(cmPkCmTptAddr, &pkStruct->remAddr, mBuf);
   CMCHKPK(cmPkCmTptAddr, &pkStruct->srcAddr, mBuf);
   CMCHKPK(SPkU32,        pkStruct->lclTeid, mBuf);

   RETVALUE(ROK);
} /* end of cmPkEgUMsg */


/***********************************************************
*
*     Func   : cmUnpkEgUMsg
*
*     Desc   : EgUMsg
*              @brief Unpacking of structure EgUMsg
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgUMsg
(
EgUMsg              *unpkStruct,     
Buffer              *mBuf,          
Mem                  memInfo
)
#else
PUBLIC S16 cmUnpkEgUMsg(unpkStruct,mBuf,memInfo)
EgUMsg              *unpkStruct;  
Buffer              *mBuf;         
Mem                  memInfo;
#endif
{
   S16    retValue = 0;
   MsgLen msgLen =0;
   U8 tmpByte = 0;
   TRC3(cmUnpkEgUMsg);

   CMCHKUNPK(SUnpkU32,         &unpkStruct->lclTeid, mBuf);
   CMCHKUNPK(cmUnpkCmTptAddr,  &unpkStruct->srcAddr, mBuf);
   CMCHKUNPK(cmUnpkCmTptAddr,  &unpkStruct->remAddr, mBuf);
   CMCHKUNPK(cmUnpkEgUMsgHdr,  &unpkStruct->msgHdr, mBuf);

   switch (unpkStruct->msgHdr.msgType)
   {
      case EGT_GTPU_MSG_GPDU:
      {
         MsgLen tpduLen = 0;

         /* unpack the length of T-PDU appended */
         CMCHKUNPK(cmUnpkMsgLen, &tpduLen, mBuf);
         SFndLenMsg(mBuf, &msgLen);
         if(tpduLen <= msgLen)
         {
            if (SGetMsg(memInfo.region, memInfo.pool, &(unpkStruct->u.mBuf)) != ROK) 
            {
#if (ERRCLASS & ERRCLS_ADD_RES)
               SLogError(ENTNC, INSTNC, ENTNC,
                     __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
                     "cmUnpkEgUMsg: Unpacking the T-PDU failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
               RETVALUE(RFAILED);
            }
            while(tpduLen--)
            {
               SRemPreMsg(&tmpByte, mBuf);
               SAddPstMsg(tmpByte, unpkStruct->u.mBuf);
            }
         }
         /*-- eg003.201 : In case msgLen is 0, just pack mBuf pointer --*/ 
         else if ( 0 == msgLen )
         {
            if (SGetMsg(memInfo.region, memInfo.pool, &(unpkStruct->u.mBuf)) != ROK) 
            {
#if (ERRCLASS & ERRCLS_ADD_RES)
               SLogError(ENTNC, INSTNC, ENTNC,
                     __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
                     "cmUnpkEgUMsg: Unpacking the T-PDU failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
               RETVALUE(RFAILED);
            }
         }
         else
         {
            if ( (retValue = SSegMsg(mBuf, 0, &(unpkStruct->u.mBuf))) != ROK)
            {
#if (ERRCLASS & ERRCLS_ADD_RES)
               SLogError(ENTNC, INSTNC, ENTNC,
                     __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
                     "cmUnpkEgUMsg: Unpacking the T-PDU failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

               /*-- egt_c_001.main_9: free memory in case of Error --*/
               if(unpkStruct->u.mBuf != NULLP)
               {   
                  SPutMsg(unpkStruct->u.mBuf); /*kwork fix: */
               }
               RETVALUE(RFAILED);
            } /* end of if packing fails */
         }

         break;
      } /* end of case G-PDU */

      default:
      {
         if ( (retValue = cmUnpkEgUIeList(&unpkStruct->u.egIeList, mBuf, &unpkStruct->memCp)) != ROK)
         {
#if (ERRCLASS & ERRCLS_ADD_RES)
            SLogError(ENTNC, INSTNC, ENTNC,
                      __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
                      "cmUnpkEgUMsg: Unpacking the IE List failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

            RETVALUE(RFAILED);
         } /* end of if packing fails */

         break;
      } /* end of case default */
   } /* end of switch case */

   /* return success */
   RETVALUE(ROK);
} /* end of cmUnpkEgUMsg */


/***********************************************************
*
*     Func   : cmPkEgUIpAddr
*
*     Desc   : EgUIpAddr
*              @brief Packing of structure EgUIpAddr
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgUIpAddr
(
EgUIpAddr           *pkStruct,     
Buffer              *mBuf         
)
#else
PUBLIC S16 cmPkEgUIpAddr(pkStruct, mBuf)
EgUIpAddr           *pkStruct;   
Buffer              *mBuf;      
#endif
{
   TRC3(cmPkEgUIpAddr);

   switch (pkStruct->addrType)
   {
      case CM_IPV4ADDR_TYPE:
      {
         CMCHKPK(SPkU32,     pkStruct->u.ipv4, mBuf);
         break;
      } /* end of case CM_IPV4ADDR_TYPE */

#ifdef EG_IPV6_SUPPORTED
      case CM_IPV6ADDR_TYPE:
      {
        S16 cnt = 0;

        for (; cnt < 16; cnt++)
        {
             CMCHKPK(SPkU8,   pkStruct->u.ipv6[cnt], mBuf);
        } /* end of loop */

         break;
      } /* end of case CM_IPV6ADDR_TYPE */
#endif /* EG_IPV6_SUPPORTED */

      default:
      {
         /*-- egt_c_001.main_7: handling pack/unpack error --*/
         /* RETVALUE(RFAILED); --*/
      } /* end of case default */
   } /* end of switch case */

   CMCHKPK(SPkU8, pkStruct->addrType, mBuf);

   RETVALUE(ROK);
} /* end of cmPkEgUIpAddr */


/***********************************************************
*
*     Func   : cmUnpkEgUIpAddr
*
*     Desc   : EgUIpAddr
*              @brief Unpacking of structure EgUIpAddr
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgUIpAddr
(
EgUIpAddr           *unpkStruct,    
Buffer              *mBuf          
)
#else
PUBLIC S16 cmUnpkEgUIpAddr( unpkStruct, mBuf)
EgUIpAddr           *unpkStruct;    
Buffer              *mBuf;         
#endif
{
   TRC3(cmUnpkEgUIpAddr);

   CMCHKUNPK(SUnpkU8, &unpkStruct->addrType, mBuf);

   switch (unpkStruct->addrType)
   {
      case CM_IPV4ADDR_TYPE:
      {
         CMCHKUNPK(SUnpkU32,      &unpkStruct->u.ipv4, mBuf);
         break;
      } /* end of case CM_IPV4ADDR_TYPE */

#ifdef EG_IPV6_SUPPORTED
      case CM_IPV6ADDR_TYPE:
      {
         S32 cnt = 15;

         for (; cnt >= 0; cnt--)
         {
            CMCHKUNPK(SUnpkU8,    &unpkStruct->u.ipv6[cnt], mBuf);
         } /* end of loop */

         break;
      } /* end of case CM_IPV6ADDR_TYPE */
#endif /* EG_IPV6_SUPPORTED */

      default:
      {
         /*-- egt_c_001.main_7: handling pack/unpack error --*/
         /*-- RETVALUE(RFAILED); --*/
      } /* end of case default */
   } /* end of switch case */

   /* return success */
   RETVALUE(ROK);
} /* end of cmUnpkEgUIpAddr */


/***********************************************************
*
*     Func   : cmPkEgUExtHdrTypeLst
*
*     Desc   : EgUExtHdrTypeLst
*              @brief Packing of structure EgUExtHdrTypeLst
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgUExtHdrTypeLst
(
EgUExtHdrTypeLst    *pkStruct,    
Buffer              *mBuf        
)
#else
PUBLIC S16 cmPkEgUExtHdrTypeLst(pkStruct, mBuf)
EgUExtHdrTypeLst    *pkStruct;     
Buffer              *mBuf;        
#endif
{
   U8 cnt = 0;
   /* egt_c_001.main_13: Variable added to check for max ext type while unpacking */
   S32 extHdrCnt = 0;

   TRC3(cmPkEgUExtHdrTypeLst);
   /* egt_c_001.main_13: Pack only upto the max ext type supported */   
   if(pkStruct->noOfExtHdrs > EGT_U_MAX_EXT_TYPES)
   {
      extHdrCnt = EGT_U_MAX_EXT_TYPES;
   }
   else
   {
      extHdrCnt = pkStruct->noOfExtHdrs;
   }
   for (; cnt < extHdrCnt; cnt++)
   {
      CMCHKPK(SPkU8, pkStruct->extType[cnt], mBuf);
   } /* end of loop */

   CMCHKPK(SPkU8,    pkStruct->noOfExtHdrs, mBuf);

   RETVALUE(ROK);
} /* end of cmPkEgUExtHdrTypeLst */


/***********************************************************
*
*     Func   : cmUnpkEgUExtHdrTypeLst
*
*     Desc   : EgUExtHdrTypeLst
*              @brief Unpacking of structure EgUExtHdrTypeLst
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgUExtHdrTypeLst
(
EgUExtHdrTypeLst    *unpkStruct,      
Buffer              *mBuf            
)
#else
PUBLIC S16 cmUnpkEgUExtHdrTypeLst(unpkStruct, mBuf)
EgUExtHdrTypeLst    *unpkStruct;     
Buffer              *mBuf;          
#endif
{
   /*egt_c_001.main_11 :Klocwork fix,modified S16 to U8*/
   S32 cnt = 0;
   /* egt_c_001.main_13: Variable added to check for max ext type while unpacking */
   S32 extHdrCnt = 0;

   TRC3(cmUnpkEgUExtHdrTypeLst);

   CMCHKUNPK(SUnpkU8,    &unpkStruct->noOfExtHdrs, mBuf);

   /* egt_c_001.main_13: Unpack only upto the max ext type supported */ 
   if(unpkStruct->noOfExtHdrs > EGT_U_MAX_EXT_TYPES)
   {
      extHdrCnt = EGT_U_MAX_EXT_TYPES;
   }
   else
   {
      extHdrCnt = unpkStruct->noOfExtHdrs;
   }
   for (cnt = extHdrCnt-1; cnt >= 0; cnt--)
   {
      CMCHKUNPK(SUnpkU8, &unpkStruct->extType[cnt], mBuf);
   } /* end of loop */

   /* return success */
   RETVALUE(ROK);
} /* end of cmUnpkEgUExtHdrTypeLst */


/***********************************************************
*
*     Func   : cmPkEgUIe
*
*     Desc   : EgUIe
*              @brief Packing of structure EgUIe
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgUIe
(
EgUIe               *pkStruct,   
Buffer              *mBuf       
)
#else
PUBLIC S16 cmPkEgUIe(pkStruct, mBuf)
EgUIe               *pkStruct;   
Buffer              *mBuf;      
#endif
{

   TRC3(cmPkEgUIe);

   switch (pkStruct->dataType)
   {
      case EG_UNSIGNED_8:
      {
         CMCHKPK(SPkU8, pkStruct->t.valUnSgnd8, mBuf);

         break;
      } /* end of case */

      case EG_UNSIGNED_32:
      {
         CMCHKPK(SPkU32, pkStruct->t.valUnSgnd32, mBuf);

         break;
      } /* end of case */

      case EG_PVT_EXTN:
      {
         CMCHKPK(cmPkEgPvtExt, &pkStruct->t.pvtExt, mBuf);

         break;
      } /* end of case */

      case EG_IP_ADDR:
      {
         CMCHKPK(cmPkEgUIpAddr, &pkStruct->t.ipAddr, mBuf);

         break;
      } /* end of case */

      case EG_EXT_HDR_TYPE_LST:
      {
         CMCHKPK(cmPkEgUExtHdrTypeLst, &pkStruct->t.extHdrTypeLst, mBuf);

         break;
      } /* end of case */

      default:
      {
         RETVALUE(RFAILED);
      } /* end of case */
   } /* end of switch case */

   CMCHKPK(SPkU8,                      pkStruct->dataType, mBuf);
   CMCHKPK(SPkU8,                      pkStruct->ieType, mBuf);

   RETVALUE(ROK);
} /* end of cmPkEgUIe */


/***********************************************************
*
*     Func   : cmUnpkEgUIe
*
*     Desc   : EgUIe
*              @brief Unpacking of structure EgUIe
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgUIe
(
EgUIe               *unpkStruct,  
Buffer              *mBuf        
)
#else
PUBLIC S16 cmUnpkEgUIe(unpkStruct, mBuf)
EgUIe               *unpkStruct;   
Buffer              *mBuf;        
#endif
{

   TRC3(cmUnpkEgUIe);

   CMCHKUNPK(SUnpkU8,                      &unpkStruct->ieType, mBuf);
   CMCHKUNPK(SUnpkU8,                      &unpkStruct->dataType, mBuf);

   switch (unpkStruct->dataType)
   {
      case EG_UNSIGNED_8:
      {
         CMCHKUNPK(SUnpkU8,                &unpkStruct->t.valUnSgnd8, mBuf);

         break;
      } /* end of case */

      case EG_UNSIGNED_32:
      {
         CMCHKUNPK(SUnpkU32,               &unpkStruct->t.valUnSgnd32, mBuf);

         break;
      } /* end of case */

      case EG_PVT_EXTN:
      {
         CMCHKUNPK(cmUnpkEgPvtExt,         &unpkStruct->t.pvtExt, mBuf);

         break;
      } /* end of case */

      case EG_IP_ADDR:
      {
         CMCHKUNPK(cmUnpkEgUIpAddr,        &unpkStruct->t.ipAddr, mBuf);

         break;
      } /* end of case */

      case EG_EXT_HDR_TYPE_LST:
      {
         CMCHKUNPK(cmUnpkEgUExtHdrTypeLst, &unpkStruct->t.extHdrTypeLst, mBuf);

         break;
      } /* end of case */

      default:
      {
         RETVALUE(RFAILED);
      } /* end of case */
   } /* end of switch case */

   /* return success */
   RETVALUE(ROK);
} /* end of cmUnpkEgUIe */


/***********************************************************
*
*     Func   : cmPkEgUStatus
*
*     Desc   : EgUStatus
*              @brief Packing of structure EgUStatus
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgUStatus
(
EgUStatus           *pkStruct,      
Buffer              *mBuf          
)
#else
PUBLIC S16 cmPkEgUStatus(pkStruct, mBuf)
EgUStatus           *pkStruct;     
Buffer              *mBuf;        
#endif
{
   TRC3(cmPkEgUStatus);

   CMCHKPK(cmPkCmTptAddr, &pkStruct->srcAddr, mBuf);
   CMCHKPK(cmPkCmTptAddr, &pkStruct->dstAddr, mBuf);
   CMCHKPK(cmPkCmStatus,  &pkStruct->cfmStatus, mBuf);

   RETVALUE(ROK);
} /* end of cmPkEgUStatus */


/***********************************************************
*
*     Func   : cmUnpkEgUStatus
*
*     Desc   : EgUStatus
*              @brief Unpacking of structure EgUStatus
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgUStatus
(
EgUStatus           *unpkStruct,     
Buffer              *mBuf           
)
#else
PUBLIC S16 cmUnpkEgUStatus(unpkStruct, mBuf)
EgUStatus           *unpkStruct;   
Buffer              *mBuf;        
#endif
{
   TRC3(cmUnpkEgUStatus);

   CMCHKUNPK(cmUnpkCmStatus,  &unpkStruct->cfmStatus, mBuf);
   CMCHKUNPK(cmUnpkCmTptAddr, &unpkStruct->dstAddr, mBuf);
   CMCHKUNPK(cmUnpkCmTptAddr, &unpkStruct->srcAddr, mBuf);

   /* return success */
   RETVALUE(ROK);
} /* end of cmUnpkEgUStatus */


/***********************************************************
*
*     Func   : cmPkEgUErrEvnt
*
*     Desc   : EgUErrEvnt
*              @brief Packing of structure EgUErrEvnt
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgUErrEvnt
(
EgUErrEvnt          *pkStruct,     
Buffer              *mBuf         
)
#else
PUBLIC S16 cmPkEgUErrEvnt(pkStruct, mBuf)
EgUErrEvnt          *pkStruct;   
Buffer              *mBuf;      
#endif
{
   TRC3(cmPkEgUErrEvnt);

   CMCHKPK(SPkU32,          pkStruct->localTeid, mBuf);
   CMCHKPK(SPkU32,          pkStruct->remTeid, mBuf);
   CMCHKPK(SPkU8,           (U8)pkStruct->errCause, mBuf);
   CMCHKPK(cmPkCmTptAddr,   &pkStruct->srcAddr, mBuf);
   CMCHKPK(cmPkCmTptAddr,   &pkStruct->dstAddr, mBuf);
   CMCHKPK(SPkU32,          pkStruct->diagInfo, mBuf);
   CMCHKPK(SPkU8,           pkStruct->failedIeType, mBuf);
   CMCHKPK(SPkU8,           pkStruct->failedMsgType, mBuf);

   RETVALUE(ROK);
} /* end of cmPkEgUErrEvnt */


/***********************************************************
*
*     Func   : cmUnpkEgUErrEvnt
*
*     Desc   : EgUErrEvnt
*              @brief Unpacking of structure EgUErrEvnt
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgUErrEvnt
(
EgUErrEvnt          *unpkStruct,      
Buffer              *mBuf            
)
#else
PUBLIC S16 cmUnpkEgUErrEvnt(unpkStruct, mBuf)
EgUErrEvnt          *unpkStruct;    
Buffer              *mBuf;         
#endif
{
   TRC3(cmUnpkEgUErrEvnt);

   CMCHKUNPK(SUnpkU8,           &unpkStruct->failedMsgType, mBuf);
   CMCHKUNPK(SUnpkU8,           &unpkStruct->failedIeType, mBuf);
   CMCHKUNPK(SUnpkU32,          &unpkStruct->diagInfo, mBuf);
   CMCHKUNPK(cmUnpkCmTptAddr,   &unpkStruct->dstAddr, mBuf);
   CMCHKUNPK(cmUnpkCmTptAddr,   &unpkStruct->srcAddr, mBuf);
   CMCHKUNPK(SUnpkU8,           (U8*)&unpkStruct->errCause, mBuf);
   CMCHKUNPK(SUnpkU32,          &unpkStruct->remTeid, mBuf);
   CMCHKUNPK(SUnpkU32,          &unpkStruct->localTeid, mBuf);

   /* return success */
   RETVALUE(ROK);
} /* end of cmUnpkEgUErrEvnt */


/***********************************************************
*
*     Func   : cmPkEgUTnlMgmt
*
*     Desc   : EgUTnlMgmt
*              @brief Packing of structure EgUTnlMgmt
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgUTnlMgmt
(
EgUTnlMgmt          *pkStruct,    
Buffer              *mBuf        
)
#else
PUBLIC S16 cmPkEgUTnlMgmt(pkStruct, mBuf)
EgUTnlMgmt          *pkStruct;  
Buffer              *mBuf;     
#endif
{
   TRC3(cmPkEgUTnlMgmt);

   CMCHKPK(SPkU8,           pkStruct->action, mBuf);
   CMCHKPK(SPkU8,           pkStruct->intfType, mBuf);
   CMCHKPK(SPkU8,           pkStruct->dscp, mBuf);
   CMCHKPK(cmPkBool,        pkStruct->reOrderPres, mBuf);
/* egt_c_001.main_6 Adding tunnelType to the Packing function */
#ifdef EGTP_U_REL_9
   CMCHKPK(SPkU8,           pkStruct->tunnelType, mBuf);
#endif
   CMCHKPK(SPkU32,          pkStruct->teId, mBuf);
   CMCHKPK(SPkU8,           pkStruct->reordAlgo, mBuf);
   CMCHKPK(SPkU16,          pkStruct->expSeqNmb, mBuf);
   CMCHKPK(cmPkCmTptAddr,   &pkStruct->srcAddr, mBuf);
   CMCHKPK(cmPkCmTptAddr,   &pkStruct->dstIpAddr, mBuf);
   CMCHKPK(cmPkCmTptAddr,   &pkStruct->frmDstIpAddr, mBuf);
   CMCHKPK(SPkU16,          pkStruct->maxTPduSize, mBuf);
   CMCHKPK(cmPkCmStatus,    &pkStruct->cfmStatus, mBuf);

   RETVALUE(ROK);
} /* end of cmPkEgUTnlMgmt */


/***********************************************************
*
*     Func   : cmUnpkEgUTnlMgmt
*
*     Desc   : EgUTnlMgmt
*              @brief Unpacking of structure EgUTnlMgmt
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgUTnlMgmt
(
EgUTnlMgmt          *unpkStruct,  
Buffer              *mBuf        
)
#else
PUBLIC S16 cmUnpkEgUTnlMgmt(unpkStruct, mBuf)
EgUTnlMgmt          *unpkStruct; 
Buffer              *mBuf;        
#endif
{
   TRC3(cmUnpkEgUTnlMgmt);

   CMCHKUNPK(cmUnpkCmStatus,    &unpkStruct->cfmStatus, mBuf);
   CMCHKUNPK(SUnpkU16,          &unpkStruct->maxTPduSize, mBuf);
   CMCHKUNPK(cmUnpkCmTptAddr,   &unpkStruct->frmDstIpAddr, mBuf);
   CMCHKUNPK(cmUnpkCmTptAddr,   &unpkStruct->dstIpAddr, mBuf);
   CMCHKUNPK(cmUnpkCmTptAddr,   &unpkStruct->srcAddr, mBuf);
   CMCHKUNPK(SUnpkU16,          &unpkStruct->expSeqNmb, mBuf);
   CMCHKUNPK(SUnpkU8,           &unpkStruct->reordAlgo, mBuf);
   CMCHKUNPK(SUnpkU32,          &unpkStruct->teId, mBuf);
/* egt_c_001.main_6 Adding tunnelType to the Unpacking function*/
#ifdef EGTP_U_REL_9
   CMCHKUNPK(SUnpkU8,           &unpkStruct->tunnelType, mBuf);
#endif
   CMCHKUNPK(cmUnpkBool,        &unpkStruct->reOrderPres, mBuf);
   CMCHKUNPK(SUnpkU8,           &unpkStruct->dscp, mBuf);
   CMCHKUNPK(SUnpkU8,           &unpkStruct->intfType, mBuf);
   CMCHKUNPK(SUnpkU8,           &unpkStruct->action, mBuf);

   /* return success */
   RETVALUE(ROK);
} /* end of cmUnpkEgUTnlMgmt */


/***********************************************************
*
*     Func   : cmPkEgtUEvnt
*
*     Desc   : EgtUEvnt
*              @brief Packing of structure EgtUEvnt
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgtUEvnt
(
EgtUEvnt            *pkStruct,    
Buffer              *mBuf        
)
#else
PUBLIC S16 cmPkEgtUEvnt(pkStruct, mBuf)
EgtUEvnt            *pkStruct;  
Buffer              *mBuf;     
#endif
{
   S16  retValue = 0;

   TRC3(cmPkEgtUEvnt);

   switch (pkStruct->event)
   {
      case EVTEGTUDATREQ:
      {

         CMCHKPK(cmPkEgUMsg, pkStruct->u.egMsg, mBuf);

         if ( (retValue = EgUUtilDeAllocGmMsg(&pkStruct->u.egMsg)) != ROK)
         {
#if (ERRCLASS & ERRCLS_ADD_RES)
            SLogError(ENTNC, INSTNC, 0,
                         __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
                         "cmPkEgtUEvnt: Deallocating memory for egMsg after packing failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

            RETVALUE(RFAILED);
         } /* end of if allocating memory fails */

         break;
      } /* end of case data req / ind */

      case EVTEGTUDATIND:
      {
         EgUMsg *egMsg = pkStruct->u.egMsg;
         EgUMsg *tempEgMsg = NULLP;

         do
         {
            CMCHKPK(cmPkEgUMsg,   egMsg, mBuf);

            /* store the next pointer before freeing */
            tempEgMsg = egMsg->next;

            if ( (retValue = EgUUtilDeAllocGmMsg(&egMsg)) != ROK)
            {
#if (ERRCLASS & ERRCLS_ADD_RES)
               SLogError(ENTNC, INSTNC, 0,
                         __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
                         "cmPkEgtUEvnt: Deallocating memory for egMsg after packing failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

               RETVALUE(RFAILED);
            } /* end of if allocating memory fails */

            /* restore the next message */
            egMsg = tempEgMsg;
         } while (egMsg);/* end of while */

         break;
      } /* end of case data req / ind */

      case EVTEGTULCLTNLMGMTREQ:
      case EVTEGTULCLTNLMGMTCFM:
      {
         CMCHKPK(cmPkEgUTnlMgmt,  &pkStruct->u.tnlMgmt, mBuf);

         break;
      } /* end of case tunnel mgmt req / cfm */

      case EVTEGTUSTAREQ:
      case EVTEGTUSTACFM:
      {
         CMCHKPK(cmPkEgUStatus,   &pkStruct->u.status, mBuf);

         break;
      } /* end of case status req / cfm */

      case EVTEGTUUSTAIND:
      {
         CMCHKPK(cmPkEgUStatus,   &pkStruct->u.uStaInd, mBuf);

         break;
      } /* end of case status req / cfm */

      case EVTEGTUERRIND:
      {
         CMCHKPK(cmPkEgUErrEvnt,  &pkStruct->u.errInd, mBuf);

         break;
      } /* end of case status req / cfm */

      default:
      {
         break;
      } /* end of case status req / cfm */
   } /* end of struct */

   CMCHKPK(SPkU8,                 pkStruct->event, mBuf);

   RETVALUE(ROK);
} /* end of cmPkEgtUEvnt */


/***********************************************************
*
*     Func   : cmUnpkEgtUEvnt
*
*     Desc   : EgtUEvnt
*              @brief Unpacking of structure EgtUEvnt
*
*     Ret    : ROK - in case of success
*              RFAILED - in case of failure
*
*     Notes  : None
*
*     File   : egt.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgtUEvnt
(
EgtUEvnt            *unpkStruct,     
Buffer              *mBuf,          
Pst                 *pst
)
#else
PUBLIC S16 cmUnpkEgtUEvnt(unpkStruct, mBuf, pst)
EgtUEvnt            *unpkStruct;   
Buffer              *mBuf;        
Pst                 *pst;
#endif
{
   S16   retValue = 0;
   Mem       memInfo;

   TRC3(cmUnpkEgtUEvnt);

   memInfo.region = pst->region;
   memInfo.pool = pst->pool;

   CMCHKUNPK(SUnpkU8, &unpkStruct->event, mBuf);

   switch (unpkStruct->event)
   {
      case EVTEGTUDATREQ:
      {
         /* allocate memory for the EGTP-U message */
         if ( (retValue = EgUUtilAllocGmMsg(&unpkStruct->u.egMsg, &memInfo)) != ROK)
         {
#if (ERRCLASS & ERRCLS_ADD_RES)
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                         __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
                         "cmUnpkEgtUEvnt: Allocating memory for message failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

            RETVALUE(RFAILED);
         } /* end of if allocating memory fails */

         /*-- egt_c_001.main_9: Dealloc Egmsg on Unpack failure --*/
         if ( cmUnpkEgUMsg(unpkStruct->u.egMsg, mBuf, memInfo) != ROK)
         {
            EgUUtilDeAllocGmMsg(&unpkStruct->u.egMsg);
            RETVALUE(RFAILED);
         } 

         break;
      } /* end of case data req */

      case EVTEGTUDATIND:
      {
         /* this will be of use to iterate through the buffer
          * and unpack all the messages that are present
          */
         MsgLen bufLen = 0;
         EgUMsg *egMsg = NULLP;
         EgUMsg *nextEgMsg = NULLP;

         /* get the buffer length */
         SFndLenMsg(mBuf, &bufLen);

         if (bufLen)
         {
            /* allocate memory for the EGTP-U message */
            if ( (retValue = EgUUtilAllocGmMsg(&egMsg, &memInfo)) != ROK)
            {
#if (ERRCLASS & ERRCLS_ADD_RES)
               SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                         __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
                         "cmUnpkEgtUEvnt: Allocating memory for message failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

               RETVALUE(RFAILED);
            } /* end of if allocating memory fails */

            /* store the parent pointer */
            unpkStruct->u.egMsg = egMsg;
            egMsg->next = NULLP;

            /* In a loop, unpack the eGTP-U message and then
             * if the message length is valid unpack the next
             * message
             */
            while (bufLen)
            {
               /* unpack the message */
               cmUnpkEgUMsg(egMsg, mBuf, memInfo);

               /* get the remaining length left in the buffer */
               SFndLenMsg(mBuf, &bufLen);

               /* if the buffer length is valid it means that the
                * buffer contains next message.  The buffer length will
                * always be in multiples of EgUMsg
                */
               if (bufLen)
               {
                  if ( (retValue = EgUUtilAllocGmMsg(&nextEgMsg, &memInfo)) != ROK)
                  {
#if (ERRCLASS & ERRCLS_ADD_RES)
                     SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                               __FILE__, __LINE__, ERRCLS_ADD_RES, EEGTXXX, ERRZERO,
                               "cmUnpkEgtUEvnt: Allocating memory for message failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

                     RETVALUE(RFAILED);
                  } /* end of if allocating memory fails */

                  /* link the two messages */
                  nextEgMsg->next = egMsg;

                  /* move to next node */
                  egMsg = nextEgMsg;
                  unpkStruct->u.egMsg = nextEgMsg;
               } /* end of if bytes are left over */
            } while (bufLen);/* end of while */
         } /* end of if buffer is valid */

         break;
      } /* end of case data req / ind */

      case EVTEGTULCLTNLMGMTREQ:
      case EVTEGTULCLTNLMGMTCFM:
      {
         CMCHKUNPK(cmUnpkEgUTnlMgmt,  &unpkStruct->u.tnlMgmt, mBuf);

         break;
      } /* end of case tunnel mgmt req / cfm */

      case EVTEGTUSTAREQ:
      case EVTEGTUSTACFM:
      {
         CMCHKUNPK(cmUnpkEgUStatus,   &unpkStruct->u.status, mBuf);

         break;
      } /* end of case status req / cfm */

      case EVTEGTUUSTAIND:
      {
         CMCHKUNPK(cmUnpkEgUStatus,   &unpkStruct->u.uStaInd, mBuf);

         break;
      } /* end of case status req / cfm */

      case EVTEGTUERRIND:
      {
         CMCHKUNPK(cmUnpkEgUErrEvnt,  &unpkStruct->u.errInd, mBuf);

         break;
      } /* end of case status req / cfm */

      default:
      {
         break;
      } /* end of case status req / cfm */
   } /* end of struct */

   /* return success */
   RETVALUE(ROK);
} /* end of cmUnpkEgtUEvnt */

#endif /* end of EGTP_U */

#endif


/********************************************************************30**

         End of file:     egt.c@@/main/14 - Wed Jun  5 16:46:20 2013

*********************************************************************31*/

/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/

/********************************************************************60**

        Revision history:

*********************************************************************61*/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---                 kc      1. initial release.
/main/2      egt_c_001.main_1    rss     1. Egtpu release changes
/main/3      ---                 akulkarni Header updation for eGTP-U release
/main/4      egt_c_001.main_3    rss     1. Multithreaded performance changes 
                                            gaurded under SS_MT_CB flag.
                                         2. EGTP_C Path management functionality
                                            is introduced
/main/5      egt_c_001.main_4    rk      1. Packing and unpacking ip4/ip6 address 
                                            properly for F-TEID
                                         2. Unpacking the suId in cmUnpkEgtEguDatInd
/main/6      ---      pmacharla         Initial for eGTP release 2.1
/main/7        egt_c_001.main_6   asaurabh 1. Adding tunnelType to the Packing function 
                                         2. Adding tunnelType to the Unpacking function
/main/8      ---      egt_c_001.main_7    psingh  1. Removed cmMemset in cmUnpkEgtEguDatReq, which
                                            was causing SEGFAULT in loose coupling
                                         2. Handling for Invalid IPaddr type
/main/9      ---      egt_c_001.main_8    psingh  1. Removed cmMemset in cmUnpkEgtEguDatReq, which
/main/10     ---      egt_c_001.main_9    psingh  1. corrected byte pack/unpack for PAA IE
                                                  2. Memory leak corrections
/main/11     ---      egt_c_001.main_10   psingh  1. Memory leak corrections for Negative tests
/main/12     ---      egt_c_001.main_11   asaurabh 1. Klocwork fix,modified S16 to U8
                                                   2. Klocwork fix,modified to S32
                                                   3. Added for S2B and S2B.
/main/13        ---      egt_c_001.main_12   asaurabh 1. Unpack pMsgPres
                                                   2. pack pMsgPres
/main/14     ---      egt_c_001.main_13   shpandey 1. check for no. of extension headers in unpacking of EgUExtHdrTypeLst
*********************************************************************91*/
