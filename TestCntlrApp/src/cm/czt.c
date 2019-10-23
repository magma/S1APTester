
/********************************************************************20**

     Name:     X2AP Layer

     Type:     C source file

     Desc:     C Source code for Upper Interface procedures

     File:     czt.c

     Sid:      czt.c@@/main/3 - Thu Aug 25 18:15:05 2011

     Prg:      rs

*********************************************************************21*/

/* ---- CZT interface ---- */
/*

the following matrices define the mapping between the primitives
called by the upper interface of X2AP and the corresponding
primitives of the X2AP service user(s).

The parameter MAXCZUICZT defines the maximum number of service users on
top of X2AP. There is an array of functions per primitive
invoked by X2AP.

The dispatching is performed by the configurable variable: selector.
The selectors are:

   0 - loosely coupled (#define LCRSLICZT)
   1 - application (#define CZ)
   3 - Light weight loosely coupled

*/
/* header include files (.h) --*/
#include "envopt.h"        /* environment options --*/
#include "envdep.h"        /* environment dependent --*/
#include "envind.h"        /* environment independent --*/
#include "gen.h"           /* general --*/
#include "ssi.h"           /* system services --*/
#include "cm5.h"           /* common timer library --*/
#include "cm_hash.h"       /* common hash library --*/
#include "cm_llist.h"      /* common linked list library --*/
#include "cm_inet.h"       /* common socket library --*/
#include "cm_tpt.h"        /* common transport library --*/
#include "cm_tkns.h"       /* common tokens --*/
#include "cm_mblk.h"       /* Common memory allocation        */
#include "cm_inet.h"       /* Common socket library           */
#include "cm_pasn.h"       /* Common Asn.1 library           */
#include "sct.h"           /* SCT interface defines           */
#include "czt.h"           /* CZT interface defines           */


/* header/extern include files (.x) --*/
#include "gen.x"           /* general --*/
#include "ssi.x"           /* system services --*/
#include "cm5.x"           /* common timer library --*/
#include "cm_hash.x"       /* common hash library --*/
#include "cm_llist.x"      /* common linked list library --*/
#include "cm_inet.x"       /* common socket library --*/
#include "cm_mblk.x"       /* common mem alloc defines --*/
#include "cm_tkns.x"       /* common tokens --*/
#include "cm_tpt.x"        /* common transport library --*/
#include "cm_lib.x"
#include "cm_inet.x"       /* Common socket library           */
#include "cm_pasn.x"       /* Common ASn.1 Library           */
#include "sct.x"           /* SCT interface defines           */
#include "czt.x"           /* CZT interface structures        */
#include "czt_pk.x"        /* CZT pack fucntion prototypes       */
#include "czt_unpk.x"        /* CZT pack fucntion prototypes       */


/* czt_c_001.main_1 : CR Fixes */
#if (defined(LCCZT) || defined(LWLCCZT))

#ifdef ANSI
PUBLIC S16 cmPkCztBndReq
(
Pst * pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 cmPkCztBndReq(pst, suId, spId)
Pst * pst;
SuId suId;
SpId spId;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCztBndReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT001, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT002, (ErrVal)0, (S8*)"Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT003, (ErrVal)0, (S8*)"Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTCZTBNDREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCztBndReq
(
CztBndReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztBndReq(func, pst, mBuf)
CztBndReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   SpId spId;
   
   TRC3(cmUnpkCztBndReq)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT004, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT005, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, spId));
}

#ifdef ANSI
PUBLIC S16 cmPkCztUbndReq
(
Pst * pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 cmPkCztUbndReq(pst, spId, reason)
Pst * pst;
SpId spId;
Reason reason;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCztUbndReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT006, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SPkS16(reason, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT007, (ErrVal)0, (S8*)"Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT008, (ErrVal)0, (S8*)"Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTCZTUBNDREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCztUbndReq
(
CztUbndReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztUbndReq(func, pst, mBuf)
CztUbndReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   Reason reason;
   
   TRC3(cmUnpkCztUbndReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT009, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkS16(&reason, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT010, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, reason));
}

#ifdef ANSI
PUBLIC S16 cmPkCztBndCfm
(
Pst * pst,
SuId suId,
U8 status
)
#else
PUBLIC S16 cmPkCztBndCfm(pst, suId, status)
Pst * pst;
SuId suId;
U8 status;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCztBndCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT011, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SPkU8(status, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT012, (ErrVal)0, (S8*)"Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT013, (ErrVal)0, (S8*)"Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTCZTBNDCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCztBndCfm
(
CztBndCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztBndCfm(func, pst, mBuf)
CztBndCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   U8 status;
   
   TRC3(cmUnpkCztBndCfm)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT014, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkU8(&status, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT015, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, status));
}

#ifdef ANSI
PUBLIC S16 cmPkCztGpReq
(
Pst * pst,
SpId spId,
CztEvnt * gpReq
)
#else
PUBLIC S16 cmPkCztGpReq(pst, spId, gpReq)
Pst * pst;
SpId spId;
CztEvnt * gpReq;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCztGpReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT016, (ErrVal)0, (S8*)"Packing failed");
#endif
      cmFreeMem((Ptr)gpReq);
      RETVALUE(RFAILED);
   }
   if (pst->selector == CZT_SEL_LC) {
      if (cmPkCztEvnt(gpReq, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT017, (ErrVal)0, (S8*)"Packing failed");
#endif
         cmFreeMem((Ptr)gpReq);
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LWLC) {
      if (cmPkPtr((PTR)gpReq, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT018, (ErrVal)0, (S8*)"Packing failed");
#endif
         cmFreeMem((Ptr)gpReq);
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT019, (ErrVal)0, (S8*)"Packing failed");
#endif
      cmFreeMem((Ptr)gpReq);
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      cmFreeMem((Ptr)gpReq);
   }
   pst->event = (Event) EVTCZTGPREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCztGpReq
(
CztGpReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztGpReq(func, pst, mBuf)
CztGpReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   CztEvnt *gpReq;
   Mem sMem;   
   TRC3(cmUnpkCztGpReq)
   sMem.region=pst->region;
   sMem.pool=pst->pool;

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT020, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      if(cmAllocEvnt(sizeof(CztEvnt), CZT_MAXBLK_SIZE, &sMem, (Ptr*)&gpReq)!= ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT021, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector == CZT_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&gpReq, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LC) 
      if (cmUnpkCztEvnt(gpReq, mBuf) != ROK) {
      cmFreeMem((Ptr)gpReq);
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT022, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, gpReq));
}

#ifdef ANSI
PUBLIC S16 cmPkCztGpInd
(
Pst * pst,
SuId suId,
CztEvnt * gpInd
)
#else
PUBLIC S16 cmPkCztGpInd(pst, suId, gpInd)
Pst * pst;
SuId suId;
CztEvnt * gpInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCztGpInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT023, (ErrVal)0, (S8*)"Packing failed");
#endif
      cmFreeMem((Ptr)gpInd);
      RETVALUE(RFAILED);
   }
   if (pst->selector == CZT_SEL_LC) {
      if (cmPkCztEvnt(gpInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT024, (ErrVal)0, (S8*)"Packing failed");
#endif
         cmFreeMem((Ptr)gpInd);
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LWLC) {
      if (cmPkPtr((PTR)gpInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT025, (ErrVal)0, (S8*)"Packing failed");
#endif
         cmFreeMem((Ptr)gpInd);
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT026, (ErrVal)0, (S8*)"Packing failed");
#endif
      cmFreeMem((Ptr)gpInd);
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      cmFreeMem((Ptr)gpInd);
   }
   pst->event = (Event) EVTCZTGPIND;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCztGpInd
(
CztGpInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztGpInd(func, pst, mBuf)
CztGpInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   CztEvnt *gpInd;
   Mem sMem;   
   TRC3(cmUnpkCztGpInd)
   sMem.region=pst->region;
   sMem.pool=pst->pool;

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT027, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      if(cmAllocEvnt(sizeof(CztEvnt), CZT_MAXBLK_SIZE, &sMem, (Ptr*)&gpInd)!= ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT028, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector == CZT_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&gpInd, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LC) 
      if (cmUnpkCztEvnt(gpInd, mBuf) != ROK) {
      cmFreeMem((Ptr)gpInd);
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT029, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, gpInd));
}

#ifdef ANSI
PUBLIC S16 cmPkCztGpRsp
(
Pst * pst,
SpId spId,
CztEvnt * gpRsp
)
#else
PUBLIC S16 cmPkCztGpRsp(pst, spId, gpRsp)
Pst * pst;
SpId spId;
CztEvnt * gpRsp;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCztGpRsp)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT030, (ErrVal)0, (S8*)"Packing failed");
#endif
      cmFreeMem((Ptr)gpRsp);
      RETVALUE(RFAILED);
   }
   if (pst->selector == CZT_SEL_LC) {
      if (cmPkCztEvnt(gpRsp, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT031, (ErrVal)0, (S8*)"Packing failed");
#endif
         cmFreeMem((Ptr)gpRsp);
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LWLC) {
      if (cmPkPtr((PTR)gpRsp, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT032, (ErrVal)0, (S8*)"Packing failed");
#endif
         cmFreeMem((Ptr)gpRsp);
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT033, (ErrVal)0, (S8*)"Packing failed");
#endif
      cmFreeMem((Ptr)gpRsp);
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      cmFreeMem((Ptr)gpRsp);
   }
   pst->event = (Event) EVTCZTGPRSP;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCztGpRsp
(
CztGpRsp func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztGpRsp(func, pst, mBuf)
CztGpRsp func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   CztEvnt *gpRsp;
   Mem sMem;   
   TRC3(cmUnpkCztGpRsp)
   sMem.region=pst->region;
   sMem.pool=pst->pool;

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT034, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      if(cmAllocEvnt(sizeof(CztEvnt), CZT_MAXBLK_SIZE, &sMem, (Ptr*)&gpRsp)!= ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT035, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector == CZT_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&gpRsp, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LC) 
      if (cmUnpkCztEvnt(gpRsp, mBuf) != ROK) {
      cmFreeMem((Ptr)gpRsp);
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT036, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, gpRsp));
}

#ifdef ANSI
PUBLIC S16 cmPkCztGpCfm
(
Pst * pst,
SuId suId,
CztEvnt * gpCfm
)
#else
PUBLIC S16 cmPkCztGpCfm(pst, suId, gpCfm)
Pst * pst;
SuId suId;
CztEvnt * gpCfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCztGpCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT037, (ErrVal)0, (S8*)"Packing failed");
#endif
      cmFreeMem((Ptr)gpCfm);
      RETVALUE(RFAILED);
   }
   if (pst->selector == CZT_SEL_LC) {
      if (cmPkCztEvnt(gpCfm, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT038, (ErrVal)0, (S8*)"Packing failed");
#endif
         cmFreeMem((Ptr)gpCfm);
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LWLC) {
      if (cmPkPtr((PTR)gpCfm, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT039, (ErrVal)0, (S8*)"Packing failed");
#endif
         cmFreeMem((Ptr)gpCfm);
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT040, (ErrVal)0, (S8*)"Packing failed");
#endif
      cmFreeMem((Ptr)gpCfm);
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      cmFreeMem((Ptr)gpCfm);
   }
   pst->event = (Event) EVTCZTGPCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCztGpCfm
(
CztGpCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztGpCfm(func, pst, mBuf)
CztGpCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   CztEvnt *gpCfm;
   Mem sMem;   
   TRC3(cmUnpkCztGpCfm)
   sMem.region=pst->region;
   sMem.pool=pst->pool;

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT041, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      if(cmAllocEvnt(sizeof(CztEvnt), CZT_MAXBLK_SIZE, &sMem, (Ptr*)&gpCfm)!= ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT042, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector == CZT_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&gpCfm, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LC) 
      if (cmUnpkCztEvnt(gpCfm, mBuf) != ROK) {
      cmFreeMem((Ptr)gpCfm);
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT043, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, gpCfm));
}

#ifdef ANSI
PUBLIC S16 cmPkCztGpRetxReq
(
Pst * pst,
SpId spId,
CztReTxInfo          * reTxInfo
)
#else
PUBLIC S16 cmPkCztGpRetxReq(pst, spId, reTxInfo)
Pst * pst;
SpId spId;
CztReTxInfo          * reTxInfo;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCztGpRetxReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT044, (ErrVal)0, (S8*)"Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)reTxInfo, sizeof(CztReTxInfo));
      RETVALUE(RFAILED);
   }
   if (pst->selector == CZT_SEL_LC) {
      if (cmPkCztReTxInfo(reTxInfo, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT045, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)reTxInfo, sizeof(CztReTxInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LWLC) {
      if (cmPkPtr((PTR)reTxInfo, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT046, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)reTxInfo, sizeof(CztReTxInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT047, (ErrVal)0, (S8*)"Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)reTxInfo, sizeof(CztReTxInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      if (SPutSBuf(pst->region, pst->pool, (Data *)reTxInfo, sizeof(CztReTxInfo)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT048, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   pst->event = (Event) EVTCZTGPRETXREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCztGpRetxReq
(
CztGpRetxReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztGpRetxReq(func, pst, mBuf)
CztGpRetxReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   CztReTxInfo *reTxInfo;
   
   TRC3(cmUnpkCztGpRetxReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT049, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      if ((SGetSBuf(pst->region, pst->pool, (Data **)&reTxInfo, sizeof(CztReTxInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT050, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }

         cmMemset((U8 *)reTxInfo, (U8 )0, (sizeof(CztReTxInfo)));
   }
   if (pst->selector == CZT_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&reTxInfo, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LC) 
      if (cmUnpkCztReTxInfo(reTxInfo, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)reTxInfo, sizeof(CztReTxInfo));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT051, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, reTxInfo));
}

#ifdef ANSI
PUBLIC S16 cmPkCztBmpReq
(
Pst * pst,
SpId spId,
CztEvnt * bmpEvnt
)
#else
PUBLIC S16 cmPkCztBmpReq(pst, spId, bmpEvnt)
Pst * pst;
SpId spId;
CztEvnt * bmpEvnt;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCztBmpReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT052, (ErrVal)0, (S8*)"Packing failed");
#endif
      cmFreeMem((Ptr)bmpEvnt);
      RETVALUE(RFAILED);
   }
   if (pst->selector == CZT_SEL_LC) {
      if (cmPkCztEvnt(bmpEvnt, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT053, (ErrVal)0, (S8*)"Packing failed");
#endif
         cmFreeMem((Ptr)bmpEvnt);
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LWLC) {
      if (cmPkPtr((PTR)bmpEvnt, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT054, (ErrVal)0, (S8*)"Packing failed");
#endif
         cmFreeMem((Ptr)bmpEvnt);
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT055, (ErrVal)0, (S8*)"Packing failed");
#endif
      cmFreeMem((Ptr)bmpEvnt);
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      cmFreeMem((Ptr)bmpEvnt);
   }
   pst->event = (Event) EVTCZTBMPREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCztBmpReq
(
CztBmpReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztBmpReq(func, pst, mBuf)
CztBmpReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   CztEvnt *bmpEvnt;
   Mem sMem;   
   TRC3(cmUnpkCztBmpReq)
   sMem.region=pst->region;
   sMem.pool=pst->pool;

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT056, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      if(cmAllocEvnt(sizeof(CztEvnt), CZT_MAXBLK_SIZE, &sMem, (Ptr*)&bmpEvnt)!= ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT057, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector == CZT_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&bmpEvnt, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LC) 
      if (cmUnpkCztEvnt(bmpEvnt, mBuf) != ROK) {
      cmFreeMem((Ptr)bmpEvnt);
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT058, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, bmpEvnt));
}

#ifdef ANSI
PUBLIC S16 cmPkCztBmpInd
(
Pst * pst,
SuId suId,
CztEvnt * bmpEvnt
)
#else
PUBLIC S16 cmPkCztBmpInd(pst, suId, bmpEvnt)
Pst * pst;
SuId suId;
CztEvnt * bmpEvnt;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCztBmpInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT059, (ErrVal)0, (S8*)"Packing failed");
#endif
      cmFreeMem((Ptr)bmpEvnt);
      RETVALUE(RFAILED);
   }
   if (pst->selector == CZT_SEL_LC) {
      if (cmPkCztEvnt(bmpEvnt, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT060, (ErrVal)0, (S8*)"Packing failed");
#endif
         cmFreeMem((Ptr)bmpEvnt);
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LWLC) {
      if (cmPkPtr((PTR)bmpEvnt, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT061, (ErrVal)0, (S8*)"Packing failed");
#endif
         cmFreeMem((Ptr)bmpEvnt);
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT062, (ErrVal)0, (S8*)"Packing failed");
#endif
      cmFreeMem((Ptr)bmpEvnt);
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      cmFreeMem((Ptr)bmpEvnt);
   }
   pst->event = (Event) EVTCZTBMPIND;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCztBmpInd
(
CztBmpInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztBmpInd(func, pst, mBuf)
CztBmpInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   CztEvnt *bmpEvnt;
   Mem sMem;   
   TRC3(cmUnpkCztBmpInd)
   sMem.region=pst->region;
   sMem.pool=pst->pool;

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT063, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      if(cmAllocEvnt(sizeof(CztEvnt), CZT_MAXBLK_SIZE, &sMem, (Ptr*)&bmpEvnt)!= ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT064, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector == CZT_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&bmpEvnt, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LC) 
      if (cmUnpkCztEvnt(bmpEvnt, mBuf) != ROK) {
      cmFreeMem((Ptr)bmpEvnt);
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT065, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, bmpEvnt));
}

#ifdef ANSI
PUBLIC S16 cmPkCztBmpRsp
(
Pst * pst,
SpId spId,
CztEvnt * bmpRsp
)
#else
PUBLIC S16 cmPkCztBmpRsp(pst, spId, bmpRsp)
Pst * pst;
SpId spId;
CztEvnt * bmpRsp;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCztBmpRsp)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT066, (ErrVal)0, (S8*)"Packing failed");
#endif
      cmFreeMem((Ptr)bmpRsp);
      RETVALUE(RFAILED);
   }
   if (pst->selector == CZT_SEL_LC) {
      if (cmPkCztEvnt(bmpRsp, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT067, (ErrVal)0, (S8*)"Packing failed");
#endif
         cmFreeMem((Ptr)bmpRsp);
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LWLC) {
      if (cmPkPtr((PTR)bmpRsp, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT068, (ErrVal)0, (S8*)"Packing failed");
#endif
         cmFreeMem((Ptr)bmpRsp);
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT069, (ErrVal)0, (S8*)"Packing failed");
#endif
      cmFreeMem((Ptr)bmpRsp);
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      cmFreeMem((Ptr)bmpRsp);
   }
   pst->event = (Event) EVTCZTBMPRSP;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCztBmpRsp
(
CztBmpRsp func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztBmpRsp(func, pst, mBuf)
CztBmpRsp func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   CztEvnt *bmpRsp;
   Mem sMem;   
   TRC3(cmUnpkCztBmpRsp)
   sMem.region=pst->region;
   sMem.pool=pst->pool;

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT070, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      if(cmAllocEvnt(sizeof(CztEvnt), CZT_MAXBLK_SIZE, &sMem, (Ptr*)&bmpRsp)!= ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT071, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector == CZT_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&bmpRsp, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LC) 
      if (cmUnpkCztEvnt(bmpRsp, mBuf) != ROK) {
      cmFreeMem((Ptr)bmpRsp);
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT072, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, bmpRsp));
}

#ifdef ANSI
PUBLIC S16 cmPkCztBmpCfm
(
Pst * pst,
SuId suId,
CztEvnt * bmpCfm
)
#else
PUBLIC S16 cmPkCztBmpCfm(pst, suId, bmpCfm)
Pst * pst;
SuId suId;
CztEvnt * bmpCfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCztBmpCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT073, (ErrVal)0, (S8*)"Packing failed");
#endif
      cmFreeMem((Ptr)bmpCfm);
      RETVALUE(RFAILED);
   }
   if (pst->selector == CZT_SEL_LC) {
      if (cmPkCztEvnt(bmpCfm, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT074, (ErrVal)0, (S8*)"Packing failed");
#endif
         cmFreeMem((Ptr)bmpCfm);
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LWLC) {
      if (cmPkPtr((PTR)bmpCfm, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT075, (ErrVal)0, (S8*)"Packing failed");
#endif
         cmFreeMem((Ptr)bmpCfm);
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT076, (ErrVal)0, (S8*)"Packing failed");
#endif
      cmFreeMem((Ptr)bmpCfm);
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      cmFreeMem((Ptr)bmpCfm);
   }
   pst->event = (Event) EVTCZTBMPCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCztBmpCfm
(
CztBmpCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztBmpCfm(func, pst, mBuf)
CztBmpCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   CztEvnt *bmpCfm;
   Mem sMem;   
   TRC3(cmUnpkCztBmpCfm)
   sMem.region=pst->region;
   sMem.pool=pst->pool;

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT077, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      if(cmAllocEvnt(sizeof(CztEvnt), CZT_MAXBLK_SIZE, &sMem, (Ptr*)&bmpCfm)!= ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT078, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector == CZT_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&bmpCfm, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LC) 
      if (cmUnpkCztEvnt(bmpCfm, mBuf) != ROK) {
      cmFreeMem((Ptr)bmpCfm);
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT079, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, bmpCfm));
}

#ifdef ANSI
PUBLIC S16 cmPkCztGpErrReq
(
Pst * pst,
SpId spId,
CztEvnt * gpErrReq
)
#else
PUBLIC S16 cmPkCztGpErrReq(pst, spId, gpErrReq)
Pst * pst;
SpId spId;
CztEvnt * gpErrReq;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCztGpErrReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT080, (ErrVal)0, (S8*)"Packing failed");
#endif
      cmFreeMem((Ptr)gpErrReq);
      RETVALUE(RFAILED);
   }
   if (pst->selector == CZT_SEL_LC) {
      if (cmPkCztEvnt(gpErrReq, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT081, (ErrVal)0, (S8*)"Packing failed");
#endif
         cmFreeMem((Ptr)gpErrReq);
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LWLC) {
      if (cmPkPtr((PTR)gpErrReq, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT082, (ErrVal)0, (S8*)"Packing failed");
#endif
         cmFreeMem((Ptr)gpErrReq);
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT083, (ErrVal)0, (S8*)"Packing failed");
#endif
      cmFreeMem((Ptr)gpErrReq);
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      cmFreeMem((Ptr)gpErrReq);
   }
   pst->event = (Event) EVTCZTGPERRREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCztGpErrReq
(
CztGpErrReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztGpErrReq(func, pst, mBuf)
CztGpErrReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   CztEvnt *gpErrReq;
   Mem sMem;   
   TRC3(cmUnpkCztGpErrReq)
   sMem.region=pst->region;
   sMem.pool=pst->pool;

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT084, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      if(cmAllocEvnt(sizeof(CztEvnt), CZT_MAXBLK_SIZE, &sMem, (Ptr*)&gpErrReq)!= ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT085, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector == CZT_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&gpErrReq, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LC) 
      if (cmUnpkCztEvnt(gpErrReq, mBuf) != ROK) {
      cmFreeMem((Ptr)gpErrReq);
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT086, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, gpErrReq));
}

#ifdef ANSI
PUBLIC S16 cmPkCztGpErrInd
(
Pst * pst,
SuId suId,
CztEvnt * gpErrInd
)
#else
PUBLIC S16 cmPkCztGpErrInd(pst, suId, gpErrInd)
Pst * pst;
SuId suId;
CztEvnt * gpErrInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCztGpErrInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT087, (ErrVal)0, (S8*)"Packing failed");
#endif
      cmFreeMem((Ptr)gpErrInd);
      RETVALUE(RFAILED);
   }
   if (pst->selector == CZT_SEL_LC) {
      if (cmPkCztEvnt(gpErrInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT088, (ErrVal)0, (S8*)"Packing failed");
#endif
         cmFreeMem((Ptr)gpErrInd);
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LWLC) {
      if (cmPkPtr((PTR)gpErrInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT089, (ErrVal)0, (S8*)"Packing failed");
#endif
         cmFreeMem((Ptr)gpErrInd);
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT090, (ErrVal)0, (S8*)"Packing failed");
#endif
      cmFreeMem((Ptr)gpErrInd);
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      cmFreeMem((Ptr)gpErrInd);
   }
   pst->event = (Event) EVTCZTGPERRIND;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCztGpErrInd
(
CztGpErrInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztGpErrInd(func, pst, mBuf)
CztGpErrInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   CztEvnt *gpErrInd;
   Mem sMem;    
   TRC3(cmUnpkCztGpErrInd)
   
   sMem.region=pst->region;
   sMem.pool=pst->pool;
   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT091, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      if(cmAllocEvnt(sizeof(CztEvnt), CZT_MAXBLK_SIZE, &sMem, (Ptr*)&gpErrInd)!= ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT092, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector == CZT_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&gpErrInd, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LC) 
      if (cmUnpkCztEvnt(gpErrInd, mBuf) != ROK) {
      cmFreeMem((Ptr)gpErrInd);
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT093, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, gpErrInd));
}

#ifdef ANSI
PUBLIC S16 cmPkCztLclErrorInd
(
Pst * pst,
SuId suId,
CztLclErrInd * cztLclErrInd
)
#else
PUBLIC S16 cmPkCztLclErrorInd(pst, suId, cztLclErrInd)
Pst * pst;
SuId suId;
CztLclErrInd * cztLclErrInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCztLclErrorInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT094, (ErrVal)0, (S8*)"Packing failed");
#endif
      if(cztLclErrInd->rcvBuf != NULLP)
      {
         SPutMsg(cztLclErrInd->rcvBuf);
      }
      if(cztLclErrInd->event != NULLP)
      {
         cmFreeMem((Ptr)cztLclErrInd->event);
      }
      SPutSBuf(pst->region, pst->pool, (Data *)cztLclErrInd, sizeof(CztLclErrInd));
      RETVALUE(RFAILED);
   }
   if (pst->selector == CZT_SEL_LC) {
      if (cmPkCztLclErrInd(cztLclErrInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT095, (ErrVal)0, (S8*)"Packing failed");
#endif
         if(cztLclErrInd->rcvBuf != NULLP)
         {
            SPutMsg(cztLclErrInd->rcvBuf);
         }
         if(cztLclErrInd->event != NULLP)
         {
            cmFreeMem((Ptr)cztLclErrInd->event);
         }
         SPutSBuf(pst->region, pst->pool, (Data *)cztLclErrInd, sizeof(CztLclErrInd));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LWLC) {
      if (cmPkPtr((PTR)cztLclErrInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT096, (ErrVal)0, (S8*)"Packing failed");
#endif
         if(cztLclErrInd->rcvBuf != NULLP)
         {
            SPutMsg(cztLclErrInd->rcvBuf);
         }
         if(cztLclErrInd->event != NULLP)
         {
            cmFreeMem((Ptr)cztLclErrInd->event);
         }
         SPutSBuf(pst->region, pst->pool, (Data *)cztLclErrInd, sizeof(CztLclErrInd));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT097, (ErrVal)0, (S8*)"Packing failed");
#endif
      if(cztLclErrInd->rcvBuf != NULLP)
      {
         SPutMsg(cztLclErrInd->rcvBuf);
      }
      if(cztLclErrInd->event != NULLP)
      {
         cmFreeMem((Ptr)cztLclErrInd->event);
      }
      SPutSBuf(pst->region, pst->pool, (Data *)cztLclErrInd, sizeof(CztLclErrInd));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {

      if(cztLclErrInd->event != NULLP)
      {
         cmFreeMem((Ptr)cztLclErrInd->event);
      }
      if (SPutSBuf(pst->region, pst->pool, (Data *)cztLclErrInd, sizeof(CztLclErrInd)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT098, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   pst->event = (Event) EVTCZTERRIND;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCztLclErrorInd
(
CztLclErrorInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztLclErrorInd(func, pst, mBuf)
CztLclErrorInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   Mem sMem;   
   CztLclErrInd *cztLclErrInd;
   
   sMem.region=pst->region;
   sMem.pool=pst->pool;

   TRC3(cmUnpkCztLclErrorInd)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT099, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      if ((SGetSBuf(pst->region, pst->pool, (Data **)&cztLclErrInd, sizeof(CztLclErrInd))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT100, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
         cmMemset((U8 *)cztLclErrInd, (U8 )0, (sizeof(CztLclErrInd)));
   }
   if (pst->selector == CZT_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&cztLclErrInd, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LC)
   {
      if(cmAllocEvnt(sizeof(CztEvnt), CZT_MAXBLK_SIZE, &sMem, (Ptr*)&(cztLclErrInd->event))!= ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT101, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      if (cmUnpkCztLclErrInd(cztLclErrInd, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)cztLclErrInd, sizeof(CztLclErrInd));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT102, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, cztLclErrInd));
}

#ifdef ANSI
PUBLIC S16 cmPkCztRelReq
(
Pst * pst,
SpId spId,
CztRlsReq            * rlsReq
)
#else
PUBLIC S16 cmPkCztRelReq(pst, spId, rlsReq)
Pst * pst;
SpId spId;
CztRlsReq            * rlsReq;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCztRelReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT103, (ErrVal)0, (S8*)"Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)rlsReq, sizeof(CztRlsReq));
      RETVALUE(RFAILED);
   }
   if (pst->selector == CZT_SEL_LC) {
      if (cmPkCztRlsReq(rlsReq, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT104, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)rlsReq, sizeof(CztRlsReq));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LWLC) {
      if (cmPkPtr((PTR)rlsReq, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT105, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)rlsReq, sizeof(CztRlsReq));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT106, (ErrVal)0, (S8*)"Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)rlsReq, sizeof(CztRlsReq));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      if (SPutSBuf(pst->region, pst->pool, (Data *)rlsReq, sizeof(CztRlsReq)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT107, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   pst->event = (Event) EVTCZTLOCALRELREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCztRelReq
(
CztRelReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztRelReq(func, pst, mBuf)
CztRelReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   CztRlsReq *rlsReq;
   
   TRC3(cmUnpkCztRelReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT108, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      if ((SGetSBuf(pst->region, pst->pool, (Data **)&rlsReq, sizeof(CztRlsReq))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT109, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
         cmMemset((U8 *)rlsReq, (U8 )0, (sizeof(CztRlsReq)));
   }
   if (pst->selector == CZT_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&rlsReq, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LC) 
      if (cmUnpkCztRlsReq(rlsReq, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)rlsReq, sizeof(CztRlsReq));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT110, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, rlsReq));
}

#ifdef ANSI
PUBLIC S16 cmPkCztRelCfm
(
Pst * pst,
SuId suId,
CztRlsCfm  * rlsCfm
)
#else
PUBLIC S16 cmPkCztRelCfm(pst, suId, rlsCfm)
Pst * pst;
SuId suId;
CztRlsCfm  * rlsCfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCztRelCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT111, (ErrVal)0, (S8*)"Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)rlsCfm, sizeof(CztRlsCfm));
      RETVALUE(RFAILED);
   }
   if (pst->selector == CZT_SEL_LC) {
      if (cmPkCztStaInd(rlsCfm, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT112, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)rlsCfm, sizeof(CztRlsCfm));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LWLC) {
      if (cmPkPtr((PTR)rlsCfm, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT113, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)rlsCfm, sizeof(CztRlsCfm));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT114, (ErrVal)0, (S8*)"Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)rlsCfm, sizeof(CztRlsCfm));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      if (SPutSBuf(pst->region, pst->pool, (Data *)rlsCfm, sizeof(CztRlsCfm)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT115, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   pst->event = (Event) EVTCZTLOCALRELCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCztRelCfm
(
CztRelCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztRelCfm(func, pst, mBuf)
CztRelCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   CztRlsCfm *rlsCfm;
   
   TRC3(cmUnpkCztRelCfm)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT116, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      if ((SGetSBuf(pst->region, pst->pool, (Data **)&rlsCfm, sizeof(CztRlsCfm))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT117, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
         cmMemset((U8 *)rlsCfm, (U8 )0, (sizeof(CztRlsCfm)));
   }
   if (pst->selector == CZT_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&rlsCfm, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LC) 
      if (cmUnpkCztStaInd(rlsCfm, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)rlsCfm, sizeof(CztRlsCfm));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT118, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, rlsCfm));
}

#ifdef ANSI
PUBLIC S16 cmPkCztStatusInd
(
Pst * pst,
SuId suId,
CztStaInd * cztSta
)
#else
PUBLIC S16 cmPkCztStatusInd(pst, suId, cztSta)
Pst * pst;
SuId suId;
CztStaInd * cztSta;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCztStatusInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT119, (ErrVal)0, (S8*)"Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)cztSta, sizeof(CztStaInd));
      RETVALUE(RFAILED);
   }
   if (pst->selector == CZT_SEL_LC) {
      if (cmPkCztStaInd(cztSta, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT120, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)cztSta, sizeof(CztStaInd));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LWLC) {
      if (cmPkPtr((PTR)cztSta, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT121, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)cztSta, sizeof(CztStaInd));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT122, (ErrVal)0, (S8*)"Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)cztSta, sizeof(CztStaInd));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      if (SPutSBuf(pst->region, pst->pool, (Data *)cztSta, sizeof(CztStaInd)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT123, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   pst->event = (Event) EVTCZTSTAIND;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCztStatusInd
(
CztStatusInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztStatusInd(func, pst, mBuf)
CztStatusInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   CztStaInd *cztSta;
   
   TRC3(cmUnpkCztStatusInd)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT124, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      if ((SGetSBuf(pst->region, pst->pool, (Data **)&cztSta, sizeof(CztStaInd))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT125, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
         cmMemset((U8 *)cztSta, (U8 )0, (sizeof(CztStaInd)));
   }
   if (pst->selector == CZT_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&cztSta, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LC) 
      if (cmUnpkCztStaInd(cztSta, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)cztSta, sizeof(CztStaInd));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT126, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, cztSta));
}

#ifdef ANSI
PUBLIC S16 cmPkCztDynamPeerAssocInd
(
Pst * pst,
SuId suId,
CztPeerAssocInd * peerAssocInd
)
#else
PUBLIC S16 cmPkCztDynamPeerAssocInd(pst, suId, peerAssocInd)
Pst * pst;
SuId suId;
CztPeerAssocInd * peerAssocInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCztDynamPeerAssocInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT127, (ErrVal)0, (S8*)"Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)peerAssocInd, sizeof(CztPeerAssocInd));
      RETVALUE(RFAILED);
   }
   if (pst->selector == CZT_SEL_LC) {
      if (cmPkCztPeerAssocInd(peerAssocInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT128, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)peerAssocInd, sizeof(CztPeerAssocInd));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LWLC) {
      if (cmPkPtr((PTR)peerAssocInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT129, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)peerAssocInd, sizeof(CztPeerAssocInd));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT130, (ErrVal)0, (S8*)"Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)peerAssocInd, sizeof(CztPeerAssocInd));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      if (SPutSBuf(pst->region, pst->pool, (Data *)peerAssocInd, sizeof(CztPeerAssocInd)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT131, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   pst->event = (Event) EVTCZTPEERASSOCIND;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCztDynamPeerAssocInd
(
CztDynamPeerAssocInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztDynamPeerAssocInd(func, pst, mBuf)
CztDynamPeerAssocInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   CztPeerAssocInd *peerAssocInd;
   
   TRC3(cmUnpkCztDynamPeerAssocInd)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT132, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      if ((SGetSBuf(pst->region, pst->pool, (Data **)&peerAssocInd, sizeof(CztPeerAssocInd))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT133, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
         cmMemset((U8 *)peerAssocInd, (U8 )0, (sizeof(CztPeerAssocInd)));
   }
   if (pst->selector == CZT_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&peerAssocInd, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LC) 
      if (cmUnpkCztPeerAssocInd(peerAssocInd, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)peerAssocInd, sizeof(CztPeerAssocInd));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT134, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, peerAssocInd));
}

#ifdef ANSI
PUBLIC S16 cmPkCztDynamPeerAssocRsp
(
Pst * pst,
SuId suId,
CztPeerAssocRsp * peerAssocRsp
)
#else
PUBLIC S16 cmPkCztDynamPeerAssocRsp(pst, suId, peerAssocRsp)
Pst * pst;
SuId suId;
CztPeerAssocRsp * peerAssocRsp;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCztDynamPeerAssocRsp)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT135, (ErrVal)0, (S8*)"Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)peerAssocRsp, sizeof(CztPeerAssocRsp));
      RETVALUE(RFAILED);
   }
   if (pst->selector == CZT_SEL_LC) {
      if (cmPkCztPeerAssocRsp(peerAssocRsp, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT136, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)peerAssocRsp, sizeof(CztPeerAssocRsp));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LWLC) {
      if (cmPkPtr((PTR)peerAssocRsp, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT137, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)peerAssocRsp, sizeof(CztPeerAssocRsp));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT138, (ErrVal)0, (S8*)"Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)peerAssocRsp, sizeof(CztPeerAssocRsp));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      if (SPutSBuf(pst->region, pst->pool, (Data *)peerAssocRsp, sizeof(CztPeerAssocRsp)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT139, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   pst->event = (Event) EVTCZTPEERASSOCRSP;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkCztDynamPeerAssocRsp
(
CztDynamPeerAssocRsp func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztDynamPeerAssocRsp(func, pst, mBuf)
CztDynamPeerAssocRsp func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   CztPeerAssocRsp *peerAssocRsp;
   
   TRC3(cmUnpkCztDynamPeerAssocRsp)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT140, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != CZT_SEL_LWLC) {
      if ((SGetSBuf(pst->region, pst->pool, (Data **)&peerAssocRsp, sizeof(CztPeerAssocRsp))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT141, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
         cmMemset((U8 *)peerAssocRsp, (U8 )0, (sizeof(CztPeerAssocRsp)));
   }
   if (pst->selector == CZT_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&peerAssocRsp, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LC) 
      if (cmUnpkCztPeerAssocRsp(peerAssocRsp, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)peerAssocRsp, sizeof(CztPeerAssocRsp));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT142, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, peerAssocRsp));
}


/*
*
*       Fun:   cmPkCztAudEvnt
*
*       Desc:  This function packs the Audit Event
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCztAudEvnt
(
CztAudEvnt *audEvnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCztAudEvnt(audEvnt, mBuf)
CztAudEvnt *audEvnt;
Buffer *mBuf;
#endif
{
   TRC2(cmPkCztAudEvnt);

    CMCHKPK(SPkU8,audEvnt->status.cause,mBuf);
    CMCHKPK(SPkU8,audEvnt->status.status,mBuf);
   
    if((audEvnt->type == CZT_AUD_PEER) || 
         (audEvnt->type == CZT_AUD_FLC))
    {
       CMCHKPK(SPkU32,audEvnt->u.audPeer.peerId, mBuf);
       CMCHKPK(SPkU8 ,audEvnt->u.audPeer.peerState,mBuf);
    }
    CMCHKPK(SPkU8,audEvnt->type,mBuf);

    RETVALUE(ROK);
}/*cmPkCztAudEvnt */

/*
*
*    Fun:    cmPkCztAudReq
*
*    Desc:   pack the primitive CztAudReq
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCztAudReq
(
Pst *pst,
SpId spId,
CztAudEvnt *audReq
)
#else
PUBLIC S16 cmPkCztAudReq(pst, spId, audReq)
Pst *pst;
SpId spId;
CztAudEvnt *audReq;
#endif
{
    Buffer *mBuf;
    S16 ret1;
    mBuf = NULLP;
    TRC3(cmPkCztAudReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ECZT116, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    /*czt_c_001.main_2 : X2AP 1.2 fix for existing  tc*/
     if (pst->selector == CZT_SEL_LWLC) { 
      if (cmPkPtr((PTR)audReq, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT105, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)audReq, sizeof(CztAudEvnt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == CZT_SEL_LC)
   {
      CMCHKPKLOG(cmPkCztAudEvnt, audReq, mBuf, ECZT117, pst);
   }
   /* czt_c_001.main_3 : purify fix :Freeing the audreq structure */
   if (pst->selector != CZT_SEL_LWLC) 
   {
      if (SPutSBuf(pst->region, pst->pool, (Data *)audReq, sizeof(CztAudEvnt)) != ROK) 
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ECZT107, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }

    CMCHKPKLOG(SPkS16, spId, mBuf, ECZT118, pst); 
    pst->event = (Event) EVTCZTAUDREQ;
    RETVALUE(SPstTsk(pst,mBuf));

} /*end of function cmPkCztAudReq */

/*
*
*    Fun:    cmPkCztAudCfm
*
*    Desc:   pack the primitive CztAudCfm
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCztAudCfm
(
Pst *pst,
SuId suId,
CztAudEvnt *audCfm
)
#else
PUBLIC S16 cmPkCztAudCfm(pst, suId, audCfm)
Pst *pst;
SuId suId;
CztAudEvnt *audCfm;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkCztAudCfm)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ECZT119, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }

    /* X2AP 1.2 fix for existing testcase*/
        if (pst->selector == CZT_SEL_LWLC) { /*udaka */
      if (cmPkPtr((PTR)audCfm, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT105, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)audCfm, sizeof(CztAudEvnt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == CZT_SEL_LC)
   {

    CMCHKPKLOG(cmPkCztAudEvnt, audCfm, mBuf, ECZT120, pst);
   }

   /* czt_c_001.main_3 : purify Fix: Freeing the audCfm structure */
   if (pst->selector != CZT_SEL_LWLC) 
   {
      if (SPutSBuf(pst->region, pst->pool, (Data *)audCfm, sizeof(CztAudEvnt)) != ROK) 
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ECZT107, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }

    CMCHKPKLOG(SPkS16, suId, mBuf, ECZT121, pst);
    pst->event = (Event) EVTCZTAUDCFM;
    RETVALUE(SPstTsk(pst,mBuf));
   
} /*end of function cmPkCztAudCfm */


/*
*
*       Fun:   cmUnpkCztAudEvnt
*
*       Desc:  This function unpacks the Audit Event
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCztAudEvnt
(
CztAudEvnt *audEvnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztAudEvnt(audEvnt, mBuf)
CztAudEvnt *audEvnt;
Buffer *mBuf;
#endif
{
   TRC2(cmUnpkCztAudEvnt);

    CMCHKUNPK(SUnpkU8, &audEvnt->type,mBuf);
   
    if((audEvnt->type == CZT_AUD_PEER) ||
          (audEvnt->type == CZT_AUD_FLC))
    {
       CMCHKUNPK(SUnpkU8 ,&audEvnt->u.audPeer.peerState,mBuf);
       CMCHKUNPK(SUnpkU32,&audEvnt->u.audPeer.peerId, mBuf);
    }
    CMCHKUNPK(SUnpkU8, &audEvnt->status.status,mBuf);
    CMCHKUNPK(SUnpkU8, &audEvnt->status.cause,mBuf);


    RETVALUE(ROK);
}/* cmUnpkCztAudEvnt */

/*
*
*    Fun:   cmUnpkCztAudReq
*
*    Desc:   Unpack the primitive CztAudReq
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCztAudReq
(
CztAudReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztAudReq(func, pst, mBuf)
CztAudReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
    SpId spId;
    CztAudEvnt *audEvnt= NULLP; /* X2AP 1.2 fix for existing testcase*/

    TRC3(cmUnpkCztAudReq)

    CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, ERRCZT, pst);

   if (pst->selector != CZT_SEL_LWLC) {
      if ((SGetSBuf(pst->region, pst->pool, (Data **)&audEvnt, sizeof(CztAudEvnt))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT050, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }

         cmMemset((U8 *)audEvnt, (U8 )0, (sizeof(CztAudEvnt)));
   }

   if (pst->selector == CZT_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&audEvnt, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LC) 
      if (cmUnpkCztAudEvnt(audEvnt, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)audEvnt, sizeof(CztAudEvnt));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT051, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }

    SPutMsg(mBuf);
    RETVALUE((*func)(pst, spId, audEvnt));
} /*end of function cmUnpkCztAudReq */

/*
*
*    Fun:   cmUnpkCztAudCfm
*
*    Desc:   Unpack the primitive CztAudCfm
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCztAudCfm
(
CztAudCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztAudCfm(func, pst, mBuf)
CztAudCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
    SuId suId;
    CztAudEvnt *audEvnt;

    TRC3(cmUnpkCztAudCfm)

    CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, ERRCZT, pst);
   if (pst->selector != CZT_SEL_LWLC) {
      if ((SGetSBuf(pst->region, pst->pool, (Data **)&audEvnt, sizeof(CztAudEvnt))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECZT050, (ErrVal)0, (S8*)"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }

         cmMemset((U8 *)audEvnt, (U8 )0, (sizeof(CztAudEvnt)));
   }

   if (pst->selector == CZT_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&audEvnt, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CZT_SEL_LC) 
      if (cmUnpkCztAudEvnt(audEvnt, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)audEvnt, sizeof(CztAudEvnt));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECZT051, (ErrVal)0, (S8*)"Packing failed");
#endif
      RETVALUE(RFAILED);
   }

    SPutMsg(mBuf);
    RETVALUE((*func)(pst, suId, audEvnt));
}






/***********************************************************
*
*     Func : cmPkCztNetAddrLst
*
*
*     Desc : cztNetAddrLst 
   @brief X2AP Net Address List used for SCTP Association
   @details This structure contains the list of IP Address specified by
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
PUBLIC S16 cmPkCztNetAddrLst
(
CztNetAddrLst *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCztNetAddrLst(param, mBuf)
CztNetAddrLst *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkCztNetAddrLst)

   for (i=param->nmb; i > 0; i--) {
      CMCHKPK(cmPkCmNetAddr,&param->nAddr[i-1], mBuf);
   }
   CMCHKPK(SPkU8, param->nmb, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCztNetAddrLst
*
*
*     Desc : cztNetAddrLst 
   @brief X2AP Net Address List used for SCTP Association
   @details This structure contains the list of IP Address specified by
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
PUBLIC S16 cmUnpkCztNetAddrLst
(
CztNetAddrLst *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztNetAddrLst(param, mBuf)
CztNetAddrLst *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkCztNetAddrLst)

   CMCHKUNPK(SUnpkU8, &param->nmb, mBuf);
   for (i=0; i<param->nmb; i++) {
      CMCHKUNPK(cmUnpkCmNetAddr, &param->nAddr[i], mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCztReqStatus
*
*
*     Desc : cztReqStatus
   @brief X2AP Dynamic Peer Assocation Response' s status
   @details This structure contains the status and the cause of the status.
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
PUBLIC S16 cmPkCztReqStatus
(
CztReqStatus *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCztReqStatus(param, mBuf)
CztReqStatus *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCztReqStatus)

   CMCHKPK(SPkU8, param->cause, mBuf);
   CMCHKPK(SPkU8, param->status, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCztReqStatus
*
*
*     Desc : cztReqStatus
   @brief X2AP Dynamic Peer Assocation Response' s status
   @details This structure contains the status and the cause of the status.
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
PUBLIC S16 cmUnpkCztReqStatus
(
CztReqStatus *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztReqStatus(param, mBuf)
CztReqStatus *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCztReqStatus)

   CMCHKUNPK(SUnpkU8, &param->status, mBuf);
   CMCHKUNPK(SUnpkU8, &param->cause, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCztEvnt
*
*
*     Desc : cztEvnt
   @brief  X2AP Event structure
   @details This structure contains the X2AP pdu, Peer Id and 
            memory related information
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
PUBLIC S16 cmPkCztEvnt
(
CztEvnt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCztEvnt(param, mBuf)
CztEvnt *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCztEvnt)

   CMCHKPK(cmPkCztX2AP_PDU, &param->pdu, mBuf);
   CMCHKPK(SPkU32, param->peerId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCztEvnt
*
*
*     Desc : cztEvnt
   @brief  X2AP Event structure
   @details This structure contains the X2AP pdu, Peer Id and 
            memory related information
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
PUBLIC S16 cmUnpkCztEvnt
(
CztEvnt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztEvnt(param, mBuf)
CztEvnt *param;
Buffer *mBuf;
#endif
{

   Ptr ptr;
   TRC3(cmUnpkCztEvnt)

   ptr =(Ptr)param;
   CMCHKUNPK(SUnpkU32, &param->peerId, mBuf);
   CMCHKUNPKPTR(cmUnpkCztX2AP_PDU, &param->pdu, ptr, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCztStaInd
*
*
*     Desc : cztStaInd
   @brief X2AP Status Indication 
   @details This structure coantains information for Status Indication. <br>
            For more detail on Status Indication's Status 
            please refer to @ref cztstaindstatus. <br>
            For more detail on Status Indication's reason 
            please refer to @ref cztstaindreason.
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
PUBLIC S16 cmPkCztStaInd
(
CztStaInd *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCztStaInd(param, mBuf)
CztStaInd *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCztStaInd)

   CMCHKPK(SPkU16, param->oldUEX2APId, mBuf);
   CMCHKPK(SPkU8, param->reason, mBuf);
   CMCHKPK(SPkU8, param->status, mBuf);
   CMCHKPK(SPkU8, param->type, mBuf);
   CMCHKPK(SPkU32, param->peerId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCztStaInd
*
*
*     Desc : cztStaInd
   @brief X2AP Status Indication 
   @details This structure coantains information for Status Indication. <br>
            For more detail on Status Indication's Status 
            please refer to @ref cztstaindstatus. <br>
            For more detail on Status Indication's reason 
            please refer to @ref cztstaindreason.
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
PUBLIC S16 cmUnpkCztStaInd
(
CztStaInd *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztStaInd(param, mBuf)
CztStaInd *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCztStaInd)

   CMCHKUNPK(SUnpkU32, &param->peerId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->type, mBuf);
   CMCHKUNPK(SUnpkU8, &param->status, mBuf);
   CMCHKUNPK(SUnpkU8, &param->reason, mBuf);
   CMCHKUNPK(SUnpkU16, &param->oldUEX2APId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCztUeInfo
*
*
*     Desc : cztUeInfo
  @brief X2AP UE Information 
  @details This structure contains the old UE X2AP ID and new UE X2AP ID.
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
PUBLIC S16 cmPkCztUeInfo
(
CztUeInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCztUeInfo(param, mBuf)
CztUeInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCztUeInfo)

   CMCHKPK(SPkU16, param->newUEX2APId, mBuf);
   CMCHKPK(SPkU16, param->oldUEX2APId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCztUeInfo
*
*
*     Desc : cztUeInfo
  @brief X2AP UE Information 
  @details This structure contains the old UE X2AP ID and new UE X2AP ID.
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
PUBLIC S16 cmUnpkCztUeInfo
(
CztUeInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztUeInfo(param, mBuf)
CztUeInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCztUeInfo)

   CMCHKUNPK(SUnpkU16, &param->oldUEX2APId, mBuf);
   CMCHKUNPK(SUnpkU16, &param->newUEX2APId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRsrcProcInfo
*
*
*     Desc : rsrcProcInfo
   @brief X2AP Resource Procedure Information 
   @details This structure conatins the eNodeB measure Ids required 
            by Resource Procedure
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
PUBLIC S16 cmPkRsrcProcInfo
(
CztRsrcProcInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRsrcProcInfo(param, mBuf)
CztRsrcProcInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRsrcProcInfo)

   CMCHKPK(SPkU16, param->eNb2MeasId, mBuf);
   CMCHKPK(SPkU16, param->eNb1MeasId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRsrcProcInfo
*
*
*     Desc : rsrcProcInfo
   @brief X2AP Resource Procedure Information 
   @details This structure conatins the eNodeB measure Ids required 
            by Resource Procedure
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
PUBLIC S16 cmUnpkRsrcProcInfo
(
CztRsrcProcInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRsrcProcInfo(param, mBuf)
CztRsrcProcInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRsrcProcInfo)

      
   CMCHKUNPK(SUnpkU16, &param->eNb1MeasId, mBuf);
   CMCHKUNPK(SUnpkU16, &param->eNb2MeasId, mBuf);
   RETVALUE(ROK);
}





/***********************************************************
*
*     Func : cmPkCztLclErrInd
*
*
*     Desc : cztLclErrInd
   @brief X2AP Local Error Indication 
   @details This structure holds the information about the error occured 
            in X2AP Layer.<br>
            For Cause Type please refer to @ref cztmerrtype  <br>
            For Cause Values please refer to @ref cztmerrcause
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
PUBLIC S16 cmPkCztLclErrInd
(
CztLclErrInd *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCztLclErrInd(param, mBuf)
CztLclErrInd *param;
Buffer *mBuf;
#endif
{

   MsgLen msgLen=0;
   TRC3(cmPkCztLclErrInd)
    if(param->rcvBuf!=NULLP)
    {   
       if (SFndLenMsg(param->rcvBuf, &msgLen) != ROK)
          RETVALUE(RFAILED);
       if (SCatMsg(mBuf, param->rcvBuf, M1M2) != ROK)
          RETVALUE(RFAILED);
       SPutMsg(param->rcvBuf);
       param->rcvBuf = NULLP;
    }
   CMCHKPK(SPkS16, msgLen, mBuf);
   if(param->evntPres==TRUE)
   CMCHKPK(cmPkCztEvnt, param->event, mBuf);
   
   CMCHKPK(SPkU8,param->evntPres, mBuf);
   
   switch(param->msgType) 
   {
      case CZT_MSG_HO_REQ:         
      case CZT_MSG_HO_ACK:         
      case CZT_MSG_HO_FAIL:        
      case CZT_MSG_HO_CANCEL:      
      case CZT_MSG_SN_STATUS_TRFR:    
      case CZT_MSG_UE_CXT_RELEASE:    
         CMCHKPK(cmPkCztUeInfo, &param->u.ueInfo, mBuf);
         break;
      case  CZT_MSG_RSRC_ST_REQ:
      case  CZT_MSG_RSRC_ST_RSP:  
      case  CZT_MSG_RSRC_ST_FAIL: 
      case  CZT_MSG_RSRC_ST_UPD:  
      CMCHKPK(cmPkRsrcProcInfo, &param->u.rsrcInfo, mBuf);
         break;
      default :
         break;
   }

   CMCHKPK(SPkU8, param->msgType, mBuf);
   CMCHKPK(SPkU8, param->causeValue, mBuf);
   CMCHKPK(SPkU8, param->causeType, mBuf);
   CMCHKPK(SPkU32, param->peerId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCztLclErrInd
*
*
*     Desc : cztLclErrInd
   @brief X2AP Local Error Indication 
   @details This structure holds the information about the error occured 
            in X2AP Layer.<br>
            For Cause Type please refer to @ref cztmerrtype  <br>
            For Cause Values please refer to @ref cztmerrcause
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
PUBLIC S16 cmUnpkCztLclErrInd
(
CztLclErrInd *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztLclErrInd(param, mBuf)
CztLclErrInd *param;
Buffer *mBuf;
#endif
{

   S16 msgLen;
  MsgLen    totalMsgLen;
   TRC3(cmUnpkCztLclErrInd)

   CMCHKUNPK(SUnpkU32, &param->peerId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->causeType, mBuf);
   CMCHKUNPK(SUnpkU8, &param->causeValue, mBuf);
   CMCHKUNPK(SUnpkU8, &param->msgType, mBuf);

   switch(param->msgType) {
       case CZT_MSG_HO_REQ:         
      case CZT_MSG_HO_ACK:         
      case CZT_MSG_HO_FAIL:        
      case CZT_MSG_HO_CANCEL:      
      case CZT_MSG_SN_STATUS_TRFR:    
      case CZT_MSG_UE_CXT_RELEASE:    
         CMCHKUNPK(cmUnpkCztUeInfo, &param->u.ueInfo, mBuf);
         break;
      case  CZT_MSG_RSRC_ST_REQ:
      case  CZT_MSG_RSRC_ST_RSP:  
      case  CZT_MSG_RSRC_ST_FAIL: 
      case  CZT_MSG_RSRC_ST_UPD:  
         CMCHKUNPK(cmUnpkRsrcProcInfo, &param->u.rsrcInfo, mBuf);
         break;
    default :
     break;  
    }

   CMCHKUNPK(SUnpkU8, &param->evntPres, mBuf);
   if(param->evntPres ==TRUE)
   CMCHKUNPK(cmUnpkCztEvnt, param->event, mBuf);
   CMCHKUNPK(SUnpkS16, &msgLen, mBuf);
   if(msgLen!=0)
   {  
   if (SFndLenMsg(mBuf, &totalMsgLen) != ROK)
      RETVALUE(RFAILED);
   if (SSegMsg(mBuf, totalMsgLen-msgLen, &param->rcvBuf) != ROK)
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCztReTxInfo
*
*
*     Desc : cztReTxInfo
   @brief X2AP Re-transmission 
   @details This structure conatains the information required to re-transmit 
            the X2AP Message
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
PUBLIC S16 cmPkCztReTxInfo
(
CztReTxInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCztReTxInfo(param, mBuf)
CztReTxInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCztReTxInfo)

      switch(param->msgType) 
      {
         case CZT_MSG_RSRC_ST_REQ:   
            CMCHKPK(SPkU16, param->u.eNb1MeasId, mBuf);
            break;
         case CZT_MSG_CFG_UPD_REQ:
         case CZT_MSG_X2_SETUP:
            break;
         default :
            break;
      }

   CMCHKPK(SPkU8, param->msgType, mBuf);
   CMCHKPK(SPkU32, param->peerId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCztReTxInfo
*
*
*     Desc : cztReTxInfo
   @brief X2AP Re-transmission 
   @details This structure conatains the information required to re-transmit 
            the X2AP Message
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
PUBLIC S16 cmUnpkCztReTxInfo
(
CztReTxInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztReTxInfo(param, mBuf)
CztReTxInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCztReTxInfo)

   CMCHKUNPK(SUnpkU32, &param->peerId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->msgType, mBuf);

   switch(param->msgType) 
    {
      case CZT_MSG_RSRC_ST_REQ:   
         CMCHKUNPK(SUnpkU16, &param->u.eNb1MeasId, mBuf);
         break;
      case CZT_MSG_CFG_UPD_REQ:
      case CZT_MSG_X2_SETUP:
         break;
      default :
         break;
    } 

   RETVALUE(ROK);
}







/***********************************************************
*
*     Func : cmPkCztRlsReq
*
*
*     Desc : cztRlsReq
   @brief X2AP Release Request 
   @details This structure contains the information required for Release request.
            For Node Type please refer to @ref cztnodetype
            For Release Type please refer to @ref cztreltype
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
PUBLIC S16 cmPkCztRlsReq
(
CztRlsReq *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCztRlsReq(param, mBuf)
CztRlsReq *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCztRlsReq)

      switch(param->rlsType) 
      {
      case CZT_RELTYPE_UE:
         CMCHKPK(SPkU16, param->u.oldUEX2APId, mBuf);
         break;
      case CZT_RELTYPE_RSRC:
         CMCHKPK(SPkU16, param->u.eNb1MeasId, mBuf);
         break;
      case CZT_RELTYPE_RESET:
      case CZT_RELTYPE_TERM:
         break;
      default :
         break; /* X2AP 1.2 fix for existing testcase */
   }

   CMCHKPK(SPkU8, param->rlsType, mBuf);
   CMCHKPK(SPkU8, param->idType, mBuf);
   CMCHKPK(SPkU32, param->peerId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCztRlsReq
*
*
*     Desc : cztRlsReq
   @brief X2AP Release Request 
   @details This structure contains the information required for Release request.
            For Node Type please refer to @ref cztnodetype
            For Release Type please refer to @ref cztreltype
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
PUBLIC S16 cmUnpkCztRlsReq
(
CztRlsReq *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztRlsReq(param, mBuf)
CztRlsReq *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCztRlsReq)

   CMCHKUNPK(SUnpkU32, &param->peerId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->idType, mBuf);
   CMCHKUNPK(SUnpkU8, &param->rlsType, mBuf);
   switch(param->rlsType) 
   {
      case CZT_RELTYPE_RSRC:
         CMCHKUNPK(SUnpkU16, &param->u.eNb1MeasId, mBuf);
         break;
      case CZT_RELTYPE_UE:
         CMCHKUNPK(SUnpkU16, &param->u.oldUEX2APId, mBuf);
         break;
      case CZT_RELTYPE_RESET:
      case CZT_RELTYPE_TERM:
         break;
      default :
         break; /* X2AP 1.2 fix for existing testcase */
   }

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCztPeerAssocInd
*
*
*     Desc : cztPeerAssocInd
   @brief X2AP Peer Association Indication 
   @details This structure contains the destination Address and Port 
            from which Association request is coming. 
            This is used for dynamic peer when allowed to be condfigured by 
            layer manager.
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
PUBLIC S16 cmPkCztPeerAssocInd
(
CztPeerAssocInd *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCztPeerAssocInd(param, mBuf)
CztPeerAssocInd *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCztPeerAssocInd)

   CMCHKPK(SPkU16, param->dstPort, mBuf);
   CMCHKPK(cmPkCztNetAddrLst, &param->dstAddrLst, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCztPeerAssocInd
*
*
*     Desc : cztPeerAssocInd
   @brief X2AP Peer Association Indication 
   @details This structure contains the destination Address and Port 
            from which Association request is coming. 
            This is used for dynamic peer when allowed to be condfigured by 
            layer manager.
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
PUBLIC S16 cmUnpkCztPeerAssocInd
(
CztPeerAssocInd *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztPeerAssocInd(param, mBuf)
CztPeerAssocInd *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCztPeerAssocInd)

   CMCHKUNPK(cmUnpkCztNetAddrLst, &param->dstAddrLst, mBuf);
   CMCHKUNPK(SUnpkU16, &param->dstPort, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCztPeerAssocRsp
*
*
*     Desc : cztPeerAssocRsp
   @brief X2AP Peer Association Response
   @details This structures contains the information for Peer Association 
            Response. This is used for dynamic peer when allowed to be condfigured by 
            layer manager.
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
PUBLIC S16 cmPkCztPeerAssocRsp
(
CztPeerAssocRsp *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCztPeerAssocRsp(param, mBuf)
CztPeerAssocRsp *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCztPeerAssocRsp)

   CMCHKPK(cmPkCztReqStatus, &param->status, mBuf);
   CMCHKPK(SPkU16, param->locOutStrms, mBuf);
   CMCHKPK(SPkU16, param->globalStreamId, mBuf);
   CMCHKPK(cmPkCmNetAddr, &param->priDstAddr, mBuf);
   CMCHKPK(SPkU16, param->dstPort, mBuf);
   CMCHKPK(cmPkCztNetAddrLst, &param->dstAddrLst, mBuf);
   CMCHKPK(SPkU32, param->peerId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCztPeerAssocRsp
*
*
*     Desc : cztPeerAssocRsp
   @brief X2AP Peer Association Response
   @details This structures contains the information for Peer Association 
            Response. This is used for dynamic peer when allowed to be condfigured by 
            layer manager.
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
PUBLIC S16 cmUnpkCztPeerAssocRsp
(
CztPeerAssocRsp *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCztPeerAssocRsp(param, mBuf)
CztPeerAssocRsp *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCztPeerAssocRsp)

   CMCHKUNPK(SUnpkU32, &param->peerId, mBuf);
   CMCHKUNPK(cmUnpkCztNetAddrLst, &param->dstAddrLst, mBuf);
   CMCHKUNPK(SUnpkU16, &param->dstPort, mBuf);
   CMCHKUNPK(cmUnpkCmNetAddr, &param->priDstAddr, mBuf);
   CMCHKUNPK(SUnpkU16, &param->globalStreamId, mBuf);
   CMCHKUNPK(SUnpkU16, &param->locOutStrms, mBuf);
   CMCHKUNPK(cmUnpkCztReqStatus, &param->status, mBuf);
   RETVALUE(ROK);
}


#endif



/**********************************************************************
    
           End of file:     czt.c@@/main/3 - Thu Aug 25 18:15:05 2011
              
**********************************************************************/

/**********************************************************************
          Revision History:

**********************************************************************/
/********************************************************************90**
   
       ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     ds              1. LTE-X2AP Initial Release.
/main/2      ---      czt_c_001.main_1 mm              1. CR Fixes, Memory Leak fixes.
/main/3      ---      czt_c_001.main_2  pt        1. Updated for release of X2AP 3.1.
/main/3      ---      czt_c_001.main_3  akaranth  1. freeing the audReq structure in 
                                                     function cmPkCztAudReq.
*********************************************************************91*/
