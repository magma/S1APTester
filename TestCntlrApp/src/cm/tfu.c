

/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for pack/unpack of TFU interface primitives. 
  
     File:     tfu.c 
  
     Sid:      tfu.c@@/main/8 - Wed Jul 27 12:18:38 2011
  
     Prg:      sm
  
**********************************************************************/

/** @file tfu.c
@brief This file contains the packing/unpacking code for the TFU interface 
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
#include "cm_mblk.h"        /* Common LTE Defines */
#include "tfu.h"           /* RGU Interface defines */

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_lib.x"        /* Common Library Definitions */
#include "cm_hash.x"       /* Common Hash List Definitions */
#include "cm_lte.x"        /* Common LTE Defines */
#include "cm_mblk.x"        /* Common LTE Defines */
#include "tfu.x"           /* RGU Interface includes */

#if (defined(LCTFU))


/***********************************************************
*
*     Func : cmPkTfuBndReq
*
*
*     Desc : This API is used to send a Bind Request from MAC to PHY.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param spId SAP ID of the service provider.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuBndReq
(
Pst * pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 cmPkTfuBndReq(pst, suId, spId)
Pst * pst;
SuId suId;
SpId spId;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTfuBndReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU001, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU002, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU003, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTTFUBNDREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkTfuBndReq
*
*
*     Desc : This API is used to send a Bind Request from MAC to PHY.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param spId SAP ID of the service provider.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuBndReq
(
TfuBndReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuBndReq(func, pst, mBuf)
TfuBndReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   SpId spId;
   
   TRC3(cmUnpkTfuBndReq)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU004, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkS16(&spId, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU005, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   TFU_FREE_MSG(mBuf);
   RETVALUE((*func)(pst, suId, spId));
}


/***********************************************************
*
*     Func : cmPkTfuBndCfm
*
*
*     Desc : This API is used to receive a Bind Confirm from PHY to MAC.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param status Status of the bind request.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuBndCfm
(
Pst * pst,
SuId suId,
U8 status
)
#else
PUBLIC S16 cmPkTfuBndCfm(pst, suId, status)
Pst * pst;
SuId suId;
U8 status;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTfuBndCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU006, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SPkU8(status, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU007, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU008, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTTFUBNDCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkTfuBndCfm
*
*
*     Desc : This API is used to receive a Bind Confirm from PHY to MAC.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param status Status of the bind request.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuBndCfm
(
TfuBndCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuBndCfm(func, pst, mBuf)
TfuBndCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   U8 status;
   
   TRC3(cmUnpkTfuBndCfm)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU009, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkU8(&status, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU010, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   TFU_FREE_MSG(mBuf);
   RETVALUE((*func)(pst, suId, status));
}


/***********************************************************
*
*     Func : cmPkTfuUbndReq
*
*
*     Desc : This API is used to send an Unbind Request from MAC to PHY.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service provider.
 * @param reason Reason for Unbind request.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuUbndReq
(
Pst * pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 cmPkTfuUbndReq(pst, spId, reason)
Pst * pst;
SpId spId;
Reason reason;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTfuUbndReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU011, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SPkS16(reason, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU012, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU013, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTTFUUBNDREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkTfuUbndReq
*
*
*     Desc : This API is used to send an Unbind Request from MAC to PHY.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service provider.
 * @param reason Reason for Unbind request.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuUbndReq
(
TfuUbndReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuUbndReq(func, pst, mBuf)
TfuUbndReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   Reason reason;
   
   TRC3(cmUnpkTfuUbndReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU014, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkS16(&reason, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU015, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   TFU_FREE_MSG(mBuf);
   RETVALUE((*func)(pst, spId, reason));
}


/***********************************************************
*
*     Func : cmPkTfuSchBndReq
*
*
*     Desc : This API is used to send a Bind Request from Scheduler to PHY.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param spId SAP ID of the service provider.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuSchBndReq
(
Pst * pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 cmPkTfuSchBndReq(pst, suId, spId)
Pst * pst;
SuId suId;
SpId spId;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTfuSchBndReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU016, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU017, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU018, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTTFUSCHBNDREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkTfuSchBndReq
*
*
*     Desc : This API is used to send a Bind Request from Scheduler to PHY.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param spId SAP ID of the service provider.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuSchBndReq
(
TfuSchBndReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuSchBndReq(func, pst, mBuf)
TfuSchBndReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   SpId spId;
   
   TRC3(cmUnpkTfuSchBndReq)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU019, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkS16(&spId, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU020, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   TFU_FREE_MSG(mBuf);
   RETVALUE((*func)(pst, suId, spId));
}


/***********************************************************
*
*     Func : cmPkTfuSchBndCfm
*
*
*     Desc : This API is used to receive a Bind Confirm from PHY to Scheduler.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param status Status of the bind request.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuSchBndCfm
(
Pst * pst,
SuId suId,
U8 status
)
#else
PUBLIC S16 cmPkTfuSchBndCfm(pst, suId, status)
Pst * pst;
SuId suId;
U8 status;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTfuSchBndCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU021, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SPkU8(status, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU022, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU023, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTTFUSCHBNDCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkTfuSchBndCfm
*
*
*     Desc : This API is used to receive a Bind Confirm from PHY to Scheduler.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param status Status of the bind request.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuSchBndCfm
(
TfuSchBndCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuSchBndCfm(func, pst, mBuf)
TfuSchBndCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   U8 status;
   
   TRC3(cmUnpkTfuSchBndCfm)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU024, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkU8(&status, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU025, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   TFU_FREE_MSG(mBuf);
   RETVALUE((*func)(pst, suId, status));
}


/***********************************************************
*
*     Func : cmPkTfuSchUbndReq
*
*
*     Desc : This API is used to send an Unbind Request from Scheduler to PHY.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service provider.
 * @param reason Reason for Unbind request.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuSchUbndReq
(
Pst * pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 cmPkTfuSchUbndReq(pst, spId, reason)
Pst * pst;
SpId spId;
Reason reason;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTfuSchUbndReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU026, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SPkS16(reason, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU027, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU028, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTTFUSCHUBNDREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkTfuSchUbndReq
*
*
*     Desc : This API is used to send an Unbind Request from Scheduler to PHY.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service provider.
 * @param reason Reason for Unbind request.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuSchUbndReq
(
TfuSchUbndReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuSchUbndReq(func, pst, mBuf)
TfuSchUbndReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   Reason reason;
   
   TRC3(cmUnpkTfuSchUbndReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU029, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkS16(&reason, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU030, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   TFU_FREE_MSG(mBuf);
   RETVALUE((*func)(pst, spId, reason));
}


/***********************************************************
*
*     Func : cmPkTfuRaReqInd
*
*
*     Desc : This API is used to indication Random Access Request reception from
 * PHY to Scheduler.
 * @details This primitive is used by physical layer to indicate the reception
 * of a Random Access Request from a set of UEs. The information passed consists
 * of the RA-RNTI and the list of preambles received. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param raReqInd Pointer to the TfuRaReqIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuRaReqInd
(
Pst * pst,
SuId suId,
TfuRaReqIndInfo * raReqInd
)
#else
PUBLIC S16 cmPkTfuRaReqInd(pst, suId, raReqInd)
Pst * pst;
SuId suId;
TfuRaReqIndInfo * raReqInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTfuRaReqInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU031, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MEM(raReqInd);
      RETVALUE(RFAILED);
   }
   if (pst->selector == TFU_SEL_LC) {
      if (cmPkTfuRaReqIndInfo(raReqInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU032, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MEM(raReqInd);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if (cmPkPtr((PTR)raReqInd, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFUXXX, (ErrVal)0, "LWLC Packing failed");
#endif
         TFU_FREE_MEM(raReqInd);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }

   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU033, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MEM(raReqInd);
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      TFU_FREE_MEM(raReqInd);
   }

   pst->event = (Event) EVTTFURAREQIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkTfuRaReqInd
*
*
*     Desc : This API is used to indication Random Access Request reception from
 * PHY to Scheduler.
 * @details This primitive is used by physical layer to indicate the reception
 * of a Random Access Request from a set of UEs. The information passed consists
 * of the RA-RNTI and the list of preambles received. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param raReqInd Pointer to the TfuRaReqIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuRaReqInd
(
TfuRaReqInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuRaReqInd(func, pst, mBuf)
TfuRaReqInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   TfuRaReqIndInfo *raReqInd;
   
   TRC3(cmUnpkTfuRaReqInd)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU034, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      Mem   sMem;
      sMem.region = pst->region;
      sMem.pool = pst->pool;
      if ((cmAllocEvnt(sizeof(TfuRaReqIndInfo), TFU_BLKSZ, &sMem, (Ptr *)&raReqInd)) != ROK)            {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU035, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }


   if (pst->selector == TFU_SEL_LC) 
   {
      if (cmUnpkTfuRaReqIndInfo(raReqInd, mBuf) != ROK) {
         TFU_FREE_MEM(raReqInd);
         TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ETFU036, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if (cmUnpkPtr((PTR *)&raReqInd, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFUXXX, (ErrVal)0, "LWLC un-Packing failed");
#endif
         TFU_FREE_MEM(raReqInd);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   TFU_FREE_MSG(mBuf);
   RETVALUE((*func)(pst, suId, raReqInd));
}


/***********************************************************
*
*     Func : cmPkTfuRecpReq
*
*
*     Desc : This primitive is sent from Scheduler to PHY.
 * @details This primitive provides PHY with all the information required by 
 * PHY to decode transmissions from the UE on either PUCCH or PUSCH.
 * -# On PUCCH UE can transmit the following
 *    -# SR
 *    -# HARQ feedback
 *    -# CQI report
 *    -# HARQ + CQI
 *    -# HARQ + SR
 * -# On PUSCH UE can transmit the following
 *    -# Data
 *    -# Data + CQI
 *    -# Data + HARQ Feedback
 * This primitive carries all the information for the expected subframe for all
 * the UEs that have been scheduled to transmit.
 * @param pst Pointer to the post structure.
 * @param spId SAP ID of the service provider.
 * @param recpReq Pointer to the TfuRecpReqInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuRecpReq
(
Pst * pst,
SpId spId,
TfuRecpReqInfo * recpReq
)
#else
PUBLIC S16 cmPkTfuRecpReq(pst, spId, recpReq)
Pst * pst;
SpId spId;
TfuRecpReqInfo * recpReq;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTfuRecpReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU037, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MEM(recpReq);
      RETVALUE(RFAILED);
   }
   if (pst->selector == TFU_SEL_LC) {
      if (cmPkTfuRecpReqInfo(recpReq, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU038, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MEM(recpReq);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if (cmPkPtr((PTR)recpReq, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFUXXX, (ErrVal)0, "LWLC Packing failed");
#endif
         TFU_FREE_MEM(recpReq);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }


   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU039, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MEM(recpReq);
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      TFU_FREE_MEM(recpReq);
   }

   pst->event = (Event) EVTTFURECPREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

PUBLIC S16 cmUnpkTful1DataReq
(
TfuL1ReadReq func,
Pst *pst,
Buffer *mBuf
)
{
   SpId spId;
   U8 event;   
   TRC3(cmUnpkTfuRecpReq)

   SUnpkS16(&spId, mBuf);

   TFU_FREE_MSG(mBuf);
   RETVALUE((*func)(pst, spId, 0));
}


/***********************************************************
*
*     Func : cmUnpkTfuRecpReq
*
*
*     Desc : This primitive is sent from Scheduler to PHY.
 * @details This primitive provides PHY with all the information required by 
 * PHY to decode transmissions from the UE on either PUCCH or PUSCH.
 * -# On PUCCH UE can transmit the following
 *    -# SR
 *    -# HARQ feedback
 *    -# CQI report
 *    -# HARQ + CQI
 *    -# HARQ + SR
 * -# On PUSCH UE can transmit the following
 *    -# Data
 *    -# Data + CQI
 *    -# Data + HARQ Feedback
 * This primitive carries all the information for the expected subframe for all
 * the UEs that have been scheduled to transmit.
 * @param pst Pointer to the post structure.
 * @param spId SAP ID of the service provider.
 * @param recpReq Pointer to the TfuRecpReqInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuRecpReq
(
TfuRecpReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuRecpReq(func, pst, mBuf)
TfuRecpReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   TfuRecpReqInfo *recpReq;
   
   TRC3(cmUnpkTfuRecpReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU040, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      Mem   sMem;
      sMem.region = pst->region;
      sMem.pool = pst->pool;
      if ((cmAllocEvnt(sizeof(TfuRecpReqInfo), TFU_BLKSZ, &sMem, (Ptr *)&recpReq)) != ROK)            {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU041, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if (cmUnpkPtr((PTR *)&recpReq, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFUXXX, (ErrVal)0, "LWLC un-Packing failed");
#endif
         TFU_FREE_MEM(recpReq);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }

   if (pst->selector == TFU_SEL_LC) 
   {
      if (cmUnpkTfuRecpReqInfo(recpReq, (Ptr)&recpReq->memCp, mBuf) != ROK) {
         TFU_FREE_MEM(recpReq);
         TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ETFU042, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if (cmUnpkPtr((PTR*)&recpReq, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFUXXX, (ErrVal)0, "LWLC un-Packing failed");
#endif
         TFU_FREE_MEM(recpReq);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }

   TFU_FREE_MSG(mBuf);
   RETVALUE((*func)(pst, spId, recpReq));
}


/***********************************************************
*
*     Func : cmPkTfuUlCqiInd
*
*
*     Desc : This API is used to indicate CQI reporting from PHY to Scheduler
 * @details This primitive carries an estimate of the uplink Channel quality
 * index (CQI) for a list of UEs. This is an extimate of the uplink channel
 * quality i.e. the transmission from UE as calculated at the Physical layer at
 * the eNodeB. 
 * It carries a list of subband CQIs for each UE. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param ulCqiInd Pointer to the TfuUlCqiIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuUlCqiInd
(
Pst * pst,
SuId suId,
TfuUlCqiIndInfo * ulCqiInd
)
#else
PUBLIC S16 cmPkTfuUlCqiInd(pst, suId, ulCqiInd)
Pst * pst;
SuId suId;
TfuUlCqiIndInfo * ulCqiInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTfuUlCqiInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU043, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MEM(ulCqiInd);
      RETVALUE(RFAILED);
   }
   if (pst->selector == TFU_SEL_LC) {
      if (cmPkTfuUlCqiIndInfo(ulCqiInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU044, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MEM(ulCqiInd);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if (cmPkPtr((PTR)ulCqiInd, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFUXXX, (ErrVal)0, "LWLC Packing failed");
#endif
         TFU_FREE_MEM(ulCqiInd);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }

   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU045, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MEM(ulCqiInd);
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      TFU_FREE_MEM(ulCqiInd);
   }

   pst->event = (Event) EVTTFUULCQIIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkTfuUlCqiInd
*
*
*     Desc : This API is used to indicate CQI reporting from PHY to Scheduler
 * @details This primitive carries an estimate of the uplink Channel quality
 * index (CQI) for a list of UEs. This is an extimate of the uplink channel
 * quality i.e. the transmission from UE as calculated at the Physical layer at
 * the eNodeB. 
 * It carries a list of subband CQIs for each UE. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param ulCqiInd Pointer to the TfuUlCqiIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuUlCqiInd
(
TfuUlCqiInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuUlCqiInd(func, pst, mBuf)
TfuUlCqiInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   TfuUlCqiIndInfo *ulCqiInd;
   
   TRC3(cmUnpkTfuUlCqiInd)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU046, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      Mem   sMem;
      sMem.region = pst->region;
      sMem.pool = pst->pool;
      if ((cmAllocEvnt(sizeof(TfuUlCqiIndInfo), TFU_BLKSZ, &sMem, (Ptr *)&ulCqiInd)) != ROK)            {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU047, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }


   if (pst->selector == TFU_SEL_LC) 
   {
      if (cmUnpkTfuUlCqiIndInfo(ulCqiInd, (Ptr)&ulCqiInd->memCp, mBuf) != ROK) {
         TFU_FREE_MEM(ulCqiInd);
         TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ETFU048, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if (cmUnpkPtr((PTR *)&ulCqiInd, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFUXXX, (ErrVal)0, "LWLC un-Packing failed");
#endif
         TFU_FREE_MEM(ulCqiInd);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   TFU_FREE_MSG(mBuf);
   RETVALUE((*func)(pst, suId, ulCqiInd));
}


/***********************************************************
*
*     Func : cmPkTfuHqInd
*
*
*     Desc : This Primitive carries the HARQ Feedback from PHY to scheduler
 * @details HARQ feedback is sent by the UE to the eNodeB, an ACK is sent if UE
 * could successfully recieve the data transmitted by the eNodeB, else a NACK is
 * sent. This feedback is utilized by MAC for further scheduling, for instance
 * it could schedule an adaptive retransmission of the same data. 
 * @param pst 
 * @param spId
 * @param tfuHqInd pointer to TfuHqIndInfo
 * @return
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuHqInd
(
Pst * pst,
SpId spId,
TfuHqIndInfo * hqInd
)
#else
PUBLIC S16 cmPkTfuHqInd(pst, spId, hqInd)
Pst * pst;
SpId spId;
TfuHqIndInfo * hqInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTfuHqInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU049, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MEM(hqInd);
      RETVALUE(RFAILED);
   }
   if (pst->selector == TFU_SEL_LC) {
      if (cmPkTfuHqIndInfo(hqInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU050, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MEM(hqInd);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if (cmPkPtr((PTR)hqInd, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFUXXX, (ErrVal)0, "LWLC Packing failed");
#endif
         TFU_FREE_MEM(hqInd);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }

   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU051, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MEM(hqInd);
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      TFU_FREE_MEM(hqInd);
   }

   pst->event = (Event) EVTTFUHQIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkTfuHqInd
*
*
*     Desc : This Primitive carries the HARQ Feedback from PHY to scheduler
 * @details HARQ feedback is sent by the UE to the eNodeB, an ACK is sent if UE
 * could successfully recieve the data transmitted by the eNodeB, else a NACK is
 * sent. This feedback is utilized by MAC for further scheduling, for instance
 * it could schedule an adaptive retransmission of the same data. 
 * @param pst 
 * @param spId
 * @param tfuHqInd pointer to TfuHqIndInfo
 * @return
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuHqInd
(
TfuHqInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuHqInd(func, pst, mBuf)
TfuHqInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   TfuHqIndInfo *hqInd;
   
   TRC3(cmUnpkTfuHqInd)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU052, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      Mem   sMem;
      sMem.region = pst->region;
      sMem.pool = pst->pool;
      if ((cmAllocEvnt(sizeof(TfuHqIndInfo), TFU_BLKSZ, &sMem, (Ptr *)&hqInd)) != ROK)            {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU053, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }


   if (pst->selector == TFU_SEL_LC) 
   {
      if (cmUnpkTfuHqIndInfo(hqInd, (Ptr)&hqInd->memCp, mBuf) != ROK) {
         TFU_FREE_MEM(hqInd);
         TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ETFU054, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if (cmUnpkPtr((PTR *)&hqInd, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFUXXX, (ErrVal)0, "LWLC un-Packing failed");
#endif
         TFU_FREE_MEM(hqInd);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   TFU_FREE_MSG(mBuf);
   RETVALUE((*func)(pst, spId, hqInd));
}


/***********************************************************
*
*     Func : cmPkTfuSrInd
*
*
*     Desc : This Primitive carries the SR Indication from PHY to scheduler. 
 * @details Scheduling Request (SR) is sent by the UE to the eNodeB to request
 * for Uplink (UL) grant. This primitive carries a list of SRs for a number of
 * UEs received in the indicated subframe. 
 * @param pst 
 * @param spId
 * @param tfqSrInd pointer to TfuSrIndInfo
 * @return
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuSrInd
(
Pst * pst,
SpId spId,
TfuSrIndInfo * srInd
)
#else
PUBLIC S16 cmPkTfuSrInd(pst, spId, srInd)
Pst * pst;
SpId spId;
TfuSrIndInfo * srInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTfuSrInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU055, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MEM(srInd);
      RETVALUE(RFAILED);
   }
   if (pst->selector == TFU_SEL_LC) {
      if (cmPkTfuSrIndInfo(srInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU056, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MEM(srInd);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if (cmPkPtr((PTR)srInd, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFUXXX, (ErrVal)0, "LWLC Packing failed");
#endif
         TFU_FREE_MEM(srInd);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }

   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU057, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MEM(srInd);
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      TFU_FREE_MEM(srInd);
   }

   pst->event = (Event) EVTTFUSRIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkTfuSrInd
*
*
*     Desc : This Primitive carries the SR Indication from PHY to scheduler. 
 * @details Scheduling Request (SR) is sent by the UE to the eNodeB to request
 * for Uplink (UL) grant. This primitive carries a list of SRs for a number of
 * UEs received in the indicated subframe. 
 * @param pst 
 * @param spId
 * @param tfqSrInd pointer to TfuSrIndInfo
 * @return
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuSrInd
(
TfuSrInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuSrInd(func, pst, mBuf)
TfuSrInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   TfuSrIndInfo *srInd;
   
   TRC3(cmUnpkTfuSrInd)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU058, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      Mem   sMem;
      sMem.region = pst->region;
      sMem.pool = pst->pool;
      if ((cmAllocEvnt(sizeof(TfuSrIndInfo), TFU_BLKSZ, &sMem, (Ptr *)&srInd)) != ROK)            {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU059, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }


   if (pst->selector == TFU_SEL_LC) 
   {
      if (cmUnpkTfuSrIndInfo(srInd, (Ptr)&srInd->memCp, mBuf) != ROK) {
         TFU_FREE_MEM(srInd);
         TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ETFU060, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if (cmUnpkPtr((PTR *)&srInd, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFUXXX, (ErrVal)0, "LWLC un-Packing failed");
#endif
         TFU_FREE_MEM(srInd);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   TFU_FREE_MSG(mBuf);
   RETVALUE((*func)(pst, spId, srInd));
}


/***********************************************************
*
*     Func : cmPkTfuDlCqiInd
*
*
*     Desc : This API is used to indicate the reception of CQI report from PHY to
 * Scheduler, also carries the RI.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param dlCqiInd Pointer to the TfuDlCqiIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDlCqiInd
(
Pst * pst,
SuId suId,
TfuDlCqiIndInfo * dlCqiInd
)
#else
PUBLIC S16 cmPkTfuDlCqiInd(pst, suId, dlCqiInd)
Pst * pst;
SuId suId;
TfuDlCqiIndInfo * dlCqiInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTfuDlCqiInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU061, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MEM(dlCqiInd);
      RETVALUE(RFAILED);
   }
   if (pst->selector == TFU_SEL_LC) {
      if (cmPkTfuDlCqiIndInfo(dlCqiInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU062, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MEM(dlCqiInd);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if (cmPkPtr((PTR)dlCqiInd, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFUXXX, (ErrVal)0, "LWLC Packing failed");
#endif
         TFU_FREE_MEM(dlCqiInd);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }

   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU063, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MEM(dlCqiInd);
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      TFU_FREE_MEM(dlCqiInd);
   }
   pst->event = (Event) EVTTFUDLCQIIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkTfuDlCqiInd
*
*
*     Desc : This API is used to indicate the reception of CQI report from PHY to
 * Scheduler, also carries the RI.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param dlCqiInd Pointer to the TfuDlCqiIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDlCqiInd
(
TfuDlCqiInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDlCqiInd(func, pst, mBuf)
TfuDlCqiInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   TfuDlCqiIndInfo *dlCqiInd;
   
   TRC3(cmUnpkTfuDlCqiInd)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU064, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      Mem   sMem;
      sMem.region = pst->region;
      sMem.pool = pst->pool;
      if ((cmAllocEvnt(sizeof(TfuDlCqiIndInfo), TFU_BLKSZ, &sMem, (Ptr *)&dlCqiInd)) != ROK)            {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU065, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }


   if (pst->selector == TFU_SEL_LC) 
   {
      if (cmUnpkTfuDlCqiIndInfo(dlCqiInd, (Ptr)&dlCqiInd->memCp, mBuf) != ROK) {
         TFU_FREE_MEM(dlCqiInd);
         TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ETFU066, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if (cmUnpkPtr((PTR *)&dlCqiInd, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFUXXX, (ErrVal)0, "LWLC un-Packing failed");
#endif
         TFU_FREE_MEM(dlCqiInd);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   TFU_FREE_MSG(mBuf);
   RETVALUE((*func)(pst, suId, dlCqiInd));
}


#ifdef TFU_UPGRADE


/***********************************************************
*
*     Func : cmPkTfuRawCqiInd
*
*
*     Desc : This Primitive is used to convey the Raw CQI information 
 * transmitted by the UE.
 * @details Raw CQI report is the actual bits transmitted by the UE when
 * reporting CQI/PMI/RI. The interpretation of these bits to CQI/subband CQI
 * etc. shall be done by MAC.
 * 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param  cqiInd Pointer to the TfuRawCqiIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuRawCqiInd
(
Pst * pst,
SuId suId,
TfuRawCqiIndInfo * rawCqiInd
)
#else
PUBLIC S16 cmPkTfuRawCqiInd(pst, suId, rawCqiInd)
Pst * pst;
SuId suId;
TfuRawCqiIndInfo * rawCqiInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTfuRawCqiInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU067, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MEM(rawCqiInd);
      RETVALUE(RFAILED);
   }
      cmPkTfuRawCqiIndInfo(rawCqiInd, mBuf);
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU068, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MEM(rawCqiInd);
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   TFU_FREE_MEM(rawCqiInd);
   pst->event = (Event) EVTTFURAWCQIIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkTfuRawCqiInd
*
*
*     Desc : This Primitive is used to convey the Raw CQI information 
 * transmitted by the UE.
 * @details Raw CQI report is the actual bits transmitted by the UE when
 * reporting CQI/PMI/RI. The interpretation of these bits to CQI/subband CQI
 * etc. shall be done by MAC.
 * 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param  cqiInd Pointer to the TfuRawCqiIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuRawCqiInd
(
TfuRawCqiInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuRawCqiInd(func, pst, mBuf)
TfuRawCqiInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   TfuRawCqiIndInfo *rawCqiInd;
   
   TRC3(cmUnpkTfuRawCqiInd)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU069, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   {
      Mem   sMem;
      sMem.region = pst->region;
      sMem.pool = pst->pool;
      if ((cmAllocEvnt(sizeof(TfuRawCqiIndInfo), TFU_BLKSZ, &sMem, (Ptr *)&rawCqiInd)) != ROK)            {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU070, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
      cmUnpkTfuRawCqiIndInfo(rawCqiInd, (Ptr)&rawCqiInd->memCp, mBuf);
   TFU_FREE_MSG(mBuf);
   RETVALUE((*func)(pst, suId, rawCqiInd));
}


/***********************************************************
*
*     Func : cmPkTfuSrsInd
*
*
*     Desc : This Primitive is used to convey the information derived by the
 * physical layer from the SRS transmission from the UE.
 * @details This primitive carries information derived from the SRS transmission
 * from the UE. 
 * 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param  srsInd Pointer to the TfuSrIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuSrsInd
(
Pst * pst,
SuId suId,
TfuSrsIndInfo * srsInd
)
#else
PUBLIC S16 cmPkTfuSrsInd(pst, suId, srsInd)
Pst * pst;
SuId suId;
TfuSrsIndInfo * srsInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTfuSrsInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU071, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MEM(srsInd);
      RETVALUE(RFAILED);
   }
      cmPkTfuSrsIndInfo(srsInd, mBuf);
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU072, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MEM(srsInd);
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   TFU_FREE_MEM(srsInd);
   pst->event = (Event) EVTTFUSRSIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkTfuSrsInd
*
*
*     Desc : This Primitive is used to convey the information derived by the
 * physical layer from the SRS transmission from the UE.
 * @details This primitive carries information derived from the SRS transmission
 * from the UE. 
 * 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param  srsInd Pointer to the TfuSrIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuSrsInd
(
TfuSrsInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuSrsInd(func, pst, mBuf)
TfuSrsInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   TfuSrsIndInfo *srsInd;
   
   TRC3(cmUnpkTfuSrsInd)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU073, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   {
      Mem   sMem;
      sMem.region = pst->region;
      sMem.pool = pst->pool;
      if ((cmAllocEvnt(sizeof(TfuSrsIndInfo), TFU_BLKSZ, &sMem, (Ptr *)&srsInd)) != ROK)            {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU074, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
      cmUnpkTfuSrsIndInfo(srsInd, (Ptr)&srsInd->memCp, mBuf);
   TFU_FREE_MSG(mBuf);
   RETVALUE((*func)(pst, suId, srsInd));
}
#endif



/***********************************************************
*
*     Func : cmPkTfuDatInd
*
*
*     Desc : This Primitive carries the Data PDUs from PHY to MAC.
 * @details The uplink Data i.e. the data transmitted by the UEs received by the
 * physical layer at the eNodeB in the subframe (indicated by the timingInfo),
 * is relayed to MAC using this primitive. 
 * @param pst 
 * @param spId
 * @param tfuDatInd pointer to TfuDatIndInfo
 * @return
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDatInd
(
Pst * pst,
SpId spId,
TfuDatIndInfo * datInd
)
#else
PUBLIC S16 cmPkTfuDatInd(pst, spId, datInd)
Pst * pst;
SpId spId;
TfuDatIndInfo * datInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTfuDatInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU075, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MEM(datInd);
      RETVALUE(RFAILED);
   }
   if (pst->selector == TFU_SEL_LC) {
      if (cmPkTfuDatIndInfo(datInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU076, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MEM(datInd);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if(cmPkPtr((PTR)datInd, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ETFUXXX, (ErrVal)0, "LWLC Packing failed");
#endif
         TFU_FREE_MEM(datInd);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }

   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU077, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MEM(datInd);
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      TFU_FREE_MEM(datInd);
   }

   pst->event = (Event) EVTTFUDATIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkTfuDatInd
*
*
*     Desc : This Primitive carries the Data PDUs from PHY to MAC.
 * @details The uplink Data i.e. the data transmitted by the UEs received by the
 * physical layer at the eNodeB in the subframe (indicated by the timingInfo),
 * is relayed to MAC using this primitive. 
 * @param pst 
 * @param spId
 * @param tfuDatInd pointer to TfuDatIndInfo
 * @return
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDatInd
(
TfuDatInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDatInd(func, pst, mBuf)
TfuDatInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   TfuDatIndInfo *datInd;
   
   TRC3(cmUnpkTfuDatInd)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU078, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      Mem   sMem;
      sMem.region = pst->region;
      sMem.pool = pst->pool;
      if ((cmAllocEvnt(sizeof(TfuDatIndInfo), TFU_BLKSZ, &sMem, (Ptr *)&datInd)) != ROK)            {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU079, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }


   if (pst->selector == TFU_SEL_LC) 
   {
      if (cmUnpkTfuDatIndInfo(datInd, (Ptr)&datInd->memCp, mBuf) != ROK) {
         TFU_FREE_MEM(datInd);
         TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ETFU080, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if(cmUnpkPtr((PTR *)&datInd, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ETFUXXX, (ErrVal)0, "LWLC un-Packing failed");
#endif
         TFU_FREE_MEM(datInd);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   TFU_FREE_MSG(mBuf);
   RETVALUE((*func)(pst, spId, datInd));
}


/***********************************************************
*
*     Func : cmPkTfuCrcInd
*
*
*     Desc : This API is used by the Physical layer to indicate if the CRC Check
 * on the PUSCH Data was successful or not.
 * @details This primitive carries CRC indication for a list of UEs. This
 * is utilized in the scenario where MAC requested the reception of uplink data
 * for a particular UE. On reception of the PUSCH data, the CRC check on it
 * failed. This CRC failure is indicated to MAC, which would utillize this
 * information for further scheduling. 
 * Physical layer would indicate failure or success for each PUSCH transmission.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param crcInd Pointer to the TfuCrcIndInfo.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuCrcInd
(
Pst * pst,
SuId suId,
TfuCrcIndInfo * crcIndInfo
)
#else
PUBLIC S16 cmPkTfuCrcInd(pst, suId, crcIndInfo)
Pst * pst;
SuId suId;
TfuCrcIndInfo * crcIndInfo;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTfuCrcInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU081, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MEM(crcIndInfo);
      RETVALUE(RFAILED);
   }
   if (pst->selector == TFU_SEL_LC) {
      if (cmPkTfuCrcIndInfo(crcIndInfo, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU082, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MEM(crcIndInfo);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if (cmPkPtr((PTR)crcIndInfo, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFUXXX, (ErrVal)0, "LWLC Packing failed");
#endif
         TFU_FREE_MEM(crcIndInfo);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }


   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU083, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MEM(crcIndInfo);
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      TFU_FREE_MEM(crcIndInfo);
   }

   pst->event = (Event) EVTTFUCRCIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkTfuCrcInd
*
*
*     Desc : This API is used by the Physical layer to indicate if the CRC Check
 * on the PUSCH Data was successful or not.
 * @details This primitive carries CRC indication for a list of UEs. This
 * is utilized in the scenario where MAC requested the reception of uplink data
 * for a particular UE. On reception of the PUSCH data, the CRC check on it
 * failed. This CRC failure is indicated to MAC, which would utillize this
 * information for further scheduling. 
 * Physical layer would indicate failure or success for each PUSCH transmission.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param crcInd Pointer to the TfuCrcIndInfo.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuCrcInd
(
TfuCrcInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuCrcInd(func, pst, mBuf)
TfuCrcInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   TfuCrcIndInfo *crcIndInfo;
   
   TRC3(cmUnpkTfuCrcInd)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU084, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      Mem   sMem;
      sMem.region = pst->region;
      sMem.pool = pst->pool;
      if ((cmAllocEvnt(sizeof(TfuCrcIndInfo), TFU_BLKSZ, &sMem, (Ptr *)&crcIndInfo)) != ROK)            {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU085, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }


   if (pst->selector == TFU_SEL_LC) 
   {
      if (cmUnpkTfuCrcIndInfo(crcIndInfo, (Ptr)&crcIndInfo->memCp, mBuf) != ROK) {
         TFU_FREE_MEM(crcIndInfo);
         TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ETFU086, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if (cmUnpkPtr((PTR *)&crcIndInfo, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFUXXX, (ErrVal)0, "LWLC un-Packing failed");
#endif
         TFU_FREE_MEM(crcIndInfo);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   TFU_FREE_MSG(mBuf);
   RETVALUE((*func)(pst, suId, crcIndInfo));
}


/***********************************************************
*
*     Func : cmPkTfuTimingAdvInd
*
*
*     Desc : This API is used to indicate a Timing Advance from PHY to Scheduler .
 * @details This primitive carries timing advance information for a number of
 * UEs that may need timing advance. Timing advance information is an estimate
 * of the timing adjustment that a UE would need to apply in order to be
 * synchronized in uplink. This estimate is to be calculated by physical layer. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param timingAdvInd Pointer to the TfuTimingAdvIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuTimingAdvInd
(
Pst * pst,
SuId suId,
TfuTimingAdvIndInfo * timingAdvInd
)
#else
PUBLIC S16 cmPkTfuTimingAdvInd(pst, suId, timingAdvInd)
Pst * pst;
SuId suId;
TfuTimingAdvIndInfo * timingAdvInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTfuTimingAdvInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU087, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MEM(timingAdvInd);
      RETVALUE(RFAILED);
   }
   if (pst->selector == TFU_SEL_LC) {
      if (cmPkTfuTimingAdvIndInfo(timingAdvInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU088, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MEM(timingAdvInd);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if (cmPkPtr((PTR)timingAdvInd, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFUXXX, (ErrVal)0, "LWLC Packing failed");
#endif
         TFU_FREE_MEM(timingAdvInd);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }

   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU089, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MEM(timingAdvInd);
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      TFU_FREE_MEM(timingAdvInd);
   }

   pst->event = (Event) EVTTFUTIMINGADVIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkTfuTimingAdvInd
*
*
*     Desc : This API is used to indicate a Timing Advance from PHY to Scheduler .
 * @details This primitive carries timing advance information for a number of
 * UEs that may need timing advance. Timing advance information is an estimate
 * of the timing adjustment that a UE would need to apply in order to be
 * synchronized in uplink. This estimate is to be calculated by physical layer. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param timingAdvInd Pointer to the TfuTimingAdvIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuTimingAdvInd
(
TfuTimingAdvInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuTimingAdvInd(func, pst, mBuf)
TfuTimingAdvInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   TfuTimingAdvIndInfo *timingAdvInd;
   
   TRC3(cmUnpkTfuTimingAdvInd)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU090, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      Mem   sMem;
      sMem.region = pst->region;
      sMem.pool = pst->pool;
      if ((cmAllocEvnt(sizeof(TfuTimingAdvIndInfo), TFU_BLKSZ, &sMem, (Ptr *)&timingAdvInd)) != ROK)            {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU091, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }


   if (pst->selector == TFU_SEL_LC) 
   {
      if (cmUnpkTfuTimingAdvIndInfo(timingAdvInd, (Ptr)&timingAdvInd->memCp, mBuf) != ROK) {
         TFU_FREE_MEM(timingAdvInd);
         TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ETFU092, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if (cmUnpkPtr((PTR *)&timingAdvInd, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFUXXX, (ErrVal)0, "LWLC un-Packing failed");
#endif
         TFU_FREE_MEM(timingAdvInd);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   TFU_FREE_MSG(mBuf);
   RETVALUE((*func)(pst, suId, timingAdvInd));
}


/***********************************************************
*
*     Func : cmPkTfuDatReq
*
*
*     Desc : This Primitive carries the Data PDUs from MAC to PHY for
  * transmission. 
  * @details The data being sent in this primitive is meant to be transmitted on
  * the downlink channel PDSCH and PBCH (if present). To facilitate physical
  * layer processing, requisite control information is also sent along with the
  * data. 
  * @sa TfUiTfuCntrlReq
  * @param pst 
  * @param spId
  * @param tfuDatReq pointer to TfuDatReqInfo
  * @return
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDatReq
(
Pst * pst,
SpId spId,
TfuDatReqInfo * datReq
)
#else
PUBLIC S16 cmPkTfuDatReq(pst, spId, datReq)
Pst * pst;
SpId spId;
TfuDatReqInfo * datReq;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTfuDatReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU093, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MEM(datReq);
      RETVALUE(RFAILED);
   }
   if (pst->selector == TFU_SEL_LC) {
      if (cmPkTfuDatReqInfo(datReq, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU094, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MEM(datReq);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if(cmPkPtr((PTR)datReq, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFUXXX, (ErrVal)0, "LWLC Packing failed");
#endif
         TFU_FREE_MEM(datReq);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }

   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU095, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MEM(datReq);
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      TFU_FREE_MEM(datReq);
   }

   pst->event = (Event) EVTTFUDATREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkTfuDatReq
*
*
*     Desc : This Primitive carries the Data PDUs from MAC to PHY for
  * transmission. 
  * @details The data being sent in this primitive is meant to be transmitted on
  * the downlink channel PDSCH and PBCH (if present). To facilitate physical
  * layer processing, requisite control information is also sent along with the
  * data. 
  * @sa TfUiTfuCntrlReq
  * @param pst 
  * @param spId
  * @param tfuDatReq pointer to TfuDatReqInfo
  * @return
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDatReq
(
TfuDatReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDatReq(func, pst, mBuf)
TfuDatReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   TfuDatReqInfo *datReq;
   
   TRC3(cmUnpkTfuDatReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU096, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      Mem   sMem;
      sMem.region = pst->region;
      sMem.pool = pst->pool;
      if ((cmAllocEvnt(sizeof(TfuDatReqInfo), TFU_BLKSZ, &sMem, (Ptr *)&datReq)) != ROK)            {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU097, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }


   if (pst->selector == TFU_SEL_LC) 
   {
      if (cmUnpkTfuDatReqInfo(datReq, (Ptr)&datReq->memCp, mBuf) != ROK) {
         TFU_FREE_MEM(datReq);
         TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ETFU098, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == TFU_SEL_LWLC)
   {
      if(cmUnpkPtr((PTR *)&datReq, mBuf) != ROK)
      {
         TFU_FREE_MEM(datReq);
         TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ETFUXXX, (ErrVal)0, "LWLC Un-Packing failed");
#endif
         RETVALUE(RFAILED);
      }
   }
   TFU_FREE_MSG(mBuf);
   RETVALUE((*func)(pst, spId, datReq));
}


/***********************************************************
*
*     Func : cmPkTfuCntrlReq
*
*
*     Desc : This Primitive is sent from Scheduler to PHY. It provides PHY with
  * all the control information
  * @details This primitive carries the information sent on the following
  * channels - 
  * -# PDCCH
  * -# PHICH
  * -# PCFICH
  * 
  * @param pst
  * @param spId
  * @param cntrlReq pointer to TfuCntrlReqInfo
  * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuCntrlReq
(
Pst * pst,
SpId spId,
TfuCntrlReqInfo * cntrlReq
)
#else
PUBLIC S16 cmPkTfuCntrlReq(pst, spId, cntrlReq)
Pst * pst;
SpId spId;
TfuCntrlReqInfo * cntrlReq;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTfuCntrlReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU099, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MEM(cntrlReq);
      RETVALUE(RFAILED);
   }
   if (pst->selector == TFU_SEL_LC) {
      if (cmPkTfuCntrlReqInfo(cntrlReq, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU100, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MEM(cntrlReq);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if (cmPkPtr((PTR)cntrlReq, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFUXXX, (ErrVal)0, "LWLC Packing failed");
#endif
         TFU_FREE_MEM(cntrlReq);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }


   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU101, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MEM(cntrlReq);
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      TFU_FREE_MEM(cntrlReq);
   }

   pst->event = (Event) EVTTFUCNTRLREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkTfuCntrlReq
*
*
*     Desc : This Primitive is sent from Scheduler to PHY. It provides PHY with
  * all the control information
  * @details This primitive carries the information sent on the following
  * channels - 
  * -# PDCCH
  * -# PHICH
  * -# PCFICH
  * 
  * @param pst
  * @param spId
  * @param cntrlReq pointer to TfuCntrlReqInfo
  * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuCntrlReq
(
TfuCntrlReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuCntrlReq(func, pst, mBuf)
TfuCntrlReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   TfuCntrlReqInfo *cntrlReq;
   
   TRC3(cmUnpkTfuCntrlReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU102, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      Mem   sMem;
      sMem.region = pst->region;
      sMem.pool = pst->pool;
      if ((cmAllocEvnt(sizeof(TfuCntrlReqInfo), TFU_BLKSZ, &sMem, (Ptr *)&cntrlReq)) != ROK)            {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU103, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }


   if (pst->selector == TFU_SEL_LC) 
   {
      if (cmUnpkTfuCntrlReqInfo(cntrlReq, (Ptr)&cntrlReq->memCp, mBuf) != ROK) {
         TFU_FREE_MEM(cntrlReq);
         TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ETFU104, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if (cmUnpkPtr((PTR *)&cntrlReq, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFUXXX, (ErrVal)0, "LWLC un-Packing failed");
#endif
         TFU_FREE_MEM(cntrlReq);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   TFU_FREE_MSG(mBuf);
   RETVALUE((*func)(pst, spId, cntrlReq));
}



/***********************************************************
*
*     Func : cmPkTfuTtiInd
*
*
*     Desc : This API is the TTI indication from PHY to MAC . 
 * @details This primitive provides the timing information (SFN and subframe)
 * which is currently running on the physical layer. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param ttiInd Pointer to the TfuTtiIndInfo.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuTtiInd
(
Pst * pst,
SuId suId,
TfuTtiIndInfo * ttiInd
)
#else
PUBLIC S16 cmPkTfuTtiInd(pst, suId, ttiInd)
Pst * pst;
SuId suId;
TfuTtiIndInfo * ttiInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTfuTtiInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU105, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)ttiInd, sizeof(TfuTtiIndInfo));
      RETVALUE(RFAILED);
   }
   if (pst->selector == TFU_SEL_LC) {
      if (cmPkTfuTtiIndInfo(ttiInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU106, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)ttiInd, sizeof(TfuTtiIndInfo));
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if (cmPkPtr((PTR)ttiInd, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFUXXX, (ErrVal)0, "LWLC Packing failed");
#endif
         
         /*MS_FIX:71858:Changed to SPutSBuf as being allocated with SGetSBuf*/
         SPutSBuf(pst->region, pst->pool, (Data *)ttiInd, sizeof(TfuTtiIndInfo));
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }

   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU107, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)ttiInd, sizeof(TfuTtiIndInfo));
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      if (SPutSBuf(pst->region, pst->pool, (Data *)ttiInd, sizeof(TfuTtiIndInfo)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU108, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }

   pst->event = (Event) EVTTFUTTIIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkTfuTtiInd
*
*
*     Desc : This API is the TTI indication from PHY to MAC . 
 * @details This primitive provides the timing information (SFN and subframe)
 * which is currently running on the physical layer. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param ttiInd Pointer to the TfuTtiIndInfo.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuTtiInd
(
TfuTtiInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuTtiInd(func, pst, mBuf)
TfuTtiInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   TfuTtiIndInfo *ttiInd;
   
   TRC3(cmUnpkTfuTtiInd)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU109, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      if ((SGetSBuf(pst->region, pst->pool, (Data **)&ttiInd,             sizeof(TfuTtiIndInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU110, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }

   if (pst->selector == TFU_SEL_LC) 
   {
      if (cmUnpkTfuTtiIndInfo(ttiInd, mBuf) != ROK) {
         SPutSBuf(pst->region, pst->pool, (Data *)ttiInd, sizeof(TfuTtiIndInfo));
         TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ETFU111, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if (cmUnpkPtr((PTR *)&ttiInd, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFUXXX, (ErrVal)0, "LWLC un-Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)ttiInd, sizeof(TfuTtiIndInfo));
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   TFU_FREE_MSG(mBuf);
   /* [ccpu00141698]-MOD- MAC/SCH does not free the TTI ind anymore */
   (*func)(pst, suId, ttiInd);
   SPutSBuf(pst->region, pst->pool, (Data *)ttiInd, sizeof(TfuTtiIndInfo));

   RETVALUE((*func)(pst, suId, ttiInd));
}

#if defined(TENB_T2K3K_SPECIFIC_CHANGES) && defined(LTE_TDD)
/***********************************************************
 *
 *     Func : cmPkTfuNonRtInd
 *
 *
 *     Desc : This API is the Non-Rt indication from CL to MAC . 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @return ROK/RFAILED
 *
 *
 *     Ret  : S16
 *
 *     Notes:
 *
 *     File  : 
 *
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuNonRtInd
(
Pst * pst,
SuId suId
)
#else
PUBLIC S16 cmPkTfuNonRtInd(pst, suId)
Pst * pst;
SuId suId;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTfuNonRtInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU105, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
  }
  if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU107, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
  }
  pst->event = (Event) EVTTFUNONRTIND;
  RETVALUE(SPstTsk(pst,mBuf));
}

/***********************************************************
*
*     Func : cmUnpkTfuNonRtInd
*
*
*     Desc : This API is the Non Rt indication from PHY to MAC . 
* @param pst Pointer to the post structure.
* @param suId SAP ID of the service user.
* @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuNonRtInd
(
TfuNonRtInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuNonRtInd(func, pst, mBuf)
TfuNonRtInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   TRC3(cmUnpkTfuNonRtInd)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU109, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   TFU_FREE_MSG(mBuf);
   RETVALUE((*func)(pst, suId));
}

#endif

/***********************************************************
*
*     Func : cmPkTfuSchTtiInd
*
*
*     Desc : This API is the TTI indication from PHY to scheduler. 
 * @details This primitive provides the timing information (SFN and subframe)
 * which is currently running on the physical layer. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param ttiInd Pointer to the TfuTtiIndInfo.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuSchTtiInd
(
Pst * pst,
SuId suId,
TfuTtiIndInfo * ttiInd
)
#else
PUBLIC S16 cmPkTfuSchTtiInd(pst, suId, ttiInd)
Pst * pst;
SuId suId;
TfuTtiIndInfo * ttiInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTfuSchTtiInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU112, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)ttiInd, sizeof(TfuTtiIndInfo));
      RETVALUE(RFAILED);
   }
   if (pst->selector == TFU_SEL_LC) {
      if (cmPkTfuTtiIndInfo(ttiInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU113, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)ttiInd, sizeof(TfuTtiIndInfo));
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if (cmPkPtr((PTR)ttiInd, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFUXXX, (ErrVal)0, "LWLC Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)ttiInd, sizeof(TfuTtiIndInfo));
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }

   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU114, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)ttiInd, sizeof(TfuTtiIndInfo));
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      if (SPutSBuf(pst->region, pst->pool, (Data *)ttiInd, sizeof(TfuTtiIndInfo)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU115, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   pst->event = (Event) EVTTFUSCHTTIIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkTfuSchTtiInd
*
*
*     Desc : This API is the TTI indication from PHY to scheduler. 
 * @details This primitive provides the timing information (SFN and subframe)
 * which is currently running on the physical layer. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param ttiInd Pointer to the TfuTtiIndInfo.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuSchTtiInd
(
TfuSchTtiInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuSchTtiInd(func, pst, mBuf)
TfuSchTtiInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   TfuTtiIndInfo *ttiInd;
   
   TRC3(cmUnpkTfuSchTtiInd)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU116, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      if ((SGetSBuf(pst->region, pst->pool, (Data **)&ttiInd,             sizeof(TfuTtiIndInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU117, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }

   if (pst->selector == TFU_SEL_LC) 
   {
      if (cmUnpkTfuTtiIndInfo(ttiInd, mBuf) != ROK) {
         SPutSBuf(pst->region, pst->pool, (Data *)ttiInd, sizeof(TfuTtiIndInfo));
         TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ETFU118, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if (cmUnpkPtr((PTR *)&ttiInd, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFUXXX, (ErrVal)0, "LWLC un-Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)ttiInd, sizeof(TfuTtiIndInfo));
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   TFU_FREE_MSG(mBuf);
   /* [ccpu00141698]-MOD- MAC/SCH does not free the TTI ind anymore */
   (*func)(pst, suId, ttiInd);
   SPutSBuf(pst->region, pst->pool, (Data *)ttiInd, sizeof(TfuTtiIndInfo));
 
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkTfuPucchDeltaPwr
*
*
*     Desc : This Primitive is used to convey PUCCH Delta power calculated by the
 * Physical layer.
 * This information is utilized by Scheduler for power control. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param  Pointer to the TfuPucchDeltaPwrIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuPucchDeltaPwr
(
Pst * pst,
SuId suId,
TfuPucchDeltaPwrIndInfo * pucchDeltaPwr
)
#else
PUBLIC S16 cmPkTfuPucchDeltaPwr(pst, suId, pucchDeltaPwr)
Pst * pst;
SuId suId;
TfuPucchDeltaPwrIndInfo * pucchDeltaPwr;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTfuPucchDeltaPwr)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU119, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)pucchDeltaPwr, sizeof(TfuPucchDeltaPwrIndInfo));
      RETVALUE(RFAILED);
   }
   if (pst->selector == TFU_SEL_LC) {
      if (cmPkTfuPucchDeltaPwrIndInfo(pucchDeltaPwr, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU120, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MEM(pucchDeltaPwr);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if (cmPkPtr((PTR)pucchDeltaPwr, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFUXXX, (ErrVal)0, "LWLC Packing failed");
#endif
         TFU_FREE_MEM(pucchDeltaPwr);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }

   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU121, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MEM(pucchDeltaPwr);
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      TFU_FREE_MEM(pucchDeltaPwr);
   }
   pst->event = (Event) EVTTFUPUCCHDELPWR;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkTfuPucchDeltaPwr
*
*
*     Desc : This Primitive is used to convey PUCCH Delta power calculated by the
 * Physical layer.
 * This information is utilized by Scheduler for power control. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param  Pointer to the TfuPucchDeltaPwrIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuPucchDeltaPwr
(
TfuPucchDeltaPwrInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuPucchDeltaPwr(func, pst, mBuf)
TfuPucchDeltaPwrInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   TfuPucchDeltaPwrIndInfo *pucchDeltaPwr;
   
   TRC3(cmUnpkTfuPucchDeltaPwr)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU122, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      Mem   sMem;
      sMem.region = pst->region;
      sMem.pool = pst->pool;
      if ((cmAllocEvnt(sizeof(TfuPucchDeltaPwrIndInfo), TFU_BLKSZ, &sMem, (Ptr *)&pucchDeltaPwr)) != ROK)            {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU123, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }

   if (pst->selector == TFU_SEL_LC) 
   {
      if (cmUnpkTfuPucchDeltaPwrIndInfo(pucchDeltaPwr, (Ptr)&pucchDeltaPwr->memCp, mBuf) != ROK) {
         TFU_FREE_MEM(pucchDeltaPwr);
         TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ETFU124, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if (cmUnpkPtr((PTR *)&pucchDeltaPwr, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFUXXX, (ErrVal)0, "LWLC un-Packing failed");
#endif
         TFU_FREE_MEM(pucchDeltaPwr);
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   TFU_FREE_MSG(mBuf);
   RETVALUE((*func)(pst, suId, pucchDeltaPwr));
}


/***********************************************************
*
*     Func : cmPkTfuDciFormat0Info
*
*
*     Desc : This structure contains the information needed to convey DCI format 0.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDciFormat0Info
(
TfuDciFormat0Info *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDciFormat0Info(param, mBuf)
TfuDciFormat0Info *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuDciFormat0Info)

   /* tfu_c_001.main_3: Adding pack for hqProcId */
   CMCHKPK(SPkU8, param->hqProcId, mBuf);
   CMCHKPK(SPkU8, param->txAntenna, mBuf);
   CMCHKPK(SPkU8, param->numCqiBit, mBuf);
   CMCHKPK(SPkU8, param->cqiReq, mBuf);
   CMCHKPK(SPkU8, param->nDmrs, mBuf);

#ifdef TFU_TDD
   CMCHKPK(SPkU8, param->dai, mBuf);
   CMCHKPK(SPkU8, param->ulIdx, mBuf);

#endif
   CMCHKPK(SPkU8, param->tpcCmd, mBuf);
   CMCHKPK(SPkU8, param->ndi, mBuf);
   CMCHKPK(SPkU8, param->mcs, mBuf);
   CMCHKPK(SPkU8, param->hoppingBits, mBuf);
/* tfu_c_001.main_7. Added changes of TFU_UPGRADE */
#ifdef TFU_UPGRADE
   CMCHKPK(SPkU32, param->riv, mBuf);
#endif
   CMCHKPK(SPkU8, param->numRb, mBuf);
   CMCHKPK(SPkU8, param->rbStart, mBuf);
   CMCHKPK(SPkU8, param->hoppingEnbld, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDciFormat0Info
*
*
*     Desc : This structure contains the information needed to convey DCI format 0.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDciFormat0Info
(
TfuDciFormat0Info *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDciFormat0Info(param, mBuf)
TfuDciFormat0Info *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuDciFormat0Info)

   CMCHKUNPK(SUnpkU8, &param->hoppingEnbld, mBuf);
   CMCHKUNPK(SUnpkU8, &param->rbStart, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numRb, mBuf);
#ifdef TFU_UPGRADE
   CMCHKUNPK(SUnpkU32, &param->riv, mBuf);
#endif /* TFU_UPGRADE */
   CMCHKUNPK(SUnpkU8, &param->hoppingBits, mBuf);
   CMCHKUNPK(SUnpkU8, &param->mcs, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ndi, mBuf);
   CMCHKUNPK(SUnpkU8, &param->tpcCmd, mBuf);

#ifdef TFU_TDD
   CMCHKUNPK(SUnpkU8, &param->ulIdx, mBuf);
   CMCHKUNPK(SUnpkU8, &param->dai, mBuf);

#endif
   CMCHKUNPK(SUnpkU8, &param->nDmrs, mBuf);
   CMCHKUNPK(SUnpkU8, &param->cqiReq, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numCqiBit, mBuf);
   CMCHKUNPK(SUnpkU8, &param->txAntenna, mBuf);
   /* tfu_c_001.main_3: Adding unpack for hqProcId */
   CMCHKUNPK(SUnpkU8, &param->hqProcId, mBuf);

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuAllocMapOrRiv
*
*
*     Desc : This Structure could either contain a resource allocation bit map OR a
 * RIV Value as defined in 213 - 7.1.6.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuAllocMapOrRiv
(
TfuAllocMapOrRiv *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuAllocMapOrRiv(param, mBuf)
TfuAllocMapOrRiv *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkTfuAllocMapOrRiv)

      switch(param->type) {
      /*tfu_c_001.main_7 - ADD - TFU_RESMAP_CHANGE support */
#ifdef TFU_RESMAP_CHANGE
         case UnKnown:
            CMCHKPK(cmPkTfuAllocMap, &param->u.allocMap, mBuf);
            break;
   
#endif
   
      /*tfu_c_001.main_7 - ADD - TFU_RESMAP_CHANGE support */
#ifndef TFU_RESMAP_CHANGE
         case TFU_ALLOC_TYPE_MAP:
            for (i=TFU_MAX_ALLOC_BYTES-1; i >= 0; i--) {
               CMCHKPK(SPkU8, param->u.resAllocMap[i], mBuf);
            }
            break;
   
#endif
         case TFU_ALLOC_TYPE_RIV:
            CMCHKPK(SPkU32, param->u.riv, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(SPkU32, param->type, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuAllocMapOrRiv
*
*
*     Desc : This Structure could either contain a resource allocation bit map OR a
 * RIV Value as defined in 213 - 7.1.6.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuAllocMapOrRiv
(
TfuAllocMapOrRiv *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuAllocMapOrRiv(param, mBuf)
TfuAllocMapOrRiv *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkTfuAllocMapOrRiv)

   CMCHKUNPK(SUnpkU32, (U32 *)&param->type, mBuf);
      switch(param->type) {
         case TFU_ALLOC_TYPE_RIV:
            CMCHKUNPK(SUnpkU32, &param->u.riv, mBuf);
            break;
   
      /*tfu_c_001.main_7 - ADD - TFU_RESMAP_CHANGE support */
#ifndef TFU_RESMAP_CHANGE
         case TFU_ALLOC_TYPE_MAP:
            for (i=0; i<TFU_MAX_ALLOC_BYTES; i++) {
               CMCHKUNPK(SUnpkU8, &param->u.resAllocMap[i], mBuf);
            }
            break;
   
#endif
   
      /*tfu_c_001.main_7 - ADD - TFU_RESMAP_CHANGE support */
#ifdef TFU_RESMAP_CHANGE
         case UnKnown:
            CMCHKUNPK(cmUnpkTfuAllocMap, &param->u.allocMap, mBuf);
            break;
   
#endif
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuDciFormat1AllocInfo
*
*
*     Desc : This structure contains only the allocation information, thats part
 * of DCI format 1. 
 * @details Allocation information also contains parameters necessary
 * for Physical layer to process Downlink Data. This structure accompanies the
 * Data that is sent from MAC to PHY in the TfUiTfuDatReq primitive.
 * @sa TfuDciFormat1Info
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDciFormat1AllocInfo
(
TfuDciFormat1AllocInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDciFormat1AllocInfo(param, mBuf)
TfuDciFormat1AllocInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkTfuDciFormat1AllocInfo)

   CMCHKPK(SPkU8, param->rv, mBuf);
   CMCHKPK(SPkU8, param->mcs, mBuf);
   CMCHKPK(SPkU8, param->ndi, mBuf);
   CMCHKPK(SPkU8, param->harqProcId, mBuf);
   for (i=TFU_MAX_ALLOC_BYTES-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->resAllocMap[i], mBuf);
   }
   CMCHKPK(SPkU8, param->isAllocType0, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDciFormat1AllocInfo
*
*
*     Desc : This structure contains only the allocation information, thats part
 * of DCI format 1. 
 * @details Allocation information also contains parameters necessary
 * for Physical layer to process Downlink Data. This structure accompanies the
 * Data that is sent from MAC to PHY in the TfUiTfuDatReq primitive.
 * @sa TfuDciFormat1Info
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDciFormat1AllocInfo
(
TfuDciFormat1AllocInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDciFormat1AllocInfo(param, mBuf)
TfuDciFormat1AllocInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkTfuDciFormat1AllocInfo)

   CMCHKUNPK(SUnpkU8, &param->isAllocType0, mBuf);
   for (i=0; i<TFU_MAX_ALLOC_BYTES; i++) {
      CMCHKUNPK(SUnpkU8, &param->resAllocMap[i], mBuf);
   }
   CMCHKUNPK(SUnpkU8, &param->harqProcId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ndi, mBuf);
   CMCHKUNPK(SUnpkU8, &param->mcs, mBuf);
   CMCHKUNPK(SUnpkU8, &param->rv, mBuf);
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkTfuDciFormat1Info
*
*
*     Desc : This structure contains the information needed to convey DCI format 1.
 * @details Allocation information is separated from the other control
 * information carried in this format. This separation is needed as Data shall
 * also carry some control information, essentially allocation information,
 * along with it, in order to aid physical layer processing of the data.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDciFormat1Info
(
TfuDciFormat1Info *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDciFormat1Info(param, mBuf)
TfuDciFormat1Info *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuDciFormat1Info)

   CMCHKPK(SPkU8, param->tpcCmd, mBuf);

#ifdef TFU_TDD
   CMCHKPK(SPkU8, param->dai, mBuf);

#endif
   CMCHKPK(cmPkTfuDciFormat1AllocInfo, &param->allocInfo, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDciFormat1Info
*
*
*     Desc : This structure contains the information needed to convey DCI format 1.
 * @details Allocation information is separated from the other control
 * information carried in this format. This separation is needed as Data shall
 * also carry some control information, essentially allocation information,
 * along with it, in order to aid physical layer processing of the data.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDciFormat1Info
(
TfuDciFormat1Info *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDciFormat1Info(param, mBuf)
TfuDciFormat1Info *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuDciFormat1Info)

   CMCHKUNPK(cmUnpkTfuDciFormat1AllocInfo, &param->allocInfo, mBuf);

#ifdef TFU_TDD
   CMCHKUNPK(SUnpkU8, &param->dai, mBuf);

#endif
   CMCHKUNPK(SUnpkU8, &param->tpcCmd, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuDciFormat2AAllocInfo
*
*
*     Desc : This structure contains only the allocation information, that is part
  * of DCI format 2A. 
  * @details Allocation information also contains parameters necessary
  * for Physical layer to process Downlink data. This structure accompanies the
  * Data that is sent from MAC to PHY in the TfUiTfuDatReq primitive.
  * @sa TfuDciFormat2AInfo
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDciFormat2AAllocInfo
(
TfuDciFormat2AAllocInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDciFormat2AAllocInfo(param, mBuf)
TfuDciFormat2AAllocInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkTfuDciFormat2AAllocInfo)

   CMCHKPK(SPkU8, param->transSwap, mBuf);
   CMCHKPK(SPkU8, param->precoding, mBuf);

   for (i=1; i >= 0; i--) {
      CMCHKPK(cmPkTfuDciFormatTbInfo, &param->tbInfo[i], mBuf);
   }

   CMCHKPK(SPkU8, param->harqProcId, mBuf);
   for (i=TFU_MAX_ALLOC_BYTES-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->resAllocMap[i], mBuf);
   }

   CMCHKPK(SPkU8, param->isAllocType0, mBuf);

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDciFormat2AAllocInfo
*
*
*     Desc : This structure contains only the allocation information, that is part
  * of DCI format 2A. 
  * @details Allocation information also contains parameters necessary
  * for Physical layer to process Downlink data. This structure accompanies the
  * Data that is sent from MAC to PHY in the TfUiTfuDatReq primitive.
  * @sa TfuDciFormat2AInfo
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDciFormat2AAllocInfo
(
TfuDciFormat2AAllocInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDciFormat2AAllocInfo(param, mBuf)
TfuDciFormat2AAllocInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkTfuDciFormat2AAllocInfo)


/* tfu_c_001.main_4 - Changes for MIMO feature addition */
/* tfu_c_001.main_5 - Removed dependency on MIMO compile-time flag */
   CMCHKUNPK(SUnpkU8, &param->isAllocType0, mBuf);


/* tfu_c_001.main_4 - Changes for MIMO feature addition */
/* tfu_c_001.main_5 - Removed dependency on MIMO compile-time flag */
   for (i=0; i<TFU_MAX_ALLOC_BYTES; i++) {
      CMCHKUNPK(SUnpkU8, &param->resAllocMap[i], mBuf);
   }
   CMCHKUNPK(SUnpkU8, &param->harqProcId, mBuf);

/* tfu_c_001.main_4 - Changes for MIMO feature addition */
/* tfu_c_001.main_5 - Removed dependency on MIMO compile-time flag */

/* tfu_c_001.main_4 - Changes for MIMO feature addition */
/* tfu_c_001.main_5 - Removed dependency on MIMO compile-time flag */
   for (i=0; i<=1; i++) {
      CMCHKUNPK(cmUnpkTfuDciFormatTbInfo, &param->tbInfo[i], mBuf);
   }

   CMCHKUNPK(SUnpkU8, &param->precoding, mBuf);
   CMCHKUNPK(SUnpkU8, &param->transSwap, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuDciFormat2AInfo
*
*
*     Desc : This structure contains the information carried by DCI format 2A. 
 * @details It carries the allocation information and other control information.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDciFormat2AInfo
(
TfuDciFormat2AInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDciFormat2AInfo(param, mBuf)
TfuDciFormat2AInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuDciFormat2AInfo)

   CMCHKPK(SPkU8, param->tpcCmd, mBuf);

#ifdef TFU_TDD
   CMCHKPK(SPkU8, param->dai, mBuf);

#endif
   CMCHKPK(cmPkTfuDciFormat2AAllocInfo, &param->allocInfo, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDciFormat2AInfo
*
*
*     Desc : This structure contains the information carried by DCI format 2A. 
 * @details It carries the allocation information and other control information.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDciFormat2AInfo
(
TfuDciFormat2AInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDciFormat2AInfo(param, mBuf)
TfuDciFormat2AInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuDciFormat2AInfo)

   CMCHKUNPK(cmUnpkTfuDciFormat2AAllocInfo, &param->allocInfo, mBuf);

#ifdef TFU_TDD
   CMCHKUNPK(SUnpkU8, &param->dai, mBuf);

#endif
   CMCHKUNPK(SUnpkU8, &param->tpcCmd, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuDciFormat2AllocInfo
*
*
*     Desc : This structure contains only the allocation information, that is part
  * of DCI format 2. 
  * @details Allocation information also contains parameters necessary
  * for Physical layer to process Downlink data. This structure accompanies the
  * Data that is sent from MAC to PHY in the TfUiTfuDatReq primitive.
  * @sa TfuDciFormat2Info
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDciFormat2AllocInfo
(
TfuDciFormat2AllocInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDciFormat2AllocInfo(param, mBuf)
TfuDciFormat2AllocInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkTfuDciFormat2AllocInfo)


/* tfu_c_001.main_4 - Changes for MIMO feature addition */
/* tfu_c_001.main_5 - Removed dependency on MIMO compile-time flag */
   for (i=1; i >= 0; i--) {
      CMCHKPK(cmPkTfuDciFormatTbInfo, &param->tbInfo[i], mBuf);
   }
   CMCHKPK(SPkU8, param->harqProcId, mBuf);

   CMCHKPK(SPkU8, param->precoding, mBuf);
   CMCHKPK(SPkU8, param->transSwap, mBuf);

/* tfu_c_001.main_4 - Changes for MIMO feature addition */
/* tfu_c_001.main_5 - Removed dependency on MIMO compile-time flag */

#ifdef TFU_TDD
   CMCHKPK(SPkU8, param->dai, mBuf);

#endif
   for (i=TFU_MAX_ALLOC_BYTES-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->resAllocMap[i], mBuf);
   }

/* tfu_c_001.main_4 - Changes for MIMO feature addition */
/* tfu_c_001.main_5 - Removed dependency on MIMO compile-time flag */

/* tfu_c_001.main_4 - Changes for MIMO feature addition */
/* tfu_c_001.main_5 - Removed dependency on MIMO compile-time flag */
   CMCHKPK(SPkU8, param->isAllocType0, mBuf);

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDciFormat2AllocInfo
*
*
*     Desc : This structure contains only the allocation information, that is part
  * of DCI format 2. 
  * @details Allocation information also contains parameters necessary
  * for Physical layer to process Downlink data. This structure accompanies the
  * Data that is sent from MAC to PHY in the TfUiTfuDatReq primitive.
  * @sa TfuDciFormat2Info
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDciFormat2AllocInfo
(
TfuDciFormat2AllocInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDciFormat2AllocInfo(param, mBuf)
TfuDciFormat2AllocInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkTfuDciFormat2AllocInfo)


/* tfu_c_001.main_4 - Changes for MIMO feature addition */
/* tfu_c_001.main_5 - Removed dependency on MIMO compile-time flag */
   CMCHKUNPK(SUnpkU8, &param->isAllocType0, mBuf);


/* tfu_c_001.main_4 - Changes for MIMO feature addition */
/* tfu_c_001.main_5 - Removed dependency on MIMO compile-time flag */
   for (i=0; i<TFU_MAX_ALLOC_BYTES; i++) {
      CMCHKUNPK(SUnpkU8, &param->resAllocMap[i], mBuf);
   }

#ifdef TFU_TDD
   CMCHKUNPK(SUnpkU8, &param->dai, mBuf);

#endif

/* tfu_c_001.main_4 - Changes for MIMO feature addition */
/* tfu_c_001.main_5 - Removed dependency on MIMO compile-time flag */
   CMCHKUNPK(SUnpkU8, &param->transSwap, mBuf);
   CMCHKUNPK(SUnpkU8, &param->precoding, mBuf);

/* tfu_c_001.main_4 - Changes for MIMO feature addition */
/* tfu_c_001.main_5 - Removed dependency on MIMO compile-time flag */
   CMCHKUNPK(SUnpkU8, &param->harqProcId, mBuf);
   for (i=0; i<=1; i++) {
      CMCHKUNPK(cmUnpkTfuDciFormatTbInfo, &param->tbInfo[i], mBuf);
   }

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuDciFormat2Info
*
*
*     Desc : This structure contains the information carried by DCI format 2.
 * @details Allocation information is separated from the other control
 * information carried in this format. This separation is needed as Data must
 * also carry some control information, essentially, allocation information
 * along with it, in order to aid physical layer processing of the data.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDciFormat2Info
(
TfuDciFormat2Info *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDciFormat2Info(param, mBuf)
TfuDciFormat2Info *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuDciFormat2Info)


/* tfu_c_001.main_4 - Changes for MIMO feature addition */
/* tfu_c_001.main_5 - Removed dependency on MIMO compile-time flag */

#ifdef TFU_TDD
   CMCHKPK(SPkU8, param->dai, mBuf);

#endif

   CMCHKPK(SPkU8, param->tpcCmd, mBuf);

/* tfu_c_001.main_4 - Changes for MIMO feature addition */
/* tfu_c_001.main_5 - Removed dependency on MIMO compile-time flag */
   CMCHKPK(cmPkTfuDciFormat2AllocInfo, &param->allocInfo, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDciFormat2Info
*
*
*     Desc : This structure contains the information carried by DCI format 2.
 * @details Allocation information is separated from the other control
 * information carried in this format. This separation is needed as Data must
 * also carry some control information, essentially, allocation information
 * along with it, in order to aid physical layer processing of the data.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDciFormat2Info
(
TfuDciFormat2Info *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDciFormat2Info(param, mBuf)
TfuDciFormat2Info *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuDciFormat2Info)

   CMCHKUNPK(cmUnpkTfuDciFormat2AllocInfo, &param->allocInfo, mBuf);

/* tfu_c_001.main_4 - Changes for MIMO feature addition */
/* tfu_c_001.main_5 - Removed dependency on MIMO compile-time flag */
   CMCHKUNPK(SUnpkU8, &param->tpcCmd, mBuf);

/* tfu_c_001.main_4 - Changes for MIMO feature addition */
/* tfu_c_001.main_5 - Removed dependency on MIMO compile-time flag */

#ifdef TFU_TDD
   CMCHKUNPK(SUnpkU8, &param->dai, mBuf);

#endif

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuDciFormat3Info
*
*
*     Desc : This structure contains the information carried in DCI format 3.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDciFormat3Info
(
TfuDciFormat3Info *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDciFormat3Info(param, mBuf)
TfuDciFormat3Info *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkTfuDciFormat3Info)

   CMCHKPK(SPkU8, param->isPucch, mBuf);
   for (i=TFU_MAX_2BIT_TPC-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->tpcCmd[i], mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDciFormat3Info
*
*
*     Desc : This structure contains the information carried in DCI format 3.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDciFormat3Info
(
TfuDciFormat3Info *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDciFormat3Info(param, mBuf)
TfuDciFormat3Info *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkTfuDciFormat3Info)

   for (i=0; i<TFU_MAX_2BIT_TPC; i++) {
      CMCHKUNPK(SUnpkU8, &param->tpcCmd[i], mBuf);
   }
   CMCHKUNPK(SUnpkU8, &param->isPucch, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuDciFormat3AInfo
*
*
*     Desc : This structure contains the information carried by DCI format 3A.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDciFormat3AInfo
(
TfuDciFormat3AInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDciFormat3AInfo(param, mBuf)
TfuDciFormat3AInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkTfuDciFormat3AInfo)
   CMCHKPK(SPkU8, param->isPucch, mBuf);
   for (i=TFU_MAX_2BIT_TPC-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->tpcCmd[i], mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDciFormat3AInfo
*
*
*     Desc : This structure contains the information carried by DCI format 3A.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDciFormat3AInfo
(
TfuDciFormat3AInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDciFormat3AInfo(param, mBuf)
TfuDciFormat3AInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkTfuDciFormat3AInfo)

   for (i=0; i<TFU_MAX_2BIT_TPC; i++) {
      CMCHKUNPK(SUnpkU8, &param->tpcCmd[i], mBuf);
   }
   CMCHKUNPK(SUnpkU8, &param->isPucch, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuDciFormat1dAllocInfo
*
*
*     Desc : This structure contains only the allocation information, thats part
  * of DCI format 1D. 
  * @details Allocation information also contains parameters necessary
  * for Physical layer to process Downlink Data. This structure accompanies the
  * Data that is sent from MAC to PHY in the TfUiTfuDatReq primitive.
  * @sa TfuDciFormat1dInfo
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDciFormat1dAllocInfo
(
TfuDciFormat1dAllocInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDciFormat1dAllocInfo(param, mBuf)
TfuDciFormat1dAllocInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuDciFormat1dAllocInfo)

   CMCHKPK(SPkU8, param->tPmi, mBuf);
   CMCHKPK(SPkU8, param->rv, mBuf);
   CMCHKPK(SPkU8, param->mcs, mBuf);
   CMCHKPK(cmPkTfuAllocMapOrRiv, &param->alloc, mBuf);
   CMCHKPK(cmPkTknU8, &param->nGap2, mBuf);
   CMCHKPK(SPkU8, param->isLocal, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDciFormat1dAllocInfo
*
*
*     Desc : This structure contains only the allocation information, thats part
  * of DCI format 1D. 
  * @details Allocation information also contains parameters necessary
  * for Physical layer to process Downlink Data. This structure accompanies the
  * Data that is sent from MAC to PHY in the TfUiTfuDatReq primitive.
  * @sa TfuDciFormat1dInfo
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDciFormat1dAllocInfo
(
TfuDciFormat1dAllocInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDciFormat1dAllocInfo(param, mBuf)
TfuDciFormat1dAllocInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuDciFormat1dAllocInfo)

   CMCHKUNPK(SUnpkU8, &param->isLocal, mBuf);
   CMCHKUNPK(cmUnpkTknU8, &param->nGap2, mBuf);
   CMCHKUNPK(cmUnpkTfuAllocMapOrRiv, &param->alloc, mBuf);
   CMCHKUNPK(SUnpkU8, &param->mcs, mBuf);
   CMCHKUNPK(SUnpkU8, &param->rv, mBuf);
   CMCHKUNPK(SUnpkU8, &param->tPmi, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuDciFormat1dInfo
*
*
*     Desc : This structure contains the information carried by DCI format 1D.
 * @details Allocation information is separated from the other control
 * information carried in this format. This separation is needed as Data shall
 * also carry some control information, essentially allocation information,
 * along with it, in order to aid physical layer processing of the data.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDciFormat1dInfo
(
TfuDciFormat1dInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDciFormat1dInfo(param, mBuf)
TfuDciFormat1dInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuDciFormat1dInfo)

   CMCHKPK(SPkU8, param->dlPwrOffset, mBuf);

#ifdef TFU_TDD
   CMCHKPK(SPkU8, param->dai, mBuf);

#endif
   CMCHKPK(SPkU8, param->tpcCmd, mBuf);
   CMCHKPK(SPkU8, param->ndi, mBuf);
   CMCHKPK(SPkU8, param->harqProcId, mBuf);
   CMCHKPK(cmPkTfuDciFormat1dAllocInfo, &param->allocInfo, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDciFormat1dInfo
*
*
*     Desc : This structure contains the information carried by DCI format 1D.
 * @details Allocation information is separated from the other control
 * information carried in this format. This separation is needed as Data shall
 * also carry some control information, essentially allocation information,
 * along with it, in order to aid physical layer processing of the data.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDciFormat1dInfo
(
TfuDciFormat1dInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDciFormat1dInfo(param, mBuf)
TfuDciFormat1dInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuDciFormat1dInfo)

   CMCHKUNPK(cmUnpkTfuDciFormat1dAllocInfo, &param->allocInfo, mBuf);
   CMCHKUNPK(SUnpkU8, &param->harqProcId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ndi, mBuf);
   CMCHKUNPK(SUnpkU8, &param->tpcCmd, mBuf);

#ifdef TFU_TDD
   CMCHKUNPK(SUnpkU8, &param->dai, mBuf);

#endif
   CMCHKUNPK(SUnpkU8, &param->dlPwrOffset, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuDciFormat1cInfo
*
*
*     Desc : This structure contains only the allocation information, thats part
  * of DCI format 1C. 
  * @details Allocation information also contains parameters necessary
  * for Physical layer to process Downlink Data. This structure accompanies the
  * Data that is sent from MAC to PHY in the TfUiTfuDatReq primitive.
  * @sa TfuDciFormat1CInfo
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDciFormat1cInfo
(
TfuDciFormat1cInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDciFormat1cInfo(param, mBuf)
TfuDciFormat1cInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuDciFormat1cInfo)

   CMCHKPK(SPkU8, param->iTbs, mBuf);
   CMCHKPK(cmPkTfuAllocMapOrRiv, &param->alloc, mBuf);
   CMCHKPK(cmPkTknU8, &param->nGap2, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDciFormat1cInfo
*
*
*     Desc : This structure contains only the allocation information, thats part
  * of DCI format 1C. 
  * @details Allocation information also contains parameters necessary
  * for Physical layer to process Downlink Data. This structure accompanies the
  * Data that is sent from MAC to PHY in the TfUiTfuDatReq primitive.
  * @sa TfuDciFormat1CInfo
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDciFormat1cInfo
(
TfuDciFormat1cInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDciFormat1cInfo(param, mBuf)
TfuDciFormat1cInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuDciFormat1cInfo)

   CMCHKUNPK(cmUnpkTknU8, &param->nGap2, mBuf);
   CMCHKUNPK(cmUnpkTfuAllocMapOrRiv, &param->alloc, mBuf);
   CMCHKUNPK(SUnpkU8, &param->iTbs, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuDciFormat1bAllocInfo
*
*
*     Desc : This structure contains only the allocation information, thats part
  * of DCI format 1 B. 
  * @details Allocation information also contains parameters necessary
  * for Physical layer to process Downlink Data. This structure accompanies the
  * Data that is sent from MAC to PHY in the TfUiTfuDatReq primitive.
  * @sa TfuDciFormat1BInfo
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDciFormat1bAllocInfo
(
TfuDciFormat1bAllocInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDciFormat1bAllocInfo(param, mBuf)
TfuDciFormat1bAllocInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuDciFormat1bAllocInfo)

   CMCHKPK(SPkU8, param->pmiCfm, mBuf);
   CMCHKPK(SPkU8, param->tPmi, mBuf);
   CMCHKPK(SPkU8, param->ndi, mBuf);
   CMCHKPK(SPkU8, param->harqProcId, mBuf);
   CMCHKPK(SPkU8, param->rv, mBuf);
   CMCHKPK(SPkU8, param->mcs, mBuf);
   CMCHKPK(cmPkTfuAllocMapOrRiv, &param->alloc, mBuf);
   CMCHKPK(cmPkTknU8, &param->nGap2, mBuf);
   CMCHKPK(SPkU8, param->isLocal, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDciFormat1bAllocInfo
*
*
*     Desc : This structure contains only the allocation information, thats part
  * of DCI format 1 B. 
  * @details Allocation information also contains parameters necessary
  * for Physical layer to process Downlink Data. This structure accompanies the
  * Data that is sent from MAC to PHY in the TfUiTfuDatReq primitive.
  * @sa TfuDciFormat1BInfo
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDciFormat1bAllocInfo
(
TfuDciFormat1bAllocInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDciFormat1bAllocInfo(param, mBuf)
TfuDciFormat1bAllocInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuDciFormat1bAllocInfo)

   CMCHKUNPK(SUnpkU8, &param->isLocal, mBuf);
   CMCHKUNPK(cmUnpkTknU8, &param->nGap2, mBuf);
   CMCHKUNPK(cmUnpkTfuAllocMapOrRiv, &param->alloc, mBuf);
   CMCHKUNPK(SUnpkU8, &param->mcs, mBuf);
   CMCHKUNPK(SUnpkU8, &param->rv, mBuf);
   CMCHKUNPK(SUnpkU8, &param->harqProcId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ndi, mBuf);
   CMCHKUNPK(SUnpkU8, &param->tPmi, mBuf);
   CMCHKUNPK(SUnpkU8, &param->pmiCfm, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuPdcchOrderInfo
*
*
*     Desc : This structure contains the information that is carried in DCI
  * format 1A in the case of a PDCCH order.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuPdcchOrderInfo
(
TfuPdcchOrderInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuPdcchOrderInfo(param, mBuf)
TfuPdcchOrderInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuPdcchOrderInfo)

   CMCHKPK(SPkU8, param->prachMaskIdx, mBuf);
   CMCHKPK(SPkU8, param->preambleIdx, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuPdcchOrderInfo
*
*
*     Desc : This structure contains the information that is carried in DCI
  * format 1A in the case of a PDCCH order.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuPdcchOrderInfo
(
TfuPdcchOrderInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuPdcchOrderInfo(param, mBuf)
TfuPdcchOrderInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuPdcchOrderInfo)

   CMCHKUNPK(SUnpkU8, &param->preambleIdx, mBuf);
   CMCHKUNPK(SUnpkU8, &param->prachMaskIdx, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuDciFormat1aAllocInfo
*
*
*     Desc : This structure contains only the allocation information, thats part
  * of DCI format 1A. 
  * @details Allocation information also contains parameters necessary
  * for Physical layer to process Downlink Data. This structure accompanies the
  * Data that is sent from MAC to PHY in the TfUiTfuDatReq primitive.
  * @sa TfuDciFormat1AInfo
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDciFormat1aAllocInfo
(
TfuDciFormat1aAllocInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDciFormat1aAllocInfo(param, mBuf)
TfuDciFormat1aAllocInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuDciFormat1aAllocInfo)

   CMCHKPK(SPkU8, param->ndi, mBuf);
   CMCHKPK(cmPkTknU8, &param->harqProcId, mBuf);
   CMCHKPK(SPkU8, param->rv, mBuf);
   CMCHKPK(SPkU8, param->mcs, mBuf);
   CMCHKPK(cmPkTfuAllocMapOrRiv, &param->alloc, mBuf);
   CMCHKPK(cmPkTknU8, &param->nGap2, mBuf);
   CMCHKPK(SPkU8, param->isLocal, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDciFormat1aAllocInfo
*
*
*     Desc : This structure contains only the allocation information, thats part
  * of DCI format 1A. 
  * @details Allocation information also contains parameters necessary
  * for Physical layer to process Downlink Data. This structure accompanies the
  * Data that is sent from MAC to PHY in the TfUiTfuDatReq primitive.
  * @sa TfuDciFormat1AInfo
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDciFormat1aAllocInfo
(
TfuDciFormat1aAllocInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDciFormat1aAllocInfo(param, mBuf)
TfuDciFormat1aAllocInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuDciFormat1aAllocInfo)

   CMCHKUNPK(SUnpkU8, &param->isLocal, mBuf);
   CMCHKUNPK(cmUnpkTknU8, &param->nGap2, mBuf);
   CMCHKUNPK(cmUnpkTfuAllocMapOrRiv, &param->alloc, mBuf);
   CMCHKUNPK(SUnpkU8, &param->mcs, mBuf);
   CMCHKUNPK(SUnpkU8, &param->rv, mBuf);
   CMCHKUNPK(cmUnpkTknU8, &param->harqProcId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ndi, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfudciformat1aPdsch
*
*
*     Desc : This structure contains the information carried in DCI format 1A
  * when it is NOT used for a PDCCH order.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfudciformat1aPdsch
(
Tfudciformat1aPdsch *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfudciformat1aPdsch(param, mBuf)
Tfudciformat1aPdsch *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfudciformat1aPdsch)

   CMCHKPK(SPkU8, param->tpcCmd, mBuf);

#ifdef TFU_TDD
   CMCHKPK(cmPkTknU8, &param->dai, mBuf);

#endif
   CMCHKPK(cmPkTfuDciFormat1aAllocInfo, &param->allocInfo, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfudciformat1aPdsch
*
*
*     Desc : This structure contains the information carried in DCI format 1A
  * when it is NOT used for a PDCCH order.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfudciformat1aPdsch
(
Tfudciformat1aPdsch *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfudciformat1aPdsch(param, mBuf)
Tfudciformat1aPdsch *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfudciformat1aPdsch)

   CMCHKUNPK(cmUnpkTfuDciFormat1aAllocInfo, &param->allocInfo, mBuf);

#ifdef TFU_TDD
   CMCHKUNPK(cmUnpkTknU8, &param->dai, mBuf);

#endif
   CMCHKUNPK(SUnpkU8, &param->tpcCmd, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuDciFormat1aInfo
*
*
*     Desc : This structure contains the information needed to convey DCI format 1A.
 * @details Format can possibly carry PDSCH allocation or information needed for
 * a PDCCH order, used to initiate a RACH procedure in cases where UE looses
 * sync with eNodeB.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDciFormat1aInfo
(
TfuDciFormat1aInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDciFormat1aInfo(param, mBuf)
TfuDciFormat1aInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuDciFormat1aInfo)

   switch(param->isPdcchOrder) {
      case FALSE:
         CMCHKPK(cmPkTfudciformat1aPdsch, &param->t.pdschInfo, mBuf);
         break;
      case TRUE:
         CMCHKPK(cmPkTfuPdcchOrderInfo, &param->t.pdcchOrder, mBuf);
         break;
      default :
         RETVALUE(RFAILED);
      }
   CMCHKPK(SPkU8, param->isPdcchOrder, mBuf);

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDciFormat1aInfo
*
*
*     Desc : This structure contains the information needed to convey DCI format 1A.
 * @details Format can possibly carry PDSCH allocation or information needed for
 * a PDCCH order, used to initiate a RACH procedure in cases where UE looses
 * sync with eNodeB.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDciFormat1aInfo
(
TfuDciFormat1aInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDciFormat1aInfo(param, mBuf)
TfuDciFormat1aInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuDciFormat1aInfo)

   CMCHKUNPK(SUnpkU8, &param->isPdcchOrder, mBuf);
   switch(param->isPdcchOrder) {
      case TRUE:
         CMCHKUNPK(cmUnpkTfuPdcchOrderInfo, &param->t.pdcchOrder, mBuf);
         break;
      case FALSE:
         CMCHKUNPK(cmUnpkTfudciformat1aPdsch, &param->t.pdschInfo, mBuf);
         break;
      default :
         RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuDciFormat1bInfo
*
*
*     Desc : This structure contains the information needed to convey DCI format 1A.
 * @details Allocation information is separated from the other control
 * information carried in this format. This separation is needed as Data shall
 * also carry some control information, essentially allocation information,
 * along with it, in order to aid physical layer processing of the data.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDciFormat1bInfo
(
TfuDciFormat1bInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDciFormat1bInfo(param, mBuf)
TfuDciFormat1bInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuDciFormat1bInfo)

   CMCHKPK(SPkU8, param->tpcCmd, mBuf);

#ifdef TFU_TDD
   CMCHKPK(SPkU8, param->dai, mBuf);

#endif
   CMCHKPK(cmPkTfuDciFormat1bAllocInfo, &param->allocInfo, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDciFormat1bInfo
*
*
*     Desc : This structure contains the information needed to convey DCI format 1A.
 * @details Allocation information is separated from the other control
 * information carried in this format. This separation is needed as Data shall
 * also carry some control information, essentially allocation information,
 * along with it, in order to aid physical layer processing of the data.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDciFormat1bInfo
(
TfuDciFormat1bInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDciFormat1bInfo(param, mBuf)
TfuDciFormat1bInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuDciFormat1bInfo)

   CMCHKUNPK(cmUnpkTfuDciFormat1bAllocInfo, &param->allocInfo, mBuf);

#ifdef TFU_TDD
   CMCHKUNPK(SUnpkU8, &param->dai, mBuf);

#endif
   CMCHKUNPK(SUnpkU8, &param->tpcCmd, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuDciInfo
*
*
*     Desc : This structure contains the information needed to convey the possible DCI
 * formats. The following are the supported formats - 
 * -# Format 0    - used for PUSCH scheduling
 * -# Format 1    - used for PDSCH scheduling
 * -# Format 1A   - used for compact scheduling of PDSCH or RA procedure
 *                   intitiated by a PDCCH order.
 * -# Format 1B   - used for compact scheduling of PDSCH with precoding
 *                   information.
 * -# Format 1C   - used for very compact scheduling of PDSCH.
 * -# Format 1D   - used for compact scheduling for PDSCH with precoding
 *                   information with power offset.
 * -# Format 2    - used for PDSCH Scheduling
 * -# Format 2A   - used for PDSCH Scheduling
 * -# Format 3    - used for power control 
 * -# Format 3A   - used for power control
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDciInfo
(
TfuDciInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDciInfo(param, mBuf)
TfuDciInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuDciInfo)

      switch(param->dciFormat) {
         case TFU_DCI_FORMAT_3A:
            CMCHKPK(cmPkTfuDciFormat3AInfo, &param->u.format3AInfo, mBuf);
            break;
         case TFU_DCI_FORMAT_3:
            CMCHKPK(cmPkTfuDciFormat3Info, &param->u.format3Info, mBuf);
            break;
         case TFU_DCI_FORMAT_2A:
            CMCHKPK(cmPkTfuDciFormat2AInfo, &param->u.format2AInfo, mBuf);
            break;
         case TFU_DCI_FORMAT_2:
            CMCHKPK(cmPkTfuDciFormat2Info, &param->u.format2Info, mBuf);
            break;
         case TFU_DCI_FORMAT_1D:
            CMCHKPK(cmPkTfuDciFormat1dInfo, &param->u.format1dInfo, mBuf);
            break;
         case TFU_DCI_FORMAT_1C:
            CMCHKPK(cmPkTfuDciFormat1cInfo, &param->u.format1cInfo, mBuf);
            break;
         case TFU_DCI_FORMAT_1B:
            CMCHKPK(cmPkTfuDciFormat1bInfo, &param->u.format1bInfo, mBuf);
            break;
         case TFU_DCI_FORMAT_1A:
            CMCHKPK(cmPkTfuDciFormat1aInfo, &param->u.format1aInfo, mBuf);
            break;
         case TFU_DCI_FORMAT_1:
            CMCHKPK(cmPkTfuDciFormat1Info, &param->u.format1Info, mBuf);
            break;
         case TFU_DCI_FORMAT_0:
            CMCHKPK(cmPkTfuDciFormat0Info, &param->u.format0Info, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(SPkU32, param->dciFormat, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDciInfo
*
*
*     Desc : This structure contains the information needed to convey the possible DCI
 * formats. The following are the supported formats - 
 * -# Format 0    - used for PUSCH scheduling
 * -# Format 1    - used for PDSCH scheduling
 * -# Format 1A   - used for compact scheduling of PDSCH or RA procedure
 *                   intitiated by a PDCCH order.
 * -# Format 1B   - used for compact scheduling of PDSCH with precoding
 *                   information.
 * -# Format 1C   - used for very compact scheduling of PDSCH.
 * -# Format 1D   - used for compact scheduling for PDSCH with precoding
 *                   information with power offset.
 * -# Format 2    - used for PDSCH Scheduling
 * -# Format 2A   - used for PDSCH Scheduling
 * -# Format 3    - used for power control 
 * -# Format 3A   - used for power control
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDciInfo
(
TfuDciInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDciInfo(param, mBuf)
TfuDciInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuDciInfo)

   CMCHKUNPK(SUnpkU32, (U32 *)&param->dciFormat, mBuf);
      switch(param->dciFormat) {
         case TFU_DCI_FORMAT_0:
            CMCHKUNPK(cmUnpkTfuDciFormat0Info, &param->u.format0Info, mBuf);
            break;
         case TFU_DCI_FORMAT_1:
            CMCHKUNPK(cmUnpkTfuDciFormat1Info, &param->u.format1Info, mBuf);
            break;
         case TFU_DCI_FORMAT_1A:
            CMCHKUNPK(cmUnpkTfuDciFormat1aInfo, &param->u.format1aInfo, mBuf);
            break;
         case TFU_DCI_FORMAT_1B:
            CMCHKUNPK(cmUnpkTfuDciFormat1bInfo, &param->u.format1bInfo, mBuf);
            break;
         case TFU_DCI_FORMAT_1C:
            CMCHKUNPK(cmUnpkTfuDciFormat1cInfo, &param->u.format1cInfo, mBuf);
            break;
         case TFU_DCI_FORMAT_1D:
            CMCHKUNPK(cmUnpkTfuDciFormat1dInfo, &param->u.format1dInfo, mBuf);
            break;
         case TFU_DCI_FORMAT_2:
            CMCHKUNPK(cmUnpkTfuDciFormat2Info, &param->u.format2Info, mBuf);
            break;
         case TFU_DCI_FORMAT_2A:
            CMCHKUNPK(cmUnpkTfuDciFormat2AInfo, &param->u.format2AInfo, mBuf);
            break;
         case TFU_DCI_FORMAT_3:
            CMCHKUNPK(cmUnpkTfuDciFormat3Info, &param->u.format3Info, mBuf);
            break;
         case TFU_DCI_FORMAT_3A:
            CMCHKUNPK(cmUnpkTfuDciFormat3AInfo, &param->u.format3AInfo, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuSubbandInfo
*
*
*     Desc : This structure contains the information needed to convey the start and size
 * of the subband in the CQI report.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuSubbandInfo
(
TfuSubbandInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuSubbandInfo(param, mBuf)
TfuSubbandInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuSubbandInfo)

   CMCHKPK(SPkU8, param->numRb, mBuf);
   CMCHKPK(SPkU8, param->rbStart, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuSubbandInfo
*
*
*     Desc : This structure contains the information needed to convey the start and size
 * of the subband in the CQI report.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuSubbandInfo
(
TfuSubbandInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuSubbandInfo(param, mBuf)
TfuSubbandInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuSubbandInfo)

   CMCHKUNPK(SUnpkU8, &param->rbStart, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numRb, mBuf);
   RETVALUE(ROK);
}




/***********************************************************
*
*     Func : cmPkTfuSubbandCqiInfo
*
*
*     Desc : This structure is used to convey the subbannd CQI reported.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuSubbandCqiInfo
(
TfuSubbandCqiInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuSubbandCqiInfo(param, mBuf)
TfuSubbandCqiInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuSubbandCqiInfo)

   CMCHKPK(SPkU8, param->cqiIdx, mBuf);
   CMCHKPK(cmPkTfuSubbandInfo, &param->subband, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuSubbandCqiInfo
*
*
*     Desc : This structure is used to convey the subbannd CQI reported.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuSubbandCqiInfo
(
TfuSubbandCqiInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuSubbandCqiInfo(param, mBuf)
TfuSubbandCqiInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuSubbandCqiInfo)

   CMCHKUNPK(cmUnpkTfuSubbandInfo, &param->subband, mBuf);
   CMCHKUNPK(SUnpkU8, &param->cqiIdx, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuPdcchCceInfo
*
*
*     Desc : This structure conveys the CCE information.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuPdcchCceInfo
(
TfuPdcchCceInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuPdcchCceInfo(param, mBuf)
TfuPdcchCceInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuPdcchCceInfo)

   CMCHKPK(cmPkLteAggrLvl, param->aggrLvl, mBuf);
   CMCHKPK(SPkU8, param->cceIdx, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuPdcchCceInfo
*
*
*     Desc : This structure conveys the CCE information.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuPdcchCceInfo
(
TfuPdcchCceInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuPdcchCceInfo(param, mBuf)
TfuPdcchCceInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuPdcchCceInfo)

   CMCHKUNPK(SUnpkU8, &param->cceIdx, mBuf);
   CMCHKUNPK(cmUnpkLteAggrLvl,(U32 *)&param->aggrLvl, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuCqiPucchMode10
*
*
*     Desc : This structure maps to the CQI mode 10. The report could either
  * convey a Rank index or a wideband CQI.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuCqiPucchMode10
(
TfuCqiPucchMode10 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuCqiPucchMode10(param, mBuf)
TfuCqiPucchMode10 *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuCqiPucchMode10)

      switch(param->type) {
         case TFU_RPT_CQI:
            CMCHKPK(SPkU8, param->u.cqi, mBuf);
            break;
         case TFU_RPT_RI:
            CMCHKPK(SPkU8, param->u.ri, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(SPkU32, param->type, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuCqiPucchMode10
*
*
*     Desc : This structure maps to the CQI mode 10. The report could either
  * convey a Rank index or a wideband CQI.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuCqiPucchMode10
(
TfuCqiPucchMode10 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuCqiPucchMode10(param, mBuf)
TfuCqiPucchMode10 *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuCqiPucchMode10)

   CMCHKUNPK(SUnpkU32, (U32 *)&param->type, mBuf);
      switch(param->type) {
         case TFU_RPT_RI:
            CMCHKUNPK(SUnpkU8, &param->u.ri, mBuf);
            break;
         case TFU_RPT_CQI:
            CMCHKUNPK(SUnpkU8, &param->u.cqi, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuCqiMode11Cqi
*
*
*     Desc : This structure contains a wideband CQI, PMI and optionally a
  * wideband differential CQI.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuCqiMode11Cqi
(
TfuCqiMode11Cqi *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuCqiMode11Cqi(param, mBuf)
TfuCqiMode11Cqi *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuCqiMode11Cqi)

   CMCHKPK(cmPkTknU8, &param->wideDiffCqi, mBuf);
   CMCHKPK(SPkU8, param->pmi, mBuf);
   CMCHKPK(SPkU8, param->cqi, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuCqiMode11Cqi
*
*
*     Desc : This structure contains a wideband CQI, PMI and optionally a
  * wideband differential CQI.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuCqiMode11Cqi
(
TfuCqiMode11Cqi *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuCqiMode11Cqi(param, mBuf)
TfuCqiMode11Cqi *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuCqiMode11Cqi)

   CMCHKUNPK(SUnpkU8, &param->cqi, mBuf);
   CMCHKUNPK(SUnpkU8, &param->pmi, mBuf);
   CMCHKUNPK(cmUnpkTknU8, &param->wideDiffCqi, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuCqiPucchMode11
*
*
*     Desc : This structure maps to the CQI mode 11. The report could either
  * convey a Rank index or a CQI report.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuCqiPucchMode11
(
TfuCqiPucchMode11 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuCqiPucchMode11(param, mBuf)
TfuCqiPucchMode11 *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuCqiPucchMode11)

      switch(param->type) {
         case TFU_RPT_CQI:
            CMCHKPK(cmPkTfuCqiMode11Cqi, &param->u.cqi, mBuf);
            break;
         case TFU_RPT_RI:
            CMCHKPK(SPkU8, param->u.ri, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(SPkU32, param->type, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuCqiPucchMode11
*
*
*     Desc : This structure maps to the CQI mode 11. The report could either
  * convey a Rank index or a CQI report.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuCqiPucchMode11
(
TfuCqiPucchMode11 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuCqiPucchMode11(param, mBuf)
TfuCqiPucchMode11 *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuCqiPucchMode11)

   CMCHKUNPK(SUnpkU32, (U32 *)&param->type, mBuf);
      switch(param->type) {
         case TFU_RPT_RI:
            CMCHKUNPK(SUnpkU8, &param->u.ri, mBuf);
            break;
         case TFU_RPT_CQI:
            CMCHKUNPK(cmUnpkTfuCqiMode11Cqi, &param->u.cqi, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuCqiMode20SubCqi
*
*
*     Desc : This structure contains the SubBand CQI for mode 2-0.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuCqiMode20SubCqi
(
TfuCqiMode20SubCqi *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuCqiMode20SubCqi(param, mBuf)
TfuCqiMode20SubCqi *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuCqiMode20SubCqi)

   CMCHKPK(SPkU8, param->l, mBuf);
   CMCHKPK(SPkU8, param->cqi, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuCqiMode20SubCqi
*
*
*     Desc : This structure contains the SubBand CQI for mode 2-0.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuCqiMode20SubCqi
(
TfuCqiMode20SubCqi *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuCqiMode20SubCqi(param, mBuf)
TfuCqiMode20SubCqi *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuCqiMode20SubCqi)

   CMCHKUNPK(SUnpkU8, &param->cqi, mBuf);
   CMCHKUNPK(SUnpkU8, &param->l, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuCqiMode20Cqi
*
*
*     Desc : This structure contains Mode20 CQI report. It could either be a
  * wideband CQI or a sub-band CQI.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuCqiMode20Cqi
(
TfuCqiMode20Cqi *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuCqiMode20Cqi(param, mBuf)
TfuCqiMode20Cqi *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuCqiMode20Cqi)

      switch(param->isWideband) {
         case FALSE:
            CMCHKPK(cmPkTfuCqiMode20SubCqi, &param->u.subCqi, mBuf);
            break;
         case TRUE:
            CMCHKPK(SPkU8, param->u.wideCqi, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(SPkU8, param->isWideband, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuCqiMode20Cqi
*
*
*     Desc : This structure contains Mode20 CQI report. It could either be a
  * wideband CQI or a sub-band CQI.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuCqiMode20Cqi
(
TfuCqiMode20Cqi *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuCqiMode20Cqi(param, mBuf)
TfuCqiMode20Cqi *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuCqiMode20Cqi)

   CMCHKUNPK(SUnpkU8, &param->isWideband, mBuf);
      switch(param->isWideband) {
         case TRUE:
            CMCHKUNPK(SUnpkU8, &param->u.wideCqi, mBuf);
            break;
         case FALSE:
            CMCHKUNPK(cmUnpkTfuCqiMode20SubCqi, &param->u.subCqi, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuCqiPucchMode20
*
*
*     Desc : This structure maps to CQI mode 20. The report either contains a
  * Rank Index or a CQI report.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuCqiPucchMode20
(
TfuCqiPucchMode20 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuCqiPucchMode20(param, mBuf)
TfuCqiPucchMode20 *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuCqiPucchMode20)

      switch(param->type) {
         case TFU_RPT_CQI:
            CMCHKPK(cmPkTfuCqiMode20Cqi, &param->u.cqi, mBuf);
            break;
         case TFU_RPT_RI:
            CMCHKPK(SPkU8, param->u.ri, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(SPkU32, param->type, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuCqiPucchMode20
*
*
*     Desc : This structure maps to CQI mode 20. The report either contains a
  * Rank Index or a CQI report.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuCqiPucchMode20
(
TfuCqiPucchMode20 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuCqiPucchMode20(param, mBuf)
TfuCqiPucchMode20 *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuCqiPucchMode20)

   CMCHKUNPK(SUnpkU32, (U32 *)&param->type, mBuf);
      switch(param->type) {
         case TFU_RPT_RI:
            CMCHKUNPK(SUnpkU8, &param->u.ri, mBuf);
            break;
         case TFU_RPT_CQI:
            CMCHKUNPK(cmUnpkTfuCqiMode20Cqi, &param->u.cqi, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuCqiMode21SubCqi
*
*
*     Desc : This structure contains the sub-band CQI report for mode 2-1. 
  * It carries a CQI, 'L' bit sub-band label, and optionally a differential CQI.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuCqiMode21SubCqi
(
TfuCqiMode21SubCqi *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuCqiMode21SubCqi(param, mBuf)
TfuCqiMode21SubCqi *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuCqiMode21SubCqi)

   CMCHKPK(cmPkTknU8, &param->diffCqi, mBuf);
   CMCHKPK(SPkU8, param->l, mBuf);
   CMCHKPK(SPkU8, param->cqi, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuCqiMode21SubCqi
*
*
*     Desc : This structure contains the sub-band CQI report for mode 2-1. 
  * It carries a CQI, 'L' bit sub-band label, and optionally a differential CQI.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuCqiMode21SubCqi
(
TfuCqiMode21SubCqi *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuCqiMode21SubCqi(param, mBuf)
TfuCqiMode21SubCqi *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuCqiMode21SubCqi)

   CMCHKUNPK(SUnpkU8, &param->cqi, mBuf);
   CMCHKUNPK(SUnpkU8, &param->l, mBuf);
   CMCHKUNPK(cmUnpkTknU8, &param->diffCqi, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuCqiMode21WideCqi
*
*
*     Desc : This structure contains the wideband CQI report for mode 2-1.
  * It carries a wideband CQI, PMI and optionally a differential CQI.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuCqiMode21WideCqi
(
TfuCqiMode21WideCqi *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuCqiMode21WideCqi(param, mBuf)
TfuCqiMode21WideCqi *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuCqiMode21WideCqi)

   CMCHKPK(cmPkTknU8, &param->diffCqi, mBuf);
   CMCHKPK(SPkU8, param->pmi, mBuf);
   CMCHKPK(SPkU8, param->cqi, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuCqiMode21WideCqi
*
*
*     Desc : This structure contains the wideband CQI report for mode 2-1.
  * It carries a wideband CQI, PMI and optionally a differential CQI.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuCqiMode21WideCqi
(
TfuCqiMode21WideCqi *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuCqiMode21WideCqi(param, mBuf)
TfuCqiMode21WideCqi *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuCqiMode21WideCqi)

   CMCHKUNPK(SUnpkU8, &param->cqi, mBuf);
   CMCHKUNPK(SUnpkU8, &param->pmi, mBuf);
   CMCHKUNPK(cmUnpkTknU8, &param->diffCqi, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuCqiMode21Cqi
*
*
*     Desc : This structure conveys CQI report for mode 2-1. The reported value
  * could either be wideband or sub-band.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuCqiMode21Cqi
(
TfuCqiMode21Cqi *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuCqiMode21Cqi(param, mBuf)
TfuCqiMode21Cqi *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuCqiMode21Cqi)

      switch(param->isWideband) {
         case FALSE:
            CMCHKPK(cmPkTfuCqiMode21SubCqi, &param->u.subCqi, mBuf);
            break;
         case TRUE:
            CMCHKPK(cmPkTfuCqiMode21WideCqi, &param->u.wideCqi, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(SPkU8, param->isWideband, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuCqiMode21Cqi
*
*
*     Desc : This structure conveys CQI report for mode 2-1. The reported value
  * could either be wideband or sub-band.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuCqiMode21Cqi
(
TfuCqiMode21Cqi *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuCqiMode21Cqi(param, mBuf)
TfuCqiMode21Cqi *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuCqiMode21Cqi)

   CMCHKUNPK(SUnpkU8, &param->isWideband, mBuf);
      switch(param->isWideband) {
         case TRUE:
            CMCHKUNPK(cmUnpkTfuCqiMode21WideCqi, &param->u.wideCqi, mBuf);
            break;
         case FALSE:
            CMCHKUNPK(cmUnpkTfuCqiMode21SubCqi, &param->u.subCqi, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuCqiPucchMode21
*
*
*     Desc : This structure maps to the CQI reporting mode 2-1. The report either
  * conveys a Rank Indicator or a CQI report.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuCqiPucchMode21
(
TfuCqiPucchMode21 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuCqiPucchMode21(param, mBuf)
TfuCqiPucchMode21 *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuCqiPucchMode21)

      switch(param->type) {
         case TFU_RPT_CQI:
            CMCHKPK(cmPkTfuCqiMode21Cqi, &param->u.cqi, mBuf);
            break;
         case TFU_RPT_RI:
            CMCHKPK(SPkU8, param->u.ri, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(SPkU32, param->type, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuCqiPucchMode21
*
*
*     Desc : This structure maps to the CQI reporting mode 2-1. The report either
  * conveys a Rank Indicator or a CQI report.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuCqiPucchMode21
(
TfuCqiPucchMode21 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuCqiPucchMode21(param, mBuf)
TfuCqiPucchMode21 *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuCqiPucchMode21)

   CMCHKUNPK(SUnpkU32, (U32 *)&param->type, mBuf);
      switch(param->type) {
         case TFU_RPT_RI:
            CMCHKUNPK(SUnpkU8, &param->u.ri, mBuf);
            break;
         case TFU_RPT_CQI:
            CMCHKUNPK(cmUnpkTfuCqiMode21Cqi, &param->u.cqi, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuDlCqiPucch
*
*
*     Desc : This structure conveys the Downlink CQI reported on PUCCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDlCqiPucch
(
TfuDlCqiPucch *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDlCqiPucch(param, mBuf)
TfuDlCqiPucch *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuDlCqiPucch)

      switch(param->mode) {
         case TFU_PUCCH_CQI_MODE21:
            CMCHKPK(cmPkTfuCqiPucchMode21, &param->u.mode21Info, mBuf);
            break;
         case TFU_PUCCH_CQI_MODE20:
            CMCHKPK(cmPkTfuCqiPucchMode20, &param->u.mode20Info, mBuf);
            break;
         case TFU_PUCCH_CQI_MODE11:
            CMCHKPK(cmPkTfuCqiPucchMode11, &param->u.mode11Info, mBuf);
            break;
         case TFU_PUCCH_CQI_MODE10:
            CMCHKPK(cmPkTfuCqiPucchMode10, &param->u.mode10Info, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(SPkU32, param->mode, mBuf);
   CMCHKPK(SPkU8, param->cellIdx, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDlCqiPucch
*
*
*     Desc : This structure conveys the Downlink CQI reported on PUCCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDlCqiPucch
(
TfuDlCqiPucch *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDlCqiPucch(param, mBuf)
TfuDlCqiPucch *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuDlCqiPucch)

   CMCHKUNPK(SUnpkU8, &param->cellIdx, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&param->mode, mBuf);
      switch(param->mode) {
         case TFU_PUCCH_CQI_MODE10:
            CMCHKUNPK(cmUnpkTfuCqiPucchMode10, &param->u.mode10Info, mBuf);
            break;
         case TFU_PUCCH_CQI_MODE11:
            CMCHKUNPK(cmUnpkTfuCqiPucchMode11, &param->u.mode11Info, mBuf);
            break;
         case TFU_PUCCH_CQI_MODE20:
            CMCHKUNPK(cmUnpkTfuCqiPucchMode20, &param->u.mode20Info, mBuf);
            break;
         case TFU_PUCCH_CQI_MODE21:
            CMCHKUNPK(cmUnpkTfuCqiPucchMode21, &param->u.mode21Info, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuSubbandMode12
*
*
*     Desc : This structure carries subband information and PMI, in the CQI
  * reporting format 1-2.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuSubbandMode12
(
TfuSubbandMode12 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuSubbandMode12(param, mBuf)
TfuSubbandMode12 *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuSubbandMode12)

   CMCHKPK(cmPkTfuSubbandInfo, &param->subBand, mBuf);
   CMCHKPK(SPkU8, param->pmi, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuSubbandMode12
*
*
*     Desc : This structure carries subband information and PMI, in the CQI
  * reporting format 1-2.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuSubbandMode12
(
TfuSubbandMode12 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuSubbandMode12(param, mBuf)
TfuSubbandMode12 *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuSubbandMode12)

   CMCHKUNPK(SUnpkU8, &param->pmi, mBuf);
   CMCHKUNPK(cmUnpkTfuSubbandInfo, &param->subBand, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuCqiPuschMode12
*
*
*     Desc : This structure conveys information present in CQI reporting mode 1-2 received
 * over PUSCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuCqiPuschMode12
(
TfuCqiPuschMode12 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuCqiPuschMode12(param, mBuf)
TfuCqiPuschMode12 *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkTfuCqiPuschMode12)

   for (i=TFU_MAX_DL_SUBBAND-1; i >= 0; i--) {
      CMCHKPK(cmPkTfuSubbandMode12, &param->subbandArr[i], mBuf);
   }
   for (i=TFU_MAX_TB-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->cqiIdx[i], mBuf);
   }
   CMCHKPK(SPkU8, param->numSubband, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuCqiPuschMode12
*
*
*     Desc : This structure conveys information present in CQI reporting mode 1-2 received
 * over PUSCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuCqiPuschMode12
(
TfuCqiPuschMode12 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuCqiPuschMode12(param, mBuf)
TfuCqiPuschMode12 *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkTfuCqiPuschMode12)

   CMCHKUNPK(SUnpkU8, &param->numSubband, mBuf);
   for (i=0; i<TFU_MAX_TB; i++) {
      CMCHKUNPK(SUnpkU8, &param->cqiIdx[i], mBuf);
   }
   for (i=0; i<TFU_MAX_DL_SUBBAND; i++) {
      CMCHKUNPK(cmUnpkTfuSubbandMode12, &param->subbandArr[i], mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuCqiPuschMode20
*
*
*     Desc : This structure conveys information present in CQI reporting mode 2-0 received
 * over PUSCH. This mode is for UE selected sub-band feedback.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuCqiPuschMode20
(
TfuCqiPuschMode20 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuCqiPuschMode20(param, mBuf)
TfuCqiPuschMode20 *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkTfuCqiPuschMode20)

   for (i=TFU_MAX_DL_SUBBAND-1; i >= 0; i--) {
      CMCHKPK(cmPkTfuSubbandInfo, &param->subbandArr[i], mBuf);
   }
   CMCHKPK(SPkU8, param->numSubband, mBuf);
   CMCHKPK(SPkU8, param->wideBandCqi, mBuf);
   CMCHKPK(SPkU8, param->cqiIdx, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuCqiPuschMode20
*
*
*     Desc : This structure conveys information present in CQI reporting mode 2-0 received
 * over PUSCH. This mode is for UE selected sub-band feedback.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuCqiPuschMode20
(
TfuCqiPuschMode20 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuCqiPuschMode20(param, mBuf)
TfuCqiPuschMode20 *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkTfuCqiPuschMode20)

   CMCHKUNPK(SUnpkU8, &param->cqiIdx, mBuf);
   CMCHKUNPK(SUnpkU8, &param->wideBandCqi, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numSubband, mBuf);
   for (i=0; i<TFU_MAX_DL_SUBBAND; i++) {
      CMCHKUNPK(cmUnpkTfuSubbandInfo, &param->subbandArr[i], mBuf);
   }
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkTfuCqiPuschMode22
*
*
*     Desc : This structure conveys information present in CQI reporting mode 2-2 received
 * over PUSCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuCqiPuschMode22
(
TfuCqiPuschMode22 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuCqiPuschMode22(param, mBuf)
TfuCqiPuschMode22 *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkTfuCqiPuschMode22)


   for (i=TFU_MAX_DL_SUBBAND-1; i >= 0; i--) {
      CMCHKPK(cmPkTfuSubbandInfo, &param->subbandArr[i], mBuf);
   }

   CMCHKPK(SPkU8, param->numSubband, mBuf);
   CMCHKPK(SPkU8, param->wideBandPmi, mBuf);
   for (i=TFU_MAX_TB-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->wideBandCqi[i], mBuf);
   }
   CMCHKPK(SPkU8, param->pmi, mBuf);
   for (i=TFU_MAX_TB-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->cqi[i], mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuCqiPuschMode22
*
*
*     Desc : This structure conveys information present in CQI reporting mode 2-2 received
 * over PUSCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuCqiPuschMode22
(
TfuCqiPuschMode22 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuCqiPuschMode22(param, mBuf)
TfuCqiPuschMode22 *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkTfuCqiPuschMode22)

   for (i=0; i<TFU_MAX_TB; i++) {
      CMCHKUNPK(SUnpkU8, &param->cqi[i], mBuf);
   }
   CMCHKUNPK(SUnpkU8, &param->pmi, mBuf);
   for (i=0; i<TFU_MAX_TB; i++) {
      CMCHKUNPK(SUnpkU8, &param->wideBandCqi[i], mBuf);
   }
   CMCHKUNPK(SUnpkU8, &param->wideBandPmi, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numSubband, mBuf);

   for (i=0; i<TFU_MAX_DL_SUBBAND; i++) {
      CMCHKUNPK(cmUnpkTfuSubbandInfo, &param->subbandArr[i], mBuf);
   }

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmPkTfuSubbandMode30
(
TfuSubbandMode30 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuSubbandMode30(param, mBuf)
TfuSubbandMode30 *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuSubbandMode30)

   CMCHKPK(cmPkTfuSubbandInfo, &param->subBand, mBuf);
   CMCHKPK(SPkU8, param->cqi, mBuf);
   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmUnpkTfuSubbandMode30
(
TfuSubbandMode30 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuSubbandMode30(param, mBuf)
TfuSubbandMode30 *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuSubbandMode30)

   CMCHKUNPK(SUnpkU8, &param->cqi, mBuf);
   CMCHKUNPK(cmUnpkTfuSubbandInfo, &param->subBand, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuCqiPuschMode30
*
*
*     Desc : This structure conveys information present in CQI reporting mode 3-0
 * received over PUSCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuCqiPuschMode30
(
TfuCqiPuschMode30 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuCqiPuschMode30(param, mBuf)
TfuCqiPuschMode30 *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkTfuCqiPuschMode30)

   for (i=TFU_MAX_DL_SUBBAND-1; i >= 0; i--) {
      CMCHKPK(cmPkTfuSubbandMode30, &param->subbandArr[i], mBuf);
   }
   CMCHKPK(SPkU8, param->numSubband, mBuf);
   CMCHKPK(SPkU8, param->wideBandCqi, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuCqiPuschMode30
*
*
*     Desc : This structure conveys information present in CQI reporting mode 3-0
 * received over PUSCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuCqiPuschMode30
(
TfuCqiPuschMode30 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuCqiPuschMode30(param, mBuf)
TfuCqiPuschMode30 *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkTfuCqiPuschMode30)

   CMCHKUNPK(SUnpkU8, &param->wideBandCqi, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numSubband, mBuf);
   for (i=0; i<TFU_MAX_DL_SUBBAND; i++) {
      CMCHKUNPK(cmUnpkTfuSubbandMode30, &param->subbandArr[i], mBuf);
   }
   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmPkTfuSubbandMode31
(
TfuSubbandMode31 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuSubbandMode31(param, mBuf)
TfuSubbandMode31 *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkTfuSubbandMode31)

   CMCHKPK(cmPkTfuSubbandInfo, &param->subBand, mBuf);
   for (i=TFU_MAX_TB-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->cqi[i], mBuf);
   }
   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmUnpkTfuSubbandMode31
(
TfuSubbandMode31 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuSubbandMode31(param, mBuf)
TfuSubbandMode31 *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkTfuSubbandMode31)

   for (i=0; i<TFU_MAX_TB; i++) {
      CMCHKUNPK(SUnpkU8, &param->cqi[i], mBuf);
   }
   CMCHKUNPK(cmUnpkTfuSubbandInfo, &param->subBand, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuCqiPuschMode31
*
*
*     Desc : This structure conveys information present in CQI reporting mode 3-1
 * received over PUSCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuCqiPuschMode31
(
TfuCqiPuschMode31 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuCqiPuschMode31(param, mBuf)
TfuCqiPuschMode31 *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkTfuCqiPuschMode31)


/* tfu_c_001.main_4 - Changes for MIMO feature addition */
/* tfu_c_001.main_5 - Removed dependency on MIMO compile-time flag */

/* tfu_c_001.main_4 - Changes for MIMO feature addition */
/* tfu_c_001.main_5 - Removed dependency on MIMO compile-time flag */
   for (i=param->numSubband-1; i >= 0; i--) {
      CMCHKPK(cmPkTfuSubbandDlCqiInfo, &param->subbandCqiArr[i], mBuf);
   }

   CMCHKPK(SPkU8, param->numSubband, mBuf);
   for (i=TFU_MAX_TB-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->wideBandCqi[i], mBuf);
   }
   CMCHKPK(SPkU8, param->pmi, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuCqiPuschMode31
*
*
*     Desc : This structure conveys information present in CQI reporting mode 3-1
 * received over PUSCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuCqiPuschMode31
(
TfuCqiPuschMode31 *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuCqiPuschMode31(param, mBuf)
TfuCqiPuschMode31 *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkTfuCqiPuschMode31)

   CMCHKUNPK(SUnpkU8, &param->pmi, mBuf);
   for (i=0; i<TFU_MAX_TB; i++) {
      CMCHKUNPK(SUnpkU8, &param->wideBandCqi[i], mBuf);
   }
   CMCHKUNPK(SUnpkU8, &param->numSubband, mBuf);

/* tfu_c_001.main_4 - Changes for MIMO feature addition */
/* tfu_c_001.main_5 - Removed dependency on MIMO compile-time flag */
   for (i=0; i<param->numSubband; i++) {
      CMCHKUNPK(cmUnpkTfuSubbandDlCqiInfo, &param->subbandCqiArr[i], mBuf);
   }


/* tfu_c_001.main_4 - Changes for MIMO feature addition */
/* tfu_c_001.main_5 - Removed dependency on MIMO compile-time flag */

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuDlCqiPusch
*
*
*     Desc : This structure conveys Downlink CQI information (mode and corresponding
 * CQI) received over PUSCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDlCqiPusch
(
TfuDlCqiPusch *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDlCqiPusch(param, mBuf)
TfuDlCqiPusch *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuDlCqiPusch)

      switch(param->mode) {
         case TFU_PUSCH_CQI_MODE_31:
            CMCHKPK(cmPkTfuCqiPuschMode31, &param->u.mode31Info, mBuf);
            break;
         case TFU_PUSCH_CQI_MODE_30:
            CMCHKPK(cmPkTfuCqiPuschMode30, &param->u.mode30Info, mBuf);
            break;
         case TFU_PUSCH_CQI_MODE_22:
            CMCHKPK(cmPkTfuCqiPuschMode22, &param->u.mode22Info, mBuf);
            break;
         case TFU_PUSCH_CQI_MODE_20:
            CMCHKPK(cmPkTfuCqiPuschMode20, &param->u.mode20Info, mBuf);
            break;
         case TFU_PUSCH_CQI_MODE_12:
            CMCHKPK(cmPkTfuCqiPuschMode12, &param->u.mode12Info, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }

   CMCHKPK(cmPkTknU8, &param->ri, mBuf);
   CMCHKPK(SPkU32, param->mode, mBuf);

   CMCHKPK(SPkU8, param->cellIdx, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDlCqiPusch
*
*
*     Desc : This structure conveys Downlink CQI information (mode and corresponding
 * CQI) received over PUSCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDlCqiPusch
(
TfuDlCqiPusch *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDlCqiPusch(param, mBuf)
TfuDlCqiPusch *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuDlCqiPusch)

   CMCHKUNPK(SUnpkU8, &param->cellIdx, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&param->mode, mBuf);
   CMCHKUNPK(cmUnpkTknU8, &param->ri, mBuf);
   switch(param->mode) {
      case TFU_PUSCH_CQI_MODE_12:
         CMCHKUNPK(cmUnpkTfuCqiPuschMode12, &param->u.mode12Info, mBuf);
         break;
      case TFU_PUSCH_CQI_MODE_20:
         CMCHKUNPK(cmUnpkTfuCqiPuschMode20, &param->u.mode20Info, mBuf);
         break;
      case TFU_PUSCH_CQI_MODE_22:
         CMCHKUNPK(cmUnpkTfuCqiPuschMode22, &param->u.mode22Info, mBuf);
         break;
      case TFU_PUSCH_CQI_MODE_30:
         CMCHKUNPK(cmUnpkTfuCqiPuschMode30, &param->u.mode30Info, mBuf);
         break;
      case TFU_PUSCH_CQI_MODE_31:
         CMCHKUNPK(cmUnpkTfuCqiPuschMode31, &param->u.mode31Info, mBuf);
         break;
      default :
         RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkTfuDlCqiInfo
*
*
*     Desc : This structure contains CQI information received over PUCCH or PUSCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDlCqiInfo
(
U8 selector,
TfuDlCqiInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDlCqiInfo(selector, param, mBuf)
U8 selector;
TfuDlCqiInfo *param;
Buffer *mBuf;
#endif
{
   U32 idx;

   TRC3(cmPkTfuDlCqiInfo)

   switch(selector) {
      case FALSE:
         for (idx = 0; idx < param->pusch.numOfCells; idx++)
         {
            CMCHKPK(cmPkTfuDlCqiPusch, &param->pusch.puschCqi[idx], mBuf);
         }
         CMCHKPK(SPkU8, param->pusch.numOfCells, mBuf);
         break;
      case TRUE:
         CMCHKPK(cmPkTfuDlCqiPucch, &param->pucchCqi, mBuf);
         break;
      default :
         RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDlCqiInfo
*
*
*     Desc : This structure contains CQI information received over PUCCH or PUSCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDlCqiInfo
(
U8 selector,
TfuDlCqiInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDlCqiInfo(selector, param, mBuf)
U8 selector;
TfuDlCqiInfo *param;
Buffer *mBuf;
#endif
{

   U8 idx;
   TRC3(cmUnpkTfuDlCqiInfo)

   switch(selector) {
      case TRUE:
         CMCHKUNPK(cmUnpkTfuDlCqiPucch, &param->pucchCqi, mBuf);
         break;
      case FALSE:
         CMCHKUNPK(SUnpkU8, &param->pusch.numOfCells, mBuf);
         for (idx = param->pusch.numOfCells; idx > 0; idx--)
         {
            CMCHKUNPK(cmUnpkTfuDlCqiPusch, &param->pusch.puschCqi[idx-1], mBuf);
         }
         break;
      default :
         RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuRecpReqInfo
*
*
*     Desc : This structure is sent from Scheduler to PHY. This includes params
 * needed by PHY to decode the following 
 * 1. DATA on PUSCH
 * 2. HARQ Feedback on PUCCH
 * 3. CQI Report 
 * 4. RI Report
 * 5. SR Indications.
 * This structure carries the reception information for all the scheduled UE.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuRecpReqInfo
(
TfuRecpReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuRecpReqInfo(param, mBuf)
TfuRecpReqInfo *param;
Buffer *mBuf;
#endif
{
   CmLList *node;
   U32 count;
   TfuUeRecpReqInfo *tfuUeRecpReqInfo;

   TRC3(cmPkTfuRecpReqInfo)

   /*ccpu00116923 - ADD - SRS present support*/
   /*tfu_c_001.main_7 - ADD - SRS present field inclusion */
#ifdef TFU_UPGRADE
   CMCHKPK(SPkU8, param->srsPres, mBuf);
#endif
   count = param->ueRecpReqLst.count;
   node = param->ueRecpReqLst.last;
   while (node) {
      tfuUeRecpReqInfo = (TfuUeRecpReqInfo *)node->node;
      node=node->prev;
      CMCHKPK(cmPkTfuUeRecpReqInfo, tfuUeRecpReqInfo, mBuf);
      cmLListDelFrm(&param->ueRecpReqLst, &tfuUeRecpReqInfo->lnk);
      tfuUeRecpReqInfo->lnk.node = (PTR)NULLP;
   }
   CMCHKPK(SPkU32, count, mBuf);
   CMCHKPK(cmPkLteTimingInfo, &param->timingInfo, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuRecpReqInfo
*
*
*     Desc : This structure is sent from Scheduler to PHY. This includes params
 * needed by PHY to decode the following 
 * 1. DATA on PUSCH
 * 2. HARQ Feedback on PUCCH
 * 3. CQI Report 
 * 4. RI Report
 * 5. SR Indications.
 * This structure carries the reception information for all the scheduled UE.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuRecpReqInfo
(
TfuRecpReqInfo *param,
Ptr memCp,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuRecpReqInfo(param, memCp, mBuf)
TfuRecpReqInfo *param;
Ptr memCp;
Buffer *mBuf;
#endif
{

   U32 count, loopCnt;
   TfuUeRecpReqInfo *tfuUeRecpReqInfo;

   TRC3(cmUnpkTfuRecpReqInfo)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteTimingInfo, &param->timingInfo, mBuf);
   cmLListInit(&param->ueRecpReqLst);
   CMCHKUNPK(SUnpkU32, &count, mBuf);
   for (loopCnt=0; loopCnt<count; loopCnt++) {
      cmGetMem((Ptr)memCp, sizeof(*tfuUeRecpReqInfo), (Ptr *)&tfuUeRecpReqInfo);
      CMCHKUNPK(cmUnpkTfuUeRecpReqInfo, tfuUeRecpReqInfo, mBuf);
      cmLListAdd2Tail(&param->ueRecpReqLst, &tfuUeRecpReqInfo->lnk);
      tfuUeRecpReqInfo->lnk.node = (PTR)tfuUeRecpReqInfo;
   }
   /*ccpu00116923 - ADD - SRS present support*/
   /*tfu_c_001.main_7 - ADD - SRS present field inclusion */
#ifdef TFU_UPGRADE
   CMCHKUNPK(SUnpkU8, &param->srsPres, mBuf);
#endif
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuPdcchInfo
*
*
*     Desc : This structure contains the PDCCH to be sent on PHY i.e. DCI
  * formats. This information is associated with an RNTI.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuPdcchInfo
(
TfuPdcchInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuPdcchInfo(param, mBuf)
TfuPdcchInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuPdcchInfo)

   CMCHKPK(cmPkTfuDciInfo, &param->dci, mBuf);
   CMCHKPK(SPkU8, param->dciNumOfBits, mBuf);
   CMCHKPK(cmPkLteAggrLvl, param->aggrLvl, mBuf);
   CMCHKPK(SPkU16, param->nCce, mBuf);
#ifdef LTEMAC_SPS
   CMCHKPK(cmPkLteRnti, param->crnti, mBuf);
   CMCHKPK(SPkU8, param->isSpsRnti, mBuf);
#endif
   CMCHKPK(cmPkLteRnti, param->rnti, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuPdcchInfo
*
*
*     Desc : This structure contains the PDCCH to be sent on PHY i.e. DCI
  * formats. This information is associated with an RNTI.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuPdcchInfo
(
TfuPdcchInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuPdcchInfo(param, mBuf)
TfuPdcchInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuPdcchInfo)

   CMCHKUNPK(cmUnpkLteRnti, &param->rnti, mBuf);
#ifdef LTEMAC_SPS
   CMCHKUNPK(SUnpkU8, &param->isSpsRnti, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &param->crnti, mBuf);
#endif
   CMCHKUNPK(SUnpkU16, &param->nCce, mBuf);
   CMCHKUNPK(cmUnpkLteAggrLvl, (U32*)&param->aggrLvl, mBuf);
   CMCHKUNPK(SUnpkU8, &param->dciNumOfBits, mBuf);
   CMCHKUNPK(cmUnpkTfuDciInfo, &param->dci, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuPhichInfo
*
*
*     Desc : This structure contains one PHICH information. In order to locate the
 * resources to be used for PHICH the following information is provided along
 * with the feedback -
 * -# rbStart
 * -# nDmrs
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuPhichInfo
(
TfuPhichInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuPhichInfo(param, mBuf)
TfuPhichInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuPhichInfo)
/* tfu_c_001.main_7. Added changes of TFU_UPGRADE */
#ifdef TFU_UPGRADE
   CMCHKPK(SPkU16, param->txPower, mBuf);
#endif
#ifdef TFU_TDD
   CMCHKPK(SPkU8, param->iPhich, mBuf);
#endif
   CMCHKPK(SPkU8, param->isAck, mBuf);
   CMCHKPK(SPkU8, param->nDmrs, mBuf);
   CMCHKPK(SPkU8, param->rbStart, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuPhichInfo
*
*
*     Desc : This structure contains one PHICH information. In order to locate the
 * resources to be used for PHICH the following information is provided along
 * with the feedback -
 * -# rbStart
 * -# nDmrs
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuPhichInfo
(
TfuPhichInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuPhichInfo(param, mBuf)
TfuPhichInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuPhichInfo)

   CMCHKUNPK(SUnpkU8, &param->rbStart, mBuf);
   CMCHKUNPK(SUnpkU8, &param->nDmrs, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isAck, mBuf);
/* tfu_c_001.main_7. Added changes of TFU_UPGRADE */
#ifdef TFU_TDD
   CMCHKUNPK(SUnpkU8, &param->iPhich, mBuf);
#endif
#ifdef TFU_UPGRADE   
   CMCHKUNPK(SUnpkU16, &param->txPower, mBuf);
#endif
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuCntrlReqInfo
*
*
*     Desc : This structure is sent from Scheduler to PHY. This includes all the
 * control information to be sent to the UE. 
 * -# PDCCH  Physical Downlink Control Channel
 * -# PHICH  Physical HARQ Indicator Channel
 * -# PCFICH Physical Control Format Indicator Channel
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuCntrlReqInfo
(
TfuCntrlReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuCntrlReqInfo(param, mBuf)
TfuCntrlReqInfo *param;
Buffer *mBuf;
#endif
{

   TfuPdcchInfo   *tfuPdcchInfo;
   TfuPhichInfo *tfuPhichInfo;
   CmLList *node;
   U32 count;

   TRC3(cmPkTfuCntrlReqInfo)
#ifdef LTEMAC_SPS /* SPS_NEW_CHGS */
   CMCHKPK(cmPkBool, param->isSPSOcc, mBuf);
#endif
   count = param->phichLst.count;
   node = param->phichLst.last;
   while (node) {
      tfuPhichInfo = (TfuPhichInfo *)node->node;
      node=node->prev;
      CMCHKPK(cmPkTfuPhichInfo, tfuPhichInfo, mBuf);
      cmLListDelFrm(&param->phichLst, &tfuPhichInfo->lnk);
      tfuPhichInfo->lnk.node = (PTR)NULLP;
   }
   CMCHKPK(SPkU32, count, mBuf);
   count = param->dlPdcchLst.count;
   node = param->dlPdcchLst.last;
   while (node) {
      tfuPdcchInfo = (TfuPdcchInfo *)node->node;
      node=node->prev;
      CMCHKPK(cmPkTfuPdcchInfo, tfuPdcchInfo, mBuf);
      cmLListDelFrm(&param->dlPdcchLst, &tfuPdcchInfo->lnk);
      tfuPdcchInfo->lnk.node = (PTR)NULLP;
   }
   CMCHKPK(SPkU32, count, mBuf);
   count = param->ulPdcchLst.count;
   node = param->ulPdcchLst.last;
   while (node) {
      tfuPdcchInfo = (TfuPdcchInfo *)node->node;
      node=node->prev;
      CMCHKPK(cmPkTfuPdcchInfo, tfuPdcchInfo, mBuf);
      cmLListDelFrm(&param->ulPdcchLst, &tfuPdcchInfo->lnk);
      tfuPdcchInfo->lnk.node = (PTR)NULLP;
   }
   CMCHKPK(SPkU32, count, mBuf);
   CMCHKPK(SPkU8, param->cfi, mBuf);
   CMCHKPK(cmPkLteTimingInfo, &param->dlTiming, mBuf);
   CMCHKPK(cmPkLteTimingInfo, &param->ulTiming, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuCntrlReqInfo
*
*
*     Desc : This structure is sent from Scheduler to PHY. This includes all the
 * control information to be sent to the UE. 
 * -# PDCCH  Physical Downlink Control Channel
 * -# PHICH  Physical HARQ Indicator Channel
 * -# PCFICH Physical Control Format Indicator Channel
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuCntrlReqInfo
(
TfuCntrlReqInfo *param,
Ptr memCp,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuCntrlReqInfo(param, memCp, mBuf)
TfuCntrlReqInfo *param;
Ptr memCp;
Buffer *mBuf;
#endif
{

   TfuPdcchInfo *tfuPdcchInfo;
   U32 count, loopCnt;
   TfuPhichInfo *tfuPhichInfo;

   TRC3(cmUnpkTfuCntrlReqInfo)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteTimingInfo, &param->ulTiming, mBuf);
   CMCHKUNPK(cmUnpkLteTimingInfo, &param->dlTiming, mBuf);
   CMCHKUNPK(SUnpkU8, &param->cfi, mBuf);
   cmLListInit(&param->ulPdcchLst);
   CMCHKUNPK(SUnpkU32, &count, mBuf);
   for (loopCnt=0; loopCnt<count; loopCnt++) {
      cmGetMem((Ptr)memCp, sizeof(*tfuPdcchInfo), (Ptr *)&tfuPdcchInfo);
      CMCHKUNPK(cmUnpkTfuPdcchInfo, tfuPdcchInfo, mBuf);
      cmLListAdd2Tail(&param->ulPdcchLst, &tfuPdcchInfo->lnk);
      tfuPdcchInfo->lnk.node = (PTR)tfuPdcchInfo;
   }
   cmLListInit(&param->dlPdcchLst);
   CMCHKUNPK(SUnpkU32, &count, mBuf);
   for (loopCnt=0; loopCnt<count; loopCnt++) {
      cmGetMem((Ptr)memCp, sizeof(*tfuPdcchInfo), (Ptr *)&tfuPdcchInfo);
      CMCHKUNPK(cmUnpkTfuPdcchInfo, tfuPdcchInfo, mBuf);
      cmLListAdd2Tail(&param->dlPdcchLst, &tfuPdcchInfo->lnk);
      tfuPdcchInfo->lnk.node = (PTR)tfuPdcchInfo;
   }
   cmLListInit(&param->phichLst);
   CMCHKUNPK(SUnpkU32, &count, mBuf);
   for (loopCnt=0; loopCnt<count; loopCnt++) {
      cmGetMem((Ptr)memCp, sizeof(*tfuPhichInfo), (Ptr *)&tfuPhichInfo);
      CMCHKUNPK(cmUnpkTfuPhichInfo, tfuPhichInfo, mBuf);
      cmLListAdd2Tail(&param->phichLst, &tfuPhichInfo->lnk);
      tfuPhichInfo->lnk.node = (PTR)tfuPhichInfo;
   }

#ifdef LTEMAC_SPS /* SPS_NEW_CHGS */
   CMCHKUNPK(cmUnpkBool, &param->isSPSOcc, mBuf);
#endif
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuPdschDciInfo
*
*
*     Desc : This structure Carries the control information that would be needed
  * by the Physical layer to process the data to be sent on PDSCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuPdschDciInfo
(
TfuPdschDciInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuPdschDciInfo(param, mBuf)
TfuPdschDciInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuPdschDciInfo)

      switch(param->format) {
         case TFU_DCI_FORMAT_2A:
            CMCHKPK(cmPkTfuDciFormat2AAllocInfo, &param->u.format2AAllocInfo, mBuf);
            break;
         case TFU_DCI_FORMAT_2:
            CMCHKPK(cmPkTfuDciFormat2AllocInfo, &param->u.format2AllocInfo, mBuf);
            break;
         case TFU_DCI_FORMAT_1D:
            CMCHKPK(cmPkTfuDciFormat1dAllocInfo, &param->u.format1dAllocInfo, mBuf);
            break;
         case TFU_DCI_FORMAT_1C:
            CMCHKPK(cmPkTfuDciFormat1cInfo, &param->u.format1cAllocInfo, mBuf);
            break;
         case TFU_DCI_FORMAT_1B:
            CMCHKPK(cmPkTfuDciFormat1bAllocInfo, &param->u.format1bAllocInfo, mBuf);
            break;
         case TFU_DCI_FORMAT_1A:
            CMCHKPK(cmPkTfuDciFormat1aAllocInfo, &param->u.format1aAllocInfo, mBuf);
            break;
         case TFU_DCI_FORMAT_1:
            CMCHKPK(cmPkTfuDciFormat1AllocInfo, &param->u.format1AllocInfo, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(SPkU32, param->format, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuPdschDciInfo
*
*
*     Desc : This structure Carries the control information that would be needed
  * by the Physical layer to process the data to be sent on PDSCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuPdschDciInfo
(
TfuPdschDciInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuPdschDciInfo(param, mBuf)
TfuPdschDciInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuPdschDciInfo)

   CMCHKUNPK(SUnpkU32, (U32 *)&param->format, mBuf);
      switch(param->format) {
         case TFU_DCI_FORMAT_1:
            CMCHKUNPK(cmUnpkTfuDciFormat1AllocInfo, &param->u.format1AllocInfo, mBuf);
            break;
         case TFU_DCI_FORMAT_1A:
            CMCHKUNPK(cmUnpkTfuDciFormat1aAllocInfo, &param->u.format1aAllocInfo, mBuf);
            break;
         case TFU_DCI_FORMAT_1B:
            CMCHKUNPK(cmUnpkTfuDciFormat1bAllocInfo, &param->u.format1bAllocInfo, mBuf);
            break;
         case TFU_DCI_FORMAT_1C:
            CMCHKUNPK(cmUnpkTfuDciFormat1cInfo, &param->u.format1cAllocInfo, mBuf);
            break;
         case TFU_DCI_FORMAT_1D:
            CMCHKUNPK(cmUnpkTfuDciFormat1dAllocInfo, &param->u.format1dAllocInfo, mBuf);
            break;
         case TFU_DCI_FORMAT_2:
            CMCHKUNPK(cmUnpkTfuDciFormat2AllocInfo, &param->u.format2AllocInfo, mBuf);
            break;
         case TFU_DCI_FORMAT_2A:
            CMCHKUNPK(cmUnpkTfuDciFormat2AAllocInfo, &param->u.format2AAllocInfo, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}
/* tfu_c_001.main_7. Added changes of TFU_UPGRADE */
#ifdef TFU_UPGRADE
/***********************************************************
*
*     Func : cmPkTfuBfVectorInfo
*
*
*     Desc : This structure conveys the BeamForming Vector 
*               Information that hold relevance to Tx Mode 7
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuBfVectorInfo
(
TfuBfVectorInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuBfVectorInfo(param, mBuf)
TfuBfVectorInfo *param;
Buffer *mBuf;
#endif
{
   S32 idx, idx2;
   TRC3(cmPkTfuBfVectorInfo)
   for(idx=TFU_MAX_DL_SUBBAND-1;idx>=0; idx--)
   {
      for (idx2=param->numPhyAnt -1; idx2 >= 0; idx2--) {
      CMCHKPK(SPkU16, param->bfValue[idx2], mBuf);}
      CMCHKPK(SPkU8, param->numPhyAnt, mBuf);
      CMCHKPK(SPkU8, param->sbIndex, mBuf);
   }
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmUnpkTfuBfVectorInfo
*
*
*     Desc : This structure conveys the BeamForming Vector 
*               Information that hold relevance to Tx Mode 7
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuBfVectorInfo
(
   TfuBfVectorInfo *param,
   Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuBfVectorInfo(param, mBuf)
 TfuBfVectorInfo *param;
 Buffer *mBuf;
#endif
{
   S32 idx, idx2;
   TRC3(cmUnpkTfuBfVectorInfo)
    for(idx=0;idx<TFU_MAX_DL_SUBBAND; idx++)
   {
      CMCHKUNPK(SUnpkU8, &param->sbIndex, mBuf);
      CMCHKUNPK(SUnpkU8, &param->numPhyAnt, mBuf);
      for (idx2=0; idx2 <param->numPhyAnt; idx2++) {
      CMCHKUNPK(SUnpkU16, &param->bfValue[idx2], mBuf);}
   }
  
   RETVALUE(ROK);
}
#endif 

/***********************************************************
*
*     Func : cmPkTfuDatReqPduInfo
*
*
*     Desc : Pack Function for Tfu Dat Req PDU.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDatReqPduInfo
(
TfuDatReqPduInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDatReqPduInfo(param, mBuf)
TfuDatReqPduInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   U8  tbMask = 0;
#ifdef L2_OPTMZ
   U32 lchIdx, pduIdx;
#endif

   TRC3(cmPkTfuDatReqPduInfo)

   /* LTE_ADV_FLAG_REMOVED_START */
   CMCHKPK(SPkU8, param->isEnbSFR, mBuf);
   /* LTE_ADV_FLAG_REMOVED_END */

   /* tfu_c_001.main_7. Added changes of TFU_UPGRADE */
#ifdef TFU_UPGRADE 
   CMCHKPK(SPkU16, param->txPwrOffset, mBuf);
   if(param->transMode == TFU_UE_TM_7)
   {
      CMCHKPK(cmPkTfuBfVectorInfo, param->bfVector, mBuf);
      CMCHKPK(SPkU8, param->numBfVectors, mBuf);
      CMCHKPK(SPkU8, param->numBfPrbPerSb, mBuf);
   }
   CMCHKPK(SPkU8, param->deltaPowOffIdx, mBuf);
   /* LTE_ADV_FLAG_REMOVED_START */
   CMCHKPK(SPkU8, param->pa, mBuf);
   /* LTE_ADV_FLAG_REMOVED_END */
   CMCHKPK(SPkU8, param->numLayers, mBuf);
#endif
   CMCHKPK(cmPkBool, param->isTApres, mBuf);
   CMCHKPK(cmPkTknU32, &param->doa, mBuf);
   CMCHKPK(SPkU32, param->transMode, mBuf);
   CMCHKPK(cmPkTfuDlCqiPuschInfo, &param->puschPmiInfo, mBuf);
   CMCHKPK(SPkU8, param->puschRptUsd, mBuf);
   for (i = 0; i < TFU_MAX_TB; i++)
   {
#ifndef L2_OPTMZ
     if (param->mBuf[i] != NULLP)
     {
        tbMask = tbMask | (1 << i);
     }
#else /* L2_OPTMZ */
     for(lchIdx = 0; lchIdx < param->tbInfo[i].numLch; lchIdx++)
     {
        for(pduIdx = 0; pduIdx < param->tbInfo[i].lchInfo[lchIdx].numPdu;
              pduIdx++)
        {
           if (param->tbInfo[i].lchInfo[lchIdx].mBuf[pduIdx] != NULLP)
           {
              tbMask = tbMask | (1 << i);
           }
        }
     }
#endif /* L2_OPTMZ */
   }
   /* tfu_c_001.main_2: Packing should consider nmbOfTBs.*/
   for (i=TFU_MAX_TB - 1; i >= 0; i--) {
#ifndef L2_OPTMZ
      if (param->mBuf[i] != NULLP)
      {
         CMCHKPK(cmPkBuffer, &param->mBuf[i], mBuf);
      }
#else
     // CMCHKPK(cmPkBuffer, &param->tbInfo[i].macPad, mBuf);
      for(lchIdx = 0; lchIdx < param->tbInfo[i].numLch; lchIdx++)
      {
         for(pduIdx = 0; pduIdx < param->tbInfo[i].lchInfo[lchIdx].numPdu;
               pduIdx++)
         {
            CMCHKPK(cmPkBuffer, &param->tbInfo[i].lchInfo[lchIdx].mBuf[pduIdx],
                  mBuf);

         }
         CMCHKPK(SPkU32, param->tbInfo[i].lchInfo[lchIdx].numPdu, mBuf);
      }
      CMCHKPK(SPkU32, param->tbInfo[i].numLch, mBuf);
      CMCHKPK(SPkU32, param->tbInfo[i].padSize, mBuf);
      CMCHKPK(cmPkBuffer, &param->tbInfo[i].macCes, mBuf);
      CMCHKPK(cmPkBuffer, &param->tbInfo[i].macHdr, mBuf);
      CMCHKPK(cmPkMsgLen, param->tbInfo[i].tbSize, mBuf);
      CMCHKPK(cmPkBool, param->tbInfo[i].tbPres, mBuf);
#endif
   }
   CMCHKPK(SPkU8, tbMask, mBuf);
   CMCHKPK(SPkU8, param->nmbOfTBs, mBuf);
   CMCHKPK(cmPkTfuPdschDciInfo, &param->dciInfo, mBuf);
   CMCHKPK(cmPkLteRnti, param->rnti, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDatReqPduInfo
*
*
*     Desc : UnPack function for Tfu Dat req pdu .
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDatReqPduInfo
(
TfuDatReqPduInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDatReqPduInfo(param, mBuf)
TfuDatReqPduInfo *param;
Buffer *mBuf;
#endif
{

   U8 i;
   U8  tbMask = 0;
#ifdef L2_OPTMZ
   U32 lchIdx, pduIdx;
#endif
   TRC3(cmUnpkTfuDatReqPduInfo)

   CMCHKUNPK(cmUnpkLteRnti, &param->rnti, mBuf);
   CMCHKUNPK(cmUnpkTfuPdschDciInfo, &param->dciInfo, mBuf);
   CMCHKUNPK(SUnpkU8, &param->nmbOfTBs, mBuf);

   CMCHKUNPK(SUnpkU8, &tbMask, mBuf);
   for (i=0; i<TFU_MAX_TB; i++) {
#ifndef L2_OPTMZ
      if (tbMask & (1<<i))
      {
         CMCHKUNPK(cmUnpkBuffer, &param->mBuf[i], mBuf);
      }
      else
      {
         param->mBuf[i] = NULLP;
      }
#else /* L2_OPTMZ*/
      CMCHKUNPK(cmUnpkBool, &param->tbInfo[i].tbPres, mBuf);
      CMCHKUNPK(cmUnpkMsgLen, &param->tbInfo[i].tbSize, mBuf);
      CMCHKUNPK(cmUnpkBuffer, &param->tbInfo[i].macHdr, mBuf);
      CMCHKUNPK(cmUnpkBuffer, &param->tbInfo[i].macCes, mBuf);
      CMCHKUNPK(SUnpkU32, &param->tbInfo[i].padSize, mBuf);
      CMCHKUNPK(SUnpkU32, (U32 *)&param->tbInfo[i].numLch, mBuf);
      for(lchIdx = 0; lchIdx < param->tbInfo[i].numLch; lchIdx++)
      {
         CMCHKUNPK(SUnpkU32, (U32 *)&param->tbInfo[i].lchInfo[lchIdx].numPdu,
               mBuf);
         for(pduIdx = 0; pduIdx < param->tbInfo[i].lchInfo[lchIdx].numPdu;
               pduIdx++)
         {
            if (tbMask & (1<<i))
            {
               CMCHKUNPK(cmUnpkBuffer, &param->tbInfo[i].lchInfo[lchIdx].\
                     mBuf[pduIdx], mBuf);
            }
            else
            {
               param->tbInfo[i].lchInfo[lchIdx].mBuf[pduIdx] = NULLP;
            }
         }
      }
      //CMCHKUNPK(cmUnpkBuffer, &param->tbInfo[i].macPad, mBuf);
#endif /* L2_OPTMZ*/
   }

   CMCHKUNPK(SUnpkU8, &param->puschRptUsd, mBuf);
   CMCHKUNPK(cmUnpkTfuDlCqiPuschInfo, &param->puschPmiInfo, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&param->transMode, mBuf);
   CMCHKUNPK(cmUnpkTknU32, &param->doa, mBuf);
   CMCHKUNPK(cmUnpkBool, &param->isTApres, mBuf);
/* tfu_c_001.main_7. Added changes of TFU_UPGRADE */
#ifdef TFU_UPGRADE
   CMCHKUNPK(SUnpkU8, &param->numLayers, mBuf);
   /* LTE_ADV_FLAG_REMOVED_START */
   CMCHKUNPK(SUnpkU8, &param->pa, mBuf);
   /* LTE_ADV_FLAG_REMOVED_END */
   CMCHKUNPK(SUnpkU8, &param->deltaPowOffIdx, mBuf);
   if(param->transMode == TFU_UE_TM_7)
   {
      CMCHKUNPK(SUnpkU8, &param->numBfPrbPerSb, mBuf);
      CMCHKUNPK(SUnpkU8, &param->numBfVectors, mBuf);
      CMCHKUNPK(cmUnpkTfuBfVectorInfo, param->bfVector, mBuf);
   }
   CMCHKUNPK(SUnpkU16, &param->txPwrOffset, mBuf);
#endif

   /* LTE_ADV_FLAG_REMOVED_START */
   CMCHKUNPK(SUnpkU8, &param->isEnbSFR, mBuf);
   /* LTE_ADV_FLAG_REMOVED_END */

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuDatReqInfo
*
*
*     Desc : This structure contains the Data PDUs 
 * @details This structure contains Data meant to be sent on both PBCH and
 * PDSCH. Control information necessary for processing of the data is sent along
 * with the Data.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDatReqInfo
(
TfuDatReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDatReqInfo(param, mBuf)
TfuDatReqInfo *param;
Buffer *mBuf;
#endif
{

   CmLList *node;
   U32 count;
   TfuDatReqPduInfo *tfuDatReqPduInfo;

   TRC3(cmPkTfuDatReqInfo)

   count = param->pdus.count;
   node = param->pdus.last;
   while (node) {
      tfuDatReqPduInfo = (TfuDatReqPduInfo *)node->node;
      node=node->prev;
      CMCHKPK(cmPkTfuDatReqPduInfo, tfuDatReqPduInfo, mBuf);
      cmLListDelFrm(&param->pdus, &tfuDatReqPduInfo->lnk);
      tfuDatReqPduInfo->lnk.node = (PTR)NULLP;
   }
   CMCHKPK(SPkU32, count, mBuf);
   CMCHKPK(cmPkTknBuf, &param->bchDat, mBuf);
   CMCHKPK(cmPkLteTimingInfo, &param->timingInfo, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDatReqInfo
*
*
*     Desc : This structure contains the Data PDUs 
 * @details This structure contains Data meant to be sent on both PBCH and
 * PDSCH. Control information necessary for processing of the data is sent along
 * with the Data.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDatReqInfo
(
TfuDatReqInfo *param,
Ptr memCp,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDatReqInfo(param, memCp, mBuf)
TfuDatReqInfo *param;
Ptr memCp;
Buffer *mBuf;
#endif
{

   U32 count, loopCnt;
   TfuDatReqPduInfo *tfuDatReqPduInfo;

   TRC3(cmUnpkTfuDatReqInfo)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteTimingInfo, &param->timingInfo, mBuf);
   CMCHKUNPK(cmUnpkTknBuf, &param->bchDat, &mBuf);
   cmLListInit(&param->pdus);
   CMCHKUNPK(SUnpkU32, &count, mBuf);
   for (loopCnt=0; loopCnt<count; loopCnt++) {
      cmGetMem((Ptr)memCp, sizeof(*tfuDatReqPduInfo), (Ptr *)&tfuDatReqPduInfo);
      CMCHKUNPK(cmUnpkTfuDatReqPduInfo, tfuDatReqPduInfo, mBuf);
      cmLListAdd2Tail(&param->pdus, &tfuDatReqPduInfo->lnk);
      tfuDatReqPduInfo->lnk.node = (PTR)tfuDatReqPduInfo;
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuDatInfo
*
*
*     Desc : This structure contains the Data PDU and the RNTI of the UE.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDatInfo
(
TfuDatInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDatInfo(param, mBuf)
TfuDatInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuDatInfo)

   CMCHKPK(cmPkBuffer, &param->mBuf, mBuf);
   CMCHKPK(cmPkLteRnti, param->rnti, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDatInfo
*
*
*     Desc : This structure contains the Data PDU and the RNTI of the UE.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDatInfo
(
TfuDatInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDatInfo(param, mBuf)
TfuDatInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuDatInfo)

   CMCHKUNPK(cmUnpkLteRnti, &param->rnti, mBuf);
   CMCHKUNPK(cmUnpkBuffer, &param->mBuf, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuDatIndInfo
*
*
*     Desc : This structure contains the Data PDUs received at Physical Layer.
 * @details All the PDUs received by Physical layer in one subframe are clubbed
 * together into a single data structure and sent to MAC for processing.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDatIndInfo
(
TfuDatIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDatIndInfo(param, mBuf)
TfuDatIndInfo *param;
Buffer *mBuf;
#endif
{

   CmLList *node;
   U32 count;
   TfuDatInfo *tfuDatInfo;

   TRC3(cmPkTfuDatIndInfo)

   count = param->datIndLst.count;
   node = param->datIndLst.last;
   while (node) {
      tfuDatInfo = (TfuDatInfo *)node->node;
      node=node->prev;
      CMCHKPK(cmPkTfuDatInfo, tfuDatInfo, mBuf);
      cmLListDelFrm(&param->datIndLst, &tfuDatInfo->lnk);
      tfuDatInfo->lnk.node = (PTR)NULLP;
   }
   CMCHKPK(SPkU32, count, mBuf);
   CMCHKPK(cmPkLteTimingInfo, &param->timingInfo, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDatIndInfo
*
*
*     Desc : This structure contains the Data PDUs received at Physical Layer.
 * @details All the PDUs received by Physical layer in one subframe are clubbed
 * together into a single data structure and sent to MAC for processing.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDatIndInfo
(
TfuDatIndInfo *param,
Ptr memCp,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDatIndInfo(param, memCp, mBuf)
TfuDatIndInfo *param;
Ptr memCp;
Buffer *mBuf;
#endif
{

   U32 count, loopCnt;
   TfuDatInfo *tfuDatInfo;

   TRC3(cmUnpkTfuDatIndInfo)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteTimingInfo, &param->timingInfo, mBuf);
   cmLListInit(&param->datIndLst);
   CMCHKUNPK(SUnpkU32, &count, mBuf);
   for (loopCnt=0; loopCnt<count; loopCnt++) {
      cmGetMem((Ptr)memCp, sizeof(*tfuDatInfo), (Ptr *)&tfuDatInfo);
      CMCHKUNPK(cmUnpkTfuDatInfo, tfuDatInfo, mBuf);
      cmLListAdd2Tail(&param->datIndLst, &tfuDatInfo->lnk);
      tfuDatInfo->lnk.node = (PTR)tfuDatInfo;
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuSrInfo
*
*
*     Desc : This structure contains the SR indication for a UE, identified by
  * the given RNTI. The structure also contains a PUCCH Delta power, that is
  * calculated by the physical layer, and is used by the scheduler for Power
  * control of the UE.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuSrInfo
(
TfuSrInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuSrInfo(param, mBuf)
TfuSrInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuSrInfo)

   CMCHKPK(cmPkLteRnti, param->rnti, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuSrInfo
*
*
*     Desc : This structure contains the SR indication for a UE, identified by
  * the given RNTI. The structure also contains a PUCCH Delta power, that is
  * calculated by the physical layer, and is used by the scheduler for Power
  * control of the UE.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuSrInfo
(
TfuSrInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuSrInfo(param, mBuf)
TfuSrInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuSrInfo)

   CMCHKUNPK(cmUnpkLteRnti, &param->rnti, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuSrIndInfo
*
*
*     Desc : This structure contains all the Scheduling Requests (SR) indications
  * received in a subframe.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuSrIndInfo
(
TfuSrIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuSrIndInfo(param, mBuf)
TfuSrIndInfo *param;
Buffer *mBuf;
#endif
{

   CmLList *node;
   U32 count;
   TfuSrInfo *tfuSrInfo;

   TRC3(cmPkTfuSrIndInfo)

   count = param->srLst.count;
   node = param->srLst.last;
   while (node) {
      tfuSrInfo = (TfuSrInfo *)node->node;
      node=node->prev;
      CMCHKPK(cmPkTfuSrInfo, tfuSrInfo, mBuf);
      cmLListDelFrm(&param->srLst, &tfuSrInfo->lnk);
      tfuSrInfo->lnk.node = (PTR)NULLP;
   }
   CMCHKPK(SPkU32, count, mBuf);
   CMCHKPK(cmPkLteTimingInfo, &param->timingInfo, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuSrIndInfo
*
*
*     Desc : This structure contains all the Scheduling Requests (SR) indications
  * received in a subframe.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuSrIndInfo
(
TfuSrIndInfo *param,
Ptr memCp,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuSrIndInfo(param, memCp, mBuf)
TfuSrIndInfo *param;
Ptr memCp;
Buffer *mBuf;
#endif
{

   U32 count, loopCnt;
   TfuSrInfo *tfuSrInfo;

   TRC3(cmUnpkTfuSrIndInfo)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteTimingInfo, &param->timingInfo, mBuf);
   cmLListInit(&param->srLst);
   CMCHKUNPK(SUnpkU32, &count, mBuf);
   for (loopCnt=0; loopCnt<count; loopCnt++) {
      cmGetMem((Ptr)memCp, sizeof(*tfuSrInfo), (Ptr *)&tfuSrInfo);
      CMCHKUNPK(cmUnpkTfuSrInfo, tfuSrInfo, mBuf);
      cmLListAdd2Tail(&param->srLst, &tfuSrInfo->lnk);
      tfuSrInfo->lnk.node = (PTR)tfuSrInfo;
   }
   RETVALUE(ROK);
}

/* tfu_c_001.main_7. Added changes of TFU_UPGRADE */
/***********************************************************
*
*     Func : cmPkTfuHqInfo
*
*
*     Desc : This structure contains the HARQ feedback for a single UE. 
  * @details RNTI is present to identify the UE. 
  * For FDD a single feedback is present. 
  * For TDD HARQ multiplexing a list of HARQ feedbacks is present.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuHqInfo
(
TfuHqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuHqInfo(param, mBuf)
TfuHqInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkTfuHqInfo)

   CMCHKPK(SPkU8, param->isPusch, mBuf);
   for (i=TFU_MAX_HARQ_FDBKS-1; i >= 0; i--) {
      CMCHKPK(SPkU32, param->isAck[i], mBuf);
   }
#ifdef TFU_TDD        
   CMCHKPK(SPkU8, param->M, mBuf);
#endif/*TFU_TDD*/
   CMCHKPK(SPkU8, param->noOfTbs, mBuf);
/* ACC-TDD ccpu00130520 */
   CMCHKPK(SPkU32, param->hqFdbkMode, mBuf);
   CMCHKPK(cmPkLteRnti, param->rnti, mBuf);
   RETVALUE(ROK);
}

/* tfu_c_001.main_7. Added changes of TFU_UPGRADE */
/***********************************************************
*
*     Func : cmUnpkTfuHqInfo
*
*
*     Desc : This structure contains the HARQ feedback for a single UE. 
  * @details RNTI is present to identify the UE. 
  * For FDD a single feedback is present. 
  * For TDD HARQ multiplexing a list of HARQ feedbacks is present.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuHqInfo
(
TfuHqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuHqInfo(param, mBuf)
TfuHqInfo *param;
Buffer *mBuf;
#endif
{
   S32 i;
   TRC3(cmUnpkTfuHqInfo)

   CMCHKUNPK(cmUnpkLteRnti, &param->rnti, mBuf);
/* ACC-TDD ccpu00130520 */
   CMCHKUNPK(SUnpkU32, (U32 *)&param->hqFdbkMode, mBuf);
   CMCHKUNPK(SUnpkU8, &param->noOfTbs, mBuf);
#ifdef TFU_TDD
   CMCHKUNPK(SUnpkU8, &param->M, mBuf);
#endif
   for (i=0; i<TFU_MAX_HARQ_FDBKS; i++) {
      CMCHKUNPK(SUnpkU32, (U32 *)&param->isAck[i], mBuf);
   }
   CMCHKUNPK(SUnpkU8, &param->isPusch, mBuf);
   RETVALUE(ROK);
}





/***********************************************************
*
*     Func : cmPkTfuHqIndInfo
*
*
*     Desc : This structure contains a list of HARQ feedback for a number of UEs.
  * @details All the HARQ feedback received in the subframe are clubbed together
  * in this data structure and given to the scheduler for processing.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuHqIndInfo
(
TfuHqIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuHqIndInfo(param, mBuf)
TfuHqIndInfo *param;
Buffer *mBuf;
#endif
{

   CmLList *node;
   U32 count;
   TfuHqInfo *tfuHqInfo;

   TRC3(cmPkTfuHqIndInfo)

   count = param->hqIndLst.count;
   node = param->hqIndLst.last;
   while (node) {
      tfuHqInfo = (TfuHqInfo *)node->node;
      node=node->prev;
      CMCHKPK(cmPkTfuHqInfo, tfuHqInfo, mBuf);
      cmLListDelFrm(&param->hqIndLst, &tfuHqInfo->lnk);
      tfuHqInfo->lnk.node = (PTR)NULLP;
   }
   CMCHKPK(SPkU32, count, mBuf);
   CMCHKPK(cmPkLteTimingInfo, &param->timingInfo, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuHqIndInfo
*
*
*     Desc : This structure contains a list of HARQ feedback for a number of UEs.
  * @details All the HARQ feedback received in the subframe are clubbed together
  * in this data structure and given to the scheduler for processing.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuHqIndInfo
(
TfuHqIndInfo *param,
Ptr memCp,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuHqIndInfo(param, memCp, mBuf)
TfuHqIndInfo *param;
Ptr memCp;
Buffer *mBuf;
#endif
{

   U32 count, loopCnt;
   TfuHqInfo *tfuHqInfo;

   TRC3(cmUnpkTfuHqIndInfo)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteTimingInfo, &param->timingInfo, mBuf);
   cmLListInit(&param->hqIndLst);
   CMCHKUNPK(SUnpkU32, &count, mBuf);
   for (loopCnt=0; loopCnt<count; loopCnt++) {
      cmGetMem((Ptr)memCp, sizeof(*tfuHqInfo), (Ptr *)&tfuHqInfo);
      CMCHKUNPK(cmUnpkTfuHqInfo, tfuHqInfo, mBuf);
      cmLListAdd2Tail(&param->hqIndLst, &tfuHqInfo->lnk);
      tfuHqInfo->lnk.node = (PTR)tfuHqInfo;
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuUlCqiInfo
*
*
*     Desc : This structure conveys the Uplink CQI information for a single subband.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuUlCqiInfo
(
TfuUlCqiInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuUlCqiInfo(param, mBuf)
TfuUlCqiInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuUlCqiInfo)

   CMCHKPK(cmPkTfuSubbandCqiInfo, &param->subbandCqi, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuUlCqiInfo
*
*
*     Desc : This structure conveys the Uplink CQI information for a single subband.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuUlCqiInfo
(
TfuUlCqiInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuUlCqiInfo(param, mBuf)
TfuUlCqiInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuUlCqiInfo)

   CMCHKUNPK(cmUnpkTfuSubbandCqiInfo, &param->subbandCqi, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuUlCqiRpt
*
*
*     Desc : This structure contains the UL CQI estimated by the physical layer. 
  * @details The report could be wideband CQI or subBand CQI or both.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuUlCqiRpt
(
TfuUlCqiRpt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuUlCqiRpt(param, mBuf)
TfuUlCqiRpt *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkTfuUlCqiRpt)

   for (i=TFU_MAX_UL_SUBBAND-1; i >= 0; i--) {
      CMCHKPK(cmPkTfuUlCqiInfo, &param->ulCqiInfoArr[i], mBuf);
   }
   CMCHKPK(SPkU8, param->numSubband, mBuf);
   CMCHKPK(SPkU8, param->wideCqi, mBuf);
   CMCHKPK(SPkU8, param->isTxPort0, mBuf);
   CMCHKPK(cmPkLteRnti, param->rnti, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuUlCqiRpt
*
*
*     Desc : This structure contains the UL CQI estimated by the physical layer. 
  * @details The report could be wideband CQI or subBand CQI or both.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuUlCqiRpt
(
TfuUlCqiRpt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuUlCqiRpt(param, mBuf)
TfuUlCqiRpt *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkTfuUlCqiRpt)

   CMCHKUNPK(cmUnpkLteRnti, &param->rnti, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isTxPort0, mBuf);
   CMCHKUNPK(SUnpkU8, &param->wideCqi, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numSubband, mBuf);
   for (i=0; i<TFU_MAX_UL_SUBBAND; i++) {
      CMCHKUNPK(cmUnpkTfuUlCqiInfo, &param->ulCqiInfoArr[i], mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuUlCqiIndInfo
*
*
*     Desc : This structure conveys the Uplink CQI information.
 * @details Uplink CQI is calculated by the physical layer, and is this
 * information is provided to the scheduler. 
 * This data structure clubs together the UL CQI estimates for all the UEs that
 * have been scheduled in the subframe for uplink transmission.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuUlCqiIndInfo
(
TfuUlCqiIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuUlCqiIndInfo(param, mBuf)
TfuUlCqiIndInfo *param;
Buffer *mBuf;
#endif
{

   CmLList *node;
   U32 count;
   TfuUlCqiRpt *tfuUlCqiRpt;

   TRC3(cmPkTfuUlCqiIndInfo)

   count = param->ulCqiRpt.count;
   node = param->ulCqiRpt.last;
   while (node) {
      tfuUlCqiRpt = (TfuUlCqiRpt *)node->node;
      node=node->prev;
      CMCHKPK(cmPkTfuUlCqiRpt, tfuUlCqiRpt, mBuf);
      cmLListDelFrm(&param->ulCqiRpt, &tfuUlCqiRpt->lnk);
      tfuUlCqiRpt->lnk.node = (PTR)NULLP;
   }
   CMCHKPK(SPkU32, count, mBuf);
   CMCHKPK(cmPkLteTimingInfo, &param->timingInfo, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuUlCqiIndInfo
*
*
*     Desc : This structure conveys the Uplink CQI information.
 * @details Uplink CQI is calculated by the physical layer, and is this
 * information is provided to the scheduler. 
 * This data structure clubs together the UL CQI estimates for all the UEs that
 * have been scheduled in the subframe for uplink transmission.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuUlCqiIndInfo
(
TfuUlCqiIndInfo *param,
Ptr memCp,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuUlCqiIndInfo(param, memCp, mBuf)
TfuUlCqiIndInfo *param;
Ptr memCp;
Buffer *mBuf;
#endif
{

   U32 count, loopCnt;
   TfuUlCqiRpt *tfuUlCqiRpt;

   TRC3(cmUnpkTfuUlCqiIndInfo)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteTimingInfo, &param->timingInfo, mBuf);
   cmLListInit(&param->ulCqiRpt);
   CMCHKUNPK(SUnpkU32, &count, mBuf);
   for (loopCnt=0; loopCnt<count; loopCnt++) {
      cmGetMem((Ptr)memCp, sizeof(*tfuUlCqiRpt), (Ptr *)&tfuUlCqiRpt);
      CMCHKUNPK(cmUnpkTfuUlCqiRpt, tfuUlCqiRpt, mBuf);
      cmLListAdd2Tail(&param->ulCqiRpt, &tfuUlCqiRpt->lnk);
      tfuUlCqiRpt->lnk.node = (PTR)tfuUlCqiRpt;
   }
   RETVALUE(ROK);
}




/***********************************************************
*
*     Func : cmPkTfuDlCqiRpt
*
*
*     Desc : This structure contains the DL CQI report for a single UE. 
  * @details The report could either be reported on PUCCH or PUSCH, a flag
  * conveys this information.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDlCqiRpt
(
TfuDlCqiRpt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDlCqiRpt(param, mBuf)
TfuDlCqiRpt *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuDlCqiRpt)

      if (cmPkTfuDlCqiInfo(param->isPucchInfo, &param->dlCqiInfo, mBuf) != ROK)
         RETVALUE(RFAILED);
   CMCHKPK(SPkU8, param->isPucchInfo, mBuf);
   CMCHKPK(cmPkLteRnti, param->rnti, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDlCqiRpt
*
*
*     Desc : This structure contains the DL CQI report for a single UE. 
  * @details The report could either be reported on PUCCH or PUSCH, a flag
  * conveys this information.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDlCqiRpt
(
TfuDlCqiRpt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDlCqiRpt(param, mBuf)
TfuDlCqiRpt *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuDlCqiRpt)

   CMCHKUNPK(cmUnpkLteRnti, &param->rnti, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isPucchInfo, mBuf);
   if (cmUnpkTfuDlCqiInfo (param->isPucchInfo, &param->dlCqiInfo, mBuf) != ROK)
      RETVALUE(RFAILED);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuDlCqiIndInfo
*
*
*     Desc : This structure contains a list of Downlink CQI reports transmitted by
 * UEs. 
 * @details This structure clubs together DL CQI reports for a number of UEs.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDlCqiIndInfo
(
TfuDlCqiIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDlCqiIndInfo(param, mBuf)
TfuDlCqiIndInfo *param;
Buffer *mBuf;
#endif
{

   CmLList *node;
   U32 count;
   TfuDlCqiRpt *tfuDlCqiRpt;

   TRC3(cmPkTfuDlCqiIndInfo)

   count = param->dlCqiRptsLst.count;
   node = param->dlCqiRptsLst.last;
   while (node) {
      tfuDlCqiRpt = (TfuDlCqiRpt *)node->node;
      node=node->prev;
      CMCHKPK(cmPkTfuDlCqiRpt, tfuDlCqiRpt, mBuf);
      cmLListDelFrm(&param->dlCqiRptsLst, &tfuDlCqiRpt->lnk);
      tfuDlCqiRpt->lnk.node = (PTR)NULLP;
   }
   CMCHKPK(SPkU32, count, mBuf);
   CMCHKPK(cmPkLteTimingInfo, &param->timingInfo, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDlCqiIndInfo
*
*
*     Desc : This structure contains a list of Downlink CQI reports transmitted by
 * UEs. 
 * @details This structure clubs together DL CQI reports for a number of UEs.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDlCqiIndInfo
(
TfuDlCqiIndInfo *param,
Ptr memCp,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDlCqiIndInfo(param, memCp, mBuf)
TfuDlCqiIndInfo *param;
Ptr memCp;
Buffer *mBuf;
#endif
{

   U32 count, loopCnt;
   TfuDlCqiRpt *tfuDlCqiRpt;

   TRC3(cmUnpkTfuDlCqiIndInfo)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteTimingInfo, &param->timingInfo, mBuf);
   cmLListInit(&param->dlCqiRptsLst);
   CMCHKUNPK(SUnpkU32, &count, mBuf);
   for (loopCnt=0; loopCnt<count; loopCnt++) {
      cmGetMem((Ptr)memCp, sizeof(*tfuDlCqiRpt), (Ptr *)&tfuDlCqiRpt);
      CMCHKUNPK(cmUnpkTfuDlCqiRpt, tfuDlCqiRpt, mBuf);
      cmLListAdd2Tail(&param->dlCqiRptsLst, &tfuDlCqiRpt->lnk);
      tfuDlCqiRpt->lnk.node = (PTR)tfuDlCqiRpt;
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuCrcInfo
*
*
*     Desc : This structure contains the CRC indication for a single
  * UE.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuCrcInfo
(
TfuCrcInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuCrcInfo(param, mBuf)
TfuCrcInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuCrcInfo)

   CMCHKPK(cmPkTknU8, &param->rv, mBuf);
   CMCHKPK(SPkU8, param->isFailure, mBuf);
   CMCHKPK(cmPkLteRnti, param->rnti, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuCrcInfo
*
*
*     Desc : This structure contains the CRC indication for a single
  * UE.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuCrcInfo
(
TfuCrcInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuCrcInfo(param, mBuf)
TfuCrcInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuCrcInfo)

   CMCHKUNPK(cmUnpkLteRnti, &param->rnti, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isFailure, mBuf);
   CMCHKUNPK(cmUnpkTknU8, &param->rv, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuCrcIndInfo
*
*
*     Desc : This structure contains information that is passed as a part of the
 * CRC Indication from PHY to MAC.
 * @details This structure clubs together all the CRC indications for
 * a single subframe and conveys this information to the scheduler.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuCrcIndInfo
(
TfuCrcIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuCrcIndInfo(param, mBuf)
TfuCrcIndInfo *param;
Buffer *mBuf;
#endif
{

   CmLList *node;
   U32 count;
   TfuCrcInfo *tfuCrcIndInfo;

   TRC3(cmPkTfuCrcIndInfo)

   count = param->crcLst.count;
   node = param->crcLst.last;
   while (node) {
      tfuCrcIndInfo = (TfuCrcInfo *)node->node;
      node=node->prev;
      CMCHKPK(cmPkTfuCrcInfo, tfuCrcIndInfo, mBuf);
      cmLListDelFrm(&param->crcLst, &tfuCrcIndInfo->lnk);
      tfuCrcIndInfo->lnk.node = (PTR)NULLP;
   }
   CMCHKPK(SPkU32, count, mBuf);
   CMCHKPK(cmPkLteTimingInfo, &param->timingInfo, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuCrcIndInfo
*
*
*     Desc : This structure contains information that is passed as a part of the
 * CRC Indication from PHY to MAC.
 * @details This structure clubs together all the CRC indications for
 * a single subframe and conveys this information to the scheduler.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuCrcIndInfo
(
TfuCrcIndInfo *param,
Ptr memCp,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuCrcIndInfo(param, memCp, mBuf)
TfuCrcIndInfo *param;
Ptr memCp;
Buffer *mBuf;
#endif
{

   U32 count, loopCnt;
   TfuCrcInfo *tfuCrcIndInfo;

   TRC3(cmUnpkTfuCrcIndInfo)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteTimingInfo, &param->timingInfo, mBuf);
   cmLListInit(&param->crcLst);
   CMCHKUNPK(SUnpkU32, &count, mBuf);
   for (loopCnt=0; loopCnt<count; loopCnt++) {
      cmGetMem((Ptr)memCp, sizeof(*tfuCrcIndInfo), (Ptr *)&tfuCrcIndInfo);
      CMCHKUNPK(cmUnpkTfuCrcInfo, tfuCrcIndInfo, mBuf);
      cmLListAdd2Tail(&param->crcLst, &tfuCrcIndInfo->lnk);
      tfuCrcIndInfo->lnk.node = (PTR)tfuCrcIndInfo;
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuTimingAdvInfo
*
*
*     Desc : This structure contains the timing advance information for a single
  * UE.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuTimingAdvInfo
(
TfuTimingAdvInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuTimingAdvInfo(param, mBuf)
TfuTimingAdvInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuTimingAdvInfo)

   CMCHKPK(SPkU8, param->timingAdv, mBuf);
   CMCHKPK(cmPkLteRnti, param->rnti, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuTimingAdvInfo
*
*
*     Desc : This structure contains the timing advance information for a single
  * UE.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuTimingAdvInfo
(
TfuTimingAdvInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuTimingAdvInfo(param, mBuf)
TfuTimingAdvInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuTimingAdvInfo)

   CMCHKUNPK(cmUnpkLteRnti, &param->rnti, mBuf);
   CMCHKUNPK(SUnpkU8, &param->timingAdv, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuTimingAdvIndInfo
*
*
*     Desc : This structure contains information that is passed as part of the Timing
 * Advance indication from PHY to MAC.
 * @details This structure clubs together timing advances for a number of UEs.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuTimingAdvIndInfo
(
TfuTimingAdvIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuTimingAdvIndInfo(param, mBuf)
TfuTimingAdvIndInfo *param;
Buffer *mBuf;
#endif
{

   CmLList *node;
   U32 count;
   TfuTimingAdvInfo *tfuTimingAdvInfo;

   TRC3(cmPkTfuTimingAdvIndInfo)

   count = param->timingAdvLst.count;
   node = param->timingAdvLst.last;
   while (node) {
      tfuTimingAdvInfo = (TfuTimingAdvInfo *)node->node;
      node=node->prev;
      CMCHKPK(cmPkTfuTimingAdvInfo, tfuTimingAdvInfo, mBuf);
      cmLListDelFrm(&param->timingAdvLst, &tfuTimingAdvInfo->lnk);
      tfuTimingAdvInfo->lnk.node = (PTR)NULLP;
   }
   CMCHKPK(SPkU32, count, mBuf);
   CMCHKPK(cmPkLteTimingInfo, &param->timingInfo, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuTimingAdvIndInfo
*
*
*     Desc : This structure contains information that is passed as part of the Timing
 * Advance indication from PHY to MAC.
 * @details This structure clubs together timing advances for a number of UEs.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuTimingAdvIndInfo
(
TfuTimingAdvIndInfo *param,
Ptr memCp,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuTimingAdvIndInfo(param, memCp, mBuf)
TfuTimingAdvIndInfo *param;
Ptr memCp;
Buffer *mBuf;
#endif
{

   U32 count, loopCnt;
   TfuTimingAdvInfo *tfuTimingAdvInfo;

   TRC3(cmUnpkTfuTimingAdvIndInfo)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteTimingInfo, &param->timingInfo, mBuf);
   cmLListInit(&param->timingAdvLst);
   CMCHKUNPK(SUnpkU32, &count, mBuf);
   for (loopCnt=0; loopCnt<count; loopCnt++) {
      cmGetMem((Ptr)memCp, sizeof(*tfuTimingAdvInfo), (Ptr *)&tfuTimingAdvInfo);
      CMCHKUNPK(cmUnpkTfuTimingAdvInfo, tfuTimingAdvInfo, mBuf);
      cmLListAdd2Tail(&param->timingAdvLst, &tfuTimingAdvInfo->lnk);
      tfuTimingAdvInfo->lnk.node = (PTR)tfuTimingAdvInfo;
   }
   RETVALUE(ROK);
}

/*CA dev Start*/
/***********************************************************
*
*     Func : cmPkTfuTtiCellInfo
*
*
*     Desc : This structure contains information that is 
*     passed as a part of the TTI indication sent 
*     from CL to MAC and SCH
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuTtiCellInfo
(
TfuTtiCellInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuTtiCellInfo(param, mBuf)
TfuTtiCellInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuTtiCellInfo)

   CMCHKPK(SPkU8, param->ulBlankSf, mBuf);
   CMCHKPK(SPkU8, param->dlBlankSf, mBuf);
   CMCHKPK(SPkU8, param->schTickDelta, mBuf);
   CMCHKPK(cmPkBool, param->isDummyTti, mBuf);
   CMCHKPK(cmPkLteTimingInfo, &param->timingInfo, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}
/*CA dev End*/

/***********************************************************
*
*     Func : cmPkTfuTtiIndInfo
*
*
*     Desc : This structure contains information that is passed as a part of the TTI
 * indication sent from PHY to MAC.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuTtiIndInfo
(
TfuTtiIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuTtiIndInfo(param, mBuf)
TfuTtiIndInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkTfuTtiIndInfo)

   /*CA dev Start*/
   for (i=(param->numCells-1); i >= 0; i--) {
         CMCHKPK(cmPkTfuTtiCellInfo, &param->cells[i], mBuf);
      }
   CMCHKPK(SPkU8, param->numCells, mBuf);
   /*CA dev End*/
   RETVALUE(ROK);
}

/* CA dev Start */
/***********************************************************
*
*     Func : cmUnpkTfuTtiCellInfo
*
*
*     Desc : This structure contains information that is 
*     passed as a part of the TTI indication sent 
*     from CL to MAC and SCH
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuTtiCellInfo
(
TfuTtiCellInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuTtiCellInfo(param, mBuf)
TfuTtiCellInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuTtiCellInfo)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteTimingInfo, &param->timingInfo, mBuf);
   CMCHKUNPK(cmUnpkBool, &param->isDummyTti, mBuf);
   CMCHKUNPK(SUnpkU8, &param->schTickDelta, mBuf);
   CMCHKUNPK(SUnpkU8, &param->dlBlankSf, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ulBlankSf, mBuf);
   RETVALUE(ROK);
}
/* CA dev End */


/***********************************************************
*
*     Func : cmUnpkTfuTtiIndInfo
*
*
*     Desc : This structure contains information that is passed as a part of the TTI
 * indication sent from PHY to MAC.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuTtiIndInfo
(
TfuTtiIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuTtiIndInfo(param, mBuf)
TfuTtiIndInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkTfuTtiIndInfo)

   /* CA dev Start */
   CMCHKUNPK(SUnpkU8, &param->numCells, mBuf);
   for (i=0; i<(param->numCells); i++) {
      CMCHKUNPK(cmUnpkTfuTtiCellInfo, &param->cells[i], mBuf);
   }
   /* CA dev End */
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuRaReqInfo
*
*
*     Desc : This structure contains the information for a single Random Access Request.
 * @details The information present in this structure is for a single preamble.
 * Associated with each preamble are fields that the physical layer calculates
 * based on the reception of the Random Access Request. These are the following
 * -# Timing Advance
 * -# TPC
 * -# CQI (optional).
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuRaReqInfo
(
TfuRaReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuRaReqInfo(param, mBuf)
TfuRaReqInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuRaReqInfo)

   CMCHKPK(SPkU8, param->cqiIdx, mBuf);
   CMCHKPK(SPkU8, param->cqiPres, mBuf);
   CMCHKPK(SPkU8, param->tpc, mBuf);
   CMCHKPK(SPkU16, param->ta, mBuf);
   CMCHKPK(SPkU8, param->rapId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuRaReqInfo
*
*
*     Desc : This structure contains the information for a single Random Access Request.
 * @details The information present in this structure is for a single preamble.
 * Associated with each preamble are fields that the physical layer calculates
 * based on the reception of the Random Access Request. These are the following
 * -# Timing Advance
 * -# TPC
 * -# CQI (optional).
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuRaReqInfo
(
TfuRaReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuRaReqInfo(param, mBuf)
TfuRaReqInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuRaReqInfo)

   CMCHKUNPK(SUnpkU8, &param->rapId, mBuf);
   CMCHKUNPK(SUnpkU16, &param->ta, mBuf);
   CMCHKUNPK(SUnpkU8, &param->tpc, mBuf);
   CMCHKUNPK(SUnpkU8, &param->cqiPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->cqiIdx, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuRachInfo
*
*
*     Desc : This structure contains RACH request information for a single
  * RA-RNTI.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuRachInfo
(
 CmMemListCp   memCp,
TfuRachInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuRachInfo(memCp, param, mBuf)
 CmMemListCp   memCp;
TfuRachInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkTfuRachInfo)

   for (i= (param->numRaReqInfo - 1); i >= 0; i--) {
      CMCHKPK(cmPkTfuRaReqInfo, &(param->raReqInfoArr[i]), mBuf);
   }
   CMCHKPK(SPkU8, param->numRaReqInfo, mBuf);
   CMCHKPK(cmPkLteRnti, param->raRnti, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuRachInfo
*
*
*     Desc : This structure contains RACH request information for a single
  * RA-RNTI.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuRachInfo
(
CmMemListCp   memCp,
TfuRachInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuRachInfo(memCp, param, mBuf)
CmMemListCp   memCp;
TfuRachInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkTfuRachInfo)

   CMCHKUNPK(cmUnpkLteRnti, &param->raRnti, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numRaReqInfo, mBuf);
   if (cmGetMem (&(memCp), (sizeof(TfuRaReqInfo) * param->numRaReqInfo), 
            (Ptr *)&param->raReqInfoArr) != ROK)
   {
      RETVALUE(RFAILED);
   }
   for (i=0; i<param->numRaReqInfo; i++) {
      CMCHKUNPK(cmUnpkTfuRaReqInfo, &param->raReqInfoArr[i], mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuRaReqIndInfo
*
*
*     Desc : This structure contains the list of Random Access Requests received in a
 * single TTI.
 * @details Random Access Request is associated with a RA-RNTI, which remains
 * common for all the Random access requests within a subframe. This structure
 * thus carries the RA-RNTI and a list of Random Access Request information.
 * This information consists of the following 
 * -# preamble-id - this corresponds to the Index of the Preamble choosen by the
 * UE.
 * -# Timing Advance - this corresponds to the timing adjustment that the UE
 * needs to be uplink synchronized. This value is calculated by physical layer. 
 * -# tpc - this is the power control command that the physical layer calculates
 * from the received RA request. This value is transmitted in the RA Response
 * sent out by MAC.
 * -# CQI - this is the Channel quality index of the UL channel estimated by the
 * physical layer. This aids MAC in the scheduling of this UE.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuRaReqIndInfo
(
TfuRaReqIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuRaReqIndInfo(param, mBuf)
TfuRaReqIndInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkTfuRaReqIndInfo)

   for (i= (param->nmbOfRaRnti-1); i >= 0; i--) 
   {
      if (ROK != cmPkTfuRachInfo(param->memCp, 
               &(param->rachInfoArr[i]), mBuf))
      {
         RETVALUE(RFAILED);
      }
   }
   CMCHKPK(SPkU8, param->nmbOfRaRnti, mBuf);
   CMCHKPK(cmPkLteTimingInfo, &param->timingInfo, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuRaReqIndInfo
*
*
*     Desc : This structure contains the list of Random Access Requests received in a
 * single TTI.
 * @details Random Access Request is associated with a RA-RNTI, which remains
 * common for all the Random access requests within a subframe. This structure
 * thus carries the RA-RNTI and a list of Random Access Request information.
 * This information consists of the following 
 * -# preamble-id - this corresponds to the Index of the Preamble choosen by the
 * UE.
 * -# Timing Advance - this corresponds to the timing adjustment that the UE
 * needs to be uplink synchronized. This value is calculated by physical layer. 
 * -# tpc - this is the power control command that the physical layer calculates
 * from the received RA request. This value is transmitted in the RA Response
 * sent out by MAC.
 * -# CQI - this is the Channel quality index of the UL channel estimated by the
 * physical layer. This aids MAC in the scheduling of this UE.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuRaReqIndInfo
(
TfuRaReqIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuRaReqIndInfo(param, mBuf)
TfuRaReqIndInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkTfuRaReqIndInfo)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteTimingInfo, &param->timingInfo, mBuf);
   CMCHKUNPK(SUnpkU8, &param->nmbOfRaRnti, mBuf);
   if (cmGetMem (&(param->memCp), (sizeof(TfuRachInfo) * param->nmbOfRaRnti), 
            (Ptr *)&param->rachInfoArr) != ROK)
   {
      RETVALUE(RFAILED);
   }
   for (i=0; i<param->nmbOfRaRnti; i++) 
   {
      if (ROK != cmUnpkTfuRachInfo(param->memCp, &param->rachInfoArr[i], mBuf))
      {
         RETVALUE(RFAILED);
      }
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuPucchDeltaPwr
*
*
*     Desc : This structure contains PUCCH Delta power for a single UE.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuPucchDeltaPwrInfo
(
TfuPucchDeltaPwr *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuPucchDeltaPwrInfo(param, mBuf)
TfuPucchDeltaPwr *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuPucchDeltaPwrInfo)

   CMCHKPK(SPkS8, param->pucchDeltaPwr, mBuf);
   CMCHKPK(cmPkLteRnti, param->rnti, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuPucchDeltaPwr
*
*
*     Desc : This structure contains PUCCH Delta power for a single UE.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuPucchDeltaPwrInfo
(
TfuPucchDeltaPwr *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuPucchDeltaPwrInfo(param, mBuf)
TfuPucchDeltaPwr *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuPucchDeltaPwrInfo)

   CMCHKUNPK(cmUnpkLteRnti, &param->rnti, mBuf);
   CMCHKUNPK(SUnpkS8, &param->pucchDeltaPwr, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuPucchDeltaPwrIndInfo
*
*
*     Desc : This structure contains information that is passed as a part of the
 * PUCCH Delta power indication from PHY to SCH.
 * @details This structure clubs together PUCCH Delta power values for a number
 * of UEs.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuPucchDeltaPwrIndInfo
(
TfuPucchDeltaPwrIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuPucchDeltaPwrIndInfo(param, mBuf)
TfuPucchDeltaPwrIndInfo *param;
Buffer *mBuf;
#endif
{

   CmLList *node;
   U32 count;
   TfuPucchDeltaPwr *tfuPucchDeltaPwr;

   TRC3(cmPkTfuPucchDeltaPwrIndInfo)

   count = param->pucchDeltaPwrLst.count;
   node = param->pucchDeltaPwrLst.last;
   while (node) {
      tfuPucchDeltaPwr = (TfuPucchDeltaPwr *)node->node;
      node=node->prev;
      CMCHKPK(cmPkTfuPucchDeltaPwrInfo, tfuPucchDeltaPwr, mBuf);
      cmLListDelFrm(&param->pucchDeltaPwrLst, &tfuPucchDeltaPwr->lnk);
      tfuPucchDeltaPwr->lnk.node = (PTR)NULLP;
   }
   CMCHKPK(SPkU32, count, mBuf);
   CMCHKPK(cmPkLteTimingInfo, &param->timingInfo, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuPucchDeltaPwrIndInfo
*
*
*     Desc : This structure contains information that is passed as a part of the
 * PUCCH Delta power indication from PHY to SCH.
 * @details This structure clubs together PUCCH Delta power values for a number
 * of UEs.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuPucchDeltaPwrIndInfo
(
TfuPucchDeltaPwrIndInfo *param,
Ptr memCp,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuPucchDeltaPwrIndInfo(param, memCp, mBuf)
TfuPucchDeltaPwrIndInfo *param;
Ptr memCp;
Buffer *mBuf;
#endif
{

   U32 count, loopCnt;
   TfuPucchDeltaPwr *tfuPucchDeltaPwr;

   TRC3(cmUnpkTfuPucchDeltaPwrIndInfo)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteTimingInfo, &param->timingInfo, mBuf);
   cmLListInit(&param->pucchDeltaPwrLst);
   CMCHKUNPK(SUnpkU32, &count, mBuf);
   for (loopCnt=0; loopCnt<count; loopCnt++) {
      cmGetMem((Ptr)memCp, sizeof(*tfuPucchDeltaPwr), (Ptr *)&tfuPucchDeltaPwr);
      CMCHKUNPK(cmUnpkTfuPucchDeltaPwrInfo, tfuPucchDeltaPwr, mBuf);
      cmLListAdd2Tail(&param->pucchDeltaPwrLst, &tfuPucchDeltaPwr->lnk);
      tfuPucchDeltaPwr->lnk.node = (PTR)tfuPucchDeltaPwr;
   }
   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 cmPkBuffer
(
Buffer **param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkBuffer(param, mBuf)
Buffer **param;
Buffer *mBuf;
#endif
{
   MsgLen msgLen=0;
   TRC3(cmPkBuffer)
   if (SFndLenMsg(*param, &msgLen) != ROK)
      RETVALUE(RFAILED);
   if (SCatMsg(mBuf, *param, M1M2) != ROK)
      RETVALUE(RFAILED);
   TFU_FREE_MSG(*param);
   *param = NULLP;
   CMCHKPK(cmPkMsgLen, msgLen, mBuf);
   RETVALUE(ROK);
}
#ifdef ANSI
PUBLIC S16 cmUnpkBuffer
(
Buffer **param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkBuffer(param, mBuf)
Buffer **param;
Buffer *mBuf;
#endif
{
   MsgLen msgLen=0, totalMsgLen=0;
   TRC3(cmUnpkBuffer)
   CMCHKUNPK(cmUnpkMsgLen, &msgLen, mBuf);
   if (SFndLenMsg(mBuf, &totalMsgLen) != ROK)
      RETVALUE(RFAILED);
   if (SSegMsg(mBuf, totalMsgLen-msgLen, param) != ROK)
      RETVALUE(RFAILED);
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkTfuDoaInd
*
*
*     Desc : This API is used to indicate DOA(Direction Of Arrival)
 * identifier for one or more UEs.
 * It carries a DOA for each UE. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param doaInd Pointer to the TfuDoaIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDoaInd
(
Pst * pst,
SuId suId,
TfuDoaIndInfo * doaInd
)
#else
PUBLIC S16 cmPkTfuDoaInd(pst, suId, doaInd)
Pst * pst;
SuId suId;
TfuDoaIndInfo * doaInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTfuDoaInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU125, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)doaInd, sizeof(TfuDoaIndInfo));
      RETVALUE(RFAILED);
   }
      cmPkTfuDoaIndInfo(doaInd, mBuf);
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU126, (ErrVal)0, "Packing failed");
#endif
      TFU_FREE_MEM(doaInd);
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   TFU_FREE_MEM(doaInd);
   pst->event = (Event) EVTTFUDOAIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkTfuDoaInd
*
*
*     Desc : This API is used to indicate DOA(Direction Of Arrival)
 * identifier for one or more UEs.
 * It carries a DOA for each UE. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param doaInd Pointer to the TfuDoaIndInfo structure.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDoaInd
(
TfuDoaInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDoaInd(func, pst, mBuf)
TfuDoaInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   TfuDoaIndInfo *doaInd;
   
   TRC3(cmUnpkTfuDoaInd)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU127, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   {
      Mem   sMem;
      sMem.region = pst->region;
      sMem.pool = pst->pool;
      if ((cmAllocEvnt(sizeof(TfuDoaIndInfo), TFU_BLKSZ, &sMem, (Ptr *)&doaInd)) != ROK)            {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU128, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   
      cmUnpkTfuDoaIndInfo(doaInd, (Ptr)&doaInd->memCp, mBuf);
   TFU_FREE_MSG(mBuf);
   RETVALUE((*func)(pst, suId, doaInd));
}



/***********************************************************
*
*     Func : cmPkTfuDciFormatTbInfo
*
*
*     Desc : This structure contains the TB level DCI signalling
  * parameters in case of DCI formats 2 and 2A
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDciFormatTbInfo
(
TfuDciFormatTbInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDciFormatTbInfo(param, mBuf)
TfuDciFormatTbInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuDciFormatTbInfo)

   CMCHKPK(SPkU8, param->mcs, mBuf);
   CMCHKPK(SPkU8, param->rv, mBuf);
   CMCHKPK(SPkU8, param->ndi, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDciFormatTbInfo
*
*
*     Desc : This structure contains the TB level DCI signalling
  * parameters in case of DCI formats 2 and 2A
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDciFormatTbInfo
(
TfuDciFormatTbInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDciFormatTbInfo(param, mBuf)
TfuDciFormatTbInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuDciFormatTbInfo)

   CMCHKUNPK(SUnpkU8, &param->ndi, mBuf);
   CMCHKUNPK(SUnpkU8, &param->rv, mBuf);
   CMCHKUNPK(SUnpkU8, &param->mcs, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuSubbandDlCqiInfo
*
*
*     Desc : This structure is used to convey the subbannd CQI reported.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuSubbandDlCqiInfo
(
TfuSubbandDlCqiInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuSubbandDlCqiInfo(param, mBuf)
TfuSubbandDlCqiInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkTfuSubbandDlCqiInfo)

   for (i=TFU_MAX_TB-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->cqiIdx[i], mBuf);
   }
   CMCHKPK(cmPkTfuSubbandInfo, &param->subband, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuSubbandDlCqiInfo
*
*
*     Desc : This structure is used to convey the subbannd CQI reported.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuSubbandDlCqiInfo
(
TfuSubbandDlCqiInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuSubbandDlCqiInfo(param, mBuf)
TfuSubbandDlCqiInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkTfuSubbandDlCqiInfo)

   CMCHKUNPK(cmUnpkTfuSubbandInfo, &param->subband, mBuf);
   for (i=0; i<TFU_MAX_TB; i++) {
      CMCHKUNPK(SUnpkU8, &param->cqiIdx[i], mBuf);
   }
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmPkTfuDlCqiPuschInfo
*
*
*     Desc : This structure conveys explicitly the PMI information in case
 *  of PUSCH feedback usage in scheduling. Applicable for TM 4,5,6.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDlCqiPuschInfo
(
TfuDlCqiPuschInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDlCqiPuschInfo(param, mBuf)
TfuDlCqiPuschInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuDlCqiPuschInfo)

      switch(param->mode) {
         case TFU_PUSCH_CQI_MODE_31:
            CMCHKPK(cmPkTfuCqiPuschMode31, &param->u.mode31Info, mBuf);
            break;
         case TFU_PUSCH_CQI_MODE_22:
            CMCHKPK(cmPkTfuCqiPuschMode22, &param->u.mode22Info, mBuf);
            break;
         case TFU_PUSCH_CQI_MODE_12:
            CMCHKPK(cmPkTfuCqiPuschMode12, &param->u.mode12Info, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(SPkU32, param->mode, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDlCqiPuschInfo
*
*
*     Desc : This structure conveys explicitly the PMI information in case
 *  of PUSCH feedback usage in scheduling. Applicable for TM 4,5,6.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDlCqiPuschInfo
(
TfuDlCqiPuschInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDlCqiPuschInfo(param, mBuf)
TfuDlCqiPuschInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuDlCqiPuschInfo)

   CMCHKUNPK(SUnpkU32, (U32 *)&param->mode, mBuf);
      switch(param->mode) {
         case TFU_PUSCH_CQI_MODE_12:
            CMCHKUNPK(cmUnpkTfuCqiPuschMode12, &param->u.mode12Info, mBuf);
            break;
         case TFU_PUSCH_CQI_MODE_22:
            CMCHKUNPK(cmUnpkTfuCqiPuschMode22, &param->u.mode22Info, mBuf);
            break;
         case TFU_PUSCH_CQI_MODE_31:
            CMCHKUNPK(cmUnpkTfuCqiPuschMode31, &param->u.mode31Info, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmPkTfuDoaRpt
*
*
*     Desc : This structure contains the DOA estimated by the physical layer. 
  * @details DOA for a given UE.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDoaRpt
(
TfuDoaRpt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDoaRpt(param, mBuf)
TfuDoaRpt *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuDoaRpt)

   CMCHKPK(SPkU32, param->doa, mBuf);
   CMCHKPK(cmPkLteRnti, param->rnti, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDoaRpt
*
*
*     Desc : This structure contains the DOA estimated by the physical layer. 
  * @details DOA for a given UE.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDoaRpt
(
TfuDoaRpt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDoaRpt(param, mBuf)
TfuDoaRpt *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuDoaRpt)

   CMCHKUNPK(cmUnpkLteRnti, &param->rnti, mBuf);
   CMCHKUNPK(SUnpkU32, &param->doa, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuDoaIndInfo
*
*
*     Desc : This structure conveys the DOA(Direction Of Arrival) indicator.
 * @details DOA is calculated by the physical layer, and this
 * information is provided to the scheduler. 
 * This data structure clubs together the DOAs for all the UEs
 * calculated by PHY in this subframe.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuDoaIndInfo
(
TfuDoaIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuDoaIndInfo(param, mBuf)
TfuDoaIndInfo *param;
Buffer *mBuf;
#endif
{

   CmLList *node;
   U32 count;
   TfuDoaRpt *tfuDoaRpt;
   TRC3(cmPkTfuDoaIndInfo)

   count = param->doaRpt.count;
   node = param->doaRpt.last;
   while (node) {
      tfuDoaRpt = (TfuDoaRpt *)node->node;
      node=node->prev;
      CMCHKPK(cmPkTfuDoaRpt, tfuDoaRpt, mBuf);
      cmLListDelFrm(&param->doaRpt, &tfuDoaRpt->lnk);
      tfuDoaRpt->lnk.node = (PTR)NULLP;
   }
   CMCHKPK(SPkU32, count, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuDoaIndInfo
*
*
*     Desc : This structure conveys the DOA(Direction Of Arrival) indicator.
 * @details DOA is calculated by the physical layer, and this
 * information is provided to the scheduler. 
 * This data structure clubs together the DOAs for all the UEs
 * calculated by PHY in this subframe.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuDoaIndInfo
(
TfuDoaIndInfo *param,
Ptr memCp,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuDoaIndInfo(param, memCp, mBuf)
TfuDoaIndInfo *param;
Ptr memCp;
Buffer *mBuf;
#endif
{

   U32 count, loopCnt;
   TfuDoaRpt *tfuDoaRpt;
   TRC3(cmUnpkTfuDoaIndInfo)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   cmLListInit(&param->doaRpt);
   CMCHKUNPK(SUnpkU32, &count, mBuf);
   for (loopCnt=0; loopCnt<count; loopCnt++) {
      cmGetMem((Ptr)memCp, sizeof(*tfuDoaRpt), (Ptr *)&tfuDoaRpt);
      CMCHKUNPK(cmUnpkTfuDoaRpt, tfuDoaRpt, mBuf);
      cmLListAdd2Tail(&param->doaRpt, &tfuDoaRpt->lnk);
      tfuDoaRpt->lnk.node = (PTR)tfuDoaRpt;
   }
   RETVALUE(ROK);
}


/* tfu_c_001.main_7. Added changes of TFU_UPGRADE */
#ifdef TFU_UPGRADE


/***********************************************************
*
*     Func : cmPkTfuSrsRpt
*
*
*     Desc : This structure conveys the Uplink SRS indication of a UE.
 * @details Uplink SRS from each UE is received by the physical layer, and this
 * information is provided to the scheduler.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuSrsRpt
(
TfuSrsRpt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuSrsRpt(param, mBuf)
TfuSrsRpt *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkTfuSrsRpt)

   CMCHKPK(SPkU8, param->wideCqi, mBuf);
   CMCHKPK(SPkU8, param->wideCqiPres, mBuf);
   for (i=TFU_MAX_UL_RB-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->snr[i], mBuf);
   }
   CMCHKPK(SPkU8, param->rbStart, mBuf);
   CMCHKPK(SPkU8, param->numRbs, mBuf);
   CMCHKPK(SPkU16, param->ta, mBuf);
   CMCHKPK(SPkU16, param->dopEst, mBuf);
   CMCHKPK(cmPkLteRnti, param->ueId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuSrsRpt
*
*
*     Desc : This structure conveys the Uplink SRS indication of a UE.
 * @details Uplink SRS from each UE is received by the physical layer, and this
 * information is provided to the scheduler.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuSrsRpt
(
TfuSrsRpt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuSrsRpt(param, mBuf)
TfuSrsRpt *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkTfuSrsRpt)

   CMCHKUNPK(cmUnpkLteRnti, &param->ueId, mBuf);
   CMCHKUNPK(SUnpkU16, &param->dopEst, mBuf);
   CMCHKUNPK(SUnpkU16, &param->ta, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numRbs, mBuf);
   CMCHKUNPK(SUnpkU8, &param->rbStart, mBuf);
   for (i=0; i<TFU_MAX_UL_RB; i++) {
      CMCHKUNPK(SUnpkU8, &param->snr[i], mBuf);
   }
   CMCHKUNPK(SUnpkU8, &param->wideCqiPres, mBuf);
   CMCHKUNPK(SUnpkU8, &param->wideCqi, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuSrsIndInfo
*
*
*     Desc : This structure conveys the Uplink SRS indication.
 * @details Uplink SRS is received by the physical layer, and this
 * information is provided to the scheduler. 
 * This data structure clubs together the UL SRS indications of all the UEs 
 * in the subframe.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuSrsIndInfo
(
TfuSrsIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuSrsIndInfo(param, mBuf)
TfuSrsIndInfo *param;
Buffer *mBuf;
#endif
{

   CmLList *node;
   U32 count;
   TfuSrsRpt *tfuSrsRpt;

   TRC3(cmPkTfuSrsIndInfo)

   count = param->srsRpt.count;
   node = param->srsRpt.last;
   while (node) {
      tfuSrsRpt = (TfuSrsRpt *)node->node;
      node=node->prev;
      CMCHKPK(cmPkTfuSrsRpt, tfuSrsRpt, mBuf);
      cmLListDelFrm(&param->srsRpt, &tfuSrsRpt->lnk);
      tfuSrsRpt->lnk.node = (PTR)NULLP;
   }
   CMCHKPK(SPkU32, count, mBuf);
   CMCHKPK(cmPkLteTimingInfo, &param->timingInfo, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuSrsIndInfo
*
*
*     Desc : This structure conveys the Uplink SRS indication.
 * @details Uplink SRS is received by the physical layer, and this
 * information is provided to the scheduler. 
 * This data structure clubs together the UL SRS indications of all the UEs 
 * in the subframe.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuSrsIndInfo
(
TfuSrsIndInfo *param,
Ptr memCp,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuSrsIndInfo(param, memCp, mBuf)
TfuSrsIndInfo *param;
Ptr memCp;
Buffer *mBuf;
#endif
{

   U32 count, loopCnt;
   TfuSrsRpt *tfuSrsRpt;

   TRC3(cmUnpkTfuSrsIndInfo)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteTimingInfo, &param->timingInfo, mBuf);
   cmLListInit(&param->srsRpt);
   CMCHKUNPK(SUnpkU32, &count, mBuf);
   for (loopCnt=0; loopCnt<count; loopCnt++) {
      cmGetMem((Ptr)memCp, sizeof(*tfuSrsRpt), (Ptr *)&tfuSrsRpt);
      CMCHKUNPK(cmUnpkTfuSrsRpt, tfuSrsRpt, mBuf);
      cmLListAdd2Tail(&param->srsRpt, &tfuSrsRpt->lnk);
      tfuSrsRpt->lnk.node = (PTR)tfuSrsRpt;
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuRawCqiRpt
*
*
*     Desc : This structure contains the Raw CQI information i.e. the CQI report
 * as transmitted by the UE. 
 * @details These bits shall be interpretted by MAC to derive the following 
 * -# Wideband CQI
 * -# Subband CQI
 * -# PMI
 * -# RI
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuRawCqiRpt
(
TfuRawCqiRpt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuRawCqiRpt(param, mBuf)
TfuRawCqiRpt *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkTfuRawCqiRpt)
   for (i=CM_LTE_MAX_CELLS-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->ri[i], mBuf);
   }
   for (i=TFU_MAX_CQI_BYTES-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->cqiBits[i], mBuf);
   }
   CMCHKPK(SPkU8, param->numBits, mBuf);
   CMCHKPK(cmPkLteRnti, param->crnti, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuRawCqiRpt
*
*
*     Desc : This structure contains the Raw CQI information i.e. the CQI report
 * as transmitted by the UE. 
 * @details These bits shall be interpretted by MAC to derive the following 
 * -# Wideband CQI
 * -# Subband CQI
 * -# PMI
 * -# RI
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuRawCqiRpt
(
TfuRawCqiRpt *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuRawCqiRpt(param, mBuf)
TfuRawCqiRpt *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkTfuRawCqiRpt)

   CMCHKUNPK(cmUnpkLteRnti, &param->crnti, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numBits, mBuf);
   for (i=0; i<TFU_MAX_CQI_BYTES; i++) {
      CMCHKUNPK(SUnpkU8, &param->cqiBits[i], mBuf);
   }
   for (i=0; i<CM_LTE_MAX_CELLS; i++) {
      CMCHKUNPK(SUnpkU8, &param->ri[i], mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuRawCqiIndInfo
*
*
*     Desc : This structure contains the Raw CQI reports received for the
 * transmitting UEs in a single subframe. 
 * @details Raw CQI corresponds to the actual bits transmitted by the UE, whose
 * interpretation is upto the MAC layer.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuRawCqiIndInfo
(
TfuRawCqiIndInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuRawCqiIndInfo(param, mBuf)
TfuRawCqiIndInfo *param;
Buffer *mBuf;
#endif
{

   U32 count;
   TfuRawCqiRpt *tfuRawCqiRpt;
   CmLList *node;

   TRC3(cmPkTfuRawCqiIndInfo)

   count = param->rawCqiRpt.count;
   node = param->rawCqiRpt.last;
   while (node) {
      tfuRawCqiRpt = (TfuRawCqiRpt *)node->node;
      node=node->prev;
      CMCHKPK(cmPkTfuRawCqiRpt, tfuRawCqiRpt, mBuf);
      cmLListDelFrm(&param->rawCqiRpt, &tfuRawCqiRpt->lnk);
      tfuRawCqiRpt->lnk.node = (PTR)NULLP;
   }
   CMCHKPK(SPkU32, count, mBuf);
   CMCHKPK(cmPkLteTimingInfo, &param->timingInfo, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuRawCqiIndInfo
*
*
*     Desc : This structure contains the Raw CQI reports received for the
 * transmitting UEs in a single subframe. 
 * @details Raw CQI corresponds to the actual bits transmitted by the UE, whose
 * interpretation is upto the MAC layer.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuRawCqiIndInfo
(
TfuRawCqiIndInfo *param,
Ptr memCp,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuRawCqiIndInfo(param, memCp, mBuf)
TfuRawCqiIndInfo *param;
Ptr memCp;
Buffer *mBuf;
#endif
{

   U32 count, loopCnt;
   TfuRawCqiRpt *tfuRawCqiRpt;

   TRC3(cmUnpkTfuRawCqiIndInfo)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteTimingInfo, &param->timingInfo, mBuf);
   cmLListInit(&param->rawCqiRpt);
   CMCHKUNPK(SUnpkU32, &count, mBuf);
   for (loopCnt=0; loopCnt<count; loopCnt++) {
      cmGetMem((Ptr)memCp, sizeof(*tfuRawCqiRpt), (Ptr *)&tfuRawCqiRpt);
      CMCHKUNPK(cmUnpkTfuRawCqiRpt, tfuRawCqiRpt, mBuf);
      cmLListAdd2Tail(&param->rawCqiRpt, &tfuRawCqiRpt->lnk);
      tfuRawCqiRpt->lnk.node = (PTR)tfuRawCqiRpt;
   }
   RETVALUE(ROK);
}


#ifdef TFU_TDD

#ifdef TFU_TDD


/***********************************************************
*
*     Func : cmPkTfuUePucchHqRecpInfo
*
*
*     Desc : This structure is sent from scheduler to PHY in order to request the
 * reception of harq information on PUCCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuUePucchHqRecpInfo
(
TfuUePucchHqRecpInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuUePucchHqRecpInfo(param, mBuf)
TfuUePucchHqRecpInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkTfuUePucchHqRecpInfo)

   CMCHKPK(SPkU8, param->a, mBuf);
   for (i=TFU_MAX_HQ_RES-1; i >= 0; i--) {
      CMCHKPK(SPkU16, param->hqRes[i], mBuf);
   }
   CMCHKPK(SPkU8, param->pucchResCnt, mBuf);
   CMCHKPK(SPkU8, param->hqSz, mBuf);
   CMCHKPK(SPkU32, param->hqFdbkMode, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuUePucchHqRecpInfo
*
*
*     Desc : This structure is sent from scheduler to PHY in order to request the
 * reception of harq information on PUCCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuUePucchHqRecpInfo
(
TfuUePucchHqRecpInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuUePucchHqRecpInfo(param, mBuf)
TfuUePucchHqRecpInfo *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkTfuUePucchHqRecpInfo)

   CMCHKUNPK(SUnpkU32, (U32 *)&param->hqFdbkMode, mBuf);
   CMCHKUNPK(SUnpkU8, &param->hqSz, mBuf);
   CMCHKUNPK(SUnpkU8, &param->pucchResCnt, mBuf);
   for (i=0; i<TFU_MAX_HQ_RES; i++) {
      CMCHKUNPK(SUnpkU16, &param->hqRes[i], mBuf);
   }
   CMCHKUNPK(SUnpkU8, &param->a, mBuf);
   RETVALUE(ROK);
}


#endif

#endif

#ifndef TFU_TDD  /* else of TFU_TDD */

#ifndef TFU_TDD  /* else of TFU_TDD */


/***********************************************************
*
*     Func : cmPkTfuUePucchHqRecpInfo
*
*
*     Desc : This structure is sent from scheduler to PHY in order to request the
 * reception of harq information on PUCCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuUePucchHqRecpInfo
(
TfuUePucchHqRecpInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuUePucchHqRecpInfo(param, mBuf)
TfuUePucchHqRecpInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuUePucchHqRecpInfo)
#ifdef LTE_ADV
   S32 idx;
   for (idx=(TFU_MAX_HQ_RES-1); idx >= 0; idx--) {
      CMCHKPK(SPkU16, param->hqRes[idx], mBuf);
   }
#else
   CMCHKPK(SPkU16, param->hqRes[0], mBuf);
#endif
   CMCHKPK(SPkU8, param->pucchResCnt, mBuf);
   CMCHKPK(SPkU8, param->hqSz, mBuf);
   CMCHKPK(SPkU32, param->hqFdbkMode, mBuf);

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuUePucchHqRecpInfo
*
*
*     Desc : This structure is sent from scheduler to PHY in order to request the
 * reception of harq information on PUCCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuUePucchHqRecpInfo
(
TfuUePucchHqRecpInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuUePucchHqRecpInfo(param, mBuf)
TfuUePucchHqRecpInfo *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkTfuUePucchHqRecpInfo)

   CMCHKUNPK(SUnpkU32, (U32 *)&param->hqFdbkMode, mBuf);
   CMCHKUNPK(SUnpkU8, &param->hqSz, mBuf);
   CMCHKUNPK(SUnpkU8, &param->pucchResCnt, mBuf);
#ifdef LTE_ADV
   S32 idx;
   for (idx=0; idx<TFU_MAX_HQ_RES; idx++) {
      CMCHKUNPK(SUnpkU16, &param->hqRes[idx], mBuf);
   }
#else
   CMCHKUNPK(SUnpkU16, &param->hqRes[0], mBuf);
#endif

   RETVALUE(ROK);
}


#endif

#endif


/***********************************************************
*
*     Func : cmPkTfuUePucchSrRecpInfo
*
*
*     Desc : This structure is sent from scheduler to PHY in order to request the
 * reception of SR information on PUCCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuUePucchSrRecpInfo
(
TfuUePucchSrRecpInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuUePucchSrRecpInfo(param, mBuf)
TfuUePucchSrRecpInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuUePucchSrRecpInfo)

   CMCHKPK(SPkU16, param->n1PucchIdx, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuUePucchSrRecpInfo
*
*
*     Desc : This structure is sent from scheduler to PHY in order to request the
 * reception of SR information on PUCCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuUePucchSrRecpInfo
(
TfuUePucchSrRecpInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuUePucchSrRecpInfo(param, mBuf)
TfuUePucchSrRecpInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuUePucchSrRecpInfo)

   CMCHKUNPK(SUnpkU16, &param->n1PucchIdx, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuUePucchCqiRecpInfo
*
*
*     Desc : This structure is sent from scheduler to PHY in order to request the
 * reception of CQI information on PUCCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuUePucchCqiRecpInfo
(
TfuUePucchCqiRecpInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuUePucchCqiRecpInfo(param, mBuf)
TfuUePucchCqiRecpInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuUePucchCqiRecpInfo)

   CMCHKPK(SPkU8, param->cqiPmiSz, mBuf);
   CMCHKPK(SPkU16, param->n2PucchIdx, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuUePucchCqiRecpInfo
*
*
*     Desc : This structure is sent from scheduler to PHY in order to request the
 * reception of CQI information on PUCCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuUePucchCqiRecpInfo
(
TfuUePucchCqiRecpInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuUePucchCqiRecpInfo(param, mBuf)
TfuUePucchCqiRecpInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuUePucchCqiRecpInfo)

   CMCHKUNPK(SUnpkU16, &param->n2PucchIdx, mBuf);
   CMCHKUNPK(SUnpkU8, &param->cqiPmiSz, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuUePucchSrsRecpInfo
*
*
*     Desc : This structure is sent from scheduler to PHY in order to request the
 * reception of SRS information on PUCCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuUePucchSrsRecpInfo
(
TfuUePucchSrsRecpInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuUePucchSrsRecpInfo(param, mBuf)
TfuUePucchSrsRecpInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuUePucchSrsRecpInfo)

   CMCHKPK(SPkU32, param->srsCyclicShft, mBuf);
   CMCHKPK(SPkU16, param->srsCfgIdx, mBuf);
   CMCHKPK(SPkU8, param->transComb, mBuf);
   CMCHKPK(SPkU32, param->srsHopBw, mBuf);
   CMCHKPK(SPkU8, param->nRrc, mBuf);
   CMCHKPK(SPkU32, param->srsBw, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuUePucchSrsRecpInfo
*
*
*     Desc : This structure is sent from scheduler to PHY in order to request the
 * reception of SRS information on PUCCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuUePucchSrsRecpInfo
(
TfuUePucchSrsRecpInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuUePucchSrsRecpInfo(param, mBuf)
TfuUePucchSrsRecpInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuUePucchSrsRecpInfo)

   CMCHKUNPK(SUnpkU32, (U32 *)&param->srsBw, mBuf);
   CMCHKUNPK(SUnpkU8, &param->nRrc, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&param->srsHopBw, mBuf);
   CMCHKUNPK(SUnpkU8, &param->transComb, mBuf);
   CMCHKUNPK(SUnpkU16, &param->srsCfgIdx, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&param->srsCyclicShft, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuUePucchRecpReq
*
*
*     Desc : This structure is sent from scheduler to PHY in order to request the
  * reception of UCI on PUCCH. This may contain the following:
  * -# HARQ
  * -# SR
  * -# SRS
  * -# CQI
  * -# HARQ+SR
  * -# HARQ+SRS
  * -# HARQ+CQI
  * -# HARQ+SR+SRS
  * -# HARQ+SR+CQI
  * -# SR+SRS
  * -# SR+CQI
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuUePucchRecpReq
(
TfuUePucchRecpReq *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuUePucchRecpReq(param, mBuf)
TfuUePucchRecpReq *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuUePucchRecpReq)

   CMCHKPK(cmPkTfuUePucchSrsRecpInfo, &param->srsInfo, mBuf);
   CMCHKPK(cmPkTfuUePucchHqRecpInfo, &param->hqInfo, mBuf);
   CMCHKPK(cmPkTfuUePucchSrRecpInfo, &param->srInfo, mBuf);
   CMCHKPK(cmPkTfuUePucchCqiRecpInfo, &param->cqiInfo, mBuf);
   CMCHKPK(SPkU32, param->uciInfo, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuUePucchRecpReq
*
*
*     Desc : This structure is sent from scheduler to PHY in order to request the
  * reception of UCI on PUCCH. This may contain the following:
  * -# HARQ
  * -# SR
  * -# SRS
  * -# CQI
  * -# HARQ+SR
  * -# HARQ+SRS
  * -# HARQ+CQI
  * -# HARQ+SR+SRS
  * -# HARQ+SR+CQI
  * -# SR+SRS
  * -# SR+CQI
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuUePucchRecpReq
(
TfuUePucchRecpReq *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuUePucchRecpReq(param, mBuf)
TfuUePucchRecpReq *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuUePucchRecpReq)

   CMCHKUNPK(SUnpkU32, (U32 *)&param->uciInfo, mBuf);
   CMCHKUNPK(cmUnpkTfuUePucchCqiRecpInfo, &param->cqiInfo, mBuf);
   CMCHKUNPK(cmUnpkTfuUePucchSrRecpInfo, &param->srInfo, mBuf);
   CMCHKUNPK(cmUnpkTfuUePucchHqRecpInfo, &param->hqInfo, mBuf);
   CMCHKUNPK(cmUnpkTfuUePucchSrsRecpInfo, &param->srsInfo, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuUeUlSchRecpInfo
*
*
*     Desc : This structure is sent from scheduler to PHY in order to request the
  * reception of UEs data on ULSCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuUeUlSchRecpInfo
(
TfuUeUlSchRecpInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuUeUlSchRecpInfo(param, mBuf)
TfuUeUlSchRecpInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuUeUlSchRecpInfo)
   CMCHKPK(SPkU8, param->nSrs, mBuf);
   CMCHKPK(SPkU8, param->crntTxNb, mBuf);
   CMCHKPK(SPkU8, param->txMode, mBuf);
   CMCHKPK(SPkU8, param->harqProcId, mBuf);
   CMCHKPK(SPkU8, param->rv, mBuf);
   CMCHKPK(SPkU8, param->ndi, mBuf);
   CMCHKPK(SPkU8, param->isRtx, mBuf);
   CMCHKPK(SPkU8, param->hoppingBits, mBuf);
   CMCHKPK(SPkU8, param->hoppingEnbld, mBuf);
   CMCHKPK(SPkU8, param->nDmrs, mBuf);
   CMCHKPK(SPkU32, param->modType, mBuf);
   CMCHKPK(SPkU8, param->numRb, mBuf);
   CMCHKPK(SPkU8, param->rbStart, mBuf);
   CMCHKPK(SPkU16, param->size, mBuf);

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuUeUlSchRecpInfo
*
*
*     Desc : This structure is sent from scheduler to PHY in order to request the
  * reception of UEs data on ULSCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuUeUlSchRecpInfo
(
TfuUeUlSchRecpInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuUeUlSchRecpInfo(param, mBuf)
TfuUeUlSchRecpInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuUeUlSchRecpInfo)

   CMCHKUNPK(SUnpkU16, &param->size, mBuf);
   CMCHKUNPK(SUnpkU8, &param->rbStart, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numRb, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&param->modType, mBuf);
   CMCHKUNPK(SUnpkU8, &param->nDmrs, mBuf);
   CMCHKUNPK(SUnpkU8, &param->hoppingEnbld, mBuf);
   CMCHKUNPK(SUnpkU8, &param->hoppingBits, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isRtx, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ndi, mBuf);
   CMCHKUNPK(SUnpkU8, &param->rv, mBuf);
   CMCHKUNPK(SUnpkU8, &param->harqProcId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->txMode, mBuf);
   CMCHKUNPK(SUnpkU8, &param->crntTxNb, mBuf);
   CMCHKUNPK(SUnpkU8, &param->nSrs, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuUePuschCqiRecpInfo
*
*
*     Desc : This structure is sent from scheduler to PHY in order to request the
  * reception of CQI_RI info on PUSCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuUePuschCqiRecpInfo
(
TfuUePuschCqiRecpInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuUePuschCqiRecpInfo(param, mBuf)
TfuUePuschCqiRecpInfo *param;
Buffer *mBuf;
#endif
{

   U32 idx = 0;
   TRC3(cmPkTfuUePuschCqiRecpInfo)

   CMCHKPK(SPkU8, param->riBetaOff, mBuf);
   CMCHKPK(SPkU8, param->cqiBetaOff, mBuf);
   for (idx = 0; idx < param->cCNum; idx++)
   {
      CMCHKPK(cmPkTknU8, &param->riSz[idx], mBuf);
      CMCHKPK(SPkU8, param->cqiPmiSzRn1[idx], mBuf);
      CMCHKPK(SPkU8, param->cqiPmiSzR1[idx], mBuf);
   }
   CMCHKPK(SPkU8, param->cCNum, mBuf);
   CMCHKPK(SPkU8, param->reportType, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuUePuschCqiRecpInfo
*
*
*     Desc : This structure is sent from scheduler to PHY in order to request the
  * reception of CQI_RI info on PUSCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuUePuschCqiRecpInfo
(
TfuUePuschCqiRecpInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuUePuschCqiRecpInfo(param, mBuf)
TfuUePuschCqiRecpInfo *param;
Buffer *mBuf;
#endif
{

   U32 idx;
   TRC3(cmUnpkTfuUePuschCqiRecpInfo)

   CMCHKUNPK(SUnpkU8, &param->reportType, mBuf);
   CMCHKUNPK(SUnpkU8, &param->cCNum, mBuf);
   for (idx = param->cCNum; idx > 0; idx--)
   {
      CMCHKUNPK(SUnpkU8, &param->cqiPmiSzR1[idx-1], mBuf);
      CMCHKUNPK(SUnpkU8, &param->cqiPmiSzRn1[idx-1], mBuf);
      CMCHKUNPK(cmUnpkTknU8, &param->riSz[idx-1], mBuf);
   }
   CMCHKUNPK(SUnpkU8, &param->cqiBetaOff, mBuf);
   CMCHKUNPK(SUnpkU8, &param->riBetaOff, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuUePuschHqRecpInfo
*
*
*     Desc : This structure is sent from scheduler to PHY in order to request the
  * reception of Harq info on PUSCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuUePuschHqRecpInfo
(
TfuUePuschHqRecpInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuUePuschHqRecpInfo(param, mBuf)
TfuUePuschHqRecpInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuUePuschHqRecpInfo)


#ifdef TFU_TDD
   CMCHKPK(SPkU8, param->ulDai, mBuf);
   CMCHKPK(SPkU8, param->nBundled, mBuf);
   CMCHKPK(SPkU32, param->hqFdbkMode, mBuf);
#endif
   CMCHKPK(SPkU8, param->hqBetaOff, mBuf);
   CMCHKPK(SPkU8, param->hqSz, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuUePuschHqRecpInfo
*
*
*     Desc : This structure is sent from scheduler to PHY in order to request the
  * reception of Harq info on PUSCH.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuUePuschHqRecpInfo
(
TfuUePuschHqRecpInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuUePuschHqRecpInfo(param, mBuf)
TfuUePuschHqRecpInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuUePuschHqRecpInfo)

   CMCHKUNPK(SUnpkU8, &param->hqSz, mBuf);
   CMCHKUNPK(SUnpkU8, &param->hqBetaOff, mBuf);

#ifdef TFU_TDD
   CMCHKUNPK(SUnpkU32, (U32 *)&param->hqFdbkMode, mBuf);
   CMCHKUNPK(SUnpkU8, &param->nBundled, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ulDai, mBuf);
#endif
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuUePuschRecpReq
*
*
*     Desc : This structure is sent from scheduler to PHY in order to request the
  * reception of UEs data on PUSCH. This may contain the following: 
  * -# Data
  * -# Data + SRS
  * -# Data + HARQ
  * -# Data + HARQ + SRS
  * -# Data + CQI/RI
  * -# Data + CQI/RI + SRS
  * -# Data + CQI/RI + HARQ
  * -# Data + CQI/RI + HARQ + SRS
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuUePuschRecpReq
(
TfuUePuschRecpReq *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuUePuschRecpReq(param, mBuf)
TfuUePuschRecpReq *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuUePuschRecpReq)

   CMCHKPK(cmPkTknU8, &param->initialNumRbs, mBuf);
   CMCHKPK(cmPkTknU8, &param->initialNSrs, mBuf);
   CMCHKPK(cmPkTfuUePucchSrsRecpInfo, &param->srsInfo, mBuf);
   CMCHKPK(cmPkTfuUePuschHqRecpInfo, &param->hqInfo, mBuf);
   CMCHKPK(cmPkTfuUePuschCqiRecpInfo, &param->cqiRiInfo, mBuf);
   CMCHKPK(cmPkTfuUeUlSchRecpInfo, &param->ulSchInfo, mBuf);
   CMCHKPK(SPkU32, param->rcpInfo, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuUePuschRecpReq
*
*
*     Desc : This structure is sent from scheduler to PHY in order to request the
  * reception of UEs data on PUSCH. This may contain the following: 
  * -# Data
  * -# Data + SRS
  * -# Data + HARQ
  * -# Data + HARQ + SRS
  * -# Data + CQI/RI
  * -# Data + CQI/RI + SRS
  * -# Data + CQI/RI + HARQ
  * -# Data + CQI/RI + HARQ + SRS
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuUePuschRecpReq
(
TfuUePuschRecpReq *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuUePuschRecpReq(param, mBuf)
TfuUePuschRecpReq *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuUePuschRecpReq)

   CMCHKUNPK(SUnpkU32, (U32 *)&param->rcpInfo, mBuf);
   CMCHKUNPK(cmUnpkTfuUeUlSchRecpInfo, &param->ulSchInfo, mBuf);
   CMCHKUNPK(cmUnpkTfuUePuschCqiRecpInfo, &param->cqiRiInfo, mBuf);
   CMCHKUNPK(cmUnpkTfuUePuschHqRecpInfo, &param->hqInfo, mBuf);
   CMCHKUNPK(cmUnpkTfuUePucchSrsRecpInfo, &param->srsInfo, mBuf);
   CMCHKUNPK(cmUnpkTknU8, &param->initialNSrs, mBuf);
   CMCHKUNPK(cmUnpkTknU8, &param->initialNumRbs, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuUeRecpReqInfo
*
*
*     Desc : This structure is a Per UE reception request for either PUCCH or PUSCH
 * data. This contains information needed by PHY to decode the data sent by the
 * UE.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuUeRecpReqInfo
(
TfuUeRecpReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuUeRecpReqInfo(param, mBuf)
TfuUeRecpReqInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuUeRecpReqInfo)

      switch(param->type) {
         case TFU_RECP_REQ_PUSCH:
            CMCHKPK(cmPkTfuUePuschRecpReq, &param->t.puschRecpReq, mBuf);
            break;
         case TFU_RECP_REQ_PUCCH:
            CMCHKPK(cmPkTfuUePucchRecpReq, &param->t.pucchRecpReq, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(SPkU32, param->type, mBuf);
   CMCHKPK(cmPkLteRnti, param->rnti, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuUeRecpReqInfo
*
*
*     Desc : This structure is a Per UE reception request for either PUCCH or PUSCH
 * data. This contains information needed by PHY to decode the data sent by the
 * UE.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuUeRecpReqInfo
(
TfuUeRecpReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuUeRecpReqInfo(param, mBuf)
TfuUeRecpReqInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuUeRecpReqInfo)

   CMCHKUNPK(cmUnpkLteRnti, &param->rnti, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&param->type, mBuf);
      switch(param->type) {
         case TFU_RECP_REQ_PUCCH:
            CMCHKUNPK(cmUnpkTfuUePucchRecpReq, &param->t.pucchRecpReq, mBuf);
            break;
         case TFU_RECP_REQ_PUSCH:
            CMCHKUNPK(cmUnpkTfuUePuschRecpReq, &param->t.puschRecpReq, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}
#endif /* TFU_UPGRADE */
#ifndef TFU_UPGRADE  /* TFU_UPGRADE */
/***********************************************************
*
*     Func : cmPkTfuUePucchRecpReq
*
*
*     Desc : This structure is sent from Scheduler to PHY in order to request the
  * reception of an UEs data on PUCCH. This may contain the following: 
  * -# HARQ-ACK 
  * -# Scheduling Request (SR)
  * -# HARQ-ACK and SR
  * -# CQI
  * -# CQI and HARQ-ACK
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuUePucchRecpReq
(
TfuUePucchRecpReq *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuUePucchRecpReq(param, mBuf)
TfuUePucchRecpReq *param;
Buffer *mBuf;
#endif
{

#ifdef TFU_TDD
   S32 i;
#endif
   TRC3(cmPkTfuUePucchRecpReq)


#ifdef TFU_TDD
   for (i=TFU_MAX_M-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->p[i], mBuf);
   }
   for (i=TFU_MAX_M-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->m[i], mBuf);
   }
   CMCHKPK(SPkU8, param->M, mBuf);
   CMCHKPK(SPkU8, param->multCnt, mBuf);

#endif
   CMCHKPK(SPkU32, param->type, mBuf);
      switch(param->hqType) {
         case TFU_HQ_RECP_REQ_N1PUCCH:
            CMCHKPK(SPkU16, param->t.n1Pucch, mBuf);
            break;
   
#ifdef TFU_TDD
         case TFU_HQ_RECP_REQ_NORMAL:
            for (i=TFU_MAX_M-1; i >= 0; i--) {
               CMCHKPK(SPkU16, param->t.nCce[i], mBuf);
            }
            break;
   
#endif
   
#ifndef TFU_TDD
         case TFU_HQ_RECP_REQ_NORMAL:
            CMCHKPK(SPkU16, param->t.nCce, mBuf);
            break;
   
#endif
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(SPkU32, param->hqType, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuUePucchRecpReq
*
*
*     Desc : This structure is sent from Scheduler to PHY in order to request the
  * reception of an UEs data on PUCCH. This may contain the following: 
  * -# HARQ-ACK 
  * -# Scheduling Request (SR)
  * -# HARQ-ACK and SR
  * -# CQI
  * -# CQI and HARQ-ACK
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuUePucchRecpReq
(
TfuUePucchRecpReq *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuUePucchRecpReq(param, mBuf)
TfuUePucchRecpReq *param;
Buffer *mBuf;
#endif
{

#ifdef TFU_TDD
   S32 i;
#endif
   TRC3(cmUnpkTfuUePucchRecpReq)

   CMCHKUNPK(SUnpkU32, (U32 *)&param->hqType, mBuf);
      switch(param->hqType) {
   
#ifndef TFU_TDD
         case TFU_HQ_RECP_REQ_NORMAL:
            CMCHKUNPK(SUnpkU16, &param->t.nCce, mBuf);
            break;
   
#endif
   
#ifdef TFU_TDD
         case TFU_HQ_RECP_REQ_NORMAL:
            for (i=0; i<TFU_MAX_M; i++) {
               CMCHKUNPK(SUnpkU16, &param->t.nCce[i], mBuf);
            }
            break;
   
#endif
         case TFU_HQ_RECP_REQ_N1PUCCH:
            CMCHKUNPK(SUnpkU16, &param->t.n1Pucch, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   CMCHKUNPK(SUnpkU32, (U32 *)&param->type, mBuf);

#ifdef TFU_TDD
   CMCHKUNPK(SUnpkU8, &param->multCnt, mBuf);
   CMCHKUNPK(SUnpkU8, &param->M, mBuf);
   for (i=0; i<TFU_MAX_M; i++) {
      CMCHKUNPK(SUnpkU8, &param->m[i], mBuf);
   }
   for (i=0; i<TFU_MAX_M; i++) {
      CMCHKUNPK(SUnpkU8, &param->p[i], mBuf);
   }

#endif
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuUeMsg3RecpReq
*
*
*     Desc : This structure is sent from scheduler to PHY in order to request the
  * reception of UEs data sent as MSG3 for Random access.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuUeMsg3RecpReq
(
TfuUeMsg3RecpReq *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuUeMsg3RecpReq(param, mBuf)
TfuUeMsg3RecpReq *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuUeMsg3RecpReq)

   CMCHKPK(SPkU32, param->modType, mBuf);
   CMCHKPK(SPkU16, param->size, mBuf);
   /*ccpu00128993 - ADD - fix for msg3 softcombining bug*/
   CMCHKPK(SPkU8, param->nDmrs, mBuf);
   CMCHKPK(SPkU8, param->rv, mBuf);
   CMCHKPK(SPkU8, param->ndi, mBuf);
   CMCHKPK(SPkU8, param->harqProcId, mBuf);
   CMCHKPK(SPkU8, param->isRtx, mBuf);
   CMCHKPK(SPkU8, param->ulDelay, mBuf);
   CMCHKPK(SPkU8, param->expCqi, mBuf);
   CMCHKPK(SPkU8, param->mcs, mBuf);
   CMCHKPK(SPkU8, param->numRb, mBuf);
   CMCHKPK(SPkU8, param->rbStart, mBuf);
   CMCHKPK(SPkU8, param->hoppingEnbld, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuUeMsg3RecpReq
*
*
*     Desc : This structure is sent from scheduler to PHY in order to request the
  * reception of UEs data sent as MSG3 for Random access.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuUeMsg3RecpReq
(
TfuUeMsg3RecpReq *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuUeMsg3RecpReq(param, mBuf)
TfuUeMsg3RecpReq *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuUeMsg3RecpReq)

   CMCHKUNPK(SUnpkU8, &param->hoppingEnbld, mBuf);
   CMCHKUNPK(SUnpkU8, &param->rbStart, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numRb, mBuf);
   CMCHKUNPK(SUnpkU8, &param->mcs, mBuf);
   CMCHKUNPK(SUnpkU8, &param->expCqi, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ulDelay, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isRtx, mBuf);
   /*ccpu00128993 - ADD - fix for msg3 softcombining bug*/
   CMCHKUNPK(SUnpkU8, &param->harqProcId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ndi, mBuf);
   CMCHKUNPK(SUnpkU8, &param->rv, mBuf);
   CMCHKUNPK(SUnpkU8, &param->nDmrs, mBuf);
   CMCHKUNPK(SUnpkU16, &param->size, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&param->modType, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuUePuschRecpReq
*
*
*     Desc : This structure is sent from scheduler to PHY in order to request the
  * reception of UEs data on PUSCH. This may contain the following: 
  * -# Data
  * -# Data + CQI and RI
  * -# Data + CQI and HARQ
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuUePuschRecpReq
(
TfuUePuschRecpReq *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuUePuschRecpReq(param, mBuf)
TfuUePuschRecpReq *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuUePuschRecpReq)

   CMCHKPK(SPkU32, param->modType, mBuf);
   CMCHKPK(SPkU16, param->size, mBuf);
   CMCHKPK(SPkU32, param->mode, mBuf);
   CMCHKPK(SPkU8, param->expHarq, mBuf);
   CMCHKPK(SPkU8, param->expCqi, mBuf);
   CMCHKPK(SPkU8, param->nDmrs, mBuf);
   CMCHKPK(SPkU8, param->rv, mBuf);
   CMCHKPK(SPkU8, param->isRtx, mBuf);
   CMCHKPK(SPkU8, param->ndi, mBuf);
   CMCHKPK(SPkU8, param->harqProcId, mBuf);
   CMCHKPK(SPkU8, param->mcs, mBuf);
   CMCHKPK(SPkU8, param->numRb, mBuf);
   CMCHKPK(SPkU8, param->rbStart, mBuf);
   CMCHKPK(SPkU8, param->hoppingBits, mBuf);
   CMCHKPK(SPkU8, param->hoppingEnbld, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuUePuschRecpReq
*
*
*     Desc : This structure is sent from scheduler to PHY in order to request the
  * reception of UEs data on PUSCH. This may contain the following: 
  * -# Data
  * -# Data + CQI and RI
  * -# Data + CQI and HARQ
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuUePuschRecpReq
(
TfuUePuschRecpReq *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuUePuschRecpReq(param, mBuf)
TfuUePuschRecpReq *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuUePuschRecpReq)

   CMCHKUNPK(SUnpkU8, &param->hoppingEnbld, mBuf);
   CMCHKUNPK(SUnpkU8, &param->hoppingBits, mBuf);
   CMCHKUNPK(SUnpkU8, &param->rbStart, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numRb, mBuf);
   CMCHKUNPK(SUnpkU8, &param->mcs, mBuf);
   CMCHKUNPK(SUnpkU8, &param->harqProcId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ndi, mBuf);
   CMCHKUNPK(SUnpkU8, &param->isRtx, mBuf);
   CMCHKUNPK(SUnpkU8, &param->rv, mBuf);
   CMCHKUNPK(SUnpkU8, &param->nDmrs, mBuf);
   CMCHKUNPK(SUnpkU8, &param->expCqi, mBuf);
   CMCHKUNPK(SUnpkU8, &param->expHarq, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&param->mode, mBuf);
   CMCHKUNPK(SUnpkU16, &param->size, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&param->modType, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkTfuUeRecpReqInfo
*
*
*     Desc : This structure is a Per UE reception request for either PUCCH or PUSCH
 * data. This contains information needed by PHY to decode the data sent by the
 * UE.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuUeRecpReqInfo
(
TfuUeRecpReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkTfuUeRecpReqInfo(param, mBuf)
TfuUeRecpReqInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuUeRecpReqInfo)

      switch(param->type) {
         case TFU_RECP_REQ_PUSCH:
            CMCHKPK(cmPkTfuUePuschRecpReq, &param->t.puschRecpReq, mBuf);
            break;
         case TFU_RECP_REQ_MSG3:
            CMCHKPK(cmPkTfuUeMsg3RecpReq, &param->t.msg3RecpReq, mBuf);
            break;
         case TFU_RECP_REQ_PUCCH:
            CMCHKPK(cmPkTfuUePucchRecpReq, &param->t.pucchRecpReq, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(SPkU32, param->type, mBuf);
   CMCHKPK(cmPkLteRnti, param->rnti, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkTfuUeRecpReqInfo
*
*
*     Desc : This structure is a Per UE reception request for either PUCCH or PUSCH
 * data. This contains information needed by PHY to decode the data sent by the
 * UE.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuUeRecpReqInfo
(
TfuUeRecpReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuUeRecpReqInfo(param, mBuf)
TfuUeRecpReqInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuUeRecpReqInfo)

   CMCHKUNPK(cmUnpkLteRnti, &param->rnti, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&param->type, mBuf);
      switch(param->type) {
         case TFU_RECP_REQ_PUCCH:
            CMCHKUNPK(cmUnpkTfuUePucchRecpReq, &param->t.pucchRecpReq, mBuf);
            break;
         case TFU_RECP_REQ_MSG3:
            CMCHKUNPK(cmUnpkTfuUeMsg3RecpReq, &param->t.msg3RecpReq, mBuf);
            break;
         case TFU_RECP_REQ_PUSCH:
            CMCHKUNPK(cmUnpkTfuUePuschRecpReq, &param->t.puschRecpReq, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}


#endif /* ifndef TFU_UPGRADE */
/*LAA: Packing and Unpacking*/

/***********************************************************
*
*     Func : cmPkTfuErrIndInfo
*
*
*     Desc : This structure contains information that is passed as a part of
*     the ERR indication sent from PHY to MAC.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PRIVATE S16 cmPkTfuErrIndInfo
(
TfuErrIndInfo *param,
Buffer *mBuf
)
#else
PRIVATE S16 cmPkTfuErrIndInfo(param, mBuf)
TfuErrIndInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkTfuErrIndInfo)

   CMCHKPK(cmPkLteTimingInfo, &param->timingInfo, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}
/***********************************************************
*
*     Func : cmUnpkTfuErrIndInfo
*
*
*     Desc : This structure contains information that is passed as a part of the ERR
 * indication sent from PHY to MAC.
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PRIVATE S16 cmUnpkTfuErrIndInfo
(
TfuErrIndInfo *param,
Buffer *mBuf
)
#else
PRIVATE S16 cmUnpkTfuErrIndInfo(param, mBuf)
TfuErrIndInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkTfuErrIndInfo)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteTimingInfo, &param->timingInfo, mBuf);
   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmPkTfuErrInd
*
*
 *      This API is invoked by PHY to send ERROR INDICATION to scheduler 
 *      Currently invoked in the cases when the Unlicensed SCell transmission
 *      fails.
 *      This API contains the Cell and subframe information for which the
 *      transmission failed. 
 *           
 *  @param[in]  Pst                *pst
 *  @param[in]  SuId               suId 
 *  @param[in]  TfuErrIndInfo      *errIndInfo 
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkTfuErrInd
(
Pst * pst,
SuId suId,
TfuErrIndInfo * errInd
)
#else
PUBLIC S16 cmPkTfuErrInd(pst, suId, errInd)
Pst * pst;
SuId suId;
TfuErrIndInfo * errInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTfuErrInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU105, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)errInd, sizeof(TfuErrIndInfo));
      RETVALUE(RFAILED);
   }
   if (pst->selector == TFU_SEL_LC) {
      if (cmPkTfuErrIndInfo(errInd, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU106, (ErrVal)0, "Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)errInd, sizeof(TfuErrIndInfo));
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if (cmPkPtr((PTR)errInd, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFUXXX, (ErrVal)0, "LWLC Packing failed");
#endif
         
         /*MS_FIX:71858:Changed to SPutSBuf as being allocated with SGetSBuf*/
         SPutSBuf(pst->region, pst->pool, (Data *)errInd, sizeof(TfuErrIndInfo));
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }

   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU107, (ErrVal)0, "Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)errInd, sizeof(TfuErrIndInfo));
      TFU_FREE_MSG(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      if (SPutSBuf(pst->region, pst->pool, (Data *)errInd, sizeof(TfuErrIndInfo)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU108, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }

   pst->event = (Event) EVTTFUERRIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/***********************************************************
*
*     Func : cmUnpkTfuErrInd
*
*
 *      This API is invoked by PHY to send ERROR INDICATION to scheduler 
 *      Currently invoked in the cases when the Unlicensed SCell transmission
 *      fails.
 *      This API contains the Cell and subframe information for which the
 *      transmission failed. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param errInd Pointer to the TfuErrIndInfo.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkTfuErrInd
(
TfuErrInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkTfuErrInd(func, pst, mBuf)
TfuErrInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   TfuErrIndInfo *errInd;
   
   TRC3(cmUnpkTfuErrInd)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ETFU109, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != TFU_SEL_LWLC) {
      if ((SGetSBuf(pst->region, pst->pool, (Data **)&errInd, sizeof(TfuErrIndInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFU110, (ErrVal)0, "Packing failed");
#endif
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }

   if (pst->selector == TFU_SEL_LC) 
   {
      if (cmUnpkTfuErrIndInfo(errInd, mBuf) != ROK) {
         SPutSBuf(pst->region, pst->pool, (Data *)errInd, sizeof(TfuErrIndInfo));
         TFU_FREE_MSG(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ETFU111, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
   }
   else if(pst->selector == TFU_SEL_LWLC)
   {
      if (cmUnpkPtr((PTR *)&errInd, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ETFUXXX, (ErrVal)0, "LWLC un-Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)errInd, sizeof(TfuErrIndInfo));
         TFU_FREE_MSG(mBuf);
         RETVALUE(RFAILED);
      }
   }
   TFU_FREE_MSG(mBuf);
   /* [ccpu00141698]-MOD- MAC/SCH does not free the TTI ind anymore */
   (*func)(pst, suId, errInd);
   SPutSBuf(pst->region, pst->pool, (Data *)errInd, sizeof(TfuErrIndInfo));
   RETVALUE(ROK);

}
#endif /* if defined(LCTFU) */

/**********************************************************************
 
         End of file:     tfu.c@@/main/8 - Wed Jul 27 12:18:38 2011
 
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
/main/1      ---       sm         1. Initial Release.
/main/2      ---       sm         1. LTE MAC 2.1 release
/main/3      --- tfu_c_001.main_2 sm         1. ccpu00107387: To include 
                                             the length and ModOrder in 
                                             DataRecp Req.   
                                             2. Pk/UnPk should take the 
                                             nmbOfTBs.
/main/5      --- tfu_c_001.main_3 rk         1. Adding Pk/UnPk for hqProcId
/main/5      ---      tfu_c_001.main_4 ap        1. Added support for MIMO
/main/6      ---    tfu_c_001.main_5   sd    1.Removed dependency on MIMO flag.
/main/7      ---    tfu_c_001.main_6   dv    1.Support for TFU upgrade.
/main/8      ---    tfu_c_001.main_7   dv    1.Support for TFU upgrade.
*********************************************************************91*/
