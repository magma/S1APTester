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
#include "fw_tst.h"
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
#include "nbt.x"
#include "fw_read_dflcfg.h"
#include "fw_api_int.x"
#include "fw.x"
#include "fw_tmr.x"
#include "fw_log.h"
#include "fw_sm.x"

EXTERN FwCb gfwCb;
/*
*        Fun:   fwActvInit
*
*        Desc:  Initialize the Pst structure, init structure.
*
*        Ret:   S16
* 
*        Notes: None
* 
*        File:  
* 
* 
*/

PUBLIC S16 fwActvInit
(
   Ent      entity,
   Inst     inst,
   Region   region,
   Reason   reason
)
{
   S16 ret = ROK;
   FwCb *fwCb = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_LOG_DEBUG(fwCb, "Doing fwActvInit");

   fwCb->init.ent = entity;
   fwCb->init.inst = inst;
   fwCb->init.region = region;
   fwCb->init.reason = reason;
   fwCb->init.cfgDone = FALSE;
   fwCb->init.pool = 0;
   fwCb->init.acnt = FALSE;
   fwCb->init.trc = FALSE;
   fwCb->init.usta = TRUE;
#ifdef DEBUGP
   fwCb->init.dbgMask = LFW_LOGLVL_TRACE;
#endif
   fwCb->uePst.srcInst   = FW_INST_ID;
   fwCb->uePst.srcEnt    = fwCb->init.ent;
   fwCb->uePst.srcProcId = fwCb->init.procId;
   fwCb->uePst.region    = fwCb->init.region;
   fwCb->uePst.pool      = fwCb->init.pool;
   fwCb->uePst.dstEnt    = ENTUE;
   fwCb->uePst.dstInst   = UE_INST_ID;
   fwCb->uePst.selector  = UET_SEL_LWLC;
   fwCb->uePst.dstProcId = SFndProcId();

   fwCb->nbPst.srcInst   = FW_INST_ID;
   fwCb->nbPst.srcEnt    = fwCb->init.ent;
   fwCb->nbPst.srcProcId = fwCb->init.procId;
   fwCb->nbPst.region    = fwCb->init.region;
   fwCb->nbPst.pool      = fwCb->init.pool;
   fwCb->nbPst.dstEnt    = ENTNB;
   fwCb->nbPst.dstInst   = NB_INST_ID;
   fwCb->nbPst.selector  = NBT_SEL_LWLC;
   fwCb->nbPst.dstProcId = SFndProcId();

   fwCb->ueState = UE_DEREGISTERED;

   cmMemset((U8*)&fwCb->tfwCfgCb, 0, sizeof(TfwAppCfgCb));
   cmMemset((U8*)&fwCb->ueAppCfgCb, 0, sizeof(UeAppCfgCb));
   cmMemset((U8*)&fwCb->nbAppCfgCb, 0, sizeof(NbAppCfgCb));
   cmMemset((U8*)&fwCb->ueCfgCb, 0, sizeof(UeCfgCb));
  
   cmLListInit(&fwCb->ueIdList);

   fwCb->tmrRes = 10; /* TODO : should come from SM in genCfg */
   /* Initilize the timers */
   ret = fwRegInitTmr(fwCb);
   if (ret != ROK)
   {
      FW_LOG_ERROR(fwCb,"Timer Registration failed");
      FW_LOG_EXITFN(fwCb, RFAILED);
   }

   readDfltCfgs();
   FW_LOG_DEBUG(fwCb, "Fw task initialized");
   FW_LOG_EXITFN(fwCb, ret);
} /* fwActvInit */
