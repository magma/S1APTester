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

EXTERN SmCb smCb;
#if 0
PRIVATE Void fwHndlUeEvnt(Pst *pst, Buffer *mBuf);
PRIVATE Void fwHndlNbEvnt(Pst *pst, Buffer *mBuf);
#endif
 
#if 0
PUBLIC S16 smActvTsk
(
   Pst      *pst,
   Buffer   *mBuf
)
{
   S16 ret = ROK;
   SM_LOG_ENTERFN(smCb);

   if (NULLP == pst || NULLP == mBuf)
   {
      if (mBuf != (Buffer *)NULLP)
      {
         (Void)SPutMsg(mBuf);
      }

      SM_LOG_ERROR(smCb, "NULL function parameters pst/mBuf");
      ret = RFAILED;
      SM_LOG_EXITFN(smCb, ret);
   }

   /**
    * identify source entity
    * basing on this handle the post structure appropriately
    */
   switch (pst->srcEnt)
   {
      default:
      {
         (Void)SPutMsg(mBuf);
         SM_LOG_ERROR(smCb, "Unhandled Event received from Module [%d]",\
                      pst->srcEnt);
         
         SM_LOG_EXITFN(smCb, RFAILED);

         break;
      }
   }

   SM_LOG_EXITFN(smCb, ret);
}

PRIVATE Void fwHndlUeEvnt(Pst *pst, Buffer *mBuf)
{
   SM_LOG_ENTERFN(smCb);

   switch (pst->event)
   {
      default:
      {
         SM_LOG_ERROR(smCb, "Unhandled Event received from FW [%d]",\
               pst->event);
         (Void)SPutMsg(mBuf);
         break;
      }
   }

   SM_LOG_EXITFNVOID(smCb);
}

PRIVATE Void fwHndlNbEvnt(Pst *pst, Buffer *mBuf)
{
   SM_LOG_ENTERFN(smCb);

   switch (pst->event)
   {
      default:
      {
         SM_LOG_ERROR(smCb, "Unhandled Event received from FW [%d]",\
               pst->event);
         (Void)SPutMsg(mBuf);
         break;
      }
   }

   SM_LOG_EXITFNVOID(smCb);
}
#endif
