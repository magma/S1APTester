/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

/********************************************************************20**

    Name:  LTE S1SIM - TFW API
 
    Type:  C include file
 
    Desc:  C source code for Test Framework interface API with Stub.
 
    File:  fw_api_int.c
 
    Sid:   
 
    Prg:   
 
**********************************************************************/

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_hash.h"       /* common hashing */
#include "cm_llist.h"      /* common linked list */
#include "cm_mblk.h"       /* common  */
#include "cm5.h"           /* common timer */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_inet.h"       /* common sockets */
#include "cm_dns.h"        /* common DNS Library */
#include "cm_tkns.h"
#include "ss_queue.h"      /* queues */
#include "ss_task.h"       /* tasking */
#include "ss_msg.h"        /* messaging */
#include "ss_mem.h"        /* memory management interface */
#include "ss_gen.h"        /* general */
#include "rl_interface.h"
#include "rl_common.h"
#include "lfw.h"
#include "uet.h"
#include "nbt.h"
#include "fw_api_int.h"
#include "fw.h"
#include "fw_tmr.h"

#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_hash.x"       /* common hashing */
#include "cm_llist.x"      /* common linked list */
#include "cm_lib.x"        /* common library */
#include "cm5.x"           /* common timer */
#include "cm_tpt.x"        /* common transport typedefs */
#include "cm_inet.x"       /* common sockets */
#include "cm_mblk.x"       /* common blk memory */
#include "cm_dns.x"        /* common DNS Library */
#include "cm_tkns.x"
#include "ss_queue.x"      /* queues */
#include "ss_task.x"       /* tasking */
#include "ss_timer.x"      /* timers */
#include "ss_strm.x"       /* STREAMS */
#include "ss_msg.x"        /* messaging */
#include "ss_mem.x"        /* memory management interface */
#include "ss_drvr.x"       /* driver tasks */
#include "ss_gen.x"        /* general */
#include "lfw.x"
#include "uet.x"
#include "nbt.x"
#include "fw_read_dflcfg.h"
#include "fw_api_int.x"
#include "fw.x"
#include "fw_tmr.x"
#include "fw_log.h"

PUBLIC S16 handleUeAppConfig(ueAppConfig_t*);
PUBLIC S16 handleUeConfig(ueConfig_t *);
PUBLIC S16 handleUeRadCapConfig(ueRadCapUpd_t *);
EXTERN Void fwHndlPdnTmrExp(PTR  cb);
PUBLIC S16 handlEnbConfig(FwNbConfigReq_t *);
PUBLIC S16 handlEnbInactvTmrCfg(FwNbConfigReq_t *);
PRIVATE S16 handlS1SetupReq(Void);
PRIVATE Void handlPdnConReq(uepdnConReq_t* data);
PRIVATE S16 handlErrIndMsg(fwNbErrIndMsg_t *data);
PRIVATE S16 handleUeActvDedBerAcc(UeActDedBearCtxtAcc_t* data);
PRIVATE S16 handleUeActvDedBerRej(UeActDedBearCtxtRej_t* data);
PRIVATE S16 handleSctpAbortReq(FwSctpAbortReq_t* data);
PRIVATE S16 handleSctpShutdownReq(Void);
PUBLIC S16 handleUeResAllocReq(ueBearerAllocReq_t *data);
PUBLIC Void handleUeNasNonDelivery(UeNasNonDel* data);
PUBLIC Void handleUeInitCtxtSetupFail(ueInitCtxtSetupFail* data);
PRIVATE Void handleDropUeInitCtxtSetupReq(UeDropInitCtxtSetup* data);
PRIVATE Void handleDelayUeInitCtxtSetupRsp(UeDelayInitCtxtSetupRsp* data);
PRIVATE Void handleSetCtxtRelForICS(UeSetCtxtRelForInitCtxtSetup* data);
PRIVATE Void handleDelayUeCtxtRelCmp(UeDelayUeCtxtRelCmp* data);
PRIVATE S16 handleUeDeActvBerAcc(UeDeActvBearCtxtAcc_t* data);
PRIVATE Void handleEsmInformationRsp(ueEsmInformationRsp_t* data);
PRIVATE Void handleMultiEnbConfigReq(multiEnbConfigReq_t* data);
PUBLIC Void handleX2HoTriggerReq(NbX2HOTriggerReq* data);
PRIVATE S16 handleActvDfltEpsBearerContextAcc(UeActDefEpsBearCtxtAcc_t* data);
PRIVATE Void handlPdnDisconnectReq(uepdnDisconnectReq_t* data);
EXTERN Void fwHndlPdnDisconnTmrExp(PTR  cb);
PUBLIC FwCb gfwCb;

/* Adding UEID, epsupdate type, active flag into linked list for 
 * TAU request
 */
PRIVATE Void insertUeCb(U8 ueid, U8 epsUpdType, U8 flag, UeIdCb *ueIdCb)
{
   FwCb *fwCb = NULLP;
   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);
   
   ueIdCb->ue_id = ueid;
   ueIdCb->epsUpdType = epsUpdType;
   ueIdCb->ActvFlag = flag;
   ueIdCb->link.node = (PTR)ueIdCb;

   cmLListAdd2Tail(&fwCb->ueIdList, &ueIdCb->link);
   FW_LOG_EXITFNVOID(fwCb);
}

/*
 * 
 *   Fun:   handlTauReq
 * 
 *   Desc:  This function is used to handle Tracking area update request 
 *          from Test Controller.
 * 
 *   Ret:   None
 * 
 *   Notes: None
 * 
 *   File:  fw_api_int.c
 * 
 */
PUBLIC S16 handlTauReq(ueTauReq_t* data)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   UetMessage *uetMsg = NULLP;
   UeUetTauRequest *ueTauReq = NULLP;
   UeIdCb *ueIdCb = NULLP;
   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &uetMsg, sizeof(UetMessage));
   uetMsg->msgType = UE_TAU_REQUEST_TYPE;
   ueTauReq = &uetMsg->msg.ueUetTauRequest;
   FW_ALLOC_MEM(fwCb, &ueIdCb, sizeof(UeIdCb));
   insertUeCb(data->ue_Id, data->type, data->Actv_flag, ueIdCb);

   ueTauReq->ueId = data->ue_Id;
   ueTauReq->ueMtmsi.pres = data->ueMtmsi.pres;
   ueTauReq->ueMtmsi.mTmsi = data->ueMtmsi.mTmsi;
   ueTauReq->epsUpdtType = data->type;
   ueTauReq->ActvFlag = data->Actv_flag;
   fwSendToUeApp(uetMsg);
   
   FW_LOG_DEBUG(fwCb, "\n-------------------------------\n\
            Starting T3430\n-------------------------------\n");
   ret = fwStartTmr(fwCb, ueIdCb, fwHndlTauTmrExp, 2000000);
   if (ROK != ret)
   {
      FW_LOG_ERROR(fwCb, "Failed to start T3430 timer");
   }
   FW_LOG_EXITFN(fwCb, ROK);
} 

/*
 *   Fun:   handlTauComp
 * 
 *   Desc:  This function is used to handle Tracking area update complete 
 *          from Test Controller.
 * 
 *   Ret:   None
 * 
 *   Notes: None
 * 
 *   File:  fw_api_int.c
 * 
 */
PUBLIC S16 handlTauComp(ueTauComplete_t* data)
{
   FwCb *fwCb = NULLP;
   UetMessage *uetMsg = NULLP;
   UeUetTauComplete *ueTauComp = NULLP;
   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &uetMsg, sizeof(UetMessage));
   uetMsg->msgType = UE_TAU_COMPLETE_TYPE;
   ueTauComp = &uetMsg->msg.ueUetTauComplete;

   ueTauComp->ueId = data->ue_Id;

   fwSendToUeApp(uetMsg);
   FW_LOG_EXITFN(fwCb, ROK);
}

/*
 * 
 *   Fun:   handlServiceReq
 * 
 *   Desc:  This function is used to handle Service request 
 *          from Test Controller 
 * 
 *   Ret:   None
 * 
 *   Notes: None
 * 
 *   File:  fw_api_int.c
 * 
 */
PUBLIC Void handlServiceReq(ueserviceReq_t* data)
{
   FwCb *fwCb = NULLP;
   UetMessage *uetMsg = NULLP;
   UeUetServiceReq *ueServiceReq = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   if(SGetSBuf(fwCb->init.region, fwCb->init.pool, 
       (Data **)&uetMsg, (Size) sizeof(UetMessage)) == ROK) 
   {                                                  
      cmMemset((U8 *)(uetMsg), 0, sizeof(UetMessage));              
   }
   else
   {
      RETVOID;
   }   
   uetMsg->msgType = UE_SERVICE_REQUEST_TYPE;
   ueServiceReq = &uetMsg->msg.ueUetServiceReq;

   ueServiceReq->ueId = data->ue_Id;
   ueServiceReq->ueMtmsi.pres = data->ueMtmsi.pres;
   ueServiceReq->ueMtmsi.mTmsi = data->ueMtmsi.mTmsi;
   ueServiceReq->rrcCause = data->rrcCause;

   fwSendToUeApp(uetMsg);
   RETVOID;
}

/*
 * 
 *   Fun:   handlUeCntxtRelReq
 * 
 *   Desc:  This function is used to handle Service request 
 *          from Test Controller 
 * 
 *   Ret:   None
 * 
 *   Notes: None
 * 
 *   File:  fw_api_int.c
 * 
 */
PUBLIC Void handlUeCntxtRelReq(ueCntxtRelReq_t* data)
{
   FwCb *fwCb = NULLP;
   NbtRequest *msgReq = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);
   
   if(SGetSBuf(fwCb->init.region, fwCb->init.pool, 
       (Data **)&msgReq, (Size)sizeof(NbtRequest)) == ROK) 
   {                                                  
      cmMemset((U8 *)(msgReq), 0, sizeof(NbtRequest));              
   }
   else
   {
      FW_LOG_ERROR(fwCb, "Failed to allocate memory");
      RETVOID;
   }

   msgReq->msgType = NB_UE_CNTXT_REL_REQ;
   msgReq->t.ueCntxtRelReq.ueId = data->ue_Id;
   msgReq->t.ueCntxtRelReq.cause.causeType = data->cause.causeType;
   msgReq->t.ueCntxtRelReq.cause.causeVal = data->cause.causeVal;

   fwSendToNbApp(msgReq);
   RETVOID;
}

/*
 * 
 *   Fun:   handlDetachReq
 * 
 *   Desc:  This function is used to handle Detach request 
 *          from Test Controller 
 * 
 *   Ret:   None
 * 
 *   Notes: None
 * 
 *   File:  fw_api_int.c
 * 
 */
PUBLIC S16 handlDetachReq(uedetachReq_t* data)
{
   FwCb *fwCb = NULLP;
   UetMessage *uetMsg = NULLP;
   UeUetDetachReq *ueDetachReq = NULLP;
   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &uetMsg, sizeof(UetMessage));
   uetMsg->msgType = UE_DETACH_REQUEST_TYPE;
   ueDetachReq = &uetMsg->msg.ueUetDetachReq;

   ueDetachReq->ueId = data->ue_Id;
   ueDetachReq->ueDetType = data->ueDetType;

   fwSendToUeApp(uetMsg);
   FW_LOG_EXITFN(fwCb, ROK);
}

/*
 * 
 *   Fun:   handlAttachComp
 * 
 *   Desc:  This function is used to handle Attach complete message 
 *          from Test Controller 
 * 
 *   Ret:   None
 * 
 *   Notes: None
 * 
 *   File:  fw_api_int.c
 * 
 */
PUBLIC S16 handlAttachComp(ueAttachComplete_t *data)
{
   FwCb *fwCb = NULLP;
   UetMessage *uetMsg = NULLP;
   UeUetAttachComplete *ueAttachComp = NULLP;
   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &uetMsg, sizeof(UetMessage));
   uetMsg->msgType = UE_ATTACH_COMPLETE_TYPE;
   ueAttachComp = &uetMsg->msg.ueUetAttachComplete;

   ueAttachComp->ueId = data->ue_Id;

   fwSendToUeApp(uetMsg);
   FW_LOG_EXITFN(fwCb, ROK);
}
/*
 * 
 *   Fun:   handleActvDfltEpsBearerContextRej
 * 
 *   Desc:  This function is used to handle Attach complete + Activate Default Eps Bearer context reject message 
 *          from Test Controller 
 * 
 *   Ret:   None
 * 
 *   Notes: None
 * 
 *   File:  fw_api_int.c
 * 
 */
PUBLIC S16 handleActvDfltEpsBearerContextRej(ueActvDfltEpsBearerCtxtRej_t *data)
{
   FwCb *fwCb = NULLP;
   UetMessage *uetMsg = NULLP;
   UeEsmActDfltBearCtxtRej *ueActDfltBearCtxtRej = NULLP;
   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &uetMsg, sizeof(UetMessage));
   uetMsg->msgType = UE_EPS_DEFAULT_BER_REJ;
   ueActDfltBearCtxtRej = &uetMsg->msg.ueActDfltBerRej;

   ueActDfltBearCtxtRej->ueId = data->ue_Id;
   ueActDfltBearCtxtRej->bearerId = data->bearerId;
   ueActDfltBearCtxtRej->esmCause = data->cause;

   fwSendToUeApp(uetMsg);
   FW_LOG_EXITFN(fwCb, ROK);
}
/*
 * 
 *   Fun:   handlIdentResp
 * 
 *   Desc:  This function is used to handle Identity Response coming from
 *          Test Controller.
 * 
 *   Ret:   None
 * 
 *   Notes: None
 * 
 *   File:  fw_api_int.c
 * 
 */
PUBLIC S16 handlIdentResp(ueIdentityResp_t *data)
{
   FwCb *fwCb = NULLP;
   UetMessage *uetMsg = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &uetMsg, sizeof(UetMessage));
   uetMsg->msgType = UE_IDENTITY_RES_TYPE;

   uetMsg->msg.ueUetIdentRsp.ueId = data->ue_Id;
   uetMsg->msg.ueUetIdentRsp.idType = data->idType;

   fwSendToUeApp(uetMsg);

   RETVALUE(ROK);
}

/*
 * 
 *   Fun:   handlSecModComp
 * 
 *   Desc:  This function is used to handle Security mode complete 
 *          from Test Controller 
 * 
 *   Ret:   None
 * 
 *   Notes: None
 * 
 *   File:  fw_api_int.c
 * 
 */
PUBLIC S16 handlSecModComp(ueSecModeComplete_t *data)
{
   FwCb *fwCb = NULLP;
   UetMessage *uetMsg = NULLP;
   UeUetSecModeComplete *ueSecModComp = NULLP;
   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &uetMsg, sizeof(UetMessage));
   uetMsg->msgType = UE_SEC_MOD_CMP_TYPE;
   ueSecModComp = &uetMsg->msg.ueUetSecModeComplete;

   ueSecModComp->ueId = data->ue_Id;

   fwSendToUeApp(uetMsg);
   FW_LOG_EXITFN(fwCb, ROK);
}

/*
 * 
 *   Fun:   handlSecModRej
 * 
 *   Desc:  This function is used to handle Security mode Reject 
 *          from Test Controller 
 * 
 *   Ret:   None
 * 
 *   Notes: None
 * 
 *   File:  fw_api_int.c
 * 
 */
PUBLIC S16 handlSecModRej(ueSecModeReject_t *data)
{
   FwCb *fwCb = NULLP;
   UetMessage *uetMsg = NULLP;
   UeUetSecModeReject *ueSecModRej = NULLP;
   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &uetMsg, sizeof(UetMessage));
   uetMsg->msgType = UE_SEC_MOD_REJ_TYPE;
   ueSecModRej = &uetMsg->msg.ueUetSecModeReject;

   ueSecModRej->ueId = data->ue_Id;
   ueSecModRej->cause = data->cause;

   fwSendToUeApp(uetMsg);
   FW_LOG_EXITFN(fwCb, ROK);
}

/*
 * 
 *   Fun:   handlAuthResp
 * 
 *   Desc:  This function is used to handle Auth Response
 *          from Test Controller 
 * 
 *   Ret:   None
 * 
 *   Notes: None
 * 
 *   File:  fw_api_int.c
 * 
 */
PUBLIC S16 handlAuthResp(ueAuthResp_t *data)
{
   FwCb *fwCb = NULLP;
   UetMessage *uetMsg = NULLP;
   /*UeUetAuthRsp *ueAuthResp = NULLP;*/
   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &uetMsg, sizeof(UetMessage));
   uetMsg->msgType = UE_AUTH_RES_TYPE;

   uetMsg->msg.ueUetAuthRsp.ueId = data->ue_Id;
   uetMsg->msg.ueUetAuthRsp.nonEPSAuthFail = data->nonEPSAuthFail;
   if(data->sqnRcvd.pres == TRUE)
   {
      uetMsg->msg.ueUetAuthRsp.sqnRcvd.pres = TRUE;
      cmMemcpy(uetMsg->msg.ueUetAuthRsp.sqnRcvd.sqn, data->sqnRcvd.sqn, 6);
   }
   else
   {
      uetMsg->msg.ueUetAuthRsp.sqnRcvd.pres = FALSE;
   }
   if(data->maxSqnRcvd.pres == TRUE)
   {
      uetMsg->msg.ueUetAuthRsp.maxSqnRcvd.pres = TRUE;
      cmMemcpy(uetMsg->msg.ueUetAuthRsp.maxSqnRcvd.sqn, data->maxSqnRcvd.sqn, 6);
   }
   else
   {
      uetMsg->msg.ueUetAuthRsp.maxSqnRcvd.pres = FALSE;
   }
   if(data->randRcvd.pres == TRUE)
   {
      uetMsg->msg.ueUetAuthRsp.randRcvd.pres = TRUE;
      cmMemcpy(uetMsg->msg.ueUetAuthRsp.randRcvd.val, data->randRcvd.val, 16);
   }
   else
   {
      uetMsg->msg.ueUetAuthRsp.randRcvd.pres = FALSE;
   }
   

   fwSendToUeApp(uetMsg);
   RETVALUE(ROK);
}

/*
 * 
 *   Fun:   handlRadCapUpd
 * 
 *   Desc:  This function is used to handle UE Radio Capability Update
 *          from Test Controller 
 * 
 *   Ret:   None
 * 
 *   Notes: None
 * 
 *   File:  fw_api_int.c
 * 
 */
PUBLIC S16 handlRadCapUpd(ueRadCapUpd_t *data)
{
   FwCb *fwCb = NULLP;
   UetMessage *uetMsg = NULLP;
   /*UeUetAuthRsp *ueAuthResp = NULLP;*/
   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &uetMsg, sizeof(UetMessage));
   uetMsg->msgType = UE_RAD_CAP_UPD_TYPE;

   uetMsg->msg.ueUetRadCapUpdReq.ueId = data->ue_Id;
   uetMsg->msg.ueUetRadCapUpdReq.send_s1ap_msg = data->snd_S1AP;
   if (data->radioCap_pr.pres == TRUE)
   	{
   	   FW_ALLOC_MEM(fwCb, &(uetMsg->msg.ueUetRadCapUpdReq.radCapMsg), data->radioCap_pr.len);
	   cmMemcpy(uetMsg->msg.ueUetRadCapUpdReq.radCapMsg,data->radioCap_pr.radioCapMsg,data->radioCap_pr.len);
	   uetMsg->msg.ueUetRadCapUpdReq.upd_ueRadCap = TRUE;
   	}
   fwSendToUeApp(uetMsg);
   RETVALUE(ROK);
}

/* Adding UEID into linked list for END TO END ATTACH */
PRIVATE Void insert_ue_entry(U8 ueid, UeIdCb *ueIdCb)
{
   FwCb *fwCb = NULLP;
   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);
   
   ueIdCb->ue_id = ueid;
   ueIdCb->state = UE_ATTACH_REQUEST_DONE;
   ueIdCb->link.node = (PTR)ueIdCb;

   cmLListAdd2Tail(&fwCb->ueIdList, &ueIdCb->link);
   FW_LOG_EXITFNVOID(fwCb);
}

/*
 *
 *   Fun:   handleEndToEndAttachReq
 *
 *   Desc:  This function is used to handle Attach request 
 *          from Test Controller 
 *
 *   Ret:   None
 *
 *   Notes: None
 *
 *   File:  fw_api_int.c
 *
 */
PUBLIC S16 handleEndToEndAttachReq(ueAttachRequest_t *data)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   UeIdCb *ueIdCb = NULLP;
   UetMessage *uetMsg = NULLP;
   UeUetAttachReq *ueAttachReq = NULLP;
   U8 count;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   /* cmLListInit(&fwCb->ueIdList);*/
   FW_ALLOC_MEM(fwCb, &ueIdCb, sizeof(UeIdCb));
   insert_ue_entry(data->ue_Id, ueIdCb);

   FW_ALLOC_MEM(fwCb, &uetMsg, sizeof(UetMessage));

   uetMsg->msgType = UE_ATTACH_REQ_TYPE;
   ueAttachReq = &uetMsg->msg.ueUetAttachReq;

   /* mandatory feilds */
   ueAttachReq->ueId = data->ue_Id;
   ueAttachReq->mIdType = data->mIdType;
   ueAttachReq->epsAtchType.type = data->epsAttachType;
   ueAttachReq->useOldSecCtxt = data->useOldSecCtxt;

   /* optional feilds */
   if (data->guti_pr.pres == TRUE)
   {
      cmMemcpy(ueAttachReq->oldGuti.mcc, data->guti_pr.guti.mcc, 3);
      cmMemcpy(ueAttachReq->oldGuti.mnc, data->guti_pr.guti.mnc, 3);
      ueAttachReq->oldGuti.mmeGrpId = data->guti_pr.guti.mmeGrdId;
      ueAttachReq->oldGuti.mmeCode = data->guti_pr.guti.mmeCode;
      ueAttachReq->oldGuti.mTMSI = data->guti_pr.guti.mTmsi;
   }
   else
   {
      cmMemcpy(ueAttachReq->oldGuti.mcc, fwCb->ueCfgCb.mcc , 3);
      cmMemcpy(ueAttachReq->oldGuti.mnc, fwCb->ueCfgCb.mnc , 3);
      ueAttachReq->oldGuti.mmeGrpId = fwCb->ueCfgCb.mmeGrpId;
      ueAttachReq->oldGuti.mmeCode = fwCb->ueCfgCb.mmeCode;
      ueAttachReq->oldGuti.mTMSI = fwCb->ueCfgCb.mTmsi;
   }

   if(data->pdnType_pr.pres == TRUE)
   {
      ueAttachReq->pdnType = data->pdnType_pr.pdn_type;
   }
   else
   {
      ueAttachReq->pdnType = fwCb->ueCfgCb.pdnType;
   }

   if (data->pdnAPN_pr.pres == TRUE)
   {
      cmMemcpy(ueAttachReq->nasPdnApn.apn, data->pdnAPN_pr.pdn_apn, \
          data->pdnAPN_pr.len);
      ueAttachReq->nasPdnApn.len = data->pdnAPN_pr.len;
   }
   else
   {
      cmMemcpy(ueAttachReq->nasPdnApn.apn, fwCb->ueCfgCb.pdnAPN, \
          strlen((S8*)fwCb->ueCfgCb.pdnAPN));
      ueAttachReq->nasPdnApn.len = strlen((S8*)fwCb->ueCfgCb.pdnAPN);
   }

   if (data->lastTAI_pr.pres == TRUE)
   {
      cmMemcpy(ueAttachReq->ueLastTai.mcc, data->lastTAI_pr.last_tai.mcc, 3);
      cmMemcpy(ueAttachReq->ueLastTai.mnc, data->lastTAI_pr.last_tai.mnc, 3);
      ueAttachReq->ueLastTai.tac = data->lastTAI_pr.last_tai.tac;
   }
   else
   {
      cmMemcpy(ueAttachReq->ueLastTai.mcc, fwCb->ueCfgCb.lastMcc, 3);
      cmMemcpy(ueAttachReq->ueLastTai.mnc, fwCb->ueCfgCb.lastMnc, 3);
      ueAttachReq->ueLastTai.tac = fwCb->ueCfgCb.lastTac;
   }
   if (data->protCfgOpts_pr.pres == TRUE)
   {
   	  ueAttachReq->protCfgOpt.pres = TRUE;
	  ueAttachReq->protCfgOpt.len = data->protCfgOpts_pr.len;
	  ueAttachReq->protCfgOpt.cfgProt = data->protCfgOpts_pr.cfgProt;
	  ueAttachReq->protCfgOpt.ext = data->protCfgOpts_pr.ext;
	  ueAttachReq->protCfgOpt.numProtId = data->protCfgOpts_pr.numProtId;
	  ueAttachReq->protCfgOpt.numContId = data->protCfgOpts_pr.numContId;
	  for (count=0;count<data->protCfgOpts_pr.numProtId;count ++)
	  {
	  	ueAttachReq->protCfgOpt.p[count].pid = data->protCfgOpts_pr.p[count].pid;
	  	ueAttachReq->protCfgOpt.p[count].len = data->protCfgOpts_pr.p[count].len;
		cmMemcpy(ueAttachReq->protCfgOpt.p[count].val, 
			   data->protCfgOpts_pr.p[count].val, 
			   data->protCfgOpts_pr.p[count].len);
	  }
	  for (count=0;count<data->protCfgOpts_pr.numContId;count ++)
	  {
	  	ueAttachReq->protCfgOpt.c[count].cid = data->protCfgOpts_pr.c[count].cid;
	  	ueAttachReq->protCfgOpt.c[count].len = data->protCfgOpts_pr.c[count].len;
		cmMemcpy(ueAttachReq->protCfgOpt.c[count].val, 
			   data->protCfgOpts_pr.c[count].val, 
			   data->protCfgOpts_pr.c[count].len);
	  }
   }
   if(data->drxParm_pr.pres)
   	{
   	  ueAttachReq->drxParm.pres = TRUE;
	  ueAttachReq->drxParm.spltPGCycle = data->drxParm_pr.spltPGCycle;
	  ueAttachReq->drxParm.nonDrxTmr = data->drxParm_pr.nonDrxTmr;
	  ueAttachReq->drxParm.spltOnCcch = data->drxParm_pr.spltOnCcch;
	  ueAttachReq->drxParm.u.drxVal = data->drxParm_pr.u.drxVal;
   	}
   if (data->eti.pres) {
     ueAttachReq->eti = TRUE;
   } else {
     ueAttachReq->eti = FALSE;
   }
   fwSendToUeApp(uetMsg);

   /* Start Attach timer */
   FW_LOG_DEBUG(fwCb, "Starting Attach Timer");
   ret = fwStartTmr(fwCb, ueIdCb, fwHndlAttachTmrExp, 2000);
   if (ROK != ret)
   {
      FW_LOG_ERROR(fwCb, "Failed to start Attach timer");
   }
   FW_LOG_EXITFN(fwCb, ROK);
}

/*
 *
 *   Fun:   handleAttachReq
 *
 *   Desc:  This function is used to handle Attach request 
 *          from Test Controller 
 *
 *   Ret:   None
 *
 *   Notes: None
 *
 *   File:  fw_api_int.c
 *
 */
PUBLIC S16 handleAttachReq(ueAttachRequest_t *data)
{
   FwCb *fwCb = NULLP;
   UetMessage *uetMsg = NULLP;
   UeUetAttachReq *ueAttachReq = NULLP;
   U8 count;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &uetMsg, sizeof(UetMessage));

   uetMsg->msgType = UE_ATTACH_REQ_TYPE;
   ueAttachReq = &uetMsg->msg.ueUetAttachReq;

   /* mandatory feilds */
   ueAttachReq->ueId = data->ue_Id;
   ueAttachReq->mIdType = data->mIdType;
   ueAttachReq->epsAtchType.type = data->epsAttachType;
   ueAttachReq->useOldSecCtxt = data->useOldSecCtxt;

   /* optional feilds */
   if (data->guti_pr.pres == TRUE)
   {
      cmMemcpy(ueAttachReq->oldGuti.mcc, data->guti_pr.guti.mcc, 3);
      cmMemcpy(ueAttachReq->oldGuti.mnc, data->guti_pr.guti.mnc, 3);
      ueAttachReq->oldGuti.mmeGrpId = data->guti_pr.guti.mmeGrdId;
      ueAttachReq->oldGuti.mmeCode = data->guti_pr.guti.mmeCode;
      ueAttachReq->oldGuti.mTMSI = data->guti_pr.guti.mTmsi;
   }
   else
   {
      cmMemcpy(ueAttachReq->oldGuti.mcc, fwCb->ueCfgCb.mcc , 3);
      cmMemcpy(ueAttachReq->oldGuti.mnc, fwCb->ueCfgCb.mnc , 3);
      ueAttachReq->oldGuti.mmeGrpId = fwCb->ueCfgCb.mmeGrpId;
      ueAttachReq->oldGuti.mmeCode = fwCb->ueCfgCb.mmeCode;
      ueAttachReq->oldGuti.mTMSI = fwCb->ueCfgCb.mTmsi;
   }

   if (data->pdnType_pr.pres == TRUE)
      ueAttachReq->pdnType = data->pdnType_pr.pdn_type;
   else
      ueAttachReq->pdnType = fwCb->ueCfgCb.pdnType;

   if (data->pdnAPN_pr.pres == TRUE)
   {
      cmMemcpy(ueAttachReq->nasPdnApn.apn, \
             data->pdnAPN_pr.pdn_apn, data->pdnAPN_pr.len);
      ueAttachReq->nasPdnApn.len = data->pdnAPN_pr.len;
   }
   else
   {
      cmMemcpy(ueAttachReq->nasPdnApn.apn, \
          fwCb->ueCfgCb.pdnAPN, strlen((S8*)fwCb->ueCfgCb.pdnAPN));
      ueAttachReq->nasPdnApn.len = strlen((S8*)fwCb->ueCfgCb.pdnAPN);
   }

   if (data->lastTAI_pr.pres == TRUE)
   {
      cmMemcpy(ueAttachReq->ueLastTai.mcc, data->lastTAI_pr.last_tai.mcc, 3);
      cmMemcpy(ueAttachReq->ueLastTai.mnc, data->lastTAI_pr.last_tai.mnc, 3);
      ueAttachReq->ueLastTai.tac = data->lastTAI_pr.last_tai.tac;
   }
   else
   {
      cmMemcpy(ueAttachReq->ueLastTai.mcc, fwCb->ueCfgCb.lastMcc, 3);
      cmMemcpy(ueAttachReq->ueLastTai.mnc, fwCb->ueCfgCb.lastMnc, 3);
      ueAttachReq->ueLastTai.tac = fwCb->ueCfgCb.lastTac;
   }
   if (data->addUpdTyp_pr.pres == TRUE)
   {
      ueAttachReq->addUpdType.pres = TRUE;
	  ueAttachReq->addUpdType.type = data->addUpdTyp_pr.type;
   }
   if (data->protCfgOpts_pr.pres == TRUE)
   {
   	  ueAttachReq->protCfgOpt.pres = TRUE;
	  ueAttachReq->protCfgOpt.len = data->protCfgOpts_pr.len;
	  ueAttachReq->protCfgOpt.cfgProt = data->protCfgOpts_pr.cfgProt;
	  ueAttachReq->protCfgOpt.ext = data->protCfgOpts_pr.ext;
	  ueAttachReq->protCfgOpt.numProtId = data->protCfgOpts_pr.numProtId;
	  ueAttachReq->protCfgOpt.numContId = data->protCfgOpts_pr.numContId;
	  for (count=0;count<data->protCfgOpts_pr.numProtId;count ++)
	  {
	  	ueAttachReq->protCfgOpt.p[count].len = data->protCfgOpts_pr.p[count].len;
		cmMemcpy(ueAttachReq->protCfgOpt.p[count].val, 
			   data->protCfgOpts_pr.p[count].val, 
			   data->protCfgOpts_pr.p[count].len);
	  }
	  for (count=0;count<data->protCfgOpts_pr.numContId;count ++)
	  {
	  	ueAttachReq->protCfgOpt.c[count].len = data->protCfgOpts_pr.c[count].len;
		cmMemcpy(ueAttachReq->protCfgOpt.c[count].val, 
			   data->protCfgOpts_pr.c[count].val, 
			   data->protCfgOpts_pr.c[count].len);
	  }
   }  
   if(data->drxParm_pr.pres)
   	{
   	  ueAttachReq->drxParm.pres = TRUE;
	  ueAttachReq->drxParm.spltPGCycle = data->drxParm_pr.spltPGCycle;
	  ueAttachReq->drxParm.nonDrxTmr = data->drxParm_pr.nonDrxTmr;
	  ueAttachReq->drxParm.spltOnCcch = data->drxParm_pr.spltOnCcch;
	  ueAttachReq->drxParm.u.drxVal = data->drxParm_pr.u.drxVal;
   	}
   if (data->eti.pres) {
     ueAttachReq->eti = TRUE;
   } else {
     ueAttachReq->eti = FALSE;
   }
   fwSendToUeApp(uetMsg);
   FW_LOG_EXITFN(fwCb, ROK);
}   

/*
 *
 *   Fun:   handleUeAppConfig
 *
 *   Desc:  This function is used to handle Ue App Config request 
 *          from Test Controller 
 *
 *   Ret:   None
 *
 *   Notes: None
 *
 *   File:  fw_api_int.c
 *
 */
PUBLIC S16 handleUeAppConfig(ueAppConfig_t *data)
{
   FwCb *fwCb = NULLP;
   UetMessage *uetMsg = NULLP;
   UeUetAppCfReq *ueAppCfg = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &uetMsg, sizeof(UetMessage));

   uetMsg->msgType = UE_APP_CONFIG_REQ_TYPE;
   ueAppCfg = &uetMsg->msg.ueAppCfgReq;
   /* copying feilds */

   if (data->trfGenIPAddr_pr.pres == TRUE)
      ueAppCfg->trfGenIPAddr = data->trfGenIPAddr_pr.trf_gen_ip_addr;
   else
      ueAppCfg->trfGenIPAddr = fwCb->ueAppCfgCb.trfGenIPAddr;

   if (data->nasProcGuardTimer_pr.pres == TRUE)
      ueAppCfg->NASProcGuardTimer = data->nasProcGuardTimer_pr.\
                                    nas_proc_guard_timer;
   else
      ueAppCfg->NASProcGuardTimer = fwCb->ueAppCfgCb.NASProcGuardTimer;

   if (data->numOfUe_pr.pres == TRUE)
      ueAppCfg->numOfUE = data->numOfUe_pr.num_of_ue;
   else
      ueAppCfg->numOfUE = fwCb->ueAppCfgCb.numOfUE;

   fwSendToUeApp(uetMsg);
   FW_LOG_EXITFN(fwCb, ROK);
} /* handleUeAppConfig */

/*
 *
 *   Fun:   handleUeConfig
 *
 *   Desc:  This function is used to handle Ue config request 
 *          from Test Controller 
 *
 *   Ret:   None
 *
 *   Notes: None
 *
 *   File:  fw_api_int.c
 *
 */
PUBLIC S16 handleUeConfig(ueConfig_t *data)
{
   U16 cnt = 0;
   FwCb *fwCb = NULLP;
   UetMessage *uetMsg = NULLP;
   UeUetCfgReq *ueCfg = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);
   
   FW_ALLOC_MEM(fwCb, &uetMsg, sizeof(UetMessage));
   cmMemset((U8 *)uetMsg, 0, sizeof(UetMessage));

   /* copying mandatory feilds */
   uetMsg->msgType = UE_CONFIG_REQ_TYPE;
   ueCfg = &uetMsg->msg.ueCfgReq;
   /*memset(&ueCfg->ueNwCap, 0, sizeof(UeEmmNwCap));*/

   ueCfg->ueId = data->ue_id;
   ueCfg->imsiLen = data->imsiLen;
   cmMemcpy((U8*)ueCfg->imsi, (U8*)data->imsi, ueCfg->imsiLen);
   cmMemcpy((U8*)ueCfg->imei, (U8*)data->imei, 16);

   /* checking optional feilds */
   if (data->algoType_pr.pres == TRUE)
   {
      ueCfg->algoType = data->algoType_pr.algo_type;
   }
   else
   {
      ueCfg->algoType = fwCb->ueCfgCb.algoType;
   }

   if (data->opId_pr.pres == TRUE)
   {
      ueCfg->opId = data->opId_pr.op_id;
   }
   else
   {
      ueCfg->opId = fwCb->ueCfgCb.opId;
   }

   if (data->authType_pr.pres == TRUE)
   {
      ueCfg->authType = data->authType_pr.auth_type;
   }
   else
   {
      ueCfg->authType = fwCb->ueCfgCb.authType;
   }

   if (data->nasCypCfg_pr.pres == TRUE)
   {
      ueCfg->NASCyphCfg = data->nasCypCfg_pr.nas_cyp_cfg;
   }
   else
   {
      ueCfg->NASCyphCfg = fwCb->ueCfgCb.NASCyphCfg;
   }

   if (data->nasIntProtCfg_pr.pres == TRUE)
   {
      ueCfg->NASIntProtCfg = data->nasIntProtCfg_pr.nas_int_prot_cfg;
   }
   else
   {
      ueCfg->NASIntProtCfg = fwCb->ueCfgCb.NASIntProtCfg;
   }

   if (data->ueNwCap_pr.pres == TRUE)
   {
      ueCfg->ueNwCap.eea0 = data->ueNwCap_pr.eea0;
      ueCfg->ueNwCap.eea1_128 = data->ueNwCap_pr.eea1_128;
      ueCfg->ueNwCap.eea2_128 = data->ueNwCap_pr.eea2_128;
      ueCfg->ueNwCap.eia0 = data->ueNwCap_pr.eia0;
      ueCfg->ueNwCap.eia1_128 = data->ueNwCap_pr.eia1_128;
      ueCfg->ueNwCap.eia2_128 = data->ueNwCap_pr.eia2_128;
   }
   else
   {
      ueCfg->ueNwCap.eea0 = fwCb->ueCfgCb.ueNwCap.eea0; 
      ueCfg->ueNwCap.eea1_128 = fwCb->ueCfgCb.ueNwCap.eea1_128;
      ueCfg->ueNwCap.eea2_128 = fwCb->ueCfgCb.ueNwCap.eea2_128;
      ueCfg->ueNwCap.eia0 = fwCb->ueCfgCb.ueNwCap.eia0;
      ueCfg->ueNwCap.eia1_128 = fwCb->ueCfgCb.ueNwCap.eia1_128;
      ueCfg->ueNwCap.eia2_128 = fwCb->ueCfgCb.ueNwCap.eia2_128;
   }
      

   if (data->opKey_pr.pres == TRUE)
      cmMemcpy((U8*)ueCfg->opKey, (U8*)data->opKey_pr.op_key,
               MAX_OPKEY_LEN * sizeof(U32));
   else
      cmMemcpy((U8*)ueCfg->opKey, (U8*)fwCb->ueCfgCb.opKey,
               MAX_OPKEY_LEN * sizeof(U32));

   if (data->sharedKey_pr.pres == TRUE)
      cmMemcpy((U8*)ueCfg->sharedKey, (U8*)data->sharedKey_pr.shared_key,
               MAX_SHAREDKEY_LEN * sizeof(U32));
   else
      cmMemcpy((U8*)ueCfg->sharedKey, (U8*)fwCb->ueCfgCb.sharedKey,
               MAX_SHAREDKEY_LEN * sizeof(U32));

   if (data->srvPlmn_pr.pres == TRUE)
      cmMemcpy((U8*)ueCfg->srvPlmn, (U8*)data->srvPlmn_pr.srv_plmn,
               6 * sizeof(U8));
   else
   {
      cmMemcpy((U8*)ueCfg->srvPlmn, (U8*)fwCb->ueCfgCb.srvPlmn, \
          6 * sizeof(U8));
   }
   FW_ALLOC_MEM(fwCb, &ueCfg->radCapIndRrcPdu, fwCb->ueCfgCb.ueRadCapRrcPduLen);
   ueCfg->radCapIndRrcPdulen = fwCb->ueCfgCb.ueRadCapRrcPduLen;
   for(cnt = 0; cnt < ueCfg->radCapIndRrcPdulen; cnt++)
   {
      ueCfg->radCapIndRrcPdu[cnt] = (U8)fwCb->ueCfgCb.ueRadCapRrcPdu[cnt];
   }

   fwSendToUeApp(uetMsg);
   FW_LOG_EXITFN(fwCb, ROK);
} /* handleUeConfig */

/*
 *
 *   Fun:   handleUeRadCapConfig
 *
 *   Desc:  This function is used to handle Ue config request 
 *          from Test Controller 
 *
 *   Ret:   None
 *
 *   Notes: None
 *
 *   File:  fw_api_int.c
 *
 */
PUBLIC S16 handleUeRadCapConfig(ueRadCapUpd_t *data)
{
   U16 cnt = 0;
   FwCb *fwCb = NULLP;
   UetMessage *uetMsg = NULLP;
   UeUetRadCapUpdReq *ueCfg = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);
   
   FW_ALLOC_MEM(fwCb, &uetMsg, sizeof(UetMessage));
   cmMemset((U8 *)uetMsg, 0, sizeof(UetMessage));
   /* copying mandatory feilds */
   uetMsg->msgType = UE_RAD_CAP_UPD_TYPE;
   ueCfg = &uetMsg->msg.ueUetRadCapUpdReq;
  
   ueCfg->ueId = data->ue_Id;
   ueCfg->send_s1ap_msg = data->snd_S1AP;
   if(data->radioCap_pr.len > 0)
   {
     ueCfg->upd_ueRadCap = TRUE;
     ueCfg->len = data->radioCap_pr.len;
     FW_ALLOC_MEM(fwCb, &ueCfg->radCapMsg,data->radioCap_pr.len);
     cmMemcpy((U8*)ueCfg->radCapMsg, (U8*)data->radioCap_pr.radioCapMsg,data->radioCap_pr.len);
   }
   else
   {
    /* Copy data from default config*/
    ueCfg->len = fwCb->ueCfgCb.ueRadCapRrcPduLen;
    FW_ALLOC_MEM(fwCb, &ueCfg->radCapMsg, fwCb->ueCfgCb.ueRadCapRrcPduLen);
    for(cnt = 0; cnt < ueCfg->len; cnt++)
    {
       ueCfg->radCapMsg[cnt] = (U8)fwCb->ueCfgCb.ueRadCapRrcPdu[cnt];
    }
    ueCfg->upd_ueRadCap = TRUE;
   }
   fwSendToUeApp(uetMsg);
   FW_LOG_EXITFN(fwCb, ROK);
} /* handleUeRadCapConfig */

/*
 *       Fun:  handlUeTrigDetachAccept 
 *
 *       Desc:  This function is used to handle Detach Accept 
 *              from Test Controller and sends to ueApp
 *
 *       Ret:   None
 *
 *       Notes: None
 *
 *       File:  fw_api_int.c
 *
 */
PRIVATE S16 handlUeTrigDetachAccept(ueTrigDetachAcceptInd_t *data)
{
   FwCb  *fwCb        = NULLP;
   UetMessage *uetMsg = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &uetMsg, sizeof(UetMessage));
   cmMemset((U8 *)uetMsg, 0, sizeof(UetMessage));
   
   uetMsg->msgType = UE_TRIG_DETACH_ACCEPT_TYPE;
   uetMsg->msg.ueUetUeTrigDetachAcc.ueId = data->ue_Id;
    
   fwSendToUeApp(uetMsg);

   FW_LOG_EXITFN(fwCb, ROK);
}

/*
 * 
 *       Fun:  handlUeFlushCmnd 
 *
 *       Desc:  This function is used to handle Flush Command 
 *              from Test Controller and sends to ueApp
 *
 *       Ret:   None
 *
 *       Notes: None
 *
 *       File:  fw_api_int.c
 *
 */
PRIVATE S16 handlUeFlushCmnd(ueFlush_t *data)
{
   FwCb  *fwCb        = NULLP;
   UetMessage *uetMsg = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &uetMsg, sizeof(UetMessage));
   cmMemset((U8 *)uetMsg, 0, sizeof(UetMessage));
   
   uetMsg->msgType = UE_FLUSH_TYPE;
   uetMsg->msg.ueUetFlush.noOfUe = data->noOfUe;
    
   fwSendToUeApp(uetMsg);

   FW_LOG_EXITFN(fwCb, ROK);
}

/*
 *
 *       Fun:   handlEnbConfig
 *
 *       Desc:  This function is used to handle EnodeB config request 
 *              from Test Controller 
 *
 *       Ret:   None
 *
 *       Notes: None
 *
 *       File:  fw_api_int.c
 *
 */
PUBLIC S16 handlEnbConfig(FwNbConfigReq_t *data)
{
   U16 i = 0;
   U16 j = 0;
   U16 cnt = 0;
   FwCb  *fwCb = NULLP;
   NbtRequest *msgReq = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &msgReq, sizeof(NbtMsg));
   /* copying all optional feilds */
   msgReq->msgType = NB_CONFIG_REQ;

   if(data->cellId_pr.pres == TRUE)
   {
      msgReq->t.configReq.cellId = data->cellId_pr.cell_id;
   }
   else
   {
      msgReq->t.configReq.cellId = fwCb->nbAppCfgCb.cellId;
   }
   if (data->tac_pr.pres == TRUE)
   {
      msgReq->t.configReq.tac  = data->tac_pr.tac;
   }
   else
   {
      msgReq->t.configReq.tac  =fwCb->nbAppCfgCb.tac;
   }

   if (data->enbIpAddr_pr.pres  == TRUE)
   {
      msgReq->t.configReq.enbIpAddr = data->enbIpAddr_pr.enb_ip_addr;
   }
   else
   {
      msgReq->t.configReq.enbIpAddr = fwCb->nbAppCfgCb.enbIPAddr;
   }

   if (data->mmeId_pr.pres  == TRUE)
   {
      msgReq->t.configReq.mmeId  = data->mmeId_pr.mme_id;
   }
   else
   {
      msgReq->t.configReq.mmeId  =fwCb->nbAppCfgCb.mmeId;
   }

   if (data->mmeAddr_pr.pres  == TRUE)
   {
      msgReq->t.configReq.mmeAddr = data->mmeAddr_pr.mme_addr;
   }
   else
   {
      msgReq->t.configReq.mmeAddr = fwCb->nbAppCfgCb.mmeAddr;
   }

   if (data->sctpIpAddr_pr.pres  == TRUE)
   {
      msgReq->t.configReq.sctpIpAddr = data->sctpIpAddr_pr.sctp_ip_addr;
   }
   else
   {
      msgReq->t.configReq.sctpIpAddr = fwCb->nbAppCfgCb.sctpIPAddr;
   }

   if (data->enbName_pr.pres  == TRUE)
   {
      strcpy((S8*)msgReq->t.configReq.enbName, (S8*)data->enbName_pr.enb_name);
   }
   else
   {
      strcpy((S8*)msgReq->t.configReq.enbName, (S8*)fwCb->nbAppCfgCb.enbName);
   }

   if (data->plmnId_pr.pres  == TRUE)
   {
      strcpy((S8*)msgReq->t.configReq.plmnId, (S8*)data->plmnId_pr.plmn_id);
   }
   else
   {
      strcpy((S8*)msgReq->t.configReq.plmnId, (S8*)fwCb->nbAppCfgCb.plmnId);
   }

   if (data->heratbeatInterval_pr.pres  == TRUE)
   {
      msgReq->t.configReq.heartBeatInterval  = data->heratbeatInterval_pr.heartbeat_interval;
   }
   else
   {
      msgReq->t.configReq.heartBeatInterval  =fwCb->nbAppCfgCb.heartBeatInterval;
   }

   if (data->rtoInitial_pr.pres  == TRUE)
   {
      msgReq->t.configReq.rtoInitial  = data->rtoInitial_pr.rto_initial;
   }
   else
   {
      msgReq->t.configReq.rtoInitial  =fwCb->nbAppCfgCb.rtoInitial;
   }

   if (data->rtoMin_pr.pres  == TRUE)
   {
      msgReq->t.configReq.rtoMin  = data->rtoMin_pr.rto_min;
   }
   else
   {
      msgReq->t.configReq.rtoMin  =fwCb->nbAppCfgCb.rtoMin;
   }

   if (data->rtoMax_pr.pres  == TRUE)
   {
      msgReq->t.configReq.rtoMax  = data->rtoMax_pr.rto_max;
   }
   else
   {
      msgReq->t.configReq.rtoMax  =fwCb->nbAppCfgCb.rtoMax;
   }

   if (data->s1PrepTimerVal_pr.pres  == TRUE)
   {
      msgReq->t.configReq.s1PrepTimerVal  = data->s1PrepTimerVal_pr.s1_prepimer_val;
   }
   else
   {
      msgReq->t.configReq.s1PrepTimerVal  =fwCb->nbAppCfgCb.s1PrepTimerVal;
   }

   if (data->s1OverallTimerVal_pr.pres  == TRUE)
   {
      msgReq->t.configReq.s1OvrAllTimerVal  = data->s1OverallTimerVal_pr.s1_overallimer_val;
   }
   else
   {
      msgReq->t.configReq.s1OvrAllTimerVal  =fwCb->nbAppCfgCb.s1OverallTimerVal;
   }

   if (data->sctpUdpServiceType_pr.pres == TRUE)
   {
      msgReq->t.configReq.sctpUdpServiceType  = data->sctpUdpServiceType_pr.sctp_udp_service_type;
   }
   else
   {
      msgReq->t.configReq.sctpUdpServiceType  =fwCb->nbAppCfgCb.sctpUdpServiceType;
   }

   if (data->inactvTmrVal_pr.pres == TRUE)
   {
      msgReq->t.configReq.inactvTmrVal  = data->inactvTmrVal_pr.val;
   }
   else
   {
      msgReq->t.configReq.inactvTmrVal  = fwCb->nbAppCfgCb.inactvTmrVal;
   }

   if (data->maxExpires_pr.pres == TRUE)
   {
      msgReq->t.configReq.maxExpires  = data->maxExpires_pr.val;
   }
   else
   {
      msgReq->t.configReq.maxExpires  = fwCb->nbAppCfgCb.maxExpires;
   }

   if(data->s1SetUpTmr_pr.pres == TRUE)
   {
      msgReq->t.configReq.s1SetupTmr = data->s1SetUpTmr_pr.val;
   }
   else
   {
      msgReq->t.configReq.s1SetupTmr = fwCb->nbAppCfgCb.s1SetupTmr;
   }

   /* Copy info from data to msgReq */
#if 0
   /* Copy Home PLMN */
   if (data->plmnId_pr.pres == TRUE)
   {
      memcpy(msgReq->t.configReq.plmnId, data->plmnId_pr.plmn_id,
             NBT_MAX_PLMN_ID);
   }
#endif

   /* Copy Supported TAs */
   if (data->suppTAs.pres)
   {
      msgReq->t.configReq.suppTAs.pres = data->suppTAs.pres;
      msgReq->t.configReq.suppTAs.numTAs = data->suppTAs.numTAs;
      for (i = 0; i < data->suppTAs.numTAs; i++)
      {
         msgReq->t.configReq.suppTAs.suppTA[i].tac = data->suppTAs.suppTA[i].tac;
         msgReq->t.configReq.suppTAs.suppTA[i].bPlmnList.numBPlmns =
                                      data->suppTAs.suppTA[i].bPlmnList.numBPlmns;
         /* Copy Broadcasted PLMNs */
         for (j = 0; j < msgReq->t.configReq.suppTAs.suppTA[i].bPlmnList.numBPlmns;
              j++)
         {
            memcpy(&(msgReq->t.configReq.suppTAs.suppTA[i].bPlmnList.plmnIds[j]),
                   &(data->suppTAs.suppTA[i].bPlmnList.bPlmn[j]),
                   sizeof(FwPlmnId));
         }
      }
   }

   /* eNodeB type: Macro eNodeB or Home eNodeB */
   if (data->eNodeBType.pres)
   {
      msgReq->t.configReq.eNodeBType.pres = data->eNodeBType.pres;
      msgReq->t.configReq.eNodeBType.val = data->eNodeBType.val;
   }

   /* Copy number of CSG IDs */
   if (data->csgIdList.pres)
   {
      msgReq->t.configReq.csgIdList.pres = data->csgIdList.pres;
      msgReq->t.configReq.csgIdList.numCsgIds = data->csgIdList.numCsgIds;
      for (i = 0; i < msgReq->t.configReq.csgIdList.numCsgIds; i++)
      {
         /* Copy CSG IDs (only lower 27 bits valid) */
         msgReq->t.configReq.csgIdList.csgId[i] = data->csgIdList.csgId[i];
      }
   }

   if(data->noOfSctpInStreams_pr.pres == TRUE)
   {
      msgReq->t.configReq.noOfSctpInStreams = data->noOfSctpInStreams_pr.val;
   }
   else
   {
      msgReq->t.configReq.noOfSctpInStreams = fwCb->nbAppCfgCb.noOfSctpInStreams;
   }
   if(data->noOfSctpOutStreams_pr.pres == TRUE)
   {
      msgReq->t.configReq.noOfSctpOutStreams = data->noOfSctpOutStreams_pr.val;
   }
   else
   {
      msgReq->t.configReq.noOfSctpOutStreams = fwCb->nbAppCfgCb.noOfSctpOutStreams;
   }

   while(fwCb->nbAppCfgCb.ueEthIntf[cnt])
   {
      msgReq->t.configReq.ueEthIntf[cnt] = fwCb->nbAppCfgCb.ueEthIntf[cnt];
      cnt++;
   }
   msgReq->t.configReq.ueEthIntf[cnt] = '\0';
#ifdef MULTI_ENB_SUPPORT
   /* Number of ENBs */
   msgReq->t.configReq.numOfEnbs = MAX_NUM_OF_ENBS;
#else
   msgReq->t.configReq.numOfEnbs = 1;
#endif
   FW_LOG_DEBUG(fwCb, "*********numOfEnbs = %d MAX_NUM_OF_ENBS = %d\n", msgReq->t.configReq.numOfEnbs, MAX_NUM_OF_ENBS);

   fwCb->nbState = NB_CONFIG_INITIATED;

   fwSendToNbApp(msgReq);

   FW_LOG_EXITFN(fwCb, ROK);
}

PUBLIC S16 handlEnbInactvTmrCfg(FwNbConfigReq_t *data)
{
   FwCb  *fwCb = NULLP;
   NbtRequest *msgReq = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &msgReq, sizeof(NbtMsg));
   /* copying all optional feilds */
   msgReq->msgType = NB_CONFIG_REQ;

   if (data->inactvTmrVal_pr.pres == TRUE)
   {
      msgReq->t.configReq.inactvTmrVal  = data->inactvTmrVal_pr.val;
   }
   else
   {
      msgReq->t.configReq.inactvTmrVal  = fwCb->nbAppCfgCb.inactvTmrVal;
   }

   if (data->maxExpires_pr.pres == TRUE)
   {
      msgReq->t.configReq.maxExpires  = data->maxExpires_pr.val;
   }
   else
   {
      msgReq->t.configReq.maxExpires  = fwCb->nbAppCfgCb.maxExpires;
   }

   fwSendToNbApp(msgReq);

   FW_LOG_EXITFN(fwCb, ROK);
}

/*
 * 
 *     Fun:  handlS1SetupReq 
 * 
 *     Desc:  This function is used to handle S1-SETUP Request 
 *            from Test Controller.
 * 
 *     Ret:   None
 * 
 *     Notes: None
 * 
 *     File:  fw_api_int.c
 * 
 */
PRIVATE S16 handlS1SetupReq(Void)
{
   FwCb  *fwCb = NULLP;
   NbtRequest *msgReq = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &msgReq, sizeof(NbtMsg));
   msgReq->msgType = NB_S1_SETUP_REQ;

   fwCb->nbState = S1_SETUP_INITIATED;
   fwSendToNbApp(msgReq);

   FW_LOG_EXITFN(fwCb, ROK);
}

PUBLIC S16 handleResetRequest(ResetReq *data)
{
   FwCb *fwCb = NULLP;
   NbtRequest *msgReq = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &msgReq, sizeof(NbtMsg));
   /* copying all optional feilds */
   msgReq->msgType = NB_RESET_REQUEST;

   msgReq->t.resetReq.rstType = data->rstType;
   msgReq->t.resetReq.cause.causeType = data->cause.causeType;
   msgReq->t.resetReq.cause.causeVal = data->cause.causeVal;

   if(msgReq->t.resetReq.rstType == NB_COMPLETE_RESET)
   {
      msgReq->t.resetReq.u.completeRst.s1IntfId = data->r.completeRst.s1IntfId;
#ifdef MULTI_ENB_SUPPORT
      msgReq->t.resetReq.u.completeRst.enbId = data->r.completeRst.enbId;
#endif
   }
   else if(msgReq->t.resetReq.rstType == NB_PARTIAL_RESET)
   {
      msgReq->t.resetReq.u.partialRst.numOfConn = data->r.partialRst.numOfConn;
      FW_ALLOC_MEM(fwCb, &msgReq->t.resetReq.u.partialRst.ueIdLst,
            msgReq->t.resetReq.u.partialRst.numOfConn);

      cmMemcpy(msgReq->t.resetReq.u.partialRst.ueIdLst,
            data->r.partialRst.ueIdLst,
            msgReq->t.resetReq.u.partialRst.numOfConn);
   }
   else
   {
      FW_LOG_ERROR(fwCb, "Invalid reset Type");
      FW_LOG_EXITFN(fwCb, RFAILED);
   }

   fwSendToNbApp(msgReq);

   FW_LOG_EXITFN(fwCb, ROK);
} /* handleResetRequest */

#if 0
PUBLIC S16 handleFwErabRelInd(FwErabRelInd_t *data)
{
   FwCb *fwCb = NULLP;
   NbtRequest *msgReq = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &msgReq, sizeof(NbtMsg));

   msgReq->msgType = NB_ERAB_REL_IND;

   msgReq->t.erabRelInd.ueId = data->ueId;
   msgReq->t.erabRelInd.numOfErabIds = data->numOfErabIds;

   FW_ALLOC_MEM(fwCb, &msgReq->t.erabRelInd.erabIdLst,
         data->numOfErabIds);
   cmMemcpy(msgReq->t.erabRelInd.erabIdLst, data->erabIdLst,
         data->numOfErabIds);

   fwSendToNbApp(msgReq);

   FW_LOG_EXITFN(fwCb, ROK);
} /* handleFwErabRelInd_t */
#endif

PUBLIC S16 handleFwErabRelInd(FwErabRelInd_t *data)
{
   FwCb  *fwCb        = NULLP;
   UetMessage *uetMsg = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &uetMsg, sizeof(UetMessage));
   cmMemset((U8 *)uetMsg, 0, sizeof(UetMessage));
   
   uetMsg->msgType = UE_ERAB_REL_IND;
   uetMsg->msg.ueErabRelInd.ueId = data->ueId;
   uetMsg->msg.ueErabRelInd.numOfErabIds = data->numOfErabIds;
   FW_ALLOC_MEM(fwCb, &uetMsg->msg.ueErabRelInd.erabIdLst,
         data->numOfErabIds);
   cmMemcpy(uetMsg->msg.ueErabRelInd.erabIdLst, data->erabIdLst,
         data->numOfErabIds);
   fwSendToUeApp(uetMsg);

   FW_LOG_EXITFN(fwCb, ROK); 
} /* handleFwErabRelInd_t */

PUBLIC S16 handleFwErabRelRsp(FwErabRelRsp_t *data)
{
   FwCb *fwCb = NULLP;
   NbtRequest *msgReq = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &msgReq, sizeof(NbtMsg));

   msgReq->msgType = NB_ERAB_REL_RSP;

   msgReq->t.erabRelRsp.ueId = data->ueId;
   msgReq->t.erabRelRsp.mmeUeS1apId = data->mmeUeS1apId;
   msgReq->t.erabRelRsp.enbUeS1apId = data->enbUeS1apId;
   msgReq->t.erabRelRsp.numOfErabIds = data->numOfErabIds;

   FW_ALLOC_MEM(fwCb, &msgReq->t.erabRelRsp.erabIdLst,
         data->numOfErabIds);
   cmMemcpy(msgReq->t.erabRelRsp.erabIdLst, data->erabIdLst,
         data->numOfErabIds);

   fwSendToNbApp(msgReq);

   FW_LOG_EXITFN(fwCb, ROK);
} /* handleFwErabRelInd_t */

/*
 *
 *   Fun:   handleEmmStatus
 *
 *   Desc:  This function is used to handle EMM STATUS 
 *          from Test Controller 
 *
 *   Ret:   None
 *
 *   Notes: None
 *
 *   File:  fw_api_int.c
 *
 */
PUBLIC S16 handleEmmStatus(ueEmmStatus_t *data)
{
   FwCb *fwCb = NULLP;
   UetMessage *uetMsg = NULLP;
   UeUetEmmStatus *ueEmmStatus = NULLP;
   U8 count;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &uetMsg, sizeof(UetMessage));

   uetMsg->msgType = UE_EMM_STATUS_TYPE;
   ueEmmStatus = &uetMsg->msg.ueUetEmmStatus;

   /* mandatory feilds */
   ueEmmStatus->ueId = data->ue_Id;
   ueEmmStatus->cause = data->cause;
   fwSendToUeApp(uetMsg);
   FW_LOG_EXITFN(fwCb, ROK);
}

/*
 * 
 *   Fun:   handleX2HoTriggerReq
 * 
 *   Desc:  This function is used to handle X2 HO request 
 *          from Test Controller 
 * 
 *   Ret:   None
 * 
 *   Notes: None
 * 
 *   File:  fw_api_int.c
 * 
 */
PUBLIC Void handleX2HoTriggerReq(NbX2HOTriggerReq* data)
{
   FwCb *fwCb = NULLP;
   NbtRequest *msgReq = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);
   
   if(SGetSBuf(fwCb->init.region, fwCb->init.pool, 
       (Data **)&msgReq, (Size)sizeof(NbtRequest)) == ROK) 
   {                                                  
      cmMemset((U8 *)(msgReq), 0, sizeof(NbtRequest));              
   }
   else
   {
      FW_LOG_ERROR(fwCb, "Failed to allocate memory in handleX2HoTriggerReq");
      RETVOID;
   }

   msgReq->msgType = NB_X2_HO_TRIGGER_REQ;
   msgReq->t.x2HOTriggerReq.ueId = data->ueId;
   //Send X2 HO Trigger to NB APP
   fwSendToNbApp(msgReq);
   RETVOID;
}

/*
 * 
 *   Fun:   handleEnbConfigTrnsf
 * 
 *   Desc:  This function is used to handle enb Config Transfer
 *          from Test Controller 
 * 
 *   Ret:   None
 * 
 *   Notes: None
 * 
 *   File:  fw_api_int.c
 * 
 */
PUBLIC Void handleEnbConfigTransfer(NbEnbConfigTrnsf* data)
{
   FwCb *fwCb = NULLP;
   NbtRequest *msgReq = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);
   
   if(SGetSBuf(fwCb->init.region, fwCb->init.pool, 
       (Data **)&msgReq, (Size)sizeof(NbtRequest)) == ROK) 
   {                                                  
      cmMemset((U8 *)(msgReq), 0, sizeof(NbtRequest));              
   }
   else
   {
      FW_LOG_ERROR(fwCb, "Failed to allocate memory in handleEnbConfigTransfer");
      RETVOID;
   }

   msgReq->msgType = NB_ENB_CONFIG_TRANSFER;
   msgReq->t.enbConfigTrnsf.ueId = data->ueId;
   //Send eNB CONFIG TRANSFER to NB APP
   fwSendToNbApp(msgReq);
   RETVOID;
}

/*
 *   Fun:   tfwApi
 *
 *   Desc:  This function is used to distinguish the messages from  
 *          Test controller based on message type and call the 
 *          corresponding handler function.
 *
 *   Ret:   ROK
 *
 *   Notes: None
 *
 *   File:  fw_api_int.c
 *
 */
PUBLIC S16 tfwApi
(
   tfwCmd type,
   Void *msg
)
{
   S16 ret = ROK;
   FwCb  *fwCb = NULLP;
  
   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   if ((NULLP == msg) &&
       (type != ENB_S1_SETUP_REQ) &&
       (type != SCTP_SHUTDOWN_REQ))
   {
      FW_LOG_ERROR(fwCb, "recieved NULL parameter in msg");
      FW_LOG_EXITFN(fwCb, RFAILED);
   }
   switch (type)
   {
      case UE_APPL_CONFIG:
      {
         FW_LOG_DEBUG(fwCb, "ueAppConfig");
         handleUeAppConfig((ueAppConfig_t*)msg);
         break;
      }
      case UE_CONFIG:
      {
         FW_LOG_DEBUG(fwCb, "ueConfig");
         handleUeConfig((ueConfig_t*)msg);
         break;
      }
      case UE_RAD_CAP_UPDATE_REQ:
      {   
         FW_LOG_DEBUG(fwCb, "ueRadCapabilityConfig");
         handleUeRadCapConfig((ueRadCapUpd_t*)msg);
         break;
      }
      case ENB_CONFIG:
      {
         FW_LOG_DEBUG(fwCb, "ENB_CONFIG");
         handlEnbConfig((FwNbConfigReq_t *)msg);
         break;
      }
      case ENB_INACTV_TMR_CFG:
      {
         FW_LOG_DEBUG(fwCb, "ENB_INACTV_TMR_CFG");
         handlEnbInactvTmrCfg((FwNbConfigReq_t *)msg);
         break;
      }
      case ENB_S1_SETUP_REQ:
      {
         FW_LOG_DEBUG(fwCb, "S1 SETUP-REQ");
         switch(fwCb->nbState)
         {
            case NB_CONFIG_DONE: 
            {
               handlS1SetupReq();
               break;
            }
            case ENB_IS_UP:
            {
               FW_LOG_ERROR(fwCb, "FAILED TO SEND S1 SETUP REQ: "\
                     "ENAPP IS ALREADY UP");
               break;
            }
            case S1_SETUP_INITIATED:
            {
               FW_LOG_ERROR(fwCb, "FAILED TO SEND S1 SETUP REQ: "\
                     "ALREADY INITIATED");
               break;
            }
            default:
            {
               FW_LOG_ERROR(fwCb, "FAILED TO SEND S1 SETUP REQ: "\
                     "ENBAPP IS NOT CONFIGURED");
               ret = RFAILED;
            }
         }
         break;
      }
      case UE_ATTACH_REQUEST:
      {
         FW_LOG_DEBUG(fwCb, "UE_ATTACH_REQUEST");
         if (fwCb->nbState == ENB_IS_UP)
         {
            handleAttachReq((ueAttachRequest_t *)msg);
         }
         else
         {
            FW_LOG_ERROR(fwCb, "FAILED TO SEND UE ATTACH REQ: "\
                  "ENBAPP IS NOT UP");
            ret = RFAILED;
         }
         break;
      }
      case UE_END_TO_END_ATTACH_REQUEST:
      {
         FW_LOG_DEBUG(fwCb, "UE_END_TO_END_ATTACH_REQUEST");
         if (fwCb->nbState == ENB_IS_UP)
         {
            handleEndToEndAttachReq((ueAttachRequest_t*)msg);
         }
         else
         {
            FW_LOG_ERROR(fwCb, "FAILED TO SEND "\
                  "UE_END_TO_END_ATTACH_REQUEST: ENBAPP IS NOT UP");
            ret = RFAILED;
         }
         break;
      }
      case UE_AUTH_RESP:
      {
         FW_LOG_DEBUG(fwCb, "UE_AUTH_RESP");
         if (fwCb->nbState == ENB_IS_UP)
         {
            handlAuthResp((ueAuthResp_t*)msg);
         }  
         else
         {
            FW_LOG_ERROR(fwCb, "FAILED TO SEND UE_AUTH_RESP: "\
                  "ENBAPP IS NOT UP");
            ret = RFAILED;
         }
         break;
      }
      case UE_SEC_MOD_COMPLETE:
      {
         FW_LOG_DEBUG(fwCb, "UE_SEC_MOD_COMPLETE");
         if (fwCb->nbState == ENB_IS_UP)
         {
            handlSecModComp((ueSecModeComplete_t*)msg);
         }
         else
         {
            FW_LOG_ERROR(fwCb, "FAILED TO SEND UE_SEC_MOD_COMPLETE: "\
                  "ENBAPP IS NOT UP");
            ret = RFAILED;
         }
         break;
      }
      case UE_SEC_MOD_REJECT:
      {
         FW_LOG_DEBUG(fwCb, "UE_SEC_MOD_REJECT");
         if (fwCb->nbState == ENB_IS_UP)
         {
            handlSecModRej((ueSecModeReject_t*)msg);
         }
         else
         {
            FW_LOG_ERROR(fwCb, "FAILED TO SEND UE_SEC_MOD_REJECT: "\
                  "ENBAPP IS NOT UP");
            ret = RFAILED;
         }
         break;
      }
      case UE_ATTACH_COMPLETE:
      {
         FW_LOG_DEBUG(fwCb, "UE_ATTACH_COMPLETE");
         if (fwCb->nbState == ENB_IS_UP)
         {
            handlAttachComp((ueAttachComplete_t*)msg);
         }
         else
         {
            FW_LOG_ERROR(fwCb, "FAILED TO SEND UE_ATTACH_COMPLETE: "\
                  "ENBAPP IS NOT UP");
            ret = RFAILED;
         }
         break;
      }
      case UE_DETACH_REQUEST:
      {
         FW_LOG_DEBUG(fwCb, "UE_DETACH_REQUEST");
         if (fwCb->nbState == ENB_IS_UP)
         {
            handlDetachReq((uedetachReq_t*)msg);
         }
         else
         {
            FW_LOG_ERROR(fwCb, "FAILED TO SEND UE_DETACH_REQUEST: "\
                  "ENBAPP IS NOT UP");
            ret = RFAILED;
         }
         break;
      }
      case UE_SERVICE_REQUEST:
      {
         FW_LOG_DEBUG(fwCb, "UE_SERVICE_REQ");
         if (fwCb->nbState == ENB_IS_UP)
         {
            handlServiceReq((ueserviceReq_t*)msg);
         }
         else
         {
            FW_LOG_ERROR(fwCb, "FAILED TO SEND UE_SERVICE_REQ:ENBAPP "\
                  "IS NOT UP");
            ret = RFAILED;
         }
         break;
      }
      case UE_CNTXT_REL_REQUEST:
      {
         FW_LOG_DEBUG(fwCb, "UE_CNTXT_REL_REQUEST");
         if (fwCb->nbState == ENB_IS_UP)
         {
            handlUeCntxtRelReq((ueCntxtRelReq_t*)msg);
         }
         else
         {
            FW_LOG_ERROR(fwCb, "FAILED TO SEND UE_CNTXT_REL_REQUEST: "\
                  "ENBAPP IS NOT UP");
            ret = RFAILED;
         }
         break;
      }
      case UE_IDENTITY_RESP:
      {
         FW_LOG_DEBUG(fwCb, "UE_IDENTITY_RESP");
         handlIdentResp((ueIdentityResp_t *)msg);
         break;
      }
      case UE_TAU_REQ:
      {
         FW_LOG_DEBUG(fwCb, "UE_TAU_REQ");
         if (fwCb->nbState == ENB_IS_UP)
         {
            handlTauReq((ueTauReq_t*)msg);
         }
         else
         {
            FW_LOG_ERROR(fwCb, "FAILED TO SEND UE_TAU_REQ:ENBAPP IS NOT UP");
            ret = RFAILED;
         }
         break;
      }
      case UE_TAU_COMPLETE:
      {
         FW_LOG_DEBUG(fwCb, "UE_TAU_COMPLETE");
         if (fwCb->nbState == ENB_IS_UP)
         {
            handlTauComp((ueTauComplete_t*)msg);
         }
         else
         {
            FW_LOG_ERROR(fwCb, "FAILED TO SEND UE_TAU_REQ:ENBAPP IS NOT UP");
            ret = RFAILED;
         }
         break;
      }
      case UE_PDN_CONN_REQ:
      {
         FW_LOG_DEBUG(fwCb, "UE_PDN_CONN_REQ");
         if(fwCb->nbState == ENB_IS_UP)
         {
            handlPdnConReq((uepdnConReq_t*)msg);
         }
         else
         {
            FW_LOG_ERROR(fwCb, "FAILED TO SEND UE_PDN_CONN_REQ: "\
                  "ENBAPP IS NOT UP");
            ret = RFAILED;
         }
         break;
      }
      case RESET_REQ:
      {
         FW_LOG_DEBUG(fwCb, "RESET_REQ");
         if(fwCb->nbState == ENB_IS_UP)
         {
            handleResetRequest((ResetReq*)msg);
         }
         else
         {
            FW_LOG_ERROR(fwCb, "FAILED TO SEND RESET REQUEST: "\
                  "ENBAPP IS NOT UP");
            ret = RFAILED;
         }
         break;
      }
      case UE_TRIGGERED_DETACH_ACCEPT:
      {
         FW_LOG_DEBUG(fwCb, "UE_TRIGGERED_DETACH_ACCEPT");
         if (fwCb->nbState == ENB_IS_UP)
         {
            handlUeTrigDetachAccept((ueTrigDetachAcceptInd_t*)msg);
         }
         else
         {
            FW_LOG_ERROR(fwCb, "FAILED TO SEND UE_TRIG_DETACH_ACCEPT: "\
                  "ENBAPP IS NOT UP");
            ret = RFAILED;
         }
         break;
      }
      case ENB_ERR_IND_MSG:
      {
         FW_LOG_DEBUG(fwCb, "ERROR INDICATION MSG");
         if (fwCb->nbState == ENB_IS_UP)
         {
            handlErrIndMsg((fwNbErrIndMsg_t*)msg);
         }
         else
         {
            FW_LOG_ERROR(fwCb, "FAILED TO SEND ERROR INDICATION MSG: "\
                  "ENBAPP IS NOT UP");
            ret = RFAILED;
         }
         break;
      }
      case UE_FLUSH:
      {
         FW_LOG_DEBUG(fwCb, "UE_FLUSH");
         if (fwCb->nbState == ENB_IS_UP)
         {
            handlUeFlushCmnd((ueFlush_t*)msg);
         }
         else
         {
            FW_LOG_ERROR(fwCb, "FAILED TO SEND UE_FLUSH:ENBAPP IS NOT UP");
            ret = RFAILED;
         }
         break;
      }
      case ERAB_REL_IND:
      {
         FW_LOG_DEBUG(fwCb, "ERAB_REL_IND");
         if(fwCb->nbState == ENB_IS_UP)
         {
            handleFwErabRelInd((FwErabRelInd_t*)msg);
         }
         else
         {
            FW_LOG_ERROR(fwCb, "FAILED TO SEND ERAB RELEASE INDICATION: "\
                  "ENBAPP IS NOT UP");
            ret = RFAILED;
         }
         break;
      }
      case ERAB_REL_RSP:
      {
         FW_LOG_DEBUG(fwCb, "ERAB_REL_RSP");
         if(fwCb->nbState == ENB_IS_UP)
         {
            handleFwErabRelRsp((FwErabRelRsp_t*)msg);
         }
         else
         {
            FW_LOG_ERROR(fwCb, "FAILED TO SEND ERAB RELEASE RESPONSE: "\
                  "ENBAPP IS NOT UP");
            ret = RFAILED;
         }
         break;
      }
      case UE_BER_RES_ALLOC_REQ:
      {
         FW_LOG_DEBUG(fwCb, "Bearer resource allocation request");
         if (fwCb->nbState == ENB_IS_UP)
         {
            handleUeResAllocReq((ueBearerAllocReq_t*)msg);
         }
         else
         {
            FW_LOG_ERROR(fwCb, "FAILED TO SEND UE_BER_RES_ALLOC_REQ:ENBAPP IS NOT UP");
            ret = RFAILED;
         }
         break;
      }
      case UE_ACT_DED_BER_ACC:
      {
         FW_LOG_DEBUG(fwCb, "Activate Dedicated Bearer Context accept ");
         if (fwCb->nbState == ENB_IS_UP)
         {
            handleUeActvDedBerAcc((UeActDedBearCtxtAcc_t*)msg);
         }
         else
         {
            FW_LOG_ERROR(fwCb, "Activate Dedicated Bearer Context accept:ENBAPP IS NOT UP");
            ret = RFAILED;
         }
         break;
      }
      case UE_SET_NAS_NON_DELIVERY:
      {
         FW_LOG_DEBUG(fwCb, "Nas Non delivery ");
         if (fwCb->nbState == ENB_IS_UP)
         {
            handleUeNasNonDelivery((UeNasNonDel*)msg);
         }
         else
         {
            FW_LOG_ERROR(fwCb, "Nas Non delivery:ENBAPP IS NOT UP");
            ret = RFAILED;
         }
         break;
      } 
      case UE_SET_INIT_CTXT_SETUP_FAIL:
      {
         FW_LOG_DEBUG(fwCb, "Initial context setup Fail");
         if (fwCb->nbState == ENB_IS_UP)
         {
            handleUeInitCtxtSetupFail((ueInitCtxtSetupFail*)msg);
         }
         else
         {
            FW_LOG_ERROR(fwCb, "Initial context setup Fail:ENBAPP IS NOT UP");
            ret = RFAILED;
         }
         break;
      }
      case UE_SET_DROP_ICS:
      {
         FW_LOG_DEBUG(fwCb, "Process Drop ICS Request ");
         if (fwCb->nbState == ENB_IS_UP)
         {
            handleDropUeInitCtxtSetupReq((UeDropInitCtxtSetup*)msg);
         }
         else
         {
            FW_LOG_ERROR(fwCb, "Failed To Prcess ICS Drop Request:ENBAPP IS NOT UP");
            ret = RFAILED;
         }
         break;
      }
      case UE_SET_DELAY_ICS_RSP:
      {
         FW_LOG_DEBUG(fwCb, "Process Delay ICS Request ");
         if (fwCb->nbState == ENB_IS_UP)
         {
            handleDelayUeInitCtxtSetupRsp((UeDelayInitCtxtSetupRsp*)msg);
         }
         else
         {
            FW_LOG_ERROR(fwCb, "Failed To Prcess ICS Delay Request:ENBAPP IS NOT UP");
            ret = RFAILED;
         }
         break;
      }
      case UE_SET_DELAY_UE_CTXT_REL_CMP:
      {
         FW_LOG_DEBUG(fwCb, "Process Delay CRC Request ");
         if (fwCb->nbState == ENB_IS_UP)
         {
            handleDelayUeCtxtRelCmp((UeDelayUeCtxtRelCmp*)msg);
         }
         else
         {
            FW_LOG_ERROR(fwCb, "Failed To Prcess ICS Delay Request:ENBAPP IS NOT UP");
            ret = RFAILED;
         }
         break;
      }
      case UE_SET_CTXT_REL_REQ_FOR_ICS:
      {
         FW_LOG_DEBUG(fwCb, "Process Send Rel Req Request for ICS");
         if (fwCb->nbState == ENB_IS_UP)
         {
            handleSetCtxtRelForICS((UeSetCtxtRelForInitCtxtSetup*)msg);
         }
         else
         {
            FW_LOG_ERROR(fwCb, "Failed To Prcess ICS Rel Req Request:ENBAPP IS NOT UP");
            ret = RFAILED;
         }
         break;
      }
      case UE_ACT_DED_BER_REJ:
      {
         FW_LOG_DEBUG(fwCb, "Activate Dedicated Bearer Context Reject");
         if (fwCb->nbState == ENB_IS_UP)
         {
            handleUeActvDedBerRej((UeActDedBearCtxtRej_t*)msg);
         }
         else
         {
            FW_LOG_ERROR(fwCb, "Activate Dedicated Bearer Context accept:ENBAPP IS NOT UP");
            ret = RFAILED;
         }
         break;
      }
      case UE_DEACTIVATE_BER_ACC:
      {
         FW_LOG_DEBUG(fwCb, "De Activate Bearer Context accept ");
         if (fwCb->nbState == ENB_IS_UP)
         {
            handleUeDeActvBerAcc((UeDeActvBearCtxtAcc_t*)msg);
         }
         else
         {
            FW_LOG_ERROR(fwCb, "Activate Dedicated Bearer Context accept:ENBAPP IS NOT UP");
            ret = RFAILED;
         }
         break;
      }
      case SCTP_ABORT_REQ:
      {
         FW_LOG_DEBUG(fwCb, "SCTP_ABORT_REQ");
         handleSctpAbortReq((FwSctpAbortReq_t*)msg);
         break;
      }
      case SCTP_SHUTDOWN_REQ:
      {
         FW_LOG_DEBUG(fwCb, "SCTP_SHUTDOWN_REQ");
         handleSctpShutdownReq();
         break;
      }
      case UE_EMM_STATUS:
      {
         FW_LOG_DEBUG(fwCb, "EMM STATUS message");
	 handleEmmStatus((ueEmmStatus_t*)msg);
	 break;
      }
      case UE_ACTV_DEFAULT_EPS_BEARER_CNTXT_REJECT:
      {
         FW_LOG_DEBUG(fwCb, " ATTACH COMPLETE + ACTIVATE DEFAULT EPS BEARER CONTEXT REJECT message");
	 handleActvDfltEpsBearerContextRej((ueActvDfltEpsBearerCtxtRej_t*)msg);
	 break;
      }
      case UE_ESM_INFORMATION_RSP:
      {
         FW_LOG_DEBUG(fwCb, "UE_ESM_INFORMATION_RSP");
         if(fwCb->nbState == ENB_IS_UP)
         {
            handleEsmInformationRsp((ueEsmInformationRsp_t*)msg);
         }
         else
         {
            FW_LOG_ERROR(fwCb, "FAILED TO SEND UE_PDN_CONN_REQ: "\
                  "ENBAPP IS NOT UP");
            ret = RFAILED;
         }
         break;
      }
      case MULTIPLE_ENB_CONFIG_REQ:
      {
         FW_LOG_DEBUG(fwCb, "MULTIPLE_ENB_CONFIG_REQ");
         handleMultiEnbConfigReq((multiEnbConfigReq_t*)msg);
         break;
      }
      case UE_PARM_QRY:
      {
         FW_LOG_DEBUG(fwCb, "UE_PARM_QRY");
         break;
      }
      case UE_APPP_PARM_QRY:
      {
         FW_LOG_DEBUG(fwCb, "UE_APPP_PARM_QRY");
         break;
      }
      case ENB_PARM_QRY:
      {
         FW_LOG_DEBUG(fwCb, "ENB_PARM_QRY");
         break;
      }
      case X2_HO_TRIGGER_REQ:
      {
         FW_LOG_DEBUG(fwCb, "X2_HO_TRIGGER_REQ");
	     handleX2HoTriggerReq((NbX2HOTriggerReq*)msg);
         break;
      }
      case ENB_CONFIGURATION_TRANSFER:
      {
         FW_LOG_DEBUG(fwCb, "eNB_CONFIGURATION_TRANSFER");
    	 handleEnbConfigTransfer((NbEnbConfigTrnsf*)msg);
         break;
      }
      case UE_ACTV_DEFAULT_EPS_BEARER_CNTXT_ACCEPT:
      {
         FW_LOG_DEBUG(fwCb, "UE_ACTV_DEFAULT_EPS_BEARER_CNTXT_ACCEPT");
         handleActvDfltEpsBearerContextAcc((UeActDefEpsBearCtxtAcc_t*)msg);
         break;
      }
      case UE_PDN_DISCONNECT_REQ:
      {
         FW_LOG_DEBUG(fwCb, "UE_PDN_DISCONNECT_REQ");
         if(fwCb->nbState == ENB_IS_UP)
         {
            handlPdnDisconnectReq((uepdnDisconnectReq_t*)msg);
         }
         else
         {
            FW_LOG_ERROR(fwCb, "FAILED TO SEND UE_PDN_DISCONN_REQ: "\
                  "ENBAPP IS NOT UP");
            ret = RFAILED;
         }
         break;
      }

     default:
      {
         FW_LOG_ERROR(fwCb, "Invalid Message");
         ret = RFAILED;
         break;
      }
   }

   FW_LOG_EXITFN(fwCb, ret);
} /* tfwApi */

/*
 *
 *   Fun:   initTestFrameWork
 *
 *   Desc:  This function initializes Test Framework.
 *
 *   Ret:   ROK
 *
 *   Notes: None
 *
 *   File:  fw_api_int.c
 *
 */
Void initTestFrameWork(TestCnrlrCallBack func)
{
   FwCb *fwCb = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   /* Initialize the TAPA/SSI */
   FW_LOG_DEBUG(fwCb, "Initializing the SSI...");
   if (init_ssi() != ROK)
   {
      FW_LOG_ERROR(fwCb, "Failed in initializing the SSI");
      FW_LOG_EXITFNVOID(fwCb);
   }

   /* Register Call back function of test controller */
   FW_LOG_DEBUG(fwCb, "Initializing the Callback pointer for Test Controller");
   fwCb->testConrollerCallBack = func;

   FW_LOG_EXITFNVOID(fwCb);
} /* initTestFrameWork */

/*
 * 
 *   Fun:   handlPdnConnReq
 * 
 *   Desc:  This function is used to handle PDN connectivity Request 
 *          from Test Controller 
 * 
 *   Ret:   None
 * 
 *   Notes: None
 * 
 *   File:  fw_api_int.c
 * 
 */
PRIVATE Void handlPdnConReq(uepdnConReq_t* data)
{
   FwCb *fwCb = NULLP;
   S16 ret;
   UetMessage *uetMsg = NULLP;
   UeUetPdnConReq *uePdnConReq = NULLP;
   UeIdCb *ueIdCb = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   if (SGetSBuf(fwCb->init.region, fwCb->init.pool, 
            (Data **)&uetMsg, (Size) sizeof(UetMessage)) == ROK) 
   {                                                  
      cmMemset((U8 *)(uetMsg), 0,sizeof(UetMessage));              
   }
   else
   {
      RETVOID;
   }   
   if (SGetSBuf(fwCb->init.region, fwCb->init.pool, 
            (Data **)&ueIdCb, (Size) sizeof(UeIdCb)) == ROK) 
   {                                                  
      cmMemset((U8 *)(ueIdCb), 0,sizeof(UeIdCb));              
   }
   else
   {
      RETVOID;
   }
   
   insertUeCb(data->ue_Id, 0, 0, ueIdCb);
   uetMsg->msgType = UE_PDN_CON_REQ_TYPE;
   uePdnConReq = &uetMsg->msg.ueUetPdnConReq;
   uePdnConReq->ueId    = data->ue_Id;
   if(data->pdnType_pr.pres == TRUE)
      uePdnConReq->pdnType = data->pdnType_pr.pdn_type;
   uePdnConReq->reqType = data->reqType;
   if(data->pdnAPN_pr.pres == TRUE)
   {
      uePdnConReq->nasPdnApn.len = data->pdnAPN_pr.len;
      cmMemcpy(uePdnConReq->nasPdnApn.apn, data->pdnAPN_pr.pdn_apn,data->pdnAPN_pr.len);
   }
   fwSendToUeApp(uetMsg);
   FW_LOG_DEBUG(fwCb, "\n-------------------------------\n\
            Starting T3482\n-------------------------------\n");
   ret = fwStartTmr(fwCb, ueIdCb, fwHndlPdnTmrExp, 800);
   if (ROK != ret)
   {
      FW_LOG_ERROR(fwCb, "Failed to start T3482 timer");
   }
   RETVOID;
}

/*
 *
 *       Fun:   handlErrIndMsg 
 *
 *       Desc:  This function is used to handle Error Indication Msg 
 *              from Test Controller 
 *
 *       Ret:   None
 *
 *       Notes: None
 *
 *       File:  fw_api_int.c
 *
 */
PRIVATE S16 handlErrIndMsg(fwNbErrIndMsg_t *data)
{
   FwCb  *fwCb    = NULLP;
   NbtRequest *msgReq = NULLP;
   U8 idx = 0;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &msgReq, sizeof(NbtMsg));
   /* copying all optional feilds */
   msgReq->msgType = NB_ERR_IND_MSG;
   msgReq->t.s1ErrIndMsg.isUeAssoc = data->isUeAssoc;
   if(data->isUeAssoc == TRUE)
   { 
      msgReq->t.s1ErrIndMsg.ue_Id = data->ue_Id; 
   }
   if(data->cause.pres == TRUE)
   {
      msgReq->t.s1ErrIndMsg.causePres = data->cause.pres;
      msgReq->t.s1ErrIndMsg.cause.causeType = data->cause.causeType;
      msgReq->t.s1ErrIndMsg.cause.causeVal = data->cause.causeVal;
   }
   msgReq->t.s1ErrIndMsg.criticalityDiag.pres = data->criticalityDiag.pres;
   if(data->criticalityDiag.pres == TRUE)
   {
      msgReq->t.s1ErrIndMsg.criticalityDiag.pres = TRUE;
      if(data->criticalityDiag.procCodePres == TRUE)
      {
         msgReq->t.s1ErrIndMsg.criticalityDiag.procCodePres = TRUE;
         msgReq->t.s1ErrIndMsg.criticalityDiag.procedureCode =\
            data->criticalityDiag.procedureCode;
      }
      if(data->criticalityDiag.trigMsgPres == TRUE)
      {
         msgReq->t.s1ErrIndMsg.criticalityDiag.trigMsgPres = TRUE;
         msgReq->t.s1ErrIndMsg.criticalityDiag.triggeringMsg = \
            data->criticalityDiag.triggeringMsg;
      }
      if(data->criticalityDiag.proCriticalityPres == TRUE)
      {
         msgReq->t.s1ErrIndMsg.criticalityDiag.proCriticalityPres = TRUE;
         msgReq->t.s1ErrIndMsg.criticalityDiag.procedureCriticality = \
            data->criticalityDiag.procedureCriticality;
      }
      msgReq->t.s1ErrIndMsg.criticalityDiag.ieLst.noComp =
         data->criticalityDiag.ieLst.noComp; 
      FW_ALLOC_MEM(fwCb, &msgReq->t.s1ErrIndMsg.criticalityDiag.ieLst.member, \
      sizeof(FwCriticalityDiag_IE_Item));
      for(idx = 0 ; idx < data->criticalityDiag.ieLst.noComp ; idx++)
      { 
         if(data->criticalityDiag.ieLst.member[idx].pres  == TRUE)
         {
            msgReq->t.s1ErrIndMsg.criticalityDiag.ieLst.member[idx].pres = TRUE;
            msgReq->t.s1ErrIndMsg.criticalityDiag.ieLst.member[idx].iECriticality = \
              data->criticalityDiag.ieLst.member[idx].iECriticality; 
            msgReq->t.s1ErrIndMsg.criticalityDiag.ieLst.member[idx].iE_ID = \
              data->criticalityDiag.ieLst.member[idx].iE_ID;
            msgReq->t.s1ErrIndMsg.criticalityDiag.ieLst.member[idx].TypOfErr = \
              data->criticalityDiag.ieLst.member[idx].TypOfErr;
         }
      }
   }
   fwSendToNbApp(msgReq);

   FW_LOG_EXITFN(fwCb, ROK);
}

/*
 *
 *   Fun:   handleUeResAllocReq 
 *
 *   Desc:  This function is used to handle Attach request 
 *          from Test Controller 
 *
 *   Ret:   None
 *
 *   Notes: None
 *
 *   File:  fw_api_int.c
 *
 */
PUBLIC S16 handleUeResAllocReq(ueBearerAllocReq_t *data)
{
   U8 idx;
   FwCb *fwCb = NULLP;
   UetMessage *uetMsg = NULLP;
   UeUetBearerAllocReq *bearAllocReq = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &uetMsg, sizeof(UetMessage));

   uetMsg->msgType = UE_BEAR_RES_ALLOC_REQ;
   bearAllocReq = &uetMsg->msg.ueBearerAllocReq;

   /* mandatory feilds */
   bearAllocReq->ueId           = data->ue_Id;
   bearAllocReq->bearerId       = data->bearerId;
   bearAllocReq->lnkEpsBearerId = data->lnkEpsBearerId;

   bearAllocReq->epsQos.pres = data->qos.pres; 
   if(bearAllocReq->epsQos.pres == TRUE)
   {
     bearAllocReq->epsQos.qci             = data->qos.qci;
     bearAllocReq->epsQos.lenQosCont      = data->qos.lenQosCont;
     bearAllocReq->epsQos.maxBitRateUL    = data->qos.maxBitRateUL;
     bearAllocReq->epsQos.maxBitRateDL    = data->qos.maxBitRateDL; 
     bearAllocReq->epsQos.guaraBitRateUL  = data->qos.guaraBitRateUL;
     bearAllocReq->epsQos.guaraBitRateDL  = data->qos.guaraBitRateDL;
   }
   bearAllocReq->tft.pres = data->tft.pres;

   if(bearAllocReq->tft.pres == TRUE)
   {
       bearAllocReq->tft.pres           = data->tft.pres;
       bearAllocReq->tft.len            = data->tft.len;       
       bearAllocReq->tft.opCode         = data->tft.opCode;    
       bearAllocReq->tft.noOfPfs        = data->tft.noOfPfs;   
       bearAllocReq->tft.eBit           = data->tft.eBit;       
       bearAllocReq->tft.noOfParams     = data->tft.noOfParams; 

      bearAllocReq->tft.noOfPfs = data->tft.noOfPfs;
      for( idx = 0 ; idx < bearAllocReq->tft.noOfPfs ; idx++)
      {
         bearAllocReq->tft.pfList[idx].pres = TRUE;
         bearAllocReq->tft.pfList[idx].id =    data->tft.pfList[idx].id;    
         bearAllocReq->tft.pfList[idx].dir =   data->tft.pfList[idx].dir;
         bearAllocReq->tft.pfList[idx].preced = data->tft.pfList[idx].preced;     
         bearAllocReq->tft.pfList[idx].len =    data->tft.pfList[idx].len; 
         bearAllocReq->tft.pfList[idx].ipv4.pres =  data->tft.pfList[idx].ipv4.pres;
         if(bearAllocReq->tft.pfList[idx].ipv4.pres == TRUE)
         { 
            cmMemcpy((U8 *)&bearAllocReq->tft.pfList[idx].ipv4.ip4, \
               (U8 *)data->tft.pfList[idx].ipv4.ip4,CM_ESM_IPV4_SIZE);
            bearAllocReq->tft.pfList[idx].ipv4Mask = data->tft.pfList[idx].ipv4Mask;
         }
         if(bearAllocReq->tft.pfList[idx].ipv6.pres == TRUE)
         { 
            cmMemcpy((U8 *)&bearAllocReq->tft.pfList[idx].ipv6.ip6, \
               (U8 *)data->tft.pfList[idx].ipv6.ip6,CM_ESM_IPV6_SIZE);
         }
         if(data->tft.pfList[idx].protId.pres)
         {
            bearAllocReq->tft.pfList[idx].protId.pres           =  data->tft.pfList[idx].protId.pres;
            bearAllocReq->tft.pfList[idx].protId.protType       =  data->tft.pfList[idx].protId.protType;
         }
         if(data->tft.pfList[idx].localPort.pres)
         {
            bearAllocReq->tft.pfList[idx].localPort.pres        =  data->tft.pfList[idx].localPort.pres; 
            bearAllocReq->tft.pfList[idx].localPort.port        =  data->tft.pfList[idx].localPort.port;
         }
         if(data->tft.pfList[idx].remotePort.pres)
         { 
            bearAllocReq->tft.pfList[idx].remotePort.pres       =  data->tft.pfList[idx].remotePort.pres;
            bearAllocReq->tft.pfList[idx].remotePort.port       =  data->tft.pfList[idx].remotePort.port;
         }
         if(data->tft.pfList[idx].locPortRange.pres)
         {
            bearAllocReq->tft.pfList[idx].locPortRange.pres     =  data->tft.pfList[idx].locPortRange.pres;
            bearAllocReq->tft.pfList[idx].locPortRange.rangeLow =  data->tft.pfList[idx].locPortRange.rangeLow;
            bearAllocReq->tft.pfList[idx].locPortRange.rangeHigh   =\
               data->tft.pfList[idx].locPortRange.rangeHigh;
         }
         if(data->tft.pfList[idx].remPortRange.pres)
         {
            bearAllocReq->tft.pfList[idx].remPortRange.pres      =  data->tft.pfList[idx].remPortRange.pres;
            bearAllocReq->tft.pfList[idx].remPortRange.rangeLow  =  \
               data->tft.pfList[idx].remPortRange.rangeLow;
             bearAllocReq->tft.pfList[idx].remPortRange.rangeHigh   =\
               data->tft.pfList[idx].remPortRange.rangeHigh; 
         }
         if(data->tft.pfList[idx].secParam.pres)
         { 
            bearAllocReq->tft.pfList[idx].secParam.pres  =  data->tft.pfList[idx].secParam.pres;
            cmMemcpy((U8 *)&bearAllocReq->tft.pfList[idx].secParam.params, \
               (U8 *)data->tft.pfList[idx].secParam.params, CM_ESM_IP_SEC_SIZE);
         }
         if(data->tft.pfList[idx].tos.pres)
         {
            bearAllocReq->tft.pfList[idx].tos.pres       = data->tft.pfList[idx].tos.pres;
            bearAllocReq->tft.pfList[idx].tos.tos        = data->tft.pfList[idx].tos.tos; 
            bearAllocReq->tft.pfList[idx].tos.mask       = data->tft.pfList[idx].tos.mask; 
         }
         if(data->tft.pfList[idx].flowLabel.pres)
         { 
            bearAllocReq->tft.pfList[idx].flowLabel.pres = data->tft.pfList[idx].flowLabel.pres;
            cmMemcpy((U8 *)&bearAllocReq->tft.pfList[idx].flowLabel.buf, \
               (U8 *)data->tft.pfList[idx].flowLabel.buf,CM_ESM_IPV6_FLOW_LABEL_SIZE);
         }
      }
       bearAllocReq->tft.noOfParams =  data->tft.noOfParams;
      for( idx = 0 ; idx < bearAllocReq->tft.noOfParams ; idx++)
      {
         bearAllocReq->tft.params[idx].len      = data->tft.params[idx].len;
         bearAllocReq->tft.params[idx].paramType = data->tft.params[idx].paramType; 
          cmMemcpy((U8 *)&bearAllocReq->tft.params[idx].buf, \
            (U8 *)data->tft.params[idx].buf,CM_ESM_TFT_MAX_PARAM_BUF);
      }
   }
   fwSendToUeApp(uetMsg);
   FW_LOG_EXITFN(fwCb, ROK);
}   

/*
 *
 *   Fun:   handleUeDeActvBerAcc 
 *
 *   Desc:  This function is used to handle Attach request 
 *          from Test Controller 
 *
 *   Ret:   None
 *
 *   Notes: None
 *
 *   File:  fw_api_int.c
 *
 */
PRIVATE S16 handleUeDeActvBerAcc(UeDeActvBearCtxtAcc_t* data)
{
   FwCb *fwCb = NULLP;
   UetMessage *uetMsg = NULLP;
   UeEsmActDedBearCtxtAcc *deActvBerAcc = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &uetMsg, sizeof(UetMessage));

   uetMsg->msgType = UE_EPS_DEACTIVATE_BER_ACC;
   deActvBerAcc = &uetMsg->msg.ueDeActvBerAcc;

   /* mandatory feilds */
   deActvBerAcc->ueId           = data->ue_Id;
   deActvBerAcc->bearerId       = data->bearerId;

   fwSendToUeApp(uetMsg);
   FW_LOG_EXITFN(fwCb, ROK);
}
/*
 *
 *   Fun:   handleUeActvDedBerAcc 
 *
 *   Desc:  This function is used to handle Attach request 
 *          from Test Controller 
 *
 *   Ret:   None
 *
 *   Notes: None
 *
 *   File:  fw_api_int.c
 *
 */
PRIVATE S16 handleUeActvDedBerAcc(UeActDedBearCtxtAcc_t* data)
{
   FwCb *fwCb = NULLP;
   UetMessage *uetMsg = NULLP;
   UeEsmActDedBearCtxtAcc *actvBerAcc = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &uetMsg, sizeof(UetMessage));

   uetMsg->msgType = UE_EPS_DED_BER_ACC;
   actvBerAcc = &uetMsg->msg.ueActDedBerAcc;

   /* mandatory feilds */
   actvBerAcc->ueId           = data->ue_Id;
   actvBerAcc->bearerId       = data->bearerId;

   fwSendToUeApp(uetMsg);
   FW_LOG_EXITFN(fwCb, ROK);
}



/*
 *
 *   Fun:   handleUeActvDedBerRej 
 *
 *
 *   Ret:   None
 *
 *   Notes: None
 *
 *   File:  fw_api_int.c
 *
 */
PRIVATE S16 handleUeActvDedBerRej(UeActDedBearCtxtRej_t* data)
{
   FwCb *fwCb = NULLP;
   UetMessage *uetMsg = NULLP;
   UeEsmActDedBearCtxtRej *actvBerRej = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &uetMsg, sizeof(UetMessage));

   uetMsg->msgType = UE_EPS_DED_BER_REJ;
   actvBerRej = &uetMsg->msg.ueActDedBerRej;

   /* mandatory feilds */
   actvBerRej->ueId           = data->ue_Id;
   actvBerRej->bearerId       = data->bearerId;
   actvBerRej->esmCause       = data->esmCause;

   fwSendToUeApp(uetMsg);
   FW_LOG_EXITFN(fwCb, ROK);
}   

/*
 *
 *   Fun:   handleSctpAbortReq
 *
 *
 *   Ret:   None
 *
 *   Notes: None
 *
 *   File:  fw_api_int.c
 *
 */
PRIVATE S16 handleSctpAbortReq(FwSctpAbortReq_t* data)
{
   FwCb *fwCb = NULLP;
   NbtRequest *msgReq = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &msgReq, sizeof(NbtMsg));

   msgReq->msgType = NB_SCTP_ABORT_REQ;
   msgReq->t.sctpAbortReqMsg.cause = data->cause;

   fwSendToNbApp(msgReq);
   fwCb->nbState = NB_CONFIG_DONE;

   FW_LOG_EXITFN(fwCb, ROK);
}

/*
 *
 *   Fun:   handleSctpShutdownReq
 *
 *
 *   Ret:   None
 *
 *   Notes: None
 *
 *   File:  fw_api_int.c
 *
 */
PRIVATE S16 handleSctpShutdownReq(Void)
{
   FwCb *fwCb = NULLP;
   NbtRequest *msgReq = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &msgReq, sizeof(NbtMsg));

   msgReq->msgType = NB_SCTP_SHUTDOWN_REQ;

   fwSendToNbApp(msgReq);
   fwCb->nbState = NB_CONFIG_DONE;

   FW_LOG_EXITFN(fwCb, ROK);
}

/*
 * 
 *   Fun:   handleUeNasNonDelivery
 * 
 *   Desc:  This function is used to handle the Nas non delivery 
 * 
 *   Ret:   None
 * 
 *   Notes: None
 * 
 *   File:  fw_api_int.c
 * 
 */
PUBLIC Void handleUeNasNonDelivery(UeNasNonDel* data)
{
   FwCb *fwCb = NULLP;
   NbtRequest *msgReq = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   if(SGetSBuf(fwCb->init.region, fwCb->init.pool, 
       (Data **)&msgReq, (Size)sizeof(NbtRequest)) == ROK) 
   {                                                  
      cmMemset((U8 *)(msgReq), 0, sizeof(NbtRequest));              
   }
   else
   {
      FW_LOG_ERROR(fwCb, "Failed to allocate memory");
      RETVOID;
   }

   msgReq->msgType = NB_NAS_NON_DEL;
   msgReq->t.nasNondel.ueId = data->ue_Id;
   msgReq->t.nasNondel.flag= data->flag;
   msgReq->t.nasNondel.causeType = data->causeType;
   msgReq->t.nasNondel.causeVal = data->causeVal;

   fwSendToNbApp(msgReq);
   RETVOID;
}
/*
 * 
 *   Fun:   handleUeInitCtxtSetupFail 
 * 
 *   Desc:  This function is used to handle the Initial Context Setup Failure  
 * 
 *   Ret:   None
 * 
 *   Notes: None
 * 
 *   File:  fw_api_int.c
 * 
 */
PUBLIC Void handleUeInitCtxtSetupFail(ueInitCtxtSetupFail* data)
{
   FwCb *fwCb = NULLP;
   NbtRequest *msgReq = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   if(SGetSBuf(fwCb->init.region, fwCb->init.pool, 
       (Data **)&msgReq, (Size)sizeof(NbtRequest)) == ROK) 
   {                                                  
      cmMemset((U8 *)(msgReq), 0, sizeof(NbtRequest));              
   }
   else
   {
      FW_LOG_ERROR(fwCb, "Failed to allocate memory");
      RETVOID;
   }

   msgReq->msgType = NB_INIT_CTXT_SETUP_FAIL;
   msgReq->t.initCtxtSetupFail.ueId = data->ue_Id;
   msgReq->t.initCtxtSetupFail.initCtxtSetupFailInd = data->flag;
   msgReq->t.initCtxtSetupFail.causeType = data->causeType;
   msgReq->t.initCtxtSetupFail.causeVal = data->causeVal;

   fwSendToNbApp(msgReq);
   RETVOID;
}
/*
 * 
 *   Fun:   handleDropUeInitCtxtSetupReq 
 * 
 *   Desc:  This function is used to handle  Drop Initial Context Setup Request
 * 
 *   Ret:   None
 * 
 *   Notes: None
 * 
 *   File:  fw_api_int.c
 * 
 */
PRIVATE Void handleDropUeInitCtxtSetupReq(UeDropInitCtxtSetup* data)
{
   FwCb *fwCb = NULLP;
   NbtRequest *msgReq = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   if(SGetSBuf(fwCb->init.region, fwCb->init.pool, 
       (Data **)&msgReq, (Size)sizeof(NbtRequest)) == ROK) 
   {                                                  
      cmMemset((U8 *)(msgReq), 0, sizeof(NbtRequest));              
   }
   else
   {
      FW_LOG_ERROR(fwCb, "Failed to allocate memory");
      RETVOID;
   }

   msgReq->msgType = NB_DROP_INIT_CTXT_SETUP;
   msgReq->t.dropInitCtxtSetup.ueId = data->ue_Id;
   msgReq->t.dropInitCtxtSetup.isDropICSEnable = data->flag;
   msgReq->t.dropInitCtxtSetup.tmrVal = data->tmrVal;

   fwSendToNbApp(msgReq);
   RETVOID;
}
/*
 * 
 *   Fun:   handleDelayUeCtxtRelCmp 
 * 
 *   Desc:  This function is used to handle  Delay Initial Context Setup Response
 * 
 *   Ret:   None
 * 
 *   Notes: None
 * 
 *   File:  fw_api_int.c
 * 
 */
PRIVATE Void handleDelayUeCtxtRelCmp(UeDelayUeCtxtRelCmp* data)
{
   FwCb *fwCb = NULLP;
   NbtRequest *msgReq = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   if(SGetSBuf(fwCb->init.region, fwCb->init.pool, 
       (Data **)&msgReq, (Size)sizeof(NbtRequest)) == ROK) 
   {                                                  
      cmMemset((U8 *)(msgReq), 0, sizeof(NbtRequest));              
   }
   else
   {
      FW_LOG_ERROR(fwCb, "Failed to allocate memory");
      RETVOID;
   }

   msgReq->msgType = NB_DELAY_UE_CTXT_REL_CMP;
   msgReq->t.delayUeCtxtRelCmp.ueId = data->ue_Id;
   msgReq->t.delayUeCtxtRelCmp.isDelayUeCtxtRelCmp = data->flag;
   msgReq->t.delayUeCtxtRelCmp.tmrVal = data->tmrVal;

   fwSendToNbApp(msgReq);
   RETVOID;
}
/*
 * 
 *   Fun:   handleDelayUeInitCtxtSetupRsp 
 * 
 *   Desc:  This function is used to handle  Delay Initial Context Setup Response
 * 
 *   Ret:   None
 * 
 *   Notes: None
 * 
 *   File:  fw_api_int.c
 * 
 */
PRIVATE Void handleDelayUeInitCtxtSetupRsp(UeDelayInitCtxtSetupRsp* data)
{
   FwCb *fwCb = NULLP;
   NbtRequest *msgReq = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   if(SGetSBuf(fwCb->init.region, fwCb->init.pool, 
       (Data **)&msgReq, (Size)sizeof(NbtRequest)) == ROK) 
   {                                                  
      cmMemset((U8 *)(msgReq), 0, sizeof(NbtRequest));              
   }
   else
   {
      FW_LOG_ERROR(fwCb, "Failed to allocate memory");
      RETVOID;
   }

   msgReq->msgType = NB_DELAY_INIT_CTXT_SETUP_RSP;
   msgReq->t.delayInitCtxtSetupRsp.ueId = data->ue_Id;
   msgReq->t.delayInitCtxtSetupRsp.isDelayICSRsp = data->flag;
   msgReq->t.delayInitCtxtSetupRsp.tmrVal = data->tmrVal;

   fwSendToNbApp(msgReq);
   RETVOID;
}

/*
 * 
 *   Fun:   handleSetCtxtRelForICS 
 * 
 *   Desc:  This function is used to set the Ctxt Rel for ICS
 * 
 *   Ret:   None
 * 
 *   Notes: None
 * 
 *   File:  fw_api_int.c
 * 
 */
PRIVATE Void handleSetCtxtRelForICS(UeSetCtxtRelForInitCtxtSetup* data)
{
   FwCb *fwCb = NULLP;
   NbtRequest *msgReq = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   if(SGetSBuf(fwCb->init.region, fwCb->init.pool, 
       (Data **)&msgReq, (Size)sizeof(NbtRequest)) == ROK) 
   {                                                  
      cmMemset((U8 *)(msgReq), 0, sizeof(NbtRequest));              
   }
   else
   {
      FW_LOG_ERROR(fwCb, "Failed to allocate memory");
      RETVOID;
   }

   msgReq->msgType = NB_SEND_UE_CTXT_REL_FOR_ICS;
   msgReq->t.sendUeCtxtRelForICS.ueId = data->ue_Id;
   msgReq->t.sendUeCtxtRelForICS.sndICSRspUeCtxtRel = data->flag;
   msgReq->t.sendUeCtxtRelForICS.causeType = data->causeType;
   msgReq->t.sendUeCtxtRelForICS.causeVal = data->causeVal;

   fwSendToNbApp(msgReq);
   RETVOID;
}
/*
 * 
 *   Fun:   handleEsmInformationRsp
 * 
 *   Desc:  This function is used to handle ESM Information Response 
 *          from Test Controller 
 * 
 *   Ret:   None
 * 
 *   Notes: None
 * 
 *   File:  fw_api_int.c
 * 
 */
PRIVATE Void handleEsmInformationRsp(ueEsmInformationRsp_t* data)
{
   FwCb *fwCb = NULLP;
   S16 ret;
   UetMessage *uetMsg = NULLP;
   UeUetEsmInformationRsp *ueEsmInfoRsp = NULLP;
   UeIdCb *ueIdCb = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   if (SGetSBuf(fwCb->init.region, fwCb->init.pool, 
            (Data **)&uetMsg, (Size) sizeof(UetMessage)) == ROK) 
   {                                                  
      cmMemset((U8 *)(uetMsg), 0,sizeof(UetMessage));              
   }
   else
   {
      RETVOID;
   }   
   if (SGetSBuf(fwCb->init.region, fwCb->init.pool, 
            (Data **)&ueIdCb, (Size) sizeof(UeIdCb)) == ROK) 
   {                                                  
      cmMemset((U8 *)(ueIdCb), 0,sizeof(UeIdCb));              
   }
   else
   {
      RETVOID;
   }
   
   insertUeCb(data->ue_Id, 0, 0, ueIdCb);
   uetMsg->msgType = UE_ESM_INFORMATION_RSP_TYPE;
   ueEsmInfoRsp = &uetMsg->msg.ueEsmInformationRsp;
   ueEsmInfoRsp->ueId    = data->ue_Id;
   if(data->pdnAPN_pr.pres == TRUE)
   {
      ueEsmInfoRsp->nasPdnApn.len = data->pdnAPN_pr.len;
      cmMemcpy(ueEsmInfoRsp->nasPdnApn.apn, data->pdnAPN_pr.pdn_apn,data->pdnAPN_pr.len);
   }
   fwSendToUeApp(uetMsg);
   RETVOID;
}

/*
 * 
 *   Fun:   handleMultiEnbConfigReq
 * 
 *   Desc:  This function is used to handle multiple enb config request 
 *          from Test Controller
 * 
 *   Ret:   None
 * 
 *   Notes: None
 * 
 *   File:  fw_api_int.c
 * 
 */
PRIVATE Void handleMultiEnbConfigReq(multiEnbConfigReq_t* data)
{
   FwCb *fwCb = NULLP;
   NbtRequest *msgReq = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_LOG_DEBUG(fwCb, "Handling Multi Enb config Req msg in TFW");
   if(SGetSBuf(fwCb->init.region, fwCb->init.pool, 
       (Data **)&msgReq, (Size)sizeof(NbtRequest)) == ROK) 
   {                                                  
      cmMemset((U8 *)(msgReq), 0, sizeof(NbtRequest));              
   }
   else
   {
      FW_LOG_ERROR(fwCb, "Failed to allocate memory");
      RETVOID;
   }

   msgReq->msgType = NB_MULTI_ENB_CONFIG_REQ;
   printf("**** data->numOfEnbs = %d\n", data->numOfEnbs);
   for (int index = 0; index < data->numOfEnbs; index++)
   {
      msgReq->t.multiEnbConfigReq.numOfEnbs  = data->numOfEnbs;
      msgReq->t.multiEnbConfigReq.nbMultiEnbCfgParam[index].cell_id    = data->multiEnbCfgParam[index].cell_id;
      msgReq->t.multiEnbConfigReq.nbMultiEnbCfgParam[index].tac        = data->multiEnbCfgParam[index].tac;
      msgReq->t.multiEnbConfigReq.nbMultiEnbCfgParam[index].enbType    = data->multiEnbCfgParam[index].enbType;
      msgReq->t.multiEnbConfigReq.nbMultiEnbCfgParam[index].plmn_id[0] = data->multiEnbCfgParam[index].plmn_id[0];
      msgReq->t.multiEnbConfigReq.nbMultiEnbCfgParam[index].plmn_id[1] = data->multiEnbCfgParam[index].plmn_id[1];
      msgReq->t.multiEnbConfigReq.nbMultiEnbCfgParam[index].plmn_id[2] = data->multiEnbCfgParam[index].plmn_id[2];
      msgReq->t.multiEnbConfigReq.nbMultiEnbCfgParam[index].plmn_id[3] = data->multiEnbCfgParam[index].plmn_id[3];
      msgReq->t.multiEnbConfigReq.nbMultiEnbCfgParam[index].plmn_id[4] = data->multiEnbCfgParam[index].plmn_id[4];
      msgReq->t.multiEnbConfigReq.nbMultiEnbCfgParam[index].plmn_id[5] = data->multiEnbCfgParam[index].plmn_id[5];
   }
   fwSendToNbApp(msgReq);
   RETVOID;
}

/*
 *
 *   Fun:   handleActvDfltEpsBearerContextAcc
 *
 *   Desc:  This function is used to handle Activate
 *          default EPS bearer context accept
 *
 *   Ret:   None
 *
 *   Notes: None
 *
 *   File:  fw_api_int.c
 *
 */

PRIVATE S16 handleActvDfltEpsBearerContextAcc(UeActDefEpsBearCtxtAcc_t* data)
{
   FwCb *fwCb = NULLP;
   UetMessage *uetMsg = NULLP;
   UeEsmActDefBearCtxtAcc *actvDefBerAcc = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &uetMsg, sizeof(UetMessage));

   uetMsg->msgType = UE_EPS_DEFAULT_BER_ACC;
   actvDefBerAcc = &uetMsg->msg.ueActDefBerAcc;

   if (actvDefBerAcc)
   {
     actvDefBerAcc->ueId           = data->ue_Id;
     actvDefBerAcc->bearerId       = data->bearerId;

     fwSendToUeApp(uetMsg);
   }
   else
   {
     FW_LOG_ERROR(fwCb, "Memory allocation failed for ActDefBearCtxtAcc\n");
   }
     FW_LOG_EXITFN(fwCb, ROK);
}

/*
 *
 *   Fun:   handlPdnDisconnReq
 *
 *   Desc:  This function is used to handle PDN Disconnect Request
 *          from Test Controller
 *
 *   Ret:   None
 *
 *   Notes: None
 *
 *   File:  fw_api_int.c
 *
 */
PRIVATE Void handlPdnDisconnectReq(uepdnDisconnectReq_t* data)
{
   FwCb *fwCb = NULLP;
   S16 ret;
   UetMessage *uetMsg = NULLP;
   UeUetPdnDisconnectReq *uePdnDisconnectReq = NULLP;
   UeIdCb *ueIdCb = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   if (SGetSBuf(fwCb->init.region, fwCb->init.pool,
            (Data **)&uetMsg, (Size) sizeof(UetMessage)) == ROK)
   {
     cmMemset((U8 *)(uetMsg), 0,sizeof(UetMessage));
   }
   else
   {
      RETVOID;
   }
   if (SGetSBuf(fwCb->init.region, fwCb->init.pool,
            (Data **)&ueIdCb, (Size) sizeof(UeIdCb)) == ROK)
   {
      cmMemset((U8 *)(ueIdCb), 0,sizeof(UeIdCb));
   }
   else
   {
      RETVOID;
   }

   insertUeCb(data->ue_Id, 0, 0, ueIdCb);
   uetMsg->msgType = UE_PDN_DISCONNECT_REQ_TYPE;
   uePdnDisconnectReq = &uetMsg->msg.ueUetPdnDisconnectReq;
   uePdnDisconnectReq->ueId    = data->ue_Id;
   uePdnDisconnectReq->bearerId = data->epsBearerId;
   fwSendToUeApp(uetMsg);
   // Start T3492 timer
   FW_LOG_DEBUG(fwCb, "\n-------------------------------\n\
            Starting T3492\n-------------------------------\n");
   /* 10ms(tick)*600 = 6000ms = 6s timer*/
   ret = fwStartTmr(fwCb, ueIdCb, fwHndlPdnDisconnTmrExp, 600);
   if (ROK != ret)
   {
      FW_LOG_ERROR(fwCb, "Failed to start T3492 timer");
   }
   RETVOID;
}
