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
#include <pthread.h>

#include "fw_api_int.x"
#include "trfgen.x"
#include "ts_utls.x"
#include "ts_timer_queue.h"
#include "ts_timer_thread.h"

void tsSendSctpShutdown();
extern pthread_mutex_t timer_queue_mutex;

typedef struct _ueTAUInfo{
	U16 T3412;
	U8 nSuccTAU;
}ueTAUInfo;

ueTAUInfo ueTAU[32];

U8 maxTAUprocs; 
U8 numTestUE;
U8 nSuccDet;

U8 currQIndx = 0;

int TC_recv(void);
void tsSendPeriodicTau(unsigned char ueId);
void tsSendDetach(unsigned char ueId);

void tsAttach_tau_detach(U8 nUE, U8 nTAUReq)
{
   U8 ueIndx;

   void* msgptr =  NULL;

   maxTAUprocs = nTAUReq;
   numTestUE = nUE;
   for (ueIndx = 1; ueIndx <= nUE; ueIndx++)
   {
      printf("[Stub] Entering tsCompleteAttach(), ueId(%d)\n", ueIndx);

      /* send Attach request(END_TO_END) */
      msgptr = malloc(sizeof(ueAttachRequest_t));
      memset(msgptr, 0, sizeof(ueAttachRequest_t));
      ((ueAttachRequest_t*)msgptr)->ue_Id = ueIndx;
      ((ueAttachRequest_t*)msgptr)->mIdType = TFW_MID_TYPE_IMSI;
      ((ueAttachRequest_t*)msgptr)->epsAttachType = TFW_EPS_ATTACH_TYPE_EPS_ATTACH;
      ((ueAttachRequest_t*)msgptr)->useOldSecCtxt = TFW_CREATE_NEW_SECURITY_CONTEXT;

      printf("\n[Stub] Sending End-to-End Attach Request, ueId(%d)\n", ueIndx);
      tfwApi(UE_END_TO_END_ATTACH_REQUEST, msgptr);
      free(msgptr);
   }
   /* Wait for Attach Accept indication */
   while(1)
      TC_recv();
}

int TC_recv()
{
   /* Read from message queue untill msg Id msg is received */
   Bool msg_recvd = FALSE;
   MsgBuf msgptr;
   int retVal = 0;
   timer_queue_msg tqm;

   printf("[Stub] %s:%s():%d: Entering\n", __FILE__, __FUNCTION__, __LINE__);

   while (!msg_recvd)
   {
      if (msgrcv(msgQid, (void *)&msgptr, sizeof(MsgBuf), 0, 0) == -1)
      {
         printf("[Stub] msgcrv failed with error");
         return 0;
      }

      printf("\n[Stub] Received (msgptr.msgType=%ld)\n",
            msgptr.msgType);

      if (msgptr.msgType == UE_ATTACH_ACCEPT_IND)
      {
         printf("\n[Stub] Received msgptr.mtype = %ld\n", msgptr.msgType);
         msg_recvd = TRUE;
         retVal = FAIL;
      }
      if (msgptr.msgType == UE_TAU_ACCEPT_IND)
      {
         printf("\n[Stub] Received msgptr.mtype = %ld\n", msgptr.msgType);
         msg_recvd = TRUE;
         retVal = FAIL;
      }
      if (msgptr.msgType == UE_DETACH_ACCEPT_IND)
      {
         printf("\n[Stub] Received msgptr.mtype = %ld\n", msgptr.msgType);
         msg_recvd = TRUE;
         retVal = FAIL;
      }
      if (msgptr.msgType == UE_CTX_REL_IND)
      {
         printf("\n[Stub] Received msgptr.mtype = %ld\n", msgptr.msgType);
         msg_recvd = TRUE;
         retVal = FAIL;
      }
   }

   if(msgptr.msgType == UE_ATTACH_ACCEPT_IND)
   {
      ueAttachAccept_t TC_AttachAccept;
      memcpy(&TC_AttachAccept, &msgptr.msg, sizeof(ueAttachAccept_t));
      unsigned char  ueId = TC_AttachAccept.ue_Id;
      memcpy(UeIpInfoLst[ueId-1].UeIpAdrLst[UeIpInfoLst[ueId-1].noIfAssinedIps],
            TC_AttachAccept.esmInfo.pAddr.addrInfo, 4);
      ueTAU[ueId - 1].T3412 = TC_AttachAccept.t3412;
      ueTAU[ueId - 1].nSuccTAU = 0;
      printf("[Stub] T3412 = %d\n", ueTAU[ueId - 1].T3412);

      /* Sending UE Context Release Reuest */
      /*void *ueCtxRelReq =  NULL;
      ueCtxRelReq = malloc(sizeof(ueCntxtRelReq_t));
      memset(ueCtxRelReq, 0, sizeof(ueCntxtRelReq_t));
      ((ueCntxtRelReq_t*)ueCtxRelReq)->ue_Id = ueId;

      ((ueCntxtRelReq_t*)ueCtxRelReq)->cause = 18;
      printf("\n[Stub] Sending Ue Context Release request, ueId(%d)\n", ueId); 
      tfwApi(UE_CNTXT_REL_REQUEST, ueCtxRelReq);
      free(ueCtxRelReq);
      sleep(1);*/

      /* Insert timer to Timer Queue */
      printf("main thread: got the timer queue lock [%lu]\n", time(NULL));
      pthread_mutex_lock(&timer_queue_mutex);
      tqm.ueId = ueId;
      tqm.callbk = &tsSendPeriodicTau;
      time(&(tqm.timer));
      tqm.timer += (time_t)(ueTAU[ueId - 1].T3412);
      /*tqm.timer += (time_t)(20);*/
      if (tq_add_msg(&tqm, currQIndx++) == -1)
         printf("Adding timer to Q failed\n");
      if (currQIndx >= 100) currQIndx = 0;
      pthread_mutex_unlock(&timer_queue_mutex);
      printf("main thread: released the timer queue lock [%lu]\n", time(NULL));
   }

   return retVal;
} /* TC_msg_recv */

void tsSendPeriodicTau(unsigned char ueId)
{
   void* msgptr = NULL;
   timer_queue_msg tqm;

   if(ueTAU[ueId - 1].nSuccTAU >= maxTAUprocs){
      tsSendDetach(ueId);
      return;
   }
   printf("-------------------------------------"\
         "Sending Tracking area update "\
         "-------------------------------------\n");

   msgptr = malloc(sizeof(ueTauReq_t));
   memset(msgptr, 0, sizeof(ueTauReq_t));
   ((ueTauReq_t*)msgptr)->ue_Id = ueId;
   ((ueTauReq_t*)msgptr)->type = TFW_PERIODIC_UPDATING;
   ((ueTauReq_t*)msgptr)->Actv_flag = FALSE;

   printf("\n[Stub] Sending Tracking Area Update, ueId(%d)\n", ueId);
   tfwApi(UE_TAU_REQ, msgptr);

   /*insert timer to Timer Queue */
   printf("main thread: got the timer queue lock [%lu]\n", time(NULL));
   /*No need to acquire lock here since this runs in the Timer thread context*/
   /*pthread_mutex_lock(&timer_queue_mutex);*/
   tqm.ueId = ueId;
   tqm.callbk = &tsSendPeriodicTau;
   time(&(tqm.timer));
   tqm.timer += (time_t)(ueTAU[ueId - 1].T3412);
   if (tq_add_msg(&tqm, currQIndx++) == -1)
      printf("Adding timer to Q failed\n");
   if (currQIndx >= 100) currQIndx = 0;
   /*pthread_mutex_unlock(&timer_queue_mutex);*/
   printf("main thread: released the timer queue lock [%lu]\n", time(NULL));

   ueTAU[ueId - 1].nSuccTAU += 1;

   free(msgptr);
}

void tsSendDetach(unsigned char ueId)
{
   void* msgptr = NULL;
   printf("[Stub] Entering tsSendDetachRequest(), ueId(%d)\n", ueId);

   msgptr = malloc(sizeof(uedetachReq_t));
   memset(msgptr, 0, sizeof(uedetachReq_t));
   ((uedetachReq_t*)msgptr)->ue_Id = ueId;
   ((uedetachReq_t*)msgptr)->ueDetType = UE_SWITCHOFF_DETACH;

   /* send Deatch request */
   printf("\n[Stub] Sending Detach Request, ueId(%d)\n", ueId);
   tfwApi(UE_DETACH_REQUEST, msgptr);
   free(msgptr);
   nSuccDet += 1;
   if(nSuccDet >= numTestUE){
        sleep(2);
        tsSendSctpShutdown();
        sleep(2);
        exit(0);
   }
}
