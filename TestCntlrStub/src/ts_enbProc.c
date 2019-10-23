
/**********************************************************************

     Name:     S1SIM Test Controller Stub 
  
     Type:     C source file
  
     Desc:     This file contains the stub code for S1SIM Test Controller

     File:     ts_enbProc.c

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

void enbCfgWithS1SetupFail();
int  s1SetUpReq(int result);
void enbCfgWithWrongPlmn();
void enbCfgWithAllIEs();

int s1SetUpReq(int result)
{
   void* msgptr = NULL;

   printf("\n[Stub]: Sending S1 SETUP Request\n");
   tfwApi(ENB_S1_SETUP_REQ, msgptr);

   /* receive eNbApp config complete indication */
   if (TC_msg_recv(result, 10) == 0)
   {
      printf("\n[Stub]: RECEIVED S1-SETUP RESPONSE FROM TFWAPP\n");
      return 0;
   }
   else
   {
      printf("\n[Stub]: S1 SETUP Processing failed\n");
      return 1;
   }
}

void enbCfg()
{
   void* msgptr = NULL;

   /* send eNbApp config msg */
   msgptr = malloc(sizeof(FwNbConfigReq_t));
   memset(msgptr, 0, sizeof(FwNbConfigReq_t));
   ((FwNbConfigReq_t*)msgptr)->cellId_pr.pres = TRUE;
   ((FwNbConfigReq_t*)msgptr)->cellId_pr.cell_id = 10;

   /* Send EnodeB Config */
   printf("\n[Stub]: Sending eNodeB Config\n");
   tfwApi(ENB_CONFIG,msgptr);
   free(msgptr);

   /* Wait for eNbApp config complete indication */
   if (TC_msg_recv(ENB_CONFIG_CONFIRM,10) == 0)
   {
      printf("\n[Stub]: eNb Config Completed\n");
   }
   else
   {
      printf("\n[Stub]: eNb Config failed\n");
   }
}

void enbInactvTmrCfg(int inactvTmrVal, int maxRetries)
{
   void* msgptr = NULL;

   /* send eNbApp config msg */
   msgptr = malloc(sizeof(FwNbConfigReq_t));
   memset(msgptr, 0, sizeof(FwNbConfigReq_t));
   ((FwNbConfigReq_t*)msgptr)->inactvTmrVal_pr.pres = TRUE;
   ((FwNbConfigReq_t*)msgptr)->inactvTmrVal_pr.val = inactvTmrVal;
   ((FwNbConfigReq_t*)msgptr)->maxExpires_pr.pres = TRUE;
   ((FwNbConfigReq_t*)msgptr)->maxExpires_pr.val = maxRetries;

   /* Send EnodeB Config */
   printf("\n[Stub]: Sending eNodeB Inactivity Timer Config\n");
   tfwApi(ENB_INACTV_TMR_CFG, msgptr);
   free(msgptr);
}

void enbCfgWithS1Setup()
{
   enbCfg();
   s1SetUpReq(ENB_S1_SETUP_RESP);
}

void enbCfgAndS1SetupWithAllIEs()
{
   short int ret;

   /* sgavalkar */
   enbCfgWithAllIEs();
   ret = s1SetUpReq(ENB_S1_SETUP_RESP);
   if (ret == 0)
   {
      printf("[Stub]: S1 SETUP success \n");
   }
   else
   {
      printf("[Stub]: S1 SETUP failed \n");
   }
}

void enbCfgWithWrongPlmn()
{
   void* msgptr;

   /* Send eNbApp config msg */
   msgptr = malloc(sizeof(FwNbConfigReq_t));
   memset(msgptr, 0, sizeof(FwNbConfigReq_t));
   ((FwNbConfigReq_t*)msgptr)->cellId_pr.pres = TRUE;
   ((FwNbConfigReq_t*)msgptr)->cellId_pr.cell_id = 10;
   memcpy(((FwNbConfigReq_t*)msgptr)->plmnId_pr.plmn_id, "40502",
          strlen("40502"));
   ((FwNbConfigReq_t*)msgptr)->plmnId_pr.pres = TRUE;
   printf("\n[Stub]: Sending Enb Config.\n");
   tfwApi(ENB_CONFIG,msgptr);
   free(msgptr);

   /* Receive eNbApp config complete indication */
   if (TC_msg_recv(ENB_CONFIG_CONFIRM, 10) == 0)
   {
      printf("\n[Stub]: eNb Config Completed\n");
   }
   else
   {
      printf("\n[Stub]: eNb Config failed\n");
   }
}
 
void enbCfgWithWrongMmeIp()
{
   void* msgptr;
   /* send eNbApp config msg */
   msgptr = malloc(sizeof(FwNbConfigReq_t));
   memset(msgptr, 0, sizeof(FwNbConfigReq_t));

   ((FwNbConfigReq_t*)msgptr)->cellId_pr.pres = TRUE;
   ((FwNbConfigReq_t*)msgptr)->cellId_pr.cell_id = 10;

   ((FwNbConfigReq_t*)msgptr)->mmeAddr_pr.pres = TRUE;
   ((FwNbConfigReq_t*)msgptr)->mmeAddr_pr.mme_addr = 3232286811; /* 192.168.200.91 */

   printf("\n[Stub]: Sending S1 Enb Config.\n");
   tfwApi(ENB_CONFIG,msgptr);
   free(msgptr);

   /* receive eNbApp config complete indication */
   if (TC_msg_recv(ENB_CONFIG_CONFIRM, 10) == 0)
   {
      printf("\n[Stub]: eNb Config Completed\n");
   }
   else
   {
      printf("\n[Stub]: eNb Config failed\n");
   }
}

void enbCfgWithAllIEs()
{
   void* msgptr;
   FwSuppTAList *suppTAs;
   U8 mcc[5][3] = { {5,0,5}, {4,0,4}, {4,0,4}, {4,0,4}, {4,0,5} };
   U8 mnc[5][3] = { {0,2,0}, {4,5,0}, {4,6,0}, {4,7,0}, {8,4,7} };

   printf("\n[Stub]: Sending eNodeB Config with HPLMN, Broadcasted PLMNS, "
          "eNodeB type, CSG IDs\n");
   msgptr = malloc(sizeof(FwNbConfigReq_t));
   memset(msgptr, 0, sizeof(FwNbConfigReq_t));

#if 0
   ((FwNbConfigReq_t*)msgptr)->cellId_pr.pres = TRUE;
   ((FwNbConfigReq_t*)msgptr)->cellId_pr.cell_id = 10;

   ((FwNbConfigReq_t*)msgptr)->mmeAddr_pr.pres = TRUE;
   ((FwNbConfigReq_t*)msgptr)->mmeAddr_pr.mme_addr = 3232286811; /* 192.168.200.91 */
#endif

#if 0
   /* Home PLMN */
   memcpy(((FwNbConfigReq_t*)msgptr)->plmnId_pr.plmn_id, "40502",
          strlen("40502"));
   ((FwNbConfigReq_t*)msgptr)->plmnId_pr.pres = TRUE;
#endif

   /* Supported TAs */
   suppTAs = &((FwNbConfigReq_t*)msgptr)->suppTAs;
   suppTAs->pres = TRUE;
   suppTAs->numTAs = 5;

   /* TA 0 */
   suppTAs->suppTA[0].tac = 0x1000;
   suppTAs->suppTA[0].bPlmnList.numBPlmns = 0x01;
   suppTAs->suppTA[0].bPlmnList.bPlmn[0].numMncDigits = 2;
   memcpy(suppTAs->suppTA[0].bPlmnList.bPlmn[0].mcc, &mcc[0], 3);
   memcpy(suppTAs->suppTA[0].bPlmnList.bPlmn[0].mnc, &mnc[0], 2);

   /* TA 1 */
   suppTAs->suppTA[1].tac = 0x1001;
   suppTAs->suppTA[1].bPlmnList.numBPlmns = 0x01;
   suppTAs->suppTA[1].bPlmnList.bPlmn[0].numMncDigits = 2;
   memcpy(suppTAs->suppTA[1].bPlmnList.bPlmn[0].mcc, &mcc[1], 3);
   memcpy(suppTAs->suppTA[1].bPlmnList.bPlmn[0].mnc, &mnc[1], 2);

   /* TA 2 */
   suppTAs->suppTA[2].tac = 0x1002;
   suppTAs->suppTA[2].bPlmnList.numBPlmns = 0x01;
   suppTAs->suppTA[2].bPlmnList.bPlmn[0].numMncDigits = 2;
   memcpy(suppTAs->suppTA[2].bPlmnList.bPlmn[0].mcc, &mcc[2], 3);
   memcpy(suppTAs->suppTA[2].bPlmnList.bPlmn[0].mnc, &mnc[2], 2);

   /* TA 3 */
   suppTAs->suppTA[3].tac = 0x1003;
   suppTAs->suppTA[3].bPlmnList.numBPlmns = 0x01;
   suppTAs->suppTA[3].bPlmnList.bPlmn[0].numMncDigits = 2;
   memcpy(suppTAs->suppTA[3].bPlmnList.bPlmn[0].mcc, &mcc[3], 3);
   memcpy(suppTAs->suppTA[3].bPlmnList.bPlmn[0].mnc, &mnc[3], 2);

   /* TA 4 */
   suppTAs->suppTA[4].tac = 0x1004;
   suppTAs->suppTA[4].bPlmnList.numBPlmns = 0x01;
   suppTAs->suppTA[4].bPlmnList.bPlmn[0].numMncDigits = 3;
   memcpy(suppTAs->suppTA[4].bPlmnList.bPlmn[0].mcc, &mcc[4], 3);
   memcpy(suppTAs->suppTA[4].bPlmnList.bPlmn[0].mnc, &mnc[4], 3);

   /* eNodeB type: Macro eNodeB or Home eNodeB */
   ((FwNbConfigReq_t*)msgptr)->eNodeBType.pres = TRUE;
   ((FwNbConfigReq_t*)msgptr)->eNodeBType.val = TFW_ENODEB_TYPE_MACRO;

   /* CSG List */
   ((FwNbConfigReq_t*)msgptr)->csgIdList.pres = TRUE;
   /* Fill number of CSG IDs */
   ((FwNbConfigReq_t*)msgptr)->csgIdList.numCsgIds = 0x03;
   /* Fill CSG IDs (only lower 27 bits valid) */
   ((FwNbConfigReq_t*)msgptr)->csgIdList.csgId[0] = 0x0000001;
   ((FwNbConfigReq_t*)msgptr)->csgIdList.csgId[1] = 0x1234567;
   ((FwNbConfigReq_t*)msgptr)->csgIdList.csgId[2] = 0x7FFFFFF;

   printf("\n[Stub]: Sending eNodeB Config\n");
   tfwApi(ENB_CONFIG, msgptr);
   free(msgptr);

   /* Receive eNbApp config complete indication */
   if (TC_msg_recv(ENB_CONFIG_CONFIRM, 10) == 0)
   {
      printf("\n[Stub] eNodeB Config Completed\n");
   }
   else
   {
      printf("\n[Stub] eNodeB Config failed\n");
   }
}

void enbCfgWithS1SetupFail()
{
  enbCfgWithWrongPlmn();
  /* trigger the s1Setup Req */
  s1SetUpReq(ENB_S1_SETUP_RESP);

}

void enbCfgWithS1SetupTimeOut()
{
   static int s1Retry = 0;
   if(s1Retry == 0)
      enbCfgWithWrongMmeIp();

   s1SetUpReq(ENB_S1_SETUP_TIMEOUT_IND);
   s1Retry++;
   if (s1Retry < 3)
      enbCfgWithS1SetupTimeOut();
   else
      return;
}

void tsSendSctpAbort()
{
   void* msgptr = NULL;

   msgptr = malloc(sizeof(FwSctpAbortReq_t));
   memset(msgptr, 0, sizeof(FwSctpAbortReq_t));

   printf("\n[Stub]: Sending SCTP ABORT from Stub\n");

   /* Fill user defined cause/reason for Abort */
   ((FwSctpAbortReq_t*)msgptr)->cause = TFW_ERR_USER_INITD_SCTP_ABORT;

   tfwApi(SCTP_ABORT_REQ, msgptr);
   free(msgptr);

   return;
}

void tsSendSctpShutdown()
{
   void* msgptr = NULL;

   /* No parameters to be filled */

   printf("\n[Stub]: Sending SCTP SHUTDOWN from Stub\n");
   tfwApi(SCTP_SHUTDOWN_REQ, msgptr);

   /* SHUTDOWN_ACK will be received at SCTP & 
      SHUTDOWN_COMPLETE will be sent by SCTP to MME.
      Indication to Stub not required */

   return;
}
