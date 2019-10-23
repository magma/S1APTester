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
#include "cm_tkns.x"
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
#include "fw_read_dflcfg.h"
#include "fw_api_int.x"
#include "nbt.x"
#include "fw.x"
#include "fw_tmr.x"
#include "fw_log.h"

#ifndef LWLCFWLIUET
PRIVATE S16 PtLiUetDatReq(Pst*, UetMessage*);
#endif
#ifndef LWLCFWLINBT
PRIVATE S16 PtLiNbtDatReq(Pst*, NbConfigReq*);
#endif
PRIVATE UetMsgReq FwLiUetDatReqMt[FW_MAX_UET_SEL] = \
{
#ifdef LWLCFWLIUET
   cmPkUetMsgReq,    /* 0 - lightweight loosely coupled */
#else
   PtLiUetDatReq,    /* 0 - loosely coupled, portable */
#endif
};

PRIVATE NbtReqHdl FwLiNbtDatReqMt[FW_MAX_NBT_SEL] = \
{
#ifdef LWLCFWLINBT
   cmPkNbtMsgReq,    /* 0 - lightweight loosely coupled */
#else
   PtLiNbtDatReq,    /* 0 - loosely coupled, portable */
#endif
};
/*
*        Fun:   FwLiUetDatReq
*
*        Desc:  .
*
*        Ret:   S16
* 
*        Notes: None
* 
*        File: fw_ptli.c 
* 
* 
*/

PUBLIC S16 FwLiUetDatReq
(
   Pst *pst,
   UetMessage *msg
)
{
   (*FwLiUetDatReqMt[pst->selector])(pst, msg);

   RETVALUE(ROK);
}
/*
*        Fun:   PtLiUetDatReq
*
*        Desc:  
*
*        Ret:   S16
* 
*        Notes: None
* 
*        File: fw_ptli.c
* 
* 
*/

#ifndef LWLCFWLIUET
PRIVATE S16 PtLiUetDatReq
(
   Pst* pst,
   UetMessage* msg
)
{
   return ROK;
}
#endif
/*
*        Fun:   FwLiNbtDatReq
*
*        Desc:  
*
*        Ret:   S16
* 
*        Notes: None
* 
*        File: fw_ptli.c
* 
* 
*/

PUBLIC S16 FwLiNbtDatReq
(
   Pst *pst,
   NbtRequest  *msg
)
{
   (*FwLiNbtDatReqMt[pst->selector])(pst, msg);

   RETVALUE(ROK);
}
/*
*        Fun:   PtLiNbtDatReq
*
*        Desc:  
*
*        Ret:   S16
* 
*        Notes: None
* 
*        File: fw_ptli.c
* 
* 
*/
#ifndef LWLCFWLINBT

PRIVATE S16 PtLiNbtDatReq
(
   Pst* pst,
   NbtRequest* msg
)
{
   return ROK;
}
#endif
