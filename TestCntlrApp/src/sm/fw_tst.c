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
SSTskId smTskId; /** This system task id is used for Stack manager */
SSTskId fwTskId; /** This system task id used by TFW APP */
SSTskId ueTskId; /** This system task id used by UE APP */

/* Function prototypes */
EXTERN S16 smActvTsk(Pst*, Buffer*);
PRIVATE S16 fwCreateNAttachTskForFw(Void);
PRIVATE S16 fwCreateNAttachTskForSM(Void);
PRIVATE S16 fwCreateNAttachTskForUE(Void);
PRIVATE Void fwLogInit(Void);
PRIVATE S16 createNAttachTsks(Void);
PUBLIC S16 smNbInit(SSTskId sysTskId);
PUBLIC S16 smSzInit(SSTskId sysTskId);
PUBLIC S16 smEgInit(SSTskId sysTskId);
PUBLIC S16 smEuInit(SSTskId sysTskId);
PUBLIC S16 smSbInit(SSTskId sysTskId);
PUBLIC S16 smHiInit(SSTskId sysTskId);
/*
*
*       Fun:   tst
*
*       Desc:  tst entry point. First entry point.
*
*       Ret:   ROK on success, RFAILED on error
*
*       Notes: None
*
*       File:  nb_smm_init.c
*
*/
#ifdef ANSI
PUBLIC S16 tst
(
Void
)
#else
PUBLIC S16 tst(Void)
#endif
{
   SSTskId egtp_dat_app_taskId;
   SSTskId sctp_taskId;
   SSTskId s1ap_taskId;
   SSTskId sm_taskId;
   SSTskId tucl_taskId;
   SSTskId enbapp_taskId;
   #if 0
   U16 smEvent;
   #endif
   TRC2(tst)
   SSetProcId(SM_SM_PROC);

   /* 1> create the tasks and attach for enbapp,sctp,s1ap,tucl,etgpu */

   fwLogInit();
   createNAttachTsks();
   SCreateSTsk(PRIOR0, &enbapp_taskId); 
   SCreateSTsk(PRIOR0, &sm_taskId); 
   SCreateSTsk(PRIOR0, &egtp_dat_app_taskId);
   tucl_taskId = egtp_dat_app_taskId;
   s1ap_taskId = sctp_taskId = enbapp_taskId;
   if(smNbInit(enbapp_taskId) != ROK )
   {
      printf("\nApp Tapa Task initialization failed\n");
      RETVALUE(RFAILED);
   } /* end of if statement */ 
   if(smSzInit(s1ap_taskId) != ROK )
   {
      printf("\nS1AP Tapa Task initialization failed\n");
      RETVALUE(RFAILED);
   } /* end of if statement */
   /* Create EGTP and EGTP APP TAPA tasks and attach them 
    *       to a single system thread */
   if(smEgInit(egtp_dat_app_taskId) != ROK)
   {
      printf("EGTP Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */
#if 1 
   if(smEuInit(egtp_dat_app_taskId) != ROK)
   {
      printf("\nEGTP Data APP Tapa Task initialization failed\n");
      RETVALUE(RFAILED);
   } /* end of if statement */
#endif /* EU_DAT_APP */
   /* Create SCTP TAPA tasks and attach them to system thread */
   if(smSbInit(sctp_taskId) != ROK)
   {
      printf("\nSCTP Tapa Task initialization failed\n");
      RETVALUE(RFAILED);
   } /* end of if statement */

   /* Create TUCL TAPA task and attach them to system threads */
   if(smHiInit(tucl_taskId) != ROK)
   {
      printf("\nTUCL Tapa Task initialization failed\n");
      RETVALUE(RFAILED);
   }
   /* Create the SM TAPA task */
   SRegTTsk(ENTSM, (Inst) 0, TTNORM, PRIOR0, (PAIFS16)smActvInit, smActvTsk);
   SAttachTTsk(ENTSM, (Inst) 0, sm_taskId);

   /* initialize the default parameters and polulate the strcture,nbcb,nbcfgcb */
#if 0
   smEvent = EVTNBTUCLCFG;
   smCfgCb.smState = NB_SM_STATE_INIT;
   /* trigger the state machine for configuration */
   smNbProcSm(smEvent);
#endif
   RETVALUE(ROK);
} /* tst */

/**
 * @brief   createNAttachTsks
 *
 * @details  creates and attaches different Task.
 *
 * @param [in][in] void
 *
 * @return 
 *    
 */

PRIVATE S16 createNAttachTsks
(
   Void
)
{
   U16 ret = ROK;

   SM_LOG_ENTERFN(smCb);
   /**
    * creating system task and registering Tapa task for TFW-APP interface 
    */
   if((ret = fwCreateNAttachTskForFw()) != ROK)
   {
      ret = RFAILED;
      SM_LOG_EXITFN(smCb, ret);
   }

   /**
    * creating system task and registering Tapa task for SM interface 
    */
   if((ret = fwCreateNAttachTskForSM()) != ROK)
   {
      ret = RFAILED;
      SM_LOG_EXITFN(smCb, ret);
   }

   if((ret = fwCreateNAttachTskForUE()) != ROK)
   {
      ret = RFAILED;
      SM_LOG_EXITFN(smCb, ret);
   }
   SM_LOG_EXITFN(smCb, ret);
} /* end of createNAttachTsks */

/**
 * @brief   tfwCreateNAttachTskForTfw creates system and tapa task
 *
 * @details  creates system task and TAPA task for TFW Application,
 *          and attaches the TAPA task to this system task.
 *
 * @param [in][in] void
 *
 * @return S16  ROK      : On Success
 *              RFAILED  : On Failure
 */
PRIVATE S16 fwCreateNAttachTskForFw()
{
   S16 ret = ROK;

    /* Registration of TAPA task for TFW Application */
   if (SRegTTsk(ENTFW, FW_INST_ID, TTNORM, PRIOR0,
                 fwActvInit, fwActvTsk) != ROK)

   {
      SM_LOG_ERROR(smCb, "tst: SRegTTsk failed for TA");
      ret = RFAILED;
      SM_LOG_EXITFN(smCb, ret);
   }
   /* Create system task for TFW Application */
   if (SCreateSTsk(SS_NORM_TSK_PRI, &fwTskId) != ROK)
   {
      SM_LOG_ERROR(smCb, "tst: SCreateSTsk failed for TWF App");
      ret = RFAILED;
      SM_LOG_EXITFN(smCb, ret);
   }

    /* Attaching TAPA & system tasks */
   if (SAttachTTsk(ENTFW, FW_INST_ID, fwTskId) != ROK)
   {
      SDestroySTsk(fwTskId);
      SM_LOG_ERROR(smCb, "tst: SAttachTTsk failed for TFW instance Id");
      ret = RFAILED;
      SM_LOG_EXITFN(smCb, ret);
   }
   SM_LOG_DEBUG(smCb, "created system task and attached for TFW");
   SM_LOG_EXITFN(smCb, ret);
} /* End of tfwCreateNAttachTskForTfw */

/**
 * @brief fwCreateNAttachTskForSM creates tapa and system task.
 *
 * @details fwCreateNAttachTskForSM function  creates SM task and
 *         attaches to the stack manager system task
 *
 * @param[in][in] void
 *
 * @return
 */

PRIVATE S16 fwCreateNAttachTskForSM()
{
   U16 ret = ROK;
   SM_LOG_ENTERFN(smCb);
   /* Stack manager registration */
   if (SRegTTsk (ENTSM, SM_INST_ID, TTNORM,PRIOR0, smActvInit,
            smActvTsk) != ROK)
   {
      SM_LOG_ERROR(smCb, "tst: SRegTTsk failed for StackManager");
      ret = RFAILED;
      SM_LOG_EXITFN(smCb, ret);
   }
   
   /* Create system task for stack manager */
   if (SCreateSTsk(SS_NORM_TSK_PRI, &smTskId) != ROK)
   {
      SM_LOG_ERROR(smCb, "tst: SCreateSTsk failed for Stack manager");
      ret = RFAILED;
      SM_LOG_EXITFN(smCb, ret);
   }

   /* Attaching SM TAPA task to SM System task */
   if (SAttachTTsk(ENTSM, SM_INST_ID, smTskId) != ROK)
   {
      SM_LOG_ERROR(smCb, "tst:SAttachTTsk failed for SM");
      SDestroySTsk(fwTskId);
      SDestroySTsk(smTskId);
      ret = RFAILED;
      SM_LOG_EXITFN(smCb, ret);
   }

   SM_LOG_DEBUG(smCb, "tst:SM(Stack manager), SYSTEM task creation and "\
         "attachment were done");
   SM_LOG_EXITFN(smCb, ret);
}/* end of fwCreateNAttachTskForSM() */

PRIVATE S16 fwCreateNAttachTskForUE(Void)
{
   U16 ret = ROK;

   SM_LOG_ENTERFN(smCb);

    /* Creating a system task*/
   if (SCreateSTsk(SS_NORM_TSK_PRI, &ueTskId) != ROK)
   {
      SM_LOG_ERROR(smCb, "tst: SCreateSTsk failed for UE");
      ret = RFAILED;
      SM_LOG_EXITFN(smCb, ret);
   }

    /* Creating TAPA task for UE */
   if (SRegTTsk(ENTUE, UE_INST_ID, TTNORM, PRIOR0,
                 ueActvInit, ueActvTsk) != ROK)
   {
      SM_LOG_ERROR(smCb, "tst: SRegTTsk failed for UE");
      ret = RFAILED;
      SM_LOG_EXITFN(smCb, ret);
   }

    /* Attaching TAPA & system tasks for UE */
   if (SAttachTTsk(ENTUE, UE_INST_ID, ueTskId) != ROK)
   {
      SDestroySTsk(fwTskId);
      SDestroySTsk(smTskId);
      SDestroySTsk(ueTskId);
      SM_LOG_ERROR(smCb, "tst: SAttachTTsk failed for UE Application");
      ret = RFAILED;
      SM_LOG_EXITFN(smCb, ret);
   }
   SM_LOG_DEBUG(smCb, "created system task and attached for UE");
   SM_LOG_EXITFN(smCb, ret);
} /* fwCreateNAttachTskForUE */

/**
 * @brief   fwLogInit 
 *
 * @details Rlog Frame work initializing
 *
 * @return Void 
 */
PUBLIC Void fwLogInit()
{
   U8 logPath[50];
   U8 file[50];
   strcpy((char*)logPath, FW_LOG_PATH);
   strcpy((char*)file, "fw.txt");
   rlSetLogPath((const char*)logPath);
   rlSetLogFile((const char*) file);
   rlSetLogLevel((R_LOG_LEVEL)0);
   rlSetModuleMask(1);
   rlSetLogFileSizeLimit(10);
   rlSetNumOfLogFiles(5);

#ifdef RLOG_USE_CIRCULAR_BUFFER
   rlSetCircularBufferSize(1024);
#endif

   rlInitLog(CM_TPTADDR_IPV4);

   RETVOID;
}
