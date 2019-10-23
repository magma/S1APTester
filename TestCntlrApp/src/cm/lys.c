

/************************************************************************
 
     Name:     LTE-CL layer
  
     Type:     C source file
  
     Desc:     C source code for pack/unpack of LYS interface primitives. 
  
     File:     lys.c 
  
     Sid:      lys.c@@/main/3 - Tue Aug 30 18:10:39 2011
  
     Prg:      pk
  
**********************************************************************/

/** @file lys.c
@brief This file contains the packing/unpacking code for the LYS interface 
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
#include "lys.h"           /* LRG Interface defines */

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_lib.x"        /* Common Library Definitions */
#include "cm_hash.x"       /* Common Hash List Definitions */
#include "cm_lte.x"        /* Common LTE Defines */
#include "lys.x"           /* LRG Interface includes */
#ifdef SS_4GMX_LCORE
#include "ss_diag.h"   /* log and diagnostics */
#else
#include "ss_diag.h"
#endif /*SS_4GMX_LCORE*/


#ifdef LCLYS

/**
* @brief This API is used to send a 
Config Request from LM to CL.
*
* @details
*
*     Function : cmPkLysCfgReq
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  cfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLysCfgReq
(
Pst * pst,
YsMngmt * cfg
)
#else
PUBLIC S16 cmPkLysCfgReq(pst, cfg)
Pst * pst;
YsMngmt * cfg;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLysCfgReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)cfg, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   if (cmPkYsMngmt(pst, cfg, EVTLYSCFGREQ, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)cfg, sizeof(YsMngmt));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPutSBuf(pst->region, pst->pool, (Data *)cfg, sizeof(YsMngmt)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTLYSCFGREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
Config Request from LM to CL.
*
* @details
*
*     Function : cmUnpkLysCfgReq
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  cfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLysCfgReq
(
LysCfgReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysCfgReq(func, pst, mBuf)
LysCfgReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   YsMngmt *cfg;
   
   TRC3(cmUnpkLysCfgReq)

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfg, sizeof(YsMngmt))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmUnpkYsMngmt(pst, cfg, EVTLYSCFGREQ, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data *)cfg, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cfg));
}


/**
* @brief This API is used to send a 
Config Cfm from CL to LM.
*
* @details
*
*     Function : cmPkLysCfgCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLysCfgCfm
(
Pst * pst,
YsMngmt * cfm
)
#else
PUBLIC S16 cmPkLysCfgCfm(pst, cfm)
Pst * pst;
YsMngmt * cfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLysCfgCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   if (cmPkYsMngmt(pst, cfm, EVTLYSCFGCFM, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTLYSCFGCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
Config Cfm from CL to LM.
*
* @details
*
*     Function : cmUnpkLysCfgCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLysCfgCfm
(
LysCfgCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysCfgCfm(func, pst, mBuf)
LysCfgCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   YsMngmt *cfm;
   
   TRC3(cmUnpkLysCfgCfm)

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfm, sizeof(YsMngmt))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmUnpkYsMngmt(pst, cfm, EVTLYSCFGCFM, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cfm));
}


/**
* @brief This API is used to send a 
Statistics Request from LM to CL.
*
* @details
*
*     Function : cmPkLysStsReq
*
*  @param[in]   Pst *  pst
*  @param[in]   Action  action
*  @param[in]   YsMngmt *  sts
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLysStsReq
(
Pst * pst,
YsMngmt * sts
)
#else
PUBLIC S16 cmPkLysStsReq(pst, sts)
Pst * pst;
YsMngmt * sts;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLysStsReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)sts, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   if (cmPkYsMngmt(pst, sts, EVTLYSSTSREQ, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)sts, sizeof(YsMngmt));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPutSBuf(pst->region, pst->pool, (Data *)sts, sizeof(YsMngmt)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTLYSSTSREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

/**
* @brief this api is used to send a 
          indication for l2 rlog level change.
*
* @details
*
*     function : cmpklysrlind
*
*  @param[in]   pst *  pst
*  @param[in]   u8     rlloglvl
*  @return   s16
*      -# rok
**/
#ifdef ANSI
PUBLIC S16 cmPkLysRlInd
(
Pst * pst,
U8     rlLogLvl
)
#else
PUBLIC S16 cmPkLysRlInd(pst, rlLogLvl)
Pst * pst;
U8     rlLogLvl;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLysRlInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      RETVALUE(RFAILED);
   }

   CMCHKPK(SPkU8, rlLogLvl, mBuf);

   pst->event = (Event) EVTLYSRLIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to receive the RLOG 
*         Indication for  Log Level Change.
*
* @details
*
*     Function : cmUnpkLysRlInd
*
*  @param[in]   Pst *  pst
*  @param[in]   Buffer *mBuf
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLysRlInd
(
LysRlInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysRlInd(func, pst, mBuf)
LysRlInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   U8    rlLogLvl;
   
   TRC3(cmUnpkLysStsReq)

   CMCHKUNPK(SUnpkU8, &rlLogLvl, mBuf);


   SPutMsg(mBuf);

   RETVALUE((*func)(pst, rlLogLvl));
}


/**
* @brief This API is used to send a 
Statistics Request from LM to CL.
*
* @details
*
*     Function : cmUnpkLysStsReq
*
*  @param[in]   Pst *  pst
*  @param[in]   Action  action
*  @param[in]   YsMngmt *  sts
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLysStsReq
(
LysStsReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysStsReq(func, pst, mBuf)
LysStsReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   YsMngmt *sts;
   
   TRC3(cmUnpkLysStsReq)

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&sts, sizeof(YsMngmt))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmUnpkYsMngmt(pst, sts, EVTLYSSTSREQ, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data *)sts, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, sts));
}


/**
* @brief This API is used to send a 
statistics Confirm from CL to LM.
*
* @details
*
*     Function : cmPkLysStsCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLysStsCfm
(
Pst * pst,
YsMngmt * cfm
)
#else
PUBLIC S16 cmPkLysStsCfm(pst, cfm)
Pst * pst;
YsMngmt * cfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLysStsCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   if (cmPkYsMngmt(pst, cfm, EVTLYSSTSCFM, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   
   if (SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTLYSSTSCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
statistics Confirm from CL to LM.
*
* @details
*
*     Function : cmUnpkLysStsCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLysStsCfm
(
LysStsCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysStsCfm(func, pst, mBuf)
LysStsCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   YsMngmt *cfm;
   
   TRC3(cmUnpkLysStsCfm)

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfm, sizeof(YsMngmt))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmUnpkYsMngmt(pst, cfm, EVTLYSSTSCFM, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cfm));
}


/**
* @brief This API is used to send a 
Status Request from LM to CL.
*
* @details
*
*     Function : cmPkLysStaReq
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  sta
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLysStaReq
(
Pst * pst,
YsMngmt * sta
)
#else
PUBLIC S16 cmPkLysStaReq(pst, sta)
Pst * pst;
YsMngmt * sta;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLysStaReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)sta, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   if (cmPkYsMngmt(pst, sta, EVTLYSSSTAREQ, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)sta, sizeof(YsMngmt));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPutSBuf(pst->region, pst->pool, (Data *)sta, sizeof(YsMngmt)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTLYSSSTAREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
Status Request from LM to CL.
*
* @details
*
*     Function : cmUnpkLysStaReq
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  sta
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLysStaReq
(
LysStaReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysStaReq(func, pst, mBuf)
LysStaReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   YsMngmt *sta;
   
   TRC3(cmUnpkLysStaReq)

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&sta, sizeof(YsMngmt))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   cmMemset((U8 *)sta, 0, sizeof(YsMngmt));
   if (cmUnpkYsMngmt(pst, sta, EVTLYSSSTAREQ, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data *)sta, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, sta));
}


/**
* @brief This API is used to send a 
status Confirm from CL to LM.
*
* @details
*
*     Function : cmPkLysStaCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLysStaCfm
(
Pst * pst,
YsMngmt * cfm
)
#else
PUBLIC S16 cmPkLysStaCfm(pst, cfm)
Pst * pst;
YsMngmt * cfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLysStaCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   if (cmPkYsMngmt(pst, cfm, EVTLYSSSTACFM, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTLYSSSTACFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
status Confirm from CL to LM.
*
* @details
*
*     Function : cmUnpkLysStaCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLysStaCfm
(
LysStaCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysStaCfm(func, pst, mBuf)
LysStaCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   YsMngmt *cfm;
   
   TRC3(cmUnpkLysStaCfm)

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfm, sizeof(YsMngmt))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   cmMemset((U8 *)cfm, 0, sizeof(YsMngmt));
   if (cmUnpkYsMngmt(pst, cfm, EVTLYSSSTACFM, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cfm));
}


/**
* @brief This API is used to send a 
status Indication from CL to LM.
*
* @details
*
*     Function : cmPkLysStaInd
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  usta
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLysStaInd
(
Pst * pst,
YsMngmt * usta
)
#else
PUBLIC S16 cmPkLysStaInd(pst, usta)
Pst * pst;
YsMngmt * usta;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLysStaInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)usta, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   if (cmPkYsMngmt(pst, usta, EVTLYSUSTAIND, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)usta, sizeof(YsMngmt));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPutSBuf(pst->region, pst->pool, (Data *)usta, sizeof(YsMngmt)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTLYSUSTAIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
status Indication from CL to LM.
*
* @details
*
*     Function : cmUnpkLysStaInd
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  usta
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLysStaInd
(
LysStaInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysStaInd(func, pst, mBuf)
LysStaInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   YsMngmt *usta;
   
   TRC3(cmUnpkLysStaInd)

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&usta, sizeof(YsMngmt))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmUnpkYsMngmt(pst, usta, EVTLYSUSTAIND, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data *)usta, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, usta));
}


/**
* @brief This API is used to send a 
Control Request from LM to CL.
*
* @details
*
*     Function : cmPkLysCntrlReq
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  cntrl
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLysCntrlReq
(
Pst * pst,
YsMngmt * cntrl
)
#else
PUBLIC S16 cmPkLysCntrlReq(pst, cntrl)
Pst * pst;
YsMngmt * cntrl;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLysCntrlReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)cntrl, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   if (cmPkYsMngmt(pst, cntrl, EVTLYSCNTRLREQ, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)cntrl, sizeof(YsMngmt));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPutSBuf(pst->region, pst->pool, (Data *)cntrl, sizeof(YsMngmt)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTLYSCNTRLREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
Control Request from LM to CL.
*
* @details
*
*     Function : cmUnpkLysCntrlReq
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  cntrl
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLysCntrlReq
(
LysCntrlReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysCntrlReq(func, pst, mBuf)
LysCntrlReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   YsMngmt *cntrl;
   
   TRC3(cmUnpkLysCntrlReq)

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&cntrl, sizeof(YsMngmt))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmUnpkYsMngmt(pst, cntrl, EVTLYSCNTRLREQ, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data *)cntrl, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cntrl));
}


/**
* @brief This API is used to send a 
control Confirm from CL to LM.
*
* @details
*
*     Function : cmPkLysCntrlCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLysCntrlCfm
(
Pst * pst,
YsMngmt * cfm
)
#else
PUBLIC S16 cmPkLysCntrlCfm(pst, cfm)
Pst * pst;
YsMngmt * cfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLysCntrlCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   if (cmPkYsMngmt(pst, cfm, EVTLYSCNTRLCFM, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTLYSCNTRLCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
control Confirm from CL to LM.
*
* @details
*
*     Function : cmUnpkLysCntrlCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLysCntrlCfm
(
LysCntrlCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysCntrlCfm(func, pst, mBuf)
LysCntrlCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   YsMngmt *cfm;
   
   TRC3(cmUnpkLysCntrlCfm)

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfm, sizeof(YsMngmt))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmUnpkYsMngmt(pst, cfm, EVTLYSCNTRLCFM, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cfm));
}


/**
* @brief This API is used to send a 
trace Indication from CL to LM.
*
* @details
*
*     Function : cmPkLysTrcInd
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  trc
*  @param[in]   Buffer *  trcBuf
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLysTrcInd
(
Pst * pst,
YsMngmt * trc,
Buffer * trcBuf
)
#else
PUBLIC S16 cmPkLysTrcInd(pst, trc, trcBuf)
Pst * pst;
YsMngmt * trc;
Buffer * trcBuf;
#endif
{
   Buffer *mBuf = NULLP;
   MsgLen msgLen;
   TRC3(cmPkLysTrcInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)trc, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   if (SFndLenMsg(trcBuf, &msgLen) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      RETVALUE(RFAILED);
   }
   if (SCatMsg(mBuf, trcBuf, M1M2) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      RETVALUE(RFAILED);
   }
   SPutMsg(trcBuf);
   CMCHKPK(SPkS16, msgLen, mBuf);

   if (cmPkYsMngmt(pst, trc, EVTLYSTRCIND, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)trc, sizeof(YsMngmt));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPutSBuf(pst->region, pst->pool, (Data *)trc, sizeof(YsMngmt)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTLYSTRCIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
trace Indication from CL to LM.
*
* @details
*
*     Function : cmUnpkLysTrcInd
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  trc
*  @param[in]   Buffer *  trcBuf
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLysTrcInd
(
LysTrcInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysTrcInd(func, pst, mBuf)
LysTrcInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   YsMngmt *trc;
   Buffer *trcBuf;
   MsgLen msgLen, totalMsgLen;
   
   TRC3(cmUnpkLysTrcInd)

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&trc, sizeof(YsMngmt))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmUnpkYsMngmt(pst, trc, EVTLYSTRCIND, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data *)trc, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   CMCHKUNPK(cmUnpkMsgLen, &msgLen, mBuf);
   if (SFndLenMsg(mBuf, &totalMsgLen) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      RETVALUE(RFAILED);
   }
   if (SSegMsg(mBuf, totalMsgLen-msgLen, &trcBuf) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      RETVALUE(RFAILED);
   }

   SPutMsg(mBuf);
   RETVALUE((*func)(pst, trc, trcBuf));
}


/***********************************************************
*
*     Func : cmPkYsGenCfg
*
*
*     Desc : ysGenCfg
   Structure holding configuration parameters for CL General Configuration
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsGenCfg
(
YsGenCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsGenCfg(param, mBuf)
YsGenCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsGenCfg);

   CMCHKPK(SPkU8, param->enblSIAndPagngLog, mBuf);
#ifdef MSPD
   CMCHKPK(SPkU16, param->logBuf1Size, mBuf);
   CMCHKPK(SPkU16, param->logBuf0Size, mBuf);
#endif
   CMCHKPK(SPkU16, param->freqSyncEarfcn, mBuf);
   CMCHKPK(SPkU16, param->freqSyncPci, mBuf);
   CMCHKPK(SPkU16, param->nmbUe, mBuf);
   CMCHKPK(SPkU16, param->maxTfuSaps, mBuf);
   CMCHKPK(cmPkPst, &param->lmPst, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkYsGenCfg
*
*
*     Desc : ysGenCfg
   Structure holding configuration parameters for CL General Configuration
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsGenCfg
(
YsGenCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsGenCfg(param, mBuf)
YsGenCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsGenCfg);

   CMCHKUNPK(cmUnpkPst, &param->lmPst, mBuf);
   CMCHKUNPK(SUnpkU16, &param->maxTfuSaps, mBuf);
   CMCHKUNPK(SUnpkU16, &param->nmbUe, mBuf);
   CMCHKUNPK(SUnpkU16, &param->freqSyncPci, mBuf);
   CMCHKUNPK(SUnpkU16, &param->freqSyncEarfcn, mBuf);
#ifdef MSPD
   CMCHKUNPK(SUnpkU16, &param->logBuf0Size, mBuf);
   CMCHKUNPK(SUnpkU16, &param->logBuf1Size, mBuf);
#endif
   CMCHKUNPK(SUnpkU8, &param->enblSIAndPagngLog, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkYsTfuSapCfg
*
*
*     Desc : ysTfuSapCfg
   Structure holding configuration parameters for CL Upper SAP Configuration
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsTfuSapCfg
(
YsTfuSapCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsTfuSapCfg(param, mBuf)
YsTfuSapCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsTfuSapCfg);

   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   CMCHKPK(SPkU32, param->type, mBuf);
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
*     Func : cmUnpkYsTfuSapCfg
*
*
*     Desc : ysTfuSapCfg
   Structure holding configuration parameters for CL Upper SAP Configuration
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsTfuSapCfg
(
YsTfuSapCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsTfuSapCfg(param, mBuf)
YsTfuSapCfg *param;
Buffer *mBuf;
#endif
{

   U32 tmpEnum;
   TRC3(cmUnpkYsTfuSapCfg);

   CMCHKUNPK(SUnpkU8, &param->selector, mBuf);
   CMCHKUNPK(cmUnpkMemoryId, &param->mem, mBuf);
   CMCHKUNPK(SUnpkU8, &param->prior, mBuf);
   CMCHKUNPK(SUnpkU16, &param->procId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ent, mBuf);
   CMCHKUNPK(SUnpkU8, &param->inst, mBuf);
   CMCHKUNPK(SUnpkU8, &param->route, mBuf);
   CMCHKUNPK(SUnpkS16, &param->spId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->suId, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->type = tmpEnum;
   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkYsCtfSapCfg
*
*
*     Desc : ysCtfSapCfg
   Structure holding configuration parameters for CL Upper SAP Configuration
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsCtfSapCfg
(
YsCtfSapCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsCtfSapCfg(param, mBuf)
YsCtfSapCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsCtfSapCfg);

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
*     Func : cmUnpkYsCtfSapCfg
*
*
*     Desc : ysCtfSapCfg
   Structure holding configuration parameters for CL Upper SAP Configuration
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsCtfSapCfg
(
YsCtfSapCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsCtfSapCfg(param, mBuf)
YsCtfSapCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsCtfSapCfg);

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
*     Func : cmPkYsCtfSapSts
*
*
*     Desc : ysCtfSapSts
   Structure holding CTF SAP statistical information of CL
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsCtfSapSts
(
YsCtfSapSts *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsCtfSapSts(param, mBuf)
YsCtfSapSts *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsCtfSapSts);

   CMCHKPK(SPkU16, param->numCellCfg, mBuf);
   CMCHKPK(SPkU32, param->numUeCfg, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkYsCtfSapSts
*
*
*     Desc : ysGenSts
   Structure holding General statistical information of CL
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsCtfSapSts
(
YsCtfSapSts *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsCtfSapSts(param, mBuf)
YsCtfSapSts *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsCtfSapSts);

   CMCHKUNPK(SUnpkU32, &param->numUeCfg, mBuf);
   CMCHKUNPK(SUnpkU16, &param->numCellCfg, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkYsTfuSapSts
*
*
*     Desc : ysTfuSapSts
   Structure holding statistical information of a SAP in CL
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsTfuSapSts
(
YsTfuSapSts *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsTfuSapSts(param, mBuf)
YsTfuSapSts *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsTfuSapSts);

   CMCHKPK(SPkU32, param->numRecpReqRcvd, mBuf);
   CMCHKPK(SPkU32, param->numDatReqRcvd, mBuf);
   CMCHKPK(SPkU32, param->numCntrlReqRcvd, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkYsTfuSapSts
*
*
*     Desc : ysTfuSapSts
   Structure holding statistical information of a SAP in CL
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsTfuSapSts
(
YsTfuSapSts *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsTfuSapSts(param, mBuf)
YsTfuSapSts *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsTfuSapSts);

   CMCHKUNPK(SUnpkU32, &param->numCntrlReqRcvd, mBuf);
   CMCHKUNPK(SUnpkU32, &param->numDatReqRcvd, mBuf);
   CMCHKUNPK(SUnpkU32, &param->numRecpReqRcvd, mBuf);
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkYsPhySts
*
*
*     Desc : ysPhySts
   Structure holding statistical information of a SAP in CL
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsPhySts
(
YsL1PhySts *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsPhySts(param, mBuf)
YsL1PhySts *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsPhySts);

   /* lys_c_001.main_1 */
#ifdef YS_MSPD
#ifdef PHY_ERROR_LOGING
   CMCHKPK(cmPkStsCntr, param->numUlPackets, mBuf);
   CMCHKPK(cmPkStsCntr, param->numCrcOk, mBuf);
   CMCHKPK(cmPkStsCntr, param->numCrcErr, mBuf);
#endif
   CMCHKPK(cmPkStsCntr, param->numRxStatusInd, mBuf);
   CMCHKPK(cmPkStsCntr, param->numRxEndInd, mBuf);
   CMCHKPK(cmPkStsCntr, param->numRxSduInd, mBuf);
   CMCHKPK(cmPkStsCntr, param->numRxStartInd, mBuf);
   CMCHKPK(cmPkStsCntr, param->numRxStartCfm, mBuf);
   CMCHKPK(cmPkStsCntr, param->numRxStartReq, mBuf);
   CMCHKPK(cmPkStsCntr, param->numTxEndInd, mBuf);
   CMCHKPK(cmPkStsCntr, param->numTxSduCfm, mBuf);
   CMCHKPK(cmPkStsCntr, param->numTxSduReq, mBuf);
   CMCHKPK(cmPkStsCntr, param->numTxStartInd, mBuf);
   CMCHKPK(cmPkStsCntr, param->numTxStartCfm, mBuf);
   CMCHKPK(cmPkStsCntr, param->numTxStartReq, mBuf);
#else
   CMCHKPK(cmPkStsCntr, param->numSrsIndRx, mBuf);
   CMCHKPK(cmPkStsCntr, param->numRachIndRx, mBuf);
   CMCHKPK(cmPkStsCntr, param->numRxIndRx, mBuf);
   CMCHKPK(cmPkStsCntr, param->numCrcIndRx, mBuf);
   CMCHKPK(cmPkStsCntr, param->numHarqIndRx, mBuf);
   CMCHKPK(cmPkStsCntr, param->numTxReqTx, mBuf);
   CMCHKPK(cmPkStsCntr, param->numHiDciReqTx, mBuf);
   CMCHKPK(cmPkStsCntr, param->numSfIndRx, mBuf);
   CMCHKPK(cmPkStsCntr, param->numSfReqTx, mBuf);
#endif   

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkYsPhySts
*
*
*     Desc : ysPhySts
   Structure holding statistical information of a SAP in CL
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsPhySts
(
YsL1PhySts *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsPhySts(param, mBuf)
YsL1PhySts *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsPhySts);

   /* lys_c_001.main_1 */
#ifdef YS_MSPD
   CMCHKUNPK(cmUnpkStsCntr, &param->numTxStartReq, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numTxStartCfm, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numTxStartInd, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numTxSduReq, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numTxSduCfm, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numTxEndInd, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numRxStartReq, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numRxStartCfm, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numRxStartInd, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numRxSduInd, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numRxEndInd, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numRxStatusInd, mBuf);
#ifdef PHY_ERROR_LOGING
   CMCHKUNPK(cmUnpkStsCntr, &param->numCrcErr, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numCrcOk, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numUlPackets, mBuf);
#endif
#else
   CMCHKUNPK(cmUnpkStsCntr, &param->numSfReqTx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numSfIndRx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numHiDciReqTx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numTxReqTx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numHarqIndRx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numCrcIndRx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numRxIndRx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numRachIndRx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numSrsIndRx, mBuf);
#endif

   RETVALUE(ROK);
}
#ifdef E_TM
/***********************************************************
*
*     Func : cmPkYsEtmInit
*
*
*     Desc : ysEtmInit
   Structure holding configuration parameters for ETM Initialization 
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsEtmInit
(
YsEtmInit *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsEtmInit(param, mBuf)
YsEtmInit *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsEtmInit);

   CMCHKPK(SPkU32,(U32)param->tModel, mBuf);
   CMCHKPK(SPkU32,(U32)param->bw, mBuf);
   CMCHKPK(SPkS32,param->e_rs, mBuf);
   CMCHKPK(SPkU8,param->ant0, mBuf);
   CMCHKPK(SPkU8,param->ant1, mBuf);
   CMCHKPK(SPkU8,param->num_layers, mBuf);
   CMCHKPK(SPkU8,param->num_cw, mBuf);
   CMCHKPK(SPkU8,param->tdd, mBuf);
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmPkYsEtmCfg
*
*
*     Desc : ysEtmCfg
   Structure holding configuration parameters for ETM Initialization 
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsEtmCfg
(
YsEtmCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsEtmCfg(param, mBuf)
YsEtmCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsEtmCfg);

   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   CMCHKPK(cmPkYsEtmInit, &param->etmInit, mBuf);
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmUnpkYsEtmInit
*
*
*     Desc : ysEtmInit
   Structure holding configuration parameters for ETM Initialization 
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsEtmInit
(
YsEtmInit *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsEtmInit(param, mBuf)
YsEtmInit *param;
Buffer *mBuf;
#endif
{
   U32 tmpEnum;

   TRC3(cmUnPkYsEtmInit);

   CMCHKUNPK(SUnpkU8,&param->tdd,mBuf);
   CMCHKUNPK(SUnpkU8,&param->num_cw,mBuf);
   CMCHKUNPK(SUnpkU8,&param->num_layers,mBuf);
   CMCHKUNPK(SUnpkU8,&param->ant1,mBuf);
   CMCHKUNPK(SUnpkU8,&param->ant0,mBuf);
   CMCHKUNPK(SUnpkS32,&param->e_rs,mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->bw = tmpEnum;
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->tModel = tmpEnum;
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmUnpkYsEtmCfg
*
*
*     Desc : ysEtmCfg
   Structure holding configuration parameters for ETM Initialization 
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsEtmCfg
(
YsEtmCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsEtmCfg(param, mBuf)
YsEtmCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsEtmCfg);

   CMCHKPK(cmUnpkYsEtmInit, &param->etmInit, mBuf);
   CMCHKPK(cmUnpkLteCellId, &param->cellId, mBuf);
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func: cmPkLysSrsUlCfgInfo
*
*
*     Desc:   SRS uplink configuration
 * @details This structure contains the information for setting-up/release
 *          of uplink SRS configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkLysSrsUlCfgInfo
(
LysSrsUlCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkLysSrsUlCfgInfo(param, mBuf)
LysSrsUlCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkLysSrsUlCfgInfo)

   if(param->pres != FALSE)
   {
      CMCHKPK(SPkU8, param->srsSetup.srsMaxUpPts, mBuf);
      CMCHKPK(SPkU8, param->srsSetup.srsANSimultTx, mBuf);
      CMCHKPK(SPkU8, param->srsSetup.sfCfg, mBuf);
      CMCHKPK(SPkU8, param->srsSetup.srsBw, mBuf);
      CMCHKPK(SPkU8, param->srsCfgType, mBuf);
   }
   CMCHKPK(SPkU8, param->pres, mBuf);
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func: cmPkLysPdschCfgInfo
*
*
*     Desc:   PDSCH configuration
 * @details This structure contains the PDSCH configuration information for 
 *          configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkLysPdschCfgInfo
(
LysPdschCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkLysPdschCfgInfo(param, mBuf)
LysPdschCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkLysPdschCfgInfo)
   if(param->pres != FALSE)
   {
      CMCHKPK(SPkU8, param->p_b, mBuf);
      CMCHKPK(SPkS16, param->refSigPwr, mBuf);
   }
   CMCHKPK(SPkU8, param->pres, mBuf);
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func: cmPkLysPrachCfgInfo
*
*
*     Desc:   PRACH configuration
 * @details This structure contains the configuration information for PRACH at PHY.
 *          -# PRACH preamble sequences are generated by PHY using Zadoff-Chu 
 *             sequences.[Ref: 36.211, 5.7.2]
 *          -# PRACH preamble format is derived from PRACH Configuration Index.
 *             [Ref: 36.211, Table 5.7.1-2]
 *          -# PrachFreqOffset is the first physical resource block allocated to 
 *             the PRACH opportunity considered for preamble format 0, 1, 2, and 3.
 *             [Ref: 36.211, 5.7.1]
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkLysPrachCfgInfo
(
LysPrachCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkLysPrachCfgInfo(param, mBuf)
LysPrachCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkLysPrachCfgInfo)

   if(param->pres != FALSE)
   {
      CMCHKPK(SPkU8, param->prachFreqOffset, mBuf);
      CMCHKPK(SPkU8, param->highSpeedFlag, mBuf);
      CMCHKPK(SPkU8, param->zeroCorrelationZoneCfg, mBuf);
      CMCHKPK(SPkU8, param->prachCfgIndex, mBuf);
      CMCHKPK(SPkU16, param->rootSequenceIndex, mBuf);
   }
   CMCHKPK(SPkU8, param->pres, mBuf);
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func: cmPkLysAntennaCfgInfo
*
*
*     Desc:   Antenna Ports configuration
 * @details This structure contains the antenna configuration information for 
 *          configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkLysAntennaCfgInfo
(
LysAntennaCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkLysAntennaCfgInfo(param, mBuf)
LysAntennaCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkLysAntennaCfgInfo)

   CMCHKPK(SPkU32, param->antPortsCnt, mBuf);
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func: cmPkLysTxSchemeCfg
*
*
*     Desc:   Transmission Scheme Configuration
 * @details This structure contains the transmission scheme related information.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkLysTxSchemeCfg
(
LysTxSchemeCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkLysTxSchemeCfg(param, mBuf)
LysTxSchemeCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkLysTxSchemeCfg)

   CMCHKPK(SPkU32, param->cycPfx, mBuf);
   CMCHKPK(SPkU32, param->scSpacing, mBuf);
   CMCHKPK(SPkU32, param->duplexMode, mBuf);
    
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func: cmPkLysBwCfgInfo
*
*
*     Desc:   Bandwidth Configuration
 * @details This structure contains the uplink and downlink bandwidth 
 *          information for configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkLysBwCfgInfo
(
LysBwCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkLysBwCfgInfo(param, mBuf)
LysBwCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkLysBwCfgInfo)

   CMCHKPK(SPkU8, param->eUtraBand, mBuf);
   CMCHKPK(SPkU32, param->ulBw, mBuf);
   CMCHKPK(SPkU32, param->dlBw, mBuf);

   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkLysCellCfgInfo 
*
*
*     Desc : LysCellCfgInfo 
   Structure holding configuration parameters for CELL Initialization 
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkLysCellCfgInfo
(
LysCellCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkLysCellCfgInfo(param, mBuf)
LysCellCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsEtmCfg);

   CMCHKPK(SPkS16, param->priSigPwr, mBuf);
   CMCHKPK(SPkS16, param->secSigPwr, mBuf);
   CMCHKPK(SPkU32, param->period, mBuf);
   CMCHKPK(SPkU32, param->counter, mBuf);
   CMCHKPK(SPkU16, param->opMode, mBuf);
   CMCHKPK(cmPkLysSrsUlCfgInfo, &param->srsUlCfg, mBuf);
   CMCHKPK(cmPkLysPdschCfgInfo, &param->pdschCfg, mBuf);
   CMCHKPK(cmPkLysPrachCfgInfo, &param->prachCfg, mBuf);
   CMCHKPK(cmPkLysAntennaCfgInfo, &param->antennaCfg, mBuf);
   CMCHKPK(cmPkLysTxSchemeCfg, &param->txCfg, mBuf);
   CMCHKPK(cmPkLysBwCfgInfo, &param->bwCfg, mBuf);
   CMCHKPK(SPkU8, param->physCellId, mBuf);
   CMCHKPK(SPkU8, param->cellIdGrpId, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func: cmUnpkLysBwCfgInfo
*
*
*     Desc:   Bandwidth Configuration
 * @details This structure contains the uplink and downlink bandwidth 
 *          information for configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkLysBwCfgInfo
(
LysBwCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysBwCfgInfo(param, mBuf)
LysBwCfgInfo *param;
Buffer *mBuf;
#endif
{

   U32 tmpEnum;
   TRC3(cmUnpkLysBwCfgInfo)

   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->dlBw = tmpEnum;
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->ulBw = tmpEnum;
   CMCHKUNPK(SUnpkU8, &param->eUtraBand, mBuf);
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func: cmUnpkLysTxSchemeCfg
*
*
*     Desc:   Transmission Scheme Configuration
 * @details This structure contains the transmission scheme related information.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkLysTxSchemeCfg
(
LysTxSchemeCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysTxSchemeCfg(param, mBuf)
LysTxSchemeCfg *param;
Buffer *mBuf;
#endif
{
   U32 tmpEnum;

   TRC3(cmUnpkLysTxSchemeCfg)

   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->duplexMode = tmpEnum;
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->scSpacing = tmpEnum;
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->cycPfx = tmpEnum;
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func: cmUnpkLysAntennaCfgInfo
*
*
*     Desc:   Antenna Ports configuration
 * @details This structure contains the antenna configuration information for 
 *          configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkLysAntennaCfgInfo
(
LysAntennaCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysAntennaCfgInfo(param, mBuf)
LysAntennaCfgInfo *param;
Buffer *mBuf;
#endif
{
   U32 tmpEnum;

   TRC3(cmUnpkLysAntennaCfgInfo)
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->antPortsCnt = tmpEnum;
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func: cmUnpkLysPrachCfgInfo
*
*
*     Desc:   PRACH configuration
 * @details This structure contains the configuration information for PRACH at PHY.
 *          -# PRACH preamble sequences are generated by PHY using Zadoff-Chu 
 *             sequences.[Ref: 36.211, 5.7.2]
 *          -# PRACH preamble format is derived from PRACH Configuration Index.
 *             [Ref: 36.211, Table 5.7.1-2]
 *          -# PrachFreqOffset is the first physical resource block allocated to 
 *             the PRACH opportunity considered for preamble format 0, 1, 2, and 3.
 *             [Ref: 36.211, 5.7.1]
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkLysPrachCfgInfo
(
LysPrachCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysPrachCfgInfo(param, mBuf)
LysPrachCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkLysPrachCfgInfo)

   CMCHKUNPK(SUnpkU8, &param->pres, mBuf);
   if(param->pres != FALSE)
   {
      CMCHKUNPK(SUnpkU16, &param->rootSequenceIndex, mBuf);
      CMCHKUNPK(SUnpkU8, &param->prachCfgIndex, mBuf);
      CMCHKUNPK(SUnpkU8, &param->zeroCorrelationZoneCfg, mBuf);
      CMCHKUNPK(SUnpkU8, &param->highSpeedFlag, mBuf);
      CMCHKUNPK(SUnpkU8, &param->prachFreqOffset, mBuf);
   }
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func: cmUnpkLysPdschCfgInfo
*
*
*     Desc:   PDSCH configuration
 * @details This structure contains the PDSCH configuration information for 
 *          configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkLysPdschCfgInfo
(
LysPdschCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysPdschCfgInfo(param, mBuf)
LysPdschCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkLysPdschCfgInfo)

   CMCHKUNPK(SUnpkU8, &param->pres, mBuf);
   if(param->pres != FALSE)
   {
     CMCHKUNPK(SUnpkS16, &param->refSigPwr, mBuf);
     CMCHKUNPK(SUnpkU8, &param->p_b, mBuf);
   }
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func: cmUnpkLysSrsUlCfgInfo
*
*
*     Desc:   SRS uplink configuration
 * @details This structure contains the information for setting-up/release
 *          of uplink SRS configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkLysSrsUlCfgInfo
(
LysSrsUlCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysSrsUlCfgInfo(param, mBuf)
LysSrsUlCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkLysSrsUlCfgInfo)

   CMCHKUNPK(SUnpkU8, &param->pres, mBuf);
   if(param->pres != FALSE)
   {
      CMCHKUNPK(SUnpkU8, &param->srsCfgType, mBuf);
      CMCHKUNPK(SUnpkU8, &param->srsSetup.srsBw, mBuf);
      CMCHKUNPK(SUnpkU8, &param->srsSetup.sfCfg, mBuf);
      CMCHKUNPK(SUnpkU8, &param->srsSetup.srsANSimultTx, mBuf);
      CMCHKUNPK(SUnpkU8, &param->srsSetup.srsMaxUpPts, mBuf);
   }
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func: cmUnpkLysCellCfgInfo
*
*
*     Desc:   Cell Configuration Information
 * @details This structure contains the information for setting-up
 *          of a cell and its associated resources at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkLysCellCfgInfo
(
LysCellCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysCellCfgInfo(param, mBuf)
LysCellCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkLysCellCfgInfo)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->cellIdGrpId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->physCellId, mBuf);
   CMCHKUNPK(cmUnpkLysBwCfgInfo, &param->bwCfg, mBuf);
   CMCHKUNPK(cmUnpkLysTxSchemeCfg, &param->txCfg, mBuf);
   CMCHKUNPK(cmUnpkLysAntennaCfgInfo, &param->antennaCfg, mBuf);
   CMCHKUNPK(cmUnpkLysPrachCfgInfo, &param->prachCfg, mBuf);
   CMCHKUNPK(cmUnpkLysPdschCfgInfo, &param->pdschCfg, mBuf);
   CMCHKUNPK(cmUnpkLysSrsUlCfgInfo, &param->srsUlCfg, mBuf);
   /* UnPacking PHY configuration parameters */
   CMCHKUNPK(SUnpkU16, &param->opMode, mBuf);
   CMCHKUNPK(SUnpkU32, &param->counter, mBuf);
   CMCHKUNPK(SUnpkU32, &param->period, mBuf);
   CMCHKUNPK(SUnpkS16, &param->priSigPwr, mBuf);
   CMCHKUNPK(SUnpkS16, &param->secSigPwr, mBuf);

   RETVALUE(ROK);
}
#endif /* E_TM */


/***********************************************************
*
*     Func : cmPkYsCfg
*
*
*     Desc : ysCfg
   Structure holding configuration parameters for CL
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsCfg
(
YsCfg *param,
S16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsCfg(param, elmnt, mBuf)
YsCfg *param;
S16 elmnt;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsCfg);

   switch(elmnt) {
      case STCTFSAP:
         CMCHKPK(cmPkYsCtfSapCfg, &param->s.ctfSap, mBuf);
         break;
      case STTFUSAP:
         CMCHKPK(cmPkYsTfuSapCfg, &param->s.tfuSap, mBuf);
         break;
      case STGEN:
         CMCHKPK(cmPkYsGenCfg, &param->s.genCfg, mBuf);
         break;
#ifdef E_TM
      case STETMCELL: 
         CMCHKPK(cmPkLysCellCfgInfo, &param->s.cellCfg, mBuf);
         break;
      case STETM: 
         CMCHKPK(cmPkYsEtmCfg, &param->s.etmCfg, mBuf);
         break;
#endif /* E_TM */ 
      default :
         break;
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkYsCfg
*
*
*     Desc : ysCfg
   Structure holding configuration parameters for CL
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsCfg
(
YsCfg *param,
S16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsCfg(param, elmnt, mBuf)
YsCfg *param;
S16 elmnt;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsCfg);

   switch(elmnt) {
      case STGEN:
         CMCHKUNPK(cmUnpkYsGenCfg, &param->s.genCfg, mBuf);
         break;
      case STTFUSAP:
         CMCHKUNPK(cmUnpkYsTfuSapCfg, &param->s.tfuSap, mBuf);
         break;
      case STCTFSAP:
         CMCHKUNPK(cmUnpkYsCtfSapCfg, &param->s.ctfSap, mBuf);
         break;
#ifdef E_TM
      case STETMCELL: 
          CMCHKUNPK(cmUnpkLysCellCfgInfo, &param->s.cellCfg, mBuf);
         break;
      case STETM: 
          CMCHKUNPK(cmUnpkYsEtmCfg, &param->s.etmCfg, mBuf);
         break;
#endif /* E_TM */ 
      default :
         break;
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkYsSapSta
*
*
*     Desc : ysSapSta
   Structure holding a SAP's status information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsSapSta
(
YsSapSta *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsSapSta(param, mBuf)
YsSapSta *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsSapSta);

   CMCHKPK(SPkU8, param->sapState, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkYsSapSta
*
*
*     Desc : ysSapSta
   Structure holding a SAP's status information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsSapSta
(
YsSapSta *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsSapSta(param, mBuf)
YsSapSta *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsSapSta);

   CMCHKUNPK(SUnpkU8, &param->sapState, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkYsSts
*
*
*     Desc : ysSts
   Structure holding CL's statistical Information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsSts
(
YsSts *param,
S16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsSts(param, elmnt, mBuf)
YsSts *param;
S16 elmnt;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsSts);

   switch(elmnt) {
      case STL1PHY:
         CMCHKPK(cmPkYsPhySts, &param->s.phySts, mBuf);
         break;
      case STTFUSAP:
         CMCHKPK(cmPkYsTfuSapSts, &param->s.tfuSts, mBuf);
         break;
      case STCTFSAP:
         CMCHKPK(cmPkYsCtfSapSts, &param->s.ctfSts, mBuf);
         break;
      default :
         break;
   }
   CMCHKPK(SPkS16, param->action, mBuf);
   CMCHKPK(SPkU8, param->sapInst, mBuf);
   CMCHKPK(cmPkDateTime, &param->dt, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkYsSts
*
*
*     Desc : ysSts
   Structure holding CL's statistical Information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsSts
(
YsSts *param,
S16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsSts(param, elmnt, mBuf)
YsSts *param;
S16 elmnt;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsSts);

   CMCHKUNPK(cmUnpkDateTime, &param->dt, mBuf);
   CMCHKUNPK(SUnpkU8, &param->sapInst, mBuf);
   CMCHKUNPK(SUnpkS16, &param->action, mBuf);
   switch(elmnt) {
      case STCTFSAP:
         CMCHKUNPK(cmUnpkYsCtfSapSts, &param->s.ctfSts, mBuf);
         break;
      case STTFUSAP:
         CMCHKUNPK(cmUnpkYsTfuSapSts, &param->s.tfuSts, mBuf);
         break;
      case STL1PHY:
         CMCHKPK(cmUnpkYsPhySts, &param->s.phySts, mBuf);
         break;
      default :
         break;
   }
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkYsSsta
*
*
*     Desc : ysSsta
   Structure holding CL's solicited status information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsSsta
(
Pst *pst,
YsSsta *param,
S16 elmnt,
U8 eventType,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsSsta(pst, param, elmnt,eventType, mBuf)
Pst *pst;
YsSsta *param;
S16 elmnt;
U8 eventType;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsSsta);

   switch(elmnt) {
      case STL1PHY:
         CMCHKPK(SPkU8, param->s.phyState,mBuf);
         break;
      case STCTFSAP:
         CMCHKPK(cmPkYsSapSta, &param->s.ctfSapSta, mBuf);
         break;
      case STTFUSAP:
         CMCHKPK(cmPkYsSapSta, &param->s.tfuSapSta, mBuf);
         break;
      case STGEN:
         /*lys_c_001.main_2 : ccpu00118324 system id packing/unpacking done on confirm event */
         if( eventType == EVTLYSSSTACFM)
         {
            CMCHKPK(cmPkSystemId, &param->s.sysId, mBuf);
            if (param->s.sysId.ptNmb != NULLP)
            {
               SPutSBuf(pst->region, pst->pool, (Data *)param->s.sysId.ptNmb, LYS_PT_NUM_SIZE);
            }
         }
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
*     Func : cmUnpkYsSsta
*
*
*     Desc : ysSsta
   Structure holding CL's solicited status information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsSsta
(
Pst *pst,
YsSsta *param,
S16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsSsta(pst, param, elmnt, mBuf)
Pst *pst;
YsSsta *param;
S16 elmnt;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsSsta);

   CMCHKUNPK(cmUnpkDateTime, &param->dt, mBuf);
   CMCHKUNPK(SUnpkU8, &param->sapInst, mBuf);
   switch(elmnt) {
      case STGEN:
         /*lys_c_001.main_2 : ccpu00118324 system id packing/unpacking done on confirm event */
         if(pst->event == EVTLYSSSTACFM)
         {
            SGetSBuf(pst->region, pst->pool, (Data **)&param->s.sysId.ptNmb, LYS_PT_NUM_SIZE);
            cmMemset((U8 *)param->s.sysId.ptNmb, 0, LYS_PT_NUM_SIZE);
            /* lys_c_001.main_1 */
            CMCHKUNPK(cmUnpkSystemId, &param->s.sysId, mBuf);
         }
         break;
      case STTFUSAP:
         CMCHKUNPK(cmUnpkYsSapSta, &param->s.tfuSapSta, mBuf);
         break;
      case STCTFSAP:
         CMCHKUNPK(cmUnpkYsSapSta, &param->s.ctfSapSta, mBuf);
         break;
      case STL1PHY:
         CMCHKUNPK(SUnpkU8, &param->s.phyState, mBuf);
         break;
      default :
         break;
   }
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkYsUstaDgn
*
*
*     Desc : ysUstaDgn 
   Alarm diagnostics structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsUstaDgn
(
YsUstaDgn *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsUstaDgn(param, mBuf)
YsUstaDgn *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsUstaDgn);

   switch(param->type) {
      case LYS_USTA_DGNVAL_SFN_SF:
         CMCHKPK(cmPkLteTimingInfo, &param->u.timingInfo, mBuf);
         break;
      case LYS_USTA_DGNVAL_SAP:
         CMCHKPK(SPkS16, param->u.sapId,mBuf);
         break;
      case LYS_USTA_DGNVAL_MEM:
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
*     Func : cmUnpkYsUstaDgn
*
*
*     Desc : ysUstaDgn 
   Alarm diagnostics structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsUstaDgn
(
YsUstaDgn *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsUstaDgn(param, mBuf)
YsUstaDgn *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsUstaDgn);

   CMCHKUNPK(SUnpkU8, &param->type, mBuf);
   switch(param->type) {
      case LYS_USTA_DGNVAL_MEM:
         CMCHKUNPK(cmUnpkMemoryId, &param->u.mem, mBuf);
         break;
      case LYS_USTA_DGNVAL_SAP:
         CMCHKUNPK(SUnpkS16, &param->u.sapId,mBuf);
         break;
      case LYS_USTA_DGNVAL_SFN_SF:
         CMCHKUNPK(cmUnpkLteTimingInfo, &param->u.timingInfo,mBuf);
         break;
      default :
         break;
   }
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkYsUsta
*
*
*     Desc : ysUsta
   Structure holding CL's Unsolicited status information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsUsta
(
YsUsta *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsUsta(param, mBuf)
YsUsta *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsUsta);

   CMCHKPK(cmPkYsUstaDgn, &param->dgn, mBuf);
   CMCHKPK(cmPkCmAlarm, &param->cmAlarm, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkYsUsta
*
*
*     Desc : ysUsta
   Structure holding CL's Unsolicited status information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsUsta
(
YsUsta *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsUsta(param, mBuf)
YsUsta *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsUsta);

   CMCHKUNPK(cmUnpkCmAlarm, &param->cmAlarm, mBuf);
   CMCHKUNPK(cmUnpkYsUstaDgn, &param->dgn, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkYsTrc
*
*
*     Desc : ysTrc
   Structure holding CL's Trace Indication information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsTrc
(
YsTrc *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsTrc(param, mBuf)
YsTrc *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsTrc);

   CMCHKPK(SPkU8, param->evnt, mBuf);
   CMCHKPK(cmPkDateTime, &param->dt, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkYsTrc
*
*
*     Desc : ysTrc
   Structure holding CL's Trace Indication information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsTrc
(
YsTrc *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsTrc(param, mBuf)
YsTrc *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsTrc);

   CMCHKUNPK(cmUnpkDateTime, &param->dt, mBuf);
   CMCHKUNPK(SUnpkU8, &param->evnt, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkYsDbgCntrl
*
*
*     Desc : ysDbgCntrl
   Structure holding CL's Debug Control information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsDbgCntrl
(
YsDbgCntrl *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsDbgCntrl(param, mBuf)
YsDbgCntrl *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsDbgCntrl);

   CMCHKPK(SPkU32, param->dbgMask, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkYsDbgCntrl
*
*
*     Desc : ysDbgCntrl
   Structure holding CL's Debug Control information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsDbgCntrl
(
YsDbgCntrl *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsDbgCntrl(param, mBuf)
YsDbgCntrl *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsDbgCntrl);

   CMCHKUNPK(SUnpkU32, &param->dbgMask, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkYsSapCntrl
*
*
*     Desc : ysSapCntrl
   Structure holding CL's SAP Control information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsSapCntrl
(
YsSapCntrl *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsSapCntrl(param, mBuf)
YsSapCntrl *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsSapCntrl);

   CMCHKPK(SPkS16, param->spId, mBuf);
   CMCHKPK(SPkS16, param->suId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkYsSapCntrl
*
*
*     Desc : ysSapCntrl
   Structure holding CL's SAP Control information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsSapCntrl
(
YsSapCntrl *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsSapCntrl(param, mBuf)
YsSapCntrl *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsSapCntrl);

   CMCHKUNPK(SUnpkS16, &param->suId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->spId, mBuf);
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkYsCntrl
*
*
*     Desc : ysCntrl
   Structure holding CL's Control information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsCntrl
(
YsCntrl *param,
S16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsCntrl(param, elmnt, mBuf)
YsCntrl *param;
S16 elmnt;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsCntrl);

   switch(elmnt) {
      case STGEN:
         switch( param->subAction )
         {
            case SADBG :
               CMCHKPK(cmPkYsDbgCntrl, &param->s.ysDbgCntrl, mBuf);
               break;
            case SATRC:
               CMCHKPK(SPkS16, param->s.trcLen, mBuf);
               break;
            case SASTOPL1:
               CMCHKPK(cmPkLteCellId, param->s.cellId, mBuf);
               break;
#ifdef SS_DIAG
            case SALOG:
               CMCHKPK(SPkU32,  param->s.logMask, mBuf);
               break;
#endif
#ifdef TENB_STATS
            case SAACNT:
               CMCHKPK(SPkU32, param->s.statsPer, mBuf);
               break;
#endif
            default:
               break;
         }
         break;
      case STTFUSAP:
      case STCTFSAP:
         switch(param->subAction)
         {
            default:
               CMCHKPK(cmPkYsSapCntrl, &param->s.ysSapCntrl, mBuf);
               break;
         }
      break;
#ifdef E_TM
      case STETM:
         switch( param->action )
         {
           default: 
              CMCHKPK(cmPkLteCellId, param->s.cellId, mBuf);
              break;
         }
         break;
#endif /* E_TM  */
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
*     Func : cmUnpkYsCntrl
*
*
*     Desc : ysCntrl
   Structure holding CL's Control information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsCntrl
(
YsCntrl *param,
S16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsCntrl(param, elmnt, mBuf)
YsCntrl *param;
S16 elmnt;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsCntrl);

   CMCHKUNPK(cmUnpkDateTime, &param->dt, mBuf);
   CMCHKUNPK(SUnpkU8, &param->action, mBuf);
   CMCHKUNPK(SUnpkU8, &param->subAction, mBuf);
   switch(elmnt)
   {
      case STGEN :
         switch( param->subAction )
         {
            case SADBG:
               CMCHKUNPK(cmUnpkYsDbgCntrl, &param->s.ysDbgCntrl,mBuf);
               break;
            case SATRC:
               CMCHKUNPK(SUnpkS16, &param->s.trcLen,mBuf);
               break;
            case SASTOPL1:
               CMCHKUNPK(cmUnpkLteCellId, &param->s.cellId, mBuf);
               break;
#ifdef SS_DIAG
            case SALOG:
               CMCHKUNPK(SUnpkU32, &param->s.logMask, mBuf);
               break;
#endif
#ifdef TENB_STATS
            case SAACNT:
               CMCHKUNPK(SUnpkU32, &param->s.statsPer, mBuf);
               break;
#endif
            default:
               break;
         }
         break;
      case STTFUSAP:
      case STCTFSAP:
         switch( param->subAction )
         {
            default:
               CMCHKUNPK(cmUnpkYsSapCntrl, &param->s.ysSapCntrl,mBuf);
               break;
         }
#ifdef E_TM
      case STETM:
         switch( param->action )
         {
           default: 
              CMCHKUNPK(cmUnpkLteCellId, &param->s.cellId, mBuf);
              break;
         }
         break;
#endif /* E_TM */
      default:
         break;
   }
   RETVALUE(ROK);
}

#ifdef TENB_T3K_SPEC_CHNGS
/***********************************************************
*
*     Func : cmPkYslogStrmInfo
*
*       Desc :YsCtfLogStrmInfo 
*      Structure holding CL's Log Stream Information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsLogStrmInfo
(
YsCtfLogStrmInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsLogStrmInfo(param, mBuf)
YsCtfLogStrmInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsLogStrmInfo);

   CMCHKPK(SPkU32, param->bufSize, mBuf);
   CMCHKPK(SPkU32, param->bufAddr, mBuf);
   CMCHKPK(SPkU8, param->stat, mBuf);
   CMCHKPK(SPkU8, param->logStrmInfoTyp, mBuf);

   RETVALUE(ROK);
}/*cmPkYsLogStrmInfo*/

/*watchdog changes*/
/***********************************************************
*
*     Func : cmPkYsLogStrmInfoCfm
*
*
*     Desc : YsCtfLogStrmInfoCfm
*   Structure holding CL's Log Stream Information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsLogStrmInfoCfm
(
YsCtfLogStrmInfoCfm *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsLogStrmInfo(param, mBuf)
YsCtfLogStrmInfoCfm *param;
Buffer *mBuf;
#endif
{
   U8  indx;
   TRC3(cmPkYsLogStrmInfoCfm);

   for(indx = 0; indx < param->numOfLogStrmInfo; indx++)
   {
      cmPkYsLogStrmInfo(&param->logStrmInfo[indx] ,mBuf);
   }
   CMCHKPK(SPkU8, param->numOfLogStrmInfo, mBuf);
   CMCHKPK(SPkU16, param->logStrmInfoReqType, mBuf);
   CMCHKPK(cmPkCmStatus, &param->status, mBuf);

   RETVALUE(ROK);
}/*cmPkYsLogStrmInfoCfm*/
/*watchdog changes*/

/***********************************************************
*
*     Func : cmUnpkYsLogStrmInfo
*
*
*     Desc : YsCtfLogStrmInfo
*   Structure holding CL's Log Stream Information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsLogStrmInfo
(
YsCtfLogStrmInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsLogStrmInfo(param, mBuf)
YsCtfLogStrmInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsLogStrmInfo);

   CMCHKUNPK(SUnpkU8, &param->logStrmInfoTyp, mBuf);
   CMCHKUNPK(SUnpkU8, &param->stat, mBuf);
   CMCHKUNPK(SUnpkU32, &param->bufAddr, mBuf);
   CMCHKUNPK(SUnpkU32, &param->bufSize, mBuf);

   RETVALUE(ROK);
}/*cmUnpkYsLogStrmInfo*/

/*watchdog changes*/


/***********************************************************
*
*     Func : cmUnpkYsLogStrmInfoCfm
*
*
*     Desc :YsCtfLogStrmInfoCfm
*   Structure holding CL's Log Stream Information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsLogStrmInfoCfm
(
YsCtfLogStrmInfoCfm *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsLogStrmInfoCfm(param mBuf)
YsCtfLogStrmInfoCfm *param;
Buffer *mBuf;
#endif
{
   U8 indx;
   TRC3(cmUnpkYsLogStrmInfoCfm);

   CMCHKUNPK(cmUnpkCmStatus, &param->status, mBuf);
   CMCHKUNPK(SUnpkU16, &param->logStrmInfoReqType, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numOfLogStrmInfo, mBuf); 
   for(indx = 0; indx < param->numOfLogStrmInfo; indx++)
   {
      cmUnpkYsLogStrmInfo(&param->logStrmInfo[indx], mBuf);
   } 

   RETVALUE(ROK);
}/*cmUnpkYsLogStrmInfoCfm*/

/*watchdog changes*/
/**
* @brief This API is used to send a log Stream info request from LM to CL.
*
* @details
*
*     Function : cmPkLysLogStrmInfoReq
*
*  @param[in]   Pst *  pst
*  @param[in]   Action  action
*  @param[in]   YsMngmt *  sts
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLysLogStrmInfoReq 
(
Pst * pst,
YsMngmt * logInfoReq
)
#else
PUBLIC S16 cmPkLysLogStrmInfoReq(pst, logInfoReq)
Pst * pst;
YsMngmt * logInfoReq;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLysLogStrmInfoReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
	    (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
	    (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)logInfoReq, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   if (cmPkYsMngmt(pst, logInfoReq, EVTLYSLOGINFOREQ, mBuf) != ROK) 
   {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
	    (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
	    (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)logInfoReq, sizeof(YsMngmt));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPutSBuf(pst->region, pst->pool, (Data *)logInfoReq, sizeof(YsMngmt))
	 != ROK) 
   {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
	    (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
	    (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTLYSLOGINFOREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}/*cmPkLysLogStrmInfoReq*/
/*watchdog changes*/


/**
* @brief This API is used to send a log stream info Request from LM to CL.
*
* @details
*
*     Function : cmUnpkLysLogStrmInfoReq
*
*  @param[in]   LysLogStrmInfoReq func
*  @param[in]   Pst *pst 
*  @param[in]   Buffer *mBuf
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLysLogStrmInfoReq
(
LysLogStrmInfoReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysLogInfoReq(func, pst, mBuf)
LysLogStrmInfoReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   YsMngmt *logInfo;

   TRC3(cmUnpkLysLogInfoReq)

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&logInfo, 
		  sizeof(YsMngmt))) != ROK) 
   {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
	    (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
	    (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmUnpkYsMngmt(pst, logInfo, EVTLYSLOGINFOREQ, mBuf) != ROK) 
   {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
	    (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
	    (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data *)logInfo, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, logInfo));
}/*cmUnpkLysLogStrmInfoReq*/
/*watchdog changes*/


/**
* @brief This API is used to send a Log Stream Info Confirm from CL to LM.
*
* @details
*
*     Function : cmPkLyslogInfoCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   YsCtfLogStrmInfoCfm *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLysLogStrmInfoCfm
(
Pst * pst,
YsCtfLogStrmInfoCfm * cfm
)
#else
PUBLIC S16 cmPkLysLogStrmInfoCfm(pst, cfm)
Pst * pst;
YsCtfLogStrmInfoCfm * cfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLysLogStrmInfoCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
	    (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
	    (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)cfm,
	    sizeof(YsCtfLogStrmInfoCfm));
      RETVALUE(RFAILED);
   }
   if (cmPkYsLogStrmInfoCfm(cfm, mBuf) != ROK) 
   { 
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
	    (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
	    (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsCtfLogStrmInfoCfm));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (SPutSBuf(pst->region, pst->pool, (Data *)cfm,
	    sizeof(YsCtfLogStrmInfoCfm)) != ROK) 
   {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
	    (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
	    (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTLYSLOGINFOCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}/*cmPkLysLogStrmInfoCfm*/
/*watchdog changes*/

/**
* @brief This API is used to send a log Stream Info Confirm from CL to LM.
*
* @details
*
*     Function : cmUnpkLysLogStrmInfoCfm
*
*  @param[in]   LysLogStrmInofCfm func
*  @param[in]   Pst *pst 
*  @param[in]   Buffer *  mBuf
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLysLogStrmInfoCfm
(
LysLogStrmInfoCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysLogStrmInfoCfm(func, pst, mBuf)
LysLogStrmInfoCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   YsCtfLogStrmInfoCfm *cfm;

   TRC3(cmUnpkLysLogStrmInfoCfm)

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfm, 
		  sizeof(YsCtfLogStrmInfoCfm))) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
	    (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
	    (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmUnpkYsLogStrmInfoCfm(cfm ,mBuf) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
	    (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
	    (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsCtfLogStrmInfoCfm));
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cfm));
}/*cmUnpkLysLogStrmInfoCfm*/
#endif /* TENB_T3K_SPEC_CHNGS*/


/***********************************************************
*
*     Func : cmPkYsMngmt
*
*
*     Desc : ysMngmt
   Structure holding CL's Configuration and Control Management Information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsMngmt
(
Pst *pst,
YsMngmt *param,
U8 eventType,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsMngmt(pst, param, eventType, mBuf)
Pst *pst;
YsMngmt *param;
U8 eventType;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsMngmt);

   switch(eventType) {
      case EVTLYSCNTRLREQ:
      case EVTLYSCNTRLCFM:
         if (cmPkYsCntrl(&param->t.cntrl, param->hdr.elmId.elmnt, mBuf) != ROK)
            RETVALUE(RFAILED);
         break;
      case EVTLYSTRCIND:
         CMCHKPK(cmPkYsTrc, &param->t.trc, mBuf);
         break;
      case EVTLYSUSTAIND:
         CMCHKPK(cmPkYsUsta, &param->t.usta, mBuf);
         break;
      case EVTLYSSSTACFM:
      case EVTLYSSSTAREQ:
         /*lys_c_001.main_2 : ccpu00118324 system id packing/unpacking done on confirm event */
         if (cmPkYsSsta(pst, &param->t.ssta, param->hdr.elmId.elmnt,eventType, mBuf) != ROK)
            RETVALUE(RFAILED);
         break;
      case EVTLYSSTSCFM:
      case EVTLYSSTSREQ:
         if (cmPkYsSts(&param->t.sts, param->hdr.elmId.elmnt, mBuf) != ROK)
            RETVALUE(RFAILED);
         break;
      case EVTLYSCFGREQ:
      case EVTLYSCFGCFM:
         if (cmPkYsCfg(&param->t.cfg, param->hdr.elmId.elmnt, mBuf) != ROK)
            RETVALUE(RFAILED);
         break;
#ifdef TENB_T3K_SPEC_CHNGS
      case EVTLYSLOGINFOREQ:
           break;
#endif /* TENB_T3K_SPEC_CHNGS*/
      default :
         RETVALUE(RFAILED);
   }
   CMCHKPK(cmPkCmStatus, &param->cfm, mBuf);
   CMCHKPK(cmPkHeader, &param->hdr, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkYsMngmt
*
*
*     Desc : ysMngmt
   Structure holding CL's Configuration and Control Management Information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsMngmt
(
Pst *pst,
YsMngmt *param,
U8 eventType,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsMngmt(pst, param, eventType, mBuf)
Pst *pst;
YsMngmt *param;
U8 eventType;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsMngmt);

   CMCHKUNPK(cmUnpkHeader, &param->hdr, mBuf);
   CMCHKUNPK(cmUnpkCmStatus, &param->cfm, mBuf);
   switch(eventType) {
      case EVTLYSCFGREQ:
      case EVTLYSCFGCFM:
         if (cmUnpkYsCfg(&param->t.cfg, param->hdr.elmId.elmnt, mBuf) != ROK)
            RETVALUE(RFAILED);
         break;
      case EVTLYSSTSCFM:
      case EVTLYSSTSREQ:
         if (cmUnpkYsSts(&param->t.sts, param->hdr.elmId.elmnt, mBuf) != ROK)
            RETVALUE(RFAILED);
         break;
      case EVTLYSSSTACFM:
      case EVTLYSSSTAREQ:
         if (cmUnpkYsSsta(pst, &param->t.ssta, param->hdr.elmId.elmnt, mBuf) != ROK)
            RETVALUE(RFAILED);
         break;
      case EVTLYSUSTAIND:
         CMCHKUNPK(cmUnpkYsUsta, &param->t.usta, mBuf);
         break;
      case EVTLYSTRCIND:
         CMCHKUNPK(cmUnpkYsTrc, &param->t.trc, mBuf);
         break;
      case EVTLYSCNTRLREQ:
      case EVTLYSCNTRLCFM:
         if (cmUnpkYsCntrl(&param->t.cntrl, param->hdr.elmId.elmnt, mBuf) != ROK)
            RETVALUE(RFAILED);
         break;
#ifdef TENB_T3K_SPEC_CHNGS
      case EVTLYSLOGINFOREQ:
          break;
#endif /* TENB_T3K_SPEC_CHNGS*/
      default :
         RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}

/**
* @brief This API is used to send a 
REM Scan Config Request from LM to CL.
*
* @details
*
*     Function : cmPkLysTPMRefSigPwrChangeReq
*
*  @param[in]   Pst *  pst
*  @param[in]   U16 remScanInterval 
*  @param[in]   U16 remScanCount 
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLysTPMRefSigPwrChangeReq
(
Pst *pst,
S16 refSigPwr 
)
#else
PUBLIC S16 cmPkLysTPMRefSigPwrChangeReq(pst, refSigPwr)
Pst *pst;
S16 refSigPwr; 
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLysTPMRefSigPwrChangeReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      RETVALUE(RFAILED);
   }

   CMCHKPK(SPkS16, refSigPwr, mBuf);
   pst->event = (Event) EVTLYSTPMPWRCHGREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

/**
* @brief This API is used to send a 
Unpack REM Scan Config Request received from LM.
*
* @details
*
*     Function : cmUnPkLysTPMRefSigPwrChangeReq
*
*  @param[in]   Pst *  pst
*  @param[in]   U16 remScanInterval 
*  @param[in]   U16 remScanCount 
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnPkLysTPMRefSigPwrChangeReq
(
LysTPMRefSigPwrChangeReq func,
Pst    *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnPkLysTPMRefSigPwrChangeReq(func, pst, mBuf)
LysTPMRefSigPwrChangeReq func;
Pst    *pst;
Buffer *mBuf;
#endif
{
   S16 ret = ROK;
   S16 refSigPwr;
   TRC3(cmUnPkLysTPMRefSigPwrChangeReq)

   CMCHKUNPK(SUnpkS16, &refSigPwr, mBuf);
   
   SPutMsg(mBuf);
   ret = (*func)(pst,refSigPwr);
   RETVALUE(ret);
}


/**
* @brief This API is used to send a 
REM Scan Config Request from LM to CL.
*
* @details
*
*     Function : cmPkLysREMScanCfgReq
*
*  @param[in]   Pst *  pst
*  @param[in]   U16 remScanInterval 
*  @param[in]   U16 remScanCount 
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLysREMScanCfgReq
(
Pst *pst,
U16 remScanInterval,        
U16 remScanCount            
)
#else
PUBLIC S16 cmPkLysREMScanCfgReq(pst, remScanInterval, remScanCount)
Pst *pst;
U16 remScanInterval;        
U16 remScanCount;            
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLysREMScanCfgReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      RETVALUE(RFAILED);
   }
   CMCHKPK(SPkU16, remScanInterval, mBuf);
   CMCHKPK(SPkU16, remScanCount, mBuf);
   pst->event = (Event) EVTLYSPERDREMSCAN;
   RETVALUE(SPstTsk(pst,mBuf));
}

/**
* @brief This API is used to send a 
Unpack REM Scan Config Request received from LM.
*
* @details
*
*     Function : cmUnpkLysREMScanCfgReq
*
*  @param[in]   Pst *  pst
*  @param[in]   U16 remScanInterval 
*  @param[in]   U16 remScanCount 
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLysREMScanCfgReq
(
LysREMScanCfgReq func,
Pst    *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysREMScanCfgReq(func, pst, mBuf)
LysREMScanCfgReq func;
Pst    *pst;
Buffer *mBuf;
#endif
{
   U16 remScanCount;
   U16 remScanInterval;
   S16 ret = ROK;
   TRC3(cmUnpkLysREMScanCfgReq)

   CMCHKUNPK(SUnpkU16, &remScanCount, mBuf);
   CMCHKUNPK(SUnpkU16, &remScanInterval, mBuf);
   
   SPutMsg(mBuf);
   ret = (*func)(pst,remScanInterval,remScanCount);
   RETVALUE(ret);
}

#endif

/**********************************************************************
 
         End of file:     lys.c@@/main/3 - Tue Aug 30 18:10:39 2011
 
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
/main/1      ---     pk                1. Initial Release.
/main/2      ---      lys_c_001.main_1 apany      1. Minor fixes and additional PHY info
/main/3      ---      lys_c_001.main_2 ms           1. system id packing/unpacking done on confirm event.
*********************************************************************91*/
