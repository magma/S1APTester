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
#include "lfw.h"
#include "uet.h"
#include "nbu.h"
#include "fw.h"

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
#include "lfw.x"
#include "uet.x"
#include "nbu.x"
#include "fw_read_dflcfg.h"
#include "fw.x"
#include "fw_log.h"

EXTERN FwCb gfwCb;
#if 0
/*
*        Fun:   handleNbAppMsg
*
*        Desc:  Handles the Enb Config Request
*
*        Ret:   S16
* 
*        Notes: None
* 
*        File:  
* 
* 
*/

PUBLIC S16 handleNbAppMsg
(
 Pst *pst,
 NbConfigReq *nbRspMsg
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   /*TODO: */

   FW_LOG_EXITFN(fwCb, ret);
}
#endif
