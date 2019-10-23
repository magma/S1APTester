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
#include "ue.x"
#include "ue_log.h"

PUBLIC S16 PtUiUetDatReq(Pst*, UetMessage*);
PUBLIC S16 PtUiUetDatRsp(Pst*, UetMessage*);
PUBLIC S16 UeUiUetDatRsp(Pst*, UetMessage*);

PRIVATE UetMsgRsp UeUiUetDatRspMt[UE_MAX_UET_SEL] = \
{
#ifdef LWLCFWLIUET
   cmPkUetMsgRsp,         /* 0 - loosely coupled */
#else
   PtUiUetDatRsp          /* 1 - tightly coupled, portable */
#endif
};

PUBLIC S16 PtUiUetDatRsp
(
 Pst*     pst,
 UetMessage*  msg
)
{
   return ROK;
}

PUBLIC S16 UeUiUetDatRsp
(
 Pst         *pst,
 UetMessage  *msg
)
{
   (*UeUiUetDatRspMt[pst->selector])(pst, msg);

   RETVALUE(ROK);
}

PUBLIC S16 PtUiUetDatReq
(
 Pst*     pst,
 UetMessage*  msg
 )
{
   return ROK;
}
