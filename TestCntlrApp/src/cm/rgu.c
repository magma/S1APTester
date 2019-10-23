

/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for packing/unpacking of RGU interface
               primitives.
  
     File:     rgu.c 
  
     Sid:      rgu.c@@/main/6 - Wed Jul 27 14:15:21 2011
  
     Prg:      sm
  
**********************************************************************/

/** @file rgu.c
@brief This file contains the packing/unpacking code for the RGU interface 
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
#include "rgu.h"           /* RGU Interface defines */

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_lib.x"        /* Common Library Definitions */
#include "cm_hash.x"       /* Common Hash List Definitions */
#include "cm_lte.x"        /* Common LTE Defines */
#include "rgu.x"           /* RGU Interface includes */

#ifdef SS_RBUF
#include "ss_rbuf.h"
#include "ss_rbuf.x"
#endif

#ifdef LCRGU


/**
* @brief Request from RLC to MAC to bind the interface saps
*
* @details
*
*     Function : cmPkRguBndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   SpId  spId
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkRguBndReq
(
Pst* pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 cmPkRguBndReq(pst, suId, spId)
Pst* pst;
SuId suId;
SpId spId;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkRguBndReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU001, (ErrVal)0, "Packing failed");
#endif      
      RETVALUE(RFAILED);
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU002, (ErrVal)0, "Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU003, (ErrVal)0, "Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTRGUBNDREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief Request from RLC to MAC to bind the interface saps
*
* @details
*
*     Function : cmUnpkRguBndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   SpId  spId
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkRguBndReq
(
RguBndReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguBndReq(func, pst, mBuf)
RguBndReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   SpId spId;
   
   TRC3(cmUnpkRguBndReq)

   if (SUnpkS16(&suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU004, (ErrVal)0, "UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SUnpkS16(&spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU005, (ErrVal)0, "UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, spId));
}


/**
* @brief Request from RLC to MAC to Unbind the interface saps
*
* @details
*
*     Function : cmPkRguUbndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   Reason  reason
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkRguUbndReq
(
Pst* pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 cmPkRguUbndReq(pst, spId, reason)
Pst* pst;
SpId spId;
Reason reason;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkRguUbndReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU006, (ErrVal)0, "Packing failed");
#endif      
      RETVALUE(RFAILED);
   }
   if (SPkS16(reason, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU007, (ErrVal)0, "Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU008, (ErrVal)0, "Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTRGUUBNDREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief Request from RLC to MAC to Unbind the interface saps
*
* @details
*
*     Function : cmUnpkRguUbndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   Reason  reason
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkRguUbndReq
(
RguUbndReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguUbndReq(func, pst, mBuf)
RguUbndReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   Reason reason;
   
   TRC3(cmUnpkRguUbndReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU009, (ErrVal)0, "UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SUnpkS16(&reason, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU010, (ErrVal)0, "UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, reason));
}


/**
* @brief Confirmation from MAC to RLC for the bind/Unbind 
 * request for the interface saps
*
* @details
*
*     Function : cmPkRguBndCfm
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   U8  status
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkRguBndCfm
(
Pst* pst,
SuId suId,
U8 status
)
#else
PUBLIC S16 cmPkRguBndCfm(pst, suId, status)
Pst* pst;
SuId suId;
U8 status;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkRguBndCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU011, (ErrVal)0, "Packing failed");
#endif      
      RETVALUE(RFAILED);
   }
   if (SPkU8(status, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU012, (ErrVal)0, "Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU013, (ErrVal)0, "Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTRGUBNDCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief Confirmation from MAC to RLC for the bind/Unbind 
 * request for the interface saps
*
* @details
*
*     Function : cmUnpkRguBndCfm
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   U8  status
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkRguBndCfm
(
RguBndCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguBndCfm(func, pst, mBuf)
RguBndCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   U8 status;
   
   TRC3(cmUnpkRguBndCfm)

   if (SUnpkS16(&suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU014, (ErrVal)0, "UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SUnpkU8(&status, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU015, (ErrVal)0, "UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, status));
}


/**
* @brief Request from RLC to MAC for forwarding SDUs on common
 * channel for transmission
*
* @details
*
*     Function : cmPkRguCDatReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RguCDatReqInfo  *  datReq
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkRguCDatReq
(
Pst* pst,
SpId spId,
RguCDatReqInfo  * datReq
)
#else
PUBLIC S16 cmPkRguCDatReq(pst, spId, datReq)
Pst* pst;
SpId spId;
RguCDatReqInfo  * datReq;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkRguCDatReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU016, (ErrVal)0, "Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)datReq, sizeof(RguCDatReqInfo));
      RETVALUE(RFAILED);
   }
   if (pst->selector == RGU_SEL_LWLC)
   {
      CMCHKPK(cmPkPtr,(PTR) datReq, mBuf);
   }
   else
   {
      if (cmPkRguCDatReqInfo(datReq, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU017, (ErrVal)0, "Packing failed");
#endif      
         SPutSBuf(pst->region, pst->pool, 
                  (Data *)datReq, sizeof(RguCDatReqInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      if (SPutSBuf(pst->region, pst->pool, 
                   (Data *)datReq, sizeof(RguCDatReqInfo)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ERGU019, (ErrVal)0, "Packing failed");
#endif      
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      datReq = NULLP;
   }

   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU018, (ErrVal)0, "Packing failed");
#endif      

      if (datReq != NULLP)
      {
         SPutSBuf(pst->region, pst->pool, 
                   (Data *)datReq, sizeof(RguCDatReqInfo));
      }

      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) EVTRGUCDATREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief Request from RLC to MAC for forwarding SDUs on common
 * channel for transmission
*
* @details
*
*     Function : cmUnpkRguCDatReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RguCDatReqInfo  *  datReq
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkRguCDatReq
(
RguCDatReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguCDatReq(func, pst, mBuf)
RguCDatReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   RguCDatReqInfo *datReq;
   
   TRC3(cmUnpkRguCDatReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector == RGU_SEL_LWLC)
   {
      CMCHKUNPK(cmUnpkPtr,(PTR *) &datReq, mBuf);
   }
   else 
   {
      if ((SGetSBuf(pst->region, pst->pool, 
                   (Data **)&datReq, sizeof(RguCDatReqInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ERGU020, (ErrVal)0, "UnPacking failed");
#endif      
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
     }
     cmMemset((U8*)datReq, (U8)0, sizeof(RguCDatReqInfo));
     if (cmUnpkRguCDatReqInfo(datReq, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ERGU021, (ErrVal)0, "UnPacking failed");
#endif      
         SPutMsg(mBuf);
         SPutSBuf(pst->region, pst->pool, 
                  (Data *)datReq, sizeof(RguCDatReqInfo));
         RETVALUE(RFAILED);
      }
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, datReq));
}


/**
* @brief Request from RLC to MAC for forwarding SDUs on 
 * dedicated channel for transmission
*
* @details
*
*     Function : cmPkRguDDatReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RguDDatReqInfo  *  datReq
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkRguDDatReq
(
Pst* pst,
SpId spId,
RguDDatReqInfo  * datReq
)
#else
PUBLIC S16 cmPkRguDDatReq(pst, spId, datReq)
Pst* pst;
SpId spId;
RguDDatReqInfo  * datReq;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkRguDDatReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU022, (ErrVal)0, "Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)datReq, sizeof(RguDDatReqInfo));
      RETVALUE(RFAILED);
   }

   if (pst->selector == RGU_SEL_LWLC)
   {
      CMCHKPK(cmPkPtr,(PTR) datReq, mBuf);
   }
   else
   {
      /*rgu_c_001.main_5 - ADD - L2M Support */
#ifdef LTE_L2_MEAS
      if (cmPkRguDDatReqInfo(pst, datReq, mBuf) != ROK)
#else
      if (cmPkRguDDatReqInfo(datReq, mBuf) != ROK) 
#endif
      {
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU023, (ErrVal)0, "Packing failed");
#endif      
         SPutSBuf(pst->region, pst->pool, (Data *)datReq,
                                       sizeof(RguDDatReqInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }

      if (SPutSBuf(pst->region, pst->pool, 
                   (Data *)datReq, sizeof(RguDDatReqInfo)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
              __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ERGU025, (ErrVal)0, "Packing failed");
#endif      
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      datReq = NULLP;
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU024, (ErrVal)0, "Packing failed");
#endif      
      if (datReq != NULLP);
      {
         SPutSBuf(pst->region, pst->pool, 
                  (Data *)datReq, sizeof(RguDDatReqInfo));
      }
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTRGUDDATREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief Request from RLC to MAC for forwarding SDUs on 
 * dedicated channel for transmission
*
* @details
*
*     Function : cmUnpkRguDDatReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RguDDatReqInfo  *  datReq
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkRguDDatReq
(
RguDDatReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguDDatReq(func, pst, mBuf)
RguDDatReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   RguDDatReqInfo *datReq;
   
   TRC3(cmUnpkRguDDatReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (pst->selector == RGU_SEL_LWLC)
   {
      CMCHKUNPK(cmUnpkPtr,(PTR *) &datReq, mBuf);
   }
   else 
   {
      if ((SGetSBuf(pst->region, pst->pool, 
                     (Data **)&datReq, sizeof(RguDDatReqInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ERGU026, (ErrVal)0, "UnPacking failed");
#endif      
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      cmMemset((U8*)datReq, (U8)0, sizeof(RguDDatReqInfo));
  /*rgu_c_001.main_5 - ADD - L2M Support */
#ifdef LTE_L2_MEAS
      if (cmUnpkRguDDatReqInfo(pst,datReq, mBuf) != ROK)
#else
      if (cmUnpkRguDDatReqInfo(datReq, mBuf) != ROK) 
#endif
      {
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ERGU027, (ErrVal)0, "UnPacking failed");
#endif      
         SPutMsg(mBuf);
         SPutSBuf(pst->region, pst->pool, (Data *)datReq,
                                     sizeof(RguDDatReqInfo));
         RETVALUE(RFAILED);
      }
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, datReq));
}


/**
* @brief Data Indication from MAC to RLC to 
 * forward the data received for common channels
*
* @details
*
*     Function : cmPkRguCDatInd
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   RguCDatIndInfo  *  datInd
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkRguCDatInd
(
Pst* pst,
SuId suId,
RguCDatIndInfo  * datInd
)
#else
PUBLIC S16 cmPkRguCDatInd(pst, suId, datInd)
Pst* pst;
SuId suId;
RguCDatIndInfo  * datInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkRguCDatInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU028, (ErrVal)0, "Packing failed");
#endif      
      SPutStaticBuffer(pst->region, pst->pool, (Data *)datInd, sizeof(RguCDatIndInfo),0);
      RETVALUE(RFAILED);
   }
   if (pst->selector == RGU_SEL_LWLC)
   {
      CMCHKPK(cmPkPtr,(PTR) datInd, mBuf);
   }
   else
   {
      if (cmPkRguCDatIndInfo(datInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
        SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGU029, (ErrVal)0, "Packing failed");
#endif      
        SPutStaticBuffer(pst->region, pst->pool, (Data *)datInd,
                                    sizeof(RguCDatIndInfo),0);
        SPutMsg(mBuf);
        RETVALUE(RFAILED);
     }
     if (SPutStaticBuffer(pst->region, pst->pool, (Data *)datInd, 
                               sizeof(RguCDatIndInfo),0) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
        SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGU031, (ErrVal)0, "Packing failed");
#endif      
        SPutMsg(mBuf);
        RETVALUE(RFAILED);
     }
     datInd = NULLP;
  }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU030, (ErrVal)0, "Packing failed");
#endif      
      SPutStaticBuffer(pst->region, pst->pool, (Data *)datInd, sizeof(RguCDatIndInfo),0);
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) EVTRGUCDATIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief Data Indication from MAC to RLC to 
 * forward the data received for common channels
*
* @details
*
*     Function : cmUnpkRguCDatInd
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   RguCDatIndInfo  *  datInd
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkRguCDatInd
(
RguCDatInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguCDatInd(func, pst, mBuf)
RguCDatInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   RguCDatIndInfo *datInd;
   
   TRC3(cmUnpkRguCDatInd)

   if (SUnpkS16(&suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU032, (ErrVal)0, "UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (pst->selector == RGU_SEL_LWLC)
   {
      CMCHKUNPK(cmUnpkPtr,(PTR *) &datInd, mBuf);
   }
   else 
   {
      if ((SGetStaticBuffer(pst->region, pst->pool, 
                    (Data **)&datInd, sizeof(RguCDatIndInfo),0)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ERGU033, (ErrVal)0, "UnPacking failed");
#endif      
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      if (cmUnpkRguCDatIndInfo(datInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ERGU034, (ErrVal)0, "UnPacking failed");
#endif      
         SPutMsg(mBuf);
         SPutStaticBuffer(pst->region, pst->pool, (Data *)datInd, 
                                       sizeof(RguCDatIndInfo),0);
         RETVALUE(RFAILED);
      }
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, datInd));
}


/**
* @brief Data Indication from MAC to RLC to 
 * forward the data received for dedicated channels
*
* @details
*
*     Function : cmPkRguDDatInd
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   RguDDatIndInfo  *  datInd
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkRguDDatInd
(
Pst* pst,
SuId suId,
RguDDatIndInfo  * datInd
)
#else
PUBLIC S16 cmPkRguDDatInd(pst, suId, datInd)
Pst* pst;
SuId suId;
RguDDatIndInfo  * datInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkRguDDatInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU035, (ErrVal)0, "Packing failed");
#endif      
      SPutStaticBuffer(pst->region, pst->pool, (Data *)datInd, sizeof(RguDDatIndInfo),0);
      RETVALUE(RFAILED);
   }

   if (pst->selector == RGU_SEL_LWLC)
   {
      CMCHKPK(cmPkPtr,(PTR) datInd, mBuf);
   }
   else
   {
      if (cmPkRguDDatIndInfo(datInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                (ErrVal)ERGU036, (ErrVal)0, "Packing failed");
#endif            
         SPutStaticBuffer(pst->region, pst->pool, (Data *)datInd, sizeof(RguDDatIndInfo),0);
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }

      if (SPutStaticBuffer(pst->region, pst->pool, 
                      (Data *)datInd, sizeof(RguDDatIndInfo),0) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ERGU038, (ErrVal)0, "Packing failed");
#endif      
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      datInd = NULLP;
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU037, (ErrVal)0, "Packing failed");
#endif      
      SPutStaticBuffer(pst->region, pst->pool, (Data *)datInd, sizeof(RguDDatIndInfo),0);
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) EVTRGUDDATIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief Data Indication from MAC to RLC to 
 * forward the data received for dedicated channels
*
* @details
*
*     Function : cmUnpkRguDDatInd
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   RguDDatIndInfo  *  datInd
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkRguDDatInd
(
RguDDatInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguDDatInd(func, pst, mBuf)
RguDDatInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   RguDDatIndInfo *datInd;
   
   TRC3(cmUnpkRguDDatInd)

   if (SUnpkS16(&suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU039, (ErrVal)0, "UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (pst->selector == RGU_SEL_LWLC)
   {
      CMCHKUNPK(cmUnpkPtr,(PTR *) &datInd, mBuf);
   }
   else 
   {
       if ((SGetStaticBuffer(pst->region, pst->pool, 
                    (Data **)&datInd, sizeof(RguDDatIndInfo),0)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ERGU040, (ErrVal)0, "UnPacking failed");
#endif      
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      if (cmUnpkRguDDatIndInfo(datInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ERGU041, (ErrVal)0, "UnPacking failed");
#endif      
         SPutMsg(mBuf);
         SPutStaticBuffer(pst->region, pst->pool, 
                    (Data *)datInd, sizeof(RguDDatIndInfo),0);
         RETVALUE(RFAILED);
      }
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, datInd));
}


/**
* @brief Primitive invoked from RLC to MAC to 
 * inform the BO report for common channels
*
* @details
*
*     Function : cmPkRguCStaRsp
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RguCStaRspInfo  *  staRsp
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkRguCStaRsp
(
Pst* pst,
SpId spId,
RguCStaRspInfo  * staRsp
)
#else
PUBLIC S16 cmPkRguCStaRsp(pst, spId, staRsp)
Pst* pst;
SpId spId;
RguCStaRspInfo  * staRsp;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkRguCStaRsp)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU042, (ErrVal)0, "Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)staRsp, sizeof(RguCStaRspInfo));
      RETVALUE(RFAILED);
   }
   if (pst->selector == RGU_SEL_LWLC)
   {
      CMCHKPK(cmPkPtr,(PTR) staRsp, mBuf);
   }
   else
   {
      if (cmPkRguCStaRspInfo(staRsp, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ERGU043, (ErrVal)0, "Packing failed");
#endif      
         SPutSBuf(pst->region, pst->pool, (Data *)staRsp, 
                                     sizeof(RguCStaRspInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }

      if (SPutSBuf(pst->region, pst->pool, (Data *)staRsp, 
                                     sizeof(RguCStaRspInfo)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU045, (ErrVal)0, "Packing failed");
#endif      
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      staRsp = NULLP;
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU044, (ErrVal)0, "Packing failed");
#endif      
      if (staRsp != NULLP)
      {
         SPutSBuf(pst->region, pst->pool, 
                       (Data *)staRsp, sizeof(RguCStaRspInfo));
      }
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) EVTRGUCSTARSP;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief Primitive invoked from RLC to MAC to 
 * inform the BO report for common channels
*
* @details
*
*     Function : cmUnpkRguCStaRsp
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RguCStaRspInfo  *  staRsp
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkRguCStaRsp
(
RguCStaRsp func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguCStaRsp(func, pst, mBuf)
RguCStaRsp func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   RguCStaRspInfo *staRsp;
   
   TRC3(cmUnpkRguCStaRsp)

   if (SUnpkS16(&spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU046, (ErrVal)0, "UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector == RGU_SEL_LWLC)
   {
      CMCHKUNPK(cmUnpkPtr,(PTR *) &staRsp, mBuf);
   }
   else 
   {
      if ((SGetSBuf(pst->region, pst->pool, (Data **)&staRsp, 
                                    sizeof(RguCStaRspInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ERGU047, (ErrVal)0, "UnPacking failed");
#endif      
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      if (cmUnpkRguCStaRspInfo(staRsp, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ERGU048, (ErrVal)0, "UnPacking failed");
#endif      
         SPutMsg(mBuf);
         SPutSBuf(pst->region, pst->pool, (Data *)staRsp, 
                                          sizeof(RguCStaRspInfo));
         RETVALUE(RFAILED);
      }
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, staRsp));
}

/*rgu_c_001.main_5 - ADD - L2M & R9 Support */
#ifdef LTE_L2_MEAS

/***********************************************************
*
*     Func :cmPkRguL2MUlThrpMeasReqInfo 
*
*
* Status Response from RLC to MAC on UL dedicated logical channel for Uplink
* Scheduled throughput measurement
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRguL2MUlThrpMeasReqInfo 
(
RguL2MUlThrpMeasReqInfo* param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRguL2MUlThrpMeasReqInfo(param, mBuf)
RguL2MUlThrpMeasReqInfo* param;
Buffer *mBuf;
#endif
{
   S32 loop;
   TRC3(cmPkRguL2MUlThrpMeasReqInfo);

   CMCHKPK(SPkU8, param->enbMeas, mBuf);
   for (loop=param->numLcId-1; loop >= 0; loop--)
   {
      CMCHKPK(SPkU8, param->lcId[loop], mBuf);
   }
   CMCHKPK(cmPkLteLcId, param->numLcId, mBuf);
   CMCHKPK(cmPkLteRnti, param->rnti, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func :cmUnpkRguL2MUlThrpMeasReqInfo 
*
*
* Status Response from RLC to MAC on UL dedicated logical channel for Uplink
* Scheduled throughput measurement
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRguL2MUlThrpMeasReqInfo 
(
RguL2MUlThrpMeasReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguL2MUlThrpMeasReqInfo(param, mBuf)
RguL2MUlThrpMeasReqInfo *param;
Buffer *mBuf;
#endif
{
   U8 loop;
   TRC3(cmUnpkRguL2MUlThrpMeasReqInfo);

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &param->rnti, mBuf);
   CMCHKUNPK(cmUnpkLteLcId, &param->numLcId, mBuf);
   for (loop=0; loop<param->numLcId; loop++)
   {
      CMCHKUNPK(SUnpkU8, &param->lcId[loop], mBuf);
   }
   CMCHKUNPK(SUnpkU8, &param->enbMeas, mBuf);
   RETVALUE(ROK);
}

/**
* @brief Primitive invoked from RLC to MAC to 
* inform the On/Off status for Scheduled UL throughput 
* measurment for dedicated channels
*
* @details
*
*     Function :cmPkRguL2MUlThrpMeasReq 
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RguL2MUlThrpMeasReqInfo*  measReq
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkRguL2MUlThrpMeasReq 
(
Pst* pst,
SpId spId,
RguL2MUlThrpMeasReqInfo* measReq
)
#else
PUBLIC S16 cmPkRguL2MUlThrpMeasReq(pst, spId, measReq)
Pst* pst;
SpId spId;
RguL2MUlThrpMeasReqInfo* measReq;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkRguL2MUlThrpMeasReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU049, (ErrVal)0, "Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)measReq, sizeof(RguL2MUlThrpMeasReqInfo));
      RETVALUE(RFAILED);
   }
   if (pst->selector == RGU_SEL_LWLC)
   {
      CMCHKPK(cmPkPtr,(PTR) measReq, mBuf);
   }
   else
   {
      if (cmPkRguL2MUlThrpMeasReqInfo(measReq, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ERGU050, (ErrVal)0, "Packing failed");
#endif      
         SPutSBuf(pst->region, pst->pool, (Data *)measReq, 
                                    sizeof(RguL2MUlThrpMeasReqInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      if (SPutSBuf(pst->region, pst->pool, (Data *)measReq, 
                           sizeof(RguL2MUlThrpMeasReqInfo)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ERGU052, (ErrVal)0, "Packing failed");
#endif      
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      measReq = NULLP;
   }

   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU051, (ErrVal)0, "Packing failed");
#endif      
      if (measReq != NULLP)
      {
         SPutSBuf(pst->region, pst->pool, (Data *)measReq,
                             sizeof(RguL2MUlThrpMeasReqInfo));
      }
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) EVTRGUL2MULTHRPMEASREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief Primitive invoked from RLC to MAC to 
* inform the On/Off status for Scheduled UL throughput 
* measurment for dedicated channels
*
* @details
*
*     Function :cmUnpkRguL2MUlThrpMeasReq 
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RguL2MUlThrpMeasReqInfo  * measReq 
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkRguL2MUlThrpMeasReq 
(
RguL2MUlThrpMeasReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguL2MUlThrpMeasReq(func, pst, mBuf)
RguL2MUlThrpMeasReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   RguL2MUlThrpMeasReqInfo* measReq;
   
   TRC3(cmUnpkRguL2MUlThrpMeasReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU053, (ErrVal)0, "UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector == RGU_SEL_LWLC)
   {
      CMCHKUNPK(cmUnpkPtr,(PTR *) &measReq, mBuf);
   }
   else 
   {
      if ((SGetSBuf(pst->region, pst->pool, (Data **)&measReq,
                              sizeof(RguL2MUlThrpMeasReqInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ERGU054, (ErrVal)0, "UnPacking failed");
#endif      
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      if (cmUnpkRguL2MUlThrpMeasReqInfo(measReq, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ERGU055, (ErrVal)0, "UnPacking failed");
#endif      
         SPutMsg(mBuf);
         SPutSBuf(pst->region, pst->pool, (Data *)measReq, 
                                sizeof(RguL2MUlThrpMeasReqInfo));
         RETVALUE(RFAILED);
      }
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, measReq));
}

#endif




/**
* @brief Primitive invoked from RLC to MAC to 
 * inform the BO report for dedicated channels
*
* @details
*
*     Function : cmPkRguDStaRsp
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RguDStaRspInfo  *  staRsp
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkRguDStaRsp
(
Pst* pst,
SpId spId,
RguDStaRspInfo  *staRsp
)
#else
PUBLIC S16 cmPkRguDStaRsp(pst, spId, staRsp)
Pst* pst;
SpId spId;
RguDStaRspInfo  *staRsp;
#endif
{

   RguDStaRspInfo  *staRspInfo = NULL;
   Buffer *mBuf = NULLP;

   if(SGetSBuf(pst->region, pst->pool, (Data **)&staRspInfo, sizeof(RguDStaRspInfo)) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGU056, (ErrVal)0, "Packing failed");
#endif      
      RETVALUE(RFAILED);
   }
   cmMemcpy((U8 *)staRspInfo, (U8 *)staRsp, sizeof(RguDStaRspInfo)); 
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU056, (ErrVal)0, "Packing failed");
#endif      
         SPutSBuf(pst->region, pst->pool, (Data *)staRspInfo, sizeof(RguDStaRspInfo));

      RETVALUE(RFAILED);
   }
   if (pst->selector == RGU_SEL_LWLC)
   {
      CMCHKPK(cmPkPtr,(PTR) staRspInfo, mBuf);
   }
   else
   {
      if (cmPkRguDStaRspInfo(staRsp, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
        SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGU057, (ErrVal)0, "Packing failed");
#endif      
        SPutMsg(mBuf);
        RETVALUE(RFAILED);
     }
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU058, (ErrVal)0, "Packing failed");
#endif      
      if (staRspInfo != NULLP)
      {
         SPutSBuf(pst->region, pst->pool, (Data *)staRspInfo, sizeof(RguDStaRspInfo));
      }
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) EVTRGUDSTARSP;
   RETVALUE(SPstTsk(pst,mBuf));
   SPutMsg(mBuf);
}


/**
* @brief Primitive invoked from RLC to MAC to 
 * inform the BO report for dedicated channels
*
* @details
*
*     Function : cmUnpkRguDStaRsp
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RguDStaRspInfo  *  staRsp
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkRguDStaRsp
(
RguDStaRsp func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguDStaRsp(func, pst, mBuf)
RguDStaRsp func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   RguDStaRspInfo *staRsp;
   
   TRC3(cmUnpkRguDStaRsp)

   if (SUnpkS16(&spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU060, (ErrVal)0, "UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (pst->selector == RGU_SEL_LWLC)
   {
      CMCHKUNPK(cmUnpkPtr,(PTR *) &staRsp, mBuf);
   }
   else
   {
      if ((SGetSBuf(pst->region, pst->pool, (Data **)&staRsp, 
                                 sizeof(RguDStaRspInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ERGU061, (ErrVal)0, "UnPacking failed");
#endif      
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      if (cmUnpkRguDStaRspInfo(staRsp, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ERGU062, (ErrVal)0, "UnPacking failed");
#endif      
         SPutMsg(mBuf);
         SPutSBuf(pst->region, pst->pool, (Data *)staRsp, sizeof(RguDStaRspInfo));
         RETVALUE(RFAILED);
      }
   }
   SPutMsg(mBuf);
   (*func)(pst, spId, staRsp);
   SPutSBuf(pst->region, pst->pool, (Data *)staRsp, sizeof(RguDStaRspInfo));
   RETVALUE(ROK);
}


/**
* @brief Status Indication from MAC to RLC  
 * as a response to the staRsp primitive from RLC.
 * Informs RLC of the totalBufferSize and Timing Info 
 * for the transmission on common channels.
*
* @details
*
*     Function : cmPkRguCStaInd
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   RguCStaIndInfo  *  staInd
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkRguCStaInd
(
Pst* pst,
SuId suId,
RguCStaIndInfo  * staInd
)
#else
PUBLIC S16 cmPkRguCStaInd(pst, suId, staInd)
Pst* pst;
SuId suId;
RguCStaIndInfo  * staInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkRguCStaInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU063, (ErrVal)0, "Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)staInd, sizeof(RguCStaIndInfo));
      RETVALUE(RFAILED);
   }
      if (pst->selector == RGU_SEL_LWLC)
   {
      CMCHKPK(cmPkPtr,(PTR) staInd, mBuf);
   }
   else
   {
      if (cmPkRguCStaIndInfo(staInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                (ErrVal)ERGU064, (ErrVal)0, "Packing failed");
#endif      
         SPutSBuf(pst->region, pst->pool, (Data *)staInd, sizeof(RguCStaIndInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      if (SPutSBuf(pst->region, pst->pool, 
                    (Data *)staInd, sizeof(RguCStaIndInfo)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ERGU066, (ErrVal)0, "Packing failed");
#endif      
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      staInd = NULLP;
  }
  if (SPkS16(suId,mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU065, (ErrVal)0, "Packing failed");
#endif      
      if (staInd != NULLP)
      {
         SPutSBuf(pst->region, pst->pool, (Data *)staInd,
                                     sizeof(RguCStaIndInfo));
      }
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTRGUCSTAIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief Status Indication from MAC to RLC  
 * as a response to the staRsp primitive from RLC.
 * Informs RLC of the totalBufferSize and Timing Info 
 * for the transmission on common channels.
*
* @details
*
*     Function : cmUnpkRguCStaInd
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   RguCStaIndInfo  *  staInd
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkRguCStaInd
(
RguCStaInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguCStaInd(func, pst, mBuf)
RguCStaInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   RguCStaIndInfo *staInd;
   
   TRC3(cmUnpkRguCStaInd)

   if (SUnpkS16(&suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU067, (ErrVal)0, "UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (pst->selector == RGU_SEL_LWLC)
   {
      CMCHKUNPK(cmUnpkPtr,(PTR *) &staInd, mBuf);
   }
   else
   {
      if ((SGetSBuf(pst->region, pst->pool, (Data **)&staInd, sizeof(RguCStaIndInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
           SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ERGU068, (ErrVal)0, "UnPacking failed");
#endif      
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      if (cmUnpkRguCStaIndInfo(staInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ERGU069, (ErrVal)0, "UnPacking failed");
#endif      
         SPutMsg(mBuf);
         SPutSBuf(pst->region, pst->pool, (Data *)staInd, sizeof(RguCStaIndInfo));
         RETVALUE(RFAILED);
      }
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, staInd));
}

   /*rgu_c_001.main_5 - ADD - L2M Support */
#ifdef LTE_L2_MEAS
#if 0

/**
* @brief Packing function for RguLchMapInfo
*
* @details
*
*     Function : cmPkRguLchMapInfo
*  @param[in]   RguLchMapInfo  *param
*  @param[out]  Buffer         *mBuf 
*  @return  Void 
**/
#ifdef ANSI
PRIVATE S16 cmPkRguLchMapInfo
(
RguLchMapInfo   *param,
Buffer          *mBuf
)
#else
PRIVATE S16 cmPkRguLchMapInfo(param, mBuf)
RguLchMapInfo   *param;
Buffer          *mBuf;
#endif
{
   U8    idx;

   TRC3(cmPkRguLchMapInfo);

   for(idx = 0; idx < RGU_MAX_LC; idx++)
   {
      CMCHKPK(SPkU16, param->snList[idx], mBuf);
   }
   CMCHKPK(cmPkLteLcId, param->lChId, mBuf);

   RETVALUE(ROK);
}

/**
* @brief Unpacking function for RguLchMapInfo
*
* @details
*
*     Function : cmUnpkRguLchMapInfo
*
*  @param[out] RguLchMapInfo  *param
*  @param[in]  Buffer        *mBuf
*  @return   Void
**/
#ifdef ANSI
PRIVATE S16 cmUnpkRguLchMapInfo
(
RguLchMapInfo *param, 
Buffer       *mBuf
)
#else
PRIVATE S16 cmUnpkRguLchMapInfo(param, mBuf)
RguLchMapInfo *param;   
Buffer       *mBuf;
#endif
{
   U8    idx;

   TRC3(cmUnpkRguLchMapInfo)

   CMCHKUNPK(cmUnpkLteLcId, &param->lChId, mBuf);
   for(idx = RGU_MAX_LC; idx > 0; idx--)
   {
      CMCHKUNPK(SUnpkU16, &param->snList[idx - 1], mBuf);
   }

   RETVALUE(ROK);
}
#endif

/**
* @brief Harq Status Indication from MAC to RLC  
*
* @details
*
*     Function : cmPkRguHqStaInd
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   RguHarqStatusInd  *harqStatusInd
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkRguHqStaInd
(
Pst* pst,
SuId suId,
RguHarqStatusInd  *harqStatusInd
)
#else
PUBLIC S16 cmPkRguHqStaInd(pst, suId, harqStatusInd)
Pst* pst;
SuId suId;
RguHarqStatusInd  *harqStatusInd;
#endif
{

   Buffer   *mBuf;
   U8       idx;
   RguHarqStatusInd *harqStaInd = NULL;

   TRC3(cmPkRguHqStaInd)
   if (SGetSBuf(pst->region, pst->pool, (Data **)&harqStaInd, sizeof(RguHarqStatusInd)) != ROK){
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ERGU070, (ErrVal)0, "Packing failed");
#endif      
         RETVALUE(RFAILED);
      }
   cmMemcpy((U8 *)harqStaInd, (U8 *)harqStatusInd, sizeof(RguHarqStatusInd));

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU070, (ErrVal)0, "Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)harqStaInd, sizeof(RguHarqStatusInd));
      RETVALUE(RFAILED);
   }

   if (pst->selector == RGU_SEL_LWLC)
   {
      CMCHKPK(cmPkPtr,(PTR) harqStaInd, mBuf); 
   }
   else
   {
      for(idx = 0; idx < harqStaInd->numTbs; idx++)
      {
         CMCHKPK(SPkU16, harqStaInd->status[idx], mBuf);
      }
      for(idx = 0; idx < harqStaInd->numTbs; idx++)
      {
         CMCHKPK(SPkU32, harqStaInd->tbId[idx], mBuf);
      }
      CMCHKPK(SPkU8, harqStaInd->numTbs, mBuf);
      CMCHKPK(cmPkLteRnti, harqStaInd->ueId, mBuf);
      CMCHKPK(cmPkLteCellId, harqStaInd->cellId, mBuf);
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU071, (ErrVal)0, "Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)harqStaInd,
              sizeof(RguHarqStatusInd));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPutSBuf(pst->region, pst->pool, (Data *)harqStaInd,
       sizeof(RguHarqStatusInd)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU072, (ErrVal)0, "Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) EVTRGUHQSTAIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


#if 0
/**
* @brief Unpacking function for RguSnMapInfo
*
* @details
*
*     Function : cmUnpkRguSnMapInfo
*
*  @param[out] RguSnMapInfo  *param
*  @param[in]  Buffer        *mBuf
*  @return  Void
**/
#ifdef ANSI
PRIVATE S16 cmUnpkRguSnMapInfo
(
RguSnMapInfo *param, 
Buffer       *mBuf
)
#else
PRIVATE S16 cmUnpkRguSnMapInfo(param, mBuf)
RguSnMapInfo *param;   
Buffer       *mBuf;
#endif
{
   U8    idx;
   
   TRC3(cmUnpkRguSnMapInfo)
   
   CMCHKUNPK(SUnpkU32, &param->tbId, mBuf);   
   CMCHKUNPK(SUnpkU8, &param->numLch, mBuf);   
   for(idx = param->numLch; idx > 0; idx--)
   {
      CMCHKUNPK(cmUnpkRguLchMapInfo, &param->lchMap[idx - 1], mBuf);
   }
   RETVALUE(ROK);
}
#endif

/**
* @brief Harq Status Indication from MAC to RLC  
*
* @details
*
*     Function : cmUnpkRguHqStaInd
*
*  @param[in]  RguHqStaInd   func
*  @param[in]  Pst           *pst
*  @param[in]  Buffer        *mBuf
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkRguHqStaInd
(
RguHqStaInd  func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguHqStaInd(func, pst, mBuf)
RguHqStaInd   func;
Pst *pst;
Buffer *mBuf;
#endif
{
   RguHarqStatusInd    *hqStaInd;  
   SuId                suId;
   U8                  idx;

   TRC3(cmUnpkRguHqStaInd)

   if (SUnpkS16(&suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU073, (ErrVal)0, "UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if ((SGetSBuf(pst->region, pst->pool, (Data **)&hqStaInd, 
        sizeof(RguHarqStatusInd))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU074, (ErrVal)0, "UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   CMCHKUNPK(cmUnpkLteCellId, &hqStaInd->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &hqStaInd->ueId, mBuf);
   CMCHKUNPK(SUnpkU8, &hqStaInd->numTbs, mBuf);
   for(idx = hqStaInd->numTbs; idx > 0; idx--)
   {
      CMCHKUNPK(SUnpkU32, &hqStaInd->tbId[idx - 1], mBuf);
   }
   for(idx = hqStaInd->numTbs; idx > 0; idx--)
   {
      CMCHKUNPK(SUnpkU16, &hqStaInd->status[idx - 1], mBuf);
   }

   SPutMsg(mBuf);
   (*func)(pst, suId, hqStaInd);
   SPutSBuf(pst->region, pst->pool, (Data *)hqStaInd, sizeof(RguHarqStatusInd));
   RETVALUE(ROK);
}
#endif /* LTE_L2_MEAS */


/**
* @brief Status Indication from MAC to RLC  
 * as a response to the staRsp primitive from RLC.
 * Informs RLC of the totalBufferSize and Timing Info 
 * for the transmission on dedicated channels.
*
* @details
*
*     Function : cmPkRguDStaInd
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   RguDStaIndInfo  *  staInd
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkRguDStaInd
(
Pst* pst,
SuId suId,
RguDStaIndInfo  * staInd
)
#else
PUBLIC S16 cmPkRguDStaInd(pst, suId, staInd)
Pst* pst;
SuId suId;
RguDStaIndInfo  * staInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkRguDStaInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU076, (ErrVal)0, "Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)staInd, sizeof(RguDStaIndInfo));
      RETVALUE(RFAILED);
   }
   if (pst->selector == RGU_SEL_LWLC)
   {
      CMCHKPK(cmPkPtr,(PTR) staInd, mBuf);
   }
   else
   {
      if (cmPkRguDStaIndInfo(staInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
           SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ERGU077, (ErrVal)0, "Packing failed");
#endif      
        SPutSBuf(pst->region, pst->pool, (Data *)staInd, 
                                         sizeof(RguDStaIndInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      } 
      if (SPutSBuf(pst->region, pst->pool, (Data *)staInd,
                                  sizeof(RguDStaIndInfo)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ERGU079, (ErrVal)0, "Packing failed");
#endif      
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      staInd = NULLP;
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU078, (ErrVal)0, "Packing failed");
#endif      
      if (staInd != NULLP)
      {
         SPutSBuf(pst->region, pst->pool, (Data *)staInd, sizeof(RguDStaIndInfo));
      }
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) EVTRGUDSTAIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief Status Indication from MAC to RLC  
 * as a response to the staRsp primitive from RLC.
 * Informs RLC of the totalBufferSize and Timing Info 
 * for the transmission on dedicated channels.
*
* @details
*
*     Function : cmUnpkRguDStaInd
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   RguDStaIndInfo  *  staInd
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkRguDStaInd
(
RguDStaInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguDStaInd(func, pst, mBuf)
RguDStaInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   RguDStaIndInfo *staInd;
   
   TRC3(cmUnpkRguDStaInd)

   if (SUnpkS16(&suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU080, (ErrVal)0, "UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector == RGU_SEL_LWLC)
   {
      CMCHKUNPK(cmUnpkPtr,(PTR *) &staInd, mBuf);
   }
   else 
   {
      if ((SGetSBuf(pst->region, pst->pool, (Data **)&staInd, sizeof(RguDStaIndInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGU081, (ErrVal)0, "UnPacking failed");
#endif      
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      if (cmUnpkRguDStaIndInfo(staInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ERGU082, (ErrVal)0, "UnPacking failed");
#endif      
         SPutMsg(mBuf);
         SPutSBuf(pst->region, pst->pool, (Data *)staInd, sizeof(RguDStaIndInfo));
         RETVALUE(RFAILED);
      }
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, staInd));
}

#ifdef ANSI
PUBLIC S16 cmPkRguLcFlowCntrlInfo
(
RguLcFlowCntrlInfo *param,
Buffer             *mBuf
)
#else
PUBLIC S16 cmPkRguLcFlowCntrlInfo (param,mBuf)
RguLcFlowCntrlInfo *param;
Buffer             *mBuf;
#endif
{
  TRC3(cmPkRguLcFlowCntrlInfo);
  CMCHKPK(SPkU32, param->maxBo4FlowCtrl, mBuf);
  CMCHKPK(SPkU32, param->pktAdmitCnt, mBuf);
  CMCHKPK(cmPkLteLcId, param->lcId, mBuf);

  RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 cmPkRguUeFlowCntrlInfo
(
RguUeFlowCntrlInfo *param,
Buffer             *mBuf
)
#else
PUBLIC S16 cmPkRguUeFlowCntrlInfo (param,mBuf)
RguUeFlowCntrlInfo *param;
Buffer             *mBuf;
#endif
{
  U32 idx;

  TRC3(cmPkRguUeFlowCntrlInfo);

  for(idx=(param->numLcs - 1); idx >= 0; idx--)
  {
    cmPkRguLcFlowCntrlInfo(&param->lcInfo[idx],mBuf);
  }
  CMCHKPK(SPkU32, param->numLcs, mBuf);
  CMCHKPK(cmPkLteRnti, param->ueId, mBuf);
  RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 cmPkRguFlowCntrlInfo
(
RguFlowCntrlInd *param, 
Buffer          *mBuf
)
#else
PUBLIC S16 cmPkRguFlowCntrlInfo(flowCntrlInd, mBuf)
RguFlowCntrlInd *param;
Buffer          *mBuf;
#endif
{
  U32 idx;

  TRC3(cmPkRguFlowCntrlInfo);

  for (idx=(param->numUes - 1); idx >= 0; idx--)
  {
    cmPkRguUeFlowCntrlInfo(&param->ueFlowCntrlInfo[idx],mBuf);
  }
  CMCHKPK(SPkU32, param->numUes, mBuf);
  CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
  RETVALUE(ROK);
}

/**
* @brief Flow Cntrl Indication from MAC to RLC  
 * Informs RLC of the LCs on which flow control
 * to be performed.
*
* @details
*
*     Function : cmPkRguFlowCntrlInd
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   RguFlowCntrlInd *staInd
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkRguFlowCntrlInd
(
Pst* pst,
SuId suId,
RguFlowCntrlInd  *flowCntrlInd
)
#else
PUBLIC S16 cmPkRguFlowCntrlInd(pst, suId, flowCntrlInd)
Pst* pst;
SuId suId;
RguFlowCntrlInd   *flowCntrlInd;
#endif
{
   Buffer *mBuf = NULLP;

   TRC3(cmPkRguFlowCntrlInd);
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU076, (ErrVal)0, "Packing failed");
#endif      
      RETVALUE(RFAILED);
   }
   if (pst->selector == RGU_SEL_LWLC)
   {
      CMCHKPK(cmPkPtr,(PTR) flowCntrlInd, mBuf);
   }
   else
   {
      if (cmPkRguFlowCntrlInfo(flowCntrlInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
           SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ERGU077, (ErrVal)0, "Packing failed");
#endif      
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      } 
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU078, (ErrVal)0, "Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   
   pst->event = (Event) EVTRGUFLOWCNTRLIND;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkRguLcFlowCntrlInfo
(
RguLcFlowCntrlInfo *param,
Buffer           *mBuf
)
#else
PUBLIC S16 cmUnpkRguLcFlowCntrlInfo (param,mBuf)
RguLcFlowCntrlInfo *param;
Buffer           *mBuf;
#endif
{
  TRC3(cmUnpkRguLcFlowCntrlInfo);

  CMCHKUNPK(cmUnpkLteLcId, &param->lcId, mBuf);
  CMCHKUNPK(SUnpkU32, &param->pktAdmitCnt, mBuf);
  CMCHKUNPK(SUnpkU32, &param->maxBo4FlowCtrl, mBuf);
  
  RETVALUE(ROK);
}
#ifdef ANSI
PUBLIC S16 cmUnpkRguUeFlowCntrlInfo
(
RguUeFlowCntrlInfo *param,
Buffer           *mBuf
)
#else
PUBLIC S16 cmUnpkRguUeFlowCntrlInfo (param,mBuf)
RguUeFlowCntrlInfo *param;
Buffer           *mBuf;
#endif
{
  U32 idx;
  TRC3(cmUnpkRguUeFlowCntrlInfo);
  CMCHKUNPK(cmUnpkLteRnti, &param->ueId, mBuf);
  CMCHKUNPK(SUnpkU32, &param->numLcs, mBuf);
  for(idx=0; idx < param->numLcs; idx++)
  {
    cmUnpkRguLcFlowCntrlInfo(&param->lcInfo[idx],mBuf);
  }
  RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 cmUnpkRguFlowCntrlInfo
(
RguFlowCntrlInd *param, 
Buffer           *mBuf
)
#else
PUBLIC S16 cmUnpkRguFlowCntrlInfo(flowCntrlInfo, mBuf)
RguFlowCntrlInd *param;
Buffer           *mBuf;
#endif
{
  U32 idx; 
  
  TRC3(cmUnpkRguFlowCntrlInfo);

  CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
  CMCHKUNPK(SUnpkU32, &param->numUes, mBuf);
  for (idx=0; idx < param->numUes; idx++)
  {
    cmUnpkRguUeFlowCntrlInfo(&param->ueFlowCntrlInfo[idx],mBuf);
  }
  RETVALUE(ROK);
}

/**
* @brief Flow control indication from MAC to RLC  
* Informs RLC of the LCs on which flow control to  
* be started
*
* @details
*
*     Function : cmUnpkRguFlowCntrlInd
*
*  @param[in]   RguFlowCntrlInd func
*  @param[in]   Pst    *pst
*  @param[in]   Buffer *mBuf
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkRguFlowCntrlInd
(
RguFlowCntrlIndInfo func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguFlowCntrlInd(func, pst, mBuf)
RguFlowCntrlIndInfo func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   RguFlowCntrlInd *flowCntrlInd;
   
   TRC3(cmUnpkRguFlowCntrlInd)

   if (SUnpkS16(&suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ERGU080, (ErrVal)0, "UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector == RGU_SEL_LWLC)
   {
      CMCHKUNPK(cmUnpkPtr,(PTR *) &flowCntrlInd, mBuf);
   }
   else 
   {
      if ((SGetSBuf(pst->region, pst->pool, (Data **)&flowCntrlInd, sizeof(RguFlowCntrlInd))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ERGU081, (ErrVal)0, "UnPacking failed");
#endif      
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      if (cmUnpkRguFlowCntrlInfo(flowCntrlInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ERGU082, (ErrVal)0, "UnPacking failed");
#endif      
         SPutMsg(mBuf);
         SPutSBuf(pst->region, pst->pool, (Data *)flowCntrlInd, sizeof(RguFlowCntrlInd));
         RETVALUE(RFAILED);
      }
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, flowCntrlInd));
}

/***********************************************************
*
*     Func : cmPkRguPduInfo
*
*
*     Desc : RguPduInfo
 * PDU information given on a logical channel
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRguPduInfo
(
RguPduInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRguPduInfo(param, mBuf)
RguPduInfo *param;
Buffer *mBuf;
#endif
{
   S32 i;

   TRC3(cmPkRguPduInfo);

   for (i=param->numPdu-1; i >= 0; i--) {
     /* rgu_c_001.main_3: ccpu00111328: S16 is renamed as MsgLen */
      MsgLen msgLen = 0;
      if (SFndLenMsg(param->mBuf[i], &msgLen) != ROK)
         RETVALUE(RFAILED);
      if (SCatMsg(mBuf, param->mBuf[i], M1M2) != ROK)
         RETVALUE(RFAILED);
      SPutMsg(param->mBuf[i]);
      CMCHKPK(cmPkMsgLen, msgLen, mBuf);
   }
   CMCHKPK(SPkU8, param->numPdu, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRguPduInfo
*
*
*     Desc : RguPduInfo
 * PDU information given on a logical channel
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRguPduInfo
(
RguPduInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguPduInfo(param, mBuf)
RguPduInfo *param;
Buffer *mBuf;
#endif
{
   S32 i;

   TRC3(cmUnpkRguPduInfo);

   CMCHKUNPK(SUnpkU8, &param->numPdu, mBuf);
   for (i=0; i<param->numPdu; i++) {
      MsgLen msgLen, totalMsgLen;
      CMCHKUNPK(cmUnpkMsgLen, &msgLen, mBuf);
      if (SFndLenMsg(mBuf, &totalMsgLen) != ROK)
         RETVALUE(RFAILED);
      if (SSegMsg(mBuf, totalMsgLen-msgLen, &param->mBuf[i]) != ROK)
         RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRguDBoReport
*
*
*     Desc : RguDBoReport
 * Buffer Occupancy Report for dedicated logical channel
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRguDBoReport
(
RguDBoReport *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRguDBoReport(param, mBuf)
RguDBoReport *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRguDBoReport);

   CMCHKPK(SPkU32, param->oldestSduArrTime, mBuf);
   CMCHKPK(SPkU32, param->staPduBo, mBuf);
#ifdef CCPU_OPT
   CMCHKPK(SPkU8, param->staPduPrsnt, mBuf);
   CMCHKPK(SPkU16, param->estRlcHdrSz, mBuf);
#endif
   CMCHKPK(SPkS32, param->bo, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRguDBoReport
*
*
*     Desc : RguDBoReport
 * Buffer Occupancy Report for dedicated logical channel
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRguDBoReport
(
RguDBoReport *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguDBoReport(param, mBuf)
RguDBoReport *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRguDBoReport);

   CMCHKUNPK(SUnpkS32, &param->bo, mBuf);
#ifdef CCPU_OPT
   CMCHKUNPK(SUnpkU16, &param->estRlcHdrSz, mBuf);
   CMCHKUNPK(SUnpkU8, &param->staPduPrsnt, mBuf);
#endif
   
   CMCHKUNPK(SUnpkU32, &param->staPduBo, mBuf);
   CMCHKUNPK(SUnpkU32, &param->oldestSduArrTime, mBuf);
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkRguCDatReqInfo
*
*
*     Desc : RguCDatReqInfo
 * DatReq from RLC to MAC for Common Channels(BCCH, PCCH and CCCH)
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRguCDatReqInfo
(
RguCDatReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRguCDatReqInfo(param, mBuf)
RguCDatReqInfo *param;
Buffer *mBuf;
#endif
{
   MsgLen msgLen;

   TRC3(cmPkRguCDatReqInfo);

   if (param->pdu != NULLP)
   {
      if (SFndLenMsg(param->pdu, &msgLen) != ROK)
         RETVALUE(RFAILED);
      if (SCatMsg(mBuf, param->pdu, M1M2) != ROK)
         RETVALUE(RFAILED);
      SPutMsg(param->pdu);
      CMCHKPK(cmPkMsgLen, msgLen, mBuf);
   }
   switch(param->lcType) {
      case CM_LTE_LCH_CCCH:
         CMCHKPK(cmPkLteRnti, param->u.rnti, mBuf);
         break;
      case CM_LTE_LCH_BCCH:
      case CM_LTE_LCH_PCCH:
         CMCHKPK(cmPkLteTimingInfo, &param->u.timeToTx, mBuf);
         break;
      default :
         RETVALUE(RFAILED);
   }
   CMCHKPK(SPkU32, param->transId, mBuf);
   CMCHKPK(cmPkLteLcType, param->lcType, mBuf);
   CMCHKPK(cmPkLteLcId, param->lcId, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRguCDatReqInfo
*
*
*     Desc : RguCDatReqInfo
 * DatReq from RLC to MAC for Common Channels(BCCH, PCCH and CCCH)
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRguCDatReqInfo
(
RguCDatReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguCDatReqInfo(param, mBuf)
RguCDatReqInfo *param;
Buffer *mBuf;
#endif
{
   MsgLen msgLen, totalMsgLen;

   TRC3(cmUnpkRguCDatReqInfo);

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteLcId, &param->lcId, mBuf);
   CMCHKUNPK(cmUnpkLteLcType, &param->lcType, mBuf);
   CMCHKUNPK(SUnpkU32, &param->transId, mBuf);
   switch(param->lcType) {
      case CM_LTE_LCH_BCCH:
      case CM_LTE_LCH_PCCH:
         CMCHKUNPK(cmUnpkLteTimingInfo, &param->u.timeToTx, mBuf);
         break;
      case CM_LTE_LCH_CCCH:
         CMCHKUNPK(cmUnpkLteRnti, &param->u.rnti, mBuf);
         break;
      default :
         RETVALUE(RFAILED);
   }
   SFndLenMsg(mBuf, &msgLen);
   if (msgLen > 0)
   {
      CMCHKUNPK(cmUnpkMsgLen, &msgLen, mBuf);
      if (SFndLenMsg(mBuf, &totalMsgLen) != ROK)
         RETVALUE(RFAILED);
      if (SSegMsg(mBuf, totalMsgLen-msgLen, &param->pdu) != ROK)
         RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRguLchDatReq
*
*
*     Desc : RguLchDatReq
 * DatReq Information of a logical channel
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRguLchDatReq
(
RguLchDatReq *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRguLchDatReq(param, mBuf)
RguLchDatReq *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRguLchDatReq);

#ifdef L2_OPTMZ
   CMCHKPK(SPkU8, param->freeBuff, mBuf);
#endif
   CMCHKPK(SPkU8, param->setMaxUlPrio, mBuf);
   CMCHKPK(cmPkRguPduInfo, &param->pdu, mBuf);
   CMCHKPK(cmPkRguDBoReport, &param->boReport, mBuf);
   CMCHKPK(cmPkLteLcId, param->lcId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRguLchDatReq
*
*
*     Desc : RguLchDatReq
 * DatReq Information of a logical channel
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRguLchDatReq
(
RguLchDatReq *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguLchDatReq(param, mBuf)
RguLchDatReq *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRguLchDatReq);

   CMCHKUNPK(cmUnpkLteLcId, &param->lcId, mBuf);
   CMCHKUNPK(cmUnpkRguDBoReport, &param->boReport, mBuf);
   CMCHKUNPK(cmUnpkRguPduInfo, &param->pdu, mBuf);
   CMCHKUNPK(SUnpkU8, &param->setMaxUlPrio, mBuf);
#ifdef L2_OPTMZ
   CMCHKUNPK(SUnpkU8, &param->freeBuff, mBuf);
#endif
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkRguDatReqTb
*
*
*     Desc : RguDatReqTb
* DatReq from RLC to MAC for dedicated channels of a UE
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRguDatReqTb
(
RguDatReqTb *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRguDatReqTb(param, mBuf)
RguDatReqTb *param;
Buffer *mBuf;
#endif
{
   S32 i;

   TRC3(cmPkRguDatReqTb);
   /*rgu_c_001.main_5 - ADD - L2M Support */
#ifdef LTE_L2_MEAS
   CMCHKPK(SPkU32, param->tbId, mBuf);
#endif
   for (i=param->nmbLch-1; i >= 0; i--) {
      CMCHKPK(cmPkRguLchDatReq, &param->lchData[i], mBuf);
   }
   CMCHKPK(SPkU8, param->nmbLch, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRguDatReqTb
*
*
*     Desc : RguDatReqTb
 * DatReq from RLC to MAC for dedicated channels of a UE
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef LTE_L2_MEAS
#ifdef ANSI
PUBLIC S16 cmUnpkRguDatReqTb
(
Pst         *pst, 
RguDatReqTb *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguDatReqTb(pst, param, mBuf)
Pst         *pst;   
RguDatReqTb *param;
Buffer *mBuf;
#endif
#else
#ifdef ANSI
PUBLIC S16 cmUnpkRguDatReqTb
(
RguDatReqTb *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguDatReqTb(param, mBuf)
RguDatReqTb *param;
Buffer *mBuf;
#endif
#endif
{
   S32 i;

   TRC3(cmUnpkRguDatReqTb);

   CMCHKUNPK(SUnpkU8, &param->nmbLch, mBuf);
   for (i=0; i<param->nmbLch; i++) {
      CMCHKUNPK(cmUnpkRguLchDatReq, &param->lchData[i], mBuf);
   }
   /*rgu_c_001.main_5 - ADD - L2M Support */
#ifdef LTE_L2_MEAS
   CMCHKUNPK(SUnpkU32, &param->tbId, mBuf);
#endif
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkRguDDatReqInfo
*
*
*     Desc : RguDDatReqInfo
 * DatReq from RLC to MAC for dedicated channels of a UE
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
   /*rgu_c_001.main_5 - ADD - L2M Support */
#ifdef LTE_L2_MEAS
#ifdef ANSI
PUBLIC S16 cmPkRguDDatReqInfo
(
Pst            *pst,
RguDDatReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRguDDatReqInfo(pst, param, mBuf)
Pst            *pst;
RguDDatReqInfo *param;
Buffer *mBuf;
#endif
#else
#ifdef ANSI
PUBLIC S16 cmPkRguDDatReqInfo
(
RguDDatReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRguDDatReqInfo(param, mBuf)
RguDDatReqInfo *param;
Buffer *mBuf;
#endif
#endif
{
   S32 i;
   S32 idx;

   TRC3(cmPkRguDDatReqInfo);

   for(idx = (param->nmbOfUeGrantPerTti-1); idx >= 0; idx--)
   {
      RguDDatReqPerUe *datReq = &param->datReq[idx];
      for (i=RGU_MAX_TB-1; i >= 0; i--) 
      {
         CMCHKPK(cmPkRguDatReqTb, &datReq->datReqTb[i], mBuf);
      }
      CMCHKPK(SPkU8, datReq->nmbOfTbs, mBuf);
      CMCHKPK(SPkU32, datReq->transId, mBuf);
      CMCHKPK(cmPkLteRnti, datReq->rnti, mBuf);
   }
   CMCHKPK(SPkU8, param->nmbOfUeGrantPerTti, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRguDDatReqInfo
*
*
*     Desc : RguDDatReqInfo
 * DatReq from RLC to MAC for dedicated channels of a UE
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef LTE_L2_MEAS
#ifdef ANSI
PUBLIC S16 cmUnpkRguDDatReqInfo
(
Pst            *pst, 
RguDDatReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguDDatReqInfo(pst, param, mBuf)
Pst            *pst;
RguDDatReqInfo *param;
Buffer *mBuf;
#endif
#else
#ifdef ANSI
PUBLIC S16 cmUnpkRguDDatReqInfo
(
RguDDatReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguDDatReqInfo(param, mBuf)
RguDDatReqInfo *param;
Buffer *mBuf;
#endif
#endif
{
   S32 i;
  /* After Merging from 2.1 to 2.2 */
   /*rgu_c_001.main_5 - ADD - L2M Support */
#ifdef LTE_L2_MEAS
   S16 retVal;
#endif
   S32 idx;

   TRC3(cmUnpkRguDDatReqInfo);

  /* After Merging from 2.1 to 2.2 */
   /*rgu_c_001.main_5 - ADD - L2M Support */
#ifdef LTE_L2_MEAS
   retVal = ROK;
#endif
   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->nmbOfUeGrantPerTti, mBuf);
   for(idx = 0; idx < param->nmbOfUeGrantPerTti; idx++)
   { 
      RguDDatReqPerUe *datReq = &param->datReq[idx];
      CMCHKUNPK(cmUnpkLteRnti, &datReq->rnti, mBuf);
      CMCHKUNPK(SUnpkU32, &datReq->transId, mBuf);
      CMCHKUNPK(SUnpkU8, &datReq->nmbOfTbs, mBuf);
      /* rgu_c_001.main_4 - Changes for MIMO feature addition */
      for (i=0; i<RGU_MAX_TB; i++) 
      {
         /*rgu_c_001.main_5 - ADD - L2M Support */
#ifdef LTE_L2_MEAS
         /* After Merging from 2.1 to 2.2 */
         retVal = cmUnpkRguDatReqTb(pst, &datReq->datReqTb[i], mBuf);
         if(retVal != ROK)
         {
            RETVALUE(RFAILED);
         }
#else
         CMCHKUNPK(cmUnpkRguDatReqTb, &datReq->datReqTb[i], mBuf);
#endif
      }
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRguCDatIndInfo
*
*
*     Desc : RguCDatIndInfo
 * DatInd from MAC to RLC on CCCH
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRguCDatIndInfo
(
RguCDatIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRguCDatIndInfo(param, mBuf)
RguCDatIndInfo *param;
Buffer *mBuf;
#endif
{
   MsgLen msgLen;

   TRC3(cmPkRguCDatIndInfo);

   if (SFndLenMsg(param->pdu, &msgLen) != ROK)
      RETVALUE(RFAILED);
   if (SCatMsg(mBuf, param->pdu, M1M2) != ROK)
      RETVALUE(RFAILED);
   SPutMsg(param->pdu);
   CMCHKPK(cmPkMsgLen, msgLen, mBuf);
   CMCHKPK(cmPkLteLcId, param->lcId, mBuf);
   CMCHKPK(cmPkLteRnti, param->rnti, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRguCDatIndInfo
*
*
*     Desc : RguCDatIndInfo
 * DatInd from MAC to RLC on CCCH
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRguCDatIndInfo
(
RguCDatIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguCDatIndInfo(param, mBuf)
RguCDatIndInfo *param;
Buffer *mBuf;
#endif
{
   MsgLen msgLen, totalMsgLen;

   TRC3(cmUnpkRguCDatIndInfo);

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &param->rnti, mBuf);
   CMCHKUNPK(cmUnpkLteLcId, &param->lcId, mBuf);
   CMCHKUNPK(cmUnpkMsgLen, &msgLen, mBuf);
   if (SFndLenMsg(mBuf, &totalMsgLen) != ROK)
      RETVALUE(RFAILED);
   if (SSegMsg(mBuf, totalMsgLen-msgLen, &param->pdu) != ROK)
      RETVALUE(RFAILED);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRguLchDatInd
*
*
*     Desc : RguLchDatInd
 * DatInd Information for a logical channel
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRguLchDatInd
(
RguLchDatInd *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRguLchDatInd(param, mBuf)
RguLchDatInd *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkRguLchDatInd);

      CMCHKPK(cmPkRguPduInfo, &param->pdu, mBuf);
   CMCHKPK(cmPkLteLcId, param->lcId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRguLchDatInd
*
*
*     Desc : RguLchDatInd
 * DatInd Information for a logical channel
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRguLchDatInd
(
RguLchDatInd *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguLchDatInd(param, mBuf)
RguLchDatInd *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkRguLchDatInd);

   CMCHKUNPK(cmUnpkLteLcId, &param->lcId, mBuf);
   CMCHKUNPK(cmUnpkRguPduInfo, &param->pdu, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRguDDatIndInfo
*
*
*     Desc : RguDDatIndInfo
 * Data Indication from MAC to RLC for dedicated channels of a UE
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRguDDatIndInfo
(
RguDDatIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRguDDatIndInfo(param, mBuf)
RguDDatIndInfo *param;
Buffer *mBuf;
#endif
{
   S32 i;

   TRC3(cmPkRguDDatIndInfo);

#ifdef LTE_L2_MEAS
   CMCHKPK(SPkU8, param->burstInd, mBuf);
   CMCHKPK(SPkU32, param->ttiCnt, mBuf);
#endif
   for (i=param->numLch-1; i >= 0; i--) {
      CMCHKPK(cmPkRguLchDatInd, &param->lchData[i], mBuf);
   }
   CMCHKPK(SPkU8, param->numLch, mBuf);
   CMCHKPK(cmPkLteRnti, param->rnti, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRguDDatIndInfo
*
*
*     Desc : RguDDatIndInfo
 * Data Indication from MAC to RLC for dedicated channels of a UE
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRguDDatIndInfo
(
RguDDatIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguDDatIndInfo(param, mBuf)
RguDDatIndInfo *param;
Buffer *mBuf;
#endif
{
   S32 i;

   TRC3(cmUnpkRguDDatIndInfo);

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &param->rnti, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numLch, mBuf);
   for (i=0; i<param->numLch; i++) {
      CMCHKUNPK(cmUnpkRguLchDatInd, &param->lchData[i], mBuf);
   }
#ifdef LTE_L2_MEAS
   CMCHKUNPK(SUnpkU32, &param->ttiCnt, mBuf);
   CMCHKUNPK(SUnpkU8, &param->burstInd, mBuf);
#endif
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkRguCStaRspInfo
*
*
*     Desc : RguCStaRspInfo
 * Status Response from RLC to MAC  for common logical channel
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRguCStaRspInfo
(
RguCStaRspInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRguCStaRspInfo(param, mBuf)
RguCStaRspInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRguCStaRspInfo);

   switch(param->lcType) {
      case CM_LTE_LCH_CCCH:
         CMCHKPK(cmPkLteRnti, param->u.rnti, mBuf);
         break;
      case CM_LTE_LCH_BCCH:
      case CM_LTE_LCH_PCCH:
         CMCHKPK(cmPkLteTimingInfo, &param->u.timeToTx, mBuf);
         break;
      default :
         RETVALUE(RFAILED);
   }
   CMCHKPK(SPkS32, param->bo, mBuf);
   CMCHKPK(cmPkLteLcType, param->lcType, mBuf);
   CMCHKPK(cmPkLteLcId, param->lcId, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRguCStaRspInfo
*
*
*     Desc : RguCStaRspInfo
 * Status Response from RLC to MAC  for common logical channel
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRguCStaRspInfo
(
RguCStaRspInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguCStaRspInfo(param, mBuf)
RguCStaRspInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRguCStaRspInfo);

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteLcId, &param->lcId, mBuf);
   CMCHKUNPK(cmUnpkLteLcType, &param->lcType, mBuf);
   CMCHKUNPK(SUnpkS32, &param->bo, mBuf);
   switch(param->lcType) {
      case CM_LTE_LCH_BCCH:
      case CM_LTE_LCH_PCCH:
         CMCHKUNPK(cmUnpkLteTimingInfo, &param->u.timeToTx, mBuf);
         break;
      case CM_LTE_LCH_CCCH:
         CMCHKUNPK(cmUnpkLteRnti, &param->u.rnti, mBuf);
         break;
      default :
         RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRguDStaRspInfo
*
*
*     Desc : RguDStaRspInfo
 * Status Response from RLC to MAC  for dedicated logical channel
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRguDStaRspInfo
(
RguDStaRspInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRguDStaRspInfo(param, mBuf)
RguDStaRspInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRguDStaRspInfo);

   CMCHKPK(cmPkRguDBoReport, &param->boReport, mBuf);
   CMCHKPK(cmPkLteLcId, param->lcId, mBuf);
   CMCHKPK(cmPkLteRnti, param->rnti, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRguDStaRspInfo
*
*
*     Desc : RguDStaRspInfo
 * Status Response from RLC to MAC  for dedicated logical channel
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRguDStaRspInfo
(
RguDStaRspInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguDStaRspInfo(param, mBuf)
RguDStaRspInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRguDStaRspInfo);

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &param->rnti, mBuf);
   CMCHKUNPK(cmUnpkLteLcId, &param->lcId, mBuf);
   CMCHKUNPK(cmUnpkRguDBoReport, &param->boReport, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRguCStaIndInfo
*
*
*     Desc : RguCStaIndInfo
 * Status Indication from MAC to RLC for common logical channel
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRguCStaIndInfo
(
RguCStaIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRguCStaIndInfo(param, mBuf)
RguCStaIndInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRguCStaIndInfo);
   CMCHKPK(cmPkLteRnti, param->rnti, mBuf);
   CMCHKPK(SPkU32, param->transId, mBuf);
   CMCHKPK(cmPkLteLcId, param->lcId, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRguCStaIndInfo
*
*
*     Desc : RguCStaIndInfo
 * Status Indication from MAC to RLC for common logical channel
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRguCStaIndInfo
(
RguCStaIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguCStaIndInfo(param, mBuf)
RguCStaIndInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRguCStaIndInfo);

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteLcId, &param->lcId, mBuf);
   CMCHKUNPK(SUnpkU32, &param->transId, mBuf);
   /*TODO:Mukesh: Need to check why rnti unpacking is missing*/
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkRguLchStaInd
*
*
*     Desc : RguLchStaInd
 * StaInd info for each logical channel of a UE
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRguLchStaInd
(
RguLchStaInd *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRguLchStaInd(param, mBuf)
RguLchStaInd *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkRguLchStaInd);

   CMCHKPK(SPkS16, param->totBufSize, mBuf);
   CMCHKPK(cmPkLteLcId, param->lcId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRguLchStaInd
*
*
*     Desc : RguLchStaInd
 * StaInd info for each logical channel of a UE
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRguLchStaInd
(
RguLchStaInd *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguLchStaInd(param, mBuf)
RguLchStaInd *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkRguLchStaInd);

   CMCHKUNPK(cmUnpkLteLcId, &param->lcId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->totBufSize, mBuf);
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkRguStaIndTb
*
*
*     Desc : RguStaIndTb
* StaInd from RLC to MAC for dedicated channels of a UE
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRguStaIndTb
(
RguStaIndTb *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRguStaIndTb(param, mBuf)
RguStaIndTb *param;
Buffer *mBuf;
#endif
{
   S32 i;

   TRC3(cmPkRguStaIndTb);

#ifdef LTE_L2_MEAS
   CMCHKPK(SPkU16, param->status, mBuf);
   CMCHKPK(SPkU32, param->tbId, mBuf);
#endif   
   for (i=param->nmbLch-1; i >= 0; i--) {
      CMCHKPK(cmPkRguLchStaInd, &param->lchStaInd[i], mBuf);
   }
   CMCHKPK(SPkU8, param->nmbLch, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRguStaIndTb
*
*
*     Desc : RguStaIndTb
* StaInd from RLC to MAC for dedicated channels of a UE
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRguStaIndTb
(
RguStaIndTb *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguStaIndTb(param, mBuf)
RguStaIndTb *param;
Buffer *mBuf;
#endif
{
   S32 i;

   TRC3(cmUnpkRguStaIndTb);

   CMCHKUNPK(SUnpkU8, &param->nmbLch, mBuf);
   for (i=0; i<param->nmbLch; i++) {
      CMCHKUNPK(cmUnpkRguLchStaInd, &param->lchStaInd[i], mBuf);
   }
#ifdef LTE_L2_MEAS
   CMCHKUNPK(SUnpkU32, &param->tbId, mBuf);
   CMCHKUNPK(SUnpkU16, &param->status, mBuf);
#endif   
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkRguDStaIndInfo
*
*
*     Desc : RguDStaIndInfo
 * StaInd from MAC to RLC for dedicated logical channels of a UE
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkRguDStaIndInfo
(
RguDStaIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkRguDStaIndInfo(param, mBuf)
RguDStaIndInfo *param;
Buffer *mBuf;
#endif
{
   S32 i;
   S32 idx;

   TRC3(cmPkRguDStaIndInfo);

   for(idx = (param->nmbOfUeGrantPerTti - 1); idx >= 0 ; idx--)
   {
      RguDStaIndPerUe *staInd = &param->staInd[idx];
      CMCHKPK(SPkU8, staInd->fillCtrlPdu, mBuf);
      for (i=staInd->nmbOfTbs-1; i >= 0; i--) {
         CMCHKPK(cmPkRguStaIndTb, &staInd->staIndTb[i], mBuf);
      }
      CMCHKPK(SPkU8, staInd->nmbOfTbs, mBuf);
      CMCHKPK(SPkU32,staInd->transId, mBuf);
      CMCHKPK(cmPkLteRnti, staInd->rnti, mBuf);
   }
   CMCHKPK(SPkU8, param->nmbOfUeGrantPerTti, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkRguDStaIndInfo
*
*
*     Desc : RguDStaIndInfo
 * StaInd from MAC to RLC for dedicated logical channels of a UE
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkRguDStaIndInfo
(
RguDStaIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRguDStaIndInfo(param, mBuf)
RguDStaIndInfo *param;
Buffer *mBuf;
#endif
{
   S32 i;
   S32 idx;

   TRC3(cmUnpkRguDStaIndInfo);

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->nmbOfUeGrantPerTti, mBuf);
   for(idx = 0; idx < param->nmbOfUeGrantPerTti; idx++)
   {
      RguDStaIndPerUe *staInd = &param->staInd[idx];
      CMCHKUNPK(cmUnpkLteRnti, &staInd->rnti, mBuf);
      CMCHKUNPK(SUnpkU32, &staInd->transId, mBuf);
      CMCHKUNPK(SUnpkU8, &staInd->nmbOfTbs, mBuf);
      for (i=0; i<staInd->nmbOfTbs; i++) 
      {
         CMCHKUNPK(cmUnpkRguStaIndTb, &staInd->staIndTb[i], mBuf);
      }
      CMCHKUNPK(SUnpkU8, &staInd->fillCtrlPdu, mBuf);
   }
   RETVALUE(ROK);
}

#endif


/**********************************************************************
 
         End of file:     rgu.c@@/main/6 - Wed Jul 27 14:15:21 2011
 
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
/main/2      ---     sm                1. Initial Release.
/main/4      ---      rgu_c_001.main_3 ms  1.ccpu00111328: S16 is renamed as MsgLen
/main/5      ---      rgu_c_001.main_4  gvj 1. Changes for MIMO feature addition              
/main/6      ---      rgu_c_001.main_5 gvj             1. Updated for LTE MAC Rel 3.1
*********************************************************************91*/
