
/**********************************************************************

     Name:     S1SIM Test Controller Stub 
  
     Type:     C source file
  
     Desc:     This file contains the stub code for S1SIM Test Controller

     File:     ts_periodicTauProcs.c

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

int testPeriodicTauRequest(unsigned char ueId)
{
   tsSendAttachRequest(ueId);
   sleep(1);

   /* Release the UE context */
   tsSendUeCntxtReleaseRequest(ueId, 18);
   sleep(5);

   tsStartPeriodicTauTimer(ueId, TEST_TYPE_TAU_REQUEST);
   sleep(5);

   tsSendDetachRequest(ueId, UE_NORMAL_DETACH, UE_IN_IDLE_MODE);

   return 0;
}

int testPeriodicTauRequestReject(unsigned char ueId)
{
   tsSendAttachRequest(ueId);
   sleep(1);

   /* Release the UE context */
   tsSendUeCntxtReleaseRequest(ueId, 18);

   tsStartPeriodicTauTimer(ueId, TEST_TYPE_TAU_REJECT);

   tsSendDetachRequest(ueId, UE_NORMAL_DETACH, UE_IN_IDLE_MODE);
   sleep(5);

   return 0;
}

int testNormalTauRequest(unsigned char ueId)
{
   tsSendAttachRequest(ueId);
   sleep(2);
   
   /* Release the UE context */
   tsSendUeCntxtReleaseRequest(ueId, 18);
   sleep(2);   

   tsSendTauRequest(ueId, "Normal", FALSE, TEST_TYPE_TAU_REQUEST);
   sleep(2);
   if(TC_msg_recv(UE_CTX_REL_IND, 10) == SUCC)
   {
      printf("\nReceived UE Context Release indication\n");
   }
   
   tsSendDetachRequest(ueId, UE_NORMAL_DETACH, UE_IN_IDLE_MODE);
   sleep(2);

   return 0;
}

int testNormalTauRequestWithActFlag(unsigned char ueId)
{
   tsSendAttachRequest(ueId);
   sleep(1);

   /* Release the UE context */
   tsSendUeCntxtReleaseRequest(ueId, 18);

   tsSendTauRequest(ueId, "Normal", TRUE, TEST_TYPE_TAU_REQUEST);
   sleep(1);

   tsStartUlData(ueId);
   sleep(20);

   tsSendDetachRequest(ueId, UE_SWITCHOFF_DETACH, UE_IN_CONNECTED_MODE);
   sleep(5);

   return 0;
}
