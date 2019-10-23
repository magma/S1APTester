/**********************************************************************

    Name:  LTE S1SIM - ENODEB Application Module 

    Type:  C include file

    Desc:  C source code for ENODEB Application

    File:  nb_dam_tmr.c

    Sid:   

    Prg:   

**********************************************************************/

/* Header include files (.h) */
#include "ssi.h"
#include "nb.h" 
#include "rl_interface.h"
#include "rl_common.h"
#include "nb_dam.h"
#include "nb_smm_init.h"
#include "nb_dam_ifm_app.h"
#include "nb_log.h"

PRIVATE Void nbDamProcTmr (Ptr cb, S16 tmrEvnt);
EXTERN Void nbIfmDamNbSendLmAlarm(U16, U16, U16);

/** @brief This function registers and initializes the timer
 *         queue structures used by DAM
 *
 * @details
 *
 *     Function: nbDamRegInitTmr
 *
 *         Processing steps:
 *
 * @param[in] Void 
 * @return S16
 *        -# Success : ROK
 */
PUBLIC S16 nbDamRegInitTmr
(
Void
)
{
   U32 idx;
   S16 ret;
   ret = SRegTmr((Ent)ENTEU, (Inst)nbDamCb.init.inst, nbDamCb.timeRes,
         nbDamActvTmr);
   if (ret != ROK)
   {
      NB_LOG_ERROR(&nbCb,"SRegTmr Failed");
      RETVALUE(RFAILED);
   }

   /* initialize timing queues */
   nbDamCb.tqCp.tmrLen      = NB_NUM_TQENTRY;

   for (idx = 0; idx < NB_NUM_TQENTRY; idx++)
   {
      nbDamCb.tq[idx].first = NULLP;
      nbDamCb.tq[idx].tail  = NULLP;
   }

   RETVALUE(ROK);
} /* wrDamRegInitTmr */


/** @brief This function de-registers the DAM timers
 *
 * @details
 *
 *     Function: nbDamDeRegTmr
 *
 *         Processing steps:
 *
 * @param[in] Void 
 * @return S16
 *        -# Success : ROK
 */
PUBLIC S16 nbDamDeRegTmr 
(
Void
)
{
   RETVALUE(SDeregTmr((Ent)ENTEU, (Inst)nbDamCb.init.inst, nbDamCb.timeRes,
            nbDamActvTmr));
}/* wrDamDeRegTmr */


/** @brief Invoked by system services to activate a task with
 *              a timer tick.
 *
 * @details
 *
 *     Function: nbDamActvTmr
 *
 *         Processing steps:
 *
 * @param[in] Void 
 * @return S16
 *        -# Success : ROK
 */

PUBLIC S16 nbDamActvTmr
(
 Void
)
{
   cmPrcTmr(&nbDamCb.tqCp,nbDamCb.tq,(PFV)nbDamProcTmr);
   RETVALUE(ROK);
} /* end of wrDamActvTmr */


/** @brief This function is used to start a given timer. 
 *
 * @details
 *
 *     Function: nbDamStartTmr
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
PUBLIC S16 nbDamStartTmr
(
PTR cb,
S16 tmrEvnt,
U32 delay
)
{
   U32         wait;
   CmTmrArg    arg;
   CmTimer     *tmr;
   U8          maxTmrs;

   wait = NB_DAM_CALC_WAIT_TIME(delay);
   maxTmrs  = 1;

   switch (tmrEvnt)
   {
      /* For SZT Bind Timer Timer */
      case NB_TMR_EGT_SAP_BND:
         {
            NbLiSapCb   *sapCb;
            sapCb = ( NbLiSapCb*)cb;
            tmr      = &sapCb->timer;
            break;
         }
      case NB_TMR_INACTIVITY:
         {
            NbDamUeCb   *damUeCb;
            damUeCb = (NbDamUeCb *)cb;
            tmr      = &damUeCb->inactivityTmr;
            break;
         }

      default:
         {
         NB_LOG_ERROR(&nbCb,"Invalid tmrEvnt");
            RETVALUE(RFAILED);
         }
   } /* end of switch */

   /* if the timer is already running return failure */
   if(tmr->tmrEvnt != TMR_NONE)
   {
      RETVALUE(RFAILED);
   }         
   /* initialize argument for common timer function */
   if(wait != 0)
   {
      arg.tqCp   = &(nbDamCb.tqCp);
      arg.tq     = nbDamCb.tq;
      arg.cb     = cb;
      arg.timers = tmr;
      arg.evnt   = tmrEvnt;
      arg.wait   = wait;
      arg.tNum   = 0;
      arg.max    = maxTmrs;

      cmPlcCbTq(&arg);
   }

   RETVALUE(ROK);
} /* end of nbDamStartTmr() */


/** @brief This function is used to stop a previously running timer. 
 *
 * @details
 *
 *     Function: nbDamStopTmr
 *
 *         Processing steps:
 *               This function based upon the timer event reterives relevant timerCb and 
 *               tries to determine whether timer is running or not.In case timer 
 *               was running, it is stopped .
 *
 * @param[in] Cb : This holds approriate Control block for the timer event passed. 
 * @param[in] tmrEvent : One of the many possible timer types. 
 * @return Void
 */
PUBLIC Void nbDamStopTmr
(
PTR cb,
S16 event
)
{
   CmTmrArg    arg;
   U8          idx;
   CmTimer     *timers = NULLP;
   U8          max = 0;

   idx = 0;
   max = 1;
   switch(event)
   {
      case NB_TMR_EGT_SAP_BND:
      {
         NbLiSapCb   *sapCb;
         sapCb = (NbLiSapCb*)cb;
         timers = &sapCb->timer;
         break;
      }
      case NB_TMR_INACTIVITY:
      {
         NbDamUeCb   *damUeCb;
         damUeCb = (NbDamUeCb *)cb;
         timers = &damUeCb->inactivityTmr;
         break;
      }/* End of NB_TMR_INACTIVITY */
      default:
         break;
   }
 
   if(NULLP == timers)
   {
      NB_LOG_ERROR(&nbCb,"nbDamStopTmr: event=[%d] does not have any timers", event);
      RETVOID;
   }
   /* if the timer is already not running return failure */
   if(timers->tmrEvnt == TMR_NONE)
   {
      RETVOID;
   } 

   /* initialize argument for common timer function */
   arg.tqCp    = &nbDamCb.tqCp;
   arg.tq      = nbDamCb.tq; 
   arg.timers  = timers;
   arg.cb      = cb;
   arg.evnt    = event;
   arg.wait    = 0;
   arg.max     = max;
   arg.tNum    = idx;
   cmRmvCbTq(&arg);

   RETVOID;
} /* end of nbDamStopTmr() */

/** @brief This function handles timer expiry. 
 *
 * @details
 *
 *     Function: nbDamProcTmr
 *
 *         Processing steps:
 *               This function based upon the timer event invokes specific 
 *               routine to handle timer expiry. 
 *
 * @param[in] Cb : This holds approriate Control block for the timer event passed. 
 * @param[in] tmrEvent : One of the many possible timer types. 
 * @return Void
 */
PRIVATE Void nbDamProcTmr
(
Ptr cb,
S16 event
)
{
   NbLiSapCb     *sapCb = NULLP;
   NbDamUeCb     *damUeCb = NULLP;

   switch(event)
   {
      case NB_TMR_EGT_SAP_BND:
         {
            sapCb = (NbLiSapCb *)cb;
            sapCb->sapState = LNB_SAP_UNBOUND; 
            nbIfmDamNbSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_BND_FAIL, 
                  LNB_CAUSE_EGT_SAP_BOUND);
            break;
         }
      case NB_TMR_INACTIVITY:
         {
            damUeCb = (NbDamUeCb*)cb;
            if(damUeCb->dataRcvd == FALSE)
            {
               damUeCb->expiryCnt++;
               if(damUeCb->expiryCnt == nbDamCb.expiryCnt)
               {
                  NB_LOG_DEBUG(&nbCb,"UE INACTIVITY OCCURED");
                  NB_LOG_DEBUG(&nbCb,"INFORMING UEAPP UE INACTIVITY");
                  nbUiNbuHandleUeInactivity(damUeCb->ueId);
                  NB_LOG_DEBUG(&nbCb,"DELETING THE UE CONTEXT");
                  nbIfmDamNbCtxtRel(damUeCb->ueId,NB_UE_CTXT_REL_INACTIVITY, NB_CAUSE_RADIONW);
               }
               else
               {
                  NB_LOG_ERROR(&nbCb,"Inactivity Timer Expired for UE %d: "\
                        "Current Expiry Count = %d MAX_EXPIRY_COUNT = %d",
                        damUeCb->ueId, damUeCb->expiryCnt, nbDamCb.expiryCnt);
                  nbDamStartTmr((PTR)damUeCb, NB_TMR_INACTIVITY,
                        nbDamCb.inactvTmrVal);
               }
            }
            else
            {
               damUeCb->dataRcvd = FALSE;
               damUeCb->expiryCnt = 0;
               nbDamStartTmr((PTR)damUeCb, NB_TMR_INACTIVITY,
                     nbDamCb.inactvTmrVal);
            }
            break;
         }
      default:
         {
            /* Invalid Timer */
            NB_LOG_ERROR(&nbCb,"Invalid timer [%d]", event);
            break;
         }
   }/*End of timer event switch*/
   RETVOID;
} /* end of nbDamProcTmr() */


