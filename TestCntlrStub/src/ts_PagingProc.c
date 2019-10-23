
/**********************************************************************

     Name:     S1SIM Test Controller Stub 
  
     Type:     C source file
  
     Desc:     This file contains the stub code for SERVICE REQUEST related
               procedures. 

     File:     ts_PagingProc.c

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

extern int paging_ueid;

int testNormalPaging(unsigned char ueId)
{
   tsSendAttachRequest(ueId);
   sleep(2);

   printf("\n----------------------------------\n"\
          "Sending UE context Release Request\n"\
          "----------------------------------\n");
   tsSendUeCntxtReleaseRequest(ueId, 18);
   sleep(2);

   printf("\n-----------------------\n"\
         "Waiting for paging indication\n"\
         "-----------------------\n");
   
   if (TC_msg_recv(UE_PAGING_IND, 10) == SUCC)
   {
      printf("\nReceived Paging indication\n");
      printf("\n-----------------------\n"\
        	 "Sening Service request\n"\
        	 "-----------------------\n");
      tsSendServiceRequest(paging_ueid, TEST_TYPE_PAGING);
      if(TC_msg_recv(INT_CTX_SETUP_IND, 10) == SUCC)
      {
         printf("\n[Stub] Received Initial Context Setup indication\n");
      }
   }
   else
   {
      printf("\n[Stub] Paging failed\n");
   }
   sleep(2);

   tsSendDetachRequest(ueId, UE_SWITCHOFF_DETACH, UE_IN_CONNECTED_MODE);

   return 0;
}

int testTimeoutPaging(unsigned char ueId)
{
   tsSendAttachRequest(ueId);
   sleep(2);

   printf("\n----------------------------------\n"\
          "Sending UE context Release Request\n"\
          "----------------------------------\n");
   tsSendUeCntxtReleaseRequest(ueId, 18);
   sleep(2);

   printf("\n-----------------------\n"\
         "Waiting for paging indication\n"\
         "-----------------------\n");
   /* Wait for Attach Accept indication */
   
   if (TC_msg_recv(UE_PAGING_IND, 10) == SUCC)
   {
      printf("\nReceived first Paging indication\n");
   }
   else
   {
      printf("\n[Stub] Paging failed\n");
   }
   printf("\n-----------------------\n"\
         "Waiting for next paging indication\n"\
         "-----------------------\n");
   if (TC_msg_recv(UE_PAGING_IND, 10) == SUCC)
   {
      printf("\nReceived second Paging indication\n");
   }
   else
   {
      printf("\n[Stub] Paging failed\n");
   }
   printf("\n-----------------------\n"\
         "Waiting for next  paging indication\n"\
         "-----------------------\n");
   if (TC_msg_recv(UE_PAGING_IND, 10) == SUCC)
   {
      printf("\nReceived third Paging indication\n");
      printf("\n-----------------------\n"\
        	 "Sending Service request\n"\
        	 "-----------------------\n");
      tsSendServiceRequest(paging_ueid, TEST_TYPE_PAGING);
      if(TC_msg_recv(INT_CTX_SETUP_IND, 10) == SUCC)
      {
         printf("\n[Stub] Received Initial Context Setup indication\n");
      }
   }
   else
   {
      printf("\n[Stub] Paging failed\n");
   }
   sleep(2);

   tsSendDetachRequest(ueId, UE_SWITCHOFF_DETACH, UE_IN_CONNECTED_MODE);

   return 0;
}
