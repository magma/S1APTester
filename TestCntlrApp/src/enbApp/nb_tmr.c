/**********************************************************************

    Name:  LTE S1SIM - ENODEB Application Module 

    Type:  C include file

    Desc:  C source code for UE Application
               
    File:  nb_tmr.c

    Sid:   

    Prg:   

**********************************************************************/

/* Header include files (.h) */
#include "ssi.h"
#include "nb.h" 
#include "rl_interface.h"
#include "rl_common.h"
#include "nb_log.h"
/* End - Fix for ccpu00123981 */
PRIVATE Void nbProcTmr (Ptr cb, S16 tmrEvnt);

/** @brief This function registers and initializes the timer
 *         queue structures in LTE eNodeB during general config.
 *
 * @details
 *
 *     Function: wrRegInitTmr
 *
 *         Processing steps:
 *
 * @param[in] Void 
 * @return S16
 *        -# Success : ROK
 */
PUBLIC S16 nbRegInitTmr
(
Void
)
{
   U16                       idx;
   S16                       ret;

   ret = SRegTmr((Ent)ENTNB, (Inst)0, nbCb.timeRes, nbActvTmr);
   if (ret != ROK)
   {
      NB_LOG_ERROR(&nbCb,"SRegTmr Failed");
      RETVALUE(RFAILED);
   }

   /* initialize timing queues */
   nbCb.tqCp.tmrLen      = NB_NUM_TQENTRY;

   for (idx = 0; idx < NB_NUM_TQENTRY; idx++)
   {
      nbCb.tq[idx].first    = NULLP;
      nbCb.tq[idx].tail     = NULLP;
   }

   RETVALUE(ROK);

} /* nbRegInitTmr */


/** @brief Invoked by system services to activate a task with
 *              a timer tick.
 *
 * @details
 *
 *     Function: wrActvTmr
 *
 *         Processing steps:
 *
 * @param[in] Void 
 * @return S16
 *        -# Success : ROK
 */

PUBLIC S16 nbActvTmr
(
 Void
)
{
   cmPrcTmr(&nbCb.tqCp, nbCb.tq, (PFV) nbProcTmr);

   RETVALUE(ROK);
} /* end of nbActvTmr */


/** @brief This function is used to start a given timer. 
 *
 * @details
 *
 *     Function: nbStartTmr
 *
 *         Processing steps:
 *               This function based upon the timer event, derives the TimerCB 
 *               and adds it to the timer queue.
 *
 * @param[in] Cb : This holds approriate Control block for the timer event passed. 
 * @param[in] tmrEvent : One of the many possible timer types. 
 * @param[in] delay : Duration of the timer.
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 nbStartTmr
(
PTR                          cb,
S16                          tmrEvnt,
U32                          delay
)
{
   U32                       wait;
   CmTmrArg                  arg;
   CmTimer                   *tmr;
   U8                        maxTmrs;
   NbLiSapCb                 *sapCb = NULLP;
   U32                       idx;
   NbMmeCb                   *mmeCb  = NULLP;
   NbUeCb                    *ueCb   = NULLP;
   NbDelayICSRspCb *icsRspCb = NULLP;
   NbDelayUeCtxtRelCmpCb *ueCtxRelCmp = NULLP;
 
   wait = 0;
   wait = NB_CALC_WAIT_TIME(delay);
   switch (tmrEvnt)
   {
      /* For SZT Bind Timer Timer */
      case NB_TMR_SZT_SAP_BND:
      case NB_TMR_EGT_SAP_BND:
      {
         sapCb = ( NbLiSapCb*)cb;
         tmr      = &sapCb->timer;
         maxTmrs  = 1;
         break;
      }
      case NB_TMR_MME_SETUP_RSP:
      {
         mmeCb = (NbMmeCb *)cb;
         tmr = &mmeCb->timer;
         maxTmrs = 1;
         break;
      }
      case NB_TMR_MME_SETUP_WAIT:
      {
         mmeCb = (NbMmeCb *)cb;
         tmr = &mmeCb->timer;
         maxTmrs = 1;
         break;
      }
      case NB_TMR_LCL_UE_CTXT_REL_REQ:
      {
         ueCb = (NbUeCb *)cb;
         tmr =&(nbCb.dropInitCtxtSetup[(ueCb->ueId) - 1].timer);
         maxTmrs = 1;
         break;
      }
      case NB_TMR_DELAY_ICS_RSP:
      {
         icsRspCb = (NbDelayICSRspCb *)cb;
         tmr = &icsRspCb->timer;
         maxTmrs = 1;
         break;
      }
      case NB_TMR_DELAY_UE_CTX_REL_COMP:
      {
         ueCtxRelCmp = (NbDelayUeCtxtRelCmpCb *)cb;
         tmr = &ueCtxRelCmp->timer;
         maxTmrs = 1;
         break;
      }
      default:
      {
         NB_LOG_ERROR(&nbCb,"Invalid Timer event [%d] received", tmrEvnt);
         RETVALUE(RFAILED);
      }
   } /* end of switch */

   for(idx = 0; idx < maxTmrs; idx++)
   {
      if (tmr[idx].tmrEvnt == TMR_NONE)
      {
         break;
      }
   }
   if (idx >= maxTmrs)
   {
      RETVALUE(RFAILED);
   }

   /* initialize argument for common timer function */
   if(wait != 0)
   {
      arg.tqCp   = &(nbCb.tqCp);
      arg.tq     = nbCb.tq;
      arg.cb     = cb;
      arg.timers = tmr;
      arg.evnt   = tmrEvnt;
      arg.wait   = wait;
      arg.tNum   = 0;
      arg.max    = maxTmrs;

      cmPlcCbTq(&arg);
   }

   RETVALUE(ROK);
} /* end of nbStartTmr() */


/** @brief This function is used to stop a previously running timer. 
 *
 * @details
 *
 *     Function: nbStopTmr
 *
 *         Processing steps:
 *               This function based upon the timer event reterives relevant timerCb and 
 *               tries to determine whether timer is running or not.In case timer 
 *               was running, it is stopped .
 *
 * @param[in] Cb : This holds approriate Control block for the timer event passed. 
 * @param[in] tmrEvent : One of the many possible timer types. 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC Void nbStopTmr
(
PTR                          cb,
S16                          event
)
{
   CmTmrArg                  arg;
   U8                        idx;
   Bool                      tmrRunning;
   CmTimer                   *timers = NULLP;
   U8                        max = 0;
   NbLiSapCb                 *sapCb;

   idx = 0;

   tmrRunning = FALSE;
   switch(event)
   {
      case NB_TMR_SZT_SAP_BND:
      case NB_TMR_EGT_SAP_BND:
      {
         sapCb = (NbLiSapCb*)cb;
         max     =  1;
         if(sapCb->timer.tmrEvnt == event)
         {
            tmrRunning = TRUE;
            sapCb->bndRetryCnt = 0;
         }
         timers = &sapCb->timer;
         break;
      }
      case NB_TMR_MME_SETUP_RSP:
      {
         NbMmeCb             *mmeCb = (NbMmeCb *)cb;
         timers = &mmeCb->timer;
         max    = 1;
         if (mmeCb->timer.tmrEvnt == event)
         {
            tmrRunning = TRUE;
         }
         break;
      }
      case NB_TMR_MME_SETUP_WAIT:
      {
         NbMmeCb             *mmeCb = (NbMmeCb *)cb;
         timers = &mmeCb->timer;
         max    = 1;
         if (mmeCb->timer.tmrEvnt == event)
         {
            tmrRunning = TRUE;
         }
         break;
      }
      default:
         break;
   }
   if(tmrRunning == FALSE)
   {
      RETVOID;
   }

   /* initialize argument for common timer function */
   arg.tqCp    = &nbCb.tqCp;
   arg.tq      = nbCb.tq; 
   arg.timers  = timers;
   arg.cb      = cb;
   arg.evnt    = event;
   arg.wait    = 0;
   arg.max     = max;
   arg.tNum    = idx;
   cmRmvCbTq(&arg);

   RETVOID;
} /* end of nbStopTmr() */


/** @brief This function handles timer expiry. 
 *
 * @details
 *
 *     Function: nbProcTmr
 *
 *         Processing steps:
 *               This function based upon the timer event invokes specific 
 *               routine to handle timer expiry. 
 *
 * @param[in] Cb : This holds approriate Control block for the timer event passed. 
 * @param[in] tmrEvent : One of the many possible timer types. 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PRIVATE Void nbProcTmr
(
Ptr                          cb,
S16                          event
)
{
   NbLiSapCb                 *sapCb;
   NbUeCb                    *ueCb;
   NbDelayICSRspCb           *icsRspCb;
   NbDelayUeCtxtRelCmpCb     *ueCtxtRelCb;
  /*U32 size;*/
   switch(event)
   {
      case NB_TMR_SZT_SAP_BND:
         {
            sapCb           = (NbLiSapCb *)cb;
            sapCb->sapState = LNB_SAP_UNBOUND; 
            nbSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_BND_FAIL, 
                  LNB_CAUSE_SZT_SAP_BOUND);
            break;
         }
#ifdef EU_DAT_APP
      case NB_TMR_EGT_SAP_BND:
         {
            sapCb           = (NbLiSapCb *)cb;
            sapCb->sapState = LNB_SAP_UNBOUND; 
            nbSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_BND_FAIL, 
                  LNB_CAUSE_EGT_SAP_BOUND);
            break;
         }
#endif
      case NB_TMR_MME_SETUP_RSP:
      {
            NB_LOG_ERROR(&nbCb,"S1 SetUp Timer Expired,Indicating to USER");
         nbUiSendS1TimeOutInd();
         break;
      }
      case NB_TMR_LCL_UE_CTXT_REL_REQ:
      {
         ueCb = (NbUeCb *)cb;
         NB_LOG_DEBUG(&nbCb,"Local Context Release Timer Expired for UE:[%d]",ueCb->ueId);
         break;
      }
      case NB_TMR_DELAY_ICS_RSP:
      {
         icsRspCb = (NbDelayICSRspCb *)cb;
         NB_LOG_DEBUG(&nbCb,"Local Context Release Timer Expired for UE:[%d]",icsRspCb->ueId);
         nbHandleDelayTimerForICSExpiry(icsRspCb);
         break;
      }
      case NB_TMR_DELAY_UE_CTX_REL_COMP:
      {
         ueCtxtRelCb = (NbDelayUeCtxtRelCmpCb *)cb;
         NB_LOG_DEBUG(&nbCb,"Local UE Context Release Timer Expired for UE:[%d]",ueCtxtRelCb->ueId);
         nbHandleDelayTimerForUeCtxRelComplExpiry(ueCtxtRelCb);
         /*HandleDelayTimerForICSExpiry(ueCtxtRelCb);*/
         break;
      }
      default:
         {
            /* Invalid Timer */
            NB_LOG_ERROR(&nbCb,"Invalid Timer event [%d] received", event);
            break;
         }
   }
   RETVOID;
} /* end of wrProcTmr() */

/** @brief This function Finds whether Timer is running or not
 *
 * @details
 *
 *     Function: wrIsTmrRunning
 *
 *         Processing steps:
 *               Check Whetether Timer is running or not based on Event type
 *
 * @param[in] tmr : pointre to the Timer. 
 * @param[in] event : One of the many possible timer types. 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC Bool nbIsTmrRunning
(
CmTimer                      *tmr,
S16                          event
)
{
   if(tmr != NULLP)
   {	
      if(tmr->tmrEvnt == event)
      {
         RETVALUE(TRUE);
      }
      else if (tmr->tmrEvnt != TMR_NONE)
      {
         NB_LOG_ERROR(&nbCb,"Invalid Timer event [%d] received", event);
      }
   }
   RETVALUE(FALSE);
}
