
/**********************************************************************

     Name:     S1SIM Test Controller Stub 
  
     Type:     C source file
  
     Desc:     This file contains the stub code for SERVICE REQUEST related
               procedures. 

     File:     ts_serviceProcs.c

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

int testServiceRequest(unsigned char ueId)
{
   tsSendAttachRequest(ueId);
   sleep(1);

   /* Release the UE Context */
   tsSendUeCntxtReleaseRequest(ueId, 18);
   sleep(5);

   printf("\n-----------------------\n"\
         "Sending Service Request\n"\
         "-----------------------\n");

   tsSendServiceRequest(ueId, TEST_TYPE_SERVICE_REQUEST);

   /* Wait for Initial Context Setup indication */
   if (TC_msg_recv(INT_CTX_SETUP_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Initial Context Setup indication\n");
   }
   else
   {
      printf("\n[Stub] Initial Context Setup indication failed\n");
   }

   sleep(5);

   tsSendDetachRequest(ueId, UE_SWITCHOFF_DETACH, UE_IN_CONNECTED_MODE);

   return 0;
}

int testServiceRequestAndData(unsigned char ueId)
{
   tsSendAttachRequest(ueId);
   sleep(1);
   
   /* Release the UE Context */
   tsSendUeCntxtReleaseRequest(ueId, 18);
   sleep(5);

   printf("\n-----------------------\n"\
         "Sending Service Request\n"\
         "-----------------------\n");

   tsSendServiceRequest(ueId, TEST_TYPE_SERVICE_REQUEST);

   /* Wait for Initial Context Setup indication */
   if (TC_msg_recv(INT_CTX_SETUP_IND, 10)== SUCC)
   {
      printf("\n[Stub] Received Initial Context Setup indication\n");
   }
   else
   {
      printf("\n[Stub] Initial Context Setup indication failed\n");
   }

   tsStartUlData(ueId);
   sleep(20);

   tsSendDetachRequest(ueId, UE_SWITCHOFF_DETACH, UE_IN_CONNECTED_MODE);

   return 0;
}

int testServiceRequestReject(unsigned char ueId)
{
   tsSendAttachRequest(ueId);
   sleep(1);

   /* Release the UE Context */
   tsSendUeCntxtReleaseRequest(ueId, 18);
   sleep(5);

   printf("\n-----------------------\n"\
         "Sending Service Request\n"\
         "----------------------------\n");

   tsSendServiceRequest(ueId, TEST_TYPE_SERVICE_REJECT);

   /* Wait for Service Reject Indication */
   if (TC_msg_recv(UE_SERVICE_REJECT_IND, 10) == SUCC)
   {
      printf("\nReceived Service Reject indication\n");
   }
   else
   {
      printf("Failed to recieve Service Reject Indication\n");
   }
   sleep(5);
   if(TC_msg_recv(UE_CTX_REL_IND, 10) == SUCC)
   {
      printf("\nReceived UE Context Release indication\n");
   }

   tsSendDetachRequest(ueId, UE_NORMAL_DETACH, UE_IN_IDLE_MODE);
   sleep(5);

   return 0;
}

int testServiceRequest1(unsigned char ueId)
{
   tsSendAttachRequest(ueId);
   sleep(1);
   


   tsSendDetachRequest(ueId, UE_NORMAL_DETACH, UE_IN_IDLE_MODE);
   tsSendServiceRequest(ueId, TEST_TYPE_SERVICE_REQUEST);
   /* Wait for Service Reject Indication */
   if (TC_msg_recv(UE_SERVICE_REJECT_IND, 10) == SUCC)
   {
      printf("\nReceived Service Reject indication\n");
   }
   else
   {
      printf("Failed to recieve Service Reject Indication\n");
   }

   return 0;
}
