/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

/**********************************************************************

    Name:  LTE S1SIM - UE Application Module

    Type:  C ource file

    Desc:  C source code for UE Application

    File:  ue_app.c

    Sid:

    Prg:

**********************************************************************/

#include <stdbool.h>
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* General */
#include "ssi.h"           /* System Services */
#include "cm_tkns.h"       /* common tokens */
#include "cm_hash.h"       /* common structs 1 */
#include "cm_mblk.h"       /* common memory */
#include "cm_llist.h"      /* cm link list */
#include "cm5.h"           /* common structs 3 */
#include "cm_inet.h"       /* common tokens  */
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport */
#include "cm_dns.h"        /* common DNS library */
#include "cm_inet.h"
#include "cm_tpt.h"
#include "lfw.h"
#include "lue.h"
#include "ue_log.h"
#include "ue.h"
#include "ue_emm.h"
#include "ue_esm.h"
#include "ue_emm_esm.h"
#include "ue_app_sec.h"
#include "nbu.h"
#include "rl_interface.h"
#include "rl_common.h"
#include "ue_app.h"

/* Header Include Files (.x) */
#include "gen.x"           /* General */
#include "ssi.x"           /* System Services */
#include "cm_tkns.x"       /* common tokens */
#include "cm_hash.x"       /* common structs 1 */
#include "cm_lib.x"        /* common library */
#include "cm_mblk.x"       /* common memory */
#include "cm_llist.x"      /* cm link list */
#include "cm5.x"           /* common structs 3 */
#include "cm_inet.x"       /* common transport */
#include "cm_tpt.x"        /* common transport */
#include "cm_dns.x"        /* common DNS library */
#include "cm_tkns.x"
#include "cm_tpt.x"
#include "lue.x"
#include "uet.x"
#include "ue.x"            /* S6a Layer */
#include "ue_emm.x"
#include "ue_esm.x"
#include "ue_emm_esm.x"
#include "ue_app_sec.x"
#include "ue_app.x"
#include "nbu.x"
#include "ueAppdbm.x"
#include "tft.h"

EXTERN UeAppCb gueAppCb;

EXTERN S16 ueAppEdmEncode(CmNasEvnt*, NhuDedicatedInfoNAS*);
EXTERN PUBLIC S16 ueSendUeRadCapInd(UeCb*);
EXTERN S16 ueSendToTfwApp(UetMessage*, Pst*);
EXTERN S16 ueSendInitialUeMsg(NbuInitialUeMsg*, Pst*);
EXTERN S16 ueSendUlNasMsgToNb(NbuUlNasMsg*, Pst*);
EXTERN S16 ueSendUlRrcMsgToNb(NbuUlRrcMsg*, Pst*);
EXTERN S16 ueDbmFetchUe(U32, PTR*);
EXTERN S16 ueDbmAddUe(UeCb*);
EXTERN S16 ueDbmDelAllUe(Void);
EXTERN S16 ueDbmInit(Void);
EXTERN S16 ueDbmDeInit(Void);
EXTERN S16 ueAppBldAndSndIpAddrToNb(U8, U8*, U8, Pst*);
EXTERN S16 ueDbmFetchUeWithS_TMSI(UePagingMsg*, PTR*);
EXTERN S16 ueDbmDelUe(UeAppCb*, U32);
EXTERN S16 ueUiProcErabsInfoMsg(Pst*, NbuErabsInfo*);
EXTERN S16 ueAppBldAndSndIpInfoRspToNb(UeCb*, U8, Pst*);
EXTERN S16 ueUiProcRelBearerRsp(UeCb *p_ueCb, NbuRelBearerRsp *);

PUBLIC S16 ueSendErabRelInd(NbuErabRelIndList*, Pst*);
PRIVATE S16 ueProcUeActvDedBerAcc(UetMessage *p_ueMsg,Pst *pst);
PRIVATE S16 ueProcUeDeActvBerAcc(UetMessage *p_ueMsg,Pst *pst);
PRIVATE S16 ueAppUtlBldActDedBerContextReject(UeCb *ueCb, CmNasEvnt **esmEvnt,
                U8 epsBearerId, U8 esmCause);
PRIVATE Void ueAppAuthHexDump
(
U8    *buf,
U16   len
);
PRIVATE S16 ueProcUeActvDedBerRej(UetMessage *p_ueMsg,Pst *pst);
PRIVATE S16 ueAppBuildAndSendActDefltBerContextAccept(UeCb *ueCb, U8 bearerId);
PRIVATE S16 ueAppBuildAndSendActDedBerContextAccept(UeCb *ueCb, U8 bearerId);
PRIVATE S16 ueAppBuildAndSendDeActvBerContextAccept(UeCb *ueCb, U8 bearerId);
PRIVATE S16 ueAppBuildAndSendActDedBerContextReject(UeCb *ueCb, U8 bearerId,U8 esmCause);
PRIVATE S16 ueAppEdmDecode(NhuDedicatedInfoNAS *nasPdu, CmNasEvnt **ueEvnt);
PRIVATE S16 ueAppSendIncActDedBerReqInd(UeCb *ueCb,U8 drbIdx);
PRIVATE S16 ueAppEsmHndlIncActDedBearerReq(UeEsmCb*,CmNasEvnt*,UeCb*,U8);
PRIVATE S16 ueAppUtlBldBearerResAllocReq (CmNasEvnt**,UeUetBearerAllocReq*);
PRIVATE S16 ueProcUeAppConfigReq(UetMessage *pCfgReq, Pst *pst);
PRIVATE S16 ueProcUeConfigReq(UetMessage *pCfgReq, Pst *pst);
PRIVATE S16 sendUeAppCfgCompInd(Void);
PRIVATE S16 sendUeConfigCompInd(Void);
PRIVATE S16 ueAppGetDrb(UeCb *ueCb, U8 *drb);
PRIVATE S16 ueAppUtlBldIdentResp(UeCb*, CmNasEvnt**, UeUetIdentRsp identityRsp);
PRIVATE S16 ueAppUtlBldAuthResp(UeCb*, CmNasEvnt**, CmEmmAuthPrmRES*);
PRIVATE S16 ueAppSndIdentResponse(UeCb *ueCb, UeUetIdentRsp identityRsp);
PRIVATE S16 ueAppSndAuthResponse(UeCb *ueCb, UeSQN sqnRcvd,UeSQN maxSqnRcvd,UeRand randRcvd);
PRIVATE S16 ueProcUeIdentResp(UetMessage *tfwMsg, Pst *pst);
PRIVATE S16 ueProcUeAuthResp(UetMessage *tfwMsg, Pst *pst);
PRIVATE S16 ueAppUtlBldPdnConReq(UeCb *ueCb,
	        CmNasEvnt **esmEvnt, UeEsmProtCfgOpt *protCfgOpt, U32 pdnType, Bool eti);
PRIVATE S16 ueAppUtlBldAttachReq(UeCb*, CmNasEvnt**, UeUetAttachReq ueUetAttachReq);
PRIVATE S16 ueAppEsmHndlOutActDefBearerAcc(UeEsmCb *esmCb, CmNasEvnt *evnt);
PRIVATE S16 ueAppEsmHndlOutActDedBearerAcc(UeEsmCb *esmCb, CmNasEvnt *evnt);
PRIVATE S16 ueAppEsmHndlOutActDedBearerRej(UeEsmCb *esmCb, CmNasEvnt *evnt);
PRIVATE S16 ueAppEsmHndlOutBerResAllocReq(UeEsmCb *esmCb, CmNasEvnt *evnt);
PRIVATE S16 ueAppEsmHndlOutPDNConnectReq(UeEsmCb *esmCb, CmNasEvnt *evnt);
PRIVATE S16 ueAppUtlAddEsmCb(UeEsmCb **esmCb, UeCb *ueCb);
PRIVATE S16 ueAppUtlFndEsmCb(UeEsmCb**, U8, UeAppEsmKeyType, UeCb*);
PRIVATE S16 ueAppEsmHndlInvEvnt(UeEsmCb *esmCb, CmNasEvnt *evnt, UeCb *ueCb);
PRIVATE S16 ueAppEsmHdlOutUeEvnt(CmNasEvnt *evnt, UeCb *ueCb);
PRIVATE S16 ueProcUeAttachReq(UetMessage *p_ueMsg, Pst *pst);
PRIVATE S16 ueAppUtlBldSecModComplete(UeCb *ueCb, UeUetSecModeComplete uetSmc,
            CmNasEvnt **ueEvt);
PRIVATE S16 ueAppUtlBldSecModReject(UeCb *ueCb, CmNasEvnt **ueEvt, U8 cause);
PRIVATE S16 ueAppUtlBldActDefltBerContextAccept(UeCb*, CmNasEvnt**, U8);
PRIVATE S16 ueAppUtlBldActDedBerContextAccept(UeCb*, CmNasEvnt**, U8);
PRIVATE S16 ueAppUtlBldDeActvBerContextAccept(UeCb*, CmNasEvnt**, U8);
PRIVATE S16 ueAppUtlBldActDedBerContextReject(UeCb*, CmNasEvnt**, U8,U8);
PRIVATE S16 ueAppUtlBldAttachComplete(UeCb *ueCb, CmNasEvnt **ueEvt);
PRIVATE S16 ueAppSndAttachComplete(UeCb *ueCb);
PRIVATE S16 ueProcUeAttachComplete(UetMessage *p_ueMsg, Pst *pst);
PRIVATE S16 ueProcUeSecModeCmdComplete(UetMessage *p_ueMsg, Pst *pst);
PRIVATE S16 ueProcUeSecModeRejectCmd(UetMessage *p_ueMsg, Pst *pst);
PRIVATE S16 ueAppSndAuthFailure(UeCb *ueCb);
PRIVATE S16 ueAppEmmHndlInServiceRej(CmNasEvnt *evnt, UeCb *ueCb);
PRIVATE S16 ueAppEmmHndlInDetachAccept(CmNasEvnt *evnt, UeCb *ueCb);
PRIVATE S16 ueAppEmmHndlInIdentReq(CmNasEvnt *evnt, UeCb *ueCb);
PRIVATE S16 ueAppEmmHndlInAuthReq(CmNasEvnt *evnt, UeCb *ueCb);
PRIVATE S16 ueAppEmmHndlInSecModecmd(CmNasEvnt *evnt, UeCb *ueCb);
PRIVATE S16 ueAppEsmHndlIncActDefBearerReq(UeEsmCb*, CmNasEvnt*, UeCb*,U8*,U8);
PRIVATE S16 ueAppEmmHndlInAttachAccept(CmNasEvnt *evnt, UeCb  *ueCb);
EXTERN S16 ueUiProcIpInfoReqMsg(UeCb * p_ueCb, U8 bearerId);
EXTERN S16 ueUiProcIpInfoUpdtMsg(UeCb *p_ueCb, NbuUeIpInfoUpdt *);
PRIVATE S16 ueAppEsmHndlOutEsmInformationRsp(UeEsmCb *esmCb, CmNasEvnt *evnt);
#if 0
PRIVATE S16 handleUeCntxtRcvdIndFromEnb(UeCb *ueCb);
#endif
PRIVATE S16 ueAppUtlBldDetachReq(UeCb*, CmNasEvnt**, U8, U8, U8);
PRIVATE S16 ueSendDetachRequest(UeCb *ueCb, U8 detCause);
PRIVATE S16 ueProcUeDetachRequest(UetMessage *p_ueMsg, Pst *pst);
PRIVATE S16 ueBldIdentReqIndMsgToTfw(UetMessage *tfwMsg, UeCb*, U8);
PRIVATE S16 ueBldAuthReqIndMsgToTfw(UetMessage *tfwMsg, UeCb *ueCb);
PRIVATE S16 ueAppUtlBldAuthFailure(UeCb *ueCb, CmNasEvnt **ueEvt);
PRIVATE S16 ueBldSecModeCmdIndToTfw(UetMessage *tfwMsg, UeCb *ueCb);
PRIVATE S16 ueBldAttachAcceptToTfw(UetMessage *tfwMsg, UeCb *ueCb);
PRIVATE Void updateGutiInUeCb(UeCb *ueCb, CmEmmEpsMI *guti);
PRIVATE S16 compareGutiInUeCb(UeCb *ueCb, CmEmmEpsMI *epsMi);
PRIVATE Void reverse(U8* str);
PRIVATE U8* itoa(int num, U8* str, int base);
PUBLIC Void populateIpInfo(UeCb *ueCb, U8 bearerId, NbuUeIpInfoRsp *);
PRIVATE S16 ueAppRcvEmmMsg(CmNasEvnt *evnt, U8 emmMsgType, UeCb *ueCb);
PRIVATE S16 ueAppUtlMovEsmCbTransToBid(UeEsmCb *esmCb, UeCb *ueCb);
PRIVATE S16 uefillDefEsmInfoToUeCb(UeCb *ueCb, CmNasEvnt*, U8, U8);
PRIVATE S16 ueAppEsmHdlIncUeEvnt(CmNasEvnt*, UeCb*, U8);
PRIVATE S16 ueAppEmmHdlIncUeEvnt(CmNasEvnt *ueEvnt, UeCb *ueCb);
PRIVATE S16 ueProcUeTauRequest(UetMessage *p_ueMsg, Pst *pst);
PRIVATE S16 ueProcUeTauComplete(UetMessage *p_ueMsg, Pst *pst);
PRIVATE S16 ueAppUtlBldTauReq(UeCb *ueCb, CmNasEvnt**, UeUetTauRequest *ueUetTauRequest);
PRIVATE S16 ueAppUtlBldTauComp(UeCb *ueCb, CmNasEvnt **ueEvt);
PRIVATE S16 ueBldTauAcceptToTfw(UetMessage*, CmEmmTAUAccept*, UeCb*);
PRIVATE S16 ueBldAttachRejectIndToTfw(UetMessage*, UeCb*, U8);
PRIVATE S16 ueBldServiceRejectIndToTfw(UetMessage*, UeCb*, U8);
PRIVATE S16 ueBldDetachAcceptIndToTfw(UetMessage*, UeCb*, U8);
PRIVATE S16 ueProcUeAttachFail(UetMessage*, Pst*);
PRIVATE S16 ueAppUtlBldServiceReq(UeCb *ueCb, CmNasEvnt **ueEvt);
PRIVATE S16 ueSendServiceRequest(UeCb *ueCb, U32 mTmsi, U8 rrcCause, Bool noMac);
PRIVATE S16 ueProcUeServiceRequest(UetMessage *p_ueMsg, Pst *pst);
PRIVATE S16 ueAppEmmHndlInAttachReject(CmNasEvnt *evnt, UeCb *ueCb);
PRIVATE S16 ueBldTauRejectIndToTfw(UetMessage *tfwMsg, UeCb *ueCb, U8 cause);
PRIVATE S16 ueAppEmmHndlInTauReject(CmNasEvnt *evnt, UeCb *ueCb);
PRIVATE S16 ueProcUePdnConReq(UetMessage *p_ueMsg,Pst *pst);
PRIVATE S16 ueAppUtlBldStandAlonePdnConReq(CmNasEvnt**, UeUetPdnConReq*);
PRIVATE S16 ueUiBldAndSendPagingInfo(UeCb*, UePagingMsg*);
PUBLIC S16 ueUiProcPagingMsg(UePagingMsg*, Pst*);
PUBLIC S16 ueUiProcessTfwMsg(UetMessage*, Pst*);
PUBLIC S16 ueUiProcessNbMsg(NbuDlNasMsg*, Pst*);
PRIVATE S16 ueProcUeBearResAllocReq(UetMessage *p_ueMsg,Pst *pst);
PRIVATE S16 ueAppFillLinkedBrIdAndSendErabRelInd(UeCb *ueCb, UeErabRelInd *pErabRel);
PRIVATE S16 ueAppEmmHndlInEmmInformation(CmNasEvnt *evnt, UeCb *ueCb);
PRIVATE S16 ueBldEmmInformationToTfw(UetMessage *tfwMsg, UeCb *ueCb);
PRIVATE S16 ueAppEmmHndlInAuthReject(CmNasEvnt *evnt, UeCb *ueCb);
PRIVATE S16 ueBldAuthRejToTfw(UetMessage *tfwMsg, UeCb *ueCb);
PRIVATE S16 ueAppEsmHndlIncDeActvBearerReq(UeEsmCb*,CmNasEvnt*,UeCb*,U8);
PRIVATE S16 ueAppSendIncDeActvBerReqInd(UeCb *ueCb,U8 bId);
PRIVATE S16 ueProcUeEsmInformationRsp(UetMessage *p_ueMsg, Pst *pst);
PRIVATE S16 ueAppEsmHndlIncEsmInfoReq(UeEsmCb *esmCb, CmNasEvnt *evnt, UeCb *ueCb);
PRIVATE S16 ueAppUtlBldEsmInformationRsp(CmNasEvnt **esmEvnt, UeUetEsmInformationRsp  *ueEsmInformationRsp);
PRIVATE S16 ueProcUePdnDisconnectReq(UetMessage *p_ueMsg,Pst *pst);
PRIVATE S16 ueAppUtlBldStandAlonePdnDisconnectReq(
  CmNasEvnt **esmEvnt,
  UeUetPdnDisconnectReq *ueUetPdnDisConReq);
PRIVATE S16 ueAppEsmHndlOutPDNDisConnectReq(UeEsmCb *esmCb, CmNasEvnt *evnt);
PRIVATE S16 ueAppEsmHndlIncPdnDisconRej(UeEsmCb *esmCb,CmNasEvnt *evnt,
  UeCb *ueCb);
void ueSendErabSetupRspForFailedBearers(NbuErabsInfo *pNbuErabsInfo);
PRIVATE S16 ueProcUeStandAloneActvDfltBerCtxtRej(UetMessage *p_ueMsg, Pst *pst);
PRIVATE S16 ueAppBuildAndSendActDefltBerContextReject(UeCb *ueCb, U8 bearerId);

PRIVATE S16 ueProcDropActDefaultEpsBerCtxtReq(UetMessage *p_ueMsg, Pst *pst);
PRIVATE S16 ueAppGetDrb(UeCb *ueCb, U8 *drb)
{
   U8  idx;

   /* drb id can range between 1..32 */
   for(idx = 1; idx < UE_APP_MAX_DRBS; idx++)
   {
      if (ueCb->drbs[idx] == UE_APP_DRB_AVAILABLE)
      {
         *drb = idx;
         ueCb->drbs[idx] = UE_APP_DRB_INUSE;
         RETVALUE(ROK);
      }
   }
   RETVALUE(RFAILED);
}

/*
 *
 *       Fun:   ueAppUtlBldIdentResp
 *
 *       Desc:  Builds Identity Response message.
 *
 *       Ret:   ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppUtlBldIdentResp
(
   UeCb *ueCb,
   CmNasEvnt **ueEvt,
   UeUetIdentRsp identityRsp
)
{
   CmEmmIdRsp *identRsp;
   CmEmmMsg* emmMsg;
   UeAppCb *ueAppCb;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Building an Identity Response for UE");

   if (ueEvt == NULLP)
   {
      RETVALUE(RFAILED);
   }

   /* Allocate memory for pdu */
   CM_ALLOC_NASEVNT (ueEvt, CM_EMM_PD);

   if (*ueEvt == NULLP)
   {
      RETVALUE(RFAILED);
   }

   if (cmGetMem(&((*ueEvt)->memCp), sizeof(CmEmmMsg), (Ptr *)&emmMsg) != ROK)
   {
      CM_FREE_NASEVNT(ueEvt);
      RETVALUE(RFAILED);
   }

   (*ueEvt)->m.emmEvnt = emmMsg;
   identRsp = &((*ueEvt)->m.emmEvnt->u.idRsp);

   /* Fill header information*/
   if (UE_APP_SEC_CTXT_CRNT == ueCb->secCtxt.status)
   {
      (*ueEvt)->secHT = CM_NAS_SEC_HDR_TYPE_INT_PRTD;
   }

   /* Security header type is "Plain NAS message, not security protected" */
   emmMsg->protDisc = CM_EMM_PD;
   emmMsg->secHdrType = CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG;
   emmMsg->msgId = CM_EMM_MSG_ID_RSP;

   /* Fill mandatory IEs */
   switch (identityRsp.idType)
   {
      case CM_EMM_MID_TYPE_IMSI:
      {
         UE_LOG_DEBUG(ueAppCb, "Filling IMSI in Identity Response");
         identRsp->msId.pres = TRUE;
         identRsp->msId.type = CM_EMM_MID_TYPE_IMSI;
         identRsp->msId.len = ueCb->ueCtxt.imsiLen;
         identRsp->msId.evenOddInd = (((identRsp->msId.len) % 2) != 0) ? \
                                       (UE_ODD):(UE_EVEN);
         cmMemcpy((U8 *)&identRsp->msId.u.imsi.id,
                  (U8 *)&ueCb->ueCtxt.ueImsi, identRsp->msId.len);
         break;
      }
      case CM_EMM_MID_TYPE_IMEI:
      {
         UE_LOG_DEBUG(ueAppCb, "Filling IMEI in Identity Response");
         identRsp->msId.pres = TRUE;
         identRsp->msId.type = CM_EMM_MID_TYPE_IMEI;
         identRsp->msId.len = CM_EMM_MAX_IMEI_DIGS;
         identRsp->msId.evenOddInd = (((identRsp->msId.len) % 2) != 0) ? \
                                       (UE_ODD):(UE_EVEN);
         cmMemcpy((U8 *)&identRsp->msId.u.imei.id,
                  (U8 *)&ueCb->ueCtxt.ueImei, identRsp->msId.len);
         break;
      }
      case CM_EMM_MID_TYPE_IMEISV:
      {
         UE_LOG_DEBUG(ueAppCb, "Filling IMEISV in Identity Response");
         identRsp->msId.pres = TRUE;
         identRsp->msId.type = CM_EMM_MID_TYPE_IMEISV;
         identRsp->msId.len = CM_EMM_MAX_IMEI_DIGS;
         identRsp->msId.evenOddInd = (((identRsp->msId.len) % 2) != 0) ? \
                                       (UE_ODD):(UE_EVEN);
         if (!identityRsp.idValPres) {
           cmMemcpy((U8 *)&identRsp->msId.u.imei.id,
                    (U8 *)&ueCb->ueCtxt.ueImei, identRsp->msId.len);
         } else {
           cmMemcpy((U8 *)&identRsp->msId.u.imei.id,
                    identityRsp.idVal, identRsp->msId.len);
         }
         break;
      }

      default:
      {
         UE_LOG_ERROR(ueAppCb, "Invalid idType");
         RETVALUE(RFAILED);
      }
   }

   RETVALUE(OK);
}

/*
 *
 *       Fun: ueAppUtlBldAuthResp
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppUtlBldAuthResp
(
 UeCb *ueCb,
 CmNasEvnt **ueEvt,
 CmEmmAuthPrmRES *authParmRes
)
{
   UeAppCb *ueAppCb = NULLP;
   CmEmmAuthRsp  *authRsp = NULLP;
   CmEmmMsg *emmMsg = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Building Authentication response");

   if(ueEvt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /* Allocate memory for pdu */
   CM_ALLOC_NASEVNT (ueEvt, CM_EMM_PD);

   if(*ueEvt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   if (cmGetMem(&((*ueEvt)->memCp), sizeof(CmEmmMsg), (Ptr *)&emmMsg) != ROK)
   {
      CM_FREE_NASEVNT(ueEvt);
      RETVALUE(RFAILED);
   }

   (*ueEvt)->m.emmEvnt = emmMsg;
   authRsp = &((*ueEvt)->m.emmEvnt->u.authRsp);

   /* Fill header information*/

   /* Security header type is "Plain NAS message, not security protected" */
   emmMsg->secHdrType = CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG;
   emmMsg->protDisc = CM_EMM_PD;
   emmMsg->msgId = CM_EMM_MSG_AUTH_RSP;

   /* Fill mandatory IEs */
   /* Auth response parameter*/
   cmMemcpy((U8 *)&authRsp->RES, (U8 *)authParmRes, sizeof(CmEmmAuthPrmRES));

   RETVALUE(ROK);
}

/*
 *
 *       Fun:   ueAppSndIdentResponse
 *
 *       Desc:  Builds, Encodes & sends Identity Response message to enbApp.
 *
 *       Ret:   ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppSndIdentResponse(UeCb *ueCb, UeUetIdentRsp identityRsp)
{
   U8                   isPlainMsg   = TRUE;
   S16                  ret          = ROK;
   UeAppCb              *ueAppCb;
   UeAppMsg             srcMsg;
   UeAppMsg             dstMsg;
   CmNasEvnt            *identRspEvnt = NULLP;
   NbuUlNasMsg          *pUlNbMsg    = NULLP;
   NhuDedicatedInfoNAS  nasEncPdu;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Preparing Identity Response for ueId(%d), idType(%d)",
                ueCb->ueId, identityRsp.idType);

   ret = ueAppUtlBldIdentResp(ueCb, &identRspEvnt, identityRsp);
   if (ROK != ret)
   {
      UE_LOG_DEBUG(ueAppCb, "Could not build Identity Response message");
      RETVALUE(ret);
   }

   /* NB message filling */
   pUlNbMsg = (NbuUlNasMsg *)ueAlloc(sizeof(NbuUlNasMsg));

   /* Encoding Nas PDU */
   ret = ueAppEdmEncode(identRspEvnt, &nasEncPdu);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Identity Response message Encode Failed");
      CM_FREE_NASEVNT(&identRspEvnt);
      RETVALUE(ret);
   }

   /* Integrity Protected */
   if (CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG != identRspEvnt->secHT)
   {
      isPlainMsg = FALSE;
      srcMsg.val = nasEncPdu.val;
      srcMsg.len = nasEncPdu.len;
      ret = ueAppCmpUplnkSec(&ueCb->secCtxt, identRspEvnt->secHT, &srcMsg,
                             &dstMsg);
      if (ROK != ret)
      {
         UE_LOG_ERROR(ueAppCb, "Uplink Security Failed");
         identRspEvnt->pdu = NULLP;
         CM_FREE_NASEVNT(&identRspEvnt);
         EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
         RETVALUE(ret);
      }

      EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
      nasEncPdu.val = dstMsg.val;
      nasEncPdu.len = dstMsg.len;
   }
   CM_FREE_NASEVNT(&identRspEvnt);

   pUlNbMsg->ueId = ueCb->ueId;
   pUlNbMsg->nasPdu.pres = TRUE;
   pUlNbMsg->nasPdu.len = nasEncPdu.len;

   pUlNbMsg->nasPdu.val = (U8 *)ueAlloc(pUlNbMsg->nasPdu.len);
   cmMemcpy((U8 *)pUlNbMsg->nasPdu.val, (U8 *)nasEncPdu.val,
            pUlNbMsg->nasPdu.len);

   if (isPlainMsg)
   {
      EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
   }

   UE_LOG_DEBUG(ueAppCb, "Sending Identity Response to enbApp");
   ret = ueSendUlNasMsgToNb(pUlNbMsg, &ueAppCb->nbPst);
   if (ret != ROK)
   {
      UE_LOG_DEBUG(ueAppCb, "Could not send the Identity Response");
      RETVALUE(RFAILED);
   }

   RETVALUE(ret);
}

/*
 *
 *       Fun: ueAppSndAuthResponse
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppSndAuthResponse(UeCb *ueCb, UeSQN sqnRcvd,UeSQN maxSqnRcvd,UeRand randRcvd)
{
   U8                   isPlainMsg   = TRUE;
   S16                  ret          = ROK;
   UeAppCb              *ueAppCb = NULLP;
   UeAppMsg             srcMsg;
   UeAppMsg             dstMsg;
   CmNasEvnt            *authRspEvnt = NULLP;
   CmEmmAuthPrmRES      authParmRes;
   NbuUlNasMsg          *pUlNbMsg    = NULLP;
   NhuDedicatedInfoNAS  nasEncPdu;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Authenticating the MME");
   ret = ueUsimGenAuthRsp(&ueCb->ueInfo,
         &ueCb->ueAuthKeys,
         sqnRcvd,
         ueCb->srvPlmn,
         ueCb->res.val,
         ueCb->secCtxt.kasme,
         &ueCb->authFlr.cause.cause,
         ueCb->authFlr.failrPrm.authFailPrm,
         maxSqnRcvd);

   if (ROK != ret)
   {
      UE_LOG_DEBUG(ueAppCb, "Authentication Failed, Failure cause is %d",
            ueCb->authFlr.cause.cause);
      printf("Authentication Failed, Failure cause is %d\n",
            ueCb->authFlr.cause.cause);
      ueCb->authFlr.cause.pres = TRUE;
      if(UE_APP_USIM_SYNC_FAILURE == ueCb->authFlr.cause.cause)
      {
         ueCb->authFlr.failrPrm.pres = TRUE;
         ueCb->authFlr.failrPrm.len = UE_AUTS_SIZE;
      }
      ret = ueAppSndAuthFailure(ueCb);
      if (ret != ROK)
      {
         UE_LOG_ERROR(ueAppCb, "Sending Authentication Failure "\
               "message to ENB failed");
      }
      RETVALUE(ret);
   }

   UE_LOG_DEBUG(ueAppCb, "Sending Authentication response");

   /* Fill authParmRes */
   cmMemset((U8*)&authParmRes, 0, sizeof(CmEmmAuthPrmRES));
   authParmRes.pres = TRUE;
   authParmRes.len = 16;
   if(randRcvd.pres == TRUE)
   {
      U8 ak[UE_USIM_AK_SIZE] = {0};
      U8 ck[UE_USIM_CK_SIZE] = {0};
      U8 ik[UE_USIM_IK_SIZE] = {0};
      U8 res[CM_EMM_MAX_RES] = {0};
      ueUsimCalcAuthKeys(&ueCb->ueInfo, &ueCb->ueAuthKeys,
      res, ueCb->ueAuthKeys.autn,
      randRcvd.val,ak,ck,ik);
      /* copy random genearted string */
      cmMemcpy(authParmRes.val,res, 16);
   }
   else
   {
      cmMemcpy(authParmRes.val, ueCb->res.val, 16);
   }

   ret = ueAppUtlBldAuthResp(ueCb, &authRspEvnt, &authParmRes);
   if(ROK != ret)
   {
      UE_LOG_DEBUG(ueAppCb, "Could not Build the Authentication response");
      RETVALUE(ret);
   }

   /* NB message filliing */
   pUlNbMsg = (NbuUlNasMsg *)ueAlloc(sizeof(NbuUlNasMsg));
   /* Encoding Nas PDU */
   ret = ueAppEdmEncode(authRspEvnt, &nasEncPdu);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Authentication Response message Encode Failed");
      CM_FREE_NASEVNT(&authRspEvnt);
      RETVALUE(ret);
   }

   /** Integrity Protected **/
   if(CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG != authRspEvnt->secHT)
   {
      isPlainMsg = FALSE;
      srcMsg.val = nasEncPdu.val;
      srcMsg.len = nasEncPdu.len;
      ret = ueAppCmpUplnkSec(&ueCb->secCtxt, authRspEvnt->secHT, &srcMsg,
            &dstMsg);
      if(ROK != ret)
      {
         UE_LOG_ERROR(ueAppCb, "Uplink Security Failed");
         authRspEvnt->pdu = NULLP;
         CM_FREE_NASEVNT(&authRspEvnt);
         EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
         RETVALUE(ret);
      }
      EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
      nasEncPdu.val = dstMsg.val;
      nasEncPdu.len = dstMsg.len;
   }
   CM_FREE_NASEVNT(&authRspEvnt);

   pUlNbMsg->ueId = ueCb->ueId;
   pUlNbMsg->nasPdu.pres = TRUE;
   pUlNbMsg->nasPdu.len = nasEncPdu.len;

   pUlNbMsg->nasPdu.val = (U8 *)ueAlloc(pUlNbMsg->nasPdu.len);
   cmMemcpy((U8 *)pUlNbMsg->nasPdu.val, (U8 *)nasEncPdu.val,
         pUlNbMsg->nasPdu.len);

   if(isPlainMsg)
   {
      EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
   }
   ret = ueSendUlNasMsgToNb(pUlNbMsg,&ueAppCb->nbPst);
   if (ret != ROK)
   {
      UE_LOG_DEBUG(ueAppCb, "Could not Send the Authentication response.\n");
      RETVALUE(RFAILED);
   }
   RETVALUE(ret);
}

/*
 *
 *       Fun:   ueProcUeIdentResp
 *
 *       Desc:  Processes request from TFW to send Identity Response message.
 *
 *       Ret:   ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueProcUeIdentResp(UetMessage *tfwMsg, Pst *pst)
{
   S16 ret = ROK;
   U32 ueId;
   UeAppCb *ueAppCb = NULLP;
   UeCb *ueCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   ueId = tfwMsg->msg.ueUetIdentRsp.ueId;

   /* Fetching the UeCb */
   ret = ueDbmFetchUe(ueId, (PTR*)&ueCb);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "UeCb List NULL ueId = %d", ueId);
      RETVALUE(ret);
   }

   ret = ueAppSndIdentResponse(ueCb, tfwMsg->msg.ueUetIdentRsp);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb,
                   "Could not send the Ident Response message to eNodeB");
      RETVALUE(ret);
   }

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueProcUeAuthResp
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueProcUeAuthResp(UetMessage *tfwMsg, Pst *pst)
{
   S16 ret = ROK;
   U32 ueId;
   UeSQN sqnRcvd    = {0};
   UeSQN maxSqnRcvd = {0};
   UeRand randRcvd  = {0};

   UeAppCb *ueAppCb = NULLP;
   UeCb *ueCb = NULLP;
   UE_GET_CB(ueAppCb);

   UE_LOG_ENTERFN(ueAppCb);
   ueId = tfwMsg->msg.ueUetAuthRsp.ueId;

   /* Fetching the UeCb */
   ret = ueDbmFetchUe(ueId, (PTR*)&ueCb);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "UeCb List NULL ueId = %d", ueId);
      RETVALUE(ret);
   }
   if(tfwMsg->msg.ueUetAuthRsp.nonEPSAuthFail == TRUE)
   {
      ueCb->authFlr.cause.cause = UE_APP_USIM_NON_EPS_AUTH_FAIL;
      UE_LOG_DEBUG(ueAppCb, "Authentication Failed, Failure cause is %d",
	   ueCb->authFlr.cause.cause);
      ueCb->authFlr.cause.pres = TRUE;
      ueCb->authFlr.failrPrm.pres = TRUE;
      ueCb->authFlr.failrPrm.len = UE_AUTS_SIZE;
      ret = ueAppSndAuthFailure(ueCb);
      if (ret != ROK)
      {
         UE_LOG_ERROR(ueAppCb, "Sending Authentication Failure "\
               "message to ENB failed");
      }
      RETVALUE(ret);
   }
   if(tfwMsg->msg.ueUetAuthRsp.sqnRcvd.pres == TRUE)
   {
      sqnRcvd.pres = TRUE;
      cmMemcpy(sqnRcvd.sqn, tfwMsg->msg.ueUetAuthRsp.sqnRcvd.sqn, 6);
      UE_LOG_DEBUG(ueAppCb, "SQN-RECEIVED FROM TEST STUB");
      ueAppAuthHexDump(sqnRcvd.sqn, 6);
   }
   else
   {
      sqnRcvd.pres = FALSE;
      cmMemcpy(sqnRcvd.sqn, ueCb->ueAuthKeys.sqnRcvd, 6);
   }
   if(tfwMsg->msg.ueUetAuthRsp.maxSqnRcvd.pres == TRUE)
   {
      maxSqnRcvd.pres = TRUE;
      cmMemcpy(maxSqnRcvd.sqn, tfwMsg->msg.ueUetAuthRsp.maxSqnRcvd.sqn, 6);
      UE_LOG_DEBUG(ueAppCb, "HIGH-SQN-RECEIVED FROM TEST STUB");
      ueAppAuthHexDump(maxSqnRcvd.sqn, 6);
   }
   else
   {
      maxSqnRcvd.pres = FALSE;
   }
   if(tfwMsg->msg.ueUetAuthRsp.maxSqnRcvd.pres == TRUE)
   {
      maxSqnRcvd.pres = TRUE;
      cmMemcpy(maxSqnRcvd.sqn, tfwMsg->msg.ueUetAuthRsp.maxSqnRcvd.sqn, 6);
      UE_LOG_DEBUG(ueAppCb, "HIGH-SQN-RECEIVED FROM TEST STUB");
      ueAppAuthHexDump(maxSqnRcvd.sqn, 6);
   }
   else
   {
      maxSqnRcvd.pres = FALSE;
   }
   if(tfwMsg->msg.ueUetAuthRsp.randRcvd.pres == TRUE)
   {
      randRcvd.pres = TRUE;
      randRcvd.val  =  tfwMsg->msg.ueUetAuthRsp.randRcvd.val;
      UE_LOG_DEBUG(ueAppCb, "RAND RECEIVED FROM TEST STUB");
      ueAppAuthHexDump(tfwMsg->msg.ueUetAuthRsp.randRcvd.val, 16);
   }
   if (sqnRcvd.pres){
   for (int i = 0; i < 6; i++) {
   }
   } else {
   }

   if (maxSqnRcvd.pres){
   for (int i = 0; i < 6; i++) {
   }
   } else {
   }
   ret = ueAppSndAuthResponse(ueCb, sqnRcvd,maxSqnRcvd,randRcvd);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Could not send the Auth Response message to "\
            "eNodeB");
      RETVALUE(ret);
   }
   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueProcUeAuthFailure
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueProcUeAuthFailure(UetMessage *tfwMsg, Pst *pst) {
  S16 ret = ROK;
  U32 ueId;

  UeAppCb *ueAppCb = NULLP;
  UeCb *ueCb = NULLP;
  UE_GET_CB(ueAppCb);

  UE_LOG_ENTERFN(ueAppCb);
  ueId = tfwMsg->msg.ueUetAuthFailure.ueId;

  /* Fetching the UeCb */
  ret = ueDbmFetchUe(ueId, (PTR *)&ueCb);
  if (ret != ROK) {
    UE_LOG_ERROR(ueAppCb, "UeCb List NULL ueId = %d", ueId);
    RETVALUE(ret);
  }
  ueCb->authFlr.cause.cause = tfwMsg->msg.ueUetAuthFailure.cause;
  UE_LOG_DEBUG(ueAppCb, "Authentication Failed, Failure cause is %d",
               ueCb->authFlr.cause.cause);
  ueCb->authFlr.cause.pres = TRUE;
  ueCb->authFlr.failrPrm.pres = TRUE;
  ueCb->authFlr.failrPrm.len = UE_AUTS_SIZE;
  ret = ueAppSndAuthFailure(ueCb);
  if (ret != ROK) {
    UE_LOG_ERROR(ueAppCb,
                 "Sending Authentication Failure "
                 "message to ENB failed");
  }
  UE_LOG_EXITFN(ueAppCb, ret);
  RETVALUE(ret);
}
/*
 *
 *       Fun: ueAppEdmDecode
 *
 *       Desc: This function decodes NAS message received from eNodeB.
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppEdmDecode
(
 NhuDedicatedInfoNAS *nasPdu,
 CmNasEvnt **ueEvnt
)
{
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Decoding the received EDM event");

   /* check the protocol discriminator and call respective decoder */
   switch (nasPdu->val[0] & 0x0f)
   {
      case CM_EMM_PD:
         {
            RETVALUE(cmEmmDecMsg(nasPdu->val, ueEvnt, nasPdu->len));
         }
      case CM_ESM_PD:
         {
            RETVALUE(cmEsmDecMsg(nasPdu->val, ueEvnt, nasPdu->len));
         }
      default:
         {
            UE_LOG_ERROR(ueAppCb, "Unknown PD(%x) in NAS message",
                  nasPdu->val[0] & 0x0f);
            RETVALUE(RFAILED);
         }
   }

   RETVALUE(ROK);
}

PRIVATE S16 encode_apn
(
 CmEsmAccessPtName *dst_apn,
 UeEmmNasPdnApn *src_apn
)
{
   U8 *str = malloc(src_apn->len);
   U8  idx = 0;
   U8  str_len = 0;
   memset(str,0,src_apn->len);
#define APN_FIRST_LABEL_LEN_PLACE_HOLDER 1
   U8 *temp_apn = malloc(src_apn->len +
		         APN_FIRST_LABEL_LEN_PLACE_HOLDER);
   memset(temp_apn,0,src_apn->len +
	                 APN_FIRST_LABEL_LEN_PLACE_HOLDER);
   for (str = strtok(src_apn->apn,"."); str != NULL;
        str = strtok(NULL, "."))
   {
      str_len = strlen(str);
      temp_apn[idx] = str_len;
      ++idx;
      strcat(&temp_apn[idx], str);
      idx += str_len;
   }
   cmMemcpy((U8 *)&dst_apn->apn[0],temp_apn,strlen(temp_apn));
   dst_apn->len    =  strlen(&dst_apn->apn);

   RETVALUE(RFAILED);
}

PRIVATE S16 ueAppUtlBldStandAlonePdnConReq(CmNasEvnt **esmEvnt,
                                           UeUetPdnConReq *ueUetPdnConReq)
{
  CmEsmMsg *msg = NULLP;
  printf("Building PDN Connection Request\n");

  if (esmEvnt == NULLP) {
    RETVALUE(RFAILED);
  }

  /* Allocate memory for mme evnt */
  CM_ALLOC_NASEVNT(esmEvnt, CM_ESM_PD);
  if (*esmEvnt == NULLP) {
    RETVALUE(RFAILED);
  }

  /*Allocate memory for ESM message*/
  if (cmGetMem(&(*esmEvnt)->memCp, sizeof(CmEsmMsg), (Ptr *)&msg) != ROK) {
    CM_FREE_NASEVNT(esmEvnt);
    RETVALUE(RFAILED);
  }

  msg->protDisc = CM_ESM_PD;
  (*esmEvnt)->m.esmEvnt = msg;

  (*esmEvnt)->secHT = CM_NAS_SEC_HDR_TYPE_INT_PRTD_ENC;
  /* Fill ESM PDN connectivity request message */

  /*Fill mandatory IE's*/
  /* EPS barer ID IE*/
  msg->bearerId = 0;

  /* PDN connectivity request message idenmtity*/
  msg->msgType = CM_ESM_MSG_PDN_CONN_REQ;

  /* Request type IE*/
  msg->u.conReq.reqType.pres = TRUE;
  msg->u.conReq.reqType.val = CM_ESM_REQTYPE_INIT;
  /* PDN type IE*/
  msg->u.conReq.pdnType.pres = TRUE;
  msg->u.conReq.pdnType.val = ueUetPdnConReq->pdnType;

  if (ueUetPdnConReq->nasPdnApn.len != 0) {
    msg->u.conReq.apn.pres = TRUE;
    encode_apn(&msg->u.conReq.apn, &ueUetPdnConReq->nasPdnApn);
  } else {
    msg->u.conReq.apn.pres = FALSE;
  }
  /* protocol configuration options */
  if (ueUetPdnConReq->protCfgOpt.pres == TRUE) {
    cmMemcpy(&msg->u.conReq.protCfgOpt, &ueUetPdnConReq->protCfgOpt,
             sizeof(ueUetPdnConReq->protCfgOpt));
  }
  RETVALUE(ROK);
}

/*
 *
 *       Fun:   ueAppUtlBldPdnConReq
 *
 *       Desc:  Build PDN Connectivity Request.
 *
 *       Ret:   ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppUtlBldPdnConReq
(
 UeCb *ueCb,
 CmNasEvnt **esmEvnt,
 UeEsmProtCfgOpt *protCfgOpt,
 U32   pdnType,
 Bool eti
)
{
   CmEsmMsg *msg = NULLP;
   UeAppCb *ueAppCb = NULLP;
   U8 count;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Building PDN Connection Request for UE");

   if (ueCb == NULLP || esmEvnt == NULLP)
   {
      RETVALUE(RFAILED);
   }

   /* Allocate memory for mme evnt */
   CM_ALLOC_NASEVNT (esmEvnt, CM_ESM_PD);
   if (*esmEvnt == NULLP)
   {
      RETVALUE(RFAILED);
   }

   /*Allocate memory for ESM message*/
   if (cmGetMem(&(*esmEvnt)->memCp, sizeof(CmEsmMsg), (Ptr *)&msg) != ROK)
   {
      CM_FREE_NASEVNT(esmEvnt);
      RETVALUE(RFAILED);
   }

   msg->protDisc = CM_ESM_PD;
   (*esmEvnt)->m.esmEvnt = msg;

   (*esmEvnt)->secHT = CM_NAS_SEC_HDR_TYPE_INT_PRTD_ENC;

   /* Fill ESM PDN connectivity request message */

   /*Fill mandatory IE's*/
   /* EPS barer ID IE*/
   msg->bearerId = 0;

   /* Procedure transaction identity IE*/
   msg->prTxnId  = 0;

   /* PDN connectivity request message idenmtity*/
   msg->msgType  = CM_ESM_MSG_PDN_CONN_REQ;

   /* Request type IE*/
   msg->u.conReq.reqType.pres = TRUE;
   msg->u.conReq.reqType.val = CM_ESM_REQTYPE_INIT;

   /* PDN type IE*/
   msg->u.conReq.pdnType.pres = TRUE;
   msg->u.conReq.pdnType.val = pdnType;

   /*ESM Information Transfer Flag*/
   if (eti == 1) {
     msg->u.conReq.infoTransFlg.pres = TRUE;
     msg->u.conReq.infoTransFlg.val = eti;
   } else {
     msg->u.conReq.infoTransFlg.pres = FALSE;
   }

   /* protocol configuration options */
   if(protCfgOpt->pres == TRUE)
   {
      msg->u.conReq.protCfgOpt.pres = TRUE;
      msg->u.conReq.protCfgOpt.cfgProt = protCfgOpt->cfgProt;
      msg->u.conReq.protCfgOpt.ext = protCfgOpt->ext;
      msg->u.conReq.protCfgOpt.numProtId = protCfgOpt->numProtId;
      msg->u.conReq.protCfgOpt.numContId = protCfgOpt->numContId;

     for (count=0;count<protCfgOpt->numProtId;count ++)
     {
  	msg->u.conReq.protCfgOpt.p[count].pid = protCfgOpt->p[count].pid;
  	msg->u.conReq.protCfgOpt.p[count].len = protCfgOpt->p[count].len;
	cmMemcpy(msg->u.conReq.protCfgOpt.p[count].val,
		   protCfgOpt->p[count].val,
		   protCfgOpt->p[count].len);
     }
     for (count=0;count<protCfgOpt->numContId;count ++)
     {
  	msg->u.conReq.protCfgOpt.c[count].cid = protCfgOpt->c[count].cid;
  	msg->u.conReq.protCfgOpt.c[count].len = protCfgOpt->c[count].len;
	cmMemcpy(msg->u.conReq.protCfgOpt.c[count].val,
		   protCfgOpt->c[count].val,
		   protCfgOpt->c[count].len);
      }
   }

   RETVALUE(ROK);
}

/*
 *
 *       Fun:   ueAppUtlBldAttachReq
 *
 *       Desc:  Builds ATTACH REQUEST message.
 *
 *       Ret:   ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppUtlBldAttachReq(UeCb *ueCb, CmNasEvnt **ueEvt,
                                 UeUetAttachReq ueUetAttachReq) {
  S16 ret = ROK;
  UeAppCb *ueAppCb = NULLP;
  CmEmmAttachRequest *attachReq = NULLP;
  CmEmmMsg *emmMsg;
  U8 mIdType, useOldSecCtxt, epsAttachType, pdnType;
  UeEmmNasAddUpdType *addUpdType;
  UeEsmProtCfgOpt *protCfgOpt;
  UeEmmDrxPrm *drxParm;
  Bool eti = FALSE;
  U8 imsi[15] = {0};
  U8 imsi_len = 0;

  mIdType = ueUetAttachReq.mIdType;
  useOldSecCtxt = ueUetAttachReq.useOldSecCtxt;
  addUpdType = &(ueUetAttachReq.addUpdType);
  protCfgOpt = &(ueUetAttachReq.protCfgOpt);
  drxParm = &(ueUetAttachReq.drxParm);
  epsAttachType = ueUetAttachReq.epsAtchType.type;
  pdnType = ueUetAttachReq.pdnType;
  eti = ueUetAttachReq.eti;
  imsi_len = ueUetAttachReq.imsi_len;
  cmMemcpy(imsi, ueUetAttachReq.imsi, imsi_len);

  UE_GET_CB(ueAppCb);
  UE_LOG_ENTERFN(ueAppCb);

  UE_LOG_DEBUG(ueAppCb, "Building Attach Request for ueId(%d)"
               "useOldSecCtxt=%d", ueCb->ueId, useOldSecCtxt);

  if (ueEvt == NULLP) {
    UE_LOG_ERROR(ueAppCb, "ueEvnt NULL Pointer!!!");
    RETVALUE(RFAILED);
  }
  // Allocate memory for pdu
  CM_ALLOC_NASEVNT(ueEvt, CM_EMM_PD);

  if (*ueEvt == NULLP) {
    UE_LOG_ERROR(ueAppCb, "ueEvnt NULL Pointer!!!");
    RETVALUE(RFAILED);
  }

  if (cmGetMem(&((*ueEvt)->memCp), sizeof(CmEmmMsg), (Ptr *)&emmMsg) != ROK) {
    CM_FREE_NASEVNT(ueEvt);
    RETVALUE(RFAILED);
  }

  (*ueEvt)->m.emmEvnt = emmMsg;
  attachReq = &((*ueEvt)->m.emmEvnt->u.atchReq);

  // Fill header information
  if (UE_APP_SEC_CTXT_CRNT == ueCb->secCtxt.status) {
    (*ueEvt)->secHT = CM_NAS_SEC_HDR_TYPE_INT_PRTD;
  }

  // Security header type is "Plain NAS message, not security protected"
  emmMsg->protDisc = CM_EMM_PD;
  emmMsg->secHdrType = CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG;
  emmMsg->msgId = CM_EMM_MSG_ATTACH_REQ;

  // Fill mandatory IEs
  // EPS attach type IE
  attachReq->epsAtchType.pres = TRUE;
  attachReq->epsAtchType.type = epsAttachType;

  // NAS key set identifier IE
  attachReq->nasKsi.pres = TRUE;
  attachReq->nasKsi.id = CM_EMM_NONAS_KEY_AVAILABLE;
  attachReq->nasKsi.tsc = CM_EMM_NASKEYSID_NATIVE_SEC;

  switch (mIdType) {
    case CM_EMM_MID_TYPE_IMSI: {
      // Fill Mobile Id
      attachReq->epsMi.pres = TRUE;
      attachReq->epsMi.type = CM_EMM_MID_TYPE_IMSI;
      if (imsi_len == 0) {
        attachReq->epsMi.len = ueCb->ueCtxt.imsiLen;
        attachReq->epsMi.evenOddInd =
            (((attachReq->epsMi.len) % 2) != 0) ? (UE_ODD) : (UE_EVEN);
        cmMemcpy((U8 *)&attachReq->epsMi.u.imsi.id, (U8 *)&ueCb->ueCtxt.ueImsi,
                 attachReq->epsMi.len);
      } else {
        attachReq->epsMi.len = imsi_len;
        attachReq->epsMi.evenOddInd =
            (((imsi_len) % 2) != 0) ? (UE_ODD) : (UE_EVEN);
        cmMemcpy((U8 *)&attachReq->epsMi.u.imsi.id, imsi, attachReq->epsMi.len);
      }
      break;
    }
    case CM_EMM_MID_TYPE_GUTI: {
      if (useOldSecCtxt) {
        // Fill old ksi from UeCb
        attachReq->nasKsi.id = ueCb->secCtxt.ksi;
        attachReq->nasKsi.tsc = ueCb->secCtxt.tsc;
      }

      // Fill Mobile Id
      attachReq->epsMi.pres = TRUE;
      attachReq->epsMi.type = CM_EMM_MID_TYPE_GUTI;
      attachReq->epsMi.evenOddInd = UE_EVEN;
      attachReq->epsMi.len = sizeof(GUTI);
      if (ueUetAttachReq.gutiMI_pres) {
        UE_LOG_DEBUG(ueAppCb, "Filling MI GUTI received from testscript");
        cmMemcpy((U8 *)&attachReq->epsMi.u.guti, (U8 *)&ueUetAttachReq.gutiMI,
               attachReq->epsMi.len);
      } else {
        cmMemcpy((U8 *)&attachReq->epsMi.u.guti, (U8 *)&ueCb->ueCtxt.ueGuti,
               attachReq->epsMi.len);
      }
      break;
    }
    case CM_EMM_MID_TYPE_IMEI: {
      if (useOldSecCtxt) {
        // Fill old ksi from UeCb
        attachReq->nasKsi.id = ueCb->secCtxt.ksi;
        attachReq->nasKsi.tsc = ueCb->secCtxt.tsc;
      }

      // Fill Mobile Id
      attachReq->epsMi.pres = TRUE;
      attachReq->epsMi.type = CM_EMM_MID_TYPE_IMEISV;
      attachReq->epsMi.evenOddInd = UE_EVEN;
      attachReq->epsMi.len = 15;
      attachReq->epsMi.evenOddInd =
          (((attachReq->epsMi.len) % 2) != 0) ? (UE_ODD) : (UE_EVEN);
      cmMemcpy((U8 *)&attachReq->epsMi.u.imei.id, (U8 *)&ueCb->ueCtxt.ueImei,
               attachReq->epsMi.len);
      break;
    }
    default: {
      UE_LOG_ERROR(ueAppCb, "Invalid miType");
      UE_LOG_EXITFN(ueAppCb, RFAILED);
    }
  }

  // Copy UE capabilities from UE Cb
  cmMemcpy((U8 *)&attachReq->ueNwCap, (U8 *)&ueCb->ueCtxt.ueNwCap,
           sizeof(CmEmmUeNwCap));

  // Include Additional Update Type
  if (addUpdType->pres == TRUE) {
    attachReq->addUpdType.pres = TRUE;             /* Additional Update Type*/
    attachReq->addUpdType.type = addUpdType->type; /* Additional Update Type*/
  }
  // Include DRX Parameter Ie
  if (drxParm->pres == TRUE) {
    attachReq->drxPrm.pres = TRUE;
    attachReq->drxPrm.spltPGCycle = drxParm->spltPGCycle;
    attachReq->drxPrm.nonDrxTmr = drxParm->nonDrxTmr;
    attachReq->drxPrm.spltOnCcch = drxParm->spltOnCcch;
    attachReq->drxPrm.u.drxVal = drxParm->u.drxVal;
  }
  attachReq->suppCodecLst.pres = TRUE;
  attachReq->suppCodecLst.len = 2;
  attachReq->suppCodecLst.codec[0].sysId = 0x04;
  attachReq->suppCodecLst.codec[0].bmpLen = 2;
  attachReq->suppCodecLst.codec[0].bmp = (0x60 << 8) | 0x04;

  attachReq->suppCodecLst.codec[1].sysId = 0x00;
  attachReq->suppCodecLst.codec[1].bmpLen = 2;
  attachReq->suppCodecLst.codec[1].bmp = (0x1c << 8);
  // ESM message container IE
  if ((ret = ueAppUtlBldPdnConReq(ueCb, &(attachReq->esmEvnt), protCfgOpt,
                                  pdnType, eti)) != ROK) {
    UE_LOG_ERROR(ueAppCb, "Building PDN Connection Request Failed\n");
    CM_FREE_NASEVNT(ueEvt);
    RETVALUE(RFAILED);
  }
  UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun:   ueAppUtlBldTauReq
 *
 *       Desc:  This function builds TAU Request message.
 *
 *       Ret:   ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PUBLIC S16 ueAppUtlBldTauReq(UeCb *ueCb, CmNasEvnt **ueEvt,
                             UeUetTauRequest *ueUetTauRequest) {
  S16 ret = ROK;
  U32 mTmsi = 0;
  UeAppCb *ueAppCb = NULLP;
  CmEmmTAURequest *tauReq = NULLP;
  CmEmmMsg *emmMsg;

  UE_GET_CB(ueAppCb);
  UE_LOG_ENTERFN(ueAppCb);

  UE_LOG_DEBUG(ueAppCb, "Building TAU Request message");

  if (ueEvt == NULLP) {
    UE_LOG_ERROR(ueAppCb, "ueEvnt NULL Pointer !");
    RETVALUE(RFAILED);
  }
  /* Allocate memory for pdu */
  CM_ALLOC_NASEVNT(ueEvt, CM_EMM_PD);

  if (*ueEvt == NULLP) {
    UE_LOG_ERROR(ueAppCb, "ueEvnt NULL Pointer !");
    RETVALUE(RFAILED);
  }

  if (ueUetTauRequest->ueMtmsi.pres == TRUE) {
    mTmsi = ueUetTauRequest->ueMtmsi.mTmsi;
  } else {
    mTmsi = ueCb->ueCtxt.ueGuti.mTMSI;
  }

  if (cmGetMem(&((*ueEvt)->memCp), sizeof(CmEmmMsg), (Ptr *)&emmMsg) != ROK) {
    CM_FREE_NASEVNT(ueEvt);
    RETVALUE(RFAILED);
  }

  (*ueEvt)->m.emmEvnt = emmMsg;
  tauReq = &((*ueEvt)->m.emmEvnt->u.tauReq);

  /*Fill header information*/
  (*ueEvt)->secHT = CM_NAS_SEC_HDR_TYPE_INT_PRTD;

  /* Security header type is "Plain NAS message, not security protected" */
  emmMsg->protDisc = CM_EMM_PD;
  emmMsg->secHdrType = CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG;
  emmMsg->msgId = CM_EMM_MSG_TAU_REQ;

  /* Fill mandatory IEs */
  tauReq->epsUpdType.pres = TRUE;
  tauReq->epsUpdType.actv = ueUetTauRequest->ActvFlag;
  tauReq->epsUpdType.type = ueUetTauRequest->epsUpdtType;

  /*NAS key set identifier IE*/
  tauReq->nasKsi.pres = TRUE;
  tauReq->nasKsi.id = ueCb->secCtxt.ksi;
  tauReq->nasKsi.tsc = ueCb->secCtxt.tsc;

  tauReq->epsMi.pres = TRUE;
  tauReq->epsMi.type = CM_EMM_MID_TYPE_GUTI;
  tauReq->epsMi.evenOddInd = UE_EVEN;
  tauReq->epsMi.len = sizeof(Guti);
  cmMemcpy((U8 *)&tauReq->epsMi.u.guti, (U8 *)&ueCb->ueCtxt.ueGuti,
           sizeof(Guti));
  tauReq->epsMi.u.guti.mTMSI = mTmsi;

  if (ueUetTauRequest->epsBearerCtxSts > 0) {
    tauReq->epsBearCtxtSts.pres = TRUE;
    tauReq->epsBearCtxtSts.len = 2;
    cmMemcpy((U8 *)&tauReq->epsBearCtxtSts.val,
             &ueUetTauRequest->epsBearerCtxSts,
             sizeof(ueUetTauRequest->epsBearerCtxSts));
  }
  UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun:   ueAppUtlBldTauComp
 *
 *       Desc:  This function builds TAU Complete message.
 *
 *       Ret:   ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppUtlBldTauComp(UeCb *ueCb, CmNasEvnt **ueEvt)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   CmEmmMsg* emmMsg;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Building TAU Complete message");

   if (ueEvt == NULLP)
   {
      UE_LOG_ERROR(ueAppCb, "ueEvnt NULL Pointer !");
      RETVALUE(RFAILED);
   }

   /* Allocate memory for pdu */
   CM_ALLOC_NASEVNT(ueEvt, CM_EMM_PD);

   if (*ueEvt == NULLP)
   {
      UE_LOG_ERROR(ueAppCb, "ueEvnt NULL Pointer !");
      RETVALUE(RFAILED);
   }

   if (cmGetMem(&((*ueEvt)->memCp), sizeof(CmEmmMsg), (Ptr *)&emmMsg) != ROK)
   {
      CM_FREE_NASEVNT(ueEvt);
      RETVALUE(RFAILED);
   }

   (*ueEvt)->m.emmEvnt = emmMsg;

   /* Fill header information */
   if (UE_APP_SEC_CTXT_CRNT == ueCb->secCtxt.status)
   {
      (*ueEvt)->secHT = CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG;
   }

   /* Security header type is "Plain NAS message, not security protected" */
   emmMsg->protDisc = CM_EMM_PD;
   emmMsg->secHdrType = CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG;
   emmMsg->msgId = CM_EMM_MSG_TAU_CMP;

   /* Other than header, there are no IEs in this message */

   UE_LOG_EXITFN(ueAppCb, ret);
}


/*
 *
 *   Fun:   ueAppEdmEncode
 *
 *   Desc:  Encodes EDM message and sends it to lower layer
 *
 *   Ret:   ROK - ok; RFAILED - failed
 *
 *   Notes: none
 *
 *   File:  ue_app.c
 *
 */
PUBLIC S16 ueAppEdmEncode(CmNasEvnt *ueEvnt, NhuDedicatedInfoNAS *nasPdu)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Encoding the EDM message and sending it to "\
         "lower layer");

   if (NULLP == ueEvnt)
   {
      UE_LOG_ERROR(ueAppCb, "NULL Pointer!!!");
      ret = RFAILED;
      RETVALUE(ret);
   }

   /* Check the protocol discriminator and call respective encoder */
   switch (ueEvnt->protDisc)
   {
      case CM_EMM_PD:
      {
         UE_LOG_DEBUG(ueAppCb, "Protocol descriptor is CM_EMM_PD");
         ret = cmEmmEncMsg(ueEvnt, &nasPdu->val, &nasPdu->len);
         break;
      }
      case CM_ESM_PD:
      {
         UE_LOG_DEBUG(ueAppCb, "Protocol descriptor is CM_ESM_PD");
         ret = cmEsmEncMsg(ueEvnt, &nasPdu->val, &nasPdu->len);
         break;
      }
      default:
      {
         UE_LOG_ERROR(ueAppCb, "Invaild protocal discription!!");
         ret = RFAILED;
         break;
      }
   }
   UE_LOG_EXITFN(ueAppCb, ret);

} /* ueAppEdmEncode */

/*
 *
 *       Fun: ueAppEsmHndlOutActDefBearerAcc
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppEsmHndlOutActDefBearerAcc(UeEsmCb *esmCb, CmNasEvnt *evnt)
{
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Activate default bearer accept");

   /* Update bearer context state */
   esmCb->bState = UE_ESM_ST_BEARER_CTXT_ACTIVE;

   UE_LOG_EXITFN(ueAppCb, ROK);
} /* ueAppEsmHndlOutActDefBearerAcc */

/*
 *
 *       Fun: ueAppEsmHndlOutDeActvBearerAcc
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppEsmHndlOutDeActvBearerAcc(UeEsmCb *esmCb, CmNasEvnt *evnt)
{
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "DeActivate bearer accept");

   /* Update bearer context state */
   esmCb->bState = UE_ESM_ST_BEARER_CTXT_INACTIVE;

   UE_LOG_EXITFN(ueAppCb, ROK);
} /* ueAppEsmHndlOutActDedBearerAcc */


/*
 *
 *       Fun: ueAppEsmHndlOutActDedBearerAcc
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppEsmHndlOutActDedBearerAcc(UeEsmCb *esmCb, CmNasEvnt *evnt)
{
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Activate dedicate bearer accept");

   /* Update bearer context state */
   esmCb->bState = UE_ESM_ST_BEARER_CTXT_ACTIVE;

   UE_LOG_EXITFN(ueAppCb, ROK);
} /* ueAppEsmHndlOutActDedBearerAcc */

/*
 *
 *       Fun: ueAppEsmHndlOutActDedBearerRej
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppEsmHndlOutActDedBearerRej(UeEsmCb *esmCb, CmNasEvnt *evnt)
{
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Activate dedicate bearer reject");

   /* Update bearer context state */
   esmCb->bState = UE_ESM_ST_BEARER_CTXT_INACTIVE;

   UE_LOG_EXITFN(ueAppCb, ROK);
} /* ueAppEsmHndlOutActDedBeareRej */
/*
 *
 *       Fun: ueAppEsmHndlOutPDNConnectReq
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppEsmHndlOutPDNConnectReq(UeEsmCb *esmCb, CmNasEvnt *evnt)
{
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "PDN connectivity request");

   /* Update procedure transaction state */
   esmCb->pState = UE_ESM_ST_PROC_TXN_PENDING;

   /* Updating bearerId and transaction Id to event */
   evnt->m.esmEvnt->bearerId = esmCb->bId;
   evnt->m.esmEvnt->prTxnId = esmCb->tId;

   UE_LOG_EXITFN(ueAppCb, ROK);
} /* ueAppEsmHndlOutPDNConnectReq */
/*
 *
 *       Fun: ueAppEsmHndlOutEsmInformationRsp
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppEsmHndlOutEsmInformationRsp(UeEsmCb *esmCb, CmNasEvnt *evnt)
{
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "ESM Information Response");

   /* Update procedure transaction state */
   esmCb->pState = UE_ESM_ST_PROC_TXN_PENDING;

   UE_LOG_EXITFN(ueAppCb, ROK);
} /* ueAppEsmHndlOutPDNConnectReq */

/*
 *
 *       Fun: ueAppEsmHndlOutBerResAllocReq
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppEsmHndlOutBerResAllocReq(UeEsmCb *esmCb, CmNasEvnt *evnt)
{
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

      UE_LOG_DEBUG(ueAppCb, " Baerer Resource Allocation Request");

   /* Update procedure transaction state */
   esmCb->pState = UE_ESM_ST_PROC_TXN_PENDING;

   /* Updating bearerId and transaction Id to event */
   evnt->m.esmEvnt->bearerId = esmCb->bId;
   evnt->m.esmEvnt->prTxnId = esmCb->tId;

   UE_LOG_EXITFN(ueAppCb, ROK);
} /* ueAppEsmHndlOutBerResAllocReq*/

/*
 *
 *       Fun: ueAppUtlAddEsmCb
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppUtlAddEsmCb(UeEsmCb **esmCb, UeCb *ueCb)
{
   U8 i = 0;
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   UeEsmCb *newEsmCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);
   UE_LOG_DEBUG(ueAppCb, "Adding ESM Cb");

   /* Allocate esmCb */
   newEsmCb = (UeEsmCb *)ueAlloc(sizeof(UeEsmCb));
   if (newEsmCb == NULLP)
   {
      UE_LOG_ERROR(ueAppCb, "Failed to allocate memory\n");
      RETVALUE(RFAILED);
   }
   for (i = 1; i < CM_ESM_MAX_BEARER_ID; i++)
   {
      if (ueCb->esmTList[i] == NULLP)
      {
         newEsmCb->tId = i;
         ueCb->esmTList[i] = newEsmCb;
         break;
      }
   }

   if (newEsmCb->tId == 0)
   {
      UE_LOG_ERROR(ueAppCb, "Failed to get available transId");
      ueFree((U8*)newEsmCb, sizeof(UeEsmCb));
      RETVALUE(RFAILED);
   }

   UE_LOG_DEBUG(ueAppCb, "Esm transaction Id: (%d)", newEsmCb->tId);
   newEsmCb->bState = UE_ESM_ST_BEARER_CTXT_INACTIVE;
   newEsmCb->pState = UE_ESM_ST_PROC_TXN_INACTIVE;

   *esmCb = newEsmCb;
   UE_LOG_EXITFN(ueAppCb, ret);
} /* end of ueAppUtlAddEsmCb */

/*
 *
 *       Fun: ueAppEsmHndlInvEvnt
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppEsmHndlInvEvnt(UeEsmCb *esmCb, CmNasEvnt *evnt, UeCb *ueCb)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

      /* Invalid message in the state, returing RFAILED */
   UE_LOG_ERROR(ueAppCb, "Invalid message");

   UE_LOG_EXITFN(ueAppCb, ret);
} /* ueAppEsmHndlInvEvnt */

/*
 *
 *       Fun: ueAppUtlFndEsmCb
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PUBLIC S16 ueAppUtlFndEsmCb(UeEsmCb **esmCb, U8 key, UeAppEsmKeyType type,
                            UeCb *ueCb)
{
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   *esmCb = NULLP;
   /* Checking for valid trans id, valid = 1 to 254 */
   if (((key < UE_ESM_TRANS_ID_INDX) || (key > UE_ESM_MAX_TRANS_ID)))
      UE_LOG_EXITFN(ueAppCb, RFAILED);

   if ((type == UE_ESM_TRANS_KEY) && (key < CM_ESM_MAX_BEARER_ID))
   {
      *esmCb = ueCb->esmTList[key];
   }
   else if ((type == UE_ESM_BID_KEY) && (key < CM_ESM_MAX_BEARER_ID))
   {
      *esmCb = ueCb->esmBList[key];
   }
   else
   {
      UE_LOG_DEBUG(ueAppCb, "Esm Cb not found for transaction Id (%d)", key);
      UE_LOG_EXITFN(ueAppCb, RFAILED);
   }
   UE_LOG_EXITFN(ueAppCb, ROK);
} /* end of ueAppUtlFndEsmCb */

/*
 *
 *       Fun: ueAppUtlFndRbCb
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppUtlFndRbCb(U8 *rbIdx,UeCb *ueCb,U8 bearerId)
{
   UeAppCb *ueAppCb = NULLP;
   U8 idx;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   /* drb id can range between 1..32 */
   for(idx = 1; idx < UE_APP_MAX_DRBS; idx++)
   {
      if ((ueCb->drbs[idx] == UE_APP_DRB_INUSE) &&\
            (ueCb->ueRabCb[idx-1].epsBearerId == bearerId))
      {
         *rbIdx = idx-1;
         RETVALUE(ROK);
      }
   }
   RETVALUE(RFAILED);
   UE_LOG_EXITFN(ueAppCb, ROK);
} /* end of ueAppUtlFndRbCb */

/*
 *
 *       Fun: ueAppEsmHdlOutUeEvnt
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppEsmHdlOutUeEvnt(CmNasEvnt *evnt, UeCb *ueCb)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   UeEsmCb  *esmCb = NULLP;
   CmEsmMsg *esmMsg = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);
   if(evnt == NULLP)
   {
      UE_LOG_ERROR(ueAppCb, "Invalid esm event");
      RETVALUE(RFAILED);
   }

   UE_LOG_DEBUG(ueAppCb, "Outgoing esm events");

   esmMsg = evnt->m.esmEvnt;
   if ((esmMsg->msgType != CM_ESM_MSG_PDN_CONN_REQ) && (esmMsg->msgType != CM_ESM_MSG_BEAR_RES_ALLOC_REQ)
   && (esmMsg->msgType != CM_ESM_MSG_ESM_INFO_RSP)
   && (esmMsg->msgType != CM_ESM_MSG_PDN_DISCONN_REQ))
   {
       /*esmMsg->bearerId = 6;*/
      ret = ueAppUtlFndEsmCb(&esmCb, esmMsg->bearerId, UE_ESM_BID_KEY, ueCb);
   }
   else if (esmMsg->msgType == CM_ESM_MSG_ESM_INFO_RSP)
   {
     ret = ueAppUtlFndEsmCb(&esmCb, esmMsg->prTxnId, UE_ESM_TRANS_KEY, ueCb);
   }
   else
   {
      ret = ueAppUtlAddEsmCb(&esmCb, ueCb);
   }

   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "ESM Cb not found\n");
      RETVALUE(RFAILED);
   }

   if (esmCb == NULLP)
   {
      UE_LOG_ERROR(ueAppCb, "ESM Cb is NULL\n");
      RETVALUE(RFAILED);
   }

   switch(esmMsg->msgType)
   {
      case CM_ESM_MSG_PDN_CONN_REQ:
         {
            ret = ueAppEsmHndlOutPDNConnectReq(esmCb, evnt);
            break;
         }
      case CM_ESM_MSG_ACTV_DEF_BEAR_ACC:
         {
            ret = ueAppEsmHndlOutActDefBearerAcc(esmCb, evnt);
            break;
         }
      case CM_ESM_MSG_BEAR_RES_ALLOC_REQ:
         {
            ret = ueAppEsmHndlOutBerResAllocReq(esmCb, evnt);
            break;
         }
      case CM_ESM_MSG_ACTV_DED_BEAR_ACC:
         {
            ret = ueAppEsmHndlOutActDedBearerAcc(esmCb, evnt);
            break;
         }
      case CM_ESM_MSG_DEACTV_BEAR_ACC:
         {
            ret = ueAppEsmHndlOutDeActvBearerAcc(esmCb, evnt);
            break;
         }

      case CM_ESM_MSG_ACTV_DED_BEAR_REJ:
         {
            ret = ueAppEsmHndlOutActDedBearerRej(esmCb, evnt);
            break;
         }
      case CM_ESM_MSG_ESM_INFO_RSP:
         {
            ret = ueAppEsmHndlOutEsmInformationRsp(esmCb, evnt);
            break;
         }
      case CM_ESM_MSG_PDN_DISCONN_REQ:
         {
            ret = ueAppEsmHndlOutPDNDisConnectReq(esmCb, evnt);
            break;
         }

      default:
         {
            ret = ueAppEsmHndlInvEvnt(esmCb, evnt, ueCb);
            break;
         }
   }

   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Failed to handle esm event\n");
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* ueAppEsmHdlOutUeEvnt */

/*
 *
 *       Fun:   ueProcUeAttachReq
 *
 *       Desc:  Processing requst from TFW to send ATTACH REQUEST.
 *
 *       Ret:   ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueProcUeAttachReq(UetMessage *p_ueMsg, Pst *pst) {
  U32 pdnType;
  U8 isPlainMsg = TRUE;
  U8 mIdType;
  S16 ret = ROK;
  U32 ueId;
  UeAppCb *ueAppCb = NULLP;
  UeCb *ueCb = NULLP;
  NhuDedicatedInfoNAS nasEncPdu;
  CmNasEvnt *attachReqEvnt = NULLP;
  NbuInitialUeMsg *nbuInitialUeMsg = NULLP;
  NbuUlNasMsg *pUlNbMsg = NULLP;
  UeAppMsg srcMsg;
  UeAppMsg dstMsg;

  UE_GET_CB(ueAppCb);
  UE_LOG_ENTERFN(ueAppCb);

  UE_LOG_DEBUG(ueAppCb, "Processing UE Attach Request message");
  ueId = p_ueMsg->msg.ueUetAttachReq.ueId;

  /* Fetching the UeCb */
  ret = ueDbmFetchUe(ueId, (PTR *)&ueCb);
  if (ret != ROK) {
    UE_LOG_ERROR(ueAppCb, "UeCb List NULL ueId = %d", ueId);
    RETVALUE(ret);
  }

  ret = ueAppUtlBldAttachReq(ueCb, &attachReqEvnt, p_ueMsg->msg.ueUetAttachReq);
  if (ret != ROK) {
    UE_LOG_ERROR(ueAppCb, "Attach Request Building failed");
    RETVALUE(ret);
  }

  if ((ret = ueAppEsmHdlOutUeEvnt(attachReqEvnt->m.emmEvnt->u.atchReq.esmEvnt,
                                  ueCb)) != ROK) {
    UE_LOG_ERROR(ueAppCb, "Handling Attach Request failed");
    RETVALUE(RFAILED);
  }

  ueCb->emmCb.state = UE_EMM_UE_REG_INIT;
  ueCb->emmCb.esmPiggyBacked = TRUE;
  cmMemset((U8 *)&nasEncPdu, 0, sizeof(NhuDedicatedInfoNAS));

  /* Encode the PDU */
  ret = ueAppEdmEncode(attachReqEvnt, &nasEncPdu);
  if (ret != ROK) {
    UE_LOG_ERROR(ueAppCb, "Attach Request Encode Failed");
    CM_FREE_NASEVNT(&attachReqEvnt);
    RETVALUE(ret);
  }

  /* Integrity Protected */
  if (CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG != attachReqEvnt->secHT) {
    isPlainMsg = FALSE;
    srcMsg.val = nasEncPdu.val;
    srcMsg.len = nasEncPdu.len;
    ret = ueAppCmpUplnkSec(&ueCb->secCtxt, attachReqEvnt->secHT, &srcMsg,
                           &dstMsg);
    if (ROK != ret) {
      UE_LOG_ERROR(ueAppCb, "Uplink Security Failed");
      attachReqEvnt->pdu = NULLP;
      CM_FREE_NASEVNT(&attachReqEvnt);
      EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
      RETVALUE(ret);
    }
    EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
    nasEncPdu.val = dstMsg.val;
    nasEncPdu.len = dstMsg.len;
  }

  CM_FREE_NASEVNT(&attachReqEvnt);

  if (ueCb->ecmCb.state == UE_ECM_CONNECTED) {
    pUlNbMsg = (NbuUlNasMsg *)ueAlloc(sizeof(NbuUlNasMsg));
    pUlNbMsg->ueId = ueCb->ueId;
    pUlNbMsg->nasPdu.pres = TRUE;
    pUlNbMsg->nasPdu.len = nasEncPdu.len;
    pUlNbMsg->nasPdu.val = (U8 *)ueAlloc(pUlNbMsg->nasPdu.len);
    cmMemcpy((U8 *)pUlNbMsg->nasPdu.val, (U8 *)nasEncPdu.val,
             pUlNbMsg->nasPdu.len);

    UE_LOG_DEBUG(ueAppCb, "Sending UL NAS Message to eNodeB");
    ret = ueSendUlNasMsgToNb(pUlNbMsg, &ueAppCb->nbPst);
  } else {
    nbuInitialUeMsg = (NbuInitialUeMsg *)ueAlloc(sizeof(NbuInitialUeMsg));
    nbuInitialUeMsg->ueId = ueId;
    nbuInitialUeMsg->rrcCause = 3;

    if (mIdType == CM_EMM_MID_TYPE_GUTI) {
      nbuInitialUeMsg->stmsi.pres = TRUE;
      nbuInitialUeMsg->stmsi.mmec = ueCb->ueCtxt.ueGuti.mmeCode;
      nbuInitialUeMsg->stmsi.mTMSI = ueCb->ueCtxt.ueGuti.mTMSI;
    }

    nbuInitialUeMsg->nasPdu.pres = TRUE;
    nbuInitialUeMsg->nasPdu.len = nasEncPdu.len;
    nbuInitialUeMsg->nasPdu.val = (U8 *)ueAlloc(nbuInitialUeMsg->nasPdu.len);
    cmMemcpy((U8 *)nbuInitialUeMsg->nasPdu.val, nasEncPdu.val,
             nbuInitialUeMsg->nasPdu.len);

    UE_LOG_DEBUG(ueAppCb, "Sending Initial UE Message to eNodeB");
    ret = ueSendInitialUeMsg(nbuInitialUeMsg, &ueAppCb->nbPst);
  }
  if (ret != ROK) {
    UE_LOG_ERROR(ueAppCb, "Sending Attach Request to eNodeB failed");
    ret = RFAILED;
  }

  if (isPlainMsg) {
    EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
  }

  UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *       Fun: ueProcUeTauRequest
 *
 *       Desc:  This function processes TAU Request from TFW
 *
 *       Ret:   ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueProcUeTauRequest(UetMessage *p_ueMsg, Pst *pst) {
  U8 isPlainMsg = TRUE;
  S16 ret = ROK;
  U32 ueId = 0;
  UeAppCb *ueAppCb = NULLP;
  UeCb *ueCb = NULLP;
  UeAppMsg srcMsg;
  UeAppMsg dstMsg;
  U8 rbIdx = 0;
  U8 bearerToBeRel = 0;
  U8 tmpBearerList[CM_ESM_MAX_BEARER_ID] = {0};

  NhuDedicatedInfoNAS nasEncPdu;
  CmNasEvnt *tauReqEvnt = NULLP;
  NbuInitialUeMsg *nbUeTauReq = NULLP;
  NbuUlNasMsg *nbUeTauReqUlNas = NULLP;
  NbuRelBearerReq *nbuRelBerReq = NULLP;

  UE_GET_CB(ueAppCb);
  UE_LOG_ENTERFN(ueAppCb);

  UE_LOG_DEBUG(ueAppCb, "Processing UE Tracking area update message");
  ueId = p_ueMsg->msg.ueUetTauRequest.ueId;
  U16 epsBearerCtxSts = p_ueMsg->msg.ueUetTauRequest.epsBearerCtxSts;

  // Fetching the UeCb
  ret = ueDbmFetchUe(ueId, (PTR *)&ueCb);
  if (ret != ROK) {
    UE_LOG_ERROR(ueAppCb, "ueProcUeTauReq: UeCb List NULL ueId = %d", ueId);
    RETVALUE(ret);
  }
  /* Deactivate bearer only if epsBearerCtxSts received from test script is
   * non zero and there is more than 1 PDN
   */
  if (epsBearerCtxSts > 0) {
    for (U8 ebi = CM_ESM_BEARER_ID_INDX; ebi < CM_ESM_MAX_BEARER_ID; ebi++) {
      rbIdx = 0;
      if (!(epsBearerCtxSts & (1 << ebi))) {
        // Find the bearer index
        if ((ueAppUtlFndRbCb(&rbIdx, ueCb, ebi) == ROK)) {
          if (ueCb->ueRabCb[rbIdx].bearerType == DEFAULT_BEARER) {
            if (ueCb->numPdns == 1) {
              continue;
            }
            // Clear the bearer context
            cmMemset((U8 *)&(ueCb->ueRabCb[rbIdx]), 0,
                     sizeof(ueCb->ueRabCb[rbIdx]));
            ueCb->drbs[rbIdx] = UE_APP_DRB_AVAILABLE;
            tmpBearerList[bearerToBeRel] = ebi;
            UE_LOG_DEBUG(ueAppCb, "Adding default ebi=%d to tmpBearerList\n",
                         ebi);
            bearerToBeRel++;
          } else if (ueCb->ueRabCb[rbIdx].bearerType == DEDICATED_BEARER) {
            // Clear the bearer context
            cmMemset((U8 *)&(ueCb->ueRabCb[rbIdx]), 0,
                     sizeof(ueCb->ueRabCb[rbIdx]));
            ueCb->drbs[rbIdx + 1] = UE_APP_DRB_AVAILABLE;
            tmpBearerList[bearerToBeRel] = ebi;
            UE_LOG_DEBUG(ueAppCb, "Adding dedicated ebi=%d to tmpBearerList\n",
                         ebi);
            bearerToBeRel++;
          }
        }
      }
    }
    if (bearerToBeRel > 0) {
      nbuRelBerReq = (NbuRelBearerReq *)ueAlloc(sizeof(NbuRelBearerReq));
      if (!nbuRelBerReq) {
        UE_LOG_ERROR(ueAppCb,
                     "Failed to allocate memory to nbuRelBerReq for ueId=%d",
                     ueId);
        RETVALUE(RFAILED);
      }
      nbuRelBerReq->ueId = ueId;
      nbuRelBerReq->numOfErabIds = bearerToBeRel;
      nbuRelBerReq->erabIdLst =
          (U8 *)ueAlloc((sizeof(U8)) * nbuRelBerReq->numOfErabIds);
      if (!nbuRelBerReq->erabIdLst) {
        UE_LOG_ERROR(ueAppCb,
                     "Failed to allocate memory to erabIdLst for ueId=%d",
                     ueId);
        RETVALUE(RFAILED);
      }
      cmMemset((U8 *)(nbuRelBerReq->erabIdLst), 0,
               ((sizeof(U8)) * nbuRelBerReq->numOfErabIds));
      cmMemcpy(nbuRelBerReq->erabIdLst, tmpBearerList, bearerToBeRel);
      if (ueSendRelBearerReqMsgToNb(nbuRelBerReq, &ueAppCb->nbPst) == ROK) {
        // Store TAU req in ueCb and send after receiving RelBearerRsp from enb
        ueCb->ueUetTauRequest =
            (UeUetTauRequest *)ueAlloc(sizeof(UeUetTauRequest));
        if (!ueCb->ueUetTauRequest) {
          UE_LOG_ERROR(
              ueAppCb,
              "Failed to allocate memory to ueCb->ueUetTauRequest for ueId=%d",
              ueId);
          RETVALUE(RFAILED);
        }
        cmMemcpy(ueCb->ueUetTauRequest, &p_ueMsg->msg.ueUetTauRequest,
                 sizeof(UeUetTauRequest));
        RETVALUE(ROK);
      } else {
        UE_LOG_ERROR(ueAppCb, "Failed to send RelBearerReq to enb for ueId=%d",
                     ueId);
        RETVALUE(RFAILED);
      }
    }
  }
  ret = ueAppUtlBldTauReq(ueCb, &tauReqEvnt, &p_ueMsg->msg.ueUetTauRequest);
  if (ret != ROK) {
    UE_LOG_ERROR(ueAppCb, "TAU Request Building failed");
    RETVALUE(ret);
  }

  cmMemset((U8 *)&nasEncPdu, 0, sizeof(NhuDedicatedInfoNAS));
  /* Encode the PDU */
  ret = ueAppEdmEncode(tauReqEvnt, &nasEncPdu);

  if (ret != ROK) {
    UE_LOG_ERROR(ueAppCb, "TAU Request Encode Failed\n");
    CM_FREE_NASEVNT(&tauReqEvnt);
    RETVALUE(ret);
  }

  /** Integrity Protected **/
  if (CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG != tauReqEvnt->secHT) {
    isPlainMsg = FALSE;
    srcMsg.val = nasEncPdu.val;
    srcMsg.len = nasEncPdu.len;
    ret = ueAppCmpUplnkSec(&ueCb->secCtxt, tauReqEvnt->secHT, &srcMsg, &dstMsg);
    if (ROK != ret) {
      UE_LOG_ERROR(ueAppCb, "Uplink Security Failed");
      EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
      tauReqEvnt->pdu = NULLP;
      CM_FREE_NASEVNT(&tauReqEvnt);
      RETVALUE(ret);
    }
    EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
    nasEncPdu.val = dstMsg.val;
    nasEncPdu.len = dstMsg.len;
  }
  CM_FREE_NASEVNT(&tauReqEvnt);

  nbUeTauReq = (NbuInitialUeMsg *)ueAlloc(sizeof(NbuInitialUeMsg));
  nbUeTauReq->ueId = ueId;
  nbUeTauReq->rrcCause = 3;

  nbUeTauReq->stmsi.pres = TRUE;
  nbUeTauReq->stmsi.mmec = ueCb->ueCtxt.ueGuti.mmeCode;
  if (p_ueMsg->msg.ueUetTauRequest.ueMtmsi.pres == TRUE) {
    nbUeTauReq->stmsi.mTMSI = p_ueMsg->msg.ueUetTauRequest.ueMtmsi.mTmsi;
  } else {
    nbUeTauReq->stmsi.mTMSI = ueCb->ueCtxt.ueGuti.mTMSI;
  }

  nbUeTauReq->nasPdu.pres = TRUE;
  nbUeTauReq->nasPdu.len = nasEncPdu.len;
  nbUeTauReq->nasPdu.val = (U8 *)ueAlloc(nbUeTauReq->nasPdu.len);
  cmMemcpy((U8 *)nbUeTauReq->nasPdu.val, nasEncPdu.val, nbUeTauReq->nasPdu.len);

  if (isPlainMsg) {
    EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
  }

  if (ueCb->ecmCb.state == UE_ECM_IDLE) {
    UE_LOG_DEBUG(ueAppCb, "Sending TAU in initial ue message");
    ret = ueSendInitialUeMsg(nbUeTauReq, &ueAppCb->nbPst);
  } else if (ueCb->ecmCb.state == UE_ECM_CONNECTED) {
    nbUeTauReqUlNas = (NbuUlNasMsg *)ueAlloc(sizeof(NbuUlNasMsg));
    nbUeTauReqUlNas->ueId = ueCb->ueId;
    nbUeTauReqUlNas->nasPdu.pres = TRUE;
    nbUeTauReqUlNas->nasPdu.len = nasEncPdu.len;
    nbUeTauReqUlNas->nasPdu.val = (U8 *)ueAlloc(nbUeTauReqUlNas->nasPdu.len);
    cmMemcpy((U8 *)nbUeTauReqUlNas->nasPdu.val, (U8 *)nasEncPdu.val,
             nbUeTauReqUlNas->nasPdu.len);

    UE_LOG_DEBUG(ueAppCb, "Sending TAU in UL NAS message");
    ret = ueSendUlNasMsgToNb(nbUeTauReqUlNas, &ueAppCb->nbPst);
  }
  if (ret != ROK) {
    UE_LOG_ERROR(ueAppCb, "Sending TAU Request to eNodeB failed\n");
    ret = RFAILED;
  }

  UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun:   ueProcUeTauComplete
 *
 *       Desc:  This function processes TAU Complete coming from TFW
 *
 *       Ret:   ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueProcUeTauComplete(UetMessage *p_ueMsg, Pst *pst)
{
   U8 isPlainMsg = TRUE;
   S16 ret = ROK;
   U32 ueId;
   UeAppCb *ueAppCb = NULLP;
   UeCb *ueCb = NULLP;
   UeAppMsg srcMsg;
   UeAppMsg dstMsg;
   NhuDedicatedInfoNAS nasEncPdu;
   CmNasEvnt *tauCompEvnt = NULLP;
   NbuUlNasMsg *nbUeTauComp = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   ueId = p_ueMsg->msg.ueUetTauComplete.ueId;
   UE_LOG_DEBUG(ueAppCb, "Processing UE TAU Complete message for ueId(%d)",
                ueId);

   /* Fetching the UeCb */
   ret = ueDbmFetchUe(ueId,(PTR*)&ueCb);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "UeCb List NULL ueId = %d", ueId);
      RETVALUE(ret);
   }

   ret = ueAppUtlBldTauComp(ueCb, &tauCompEvnt);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "TAU Complete Building failed");
      RETVALUE(ret);
   }

   cmMemset((U8 *)&nasEncPdu, 0, sizeof(NhuDedicatedInfoNAS));
   /* Encode the PDU */
   ret = ueAppEdmEncode(tauCompEvnt, &nasEncPdu);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "TAU Complete Encode Failed");
      CM_FREE_NASEVNT(&tauCompEvnt);
      RETVALUE(ret);
   }

   /* Integrity Protected */
   if (CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG != tauCompEvnt->secHT)
   {
      isPlainMsg = FALSE;
      srcMsg.val = nasEncPdu.val;
      srcMsg.len = nasEncPdu.len;
      ret = ueAppCmpUplnkSec(&ueCb->secCtxt, tauCompEvnt->secHT, &srcMsg,
            &dstMsg);
      if (ROK != ret)
      {
         UE_LOG_ERROR(ueAppCb, "Uplink Security Failed");
         EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
         tauCompEvnt->pdu = NULLP;
         CM_FREE_NASEVNT(&tauCompEvnt);
         RETVALUE(ret);
      }
      EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
      nasEncPdu.val = dstMsg.val;
      nasEncPdu.len = dstMsg.len;
   }
   CM_FREE_NASEVNT(&tauCompEvnt);

   nbUeTauComp = (NbuUlNasMsg *)ueAlloc(sizeof(NbuUlNasMsg));
   nbUeTauComp->ueId = ueId;
   /*nbUeTauComp->rrcCause = 3;*/
   nbUeTauComp->nasPdu.pres = TRUE;
   nbUeTauComp->nasPdu.len = nasEncPdu.len;
   nbUeTauComp->nasPdu.val = (U8 *)ueAlloc(nbUeTauComp->nasPdu.len);
   cmMemcpy((U8 *)nbUeTauComp->nasPdu.val, nasEncPdu.val,
         nbUeTauComp->nasPdu.len);

   if (isPlainMsg)
   {
      EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
   }

   ret = ueSendUlNasMsgToNb(nbUeTauComp, &ueAppCb->nbPst);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Sending TAU Complete to eNodeB failed");
      ret = RFAILED;
   }

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *       Fun: ueProcUeAppConfigReq
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueProcUeAppConfigReq(UetMessage *pCfgReq, Pst *pst)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   if (pCfgReq != NULLP)
   {
      ueAppCb->numOfUeCfgd = pCfgReq->msg.ueAppCfgReq.numOfUE;
      ueAppCb->trfGenIfAddr = pCfgReq->msg.ueAppCfgReq.trfGenIPAddr;
      ueAppCb->NASProcGuardtimer = pCfgReq->msg.ueAppCfgReq.NASProcGuardTimer;
   }
   ret = sendUeAppCfgCompInd();
   UE_LOG_EXITFN(ueAppCb, ret);
} /* ueProcUeAppConfigReq */

/*
 *
 *       Fun: sendUeConfigCompInd
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 sendUeConfigCompInd(Void)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   UetMessage *tfwMsg = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   tfwMsg = (UetMessage *)ueAlloc(sizeof(UetMessage));

   if (tfwMsg == NULLP)
   {
      UE_LOG_ERROR(ueAppCb, "Failed to Allocate memeory");
      UE_LOG_EXITFN(ueAppCb, RFAILED);
   }

   cmMemset((U8*)tfwMsg, 0, sizeof(UetMessage));
   tfwMsg->msgType = UE_CONFIG_COMPLETE_TYPE;

   ret = ueSendToTfwApp(tfwMsg, &ueAppCb->fwPst);
   UE_LOG_EXITFN(ueAppCb, ret);
} /* sendUeConfigCompInd */

/*
 *
 *       Fun:   ueProcUeConfigReq
 *
 *       Desc:  Receives and updated UE info coming from TFW.
 *
 *       Ret:   ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueProcUeConfigReq(UetMessage *pCfgReq, Pst *pst)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   UeCb *ueCb = NULLP;

   UE_GET_CB(ueAppCb);

   ueCb = (UeCb *)ueAlloc(sizeof(UeCb));
   cmMemset((U8 *)ueCb, 0, sizeof(UeCb));

   if (pCfgReq == NULLP)
   {
      UE_LOG_ERROR(ueAppCb, "pCfgReq is empty");
      RETVALUE(RFAILED);
   }

   ueCb->ueId = pCfgReq->msg.ueCfgReq.ueId;
   ueCb->ueCtxt.imsiLen = pCfgReq->msg.ueCfgReq.imsiLen;
   cmMemcpy((U8*)ueCb->ueCtxt.ueImsi, (U8*)pCfgReq->msg.ueCfgReq.imsi,
         ueCb->ueCtxt.imsiLen);

   cmMemcpy((U8*)ueCb->ueCtxt.ueImei, (U8*)pCfgReq->msg.ueCfgReq.imei,
         MAX_IMEI_LEN);

   ueCb->secCtxt.encAlg = pCfgReq->msg.ueCfgReq.NASCyphCfg;
   ueCb->secCtxt.intAlg = pCfgReq->msg.ueCfgReq.NASIntProtCfg;
   ueCb->ueInfo.authAlg = pCfgReq->msg.ueCfgReq.authType;

   cmMemset((U8 *)&ueCb->ueCtxt.ueNwCap, 0, sizeof(CmEmmUeNwCap));

   ueCb->ueCtxt.ueNwCap.pres     = TRUE;
   ueCb->ueCtxt.ueNwCap.len      = 2;
   ueCb->ueCtxt.ueNwCap.eia0     = pCfgReq->msg.ueCfgReq.ueNwCap.eia0;
   ueCb->ueCtxt.ueNwCap.eia1_128 = pCfgReq->msg.ueCfgReq.ueNwCap.eia1_128;
   ueCb->ueCtxt.ueNwCap.eia2_128 = pCfgReq->msg.ueCfgReq.ueNwCap.eia2_128;
   ueCb->ueCtxt.ueNwCap.eea0     = pCfgReq->msg.ueCfgReq.ueNwCap.eea0;
   ueCb->ueCtxt.ueNwCap.eea1_128 = pCfgReq->msg.ueCfgReq.ueNwCap.eea1_128;
   ueCb->ueCtxt.ueNwCap.eea2_128 = pCfgReq->msg.ueCfgReq.ueNwCap.eea2_128;

   ueCb->ueCtxt.ueSecCap.pres = TRUE;
   ueCb->ueCtxt.ueSecCap.len = 2;
   ueCb->ueCtxt.ueSecCap.eea0 = 1;
   ueCb->ueCtxt.ueSecCap.eia1_128 = 1;
   ueCb->ueCtxt.ueSecCap.uea0 = 1;
   ueCb->ueCtxt.ueSecCap.uea1 = 1;
   ueCb->ueCtxt.ueSecCap.uea1 = 1;

   /* filling OP key value UE_USIM_SHARED_KEY_SIZE, UE_USIM_OP_KEY_SIZE,
    * UE_USIM_SEQ_NMB_SIZE*/
   ueCb->ueInfo.sharedKey[0]  = pCfgReq->msg.ueCfgReq.sharedKey[0];
   ueCb->ueInfo.sharedKey[1]  = pCfgReq->msg.ueCfgReq.sharedKey[1];
   ueCb->ueInfo.sharedKey[2]  = pCfgReq->msg.ueCfgReq.sharedKey[2];
   ueCb->ueInfo.sharedKey[3]  = pCfgReq->msg.ueCfgReq.sharedKey[3];
   ueCb->ueInfo.sharedKey[4]  = pCfgReq->msg.ueCfgReq.sharedKey[4];
   ueCb->ueInfo.sharedKey[5]  = pCfgReq->msg.ueCfgReq.sharedKey[5];
   ueCb->ueInfo.sharedKey[6]  = pCfgReq->msg.ueCfgReq.sharedKey[6];
   ueCb->ueInfo.sharedKey[7]  = pCfgReq->msg.ueCfgReq.sharedKey[7];
   ueCb->ueInfo.sharedKey[8]  = pCfgReq->msg.ueCfgReq.sharedKey[8];
   ueCb->ueInfo.sharedKey[9]  = pCfgReq->msg.ueCfgReq.sharedKey[9];
   ueCb->ueInfo.sharedKey[10] = pCfgReq->msg.ueCfgReq.sharedKey[10];
   ueCb->ueInfo.sharedKey[11] = pCfgReq->msg.ueCfgReq.sharedKey[11];
   ueCb->ueInfo.sharedKey[12] = pCfgReq->msg.ueCfgReq.sharedKey[12];
   ueCb->ueInfo.sharedKey[13] = pCfgReq->msg.ueCfgReq.sharedKey[13];
   ueCb->ueInfo.sharedKey[14] = pCfgReq->msg.ueCfgReq.sharedKey[14];
   ueCb->ueInfo.sharedKey[15] = pCfgReq->msg.ueCfgReq.sharedKey[15];

   /* 69 d5 c2 eb 2e 2e 62 47 50 54 1d 3b bc 69 2b a5  */
   ueCb->ueInfo.opKey[0]  = pCfgReq->msg.ueCfgReq.opKey[0];
   ueCb->ueInfo.opKey[1]  = pCfgReq->msg.ueCfgReq.opKey[1];
   ueCb->ueInfo.opKey[2]  = pCfgReq->msg.ueCfgReq.opKey[2];
   ueCb->ueInfo.opKey[3]  = pCfgReq->msg.ueCfgReq.opKey[3];
   ueCb->ueInfo.opKey[4]  = pCfgReq->msg.ueCfgReq.opKey[4];
   ueCb->ueInfo.opKey[5]  = pCfgReq->msg.ueCfgReq.opKey[5];
   ueCb->ueInfo.opKey[6]  = pCfgReq->msg.ueCfgReq.opKey[6];
   ueCb->ueInfo.opKey[7]  = pCfgReq->msg.ueCfgReq.opKey[7];
   ueCb->ueInfo.opKey[8]  = pCfgReq->msg.ueCfgReq.opKey[8];
   ueCb->ueInfo.opKey[9]  = pCfgReq->msg.ueCfgReq.opKey[9];
   ueCb->ueInfo.opKey[10] = pCfgReq->msg.ueCfgReq.opKey[10];
   ueCb->ueInfo.opKey[11] = pCfgReq->msg.ueCfgReq.opKey[11];
   ueCb->ueInfo.opKey[12] = pCfgReq->msg.ueCfgReq.opKey[12];
   ueCb->ueInfo.opKey[13] = pCfgReq->msg.ueCfgReq.opKey[13];
   ueCb->ueInfo.opKey[14] = pCfgReq->msg.ueCfgReq.opKey[14];
   ueCb->ueInfo.opKey[15] = pCfgReq->msg.ueCfgReq.opKey[15];
   ueCb->srvPlmn[0] = pCfgReq->msg.ueCfgReq.srvPlmn[0];
   ueCb->srvPlmn[1] = pCfgReq->msg.ueCfgReq.srvPlmn[1];
   ueCb->srvPlmn[2] = pCfgReq->msg.ueCfgReq.srvPlmn[2];

   ueCb->ueCtxt.ueRadCap.pres = TRUE;
   ueCb->ueCtxt.ueRadCap.len = pCfgReq->msg.ueCfgReq.radCapIndRrcPdulen;
   ueCb->ueCtxt.ueRadCap.rrcPDU = (U8 *)ueAlloc(ueCb->ueCtxt.ueRadCap.len);

   cmMemcpy(ueCb->ueCtxt.ueRadCap.rrcPDU,
         pCfgReq->msg.ueCfgReq.radCapIndRrcPdu,
         pCfgReq->msg.ueCfgReq.radCapIndRrcPdulen);

   ueFree(pCfgReq->msg.ueCfgReq.radCapIndRrcPdu,
         pCfgReq->msg.ueCfgReq.radCapIndRrcPdulen);

   ret = ueDbmAddUe(ueCb);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Failed to add the UE Context");
      UE_LOG_EXITFN(ueAppCb, ret);
   }

   ret = sendUeConfigCompInd();

   RETVALUE(ret);
} /* ueProcUeConfigReq */

/*
 *
 *       Fun: sendUeAppCfgCompInd
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 sendUeAppCfgCompInd(Void)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   UetMessage *tfwMsg = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   tfwMsg = (UetMessage *)ueAlloc(sizeof(UetMessage));
   if (tfwMsg == NULLP)
   {
      UE_LOG_ERROR(ueAppCb, "Failed to allocate memeory");
      UE_LOG_EXITFN(ueAppCb, RFAILED);
   }

   cmMemset((U8*)tfwMsg, 0, sizeof(UetMessage));
   tfwMsg->msgType = UE_APP_CONFIG_COMPLETE_TYPE;

   ret = ueSendToTfwApp(tfwMsg, &ueAppCb->fwPst);
   RETVALUE(ret);
} /* sendUeAppCfgCompInd */

/*
 *
 *       Fun: ueAppUtlBldSecModReject
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppUtlBldSecModReject(UeCb *ueCb, CmNasEvnt **ueEvt, U8 cause)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   CmEmmMsg* emmMsg;
   CmEmmSecModeRej *secModRej;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Building Security Mode Reject  for Ue");

   if(ueEvt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /* Allocate memory for pdu */
   CM_ALLOC_NASEVNT (ueEvt, CM_EMM_PD);

   if(*ueEvt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   if (cmGetMem(&((*ueEvt)->memCp), sizeof(CmEmmMsg), (Ptr *)&emmMsg) != ROK)
   {
      CM_FREE_NASEVNT(ueEvt);
      RETVALUE(RFAILED);
   }

   (*ueEvt)->m.emmEvnt = emmMsg;
   secModRej = &((*ueEvt)->m.emmEvnt->u.secModRej);
   /*Fill header information*/
   /*(*ueEvt)->secHT = UE_APP_SEC_HT_INT_PRTD_ENC_NEW_SEC_CTXT;*/
   (*ueEvt)->secHT = CM_NAS_SEC_HDR_TYPE_PLAIN_NAS_MSG;

   /*(*ueEvt)->mac */

   /* Security header type is "Plain NAS message, not security protected" */
   /*emmMsg->secHdrType = CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG;*/
   emmMsg->secHdrType = CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG;
   emmMsg->msgId      = CM_EMM_MSG_SEC_MODE_REJ;
   emmMsg->protDisc   = CM_EMM_PD;
   /* Fill Security mode Reject EMM Cause */
   secModRej->cause.pres = TRUE;
   secModRej->cause.cause = cause;

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueAppUtlBldSecModComplete
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppUtlBldSecModComplete(UeCb *ueCb, UeUetSecModeComplete uetSmc, CmNasEvnt **ueEvt)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   CmEmmMsg* emmMsg;
   CmEmmSecModeCmp *secModeCmp = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Building Security Mode complete  for Ue");

   if(ueEvt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /* Allocate memory for pdu */
   CM_ALLOC_NASEVNT (ueEvt, CM_EMM_PD);

   if(*ueEvt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   if (cmGetMem(&((*ueEvt)->memCp), sizeof(CmEmmMsg), (Ptr *)&emmMsg) != ROK)
   {
      CM_FREE_NASEVNT(ueEvt);
      RETVALUE(RFAILED);
   }
   (*ueEvt)->m.emmEvnt = emmMsg;
   if (!uetSmc.noImeisv) {
     secModeCmp = &((*ueEvt)->m.emmEvnt->u.secModCmp);
     // Check if MME requested for imeisv in smc
     if (ueCb->ueCtxt.imeisvReq) {
       // Reset flag
       ueCb->ueCtxt.imeisvReq = FALSE;
       UE_LOG_DEBUG(ueAppCb, "Filling IMEISV in security mode complete");
       secModeCmp->imeisv.pres = TRUE;
       secModeCmp->imeisv.type = CM_EMM_MID_TYPE_IMEISV;
       secModeCmp->imeisv.len = CM_EMM_MAX_IMEI_DIGS;
       secModeCmp->imeisv.evenOddInd = (((secModeCmp->imeisv.len) % 2) != 0) ? \
                                     (UE_ODD):(UE_EVEN);

       if (!uetSmc.imeisvPres) {
         UE_LOG_DEBUG(ueAppCb, "Filling IMEISV from ueCb");
         cmMemcpy((U8 *)&secModeCmp->imeisv.u.imei.id,
                  (U8 *)&ueCb->ueCtxt.ueImei, secModeCmp->imeisv.len);
       } else {
         UE_LOG_DEBUG(ueAppCb, "Filling IMEISV"
                               "received from the test");
         cmMemcpy((U8 *)&secModeCmp->imeisv.u.imei.id,
                  uetSmc.imeisv, secModeCmp->imeisv.len);
         // Reset flag
         uetSmc.imeisvPres = FALSE;
       }
     }
   }

   /*Fill header information*/
   /*(*ueEvt)->secHT = UE_APP_SEC_HT_INT_PRTD_ENC_NEW_SEC_CTXT;*/
   (*ueEvt)->secHT = CM_NAS_SEC_HDR_TYPE_INT_PRTD_ENC_NEW_SEC_CTXT;

   /*(*ueEvt)->mac */

   /* Security header type is "Plain NAS message, not security protected" */
   /*emmMsg->secHdrType = CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG;*/
   emmMsg->secHdrType = CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG;
   emmMsg->msgId      = CM_EMM_MSG_SEC_MODE_CMP;
   emmMsg->protDisc   = CM_EMM_PD;

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueBldAttachRejectIndToTfw
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueBldAttachRejectIndToTfw(UetMessage *tfwMsg, UeCb *ueCb, U8 cause)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Building Attach Reject Indication to TFWAPP");
   tfwMsg->msgType = UE_ATTACH_REJ_TYPE;
   tfwMsg->msg.ueUetAttachRej.ueId = ueCb->ueId;
   tfwMsg->msg.ueUetAttachRej.cause = cause;

   UE_LOG_EXITFN(ueAppCb, ret);
}
/*
 *
 *       Fun: ueBldTauRejectIndToTfw
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueBldTauRejectIndToTfw(UetMessage *tfwMsg, UeCb *ueCb, U8 cause)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);

   UE_LOG_ENTERFN(ueAppCb);
   UE_LOG_DEBUG(ueAppCb, "Building Tracking Area Update  Reject Indication to TFWAPP");

   tfwMsg->msgType = UE_TAU_REJECT_TYPE;
   tfwMsg->msg.ueUetTauReject.ueId  = ueCb->ueId;
   tfwMsg->msg.ueUetTauReject.cause = cause;

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueBldDetachAcceptIndToTfw
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueBldDetachAcceptIndToTfw(UetMessage *tfwMsg, UeCb *ueCb, U8 status)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Building Detach Accept Indication to TFWAPP");
   tfwMsg->msgType = UE_DETACH_ACCEPT_IND_TYPE;
   tfwMsg->msg.ueUetDetachAcceptInd.ueId = ueCb->ueId;

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueBldServiceRejectIndToTfw
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueBldServiceRejectIndToTfw
(
 UetMessage *tfwMsg,
 UeCb *ueCb,
 U8 cause
)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Building Service Reject Indication to TFWAPP");
   tfwMsg->msgType = UE_SERVICE_REJ_TYPE;
   tfwMsg->msg.ueUetServiceRej.ueId = ueCb->ueId;
   tfwMsg->msg.ueUetServiceRej.cause = cause;

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueBldNwInitDetachReqToTfw
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */

PRIVATE S16 ueBldNwInitDetachReqToTfw
(
 UetMessage *tfwMsg,
 UeCb *ueCb,
 CmEmmDetachType detachType,
 CmEmmCause emmCause
)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Building Network Initiate Detach request to TFWAPP");
   tfwMsg->msgType = UE_NW_INIT_DETACH_REQUEST_TYPE;
   tfwMsg->msg.ueUetNwInitDetachReq.ueId = ueCb->ueId;
   if (detachType.pres == TRUE)
   {
      tfwMsg->msg.ueUetNwInitDetachReq.ueNwInitDetType = detachType.type;
   }
   else
   {
      tfwMsg->msg.ueUetNwInitDetachReq.ueNwInitDetType = 0;
   }
   if (emmCause.pres == TRUE)
   {
      tfwMsg->msg.ueUetNwInitDetachReq.cause = emmCause.cause;
   }
   else
   {
      tfwMsg->msg.ueUetNwInitDetachReq.cause = 0;
   }

   UE_LOG_EXITFN(ueAppCb, ret);
}



/*
 *
 *       Fun: ueAppUtlBldActDefltBerContextAccept
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppUtlBldActDefltBerContextAccept
(
 UeCb *ueCb,
 CmNasEvnt **esmEvnt,
 U8 epsBearerId
)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   CmEsmMsg    *msg = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);
   UE_LOG_DEBUG(ueAppCb, "Building UE Activate Default Bearer Context Accept");

   if(ueCb == NULLP || esmEvnt == NULLP)
   {
      ret = RFAILED;
      RETVALUE(ret);
   }

   /* Allocate memory for mme evnt */
   CM_ALLOC_NASEVNT (esmEvnt, CM_ESM_PD);

   if (*esmEvnt == NULLP)
   {
      ret = RFAILED;
      RETVALUE(ret);
   }
   /*Allocate memory for ESM message*/
   if (cmGetMem(&(*esmEvnt)->memCp, sizeof(CmEsmMsg), (Ptr *)&msg) != ROK)
   {
      CM_FREE_NASEVNT(esmEvnt);
      RETVALUE(RFAILED);
   }

   (*esmEvnt)->m.esmEvnt = msg;
   msg->protDisc = CM_ESM_PD;

   /* Fill ESM Acticate defauld berer context accept message */
   /* Fill mandatory IE's*/

   /* EPS barer ID IE*/
   msg->bearerId = epsBearerId;

   /* Procedure transaction identity IE*/
   /* TODO:   msg->prTxnId  = ueCb->esmBList[UE_APP_EPS_DFLT_BEARER_INDX]->tId;*/

   /* Activate defaule EPS barer context accept*/
   msg->msgType = CM_ESM_MSG_ACTV_DEF_BEAR_ACC;
   ueCb->numPdns ++;
   UE_LOG_EXITFN(ueAppCb, ret);
}
/*
 *
 *       Fun: ueAppUtlBldActDfltBerContextReject
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppUtlBldActDfltBerContextReject
(
 UeCb *ueCb,
 CmNasEvnt **esmEvnt,
 U8 epsBearerId
)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   CmEsmMsg    *msg = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);
   UE_LOG_DEBUG(ueAppCb, "Building UE Activate Default EPS Bearer Context Reject");

   if(ueCb == NULLP || esmEvnt == NULLP)
   {
      ret = RFAILED;
      RETVALUE(ret);
   }

   /* Allocate memory for mme evnt */
   CM_ALLOC_NASEVNT (esmEvnt, CM_ESM_PD);

   if (*esmEvnt == NULLP)
   {
      ret = RFAILED;
      RETVALUE(ret);
   }
   /*Allocate memory for ESM message*/
   if (cmGetMem(&(*esmEvnt)->memCp, sizeof(CmEsmMsg), (Ptr *)&msg) != ROK)
   {
      CM_FREE_NASEVNT(esmEvnt);
      RETVALUE(RFAILED);
   }

   (*esmEvnt)->m.esmEvnt = msg;
   msg->protDisc = CM_ESM_PD;

   /* Fill mandatory IE's*/

   /* EPS barer ID IE*/
   msg->bearerId = epsBearerId;
   msg->u.actRej.cause.pres = TRUE;
   msg->u.actRej.cause.val = ueCb->actv_dflt_eps_bear_ctxt_reject_cause;
   msg->msgType = CM_ESM_MSG_ACTV_DEF_BEAR_REJ;
   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueAppUtlBldDeActvBerContextAccept
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppUtlBldDeActvBerContextAccept
(
 UeCb *ueCb,
 CmNasEvnt **esmEvnt,
 U8 epsBearerId
)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   CmEsmMsg    *msg = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);
   UE_LOG_DEBUG(ueAppCb, "Building UE De Activate Bearer Context Accept");
   if(ueCb == NULLP || esmEvnt == NULLP)
   {
      ret = RFAILED;
      RETVALUE(ret);
   }

   /* Allocate memory for mme evnt */
   CM_ALLOC_NASEVNT (esmEvnt, CM_ESM_PD);

   if (*esmEvnt == NULLP)
   {
      ret = RFAILED;
      RETVALUE(ret);
   }
   /*Allocate memory for ESM message*/
   if (cmGetMem(&(*esmEvnt)->memCp, sizeof(CmEsmMsg), (Ptr *)&msg) != ROK)
   {
      CM_FREE_NASEVNT(esmEvnt);
      RETVALUE(RFAILED);
   }

   (*esmEvnt)->m.esmEvnt = msg;
   msg->protDisc = CM_ESM_PD;

   /* Fill mandatory IE's*/

   /* EPS barer ID IE*/
   msg->bearerId = epsBearerId;

   /* Activate defaule EPS barer context accept*/
   msg->msgType  = CM_ESM_MSG_DEACTV_BEAR_ACC;
   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueAppUtlBldActDedBerContextAccept
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppUtlBldActDedBerContextAccept
(
 UeCb *ueCb,
 CmNasEvnt **esmEvnt,
 U8 epsBearerId
)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   CmEsmMsg    *msg = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);
   UE_LOG_DEBUG(ueAppCb, "Building UE Activate Dedicate Bearer Context Accept");
   if(ueCb == NULLP || esmEvnt == NULLP)
   {
      ret = RFAILED;
      RETVALUE(ret);
   }

   /* Allocate memory for mme evnt */
   CM_ALLOC_NASEVNT (esmEvnt, CM_ESM_PD);

   if (*esmEvnt == NULLP)
   {
      ret = RFAILED;
      RETVALUE(ret);
   }
   /*Allocate memory for ESM message*/
   if (cmGetMem(&(*esmEvnt)->memCp, sizeof(CmEsmMsg), (Ptr *)&msg) != ROK)
   {
      CM_FREE_NASEVNT(esmEvnt);
      RETVALUE(RFAILED);
   }

   (*esmEvnt)->m.esmEvnt = msg;
   msg->protDisc = CM_ESM_PD;

   /* Fill mandatory IE's*/

   /* EPS barer ID IE*/
   msg->bearerId = epsBearerId;

   /* Activate Dedicated EPS bearer context accept*/
   msg->msgType  = CM_ESM_MSG_ACTV_DED_BEAR_ACC;
   UE_LOG_EXITFN(ueAppCb, ret);
}


/*
 *
 *       Fun: ueAppUtlBldActDedBerContextReject
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppUtlBldActDedBerContextReject
(
 UeCb *ueCb,
 CmNasEvnt **esmEvnt,
 U8 epsBearerId,
 U8 esmCause
)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   CmEsmMsg    *msg = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);
   UE_LOG_DEBUG(ueAppCb, "Building UE Activate Dedicate Bearer Context Reject");

   if(ueCb == NULLP || esmEvnt == NULLP)
   {
      ret = RFAILED;
      RETVALUE(ret);
   }

   /* Allocate memory for mme evnt */
   CM_ALLOC_NASEVNT (esmEvnt, CM_ESM_PD);

   if (*esmEvnt == NULLP)
   {
      ret = RFAILED;
      RETVALUE(ret);
   }
   /*Allocate memory for ESM message*/
   if (cmGetMem(&(*esmEvnt)->memCp, sizeof(CmEsmMsg), (Ptr *)&msg) != ROK)
   {
      CM_FREE_NASEVNT(esmEvnt);
      RETVALUE(RFAILED);
   }

   (*esmEvnt)->m.esmEvnt = msg;
   msg->protDisc = CM_ESM_PD;

   /* Fill mandatory IE's*/

   /* EPS barer ID IE*/
   msg->bearerId = epsBearerId;
   msg->u.actDedBearRej.cause.pres = TRUE;
   msg->u.actDedBearRej.cause.val = esmCause;
   msg->msgType = CM_ESM_MSG_ACTV_DED_BEAR_REJ;
   UE_LOG_EXITFN(ueAppCb, ret);
}
/*
 *
 *       Fun: ueAppUtlBldEmmStatus
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppUtlBldEmmStatus(UeCb *ueCb, CmNasEvnt **ueEvt, U8 cause)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   CmEmmStatus  *emmStatusMsg;
   CmEmmMsg* emmMsg;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);
   UE_LOG_DEBUG(ueAppCb, "Building UE Emm Status message To EnodeB");

   if(ueEvt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /* Allocate memory for pdu */
   CM_ALLOC_NASEVNT (ueEvt, CM_EMM_PD);

   if(*ueEvt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   if (cmGetMem(&((*ueEvt)->memCp), sizeof(CmEmmMsg), (Ptr *)&emmMsg) != ROK)
   {
      CM_FREE_NASEVNT(ueEvt);
      RETVALUE(RFAILED);
   }

   (*ueEvt)->m.emmEvnt = emmMsg;
   emmStatusMsg = &((*ueEvt)->m.emmEvnt->u.emmSts);

   /* Fill header information*/
   (*ueEvt)->secHT = CM_NAS_SEC_HDR_TYPE_INT_PRTD_ENC;

   /* Security header type is "Plain NAS message, not security protected" */
   emmMsg->secHdrType = CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG;
   emmMsg->msgId = CM_EMM_MSG_EMM_STS;
   emmMsg->protDisc = CM_EMM_PD;

   /* Fill mandatory IEs */

   emmMsg->u.emmSts.emmCause.pres = TRUE;
   emmMsg->u.emmSts.emmCause.cause = cause;

   UE_LOG_EXITFN(ueAppCb, ret);
}
/*
 *
 *       Fun: ueAppUtlBldAttachComplete
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppUtlBldAttachComplete(UeCb *ueCb, CmNasEvnt **ueEvt)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   CmEmmAttachComplete  *attachCmplt;
   CmEmmMsg* emmMsg;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);
   UE_LOG_DEBUG(ueAppCb, "Building UE Attach Complete message To EnodeB");

   if(ueEvt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /* Allocate memory for pdu */
   CM_ALLOC_NASEVNT (ueEvt, CM_EMM_PD);

   if(*ueEvt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   if (cmGetMem(&((*ueEvt)->memCp), sizeof(CmEmmMsg), (Ptr *)&emmMsg) != ROK)
   {
      CM_FREE_NASEVNT(ueEvt);
      RETVALUE(RFAILED);
   }

   (*ueEvt)->m.emmEvnt = emmMsg;
   attachCmplt = &((*ueEvt)->m.emmEvnt->u.atchCmp);

   /* Fill header information*/
   (*ueEvt)->secHT = CM_NAS_SEC_HDR_TYPE_INT_PRTD_ENC;

   /* Security header type is "Plain NAS message, not security protected" */
   emmMsg->secHdrType = CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG;
   emmMsg->msgId = CM_EMM_MSG_ATTACH_CMP;
   emmMsg->protDisc = CM_EMM_PD;

   /* Fill mandatory IEs */
   /* ESM message container IE*/
   if (ueCb->is_actv_dflt_eps_ber_ctxt_rej == TRUE)
   {
      if((ret = ueAppUtlBldActDfltBerContextReject(ueCb, &(attachCmplt->esmEvnt),
                  ueCb->ueRabCb[0].epsBearerId)) != ROK)
      {
         UE_LOG_ERROR(ueAppCb, "Building Activate Default Bearer Context Reject "\
			 "message failed");
	 CM_FREE_NASEVNT(ueEvt);
	 RETVALUE(RFAILED);
      }
   }
   else
   {
      if((ret = ueAppUtlBldActDefltBerContextAccept(ueCb, &(attachCmplt->esmEvnt),
                  ueCb->ueRabCb[0].epsBearerId)) != ROK)
      {
         UE_LOG_ERROR(ueAppCb, "Building Activate Default Bearer Context Accept "\
			 "message failed");
	 CM_FREE_NASEVNT(ueEvt);
	 RETVALUE(RFAILED);
      }
   }

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueAppSndAttachComplete
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppSndAttachComplete(UeCb *ueCb)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   UeAppMsg     srcMsg;
   UeAppMsg     dstMsg;
   CmNasEvnt   *attachCompEvnt = NULLP;
   NhuDedicatedInfoNAS nasEncPdu;
   NbuUlNasMsg *pUlNbMsg = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Sending UE Attach Complete message To EnodeB");

   ret = ueAppUtlBldAttachComplete(ueCb, &attachCompEvnt);
   if(ROK != ret)
   {
      UE_LOG_ERROR(ueAppCb, "Building Attach Complete failed");
      ret = RFAILED;
      RETVALUE(ret);
   }

   cmMemset((U8 *)&nasEncPdu, 0, sizeof(NhuDedicatedInfoNAS));
   pUlNbMsg = (NbuUlNasMsg *)ueAlloc(sizeof(NbuUlNasMsg));

   ret = ueAppEdmEncode(attachCompEvnt, &nasEncPdu);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Encoding failed");
      ret = RFAILED;
      RETVALUE(ret);
   }
   /** Integrity Protected **/
   if(CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG != attachCompEvnt->secHT)
   {
      srcMsg.val = nasEncPdu.val;
      srcMsg.len = nasEncPdu.len;
      ret = ueAppCmpUplnkSec(&ueCb->secCtxt, attachCompEvnt->secHT, &srcMsg,
            &dstMsg);
      if(ROK != ret)
      {
         UE_LOG_ERROR(ueAppCb, "Uplink Security Failed");
         attachCompEvnt->pdu = NULLP;
         CM_FREE_NASEVNT(&attachCompEvnt);
         EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
         RETVALUE(ret);
      }
      EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
      nasEncPdu.val = dstMsg.val;
      nasEncPdu.len = dstMsg.len;
   }
   CM_FREE_NASEVNT(&attachCompEvnt);

   pUlNbMsg->ueId        = ueCb->ueId;
   pUlNbMsg->nasPdu.pres = TRUE;
   pUlNbMsg->nasPdu.len  = nasEncPdu.len;
   pUlNbMsg->nasPdu.val  = (U8 *)ueAlloc(pUlNbMsg->nasPdu.len);
   cmMemcpy((U8 *)pUlNbMsg->nasPdu.val, (U8 *)nasEncPdu.val,
         pUlNbMsg->nasPdu.len );

   ret = ueSendUlNasMsgToNb(pUlNbMsg,&ueAppCb->nbPst);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Could not Send the Attach Complete message");
      RETVALUE(RFAILED);
   }
   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueProcUeAttachComplete
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueProcUeAttachComplete(UetMessage *p_ueMsg, Pst *pst)
{
   S16 ret = ROK;
   U32  ueId;
   UeAppCb *ueAppCb = NULLP;
   UeCb *ueCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);
   UE_LOG_DEBUG(ueAppCb, "Processing UE Attach Complete message from TFWAPP");

   ueId = p_ueMsg->msg.ueUetAttachComplete.ueId;
   ret = ueDbmFetchUe(ueId,(PTR*)&ueCb);
   if( ret != ROK )
   {
      UE_LOG_ERROR(ueAppCb, "UeCb List NULL ueId = %d", ueId);
      RETVALUE(ret);
   }
   /* mark as ue connected */
   ueCb->ecmCb.state = UE_ECM_CONNECTED;
   ret = ueAppSndAttachComplete(ueCb);

   UE_LOG_EXITFN(ueAppCb, ret);
}
/*
 *
 *       Fun: ueProcUeAttachCompleteWithActvDfltBerCtxtRej
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueProcUeAttachCompleteWithActvDfltBerCtxtRej(UetMessage *p_ueMsg, Pst *pst)
{
   S16 ret = ROK;
   U32  ueId;
   UeAppCb *ueAppCb = NULLP;
   UeCb *ueCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);
   UE_LOG_DEBUG(ueAppCb, "Processing UE Attach Complete + Activate Default EPS Bearer Context Rejectmessage from TFWAPP");

   ueId = p_ueMsg->msg.ueActDfltBerRej.ueId;
   ret = ueDbmFetchUe(ueId,(PTR*)&ueCb);
   if( ret != ROK )
   {
      UE_LOG_ERROR(ueAppCb, "UeCb List NULL ueId = %d", ueId);
      RETVALUE(ret);
   }
   /* mark as ue connected */
   ueCb->ecmCb.state = UE_ECM_CONNECTED;
   ueCb->is_actv_dflt_eps_ber_ctxt_rej = TRUE;
   ueCb->actv_dflt_eps_bear_ctxt_reject_cause = p_ueMsg->msg.ueActDfltBerRej.esmCause;
   ret = ueAppSndAttachComplete(ueCb);

   UE_LOG_EXITFN(ueAppCb, ret);
}
/*
 *
 *       Fun: ueProcUeAttachFail
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueProcUeAttachFail(UetMessage *p_ueMsg, Pst *pst)
{
   S16 ret = ROK;
   U32  ueId;
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);
   UE_LOG_DEBUG(ueAppCb, "Processing UE Attach Fail from TFWAPP");

   ueId = p_ueMsg->msg.ueUetAttachFail.ueId;
   UE_LOG_DEBUG(ueAppCb, "Attach failed for ueId = %d", ueId);

   /* Delete the UE from DB */
   UE_LOG_DEBUG(ueAppCb, "Delete UE context from UE DB");
   ret = ueDbmDelUe(ueAppCb, ueId);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "UeCb List NULL ueId = %d", ueId);
      RETVALUE(ret);
   }

   UE_LOG_EXITFN(ueAppCb, ret);
}


/*
 *
 *       Fun: ueProcUeSecModeRejectCmd
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueProcUeSecModeRejectCmd(UetMessage *p_ueMsg, Pst *pst)
{
   S16 ret = ROK;
   U32 ueId;
   UeAppCb *ueAppCb = NULLP;
   UeCb *ueCb = NULLP;
   U8           cause;

   CmNasEvnt   *secModeRejEvnt = NULLP;
   NbuUlNasMsg *pUlNbMsg = NULLP;
   NhuDedicatedInfoNAS  nasEncPdu;
   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);
   ueId = p_ueMsg->msg.ueUetSecModeReject.ueId;
   cause = p_ueMsg->msg.ueUetSecModeReject.cause;
   /* Fetching the UeCb */
   ret = ueDbmFetchUe(ueId, (PTR *)&ueCb);
   if( ret != ROK )
   {
      UE_LOG_ERROR(ueAppCb, "UeCb List NULL ueId = %d", ueId);
      RETVALUE(ret);
   }

   ret = ueAppUtlBldSecModReject(ueCb, &secModeRejEvnt,cause);
   if(ROK != ret)
   {
      UE_LOG_ERROR(ueAppCb, "Could not build  and send the "\
            "security mode Reject");
      RETVALUE(ret);
   }

   cmMemset((U8 *)&nasEncPdu, 0, sizeof(NhuDedicatedInfoNAS));
   pUlNbMsg = (NbuUlNasMsg *)ueAlloc(sizeof(NbuUlNasMsg));
   /* Encoding Nas PDU */
   ret = ueAppEdmEncode(secModeRejEvnt, &nasEncPdu);
   if(ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Encoding failed");
      CM_FREE_NASEVNT(&secModeRejEvnt);
      RETVALUE(ret);
   }

   /** Integrity Protected
   if(CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG != secModeCompEvnt->secHT)
   {
      srcMsg.val = nasEncPdu.val;
      srcMsg.len = nasEncPdu.len;
      ret = ueAppCmpUplnkSec(&ueCb->secCtxt, secModeCompEvnt->secHT, &srcMsg, &dstMsg);
      if(ROK != ret)
      {
         UE_LOG_ERROR(ueAppCb, "Uplink Security Failed");
         secModeCompEvnt->pdu = NULLP;
         CM_FREE_NASEVNT(&secModeCompEvnt);
         EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
         RETVALUE(ret);
      }
      EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
      nasEncPdu.val = dstMsg.val;
      nasEncPdu.len = dstMsg.len;
   }
   Integrity Protected */
   CM_FREE_NASEVNT(&secModeRejEvnt);
   /** END **/
   /* NB message filliing */
   pUlNbMsg->ueId        = ueCb->ueId;
   pUlNbMsg->nasPdu.pres = TRUE;
   pUlNbMsg->nasPdu.len  = nasEncPdu.len;

   pUlNbMsg->nasPdu.val = (U8 *)ueAlloc(pUlNbMsg->nasPdu.len);
   cmMemcpy((U8 *)pUlNbMsg->nasPdu.val, (U8 *)nasEncPdu.val, pUlNbMsg->nasPdu.len );

   ret = ueSendUlNasMsgToNb(pUlNbMsg,&ueAppCb->nbPst);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Could not Send Security Mode Reject NAS message");
      RETVALUE(RFAILED);
   }
   EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *       Fun: ueProcUeSecModeCmdComplete
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 */
PRIVATE S16 ueProcUeSecModeCmdComplete(UetMessage *p_ueMsg, Pst *pst)
{
   S16 ret = ROK;
   U32 ueId;
   UeAppCb *ueAppCb = NULLP;
   UeCb *ueCb = NULLP;
   UeAppMsg     srcMsg;
   UeAppMsg     dstMsg;

   CmNasEvnt   *secModeCompEvnt = NULLP;
   NbuUlNasMsg *pUlNbMsg = NULLP;
   NhuDedicatedInfoNAS  nasEncPdu;
   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);
   ueId = p_ueMsg->msg.ueUetSecModeComplete.ueId;

   /* Fetching the UeCb */
   ret = ueDbmFetchUe(ueId, (PTR *)&ueCb);
   if( ret != ROK )
   {
      UE_LOG_ERROR(ueAppCb, "UeCb List NULL ueId = %d", ueId);
      RETVALUE(ret);
   }

   ret = ueAppUtlBldSecModComplete(ueCb, p_ueMsg->msg.ueUetSecModeComplete,
         &secModeCompEvnt);
   if(ROK != ret)
   {
      UE_LOG_ERROR(ueAppCb, "Could not build  and send the "\
            "security mode complete");
      RETVALUE(ret);
   }

   cmMemset((U8 *)&nasEncPdu, 0, sizeof(NhuDedicatedInfoNAS));
   pUlNbMsg = (NbuUlNasMsg *)ueAlloc(sizeof(NbuUlNasMsg));
   /* Encoding Nas PDU */
   ret = ueAppEdmEncode(secModeCompEvnt, &nasEncPdu);
   if(ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Encoding failed");
      CM_FREE_NASEVNT(&secModeCompEvnt);
      RETVALUE(ret);
   }
   /** Integrity Protected **/
   if(CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG != secModeCompEvnt->secHT)
   {
      srcMsg.val = nasEncPdu.val;
      srcMsg.len = nasEncPdu.len;
      ret = ueAppCmpUplnkSec(&ueCb->secCtxt, secModeCompEvnt->secHT, &srcMsg,
            &dstMsg);
      if(ROK != ret)
      {
         UE_LOG_ERROR(ueAppCb, "Uplink Security Failed");
         secModeCompEvnt->pdu = NULLP;
         CM_FREE_NASEVNT(&secModeCompEvnt);
         EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
         RETVALUE(ret);
      }
      EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
      nasEncPdu.val = dstMsg.val;
      nasEncPdu.len = dstMsg.len;
   }
   CM_FREE_NASEVNT(&secModeCompEvnt);
   /** END **/
   /* NB message filliing */
   pUlNbMsg->ueId        = ueCb->ueId;
   pUlNbMsg->nasPdu.pres = TRUE;
   pUlNbMsg->nasPdu.len  = nasEncPdu.len;

   pUlNbMsg->nasPdu.val = (U8 *)ueAlloc(pUlNbMsg->nasPdu.len);
   cmMemcpy((U8 *)pUlNbMsg->nasPdu.val, (U8 *)nasEncPdu.val,
         pUlNbMsg->nasPdu.len);

   ret = ueSendUlNasMsgToNb(pUlNbMsg,&ueAppCb->nbPst);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Could not Send the Authentication response");
      RETVALUE(RFAILED);
   }

   UE_LOG_EXITFN(ueAppCb, ret);
} /* ueProcUeSecModeCmdComplete */

/*
 *
 *       Fun: ueAppUtlBldDetachReq
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppUtlBldDetachReq
(
 UeCb *ueCb,
 CmNasEvnt **ueEvt,
 U8 detachType,
 U8 miType,
 U8 detCause
)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   CmEmmDetachReq  *detachReq = NULLP;
   CmEmmMsg* emmMsg;
   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Building Detach Request for Ue");

   if (ueEvt == NULLP)
   {
      RETVALUE(RFAILED);
   }

   /* Allocate memory for pdu */
   CM_ALLOC_NASEVNT (ueEvt, CM_EMM_PD);

   if (*ueEvt == NULLP)
   {
      UE_LOG_ERROR(ueAppCb, "Failed to allocate memory to NAS event\n");
      RETVALUE(RFAILED);
   }

   if (cmGetMem(&((*ueEvt)->memCp), sizeof(CmEmmMsg), (Ptr *)&emmMsg) != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Failed to allocate memory to EMM msg\n");
      CM_FREE_NASEVNT(ueEvt);
      RETVALUE(RFAILED);
   }

   (*ueEvt)->m.emmEvnt = emmMsg;
   detachReq = &((*ueEvt)->m.emmEvnt->u.dtchReq);

   if(ueCb->ecmCb.state == UE_ECM_IDLE)
   {
      /*Fill header information*/
      (*ueEvt)->secHT = CM_NAS_SEC_HDR_TYPE_INT_PRTD;
   }
   else
   {
      /*Fill header information*/
      (*ueEvt)->secHT = CM_NAS_SEC_HDR_TYPE_INT_PRTD_ENC;
   }
   /* Security header type is "Plain NAS message, not security protected" */
   emmMsg->secHdrType = CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG;
   emmMsg->msgId = CM_EMM_MSG_DETACH_REQ;
   emmMsg->protDisc = CM_EMM_PD;

   /* Fill mandatory IEs */
   /*detach type IE*/
   detachReq->detchType.pres = TRUE;
   detachReq->detchType.type = detachType;
   detachReq->detchType.switchOff = detCause;

   /*NAS key set identifier IE*/
   detachReq->nasKsi.pres = TRUE;
   detachReq->nasKsi.id = ueCb->secCtxt.ksi;
   detachReq->nasKsi.tsc = ueCb->secCtxt.tsc;

   switch (miType)
   {
      case CM_EMM_MID_TYPE_IMSI:
      {
         detachReq->epsMi.pres = TRUE;
         detachReq->epsMi.type = CM_EMM_MID_TYPE_IMSI;
         detachReq->epsMi.len = 15; /*cmStrlen(ueCb->ueCtxt.ueImsi);*/
         detachReq->epsMi.evenOddInd = (((detachReq->epsMi.len)%2) != 0) ? \
                                       UE_ODD : UE_EVEN;
         cmMemcpy((U8 *)&detachReq->epsMi.u.imsi.id, (U8 *)&ueCb->ueCtxt.\
                  ueImsi, detachReq->epsMi.len);
         break;
      }
      case CM_EMM_MID_TYPE_GUTI:
      {
         detachReq->epsMi.pres = TRUE;
         detachReq->epsMi.type = CM_EMM_MID_TYPE_GUTI;
         detachReq->epsMi.evenOddInd = UE_EVEN;
         detachReq->epsMi.len  = sizeof(GUTI);
         cmMemcpy((U8 *)&detachReq->epsMi.u.guti, (U8 *)&ueCb->ueCtxt.ueGuti,
                  sizeof(GUTI));
         break;
      }
      default:
      {
         UE_LOG_ERROR(ueAppCb, "Invalid miType\n");
         ret = RFAILED;
         break;
      }
   }

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueSendDetachRequest
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueSendDetachRequest
(
 UeCb *ueCb,
 U8 detCause
)
{
   S16 ret = ROK;
   U8 isPlainMsg = TRUE;
   UeAppCb *ueAppCb = NULLP;
   CmNasEvnt *detachReq = NULLP;
   NbuInitialUeMsg *nbuInitialUeMsg = NULLP;
   NbuUlNasMsg *pUlNbMsg = NULLP;
   NhuDedicatedInfoNAS nasEncPdu = {0};
   UeAppMsg srcMsg;
   UeAppMsg dstMsg;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   ret = ueAppUtlBldDetachReq(ueCb, &detachReq, UE_DETACH_EPS,
         CM_EMM_MID_TYPE_GUTI, detCause);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Building DetachReq Failed\n");
      RETVALUE(RFAILED);
   }
   cmMemset((U8 *)&nasEncPdu, 0, sizeof(NhuDedicatedInfoNAS));

   ret = ueAppEdmEncode(detachReq, &nasEncPdu);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Encoding failed");
      CM_FREE_NASEVNT(&detachReq);
      RETVALUE(RFAILED);
   }

   /** Integrity Protected **/
   if(CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG != detachReq->secHT)
   {
      isPlainMsg = FALSE;
      srcMsg.val = nasEncPdu.val;
      srcMsg.len = nasEncPdu.len;
#if 0
      printf("\n**************ueCb Security Context Details***************\n");
      printf("dlSeqNmb = %d\n",ueCb->secCtxt.dlSeqNmb.seqNmb);
      printf("ulSeqNmb = %d\n",ueCb->secCtxt.ulSeqNmb.seqNmb);
      printf("lstUsdCnt = %d\n",ueCb->secCtxt.lstUsdCnt);

      printf("\nintKey:");
      for (count = 0; count < 16; count ++)
      printf("%x " ,ueCb->secCtxt.intKey[count]);

      printf("\nencKey:");
      for (count = 0; count < 16; count ++)
      printf("%x " ,ueCb->secCtxt.encKey[count]);

      printf("\nNas PDU:\n");
      printf("\nNas PDU len:%d\n", nasEncPdu.len);
      for (count = 0; count < nasEncPdu.len; count ++)
      printf("%x ", *(srcMsg.val + count));
#endif
      ret = ueAppCmpUplnkSec(&ueCb->secCtxt, detachReq->secHT, &srcMsg,
            &dstMsg);
      if(ROK != ret)
      {
         UE_LOG_ERROR(ueAppCb, "Uplink Security Failed");
         detachReq->pdu = NULLP;
         CM_FREE_NASEVNT(&detachReq);
         EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
         RETVALUE(ret);
      }
      EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
      nasEncPdu.val = dstMsg.val;
      nasEncPdu.len = dstMsg.len;
   }
   CM_FREE_NASEVNT(&detachReq);

   if(ueCb->ecmCb.state == UE_ECM_IDLE)
   {
      nbuInitialUeMsg = (NbuInitialUeMsg *)ueAlloc(sizeof(NbuInitialUeMsg));
      nbuInitialUeMsg->ueId = ueCb->ueId;
      nbuInitialUeMsg->rrcCause = 3;

      nbuInitialUeMsg->stmsi.pres  = TRUE;
      nbuInitialUeMsg->stmsi.mmec  = ueCb->ueCtxt.ueGuti.mmeCode;
      nbuInitialUeMsg->stmsi.mTMSI = ueCb->ueCtxt.ueGuti.mTMSI;

      nbuInitialUeMsg->nasPdu.pres = TRUE;
      nbuInitialUeMsg->nasPdu.len = nasEncPdu.len;
      nbuInitialUeMsg->nasPdu.val = (U8 *)ueAlloc(nbuInitialUeMsg->nasPdu.len);
      cmMemcpy((U8 *)nbuInitialUeMsg->nasPdu.val, nasEncPdu.val,
            nbuInitialUeMsg->nasPdu.len);

      ret = ueSendInitialUeMsg(nbuInitialUeMsg, &ueAppCb->nbPst);
      if (ret != ROK)
      {
         UE_LOG_ERROR(ueAppCb, "Sending Detach Request to eNodeB failed");
         ret = RFAILED;
      }
   }
   else
   {
      pUlNbMsg = (NbuUlNasMsg *)ueAlloc(sizeof(NbuUlNasMsg));
      pUlNbMsg->ueId        = ueCb->ueId;
      pUlNbMsg->nasPdu.pres = TRUE;
      pUlNbMsg->nasPdu.len  = nasEncPdu.len;
      pUlNbMsg->nasPdu.val = (U8 *)ueAlloc(pUlNbMsg->nasPdu.len);
      cmMemcpy((U8 *)pUlNbMsg->nasPdu.val, (U8 *)nasEncPdu.val,
            pUlNbMsg->nasPdu.len);

      ret = ueSendUlNasMsgToNb(pUlNbMsg, &ueAppCb->nbPst);
      if (ret != ROK)
      {
         UE_LOG_ERROR(ueAppCb, "Could not Send the Detach Request message");
         RETVALUE(RFAILED);
      }
   }

   if(isPlainMsg)
   {
      EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
   }

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueProcUeDetachRequest
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueProcUeDetachRequest
(
 UetMessage *p_ueMsg,
 Pst *pst
)
{
   S16 ret = ROK;
   U32  ueId;
   U8 detCause;
   UeAppCb *ueAppCb = NULLP;
   UeCb *ueCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Recieved Ue Detach Request");
   ueId = p_ueMsg->msg.ueUetDetachReq.ueId;
   ret = ueDbmFetchUe(ueId, (PTR *)&ueCb);
   if(ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "UeCb is empty for ueId = %d", ueId);
      UE_LOG_EXITFN(ueAppCb, ret);
   }
   if(p_ueMsg->msg.ueUetDetachReq.ueDetType == UET_NORMAL_DETACH)
   {
      detCause = UE_DETACH_NORMAL;
   }
   else if(p_ueMsg->msg.ueUetDetachReq.ueDetType == UET_SWITCHOFF_DETACH)
   {
      detCause = UE_DETACH_SWITCHOFF;
   }
   else
   {
      UE_LOG_ERROR(ueAppCb, "Invalid Detach Cause Recieved");
      UE_LOG_EXITFN(ueAppCb, RFAILED);
   }

   ret = ueSendDetachRequest(ueCb, detCause);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Sending Detach Request message failed");
      UE_LOG_EXITFN(ueAppCb, ret);
   }
   /* Free all the DRBs allocated for this ueId */
   UE_LOG_DEBUG(ueAppCb, "Freeing all the DRBs allocated for ueId: %d", ueId);
   for (U8 idx = 0; idx < UE_APP_MAX_DRBS; idx++) {
     cmMemset((U8 *)&(ueCb->ueRabCb[idx]), 0, sizeof(ueCb->ueRabCb[idx]));
     ueCb->drbs[idx] = UE_APP_DRB_AVAILABLE;
     ueCb->numRabs--;
   }

   UE_LOG_EXITFN(ueAppCb, ret);
} /* ueProcUeDetachRequest */

/*
 *
 *       Fun: ueAppUtlBldUeTrigDetachAcc
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppUtlBldUeTrigDetachAcc
(
 CmNasEvnt **ueEvt
)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
/*   CmEmmDetachReq  *detachReq = NULLP;*/
   CmEmmDetachAcc  *dtchAcc = NULLP;
   CmEmmMsg* emmMsg;
   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Building Detach Request for Ue");

   if (ueEvt == NULLP)
   {
      RETVALUE(RFAILED);
   }

   /* Allocate memory for pdu */
   CM_ALLOC_NASEVNT (ueEvt, CM_EMM_PD);

   if (*ueEvt == NULLP)
   {
      UE_LOG_ERROR(ueAppCb, "Failed to allocate memory to NAS event\n");
      RETVALUE(RFAILED);
   }

   if (cmGetMem(&((*ueEvt)->memCp), sizeof(CmEmmMsg), (Ptr *)&emmMsg) != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Failed to allocate memory to EMM msg\n");
      CM_FREE_NASEVNT(ueEvt);
      RETVALUE(RFAILED);
   }

   (*ueEvt)->m.emmEvnt = emmMsg;
   dtchAcc = &((*ueEvt)->m.emmEvnt->u.dtchAcc);

   /*Fill header information*/
   (*ueEvt)->secHT = CM_NAS_SEC_HDR_TYPE_INT_PRTD;

   /* Security header type is "Plain NAS message, not security protected" */
   emmMsg->secHdrType = CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG;
   emmMsg->msgId = CM_EMM_MSG_DETACH_ACC;
   emmMsg->protDisc = CM_EMM_PD;

   /* Fill mandatory IEs */
   /*detach type IE*/
   dtchAcc->type = CM_EMM_MSG_DETACH_ACC;

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueSendUeTrigDetachAcc
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueSendUeTrigDetachAcc
(
 UeCb *ueCb
)
{
   S16 ret = ROK;
   U8 isPlainMsg = TRUE;
   UeAppCb *ueAppCb = NULLP;
   CmNasEvnt *detachAcc = NULLP;
   NbuInitialUeMsg *nbuInitialUeMsg = NULLP;
   NbuUlNasMsg *pUlNbMsg = NULLP;
   NhuDedicatedInfoNAS nasEncPdu = {0};
   UeAppMsg srcMsg;
   UeAppMsg dstMsg;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   ret = ueAppUtlBldUeTrigDetachAcc(&detachAcc);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Building DetachReq Failed\n");
      RETVALUE(RFAILED);
   }
   cmMemset((U8 *)&nasEncPdu, 0, sizeof(NhuDedicatedInfoNAS));

   ret = ueAppEdmEncode(detachAcc, &nasEncPdu);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Encoding failed");
      CM_FREE_NASEVNT(&detachAcc);
      RETVALUE(RFAILED);
   }

   /** Integrity Protected **/
   if(CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG != detachAcc->secHT)
   {
      isPlainMsg = FALSE;
      srcMsg.val = nasEncPdu.val;
      srcMsg.len = nasEncPdu.len;
#if 0
      printf("\n**************ueCb Security Context Details***************\n");
      printf("dlSeqNmb = %d\n",ueCb->secCtxt.dlSeqNmb.seqNmb);
      printf("ulSeqNmb = %d\n",ueCb->secCtxt.ulSeqNmb.seqNmb);
      printf("lstUsdCnt = %d\n",ueCb->secCtxt.lstUsdCnt);

      printf("\nintKey:");
      for (count = 0; count < 16; count ++)
      printf("%x " ,ueCb->secCtxt.intKey[count]);

      printf("\nencKey:");
      for (count = 0; count < 16; count ++)
      printf("%x " ,ueCb->secCtxt.encKey[count]);

      printf("\nNas PDU:\n");
      printf("\nNas PDU len:%d\n", nasEncPdu.len);
      for (count = 0; count < nasEncPdu.len; count ++)
      printf("%x ", *(srcMsg.val + count));
#endif
      ret = ueAppCmpUplnkSec(&ueCb->secCtxt, detachAcc->secHT, &srcMsg,
            &dstMsg);
      if(ROK != ret)
      {
         UE_LOG_ERROR(ueAppCb, "Uplink Security Failed");
         detachAcc->pdu = NULLP;
         CM_FREE_NASEVNT(&detachAcc);
         EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
         RETVALUE(ret);
      }
      EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
      nasEncPdu.val = dstMsg.val;
      nasEncPdu.len = dstMsg.len;
   }
   CM_FREE_NASEVNT(&detachAcc);

   if(ueCb->ecmCb.state == UE_ECM_IDLE)
   {
      nbuInitialUeMsg = (NbuInitialUeMsg *)ueAlloc(sizeof(NbuInitialUeMsg));
      nbuInitialUeMsg->ueId = ueCb->ueId;
      nbuInitialUeMsg->rrcCause = 3;

      nbuInitialUeMsg->stmsi.pres  = TRUE;
      nbuInitialUeMsg->stmsi.mmec  = ueCb->ueCtxt.ueGuti.mmeCode;
      nbuInitialUeMsg->stmsi.mTMSI = ueCb->ueCtxt.ueGuti.mTMSI;

      nbuInitialUeMsg->nasPdu.pres = TRUE;
      nbuInitialUeMsg->nasPdu.len = nasEncPdu.len;
      nbuInitialUeMsg->nasPdu.val = (U8 *)ueAlloc(nbuInitialUeMsg->nasPdu.len);
      cmMemcpy((U8 *)nbuInitialUeMsg->nasPdu.val, nasEncPdu.val,
            nbuInitialUeMsg->nasPdu.len);

      ret = ueSendInitialUeMsg(nbuInitialUeMsg, &ueAppCb->nbPst);
      if (ret != ROK)
      {
         UE_LOG_ERROR(ueAppCb, "Sending Ue Triggered detach Accept to eNodeB failed\n");
         ret = RFAILED;
      }
   }
   else
   {
      pUlNbMsg = (NbuUlNasMsg *)ueAlloc(sizeof(NbuUlNasMsg));
      pUlNbMsg->ueId        = ueCb->ueId;
      pUlNbMsg->nasPdu.pres = TRUE;
      pUlNbMsg->nasPdu.len  = nasEncPdu.len;
      pUlNbMsg->nasPdu.val = (U8 *)ueAlloc(pUlNbMsg->nasPdu.len);
      cmMemcpy((U8 *)pUlNbMsg->nasPdu.val, (U8 *)nasEncPdu.val,
            pUlNbMsg->nasPdu.len);

      ret = ueSendUlNasMsgToNb(pUlNbMsg, &ueAppCb->nbPst);
      if (ret != ROK)
      {
         UE_LOG_ERROR(ueAppCb, "Could not Send the Detach Request message");
         RETVALUE(RFAILED);
      }
   }

   if(isPlainMsg)
   {
      EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
   }

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueProcUeTrigDetachAcc
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueProcUeTrigDetachAcc
(
 UetMessage *p_ueMsg,
 Pst *pst
)
{
   S16 ret = ROK;
   U32  ueId;
   UeAppCb *ueAppCb = NULLP;
   UeCb *ueCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Recieved Ue Triggered Detach Accept");
   ueId = p_ueMsg->msg.ueUetUeTrigDetachAcc.ueId;
   ret = ueDbmFetchUe(ueId, (PTR *)&ueCb);
   if( ret != ROK )
   {
      UE_LOG_ERROR(ueAppCb, "UeCb is empty for ueId = %d", ueId);
      UE_LOG_EXITFN(ueAppCb, ret);
   }

   ret = ueSendUeTrigDetachAcc(ueCb);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Sending Ue Triggered Detach Accept message failed");
      UE_LOG_EXITFN(ueAppCb, ret);
   }


   UE_LOG_EXITFN(ueAppCb, ret);
}
/*
 *
 *       Fun: ueProcUeFlush
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueProcUeFlush
(
 UetMessage *p_ueMsg,
 Pst *pst
)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Recieved Ue Flush Command");
   ret = ueDbmDelAllUe();
   if( ret != ROK )
   {
      UE_LOG_ERROR(ueAppCb, "Flushing all UE's Failed");
      UE_LOG_EXITFN(ueAppCb, ret);
   }

   UE_LOG_EXITFN(ueAppCb, ret);
}
/*
 *
 *       Fun: ueProcErabRelInd
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueProcErabRelInd
(
 UetMessage *p_ueMsg,
 Pst *pst
)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   UeCb *ueCb = NULLP;
   U32 ueId;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Recieved Ue Erab Release Indication");

   ueId = p_ueMsg->msg.ueErabRelInd.ueId;
   /* Fetching the UeCb */
   ret = ueDbmFetchUe(ueId, (PTR *)&ueCb);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "UeCb List NULL ueId = %d", ueId);
      RETVALUE(ret);
   }
   ret = ueAppFillLinkedBrIdAndSendErabRelInd(ueCb,&p_ueMsg->msg.ueErabRelInd);
   if( ret != ROK )
   {
      UE_LOG_ERROR(ueAppCb, "Erab Release Indication Failed");
      UE_LOG_EXITFN(ueAppCb, ret);
   }

   UE_LOG_EXITFN(ueAppCb, ret);
}

PRIVATE S16 ueAppFillLinkedBrIdAndSendErabRelInd
(
 UeCb *ueCb,
 UeErabRelInd *pErabRel
)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   U8 rbIdx = 0, flag=0;
   U8 noOfErabIds = pErabRel->numOfErabIds;

   U8 *tempErabIdLst = (U8 *)ueAlloc((sizeof(U8)) * UE_APP_MAX_DRBS);
   /*cmMemset((U8 *)&(tempErabIdLst), 0, ((sizeof(U8))*UE_APP_MAX_DRBS));
   */
   U8 brCount=0,ctxtCount=0,dCount=0,tempCount=0,mCount=0;
   NbuErabRelIndList *nbuErabRelInd = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);
   UE_LOG_DEBUG(ueAppCb, "Filling LinkedBrIds in the Erab List And "\
         "Sending Erab Rel Indication");

   if(ueCb == NULLP)
   {
      UE_LOG_ERROR(ueAppCb, "UeCb is Empty");
      RETVALUE(RFAILED);
   }

   nbuErabRelInd = (NbuErabRelIndList *)ueAlloc(sizeof(NbuErabRelIndList));
   nbuErabRelInd->ueId = pErabRel->ueId;
   nbuErabRelInd->numOfErabIds = pErabRel->numOfErabIds;
   nbuErabRelInd->erabIdLst = (U8 *)ueAlloc((sizeof(U8)) * \
         nbuErabRelInd->numOfErabIds);
   cmMemset((U8 *)(nbuErabRelInd->erabIdLst), 0, ((sizeof(U8)) * \
            nbuErabRelInd->numOfErabIds));
   cmMemcpy((U8 *)nbuErabRelInd->erabIdLst, pErabRel->erabIdLst,
         nbuErabRelInd->numOfErabIds);

   for(brCount=0;brCount<noOfErabIds;brCount++)
   {
      /*Find the bearer index*/
      if((ueAppUtlFndRbCb(&rbIdx, ueCb,
                  nbuErabRelInd->erabIdLst[brCount]) == ROK) && (ueCb->\
                  ueRabCb[rbIdx].bearerType == DEFAULT_BEARER))
      {
         for(ctxtCount = 0; ctxtCount < UE_APP_MAX_DRBS; ctxtCount++)
         {
            if(nbuErabRelInd->erabIdLst[brCount] == ueCb->ueRabCb[ctxtCount].\
                  lnkEpsBearId)
            {
               tempErabIdLst[tempCount] = ueCb->ueRabCb[ctxtCount].epsBearerId;
               tempCount++;

               cmMemset((U8 *)&(ueCb->ueRabCb[ctxtCount]), 0,
                     sizeof(ueCb->ueRabCb[ctxtCount]));
               ueCb->drbs[ctxtCount] = UE_APP_DRB_AVAILABLE;
            }
         }
      }
      else if (ueCb->ueRabCb[rbIdx].bearerType == DEDICATED_BEARER)
      {
         cmMemset((U8 *)&(ueCb->ueRabCb[rbIdx]), 0,
               sizeof(ueCb->ueRabCb[rbIdx]));
         ueCb->drbs[rbIdx + 1] = UE_APP_DRB_AVAILABLE;
      }
   }

   /*check duplicates and merge the templist and ErabList*/
   for(mCount=0; mCount<tempCount;mCount++)
   {
      for(dCount=0;dCount<noOfErabIds;dCount++)
      {
         if (tempErabIdLst[mCount] == nbuErabRelInd->erabIdLst[dCount])
         {
            flag = 1;
         }
      }
      if (flag == 0)
      {
         nbuErabRelInd->erabIdLst[brCount]=tempErabIdLst[mCount];
         nbuErabRelInd->numOfErabIds++;
         brCount++;
      }
   }
   ret = ueSendErabRelInd(nbuErabRelInd, &ueAppCb->nbPst);

   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Filling Erab List And Sending Erab Rel "\
            "Indication failed");
      RETVALUE(ret);
   }
   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
*
*       Fun:   ueAppUtlBldServiceReq
*
*       Desc:  This is build a Service Request that is to be sent to
*              the core network.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  ue_app.c
*
*/
PRIVATE S16 ueAppUtlBldServiceReq(UeCb *ueCb, CmNasEvnt **ueEvt)
{
   UeAppCb *ueAppCb = NULLP;
   CmEmmServiceReq  *serviceReq;
   CmEmmMsg* emmMsg;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Sending UE Service Request message");

   UE_LOG_DEBUG(ueAppCb, "Building a Service Request");

   /* Allocate memory for pdu */
   CM_ALLOC_NASEVNT (ueEvt, CM_EMM_PD);

   if(*ueEvt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   if (cmGetMem(&((*ueEvt)->memCp), sizeof(CmEmmMsg), (Ptr *)&emmMsg) != ROK)
   {
      CM_FREE_NASEVNT(ueEvt);
      RETVALUE(RFAILED);
   }

   (*ueEvt)->m.emmEvnt = emmMsg;
   serviceReq = &((*ueEvt)->m.emmEvnt->u.srvReq);

   /*Fill header information*/
   (*ueEvt)->secHT = CM_NAS_SEC_HDR_TYPE_SER_REQ;

   /* Security header type is "Plain NAS message, not security protected */
   emmMsg->protDisc = CM_EMM_PD;
   emmMsg->secHdrType = 12;
   emmMsg->msgId = CM_EMM_MSG_SERVICE_REQ;

   /* Fill mandatory IEs */
   /* KSI and Sequence Number IE*/
   serviceReq->ksiSeqNum.pres = TRUE;
   serviceReq->ksiSeqNum.seqNum = 0;
   serviceReq->ksiSeqNum.Ksi    = CM_EMM_NONAS_KEY_AVAILABLE;

   /*Short MAC IE*/
   serviceReq->shortMac.pres = TRUE;
   serviceReq->shortMac.val  = 0;

   RETVALUE(ROK);
} /* ueAppUtlBldServiceReq */

/*
 *
 *       Fun: ueSendServiceRequest
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueSendServiceRequest
(
 UeCb *ueCb,
 U32 mTmsi,
 U8 rrcCause,
 Bool noMac
)
{
   S16 ret = ROK;
   U8 isPlainMsg = TRUE;
   UeAppCb *ueAppCb = NULLP;
   NhuDedicatedInfoNAS nasEncPdu;
   NbuInitialUeMsg *nbuInitialUeMsg = NULLP;
   UeAppMsg srcMsg;
   UeAppMsg dstMsg;
   CmNasEvnt *serviceReqEvnt = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Sending UE Service Request message");

   ueCb->ecmCb.state = UE_ECM_CONNECTED;
   if (noMac) {
     ueCb->secCtxt.noMac = TRUE;
   }
   ret = ueAppUtlBldServiceReq(ueCb, &serviceReqEvnt);
   if(ROK != ret)
   {
      UE_LOG_ERROR(ueAppCb, "Could not send the Service request\n");
      RETVALUE(ret);
   }

   cmMemset((U8 *)&nasEncPdu, 0, sizeof(NhuDedicatedInfoNAS));
   nbuInitialUeMsg = (NbuInitialUeMsg *)ueAlloc(sizeof(NbuInitialUeMsg));

   /* Encoding Nas PDU */
   ret = ueAppEdmEncode(serviceReqEvnt, &nasEncPdu);
   if(ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Encoding failed");
      CM_FREE_NASEVNT(&serviceReqEvnt);
      RETVALUE(ret);
   }

   /** Integrity Protected **/
   if(CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG != serviceReqEvnt->secHT)
   {
      isPlainMsg = FALSE;
      srcMsg.val = nasEncPdu.val;
      srcMsg.len = nasEncPdu.len;
      ret = ueAppCmpUplnkSec(&ueCb->secCtxt, serviceReqEvnt->secHT, &srcMsg,
            &dstMsg);
      if(ROK != ret)
      {
         UE_LOG_ERROR(ueAppCb, "Uplink Security Failed");
         serviceReqEvnt->pdu = NULLP;
         CM_FREE_NASEVNT(&serviceReqEvnt);
         EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
         RETVALUE(ret);
      }
      EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
      nasEncPdu.val = dstMsg.val;
      nasEncPdu.len = dstMsg.len;
   }
   /** END **/
   CM_FREE_NASEVNT(&serviceReqEvnt);

   /* NB message filling */
   nbuInitialUeMsg->ueId        = ueCb->ueId;
   nbuInitialUeMsg->rrcCause    = rrcCause;

   nbuInitialUeMsg->stmsi.pres  = TRUE;
   nbuInitialUeMsg->stmsi.mmec  = ueCb->ueCtxt.ueGuti.mmeCode;
   nbuInitialUeMsg->stmsi.mTMSI = mTmsi;

   nbuInitialUeMsg->nasPdu.pres = TRUE;
   nbuInitialUeMsg->nasPdu.len  = nasEncPdu.len;
   nbuInitialUeMsg->nasPdu.val = (U8 *)ueAlloc(nbuInitialUeMsg->nasPdu.len);
   cmMemcpy((U8 *)nbuInitialUeMsg->nasPdu.val, (U8 *)nasEncPdu.val,
         nbuInitialUeMsg->nasPdu.len);

   if(isPlainMsg)
   {
      EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
   }

   ret = ueSendInitialUeMsg(nbuInitialUeMsg, &ueAppCb->nbPst);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Could not Send the Service request");
      RETVALUE(RFAILED);
   }

   UE_LOG_EXITFN(ueAppCb, ROK);
}

/*
 *
 *       Fun: ueProcUePdnConReq
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueProcUePdnConReq
(
 UetMessage *p_ueMsg,
 Pst *pst
)
{
   S16 ret = ROK;
   U32  ueId = 0;
   U8 isPlainMsg = TRUE;
   UeAppMsg srcMsg;
   UeAppMsg dstMsg;
   UeAppCb *ueAppCb = NULLP;
   UeCb *ueCb = NULLP;
   CmNasEvnt           *pdnConReqEvnt = NULLP;
   NhuDedicatedInfoNAS nasEncPdu;
   NbuUlNasMsg *nbUePdnConReq = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Recieved Ue Service Request");
   ueId = p_ueMsg->msg.ueUetPdnConReq.ueId;
   ret = ueDbmFetchUe(ueId, (PTR *)&ueCb);
   if( ret != ROK )
   {
      UE_LOG_ERROR(ueAppCb, "UeCb List NULL ueId = %d", ueId);
   }
   ret = ueAppUtlBldStandAlonePdnConReq(&pdnConReqEvnt,
         &p_ueMsg->msg.ueUetPdnConReq);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Building pdn connection req message failed");
      RETVALUE(ret);
   }

   if ((ret = ueAppEsmHdlOutUeEvnt(pdnConReqEvnt, ueCb))!= ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Handling PDN connection Request failed \n");
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&nasEncPdu, 0, sizeof(NhuDedicatedInfoNAS));

   /* Encode the PDU */
   ret = ueAppEdmEncode(pdnConReqEvnt, &nasEncPdu);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Pdn Con Req Encode Failed");
      CM_FREE_NASEVNT(&pdnConReqEvnt);
      RETVALUE(ret);
   }
   /** Integrity Protected **/
   if (CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG != pdnConReqEvnt->secHT)
   {
      isPlainMsg = FALSE;
      srcMsg.val = nasEncPdu.val;
      srcMsg.len = nasEncPdu.len;
      ret = ueAppCmpUplnkSec(&ueCb->secCtxt, pdnConReqEvnt->secHT, &srcMsg,
                             &dstMsg);
      if (ROK != ret)
      {
         UE_LOG_ERROR(ueAppCb, "Uplink Security Failed");
         EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
         pdnConReqEvnt->pdu = NULLP;
         CM_FREE_NASEVNT(&pdnConReqEvnt);
         RETVALUE(ret);
      }
      EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
      nasEncPdu.val = dstMsg.val;
      nasEncPdu.len = dstMsg.len;
   }
   CM_FREE_NASEVNT(&pdnConReqEvnt);

   nbUePdnConReq = (NbuUlNasMsg *)ueAlloc(sizeof(NbuUlNasMsg));
   nbUePdnConReq->ueId = ueId;
   nbUePdnConReq->nasPdu.pres = TRUE;
   nbUePdnConReq->nasPdu.len = nasEncPdu.len;
   nbUePdnConReq->nasPdu.val = (U8 *)ueAlloc(nbUePdnConReq->nasPdu.len);
   cmMemcpy((U8 *)nbUePdnConReq->nasPdu.val, nasEncPdu.val,
         nbUePdnConReq->nasPdu.len);

   if (isPlainMsg)
   {
   EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
   }

   ret = ueSendUlNasMsgToNb(nbUePdnConReq, &ueAppCb->nbPst);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Sending PDN Connection Req to enbAPP failed");
      ret = RFAILED;
   }

   UE_LOG_EXITFN(ueAppCb, ret);
} /* End of ueProcUePdnConReq */

PRIVATE S16 ueAppBuildAndSendActDefltBerContextAccept(UeCb *ueCb, U8 bearerId)
{
   S16 ret = ROK;
   U8 isPlainMsg = TRUE;
   UeAppMsg srcMsg;
   UeAppMsg dstMsg;
   UeAppCb *ueAppCb = NULLP;
   CmNasEvnt           *BearerAccEvnt = NULLP;
   NhuDedicatedInfoNAS nasEncPdu;
   NbuUlNasMsg *nbUeBearerAccReq = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   ret = ueAppUtlBldActDefltBerContextAccept(ueCb,&BearerAccEvnt,bearerId);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Building Activate Deafult Bearer Acc failed");
      RETVALUE(ret);
   }

   BearerAccEvnt->secHT = CM_NAS_SEC_HDR_TYPE_INT_PRTD_ENC;
   if ((ret = ueAppEsmHdlOutUeEvnt(BearerAccEvnt,ueCb))!= ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Handling Activate Deafult Bearer Acc failed \n");
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&nasEncPdu, 0, sizeof(NhuDedicatedInfoNAS));

   /* Encode the PDU */
   ret = ueAppEdmEncode(BearerAccEvnt, &nasEncPdu);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Activate Deafult Bearer Acc Failed");
      CM_FREE_NASEVNT(&BearerAccEvnt);
      RETVALUE(ret);
   }
   /** Integrity Protected **/
   if (CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG != BearerAccEvnt->secHT)
   {
      isPlainMsg = FALSE;
      srcMsg.val = nasEncPdu.val;
      srcMsg.len = nasEncPdu.len;
      ret = ueAppCmpUplnkSec(&ueCb->secCtxt, BearerAccEvnt->secHT, &srcMsg,
                             &dstMsg);
      if (ROK != ret)
      {
         UE_LOG_ERROR(ueAppCb, "Uplink Security Failed");
         EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
         BearerAccEvnt->pdu = NULLP;
         CM_FREE_NASEVNT(&BearerAccEvnt);
         RETVALUE(ret);
      }
      EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
      nasEncPdu.val = dstMsg.val;
      nasEncPdu.len = dstMsg.len;
   }
   CM_FREE_NASEVNT(&BearerAccEvnt);

   nbUeBearerAccReq = (NbuUlNasMsg *)ueAlloc(sizeof(NbuUlNasMsg));
   nbUeBearerAccReq->ueId = ueCb->ueId;
   nbUeBearerAccReq->nasPdu.pres = TRUE;
   nbUeBearerAccReq->nasPdu.len = nasEncPdu.len;
   nbUeBearerAccReq->nasPdu.val = (U8 *)ueAlloc(nbUeBearerAccReq->nasPdu.len);
   cmMemcpy((U8 *)nbUeBearerAccReq->nasPdu.val, nasEncPdu.val,
         nbUeBearerAccReq->nasPdu.len);

   if (isPlainMsg)
   {
   EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
   }

   ret = ueSendUlNasMsgToNb(nbUeBearerAccReq, &ueAppCb->nbPst);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Sending Activate Default Berarer accept to "\
            "Enodeb Failed");
      ret = RFAILED;
   }
   UE_LOG_EXITFN(ueAppCb, ret);
}

PRIVATE S16 ueAppBuildAndSendDeActvBerContextAccept(UeCb *ueCb, U8 bearerId)
{
   S16 ret = ROK;
   U8 isPlainMsg = TRUE;
   UeAppMsg srcMsg;
   UeAppMsg dstMsg;
   UeAppCb *ueAppCb = NULLP;
   CmNasEvnt           *deActvBearerAccEvnt = NULLP;
   NhuDedicatedInfoNAS nasEncPdu;
   NbuUlNasMsg *nbUeDeActvBearerAccReq = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   ret = ueAppUtlBldDeActvBerContextAccept(ueCb,&deActvBearerAccEvnt,bearerId);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Building De Activate Bearer Acc failed");
      RETVALUE(ret);
   }

   deActvBearerAccEvnt->secHT = CM_NAS_SEC_HDR_TYPE_INT_PRTD_ENC;

   if ((ret = ueAppEsmHdlOutUeEvnt(deActvBearerAccEvnt,ueCb))!= ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Handling De Activate Bearer Acc failed \n");
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&nasEncPdu, 0, sizeof(NhuDedicatedInfoNAS));

   /* Encode the PDU */
   ret = ueAppEdmEncode(deActvBearerAccEvnt, &nasEncPdu);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "DeActivate Bearer Acc Failed");
      CM_FREE_NASEVNT(&deActvBearerAccEvnt);
      RETVALUE(ret);
   }
   /** Integrity Protected **/
   if (CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG != deActvBearerAccEvnt->secHT)
   {
      isPlainMsg = FALSE;
      srcMsg.val = nasEncPdu.val;
      srcMsg.len = nasEncPdu.len;
      ret = ueAppCmpUplnkSec(&ueCb->secCtxt, deActvBearerAccEvnt->secHT, &srcMsg,
                             &dstMsg);
      if (ROK != ret)
      {
         UE_LOG_ERROR(ueAppCb, "Uplink Security Failed");
         EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
         deActvBearerAccEvnt->pdu = NULLP;
         CM_FREE_NASEVNT(&deActvBearerAccEvnt);
         RETVALUE(ret);
      }
      EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
      nasEncPdu.val = dstMsg.val;
      nasEncPdu.len = dstMsg.len;
   }
   CM_FREE_NASEVNT(&deActvBearerAccEvnt);

   nbUeDeActvBearerAccReq = (NbuUlNasMsg *)ueAlloc(sizeof(NbuUlNasMsg));
   nbUeDeActvBearerAccReq->ueId = ueCb->ueId;
   nbUeDeActvBearerAccReq->nasPdu.pres = TRUE;
   nbUeDeActvBearerAccReq->nasPdu.len = nasEncPdu.len;
   nbUeDeActvBearerAccReq->nasPdu.val = (U8 *)ueAlloc(nbUeDeActvBearerAccReq->nasPdu.len);
   cmMemcpy((U8 *)nbUeDeActvBearerAccReq->nasPdu.val, nasEncPdu.val,
         nbUeDeActvBearerAccReq->nasPdu.len);

   if (isPlainMsg)
   {
   EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
   }

   ret = ueSendUlNasMsgToNb(nbUeDeActvBearerAccReq, &ueAppCb->nbPst);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Sending DeActivate Bearer Accept to "\
            "Enodeb Failed");
      ret = RFAILED;
   }

   UE_LOG_EXITFN(ueAppCb, ret);
}

PRIVATE S16 ueAppBuildAndSendActDedBerContextAccept(UeCb *ueCb, U8 bearerId)
{
   S16 ret = ROK;
   U8 isPlainMsg = TRUE;
   UeAppMsg srcMsg;
   UeAppMsg dstMsg;
   UeAppCb *ueAppCb = NULLP;
   CmNasEvnt           *BearerAccEvnt = NULLP;
   NhuDedicatedInfoNAS nasEncPdu;
   NbuUlNasMsg *nbUeBearerAccReq = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);


   ret = ueAppUtlBldActDedBerContextAccept(ueCb,&BearerAccEvnt,bearerId);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Building Activate Dedicated Bearer Acc failed");
      RETVALUE(ret);
   }

   BearerAccEvnt->secHT = CM_NAS_SEC_HDR_TYPE_INT_PRTD_ENC;
   if ((ret = ueAppEsmHdlOutUeEvnt(BearerAccEvnt,ueCb))!= ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Handling Activate Dedicated Bearer Acc failed \n");
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&nasEncPdu, 0, sizeof(NhuDedicatedInfoNAS));

   /* Encode the PDU */
   ret = ueAppEdmEncode(BearerAccEvnt, &nasEncPdu);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Activate Dedicated Bearer Acc Failed");
      CM_FREE_NASEVNT(&BearerAccEvnt);
      RETVALUE(ret);
   }
   /** Integrity Protected **/
   if (CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG != BearerAccEvnt->secHT)
   {
      isPlainMsg = FALSE;
      srcMsg.val = nasEncPdu.val;
      srcMsg.len = nasEncPdu.len;
      ret = ueAppCmpUplnkSec(&ueCb->secCtxt, BearerAccEvnt->secHT, &srcMsg,
                             &dstMsg);
      if (ROK != ret)
      {
         UE_LOG_ERROR(ueAppCb, "Uplink Security Failed");
         EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
         BearerAccEvnt->pdu = NULLP;
         CM_FREE_NASEVNT(&BearerAccEvnt);
         RETVALUE(ret);
      }
      EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
      nasEncPdu.val = dstMsg.val;
      nasEncPdu.len = dstMsg.len;
   }
   CM_FREE_NASEVNT(&BearerAccEvnt);

   nbUeBearerAccReq = (NbuUlNasMsg *)ueAlloc(sizeof(NbuUlNasMsg));
   nbUeBearerAccReq->ueId = ueCb->ueId;
   nbUeBearerAccReq->nasPdu.pres = TRUE;
   nbUeBearerAccReq->nasPdu.len = nasEncPdu.len;
   nbUeBearerAccReq->nasPdu.val = (U8 *)ueAlloc(nbUeBearerAccReq->nasPdu.len);
   cmMemcpy((U8 *)nbUeBearerAccReq->nasPdu.val, nasEncPdu.val,
         nbUeBearerAccReq->nasPdu.len);

   if (isPlainMsg)
   {
   EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
   }

   ret = ueSendUlNasMsgToNb(nbUeBearerAccReq, &ueAppCb->nbPst);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Sending Activate Dedicated Berarer Accept to "\
            "Enodeb Failed");
      ret = RFAILED;
   }

   UE_LOG_EXITFN(ueAppCb, ret);
}

PRIVATE S16 ueAppBuildAndSendActDedBerContextReject(UeCb *ueCb, U8 bearerId,U8 esmCause)
{
   S16 ret = ROK;
   U8 isPlainMsg = TRUE;
   UeAppMsg srcMsg;
   UeAppMsg dstMsg;
   UeAppCb *ueAppCb = NULLP;
   CmNasEvnt           *BearerRejEvnt = NULLP;
   NhuDedicatedInfoNAS nasEncPdu;
   NbuUlNasMsg *nbUeBearerAccReq = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);


   ret = ueAppUtlBldActDedBerContextReject(ueCb,&BearerRejEvnt,bearerId,esmCause);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Building Activate Dedicated Bearer Rej failed");
      RETVALUE(ret);
   }

   BearerRejEvnt->secHT = CM_NAS_SEC_HDR_TYPE_INT_PRTD_ENC;

   if ((ret = ueAppEsmHdlOutUeEvnt(BearerRejEvnt,ueCb))!= ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Handling Activate Dedicated Bearer Rej failed \n");
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&nasEncPdu, 0, sizeof(NhuDedicatedInfoNAS));

   /* Encode the PDU */
   ret = ueAppEdmEncode(BearerRejEvnt, &nasEncPdu);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Activate Dedicated Bearer Rej Encoding Failed");
      CM_FREE_NASEVNT(&BearerRejEvnt);
      RETVALUE(ret);
   }
   /** Integrity Protected **/
   if (CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG != BearerRejEvnt->secHT)
   {
      isPlainMsg = FALSE;
      srcMsg.val = nasEncPdu.val;
      srcMsg.len = nasEncPdu.len;
      ret = ueAppCmpUplnkSec(&ueCb->secCtxt, BearerRejEvnt->secHT, &srcMsg,
                             &dstMsg);
      if (ROK != ret)
      {
         UE_LOG_ERROR(ueAppCb, "Uplink Security Failed");
         EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
         BearerRejEvnt->pdu = NULLP;
         CM_FREE_NASEVNT(&BearerRejEvnt);
         RETVALUE(ret);
      }
      EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
      nasEncPdu.val = dstMsg.val;
      nasEncPdu.len = dstMsg.len;
   }
   CM_FREE_NASEVNT(&BearerRejEvnt);

   nbUeBearerAccReq = (NbuUlNasMsg *)ueAlloc(sizeof(NbuUlNasMsg));
   nbUeBearerAccReq->ueId = ueCb->ueId;
   nbUeBearerAccReq->nasPdu.pres = TRUE;
   nbUeBearerAccReq->nasPdu.len = nasEncPdu.len;
   nbUeBearerAccReq->nasPdu.val = (U8 *)ueAlloc(nbUeBearerAccReq->nasPdu.len);
   cmMemcpy((U8 *)nbUeBearerAccReq->nasPdu.val, nasEncPdu.val,
         nbUeBearerAccReq->nasPdu.len);

   if (isPlainMsg)
   {
   EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
   }

   ret = ueSendUlNasMsgToNb(nbUeBearerAccReq, &ueAppCb->nbPst);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Sending Activate Dedicated Berarer Reject to "\
            "Enodeb Failed");
      ret = RFAILED;
   }

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueProcUeServiceRequest
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueProcUeServiceRequest
(
 UetMessage *p_ueMsg,
 Pst *pst
)
{
   S16 ret = ROK;
   U32  ueId = 0;
   U32 mTmsi = 0;
   U8 rrcCause = 0;
   UeAppCb *ueAppCb = NULLP;
   UeCb *ueCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Recieved Ue Service Request");
   ueId = p_ueMsg->msg.ueUetServiceReq.ueId;
   rrcCause = p_ueMsg->msg.ueUetServiceReq.rrcCause;
   Bool noMac = p_ueMsg->msg.ueUetServiceReq.noMac;
   ret = ueDbmFetchUe(ueId, (PTR *)&ueCb);
   if( ret != ROK )
   {
      UE_LOG_ERROR(ueAppCb, "UeCb List NULL ueId = %d", ueId);
   }
   if(p_ueMsg->msg.ueUetServiceReq.ueMtmsi.pres == TRUE)
   {
      mTmsi = p_ueMsg->msg.ueUetServiceReq.ueMtmsi.mTmsi;
   }
   else
   {
      mTmsi = ueCb->ueCtxt.ueGuti.mTMSI;
   }
   ret = ueSendServiceRequest(ueCb, mTmsi, rrcCause, noMac);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Sending Service Request message failed");
   }

   UE_LOG_EXITFN(ueAppCb, ret);
} /* End of ueProcUeServiceRequest */
/*
 *
 *       Fun: ueSendUeRadCapInd
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PUBLIC S16 ueSendUeRadCapInd
(
 UeCb *ueCb
)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   NbuUlRrcMsg *pUlNbRrcMsg;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);
   pUlNbRrcMsg = (NbuUlRrcMsg *)ueAlloc(sizeof(NbuUlRrcMsg));
   pUlNbRrcMsg->ueId = ueCb->ueId;
   pUlNbRrcMsg->rrcPdu.val = (U8*) ueAlloc(ueCb->ueCtxt.ueRadCap.len);
   cmMemcpy((U8 *)pUlNbRrcMsg->rrcPdu.val, (U8 *)ueCb->ueCtxt.ueRadCap.rrcPDU,
         ueCb->ueCtxt.ueRadCap.len);
   pUlNbRrcMsg->rrcPdu.len = ueCb->ueCtxt.ueRadCap.len;
   UE_LOG_DEBUG(ueAppCb, "Sending UE Radio Capability message");
   /* vinay: to do - send message to enbApp */
   ret = ueSendUlRrcMsgToNb(pUlNbRrcMsg, &ueAppCb->nbPst);
   RETVALUE(ret);
}

/*
 *
 *       Fun: ueProcUeRadCapUpdateReq
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueProcUeRadCapUpdateReq
(
 UetMessage *p_ueMsg,
 Pst *pst
)
{
   S16 ret = ROK;
   U32  ueId = 0;
   UeAppCb *ueAppCb = NULLP;
   UeCb *ueCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Recieved Ue Radio capability update Request");
   ueId = p_ueMsg->msg.ueUetRadCapUpdReq.ueId;
   ret = ueDbmFetchUe(ueId, (PTR *)&ueCb);
   if( ret != ROK )
   {
      UE_LOG_ERROR(ueAppCb, "UeCb List NULL ueId = %d", ueId);
   }
   if(p_ueMsg->msg.ueUetRadCapUpdReq.upd_ueRadCap == TRUE)
   {
      if (ueCb->ueCtxt.ueRadCap.pres==TRUE)
      {
         ueFree(ueCb->ueCtxt.ueRadCap.rrcPDU,
               ueCb->ueCtxt.ueRadCap.len * sizeof(U8));
      }
      ueCb->ueCtxt.ueRadCap.rrcPDU = (U8 *)ueAlloc(p_ueMsg->msg.\
            ueUetRadCapUpdReq.len);
      cmMemcpy(ueCb->ueCtxt.ueRadCap.rrcPDU,p_ueMsg->msg.ueUetRadCapUpdReq.\
            radCapMsg , p_ueMsg->msg.ueUetRadCapUpdReq.len);
      ueCb->ueCtxt.ueRadCap.len = p_ueMsg->msg.ueUetRadCapUpdReq.len;
      ueCb->ueCtxt.ueRadCap.pres = TRUE;
      ueFree((U8*)p_ueMsg->msg.ueUetRadCapUpdReq.radCapMsg,
            p_ueMsg->msg.ueUetRadCapUpdReq.len * sizeof(U8));
   }

   if(p_ueMsg->msg.ueUetRadCapUpdReq.send_s1ap_msg == TRUE)
   {
      ret = ueSendUeRadCapInd(ueCb);
   }
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Sending UE Radio Capabilty Ind failed");
   }

   UE_LOG_EXITFN(ueAppCb, ret);
}
/*
 *
 *       Fun: ueAppSndEmmStatus
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppSndEmmStatus(UeCb *ueCb, U8 cause)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   UeAppMsg     srcMsg;
   UeAppMsg     dstMsg;
   CmNasEvnt   *emmStatusEvnt = NULLP;
   NhuDedicatedInfoNAS nasEncPdu;
   NbuUlNasMsg *pUlNbMsg = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Sending UE EMM Status message To EnodeB");
   ret = ueAppUtlBldEmmStatus(ueCb, &emmStatusEvnt, cause);
   if(ROK != ret)
   {
      UE_LOG_ERROR(ueAppCb, "Building EMM STATUS failed");
      ret = RFAILED;
      RETVALUE(ret);
   }

   cmMemset((U8 *)&nasEncPdu, 0, sizeof(NhuDedicatedInfoNAS));
   pUlNbMsg = (NbuUlNasMsg *)ueAlloc(sizeof(NbuUlNasMsg));

   ret = ueAppEdmEncode(emmStatusEvnt, &nasEncPdu);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Encoding failed");
      ret = RFAILED;
      RETVALUE(ret);
   }
   /** Integrity Protected **/
   if(CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG != emmStatusEvnt->secHT)
   {
      srcMsg.val = nasEncPdu.val;
      srcMsg.len = nasEncPdu.len;
      ret = ueAppCmpUplnkSec(&ueCb->secCtxt, emmStatusEvnt->secHT, &srcMsg,
            &dstMsg);
      if(ROK != ret)
      {
         UE_LOG_ERROR(ueAppCb, "Uplink Security Failed");
         emmStatusEvnt->pdu = NULLP;
         CM_FREE_NASEVNT(&emmStatusEvnt);
         EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
         RETVALUE(ret);
      }
      EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
      nasEncPdu.val = dstMsg.val;
      nasEncPdu.len = dstMsg.len;
   }
   CM_FREE_NASEVNT(&emmStatusEvnt);

   pUlNbMsg->ueId        = ueCb->ueId;
   pUlNbMsg->nasPdu.pres = TRUE;
   pUlNbMsg->nasPdu.len  = nasEncPdu.len;
   pUlNbMsg->nasPdu.val  = (U8 *)ueAlloc(pUlNbMsg->nasPdu.len);
   cmMemcpy((U8 *)pUlNbMsg->nasPdu.val, (U8 *)nasEncPdu.val,
         pUlNbMsg->nasPdu.len );

   ret = ueSendUlNasMsgToNb(pUlNbMsg,&ueAppCb->nbPst);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Could not Send the Emm Status message");
      RETVALUE(RFAILED);
   }
   UE_LOG_EXITFN(ueAppCb, ret);
}
/*
 *
 *       Fun: ueProcUeEmmStatus
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueProcUeEmmStatus(UetMessage *p_ueMsg, Pst *pst)
{
   S16 ret = ROK;
   U32  ueId;
   UeAppCb *ueAppCb = NULLP;
   UeCb *ueCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);
   UE_LOG_DEBUG(ueAppCb, "Processing UE EMM STATUS from TFWAPP");

   ueId = p_ueMsg->msg.ueUetEmmStatus.ueId;
   ret = ueDbmFetchUe(ueId,(PTR*)&ueCb);
   if( ret != ROK )
   {
      UE_LOG_ERROR(ueAppCb, "UeCb List NULL ueId = %d", ueId);
      RETVALUE(ret);
   }
   ret = ueAppSndEmmStatus(ueCb, p_ueMsg->msg.ueUetEmmStatus.cause);

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun:   ueUiProcessTfwMsg
 *
 *       Desc:  This function processes messages/events received from TFW.
 *
 *       Ret:   ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PUBLIC S16 ueUiProcessTfwMsg(UetMessage *p_ueMsg, Pst *pst)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);

   switch (p_ueMsg->msgType)
   {
      case UE_APP_CONFIG_REQ_TYPE:
      {
         UE_LOG_DEBUG(ueAppCb, "RECIEVED UE APP CONFIGURATION REQUEST MESSAGE "\
               "FROM TFWAPP");
         ret = ueProcUeAppConfigReq(p_ueMsg, pst);
         break;
      }
      case UE_CONFIG_REQ_TYPE:
      {
         UE_LOG_DEBUG(ueAppCb, "RECIEVED UE CONFIGURATION REQUEST MESSAGE "\
               "FROM TFWAPP");
         ret = ueProcUeConfigReq(p_ueMsg, pst);
         break;
      }
      case UE_ATTACH_REQ_TYPE:
      {
         UE_LOG_DEBUG(ueAppCb, "RECIEVED UE ATTACH REQUEST MESSAGE FROM "\
               "TFWAPP");
         ret = ueProcUeAttachReq(p_ueMsg, pst);
         break;
      }
      case UE_IDENTITY_RES_TYPE:
      {
         UE_LOG_DEBUG(ueAppCb, "RECIEVED UE IDENTITY RESPONSE MESSAGE FROM "\
               "TFWAPP");
         ret = ueProcUeIdentResp(p_ueMsg, pst);
         break;
      }
      case UE_AUTH_RES_TYPE:
      {
         UE_LOG_DEBUG(ueAppCb, "RECIEVED UE AUTHENTICATION RESPONSE "\
               "MESSAGE FROM TFWAPP");
         ret = ueProcUeAuthResp(p_ueMsg, pst);
         break;
      }
      case UE_SEC_MOD_CMP_TYPE:
      {
         UE_LOG_DEBUG(ueAppCb, "RECEIVED UE SECURITY MODE COMMAND COMPLETE "\
               "FROM TFWAPP");
         ret = ueProcUeSecModeCmdComplete(p_ueMsg, pst);
         break;
      }
      case UE_SEC_MOD_REJ_TYPE:
      {
         UE_LOG_DEBUG(ueAppCb,
                      "RECEIVED UE SECURITY MODE COMMAND REJECT FROM TFWAPP");
         ret = ueProcUeSecModeRejectCmd(p_ueMsg, pst);
         break;
      }
      case UE_ATTACH_COMPLETE_TYPE:
      {
         UE_LOG_DEBUG(ueAppCb, "RECEIVED UE ATTACH COMPLETE FROM TFWAPP");
         ret = ueProcUeAttachComplete(p_ueMsg, pst);
         break;
      }
      case UE_ATTACH_FAIL_TYPE:
      {
         UE_LOG_DEBUG(ueAppCb, "RECEIVED UE ATTACH FAIL FROM TFWAPP");
         ret = ueProcUeAttachFail(p_ueMsg, pst);
         break;
      }
      case UE_DETACH_REQUEST_TYPE:
      {
         UE_LOG_DEBUG(ueAppCb, "RECEIVED UE DETACH REQUEST FROM TFWAPP");
         ret = ueProcUeDetachRequest(p_ueMsg, pst);
         break;
      }
      case UE_TAU_REQUEST_TYPE:
      {
         UE_LOG_DEBUG(ueAppCb,
                      "RECEIVED UE TRACKING AREA UPDATE REQUEST FROM TFWAPP");
         ret = ueProcUeTauRequest(p_ueMsg, pst);
         break;
      }
      case UE_TAU_COMPLETE_TYPE:
      {
         UE_LOG_DEBUG(ueAppCb, "RECEIVED UE TRACKING AREA UPDATE COMPLETE "\
               "FROM TFWAPP");
         ret = ueProcUeTauComplete(p_ueMsg, pst);
         break;
      }
      case UE_SERVICE_REQUEST_TYPE:
      {
         UE_LOG_DEBUG(ueAppCb, "RECEIVED UE SERVICE REQUEST FROM TFWAPP");
         ret = ueProcUeServiceRequest(p_ueMsg, pst);
         break;
      }
      case UE_PDN_CON_REQ_TYPE:
      {
            UE_LOG_DEBUG(ueAppCb, "RECEIVED UE PDN CONNECTION REQ FROM TFWAPP");
            ret = ueProcUePdnConReq(p_ueMsg, pst);
            break;
      }
      case UE_RAD_CAP_UPD_TYPE:
      {
         UE_LOG_DEBUG(ueAppCb, "RECEIVED UE RADIO CAPABILITY UPDATE FROM TFW");
         ret = ueProcUeRadCapUpdateReq(p_ueMsg, pst);
         break;
      }
      case UE_TRIG_DETACH_ACCEPT_TYPE:
      {
         UE_LOG_DEBUG(ueAppCb, "RECEIVED UE RADIO CAPABILITY UPDATE FROM TFW");
         ret = ueProcUeTrigDetachAcc(p_ueMsg, pst);
         break;
      }
      case UE_FLUSH_TYPE:
      {
         UE_LOG_DEBUG(ueAppCb, "RECEIVED UE FLUSH COMMAND FROM TFW");
         ret = ueProcUeFlush(p_ueMsg, pst);
         break;
      }
      case UE_BEAR_RES_ALLOC_REQ:
      {
         UE_LOG_DEBUG(ueAppCb, "RECEIVED Bearer Resource Allocation requestion TFW");
         ret = ueProcUeBearResAllocReq(p_ueMsg, pst);
         break;
      }
      case UE_ERAB_REL_IND:
      {
         UE_LOG_DEBUG(ueAppCb, "RECEIVED UE Erab Release Indication FROM TFW");
         ret = ueProcErabRelInd(p_ueMsg, pst);
         break;
      }
      case UE_EPS_DED_BER_ACC:
      {
         UE_LOG_DEBUG(ueAppCb, "RECEIVED Actv Dedicated Bearer Acc from TFW");
         ret = ueProcUeActvDedBerAcc(p_ueMsg, pst);
         break;
      }
      case UE_EPS_DED_BER_REJ:
      {
         UE_LOG_DEBUG(ueAppCb, "RECEIVED Actv Dedicated Bearer Rej from TFW");
         ret = ueProcUeActvDedBerRej(p_ueMsg, pst);
         break;
      }
      case UE_EMM_STATUS_TYPE:
      {
         UE_LOG_DEBUG(ueAppCb, "RECEIVED EMM STATUS from TFW");
         ret = ueProcUeEmmStatus(p_ueMsg, pst);
         //ret = ueProcUeActvDedBerRej(p_ueMsg, pst);
         break;
      }
      case UE_EPS_DEFAULT_BER_REJ:
      {
         UE_LOG_DEBUG(ueAppCb, "UE ATTACH COMPLETE + ACTIVATE DEFAULT EPS BEARER CONTEXT REJECT from TFW");
         ret = ueProcUeAttachCompleteWithActvDfltBerCtxtRej(p_ueMsg, pst);

         break;
      }
      case UE_EPS_DEACTIVATE_BER_ACC:
      {
         UE_LOG_DEBUG(ueAppCb, "RECEIVED De Activate Bearer Acc from TFW");
         ret = ueProcUeDeActvBerAcc(p_ueMsg, pst);
         break;
      }
      case UE_ESM_INFORMATION_RSP_TYPE:
      {
         UE_LOG_DEBUG(ueAppCb, "UE_ESM_INFORMATION_RSP_TYPE");
         ret = ueProcUeEsmInformationRsp(p_ueMsg, pst);

         break;
      }
      case UE_PDN_DISCONNECT_REQ_TYPE:
      {
         UE_LOG_DEBUG(ueAppCb, "RECEIVED UE PDN DISCONNECT REQ FROM TFWAPP");
         ret = ueProcUePdnDisconnectReq(p_ueMsg, pst);
         break;
      }
      case UE_AUTH_FAILURE_TYPE: {
        UE_LOG_DEBUG(ueAppCb,
                     "RECIEVED UE AUTHENTICATION FAILURE "
                     "MESSAGE FROM TFWAPP");
        ret = ueProcUeAuthFailure(p_ueMsg, pst);
        break;
      }
      case UE_STANDALONE_DEFAULT_EPS_BER_REJ: {
        UE_LOG_DEBUG(ueAppCb,
                     "Received UE_STANDALONE_DEFAULT_EPS_BER_REJ from TFW");
        ret = ueProcUeStandAloneActvDfltBerCtxtRej(p_ueMsg, pst);

        break;
      }
      case UE_DROP_ACT_DEFAULT_EPS_BER_CTXT_REQ: {
        UE_LOG_DEBUG(ueAppCb,
                     "Received UE_DROP_ACT_DEFAULT_EPS_BER_CTXT_REQ from TFW");
        ret = ueProcDropActDefaultEpsBerCtxtReq(p_ueMsg, pst);
        break;
      }

      default: {
        UE_LOG_ERROR(ueAppCb, "Recieved Invalid message of type: %d",
                     p_ueMsg->msgType);
        ret = RFAILED;
        break;
      }
   }
   RETVALUE(ret);
}

/*
 *
 *       Fun:   ueBldIdentReqIndMsgToTfw
 *
 *       Desc:  Build Identity Request Indication to be sent to TFW.
 *
 *       Ret:   ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueBldIdentReqIndMsgToTfw
(
   UetMessage *tfwMsg,
   UeCb *ueCb,
   U8 idType
)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);

   UE_LOG_ENTERFN(ueAppCb);
   UE_LOG_DEBUG(ueAppCb, "Building Identity Request Indication to TFWAPP");

   tfwMsg->msgType = UE_IDENTITY_REQ_IND_TYPE;
   tfwMsg->msg.ueUetIdentReqInd.ueId = ueCb->ueId;
   tfwMsg->msg.ueUetIdentReqInd.idType = idType;

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueBldAuthReqIndMsgToTfw
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueBldAuthReqIndMsgToTfw(UetMessage *tfwMsg, UeCb *ueCb)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   UE_GET_CB(ueAppCb);

   UE_LOG_ENTERFN(ueAppCb);
   UE_LOG_DEBUG(ueAppCb, "Building Authentication Request Indication");
   tfwMsg->msgType = UE_AUTH_REQ_IND_TYPE;
   tfwMsg->msg.ueUetAuthReqInd.ueId = ueCb->ueId;

   cmMemcpy(tfwMsg->msg.ueUetAuthReqInd.rand, ueCb->ueCtxt.rnd, 16);
   cmMemcpy(tfwMsg->msg.ueUetAuthReqInd.autn, ueCb->secCtxt.autn, 16);
   cmMemcpy(tfwMsg->msg.ueUetAuthReqInd.sqn, ueCb->ueAuthKeys.sqnRcvd, 6);
   tfwMsg->msg.ueUetAuthReqInd.KNASVrfySts = TRUE; /* TODO */

   UE_LOG_EXITFN(ueAppCb, ret);
} /* End of ueBldAuthReqIndMsgToTfw */

/*
 *
 *       Fun: ueAppUtlBldAuthFailure
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppUtlBldAuthFailure(UeCb *ueCb, CmNasEvnt **ueEvt)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   CmEmmAuthFailure  *authFail;
   CmEmmMsg* emmMsg;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Building a  Authentication failure message to MME");

   if(ueEvt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /* Allocate memory for pdu */
   CM_ALLOC_NASEVNT (ueEvt, CM_EMM_PD);

   if(*ueEvt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   if (cmGetMem(&((*ueEvt)->memCp), sizeof(CmEmmMsg), (Ptr *)&emmMsg) != ROK)
   {
      CM_FREE_NASEVNT(ueEvt);
      RETVALUE(RFAILED);
   }
   (*ueEvt)->m.emmEvnt = emmMsg;
   authFail = &((*ueEvt)->m.emmEvnt->u.authFlr);

   /* Fill header information*/

   /* Security header type is "Plain NAS message, not security protected" */
   emmMsg->secHdrType = CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG;
   emmMsg->protDisc = CM_EMM_PD;
   emmMsg->msgId = CM_EMM_MSG_AUTH_FAIL;

   /* Fill mandatory IEs */
   /* Auth response parameter*/
   cmMemcpy((U8 *)authFail, (U8*)&ueCb->authFlr, sizeof(CmEmmAuthFailure));

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueAppSndAuthFailure
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppSndAuthFailure(UeCb *ueCb)
{
   CmNasEvnt *authFlrEvnt = NULLP;
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   NbuUlNasMsg *pNbUlNasMsg = NULLP;
   NhuDedicatedInfoNAS nasEncPdu;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Sending Authentication failure");

   ret = ueAppUtlBldAuthFailure(ueCb, &authFlrEvnt);
   if(ROK != ret)
   {
      UE_LOG_ERROR(ueAppCb, "Could not send the Authentication failure");
      RETVALUE(ret);
   }
   pNbUlNasMsg = (NbuUlNasMsg *)ueAlloc(sizeof(NbuUlNasMsg));
   cmMemset((U8 *)&nasEncPdu, 0, sizeof(NhuDedicatedInfoNAS));
   ret = ueAppEdmEncode(authFlrEvnt, &nasEncPdu);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Encoding failed");
      CM_FREE_NASEVNT(&authFlrEvnt);
      RETVALUE(RFAILED);
   }

   CM_FREE_NASEVNT(&authFlrEvnt);
   pNbUlNasMsg->ueId        = ueCb->ueId;
   pNbUlNasMsg->nasPdu.pres = TRUE;
   pNbUlNasMsg->nasPdu.len  = nasEncPdu.len;
   pNbUlNasMsg->nasPdu.val = (U8 *)ueAlloc(pNbUlNasMsg->nasPdu.len);

   cmMemcpy((U8 *)pNbUlNasMsg->nasPdu.val, (U8 *)nasEncPdu.val,
         pNbUlNasMsg->nasPdu.len);
   EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);

   ret = ueSendUlNasMsgToNb(pNbUlNasMsg, &ueAppCb->nbPst);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Could not Send the Authentication Failure "\
            "message to NB");
      RETVALUE(RFAILED);
   }
   UE_LOG_EXITFN(ueAppCb, ret);
} /* End of ueAppSndAuthFailure */

/*
 *       Fun: ueBldSecModeCmdIndToTfw
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueBldSecModeCmdIndToTfw(UetMessage *tfwMsg, UeCb *ueCb)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);
   UE_LOG_DEBUG(ueAppCb, "Building SEC MODE CMD Indication to TFWAPP");
   tfwMsg->msgType = UE_SEC_MOD_CMD_IND_TYPE;
   tfwMsg->msg.ueUetSecModeCmdInd.ueId          = ueCb->ueId;
   tfwMsg->msg.ueUetSecModeCmdInd.NasCyphCfg    = ueCb->secCtxt.encAlg;
   tfwMsg->msg.ueUetSecModeCmdInd.NasIntProtCfg = ueCb->secCtxt.intAlg;

   cmMemcpy((U8 *)&tfwMsg->msg.ueUetSecModeCmdInd.Kasme,
         (U8 *)&ueCb->secCtxt.kasme, UE_APP_SZ_KASME_KEY);
   cmMemcpy((U8 *)&tfwMsg->msg.ueUetSecModeCmdInd.KNasEnc,
         (U8 *)&ueCb->secCtxt.encKey, UE_APP_SZ_NAS_ENC_KEY);
   cmMemcpy((U8 *)&tfwMsg->msg.ueUetSecModeCmdInd.KNasInt,
         (U8 *)&ueCb->secCtxt.intKey, UE_APP_SZ_NAS_INT_KEY);

   tfwMsg->msg.ueUetSecModeCmdInd.KNasVrfySts    = TRUE;

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *       Fun:   ueBldTauAcceptToTfw
 *
 *       Desc:  This function builds TAU Accept Indication which is to be sent
 *              to TFW=>Test Stub.
 *
 *       Ret:   ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueBldTauAcceptToTfw
(
   UetMessage *tfwMsg,
   CmEmmTAUAccept *tauAccept,
   UeCb *ueCb
)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Building TAU Accept Indication for ueId(%d)",
         ueCb->ueId);

   tfwMsg->msgType = UE_TAU_ACCEPT_TYPE;
   tfwMsg->msg.ueUetTauAccept.ueId = ueCb->ueId;
   tfwMsg->msg.ueUetTauAccept.gutiChanged = ueCb->gutiChanged;

   if (tauAccept->epsUpdateRes.pres)
   {
      tfwMsg->msg.ueUetTauAccept.epsUpdateRes = tauAccept->epsUpdateRes.res;
   }

   cmMemset((U8 *)&tfwMsg->msg.ueUetTauAccept.guti, 0, sizeof(Guti));
   if (tauAccept->guti.pres)
   {
      cmMemcpy((U8 *)&tfwMsg->msg.ueUetTauAccept.guti.mcc,
               (U8 *)&ueCb->ueCtxt.ueGuti.mcc, 3);
      cmMemcpy((U8 *)&tfwMsg->msg.ueUetTauAccept.guti.mnc,
               (U8 *)&ueCb->ueCtxt.ueGuti.mnc, 3);
      tfwMsg->msg.ueUetTauAccept.guti.mmeGrpId = ueCb->ueCtxt.ueGuti.mmeGrpId;
      tfwMsg->msg.ueUetTauAccept.guti.mmeCode = ueCb->ueCtxt.ueGuti.mmeCode;
      tfwMsg->msg.ueUetTauAccept.guti.mTMSI = ueCb->ueCtxt.ueGuti.mTMSI;
   }

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *       Fun: ueBldAttachAcceptToTfw
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueBldAttachAcceptToTfw
(
 UetMessage *tfwMsg,
 UeCb *ueCb
)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   U8 count;
   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Building Attach Accept Indication to TFWAPP");
   tfwMsg->msgType = UE_ATTACH_ACCEPT_IND_TYPE;
   tfwMsg->msg.ueUetAttachAcceptInd.ueId = ueCb->ueId;
   tfwMsg->msg.ueUetAttachAcceptInd.epsAtchRes = ueCb->epsAtchRes;
   tfwMsg->msg.ueUetAttachAcceptInd.t3412 = ueCb->t3412;
   cmMemcpy(tfwMsg->msg.ueUetAttachAcceptInd.msId, ueCb->ueCtxt.msId,
         CM_EMM_MAX_MOBILE_ID_DIGS);

   /* GUTI */
   cmMemcpy((U8 *)&tfwMsg->msg.ueUetAttachAcceptInd.guti.mcc,
         (U8 *)&ueCb->ueCtxt.ueGuti.mcc, 3);
   cmMemcpy((U8 *)&tfwMsg->msg.ueUetAttachAcceptInd.guti.mnc,
         (U8 *)&ueCb->ueCtxt.ueGuti.mnc,3);
   tfwMsg->msg.ueUetAttachAcceptInd.guti.mmeGrpId = ueCb->ueCtxt.ueGuti.\
                                                    mmeGrpId;
   tfwMsg->msg.ueUetAttachAcceptInd.guti.mmeCode = ueCb->ueCtxt.ueGuti.mmeCode;
   tfwMsg->msg.ueUetAttachAcceptInd.guti.mTMSI = ueCb->ueCtxt.ueGuti.mTMSI;

   tfwMsg->msg.ueUetAttachAcceptInd.cause = ueCb->emmCause;
   tfwMsg->msg.ueUetAttachAcceptInd.t3402 = ueCb->t3402;
   tfwMsg->msg.ueUetAttachAcceptInd.t3423 = ueCb->t3423;
   cmMemcpy((U8 *)&tfwMsg->msg.ueUetAttachAcceptInd.plmnList,
         (U8 *)&ueCb->plmnLst, sizeof(CmEmmPlmnId));

   /* Populating ESM INFO  */
   if(ueCb->ueRabCb[0].qos.pres)
   {
      tfwMsg->msg.ueUetAttachAcceptInd.esmInfo.qos.qci = ueCb->ueRabCb[0].\
                                                         epsQos.qci;
      tfwMsg->msg.ueUetAttachAcceptInd.esmInfo.qos.\
         maxBitRateUL = ueCb->ueRabCb[0].qos.maxBitRateUL;
      tfwMsg->msg.ueUetAttachAcceptInd.esmInfo.qos.\
         maxBitRateDL = ueCb->ueRabCb[0].qos.maxBitRateDL;
      tfwMsg->msg.ueUetAttachAcceptInd.esmInfo.qos.\
         guaraBitRateUL = ueCb->ueRabCb[0].qos.guaraBitRateUL;
      tfwMsg->msg.ueUetAttachAcceptInd.esmInfo.qos.\
         guaraBitRateDL = ueCb->ueRabCb[0].qos.guaraBitRateDL;
   }
   if(ueCb->ueRabCb[0].apn.pres)
   {
      tfwMsg->msg.ueUetAttachAcceptInd.esmInfo.apn.len = ueCb->ueRabCb[0].\
                                                         apn.len;
      cmMemcpy(tfwMsg->msg.ueUetAttachAcceptInd.esmInfo.apn.apn,
            ueCb->ueRabCb[0].apn.apn, ueCb->ueRabCb[0].apn.len);
   }
   if(ueCb->ueRabCb[0].pAddr.pres)
   {
      tfwMsg->msg.ueUetAttachAcceptInd.esmInfo.pAddr.\
         pdnType = ueCb->ueRabCb[0].pAddr.pdnType;
      cmMemcpy(tfwMsg->msg.ueUetAttachAcceptInd.esmInfo.pAddr.addrInfo,
            ueCb->ueRabCb[0].pAddr.addrInfo, CM_ESM_MAX_LEN_PDN_ADDRESS);
   }
   if(ueCb->ueRabCb[0].apnAmbr.pres)
   {
      tfwMsg->msg.ueUetAttachAcceptInd.esmInfo.apnAmbr.\
         len = ueCb->ueRabCb[0].apnAmbr.len;
      tfwMsg->msg.ueUetAttachAcceptInd.esmInfo.apnAmbr.\
         dl  = ueCb->ueRabCb[0].apnAmbr.dl;
      tfwMsg->msg.ueUetAttachAcceptInd.esmInfo.\
         apnAmbr.ul = ueCb->ueRabCb[0].apnAmbr.ul;
   }
   if(ueCb->ueRabCb[0].protCfgOpt.pres)
   {
     tfwMsg->msg.ueUetAttachAcceptInd.esmInfo.protCfgOpt.pres = TRUE;
     tfwMsg->msg.ueUetAttachAcceptInd.esmInfo.protCfgOpt.len = \
	 	ueCb->ueRabCb[0].protCfgOpt.len;
     tfwMsg->msg.ueUetAttachAcceptInd.esmInfo.protCfgOpt.numProtId = \
	 	ueCb->ueRabCb[0].protCfgOpt.numProtId;
     tfwMsg->msg.ueUetAttachAcceptInd.esmInfo.protCfgOpt.numContId = \
	 	ueCb->ueRabCb[0].protCfgOpt.numContId;

     for (count=0;count<ueCb->ueRabCb[0].protCfgOpt.numProtId;count++)
 	{
 	  tfwMsg->msg.ueUetAttachAcceptInd.esmInfo.protCfgOpt.p[count].pid =\
	  	ueCb->ueRabCb[0].protCfgOpt.p[count].pid;
	  tfwMsg->msg.ueUetAttachAcceptInd.esmInfo.protCfgOpt.p[count].len =\
	  	ueCb->ueRabCb[0].protCfgOpt.p[count].len;
	  cmMemcpy(tfwMsg->msg.ueUetAttachAcceptInd.esmInfo.protCfgOpt.p[count].val,\
	  	ueCb->ueRabCb[0].protCfgOpt.p[count].val,\
	  	ueCb->ueRabCb[0].protCfgOpt.p[count].len);
 	}
     for (count=0;count<ueCb->ueRabCb[0].protCfgOpt.numContId;count++)
 	{
 	  tfwMsg->msg.ueUetAttachAcceptInd.esmInfo.protCfgOpt.c[count].cid =\
	  	ueCb->ueRabCb[0].protCfgOpt.c[count].cid;
	  tfwMsg->msg.ueUetAttachAcceptInd.esmInfo.protCfgOpt.c[count].len =\
	  	ueCb->ueRabCb[0].protCfgOpt.c[count].len;
	  cmMemcpy(tfwMsg->msg.ueUetAttachAcceptInd.esmInfo.protCfgOpt.c[count].val,\
	  	ueCb->ueRabCb[0].protCfgOpt.c[count].val,\
	  	ueCb->ueRabCb[0].protCfgOpt.c[count].len);
 	}
   }
   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun:   updateGutiInUeCb
 *
 *       Desc:  Updates GUTI in UE CB.
 *
 *       Ret:  void
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE Void updateGutiInUeCb
(
   UeCb *ueCb,
   CmEmmEpsMI *epsMi
)
{
   cmMemcpy(ueCb->ueCtxt.ueGuti.mcc, epsMi->u.guti.mcc, 3);
   cmMemcpy(ueCb->ueCtxt.ueGuti.mnc, epsMi->u.guti.mnc, 3);
   ueCb->ueCtxt.ueGuti.mmeCode = epsMi->u.guti.mmeCode;
   ueCb->ueCtxt.ueGuti.mmeGrpId = epsMi->u.guti.mmeGrpId;
   ueCb->ueCtxt.ueGuti.mTMSI = epsMi->u.guti.mTMSI;

   RETVOID;
}

/*
 *
 *       Fun:   compareGutiInUeCb
 *
 *       Desc:  Compares received GUTI with one present in UE CB.
 *
 *       Ret:   ROK : if matches, RFAILED if does not match
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 compareGutiInUeCb
(
   UeCb *ueCb,
   CmEmmEpsMI *epsMi
)
{
   S16 ret = RFAILED;

   cmMemcpy(ueCb->ueCtxt.ueGuti.mcc, epsMi->u.guti.mcc, 3);
   cmMemcpy(ueCb->ueCtxt.ueGuti.mnc, epsMi->u.guti.mnc, 3);
   ueCb->ueCtxt.ueGuti.mmeCode = epsMi->u.guti.mmeCode;
   ueCb->ueCtxt.ueGuti.mmeGrpId = epsMi->u.guti.mmeGrpId;
   ueCb->ueCtxt.ueGuti.mTMSI = epsMi->u.guti.mTMSI;

   if ((cmMemcpy(ueCb->ueCtxt.ueGuti.mcc, epsMi->u.guti.mcc, 3)) &&
       (cmMemcpy(ueCb->ueCtxt.ueGuti.mnc, epsMi->u.guti.mnc, 3)) &&
       (ueCb->ueCtxt.ueGuti.mmeCode = epsMi->u.guti.mmeCode) &&
       (ueCb->ueCtxt.ueGuti.mmeGrpId = epsMi->u.guti.mmeGrpId) &&
       (ueCb->ueCtxt.ueGuti.mTMSI = epsMi->u.guti.mTMSI))
   {
      ret = ROK;
   }

   RETVALUE(ret);
}

/*
 *
 *       Fun: reverse
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE Void reverse(U8* str)
{
   U32 i, j;
   U8 temp;
   i=j=temp=0;

   j=strlen((S8*)str)-1;
   for (i=0; i<j; i++, j--)
   {
      temp=str[i];
      str[i]=str[j];
      str[j]=temp;
   }
}

/*
 *
 *       Fun: itoa()
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE U8* itoa(int num, U8* str, int base)
{
   U32 i = 0;
   U32 isNegative = 0;

   /* Handle 0 explicitely, otherwise empty string is printed for 0 */
   if (num == 0)
   {
      str[i++] = '0';
      str[i] = '\0';
      return str;
   }

   /* In standard itoa(), negative numbers are handled only with
    *     base 10. Otherwise numbers are considered unsigned.*/
   if (num < 0 && base == 10)
   {
      isNegative = 1;
      num = -num;
   }

   /* Process individual digits*/
   while (num != 0)
   {
      int rem = num % base;
      str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
      num = num/base;
   }

   /* If number is negative, append '-'*/
   if (isNegative)
      str[i++] = '-';

   str[i] = '\0'; /* Append string terminator*/

   /* Reverse the string*/
   reverse(str);

   return str;
}

/*
 *
 *       Fun: _fill_pf_comp
 *
 *       Desc: Fill Packet filters
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */

PRIVATE Void _fill_pf_comp(U8 idx, UeCb *ueCb, NbuUeIpInfoRsp *ueIpInfoRsp)
{
  U8 itrn = idx - 1;
  ueIpInfoRsp->noOfPfs = ueCb->ueRabCb[itrn].tft.noOfPfs;
  for (U8 pf_idx = 0; pf_idx < ueCb->ueRabCb[itrn].tft.noOfPfs; pf_idx++) {
    ueIpInfoRsp->pfList[pf_idx].id = ueCb->ueRabCb[itrn].tft.pfList[pf_idx].id;
    ueIpInfoRsp->pfList[pf_idx].dir =
        ueCb->ueRabCb[itrn].tft.pfList[pf_idx].dir;
    ueIpInfoRsp->pfList[pf_idx].preced =
        ueCb->ueRabCb[itrn].tft.pfList[pf_idx].preced;
    if (ueCb->ueRabCb[itrn].tft.pfList[pf_idx].ipv4.pres) {
      ueIpInfoRsp->pfList[pf_idx].presenceMask |= IPV4_REM_ADDR_PKT_FLTR_MASK;
      ueIpInfoRsp->pfList[pf_idx].remoteIpv4 =
          (ueCb->ueRabCb[itrn].tft.pfList[pf_idx].ipv4.ip4[0] << 24) +
          (ueCb->ueRabCb[itrn].tft.pfList[pf_idx].ipv4.ip4[1] << 16) +
          (ueCb->ueRabCb[itrn].tft.pfList[pf_idx].ipv4.ip4[2] << 8) +
          (ueCb->ueRabCb[itrn].tft.pfList[pf_idx].ipv4.ip4[3]);
    }
    if (ueCb->ueRabCb[itrn].tft.pfList[pf_idx].ipv6.pres) {
      ueIpInfoRsp->pfList[pf_idx].presenceMask |= IPV6_REM_ADDR_PKT_FLTR_MASK;
      cmMemcpy(ueIpInfoRsp->pfList[pf_idx].remoteIpv6Addr,
               ueCb->ueRabCb[itrn].tft.pfList[pf_idx].ipv6.ip6,
               CM_ESM_IPV6_SIZE);
    }
    if (ueCb->ueRabCb[itrn].tft.pfList[pf_idx].protId.pres) {
      ueIpInfoRsp->pfList[pf_idx].presenceMask |= PROTO_ID_PKT_FLTR_MASK;
      ueIpInfoRsp->pfList[pf_idx].protId =
          ueCb->ueRabCb[itrn].tft.pfList[pf_idx].protId.protType;
    }
    if (ueCb->ueRabCb[itrn].tft.pfList[pf_idx].localPort.pres) {
      ueIpInfoRsp->pfList[pf_idx].presenceMask |= SNGL_LOC_PORT_PKT_FLTR_MASK;
      ueIpInfoRsp->pfList[pf_idx].localPort =
          ntohs(ueCb->ueRabCb[itrn].tft.pfList[pf_idx].localPort.port);
    }
    if (ueCb->ueRabCb[itrn].tft.pfList[pf_idx].remotePort.pres) {
      ueIpInfoRsp->pfList[pf_idx].presenceMask |= SNGL_REM_PORT_PKT_FLTR_MASK;
      ueIpInfoRsp->pfList[pf_idx].remotePort =
          ntohs(ueCb->ueRabCb[itrn].tft.pfList[pf_idx].remotePort.port);
    }
    if (ueCb->ueRabCb[itrn].tft.pfList[pf_idx].locPortRange.pres) {
      ueIpInfoRsp->pfList[pf_idx].presenceMask |= LOC_PORT_RNG_PKT_FLTR_MASK;
      ueIpInfoRsp->pfList[pf_idx].locPortRangeLow =
          ntohs(ueCb->ueRabCb[itrn].tft.pfList[pf_idx].locPortRange.rangeLow);
      ueIpInfoRsp->pfList[pf_idx].locPortRangeHigh =
          ntohs(ueCb->ueRabCb[itrn].tft.pfList[pf_idx].locPortRange.rangeHigh);
    }
    if (ueCb->ueRabCb[itrn].tft.pfList[pf_idx].remPortRange.pres) {
      ueIpInfoRsp->pfList[pf_idx].presenceMask |= REM_PORT_RNG_PKT_FLTR_MASK;
      ueIpInfoRsp->pfList[pf_idx].remPortRangeLow =
          ntohs(ueCb->ueRabCb[itrn].tft.pfList[pf_idx].remPortRange.rangeLow);
      ueIpInfoRsp->pfList[pf_idx].remPortRangeLow =
          ntohs(ueCb->ueRabCb[itrn].tft.pfList[pf_idx].remPortRange.rangeHigh);
    }
    if (ueCb->ueRabCb[itrn].tft.pfList[pf_idx].secParam.pres) {
      ueIpInfoRsp->pfList[pf_idx].presenceMask |= SECURITY_PARAM_PKT_FLTR_MASK;
      cmMemcpy((U8 *)&ueIpInfoRsp->pfList[pf_idx].secParam,
               (U8 *)ueCb->ueRabCb[itrn].tft.pfList[pf_idx].secParam.params,
               CM_ESM_IP_SEC_SIZE);
    }
    if (ueCb->ueRabCb[itrn].tft.pfList[pf_idx].tos.pres) {
      ueIpInfoRsp->pfList[pf_idx].presenceMask |= SERV_N_CLASS_PKT_FLTR_MASK;
      ueIpInfoRsp->pfList[pf_idx].tos =
          ueCb->ueRabCb[itrn].tft.pfList[pf_idx].tos.tos;
    }
  }
}

/*
 *
 *       Fun: ueAppFormIpv4Addr
 *
 *       Desc: Converts the IPv4 address received from NW
 *             into dotted format(x.x.x.x)
 *
 *       Ret:  None
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */

PRIVATE Void ueAppFormIpv4Addr(NbuUeIpInfoRsp *ueIpInfoRsp,
                               CmEsmPdnAdd *pdn_addr) {
#define IPV4_BUF_SZ 20
  U8 temp[IPV4_BUF_SZ] = {0}, itrn = 0, cnt = 0;
  U8 ip_addr[IPV4_BUF_SZ] = {0};
  U32 counter = 0;
  U8 idx = 0;
  U8 offset = 0;
  /* In case of CM_ESM_PDN_IPV4V6 pdn_addr contains IPv6 addr
   * followed by IPv4 address. Hence skip first 8 bytes*/
  if (pdn_addr->pdnType == CM_ESM_PDN_IPV4V6) {
    offset = 8;
  }
  for (counter = offset; counter < (pdn_addr->len - 1); counter++) {
    itoa(pdn_addr->addrInfo[counter], temp, 10);
    for (cnt = 0; (itrn < IPV4_BUF_SZ) && (temp[cnt] != '\0') &&
                  (cnt < (IPV4_BUF_SZ - 1));
         itrn++, cnt++)
      ip_addr[itrn] = temp[cnt];
    if (counter != (pdn_addr->len - 2) && (itrn < IPV4_BUF_SZ))
      ip_addr[itrn++] = '.';
    if (counter == (pdn_addr->len - 2) && (itrn < IPV4_BUF_SZ))
      ip_addr[itrn] = '\0';
  }
  strcpy(ueIpInfoRsp->Ip4Addr, ip_addr);
  RETVOID;
}

/*
 *
 *       Fun: ueAppFormIpv6Addr
 *
 *       Desc: Converts the IPv6 address received from NW
 *             into : separated format(x:x:x:x:x:x:x:x)
 *
 *       Ret:  None
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE Void ueAppFormIpv6Addr(NbuUeIpInfoRsp *ueIpInfoRsp, UeRabCb *ueRabCb) {
  UeAppCb *ueAppCb = NULLP;
  U8 ip6_str[INET6_ADDRSTRLEN];

  UE_GET_CB(ueAppCb);
  UE_LOG_ENTERFN(ueAppCb);

  /* For default bearer form IPv6 address string by prepending
   * Link local address-fe80:
   */
  if (ueRabCb->bearerType == DEFAULT_BEARER) {
    sprintf(ip6_str, "%s::%02x%02x:%02x%02x:%02x%02x:%02x%02x", "fe80",
            (int)ueRabCb->pAddr.addrInfo[0], (int)ueRabCb->pAddr.addrInfo[1],
            (int)ueRabCb->pAddr.addrInfo[2], (int)ueRabCb->pAddr.addrInfo[3],
            (int)ueRabCb->pAddr.addrInfo[4], (int)ueRabCb->pAddr.addrInfo[5],
            (int)ueRabCb->pAddr.addrInfo[6], (int)ueRabCb->pAddr.addrInfo[7]);

  } else {
    /* For dedicated bearer form IPv6 address string using the
     * ipv6 address in ueRabCb->ipv6Addr as the pAddr.addrInfo contains
     * only interface id
     */
    sprintf(ip6_str,
            "%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%"
            "02x%02x",
            (int)ueRabCb->ipv6Addr[0], (int)ueRabCb->ipv6Addr[1],
            (int)ueRabCb->ipv6Addr[2], (int)ueRabCb->ipv6Addr[3],
            (int)ueRabCb->ipv6Addr[4], (int)ueRabCb->ipv6Addr[5],
            (int)ueRabCb->ipv6Addr[6], (int)ueRabCb->ipv6Addr[7],
            (int)ueRabCb->ipv6Addr[8], (int)ueRabCb->ipv6Addr[9],
            (int)ueRabCb->ipv6Addr[10], (int)ueRabCb->ipv6Addr[11],
            (int)ueRabCb->ipv6Addr[12], (int)ueRabCb->ipv6Addr[13],
            (int)ueRabCb->ipv6Addr[14], (int)ueRabCb->ipv6Addr[15]);
  }
  cmMemcpy(ueIpInfoRsp->Ip6Addr, ip6_str, INET6_ADDRSTRLEN);
  UE_LOG_DEBUG(ueAppCb, "Sending ipv6 address %s to enbApp for bearer %d",
               ip6_str, ueRabCb->epsBearerId);
  RETVOID;
}

/*
 *
 *       Fun: populateIpInfo
 *
 *       Desc: Populates NbuUeIpInfoRsp structure
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PUBLIC Void populateIpInfo(UeCb *ueCb, U8 bearerId,
                           NbuUeIpInfoRsp *ueIpInfoRsp)
{
  U8 idx = 0;
  CmEsmPdnAdd *pdn_addr = NULLP;
  ueIpInfoRsp->ueId = ueCb->ueId;
  ueIpInfoRsp->bearerId = bearerId;

  for (idx = 1; idx < UE_APP_MAX_DRBS; idx++) {
    if (ueCb->drbs[idx] == UE_APP_DRB_INUSE) {
      if (ueCb->ueRabCb[idx - 1].epsBearerId == bearerId) {
        pdn_addr = &ueCb->ueRabCb[idx - 1].pAddr;
        ueIpInfoRsp->berType = ueCb->ueRabCb[idx - 1].bearerType;
        ueIpInfoRsp->lnkEpsBearId = bearerId;
        _fill_pf_comp(idx, ueCb, ueIpInfoRsp);
        break;
      }
    }
  }
  // Construct IP address
  if ((pdn_addr != NULLP) && pdn_addr->pres) {
    if (pdn_addr->pdnType == CM_ESM_PDN_IPV4) {
      ueIpInfoRsp->pdnType = CM_ESM_PDN_IPV4;
      // Convert IPv4 address arrary to dotted notation(x.x.x.x)
      ueAppFormIpv4Addr(ueIpInfoRsp, pdn_addr);
    } else if (pdn_addr->pdnType == CM_ESM_PDN_IPV6) {
      ueIpInfoRsp->pdnType = CM_ESM_PDN_IPV6;
      // Convert IPv6 address arrary to ":" separated notation(x:x:x:x:x:x:x:x)
      ueAppFormIpv6Addr(ueIpInfoRsp, &ueCb->ueRabCb[idx - 1]);
    } else if (pdn_addr->pdnType == CM_ESM_PDN_IPV4V6) {
      ueIpInfoRsp->pdnType = CM_ESM_PDN_IPV4V6;
      // Convert IPv4 address arrary to dotted notation(x.x.x.x)
      ueAppFormIpv4Addr(ueIpInfoRsp, pdn_addr);
      // Convert IPv6 address arrary to ":" separated notation(x:x:x:x:x:x:x:x)
      ueAppFormIpv6Addr(ueIpInfoRsp, &(ueCb->ueRabCb[idx - 1]));
    }
  }
}

/*
 *
 *       Fun: ueAppRcvEmmMsg
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppRcvEmmMsg
(
 CmNasEvnt *evnt,
 U8 emmMsgType,
 UeCb *ueCb
)
{
   S16 ret = RFAILED;
   UeAppCb *ueAppCb = NULLP;
   UetMessage *tfwMsg = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   /* Release the Event Structure as we dont use it anymore */
   UE_LOG_DEBUG(ueAppCb, "Received EMM Msg with MsgType(%d)", emmMsgType);

   switch (emmMsgType)
   {
      case CM_EMM_MSG_ID_REQ: /* Identity request from mme */
      {
         ueCb->res.pres = TRUE;
         ueCb->res.len = UE_USIM_RES_SIZE;
         if (ueCb->ecmCb.state == UE_ECM_IDLE) {
           ueCb->ecmCb.state = UE_ECM_CONNECTED;
         }
         tfwMsg = (UetMessage*)ueAlloc(sizeof(UetMessage));
         ret = ueBldIdentReqIndMsgToTfw(tfwMsg, ueCb,
                                        evnt->m.emmEvnt->u.idReq.idType.type);

         ret = ueSendToTfwApp(tfwMsg, &ueAppCb->fwPst);
         if (ret != ROK)
         {
            UE_LOG_ERROR(ueAppCb,
                        "Sending Identity Request Indication to TFWAPP failed");
         }
         break;
      }
      case CM_EMM_MSG_AUTH_REQ: /* Authentication request from mme */
      {
         ueCb->ueCtxt.rnd[0] = 1;
         /* Initiate authentication response to MME */
         if (0 == cmMemcmp(ueCb->ueCtxt.rnd,\
                           evnt->m.emmEvnt->u.authReq.RAND.val, 16))
         {
            UE_LOG_DEBUG(ueAppCb, "RAND Is Matching, Ignoring The AuthRequest");
            CM_FREE_NASEVNT(&evnt);
            RETVALUE(RFAILED);
         }

         cmMemset((U8*)&ueCb->secCtxt, 0, sizeof(ueCb->secCtxt));
         cmMemcpy(ueCb->ueCtxt.rnd, evnt->m.emmEvnt->u.authReq.RAND.val, 16);
         cmMemcpy(ueCb->secCtxt.autn, evnt->m.emmEvnt->u.authReq.AUTN.val, 16);
         ueCb->secCtxt.tsc = evnt->m.emmEvnt->u.authReq.nasKsi.tsc;
         ueCb->secCtxt.ksi = evnt->m.emmEvnt->u.authReq.nasKsi.id;

         if (ueCb->ecmCb.state == UE_ECM_IDLE) {
           ueCb->ecmCb.state = UE_ECM_CONNECTED;
         }

         /* Milanage, Snow3g, AES based auth and security */
         ueUsimCalcAndStoreAuthKeys(&ueCb->ueInfo, &ueCb->ueAuthKeys,
               ueCb->res.val, evnt->m.emmEvnt->u.authReq.AUTN.val,
               evnt->m.emmEvnt->u.authReq.RAND.val);

         UE_LOG_DEBUG(ueAppCb, "Sending Auth Request Indication to Test "\
               "Controller");
         ueCb->res.pres = TRUE;
         ueCb->res.len = UE_USIM_RES_SIZE;
         tfwMsg = (UetMessage*)ueAlloc(sizeof(UetMessage));
         ret = ueBldAuthReqIndMsgToTfw(tfwMsg, ueCb);

         ret = ueSendToTfwApp(tfwMsg, &ueAppCb->fwPst);
         if (ret != ROK)
         {
            UE_LOG_ERROR(ueAppCb, "Sending Authentication Request "\
                  "Indication to TFWAPP failed");
         }
         break;
      }
      case CM_EMM_MSG_SEC_MODE_CMD:
      {
         ueCb->secCtxt.ksi    = evnt->m.emmEvnt->u.secModCmd.nasKsi.id;
         ueCb->secCtxt.tsc    = evnt->m.emmEvnt->u.secModCmd.nasKsi.tsc;
         ueCb->secCtxt.status = UE_APP_SEC_CTXT_CRNT;
         ueCb->secCtxt.intAlg =
            evnt->m.emmEvnt->u.secModCmd.selNasSecAlgo.intProtAlgo;
         ueCb->secCtxt.encAlg =
            evnt->m.emmEvnt->u.secModCmd.selNasSecAlgo.ciphAlgo;

         if (evnt->m.emmEvnt->u.secModCmd.imeisvReq.pres) {
           ueCb->ueCtxt.imeisvReq = TRUE;
         }
         ret = ueAppGenerateNasKey(&ueCb->secCtxt);
         if (ROK != ret)
         {
            UE_LOG_ERROR(ueAppCb, "NAS Key Gen Failed");
            ret = RFAILED;
         }
         ret = ueAppGenerateEnbKey(&ueCb->secCtxt,
               (U32)ueCb->secCtxt.lstUsdCnt);

         if (ROK != ret)
         {
            UE_LOG_ERROR(ueAppCb, "AS Key Gen Failed");
            ret = RFAILED;
         }
         tfwMsg = (UetMessage*)ueAlloc(sizeof(UetMessage));
         ret = ueBldSecModeCmdIndToTfw(tfwMsg, ueCb);

         ret = ueSendToTfwApp(tfwMsg, &ueAppCb->fwPst);
         if (ret != ROK)
         {
            UE_LOG_ERROR(ueAppCb, "Sending SEC MODE SMD Indication to TFWAPP failed");
         }
         break;
      }
      case CM_EMM_MSG_ATTACH_ACC:
      {
         /* Updating the Uecb */
         /* if unit is 0, then multiply the val into 2 seconds */
         if (evnt->m.emmEvnt->u.atchAcc.t3412.unit == 0)
         {
            ueCb->t3412 = evnt->m.emmEvnt->u.atchAcc.t3412.val * 2;
         }
         /* if unit is 1, then multiply the val into 60 seconds(1 min) */
         else if (evnt->m.emmEvnt->u.atchAcc.t3412.unit == 1)
         {
            ueCb->t3412 = evnt->m.emmEvnt->u.atchAcc.t3412.val * 60;
         }
         /* if unit is 2, then multiply the val into 6*60 seconds(6 min) */
         else if (evnt->m.emmEvnt->u.atchAcc.t3412.unit == 2)
         {
            ueCb->t3412 = evnt->m.emmEvnt->u.atchAcc.t3412.val * 6 * 60;
         }
         else
         {
            UE_LOG_ERROR(ueAppCb, "Invalid unit for t3412 timer");
         }
         ueCb->t3402 = evnt->m.emmEvnt->u.atchAcc.t3402.val;
         ueCb->t3423 = evnt->m.emmEvnt->u.atchAcc.t3423.val;
         ueCb->epsAtchRes = evnt->m.emmEvnt->u.atchAcc.epsAtchRes.res;

         UE_LOG_DEBUG(ueAppCb, "Updating GUTI in UeCb");
         updateGutiInUeCb(ueCb, &evnt->m.emmEvnt->u.atchAcc.guti);

         cmMemcpy(ueCb->ueCtxt.msId, evnt->m.emmEvnt->u.atchAcc.msId.u.imsi.id,
               CM_EMM_MAX_MOBILE_ID_DIGS);

         ueCb->emmCause = evnt->m.emmEvnt->u.atchAcc.cause.cause;
         cmMemcpy((U8 *)&ueCb->plmnLst, (U8 *)&evnt->m.emmEvnt->u.atchAcc.\
               eqPlmnLst.plmnLst, sizeof(CmEmmPlmnId));

         tfwMsg = (UetMessage*)ueAlloc(sizeof(UetMessage));
         cmMemset((U8 *)tfwMsg, 0, sizeof(UetMessage));

         tfwMsg->msg.ueUetAttachAcceptInd.esmInfo.epsBearerId = evnt->m.emmEvnt->u.atchAcc.esmEvnt->m.esmEvnt->bearerId;
         ret = ueBldAttachAcceptToTfw(tfwMsg, ueCb);
         if (ret != ROK)
         {
            UE_LOG_ERROR(ueAppCb, "Building Attach Accept Indication to TFWAPP Failed");
            ret = RFAILED;
         }
         ret = ueSendToTfwApp(tfwMsg, &ueAppCb->fwPst);
         if (ret != ROK)
         {
            UE_LOG_ERROR(ueAppCb, "Sending Attach Accept Indication to TFWAPP Failed");
            ret = RFAILED;
         }
         break;
      }
      case CM_EMM_MSG_TAU_ACC:
      {
         /* Updating the UeCb */
         if (evnt->m.emmEvnt->u.tauAcc.t3412.unit == 0)
         {
            /* if unit is 0, then multiply the val into 2 seconds */
            ueCb->t3412 = evnt->m.emmEvnt->u.tauAcc.t3412.val * 2;
         }
         else if (evnt->m.emmEvnt->u.tauAcc.t3412.unit == 1)
         {
            /* if unt is 1, then multiply the val into 60 seconds(1 min) */
            ueCb->t3412 = evnt->m.emmEvnt->u.tauAcc.t3412.val * 60;
         }
         /* if unit is 2, then multiply the val into 6*60 seconds(6 min) */
         else if (evnt->m.emmEvnt->u.tauAcc.t3412.unit == 2)
         {
            ueCb->t3412 = evnt->m.emmEvnt->u.tauAcc.t3412.val * 6 * 60;
         }
         else
         {
            UE_LOG_ERROR(ueAppCb, "Invalid unit for t3412 timer");
         }

         ueCb->t3402 = evnt->m.emmEvnt->u.tauAcc.t3402.val;
         ueCb->t3423 = evnt->m.emmEvnt->u.tauAcc.t3423.val;

         cmMemcpy(ueCb->ueCtxt.msId,
                  evnt->m.emmEvnt->u.tauAcc.msId.u.imsi.id,
                  CM_EMM_MAX_MOBILE_ID_DIGS);

         ueCb->emmCause = evnt->m.emmEvnt->u.tauAcc.cause.cause;
         cmMemcpy((U8 *)&ueCb->plmnLst,
                  (U8 *)&evnt->m.emmEvnt->u.tauAcc.eqPlmnLst.plmnLst,
                  sizeof(CmEmmPlmnId));

         /* TODO:
            Check if Guti is present,
            Compare with oldGuti,
            If it is diferent update in UeCb, then print */

         /* If GUTI is present then update in UE Db */
         if (evnt->m.emmEvnt->u.tauAcc.guti.pres)
         {
            /* Check if GUTI has changed */
            ret = compareGutiInUeCb(ueCb, &evnt->m.emmEvnt->u.tauAcc.guti);
            if (ret == ROK)
            {
               ueCb->gutiChanged = TRUE;
               UE_LOG_DEBUG(ueAppCb, "GUTI changed, updating GUTI in UeCb");
               updateGutiInUeCb(ueCb, &evnt->m.emmEvnt->u.tauAcc.guti);
            }
         }

         tfwMsg = (UetMessage*)ueAlloc(sizeof(UetMessage));
         cmMemset((U8 *)tfwMsg, 0, sizeof(UetMessage));
         ret = ueBldTauAcceptToTfw(tfwMsg, &evnt->m.emmEvnt->u.tauAcc, ueCb);
         if (ret != ROK)
         {
            UE_LOG_ERROR(ueAppCb, "Building TAU Accept Ind Failed");
            ret = RFAILED;
         }

         ret = ueSendToTfwApp(tfwMsg, &ueAppCb->fwPst);
         if (ret != ROK)
         {
            UE_LOG_ERROR(ueAppCb, "Sending of TAU Accept Indication to "\
                  "TFWAPP Failed");
            ret = RFAILED;
         }

         break;
      }
      case CM_EMM_MSG_ATTACH_REJ:
      {
         tfwMsg = (UetMessage*)ueAlloc(sizeof(UetMessage));
         ret = ueBldAttachRejectIndToTfw(tfwMsg, ueCb,
               evnt->m.emmEvnt->u.atchRej.emmCause.cause);

         ret = ueSendToTfwApp(tfwMsg, &ueAppCb->fwPst);
         if (ret != ROK)
         {
            UE_LOG_ERROR(ueAppCb, "Sending Attach Reject Indication to "\
                  "TFWAPP failed");
         }
         break;
      }
      case CM_EMM_MSG_TAU_REJ:
      {
         if (evnt->m.emmEvnt->u.tauRej.t3346.pres == TRUE)
         {
            ueCb->t3346 = evnt->m.emmEvnt->u.tauRej.t3346.val;
         }
         tfwMsg = (UetMessage*)ueAlloc(sizeof(UetMessage));
         ret = ueBldTauRejectIndToTfw(tfwMsg, ueCb,\
               evnt->m.emmEvnt->u.tauRej.emmCause.cause);

         ret = ueSendToTfwApp(tfwMsg, &ueAppCb->fwPst);
         if (ret != ROK)
         {
            UE_LOG_ERROR(ueAppCb, "Sending Tracking Area Update Reject "\
                  "Indication to TFW APP failed");
         }
         break;
      }
      case CM_EMM_MSG_DETACH_ACC:
      {
         tfwMsg = (UetMessage*)ueAlloc(sizeof(UetMessage));
         ret = ueBldDetachAcceptIndToTfw(tfwMsg, ueCb, evnt->m.emmEvnt->\
               u.dtchAcc.type);

         ret = ueSendToTfwApp(tfwMsg, &ueAppCb->fwPst);
         if (ret != ROK)
         {
            UE_LOG_ERROR(ueAppCb, "Sending Detach Accept Indication to "\
                  "TFWAPP failed");
         }
         else
         {
            UE_LOG_DEBUG(ueAppCb, "UeCb deleted in Detach "\
                  "Accept handling");
         }
         break;
      }
      case CM_EMM_MSG_SVC_REJ:
      {
         tfwMsg = (UetMessage*)ueAlloc(sizeof(UetMessage));
         ret = ueBldServiceRejectIndToTfw(tfwMsg, ueCb, evnt->m.emmEvnt->\
               u.srvRej.emmCause.cause);

         ret = ueSendToTfwApp(tfwMsg, &ueAppCb->fwPst);
         if (ret != ROK)
         {
            UE_LOG_ERROR(ueAppCb, "Sending Service Reject Indication to "\
                  "TFWAPP failed");
         }
         break;
      }
      case CM_EMM_MSG_DETACH_REQ:
      {
         tfwMsg = (UetMessage*)ueAlloc(sizeof(UetMessage));
         ret = ueBldNwInitDetachReqToTfw(tfwMsg, ueCb,evnt->m.emmEvnt->\
               u.dtchReq.detchType, evnt->m.emmEvnt->\
               u.dtchReq.cause);

         ret = ueSendToTfwApp(tfwMsg, &ueAppCb->fwPst);
         if (ret != ROK)
         {
            UE_LOG_ERROR(ueAppCb, "Sending Network init detach Request"\
                  "Indication to TFWAPP failed");
         }
         break;
      }
      case CM_EMM_MSG_EMM_INFO:
      {
         tfwMsg = (UetMessage*)ueAlloc(sizeof(UetMessage));
         ret = ueBldEmmInformationToTfw(tfwMsg, ueCb);
         ret = ueSendToTfwApp(tfwMsg, &ueAppCb->fwPst);
         if (ret != ROK)
         {
            UE_LOG_ERROR(ueAppCb, "Sending EMM Information Failed");
         }
         break;
      }
      case CM_EMM_MSG_AUTH_REJ:
      {
         UE_LOG_DEBUG(ueAppCb, "Received Auth Reject message \n");
         tfwMsg = (UetMessage*)ueAlloc(sizeof(UetMessage));
         ret = ueBldAuthRejToTfw(tfwMsg, ueCb);
         ret = ueSendToTfwApp(tfwMsg, &ueAppCb->fwPst);
         if (ret != ROK)
         {
            UE_LOG_ERROR(ueAppCb, "Sending Authentication Reject Failed");
         }
         break;
      }
      default:
      {
         UE_LOG_ERROR(ueAppCb, "Invalid EMM MsgType");
         ret = RFAILED;
      }
   }

   UE_LOG_EXITFN(ueAppCb, ret);
} /* End od ueAppRcvEmmMsg */

/*
 *
 *       Fun: ueAppEmmHndlInDetachAccept
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppEmmHndlInDetachAccept
(
 CmNasEvnt *evnt,
 UeCb *ueCb
)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Handling Incoming Detach Accept message");

   /*send message to USER*/
   ret = ueAppRcvEmmMsg(evnt, evnt->m.emmEvnt->msgId, ueCb);

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueAppEmmHndlInServiceRej
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppEmmHndlInServiceRej
(
 CmNasEvnt *evnt,
 UeCb *ueCb
)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Handling Incoming Service Reject message");
   /*send message to USER*/
   ret = ueAppRcvEmmMsg(evnt, evnt->m.emmEvnt->msgId, ueCb);

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueAppEmmHndlInIdentReq
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppEmmHndlInIdentReq(CmNasEvnt *evnt, UeCb *ueCb)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Handling Incoming Identity Request message");

   /*send message to USER*/
   ret = ueAppRcvEmmMsg(evnt, evnt->m.emmEvnt->msgId, ueCb);

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueAppEmmHndlInAuthReq
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppEmmHndlInAuthReq(CmNasEvnt *evnt, UeCb *ueCb)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Handling Incoming Authenticatin request message");
   /*send message to USER*/
   ret = ueAppRcvEmmMsg(evnt, evnt->m.emmEvnt->msgId, ueCb);

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueAppEmmHndlInSecModecmd
 *
 *       Desc: Handle Security Mode Command coming from eNodeB/MME.
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppEmmHndlInSecModecmd(CmNasEvnt *evnt, UeCb *ueCb)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Handling Incoming SEC MODE CMD message");

   /*send message to USER*/
   ret = ueAppRcvEmmMsg(evnt, evnt->m.emmEvnt->msgId, ueCb);
   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueAppUtlMovEsmCbTransToBid
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppUtlMovEsmCbTransToBid(UeEsmCb *esmCb, UeCb *ueCb)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Moving EsmCb to bid list");

   ueCb->esmTList[esmCb->tId] = NULLP;
   if(!ueCb->esmBList[esmCb->bId])
   {
      ueCb->esmBList[esmCb->bId] = esmCb;
   }
   else
   {
      UE_LOG_DEBUG(ueAppCb, "The bid Entry Exist in the List bid(%d)", esmCb->bId);
   }

   UE_LOG_EXITFN(ueAppCb, ret);
} /* end of ueAppUtlMovEsmCbTransToBid */

/*
 *
 *       Fun: uefillDefEsmInfoToUeCb
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 uefillDefEsmInfoToUeCb
(
 UeCb *ueCb,
 CmNasEvnt *evnt,
 U8 drbId,
 U8 epsBearerId
)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   CmEsmActDefBearCtxtReq *actReq = NULLP;
   UeRabCb *params;
   U8 count;
   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);
   params = &ueCb->ueRabCb[drbId];
   actReq = &evnt->m.esmEvnt->u.actReq;
   ueCb->ueRabCb[drbId].drbId = drbId;
   ueCb->ueRabCb[drbId].epsBearerId = epsBearerId;
   params->bearerType = DEFAULT_BEARER;
   if(actReq->epsQos.pres == TRUE)
   {
      params->epsQos.pres              = TRUE;
      params->epsQos.lenQosCont        = actReq->epsQos.lenQosCont;
      params->epsQos.qci               = actReq->epsQos.qci;
      params->epsQos.maxBitRateUL      = actReq->epsQos.maxBitRateUL;
      params->epsQos.maxBitRateDL      = actReq->epsQos.maxBitRateDL;;
      params->epsQos.guaraBitRateUL    = actReq->epsQos.guaraBitRateUL;
      params->epsQos.guaraBitRateDL    = actReq->epsQos.guaraBitRateDL;
      params->epsQos.maxBitRateULExt   = actReq->epsQos.maxBitRateULExt;
      params->epsQos.maxBitRateDLExt   = actReq->epsQos.maxBitRateDLExt;
      params->epsQos.guaraBitRateULExt = actReq->epsQos.guaraBitRateULExt;
      params->epsQos.guaraBitRateDLExt = actReq->epsQos.guaraBitRateDLExt;
   }
   else
   {
      params->epsQos.pres = FALSE;
   }
   if(actReq->apn.pres == TRUE)
   {
      params->apn.pres = TRUE;
      params->apn.len = actReq->apn.len;
      cmMemcpy((U8 *)&params->apn.apn, (U8 *)&actReq->apn.apn,
            CM_ESM_MAX_LEN_ACCESS_PTNAME);
   }
   else
   {
      params->apn.pres = FALSE;
   }
   if (actReq->pAddr.pres == TRUE) {
     params->pAddr.pres = TRUE;
     params->pAddr.len = actReq->pAddr.len;
     params->pAddr.pdnType = actReq->pAddr.pdnType;
     cmMemcpy((U8 *)&params->pAddr.addrInfo, (U8 *)&actReq->pAddr.addrInfo,
              sizeof(actReq->pAddr.addrInfo));
   } else {
     params->pAddr.pres = FALSE;
   }
   if(actReq->pAddr.pres == TRUE) {
      params->pAddr.pres = TRUE;
      params->pAddr.len = actReq->pAddr.len;
      params->pAddr.pdnType = actReq->pAddr.pdnType;
      cmMemcpy((U8 *)&params->pAddr.addrInfo, (U8 *)&actReq->pAddr.addrInfo,
            sizeof(actReq->pAddr.addrInfo));
   }
   else
   {
      params->pAddr.pres = FALSE;
   }
   if(actReq->txnId.pres == TRUE)
   {
      params->txnId.pres = TRUE;
      params->txnId.len = actReq->txnId.len;
      params->txnId.tiVal = actReq->txnId.tiVal;
      params->txnId.tiFlag = actReq->txnId.tiFlag;
      params->txnId.tie = actReq->txnId.tie;
      params->txnId.tiExt = actReq->txnId.tiExt;
   }
   else
   {
      params->txnId.pres = FALSE;
   }
   if(actReq->qos.pres == TRUE)
   {
      params->qos.pres              = TRUE;
      params->qos.lenQosCont        = actReq->qos.lenQosCont;
      params->qos.relClass          = actReq->qos.relClass;
      params->qos.delayClass        = actReq->qos.delayClass;
      params->qos.precClass         = actReq->qos.precClass;
      params->qos.peakTp            = actReq->qos.peakTp;
      params->qos.meanTp            = actReq->qos.meanTp;
      params->qos.deliveryErrSdu    = actReq->qos.deliveryErrSdu;
      params->qos.deliveryOrder     = actReq->qos.deliveryOrder;
      params->qos.trafficClass      = actReq->qos.trafficClass;
      params->qos.maxSdu            = actReq->qos.maxSdu;
      params->qos.maxBitRateUL      = actReq->qos.maxBitRateUL;
      params->qos.maxBitRateDL      = actReq->qos.maxBitRateDL;
      params->qos.sduErrRatio       = actReq->qos.sduErrRatio;
      params->qos.residualBer       = actReq->qos.residualBer;
      params->qos.trafHandPrio      = actReq->qos.trafHandPrio;
      params->qos.transferDelay     = actReq->qos.transferDelay;
      params->qos.guaraBitRateUL    = actReq->qos.guaraBitRateUL;
      params->qos.guaraBitRateDL    = actReq->qos.guaraBitRateDL;
      params->qos.srcStatDesc       = actReq->qos.srcStatDesc;
      params->qos.signalInd         = actReq->qos.signalInd;
      params->qos.maxBitRateDLExt   = actReq->qos.maxBitRateDLExt;
      params->qos.maxBitRateULExt   = actReq->qos.maxBitRateULExt;
      params->qos.guaraBitRateDLExt = actReq->qos.guaraBitRateDLExt;
      params->qos.guaraBitRateULExt = actReq->qos.guaraBitRateULExt;
   }
   else
   {
      params->qos.pres              = FALSE;
   }
   if(actReq->llc.pres == TRUE)
   {
      params->llc.pres = TRUE;
      params->llc.ieVal = actReq->llc.ieVal;
   }
   else
   {
      params->llc.pres = FALSE;
   }
   if(actReq->radioPrio.pres == TRUE)
   {
      params->radioPrio.pres = TRUE;
      params->radioPrio.ieVal = actReq->radioPrio.ieVal;
   }
   else
   {
      params->radioPrio.pres = FALSE;
   }
   if(actReq->pktFlowId.pres == TRUE)
   {
      params->pktFlowId.pres = TRUE;
      params->pktFlowId.len = actReq->pktFlowId.len;
      params->pktFlowId.ieVal = actReq->pktFlowId.ieVal;
   }
   else
   {
      params->pktFlowId.pres = FALSE;
   }
   if(actReq->apnAmbr.pres == TRUE)
   {
      params->apnAmbr.pres = TRUE;
      params->apnAmbr.len = actReq->apnAmbr.len;
      params->apnAmbr.dl = actReq->apnAmbr.dl;
      params->apnAmbr.ul = actReq->apnAmbr.ul;
      params->apnAmbr.dlExt = actReq->apnAmbr.dlExt;
      params->apnAmbr.ulExt = actReq->apnAmbr.ulExt;
      params->apnAmbr.dlExt2 = actReq->apnAmbr.dlExt2;
      params->apnAmbr.ulExt2 = actReq->apnAmbr.ulExt2;
   }
   else
   {
      params->apnAmbr.pres = FALSE;
   }
   if(actReq->cause.pres == TRUE)
   {
      params->cause.pres = TRUE;
      params->cause.val = actReq->cause.val;
   }
   else
   {
      params->cause.pres = FALSE;
   }
   if(actReq->protCfgOpt.pres == TRUE)
   {
     params->protCfgOpt.pres = TRUE;
     params->protCfgOpt.len = actReq->protCfgOpt.len;
     params->protCfgOpt.cfgProt = actReq->protCfgOpt.cfgProt;
     params->protCfgOpt.ext = actReq->protCfgOpt.ext;
     params->protCfgOpt.numProtId = actReq->protCfgOpt.numProtId;
     params->protCfgOpt.numContId = actReq->protCfgOpt.numContId;

     for(count=0;count<actReq->protCfgOpt.numProtId;count++)
     {
          params->protCfgOpt.p[count].pid = actReq->protCfgOpt.p[count].pid;
          params->protCfgOpt.p[count].len = actReq->protCfgOpt.p[count].len;
          cmMemcpy(params->protCfgOpt.p[count].val,
             actReq->protCfgOpt.p[count].val,
             actReq->protCfgOpt.p[count].len);
     }
     for(count=0;count<actReq->protCfgOpt.numContId;count++)
     {
       params->protCfgOpt.c[count].cid = actReq->protCfgOpt.c[count].cid;
       params->protCfgOpt.c[count].len = actReq->protCfgOpt.c[count].len;
       cmMemcpy(params->protCfgOpt.c[count].val,
          actReq->protCfgOpt.c[count].val,
       actReq->protCfgOpt.c[count].len);
     }

   }
   else
   {
     params->protCfgOpt.pres = FALSE;
   }

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueAppEsmHndlIncActDefBearerReq
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppEsmHndlIncActDefBearerReq(UeEsmCb *esmCb, CmNasEvnt *evnt,
                                           UeCb *ueCb, U8 *AllocDrbId,
                                           U8 epsBearerId) {
  S16 ret = ROK;
  UeAppCb *ueAppCb = NULLP;
  CmInetNetAddr *selfAddr = NULLP;
  CmEsmPdnAdd *pAddr = NULLP;
  U8 drbId = 0;

  UE_GET_CB(ueAppCb);
  UE_LOG_ENTERFN(ueAppCb);

  UE_LOG_DEBUG(ueAppCb, "Activate default bearer request");

  /* Update procedure transaction state */
  esmCb->pState = UE_ESM_ST_PROC_TXN_INACTIVE;

  /* update bearer Id */
  esmCb->bId = evnt->m.esmEvnt->bearerId;

  ueAppUtlMovEsmCbTransToBid(esmCb, ueCb);
  /* If is_actv_dflt_eps_ber_ctxt_rej flag is set
   * do not create context for the bearer*/
  if (ueCb->is_actv_dflt_eps_ber_ctxt_rej) {
    RETVALUE(ROK);
  }
  /* Update pdn address in ue context */
  selfAddr = &(ueCb->ueCtxt.selfAddr);
  pAddr = &evnt->m.esmEvnt->u.actReq.pAddr;

  if (pAddr->pdnType == CM_ESM_PDN_IPV4) {
    selfAddr->u.ipv4NetAddr =
        (((U32)(pAddr->addrInfo[0]) << 24) | ((U32)(pAddr->addrInfo[1]) << 16) |
         ((U32)(pAddr->addrInfo[2]) << 8) | (U32)(pAddr->addrInfo[3]));
  } else {
#ifdef IPV6_SUPPORTED
    cmMemcpy((U8 *)&selfAddr->u.ipv6NetAddr, (U8 *)pAddr->addrInfo, pAddr->len);
#endif
  }

  ret = ueAppGetDrb(ueCb, &drbId);
  if (ret != ROK) {
    UE_LOG_ERROR(ueAppCb, "DRB Cb not found");
    RETVALUE(ret);
  }

  ueCb->numRabs++;

  ret = uefillDefEsmInfoToUeCb(ueCb, evnt, (drbId - 1), epsBearerId);

  *AllocDrbId = drbId;
  RETVALUE(ROK);
} /* ueAppEsmHndlIncActDefBearerReq */

PRIVATE S16 ueAppEsmHndlIncPdnConRej
(
 UeEsmCb *esmCb,
 CmNasEvnt *evnt,
 UeCb *ueCb
)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb   = NULLP;
   UetMessage *tfwMsg = NULLP;
   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   TRC2(ueAppEsmHndlIncPdnConRej)

   UE_LOG_DEBUG(ueAppCb, "Activate default bearer request");

   /* Update procedure transaction state */
   esmCb->pState = UE_ESM_ST_PROC_TXN_INACTIVE;
   /* send pdn connection reject indication to user */
   tfwMsg = (UetMessage*)ueAlloc(sizeof(UetMessage));
   tfwMsg->msg.ueUetPdnConRsp.ueId                        = ueCb->ueId;
   tfwMsg->msg.ueUetPdnConRsp.status                      = FALSE;
   tfwMsg->msg.ueUetPdnConRsp.m.pdnConRejInfo.esmCause    = \
     evnt->m.esmEvnt->u.conRej.cause.val;
   tfwMsg->msg.ueUetPdnConRsp.m.pdnConRejInfo.epsBearerId = esmCb->bId;
   tfwMsg->msgType = UE_PDN_CON_RSP_TYPE;
   ret = ueSendToTfwApp(tfwMsg, &ueAppCb->fwPst);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Sending Attach Reject Indication to "\
            "TFWAPP failed");
   }
   RETVALUE(ROK);
} /* ueAppEsmHndlIncPdnConRej */

PRIVATE S16 ueAppEsmHndlIncEsmInfoReq
(
 UeEsmCb *esmCb,
 CmNasEvnt *evnt,
 UeCb *ueCb
)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb   = NULLP;
   UetMessage *tfwMsg = NULLP;
   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   TRC2(ueAppEsmHndlIncEsmInfoReq)

   UE_LOG_DEBUG(ueAppCb, "Esm Information Request");

   /* Update procedure transaction state */
   esmCb->pState = UE_ESM_ST_PROC_TXN_INACTIVE;
   /* send ESM Information Indication to user */
   tfwMsg = (UetMessage*)ueAlloc(sizeof(UetMessage));
   tfwMsg->msg.ueEsmInformationReq.ueId = ueCb->ueId;
   tfwMsg->msgType = UE_ESM_INFORMATION_REQ_TYPE;
   tfwMsg->msg.ueEsmInformationReq.tId = evnt->m.esmEvnt->prTxnId;
   ret = ueSendToTfwApp(tfwMsg, &ueAppCb->fwPst);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Sending Esm Information Request Indication to "\
            "TFWAPP failed");
   }
   RETVALUE(ROK);
} /* ueAppEsmHndlIncEsmInfoReq */


/*
 *
 *       Fun: ueAppEsmHdlIncUeEvnt
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppEsmHdlIncUeEvnt
(
 CmNasEvnt *evnt,
 UeCb *ueCb,
 U8 rcvdAsPiggyBackd
)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   UeEsmCb  *esmCb = NULLP;
   CmEsmMsg *esmMsg = NULLP;
   UetMessage *tfwMsg = NULLP;
   U8 drbId;
   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);
   UE_LOG_DEBUG(ueAppCb, "Handling incoming ESM UE Event");

   if(evnt == NULLP)
   {
      UE_LOG_ERROR(ueAppCb, "Invalid esm event");
      RETVALUE(RFAILED);
   }

   esmMsg = evnt->m.esmEvnt;

   ret = ueAppUtlFndEsmCb(&esmCb, esmMsg->prTxnId, UE_ESM_TRANS_KEY, ueCb);
   if(esmCb == NULLP)
   {
      if(ueCb->numRabs > 0)
      {
         esmCb = ueCb->esmBList[evnt->m.esmEvnt->bearerId];
      }
      if(esmCb == NULLP)
      {
         if (esmMsg->msgType == CM_ESM_MSG_ACTV_DED_BEAR_REQ) {
            ret = ueAppUtlAddEsmCb(&esmCb, ueCb);
         }else {
         UE_LOG_ERROR(ueAppCb, "esmCb not found");
         RETVALUE(RFAILED);
         }
      }
   }

   switch(esmMsg->msgType)
   {
      case CM_ESM_MSG_ACTV_DEF_BEAR_REQ:
         {
            UE_LOG_DEBUG(ueAppCb, "Received CM_ESM_MSG_ACTV_DEF_BEAR_REQ: MSG");
            ret = ueAppEsmHndlIncActDefBearerReq(esmCb, evnt, ueCb, &drbId,
                esmMsg->bearerId);
            CmEsmActDefBearCtxtReq *actReq = &evnt->m.esmEvnt->u.actReq;
           /* send as a standalone esm message:user expecting resonse */
            if((ret == ROK) && (rcvdAsPiggyBackd == FALSE))
            {
               /* send pdn connection response to user */
               tfwMsg = (UetMessage*)ueAlloc(sizeof(UetMessage));
               cmMemset((U8 *)tfwMsg, 0, sizeof(UetMessage));
               tfwMsg->msg.ueUetPdnConRsp.ueId   = ueCb->ueId;
               tfwMsg->msg.ueUetPdnConRsp.status = TRUE;
               tfwMsg->msg.ueUetPdnConRsp.m.pdnInfo.epsBearerId = evnt->m.esmEvnt->bearerId;
               tfwMsg->msgType = UE_PDN_CON_RSP_TYPE;
               if(actReq->apn.len > 0)
               {
                  tfwMsg->msg.ueUetPdnConRsp.m.pdnInfo.\
                     apn.len = actReq->apn.len;
                  cmMemcpy(tfwMsg->msg.ueUetPdnConRsp.m.pdnInfo.apn.apn,
                        actReq->apn.apn,
                        tfwMsg->msg.ueUetPdnConRsp.m.pdnInfo.apn.len);
               }
               if(actReq->pAddr.addrInfo) {
                  tfwMsg->msg.ueUetPdnConRsp.m.pdnInfo.pAddr.pdnType = \
                     actReq->pAddr.pdnType;
                  cmMemcpy(tfwMsg->msg.ueUetPdnConRsp.m.pdnInfo.pAddr.addrInfo,
                        (U8 *)&actReq->pAddr.addrInfo,
                        CM_ESM_MAX_LEN_PDN_ADDRESS);
               }
               if (!ueCb->is_drop_actv_dflt_eps_ber_ctxt_req) {
                 ret = ueSendToTfwApp(tfwMsg, &ueAppCb->fwPst);
               }
                if (ret != ROK)
                {
                   UE_LOG_ERROR(ueAppCb, "Sending PDN Connection Response "\
                         "Indication to TFWAPP Failed");
                }
                if (ueCb->is_actv_dflt_eps_ber_ctxt_rej) {
                  /* send stand-alone activate default bearer reject to mme */
                  ret = ueAppBuildAndSendActDefltBerContextReject(ueCb,
                        esmMsg->bearerId);
                  if (ret != ROK) {
                     UE_LOG_ERROR(ueAppCb, "Sending Activate Default Bearer "\
                         "Context Reject Failed ");
                  }
                  break;
                }
                if (ueCb->is_drop_actv_dflt_eps_ber_ctxt_req) {
                  /* Don't respond to MME with either default bearer reject or
                   * accept to mme */
                  UE_LOG_DEBUG(ueAppCb,
                               "Don't respond to Activate Default Bearer "
                               "Context Request ");
                  break;
                }

               /* send stand-alone activate default bearer accept to mme */
                ret = ueAppBuildAndSendActDefltBerContextAccept(ueCb,
                      ueCb->ueRabCb[drbId-1].epsBearerId);
                if (ret != ROK)
                {
                   UE_LOG_ERROR(ueAppCb, "Sending Activate Default Bearer "\
                         "Context Acccept Failed ");
                }
            }
            break;
         }
      case CM_ESM_MSG_PDN_CONN_REJ:
         {
            UE_LOG_DEBUG(ueAppCb, "Received CM_ESM_MSG_PDN_CONN_REJ: MSG");
            ret = ueAppEsmHndlIncPdnConRej(esmCb, evnt, ueCb);
            break;
         }
      case CM_ESM_MSG_ACTV_DED_BEAR_REQ:
         {
            UE_LOG_DEBUG(ueAppCb, "Received CM_ESM_MSG_ACTV_DED_BEAR_REQ: MSG");
            ret = ueAppEsmHndlIncActDedBearerReq(esmCb, evnt, ueCb,
                  esmMsg->bearerId);
            break;
         }
      case CM_ESM_MSG_DEACTV_BEAR_REQ:
         {
            UE_LOG_DEBUG(ueAppCb, "Received CM_ESM_MSG_DEACTV_BEAR_REQ MSG");
            ret = ueAppEsmHndlIncDeActvBearerReq(esmCb, evnt, ueCb,
                  esmMsg->bearerId);
            break;
         }
      case CM_ESM_MSG_ESM_INFO_REQ:
         {
            UE_LOG_DEBUG(ueAppCb, "Received CM_ESM_MSG_ESM_INFO_REQ: MSG");
            ret = ueAppEsmHndlIncEsmInfoReq(esmCb, evnt, ueCb);
            break;
         }
      case CM_ESM_MSG_PDN_DISCONN_REJ:
         {
            UE_LOG_DEBUG(ueAppCb, "Received CM_ESM_MSG_PDN_DISCONN_REJ: MSG");
            ret = ueAppEsmHndlIncPdnDisconRej(esmCb, evnt, ueCb);
            break;
         }
      default:
         {
            ret = ueAppEsmHndlInvEvnt(esmCb, evnt, ueCb);
            break;
         }
   }
   if(ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Failed to handle esm event");
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* ueAppEsmHdlIncUeEvnt */

/*
 *
 *       Fun:   ueAppEmmHndlInTauAccept
 *
 *       Desc:  Handles incoming TAU Accept message.
 *
 *       Ret:   ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppEmmHndlInTauAccept(CmNasEvnt *evnt, UeCb  *ueCb)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Handling Incoming TAU Accept message");

   /*send message to USER*/
   ret = ueAppRcvEmmMsg(evnt, evnt->m.emmEvnt->msgId, ueCb);
   UE_LOG_EXITFN(ueAppCb, ret);

}

/*
 *
 *       Fun: ueAppEmmHndlInAttachAccept
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppEmmHndlInAttachAccept(CmNasEvnt *evnt, UeCb  *ueCb)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   if(evnt->m.emmEvnt->u.atchAcc.esmEvnt)
   {
      UE_LOG_DEBUG(ueAppCb, "Handling Incoming ACTIVATE Default bearer "\
            "ESM message");
      ret = ueAppEsmHdlIncUeEvnt(evnt->m.emmEvnt->u.atchAcc.esmEvnt, ueCb, TRUE);
      if(ret != ROK)
         RETVALUE(RFAILED);
   }

   UE_LOG_DEBUG(ueAppCb, "Handling Incoming Attach Accept message");
   /*copy GUTI received from CNE in to UE's context*/
   cmMemcpy((U8 *)&ueCb->ueCtxt.ueGuti,
         (U8*)&evnt->m.emmEvnt->u.atchAcc.guti.u.guti, sizeof(GUTI));

   /*send message to USER*/
   ret = ueAppRcvEmmMsg(evnt, evnt->m.emmEvnt->msgId, ueCb);
   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueAppEmmHndlInAttachReject
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppEmmHndlInAttachReject
(
 CmNasEvnt *evnt,
 UeCb *ueCb
)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Handling UE Attach Reject Messsage");

   ret = ueAppRcvEmmMsg(evnt, evnt->m.emmEvnt->msgId, ueCb);

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueAppEmmHndlInTauReject
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppEmmHndlInTauReject(CmNasEvnt *evnt, UeCb *ueCb)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Handling UE Tracking Area Update Reject Messsage");

   ret = ueAppRcvEmmMsg(evnt, evnt->m.emmEvnt->msgId, ueCb);

   UE_LOG_EXITFN(ueAppCb, ret);
}
/*
 *
 *       Fun: ueAppEmmHndlInNwInitDetachReq
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppEmmHndlInNwInitDetachReq(CmNasEvnt *evnt, UeCb *ueCb)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Handling Network initiate detach request Messsage");

   ret = ueAppRcvEmmMsg(evnt, evnt->m.emmEvnt->msgId, ueCb);

   UE_LOG_EXITFN(ueAppCb, ret);
}


/*
 *
 *       Fun:   ueAppEmmHdlIncUeEvnt
 *
 *       Desc:  This function handles incoming events from eNodeB.
 *
 *       Ret:   ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppEmmHdlIncUeEvnt(CmNasEvnt *ueEvnt, UeCb *ueCb)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Handling Incoming Ue Event");

   if (ueEvnt == NULLP)
   {
      UE_LOG_ERROR(ueAppCb, "Invalid esm event");
      RETVALUE(RFAILED);
   }

   switch (ueEvnt->m.emmEvnt->msgId)
   {
      case CM_EMM_MSG_DETACH_ACC:
      {
         UE_LOG_DEBUG(ueAppCb, "Received Detach Accept");
         ret = ueAppEmmHndlInDetachAccept(ueEvnt, ueCb);
         if (ret != ROK)
         {
            UE_LOG_ERROR(ueAppCb, "Handling Detach Accept message failed");
            ret = RFAILED;
         }
         break;
      }
      case CM_EMM_MSG_SVC_REJ:
      {
         UE_LOG_DEBUG(ueAppCb, "Received Service Reject");
         ret = ueAppEmmHndlInServiceRej(ueEvnt, ueCb);
         if (ret != ROK)
         {
            UE_LOG_DEBUG(ueAppCb, "Received Service Reject");
            ret = ueAppEmmHndlInServiceRej(ueEvnt, ueCb);
            if (ret != ROK)
            {
               UE_LOG_ERROR(ueAppCb, "Handling Service Reject message failed");
               ret = RFAILED;
            }
         }
         break;
      }
      case CM_EMM_MSG_ID_REQ:
      {
         UE_LOG_DEBUG(ueAppCb, "Received Identity Request");
         ret = ueAppEmmHndlInIdentReq(ueEvnt, ueCb);
         if (ret != ROK)
         {
            UE_LOG_ERROR(ueAppCb, "Handling Incoming Identity "\
                  "Request message failed");
            ret = RFAILED;
         }
         break;
      }
      case CM_EMM_MSG_AUTH_REQ:
      {
         UE_LOG_DEBUG(ueAppCb, "Received Authentication Request");
         ret = ueAppEmmHndlInAuthReq(ueEvnt, ueCb);
         if (ret != ROK)
         {
            UE_LOG_ERROR(ueAppCb, "Handling Incoming Authentication "\
                  "Request message failed");
            ret = RFAILED;
         }
         break;
      }
      case CM_EMM_MSG_SEC_MODE_CMD:
      {
         UE_LOG_DEBUG(ueAppCb, "Received Security Mode Command");
         ret = ueAppEmmHndlInSecModecmd(ueEvnt, ueCb);
         if (ret != ROK)
         {
            UE_LOG_ERROR(ueAppCb, "Handling Incoming SEC MODE CMD failed");
            ret = RFAILED;
         }
         break;
      }
      case CM_EMM_MSG_ATTACH_ACC:
      {
         UE_LOG_DEBUG(ueAppCb, "Received Attach Accept message");
         ret = ueAppEmmHndlInAttachAccept(ueEvnt, ueCb);
         break;
      }
      case CM_EMM_MSG_TAU_ACC:
      {
         UE_LOG_DEBUG(ueAppCb, "Received TAU Accept message");
         ret = ueAppEmmHndlInTauAccept(ueEvnt, ueCb);
         break;
      }
      case CM_EMM_MSG_ATTACH_REJ:
      {
         UE_LOG_DEBUG(ueAppCb, "Received Attach Reject message");
         ret = ueAppEmmHndlInAttachReject(ueEvnt, ueCb);
         /*Handling the attach Reject*/
         break;
      }
      case CM_EMM_MSG_TAU_REJ:
      {
         UE_LOG_DEBUG(ueAppCb, "Received Tracking Area update Reject message");
         ret = ueAppEmmHndlInTauReject(ueEvnt, ueCb);
         break;
      }
      case CM_EMM_MSG_DETACH_REQ:
      {
         UE_LOG_DEBUG(ueAppCb, "Received Detach request message");
         ret = ueAppEmmHndlInNwInitDetachReq(ueEvnt, ueCb);
         break;
      }
      case CM_EMM_MSG_EMM_INFO:
      {
         UE_LOG_DEBUG(ueAppCb, "Received EMM Information message");
         ret = ueAppEmmHndlInEmmInformation(ueEvnt, ueCb);
         break;
      }
      case CM_EMM_MSG_AUTH_REJ:
      {
         UE_LOG_DEBUG(ueAppCb, "Received Auth Reject message");
         ret = ueAppEmmHndlInAuthReject(ueEvnt, ueCb);
         break;
      }
      default:
      {
         UE_LOG_ERROR(ueAppCb, "Invalid message ESM  message\n");
         CM_FREE_NASEVNT(&ueEvnt);
         RETVALUE(RFAILED);
      }
   }

   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "handling failed for ESM message\n");
      CM_FREE_NASEVNT(&ueEvnt);
      ret = RFAILED;
   }

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun:   ueUiProcessNbMsg
 *
 *       Desc:  This function processes DL messages received from eNodeB.
 *
 *       Ret:   ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PUBLIC S16 ueUiProcessNbMsg(NbuDlNasMsg *pNbDlMsg, Pst *pst)
{
   S16 ret = ROK;
   U32 ueId;
   UeAppCb *ueAppCb = NULLP;
   UeCb *ueCb = NULLP;
   UeAppMsg     srcMsg;
   UeAppMsg     dstMsg;
   NhuDedicatedInfoNAS *nasPdu = NULLP;
   NhuDedicatedInfoNAS nasMsg;
   CmNasEvnt   *ueEvnt = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Received Downlink Message from ENODEB");

   ueId = pNbDlMsg->ueId;
   /* Fetching the UeCb */
   ret = ueDbmFetchUe(ueId,(PTR *)&ueCb);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "UeCb List NULL ueId = %d", ueId);
      RETVALUE(ret);
   }

   nasPdu = &pNbDlMsg->nasPdu;
   /* Decoding the PDU */
   ret = ueAppEdmDecode(nasPdu, &ueEvnt);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "NAS pdu decoding failed");
      ret = RFAILED;
      RETVALUE(ret);
   }

   if (ueEvnt == NULL)
   {
      UE_LOG_ERROR(ueAppCb, "ueEvnt is NULL");
      RETVALUE(RFAILED);
   }

   if ((CM_NAS_SEC_HDR_TYPE_INT_PRTD_ENC == ueEvnt->secHT) ||
       (CM_NAS_SEC_HDR_TYPE_INT_PRTD_ENC_NEW_SEC_CTXT == ueEvnt->secHT))
   {
      srcMsg.val = nasPdu->val;
      srcMsg.len = nasPdu->len;
      ret = ueAppVldDwnlnkSec(&ueCb->secCtxt, &srcMsg, &dstMsg);
      if (ROK != ret)
      {
         UE_LOG_ERROR(ueAppCb, "Downlink security validation failed");
         /*Ignore the event*/
         ueEvnt->pdu = NULLP;
         CM_FREE_NASEVNT(&ueEvnt);
         RETVALUE(RFAILED);
      }

      cmMemcpy((U8 *)&nasMsg, (CONSTANT U8 *)nasPdu,
               sizeof(NhuDedicatedInfoNAS));
      nasMsg.val = dstMsg.val;
      nasMsg.len = dstMsg.len;
      ret = ueAppEdmDecode(&nasMsg, &ueEvnt);
      if (ROK != ret || ueEvnt == NULLP)
      {
         UE_LOG_ERROR(ueAppCb, "Downlink NAS message decoding failed");
         RETVALUE(ret); /* Should we send Failure back to eNB */
      }
   }

   /* Handle the incoming events */
   if(ueEvnt->protDisc == CM_EMM_PD)
   {
      ret = ueAppEmmHdlIncUeEvnt(ueEvnt, ueCb);
   }
   else if(ueEvnt->protDisc == CM_ESM_PD)
   {
      ueAppEsmHdlIncUeEvnt(ueEvnt, ueCb,FALSE);
   }
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Handling Initial UE Event failed");
      ret = RFAILED;
   }

   if(CM_NAS_SEC_HDR_TYPE_INT_PRTD_NEW_SEC_CTXT == ueEvnt->secHT)
   {
      srcMsg.val = nasPdu->val;
      srcMsg.len = nasPdu->len;
      ret = ueAppVldDwnlnkSec(&ueCb->secCtxt, &srcMsg, &dstMsg);

   }

   CM_FREE_NASEVNT(&ueEvnt);
   UE_LOG_EXITFN(ueAppCb, ret);
}

#if 0
PRIVATE S16 handleUeCntxtRcvdIndFromEnb
(
  UeCb *ueCb,
  U8   bearerId
)
{
   S16 ret = ROK;
   U8 ipAddrStr[20] = {0};
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   /*Change the Ue ESM state to Connected mode */
   ueCb->ecmCb.state = UE_ECM_CONNECTED;

/*sharad: need tp move to new api for sending ip address */
   /* Populate Ip Address in string format */
   populateIpAddrStrFromUeCb(ipAddrStr,ueCb,bearerId);

   /* Sending the UE IP Address to enbapp */
   ret = ueAppBldAndSndIpAddrToNb(ueCb->ueId, ipAddrStr, &ueAppCb->nbPst);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Failed");
      ret = RFAILED;
   }
   UE_LOG_EXITFN(ueAppCb, ret);
}
#endif

/*
 *
 *       Fun: ueUiProcPagingMsg
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PUBLIC S16 ueUiProcPagingMsg(UePagingMsg *p_ueMsg, Pst *pst)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   UeCb *ueCb = NULLP;

   UE_GET_CB(ueAppCb);

   UE_LOG_ENTERFN(ueAppCb);
   UE_LOG_DEBUG(ueAppCb, "Received Paging from ENODEB");
   /* Fetching the UeCb */
   ret = ueDbmFetchUeWithS_TMSI(p_ueMsg, (PTR *)&ueCb);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "UeCb List NULL ueId = %d",ueCb->ueId);
      RETVALUE(ret);
   }
   ret = ueUiBldAndSendPagingInfo(ueCb, p_ueMsg);
   if(ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Failed to handle Init Context Message With "\
            "No NAS PDU");
      RETVALUE(ret);
   }
   RETVALUE(ROK);
}

PRIVATE S16 ueUiBldAndSendPagingInfo(UeCb *ueCb, UePagingMsg *p_ueMsg)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;
   UetMessage *tfwMsg = NULLP;

   UE_GET_CB(ueAppCb);

   UE_LOG_ENTERFN(ueAppCb);
   tfwMsg = (UetMessage*)ueAlloc(sizeof(UetMessage));

   tfwMsg->msgType = UE_PAGING_MSG_TYPE;
   tfwMsg->msg.ueUetPagingMsg.ueId = ueCb->ueId;
   tfwMsg->msg.ueUetPagingMsg.domainType = p_ueMsg->domIndType;
   ret = ueSendToTfwApp(tfwMsg, &ueAppCb->fwPst);
   RETVALUE(ret);
}

PUBLIC S16 ueUiProcErabsRelInfoMsg(Pst *pst, NbuErabsRelInfo *pNbuErabsRelInfo)
{
   int i = 0;
   S16 ret = ROK;
   U32 ueId;
   UeAppCb *ueAppCb = NULLP;
   UeAppMsg     srcMsg;
   UeAppMsg     dstMsg;
   UeCb *ueCb = NULLP;
   NhuDedicatedInfoNAS *nasPdu = NULLP;
   NhuDedicatedInfoNAS nasMsg;
   CmNasEvnt   *ueEvnt = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);
   UE_LOG_DEBUG(ueAppCb, "Received Downlink Message from ENODEB");

   ueId = pNbuErabsRelInfo->ueId;
   UE_LOG_DEBUG(ueAppCb, "Received Downlink Message from ENODEB with ue id %d\n",ueId);
   /* Fetching the UeCb */
   ret = ueDbmFetchUe(ueId, (PTR *)&ueCb);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "UeCb List NULL ueId = %d", ueId);
      RETVALUE(ret);
   }
   nasPdu = &pNbuErabsRelInfo->nasPdu;
   /* Decoding the PDU */
   ret = ueAppEdmDecode(nasPdu, &ueEvnt);
   if (ret != ROK)
   {
     UE_LOG_ERROR(ueAppCb, "NAS pdu decoding failed");
     ret = RFAILED;
     RETVALUE(ret);
   }
   if (ueEvnt == NULLP)
   {
     UE_LOG_ERROR(ueAppCb, "ueEvnt is NULL");
     RETVALUE(RFAILED);
   }
   if ((CM_NAS_SEC_HDR_TYPE_INT_PRTD_ENC == ueEvnt->secHT) ||
           (CM_NAS_SEC_HDR_TYPE_INT_PRTD_ENC_NEW_SEC_CTXT == ueEvnt->secHT))
   {
     srcMsg.val = nasPdu->val;
     srcMsg.len = nasPdu->len;
     ret = ueAppVldDwnlnkSec(&ueCb->secCtxt, &srcMsg, &dstMsg);
     if(ROK != ret)
     {
             UE_LOG_ERROR(ueAppCb, "Uplink security validation failed \n");
             /*Ignore the event*/
             ueEvnt->pdu = NULLP;
             CM_FREE_NASEVNT(&ueEvnt);
             RETVALUE(RFAILED);
     }

     cmMemcpy((U8 *)&nasMsg, (CONSTANT U8 *)nasPdu,
          	   sizeof(NhuDedicatedInfoNAS));
     nasMsg.val = dstMsg.val;
     nasMsg.len = dstMsg.len;
     ret = ueAppEdmDecode(&nasMsg, &ueEvnt);
     if (ROK != ret)
     {
             UE_LOG_ERROR(ueAppCb, "Uplink NAS message decode failed\n");
             RETVALUE(ret); /* Should we send Failure back to eNB */
     }
     if (ueEvnt == NULLP)
     {
             UE_LOG_ERROR(ueAppCb, "ueEvnt is NULL");
             RETVALUE(RFAILED);
     }
   }

   /* Handle the incoming events */
   if(ueEvnt->protDisc == CM_EMM_PD)
   {
     ret = ueAppEmmHdlIncUeEvnt(ueEvnt, ueCb);
   }
   else if(ueEvnt->protDisc == CM_ESM_PD)
   {
     ret = ueAppEsmHdlIncUeEvnt(ueEvnt, ueCb,FALSE);
   }
   if (ret != ROK)
   {
     UE_LOG_ERROR(ueAppCb, "Handling Initial UE Event failed");
     ret = RFAILED;
   }

   ueFree((U8*)nasPdu->val, nasPdu->len * sizeof(U8));
   CM_FREE_NASEVNT(&ueEvnt);


   UE_LOG_EXITFN(ueAppCb, ret);
}

PUBLIC S16 ueUiProcErabsInfoMsg(Pst *pst, NbuErabsInfo *pNbuErabsInfo)
{
   int idx = 0;
   S16 ret = ROK;
   U32 ueId;
   UeAppCb *ueAppCb = NULLP;
   UeAppMsg     srcMsg;
   UeAppMsg     dstMsg;
   UeCb *ueCb = NULLP;
   NhuDedicatedInfoNAS *nasPdu = NULLP;
   NhuDedicatedInfoNAS nasMsg;
   CmNasEvnt   *ueEvnt = NULLP;

   UE_GET_CB(ueAppCb);

   UE_LOG_ENTERFN(ueAppCb);
   UE_LOG_DEBUG(ueAppCb, "Received Downlink Message from ENODEB");

   ueId = pNbuErabsInfo->ueId;
   /* Fetching the UeCb */
   ret = ueDbmFetchUe(ueId, (PTR *)&ueCb);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "UeCb List NULL ueId = %d", ueId);
      RETVALUE(ret);
   }

   if (pNbuErabsInfo->ueRadCapRcvd == FALSE)
   {
     ret = ueSendUeRadCapInd(ueCb);
   }
   if (pNbuErabsInfo->erabInfo) {
     for (idx = 0; idx < pNbuErabsInfo->erabInfo->numOfErab; idx++) {
       nasPdu = &pNbuErabsInfo->erabInfo->rabCbs[idx].nasPdu;
       if (nasPdu->val) {
         /* Decoding the PDU */
         ret = ueAppEdmDecode(nasPdu, &ueEvnt);
         if (ret != ROK) {
           UE_LOG_ERROR(ueAppCb, "NAS pdu decoding failed");
           RETVALUE(ret);
         }
         if (ueEvnt == NULLP) {
           UE_LOG_ERROR(ueAppCb, "ueEvnt is NULL");
           RETVALUE(RFAILED);
         }
         if ((CM_NAS_SEC_HDR_TYPE_INT_PRTD_ENC == ueEvnt->secHT) ||
             (CM_NAS_SEC_HDR_TYPE_INT_PRTD_ENC_NEW_SEC_CTXT == ueEvnt->secHT)) {
           srcMsg.val = nasPdu->val;
           srcMsg.len = nasPdu->len;
           ret = ueAppVldDwnlnkSec(&ueCb->secCtxt, &srcMsg, &dstMsg);
           if (ROK != ret) {
             UE_LOG_ERROR(ueAppCb, "Uplink security validation failed \n");
             /*Ignore the event*/
             ueEvnt->pdu = NULLP;
             CM_FREE_NASEVNT(&ueEvnt);
             RETVALUE(RFAILED);
           }

           cmMemcpy((U8 *)&nasMsg, (CONSTANT U8 *)nasPdu,
                    sizeof(NhuDedicatedInfoNAS));
           nasMsg.val = dstMsg.val;
           nasMsg.len = dstMsg.len;
           ret = ueAppEdmDecode(&nasMsg, &ueEvnt);
           if (ROK != ret) {
             UE_LOG_ERROR(ueAppCb, "Uplink NAS message decode failed\n");
             RETVALUE(ret); /* Should we send Failure back to eNB */
           }
           if (ueEvnt == NULLP) {
             UE_LOG_ERROR(ueAppCb, "ueEvnt is NULL");
             RETVALUE(RFAILED);
           }
         }

         /* Handle the incoming events */
         if (ueEvnt->protDisc == CM_EMM_PD) {
           ret = ueAppEmmHdlIncUeEvnt(ueEvnt, ueCb);
         } else if (ueEvnt->protDisc == CM_ESM_PD) {
           ret = ueAppEsmHdlIncUeEvnt(ueEvnt, ueCb, FALSE);
         }
         if (ret != ROK) {
           UE_LOG_ERROR(ueAppCb, "Handling Initial UE Event failed");
           ret = RFAILED;
         }

         ueFree((U8 *)nasPdu->val, nasPdu->len * sizeof(U8));
         CM_FREE_NASEVNT(&ueEvnt);
       }
     }
   }
   if (pNbuErabsInfo->failedErabList &&
       pNbuErabsInfo->failedErabList->noOfFailedErabs > 0) {
     UE_LOG_DEBUG(ueAppCb, "Send E_RAB_SETUP_REQ failed for some bearers \n");
     ueSendErabSetupRspForFailedBearers(pNbuErabsInfo);
   }
   UE_LOG_EXITFN(ueAppCb, ret);
}

// This function handles ipv6 address allocation failure
PRIVATE S16 ueUihandleIpInfoUpdtFail(UeCb *ueCb, NbuUeIpInfoUpdt *ipInfoUpdt,
                                     uint32_t idx) {
  UeAppCb *ueAppCb = NULLP;
  UE_GET_CB(ueAppCb);
  UE_LOG_ENTERFN(ueAppCb);

  /* 1.If the pdn type is IPv6 and this is a secondary pdn, delete the session
   * 2.If the pdn type is IPv6 and this is the default pdn, initiate detach
   * 3.If the pdn type is IPv4v6, do nothing
   */
  if (ueCb->ueRabCb[idx].pAddr.pdnType == CM_ESM_PDN_IPV6) {
    if (ueCb->numPdns == 1) {
      // Initiate detach
      if (ueSendDetachRequest(ueCb, UE_DETACH_SWITCHOFF) == ROK) {
        UE_LOG_DEBUG(ueAppCb, "Sending Detach Request for ueId: %d",
                     ueCb->ueId);
        UE_LOG_DEBUG(ueAppCb, "Freeing all the DRBs allocated for ueId: %d",
                     ueCb->ueId);
        for (U8 itr = 0; itr < UE_APP_MAX_DRBS; itr++) {
          cmMemset((U8 *)&(ueCb->ueRabCb[itr]), 0, sizeof(ueCb->ueRabCb[itr]));
          ueCb->drbs[itr] = UE_APP_DRB_AVAILABLE;
          ueCb->numRabs--;
        }
      } else {
        UE_LOG_ERROR(ueAppCb,
                     " Error in sending Detach Req for bearer %u, ue %u\n",
                     ipInfoUpdt->bearerId, ueCb->ueId);
        RETVALUE(RFAILED);
      }
    } else if (ueCb->numPdns > 1) {
      // Send PDN disconnect
      UetMessage uetMsg;
      uetMsg.msg.ueUetPdnDisconnectReq.ueId = ueCb->ueId;
      uetMsg.msg.ueUetPdnDisconnectReq.bearerId = ipInfoUpdt->bearerId;
      if (ueProcUePdnDisconnectReq(&uetMsg, NULLP) == ROK) {
        UE_LOG_DEBUG(ueAppCb, "Pdn Disconnect Req for ueId: %d, bearer %u",
                     ueCb->ueId, ipInfoUpdt->bearerId);
      } else {
        UE_LOG_ERROR(
            ueAppCb,
            " Error in sending Pdn Disconnect Req for bearer %u, ue %u\n",
            ipInfoUpdt->bearerId, ueCb->ueId);
        RETVALUE(RFAILED);
      }
    }
  }
  RETVALUE(ROK);
}

PUBLIC S16 ueUiProcIpInfoUpdtMsg(UeCb *ueCb, NbuUeIpInfoUpdt *ipInfoUpdt) {
  UeAppCb *ueAppCb = NULLP;
  UetMessage *tfwMsg = NULLP;
  S16 retVal = RFAILED;
  uint32_t idx;
  Bool bearerFound = FALSE;
  UE_GET_CB(ueAppCb);
  UE_LOG_ENTERFN(ueAppCb);

  for (idx = 0; idx < UE_APP_MAX_DRBS; idx++) {
    if (ueCb->ueRabCb[idx].epsBearerId == ipInfoUpdt->bearerId) {
      bearerFound = TRUE;
      break;
    }
  }
  if (!bearerFound) {
    UE_LOG_ERROR(ueAppCb, "Bearer id %u not found in ueRabCb for ue %u\n",
                 ipInfoUpdt->bearerId, ueCb->ueId);
    RETVALUE(RFAILED);
  }

  if (ipInfoUpdt->status == FAILURE) {
    retVal = ueUihandleIpInfoUpdtFail(ueCb, ipInfoUpdt, idx);
    RETVALUE(retVal);
  }
  // Update the IPv6 address to ueAppCb
  cmMemcpy(ueCb->ueRabCb[idx].ipv6Addr, ipInfoUpdt->ipv6Addr,
           sizeof(ipInfoUpdt->ipv6Addr));
  // Send message to Test controller
  tfwMsg = (UetMessage *)ueAlloc(sizeof(UetMessage));
  tfwMsg->msg.ueUetRouterAdv.ueId = ueCb->ueId;
  tfwMsg->msg.ueUetRouterAdv.bearerId = ipInfoUpdt->bearerId;
  cmMemcpy(tfwMsg->msg.ueUetRouterAdv.ipv6Addr, ipInfoUpdt->ipv6Addr,
           sizeof(ipInfoUpdt->ipv6Addr));
  tfwMsg->msgType = UE_ICMPV6_ROUTER_ADV_TYPE;
  if (ueSendToTfwApp(tfwMsg, &ueAppCb->fwPst) != ROK) {
    UE_LOG_ERROR(ueAppCb, "Sending ICMPV6 ROUTER ADVERTISEMENT to "
                          "TFWAPP failed");
    RETVALUE(RFAILED);
  }
  UE_LOG_DEBUG(
      ueAppCb,
      "Sent ICMPV6 ROUTER ADVERTISEMENT to tfwApp for ue %d bearer %d\n",
      ueCb->ueId, ipInfoUpdt->bearerId);
  RETVALUE(ROK);
}

PUBLIC S16 ueUiProcIpInfoReqMsg(UeCb *p_ueCb, U8 bearerId) {
  UeAppCb *ueAppCb = NULLP;
  UE_GET_CB(ueAppCb);
  UE_LOG_ENTERFN(ueAppCb);

  p_ueCb->ecmCb.state = UE_ECM_CONNECTED;
  /* enbApp creates a tunnel after receiving IpInfoRsp message.
   * If is_actv_dflt_eps_ber_ctxt_rej flag is set, send IpInfoRej
   * message so that enbApp does not create a tunnel for this bearer
   */
  if (p_ueCb->is_actv_dflt_eps_ber_ctxt_rej) {
    p_ueCb->is_actv_dflt_eps_ber_ctxt_rej = FALSE;
    UE_LOG_DEBUG(ueAppCb, "Sending IpInfoRej message as "
                          "is_actv_dflt_eps_ber_ctxt_rej flag is set \n");
    ueAppBldAndSndIpInfoRejToNb(p_ueCb, bearerId, &ueAppCb->nbPst);
    RETVALUE(ROK);
  }
  ueAppBldAndSndIpInfoRspToNb(p_ueCb, bearerId, &ueAppCb->nbPst);
  RETVALUE(ROK);
}

/*
 *
 *       Fun: ueProcUeBearResAllocReq
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueProcUeBearResAllocReq
(
 UetMessage *p_ueMsg,
 Pst *pst
)
{
   CmNasEvnt           *reqEvnt = NULLP;
   U32 ueId;
   U8                   isPlainMsg   = TRUE;
   UeCb *ueCb = NULLP;
   S16 ret;
   NhuDedicatedInfoNAS nasEncPdu;
   NbuUlNasMsg *nbUeBearResAllocReq = NULLP;
   UeAppCb *ueAppCb;
   UeAppMsg             srcMsg;
   UeAppMsg             dstMsg;

   UE_GET_CB(ueAppCb);

   UE_LOG_ENTERFN(ueAppCb);
   UE_LOG_DEBUG(ueAppCb, "Received UE RESOURCE ALLOCATION REQ FROM TFW");

   ueId = p_ueMsg->msg.ueBearerAllocReq.ueId;
   /* Fetching the UeCb */
   ret = ueDbmFetchUe(ueId, (PTR *)&ueCb);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "UeCb List NULL ueId = %d", ueId);
      RETVALUE(ret);
   }

   ret = ueAppUtlBldBearerResAllocReq(&reqEvnt,
         &p_ueMsg->msg.ueBearerAllocReq);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Building Bearer Resource Allocation Request failed");
      RETVALUE(ret);
   }

   if ((ret = ueAppEsmHdlOutUeEvnt(reqEvnt,ueCb))!= ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Handling Bearer Resource Allocation Request failed  \n");
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&nasEncPdu, 0, sizeof(NhuDedicatedInfoNAS));

   /* Encode the PDU */
   ret = ueAppEdmEncode(reqEvnt, &nasEncPdu);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Bearer Resource Allocation Request Encode Failed");
      CM_FREE_NASEVNT(&reqEvnt);
      RETVALUE(ret);
   }
   /** Integrity Protected **/
   if (CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG != reqEvnt->secHT)
   {
      isPlainMsg = FALSE;
      srcMsg.val = nasEncPdu.val;
      srcMsg.len = nasEncPdu.len;
      ret = ueAppCmpUplnkSec(&ueCb->secCtxt, reqEvnt->secHT, &srcMsg,
                             &dstMsg);
      if (ROK != ret)
      {
         UE_LOG_ERROR(ueAppCb, "Uplink Security Failed");
         EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
         reqEvnt->pdu = NULLP;
         CM_FREE_NASEVNT(&reqEvnt);
         RETVALUE(ret);
      }
      EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
      nasEncPdu.val = dstMsg.val;
      nasEncPdu.len = dstMsg.len;
   }
   CM_FREE_NASEVNT(&reqEvnt);

   nbUeBearResAllocReq = (NbuUlNasMsg *)ueAlloc(sizeof(NbuUlNasMsg));
   nbUeBearResAllocReq->ueId = ueId;
   nbUeBearResAllocReq->nasPdu.pres = TRUE;
   nbUeBearResAllocReq->nasPdu.len = nasEncPdu.len;
   nbUeBearResAllocReq->nasPdu.val = (U8 *)ueAlloc(nbUeBearResAllocReq->nasPdu.len);
   cmMemcpy((U8 *)nbUeBearResAllocReq->nasPdu.val, nasEncPdu.val,
         nbUeBearResAllocReq->nasPdu.len);

   if (isPlainMsg)
   {
   EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
   }

   ret = ueSendUlNasMsgToNb(nbUeBearResAllocReq, &ueAppCb->nbPst);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Sending Bearer Resource Allocation Req to enbAPP failed");
      ret = RFAILED;
   }

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueProcUeDeActvBerAcc
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueProcUeDeActvBerAcc
(
 UetMessage *p_ueMsg,
 Pst *pst
)
{
   U32 ueId;
   UeCb *ueCb = NULLP;
   S16 ret;
   UeAppCb *ueAppCb;

   UE_GET_CB(ueAppCb);

   UE_LOG_ENTERFN(ueAppCb);
   UE_LOG_DEBUG(ueAppCb, "Received UE De Activate Bearer Acc FROM TFW");
   ueId = p_ueMsg->msg.ueDeActvBerAcc.ueId;
   /* Fetching the UeCb */
   ret = ueDbmFetchUe(ueId, (PTR *)&ueCb);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "UeCb List NULL ueId = %d", ueId);
      RETVALUE(ret);
   }
   ret = ueAppBuildAndSendDeActvBerContextAccept(ueCb,p_ueMsg->msg.ueDeActvBerAcc.bearerId);
   if (ret != ROK)
   {
      RETVALUE(ret);
   }
   RETVALUE(ret);
}
/*
 *
 *       Fun: ueProcUeActvDedBerAcc
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueProcUeActvDedBerAcc
(
 UetMessage *p_ueMsg,
 Pst *pst
)
{
   U32 ueId;
   UeCb *ueCb = NULLP;
   S16 ret;
   UeAppCb *ueAppCb;

   UE_GET_CB(ueAppCb);

   UE_LOG_ENTERFN(ueAppCb);
   UE_LOG_DEBUG(ueAppCb, "Received UE Activate Dedicated Bearer Acc FROM TFW");

   ueId = p_ueMsg->msg.ueActDedBerAcc.ueId;
   /* Fetching the UeCb */
   ret = ueDbmFetchUe(ueId, (PTR *)&ueCb);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "UeCb List NULL ueId = %d", ueId);
      RETVALUE(ret);
   }
   ret = ueAppBuildAndSendActDedBerContextAccept(ueCb,p_ueMsg->msg.ueActDedBerAcc.bearerId);
   if (ret != ROK)
   {
      RETVALUE(ret);
   }
   RETVALUE(ret);
}

/*
 *
 *       Fun: ueProcUeActvDedBerRej
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueProcUeActvDedBerRej
(
 UetMessage *p_ueMsg,
 Pst *pst
)
{
   U32 ueId;
   U8  bearerId;
   U8 esmCause;
   UeCb *ueCb = NULLP;
   S16 ret;
   UeAppCb *ueAppCb;

   UE_GET_CB(ueAppCb);

   UE_LOG_ENTERFN(ueAppCb);
   UE_LOG_DEBUG(ueAppCb, "Received UE Activate Dedicated Bearer Rej FROM TFW");

   ueId = p_ueMsg->msg.ueActDedBerRej.ueId;
   /* Fetching the UeCb */
   ret = ueDbmFetchUe(ueId, (PTR *)&ueCb);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "UeCb List NULL ueId = %d", ueId);
      RETVALUE(ret);
   }
   bearerId = p_ueMsg->msg.ueActDedBerRej.bearerId;
   esmCause = p_ueMsg->msg.ueActDedBerRej.esmCause;
   ret = ueAppBuildAndSendActDedBerContextReject(ueCb,bearerId,esmCause);
   if (ret != ROK)
   {
      RETVALUE(ret);
   }
   RETVALUE(ret);
}

PRIVATE S16 ueAppUtlBldBearerResAllocReq
(
 CmNasEvnt **esmEvnt,
 UeUetBearerAllocReq *bearAllocReq
)
{
   U8 idx;
   CmEsmMsg    *msg = NULLP;
   printf("Building Bearer Resource Allocation Request for Ue\n");

   if(esmEvnt == NULLP)
   {
      RETVALUE(RFAILED);
   }

   /* Allocate memory for mme evnt */
   CM_ALLOC_NASEVNT (esmEvnt, CM_ESM_PD);
   if (*esmEvnt == NULLP)
   {
      RETVALUE(RFAILED);
   }

   /*Allocate memory for ESM message*/
   if (cmGetMem(&(*esmEvnt)->memCp, sizeof(CmEsmMsg), (Ptr *)&msg) != ROK)
   {
      CM_FREE_NASEVNT(esmEvnt);
      RETVALUE(RFAILED);
   }

   msg->protDisc = CM_ESM_PD;
   (*esmEvnt)->m.esmEvnt = msg;

   (*esmEvnt)->secHT = CM_NAS_SEC_HDR_TYPE_INT_PRTD_ENC;
   /* Fill ESM  Bearer Resource Allocation  request message */

   /*Fill mandatory IE's*/
   /* EPS barer ID IE*/
   msg->bearerId = bearAllocReq->bearerId;
   /* Linked EPS Bearer Id */
   msg->u.bearAllocReq.lnkBearerId = bearAllocReq->lnkEpsBearerId;

   /* Bearer Resource Allocation request message identity*/
   msg->msgType  = CM_ESM_MSG_BEAR_RES_ALLOC_REQ;

   msg->u.bearAllocReq.epsQos.pres = bearAllocReq->epsQos.pres;
   if(msg->u.bearAllocReq.epsQos.pres == TRUE)
   {
      msg->u.bearAllocReq.epsQos.lenQosCont   = bearAllocReq->epsQos.lenQosCont;
      msg->u.bearAllocReq.epsQos.maxBitRateUL = bearAllocReq->epsQos.maxBitRateUL;
      msg->u.bearAllocReq.epsQos.maxBitRateDL = bearAllocReq->epsQos.maxBitRateDL;
      msg->u.bearAllocReq.epsQos.guaraBitRateUL = bearAllocReq->epsQos.guaraBitRateUL;
      msg->u.bearAllocReq.epsQos.guaraBitRateDL = bearAllocReq->epsQos.guaraBitRateDL;
   }

   msg->u.bearAllocReq.tft.pres = bearAllocReq->tft.pres;
   if(msg->u.bearAllocReq.tft.pres == TRUE)
   {
      msg->u.bearAllocReq.tft.pres       = bearAllocReq->tft.pres;
      msg->u.bearAllocReq.tft.len        = bearAllocReq->tft.len;
      msg->u.bearAllocReq.tft.opCode     = bearAllocReq->tft.opCode;
      msg->u.bearAllocReq.tft.noOfPfs    = bearAllocReq->tft.noOfPfs;
      msg->u.bearAllocReq.tft.eBit       = bearAllocReq->tft.eBit;
      msg->u.bearAllocReq.tft.noOfParams = bearAllocReq->tft.noOfParams;

      msg->u.bearAllocReq.tft.noOfPfs  =  bearAllocReq->tft.noOfPfs;
      for( idx = 0 ; idx < msg->u.bearAllocReq.tft.noOfPfs ; idx++)
      {
         msg->u.bearAllocReq.tft.pfList[idx].pres = TRUE;
         msg->u.bearAllocReq.tft.pfList[idx].id =    bearAllocReq->tft.pfList[idx].id;
         msg->u.bearAllocReq.tft.pfList[idx].dir =   bearAllocReq->tft.pfList[idx].dir;
         msg->u.bearAllocReq.tft.pfList[idx].preced = bearAllocReq->tft.pfList[idx].preced;
         msg->u.bearAllocReq.tft.pfList[idx].len =   bearAllocReq->tft.pfList[idx].len;
         if(bearAllocReq->tft.pfList[idx].ipv4.pres)
         {
            msg->u.bearAllocReq.tft.pfList[idx].ipv4.pres =\
                                                           bearAllocReq->tft.pfList[idx].ipv4.pres;
            cmMemcpy((U8 *)&msg->u.bearAllocReq.tft.pfList[idx].ipv4.ip4, \
                  (U8 *)bearAllocReq->tft.pfList[idx].ipv4.ip4,CM_ESM_IPV4_SIZE);
            msg->u.bearAllocReq.tft.pfList[idx].ipv4Mask =\
                                                          bearAllocReq->tft.pfList[idx].ipv4Mask;
         }
         if(bearAllocReq->tft.pfList[idx].ipv6.pres)
         {
            msg->u.bearAllocReq.tft.pfList[idx].ipv6.pres =\
               bearAllocReq->tft.pfList[idx].ipv6.pres;
            cmMemcpy((U8 *)&msg->u.bearAllocReq.tft.pfList[idx].ipv6.ip6, \
               (U8 *)bearAllocReq->tft.pfList[idx].ipv6.ip6,CM_ESM_IPV6_SIZE);
         }
         if(msg->u.bearAllocReq.tft.pfList[idx].protId.pres)
         {
            msg->u.bearAllocReq.tft.pfList[idx].protId.pres     =\
               bearAllocReq->tft.pfList[idx].protId.pres;
            msg->u.bearAllocReq.tft.pfList[idx].protId.protType =\
               bearAllocReq->tft.pfList[idx].protId.protType;
         }
         if(bearAllocReq->tft.pfList[idx].localPort.pres)
         {
            msg->u.bearAllocReq.tft.pfList[idx].localPort.pres  =\
               bearAllocReq->tft.pfList[idx].localPort.pres;
            msg->u.bearAllocReq.tft.pfList[idx].localPort.port  =\
               bearAllocReq->tft.pfList[idx].localPort.port;
         }
         if(bearAllocReq->tft.pfList[idx].remotePort.pres)
         {
            msg->u.bearAllocReq.tft.pfList[idx].remotePort.pres =\
               bearAllocReq->tft.pfList[idx].remotePort.pres;
         msg->u.bearAllocReq.tft.pfList[idx].remotePort.port =\
                bearAllocReq->tft.pfList[idx].remotePort.port;
         }
         if(bearAllocReq->tft.pfList[idx].locPortRange.pres)
         {
            msg->u.bearAllocReq.tft.pfList[idx].locPortRange.pres = \
                bearAllocReq->tft.pfList[idx].locPortRange.pres;
         msg->u.bearAllocReq.tft.pfList[idx].locPortRange.rangeLow = \
            bearAllocReq->tft.pfList[idx].locPortRange.rangeLow;
         msg->u.bearAllocReq.tft.pfList[idx].locPortRange.rangeHigh =  \
            bearAllocReq->tft.pfList[idx].locPortRange.rangeHigh;
         }
         if(bearAllocReq->tft.pfList[idx].remPortRange.pres)
         {
            msg->u.bearAllocReq.tft.pfList[idx].remPortRange.pres = \
               bearAllocReq->tft.pfList[idx].remPortRange.pres;
            msg->u.bearAllocReq.tft.pfList[idx].remPortRange.rangeLow = \
               bearAllocReq->tft.pfList[idx].remPortRange.rangeLow;
            msg->u.bearAllocReq.tft.pfList[idx].remPortRange.rangeHigh =  \
               bearAllocReq->tft.pfList[idx].remPortRange.rangeHigh;
         }
         if(msg->u.bearAllocReq.tft.pfList[idx].secParam.pres)
         {
            msg->u.bearAllocReq.tft.pfList[idx].secParam.pres = \
               bearAllocReq->tft.pfList[idx].secParam.pres;
            cmMemcpy((U8 *)&msg->u.bearAllocReq.tft.pfList[idx].secParam.params, \
               (U8 *)bearAllocReq->tft.pfList[idx].secParam.params, CM_ESM_IP_SEC_SIZE);
         }
         if(bearAllocReq->tft.pfList[idx].tos.pres)
         {
            msg->u.bearAllocReq.tft.pfList[idx].tos.pres = bearAllocReq->tft.pfList[idx].tos.pres;
            msg->u.bearAllocReq.tft.pfList[idx].tos.tos =  bearAllocReq->tft.pfList[idx].tos.tos;
            msg->u.bearAllocReq.tft.pfList[idx].tos.mask = bearAllocReq->tft.pfList[idx].tos.mask;
         }
         if(bearAllocReq->tft.pfList[idx].flowLabel.pres)
         {
            msg->u.bearAllocReq.tft.pfList[idx].flowLabel.pres =\
               bearAllocReq->tft.pfList[idx].flowLabel.pres;
            cmMemcpy((U8 *)&msg->u.bearAllocReq.tft.pfList[idx].flowLabel.buf, \
               (U8 *)bearAllocReq->tft.pfList[idx].flowLabel.buf,CM_ESM_IPV6_FLOW_LABEL_SIZE);
         }
      }
      for( idx = 0 ; idx < msg->u.bearAllocReq.tft.noOfParams ; idx++)
      {
         msg->u.bearAllocReq.tft.params[idx].len       =  bearAllocReq->tft.params[idx].len;
         msg->u.bearAllocReq.tft.params[idx].paramType =  bearAllocReq->tft.params[idx].paramType;
         cmMemcpy((U8 *)&msg->u.bearAllocReq.tft.params[idx].buf, \
            (U8 *)bearAllocReq->tft.params[idx].buf,CM_ESM_TFT_MAX_PARAM_BUF);
      }
   }
   /* Protocol Cfg Options */
   msg->u.bearAllocReq.protCfgOpt.pres = NOTPRSNT;

   RETVALUE(ROK);
}

/*
 *
 *       Fun: uefillDedEsmInfoToUeCb
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 uefillDedEsmInfoToUeCb
(
 UeCb *ueCb,
 CmNasEvnt *evnt,
 U8 drbId,
 U8 epsBearerId
)
{
   S16 ret = ROK;
   U8 idx = 0;
   U8 rbIdx = 0;
   UeAppCb *ueAppCb = NULLP;
   CmEsmActDedBearCtxtReq *actReq = NULLP;
   UeRabCb *params;
   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);
   params = &ueCb->ueRabCb[drbId];

   actReq = &evnt->m.esmEvnt->u.actDedBearReq;
   params->bearerType = DEDICATED_BEARER;
   ueCb->ueRabCb[drbId].drbId = drbId;
   ueCb->ueRabCb[drbId].epsBearerId = epsBearerId;
   params->lnkEpsBearId = actReq->lnkBearerId;
   /* If this dedicated bearer is for IPv6 or IPv4v6 pdn type,
    * copy the ipv6 address from the default bearer to dedicated ueRabCb
    * Because the pdn address in ueRabCb contains only interface id
    */
   if( (ret = ueAppUtlFndRbCb(&rbIdx, ueCb, params->lnkEpsBearId) == ROK)){
     if ((ueCb->ueRabCb[rbIdx].pAddr.pdnType == CM_ESM_PDN_IPV4V6) ||
       (ueCb->ueRabCb[rbIdx].pAddr.pdnType == CM_ESM_PDN_IPV6)) {
       cmMemcpy(params->ipv6Addr, ueCb->ueRabCb[rbIdx].ipv6Addr, sizeof(params->ipv6Addr));
     }
   }
   if(actReq->epsQos.pres == TRUE)
   {
      params->epsQos.pres              = TRUE;
      params->epsQos.lenQosCont        = actReq->epsQos.lenQosCont;
      params->epsQos.qci               = actReq->epsQos.qci;
      params->epsQos.maxBitRateUL      = actReq->epsQos.maxBitRateUL;
      params->epsQos.maxBitRateDL      = actReq->epsQos.maxBitRateDL;;
      params->epsQos.guaraBitRateUL    = actReq->epsQos.guaraBitRateUL;
      params->epsQos.guaraBitRateDL    = actReq->epsQos.guaraBitRateDL;
      params->epsQos.maxBitRateULExt   = actReq->epsQos.maxBitRateULExt;
      params->epsQos.maxBitRateDLExt   = actReq->epsQos.maxBitRateDLExt;
      params->epsQos.guaraBitRateULExt = actReq->epsQos.guaraBitRateULExt;
      params->epsQos.guaraBitRateDLExt = actReq->epsQos.guaraBitRateDLExt;
   }
   else
   {
      params->epsQos.pres = FALSE;
   }
   if(actReq->txnId.pres == TRUE)
   {
      params->txnId.pres = TRUE;
      params->txnId.len = actReq->txnId.len;
      params->txnId.tiVal = actReq->txnId.tiVal;
      params->txnId.tiFlag = actReq->txnId.tiFlag;
      params->txnId.tie = actReq->txnId.tie;
      params->txnId.tiExt = actReq->txnId.tiExt;
   }
   else
   {
      params->txnId.pres = FALSE;
   }
   if(actReq->qos.pres == TRUE)
   {
      params->qos.pres              = TRUE;
      params->qos.lenQosCont        = actReq->qos.lenQosCont;
      params->qos.relClass          = actReq->qos.relClass;
      params->qos.delayClass        = actReq->qos.delayClass;
      params->qos.precClass         = actReq->qos.precClass;
      params->qos.peakTp            = actReq->qos.peakTp;
      params->qos.meanTp            = actReq->qos.meanTp;
      params->qos.deliveryErrSdu    = actReq->qos.deliveryErrSdu;
      params->qos.deliveryOrder     = actReq->qos.deliveryOrder;
      params->qos.trafficClass      = actReq->qos.trafficClass;
      params->qos.maxSdu            = actReq->qos.maxSdu;
      params->qos.maxBitRateUL      = actReq->qos.maxBitRateUL;
      params->qos.maxBitRateDL      = actReq->qos.maxBitRateDL;
      params->qos.sduErrRatio       = actReq->qos.sduErrRatio;
      params->qos.residualBer       = actReq->qos.residualBer;
      params->qos.trafHandPrio      = actReq->qos.trafHandPrio;
      params->qos.transferDelay     = actReq->qos.transferDelay;
      params->qos.guaraBitRateUL    = actReq->qos.guaraBitRateUL;
      params->qos.guaraBitRateDL    = actReq->qos.guaraBitRateDL;
      params->qos.srcStatDesc       = actReq->qos.srcStatDesc;
      params->qos.signalInd         = actReq->qos.signalInd;
      params->qos.maxBitRateDLExt   = actReq->qos.maxBitRateDLExt;
      params->qos.maxBitRateULExt   = actReq->qos.maxBitRateULExt;
      params->qos.guaraBitRateDLExt = actReq->qos.guaraBitRateDLExt;
      params->qos.guaraBitRateULExt = actReq->qos.guaraBitRateULExt;
   }
   else
   {
      params->qos.pres              = FALSE;
   }
   if(actReq->llc.pres == TRUE)
   {
      params->llc.pres = TRUE;
      params->llc.ieVal = actReq->llc.ieVal;
   }
   else
   {
      params->llc.pres = FALSE;
   }
   if(actReq->radioPrio.pres == TRUE)
   {
      params->radioPrio.pres = TRUE;
      params->radioPrio.ieVal = actReq->radioPrio.ieVal;
   }
   else
   {
      params->radioPrio.pres =FALSE;
   }
   if(actReq->pktFlowId.pres == TRUE)
   {
      params->pktFlowId.pres = TRUE;
      params->pktFlowId.len = actReq->pktFlowId.len;
      params->pktFlowId.ieVal = actReq->pktFlowId.ieVal;
   }
   else
   {
      params->pktFlowId.pres = FALSE;
   }
   params->tft.pres = actReq->tft.pres;
   if(params->tft.pres == TRUE)
   {
      params->tft.pres       = actReq->tft.pres;
      params->tft.len        = actReq->tft.len;
      params->tft.opCode     = actReq->tft.opCode;
      params->tft.noOfPfs    = actReq->tft.noOfPfs;
      params->tft.eBit       = actReq->tft.eBit;
      params->tft.noOfParams = actReq->tft.noOfParams;

      params->tft.noOfPfs  =  actReq->tft.noOfPfs;
      for( idx = 0 ; idx < params->tft.noOfPfs ; idx++)
      {
         params->tft.pfList[idx].pres = TRUE;
         params->tft.pfList[idx].id =    actReq->tft.pfList[idx].id;
         params->tft.pfList[idx].dir =   actReq->tft.pfList[idx].dir;
         params->tft.pfList[idx].preced = actReq->tft.pfList[idx].preced;
         params->tft.pfList[idx].len =   actReq->tft.pfList[idx].len;
         params->tft.pfList[idx].ipv4.pres = actReq->tft.pfList[idx].ipv4.pres;
         if(params->tft.pfList[idx].ipv4.pres)
         {
            cmMemcpy((U8 *)&params->tft.pfList[idx].ipv4.ip4, \
               (U8 *)actReq->tft.pfList[idx].ipv4.ip4,CM_ESM_IPV4_SIZE);
         }
         params->tft.pfList[idx].ipv6.pres = actReq->tft.pfList[idx].ipv6.pres;
         if(params->tft.pfList[idx].ipv6.pres)
         {
            cmMemcpy((U8 *)&params->tft.pfList[idx].ipv6.ip6, \
               (U8 *)actReq->tft.pfList[idx].ipv6.ip6,CM_ESM_IPV6_SIZE);
         }
         params->tft.pfList[idx].protId.pres     = actReq->tft.pfList[idx].protId.pres;
         if(params->tft.pfList[idx].protId.pres)
         {
            params->tft.pfList[idx].protId.protType = actReq->tft.pfList[idx].protId.protType;
         }
         if(params->tft.pfList[idx].localPort.pres)
         {
            params->tft.pfList[idx].localPort.pres  = actReq->tft.pfList[idx].localPort.pres;
            params->tft.pfList[idx].localPort.port  = actReq->tft.pfList[idx].localPort.port;
         }
         if(actReq->tft.pfList[idx].remotePort.pres)
         {
            params->tft.pfList[idx].remotePort.pres = actReq->tft.pfList[idx].remotePort.pres;
            params->tft.pfList[idx].remotePort.port = actReq->tft.pfList[idx].remotePort.port;
         }
         params->tft.pfList[idx].locPortRange.pres = \
             actReq->tft.pfList[idx].locPortRange.pres;
         if(actReq->tft.pfList[idx].locPortRange.pres)
         {
            params->tft.pfList[idx].locPortRange.rangeLow =
               actReq->tft.pfList[idx].locPortRange.rangeLow;
            params->tft.pfList[idx].locPortRange.rangeHigh =  \
               actReq->tft.pfList[idx].locPortRange.rangeHigh;
         }
         params->tft.pfList[idx].remPortRange.pres = \
            actReq->tft.pfList[idx].remPortRange.pres;
         if(params->tft.pfList[idx].remPortRange.pres)
         {
            params->tft.pfList[idx].remPortRange.rangeLow = \
               actReq->tft.pfList[idx].remPortRange.rangeLow;
            params->tft.pfList[idx].remPortRange.rangeHigh =  \
               actReq->tft.pfList[idx].remPortRange.rangeHigh;
         }
         params->tft.pfList[idx].secParam.pres = \
            actReq->tft.pfList[idx].secParam.pres;
         if(params->tft.pfList[idx].secParam.pres)
         {
            cmMemcpy((U8 *)& params->tft.pfList[idx].secParam.params, \
               (U8 *)actReq->tft.pfList[idx].secParam.params, CM_ESM_IP_SEC_SIZE);
         }
         if(actReq->tft.pfList[idx].tos.pres)
         {
            params->tft.pfList[idx].tos.pres =   actReq->tft.pfList[idx].tos.pres;
            params->tft.pfList[idx].tos.tos  =    actReq->tft.pfList[idx].tos.tos;
            params->tft.pfList[idx].tos.mask =  actReq->tft.pfList[idx].tos.mask;
         }
         if(actReq->tft.pfList[idx].flowLabel.pres)
         {
            params->tft.pfList[idx].flowLabel.pres = actReq->tft.pfList[idx].flowLabel.pres;
            cmMemcpy((U8 *)&params->tft.pfList[idx].flowLabel.buf, \
               (U8 *)actReq->tft.pfList[idx].flowLabel.buf,CM_ESM_IPV6_FLOW_LABEL_SIZE);
         }
      }
      for( idx = 0 ; idx < params->tft.noOfParams ; idx++)
      {
         params->tft.params[idx].len       =  actReq->tft.params[idx].len;
         params->tft.params[idx].paramType =  actReq->tft.params[idx].paramType;
         cmMemcpy((U8 *)&params->tft.params[idx].buf, \
            (U8 *)actReq->tft.params[idx].buf,CM_ESM_TFT_MAX_PARAM_BUF);
      }
   }
     if( (ret = ueAppUtlFndRbCb(&rbIdx,ueCb,params->lnkEpsBearId) == ROK))
     {
        /* copy the IP ADDESS FROM DEFAULT BEARER */
         params->pAddr.pres = TRUE;
         params->pAddr.len = ueCb->ueRabCb[rbIdx].pAddr.len;
         params->pAddr.pdnType = ueCb->ueRabCb[rbIdx].pAddr.pdnType;
         cmMemcpy((U8 *)&params->pAddr.addrInfo, (U8 *)&ueCb->ueRabCb[rbIdx].pAddr.addrInfo,
               CM_ESM_MAX_LEN_PDN_ADDRESS);
     }
   UE_LOG_EXITFN(ueAppCb, ret);
}
/*
 *
 *       Fun: ueAppEsmHndlIncDeActvBearerReq
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppEsmHndlIncDeActvBearerReq
(
 UeEsmCb *esmCb,
 CmNasEvnt *evnt,
 UeCb *ueCb,
 U8 epsBearerId
)
{
   S16 ret = ROK;
   U8 drbId = 0;
   UeAppCb *ueAppCb;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);
   UE_LOG_DEBUG(ueAppCb, "De-Activate bearer request");

   /* Update procedure transaction state */
   esmCb->pState = UE_ESM_ST_PROC_TXN_INACTIVE;

   /* update bearer Id */
   esmCb->bId = evnt->m.esmEvnt->bearerId;
   ueAppSendIncDeActvBerReqInd(ueCb, esmCb->bId);
   RETVALUE(ROK);

} /* ueAppEsmHndlIncActDedBearerReq */


/*
 *
 *       Fun: ueAppEsmHndlIncActDedBearerReq
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppEsmHndlIncActDedBearerReq
(
 UeEsmCb *esmCb,
 CmNasEvnt *evnt,
 UeCb *ueCb,
 U8 epsBearerId
)
{
   S16 ret = ROK;
   U8 drbId = 0;
   UeAppCb *ueAppCb;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Activate Dedicated bearer request");

   /* Update procedure transaction state */
   esmCb->pState = UE_ESM_ST_PROC_TXN_INACTIVE;

   /* update bearer Id */
   esmCb->bId = evnt->m.esmEvnt->bearerId;
   ret = ueAppGetDrb(ueCb, &drbId);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "DRB Cb not found");
      RETVALUE(ret);
   }

   ueCb->numRabs++;

   ret = uefillDedEsmInfoToUeCb(ueCb, evnt, (drbId - 1),epsBearerId);

   ueAppUtlMovEsmCbTransToBid(esmCb, ueCb);
   ueAppSendIncActDedBerReqInd(ueCb, drbId - 1);
   RETVALUE(ROK);

} /* ueAppEsmHndlIncActDedBearerReq */

PRIVATE S16 ueAppSendIncDeActvBerReqInd(UeCb *ueCb,U8 bId)
{
  U8 idx;
  UeAppCb *ueAppCb;
  UetMessage *tfwMsg = NULLP;
  UeUetDeActvBearCtxtReq *ueDeActvBerReq = NULLP;
  U8 cause = 0;
  UE_GET_CB(ueAppCb);
  tfwMsg = (UetMessage*)ueAlloc(sizeof(UetMessage));
  cmMemset((U8 *)tfwMsg, 0, sizeof(UetMessage));
  tfwMsg->msg.ueDeActvBerReq.ueId   = ueCb->ueId;
  tfwMsg->msgType = UE_EPS_DEACTIVATE_BER_REQ;

  ueDeActvBerReq = &tfwMsg->msg.ueDeActvBerReq;
  ueDeActvBerReq->bearerId  =  bId;
  ueDeActvBerReq->esmCause  =  cause;

   RETVALUE(ueSendToTfwApp(tfwMsg, &ueAppCb->fwPst));
}
PRIVATE S16 ueAppSendIncActDedBerReqInd(UeCb *ueCb,U8 drbIdx)
{
   U8 idx;
   UeAppCb *ueAppCb;
   UetMessage *tfwMsg = NULLP;
   UeUetActDedBearCtxtReq *ueActDedBerReq = NULLP;
   UeRabCb *params = NULLP;
  UE_GET_CB(ueAppCb);
  params = &ueCb->ueRabCb[drbIdx];
  tfwMsg = (UetMessage*)ueAlloc(sizeof(UetMessage));
  cmMemset((U8 *)tfwMsg, 0, sizeof(UetMessage));
  tfwMsg->msg.ueActDedBerReq.ueId   = ueCb->ueId;
  tfwMsg->msgType = UE_EPS_DED_BER_REQ;

  ueActDedBerReq = &tfwMsg->msg.ueActDedBerReq;
  ueActDedBerReq->lnkBearerId              =  params->lnkEpsBearId;
  ueActDedBerReq->bearerId                 =  params->epsBearerId;
 if(params->epsQos.pres)
 {
    ueActDedBerReq->epsQos.pres              =  params->epsQos.pres;
    ueActDedBerReq->epsQos.lenQosCont        =  params->epsQos.lenQosCont;
    ueActDedBerReq->epsQos.qci               =  params->epsQos.qci;
    ueActDedBerReq->epsQos.maxBitRateUL      =  params->epsQos.maxBitRateUL;
    ueActDedBerReq-> epsQos.maxBitRateDL     =  params->epsQos.maxBitRateDL;
    ueActDedBerReq->epsQos.guaraBitRateUL    =  params->epsQos.guaraBitRateUL;
    ueActDedBerReq->epsQos.guaraBitRateDL    =  params->epsQos.guaraBitRateDL;
#if 0
 ueActDedBerReq->epsQos.maxBitRateULExt   =  params->epsQos.maxBitRateULExt;
 ueActDedBerReq->epsQos.maxBitRateDLExt   =  params->epsQos.maxBitRateDLExt;
 ueActDedBerReq-> epsQos.guaraBitRateULExt =  params->epsQos.guaraBitRateULExt;
 ueActDedBerReq->epsQos.guaraBitRateDLExt =  params->epsQos.guaraBitRateDLExt;
#endif
 }

 if(params->txnId.pres)
 {
    ueActDedBerReq->txnId.pres          = params->txnId.pres;
    ueActDedBerReq->txnId.len           = params->txnId.len;
    ueActDedBerReq->txnId.tiVal         = params->txnId.tiVal;
    ueActDedBerReq->txnId.tiFlag        = params->txnId.tiFlag;
    ueActDedBerReq->txnId.tie           = params->txnId.tie;
    ueActDedBerReq->txnId.tiExt         = params->txnId.tiExt;
 }
 if(params->qos.pres)
 {
    ueActDedBerReq->qos.pres            = params->qos.pres;
    ueActDedBerReq->qos.lenQosCont      = params->qos.lenQosCont;
    ueActDedBerReq->qos.relClass        = params->qos.relClass;
    ueActDedBerReq->qos.delayClass      = params->qos.delayClass;
    ueActDedBerReq->qos.precClass       = params->qos.precClass;
    ueActDedBerReq->qos.peakTp          = params->qos.peakTp;
    ueActDedBerReq->qos.meanTp          = params->qos.meanTp;
    ueActDedBerReq->qos.deliveryErrSdu  = params->qos.deliveryErrSdu;
    ueActDedBerReq->qos.deliveryOrder   = params->qos.deliveryOrder;
    ueActDedBerReq->qos.trafficClass    = params->qos.trafficClass;
    ueActDedBerReq->qos.maxSdu          = params->qos.maxSdu;
    ueActDedBerReq->qos.maxBitRateUL    = params->qos.maxBitRateUL;
    ueActDedBerReq->qos.maxBitRateDL    = params->qos.maxBitRateDL;
    ueActDedBerReq->qos.sduErrRatio     = params->qos.sduErrRatio;
    ueActDedBerReq->qos.residualBer     = params->qos.residualBer;
    ueActDedBerReq->qos.trafHandPrio    = params->qos.trafHandPrio;
    ueActDedBerReq->qos.transferDelay   = params->qos.transferDelay;
    ueActDedBerReq->qos.guaraBitRateUL  = params->qos.guaraBitRateUL;
    ueActDedBerReq->qos.guaraBitRateDL  = params->qos.guaraBitRateDL;
    ueActDedBerReq->qos.srcStatDesc     = params->qos.srcStatDesc;
    ueActDedBerReq->qos.signalInd       = params->qos.signalInd;
#if 0
 ueActDedBerReq->qos.maxBitRateDLExt = params->qos.maxBitRateDLExt;
 ueActDedBerReq->qos.maxBitRateULExt   = params->qos.maxBitRateULExt;
 ueActDedBerReq->qos.guaraBitRateDLExt = params->qos.guaraBitRateDLExt;
 ueActDedBerReq->qos.guaraBitRateULExt = params->qos.guaraBitRateULExt;
#endif
 }
 if(params->llc.pres)
 {
    ueActDedBerReq->llc.pres  = params->llc.pres;
    ueActDedBerReq->llc.ieVal = params->llc.ieVal;
 }
 if(params->radioPrio.pres)
 {
    ueActDedBerReq->radioPrio.pres  = params->radioPrio.pres;
    ueActDedBerReq->radioPrio.ieVal = params->radioPrio.ieVal;
 }
 if(params->pktFlowId.pres)
 {
    ueActDedBerReq->pktFlowId.pres   = params->pktFlowId.pres;
    ueActDedBerReq->pktFlowId.len    = params->pktFlowId.len;
    ueActDedBerReq->pktFlowId.ieVal  = params->pktFlowId.ieVal;
 }

 ueActDedBerReq->tft.pres         = params->tft.pres;
 if(params->tft.pres )
 {
    ueActDedBerReq->tft.len          = params->tft.len;
    ueActDedBerReq->tft.opCode       = params->tft.opCode;
    ueActDedBerReq->tft.noOfPfs      = params->tft.noOfPfs;
    ueActDedBerReq->tft.eBit         = params->tft.eBit;
    ueActDedBerReq->tft.noOfParams   = params->tft.noOfParams;

    ueActDedBerReq->tft.noOfPfs = params->tft.noOfPfs;
    for( idx = 0 ; idx < ueActDedBerReq->tft.noOfPfs ; idx++)
    {
       ueActDedBerReq->tft.pfList[idx].pres         = params->tft.pfList[idx].pres;
       ueActDedBerReq->tft.pfList[idx].id           = params->tft.pfList[idx].id;
       ueActDedBerReq->tft.pfList[idx].dir          = params->tft.pfList[idx].dir;
       ueActDedBerReq->tft.pfList[idx].preced       = params->tft.pfList[idx].preced;
       ueActDedBerReq->tft.pfList[idx].len          = params->tft.pfList[idx].len;
       if(params->tft.pfList[idx].ipv4.pres)
       {
          ueActDedBerReq->tft.pfList[idx].ipv4.pres    = params->tft.pfList[idx].ipv4.pres;
            cmMemcpy((U8 *)&ueActDedBerReq->tft.pfList[idx].ipv4.ip4, \
               (U8 *)params->tft.pfList[idx].ipv4.ip4,CM_ESM_IPV4_SIZE);
       }
       if(params->tft.pfList[idx].ipv6.pres)
       {
          ueActDedBerReq->tft.pfList[idx].ipv6.pres =  params->tft.pfList[idx].ipv6.pres;
            cmMemcpy((U8 *)&ueActDedBerReq->tft.pfList[idx].ipv6.ip6, \
               (U8 *)params->tft.pfList[idx].ipv6.ip6,CM_ESM_IPV6_SIZE);
       }
       if(params->tft.pfList[idx].protId.pres)
       {
          ueActDedBerReq->tft.pfList[idx].protId.pres        = params->tft.pfList[idx].protId.pres;
          ueActDedBerReq->tft.pfList[idx].protId.protType    = params->tft.pfList[idx].protId.protType;
       }
       if(params->tft.pfList[idx].localPort.pres)
       {
          ueActDedBerReq->tft.pfList[idx].localPort.pres     = params->tft.pfList[idx].localPort.pres;
          ueActDedBerReq->tft.pfList[idx].localPort.port     = params->tft.pfList[idx].localPort.port;
       }
       if(params->tft.pfList[idx].remotePort.pres)
       {
          ueActDedBerReq->tft.pfList[idx].remotePort.pres    = params->tft.pfList[idx].remotePort.pres;
          ueActDedBerReq->tft.pfList[idx].remotePort.port    = params->tft.pfList[idx].remotePort.port;
       }
       if(params->tft.pfList[idx].locPortRange.pres)
       {
          ueActDedBerReq->tft.pfList[idx].locPortRange.pres  =\
              params->tft.pfList[idx].locPortRange.pres;
          ueActDedBerReq->tft.pfList[idx].locPortRange.rangeLow =\
          params->tft.pfList[idx].locPortRange.rangeLow;
          ueActDedBerReq->tft.pfList[idx].locPortRange.rangeHigh   = \
             params->tft.pfList[idx].locPortRange.rangeHigh;
       }
       if(params->tft.pfList[idx].remPortRange.pres)
       {
          ueActDedBerReq->tft.pfList[idx].remPortRange.pres        = \
             params->tft.pfList[idx].remPortRange.pres;
          ueActDedBerReq->tft.pfList[idx].remPortRange.rangeLow    = \
             params->tft.pfList[idx].remPortRange.rangeLow;
          ueActDedBerReq->tft.pfList[idx].remPortRange.rangeHigh   = \
             params->tft.pfList[idx].remPortRange.rangeHigh;
       }
       if(params->tft.pfList[idx].secParam.pres)
       {
          ueActDedBerReq->tft.pfList[idx].secParam.pres  = \
             params->tft.pfList[idx].secParam.pres;
            cmMemcpy((U8 *)&ueActDedBerReq->tft.pfList[idx].secParam.params, \
               (U8 *)params->tft.pfList[idx].secParam.params, CM_ESM_IP_SEC_SIZE);
       }
       if(ueActDedBerReq->tft.pfList[idx].tos.pres)
       {
          ueActDedBerReq->tft.pfList[idx].tos.pres         = params->tft.pfList[idx].tos.pres;
          ueActDedBerReq->tft.pfList[idx].tos.tos          = params->tft.pfList[idx].tos.tos;
          ueActDedBerReq->tft.pfList[idx].tos.mask         = params->tft.pfList[idx].tos.mask;
       }
       if(params->tft.pfList[idx].flowLabel.pres)
       {
          ueActDedBerReq->tft.pfList[idx].flowLabel.pres   = params->tft.pfList[idx].flowLabel.pres;
            cmMemcpy((U8 *)&ueActDedBerReq->tft.pfList[idx].flowLabel.buf, \
               (U8 *)params->tft.pfList[idx].flowLabel.buf,CM_ESM_IPV6_FLOW_LABEL_SIZE);
       }
      }
      for( idx = 0 ; idx < params->tft.noOfParams ; idx++)
      {
       ueActDedBerReq->tft.params[idx].len          = params->tft.params[idx].len;
       ueActDedBerReq->tft.params[idx].paramType    = params->tft.params[idx].paramType;
       cmMemcpy((U8 *)&ueActDedBerReq->tft.params[idx].buf, \
            (U8 *)params->tft.params[idx].buf,CM_ESM_TFT_MAX_PARAM_BUF);
      }
   }
   RETVALUE(ueSendToTfwApp(tfwMsg, &ueAppCb->fwPst));
}


#ifdef ANSI
PRIVATE Void ueAppAuthHexDump
(
U8    *buf,
U16   len
)
#else
PRIVATE Void ueAppAuthHexDump(name,buf, len)
(
U8    *buf;
U16   len;
)
#endif
{
   U16 cnt = 0;
   printf(" \n[");
   for(cnt = 0; cnt < len; cnt++)
   {
      if((cnt != 0) &&(0 == cnt%16))
      {
         printf(" ]\n [");
      }
      else if((cnt != 0) &&(0 == cnt%8))
      {
         printf("  ");
      }
      else if((cnt != 0) &&(0 == cnt%4))
      {
         printf(" ");
      }
      printf(" %02x", buf[cnt]);
   }
   printf(" ]\n");
}

/*
 *
 *       Fun: ueAppEmmHndlInEmmInformation
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppEmmHndlInEmmInformation(CmNasEvnt *evnt, UeCb *ueCb)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Handling EMM Information Messsage");

   ret = ueAppRcvEmmMsg(evnt, evnt->m.emmEvnt->msgId, ueCb);

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueBldEmmInformationToTfw
 *
 *       Desc: Builds Emm information towards TFW
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueBldEmmInformationToTfw(UetMessage *tfwMsg, UeCb *ueCb)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Building Detach Accept Indication to TFWAPP");
   tfwMsg->msgType = UE_EMM_INFORMATION_TYPE;
   tfwMsg->msg.ueEmmInformation.ueId = ueCb->ueId;

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueAppEmmHndlInAuthReject
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppEmmHndlInAuthReject
(
 CmNasEvnt *evnt,
 UeCb *ueCb
)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Handling UE Authentication Reject Messsage");

   ret = ueAppRcvEmmMsg(evnt, evnt->m.emmEvnt->msgId, ueCb);

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueBldAuthRejToTfw
 *
 *       Desc: Builds Authentication Reject towards TFW
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueBldAuthRejToTfw(UetMessage *tfwMsg, UeCb *ueCb)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Building Auth reject Indication to TFWAPP");
   tfwMsg->msgType = UE_AUTH_REJ_IND_TYPE;
   tfwMsg->msg.ueUetAuthRejInd.ueId = ueCb->ueId;

   UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueAppUtlBldEsmInformationRsp
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppUtlBldEsmInformationRsp
(
 CmNasEvnt **esmEvnt,
 UeUetEsmInformationRsp  *ueEsmInformationRsp
)
{
   CmEsmMsg    *msg = NULLP;
   printf("Building ESM Information Response for Ue\n");

   if(esmEvnt == NULLP)
   {
      RETVALUE(RFAILED);
   }

   /* Allocate memory for mme evnt */
   CM_ALLOC_NASEVNT (esmEvnt, CM_ESM_PD);
   if (*esmEvnt == NULLP)
   {
      RETVALUE(RFAILED);
   }

   /*Allocate memory for ESM message*/
   if (cmGetMem(&(*esmEvnt)->memCp, sizeof(CmEsmMsg), (Ptr *)&msg) != ROK)
   {
      CM_FREE_NASEVNT(esmEvnt);
      RETVALUE(RFAILED);
   }

   msg->protDisc = CM_ESM_PD;
   (*esmEvnt)->m.esmEvnt = msg;

   (*esmEvnt)->secHT = CM_NAS_SEC_HDR_TYPE_INT_PRTD_ENC;
   /* Fill ESM Information Response message */

   /*Fill mandatory IE's*/
   /* EPS barer ID IE*/
   msg->bearerId = 0;
   msg->prTxnId = ueEsmInformationRsp->tId;

   /* PDN connectivity request message idenmtity*/
   msg->msgType = CM_ESM_MSG_ESM_INFO_RSP;

   if( ueEsmInformationRsp->nasPdnApn.len != 0) {
     msg->u.esmInfoResp.apn.pres      = TRUE;
     encode_apn(&msg->u.esmInfoResp.apn,&ueEsmInformationRsp->nasPdnApn);
    } else {
     msg->u.esmInfoResp.apn.pres      = FALSE;
   }
   RETVALUE(ROK);
}
/*
 *
 *       Fun: ueProcUeEsmInformationRsp
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueProcUeEsmInformationRsp(UetMessage *p_ueMsg, Pst *pst)
{
   S16 ret = ROK;
   U32  ueId = 0;
   U8 isPlainMsg = TRUE;
   UeAppMsg srcMsg;
   UeAppMsg dstMsg;
   UeAppCb *ueAppCb = NULLP;
   UeCb *ueCb = NULLP;
   CmNasEvnt           *esmInfoRspEvnt = NULLP;
   NhuDedicatedInfoNAS nasEncPdu;
   NbuUlNasMsg *nbUeEsmInfoRsp = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Sending ESM Information Rsp");
   ueId = p_ueMsg->msg.ueEsmInformationRsp.ueId;
   ret = ueDbmFetchUe(ueId, (PTR *)&ueCb);
   if( ret != ROK )
   {
      UE_LOG_ERROR(ueAppCb, "UeCb List NULL ueId = %d", ueId);
   }
   ret = ueAppUtlBldEsmInformationRsp(&esmInfoRspEvnt,
         &p_ueMsg->msg.ueEsmInformationRsp);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Building Esm Information Response failed");
      RETVALUE(ret);
   }

   if ((ret = ueAppEsmHdlOutUeEvnt(esmInfoRspEvnt, ueCb))!= ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Handling ESM Information Response message failed \n");
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&nasEncPdu, 0, sizeof(NhuDedicatedInfoNAS));

   /* Encode the PDU */
   ret = ueAppEdmEncode(esmInfoRspEvnt, &nasEncPdu);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Esm Information Response Encode Failed");
      CM_FREE_NASEVNT(&esmInfoRspEvnt);
      RETVALUE(ret);
   }
   /** Integrity Protected **/
   if (CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG != esmInfoRspEvnt->secHT)
   {
      isPlainMsg = FALSE;
      srcMsg.val = nasEncPdu.val;
      srcMsg.len = nasEncPdu.len;
      ret = ueAppCmpUplnkSec(&ueCb->secCtxt, esmInfoRspEvnt->secHT, &srcMsg,
                             &dstMsg);
      if (ROK != ret)
      {
         UE_LOG_ERROR(ueAppCb, "Uplink Security Failed");
         EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
         esmInfoRspEvnt->pdu = NULLP;
         CM_FREE_NASEVNT(&esmInfoRspEvnt);
         RETVALUE(ret);
      }
      EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
      nasEncPdu.val = dstMsg.val;
      nasEncPdu.len = dstMsg.len;
   }
   CM_FREE_NASEVNT(&esmInfoRspEvnt);

   nbUeEsmInfoRsp = (NbuUlNasMsg *)ueAlloc(sizeof(NbuUlNasMsg));
   nbUeEsmInfoRsp->ueId = ueId;
   nbUeEsmInfoRsp->nasPdu.pres = TRUE;
   nbUeEsmInfoRsp->nasPdu.len = nasEncPdu.len;
   nbUeEsmInfoRsp->nasPdu.val = (U8 *)ueAlloc(nbUeEsmInfoRsp->nasPdu.len);
   cmMemcpy((U8 *)nbUeEsmInfoRsp->nasPdu.val, nasEncPdu.val,
         nbUeEsmInfoRsp->nasPdu.len);

   if (isPlainMsg)
   {
   EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
   }

   ret = ueSendUlNasMsgToNb(nbUeEsmInfoRsp, &ueAppCb->nbPst);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Sending Esm Information Response to enbAPP failed");
      ret = RFAILED;
   }

   UE_LOG_EXITFN(ueAppCb, ret);
} /* End of ueProcUeEsmInformationRsp */

/*
 *
 *       Fun: ueAppUtlBldStandAlonePdnDisconnectReq
 *
 *       Desc: Builds standalone PDN disconnect request
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */

PRIVATE S16 ueAppUtlBldStandAlonePdnDisconnectReq
(
 CmNasEvnt **esmEvnt,
 UeUetPdnDisconnectReq *ueUetPdnDisConReq
)
{
   CmEsmMsg    *msg = NULLP;
   printf("Building PDN Disconnect Request\n");

   if(esmEvnt == NULLP)
   {
      RETVALUE(RFAILED);
   }

   /* Allocate memory for mme evnt */
   CM_ALLOC_NASEVNT (esmEvnt, CM_ESM_PD);
   if (*esmEvnt == NULLP)
   {
      RETVALUE(RFAILED);
   }

   /*Allocate memory for ESM message*/
   if (cmGetMem(&(*esmEvnt)->memCp, sizeof(CmEsmMsg), (Ptr *)&msg) != ROK)
   {
      CM_FREE_NASEVNT(esmEvnt);
      RETVALUE(RFAILED);
   }

   msg->protDisc = CM_ESM_PD;
   (*esmEvnt)->m.esmEvnt = msg;

   (*esmEvnt)->secHT = CM_NAS_SEC_HDR_TYPE_INT_PRTD_ENC;
   /* Fill ESM PDN disconnect request message */

   /*Fill mandatory IE's*/
   /* EPS barer ID IE*/
   msg->bearerId = 0;
   /* Linked bearer ID*/
   msg->u.disconReq.lnkBearerId = ueUetPdnDisConReq->bearerId;

   /* PDN disconnect request message identity*/
   msg->msgType = CM_ESM_MSG_PDN_DISCONN_REQ;

   RETVALUE(ROK);
}


/*
 *
 *       Fun: ueProcUePdnDisconnectReq
 *
 *       Desc: Processes PDN disconnect request
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueProcUePdnDisconnectReq(UetMessage *p_ueMsg, Pst *pst) {
  S16 ret = ROK;
  U32 ueId = 0;
  U8 isPlainMsg = TRUE;
  UeAppMsg srcMsg;
  UeAppMsg dstMsg;
  UeAppCb *ueAppCb = NULLP;
  UeCb *ueCb = NULLP;
  CmNasEvnt *pdnDisconnectReqEvnt = NULLP;
  NhuDedicatedInfoNAS nasEncPdu;
  NbuUlNasMsg *nbUePdnDisconnectReq = NULLP;

  UE_GET_CB(ueAppCb);
  UE_LOG_ENTERFN(ueAppCb);

  UE_LOG_DEBUG(ueAppCb, "Recieved PDN Disconnect Request");
  ueId = p_ueMsg->msg.ueUetPdnDisconnectReq.ueId;
  ret = ueDbmFetchUe(ueId, (PTR *)&ueCb);
  if (ret != ROK) {
    UE_LOG_ERROR(ueAppCb, "UeCb List NULL ueId = %d", ueId);
  }
  ret = ueAppUtlBldStandAlonePdnDisconnectReq(
      &pdnDisconnectReqEvnt, &p_ueMsg->msg.ueUetPdnDisconnectReq);
  if (ret != ROK) {
    UE_LOG_ERROR(ueAppCb, "Building pdn disconnect req message failed");
    RETVALUE(ret);
  }

  if ((ret = ueAppEsmHdlOutUeEvnt(pdnDisconnectReqEvnt, ueCb)) != ROK) {
    UE_LOG_ERROR(ueAppCb, "Handling PDN disconnect Request failed \n");
    RETVALUE(RFAILED);
  }

  cmMemset((U8 *)&nasEncPdu, 0, sizeof(NhuDedicatedInfoNAS));

  /* Encode the PDU */
  ret = ueAppEdmEncode(pdnDisconnectReqEvnt, &nasEncPdu);
  if (ret != ROK) {
    UE_LOG_ERROR(ueAppCb, "Pdn Disconnect Req Encode Failed");
    CM_FREE_NASEVNT(&pdnDisconnectReqEvnt);
    RETVALUE(ret);
  }
  /** Integrity Protected **/
  if (CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG != pdnDisconnectReqEvnt->secHT) {
    isPlainMsg = FALSE;
    srcMsg.val = nasEncPdu.val;
    srcMsg.len = nasEncPdu.len;
    ret = ueAppCmpUplnkSec(&ueCb->secCtxt, pdnDisconnectReqEvnt->secHT, &srcMsg,
                           &dstMsg);
    if (ROK != ret) {
      UE_LOG_ERROR(ueAppCb, "Uplink Security Failed");
      EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
      pdnDisconnectReqEvnt->pdu = NULLP;
      CM_FREE_NASEVNT(&pdnDisconnectReqEvnt);
      RETVALUE(ret);
    }
    EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
    nasEncPdu.val = dstMsg.val;
    nasEncPdu.len = dstMsg.len;
  }
  CM_FREE_NASEVNT(&pdnDisconnectReqEvnt);

  nbUePdnDisconnectReq = (NbuUlNasMsg *)ueAlloc(sizeof(NbuUlNasMsg));
  nbUePdnDisconnectReq->ueId = ueId;
  nbUePdnDisconnectReq->nasPdu.pres = TRUE;
  nbUePdnDisconnectReq->nasPdu.len = nasEncPdu.len;
  nbUePdnDisconnectReq->nasPdu.val =
      (U8 *)ueAlloc(nbUePdnDisconnectReq->nasPdu.len);
  cmMemcpy((U8 *)nbUePdnDisconnectReq->nasPdu.val, nasEncPdu.val,
           nbUePdnDisconnectReq->nasPdu.len);

  if (isPlainMsg) {
    EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
  }

  ret = ueSendUlNasMsgToNb(nbUePdnDisconnectReq, &ueAppCb->nbPst);
  if (ret != ROK) {
    UE_LOG_ERROR(ueAppCb, "Sending PDN Disconnect Req to enbAPP failed");
    ret = RFAILED;
  } else {
    // Decrement pdns
    ueCb->numPdns --;
  }
  UE_LOG_EXITFN(ueAppCb, ret);
} /* End of ueProcUePdnDisconnectReq */

/*
 *
 *       Fun: ueAppEsmHndlOutPDNDisConnectReq
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppEsmHndlOutPDNDisConnectReq(UeEsmCb *esmCb, CmNasEvnt *evnt)
{
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "PDN disconnect request");

   /* Update procedure transaction state */
   esmCb->pState = UE_ESM_ST_PROC_TXN_PENDING;

  /* Updating transaction Id to event */
   evnt->m.esmEvnt->prTxnId = esmCb->tId;
   UE_LOG_EXITFN(ueAppCb, ROK);
} /* ueAppEsmHndlOutPDNDisConnectReq */

 /*
 *
 *       Fun: ueAppEsmHndlOutPDNDisconRej
 *
 *       Desc: Handles PDN Disconnect Rej message
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueAppEsmHndlIncPdnDisconRej
(
 UeEsmCb *esmCb,
 CmNasEvnt *evnt,
 UeCb *ueCb
)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb   = NULLP;
   UetMessage *tfwMsg = NULLP;
   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   TRC2(ueAppEsmHndlIncPdnDisconRej)

   UE_LOG_DEBUG(ueAppCb, "PDN Disconnect Reject");

   /* Update procedure transaction state */
   esmCb->pState = UE_ESM_ST_PROC_TXN_INACTIVE;
   /* send pdn disconnection reject indication to user */
   tfwMsg = (UetMessage*)ueAlloc(sizeof(UetMessage));
   tfwMsg->msg.ueUetPdnDisconnectRej.ueId = ueCb->ueId;
   tfwMsg->msg.ueUetPdnDisconnectRej.cause    = \
     evnt->m.esmEvnt->u.disconRej.cause.val;
   tfwMsg->msgType = UE_PDN_DISCONNECT_REJ_TYPE;
   ret = ueSendToTfwApp(tfwMsg, &ueAppCb->fwPst);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Sending PDN Disconnect Reject to "\
            "TFWAPP failed");
   }
   RETVALUE(ROK);
} /* ueAppEsmHndlIncPdnDisconRej */

void ueSendErabSetupRspForFailedBearers(NbuErabsInfo *pNbuErabsInfo) {
  S16 ret = ROK;
  UetMessage *tfwMsg = NULLP;
  UeAppCb *ueAppCb = NULLP;
  UE_GET_CB(ueAppCb);
  UE_LOG_ENTERFN(ueAppCb);
  tfwMsg = (UetMessage *)ueAlloc(sizeof(UetMessage));
  cmMemset((U8 *)tfwMsg, 0, sizeof(UetMessage));
  tfwMsg->msgType = UE_ERAB_SETUP_REQ_FAILED_FOR_ERABS;
  tfwMsg->msg.ueErabsFailedToSetup.ueId = pNbuErabsInfo->ueId;
  tfwMsg->msg.ueErabsFailedToSetup.noOfFailedErabs =
      pNbuErabsInfo->failedErabList->noOfFailedErabs;
  for (int indx = 0; indx < pNbuErabsInfo->failedErabList->noOfFailedErabs;
       indx++) {
    tfwMsg->msg.ueErabsFailedToSetup.failedErablist[indx].qci =
        pNbuErabsInfo->failedErabList->failedErabs[indx].qci;
    tfwMsg->msg.ueErabsFailedToSetup.failedErablist[indx].erabId =
        pNbuErabsInfo->failedErabList->failedErabs[indx].erabId;
    tfwMsg->msg.ueErabsFailedToSetup.failedErablist[indx].cause =
        pNbuErabsInfo->failedErabList->failedErabs[indx].cause.val.radioNw;
  }
  ret = ueSendToTfwApp(tfwMsg, &ueAppCb->fwPst);
  if (ret != ROK) {
    UE_LOG_ERROR(ueAppCb,
                 "Sending an indication,"
                 "E_RAB_SETUP_REQ_FAILED_FOR_BEARERS to TFWAPP for ueId:%u \n",
                 pNbuErabsInfo->ueId);
  }
  RETVOID;
}

/*
 *
 *       Fun: ueProcUeStandAloneActvDfltBerCtxtRej
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueProcUeStandAloneActvDfltBerCtxtRej(UetMessage *p_ueMsg,
                                                 Pst *pst) {
  S16 ret = ROK;
  U32 ueId;
  UeAppCb *ueAppCb = NULLP;
  UeCb *ueCb = NULLP;

  UE_GET_CB(ueAppCb);
  UE_LOG_ENTERFN(ueAppCb);
  UE_LOG_DEBUG(ueAppCb, "Processing standalone activate default EPS bearer "
                        "context reject message from TFWAPP");

  ueId = p_ueMsg->msg.ueActDfltBerRej.ueId;
  ret = ueDbmFetchUe(ueId, (PTR *)&ueCb);
  if (ret != ROK) {
    UE_LOG_ERROR(ueAppCb, "UeCb List NULL ueId = %d", ueId);
    RETVALUE(ret);
  }
  ueCb->is_actv_dflt_eps_ber_ctxt_rej = TRUE;
  ueCb->actv_dflt_eps_bear_ctxt_reject_cause =
      p_ueMsg->msg.ueActDfltBerRej.esmCause;

  UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueAppBuildAndSendActDefltBerContextReject
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */

PRIVATE S16 ueAppBuildAndSendActDefltBerContextReject(UeCb *ueCb, U8 bearerId) {
  S16 ret = ROK;
  U8 isPlainMsg = TRUE;
  UeAppMsg srcMsg;
  UeAppMsg dstMsg;
  UeAppCb *ueAppCb = NULLP;
  CmNasEvnt *bearerRejEvnt = NULLP;
  NhuDedicatedInfoNAS nasEncPdu;
  NbuUlNasMsg *nbUeBearerRejReq = NULLP;

  UE_GET_CB(ueAppCb);
  UE_LOG_ENTERFN(ueAppCb);

  ret = ueAppUtlBldActDfltBerContextReject(ueCb, &bearerRejEvnt, bearerId);
  if (ret != ROK) {
    UE_LOG_ERROR(ueAppCb, "Building Activate Default Bearer Reject failed");
    RETVALUE(ret);
  }

  bearerRejEvnt->secHT = CM_NAS_SEC_HDR_TYPE_INT_PRTD_ENC;
  if ((ret = ueAppEsmHdlOutUeEvnt(bearerRejEvnt, ueCb)) != ROK) {
    UE_LOG_ERROR(ueAppCb, "Handling Activate Default Bearer Reject failed \n");
    RETVALUE(RFAILED);
  }

  cmMemset((U8 *)&nasEncPdu, 0, sizeof(NhuDedicatedInfoNAS));

  /* Encode the PDU */
  ret = ueAppEdmEncode(bearerRejEvnt, &nasEncPdu);
  if (ret != ROK) {
    UE_LOG_ERROR(ueAppCb, "Activate Default Bearer Reject Failed");
    CM_FREE_NASEVNT(&bearerRejEvnt);
    RETVALUE(ret);
  }
  /** Integrity Protected **/
  if (CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG != bearerRejEvnt->secHT) {
    isPlainMsg = FALSE;
    srcMsg.val = nasEncPdu.val;
    srcMsg.len = nasEncPdu.len;
    ret = ueAppCmpUplnkSec(&ueCb->secCtxt, bearerRejEvnt->secHT, &srcMsg,
                           &dstMsg);
    if (ROK != ret) {
      UE_LOG_ERROR(ueAppCb, "Uplink Security Failed");
      EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
      bearerRejEvnt->pdu = NULLP;
      CM_FREE_NASEVNT(&bearerRejEvnt);
      RETVALUE(ret);
    }
    EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
    nasEncPdu.val = dstMsg.val;
    nasEncPdu.len = dstMsg.len;
  }
  CM_FREE_NASEVNT(&bearerRejEvnt);

  nbUeBearerRejReq = (NbuUlNasMsg *)ueAlloc(sizeof(NbuUlNasMsg));
  nbUeBearerRejReq->ueId = ueCb->ueId;
  nbUeBearerRejReq->nasPdu.pres = TRUE;
  nbUeBearerRejReq->nasPdu.len = nasEncPdu.len;
  nbUeBearerRejReq->nasPdu.val = (U8 *)ueAlloc(nbUeBearerRejReq->nasPdu.len);
  cmMemcpy((U8 *)nbUeBearerRejReq->nasPdu.val, nasEncPdu.val,
           nbUeBearerRejReq->nasPdu.len);

  if (isPlainMsg) {
    EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
  }

  ret = ueSendUlNasMsgToNb(nbUeBearerRejReq, &ueAppCb->nbPst);
  if (ret != ROK) {
    UE_LOG_ERROR(ueAppCb, "Sending Activate Default Berarer Reject to "
                          "Enodeb Failed");
    ret = RFAILED;
  }

  UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueProcDropActDefaultEpsBerCtxtReq
 *
 *       Desc:
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */
PRIVATE S16 ueProcDropActDefaultEpsBerCtxtReq(UetMessage *p_ueMsg, Pst *pst) {
  S16 ret = ROK;
  U32 ueId;
  UeAppCb *ueAppCb = NULLP;
  UeCb *ueCb = NULLP;

  UE_GET_CB(ueAppCb);
  UE_LOG_ENTERFN(ueAppCb);
  UE_LOG_DEBUG(
      ueAppCb,
      "Received an indication from TFWAPP to drop activate default EPS bearer "
      "context request message \n");

  ueId = p_ueMsg->msg.ueDropActDfltBerReq.ueId;
  ret = ueDbmFetchUe(ueId, (PTR *)&ueCb);
  if (ret != ROK) {
    UE_LOG_ERROR(ueAppCb, "UeCb List NULL ueId = %d", ueId);
    RETVALUE(ret);
  }
  ueCb->is_drop_actv_dflt_eps_ber_ctxt_req =
      p_ueMsg->msg.ueDropActDfltBerReq.dropActDfltEpsBearCtxtReq;

  UE_LOG_EXITFN(ueAppCb, ret);
}

/*
 *
 *       Fun: ueUiProcRelBearerRsp
 *
 *       Desc: Handles RelBearerRsp received from enbApp
 *             and sends TAU request message
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_app.c
 *
 */

PUBLIC S16 ueUiProcRelBearerRsp(UeCb *ueCb, NbuRelBearerRsp *relBearerRsp) {
  UeAppCb *ueAppCb = NULLP;
  CmNasEvnt *tauReqEvnt = NULLP;
  NbuInitialUeMsg *nbUeTauReq = NULLP;
  NbuUlNasMsg *nbUeTauReqUlNas = NULLP;
  NhuDedicatedInfoNAS nasEncPdu;
  UeAppMsg srcMsg;
  UeAppMsg dstMsg;
  U8 isPlainMsg = TRUE;
  S16 ret = ROK;

  UE_GET_CB(ueAppCb);
  UE_LOG_ENTERFN(ueAppCb);

  U32 ueId = relBearerRsp->ueId;
  if (ueDbmFetchUe(ueId, (PTR *)&ueCb) != ROK) {
    UE_LOG_ERROR(ueAppCb, "UeCb List NULL ueId = %d", ueId);
    RETVALUE(RFAILED);
  }
  // Send TAU request
  if (!ueCb->ueUetTauRequest) {
    UE_LOG_ERROR(ueAppCb, "TAU Request stored in ueCb is NULL for ueId=%d",
                 ueId);
    RETVALUE(RFAILED);
  }
  if (ueAppUtlBldTauReq(ueCb, &tauReqEvnt, ueCb->ueUetTauRequest) != ROK) {
    UE_LOG_ERROR(ueAppCb, "TAU Request Building failed");
    RETVALUE(RFAILED);
  }
  cmMemset((U8 *)&nasEncPdu, 0, sizeof(NhuDedicatedInfoNAS));
  // Encode the PDU
  if (ueAppEdmEncode(tauReqEvnt, &nasEncPdu) != ROK) {
    UE_LOG_ERROR(ueAppCb, "TAU Request Encode Failed\n");
    CM_FREE_NASEVNT(&tauReqEvnt);
    RETVALUE(RFAILED);
  }

  // Integrity Protected
  if (CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG != tauReqEvnt->secHT) {
    isPlainMsg = FALSE;
    srcMsg.val = nasEncPdu.val;
    srcMsg.len = nasEncPdu.len;
    if (ueAppCmpUplnkSec(&ueCb->secCtxt, tauReqEvnt->secHT, &srcMsg, &dstMsg) !=
        ROK) {
      UE_LOG_ERROR(ueAppCb, "Uplink Security Failed");
      EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
      tauReqEvnt->pdu = NULLP;
      CM_FREE_NASEVNT(&tauReqEvnt);
      RETVALUE(RFAILED);
    }
    EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
    nasEncPdu.val = dstMsg.val;
    nasEncPdu.len = dstMsg.len;
  }
  CM_FREE_NASEVNT(&tauReqEvnt);

  nbUeTauReq = (NbuInitialUeMsg *)ueAlloc(sizeof(NbuInitialUeMsg));
  if (!nbUeTauReq) {
    UE_LOG_ERROR(ueAppCb,
                 "Memory allocation failed for TAU Request for ueId=%d", ueId);
    RETVALUE(RFAILED);
  }
  nbUeTauReq->ueId = ueId;
  nbUeTauReq->rrcCause = 3;

  nbUeTauReq->stmsi.pres = TRUE;
  nbUeTauReq->stmsi.mmec = ueCb->ueCtxt.ueGuti.mmeCode;
  if (ueCb->ueUetTauRequest->ueMtmsi.pres == TRUE) {
    nbUeTauReq->stmsi.mTMSI = ueCb->ueUetTauRequest->ueMtmsi.mTmsi;
  } else {
    nbUeTauReq->stmsi.mTMSI = ueCb->ueCtxt.ueGuti.mTMSI;
  }

  nbUeTauReq->nasPdu.pres = TRUE;
  nbUeTauReq->nasPdu.len = nasEncPdu.len;
  nbUeTauReq->nasPdu.val = (U8 *)ueAlloc(nbUeTauReq->nasPdu.len);
  cmMemcpy((U8 *)nbUeTauReq->nasPdu.val, nasEncPdu.val, nbUeTauReq->nasPdu.len);

  if (isPlainMsg) {
    EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
  }

  if (ueCb->ecmCb.state == UE_ECM_IDLE) {
    UE_LOG_DEBUG(ueAppCb, "Sending TAU in initial ue message");
    ret = ueSendInitialUeMsg(nbUeTauReq, &ueAppCb->nbPst);
  } else if (ueCb->ecmCb.state == UE_ECM_CONNECTED) {
    nbUeTauReqUlNas = (NbuUlNasMsg *)ueAlloc(sizeof(NbuUlNasMsg));
    nbUeTauReqUlNas->ueId = ueId;
    nbUeTauReqUlNas->nasPdu.pres = TRUE;
    nbUeTauReqUlNas->nasPdu.len = nasEncPdu.len;
    nbUeTauReqUlNas->nasPdu.val = (U8 *)ueAlloc(nbUeTauReqUlNas->nasPdu.len);
    cmMemcpy((U8 *)nbUeTauReqUlNas->nasPdu.val, (U8 *)nasEncPdu.val,
             nbUeTauReqUlNas->nasPdu.len);

    UE_LOG_DEBUG(ueAppCb, "Sending TAU in UL NAS message for ueId=%d", ueId);
    ret = ueSendUlNasMsgToNb(nbUeTauReqUlNas, &ueAppCb->nbPst);
  }
  if (ret != ROK) {
    UE_LOG_ERROR(ueAppCb, "Sending TAU Request to eNodeB failed=%d\n", ueId);
    UE_LOG_EXITFN(ueAppCb, RFAILED);
    ;
  }
  ueFree((U8 *)ueCb->ueUetTauRequest, sizeof(UeUetTauRequest));
  UE_LOG_EXITFN(ueAppCb, ROK);
}

