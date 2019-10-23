

/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for pack/unpack of LRG interface primitives. 
  
     File:     lrg.c 
  
     Sid:      lrg.c@@/main/4 - Wed Jul 27 11:59:51 2011
  
     Prg:      sm
  
**********************************************************************/

/** @file lrg.c
@brief This file contains the packing/unpacking code for the LRG interface 
       primitives.
*/

/* header include files (.h) */
#include "envopt.h"        /* Environment options */
#include "envdep.h"        /* Environment dependent */
#include "envind.h"        /* Environment independent */
#include "gen.h"           /* General */
#include "ssi.h"           /* System Services */
#include "cm_tkns.h"       /* Common Token Defines */
#include "cm_llist.h"      /* Common Link List Defines */
#include "cm_hash.h"       /* Common Hash List Defines */
#include "cm_lte.h"        /* Common LTE Defines */
#include "lrg.h"           /* LRG Interface Defines */

/* header/extern include files (.x) */
#include "gen.x"           /* General */
#include "ssi.x"           /* System Services */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_lib.x"        /* Common Library Definitions */
#include "cm_hash.x"       /* Common Hash List Definitions */
#include "cm_lte.x"        /* Common LTE Defines */
#include "lrg.x"           /* LRG Interface includes */

#if (defined(LCLRG))


/**
* @brief This API is used to send a 
Configuration Request from LM to MAC.
*
* @details
*
*     Function: cmPkLrgCfgReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLrgCfgReq
(
Pst * pst,
RgMngmt * cfg
)
#else
PUBLIC S16 cmPkLrgCfgReq(pst, cfg)
Pst * pst;
RgMngmt * cfg;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLrgCfgReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELRG001, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector == LRG_SEL_LC) {
      if (cmPkRgMngmt(pst, cfg, EVTLRGCFGREQ, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG002, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   pst->event = (Event) EVTLRGCFGREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
Configuration Request from LM to MAC.
*
* @details
*
*     Function: cmUnpkLrgCfgReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLrgCfgReq
(
LrgCfgReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLrgCfgReq(func, pst, mBuf)
LrgCfgReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   /* lrg_c_001.main_2: Changed Pointer across Interface */
   RgMngmt cfg;
   
   TRC3(cmUnpkLrgCfgReq)
   
   if (cmUnpkRgMngmt(pst, &cfg, EVTLRGCFGREQ, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG003, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, &cfg));
}


/**
* @brief This API is used to send a 
Configuration Request from LM to SCH.
*
* @details
*
*     Function: cmPkLrgSchCfgReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLrgSchCfgReq
(
Pst * pst,
RgMngmt * cfg
)
#else
PUBLIC S16 cmPkLrgSchCfgReq(pst, cfg)
Pst * pst;
RgMngmt * cfg;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLrgSchCfgReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELRG004, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector == LRG_SEL_LC) {
      if (cmPkRgMngmt(pst, cfg, EVTLRGSCHCFGREQ, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG005, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   
   pst->event = (Event) EVTLRGSCHCFGREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
Configuration Request from LM to SCH.
*
* @details
*
*     Function: cmUnpkLrgSchCfgReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLrgSchCfgReq
(
LrgSchCfgReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLrgSchCfgReq(func, pst, mBuf)
LrgSchCfgReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   /* lrg_c_001.main_2: Changed Pointer across Interface */
   RgMngmt cfg;
   
   TRC3(cmUnpkLrgSchCfgReq)

   if (cmUnpkRgMngmt(pst, &cfg, EVTLRGSCHCFGREQ, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG006, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, &cfg));
}


/**
* @brief This API is used to send a 
Configuration Confirm from MAC to LM.
*
* @details
*
*     Function: cmPkLrgCfgCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLrgCfgCfm
(
Pst * pst,
RgMngmt * cfm
)
#else
PUBLIC S16 cmPkLrgCfgCfm(pst, cfm)
Pst * pst;
RgMngmt * cfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLrgCfgCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELRG007, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector == LRG_SEL_LC) {
      if (cmPkRgMngmt(pst, cfm, EVTLRGCFGCFM, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG008, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   
   pst->event = (Event) EVTLRGCFGCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
Configuration Confirm from MAC to LM.
*
* @details
*
*     Function: cmUnpkLrgCfgCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLrgCfgCfm
(
LrgCfgCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLrgCfgCfm(func, pst, mBuf)
LrgCfgCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   RgMngmt cfm;
   
   TRC3(cmUnpkLrgCfgCfm)

   if (cmUnpkRgMngmt(pst, &cfm, EVTLRGCFGCFM, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG009, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, &cfm));
}


/**
* @brief This API is used to send a 
Configuration Confirm from SCH to LM.
*
* @details
*
*     Function: cmPkLrgSchCfgCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLrgSchCfgCfm
(
Pst * pst,
RgMngmt * cfg
)
#else
PUBLIC S16 cmPkLrgSchCfgCfm(pst, cfg)
Pst * pst;
RgMngmt * cfg;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLrgSchCfgCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELRG010, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector == LRG_SEL_LC) {
      if (cmPkRgMngmt(pst, cfg, EVTLRGSCHCFGCFM, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG011, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   
   pst->event = (Event) EVTLRGSCHCFGCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
Configuration Confirm from SCH to LM.
*
* @details
*
*     Function: cmUnpkLrgSchCfgCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLrgSchCfgCfm
(
LrgSchCfgCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLrgSchCfgCfm(func, pst, mBuf)
LrgSchCfgCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   RgMngmt cfg;
   
   TRC3(cmUnpkLrgSchCfgCfm)
  
   if (cmUnpkRgMngmt(pst, &cfg, EVTLRGSCHCFGCFM, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG012, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, &cfg));
}


/**
* @brief This API is used to send a 
Statistics Request from LM to MAC.
*
* @details
*
*     Function: cmPkLrgStsReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  sts
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLrgStsReq
(
Pst * pst,
RgMngmt * sts
)
#else
PUBLIC S16 cmPkLrgStsReq(pst, sts)
Pst * pst;
RgMngmt * sts;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLrgStsReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELRG013, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector == LRG_SEL_LC) {
      if (cmPkRgMngmt(pst, sts, EVTLRGSTSREQ, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG014, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   
   pst->event = (Event) EVTLRGSTSREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
Statistics Request from LM to MAC.
*
* @details
*
*     Function: cmUnpkLrgStsReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  sts
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLrgStsReq
(
LrgStsReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLrgStsReq(func, pst, mBuf)
LrgStsReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   RgMngmt sts;
   
   TRC3(cmUnpkLrgStsReq)

   if (cmUnpkRgMngmt(pst, &sts, EVTLRGSTSREQ, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG015, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, &sts));
}


/**
* @brief This API is used to send a 
Statistics Confirm from MAC to LM.
*
* @details
*
*     Function: cmPkLrgStsCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLrgStsCfm
(
Pst * pst,
RgMngmt * cfm
)
#else
PUBLIC S16 cmPkLrgStsCfm(pst, cfm)
Pst * pst;
RgMngmt * cfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLrgStsCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELRG016, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector == LRG_SEL_LC) {
      if (cmPkRgMngmt(pst, cfm, EVTLRGSTSCFM, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG017, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   
   pst->event = (Event) EVTLRGSTSCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
Statistics Confirm from MAC to LM.
*
* @details
*
*     Function: cmUnpkLrgStsCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLrgStsCfm
(
LrgStsCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLrgStsCfm(func, pst, mBuf)
LrgStsCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   RgMngmt cfm;
   
   TRC3(cmUnpkLrgStsCfm)

   if (cmUnpkRgMngmt(pst, &cfm, EVTLRGSTSCFM, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG018, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, &cfm));
}


/**
* @brief This API is used to send a 
Status Request from LM to MAC.
*
* @details
*
*     Function: cmPkLrgStaReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  sta
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLrgStaReq
(
Pst * pst,
RgMngmt * sta
)
#else
PUBLIC S16 cmPkLrgStaReq(pst, sta)
Pst * pst;
RgMngmt * sta;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLrgStaReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELRG019, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmPkRgMngmt(pst, sta, EVTLRGSSTAREQ, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG020, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   
   pst->event = (Event) EVTLRGSSTAREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
Status Request from LM to MAC.
*
* @details
*
*     Function: cmUnpkLrgStaReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  sta
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLrgStaReq
(
LrgStaReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLrgStaReq(func, pst, mBuf)
LrgStaReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   RgMngmt sta;
   
   TRC3(cmUnpkLrgStaReq)
   
   cmMemset((U8 *)&sta, 0, sizeof(RgMngmt));
   if (cmUnpkRgMngmt(pst, &sta, EVTLRGSSTAREQ, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG021, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, &sta));
}


/**
* @brief This API is used to send a 
Status Confirm from MAC to LM.
*
* @details
*
*     Function: cmPkLrgStaCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLrgStaCfm
(
Pst * pst,
RgMngmt * cfm
)
#else
PUBLIC S16 cmPkLrgStaCfm(pst, cfm)
Pst * pst;
RgMngmt * cfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLrgStaCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELRG022, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmPkRgMngmt(pst, cfm, EVTLRGSSTACFM, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG023, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   
   pst->event = (Event) EVTLRGSSTACFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
Status Confirm from MAC to LM.
*
* @details
*
*     Function: cmUnpkLrgStaCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLrgStaCfm
(
LrgStaCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLrgStaCfm(func, pst, mBuf)
LrgStaCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   RgMngmt cfm;
   
   TRC3(cmUnpkLrgStaCfm)
  
   cmMemset((U8 *)&cfm, 0, sizeof(RgMngmt));
   if (cmUnpkRgMngmt(pst, &cfm, EVTLRGSSTACFM, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG024, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, &cfm));
}


/**
* @brief This API is used to send a 
Status Indication from MAC to LM.
*
* @details
*
*     Function: cmPkLrgStaInd
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  usta
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLrgStaInd
(
Pst * pst,
RgMngmt * usta
)
#else
PUBLIC S16 cmPkLrgStaInd(pst, usta)
Pst * pst;
RgMngmt * usta;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLrgStaInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELRG025, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector == LRG_SEL_LC) {
      if (cmPkRgMngmt(pst, usta, EVTLRGUSTAIND, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG026, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   
   pst->event = (Event) EVTLRGUSTAIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
Status Indication from MAC to LM.
*
* @details
*
*     Function: cmUnpkLrgStaInd
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  usta
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLrgStaInd
(
LrgStaInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLrgStaInd(func, pst, mBuf)
LrgStaInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   RgMngmt usta;
   
   TRC3(cmUnpkLrgStaInd)

   if (cmUnpkRgMngmt(pst, &usta, EVTLRGUSTAIND, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG027, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, &usta));
}


/**
* @brief This API is used to send a 
Status Indication from SCH to LM.
*
* @details
*
*     Function: cmPkLrgSchStaInd
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  sta
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLrgSchStaInd
(
Pst * pst,
RgMngmt * sta
)
#else
PUBLIC S16 cmPkLrgSchStaInd(pst, sta)
Pst * pst;
RgMngmt * sta;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLrgSchStaInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELRG028, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector == LRG_SEL_LC) {
      if (cmPkRgMngmt(pst, sta, EVTLRGSCHSTAIND, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG029, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   
   pst->event = (Event) EVTLRGSCHSTAIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
Status Indication from SCH to LM.
*
* @details
*
*     Function: cmUnpkLrgSchStaInd
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  sta
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLrgSchStaInd
(
LrgSchStaInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLrgSchStaInd(func, pst, mBuf)
LrgSchStaInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   RgMngmt sta;
   
   TRC3(cmUnpkLrgSchStaInd)

   if (cmUnpkRgMngmt(pst, &sta, EVTLRGSCHSTAIND, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG030, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, &sta));
}


/**
* @brief This API is used to send a 
Control Request from LM to MAC.
*
* @details
*
*     Function: cmPkLrgCntrlReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cntrl
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLrgCntrlReq
(
Pst * pst,
RgMngmt * cntrl
)
#else
PUBLIC S16 cmPkLrgCntrlReq(pst, cntrl)
Pst * pst;
RgMngmt * cntrl;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLrgCntrlReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELRG031, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector == LRG_SEL_LC) {
      if (cmPkRgMngmt(pst, cntrl, EVTLRGCNTRLREQ, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG032, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   
   pst->event = (Event) EVTLRGCNTRLREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
Control Request from LM to MAC.
*
* @details
*
*     Function: cmUnpkLrgCntrlReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cntrl
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLrgCntrlReq
(
LrgCntrlReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLrgCntrlReq(func, pst, mBuf)
LrgCntrlReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   RgMngmt cntrl;
   
   TRC3(cmUnpkLrgCntrlReq)

   if (cmUnpkRgMngmt(pst, &cntrl, EVTLRGCNTRLREQ, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG033, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, &cntrl));
}


/**
* @brief This API is used to send a 
Control Request from LM to SCH.
*
* @details
*
*     Function: cmPkLrgSchCntrlReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cntrl
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLrgSchCntrlReq
(
Pst * pst,
RgMngmt * cntrl
)
#else
PUBLIC S16 cmPkLrgSchCntrlReq(pst, cntrl)
Pst * pst;
RgMngmt * cntrl;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLrgSchCntrlReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELRG034, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector == LRG_SEL_LC) {
      if (cmPkRgMngmt(pst, cntrl, EVTLRGSCHCNTRLREQ, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG035, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   
   pst->event = (Event) EVTLRGSCHCNTRLREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
Control Request from LM to SCH.
*
* @details
*
*     Function: cmUnpkLrgSchCntrlReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cntrl
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLrgSchCntrlReq
(
LrgSchCntrlReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLrgSchCntrlReq(func, pst, mBuf)
LrgSchCntrlReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   RgMngmt cntrl;
   
   TRC3(cmUnpkLrgSchCntrlReq)

   if (cmUnpkRgMngmt(pst, &cntrl, EVTLRGSCHCNTRLREQ, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG036, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, &cntrl));
}


/**
* @brief This API is used to send a 
Control Confirm from MAC to LM.
*
* @details
*
*     Function: cmPkLrgCntrlCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLrgCntrlCfm
(
Pst * pst,
RgMngmt * cfm
)
#else
PUBLIC S16 cmPkLrgCntrlCfm(pst, cfm)
Pst * pst;
RgMngmt * cfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLrgCntrlCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELRG037, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector == LRG_SEL_LC) {
      if (cmPkRgMngmt(pst, cfm, EVTLRGCNTRLCFM, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG038, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   
   pst->event = (Event) EVTLRGCNTRLCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
Control Confirm from MAC to LM.
*
* @details
*
*     Function: cmUnpkLrgCntrlCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLrgCntrlCfm
(
LrgCntrlCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLrgCntrlCfm(func, pst, mBuf)
LrgCntrlCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   RgMngmt cfm;
   
   TRC3(cmUnpkLrgCntrlCfm)

   if (cmUnpkRgMngmt(pst, &cfm, EVTLRGCNTRLCFM, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG039, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, &cfm));
}


/**
* @brief This API is used to send a 
Control Confirm from SCH to LM.
*
* @details
*
*     Function: cmPkLrgSchCntrlCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cntrl
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLrgSchCntrlCfm
(
Pst * pst,
RgMngmt * cntrl
)
#else
PUBLIC S16 cmPkLrgSchCntrlCfm(pst, cntrl)
Pst * pst;
RgMngmt * cntrl;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLrgSchCntrlCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELRG040, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector == LRG_SEL_LC) {
      if (cmPkRgMngmt(pst, cntrl, EVTLRGSCHCNTRLCFM, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG041, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   
   pst->event = (Event) EVTLRGSCHCNTRLCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
Control Confirm from SCH to LM.
*
* @details
*
*     Function: cmUnpkLrgSchCntrlCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  cntrl
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLrgSchCntrlCfm
(
LrgSchCntrlCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLrgSchCntrlCfm(func, pst, mBuf)
LrgSchCntrlCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   RgMngmt cntrl;
   
   TRC3(cmUnpkLrgSchCntrlCfm)

   if (cmUnpkRgMngmt(pst, &cntrl, EVTLRGSCHCNTRLCFM, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG042, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, &cntrl));
}


/**
* @brief This API is used to send a 
Trace Indication from MAC to LM.
*
* @details
*
*     Function: cmPkLrgTrcInd
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  trc
*  @param[in]   Buffer *  trcBuf
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLrgTrcInd
(
Pst * pst,
RgMngmt * trc,
Buffer * trcBuf
)
#else
PUBLIC S16 cmPkLrgTrcInd(pst, trc, trcBuf)
Pst * pst;
RgMngmt * trc;
Buffer * trcBuf;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLrgTrcInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELRG043, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(trcBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector == LRG_SEL_LC) {
      MsgLen msgLen;
      if (SFndLenMsg(trcBuf, &msgLen) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG044, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(trcBuf);
         RETVALUE(RFAILED);
      }
      if (SCatMsg(mBuf, trcBuf, M1M2) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG045, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(trcBuf);
         RETVALUE(RFAILED);
      }
      SPutMsg(trcBuf);
      CMCHKPK(cmPkMsgLen, msgLen, mBuf);
   }
   if (cmPkRgMngmt(pst, trc, EVTLRGTRCIND, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG046, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(trcBuf);
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   
   pst->event = (Event) EVTLRGTRCIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
Trace Indication from MAC to LM.
*
* @details
*
*     Function: cmUnpkLrgTrcInd
*
*  @param[in]   Pst *  pst
*  @param[in]   RgMngmt *  trc
*  @param[in]   Buffer *  trcBuf
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLrgTrcInd
(
LrgTrcInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLrgTrcInd(func, pst, mBuf)
LrgTrcInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   RgMngmt trc;
  /* lrg_c_001.main_3 - MODIFY -  Modified trcBuf to have it initialized to NULLP */
   Buffer *trcBuf = NULLP;
   
   TRC3(cmUnpkLrgTrcInd)
   
   if (cmUnpkRgMngmt(pst, &trc, EVTLRGTRCIND, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELRG047, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector == LRG_SEL_LC) {
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


/***********************************************************
*
*     Func : cmPkRgGenCfg
*
*
*     Desc :   This structure holds configuration parameters for MAC General Configuration.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgGenCfg
(
RgGenCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgGenCfg(param, mBuf)
RgGenCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgGenCfg)

#ifdef LTE_ADV
   CMCHKPK(SPkU8, param->isSCellActDeactAlgoEnable, mBuf);
   CMCHKPK(SPkU8, param->forceCntrlSrbBoOnPCel, mBuf);
#endif
   CMCHKPK(SPkU8, param->startCellId, mBuf);
   CMCHKPK(SPkU8, param->numRguSaps, mBuf);
   CMCHKPK(SPkU8, param->tmrRes, mBuf);
   CMCHKPK(cmPkMemoryId, &param->mem, mBuf);
   CMCHKPK(cmPkPst, &param->lmPst, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgGenCfg
*
*
*     Desc :   This structure holds configuration parameters for MAC General Configuration.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgGenCfg
(
RgGenCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgGenCfg(param, mBuf)
RgGenCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgGenCfg)

   CMCHKUNPK(cmUnpkPst, &param->lmPst, mBuf);
   CMCHKUNPK(cmUnpkMemoryId, &param->mem, mBuf);
   CMCHKUNPK(SUnpkU8, &param->tmrRes, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numRguSaps, mBuf);
   CMCHKUNPK(SUnpkU8, &param->startCellId, mBuf);
#ifdef LTE_ADV
   CMCHKUNPK(SUnpkU8, &param->forceCntrlSrbBoOnPCel, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isSCellActDeactAlgoEnable, mBuf);
#endif
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgUpSapCfg
*
*
*     Desc :   This structure holds configuration parameters for MAC Upper SAP Configuration.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgUpSapCfg
(
RgUpSapCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgUpSapCfg(param, mBuf)
RgUpSapCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgUpSapCfg)

   CMCHKPK(SPkS16, param->suId, mBuf);
   CMCHKPK(SPkS16, param->spId, mBuf);
   CMCHKPK(SPkU8, param->route, mBuf);
   CMCHKPK(SPkU8, param->inst, mBuf);
   CMCHKPK(SPkU8, param->ent, mBuf);
   CMCHKPK(SPkU16, param->procId, mBuf);
   CMCHKPK(SPkU8, param->prior, mBuf);
   CMCHKPK(cmPkMemoryId, &param->mem, mBuf);
   CMCHKPK(SPkU8, param->selector, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgUpSapCfg
*
*
*     Desc :   This structure holds configuration parameters for MAC Upper SAP Configuration.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgUpSapCfg
(
RgUpSapCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgUpSapCfg(param, mBuf)
RgUpSapCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgUpSapCfg)

   CMCHKUNPK(SUnpkU8, &param->selector, mBuf);
   CMCHKUNPK(cmUnpkMemoryId, &param->mem, mBuf);
   CMCHKUNPK(SUnpkU8, &param->prior, mBuf);
   CMCHKUNPK(SUnpkU16, &param->procId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ent, mBuf);
   CMCHKUNPK(SUnpkU8, &param->inst, mBuf);
   CMCHKUNPK(SUnpkU8, &param->route, mBuf);
   CMCHKUNPK(SUnpkS16, &param->spId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->suId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgLowSapCfg
*
*
*     Desc :   This structure holds configuration parameters for MAC Lower SAP Configuration.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgLowSapCfg
(
RgLowSapCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgLowSapCfg(param, mBuf)
RgLowSapCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgLowSapCfg)

   CMCHKPK(cmPkTmrCfg, &param->bndTmr, mBuf);
   CMCHKPK(SPkS16, param->suId, mBuf);
   CMCHKPK(SPkS16, param->spId, mBuf);
   CMCHKPK(SPkU8, param->route, mBuf);
   CMCHKPK(SPkU8, param->inst, mBuf);
   CMCHKPK(SPkU8, param->ent, mBuf);
   CMCHKPK(SPkU16, param->procId, mBuf);
   CMCHKPK(SPkU8, param->prior, mBuf);
   CMCHKPK(cmPkMemoryId, &param->mem, mBuf);
   CMCHKPK(SPkU8, param->selector, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgLowSapCfg
*
*
*     Desc :   This structure holds configuration parameters for MAC Lower SAP Configuration.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgLowSapCfg
(
RgLowSapCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgLowSapCfg(param, mBuf)
RgLowSapCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgLowSapCfg)

   CMCHKUNPK(SUnpkU8, &param->selector, mBuf);
   CMCHKUNPK(cmUnpkMemoryId, &param->mem, mBuf);
   CMCHKUNPK(SUnpkU8, &param->prior, mBuf);
   CMCHKUNPK(SUnpkU16, &param->procId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ent, mBuf);
   CMCHKUNPK(SUnpkU8, &param->inst, mBuf);
   CMCHKUNPK(SUnpkU8, &param->route, mBuf);
   CMCHKUNPK(SUnpkS16, &param->spId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->suId, mBuf);
   CMCHKUNPK(cmUnpkTmrCfg, &param->bndTmr, mBuf);
   RETVALUE(ROK);
}

#ifdef MAC_SCH_STATS


/***********************************************************
*
*     Func : cmPkRgAckNack
*
*
*     Desc :   Ack and Nack statistics
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgAckNack
(
RgAckNack *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgAckNack (param, mBuf)
RgAckNack *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgAckNack)

   CMCHKPK(SPkU16, param->numOfAcks, mBuf);
   CMCHKPK(SPkU16, param->numOfNacks, mBuf);
   CMCHKPK(SPkU8, param->mcs, mBuf);

   RETVALUE(ROK);
} /* cmPkRgAckNack */


/***********************************************************
*
*     Func : cmPkRgSchNackAckStats
*
*
*     Desc :   
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgSchNackAckStats
(
RgSchNackAckStats *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgSchNackAckStats (param, mBuf)
RgSchNackAckStats *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkRgSchNackAckStats)

   for (i=14; i >= 0; i--) {
      CMCHKPK(cmPkRgAckNack, &param->ulCqiStat[i], mBuf);
   }

   for (i=14; i >= 0; i--) {
      CMCHKPK(cmPkRgAckNack, &param->dlCqiStat[i], mBuf);
   }

   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkRgHqNumRetx
*
*
*     Desc :   Harq Retransmission statistics
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgHqNumRetx
(
RgSchHqNumRetx *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgHqNumRetx (param, mBuf)
RgSchHqNumRetx *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkRgHqNumRetx)

   CMCHKPK(SPkU32, param->totalTx, mBuf);
   CMCHKPK(SPkU16, param->numOfHQ_4, mBuf);
   CMCHKPK(SPkU16, param->numOfHQ_3, mBuf);
   CMCHKPK(SPkU16, param->numOfHQ_2, mBuf);
   CMCHKPK(SPkU16, param->numOfHQ_1, mBuf);
   CMCHKPK(SPkU8, param->mcs, mBuf);

   RETVALUE(ROK);
} /* cmPkRgHqNumRetx */


/***********************************************************
*
*     Func : cmPkRgSchHqRetxStats
*
*
*     Desc :   
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgSchHqRetxStats
(
RgSchHqRetxStats *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgSchHqRetxStats (param, mBuf)
RgSchHqRetxStats *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkRgSchHqRetxStats)

   for (i=14; i >= 0; i--) {
      CMCHKPK(cmPkRgHqNumRetx, &param->ulCqiStat[i], mBuf);
   }

   for (i=14; i >= 0; i--) {
      CMCHKPK(cmPkRgHqNumRetx, &param->dlCqiStat[i], mBuf);
   }

   RETVALUE(ROK);
} /* cmPkRgSchHqRetxStats */

/* unpcaking functions */

/***********************************************************
*
*     Func : cmUnpkRgAckNack
*
*
*     Desc :   Ack and Nack statistics
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgAckNack
(
RgAckNack *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgAckNack (param, mBuf)
RgAckNack *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgAckNack)

   CMCHKUNPK(SUnpkU8, &param->mcs, mBuf);
   CMCHKUNPK(SUnpkU16, &param->numOfNacks, mBuf);
   CMCHKUNPK(SUnpkU16, &param->numOfAcks, mBuf);

   RETVALUE(ROK);
} /* cmUnkRgAckNack */


/***********************************************************
*
*     Func : cmUnpkRgSchNackAckStats
*
*
*     Desc :   
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgSchNackAckStats
(
RgSchNackAckStats *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgSchNackAckStats (param, mBuf)
RgSchNackAckStats *param;
Buffer *mBuf;
#endif
{
   S32 i;
   TRC3(cmUnpkRgSchNackAckStats)

   for (i=0; i <= 14; i++) {
      CMCHKUNPK(cmUnpkRgAckNack, &param->dlCqiStat[i], mBuf);
   }

   for (i=0; i <= 14; i++) {
      CMCHKUNPK(cmUnpkRgAckNack, &param->ulCqiStat[i], mBuf);
   }

   RETVALUE(ROK);
} /* cmUnpkRgSchNackAckStats */


/***********************************************************
*
*     Func : cmUnpkRgHqNumRetx
*
*
*     Desc :   Harq Retransmission statistics
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgHqNumRetx
(
RgSchHqNumRetx *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgHqNumRetx (param, mBuf)
RgSchHqNumRetx *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkRgHqNumRetx)

   CMCHKUNPK(SUnpkU8, &param->mcs, mBuf);
   CMCHKUNPK(SUnpkU16, &param->numOfHQ_1, mBuf);
   CMCHKUNPK(SUnpkU16, &param->numOfHQ_2, mBuf);
   CMCHKUNPK(SUnpkU16, &param->numOfHQ_3, mBuf);
   CMCHKUNPK(SUnpkU16, &param->numOfHQ_4, mBuf);
   CMCHKUNPK(SUnpkU32, &param->totalTx, mBuf);

   RETVALUE(ROK);
} /* cmUnpkRgHqNumRetx */


/***********************************************************
*
*     Func : cmUnpkRgSchHqRetxStats
*
*
*     Desc :   
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgSchHqRetxStats
(
RgSchHqRetxStats *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgSchHqRetxStats (param, mBuf)
RgSchHqRetxStats *param;
Buffer *mBuf;
#endif
{
   S32 i;
   TRC3(cmUnpkRgSchHqRetxStats)

   for (i=0; i <= 14; i++) {
      CMCHKUNPK(cmUnpkRgHqNumRetx, &param->dlCqiStat[i], mBuf);
   }

   for (i=0; i <= 14; i++) {
      CMCHKUNPK(cmUnpkRgHqNumRetx, &param->ulCqiStat[i], mBuf);
   }

   RETVALUE(ROK);
} /* cmUnpkRgSchHqRetxStats */

#endif /* MAC_SCH_STATS */


/***********************************************************
*
*     Func : cmPkRgGenSts
*
*
*     Desc :   This structure holds General Statistical information of MAC.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgGenSts
(
RgGenSts *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgGenSts(param, mBuf)
RgGenSts *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgGenSts)

#ifdef MAC_SCH_STATS
   CMCHKPK(cmPkRgSchHqRetxStats, &param->hqRetxStats, mBuf);
   CMCHKPK(cmPkRgSchNackAckStats, &param->nackAckStats, mBuf);
#endif /* MAC_SCH_STATS */
   CMCHKPK(SPkU16, param->numCellCfg, mBuf);
   CMCHKPK(SPkU32, param->numUeCfg, mBuf);
   CMCHKPK(SPkU32, param->numHarqFail, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgGenSts
*
*
*     Desc :   This structure holds General Statistical information of MAC.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgGenSts
(
RgGenSts *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgGenSts(param, mBuf)
RgGenSts *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgGenSts)

   CMCHKUNPK(SUnpkU32, &param->numHarqFail, mBuf);
   CMCHKUNPK(SUnpkU32, &param->numUeCfg, mBuf);
   CMCHKUNPK(SUnpkU16, &param->numCellCfg, mBuf);
#ifdef MAC_SCH_STATS
   CMCHKUNPK(cmUnpkRgSchNackAckStats, &param->nackAckStats, mBuf);
   CMCHKUNPK(cmUnpkRgSchHqRetxStats, &param->hqRetxStats, mBuf);
#endif /* MAC_SCH_STATS */
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgSapSts
*
*
*     Desc :   This structure holds Statistical information of a SAP in MAC.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgSapSts
(
RgSapSts *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgSapSts(param, mBuf)
RgSapSts *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgSapSts)

   CMCHKPK(SPkU32, param->numPduDrop, mBuf);
   CMCHKPK(SPkU32, param->numPduTxmit, mBuf);
   CMCHKPK(SPkU32, param->numPduRcvd, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgSapSts
*
*
*     Desc :   This structure holds Statistical information of a SAP in MAC.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgSapSts
(
RgSapSts *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgSapSts(param, mBuf)
RgSapSts *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgSapSts)

   CMCHKUNPK(SUnpkU32, &param->numPduRcvd, mBuf);
   CMCHKUNPK(SUnpkU32, &param->numPduTxmit, mBuf);
   CMCHKUNPK(SUnpkU32, &param->numPduDrop, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgSchInstCfg
*
*
*     Desc : Scheduler Configuration
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgSchInstCfg
(
RgSchInstCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgSchInstCfg(param, mBuf)
RgSchInstCfg *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkRgSchInstCfg)

   for (i=param->numSaps-1; i >= 0; i--) {
      CMCHKPK(cmPkRgLowSapCfg, &param->tfuSap[i], mBuf);
   }
   for (i=param->numSaps-1; i >= 0; i--) {
      CMCHKPK(cmPkRgUpSapCfg, &param->rgrSap[i], mBuf);
   }
   for (i=param->numSaps-1; i >= 0; i--) {
      CMCHKPK(cmPkRgUpSapCfg, &param->rgmSap[i], mBuf);
   }
   CMCHKPK(SPkU8, param->numSaps, mBuf);
   CMCHKPK(cmPkRgGenCfg, &param->genCfg, mBuf);
   CMCHKPK(SPkU8, param->instId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgSchInstCfg
*
*
*     Desc : Scheduler Configuration
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgSchInstCfg
(
RgSchInstCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgSchInstCfg(param, mBuf)
RgSchInstCfg *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkRgSchInstCfg)

   CMCHKUNPK(SUnpkU8, &param->instId, mBuf);
   CMCHKUNPK(cmUnpkRgGenCfg, &param->genCfg, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numSaps, mBuf);
   for (i=0; i<param->numSaps; i++) {
      CMCHKUNPK(cmUnpkRgUpSapCfg, &param->rgmSap[i], mBuf);
   }
   for (i=0; i<param->numSaps; i++) {
      CMCHKUNPK(cmUnpkRgUpSapCfg, &param->rgrSap[i], mBuf);
   }
   for (i=0; i<param->numSaps; i++) {
      CMCHKUNPK(cmUnpkRgLowSapCfg, &param->tfuSap[i], mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgCfg
*
*
*     Desc :   This structure holds Configuration parameters for MAC.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgCfg
(
RgCfg *param,
S16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgCfg(param, elmnt, mBuf)
RgCfg *param;
S16 elmnt;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgCfg)

      switch(elmnt) {
         case STSCHINST:
            CMCHKPK(cmPkRgSchInstCfg, &param->s.schInstCfg, mBuf);
            break;
         case STTFUSAP:
            CMCHKPK(cmPkRgLowSapCfg, &param->s.tfuSap, mBuf);
            break;
         case STCRGSAP:
            CMCHKPK(cmPkRgUpSapCfg, &param->s.crgSap, mBuf);
            break;
         case STRGUSAP:
            CMCHKPK(cmPkRgUpSapCfg, &param->s.rguSap, mBuf);
            break;
         case STGEN:
            CMCHKPK(cmPkRgGenCfg, &param->s.genCfg, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgCfg
*
*
*     Desc :   This structure holds Configuration parameters for MAC.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgCfg
(
RgCfg *param,
S16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgCfg(param, elmnt, mBuf)
RgCfg *param;
S16 elmnt;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgCfg)

      switch(elmnt) {
         case STGEN:
            CMCHKUNPK(cmUnpkRgGenCfg, &param->s.genCfg, mBuf);
            break;
         case STRGUSAP:
            CMCHKUNPK(cmUnpkRgUpSapCfg, &param->s.rguSap, mBuf);
            break;
         case STCRGSAP:
            CMCHKUNPK(cmUnpkRgUpSapCfg, &param->s.crgSap, mBuf);
            break;
         case STTFUSAP:
            CMCHKUNPK(cmUnpkRgLowSapCfg, &param->s.tfuSap, mBuf);
            break;
         case STSCHINST:
            CMCHKUNPK(cmUnpkRgSchInstCfg, &param->s.schInstCfg, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgSapSta
*
*
*     Desc :   This structure holds a SAP's status information.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgSapSta
(
RgSapSta *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgSapSta(param, mBuf)
RgSapSta *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgSapSta)

   CMCHKPK(SPkU8, param->sapState, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgSapSta
*
*
*     Desc :   This structure holds a SAP's status information.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgSapSta
(
RgSapSta *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgSapSta(param, mBuf)
RgSapSta *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgSapSta)

   CMCHKUNPK(SUnpkU8, &param->sapState, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgSts
*
*
*     Desc :   This structure holds MAC's Statistical information.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgSts
(
RgSts *param,
S16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgSts(param, elmnt, mBuf)
RgSts *param;
S16 elmnt;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgSts)

      switch(elmnt) {
         case STTFUSAP:
            CMCHKPK(cmPkRgSapSts, &param->s.tfuSts, mBuf);
            break;
         case STRGRSAP:
            CMCHKPK(cmPkRgSapSts, &param->s.rgrSts, mBuf);
            break;
         case STCRGSAP:
            CMCHKPK(cmPkRgSapSts, &param->s.crgSts, mBuf);
            break;
         case STRGUSAP:
            CMCHKPK(cmPkRgSapSts, &param->s.rguSts, mBuf);
            break;
         case STGEN:
            CMCHKPK(cmPkRgGenSts, &param->s.genSts, mBuf);
            break;
         default :
            break;
      }
   CMCHKPK(cmPkAction, param->action, mBuf);
   CMCHKPK(SPkU8, param->sapInst, mBuf);
   CMCHKPK(cmPkDateTime, &param->dt, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgSts
*
*
*     Desc :   This structure holds MAC's Statistical information.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgSts
(
RgSts *param,
S16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgSts(param, elmnt, mBuf)
RgSts *param;
S16 elmnt;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgSts)

   CMCHKUNPK(cmUnpkDateTime, &param->dt, mBuf);
   CMCHKUNPK(SUnpkU8, &param->sapInst, mBuf);
   CMCHKUNPK(cmUnpkAction, &param->action, mBuf);
      switch(elmnt) {
         case STGEN:
            CMCHKUNPK(cmUnpkRgGenSts, &param->s.genSts, mBuf);
            break;
         case STRGUSAP:
            CMCHKUNPK(cmUnpkRgSapSts, &param->s.rguSts, mBuf);
            break;
         case STCRGSAP:
            CMCHKUNPK(cmUnpkRgSapSts, &param->s.crgSts, mBuf);
            break;
         case STRGRSAP:
            CMCHKUNPK(cmUnpkRgSapSts, &param->s.rgrSts, mBuf);
            break;
         case STTFUSAP:
            CMCHKUNPK(cmUnpkRgSapSts, &param->s.tfuSts, mBuf);
            break;
         default :
            break;
      }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgSsta
*
*
*     Desc :   This structure holds MAC's Solicited Status information.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgSsta
(
Pst *pst,
RgSsta *param,
S16 elmnt,
#ifdef LRG_V1
U8 eventType,
#endif
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgSsta(pst, param, elmnt, eventType, mBuf)
Pst *pst;
RgSsta *param;
S16 elmnt;
/* lrg_c_001.main_3 - ADD -  Added the extra parameter eventType  to the function  */
#ifdef LRG_V1
U8 eventType;
#endif
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgSsta)

      switch(elmnt) {
         case STTFUSAP:
            CMCHKPK(cmPkRgSapSta, &param->s.tfuSapSta, mBuf);
            break;
         case STRGRSAP:
            CMCHKPK(cmPkRgSapSta, &param->s.rgrSapSta, mBuf);
            break;
         case STCRGSAP:
            CMCHKPK(cmPkRgSapSta, &param->s.crgSapSta, mBuf);
            break;
         case STRGUSAP:
            CMCHKPK(cmPkRgSapSta, &param->s.rguSapSta, mBuf);
            break;
            /*ccpu00118255 - ADD - Check for eventType before Pack */
         case STGEN:
#ifdef LRG_V1 
            if (eventType == EVTLRGSSTACFM)
            {
               CMCHKPK(cmPkSystemId, &param->s.sysId, mBuf);
               if (param->s.sysId.ptNmb != NULLP)
               {
                  SPutSBuf(pst->region, pst->pool, 
                        (Data *)param->s.sysId.ptNmb, LRG_MAX_PT_NUM_SIZE);
               }
            }
#else /*LRG_V1 not defined */
            if (param->s.sysId.ptNmb != NULLP)
            {
                 CMCHKPK(cmPkSystemId, &param->s.sysId, mBuf);
                 SPutSBuf(pst->region, pst->pool, (Data *)param->s.sysId.ptNmb, LRG_MAX_PT_NUM_SIZE);
            }

#endif /*end of LRG_V1 */
            break;
         default :
            break;
      }
   CMCHKPK(SPkU8, param->sapInst, mBuf);
   CMCHKPK(cmPkDateTime, &param->dt, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgSsta
*
*
*     Desc :   This structure holds MAC's Solicited Status information.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgSsta
(
Pst    *pst,
RgSsta *param,
S16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgSsta(pst, param, elmnt, mBuf)
Pst    *pst;
RgSsta *param;
S16 elmnt;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgSsta)

   CMCHKUNPK(cmUnpkDateTime, &param->dt, mBuf);
   CMCHKUNPK(SUnpkU8, &param->sapInst, mBuf);
      switch(elmnt) {
         case STGEN:
            /*ccpu00118255 - ADD - Check for eventType before Unpack */
            if (pst->event == EVTLRGSSTACFM)
            {
               /* After Merging */
               if((SGetSBuf(pst->region, pst->pool, (Data **)&param->s.sysId.ptNmb,
                           LRG_MAX_PT_NUM_SIZE)) != ROK){
#if (ERRCLASS & ERRCLS_ADD_RES)
                  SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                        __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                        (ErrVal)ELRG048, (ErrVal)0, "Packing failed");
#endif
                  SPutMsg(mBuf);
                  RETVALUE(RFAILED);
               }
               /* KWORK_FIX: Moved the memset under the NULL check */
               if (param->s.sysId.ptNmb != NULLP)
               {
                  cmMemset((U8 *)param->s.sysId.ptNmb, 0, LRG_MAX_PT_NUM_SIZE);
                  CMCHKUNPK(cmUnpkSystemId, &param->s.sysId, mBuf);
               }
            }
            break;
         case STRGUSAP:
            CMCHKUNPK(cmUnpkRgSapSta, &param->s.rguSapSta, mBuf);
            break;
         case STCRGSAP:
            CMCHKUNPK(cmUnpkRgSapSta, &param->s.crgSapSta, mBuf);
            break;
         case STRGRSAP:
            CMCHKUNPK(cmUnpkRgSapSta, &param->s.rgrSapSta, mBuf);
            break;
         case STTFUSAP:
            CMCHKUNPK(cmUnpkRgSapSta, &param->s.tfuSapSta, mBuf);
            break;
         default :
            break;
      }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgUstaDgn
*
*
*     Desc :   Alarm diagnostics structure.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgUstaDgn
(
RgUstaDgn *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgUstaDgn(param, mBuf)
RgUstaDgn *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgUstaDgn)

      switch(param->type) {
         case LRG_USTA_DGNVAL_MEM:
            CMCHKPK(cmPkMemoryId, &param->u.mem, mBuf);
            break;
         default :
            break;
      }
   CMCHKPK(SPkU8, param->type, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgUstaDgn
*
*
*     Desc :   Alarm diagnostics structure.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgUstaDgn
(
RgUstaDgn *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgUstaDgn(param, mBuf)
RgUstaDgn *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgUstaDgn)

   CMCHKUNPK(SUnpkU8, &param->type, mBuf);
      switch(param->type) {
         case LRG_USTA_DGNVAL_MEM:
            CMCHKUNPK(cmUnpkMemoryId, &param->u.mem, mBuf);
            break;
         default :
            break;
      }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgUsta
*
*
*     Desc :   This structure holds MAC's Unsolicited Status information.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgUsta
(
RgUsta *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgUsta(param, mBuf)
RgUsta *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgUsta)

   CMCHKPK(cmPkRgUstaDgn, &param->dgn, mBuf);
   CMCHKPK(cmPkCmAlarm, &param->cmAlarm, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgUsta
*
*
*     Desc :   This structure holds MAC's Unsolicited Status information.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgUsta
(
RgUsta *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgUsta(param, mBuf)
RgUsta *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgUsta)

   CMCHKUNPK(cmUnpkCmAlarm, &param->cmAlarm, mBuf);
   CMCHKUNPK(cmUnpkRgUstaDgn, &param->dgn, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgTrc
*
*
*     Desc :   This structure holds MAC's Trace Indication information.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgTrc
(
RgTrc *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgTrc(param, mBuf)
RgTrc *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgTrc)

   CMCHKPK(SPkU8, param->evnt, mBuf);
   CMCHKPK(cmPkDateTime, &param->dt, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgTrc
*
*
*     Desc :   This structure holds MAC's Trace Indication information.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgTrc
(
RgTrc *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgTrc(param, mBuf)
RgTrc *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgTrc)

   CMCHKUNPK(cmUnpkDateTime, &param->dt, mBuf);
   CMCHKUNPK(SUnpkU8, &param->evnt, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgDbgCntrl
*
*
*     Desc :   This structure holds MAC's Debug Control information.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgDbgCntrl
(
RgDbgCntrl *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgDbgCntrl(param, mBuf)
RgDbgCntrl *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgDbgCntrl)

   CMCHKPK(SPkU32, param->dbgMask, mBuf);
   RETVALUE(ROK);
}

#ifdef PHY_ERROR_LOGING
/***********************************************************
*
*     Func : cmPkRgSchUlAllocCntrl
*
*
*     Desc :   This structure holds MAC's Debug Control information.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgSchUlAllocCntrl
(
RgSchUlAllocCntrl *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgSchUlAllocCntrl(param, mBuf)
RgSchUlAllocCntrl *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkRgSchUlAllocCntrl)

   CMCHKPK(SPkU8, param->mcs, mBuf);
   CMCHKPK(SPkU16, param->numOfRb, mBuf);
   CMCHKPK(SPkU16, param->rbStart, mBuf);
   CMCHKPK(SPkU8, param->testStart, mBuf);
   CMCHKPK(SPkU8, param->enaLog, mBuf);
   CMCHKPK(SPkU16, param->logTime, mBuf);

   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmUnpkRgSchUlAllocCntrl
*
*
*     Desc :   This structure holds MAC's Scheduler Configuration for Ul Allocation.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgSchUlAllocCntrl
(
RgSchUlAllocCntrl *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgSchUlAllocCntrl(param, mBuf)
RgSchUlAllocCntrl *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkRgSchUlAllocCntrl)

   CMCHKUNPK(SUnpkU16, &param->logTime, mBuf);
   CMCHKUNPK(SUnpkU8, &param->enaLog, mBuf);
   CMCHKUNPK(SUnpkU8, &param->testStart, mBuf);
   CMCHKUNPK(SUnpkU16, &param->rbStart, mBuf);
   CMCHKUNPK(SUnpkU16, &param->numOfRb, mBuf);   
   CMCHKUNPK(SUnpkU8, &param->mcs, mBuf);

   RETVALUE(ROK);
}


#endif

/***********************************************************
*
*     Func : cmUnpkRgDbgCntrl
*
*
*     Desc :   This structure holds MAC's Debug Control information.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgDbgCntrl
(
RgDbgCntrl *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgDbgCntrl(param, mBuf)
RgDbgCntrl *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgDbgCntrl)

   CMCHKUNPK(SUnpkU32, &param->dbgMask, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgSapCntrl
*
*
*     Desc :   This structure holds MAC's SAP Control information.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgSapCntrl
(
RgSapCntrl *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgSapCntrl(param, mBuf)
RgSapCntrl *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgSapCntrl)

   CMCHKPK(SPkS16, param->spId, mBuf);
   CMCHKPK(SPkS16, param->suId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgSapCntrl
*
*
*     Desc :   This structure holds MAC's SAP Control information.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgSapCntrl
(
RgSapCntrl *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgSapCntrl(param, mBuf)
RgSapCntrl *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgSapCntrl)

   CMCHKUNPK(SUnpkS16, &param->suId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->spId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgCntrl
*
*
*     Desc :   This structure holds MAC's Control information.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgCntrl
(
RgCntrl *param,
S16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgCntrl(param, elmnt, mBuf)
RgCntrl *param;
S16 elmnt;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgCntrl)

      switch(elmnt) {
         case STTFUSAP:
         case STRGUSAP:
         case STRGRSAP:
         case STCRGSAP:
            switch(param->subAction) {
               default :
                  CMCHKPK(cmPkRgSapCntrl, &param->s.rgSapCntrl, mBuf);
                  break;
            }
         break;
         case STGEN:
            switch(param->subAction) {
               case SATRC:
                  CMCHKPK(SPkS16, param->s.trcLen, mBuf);
                  break;
               case SADBG:
                  CMCHKPK(cmPkRgDbgCntrl, &param->s.rgDbgCntrl, mBuf);
                  break;
               case SAUSTA:
                  break;
#ifdef SS_DIAG
               case SALOG:
                  CMCHKPK(SPkU32,  param->s.logMask, mBuf);
                  break;
#endif
#ifdef PHY_ERROR_LOGING
               case SAELMNT:
             CMCHKPK(cmPkRgSchUlAllocCntrl, &param->s.rgSchUlAllocCntrl, mBuf);
		  break;
#endif			   
               default :
                  break;
            }
            break;
         default :
            break;
      }
   CMCHKPK(SPkU8, param->subAction, mBuf);
   CMCHKPK(SPkU8, param->action, mBuf);
   CMCHKPK(cmPkDateTime, &param->dt, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRgCntrl
*
*
*     Desc :   This structure holds MAC's Control information.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgCntrl
(
RgCntrl *param,
S16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgCntrl(param, elmnt, mBuf)
RgCntrl *param;
S16 elmnt;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgCntrl)

   CMCHKUNPK(cmUnpkDateTime, &param->dt, mBuf);
   CMCHKUNPK(SUnpkU8, &param->action, mBuf);
   CMCHKUNPK(SUnpkU8, &param->subAction, mBuf);
      switch(elmnt) {
         case STGEN:
            switch(param->subAction) {
               case SADBG:
                  CMCHKUNPK(cmUnpkRgDbgCntrl, &param->s.rgDbgCntrl, mBuf);
                  break;
               case SATRC:
                  CMCHKUNPK(SUnpkS16, &param->s.trcLen, mBuf);
                  break;
               case SAUSTA:
                  break;
#ifdef SS_DIAG
               case SALOG:
                  CMCHKUNPK(SUnpkU32, &param->s.logMask, mBuf);
                  break;
#endif
#ifdef PHY_ERROR_LOGING
               case SAELMNT:
			      CMCHKUNPK(cmUnpkRgSchUlAllocCntrl, &param->s.rgSchUlAllocCntrl, mBuf);
			      break;
#endif			   
               default :
                  break;
            }
         break;
         case STTFUSAP:
         case STRGUSAP:
         case STRGRSAP:
         case STCRGSAP:
            switch(param->subAction) {
               default :
                  CMCHKUNPK(cmUnpkRgSapCntrl, &param->s.rgSapCntrl, mBuf);
                  break;
            }
            break;
         default :
            break;
      }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRgMngmt
*
*
*     Desc :   This structure holds MAC's Configuration and Control Management Information.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRgMngmt
(
Pst *pst,
RgMngmt *param,
U8 eventType,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRgMngmt(pst, param, eventType, mBuf)
Pst *pst;
RgMngmt *param;
U8 eventType;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRgMngmt)

      switch(eventType) {
         case EVTLRGCNTRLREQ:
         case  EVTLRGCNTRLCFM:
         case EVTLRGSCHCNTRLREQ:
         case  EVTLRGSCHCNTRLCFM:
            if(cmPkRgCntrl(&param->t.cntrl, param->hdr.elmId.elmnt, mBuf) != ROK)
               RETVALUE(RFAILED);
            break;
         case EVTLRGTRCIND:
            CMCHKPK(cmPkRgTrc, &param->t.trc, mBuf);
            break;
         case EVTLRGUSTAIND:
         case EVTLRGSCHSTAIND:
            CMCHKPK(cmPkRgUsta, &param->t.usta, mBuf);
            break;
         case EVTLRGSSTAREQ:
         case  EVTLRGSSTACFM:
            /*ccpu00118255 - ADD - eventType param */
#ifdef LRG_V1
            if(cmPkRgSsta(pst, &param->t.ssta, param->hdr.elmId.elmnt,
                     eventType, mBuf) != ROK)
               RETVALUE(RFAILED);
#else /* LRG_V1 is not defined */
            if(cmPkRgSsta(pst, &param->t.ssta, param->hdr.elmId.elmnt, mBuf) != ROK)
               RETVALUE(RFAILED);
#endif /* end of LRG_V1*/            
            break;
         case EVTLRGSTSREQ:
         case  EVTLRGSTSCFM:
            if(cmPkRgSts(&param->t.sts, param->hdr.elmId.elmnt, mBuf)!= ROK)
               RETVALUE(RFAILED);
            break;
         case EVTLRGCFGREQ:
         case  EVTLRGCFGCFM:
            if(cmPkRgCfg(&param->t.cfg, param->hdr.elmId.elmnt, mBuf) != ROK)
               RETVALUE(RFAILED);
            break;
         case EVTLRGSCHCFGREQ:
         case  EVTLRGSCHCFGCFM:
            if(cmPkRgCfg(&param->t.cfg, param->hdr.elmId.elmnt, mBuf) != ROK)
               RETVALUE(RFAILED);
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
*     Func : cmUnpkRgMngmt
*
*
*     Desc :   This structure holds MAC's Configuration and Control Management Information.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRgMngmt
(
Pst *pst,
RgMngmt *param,
U8 eventType,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgMngmt(pst, param, eventType, mBuf)
Pst *pst;
RgMngmt *param;
U8 eventType;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRgMngmt)

   CMCHKUNPK(cmUnpkHeader, &param->hdr, mBuf);
   CMCHKUNPK(cmUnpkCmStatus, &param->cfm, mBuf);
      switch(eventType) {
         case EVTLRGCFGREQ:
         case  EVTLRGCFGCFM:
         case EVTLRGSCHCFGREQ:
         case  EVTLRGSCHCFGCFM:
            if(cmUnpkRgCfg(&param->t.cfg, param->hdr.elmId.elmnt, mBuf) != ROK)
               RETVALUE(RFAILED);
            break;
         case EVTLRGSTSREQ:
         case  EVTLRGSTSCFM:
            if(cmUnpkRgSts(&param->t.sts, param->hdr.elmId.elmnt, mBuf) != ROK)
               RETVALUE(RFAILED);
            break;
         case EVTLRGSSTAREQ:
         case  EVTLRGSSTACFM:
            if(cmUnpkRgSsta(pst, &param->t.ssta, param->hdr.elmId.elmnt, mBuf) != ROK)
               RETVALUE(RFAILED);
            break;
         case EVTLRGUSTAIND:
         case EVTLRGSCHSTAIND:
            CMCHKUNPK(cmUnpkRgUsta, &param->t.usta, mBuf);
            break;
         case EVTLRGTRCIND:
            CMCHKUNPK(cmUnpkRgTrc, &param->t.trc, mBuf);
            break;
         case EVTLRGCNTRLREQ:
         case  EVTLRGCNTRLCFM:
         case EVTLRGSCHCNTRLREQ:
         case  EVTLRGSCHCNTRLCFM:
            if(cmUnpkRgCntrl(&param->t.cntrl, param->hdr.elmId.elmnt, mBuf) != ROK)
               RETVALUE(RFAILED);
            break;
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}

/* lrg_c_001.main_3 - ADD -  Added the functions pertaining to LTE_L2_MEAS  */
#ifdef LTE_L2_MEAS

/**
* @brief This API is used to pack 
 LrgNmbActvUeQCI elements
*
* @details
*
*     Function: cmPkNmbActvUeQciReq
*
*  @param[in]   LrgNmbActvUeQCI
*  @param[in]   Buffer   *mBuf
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PRIVATE S16  cmPkNmbActvUeQciReq
(
LrgNmbActvUeQCI   *nmbActvUeQci, 
Buffer        *mBuf
)
#else
PRIVATE S16 cmPkNmbActvUeQciReq(nmbActvUeQci, mBuf)
LrgNmbActvUeQCI   *nmbActvUeQci;
Buffer        *mBuf;
#endif
{
   U8      idx;

   TRC3(cmPkNmbActvUeQciReq)
   
   for(idx = 0; idx < nmbActvUeQci->numQci; idx++)
   {
       CMCHKPK(SPkU8, nmbActvUeQci->qci[idx], mBuf);
   }
   CMCHKPK(SPkU8, nmbActvUeQci->numQci, mBuf);
   CMCHKPK(SPkU8, nmbActvUeQci->sampPrd, mBuf);
   RETVALUE(ROK);
}

/**
* @brief This API is used to pack 
 LrgAvgPrbQci elements
*
* @details
*
*     Function: cmPkAvgPrbQciReq
*
*  @param[in]   LrgNmbActvUeQciReq  *avgPrbQciReq
*  @param[in]   Buffer   *mBuf
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PRIVATE S16  cmPkAvgPrbQciReq
(
LrgAvgPrbQCI  *avgPrbQciReq,
Buffer        *mBuf
)
#else
PRIVATE S16 cmPkAvgPrbQciReq(avgPrbQciReq, mBuf)
LrgAvgPrbQCI  *avgPrbQciReq;
Buffer        *mBuf;
#endif
{
   U8      idx;

   TRC3(cmPkAvgPrbQciReq)
   
   for(idx = 0; idx < avgPrbQciReq->numQci; idx++)
   {
       CMCHKPK(SPkU8, avgPrbQciReq->qci[idx], mBuf);
   }
   CMCHKPK(SPkU8, avgPrbQciReq->numQci, mBuf);
   RETVALUE(ROK);

}

/**
* @brief This API is used to send a 
L2 Measurement Request from LM to MAC.
*
* @details
*
*     Function: cmPkLrgSchL2MeasReq
*
*  @param[in]   Pst *  pst
*  @param[in]   LrgSchMeasReqInfo  *  measInfo
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLrgSchL2MeasReq
(
Pst * pst,
LrgSchMeasReqInfo  *measInfo
)
#else
PUBLIC S16 cmPkLrgSchL2MeasReq(pst, measInfo)
Pst * pst;
LrgSchMeasReqInfo  *measInfo;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLrgSchL2MeasReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELRG049, (ErrVal)0, "SGetMsg failed");
#endif
      RETVALUE(RFAILED);
   }
   if(measInfo->measType & LRG_L2MEAS_NMB_ACTV_UE_PER_QCI_DL)
   {
      CMCHKPK(cmPkNmbActvUeQciReq, &measInfo->nmbActvUeQciDl, mBuf);
   }
   if(measInfo->measType & LRG_L2MEAS_NMB_ACTV_UE_PER_QCI_UL)
   {
      CMCHKPK(cmPkNmbActvUeQciReq, &measInfo->nmbActvUeQciUl, mBuf);
   }
   if(measInfo->measType & LRG_L2MEAS_AVG_PRB_PER_QCI_DL)
   {
      CMCHKPK(cmPkAvgPrbQciReq, &measInfo->avgPrbQciDl, mBuf);
   }
   if(measInfo->measType & LRG_L2MEAS_AVG_PRB_PER_QCI_UL)
   {
      CMCHKPK(cmPkAvgPrbQciReq, &measInfo->avgPrbQciUl, mBuf);
   }

   CMCHKPK(cmPkLteCellId, measInfo->cellId, mBuf);
   CMCHKPK(SPkU32, measInfo->timePrd, mBuf);
   CMCHKPK(SPkU16, measInfo->measType, mBuf);
   CMCHKPK(cmPkHeader, &measInfo->hdr, mBuf);
   pst->event = (Event) EVTLRGSCHL2MEASREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}
/**
* @brief This API is used to stop a 
L2 Measurement Request from LM to MAC.
*
* @details
*
*     Function: cmPkLrgSchL2MeasStopReq
*
*  @param[in]   Pst *  pst
*  @param[in]   LrgSchMeasReqInfo  *  measInfo
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLrgSchL2MeasStopReq
(
Pst * pst,
LrgSchMeasStopReqInfo *measInfo
)
#else
PUBLIC S16 cmPkLrgSchL2MeasStopReq(pst, measInfo)
Pst * pst;
LrgSchMeasStopReqInfo *measInfo;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLrgSchL2MeasStopReq)

 if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELRG049, (ErrVal)0, "SGetMsg failed");
#endif
      RETVALUE(RFAILED);
   }
   CMCHKPK(cmPkLteCellId, measInfo->cellId, mBuf);
   /*CMCHKPK(SPkU16, measInfo->timePrd, mBuf);*/
   CMCHKPK(SPkU16, measInfo->measType, mBuf);
   CMCHKPK(cmPkHeader, &measInfo->hdr, mBuf);
   pst->event = (Event) EVTLRGSCHL2MEASSTOPREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}/*cmPkLrgSchL2MeasStopReq*/

/**
* @brief This API is used to send a 
L2 Measurement Request from LM to MAC.
*
* @details
*
*     Function: cmPkLrgSchL2MeasSendReq
*
*  @param[in]   Pst *  pst
*  @param[in]   LrgSchMeasReqInfo  *  measInfo
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLrgSchL2MeasSendReq
(
Pst * pst,
LrgSchMeasSndReqInfo *measInfo
)
#else
PUBLIC S16 cmPkLrgSchL2MeasSendReq(pst, measInfo)
Pst * pst;
LrgSchMeasSndReqInfo *measInfo;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLrgSchL2MeasSendReq)
 if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELRG049, (ErrVal)0, "SGetMsg failed");
#endif
      RETVALUE(RFAILED);
   }
   CMCHKPK(cmPkLteCellId, measInfo->cellId, mBuf);
   CMCHKPK(SPkU32, measInfo->timePrd, mBuf);
   CMCHKPK(SPkU16, measInfo->measType, mBuf);
   CMCHKPK(cmPkHeader, &measInfo->hdr, mBuf);
   pst->event = (Event) EVTLRGSCHL2MEASSENDREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}/*cmPkLrgSchL2MeasSendReq*/

/**
* @brief This API is used to unpack AvgPrbQciReq
*
* @details
*
*     Function: cmUnpkNmbActvUeQciReq
*
*  @param[in]   LrgNmbActvUeQCI     *param
*  @param[in]   Buffer * mBuf
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PRIVATE S16 cmUnpkNmbActvUeQciReq
(
LrgNmbActvUeQCI  *param,
Buffer           *mBuf
)
#else
PRIVATE S16 cmUnpkNmbActvUeQciReq(param, mBuf)
LrgNmbActvUeQCI  *param;
Buffer           *mBuf;
#endif
{
   U8     idx;

   TRC3(cmUnpkNmbActvUeQciReq)

   CMCHKUNPK(SUnpkU8, &param->sampPrd, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numQci, mBuf);
   for(idx = param->numQci; idx > 0; idx--)
   {
      CMCHKUNPK(SUnpkU8, &param->qci[idx - 1], mBuf);
   }

   RETVALUE(ROK);
}

/**
* @brief This API is used to unpack AvgPrbQciReq
*
* @details
*
*     Function: cmUnpkAvgPrbQciReq
*
*  @param[in]   LrgAvgPrbQCI     *param
*  @param[in]   Buffer * mBuf
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PRIVATE S16 cmUnpkAvgPrbQciReq
(
LrgAvgPrbQCI     *param,
Buffer           *mBuf
)
#else
PRIVATE S16 cmUnpkAvgPrbQciReq (param, mBuf)
LrgAvgPrbQCI     *param;
Buffer           *mBuf;
#endif
{
   U8     idx;

   TRC3(cmUnpkAvgPrbQciReq)

   CMCHKUNPK(SUnpkU8, &param->numQci, mBuf);
   for(idx = param->numQci; idx > 0; idx--)
   {
      CMCHKUNPK(SUnpkU8, &param->qci[idx - 1], mBuf);
   }
   RETVALUE(ROK);

}

/**
* @brief This API is used to send a 
Measurement  Request from LM to SCH.
*
* @details
*
*     Function: cmUnpkLrgSchL2MeasReq
*
*  @param[in]   LrgSchMeasReq func
*  @param[in]   Pst *  pst
*  @param[in]   Buffer * mBuf
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLrgSchL2MeasReq
(
LrgSchL2MeasReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLrgSchL2MeasReq(func, pst, mBuf)
LrgSchL2MeasReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   LrgSchMeasReqInfo  measInfo;

   TRC3(cmUnpkLrgSchL2MeasReq)

   CMCHKUNPK(cmUnpkHeader, &measInfo.hdr, mBuf);
   CMCHKUNPK(SUnpkU16, &measInfo.measType, mBuf);
   CMCHKUNPK(SUnpkU32, &measInfo.timePrd, mBuf);
   CMCHKUNPK(cmUnpkLteCellId, &measInfo.cellId, mBuf);
   if(measInfo.measType & LRG_L2MEAS_AVG_PRB_PER_QCI_UL)
   {
      CMCHKUNPK(cmUnpkAvgPrbQciReq, &measInfo.avgPrbQciUl, mBuf);
   }
   if(measInfo.measType & LRG_L2MEAS_AVG_PRB_PER_QCI_DL)
   {
      CMCHKUNPK(cmUnpkAvgPrbQciReq, &measInfo.avgPrbQciDl, mBuf);
   }
   if(measInfo.measType & LRG_L2MEAS_NMB_ACTV_UE_PER_QCI_UL)
   {
      CMCHKUNPK(cmUnpkNmbActvUeQciReq, &measInfo.nmbActvUeQciUl, mBuf);
   }
   if(measInfo.measType & LRG_L2MEAS_NMB_ACTV_UE_PER_QCI_DL)
   {
      CMCHKUNPK(cmUnpkNmbActvUeQciReq, &measInfo.nmbActvUeQciDl, mBuf);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, &measInfo));
}

/**
* @brief This API is used to stop  a 
Measurement  Request from LM to SCH.
*
* @details
*
*     Function: cmUnpkLrgSchL2MeasStopReq
*
*  @param[in]   LrgSchMeasStopReq func
*  @param[in]   Pst *  pst
*  @param[in]   Buffer * mBuf
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLrgSchL2MeasStopReq
(
LrgSchL2MeasStopReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLrgSchL2MeasStopReq(func, pst, mBuf)
LrgSchL2MeasStopReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   LrgSchMeasStopReqInfo measInfo;

   TRC3(cmUnpkLrgSchL2MeasStopReq)

   CMCHKUNPK(cmUnpkHeader, &measInfo.hdr, mBuf);
   CMCHKUNPK(SUnpkU16, &measInfo.measType, mBuf);
   /*CMCHKUNPK(SUnpkU16, &measInfo.timePrd, mBuf);*/
   CMCHKUNPK(cmUnpkLteCellId, &measInfo.cellId, mBuf);
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, &measInfo));
}/*cmUnpkLrgSchL2MeasStopReq*/

/**
* @brief This API is used to send a 
Measurement  Request from LM to SCH.
*
* @details
*
*     Function: cmUnpkLrgSchL2MeasSendReq
*
*  @param[in]   LrgSchMeasSendReq func
*  @param[in]   Pst *  pst
*  @param[in]   Buffer * mBuf
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLrgSchL2MeasSendReq
(
LrgSchL2MeasSendReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLrgSchL2MeasSendReq(func, pst, mBuf)
LrgSchL2MeasSendReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   LrgSchMeasSndReqInfo measInfo;
   CMCHKUNPK(cmUnpkHeader, &measInfo.hdr, mBuf);
   CMCHKUNPK(SUnpkU16, &measInfo.measType, mBuf);
   CMCHKUNPK(SUnpkU32, &measInfo.timePrd, mBuf);
   CMCHKUNPK(cmUnpkLteCellId, &measInfo.cellId, mBuf);
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, &measInfo));
}/*cmUnpkLrgSchL2MeasSendReq*/

/**
* @brief This API is used to stop a 
L2 Measurement confirm from MAC to LM
*
* @details
*
*     Function: cmPkLrgSchL2MeasStopCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   LrgSchMeasCfmInfo  *  measInfo
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLrgSchL2MeasStopCfm
(
Pst * pst,
LrgSchMeasCfmInfo  *measInfo
)
#else
PUBLIC S16 cmPkLrgSchL2MeasStopCfm(pst, measInfo)
Pst * pst;
LrgSchMeasCfmInfo  *measInfo;
#endif
{
   Buffer *mBuf = NULLP;

   TRC3(cmPkLrgSchL2MeasStopCfm)
 if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELRG050, (ErrVal)0, "SGetMsg failed");
#endif
      RETVALUE(RFAILED);
   }
   CMCHKPK(cmPkLteCellId, measInfo->cellId, mBuf);
   CMCHKPK(cmPkCmStatus, &measInfo->cfm, mBuf);
   CMCHKPK(SPkU16, measInfo->measType, mBuf);
   CMCHKPK(cmPkHeader, &measInfo->hdr, mBuf);
   pst->event = (Event) EVTLRGSCHL2MEASSTOPCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}/*cmPkLrgSchL2MeasStopCfm*/
/**
* @brief This API is used to Send a 
Measurement  Confirm from SCH to LM.
*
* @details
*
*     Function: cmUnpkLrgL2SchMeasCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   Buffer * mBuf
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLrgSchL2MeasStopCfm
(
LrgSchL2MeasStopCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLrgSchL2MeasStopCfm(func, pst, mBuf)
LrgSchL2MeasStopCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   LrgSchMeasCfmInfo  measInfo;

   TRC3(cmUnpkLrgSchL2MeasCfm)

   CMCHKUNPK(cmUnpkHeader, &measInfo.hdr, mBuf);
   CMCHKUNPK(SUnpkU16, &measInfo.measType, mBuf);
   CMCHKUNPK(cmUnpkCmStatus, &measInfo.cfm, mBuf);
   CMCHKUNPK(cmUnpkLteCellId, &measInfo.cellId, mBuf);

   SPutMsg(mBuf);
   RETVALUE((*func)(pst, &measInfo));
}/*cmUnpkLrgSchL2MeasStopCfm*/

/**
* @brief This API is used to unpack LrgNumActvUeQCICfm structure
*
* @details
*
*     Function: cmPkNumUeQciCfm 
*
*  @param[in]   LrgNumActvUeQCICfm *  param
*  @param[in]   Buffer *  mBuf
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PRIVATE S16 cmPkNumUeQciCfm
(
LrgNumActvUeQCICfm  *param,
Buffer              *mBuf
)
#else
PRIVATE S16 cmPkNumUeQciCfm(param, mBuf)
LrgNumActvUeQCICfm *param;
Buffer             *mBuf;
#endif
{
   U8         idx;

   TRC3(cmPkNumUeQciCfm)
   
   for(idx = 0; idx < param->numQci; idx++)
   {
/*LRG : Review Tag*/
     CMCHKPK(SPkU8, param->numActvUeQci[idx].qciValue, mBuf);
     CMCHKPK(SPkU8, param->numActvUeQci[idx].numActvUeQci, mBuf);
/*LRG : Review Tag*/
   }
   CMCHKPK(SPkU8, param->numQci, mBuf);
   RETVALUE(ROK);
}

/**
* @brief This API is used to unpack LrgAvgPrbQCICfm structure
*
* @details
*
*     Function: cmPkAvgPrbQciCfm
*
*  @param[in]   LrgAvgPrbQCICfm *  param
*  @param[in]   Buffer *  mBuf
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PRIVATE S16 cmPkAvgPrbQciCfm
(
LrgAvgPrbQCICfm    *param,
Buffer             *mBuf
)
#else
PRIVATE S16  cmPkAvgPrbQciCfm(param, mBuf)
LrgAvgPrbQCICfm    *param;
Buffer             *mBuf;
#endif
{
   U8         idx;

   TRC3(cmPkAvgPrbQciCfm)
   for(idx = 0; idx < param->numQci; idx++)
   {
/*LRG : Review Tag*/
      CMCHKPK(SPkU8, param->prbPercQci[idx].qciValue, mBuf);
      CMCHKPK(SPkU8, param->prbPercQci[idx].prbPercQci, mBuf);
/*LRG : Review Tag*/
   } 
   CMCHKPK(SPkU8, param->numQci, mBuf);
   RETVALUE(ROK);
}

/**
* @brief This API is used to unpack raPreamblesCfm structure
*
* @details
*
*     Function: cmPkRaPrmbsCfm
*
*  @param[in]   LrgRaPreamblesCfm *  param
*  @param[in]   Buffer *  mBuf
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PRIVATE S16 cmPkRaPrmbsCfm
(
LrgRaPreamblesCfm  *param,
Buffer             *mBuf
)
#else
PRIVATE S16 cmPkRaPrmbsCfm(param, mBuf)
LrgRaPreamblesCfm  *param;
Buffer             *mBuf;
#endif
{

   TRC3(cmPkRaPrmbsCfm)
   CMCHKPK(SPkU16, param->randSelPreHighRange, mBuf);
   CMCHKPK(SPkU16, param->randSelPreLowRange, mBuf);
   CMCHKPK(SPkU16, param->dedPreambles, mBuf);
   RETVALUE(ROK);
}

/**
* @brief This API is used to unpack avgPrbCfm structure
*
* @details
*
*     Function: cmPkAvgPrbCfm
*
*  @param[in]   LrgAvgPrbCfm *  param
*  @param[in]   Buffer *  mBuf
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PRIVATE S16 cmPkAvgPrbCfm 
(
LrgAvgPrbCfm  *param,
Buffer        *mBuf
)
#else
PRIVATE S16 cmPkAvgPrbCfm(param, mBuf)
LrgAvgPrbCfm  *param;
Buffer        *mBuf;
#endif
{

   TRC3(cmPkAvgPrbCfm)
   CMCHKPK(SPkU8, param->prbPerc, mBuf);
   RETVALUE(ROK);
}

/**
* @brief This API is used to send a 
L2 Measurement confirm from MAC to LM
*
* @details
*
*     Function: cmPkLrgSchL2MeasCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   LrgSchMeasCfmInfo  *  measInfo
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLrgSchL2MeasCfm
(
Pst * pst,
LrgSchMeasCfmInfo  *measInfo
)
#else
PUBLIC S16 cmPkLrgSchL2MeasCfm(pst, measInfo)
Pst * pst;
LrgSchMeasCfmInfo  *measInfo;
#endif
{
   Buffer *mBuf = NULLP;

   TRC3(cmPkLrgSchL2MeasCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ELRG050, (ErrVal)0, "SGetMsg failed");
#endif
      RETVALUE(RFAILED);
   }
   if(measInfo->measType & LRG_L2MEAS_NMB_ACTV_UE_PER_QCI_DL)
   {
     CMCHKPK(cmPkNumUeQciCfm, &measInfo->numUeQciDlCfm, mBuf);
   }
   if(measInfo->measType & LRG_L2MEAS_NMB_ACTV_UE_PER_QCI_UL)
   {
     CMCHKPK(cmPkNumUeQciCfm, &measInfo->numUeQciUlCfm, mBuf);
   }
   if(measInfo->measType & LRG_L2MEAS_RA_PREAMBLE)
   {
     CMCHKPK(cmPkRaPrmbsCfm, &measInfo->raPrmbsCfm, mBuf);
   }
   if(measInfo->measType & LRG_L2MEAS_AVG_PRB_PER_QCI_DL)
   {
     CMCHKPK(cmPkAvgPrbQciCfm, &measInfo->avgPrbQciDlCfm, mBuf);
   }
   if(measInfo->measType & LRG_L2MEAS_AVG_PRB_PER_QCI_UL)
   {
     CMCHKPK(cmPkAvgPrbQciCfm, &measInfo->avgPrbQciUlCfm, mBuf);
   }
   if(measInfo->measType & LRG_L2MEAS_AVG_PRB_DL)
   {
     CMCHKPK(cmPkAvgPrbCfm, &measInfo->avgPrbDl, mBuf);
   }
   if(measInfo->measType & LRG_L2MEAS_AVG_PRB_UL)
   {
     CMCHKPK(cmPkAvgPrbCfm, &measInfo->avgPrbUl, mBuf);
   }
   if(measInfo->measType & LRG_L2MEAS_TB_TRANS_DL_COUNT)
   {
      CMCHKPK(SPkU32, measInfo->tbTransDlTotalCnt, mBuf);
   }   
   if(measInfo->measType & LRG_L2MEAS_TB_TRANS_DL_FAULTY_COUNT)
   {
      CMCHKPK(SPkU32, measInfo->tbTransDlFaulty, mBuf);
   }   
   if(measInfo->measType & LRG_L2MEAS_TB_TRANS_UL_COUNT)
   {
      CMCHKPK(SPkU32, measInfo->tbTransUlTotalCnt, mBuf);
   }   
   if(measInfo->measType & LRG_L2MEAS_TB_TRANS_UL_FAULTY_COUNT)
   {
      CMCHKPK(SPkU32, measInfo->tbTransUlFaulty, mBuf);
   }   
   CMCHKPK(cmPkLteCellId, measInfo->cellId, mBuf);
   CMCHKPK(cmPkCmStatus, &measInfo->cfm, mBuf);
   CMCHKPK(SPkU16, measInfo->measType, mBuf);
   CMCHKPK(cmPkHeader, &measInfo->hdr, mBuf);
   pst->event = (Event) EVTLRGSCHL2MEASCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

/**
* @brief This API is used to unpack LrgNumActvUeQCICfm
*
* @details
*
*     Function: cmUnpkNumUeQciCfm
*
*  @param[in]   LrgNumActvUeQCICfm *param
*  @param[in]   Buffer * mBuf
*  @return   Void
*      -# ROK
**/
#ifdef ANSI
PRIVATE S16 cmUnpkNumUeQciCfm
(
LrgNumActvUeQCICfm *param,
Buffer          *mBuf
)
#else
PRIVATE S16 cmUnpkNumUeQciCfm(param, mBuf)
LrgNumActvUeQCICfm *param; 
Buffer          *mBuf;
#endif
{
   U8          idx;

   TRC3(cmUnpkNumUeQciCfm)
   CMCHKUNPK(SUnpkU8, &param->numQci, mBuf);
   for(idx = param->numQci; idx > 0; idx--)
   {
/*LRG : Review Tag*/
       CMCHKUNPK(SUnpkU8, &param->numActvUeQci[idx - 1].numActvUeQci, mBuf);
       CMCHKUNPK(SUnpkU8, &param->numActvUeQci[idx - 1].qciValue, mBuf);
/*LRG : Review Tag*/
   }
   RETVALUE(ROK);
}

/**
* @brief This API is used to unpack LrgAvgPrbQCICfm
*
* @details
*
*     Function: cmUnpkAvgPrbQciCfm
*
*  @param[in]   LrgAvgPrbQCICfm *param
*  @param[in]   Buffer * mBuf
*  @return  Void 
*      -# ROK
**/
#ifdef ANSI
PRIVATE S16 cmUnpkAvgPrbQciCfm
(
LrgAvgPrbQCICfm *param,
Buffer          *mBuf
)
#else
PRIVATE S16 cmUnpkAvgPrbQciCfm(param, mBuf)
LrgAvgPrbQCICfm *param; 
Buffer          *mBuf;
#endif
{
   U8          idx;

   TRC3(cmUnpkAvgPrbQciCfm)

   CMCHKUNPK(SUnpkU8, &param->numQci, mBuf);
   for(idx = param->numQci; idx > 0; idx--)
   {
/*LRG : Review Tag*/
      CMCHKUNPK(SUnpkU8, &param->prbPercQci[idx - 1].prbPercQci, mBuf);
      CMCHKUNPK(SUnpkU8, &param->prbPercQci[idx - 1].qciValue, mBuf);
/*LRG : Review Tag*/
   }
   RETVALUE(ROK);
}

/**
* @brief This API is used to unpack LrgRaPreamblesCfm
*
* @details
*
*     Function: cmUnpkRaPrmbsCfm
*
*  @param[in]   LrgRaPreamblesCfm *param
*  @param[in]   Buffer * mBuf
*  @return   Void
*      -# ROK
**/
#ifdef ANSI
PRIVATE S16 cmUnpkRaPrmbsCfm
(
LrgRaPreamblesCfm *param,
Buffer         *mBuf
)
#else
PRIVATE S16 cmUnpkRaPrmbsCfm(param, mBuf)
LrgRaPreamblesCfm *param; 
Buffer         *mBuf;
#endif
{

   TRC3(cmUnpkRaPrmbsCfm)

   CMCHKUNPK(SUnpkU16, &param->dedPreambles, mBuf);
   CMCHKUNPK(SUnpkU16, &param->randSelPreLowRange, mBuf);
   CMCHKUNPK(SUnpkU16, &param->randSelPreHighRange, mBuf);
   RETVALUE(ROK);
}

/**
* @brief This API is used to unpack avgPrbCfm
*
* @details
*
*     Function: cmUnpkAvgPrbCfm
*
*  @param[in]   LrgAvgPrbCfm  *param
*  @param[in]   Buffer * mBuf
*  @return   Void
*      -# ROK
**/
#ifdef ANSI
PRIVATE S16 cmUnpkAvgPrbCfm
(
LrgAvgPrbCfm   *param, 
Buffer         *mBuf
)
#else
PRIVATE S16  cmUnpkAvgPrbCfm(param, mBuf)
LrgAvgPrbCfm   *param; 
Buffer         *mBuf;
#endif
{

   TRC3(cmUnpkAvgPrbCfm)

   CMCHKUNPK(SUnpkU8, &param->prbPerc, mBuf);
   RETVALUE(ROK);
}

/**
* @brief This API is used to send a 
Measurement  Confirm from LM to SCH.
*
* @details
*
*     Function: cmUnpkLrgL2SchMeasCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   Buffer * mBuf
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLrgSchL2MeasCfm
(
LrgSchL2MeasCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLrgSchL2MeasCfm(func, pst, mBuf)
LrgSchL2MeasCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   LrgSchMeasCfmInfo  measInfo;

   TRC3(cmUnpkLrgSchL2MeasCfm)

   CMCHKUNPK(cmUnpkHeader, &measInfo.hdr, mBuf);
   CMCHKUNPK(SUnpkU16, &measInfo.measType, mBuf);
   CMCHKUNPK(cmUnpkCmStatus, &measInfo.cfm, mBuf);
   CMCHKUNPK(cmUnpkLteCellId, &measInfo.cellId, mBuf);
   if(measInfo.measType & LRG_L2MEAS_TB_TRANS_UL_FAULTY_COUNT)
   {
      CMCHKPK(SUnpkU32, &measInfo.tbTransUlFaulty, mBuf);
   }    
   if(measInfo.measType & LRG_L2MEAS_TB_TRANS_UL_COUNT)
   {
      CMCHKPK(SUnpkU32, &measInfo.tbTransUlTotalCnt, mBuf);
   }   
   if(measInfo.measType & LRG_L2MEAS_TB_TRANS_DL_FAULTY_COUNT)
   {
      CMCHKPK(SUnpkU32, &measInfo.tbTransDlFaulty, mBuf);
   }   
   if(measInfo.measType & LRG_L2MEAS_TB_TRANS_DL_COUNT)
   {
      CMCHKPK(SUnpkU32, &measInfo.tbTransDlTotalCnt, mBuf);
   }   
   if(measInfo.measType & LRG_L2MEAS_AVG_PRB_UL)
   {
     CMCHKUNPK(cmUnpkAvgPrbCfm, &measInfo.avgPrbUl, mBuf);
   }
   if(measInfo.measType & LRG_L2MEAS_AVG_PRB_DL)
   {
     CMCHKUNPK(cmUnpkAvgPrbCfm, &measInfo.avgPrbDl, mBuf);
   }
   if(measInfo.measType & LRG_L2MEAS_AVG_PRB_PER_QCI_UL)
   {
     CMCHKUNPK(cmUnpkAvgPrbQciCfm, &measInfo.avgPrbQciUlCfm, mBuf);
   }
   if(measInfo.measType & LRG_L2MEAS_AVG_PRB_PER_QCI_DL)
   {
     CMCHKUNPK(cmUnpkAvgPrbQciCfm, &measInfo.avgPrbQciDlCfm, mBuf);
   }
   if(measInfo.measType & LRG_L2MEAS_RA_PREAMBLE)
   {
     CMCHKUNPK(cmUnpkRaPrmbsCfm, &measInfo.raPrmbsCfm, mBuf);
   }
   if(measInfo.measType & LRG_L2MEAS_NMB_ACTV_UE_PER_QCI_UL)
   {
     CMCHKUNPK(cmUnpkNumUeQciCfm, &measInfo.numUeQciUlCfm, mBuf);
   }
   if(measInfo.measType & LRG_L2MEAS_NMB_ACTV_UE_PER_QCI_DL)
   {
     CMCHKUNPK(cmUnpkNumUeQciCfm, &measInfo.numUeQciDlCfm, mBuf);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, &measInfo));
}
#endif
#endif

/**********************************************************************
 
         End of file:     lrg.c@@/main/4 - Wed Jul 27 11:59:51 2011
 
**********************************************************************/
 
/**********************************************************************
 
        Notes:
 
**********************************************************************/
 
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---         sm   1. Initial Release.
/main/2      ---         sm   1. LTE MAC 2.1 release
/main/3      ---      lrg_c_001.main_2 ns   1. code related to LWLC is removed
                              2. freeing memory in the product is
                              removed.
/main/4      ---      lrg_c_001.main_3 dv   1. LTE MAC 3.1 release
*********************************************************************91*/
