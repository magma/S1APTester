/********************************************************************20**

 
    Name:  LTE S1 SIM - Test FW Module 
 
    Type:  C include file
 
    Desc:  C source code for Test FW timers 
 
    File:  fw_tmr.c 
 
    Sid:      
 
    Prg:    
 
**********************************************************************/

/** header include files -- defines (.h) */
#include "envopt.h"        /* environment dependent */
#include "envdep.h"        /**< Environment dependent options */
#include "envind.h"
#include "gen.h"           /**< General Layer */
#include "ssi.h"
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
#include "fw_read_dflcfg.h"
#include "fw.h"
#include "fw_tmr.h"
#include "fw_log.h"

/** header/extern include files (.x) */
#include "gen.x"
#include "ssi.x"
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
#include "tmr_if.x"        /* Timer library defnintions */
#include "uet.x"
#include "nbt.x"
#include "lfw.x"
#include "fw_api_int.x"
#include "fw.x"
#include "fw_tmr.x"

PUBLIC FwCb gfwCb;
EXTERN S16 sendUeAttachFailIndToTstCntlr(FwCb *fwCb, UeIdCb *ueIdCb, U16 reason);
EXTERN S16 sendUePdnConnTimeOutIndToTstCntlr(FwCb *fwCb, UeIdCb *ueIdCb);
/*
*        Fun:  fwRegInitTmr 
*
*        Desc: Initialize the timer
*
*        Ret:   
* 
*        Notes: None
* 
*        File: fw_tmr.c 
* 
*/

PUBLIC S16  fwRegInitTmr
(
   FwCb *fwCb
)
{
   S16 ret = RFAILED;
   TmrConfig cfg;

   FW_LOG_ENTERFN(fwCb);

   cfg.tmrLen = FW_TQSIZE;
   cfg.tmrRes = (TmrRes)fwCb->tmrRes;
   ret = tmrRegister(ENTFW, 0, fwTmrMemAlloc, fwTmrMemFree, &cfg, &fwCb->regId);

   FW_LOG_EXITFN(fwCb, ret);
}


/*
*        Fun:   fwTmrMemAlloc
*
*        Desc:  Allocates the memory
*
*        Ret:   ROK
* 
*        Notes: None
* 
*        File: fw_tmr.c 
* 
*/
PUBLIC S16 fwTmrMemAlloc
(
   Data **ptr,
   Size size
)
{
   SGetSBuf(0, 0, (Data **)ptr, size);

   RETVALUE(ROK);
}


/*
*        Fun:  fwTmrMemFree
*
*        Desc:  Free the memory
*
*        Ret:   ROK
* 
*        Notes: None
* 
*        File: fw_tmr.c 
* 
*/
PUBLIC S16 fwTmrMemFree
(
   Data *ptr,
   Size size
)
{
   SPutSBuf(0, 0, (Data *)ptr, size);
   ptr = NULLP;

   RETVALUE(ROK);
}


/*
*        Fun:   
*
*        Desc:  .
*
*        Ret:   ROK
* 
*        Notes: None
* 
*        File: fw_tmr.c 
* 
*/
PUBLIC S16 fwDeregTmr
(
   FwCb  *fwCb
)
{
   S16 ret = ROK;

   FW_LOG_ENTERFN(fwCb);

   FW_LOG_DEBUG(fwCb, "Deregistering Timer");

   ret = tmrDeregister(fwCb->regId);
   if(ret != ROK)
   {
      FW_LOG_ERROR(fwCb, "Failed to Deregister the timer");
   }

   FW_LOG_EXITFN(fwCb, ret);
} /* fwRegInitTmr */


/*
*        Fun:  fwStartTmr 
*
*        Desc:  Start the timer
*
*        Ret:   
* 
*        Notes: None
* 
*        File: fw_tmr.c 
* 
*/
PUBLIC S16 fwStartTmr
(
 FwCb  *fwCb,
 UeIdCb  *ueIdCb,
 FwTmrExpHndlr waitTmrFun,
 U32   wait
)
{
   FwTmrCb *tmrCb = NULLP;
   TmrId *tmrId = NULLP;
   S16   ret = RFAILED;

   FW_LOG_ENTERFN(fwCb);

   FW_LOG_DEBUG(fwCb, "Starting timer");

   /* Allocate memory for timer control blocks */
   FW_ALLOC_MEM(fwCb, &tmrCb, sizeof(FwTmrCb));
   if (tmrCb == NULLP)
   {
      FW_LOG_ERROR(fwCb, "Memory allocation failed");
      FW_LOG_EXITFN(fwCb, RFAILED);
   }

   /* Storing the other control block in timer control block */
   tmrId = &tmrCb->tmrId;
   tmrCb->fwCb = fwCb;
   tmrCb->ueIdCb = ueIdCb;
   ueIdCb->tmrCb = tmrCb;

   ret = tmrStart(fwCb->regId, wait, waitTmrFun, (PTR)tmrCb, tmrId);
   FW_LOG_DEBUG(fwCb, "Timer started: tmrId[%d]", *tmrId);

   FW_LOG_EXITFN(fwCb, ret);
}

/*
*        Fun:   fwStopTmr
*
*        Desc:  Stop the timer
*
*        Ret:   ROK
* 
*        Notes: None
* 
*        File: fw_tmr.c 
* 
*/
PUBLIC Void fwStopTmr
(
   FwCb *fwCb,
   UeIdCb *ueIdCb
)
{
   FwTmrCb *tmrCb = NULLP;
   TmrId   tmrId = 0;

   FW_LOG_ENTERFN(fwCb);

   if (ueIdCb == NULLP)
   {
      FW_LOG_ERROR(fwCb, ("Invalid Parameters"));
      FW_LOG_EXITFNVOID(fwCb);
   }

   if (ueIdCb->tmrCb == NULLP)
   {
      FW_LOG_ERROR(fwCb, ("TmrCb is NULL"));
      FW_LOG_EXITFNVOID(fwCb);
   }

   tmrCb = ueIdCb->tmrCb;
   tmrId = tmrCb->tmrId;

   /* Stoping timer */
   FW_LOG_DEBUG(fwCb, "Stop timer: event = %d", tmrId);
   tmrStop(fwCb->regId, tmrId);
   FW_FREE_MEM(fwCb, ueIdCb->tmrCb, sizeof(FwTmrCb));

   FW_LOG_EXITFNVOID(fwCb);
} /* End of fwStopTmr */


/*
*        Fun:  fwHndlAttachTmrExp 
*
*        Desc:  Handles on timer expiry
*
*        Ret:   ROK
* 
*        Notes: None
* 
*        File: fw_tmr.c 
* 
*/
PUBLIC Void fwHndlAttachTmrExp
(
   PTR  cb
)
{
   FwCb *fwCb = NULLP;
   FwCb *tmrFwCb = NULLP;
   UeIdCb   *ueIdCb = NULLP;
   FwTmrCb  *tmrCb = NULLP;
   UetMessage *uetMsg = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   if (cb == NULLP)
   {
      FW_LOG_ERROR(fwCb, "Received Invalid Parameters");
      FW_LOG_EXITFNVOID(fwCb);
   }


   tmrCb = (FwTmrCb *)cb;
   tmrFwCb = tmrCb->fwCb;
   ueIdCb = tmrCb->ueIdCb;

   if ((NULLP == tmrFwCb) || (NULLP == ueIdCb))
   {
      FW_LOG_ERROR(fwCb, "Invalid parameters received");
      FW_LOG_EXITFNVOID(fwCb);
   }

   FW_LOG_ERROR(fwCb, "UE Attach timer expired (ue_id = %d)", ueIdCb->ue_id);

   /* Inform Stub with current state */
   FW_LOG_DEBUG(fwCb, "Sending indication to Test Controller");
   sendUeAttachFailIndToTstCntlr(tmrFwCb, ueIdCb, FW_RSN_UE_ATTACH_TIMER_EXPIRED);

   if (SGetSBuf(fwCb->init.region, fwCb->init.pool, 
            (Data **)&uetMsg, (Size) sizeof(UetMessage)) == ROK) 
   {                                                  
      cmMemset((U8 *)(uetMsg), 0,sizeof(UetMessage));              
   }
   else
   {
      return;
   }   
   uetMsg->msgType = UE_ATTACH_FAIL_TYPE;
   uetMsg->msg.ueUetAttachFail.ueId = ueIdCb->ue_id;
   FW_LOG_DEBUG(fwCb, "Sending indication to UeApp");
   fwSendToUeApp(uetMsg);

   FW_FREE_MEM(fwCb, ueIdCb->tmrCb, sizeof(FwTmrCb));

   FW_LOG_EXITFNVOID(fwCb);
} /* fwHndlAttachTmrExp */
/*
*        Fun:  fwHndlTauTmrExp 
*
*        Desc:  Handles on timer expiry
*
*        Ret:   ROK
* 
*        Notes: None
* 
*        File: fw_tmr.c 
* 
*/
PUBLIC Void fwHndlTauTmrExp
(
   PTR  cb
)
{
   FwCb *fwCb = NULLP;
   FwCb *tmrFwCb = NULLP;
   UeIdCb   *ueIdCb = NULLP;
   FwTmrCb  *tmrCb = NULLP;
   ueTauReq_t *tfwMsg = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   FW_LOG_ERROR(fwCb, "TAU Timer expired");
   if (cb == NULLP)
   {
      FW_LOG_ERROR(fwCb, "Received Invalid Parameters");
      FW_LOG_EXITFNVOID(fwCb);
   }


   tmrCb = (FwTmrCb *)cb;
   tmrFwCb = tmrCb->fwCb;
   ueIdCb = tmrCb->ueIdCb;

   if ((NULLP == tmrFwCb) || (NULLP == ueIdCb))
   {
      FW_LOG_ERROR(fwCb, "Invalid parameters received");
      FW_LOG_EXITFNVOID(fwCb);
   }
   FW_LOG_ERROR(fwCb, "UE TAU T3430 timer expired (ue_id = %d)", ueIdCb->ue_id);

   if (SGetSBuf(fwCb->init.region, fwCb->init.pool, 
            (Data **)&tfwMsg, (Size) sizeof(ueTauReq_t)) == ROK) 
   {                                                  
      cmMemset((U8 *)(tfwMsg), 0,sizeof(ueTauReq_t));              
   }
   else
   {
      return;
   } 
   tfwMsg->ue_Id = ueIdCb->ue_id;
   tfwMsg->type = ueIdCb->epsUpdType;
   tfwMsg->Actv_flag = ueIdCb->ActvFlag;
  
   /* Deleting node from linked list */ 
   FW_FREE_MEM(fwCb, ueIdCb->tmrCb, sizeof(FwTmrCb));
   cmLListDelFrm(&fwCb->ueIdList, &ueIdCb->link);
   FW_LOG_DEBUG(fwCb, "Retrying TAU Request to UeApp");
   handlTauReq(tfwMsg);

   FW_LOG_EXITFNVOID(fwCb);
} /* fwHndlTauTmrExp */

/*
*        Fun:  fwHndlPdnTmrExp 
*
*        Desc:  Handles on timer expiry
*
*        Ret:   ROK
* 
*        Notes: None
* 
*        File: fw_tmr.c 
* 
*/
PUBLIC Void fwHndlPdnTmrExp
(
   PTR  cb
)
{
   FwCb *fwCb = NULLP;
   FwCb *tmrFwCb = NULLP;
   UeIdCb   *ueIdCb = NULLP;
   FwTmrCb  *tmrCb = NULLP;

   FW_GET_CB(fwCb);
   FW_LOG_ENTERFN(fwCb);

   if (cb == NULLP)
   {
      FW_LOG_ERROR(fwCb, "Received Invalid Parameters");
      FW_LOG_EXITFNVOID(fwCb);
   }


   tmrCb = (FwTmrCb *)cb;
   tmrFwCb = tmrCb->fwCb;
   ueIdCb = tmrCb->ueIdCb;

   if ((NULLP == tmrFwCb) || (NULLP == ueIdCb))
   {
      FW_LOG_ERROR(fwCb, "Invalid parameters received");
      FW_LOG_EXITFNVOID(fwCb);
   }

   FW_LOG_ERROR(fwCb, "UE Pdn Connection timer expired (ue_id = %d)", ueIdCb->ue_id);

   /* Inform Stub with current state */
   FW_LOG_DEBUG(fwCb, "Sending indication to Test Controller");
   sendUeAttachFailIndToTstCntlr(tmrFwCb, ueIdCb, FW_RSN_UE_PDN_CON_TIMER_EXPIRED);
   FW_FREE_MEM(fwCb, ueIdCb->tmrCb, sizeof(FwTmrCb));

   FW_LOG_EXITFNVOID(fwCb);
} /* fwHndlPdnTmrExp */
