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
#include "ss_strm.h"       /* STREAMS */
#include "ss_task.h"       /* tasking */
#include "ss_msg.h"        /* messaging */
#include "ss_mem.h"        /* memory management interface */
#include "ss_gen.h"        /* general */
#include "rl_interface.h"
#include "rl_common.h"
#include "fw_tst.h"
#include "fw_sm.h"
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
#include "fw_sm.x"
#include "lfw.x"
#include "fw_sm_log.h"

PUBLIC SmCb smCb;

#if 0
PUBLIC S16 smActvInit
(
   Ent ent,
   Inst inst,
   Region region,
   Reason reason
)
{
   U16 ret = ROK;

   SM_LOG_ENTERFN(smCb);
   cmMemset((U8 *)&smCb, 0, sizeof(smCb));
   smCb.init.ent     = ENTSM;
   smCb.init.inst    = inst;
   smCb.init.region  = region;
   smCb.init.reason  = reason;
   smCb.init.cfgDone = FALSE;
   smCb.init.pool    = 0;
   smCb.init.acnt    = FALSE;
   smCb.init.trc     = FALSE;
   smCb.init.usta    = TRUE;
   smCb.init.dbgMask = LFW_LOGLVL_TRACE;

   SM_LOG_EXITFN(smCb, ret);
}
#endif
