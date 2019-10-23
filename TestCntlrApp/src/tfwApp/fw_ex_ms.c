/********************************************************************20**

 
    Name:  LTE S1SIM - TFW
 
    Type:  C include file
 
    Desc:  C source code to receive and Process Messages from other modules.
 
    File:  fw_ex_ms.c
 
    Sid:   
 
    Prg:   
 
**********************************************************************/

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
#include "uet.h"
#include "nbt.h"
#include "lfw.h"
#include "fw.h"
#include "fw_tmr.h"
#include "fw_api_int.h"

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
#include "uet.x"
#include "nbt.x"
#include "lfw.x"
#include "fw_read_dflcfg.h"
#include "fw_api_int.x"
#include "fw.x"
#include "fw_tmr.x"
# include "fw_sm.x"
#include "fw_log.h"

PUBLIC FwCb gfwCb;

PRIVATE S16 fwHandleEvtFromSm(Pst *, Buffer *);
PRIVATE S16 fwHandleEvtFromUe(Pst *, Buffer *);
PRIVATE S16 fwHandleEvtFromEnodeB(Pst *, Buffer *);

/*
*        Fun:   fwActvTsk
*
*        Desc:  Receives and Process Messages from other modules
*
*        Ret:   ROK
* 
*        Notes: None
* 
*        File:  fw_ex_ms.c  
* 
*/ 
PUBLIC S16 fwActvTsk
(
 Pst    *pst,
 Buffer *mBuf
)
{
   S16   ret = ROK;
   FwCb  *fwCb = NULLP;

   FW_GET_CB(fwCb);

   FW_LOG_ENTERFN(fwCb);

   if (NULLP == pst || NULLP == mBuf)
   {
      FW_LOG_ERROR(fwCb, "recieved NUll parameter in pst or mBuf");
      FW_LOG_EXITFN(fwCb, RFAILED);
   }

   /* Check from which entity message came */
   switch (pst->srcEnt)
   {
      /* Event from Stack Manager */
      case ENTSM:
      {
         /* Check the event type from stack manager */
         FW_LOG_DEBUG(fwCb, "Received Data from Stack Manager");
         ret = fwHandleEvtFromSm(pst, mBuf);
         break;
      }
      case ENTUE:
      {
         FW_LOG_DEBUG(fwCb, "Received Data from UE App");
         /* Check the event type from UE App */
         ret = fwHandleEvtFromUe(pst, mBuf);
         break;
      }
      case ENTNB:
      {
         FW_LOG_DEBUG(fwCb, "Received Data from EnodeB App");
         /* Check the event type from Xn App */
         ret = fwHandleEvtFromEnodeB(pst, mBuf);
         break;
      }
      default:
      {
         FW_LOG_ERROR(fwCb, "Event Received from Invalid Entity Failed");
         SPutMsg(mBuf);
         ret = RFAILED;
         break;
      }
   }

   SExitTsk();
   FW_LOG_EXITFN(fwCb, ret);
} /* End of fwActvTsk */


/*
*        Fun:   fwHandleEvtFromSm
*
*        Desc:  Handles event coming from Stack manages
*
*        Ret:   ROK
* 
*        Notes: None
* 
*        File: fw_ex_ms.c 
* 
*/ 
PRIVATE S16 fwHandleEvtFromSm
(
 Pst    *pst,
 Buffer *mBuf
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;
   FW_GET_CB(fwCb);

   FW_LOG_ENTERFN(fwCb);
   switch (pst->event)
   {
      default:
      {
         /* Process a config. request */
         FW_LOG_ERROR(fwCb, "Invalid event from Stack Manager");
         SPutMsg(mBuf);
         FW_LOG_EXITFN(fwCb, RFAILED);
         break;
      }
   }

   FW_LOG_EXITFN(fwCb, ret);
} /* fwHandleEvtFromSm */


/*
*        Fun:   fwHandleEvtFromUe
*
*        Desc:  Handles event coming from UE App
*
*        Ret:   ROK
* 
*        Notes: None
* 
*        File: fw_ex_ms.c
* 
*/ 
PRIVATE S16 fwHandleEvtFromUe
(
 Pst    *pst,
 Buffer *mBuf
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   switch (pst->event)
   {
      case EVTUEMSGRSP:
      {
         FW_LOG_DEBUG(fwCb, "Recieved Message from UeApp");
         cmUnpkUetMsgRsp(handleMessageFromUeApp, pst, mBuf);
         break;
      }
      default:
      {
         /* Process a config. request */
         FW_LOG_ERROR(fwCb, "Received Invalid event from Ue");
         SPutMsg(mBuf);
         FW_LOG_EXITFN(fwCb, RFAILED);
         break;
      }
   }
   FW_LOG_EXITFN(fwCb, ret);
} /* fwHandleEvtFromUe */

/*
*        Fun:   fwHandleEvtFromEnodeB
*
*        Desc:  Handles event coming from eNodeB App
*
*        Ret:   ROK
* 
*        Notes: None
* 
*        File:  fw_ex_ms.c
* 
*/ 
PRIVATE S16 fwHandleEvtFromEnodeB
(
 Pst    *pst,
 Buffer *mBuf
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;

   FW_GET_CB(fwCb);

   FW_LOG_ENTERFN(fwCb);

   switch (pst->event)
   {
      case EVTNBTMSGRSP:
      {
         FW_LOG_DEBUG(fwCb, "Recieved response from ENB App");
         cmUnPkNbtMsgRsp(handleNbAppMsg, pst, mBuf);
         break;
      }
      default:
      {
         /* Process a config. request */
         FW_LOG_ERROR(fwCb, "Received Invalid event from Nb App");
         SPutMsg(mBuf);
         FW_LOG_EXITFN(fwCb, RFAILED);
         break;
      }
   }
   FW_LOG_EXITFN(fwCb, ret);
} /* fwHandleEvtFromEnodeB */
