

/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for pack/unpack of RGR interface primitives. 
  
     File:     rgr.c 
 
     Sid:      rgr.c@@/main/10 - Wed Jul 27 13:52:30 2011
  
     Prg:      sm
  
**********************************************************************/

/** @file rgr.c
@brief This file contains the packing/unpacking code for the RGR interface 
       primitives.
*/
/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_tkns.h"       /* Common Token Defines */
#include "cm_llist.h"      /* Common Link List Defines */
#include "cm_hash.h"       /* Common Hash List Defines */
#include "cm_lte.h"        /* Common LTE Defines */
/* LTE_ADV_FLAG_REMOVED_START */
#include "cm_mblk.h"
/* LTE_ADV_FLAG_REMOVED_END */
#include "rgr.h"           /* RGR Interface defines */

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_lib.x"        /* Common Library Definitions */
#include "cm_hash.x"       /* Common Hash List Definitions */
#include "cm_lte.x"        /* Common LTE Defines */
/* LTE_ADV_FLAG_REMOVED_START */
#include "cm_mblk.x"
/* LTE_ADV_FLAG_REMOVED_END */
#include "rgr.x"           /* RGR Interface includes */

#if defined(LCRGR)


/***********************************************************
*
*     Func : cmPkRgrBndReq
*
*
*     Desc : Request from RRM to MAC to bind the interface saps
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
PUBLIC S16 cmPkRgrBndReq
(
Pst* pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 cmPkRgrBndReq(pst, suId, spId)
Pst* pst;
SuId suId;
SpId spId;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkRgrBndReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR001, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR002, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR003, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTRGRBNDREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkRgrBndReq
*
*
*     Desc : Request from RRM to MAC to bind the interface saps
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
PUBLIC S16 cmUnpkRgrBndReq
(
RgrBndReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrBndReq(func, pst, mBuf)
RgrBndReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   SpId spId;
   
   TRC3(cmUnpkRgrBndReq)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR004, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR005, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, spId));
}


/***********************************************************
*
*     Func : cmPkRgrBndCfm
*
*
*     Desc : Confirmation from MAC to RRM for the bind/Unbind 
 * request for the interface saps
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
PUBLIC S16 cmPkRgrBndCfm
(
Pst* pst,
SuId suId,
U8 status
)
#else
PUBLIC S16 cmPkRgrBndCfm(pst, suId, status)
Pst* pst;
SuId suId;
U8 status;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkRgrBndCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR006, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SPkU8(status, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR007, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR008, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTRGRBNDCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkRgrBndCfm
*
*
*     Desc : Confirmation from MAC to RRM for the bind/Unbind 
 * request for the interface saps
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
PUBLIC S16 cmUnpkRgrBndCfm
(
RgrBndCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrBndCfm(func, pst, mBuf)
RgrBndCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   U8 status;
   
   TRC3(cmUnpkRgrBndCfm)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR009, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkU8(&status, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR010, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, status));
}


/***********************************************************
*
*     Func : cmPkRgrUbndReq
*
*
*     Desc : Request from RRM to MAC to Unbind the interface saps
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
PUBLIC S16 cmPkRgrUbndReq
(
Pst* pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 cmPkRgrUbndReq(pst, spId, reason)
Pst* pst;
SpId spId;
Reason reason;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkRgrUbndReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR011, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SPkS16(reason, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR012, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR013, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTRGRUBNDREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkRgrUbndReq
*
*
*     Desc : Request from RRM to MAC to Unbind the interface saps
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
PUBLIC S16 cmUnpkRgrUbndReq
(
RgrUbndReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUbndReq(func, pst, mBuf)
RgrUbndReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   Reason reason;
   
   TRC3(cmUnpkRgrUbndReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR014, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkS16(&reason, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR015, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, reason));
}


/***********************************************************
*
*     Func : cmPkRgrCfgReq
*
*
*     Desc : Configuration Request from RRM to MAC for 
 * configuring Cell/Ue/Lc
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
PUBLIC S16 cmPkRgrCfgReq
(
Pst* pst,
SpId spId,
RgrCfgTransId transId,
RgrCfgReqInfo * cfgReqInfo
)
#else
PUBLIC S16 cmPkRgrCfgReq(pst, spId, transId, cfgReqInfo)
Pst* pst;
SpId spId;
RgrCfgTransId transId;
RgrCfgReqInfo * cfgReqInfo;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkRgrCfgReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR016, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)cfgReqInfo, sizeof(RgrCfgReqInfo));
      RETVALUE(RFAILED);
   }
   if (cmPkRgrCfgReqInfo(cfgReqInfo, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR017, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)cfgReqInfo, sizeof(RgrCfgReqInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmPkRgrCfgTransId(&transId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR018, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)cfgReqInfo, sizeof(RgrCfgReqInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR019, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)cfgReqInfo, sizeof(RgrCfgReqInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPutSBuf(pst->region, pst->pool, (Data *)cfgReqInfo, sizeof(RgrCfgReqInfo)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR020, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) EVTRGRCFGREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkRgrCfgReq
*
*
*     Desc : Configuration Request from RRM to MAC for 
 * configuring Cell/Ue/Lc
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
PUBLIC S16 cmUnpkRgrCfgReq
(
RgrCfgReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrCfgReq(func, pst, mBuf)
RgrCfgReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   RgrCfgTransId transId;
   RgrCfgReqInfo *cfgReqInfo;
   
   TRC3(cmUnpkRgrCfgReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR021, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmUnpkRgrCfgTransId(&transId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR022, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfgReqInfo,sizeof(RgrCfgReqInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR023, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   cmMemset((U8 *)cfgReqInfo, 0, sizeof(RgrCfgReqInfo));
   if (pst->selector == RGR_SEL_LC) 
      if (cmUnpkRgrCfgReqInfo(cfgReqInfo, mBuf) != ROK) {
         SPutSBuf(pst->region, pst->pool, (Data *)cfgReqInfo, sizeof(RgrCfgReqInfo));
         SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ERGR024, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, transId, cfgReqInfo));
}

/* rgr_c_001.main_3: Added TTI indication from MAC to RGR user */

/***********************************************************
*
*     Func : cmPkRgrTtiIndInfo
*
*
*     Desc : Packs the TTI indication information.
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
PUBLIC S16 cmPkRgrTtiIndInfo
(
RgrTtiIndInfo *param,
Buffer        *mBuf
)
#else
PUBLIC S16 cmPkRgrTtiIndInfo(param, mBuf)
RgrTtiIndInfo *param;
Buffer        *mBuf;
#endif
{
   TRC3(cmPkRgrTtiInd)
   CMCHKPK(SPkU16, param->sfn, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmUnpkRgrTtiIndInfo
*
*
*     Desc : Unpacking for RgrTtiIndInfo
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgrTtiIndInfo
(
RgrTtiIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrTtiIndInfo(param, mBuf)
RgrTtiIndInfo *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkRgrTtiIndInfo)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(SUnpkU16, &param->sfn, mBuf);
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkRgrTtiInd
*
*
*     Desc : TTI indication  from MAC to RRM
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
PUBLIC S16 cmPkRgrTtiInd
(
Pst* pst,
SuId suId,
RgrTtiIndInfo *ttiInd
)
#else
PUBLIC S16 cmPkRgrTtiInd(pst, suId, ttiInd)
Pst* pst;
SuId suId;
RgrTtiIndInfo *ttiInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkRgrTtiInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR025, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmPkRgrTtiIndInfo(ttiInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR026, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)ttiInd, sizeof(RgrTtiIndInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR027, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)ttiInd, sizeof(RgrTtiIndInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   SPutSBuf(pst->region, pst->pool, (Data *)ttiInd, sizeof(RgrTtiIndInfo));
   pst->event = (Event) EVTRGRTTIIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkRgrTtiInd
*
*
*     Desc : TTI indication from MAC to RRM
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
PUBLIC S16 cmUnpkRgrTtiInd
(
RgrTtiInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrTtiInd(func, pst, mBuf)
RgrTtiInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   RgrTtiIndInfo *ttiInd;
   
   TRC3(cmUnpkRgrTtiInd)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR028, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if ((SGetSBuf(pst->region, pst->pool, (Data **)&ttiInd, sizeof(RgrTtiIndInfo))) != ROK) 
   {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGR029, (ErrVal)0, "UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
 
   if (cmUnpkRgrTtiIndInfo(ttiInd, mBuf) != ROK) {
      /*ccpu00114888- Memory Leak issue- Start*/
      SPutSBuf(pst->region, pst->pool, (Data *)ttiInd, 
            sizeof(RgrTtiIndInfo));
      /*ccpu00114888- Memory Leak issue- End*/
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR030, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, ttiInd));
}


/***********************************************************
*
*     Func : cmPkRgrCfgCfm
*
*
*     Desc : Configuration Confirm from MAC to RRM
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
PUBLIC S16 cmPkRgrCfgCfm
(
Pst* pst,
SuId suId,
RgrCfgTransId transId,
U8 status
)
#else
PUBLIC S16 cmPkRgrCfgCfm(pst, suId, transId, status)
Pst* pst;
SuId suId;
RgrCfgTransId transId;
U8 status;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkRgrCfgCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR031, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SPkU8(status, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR032, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmPkRgrCfgTransId(&transId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR033, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR034, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTRGRCFGCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkRgrCfgCfm
*
*
*     Desc : Configuration Confirm from MAC to RRM
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
PUBLIC S16 cmUnpkRgrCfgCfm
(
RgrCfgCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrCfgCfm(func, pst, mBuf)
RgrCfgCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   RgrCfgTransId transId;
   U8 status;
   
   TRC3(cmUnpkRgrCfgCfm)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR035, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmUnpkRgrCfgTransId(&transId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR036, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkU8(&status, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR037, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, transId, status));
}

/* rgr_c_001.main_4: ADD-Added for SI Enhancement. */
#ifdef RGR_SI_SCH
/***********************************************************
*
*     Func : cmPkRgrSiCfgCfm
*
*
*     Desc : SI Configuration Confirm from MAC to RRM
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
PUBLIC S16 cmPkRgrSiCfgCfm
(
Pst* pst,
SuId suId,
RgrCfgTransId transId,
U8 status
)
#else
PUBLIC S16 cmPkRgrSiCfgCfm(pst, suId, transId, status)
Pst* pst;
SuId suId;
RgrCfgTransId transId;
U8 status;
#endif
{
   Buffer *mBuf = NULLP;

   TRC3(cmPkRgrSiCfgCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR038, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SPkU8(status, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR039, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmPkRgrCfgTransId(&transId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR040, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR041, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) EVTRGRSICFGCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkRgrSiCfgCfm
*
*
*     Desc : Configuration Confirm from MAC to RRM
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
PUBLIC S16 cmUnpkRgrSiCfgCfm
(
RgrSiCfgCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrSiCfgCfm(func, pst, mBuf)
RgrSiCfgCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   RgrCfgTransId transId;
   U8 status;
   
   TRC3(cmUnpkRgrSiCfgCfm)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR042, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmUnpkRgrCfgTransId(&transId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR043, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkU8(&status, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR044, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, transId, status));
}
#endif/*RGR_SI_SCH*/


/***********************************************************
*
*     Func : cmPkRgrCfgTransId
*
*
*     Desc : Transaction ID between MAC and RRM
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
PUBLIC S16 cmPkRgrCfgTransId
(
RgrCfgTransId *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrCfgTransId(param, mBuf)
RgrCfgTransId *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkRgrCfgTransId)

   for (i=RGR_CFG_TRANSID_SIZE-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->trans[i], mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrCfgTransId
*
*
*     Desc : Transaction ID between MAC and RRM
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
PUBLIC S16 cmUnpkRgrCfgTransId
(
RgrCfgTransId *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrCfgTransId(param, mBuf)
RgrCfgTransId *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkRgrCfgTransId)

   for (i=0; i<RGR_CFG_TRANSID_SIZE; i++) {
      CMCHKUNPK(SUnpkU8, &param->trans[i], mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrDlHqCfg
*
*
*     Desc :  Downlink HARQ configuration per Cell
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
PUBLIC S16 cmPkRgrDlHqCfg
(
RgrDlHqCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrDlHqCfg(param, mBuf)
RgrDlHqCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrDlHqCfg)

   CMCHKPK(SPkU8, param->maxMsg4HqTx, mBuf);
   CMCHKPK(SPkU8, param->maxDlHqTx, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrDlHqCfg
*
*
*     Desc :  Downlink HARQ configuration per Cell
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
PUBLIC S16 cmUnpkRgrDlHqCfg
(
RgrDlHqCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrDlHqCfg(param, mBuf)
RgrDlHqCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrDlHqCfg)

   CMCHKUNPK(SUnpkU8, &param->maxDlHqTx, mBuf);
   CMCHKUNPK(SUnpkU8, &param->maxMsg4HqTx, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrRntiCfg
*
*
*     Desc : Range of RNTIs managed by MAC
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
PUBLIC S16 cmPkRgrRntiCfg
(
RgrRntiCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrRntiCfg(param, mBuf)
RgrRntiCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrRntiCfg)

   CMCHKPK(SPkU16, param->size, mBuf);
   CMCHKPK(cmPkLteRnti, param->startRnti, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrRntiCfg
*
*
*     Desc : Range of RNTIs managed by MAC
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
PUBLIC S16 cmUnpkRgrRntiCfg
(
RgrRntiCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrRntiCfg(param, mBuf)
RgrRntiCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrRntiCfg)

   CMCHKUNPK(cmUnpkLteRnti, &param->startRnti, mBuf);
   CMCHKUNPK(SUnpkU16, &param->size, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrDlCmnCodeRateCfg
*
*
*     Desc : Downlink common channel code rate configuration per cell
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
PUBLIC S16 cmPkRgrDlCmnCodeRateCfg
(
RgrDlCmnCodeRateCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrDlCmnCodeRateCfg(param, mBuf)
RgrDlCmnCodeRateCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrDlCmnCodeRateCfg)

   CMCHKPK(SPkU8, param->ccchCqi, mBuf);
   CMCHKPK(SPkU16, param->pdcchCodeRate, mBuf);
   CMCHKPK(SPkU16, param->bcchPchRaCodeRate, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrDlCmnCodeRateCfg
*
*
*     Desc : Downlink common channel code rate configuration per cell
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
PUBLIC S16 cmUnpkRgrDlCmnCodeRateCfg
(
RgrDlCmnCodeRateCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrDlCmnCodeRateCfg(param, mBuf)
RgrDlCmnCodeRateCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrDlCmnCodeRateCfg)

   CMCHKUNPK(SUnpkU16, &param->bcchPchRaCodeRate, mBuf);
   CMCHKUNPK(SUnpkU16, &param->pdcchCodeRate, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ccchCqi, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrCfiCfg
*
*
*     Desc : Control Format Indicator (CFI) configuration per cell
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
PUBLIC S16 cmPkRgrCfiCfg
(
RgrCfiCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrCfiCfg(param, mBuf)
RgrCfiCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrCfiCfg)

   CMCHKPK(SPkU8, param->cfi, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrCfiCfg
*
*
*     Desc : Control Format Indicator (CFI) configuration per cell
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
PUBLIC S16 cmUnpkRgrCfiCfg
(
RgrCfiCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrCfiCfg(param, mBuf)
RgrCfiCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrCfiCfg)

   CMCHKUNPK(SUnpkU8, &param->cfi, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrPuschSubBandCfg
*
*
*     Desc : PUSCH sub-band configuration per cell
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
PUBLIC S16 cmPkRgrPuschSubBandCfg
(
RgrPuschSubBandCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrPuschSubBandCfg(param, mBuf)
RgrPuschSubBandCfg *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkRgrPuschSubBandCfg)

   for (i=param->numSubbands-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->dmrs[i], mBuf);
   }
   CMCHKPK(SPkU8, param->size, mBuf);
   CMCHKPK(SPkU8, param->numSubbands, mBuf);
   CMCHKPK(SPkU8, param->subbandStart, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrPuschSubBandCfg
*
*
*     Desc : PUSCH sub-band configuration per cell
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
PUBLIC S16 cmUnpkRgrPuschSubBandCfg
(
RgrPuschSubBandCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrPuschSubBandCfg(param, mBuf)
RgrPuschSubBandCfg *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkRgrPuschSubBandCfg)

   CMCHKUNPK(SUnpkU8, &param->subbandStart, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numSubbands, mBuf);
   CMCHKUNPK(SUnpkU8, &param->size, mBuf);
   for (i=0; i<param->numSubbands; i++) {
      CMCHKUNPK(SUnpkU8, &param->dmrs[i], mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrUlCmnCodeRateCfg
*
*
*     Desc : Uplink common channel code rate configuration per cell
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
PUBLIC S16 cmPkRgrUlCmnCodeRateCfg
(
RgrUlCmnCodeRateCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUlCmnCodeRateCfg(param, mBuf)
RgrUlCmnCodeRateCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrUlCmnCodeRateCfg)

   CMCHKPK(SPkU8, param->ccchCqi, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrUlCmnCodeRateCfg
*
*
*     Desc : Uplink common channel code rate configuration per cell
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
PUBLIC S16 cmUnpkRgrUlCmnCodeRateCfg
(
RgrUlCmnCodeRateCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUlCmnCodeRateCfg(param, mBuf)
RgrUlCmnCodeRateCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrUlCmnCodeRateCfg)

   CMCHKUNPK(SUnpkU8, &param->ccchCqi, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrUlTrgCqiCfg
*
*
*     Desc : Target Uplink CQI to achieve through group power control configured per cell
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
PUBLIC S16 cmPkRgrUlTrgCqiCfg
(
RgrUlTrgCqiCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUlTrgCqiCfg(param, mBuf)
RgrUlTrgCqiCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrUlTrgCqiCfg)

   CMCHKPK(SPkU8, param->trgCqi, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrUlTrgCqiCfg
*
*
*     Desc : Target Uplink CQI to achieve through group power control configured per cell
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
PUBLIC S16 cmUnpkRgrUlTrgCqiCfg
(
RgrUlTrgCqiCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUlTrgCqiCfg(param, mBuf)
RgrUlTrgCqiCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrUlTrgCqiCfg)

   CMCHKUNPK(SUnpkU8, &param->trgCqi, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrBwCfg
*
*
*     Desc : Bandwidth configuration per cell
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
PUBLIC S16 cmPkRgrBwCfg
(
RgrBwCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrBwCfg(param, mBuf)
RgrBwCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrBwCfg)

   CMCHKPK(SPkU8, param->ulTotalBw, mBuf);
   CMCHKPK(SPkU8, param->dlTotalBw, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrBwCfg
*
*
*     Desc : Bandwidth configuration per cell
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
PUBLIC S16 cmUnpkRgrBwCfg
(
RgrBwCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrBwCfg(param, mBuf)
RgrBwCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrBwCfg)

   CMCHKUNPK(SUnpkU8, &param->dlTotalBw, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ulTotalBw, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrPhichCfg
*
*
*     Desc : PHICH configuration per cell
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
PUBLIC S16 cmPkRgrPhichCfg
(
RgrPhichCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrPhichCfg(param, mBuf)
RgrPhichCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrPhichCfg)

   CMCHKPK(SPkU8, param->isDurExtend, mBuf);
   CMCHKPK(SPkU32, param->ngEnum, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrPhichCfg
*
*
*     Desc : PHICH configuration per cell
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
PUBLIC S16 cmUnpkRgrPhichCfg
(
RgrPhichCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrPhichCfg(param, mBuf)
RgrPhichCfg *param;
Buffer *mBuf;
#endif
{
   U32 tmpEnum;

   TRC3(cmUnpkRgrPhichCfg)

   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->ngEnum = (RgrPhichNg) tmpEnum;
   CMCHKUNPK(SUnpkU8, &param->isDurExtend, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrPucchCfg
*
*
*     Desc : PUCCH configuration per cell
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
PUBLIC S16 cmPkRgrPucchCfg
(
RgrPucchCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrPucchCfg(param, mBuf)
RgrPucchCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrPucchCfg)

   CMCHKPK(SPkU8, param->maxPucchRb, mBuf);
   CMCHKPK(SPkU8, param->cyclicShift, mBuf);
   CMCHKPK(SPkU8, param->deltaShift, mBuf);
   CMCHKPK(SPkU16, param->n1PucchAn, mBuf);
   CMCHKPK(SPkU8, param->resourceSize, mBuf);

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrPucchCfg
*
*
*     Desc : PUCCH configuration per cell
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
PUBLIC S16 cmUnpkRgrPucchCfg
(
RgrPucchCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrPucchCfg(param, mBuf)
RgrPucchCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrPucchCfg)

   CMCHKUNPK(SUnpkU8, &param->resourceSize, mBuf);
   CMCHKUNPK(SUnpkU16, &param->n1PucchAn, mBuf);
   CMCHKUNPK(SUnpkU8, &param->deltaShift, mBuf);
   CMCHKUNPK(SUnpkU8, &param->cyclicShift, mBuf);
   CMCHKUNPK(SUnpkU8, &param->maxPucchRb, mBuf);

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrSrsCfg
*
*
*     Desc : SRS configuration per cell
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
PUBLIC S16 cmPkRgrSrsCfg
(
RgrSrsCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrSrsCfg(param, mBuf)
RgrSrsCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrSrsCfg)

   CMCHKPK(SPkU8, param->srsSubFrameCfg, mBuf);
   CMCHKPK(SPkU32, param->srsBwEnum, mBuf);
   CMCHKPK(SPkU32, param->srsCfgPrdEnum, mBuf);
   CMCHKPK(SPkU8, param->isSrsCfgSetup, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrSrsCfg
*
*
*     Desc : SRS configuration per cell
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
PUBLIC S16 cmUnpkRgrSrsCfg
(
RgrSrsCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrSrsCfg(param, mBuf)
RgrSrsCfg *param;
Buffer *mBuf;
#endif
{
   U32 tmpEnum;

   TRC3(cmUnpkRgrSrsCfg)

   CMCHKUNPK(SUnpkU8, &param->isSrsCfgSetup, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->srsCfgPrdEnum = (RgrSrsCfgPrd) tmpEnum;
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->srsBwEnum = (RgrSrsBwCfg) tmpEnum;
   CMCHKUNPK(SUnpkU8, &param->srsSubFrameCfg, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrRachCfg
*
*
*     Desc : RACH configuration per cell
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
PUBLIC S16 cmPkRgrRachCfg
(
RgrRachCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrRachCfg(param, mBuf)
RgrRachCfg *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkRgrRachCfg)

   CMCHKPK(SPkU8, param->prachResource, mBuf);
   CMCHKPK(SPkU16, param->msgSizeGrpA, mBuf);
   CMCHKPK(SPkU8, param->sizeRaPreambleGrpA, mBuf);
   CMCHKPK(SPkU8, param->numRaPreamble, mBuf);
   CMCHKPK(SPkU8, param->maxMsg3Tx, mBuf);
      for (i=param->raOccasion.size-1; i >= 0; i--) {
         CMCHKPK(SPkU8, param->raOccasion.subFrameNum[i], mBuf);
      }
      CMCHKPK(SPkU32, param->raOccasion.sfnEnum, mBuf);
      CMCHKPK(SPkU8, param->raOccasion.size, mBuf);
   CMCHKPK(SPkU8, param->raWinSize, mBuf);
   CMCHKPK(SPkU8, param->preambleFormat, mBuf);
#ifdef RGR_V1
   /* rgr_c_001.main_5: cccpu00112372: Added contention resolution 
    * timer configuration */
   CMCHKPK(SPkU8, param->contResTmr, mBuf);
#endif
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrRachCfg
*
*
*     Desc : RACH configuration per cell
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
PUBLIC S16 cmUnpkRgrRachCfg
(
RgrRachCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrRachCfg(param, mBuf)
RgrRachCfg *param;
Buffer *mBuf;
#endif
{
   U32 tmpEnum;

   S32 i;
   TRC3(cmUnpkRgrRachCfg)
#ifdef RGR_V1 
   /* rgr_c_001.main_5: cccpu00112372: Added contention resolution 
    * timer configuration */
   CMCHKUNPK(SUnpkU8, &param->contResTmr, mBuf);
#endif
   CMCHKUNPK(SUnpkU8, &param->preambleFormat, mBuf);
   CMCHKUNPK(SUnpkU8, &param->raWinSize, mBuf);
      CMCHKUNPK(SUnpkU8, &param->raOccasion.size, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->raOccasion.sfnEnum = (RgrRaSfn) tmpEnum;
      for (i=0; i<param->raOccasion.size; i++) {
         CMCHKUNPK(SUnpkU8, &param->raOccasion.subFrameNum[i], mBuf);
      }
   CMCHKUNPK(SUnpkU8, &param->maxMsg3Tx, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numRaPreamble, mBuf);
   CMCHKUNPK(SUnpkU8, &param->sizeRaPreambleGrpA, mBuf);
   CMCHKUNPK(SUnpkU16, &param->msgSizeGrpA, mBuf);
   CMCHKUNPK(SUnpkU8, &param->prachResource, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrSiCfg
*
*
*     Desc : SI Configuration per cell
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
PUBLIC S16 cmPkRgrSiCfg
(
RgrSiCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrSiCfg(param, mBuf)
RgrSiCfg *param;
Buffer *mBuf;
#endif
{
   /* rgr_c_001.main_4:MOD-Modified for SI Enhancement. */
#ifdef RGR_SI_SCH
   S16 idx;
#endif/*RGR_SI_SCH*/

   TRC3(cmPkRgrSiCfg)

#ifdef RGR_SI_SCH
   if(param->numSi > sizeof(param->siPeriodicity)/
                       sizeof(param->siPeriodicity[0]))
      param->numSi = sizeof(param->siPeriodicity)/
                       sizeof(param->siPeriodicity[0]);

   for (idx=param->numSi-1; idx >= 0; idx--) {
   /* Enum to be packed/unpacked as U32 instead of S32 */
      CMCHKPK(SPkU32, param->siPeriodicity[idx], mBuf);
   }
   CMCHKPK(SPkU8, param->numSi, mBuf);
   /*rgr_c_001.main_9 ccpu00115364 MOD changed modPrd to enum*/
   CMCHKPK(SPkU32, (U32)param->modPrd, mBuf);
#endif/*RGR_SI_SCH*/
   CMCHKPK(SPkU8, param->retxCnt, mBuf);
   CMCHKPK(SPkU8, param->siWinSize, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrSiCfg
*
*
*     Desc : SI Configuration per cell
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
PUBLIC S16 cmUnpkRgrSiCfg
(
RgrSiCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrSiCfg(param, mBuf)
RgrSiCfg *param;
Buffer *mBuf;
#endif
{
   U32 tmpEnum;
   /* rgr_c_001.main_4:MOD-Modified for SI Enhancement. */
#ifdef RGR_SI_SCH
   S16 idx;
#endif/*RGR_SI_SCH*/

   TRC3(cmUnpkRgrSiCfg)

   CMCHKUNPK(SUnpkU8, &param->siWinSize, mBuf);
   CMCHKUNPK(SUnpkU8, &param->retxCnt, mBuf);
#ifdef RGR_SI_SCH
   /*rgr_c_001.main_9 ccpu00115364 MOD changed modPrd to enum*/
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->modPrd = (RgrModPeriodicity) tmpEnum;
   CMCHKUNPK(SUnpkU8, &param->numSi, mBuf);

   if(param->numSi > sizeof(param->siPeriodicity)/
                       sizeof(param->siPeriodicity[0]))
      param->numSi = sizeof(param->siPeriodicity)/
                       sizeof(param->siPeriodicity[0]);

   /* Enum to be packed/unpacked as U32 instead of S32 */
   for (idx=0; idx < param->numSi; idx++) {
      CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
      param->siPeriodicity[idx] = (RgrSiPeriodicity) tmpEnum;
   }
#endif/*RGR_SI_SCH*/

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrTpcRntiCfg
*
*
*     Desc : TPC RNTI Range
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
PUBLIC S16 cmPkRgrTpcRntiCfg
(
RgrTpcRntiCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrTpcRntiCfg(param, mBuf)
RgrTpcRntiCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrTpcRntiCfg)

   CMCHKPK(SPkU16, param->size, mBuf);
   CMCHKPK(cmPkLteRnti, param->startTpcRnti, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrTpcRntiCfg
*
*
*     Desc : TPC RNTI Range
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
PUBLIC S16 cmUnpkRgrTpcRntiCfg
(
RgrTpcRntiCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrTpcRntiCfg(param, mBuf)
RgrTpcRntiCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrTpcRntiCfg)

   CMCHKUNPK(cmUnpkLteRnti, &param->startTpcRnti, mBuf);
   CMCHKUNPK(SUnpkU16, &param->size, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrUlPwrCfg
*
*
*     Desc : Cell specific power configuration
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
PUBLIC S16 cmPkRgrUlPwrCfg
(
RgrUlPwrCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUlPwrCfg(param, mBuf)
RgrUlPwrCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrUlPwrCfg)

   CMCHKPK(cmPkRgrTpcRntiCfg, &param->puschPwrFmt3a, mBuf);
   CMCHKPK(cmPkRgrTpcRntiCfg, &param->puschPwrFmt3, mBuf);
   CMCHKPK(cmPkRgrTpcRntiCfg, &param->pucchPwrFmt3a, mBuf);
   CMCHKPK(cmPkRgrTpcRntiCfg, &param->pucchPwrFmt3, mBuf);
   CMCHKPK(SPkS8, param->deltaPreambleMsg3, mBuf);
   CMCHKPK(SPkS8, param->p0NominalPucch, mBuf);
   CMCHKPK(SPkU32, param->alpha, mBuf);
   CMCHKPK(SPkS8, param->p0NominalPusch, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrUlPwrCfg
*
*
*     Desc : Cell specific power configuration
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
PUBLIC S16 cmUnpkRgrUlPwrCfg
(
RgrUlPwrCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUlPwrCfg(param, mBuf)
RgrUlPwrCfg *param;
Buffer *mBuf;
#endif
{
   U32 tmpEnum;

   TRC3(cmUnpkRgrUlPwrCfg)

   CMCHKUNPK(SUnpkS8, &param->p0NominalPusch, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->alpha = (RgrPwrAlpha) tmpEnum;
   CMCHKUNPK(SUnpkS8, &param->p0NominalPucch, mBuf);
   CMCHKUNPK(SUnpkS8, &param->deltaPreambleMsg3, mBuf);
   CMCHKUNPK(cmUnpkRgrTpcRntiCfg, &param->pucchPwrFmt3, mBuf);
   CMCHKUNPK(cmUnpkRgrTpcRntiCfg, &param->pucchPwrFmt3a, mBuf);
   CMCHKUNPK(cmUnpkRgrTpcRntiCfg, &param->puschPwrFmt3, mBuf);
   CMCHKUNPK(cmUnpkRgrTpcRntiCfg, &param->puschPwrFmt3a, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrPuschCfg
*
*
*     Desc : brief cell specific hopping configuration
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
PUBLIC S16 cmPkRgrPuschCfg
(
RgrPuschCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrPuschCfg(param, mBuf)
RgrPuschCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrPuschCfg)

   CMCHKPK(SPkU8, param->hopOffst, mBuf);
   CMCHKPK(SPkU8, param->isIntraHop, mBuf);
   CMCHKPK(SPkU8, param->numSubBands, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrPuschCfg
*
*
*     Desc : brief cell specific hopping configuration
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
PUBLIC S16 cmUnpkRgrPuschCfg
(
RgrPuschCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrPuschCfg(param, mBuf)
RgrPuschCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrPuschCfg)

   CMCHKUNPK(SUnpkU8, &param->numSubBands, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isIntraHop, mBuf);
   CMCHKUNPK(SUnpkU8, &param->hopOffst, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrCodeBookRstCfg
*
*
*     Desc : Number of bits in code book for different transmission modes
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
PUBLIC S16 cmPkRgrCodeBookRstCfg
(
RgrCodeBookRstCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrCodeBookRstCfg(param, mBuf)
RgrCodeBookRstCfg *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkRgrCodeBookRstCfg)

   for (i=1-1; i >= 0; i--) {
      CMCHKPK(SPkU32, param->pmiBitMap[i], mBuf);
   }
   CMCHKPK(SPkU8, param->pres, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrCodeBookRstCfg
*
*
*     Desc : Number of bits in code book for different transmission modes
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
PUBLIC S16 cmUnpkRgrCodeBookRstCfg
(
RgrCodeBookRstCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrCodeBookRstCfg(param, mBuf)
RgrCodeBookRstCfg *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkRgrCodeBookRstCfg)

   CMCHKUNPK(SUnpkU8, &param->pres, mBuf);
   for (i=0; i<1; i++) {
      CMCHKUNPK(SUnpkU32, &param->pmiBitMap[i], mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrPreambleSetCfg
*
*
*     Desc : Range of PDCCH Order Preamble Set managed by MAC
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
PUBLIC S16 cmPkRgrPreambleSetCfg
(
RgrPreambleSetCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrPreambleSetCfg(param, mBuf)
RgrPreambleSetCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrPreambleSetCfg)

   CMCHKPK(SPkU8, param->size, mBuf);
   CMCHKPK(SPkU8, param->start, mBuf);
   CMCHKPK(SPkU8, param->pres, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrPreambleSetCfg
*
*
*     Desc : Range of PDCCH Order Preamble Set managed by MAC
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
PUBLIC S16 cmUnpkRgrPreambleSetCfg
(
RgrPreambleSetCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrPreambleSetCfg(param, mBuf)
RgrPreambleSetCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrPreambleSetCfg)

   CMCHKUNPK(SUnpkU8, &param->pres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->start, mBuf);
   CMCHKUNPK(SUnpkU8, &param->size, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrCmnLchCfg
*
*
*     Desc : Logical channel configuration info for common channels
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
PUBLIC S16 cmPkRgrCmnLchCfg
(
RgrCmnLchCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrCmnLchCfg(param, mBuf)
RgrCmnLchCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrCmnLchCfg)

   CMCHKPK(SPkU8, param->ulTrchType, mBuf);
   CMCHKPK(SPkU8, param->dlTrchType, mBuf);
   CMCHKPK(SPkU8, param->dir, mBuf);
   CMCHKPK(cmPkLteLcType, param->lcType, mBuf);
   CMCHKPK(cmPkLteLcId, param->lcId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrCmnLchCfg
*
*
*     Desc : Logical channel configuration info for common channels
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
PUBLIC S16 cmUnpkRgrCmnLchCfg
(
RgrCmnLchCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrCmnLchCfg(param, mBuf)
RgrCmnLchCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrCmnLchCfg)

   CMCHKUNPK(cmUnpkLteLcId, &param->lcId, mBuf);
   CMCHKUNPK(cmUnpkLteLcType, &param->lcType, mBuf);
   CMCHKUNPK(SUnpkU8, &param->dir, mBuf);
   CMCHKUNPK(SUnpkU8, &param->dlTrchType, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ulTrchType, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrDlfsCfg
*
*
*     Desc : RGR configuration for DLFS scheduler
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
PUBLIC S16 cmPkRgrDlfsCfg
(
RgrDlfsCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrDlfsCfg(param, mBuf)
RgrDlfsCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrDlfsCfg)

   CMCHKPK(SPkU8, param->thresholdCqi, mBuf);
   CMCHKPK(SPkU8, param->isDlFreqSel, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrDlfsCfg
*
*
*     Desc : RGR configuration for DLFS scheduler
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
PUBLIC S16 cmUnpkRgrDlfsCfg
(
RgrDlfsCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrDlfsCfg(param, mBuf)
RgrDlfsCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrDlfsCfg)

   CMCHKUNPK(SUnpkU8, &param->isDlFreqSel, mBuf);
   CMCHKUNPK(SUnpkU8, &param->thresholdCqi, mBuf);
   RETVALUE(ROK);
}


#ifdef LTE_TDD

#ifdef LTE_TDD


/***********************************************************
*
*     Func : cmPkRgrTddPrachInfo
*
*
*     Desc : PRACH resource information for TDD
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
PUBLIC S16 cmPkRgrTddPrachInfo
(
RgrTddPrachInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrTddPrachInfo(param, mBuf)
RgrTddPrachInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrTddPrachInfo)

   CMCHKPK(SPkU8, param->ulStartSfIdx, mBuf);
   CMCHKPK(SPkU8, param->halfFrm, mBuf);
   CMCHKPK(SPkU32, param->sfn, mBuf);
   CMCHKPK(SPkU8, param->freqIdx, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrTddPrachInfo
*
*
*     Desc : PRACH resource information for TDD
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
PUBLIC S16 cmUnpkRgrTddPrachInfo
(
RgrTddPrachInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrTddPrachInfo(param, mBuf)
RgrTddPrachInfo *param;
Buffer *mBuf;
#endif
{
   U32 tmpEnum;

   TRC3(cmUnpkRgrTddPrachInfo)

   CMCHKUNPK(SUnpkU8, &param->freqIdx, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->sfn = tmpEnum;
   CMCHKUNPK(SUnpkU8, &param->halfFrm, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ulStartSfIdx, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrTddPrachRscInfo
*
*
*     Desc : Set of PRACH Information for TDD
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
PUBLIC S16 cmPkRgrTddPrachRscInfo
(
RgrTddPrachRscInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrTddPrachRscInfo(param, mBuf)
RgrTddPrachRscInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkRgrTddPrachRscInfo)

   for (i=param->numRsc-1; i >= 0; i--) {
      CMCHKPK(cmPkRgrTddPrachInfo, &param->prachInfo[i], mBuf);
   }
   CMCHKPK(SPkU8, param->numRsc, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrTddPrachRscInfo
*
*
*     Desc : Set of PRACH Information for TDD
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
PUBLIC S16 cmUnpkRgrTddPrachRscInfo
(
RgrTddPrachRscInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrTddPrachRscInfo(param, mBuf)
RgrTddPrachRscInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkRgrTddPrachRscInfo)

   CMCHKUNPK(SUnpkU8, &param->numRsc, mBuf);
   for (i=0; i<param->numRsc; i++) {
      CMCHKUNPK(cmUnpkRgrTddPrachInfo, &param->prachInfo[i], mBuf);
   }
   RETVALUE(ROK);
}


#endif

#endif


/***********************************************************
*
*     Func : cmPkRgrEnbPfs
*
*
*     Desc : PFS Configuration
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
PUBLIC S16 cmPkRgrEnbPfs
(
RgrEnbPfs  *param,
Buffer    *mBuf
)
#else
PUBLIC S16 cmPkRgrEnbPfs(param, mBuf)
RgrEnbPfs  *param;
Buffer    *mBuf;
#endif
{
   S32 idx;
   TRC3(cmPkRgrEnbPfs)
   for(idx = RGR_MAX_NUM_QCI-1; idx >= 0; idx--)
   {
      CMCHKPK(SPkU32, param->qciWgt[idx], mBuf);
   }   
   CMCHKPK(SPkU8, param->fairCoeffi, mBuf);
   CMCHKPK(SPkU8, param->tptCoeffi, mBuf);

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrEnbPfs
*
*
*     Desc : PFS Configuration
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
PUBLIC S16 cmUnpkRgrEnbPfs
(
RgrEnbPfs *param,
Buffer   *mBuf
)
#else
PUBLIC S16 cmUnpkRgrEnbPfs(param, mBuf)
RgrEnbPfs *param;
Buffer *mBuf;
#endif
{
   S32 idx;
   TRC3(cmUnpkRgrEnbPfs)

   CMCHKUNPK(SUnpkU8, &param->tptCoeffi, mBuf);
   CMCHKUNPK(SUnpkU8, &param->fairCoeffi, mBuf);
   for(idx = 0; idx < RGR_MAX_NUM_QCI; idx++)
   {
      CMCHKUNPK(SUnpkU32, &param->qciWgt[idx], mBuf);
   }   
   RETVALUE(ROK);
}

/*rgr_c_001.main_7 - Added support for SPS*/

/***********************************************************
*
*     Func : cmPkRgrSpsCellCfg
*
*
*     Desc : DL SPS configuration parameters per UE 
TODO: Check if this is to be added to re-configuration as well
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
PUBLIC S16 cmPkRgrSpsCellCfg
(
RgrSpsCellCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrSpsCellCfg(param, mBuf)
RgrSpsCellCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrSpsCellCfg)
   CMCHKPK(SPkU16, param->maxSpsUePerUlSf, mBuf);
   CMCHKPK(SPkU16, param->maxSpsUePerDlSf, mBuf);
   CMCHKPK(SPkU8, param->maxSpsDlBw, mBuf);

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrSpsDlCellCfg
*
*
*     Desc : DL SPS configuration parameters per UE 
TODO: Check if this is to be added to re-configuration as well
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
PUBLIC S16 cmUnpkRgrSpsDlCellCfg
(
RgrSpsCellCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrSpsDlCellCfg(param, mBuf)
RgrSpsCellCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrSpsDlCellCfg)

   CMCHKUNPK(SUnpkU8, &param->maxSpsDlBw, mBuf);
   CMCHKUNPK(SUnpkU16, &param->maxSpsUePerDlSf, mBuf);
   CMCHKUNPK(SUnpkU16, &param->maxSpsUePerUlSf, mBuf);
   
   RETVALUE(ROK);
}
/*LAA : functions to pack and unpack LAA params*/
/***********************************************************
*
*     Func : cmPkRgrLteUCellCfg
*
*
*     Desc : LAA configuration for the Cell 
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
PRIVATE S16 cmPkRgrLteUCellCfg
(
RgrLteUCfg *param,
Buffer *mBuf
)
#else
PRIVATE S16 cmPkRgrLteUCellCfg(param, mBuf)
RgrLteUCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrlteUCellCfg)
   CMCHKPK(SPkU8, param->isLaaCell, mBuf);

   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmUnpkRgrLteUCellCfg
*
*
*     Desc : LAA configuration for the cell 
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
PRIVATE S16 cmUnpkRgrLteUCellCfg
(
RgrLteUCfg *param,
Buffer *mBuf
)
#else
PRIVATE S16 cmUnpkRgrLteUCellCfg(param, mBuf)
RgrLteUCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrLteUCellCfg)

   CMCHKUNPK(SUnpkU8, &param->isLaaCell, mBuf);
   
   RETVALUE(ROK);
}

/* LTE_ADV_FLAG_REMOVED_START */
/***********************************************************
 *
 *     Func : cmPkRgrLteAdvancedUeConfig
 *
 *
 *     Desc : PAcks LteAdvancedUeConfig
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
PUBLIC S16 cmPkRgrLteAdvancedUeConfig
(
 RgrLteAdvancedUeConfig *param,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmPkRgrLteAdvancedUeConfig(param, mBuf)
   RgrLteAdvancedUeConfig *param;
   Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrLteAdvancedUeConfig)
   CMCHKPK(SPkU8, param->isUeCellEdge, mBuf);
   CMCHKPK(SPkU8, param->isAbsUe, mBuf);
   CMCHKPK(SPkU32, param->pres, mBuf);
   RETVALUE(ROK);
}

/***********************************************************
 *
 *     Func : cmUnpkRgrLteAdvancedUeConfig
 *
 *
 *     Desc : unpacks LteAdvancedUeConfig
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
PUBLIC S16 cmUnpkRgrLteAdvancedUeConfig
(
 RgrLteAdvancedUeConfig *param,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmUnpkRgrLteAdvancedUeConfig(param, mBuf)
   RgrLteAdvancedUeConfig *param;
   Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrLteAdvancedUeConfig)
   CMCHKUNPK(SUnpkU32, &param->pres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isAbsUe, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isUeCellEdge, mBuf);
   RETVALUE(ROK);
}

/***********************************************************
 *
 *     Func : cmPkRgrAbsConfig
 *
 *
 *     Desc : Packs RgrAbsConfig
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
PUBLIC S16 cmPkRgrAbsConfig
(
 RgrAbsConfig *param,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmPkRgrAbsConfig(param, mBuf)
   RgrAbsConfig *param;
   Buffer *mBuf;
#endif
{
   S8   indx = 0;

   TRC3(cmPkRgrAbsConfig)
   CMCHKPK(SPkU32, (U32)param->status, mBuf);
   for (indx = RGR_ABS_PATTERN_LEN-1; indx >= 0; indx--) 
   {
      CMCHKPK(SPkU8, param->absPattern[(U8)indx], mBuf);
   }

   CMCHKPK(SPkU32, param->absPatternType, mBuf);
   CMCHKPK(SPkU32, param->absLoadPeriodicity, mBuf);

   RETVALUE(ROK);

}
/***********************************************************
 *
 *     Func : cmPkRgrSfrConfig
 *
 *
 *     Desc : Packs RgrSfrConfig
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
PUBLIC S16 cmPkRgrSfrConfig
(
 RgrSfrConfig *param,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmPkRgrSfrConfig(param, mBuf)
   RgrSfrConfig *param;
   Buffer *mBuf;
#endif
{
   TRC3(cmPkRgrSfrConfig)

   CMCHKPK(SPkU32, (U32)param->status, mBuf);
#ifdef TFU_UPGRADE   
   CMCHKPK(SPkU32, param->pwrThreshold.pHigh, mBuf);
   CMCHKPK(SPkU32, param->pwrThreshold.pLow, mBuf);
#endif   
   CMCHKPK(SPkU8, param->cellEdgeRbRange.endRb, mBuf);
   CMCHKPK(SPkU8, param->cellEdgeRbRange.startRb, mBuf);

   RETVALUE(ROK);

}


/***********************************************************
 *
 *     Func : cmPkRgrDsfrConfig
 *
 *
 *     Desc : Packs RgrDsfrConfig
 *
 *
 *     Ret  : S16
 *
 *     Notes:  AIRSPAN_LTE_ADV_DSFR
 *
 *     File  : 
 *
 **********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgrDsfrConfig
(
 RgrDsfrConfig *param,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmPkRgrDsfrConfig(param, mBuf)
   RgrDsfrConfig *param;
   Buffer *mBuf;
#endif
{
   TRC3(cmPkRgrDsfrConfig)

   CMCHKPK(SPkU32, (U32)param->status, mBuf);

   RETVALUE(ROK);

}


/***********************************************************
 *
 *     Func : cmUnpkRgrDsfrConfig
 *
 *
 *     Desc : UnPacks RgrDsfrConfig
 *
 *
 *     Ret  : S16
 *
 *     Notes:  AIRSPAN_LTE_ADV_DSFR
 *
 *     File  : 
 *
 **********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgrDsfrConfig
(
 RgrDsfrConfig *param,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmUnpkRgrDsfrConfig(param, mBuf)
   RgrDsfrConfig *param;
   Buffer *mBuf;
#endif
{
   TRC3(cmUnpkRgrDsfrConfig)

   CMCHKUNPK(SUnpkU32, (U32 *)&param->status, mBuf);
   RETVALUE(ROK);

}


/***********************************************************
 *
 *     Func : cmPkRgrCellLteAdvancedFeatureCfg
 *
 *
 *     Desc : Cell LteAdvancedFeatureCfg
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
PUBLIC S16 cmPkRgrCellLteAdvancedFeatureCfg
(
 RgrLteAdvancedCellConfig *param,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmPkRgrCellLteAdvancedFeatureCfg(param, mBuf)
   RgrLteAdvancedCellConfig *param;
   Buffer *mBuf;
#endif
{
   TRC3(cmPkRgrCellLteAdvancedFeatureCfg)

   CMCHKPK(SPkU32, param->pres, mBuf);
   CMCHKPK(cmPkRgrDsfrConfig, &param->dsfrCfg, mBuf); /*AIRSPAN_LTE_ADV_DSFR*/
   CMCHKPK(cmPkRgrSfrConfig,  &param->sfrCfg, mBuf);
   CMCHKPK(cmPkRgrAbsConfig,  &param->absCfg, mBuf);

   RETVALUE(ROK);

}   


/***********************************************************
 *
 *     Func : cmUnpkRgrAbsConfig
 *
 *
 *     Desc : Unpacks AbsConfig
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
PUBLIC S16 cmUnpkRgrAbsConfig
(
 RgrAbsConfig *param,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmUnpkRgrAbsConfig(param, mBuf)
   RgrAbsConfig *param;
   Buffer *mBuf;
#endif
{

   S8 indx = 0;
   TRC3(cmUnpkRgrAbsConfig)

   CMCHKUNPK(SUnpkU32, &param->absLoadPeriodicity, mBuf);
   CMCHKUNPK(SUnpkU32, &param->absPatternType, mBuf);
   for (indx = 0; indx <RGR_ABS_PATTERN_LEN; indx++) 
   {
      CMCHKUNPK(SUnpkU8, &param->absPattern[(U8)indx], mBuf);
   }
   CMCHKUNPK(SUnpkU32, (U32*)&param->status, mBuf);

   RETVALUE(ROK);

}

/***********************************************************
 *
 *     Func : cmUnpkRgrSfrConfig
 *
 *
 *     Desc : Unpacks SfrConfig
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
PUBLIC S16 cmUnpkRgrSfrConfig
(
 RgrSfrConfig *param,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmUnpkRgrSfrConfig(param, mBuf)
   RgrSfrConfig *param;
   Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrSfrConfig)

   CMCHKUNPK(SUnpkU8, &param->cellEdgeRbRange.startRb, mBuf);
   CMCHKUNPK(SUnpkU8, &param->cellEdgeRbRange.endRb, mBuf);
#ifdef TFU_UPGRADE   
   CMCHKUNPK(SUnpkU32, (U32*)&param->pwrThreshold.pLow, mBuf);
   CMCHKUNPK(SUnpkU32, (U32*)&param->pwrThreshold.pHigh, mBuf);
#endif   
   CMCHKUNPK(SUnpkU32, (U32*)&param->status, mBuf);

   RETVALUE(ROK);
}

/***********************************************************
 *
 *     Func : cmUnpkRgrCellLteAdvancedFeatureCfg
 *
 *
 *     Desc : unpacks LteAdvancedFeatureCfg per cell
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
PUBLIC S16 cmUnpkRgrCellLteAdvancedFeatureCfg
(
 RgrLteAdvancedCellConfig *param,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmUnpkRgrCellLteAdvancedFeatureCfg(param, mBuf)
   RgrLteAdvancedCellConfig *param;
   Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrCellLteAdvancedFeatureCfg)
   CMCHKUNPK(cmUnpkRgrAbsConfig, &param->absCfg, mBuf);
   CMCHKUNPK(cmUnpkRgrSfrConfig, &param->sfrCfg, mBuf);   
   CMCHKUNPK(cmUnpkRgrDsfrConfig, &param->dsfrCfg, mBuf); /*AIRSPAN_LTE_ADV_DSFR*/
   CMCHKUNPK(SUnpkU32, &param->pres, mBuf);

   RETVALUE(ROK);
}

/* LTE_ADV_FLAG_REMOVED_END */

/***********************************************************
*
*     Func : cmPkRgrSchedEnbCfg
*
*     Desc : SCH ENB Configurations 
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgrSchedEnbCfg
(
RgrSchedEnbCfg *param,
Buffer         *mBuf
)
#else
PUBLIC S16 cmPkRgrSchedEnbCfg(param, mBuf)
RgrSchedEnbCfg *param;
Buffer         *mBuf;
#endif
{

   //S32 i;
   TRC3(cmPkRgrSchedEnbCfg)

   CMCHKPK(SPkU32, param->accsMode, mBuf);
   switch(param->ulSchdType) 
   {
      case RGR_SCH_TYPE_PFS:
         CMCHKPK(cmPkRgrEnbPfs, &param->ulSchInfo.ulPfs, mBuf);
         break;
      default :
         break;
   }
   CMCHKPK(SPkU8, param->ulSchdType, mBuf);
   switch(param->dlSchdType) 
   {
      case RGR_SCH_TYPE_PFS:
         CMCHKPK(cmPkRgrEnbPfs, &param->dlSchInfo.dlPfs, mBuf);
         break;
      default :
         break;
   }
   CMCHKPK(SPkU8, param->dlSchdType, mBuf);
   CMCHKPK(SPkU8, param->numTxAntPorts, mBuf);
   RETVALUE(ROK);
} /* cmPkRgrSchedEnbCfg */

/***********************************************************
*
*     Func : cmUnpkRgrSchedEnbCfg
*
*
*     Desc : SCH Enodeb Configuration to SCH
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
PUBLIC S16 cmUnpkRgrSchedEnbCfg
(
RgrSchedEnbCfg *param,
Buffer         *mBuf
)
#else
PUBLIC S16 cmUnpkRgrSchedEnbCfg(param, mBuf)
RgrSchedEnbCfg *param;
Buffer         *mBuf;
#endif
{

   //S32 i;
   U32 tmpEnum;
   TRC3(cmUnpkRgrSchedEnbCfg)

   CMCHKUNPK(SUnpkU8, &param->numTxAntPorts, mBuf);
   CMCHKUNPK(SUnpkU8, &param->dlSchdType, mBuf);
   switch(param->dlSchdType) 
   {
      case RGR_SCH_TYPE_PFS:
         CMCHKUNPK(cmUnpkRgrEnbPfs, &param->dlSchInfo.dlPfs, mBuf);
         break;
      default :
         break;
   }
   CMCHKUNPK(SUnpkU8, &param->ulSchdType, mBuf);
   switch(param->ulSchdType) 
   {
      case RGR_SCH_TYPE_PFS:
         CMCHKUNPK(cmUnpkRgrEnbPfs, &param->ulSchInfo.ulPfs, mBuf);
         break;
      default :
         break;
   }
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->accsMode = (RgrCellAccsMode) tmpEnum;
   RETVALUE(ROK);
} /* cmUnpkRgrSchedEnbCfg */


/***********************************************************
*
*     Func : cmPkRgrCellCfg
*
*
*     Desc : Cell Configuration at RRM
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
PUBLIC S16 cmPkRgrCellCfg
(
RgrCellCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrCellCfg(param, mBuf)
RgrCellCfg *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkRgrCellCfg)

/*LAA: Pack LAA params*/
   CMCHKPK(cmPkRgrLteUCellCfg, &param->lteUCfg, mBuf);
   CMCHKPK(SPkU32, param->msg4pAVal, mBuf);
   CMCHKPK(SPkU8, param->isAutoCfgModeEnb, mBuf);
   CMCHKPK(SPkU8, param->isDynCfiEnb, mBuf);
   CMCHKPK(SPkU16, param->phichTxPwrOffset, mBuf);
   CMCHKPK(SPkU16, param->rarTxPwrOffset, mBuf);
   CMCHKPK(SPkU16, param->pcchTxPwrOffset, mBuf);
   CMCHKPK(SPkU16, param->bcchTxPwrOffset, mBuf);

   CMCHKPK(SPkU16, param->t300TmrVal, mBuf);
/*rgr_c_001.main_7 - Added support for SPS*/
   CMCHKPK(cmPkRgrSpsCellCfg, &param->spsCfg, mBuf);

/* rgr_c_001.main_3: Added TTI indication from MAC to RGR user */
   CMCHKPK(SPkU8, param->rrmTtiIndPrd, mBuf);
#ifdef LTE_TDD
   CMCHKPK(cmPkRgrTddPrachRscInfo, &param->prachRscInfo, mBuf);
   CMCHKPK(SPkU8, param->spclSfCfgIdx, mBuf);
   CMCHKPK(SPkU8, param->ulDlCfgIdx, mBuf);

#endif
   CMCHKPK(cmPkRgrCellCsgParamCfg, &param->csgParamCfg, mBuf);
   for (i=param->numCmnLcs-1; i >= 0; i--) {
      CMCHKPK(cmPkRgrCmnLchCfg, &param->cmnLcCfg[i], mBuf);
   }
   CMCHKPK(SPkU8, param->numCmnLcs, mBuf);
   CMCHKPK(cmPkRgrPreambleSetCfg, &param->macPreambleSet, mBuf);
   CMCHKPK(cmPkRgrPuschCfg, &param->puschCfg, mBuf);
   CMCHKPK(cmPkRgrUlPwrCfg, &param->pwrCfg, mBuf);
   CMCHKPK(cmPkRgrSiCfg, &param->siCfg, mBuf);
   CMCHKPK(cmPkRgrRachCfg, &param->rachCfg, mBuf);
   CMCHKPK(cmPkRgrSrsCfg, &param->srsCfg, mBuf);
   CMCHKPK(cmPkRgrPucchCfg, &param->pucchCfg, mBuf);
   CMCHKPK(cmPkRgrPhichCfg, &param->phichCfg, mBuf);
   /* LTE_ADV_FLAG_REMOVED_START */
   CMCHKPK(cmPkRgrCellLteAdvancedFeatureCfg, &param->rgrLteAdvCfg, mBuf);
   /* LTE_ADV_FLAG_REMOVED_END */
   CMCHKPK(cmPkRgrBwCfg, &param->bwCfg, mBuf);
   CMCHKPK(cmPkRgrDlfsCfg, &param->dlfsCfg, mBuf);
   CMCHKPK(cmPkRgrUlCmnCodeRateCfg, &param->ulCmnCodeRate, mBuf);
   CMCHKPK(cmPkRgrPuschSubBandCfg, &param->puschSubBand, mBuf);
   CMCHKPK(cmPkRgrDlCmnCodeRateCfg, &param->dlCmnCodeRate, mBuf);
   CMCHKPK(cmPkRgrUlTrgCqiCfg, &param->trgUlCqi, mBuf);
   CMCHKPK(cmPkRgrCfiCfg, &param->cfiCfg, mBuf);
   CMCHKPK(cmPkRgrRntiCfg, &param->macRnti, mBuf);
   CMCHKPK(cmPkRgrDlHqCfg, &param->dlHqCfg, mBuf);
   CMCHKPK(SPkU8, param->dlfsSchdType, mBuf);

   CMCHKPK(SPkS8, param->pMax, mBuf);
   CMCHKPK(SPkU8, param->cellModSchm, mBuf);
   CMCHKPK(SPkU8, param->isCpDlExtend, mBuf);
   CMCHKPK(SPkU8, param->isCpUlExtend, mBuf);
   CMCHKPK(SPkU8, param->maxUlUeNewTxPerTti, mBuf);
   CMCHKPK(SPkU8, param->maxDlUeNewTxPerTti, mBuf);
   CMCHKPK(SPkU8, param->maxDlRetxBw, mBuf);
   CMCHKPK(SPkU8, param->maxDlBwPerUe, mBuf);
   CMCHKPK(SPkU8, param->maxUlBwPerUe, mBuf);
   CMCHKPK(SPkU8, param->maxCcchPerDlSf, mBuf);
   CMCHKPK(SPkU8, param->maxUePerDlSf, mBuf);
   CMCHKPK(SPkU8, param->maxUePerUlSf, mBuf);
#ifdef RGR_V1
   /* rgr_x_001.main_7: [ccpu00112789] Added configuration for maximum number
      of  MSG3s */
   CMCHKPK(SPkU8, param->maxMsg3PerUlSf, mBuf);
#endif
   CMCHKPK(SPkU8, param->macInst, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrCellCfg
*
*
*     Desc : Cell Configuration at RRM
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
PUBLIC S16 cmUnpkRgrCellCfg
(
RgrCellCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrCellCfg(param, mBuf)
RgrCellCfg *param;
Buffer *mBuf;
#endif
{

   S32 i;

   TRC3(cmUnpkRgrCellCfg)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->macInst, mBuf);
#ifdef RGR_V1
   /* rgr_x_001.main_7: [ccpu00112789] Added configuration for maximum number
      of  MSG3s */
   CMCHKUNPK(SUnpkU8, &param->maxMsg3PerUlSf, mBuf);
#endif
   CMCHKUNPK(SUnpkU8, &param->maxUePerUlSf, mBuf);
   CMCHKUNPK(SUnpkU8, &param->maxUePerDlSf, mBuf);
   CMCHKUNPK(SUnpkU8, &param->maxCcchPerDlSf, mBuf);
   CMCHKUNPK(SUnpkU8, &param->maxUlBwPerUe, mBuf);
   CMCHKUNPK(SUnpkU8, &param->maxDlBwPerUe, mBuf);
   CMCHKUNPK(SUnpkU8, &param->maxDlRetxBw, mBuf);
   CMCHKUNPK(SUnpkU8, &param->maxDlUeNewTxPerTti, mBuf);
   CMCHKUNPK(SUnpkU8, &param->maxUlUeNewTxPerTti, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isCpUlExtend, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isCpDlExtend, mBuf);
   CMCHKUNPK(SUnpkU8, &param->cellModSchm, mBuf);
   CMCHKUNPK(SUnpkS8, &param->pMax, mBuf);
   CMCHKUNPK(SUnpkU8, &param->dlfsSchdType, mBuf);
   CMCHKUNPK(cmUnpkRgrDlHqCfg, &param->dlHqCfg, mBuf);
   CMCHKUNPK(cmUnpkRgrRntiCfg, &param->macRnti, mBuf);
   CMCHKUNPK(cmUnpkRgrCfiCfg, &param->cfiCfg, mBuf);
   CMCHKUNPK(cmUnpkRgrUlTrgCqiCfg, &param->trgUlCqi, mBuf);
   CMCHKUNPK(cmUnpkRgrDlCmnCodeRateCfg, &param->dlCmnCodeRate, mBuf);
   CMCHKUNPK(cmUnpkRgrPuschSubBandCfg, &param->puschSubBand, mBuf);
   CMCHKUNPK(cmUnpkRgrUlCmnCodeRateCfg, &param->ulCmnCodeRate, mBuf);
   CMCHKUNPK(cmUnpkRgrDlfsCfg, &param->dlfsCfg, mBuf);
   CMCHKUNPK(cmUnpkRgrBwCfg, &param->bwCfg, mBuf);
   /* LTE_ADV_FLAG_REMOVED_START */
   CMCHKUNPK(cmUnpkRgrCellLteAdvancedFeatureCfg, &param->rgrLteAdvCfg, mBuf);
   /* LTE_ADV_FLAG_REMOVED_END */
   CMCHKUNPK(cmUnpkRgrPhichCfg, &param->phichCfg, mBuf);
   CMCHKUNPK(cmUnpkRgrPucchCfg, &param->pucchCfg, mBuf);
   CMCHKUNPK(cmUnpkRgrSrsCfg, &param->srsCfg, mBuf);
   CMCHKUNPK(cmUnpkRgrRachCfg, &param->rachCfg, mBuf);
   CMCHKUNPK(cmUnpkRgrSiCfg, &param->siCfg, mBuf);
   CMCHKUNPK(cmUnpkRgrUlPwrCfg, &param->pwrCfg, mBuf);
   CMCHKUNPK(cmUnpkRgrPuschCfg, &param->puschCfg, mBuf);
   CMCHKUNPK(cmUnpkRgrPreambleSetCfg, &param->macPreambleSet, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numCmnLcs, mBuf);
   for (i=0; i<param->numCmnLcs; i++) {
      CMCHKUNPK(cmUnpkRgrCmnLchCfg, &param->cmnLcCfg[i], mBuf);
   }
   CMCHKUNPK(cmUnpkRgrCellCsgParamCfg, &param->csgParamCfg, mBuf);

#ifdef LTE_TDD
   CMCHKUNPK(SUnpkU8, &param->ulDlCfgIdx, mBuf);
   CMCHKUNPK(SUnpkU8, &param->spclSfCfgIdx, mBuf);
   CMCHKUNPK(cmUnpkRgrTddPrachRscInfo, &param->prachRscInfo, mBuf);

#endif
/* rgr_c_001.main_3: Added TTI indication from MAC to RGR user */
   CMCHKUNPK(SUnpkU8, &param->rrmTtiIndPrd, mBuf);
   /*rgr_c_001.main_7 - Added support for SPS*/
   CMCHKUNPK(cmUnpkRgrSpsDlCellCfg, &param->spsCfg, mBuf);

   CMCHKUNPK(SUnpkU16, &param->t300TmrVal, mBuf);
   CMCHKPK(SUnpkU16, &param->bcchTxPwrOffset, mBuf);
   CMCHKPK(SUnpkU16, &param->pcchTxPwrOffset, mBuf);
   CMCHKPK(SUnpkU16, &param->rarTxPwrOffset, mBuf);
   CMCHKPK(SUnpkU16, &param->phichTxPwrOffset, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isDynCfiEnb, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isAutoCfgModeEnb, mBuf);
   CMCHKPK(SUnpkU32, (U32*)&param->msg4pAVal, mBuf);
   /*LAA: Unpack LAA Cell params*/
   CMCHKUNPK(cmUnpkRgrLteUCellCfg, &param->lteUCfg, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrUeAprdDlCqiCfg
*
*
*     Desc : Downlink Aperiodic CQI reporting related configuration per UE
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
PUBLIC S16 cmPkRgrUeAprdDlCqiCfg
(
RgrUeAprdDlCqiCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeAprdDlCqiCfg(param, mBuf)
RgrUeAprdDlCqiCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrUeAprdDlCqiCfg)
   /*Pack Aperiodic Trigger List only for Pcell */
#ifdef LTE_ADV
   CMCHKPK(SPkU8, param->triggerSet2, mBuf);
   CMCHKPK(SPkU8, param->triggerSet1, mBuf);
#endif

   CMCHKPK(SPkU32, param->aprdModeEnum, mBuf);
   CMCHKPK(SPkU8, param->pres, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrUeAprdDlCqiCfg
*
*
*     Desc : Downlink Aperiodic CQI reporting related configuration per UE
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
PUBLIC S16 cmUnpkRgrUeAprdDlCqiCfg
(
RgrUeAprdDlCqiCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeAprdDlCqiCfg(param, mBuf)
RgrUeAprdDlCqiCfg *param;
Buffer *mBuf;
#endif
{
   U32 tmpEnum;

   TRC3(cmUnpkRgrUeAprdDlCqiCfg)

   CMCHKUNPK(SUnpkU8, &param->pres, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->aprdModeEnum = (RgrAprdCqiMode) tmpEnum;

#ifdef LTE_ADV
   CMCHKUNPK(SUnpkU8, &param->triggerSet1, mBuf);
   CMCHKUNPK(SUnpkU8, &param->triggerSet2, mBuf);
#endif

   RETVALUE(ROK);
}


/* rgr_c_001.main_8. Added changes of TFU_UPGRADE */
#ifndef TFU_UPGRADE


/***********************************************************
*
*     Func : cmPkRgrUePrdDlCqiCfg
*
*
*     Desc : Downlink Periodic CQI reporting related configuration per UE
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
PUBLIC S16 cmPkRgrUePrdDlCqiCfg
(
RgrUePrdDlCqiCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUePrdDlCqiCfg(param, mBuf)
RgrUePrdDlCqiCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrUePrdDlCqiCfg)

   CMCHKPK(SPkU16, param->cqiPmiCfgIdx, mBuf);
   CMCHKPK(SPkU8, param->k, mBuf);
   CMCHKPK(SPkS8, param->cqiOffst, mBuf);
   CMCHKPK(SPkU8, param->subframeOffst, mBuf);
   CMCHKPK(SPkU32, param->prdicityEnum, mBuf);
   CMCHKPK(SPkU32, param->prdModeEnum, mBuf);
   CMCHKPK(SPkU8, param->pres, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrUePrdDlCqiCfg
*
*
*     Desc : Downlink Periodic CQI reporting related configuration per UE
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
PUBLIC S16 cmUnpkRgrUePrdDlCqiCfg
(
RgrUePrdDlCqiCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUePrdDlCqiCfg(param, mBuf)
RgrUePrdDlCqiCfg *param;
Buffer *mBuf;
#endif
{
   U32 tmpEnum;

   TRC3(cmUnpkRgrUePrdDlCqiCfg)

   CMCHKUNPK(SUnpkU8, &param->pres, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->prdModeEnum = tmpEnum;
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->prdicityEnum = tmpEnum;
   CMCHKUNPK(SUnpkU8, &param->subframeOffst, mBuf);
   CMCHKUNPK(SUnpkS8, &param->cqiOffst, mBuf);
   CMCHKUNPK(SUnpkU8, &param->k, mBuf);
   CMCHKUNPK(SUnpkU16, &param->cqiPmiCfgIdx, mBuf);
   RETVALUE(ROK);
}


#endif

/* rgr_c_001.main_8. Added changes of TFU_UPGRADE */
#ifdef TFU_UPGRADE
/***********************************************************
*
*     Func : cmPkRgrUeDlPCqiSetup
*
*
*     Desc : Periodic CQI Setup configuration parameters information
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
PUBLIC S16 cmPkRgrUeDlPCqiSetup
(
RgrUeDlPCqiSetup *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeDlPCqiSetup(param, mBuf)
RgrUeDlPCqiSetup *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrUeDlPCqiSetup)

   CMCHKPK(SPkU32, param->prdModeEnum, mBuf);
   CMCHKPK(SPkU8, param->sANCQI, mBuf);
   /*rgr_c_001.main_9 DEL removed unwanted comments*/
   CMCHKPK(SPkU16, param->riCfgIdx, mBuf);
   CMCHKPK(SPkU8, param->riEna, mBuf);
   CMCHKPK(SPkU8, param->k, mBuf);
   CMCHKPK(SPkU8, param->cqiRepType, mBuf);
   CMCHKPK(SPkU16, param->cqiPCfgIdx, mBuf);
   CMCHKPK(SPkU16, param->cqiPResIdx, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrUeDlPCqiSetup
*
*
*     Desc : Periodic CQI Setup configuration parameters information
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
PUBLIC S16 cmUnpkRgrUeDlPCqiSetup
(
RgrUeDlPCqiSetup *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeDlPCqiSetup(param, mBuf)
RgrUeDlPCqiSetup *param;
Buffer *mBuf;
#endif
{
   U32 tmpEnum;

   TRC3(cmUnpkRgrUeDlPCqiSetup)

   CMCHKUNPK(SUnpkU16, &param->cqiPResIdx, mBuf);
   CMCHKUNPK(SUnpkU16, &param->cqiPCfgIdx, mBuf);
   CMCHKUNPK(SUnpkU8, &param->cqiRepType, mBuf);
   CMCHKUNPK(SUnpkU8, &param->k, mBuf);
   CMCHKUNPK(SUnpkU8, &param->riEna, mBuf);
   /*rgr_c_001.main_9 DEL removed unwanted comments*/
   CMCHKUNPK(SUnpkU16, &param->riCfgIdx, mBuf); 
   CMCHKUNPK(SUnpkU8, &param->sANCQI, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->prdModeEnum = (RgrPrdCqiMode) tmpEnum;
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrUePrdDlCqiCfg
*
*
*     Desc : Periodic CQI/PMI/RI configuration parameters information
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
PUBLIC S16 cmPkRgrUePrdDlCqiCfg
(
RgrUePrdDlCqiCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUePrdDlCqiCfg(param, mBuf)
RgrUePrdDlCqiCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrUePrdDlCqiCfg)

   CMCHKPK(cmPkRgrUeDlPCqiSetup, &param->cqiSetup, mBuf);
   CMCHKPK(SPkU8, param->type, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrUePrdDlCqiCfg
*
*
*     Desc : Periodic CQI/PMI/RI configuration parameters information
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
PUBLIC S16 cmUnpkRgrUePrdDlCqiCfg
(
RgrUePrdDlCqiCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUePrdDlCqiCfg(param, mBuf)
RgrUePrdDlCqiCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrUePrdDlCqiCfg)

   CMCHKUNPK(SUnpkU8, &param->type, mBuf);
   CMCHKUNPK(cmUnpkRgrUeDlPCqiSetup, &param->cqiSetup, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrUeUlSrsSetupCfg
*
*
*     Desc : SRS configuration setup parameters information. 
   Reference 36.313 SoundingRS-UL-Config
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
PUBLIC S16 cmPkRgrUeUlSrsSetupCfg
(
RgrUeUlSrsSetupCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeUlSrsSetupCfg(param, mBuf)
RgrUeUlSrsSetupCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrUeUlSrsSetupCfg)

   CMCHKPK(SPkU8, param->fDomPosi, mBuf);
   CMCHKPK(SPkU8, param->txComb, mBuf);
   CMCHKPK(SPkU8, param->sANSrs, mBuf);
   CMCHKPK(SPkU8, param->duration, mBuf);
   CMCHKPK(SPkU32, param->cycShift, mBuf);
   CMCHKPK(SPkU32, param->srsHopBw, mBuf);
   CMCHKPK(SPkU32, param->srsBw, mBuf);
   /*rgr_c_001.main_9 DEL removed unwanted comments*/
   CMCHKPK(SPkU16, param->srsCfgIdx, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrUeUlSrsSetupCfg
*
*
*     Desc : SRS configuration setup parameters information. 
   Reference 36.313 SoundingRS-UL-Config
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
PUBLIC S16 cmUnpkRgrUeUlSrsSetupCfg
(
RgrUeUlSrsSetupCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeUlSrsSetupCfg(param, mBuf)
RgrUeUlSrsSetupCfg *param;
Buffer *mBuf;
#endif
{
   U32 tmpEnum;

   TRC3(cmUnpkRgrUeUlSrsSetupCfg)

   /*rgr_c_001.main_9 DEL removed unwanted comments*/
   CMCHKUNPK(SUnpkU16, &param->srsCfgIdx, mBuf); 
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->srsBw = (RgrUlSrsBwInfo) tmpEnum;
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->srsHopBw = (RgrUlSrsHoBwInfo) tmpEnum;
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->cycShift = (RgrUlSrsCycShiftInfo) tmpEnum;
   CMCHKUNPK(SUnpkU8, &param->duration, mBuf);
   CMCHKUNPK(SUnpkU8, &param->sANSrs, mBuf);
   CMCHKUNPK(SUnpkU8, &param->txComb, mBuf);
   CMCHKUNPK(SUnpkU8, &param->fDomPosi, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrUeSrSetupCfg
*
*
*     Desc : SR Setup configuration parameters information
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
PUBLIC S16 cmPkRgrUeSrSetupCfg
(
RgrUeSrSetupCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeSrSetupCfg(param, mBuf)
RgrUeSrSetupCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrUeSrSetupCfg)

   /* ccpu00131601:DEL - dTMax Packing removed since this param will not 
    * be required by Scheduler*/
   CMCHKPK(SPkU8, param->srCfgIdx, mBuf);
   CMCHKPK(SPkU16, param->srResIdx, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrUeSrSetupCfg
*
*
*     Desc : SR Setup configuration parameters information
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
PUBLIC S16 cmUnpkRgrUeSrSetupCfg
(
RgrUeSrSetupCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeSrSetupCfg(param, mBuf)
RgrUeSrSetupCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkRgrUeSrSetupCfg)

   CMCHKUNPK(SUnpkU16, &param->srResIdx, mBuf);
   CMCHKUNPK(SUnpkU8, &param->srCfgIdx, mBuf);
   /* ccpu00131601:DEL - dTMax UnPacking removed since this param will not 
    * be required by Scheduler*/
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrUeSrCfg
*
*
*     Desc : SR configuration parameters information
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
PUBLIC S16 cmPkRgrUeSrCfg
(
RgrUeSrCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeSrCfg(param, mBuf)
RgrUeSrCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrUeSrCfg)

   CMCHKPK(cmPkRgrUeSrSetupCfg, &param->srSetup, mBuf);
   CMCHKPK(SPkU8, param->type, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrUeSrCfg
*
*
*     Desc : SR configuration parameters information
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
PUBLIC S16 cmUnpkRgrUeSrCfg
(
RgrUeSrCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeSrCfg(param, mBuf)
RgrUeSrCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrUeSrCfg)

   CMCHKUNPK(SUnpkU8, &param->type, mBuf);
   CMCHKUNPK(cmUnpkRgrUeSrSetupCfg, &param->srSetup, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrUeUlSrsCfg
*
*
*     Desc : SRS configuration parameters information.  
  Reference 36.313 SoundingRS-UL-Config
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
PUBLIC S16 cmPkRgrUeUlSrsCfg
(
RgrUeUlSrsCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeUlSrsCfg(param, mBuf)
RgrUeUlSrsCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrUeUlSrsCfg)

   /*rgr_c_001.main_9 DEL removed unwanted comments*/
   CMCHKPK(cmPkRgrUeUlSrsSetupCfg, &param->srsSetup, mBuf);  
   CMCHKPK(SPkU8, param->type, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrUeUlSrsCfg
*
*
*     Desc : SRS configuration parameters information.  
  Reference 36.313 SoundingRS-UL-Config
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
PUBLIC S16 cmUnpkRgrUeUlSrsCfg
(
RgrUeUlSrsCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeUlSrsCfg(param, mBuf)
RgrUeUlSrsCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrUeUlSrsCfg)

   CMCHKUNPK(SUnpkU8, &param->type, mBuf);
   /*rgr_c_001.main_9 DEL removed unwanted comments*/
   CMCHKUNPK(cmUnpkRgrUeUlSrsSetupCfg, &param->srsSetup, mBuf);  
   RETVALUE(ROK);
}


#endif /*TFU_UPGRADE */


/***********************************************************
*
*     Func : cmPkRgrUeDlCqiCfg
*
*
*     Desc : Downlink CQI reporting related configuration per UE
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
PUBLIC S16 cmPkRgrUeDlCqiCfg
(
RgrUeDlCqiCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeDlCqiCfg(param, mBuf)
RgrUeDlCqiCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrUeDlCqiCfg)


/* rgr_c_001.main_8. Added changes of TFU_UPGRADE */
#ifdef TFU_UPGRADE
   CMCHKPK(cmPkRgrUePrdDlCqiCfg, &param->prdCqiCfg, mBuf);
#endif

/* rgr_c_001.main_8. Added changes of TFU_UPGRADE */
#ifndef TFU_UPGRADE
   CMCHKPK(cmPkRgrUePrdDlCqiCfg, &param->prdCqiCfg, mBuf);
#endif
   CMCHKPK(cmPkRgrUeAprdDlCqiCfg, &param->aprdCqiCfg, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrUeDlCqiCfg
*
*
*     Desc : Downlink CQI reporting related configuration per UE
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
PUBLIC S16 cmUnpkRgrUeDlCqiCfg
(
RgrUeDlCqiCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeDlCqiCfg(param, mBuf)
RgrUeDlCqiCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrUeDlCqiCfg)

   CMCHKUNPK(cmUnpkRgrUeAprdDlCqiCfg, &param->aprdCqiCfg, mBuf);
   CMCHKUNPK(cmUnpkRgrUePrdDlCqiCfg, &param->prdCqiCfg, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrUeMeasGapCfg
*
*
*     Desc : Measurement gap configuration for UE
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
PUBLIC S16 cmPkRgrUeMeasGapCfg
(
RgrUeMeasGapCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeMeasGapCfg(param, mBuf)
RgrUeMeasGapCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrUeMeasGapCfg)

   CMCHKPK(SPkU8, param->gapOffst, mBuf);
   CMCHKPK(SPkU8, param->gapPrd, mBuf);
   CMCHKPK(SPkU8, param->isMesGapEnabled, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrUeMeasGapCfg
*
*
*     Desc : Measurement gap configuration for UE
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
PUBLIC S16 cmUnpkRgrUeMeasGapCfg
(
RgrUeMeasGapCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeMeasGapCfg(param, mBuf)
RgrUeMeasGapCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrUeMeasGapCfg)

   CMCHKUNPK(SUnpkU8, &param->isMesGapEnabled, mBuf);
   CMCHKUNPK(SUnpkU8, &param->gapPrd, mBuf);
   CMCHKUNPK(SUnpkU8, &param->gapOffst, mBuf);
   RETVALUE(ROK);
}

/*rgr_c_001.main_9 ADD DRX functionality under flag*/

/***********************************************************
*
*     Func : cmPkRgrDrxLongCycleOffst
*
*
*     Desc : DRX Long Cycle Offset
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
PUBLIC S16 cmPkRgrDrxLongCycleOffst
(
RgrDrxLongCycleOffst *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrDrxLongCycleOffst(param, mBuf)
RgrDrxLongCycleOffst *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrDrxLongCycleOffst)

   CMCHKPK(SPkU16, param->drxStartOffst, mBuf);
   CMCHKPK(SPkU16, param->longDrxCycle, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrDrxLongCycleOffst
*
*
*     Desc : DRX Long Cycle Offset
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
PUBLIC S16 cmUnpkRgrDrxLongCycleOffst
(
RgrDrxLongCycleOffst *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrDrxLongCycleOffst(param, mBuf)
RgrDrxLongCycleOffst *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrDrxLongCycleOffst)

   CMCHKUNPK(SUnpkU16, &param->longDrxCycle, mBuf);
   CMCHKUNPK(SUnpkU16, &param->drxStartOffst, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrDrxShortDrx
*
*
*     Desc : DRX Short Cycle Offset
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
PUBLIC S16 cmPkRgrDrxShortDrx
(
RgrDrxShortDrx *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrDrxShortDrx(param, mBuf)
RgrDrxShortDrx *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrDrxShortDrx)

   CMCHKPK(SPkU8, param->drxShortCycleTmr, mBuf);
   CMCHKPK(SPkU16, param->shortDrxCycle, mBuf);
   CMCHKPK(SPkU8, param->pres, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrDrxShortDrx
*
*
*     Desc : DRX Short Cycle Offset
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
PUBLIC S16 cmUnpkRgrDrxShortDrx
(
RgrDrxShortDrx *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrDrxShortDrx(param, mBuf)
RgrDrxShortDrx *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrDrxShortDrx)

   CMCHKUNPK(SUnpkU8, &param->pres, mBuf);
   CMCHKUNPK(SUnpkU16, &param->shortDrxCycle, mBuf);
   CMCHKUNPK(SUnpkU8, &param->drxShortCycleTmr, mBuf);
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmPkRgrUeDrxCfg
*
*
*     Desc : DRX configuration for UE
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
PUBLIC S16 cmPkRgrUeDrxCfg
(
RgrUeDrxCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeDrxCfg(param, mBuf)
RgrUeDrxCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrUeDrxCfg)

   CMCHKPK(cmPkRgrDrxShortDrx, &param->drxShortDrx, mBuf);
   CMCHKPK(cmPkRgrDrxLongCycleOffst, &param->drxLongCycleOffst, mBuf);
   CMCHKPK(SPkU8, param->drxRetxTmr, mBuf);
   CMCHKPK(SPkU16, param->drxInactvTmr, mBuf);
   CMCHKPK(SPkU8, param->drxOnDurTmr, mBuf);
/*rgr_c_001.main_9 ADD added changes for R9*/
#ifdef LTEMAC_R9
   CMCHKPK(cmPkTknS32, &param->cqiMask, mBuf);
#endif
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrUeDrxCfg
*
*
*     Desc : DRX configuration for UE
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
PUBLIC S16 cmUnpkRgrUeDrxCfg
(
RgrUeDrxCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeDrxCfg(param, mBuf)
RgrUeDrxCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrUeDrxCfg)

/*rgr_c_001.main_9 ADD added changes for R9*/
#ifdef LTEMAC_R9
   CMCHKUNPK(cmUnpkTknS32, &param->cqiMask, mBuf);
#endif
   CMCHKUNPK(SUnpkU8, &param->drxOnDurTmr, mBuf);
   CMCHKUNPK(SUnpkU16, &param->drxInactvTmr, mBuf);
   CMCHKUNPK(SUnpkU8, &param->drxRetxTmr, mBuf);
   CMCHKUNPK(cmUnpkRgrDrxLongCycleOffst, &param->drxLongCycleOffst, mBuf);
   CMCHKUNPK(cmUnpkRgrDrxShortDrx, &param->drxShortDrx, mBuf);
   RETVALUE(ROK);
}

/*rgr_c_001.main_9 ADD added DRX changes under DRX*/

/***********************************************************
*
*     Func : cmPkRgrUeCapCfg
*
*
*     Desc : RgrUeCapCfg
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
PUBLIC S16 cmPkRgrUeCapCfg
(
RgrUeCapCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeCapCfg(param, mBuf)
RgrUeCapCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrUeCapCfg)

   CMCHKPK(SPkU8, param->txAntSel, mBuf);
   CMCHKPK(SPkU8, param->simCqiAckNack, mBuf);
   CMCHKPK(SPkU8, param->resAloocType1, mBuf);
   CMCHKPK(SPkU8, param->intraSfFeqHop, mBuf);
   CMCHKPK(SPkU8, param->pwrClass, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrUeCapCfg
*
*
*     Desc : RgrUeCapCfg
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
PUBLIC S16 cmUnpkRgrUeCapCfg
(
RgrUeCapCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeCapCfg(param, mBuf)
RgrUeCapCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrUeCapCfg)

   CMCHKUNPK(SUnpkU8, &param->pwrClass, mBuf);
   CMCHKUNPK(SUnpkU8, &param->intraSfFeqHop, mBuf);
   CMCHKUNPK(SUnpkU8, &param->resAloocType1, mBuf);
   CMCHKUNPK(SUnpkU8, &param->simCqiAckNack, mBuf);
   CMCHKUNPK(SUnpkU8, &param->txAntSel, mBuf);
   
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkRgrUeAckNackRepCfg
*
*
*     Desc : rgrUeAckNackRepCfg
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
PUBLIC S16 cmPkRgrUeAckNackRepCfg
(
RgrUeAckNackRepCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeAckNackRepCfg(param, mBuf)
RgrUeAckNackRepCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrUeAckNackRepCfg)

   CMCHKPK(SPkU32, param->ackNackRepFactor, mBuf);
   CMCHKPK(SPkU16, param->pucchAckNackRep, mBuf);
   CMCHKPK(SPkU8, param->isAckNackEnabled, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrUeAckNackRepCfg
*
*
*     Desc : rgrUeAckNackRepCfg
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
PUBLIC S16 cmUnpkRgrUeAckNackRepCfg
(
RgrUeAckNackRepCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeAckNackRepCfg(param, mBuf)
RgrUeAckNackRepCfg *param;
Buffer *mBuf;
#endif
{
   U32 tmpEnum;

   TRC3(cmUnpkRgrUeAckNackRepCfg)

   CMCHKUNPK(SUnpkU8, &param->isAckNackEnabled, mBuf);
   CMCHKUNPK(SUnpkU16, &param->pucchAckNackRep, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->ackNackRepFactor = (RgrAckNackRepFactor) tmpEnum;
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrUeTxModeCfg
*
*
*     Desc : Transmission mode configuration per UE
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
PUBLIC S16 cmPkRgrUeTxModeCfg
(
RgrUeTxModeCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeTxModeCfg(param, mBuf)
RgrUeTxModeCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrUeTxModeCfg)

   CMCHKPK(SPkU32, param->txModeEnum, mBuf);
   CMCHKPK(SPkU32, param->tmTrnstnState, mBuf);
   CMCHKPK(SPkU8, param->pres, mBuf);
   
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrUeTxModeCfg
*
*
*     Desc : Transmission mode configuration per UE
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
PUBLIC S16 cmUnpkRgrUeTxModeCfg
(
RgrUeTxModeCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeTxModeCfg(param, mBuf)
RgrUeTxModeCfg *param;
Buffer *mBuf;
#endif
{
   U32 tmpEnum;

   TRC3(cmUnpkRgrUeTxModeCfg)

   CMCHKUNPK(SUnpkU8, &param->pres, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->tmTrnstnState = (RgrTxModeTrnstn) tmpEnum;

   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->txModeEnum = (RgrTxMode) tmpEnum;
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrUeUlHqCfg
*
*
*     Desc : Uplink HARQ configuration per UE
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
PUBLIC S16 cmPkRgrUeUlHqCfg
(
RgrUeUlHqCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeUlHqCfg(param, mBuf)
RgrUeUlHqCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrUeUlHqCfg)

   CMCHKPK(SPkU8, param->deltaHqOffst, mBuf);
   CMCHKPK(SPkU8, param->maxUlHqTx, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrUeUlHqCfg
*
*
*     Desc : Uplink HARQ configuration per UE
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
PUBLIC S16 cmUnpkRgrUeUlHqCfg
(
RgrUeUlHqCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeUlHqCfg(param, mBuf)
RgrUeUlHqCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrUeUlHqCfg)

   CMCHKUNPK(SUnpkU8, &param->maxUlHqTx, mBuf);
   CMCHKUNPK(SUnpkU8, &param->deltaHqOffst, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrUeGrpPwrCfg
*
*
*     Desc : Group power configuration per UE for PUCCH and PUSCH group power control
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
PUBLIC S16 cmPkRgrUeGrpPwrCfg
(
RgrUeGrpPwrCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeGrpPwrCfg(param, mBuf)
RgrUeGrpPwrCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrUeGrpPwrCfg)

   CMCHKPK(SPkU8, param->idx, mBuf);
   CMCHKPK(cmPkLteRnti, param->tpcRnti, mBuf);
   CMCHKPK(SPkU8, param->pres, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrUeGrpPwrCfg
*
*
*     Desc : Group power configuration per UE for PUCCH and PUSCH group power control
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
PUBLIC S16 cmUnpkRgrUeGrpPwrCfg
(
RgrUeGrpPwrCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeGrpPwrCfg(param, mBuf)
RgrUeGrpPwrCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrUeGrpPwrCfg)

   CMCHKUNPK(SUnpkU8, &param->pres, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &param->tpcRnti, mBuf);
   CMCHKUNPK(SUnpkU8, &param->idx, mBuf);
   RETVALUE(ROK);
}

/*rgr_c_001.main_7 - Added support for SPS*/


/***********************************************************
*
*     Func : cmPkRgrUeSpsDlCfg
*
*
*     Desc : DL SPS configuration parameters per UE
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
PUBLIC S16 cmPkRgrUeSpsDlCfg
(
RgrUeSpsDlCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeSpsDlCfg(param, mBuf)
RgrUeSpsDlCfg *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkRgrUeSpsDlCfg)
   CMCHKPK(SPkU16, param->explicitRelCnt, mBuf);
   CMCHKPK(SPkU32, param->dlSpsPrdctyEnum, mBuf);
   for (i=param->numPucchVal-1; i >= 0; i--) {
      CMCHKPK(SPkU32, param->n1PucchVal[i], mBuf);
   }
   CMCHKPK(SPkU8, param->numPucchVal, mBuf);
   CMCHKPK(SPkU8, param->numSpsHqProc, mBuf);
   CMCHKPK(SPkU8, param->isDlSpsEnabled, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrUeSpsDlCfg
*
*
*     Desc : DL SPS configuration parameters per UE
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
PUBLIC S16 cmUnpkRgrUeSpsDlCfg
(
RgrUeSpsDlCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeSpsDlCfg(param, mBuf)
RgrUeSpsDlCfg *param;
Buffer *mBuf;
#endif
{
   U32 tmpEnum;

   S32 i;
   TRC3(cmUnpkRgrUeSpsDlCfg)

   CMCHKUNPK(SUnpkU8, &param->isDlSpsEnabled, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numSpsHqProc, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numPucchVal, mBuf);
   for (i=0; i<param->numPucchVal; i++) {
      CMCHKUNPK(SUnpkU32, &param->n1PucchVal[i], mBuf);
   }
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->dlSpsPrdctyEnum = tmpEnum;
   CMCHKUNPK(SUnpkU16, &param->explicitRelCnt, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrUeSpsUlCfg
*
*
*     Desc : UL SPS configuration parameters per UE
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
PUBLIC S16 cmPkRgrUeSpsUlCfg
(
RgrUeSpsUlCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeSpsUlCfg(param, mBuf)
RgrUeSpsUlCfg *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkRgrUeSpsUlCfg)

   CMCHKPK(SPkU8, param->isLcSRMaskEnab, mBuf);
   for (i=param->lcCnt-1; i >= 0; i--) {
      /* SPS Changes starts */
      CMCHKPK(SPkU8, param->spsLcInfo[i].isSpsEnabled, mBuf);
      CMCHKPK(SPkU8, param->spsLcInfo[i].lcId, mBuf);
      /* SPS Changes ends */
   }
   CMCHKPK(SPkU8, param->lcCnt, mBuf);
   CMCHKPK(SPkU32, param->ulSpsPrdctyEnum, mBuf);
      CMCHKPK(SPkS8, param->pwrCfg.p0UePuschVal, mBuf);
      CMCHKPK(SPkS8, param->pwrCfg.p0NominalPuschVal, mBuf);
   CMCHKPK(SPkU8, param->pwrCfgPres, mBuf);

#ifdef LTE_TDD
   CMCHKPK(SPkU8, param->twoIntervalCfg, mBuf);

#endif
   CMCHKPK(SPkU32, param->implicitRelCnt, mBuf);
   CMCHKPK(SPkU8, param->isUlSpsEnabled, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrUeSpsUlCfg
*
*
*     Desc : UL SPS configuration parameters per UE
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
PUBLIC S16 cmUnpkRgrUeSpsUlCfg
(
RgrUeSpsUlCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeSpsUlCfg(param, mBuf)
RgrUeSpsUlCfg *param;
Buffer *mBuf;
#endif
{
   U32 tmpEnum;

   S32 i;
   TRC3(cmUnpkRgrUeSpsUlCfg)

   CMCHKUNPK(SUnpkU8, &param->isUlSpsEnabled, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->implicitRelCnt = tmpEnum;

#ifdef LTE_TDD
   CMCHKUNPK(SUnpkU8, &param->twoIntervalCfg, mBuf);

#endif
   CMCHKUNPK(SUnpkU8, &param->pwrCfgPres, mBuf);
      CMCHKUNPK(SUnpkS8, &param->pwrCfg.p0NominalPuschVal, mBuf);
      CMCHKUNPK(SUnpkS8, &param->pwrCfg.p0UePuschVal, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->ulSpsPrdctyEnum = tmpEnum;
   CMCHKUNPK(SUnpkU8, &param->lcCnt, mBuf); 
   for (i=0; i<param->lcCnt; i++) {
      CMCHKUNPK(SUnpkU8, &param->spsLcInfo[i].lcId, mBuf);
      CMCHKUNPK(SUnpkU8, &param->spsLcInfo[i].isSpsEnabled, mBuf);
   }
   CMCHKUNPK(SUnpkU8, &param->isLcSRMaskEnab, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrUeSpsCfg
*
*
*     Desc : SPS configuration parameters per UE
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
PUBLIC S16 cmPkRgrUeSpsCfg
(
RgrUeSpsCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeSpsCfg(param, mBuf)
RgrUeSpsCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrUeSpsCfg)

   CMCHKPK(cmPkRgrUeSpsUlCfg, &param->ulSpsCfg, mBuf);
   CMCHKPK(cmPkRgrUeSpsDlCfg, &param->dlSpsCfg, mBuf);
   CMCHKPK(cmPkLteRnti, param->spsRnti, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrUeSpsCfg
*
*
*     Desc : SPS configuration parameters per UE
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
PUBLIC S16 cmUnpkRgrUeSpsCfg
(
RgrUeSpsCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeSpsCfg(param, mBuf)
RgrUeSpsCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrUeSpsCfg)

   CMCHKUNPK(cmUnpkLteRnti, &param->spsRnti, mBuf);
   CMCHKUNPK(cmUnpkRgrUeSpsDlCfg, &param->dlSpsCfg, mBuf);
   CMCHKUNPK(cmUnpkRgrUeSpsUlCfg, &param->ulSpsCfg, mBuf);
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkRgrUeUlPwrCfg
*
*
*     Desc : Uplink power configuration per UE
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
PUBLIC S16 cmPkRgrUeUlPwrCfg
(
RgrUeUlPwrCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeUlPwrCfg(param, mBuf)
RgrUeUlPwrCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrUeUlPwrCfg)

   CMCHKPK(SPkU8, param->trgCqi, mBuf);
   CMCHKPK(SPkU8, param->pSRSOffset, mBuf);
   CMCHKPK(SPkS8, param->p0UePucch, mBuf);
   CMCHKPK(SPkS8, param->p0UePusch, mBuf);
   CMCHKPK(SPkU8, param->isDeltaMCSEnabled, mBuf);
   CMCHKPK(SPkU8, param->isAccumulated, mBuf);
   CMCHKPK(cmPkRgrUeGrpPwrCfg, &param->uePucchPwr, mBuf);
   CMCHKPK(cmPkRgrUeGrpPwrCfg, &param->uePuschPwr, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrUeUlPwrCfg
*
*
*     Desc : Uplink power configuration per UE
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
PUBLIC S16 cmUnpkRgrUeUlPwrCfg
(
RgrUeUlPwrCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeUlPwrCfg(param, mBuf)
RgrUeUlPwrCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrUeUlPwrCfg)

   CMCHKUNPK(cmUnpkRgrUeGrpPwrCfg, &param->uePuschPwr, mBuf);
   CMCHKUNPK(cmUnpkRgrUeGrpPwrCfg, &param->uePucchPwr, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isAccumulated, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isDeltaMCSEnabled, mBuf);
   CMCHKUNPK(SUnpkS8, &param->p0UePusch, mBuf);
   CMCHKUNPK(SUnpkS8, &param->p0UePucch, mBuf);
   CMCHKUNPK(SUnpkU8, &param->pSRSOffset, mBuf);
   CMCHKUNPK(SUnpkU8, &param->trgCqi, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrUeQosCfg
*
*
*     Desc : Downlink/Uplink QoS configuration per UE
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
PUBLIC S16 cmPkRgrUeQosCfg
(
RgrUeQosCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeQosCfg(param, mBuf)
RgrUeQosCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrUeQosCfg)

   CMCHKPK(SPkU32, param->ueBr, mBuf);
   CMCHKPK(SPkU32, param->dlAmbr, mBuf);
   CMCHKPK(SPkU8, param->ambrPres, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrUeQosCfg
*
*
*     Desc : Downlink/Uplink QoS configuration per UE
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
PUBLIC S16 cmUnpkRgrUeQosCfg
(
RgrUeQosCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeQosCfg(param, mBuf)
RgrUeQosCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrUeQosCfg)

   CMCHKUNPK(SUnpkU8, &param->ambrPres, mBuf);
   CMCHKUNPK(SUnpkU32, &param->dlAmbr, mBuf);
   CMCHKUNPK(SUnpkU32, &param->ueBr, mBuf);
   RETVALUE(ROK);
}

/*********************************************************** 
* 
*     Func : cmPkRgrUePuschDedCfg 
* 
* 
*     Desc : PUSCH Config Dedication for UE 
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
PUBLIC S16 cmPkRgrUePuschDedCfg 
( 
RgrUePuschDedCfg *param, 
Buffer *mBuf 
) 
#else 
PUBLIC S16 cmPkRgrUePuschDedCfg(param, mBuf) 
RgrUePuschDedCfg *param; 
Buffer *mBuf; 
#endif 
{ 
 
   TRC3(cmPkRgrUePuschDedCfg) 
 
   CMCHKPK(SPkU8, param->bCQIIdx, mBuf);
   CMCHKPK(SPkU8, param->bRIIdx, mBuf);
   CMCHKPK(SPkU8, param->bACKIdx, mBuf);
   CMCHKPK(SPkU8, param->pres, mBuf);
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmUnpkRgrUePuschDedCfg
*
*
*     Desc : PUSCH Config Dedication for UE
* 
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
PUBLIC S16 cmUnpkRgrUePuschDedCfg
(
RgrUePuschDedCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUePuschDedCfg(param, mBuf)
RgrUePuschDedCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrUePuschDedCfg)

   CMCHKUNPK(SUnpkU8, &param->pres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->bACKIdx, mBuf);
   CMCHKUNPK(SUnpkU8, &param->bRIIdx, mBuf);
   CMCHKUNPK(SUnpkU8, &param->bCQIIdx, mBuf);
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmPkRgrUeTxAntSelCfg
*
*
*     Desc : UE Transmit Antenna selection related configuration
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
PUBLIC S16 cmPkRgrUeTxAntSelCfg
(
RgrUeTxAntSelCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeTxAntSelCfg(param, mBuf)
RgrUeTxAntSelCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrUeTxAntSelCfg)

   CMCHKPK(SPkU32, param->selType, mBuf);
   CMCHKPK(SPkU8, param->pres, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrUeTxAntSelCfg
*
*
*     Desc : UE Transmit Antenna selection related configuration
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
PUBLIC S16 cmUnpkRgrUeTxAntSelCfg
(
RgrUeTxAntSelCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeTxAntSelCfg(param, mBuf)
RgrUeTxAntSelCfg *param;
Buffer *mBuf;
#endif
{
   U32 tmpEnum;

   TRC3(cmUnpkRgrUeTxAntSelCfg)

   CMCHKUNPK(SUnpkU8, &param->pres, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->selType = (RgrUeTxAntSelType) tmpEnum;
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkRgrUeTaTmrCfg
*
*
*     Desc : Time Alignment timer configuration per UE
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
PUBLIC S16 cmPkRgrUeTaTmrCfg
(
RgrUeTaTmrCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeTaTmrCfg(param, mBuf)
RgrUeTaTmrCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrUeTaTmrCfg)

   CMCHKPK(SPkU16, param->taTmr, mBuf);
   CMCHKPK(SPkU8, param->pres, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrUeTaTmrCfg
*
*
*     Desc : Time Alignment timer configuration per UE
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
PUBLIC S16 cmUnpkRgrUeTaTmrCfg
(
RgrUeTaTmrCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeTaTmrCfg(param, mBuf)
RgrUeTaTmrCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrUeTaTmrCfg)

   CMCHKUNPK(SUnpkU8, &param->pres, mBuf);
   CMCHKUNPK(SUnpkU16, &param->taTmr, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrUeCfg
*
*
*     Desc : UE configuration
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
PUBLIC S16 cmPkRgrUeCfg
(
RgrUeCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeCfg(param, mBuf)
RgrUeCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrUeCfg)
   CMCHKPK(SPkU8, param->csgMmbrSta, mBuf);

   CMCHKPK(SPkU32, param->accessStratumRls, mBuf);
   /* LTE_ADV_FLAG_REMOVED_START */
   CMCHKPK(cmPkRgrLteAdvancedUeConfig, &param->ueLteAdvCfg, mBuf);
   /* LTE_ADV_FLAG_REMOVED_END */
#ifdef TFU_UPGRADE
/*rgr_c_001.main_9 ADD PDSCH ded cfg*/
   CMCHKPK(cmPkRgrUePdschDedCfg, &param->uePdschDedCfg, mBuf);
#endif
   /*rgr_c_001.main_9 ccpu00117452 - MOD - Changed macro name from
   RGR_RRM_DLPWR_CNTRL to RGR_CQI_REPT */
#ifdef RGR_CQI_REPT
   CMCHKPK(cmPkRgrUeCqiReptCfg, &param->ueCqiReptCfg, mBuf);
#endif
   CMCHKPK(cmPkRgrUeTxAntSelCfg, &param->ulTxAntSel, mBuf);

/* rgr_c_001.main_8. Added changes of TFU_UPGRADE */
   CMCHKPK(cmPkRgrUePuschDedCfg, &param->puschDedCfg, mBuf);

/*rgr_c_001.main_9 ADD added changes for HDFDD*/
#ifdef LTEMAC_HDFDD
   CMCHKPK(SPkU8, param->isHdFddEnbld, mBuf);
#endif

#ifdef TFU_UPGRADE
   CMCHKPK(cmPkRgrUeSrCfg, &param->srCfg, mBuf);
   CMCHKPK(cmPkRgrUeUlSrsCfg, &param->srsCfg, mBuf);
#endif



   CMCHKPK(cmPkRgrUeSpsCfg, &param->ueSpsCfg, mBuf);

#ifdef LTE_TDD
   CMCHKPK(SPkU32, param->ackNackModeEnum, mBuf);

#endif
   CMCHKPK(cmPkTknU8, &param->dedPreambleId, mBuf);
   CMCHKPK(cmPkRgrCodeBookRstCfg, &param->ueCodeBookRstCfg, mBuf);
   CMCHKPK(cmPkRgrUeCapCfg, &param->ueCapCfg, mBuf);
   CMCHKPK(cmPkRgrUeMeasGapCfg, &param->ueMesGapCfg, mBuf);
   CMCHKPK(cmPkRgrUeAckNackRepCfg, &param->ueAckNackCfg, mBuf);
   CMCHKPK(SPkU8, param->isTtiBundlEnabled, mBuf);
/*rgr_c_001.main_9 ADD added changes for DRX*/
   
   /* Anshika - Pack only if DRX is enabled */
   if(TRUE == param->ueDrxCfg.isDrxEnabled)
   {   
    CMCHKPK(cmPkRgrUeDrxCfg, &param->ueDrxCfg, mBuf);
   }
   CMCHKPK(SPkU8, param->ueDrxCfg.isDrxEnabled, mBuf); /* This has to be packed even if
                                                 DRX is disabled */
   CMCHKPK(SPkU32, param->ueCatEnum, mBuf);
#ifdef RGR_V1
   /* rgr_c_001.main_5: ccpu00112398: Added periodicBSR-timer and
    * retxBSR-timer */
   CMCHKPK(cmPkRgrUeBsrTmrCfg, &param->ueBsrTmrCfg, mBuf);
#endif
   CMCHKPK(cmPkRgrUeTaTmrCfg, &param->ueTaTmrCfg, mBuf);
   CMCHKPK(cmPkRgrUeQosCfg, &param->ueQosCfg, mBuf);
   CMCHKPK(cmPkRgrUeUlPwrCfg, &param->ueUlPwrCfg, mBuf);
   CMCHKPK(cmPkRgrUeUlHqCfg, &param->ueUlHqCfg, mBuf);
   CMCHKPK(cmPkRgrUeDlCqiCfg, &param->ueDlCqiCfg, mBuf);
   CMCHKPK(cmPkRgrUeTxModeCfg, &param->txMode, mBuf);
   CMCHKPK(cmPkLteRnti, param->crnti, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrUeCfg
*
*
*     Desc : UE configuration
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
PUBLIC S16 cmUnpkRgrUeCfg
(
RgrUeCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeCfg(param, mBuf)
RgrUeCfg *param;
Buffer *mBuf;
#endif
{
   U32 tmpEnum;

   TRC3(cmUnpkRgrUeCfg)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &param->crnti, mBuf);
   CMCHKUNPK(cmUnpkRgrUeTxModeCfg, &param->txMode, mBuf);
   CMCHKUNPK(cmUnpkRgrUeDlCqiCfg, &param->ueDlCqiCfg, mBuf);
   CMCHKUNPK(cmUnpkRgrUeUlHqCfg, &param->ueUlHqCfg, mBuf);
   CMCHKUNPK(cmUnpkRgrUeUlPwrCfg, &param->ueUlPwrCfg, mBuf);
   CMCHKUNPK(cmUnpkRgrUeQosCfg, &param->ueQosCfg, mBuf);
   CMCHKUNPK(cmUnpkRgrUeTaTmrCfg, &param->ueTaTmrCfg, mBuf);
#ifdef RGR_V1
   /* rgr_c_001.main_5: ccpu00112398: Added periodicBSR-timer and
    * retxBSR-timer */
   CMCHKUNPK(cmUnpkRgrUeBsrTmrCfg, &param->ueBsrTmrCfg, mBuf);
#endif
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->ueCatEnum = (CmLteUeCategory) tmpEnum;
/*rgr_c_001.main_9 ADD added changes for DRX*/
   
   /* Anshika - Unpack only if DRX is enabled */
   CMCHKUNPK(SUnpkU8, &param->ueDrxCfg.isDrxEnabled, mBuf);
   if(TRUE == param->ueDrxCfg.isDrxEnabled)
   {
      CMCHKUNPK(cmUnpkRgrUeDrxCfg, &param->ueDrxCfg, mBuf);
   }
   CMCHKUNPK(SUnpkU8, &param->isTtiBundlEnabled, mBuf);
   CMCHKUNPK(cmUnpkRgrUeAckNackRepCfg, &param->ueAckNackCfg, mBuf);
   CMCHKUNPK(cmUnpkRgrUeMeasGapCfg, &param->ueMesGapCfg, mBuf);
   CMCHKUNPK(cmUnpkRgrUeCapCfg, &param->ueCapCfg, mBuf);
   CMCHKUNPK(cmUnpkRgrCodeBookRstCfg, &param->ueCodeBookRstCfg, mBuf);
   CMCHKUNPK(cmUnpkTknU8, &param->dedPreambleId, mBuf);

#ifdef LTE_TDD
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->ackNackModeEnum = tmpEnum;

#endif
   /*rgr_c_001.main_7 - Added support for SPS*/
   CMCHKUNPK(cmUnpkRgrUeSpsCfg, &param->ueSpsCfg, mBuf);

/* rgr_c_001.main_8. Added changes of TFU_UPGRADE */
#ifdef TFU_UPGRADE
   CMCHKUNPK(cmUnpkRgrUeUlSrsCfg, &param->srsCfg, mBuf);
   CMCHKUNPK(cmUnpkRgrUeSrCfg, &param->srCfg, mBuf);
#endif
/*rgr_c_001.main_9 ADD added changes for HDFDD*/
#ifdef LTEMAC_HDFDD
   CMCHKUNPK(SUnpkU8, &param->isHdFddEnbld, mBuf);
#endif
   CMCHKUNPK(cmUnpkRgrUePuschDedCfg, &param->puschDedCfg, mBuf);
   CMCHKUNPK(cmUnpkRgrUeTxAntSelCfg, &param->ulTxAntSel, mBuf);
/* rgr_c_001.main_9 ccpu00117452 - MOD - Changed macro name from
   RGR_RRM_DLPWR_CNTRL to RGR_CQI_REPT */
#ifdef RGR_CQI_REPT
   CMCHKUNPK(cmUnpkRgrUeCqiReptCfg, &param->ueCqiReptCfg, mBuf);
#endif
#ifdef TFU_UPGRADE
   CMCHKUNPK(cmUnpkRgrUePdschDedCfg, &param->uePdschDedCfg, mBuf);
#endif
   /* LTE_ADV_FLAG_REMOVED_START */
   CMCHKUNPK(cmUnpkRgrLteAdvancedUeConfig, &param->ueLteAdvCfg, mBuf);
   /* LTE_ADV_FLAG_REMOVED_END */
   CMCHKUNPK(SUnpkU32, (U32 *)&param->accessStratumRls, mBuf);
   CMCHKUNPK(SUnpkU8, &param->csgMmbrSta, mBuf);

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrLchQosCfg
*
*
*     Desc : QCI, GBR and MBR configuration for dedicated logical channels
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
PUBLIC S16 cmPkRgrLchQosCfg
(
RgrLchQosCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrLchQosCfg(param, mBuf)
RgrLchQosCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrLchQosCfg)

   CMCHKPK(SPkU32, param->mbr, mBuf);
   CMCHKPK(SPkU32, param->gbr, mBuf);
   CMCHKPK(SPkU8, param->qci, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrLchQosCfg
*
*
*     Desc : QCI, GBR and MBR configuration for dedicated logical channels
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
PUBLIC S16 cmUnpkRgrLchQosCfg
(
RgrLchQosCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrLchQosCfg(param, mBuf)
RgrLchQosCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrLchQosCfg)

   CMCHKUNPK(SUnpkU8, &param->qci, mBuf);
   CMCHKUNPK(SUnpkU32, &param->gbr, mBuf);
   CMCHKUNPK(SUnpkU32, &param->mbr, mBuf);
   RETVALUE(ROK);
}
/*rgr_c_001.main_7 - Added support for SPS*/


/***********************************************************
*
*     Func : cmPkRgrLchSpsCfg
*
*
*     Desc : SPS related configuration for logical channels
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
PUBLIC S16 cmPkRgrLchSpsCfg
(
RgrLchSpsCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrLchSpsCfg(param, mBuf)
RgrLchSpsCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrLchSpsCfg)

   /* SPS_DEV */
   CMCHKPK(SPkU8, param->isSpsEnabled, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrLchSpsCfg
*
*
*     Desc : SPS related configuration for logical channels
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
PUBLIC S16 cmUnpkRgrLchSpsCfg
(
RgrLchSpsCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrLchSpsCfg(param, mBuf)
RgrLchSpsCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrLchSpsCfg)

   CMCHKUNPK(SUnpkU8, &param->isSpsEnabled, mBuf);
   
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkRgrDlLchCfg
*
*
*     Desc : Logical channel configuration info for downlink logical channels
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
PUBLIC S16 cmPkRgrDlLchCfg
(
RgrDlLchCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrDlLchCfg(param, mBuf)
RgrDlLchCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrDlLchCfg)
/*rgr_c_001.main_7 - Added support for SPS*/

   CMCHKPK(cmPkRgrLchSpsCfg, &param->dlSpsCfg, mBuf);
   CMCHKPK(cmPkRgrLchQosCfg, &param->dlQos, mBuf);
   CMCHKPK(SPkU8, param->dlTrchType, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrDlLchCfg
*
*
*     Desc : Logical channel configuration info for downlink logical channels
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
PUBLIC S16 cmUnpkRgrDlLchCfg
(
RgrDlLchCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrDlLchCfg(param, mBuf)
RgrDlLchCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrDlLchCfg)

   CMCHKUNPK(SUnpkU8, &param->dlTrchType, mBuf);
   CMCHKUNPK(cmUnpkRgrLchQosCfg, &param->dlQos, mBuf);
   /*rgr_c_001.main_7 - Added support for SPs*/
   CMCHKUNPK(cmUnpkRgrLchSpsCfg, &param->dlSpsCfg, mBuf);

   RETVALUE(ROK);
}


/*rgr_c_001.main_9 ADD added changes for L2 measurements*/
#ifdef LTE_L2_MEAS


/***********************************************************
*
*     Func : cmPkRgrUlLchCfg
*
*
*     Desc : Logical channel configuration information for uplink logical channels
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
PUBLIC S16 cmPkRgrUlLchCfg
(
RgrUlLchCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUlLchCfg(param, mBuf)
RgrUlLchCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrUlLchCfg)

   CMCHKPK(SPkU8, param->qci, mBuf);
   CMCHKPK(cmPkLteLcId, param->lcId, mBuf);
   RETVALUE(ROK);
}



/*rgr_c_001.main_9 ADD added changes for L2 measurements*/
/***********************************************************
*
*     Func : cmUnpkRgrUlLchCfg
*
*
*     Desc : Logical channel configuration information for uplink logical channels
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
PUBLIC S16 cmUnpkRgrUlLchCfg
(
RgrUlLchCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUlLchCfg(param, mBuf)
RgrUlLchCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrUlLchCfg)

   CMCHKUNPK(cmUnpkLteLcId, &param->lcId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->qci, mBuf);
   RETVALUE(ROK);
}


#endif

/***********************************************************
*
*     Func : cmPkRgrUlLcgCfg
*
*
*     Desc : Logical channel configuration info for uplink logical channels
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
PUBLIC S16 cmPkRgrUlLcgCfg
(
RgrUlLcgCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUlLcgCfg(param, mBuf)
RgrUlLcgCfg *param;
Buffer *mBuf;
#endif
{

/*rgr_c_001.main_9 ADD added changes for L2 measurements*/
#ifdef LTE_L2_MEAS
   S32 i;
#endif
   TRC3(cmPkRgrUlLcgCfg)
   CMCHKPK(SPkU32, param->mbr, mBuf);
   CMCHKPK(SPkU32, param->gbr, mBuf);

/*rgr_c_001.main_9 ADD added changes for L2 measurements*/
#ifdef LTE_L2_MEAS
   for (i = param->numLch - 1; i >= 0; i--)
   {
      CMCHKPK(cmPkRgrUlLchCfg, &param->lchUlCfg[i], mBuf);
   }
   CMCHKPK(SPkU8, param->numLch, mBuf);
#endif
   CMCHKPK(SPkU8, param->lcgId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrUlLcgCfg
*
*
*     Desc : Logical channel configuration info for uplink logical channels
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
PUBLIC S16 cmUnpkRgrUlLcgCfg
(
RgrUlLcgCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUlLcgCfg(param, mBuf)
RgrUlLcgCfg *param;
Buffer *mBuf;
#endif
{

/*rgr_c_001.main_9 ADD added changes for L2 measurements*/
#ifdef LTE_L2_MEAS
   S32 i;
#endif
   TRC3(cmUnpkRgrUlLcgCfg)

   CMCHKUNPK(SUnpkU8, &param->lcgId, mBuf);
/*rgr_c_001.main_9 ADD added changes for L2 measurements*/
#ifdef LTE_L2_MEAS
   CMCHKUNPK(SUnpkU8, &param->numLch, mBuf);
   for (i = 0; i< param->numLch; i++)
   {
      CMCHKUNPK(cmUnpkRgrUlLchCfg, &param->lchUlCfg[i], mBuf);
   }

#endif
   CMCHKUNPK(SUnpkU32, &param->gbr, mBuf);
   CMCHKUNPK(SUnpkU32, &param->mbr, mBuf);
   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 cmPkRgrUlLchQciCfg
(
RgrUlLchQciCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUlLchQciCfg (param, mBuf)
RgrUlLchQciCfg *param;
Buffer *mBuf;
#endif
{
   CMCHKPK(SPkU8, param->lcId, mBuf);
   CMCHKPK(SPkU8, param->qci, mBuf);
   CMCHKPK(SPkU8, param->lcgId, mBuf);
   RETVALUE(ROK);
}
#ifdef ANSI
PUBLIC S16 cmUnpkRgrUlLchQciCfg
(
RgrUlLchQciCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUlLchQciCfg (param, mBuf)
RgrUlLchQciCfg *param;
Buffer *mBuf;
#endif
{
   CMCHKUNPK(SUnpkU8, &param->lcgId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->qci, mBuf);
   CMCHKUNPK(SUnpkU8, &param->lcId, mBuf);
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkRgrLchCfg
*
*
*     Desc : Logical channel configuration info for dedicated channels
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
PUBLIC S16 cmPkRgrLchCfg
(
RgrLchCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrLchCfg(param, mBuf)
RgrLchCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrLchCfg)
   CMCHKPK(SPkU8, param->lcgId, mBuf);
   CMCHKPK(cmPkRgrUlLchQciCfg, &param->ulLchQciInfo, mBuf);
   CMCHKPK(cmPkRgrDlLchCfg, &param->dlInfo, mBuf);
   CMCHKPK(cmPkLteLcType, param->lcType, mBuf);
   CMCHKPK(cmPkLteLcId, param->lcId, mBuf);
   CMCHKPK(cmPkLteRnti, param->crnti, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrLchCfg
*
*
*     Desc : Logical channel configuration info for dedicated channels
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
PUBLIC S16 cmUnpkRgrLchCfg
(
RgrLchCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrLchCfg(param, mBuf)
RgrLchCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrLchCfg)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &param->crnti, mBuf);
   CMCHKUNPK(cmUnpkLteLcId, &param->lcId, mBuf);
   CMCHKUNPK(cmUnpkLteLcType, &param->lcType, mBuf);
   CMCHKUNPK(cmUnpkRgrDlLchCfg, &param->dlInfo, mBuf);
   CMCHKUNPK(cmUnpkRgrUlLchQciCfg, &param->ulLchQciInfo, mBuf);
   CMCHKUNPK(SUnpkU8, &param->lcgId, mBuf);
   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmPkRgrLcgCfg
(
RgrLcgCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrLcgCfg(param, mBuf)
RgrLcgCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrLcgCfg)

   CMCHKPK(cmPkRgrUlLcgCfg, &param->ulInfo, mBuf);
   CMCHKPK(cmPkLteRnti, param->crnti, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmUnpkRgrLcgCfg
(
RgrLcgCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrLcgCfg(param, mBuf)
RgrLcgCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrLcgCfg)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &param->crnti, mBuf);
   CMCHKUNPK(cmUnpkRgrUlLcgCfg, &param->ulInfo, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrCfg
*
*
*     Desc : Basic Configuration structure at RRM
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
PUBLIC S16 cmPkRgrCfg
(
RgrCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrCfg(param, mBuf)
RgrCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrCfg)

      switch(param->cfgType) {
         case RGR_LCG_CFG:
            CMCHKPK(cmPkRgrLcgCfg, &param->u.lcgCfg, mBuf);
            break;
         case RGR_LCH_CFG:
            CMCHKPK(cmPkRgrLchCfg, &param->u.lchCfg, mBuf);
            break;
         case RGR_UE_CFG:
            CMCHKPK(cmPkRgrUeCfg, &param->u.ueCfg, mBuf);
            break;
         case RGR_CELL_CFG:
            CMCHKPK(cmPkRgrCellCfg, &param->u.cellCfg, mBuf);
            break;
         case RGR_ENB_CFG:
            CMCHKPK(cmPkRgrSchedEnbCfg, &param->u.schedEnbCfg, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(SPkU8, param->cfgType, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrCfg
*
*
*     Desc : Basic Configuration structure at RRM
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
PUBLIC S16 cmUnpkRgrCfg
(
RgrCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrCfg(param, mBuf)
RgrCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrCfg)

   CMCHKUNPK(SUnpkU8, &param->cfgType, mBuf);
      switch(param->cfgType) {
         case RGR_ENB_CFG:
            CMCHKUNPK(cmUnpkRgrSchedEnbCfg, &param->u.schedEnbCfg, mBuf);
            break;
         case RGR_CELL_CFG:
            CMCHKUNPK(cmUnpkRgrCellCfg, &param->u.cellCfg, mBuf);
            break;
         case RGR_UE_CFG:
            CMCHKUNPK(cmUnpkRgrUeCfg, &param->u.ueCfg, mBuf);
            break;
         case RGR_LCH_CFG:
            CMCHKUNPK(cmUnpkRgrLchCfg, &param->u.lchCfg, mBuf);
            break;
         case RGR_LCG_CFG:
            CMCHKUNPK(cmUnpkRgrLcgCfg, &param->u.lcgCfg, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrActvTime
*
*
*     Desc : Activation time information
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
PUBLIC S16 cmPkRgrActvTime
(
RgrActvTime *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrActvTime(param, mBuf)
RgrActvTime *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrActvTime)

   CMCHKPK(cmPkLteTimingInfo, &param->actvTime, mBuf);
   CMCHKPK(SPkU8, param->pres, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrActvTime
*
*
*     Desc : Activation time information
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
PUBLIC S16 cmUnpkRgrActvTime
(
RgrActvTime *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrActvTime(param, mBuf)
RgrActvTime *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrActvTime)

   CMCHKUNPK(SUnpkU8, &param->pres, mBuf);
   CMCHKUNPK(cmUnpkLteTimingInfo, &param->actvTime, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrCellRecfg
*
*
*     Desc : Cell reconfiguration structure at RRM
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
PUBLIC S16 cmPkRgrCellRecfg
(
RgrCellRecfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrCellRecfg(param, mBuf)
RgrCellRecfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrCellRecfg)
   CMCHKPK(cmPkRgrCellCntrlCmdCfg, &param->cntrlCmdCfg, mBuf);
   CMCHKPK(cmPkRgrCellCsgParamCfg, &param->csgParamCfg, mBuf);
   CMCHKPK(SPkU8, param->isDynCfiEnb, mBuf);
   CMCHKPK(SPkU8, param->isAutoCfgModeEnb, mBuf);
   /* LTE_ADV_FLAG_REMOVED_START */
   CMCHKPK(cmPkRgrCellLteAdvancedFeatureCfg, &param->rgrLteAdvCfg, mBuf);
   /* LTE_ADV_FLAG_REMOVED_END */
   CMCHKPK(SPkU16, param->t300TmrVal, mBuf);
   /* rgr_c_001.main_4:MOD-Modified for SI Enhancement. */
#ifdef RGR_SI_SCH
   CMCHKPK(cmPkRgrSiCfg, &param->siReCfg, mBuf);
#endif /* RGR_SI_SCH */
   CMCHKPK(cmPkRgrDlfsCfg, &param->dlfsRecfg, mBuf);
   CMCHKPK(cmPkRgrRachCfg, &param->rachRecfg, mBuf);
   CMCHKPK(cmPkRgrSrsCfg, &param->srsRecfg, mBuf);
   CMCHKPK(cmPkRgrPucchCfg, &param->pucchRecfg, mBuf);
   CMCHKPK(cmPkRgrUlCmnCodeRateCfg, &param->ulCmnCodeRate, mBuf);
   CMCHKPK(cmPkRgrPuschSubBandCfg, &param->puschSubBand, mBuf);
   CMCHKPK(cmPkRgrDlCmnCodeRateCfg, &param->dlCmnCodeRate, mBuf);
   CMCHKPK(cmPkRgrUlTrgCqiCfg, &param->trgUlCqi, mBuf);
   CMCHKPK(cmPkRgrCfiCfg, &param->cfiRecfg, mBuf);
   CMCHKPK(cmPkRgrDlHqCfg, &param->dlHqRecfg, mBuf);
   CMCHKPK(cmPkRgrActvTime, &param->recfgActvTime, mBuf);
   CMCHKPK(SPkU32, param->recfgTypes, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrCellRecfg
*
*
*     Desc : Cell reconfiguration structure at RRM
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
PUBLIC S16 cmUnpkRgrCellRecfg
(
RgrCellRecfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrCellRecfg(param, mBuf)
RgrCellRecfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrCellRecfg)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(SUnpkU32, &param->recfgTypes, mBuf);
   CMCHKUNPK(cmUnpkRgrActvTime, &param->recfgActvTime, mBuf);
   CMCHKUNPK(cmUnpkRgrDlHqCfg, &param->dlHqRecfg, mBuf);
   CMCHKUNPK(cmUnpkRgrCfiCfg, &param->cfiRecfg, mBuf);
   CMCHKUNPK(cmUnpkRgrUlTrgCqiCfg, &param->trgUlCqi, mBuf);
   CMCHKUNPK(cmUnpkRgrDlCmnCodeRateCfg, &param->dlCmnCodeRate, mBuf);
   CMCHKUNPK(cmUnpkRgrPuschSubBandCfg, &param->puschSubBand, mBuf);
   CMCHKUNPK(cmUnpkRgrUlCmnCodeRateCfg, &param->ulCmnCodeRate, mBuf);
   CMCHKUNPK(cmUnpkRgrPucchCfg, &param->pucchRecfg, mBuf);
   CMCHKUNPK(cmUnpkRgrSrsCfg, &param->srsRecfg, mBuf);
   CMCHKUNPK(cmUnpkRgrRachCfg, &param->rachRecfg, mBuf);
   CMCHKUNPK(cmUnpkRgrDlfsCfg, &param->dlfsRecfg, mBuf);
   /* rgr_c_001.main_4-MOD-Modified for SI Enhancement. */
#ifdef RGR_SI_SCH
   CMCHKUNPK(cmUnpkRgrSiCfg, &param->siReCfg, mBuf);
#endif /* RGR_SI_SCH */
   CMCHKUNPK(SUnpkU16, &param->t300TmrVal, mBuf);
   /* LTE_ADV_FLAG_REMOVED_START */
   CMCHKUNPK(cmUnpkRgrCellLteAdvancedFeatureCfg, &param->rgrLteAdvCfg, mBuf);
   /* LTE_ADV_FLAG_REMOVED_END */
   CMCHKUNPK(SUnpkU8, &param->isAutoCfgModeEnb, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isDynCfiEnb, mBuf);
   CMCHKUNPK(cmUnpkRgrCellCsgParamCfg, &param->csgParamCfg, mBuf);
   CMCHKUNPK(cmUnpkRgrCellCntrlCmdCfg, &param->cntrlCmdCfg, mBuf);

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrUeRecfg
*
*
*     Desc : UE reconfiguration info
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
PUBLIC S16 cmPkRgrUeRecfg
(
RgrUeRecfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeRecfg(param, mBuf)
RgrUeRecfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrUeRecfg)
   CMCHKPK(SPkU8, param->csgMmbrSta, mBuf);
  
   CMCHKPK(SPkU32, param->accessStratumRls, mBuf);
#ifdef LTE_ADV 
   CMCHKPK(cmPkRgrUeSCellAckPucchCfg, &param->sCellAckN1ResCfg,mBuf);
   CMCHKPK(cmPkRgrUeSecCellInfo, &param->ueSCellCfgInfo,mBuf);
#endif
   /* LTE_ADV_FLAG_REMOVED_START */
   CMCHKPK(SPkU8, param->ueLteAdvCfg.isUeCellEdge, mBuf);
   CMCHKPK(SPkU8, param->ueLteAdvCfg.isAbsUe, mBuf);
   CMCHKPK(SPkU32, param->ueLteAdvCfg.pres, mBuf);
   /* LTE_ADV_FLAG_REMOVED_END */
   /*ccpu00130497: Removed the duplicate packing*/
#ifdef TFU_UPGRADE
   CMCHKPK(cmPkRgrUePdschDedCfg, &param->uePdschDedCfg, mBuf);
#endif
   /* rgr_c_001.main_9 ccpu00117452 - MOD - Changed macro name from
   RGR_RRM_DLPWR_CNTRL to RGR_CQI_REPT */
#ifdef RGR_CQI_REPT
   CMCHKPK(cmPkRgrUeCqiReptCfg, &param->ueCqiReptCfg, mBuf);
#endif

/* rgr_c_001.main_8. Added changes of TFU_UPGRADE */
   CMCHKPK(cmPkRgrUePuschDedCfg, &param->puschDedCfg, mBuf);

/*rgr_c_001.main_9 ADD added changes for HDFDD*/
#ifdef LTEMAC_HDFDD
   CMCHKPK(SPkU8, param->isHdFddEnbld, mBuf);
#endif

#ifdef TFU_UPGRADE
   CMCHKPK(cmPkRgrUeSrCfg, &param->srCfg, mBuf);
   CMCHKPK(cmPkRgrUeUlSrsCfg, &param->srsCfg, mBuf);
   CMCHKPK(cmPkRgrUePrdDlCqiCfg, &param->cqiCfg, mBuf);
#endif 

   /*rgr_c_001.main_7 - Added support for SPS*/
   CMCHKPK(cmPkRgrUeSpsCfg, &param->ueSpsRecfg, mBuf);
   CMCHKPK(cmPkRgrUeTxAntSelCfg, &param->ulTxAntSel, mBuf);

   /* rgr_c_001.main_7 - Changes for UE category Reconfiguration */
   CMCHKPK(SPkU32, param->ueCatEnum, mBuf);

   CMCHKPK(cmPkRgrCodeBookRstCfg, &param->ueCodeBookRstRecfg, mBuf);
   CMCHKPK(cmPkRgrUeMeasGapCfg, &param->ueMeasGapRecfg, mBuf);
   CMCHKPK(cmPkRgrUeCapCfg, &param->ueCapRecfg, mBuf);
   CMCHKPK(cmPkRgrUeAckNackRepCfg, &param->ueAckNackRecfg, mBuf);
   CMCHKPK(SPkU8, param->isTtiBundlEnabled, mBuf);
/*rgr_c_001.main_9 ADD added changes for DRX*/
   
   /* Anshika - Pack only if DRX is enabled */
   if(TRUE == param->ueDrxRecfg.isDrxEnabled)
   {
      CMCHKPK(cmPkRgrUeDrxCfg, &param->ueDrxRecfg, mBuf);
   }
   CMCHKPK(SPkU8, param->ueDrxRecfg.isDrxEnabled, mBuf); /* This has to be packed even if
                                                 DRX is disabled */
   CMCHKPK(cmPkRgrUeUlPwrCfg, &param->ueUlPwrRecfg, mBuf);
#ifdef RGR_V1
   /* rgr_c_001.main_5: ccpu00112398: Added periodicBSR-timer and
    * retxBSR-timer */
   CMCHKPK(cmPkRgrUeBsrTmrCfg, &param->ueBsrTmrRecfg, mBuf);
#endif
   CMCHKPK(cmPkRgrUeTaTmrCfg, &param->ueTaTmrRecfg, mBuf);
   CMCHKPK(cmPkRgrUeQosCfg, &param->ueQosRecfg, mBuf);
   CMCHKPK(cmPkRgrUeUlHqCfg, &param->ueUlHqRecfg, mBuf);

#ifndef TFU_UPGRADE
   CMCHKPK(cmPkRgrUePrdDlCqiCfg, &param->prdDlCqiRecfg, mBuf);
#endif

   CMCHKPK(cmPkRgrUeAprdDlCqiCfg, &param->aprdDlCqiRecfg, mBuf);
   CMCHKPK(cmPkRgrUeTxModeCfg, &param->txMode, mBuf);
   /*rgr_c_001.main_9: changing ueRecfgTypes to U32 */
   /* LTE_ADV_FLAG_REMOVED_START */
   /* KW fix for LTE_ADV */
   CMCHKPK(SPkU32, param->ueRecfgTypes, mBuf);
   /* LTE_ADV_FLAG_REMOVED_END */
   CMCHKPK(cmPkLteRnti, param->newCrnti, mBuf);
   CMCHKPK(cmPkLteRnti, param->oldCrnti, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrUeRecfg
*
*
*     Desc : UE reconfiguration info
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
PUBLIC S16 cmUnpkRgrUeRecfg
(
RgrUeRecfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeRecfg(param, mBuf)
RgrUeRecfg *param;
Buffer *mBuf;
#endif
{
   U32 tmpEnum;

   TRC3(cmUnpkRgrUeRecfg)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &param->oldCrnti, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &param->newCrnti, mBuf);
   /* LTE_ADV_FLAG_REMOVED_START */
   /*rgr_c_001.main_9: changing ueRecfgTypes to U32 */
   /* KW fix for LTE_ADV */
   CMCHKUNPK(SUnpkU32, &param->ueRecfgTypes, mBuf);
   /* LTE_ADV_FLAG_REMOVED_END */
   CMCHKUNPK(cmUnpkRgrUeTxModeCfg, &param->txMode, mBuf);

   CMCHKUNPK(cmUnpkRgrUeAprdDlCqiCfg, &param->aprdDlCqiRecfg, mBuf);

#ifndef TFU_UPGRADE
   CMCHKUNPK(cmUnpkRgrUePrdDlCqiCfg, &param->prdDlCqiRecfg, mBuf);
#endif

   CMCHKUNPK(cmUnpkRgrUeUlHqCfg, &param->ueUlHqRecfg, mBuf);
   CMCHKUNPK(cmUnpkRgrUeQosCfg, &param->ueQosRecfg, mBuf);
   CMCHKUNPK(cmUnpkRgrUeTaTmrCfg, &param->ueTaTmrRecfg, mBuf);
#ifdef RGR_V1
   /* rgr_c_001.main_5: ccpu00112398: Added periodicBSR-timer and
    * retxBSR-timer */
   CMCHKUNPK(cmUnpkRgrUeBsrTmrCfg, &param->ueBsrTmrRecfg, mBuf);
#endif
   CMCHKUNPK(cmUnpkRgrUeUlPwrCfg, &param->ueUlPwrRecfg, mBuf);
/*rgr_c_001.main_9 ADD added changes for DRX*/
   
   /* Anshika - Unpack only if DRX is enabled */
   CMCHKUNPK(SUnpkU8, &param->ueDrxRecfg.isDrxEnabled, mBuf);
   if(TRUE == param->ueDrxRecfg.isDrxEnabled)
   {
      CMCHKUNPK(cmUnpkRgrUeDrxCfg, &param->ueDrxRecfg, mBuf);
   }
   CMCHKUNPK(SUnpkU8, &param->isTtiBundlEnabled, mBuf);
   CMCHKUNPK(cmUnpkRgrUeAckNackRepCfg, &param->ueAckNackRecfg, mBuf);
   CMCHKUNPK(cmUnpkRgrUeCapCfg, &param->ueCapRecfg, mBuf);
   CMCHKUNPK(cmUnpkRgrUeMeasGapCfg, &param->ueMeasGapRecfg, mBuf);
   CMCHKUNPK(cmUnpkRgrCodeBookRstCfg, &param->ueCodeBookRstRecfg, mBuf);
/* rgr_c_001.main_7 - Changes for UE category Reconfiguration */
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->ueCatEnum = (CmLteUeCategory) tmpEnum;
   CMCHKUNPK(cmUnpkRgrUeTxAntSelCfg, &param->ulTxAntSel, mBuf);
   /*rgr_c_001.main_7 - Added support for SPS*/
   CMCHKUNPK(cmUnpkRgrUeSpsCfg, &param->ueSpsRecfg, mBuf);

/* rgr_c_001.main_8. Added changes of TFU_UPGRADE */
#ifdef TFU_UPGRADE
   CMCHKUNPK(cmUnpkRgrUePrdDlCqiCfg, &param->cqiCfg, mBuf);
   CMCHKUNPK(cmUnpkRgrUeUlSrsCfg, &param->srsCfg, mBuf);
   CMCHKUNPK(cmUnpkRgrUeSrCfg, &param->srCfg, mBuf);
#endif

/*rgr_c_001.main_9 ADD added changes for HDFDD*/
#ifdef LTEMAC_HDFDD
   CMCHKUNPK(SUnpkU8, &param->isHdFddEnbld, mBuf);
#endif

   CMCHKUNPK(cmUnpkRgrUePuschDedCfg, &param->puschDedCfg, mBuf);

/* rgr_c_001.main_9 ccpu00117452 - MOD - Changed macro name from
   RGR_RRM_DLPWR_CNTRL to RGR_CQI_REPT */
#ifdef RGR_CQI_REPT
   CMCHKUNPK(cmUnpkRgrUeCqiReptCfg, &param->ueCqiReptCfg, mBuf);
#endif
#ifdef TFU_UPGRADE
   CMCHKUNPK(cmUnpkRgrUePdschDedCfg, &param->uePdschDedCfg, mBuf);
#endif

   /* LTE_ADV_FLAG_REMOVED_START */
   CMCHKUNPK(SUnpkU32, &param->ueLteAdvCfg.pres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ueLteAdvCfg.isAbsUe, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ueLteAdvCfg.isUeCellEdge, mBuf);
   /* LTE_ADV_FLAG_REMOVED_END */
#ifdef LTE_ADV 
   CMCHKUNPK(cmUnpkRgrUeSecCellInfo, &param->ueSCellCfgInfo,mBuf);
   CMCHKUNPK(cmUnpkRgrUeSCellAckPucchCfg, &param->sCellAckN1ResCfg,mBuf);
#endif
   CMCHKUNPK(SUnpkU32, (U32 *)&param->accessStratumRls, mBuf);

   CMCHKUNPK(SUnpkU8, &param->csgMmbrSta, mBuf);

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrLchRecfg
*
*
*     Desc : Logical channel reconfiguration info for dedicated channels only
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
PUBLIC S16 cmPkRgrLchRecfg
(
RgrLchRecfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrLchRecfg(param, mBuf)
RgrLchRecfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrLchRecfg)
/*rgr_c_001.main_7 - Added support for SPS*/
   CMCHKPK(SPkU8, param->lcgId, mBuf);
   
   CMCHKPK(cmPkRgrUlLchQciCfg, &param->ulLchQciInfo, mBuf);
   CMCHKPK(cmPkRgrLchSpsCfg, &param->dlRecfg.dlSpsRecfg, mBuf);
   
   CMCHKPK(cmPkRgrLchQosCfg, &param->dlRecfg.dlQos, mBuf);
   CMCHKPK(cmPkLteLcId, param->lcId, mBuf);
   CMCHKPK(cmPkLteRnti, param->crnti, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrLchRecfg
*
*
*     Desc : Logical channel reconfiguration info for dedicated channels only
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
PUBLIC S16 cmUnpkRgrLchRecfg
(
RgrLchRecfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrLchRecfg(param, mBuf)
RgrLchRecfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrLchRecfg)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &param->crnti, mBuf);
   CMCHKUNPK(cmUnpkLteLcId, &param->lcId, mBuf);
   CMCHKUNPK(cmUnpkRgrLchQosCfg, &param->dlRecfg.dlQos, mBuf);
      /*rgr_c_001.main_7 - Added support for SPs*/
   CMCHKUNPK(cmUnpkRgrLchSpsCfg, &param->dlRecfg.dlSpsRecfg, mBuf);

   CMCHKUNPK(cmUnpkRgrUlLchQciCfg, &param->ulLchQciInfo, mBuf);   
   CMCHKUNPK(SUnpkU8, &param->lcgId, mBuf);
   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmPkRgrLcgRecfg
(
RgrLcgRecfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrLcgRecfg(param, mBuf)
RgrLcgRecfg *param;
Buffer *mBuf;
#endif
{
#ifdef RG_UNUSED
   S32 i;
#endif
   TRC3(cmPkRgrLcgRecfg)

   CMCHKPK(SPkU32, param->ulRecfg.mbr, mBuf);
   CMCHKPK(SPkU32, param->ulRecfg.gbr, mBuf);
#ifdef RG_UNUSED
   for (i = param->ulRecfg.numLch - 1; i >= 0; i--)
   {
      CMCHKPK(cmPkRgrUlLchCfg, &param->ulRecfg.lchUlCfg[i], mBuf);
   }
   CMCHKPK(SPkU8, param->ulRecfg.numLch, mBuf);
#endif
   CMCHKPK(SPkU8, param->ulRecfg.lcgId, mBuf);
   CMCHKPK(cmPkLteRnti, param->crnti, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmUnpkRgrLcgRecfg
(
RgrLcgRecfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrLcgRecfg(param, mBuf)
RgrLcgRecfg *param;
Buffer *mBuf;
#endif
{
#ifdef RG_UNUSED
   S32 i;
#endif
   TRC3(cmUnpkRgrLcgRecfg)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &param->crnti, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ulRecfg.lcgId, mBuf);

#ifdef RG_UNUSED
   CMCHKUNPK(SUnpkU8, &param->ulRecfg.numLch, mBuf);
   for (i = 0; i < param->ulRecfg.numLch; i++)
   {
      CMCHKUNPK(cmUnpkRgrUlLchCfg, &param->ulRecfg.lchUlCfg[i], mBuf);
   }
#endif
   CMCHKUNPK(SUnpkU32, &param->ulRecfg.gbr, mBuf);
   CMCHKUNPK(SUnpkU32, &param->ulRecfg.mbr, mBuf);

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrRecfg
*
*
*     Desc : Basic reconfiguration structure at RRM
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
PUBLIC S16 cmPkRgrRecfg
(
RgrRecfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrRecfg(param, mBuf)
RgrRecfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrRecfg)

      switch(param->recfgType) {
         case RGR_LCG_CFG:
            CMCHKPK(cmPkRgrLcgRecfg, &param->u.lcgRecfg, mBuf);
            break;
         case RGR_LCH_CFG:
            CMCHKPK(cmPkRgrLchRecfg, &param->u.lchRecfg, mBuf);
            break;
         case RGR_UE_CFG:
            CMCHKPK(cmPkRgrUeRecfg, &param->u.ueRecfg, mBuf);
            break;
         case RGR_CELL_CFG:
            CMCHKPK(cmPkRgrCellRecfg, &param->u.cellRecfg, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(SPkU8, param->recfgType, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrRecfg
*
*
*     Desc : Basic reconfiguration structure at RRM
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
PUBLIC S16 cmUnpkRgrRecfg
(
RgrRecfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrRecfg(param, mBuf)
RgrRecfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrRecfg)

   CMCHKUNPK(SUnpkU8, &param->recfgType, mBuf);
      switch(param->recfgType) {
         case RGR_CELL_CFG:
            CMCHKUNPK(cmUnpkRgrCellRecfg, &param->u.cellRecfg, mBuf);
            break;
         case RGR_UE_CFG:
            CMCHKUNPK(cmUnpkRgrUeRecfg, &param->u.ueRecfg, mBuf);
            break;
         case RGR_LCH_CFG:
            CMCHKUNPK(cmUnpkRgrLchRecfg, &param->u.lchRecfg, mBuf);
            break;
         case RGR_LCG_CFG:
            CMCHKUNPK(cmUnpkRgrLcgRecfg, &param->u.lcgRecfg, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}

#ifdef LTE_ADV
/***********************************************************
*
*     Func : cmPkRgrUeDlSecCellRelInfo
*
*
*     Desc : DL Secondary Cell information of the UE
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
PUBLIC S16 cmPkRgrUeDlSecCellRelInfo
(
RgrUeDlSecCellRelInfo *param,
Buffer *mBuf
)
#else
PRIVATE S16 cmPkRgrUeDlSecCellRelInfo(param, mBuf)
RgrUeDlSecCellRelInfo *param;
Buffer *mBuf;
#endif
{
   CMCHKPK(SPkU16, param->sCellId, mBuf);
   CMCHKPK(SPkU8, param->sCellIdx, mBuf);
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmPkRgrUeSecCellRelInfo
*
*
*     Desc : Secondary Cell Delete information of the UE
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
PUBLIC S16 cmPkRgrUeSecCellRelInfo
(
RgrUeSecCellRelInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeSecCellRelInfo(param, mBuf)
RgrUeSecCellRelInfo *param;
Buffer *mBuf;
#endif
{
   S8 idx;
   for(idx = param->numSCells - 1; idx >= 0; idx--)
   {
      CMCHKPK(cmPkRgrUeDlSecCellRelInfo, &param->ueSCellRelDedCfg[(U8)idx],mBuf);
   }
   CMCHKPK(SPkU8, param->numSCells, mBuf);

   RETVALUE(ROK);
}
#endif


/***********************************************************
*
*     Func : cmPkRgrDel
*
*
*     Desc : Basic Delete info for MAC
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
PUBLIC S16 cmPkRgrDel
(
RgrDel *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrDel(param, mBuf)
RgrDel *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrDel)

      switch(param->delType) {
         case RGR_LCG_CFG:
            CMCHKPK(SPkU8, param->u.lcgDel.lcgId, mBuf);
            CMCHKPK(cmPkLteRnti, param->u.lcgDel.crnti, mBuf);
            CMCHKPK(cmPkLteCellId, param->u.lcgDel.cellId, mBuf);
         break;
         case RGR_LCH_CFG:
            CMCHKPK(SPkU8, param->u.lchDel.lcgId, mBuf);
            CMCHKPK(cmPkLteLcId, param->u.lchDel.lcId, mBuf);
            CMCHKPK(cmPkLteRnti, param->u.lchDel.crnti, mBuf);
            CMCHKPK(cmPkLteCellId, param->u.lchDel.cellId, mBuf);
         break;
         case RGR_UE_CFG:
            CMCHKPK(cmPkLteRnti, param->u.ueDel.crnti, mBuf);
            CMCHKPK(cmPkLteCellId, param->u.ueDel.cellId, mBuf);
         break;
         case RGR_CELL_CFG:
            CMCHKPK(cmPkLteCellId, param->u.cellDel.cellId, mBuf);
         break;
#ifdef LTE_ADV
         case RGR_SCELL_UE_CFG:
            CMCHKPK(cmPkRgrUeSecCellRelInfo, &param->u.ueScellRel.ueSCellRelCfgInfo, mBuf);
            CMCHKPK(SPkU32, param->u.ueScellRel.ueDelTypes, mBuf);
            CMCHKPK(cmPkLteRnti, param->u.ueScellRel.crnti, mBuf);
            CMCHKPK(cmPkLteCellId, param->u.ueScellRel.cellId, mBuf);
         break;
#endif
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(SPkU8, param->delType, mBuf);
   RETVALUE(ROK);
}


#ifdef LTE_ADV

/***********************************************************
*
*     Func : cmUnpkRgrUeDlSecCellRelInfo
*
*
*     Desc : DL Secondary Cell information of the UE
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
PUBLIC S16 cmUnpkRgrUeDlSecCellRelInfo
(
RgrUeDlSecCellRelInfo *param,
Buffer *mBuf
)
#else
PRIVATE S16 cmUnpkRgrUeDlSecCellRelInfo(param, mBuf)
RgrUeDlSecCellRelInfo *param;
Buffer *mBuf;
#endif
{
   CMCHKUNPK(SUnpkU8, &param->sCellIdx, mBuf);
   CMCHKUNPK(SUnpkU16, &param->sCellId, mBuf);
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmUnpkRgrUeSecCellRelInfo
*
*
*     Desc : Secondary Cell information of the UE
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
PUBLIC S16 cmUnpkRgrUeSecCellRelInfo
(
RgrUeSecCellRelInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeSecCellRelInfo(param, mBuf)
RgrUeSecCellRelInfo *param;
Buffer *mBuf;
#endif
{
   U8 idx;

   CMCHKUNPK(SUnpkU8, &param->numSCells, mBuf);

   for(idx = 0; idx < param->numSCells;idx++)
   {
      CMCHKUNPK(cmUnpkRgrUeDlSecCellRelInfo, &param->ueSCellRelDedCfg[idx],mBuf);
   }
   RETVALUE(ROK);
}
#endif

/***********************************************************
*
*     Func : cmUnpkRgrDel
*
*
*     Desc : Basic Delete info for MAC
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
PUBLIC S16 cmUnpkRgrDel
(
RgrDel *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrDel(param, mBuf)
RgrDel *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrDel)

   CMCHKUNPK(SUnpkU8, &param->delType, mBuf);
      switch(param->delType) {
         case RGR_CELL_CFG:
            CMCHKUNPK(cmUnpkLteCellId, &param->u.cellDel.cellId, mBuf);
         break;
         case RGR_UE_CFG:
            CMCHKUNPK(cmUnpkLteCellId, &param->u.ueDel.cellId, mBuf);
            CMCHKUNPK(cmUnpkLteRnti, &param->u.ueDel.crnti, mBuf);
         break;
         case RGR_LCH_CFG:
            CMCHKUNPK(cmUnpkLteCellId, &param->u.lchDel.cellId, mBuf);
            CMCHKUNPK(cmUnpkLteRnti, &param->u.lchDel.crnti, mBuf);
            CMCHKUNPK(cmUnpkLteLcId, &param->u.lchDel.lcId, mBuf);
            CMCHKUNPK(SUnpkU8, &param->u.lchDel.lcgId, mBuf);
         break;
         case RGR_LCG_CFG:
            CMCHKUNPK(cmUnpkLteCellId, &param->u.lcgDel.cellId, mBuf);
            CMCHKUNPK(cmUnpkLteRnti, &param->u.lcgDel.crnti, mBuf);
            CMCHKUNPK(SUnpkU8, &param->u.lcgDel.lcgId, mBuf);
         break;
#ifdef LTE_ADV
         case RGR_SCELL_UE_CFG:
            CMCHKUNPK(cmUnpkLteCellId, &param->u.ueScellRel.cellId, mBuf);
            CMCHKUNPK(cmUnpkLteRnti, &param->u.ueScellRel.crnti, mBuf);
            CMCHKUNPK(SUnpkU32, &param->u.ueScellRel.ueDelTypes, mBuf);
            CMCHKUNPK(cmUnpkRgrUeSecCellRelInfo, &param->u.ueScellRel.ueSCellRelCfgInfo, mBuf);
         break;
#endif
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}
/***********************************************************
*
*     Func : cmPkRgrSonPrbCfg
*
*
*     Desc : SON PRB Configuration info for MAC
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
PUBLIC S16 cmPkRgrSonPrbCfg
(
RgrPrbCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrSonPrbCfg(param, mBuf)
RgrPrbCfg *param;
Buffer *mBuf;
#endif
{
   S32 count;
   TRC3(cmPkRgrPrbCfg)
   for(count = RGR_SCH_MAX_PA_PER_PRB - 1; count >= 0; count --)
   {
      CMCHKPK(SPkU32, param->paLevelPerPrb[count], mBuf);
   }
   for(count = param->numCellCentreUEs - 1; count >= 0; count --)
   {
      CMCHKPK(cmPkLteRnti, param->cellCentreUe[count], mBuf);
   } 
   for(count = param->numCellEdgeUEs - 1; count >= 0; count --)
   {
      CMCHKPK(cmPkLteRnti, param->cellEdgeUe[count], mBuf);
   }
   CMCHKPK(SPkU8, param->numCellCentreUEs, mBuf);
   CMCHKPK(SPkU8, param->numCellEdgeUEs, mBuf);
   CMCHKPK(SPkU8, param->isSonIcicEnable, mBuf);
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmUnpkRgrSon
*
*
*     Desc : SON configuration info for MAC
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
PUBLIC S16 cmUnpkRgrSonPrbCfg
(
RgrPrbCfg   *param,
Buffer      *mBuf
)
#else
PUBLIC S16 cmUnpkRgrSonPrbCfg(param, mBuf)
RgrPrbCfg   *param;
Buffer      *mBuf;
#endif
{
   S32   count;
   TRC3(cmUnpkRgrSonPrbCfg)
   CMCHKUNPK(SUnpkU8, &param->isSonIcicEnable, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numCellEdgeUEs, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numCellCentreUEs, mBuf);
   for (count = 0; count < param->numCellEdgeUEs; count++)
   {
      CMCHKUNPK(cmUnpkLteRnti, &param->cellEdgeUe[count], mBuf);
   }
   for (count = 0; count < param->numCellCentreUEs; count++)
   {
      CMCHKUNPK(cmUnpkLteRnti, &param->cellCentreUe[count], mBuf);
   }
   for(count = 0; count < RGR_SCH_MAX_PA_PER_PRB; count ++)
   {
      CMCHKUNPK(SUnpkU32,(U32 *) &param->paLevelPerPrb[count], mBuf);
   }
   RETVALUE(ROK);
}
/***********************************************************
*
*     Func : cmPkRgrSonCfg
*
*
*     Desc : SON Configuration info for MAC
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
PUBLIC S16 cmPkRgrSonCfg
(
RgrSonCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrSonCfg(param, mBuf)
RgrSonCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrSonCfg)
   switch(param->cfgType)
   {
      case RGR_SON_PRB_CFG :
      CMCHKPK(cmPkRgrSonPrbCfg, &param->u.prbCfg, mBuf);
      break;
      default :
      RETVALUE(RFAILED);
   }
   CMCHKPK(SPkU32, param->cfgType, mBuf);
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmUnpkRgrSon
*
*
*     Desc : SON configuration info for MAC
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
PUBLIC S16 cmUnpkRgrSonCfg
(
RgrSonCfg   *param,
Buffer      *mBuf
)
#else
PUBLIC S16 cmUnpkRgrSonCfg(param, mBuf)
RgrSonCfg   *param;
Buffer      *mBuf;
#endif
{

   TRC3(cmUnpkRgrSonCfg)
   CMCHKUNPK(SUnpkU32, (U32 *)&param->cfgType, mBuf);
   switch(param->cfgType)
   {
      case RGR_SON_PRB_CFG :
      {
         CMCHKUNPK(cmUnpkRgrSonPrbCfg, &param->u.prbCfg, mBuf);
         break;
         default :
         RETVALUE(RFAILED);
      }
   }
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkRgrRst
*
*
*     Desc : UE RESET info for MAC
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
PUBLIC S16 cmPkRgrRst
(
RgrRst *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrRst(param, mBuf)
RgrRst *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrRst)

   CMCHKPK(cmPkLteRnti, param->crnti, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrRst
*
*
*     Desc : UE RESET info for MAC
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
PUBLIC S16 cmUnpkRgrRst
(
RgrRst *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrRst(param, mBuf)
RgrRst *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrRst)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &param->crnti, mBuf);
   RETVALUE(ROK);
}
#ifdef LTE_ADV
/***********************************************************
*
*     Func : cmUnPkRgrSCellActDeactInfo
*
*
*     Desc : SCell Activation information of the UE
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
PRIVATE S16 cmUnPkRgrSCellActDeactInfo
(
RgrSCellActDeactInfo *param,
Buffer *mBuf
)
#else
PRIVATE S16 cmUnPkRgrSCellActInfo(param, mBuf)
RgrSCellActDeactInfo *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnPkRgrSCellActDeactInfo)

   CMCHKUNPK(SUnpkU8, &param->sCellIdx, mBuf);
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmUnPkRgrSCellActDeactEvnt
*
*
*     Desc : SCell Activation Configuration structure to SCH
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
PUBLIC S16 cmUnPkRgrSCellActDeactEvnt
(
RgrSCellActDeactEvnt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnPkRgrSCellActDeactEvnt(param, mBuf)
RgrSCellActDeactEvnt *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnPkRgrSCellActDeactEvnt)

   U8 idx;

   CMCHKUNPK(cmUnpkLteRnti, &param->crnti, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numOfSCells, mBuf);

   for(idx = 0; idx < param->numOfSCells;idx++)
   {
      CMCHKUNPK(cmUnPkRgrSCellActDeactInfo, &param->sCellActDeactInfo[idx],mBuf);
   }

   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkRgrSCellActInfo
*
*
*     Desc : SCell Activation information of the UE
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
PRIVATE S16 cmPkRgrSCellActDeactInfo
(
RgrSCellActDeactInfo *param,
Buffer *mBuf
)
#else
PRIVATE S16 cmPkRgrSCellActDeactInfo(param, mBuf)
RgrSCellActDeactInfo *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkRgrSCellActDeactInfo)

   CMCHKPK(SPkU8, param->sCellIdx, mBuf);

   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmPkRgrSCellActDeactEvnt
*
*
*     Desc : Basic Configuration structure at SCH
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
PUBLIC S16 cmPkRgrSCellActDeactEvnt
(
RgrSCellActDeactEvnt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrSCellActDeactEvnt(param, mBuf)
RgrSCellActDeactEvnt *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrSCellActDeactEvnt)

   S8 idx;
   for(idx = param->numOfSCells - 1; idx >= 0; idx--)
   {
      CMCHKPK(cmPkRgrSCellActDeactInfo, &param->sCellActDeactInfo[(U8)idx], mBuf);
   }

   CMCHKPK(SPkU8, param->numOfSCells, mBuf);
   CMCHKPK(cmPkLteRnti, param->crnti, mBuf);

   RETVALUE(ROK);
}


#endif /* LTE_ADV */

/***********************************************************
*
*     Func : cmPkRgrCfgReqInfo
*
*
*     Desc : Basic RGR configuration/reconfiguration info at RRM
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
PUBLIC S16 cmPkRgrCfgReqInfo
(
RgrCfgReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrCfgReqInfo(param, mBuf)
RgrCfgReqInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrCfgReqInfo)

      switch(param->action) {
         case RGR_SON_CFG:
            CMCHKPK(cmPkRgrSonCfg, &param->u.sonCfg, mBuf);
            break;
         case RGR_RESET:
            CMCHKPK(cmPkRgrRst, &param->u.rstInfo, mBuf);
            break;
         case RGR_DELETE:
            CMCHKPK(cmPkRgrDel, &param->u.delInfo, mBuf);
            break;
         case RGR_RECONFIG:
            CMCHKPK(cmPkRgrRecfg, &param->u.recfgInfo, mBuf);
            break;
         case RGR_CONFIG:
            CMCHKPK(cmPkRgrCfg, &param->u.cfgInfo, mBuf);
            break;
#ifdef LTE_ADV
         case RGR_SCELL_ACT:
         case RGR_SCELL_DEACT:
         case RGR_SCELL_READY:
            CMCHKPK(cmPkRgrSCellActDeactEvnt, &param->u.sCellActDeactEvnt, mBuf);
            break;
#endif
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(SPkU8, param->action, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgrCfgReqInfo
*
*
*     Desc : Basic RGR configuration/reconfiguration info at RRM
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
PUBLIC S16 cmUnpkRgrCfgReqInfo
(
RgrCfgReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrCfgReqInfo(param, mBuf)
RgrCfgReqInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrCfgReqInfo)

   CMCHKUNPK(SUnpkU8, &param->action, mBuf);
      switch(param->action) {
         case RGR_CONFIG:
            CMCHKUNPK(cmUnpkRgrCfg, &param->u.cfgInfo, mBuf);
            break;
         case RGR_RECONFIG:
            CMCHKUNPK(cmUnpkRgrRecfg, &param->u.recfgInfo, mBuf);
            break;
         case RGR_DELETE:
            CMCHKUNPK(cmUnpkRgrDel, &param->u.delInfo, mBuf);
            break;
         case RGR_RESET:
            CMCHKUNPK(cmUnpkRgrRst, &param->u.rstInfo, mBuf);
            break;
         case RGR_SON_CFG:
            CMCHKUNPK(cmUnpkRgrSonCfg, &param->u.sonCfg, mBuf);
            break;
#ifdef LTE_ADV
         case RGR_SCELL_ACT:
         case RGR_SCELL_DEACT:
         case RGR_SCELL_READY:
            CMCHKUNPK(cmUnPkRgrSCellActDeactEvnt, &param->u.sCellActDeactEvnt, mBuf);
            break;
#endif /* LTE_ADV */
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}
#ifdef RGR_V1
/* rgr_c_001.main_5: ccpu00112398: Added periodicBSR-timer and
 * retxBSR-timer */
/***********************************************************
*
*     Func : cmPkRgrUeBsrTmrCfg
*
*
*     Desc : BSR timer configuration per UE
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
PUBLIC S16 cmPkRgrUeBsrTmrCfg
(
RgrUeBsrTmrCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeBsrTmrCfg(param, mBuf)
RgrUeBsrTmrCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrUeBsrTmrCfg)

   CMCHKPK(SPkU16, param->prdBsrTmr, mBuf);
   CMCHKPK(SPkU16, param->retxBsrTmr, mBuf);
   CMCHKPK(SPkU8, param->isPrdBsrTmrPres, mBuf);
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmUnpkRgrUeBsrTmrCfg
*
*
*     Desc : BSR timer configuration per UE
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
PUBLIC S16 cmUnpkRgrUeBsrTmrCfg
(
RgrUeBsrTmrCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeBsrTmrCfg(param, mBuf)
RgrUeBsrTmrCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrUeBsrTmrCfg)

   CMCHKUNPK(SUnpkU8, &param->isPrdBsrTmrPres, mBuf);
   CMCHKUNPK(SUnpkU16, &param->retxBsrTmr, mBuf);
   CMCHKUNPK(SUnpkU16, &param->prdBsrTmr, mBuf);
   RETVALUE(ROK);
}
#endif /* RGR_V1 */
/* rgr_c_001.main_4-ADD-Added for SI Enhancement. */
#ifdef RGR_SI_SCH
/***********************************************************
*
*     Func : cmPkRgrSiCfgReq
*
*
*     Desc : SI Configuration Request from RRM to MAC for 
*            configuring SI
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
PUBLIC S16 cmPkRgrSiCfgReq
(
Pst* pst,
SpId spId,
RgrCfgTransId transId,
RgrSiCfgReqInfo * cfgReqInfo
)
#else
PUBLIC S16 cmPkRgrSiCfgReq(pst, spId, transId, cfgReqInfo)
Pst* pst;
SpId spId;
RgrCfgTransId transId;
RgrSiCfgReqInfo * cfgReqInfo;
#endif
{
   Buffer *mBuf = NULLP;

   TRC3(cmPkRgrSiCfgReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR045, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)cfgReqInfo, 
                 sizeof(RgrSiCfgReqInfo));
      RETVALUE(RFAILED);
   }
   if (cmPkRgrSiCfgReqInfo(cfgReqInfo, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR046, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)cfgReqInfo, 
                sizeof(RgrSiCfgReqInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmPkRgrCfgTransId(&transId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR047, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)cfgReqInfo, 
               sizeof(RgrSiCfgReqInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR048, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)cfgReqInfo, 
               sizeof(RgrSiCfgReqInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPutSBuf(pst->region, pst->pool, (Data *)cfgReqInfo, 
               sizeof(RgrSiCfgReqInfo)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR049, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) EVTRGRSICFGREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

/***********************************************************
*
*     Func : cmUnpkRgrSiCfgReq
*
*
*     Desc : SI Configuration Request from RRM to MAC for 
*     configuring SI
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
PUBLIC S16 cmUnpkRgrSiCfgReq
(
RgrSiCfgReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrSiCfgReq(func, pst, mBuf)
RgrSiCfgReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   RgrCfgTransId transId;
   RgrSiCfgReqInfo *cfgReqInfo;
   
   TRC3(cmUnpkRgrSiCfgReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR050, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmUnpkRgrCfgTransId(&transId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR051, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfgReqInfo,
            sizeof(RgrSiCfgReqInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR052, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   cmMemset((U8 *)cfgReqInfo, 0, sizeof(RgrSiCfgReqInfo));
   if (pst->selector == RGR_SEL_LC) 
      if (cmUnpkRgrSiCfgReqInfo(cfgReqInfo, mBuf) != ROK) {
         SPutSBuf(pst->region, pst->pool, (Data *)cfgReqInfo, 
                          sizeof(RgrSiCfgReqInfo));
         SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ERGR053, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
   SPutMsg(mBuf);

   RETVALUE((*func)(pst, spId, transId, cfgReqInfo));
}

/***********************************************************
*
*     Func : cmPkRgrSiCfgReqInfo
*
*
*     Desc : Basic SI configuration/reconfiguration info at RRM
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
PUBLIC S16 cmPkRgrSiCfgReqInfo
(
RgrSiCfgReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrSiCfgReqInfo(param, mBuf)
RgrSiCfgReqInfo *param;
Buffer *mBuf;
#endif
{
  /* ccpu00111328: S16 is renamed as MsgLen */
   MsgLen msgLen;

   TRC3(cmPkRgrSiCfgReqInfo)

   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   CMCHKPK(SPkS32, param->cfgType, mBuf);
   CMCHKPK(SPkU8, param->siId, mBuf);

   if(NULLP != param->pdu)
   {
      if (SFndLenMsg(param->pdu, &msgLen) != ROK)
         RETVALUE(RFAILED);
      if (SCatMsg(mBuf, param->pdu, M1M2) != ROK)
         RETVALUE(RFAILED);
      SPutMsg(param->pdu);
      CMCHKPK(cmPkMsgLen, msgLen, mBuf);
   }
   /*ccpu00140789*/
   else
   {
      CMCHKPK(cmPkMsgLen, 0, mBuf);
   }

   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmUnpkRgrSiCfgReqInfo
*
*
*     Desc : Basic SI configuration/reconfiguration info at RRM
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
PUBLIC S16 cmUnpkRgrSiCfgReqInfo
(
RgrSiCfgReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrSiCfgReqInfo(param, mBuf)
RgrSiCfgReqInfo *param;
Buffer *mBuf;
#endif
{
   MsgLen  msgLen, totalMsgLen;
   /*Merge from Mohit Changes*/
   S32    cfgType;

   TRC3(cmUnpkRgrSiCfgReqInfo)

   SFndLenMsg(mBuf, &msgLen);
   if(msgLen > 0)
   {
      CMCHKUNPK(cmUnpkMsgLen, &msgLen, mBuf);
      /*ccpu00140789*/
      if(msgLen > 0)
      {
         if (SFndLenMsg(mBuf, &totalMsgLen) != ROK)
            RETVALUE(RFAILED);
         if (SSegMsg(mBuf, totalMsgLen-msgLen, &param->pdu) != ROK)
            RETVALUE(RFAILED);
      }
      else
      {
         param->pdu = NULLP;
      }
   }

   CMCHKUNPK(SUnpkU8, &param->siId, mBuf);
   /*CMCHKUNPK(SUnpkS32, (S32 *)&param->cfgType, mBuf);*/
   /*Merge from Mohit Changes*/
   CMCHKUNPK(SUnpkS32,(S32 *)&cfgType, mBuf);
   param->cfgType = (RgrSiCfgType) cfgType;
   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrWarningSiCfgReq
*
*
*     Desc : SI Configuration Request from RRM to MAC for 
*            configuring warning SI
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
PUBLIC S16 cmPkRgrWarningSiCfgReq
(
Pst* pst,
SpId spId,
RgrCfgTransId transId,
RgrWarningSiCfgReqInfo * warningSiCfgReqInfo
)
#else
PUBLIC S16 cmPkRgrWarningSiCfgReq(pst, spId, transId, warningSiCfgReqInfo)
Pst* pst;
SpId spId;
RgrCfgTransId transId;
RgrWarningSiCfgReqInfo * warningSiCfgReqInfo;
#endif
{
   Buffer *mBuf = NULLP;

   TRC3(cmPkRgrWarningSiCfgReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR061, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)warningSiCfgReqInfo, 
                 sizeof(RgrWarningSiCfgReqInfo));
      RETVALUE(RFAILED);
   }

   if (cmPkRgrWarningSiCfgReqInfo(pst, warningSiCfgReqInfo, mBuf) != ROK) 
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR062, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)warningSiCfgReqInfo, 
                sizeof(RgrWarningSiCfgReqInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (cmPkRgrCfgTransId(&transId, mBuf) != ROK) 
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR063, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)warningSiCfgReqInfo, 
               sizeof(RgrWarningSiCfgReqInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (SPkS16(spId, mBuf) != ROK) 
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR064, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)warningSiCfgReqInfo, 
               sizeof(RgrWarningSiCfgReqInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   /* if the application wants to retain this structure, the below 
    * code should be removed */
   if (SPutSBuf(pst->region, pst->pool, (Data *)warningSiCfgReqInfo, 
               sizeof(RgrWarningSiCfgReqInfo)) != ROK) 
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR065, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) EVTRGRWARNINGSICFGREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}/*cmPkRgrWarningSiCfgReq*/


/***********************************************************
*
*     Func : cmUnpkRgrWarningSiCfgReq
*
*
*     Desc : SI Configuration Request from RRM to MAC for  
*            configuring warning SI
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
PUBLIC S16 cmUnpkRgrWarningSiCfgReq
(
RgrWarningSiCfgReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrWarningSiCfgReq(func, pst, mBuf)
RgrWarningSiCfgReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   RgrCfgTransId transId;
   RgrWarningSiCfgReqInfo *warningSiCfgReqInfo;
   
   TRC3(cmUnpkRgrWarningSiCfgReq)

   if (SUnpkS16(&spId, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR066, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   if (cmUnpkRgrCfgTransId(&transId, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR067, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&warningSiCfgReqInfo,
            sizeof(RgrWarningSiCfgReqInfo))) != ROK) 
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR068, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }


   if (pst->selector == RGR_SEL_LC)
   {
      if (cmUnpkRgrWarningSiCfgReqInfo(pst, warningSiCfgReqInfo, mBuf) != ROK) 
      {
         SPutSBuf(pst->region, pst->pool, (Data *)warningSiCfgReqInfo, 
                          sizeof(RgrWarningSiCfgReqInfo));
         SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ERGR069, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
   }
   SPutMsg(mBuf);

   RETVALUE((*func)(pst, spId, transId, warningSiCfgReqInfo));
} /* cmUnpkRgrWarningSiCfgReq */


/***********************************************************
*
*     Func : cmPkRgrWarningSiCfgReqInfo
*
*
*     Desc : Basic warning SI configuration/reconfiguration 
*            info at RRM
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
PUBLIC S16 cmPkRgrWarningSiCfgReqInfo
(
Pst *pst,
RgrWarningSiCfgReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrWarningSiCfgReqInfo(pst, param, mBuf)
Pst *pst;
RgrWarningSiCfgReqInfo *param;
Buffer *mBuf;
#endif
{
   MsgLen   msgLen;
   U32      count;
   CmLList  *node, *prevNode;
   RgrSegmentInfo   *pdu;
 
   TRC3(cmPkRgrWarningSiCfgReqInfo)

   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   CMCHKPK(SPkU8, param->siId, mBuf);

   count = param->siPduLst.count;
   node = param->siPduLst.last;
   while (node) 
   {
      pdu = (RgrSegmentInfo *)node->node;
      prevNode= node->prev;
      if(NULLP != pdu)
      {
         if (SFndLenMsg(pdu->pdu, &msgLen) != ROK)
            RETVALUE(RFAILED);
         if (SCatMsg(mBuf, pdu->pdu, M1M2) != ROK)
            RETVALUE(RFAILED);
         /* The PDU is not Released. This has to be done by 
          * the caller of the packing function  */
         CMCHKPK(cmPkMsgLen, msgLen, mBuf);
         SPutMsg(pdu->pdu);
      }
      cmLListDelFrm(&param->siPduLst, node);
      SPutSBuf(pst->region, pst->pool, (Data *)node, sizeof(RgrSegmentInfo));
      node= prevNode;
   }
   CMCHKPK(SPkU32, count, mBuf);
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmUnpkRgrWarningSiCfgReqInfo
*
*
*     Desc : Unpack warning SI configuration info at SCH 
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
PUBLIC S16 cmUnpkRgrWarningSiCfgReqInfo
(
Pst *pst,
RgrWarningSiCfgReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrWarningSiCfgReqInfo(pst, param, mBuf)
Pst *pst;
RgrWarningSiCfgReqInfo *param;
Buffer *mBuf;
#endif
{
   MsgLen   msgLen, totalMsgLen;
   U32      count, loopCnt;
   Buffer   *pdu;
   CmLList  *node;

   TRC3(cmUnpkRgrWarningSiCfgReqInfo)

   cmLListInit(&param->siPduLst);
   CMCHKUNPK(SUnpkU32, &count, mBuf);
   for (loopCnt=0; loopCnt<count; loopCnt++) 
   {
      if(SFndLenMsg(mBuf, &msgLen) != ROK)
      {
         RETVALUE(RFAILED);
      } 

      if(msgLen > 0)
      { 
         CMCHKUNPK(cmUnpkMsgLen, &msgLen, mBuf);
         if (SFndLenMsg(mBuf, &totalMsgLen) != ROK)
         { 
            RETVALUE(RFAILED);
         }   
         if (SSegMsg(mBuf, totalMsgLen-msgLen, &pdu) != ROK)
         {		 
            RETVALUE(RFAILED);
         }   
      }
      else
      {
         RETVALUE(RFAILED);
      }
      if ((SGetSBuf(pst->region, pst->pool, (Data **)&node,
                  sizeof(CmLList))) != ROK)
         RETVALUE(RFAILED);
      node->node = (PTR)pdu;
      cmLListAdd2Tail(&param->siPduLst, node);
   }

   CMCHKUNPK(SUnpkU8, &param->siId, mBuf);
   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);

   RETVALUE(ROK);
}


/***********************************************************
*
*    Func : cmPkRgrWarningSiStopReq
*
*    Desc : To stop the broadcast for SIB10, SIB11 and SIB12.
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgrWarningSiStopReq
(
Pst           *pst,
SpId          spId,
RgrCfgTransId transId,
U8            siId
)
#else
PUBLIC S16 cmPkRgrWarningSiStopReq(pst,spId, transId, siId)
Pst           *pst;
SpId          spId;
RgrCfgTransId transId;
U8            siId;
#endif
{
   Buffer *mBuf = NULLP;

   TRC3(cmPkRgrWarningSiStopReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR070, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   CMCHKPK(SPkU8, siId, mBuf);

 
   if (cmPkRgrCfgTransId(&transId, mBuf) != ROK) 
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR082, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }


   if (SPkS16(spId, mBuf) != ROK) 
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR071, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) EVTRGRWARNINGSISTOPREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}/*cmPkRgrWarningSiStopReq */


/***********************************************************
*
*    Func : cmUnpkRgrWarningSiStopReq
*
*    Desc : To stop the broadcast for SIB10, SIB11 and SIB12.
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgrWarningSiStopReq
(
RgrWarningSiStopReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrWarningSiStopReq(param, mBuf)
RgrWarningSiStopReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId          spId;
   U8            siId;
   RgrCfgTransId transId;

   TRC3(cmUnpkRgrWarningSiStopReq)

  if (SUnpkS16(&spId, mBuf) != ROK)
  {
     SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
     SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
           __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
           (ErrVal)ERGR072, (ErrVal)0, "Packing failed");
#endif
     RETVALUE(RFAILED);
  }

    if (cmUnpkRgrCfgTransId(&transId, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR083, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
 
   CMCHKUNPK(SUnpkU8, &siId, mBuf);

   SPutMsg(mBuf);

   RETVALUE((*func)(pst, spId, transId, siId));
} /*cmUnpkRgrWarningSiStopReq */


/***********************************************************
*
*     Func : cmPkRgrWarningSiCfgCfm
*
*
*     Desc : Warning SI Configuration Confirm from MAC to RRM
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
PUBLIC S16 cmPkRgrWarningSiCfgCfm
(
Pst* pst,
SuId suId,
RgrCfgTransId transId,
U8 siId,
U8 status
)
#else
PUBLIC S16 cmPkRgrWarningSiCfgCfm(pst, suId, transId, siId, status)
Pst* pst;
SuId suId;
RgrCfgTransId transId;
U8  siId;
U8 status;
#endif
{
   Buffer *mBuf = NULLP;

   TRC3(cmPkRgrWarningSiCfgCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR073, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   if (SPkU8(status, mBuf) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR074, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (SPkU8(siId, mBuf) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR075, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (cmPkRgrCfgTransId(&transId, mBuf) != ROK) 
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR076, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (SPkS16(suId, mBuf) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR077, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) EVTRGRWARNINGSICFGCFM;
   RETVALUE(SPstTsk(pst,mBuf));
} /* cmPkRgrWarningSiCfgCfm */


/***********************************************************
*
*     Func : cmUnpkRgrwarningSiCfgCfm
*
*
*     Desc : Warning SI Configuration Confirm from MAC to RRM
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
PUBLIC S16 cmUnpkRgrWarningSiCfgCfm
(
RgrWarningSiCfgCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrWarningSiCfgCfm(func, pst, mBuf)
RgrWarningSiCfgCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId          suId;
   U8            siId;
   RgrCfgTransId transId;
   U8            status;

   TRC3(cmUnpkRgrWarningSiCfgCfm)

   if (SUnpkS16(&suId, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR078, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   if (cmUnpkRgrCfgTransId(&transId, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR079, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   if (SUnpkU8(&siId, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR080, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   if (SUnpkU8(&status, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR081, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, transId, siId, status));
}/* cmUnpkRgrwarningSiCfgCfm */
#endif/*RGR_SI_SCH*/

/* LTE_ADV_FLAG_REMOVED_START */
/***********************************************************
*
*     Func : cmPkRgrLoadInfReq
*
*
*     Desc : LOAD INF Configuration Request from RRM to MAC for
*            configuring RNTP, ABS etc
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
PUBLIC S16 cmPkRgrLoadInfReq
(
Pst* pst,
SpId spId,
RgrCfgTransId transId,
RgrLoadInfReqInfo * loadInfReq
)
#else
PUBLIC S16 cmPkRgrLoadInfReq(pst, spId, transId, loadInfReq)
Pst* pst;
SpId spId;
RgrCfgTransId transId;
RgrLoadInfReqInfo * loadInfReq;
#endif
{
   Buffer *mBuf = NULLP;

   TRC3(cmPkRgrLoadInfReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR045, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)loadInfReq, 
                 sizeof(RgrLoadInfReqInfo));
      RETVALUE(RFAILED);
   }
   if (cmPkRgrLoadInfReqInfo(loadInfReq, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR046, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)loadInfReq, 
                sizeof(RgrLoadInfReqInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmPkRgrCfgTransId(&transId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR047, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)loadInfReq, 
               sizeof(RgrLoadInfReqInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR048, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)loadInfReq, 
               sizeof(RgrLoadInfReqInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPutSBuf(pst->region, pst->pool, (Data *)loadInfReq, 
               sizeof(RgrLoadInfReqInfo)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR049, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) EVTRGRLOADINFREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

/***********************************************************
*
*     Func : cmUnpkRgrLoadInfReq
*
*
*     Desc : LOAD INF Configuration Request from RRM to MAC for 
*     configuring RNTP, ABS etc
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
PUBLIC S16 cmUnpkRgrLoadInfReq
(
RgrLoadInfReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrLoadInfReq(func, pst, mBuf)
RgrLoadInfReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   RgrCfgTransId transId;
   RgrLoadInfReqInfo *loadInfReq;
   
   TRC3(cmUnpkRgrLoadInfReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR050, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   if (cmUnpkRgrCfgTransId(&transId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR051, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&loadInfReq,
            sizeof(RgrLoadInfReqInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR052, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)loadInfReq, 0, sizeof(RgrLoadInfReqInfo));

   if (pst->selector == RGR_SEL_LC) 
      if (cmUnpkRgrLoadInfReqInfo(loadInfReq, mBuf) != ROK) {
         SPutSBuf(pst->region, pst->pool, (Data *)loadInfReq, 
                          sizeof(RgrLoadInfReqInfo));
         SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ERGR053, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
   SPutMsg(mBuf);

   RETVALUE((*func)(pst, spId, transId, loadInfReq));
}

/***********************************************************
*
*     Func : cmPkRgrLoadInfReqInfo
*
*
*     Desc : Basic LOAD INF configuration/reconfiguration info at RRM
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
PUBLIC S16 cmPkRgrLoadInfReqInfo
(
RgrLoadInfReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrLoadInfReqInfo(param, mBuf)
RgrLoadInfReqInfo *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkRgrLoadInfReqInfo)

   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   CMCHKPK(SPkU8, param->rgrCcPHighStartRb, mBuf);
   CMCHKPK(SPkU8, param->rgrCcPHighEndRb, mBuf);

   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmUnpkRgrLoadInfReqInfo
*
*
*     Desc : Basic LOAD INF configuration/reconfiguration info at RRM
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
PUBLIC S16 cmUnpkRgrLoadInfReqInfo
(
RgrLoadInfReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrLoadInfReqInfo(param, mBuf)
RgrLoadInfReqInfo *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkRgrLoadInfReqInfo)

   CMCHKUNPK(SUnpkU8, &param->rgrCcPHighEndRb, mBuf);
   CMCHKUNPK(SUnpkU8, &param->rgrCcPHighStartRb, mBuf);
   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);

   RETVALUE(ROK);
}
/* LTE_ADV_FLAG_REMOVED_END */

/*rgr_c_001.main_9 ccpu00117452 - MOD - Changed macro name from
   RGR_RRM_DLPWR_CNTRL to RGR_CQI_REPT */
#ifdef RGR_CQI_REPT

/***********************************************************
*
*     Func : cmPkRgrUeCqiReptCfg
*
*
*     Desc : Transaction ID between MAC and RRM
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
PUBLIC S16 cmPkRgrUeCqiReptCfg
(
RgrUeCqiReptCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeCqiReptCfg(param, mBuf)
RgrUeCqiReptCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkRgrUeCqiReptCfg)

   CMCHKPK(SPkU8, param->numColltdCqiRept, mBuf);

   RETVALUE(ROK);
}


/*rgr_c_001.main_9 ADD added changes for CQI management*/
/***********************************************************
*
*     Func : cmUnpkRgrUeCqiReptCfg
*
*
*     Desc : Transaction ID between MAC and RRM
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
PUBLIC S16 cmUnpkRgrUeCqiReptCfg
(
RgrUeCqiReptCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeCqiReptCfg(param, mBuf)
RgrUeCqiReptCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkRgrUeCqiReptCfg)

   CMCHKUNPK(SUnpkU8, &param->numColltdCqiRept, mBuf);

   RETVALUE(ROK);
}


/*rgr_c_001.main_9 ADD added changes for CQI management*/
/***********************************************************
*
*     Func : cmPkRgrStaInd
*
*
*     Desc : Packing Sta Indication sent to RRM
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
PUBLIC S16 cmPkRgrStaInd
(
Pst* pst,
SuId suId,
RgrStaIndInfo* staInd
)
#else
PUBLIC S16 cmPkRgrStaInd(pst, suId, staInd)
Pst* pst;
SuId suId;
RgrStaIndInfo* staInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkRgrStaInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR054, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)staInd, 
               sizeof(RgrStaIndInfo));
      RETVALUE(RFAILED);
   }

   if (cmPkRgrStaIndInfo(staInd, mBuf) != ROK) 
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR055, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)staInd, sizeof(RgrStaIndInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   
   if (SPkS16(suId, mBuf) != ROK) 
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR056, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)staInd, 
                  sizeof(RgrStaIndInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (SPutSBuf(pst->region, pst->pool, (Data *)staInd, 
                  sizeof(RgrStaIndInfo)) != ROK) 
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR057, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) EVTRGRSTAIND;
   RETVALUE(SPstTsk(pst,mBuf));
}

/*rgr_c_001.main_9 ADD added changes for CQI management*/
/***********************************************************
*
*     Func : cmUnpkRgrStaInd
*
*
*     Desc : Unpacking Sta Indication sent to RRM
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgrStaInd
(
RgrStaInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrStaInd(func, pst, mBuf)
RgrStaInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   RgrStaIndInfo *staInd;

   TRC3(cmUnpkRgrStaInd)

   if (SUnpkS16(&suId, mBuf) != ROK)
   {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR058, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&staInd,
                 sizeof(RgrStaIndInfo))) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR059, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }

   if (cmUnpkRgrStaIndInfo(staInd, mBuf) != ROK)
   {
      SPutSBuf(pst->region, pst->pool, (Data *)staInd,
             sizeof(RgrStaIndInfo));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR060, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, staInd));
}

/*rgr_c_001.main_9 ADD added changes for CQI management*/
/***********************************************************
*
*     Func : cmPkRgrStaIndInfo
*
*
*     Desc : Packing of StaIndInfo structure 
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgrStaIndInfo
(
RgrStaIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrStaIndInfo(param, mBuf)
RgrStaIndInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrStaIndInfo)

   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   CMCHKPK(cmPkLteRnti, param->crnti, mBuf);
   CMCHKPK(cmPkRgrUeCqiInfo, &param->ueCqiInfo, mBuf);

   RETVALUE(ROK);
}
/*rgr_c_001.main_9 ADD added changes for CQI management*/
/***********************************************************
*
*     Func : cmUnpkRgrStaIndInfo
*
*
*     Desc : Unpacking of StaIndInfo structure 
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgrStaIndInfo
(
RgrStaIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrStaIndInfo(param, mBuf)
RgrStaIndInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrStaIndInfo)

   CMCHKUNPK(cmUnpkRgrUeCqiInfo, &param->ueCqiInfo, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &param->crnti, mBuf);
   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);

   RETVALUE(ROK);
}
/*rgr_c_001.main_9 ADD added changes for CQI management*/
/***********************************************************
*
*     Func : cmPkRgrUeCqiInfo
*
*
*     Desc : Packing of StaIndInfo structure 
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgrUeCqiInfo
(
RgrUeCqiInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeCqiInfo(param, mBuf)
RgrUeCqiInfo *param;
Buffer *mBuf;
#endif
{

   S16 idx;
   TRC3(cmPkRgrUeCqiInfo)

   for (idx = param->numCqiRept - 1; idx >= 0; idx--)
   {
      CMCHKPK(cmPkRgrUeCqiRept, &param->cqiRept[idx], mBuf);
   }
   CMCHKPK(SPkU8, param->numCqiRept, mBuf);

   RETVALUE(ROK);
} /* cmPkRgrUeCqiInfo */

/*rgr_c_001.main_9 ADD added changes for CQI management*/
/***********************************************************
*
*     Func : cmUnpkRgrUeCqiInfo
*
*
*     Desc : Packing of StaIndInfo structure 
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgrUeCqiInfo
(
RgrUeCqiInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeCqiInfo(param, mBuf)
RgrUeCqiInfo *param;
Buffer *mBuf;
#endif
{

   U8  idx;
   TRC3(cmUnpkRgrUeCqiInfo)

   CMCHKUNPK(SUnpkU8, &param->numCqiRept, mBuf);
   for (idx = 0; idx < param->numCqiRept; idx++)
   {
      CMCHKUNPK(cmUnpkRgrUeCqiRept, &param->cqiRept[idx], mBuf);
   }

   RETVALUE(ROK);
} /* cmUnpkRgrUeCqiInfo */

/***********************************************************
*
*     Func : cmPkRgrSubBandCqiInfo 
*
*
*     Desc : Packing ofcmPkRgrSubBandCqiInfo structure 
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgrSubBandCqiInfo 
(
RgrSubBandCqiInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrSubBandCqiInfo(param, mBuf)
RgrSubBandCqiInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrSubBandCqiInfo)

   CMCHKPK(SPkU8, param->cqi[0], mBuf);
   CMCHKPK(SPkU8, param->cqi[1], mBuf);
   CMCHKPK(SPkU8, param->subBandIdx, mBuf);

   RETVALUE(ROK);
} /* cmPkRgrSubBandCqiInfo */

/*rgr_c_001.main_9 ADD added changes for CQI management*/
/***********************************************************
*
*     Func : cmPkRgrUeCqiRept
*
*
*     Desc : Packing of StaIndInfo structure 
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgrUeCqiRept
(
RgrUeCqiRept *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeCqiRept(param, mBuf)
RgrUeCqiRept *param;
Buffer *mBuf;
#endif
{
   S8 idx;
   U8 count;

   TRC3(cmPkRgrUeCqiRept)

   CMCHKPK(SPkU8, param->cqi[0], mBuf);
   CMCHKPK(SPkU8, param->cqi[1], mBuf);
   CMCHKPK(SPkU8, param->cqiMode, mBuf);
   for (idx = param->numSubBand - 1; idx >= 0; idx--)
   {
      count = idx;
      CMCHKPK(cmPkRgrSubBandCqiInfo, &param->sbCqiInfo[count], mBuf);
   }
   CMCHKPK(SPkU8, param->numSubBand, mBuf);
   RETVALUE(ROK);
} /* cmPkRgrUeCqiRept */

/***********************************************************
*
*     Func :cmUnpkRgrSubBandCqiInfo 
*
*
*     Desc : Packing of cmUnpkRgrSubBandCqiInfo structure 
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgrSubBandCqiInfo 
(
RgrSubBandCqiInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrSubBandCqiInfo(param, mBuf)
RgrSubBandCqiInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrSubBandCqiInfo)

   CMCHKUNPK(SUnpkU8, &param->subBandIdx, mBuf);
   CMCHKUNPK(SUnpkU8, &param->cqi[1], mBuf);
   CMCHKUNPK(SUnpkU8, &param->cqi[0], mBuf);

   RETVALUE(ROK);
} /* cmUnpkRgrSubBandCqiInfo*/

/*rgr_c_001.main_9 ADD added changes for CQI management*/
/***********************************************************
*
*     Func : cmUnpkRgrUeCqiRept
*
*
*     Desc : Packing of StaIndInfo structure 
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgrUeCqiRept
(
RgrUeCqiRept *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeCqiRept(param, mBuf)
RgrUeCqiRept *param;
Buffer *mBuf;
#endif
{
   U8 idx;

   TRC3(cmUnpkRgrUeCqiRept)
   CMCHKUNPK(SUnpkU8, &param->numSubBand, mBuf);
   for (idx = 0; idx < param->numSubBand; idx++)
   {
      CMCHKUNPK(cmUnpkRgrSubBandCqiInfo, &param->sbCqiInfo[idx], mBuf);
   }
   CMCHKUNPK(SUnpkU8, &param->cqiMode, mBuf);
   CMCHKUNPK(SUnpkU8, &param->cqi[1], mBuf);
   CMCHKUNPK(SUnpkU8, &param->cqi[0], mBuf);

   RETVALUE(ROK);
} /* cmUnpkRgrUeCqiRept */
#endif /* End of ifdef RGR_CQI_REPT */

/* LTE_ADV_FLAG_REMOVED_START */
/***********************************************************
*
*     Func : cmPkRgrLoadInfInd
*
*
*     Desc : Packing LOAD INFORMATION Indication sent to RRM
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
PUBLIC S16 cmPkRgrLoadInfInd
(
Pst* pst,
SuId suId,
RgrLoadInfIndInfo* loadInfInd
)
#else
PUBLIC S16 cmPkRgrLoadInfInd(pst, suId, loadInfInd)
Pst* pst;
SuId suId;
RgrLoadInfIndInfo* loadInfInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkRgrLoadInfInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR054, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)loadInfInd,
            sizeof(RgrLoadInfIndInfo));
      RETVALUE(RFAILED);
   }

   if (cmPkRgrLoadInfIndInfo(loadInfInd, mBuf) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR055, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)loadInfInd,
            sizeof(RgrLoadInfIndInfo));
      SPutMsg(mBuf);

      RETVALUE(RFAILED);
   }

   if (SPkS16(suId, mBuf) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR056, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)loadInfInd,
            sizeof(RgrLoadInfIndInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (SPutSBuf(pst->region, pst->pool, (Data *)loadInfInd,
                  sizeof(RgrLoadInfIndInfo)) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR057, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) EVTRGRLOADINFIND;
   RETVALUE(SPstTsk(pst,mBuf));
}

/***********************************************************
*
*     Func : cmUnpkRgrLoadInfInd
*
*
*     Desc : Unpacking LOAD INFORMATION Indication sent to RRM
*
*     Ret  : S16
*
*     Notes:
*
*     File  :
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgrLoadInfInd
(
RgrLoadInfInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrLoadInfInd(func, pst, mBuf)
RgrLoadInfInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   RgrLoadInfIndInfo *loadInfInd = NULLP; /* dsfr_pal_fixes ** 21-March-2013 ** SKS */

   TRC3(cmUnpkRgrLoadInfInd)

   if (SUnpkS16(&suId, mBuf) != ROK)
   {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR058, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&loadInfInd,
                 sizeof(RgrLoadInfIndInfo))) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR059, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }

   /* dsfr_pal_fixes ** 22-March-2013 ** SKS */
   if (cmUnpkRgrLoadInfIndInfo(loadInfInd, pst, mBuf) != ROK)
   {
      SPutSBuf(pst->region, pst->pool, (Data *)loadInfInd,
             sizeof(RgrLoadInfIndInfo));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR060, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, loadInfInd));
}


/***********************************************************
*
*     Func : cmPkRgrLoadInfIndInfo
*
*
*     Desc : Packing of LoadInfIndInfo structure
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgrLoadInfIndInfo
(
RgrLoadInfIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrLoadInfIndInfo(param, mBuf)
RgrLoadInfIndInfo *param;
Buffer *mBuf;
#endif
{
   U8                     idx;
   TRC3(cmPkRgrLoadInfIndInfo)

   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   CMCHKPK(SPkU16, param->bw, mBuf);
   if(RGR_ABS == param->type)
   {
      for(idx = 0; idx < RGR_ABS_PATTERN_LEN; idx++)
      {
         CMCHKPK(SPkU32, param->u.absLoadInfo[idx], mBuf);
      }
   }
   else
   {
      CMCHKPK(cmPkTknStrOSXL, &param->u.rntpInfo, mBuf);
   }

   CMCHKPK(SPkU32, param->type, mBuf);

   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmUnpkRgrLoadInfIndInfo
*
*
*     Desc : Unpacking of LoadInfIndInfo structure
*
*     Ret  : S16
*
*     Notes:
*
*     File  :
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgrLoadInfIndInfo
(
RgrLoadInfIndInfo *param,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrLoadInfIndInfo(param, pst, mBuf)
RgrLoadInfIndInfo *param;
Pst *pst;
Buffer *mBuf;
#endif
{
   S8          idx;
   Ptr         ptr;

   /* dsfr_pal_fixes ** 21-March-2013 ** SKS */
   TknStrOSXL  *tknStr;
   U16         ndx;

   TRC3(cmUnpkRgrLoadInfIndInfo)

   CMCHKUNPK(SUnpkU32, &param->type, mBuf);
   if(RGR_ABS == param->type)
   {
      for(idx = RGR_ABS_PATTERN_LEN -1 ; idx >= 0; idx--)
      {
         CMCHKUNPK(SUnpkU32, &param->u.absLoadInfo[(U8)idx], mBuf);
      }
   }
   else
   {
      ptr =(Ptr)param;

      /* dsfr_pal_fixes ** 21-March-2013 ** SKS ** Start */
      tknStr = &param->u.rntpInfo;

      CMCHKUNPK(SUnpkU8, &tknStr->pres, mBuf);

      if(tknStr->pres)
      {
         /* Length */
         CMCHKUNPK(SUnpkU16, &tknStr->len, mBuf);

         if ((SGetSBuf(pst->region, pst->pool, (Data **)&tknStr->val,tknStr->len)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ERGR052, (ErrVal)0, "Packing failed");
#endif
            SPutMsg(mBuf);
            RETVALUE(RFAILED);
         }

         /* Value */
         for (ndx = 1; ndx <= tknStr->len; ndx++)
         {
            CMCHKUNPK(SUnpkU8, &tknStr->val[tknStr->len - ndx], mBuf);
         }
      }
   }
   /* dsfr_pal_fixes ** 21-March-2013 ** SKS ** End */

   /* dsfr_pal_fixes ** 22-March-2013 ** SKS */
   CMCHKUNPK(SUnpkU16, &param->bw, mBuf);

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);

   RETVALUE(ROK);
}
/* LTE_ADV_FLAG_REMOVED_END */

#ifdef TFU_UPGRADE 
/*rgr_c_001.main_9 ADD added changes for CQI management*/
/***********************************************************
*
*     Func : cmPkRgrUepACfg
*
*
*     Desc : Transaction ID between MAC and RRM
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
PUBLIC S16 cmPkRgrUepACfg
(
RgrUepACfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUepACfg(param, mBuf)
RgrUepACfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkRgrUepACfg)

   if(param->pAPrsnt)
   {
      CMCHKPK(SPkU32, param->pA, mBuf);
   }
   CMCHKPK(SPkU8, param->pAPrsnt, mBuf);

   RETVALUE(ROK);
}


/*rgr_c_001.main_9 ADD added changes for CQI management*/
/***********************************************************
*
*     Func : cmUnpkRgrUepACfg
*
*
*     Desc : Transaction ID between MAC and RRM
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
PUBLIC S16 cmUnpkRgrUepACfg
(
RgrUepACfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUepACfg(param, mBuf)
RgrUepACfg *param;
Buffer *mBuf;
#endif
{
   U32 tmpEnum;
   TRC3(cmUnpkRgrUepACfg)

   CMCHKUNPK(SUnpkU8, (U8 *)&param->pAPrsnt, mBuf);
   if (param->pAPrsnt)
   {
      CMCHKUNPK(SUnpkU32, (U32*)&tmpEnum, mBuf);
      param->pA = (RgrUeDlPwrCntrlPaCfg) tmpEnum;
   }

   RETVALUE(ROK);
}

/*rgr_c_001.main_9 ADD PDSCH ded cfg*/
/***********************************************************
*
*     Func : cmPkRgrUePdschDedCfg
*
*
*     Desc : Transaction ID between MAC and RRM
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
PUBLIC S16 cmPkRgrUePdschDedCfg
(
RgrUePdschDedCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUePdschDedCfg(param, mBuf)
RgrUePdschDedCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkRgrUePdschDedCfg)

   CMCHKPK(cmPkRgrUepACfg, &param->uepACfg, mBuf);

   RETVALUE(ROK);
}


/*rgr_c_001.main_9 ADD PDSCH ded cfg*/
/***********************************************************
*
*     Func : cmUnpkRgrUePdschDedCfg
*
*
*     Desc : Transaction ID between MAC and RRM
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
PUBLIC S16 cmUnpkRgrUePdschDedCfg
(
RgrUePdschDedCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUePdschDedCfg(param, mBuf)
RgrUePdschDedCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkRgrUePdschDedCfg)

   CMCHKUNPK(cmUnpkRgrUepACfg, &param->uepACfg, mBuf);

   RETVALUE(ROK);
}
#endif


#ifdef LTE_ADV 

/***********************************************************
*
*     Func : cmPkRgrUeUlPwrDedSCellCfg
*
*
*     Desc : DL Secondary Cell UL PC Info
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
PRIVATE S16 cmPkRgrUeUlPwrDedSCellCfg
(
RgrUeUlPwrDedSCellCfg *param,
Buffer *mBuf
)
#else
PRIVATE S16 cmPkRgrUeUlPwrDedSCellCfg(param, mBuf)
RgrUeUlPwrDedSCellCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkRgrUeUlPwrDedSCellCfg)
   CMCHKPK(SPkU8, param->pSRSOffset, mBuf);
   CMCHKPK(SPkS8, param->p0UePusch, mBuf);
   CMCHKPK(SPkU8, param->isDeltaMCSEnabled, mBuf);
   CMCHKPK(SPkU8, param->isAccumulated, mBuf);

   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmUnpkRgrUeUlPwrDedSCellCfg
*
*
*     Desc : Uplink power configuration per UE
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
PRIVATE S16 cmUnpkRgrUeUlPwrDedSCellCfg
(
RgrUeUlPwrDedSCellCfg *param,
Buffer *mBuf
)
#else
PRIVATE S16 cmUnpkRgrUeUlPwrDedSCellCfg(param, mBuf)
RgrUeUlPwrDedSCellCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrUeUlPwrDedSCellCfg)

   CMCHKUNPK(SUnpkU8, &param->isAccumulated, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isDeltaMCSEnabled, mBuf);
   CMCHKUNPK(SUnpkS8, &param->p0UePusch, mBuf);
   CMCHKUNPK(SUnpkU8, &param->pSRSOffset, mBuf);
   RETVALUE(ROK);
}




/***********************************************************
*
*     Func : cmPkRgrUeSecCellCfg
*
*
*     Desc : DL Secondary Cell information of the UE
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
PRIVATE S16 cmPkRgrUeSecCellCfg
(
RgrUeSecCellCfg *param,
Buffer *mBuf
)
#else
PRIVATE S16 cmPkRgrUeSecCellCfg(param, mBuf)
RgrUeSecCellCfg *param;
Buffer *mBuf;
#endif
{
   CMCHKPK(cmPkRgrUeUlPwrDedSCellCfg,&param->ueSCellUlDedPwrCfg, mBuf);
   CMCHKPK(SPkU8, param->isUlCaEnabled, mBuf);
   CMCHKPK(cmPkRgrUeTxModeCfg, &param->txMode, mBuf);
#ifdef TFU_UPGRADE
/*rgr_c_001.main_9 ADD PDSCH ded cfg*/
   CMCHKPK(cmPkRgrUePdschDedCfg, &param->uePdschDedCfg, mBuf);
#endif
   CMCHKPK(cmPkRgrUeDlCqiCfg,&param->ueSCellDlCqiCfg, mBuf);
   CMCHKPK(cmPkTknU32, &param->sCellDeActTmr, mBuf);
   CMCHKPK(SPkU16, param->sCellId, mBuf);
   CMCHKPK(SPkU8, param->sCellIdx, mBuf);

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgrUeSecCellInfo
*
*
*     Desc : Secondary Cell information of the UE
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
PUBLIC S16 cmPkRgrUeSecCellInfo
(
RgrUeSecCellInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeSecCellInfo(param, mBuf)
RgrUeSecCellInfo *param;
Buffer *mBuf;
#endif
{
   S8 idx;
   for(idx = param->numSCells - 1; idx >= 0; idx--)
   {
      CMCHKPK(cmPkRgrUeSecCellCfg, &param->ueSCellDedCfg[(U8)idx],mBuf);
   }

   CMCHKPK(SPkU8, param->numSCells, mBuf);

   CMCHKPK(SPkU8, param->useExtBSRSizes, mBuf);

   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmUnpkRgrUeSecCellCfg
*
*
*     Desc : DL Secondary Cell information of the UE
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
PRIVATE S16 cmUnpkRgrUeSecCellCfg
(
RgrUeSecCellCfg *param,
Buffer *mBuf
)
#else
PRIVATE S16 cmUnpkRgrUeSecCellCfg(param, mBuf)
RgrUeSecCellCfg *param;
Buffer *mBuf;
#endif
{
   CMCHKUNPK(SUnpkU8, &param->sCellIdx, mBuf);
   CMCHKUNPK(SUnpkU16, &param->sCellId, mBuf);
   CMCHKUNPK(cmUnpkTknU32, &param->sCellDeActTmr, mBuf);
   CMCHKUNPK(cmUnpkRgrUeDlCqiCfg, &param->ueSCellDlCqiCfg, mBuf);
#ifdef TFU_UPGRADE
   CMCHKUNPK(cmUnpkRgrUePdschDedCfg, &param->uePdschDedCfg, mBuf);
#endif
   CMCHKUNPK(cmUnpkRgrUeTxModeCfg, &param->txMode, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isUlCaEnabled, mBuf);
   CMCHKUNPK(cmUnpkRgrUeUlPwrDedSCellCfg, &param->ueSCellUlDedPwrCfg, mBuf);

   RETVALUE(ROK);
}




/***********************************************************
*
*     Func : cmUnpkRgrUeSecCellInfo
*
*
*     Desc : Secondary Cell information of the UE
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
PUBLIC S16 cmUnpkRgrUeSecCellInfo
(
RgrUeSecCellInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeSecCellInfo(param, mBuf)
RgrUeSecCellInfo *param;
Buffer *mBuf;
#endif
{
   U8 idx;

   CMCHKUNPK(SUnpkU8, &param->useExtBSRSizes, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numSCells, mBuf);

   for(idx = 0; idx < param->numSCells;idx++)
   {
      CMCHKUNPK(cmUnpkRgrUeSecCellCfg, &param->ueSCellDedCfg[idx],mBuf);
   }

   RETVALUE(ROK);
}
/* Sprint 3 */
/***********************************************************
*
*     Func : cmPkRgrUeSCellAckPucchCfg
*
*
*     Desc : PUCCH Configuration information of the UE
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
PUBLIC S16 cmPkRgrUeSCellAckPucchCfg
(
RgrUeSCellAckPucchCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeSCellAckPucchCfg(param, mBuf)
RgrUeSCellAckPucchCfg *param;
Buffer *mBuf;
#endif
{
   S8 idx;
   TRC3(cmPkRgrUeSCellAckPucchCfg);

   for(idx = param->sCellAckN1ResTb2Count - 1; idx >=0 ;idx--)
   {
      CMCHKPK(SPkU16, param->sCellAckN1ResTb2[(U8)idx], mBuf);
   }

   CMCHKPK(SPkU8, param->sCellAckN1ResTb2Count, mBuf);

   for(idx = param->sCellAckN1ResTb1Count - 1; idx >=0 ;idx--)
   {
      CMCHKPK(SPkU16, param->sCellAckN1ResTb1[(U8)idx], mBuf);
   }

   CMCHKPK(SPkU8, param->sCellAckN1ResTb1Count, mBuf);
   CMCHKPK(SPkU32, param->pucchFormatType, mBuf);

   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmUnpkRgrUeSCellAckPucchCfg
*
*
*     Desc : PUCCH Configuration information of the UE
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
PUBLIC S16 cmUnpkRgrUeSCellAckPucchCfg
(
RgrUeSCellAckPucchCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeSCellAckPucchCfg(param, mBuf)
RgrUeSCellAckPucchCfg *param;
Buffer *mBuf;
#endif
{
   U8 idx;

   TRC3(cmUnpkRgrUeSCellAckPucchCfg);

   CMCHKUNPK(SUnpkU32, (U32*)&param->pucchFormatType, mBuf);

   CMCHKUNPK(SUnpkU8, &param->sCellAckN1ResTb1Count, mBuf);

   for(idx = 0; idx < param->sCellAckN1ResTb1Count; idx++)
   {
      CMCHKUNPK(SUnpkU16, &param->sCellAckN1ResTb1[idx], mBuf);
   }

   CMCHKUNPK(SUnpkU8, &param->sCellAckN1ResTb2Count, mBuf);

   for(idx = 0; idx < param->sCellAckN1ResTb2Count; idx++)
   {
      CMCHKUNPK(SUnpkU16, &param->sCellAckN1ResTb2[idx], mBuf);
   }

   RETVALUE(ROK);
}




#endif


/***********************************************************
*
*     Func : cmPkRgrUeStaInd
*
*
*     Desc : Packing Ue Sta Indication sent to RRM
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
PUBLIC S16 cmPkRgrUeStaInd
(
Pst* pst,
SuId suId,
RgrUeStaIndInfo* ueStaInd
)
#else
PUBLIC S16 cmPkRgrUeStaInd(pst, suId, ueStaInd)
Pst* pst;
SuId suId;
RgrUeStaIndInfo* ueStaInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkRgrUeStaInd)
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR054, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)ueStaInd, 
               sizeof(RgrUeStaIndInfo));
      RETVALUE(RFAILED);
   }

   if (cmPkRgrUeStaIndInfo(ueStaInd, mBuf) != ROK) 
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR055, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)ueStaInd, 
               sizeof(RgrUeStaIndInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   
   if (SPkS16(suId, mBuf) != ROK) 
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR056, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)ueStaInd, 
                  sizeof(RgrUeStaIndInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (SPutSBuf(pst->region, pst->pool, (Data *)ueStaInd, 
                  sizeof(RgrUeStaIndInfo)) != ROK) 
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR057, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) EVTRGRUESTAIND;
   RETVALUE(SPstTsk(pst,mBuf));
}

/*rgr_c_001.main_9 ADD added changes for CQI management*/
/***********************************************************
*
*     Func : cmUnpkRgrUeStaInd
*
*
*     Desc : Unpacking Sta Indication sent to RRM
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgrUeStaInd
(
RgrUeStaInd  func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeStaInd(func, pst, mBuf)
RgrUeStaInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   RgrUeStaIndInfo *ueStaInd;

   TRC3(cmUnpkRgrUeStaInd)

   if (SUnpkS16(&suId, mBuf) != ROK)
   {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR058, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&ueStaInd,
                 sizeof(RgrUeStaIndInfo))) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGR059, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }

   if (cmUnpkRgrUeStaIndInfo(ueStaInd, mBuf) != ROK)
   {
      SPutSBuf(pst->region, pst->pool, (Data *)ueStaInd,
             sizeof(RgrUeStaIndInfo));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGR060, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, ueStaInd));
}

/***********************************************************
*
*     Func : cmPkRgrUeStaIndInfo
*
*
*     Desc : Packing of UeStaIndInfo structure 
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgrUeStaIndInfo
(
RgrUeStaIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrUeStaIndInfo(param, mBuf)
RgrUeStaIndInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrUeStaIndInfo)

   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   CMCHKPK(cmPkLteRnti, param->crnti, mBuf);
   CMCHKPK(SPkU8, param->status, mBuf);

   RETVALUE(ROK);
}
/***********************************************************
*
*     Func : cmUnpkRgrUeStaIndInfo
*
*
*     Desc : Unpacking of UeStaIndInfo structure 
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgrUeStaIndInfo
(
RgrUeStaIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrUeStaIndInfo(param, mBuf)
RgrUeStaIndInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrUeStaIndInfo)

   CMCHKUNPK(SUnpkU8, &param->status, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &param->crnti, mBuf);
   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);

   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkRgrCellCsgParamCfg 
*
*
*     Desc : CSG Parameter configuration
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
PUBLIC S16 cmPkRgrCellCsgParamCfg 
(
RgrCellCsgParamCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrCellCsgParamCfg(param, mBuf)
RgrCellCsgParamCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgrCellCsgParamCfg)

   CMCHKPK(SPkU8, param->minUlResNonCsg, mBuf);
   CMCHKPK(SPkU8, param->minDlResNonCsg, mBuf);

   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmUnpkRgrCellCsgParamCfg
*
*
*     Desc : Unpacking of RgrCellCsgParamCfg structure 
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgrCellCsgParamCfg
(
RgrCellCsgParamCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrCellCsgParamCfg(param, mBuf)
RgrCellCsgParamCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgrCellCsgParamCfg)

   CMCHKUNPK(SUnpkU8, &param->minDlResNonCsg, mBuf);
   CMCHKUNPK(SUnpkU8, &param->minUlResNonCsg, mBuf);

   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmPkRgrCellCntrlCmdCfg
*
*
*     Desc : Packing of RgrCellCntrlCmdCfg structure 
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgrCellCntrlCmdCfg
(
RgrCellCntrlCmdCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgrCellCntrlCmdCfg(param, mBuf)
RgrCellCntrlCmdCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkRgrCellCntrlCmdCfg)

   switch(param->cmdType)
   {
      case RGR_CNTRL_CMD_RACH_OVRLD:
         CMCHKUNPK(SPkU8, param->cmdDesc.rachOvrLd.backOffVal, mBuf);
         CMCHKUNPK(SPkU8, param->cmdDesc.rachOvrLd.backOffEnb, mBuf);
         break;
      case RGR_CNTRL_CMD_CPU_OVRLD:
         CMCHKUNPK(SPkU8, param->cmdDesc.cpuOvrLd.instruction, mBuf);
         break;
      default:
         break;
   }
   CMCHKUNPK(SPkU32, param->cmdType, mBuf);

   RETVALUE(ROK);
}
/***********************************************************
*
*     Func : cmUnpkRgrCellCntrlCmdCfg
*
*
*     Desc : Unpacking of RgrCellCntrlCmdCfg structure 
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgrCellCntrlCmdCfg
(
RgrCellCntrlCmdCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgrCellCntrlCmdCfg(param, mBuf)
RgrCellCntrlCmdCfg *param;
Buffer *mBuf;
#endif
{
   U32 tmpEnum;

   TRC3(cmUnpkRgrCellCntrlCmdCfg)

   CMCHKUNPK(SUnpkU32, &tmpEnum, mBuf);
   param->cmdType = (RgrCellCntrlCmdType) tmpEnum;
   switch(param->cmdType)
   {
      case RGR_CNTRL_CMD_RACH_OVRLD:
         CMCHKUNPK(SUnpkU8, &param->cmdDesc.rachOvrLd.backOffEnb, mBuf);
         CMCHKUNPK(SUnpkU8, &param->cmdDesc.rachOvrLd.backOffVal, mBuf);
         break;
      case RGR_CNTRL_CMD_CPU_OVRLD:
         CMCHKUNPK(SUnpkU8, &param->cmdDesc.cpuOvrLd.instruction, mBuf);
         break;
      default:
         break;
   }

   RETVALUE(ROK);
}
#endif /* End of if defined(LCRGR) */
/**********************************************************************

        End of file:     rgr.c@@/main/10 - Wed Jul 27 13:52:30 2011
 
**********************************************************************/
 
/**********************************************************************
 
        Notes:
 
**********************************************************************/
 
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat      init                  description
------------ -------- ---- ----------------------------------------------
/main/1        ---       sm            1. Initial Release.
      rgr_c_001.main_1   sm            1. Removing unwanted srMcs 
                                          Cfg pk/unpk from cellReCfg.
/main/3      ---                   sm     1.LTE MAC 2.1 release
/main/4      ---  rgr_c_001.main_3 sm     1.Added TTI indication from MAC to RGR user.
/main/5       ---  rgr_c_001.main_4        1.Modified for SI Enhancement.
/main/7      ---      rgr_c_001.main_5 sd 1.ccpu00112398: Added 
                                           2.ccpu00111328: S16 is renamed as MsgLen

                                            periodicBSR-timer and retxBSR-timer
                                           3.cccpu00112372: Added contention
                                            resolution timer.
                                           4.ccpu00112789: Added configuration
                                            for maximum number of  MSG3s.
/main/7      ---      rgr_c_001.main_6   ap   1. Added support for MIMO
/main/8      ---      rgr_c_001.main_7  rsharon   1. Added support for SPS
/main/9               rgr_c_001.main_8   dv   Added changes of TFU_UPGRADE. 
/main/10     ---      rgr_c_001.main_9   gvj  1. Updated for LTE MAC Rel 3.1
*********************************************************************91*/
