/********************************************************************20**
  
        Name:    LTE PDCP Interface  
    
        Type:    C file
  
        Desc:    This file contains the pack/unpack functions for the
                 data structures at PJU Interface.
 
        File:    pju.c

        Sid:      pju.c@@/main/5 - Fri Sep  2 19:27:53 2011
  
        Prg:     Dinesh 
  
*********************************************************************21*/

/* header include files (.h) */
  
#include "envopt.h"             /* Environment options */  
#include "envdep.h"             /* Environment dependent */
#include "envind.h"             /* Environment independent */
#include "gen.h"                /* General */
#include "ssi.h"                /* System services interface */
#include "cm_lte.h"             /* Common LTE header file */
#include "cm_llist.h"           /* Linked list header file */
#include "cm_tkns.h"            /* Common tokens header file */
#include "cm_hash.h"            /* Hash List header file */
#include "pju.h"                /* PJU Interface header file */



/* header/extern include files (.x) */

#include "gen.x"                /* General */
#include "ssi.x"                /* System services interface */
#include "cm_lib.x"             /* Common lib header file */
#include "cm_hash.x"            /* Hash List header file */
#include "cm_llist.x"           /* Linked list header file */
#include "cm_tkns.x"            /* Common tokens header file */
#include "cm_lte.x"             /* Common LTE header file */
#include "pju.x"                /* PJU Interface header file */

#include "ss_queue.h"
#include "ss_queue.x"
#include "ss_task.x"
#include "ss_msg.x"
#if (defined(LCPJU) || defined(LWLCPJU))

#ifdef __cplusplus
EXTERN "C" {
#endif /* __cplusplus */
#ifdef SS_RBUF
/* Cache Opt Changes */
PUBLIC S16 bcIcpuRouteMsg ARGS((U8 msgType, Buffer *buf, Pst* pst, U8 procId, U8 priority));
EXTERN void bcIcpuFlushBuffer(Buffer *buf);
#endif

#ifdef ANSI
PUBLIC S16 cmPkPjuBndReq
(
Pst* pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 cmPkPjuBndReq(pst, suId, spId)
Pst* pst;
SuId suId;
SpId spId;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkPjuBndReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU001, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU002, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU003, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTPJUBNDREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkPjuBndReq
(
PjuBndReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjuBndReq(func, pst, mBuf)
PjuBndReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   SuId suId;
   
   TRC3(cmUnpkPjuBndReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU004, (ErrVal)0, "Unpacking failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU005, (ErrVal)0, "Unpacking failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, spId));
}

#ifdef ANSI
PUBLIC S16 cmPkPjuBndCfm
(
Pst* pst,
SuId suId,
U8 status
)
#else
PUBLIC S16 cmPkPjuBndCfm(pst, suId, status)
Pst* pst;
SuId suId;
U8 status;
#endif
{
   Buffer *mBuf = NULLP;
   U8 reg;
   TRC3(cmPkPjuBndCfm)

   reg = pst->region;

   if (SGetMsg(reg, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU006, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SPkU8(status, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU007, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU008, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTPJUBNDCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkPjuBndCfm
(
PjuBndCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjuBndCfm(func, pst, mBuf)
PjuBndCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   U8 status;
   
   TRC3(cmUnpkPjuBndCfm)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU009, (ErrVal)0, "Unpacking failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkU8(&status, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU010, (ErrVal)0, "Unpacking failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, status));
}

#ifdef ANSI
PUBLIC S16 cmPkPjuUbndReq
(
Pst* pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 cmPkPjuUbndReq(pst, spId, reason)
Pst* pst;
SpId spId;
Reason reason;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkPjuUbndReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU011, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SPkS16(reason, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU012, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU013, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTPJUUBNDREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkPjuUbndReq
(
PjuUbndReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjuUbndReq(func, pst, mBuf)
PjuUbndReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   Reason reason;
   
   TRC3(cmUnpkPjuUbndReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU014, (ErrVal)0, "Unpacking failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkS16(&reason, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU015, (ErrVal)0, "Unpacking failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, reason));
}

#ifdef FLAT_BUFFER_OPT
#ifdef ANSI
PUBLIC S16 cmPkPjuDatReqFB
(
Pst* pst,
SpId spId,
CmLtePdcpId * pdcpId,
PjuSduId sduId,
FlatBuffer *buff
)
#else
PUBLIC S16 cmPkPjuDatReqFB(pst, spId, pdcpId, sduId, buff)
Pst* pst;
SpId spId;
CmLtePdcpId * pdcpId;
PjuSduId sduId;
FlatBuffer *buff;
#endif
{
   Buffer *mBuf = NULLP;
   MsgLen msgLen = 0;
   TRC3(cmPkPjuDatReqFB)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU016, (ErrVal)0, "Packing failed");
#endif
      /* pju_c_001.main_3 - Free the existing buffer */
      SPutMsg((Buffer*)buff); 
      RETVALUE(RFAILED);
   }
   if (pst->selector == PJU_SEL_LC) {
      if (SFndLenMsg((Buffer*)buff, &msgLen) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)EPJU017, (ErrVal)0, "Packing failed");
#endif
         SPutMsg((Buffer*)buff);
      /* pju_c_001.main_3 - Memory leak fix */
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      if (SCatMsg(mBuf, (Buffer*)buff, M1M2) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)EPJU018, (ErrVal)0, "Packing failed");
#endif
         SPutMsg((Buffer*)buff);
      /* pju_c_001.main_3 - Memory leak fix */
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      SPutMsg((Buffer*)buff);
      CMCHKPK(SPkS16, msgLen, mBuf);

   }
   if (SPkU32(sduId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU020, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector == PJU_SEL_LC) {
      if (cmPkLtePdcpId(pdcpId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)EPJU021, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }

   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU023, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) EVTPJUDATREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}
#endif

#ifdef ANSI
PUBLIC S16 cmPkPjuDatReq
(
Pst* pst,
SpId spId,
CmLtePdcpId * pdcpId,
PjuSduId sduId,
Buffer * buff
)
#else
PUBLIC S16 cmPkPjuDatReq(pst, spId, pdcpId, sduId, buff)
Pst* pst;
SpId spId;
CmLtePdcpId * pdcpId;
PjuSduId sduId;
Buffer * buff;
#endif
{
   S16 ret1;
   Buffer *mBuf = NULLP;
   MsgLen msgLen = 0;
   TRC3(cmPkPjuDatReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU016, (ErrVal)0, "Packing failed");
#endif
      /* pju_c_001.main_3 - Free the existing buffer */
      SPutMsg(buff); 
      RETVALUE(RFAILED);
   }
   if (pst->selector == PJU_SEL_LC) {
      if (SFndLenMsg(buff, &msgLen) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)EPJU017, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(buff);
      /* pju_c_001.main_3 - Memory leak fix */
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      if (SCatMsg(mBuf, buff, M1M2) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)EPJU018, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(buff);
      /* pju_c_001.main_3 - Memory leak fix */
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      SPutMsg(buff);
      CMCHKPK(SPkS16, msgLen, mBuf);

   }
   if (SPkU32(sduId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU020, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector == PJU_SEL_LC) {
      if (cmPkLtePdcpId(pdcpId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)EPJU021, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }

   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU023, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) EVTPJUDATREQ;
   ret1 = SPstTsk(pst,mBuf);
   RETVALUE(ret1);
}   
#ifdef SS_RBUF
#ifdef ANSI
PUBLIC S16 cmPkFpPjuDatReq
(
Pst* pst,
SpId spId,
CmLtePdcpId * pdcpId,
PjuSduId sduId,
Buffer * buff
)
#else
PUBLIC S16 cmPkFpPjuDatReq(pst, spId, pdcpId, sduId, buff)
Pst* pst;
SpId spId;
CmLtePdcpId * pdcpId;
PjuSduId sduId;
Buffer * buff;
#endif
{

   Buffer *dBuf = NULLP;
   PjuDatReqInfo *pjuDatReqInfo = NULLP;
   SsMsgInfo *mInfo = NULLP;
   TRC3(mPkWrPjuDatReq)
   mInfo = (SsMsgInfo*) buff->b_rptr;
   dBuf = mInfo->endptr;
   pjuDatReqInfo = ((PjuDatReqInfo *)(dBuf->b_wptr));
   pjuDatReqInfo->spId = spId;
   memcpy(&pjuDatReqInfo->pdcpId, pdcpId, sizeof(CmLtePdcpId));
   pjuDatReqInfo->sduId = sduId;
   dBuf->b_wptr += sizeof(PjuDatReqInfo);
   pst->event = (Event) EVTPJUDATREQ;
/* DL BATCH Send */
/* Cache Opt Changes */
   if( bcIcpuRouteMsg(SS_ICPU_DATA, buff, 0, 0, pst->prior) == ROK )
   {
      RETVALUE(ROK);
   }
   else
   {
     /* Icpu Batch Send Failed..Send via traditional Icpu send */
      RETVALUE(SPstTsk(pst,buff));
   }
}
#endif /* BRDCM */

#ifdef ANSI
PUBLIC S16 cmUnpkPjuDatReq
(
PjuDatReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjuDatReq(func, pst, mBuf)
PjuDatReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   
   SpId spId;
   CmLtePdcpId pdcpId;
   PjuSduId sduId;
   Buffer *buff = NULLP;
   
   TRC3(cmUnpkPjuDatReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU025, (ErrVal)0, "Unpacking failed");
#endif
      RETVALUE(RFAILED);
   }

   if (pst->selector == PJU_SEL_LC) 
   {
      if (cmUnpkLtePdcpId(&pdcpId, mBuf) != ROK)
      {
          SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)EPJU027, (ErrVal)0, "Unpacking failed");
#endif
         RETVALUE(RFAILED);
      }
   }
   if (SUnpkU32(&sduId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU028, (ErrVal)0, "Unpacking failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector == PJU_SEL_LC) {
      MsgLen msgLen, totalMsgLen;
      CMCHKUNPK(cmUnpkMsgLen, &msgLen, mBuf);
      if (SFndLenMsg(mBuf, &totalMsgLen) != ROK)
      {
         /* pju_c_001.main_3 - Memory leak fix */
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      /* pju_c_001.main_2 */
      if (SSegMsg(mBuf, (MsgLen)(totalMsgLen-msgLen), &buff) != ROK)
      {
         /* pju_c_001.main_3 - Memory leak fix */
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }  
   }
   SPutMsg(mBuf);

   RETVALUE((*func)(pst, spId, &pdcpId, sduId, buff));
}
#ifdef SS_RBUF
#ifdef ANSI
PUBLIC S16 cmUnpkFpPjuDatReq
(
PjuDatReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkFpPjuDatReq(func, pst, mBuf)
PjuDatReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   CmLtePdcpId pdcpId;
   PjuSduId sduId;
   Buffer *buff = mBuf;
   Buffer *dBuf;
   PjuDatReqInfo *pjuDatReqInfo = NULLP;
   SsMsgInfo *mInfo = NULLP;
   TRC3(cmUnpkPjuDatReq)

   mInfo = (SsMsgInfo*) buff->b_rptr;
   dBuf = (Buffer *)mInfo->endptr;
   dBuf->b_wptr -= sizeof(PjuDatReqInfo);
   pjuDatReqInfo = ((PjuDatReqInfo *)dBuf->b_wptr);
   spId = pjuDatReqInfo->spId;
   memcpy(&pdcpId, &pjuDatReqInfo->pdcpId, sizeof(CmLtePdcpId));
   sduId = pjuDatReqInfo->sduId;
   RETVALUE((*func)(pst, spId, &pdcpId, sduId, buff));
}
#endif /* SS_RBUF */

#ifdef ANSI
PUBLIC S16 cmPkPjuDatCfm
(
Pst* pst,
SuId suId,
CmLtePdcpId * pdcpId,
PjuDatCfmInfo * datCfm
)
#else
PUBLIC S16 cmPkPjuDatCfm(pst, suId, pdcpId, datCfm)
Pst* pst;
SuId suId;
CmLtePdcpId * pdcpId;
PjuDatCfmInfo * datCfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkPjuDatCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU029, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector == PJU_SEL_LC) {
      if (cmPkPjuDatCfmInfo(datCfm, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)EPJU030, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }

   if (pst->selector == PJU_SEL_LC) {
      if (cmPkLtePdcpId(pdcpId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)EPJU032, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }

   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU034, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) EVTPJUDATCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkPjuDatCfm
(
PjuDatCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjuDatCfm(func, pst, mBuf)
PjuDatCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16   ret1= ROK;
   SuId suId;
   CmLtePdcpId pdcpId;
   PjuDatCfmInfo datCfm;
   
   TRC3(cmUnpkPjuDatCfm)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU037, (ErrVal)0, "Unpacking failed");
#endif
      RETVALUE(RFAILED);
   }


   if (pst->selector == PJU_SEL_LC) 
   {

      if (cmUnpkLtePdcpId(&pdcpId, mBuf) != ROK)
      {
         SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)EPJU039, (ErrVal)0, "Unpacking failed");
#endif
         RETVALUE(RFAILED);
      }
   }

   if (pst->selector == PJU_SEL_LC) 
   {

      cmMemset((U8 *)(&datCfm), 0, sizeof(PjuDatCfmInfo));

      if (cmUnpkPjuDatCfmInfo(&datCfm, mBuf) != ROK) {
         SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)EPJU041, (ErrVal)0, "Unpacking failed");
#endif
         if (ret1 == RIGNORE)
         {
            RETVALUE(RIGNORE);
         }
         else
         {
            RETVALUE(RFAILED);
         }
      }
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, &pdcpId, &datCfm));
}

#ifdef ANSI
PUBLIC S16 cmPkPjuDatInd
(
Pst* pst,
SuId suId,
CmLtePdcpId * pdcpId,
Buffer * buff
)
#else
PUBLIC S16 cmPkPjuDatInd(pst, suId, pdcpId, buff)
Pst* pst;
SuId suId;
CmLtePdcpId * pdcpId;
Buffer * buff;
#endif
{
   Buffer *mBuf = NULLP;
   MsgLen msgLen = 0;
   TRC3(cmPkPjuDatInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU042, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(buff);
      RETVALUE(RFAILED);
   }
   if (pst->selector == PJU_SEL_LC) {
      if (SFndLenMsg(buff, &msgLen) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)EPJU043, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(buff);
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      if (SCatMsg(mBuf, buff, M1M2) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)EPJU044, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(buff);
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      SPutMsg(buff);
      CMCHKPK(SPkS16, msgLen, mBuf);

   }

   if (pst->selector == PJU_SEL_LC) {
      if (cmPkLtePdcpId(pdcpId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)EPJU046, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }

   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU048, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) EVTPJUDATIND;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkPjuDatInd
(
PjuDatInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjuDatInd(func, pst, mBuf)
PjuDatInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   CmLtePdcpId pdcpId;
   Buffer *buff = NULLP;
   
   TRC3(cmUnpkPjuDatInd)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU050, (ErrVal)0, "Unpacking failed");
#endif
      RETVALUE(RFAILED);
   }

   if (pst->selector == PJU_SEL_LC) 
   {
      if (cmUnpkLtePdcpId(&pdcpId, mBuf) != ROK)
      {
         SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)EPJU052, (ErrVal)0, "Unpacking failed");
#endif
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector == PJU_SEL_LC) {
      MsgLen msgLen, totalMsgLen;
      CMCHKUNPK(cmUnpkMsgLen, &msgLen, mBuf);
      if (SFndLenMsg(mBuf, &totalMsgLen) != ROK)
      {
         /* pju_c_001.main_3 - Memory leak fix */
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }  
      /* pju_c_001.main_2 */
      if (SSegMsg(mBuf, (S16)(totalMsgLen-msgLen), &buff) != ROK)
      {
         /* pju_c_001.main_3 - Memory leak fix */
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }

   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, &pdcpId, buff));
}

#ifdef SS_RBUF
#ifndef TENB_ACC 
#ifdef ANSI
PUBLIC S16 cmPkFpPjuDatInd
(
Pst* pst,
SuId suId,
CmLtePdcpId * pdcpId,
Buffer * buff
)
#else
PUBLIC S16 cmPkFpPjuDatInd(pst, suId, pdcpId, buff)
Pst* pst;
SuId suId;
CmLtePdcpId * pdcpId;
Buffer * buff;
#endif
{
   Buffer *mBuf = buff;
   Buffer *mHdrBuf = NULLP;
   PjuDatIndInfo *pjuDatIndInfo = NULLP;
   SsMsgInfo* minfo;
   Data *wptr;

   TRC3(cmPkFpPjuDatInd)

   if(pst->dstEnt == ENTPX)
   {
       minfo = (SsMsgInfo*)buff->b_rptr;
       wptr  = (Data*)&(minfo->pst);
       memcpy(wptr, &suId, sizeof(suId));
       memcpy((wptr + sizeof(suId)), pdcpId, sizeof(CmLtePdcpId));

       pst->event = (Event) EVTFPPJUDATIND;
       /* Batching UL */
       /* Cache Opt Changes */
       if((bcIcpuRouteMsg(SS_ICPU_DATA, mBuf, 0, 0, pst->prior) == ROK ))
       {
          RETVALUE(ROK);
       }
       else
       {
          SPutMsg(buff);
       }
   }
   else
   {
       if(SGetDBuf(pst->region, pst->pool, &mHdrBuf) != ROK)
       {
           RETVALUE(RFAILED);
       }

       /* Get the location from where we can write */
       pjuDatIndInfo = (PjuDatIndInfo*)mHdrBuf->b_wptr;

       /* Assign the dat indication header */
       memcpy(&pjuDatIndInfo->pdcpId, pdcpId, sizeof(CmLtePdcpId));
       pjuDatIndInfo->suId   = suId;

       /* Move the write pointer */
       mHdrBuf->b_wptr += sizeof(PjuDatIndInfo);

       /* Insert the new dbuf into the chain at the head */
       mHdrBuf->b_cont = buff->b_cont;
       buff->b_cont    = mHdrBuf;

       pst->event = (Event) EVTFPPJUDATIND;
       /* Batching UL */
       if((pst->dstEnt == ENTPX) && (bcIcpuRouteMsg(SS_ICPU_DATA, mBuf, 0, 0, pst->prior) == ROK ))
       {
          RETVALUE(ROK);
       }
       else
       {
           RETVALUE(SPstTsk(pst,mBuf));
       }
    }

    RETVALUE(ROK); /*warn_fix :: rohit */

}

#ifdef ANSI
PUBLIC S16 cmUnpkFpPjuDatInd
(
PjuDatInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkFpPjuDatInd(func, pst, mBuf)
PjuDatInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   CmLtePdcpId pdcpId;
   Buffer *mHdrBuf = NULLP;   
   PjuDatIndInfo *pjuDatInd = NULLP;
   SsMsgInfo* minfo;
   Data* rptr;

   TRC3(cmUnpkFpPjuDatInd)

   
   if(pst->dstEnt == ENTPX)
   {
       minfo = (SsMsgInfo*)mBuf->b_rptr;
       rptr  = (Data*)&(minfo->pst);
       memcpy(&suId,rptr, sizeof(suId));
       memcpy(&pdcpId, (rptr + sizeof(suId)), sizeof(CmLtePdcpId));

       RETVALUE((*func)(pst, suId, &pdcpId, mBuf));
   }
   else
   {
       /* Obtain the data indication hdr data buffer */
       mHdrBuf   = mBuf->b_cont;
       pjuDatInd =(PjuDatIndInfo *) mHdrBuf->b_rptr; 

       /* Copy the data indication header info */
       memcpy(&pdcpId, &pjuDatInd->pdcpId, sizeof(CmLtePdcpId));
       suId    = pjuDatInd->suId; 

       /* Delink the hdr buffer from the chain */
       mBuf->b_cont    = mHdrBuf->b_cont;
       mHdrBuf->b_cont = NULLP;

       SPutDBuf(pst->region, pst->pool, mHdrBuf);

       RETVALUE((*func)(pst, suId, &pdcpId, mBuf));
   }
}

#endif  /* TENB_ACC */
#endif  /* SS_RBUF */

#ifdef ANSI
PUBLIC S16 cmPkPjuStaInd
(
Pst* pst,
SuId suId,
CmLtePdcpId * pdcpId,
PjuStaIndInfo * staInd,
Buffer * buff
)
#else
PUBLIC S16 cmPkPjuStaInd(pst, suId, pdcpId, staInd, buff)
Pst* pst;
SuId suId;
CmLtePdcpId * pdcpId;
PjuStaIndInfo * staInd;
Buffer * buff;
#endif
{
   Buffer *mBuf = NULLP;
   MsgLen msgLen = 0;
   TRC3(cmPkPjuStaInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU053, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(buff);
      RETVALUE(RFAILED);
   }
   if (pst->selector == PJU_SEL_LC) {
      if ( buff != NULLP )
      {
         if (SFndLenMsg(buff, &msgLen) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)EPJU054, (ErrVal)0, "Packing failed");
#endif
            SPutMsg(buff);
            SPutMsg(mBuf);
            RETVALUE(RFAILED);
         }
         if (SCatMsg(mBuf, buff, M1M2) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)EPJU055, (ErrVal)0, "Packing failed");
#endif
            SPutMsg(buff);
            SPutMsg(mBuf);
            RETVALUE(RFAILED);
         }
         SPutMsg(buff);
      }
      else
      {
         msgLen = 0;
      }
      CMCHKPK(SPkS16, msgLen, mBuf);
   }
   if (pst->selector == PJU_SEL_LC) {
      if (cmPkPjuStaIndInfo(staInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)EPJU054, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }

   if (pst->selector == PJU_SEL_LC) {
      if (cmPkLtePdcpId(pdcpId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)EPJU056, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }

   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU058, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
    pst->event = (Event) EVTPJUSTAIND;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkPjuStaInd
(
PjuStaInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjuStaInd(func, pst, mBuf)
PjuStaInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   CmLtePdcpId pdcpId;
   PjuStaIndInfo staInd;
   Buffer *buff = NULLP;
   
   TRC3(cmUnpkPjuStaInd)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU061, (ErrVal)0, "Unpacking failed");
#endif
      RETVALUE(RFAILED);
   }

   if (pst->selector == PJU_SEL_LC) 
   {
      if (cmUnpkLtePdcpId(&pdcpId, mBuf) != ROK)
      {
         SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)EPJU063, (ErrVal)0, "Unpacking failed");
#endif
         RETVALUE(RFAILED);
      }
   }

   if (pst->selector == PJU_SEL_LC) 
   {
      cmMemset((U8 *)(&staInd), 0, sizeof(PjuStaIndInfo));

      if (cmUnpkPjuStaIndInfo(&staInd, mBuf) != ROK)
      {
         SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)EPJU065, (ErrVal)0, "Unpacking failed");
#endif
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector == PJU_SEL_LC) {
      MsgLen msgLen, totalMsgLen;
      CMCHKUNPK(cmUnpkMsgLen, &msgLen, mBuf);
      if ( msgLen != 0 )
      {
         if (SFndLenMsg(mBuf, &totalMsgLen) != ROK)
            RETVALUE(RFAILED);
         /* pju_c_001.main_2 */
         if (SSegMsg(mBuf, (S16)(totalMsgLen-msgLen), &buff) != ROK)
            RETVALUE(RFAILED);
      }
   }

   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, &pdcpId, &staInd, buff));
}

#ifdef ANSI
PUBLIC S16 cmPkPjuDatFwdReq
(
Pst* pst,
SpId spId,
CmLtePdcpId * pdcpId,
PjuDatFwdReqInfo * datFwdReq
)
#else
PUBLIC S16 cmPkPjuDatFwdReq(pst, spId, pdcpId, datFwdReq)
Pst* pst;
SpId spId;
CmLtePdcpId * pdcpId;
PjuDatFwdReqInfo * datFwdReq;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkPjuDatFwdReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU066, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)datFwdReq, sizeof(PjuDatFwdReqInfo));
      RETVALUE(RFAILED);
   }
   if (pst->selector == PJU_SEL_LC) {
      if (cmPkPjuDatFwdReqInfo(datFwdReq, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)EPJU067, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)datFwdReq, sizeof(PjuDatFwdReqInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      SPutSBuf(pst->region, pst->pool, (Data *)datFwdReq->datFwdInfo,
            (datFwdReq->numSdus * sizeof(PjuDatFwdInfo)) );
   }

   if (pst->selector == PJU_SEL_LC) {
      if (cmPkLtePdcpId(pdcpId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)EPJU069, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)datFwdReq, sizeof(PjuDatFwdReqInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }

   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU071, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)datFwdReq, sizeof(PjuDatFwdReqInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   SPutSBuf(pst->region, pst->pool, (Data *)datFwdReq, sizeof(PjuDatFwdReqInfo));

   pst->event = (Event) EVTPJUDATFWDREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkPjuDatFwdReq
(
PjuDatFwdReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjuDatFwdReq(func, pst, mBuf)
PjuDatFwdReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16   ret1;
   SpId spId;
   CmLtePdcpId pdcpId;
   PjuDatFwdReqInfo *datFwdReq = NULLP;
   
   TRC3(cmUnpkPjuDatFwdReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU074, (ErrVal)0, "Unpacking failed");
#endif
      RETVALUE(RFAILED);
   }

   if (pst->selector == PJU_SEL_LC)
   {
      if (cmUnpkLtePdcpId(&pdcpId, mBuf) != ROK) {
         SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)EPJU076, (ErrVal)0, "Unpacking failed");
#endif
         RETVALUE(RFAILED);
      }
   }

   if (pst->selector == PJU_SEL_LC) 
   {
      if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&datFwdReq,\
                  sizeof(PjuDatFwdReqInfo))) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)EPJU040, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(ret1);
      }

      if (cmUnpkPjuDatFwdReqInfo(pst, datFwdReq, mBuf) != ROK)
      {
         SPutSBuf(pst->region, pst->pool, (Data *)datFwdReq, sizeof(PjuDatFwdReqInfo));
         SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)EPJU078, (ErrVal)0, "Unpacking failed");
#endif
         RETVALUE(RFAILED);
      }
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, &pdcpId, datFwdReq));
}

#ifdef ANSI
PUBLIC S16 cmPkPjuDatFwdInd
(
Pst* pst,
SuId suId,
CmLtePdcpId * pdcpId,
PjuDatFwdIndInfo * datFwdInd
)
#else
PUBLIC S16 cmPkPjuDatFwdInd(pst, suId, pdcpId, datFwdInd)
Pst* pst;
SuId suId;
CmLtePdcpId * pdcpId;
PjuDatFwdIndInfo * datFwdInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkPjuDatFwdInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU079, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)datFwdInd, sizeof(PjuDatFwdIndInfo));
      RETVALUE(RFAILED);
   }
   if (pst->selector == PJU_SEL_LC) 
   {
      if (cmPkPjuDatFwdReqInfo(datFwdInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)EPJU080, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)datFwdInd, sizeof(PjuDatFwdIndInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      /* pju_c_001.main_4 if numSdus == 0, then do not free the memory */
      if(datFwdInd->numSdus != 0)
      {
         SPutSBuf(pst->region, pst->pool, (Data *)datFwdInd->datFwdInfo,
                 (datFwdInd->numSdus * sizeof(PjuDatFwdInfo)) );
      }
   }

   if (pst->selector == PJU_SEL_LC) {
      if (cmPkLtePdcpId(pdcpId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)EPJU082, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)datFwdInd, sizeof(PjuDatFwdIndInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }

   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU084, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)datFwdInd, sizeof(PjuDatFwdIndInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   /* Free Confirm Structure after packing */
   SPutSBuf(pst->region, pst->pool, (Data *)datFwdInd, sizeof(PjuDatFwdIndInfo));

   pst->event = (Event) EVTPJUDATFWDIND;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkPjuDatFwdInd
(
PjuDatFwdInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjuDatFwdInd(func, pst, mBuf)
PjuDatFwdInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16   ret1;
   SuId suId;
   CmLtePdcpId pdcpId;
   PjuDatFwdIndInfo *datFwdInd = NULLP;
   
   TRC3(cmUnpkPjuDatFwdInd)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EPJU087, (ErrVal)0, "Unpacking failed");
#endif
      RETVALUE(RFAILED);
   }

   if (pst->selector == PJU_SEL_LC) 
   {
      if (cmUnpkLtePdcpId(&pdcpId, mBuf) != ROK)
      {
         SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)EPJU089, (ErrVal)0, "Unpacking failed");
#endif
         RETVALUE(RFAILED);
      }
   }

   if (pst->selector == PJU_SEL_LC) 
   {
      if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&datFwdInd,\
                  sizeof(PjuDatFwdIndInfo))) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)EPJU040, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(ret1);
      }

      if (cmUnpkPjuDatFwdReqInfo(pst, datFwdInd, mBuf) != ROK)
      {
         SPutSBuf(pst->region, pst->pool, (Data *)datFwdInd, sizeof(PjuDatFwdIndInfo));
         SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)EPJU091, (ErrVal)0, "Unpacking failed");
#endif
         RETVALUE(RFAILED);
      }
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, &pdcpId, datFwdInd));
}


/***********************************************************
*
*     Func : cmPkPjuDatCfmInfoSta
*
*
*     Desc :   Data confirmation status parameters
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
PUBLIC S16 cmPkPjuDatCfmInfoSta
(
PjuDatCfmSta *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkPjuDatCfmInfoSta(param, mBuf)
PjuDatCfmSta *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkPjuDatCfmInfoSta)

   CMCHKPK(SPkU8, param->status, mBuf);
   CMCHKPK(SPkU32, param->sduId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkPjuDatCfmInfoSta
*
*
*     Desc :   Data confirmation status parameters
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
PUBLIC S16 cmUnpkPjuDatCfmInfoSta
(
PjuDatCfmSta *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjuDatCfmInfoSta(param, mBuf)
PjuDatCfmSta *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkPjuDatCfmInfoSta)

   CMCHKUNPK(SUnpkU32, &param->sduId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->status, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkPjuDatCfmInfo
*
*
*     Desc :   Data confirmation parameters
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
PUBLIC S16 cmPkPjuDatCfmInfo
(
PjuDatCfmInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkPjuDatCfmInfo(param, mBuf)
PjuDatCfmInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkPjuDatCfmInfo)

   for (i=param->numSdus-1; i >= 0; i--) {
      CMCHKPK(cmPkPjuDatCfmInfoSta, &param->cfmSta[i], mBuf);
   }
   CMCHKPK(SPkU16, param->numSdus, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkPjuDatCfmInfo
*
*
*     Desc :   Data confirmation parameters
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
PUBLIC S16 cmUnpkPjuDatCfmInfo
(
PjuDatCfmInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjuDatCfmInfo(param, mBuf)
PjuDatCfmInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkPjuDatCfmInfo)

   CMCHKUNPK(SUnpkU16, &param->numSdus, mBuf);
   if(param->numSdus > PJU_MAX_SDU_CFM)
   {                      
      /*Memory corruption is observed and hence Returning and logging this event in L3*/ 
      RETVALUE(RIGNORE);
   }
   for (i=0; i<param->numSdus ; i++) {
      CMCHKUNPK(cmUnpkPjuDatCfmInfoSta, &param->cfmSta[i], mBuf);
   }
   
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkPjuStaIndInfo
*
*
*     Desc :   Status indication parameters
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
PUBLIC S16 cmPkPjuStaIndInfo
(
PjuStaIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkPjuStaIndInfo(param, mBuf)
PjuStaIndInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkPjuStaIndInfo)

   CMCHKPK(SPkU8, param->cause, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkPjuStaIndInfo
*
*
*     Desc :   Status indication parameters
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
PUBLIC S16 cmUnpkPjuStaIndInfo
(
PjuStaIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjuStaIndInfo(param, mBuf)
PjuStaIndInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkPjuStaIndInfo)

   CMCHKUNPK(SUnpkU8, &param->cause, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkPjuDatFwdInfo
*
*
*     Desc :   Data Forward Information
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
PUBLIC S16 cmPkPjuDatFwdInfo
(
PjuDatFwdInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkPjuDatFwdInfo(param, mBuf)
PjuDatFwdInfo *param;
Buffer *mBuf;
#endif
{

   MsgLen msgLen = 0;
   TRC3(cmPkPjuDatFwdInfo)
   if (SFndLenMsg(param->sdu, &msgLen) != ROK)
      RETVALUE(RFAILED);
#ifndef SS_RBUF
   if (SCatMsg(mBuf, param->sdu, M1M2) != ROK)
      RETVALUE(RFAILED);
   SPutMsg(param->sdu);
#else 
   CMCHKPK(SPkU32, (U32)param->sdu, mBuf)
#endif
   CMCHKPK(SPkS16, msgLen, mBuf);

   CMCHKPK(SPkU16, param->sn, mBuf);
   CMCHKPK(SPkU32, param->sduId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkPjuDatFwdInfo
*
*
*     Desc :   Data Forward Information
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
PUBLIC S16 cmUnpkPjuDatFwdInfo
(
PjuDatFwdInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjuDatFwdInfo(param, mBuf)
PjuDatFwdInfo *param;
Buffer *mBuf;
#endif
{

   MsgLen msgLen = 0;
#ifndef SS_RBUF
   MsgLen totalMsgLen = 0;
#endif
   TRC3(cmUnpkPjuDatFwdInfo)

   CMCHKUNPK(SUnpkU32, &param->sduId, mBuf);
   CMCHKUNPK(SUnpkU16, &param->sn, mBuf);
   CMCHKUNPK(cmUnpkMsgLen, &msgLen, mBuf);
#ifndef SS_RBUF 
   if (SFndLenMsg(mBuf, &totalMsgLen) != ROK)
      RETVALUE(RFAILED);
   /* pju_c_001.main_2 */
   if (SSegMsg(mBuf, (S16)(totalMsgLen-msgLen), &param->sdu) != ROK)
      RETVALUE(RFAILED);
#else
   CMCHKUNPK(SUnpkU32,(U32 *)&param->sdu, mBuf);
#endif
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkPjuDatFwdReqInfo
*
*
*     Desc :   Data Forward Request parameters for PDCP 
            entity mapped to RLC AM
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
PUBLIC S16 cmPkPjuDatFwdReqInfo
(
PjuDatFwdReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkPjuDatFwdReqInfo(param, mBuf)
PjuDatFwdReqInfo *param;
Buffer *mBuf;
#endif
{
   S32  numSdus = 0;

   TRC3(cmPkPjuDatFwdReqInfo)

   CMCHKPK(SPkU8, param->isLastDatFwdInd, mBuf);

   while ( numSdus < param->numSdus )
   {
#ifdef SS_RBUF
      if(param->dir == CM_LTE_DIR_UL)
      {
         bcIcpuFlushBuffer(param->datFwdInfo[numSdus].sdu); 
      }
#endif
      CMCHKPK(cmPkPjuDatFwdInfo, &(param->datFwdInfo[numSdus]), mBuf);
      numSdus++;
   }
   CMCHKPK(SPkU16, param->numSdus, mBuf);
   CMCHKPK(SPkU8, param->dir, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkPjuDatFwdReqInfo
*
*
*     Desc :   Data Forward Request parameters for PDCP 
            entity mapped to RLC AM
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
PUBLIC S16 cmUnpkPjuDatFwdReqInfo
(
Pst *pst,
PjuDatFwdReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjuDatFwdReqInfo(pst,param, mBuf)
Pst *pst;
PjuDatFwdReqInfo *param;
Buffer *mBuf;
#endif
{
   S16   ret1;
   S32  numSdus = 0;

   TRC3(cmUnpkPjuDatFwdReqInfo)

   CMCHKUNPK(SUnpkU8, &param->dir, mBuf);
   CMCHKUNPK(SUnpkU16, &param->numSdus, mBuf);
   /* pju_c_001.main_4 if numSdus == 0, then return ROK */
   if(param->numSdus == 0)
   {
      CMCHKUNPK(SUnpkU8, &param->isLastDatFwdInd, mBuf);
      RETVALUE(ROK);
   }
   if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&param->datFwdInfo,\
               (sizeof(PjuDatFwdInfo)* param->numSdus ))) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)EPJU040, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
      RETVALUE(ret1);
   }
   numSdus = param->numSdus - 1;
    while ( numSdus >= 0 )
   {
      CMCHKUNPK(cmUnpkPjuDatFwdInfo, &(param->datFwdInfo[numSdus]), mBuf);
      numSdus--;
   }

   CMCHKUNPK(SUnpkU8, &param->isLastDatFwdInd, mBuf);

   RETVALUE(ROK);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* (defined(LCPJU) || defined(LWLCPJU)) */


/********************************************************************30**
  
         End of file:     pju.c@@/main/5 - Fri Sep  2 19:27:53 2011
  
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
/main/1      ---      dm   1. LTE RRC Initial Release.
/main/2      ---      gk   1. LTE RLC PDCP Release 2.1
/main/3      ---      pju_c_001.main_2  nm   1. Typecast arg with S16 for SSegMsg
/main/4      ---      pju_c_001.main_3  sv   1. Fixed memory leaks 
                                                in error cases.
/main/4      pju_c_001.main_4 ap  1. Added support for sending Data Fwd indication 
                                     even numSdu is zero                                                
/main/5      pju_c_001.main_5 ap  1. ccpu00120534, fixed the problem of passing 
                                     suId and spId as argument.
*********************************************************************91*/
