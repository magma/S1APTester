

/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for pack/unpack of CRG interface primitives. 
  
     File:     crg.c 
  
     Sid:      crg.c@@/main/6 - Wed Jul 27 12:49:15 2011
  
     Prg:      sm
  
**********************************************************************/

/** @file crg.c
@brief This file contains the packing/unpacking code for the CRG interface 
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
#include "crg.h"           /* CRG Interface defines */

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_lib.x"        /* Common Library Definitions */
#include "cm_hash.x"       /* Common Hash List Definitions */
#include "cm_lte.x"        /* Common LTE Defines */
#include "crg.x"           /* CRG Interface includes */


#ifdef LCCRG

/**
* @brief Request from RRC to MAC to bind the interface saps
*
* @details
*
*     Function : cmPkCrgBndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   SpId  spId
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkCrgBndReq
(
Pst* pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 cmPkCrgBndReq(pst, suId, spId)
Pst* pst;
SuId suId;
SpId spId;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCrgBndReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG001, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG002, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG003, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTCRGBNDREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief Request from RRC to MAC to bind the interface saps
*
* @details
*
*     Function : cmUnpkCrgBndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   SpId  spId
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkCrgBndReq
(
CrgBndReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCrgBndReq(func, pst, mBuf)
CrgBndReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   SpId spId;
   
   TRC3(cmUnpkCrgBndReq)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG004, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG005, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, spId));
}


/**
* @brief Confirmation from MAC to RRC for the bind/Unbind 
 * request for the interface saps
*
* @details
*
*     Function : cmPkCrgBndCfm
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   U8  status
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkCrgBndCfm
(
Pst* pst,
SuId suId,
U8 status
)
#else
PUBLIC S16 cmPkCrgBndCfm(pst, suId, status)
Pst* pst;
SuId suId;
U8 status;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCrgBndCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG006, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SPkU8(status, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG007, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG008, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTCRGBNDCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief Confirmation from MAC to RRC for the bind/Unbind 
 * request for the interface saps
*
* @details
*
*     Function : cmUnpkCrgBndCfm
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   U8  status
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkCrgBndCfm
(
CrgBndCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCrgBndCfm(func, pst, mBuf)
CrgBndCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   U8 status;
   
   TRC3(cmUnpkCrgBndCfm)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG009, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkU8(&status, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG010, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, status));
}


/**
* @brief Request from RRC to MAC to Unbind the interface saps
*
* @details
*
*     Function : cmPkCrgUbndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   Reason  reason
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkCrgUbndReq
(
Pst* pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 cmPkCrgUbndReq(pst, spId, reason)
Pst* pst;
SpId spId;
Reason reason;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCrgUbndReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG011, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SPkS16(reason, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG012, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG013, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTCRGUBNDREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief Request from RRC to MAC to Unbind the interface saps
*
* @details
*
*     Function : cmUnpkCrgUbndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   Reason  reason
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkCrgUbndReq
(
CrgUbndReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCrgUbndReq(func, pst, mBuf)
CrgUbndReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   Reason reason;
   
   TRC3(cmUnpkCrgUbndReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG014, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkS16(&reason, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG015, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, reason));
}


/**
* @brief Configuration Request from RRC to MAC for 
 * configuring Cell/Ue/Lc
*
* @details
*
*     Function : cmPkCrgCfgReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   CrgCfgTransId  transId
*  @param[in]   CrgCfgReqInfo  *  cfgReqInfo
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkCrgCfgReq
(
Pst* pst,
SpId spId,
CrgCfgTransId transId,
CrgCfgReqInfo  * cfgReqInfo
)
#else
PUBLIC S16 cmPkCrgCfgReq(pst, spId, transId, cfgReqInfo)
Pst* pst;
SpId spId;
CrgCfgTransId transId;
CrgCfgReqInfo  * cfgReqInfo;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCrgCfgReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG016, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)cfgReqInfo, sizeof(CrgCfgReqInfo));
      RETVALUE(RFAILED);
   }
   if (cmPkCrgCfgReqInfo(cfgReqInfo, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG017, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)cfgReqInfo, sizeof(CrgCfgReqInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
/* crg_c_001.main_5: MOD - Updating ERR code */
   if (cmPkCrgCfgTransId(&transId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG018, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)cfgReqInfo, sizeof(CrgCfgReqInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG019, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)cfgReqInfo, sizeof(CrgCfgReqInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPutSBuf(pst->region, pst->pool, (Data *)cfgReqInfo, sizeof(CrgCfgReqInfo)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG020, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTCRGCFGREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief Configuration Request from RRC to MAC for 
 * configuring Cell/Ue/Lc
*
* @details
*
*     Function : cmUnpkCrgCfgReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   CrgCfgTransId  transId
*  @param[in]   CrgCfgReqInfo  *  cfgReqInfo
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkCrgCfgReq
(
CrgCfgReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCrgCfgReq(func, pst, mBuf)
CrgCfgReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   CrgCfgTransId transId;
   CrgCfgReqInfo *cfgReqInfo;
   
   TRC3(cmUnpkCrgCfgReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG021, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmUnpkCrgCfgTransId(&transId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG022, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfgReqInfo, sizeof(CrgCfgReqInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG023, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
    
   if (cmUnpkCrgCfgReqInfo(cfgReqInfo, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)cfgReqInfo, sizeof(CrgCfgReqInfo));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG024, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, transId, cfgReqInfo));
}


/**
* @brief Configuration Confirm from MAC to RRC
*
* @details
*
*     Function : cmPkCrgCfgCfm
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   CrgCfgTransId  transId
*  @param[in]   U8  status
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkCrgCfgCfm
(
Pst* pst,
SuId suId,
CrgCfgTransId transId,
U8 status
)
#else
PUBLIC S16 cmPkCrgCfgCfm(pst, suId, transId, status)
Pst* pst;
SuId suId;
CrgCfgTransId transId;
U8 status;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCrgCfgCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG025, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
/* crg_c_001.main_5 - ADD - Added the packing for status. */
   if (SPkU8(status, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG026, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmPkCrgCfgTransId(&transId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG027, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG028, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTCRGCFGCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief Configuration Confirm from MAC to RRC
*
* @details
*
*     Function : cmUnpkCrgCfgCfm
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   CrgCfgTransId  transId
*  @param[in]   U8  status
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkCrgCfgCfm
(
CrgCfgCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCrgCfgCfm(func, pst, mBuf)
CrgCfgCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   CrgCfgTransId transId;
   U8 status;
   
   TRC3(cmUnpkCrgCfgCfm)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG029, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmUnpkCrgCfgTransId(&transId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG030, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkU8(&status, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECRG031, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, transId, status));
}


/***********************************************************
*
*     Func : cmPkCrgCfgTransId
*
*
*     Desc : Transaction ID between MAC and RRC
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCrgCfgTransId
(
CrgCfgTransId *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCrgCfgTransId(param, mBuf)
CrgCfgTransId *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkCrgCfgTransId)

   for (i=CRG_CFG_TRANSID_SIZE-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->trans[i], mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCrgCfgTransId
*
*
*     Desc : Transaction ID between MAC and RRC
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCrgCfgTransId
(
CrgCfgTransId *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCrgCfgTransId(param, mBuf)
CrgCfgTransId *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkCrgCfgTransId)

   for (i=0; i<CRG_CFG_TRANSID_SIZE; i++) {
      CMCHKUNPK(SUnpkU8, &param->trans[i], mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCrgBwCfg
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
PUBLIC S16 cmPkCrgBwCfg
(
CrgBwCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCrgBwCfg(param, mBuf)
CrgBwCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCrgBwCfg)

   CMCHKPK(SPkU8, param->ulTotalBw, mBuf);
   CMCHKPK(SPkU8, param->dlTotalBw, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCrgBwCfg
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
PUBLIC S16 cmUnpkCrgBwCfg
(
CrgBwCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCrgBwCfg(param, mBuf)
CrgBwCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCrgBwCfg)

   CMCHKUNPK(SUnpkU8, &param->dlTotalBw, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ulTotalBw, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCrgRachCfg
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
PUBLIC S16 cmPkCrgRachCfg
(
CrgRachCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCrgRachCfg(param, mBuf)
CrgRachCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCrgRachCfg)

   CMCHKPK(SPkU8, param->maxMsg3Tx, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCrgRachCfg
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
PUBLIC S16 cmUnpkCrgRachCfg
(
CrgRachCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCrgRachCfg(param, mBuf)
CrgRachCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCrgRachCfg)

   CMCHKUNPK(SUnpkU8, &param->maxMsg3Tx, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCrgCellCfg
*
*
*     Desc : Cell configuration
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCrgCellCfg
(
CrgCellCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCrgCellCfg(param, mBuf)
CrgCellCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCrgCellCfg)

#ifdef TENB_MULT_CELL_SUPPRT
   CMCHKPK(SPkS16, param->rguDlSapId, mBuf);
   CMCHKPK(SPkS16, param->rguUlSapId, mBuf);
#endif
   CMCHKPK(cmPkCrgBwCfg, &param->bwCfg, mBuf);
   CMCHKPK(cmPkCrgRachCfg, &param->rachCfg, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCrgCellCfg
*
*
*     Desc : Cell configuration
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCrgCellCfg
(
CrgCellCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCrgCellCfg(param, mBuf)
CrgCellCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCrgCellCfg)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkCrgRachCfg, &param->rachCfg, mBuf);
   CMCHKUNPK(cmUnpkCrgBwCfg, &param->bwCfg, mBuf);
#ifdef TENB_MULT_CELL_SUPPRT
   CMCHKUNPK(SUnpkS16, &param->rguUlSapId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->rguDlSapId, mBuf);
#endif
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCrgUeUlHqCfg
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
PUBLIC S16 cmPkCrgUeUlHqCfg
(
CrgUeUlHqCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCrgUeUlHqCfg(param, mBuf)
CrgUeUlHqCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCrgUeUlHqCfg)

   CMCHKPK(SPkU8, param->maxUlHqTx, mBuf);
   RETVALUE(ROK);
}

#ifdef LTE_ADV
/***********************************************************
*
*     Func : cmPkCrgUeSCellCfg
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
PRIVATE S16 cmPkCrgUeSCellCfg
(
CrgUeSCellInfo *param,
Buffer *mBuf
)
#else
PRIVATE S16 cmPkCrgUeSCellCfg(param, mBuf)
CrgUeSCellInfo *param;
Buffer *mBuf;
#endif
{
   CMCHKPK(SPkS16, param->rguDlSapId, mBuf);
   CMCHKPK(SPkS16, param->rguUlSapId, mBuf);
   CMCHKPK(SPkU8, param->macInst, mBuf);
   CMCHKPK(SPkU16, param->sCellId, mBuf);

   RETVALUE(ROK);
}
/***********************************************************
*
*     Func : cmUnpkCrgUeSCellCfg
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
PRIVATE S16 cmUnpkCrgUeSCellCfg
(
CrgUeSCellInfo *param,
Buffer *mBuf
)
#else
PRIVATE S16 cmUnpkCrgUeSCellCfg(param, mBuf)
CrgUeSCellInfo *param;
Buffer *mBuf;
#endif
{
   CMCHKUNPK(SUnpkU16, &param->sCellId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->macInst, mBuf);
   CMCHKUNPK(SUnpkS16, &param->rguUlSapId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->rguDlSapId, mBuf);
   RETVALUE(ROK);
}
/***********************************************************
*
*     Func : cmPkCrgUeSecCellInfo
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
PUBLIC S16 cmPkCrgUeSecCellInfo
(
CrgUeSecCellInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCrgUeSecCellInfo(param, mBuf)
CrgUeSecCellInfo *param;
Buffer *mBuf;
#endif
{
   S8 idx;
   for(idx = param->numSCells - 1; idx >= 0; idx--)
   {
      CMCHKPK(cmPkCrgUeSCellCfg, &param->ueSCellCfg[(U8)idx], mBuf);
   }

   CMCHKPK(SPkU8, param->numSCells, mBuf);
   CMCHKPK(SPkU8, param->isSCellCfgPres, mBuf);

   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmUnpkCrgUeSecCellInfo
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
PUBLIC S16 cmUnpkCrgUeSecCellInfo
(
CrgUeSecCellInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCrgUeSecCellInfo(param, mBuf)
CrgUeSecCellInfo *param;
Buffer *mBuf;
#endif
{
   U8 idx;

   CMCHKUNPK(SUnpkU8, &param->isSCellCfgPres, mBuf);
   if(TRUE == param->isSCellCfgPres)
   {
      CMCHKUNPK(SUnpkU8, &param->numSCells, mBuf);

      for(idx = 0; idx < param->numSCells; idx++)
      {
         CMCHKUNPK(cmUnpkCrgUeSCellCfg, &param->ueSCellCfg[idx],mBuf);
      }
   }

   RETVALUE(ROK);
}

#endif /* LTE_ADV */


/***********************************************************
*
*     Func : cmUnpkCrgUeUlHqCfg
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
PUBLIC S16 cmUnpkCrgUeUlHqCfg
(
CrgUeUlHqCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCrgUeUlHqCfg(param, mBuf)
CrgUeUlHqCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCrgUeUlHqCfg)

   CMCHKUNPK(SUnpkU8, &param->maxUlHqTx, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCrgUeCfg
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
PUBLIC S16 cmPkCrgUeCfg
(
CrgUeCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCrgUeCfg(param, mBuf)
CrgUeCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCrgUeCfg)
#ifdef TENB_MULT_CELL_SUPPRT
   CMCHKPK(SPkS16, param->rguDlSapId, mBuf);
   CMCHKPK(SPkS16, param->rguUlSapId, mBuf);
#endif
   CMCHKPK(SPkU32, param->txMode.tm, mBuf);
   CMCHKPK(SPkU8, param->txMode.pres, mBuf);
   CMCHKPK(cmPkCrgUeUlHqCfg, &param->ueUlHqCfg, mBuf);
   CMCHKPK(cmPkLteRnti, param->crnti, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCrgUeCfg
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
PUBLIC S16 cmUnpkCrgUeCfg
(
CrgUeCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCrgUeCfg(param, mBuf)
CrgUeCfg *param;
Buffer *mBuf;
#endif
{
   U32 tmpEnum;
   
   TRC3(cmUnpkCrgUeCfg)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &param->crnti, mBuf);
   CMCHKUNPK(cmUnpkCrgUeUlHqCfg, &param->ueUlHqCfg, mBuf);
   CMCHKUNPK(SUnpkU8, &param->txMode.pres, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpEnum, mBuf);
   param->txMode.tm = (CrgTxMode) tmpEnum;
#ifdef TENB_MULT_CELL_SUPPRT
   CMCHKUNPK(SUnpkS16, &param->rguUlSapId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->rguDlSapId, mBuf);
#endif
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCrgDlLchCfg
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
PUBLIC S16 cmPkCrgDlLchCfg
(
CrgDlLchCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCrgDlLchCfg(param, mBuf)
CrgDlLchCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCrgDlLchCfg)

   CMCHKPK(SPkU8, param->dlTrchType, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCrgDlLchCfg
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
PUBLIC S16 cmUnpkCrgDlLchCfg
(
CrgDlLchCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCrgDlLchCfg(param, mBuf)
CrgDlLchCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCrgDlLchCfg)

   CMCHKUNPK(SUnpkU8, &param->dlTrchType, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCrgUlLchCfg
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
PUBLIC S16 cmPkCrgUlLchCfg
(
CrgUlLchCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCrgUlLchCfg(param, mBuf)
CrgUlLchCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCrgUlLchCfg)

   CMCHKPK(SPkU8, param->lcgId, mBuf);
   CMCHKPK(SPkU8, param->ulTrchType, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCrgUlLchCfg
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
PUBLIC S16 cmUnpkCrgUlLchCfg
(
CrgUlLchCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCrgUlLchCfg(param, mBuf)
CrgUlLchCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCrgUlLchCfg)

   CMCHKUNPK(SUnpkU8, &param->ulTrchType, mBuf);
   CMCHKUNPK(SUnpkU8, &param->lcgId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCrgLchCfg
*
*
*     Desc : Logical channel configuration info for common and dedicated channels
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCrgLchCfg
(
CrgLchCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCrgLchCfg(param, mBuf)
CrgLchCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCrgLchCfg)
/* crg_c_001.main_5 - ADD - Added the packing for LTE_L2_MEAS. */
#ifdef LTE_L2_MEAS
   CMCHKPK(SPkU8, param->qci, mBuf);
#endif
   CMCHKPK(cmPkCrgUlLchCfg, &param->ulInfo, mBuf);
   CMCHKPK(cmPkCrgDlLchCfg, &param->dlInfo, mBuf);
   CMCHKPK(SPkU8, param->dir, mBuf);
   CMCHKPK(cmPkLteLcType, param->lcType, mBuf);
   CMCHKPK(cmPkLteLcId, param->lcId, mBuf);
   CMCHKPK(cmPkLteRnti, param->crnti, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCrgLchCfg
*
*
*     Desc : Logical channel configuration info for common and dedicated channels
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCrgLchCfg
(
CrgLchCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCrgLchCfg(param, mBuf)
CrgLchCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCrgLchCfg)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &param->crnti, mBuf);
   CMCHKUNPK(cmUnpkLteLcId, &param->lcId, mBuf);
   CMCHKUNPK(cmUnpkLteLcType, &param->lcType, mBuf);
   CMCHKUNPK(SUnpkU8, &param->dir, mBuf);
   CMCHKUNPK(cmUnpkCrgDlLchCfg, &param->dlInfo, mBuf);
   CMCHKUNPK(cmUnpkCrgUlLchCfg, &param->ulInfo, mBuf);
/* crg_c_001.main_5 - ADD - Added the unpacking for LTE_L2_MEAS. */
#ifdef LTE_L2_MEAS
   CMCHKUNPK(SUnpkU8, &param->qci, mBuf);
#endif
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCrgCfg
*
*
*     Desc : Basic configuration info for MAC
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCrgCfg
(
CrgCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCrgCfg(param, mBuf)
CrgCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCrgCfg)

      switch(param->cfgType) {
         case CRG_LCH_CFG:
            CMCHKPK(cmPkCrgLchCfg, &param->u.lchCfg, mBuf);
            break;
         case CRG_UE_CFG:
            CMCHKPK(cmPkCrgUeCfg, &param->u.ueCfg, mBuf);
            break;
         case CRG_CELL_CFG:
            CMCHKPK(cmPkCrgCellCfg, &param->u.cellCfg, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(SPkU8, param->cfgType, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCrgCfg
*
*
*     Desc : Basic configuration info for MAC
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCrgCfg
(
CrgCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCrgCfg(param, mBuf)
CrgCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCrgCfg)

   CMCHKUNPK(SUnpkU8, &param->cfgType, mBuf);
      switch(param->cfgType) {
         case CRG_CELL_CFG:
            CMCHKUNPK(cmUnpkCrgCellCfg, &param->u.cellCfg, mBuf);
            break;
         case CRG_UE_CFG:
            CMCHKUNPK(cmUnpkCrgUeCfg, &param->u.ueCfg, mBuf);
            break;
         case CRG_LCH_CFG:
            CMCHKUNPK(cmUnpkCrgLchCfg, &param->u.lchCfg, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCrgCellRecfg
*
*
*     Desc : Cell reconfiguration info
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCrgCellRecfg
(
CrgCellRecfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCrgCellRecfg(param, mBuf)
CrgCellRecfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCrgCellRecfg)

   CMCHKPK(cmPkCrgRachCfg, &param->rachRecfg, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCrgCellRecfg
*
*
*     Desc : Cell reconfiguration info
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCrgCellRecfg
(
CrgCellRecfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCrgCellRecfg(param, mBuf)
CrgCellRecfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCrgCellRecfg)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkCrgRachCfg, &param->rachRecfg, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCrgUeRecfg
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
PUBLIC S16 cmPkCrgUeRecfg
(
CrgUeRecfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCrgUeRecfg(param, mBuf)
CrgUeRecfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCrgUeRecfg)
#ifdef LTE_ADV
   if(TRUE == param->crgSCellCfg.isSCellCfgPres)
   {
      CMCHKPK(cmPkCrgUeSecCellInfo, &param->crgSCellCfg, mBuf);
   }
   else
   {
      CMCHKPK(SPkU8, param->crgSCellCfg.isSCellCfgPres, mBuf);
   }
#endif /* LTE_ADV */
   CMCHKPK(SPkU32, param->txMode.tm, mBuf);
   CMCHKPK(SPkU8, param->txMode.pres, mBuf);
   CMCHKPK(cmPkCrgUeUlHqCfg, &param->ueUlHqRecfg, mBuf);
   CMCHKPK(cmPkLteRnti, param->newCrnti, mBuf);
   CMCHKPK(cmPkLteRnti, param->oldCrnti, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCrgUeRecfg
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
PUBLIC S16 cmUnpkCrgUeRecfg
(
CrgUeRecfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCrgUeRecfg(param, mBuf)
CrgUeRecfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCrgUeRecfg)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &param->oldCrnti, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &param->newCrnti, mBuf);
   CMCHKUNPK(cmUnpkCrgUeUlHqCfg, &param->ueUlHqRecfg, mBuf);
   CMCHKUNPK(SUnpkU8, &param->txMode.pres, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&param->txMode.tm, mBuf);
#ifdef LTE_ADV 
      CMCHKUNPK(cmUnpkCrgUeSecCellInfo, &param->crgSCellCfg, mBuf);
#endif /* LTE_ADV */
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCrgLchRecfg
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
PUBLIC S16 cmPkCrgLchRecfg
(
CrgLchRecfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCrgLchRecfg(param, mBuf)
CrgLchRecfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCrgLchRecfg)

      CMCHKPK(SPkU8, param->ulRecfg.lcgId, mBuf);
   CMCHKPK(cmPkLteLcId, param->lcId, mBuf);
   CMCHKPK(cmPkLteRnti, param->crnti, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCrgLchRecfg
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
PUBLIC S16 cmUnpkCrgLchRecfg
(
CrgLchRecfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCrgLchRecfg(param, mBuf)
CrgLchRecfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCrgLchRecfg)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &param->crnti, mBuf);
   CMCHKUNPK(cmUnpkLteLcId, &param->lcId, mBuf);
      CMCHKUNPK(SUnpkU8, &param->ulRecfg.lcgId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCrgRecfg
*
*
*     Desc : Basic reconfiguration info for MAC
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCrgRecfg
(
CrgRecfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCrgRecfg(param, mBuf)
CrgRecfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCrgRecfg)

      switch(param->recfgType) {
         case CRG_LCH_CFG:
            CMCHKPK(cmPkCrgLchRecfg, &param->u.lchRecfg, mBuf);
            break;
         case CRG_UE_CFG:
            CMCHKPK(cmPkCrgUeRecfg, &param->u.ueRecfg, mBuf);
            break;
         case CRG_CELL_CFG:
            CMCHKPK(cmPkCrgCellRecfg, &param->u.cellRecfg, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(SPkU8, param->recfgType, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCrgRecfg
*
*
*     Desc : Basic reconfiguration info for MAC
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCrgRecfg
(
CrgRecfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCrgRecfg(param, mBuf)
CrgRecfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCrgRecfg)

   CMCHKUNPK(SUnpkU8, &param->recfgType, mBuf);
      switch(param->recfgType) {
         case CRG_CELL_CFG:
            CMCHKUNPK(cmUnpkCrgCellRecfg, &param->u.cellRecfg, mBuf);
            break;
         case CRG_UE_CFG:
            CMCHKUNPK(cmUnpkCrgUeRecfg, &param->u.ueRecfg, mBuf);
            break;
         case CRG_LCH_CFG:
            CMCHKUNPK(cmUnpkCrgLchRecfg, &param->u.lchRecfg, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCrgDel
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
PUBLIC S16 cmPkCrgDel
(
CrgDel *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCrgDel(param, mBuf)
CrgDel *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCrgDel)

      switch(param->delType) {
         case CRG_LCH_CFG:
            CMCHKPK(SPkU8, param->u.lchDel.dir, mBuf);
            CMCHKPK(cmPkLteLcId, param->u.lchDel.lcId, mBuf);
            CMCHKPK(cmPkLteRnti, param->u.lchDel.crnti, mBuf);
            CMCHKPK(cmPkLteCellId, param->u.lchDel.cellId, mBuf);
         break;
         case CRG_UE_CFG:
            CMCHKPK(cmPkLteRnti, param->u.ueDel.crnti, mBuf);
            CMCHKPK(cmPkLteCellId, param->u.ueDel.cellId, mBuf);
         break;
         case CRG_CELL_CFG:
            CMCHKPK(cmPkLteCellId, param->u.cellDel.cellId, mBuf);
         break;
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(SPkU8, param->delType, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCrgDel
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
PUBLIC S16 cmUnpkCrgDel
(
CrgDel *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCrgDel(param, mBuf)
CrgDel *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCrgDel)

   CMCHKUNPK(SUnpkU8, &param->delType, mBuf);
      switch(param->delType) {
         case CRG_CELL_CFG:
            CMCHKUNPK(cmUnpkLteCellId, &param->u.cellDel.cellId, mBuf);
         break;
         case CRG_UE_CFG:
            CMCHKUNPK(cmUnpkLteCellId, &param->u.ueDel.cellId, mBuf);
            CMCHKUNPK(cmUnpkLteRnti, &param->u.ueDel.crnti, mBuf);
         break;
         case CRG_LCH_CFG:
            CMCHKUNPK(cmUnpkLteCellId, &param->u.lchDel.cellId, mBuf);
            CMCHKUNPK(cmUnpkLteRnti, &param->u.lchDel.crnti, mBuf);
            CMCHKUNPK(cmUnpkLteLcId, &param->u.lchDel.lcId, mBuf);
            CMCHKUNPK(SUnpkU8, &param->u.lchDel.dir, mBuf);
         break;
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCrgRst
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
PUBLIC S16 cmPkCrgRst
(
CrgRst *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCrgRst(param, mBuf)
CrgRst *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCrgRst)

   CMCHKPK(cmPkLteRnti, param->crnti, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCrgRst
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
PUBLIC S16 cmUnpkCrgRst
(
CrgRst *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCrgRst(param, mBuf)
CrgRst *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCrgRst)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &param->crnti, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkCrgCfgReqInfo
*
*
*     Desc : Config/Reconfig/Delete info for MAC
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCrgCfgReqInfo
(
CrgCfgReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCrgCfgReqInfo(param, mBuf)
CrgCfgReqInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCrgCfgReqInfo)

      switch(param->action) {
         case CRG_RESET:
            CMCHKPK(cmPkCrgRst, &param->u.rstInfo, mBuf);
            break;
         case CRG_DELETE:
            CMCHKPK(cmPkCrgDel, &param->u.delInfo, mBuf);
            break;
         case CRG_RECONFIG:
            CMCHKPK(cmPkCrgRecfg, &param->u.recfgInfo, mBuf);
            break;
         case CRG_CONFIG:
            CMCHKPK(cmPkCrgCfg, &param->u.cfgInfo, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(SPkU8, param->action, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkCrgCfgReqInfo
*
*
*     Desc : Config/Reconfig/Delete info for MAC
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCrgCfgReqInfo
(
CrgCfgReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCrgCfgReqInfo(param, mBuf)
CrgCfgReqInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCrgCfgReqInfo)

   CMCHKUNPK(SUnpkU8, &param->action, mBuf);
      switch(param->action) {
         case CRG_CONFIG:
            CMCHKUNPK(cmUnpkCrgCfg, &param->u.cfgInfo, mBuf);
            break;
         case CRG_RECONFIG:
            CMCHKUNPK(cmUnpkCrgRecfg, &param->u.recfgInfo, mBuf);
            break;
         case CRG_DELETE:
            CMCHKUNPK(cmUnpkCrgDel, &param->u.delInfo, mBuf);
            break;
         case CRG_RESET:
            CMCHKUNPK(cmUnpkCrgRst, &param->u.rstInfo, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}
#endif


/**********************************************************************
 
         End of file:     crg.c@@/main/6 - Wed Jul 27 12:49:15 2011
 
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
/main/1      ---     sm                1. Initial Release.
/main/3      ---     sm                1. Initial Release.
/main/5      ---     crg_c_001.main_4   gvj    1. Added support for MIMO
/main/6      ---     crg_c_001.main_5   gvj    1. Updated for LTE MAC Rel 3.1
*********************************************************************91*/
