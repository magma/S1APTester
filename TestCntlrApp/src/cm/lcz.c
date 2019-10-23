
/********************************************************************20**

     Name:     LTE-X2AP Layer  
  
     Type:     C source file
  
     Desc:     C Source code for common packing and unpacking functions
               for Trillium X2AP Layer Manager Interfaces

     File:     lcz.c

     Sid:      lcz.c@@/main/4 - Wed Feb 22 12:57:55 2012

     Prg:      sy 

*********************************************************************21*/
/* cz001.301 : Removed LTE_HO_SUPPORT flag to avoid compilation error,
 * if we undefine the flag. */

/* header include files -- defines (.h) */
#include "envopt.h"        /* Environment options             */
#include "envdep.h"        /* Environment dependent options   */
#include "envind.h"        /* Environment independent options */
#include "gen.h"           /* General layer                   */
#include "ssi.h"           /* System service interface        */
#include "cm5.h"           /* Common timer library            */
#include "cm_llist.h"      /* Common linked list library      */
#include "cm_hash.h"       /* Common hash library             */
#include "cm_tpt.h"        /* Common transport library        */
#include "cm_tkns.h"       /* Common tokens                   */
#include "cm_mblk.h"       /* Common memory allocation        */
#include "cm_inet.h"       /* Common socket library           */
#include "cm_pasn.h"       /* Common Asn.1 library           */
#include "sct.h"           /* SCT interface defines           */
#include "czt.h"           /* CZT interface defines           */
#include "lcz.h"           /* X2AP Layer management           */
#include "cz.h"            /* X2AP layer defines              */
#include "cz_err.h"        /* X2AP - error */

/* header/extern include files (.x) */
#include "gen.x"           /* General layer                   */
#include "ssi.x"           /* System services interface       */
#include "cm5.x"           /* Common timer module             */
#include "cm_lib.x"        /* Common linrary function         */
#include "cm_llist.x"      /* Common link list library        */
#include "cm_hash.x"       /* Common hash list library        */
#include "cm_tkns.x"       /* Common tokens                   */
#include "cm_tpt.x"        /* Common transport library        */
#include "cm_mblk.x"       /* Common memory allocation        */
#include "cm_inet.x"       /* Common socket library           */
#include "cm_pasn.x"       /* Common Asn.1 library           */
#include "sct.x"           /* SCT interface defines           */
#include "czt.x"           /* CZT interface structures        */
#include "lcz.x"           /* X2AP Layer management           */
#include "cz.x"            /* X2AP layer structures           */

/* local function definition */

/* functions in other modules */

/* public variable declarations */

/* control variables for testing */

/* private variable declarations */

/*
 * support functions
 */
#ifdef __cplusplus
EXTERN "C" {
#endif /* __cplusplus */

/* lcz_c_001.main_1 : CR Fixes */

#if (defined(LCLCZ) || defined(LWLCLCZ))


/***********************************************************
*
*     Func : cmPkLczCfgReq
*
*
*     Desc : czPkLczCfgReq
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/

#ifdef ANSI
PUBLIC S16 cmPkLczCfgReq
(
Pst * pst,
CzMngmt * cfg
)
#else /* ANSI */
PUBLIC S16 cmPkLczCfgReq(pst, cfg)
Pst * pst;
CzMngmt * cfg;
#endif /* ANSI */
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLczCfgReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELCZ001, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */

      RETVALUE(RFAILED);
   }
   if (pst->selector == LCZ_SEL_LC) {
      /* cz001.301 : Added one more input varaible PST structure
       * to the function cmPkCzMngmt */
      if (cmPkCzMngmt(cfg, EVTLCZCFGREQ, mBuf, pst) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELCZ002, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutSBuf(pst->region, pst->pool, (Data *)cfg, sizeof(CzMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == LCZ_SEL_LWLC) {
      if (cmPkPtr((PTR)cfg, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELCZ003, (ErrVal)0, (S8*)"Packing failed");
#endif /*(ERRCLASS & ERRCLS_ADD_RES) */
         SPutSBuf(pst->region, pst->pool, (Data *)cfg, sizeof(CzMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
    /* cz001.301: Purify Fix */
   if (pst->selector != LCZ_SEL_LWLC) {
      if (SPutSBuf(pst->region, pst->pool,(Data *)cfg, sizeof(CzMngmt)) != ROK){
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELCZ004, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   pst->event = (Event) EVTLCZCFGREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkLczCfgReq
*
*
*     Desc : czUnpkLczCfgReq
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/

#ifdef ANSI
PUBLIC S16 cmUnpkLczCfgReq
(
LczCfgReq func,
Pst *pst,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkLczCfgReq(func, pst, mBuf)
LczCfgReq func;
Pst *pst;
Buffer *mBuf;
#endif /* ANSI */
{
   CzMngmt *cfg;
   
   TRC3(cmUnpkLczCfgReq)

   if (pst->selector != LCZ_SEL_LWLC) {
     if ((SGetSBuf(pst->region,pst->pool,(Data **)&cfg,sizeof(CzMngmt))) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELCZ005, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
         cmMemset((U8 *)cfg, (U8 )0, (sizeof(CzMngmt)));
   }
   if (pst->selector == LCZ_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&cfg, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == LCZ_SEL_LC) /*lcz_c_001.main_3: Passed pst in czUnpkCzMngmt*/ 
      if (cmUnpkCzMngmt(cfg, EVTLCZCFGREQ,mBuf,pst) != ROK) { 
      SPutSBuf(pst->region, pst->pool, (Data *)cfg, sizeof(CzMngmt));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELCZ006, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cfg));
}


/***********************************************************
*
*     Func : cmPkLczCfgCfm
*
*
*     Desc : cmPkLczCfgCfm
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkLczCfgCfm
(
Pst * pst,
CzMngmt * cfm
)
#else /* ANSI */
PUBLIC S16 cmPkLczCfgCfm(pst, cfm)
Pst * pst;
CzMngmt * cfm;
#endif /* ANSI */
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLczCfgCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELCZ007, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */
      RETVALUE(RFAILED);
   }
   if (pst->selector == LCZ_SEL_LC) {
      /* cz001.301 : Added one more input varaible PST structure
       * to the function cmPkCzMngmt */
      if (cmPkCzMngmt(cfm, EVTLCZCFGCFM, mBuf, pst) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELCZ008, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */
         SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(CzMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == LCZ_SEL_LWLC) {
      if (cmPkPtr((PTR)cfm, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELCZ009, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */
         SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(CzMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector != LCZ_SEL_LWLC) {
      if (SPutSBuf(pst->region, pst->pool,(Data *)cfm,sizeof(CzMngmt)) != ROK){
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELCZ010, (ErrVal)0, (S8*)"Packing failed");
#endif /*(ERRCLASS & ERRCLS_ADD_RES) */
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   pst->event = (Event) EVTLCZCFGCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkLczCfgCfm
*
*
*     Desc : cmUnpkLczCfgCfm
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/

#ifdef ANSI
PUBLIC S16 cmUnpkLczCfgCfm
(
LczCfgCfm func,
Pst *pst,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkLczCfgCfm(func, pst, mBuf)
LczCfgCfm func;
Pst *pst;
Buffer *mBuf;
#endif /* ANSI */
{
   CzMngmt *cfm;
   
   TRC3(cmUnpkLczCfgCfm)

   if (pst->selector != LCZ_SEL_LWLC) {
    if ((SGetSBuf(pst->region,pst->pool,(Data **)&cfm,sizeof(CzMngmt))) != ROK){
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELCZ011, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
         cmMemset((U8 *)cfm, (U8 )0, (sizeof(CzMngmt)));
   }
   if (pst->selector == LCZ_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&cfm, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == LCZ_SEL_LC) /*lcz_c_001.main_3: Passed pst in czUnpkCzMngmt*/ 
      if (cmUnpkCzMngmt(cfm, EVTLCZCFGCFM,mBuf,pst) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(CzMngmt));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELCZ012, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cfm));
}


/***********************************************************
*
*     Func : cmPkLczStsReq
*
*
*     Desc : czPkLczStsReq
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/

#ifdef ANSI
PUBLIC S16 cmPkLczStsReq
(
Pst * pst,
Action action,
CzMngmt * sts
)
#else /* ANSI */
PUBLIC S16 cmPkLczStsReq(pst, action, sts)
Pst * pst;
Action action;
CzMngmt * sts;
#endif /* ANSI */
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLczStsReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELCZ013, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
      RETVALUE(RFAILED);
   }
   if (pst->selector == LCZ_SEL_LC) {
      /* cz001.301 : Added one more input varaible PST structure
       * to the function cmPkCzMngmt */
      if (cmPkCzMngmt(sts, EVTLCZSTSREQ, mBuf, pst) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELCZ014, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutSBuf(pst->region, pst->pool, (Data *)sts, sizeof(CzMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == LCZ_SEL_LWLC) {
      if (cmPkPtr((PTR)sts, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELCZ015, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutSBuf(pst->region, pst->pool, (Data *)sts, sizeof(CzMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (cmPkAction(action, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELCZ016, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
      SPutSBuf(pst->region, pst->pool, (Data *)sts, sizeof(CzMngmt));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != LCZ_SEL_LWLC) {
      if (SPutSBuf(pst->region, pst->pool,(Data *)sts, sizeof(CzMngmt)) != ROK){
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELCZ017, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   pst->event = (Event) EVTLCZSTSREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkLczStsReq
*
*
*     Desc : cmUnpkLczStsReq
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/

#ifdef ANSI
PUBLIC S16 cmUnpkLczStsReq
(
LczStsReq func,
Pst *pst,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkLczStsReq(func, pst, mBuf)
LczStsReq func;
Pst *pst;
Buffer *mBuf;
#endif /* ANSI */
{
   Action action;
   CzMngmt *sts;
   
   TRC3(cmUnpkLczStsReq)

   if (cmUnpkAction(&action, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELCZ018, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
      RETVALUE(RFAILED);
   }
   if (pst->selector != LCZ_SEL_LWLC) {
     if ((SGetSBuf(pst->region,pst->pool,(Data **)&sts,sizeof(CzMngmt))) != ROK)
     {
#if (ERRCLASS & ERRCLS_ADD_RES)
        SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
              (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
              (ErrVal)ELCZ019, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
        SPutMsg(mBuf);
        RETVALUE(RFAILED);
     }
         cmMemset((U8 *)sts, (U8 )0, (sizeof(CzMngmt)));
   }
   if (pst->selector == LCZ_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&sts, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == LCZ_SEL_LC) /*lcz_c_001.main_3: Passed  pst in czUnpkCzMngmt*/ 
      if (cmUnpkCzMngmt(sts, EVTLCZSTSREQ,mBuf,pst) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)sts, sizeof(CzMngmt));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELCZ020, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, action, sts));
}


/***********************************************************
*
*     Func : cmPkLczStsCfm
*
*
*     Desc : cmPkLczStsCfm
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/

#ifdef ANSI
PUBLIC S16 cmPkLczStsCfm
(
Pst * pst,
CzMngmt * cfm
)
#else /* ANSI */
PUBLIC S16 cmPkLczStsCfm(pst, cfm)
Pst * pst;
CzMngmt * cfm;
#endif /* ANSI */
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLczStsCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELCZ021, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
      RETVALUE(RFAILED);
   }
   if (pst->selector == LCZ_SEL_LC) {
      /* cz001.301 : Added one more input varaible PST structure
       * to the function cmPkCzMngmt */
      if (cmPkCzMngmt(cfm, EVTLCZSTSCFM, mBuf, pst) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELCZ022, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(CzMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == LCZ_SEL_LWLC) {
      if (cmPkPtr((PTR)cfm, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELCZ023, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(CzMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector != LCZ_SEL_LWLC) {
      if (SPutSBuf(pst->region, pst->pool,(Data *)cfm,sizeof(CzMngmt)) != ROK){
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELCZ024, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   pst->event = (Event) EVTLCZSTSCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkLczStsCfm
*
*
*     Desc : cmUnpkLczStsCfm
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/

#ifdef ANSI
PUBLIC S16 cmUnpkLczStsCfm
(
LczStsCfm func,
Pst *pst,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkLczStsCfm(func, pst, mBuf)
LczStsCfm func;
Pst *pst;
Buffer *mBuf;
#endif /* ANSI */
{
   CzMngmt *cfm;
   
   TRC3(cmUnpkLczStsCfm)

   if (pst->selector != LCZ_SEL_LWLC) {
     if ((SGetSBuf(pst->region,pst->pool,(Data **)&cfm,sizeof(CzMngmt))) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELCZ025, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
         cmMemset((U8 *)cfm, (U8 )0, (sizeof(CzMngmt)));
   }
   if (pst->selector == LCZ_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&cfm, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == LCZ_SEL_LC)/*lcz_c_001.main_3: Passed pst in czUnpkCzMngmt*/ 
             if (cmUnpkCzMngmt(cfm, EVTLCZSTSCFM,mBuf,pst) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(CzMngmt));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELCZ026, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cfm));
}




/***********************************************************
*
*     Func : cmPkLczStaReq
*
*
*     Desc : cmPkLczStaReq
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkLczStaReq
(
Pst * pst,
CzMngmt * sta
)
#else /* ANSI */
PUBLIC S16 cmPkLczStaReq(pst, sta)
Pst * pst;
CzMngmt * sta;
#endif /* ANSI */
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLczStaReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELCZ027, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
      RETVALUE(RFAILED);
   }
   if (pst->selector == LCZ_SEL_LC) {
      /* cz001.301 : Added one more input varaible PST structure
       * to the function cmPkCzMngmt */
      if (cmPkCzMngmt(sta, EVTLCZSTAREQ, mBuf, pst) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELCZ028, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutSBuf(pst->region, pst->pool, (Data *)sta, sizeof(CzMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == LCZ_SEL_LWLC) {
      if (cmPkPtr((PTR)sta, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELCZ029, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutSBuf(pst->region, pst->pool, (Data *)sta, sizeof(CzMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   /* cz001.301 purify Fix : freeing peerStaInfo pointer */
   if (pst->selector != LCZ_SEL_LWLC){
      if(sta->hdr.elmId.elmnt == STCZPEER){
         if (SPutSBuf(pst->region, pst->pool,(Data *)sta->t.ssta.s.peerSta.peerStaInfo, 
                  (sizeof(CzPeerStaInfo) * sta->t.ssta.s.peerSta.nmbPeer)) != ROK){
#if (ERRCLASS & ERRCLS_ADD_RES)
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ELCZ030, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
            SPutMsg(mBuf);
            RETVALUE(RFAILED);
         }
      }
   }

   if (pst->selector != LCZ_SEL_LWLC) {
      if (SPutSBuf(pst->region, pst->pool,(Data *)sta,sizeof(CzMngmt)) != ROK){
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELCZ030, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   pst->event = (Event) EVTLCZSTAREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}



/***********************************************************
*
*     Func : cmUnpkLczStaReq
*
*
*     Desc : cmUnpkLczStaReq
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkLczStaReq
(
LczStaReq func,
Pst *pst,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkLczStaReq(func, pst, mBuf)
LczStaReq func;
Pst *pst;
Buffer *mBuf;
#endif /* ANSI */
{
   CzMngmt *sta;
   
   TRC3(cmUnpkLczStaReq)

   if (pst->selector != LCZ_SEL_LWLC) {
     if ((SGetSBuf(pst->region,pst->pool,(Data **)&sta,sizeof(CzMngmt))) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELCZ031, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
         cmMemset((U8 *)sta, (U8 )0, (sizeof(CzMngmt)));
   }
   if (pst->selector == LCZ_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&sta, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == LCZ_SEL_LC)/*lcz_c_001.main_3: Passed  pst in czUnpkCzMngmt*/ 
             if (cmUnpkCzMngmt(sta, EVTLCZSTAREQ,mBuf,pst) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)sta, sizeof(CzMngmt));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELCZ032, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, sta));
}


/***********************************************************
*
*     Func : cmPkLczStaCfm
*
*
*     Desc : cmPkLczStaCfm
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkLczStaCfm
(
Pst * pst,
CzMngmt * cfm
)
#else /* ANSI */
PUBLIC S16 cmPkLczStaCfm(pst, cfm)
Pst * pst;
CzMngmt * cfm;
#endif /* ANSI */
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLczStaCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELCZ033, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
      RETVALUE(RFAILED);
   }
   if (pst->selector == LCZ_SEL_LC) {
      /* cz001.301 : Added one more input varaible PST structure
       * to the function cmPkCzMngmt */
      if (cmPkCzMngmt(cfm, EVTLCZSTACFM, mBuf, pst) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELCZ034, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(CzMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == LCZ_SEL_LWLC) {
      if (cmPkPtr((PTR)cfm, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELCZ035, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(CzMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector != LCZ_SEL_LWLC) {
      if (SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(CzMngmt)) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELCZ036, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   pst->event = (Event) EVTLCZSTACFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkLczStaCfm
*
*
*     Desc : cmUnpkLczStaCfm
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkLczStaCfm
(
LczStaCfm func,
Pst *pst,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkLczStaCfm(func, pst, mBuf)
LczStaCfm func;
Pst *pst;
Buffer *mBuf;
#endif /* ANSI */
{
   CzMngmt *cfm;
   
   TRC3(cmUnpkLczStaCfm)

   if (pst->selector != LCZ_SEL_LWLC) {
     if ((SGetSBuf(pst->region,pst->pool,(Data **)&cfm,sizeof(CzMngmt))) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELCZ037, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
         cmMemset((U8 *)cfm, (U8 )0, (sizeof(CzMngmt)));
   }
   if (pst->selector == LCZ_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&cfm, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == LCZ_SEL_LC) /*lcz_c_001.main_3: Passed pst in czUnpkCzMngmt*/ 
             if (cmUnpkCzMngmt(cfm, EVTLCZSTACFM,mBuf,pst) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(CzMngmt));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELCZ038, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cfm));
}


/***********************************************************
*
*     Func : cmPkLczStaInd
*
*
*     Desc : cmPkLczStaInd
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkLczStaInd
(
Pst * pst,
CzMngmt * usta
)
#else /* ANSI */
PUBLIC S16 cmPkLczStaInd(pst, usta)
Pst * pst;
CzMngmt * usta;
#endif /*ANSI */
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLczStaInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELCZ039, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
      SPutSBuf(pst->region, pst->pool, (Data *)usta, sizeof(CzMngmt));
      RETVALUE(RFAILED);
   }
   if (pst->selector == LCZ_SEL_LC) {
      /* cz001.301 : Added one more input varaible PST structure
       * to the function cmPkCzMngmt */
      if (cmPkCzMngmt(usta, EVTLCZSTAIND, mBuf, pst) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELCZ040, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutSBuf(pst->region, pst->pool, (Data *)usta, sizeof(CzMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == LCZ_SEL_LWLC) {
      if (cmPkPtr((PTR)usta, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELCZ041, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutSBuf(pst->region, pst->pool, (Data *)usta, sizeof(CzMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector != LCZ_SEL_LWLC) {
      if (SPutSBuf(pst->region, pst->pool, (Data *)usta,sizeof(CzMngmt)) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELCZ042, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   pst->event = (Event) EVTLCZSTAIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkLczStaInd
*
*
*     Desc : cmUnpkLczStaInd
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkLczStaInd
(
LczStaInd func,
Pst *pst,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkLczStaInd(func, pst, mBuf)
LczStaInd func;
Pst *pst;
Buffer *mBuf;
#endif /* ANSI */
{
   CzMngmt *usta;
   
   TRC3(cmUnpkLczStaInd)

   if (pst->selector != LCZ_SEL_LWLC) {
    if ((SGetSBuf(pst->region,pst->pool,(Data **)&usta,sizeof(CzMngmt))) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELCZ043, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
         cmMemset((U8 *)usta, (U8 )0, (sizeof(CzMngmt)));
   }
   if (pst->selector == LCZ_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&usta, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == LCZ_SEL_LC)/*lcz_c_001.main_3: Passed pst in czUnpkCzMngmt*/ 
             if (cmUnpkCzMngmt(usta, EVTLCZSTAIND,mBuf,pst) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)usta, sizeof(CzMngmt));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELCZ044, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, usta));
}


/***********************************************************
*
*     Func : cmPkLczCntrlReq
*
*
*     Desc : cmPkLczCntrlReq
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkLczCntrlReq
(
Pst * pst,
CzMngmt * cntrl
)
#else /* ANSI */
PUBLIC S16 cmPkLczCntrlReq(pst, cntrl)
Pst * pst;
CzMngmt * cntrl;
#endif /* ANSI */
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLczCntrlReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELCZ045, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
      RETVALUE(RFAILED);
   }
   if (pst->selector == LCZ_SEL_LC) {
      /* cz001.301 : Added one more input varaible PST structure
       * to the function cmPkCzMngmt */
      if (cmPkCzMngmt(cntrl, EVTLCZCNTRLREQ, mBuf, pst) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELCZ046, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutSBuf(pst->region, pst->pool, (Data *)cntrl, sizeof(CzMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == LCZ_SEL_LWLC) {
      if (cmPkPtr((PTR)cntrl, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELCZ047, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutSBuf(pst->region, pst->pool, (Data *)cntrl, sizeof(CzMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   /* cz001.301 : Purify Fix */
   if (pst->selector != LCZ_SEL_LWLC) {
    if (SPutSBuf(pst->region, pst->pool, (Data *)cntrl,sizeof(CzMngmt)) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELCZ048, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   pst->event = (Event) EVTLCZCNTRLREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkLczCntrlReq
*
*
*     Desc : cmUnpkLczCntrlReq
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkLczCntrlReq
(
LczCntrlReq func,
Pst *pst,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkLczCntrlReq(func, pst, mBuf)
LczCntrlReq func;
Pst *pst;
Buffer *mBuf;
#endif /* ANSI */
{
   CzMngmt *cntrl;
   
   TRC3(cmUnpkLczCntrlReq)

   if (pst->selector != LCZ_SEL_LWLC) {
   if ((SGetSBuf(pst->region,pst->pool,(Data **)&cntrl,sizeof(CzMngmt))) != ROK)
         {
#if (ERRCLASS & ERRCLS_ADD_RES)
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ELCZ049, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
            SPutMsg(mBuf);
            RETVALUE(RFAILED);
         }
         cmMemset((U8 *)cntrl, (U8 )0, (sizeof(CzMngmt)));
      }
   if (pst->selector == LCZ_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&cntrl, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == LCZ_SEL_LC)/*lcz_c_001.main_3 : Passed  pst in czUnpkCzMngmt*/ 
             if (cmUnpkCzMngmt(cntrl, EVTLCZCNTRLREQ,mBuf,pst) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)cntrl, sizeof(CzMngmt));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELCZ050, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cntrl));
}


/***********************************************************
*
*     Func : cmPkLczCntrlCfm
*
*
*     Desc : cmPkLczCntrlCfm
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkLczCntrlCfm
(
Pst * pst,
CzMngmt * cfm
)
#else /* ANSI */
PUBLIC S16 cmPkLczCntrlCfm(pst, cfm)
Pst * pst;
CzMngmt * cfm;
#endif /* ANSI */
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLczCntrlCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELCZ051, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
      RETVALUE(RFAILED);
   }
   if (pst->selector == LCZ_SEL_LC) {
      /* cz001.301 : Added one more input varaible PST structure
       * to the function cmPkCzMngmt */
      if (cmPkCzMngmt(cfm, EVTLCZCNTRLCFM, mBuf, pst) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELCZ052, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(CzMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == LCZ_SEL_LWLC) {
      if (cmPkPtr((PTR)cfm, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELCZ053, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(CzMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector != LCZ_SEL_LWLC) {
      if (SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(CzMngmt)) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELCZ054, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   pst->event = (Event) EVTLCZCNTRLCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkLczCntrlCfm
*
*
*     Desc : cmUnpkLczCntrlCfm
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkLczCntrlCfm
(
LczCntrlCfm func,
Pst *pst,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkLczCntrlCfm(func, pst, mBuf)
LczCntrlCfm func;
Pst *pst;
Buffer *mBuf;
#endif /* ANSI */
{
   CzMngmt *cfm;
   
   TRC3(cmUnpkLczCntrlCfm)

   if (pst->selector != LCZ_SEL_LWLC) {
     if ((SGetSBuf(pst->region,pst->pool,(Data **)&cfm,sizeof(CzMngmt))) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELCZ055, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
         cmMemset((U8 *)cfm, (U8 )0, (sizeof(CzMngmt)));
   }
   if (pst->selector == LCZ_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&cfm, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == LCZ_SEL_LC)/*lcz_c_001.main_3: Passed argument pst in czUnpkCzMngmt*/ 
             if (cmUnpkCzMngmt(cfm, EVTLCZCNTRLCFM,mBuf,pst) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(CzMngmt));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELCZ056, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cfm));
}


/***********************************************************
*
*     Func : cmPkLczTrcInd
*
*
*     Desc : cmPkLczTrcInd
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkLczTrcInd
(
Pst * pst,
CzMngmt * trac,
Buffer * tracBuf
)
#else /* ANSI */
PUBLIC S16 cmPkLczTrcInd(pst, trac, tracBuf)
Pst * pst;
CzMngmt * trac;
Buffer * tracBuf;
#endif /* ANSI */
{
   Buffer *mBuf = NULLP;
   MsgLen msgLen=0;
   TRC3(cmPkLczTrcInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELCZ057, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
      RETVALUE(RFAILED);
   }
   if (pst->selector == LCZ_SEL_LC) {
      if (SFndLenMsg(tracBuf, &msgLen) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELCZ058, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutSBuf(pst->region, pst->pool, (Data *)trac, sizeof(CzMngmt));
         SPutMsg(tracBuf);
         RETVALUE(RFAILED);
      }
      if (SCatMsg(mBuf, tracBuf, M1M2) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELCZ059, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutSBuf(pst->region, pst->pool, (Data *)trac, sizeof(CzMngmt));
         SPutMsg(tracBuf);
         RETVALUE(RFAILED);
      }
      SPutMsg(tracBuf);
      CMCHKPK(SPkS16, msgLen, mBuf);

   }
   else if (pst->selector == LCZ_SEL_LWLC) {
      if (cmPkPtr((PTR)tracBuf, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELCZ060, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutSBuf(pst->region, pst->pool, (Data *)trac, sizeof(CzMngmt));
         SPutMsg(tracBuf);
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector == LCZ_SEL_LC) {
      /* cz001.301 : Added one more input varaible PST structure
       * to the function cmPkCzMngmt */
      if (cmPkCzMngmt(trac, EVTLCZTRCIND, mBuf, pst) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELCZ061, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutSBuf(pst->region, pst->pool, (Data *)trac, sizeof(CzMngmt));
         SPutMsg(tracBuf);
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == LCZ_SEL_LWLC) {
      if (cmPkPtr((PTR)trac, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELCZ062, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutSBuf(pst->region, pst->pool, (Data *)trac, sizeof(CzMngmt));
         SPutMsg(tracBuf);
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector != LCZ_SEL_LWLC) {
      if (SPutSBuf(pst->region, pst->pool, (Data *)trac,
           sizeof(CzMngmt)) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELCZ063, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   pst->event = (Event) EVTLCZTRCIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkLczTrcInd
*
*
*     Desc : cmUnpkkLczTrcInd
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkLczTrcInd
(
LczTrcInd func,
Pst *pst,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkLczTrcInd(func, pst, mBuf)
LczTrcInd func;
Pst *pst;
Buffer *mBuf;
#endif /* ANSI */
{
   CzMngmt *trac;
   /*x2ap kwork fix*/
   Buffer *tracBuf=NULLP;
   S16 msgLen;
   MsgLen    totalMsgLen;
   
   TRC3(cmUnpkLczTrcInd)

   if (pst->selector != LCZ_SEL_LWLC) {
     if ((SGetSBuf(pst->region,pst->pool,(Data **)&trac,
          sizeof(CzMngmt))) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELCZ064, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
         cmMemset((U8 *)trac, (U8 )0, (sizeof(CzMngmt)));
   }
   if (pst->selector == LCZ_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&trac, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == LCZ_SEL_LC)/*lcz_c_001.main_3: Passed  pst in czUnpkCzMngmt*/ 
             if (cmUnpkCzMngmt(trac, EVTLCZTRCIND,mBuf,pst) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)trac, sizeof(CzMngmt));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELCZ065, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES)*/
      RETVALUE(RFAILED);
   }
   if (pst->selector == LCZ_SEL_LC) {
      CMCHKUNPK(SUnpkS16, &msgLen, mBuf);
      if (SFndLenMsg(mBuf, &totalMsgLen) != ROK){
         /* cz001.301 : purify fix: freeing trac pointer in error scenario */
         SPutSBuf(pst->region, pst->pool, (Data *)trac, sizeof(CzMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      if (SSegMsg(mBuf, totalMsgLen-msgLen, &tracBuf) != ROK){
         /* cz001.301 : purify fix: freeing trac in error scenario */
         SPutSBuf(pst->region, pst->pool, (Data *)trac, sizeof(CzMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == LCZ_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&tracBuf, mBuf) != ROK) {
         /* cz001.301 : purify fix: freeing trac in error scenario */
         SPutSBuf(pst->region, pst->pool, (Data *)trac, sizeof(CzMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   /* lcz_c_001.main_4 : if both if and else if, didn't hit
    * than something wrong, so ret RFAILED. */
   else
   {
         /* cz001.301 : purify fix: freeing trac in error scenario */
         SPutSBuf(pst->region, pst->pool, (Data *)trac, sizeof(CzMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, trac, tracBuf));
}


/***********************************************************
*
*     Func : cmPkCzNetAddrLst
*
*
*     Desc : czNetAddrLst 
   @brief X2AP structure to hold the list of sctp ip address 
   @details This structure contains the list of IP address spacifid by number value at the time of connection establishment.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzNetAddrLst
(
CzNetAddrLst *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzNetAddrLst(param, mBuf)
CzNetAddrLst *param;
Buffer *mBuf;
#endif /* ANSI */
{

   S32 cnt;
   TRC3(cmPkCzNetAddrLst)

   for (cnt=SCT_MAX_NET_ADDRS-1; cnt >= 0; cnt--) {
      CMCHKPK(cmPkCmNetAddr, &param->nAddr[cnt], mBuf);
   }
   CMCHKPK(SPkU8, param->nmb, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzNetAddrLst
*
*
*     Desc : czNetAddrLst 
   @brief X2AP structure to hold the list of sctp ip address 
   @details This structure contains the list of IP address spacifid by number value at the time of connection establishment.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzNetAddrLst
(
CzNetAddrLst *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzNetAddrLst(param, mBuf)
CzNetAddrLst *param;
Buffer *mBuf;
#endif /* ANSI */
{

   S32 cnt;
   TRC3(cmUnpkCzNetAddrLst)

   CMCHKUNPK(SUnpkU8, &param->nmb, mBuf);
   for (cnt=0; cnt<SCT_MAX_NET_ADDRS; cnt++) {
      CMCHKUNPK(cmUnpkCmNetAddr, &param->nAddr[cnt], mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCzSctpAddr
*
*
*     Desc : czSctpAddr 
   @brief X2AP structure to hold the sctp transport address 
   @details This structure contains the list IP address and Port to be used at
   the time of connection establishment.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzSctpAddr
(
CzSctpAddr *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzSctpAddr(param, mBuf)
CzSctpAddr *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzSctpAddr)

   CMCHKPK(SPkU16, param->sctPort, mBuf);
   CMCHKPK(cmPkCzNetAddrLst, &param->ipAddr, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzSctpAddr
*
*
*     Desc : czSctpAddr 
   @brief X2AP structure to hold the sctp transport address 
   @details This structure contains the list IP address and Port to be used at
   the time of connection establishment.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzSctpAddr
(
CzSctpAddr *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzSctpAddr(param, mBuf)
CzSctpAddr *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzSctpAddr)

   CMCHKUNPK(cmUnpkCzNetAddrLst, &param->ipAddr, mBuf);
   CMCHKUNPK(SUnpkU16, &param->sctPort, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCzGenCfg
*
*
*     Desc : czGenCfg 
   @brief X2AP General Configuration
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzGenCfg
(
CzGenCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzGenCfg(param, mBuf)
CzGenCfg *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzGenCfg)

   CMCHKPK(cmPkPst, &param->lmPst, mBuf);

#ifdef DEBUGP
   CMCHKPK(SPkU32, param->dbgMask, mBuf);

#endif /* DEBUG */
   CMCHKPK(SPkS16, param->timeRes, mBuf);
   CMCHKPK(SPkS16, param->memLowerThr, mBuf);
   CMCHKPK(SPkS16, param->memUpperThr, mBuf);
   CMCHKPK(SPkU32, param->maxNmbPeer, mBuf);
   CMCHKPK(SPkS16, param->nmbSctSaps, mBuf);
   CMCHKPK(SPkS16, param->nmbCztSaps, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzGenCfg
*
*
*     Desc : czGenCfg 
   @brief X2AP General Configuration
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzGenCfg
(
CzGenCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzGenCfg(param, mBuf)
CzGenCfg *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzGenCfg)

   CMCHKUNPK(SUnpkS16, &param->nmbCztSaps, mBuf);
   CMCHKUNPK(SUnpkS16, &param->nmbSctSaps, mBuf);
   CMCHKUNPK(SUnpkU32, &param->maxNmbPeer, mBuf);
   CMCHKUNPK(SUnpkS16, &param->memUpperThr, mBuf);
   CMCHKUNPK(SUnpkS16, &param->memLowerThr, mBuf);
   CMCHKUNPK(SUnpkS16, &param->timeRes, mBuf);

#ifdef DEBUGP
   CMCHKUNPK(SUnpkU32, &param->dbgMask, mBuf);

#endif /* DEBUG */
   CMCHKUNPK(cmUnpkPst, &param->lmPst, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCzGenReCfg
*
*
*     Desc : czGenReCfg 
   @brief X2AP General Re-Configuration 
   @details This structure defines the reconfigurable parameters present in the
 GenCfg structure. Any parameters other than these are not allowed.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzGenReCfg
(
CzGenReCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzGenReCfg(param, mBuf)
CzGenReCfg *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzGenReCfg)

   CMCHKPK(SPkS16, param->memLowerThr, mBuf);
   CMCHKPK(SPkS16, param->memUpperThr, mBuf);

#ifdef DEBUGP
   CMCHKPK(SPkU32, param->dbgMask, mBuf);

#endif /* DEBUG */
   CMCHKPK(SPkS16, param->timeRes, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzGenReCfg
*
*
*     Desc : czGenReCfg 
   @brief X2AP General Re-Configuration 
   @details This structure defines the reconfigurable parameters present in the
 GenCfg structure. Any parameters other than these are not allowed.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzGenReCfg
(
CzGenReCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzGenReCfg(param, mBuf)
CzGenReCfg *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzGenReCfg)

   CMCHKUNPK(SUnpkS16, &param->timeRes, mBuf);

#ifdef DEBUGP
   CMCHKUNPK(SUnpkU32, &param->dbgMask, mBuf);

#endif /* DEBUG */
   CMCHKUNPK(SUnpkS16, &param->memUpperThr, mBuf);
   CMCHKUNPK(SUnpkS16, &param->memLowerThr, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCzProtCfg
*
*
*     Desc : czProtCfg 
   @brief X2AP Layer Protocol Configuration 
   @details This structure describes the individual parameters of the protocol 
   configuration.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzProtCfg
(
CzProtCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzProtCfg(param, mBuf)
CzProtCfg *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzProtCfg)

   CMCHKPK(cmPkCzSctpAddr, &param->srcAddr, mBuf);
   CMCHKPK(SPkS16, param->defDPeerUSapId, mBuf);
   CMCHKPK(SPkU8, param->dynamPeerFlag, mBuf);
   CMCHKPK(SPkU16, param->timeToWait, mBuf);
   CMCHKPK(SPkU16, param->tX2RELOCOverall, mBuf);
   CMCHKPK(SPkU16, param->tRELOCprep, mBuf);
   CMCHKPK(SPkU32, param->eNbId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzProtCfg
*
*
*     Desc : czProtCfg 
   @brief X2AP Layer Protocol Configuration 
   @details This structure describes the individual parameters of the protocol 
   configuration.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzProtCfg
(
CzProtCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzProtCfg(param, mBuf)
CzProtCfg *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzProtCfg)

   CMCHKUNPK(SUnpkU32, &param->eNbId, mBuf);
   CMCHKUNPK(SUnpkU16, &param->tRELOCprep, mBuf);
   CMCHKUNPK(SUnpkU16, &param->tX2RELOCOverall, mBuf);
   CMCHKUNPK(SUnpkU16, &param->timeToWait, mBuf);
   CMCHKUNPK(SUnpkU8, &param->dynamPeerFlag, mBuf);
   CMCHKUNPK(SUnpkS16, &param->defDPeerUSapId, mBuf);
   CMCHKUNPK(cmUnpkCzSctpAddr, &param->srcAddr, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCzProtReCfg
*
*
*     Desc : czProtReCfg 
   @brief X2AP Layer Protocol Re-Configuration 
   @details This structure defines the reconfigurable parameters present in the
 ProtCfg structure. Any parameters other than these are not allowed.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzProtReCfg
(
CzProtReCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzProtReCfg(param, mBuf)
CzProtReCfg *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzProtReCfg)

   CMCHKPK(SPkU16, param->timeToWait, mBuf);
   CMCHKPK(SPkU16, param->tX2RELOCOverall, mBuf);
   CMCHKPK(SPkU16, param->tRELOCprep, mBuf);
   CMCHKPK(SPkS16, param->defDPeerUSapId, mBuf);
   CMCHKPK(SPkU8, param->dynamPeerFlag, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzProtReCfg
*
*
*     Desc : czProtReCfg 
   @brief X2AP Layer Protocol Re-Configuration 
   @details This structure defines the reconfigurable parameters present in the
 ProtCfg structure. Any parameters other than these are not allowed.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzProtReCfg
(
CzProtReCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzProtReCfg(param, mBuf)
CzProtReCfg *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzProtReCfg)

   CMCHKUNPK(SUnpkU8, &param->dynamPeerFlag, mBuf);
   CMCHKUNPK(SUnpkS16, &param->defDPeerUSapId, mBuf);
   CMCHKUNPK(SUnpkU16, &param->tRELOCprep, mBuf);
   CMCHKUNPK(SUnpkU16, &param->tX2RELOCOverall, mBuf);
   CMCHKUNPK(SUnpkU16, &param->timeToWait, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCzCztSapCfg
*
*
*     Desc : czCztSapCfg 
   @brief X2AP Layer USAP Configuration 
   @details This structure describes the parameters of USAP configuration.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzCztSapCfg
(
CzCztSapCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzCztSapCfg(param, mBuf)
CzCztSapCfg *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzCztSapCfg)

   CMCHKPK(SPkU8, param->route, mBuf);
   CMCHKPK(SPkU8, param->priority, mBuf);
   CMCHKPK(cmPkMemoryId, &param->mem, mBuf);
   CMCHKPK(SPkU8, param->selector, mBuf);
   CMCHKPK(SPkS16, param->spId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzCztSapCfg
*
*
*     Desc : czCztSapCfg 
   @brief X2AP Layer USAP Configuration 
   @details This structure describes the parameters of USAP configuration.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzCztSapCfg
(
CzCztSapCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzCztSapCfg(param, mBuf)
CzCztSapCfg *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzCztSapCfg)

   CMCHKUNPK(SUnpkS16, &param->spId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->selector, mBuf);
   CMCHKUNPK(cmUnpkMemoryId, &param->mem, mBuf);
   CMCHKUNPK(SUnpkU8, &param->priority, mBuf);
   CMCHKUNPK(SUnpkU8, &param->route, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCzSctSapCfg
*
*
*     Desc : czSctSapCfg 
   @brief X2AP Layer TSAP Configuration 
   @details This structure describes the configurable parameters for SCTP SAP.
   Various SCTP SAPs supported are Trillium SCTP, kernel SCTP and dummy SCTP.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzSctSapCfg
(
CzSctSapCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzSctSapCfg(param, mBuf)
CzSctSapCfg *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzSctSapCfg)

   CMCHKPK(SPkU8, param->maxBndRetry, mBuf);
   CMCHKPK(cmPkTmrCfg, &param->tBndTmr, mBuf);
   CMCHKPK(SPkU8, param->dstInstId, mBuf);
   CMCHKPK(SPkU8, param->dstEntId, mBuf);
   CMCHKPK(SPkU16, param->dstProcId, mBuf);
   CMCHKPK(SPkU8, param->route, mBuf);
   CMCHKPK(SPkU8, param->priority, mBuf);
   CMCHKPK(cmPkMemoryId, &param->mem, mBuf);
   CMCHKPK(SPkU8, param->selector, mBuf);
   CMCHKPK(SPkS16, param->spId, mBuf);
   CMCHKPK(SPkS16, param->suId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzSctSapCfg
*
*
*     Desc : czSctSapCfg 
   @brief X2AP Layer TSAP Configuration 
   @details This structure describes the configurable parameters for SCTP SAP.
   Various SCTP SAPs supported are Trillium SCTP, kernel SCTP and dummy SCTP.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzSctSapCfg
(
CzSctSapCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzSctSapCfg(param, mBuf)
CzSctSapCfg *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzSctSapCfg)

   CMCHKUNPK(SUnpkS16, &param->suId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->spId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->selector, mBuf);
   CMCHKUNPK(cmUnpkMemoryId, &param->mem, mBuf);
   CMCHKUNPK(SUnpkU8, &param->priority, mBuf);
   CMCHKUNPK(SUnpkU8, &param->route, mBuf);
   CMCHKUNPK(SUnpkU16, &param->dstProcId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->dstEntId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->dstInstId, mBuf);
   CMCHKUNPK(cmUnpkTmrCfg, &param->tBndTmr, mBuf);
   CMCHKUNPK(SUnpkU8, &param->maxBndRetry, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCzAssocCfg
*
*
*     Desc : czAssocCfg
   @brief X2AP peer assosiation information
   @details This structure describes the Association configuration parameters.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzAssocCfg
(
CzAssocCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzAssocCfg(param, mBuf)
CzAssocCfg *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzAssocCfg)

   CMCHKPK(cmPkSctNetAddrLst, &param->dstAddrLst, mBuf);
   CMCHKPK(cmPkSctPort, param->dstPort, mBuf);
   CMCHKPK(cmPkCmNetAddr, &param->priDstAddr, mBuf);
   CMCHKPK(SPkU16, param->locOutStrms, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzAssocCfg
*
*
*     Desc : czAssocCfg
   @brief X2AP peer assosiation information
   @details This structure describes the Association configuration parameters.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzAssocCfg
(
CzAssocCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzAssocCfg(param, mBuf)
CzAssocCfg *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzAssocCfg)

   CMCHKUNPK(SUnpkU16, &param->locOutStrms, mBuf);
   CMCHKUNPK(cmUnpkCmNetAddr, &param->priDstAddr, mBuf);
   CMCHKUNPK(cmUnpkSctPort, &param->dstPort, mBuf);
   CMCHKUNPK(cmUnpkSctNetAddrLst, &param->dstAddrLst, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCzPeerCfg
*
*
*     Desc : czPeerCfg
   @brief  X2AP peer Information
   @details This structure describes the peer configurations like peerId and
   assocCfg. The layer manager configures all the acceptable peers(eNodeBs) 
   after the  LSAP configuration. X2AP layer creates the peerCb for each 
   peer. But the  association is  only be setup between two peers after the
   reception of the X2 Setup Request from User. While receiving a association
   request from the peer eNodeB, X2AP searches for the configured peer, and
   if dynamic peer support  is not enabled then X2AP not accepts the
   association.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzPeerCfg
(
CzPeerCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzPeerCfg(param, mBuf)
CzPeerCfg *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzPeerCfg)

   CMCHKPK(cmPkCzAssocCfg, &param->assocCfg, mBuf);
   CMCHKPK(cmPkTknU16, &param->globalProcStrmId, mBuf);

   CMCHKPK(SPkU16, param->iPAValue, mBuf);
   CMCHKPK(SPkU16, param->eAValue, mBuf);
   CMCHKPK(SPkS16, param->uSapId, mBuf);
   CMCHKPK(SPkS16, param->tSapId, mBuf);
   CMCHKPK(SPkU32, param->peerId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzPeerCfg
*
*
*     Desc : czPeerCfg
   @brief  X2AP peer Information
   @details This structure describes the peer configurations like peerId and
   assocCfg. The layer manager configures all the acceptable peers(eNodeBs) 
   after the  LSAP configuration. X2AP layer creates the peerCb for each 
   peer. But the  association is  only be setup between two peers after the
   reception of the X2 Setup Request from User. While receiving a association
   request from the peer eNodeB, X2AP searches for the configured peer, and
   if dynamic peer support  is not enabled then X2AP not accepts the
   association.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzPeerCfg
(
CzPeerCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzPeerCfg(param, mBuf)
CzPeerCfg *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzPeerCfg)

   CMCHKUNPK(SUnpkU32, &param->peerId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->tSapId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->uSapId, mBuf);
   CMCHKUNPK(SUnpkU16, &param->eAValue, mBuf);
   CMCHKUNPK(SUnpkU16, &param->iPAValue, mBuf);
   CMCHKUNPK(cmUnpkTknU16, &param->globalProcStrmId, mBuf);
   CMCHKUNPK(cmUnpkCzAssocCfg, &param->assocCfg, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCzPeerLstCfg
*
*
*     Desc : czPeerLstCfg 
   @brief X2AP Layer peer List Configuration 
   @details This structure defines the list of peer configurations.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzPeerLstCfg
(
Pst *pst,
CzPeerLstCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzPeerLstCfg(pst, param, mBuf)
Pst *pst;
CzPeerLstCfg *param;
Buffer *mBuf;
#endif /* ANSI */
{

   Cntr cnt;
   TRC3(cmPkCzPeerLstCfg)

   if (param->nmbPeers)
   {
      for (cnt = param->nmbPeers - 1; cnt >= 0; cnt--)
      {
         CMCHKPK(cmPkCzPeerCfg, &param->peerCfg[cnt], mBuf);
      }
      /* cz001.301 : Added one more input varaible PST structure
       * to the function cmPkCzMngmt */
      (Void)SPutSBuf(pst->region, pst->pool,(Data*)param->peerCfg,
            (sizeof(CzPeerCfg) * param->nmbPeers));
      param->peerCfg = NULLP;

   }
   CMCHKPK(SPkU32, param->nmbPeers, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzPeerLstCfg
*
*
*     Desc : czPeerLstCfg 
   @brief X2AP Layer peer List Configuration 
   @details This structure defines the list of peer configurations.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzPeerLstCfg
(
Pst *pst,/*lcz_c_001.main_3: Added pst argument*/
CzPeerLstCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzPeerLstCfg(pst,param, mBuf)
Pst *pst;/*lcz_c_001.main_3: Added pst argument*/
CzPeerLstCfg *param;
Buffer *mBuf;
#endif /* ANSI */
{
   Cntr cnt;

   TRC3(cmUnpkCzPeerLstCfg)

      CMCHKUNPK(SUnpkU32, &param->nmbPeers, mBuf);

   if (param->nmbPeers)
   {
      /*lcz_c_001.main_3: Replaced CZ_ALLOC with SGetSBuf*/
       if ((SGetSBuf(pst->region,pst->pool,(Data **)&(param->peerCfg),(sizeof(CzPeerCfg) *
        param->nmbPeers))) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELCZ066, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }

      cmMemset( (U8* )param->peerCfg, 0, sizeof(CzPeerCfg) * param->nmbPeers);

      for (cnt = 0; cnt <  (S32)param->nmbPeers; cnt++)
      {
         CMCHKUNPK(cmUnpkCzPeerCfg, &param->peerCfg[cnt], mBuf);
      }
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCzCfg
*
*
*     Desc : czCfg 
   @brief X2AP Layer Configuration 
   @details This structure contains the union of all the configuration structure
 that X2AP expects from Layer Manager. For example, peerCfg, GenCfg, USAPCfg,
 SctCfg etc.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzCfg
(
CzCfg *param,
Elmnt elmnt,
Buffer *mBuf,
Pst *pst
)
#else /* ANSI */
PUBLIC S16 cmPkCzCfg(param, elmnt, mBuf, pst)
CzCfg *param;
Elmnt elmnt;
Buffer *mBuf;
Pst *pst;
#endif /* ANSI */
{

   TRC3(cmPkCzCfg)

  switch(elmnt) 
  {
     case STCZPROT:
        CMCHKPK(cmPkCzProtReCfg, &param->r.protReCfg, mBuf);
        break;
     case STCZGEN:
        CMCHKPK(cmPkCzGenReCfg, &param->r.genReCfg, mBuf);
        break;
     default :
        break;
  }
   switch(elmnt) {
      case STCZPEER:
      /* cz001.301 : Added one more input varaible PST structure
       * to the function cmPkCzMngmt */
         CMCHKPKVERLOG(cmPkCzPeerLstCfg, &param->u.peerLst, mBuf, 0, pst);
         break;
      case STCZSCTSAP:
         CMCHKPK(cmPkCzSctSapCfg, &param->u.sctSap, mBuf);
         break;
      case STCZCZTSAP:
         CMCHKPK(cmPkCzCztSapCfg, &param->u.cztSap, mBuf);
         break;
      case STCZPROT:
         CMCHKPK(cmPkCzProtCfg, &param->u.prot, mBuf);
         break;
      case STCZGEN:
         CMCHKPK(cmPkCzGenCfg, &param->u.gen, mBuf);
         break;
      default :
         RETVALUE(RFAILED);
   }

   
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzCfg
*
*
*     Desc : czCfg 
   @brief X2AP Layer Configuration 
   @details This structure contains the union of all the configuration structure
 that X2AP expects from Layer Manager. For example, peerCfg, GenCfg, USAPCfg,
 SctCfg etc.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzCfg
(
CzCfg *param,
Elmnt elmnt,
Buffer *mBuf,
Pst    *pst/*lcz_c_001.main_3: Added pst argument*/
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzCfg(param, elmnt,mBuf,pst)
CzCfg *param;
Elmnt elmnt;
Buffer *mBuf;
Pst    *pst;  /*lcz_c_001.main_3: Added pst argument*/
#endif /* ANSI */
{

   TRC3(cmUnpkCzCfg)


   switch(elmnt) {
      case STCZGEN:
         CMCHKUNPK(cmUnpkCzGenCfg, &param->u.gen, mBuf);
         break;
      case STCZPROT:
         CMCHKUNPK(cmUnpkCzProtCfg, &param->u.prot, mBuf);
         break;
      case STCZCZTSAP:
         CMCHKUNPK(cmUnpkCzCztSapCfg, &param->u.cztSap, mBuf);
         break;
      case STCZSCTSAP:
         CMCHKUNPK(cmUnpkCzSctSapCfg, &param->u.sctSap, mBuf);
         break;
      case STCZPEER:
          /*lcz_c_001.main_3: Replaced CMCHKUNPK with CMCHKUNPKVERLOG*/
         CMCHKUNPKVERLOG(cmUnpkCzPeerLstCfg, &param->u.peerLst, mBuf,0,pst);
         break;
      default :
         RETVALUE(RFAILED);
   }
   switch(elmnt) {
      case STCZGEN:
         CMCHKUNPK(cmUnpkCzGenReCfg, &param->r.genReCfg, mBuf);
         break;
      case STCZPROT:
         CMCHKUNPK(cmUnpkCzProtReCfg, &param->r.protReCfg, mBuf);
         break;
      default :
         break;
   }

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCzSapCntrl
*
*
*     Desc : czSapCntrl
   @brief X2AP's SAP Control information
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzSapCntrl
(
CzSapCntrl *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzSapCntrl(param, mBuf)
CzSapCntrl *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzSapCntrl)

   CMCHKPK(SPkS16, param->id, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzSapCntrl
*
*
*     Desc : czSapCntrl
   @brief X2AP's SAP Control information
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzSapCntrl
(
CzSapCntrl *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzSapCntrl(param, mBuf)
CzSapCntrl *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzSapCntrl)

   CMCHKUNPK(SUnpkS16, &param->id, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCzEndPtCntrl
*
*
*     Desc : czEndPtCntrl
   @brief X2AP's End point Control request is used close/open
    the end point for the spacified end point Id.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzEndPtCntrl
(
CzEndPtCntrl *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzEndPtCntrl(param, mBuf)
CzEndPtCntrl *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzEndPtCntrl)

   CMCHKPK(SPkS16, param->tsapId, mBuf);
   CMCHKPK(SPkU32, param->endPtId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzEndPtCntrl
*
*
*     Desc : czEndPtCntrl
   @brief X2AP's End point Control request is used close/open
    the end point for the spacified end point Id.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzEndPtCntrl
(
CzEndPtCntrl *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzEndPtCntrl(param, mBuf)
CzEndPtCntrl *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzEndPtCntrl)

   CMCHKUNPK(SUnpkU32, &param->endPtId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->tsapId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCzPeerCntrl
*
*
*     Desc : czPeerCntrl
   @brief X2AP's  Peer  trace Control information
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzPeerCntrl
(
CzPeerCntrl *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzPeerCntrl(param, mBuf)
CzPeerCntrl *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzPeerCntrl)

   CMCHKPK(SPkU32, param->peerId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzPeerCntrl
*
*
*     Desc : czPeerCntrl
   @brief X2AP's  Peer  trace Control information
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzPeerCntrl
(
CzPeerCntrl *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzPeerCntrl(param, mBuf)
CzPeerCntrl *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzPeerCntrl)

   CMCHKUNPK(SUnpkU32, &param->peerId, mBuf);
   RETVALUE(ROK);
}


#ifdef DEBUGP

#ifdef DEBUGP


/***********************************************************
*
*     Func : cmPkCzDbgCntrl
*
*
*     Desc : czDbgCntrl
   @brief X2AP's peer debug Control information 
   @details This structure defines the different debug masks used in the X2AP.
    The following values are used for dbgMask:
    
      - DBGMASK_UI
      - DBGMASK_LI
      - DBGMASK_MI
 
      It can be set to a combination of the above mentioned allowable values. For
 example, if the debugging prints at the upper and lower interfaces of the layer
 are to be enabled or disabled set the mask as below.
 
 - To Enbale the debug mask for upper layer set the degug mask value DBGMASK_UI. 
 - To Enbale the debug mask for Lower layer set the degug mask value DBGMASK_LI. 
 - To Enbale the debug mask for both Lower and upper layer set the degug mask
   value to  the DBGMASK_UI (bitwise) OR with DBGMASK_LI.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzDbgCntrl
(
CzDbgCntrl *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzDbgCntrl(param, mBuf)
CzDbgCntrl *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzDbgCntrl)

   CMCHKPK(SPkU32, param->dbgMask, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzDbgCntrl
*
*
*     Desc : czDbgCntrl
   @brief X2AP's peer debug Control information 
   @details This structure defines the different debug masks used in the X2AP.
    The following values are used for dbgMask:
    
      - DBGMASK_UI
      - DBGMASK_LI
      - DBGMASK_MI
 
      It can be set to a combination of the above mentioned allowable values. For
 example, if the debugging prints at the upper and lower interfaces of the layer
 are to be enabled or disabled set the mask as below.
 
 - To Enbale the debug mask for upper layer set the degug mask value DBGMASK_UI. 
 - To Enbale the debug mask for Lower layer set the degug mask value DBGMASK_LI. 
 - To Enbale the debug mask for both Lower and upper layer set the degug mask
   value to  the DBGMASK_UI (bitwise) OR with DBGMASK_LI.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzDbgCntrl
(
CzDbgCntrl *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzDbgCntrl(param, mBuf)
CzDbgCntrl *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzDbgCntrl)

   CMCHKUNPK(SUnpkU32, &param->dbgMask, mBuf);
   RETVALUE(ROK);
}


#endif /* DEBUG */

#endif /* DEBUG */


/***********************************************************
*
*     Func : cmPkCzLSapTrcCntrl
*
*
*     Desc : czLSapTrcCntrl
   @brief X2AP's lower SAP trace Control information 
   @details This structure defines the trace mask and trace length used for the
 trace function.
 The direction of the messages to be traced. The allowable values for the trace
 mask are:
     - LCZ_TRC_PNODE
     - LCZ_TRC_LSAP_IN
     - LCZ_TRC_LSAP_OUT
 The LCZ_TRC_PNODE takes precedence. If set, tracing is done based on the trace
 parameters of the peer node else tracing is done based on the direction set
 in the trace mask. It can be set to a combination of the for the mentioned
 allowable values. For example, if tracing in both directions of the layer are
 to be enabled/disabled, the trcMask is set to LCZ_TRC_LSAP_IN |
 LCZ_TRC_LSAP_OUT.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzLSapTrcCntrl
(
CzLSapTrcCntrl *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzLSapTrcCntrl(param, mBuf)
CzLSapTrcCntrl *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzLSapTrcCntrl)

   CMCHKPK(SPkS32, param->trcLen, mBuf);
   CMCHKPK(SPkU32, param->trcMask, mBuf);
   CMCHKPK(SPkS16, param->lSapId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzLSapTrcCntrl
*
*
*     Desc : czLSapTrcCntrl
   @brief X2AP's lower SAP trace Control information 
   @details This structure defines the trace mask and trace length used for the
 trace function.
 The direction of the messages to be traced. The allowable values for the trace
 mask are:
     - LCZ_TRC_PNODE
     - LCZ_TRC_LSAP_IN
     - LCZ_TRC_LSAP_OUT
 The LCZ_TRC_PNODE takes precedence. If set, tracing is done based on the trace
 parameters of the peer node else tracing is done based on the direction set
 in the trace mask. It can be set to a combination of the for the mentioned
 allowable values. For example, if tracing in both directions of the layer are
 to be enabled/disabled, the trcMask is set to LCZ_TRC_LSAP_IN |
 LCZ_TRC_LSAP_OUT.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzLSapTrcCntrl
(
CzLSapTrcCntrl *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzLSapTrcCntrl(param, mBuf)
CzLSapTrcCntrl *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzLSapTrcCntrl)

   CMCHKUNPK(SUnpkS16, &param->lSapId, mBuf);
   CMCHKUNPK(SUnpkU32, &param->trcMask, mBuf);
   CMCHKUNPK(SUnpkS32, &param->trcLen, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCzPNodeTrcCntrl
*
*
*     Desc : czPNodeTrcCntrl
   @brief X2AP's  Peer  trace Control information 
   @details This structure defines the tracing based on the peer node.  
   The allowable values for traceMask are:
   
      - LCZ_TRC_PNODE_IN
      - LCZ_TRC_PNODE_OUT
      
   It can be set to a combination of the above mentioned allowable values. For
   example, to enable or disable the trace in both directions of the x2ap layer use 
   the below options

 - To Enbale the trace for the receiving buffer set the trcMask to LCZ_TRC_PNODE_IN. 
 - To Enbale the trace for the transmiting  buffer set the trcMask to LCZ_TRC_PNODE_OUT. 
 - To Enbale the debug mask for both transmiting and receving buffer set the
    trcmask value to  LCZ_TRC_PNODE_IN  (bitwise) OR with LCZ_TRC_PNODE_OUT.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzPNodeTrcCntrl
(
CzPNodeTrcCntrl *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzPNodeTrcCntrl(param, mBuf)
CzPNodeTrcCntrl *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzPNodeTrcCntrl)

   CMCHKPK(SPkS32, param->trcLen, mBuf);
   CMCHKPK(SPkU32, param->trcMask, mBuf);
   CMCHKPK(SPkU32, param->peerId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzPNodeTrcCntrl
*
*
*     Desc : czPNodeTrcCntrl
   @brief X2AP's  Peer  trace Control information 
   @details This structure defines the tracing based on the peer node.  
   The allowable values for traceMask are:
   
      - LCZ_TRC_PNODE_IN
      - LCZ_TRC_PNODE_OUT
      
   It can be set to a combination of the above mentioned allowable values. For
   example, to enable or disable the trace in both directions of the x2ap layer use 
   the below options

 - To Enbale the trace for the receiving buffer set the trcMask to LCZ_TRC_PNODE_IN. 
 - To Enbale the trace for the transmiting  buffer set the trcMask to LCZ_TRC_PNODE_OUT. 
 - To Enbale the debug mask for both transmiting and receving buffer set the
    trcmask value to  LCZ_TRC_PNODE_IN  (bitwise) OR with LCZ_TRC_PNODE_OUT.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzPNodeTrcCntrl
(
CzPNodeTrcCntrl *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzPNodeTrcCntrl(param, mBuf)
CzPNodeTrcCntrl *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzPNodeTrcCntrl)

   CMCHKUNPK(SUnpkU32, &param->peerId, mBuf);
   CMCHKUNPK(SUnpkU32, &param->trcMask, mBuf);
   CMCHKUNPK(SUnpkS32, &param->trcLen, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCzModAsPriAddrCntrl
*
*
*     Desc : CzModAsPriAddrCntrl
   @brief X2AP's  primary address modification Control information 
   @details This structure is used to set dest primary address of the
   association.The association control primitives are used to maintain the
   association and to dynamically change association parameters.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzModAsPriAddrCntrl
(
CzModAsPriAddrCntrl *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzModAsPriAddrCntrl(param, mBuf)
CzModAsPriAddrCntrl *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzModAsPriAddrCntrl)

   CMCHKPK(cmPkCmNetAddr, &param->priDstAddr, mBuf);
   CMCHKPK(SPkU32, param->peerId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzModAsPriAddrCntrl
*
*
*     Desc : CzModAsPriAddrCntrl
   @brief X2AP's  primary address modification Control information 
   @details This structure is used to set dest primary address of the
   association.The association control primitives are used to maintain the
   association and to dynamically change association parameters.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzModAsPriAddrCntrl
(
CzModAsPriAddrCntrl *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzModAsPriAddrCntrl(param, mBuf)
CzModAsPriAddrCntrl *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzModAsPriAddrCntrl)

   CMCHKUNPK(SUnpkU32, &param->peerId, mBuf);
   CMCHKUNPK(cmUnpkCmNetAddr, &param->priDstAddr, mBuf);
   RETVALUE(ROK);
}









/***********************************************************
*
*     Func : cmPkCzCntrl
*
*
*     Desc : czCntrl
   @brief X2AP's Control information 
   @details This structure carries the control request information during
   CntrlReq from LM .
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzCntrl
(
CzCntrl *param,
Elmnt elmnt,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzCntrl(param,elmnt,mBuf)
CzCntrl *param;
Elmnt elmnt;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzCntrl)

   switch(elmnt) 
   {
      case STASSOC:
         CMCHKPK(cmPkCzModAsPriAddrCntrl, &param->u.modPriAddrCntrl, mBuf);
         break;
      case STCZGEN:
         if (param->action != ASHUTDOWN)
         { 
            switch(param->subAction)
            {
#ifdef DEBUGP
               case SADBG:
                  CMCHKPK(cmPkCzDbgCntrl, &param->u.dbg, mBuf);
                  break;
#endif /* DEBUG */
               case SAUSTA:
                  break;
#ifdef SS_DIAG  
               case SALOG:
                  CMCHKPK(SPkU32, param->u.logMask, mBuf);
                  break;
#endif
               default:
                   break;
            } 
         }
         break;
      case STCZSCTSAP:
         {
            switch (param->subAction)
            {
               case SATRC:
                  CMCHKPK(cmPkCzLSapTrcCntrl, &param->u.lSapTrc, mBuf);
                  break;
               case SAELMNT:
                  CMCHKPK(cmPkCzSapCntrl, &param->u.sap, mBuf);
                  break;
               default:
                  break;
            }
         }
         break;
      case STCZPEER:
         {    
            switch (param->subAction)
            {
               case SATRC:
                  CMCHKPK(cmPkCzPNodeTrcCntrl, &param->u.pNodeTrc, mBuf);
                  break;
               case SAELMNT:
                  CMCHKPK(cmPkCzPeerCntrl, &param->u.peer, mBuf);
                  break;
               default:
                  break;
            }
         } 
          break;
      case STTPTSRV:
         CMCHKPK(cmPkCzEndPtCntrl, &param->u.endPtCntrl, mBuf);
         break;
      case STCZCZTSAP:
         CMCHKPK(cmPkCzSapCntrl, &param->u.sap, mBuf);
         break;
      default :
          break;
   }

   CMCHKPK(cmPkAction, param->subAction, mBuf);
   CMCHKPK(cmPkAction, param->action, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzCntrl
*
*
*     Desc : czCntrl
   @brief X2AP's Control information 
   @details This structure carries the control request information during
   CntrlReq from LM .
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzCntrl
(
CzCntrl *param,
Elmnt elmnt,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzCntrl(param, elmnt,mBuf)
CzCntrl *param;
Elmnt elmnt;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzCntrl)

   CMCHKUNPK(cmUnpkAction, &param->action, mBuf);
   CMCHKUNPK(cmUnpkAction, &param->subAction, mBuf);

   switch(elmnt) 
   {
      case STCZCZTSAP:
         CMCHKUNPK(cmUnpkCzSapCntrl, &param->u.sap, mBuf);
         break;
      case STTPTSRV:
         CMCHKUNPK(cmUnpkCzEndPtCntrl, &param->u.endPtCntrl, mBuf);
         break;
      case STCZPEER:
         {    
            switch (param->subAction)
            {
               case SAELMNT:
                  CMCHKUNPK(cmUnpkCzPeerCntrl, &param->u.peer, mBuf);
                  break;
               case SATRC:
                  CMCHKUNPK(cmUnpkCzPNodeTrcCntrl, &param->u.pNodeTrc, mBuf);
                  break;
               default:
               break;
            }
         } 
          break;
        
      case STCZSCTSAP:
          {
             switch (param->subAction)
             {
                case SAELMNT:
                   CMCHKUNPK(cmUnpkCzSapCntrl, &param->u.sap, mBuf);
                   break;
                case SATRC:
                    CMCHKUNPK(cmUnpkCzLSapTrcCntrl, &param->u.lSapTrc, mBuf);
                   break;
                default:
               break;
             }
          }
       break;
      case STCZGEN:
       {
         if (param->action != ASHUTDOWN)
         { 
            switch(param->subAction)
            {  
#ifdef SS_DIAG 
               case SALOG:
                  CMCHKUNPK(SUnpkU32,  &param->u.logMask, mBuf);
#endif
               case SAUSTA:
                  break;  
#ifdef DEBUGP
               case SADBG:
                  CMCHKUNPK(cmUnpkCzDbgCntrl, &param->u.dbg, mBuf);
                  break;
#endif /* DEBUG */
               default:
               break;
            } 
         }
       }
         break;
      case STASSOC:
         CMCHKUNPK(cmUnpkCzModAsPriAddrCntrl, &param->u.modPriAddrCntrl, mBuf);
         break;
      default :
               break;
   }

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCzGenSta
*
*
*     Desc : czGenSta
   @brief X2AP General statistical information
   @details This structure carries the general statistics for X2AP.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzGenSta
(
CzGenSta *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzGenSta(param, mBuf)
CzGenSta *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzGenSta)

   CMCHKPK(SPkU16, param->timeToWait, mBuf);
   CMCHKPK(SPkU16, param->tX2RELOCOverall, mBuf);
   CMCHKPK(SPkU16, param->tRELOCprep, mBuf);
   CMCHKPK(SPkS32, param->nmbActvPeerConn, mBuf);
   CMCHKPK(SPkU32, param->memAlloc, mBuf);
   CMCHKPK(SPkU32, param->memSize, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzGenSta
*
*
*     Desc : czGenSta
   @brief X2AP General statistical information
   @details This structure carries the general statistics for X2AP.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzGenSta
(
CzGenSta *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzGenSta(param, mBuf)
CzGenSta *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzGenSta)

   CMCHKUNPK(SUnpkU32, &param->memSize, mBuf);
   CMCHKUNPK(SUnpkU32, &param->memAlloc, mBuf);
   CMCHKUNPK(SUnpkS32, &param->nmbActvPeerConn, mBuf);
   CMCHKUNPK(SUnpkU16, &param->tRELOCprep, mBuf);
   CMCHKUNPK(SUnpkU16, &param->tX2RELOCOverall, mBuf);
   CMCHKUNPK(SUnpkU16, &param->timeToWait, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCzSSapSta
*
*
*     Desc : czSSapSta
   @brief X2AP SAP statistical information
   @details This structure carries a SAP status information for X2AP.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzSSapSta
(
CzSSapSta *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzSSapSta(param, mBuf)
CzSSapSta *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzSSapSta)

   CMCHKPK(SPkU8, param->status, mBuf);
   CMCHKPK(SPkS16, param->sSapId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzSSapSta
*
*
*     Desc : czSSapSta
   @brief X2AP SAP statistical information
   @details This structure carries a SAP status information for X2AP.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzSSapSta
(
CzSSapSta *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzSSapSta(param, mBuf)
CzSSapSta *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzSSapSta)

   CMCHKUNPK(SUnpkS16, &param->sSapId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->status, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCzTSapSta
*
*
*     Desc : czTSapSta
   @brief Statistical information of a Lower SAP in X2AP
   @details This structure carries the SCTP status information.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzTSapSta
(
CzTSapSta *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzTSapSta(param, mBuf)
CzTSapSta *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzTSapSta)

   CMCHKPK(SPkU8, param->status, mBuf);
   CMCHKPK(SPkS16, param->tSapId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzTSapSta
*
*
*     Desc : czTSapSta
   @brief Statistical information of a Lower SAP in X2AP
   @details This structure carries the SCTP status information.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzTSapSta
(
CzTSapSta *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzTSapSta(param, mBuf)
CzTSapSta *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzTSapSta)

   CMCHKUNPK(SUnpkS16, &param->tSapId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->status, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCzPeerStaInfo
*
*
*     Desc : czPeerStaInfo
   @brief Statistical information of a peer 
   @details This structure carries the peer status information.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzPeerStaInfo
(
CzPeerStaInfo *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzPeerStaInfo(param, mBuf)
CzPeerStaInfo *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzPeerStaInfo)

   CMCHKPK(SPkU32, param->peerENbId, mBuf);
   CMCHKPK(SPkU32, param->spAssocId, mBuf);
   CMCHKPK(SPkU32, param->suAssocId, mBuf);
   CMCHKPK(SPkS16, param->sapId, mBuf);
   CMCHKPK(SPkU32, param->peerId, mBuf);
   CMCHKPK(SPkU8, param->tsapState, mBuf);
   CMCHKPK(SPkU8, param->assocState, mBuf);
   CMCHKPK(SPkU8, param->peerState, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzPeerStaInfo
*
*
*     Desc : czPeerStaInfo
   @brief Statistical information of a peer 
   @details This structure carries the peer status information.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzPeerStaInfo
(
CzPeerStaInfo *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzPeerStaInfo(param, mBuf)
CzPeerStaInfo *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzPeerStaInfo)

   CMCHKUNPK(SUnpkU8, &param->peerState, mBuf);
   CMCHKUNPK(SUnpkU8, &param->assocState, mBuf);
   CMCHKUNPK(SUnpkU8, &param->tsapState, mBuf);
   CMCHKUNPK(SUnpkU32, &param->peerId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->sapId, mBuf);
   CMCHKUNPK(SUnpkU32, &param->suAssocId, mBuf);
   CMCHKUNPK(SUnpkU32, &param->spAssocId, mBuf);
   CMCHKUNPK(SUnpkU32, &param->peerENbId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCzPeerSta
*
*
*     Desc : czPeerSta
   @brief Statistical information of peers 
   @details This structure carries list of the peer for which status information
   is requested.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzPeerSta
(
CzPeerSta *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzPeerSta(param, mBuf)
CzPeerSta *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzPeerSta)

   CMCHKPK(cmPkCzPeerStaInfo, param->peerStaInfo, mBuf);
   CMCHKPK(SPkU32, param->nmbPeer, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzPeerSta
*
*
*     Desc : czPeerSta
   @brief Statistical information of peers 
   @details This structure carries list of the peer for which status information
   is requested.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzPeerSta
(
Pst *pst, /*lcz_c_001.main_3: Added pst argument*/
CzPeerSta *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzPeerSta(pst,param, mBuf)
Pst *pst;/*lcz_c_001.main_3: Added pst argument*/
CzPeerSta *param;
Buffer *mBuf;
#endif /* ANSI */
{
   Cntr cnt; /* lcz_c_001.main_2 : X2AP 3.1 : fix for existing testcase */

   TRC3(cmUnpkCzPeerSta)

   CMCHKUNPK(SUnpkU32, &param->nmbPeer, mBuf);
   /* lcz_c_001.main_2 : X2AP 3.1 : fix for existing testcase*/
   if (param->nmbPeer)
   {
        /*lcz_c_001.main_3: Replaced CZ_ALLOC with SGetSBuf*/      
       if ((SGetSBuf(pst->region,pst->pool,(Data **)&(param->peerStaInfo),(sizeof(CzPeerSta)
          * param->nmbPeer))) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               (S8*)__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELCZ067, (ErrVal)0, (S8*)"Packing failed");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
                                             
      cmMemset( (U8* )param->peerStaInfo, 0,
                 sizeof(CzPeerSta) * param->nmbPeer);

      for (cnt = 0; cnt <  (S32)param->nmbPeer; cnt++)
      {
         CMCHKUNPK(cmUnpkCzPeerStaInfo, &param->peerStaInfo[cnt], mBuf);
      }
   }

   RETVALUE(ROK);
}







/***********************************************************
*
*     Func : cmPkCzSsta
*
*
*     Desc : czSsta
   @brief X2AP's solicited statistical Information 
   @details This structure carries the status information when layer manager
   requests for StaReq.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzSsta
(
CzSsta *param,
Elmnt elmnt,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzSsta(param, elmnt, mBuf)
CzSsta *param;
Elmnt elmnt;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzSsta)

      switch(elmnt) {
      case STCZPEER:
         CMCHKPK(cmPkCzPeerSta, &param->s.peerSta, mBuf);
         break;
      case STCZCZTSAP:
         CMCHKPK(cmPkCzTSapSta, &param->s.tSapSta, mBuf);
         break;
      case STCZSCTSAP:
         CMCHKPK(cmPkCzSSapSta, &param->s.sSapSta, mBuf);
         break;
      case STCZGEN:
         CMCHKPK(cmPkCzGenSta, &param->s.genSta, mBuf);
         break;
      case STCZSID:
         CMCHKPK(cmPkSystemId, &param->s.sysId, mBuf);
         SPutSBuf(0, 0, (Data *)param->s.sysId.ptNmb, LCZ_MAX_PT_NUM_SIZE);
         break;
      default :
         break;
   }

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzSsta
*
*
*     Desc : czSsta
   @brief X2AP's solicited statistical Information 
   @details This structure carries the status information when layer manager
   requests for StaReq.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzSsta
(
CzSsta *param,
Elmnt elmnt,
Buffer *mBuf,
Pst    *pst/*lcz_c_001.main_3: Added pst argument*/
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzSsta(param, elmnt,mBuf,pst)
CzSsta *param;
Elmnt elmnt;
Buffer *mBuf;
Pst   *pst;/*lcz_c_001.main_3: Added pst argument*/
#endif /* ANSI */
{

   TRC3(cmUnpkCzSsta)

      switch(elmnt) {
      case STCZSID:
         SGetSBuf(0, 0, (Data **)&param->s.sysId.ptNmb, LCZ_MAX_PT_NUM_SIZE);
         CMCHKUNPK(cmUnpkSystemId, &param->s.sysId, mBuf);
         break;
      case STCZGEN:
         CMCHKUNPK(cmUnpkCzGenSta, &param->s.genSta, mBuf);
         break;
      case STCZCZTSAP:
         CMCHKUNPK(cmUnpkCzSSapSta, &param->s.sSapSta, mBuf);
         break;
      case STCZSCTSAP:
         CMCHKUNPK(cmUnpkCzTSapSta, &param->s.tSapSta, mBuf);
         break;
      case STCZPEER:
          /*lcz_c_001.main_3: Replaced CMCHKUNPK with CMCHKUNPKVERLOG*/
          CMCHKUNPKVERLOG(cmUnpkCzPeerSta, &param->s.peerSta, mBuf,0,pst);
         break;
      default :
          break;
   }

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCzCntr
*
*
*     Desc : czCntr
   @brief Structure for holding the counters for transmitted/recvied mesages at
   X2AP
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzCntr
(
CzCntr *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzCntr(param, mBuf)
CzCntr *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzCntr)

   CMCHKPK(SPkU32, param->errRx, mBuf);
   CMCHKPK(SPkU32, param->errTx, mBuf);
   CMCHKPK(SPkU32, param->rx, mBuf);
   CMCHKPK(SPkU32, param->tx, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzCntr
*
*
*     Desc : czCntr
   @brief Structure for holding the counters for transmitted/recvied mesages at
   X2AP
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzCntr
(
CzCntr *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzCntr(param, mBuf)
CzCntr *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzCntr)

   CMCHKUNPK(SUnpkU32, &param->tx, mBuf);
   CMCHKUNPK(SUnpkU32, &param->rx, mBuf);
   CMCHKUNPK(SUnpkU32, &param->errTx, mBuf);
   CMCHKUNPK(SUnpkU32, &param->errRx, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCzPduSts
*
*
*     Desc : czPduSts
   @brief PDU statistics counter
   @details This structure describes all the types procedures
   transmitted/recvied  at X2AP.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzPduSts
(
CzPduSts *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzPduSts(param, mBuf)
CzPduSts *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzPduSts)

    /* lcz_c_001.main_2 : X2AP 3.1 : new messages */
   CMCHKPK(cmPkCzCntr, &param->cellActvFail, mBuf);
   CMCHKPK(cmPkCzCntr, &param->cellActvRes, mBuf);
   CMCHKPK(cmPkCzCntr, &param->cellActvReq, mBuf);
   CMCHKPK(cmPkCzCntr, &param->hoReport, mBuf);
   CMCHKPK(cmPkCzCntr, &param->rlfIndication, mBuf);
   CMCHKPK(cmPkCzCntr, &param->mobChangeFail, mBuf);
   CMCHKPK(cmPkCzCntr, &param->mobChangeAck, mBuf);
   CMCHKPK(cmPkCzCntr, &param->mobChangeReq, mBuf);
   CMCHKPK(cmPkCzCntr, &param->resStatusUpd, mBuf);
   CMCHKPK(cmPkCzCntr, &param->resStatusFail, mBuf);
   CMCHKPK(cmPkCzCntr, &param->resStatusResp, mBuf);
   CMCHKPK(cmPkCzCntr, &param->resStatusRqst, mBuf);
   CMCHKPK(cmPkCzCntr, &param->eNBCfgUpdFail, mBuf);
   CMCHKPK(cmPkCzCntr, &param->eNBCfgUpdAck, mBuf);
   CMCHKPK(cmPkCzCntr, &param->eNBCfgUpdRqst, mBuf);
   CMCHKPK(cmPkCzCntr, &param->resetResp, mBuf);
   CMCHKPK(cmPkCzCntr, &param->resetRqst, mBuf);
   CMCHKPK(cmPkCzCntr, &param->x2SetupFail, mBuf);
   CMCHKPK(cmPkCzCntr, &param->x2SetupResp, mBuf);
   CMCHKPK(cmPkCzCntr, &param->x2SetupRqst, mBuf);
   CMCHKPK(cmPkCzCntr, &param->errInd, mBuf);
   CMCHKPK(cmPkCzCntr, &param->loadInform, mBuf);
   CMCHKPK(cmPkCzCntr, &param->ueCntxtRls, mBuf);
   CMCHKPK(cmPkCzCntr, &param->hovrCancel, mBuf);
   CMCHKPK(cmPkCzCntr, &param->sNStatusTfr, mBuf);
   CMCHKPK(cmPkCzCntr, &param->hovrPrepFail, mBuf);
   CMCHKPK(cmPkCzCntr, &param->hovrReqAck, mBuf);
   CMCHKPK(cmPkCzCntr, &param->hovrRqst, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzPduSts
*
*
*     Desc : czPduSts
   @brief PDU statistics counter
   @details This structure describes all the types procedures
   transmitted/recvied  at X2AP.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzPduSts
(
CzPduSts *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzPduSts(param, mBuf)
CzPduSts *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzPduSts)

   CMCHKUNPK(cmUnpkCzCntr, &param->hovrRqst, mBuf);
   CMCHKUNPK(cmUnpkCzCntr, &param->hovrReqAck, mBuf);
   CMCHKUNPK(cmUnpkCzCntr, &param->hovrPrepFail, mBuf);
   CMCHKUNPK(cmUnpkCzCntr, &param->sNStatusTfr, mBuf);
   CMCHKUNPK(cmUnpkCzCntr, &param->hovrCancel, mBuf);
   CMCHKUNPK(cmUnpkCzCntr, &param->ueCntxtRls, mBuf);
   CMCHKUNPK(cmUnpkCzCntr, &param->loadInform, mBuf);
   CMCHKUNPK(cmUnpkCzCntr, &param->errInd, mBuf);
   CMCHKUNPK(cmUnpkCzCntr, &param->x2SetupRqst, mBuf);
   CMCHKUNPK(cmUnpkCzCntr, &param->x2SetupResp, mBuf);
   CMCHKUNPK(cmUnpkCzCntr, &param->x2SetupFail, mBuf);
   CMCHKUNPK(cmUnpkCzCntr, &param->resetRqst, mBuf);
   CMCHKUNPK(cmUnpkCzCntr, &param->resetResp, mBuf);
   CMCHKUNPK(cmUnpkCzCntr, &param->eNBCfgUpdRqst, mBuf);
   CMCHKUNPK(cmUnpkCzCntr, &param->eNBCfgUpdAck, mBuf);
   CMCHKUNPK(cmUnpkCzCntr, &param->eNBCfgUpdFail, mBuf);
   CMCHKUNPK(cmUnpkCzCntr, &param->resStatusRqst, mBuf);
   CMCHKUNPK(cmUnpkCzCntr, &param->resStatusResp, mBuf);
   CMCHKUNPK(cmUnpkCzCntr, &param->resStatusFail, mBuf);
   CMCHKUNPK(cmUnpkCzCntr, &param->resStatusUpd, mBuf);
   /* lcz_c_001.main_2 : X2AP 3.1 : new messages */
   CMCHKUNPK(cmUnpkCzCntr, &param->mobChangeReq, mBuf);
   CMCHKUNPK(cmUnpkCzCntr, &param->mobChangeAck, mBuf);
   CMCHKUNPK(cmUnpkCzCntr, &param->mobChangeFail, mBuf);
   CMCHKUNPK(cmUnpkCzCntr, &param->rlfIndication, mBuf);
   CMCHKUNPK(cmUnpkCzCntr, &param->hoReport, mBuf);
   CMCHKUNPK(cmUnpkCzCntr, &param->cellActvReq, mBuf);
   CMCHKUNPK(cmUnpkCzCntr, &param->cellActvRes, mBuf);
   CMCHKUNPK(cmUnpkCzCntr, &param->cellActvFail, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCzPeerSts
*
*
*     Desc : czPeerSts
   @brief Structure for holding the general Peer Node Statistics
   @details This structure describes different parameter of  peer node
   statistics like peerId, PDUs exchanged etc.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzPeerSts
(
CzPeerSts *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzPeerSts(param, mBuf)
CzPeerSts *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzPeerSts)

   CMCHKPK(SPkS32, param->nmbUnexpEvt, mBuf);
   CMCHKPK(SPkS32, param->nmbEncErr, mBuf);
   CMCHKPK(SPkS32, param->nmbDecErr, mBuf);
   CMCHKPK(cmPkCzPduSts, &param->pdu, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzPeerSts
*
*
*     Desc : czPeerSts
   @brief Structure for holding the general Peer Node Statistics
   @details This structure describes different parameter of  peer node
   statistics like peerId, PDUs exchanged etc.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzPeerSts
(
CzPeerSts *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzPeerSts(param, mBuf)
CzPeerSts *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzPeerSts)

   CMCHKUNPK(cmUnpkCzPduSts, &param->pdu, mBuf);
   CMCHKUNPK(SUnpkS32, &param->nmbDecErr, mBuf);
   CMCHKUNPK(SUnpkS32, &param->nmbEncErr, mBuf);
   CMCHKUNPK(SUnpkS32, &param->nmbUnexpEvt, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCzPeerNodeSts
*
*
*     Desc : czPeerNodeSts
   @brief Structure for holding the general Peer Node Statistics
   @details This structure describes different parameter of  peer node
   statistics like peerId, PDUs exchanged etc.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzPeerNodeSts
(
CzPeerNodeSts *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzPeerNodeSts(param, mBuf)
CzPeerNodeSts *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzPeerNodeSts)

   CMCHKPK(cmPkCzPeerSts, &param->cfm, mBuf);
   CMCHKPK(SPkU32, param->peerId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzPeerNodeSts
*
*
*     Desc : czPeerNodeSts
   @brief Structure for holding the general Peer Node Statistics
   @details This structure describes different parameter of  peer node
   statistics like peerId, PDUs exchanged etc.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzPeerNodeSts
(
CzPeerNodeSts *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzPeerNodeSts(param, mBuf)
CzPeerNodeSts *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzPeerNodeSts)

   CMCHKUNPK(SUnpkU32, &param->peerId, mBuf);
   CMCHKUNPK(cmUnpkCzPeerSts, &param->cfm, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCzGenSts
*
*
*     Desc : czGenSts
   @brief  General Statistics of the X2AP node
   @details This structure describes the general statistics related to X2AP.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzGenSts
(
CzGenSts *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzGenSts(param, mBuf)
CzGenSts *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzGenSts)

   CMCHKPK(cmPkCzPduSts, &param->pdu, mBuf);
   CMCHKPK(SPkU32, param->maxMemAlloc, mBuf);
   CMCHKPK(SPkS32, param->nmbEncErr, mBuf);
   CMCHKPK(SPkS32, param->nmbDecErr, mBuf);
   CMCHKPK(SPkS32, param->nmbPeerConnFail, mBuf);
   CMCHKPK(SPkS32, param->nmbPeerConnected, mBuf);
   CMCHKPK(SPkS32, param->maxNumPeerConn, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzGenSts
*
*
*     Desc : czGenSts
   @brief  General Statistics of the X2AP node
   @details This structure describes the general statistics related to X2AP.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzGenSts
(
CzGenSts *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzGenSts(param, mBuf)
CzGenSts *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzGenSts)

   CMCHKUNPK(SUnpkS32, &param->maxNumPeerConn, mBuf);
   CMCHKUNPK(SUnpkS32, &param->nmbPeerConnected, mBuf);
   CMCHKUNPK(SUnpkS32, &param->nmbPeerConnFail, mBuf);
   CMCHKUNPK(SUnpkS32, &param->nmbDecErr, mBuf);
   CMCHKUNPK(SUnpkS32, &param->nmbEncErr, mBuf);
   CMCHKUNPK(SUnpkU32, &param->maxMemAlloc, mBuf);
   CMCHKUNPK(cmUnpkCzPduSts, &param->pdu, mBuf);
   RETVALUE(ROK);
}









/***********************************************************
*
*     Func : cmPkCzSts
*
*
*     Desc : czSts
   @brief X2AP's statistical Information 
   @details This structure contains the general statistics and peer node
   statistics which layer manager can request using StsReq.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzSts
(
CzSts *param,
Elmnt elmnt,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzSts(param,elmnt, mBuf)
CzSts *param;
Elmnt elmnt;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzSts)
   switch(elmnt) {
      case STCZGEN:
         CMCHKPK(cmPkCzGenSts, &param->u.genSts, mBuf);
         break;
      case STCZPEER:
         CMCHKPK(cmPkCzPeerNodeSts, &param->u.nodeSts, mBuf);
         break;
      default :
          break;
   }

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzSts
*
*
*     Desc : czSts
   @brief X2AP's statistical Information 
   @details This structure contains the general statistics and peer node
   statistics which layer manager can request using StsReq.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzSts
(
CzSts *param,
Elmnt elmnt,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzSts(param,elmnt, mBuf)
CzSts *param;
Elmnt elmnt;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzSts)

  switch(elmnt) {
      case STCZPEER:
         CMCHKUNPK(cmUnpkCzPeerNodeSts, &param->u.nodeSts, mBuf);
         break;
      case STCZGEN:
         CMCHKUNPK(cmUnpkCzGenSts, &param->u.genSts, mBuf);
         break;
      default :
       break;
   }

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCzUeInfo
*
*
*     Desc : czUeInfo
   @brief X2AP alarm diagnostics information about the UE 
   @details This structure is filled by the X2AP while generating an alarm. X2AP
 fills the UeId and peerId , category , cause values along with the other information
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzUeInfo
(
CzUeInfo *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzUeInfo(param, mBuf)
CzUeInfo *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzUeInfo)

   CMCHKPK(SPkU16, param->ueId, mBuf);
   CMCHKPK(SPkU32, param->peerId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzUeInfo
*
*
*     Desc : czUeInfo
   @brief X2AP alarm diagnostics information about the UE 
   @details This structure is filled by the X2AP while generating an alarm. X2AP
 fills the UeId and peerId , category , cause values along with the other information
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzUeInfo
(
CzUeInfo *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzUeInfo(param, mBuf)
CzUeInfo *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzUeInfo)

   CMCHKUNPK(SUnpkU32, &param->peerId, mBuf);
   CMCHKUNPK(SUnpkU16, &param->ueId, mBuf);
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkCzPeerInfo
*
*
*     Desc : czPeerInfo
   @brief X2AP alarm diagnostics information about the Peer 
   @details This structure is filled by the X2AP while generating an alarm. X2AP
 fills the peerId , category , cause values along with the other information
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzPeerInfo
(
CzPeerInfo *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzPeerInfo(param, mBuf)
CzPeerInfo *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzPeerInfo)

   CMCHKPK(cmPkCmNetAddr, &param->dstNAddr, mBuf);
   CMCHKPK(SPkU32, param->peerId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzPeerInfo
*
*
*     Desc : czPeerInfo
   @brief X2AP alarm diagnostics information about the Peer 
   @details This structure is filled by the X2AP while generating an alarm. X2AP
 fills the  peerId , category , cause values along with the other information
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzPeerInfo
(
CzPeerInfo *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzPeerInfo(param, mBuf)
CzPeerInfo *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzPeerInfo)

   CMCHKUNPK(SUnpkU32, &param->peerId, mBuf);
   CMCHKUNPK(cmUnpkCmNetAddr, &param->dstNAddr, mBuf);
   RETVALUE(ROK);
}








/***********************************************************
*
*     Func : cmPkCzUstaDgn
*
*
*     Desc : czUstaDgn
   @brief X2AP alarm diagnostics information 
   @details This structure is filled by the X2AP while generating an alarm. X2AP
 fills the alarm type, category , cause values along with the other information
 like peerId, SAPId etc.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzUstaDgn
(
CzUstaDgn *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzUstaDgn(param, mBuf)
CzUstaDgn *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzUstaDgn)

      switch(param->alarmType) {
      case LCZ_USTA_DGNVAL_UE:
         CMCHKPK(cmPkCzUeInfo, &param->u.ueInfo, mBuf);
         break;
      case LCZ_USTA_DGNVAL_PEER:
         CMCHKPK(cmPkCzPeerInfo, &param->u.peerInfo, mBuf);
         break;
      case LCZ_USTA_DGNVAL_SAPID:
         CMCHKPK(SPkS16, param->u.sapId, mBuf);
         break;
      case LCZ_USTA_DGNVAL_MEM:
         CMCHKPK(cmPkMemoryId, &param->u.mem, mBuf);
         break;
      default :
         RETVALUE(RFAILED);
   }

   CMCHKPK(SPkU8, param->alarmType, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzUstaDgn
*
*
*     Desc : czUstaDgn
   @brief X2AP alarm diagnostics information 
   @details This structure is filled by the X2AP while generating an alarm. X2AP
 fills the alarm type, category , cause values along with the other information
 like peerId, SAPId etc.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzUstaDgn
(
CzUstaDgn *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzUstaDgn(param, mBuf)
CzUstaDgn *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzUstaDgn)

   CMCHKUNPK(SUnpkU8, &param->alarmType, mBuf);

   switch( param->alarmType) {
      case LCZ_USTA_DGNVAL_MEM:
         CMCHKUNPK(cmUnpkMemoryId, &param->u.mem, mBuf);
         break;
      case LCZ_USTA_DGNVAL_SAPID:
         CMCHKUNPK(SUnpkS16, &param->u.sapId, mBuf);
         break;
      case LCZ_USTA_DGNVAL_PEER:
         CMCHKUNPK(cmUnpkCzPeerInfo, &param->u.peerInfo, mBuf);
         break;
      case LCZ_USTA_DGNVAL_UE:
         CMCHKUNPK(cmUnpkCzUeInfo, &param->u.ueInfo, mBuf);
         break;
      default :
         RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCzUsta
*
*
*     Desc : czUsta
   @brief X2AP's Unsolicited status information 
   @details This structure is used for the alarm that X2AP generates towards
   Layer Manager.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzUsta
(
CzUsta *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzUsta(param, mBuf)
CzUsta *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzUsta)

   CMCHKPK(cmPkCzUstaDgn, &param->dgn, mBuf);
   CMCHKPK(cmPkCmAlarm, &param->alarm, mBuf);
   CMCHKPK(cmPkDateTime, &param->dt, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzUsta
*
*
*     Desc : czUsta
   @brief X2AP's Unsolicited status information 
   @details This structure is used for the alarm that X2AP generates towards
   Layer Manager.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzUsta
(
CzUsta *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzUsta(param, mBuf)
CzUsta *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzUsta)

   CMCHKUNPK(cmUnpkDateTime, &param->dt, mBuf);
   CMCHKUNPK(cmUnpkCmAlarm, &param->alarm, mBuf);
   CMCHKUNPK(cmUnpkCzUstaDgn, &param->dgn, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCzTrc
*
*
*     Desc : czTrc
   @brief X2AP's Trace Indication information 
   @details This structure is used for the Trace Indiation.It is passed in
   CzMiLczTrcInd primitive (as a part of cMngmt).X2AP uses trace indication to
   provide the stack manager with a trace of all data ( SCTP messages or UDP datagrams) 
   sent or received by a specific SIP entity. It can be enabled or disabled using a control request
 primitive. The length of the traced data can also be changed using the control request primitive.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzTrc
(
CzTrc *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkCzTrc(param, mBuf)
CzTrc *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmPkCzTrc)

   CMCHKPK(SPkU32, param->peerId, mBuf);
   CMCHKPK(SPkS16, param->sapId, mBuf);
   CMCHKPK(cmPkCzSctpAddr, &param->dstAddr, mBuf);
   CMCHKPK(cmPkCzSctpAddr, &param->srcAddr, mBuf);
   CMCHKPK(SPkU16, param->event, mBuf);
   CMCHKPK(cmPkDateTime, &param->dt, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzTrc
*
*
*     Desc : czTrc
   @brief X2AP's Trace Indication information 
   @details This structure is used for the Trace Indiation.It is passed in
   CzMiLczTrcInd primitive (as a part of cMngmt).X2AP uses trace indication to
   provide the stack manager with a trace of all data ( SCTP messages or UDP datagrams) 
   sent or received by a specific SIP entity. It can be enabled or disabled using a control request
 primitive. The length of the traced data can also be changed using the control request primitive.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzTrc
(
CzTrc *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzTrc(param, mBuf)
CzTrc *param;
Buffer *mBuf;
#endif /* ANSI */
{

   TRC3(cmUnpkCzTrc)

   CMCHKUNPK(cmUnpkDateTime, &param->dt, mBuf);
   CMCHKUNPK(SUnpkU16, &param->event, mBuf);
   CMCHKUNPK(cmUnpkCzSctpAddr, &param->srcAddr, mBuf);
   CMCHKUNPK(cmUnpkCzSctpAddr, &param->dstAddr, mBuf);
   CMCHKUNPK(SUnpkS16, &param->sapId, mBuf);
   CMCHKUNPK(SUnpkU32, &param->peerId, mBuf);
   RETVALUE(ROK);
}





/***********************************************************
*
*     Func : cmPkCzMngmt
*
*
*     Desc : czMngmt
   @brief X2AP's Configuration and Control Management Information 
   @details This structure represents the configuration, control, statistics and
 status structures. This is the main structure which is passed in all requests
 like config, control, status and statistics request from the layer manager 
 towards X2AP.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCzMngmt
(
CzMngmt *param,
S16 eventType,
Buffer *mBuf,
Pst * pst
)
#else /* ANSI */
PUBLIC S16 cmPkCzMngmt(param,eventType, mBuf, pst)
CzMngmt *param;
S16 eventType;
Buffer *mBuf;
Pst * pst;
#endif /* ANSI */
{
   S16 ret1 = ROK;

   TRC3(cmPkCzMngmt)

      switch(eventType) 
      {

         case EVTLCZTRCIND:
            ret1=cmPkCzTrc(&param->t.trc, mBuf);
            break;
         case  EVTLCZSTSREQ :
            ret1=cmPkCzSts(&param->t.sts, param->hdr.elmId.elmnt,mBuf);
            break;
         case  EVTLCZSTSCFM:
            ret1=cmPkCzSts(&param->t.sts, param->hdr.elmId.elmnt, mBuf);
            break;

         case  EVTLCZSTAIND :
            CMCHKPK(cmPkCzUsta ,&param->t.usta,mBuf);
            break;
         case  EVTLCZSTAREQ :
            ret1=cmPkCzSsta(&param->t.ssta, param->hdr.elmId.elmnt,mBuf);
            break;
          case  EVTLCZSTACFM :
            ret1=cmPkCzSsta(&param->t.ssta, param->hdr.elmId.elmnt,mBuf);
            break;

         case  EVTLCZCNTRLREQ :
            ret1=cmPkCzCntrl(&param->t.cntrl, param->hdr.elmId.elmnt,mBuf);
            break;
         case  EVTLCZCFGREQ :
            /* cz001.301 : Added one more input varaible PST structure
             * to the function cmPkCzMngmt */
            ret1=cmPkCzCfg(&param->t.cfg, param->hdr.elmId.elmnt, mBuf, pst);
            break;
         default :
            break;
      }

    if (ret1 != ROK)
    {
      RETVALUE(ret1);
    }
   if( ( eventType != EVTLCZSTAIND ) &&
        ( eventType != EVTLCZTRCIND ) &&
        ( eventType != EVTLCZCFGREQ ) &&
        ( eventType != EVTLCZSTAREQ ) &&
        ( eventType != EVTLCZSTSREQ ) &&
        ( eventType != EVTLCZCNTRLREQ ))
    {

   CMCHKPK(cmPkCmStatus, &param->cfm, mBuf);
    }
   CMCHKPK(cmPkHeader, &param->hdr, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCzMngmt
*
*
*     Desc : czMngmt
   @brief X2AP's Configuration and Control Management Information 
   @details This structure represents the configuration, control, statistics and
 status structures. This is the main structure which is passed in all requests
 like config, control, status and statistics request from the layer manager 
 towards X2AP.
*
*
*     Ret  : S16
*
*     Notes: None
*
*     File  : lcz.c 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCzMngmt
(
CzMngmt *param,
S16  eventType,
Buffer *mBuf,/*lcz_c_001.main_3: Added pst argument*/
Pst    *pst
)
#else /* ANSI */
PUBLIC S16 cmUnpkCzMngmt(param, eventType, mBuf,pst)
CzMngmt *param;
S16   eventType;
Buffer *mBuf;
Pst    *pst;/*lcz_c_001.main_3: Added pst argument*/
#endif /* ANSI */
{
   S16 ret1 = ROK;

   TRC3(cmUnpkCzMngmt)

   CMCHKUNPK(cmUnpkHeader, &param->hdr, mBuf);
   if( ( eventType != EVTLCZSTAIND ) &&
        ( eventType != EVTLCZTRCIND ) &&
        ( eventType != EVTLCZCFGREQ ) &&
        ( eventType != EVTLCZSTAREQ ) &&
        ( eventType != EVTLCZSTSREQ ) &&
        ( eventType != EVTLCZCNTRLREQ ))
    {

   CMCHKUNPK(cmUnpkCmStatus, &param->cfm, mBuf);
    }
   switch(eventType) {
         case  EVTLCZCFGREQ :
          /*lcz_c_001.main_3: Passed pst in czUnpkCzCfg*/  
         ret1=cmUnpkCzCfg(&param->t.cfg,param->hdr.elmId.elmnt, mBuf,pst);
         break;
         case  EVTLCZCNTRLREQ :
         ret1=cmUnpkCzCntrl(&param->t.cntrl,param->hdr.elmId.elmnt, mBuf);
         break;
         case  EVTLCZSTACFM :
         /*lcz_c_001.main_3: Passed pst cmUnpkCzSsta*/       
         ret1=cmUnpkCzSsta(&param->t.ssta,param->hdr.elmId.elmnt, mBuf,pst);
         break;
         case  EVTLCZSTAREQ :
         /*lcz_c_001.main_3: Passed  pst cmUnpkCzSsta*/
         ret1=cmUnpkCzSsta(&param->t.ssta,param->hdr.elmId.elmnt, mBuf,pst);
         break;
      case EVTLCZSTAIND:
         CMCHKUNPK(cmUnpkCzUsta,&param->t.usta, mBuf);
         break;
      case EVTLCZSTSCFM:
         ret1=cmUnpkCzSts(&param->t.sts,param->hdr.elmId.elmnt, mBuf);
         break;
      case EVTLCZSTSREQ:
         ret1=cmUnpkCzSts(&param->t.sts,param->hdr.elmId.elmnt, mBuf);
         break;
      case EVTLCZTRCIND:
         ret1=cmUnpkCzTrc(&param->t.trc, mBuf);
         break;
      default :
         break;
   }

    if (ret1 != ROK)
    {
      RETVALUE(ret1);
    }

   RETVALUE(ROK);
}


#endif /* (defined(LCLCZ) || defined(LWLCLCZ)) */
#ifdef __cplusplus
} /* end of EXTERN "C" */

#endif /* end of __cplusplus */
/*********************************************************************

         End of file:     lcz.c@@/main/4 - Wed Feb 22 12:57:55 2012

**********************************************************************/

/**********************************************************************

**********************************************************************/

/********************************************************************

        Revision history:

**********************************************************************/

/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     sy              1. LTE-X2AP Initial Release.
/main/2      ---      lcz_c_001.main_1 mm              1. CR Fixes, Memory Leak fixes.
/main/3      ---      lcz_c_001.main_2  pt     1.Updated for release of X2AP 3.1.
/main/4      ---      lcz_c_001.main_3           sp    1.Replaced CZ_ALLOC with SGetSBuf() in cmUn
                                                 pkCzPeerLsCfg() and cmUnpkCzPeerSta().
                                               2. Added argument pst in czUnpkCzMngmt(),cmUnpkCz
                                                  PeerLstCfg(),cmUnpkCzCfg()and cmUnpkCzPeerSta()
$SID$        ---      lcz_c_001.main_4 akaranth 1.Added error scenario handler.                                                  
*********************************************************************91*/
