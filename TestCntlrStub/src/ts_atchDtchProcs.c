
/**********************************************************************

     Name:     S1SIM Test Controller Stub 
  
     Type:     C source file
  
     Desc:     This file contains the stub code for S1SIM Test Controller

     File:     ts_atchDtchProcs.c

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
#include "ts_utls.x"

extern int nwInitDetach_ueid;

void testAttachAndUlData(unsigned char ueId)
{
   tsSendAttachRequest(ueId);
   tsStartUlData(ueId);
}

void testAttachAndDlData(unsigned char ueId)
{
   tsSendAttachRequest(ueId);
   tsStartDlData(ueId);
}

void testDetachiWithCauseSwitchOff(unsigned char ueId)
{
   tsSendAttachRequest(ueId);

   printf("\n-----------------------------------------------\n"\
         "Sending Detach Request with Cause Ue Switch Off\n"\
         "-----------------------------------------------\n");
   tsSendDetachRequest(ueId, UE_SWITCHOFF_DETACH, UE_IN_CONNECTED_MODE);
}

void testDetachiWithCauseNormal(unsigned char ueId)
{
   tsSendAttachRequest(ueId);
   sleep(10);

   printf("\n--------------------------------------------------\n"\
         "Sending Detach Request with Cause Ue Normal Detach\n"\
         "--------------------------------------------------\n");
   tsSendDetachRequest(ueId, UE_NORMAL_DETACH, UE_IN_CONNECTED_MODE);
}

void testUeCntxtRelRequest(unsigned char ueId)
{
   tsSendAttachRequest(ueId);

   sleep(5);
   printf("\n--------------------------------\n"\
         "Sending UE Context Release Request\n"\
         "----------------------------------\n");
   tsSendUeCntxtReleaseRequest(ueId, 18);

   sleep(5);

   tsSendDetachRequest(ueId, UE_NORMAL_DETACH, UE_IN_CONNECTED_MODE);
}

void testUeRadCapModReq(unsigned char ueId)
{
   unsigned char UeRadCapRRCMsg[16] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F};
   Bool SndS1AP = TRUE;

   tsSendAttachRequest(ueId);
   sleep(10);
   printf("\n--------------------------------\n"\
         "Sending UE Radio Cap update Req\n"\
         "----------------------------------\n");


   /*tsSendUeRadCapUpdReq options */
   /*UeRadCapRRCMsg = NULL; len = 0; SndS1AP = TRUE  - UE Cap Info ind will be sent with default RRC msg in ueCfg.txt*/
   tsSendUeRadCapUpdReq(ueId, NULL, 0, SndS1AP);  

   /*UeRadCapRRCMsg = Valid; len = valid; SndS1AP = TRUE - UE Cap Info ind will be sent with new RRC msg */
   sleep(2);
   tsSendUeRadCapUpdReq(ueId, UeRadCapRRCMsg, 16, SndS1AP);

   /*UeRadCapRRCMsg = NULL; len = 0; SndS1AP = FALSE  - UE Cap Info RRC msg is reset to default, no S1AP msg Tx*/
   sleep(2);
   tsSendUeRadCapUpdReq(ueId, NULL, 0, FALSE);

   /*UeRadCapRRCMsg = NULL; len = 0; SndS1AP = TRUE  - UE Cap Info ind will be sent with default RRC msg in ueCfg.txt*/
   sleep(2);
   tsSendUeRadCapUpdReq(ueId, NULL, 0, SndS1AP);
   sleep(2);
   tsSendDetachRequest(ueId, UE_SWITCHOFF_DETACH, UE_IN_CONNECTED_MODE);
}

void testUePdnConnReq(unsigned char ueId)
{
   U8 apn[MAX_LEN_ACCESS_PTNAME] = "pdngw2"; 
   uepdnConReq_t pdnConReq;

   memset(&pdnConReq,0,sizeof(uepdnConReq_t));

   /*tsSendAttachRequest(ueId);
   sleep(2);*/
   /* fill the pdn-con req */

   pdnConReq.ue_Id    = ueId;     
   pdnConReq.reqType = 1;     
   pdnConReq.pdnType_pr.pres = 1;      
   pdnConReq.pdnType_pr.pdn_type = 1; /* IPV4 */     
   pdnConReq.pdnAPN_pr.pres    = 0;     
   pdnConReq.pdnAPN_pr.len    = (U8)strlen((S8*)apn);
   pdnConReq.pdnAPN_pr.pres = 1;     
   memcpy(pdnConReq.pdnAPN_pr.pdn_apn,apn,pdnConReq.pdnAPN_pr.len);    

   tsSendPdnConnReq(&pdnConReq);
   /*sleep(2);
   tsSendDetachRequest(ueId, UE_SWITCHOFF_DETACH, UE_IN_CONNECTED_MODE);
   sleep(2);*/
}

void testUePdnConnReqAndData(unsigned char ueId)
{
   U8 apn[MAX_LEN_ACCESS_PTNAME] = "pdngw1"; 
   uepdnConReq_t pdnConReq;

   memset(&pdnConReq,0,sizeof(uepdnConReq_t));

   /*tsSendAttachRequest(ueId);
   sleep(2);*/

/* fill the pdn-con req */
   pdnConReq.ue_Id = ueId;     
   pdnConReq.reqType = 1;     
   pdnConReq.pdnType_pr.pres = 1;      
   pdnConReq.pdnType_pr.pdn_type = 1; /* IPV4 */     
   pdnConReq.pdnAPN_pr.pres    = 0;     
   pdnConReq.pdnAPN_pr.len    = (U8)strlen((S8*)apn);
   pdnConReq.pdnAPN_pr.pres = 1;     
   memcpy(pdnConReq.pdnAPN_pr.pdn_apn, apn, pdnConReq.pdnAPN_pr.len);    

   tsSendPdnConnReq(&pdnConReq);
   tsStartUlData(ueId);
   sleep(20);
   /*tsSendDetachRequest(ueId, UE_SWITCHOFF_DETACH, UE_IN_CONNECTED_MODE);
   sleep(2);*/
}

void testUePdnConnRej(unsigned char ueId)
{
   U8 apn[MAX_LEN_ACCESS_PTNAME] = "gwpdn1"; /* configure wrong apn */ 
   uepdnConReq_t pdnConReq;

   memset(&pdnConReq,0,sizeof(uepdnConReq_t));

   /*tsSendAttachRequest(ueId);
   sleep(2);*/

   pdnConReq.ue_Id    = ueId;     
   pdnConReq.reqType = 1;     
   pdnConReq.pdnType_pr.pres = 1;      
   pdnConReq.pdnType_pr.pdn_type = 1; /* IPV4 */     
   pdnConReq.pdnAPN_pr.pres = 0;     
   pdnConReq.pdnAPN_pr.len = (U8)strlen((S8*)apn);
   pdnConReq.pdnAPN_pr.pres = 1;     
   memcpy(pdnConReq.pdnAPN_pr.pdn_apn, apn, pdnConReq.pdnAPN_pr.len);    

   tsSendPdnConnReq(&pdnConReq);
   /*sleep(2);
   tsSendDetachRequest(ueId, UE_SWITCHOFF_DETACH, UE_IN_CONNECTED_MODE);*/
}

int testNwInitDetach(unsigned char ueId)
{
   tsSendAttachRequest(ueId);

   sleep(5);
   printf("\n--------------------------------\n"\
         "Waiting for Network initiated detach Request\n"\
         "----------------------------------\n");

   /* Wait for Service Reject Indication */
   if (TC_msg_recv(UE_NW_INIT_DETACH_REQUEST, 10) == SUCC)
   {
      printf("\nReceived Network Initiated Detach\n");
   }
   else
   {
      printf("Failed to recieve Network initiated detach\n");
   }
   sleep(5);
   
   printf("\n--------------------------------\n"\
         "Sending Detach Accept\n"\
         "----------------------------------\n");
   tsSendDetachAccept(nwInitDetach_ueid);

   if(TC_msg_recv(UE_CTX_REL_IND, 10) == SUCC)
   {
      printf("\nReceived UE Context Release indication\n");
   }
   return 0;
}

void testErrIndWithIvalidUeS1apIds(unsigned char ueId)
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

   /* send eNbApp config msg */
   msgptr = malloc(sizeof(fwNbErrIndMsg_t));
   memset(msgptr, 0, sizeof(fwNbErrIndMsg_t));

   ((fwNbErrIndMsg_t*)msgptr)->isUeAssoc = TRUE;
   ((fwNbErrIndMsg_t*)msgptr)->ue_Id = ueId;

   ((fwNbErrIndMsg_t*)msgptr)->cause.pres = TRUE;
   ((fwNbErrIndMsg_t*)msgptr)->cause.causeType = 0; /* RADIO network */
   ((fwNbErrIndMsg_t*)msgptr)->cause.causeVal =  15; /* unknown pair ue-s1ap-id */
   ((fwNbErrIndMsg_t*)msgptr)->criticalityDiag.pres =  FALSE;

   printf("\n[STUB]: Sending Err Indication Message.\n");
   tsSendErrIndMsg(msgptr);
   sleep(5);
   if(TC_msg_recv(UE_CTX_REL_IND, 10) == SUCC)
   {  
      printf("\nReceived UE Context Release indication\n");
   }  
   free(msgptr);

}

int testUeInitiatedDedBerReq(unsigned char ueId)
{
   void* msgptr = NULL;
   ue_Esm_Tft *tft = NULL;
   tsStepByStepAttachWithImsi(ueId);
   printf("[Stub] Entering tsStepByStepAttachWithImsi(), ueId(%d)\n", ueId);

   /* Fill Attach request */
   msgptr = malloc(sizeof(ueBearerAllocReq_t));
   memset(msgptr, 0, sizeof(ueBearerAllocReq_t));
   ((ueBearerAllocReq_t*)msgptr)->ue_Id = ueId;
   ((ueBearerAllocReq_t*)msgptr)->lnkEpsBearerId = 5;
   ((ueBearerAllocReq_t*)msgptr)->bearerId = 0;

   /* EPS quality of service */
   ((ueBearerAllocReq_t*)msgptr)->qos.pres = 1;
   ((ueBearerAllocReq_t*)msgptr)->qos.lenQosCont = 5;
   ((ueBearerAllocReq_t*)msgptr)->qos.qci = 0; 
   ((ueBearerAllocReq_t*)msgptr)->qos.maxBitRateUL = 159;
   ((ueBearerAllocReq_t*)msgptr)->qos.maxBitRateDL = 159;
   ((ueBearerAllocReq_t*)msgptr)->qos.guaraBitRateUL = 159;
   ((ueBearerAllocReq_t*)msgptr)->qos.guaraBitRateDL = 159;


   /* TFT */
   tft = &(((ueBearerAllocReq_t*)msgptr)->tft);
   tft->pres = 1;
   tft->opCode = 1; /* new TFT */
   tft->eBit = 0x00;
   tft->noOfPfs = 1;
   tft->noOfParams = 0;

   tft->pfList = malloc(sizeof(ue_Esm_Tft_Pf));
   memset(tft->pfList, 0, sizeof(ue_Esm_Tft_Pf));

   tft->pfList[0].pres = 1;
   tft->pfList[0].id = 1;
   tft->pfList[0].preced = 1;
  
   tft->pfList[0].ipv4.pres = 1;
   memcpy(tft->pfList[0].ipv4.ip4,
     UeIpInfoLst[ueId-1].UeIpAdrLst[0], 4);

   tft->pfList[0].ipv4Mask = 4294967295 ; /*255.255.255.255 */ 
   tft->pfList[0].ipv6.pres = 0;

   tft->pfList[0].protId.pres = 1;
   tft->pfList[0].protId.protType = 1;


   tft->pfList[0].localPort.pres = 1;
   tft->pfList[0].localPort.port = 1235;

   tft->pfList[0].remotePort.pres = 1;
   tft->pfList[0].remotePort.port = 0x2710;

   tft->pfList[0].locPortRange.pres = 1;
   tft->pfList[0].locPortRange.rangeLow = 1235;
   tft->pfList[0].locPortRange.rangeHigh = 1235 + 20;

   tft->pfList[0].remPortRange.pres = 1; 
   tft->pfList[0].remPortRange.rangeLow = 0x2710 + 1;
   tft->pfList[0].remPortRange.rangeHigh = 0x2710 + 5;

   tft->pfList[0].secParam.pres = 0;

   tft->pfList[0].tos.pres = 0;

   tft->pfList[0].flowLabel.pres = 0;
   /* Send Attach Request to TfwApp */
   printf("\n[Stub] Sending Ue Bearer Resource allocation request, ueId(%d)\n", ueId);
   tfwApi(UE_BER_RES_ALLOC_REQ, msgptr);
   free(msgptr);

   /* Wait For Auth request indication */
   if (TC_msg_recv(UE_ACT_DED_BER_REQ, 10) == SUCC)
   {
      printf("\n[Stub]Received Activate Dedicated bearer Request ueId(%d)\n", ueId);
   }
   else
   {
      printf("\n[Stub]Received Activate Dedicated bearer Request ueId(%d)\n", ueId);
   }
   /* Fill Attach request */
   msgptr = malloc(sizeof(UeActDedBearCtxtAcc_t));
   memset(msgptr, 0, sizeof(UeActDedBearCtxtAcc_t));
   ((UeActDedBearCtxtAcc_t*)msgptr)->ue_Id = ueId;
   ((UeActDedBearCtxtAcc_t*)msgptr)->bearerId =\
   UeDedBerLst[ueId].dedBerIdLst[0]; 
   /* Send Attach Request to TfwApp */
   printf("\n[Stub] Sending Ue Actv Dedicated Bearer Acc, ueId(%d)\n", ueId);
   tfwApi(UE_ACT_DED_BER_ACC, msgptr);
   free(msgptr);
   sleep(5);
   
   return 0;
}

int testActvDedBerRejWithIvalidEpsBerId(unsigned char ueId)
{
   void* msgptr = NULL;
   ue_Esm_Tft *tft = NULL;
   tsStepByStepAttachWithImsi(ueId);
   printf("[Stub] Entering tsStepByStepAttachWithImsi(), ueId(%d)\n", ueId);

   /* Fill Attach request */
   msgptr = malloc(sizeof(ueBearerAllocReq_t));
   memset(msgptr, 0, sizeof(ueBearerAllocReq_t));
   ((ueBearerAllocReq_t*)msgptr)->ue_Id = ueId;
   ((ueBearerAllocReq_t*)msgptr)->lnkEpsBearerId = 5;
   ((ueBearerAllocReq_t*)msgptr)->bearerId = 0;

   /* EPS quality of service */
   ((ueBearerAllocReq_t*)msgptr)->qos.pres = 1;
   ((ueBearerAllocReq_t*)msgptr)->qos.lenQosCont = 5;
   ((ueBearerAllocReq_t*)msgptr)->qos.qci = 0; 
   ((ueBearerAllocReq_t*)msgptr)->qos.maxBitRateUL = 159;
   ((ueBearerAllocReq_t*)msgptr)->qos.maxBitRateDL = 159;
   ((ueBearerAllocReq_t*)msgptr)->qos.guaraBitRateUL = 159;
   ((ueBearerAllocReq_t*)msgptr)->qos.guaraBitRateDL = 159;


   /* TFT */
   tft = &(((ueBearerAllocReq_t*)msgptr)->tft);
   tft->pres = 1;
   tft->opCode = 1; /* new TFT */
   tft->eBit = 0x00;
   tft->noOfPfs = 1;
   tft->noOfParams = 0;

   tft->pfList = malloc(sizeof(ue_Esm_Tft_Pf));
   memset(tft->pfList, 0, sizeof(ue_Esm_Tft_Pf));

   tft->pfList[0].pres = 1;
   tft->pfList[0].id = 1;
   tft->pfList[0].preced = 1;
  
   tft->pfList[0].ipv4.pres = 1;
   memcpy(tft->pfList[0].ipv4.ip4,
     UeIpInfoLst[ueId-1].UeIpAdrLst[0], 4);

   tft->pfList[0].ipv4Mask = 4294967295 ; /*255.255.255.255 */ 
   tft->pfList[0].ipv6.pres = 0;

   tft->pfList[0].protId.pres = 1;
   tft->pfList[0].protId.protType = 1;


   tft->pfList[0].localPort.pres = 1;
   tft->pfList[0].localPort.port = 1235;

   tft->pfList[0].remotePort.pres = 1;
   tft->pfList[0].remotePort.port = 0x2710;

   tft->pfList[0].locPortRange.pres = 1;
   tft->pfList[0].locPortRange.rangeLow = 1235;
   tft->pfList[0].locPortRange.rangeHigh = 1235 + 20;

   tft->pfList[0].remPortRange.pres = 1; 
   tft->pfList[0].remPortRange.rangeLow = 0x2710 + 1;
   tft->pfList[0].remPortRange.rangeHigh = 0x2710 + 5;

   tft->pfList[0].secParam.pres = 0;

   tft->pfList[0].tos.pres = 0;

   tft->pfList[0].flowLabel.pres = 0;
   printf("\n[Stub] Sending Ue Bearer Resource allocation request, ueId(%d)\n", ueId);
   tfwApi(UE_BER_RES_ALLOC_REQ, msgptr);
   free(msgptr);

   if (TC_msg_recv(UE_ACT_DED_BER_REQ, 10) == SUCC)
   {
      printf("\n[Stub]Received Activate Dedicated bearer Request ueId(%d)\n", ueId);
   }
   else
   {
      printf("\n[Stub]Received Activate Dedicated bearer Request ueId(%d)\n", ueId);
   }
   msgptr = malloc(sizeof(UeActDedBearCtxtRej_t));
   memset(msgptr, 0, sizeof(UeActDedBearCtxtRej_t));
   ((UeActDedBearCtxtRej_t*)msgptr)->ue_Id = ueId;
   ((UeActDedBearCtxtRej_t*)msgptr)->bearerId =\
   UeDedBerLst[ueId].dedBerIdLst[0]; 
   ((UeActDedBearCtxtRej_t*)msgptr)->esmCause = 43; /* invalid eps bearer Id */
   /* Send Attach Request to TfwApp */
   printf("\n[Stub] Sending Ue Actv Dedicated Bearer Rej, ueId(%d)\n", ueId);
   tfwApi(UE_ACT_DED_BER_REJ, msgptr);
   free(msgptr);
   sleep(5);
   
   return 0;
}
void testInitialContextSetupFailure(unsigned char ueId)
{
   void* msgptr = NULL;

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

   /* Fill Initial Context Setup Failure*/
   msgptr = malloc(sizeof(ueInitCtxtSetupFail));
   memset(msgptr, 0, sizeof(ueInitCtxtSetupFail));
   ((ueInitCtxtSetupFail*)msgptr)->ue_Id = ueId;
   ((ueInitCtxtSetupFail*)msgptr)->flag = 1;
   /* Cause Type */
   ((ueInitCtxtSetupFail*)msgptr)->causeType = TFW_CAUSE_RADIONW;
   /* Cause Value */
   ((ueInitCtxtSetupFail*)msgptr)->causeVal = TfwCauseRadioNwsuccessful_handoverEnum;

   /* Send Initial Context Setup Failure to TfwApp */
   printf("\n[Stub] Setting Initial Context Setup Failure flag and cause, ueId(%d)\n", ueId);
   tfwApi(UE_SET_INIT_CTXT_SETUP_FAIL, msgptr);
   free(msgptr);
   sleep(1);

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

   if(TC_msg_recv(UE_CTX_REL_IND, 10) == SUCC)
   {
      printf("\nReceived UE Context Release indication\n");
   }
   
   /* Reset Initial Context Setup Failure*/
   msgptr = malloc(sizeof(ueInitCtxtSetupFail));
   memset(msgptr, 0, sizeof(ueInitCtxtSetupFail));
   ((ueInitCtxtSetupFail*)msgptr)->ue_Id = ueId;
   ((ueInitCtxtSetupFail*)msgptr)->flag = 0;
   /* Cause Type */
   ((ueInitCtxtSetupFail*)msgptr)->causeType = TFW_CAUSE_RADIONW;
   /* Cause Value */
   ((ueInitCtxtSetupFail*)msgptr)->causeVal = TfwCauseRadioNwsuccessful_handoverEnum;

   /* Send Initial Context Setup Failure to TfwApp */
   printf("\n[Stub] Setting Initial Context Setup Failure flag and cause, ueId(%d)\n", ueId);
   tfwApi(UE_SET_INIT_CTXT_SETUP_FAIL, msgptr);
   free(msgptr);
   sleep(1);
}

void testNasNonDelivery(unsigned char ueId)
{
   void* msgptr = NULL;

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

   /* Fill Nas Non Delivery ueId */
   msgptr = malloc(sizeof(UeNasNonDel));
   memset(msgptr, 0, sizeof(UeNasNonDel));
   ((UeNasNonDel*)msgptr)->ue_Id = ueId;
   ((UeNasNonDel*)msgptr)->flag = 1;
   /* Cause Type */
   ((UeNasNonDel*)msgptr)->causeType = TFW_CAUSE_RADIONW;
   /* Cause Value */
   ((UeNasNonDel*)msgptr)->causeVal = TfwCauseRadioNwsuccessful_handoverEnum;

   /* Send Nas Non Delivery to TfwApp */
   printf("\n[Stub] Setting Nas NonDelivery flag and cause, ueId(%d)\n", ueId);
   tfwApi(UE_SET_NAS_NON_DELIVERY, msgptr);
   free(msgptr);
   sleep(1);

   /* Fill Auth Response Indication */
   msgptr = malloc(sizeof(ueAuthResp_t));
   memset(msgptr, 0, sizeof(ueAuthResp_t));
   ((ueAuthResp_t*)msgptr)->ue_Id = ueId;
   printf("\n[Stub] Sending Authentication Response\n");
   tfwApi(UE_AUTH_RESP, msgptr);
   free(msgptr);

   /* Wait for Security Mode Command indication */
   if (TC_msg_recv(UE_NAS_NON_DELIVERY_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Nas Non Delivery indication\n");
   }
   else
   {
      printf("\n[Stub] NAS Non Delivery Indiaction failed\n");
   }

   if(TC_msg_recv(UE_CTX_REL_IND, 10) == SUCC)
   {
      printf("\nReceived UE Context Release indication\n");
   }
   
   /* Reset Nas Non Delivery ueId */
   msgptr = malloc(sizeof(UeNasNonDel));
   memset(msgptr, 0, sizeof(UeNasNonDel));
   ((UeNasNonDel*)msgptr)->ue_Id = ueId;
   ((UeNasNonDel*)msgptr)->flag = 0;
   /* Cause Type */
   ((UeNasNonDel*)msgptr)->causeType = TFW_CAUSE_RADIONW;
   /* Cause Value */
   ((UeNasNonDel*)msgptr)->causeVal = TfwCauseRadioNwsuccessful_handoverEnum;

   /* Send Nas Non Delivery to TfwApp */
   printf("\n[Stub] Reset Nas NonDelivery flag, ueId(%d)\n", ueId);
   tfwApi(UE_SET_NAS_NON_DELIVERY, msgptr);
   free(msgptr);
   sleep(1);
}

void testInitialContextSetupDrop(unsigned char ueId)
{
   void* msgptr = NULL;

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

   /* Fill Initial Context Setup Failure*/
   msgptr = malloc(sizeof(UeDropInitCtxtSetup));
   memset(msgptr, 0, sizeof(UeDropInitCtxtSetup));
   ((UeDropInitCtxtSetup*)msgptr)->ue_Id = ueId;
   ((UeDropInitCtxtSetup*)msgptr)->flag = 1;
   /*Timer to delete the ue context locally */
   ((UeDropInitCtxtSetup*)msgptr)->tmrVal = 1000;

   /* Send Initial Context Setup Failure to TfwApp */
   printf("\n[Stub] Setting Initial Context Setup Drop, ueId(%d)\n", ueId);
   tfwApi(UE_SET_DROP_ICS, msgptr);
   free(msgptr);
   sleep(1);

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

   /* Wait for Initial Context Setup Dropped indication */
   if (TC_msg_recv(UE_ICS_DROPD_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Initial Context Setup Dropped Indication\n");
   }
   else
   {
      printf("\n[Stub] Initial Context Setup indication failed\n");
   }
   sleep(2);
}

void testInitialContextSetupDelayRsp(unsigned char ueId)
{
   void* msgptr = NULL;

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

   /* Fill Initial Context Setup Delay*/
   msgptr = malloc(sizeof(UeDelayInitCtxtSetupRsp));
   memset(msgptr, 0, sizeof(UeDelayInitCtxtSetupRsp));
   ((UeDelayInitCtxtSetupRsp*)msgptr)->ue_Id = ueId;
   ((UeDelayInitCtxtSetupRsp*)msgptr)->flag = 1;
   /*Timer to delete the ue context locally */
   ((UeDelayInitCtxtSetupRsp*)msgptr)->tmrVal = 2000;

   /* Send Initial Context Setup Failure to TfwApp */
   printf("\n[Stub] Setting Initial Context Setup Delay, ueId(%d)\n", ueId);
   tfwApi(UE_SET_DELAY_ICS_RSP, msgptr);
   free(msgptr);
   sleep(1);

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

   sleep(4);

}
void testInitialContextSetupUeCtxtRelReq(unsigned char ueId)
{
   void* msgptr = NULL;

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

   /* Fill Initial Context Setup Failure*/
   msgptr = malloc(sizeof(UeSetCtxtRelForInitCtxtSetup));
   memset(msgptr, 0, sizeof(UeSetCtxtRelForInitCtxtSetup));
   ((UeSetCtxtRelForInitCtxtSetup*)msgptr)->ue_Id = ueId;
   ((UeSetCtxtRelForInitCtxtSetup*)msgptr)->flag = 1;
   /* Cause Type */
   ((UeSetCtxtRelForInitCtxtSetup*)msgptr)->causeType = TFW_CAUSE_RADIONW;
   /* Cause Value */
   ((UeSetCtxtRelForInitCtxtSetup*)msgptr)->causeVal = TfwCauseRadioNwsuccessful_handoverEnum;

   /* Send Initial Context Setup Failure to TfwApp */
   printf("\n[Stub] Setting Initial Context Setup drop and sending inital context request to ue , ueId(%d)\n", ueId);
   tfwApi(UE_SET_CTXT_REL_REQ_FOR_ICS, msgptr);
   free(msgptr);
   sleep(1);

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

   if(TC_msg_recv(UE_CTX_REL_IND, 10) == SUCC)
   {
      printf("\nReceived UE Context Release indication\n");
   }
   sleep(2);
}
