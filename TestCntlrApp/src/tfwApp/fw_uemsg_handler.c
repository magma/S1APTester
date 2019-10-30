/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

/********************************************************************20**

    Name:  LTE S1SIM - TFW
 
    Type:  C include file
 
    Desc:  C source code to handle messages coming from UeApp.
 
    File:  fw_uemsg_handler.c
 
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
#include "cm_tkns.x"
#include "cm_dns.x"        /* common DNS Library */
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

EXTERN FwCb gfwCb;

PUBLIC S16 sendUeIdentReqIndToTstCntlr(UetMessage *uetMsg);
PUBLIC S16 sendUeAuthReqIndToTstCntlr(UetMessage *uetMsg);
PUBLIC S16 sendUeAttachAcceptIndToTstCntlr(UetResponse *uetMsg);
PUBLIC S16 sendUeAttachFailIndToTstCntlr(FwCb *fwCb, UeIdCb *ueIdCb,
                                         U16 reason);
PUBLIC S16 sendUePdnConnTimeOutIndToTstCntlr(FwCb *fwCb, UeIdCb *ueIdCb);
PUBLIC S16 sendUeSecModCmdIndToTstCntlr(UetResponse *uetMsg);
PUBLIC S16 sendUeDetachAcceptIndToTstCntlr(UetResponse *uetMsg);
PUBLIC S16 sendUeTauAcceptIndToTstCntlr(UetResponse *uetMsg);
PUBLIC S16 sendUeAttachRejectIndToTstCntrl(UetResponse *uetMsg);
PUBLIC S16 sendUeServiceRejectIndToTstCntrl(UetResponse *uetMsg);
PUBLIC S16 sendUeEmmInformationToTstCntlr( UetMessage *ueEmmInformation);

PUBLIC S16 handleAttachAcceptInd(Pst *, UetMessage *);
PUBLIC S16 handleAttachRejInd(Pst *pst, UetMessage *uetAttachRejInd);
PUBLIC S16 handleServiceRejInd(Pst *pst, UetMessage *uetServiceRejInd);
PUBLIC S16 handleTauAcceptInd(Pst *pst, UetMessage *uetTauAccept);
PUBLIC S16 handleDetachAcceptInd(Pst *pst, UetResponse *uetRspMsg );

PUBLIC S16 ueIdentReqInd(Pst *pst, UetMessage *uetIdentReqInd);
PUBLIC S16 ueAuthReqInd(Pst *pst, UetMessage *uetAuthReqInd);
PUBLIC S16 ueSecModCmdInd(Pst *, UetMessage *);
PUBLIC S16 sendUeTauRejectIndToTstCntrl(UetResponse *uetMsg);
PUBLIC S16 handleTauRejectInd(Pst *pst, UetMessage *);
PRIVATE S16 handlePdnConRspInd (Pst *pst, UetMessage *uetPdnConRspInd);
PRIVATE Void fwFillEsmInfo(ue_Esm_Info *fwEsmInfo,UeEsmInfo *esmInfo); 
PRIVATE S16 sendUePdnConRspIndToTstCntlr(UetResponse *uetMsg);
PUBLIC S16 handlePagingInd( Pst *pst,  UetMessage *uetPagingtInd);
PUBLIC S16 sendUePagingIndToTstCntlr(UetMessage *uetPagingInd);
PRIVATE S16 handleNwInitDetachReqInd(Pst *pst, UetMessage *uetNwinitDetachInd);
PUBLIC S16 sendUeNwInitDetachReqIndToTstCntlr(UetMessage *uetNwInitDetachInd);
PRIVATE Void delete_ue_entries(U8);
PRIVATE S16 handleAndSendActDedBerReqInd (Pst *pst, UetMessage *msgreq);
PRIVATE S16 handleAndSendDeActvBerReqInd (Pst *pst, UetMessage *msgreq);
PRIVATE S16 handleEmmInformation ( Pst *pst,  UetMessage *ueEmmInformation);
PRIVATE S16 handleAuthRejectInd ( Pst *pst,UetMessage *ueUetAuthRejInd);
PRIVATE S16 handleEsmInformationReq( Pst *pst, UetMessage *ueEsmInformationReq);
PUBLIC S16 sendUeEsmInformationReqToTstCntlr( UetMessage *ueEsmInfoReq);

/*
*        Fun:  sendUeAppConfigRespToTstCntlr
*
*        Desc:  Sends UE App Config Response to TC stub
*
*        Ret:   ROK
* 
*        Notes: None
* 
*        File: fw_uemsg_handler.c 
* 
*/
PUBLIC S16 sendUeAppConfigRespToTstCntlr(UetResponse *uetMsg)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   ueAppConfigCompleteInd_t *msg = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &msg , sizeof(ueAppConfigCompleteInd_t));
   cmMemset((U8*)msg, 0, sizeof(ueAppConfigCompleteInd_t));

   msg->status = uetMsg->msg.ueAppCfgCompInd.cfgStatus;
   (fwCb->testConrollerCallBack)(UE_APP_CONFIG_COMPLETE_IND, msg,
                                  sizeof(ueAppConfigCompleteInd_t));
   FW_FREE_MEM(fwCb, msg, sizeof(ueAppConfigCompleteInd_t));
   FW_LOG_EXITFN(fwCb, ret);
} /* sendUeAppConfigRespToTstCntlr */

/*
*        Fun:   handleMessageFromUeApp 
*
*        Desc:  Handles all the messages from Ue App
*
*        Ret:   ROK
* 
*        Notes: None
* 
*        File: fw_uemsg_handler.c 
* 
*/
PUBLIC S16 handleMessageFromUeApp
(
 Pst *pst,
 UetResponse *uetRspMsg
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   switch (uetRspMsg->msgType)
   {
      case UE_APP_CONFIG_COMPLETE_TYPE:
      {
         FW_LOG_DEBUG(fwCb, "Recieved Ue App Config Complete Indication");
         if (uetRspMsg->msg.ueAppCfgCompInd.cfgStatus == SUCCESS)
         {
            fwCb->ueState = UE_REGISTERED;
         }
         ret = sendUeAppConfigRespToTstCntlr(uetRspMsg);
         break;
      }
      case UE_CONFIG_COMPLETE_TYPE:
      {
         FW_LOG_DEBUG(fwCb, "Recieved Ue Config Complete Indication");
         ret = sendUeConfigRespToTstCntlr(uetRspMsg);
         break;
      }
      case UE_IDENTITY_REQ_IND_TYPE:
      {
         FW_LOG_DEBUG(fwCb, "Recieved Identity Request Indication");
         ueIdentReqInd(pst, uetRspMsg);
         break;
      }
      case UE_AUTH_REQ_IND_TYPE:
      {
         FW_LOG_DEBUG(fwCb, "Recieved Auth Indication");
         /*ret = sendUeAuthReqIndToTstCntlr(uetRspMsg);*/
         ueAuthReqInd(pst, uetRspMsg);
         break;
      }
      case UE_SEC_MOD_CMD_IND_TYPE:
      {
         FW_LOG_DEBUG(fwCb, "Recieved Security Mode command Indication");
         /* Comment this section to test AttachTimer expiry */
         ueSecModCmdInd(pst,uetRspMsg); 
         break;
      }
      case UE_ATTACH_ACCEPT_IND_TYPE:
      {
         FW_LOG_DEBUG(fwCb, "Recieved Attach Accept Indication");
         /* Comment this section to test AttachTimer expiry */
         handleAttachAcceptInd(pst, uetRspMsg);
         break;
      }
      case UE_TAU_ACCEPT_TYPE:
      {
         FW_LOG_DEBUG(fwCb, "Recieved TAU Accept Indication");
         handleTauAcceptInd(pst, uetRspMsg);
         break;
      }
      case UE_TAU_REJECT_TYPE:
      {
         FW_LOG_DEBUG(fwCb, "Recieved TAU Reject Indication");
         handleTauRejectInd(pst, uetRspMsg);
         break;
      }
      case UE_ATTACH_REJ_TYPE:
      {
         FW_LOG_DEBUG(fwCb, "Recieved Attach Reject Indication");
         handleAttachRejInd(pst, uetRspMsg);
         break;
      }
      case UE_SERVICE_REJ_TYPE:
      {
         FW_LOG_DEBUG(fwCb, "Recieved Service Reject Indication");
         handleServiceRejInd(pst, uetRspMsg);
         break;
      }
      case UE_DETACH_ACCEPT_IND_TYPE:
      {
         FW_LOG_DEBUG(fwCb, "Recieved Detach Accept Indication");
         handleDetachAcceptInd(pst, uetRspMsg);
         break;
      }
      case UE_PDN_CON_RSP_TYPE:
      {
         FW_LOG_DEBUG(fwCb, "Recieved Pdn Connection response Indication");
         handlePdnConRspInd(pst, uetRspMsg);
         break;
      }
      case UE_PAGING_MSG_TYPE:
      {
         FW_LOG_DEBUG(fwCb, "Recieved Paging Indication");
	      handlePagingInd(pst, uetRspMsg);
	      break;
      }
      case UE_NW_INIT_DETACH_REQUEST_TYPE:
      {
         FW_LOG_DEBUG(fwCb, "Recieved Pdn Connection response Indication");
         handleNwInitDetachReqInd(pst, uetRspMsg);
         break;
      }
      case UE_EPS_DED_BER_REQ:
      {
         FW_LOG_DEBUG(fwCb, "Recieved Activate Dedicated Bearer Request Indication\n");
         handleAndSendActDedBerReqInd(pst, uetRspMsg);
         break;
      }
      case UE_EPS_DEACTIVATE_BER_REQ:
      {
         FW_LOG_DEBUG(fwCb, "Recieved De-Activate Bearer Request Indication\n");
         handleAndSendDeActvBerReqInd(pst, uetRspMsg);
         break;
      }
      case UE_EMM_INFORMATION_TYPE:
      {
         FW_LOG_DEBUG(fwCb, "Recieved EMM Information from Network");
         handleEmmInformation(pst,uetRspMsg);
         break;
      }
      case UE_AUTH_REJ_IND_TYPE:
      {
         FW_LOG_DEBUG(fwCb, "Recieved Authentication Reject from Network");
         handleAuthRejectInd(pst,uetRspMsg);
         break;
      }
      case UE_ESM_INFORMATION_REQ_TYPE:
      {
         FW_LOG_DEBUG(fwCb, "Recieved ESM Information Request from Network");
         handleEsmInformationReq(pst,uetRspMsg);
         break;
      }
      default:
      {
         FW_LOG_ERROR(fwCb, "Invalid message type recieved");
         ret = RFAILED;
         break;
      }
   }

   FW_FREE_MEM(fwCb, uetRspMsg, sizeof(UetResponse));

   FW_LOG_EXITFN(fwCb, ret);
} /* handleMessageFromUeApp */

/*
*        Fun:  sendUeConfigRespToTstCntlr 
*
*        Desc:  Sends ue Config response to TC stub
*
*        Ret:   ROK
* 
*        Notes: None
* 
*        File: fw_uemsg_handler.c 
* 
*/
PUBLIC S16 sendUeConfigRespToTstCntlr(UetResponse *uetMsg)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   ueConfigCompleteInd_t *tfwUeConfigCmplete = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &tfwUeConfigCmplete, sizeof(ueConfigCompleteInd_t));
   cmMemset((U8*)tfwUeConfigCmplete, 0, sizeof(ueConfigCompleteInd_t));

   tfwUeConfigCmplete->status = uetMsg->msg.ueCfgCompInd.cfgStatus;
   (fwCb->testConrollerCallBack)(UE_CONFIG_COMPLETE_IND, tfwUeConfigCmplete,
                                  sizeof(ueConfigCompleteInd_t));

   FW_FREE_MEM(fwCb, tfwUeConfigCmplete, sizeof(ueConfigCompleteInd_t));
   FW_LOG_EXITFN(fwCb, ret);
} /* sendUeConfigRespToTstCntlr */

/*
*        Fun:   sendUeIdentReqIndToTstCntlr
*
*        Desc:  Sends Identity Request indication to TC stub.
*
*        Ret:   ROK
* 
*        Notes: None
* 
*        File:  fw_uemsg_handler.c 
* 
*/
PUBLIC S16 sendUeIdentReqIndToTstCntlr(UetMessage *uetMsg)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   ueIdentityReqInd_t *tfwIdentReq = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);
   
   FW_ALLOC_MEM(fwCb, &tfwIdentReq, sizeof(ueIdentityReqInd_t));
   cmMemset((U8*)tfwIdentReq, 0, sizeof(ueIdentityReqInd_t));
   
   tfwIdentReq->ue_Id = uetMsg->msg.ueUetIdentReqInd.ueId;
   tfwIdentReq->idType = uetMsg->msg.ueUetIdentReqInd.idType;

   FW_LOG_DEBUG(fwCb, "Sending Identity Request Indication Test Stub");
   (fwCb->testConrollerCallBack)(UE_IDENTITY_REQ_IND, tfwIdentReq,
                                  sizeof(ueIdentityReqInd_t));

   FW_FREE_MEM(fwCb, tfwIdentReq, sizeof(ueIdentityReqInd_t));
   FW_LOG_EXITFN(fwCb, ret);
} /* sendUeIdentReqIndToTstCntlr */


/*
*        Fun:   sendUeAuthReqIndToTstCntlr
*
*        Desc:  Sends Auth Request indications.to TC stub
*
*        Ret:   ROK
* 
*        Notes: None
* 
*        File: fw_uemsg_handler.c 
* 
*/
PUBLIC S16 sendUeAuthReqIndToTstCntlr(UetMessage *uetMsg)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   ueAuthReqInd_t *tfwAuthReq = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);
   
   FW_ALLOC_MEM(fwCb, &tfwAuthReq, sizeof(ueAuthReqInd_t));
   cmMemset((U8*)tfwAuthReq, 0, sizeof(ueAuthReqInd_t));
   
   tfwAuthReq->ue_Id = uetMsg->msg.ueUetAuthReqInd.ueId;
   if (uetMsg->msg.ueUetAuthReqInd.KNASVrfySts == TRUE)
   {
      tfwAuthReq->knas_Vrfy_Sts = TRUE;
      cmMemcpy(tfwAuthReq->randm, uetMsg->msg.ueUetAuthReqInd.rand, 16);
      cmMemcpy(tfwAuthReq->autn, uetMsg->msg.ueUetAuthReqInd.autn, 16);
      cmMemcpy(tfwAuthReq->sqn, uetMsg->msg.ueUetAuthReqInd.sqn, 6);
      cmMemcpy(tfwAuthReq->kasme, uetMsg->msg.ueUetAuthReqInd.KASME, 32);
      cmMemcpy(tfwAuthReq->recvd_xres, uetMsg->msg.ueUetAuthReqInd.resXres, 16);
      cmMemcpy(tfwAuthReq->res, uetMsg->msg.ueUetAuthReqInd.res, 16);
   }
   else
   {
      tfwAuthReq->knas_Vrfy_Sts = FALSE;
   }

   (fwCb->testConrollerCallBack)(UE_AUTH_REQ_IND, tfwAuthReq,
                                  sizeof(ueAuthReqInd_t));

   FW_FREE_MEM(fwCb, tfwAuthReq, sizeof(ueAuthReqInd_t));
   FW_LOG_EXITFN(fwCb, ret);
} /* sendUeAuthReqIndToTstCntlr */

/*
*        Fun:   ueIdentReqInd 
*
*        Desc:  Handles Identity Request indications. 
*
*        Ret:   ROK
* 
*        Notes: None
* 
*        File: fw_uemsg_handler.c 
* 
*/
PUBLIC S16 ueIdentReqInd
(
   Pst *pst,
   UetMessage *uetIdentReqInd
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   S16 flag = 0;
   UeIdCb *ueIdCb = NULLP;
   ueIdentityResp_t *identResp = NULL;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   if (uetIdentReqInd->msgType == UE_IDENTITY_REQ_IND_TYPE)
   {
      CmLList  *tmpNode = NULLP;     /* Stores the Ie Node */
      CM_LLIST_FIRST_NODE(&fwCb->ueIdList, tmpNode);
      while (tmpNode != NULLP)
      {
         ueIdCb = (UeIdCb*)tmpNode->node;
         if (ueIdCb->ue_id == uetIdentReqInd->msg.ueUetIdentReqInd.ueId)
         {
            FW_LOG_DEBUG(fwCb, "Found ueId(%d)",
                         uetIdentReqInd->msg.ueUetIdentReqInd.ueId);
            flag = 1;
            ueIdCb->state = UE_IDENTITY_REQ_IND_DONE;  /*Update the state */
            ueIdCb->link.node = (PTR)ueIdCb;
         }
         tmpNode = tmpNode->next;
      }

      /* if ueid found,(END TO END ATTACH) prepare
       * Identity response and send to ue app */
      if (flag == 1)
      {
         FW_ALLOC_MEM(fwCb, &identResp, sizeof(ueIdentityResp_t));
         identResp->ue_Id = uetIdentReqInd->msg.ueUetIdentReqInd.ueId;
         identResp->idType = uetIdentReqInd->msg.ueUetIdentReqInd.idType;

         handlIdentResp(identResp);
         ueIdCb->state = UE_IDENTITY_RESP_DONE; /*Update the state */
         FW_FREE_MEM(fwCb, identResp, sizeof(ueIdentityResp_t));
      }
      /*else, send to test controller*/
      else
      {
         sendUeIdentReqIndToTstCntlr(uetIdentReqInd);   
      }
   }

   FW_LOG_EXITFN(fwCb, ret);
} /* ueIdentReqInd */


/*
*        Fun:   ueAuthReqInd 
*
*        Desc:  Handles Auth Request indications. 
*
*        Ret:   ROK
* 
*        Notes: None
* 
*        File: fw_uemsg_handler.c 
* 
*/
PUBLIC S16 ueAuthReqInd
(
 Pst *pst,
 UetMessage *uetAuthReqInd
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   S16 flag = 0;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   if(uetAuthReqInd->msgType == UE_AUTH_REQ_IND_TYPE)
   {
      UeIdCb *ueIdCb  = NULLP;
      CmLList  *tmpNode = NULLP;     /* Stores the Ie Node */

      CM_LLIST_FIRST_NODE(&fwCb->ueIdList, tmpNode);
      while (tmpNode != NULLP)
      {
         ueIdCb = (UeIdCb*)tmpNode->node;
         if (ueIdCb->ue_id == uetAuthReqInd->msg.ueUetAuthReqInd.ueId)
         {
            FW_LOG_DEBUG(fwCb, "ue id %d found",
                   uetAuthReqInd->msg.ueUetAuthReqInd.ueId);
            flag = 1;
            ueIdCb->state = UE_AUTH_REQ_IND_DONE;  /*Update the state */
            ueIdCb->link.node = (PTR)ueIdCb;
         }
         tmpNode = tmpNode->next;
      }

      /* if ueid found,(END TO END ATTACH) prepare
       * Auth response and send to ue app */
      if (flag == 1)
      {
         ueAuthResp_t *authResp = NULL;
         FW_ALLOC_MEM(fwCb, &authResp, sizeof(ueAuthResp_t));
         authResp->ue_Id = uetAuthReqInd->msg.ueUetAuthReqInd.ueId;
         authResp->sqnRcvd.pres = FALSE;
         handlAuthResp(authResp);
         ueIdCb->state = UE_AUTH_RESP_DONE; /*Update the state */
         FW_FREE_MEM(fwCb, authResp, sizeof(ueAuthResp_t));
      }
      /*else, send to test controller*/
      else
      {
         sendUeAuthReqIndToTstCntlr(uetAuthReqInd);   
      }
   }

   FW_LOG_EXITFN(fwCb, ret);
} /* ueAuthReqInd */


/*
*        Fun:  sendUeSecModCmdIndToTstCntlr 
*
*        Desc: Sends Security Mod Command Ind to TC stub 
*
*        Ret:   ROK
* 
*        Notes: None
* 
*        File: fw_uemsg_handler.c 
* 
*/
PUBLIC S16 sendUeSecModCmdIndToTstCntlr(UetResponse *uetMsg)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   ueSecModeCmdInd_t *tfwUeSecModCmdInd = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &tfwUeSecModCmdInd , sizeof(ueSecModeCmdInd_t));
   cmMemset((U8*)tfwUeSecModCmdInd, 0, sizeof(ueSecModeCmdInd_t));   

   tfwUeSecModCmdInd->ue_Id =uetMsg->msg.ueUetSecModeCmdInd.ueId;
   tfwUeSecModCmdInd->nas_cyp_cfg = \
                  uetMsg->msg.ueUetSecModeCmdInd.NasCyphCfg;
   tfwUeSecModCmdInd->nas_int_prot_cfg = \
                  uetMsg->msg.ueUetSecModeCmdInd.NasIntProtCfg;
   cmMemcpy(tfwUeSecModCmdInd->kasme, \
         uetMsg->msg.ueUetSecModeCmdInd.Kasme, MAX_KASME_KEY);
   cmMemcpy(tfwUeSecModCmdInd->knas_enc, \
         uetMsg->msg.ueUetSecModeCmdInd.KNasEnc, MAX_NAS_ENC_KEY);
   cmMemcpy(tfwUeSecModCmdInd->knas_int,
         uetMsg->msg.ueUetSecModeCmdInd.KNasInt, MAX_NAS_INT_KEY);
   tfwUeSecModCmdInd->knas_Vrfy_Sts = \
                  uetMsg->msg.ueUetSecModeCmdInd.KNasVrfySts;

   (fwCb->testConrollerCallBack)(UE_SEC_MOD_CMD_IND, tfwUeSecModCmdInd,
                                  sizeof(ueSecModeCmdInd_t));

   FW_FREE_MEM(fwCb, tfwUeSecModCmdInd , sizeof(ueSecModeCmdInd_t));
   FW_LOG_EXITFN(fwCb, ret);
} /* sendUeSecModCmdIndToTstCntlr */

/*
*        Fun:  ueSecModCmdInd 
*
*        Desc:  Handles Ue Security mode Indication
*
*        Ret:   ROK
* 
*        Notes: None
* 
*        File: fw_uemsg_handler.c 
* 
*/
PUBLIC S16 ueSecModCmdInd
(
 Pst *pst,
 UetMessage *uetSecModCmdInd
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   S16 flag = 0;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   if (uetSecModCmdInd->msgType == UE_SEC_MOD_CMD_IND_TYPE)
   {
      UeIdCb *ueIdCb  = NULLP;

      CmLList  *tmpNode = NULLP;     /* Stores the Ie Node */
      CM_LLIST_FIRST_NODE(&fwCb->ueIdList, tmpNode);
      while (tmpNode != NULLP)
      {
         ueIdCb = (UeIdCb*)tmpNode->node;
         if (ueIdCb->ue_id == uetSecModCmdInd->msg.ueUetSecModeCmdInd.ueId)
         {
            printf("ue id %d found\n",
                  uetSecModCmdInd->msg.ueUetSecModeCmdInd.ueId);
            flag = 1;
            ueIdCb->state = UE_SEC_MOD_CMD_IND_DONE;  /*Update the state */
            ueIdCb->link.node = (PTR)ueIdCb;
         }
         tmpNode = tmpNode->next;
      }
      /* if ueid found,(END TO END ATTACH) prepare Security
       * Mode complete and send to ue app */
      if (flag == 1)
      {
         ueSecModeComplete_t *secModComp = NULLP;
         FW_ALLOC_MEM(fwCb, &secModComp, sizeof(ueSecModeComplete_t));
         secModComp->ue_Id = uetSecModCmdInd->msg.ueUetSecModeCmdInd.ueId;
         handlSecModComp(secModComp);
         ueIdCb->state = UE_SEC_MOD_COMPLETE_DONE;
         FW_FREE_MEM(fwCb, secModComp, sizeof(ueSecModeComplete_t));
      }
      /*else, send to test controller*/
      else
      {
         sendUeSecModCmdIndToTstCntlr(uetSecModCmdInd);  
      } 
   }

   FW_LOG_EXITFN(fwCb, ret);
} /* ueSecModCmdInd */

/*
*        Fun:  sendUeTauAcceptIndToTstCntlr 
*
*        Desc:  Sends TAU Accept Ind to TC stub
*
*        Ret:   ROK
* 
*        Notes: None
* 
*        File: fw_uemsg_handler.c 
* 
*/
PUBLIC S16 sendUeTauAcceptIndToTstCntlr(UetResponse *uetMsg)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   ueTauAccept_t *tfwTauAccept = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &tfwTauAccept , sizeof(ueTauAccept_t));
   cmMemset((U8*)tfwTauAccept, 0, sizeof(ueTauAccept_t));
   
   tfwTauAccept->ue_Id = uetMsg->msg.ueUetTauAccept.ueId;
   tfwTauAccept->epsUpdateRes = uetMsg->msg.ueUetTauAccept.epsUpdateRes;
   tfwTauAccept->gutiChanged = uetMsg->msg.ueUetTauAccept.gutiChanged;

   cmMemcpy(tfwTauAccept->guti.mcc, uetMsg->msg.ueUetTauAccept.guti.mcc, 3);
   cmMemcpy(tfwTauAccept->guti.mnc, uetMsg->msg.ueUetTauAccept.guti.mnc, 3);
   tfwTauAccept->guti.mmeGrdId = uetMsg->msg.ueUetTauAccept.guti.mmeGrpId;
   tfwTauAccept->guti.mmeCode = uetMsg->msg.ueUetTauAccept.guti.mmeCode;
   tfwTauAccept->guti.mTmsi = uetMsg->msg.ueUetTauAccept.guti.mTMSI;

   (fwCb->testConrollerCallBack)(UE_TAU_ACCEPT_IND, tfwTauAccept,
                                  sizeof(ueTauAccept_t));

   FW_FREE_MEM(fwCb, tfwTauAccept , sizeof(ueTauAccept_t));
   FW_LOG_EXITFN(fwCb, ret);
}

/*
*        Fun:  sendUeAttachAcceptIndToTstCntlr 
*
*        Desc:  Sends Attact Accept Ind To TC stub
*
*        Ret:   ROK
* 
*        Notes: None
* 
*        File: fw_uemsg_handler.c 
* 
*/
PUBLIC S16 sendUeAttachAcceptIndToTstCntlr(UetResponse *uetMsg)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   U32 i;
   ueAttachAccept_t *tfwUeAttachAccept = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &tfwUeAttachAccept, sizeof(ueAttachAccept_t));
   cmMemset((U8*)tfwUeAttachAccept, 0, sizeof(ueAttachAccept_t));

   tfwUeAttachAccept->ue_Id = uetMsg->msg.ueUetAttachAcceptInd.ueId;
   tfwUeAttachAccept->eps_Atch_resp =\
       uetMsg->msg.ueUetAttachAcceptInd.epsAtchRes;
   
   if (!uetMsg->msg.ueUetAttachAcceptInd.t3412 == 0)
   {
      tfwUeAttachAccept->t3412 = uetMsg->msg.ueUetAttachAcceptInd.t3412;
   }

   cmMemcpy(tfwUeAttachAccept->guti.mcc,
         uetMsg->msg.ueUetAttachAcceptInd.guti.mcc,3);
   cmMemcpy(tfwUeAttachAccept->guti.mnc,
         uetMsg->msg.ueUetAttachAcceptInd.guti.mnc,3);
   tfwUeAttachAccept->guti.mmeGrdId =\
         uetMsg->msg.ueUetAttachAcceptInd.guti.mmeGrpId;
   tfwUeAttachAccept->guti.\
      mmeCode = uetMsg->msg.ueUetAttachAcceptInd.guti.mmeCode;
   tfwUeAttachAccept->guti.\
      mTmsi = uetMsg->msg.ueUetAttachAcceptInd.guti.mTMSI;
   
   cmMemcpy(tfwUeAttachAccept->lai.mcc,
         uetMsg->msg.ueUetAttachAcceptInd.lai.mcc,3);
   cmMemcpy(tfwUeAttachAccept->lai.mnc,
         uetMsg->msg.ueUetAttachAcceptInd.lai.mnc,3);
   tfwUeAttachAccept->lai.\
      lac = uetMsg->msg.ueUetAttachAcceptInd.lai.lac;
   
   cmMemcpy(tfwUeAttachAccept->ms_id,
         uetMsg->msg.ueUetAttachAcceptInd.msId, CM_EMM_MAX_MOBILE_ID_DIGS);

   tfwUeAttachAccept->cause = uetMsg->msg.ueUetAttachAcceptInd.cause;

   tfwUeAttachAccept->t3402 = uetMsg->msg.ueUetAttachAcceptInd.t3402;

   tfwUeAttachAccept->t3423 = uetMsg->msg.ueUetAttachAcceptInd.t3423;
   
   for (i = 0; i < 6; i++)
   {
      cmMemcpy(tfwUeAttachAccept->plmn_lst[i].mcc,
               uetMsg->msg.ueUetAttachAcceptInd.plmnList[i].mcc, 3);
      cmMemcpy(tfwUeAttachAccept->plmn_lst[i].mcc,
               uetMsg->msg.ueUetAttachAcceptInd.plmnList[i].mnc, 3);
   }
   /* Populating ESM INFO  */
#if 0
   tfwUeAttachAccept->esmInfo.qos.qci\
      = uetMsg->msg.ueUetAttachAcceptInd.esmInfo.qos.qci;
   tfwUeAttachAccept->esmInfo.qos.maxBitRateUL\
      = uetMsg->msg.ueUetAttachAcceptInd.esmInfo.qos.maxBitRateUL;
   tfwUeAttachAccept->esmInfo.qos.maxBitRateDL\
      = uetMsg->msg.ueUetAttachAcceptInd.esmInfo.qos.maxBitRateDL;
   tfwUeAttachAccept->esmInfo.qos.guaraBitRateUL\
      = uetMsg->msg.ueUetAttachAcceptInd.esmInfo.qos.guaraBitRateUL;
   tfwUeAttachAccept->esmInfo.qos.guaraBitRateDL\
      = uetMsg->msg.ueUetAttachAcceptInd.esmInfo.qos.guaraBitRateDL;

   tfwUeAttachAccept->esmInfo.apn.len\
      = uetMsg->msg.ueUetAttachAcceptInd.esmInfo.apn.len;
   cmMemcpy(tfwUeAttachAccept->esmInfo.apn.apn, uetMsg->msg.\
         ueUetAttachAcceptInd.esmInfo.apn.apn,UE_ESM_MAX_LEN_ACCESS_PTNAME);

   tfwUeAttachAccept->esmInfo.pAddr.pdnType\
      = uetMsg->msg.ueUetAttachAcceptInd.esmInfo.pAddr.pdnType;
   cmMemcpy(tfwUeAttachAccept->esmInfo.pAddr.addrInfo,
          uetMsg->msg.ueUetAttachAcceptInd.\
         esmInfo.pAddr.addrInfo,UE_ESM_MAX_LEN_PDN_ADDRESS);

   printf("PDN_TYPE:%d\n", tfwUeAttachAccept->esmInfo.pAddr.pdnType);
   printf("PDN_dDRESS:%d %d %d %d\n",tfwUeAttachAccept->\
         esmInfo.pAddr.addrInfo[0], tfwUeAttachAccept->\
         esmInfo.pAddr.addrInfo[1], tfwUeAttachAccept->\
         esmInfo.pAddr.addrInfo[2], tfwUeAttachAccept->\
         esmInfo.pAddr.addrInfo[3]);

   tfwUeAttachAccept->esmInfo.apnAmbr.len\
      =uetMsg->msg.ueUetAttachAcceptInd.esmInfo.apnAmbr.len;
   tfwUeAttachAccept->esmInfo.apnAmbr.dl\
      = uetMsg->msg.ueUetAttachAcceptInd.esmInfo.apnAmbr.dl;
   tfwUeAttachAccept->esmInfo.apnAmbr.ul\
      = uetMsg->msg.ueUetAttachAcceptInd.esmInfo.apnAmbr.ul;
#endif
    fwFillEsmInfo(&tfwUeAttachAccept->esmInfo,&uetMsg->msg.\
          ueUetAttachAcceptInd.esmInfo);
   (fwCb->testConrollerCallBack)(UE_ATTACH_ACCEPT_IND, tfwUeAttachAccept,
                                  sizeof(ueAttachAccept_t));

   FW_FREE_MEM(fwCb, tfwUeAttachAccept, sizeof(ueAttachAccept_t));
   FW_LOG_EXITFN(fwCb, ret);
}

PRIVATE Void fwFillEsmInfo(ue_Esm_Info *fwEsmInfo, UeEsmInfo *esmInfo) 
{
   U8 count;

   fwEsmInfo->epsBearerId = esmInfo->epsBearerId;
   fwEsmInfo->qos.qci = esmInfo->qos.qci;
   fwEsmInfo->qos.maxBitRateUL = esmInfo->qos.maxBitRateUL;
   fwEsmInfo->qos.maxBitRateDL = esmInfo->qos.maxBitRateDL;
   fwEsmInfo->qos.guaraBitRateUL = esmInfo->qos.guaraBitRateUL;
   fwEsmInfo->qos.guaraBitRateDL = esmInfo->qos.guaraBitRateDL;

   fwEsmInfo->apn.len = esmInfo->apn.len;
   cmMemcpy(fwEsmInfo->apn.apn, esmInfo->apn.apn,UE_ESM_MAX_LEN_ACCESS_PTNAME);

   fwEsmInfo->pAddr.pdnType = esmInfo->pAddr.pdnType;
   cmMemcpy(fwEsmInfo->pAddr.addrInfo, esmInfo->pAddr.addrInfo,
         UE_ESM_MAX_LEN_PDN_ADDRESS);

   printf("PDN_TYPE: %d\n", fwEsmInfo->pAddr.pdnType);
   printf("PDN_ADDRESS: %d %d %d %d\n",fwEsmInfo->pAddr.addrInfo[0],
         fwEsmInfo->pAddr.addrInfo[1],
         fwEsmInfo->pAddr.addrInfo[2],
         fwEsmInfo->pAddr.addrInfo[3]);

   fwEsmInfo->apnAmbr.len = esmInfo->apnAmbr.len;
   fwEsmInfo->apnAmbr.dl = esmInfo->apnAmbr.dl;
   fwEsmInfo->apnAmbr.ul = esmInfo->apnAmbr.ul;
   if (esmInfo->protCfgOpt.pres)
   {
      fwEsmInfo->protCfgOpts_pr.pres = TRUE;
      fwEsmInfo->protCfgOpts_pr.cfgProt = esmInfo->protCfgOpt.cfgProt;
      fwEsmInfo->protCfgOpts_pr.numProtId = esmInfo->protCfgOpt.numProtId;
      fwEsmInfo->protCfgOpts_pr.numContId = esmInfo->protCfgOpt.numContId;
      for(count=0;count<esmInfo->protCfgOpt.numProtId;count++)
      {
         fwEsmInfo->protCfgOpts_pr.p[count].\
            pid = esmInfo->protCfgOpt.p[count].pid;
         cmMemcpy(fwEsmInfo->protCfgOpts_pr.p[count].val, 
               esmInfo->protCfgOpt.p[count].val,
               esmInfo->protCfgOpt.p[count].len);
      }
      for(count=0;count<esmInfo->protCfgOpt.numContId;count++)
      {
         fwEsmInfo->protCfgOpts_pr.c[count].\
            cid = esmInfo->protCfgOpt.c[count].cid;
         cmMemcpy(fwEsmInfo->protCfgOpts_pr.c[count].val,
               esmInfo->protCfgOpt.c[count].val,
               esmInfo->protCfgOpt.c[count].len);
      }
   }
}

/*
 *        Fun:  sendUeAttachFailIndToTstCntlr 
 *
 *        Desc:  Sends Attach fail indication to TC stub
 *
 *        Ret:   ROK
 * 
 *        Notes: None
 * 
 *        File: fw_uemsg_handler.c 
 * 
*/
PUBLIC S16 sendUeAttachFailIndToTstCntlr(FwCb *fwCb, UeIdCb *ueIdCb, U16 reason)
{
   S16 ret = ROK;

   ueAttachFail_t *tfwUeAttachFail = NULLP;
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &tfwUeAttachFail , sizeof(ueAttachFail_t));
   if(tfwUeAttachFail == NULLP)
         RETVALUE(RFAILED);
   cmMemset((U8*)tfwUeAttachFail, 0, sizeof(ueAttachFail_t));

   tfwUeAttachFail->ueId = ueIdCb->ue_id;
   tfwUeAttachFail->ueState = ueIdCb->state;
   tfwUeAttachFail->reason = reason;
   
   FW_LOG_DEBUG(fwCb, "Invoking Test Controller Callback");
   (fwCb->testConrollerCallBack)(UE_ATTACH_FAIL_IND, tfwUeAttachFail,
                                  sizeof(ueAttachFail_t));

   FW_FREE_MEM(fwCb, tfwUeAttachFail,sizeof(ueAttachFail_t));
   FW_LOG_EXITFN(fwCb, ret);
}

/*
 *        Fun:   handleTauAcceptInd 
 *
 *        Desc:  Handles the the TAU Accept indications to test controller
 *
 *        Ret:   ROK
 * 
 *        Notes: None
 * 
 *        File: fw_uemsg_handler.c 
 * 
*/
PUBLIC S16 handleTauAcceptInd
(
 Pst *pst,
 UetMessage *uetTauAccept
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   S16 flag = 0; /* flag == 0(ueid not found), flag==1(found)*/
   UeIdCb *ueIdCb  = NULLP;
   CmLList  *tmpNode = NULLP; /* Stores the Ie Node */
   
   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   CM_LLIST_FIRST_NODE(&fwCb->ueIdList, tmpNode);
   while(tmpNode != NULLP)
   {
      ueIdCb = (UeIdCb*)tmpNode->node;
      if(ueIdCb->ue_id == uetTauAccept->msg.ueUetTauAccept.ueId)
      {
         FW_LOG_DEBUG(fwCb, "ueId %d found", uetTauAccept->msg.ueUetTauAccept.ueId);
         flag = 1;
         ueIdCb->link.node = (PTR)ueIdCb;
         break;
      }
      tmpNode = tmpNode->next;
   }

   if(flag == 1)
   {
      FW_LOG_DEBUG(fwCb, "Stoping T3430 timer for ueId %d", ueIdCb->ue_id);
      ret = sendUeTauAcceptIndToTstCntlr(uetTauAccept);
      fwStopTmr(fwCb, ueIdCb);
      delete_ue_entries(ueIdCb->ue_id);
      FW_FREE_MEM(fwCb, ueIdCb, sizeof(UeIdCb));
   }
   else
   {
      FW_LOG_ERROR(fwCb, "Ue id not found");
      ret = RFAILED;
   }
   FW_LOG_EXITFN(fwCb, ret);
}

/* Deleting the ueid entries from the linked list */
PRIVATE Void delete_ue_entries(U8 ueId)
{
   FwCb *fwCb = NULLP;
   CmLList  *tmpNode = NULLP;
   UeIdCb *ueIdCb;
   
   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);
   
   CM_LLIST_FIRST_NODE(&fwCb->ueIdList, tmpNode);
   while(tmpNode != NULLP)
   {
      ueIdCb = (UeIdCb *)tmpNode->node;
      if(ueId == ueIdCb->ue_id)
      {
         FW_LOG_DEBUG(fwCb, "Ueid %d deleted from linkedlist UeIdCb", ueIdCb->ue_id);
         cmLListDelFrm(&fwCb->ueIdList,tmpNode);
         break;
      }
      tmpNode = tmpNode->next;
   }
   
   FW_LOG_EXITFNVOID(fwCb);
}

/*
 *        Fun:  handleAttachAcceptInd 
 *
 *        Desc:  Handles the Attach accept indication.
 *
 *        Ret:   ROK
 * 
 *        Notes: None
 * 
 *        File: fw_uemsg_handler.c 
 * 
 */
PUBLIC S16 handleAttachAcceptInd
(
 Pst *pst,
 UetMessage *uetAttachAccept
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   S16 flag = 0; /* flag == 0(ueid not found), flag==1(found)*/
   UeIdCb *ueIdCb = NULLP;
   CmLList  *tmpNode = NULLP; /* Stores the Ie Node */

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   if(uetAttachAccept->msgType == UE_ATTACH_ACCEPT_IND_TYPE)
   {
      FW_LOG_DEBUG(fwCb, "Recieved Attach Accept Ind for ueId %d",
                   uetAttachAccept->msg.ueUetAttachAcceptInd.ueId);
      CM_LLIST_FIRST_NODE(&fwCb->ueIdList, tmpNode);
      while(tmpNode != NULLP)
      {
         ueIdCb = (UeIdCb*)tmpNode->node;
         if(ueIdCb->ue_id == uetAttachAccept->msg.ueUetAttachAcceptInd.ueId)
         {
            FW_LOG_DEBUG(fwCb, "ue id %d found\n",
                  uetAttachAccept->msg.ueUetAttachAcceptInd.ueId);
            flag = 1;
            ueIdCb->state = UE_ATTACH_ACCEPT_IND_DONE; /* Update the state */
            /*ueIdCb->link.node = (PTR)ueIdCb;*/
            break;
         }
         tmpNode = tmpNode->next;
      }
      /* if ueid found,(END TO END ATTACH) prepare Attach complete and
       * send to ue app, send Indication to test controller */
      if (flag == 1)
      {
         ueAttachComplete_t *attachComp = NULLP;
         FW_ALLOC_MEM(fwCb, &attachComp, sizeof(ueAttachComplete_t));
         attachComp->ue_Id = uetAttachAccept->msg.ueUetAttachAcceptInd.ueId;
         handlAttachComp(attachComp);
         ueIdCb->state = UE_ATTACH_COMPLETE_DONE; 
         sendUeAttachAcceptIndToTstCntlr(uetAttachAccept);
         FW_FREE_MEM(fwCb, attachComp, sizeof(ueAttachComplete_t));
         /* Stop Attach Timer */
         FW_LOG_DEBUG(fwCb, "Stopping Attach Timer for ue %d", ueIdCb->ue_id);
         fwStopTmr(fwCb, ueIdCb);
         delete_ue_entries(ueIdCb->ue_id);
         FW_FREE_MEM(fwCb, ueIdCb, sizeof(UeIdCb));
      }
      /*else, send to test controller*/
      else
      {
         sendUeAttachAcceptIndToTstCntlr(uetAttachAccept);
      }
   }

   FW_LOG_EXITFN(fwCb, ret);
}

/*
*        Fun:  sendUeDetachAcceptIndToTstCntlr 
*
*        Desc:  Sending the Detach accept indication to TC stub
*
*        Ret:   ROK
* 
*        Notes: None
* 
*        File: fw_uemsg_handler.c 
* 
*/
PUBLIC S16 sendUeDetachAcceptIndToTstCntlr(UetResponse *uetMsg)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   ueDetachAcceptInd_t *tfwUeDetachAcceptInd = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &tfwUeDetachAcceptInd , sizeof(ueDetachAcceptInd_t));
   cmMemset((U8*)tfwUeDetachAcceptInd, 0, sizeof(ueDetachAcceptInd_t));

   tfwUeDetachAcceptInd->ue_Id = uetMsg->msg.ueUetDetachAcceptInd.ueId;
   (fwCb->testConrollerCallBack)(UE_DETACH_ACCEPT_IND, tfwUeDetachAcceptInd,
                                  sizeof(ueDetachAcceptInd_t));

   FW_FREE_MEM(fwCb, tfwUeDetachAcceptInd , sizeof(ueDetachAcceptInd_t));
   FW_LOG_EXITFN(fwCb, ret);
}

PRIVATE S16 sendUePdnConRspIndToTstCntlr(UetResponse *uetMsg)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   uePdnConRsp_t *tfwPdnConRspInd = NULLP;
   Ue_Pdn_Info *pdnInfo = NULLP;
   UePdnInfo   *uePdnInfo  = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &tfwPdnConRspInd, sizeof(uePdnConRsp_t));

   tfwPdnConRspInd->ue_Id = uetMsg->msg.ueUetPdnConRsp.ueId;
   if(uetMsg->msg.ueUetPdnConRsp.status == TRUE)
   {
      tfwPdnConRspInd->status = TRUE;
      pdnInfo = &tfwPdnConRspInd->m.pdnInfo;
      uePdnInfo = &uetMsg->msg.ueUetPdnConRsp.m.pdnInfo; 
      pdnInfo->epsBearerId = uePdnInfo->epsBearerId;
      pdnInfo->apn.len = uePdnInfo->apn.len;
      cmMemcpy(pdnInfo->apn.apn, uePdnInfo->apn.apn,
            UE_ESM_MAX_LEN_ACCESS_PTNAME);

      pdnInfo->pAddr.pdnType = uePdnInfo->pAddr.pdnType;
      cmMemcpy(pdnInfo->pAddr.addrInfo, uePdnInfo->pAddr.addrInfo,
            UE_ESM_MAX_LEN_PDN_ADDRESS);

      printf("PDN_TYPE:%d\n", pdnInfo->pAddr.pdnType);
      printf("PDN_ADDRESS:%d %d %d %d\n",pdnInfo->pAddr.addrInfo[0],
            pdnInfo->pAddr.addrInfo[1],
            pdnInfo->pAddr.addrInfo[2],
            pdnInfo->pAddr.addrInfo[3]);
   }
   else
   {
      tfwPdnConRspInd->status = FALSE;
      tfwPdnConRspInd->m.conRejInfo.cause =     \
         uetMsg->msg.ueUetPdnConRsp.m.pdnConRejInfo.esmCause;
      tfwPdnConRspInd->m.conRejInfo.epsBearerId = \
         uetMsg->msg.ueUetPdnConRsp.m.pdnConRejInfo.epsBearerId;
   }
   (fwCb->testConrollerCallBack)(UE_PDN_CONN_RSP_IND, tfwPdnConRspInd,
                                  sizeof(uePdnConRsp_t));

   FW_FREE_MEM(fwCb, tfwPdnConRspInd, sizeof(uePdnConRsp_t));
   FW_LOG_EXITFN(fwCb, ret);
}

/*
*        Fun:  sendUeAttachRejectIndToTstCntrl
*
*        Desc:  Sends the Attach reject indications to test controller
*
*        Ret:   ROK
* 
*        Notes: None
* 
*        File: fw_uemsg_handler.c 
* 
*/
PUBLIC S16 sendUeAttachRejectIndToTstCntrl
(
 UetMessage *uetAttachRejInd
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   ueAttachRejInd_t *tfwUeAttachRejInd = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &tfwUeAttachRejInd , sizeof(ueAttachRejInd_t));

   tfwUeAttachRejInd->ue_Id = uetAttachRejInd->msg.ueUetAttachRej.ueId;
   tfwUeAttachRejInd->cause = uetAttachRejInd->msg.ueUetAttachRej.cause;
   if (tfwUeAttachRejInd->cause == TFW_EMM_CAUSE_IMSI_UNKNOWN)
   {
      FW_LOG_DEBUG(fwCb, "Attach Rejected:: UNKNOWN IMSI");
   }
   (fwCb->testConrollerCallBack)(UE_ATTACH_REJECT_IND, tfwUeAttachRejInd,
         sizeof(ueAttachRejInd_t));

   FW_FREE_MEM(fwCb, tfwUeAttachRejInd , sizeof(ueAttachRejInd_t));
   FW_LOG_EXITFN(fwCb, ret);
}

/*
 *        Fun:  sendUeServiceRejectIndToTstCntrl 
 *
 *        Desc:  Handles the Send Service reject indication to TC stub
 *
 *        Ret:   ROK
 * 
 *        Notes: None
 * 
 *        File: fw_uemsg_handler.c 
 * 
*/
PUBLIC S16 sendUeServiceRejectIndToTstCntrl
(
 UetMessage *uetServiceRejInd
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   ueServiceRejInd_t *tfwServiceRejInd = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &tfwServiceRejInd , sizeof(ueServiceRejInd_t));

   tfwServiceRejInd->ue_Id = uetServiceRejInd->msg.ueUetServiceRej.ueId;
   tfwServiceRejInd->cause = uetServiceRejInd->msg.ueUetServiceRej.cause;
   (fwCb->testConrollerCallBack)(UE_SERVICE_REJECT_IND, tfwServiceRejInd, 
         sizeof(ueServiceRejInd_t));

   FW_FREE_MEM(fwCb, tfwServiceRejInd, sizeof(ueServiceRejInd_t));
   FW_LOG_EXITFN(fwCb, ret);
}

/*
 *        Fun:  handleAttachRejInd 
 *
 *        Desc:  Handles the Attach reject indication
 *
 *        Ret:   ROK
 * 
 *        Notes: None
 * 
 *        File: fw_uemsg_handler.c 
 * 
*/
PUBLIC S16 handleAttachRejInd
(
 Pst *pst, 
 UetMessage *uetAttachRejInd
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   if (uetAttachRejInd->msgType == UE_ATTACH_REJ_TYPE)
   {
      sendUeAttachRejectIndToTstCntrl(uetAttachRejInd);
   }

   FW_LOG_EXITFN(fwCb, ret);
}

/*
 *        Fun:  sendUeTauRejectIndToTstCntrl 
 *
 *        Desc:  Sending the TAU Reject indication to test controller stub
 *
 *        Ret:   ROK
 * 
 *        Notes: None
 * 
 *        File: fw_uemsg_handler.c 
 * 
*/
PUBLIC S16 sendUeTauRejectIndToTstCntrl
(
 UetMessage *uetTauRejInd
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   ueTauRejInd_t *tfwUeTauRejInd = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &tfwUeTauRejInd , sizeof(ueTauRejInd_t));

   tfwUeTauRejInd->ue_Id = uetTauRejInd->msg.ueUetTauReject.ueId;
   tfwUeTauRejInd->cause = uetTauRejInd->msg.ueUetTauReject.cause;
   if (tfwUeTauRejInd->cause == TFW_EMM_CAUSE_IMSI_UNKNOWN)
   {
      FW_LOG_DEBUG(fwCb, "TAU Rejected:: UNKNOWN IMSI");
   }

   (fwCb->testConrollerCallBack)(UE_TAU_REJECT_IND,
         tfwUeTauRejInd,sizeof(ueTauRejInd_t));

   FW_FREE_MEM(fwCb, tfwUeTauRejInd , sizeof(ueTauRejInd_t));
   FW_LOG_EXITFN(fwCb, ret);
}

/*
 *        Fun:  handleTauRejectInd 
 *
 *        Desc:  Handles the TAU reject indications
 *
 *        Ret:   ROK
 * 
 *        Notes: None
 * 
 *        File: fw_uemsg_handler.c 
 * 
*/
PUBLIC S16 handleTauRejectInd
(
 Pst *pst, 
 UetMessage *uetTauRejInd
)
{
   S16 flag = 0;
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   UeIdCb *ueIdCb  = NULLP;
   CmLList  *tmpNode = NULLP;     /* Stores the Ie Node */

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   CM_LLIST_FIRST_NODE(&fwCb->ueIdList, tmpNode);
   while (tmpNode != NULLP)
   {
      ueIdCb = (UeIdCb*)tmpNode->node;
      if (ueIdCb->ue_id == uetTauRejInd->msg.ueUetTauReject.ueId)
      {
         printf("ue id %d found\n", uetTauRejInd->msg.ueUetTauReject.ueId);
         flag = 1;
         ueIdCb->link.node = (PTR)ueIdCb;
      }
      tmpNode = tmpNode->next;
   }

   FW_LOG_DEBUG(fwCb, "\nStoping timer T3430\n");

   if (flag == 1)
   {
      fwStopTmr(fwCb, ueIdCb);
      delete_ue_entries(ueIdCb->ue_id);
      ret = sendUeTauRejectIndToTstCntrl(uetTauRejInd);
   }
   else
   {
      FW_LOG_ERROR(fwCb, "Ue id not found\n");
      ret = RFAILED;
   }

   FW_LOG_EXITFN(fwCb, ret);
}

/*
 *        Fun:  handleServiceRejInd 
 *
 *        Desc:  Handles the Service reject indications
 *
 *        Ret:   ROK
 * 
 *        Notes: None
 * 
 *        File: fw_uemsg_handler.c 
 * 
*/
PUBLIC S16 handleServiceRejInd
(
 Pst *pst, 
 UetMessage *uetServiceRejInd
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   if (uetServiceRejInd->msgType == UE_SERVICE_REJ_TYPE)
   {
      sendUeServiceRejectIndToTstCntrl(uetServiceRejInd);
   }

   FW_LOG_EXITFN(fwCb, ret);
}

/*
 *        Fun:  handleDetachAcceptInd 
 *
 *        Desc:  Handles the Detach accept indication.
 *
 *        Ret:   ROK
 * 
 *        Notes: None
 * 
 *        File: fw_uemsg_handler.c 
 * 
*/
PUBLIC S16 handleDetachAcceptInd
(
 Pst *pst, 
 UetMessage *uetDetachAcceptInd
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   if (uetDetachAcceptInd->msgType == UE_DETACH_ACCEPT_IND_TYPE)
   {
      sendUeDetachAcceptIndToTstCntlr(uetDetachAcceptInd);
   }

   FW_LOG_EXITFN(fwCb, ret);
}

/*
 *        Fun:  sendUePagingIndToTstCntlr
 *
 *        Desc:  Sending the Paging indication to test controller stub
 *
 *        Ret:   ROK
 * 
 *        Notes: None
 * 
 *        File: fw_uemsg_handler.c 
 * 
*/
PUBLIC S16 sendUePagingIndToTstCntlr
(
 UetMessage *uetPagingInd
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   uePagingInd_t *tfwUePagingInd = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &tfwUePagingInd , sizeof(uePagingInd_t));

   tfwUePagingInd->ue_Id = uetPagingInd->msg.ueUetPagingMsg.ueId;
   tfwUePagingInd->domain_Type = uetPagingInd->msg.ueUetPagingMsg.domainType;
   FW_LOG_DEBUG(fwCb, "ueid: %d", tfwUePagingInd->ue_Id);
   FW_LOG_DEBUG(fwCb, "CnDomain: %d", tfwUePagingInd->domain_Type);

   (fwCb->testConrollerCallBack)(UE_PAGING_IND, tfwUePagingInd,
         sizeof(uePagingInd_t));

   FW_FREE_MEM(fwCb, tfwUePagingInd , sizeof(uePagingInd_t));
   FW_LOG_EXITFN(fwCb, ret);
}

/*
*        Fun:  handlePagingInd 
*
*        Desc:  Handles the Paging indication.
*
*        Ret:   ROK
* 
*        Notes: None
* 
*        File: fw_uemsg_handler.c 
* 
*/
PUBLIC S16 handlePagingInd
(
 Pst *pst, 
 UetMessage *uetPagingInd
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);
   if (uetPagingInd->msgType == UE_PAGING_MSG_TYPE)
   {
      sendUePagingIndToTstCntlr(uetPagingInd);
   }
   FW_LOG_EXITFN(fwCb, ret);
}

PRIVATE S16 handlePdnConRspInd 
(
 Pst *pst, 
 UetMessage *uetPdnConRspInd
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   S16 flag = 0;
   UeIdCb *ueIdCb = NULLP;
   CmLList  *tmpNode = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);
   
   CM_LLIST_FIRST_NODE(&fwCb->ueIdList, tmpNode);
   while (tmpNode != NULLP)
   {
      ueIdCb = (UeIdCb*)tmpNode->node;
      if (ueIdCb->ue_id == uetPdnConRspInd->msg.ueUetPdnConRsp.ueId)
      {
         printf("ue id %d found\n", uetPdnConRspInd->msg.ueUetPdnConRsp.ueId);
         flag = 1;
         ueIdCb->link.node = (PTR)ueIdCb;
      }
      tmpNode = tmpNode->next;
   }

   FW_LOG_DEBUG(fwCb, "\nStoping timer T3482\n");

   if (flag == 1)
   {
      fwStopTmr(fwCb, ueIdCb);
      ret = sendUePdnConRspIndToTstCntlr(uetPdnConRspInd);
   }
   else
   {
      FW_LOG_ERROR(fwCb, "Ue id not found\n");
      ret = RFAILED;
   }

   FW_LOG_EXITFN(fwCb, ret);
}

/* 
 *        Fun:  sendUePdnConnTimeOutIndToTstCntlr 
 *
 *        Desc:  Sends Pdn Connection Request Timeout indication to TC stub
 *
 *        Ret:   ROK
 * 
 *        Notes: None
 * 
 *        File: fw_uemsg_handler.c 
 * 
*/
PUBLIC S16 sendUePdnConnTimeOutIndToTstCntlr(FwCb *fwCb, UeIdCb *ueIdCb)
{
   S16 ret = ROK;

   uePdnConTimeOutInd_t *tfwMsgTimeOutInd = NULLP;
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &tfwMsgTimeOutInd , sizeof(uePdnConTimeOutInd_t));
   if(tfwMsgTimeOutInd == NULLP)
         RETVALUE(RFAILED);
   cmMemset((U8*)tfwMsgTimeOutInd, 0, sizeof(uePdnConTimeOutInd_t));

   tfwMsgTimeOutInd->ue_Id = ueIdCb->ue_id;
   
   FW_LOG_DEBUG(fwCb, "Invoking Test Controller Callback");
   (fwCb->testConrollerCallBack)(UE_PDN_CONN_REQ_TIMEOUT_IND, tfwMsgTimeOutInd,
                                  sizeof(uePdnConTimeOutInd_t));

   FW_FREE_MEM(fwCb, tfwMsgTimeOutInd,sizeof(uePdnConTimeOutInd_t));
   FW_LOG_EXITFN(fwCb, ret);
}

/*
 *        Fun:  sendUeNwInitDetachReqIndToTstCntlr 
 *
 *        Desc:  Handles the Send Nw Init Detach  indication to TC stub
 *
 *        Ret:   ROK
 * 
 *        Notes: None
 * 
 *        File: fw_uemsg_handler.c 
 * 
*/
PUBLIC S16 sendUeNwInitDetachReqIndToTstCntlr
(
 UetMessage *uetNwInitDetachInd
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   ueNwInitdetachReq_t *tfwNwInitDetReq = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &tfwNwInitDetReq , sizeof(ueNwInitdetachReq_t));

   tfwNwInitDetReq->ue_Id = uetNwInitDetachInd->msg.ueUetNwInitDetachReq.ueId;
   tfwNwInitDetReq->Type = uetNwInitDetachInd->msg.ueUetNwInitDetachReq.ueNwInitDetType;
   tfwNwInitDetReq->cause = uetNwInitDetachInd->msg.ueUetNwInitDetachReq.cause;
   (fwCb->testConrollerCallBack)(UE_NW_INIT_DETACH_REQUEST, tfwNwInitDetReq, 
         sizeof(ueNwInitdetachReq_t));

   FW_FREE_MEM(fwCb, tfwNwInitDetReq, sizeof(ueNwInitdetachReq_t));
   FW_LOG_EXITFN(fwCb, ret);
}
PRIVATE S16 handleAndSendDeActvBerReqInd 
(
 Pst *pst, 
 UetMessage *msgreq
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;

   UeUetDeActvBearCtxtReq *params  = NULLP; 
   UeDeActvBearCtxtReq_t *ueDeActvBerReq = NULLP;
   U8 idx;
   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);


  params = &msgreq->msg.ueDeActvBerReq;
 
   FW_ALLOC_MEM(fwCb, &ueDeActvBerReq , sizeof(UeDeActvBearCtxtReq_t));

  cmMemset((U8 *)ueDeActvBerReq, 0, sizeof(UeDeActvBearCtxtReq_t));
  ueDeActvBerReq->ue_Id           = params->ueId;
  ueDeActvBerReq->bearerId        = params->bearerId; 
  ueDeActvBerReq->esmCause        = params->esmCause; 
   (fwCb->testConrollerCallBack)(UE_DEACTIVATE_BER_REQ,ueDeActvBerReq, 
         sizeof(UeDeActvBearCtxtReq_t));

   FW_FREE_MEM(fwCb,ueDeActvBerReq, sizeof(UeDeActvBearCtxtReq_t));
   FW_LOG_EXITFN(fwCb, ret);
}

PRIVATE S16 handleAndSendActDedBerReqInd 
(
 Pst *pst, 
 UetMessage *msgreq
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;

   UeUetActDedBearCtxtReq *params  = NULLP; 
   UeActDedBearCtxtReq_t *ueActDedBerReq = NULLP;
   U8 idx;
   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);


  params = &msgreq->msg.ueActDedBerReq;
 
   FW_ALLOC_MEM(fwCb, &ueActDedBerReq , sizeof(UeActDedBearCtxtReq_t));

  cmMemset((U8 *)ueActDedBerReq, 0, sizeof(UeActDedBearCtxtReq_t));
  ueActDedBerReq->ue_Id           = params->ueId;
  ueActDedBerReq->bearerId        = params->bearerId; 
  ueActDedBerReq->lnkBearerId     = params->lnkBearerId; 
 
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
    if(ueActDedBerReq->tft.noOfPfs > 0)
      FW_ALLOC_MEM(fwCb, &ueActDedBerReq->tft.pfList \
         ,params->tft.noOfPfs *sizeof(ue_Esm_Tft_Pf));
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
       ueActDedBerReq->tft.noOfParams =  params->tft.noOfParams;
      FW_ALLOC_MEM(fwCb, &ueActDedBerReq->tft.params , params->tft.noOfParams *sizeof(ue_Esm_Tft_Param));
      for( idx = 0 ; idx < params->tft.noOfParams ; idx++)
      {
       ueActDedBerReq->tft.params[idx].len          = params->tft.params[idx].len;       
       ueActDedBerReq->tft.params[idx].paramType    = params->tft.params[idx].paramType; 
       cmMemcpy((U8 *)&ueActDedBerReq->tft.params[idx].buf, \
            (U8 *)params->tft.params[idx].buf,CM_ESM_TFT_MAX_PARAM_BUF);
      }
   }
   (fwCb->testConrollerCallBack)(UE_ACT_DED_BER_REQ,ueActDedBerReq, 
         sizeof(UeActDedBearCtxtReq_t));

   FW_FREE_MEM(fwCb,ueActDedBerReq->tft.pfList, sizeof(ue_Esm_Tft_Pf));
   FW_FREE_MEM(fwCb,ueActDedBerReq->tft.params, sizeof(ue_Esm_Tft_Param));
   FW_FREE_MEM(fwCb,ueActDedBerReq, sizeof(UeActDedBearCtxtReq_t));
   FW_LOG_EXITFN(fwCb, ret);
}

PRIVATE S16 handleNwInitDetachReqInd 
(
 Pst *pst, 
 UetMessage *uetNwinitDetachInd
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);
   if(uetNwinitDetachInd->msgType == UE_NW_INIT_DETACH_REQUEST_TYPE)
   {
      sendUeNwInitDetachReqIndToTstCntlr(uetNwinitDetachInd);
   }

   FW_LOG_EXITFN(fwCb, ret);
}

PRIVATE S16 handleEmmInformation
(
 Pst *pst, 
 UetMessage *ueEmmInformation
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);
   if(ueEmmInformation->msgType == UE_EMM_INFORMATION_TYPE)
   {
      sendUeEmmInformationToTstCntlr(ueEmmInformation);
   }

   FW_LOG_EXITFN(fwCb, ret);
}


/*
 *        Fun:  sendUeEmmInformationToTstCntlr
 *
 *        Desc:  Handles the Send Nw Init Detach  indication to TC stub
 *
 *        Ret:   ROK
 * 
 *        Notes: None
 * 
 *        File: fw_uemsg_handler.c
 * 
*/
PUBLIC S16 sendUeEmmInformationToTstCntlr
(
 UetMessage *ueEmmInformation
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   ueEmmInformation_t *tfwEmmInformation = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &tfwEmmInformation , sizeof(ueEmmInformation_t));

   tfwEmmInformation->ue_Id = ueEmmInformation->msg.ueEmmInformation.ueId;
   (fwCb->testConrollerCallBack)(UE_EMM_INFORMATION, tfwEmmInformation, 
         sizeof(ueEmmInformation_t));

   FW_FREE_MEM(fwCb, tfwEmmInformation, sizeof(ueEmmInformation_t));
   FW_LOG_EXITFN(fwCb, ret);
}

/*
 *        Fun:  handleAuthRejectInd
 *
 *        Desc:  Handles the Send Auth-Rej indication to TC stub
 *
 *        Ret:   ROK
 * 
 *        Notes: None
 * 
 *        File: fw_uemsg_handler.c
 * 
*/
PRIVATE S16 handleAuthRejectInd
(
 Pst             *pst, 
 UetMessage *ueUetAuthRejInd
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   U8 flag = 0;
   ueAuthRejInd_t *authRejInd = NULLP;
   CmLList  *tmpNode = NULLP;     /* Stores the Ie Node */
   UeIdCb *ueIdCb = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   CM_LLIST_FIRST_NODE(&fwCb->ueIdList, tmpNode);
   while(tmpNode != NULLP)
   {
      ueIdCb = (UeIdCb*)tmpNode->node;
      if(ueIdCb->ue_id == ueUetAuthRejInd->msg.ueUetAuthRejInd.ueId)
      {
          FW_LOG_DEBUG(fwCb, "ue id %d found\n",
              ueIdCb->ue_id);
            flag = 1;
            break;
       }
       tmpNode = tmpNode->next;
   }
   /* delete the ueCn in case of end-to-end attach */
   if(flag == 1)
   {
      /* Stop Attach Timer */
      FW_LOG_DEBUG(fwCb, "Stopping Attach Timer for ue %d", ueIdCb->ue_id);
      fwStopTmr(fwCb, ueIdCb);
      delete_ue_entries(ueIdCb->ue_id);
      FW_FREE_MEM(fwCb, ueIdCb, sizeof(UeIdCb));
   } 
   FW_ALLOC_MEM(fwCb, &authRejInd , sizeof(ueAuthRejInd_t));
   authRejInd->ue_Id = ueUetAuthRejInd->msg.ueUetAuthRejInd.ueId;

   /* send the indiaction to Test-Stub */
   (fwCb->testConrollerCallBack)(UE_AUTH_REJ_IND, authRejInd,
                                  sizeof(ueAuthRejInd_t));


   FW_FREE_MEM(fwCb, authRejInd, sizeof(ueAuthRejInd_t));
   FW_LOG_EXITFN(fwCb, ret);
}

PRIVATE S16 handleEsmInformationReq
(
 Pst *pst, 
 UetMessage *ueEsmInformationReq
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);
   if(ueEsmInformationReq->msgType == UE_ESM_INFORMATION_REQ_TYPE)
   {
      sendUeEsmInformationReqToTstCntlr(ueEsmInformationReq);
   }

   FW_LOG_EXITFN(fwCb, ret);
}

/*
 *        Fun:  sendUeEsmInformationReqToTstCntlr
 *
 *        Desc:  Handles the Send Esm Information Req to TC stub
 *
 *        Ret:   ROK
 * 
 *        Notes: None
 * 
 *        File: fw_uemsg_handler.c
 * 
*/
PUBLIC S16 sendUeEsmInformationReqToTstCntlr
(
 UetMessage *ueEsmInfoReq
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   ueEsmInformationReq_t *tfwEsmInformationReq = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &tfwEsmInformationReq , sizeof(ueEsmInformationReq_t));

   tfwEsmInformationReq->ue_Id = ueEsmInfoReq->msg.ueEsmInformationReq.ueId;
   (fwCb->testConrollerCallBack)(UE_ESM_INFORMATION_REQ, tfwEsmInformationReq, 
         sizeof(ueEsmInformationReq_t));

   FW_FREE_MEM(fwCb, tfwEsmInformationReq, sizeof(ueEsmInformationReq_t));
   FW_LOG_EXITFN(fwCb, ret);
}

