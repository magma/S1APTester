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
               
    File:  nb_ui.c

    Sid:   

     Prg:      

**********************************************************************/
#include "nb.h"
#include "rl_interface.h"
#include "rl_common.h"
#include "nb_smm_init.h"
#include "nbt.h"
#include "nb_log.h"
#include "nbt.x"
#include "nb_traffic_handler.x"
#include "nb_utils.h"

EXTERN U8 uesLocalRel;
EXTERN S16 NbUiNbuHdlUeIpInfoRsp(Pst*, NbuUeIpInfoRsp*);
EXTERN S16 NbHandleInitialUeMsg(NbuInitialUeMsg*);
EXTERN S16 NbHandleUeIpInfoRsp(NbuUeIpInfoRsp*);
EXTERN S16 NbEnUeRelReqHdl(NbUeCntxtRelReq*);
EXTERN S16 NbEnbCfgReqHdl(NbConfigReq*);
EXTERN S16 NbEnbUeRelReqHdl(NbUeCntxtRelReq*);
EXTERN S16 NbEnbResetReqHdl(NbResetRequest*);
EXTERN  S16 NbBuildAndSndErrIndMsg(NbErrIndMsg*);
EXTERN S16 NbEnbErabRelIndHdl(NbuErabRelIndList*);
EXTERN S16 NbEnbErabRelRspHdl(NbErabRelRsp*);
EXTERN S16 NbEnbNasNonDel(NbNasNonDel *nasNonDel);
EXTERN S16 NbEnbInitCtxtSetupFail(NbInitCtxtSetupFail*);
EXTERN S16 NbEnbDropInitCtxtSetup(NbDropInitCtxtSetup*);
EXTERN S16 NbEnbDelayInitCtxtSetupRsp(NbDelayICSRsp*);
EXTERN S16 NbEnbHandleInitCtxtSetupRspFailedErabs(NbInitCtxtSetupFailedErabs *);
EXTERN S16 NbEnbUeCtxtRelForInitCtxtSetup(NbSendUeCtxtRelForICSRsp*);
EXTERN S16 nbUiSendIntCtxtSetupDrpdIndToUser(U32 ueId);
EXTERN S16 NbEnbDelayUeCtxtRelCmp(NbDelayUeCtxtRelCmp*);
EXTERN S16 NbMultiEnbCfgReq(NbMultiEnbConfigReq*);
EXTERN S16 NbUiNbuHdlUeIpInfoRej(Pst *, NbuUeIpInfoRej *);
EXTERN S16 NbEnbDropRA(NbDropRA*);

int atoi(const char *nptr);

PUBLIC S16 NbUiNbtMsgReq
(
 Pst *pst,
 NbtMsg *req
)
{
   U16 noOfCfg = 0;

   NB_LOG_ENTERFN(&nbCb);

   switch (req->msgType)
   {
      case NB_CONFIG_REQ:
      {
         if (ROK != NbEnbCfgReqHdl(&req->t.configReq))
         {
            NB_LOG_ERROR(&nbCb,"FAILED to process EnbApp Config Req");
         }
         break;
      }
      case NB_S1_SETUP_REQ:
      {
         smNbProcSm(EVTNBINITS1SETUP);
         break;
      }
      case NB_SCTP_ABORT_REQ:
      {
         NB_LOG_DEBUG(&nbCb, "Send SCTP ABORT REQUEST");
         for (noOfCfg = 0; noOfCfg < smCfgCb.noOfCfg; noOfCfg++)
         {
            if (nbBuildAndSendS1AbortReq((U16)(smCfgCb.mmeCfg[noOfCfg]->mmeId),
                                         req->t.sctpAbortReqMsg.cause) != ROK)
            {
               NB_LOG_ERROR(&nbCb, "FAILED to process SCTP Abort Request"\
                            "from TFW");
               RETVALUE(RFAILED);
            }
         }
         break;
      }
      case NB_SCTP_SHUTDOWN_REQ:
      {
         NB_LOG_DEBUG(&nbCb, "Send SCTP SHUTDOWN REQUEST");
         for (noOfCfg = 0; noOfCfg < smCfgCb.noOfCfg; noOfCfg++)
         {
            if (nbBuildAndSendS1ShutdownReq((U16)(smCfgCb.mmeCfg[noOfCfg]->\
                                            mmeId)) != ROK)
            {
               NB_LOG_ERROR(&nbCb, "FAILED to process SCTP Shutdown"\
                            "Request from TFW");
               RETVALUE(RFAILED);
            }
         }
         break;
      }
      case NB_UE_CNTXT_REL_REQ:
      {
         if(ROK != NbEnbUeRelReqHdl(&req->t.ueCntxtRelReq))
         {
            NB_LOG_ERROR(&nbCb,"FAILED to process UE Context Release "\
                  "Request from TFW");
         }
         break;
      }
      case NB_RESET_REQUEST:
      {
         if(ROK != NbEnbResetReqHdl(&req->t.resetReq))
         {
            NB_LOG_ERROR(&nbCb, "Failed to process Reset Request from "\
                  "TFW");
         }
         break;
      }
      case NB_ERR_IND_MSG:
      {
         if( ROK != NbBuildAndSndErrIndMsg(&req->t.s1ErrIndMsg))
         {
            NB_LOG_ERROR(&nbCb,"FAILED to process Error Indication Message "\
                  "from TFW");
         }
         break;
      }
      case NB_ERAB_REL_RSP:
      {
         if(ROK != NbEnbErabRelRspHdl(&req->t.erabRelRsp))
         {
            NB_LOG_ERROR(&nbCb, "Failed to process Erab Release Response "\
                  "from TFW");
         }
         break;
      }
      case NB_NAS_NON_DEL:
         {
            if(ROK != NbEnbNasNonDel(&req->t.nasNondel))
            {
               NB_LOG_ERROR(&nbCb, "Failed to process NAS Non Delivery  "\
                     "from TFW");
            }
            break;
            
         }
      case NB_INIT_CTXT_SETUP_FAIL:
         {
            if(ROK != NbEnbInitCtxtSetupFail(&req->t.initCtxtSetupFail))
            {
               NB_LOG_ERROR(&nbCb, "Failed to process Initial Context Setup Failure  "\
                     "from TFW");
            }
            break;
            
         }
      case NB_DROP_INIT_CTXT_SETUP:
         {
            if(ROK != NbEnbDropInitCtxtSetup(&req->t.dropInitCtxtSetup))
            {
               NB_LOG_ERROR(&nbCb, "Failed to process Drop Initial Context Setup Indication  "\

                     "from TFW");
            }
            break;
            
         }
      case NB_DELAY_INIT_CTXT_SETUP_RSP:
         {
            if(ROK != NbEnbDelayInitCtxtSetupRsp(&req->t.delayInitCtxtSetupRsp))
            {
               NB_LOG_ERROR(&nbCb, "Failed to process Delay Initial Context Setup Rsp  "\

                     "from TFW");
            }
            break;
            
         }
      case NB_INIT_CTXT_SETUP_RSP_FAILED_ERABS: {
        if (ROK != NbEnbHandleInitCtxtSetupRspFailedErabs(
                       &req->t.initCtxtSetupRspFailedErabs)) {
          NB_LOG_ERROR(&nbCb,
                       "Failed to process NbEnbHandleInitCtxtSetupRspFailedErabs");
        }
        break;
      }
      case NB_DELAY_UE_CTXT_REL_CMP:
         {
            if(ROK != NbEnbDelayUeCtxtRelCmp(&req->t.delayUeCtxtRelCmp))
            {
               NB_LOG_ERROR(&nbCb, "Failed to process Delay Ue Context Release Complete  "\

                     "from TFW");
            }
            break;
            
         }
      case NB_SEND_UE_CTXT_REL_FOR_ICS:
         {
            if(ROK != NbEnbUeCtxtRelForInitCtxtSetup(&req->t.sendUeCtxtRelForICS))
            {
               NB_LOG_ERROR(&nbCb, "Failed to process Delay Initial Context Setup Rsp  "\

                     "from TFW");
            }
            break;
            
         }
      case NB_MULTI_ENB_CONFIG_REQ:
         {
            if(ROK != NbMultiEnbCfgReq(&req->t.multiEnbConfigReq))
            {
               NB_LOG_ERROR(&nbCb, "Failed to process Multiple ENB Config Request  "\
                     "from TFW");
            }
            break;
         }
#ifdef MULTI_ENB_SUPPORT
      case NB_X2_HO_TRIGGER_REQ:
      {
         if(ROK != NbEnbX2HOTriggerReqHdl(&req->t.ueCntxtRelReq))
         {
            NB_LOG_ERROR(&nbCb,"FAILED to process X2 HO Trigger Req "\
                  "Request from TFW");
         }
         break;
      }

      case NB_ENB_CONFIG_TRANSFER:
      {
         if(ROK != NbEnbConfigTransferHdl(&req->t.enbConfigTrnsf))
         {
            NB_LOG_ERROR(&nbCb,"FAILED to process Enb Config Transfer "\
                  "Request from TFW");
         }
         break;
      }

#endif
      case NB_DROP_RA: {
        if(ROK != NbEnbDropRA(&req->t.dropRA)) {
               NB_LOG_ERROR(&nbCb, "Failed to process Drop RA Indication  "\
                     "from TFW");
        }
            break;
      }

      default:
         NB_LOG_ERROR(&nbCb,"Invalid msgType");
         break;
   }
   /* need to free received buffer */
   RETVALUE(ROK);
} /* NbUiNbtMsgReq */

PUBLIC S16 NbUiNbuHdlInitialUeMsg 
(
 Pst *pst,
 NbuInitialUeMsg *req
)
{
   S16 retVal = ROK;

   retVal = NbHandleInitialUeMsg(req);
   /* free the received message */
   NB_FREE(req->nasPdu.val, req->nasPdu.len);
   NB_FREE(req, sizeof(NbuInitialUeMsg));
   RETVALUE(retVal);
} /* NbUiNbuHdlInitialUeMsg */

PUBLIC S16 NbUiNbuHdlUeIpInfoRsp 
(
 Pst *pst,
 NbuUeIpInfoRsp *rsp
)
{
   S16 retVal = ROK;

   retVal = NbHandleUeIpInfoRsp(rsp);
   RETVALUE(retVal);
} /* NbUiNbuHdlUeIpInfoRsp */
PUBLIC S16 NbUiNbuHdlErabRelInd 
(
 Pst *pst,
 NbuErabRelIndList *msg
)
{
   S16 retVal = ROK;

   retVal = NbEnbErabRelIndHdl(msg);
   RETVALUE(retVal);
} /* NbUiNbuHdlErabRelInd */
PUBLIC S16 NbUiNbuHdlUlNasMsg
(
 Pst *pst,
 NbuUlNasMsg *msg
)
{
   U32 ueId = 0;
   NbUeCb *ueCb = NULLP;
   NbS1ConCb *s1apConCb = NULLP;
   SztDatEvntReq s1UlInfoMsg = {0};

   NB_SET_ZERO(&s1UlInfoMsg, sizeof(SztDatEvntReq));
   ueId = msg->ueId;
#if 0
   U8 idx = 0;
   for(idx = 0; idx < nbCb.crntUeIdx; idx++)
   {
      if((nbCb.ueCbLst[idx]!= NULLP) && (nbCb.ueCbLst[idx]->ueId == ueId))
      {
         ueCb = nbCb.ueCbLst[idx];
         break;
      }
   }
   if(ueCb == NULLP)
   {
      NB_LOG_ERROR(&nbCb, "ueCb not found for UeId %d", ueId);
      NB_FREE(msg->nasPdu.val, msg->nasPdu.len);
      NB_FREE(msg, sizeof(NbuUlNasMsg));
      RETVALUE(RFAILED);
   }
#endif
   if ( ROK != (cmHashListFind(&(nbCb.ueCbLst), (U8 *)&(ueId),
      sizeof(U32),0,(PTR *)&ueCb)))
   {
      NB_LOG_ERROR(&nbCb, "ueCb not found for UeId %d", ueId);
      NB_FREE(msg->nasPdu.val, msg->nasPdu.len);
      NB_FREE(msg, sizeof(NbuUlNasMsg));
      RETVALUE(RFAILED);
   }

   /* set the datrcvd flag for ue */
   nbDamSetDatFlag(ueId);
   s1apConCb = ueCb->s1ConCb;
   if(s1apConCb == NULLP || ((s1apConCb != NULLP) && 
            (s1apConCb->s1apConnState != NB_S1AP_CONNECTED)))
   {
      NB_FREE(msg->nasPdu.val, msg->nasPdu.len);
      NB_FREE(msg, sizeof(NbuUlNasMsg));
      RETVALUE(RFAILED);
   }
#ifdef MULTI_ENB_SUPPORT
   EnbCb *enbCb = NULLP;
   if ( ROK != (cmHashListFind(&(nbCb.eNBCbLst), (U32 *)&(ueCb->enbId),
      sizeof(U32),0,(PTR *)&enbCb)))
   {
      NB_LOG_ERROR(&nbCb, "enbCb not found for enbId %d", ueCb->enbId);
      RETVALUE(RFAILED);
   }
   if (enbCb == NULLP){
      NB_LOG_ERROR(&nbCb, "enbCb is NULL!!");
   }

   if(nbS1apBldUlNasPdu(ueCb, &msg->nasPdu, &s1UlInfoMsg.pdu, enbCb) != ROK)
#else
   if(nbS1apBldUlNasPdu(ueCb, &msg->nasPdu, &s1UlInfoMsg.pdu) != ROK)
#endif
   {
      NB_FREE(msg->nasPdu.val, msg->nasPdu.len);
      NB_FREE(msg, sizeof(NbuUlNasMsg));
      RETVALUE(ROK);
   }

   s1UlInfoMsg.spConnId = s1apConCb->spConnId;

   /* Multi eNB support */
#ifdef MULTI_ENB_SUPPORT
   s1UlInfoMsg.enbId = ueCb->enbId;
#endif

   /* Dispatch the message using S1 interface to the selected MME         */
   if (ROK != NbIfmS1apDatReq(&s1UlInfoMsg))
   {
      NB_LOG_ERROR(&nbCb,"NbIfmS1apDatReq failed");
      NB_FREE(msg->nasPdu.val, msg->nasPdu.len);
      NB_FREE(msg, sizeof(NbuUlNasMsg));
      RETVALUE(RFAILED);
   }

   NB_FREE(msg->nasPdu.val, msg->nasPdu.len);
   NB_FREE(msg, sizeof(NbuUlNasMsg));

   RETVALUE(ROK);
} /* NbUiNbuHdlUlNasMsg */  

PUBLIC S16 NbUiNbuHdlUeRadioCapMsg
(
 Pst           *pst,
 NbuUlRrcMsg *msg
)
{
   U32 ueId;
   NbUeCb    *ueCb = NULLP;
   NbS1ConCb * s1apConCb = NULLP;
   SztDatEvntReq      s1UlInfoMsg;
   NB_SET_ZERO(&s1UlInfoMsg, sizeof(SztDatEvntReq));

   ueId = msg->ueId;
#if 0
   U8 idx;
   for(idx = 0; idx < nbCb.crntUeIdx; idx++)
   {
      if((nbCb.ueCbLst[idx]!= NULLP)&&(nbCb.ueCbLst[idx]->ueId == ueId))
      {
         ueCb = nbCb.ueCbLst[idx];
         break;
      }
   }
   if( ueCb == NULLP)
   {
      NB_LOG_ERROR(&nbCb,"NbUiNbuHdlUeRadioCapMsg: ueCb not found");
      NB_FREE(msg->rrcPdu.val,msg->rrcPdu.len);
      NB_FREE(msg,sizeof(NbuUlRrcMsg));
      printf("\n*************NbUiNbuHdlUeRadioCapMsg: ueCb not found"\
            "**********\n");
      RETVALUE(RFAILED);
   }
#endif
   if ( ROK != (cmHashListFind(&(nbCb.ueCbLst), (U8 *)&(ueId),
      sizeof(U32),0,(PTR *)&ueCb)))
   {
      NB_LOG_ERROR(&nbCb,"NbUiNbuHdlUeRadioCapMsg: ueCb not found");
      NB_FREE(msg->rrcPdu.val,msg->rrcPdu.len);
      NB_FREE(msg,sizeof(NbuUlRrcMsg));
      printf("\n*************NbUiNbuHdlUeRadioCapMsg: ueCb not found**********\n");
      RETVALUE(RFAILED);
   }
   /* set the datrcvd flag for ue */
   nbDamSetDatFlag(ueId);
   s1apConCb = ueCb->s1ConCb;
   if(s1apConCb == NULLP || ((s1apConCb != NULLP) && 
            (s1apConCb->s1apConnState != NB_S1AP_CONNECTED)))
   {
      NB_FREE(msg->rrcPdu.val,msg->rrcPdu.len);
      NB_FREE(msg,sizeof(NbuUlRrcMsg));
      RETVALUE(RFAILED);
   }

   if(nbS1apBldUeCapIndPdu(ueCb,&msg->rrcPdu, &s1UlInfoMsg.pdu) != ROK)
   {
      NB_FREE(msg->rrcPdu.val,msg->rrcPdu.len);
      NB_FREE(msg,sizeof(NbuUlRrcMsg));
      printf("\n*************NbUiNbuHdlUeRadioCapMsg: build UE cap msg "\
            "failed**********\n");
      RETVALUE(ROK);
   }
   s1UlInfoMsg.spConnId = s1apConCb->spConnId;

   /* Multi eNB support */
#ifdef MULTI_ENB_SUPPORT
   s1UlInfoMsg.enbId = ueCb->enbId;
#endif
   /* Dispatch the message using S1 interface to the selected MME         */
   if (ROK != NbIfmS1apDatReq(&s1UlInfoMsg))
   {
      NB_LOG_ERROR(&nbCb,"NbIfmS1apDatReq failed");
      NB_FREE(msg->rrcPdu.val,msg->rrcPdu.len);
      NB_FREE(msg,sizeof(NbuUlRrcMsg));
      printf("\n*************NbUiNbuHdlUeRadioCapMsg: Send UE cap msg failed"\
            "**********\n");
      RETVALUE(RFAILED);

   }
   printf("\n*************NbUiNbuHdlUeRadioCapMsg: Send UE cap msg SUCCESS"\
         "*********\n");
   NB_FREE(msg->rrcPdu.val,msg->rrcPdu.len);
   NB_FREE(msg,sizeof(NbuUlRrcMsg));

   RETVALUE(ROK);
} /* NbUiNbuHdlUeRadioCapMsg */

PUBLIC S16 nbUiBuildAndSendDlNasMsg
(
 NbUeCb       *ueCb,
 SztNAS_PDU   *nasPdu
) 
{
   U8 idx = 0;
   NbuDlNasMsg *msg = NULLP;

   NB_ALLOC(&msg, sizeof(NbuDlNasMsg));
   msg->ueId = ueCb->ueId;
   msg->nasPdu.len = nasPdu->len;

   NB_ALLOC(&msg->nasPdu.val, msg->nasPdu.len * sizeof(U8));
   for(idx = 0 ; idx < nasPdu->len; idx++)
   {
      msg->nasPdu.val[idx] = nasPdu->val[idx];
   }

   /* set the datrcvd flag for ue */
   nbDamSetDatFlag(ueCb->ueId);
   cmPkNbuDlNasMsg(&nbCb.ueAppPst, msg);
   RETVALUE(ROK);
} /* nbUiBuildAndSendDlNasMsg */

/* eNb is not sending NAS NON DEL IND to TFW */
#if 0
PUBLIC S16 nbUiBuildAndSendNasNonDlvryIndToTfw
(
 U32 ueId
)
{
   NbtMsg * msg = NULLP;
   Pst pst;

   SM_SET_ZERO(&pst, sizeof(Pst));
   pst.selector  = 0;
   pst.srcEnt    = ENTNB;
   pst.dstEnt    = ENTFW;
   pst.srcProcId = 0;
   pst.dstProcId = 0;
   pst.region = smCfgCb.init.region;
   pst.pool = smCfgCb.init.pool;
   pst.srcInst = 0;
   NB_ALLOC(&msg, sizeof(NbtMsg));
   if(msg == NULLP)
   {
      NB_LOG_ERROR(&nbCb, "Failed to allocate memory");
      RETVALUE(RFAILED);
   }
   smCfgCb.smState = NB_SM_STATE_AWAIT_S1_CON;
   msg->msgType = NB_NAS_NON_DEL_RSP;
   msg->t.nasNondelRsp.ueId = ueId;
   if(ROK != cmPkNbtMsgRsp(&pst, msg))
   {
      NB_LOG_ERROR(&nbCb, "Failed to send message to TFWApp");
   }
   RETVALUE(ROK);

} /* nbUiBuildAndSendNasNonDlvryIndToTfw */
#endif
PUBLIC S16 nbUiBuildAndSendPagingMsg
(
 NbPagingMsgInfo *pagMsgInfo
)
{
   U8 idx = 0;
   UePagingMsg *msg = NULLP;
   NB_ALLOC(&msg, sizeof(UePagingMsg));
   /*NB_SET_ZERO(&msg, sizeof(UePagingMsg));*/
   msg->ueIdenType = pagMsgInfo->ueIdenType;
   if (msg->ueIdenType == UEPAGID_IMSI)
   {
      for(idx = 0 ; idx < 22; idx++)
      {
         msg->ueIden.imsi[idx] = pagMsgInfo->ueIden.imsi[idx];
      }

   }
   else if (msg->ueIdenType == UEPAGID_S_TMSI)
   {
      msg->ueIden.sTMSI.pres = TRUE;
      msg->ueIden.sTMSI.mmec = pagMsgInfo->ueIden.sTMSI.mmec;
      msg->ueIden.sTMSI.mTMSI = pagMsgInfo->ueIden.sTMSI.mTMSI;
   }
   msg->domIndType = pagMsgInfo->domIndType; 
   cmPkNbuPagingMsg(&nbCb.ueAppPst,msg);
   RETVALUE(ROK);
} /* nbUiBuildAndSendPagingMsg */

PUBLIC Void nbUiNbuHandleUeInactivity(U32 ueId)
{
   NbuUeInActvInd *msg;
   NB_ALLOC(&msg, sizeof(NbuUeInActvInd));
   msg->ueId = ueId;
   cmPkNbuUeInActvInd(&nbCb.ueAppPst, msg);
} /* nbUiNbuHandleUeInactivity */

PUBLIC Void nbUiSendS1TimeOutInd(Void)
{
   NbtMsg * msg = NULLP;
   Pst pst;

   SM_SET_ZERO(&pst, sizeof(Pst));
   pst.selector  = 0;
   pst.srcEnt    = ENTNB;
   pst.dstEnt    = ENTFW;
   pst.srcProcId = 0;
   pst.dstProcId = 0;
   pst.region = smCfgCb.init.region;
   pst.pool = smCfgCb.init.pool;
   pst.srcInst = 0;
   NB_ALLOC(&msg, sizeof(NbtMsg));
   if(msg == NULLP)
      RETVOID;
   smCfgCb.smState = NB_SM_STATE_AWAIT_S1_CON;
   msg->msgType = NB_S1_SETUP_TIMEOUT_IND; 
   if(ROK != cmPkNbtMsgRsp(&pst, msg))
   {
      NB_LOG_ERROR(&nbCb,"Failed to send message to TFWApp");
   }
} /* nbUiSendS1TimeOutInd */

PUBLIC Void nbUiSendS1SetupFailInd
(
 U8 causeType,
 U32 causeVal,
 U32 wait
)
{
   NbtMsg *rsp = NULLP;
   Pst pst;
   SM_SET_ZERO(&pst, sizeof(Pst));
   pst.selector  = 0;
   pst.srcEnt    = ENTNB;
   pst.dstEnt    = ENTFW;
   pst.srcProcId = 0;
   pst.dstProcId = 0;
   pst.region = smCfgCb.init.region;
   pst.pool = smCfgCb.init.pool;
   pst.srcInst = 0;
   NB_ALLOC(&rsp, sizeof(NbtMsg));

   rsp->msgType                      = NB_S1_SETUP_RSP;
   rsp->t.s1SetupRsp.res             = S1_SETUP_FAIL;
   rsp->t.s1SetupRsp.cause.causeType = causeType;
   rsp->t.s1SetupRsp.cause.causeVal  = causeVal;
   if( wait != 0)
   {
      rsp->t.s1SetupRsp.waitIe.val   = wait;
      rsp->t.s1SetupRsp.waitIe.pres  =  TRUE; 
   }
   smCfgCb.smState = NB_SM_STATE_AWAIT_S1_CON;
   if(ROK != cmPkNbtMsgRsp(&pst, rsp))
   {
      NB_LOG_ERROR(&nbCb,"Failed to send message to TFWApp");
   }
} /* nbUiSendS1SetupFailInd */

PUBLIC Void nbUiSendConfigFailIndToUser(CfgFailCause cause)
{
   NbtResponse *rsp = NULLP;

   NB_ALLOC(&rsp, sizeof(NbtResponse));

   rsp->msgType     = NB_CONFIG_CFM;
   /*change the state to init */
   /* free any allocated memory */
   Pst pst;
   SM_SET_ZERO(&pst, sizeof(Pst));
   pst.selector  = 0;
   pst.srcEnt    = ENTNB;
   pst.dstEnt    = ENTFW;
   pst.srcProcId = 0;
   pst.dstProcId = 0;
   pst.region = smCfgCb.init.region;
   pst.pool = smCfgCb.init.pool;
   pst.srcInst = 0;

   rsp->t.configCfm.status = CFG_DONE_NOK; 
   rsp->t.configCfm.cause  = cause; 
   NB_LOG_ERROR(&nbCb,"SENDING THE CONFIGURATION CFM NOK  TO USER FW-API");

   smCfgCb.smState = NB_SM_STATE_AWAIT_S1_CON;
   if(ROK != cmPkNbtMsgRsp(&pst, rsp))
   {
      NB_LOG_ERROR(&nbCb,"Failed to send message to TFWApp");
   }
} /* nbUiSendConfigFailIndToUser */

PUBLIC Void nbUiSendSuccessResponseToUser(NbMsgTypes msgType)
{
   NbtResponse *rsp = NULLP;
   Pst pst;
   NbMmeCb *mmeCb;
   U16 idx = 0;

   NB_LOG_ENTERFN(&nbCb);

   mmeCb = &nbCb.mmeInfo;
   if (mmeCb == NULLP)
   {
      RETVOID;
   }

   NB_ALLOC(&rsp, sizeof(NbtResponse));

   rsp->msgType     = msgType;
   SM_SET_ZERO(&pst, sizeof(Pst));

   pst.selector  = 0;
   pst.srcEnt    = ENTNB;
   pst.dstEnt    = ENTFW;
   pst.srcProcId = 0;
   pst.dstProcId = 0;
   pst.region = smCfgCb.init.region;
   pst.pool = smCfgCb.init.pool;
   pst.srcInst = 0;
   if(msgType == NB_CONFIG_CFM)
   { 
      rsp->t.configCfm.status = CFG_DONE_ROK;
   }
   else if(msgType == NB_S1_SETUP_RSP)
   {
      rsp->t.s1SetupRsp.res = S1_SETUP_SUCC;

      /* Served GUMMEI list */
      rsp->t.s1SetupRsp.numPlmnIds = mmeCb->numPlmnIds;
      for (idx = 0; idx < mmeCb->numPlmnIds; idx++)
      {
         cmMemcpy((U8 *)&(rsp->t.s1SetupRsp.plmnIds[idx]),
                  (U8 *)&(mmeCb->plmnIds[idx]), sizeof(NbtPlmnId));
      }

      rsp->t.s1SetupRsp.numGrpIds = mmeCb->numGrpIds;
      for (idx = 0; idx < mmeCb->numGrpIds; idx++)
      {
         rsp->t.s1SetupRsp.groupIds[idx] = mmeCb->groupIds[idx];
      }

      rsp->t.s1SetupRsp.numCodes = mmeCb->numCodes;
      for (idx = 0; idx < mmeCb->numCodes; idx++)
      {
         rsp->t.s1SetupRsp.codes[idx] = mmeCb->codes[idx];
      }

      /* Relative MME Capacity */
      rsp->t.s1SetupRsp.relCapacity = mmeCb->relCapacity;
      /* MME Name */
      rsp->t.s1SetupRsp.mmeName.len = mmeCb->mmeName.len;
      cmMemcpy(rsp->t.s1SetupRsp.mmeName.val, mmeCb->mmeName.val,
               mmeCb->mmeName.len);
      /* MME Relay Support Indication */
      rsp->t.s1SetupRsp.mmeRelaySuppInd = mmeCb->mmeRelaySuppInd;
   }

   if(ROK != cmPkNbtMsgRsp(&pst, rsp))
   {
      NB_LOG_ERROR(&nbCb,"Failed to send message to TFW App");
   }
} /* nbUiSendSuccessResponseToUser */

PUBLIC S16 nbUiSendResetAckToUser(NbResetAckldg *resetAck)
{
   NbtResponse *rsp = NULLP;
   Pst pst;

   NB_ALLOC(&rsp, sizeof(NbtResponse));

   rsp->msgType = NB_RESET_ACK;
   SM_SET_ZERO(&pst, sizeof(Pst));

   pst.selector  = 0;
   pst.srcEnt    = ENTNB;
   pst.dstEnt    = ENTFW;
   pst.srcProcId = 0;
   pst.dstProcId = 0;
   pst.region = smCfgCb.init.region;
   pst.pool = smCfgCb.init.pool;
   pst.srcInst = 0;

   rsp->t.resetAck.status = resetAck->status;
   rsp->t.resetAck.numOfUes = resetAck->numOfUes;

   if(rsp->t.resetAck.numOfUes)
   {
      NB_ALLOC(&rsp->t.resetAck.ueIdLst, rsp->t.resetAck.numOfUes);
      cmMemcpy(rsp->t.resetAck.ueIdLst, resetAck->ueIdLst,
            rsp->t.resetAck.numOfUes);
   }

   if(ROK != cmPkNbtMsgRsp(&pst, rsp))
   {
      NB_LOG_ERROR(&nbCb,"Failed to send message to TFW App");
      RETVOID(RFAILED);
   }

   RETVALUE(ROK);
} /* nbUiSendResetAckToUser */

PUBLIC S16 nbUiSendUeCtxRelIndToUser(U32 ueId)
{
   NbtResponse *rsp = NULLP;
   Pst pst;

   NB_ALLOC(&rsp, sizeof(NbtResponse));

   rsp->msgType = NB_UE_CTX_REL_IND;
   SM_SET_ZERO(&pst, sizeof(Pst));

   pst.selector  = 0;
   pst.srcEnt    = ENTNB;
   pst.dstEnt    = ENTFW;
   pst.srcProcId = 0;
   pst.dstProcId = 0;
   pst.region = smCfgCb.init.region;
   pst.pool = smCfgCb.init.pool;
   pst.srcInst = 0;

   rsp->t.ueCtxRelInd.ueId = ueId;

   if(ROK != cmPkNbtMsgRsp(&pst, rsp))
   {
      NB_LOG_ERROR(&nbCb,"Failed to send message to TFW App");
      RETVOID(RFAILED);
   }

   RETVALUE(ROK);
} /* nbUiSendUeCtxRelIndToUser */

PUBLIC S16 nbUiSendIntCtxtSetupIndToUser(U32 ueId, U8 status)
{
   NbtResponse *rsp = NULLP;
   Pst pst;

   NB_ALLOC(&rsp, sizeof(NbtResponse));

   rsp->msgType = NB_INT_CTX_SETUP_IND;
   SM_SET_ZERO(&pst, sizeof(Pst));

   pst.selector  = 0;
   pst.srcEnt    = ENTNB;
   pst.dstEnt    = ENTFW;
   pst.srcProcId = 0;
   pst.dstProcId = 0;
   pst.region = smCfgCb.init.region;
   pst.pool = smCfgCb.init.pool;
   pst.srcInst = 0;

   rsp->t.IntCtxtSetUpInd.ueId = ueId;
   rsp->t.IntCtxtSetUpInd.status = status;

   if(ROK != cmPkNbtMsgRsp(&pst, rsp))
   {
      NB_LOG_ERROR(&nbCb,"Failed to send message to TFW App");
      RETVOID(RFAILED);
   }

   RETVALUE(ROK);
} /* nbUiSendUeCtxRelIndToUser */

PUBLIC S16 nbUiSendIntCtxtSetupDrpdIndToUser(U32 ueId)
{
   NbtResponse *rsp = NULLP;
   Pst pst;

   NB_ALLOC(&rsp, sizeof(NbtResponse));

   rsp->msgType = NB_INIT_CTXT_SETUP_DROPPD_IND;
   SM_SET_ZERO(&pst, sizeof(Pst));

   pst.selector  = 0;
   pst.srcEnt    = ENTNB;
   pst.dstEnt    = ENTFW;
   pst.srcProcId = 0;
   pst.dstProcId = 0;
   pst.region = smCfgCb.init.region;
   pst.pool = smCfgCb.init.pool;
   pst.srcInst = 0;

   rsp->t.intCtxtSetUpDrpdInd.ueId = ueId;

   if(ROK != cmPkNbtMsgRsp(&pst, rsp))
   {
      NB_LOG_ERROR(&nbCb,"Failed to send message to TFW App");
      RETVOID(RFAILED);
   }

   RETVALUE(ROK);
}
 
PUBLIC S16 nbUiSendErabRelCmdInfoToUser(NbErabRelCmd *erabRelInfo)
{
   NbtResponse *rsp = NULLP;
   Pst pst;

   NB_ALLOC(&rsp, sizeof(NbtResponse));

   rsp->msgType = NB_ERAB_REL_CMD_IND;
   SM_SET_ZERO(&pst, sizeof(Pst));

   pst.selector  = 0;
   pst.srcEnt    = ENTNB;
   pst.dstEnt    = ENTFW;
   pst.srcProcId = 0;
   pst.dstProcId = 0;
   pst.region = smCfgCb.init.region;
   pst.pool = smCfgCb.init.pool;
   pst.srcInst = 0;

   rsp->t.erabRelCmdInfo.ueId = erabRelInfo->ueId;
   rsp->t.erabRelCmdInfo.enbUeS1apId = erabRelInfo->enbUeS1apId;
   rsp->t.erabRelCmdInfo.mmeUeS1apId = erabRelInfo->mmeUeS1apId;
   rsp->t.erabRelCmdInfo.numOfErabIds = erabRelInfo->numOfErabIds;
   NB_ALLOC(&rsp->t.erabRelCmdInfo.erabIdLst,
         rsp->t.erabRelCmdInfo.numOfErabIds * sizeof(U8));
   cmMemcpy(rsp->t.erabRelCmdInfo.erabIdLst, erabRelInfo->erabIdLst,
         rsp->t.erabRelCmdInfo.numOfErabIds * sizeof(U8));

   if(ROK != cmPkNbtMsgRsp(&pst, rsp))
   {
      NB_LOG_ERROR(&nbCb, "Failed to send message to TFW App");
      RETVOID(RFAILED);
   }

   RETVALUE(ROK);
} /* nbUiSendErabRelCmdInfoToUser */

PUBLIC S16 nbUiSendPathSwReqAckToUser(NbPathSwReqAck *pathSwReqAck)
{
   NbtResponse *rsp = NULLP;
   Pst pst;

   NB_ALLOC(&rsp, sizeof(NbtResponse));

   rsp->msgType = NB_PATH_SW_REQ_ACK;
   SM_SET_ZERO(&pst, sizeof(Pst));

   pst.selector  = 0;
   pst.srcEnt    = ENTNB;
   pst.dstEnt    = ENTFW;
   pst.srcProcId = 0;
   pst.dstProcId = 0;
   pst.region = smCfgCb.init.region;
   pst.pool = smCfgCb.init.pool;
   pst.srcInst = 0;

   cmMemcpy(&rsp->t.pathSwReqAck,pathSwReqAck, sizeof(NbPathSwReqAck));

   if(ROK != cmPkNbtMsgRsp(&pst, rsp))
   {
      NB_LOG_ERROR(&nbCb,"Failed to send message to TFW App");
      RETVOID(RFAILED);
   }

   RETVALUE(ROK);
} /* nbUiSendPathSwReqAckToUser */

//PUBLIC S16 nbUiSendMmeConfigTrfToUser(NbMmeConfigTrf *mmeConfigTrf)
PUBLIC S16 nbUiSendMmeConfigTrfToUser(NbMmeConfigTrnsf *mmeConfigTrnsf)
{
   NbtResponse *rsp = NULLP;
   Pst pst;

   NB_ALLOC(&rsp, sizeof(NbtResponse));

   rsp->msgType = NB_MME_CONFIG_TRANSFER;
   SM_SET_ZERO(&pst, sizeof(Pst));

   pst.selector  = 0;
   pst.srcEnt    = ENTNB;
   pst.dstEnt    = ENTFW;
   pst.srcProcId = 0;
   pst.dstProcId = 0;
   pst.region = smCfgCb.init.region;
   pst.pool = smCfgCb.init.pool;
   pst.srcInst = 0;

   cmMemcpy(&rsp->t.mmeConfigTrnsf,mmeConfigTrnsf, sizeof(NbMmeConfigTrnsf));

   if(ROK != cmPkNbtMsgRsp(&pst, rsp))
   {
      NB_LOG_ERROR(&nbCb,"Failed to send message to TFW App");
      RETVOID(RFAILED);
   }

   RETVALUE(ROK);
} /* nbUiSendMmeConfigTrfToUser */

// Post a message to tfw app
PUBLIC Void nbUiSendAssocDownIndToUser() {
  NbtResponse *rsp = NULLP;
  Pst pst;
  NbUeCb *ueCb = NULLP, *prev = NULLP;
  NbMmeCb *mmeCb = NULLP;

  NB_LOG_ENTERFN(&nbCb);
  mmeCb = &nbCb.mmeInfo;
  if (mmeCb == NULLP) {
    RETVOID;
  }

  NB_ALLOC(&rsp, sizeof(NbtResponse));
  if (rsp == NULLP) {
    NB_LOG_ERROR(&nbCb, "Failed to allocate memory for NbtResponse");
    RETVOID;
  }
  rsp->msgType = NB_NW_INITIATED_ASSOC_DOWN;
  SM_SET_ZERO(&pst, sizeof(Pst));

  pst.selector = 0;
  pst.srcEnt = ENTNB;
  pst.dstEnt = ENTFW;
  pst.srcProcId = 0;
  pst.dstProcId = 0;
  pst.region = smCfgCb.init.region;
  pst.pool = smCfgCb.init.pool;
  pst.srcInst = 0;

  // Change the state in order to process new S1 SETUP REQ
  smCfgCb.smState = NB_SM_STATE_AWAIT_S1_CON;
  mmeCb->state = NB_MME_INITED;
  if (ROK != cmPkNbtMsgRsp(&pst, rsp)) {
    NB_LOG_ERROR(&nbCb, "Failed to send message to TFW App");
    RETVOID;
  }
  // flag to inform enbApp that it is local release
  uesLocalRel = TRUE;

  while (cmHashListGetNext(&(nbCb.ueCbLst), (PTR)prev, (PTR *)&ueCb) == ROK) {
    /* Inform the UeApp about UE context release */
    if (ROK != nbSendS1RelIndToUeApp(ueCb->ueId)) {
      NB_LOG_ERROR(&nbCb, "Failed to send Release Indication to UeApp");
    }

    /* Trigger ueCb deletion in DAM */
    NB_LOG_DEBUG(&nbCb, "Passing UE Delete Indication to DAM");
    if (ROK != nbIfmDamUeDelReq(ueCb->ueId)) {
      NB_LOG_ERROR(&nbCb, "Failed to send UE Delete Indication to DAM");
    }
    prev = NULLP;
    /* Delete hash list entry for ueCb */
    cmHashListDelete(&(nbCb.ueCbLst), (PTR)ueCb);
  }
} /* nbUiSendAssocDownIndToUser */

PUBLIC S16 NbUiNbuHdlUeIpInfoRej(Pst *pst, NbuUeIpInfoRej *rej) {
  S16 retVal = ROK;

  retVal = NbHandleUeIpInfoRej(rej);
  RETVALUE(retVal);
} /* NbUiNbuHdlUeIpInfoRej */
