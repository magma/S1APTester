

/********************************************************************20**
  
        Name:     LTE-PDCP Layer 
    
        Type:     C source file
  
        Desc:     C Source code for common packing and unpacking functions
                  for PDCP Layer Manager Interfaces.  It contains the 
                  following function definitions

                     -- cmPkLpjCfgReq
                     -- cmPkLpjCntrlReq
                     -- cmPkLpjCntrlCfm 
                     -- cmPkLpjCfgCfm
                     -- cmPkLpjStaInd

                     -- cmUnpkLpjCfgReq 
                     -- cmUnpkLpjCntrlReq
                     -- cmUnpkLpjCntrlCfm
                     -- cmUnpkLpjCfgCfm 
                     -- cmUnpkLpjStaInd
 
        File:     lpj.c

        Sid:      lpj.c@@/main/2 - Fri Sep  2 19:15:01 2011
  
        Prg:      cp
  
*********************************************************************21*/
 
  
/* header include files (.h) */
  
#include "envopt.h"             /* environment options */
#include "envdep.h"             /* environment dependent */
#include "envind.h"             /* environment independent */

#include "gen.h"                /* general */
#include "ssi.h"                /* system services interface */
#include "cm_lte.h"                /* layer manager */
#include "lpj.h"                /* Layer manager */

/* header/extern include files (.x) */

#include "gen.x"                /* general */
#include "ssi.x"                /* system services interface */
#include "cm_lib.x"             /* common library header file */
#include "cm_lte.x"                /* layer manager */
#include "lpj.x"                /* layer manager */

#if (defined(LCLPJ) || defined(LWLCLPJ))

Txt ptPjNmb[LPJ_PART_NUM_STR_LEN];         /* Part number */

#ifdef __cplusplus
EXTERN "C" {
#endif /* __cplusplus */

#ifdef ANSI
PUBLIC S16 cmPkLpjCfgReq
(
Pst * pst,
PjMngmt * cfg
)
#else
PUBLIC S16 cmPkLpjCfgReq(pst, cfg)
Pst * pst;
PjMngmt * cfg;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLpjCfgReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELPJ001, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)cfg, sizeof(PjMngmt));
      RETVALUE(RFAILED);
   }
   if (pst->selector == LPJ_SEL_LC) {
      if (cmPkPjMngmt(cfg, LPJ_EVT_CFG_REQ, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELPJ002, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)cfg, sizeof(PjMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }

   pst->event = (Event) LPJ_EVT_CFG_REQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkLpjCfgReq
(
LpjCfgReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLpjCfgReq(func, pst, mBuf)
LpjCfgReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   PjMngmt cfg;
   
   TRC3(cmUnpkLpjCfgReq)

   if (pst->selector == LPJ_SEL_LC) 
      if (cmUnpkPjMngmt(&cfg, LPJ_EVT_CFG_REQ, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELPJ006, (ErrVal)0, "Unpacking failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, &cfg));
}

#ifdef ANSI
PUBLIC S16 cmPkLpjCfgCfm
(
Pst * pst,
PjMngmt * cfgCfm
)
#else
PUBLIC S16 cmPkLpjCfgCfm(pst, cfgCfm)
Pst * pst;
PjMngmt * cfgCfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLpjCfgCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELPJ007, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)cfgCfm, sizeof(PjMngmt));
      RETVALUE(RFAILED);
   }
   if (pst->selector == LPJ_SEL_LC) {
      if (cmPkPjMngmt(cfgCfm, LPJ_EVT_CFG_CFM, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELPJ008, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)cfgCfm, sizeof(PjMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }

   pst->event = (Event) LPJ_EVT_CFG_CFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkLpjCfgCfm
(
LpjCfgCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLpjCfgCfm(func, pst, mBuf)
LpjCfgCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   PjMngmt cfgCfm;
   
   TRC3(cmUnpkLpjCfgCfm)

   if (pst->selector == LPJ_SEL_LC) 
      if (cmUnpkPjMngmt(&cfgCfm, LPJ_EVT_CFG_CFM, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELPJ012, (ErrVal)0, "Unpacking failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, &cfgCfm));
}

#ifdef ANSI
PUBLIC S16 cmPkLpjCntrlReq
(
Pst * pst,
PjMngmt * cntl
)
#else
PUBLIC S16 cmPkLpjCntrlReq(pst, cntl)
Pst * pst;
PjMngmt * cntl;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLpjCntrlReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELPJ013, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)cntl, sizeof(PjMngmt));
      RETVALUE(RFAILED);
   }
   if (pst->selector == LPJ_SEL_LC) {
      if (cmPkPjMngmt(cntl, LPJ_EVT_CNTRL_REQ, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELPJ014, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)cntl, sizeof(PjMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }

   pst->event = (Event) LPJ_EVT_CNTRL_REQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkLpjCntrlReq
(
LpjCntrlReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLpjCntrlReq(func, pst, mBuf)
LpjCntrlReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   PjMngmt cntl;
   
   TRC3(cmUnpkLpjCntrlReq)

   if (pst->selector == LPJ_SEL_LC) 
      if (cmUnpkPjMngmt(&cntl, LPJ_EVT_CNTRL_REQ, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELPJ018, (ErrVal)0, "Unpacking failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, &cntl));
}

#ifdef ANSI
PUBLIC S16 cmPkLpjCntrlCfm
(
Pst * pst,
PjMngmt * cntlCfm
)
#else
PUBLIC S16 cmPkLpjCntrlCfm(pst, cntlCfm)
Pst * pst;
PjMngmt * cntlCfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLpjCntrlCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELPJ019, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)cntlCfm, sizeof(PjMngmt));
      RETVALUE(RFAILED);
   }
   if (pst->selector == LPJ_SEL_LC) {
      if (cmPkPjMngmt(cntlCfm, LPJ_EVT_CNTRL_CFM, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELPJ020, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)cntlCfm, sizeof(PjMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }

   pst->event = (Event) LPJ_EVT_CNTRL_CFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkLpjCntrlCfm
(
LpjCntrlCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLpjCntrlCfm(func, pst, mBuf)
LpjCntrlCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   PjMngmt cntlCfm;
   
   TRC3(cmUnpkLpjCntrlCfm)

   if (pst->selector == LPJ_SEL_LC) 
      if (cmUnpkPjMngmt(&cntlCfm, LPJ_EVT_CNTRL_CFM, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELPJ024, (ErrVal)0, "Unpacking failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, &cntlCfm));
}

#ifdef ANSI
PUBLIC S16 cmPkLpjStaInd
(
Pst * pst,
PjMngmt * staInd
)
#else
PUBLIC S16 cmPkLpjStaInd(pst, staInd)
Pst * pst;
PjMngmt * staInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLpjStaInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELPJ025, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)staInd, sizeof(PjMngmt));
      RETVALUE(RFAILED);
   }
   if (pst->selector == LPJ_SEL_LC) {
      if (cmPkPjMngmt(staInd, LPJ_EVT_STA_IND, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELPJ026, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)staInd, sizeof(PjMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }

   pst->event = (Event) LPJ_EVT_STA_IND;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkLpjStaInd
(
LpjStaInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLpjStaInd(func, pst, mBuf)
LpjStaInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   PjMngmt staInd;
   
   TRC3(cmUnpkLpjStaInd)

   if (pst->selector == LPJ_SEL_LC) 
      if (cmUnpkPjMngmt(&staInd, LPJ_EVT_STA_IND, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELPJ030, (ErrVal)0, "Unpacking failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, &staInd));
}

#ifdef ANSI
PUBLIC S16 cmPkLpjStaReq
(
Pst * pst,
PjMngmt * staReq
)
#else
PUBLIC S16 cmPkLpjStaReq(pst, staReq)
Pst * pst;
PjMngmt * staReq;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLpjStaReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELPJ031, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)staReq, sizeof(PjMngmt));
      RETVALUE(RFAILED);
   }
   if (pst->selector == LPJ_SEL_LC) {
      if (cmPkPjMngmt(staReq, LPJ_EVT_STA_REQ, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELPJ032, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)staReq, sizeof(PjMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }

   pst->event = (Event) LPJ_EVT_STA_REQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkLpjStaReq
(
LpjStaReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLpjStaReq(func, pst, mBuf)
LpjStaReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   PjMngmt staReq;
   
   TRC3(cmUnpkLpjStaReq)

   if (pst->selector == LPJ_SEL_LC) 
      if (cmUnpkPjMngmt(&staReq, LPJ_EVT_STA_REQ, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELPJ036, (ErrVal)0, "Unpacking failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, &staReq));
}

#ifdef ANSI
PUBLIC S16 cmPkLpjStaCfm
(
Pst * pst,
PjMngmt * staCfm
)
#else
PUBLIC S16 cmPkLpjStaCfm(pst, staCfm)
Pst * pst;
PjMngmt * staCfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLpjStaCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELPJ037, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)staCfm, sizeof(PjMngmt));
      RETVALUE(RFAILED);
   }
   if (pst->selector == LPJ_SEL_LC) {
      if (cmPkPjMngmt(staCfm, LPJ_EVT_STA_CFM, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELPJ038, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)staCfm, sizeof(PjMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }

   pst->event = (Event) LPJ_EVT_STA_CFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkLpjStaCfm
(
LpjStaCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLpjStaCfm(func, pst, mBuf)
LpjStaCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   PjMngmt staCfm;
   
   TRC3(cmUnpkLpjStaCfm)

   if (pst->selector == LPJ_SEL_LC) 
      if (cmUnpkPjMngmt(&staCfm, LPJ_EVT_STA_CFM, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELPJ042, (ErrVal)0, "Unpacking failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, &staCfm));
}

#ifdef ANSI
PUBLIC S16 cmPkLpjStsReq
(
Pst * pst,
Action actn,
PjMngmt * sts
)
#else
PUBLIC S16 cmPkLpjStsReq(pst, actn, sts)
Pst * pst;
Action actn;
PjMngmt * sts;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLpjStsReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELPJ043, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)sts, sizeof(PjMngmt));
      RETVALUE(RFAILED);
   }
   if (pst->selector == LPJ_SEL_LC) {
      if (cmPkPjMngmt(sts, LPJ_EVT_STS_REQ, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELPJ044, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)sts, sizeof(PjMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }

   if (cmPkAction(actn, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELPJ046, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)sts, sizeof(PjMngmt));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) LPJ_EVT_STS_REQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkLpjStsReq
(
LpjStsReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLpjStsReq(func, pst, mBuf)
LpjStsReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   Action actn;
   PjMngmt sts;
   
   TRC3(cmUnpkLpjStsReq)

   if (cmUnpkAction(&actn, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELPJ048, (ErrVal)0, "Unpacking failed");
#endif
      RETVALUE(RFAILED);
   }

   if (pst->selector == LPJ_SEL_LC) 
      if (cmUnpkPjMngmt(&sts, LPJ_EVT_STS_REQ, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELPJ050, (ErrVal)0, "Unpacking failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, actn, &sts));
}

#ifdef ANSI
PUBLIC S16 cmPkLpjStsCfm
(
Pst * pst,
Action actn,
PjMngmt * stsCfm
)
#else
PUBLIC S16 cmPkLpjStsCfm(pst, actn, stsCfm)
Pst * pst;
Action actn;
PjMngmt * stsCfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLpjStsCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELPJ051, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)stsCfm, sizeof(PjMngmt));
      RETVALUE(RFAILED);
   }
   if (pst->selector == LPJ_SEL_LC) {
      if (cmPkPjMngmt(stsCfm, LPJ_EVT_STS_CFM, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELPJ052, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)stsCfm, sizeof(PjMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }

   if (cmPkAction(actn, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELPJ054, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)stsCfm, sizeof(PjMngmt));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) LPJ_EVT_STS_CFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkLpjStsCfm
(
LpjStsCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLpjStsCfm(func, pst, mBuf)
LpjStsCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   Action actn;
   PjMngmt stsCfm;
   
   TRC3(cmUnpkLpjStsCfm)

   if (cmUnpkAction(&actn, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELPJ056, (ErrVal)0, "Unpacking failed");
#endif
      RETVALUE(RFAILED);
   }

   if (pst->selector == LPJ_SEL_LC) 
      if (cmUnpkPjMngmt(&stsCfm, LPJ_EVT_STS_CFM, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELPJ058, (ErrVal)0, "Unpacking failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, actn, &stsCfm));
}

#ifdef ANSI
PUBLIC S16 cmPkLpjTrcInd
(
Pst * pst,
PjMngmt * trc,
Buffer * trcBuf
)
#else
PUBLIC S16 cmPkLpjTrcInd(pst, trc, trcBuf)
Pst * pst;
PjMngmt * trc;
Buffer * trcBuf;
#endif
{
   Buffer *mBuf = NULLP;
   MsgLen msgLen = 0;
   TRC3(cmPkLpjTrcInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELPJ059, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)trc, sizeof(PjMngmt));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector == LPJ_SEL_LC) {
      if (SFndLenMsg(trcBuf, &msgLen) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELPJ060, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)trc, sizeof(PjMngmt));
         SPutMsg(trcBuf);
         RETVALUE(RFAILED);
      }
      if (SCatMsg(mBuf, trcBuf, M1M2) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELPJ061, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)trc, sizeof(PjMngmt));
         SPutMsg(trcBuf);
         RETVALUE(RFAILED);
      }
      SPutMsg(trcBuf);
      CMCHKPK(SPkS16, msgLen, mBuf);

   }

   if (pst->selector == LPJ_SEL_LC) {
      if (cmPkPjMngmt(trc, LPJ_EVT_TRC_IND, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELPJ063, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)trc, sizeof(PjMngmt));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }

   pst->event = (Event) LPJ_EVT_TRC_IND;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkLpjTrcInd
(
LpjTrcInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLpjTrcInd(func, pst, mBuf)
LpjTrcInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   PjMngmt trc;
   Buffer *trcBuf = NULLP;
   
   TRC3(cmUnpkLpjTrcInd)

   if (pst->selector == LPJ_SEL_LC) 
      if (cmUnpkPjMngmt(&trc, LPJ_EVT_TRC_IND, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELPJ067, (ErrVal)0, "Unpacking failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector == LPJ_SEL_LC) {
      MsgLen msgLen, totalMsgLen;
      CMCHKUNPK(cmUnpkMsgLen, &msgLen, mBuf);
      if (SFndLenMsg(mBuf, &totalMsgLen) != ROK)
         RETVALUE(RFAILED);
      if (SSegMsg(mBuf, totalMsgLen-msgLen, &trcBuf) != ROK)
         RETVALUE(RFAILED);
   }

   SPutMsg(mBuf);
   RETVALUE((*func)(pst, &trc, trcBuf));
}
/* lpj_c_001.main_1 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
#ifdef ANSI
PUBLIC S16 cmPkLpjL2MeasReq
(
Pst * pst,
PjL2MeasReqEvt *measReqEvt
)
#else
PUBLIC S16 cmPkLpjL2MeasReq(pst, measReqEvt)
Pst * pst;
PjL2MeasReqEvt *measReqEvt;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLpjL2MeasReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERRLPJ, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)measReqEvt, sizeof(PjL2MeasReqEvt));
      RETVALUE(RFAILED);
   }       
   if (cmPkPjL2MeasReqInfo(&measReqEvt->measReq, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ERRLPJ, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }
   if (SPkU16(measReqEvt->measPeriod, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERRLPJ, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkU32(measReqEvt->transId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERRLPJ, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) LPJ_EVT_L2MEAS_REQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmPkLpjL2MeasStopReq
(
Pst *pst,
U16 measType
)
#else
PUBLIC S16 cmPkLpjL2MeasStopReq(pst, measType)
Pst *pst;
U16 measType;
#endif
{
   Buffer *mBuf = NULLP;

   TRC3(cmPkLpjL2MeasStopReq)
 if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERRLPJ, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   CMCHKPK(SPkU16, measType, mBuf);
   pst->event = (Event) LPJ_EVT_L2MEAS_STOP_REQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmPkLpjL2MeasSendReq
(
Pst *pst,
U16  measType
)
#else
PUBLIC S16 cmPkLpjL2MeasSendReq(pst, measType)
Pst *pst;
U16 measType;
#endif
{
   Buffer *mBuf = NULLP;

   TRC3(cmPkLpjL2MeasSendReq)
 if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERRLPJ, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   CMCHKPK(SPkU16, measType, mBuf);
   pst->event = (Event) LPJ_EVT_L2MEAS_SEND_REQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmPkPjL2MeasReqInfo
(
PjL2MeasReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkPjL2MeasReqInfo(param, mBuf)
PjL2MeasReqInfo *param;
Buffer *mBuf;
#endif
{

   U16 i;
   TRC3(cmPkPjL2InpParams)

   for(i = 0; i < param->numQci; i++)
      CMCHKPK(SPkU8, param->qci[i], mBuf);
   CMCHKPK(SPkU8, param->numQci, mBuf);
   CMCHKPK(SPkU16, param->measType, mBuf);
   RETVALUE(ROK);
}

#if 0
#ifdef ANSI
PUBLIC S16 cmPkLpjL2MeasStopReq
(
Pst *pst,
U16  measType
)
#else
PUBLIC S16 cmPkLpjL2MeasStopReq(pst, measType)
Pst *pst;
U16  measType;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLpjL2MeasStopReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERRLPJ, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   CMCHKPK(SPkU16, measType, mBuf);
   pst->event = (Event) LPJ_EVT_L2MEAS_STOP_REQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmPkLpjL2MeasSendReq
(
Pst *pst,
U16  measType
)
#else
PUBLIC S16 cmPkLpjL2MeasSendReq(pst, measType)
Pst *pst;
U16  measType;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLpjL2MeasSendReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERRLPJ, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   CMCHKPK(SPkU16, measType, mBuf);
   pst->event = (Event) LPJ_EVT_L2MEAS_SEND_REQ;
   RETVALUE(SPstTsk(pst,mBuf));
}
#endif

#ifdef ANSI
PUBLIC S16 cmUnpkLpjL2MeasReq
(
LpjL2MeasReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLpjL2MeasReq(func, pst, mBuf)
LpjL2MeasReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   PjL2MeasReqEvt measReqEvt;
   
   TRC3(cmUnpkLpjL2MeasReq)

   cmMemset((U8 *)&measReqEvt, 0, sizeof(PjL2MeasReqEvt));

   if (SUnpkU32(&measReqEvt.transId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERRLPJ, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkU16(&measReqEvt.measPeriod, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERRLPJ, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmUnpkPjL2MeasReqInfo(&measReqEvt.measReq, mBuf) != ROK) {
         SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ERRLPJ, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, &measReqEvt));
}

#ifdef ANSI
PUBLIC S16 cmUnpkPjL2MeasReqInfo
(
PjL2MeasReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjL2MeasReqInfo(param, mBuf)
PjL2MeasReqInfo *param;
Buffer *mBuf;
#endif
{

   U16 i;
   TRC3(cmUnpkPjL2MeasReqInfo)

   CMCHKUNPK(SUnpkU16, &param->measType, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numQci, mBuf);
   for(i = 0; i < param->numQci; i++)
      CMCHKUNPK(SUnpkU8, &param->qci[i], mBuf);
   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 cmUnpkLpjL2MeasStopReq
(
LpjL2MeasStopReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLpjL2MeasStopReq(func, pst, mBuf)
LpjL2MeasStopReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   U16 measType
   TRC3(cmUnpkLpjL2MeasReq)

   CMCHKUNPK(SUnpkU16, &measType, mBuf);
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, measType));
}

#ifdef ANSI
PUBLIC S16 cmUnpkLpjL2MeasSendReq
(
LpjL2MeasSendReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLpjL2MeasSendReq(func, pst, mBuf)
LpjL2MeasSendReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   U16    measType;

   TRC3(cmUnpkLpjL2MeasSendReq)

   CMCHKUNPK(SUnpkU16, &measType, mBuf); 
    SPutMsg(mBuf);
   RETVALUE((*func)(pst, measType));
}

#ifdef ANSI
PUBLIC S16 cmPkLpjL2MeasCfm
(
Pst * pst,
PjL2MeasCfmEvt *measCfmEvt
)
#else
PUBLIC S16 cmPkLpjL2MeasCfm(pst, measCfmEvt)
Pst * pst;
PjL2MeasCfmEvt *measCfmEvt;
#endif
{
   Buffer *mBuf = NULLP;
   U16 i;
   TRC3(cmPkLpjL2MeasCfm)

      if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ERRLPJ, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
   if(measCfmEvt->measType & LPJ_L2CPU_PERCORE_STATS)
   {   
      for(i = 0; i < measCfmEvt->numCores; i++)
      {
         if (cmPkPjL2MeasCpuCfmInfo(&measCfmEvt->cmLteCpuInfo[i], mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ELPJ052, (ErrVal)0, "Packing failed");
#endif
            SPutMsg(mBuf);
            RETVALUE(RFAILED);
         }
      }
      if (SPkU16(measCfmEvt->numCores, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ERRLPJ, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(mBuf);        
         RETVALUE(RFAILED);
      }
   }
      for(i = 0; i < measCfmEvt->numQciCfm; i++)
      {
         if (cmPkPjL2MeasCfmInfo(&measCfmEvt->measCfm[i], mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ELPJ052, (ErrVal)0, "Packing failed");
#endif
            SPutMsg(mBuf);
            RETVALUE(RFAILED);
         }
      }
   if (SPkU16(measCfmEvt->numQciCfm, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERRLPJ, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if(measCfmEvt->measType & LPJ_L2MEM_PERPOOL_STATS)
   {
      /* Memory Confirmation for Memory Utilization */
      if (cmPkPjL2MeasMemoryCfmInfo(&measCfmEvt->memoryInfo, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELPJ052, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }

   CMCHKPK(SPkU16,  measCfmEvt->measType, mBuf);

   CMCHKPK(cmPkCmStatus, &measCfmEvt->status, mBuf);

   if (SPkU32(measCfmEvt->transId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELPJ052, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) LPJ_EVT_L2MEAS_CFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

#if 0
#ifdef ANSI
PUBLIC S16 cmUnpkLpjL2MeasStopReq
(
LpjL2MeasStopReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLpjL2MeasStopReq(func, pst, mBuf)
LpjL2MeasStopReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
  U16 measType;
  
  TRC3(cmUnpkLpjL2MeasStopReq)

  CMCHKUNPK(SUnpkU16,&measType, mBuf); 
  SPutMsg(mBuf);
  RETVALUE((*func)(pst, measType));
}

#ifdef ANSI
PUBLIC S16 cmUnpkLpjL2MeasSendReq
(
LpjL2MeasSendReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLpjL2MeasSendReq(func, pst, mBuf)
LpjL2MeasSendReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
  U16 measType;

  TRC3(cmUnpkLpjL2MeasSendReq)

  CMCHKUNPK(SUnpkU16,&measType, mBuf);       
  SPutMsg(mBuf);
  RETVALUE((*func)(pst, measType));
}
#endif

#ifdef ANSI
PUBLIC S16 cmPkPjL2MeasCfmInfo
(
PjL2MeasCfmInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkPjL2MeasCfmInfo(param, mBuf)
PjL2MeasCfmInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkPjL2MeasCfmInfo)

   CMCHKPK(SPkU32, param->ulCpBitRate, mBuf);/*Added for L2 meas*/
   CMCHKPK(SPkU32, param->dlCpBitRate, mBuf);
   CMCHKPK(SPkU32, param->ulBitRate, mBuf);
   CMCHKPK(SPkU32, param->dlBitRate, mBuf);
   CMCHKPK(SPkU32, param->ulLoss, mBuf);
   CMCHKPK(SPkU32, param->dlDisc, mBuf);
   CMCHKPK(SPkU32, param->dlDelay, mBuf);
   CMCHKPK(SPkU8,  param->qci, mBuf);

   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 cmPkPjL2MeasCpuCfmInfo
(
CmLteCpuUtilInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkPjL2MeasCpuCfmInfo(param, mBuf)
CmLteCpuUtilInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkPjL2MeasCpuCfmInfo)

   CMCHKPK(SPkU32, param->maxCpuUtil, mBuf);
   CMCHKPK(SPkU32, param->avgCpuUtil, mBuf);
   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 cmPkPjL2MeasMemoryCfmInfo
(
CmLteMemInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkPjL2MeasMemoryCfmInfo(param, mBuf)
CmLteMemInfo *param;
Buffer *mBuf;
#endif
{
   /*U8   numReg;
   U8   numPool;*/
   U8   idxReg;
   U8   idxPool;

   for(idxReg=0; idxReg < param->numRegions; idxReg++)
   {
      CMCHKPK(SPkU8,  param->regInfo[idxReg].regionType, mBuf);
      CMCHKPK(SPkU8,  param->regInfo[idxReg].regionId, mBuf);

      for(idxPool=0; idxPool < param->regInfo[idxReg].numPools; idxPool++)
      {
         CMCHKPK(SPkU32,  param->regInfo[idxReg].poolInfo[idxPool].totAvailable, mBuf);
         CMCHKPK(SPkU32,  param->regInfo[idxReg].poolInfo[idxPool].poolSize, mBuf);
         CMCHKPK(SPkU32,  param->regInfo[idxReg].poolInfo[idxPool].crntUsed, mBuf);
         CMCHKPK(SPkU32,  param->regInfo[idxReg].poolInfo[idxPool].maxUsed, mBuf);
      }
      CMCHKPK(SPkU8,  param->regInfo[idxReg].numPools, mBuf);
   }
   CMCHKPK(SPkU8,  param->numRegions, mBuf);

   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 cmUnpkPjL2MeasMemoryCfmInfo
(
CmLteMemInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjL2MeasMemoryCfmInfo(param, mBuf)
CmLteMemInfo *param;
Buffer *mBuf;
#endif
{
   U8   idxReg;
   U8   idxPool;

   CMCHKUNPK(SUnpkU8,  &param->numRegions, mBuf);
   for(idxReg = param->numRegions ; idxReg > 0; idxReg--)
   {

      CMCHKUNPK(SUnpkU8,  &param->regInfo[idxReg - 1].numPools, mBuf);
      for(idxPool = param->regInfo[idxReg - 1].numPools; idxPool > 0 ; idxPool--)
      {
         CMCHKUNPK(SUnpkU32,  &param->regInfo[idxReg - 1].poolInfo[idxPool - 1].maxUsed, mBuf);
         CMCHKUNPK(SUnpkU32,  &param->regInfo[idxReg - 1].poolInfo[idxPool - 1].crntUsed, mBuf);
         CMCHKUNPK(SUnpkU32,  &param->regInfo[idxReg - 1].poolInfo[idxPool - 1].poolSize, mBuf);
         CMCHKUNPK(SUnpkU32,  &param->regInfo[idxReg - 1].poolInfo[idxPool - 1].totAvailable, mBuf);
      }
      CMCHKUNPK(SUnpkU8,  &param->regInfo[idxReg - 1].regionId, mBuf);
      CMCHKUNPK(SUnpkU8,  &param->regInfo[idxReg - 1].regionType, mBuf);
   }
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmUnpkLpjL2MeasCfm
*
*
*     Desc : This function will unpack Layer measurement confirmation
*            structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : lpj.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkLpjL2MeasCfm
(
LpjL2MeasCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLpjL2MeasCfm(func, pst, mBuf)
LpjL2MeasCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   U16 i;
   PjL2MeasCfmEvt measCfmEvt;

   TRC3(cmUnpkLpjL2MeasCfm)


   if (SUnpkU32(&measCfmEvt.transId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERRLPJ, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   CMCHKUNPK(cmUnpkCmStatus, &measCfmEvt.status, mBuf);
   CMCHKUNPK(SUnpkU16,  &measCfmEvt.measType, mBuf);

   if(measCfmEvt.measType & LPJ_L2MEM_PERPOOL_STATS)
   {
      /* Memory Confirmation for Memory Utilization */
      if (cmUnpkPjL2MeasMemoryCfmInfo(&measCfmEvt.memoryInfo, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELPJ052, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (SUnpkU16(&measCfmEvt.numQciCfm, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELPJ021, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   for(i = 0; i < measCfmEvt.numQciCfm; i++)
   {
      if (cmUnpkPjL2MeasCfmInfo(&measCfmEvt.measCfm[i], mBuf) != ROK) {   
         SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELPJ023, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
   }
   if(measCfmEvt.measType & LPJ_L2CPU_PERCORE_STATS)
   {
      if (SUnpkU16(&measCfmEvt.numCores, mBuf) != ROK) 
      {
         SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELPJ021, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
      for(i = measCfmEvt.numCores; i > 0; i--)
      {
         if (cmUnpkPjL2MeasCpuCfmInfo(&measCfmEvt.cmLteCpuInfo[i-1], mBuf) != ROK) {
            SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ELPJ023, (ErrVal)0, "Packing failed");
#endif
            RETVALUE(RFAILED);
         }
      }
   }

   SPutMsg(mBuf);
   RETVALUE((*func)(pst, &measCfmEvt));
}

#ifdef ANSI
PUBLIC S16 cmUnpkPjL2MeasCfmInfo
(
PjL2MeasCfmInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjL2MeasCfmInfo(param, mBuf)
PjL2MeasCfmInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkPjL2MeasCfmInfo)

   CMCHKUNPK(SUnpkU8,  &param->qci, mBuf);
   CMCHKUNPK(SUnpkU32, &param->dlDelay, mBuf);
   CMCHKUNPK(SUnpkU32, &param->dlDisc, mBuf);
   CMCHKUNPK(SUnpkU32, &param->ulLoss, mBuf);
   CMCHKUNPK(SUnpkU32, &param->dlBitRate, mBuf);
   CMCHKUNPK(SUnpkU32, &param->ulBitRate, mBuf);
   CMCHKUNPK(SUnpkU32, &param->dlCpBitRate, mBuf);
   CMCHKUNPK(SUnpkU32, &param->ulCpBitRate, mBuf);

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmUnpkPjL2MeasCpuCfmInfo
(CmLteCpuUtilInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjL2MeasCpuCfmInfo(param, mBuf)
CmLteCpuUtilInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkPjL2MeasCpuCfmInfo)
   CMCHKUNPK(SUnpkU32, &param->avgCpuUtil, mBuf);
   CMCHKUNPK(SUnpkU32, &param->maxCpuUtil, mBuf);

   RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 cmPkLpjL2MeasStopCfm
(
Pst *pst,
U16  measType,
U8  status
)
#else
PUBLIC S16 cmPkLpjL2MeasStopCfm(pst, measType,status)
Pst *pst;
U16  measType;
U8  status
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLpjL2MeasStopCfm)
    if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERRLPJ, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }

   CMCHKPK(SPkU8, status, mBuf);
   CMCHKPK(SPkU16, measType, mBuf); 
   pst->event = (Event) LPJ_EVT_L2MEAS_STOP_CFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


#ifdef ANSI
PUBLIC S16 cmUnpkLpjL2MeasStopCfm
(
LpjL2MeasStopCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLpjL2MeasStopCfm(func, pst, mBuf)
LpjL2MeasStopCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   U16 measType;
   U8 status;

   TRC3(cmUnpkLpjL2MeasStopCfm)
   
   CMCHKUNPK(SUnpkU16, &measType, mBuf);
   CMCHKUNPK(SUnpkU8, &status, mBuf);
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, measType,status));
}

#endif /* LTE_L2_MEAS */

#if (defined(PJ_SEC_ASYNC) || defined (PJ_CMP_ASYNC))



/***********************************************************
*
*     Func : cmPkPjObdPst
*
*
*     Desc : PjOBPst
 *  Post Info for off-board entities
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkPjObdPst
(
PjObdPst *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkPjObdPst(param, mBuf)
PjObdPst *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkPjObdPst)

   CMCHKPK(cmPkPst, &param->secPst, mBuf);
   CMCHKPK(cmPkPst, &param->cmpPst, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkPjObdPst
*
*
*     Desc : PjOBPst
 *  Post Info for off-board entities
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkPjObdPst
(
PjObdPst *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjObdPst(param, mBuf)
PjObdPst *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkPjObdPst)

   CMCHKUNPK(cmUnpkPst, &param->cmpPst, mBuf);
   CMCHKUNPK(cmUnpkPst, &param->secPst, mBuf);
   RETVALUE(ROK);
}


#endif



/***********************************************************
*
*     Func : cmPkPjGenCfg
*
*
*     Desc :    General Configuration Structure.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkPjGenCfg
(
PjGenCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkPjGenCfg(param, mBuf)
PjGenCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkPjGenCfg)


#if (defined(PJ_SEC_ASYNC) || defined (PJ_CMP_ASYNC))
   CMCHKPK(cmPkPjObdPst, &param->obdPst, mBuf);
   CMCHKPK(SPkS32, param->obdWtTmrInt, mBuf);
   CMCHKPK(SPkS32, param->obdTmrInt, mBuf);

#endif
   CMCHKPK(SPkU32, param->maxUe, mBuf);
   CMCHKPK(SPkU8, param->nmbDlBins, mBuf);
   CMCHKPK(SPkU8, param->nmbUlBins, mBuf);
   CMCHKPK(SPkU8, param->maxUdxSaps, mBuf);
   CMCHKPK(SPkU8, param->maxKwuSaps, mBuf);
   CMCHKPK(SPkU8, param->maxPjuSaps, mBuf);
   CMCHKPK(SPkU8, param->mode, mBuf);
   CMCHKPK(SPkU32, param->timeRes, mBuf);
   CMCHKPK(cmPkPst, &param->lmPst,mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkPjGenCfg
*
*
*     Desc :    General Configuration Structure.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkPjGenCfg
(
PjGenCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjGenCfg(param, mBuf)
PjGenCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkPjGenCfg)

   CMCHKUNPK(cmUnpkPst, &param->lmPst,mBuf);
   CMCHKUNPK(SUnpkU32, &param->timeRes, mBuf);
   CMCHKUNPK(SUnpkU8, &param->mode, mBuf);
   CMCHKUNPK(SUnpkU8, &param->maxPjuSaps, mBuf);
   CMCHKUNPK(SUnpkU8, &param->maxKwuSaps, mBuf);
   CMCHKUNPK(SUnpkU8, &param->maxUdxSaps, mBuf);
   CMCHKUNPK(SUnpkU8, &param->nmbUlBins, mBuf);
   CMCHKUNPK(SUnpkU8, &param->nmbDlBins, mBuf);
   CMCHKUNPK(SUnpkU32, &param->maxUe, mBuf);

#if (defined(PJ_SEC_ASYNC) || defined (PJ_CMP_ASYNC))
   CMCHKUNPK(SUnpkS32, &param->obdTmrInt, mBuf);
   CMCHKUNPK(SUnpkS32, &param->obdWtTmrInt, mBuf);
   CMCHKUNPK(cmUnpkPjObdPst, &param->obdPst, mBuf);

#endif
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkPjSapCfg
*
*
*     Desc :    Sap Configuration Structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkPjSapCfg
(
PjSapCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkPjSapCfg(param, mBuf)
PjSapCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkPjSapCfg)

   CMCHKPK(SPkU8, param->route, mBuf);
   CMCHKPK(SPkU8, param->priority, mBuf);
   CMCHKPK(SPkU16, param->bndTmrIntvl, mBuf);
   CMCHKPK(SPkS16, param->sapId, mBuf);
   CMCHKPK(SPkU8, param->inst, mBuf);
   CMCHKPK(SPkU8, param->ent, mBuf);
   CMCHKPK(SPkU16, param->procId, mBuf);
   CMCHKPK(cmPkMemoryId, &param->mem, mBuf);
   CMCHKPK(SPkU8, param->selector, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkPjSapCfg
*
*
*     Desc :    Sap Configuration Structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkPjSapCfg
(
PjSapCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjSapCfg(param, mBuf)
PjSapCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkPjSapCfg)

   CMCHKUNPK(SUnpkU8, &param->selector, mBuf);
   CMCHKUNPK(cmUnpkMemoryId, &param->mem, mBuf);
   CMCHKUNPK(SUnpkU16, &param->procId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ent, mBuf);
   CMCHKUNPK(SUnpkU8, &param->inst, mBuf);
   CMCHKUNPK(SUnpkS16, &param->sapId, mBuf);
   CMCHKUNPK(SUnpkU16, &param->bndTmrIntvl, mBuf);
   CMCHKUNPK(SUnpkU8, &param->priority, mBuf);
   CMCHKUNPK(SUnpkU8, &param->route, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkPjCfg
*
*
*     Desc : 
*   Configuration Structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkPjCfg
(
PjMngmt *cfg,
Elmnt elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkPjCfg(cfg, elmnt, mBuf)
PjMngmt *cfg;
Elmnt elmnt;
Buffer *mBuf;
#endif
{

   TRC3(cmPkPjCfg)

      switch(elmnt) {
         case STCPJSAP:
         case STPJUSAP:
         case STKWUSAP:
         case STUDXSAP:
            CMCHKPK(cmPkPjSapCfg, &cfg->t.cfg.s.sap, mBuf);
            break;
         case STGEN:
            CMCHKPK(cmPkPjGenCfg, &cfg->t.cfg.s.gen, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkPjCfg
*
*
*     Desc : 
*   Configuration Structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkPjCfg
(
PjMngmt *cfg,
Elmnt elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjCfg(cfg, elmnt, mBuf)
PjMngmt *cfg;
Elmnt elmnt;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkPjCfg)

      switch(elmnt) {
         case STGEN:
            CMCHKUNPK(cmUnpkPjGenCfg, &cfg->t.cfg.s.gen, mBuf);
            break;
         case STCPJSAP:
         case STPJUSAP:
         case STKWUSAP:
         case STUDXSAP:
            CMCHKUNPK(cmUnpkPjSapCfg, &cfg->t.cfg.s.sap, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkPjGenSts
*
*
*     Desc : 
    General Statistics Structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkPjGenSts
(
PjGenSts *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkPjGenSts(param, mBuf)
PjGenSts *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkPjGenSts)

   CMCHKPK(SPkU32, param->numPktsRcvd, mBuf);
   CMCHKPK(SPkU32, param->numPktsFrwd, mBuf);
   CMCHKPK(SPkU32, param->numSdusDiscObdTmrExp, mBuf);
   CMCHKPK(SPkU32, param->numPdusDiscObdTmrExp, mBuf);
   CMCHKPK(SPkU32, param->numDeciphFails, mBuf);
   CMCHKPK(SPkU32, param->numCiphFails, mBuf);
   CMCHKPK(SPkU32, param->numIntgVrfFails, mBuf);
   CMCHKPK(SPkU32, param->numIntgPrtFails, mBuf);
   CMCHKPK(SPkU32, param->numDecmpFails, mBuf);
   CMCHKPK(SPkU32, param->numCmpFails, mBuf);
   CMCHKPK(SPkU32, param->numSdusDisc, mBuf);
   CMCHKPK(SPkU32, param->errorPdusRecv, mBuf);
   CMCHKPK(SPkU32, param->txPdus, mBuf);
   CMCHKPK(SPkU32, param->rxPdus, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkPjGenSts
*
*
*     Desc : 
    General Statistics Structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkPjGenSts
(
PjGenSts *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjGenSts(param, mBuf)
PjGenSts *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkPjGenSts)

   CMCHKUNPK(SUnpkU32, &param->rxPdus, mBuf);
   CMCHKUNPK(SUnpkU32, &param->txPdus, mBuf);
   CMCHKUNPK(SUnpkU32, &param->errorPdusRecv, mBuf);
   CMCHKUNPK(SUnpkU32, &param->numSdusDisc, mBuf);
   CMCHKUNPK(SUnpkU32, &param->numCmpFails, mBuf);
   CMCHKUNPK(SUnpkU32, &param->numDecmpFails, mBuf);
   CMCHKUNPK(SUnpkU32, &param->numIntgPrtFails, mBuf);
   CMCHKUNPK(SUnpkU32, &param->numIntgVrfFails, mBuf);
   CMCHKUNPK(SUnpkU32, &param->numCiphFails, mBuf);
   CMCHKUNPK(SUnpkU32, &param->numDeciphFails, mBuf);
   CMCHKUNPK(SUnpkU32, &param->numPdusDiscObdTmrExp, mBuf);
   CMCHKUNPK(SUnpkU32, &param->numSdusDiscObdTmrExp, mBuf);
   CMCHKUNPK(SUnpkU32, &param->numPktsFrwd, mBuf);
   CMCHKUNPK(SUnpkU32, &param->numPktsRcvd, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkPjPjuSts
*
*
*     Desc : 
    General Statistics Structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkPjPjuSts
(
PjPjuSts *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkPjPjuSts(param, mBuf)
PjPjuSts *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkPjPjuSts)

   CMCHKPK(SPkU32, param->txSdus, mBuf);
   CMCHKPK(SPkU32, param->rxSdus, mBuf);
   /* lpj_c_001.main_1 added missing packing */
   CMCHKPK(SPkS16, param->spId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkPjPjuSts
*
*
*     Desc : 
    General Statistics Structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkPjPjuSts
(
PjPjuSts *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjPjuSts(param, mBuf)
PjPjuSts *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkPjPjuSts)

   /* lpj_c_001.main_1 added missing unpacking */
   CMCHKUNPK(SUnpkS16, &param->spId, mBuf);
   CMCHKUNPK(SUnpkU32, &param->rxSdus, mBuf);
   CMCHKUNPK(SUnpkU32, &param->txSdus, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkPjSts
*
*
*     Desc : 
    Statistics Structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkPjSts
(
PjMngmt *sts,
Elmnt elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkPjSts(sts, elmnt, mBuf)
PjMngmt *sts;
Elmnt elmnt;
Buffer *mBuf;
#endif
{

   TRC3(cmPkPjSts)

      switch(elmnt) {
         case STPJUSAP:
            CMCHKPK(cmPkPjPjuSts, &sts->t.sts.s.pjuSap, mBuf);
            break;
         case STGEN:
            CMCHKPK(cmPkPjGenSts, &sts->t.sts.s.gen, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(cmPkDateTime, &sts->t.sts.dt, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkPjSts
*
*
*     Desc : 
    Statistics Structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkPjSts
(
PjMngmt *sts,
Elmnt elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjSts(sts, elmnt, mBuf)
PjMngmt *sts;
Elmnt elmnt;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkPjSts)

   CMCHKUNPK(cmUnpkDateTime, &sts->t.sts.dt, mBuf);
      switch(elmnt) {
         case STGEN:
            CMCHKUNPK(cmUnpkPjGenSts, &sts->t.sts.s.gen, mBuf);
            break;
         case STPJUSAP:
            CMCHKUNPK(cmUnpkPjPjuSts, &sts->t.sts.s.pjuSap, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkPjPjuSapSta
*
*
*     Desc : 
    PDCP Data plane Upper SAP Status Structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkPjPjuSapSta
(
PjPjuSapSta *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkPjPjuSapSta(param, mBuf)
PjPjuSapSta *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkPjPjuSapSta)

   CMCHKPK(SPkU8, param->state, mBuf);
   CMCHKPK(SPkS16, param->spId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkPjPjuSapSta
*
*
*     Desc : 
    PDCP Data plane Upper SAP Status Structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkPjPjuSapSta
(
PjPjuSapSta *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjPjuSapSta(param, mBuf)
PjPjuSapSta *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkPjPjuSapSta)

   CMCHKUNPK(SUnpkS16, &param->spId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->state, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkPjCpjSapSta
*
*
*     Desc : 
    PDCP Control plane SAP Status Structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkPjCpjSapSta
(
PjCpjSapSta *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkPjCpjSapSta(param, mBuf)
PjCpjSapSta *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkPjCpjSapSta)

   CMCHKPK(SPkU8, param->state, mBuf);
   CMCHKPK(SPkS16, param->spId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkPjCpjSapSta
*
*
*     Desc : 
    PDCP Control plane SAP Status Structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkPjCpjSapSta
(
PjCpjSapSta *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjCpjSapSta(param, mBuf)
PjCpjSapSta *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkPjCpjSapSta)

   CMCHKUNPK(SUnpkS16, &param->spId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->state, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkPjSSta
*
*
*     Desc : 
    Status Structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkPjSSta
(
PjMngmt *ssta,
Elmnt elmnt,
Event eventType,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkPjSSta(ssta, elmnt, eventType, mBuf)
PjMngmt *ssta;
Elmnt elmnt;
Event eventType;
Buffer *mBuf;
#endif
{

   TRC3(cmPkPjSSta)

      switch(elmnt) {
         case STPJUSAP:
            CMCHKPK(cmPkPjPjuSapSta, &ssta->t.ssta.s.pjuSap, mBuf);
            break;
         case STCPJSAP:
            CMCHKPK(cmPkPjCpjSapSta, &ssta->t.ssta.s.cpjSap, mBuf);
            break;
         case STSID:
            if(eventType == LPJ_EVT_STA_CFM)
            {
               CMCHKPK(cmPkSystemId, &ssta->t.ssta.s.sysId, mBuf);
            }
            break;
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(cmPkDateTime, &ssta->t.ssta.dt, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkPjSSta
*
*
*     Desc : 
    Status Structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkPjSSta
(
PjMngmt *ssta,
Elmnt elmnt,
Event eventType,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjSSta(ssta, elmnt, eventType, mBuf)
PjMngmt *ssta;
Elmnt elmnt;
Event eventType;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkPjSSta)

   CMCHKUNPK(cmUnpkDateTime, &ssta->t.ssta.dt, mBuf);
      switch(elmnt) {
         case STSID:
            if(eventType == LPJ_EVT_STA_CFM)
            {
               cmMemset((U8 *) ptPjNmb, (U8) 0, LPJ_PART_NUM_STR_LEN);
               ssta->t.ssta.s.sysId.ptNmb = ptPjNmb;
               CMCHKUNPK(cmUnpkSystemId, &ssta->t.ssta.s.sysId,mBuf);
            }
            break;
         case STCPJSAP:
            CMCHKUNPK(cmUnpkPjCpjSapSta, &ssta->t.ssta.s.cpjSap, mBuf);
            break;
         case STPJUSAP:
            CMCHKUNPK(cmUnpkPjPjuSapSta, &ssta->t.ssta.s.pjuSap, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkPjTrcCntrl
*
*
*     Desc : 
    Trace control structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkPjTrcCntrl
(
PjTrcCntrl *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkPjTrcCntrl(param, mBuf)
PjTrcCntrl *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkPjTrcCntrl)

   CMCHKPK(SPkS16, param->trcLen, mBuf);
   CMCHKPK(SPkU8, param->trcMask, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkPjTrcCntrl
*
*
*     Desc : 
    Trace control structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkPjTrcCntrl
(
PjTrcCntrl *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjTrcCntrl(param, mBuf)
PjTrcCntrl *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkPjTrcCntrl)

   CMCHKUNPK(SUnpkU8, &param->trcMask, mBuf);
   CMCHKUNPK(SUnpkS16, &param->trcLen, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkPjDbgCntrl
*
*
*     Desc : 
    debug control structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkPjDbgCntrl
(
PjDbgCntrl *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkPjDbgCntrl(param, mBuf)
PjDbgCntrl *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkPjDbgCntrl)

   CMCHKPK(SPkU32, param->dbgMask, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkPjDbgCntrl
*
*
*     Desc : 
    debug control structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkPjDbgCntrl
(
PjDbgCntrl *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjDbgCntrl(param, mBuf)
PjDbgCntrl *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkPjDbgCntrl)

   CMCHKUNPK(SUnpkU32, &param->dbgMask, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkPjCntrl
*
*
*     Desc : 
    Control Structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkPjCntrl
(
PjMngmt *cntrl,
Elmnt elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkPjCntrl(cntrl, elmnt, mBuf)
PjMngmt *cntrl;
Elmnt elmnt;
Buffer *mBuf;
#endif
{
   U8 subAction;

   TRC3(cmPkPjCntrl)

      switch(elmnt)
      {
         case STGEN:
            {
               subAction = cntrl->t.cntrl.subAction;
               switch(subAction)
               {
                  case SADBG:
                     CMCHKPK(cmPkPjDbgCntrl, &cntrl->t.cntrl.s.dbgCntrl, mBuf);
                     break;
                  case SATRC:
                     CMCHKPK(cmPkPjTrcCntrl, &cntrl->t.cntrl.s.trcCntrl, mBuf);
                     break;
#ifdef SS_DIAG
                  case SALOG:
                     CMCHKPK(SPkU32, cntrl->t.cntrl.s.logMask, mBuf);
                     break;
#endif
                  default :
                     break;
               }
            }
         case STKWUSAP:
            {
               CMCHKPK(SPkS16, cntrl->t.cntrl.s.sapCntrl.spId, mBuf);
               CMCHKPK(SPkS16, cntrl->t.cntrl.s.sapCntrl.suId, mBuf);
               break;
            }
         default:
               break;
      }
   CMCHKPK(SPkU8, cntrl->t.cntrl.subAction, mBuf);
   CMCHKPK(SPkU8, cntrl->t.cntrl.action, mBuf);
   CMCHKPK(cmPkDateTime, &cntrl->t.cntrl.dt, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkPjCntrl
*
*
*     Desc : 
    Control Structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkPjCntrl
(
PjMngmt *cfm,
Elmnt elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjCntrl(cfm, elmnt, mBuf)
PjMngmt *cfm;
Elmnt elmnt;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkPjCntrl)

   CMCHKUNPK(cmUnpkDateTime, &cfm->t.cntrl.dt, mBuf);
   CMCHKUNPK(SUnpkU8, &cfm->t.cntrl.action, mBuf);
   CMCHKUNPK(SUnpkU8, &cfm->t.cntrl.subAction, mBuf);
#ifdef TENB_SPLIT_ARCH
   switch(cfm->hdr.elmId.elmnt)
   {
      case STGEN:
        {
            switch(cfm->t.cntrl.subAction) 
              {
                 case SADBG:
                    CMCHKUNPK(cmUnpkPjTrcCntrl, &cfm->t.cntrl.s.trcCntrl, mBuf);
                    break;
                 case SATRC:
                    CMCHKUNPK(cmUnpkPjDbgCntrl, &cfm->t.cntrl.s.dbgCntrl, mBuf);
                    break;
#ifdef SS_DIAG
                 case SALOG:
                    CMCHKUNPK(SUnpkU32, &cfm->t.cntrl.s.logMask, mBuf);
                    break;
#endif
                 default :
                    break;
              }
        }
        case STKWUSAP:
        {
           CMCHKUNPK(SUnpkS16, &cfm->t.cntrl.s.sapCntrl.suId, mBuf);
           CMCHKUNPK(SUnpkS16, &cfm->t.cntrl.s.sapCntrl.spId, mBuf);
           break;
        }
        default:
        {
           break;
        }
    }
#else
      switch(cfm->t.cntrl.subAction) {
         case SADBG:
            CMCHKUNPK(cmUnpkPjTrcCntrl, &cfm->t.cntrl.s.trcCntrl, mBuf);
            break;
         case SATRC:
            CMCHKUNPK(cmUnpkPjDbgCntrl, &cfm->t.cntrl.s.dbgCntrl, mBuf);
            break;
#ifdef SS_DIAG
         case SALOG:
            CMCHKUNPK(SUnpkU32, &cfm->t.cntrl.s.logMask, mBuf);
            break;
#endif
         default :
            break;
      }
#endif
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkPjUSta
*
*
*     Desc : 
    Unsolicited Status Structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkPjUSta
(
PjMngmt *usta,
Elmnt elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkPjUSta(usta, elmnt, mBuf)
PjMngmt *usta;
Elmnt elmnt;
Buffer *mBuf;
#endif
{

   TRC3(cmPkPjUSta)
/* lpj_c_001.main_1 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
   CMCHKPK(SPkU8, usta->t.usta.qci, mBuf);
#endif
   CMCHKPK(SPkU32, usta->t.usta.ueId, mBuf);
   CMCHKPK(SPkS16, usta->t.usta.suId, mBuf);
   CMCHKPK(cmPkCmAlarm, &usta->t.usta.alarm, mBuf);
   CMCHKPK(cmPkDateTime, &usta->t.usta.dt, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkPjUSta
*
*
*     Desc : 
    Unsolicited Status Structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkPjUSta
(
PjMngmt *usta,
Elmnt elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjUSta(usta, elmnt, mBuf)
PjMngmt *usta;
Elmnt elmnt;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkPjUSta)

   CMCHKUNPK(cmUnpkDateTime, &usta->t.usta.dt, mBuf);
   CMCHKUNPK(cmUnpkCmAlarm, &usta->t.usta.alarm, mBuf);
   CMCHKUNPK(SUnpkS16, &usta->t.usta.suId, mBuf);
   CMCHKUNPK(SUnpkU32, &usta->t.usta.ueId, mBuf);
/* lpj_c_001.main_1 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
   CMCHKUNPK(SUnpkU8, &usta->t.usta.qci, mBuf);
#endif
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkPjTrc
*
*
*     Desc : 
    Trace Structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkPjTrc
(
PjMngmt *trc,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkPjTrc(trc, mBuf)
PjMngmt *trc;
Buffer *mBuf;
#endif
{

   TRC3(cmPkPjTrc)

   CMCHKPK(SPkU16, trc->t.trc.event, mBuf);
   CMCHKPK(cmPkDateTime, &trc->t.trc.dt, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkPjTrc
*
*
*     Desc : 
    Trace Structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkPjTrc
(
PjMngmt *trc,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjTrc(trc, mBuf)
PjMngmt *trc;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkPjTrc)

   CMCHKUNPK(cmUnpkDateTime, &trc->t.trc.dt, mBuf);
   CMCHKUNPK(SUnpkU16, &trc->t.trc.event, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkPjMngmt
*
*
*     Desc : 
    Layer Management Structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkPjMngmt
(
PjMngmt *param,
Event eventType,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkPjMngmt(param, eventType, mBuf)
PjMngmt *param;
Event eventType;
Buffer *mBuf;
#endif
{
   S16   ret1;

   TRC3(cmPkPjMngmt)

      switch(eventType)
      {
         case LPJ_EVT_CFG_REQ:
            ret1 = cmPkPjCfg(param, param->hdr.elmId.elmnt, mBuf);
            if (ret1 != ROK)
            {
               RETVALUE(RFAILED);
            }
            break;
         case LPJ_EVT_CNTRL_REQ:
            ret1 = cmPkPjCntrl(param, param->hdr.elmId.elmnt, mBuf);
            if (ret1 != ROK)
            {
               RETVALUE(RFAILED);
            }
            break;

         case LPJ_EVT_CFG_CFM:
         case LPJ_EVT_CNTRL_CFM:
            break;

         case LPJ_EVT_STA_REQ:
         case LPJ_EVT_STA_CFM:
            ret1 = cmPkPjSSta(param, param->hdr.elmId.elmnt, eventType, mBuf);
            if (ret1 != ROK)
            {
               RETVALUE(RFAILED);
            }
            break;
         case LPJ_EVT_STS_REQ:
         case LPJ_EVT_STS_CFM:
            ret1 = cmPkPjSts(param, param->hdr.elmId.elmnt, mBuf);
            if (ret1 != ROK)
            {
               RETVALUE(RFAILED);
            }
            break;
         case LPJ_EVT_STA_IND:
            ret1 = cmPkPjUSta(param, param->hdr.elmId.elmnt, mBuf);
            if (ret1 != ROK)
            {
               RETVALUE(RFAILED);
            }
            break;
         case LPJ_EVT_TRC_IND:
            ret1 = cmPkPjTrc(param, mBuf);
            if (ret1 != ROK)
            {
               RETVALUE(RFAILED);
            }
            break;
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(cmPkCmStatus, &param->cfm, mBuf);
   CMCHKPK(cmPkHeader, &param->hdr, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkPjMngmt
*
*
*     Desc : 
    Layer Management Structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkPjMngmt
(
PjMngmt *param,
Event eventType,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPjMngmt(param, eventType, mBuf)
PjMngmt *param;
Event eventType;
Buffer *mBuf;
#endif
{
   S16   ret1;

   TRC3(cmUnpkPjMngmt)

   cmMemset((U8 *) param, (U8) 0, (S16) sizeof(PjMngmt));

   CMCHKUNPK(cmUnpkHeader, &param->hdr, mBuf);
   CMCHKUNPK(cmUnpkCmStatus, &param->cfm, mBuf);
      switch(eventType) {
         case LPJ_EVT_CFG_REQ:
            ret1 = cmUnpkPjCfg(param, param->hdr.elmId.elmnt ,mBuf);
            if (ret1 != ROK)
            {
               RETVALUE(RFAILED);
            }
            break;
         case LPJ_EVT_CNTRL_REQ:
            ret1 = cmUnpkPjCntrl(param, param->hdr.elmId.elmnt ,mBuf);
            if (ret1 != ROK)
            {
               RETVALUE(RFAILED);
            }
            break;
         case LPJ_EVT_CFG_CFM:
         case LPJ_EVT_CNTRL_CFM:
            break;
         case LPJ_EVT_STS_REQ:
         case LPJ_EVT_STS_CFM:
            ret1 = cmUnpkPjSts(param, param->hdr.elmId.elmnt ,mBuf);
            if (ret1 != ROK)
            {
               RETVALUE(RFAILED);
            }
            break;
         case LPJ_EVT_STA_REQ:
         case LPJ_EVT_STA_CFM:
            ret1 = cmUnpkPjSSta(param, param->hdr.elmId.elmnt, eventType, mBuf);
            if (ret1 != ROK)
            {
               RETVALUE(RFAILED);
            }
            break;
         case LPJ_EVT_STA_IND:
            ret1 = cmUnpkPjUSta(param, param->hdr.elmId.elmnt, mBuf);
            if (ret1 != ROK)
            {
               RETVALUE(RFAILED);
            }
            break;
         case LPJ_EVT_TRC_IND:
            ret1 = cmUnpkPjTrc(param, mBuf);
            if (ret1 != ROK)
            {
               RETVALUE(RFAILED);
            }
            break;
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* (defined(LCLPJ) || defined(LWLCLPJ)) */

  
/********************************************************************30**
  
         End of file:     lpj.c@@/main/2 - Fri Sep  2 19:15:01 2011
  
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
/main/1      ---      gk   1. LTE RLC PDCP 2.1 release
/main/2     lpj_c_001.main_1 ap 1.Added missing packing and  unpacking.
                                2. Added support for L2 Measurement.
/main/3     lpj_c_001.main_2 ap 1. Fix for ccpu00120840, correction in 
                                   cmPkPjSSta and cmUnpkPjSSta.
*********************************************************************91*/
 
