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
#include "ue.h"
#include "nbu.h"

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
#include "nbu.x"
#include "ue.x"
#include "ue_log.h"

PUBLIC S16 PtLiNbuDatReq(Pst*, NbuInitialUeMsg*);
PUBLIC S16 PtLiNbuUeInfo(Pst *pst, NbuUeIpInfoRsp *msg);
PUBLIC S16 PtLiNbuDatRsp(Pst *pst, NbuUlNasMsg* msg);
EXTERN S16 UeLiNbuInitialUeMsg(Pst *pst, NbuInitialUeMsg *msg);
EXTERN S16 UeLiNbuUlNasMsgDatRsp(Pst *pst, NbuUlNasMsg *msg);
EXTERN S16 UeLiNbuSendUeIpInfo(Pst *pst, NbuUeIpInfoRsp   *ueInfo);
EXTERN S16 UeLiNbuUlRrcMsgDatRsp(Pst *pst,NbuUlRrcMsg *msg);
EXTERN S16 UeLiNbuErabRelInd(Pst *pst,NbuErabRelIndList *msg);
PUBLIC S16 PtLiNbuErabRelInd(Pst *pst,NbuErabRelIndList *msg);

PRIVATE NbuUeIpInfoRspHdl UeLiNbuUlUeInfoMt[UE_MAX_NBU_SEL] = \
{
#ifdef LWLCFWLINBT
   cmPkNbuUeIpInfoRsp ,         /* 0 - loosely coupled */
#else
   PtLiNbuUeInfo         /* 1 - tightly coupled, portable */
#endif
};

PRIVATE NbuInitialUeMsgHdl UeLiNbuInitialUeMsgMt[UE_MAX_NBU_SEL] = \
{
#ifdef LWLCFWLINBT
   cmPkNbuInitialUeMsg,         /* 0 - loosely coupled */
#else
   PtLiNbuDatReq          /* 1 - tightly coupled, portable */
#endif
};
PRIVATE NbuErabRelIndHdl UeLiNbuErabRelIndMt[UE_MAX_NBU_SEL] = \
{
#ifdef LWLCFWLINBT
   cmPkNbuErabRelInd,         /* 0 - loosely coupled */
#else
   PtLiNbuErabRelInd          /* 1 - tightly coupled, portable */
#endif
};
PRIVATE NbuUlNasMsgHdl UeLiNbuUlNasMsgDatRspMt[UE_MAX_NBU_SEL] = \
{
#ifdef LWLCFWLINBT
   cmPkNbuUlNasMsg,         /* 0 - loosely coupled */
#else
   PtLiNbuDatRsp           /* 1 - tightly coupled, portable */
#endif
};

PRIVATE NbuUlRrcMsgHdl UeLiNbuUlRrcMsgDatRspMt[UE_MAX_NBU_SEL] = \
{
#ifdef LWLCFWLINBT
   cmPkNbuUlRrcMsg,         /* 0 - loosely coupled */
#else
      PtLiNbuDatRsp           /* 1 - tightly coupled, portable */
#endif
};
PUBLIC S16 PtLiNbuUeInfo
(
 Pst*     pst,
 NbuUeIpInfoRsp  *msg
)
{
   return ROK;
}

PUBLIC S16 PtLiNbuDatReq
(
 Pst              *pst,
 NbuInitialUeMsg  *msg
)
{
   return ROK;
}
PUBLIC S16 PtLiNbuErabRelInd
(
 Pst              *pst,
 NbuErabRelIndList *msg
)
{
   return ROK;
}
PUBLIC S16 PtLiNbuDatRsp
(
 Pst*     pst,
 NbuUlNasMsg  *msg
)
{
   return ROK;
}
PUBLIC S16 UeLiNbuInitialUeMsg
(
 Pst              *pst,
 NbuInitialUeMsg   *msg
)
{
   (*UeLiNbuInitialUeMsgMt[pst->selector])(pst, msg);

   RETVALUE(ROK);
}
PUBLIC S16 UeLiNbuErabRelInd
(
 Pst              *pst,
 NbuErabRelIndList   *msg
)
{
   (*UeLiNbuErabRelIndMt[pst->selector])(pst, msg);

   RETVALUE(ROK);
}
PUBLIC S16 UeLiNbuUlNasMsgDatRsp
(
 Pst              *pst,
 NbuUlNasMsg   *msg
)
{
   RETVALUE((*UeLiNbuUlNasMsgDatRspMt[pst->selector])(pst, msg));
}

PUBLIC S16 UeLiNbuUlRrcMsgDatRsp
(
 Pst              *pst,
 NbuUlRrcMsg   *msg
)
{
   (*UeLiNbuUlRrcMsgDatRspMt[pst->selector])(pst, msg);

   RETVALUE(ROK);
}

PUBLIC S16 UeLiNbuSendUeIpInfo
(
 Pst              *pst,
 NbuUeIpInfoRsp   *ueInfo
)
{
   (*UeLiNbuUlUeInfoMt[pst->selector])(pst, ueInfo);

   RETVALUE(ROK);
}
