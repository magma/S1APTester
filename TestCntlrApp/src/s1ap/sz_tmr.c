
/************************************************************************

     Name:     S1AP Layer

     Type:     C source file

     Desc:     C Source code for timer functions

     File:     sq_tmr.c

     Sid:      sq_tmr.c@@/main/3 - Mon Jan 10 22:17:07 2011

     Prg:      sn

************************************************************************/
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
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#include "cm_pasn.h"

#include "sct.h"           /* SCTP Layer */
#include "szt.h"           /* S1AP Upper Interface */
/* sz006.301: Removed un-necessary include files  */
#include "szt_asn.h"
#ifdef SZ_FTHA
#include "cm_psfft.h"
#include "cm_ftha.h"
#include "cm_pftha.h"
#include "cm_psf.h"
#include "sht.h"           /* System Agent */
#include "lyt.h"
#endif /* SZ_FTHA */
#include "lsz.h"           /* S1AP LM Interface */
#include "sz.h"            /* S1AP Layer */
#ifdef YT
#include "yt.h"            /* S1AP-PSF Layer */
#endif /* YT */
#include "sz_err.h"
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.h"
#endif

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
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#include "cm_pasn.x"
#ifdef SZ_FTHA
#include "cm_ftha.x"
#include "cm_pftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#endif /* SZ_FTHA */

#include"szt_asn.x"        /* common ss7 */
#ifndef SZ_ENC_DEC
#include "szt_pk.x"
#include "szt_unpk.x"
#endif /* SZ_ENC_DEC */
#include "sct.x"           /* SCTP Layer */
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.x"
#endif
#include "szt.x"           /* S1AP Upper Interface */
#ifdef SZ_FTHA
#include "sht.x"           /* System Agent */
#include "lyt.x"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.x"           /* S1AP LM Interface */
#ifdef YT
#include "yt.x"
#endif /* YT */
#include "sz.x"            /* S1AP Layer */

/* local function definition */

PRIVATE Void szBndTmrExpiry ARGS((PTR cb));

/* public variable declarations */

/* control variables for testing */

/* private variable declarations */

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
 *       File:  sz_tmr.c
 *
 */
#ifdef SS_MULTIPLE_PROCS
#ifdef ANSI
PUBLIC S16 szActvTmr
(
ProcId proc,
Ent    ent,
Inst   inst
)
#else

PUBLIC S16 szActvTmr(proc, ent, inst)
ProcId proc;
Ent    ent;
Inst   inst;
#endif
#else /* SS_MULTIPLE_PROCS */
#ifdef ANSI
PUBLIC S16 szActvTmr
(
void
)
#else
PUBLIC S16 szActvTmr()
#endif
#endif /* SS_MULTIPLE_PROCS */
{
#ifdef SS_MULTIPLE_PROCS
   S16 ret;
#endif /*SS_MULTIPLE_PROCS */
   TRC3(szActvTmr);
#ifdef SS_MULTIPLE_PROCS
   ret = SGetXxCb(proc, ent, inst, (Void **) &szCbPtr);
#if (ERRCLASS & ERRCLS_DEBUG)
   if ((ret !=ROK)||
       (szCbPtr == NULLP))
   {
      SLOGERROR(ent, inst, proc, __FILE__, __LINE__,\
                ERRCLS_DEBUG,ESZ163,(ErrVal)0,
                "szActvTmr() failed, cannot derive szCb");
      RETVALUE(RFAILED);
   }
#ifdef DEBUGP
   SZDBGP(DBGMASK_UI,(szCb.init.prntBuf,
         "--------S1AP-----(proc(%d),ent(%d),inst(%d))-------\n",
         proc, ent, inst));
#endif
#endif
#endif /* SS_MULTIPLE_PROCS */

   cmPrcTmr(&szCb.szTqCp, szCb.szTq, (PFV) szTmrEvnt);

   RETVALUE(ROK);

} /* end of szActvTmr */

/*
 *
 *       Fun:   szRegInitTmr
 *
 *       Desc:  Register and initialize timer queue structures in 
 *              S1AP during general config.
 *              
 *       Ret:   ROK - ok; 
 *              RFAILED - failed;
 *
 *       Notes: none
 *
 *       File:  sz_tmr.c
 *
 */
#ifdef ANSI
PUBLIC S16 szRegInitTmr
(
Void
)
#else
PUBLIC S16 szRegInitTmr()
#endif
{
   U16 idx;
   S16 ret;

   TRC2(szRegInitTmr);

   SZDBGP(LSZ_DBGMASK_TMR, (szCb.init.prntBuf, "szRegInitTmr: tmrRes(%d) \n",
         szCb.genCfg.timeRes));

   /* register general timer here */
#ifdef SS_MULTIPLE_PROCS
   ret = SRegTmr(szCb.init.proc,szCb.init.ent, szCb.init.inst, szCb.genCfg.timeRes, (PAIFTMRS16) szActvTmr);
#else
   ret = SRegTmr(szCb.init.ent, szCb.init.inst, szCb.genCfg.timeRes, szActvTmr);
#endif

#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
   {
      SZLOGERROR(ERRCLS_DEBUG,ESZ164,(ErrVal) 0,
                 "szRegInitTmr:  szActvTmr failed");
      RETVALUE(RFAILED);
   }
#endif

   /* initialize timing queues */
   szCb.szTqCp.tmrLen      = SZ_TQSIZE;

   for (idx = 0; idx < SZ_TQSIZE; idx++)
   {
      szCb.szTq[idx].first    = NULLP;
      szCb.szTq[idx].tail     = NULLP;
   }

   RETVALUE(ROK);

} /* szRegInitTmr */


/*
*
*       Fun:    szStartTmr
*
*       Desc:   start a timer
*
*       Ret:    None
*
*       Notes:  None
*
*       File:   sz_tmr.c
*
*/

#ifdef ANSI
PUBLIC Void szStartTmr
(
CmTimer            *tmr,                /* Common Timer Structure */
PTR                 cb,                 /* Parent Control Block */
U8                  event,              /* Event */
TmrCfg             *wait                /* Timeout Waiting Period */
)
#else
PUBLIC Void szStartTmr (tmr, cb, event, wait)
CmTimer            *tmr;                /* Common Timer Structure */
PTR                 cb;                 /* Parent Control Block */
U8                  event;              /* Event */
TmrCfg             *wait;               /* Timeout Waiting Period */
#endif /* ANSI */
{
   CmTmrArg         arg;                /* Timer Arguments to be passed */

   TRC3(szStartTmr)
#ifdef DEBUGP
   SZDBGP(DBGMASK_LYR, (szCb.init.prntBuf,
          "szStartTmr(event(%d), wait(%d))\n", event, wait->val));
#endif
   if (wait->enb == TRUE)
   {
      if (tmr->tmrEvnt != TMR_NONE)
      {
         /* Timer is currently in use - reset */
         (Void) szStopTmr(tmr);
      }
      arg.tq      = szCb.szTq;
      arg.tqCp    = &szCb.szTqCp;
      arg.timers  = tmr;
      arg.cb      = cb;
      arg.evnt    = (U8)event;
      arg.wait    = wait->val;
      arg.tNum    = NOTUSED;
      arg.max     = 1;
      cmPlcCbTq(&arg);

      /* sz003.301: Added hooks for PSF-S1AP */
      /* Send the runtime update to peer to start the timer */
#ifdef YT
      if (event == SZ_TMR_WAIT_BNDCFM)
      {
         YT_RTUPD_MOD(YT_UPD_SCT_TMR_CB, (SzSctSapCb *)cb);
      }
#endif /* YT */
   }

   RETVOID;
} /* end of szStartTmr() */


/*
*
*       Fun:    szStopTmr
*
*       Desc:   stop a timer
*
*       Ret:    None
*
*       Notes:  None
*
*       File:   sz_tmr.c
*
*/

#ifdef ANSI
PUBLIC Void szStopTmr
(
CmTimer            *tmr                 /* Common Timer Structure */
)
#else
PUBLIC Void szStopTmr (tmr)
CmTimer            *tmr;                /* Common Timer Structure */
#endif /* ANSI */
{
   CmTmrArg         arg;                /* Timer Arguments to be passed */

   TRC3(szStopTmr)

#ifdef DEBUGP
   SZDBGP(DBGMASK_LYR, (szCb.init.prntBuf,
          "szStopTmr(event(%d))\n", tmr->tmrEvnt));
#endif
   if (tmr->tmrEvnt != TMR_NONE)
   {
      /* sz003.301: Added hooks for PSF-S1AP */
      /* Send the runtime update to peer to stop the timer */
#ifdef YT
      if (tmr->tmrEvnt == SZ_TMR_WAIT_BNDCFM)
      {
         YT_RTUPD_MOD(YT_UPD_SCT_TMR_CB, (SzSctSapCb *)tmr->cb);
      }
#endif /* YT */
      arg.tq      = szCb.szTq;
      arg.tqCp    = &szCb.szTqCp;
      arg.timers  = tmr;
      arg.cb      = (PTR)NULLP;
      arg.evnt    = NOTUSED;
      arg.wait    = NOTUSED;
      arg.tNum    = 0;
      arg.max     = 1;
      cmRmvCbTq(&arg);
   }

   RETVOID;
} /* end of szStopTmr() */

/*
 *
 *       Fun:   szTmrEvnt
 *
 *       Desc:  Process the S1AP timer event. 
 *
 *       Ret:   RETVOID
 *
 *       Notes: None
 *
 *       File:  sz_tmr.c
 *
 */
#ifdef ANSI
PUBLIC Void szTmrEvnt
(
PTR       cb,
S16       event
)
#else
PUBLIC Void szTmrEvnt(cb, event)
PTR       cb;
S16       event;
#endif
{
   TRC2(szTmrEvnt)
#ifdef DEBUGP
   SZDBGP(DBGMASK_LYR, (szCb.init.prntBuf,"szTmrEvnt(event(%d))\n", event));
#endif

   switch (event)
   {
      case SZ_TMR_WAIT_BNDCFM:
      {
         szBndTmrExpiry(cb);
         break;
      }
      default:
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SZLOGERROR_DEBUG(ESZ165, (ErrVal) event,
               "szTmrEvnt(): timer event for an unknown timer\n");
#endif
         break;
      }
   }
   RETVOID;
} /* end of szTmrEvnt */

/*
 *
 *       Fun:   szBndTmrExpiry
 *
 *       Desc:  Process the S1AP bind timer expiry. If the number of retry is
 *              less than the maximum retry counter, the bind request is sent
 *              again, else an alarm is raised to the layer manager.
 *
 *       Ret:   RETVOID
 *
 *       Notes: None
 *
 *       File:  sz_tmr.c
 *
 */
#ifdef ANSI
PRIVATE Void szBndTmrExpiry
(
PTR       cb
)
#else
PRIVATE Void szBndTmrExpiry(cb)
PTR       cb;
#endif
{
   SzSctSapCb *sctSapCb;
   SzUstaDgn dgn;

   TRC2(szBndTmrExpiry);

   /* sz003.301: Added hooks for PSF-S1AP */
   /* Ignoe the timer event if it is received at standBy node */
#ifdef YT
   if (YT_IS_ACTV() == FALSE)
   {
#ifdef DEBUGP
      SZDBGP(DBGMASK_LYR, (szCb.init.prntBuf,"Standby Node\n"));
#endif
      RETVOID;
   }
#endif /* YT */

   sctSapCb = (SzSctSapCb *) cb;
   if (sctSapCb->state == LSZ_SAP_BINDING)
   {
      if (sctSapCb->retryCnt < sctSapCb->maxBndRetry)
      {
         sctSapCb->retryCnt++;
         szStartTmr(sctSapCb->timers,(PTR)sctSapCb,
                      SZ_TMR_WAIT_BNDCFM,&sctSapCb->tBndTmr);
         (Void)SzLiSctBndReq(&sctSapCb->pst, sctSapCb->suId, sctSapCb->spId);
      }
      else
      {
         sctSapCb->retryCnt = 0;
         sctSapCb->state = LSZ_SAP_CFG;
         dgn.type = LSZ_USTA_DGNVAL_SAPID;
         dgn.u.sapId = sctSapCb->suId;
         szSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_BND_FAIL,
                     LCM_CAUSE_UNKNOWN, &dgn);
      }
   }
   RETVOID;
} /* end of szBndTmrExpiry */

/**********************************************************************
 
         End of file:     sq_tmr.c@@/main/3 - Mon Jan 10 22:17:07 2011
 
**********************************************************************/

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
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/3      ---      pkaX  1. Updated for S1AP release 3.1
/main/3   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
/main/3   sz006.301   ve    1. Removed un-necessary include files
/main/4   sz008.301 akaranth 1. Support for source RNC to target RNC.
*********************************************************************91*/
