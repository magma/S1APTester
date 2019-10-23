/**********************************************************************

    Name:  LTE S1SIM - UE Application Module 
 
    Type:  C ource file
 
    Desc:  C source code for UE Application upper interface
 
    File:  ue_ui.c
 
    Sid:   
 
    Prg:   
 
**********************************************************************/

 /* UE application upper interface */
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
#include "ss_queue.h"      /* queues */
#include "ss_task.h"       /* tasking */
#include "ss_msg.h"        /* messaging */
#include "ss_mem.h"        /* memory management interface */
#include "ss_gen.h"        /* general */
#include "rl_interface.h"
#include "rl_common.h"
#include "lue.h"
#include "ue.h"
#include "ue_log.h"
#include "lfw.h"

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
#include "ss_queue.x"      /* queues */
#include "ss_task.x"       /* tasking */
#include "ss_timer.x"      /* timers */
#include "ss_strm.x"       /* STREAMS */
#include "ss_msg.x"        /* messaging */
#include "ss_mem.x"        /* memory management interface */
#include "ss_drvr.x"       /* driver tasks */
#include "ss_gen.x"        /* general */
#include "lue.x"
#include "uet.x"
#include "lnb.x"
#include "ue.x"
#include "ueAppdbm.x"

EXTERN UeAppCb gueAppCb;

EXTERN S16 ueSendToTfwApp(UetMessage *tfwMsg, Pst *pst);
EXTERN S16 ueUiProcessTfwMsg(UetMessage *p_ueMsg, Pst *pst);
EXTERN S16 UeUiUetDatRsp(Pst *pst, UetMessage *msg);

PUBLIC S16 UeUiUetMsgReq
(
 Pst        *pst,    /* Post structure */
 UetRequest *p_ueMsg /* request message */
)
{
   S16   ret = RFAILED;
   UeAppCb *ueAppCb = NULLP;
   UE_GET_CB(ueAppCb);

   UE_LOG_ENTERFN(ueAppCb);

   /* sanity check */
   if (!pst || !p_ueMsg)
   {
      /* if the message is valid, then de-allocate the
       * memory to avoid memory leak
       */
      if (p_ueMsg)
      {
         ueFree((U8*)p_ueMsg, sizeof(UetMessage));
      } /* end of if message is valid */

      RETVALUE(UE_ERR_INV_PARAM);
   } /* end of if pst or p_ueMsg are not valid pointers */

   /* process the received recived UE message from TFW */
   if ((ret = ueUiProcessTfwMsg(p_ueMsg, pst)) != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Failed while processing the Msg Request");
      ret = RFAILED;
   } /* end of if processing the message fails */

   ueFree((U8*)p_ueMsg, sizeof(UetMessage));
   UE_LOG_EXITFN(ueAppCb, ret);
} /* end of UeUiUetMsgReq */

PUBLIC S16 UeUiUetMsgRsp
(
 Pst         *pst,    /* Post structure */
 UetResponse *p_ueMsg /* request message */
)
{
   /* return value */
   S16        ret = RFAILED;
   UeAppCb *ueAppCb=NULL;
   UE_GET_CB(ueAppCb);

   UE_LOG_ENTERFN(ueAppCb);

   /* sanity check */
   if (!pst || !p_ueMsg)
   {
      /* if the message is valid, then de-allocate the
       * memory to avoid memory leak
       */
      if (p_ueMsg)
      {
         if ((ret = ueFree((U8*)p_ueMsg, sizeof(UetMessage))) != ROK)
         {
            UE_LOG_DEBUG(ueAppCb,
                        "Failed while De-allocating memory for the Ue message");
            RETVALUE(ret);
         }
      } /* end of if message is valid */

      RETVALUE(UE_ERR_INV_PARAM);
   } /* end of if pst or p_ueMsg are not valid pointers */

   /* process the received recived MME NAS message */
   if ((ret = ueUiProcessTfwMsg(p_ueMsg, pst)) != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "UeUiUetMsgReq: Failed while processing the Msg "\
            "Request");
      RETVALUE(ret);
   } /* end of if processing the message fails */

   UE_LOG_EXITFN(ueAppCb, ret);
} /* end of UeUiUetMsgReq */

PUBLIC S16 ueSendToTfwApp
(
 UetMessage *tfwMsg,
 Pst *pst
)
{
   S16 ret;

   ret = UeUiUetDatRsp(pst, tfwMsg);

   RETVALUE(ret);
}
