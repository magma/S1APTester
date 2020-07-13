/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */


/**********************************************************************

     Name:     S1SIM Test Controller Stub 
  
     Type:     C source file
  
     Desc:     This file contains the stub code for S1SIM Test Controller

     File:     ts_utls.c

     Prg:      

**********************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>

#include "fw_api_int.x"
#include "trfgen.x"
#include "ts_utls.x"

int paging_ueid = 0;
int nwInitDetach_ueid = 0;
tsErabLst ueErabInfo[32];
FwErabRelCmd_t erabRelCmdInfo[32];
extern char videoSrvrIp[20]; /* Values will be stored from reading the nbCfg.txt */
extern S8 ueIntf[]; /* This is defined in ennApp/nb_traffic_handler.c */

void trf_test_init(void)
{
   struct_test test_parms;

   printf("[Stub] Entering trf_test_init()\n");
   trfgen_init();

   test_parms.test_id = 1;
   test_parms.duration = 120;
   test_parms.trfgen_type = SERVER;
   test_parms.traffic_type = TCP;

   trfgen_configure_test(test_parms.test_id,test_parms);

   test_parms.test_id = 2;
   test_parms.duration = 120;
   test_parms.trfgen_type = CLIENT;
   test_parms.traffic_type = TCP;

   trfgen_configure_test(test_parms.test_id,test_parms);
}

void tsReadImsiAndSendUeConfig(int noOfUe)
{
   FILE *fp;
   unsigned char imsi[15] = {0};
   unsigned char temp[30] = {0};
   unsigned char id = 0;  
   int imsi_idx = 0,temp_idx = 0;
   printf("[Stub] Entering tsReadImsiAndSendUeConfig()\n");
   if ((fp = fopen("imsi.txt", "r")) == NULL)
   {   
      /* imsi file checking */
      printf("[Stub] imsi.txt::FAILED to open a file");
      exit(0);
   } /* end of if statement */

   for (id = 1; id <= noOfUe; id++)
   {
      printf("[Stub] Reading imsi file for ueId: %d\n", id);
      if(NULL != fgets((char*)temp,30,fp))
      {
          printf("[Stub] ueId :%d temp %s temp len :%lu:: \n", id,temp,strlen((char*)temp)/2);
          imsi_idx =0;
          for(temp_idx = 0; temp_idx < 30;temp_idx++)
          {
             if(temp[temp_idx] != '\n')
             {
                 if(temp[temp_idx] != ' ')
                 {
                     if(temp_idx != 29 )
                     {
                        imsi[imsi_idx++] = atoi((char*)&temp[temp_idx]);
                     }
                     else
                     {
                        imsi[imsi_idx] = atoi((char*)&temp[temp_idx]);
                     }
                 }
             }
             else 
             {
                 break;
             }
         }
         printf("[Stub] ueId :%d IMSI %s imsi len :%d::", id,imsi,imsi_idx);
      }
      printf("\n");
      tsUeConfig(id, imsi, imsi_idx);
   }
}

void convertIpToString(char *bindAddr, unsigned char *ipAddr)
{
   int cnt = 0;
   int totCnt = 0;
   int num = 0;
   int indx = 14;
   char addr[15] ={0};

   printf("[Stub] Entering convertIpToString()\n");

   for (cnt = 3; cnt >= 0; cnt--)
   {
      num = ipAddr[cnt];
      while (num)
      {
         addr[indx--] = (num % 10) + '0';
         num /= 10;
         totCnt++;
      }

      if (cnt)
      {
         addr[indx--] = '.';
         totCnt++;
      }
   }

   memcpy(bindAddr, (addr + indx + 1), totCnt);
}

void tsStartDlData(unsigned char ueId)
{
   static int portNum = 7001;
   char port[4] = {0};
   char bindAddr[15] = {0};
   char ipCfgCmd[100] ={0};
   unsigned char idx = 0;

   while(idx < UeIpInfoLst[ueId - 1].noIfAssinedIps)
   {
      convertIpToString(bindAddr, UeIpInfoLst[ueId-1].UeIpAdrLst[idx]);
      sprintf(port, "%d", portNum);
      sprintf(ipCfgCmd, "ifconfig %s:UE%d %s up", ueIntf, ueId, bindAddr);
      system(ipCfgCmd);
      trfgen_start_test(1, videoSrvrIp, bindAddr, port);
      portNum++;
      idx++;
   }
   return;
}

void tsStartUlData(unsigned char ueId)
{
   static int portNum = 5001;
   char port[4] = {0};
   char bindAddr[15] = {0};
   char ipCfgCmd[100] ={0};
   unsigned char idx = 0;

   while(idx < UeIpInfoLst[ueId - 1].noIfAssinedIps)
   {
      convertIpToString(bindAddr, UeIpInfoLst[ueId-1].UeIpAdrLst[idx]);
      sprintf(port, "%d", portNum);
      sprintf(ipCfgCmd, "ifconfig %s:UE%d %s up", ueIntf, ueId, bindAddr);
      system(ipCfgCmd);
      trfgen_start_test(2, videoSrvrIp, bindAddr, port);
      portNum++;
      idx++;
   }
   return;
}

void deleteCfgdUeIps(unsigned char ueId)
{
   char ipCfgCmd[100] ={0};
   unsigned char idx = 0;

   while(idx < UeIpInfoLst[ueId - 1].noIfAssinedIps)
   {
      sprintf(ipCfgCmd, "ifconfig %s:UE%d down", ueIntf, ueId);
      system(ipCfgCmd);
      idx++;
   }
}

void tsCleanup(void)
{
  cleaningAllProcessIds();
}

int TC_msg_recv(int msgid, int timeout)
{
   /* start timer - timeout secs - TBD */
   /* Read from message queue untill msg Id msg is received */
   Bool msg_recvd = FALSE;
   MsgBuf msgptr;
   void *msg;
   int retVal = 0;
   unsigned char ueId;
   ueAttachFail_t *tfwUeAttachFail = NULL;
   UeActDedBearCtxtReq_t *tfwActvDedBerReq = NULL;
   ueAttachAccept_t *tfwUeAttachAccept = NULL;
   ueTauAccept_t *tfwTauAccept = NULL;
   ueIdentityReqInd_t *tfwIdReq = NULL;
   FwNbConfigCfm_t    *tfwNbConfigCfm = NULL;
   FwNbS1setupRsp_t   *tfwNbS1SetupRsp = NULL;
   uePagingInd_t      *tfwPagingInd = NULL;
   uePdnConRsp_t      *tfwUePdnConRsp = NULL;
   ueNwInitdetachReq_t *tfwNwInitDetachReq = NULL;
   FwErabRelCmd_t     *tfwErabRelCmdInfo = NULL;
   ueNasNonDelRsp_t   *tfwNasNonDelRsp = NULL;
   FwNbIntCtxSetupInd_t *tfwIntCtxSetupInd = NULL;
   uePdnDisconnFail_t *tfwPdnDisconnFail = NULL;

   printf("[Stub] %s:%s():%d: Entering\n", __FILE__, __FUNCTION__, __LINE__);
   printf("[Stub] TC_msg_recv(): msgid=%d\n", msgid);

   while (!msg_recvd)
   {
      if (msgrcv(msgQid, (void *)&msgptr, sizeof(MsgBuf), 0, 0) == -1)
      {
         printf("[Stub] msgcrv failed with error");
         return 0;
      }

      printf("\n[Stub] Received (msgptr.msgType=%ld), expected (msgid=%d)\n",
             msgptr.msgType, msgid);

      if (msgptr.msgType == msgid)
      {
         printf("\n[Stub] Received a message of type = %d\n", msgid);
         msg_recvd = TRUE;
         retVal = SUCC;
      }
      else
      {
         printf("\n[Stub] Received msgptr.mtype = %ld\n", msgptr.msgType);
         msg_recvd = TRUE;
         retVal = FAIL;
         exit(0);
      }
   }

   switch (msgptr.msgType)
   {
      case UE_ATTACH_ACCEPT_IND:
         tfwUeAttachAccept = (ueAttachAccept_t *)&msgptr.msg;
         printf("[Stub] Received Attach Accept Indication from TFW\n");
         printf("[Stub] Starting Traffic to Ue with UeId %d\n",
               tfwUeAttachAccept->ue_Id);
         ueErabInfo[tfwUeAttachAccept->ue_Id - 1].brLst = realloc(ueErabInfo[tfwUeAttachAccept->ue_Id - 1].brLst, (ueErabInfo[tfwUeAttachAccept->ue_Id - 1].numOfBrs + 1) * sizeof(char));
         ueErabInfo[tfwUeAttachAccept->ue_Id - 1].brLst[ueErabInfo[tfwUeAttachAccept->ue_Id - 1].numOfBrs++] = tfwUeAttachAccept->esmInfo.epsBearerId;
         break;
      case UE_ATTACH_FAIL_IND:
         printf("[Stub] Received Attach Fail Indication from TFW\n");
         tfwUeAttachFail = (ueAttachFail_t *)&msgptr.msg;
         printf("[Stub] Attach failed for ueId(%d), ueState(%d), reason(%d)\n",
                tfwUeAttachFail->ueId, tfwUeAttachFail->ueState,
                tfwUeAttachFail->reason);
         break;
      case UE_TAU_ACCEPT_IND:
         tfwTauAccept = (ueTauAccept_t *)&msgptr.msg;
         printf("[Stub] Received TAU Accept Indication from TFW, ueId(%d)\n",
                tfwTauAccept->ue_Id);
         break;
      case ENB_CONFIG_CONFIRM:
         printf("\n[Stub] Received Enodeb Config Confirm from TFW\n");
         tfwNbConfigCfm = (FwNbConfigCfm_t *)&msgptr.msg;
         if (tfwNbConfigCfm->status == CFG_DONE)
         {
            printf("\n[Stub] eNodeB configured successfully\n");
         }
         else
         {
            printf("\n[Stub] eNodeB configuration failed with cause[%d] \n",
                   tfwNbConfigCfm->cause);
         }
         break;
      case ENB_S1_SETUP_RESP:
         printf("\n[Stub] Received S1-SETUP Response from TFW\n");
         tfwNbS1SetupRsp = (FwNbS1setupRsp_t *)&msgptr.msg;
         if(tfwNbS1SetupRsp->res == S1_SETUP_SUCCESS)
         {
            printf("\n[Stub] S1-SETUP successful received from TFWAPP\n");
            retVal = SUCC;
         }
         else
         {
            printf("\n[Stub] S1-SETUP failed, causeType[%d], causeValue[%d]\n",
                   tfwNbS1SetupRsp ->cause.type, tfwNbS1SetupRsp ->cause.val);
            if (tfwNbS1SetupRsp->waitIe.pres)
               printf("\n[Stub] Received time to wait-IE with Value[%d]\n",
                      tfwNbS1SetupRsp->waitIe.val);
            retVal = FAIL;
         }
         break;
      case ENB_S1_SETUP_TIMEOUT_IND:
         printf("\n[Stub] Received S1-SETUP TIMEOUT INDICATION from TFW\n");
         retVal = FAIL;
         break;
      case UE_IDENTITY_REQ_IND:
         tfwIdReq = (ueIdentityReqInd_t *)&msgptr.msg;
         printf("\n[Stub] Received IDENTITY REQUEST INDICATION from TFW\n");
         requestedIdType = tfwIdReq->idType;
         break;
      case UE_PAGING_IND:
         printf("\n[Stub] Received Paging indication\n");
         tfwPagingInd = (uePagingInd_t*)&msgptr.msg;
         paging_ueid = tfwPagingInd->ue_Id;
        break;
      case UE_PDN_CONN_RSP_IND:
         tfwUePdnConRsp = (uePdnConRsp_t *)&msgptr.msg;
         if(tfwUePdnConRsp->status != 1)
         {
            printf("\n[Stub] Received PDN-CONNECTION REJECT from TFW\n");
            printf("\n[Stub] ESM-CAUSE[%d]\n",
                  tfwUePdnConRsp->m.conRejInfo.cause);
            retVal = FALSE;
         }
         else
         {
            printf("\n[Stub] Received PDN-CONNECTION SUCCESS from TFW\n");
            retVal = SUCC;
            ueErabInfo[tfwUePdnConRsp->ue_Id - 1].brLst = realloc(ueErabInfo[tfwUePdnConRsp->ue_Id - 1].brLst, ueErabInfo[tfwUePdnConRsp->ue_Id - 1].numOfBrs * sizeof(char));
            ueErabInfo[tfwUePdnConRsp->ue_Id - 1].brLst[ueErabInfo[tfwUePdnConRsp->ue_Id - 1].numOfBrs++] = tfwUePdnConRsp->m.pdnInfo.epsBearerId;
         }
         break;
      case UE_PDN_CONN_REQ_TIMEOUT_IND:
         printf("\n[Stub] Received PDN CONNECTION REQ TIMEOUT INDICATION from TFW\n");
         retVal = FALSE;
         break;
      case UE_NW_INIT_DETACH_REQUEST:
	      tfwNwInitDetachReq = (ueNwInitdetachReq_t*)&msgptr.msg;
         nwInitDetach_ueid = tfwNwInitDetachReq->ue_Id;
         break;
      case ERAB_REL_CMD:
         printf("\n[Stub] Received Erab Release Command from EnodeB App\n");
         tfwErabRelCmdInfo = (FwErabRelCmd_t*)&msgptr.msg;
         erabRelCmdInfo[tfwErabRelCmdInfo->ueId - 1].ueId = tfwErabRelCmdInfo->ueId;
         erabRelCmdInfo[tfwErabRelCmdInfo->ueId - 1].enbUeS1apId = tfwErabRelCmdInfo->enbUeS1apId;
         erabRelCmdInfo[tfwErabRelCmdInfo->ueId - 1].mmeUeS1apId = tfwErabRelCmdInfo->mmeUeS1apId;
         erabRelCmdInfo[tfwErabRelCmdInfo->ueId - 1].numOfErabIds = tfwErabRelCmdInfo->numOfErabIds;
         erabRelCmdInfo[tfwErabRelCmdInfo->ueId - 1].erabIdLst = (U8 *)malloc(tfwErabRelCmdInfo->numOfErabIds * sizeof(U8));
         memcpy(erabRelCmdInfo[tfwErabRelCmdInfo->ueId - 1].erabIdLst,
               tfwErabRelCmdInfo->erabIdLst,
               tfwErabRelCmdInfo->numOfErabIds * sizeof(U8));
         break;
      case UE_ACT_DED_BER_REQ:
         tfwActvDedBerReq =(UeActDedBearCtxtReq_t*)&msgptr.msg;
         UeDedBerLst[tfwActvDedBerReq->ue_Id].ueId = tfwActvDedBerReq->ue_Id; 
         UeDedBerLst[tfwActvDedBerReq->ue_Id].dedBerIdLst[0] = tfwActvDedBerReq->bearerId;
         break;
      case UE_NAS_NON_DELIVERY_IND:
         tfwNasNonDelRsp = (ueNasNonDelRsp_t *)&msgptr.msg;
         printf("Nas Non Delivery Indication (ueId: %d)\n", tfwNasNonDelRsp->ue_Id);
         break;
      case INT_CTX_SETUP_IND:
         tfwIntCtxSetupInd = (FwNbIntCtxSetupInd_t *)&msgptr.msg;
         printf("Initial Context Setup Indication (ueId: %d) (status: %d)\n", tfwIntCtxSetupInd->ueId,tfwIntCtxSetupInd->status);
         break;
      case UE_PDN_DISCONNECT_TIMEOUT_IND:
         printf("[Stub] Received PDN Disconnect Timeout Ind from TFW\n");
         tfwPdnDisconnFail = (uePdnDisconnFail_t *)&msgptr.msg;
         printf("[Stub] PDN Disconnect failed for ueId(%d)\n",
                 tfwPdnDisconnFail->ueId);
	 break;
      default:
         break;
   }

   if (msgptr.msgType == UE_ATTACH_ACCEPT_IND)
   {
      ueAttachAccept_t TC_AttachAccept;
      memcpy(&TC_AttachAccept, &msgptr.msg, sizeof(ueAttachAccept_t));
      unsigned char  ueId = TC_AttachAccept.ue_Id;
      memcpy(UeIpInfoLst[ueId-1].UeIpAdrLst[UeIpInfoLst[ueId-1].noIfAssinedIps],
             TC_AttachAccept.esmInfo.pAddr.addrInfo, 4);
      T3412 = TC_AttachAccept.t3412;
      printf("[Stub] T3412 = %d\n", T3412);
      UeIpInfoLst[ueId-1].noIfAssinedIps++;
   }
   else if (msgptr.msgType == UE_TAU_ACCEPT_IND)
   {
      if ((tfwTauAccept->gutiChanged) && (!noTauComplete))
      {
         /* If new GUTI is coming, then send TAU complete */
         printf("[Stub] Triggering TAU Complete from stub as GUTI changed\n");
         msg = malloc(sizeof(ueTauComplete_t));
         memset(msg, 0, sizeof(ueTauComplete_t));
         ((ueTauComplete_t*)msg)->ue_Id = tfwTauAccept->ue_Id;

         tfwApi(UE_TAU_COMPLETE, msg);
         free(msg);
      }
      else
      {
         printf("[Stub] Not triggering TAU Complete from stub\n");
         noTauComplete = 0; 
      }
   }
   else if (msgptr.msgType == UE_PDN_CONN_RSP_IND)
   {
     ueId = tfwUePdnConRsp->ue_Id;
     memcpy(UeIpInfoLst[ueId-1].UeIpAdrLst[UeIpInfoLst[ueId-1].noIfAssinedIps],\
       tfwUePdnConRsp->m.pdnInfo.pAddr.addrInfo, 4);
     UeIpInfoLst[ueId-1].noIfAssinedIps++;
   }

   /*if(msgctl(msgQid, IPC_RMID, 0) == -1)
   {
      perror("msgctl(IPC_RMID) failed");
      exit(1);
   }*/

   /* Print any other message received */
   /* upon timeout return failure */
   /* upon reception of msgId return success */

   return retVal;
} /* TC_msg_recv */

void TC_API(short int msgId, void *ptr, short int msgLen)
{
   /* post received message to TC message queue */
   MsgBuf sbuf;

   sbuf.msgType = msgId;
   sbuf.msgLen = msgLen;
   memcpy(sbuf.msg, ptr, msgLen);

   if (msgsnd(msgQid, &sbuf, sizeof(MsgBuf), IPC_NOWAIT) < 0)
   {
      printf ("\n[Stub] %s:%s():%d: Message send failed\n",
              __FILE__, __FUNCTION__, __LINE__);
      perror("[Stub] ERROR: ");
      exit(0);
   }
   else
   {
      printf("[Stub] %s:%s():%d: Message Sent\n", __FILE__, __FUNCTION__,
             __LINE__);
   }

} /* TC_API */

void tsStartPeriodicTauTimer(unsigned char ueId, unsigned char testType)
{
   printf("T3412: %d\n", T3412);

   int iterations = 0;
   int iter_executed = 0;
   int msec = 0, trigger = 5 * 1000; /* 32s */
   clock_t before = clock();

   while (msec < trigger)
   {
      clock_t difference = clock() - before;
      msec = difference * 1000 / CLOCKS_PER_SEC;
      iterations++;

      if (msec == trigger)
      {
         printf("[Stub] GPRS TIMER  T3412 expired\n"\
                "Sending Tracking area update Request..\n");
         tsSendTauRequest(ueId, "Periodic", FALSE, testType);

         if(TC_msg_recv(UE_CTX_REL_IND, 10) == SUCC)
         {
            printf("\nReceived UE Context Release indication\n");
         }
         msec = 0;
         before = clock();
         iter_executed++;
      }
      if (iter_executed == 2)
         break;
   }
   printf("[Stub] Time taken %d seconds %d milliseconds (%d iterations)\n",
         msec/1000, msec%1000, iterations);
}

void tsStepByStepAttachWithImsi(unsigned char ueId)
{
   void* msgptr = NULL;

   printf("[Stub] Entering tsStepByStepAttachWithImsi(), ueId(%d)\n", ueId);

   /* Fill Attach request */
   msgptr = malloc(sizeof(ueAttachRequest_t));
   memset(msgptr, 0, sizeof(ueAttachRequest_t));
   ((ueAttachRequest_t*)msgptr)->ue_Id = ueId;
   ((ueAttachRequest_t*)msgptr)->mIdType = TFW_MID_TYPE_IMSI;
   ((ueAttachRequest_t*)msgptr)->epsAttachType = TFW_EPS_ATTACH_TYPE_EPS_ATTACH;
   ((ueAttachRequest_t*)msgptr)->useOldSecCtxt =
                                                TFW_CREATE_NEW_SECURITY_CONTEXT;

   /* Send Attach Request to TfwApp */
   printf("\n[Stub] Sending Attach Request, ueId(%d)\n", ueId);
   tfwApi(UE_ATTACH_REQUEST, msgptr);
   free(msgptr);

   /* Wait For Auth request indication */
   if (TC_msg_recv(UE_AUTH_REQ_IND, 10) == SUCC)
   {
      printf("\n[Stub] UE Auth Request indication Completed\n");
   }
   else
   {
      printf("\n[Stub] UE Auth Request indication failed\n");
   }

   /* Fill Auth Response Indication */
   msgptr = malloc(sizeof(ueAuthResp_t));
   memset(msgptr, 0, sizeof(ueAuthResp_t));
   ((ueAuthResp_t*)msgptr)->ue_Id = ueId;
   printf("\n[Stub] Sending Authentication Response\n");
   tfwApi(UE_AUTH_RESP, msgptr);
   free(msgptr);

   /* Wait for Security Mode Command indication */
   if (TC_msg_recv(UE_SEC_MOD_CMD_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Security mode command indication\n");
   }
   else
   {
      printf("\n[Stub] security mode command indication failed\n");
   }

   /* Fill Security Mode complete Indication */
   msgptr = malloc(sizeof(ueSecModeComplete_t));
   memset(msgptr, 0, sizeof(ueSecModeComplete_t));
   ((ueSecModeComplete_t*)msgptr)->ue_Id = ueId;
   printf("\n[Stub] Sending Security mode complete \n");
   tfwApi(UE_SEC_MOD_COMPLETE,msgptr);
   free(msgptr);

   /* Wait for Initial Context Setup indication */
   if (TC_msg_recv(INT_CTX_SETUP_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Initial Context Setup indication\n");
   }
   else
   {
      printf("\n[Stub] Initial Context Setup indication failed\n");
   }

   /* Wait for Attach Accept indication */
   if (TC_msg_recv(UE_ATTACH_ACCEPT_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Attach Accept indication\n");
   }
   else
   {
      printf("\n[Stub] Attach Accept indication failed\n");
   }

   /* Fill Attach Complete Indication to TFW */
   msgptr = malloc(sizeof(ueAttachComplete_t));
   memset(msgptr, 0, sizeof(ueAttachComplete_t));
   ((ueAttachComplete_t*)msgptr)->ue_Id = ueId;
   
   printf("\n[Stub] Sending Attach complete\n");
   tfwApi(UE_ATTACH_COMPLETE, msgptr);
   free(msgptr);

}
void tsAttachWithAUTV(unsigned char ueId)
{
   void* msgptr = NULL;

   printf("[Stub] Entering tsStepByStepAttachWithImsi(), ueId(%d)\n", ueId);

   /* Fill Attach request */
   msgptr = malloc(sizeof(ueAttachRequest_t));
   memset(msgptr, 0, sizeof(ueAttachRequest_t));
   ((ueAttachRequest_t*)msgptr)->ue_Id = ueId;
   ((ueAttachRequest_t*)msgptr)->mIdType = TFW_MID_TYPE_IMSI;
   ((ueAttachRequest_t*)msgptr)->epsAttachType = TFW_EPS_ATTACH_TYPE_EPS_ATTACH;
   ((ueAttachRequest_t*)msgptr)->useOldSecCtxt =
                                                TFW_CREATE_NEW_SECURITY_CONTEXT;

   ((ueAttachRequest_t*)msgptr)->addUpdTyp_pr.pres = TRUE;
   /* type= 0 means AUTV = 0 , No addnl Info - should be interpreted as combined attach by MME*/
   /* type= 1 means AUTV = 1 , SMS only */ 
   ((ueAttachRequest_t*)msgptr)->addUpdTyp_pr.type = 1; 

   /* Send Attach Request to TfwApp */
   printf("\n[Stub] Sending Attach Request, ueId(%d)\n", ueId);
   tfwApi(UE_ATTACH_REQUEST, msgptr);
   free(msgptr);

   /* Wait For Auth request indication */
   if (TC_msg_recv(UE_AUTH_REQ_IND, 10) == SUCC)
   {
      printf("\n[Stub] UE Auth Request indication Completed\n");
   }
   else
   {
      printf("\n[Stub] UE Auth Request indication failed\n");
   }

   /* Fill Auth Response Indication */
   msgptr = malloc(sizeof(ueAuthResp_t));
   memset(msgptr, 0, sizeof(ueAuthResp_t));
   ((ueAuthResp_t*)msgptr)->ue_Id = ueId;
   printf("\n[Stub] Sending Authentication Response\n");
   tfwApi(UE_AUTH_RESP, msgptr);
   free(msgptr);

   /* Wait for Security Mode Command indication */
   if (TC_msg_recv(UE_SEC_MOD_CMD_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Security mode command indication\n");
   }
   else
   {
      printf("\n[Stub] security mode command indication failed\n");
   }

   /* Fill Security Mode complete Indication */
   msgptr = malloc(sizeof(ueSecModeComplete_t));
   memset(msgptr, 0, sizeof(ueSecModeComplete_t));
   ((ueSecModeComplete_t*)msgptr)->ue_Id = ueId;
   printf("\n[Stub] Sending Security mode complete \n");
   tfwApi(UE_SEC_MOD_COMPLETE,msgptr);
   free(msgptr);

   /* Wait for Initial Context Setup indication */
   if (TC_msg_recv(INT_CTX_SETUP_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Initial Context Setup indication\n");
   }
   else
   {
      printf("\n[Stub] Initial Context Setup indication failed\n");
   }

   /* Wait for Attach Accept indication */
   if (TC_msg_recv(UE_ATTACH_ACCEPT_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Attach Accept indication\n");
   }
   else
   {
      printf("\n[Stub] Attach Accept indication failed\n");
   }

   /* Fill Attach Complete Indication to TFW */
   msgptr = malloc(sizeof(ueAttachComplete_t));
   memset(msgptr, 0, sizeof(ueAttachComplete_t));
   ((ueAttachComplete_t*)msgptr)->ue_Id = ueId;
   
   printf("\n[Stub] Sending Attach complete\n");
   tfwApi(UE_ATTACH_COMPLETE, msgptr);
   free(msgptr);
}

void tsAttachWithSecModeReject(unsigned char ueId)
{
   void* msgptr = NULL;

   printf("[Stub] Entering tsStepByStepAttachWithImsi(), ueId(%d)\n", ueId);

   /* Fill Attach request */
   msgptr = malloc(sizeof(ueAttachRequest_t));
   memset(msgptr, 0, sizeof(ueAttachRequest_t));
   ((ueAttachRequest_t*)msgptr)->ue_Id = ueId;
   ((ueAttachRequest_t*)msgptr)->mIdType = TFW_MID_TYPE_IMSI;
   ((ueAttachRequest_t*)msgptr)->epsAttachType = TFW_EPS_ATTACH_TYPE_EPS_ATTACH;
   ((ueAttachRequest_t*)msgptr)->useOldSecCtxt =
                                                TFW_CREATE_NEW_SECURITY_CONTEXT;

   /* Send Attach Request to TfwApp */
   printf("\n[Stub] Sending Attach Request \n");
   tfwApi(UE_ATTACH_REQUEST, msgptr);
   free(msgptr);

   /* Wait For Auth request indication */
   if (TC_msg_recv(UE_AUTH_REQ_IND, 10) == SUCC)
   {
      printf("\n[Stub] UE Auth Request indication Completed\n");
   }
   else
   {
      printf("\n[Stub] UE Auth Request indication failed\n");
   }

   /* Fill Auth Response Indication */
   msgptr = malloc(sizeof(ueAuthResp_t));
   memset(msgptr, 0, sizeof(ueAuthResp_t));
   ((ueAuthResp_t*)msgptr)->ue_Id = ueId;
   printf("\n[Stub] Sending Authentication Response\n");
   tfwApi(UE_AUTH_RESP, msgptr);
   free(msgptr);

   /* Wait for Security Mode Command indication */
   if (TC_msg_recv(UE_SEC_MOD_CMD_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Security mode command indication\n");
   }
   else
   {
      printf("\n[Stub] security mode command indication failed\n");
   }

   /* Fill Security Mode complete Indication */
   msgptr = malloc(sizeof(ueSecModeReject_t));
   memset(msgptr, 0, sizeof(ueSecModeReject_t));
   ((ueSecModeReject_t*)msgptr)->ue_Id = ueId;
   ((ueSecModeReject_t*)msgptr)->cause = 24;
/*
Valid EMM cause for Security mode reject - TS 24.301 sec. 5.4.3.5
#23:UE security capabilities mismatch;
#24:security mode rejected, unspecified.
*/
   
   printf("\n[Stub] Sending Security mode Reject with Cause 24 \n");
   tfwApi(UE_SEC_MOD_REJECT,msgptr);
   free(msgptr);

   /* Wait for Attach FAIL indication */
   if (TC_msg_recv(UE_ATTACH_REJECT_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Attach Fail indication\n");
   }
   if(TC_msg_recv(UE_CTX_REL_IND, 10) == SUCC)
   {  
      printf("\nReceived UE Context Release indication\n");
   }  

}

void SyncFailureWithWrapARound(unsigned char ueId)
{
   void* msgptr = NULL;

   printf("[Stub] Entering tsStepByStepAttachWithImsi(), ueId(%d)\n", ueId);

   /* Fill Attach request */
   msgptr = malloc(sizeof(ueAttachRequest_t));
   memset(msgptr, 0, sizeof(ueAttachRequest_t));
   ((ueAttachRequest_t*)msgptr)->ue_Id = ueId;
   ((ueAttachRequest_t*)msgptr)->mIdType = TFW_MID_TYPE_IMSI;
   ((ueAttachRequest_t*)msgptr)->epsAttachType = TFW_EPS_ATTACH_TYPE_EPS_ATTACH;
   ((ueAttachRequest_t*)msgptr)->useOldSecCtxt =
                                                TFW_CREATE_NEW_SECURITY_CONTEXT;

   /* Send Attach Request to TfwApp */
   printf("\n[Stub] Sending Attach Requst\n");
   tfwApi(UE_ATTACH_REQUEST, msgptr);
   free(msgptr);

   /* Wait For Auth request indication */
   if (TC_msg_recv(UE_AUTH_REQ_IND, 10) == SUCC)
   {
      printf("\n[Stub] UE Auth Request indication Completed\n");
   }
   else
   {
      printf("\n[Stub] UE Auth Request indication failed\n");
   }

   /* Fill Auth Response Indication with wrong Sqn */
   msgptr = malloc(sizeof(ueAuthResp_t));
   memset(msgptr, 0, sizeof(ueAuthResp_t));
   ((ueAuthResp_t*)msgptr)->ue_Id = ueId;
   ((ueAuthResp_t*)msgptr)->sqnRcvd.pres = TRUE;
   memcpy(((ueAuthResp_t*)msgptr)->sqnRcvd.sqn, "111111", 6);
   
   ((ueAuthResp_t*)msgptr)->maxSqnRcvd.pres = TRUE;
   memcpy(((ueAuthResp_t*)msgptr)->maxSqnRcvd.sqn, "000001", 6);
   printf("\n[Stub] Sending Authentication Response\n");
   tfwApi(UE_AUTH_RESP, msgptr);
   free(msgptr);

   /* Wait For Auth request indication */
   if (TC_msg_recv(UE_AUTH_REQ_IND, 10) == SUCC)
   {
      printf("\n[Stub] UE Auth Request indication Completed\n");
   }
   else
   {
      printf("\n[Stub] UE Auth Request indication failed\n");
   }

   /* Fill Auth Response Indication */
   msgptr = malloc(sizeof(ueAuthResp_t));
   memset(msgptr, 0, sizeof(ueAuthResp_t));
   ((ueAuthResp_t*)msgptr)->ue_Id = ueId;
   ((ueAuthResp_t*)msgptr)->sqnRcvd.pres = FALSE;
   ((ueAuthResp_t*)msgptr)->maxSqnRcvd.pres = FALSE;

   printf("\n[Stub] Sending Authentication Response\n");
   tfwApi(UE_AUTH_RESP, msgptr);
   free(msgptr);

   /* Wait for Security Mode Command indication */
   if (TC_msg_recv(UE_SEC_MOD_CMD_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Security mode command indication\n");
   }
   else
   {
      printf("\n[Stub] security mode command indication failed\n");
   }

   /* Fill Security Mode complete Indication */
   msgptr = malloc(sizeof(ueSecModeComplete_t));
   memset(msgptr, 0, sizeof(ueSecModeComplete_t));
   ((ueAuthResp_t*)msgptr)->ue_Id = ueId;

   printf("\n[Stub] Sending Security Mode Complete\n");
   tfwApi(UE_SEC_MOD_COMPLETE,msgptr);
   free(msgptr);

   /* Wait for Initial Context Setup indication */
   if (TC_msg_recv(INT_CTX_SETUP_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Initial Context Setup indication\n");
   }
   else
   {
      printf("\n[Stub] Initial Context Setup indication failed\n");
   }

   /* Wait for Attach Accept indication */
   if (TC_msg_recv(UE_ATTACH_ACCEPT_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Attach Accept indication\n");
   }
   else
   {
      printf("\n[Stub] Attach Accept indication failed\n");
   }

   /* Fill Attach Complete Indication to TFW */
   msgptr = malloc(sizeof(ueAttachComplete_t));
   memset(msgptr, 0, sizeof(ueAttachComplete_t));
   ((ueAttachComplete_t*)msgptr)->ue_Id = ueId;

   printf("\n[Stub] Sending Attach Complete\n");
   tfwApi(UE_ATTACH_COMPLETE, msgptr);
   free(msgptr);
}

void tsAuthFailAMF(unsigned char ueId)
{
   void* msgptr = NULL;

   printf("[Stub] Entering tsStepByStepAttachWithImsi(), ueId(%d)\n", ueId);

   /* Fill Attach request */
   msgptr = malloc(sizeof(ueAttachRequest_t));
   memset(msgptr, 0, sizeof(ueAttachRequest_t));
   ((ueAttachRequest_t*)msgptr)->ue_Id = ueId;
   ((ueAttachRequest_t*)msgptr)->mIdType = TFW_MID_TYPE_IMSI;
   ((ueAttachRequest_t*)msgptr)->epsAttachType = TFW_EPS_ATTACH_TYPE_EPS_ATTACH;
   ((ueAttachRequest_t*)msgptr)->useOldSecCtxt =
                                                TFW_CREATE_NEW_SECURITY_CONTEXT;

   /* Send Attach Request to TfwApp */
   printf("\n[Stub] Sending Attach Requst\n");
   tfwApi(UE_ATTACH_REQUEST, msgptr);
   free(msgptr);

   /* Wait For Auth request indication */
   if (TC_msg_recv(UE_AUTH_REQ_IND, 10) == SUCC)
   {
      printf("\n[Stub] UE Auth Request indication Completed\n");
   }
   else
   {
      printf("\n[Stub] UE Auth Request indication failed\n");
   }

   /* Fill Auth Response Indication with wrong Sqn */
   msgptr = malloc(sizeof(ueAuthResp_t));
   memset(msgptr, 0, sizeof(ueAuthResp_t));
   ((ueAuthResp_t*)msgptr)->ue_Id = ueId;
   ((ueAuthResp_t*)msgptr)->nonEPSAuthFail=TRUE;
   
   printf("\n[Stub] Sending Authentication Response\n");
   tfwApi(UE_AUTH_RESP, msgptr);
   free(msgptr);
   
   /* Wait for IDENTITY REQUEST Indication */
   if (TC_msg_recv(UE_IDENTITY_REQ_IND, 10) == SUCC)
   {
      printf("[Stub] IDENTITY REQUEST Indication Completed\n");
   }
   else
   {
      printf("[Stub] IDENTITY REQUEST Indication failed\n");
   }

   /* Fill Identity Response */
   msgptr = malloc(sizeof(ueIdentityResp_t));
   memset(msgptr, 0, sizeof(ueIdentityResp_t));
   ((ueIdentityResp_t*)msgptr)->ue_Id = ueId;
   ((ueIdentityResp_t*)msgptr)->idType = requestedIdType;

   /* Send IDENTITY RESPONSE to TfwApp */
   printf("[Stub] Triggering IDENTITY RESPONSE from stub for ueId(%d),"\
          " requestedIdType(%d)\n", ueId, requestedIdType);
   tfwApi(UE_IDENTITY_RESP, msgptr);
   free(msgptr);

   /* Wait For Auth request indication */
   if (TC_msg_recv(UE_AUTH_REQ_IND, 10) == SUCC)
   {
      printf("\n[Stub] UE Auth Request indication Completed\n");
   }
   else
   {
      printf("\n[Stub] UE Auth Request indication failed\n");
   }

   /* Fill Auth Response Indication */
   msgptr = malloc(sizeof(ueAuthResp_t));
   memset(msgptr, 0, sizeof(ueAuthResp_t));
   ((ueAuthResp_t*)msgptr)->ue_Id = ueId;
   ((ueAuthResp_t*)msgptr)->sqnRcvd.pres = FALSE;

   printf("\n[Stub] Sending Authentication Response\n");
   tfwApi(UE_AUTH_RESP, msgptr);
   free(msgptr);

   /* Wait for Security Mode Command indication */
   if (TC_msg_recv(UE_SEC_MOD_CMD_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Security mode command indication\n");
   }
   else
   {
      printf("\n[Stub] security mode command indication failed\n");
   }

   /* Fill Security Mode complete Indication */
   msgptr = malloc(sizeof(ueSecModeComplete_t));
   memset(msgptr, 0, sizeof(ueSecModeComplete_t));
   ((ueAuthResp_t*)msgptr)->ue_Id = ueId;

   printf("\n[Stub] Sending Security Mode Complete\n");
   tfwApi(UE_SEC_MOD_COMPLETE,msgptr);
   free(msgptr);

   /* Wait for Initial Context Setup indication */
   if (TC_msg_recv(INT_CTX_SETUP_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Initial Context Setup indication\n");
   }
   else
   {
      printf("\n[Stub] Initial Context Setup indication failed\n");
   }

   /* Wait for Attach Accept indication */
   if (TC_msg_recv(UE_ATTACH_ACCEPT_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Attach Accept indication\n");
   }
   else
   {
      printf("\n[Stub] Attach Accept indication failed\n");
   }

   /* Fill Attach Complete Indication to TFW */
   msgptr = malloc(sizeof(ueAttachComplete_t));
   memset(msgptr, 0, sizeof(ueAttachComplete_t));
   ((ueAttachComplete_t*)msgptr)->ue_Id = ueId;

   printf("\n[Stub] Sending Attach Complete\n");
   tfwApi(UE_ATTACH_COMPLETE, msgptr);
   free(msgptr);
}

void tsStepByStepAttachWithGuti(unsigned char ueId)
{
   void* msgptr = NULL;

   printf("[Stub] Entering tsStepByStepAttachWithGuti(), ueId(%d)\n", ueId);

   /* Fill Attach Request */
   msgptr = malloc(sizeof(ueAttachRequest_t));
   memset(msgptr, 0, sizeof(ueAttachRequest_t));
   ((ueAttachRequest_t*)msgptr)->ue_Id = ueId;
   ((ueAttachRequest_t*)msgptr)->mIdType = TFW_MID_TYPE_GUTI;
   ((ueAttachRequest_t*)msgptr)->epsAttachType = TFW_EPS_ATTACH_TYPE_EPS_ATTACH;
   ((ueAttachRequest_t*)msgptr)->useOldSecCtxt = TFW_CREATE_NEW_SECURITY_CONTEXT;

   /* Send ATTACH REQUEST to TfwApp */
   printf("[Stub] Triggering ATTACH REQUEST from stub for ueId(%d)\n", ueId);
   tfwApi(UE_ATTACH_REQUEST, msgptr);
   free(msgptr);

   /* Wait for IDENTITY REQUEST Indication */
   if (TC_msg_recv(UE_IDENTITY_REQ_IND, 10) == SUCC)
   {
      printf("[Stub] IDENTITY REQUEST Indication Completed\n");
   }
   else
   {
      printf("[Stub] IDENTITY REQUEST Indication failed\n");
   }

   /* Fill Identity Response */
   msgptr = malloc(sizeof(ueIdentityResp_t));
   memset(msgptr, 0, sizeof(ueIdentityResp_t));
   ((ueIdentityResp_t*)msgptr)->ue_Id = ueId;
   ((ueIdentityResp_t*)msgptr)->idType = requestedIdType;

   /* Send IDENTITY RESPONSE to TfwApp */
   printf("[Stub] Triggering IDENTITY RESPONSE from stub for ueId(%d),"\
          " requestedIdType(%d)\n", ueId, requestedIdType);
   tfwApi(UE_IDENTITY_RESP, msgptr);
   free(msgptr);

   /* Wait for AUTHENTICATION REQUEST indication */
   if (TC_msg_recv(UE_AUTH_REQ_IND, 10) == SUCC)
   {
      printf("[Stub] AUTHENTICATION REQUEST Indication Completed\n");
   }
   else
   {
      printf("[Stub] AUTHENTICATION REQUEST Indication failed\n");
   }

   /* Fill Auth Response Indication */
   msgptr = malloc(sizeof(ueAuthResp_t));
   memset(msgptr, 0, sizeof(ueAuthResp_t));
   ((ueAuthResp_t*)msgptr)->ue_Id = ueId;
   ((ueAuthResp_t*)msgptr)->sqnRcvd.pres = FALSE;

   /* Send AUTHENTICATION RESPONSE to TfwApp */
   printf("[Stub] Triggering AUTHENTICATION RESPONSE from stub for ueId(%d)\n",
          ueId);
   tfwApi(UE_AUTH_RESP, msgptr);

   free(msgptr);

   /* Wait for SECURITY MODE COMMAND Indication */
   if (TC_msg_recv(UE_SEC_MOD_CMD_IND, 10) == SUCC)
   {
      printf("[Stub] Received SECURITY MODE COMMAND Indication\n");
   }
   else
   {
      printf("[Stub] SECURITY MODE COMMAND Indication failed\n");
   }

   /* Fill Security Mode complete Indication */
   msgptr = malloc(sizeof(ueSecModeComplete_t));
   memset(msgptr, 0, sizeof(ueSecModeComplete_t));
   ((ueSecModeComplete_t*)msgptr)->ue_Id = ueId;

   /* Send SECURITY MODE COMPLETE to TfwApp */
   printf("[Stub] Triggering SECURITY MODE COMPLETE from stub for ueId(%d)\n",
          ueId);
   tfwApi(UE_SEC_MOD_COMPLETE, msgptr);
   free(msgptr);

   /* Wait for Initial Context Setup indication */
   if (TC_msg_recv(INT_CTX_SETUP_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Initial Context Setup indication\n");
   }
   else
   {
      printf("\n[Stub] Initial Context Setup indication failed\n");
   }

   /* Wait for ATTACH ACCEPT Indication */
   if (TC_msg_recv(UE_ATTACH_ACCEPT_IND, 10) == SUCC)
   {
      printf("[Stub] Received ATTACH ACCEPT Indication\n");
   }
   else
   {
      printf("[Stub] ATTACH ACCEPT Indication failed\n");
   }

   /* Fill Attach Complete Indication to TFW */
   msgptr = malloc(sizeof(ueAttachComplete_t));
   memset(msgptr, 0, sizeof(ueAttachComplete_t));
   ((ueAttachComplete_t*)msgptr)->ue_Id = ueId;

   /* Send ATTACH COMPLETE to TfwApp */
   printf("[Stub] Triggering ATTACH COMPLETE from stub for ueId(%d)\n", ueId);
   tfwApi(UE_ATTACH_COMPLETE, msgptr);
   free(msgptr);
}

void tsStepByStepReAttach(unsigned char ueId)
{
   void* msgptr = NULL;

   printf("[Stub] Entering tsStepByStepReAttach(), ueId(%d)\n", ueId);

   /* Fill Attach request */
   msgptr = malloc(sizeof(ueAttachRequest_t));
   memset(msgptr, 0, sizeof(ueAttachRequest_t));
   ((ueAttachRequest_t*)msgptr)->ue_Id = ueId;
   ((ueAttachRequest_t*)msgptr)->mIdType = TFW_MID_TYPE_IMSI;
   ((ueAttachRequest_t*)msgptr)->epsAttachType = TFW_EPS_ATTACH_TYPE_EPS_ATTACH;
   ((ueAttachRequest_t*)msgptr)->useOldSecCtxt =
                                                TFW_CREATE_NEW_SECURITY_CONTEXT;

   /* Send Attach Request to TfwApp */
   printf("\n[Stub] Sending Attach Request, ueId(%d)\n", ueId);
   tfwApi(UE_ATTACH_REQUEST, msgptr);
   free(msgptr);

   /* Wait For Auth request indication */
   if (TC_msg_recv(UE_AUTH_REQ_IND, 10) == SUCC)
   {
      printf("[Stub] UE Auth Request indication Completed\n");
   }
   else
   {
      printf("[Stub] UE Auth Request indication failed\n");
   }

   /* Fill Auth Response Indication */
   msgptr = malloc(sizeof(ueAuthResp_t));
   memset(msgptr, 0, sizeof(ueAuthResp_t));
   ((ueAuthResp_t*)msgptr)->ue_Id = ueId;
   ((ueAuthResp_t*)msgptr)->sqnRcvd.pres = FALSE;

   printf("\n[Stub] Sending Attach Request, ueId(%d)\n", ueId);
   tfwApi(UE_AUTH_RESP, msgptr);
   free(msgptr);

   /* Wait for Security Mode Command indication */
   if (TC_msg_recv(UE_SEC_MOD_CMD_IND, 10) == SUCC)
   {
      printf("[Stub] Received Security mode command indication\n");
   }
   else
   {
      printf("[Stub] Security mode command indication failed\n");
   }

   /* Fill Security Mode complete Indication */
   msgptr = malloc(sizeof(ueSecModeComplete_t));
   memset(msgptr, 0, sizeof(ueSecModeComplete_t));
   ((ueSecModeComplete_t*)msgptr)->ue_Id = ueId;

   printf("\n[Stub] Sending Security Mode Complete, ueId(%d)\n", ueId);
   tfwApi(UE_SEC_MOD_COMPLETE, msgptr);
   free(msgptr);

   /* Wait for Initial Context Setup indication */
   if (TC_msg_recv(INT_CTX_SETUP_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Initial Context Setup indication\n");
   }
   else
   {
      printf("\n[Stub] Initial Context Setup indication failed\n");
   }

   /* Wait for Attach Accept indication */
   if (TC_msg_recv(UE_ATTACH_ACCEPT_IND, 10)== SUCC)
   {
      printf("[Stub] Received Attach Accept indication\n");
   }
   else
   {
      printf("[Stub] Attach Accept indication failed\n");
   }

   /* Fill Attach Complete Indication to TFW */
   msgptr = malloc(sizeof(ueAttachComplete_t));
   memset(msgptr, 0, sizeof(ueAttachComplete_t));
   ((ueAttachComplete_t*)msgptr)->ue_Id = ueId;

   printf("\n[Stub] Sending Attach Complete, ueId(%d)\n", ueId);
   tfwApi(UE_ATTACH_COMPLETE, msgptr);
   free(msgptr);

   /* TODO : Store GUTI & security contexts, at ueApp or Stub ? */

   /* Send Attach Req with stored GUTI & security contexts */

   /* TODO: Check if AUTH & Security procedures are required ? */

   printf("[Stub] Waiting for UE Context Release\n");
   sleep(2);

   printf("\n----------------------------------\n"\
          "Sending UE context Release Request\n"\
          "----------------------------------\n");
   tsSendUeCntxtReleaseRequest(ueId, 18);
   sleep(2);

   printf("[Stub] Triggering Re-Attach with GUTI, ueId(%d)\n", ueId);

   /* Fill Attach Request */
   msgptr = malloc(sizeof(ueAttachRequest_t));
   memset(msgptr, 0, sizeof(ueAttachRequest_t));
   ((ueAttachRequest_t*)msgptr)->ue_Id = ueId;
   ((ueAttachRequest_t*)msgptr)->mIdType = TFW_MID_TYPE_GUTI;
   ((ueAttachRequest_t*)msgptr)->epsAttachType = TFW_EPS_ATTACH_TYPE_EPS_ATTACH;
   ((ueAttachRequest_t*)msgptr)->useOldSecCtxt =
                                                TFW_USE_OLD_SECURITY_CONTEXT;

   /* Send ATTACH REQUEST to TfwApp */
   printf("[Stub] Triggering ATTACH REQUEST from stub for ueId(%d)\n", ueId);
   tfwApi(UE_ATTACH_REQUEST, msgptr);
   free(msgptr);

   /* Wait for IDENTITY REQUEST Indication */
   if (TC_msg_recv(UE_IDENTITY_REQ_IND, 10) == SUCC)
   {
      printf("[Stub] IDENTITY REQUEST Indication Completed\n");
   }
   else
   {
      printf("[Stub] IDENTITY REQUEST Indication failed\n");
   }

   /* Fill Identity Response */
   msgptr = malloc(sizeof(ueIdentityResp_t));
   memset(msgptr, 0, sizeof(ueIdentityResp_t));
   ((ueIdentityResp_t*)msgptr)->ue_Id = ueId;
   ((ueIdentityResp_t*)msgptr)->idType = requestedIdType;

   /* Send IDENTITY RESPONSE to TfwApp */
   printf("[Stub] Triggering IDENTITY RESPONSE from stub for ueId(%d)\n", ueId);
   tfwApi(UE_IDENTITY_RESP, msgptr);
   free(msgptr);

   /* Wait for AUTHENTICATION REQUEST indication */
   if (TC_msg_recv(UE_AUTH_REQ_IND, 10) == SUCC)
   {
      printf("[Stub] AUTHENTICATION REQUEST Indication Completed\n");
   }
   else
   {
      printf("[Stub] AUTHENTICATION REQUEST Indication failed\n");
   }

   /* Fill Auth Response Indication */
   msgptr = malloc(sizeof(ueAuthResp_t));
   memset(msgptr, 0, sizeof(ueAuthResp_t));
   ((ueAuthResp_t*)msgptr)->ue_Id = ueId;
   ((ueAuthResp_t*)msgptr)->sqnRcvd.pres = FALSE;

   /* Send AUTHENTICATION RESPONSE to TfwApp */
   printf("[Stub] Triggering AUTHENTICATION RESPONSE from stub for ueId(%d)\n",
          ueId);

   tfwApi(UE_AUTH_RESP, msgptr);
   free(msgptr);

   /* Wait for SECURITY MODE COMMAND Indication */
   if (TC_msg_recv(UE_SEC_MOD_CMD_IND, 10) == SUCC)
   {
      printf("[Stub] Received SECURITY MODE COMMAND Indication\n");
   }
   else
   {
      printf("[Stub] SECURITY MODE COMMAND Indication failed\n");
   }

   /* Fill Security Mode complete Indication */
   msgptr = malloc(sizeof(ueSecModeComplete_t));
   memset(msgptr, 0, sizeof(ueSecModeComplete_t));
   ((ueSecModeComplete_t*)msgptr)->ue_Id = ueId;

   /* Send SECURITY MODE COMPLETE to TfwApp */
   printf("[Stub] Triggering SECURITY MODE COMPLETE from stub for ueId(%d)\n",
          ueId);
   tfwApi(UE_SEC_MOD_COMPLETE, msgptr);
   free(msgptr);

   /* Wait for Initial Context Setup indication */
   if (TC_msg_recv(INT_CTX_SETUP_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Initial Context Setup indication\n");
   }
   else
   {
      printf("\n[Stub] Initial Context Setup indication failed\n");
   }

   /* Wait for ATTACH ACCEPT Indication */
   if (TC_msg_recv(UE_ATTACH_ACCEPT_IND, 10) == SUCC)
   {
      printf("[Stub] Received ATTACH ACCEPT Indication\n");
   }
   else
   {
      printf("[Stub] ATTACH ACCEPT Indication failed\n");
   }

   /* Fill Attach Complete Indication to TFW */
   msgptr = malloc(sizeof(ueAttachComplete_t));
   memset(msgptr, 0, sizeof(ueAttachComplete_t));
   ((ueAttachComplete_t*)msgptr)->ue_Id = ueId;

   /* Send ATTACH COMPLETE to TfwApp */
   printf("[Stub] Triggering ATTACH COMPLETE from stub for ueId(%d)\n", ueId);
   tfwApi(UE_ATTACH_COMPLETE, msgptr);
   free(msgptr);
}

void tsAttachEmergency(unsigned char ueId)
{
   void* msgptr = NULL;

   printf("[Stub] Entering tsStepByStepReAttach(), ueId(%d)\n", ueId);

   /* Fill Attach request */
   msgptr = malloc(sizeof(ueAttachRequest_t));
   memset(msgptr, 0, sizeof(ueAttachRequest_t));
   ((ueAttachRequest_t*)msgptr)->ue_Id = ueId;
   ((ueAttachRequest_t*)msgptr)->mIdType = TFW_MID_TYPE_IMEI;
   ((ueAttachRequest_t*)msgptr)->epsAttachType = TFW_EPS_ATTACH_TYPE_EPS_EMRG_ATTACH;
   ((ueAttachRequest_t*)msgptr)->useOldSecCtxt =
                                                TFW_CREATE_NEW_SECURITY_CONTEXT;

   /* Send Attach Request to TfwApp */
   printf("\n[Stub] Sending Attach Request, ueId(%d)\n", ueId);
   tfwApi(UE_ATTACH_REQUEST, msgptr);
   free(msgptr);

   /* Wait for Initial Context Setup indication */
   if (TC_msg_recv(INT_CTX_SETUP_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Initial Context Setup indication\n");
   }
   else
   {
      printf("\n[Stub] Initial Context Setup indication failed\n");
   }

   /* Wait for Attach Accept indication */
   if (TC_msg_recv(UE_ATTACH_ACCEPT_IND, 10)== SUCC)
   {
      printf("[Stub] Received Attach Accept indication\n");
   }
   else
   {
      printf("[Stub] Attach Accept indication failed\n");
   }

   /* Fill Attach Complete Indication to TFW */
   msgptr = malloc(sizeof(ueAttachComplete_t));
   memset(msgptr, 0, sizeof(ueAttachComplete_t));
   ((ueAttachComplete_t*)msgptr)->ue_Id = ueId;

   printf("\n[Stub] Sending Attach Complete, ueId(%d)\n", ueId);
   tfwApi(UE_ATTACH_COMPLETE, msgptr);
   free(msgptr);

   /* TODO : Store GUTI & security contexts, at ueApp or Stub ? */

   /* Send Attach Req with stored GUTI & security contexts */

   /* TODO: Check if AUTH & Security procedures are required ? */

   printf("[Stub] Waiting for UE Context Release\n");
   sleep(2);

   printf("\n----------------------------------\n"\
          "Sending UE context Release Request\n"\
          "----------------------------------\n");
   tsSendUeCntxtReleaseRequest(ueId, 18);
   sleep(2);
}

void tsAttach_PCO_DRX(unsigned char ueId)
{
   void* msgptr =  NULL;

   printf("[Stub] Entering tsCompleteAttach(), ueId(%d)\n", ueId);

   /* send Attach request(END_TO_END) */
   msgptr = malloc(sizeof(ueAttachRequest_t));
   memset(msgptr, 0, sizeof(ueAttachRequest_t));
   ((ueAttachRequest_t*)msgptr)->ue_Id = ueId;
   ((ueAttachRequest_t*)msgptr)->mIdType = TFW_MID_TYPE_IMSI;
   ((ueAttachRequest_t*)msgptr)->epsAttachType = TFW_EPS_ATTACH_TYPE_EPS_ATTACH;
   ((ueAttachRequest_t*)msgptr)->useOldSecCtxt =
                                                TFW_CREATE_NEW_SECURITY_CONTEXT;

   ((ueAttachRequest_t*)msgptr)->protCfgOpts_pr.pres = TRUE;

   /* Config Protocol: '000' - PPP for use with IP PDP type or IP PDN type (see 3GPP TS 24.301 [120])*/
   /* All other values are interpreted as PPP in this version of the protocol.*/
   ((ueAttachRequest_t*)msgptr)->protCfgOpts_pr.cfgProt = 0x000;  
   
   ((ueAttachRequest_t*)msgptr)->protCfgOpts_pr.ext = 1;
   ((ueAttachRequest_t*)msgptr)->protCfgOpts_pr.numProtId = 1; /*Number of Protocols being configured*/
   ((ueAttachRequest_t*)msgptr)->protCfgOpts_pr.numContId = 2; /*Total Number of Containers */

   /* Pid: 
      0x8021:LCP
      0xC021:PAP
      0xC022:CHAP
      0xC023:IPCP
      */
   ((ueAttachRequest_t*)msgptr)->protCfgOpts_pr.p[0].pid = 0x8021; /*IPCP*/
   ((ueAttachRequest_t*)msgptr)->protCfgOpts_pr.p[0].len = 0x10;

   /* PPP IP Control Protocol packet */
   /*01 00 00 10 81 06 00 00 00 00 83 06 00 00 00 00 */
   
   ((ueAttachRequest_t*)msgptr)->protCfgOpts_pr.p[0].val[0] = 0x01; /* code = 01 - Config Request*/
   ((ueAttachRequest_t*)msgptr)->protCfgOpts_pr.p[0].val[1] = 0x00; /* Identifier : 00 */
   ((ueAttachRequest_t*)msgptr)->protCfgOpts_pr.p[0].val[2] = 0x00; /* Length : 16 */
   ((ueAttachRequest_t*)msgptr)->protCfgOpts_pr.p[0].val[3] = 0x10;
   ((ueAttachRequest_t*)msgptr)->protCfgOpts_pr.p[0].val[4] = 0x81; /* Options = 0x81: Primary DNS IP Addr */
   ((ueAttachRequest_t*)msgptr)->protCfgOpts_pr.p[0].val[5] = 0x06; /* len = 6 */
   ((ueAttachRequest_t*)msgptr)->protCfgOpts_pr.p[0].val[6] = 0x00; /* 00.00.00.00 */
   ((ueAttachRequest_t*)msgptr)->protCfgOpts_pr.p[0].val[7] = 0x00;
   ((ueAttachRequest_t*)msgptr)->protCfgOpts_pr.p[0].val[8] = 0x00;
   ((ueAttachRequest_t*)msgptr)->protCfgOpts_pr.p[0].val[9] = 0x00;
   ((ueAttachRequest_t*)msgptr)->protCfgOpts_pr.p[0].val[10] = 0x83;/* Options = 0x83: Secondary DNS IP Addr */
   ((ueAttachRequest_t*)msgptr)->protCfgOpts_pr.p[0].val[11] = 0x06;/* len = 6 */
   ((ueAttachRequest_t*)msgptr)->protCfgOpts_pr.p[0].val[12] = 0x00;/* 00.00.00.00 */
   ((ueAttachRequest_t*)msgptr)->protCfgOpts_pr.p[0].val[13] = 0x00;
   ((ueAttachRequest_t*)msgptr)->protCfgOpts_pr.p[0].val[14] = 0x00;
   ((ueAttachRequest_t*)msgptr)->protCfgOpts_pr.p[0].val[15] = 0x00;

   /* Containers */
   /*000DH (DNS Server IPv4 Address Request)*/
   ((ueAttachRequest_t*)msgptr)->protCfgOpts_pr.c[0].cid =  0x000d;
   ((ueAttachRequest_t*)msgptr)->protCfgOpts_pr.c[0].len = 0x00;

   /*000AH (IP address allocation via NAS signalling)*/
   ((ueAttachRequest_t*)msgptr)->protCfgOpts_pr.c[1].cid =  0x000a;
   ((ueAttachRequest_t*)msgptr)->protCfgOpts_pr.c[1].len = 0x00;
   
   /* Fill DRX Parameters */
   ((ueAttachRequest_t*)msgptr)->drxParm_pr.pres = TRUE;
   ((ueAttachRequest_t*)msgptr)->drxParm_pr.spltPGCycle = 704;/*704 (equivalent to no DRX)*/
   ((ueAttachRequest_t*)msgptr)->drxParm_pr.nonDrxTmr = 0x00;/*non-DRX mode after transfer state*/
   ((ueAttachRequest_t*)msgptr)->drxParm_pr.spltOnCcch = 0x01;/*Split pg cycle on CCCH is supported by the mobile station*/
   ((ueAttachRequest_t*)msgptr)->drxParm_pr.u.drxVal = 0x06;/*CN Specific DRX cycle length coefficient 6 and T = 32*/
      
   printf("\n[Stub] Sending End-to-End Attach Request, ueId(%d)\n", ueId);
   tfwApi(UE_END_TO_END_ATTACH_REQUEST, msgptr);
   free(msgptr);

   /* Wait for Initial Context Setup indication */
   if (TC_msg_recv(INT_CTX_SETUP_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Initial Context Setup indication\n");
   }
   else
   {
      printf("\n[Stub] Initial Context Setup indication failed\n");
   }

   /* Wait for Attach Accept indication */
   if (TC_msg_recv(UE_ATTACH_ACCEPT_IND, 10) == SUCC)
   {
      printf("\n[Stub] Received Attach Accept indication\n");
   }
   else
   {
      printf("\n[Stub] Attach failed\n");
   }
}

void tsCompleteAttach(unsigned char ueId)
{
   void* msgptr =  NULL;

   printf("[Stub] Entering tsCompleteAttach(), ueId(%d)\n", ueId);

   /* send Attach request(END_TO_END) */
   msgptr = malloc(sizeof(ueAttachRequest_t));
   memset(msgptr, 0, sizeof(ueAttachRequest_t));
   ((ueAttachRequest_t*)msgptr)->ue_Id = ueId;
   ((ueAttachRequest_t*)msgptr)->mIdType = TFW_MID_TYPE_IMSI;
   ((ueAttachRequest_t*)msgptr)->epsAttachType = TFW_EPS_ATTACH_TYPE_EPS_ATTACH;
   ((ueAttachRequest_t*)msgptr)->useOldSecCtxt =
                                                TFW_CREATE_NEW_SECURITY_CONTEXT;

   
   printf("\n[Stub] Sending End-to-End Attach Request, ueId(%d)\n", ueId);
   tfwApi(UE_END_TO_END_ATTACH_REQUEST, msgptr);
   free(msgptr);

   /* Wait for Initial Context Setup indication */
   if (TC_msg_recv(INT_CTX_SETUP_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Initial Context Setup indication\n");
   }
   else
   {
      printf("\n[Stub] Initial Context Setup indication failed\n");
   }

   /* Wait for Attach Accept indication */
   if (TC_msg_recv(UE_ATTACH_ACCEPT_IND, 10) == SUCC)
   {
      printf("\n[Stub] Received Attach Accept indication\n");
   }
   else
   {
      printf("\n[Stub] Attach failed\n");
   }
}

void tsSendAttachRequest(unsigned char ueId)
{
   tsCompleteAttach(ueId);
}

void tsSendDetachRequest(unsigned char ueId, unsigned char cause, Ue_Mode ueMode)
{
   void* msgptr = NULL;

   printf("[Stub] Entering tsSendDetachRequest(), ueId(%d)\n", ueId);

   msgptr = malloc(sizeof(uedetachReq_t));
   memset(msgptr, 0, sizeof(uedetachReq_t));
   ((uedetachReq_t*)msgptr)->ue_Id = ueId;
   ((uedetachReq_t*)msgptr)->ueDetType = cause;

   /* send Deatch request */
   printf("\n[Stub] Sending Detach Request, ueId(%d)\n", ueId);
   tfwApi(UE_DETACH_REQUEST, msgptr);
   free(msgptr);
   if(cause == UE_NORMAL_DETACH)
   {
      /* Wait for UE detach Accept Indication */
      if(TC_msg_recv(UE_DETACH_ACCEPT_IND, 10) == SUCC)
      {
         printf("\nReceived Detach Accept indication\n");
      }
   }
   if(TC_msg_recv(UE_CTX_REL_IND, 10) == SUCC)
   {
      printf("\nReceived UE Context Release indication\n");
   }
}

void tsSendTauRequest(unsigned char ueId, char *type, unsigned char flag, unsigned char testType)
{
   void* msgptr = NULL;
   printf("-------------------------------------"\
         "Sending Tracking area update "\
         "-------------------------------------\n");

   msgptr = malloc(sizeof(ueTauReq_t));
   memset(msgptr, 0, sizeof(ueTauReq_t));
   ((ueTauReq_t*)msgptr)->ue_Id = ueId;

   if (strcmp(type, "Normal") == 0)
      ((ueTauReq_t*)msgptr)->type = TFW_TA_UPDATING;
   else if (strcmp(type, "Periodic") == 0)
      ((ueTauReq_t*)msgptr)->type = TFW_PERIODIC_UPDATING;
   else
      printf("[Stub] Wrong EPS UPDATE TYPE\n");

   ((ueTauReq_t*)msgptr)->Actv_flag = flag;

   if (testType == TEST_TYPE_TAU_REJECT)
   {
      ((ueTauReq_t*)msgptr)->ueMtmsi.pres = TRUE;
      ((ueTauReq_t*)msgptr)->ueMtmsi.mTmsi = 1000;
   }
   else
   {
      ((ueTauReq_t*)msgptr)->ueMtmsi.pres = FALSE;
   }

   printf("\n[Stub] Sending Tracking Area Update, ueId(%d)\n", ueId);
   tfwApi(UE_TAU_REQ, msgptr);
   free(msgptr);
   if (testType == TEST_TYPE_TAU_REQUEST)
   {
      if(flag)
      {
         if(TC_msg_recv(INT_CTX_SETUP_IND, 10)== SUCC)
         {
            printf("\n[Stub] Received Initial Context Setup indication\n");
         }
      }
      if (TC_msg_recv(UE_TAU_ACCEPT_IND, 10)== SUCC)
      {
         printf("\n[Stub] Received TAU ACCEPT indication\n");
      }
      else
      {
         printf("[Stub] Failed to TAU ACCEPT Indication\n");
      }
   }
   if (testType == TEST_TYPE_TAU_REJECT)
   {
      if (TC_msg_recv(UE_TAU_REJECT_IND, 10)== SUCC)
      {
         printf("\n[Stub] Received TAU Reject indication\n");
      }
      else
      {
         printf("[Stub] Failed to TAU Reject Indication\n");
      }
   }
}

int tsSendServiceRequest(unsigned char ueId, unsigned char testType)
{
   void* msgptr =  NULL;

   msgptr = malloc(sizeof(ueserviceReq_t));
   memset(msgptr, 0, sizeof(ueserviceReq_t));
   ((ueserviceReq_t*)msgptr)->ue_Id = ueId;
   ((ueserviceReq_t*)msgptr)->rrcCause = TFW_MO_DATA;

   if (testType == TEST_TYPE_SERVICE_REJECT)
   {
      ((ueserviceReq_t*)msgptr)->ueMtmsi.pres = TRUE;
      ((ueserviceReq_t*)msgptr)->ueMtmsi.mTmsi = 1000;
   }
   else
   {
      ((ueserviceReq_t*)msgptr)->ueMtmsi.pres = FALSE;
   }

   if (testType == TEST_TYPE_PAGING)
   {
      ((ueserviceReq_t*)msgptr)->rrcCause = TFW_MT_ACCESS;
   }   

   printf("\n[Stub] Sending Service Request, ueId(%d)\n", ueId);
   tfwApi(UE_SERVICE_REQUEST, msgptr);
   free(msgptr);
   return 0;
}

int tsSendUeCntxtReleaseRequest(unsigned char ueId, unsigned char cause)
{
   void* msgptr =  NULL;

   msgptr = malloc(sizeof(ueCntxtRelReq_t));
   memset(msgptr, 0, sizeof(ueCntxtRelReq_t));
   ((ueCntxtRelReq_t*)msgptr)->ue_Id = ueId;
   ((ueCntxtRelReq_t*)msgptr)->cause.causeVal = cause;

   printf("\n[Stub] Sending Ue Context Release request, ueId(%d)\n", ueId); 
   tfwApi(UE_CNTXT_REL_REQUEST, msgptr);
   free(msgptr);

   if(TC_msg_recv(UE_CTX_REL_IND, 10) == SUCC)
   {
      printf("\nReceived UE Context Release indication\n");
   }

   return 0;
}

int tsSendUeRadCapUpdReq(U8 ueId, U8 * msg, U8 len, Bool sndS1AP  )
{
   void* msgptr =  NULL;

   msgptr = malloc(sizeof(ueRadCapUpd_t));
   memset(msgptr, 0, sizeof(ueRadCapUpd_t));
   ((ueRadCapUpd_t*)msgptr)->ue_Id = ueId;
   ((ueRadCapUpd_t*)msgptr)->snd_S1AP = sndS1AP;
   if (len > 0 && msg != NULL)
   	{
	   ((ueRadCapUpd_t*)msgptr)->radioCap_pr.pres = TRUE;
	   ((ueRadCapUpd_t*)msgptr)->radioCap_pr.len = len;
	   ((ueRadCapUpd_t*)msgptr)->radioCap_pr.radioCapMsg = malloc(len);
	   memcpy(((ueRadCapUpd_t*)msgptr)->radioCap_pr.radioCapMsg, msg,len);
	}
   printf("\n[Stub] Sending Ue Radio Capability Update Request, ueId(%d)\n", ueId);
   tfwApi(UE_RAD_CAP_UPDATE_REQ, msgptr);
   if (((ueRadCapUpd_t*)msgptr)->radioCap_pr.radioCapMsg != NULL)
   	{
   	  free(((ueRadCapUpd_t*)msgptr)->radioCap_pr.radioCapMsg);
   	}
   free(msgptr);

   return 0;
}

int tsSendPdnConnReq(uepdnConReq_t *pdnConReq)
{
   void* msgptr = NULL;

   msgptr = malloc(sizeof(uepdnConReq_t));
   memset(msgptr, 0, sizeof(uepdnConReq_t));

   ((uepdnConReq_t*)msgptr)->ue_Id = pdnConReq->ue_Id; 
   ((uepdnConReq_t*)msgptr)->reqType = pdnConReq->reqType; 
   ((uepdnConReq_t*)msgptr)->pdnType_pr.pres = pdnConReq->pdnType_pr.pres;
   if(pdnConReq->pdnType_pr.pres == 1)
   { 
      ((uepdnConReq_t*)msgptr)->pdnType_pr.pdn_type  = pdnConReq->pdnType_pr.pdn_type ;
   } 
   ((uepdnConReq_t*)msgptr)->pdnAPN_pr.pres  = pdnConReq->pdnAPN_pr.pres ;
   if(pdnConReq->pdnAPN_pr.pres == 1)
   { 
      ((uepdnConReq_t*)msgptr)->pdnAPN_pr.len  = pdnConReq->pdnAPN_pr.len ; 

      memcpy(((uepdnConReq_t*)msgptr)->pdnAPN_pr.pdn_apn,\
            pdnConReq->pdnAPN_pr.pdn_apn,pdnConReq->pdnAPN_pr.len);   
   }
   /* Send PDN Connection Request  to TfwApp */
   printf("\n[Stub] Sending PDN Connectivty Request, ueId(%d)\n", pdnConReq->ue_Id);
   tfwApi(UE_PDN_CONN_REQ, msgptr);
   free(msgptr);

   /* Wait For Auth request indication */
   if (TC_msg_recv(UE_PDN_CONN_RSP_IND, 10) == SUCC)
   {
      printf("\n[Stub] UE Pdn Connection Rsp indication Completed\n");
   }
   else
   {
      printf("\n[Stub] UE Pdn Connection Rsp indication failed\n");
   }
   return 0; 
}

int tsSendResetReq(unsigned int resetType, int numOfUes, unsigned char *ueLst)
{
   void* msgptr = NULL;

   printf("\n[Stub] Sending Reset Request\n");

   msgptr = malloc(sizeof(ResetReq));
   memset(msgptr, 0, sizeof(ResetReq));

   if(resetType == COMPLETE_RESET)
   {
      ((ResetReq*)msgptr)->rstType = COMPLETE_RESET;
      ((ResetReq*)msgptr)->cause.causeType = 1;
      ((ResetReq*)msgptr)->cause.causeVal = 1;

      tfwApi(RESET_REQ, msgptr);
      free(msgptr);
   }
   else if(resetType == PARTIAL_RESET)
   {
      ((ResetReq*)msgptr)->rstType = PARTIAL_RESET;
      ((ResetReq*)msgptr)->cause.causeType = 1;
      ((ResetReq*)msgptr)->cause.causeVal = 1;

      ((ResetReq*)msgptr)->r.partialRst.numOfConn = numOfUes;
      ((ResetReq*)msgptr)->r.partialRst.ueIdLst = malloc(numOfUes);
      memcpy(((ResetReq*)msgptr)->r.partialRst.ueIdLst, ueLst, numOfUes);

      tfwApi(RESET_REQ, msgptr);
      free(((ResetReq*)msgptr)->r.partialRst.ueIdLst);
      free(msgptr);
   }

   if (TC_msg_recv(RESET_ACK, 10) == SUCC)
   {
      printf("\n[Stub] Recieved S1 Reset Ack\n");
   }
   else
   {
      printf("\n[Stub] Failed to Recieve S1 Reset Ack\n");
   }
   return 0;
}

void tsSendDetachAccept(unsigned char ueId)
{
   void* msgptr =  NULL;

   msgptr = malloc(sizeof(ueDetachAcceptInd_t));
   memset(msgptr, 0, sizeof(ueDetachAcceptInd_t));
   ((ueDetachAcceptInd_t*)msgptr)->ue_Id = ueId;


   printf("\n[Stub] Sending Detach Accept, ueId(%d)\n", ueId);
   tfwApi(UE_TRIGGERED_DETACH_ACCEPT, msgptr);
   free(msgptr);
}

void tsSendErrIndMsg(void *msgptr)
{
   tfwApi(ENB_ERR_IND_MSG,msgptr);
}

void flush(int noOfUe)
{
   void* msgptr =  NULL;

   msgptr = malloc(sizeof(ueFlush_t));
   memset(msgptr, 0, sizeof(ueFlush_t));
   ((ueFlush_t*)msgptr)->noOfUe = noOfUe;

   printf("\n[Stub] Sending Flush\n");
   tfwApi(UE_FLUSH, msgptr);
   free(msgptr);
}

int tsSendErabRelReq
(
 unsigned char ueId,
 unsigned char numOfErabs,
 unsigned char *erabIdLst
)
{
   void* msgptr = NULL;

   printf("\n[Stub] Sending E-RAB Release Indication\n");

   msgptr = malloc(sizeof(FwErabRelInd_t));
   memset(msgptr, 0, sizeof(FwErabRelInd_t));

   ((FwErabRelInd_t*)msgptr)->ueId = ueId;
   ((FwErabRelInd_t*)msgptr)->numOfErabIds = numOfErabs;
   ((FwErabRelInd_t*)msgptr)->erabIdLst = malloc(numOfErabs * sizeof(U8));
   memcpy(((FwErabRelInd_t*)msgptr)->erabIdLst, erabIdLst, numOfErabs);

   tfwApi(ERAB_REL_IND, msgptr);
   free(((FwErabRelInd_t*)msgptr)->erabIdLst);
   free(msgptr);

   return 0;
}

int tsSendErabRelRsp
(
 unsigned char ueId
)
{
   void* msgptr = NULL;

   printf("\n[Stub] Sending E-RAB Release Indication\n");

   msgptr = malloc(sizeof(FwErabRelRsp_t));
   memset(msgptr, 0, sizeof(FwErabRelRsp_t));

   ((FwErabRelRsp_t*)msgptr)->ueId = erabRelCmdInfo[ueId - 1].ueId;
   ((FwErabRelRsp_t*)msgptr)->mmeUeS1apId = erabRelCmdInfo[ueId - 1].mmeUeS1apId;
   ((FwErabRelRsp_t*)msgptr)->enbUeS1apId = erabRelCmdInfo[ueId - 1].enbUeS1apId;
   ((FwErabRelRsp_t*)msgptr)->numOfErabIds = erabRelCmdInfo[ueId - 1].numOfErabIds;
   ((FwErabRelRsp_t*)msgptr)->erabIdLst = malloc(erabRelCmdInfo[ueId - 1].numOfErabIds * sizeof(U8));
   memcpy(((FwErabRelRsp_t*)msgptr)->erabIdLst, erabRelCmdInfo[ueId - 1].erabIdLst, erabRelCmdInfo[ueId - 1].numOfErabIds);

   tfwApi(ERAB_REL_RSP, msgptr);
   free(((FwErabRelRsp_t*)msgptr)->erabIdLst);
   free(msgptr);

   return 0;
}

void SyncFailureWithAgeLimit(unsigned char ueId)
{
   void* msgptr = NULL;

   printf("[Stub] Entering tsStepByStepAttachWithImsi(), ueId(%d)\n", ueId);

   /* Fill Attach request */
   msgptr = malloc(sizeof(ueAttachRequest_t));
   memset(msgptr, 0, sizeof(ueAttachRequest_t));
   ((ueAttachRequest_t*)msgptr)->ue_Id = ueId;
   ((ueAttachRequest_t*)msgptr)->mIdType = TFW_MID_TYPE_IMSI;
   ((ueAttachRequest_t*)msgptr)->epsAttachType = TFW_EPS_ATTACH_TYPE_EPS_ATTACH;
   ((ueAttachRequest_t*)msgptr)->useOldSecCtxt =
                                                TFW_CREATE_NEW_SECURITY_CONTEXT;

   /* Send Attach Request to TfwApp */
   printf("\n[Stub] Sending Attach Requst\n");
   tfwApi(UE_ATTACH_REQUEST, msgptr);
   free(msgptr);

   /* Wait For Auth request indication */
   if (TC_msg_recv(UE_AUTH_REQ_IND, 10) == SUCC)
   {
      printf("\n[Stub] UE Auth Request indication Completed\n");
   }
   else
   {
      printf("\n[Stub] UE Auth Request indication failed\n");
   }

   /* Fill Auth Response Indication with wrong Sqn */
   msgptr = malloc(sizeof(ueAuthResp_t));
   memset(msgptr, 0, sizeof(ueAuthResp_t));
   ((ueAuthResp_t*)msgptr)->ue_Id = ueId;
   ((ueAuthResp_t*)msgptr)->maxSqnRcvd.pres = TRUE;

   ((ueAuthResp_t*)msgptr)->maxSqnRcvd.sqn[4] = '5'-48;
   printf("\n[Stub] Sending Authentication Response\n");
   tfwApi(UE_AUTH_RESP, msgptr);
   free(msgptr);

   /* Wait For Auth request indication */
   if (TC_msg_recv(UE_AUTH_REQ_IND, 10) == SUCC)
   {
      printf("\n[Stub] UE Auth Request indication Completed\n");
   }
   else
   {
      printf("\n[Stub] UE Auth Request indication failed\n");
   }

   /* Fill Auth Response Indication */
   msgptr = malloc(sizeof(ueAuthResp_t));
   memset(msgptr, 0, sizeof(ueAuthResp_t));
   ((ueAuthResp_t*)msgptr)->ue_Id = ueId;
   ((ueAuthResp_t*)msgptr)->maxSqnRcvd.pres = FALSE;
   ((ueAuthResp_t*)msgptr)->sqnRcvd.pres = FALSE;

   printf("\n[Stub] Sending Authentication Response\n");
   tfwApi(UE_AUTH_RESP, msgptr);
   free(msgptr);

   /* Wait for Security Mode Command indication */
   if (TC_msg_recv(UE_SEC_MOD_CMD_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Security mode command indication\n");
   }
   else
   {
      printf("\n[Stub] security mode command indication failed\n");
   }

   /* Fill Security Mode complete Indication */
   msgptr = malloc(sizeof(ueSecModeComplete_t));
   memset(msgptr, 0, sizeof(ueSecModeComplete_t));
   ((ueAuthResp_t*)msgptr)->ue_Id = ueId;

   printf("\n[Stub] Sending Security Mode Complete\n");
   tfwApi(UE_SEC_MOD_COMPLETE,msgptr);
   free(msgptr);

   /* Wait for Initial Context Setup indication */
   if (TC_msg_recv(INT_CTX_SETUP_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Initial Context Setup indication\n");
   }
   else
   {
      printf("\n[Stub] Initial Context Setup indication failed\n");
   }

   /* Wait for Attach Accept indication */
   if (TC_msg_recv(UE_ATTACH_ACCEPT_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Attach Accept indication\n");
   }
   else
   {
      printf("\n[Stub] Attach Accept indication failed\n");
   }

   /* Fill Attach Complete Indication to TFW */
   msgptr = malloc(sizeof(ueAttachComplete_t));
   memset(msgptr, 0, sizeof(ueAttachComplete_t));
   ((ueAttachComplete_t*)msgptr)->ue_Id = ueId;

   printf("\n[Stub] Sending Attach Complete\n");
   tfwApi(UE_ATTACH_COMPLETE, msgptr);
   free(msgptr);
}

void SyncFailureWithDelta(unsigned char ueId)
{
   void* msgptr = NULL;

   printf("[Stub] Entering tsStepByStepAttachWithImsi(), ueId(%d)\n", ueId);

   /* Fill Attach request */
   msgptr = malloc(sizeof(ueAttachRequest_t));
   memset(msgptr, 0, sizeof(ueAttachRequest_t));
   ((ueAttachRequest_t*)msgptr)->ue_Id = ueId;
   ((ueAttachRequest_t*)msgptr)->mIdType = TFW_MID_TYPE_IMSI;
   ((ueAttachRequest_t*)msgptr)->epsAttachType = TFW_EPS_ATTACH_TYPE_EPS_ATTACH;
   ((ueAttachRequest_t*)msgptr)->useOldSecCtxt =
                                                TFW_CREATE_NEW_SECURITY_CONTEXT;

   /* Send Attach Request to TfwApp */
   printf("\n[Stub] Sending Attach Requst\n");
   tfwApi(UE_ATTACH_REQUEST, msgptr);
   free(msgptr);

   /* Wait For Auth request indication */
   if (TC_msg_recv(UE_AUTH_REQ_IND, 10) == SUCC)
   {
      printf("\n[Stub] UE Auth Request indication Completed\n");
   }
   else
   {
      printf("\n[Stub] UE Auth Request indication failed\n");
   }

   /* Fill Auth Response Indication with wrong Sqn */
   msgptr = malloc(sizeof(ueAuthResp_t));
   memset(msgptr, 0, sizeof(ueAuthResp_t));
   ((ueAuthResp_t*)msgptr)->ue_Id = ueId;
   ((ueAuthResp_t*)msgptr)->sqnRcvd.pres = TRUE;
   ((ueAuthResp_t*)msgptr)->maxSqnRcvd.pres = TRUE;
   ((ueAuthResp_t*)msgptr)->maxSqnRcvd.sqn[5] = 0xff;
   printf("\n[Stub] Sending Authentication Response\n");
   tfwApi(UE_AUTH_RESP, msgptr);
   free(msgptr);

   /* Wait For Auth request indication */
   if (TC_msg_recv(UE_AUTH_REQ_IND, 10) == SUCC)
   {
      printf("\n[Stub] UE Auth Request indication Completed\n");
   }
   else
   {
      printf("\n[Stub] UE Auth Request indication failed\n");
   }

   /* Fill Auth Response Indication */
   msgptr = malloc(sizeof(ueAuthResp_t));
   memset(msgptr, 0, sizeof(ueAuthResp_t));
   ((ueAuthResp_t*)msgptr)->ue_Id = ueId;
   ((ueAuthResp_t*)msgptr)->sqnRcvd.pres = FALSE;
   ((ueAuthResp_t*)msgptr)->maxSqnRcvd.pres = FALSE;

   printf("\n[Stub] Sending Authentication Response\n");
   tfwApi(UE_AUTH_RESP, msgptr);
   free(msgptr);

   /* Wait for Security Mode Command indication */
   if (TC_msg_recv(UE_SEC_MOD_CMD_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Security mode command indication\n");
   }
   else
   {
      printf("\n[Stub] security mode command indication failed\n");
   }

   /* Fill Security Mode complete Indication */
   msgptr = malloc(sizeof(ueSecModeComplete_t));
   memset(msgptr, 0, sizeof(ueSecModeComplete_t));
   ((ueAuthResp_t*)msgptr)->ue_Id = ueId;

   printf("\n[Stub] Sending Security Mode Complete\n");
   tfwApi(UE_SEC_MOD_COMPLETE,msgptr);
   free(msgptr);

   /* Wait for Initial Context Setup indication */
   if (TC_msg_recv(INT_CTX_SETUP_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Initial Context Setup indication\n");
   }
   else
   {
      printf("\n[Stub] Initial Context Setup indication failed\n");
   }

   /* Wait for Attach Accept indication */
   if (TC_msg_recv(UE_ATTACH_ACCEPT_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Attach Accept indication\n");
   }
   else
   {
      printf("\n[Stub] Attach Accept indication failed\n");
   }

   /* Fill Attach Complete Indication to TFW */
   msgptr = malloc(sizeof(ueAttachComplete_t));
   memset(msgptr, 0, sizeof(ueAttachComplete_t));
   ((ueAttachComplete_t*)msgptr)->ue_Id = ueId;

   printf("\n[Stub] Sending Attach Complete\n");
   tfwApi(UE_ATTACH_COMPLETE, msgptr);
   free(msgptr);
}
