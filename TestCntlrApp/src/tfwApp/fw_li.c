/********************************************************************20**

 
    Name:  LTE S1SIM - TFW
 
    Type:  C include file
 
    Desc:  C source code to send messages from TFW to UeApp/enbApp.
 
    File:  fw_li.c
 
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
#include  "cm_tkns.h"
#include "ss_queue.h"      /* queues */
#include "ss_task.h"       /* tasking */
#include "ss_msg.h"        /* messaging */
#include "ss_mem.h"        /* memory management interface */
#include "ss_gen.h"        /* general */
#include "rl_interface.h"
#include "rl_common.h"
#include "lfw.h"
#include "uet.h"
#include "nbt.h"
#include "fw.h"
#include "fw_tmr.h"

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
#include  "cm_tkns.x"
#include "ss_queue.x"      /* queues */
#include "ss_task.x"       /* tasking */
#include "ss_timer.x"      /* timers */
#include "ss_strm.x"       /* STREAMS */
#include "ss_msg.x"        /* messaging */
#include "ss_mem.x"        /* memory management interface */
#include "ss_drvr.x"       /* driver tasks */
#include "ss_gen.x"        /* general */
#include "lfw.x"
#include "uet.x"
#include "nbt.x"
#include "fw_read_dflcfg.h"
#include "fw_api_int.x"
#include "fw.x"
#include "fw_tmr.x"
#include "fw_log.h"

EXTERN FwCb gfwCb;

/*
*        Fun:   fwSendToNbApp
*
*        Desc:  function to send message from Tfw App to Enb App
*
*        Ret:   S16
* 
*        Notes: None
* 
*        File:  fw_li.c 
* 
* 
*/
PUBLIC S16 fwSendToNbApp(NbtMsg *nbMsg)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_LOG_DEBUG(fwCb, "Sending to EnodeB Application");
   FwLiNbtDatReq(&fwCb->nbPst, nbMsg);

   FW_LOG_EXITFN(fwCb, ret);
} /* fwSendToNbApp */

/*
*        Fun:   fwSendToUeApp
*
*        Desc:  Function to send message from Tfw App to UE App
*
*        Ret:   None
* 
*        Notes: None
* 
*.       File:  fw_li.c  
* 
* 
*/
PUBLIC S16 fwSendToUeApp(UetMessage *ueMsg)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_LOG_DEBUG(fwCb, "Sending to Ue Application");
   FwLiUetDatReq(&fwCb->uePst, ueMsg);

   FW_LOG_EXITFN(fwCb, ret);
} /* fwSendToUeApp */
