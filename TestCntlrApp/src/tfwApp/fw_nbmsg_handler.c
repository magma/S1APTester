/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

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

EXTERN FwCb gfwCb;
PUBLIC S16 sendNbAppConfigRespToTstCntlr(NbConfigCfm *nbtMsg);
/*
*        Fun:   sendNbAppConfigRespToTstCntlr
*
*        Desc:  Sends the Nb Config Response message to 
*               Test controller stub Message Queue
*
*        Ret:   S16
* 
*        Notes: None
* 
*        File:  fw_nbmsg_handler.c
*/

PUBLIC S16 sendNbAppS1SetupRespToTstCntlr(NbS1SetupRsp *nbtMsg);
PUBLIC S16 sendNbAppS1SetupTimeOutIndToTstCntlr(Void);
PUBLIC S16 sendNbAppS1ResetAckToTstCntlr(NbResetAckldg *rsp);
PUBLIC S16 sendNbAppUeCtxRelIndToTstCntlr(NbUeCtxRelInd *rsp);
PUBLIC S16 sendNbAppIntCtxSetupIndToTstCntlr(NbIntCtxtSetUpInd *rsp);
PUBLIC S16 sendNbAppIntCtxSetupDrpdIndToTstCntlr(NbIntCtxtSetUpDrpdInd *rsp);
PUBLIC S16 sendNbAppErabRelCmdToTstCntlr(NbErabRelCmd *rsp);
PUBLIC S16 sendNbAppNasNonDelIndToTstCntlr(NbNasNonDelRsp *rsp);
PUBLIC S16 sendNbAppPathSwReqAckToTstCntlr(NbPathSwReqAck *rsp);

/*
 *       Fun: sendNbAppConfigRespToTstCntlr 
 *
 *       Desc: 
 * 
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  fw_nbmsg_handler.c
 */
PUBLIC S16 sendNbAppConfigRespToTstCntlr(NbConfigCfm *cfm)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   FwNbConfigCfm_t *msg = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &msg , sizeof(FwNbConfigCfm_t));
   fwCb->nbState = NB_CONFIG_DONE;
   msg->status = cfm->status;
   if(cfm->status != ROK)
   {
      fwCb->nbState = NB_CONFIG_FAILED;
      msg->cause    = cfm->cause;
   }
   (*fwCb->testConrollerCallBack)(ENB_CONFIG_CONFIRM, msg,
                                  sizeof(FwNbConfigCfm_t));
   FW_FREE_MEM(fwCb, msg, sizeof(FwNbConfigCfm_t));
   if (msg != NULLP)
   {
      FW_LOG_ERROR(fwCb, "Memory Freeing failed");
   }
   
   FW_LOG_EXITFN(fwCb, ret);
} /* sendNbAppConfigRespToTstCntlr */


/*
 *       Fun: sendNbAppS1SetupRespToTstCntlr 
 *
 *       Desc: 
 * 
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  fw_nbmsg_handler.c
 */
PUBLIC S16 sendNbAppS1SetupRespToTstCntlr(NbS1SetupRsp *rsp)
{
   S16 ret = ROK;
   U16 idx = 0;
   FwCb *fwCb = NULLP;
   FwNbS1setupRsp_t  *msg = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &msg , sizeof(FwNbS1setupRsp_t));
   msg->res = rsp->res;
   fwCb->nbState = ENB_IS_UP;
   /*if(rsp->res != ROK)*/
   if(rsp->res == S1_SETUP_FAIL)
   {
      FW_LOG_DEBUG(fwCb, "sendNbAppS1SetupRespToTstCntlr(): S1_SETUP_FAIL");
      msg->res = rsp->res;
      msg->waitIe.pres = FALSE;
      if(rsp->waitIe.pres == TRUE)
      {
         msg->waitIe.val  = rsp->waitIe.val;
         msg->waitIe.pres = TRUE;
      }
      msg->cause.pres = TRUE; 
      msg->cause.type = rsp->cause.causeType;
      msg->cause.val  = rsp->cause.causeVal;
      fwCb->nbState   = NB_CONFIG_DONE;
   }
   else if (rsp->res == S1_SETUP_SUCC)
   {
      FW_LOG_DEBUG(fwCb, "sendNbAppS1SetupRespToTstCntlr(): S1_SETUP_SUCC");
      msg->res = rsp->res;

      /* Served GUMMEI list */
      msg->numPlmnIds = rsp->numPlmnIds;
      for (idx = 0; idx < msg->numPlmnIds; idx++)
      {
         cmMemcpy((U8 *)&msg->plmnIds[idx], (U8 *)&(rsp->plmnIds[idx]),
                  sizeof(NbtPlmnId));
      }

      msg->numGrpIds = rsp->numGrpIds;
      for (idx = 0; idx < msg->numGrpIds; idx++)
      {
         msg->groupIds[idx] = rsp->groupIds[idx];
      }

      msg->numCodes = rsp->numCodes;
      for (idx = 0; idx < msg->numCodes; idx++)
      {
         msg->codes[idx] = rsp->codes[idx];
      }

      /* Relative MME capacity */
      msg->relCapacity = rsp->relCapacity;
      /* MME Name */
      msg->mmeName.len = rsp->mmeName.len;
      cmMemcpy(msg->mmeName.val, rsp->mmeName.val, msg->mmeName.len);
      /* MME Relay Support Indicator */
      msg->mmeRelaySuppInd = rsp->mmeRelaySuppInd;
   }

   (*fwCb->testConrollerCallBack)(ENB_S1_SETUP_RESP, msg,
                                  sizeof(FwNbS1setupRsp_t));
   FW_FREE_MEM(fwCb, msg , sizeof(FwNbS1setupRsp_t));
   FW_LOG_EXITFN(fwCb, ret);

} /* sendNbS1SetupRespToTstCntlr */

/*
 *       Fun: sendNbAppS1ResetAckToTstCntlr 
 *
 *       Desc: 
 * 
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  fw_nbmsg_handler.c
 */
PUBLIC S16 sendNbAppS1ResetAckToTstCntlr(NbResetAckldg *rsp)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   FwNbS1ResetAck_t *msg = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &msg, sizeof(FwNbS1ResetAck_t));

   msg->status = rsp->status;
   msg->numOfUes = rsp->numOfUes;

   if(rsp->numOfUes > 0)
   {
      FW_ALLOC_MEM(fwCb, &msg->ueIdLst, rsp->numOfUes);
      cmMemcpy(msg->ueIdLst, rsp->ueIdLst, rsp->numOfUes);
   }

   (*fwCb->testConrollerCallBack)(RESET_ACK, msg,
                                  sizeof(FwNbS1ResetAck_t));
   if(rsp->numOfUes > 0)
   {
      FW_FREE_MEM(fwCb, msg->ueIdLst, rsp->numOfUes);
   }
   FW_FREE_MEM(fwCb, msg, sizeof(FwNbS1ResetAck_t));
   FW_LOG_EXITFN(fwCb, ret);
} /* sendNbAppS1ResetAckToTstCntlr */

/*
 *
 *       Fun: sendNbAppS1SetupTimeOutIndToTstCntlr 
 *
 *       Desc: 
 * 
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  fw_nbmsg_handler.c
 *
 */
PUBLIC S16 sendNbAppS1SetupTimeOutIndToTstCntlr(Void)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   fwCb->nbState   = NB_CONFIG_DONE;
   (*fwCb->testConrollerCallBack)(ENB_S1_SETUP_TIMEOUT_IND, NULL, 0);
   FW_LOG_EXITFN(fwCb, ret);
} /* sendNbAppS1SetupTimeOutIndToTstCntlr */

/*
 *       Fun: sendNbAppUeCtxRelIndToTstCntlr
 *
 *       Desc: 
 * 
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  fw_nbmsg_handler.c
 */
PUBLIC S16 sendNbAppUeCtxRelIndToTstCntlr(NbUeCtxRelInd *rsp)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   FwNbUeCtxRelInd_t *msg = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &msg, sizeof(FwErabRelInd_t));

   msg->ueId = rsp->ueId;

   (*fwCb->testConrollerCallBack)(UE_CTX_REL_IND, msg,
         sizeof(FwNbUeCtxRelInd_t));
   FW_FREE_MEM(fwCb, msg, sizeof(FwNbUeCtxRelInd_t));
   FW_LOG_EXITFN(fwCb, ret);
} /* sendNbAppUeCtxRelIndToTstCntlr */

/*
 *       Fun: sendNbAppIntCtxSetupIndToTstCntlr
 *
 *       Desc: 
 * 
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  fw_nbmsg_handler.c
 */
PUBLIC S16 sendNbAppIntCtxSetupIndToTstCntlr(NbIntCtxtSetUpInd *rsp)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   FwNbIntCtxSetupInd_t *msg = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &msg, sizeof(FwNbIntCtxSetupInd_t));

   msg->ueId = rsp->ueId;
   msg->status = rsp->status;

   (*fwCb->testConrollerCallBack)(INT_CTX_SETUP_IND, msg,
         sizeof(FwNbIntCtxSetupInd_t));
   FW_FREE_MEM(fwCb, msg, sizeof(FwNbIntCtxSetupInd_t));
   FW_LOG_EXITFN(fwCb, ret);
} /* sendNbAppUeCtxRelIndToTstCntlr */

/*
 *
 *       Fun: sendNbAppIntCtxSetupDrpdIndToTstCntlr 
 *
 *       Desc: 
 * 
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  fw_nbmsg_handler.c
 */
PUBLIC S16 sendNbAppIntCtxSetupDrpdIndToTstCntlr(NbIntCtxtSetUpDrpdInd *rsp)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   FwNbIntCtxSetupDrpdInd_t *msg = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &msg, sizeof(FwNbIntCtxSetupDrpdInd_t));

   msg->ueId = rsp->ueId;

   (*fwCb->testConrollerCallBack)(UE_ICS_DROPD_IND, msg,
         sizeof(FwNbIntCtxSetupDrpdInd_t));
   FW_FREE_MEM(fwCb, msg, sizeof(FwNbIntCtxSetupDrpdInd_t));
   FW_LOG_EXITFN(fwCb, ret);
} 

/*
 *       Fun: sendNbAppErabRelCmdToTstCntlr
 *
 *       Desc: 
 * 
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  fw_nbmsg_handler.c
 */
PUBLIC S16 sendNbAppErabRelCmdToTstCntlr(NbErabRelCmd *rsp)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   FwErabRelCmd_t *msg = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &msg, sizeof(FwErabRelCmd_t));

   msg->ueId = rsp->ueId;
   msg->ueId = rsp->ueId;
   msg->enbUeS1apId = rsp->enbUeS1apId;
   msg->mmeUeS1apId = rsp->mmeUeS1apId;
   msg->numOfErabIds = rsp->numOfErabIds;
   FW_ALLOC_MEM(fwCb, &msg->erabIdLst, msg->numOfErabIds * sizeof(U8));
   cmMemcpy(msg->erabIdLst, rsp->erabIdLst, msg->numOfErabIds * sizeof(U8));

   (*fwCb->testConrollerCallBack)(ERAB_REL_CMD, msg,
         sizeof(FwErabRelCmd_t));
   FW_FREE_MEM(fwCb, msg->erabIdLst, msg->numOfErabIds * sizeof(U8));
   FW_FREE_MEM(fwCb, msg, sizeof(FwErabRelCmd_t));
   FW_LOG_EXITFN(fwCb, ret);
} /* sendNbAppErabRelCmdToTstCntlr */

/*eNbApp wouldn't send NAS NON DEL IND to TFW */
#if 0
/*
 *       Fun: sendNbAppNasNonDelIndToTstCntlr
 *
 *       Desc: 
 * 
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  fw_nbmsg_handler.c
 */
PUBLIC S16 sendNbAppNasNonDelIndToTstCntlr(NbNasNonDelRsp *rsp)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   ueNasNonDelRsp_t *msg = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &msg, sizeof(ueNasNonDelRsp_t));

   msg->ue_Id = rsp->ueId;

   (*fwCb->testConrollerCallBack)(UE_NAS_NON_DELIVERY_IND, msg,
         sizeof(ueNasNonDelRsp_t));
   FW_FREE_MEM(fwCb, msg, sizeof(ueNasNonDelRsp_t));
   FW_LOG_EXITFN(fwCb, ret);
} /* sendNbAppNasNonDelIndToTstCntlr */
#endif

/*
 *       Fun: sendNbAppPathSwReqAckToTstCntlr
 *
 *       Desc: 
 * 
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  fw_nbmsg_handler.c
 */
PUBLIC S16 sendNbAppPathSwReqAckToTstCntlr(NbPathSwReqAck *rsp)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   FwNbPathSwReqAck_t *msg = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &msg, sizeof(FwNbPathSwReqAck_t));

   msg->ueId = rsp->ueId;

   (*fwCb->testConrollerCallBack)(PATH_SW_REQ_ACK, msg,
         sizeof(FwNbPathSwReqAck_t));
   FW_FREE_MEM(fwCb, msg, sizeof(FwNbPathSwReqAck_t));
   FW_LOG_EXITFN(fwCb, ret);
} /* sendNbAppPathSwReqAckToTstCntlr */

 /*
 *       Fun: sendNbAppMmeConfigTrfToTstCntlr
 *
 *       Desc: 
 * 
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  fw_nbmsg_handler.c
 */
PUBLIC S16 sendNbAppMmeConfigTrfToTstCntlr(FwNbMmeConfigTrnsf_t *rsp)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   FwNbMmeConfigTrnsf_t *msg = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_ALLOC_MEM(fwCb, &msg, sizeof(FwNbMmeConfigTrnsf_t));

   (*fwCb->testConrollerCallBack)(MME_CONFIGURATION_TRANSFER, msg,
         sizeof(FwNbMmeConfigTrnsf_t));
   FW_FREE_MEM(fwCb, msg, sizeof(FwNbMmeConfigTrnsf_t));
   FW_LOG_EXITFN(fwCb, ret);
} /* sendNbAppMmeConfigTrfToTstCntlr */

/*
 *       Fun: handleNwInitAssocDown
 *
 *
 *       Desc: This function handles MME initiated
 *             sctp shutdown/abort message
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *
 *       File:  fw_nbmsg_handler.c
 */
PUBLIC Void handleNwInitAssocDown()
{
  FwCb *fwCb = NULLP;

  FW_GET_CB(fwCb);
  FW_LOG_ENTERFN(fwCb);
  fwCb->nbState = NB_CONFIG_DONE;
  FW_LOG_EXITFNVOID(fwCb);
} /* handleNwInitAssocDown */

/*
 *
 *       Fun: handleNbAppMsg
 *
 *       Desc: 
 * 
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  fw_nbmsg_handler.c
 *
 */
PUBLIC S16 handleNbAppMsg
(
 Pst *pst,
 NbtResponse *nbRspMsg
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   switch(nbRspMsg->msgType)
   {
      case NB_CONFIG_CFM:
         FW_LOG_DEBUG(fwCb, "Recieved Config Response from EnodeB");
         sendNbAppConfigRespToTstCntlr(&nbRspMsg->t.configCfm);
         break;
      case NB_S1_SETUP_RSP:
         FW_LOG_DEBUG(fwCb, "Recieved SetUp Response from EnodeB");
         sendNbAppS1SetupRespToTstCntlr(&nbRspMsg->t.s1SetupRsp);
         break;
      case NB_S1_SETUP_TIMEOUT_IND:
         FW_LOG_DEBUG(fwCb, "Recieved SetUp TimeOut Indication from EnodeB");
         sendNbAppS1SetupTimeOutIndToTstCntlr();
         break;
      case NB_RESET_ACK:
         FW_LOG_DEBUG(fwCb, "Recieved S1 Reset Ack from EnodeB");
         sendNbAppS1ResetAckToTstCntlr(&nbRspMsg->t.resetAck);
         if(nbRspMsg->t.resetAck.numOfUes)
         {
            FW_FREE_MEM(fwCb, nbRspMsg->t.resetAck.ueIdLst,
                   nbRspMsg->t.resetAck.numOfUes);
         }
         break;
      case NB_UE_CTX_REL_IND:
         FW_LOG_DEBUG(fwCb, "Recieved UE Context Release Indication from "\
               "EnodeB");
         sendNbAppUeCtxRelIndToTstCntlr(&nbRspMsg->t.ueCtxRelInd);
         break;
      case NB_INT_CTX_SETUP_IND:
         FW_LOG_DEBUG(fwCb, "Recieved Initial Context Setup Indication from "\
               "EnodeB");
         sendNbAppIntCtxSetupIndToTstCntlr(&nbRspMsg->t.IntCtxtSetUpInd);
         break;
      case NB_INIT_CTXT_SETUP_DROPPD_IND:
         FW_LOG_DEBUG(fwCb, "Recieved Initial Context Setup Dropped Indication from "\
               "EnodeB");
         sendNbAppIntCtxSetupDrpdIndToTstCntlr(&nbRspMsg->t.intCtxtSetUpDrpdInd);
         break;
      case NB_ERAB_REL_CMD_IND:
         FW_LOG_DEBUG(fwCb, "Recieved Erab Release Commmand from EnodeB");
         sendNbAppErabRelCmdToTstCntlr(&nbRspMsg->t.erabRelCmdInfo);
         break;
         /* Now eNbApp wouldn't send NAS NON DEL IND to TFW  */
      /*case NB_NAS_NON_DEL_RSP:
         FW_LOG_DEBUG(fwCb, "Recieved Erab Release Commmand from EnodeB");
         sendNbAppNasNonDelIndToTstCntlr(&nbRspMsg->t.nasNondelRsp);
         break;*/
      case NB_PATH_SW_REQ_ACK:
         FW_LOG_DEBUG(fwCb, "Recieved Path Sw Req from EnodeB");
         sendNbAppPathSwReqAckToTstCntlr(&nbRspMsg->t.pathSwReqAck);
         break;         
      case NB_MME_CONFIG_TRANSFER:
         FW_LOG_DEBUG(fwCb, "Recieved NB_MME_CONFIG_TRF from EnodeB");
         sendNbAppMmeConfigTrfToTstCntlr(&nbRspMsg->t.mmeConfigTrnsf);
         break;        
      case NB_NW_INITIATED_ASSOC_DOWN:
         FW_LOG_DEBUG(fwCb, "Recieved NB_NW_INITIATED_ASSOC_DOWN from EnodeB");
         handleNwInitAssocDown();
         break;

      default:
         FW_LOG_ERROR(fwCb, "Recieved Invalid event from EnodeB");
         break;
   }

   FW_LOG_EXITFN(fwCb, ret);
}
