/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

/**********************************************************************

    Name:  LTE S1SIM - ENODEB Application Module 

    Type:  C include file

    Desc:  C source code for ENODEB Application

    File:  nb_ifm_dam_utils.c

    Sid:   

    Prg:   

**********************************************************************/

/***********************************************************************
 *        H E A D E R  I N C L U D E  F I L E S (.h)                   *
 ***********************************************************************/
#include "envopt.h"           /* environment options */
#include "envdep.h"           /* environment dependent */
#include "envind.h"           /* environment independent */
#include "gen.h"              /* General */
#include "ssi.h"              /* System Services */
#include "cm_tkns.h"          /* common tokens */
#include "cm_hash.h"          /* common structs 1 */
#include "cm_mblk.h"          /* common memory */
#include "cm_llist.h"         /* cm link list */
#include "cm5.h"              /* common structs 3 */
#include "cm_inet.h"          /* common tokens  */
#include "cm_tkns.h"          /* common tokens */
#include "cm_tpt.h"           /* common transport */
#include "cm_dns.h"           /* common transport */
#include "rl_interface.h"
#include "rl_common.h"
#include "nb_ifm_dam_utils.h" /*DAM Upper Interface */
#include "nb_dam_ifm_app.h"   /*ccpu00138576*/
#include "nb_log.h"


/***********************************************************************
 *     H E A D E R / E X T E R N   I N C L U D E  F I L E S (.h)       *
 ***********************************************************************/
#include "gen.x"               /* General */
#include "ssi.x"               /* System Services */
#include "cm_tkns.x"           /* common tokens */
#include "cm_hash.x"           /* common structs 1 */
#include "cm_lib.x"            /* common library */
#include "cm_mblk.x"           /* common memory */
#include "cm_llist.x"          /* cm link list */
#include "cm5.x"               /* common structs 3 */
#include "cm_inet.x"           /* common transport */
#include "cm_tpt.x"            /* common transport */
#include "cm_dns.x"            /* common transport */
#include "nb_ifm_dam_utils.x"  /* DMA Upper Interface */

#define NB_DAM_FREE_BUFFER(_region,_buf) \
{                                        \
   SPutMsg(_buf);                        \
}                                        

#define cmPkDamTnlType SPkU32
#define cmPkDamEgtpTeid SPkU32

EXTERN S16 nbUeTnlCreatCfm(U8, U32);
EXTERN S16 nbPrcDamUeDelCfm(U8);
/*
  Defines for the packing and unpacking
*/

/**
* @brief This API is used to pack the function for 
* the Alarm Indication 
*
* @details
*
* Function: cmPkDamSendAlarmInd
*
* @param[in] Pst *pst
* @param[in] U16 category :For what operation the alarm is being generated
* @param[in] U16 event    :alarm is generated during this event.
* @param[in] U16 cause    :Cause for the event and alarm generation.
* @return   S16
*  /RFAILED
**/
PUBLIC S16 cmPkDamSendAlarmInd
(
Pst *pst,
U16                          category,
U16                          event,
U16                          cause
)
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkDamSendAlarmInd)

   if (SGetMsg(pst->region, pst->pool,&mBuf) != ROK) 
   {
      NB_LOG_ERROR(&nbCb,"Memory allocation failed.");

      RETVALUE(RFAILED);
   }

   CMCHKPKLOG(SPkU16, category, mBuf,0, pst);
   CMCHKPKLOG(SPkU16, event, mBuf,0, pst);
   CMCHKPKLOG(SPkU16, cause, mBuf,0, pst);

   pst->event = (Event)EVTDAMALARMIND;
   RETVALUE(SPstTsk(pst, mBuf));

}/* cmPkDamSendAlarmInd */

/**
* @brief This API is used to unpack the 
* Alarm Indication.In turn it calls the Dam Interface 
* function to send the Alarm Indication. 
*
* @details
*
* Function: cmUnpkDamSendAlarmInd 
*
* @param[in] Pst    *pst
* @param[in] Buffer *mBuf 
* @return   S16
*  /RFAILED
**/
PUBLIC Void cmUnpkDamSendAlarmInd
(
Pst *pst,
Buffer *mBuf
)
{
   U16  cause;
   U16  event;
   U16  category;

   TRC3(cmUnpkDamSendAlarmInd)

   CMCHKUNPKLOG(SUnpkU16,&cause, mBuf,0, pst);
   CMCHKUNPKLOG(SUnpkU16,&event, mBuf,0, pst);
   CMCHKUNPKLOG(SUnpkU16,&category, mBuf,0, pst);

   NB_DAM_FREE_BUFFER (pst->region, mBuf);

   nbIfmDamSendAlarmInd(category, event, cause);

}/* cmUnpkDamSendAlarmInd */

/**
* @brief This API is used to pack the Dam Configuration Request 
*         and post it.
*
* @details
*
* Function: cmPkDamCfgReq
*
* @param[in] Pst      *pst
* @param[in] LnbMngmt *cfg 
* @return   S16
*  -# ROK/RFAILED
**/
PUBLIC S16 cmPkDamCfgReq
(
Pst *pst,
LnbMngmt *cfg
)
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkDamCfgReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
      NB_LOG_ERROR(&nbCb,"Memory allocation failed.");

      RETVALUE(RFAILED);
   }

   CMCHKPKLOG(cmPkPtr,(PTR)cfg, mBuf,0, pst);
   pst->event = (Event)EVTDAMCFGREQ;
   RETVALUE(SPstTsk(pst, mBuf));

}/* cmPkDamCfgReq */

/**
* @brief This API is used to pack Dam Control Confirm
*       and also it post the message.
*
* @details
*
* Function: cmPkDamCntrlCfm
*
* @param[in] Pst      *pst
* @param[in] CmStatus *cmStatus 
* @param[in] LnbMngmt *cntrl 
* @return   S16
*  -# ROK/RFAILED
**/
PUBLIC S16 cmPkDamCntrlCfm
(
Pst *pst,
CmStatus *cmStatus,
LnbMngmt *cntrl
)
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkDamCntrlCfm);

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
      NB_LOG_ERROR(&nbCb,"Memory allocation failed.");

      RETVALUE(RFAILED);
   }

   CMCHKPKLOG(cmPkPtr,(PTR)cntrl, mBuf,0, pst);
   CMCHKPKLOG(cmPkCmStatus, cmStatus, mBuf,0, pst);

   pst->event = (Event)EVTDAMCNTRLCFM;
   RETVALUE(SPstTsk(pst, mBuf));

}/* cmPkDamCntrlCfm */



/**
* @brief This API is used to pack the Dam Control Request 
* post the message.
*
* @details
*
* Function: cmPkDamCntrlReq 
*
* @param[in] Pst *  pst
* @param[in] LnbMngmt *cntrl 
* @return   S16
*  -# ROK/RFAILED
**/
PUBLIC S16 cmPkDamCntrlReq
(
Pst *pst,
LnbMngmt *cntrl
)
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkDamCfgReq)

   if (SGetMsg(pst->region, pst->pool,&mBuf)!= ROK) 
   {
      NB_LOG_ERROR(&nbCb,"Memory allocation failed.");
      RETVALUE(RFAILED);
   }

   CMCHKPKLOG(cmPkPtr,(PTR)cntrl, mBuf,0, pst);

   pst->event = (Event)EVTDAMCNTRLREQ;
   RETVALUE(SPstTsk(pst, mBuf));

}/* cmPkDamCntrlReq */

/**
* @brief This API is used to pack the Dam Config Confirm
* and send the message.
*
* @details
*
* Function: cmPkDamCfgCfm
*
* @param[in] Pst *  pst
* @param[in] LnbMngmt *cfg
* @param[in] CmStatus *cmStatus
* @return   S16
*  -# ROK/RFAILED
**/
PUBLIC S16 cmPkDamCfgCfm
(
Pst *pst,
LnbMngmt *cfg,
CmStatus *cmStatus
)
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkDamCfgCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
      NB_LOG_ERROR(&nbCb,"Memory allocation failed.");

      RETVALUE(RFAILED);
   }

   CMCHKPKLOG(cmPkPtr,(PTR)cfg, mBuf,0, pst);
   CMCHKPKLOG(cmPkCmStatus, cmStatus, mBuf,0, pst);

   pst->event = (Event)EVTDAMCFGCFM;
   RETVALUE(SPstTsk(pst, mBuf));

}/* cmPkDamCfgCfm */


/**
* @brief This API is used unpack the message and calls the 
* Dam Configuration function. 
*
* @details
*
*     Function: cmUnpkDamCfgReq
*
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return   Void
*      -# ROK
**/

PUBLIC Void cmUnpkDamCfgReq
(
Pst *pst,
Buffer *mBuf
)
{
   LnbMngmt *cfg;

   TRC3(cmUnpkDamCfgReq)

   CMCHKUNPKLOG(cmUnpkPtr,(PTR *)&cfg, mBuf, 0, pst);

   NB_DAM_FREE_BUFFER(pst->region, mBuf);

   nbIfmDamNbCfgReq(cfg);

}/* cmUnpkDamCfgReq */

/**
* @brief This API is used to call the function directly
* in DAM interface file.This function in turn will call the
* Dam Control Request function in DAM module. 
*
* @details
*
*     Function: cmUnpkDamCntrlReq 
*
*
*  @param[in]  Pst *pst 
*  @param[in]  buf *mBuf
*  @return   Void 
**/

PUBLIC Void cmUnpkDamCntrlReq
(
Pst *pst,
Buffer *mBuf
)
{
   LnbMngmt *cntrl;

   TRC3(cmUnPkDamCntrlReq)

   CMCHKUNPKLOG(cmUnpkPtr,(PTR *)&cntrl, mBuf, 0, pst);

   NB_DAM_FREE_BUFFER(pst->region, mBuf);

   nbIfmDamNbCntrlReq(cntrl);

}/* cmUnpkDamCntrlReq */

/**
* @brief This API is used unpack the function and call the 
*  config confirm function.
*
*  @details
*
*  Function: cmUnpkDamCfgCfm 
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return   Void
*      -# ROK
**/

PUBLIC Void cmUnpkDamCfgCfm
(
Pst *pst,
Buffer *mBuf
)
{
   LnbMngmt *cfg;
   CmStatus status;

   TRC3(cmUnpkDamCfgReq)

   CMCHKUNPKLOG(cmUnpkCmStatus,&status, mBuf, 0, pst);
   CMCHKUNPKLOG(cmUnpkPtr,(PTR *)&cfg, mBuf, 0, pst);

   NB_DAM_FREE_BUFFER(pst->region, mBuf);

   nbIfmDamCfgCfm(cfg,&status);

} /* cmUnpkDamCfgCfm */

/**
* @brief This API is used unpacks the message  and calls 
*        control confirm function in DAM module. 
*
* @details
*
* Function:cmUnpkDamCntrlCfm 
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return   Void
*      -# ROK
**/

PUBLIC Void cmUnpkDamCntrlCfm
(
Pst *pst,
Buffer *mBuf
)
{
   LnbMngmt *cntrl;
   CmStatus  status;

   TRC3(cmUnPkDamCntrlReq)

   CMCHKUNPKLOG(cmUnpkCmStatus,(&status), mBuf, 0, pst);
   CMCHKUNPKLOG(cmUnpkPtr,((PTR *)&cntrl), mBuf, 0, pst);

   NB_DAM_FREE_BUFFER(pst->region, mBuf);

   nbIfmDamCntrlCfm(cntrl,&status);

}/* cmUnpkDamCntrlCfm */


/**
* @brief This API is used to send a 
* Tunnel Create  Request from EnbApp to DAM.
*
* @details
*
* Function: cmPkTnlCreatReq
* 
* @param[in]  Pst *  pst
* @param[in]  U32 transId 
* @param[in]  WrDamTnlInfo *tnlInfo
* @return   S16
*  -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkTnlCreatReq
(
Pst *pst,
NbDamTnlInfo *tnlInfo
)
#else
PUBLIC S16 cmPkTnlCreatReq(pst,*tnlInfo)
Pst * pst;
NbDamTnlInfo *tnlInfo;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkTnlCreatReq)
  
   /* Buffer Allocation */
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {

      NB_LOG_ERROR(&nbCb,"Memory allocation failed.");

      RETVALUE(RFAILED);
   }
   

   /* LWLC Packing */
   if (pst->selector == DAM_SEL_LWLC) {
      CMCHKPKLOG(cmPkPtr,((PTR)tnlInfo), mBuf,0, pst);
   }
   else
   {
      NB_LOG_ERROR(&nbCb,"Incorrect Coupling Scheme selected");

     NB_DAM_FREE_BUFFER (pst->region, mBuf);

     RETVALUE(RFAILED);
   }
 
   pst->event = (Event)EVTDAMTNLCRETREQ;
   RETVALUE(SPstTsk(pst, mBuf));

}/* cmPkTnlCreatReq */

/**
* @brief This API is used to call the function directly
* in DAM interface file.This function in turn will call the
* tunnel creation function in DAM module. 
*
* @details
*
*     Function: cmUnPkTnlCreatReq
*
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return   Void
**/

#ifdef ANSI
PUBLIC Void cmUnPkTnlCreatReq
(
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC Void cmUnPkTnlCreatReq(pst, mBuf)
Pst *pst;
Buffer *mBuf;
#endif
{
    NbDamTnlInfo *tnlInfo = NULLP;

    TRC3(cmUnPkTnlCreatReq)

    CMCHKUNPKLOG(cmUnpkPtr,((PTR *)&tnlInfo), mBuf, EEGT014, pst);

    NB_DAM_FREE_BUFFER (pst->region, mBuf);

    nbIfmDamNbTnlCreatReq(tnlInfo);

}/* cmUnPkTnlCreatReq */

PUBLIC S16 cmPkUeCntxtRelReq
(
 Pst *pst,
 U32 ueId,
 U8 cause
)
{
   Buffer *mBuf = NULLP;

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {

      NB_LOG_ERROR(&nbCb,"Memory allocation failed.");

      RETVALUE(RFAILED);
   }
   CMCHKPKLOG(SPkU32, ueId, mBuf, 0, pst);
   CMCHKPKLOG(SPkU8, cause, mBuf, 0, pst);
 
   pst->event = (Event)EVTDAMUECNTXTRELREQ;
   RETVALUE(SPstTsk(pst, mBuf));
}

PUBLIC S16 cmUnPkUeCntxtRelReq
(
Pst *pst,
Buffer *mBuf
)
{
   U32 ueId = 0;
   U8 causeVal = 0;
   U8 causeType = 0;

   CMCHKUNPKLOG(SUnpkU32, &ueId, mBuf, 0, pst);
   CMCHKUNPKLOG(SUnpkU8, &causeVal, mBuf, 0, pst);
   CMCHKUNPKLOG(SUnpkU8, &causeType, mBuf, 0, pst);

   NB_DAM_FREE_BUFFER(pst->region, mBuf);
   nbIfmDamHandleUeCntxtRelReq(ueId, causeVal, causeType);

   RETVALUE(ROK);
} /* cmUnPkUeCntxtRelReq */

/**
* @brief This API is used to send a 
* tunnel create confirm  from EnbApp to DAM.
*
* @details
*
* Function:cmPkTnlCreatCfm
* 
* @param[in] Pst *  pst
* @param[in] U8 status
* @param[in] U32 lclTeid
* @return   S16
*  -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkTnlCreatCfm 
(
 Pst *pst,
 U8 status,
 U32 lclTeid
)
#else
PUBLIC S16 cmPkTnlCreatCfm(pst, status, lclTeid)
Pst * pst;
U8 status;
U32 lclTeid;
#endif
{
   Buffer *mBuf = NULLP
   TRC3(cmPkTnlCreatCfm)

   /* Buffer Allocation */
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
   
      NB_LOG_ERROR(&nbCb,"Memory allocation failed.");

      RETVALUE(RFAILED);
   }

   CMCHKPKLOG(SPkU8,(status ), mBuf, EDAM001, pst);
   CMCHKPKLOG(SPkU32,(lclTeid), mBuf, EDAM001, pst);
  
   pst->event = (Event)EVTDAMTNLCRETCFM;
   RETVALUE(SPstTsk(pst, mBuf));

}/* End of cmPkTnlCreatCfm*/


/**
* @brief This API is used to call the function directly
* in DAM interface file.This function in turn will call the
* tunnel creation confirm  function in DAM module. 
*
* @details
*
*     Function: cmUnPkTnlCreatCfm
*
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return   Void
**/

#ifdef ANSI
PUBLIC Void cmUnPkTnlCreatCfm
(
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC Void cmUnPkTnlCreatCfm(pst, mBuf)
Pst *pst;
Buffer *mBuf;
#endif
{
   U8 status   = 0;
   U32 lclTeid = 0;
 
   TRC3(cmUnPkTnlCreatCfm)
      
   CMCHKUNPKLOG(SUnpkU32,(&lclTeid), mBuf, EDAM001, pst);
   CMCHKUNPKLOG(SUnpkU8,&status, mBuf, EDAM002, pst);
  
   NB_DAM_FREE_BUFFER (pst->region, mBuf);
   nbUeTnlCreatCfm(status, lclTeid);

}/* cmUnPkTnlCreatCfm */

/**
* @brief This API is used to send a 
* Ue Delete request from Enbapp to DAM.
*
* @details
*
* Function:cmPkUeDelReq 
* 
* @param[in]   Pst *  pst
* @param[in]   U32 ueId
* @return   S16
*  -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkUeDelReq 
(
Pst *pst,
U32 ueId
)
#else
PUBLIC S16 cmPkUeDelReq(pst, ueId)
Pst * pst;
U32 ueId;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkUeDelReq)

   /* Buffer Allocation */
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {

      NB_LOG_ERROR(&nbCb,"Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   CMCHKPKLOG(SPkU32, ueId, mBuf, EDAM002, pst);

   
   pst->event = (Event)EVTDAMUEDELTREQ;
   RETVALUE(SPstTsk(pst, mBuf));

}/* cmPkUeDelReq */

/**
* @brief This API is used for  unpacking the function
* UE del request.This function in turn will directly call
* the function for the deleting the UE in wr_dam.c.
*
* @details
*
*     Function: cmUnPkUeDelReq
*
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return   Void
**/
#ifdef ANSI
PUBLIC Void cmUnPkUeDelReq 
(
 Pst *pst,
 Buffer *mBuf
)
#else
PUBLIC Void cmUnPkUeDelReq(pst, mBuf)
Pst *pst;
Buffer *mBuf;
#endif
{
   U32 ueId  = 0;

   CMCHKUNPKLOG(SUnpkU32, (&ueId), mBuf, EDAM007, pst);

   NB_DAM_FREE_BUFFER(pst->region, mBuf);
   nbIfmDamNbUeDelReq(ueId);
} /* cmUnPkUeDelReq */


PUBLIC S16 cmPkErabDelReq
(
 Pst *pst,
 Void *req
)
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkUeDelReq)

   /* Buffer Allocation */
   if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {

      NB_LOG_ERROR(&nbCb,"Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   CMCHKPKLOG(cmPkPtr,(PTR)req, mBuf, 0, pst);

   pst->event = (Event)EVTDAMERABRELREQ;
   RETVALUE(SPstTsk(pst, mBuf));
}

PUBLIC Void cmUnPkErabDelReq
(
 Pst *pst,
 Buffer *mBuf
)
{
   Void *erabRelReq = NULLP;
   CMCHKUNPKLOG(cmUnpkPtr,(PTR *)&erabRelReq, mBuf, 0, pst);
   NB_DAM_FREE_BUFFER(pst->region, mBuf);
   printf("cmUnPkErabDelReq\n");
   nbDamNbErabDelReq(erabRelReq);
}

/**
* @brief This API is used to initate a 
* Ue Delete Confirm  from DAM to EnbApp. 
*
* @details
*
* Function:cmPkUeDelCfm 
* 
* @param[in]   Pst *  pst
* @param[in]   U32 ueId
* @return   S16
*  -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkUeDelCfm 
(
 Pst *pst,
 U32 ueId
)
#else
PUBLIC S16 cmPkUeDelCfm(pst, ueId)
Pst * pst;
U32 ueId;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkUeDelCfm)

   /* Buffer Allocation */ 
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {

      NB_LOG_ERROR(&nbCb," Memory allocation failed.");

      RETVALUE(RFAILED);
   }
   
   CMCHKPKLOG(SPkU32, ueId, mBuf, EDAM002, pst);
   
   pst->event = (Event)EVTDAMUEDELTCFM;
   RETVALUE(SPstTsk(pst, mBuf));
}/* cmPkUeDelCfm */ 

/**
* @brief This API is used for  unpacking the function
* UE del request.This function in turn will directly call
* the function for sending the confirmation
* for deleting the UE in wr_dam.c.
*
* @details
*
*     Function: cmUnPkUeDelCfm
*
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return   Void
**/

#ifdef ANSI
PUBLIC Void cmUnPkUeDelCfm 
(
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC Void cmUnPkUeDelCfm(pst, mBuf)
Pst *pst;
Buffer *mBuf;
#endif
{
    U32 ueId = 0;
 
    TRC3(cmUnPkUeDelCfm)

    CMCHKUNPKLOG(SUnpkU32,(&ueId), mBuf, EDAM001, pst);
 
    NB_DAM_FREE_BUFFER (pst->region, mBuf);
 
    nbPrcDamUeDelCfm(ueId);

}/* cmUnPkUeDelCfm */

/**
* @brief This API is used to pack Dam Context Rel
*       and also posts the message.
*
* @details
*
* Function: cmPkDamSendCtxtRel 
*
* @param[in] Pst      *pst
* @param[in] U32      ueId
* @param[in] U8       causeVal
* @param[in] U8       causeTyp 
* @return   S16
*  -# ROK/RFAILED
**/
PUBLIC S16 cmPkDamSendCtxtRel 
(
Pst *pst,
U32  ueId,
U8  causeVal,
U8  causeTyp
)
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkDamSendCtxtRel);

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
      NB_LOG_ERROR(&nbCb,"Memory allocation failed");

      RETVALUE(RFAILED);
   }

   CMCHKPKLOG(SPkU32, ueId, mBuf,0, pst);
   CMCHKPKLOG(SPkU8, causeVal, mBuf,0, pst);
   CMCHKPKLOG(SPkU8, causeTyp, mBuf,0, pst);

   pst->event = (Event)EVTDAMCTXTRELREQ;
   RETVALUE(SPstTsk(pst, mBuf));

}/*cmPkDamSendCtxtRel*/

/**
* @brief This API is used to call the function directly
* in DAM interface file.This function in turn will call the
* tunnel creation confirm  function in DAM module. 
*
* @details
*
*     Function: cmUnPkDamSendCtxtRel
*
*
*  @param[in]  pst 
*  @param[in]  buf 
*  @return  Void 
**/

#ifdef ANSI
PUBLIC Void cmUnPkDamSendCtxtRel 
(
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC Void cmUnPkDamSendCtxtRel(pst, mBuf)
Pst *pst;
Buffer *mBuf;
#endif
{
   U32  ueId;
   U8  causeVal;
   U8  causeTyp;
   NbUeMsgCause relCause;
 
   TRC3(cmUnPkTnlCreatCfm)

   CMCHKUNPKLOG(SUnpkU8,&causeVal, mBuf,0, pst);
   CMCHKUNPKLOG(SUnpkU8,&causeTyp, mBuf,0, pst);
   CMCHKUNPKLOG(SUnpkU32,(&ueId), mBuf,0, pst);
   NB_DAM_FREE_BUFFER(pst->region, mBuf);
   
   relCause.causeTyp = causeTyp;
   relCause.causeVal = causeVal;
   nbSndCtxtRelReq(ueId, &relCause);
}/* cmUnPkDamSendCtxtRel */

PUBLIC S16 cmPkTunDelReq
(
 Pst *pst,
 Void *req
)
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkUeDelReq)

   /* Buffer Allocation */
   if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {

      NB_LOG_ERROR(&nbCb,"Memory allocation failed.");
      RETVALUE(RFAILED);
   }
   CMCHKPKLOG(cmPkPtr,(PTR)req, mBuf, 0, pst);

   pst->event = (Event)EVTDAMTUNDELREQ;
   RETVALUE(SPstTsk(pst, mBuf));
}

PUBLIC Void cmUnPkTunDelReq
(
 Pst *pst,
 Buffer *mBuf
)
{
   Void *tunDelReq = NULLP;
   CMCHKUNPKLOG(cmUnpkPtr,(PTR *)&tunDelReq, mBuf, 0, pst);
   NB_DAM_FREE_BUFFER(pst->region, mBuf);
   nbDamNbTunDelReq(tunDelReq);
}

