
/**********************************************************************

     Name:     S1SIM Test Controller Stub 
  
     Type:     C source file
  
     Desc:     This file contains the stub code for S1SIM Test Controller

     File:     ts_main.c

     Prg:      

**********************************************************************/
#include <fcntl.h>
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
#include <errno.h>
#include <pthread.h>
#include "fw_api_int.x"
#include "trfgen.x"
#include "ts_utls.x"
#include "ts_timer_queue.h"
#include "ts_timer_thread.h"

#define PID_FILE "/var/run/s1sim.pid"

char noTauComplete; /* If 1, don't send TAU complete */
char requestedIdType; /* Requested mobile ID type in IDENTITY REQUEST message */
int T3412 = 0;
int msgQid = -1;

static pthread_t timer_tid;
extern pthread_mutex_t timer_queue_mutex;

UeIpInfo UeIpInfoLst[32];
UeDedBerInfo UeDedBerLst[32];
void tsPrintHelp(void);
void enbCfg(void);
void enbCfgWithS1Setup(void);
void enbCfgAndS1SetupWithAllIEs(void);
void enbCfgWithS1SetupFail(void);
void enbCfgWithS1SetupTimeOut(void);
void enbInactvTmrCfg(int inactvTmrVal, int maxRetries);
void tsSendSctpAbort();
void tsSendSctpShutdown();

static void timer_signal_term(int signal)
{
   printf("Killing the timer thread...\n");
   pthread_kill(timer_tid, SIGTERM);
   tq_destroy_queue_all();
   exit(0);
}

static int signals_init(void)
{
   int rc;
   sigset_t sigmask;
   struct sigaction sa;

   sigemptyset(&sigmask);
   if((rc = sigaddset(&sigmask, SIGTERM))) {
      printf("sigaddset: %s\n", strerror(errno));
      return -1;
   }

   sa.sa_flags = 0;
   sigemptyset(&sa.sa_mask);
   sa.sa_handler = timer_signal_term;
   if((rc = sigaction(SIGTERM, &sa, NULL))) {
      printf("signal SIGTERM not registered: %s\n", strerror(errno));
      return -1;
   }

   return 0;
}

static int init_timer(void)
{
   int rtn;
   /*timer_queue_msg tqm;*/

   /* Set the signals */
   rtn = signals_init();
   if (rtn != 0)
   {
      printf("setting up signals failed\n");
      return -1;
   }

   /* Init the timer queue */
   tq_init_queue_all();

   /* Create the timer thread */
   rtn = pthread_create(&timer_tid, NULL, timer_thread_main, NULL);
   if (rtn != 0)
   {
      printf("creating a new thread failed: %s\n", strerror(errno));
      return -1;
   }
   /*pthread_join(timer_tid, NULL);*/
   return rtn;
}

int main(int argc, char *argv[])
{
   int noOfUe = 0;
   unsigned char id = 0;
   int flag = 0, eof = 0, isFile = 0, maxue = 0, currue = 0;
   unsigned char ueIdLst[20] = {0};
   char testcase[50], noUe[5];
   FILE *myFile;


   if (argc <= 1)
   {
      printf("ERROR: Insufficient command line arguments to run test cases\n");
      /* Invoke help function */
      tsPrintHelp();
      exit(0);
   }

   if (!strcmp(argv[1], "-h"))
   {
      tsPrintHelp();
      exit(0);
   }

   if ((argv[1][0] ==  '-') && strcmp(argv[1], "-h") && strcmp(argv[1], "-f") )
   {
      printf("\nIncorrect option\n");
      exit(0);
   }

   if (!strcmp(argv[1], "-f") && (argv[2] == NULL))
   {   
      printf("Please enter \"file name\" which has list of testcases to run\n");
      printf("   Example: # ./testCntrlr -f testCaseList_1.txt\n");
      exit(0);
   }

   if (!strcmp(argv[1], "-f") && (myFile = fopen(argv[2], "r")) == NULL)
   {
      printf("\nFile not exists\n");
      exit(0);
   }

   if(!strcmp(argv[1], "-f") )
   {
      isFile= 1;
      while(!feof(myFile))
      {
         fscanf(myFile, "%s %s", testcase, noUe);
         currue = atoi(noUe);
         if(currue > maxue)
         {
            maxue = currue;
         }
      }
      fclose(myFile);
      myFile = fopen(argv[2], "r");
   }

   printf("[Stub] Initialising stack manager\n");
   initTestFrameWork(TC_API);
   trf_test_init();
   init_timer();

   printf("[Stub] Creating message queue..\n");
   msgQid = msgget((key_t)1234, 0666 | IPC_CREAT);

   if (msgQid == -1)
   {
      perror("[Stub] msgget failed with error");
      exit(1);
   }

   if (argc == 2)
   {
      if (!strcmp(argv[1], "ENodeBConfig"))
      {
         enbCfg();
         sleep(5);
         flag = 1;
      }
      else if (!strcmp(argv[1], "S1SetupSucc"))
      {
         enbCfgWithS1Setup();
         sleep(5);
         flag = 1;
      }
      else if (!strcmp(argv[1], "S1SetupSuccWithAllIEs"))
      {
         enbCfgAndS1SetupWithAllIEs();
         sleep(5);
         flag = 1;
      }
      else if (!strcmp(argv[1], "S1SetupFail"))
      {
         enbCfgWithS1SetupFail();
         sleep(5);
         flag = 1;
      }
      else if (!strcmp(argv[1], "S1SetupTimeout"))
      {
         enbCfgWithS1SetupTimeOut();
         sleep(5);
         flag = 1;
      }
      else if (!strcmp(argv[1], "SendSctpAbort"))
      {
         /* Configure Ue App */
         tsUeAppConfig();
         noOfUe = 1;
         id = 1;

         /* Read imsi from file and send UE config request for 
          * required num of UEs */
         if (isFile)
            tsReadImsiAndSendUeConfig(maxue);
         else
            tsReadImsiAndSendUeConfig(noOfUe);

         printf("[Stub] Triggering enbCfg and S1SETUP\n");
         enbCfgWithS1Setup();
         sleep(3);

         printf("[Stub] Triggering step by step ATTACH(IMSI), ueId=1\n");
         tsStepByStepAttachWithImsi(id);
         sleep(3);

         printf("[Stub] Triggering SCTP ABORT\n");
         tsSendSctpAbort();
         sleep(3);

         printf("[Stub] Triggering S1SETUP again\n");
         s1SetUpReq(ENB_S1_SETUP_RESP);
         sleep(3);

         printf("[Stub] Triggering step by step ATTACH(IMSI), ueId=1\n");
         tsStepByStepAttachWithImsi(id);
         sleep(3);

         printf("[Stub] Triggering UE DETACH, ueId=1\n");
         tsSendDetachRequest(id, UE_SWITCHOFF_DETACH, UE_IN_CONNECTED_MODE);

         flag = 1;
      }
      else if (!strcmp(argv[1], "SendSctpShutdown"))
      {
         /* Configure Ue App */
         tsUeAppConfig();
         noOfUe = 1;
         id = 1;

         /* Read imsi from file and send UE config request for 
          * required num of UEs */
         if (isFile)
            tsReadImsiAndSendUeConfig(maxue);
         else
            tsReadImsiAndSendUeConfig(noOfUe);

         printf("[Stub] Triggering enbCfg and S1SETUP\n");
         enbCfgWithS1Setup();
         sleep(3);

         printf("[Stub] Triggering step by step ATTACH(IMSI), ueId=1\n");
         tsStepByStepAttachWithImsi(id);
         sleep(3);

         printf("[Stub] Triggering SCTP SHUTDOWN\n");
         tsSendSctpShutdown();
         sleep(3);

         printf("[Stub] Triggering S1SETUP again\n");
         s1SetUpReq(ENB_S1_SETUP_RESP);
         sleep(3);

         printf("[Stub] Triggering step by step ATTACH(IMSI), ueId=1\n");
         tsStepByStepAttachWithImsi(id);
         sleep(3);

         printf("[Stub] Triggering UE DETACH, ueId=1\n");
         tsSendDetachRequest(id, UE_SWITCHOFF_DETACH, UE_IN_CONNECTED_MODE);

         flag = 1;
      }

      if (1 == flag)
         return 0;
   }

   /* Configure Ue App */
   tsUeAppConfig();
   noOfUe = (int)atoi(argv[2]);

   /* Read imsi from file and send ue config request for 
    * required num of Ues */
   if(isFile)
      tsReadImsiAndSendUeConfig(maxue);/*(noOfUe);*/
   else
      tsReadImsiAndSendUeConfig(noOfUe);/*(noOfUe);*/


   /* Configure EnodeB App */
   enbCfgWithS1Setup();

   if (argc > 3)
   {
      printf("[Stub] ERROR: Excess command line arguments !\n");
      exit(0);
   }

   for (;((argc == 3) && !eof); )
   {
      if(isFile)
      {
         fscanf(myFile, "%s %s", testcase, noUe);  
         strcpy(argv[1], testcase);
         noOfUe = atoi(noUe);
         if((eof = feof(myFile)))
         {
            printf("\n============\nTC file ends\n============\n");
            break;
         }
      }
      if(argv[1][0] == '#')
           continue;

      if (!strcmp(argv[1], "StepAttachWithImsi"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            printf("[Stub] Performing step by step ATTACH(IMSI) procedure\n");
            printf("[Stub] ueId(%d)\n", id);
            tsStepByStepAttachWithImsi(id);
         }

         printf("[Stub] Detaching UEs...\n");
         sleep(2);

         for (id = 1; id <= noOfUe; id++)
         {
            tsSendDetachRequest(id, UE_SWITCHOFF_DETACH, UE_IN_CONNECTED_MODE);
         }
         sleep(2);
      }
      else if (!strcmp(argv[1], "AttachWithSecModeReject"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            printf("[Stub] Performing step by step ATTACH(IMSI) procedure\n");
            printf("[Stub] Simulating Security Mode Reject               \n");
            printf("[Stub] ueId(%d)\n", id);
            tsAttachWithSecModeReject(id);
         }
         sleep(2);
      }

      else if (!strcmp(argv[1], "StepAttachWithGuti"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            printf("[Stub] Performing step by step ATTACH(GUTI) procedure\n");
            printf("[Stub] ueId(%d)\n", id);
            tsStepByStepAttachWithGuti(id);
         }

         printf("[Stub] Detaching UEs...\n");
         sleep(2);

         for (id = 1; id <= noOfUe; id++)
         {
            tsSendDetachRequest(id, UE_SWITCHOFF_DETACH, UE_IN_CONNECTED_MODE);
         }
         sleep(2);
      }
      else if (!strcmp(argv[1], "StepReAttach"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            printf("[Stub] Performing step by step ATTACH(IMSI) and"\
                  "RE-ATTACH(GUTI) procedure\n");
            printf("[Stub] ueId(%d)\n", id);
            tsStepByStepReAttach(id);
         }

         printf("[Stub] Detaching UEs...\n");
         sleep(2);

         for (id = 1; id <= noOfUe; id++)
         {
            tsSendDetachRequest(id, UE_SWITCHOFF_DETACH, UE_IN_CONNECTED_MODE);
         }
         sleep(2);
      }
      else if (!strcmp(argv[1], "EndToEndAttach"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            printf("[Stub] Performing end to end ATTACH(IMSI)\n");
            printf("[Stub] ueId(%d)\n", id);
            tsCompleteAttach(id);
         }

         printf("[Stub] Detaching UEs...\n");
         sleep(2);

         for (id = 1; id <= noOfUe; id++)
         {
            tsSendDetachRequest(id, UE_SWITCHOFF_DETACH, UE_IN_CONNECTED_MODE);
         }
         sleep(2);
      }
      else if(!strcmp(argv[1], "AttachRequest_PCO_DRX"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            printf("[Stub] ATTACH(IMSI) Procedure Including PCO in Attach Request\n");
            printf("[Stub] ueId(%d)\n", id);
            tsAttach_PCO_DRX(id);
         }

         printf("[Stub] Detaching UEs...\n");
         sleep(10);

         for (id = 1; id <= noOfUe; id++)
         {
            tsSendDetachRequest(id, UE_SWITCHOFF_DETACH, UE_IN_CONNECTED_MODE);
         }
         sleep(2);
      }
      else if (!strcmp(argv[1], "EmergencyAttach"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            printf("[Stub] Performing end to end ATTACH(IMSI)\n");
            printf("[Stub] ueId(%d)\n", id);
            tsAttachEmergency(id);
         }

         printf("[Stub] Detaching UEs...\n");
         sleep(10);

         for (id = 1; id <= noOfUe; id++)
         {
            tsSendDetachRequest(id, UE_SWITCHOFF_DETACH, UE_IN_IDLE_MODE);
         }
         sleep(2);
      }
      else if (!strcmp(argv[1], "AttachWithAUTV"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            printf("[Stub] Performing end to end ATTACH(IMSI)\n");
            printf("[Stub] ueId(%d)\n", id);
            tsAttachWithAUTV(id);
         }

         printf("[Stub] Detaching UEs...\n");
         sleep(10);

         for (id = 1; id <= noOfUe; id++)
         {
            tsSendDetachRequest(id, UE_SWITCHOFF_DETACH, UE_IN_CONNECTED_MODE);
         }
         sleep(2);
      }
      else if (!strcmp(argv[1], "SyncFailureWithWrapARound"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            printf("[Stub] Performing Sync failure from UE\n");
            printf("[Stub] ueId(%d)\n", id);
            SyncFailureWithWrapARound(id);
         }
         sleep(2);
         for (id = 1; id <= noOfUe; id++)
         {
            tsSendDetachRequest(id, UE_SWITCHOFF_DETACH, UE_IN_CONNECTED_MODE);
         }
         sleep(2);
      }
      else if (!strcmp(argv[1], "SyncFailureWithAgeLimit"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            printf("[Stub] Performing Sync failure from UE\n");
            printf("[Stub] ueId(%d)\n", id);
            SyncFailureWithAgeLimit(id);
         }
         sleep(2);
         for (id = 1; id <= noOfUe; id++)
         {
            tsSendDetachRequest(id, UE_SWITCHOFF_DETACH, UE_IN_CONNECTED_MODE);
         }
         sleep(2);
      }
      else if (!strcmp(argv[1], "SyncFailureWithDelta"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            printf("[Stub] Performing Sync failure from UE\n");
            printf("[Stub] ueId(%d)\n", id);
            SyncFailureWithDelta(id);
         }
         sleep(2);
         for (id = 1; id <= noOfUe; id++)
         {
            tsSendDetachRequest(id, UE_SWITCHOFF_DETACH, UE_IN_CONNECTED_MODE);
         }
         sleep(2);
      }
      else if (!strcmp(argv[1], "AuthFailAMF"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            printf("[Stub] Performing Auth failure-AMF\n");
            printf("[Stub] ueId(%d)\n", id);
            tsAuthFailAMF(id);
         }
         for (id = 1; id <= noOfUe; id++)
         {
            tsSendDetachRequest(id, UE_SWITCHOFF_DETACH, UE_IN_CONNECTED_MODE);
         }
         sleep(2);
      }
      else if (!strcmp(argv[1], "NomalDetach"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            testDetachiWithCauseNormal(id);
            sleep(2);
         }
      }
      else if (!strcmp(argv[1], "AttachAndUlData"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            tsSendAttachRequest(id);
            sleep(1);
         }
         unsigned int attempts = 0;
         int fd;
         do {
            sleep((1 << attempts++) - 1);
            fd = open(PID_FILE, O_CREAT | O_EXCL | O_WRONLY);
         } while (-1 == fd);
         {
            char pid[32];
            sprintf(pid, "%d", getpid());
            write(fd, pid, strlen(pid));
         }
         for (id = 1; id <= noOfUe; id++)
         {
            tsStartUlData(id);
            sleep(1);
         }
         int i;
         for (i = 0; i < 13 && fopen(PID_FILE, "r"); i++) {
            sleep(10);
         }
         if (fopen(PID_FILE, "r")) {
            close(fd);
            unlink(PID_FILE);
         }
         for(id = 1; id <= noOfUe; id++)
         {
            tsSendDetachRequest(id, UE_SWITCHOFF_DETACH, UE_IN_CONNECTED_MODE);
         }
         for(id = 1; id <= noOfUe; id++)
         {
            deleteCfgdUeIps(id);
         }
         sleep(2);
         tsCleanup();
      }
      else if (!strcmp(argv[1], "AttachAndDlData"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            tsSendAttachRequest(id);
            sleep(1);
         }
         unsigned int attempts = 0;
         int fd;
         do {
            sleep((1 << attempts++) - 1);
            fd = open(PID_FILE, O_CREAT | O_EXCL | O_WRONLY);
         } while (-1 == fd);
         for (id = 1; id <= noOfUe; id++)
         {
            tsStartDlData(id);
            sleep(1);
         }
         int i;
         for (i = 0; i < 13 && fopen(PID_FILE, "r"); i++) {
            sleep(10);
         }
         if (fopen(PID_FILE, "r")) {
            close(fd);
            unlink(PID_FILE);
         }
         for (id = 1; id <= noOfUe; id++)
         {
            tsSendDetachRequest(id, UE_SWITCHOFF_DETACH, UE_IN_CONNECTED_MODE);
         }
         for(id = 1; id <= noOfUe; id++)
         {
            deleteCfgdUeIps(id);
         }
         sleep(2);
         tsCleanup();
      }
      else if (!strcmp(argv[1], "PeriodicTau"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            printf("[Stub] Performing periodic TAU\n");
            printf("[Stub] ueId(%d)\n", id);
            testPeriodicTauRequest(id);
            sleep(5);
         }
      }
      else if (!strcmp(argv[1], "PeriodicTauReject"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            testPeriodicTauRequestReject(id);
            sleep(5);
         }
      }
      else if (!strcmp(argv[1], "PeriodicTauNoTauComplete"))
      {
         /* Test periodic TAU, don't send TAU Complete after TAU Accept */
         for (id = 1; id <= noOfUe; id++)
         {
            printf("[Stub] Performing periodic TAU, without TAU Complete\n");
            printf("[Stub] ueId(%d)\n", id);
            /* Set the flag, not to send TAU Complete */
            noTauComplete = 1;
            testPeriodicTauRequest(id);
            sleep(5);
         }
      }
      else if (!strcmp(argv[1], "ServiceRequest"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            testServiceRequest(id);
            sleep(5);
         }
      }
      else if (!strcmp(argv[1], "ServiceRequest1"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            testServiceRequest1(id);
            sleep(5);
         }
      }
      else if (!strcmp(argv[1], "ServiceRequestAndData"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            testServiceRequestAndData(id);
            sleep(5);
         }
      }
      else if (!strcmp(argv[1], "ServiceReject"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            testServiceRequestReject(id);
            sleep(5);
         }
      }
      else if (!strcmp(argv[1], "UeCntxtRelRequest"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            testUeCntxtRelRequest(id);
         }
      }
      else if (!strcmp(argv[1], "NormalTau"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            testNormalTauRequest(1);
            sleep(2);
         }
      }
      else if(!strcmp(argv[1], "NormalTauRequestWithActFlag"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            testNormalTauRequestWithActFlag(id);
            sleep(2);
         }
      }
      else if(!strcmp(argv[1], "NormalPaging"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            testNormalPaging(id);
            sleep(2);
         }
      }
      else if(!strcmp(argv[1], "TimeoutPaging"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            testTimeoutPaging(id);
            sleep(2);
         }
      }
      else if (!strcmp(argv[1], "UeRadCapUpdate"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            testUeRadCapModReq(id);
         }
      }
      else if (!strcmp(argv[1], "PdnConnReq"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            tsSendAttachRequest(id);
            sleep(2);
         }
         for (id = 1; id <= noOfUe; id++)
         {
            testUePdnConnReq(id);
            sleep(2);
         }
         for (id = 1; id <= noOfUe; id++)
         {
            tsSendDetachRequest(id, UE_SWITCHOFF_DETACH, UE_IN_CONNECTED_MODE);
            sleep(2);
         }
      }
      else if (!strcmp(argv[1], "PdnConnRej"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            tsSendAttachRequest(id);
            sleep(2);
         }
         for (id = 1; id <= noOfUe; id++)
         {
            testUePdnConnRej(id);
            sleep(5);
         }
         for (id = 1; id <= noOfUe; id++)
         {
            tsSendDetachRequest(id, UE_SWITCHOFF_DETACH, UE_IN_CONNECTED_MODE);
            sleep(2);
         }
      }
      else if (!strcmp(argv[1], "PdnConnReqAndData"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            tsSendAttachRequest(id);
            sleep(2);
         }
         for (id = 1; id <= noOfUe; id++)
         {
            testUePdnConnReqAndData(id);
            sleep(2);
         }
         for (id = 1; id <= noOfUe; id++)
         {
            tsSendDetachRequest(id, UE_SWITCHOFF_DETACH, UE_IN_CONNECTED_MODE);
            sleep(2);
         }
      }
      else if (!strcmp(argv[1], "NwInitDetach"))
      {   
         testNwInitDetach(1);
      }   
      else if (!strcmp(argv[1], "Flush"))
      {   
         flush(noOfUe);
      }
      else if(!strcmp(argv[1], "CompleteResetRequest"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            tsSendAttachRequest(id);
         }
         sleep(2);

         tsSendResetReq(COMPLETE_RESET, 0, NULL);

         sleep(5);
      }
      else if(!strcmp(argv[1], "PartialResetRequest"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            tsSendAttachRequest(id);
            sleep(2);
         }
         sleep(2);

         ueIdLst[0] = 1;
         ueIdLst[1] = 2;
         ueIdLst[2] = 3;
         tsSendResetReq(PARTIAL_RESET, 3, ueIdLst);

         sleep(5);
      }
      else if (!strcmp(argv[1], "ErrIndWithIvalidUeS1apIds"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            testErrIndWithIvalidUeS1apIds(id);
            sleep(5);
         }
      }
      else if (!strcmp(argv[1], "ErabRelInd"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            tsSendAttachRequest(id);
            sleep(2);
         }
         for (id = 1; id <= noOfUe; id++)
         {
            testUePdnConnReq(id);
            sleep(2);
         }
         for(id = 1; id <= noOfUe; id++)
         {
            tsSendErabRelReq(id, ueErabInfo[id - 1].numOfBrs - 1,
                  &ueErabInfo[id - 1].brLst[1]);
            sleep(2);
         }
         sleep(5);
      }
      else if (!strcmp(argv[1], "IdleModeDetach"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            tsSendAttachRequest(id);
            sleep(2);
         }

         for (id = 1; id <= noOfUe; id++)
         {
            tsSendUeCntxtReleaseRequest(id, 18);
            sleep(1);
         }
         for (id = 1; id <= noOfUe; id++)
         {
            tsSendDetachRequest(id, UE_NORMAL_DETACH, UE_IN_IDLE_MODE);
            sleep(1);
         }
      }
      else if (!strcmp(argv[1], "AttachTAUDetach"))
      {
         /* Configure the inactivity timer to a small value */
         enbInactvTmrCfg(200, 3);
         tsAttach_tau_detach(noOfUe, 3);
         sleep(5);
         /* Configure the inactivity timer to a large value */
         enbInactvTmrCfg(2000000, 2000);
      }
      else if (!strcmp(argv[1], "UeInitiatedDedBer"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            testUeInitiatedDedBerReq(id);
            sleep(5);
         }
      }
      else if (!strcmp(argv[1], "ActvDedBerRejWithInvalidBerId"))
      {
         for (id = 1; id <= noOfUe; id++)
         {
            testActvDedBerRejWithIvalidEpsBerId(id);
            sleep(5);
         }
      }
      else if (!strcmp(argv[1], "NasNonDelivery"))
      {
         testNasNonDelivery(1);
         sleep(2);
      }
      else if (!strcmp(argv[1], "InitialContextSetupFailure"))
      {
         testInitialContextSetupFailure(1);
         sleep(2);
      }
      else if (!strcmp(argv[1], "InitialContextSetupDrop"))
      {
         testInitialContextSetupDrop(1);
         sleep(2);
      }
      else if (!strcmp(argv[1], "InitialContextSetupDelayRsp"))
      {
         testInitialContextSetupDelayRsp(1);
         sleep(2);
      }
      else if (!strcmp(argv[1], "InitialContextSetupSendCtxtRelReq"))
      {
         testInitialContextSetupUeCtxtRelReq(1);
         sleep(2);
      }
      else
      {
         printf("[Stub] Please use \"testCntrlr -h\" for help\n");
      }
      if(isFile == 1)
      {
         sleep(2);
         continue;
      }
      else
      {
         break; 
      }
   }
   printf("[Stub] Cleaning SCTP connection\n");
   tsSendSctpShutdown();
   sleep(3);
   return 0;
}


/* Prints help : How to run test cases */
void tsPrintHelp()
{
   printf("   Usage:\n");
   printf("     To run non-UE related testcases(S1Setup, eNB Config etc):\n");
   printf("       # ./testCntrlr <test_case_keyword>\n");
   printf("     To run UE related testcases(Attach, Detach, TAU etc):\n");
   printf("       # ./testCntrlr <test_case_keyword> <no_of_UEs>\n");
   printf("     To run list of testcases given in a text file:\n");
   printf("       # ./testCntrlr -f <file_name>\n");
   printf("\n");

   printf("      Valid test case keywords:\n");
   printf("         StepAttachWithImsi\n");
   printf("            - To test step by step ATTACH procedure with IMSI &\n");
   printf("              DETACH(poweroff)\n");
   printf("         StepAttachWithGuti\n");
   printf("            - To test step by step ATTACH procedure with GUTI,\n");
   printf("              includes IDENTITY procedure, DETACH(poweroff)\n");
   printf("         StepReAttach\n");
   printf("            - To test step by step RE-ATTACH procedure.\n");
   printf("              Does ATTACH(IMSI), RE-ATTACH with GUTI & stored\n");
   printf("              security contexts, DETACH(poweroff)\n");
   printf("         EndToEndAttach\n");
   printf("            - To test end to end ATTACH and DETACH(poweroff)\n");
   printf("         SyncFailureWithWrapARound\n");
   printf("            - To test sync Failure With WrapARound\n");
   printf("         SyncFailureWithAgeLimit\n");
   printf("            - To test sync Failure With AgeLimit\n");
   printf("         SyncFailureWithDelta\n");
   printf("            - To test sync Failure With Delta\n");
   printf("         AuthFailAMF\n");
   printf("            - To test AUTH Failure- AMF\n");
   printf("         NomalDetach\n");
   printf("            - To test DETACH(normal)\n");
   printf("         AttachAndUlData\n");
   printf("            - To test UE Attach and UL Data\n");
   printf("         AttachAndDlData\n");
   printf("            - To test UE Attach and Data\n");
   printf("         NormalTau\n");
   printf("            - To test TAU(normal)\n");
   printf("         NormalTauRequestWithActFlag\n");
   printf("            - To test TAU(normal) with Ul data pending\n");
   printf("         PeriodicTau\n");
   printf("            - To test TAU(periodic)\n");
   printf("         PeriodicTauReject\n");
   printf("            - To test TAU REJECT(normal)\n");
   printf("         PeriodicTauNoTauComplete\n");
   printf("            - To test TAU(periodic) without sending TAU Complete\n");
   printf("         ServiceRequest\n");
   printf("            - To test SERVICE REQUEST\n");
   printf("         ServiceRequest1\n");
   printf("            - To test SERVICE REQUEST\n");
   printf("         ServiceRequestAndData\n");
   printf("            - To test SERVICE REQUEST and Data\n");
   printf("         ServiceReject\n");
   printf("            - To test SERVICE REJECT\n");
   printf("         UeCntxtRelRequest\n");
   printf("            - To test UE Context Release Request\n");
   printf("         ENodeBConfig\n");
   printf("            - To test eNodeB configuration\n");
   printf("         S1SetupSucc\n");
   printf("            - To test S1 SETUP success case\n");
   printf("         S1SetupSuccWithAllIEs\n");
   printf("            - To test S1 SETUP success case with all IEs\n");
   printf("         S1SetupFail\n");
   printf("            - To test S1 SETUP failure case\n");
   printf("         S1SetupTimeout\n");
   printf("            - To test S1 SETUP timeout case\n");
   printf("         NormalPaging\n");
   printf("            - To test incoming Paging and send service request\n");
   printf("         TimeoutPaging\n");
   printf("            - To test Paging indication when MME retries after\n");
   printf("              paging timeout\n");
   printf("         PdnConnReq\n");
   printf("            - To test UE PDN Connection Req\n");
   printf("         PdnConnRej\n");
   printf("            - To test UE PDN Connection Rej\n");
   printf("         PdnConnReqAndData\n");
   printf("            - To test UE PDN Connection Req With Data\n");
   printf("         UeRadCapUpdate\n");
   printf("            - To test Ue Radio capability\n");
   printf("         AttachWithSecModeReject\n");
   printf("            - To simulate SecModeReject during IMSI Attach\n");
   printf("         EmergencyAttach\n");
   printf("            - To simulate Emergency Attach with IMEI\n");
   printf("         AttachWithAUTV\n");
   printf("            - To include Additional Update Type in AttachRequest\n");
   printf("         AttachRequest_PCO_DRX\n");
   printf("            - To include Additional Protocol Configurqation\n");
   printf("              options IE in Attach Request\n");
   printf("         CompleteResetRequest\n");
   printf("            - To send Complete Reset Request to MME\n");
   printf("         PartialResetRequest\n");
   printf("            - To send Partial Reset Request to MME\n");
   printf("         NwInitDetach\n");
   printf("            - To test Network initiated Detach\n");
   printf("         ErrIndWithIvalidUeS1apIds\n");
   printf("            - To test Error Indication With Invalid ue-s1ap-ids\n");
   printf("         ErabRelInd\n");
   printf("            - To test ERAB Release Indication\n");
   printf("         IdleModeDetach\n");
   printf("            - To test Detach in Idle mode\n");
   printf("         AttachTAUDetach\n");
   printf("            - To test Detach in Idle mode\n");
   printf("         UeInitiatedDedBer\n");
   printf("            - To test Ue Initaited dedicated bearer request\n");
   printf("         ActvDedBerRejWithInvalidBerId\n");
   printf("            - To test Actv Dedicated Bearer Context reject\n");
   printf("         SendSctpAbort\n");
   printf("            - To send SCTP ABORT Request to EPC\n");
   printf("         SendSctpShutdown\n");
   printf("            - To send SCTP SHUTDOWN Request to EPC\n");
   printf("\n");
   printf("         NasNonDelivery\n");
   printf("            - To test Nas Non Delivery\n");
   printf("         InitialContextSetupFailure\n");
   printf("            - To test Initial Context Setup Failure\n");
   printf("         InitialContextSetupDrop\n");
   printf("            - To test Initial Context Setup Drop\n");
   printf("         InitialContextSetupDelayRsp\n");
   printf("            - To test Initial Context Setup Delay Rsp\n");
   printf("         InitialContextSetupSendCtxtRelReq\n");
   printf("            - To test Send Ue Context Rel Req for Initial Context Setup Received,\n");

   printf("      No of UEs: [1...16]\n");
   printf("\n");

   printf("   Example:\n");
   printf("      # ./testCntrlr S1SetupSucc\n");
   printf("      # ./testCntrlr EndToEndAttach 1\n");
   printf("      # ./testCntrlr StepAttachWithImsi 5\n");
   printf("      # ./testCntrlr -f testCaseList_1.txt\n");
   printf("\n");
}
