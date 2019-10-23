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

#if 0
#ifndef LWLCFWMILFW
PRIVATE S16 PtMiFwCfgCfm (Pst *pst, FwMngmt * cfm);
PRIVATE S16 PtMiFwCntrlCfm (Pst *pst, FwMngmt *cfm);
#endif

/* Array to choose functions based on selector value */
PRIVATE CONSTANT LfwCfgCfm FwMiLfwCfgCfmMt[FW_MAX_LFW_SEL] =
{
#ifdef LWLCFWMILFW
   cmPkLfwCfgCfm,    /* Light weight loosely coupled */
#else
   PtMiFwCfgCfm
#endif
};

PRIVATE CONSTANT LfwCntrlCfm FwMiLfwCntrlCfmMt[FW_MAX_LFW_SEL] =
{
#ifdef LWLCFWMILFW
   cmPkLfwCntrlCfm,  /* Light weight loosely coupled */
#else
   PtMiFwCntrlCfm
#endif
};

PUBLIC S16 FwMiLfwCfgCfm
(
   Pst     *pst,
   FwMngmt *cfm
)
{
   S16   ret = ROK;

   /* Call specific primitive depending on configured selector */
   ret = (*FwMiLfwCfgCfmMt[pst->selector])(pst, cfm);

   RETVALUE(ret);
} /* FwMiLfwCfgCfm */

PUBLIC S16 FwMiLfwCntrlCfm
(
   Pst     *pst,
   FwMngmt *cfm
)
{
   S16   ret = ROK;

   /* Call specific primitive depending on configured selector */
   ret = (*FwMiLfwCntrlCfmMt[pst->selector])(pst, cfm);

   RETVALUE(ret);
} /* FwMiLfwCntrlCfm */

#ifndef LWLCFWMILFW
PRIVATE S16 PtMiFwCfgCfm
(
   Pst     *pst,
   FwMngmt *cfm
)
{
   S16   ret = ROK;

   UNUSED(pst);
   UNUSED(cfm);

   RETVALUE(ret);
} /* PtMiFwCfgCfm */

PRIVATE S16 PtMiFwCntrlCfm
(
   Pst     *pst,
   FwMngmt *cfm
)
{
   S16   ret = ROK;

   UNUSED(pst);
   UNUSED(cfm);

   RETVALUE(ret);
} /* PtMiFwCntrlCfm */
#endif
#endif
