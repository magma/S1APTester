


/********************************************************************20**

     Name:     eGTP Timer Module

     Type:     C source file

     Desc:     Timer Module

     File:     eg_tmr.c

     Sid:      eg_tmr.c@@/main/TeNB_Main_BR/5 - Mon Aug 11 16:42:30 2014

     Prg:      sn

*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* General */
#include "ssi.h"           /* System Services */
#include "cm_tkns.h"       /* common tokens */
#include "cm_hash.h"       /* common structs 1 */
#include "cm_mblk.h"       /* common memory */
#include "cm_llist.h"      /* cm link list */
#include "cm5.h"           /* common structs 3 */
#include "cm_inet.h"       /* common tokens  */
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport */
#include "hit.h"           /* TUCL Layer */
#include "egt.h"           /* EGTP Upper Interface */
#include "leg.h"           /* EGTP LM Interface */
/* eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_psf.h"
#include "sht.h"
#include "hw.h"
#endif
#include "eg.h"            /* EGTP Layer */
#include "eg_err.h"
#include "eg_tpt.h"        /* EGTP TPT Module  */
#include "eg_edm.h"        /* EDM Module structures            */

/* header/extern include files (.x) */
#include "gen.x"           /* General */
#include "ssi.x"           /* System Services */
#include "cm_tkns.x"       /* common tokens */
#include "cm_hash.x"       /* common structs 1 */
#include "cm_lib.x"        /* common library */
#include "cm_mblk.x"       /* common memory */
#include "cm_llist.x"      /* cm link list */
#include "cm5.x"           /* common structs 3 */
#include "cm_inet.x"       /* common transport */
#include "cm_tpt.x"        /* common transport */
#include "hit.x"           /* TUCL Layer */
#include "egt.x"           /* EGTP Upper Interface */
#include "leg.x"           /* EGTP LM Interface */
#include "eg_edm.x"        /* EDM Module structures            */
/* eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#include "sht.x"
#endif
#include "eg.x"            /* EGTP Layer */
#include "eg_tpt.x"        /* EGTP TPT Module  */

#ifdef HW
#include "lhw.x"
#include "hw.x"          /* EGTPC UA                       */
#endif

#include "eg_socklayer.h"
#include "eg_socklayer.x"

/***************************************************************************
********************************* Local function definitons ****************
*****************************************************************************/
/* ccpu00136421:unused function:purecov fix */
#if 0
PRIVATE Void egBndTmrExpiry ARGS((EgTSapCb       *tSapCb));
#endif
PRIVATE Void egTptOpenSrvTmrExpiry ARGS((EgTptSrvCb    *serverCb));

/* eg012.201: Enhanced the piggy backing feature by adding the Timer. */

#ifdef EGTP_U
PRIVATE Void egReordTmrExpiry ARGS((EgTeIdCb *egTeidCb));
#endif /* End of EGTP_U */


#ifdef DEBUGP
PRIVATE S8* egTmrGetEvntStr ARGS((S16    tmrEvnt));
#endif

/*
 *
 *       Fun:   Activate Task - timers
 *
 *       Desc:  Invoked by system services to activate a task with
 *              a timer tick.
 *
 *       Ret:   ROK      - ok
 *
 *       Notes: None
 *
 *       File:  eg_tmr.c
 *
 */
#ifdef SS_MULTIPLE_PROCS
#ifdef ANSI
PUBLIC S16 egActvTmr
(
ProcId proc,
Ent    ent,
Inst   inst
)
#else

PUBLIC S16 egActvTmr(proc, ent, inst)
ProcId proc;
Ent    ent;
Inst   inst;
#endif
#else /* SS_MULTIPLE_PROCS */
#ifdef ANSI
PUBLIC S16 egActvTmr
(
void
)
#else
PUBLIC S16 egActvTmr()
#endif
#endif /* SS_MULTIPLE_PROCS */
{
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC3(egActvTmr);
#ifdef SS_MULTIPLE_PROCS
   if ((SGetXxCb(proc, ent, egCb.init.inst, (Void **) &egCbPtr) !=ROK))
   {
      SLogError(ent, egCb.init.inst, proc,(Txt *) __FILE__, __LINE__,\
                ERRCLS_DEBUG,EEG325,(ErrVal)0,
                (Txt *)"egActvTmr() failed, cannot derive egCb");
      RETVALUE(RFAILED);
   }
#ifdef NOT_USED
   EGDBGP(DBGMASK_UI,(egCb.init.prntBuf,
         "--------EGTP-----(proc(%d),ent(%d),inst(%d))-------\n",
         proc, ent, egCb.init.inst));
#endif

#endif /* SS_MULTIPLE_PROCS */

   cmPrcTmr(&egCb.egTqCp, egCb.egTq, (PFV) egTmrEvnt);

   RETVALUE(ROK);

} /* end of egActvTmr */

/*
 *
 *       Fun:   egRegInitTmr
 *
 *       Desc:  Register and initialize timer queue structures in
 *              EGTP during general config.
 *
 *       Ret:   ROK - ok;
 *              RFAILED - failed;
 *
 *       Notes: none
 *
 *       File:  eg_tmr.c
 *
 */
#ifdef ANSI
PUBLIC S16 egRegInitTmr
(
Void
)
#else
PUBLIC S16 egRegInitTmr()
#endif
{
   U16 idx;
   S16 ret;

   EG_TRC2(egRegInitTmr);

   EG_DBG_INFO (0,0, (egCb.init.prntBuf, "Timer Resolution (%d) \n",egCb.genCfg.timerRes ));

    /* register general timer here */
#ifdef SS_MULTIPLE_PROCS
   ret = SRegTmr(egCb.init.proc,egCb.init.ent, egCb.init.inst, egCb.genCfg.timerRes, (PAIFTMRS16) egActvTmr);
#else
   ret = SRegTmr(egCb.init.ent, egCb.init.inst, egCb.genCfg.timerRes, egActvTmr);
#endif
   if (ret != ROK)
   {
      EGLOGERROR(ERRCLS_DEBUG,EEG328,(ErrVal) 0,
                 "egRegInitTmr:  egActvTmr failed");
      RETVALUE(RFAILED);
   }

   /* initialize timing queues */
   egCb.egTqCp.tmrLen      = EG_TQNUMENT;

   for (idx = 0; idx < EG_TQSIZE; idx++)
   {
      egCb.egTq[idx].first    = NULLP;
      egCb.egTq[idx].tail     = NULLP;
   }

   EG_RETVALUE(ROK);

} /* egRegInitTmr */



/*****************************************************************************
*
*       Fun:   egCmInitTimer
*
*       Desc:  Initialize the timer control blocks
*
*       Ret:   EG_RETVOID
*
*       Notes: None
*
*       File:  eg_tmr.c
*
*****************************************************************************/

#ifdef ANSI
PUBLIC Void egCmInitTimer
(
EgTimer      *tmr         /* timer control block array */
)
#else
PUBLIC Void egCmInitTimer (tmr)
EgTimer      *tmr;         /* timer control block array */
#endif
{
   EG_TRC2(egCmInitTimer)

   cmInitTimers ((CmTimer *)&tmr->tmr, 1);

   tmr->egCbPtr    = 0;

   EG_RETVOID;
} /* egCmInitTimer */


/**************************************************************************
*
*       Fun:   egSchedTmr
*
*       Desc:  Schedule/Deschedule a timer
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: tmrVal is in units of 500ms
*
*       File:  eg_tmr.c
*
****************************************************************************/
#ifdef S1SIMAPP
extern int tmrval;
static Bool egTxEvnt = TRUE;
#endif
#ifdef ANSI
PUBLIC S16 egSchedTmr
(
Ptr          egHandle,     /* Control block */
S16          tmrEvnt,      /* timer event */
Action       action,       /* action -- start/stop/restart */
U32          tmrVal        /* timer value */
)
#else
PUBLIC S16 egSchedTmr (egHandle, tmrEvnt, action, tmrVal)
Ptr          egHandle;     /* Control block */
S16          tmrEvnt;      /* timer event */
Action       action;       /* action -- start/stop/restart */
U32          tmrVal;       /* timer value */
#endif
{
   CmTimer   *tmr;         /* timers array */
   CmTmrArg  arg;          /* timer arguments */
   EgTimer   *egTmr = NULLP;       /* Actual EgTimer inside control block */

   EG_TRC2(egSchedTmr);

#ifdef ALIGN_64BIT
   EG_DBG_PARAM(0, 0,(egp, "Timer Event: %s, Action %d, Value %d",
         egTmrGetEvntStr(tmrEvnt), action, tmrVal) );
#else
   EG_DBG_PARAM(0, 0,(egp, "Timer Event: %s, Action %d, Value %ld",
         egTmrGetEvntStr(tmrEvnt), action, tmrVal) );
#endif

   if ((action != TMR_STOP) && (tmrVal == 0))
   {
      RETVALUE(RFAILED);
   }

   /*
    * None of the bits from EGTMR_EVNT_IDXOFFSET to
    * 16 (maximum number of bits in tmrEvnt) should be
    * set in tmrEvnt
    */
   if (tmrEvnt & EGTMR_EVNT_IDXMASK)
   {
      RETVALUE(RFAILED);
   }

   switch (tmrEvnt)
   {
      /*------------- Transport Module Timers ------------*/
      case EG_TMR_TPT_BND:
 {
    egTmr = &((EgTSapCb *)egHandle)->bndTmr;
    egTmr->egCbPtr  = (PTR)egHandle;
    tmr = &egTmr->tmr;
    break;
 } /* End of case EG_TMR_TPT_BND */
      case EG_TMR_TPT_OPEN_SRV: /*-- Open Server Timer --*/
 {
    egTmr = &((EgTptSrvCb *)egHandle)->opnSrvTmrNode;
    egTmr->egCbPtr  = (PTR)egHandle;
    tmr = &egTmr->tmr;
    break;
 } /* End of case EG_TMR_TPT_OPEN_SRV */
#ifdef S1SIMAPP
      case 100:
         {
            egTmr = &((EgTptSrvCb *)egHandle)->tstSrvTmrNode;
            egTmr->egCbPtr  = (PTR)egHandle;
            tmr = &egTmr->tmr;
            break;
         }
      case EG_TMR_EGT_RXTXDATA:
         { 
            egTmr = &((EgTLCb *)egHandle)->egtTxRxTmrNode;
            egTmr->egCbPtr  = (PTR)egHandle;
            tmr = &egTmr->tmr;
            break;
         }
#endif
#ifdef EGTP_U
      case EG_TMR_ECHO_GLOBAL: /*-- iEcho req transmit Timer --*/
 {
    tmr = &(egCb.egUCb.echoTimers);
    break;
 } /*End of case EG_TMR_TPT_MSG_RETX */
      case EG_TMR_N3T3_REQ: /*-- N3T3 retransmossoin timer --*/
 {
    tmr = &(egCb.egUCb.n3t3Timers);
    break;
 } /*End of case EG_TMR_TPT_MSG_RETX */

       case EG_TMR_REORD_EXP:
    {
       egTmr = &((EgTeIdCb *)egHandle)->reOrderTimer;
       egTmr->egCbPtr  = (PTR)egHandle;
       tmr = &egTmr->tmr;
       break;
    } /* End of case EG_TMR_REORD_EXP */

 #endif /* End of EGTP_U */

      default:
 RETVALUE(RFAILED);
 break;
   }


   if (action == TMR_STOP)
   {
      /* return ROK if timer has already been stopped.*/
      if (tmr->tmrEvnt == TMR_NONE)
         RETVALUE(ROK);

      if (tmrEvnt == (tmr->tmrEvnt & ~EGTMR_EVNT_IDXMASK))
      {
         arg.tqCp   = &egCb.egTqCp;
         arg.tq     = (CmTqType *) &egCb.egTq;

         arg.timers = tmr;
         arg.cb     = (PTR)egTmr;
         arg.evnt   = NOTUSED;
         arg.wait   = NOTUSED;
         arg.tNum   = 0;
         arg.max    = 1;

         cmRmvCbTq (&arg);
         RETVALUE(ROK);
      }
   }
   else if (action == TMR_START)
   {
      if (tmr->tmrEvnt == TMR_NONE)
      {
         arg.tqCp   = &egCb.egTqCp;
         arg.tq     = (CmTqType *) &egCb.egTq;
         arg.timers = tmr;
         arg.cb     = (PTR)egTmr;
         arg.evnt   = tmrEvnt;
         arg.wait   = tmrVal;
         arg.tNum   = NOTUSED;
         arg.max    = 1;

         cmPlcCbTq (&arg);
         RETVALUE (ROK);
      }
      else
      {
         RETVALUE (RFAILED);
      }
   }
#ifdef EG_PHASE2
   else if (action == TMR_RESTART)
   {
      if ((tmrEvnt == (tmr->tmrEvnt & ~EGTMR_EVNT_IDXMASK)) ||
          (tmr->tmrEvnt == TMR_NONE))
      {
         if (tmr->tmrEvnt != TMR_NONE)
         {
            arg.tqCp   = &egCb.egTqCp;
            arg.tq     = (CmTqType *)&egCb.egTq;
            arg.timers = tmr;
            arg.cb     = (PTR)egTmr;
            arg.evnt   = NOTUSED;
            arg.wait   = NOTUSED;
            arg.tNum   = 0;
            arg.max    = 1;

            cmRmvCbTq (&arg);
         }

         arg.tqCp   = &egCb.egTqCp;
         arg.tq     = (CmTqType *)&egCb.egTq;

         arg.timers = tmr;
         arg.cb     = (PTR)egTmr;
         arg.evnt   = tmrEvnt;
         arg.wait   = tmrVal;
         arg.tNum   = NOTUSED;
         arg.max    = 1;

         cmPlcCbTq (&arg);
         RETVALUE(ROK);
      }
   }
#endif /* EG_PHASE2 */

   RETVALUE(RFAILED);
} /* end of egSchedTmr */

/*
*
*       Fun:    egRmvTmr
*
*       Desc:   Removes control block from Timing Queue
*
*       Ret:    RETVOID
*
*       Notes:  None
*
*       File:   eg_tmr.c
*
*/
/* REVIEW-ID:56220: unused function:purecov fix */
#if 0
#ifdef ANSI
PUBLIC Void egRmvTmr
(
PTR      cbp,              /* control block pointer       */
CmTimer  *pTimerStruct,    /* pointer to timer structure */
U8       tmrNum,           /* timer number               */
U8       maxNmbTmrs        /* maximum nmb of timers for this control block */
)
#else
PUBLIC Void egRmvTmr(cbp, pTimerStruct, tmrNum, maxNmbTmrs)
PTR      cbp;              /* ontrol block pointer       */
CmTimer  *pTimerStruct;    /* pointer to timer structure */
U8       tmrNum;           /* timer number               */
U8       maxNmbTmrs;       /* maximum nmb of timers for this control block */
#endif
{
   CmTmrArg arg;           /* timer argument structure                       */

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egRmvTmr)

   arg.tq = egCb.egTq;
   arg.tqCp = &egCb.egTqCp;
   arg.timers = pTimerStruct;
   arg.cb = cbp;
   arg.evnt = pTimerStruct[tmrNum].tmrEvnt;
   arg.wait = 0;
   arg.tNum = tmrNum;
   arg.max = maxNmbTmrs;
   cmRmvCbTq(&arg);

   RETVOID;
}
#endif 

/*
 *
 *       Fun:   egTmrEvnt
 *
 *       Desc:  Process the EGTP timer event.
 *
 *       Ret:   RETVOID
 *
 *       Notes: None
 *
 *       File:  eg_tmr.c
 *
 */
#ifdef S1SIMAPP
struct timespec tsStop;
struct timespec tsStop1;
struct timespec tsResult;
extern struct timespec tsStart;
extern struct timespec tsStart1;
#endif
#ifdef ANSI
PUBLIC Void egTmrEvnt
(
Ptr       cb,
S16       event
)
#else
PUBLIC Void egTmrEvnt(cb, event)
Ptr       cb;
S16       event;
#endif
{
   EgTimer     *egTmr;        /* Timer which expired */

   EG_TRC2(egTmrEvnt);

   egTmr = (EgTimer *)cb;

   /*
      For Default path,  a timer is started. Also, when a request is sent to the
      peer, re-transmission timer is started. When  either timer expires, we are
      required to send Echo Request/Retransmission Request. This is only valid
      for Active Resource set. In order to avoid any errorenous message being sent
      out of by Standby copy, this check is required.
    */

   /*Process timer event only if resource set is in Active state.*/
   switch (event)
   {
      /* ccpu00136421:purecov fix*/
#if 0
      case EG_TMR_TPT_BND:
      {
         egBndTmrExpiry((EgTSapCb *)egTmr->egCbPtr);
         break;
      }
#endif /*0*/      
      case EG_TMR_TPT_OPEN_SRV:
      {
         egTptOpenSrvTmrExpiry((EgTptSrvCb *)egTmr->egCbPtr);

         break;
      }
#ifdef S1SIMAPP
      case 100:
      {
#if 1
         gettimeofday(&tsStop, NULL);
         tsResult.tv_nsec = (((tsStop.tv_sec -
                     tsStart.tv_sec) * 1000000) +
               (tsStop.tv_nsec -
                tsStart.tv_nsec));
         printf("\n************* Testing *Time elapsed(in usec): for timer expiry\
               :%ld usec\n", tsResult.tv_nsec);
#endif
         break;
      }
      case EG_TMR_EGT_RXTXDATA:
      {
         gettimeofday(&tsStop1, NULL);
         tsResult.tv_nsec = (((tsStop1.tv_sec -
                     tsStart1.tv_sec) * 1000000) +
               (tsStop1.tv_nsec -
                tsStart1.tv_nsec));
       /*  printf("\n************* Testing RXTADATA Timer *Time elapsed(in usec): for timer expiry\
               :%ld usec\n", tsResult.tv_nsec);*/
         if (egTxEvnt)
         {
            EgTLReadMsg(0,10);
            egTxEvnt = FALSE;
            egSchedTmr(&egTLCb, EG_TMR_EGT_RXTXDATA, TMR_START,
                  1);
         }
         else
         {
            EgTLSendMsg(FALSE);
            egTxEvnt = TRUE;
            egSchedTmr(&egTLCb, EG_TMR_EGT_RXTXDATA, TMR_START,
                  1);
         }
         break;
      }
#endif
#ifdef EGTP_U
       case EG_TMR_REORD_EXP:
      {
         /* Re-oredring timer expiry */
         egReordTmrExpiry((EgTeIdCb *)egTmr->egCbPtr);
         break;
      }
       case EG_TMR_ECHO_GLOBAL:
      {
         /* Echo timer expiry */
         egUSendEchoReq();
         break;
      }
      case EG_TMR_N3T3_REQ:
      {
         /* iN3T3 timer expiry */
         egUHndlT3N3TmrExpiry();
         break;
      }

#endif
      default:
      {
         EG_DBG_ERR(0, 0,(egp, "\nTimer event for an unknown timer\n"));
         break;
         }/*Default*/
   }/*Switch (event)*/

   EG_RETVOID;
} /* end of egTmrEvnt */


/*
 *
 *       Fun:   egBndTmrExpiry
 *
 *       Desc:  Process the EGTP bind timer expiry. If the number of retry is
 *              less than the maximum retry counter, the bind request is sent
 *              again, else an alarm is raised to the layer manager.
 *
 *       Ret:   RETVOID
 *
 *       Notes: None
 *
 *       File:  eg_tmr.c
 *
 */
/*ccpu00136421: purecov fix */
#if 0
#ifdef ANSI
PRIVATE Void egBndTmrExpiry
(
EgTSapCb       *tSapCb
)
#else
PRIVATE Void egBndTmrExpiry(tSapCb)
EgTSapCb       *tSapCb;
#endif
{
   EgUstaDgn dgn;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egBndTmrExpiry);

   if (tSapCb->state == LEG_TSAP_WAIT_BNDENA)
   {
      if (tSapCb->bndRetryCnt < tSapCb->reCfg.maxBndRetry)
      {
         tSapCb->bndRetryCnt++;
         egSchedTmr(tSapCb, EG_TMR_TPT_BND, TMR_START,
               tSapCb->reCfg.bndTmCfg.val);

         (Void)EgLiHitBndReq(&tSapCb->pst, tSapCb->suId, tSapCb->spId);
      }
      else
      {
         tSapCb->bndRetryCnt = 0;
         tSapCb->state = LEG_TSAP_UBNDDIS;
         cmMemset( (U8* )&dgn, 0, sizeof(EgUstaDgn));
         dgn.dgnVal[0].type = LEG_PAR_TSAP;
         dgn.dgnVal[0].t.sapId = tSapCb->suId;
         egSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_BND_FAIL,
                     LCM_CAUSE_UNKNOWN, &dgn);
      }
   }
   RETVOID;
} /* end of egBndTmrExpiry */
#endif /*0*/
/* eg012.201: Enhanced the piggy backing feature by adding the Timer. */


/***********************************************************************************
 *
 *       Fun:   egTptOpenSrvTmrExpiry
 *
 *       Desc:  Process the EGTP TPT Open Server timer expiry.
 *              If the number of retry is
 *              less than the maximum retry counter, the Server Open request is sent
 *              again, else an alarm is raised to the layer manager.
 *
 *       Ret:   RETVOID
 *
 *       Notes: None
 *
 *       File:  eg_tmr.c
 *
 ***********************************************************************************/
#ifdef ANSI
PRIVATE Void egTptOpenSrvTmrExpiry
(
  EgTptSrvCb    *serverCb /* Server connection control block */
)
#else
PRIVATE Void egTptOpenSrvTmrExpiry(serverCb)
EgTptSrvCb    *serverCb; /* Server connection control block */
#endif
{

   EG_TRC2(egTptOpenSrvTmrExpiry);


   EG_DBG_INFO(0, 0,(egp, "\n Timer Open Server Expired \n"));

   if (NULLP == serverCb)
   {
      EG_DBG_ERR(0, 0,(egp, "\n Null Timer CB \n"));
      EG_RETVOID;
   }

   if ((serverCb->state == LEG_TPTSRV_WAIT_ENA ||
            serverCb->state == LEG_TPTSRV_DIS))
   {
      /*-- Make the state to disalbe again, as egTptOpenServer
        function will require the same --*/

      serverCb->state = LEG_TPTSRV_DIS;
      /* Retry to open the transport server */
      if (egTptOpenServer(serverCb, NULLP) != ROK)
         EG_RETVOID;
   }
   else if (serverCb->state != LEG_TPTSRV_WAIT_ENA)
   {
      EG_DBG_ERR(0, 0, (egp,"Invalid serverCb->state %d", serverCb->state));
   }

   EG_RETVOID;

}/* egTptOpenSrvTmrExpiry */


#ifdef EGTP_U
/***********************************************************************************
 *
 *       Fun:   egReordTmrExpiry
 *
 *       Desc:  This function will be called when reodering timer expires
 *
 *       Ret:   RETVOID
 *
 *       Notes: None
 *
 *       File:  eg_tmr.c
 *
 ***********************************************************************************/

#ifdef ANSI
PRIVATE Void egReordTmrExpiry
(
EgTeIdCb *egTeidCb
)
#else
PRIVATE Void egReordTmrExpiry(egTeidCb)
EgTeIdCb *egTeidCb;
#endif
{
   EG_TRC2(egReordTmrExpiry);

#ifdef SS_MT_CB
    EG_WRLOCK(&egCb.egUCb.threadLock);
#endif /* SS_MT_CB */
    egFlushReordRcvdGtpuPdus(egTeidCb);
#ifdef SS_MT_CB
    EG_RDWR_UNLOCK(&egCb.egUCb.threadLock);
#endif /* SS_MT_CB */

   EG_RETVOID;
}

#endif /* EGTP_U */


#ifdef DEBUGP
/***********************************************************
*
*      Fun:    egTmrGetEvntStr
*
*      Desc:   Handle the expiration of a particular timer event
*
*       Ret:   RETVOID
*
*       Notes: This function dispatches the timer event expiry
*              to the appropriate module.
*
*       File:  eg_tmr.c
*
***********************************************************/

#ifdef ANSI
PRIVATE S8* egTmrGetEvntStr
(
S16              tmrEvnt      /* timer event */
)
#else
PRIVATE S8* egTmrGetEvntStr(tmrEvnt)
S16              tmrEvnt;     /* timer event */
#endif
{
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egTmrGetEvntStr)

   /* If timer is not handled on a module basis, process individually */
   switch (tmrEvnt)
   {
        /*------------- Transport Module Timers ------------*/
      case EG_TMR_TPT_BND:
         RETVALUE((S8 *)"EG_TMR_TPT_BND");

      case EG_TMR_TPT_OPEN_SRV: /*-- Open Server Timer --*/
         RETVALUE((S8 *)"EG_TMR_TPT_OPEN_SRV");

      case EG_TMR_TPT_MSG_RETX: /*-- Re-Trans Timer --*/
         RETVALUE((S8 *)"EG_TMR_TPT_MSG_RETX");

#ifdef EGTP_U
       case EG_TMR_REORD_EXP:
         RETVALUE((S8 *)"EG_TMR_REORD_EXP");

      case EG_TMR_ECHO_GLOBAL:
         RETVALUE((S8 *)"EG_TMR_ECHO_GLOBAL");

      case EG_TMR_N3T3_REQ:
         RETVALUE((S8 *)"EG_TMR_N3T3_REQ");
#endif /* EGTP_U */

      default:
         break;
   }

   RETVALUE("EG_TMR_INVALID");
}
#endif /*-- DEBUGP --*/



/********************************************************************30**

  End of file:     eg_tmr.c@@/main/TeNB_Main_BR/5 - Mon Aug 11 16:42:30 2014

*********************************************************************31*/

/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/

/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/
/********************************************************************90**

ver        pat        init                  description
------ --------      ---- --------------------------------------
/main/1      ---      an                1. Created for Initial Release 1.1
/main/2      ---      pmacharla
                      akulkarni         1. Initial for eGTP 1.2 Release
/main/2      eg001.102    snatarajan        1. EGTP_C Path management functionality is introduced.
                          rss               2. Multithreaded performance changes gaurded under SS_MT_CB flag.
/main/3      ---      pmacharla         Initial for eGTP release 2.1
/main/3      eg003.201 psingh           1. Merged code from eg006.102 to Fix
                                           TRACE5 macro related issue
/main/3      eg004.201 magnihotri       1. Header files added for eGTP-C PSF
                                        2. Check added Send ECHO Request only from ACTIVE PSF node
/main/3    eg012.201   shpandey         1. Enhanced the piggy backing feature by adding the Timer 
*********************************************************************91*/
