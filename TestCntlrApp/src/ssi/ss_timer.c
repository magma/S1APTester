

/********************************************************************20**
 
     Name:     System Services -- Timing
 
     Type:     C source file
 
     Desc:     Source code for System Services related to timing.
 
     File:     ss_timer.c
 
     Sid:      sm_timer.c@@/main/1 - Mon Nov 17 15:54:38 2008
 
     Prg:      kp
  
*********************************************************************21*/


/* header include files (.h) */

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
  
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */

#include "ss_err.h"        /* errors */
#include "ss_dep.h"        /* implementation-specific */
#include "ss_queue.h"      /* queues */
#include "ss_msg.h"        /* messaging */
#include "ss_mem.h"        /* memory management interface */
#include "ss_gen.h"        /* general */



/* header/extern include files (.x) */

#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */

#include "ss_dep.x"        /* implementation-specific */
#include "ss_queue.x"      /* queues */
#include "ss_task.x"       /* tasking */
#include "ss_timer.x"      /* timers */
#include "ss_strm.x"       /* STREAMS */
#include "ss_msg.x"        /* messaging */
#include "ss_mem.x"        /* memory management interface */
#include "ss_drvr.x"       /* driver tasks */
#include "ss_gen.x"        /* general */


/* Forward declarations */

/* ss041.103 Declaration for STmrRegHndlr */
/* ss015.301 Changed the timer activation function type as all timer activation
 * functions are enclosed in a union. 
 */
#ifndef SS_MULTIPLE_PROCS
PRIVATE S16 STmrRegHndlr ARGS((
         Ent ent,
         Inst inst,
         S16 period,
         S16 units,
         SsTmrActvFn ssTmrActvFn
      ));
/* ss015.301: Removed the timer handler prototypes guarded under SS_MT_TMR and 
 * handled mtFlag in existing timer handlers. 
 */
#else /* SS_MULTIPLE_PROCS */
PRIVATE S16 STmrRegHndlr ARGS((
         ProcId proc,
         Ent ent,
         Inst inst,
         S16 period,
         S16 units,
         SsTmrActvFn ssTmrActvFn
      ));
#endif /* SS_MULTIPLE_PROCS */

/* ss041.103 Declaration for STmrDeregHndlr */
#ifndef SS_MULTIPLE_PROCS
PRIVATE S16 STmrDeregHndlr ARGS((
         Ent ent,
         Inst inst,
         S16 period,
         S16 units,
         SsTmrActvFn ssTmrActvFn
      ));
/* ss015.301 Removed the timer handler prototypes guarded under SS_MT_TMR and 
 * handled mtFlag in existing timer handlers.
 */
#else /* SS_MULTIPLE_PROCS */
PRIVATE S16 STmrDeregHndlr ARGS((
         ProcId proc,
         Ent ent,
         Inst inst,
         S16 period,
         S16 units,
         SsTmrActvFn ssTmrActvFn
      ));
#endif /* SS_MULTIPLE_PROCS */



/* ss028.103 - Modification for SRegCfgTmr Support */
/*
*
*       Fun:   Register Configurable Timer Task - timer
*
*       Desc:  This function is used to register a timer function for the
*              layer. The system services will periodically invoke the
*              function passed to it. The timer function will be used by the
*              layer to manage the layers internal protocol timers.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes:
*
*       File:  ss_timer.c
*
*/
/* ss029.103: addition: procId added and timer function type modified */ 
#ifndef SS_MULTIPLE_PROCS
#ifdef ANSI
PUBLIC S16 SRegCfgTmr
(
Ent ent,                    /* entity */
Inst inst,                  /* instance */
S16 period,                 /* period */
S16 units,                  /* period units */
PFS16 tmrFnct               /* timer function, typically SActvTmr */
)
#else
PUBLIC S16 SRegCfgTmr(ent, inst, period, units, tmrFnct)
Ent ent;                    /* entity */
Inst inst;                  /* instance */
S16 period;                 /* period */
S16 units;                  /* period units*/
PFS16 tmrFnct;              /* timer function, typically SActvTmr */
#endif
{
	S16 ret;
	/* ss015.301 - Enclosed all timer activation functions in a union. */
	SsTmrActvFn ssTmrActvFn={0};
	/* ss041.103 - Moved handling to STmrRegHndlr */

   TRC1(SRegCfgTmr);

   ssTmrActvFn.mtFlag = FALSE;
   ssTmrActvFn.actvFnc.tmrActvFn = tmrFnct;
   ret = STmrRegHndlr(ent, inst, period, units, ssTmrActvFn);

   RETVALUE(ret);
}

#else /* SS_MULTIPLE_PROCS */

#ifdef ANSI
PUBLIC S16 SRegCfgTmr
(
ProcId proc,                /* processor */
Ent ent,                    /* entity */
Inst inst,                  /* instance */
S16 period,                 /* period */
S16 units,                  /* period units */
PAIFTMRS16 tmrFnct               /* timer function, typically SActvTmr */
)
#else
PUBLIC S16 SRegCfgTmr(proc, ent, inst, period, units, tmrFnct)
ProcId proc;                /* processor */
Ent ent;                    /* entity */
Inst inst;                  /* instance */
S16 period;                 /* period */
S16 units;                  /* period units*/
PAIFTMRS16 tmrFnct;              /* timer function, typically SActvTmr */
#endif

{
   S16 ret;
   /* ss015.301 - Enclosed all timer activation functions in a union. */
   SsTmrActvFn ssTmrActvFn;
   /* ss041.103 - Moved handling to STmrRegHndlr */

   TRC1(SRegCfgTmr);

   ssTmrActvFn.mtFlag = FALSE;
   ssTmrActvFn.actvFnc.tmrActvFn = tmrFnct;
   ret = STmrRegHndlr(proc, ent, inst, period, units, ssTmrActvFn);

   RETVALUE(ret);
}

#endif /* SS_MULTIPLE_PROCS */


#ifndef SS_MULTIPLE_PROCS
/* ss041.103 - New function for MT timer reg */
#ifdef SS_MT_TMR
/*
*
*       Fun:   Register Configurable Timer Task - timer
*
*       Desc:  This function is used to register a timer function for the
*              layer. The system services will periodically invoke the
*              function passed to it. The timer function will be used by the
*              layer to manage the layers internal protocol timers.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: By invoking this function, Ent and Inst are passed in the
*              timer activation function.
*
*       File:  ss_timer.c
*
*/
#ifdef ANSI
PUBLIC S16 SRegCfgTmrMt
(
Ent ent,                    /* entity */
Inst inst,                  /* instance */
S16 period,                 /* period */
S16 units,                  /* period units */
PAIFTMRS16 tmrFnctMt        /* timer function, typically SActvTmr */
)
#else
PUBLIC S16 SRegCfgTmrMt(ent, inst, period, units, tmrFnctMt)
Ent ent;                    /* entity */
Inst inst;                  /* instance */
S16 period;                 /* period */
S16 units;                  /* period units*/
PAIFTMRS16 tmrFnctMt;       /* timer function, typically SActvTmr */
#endif
{
   S16 ret;
   /* ss015.301 - Enclosed all timer activation functions in a union. */
   SsTmrActvFn ssTmrActvFn;

   TRC1(SRegCfgTmrMt);

   ssTmrActvFn.actvFnc.tmrActvFnMt = tmrFnctMt;
   ssTmrActvFn.mtFlag = TRUE;
   ret = STmrRegHndlr(ent, inst, period, units, ssTmrActvFn);

   RETVALUE(ret);
}
#endif /* SS_MT_TMR */
#endif /* not SS_MULTIPLE_PROCS */

/* ss041.103 - Function for timer registration handling */
/*
*
*       Fun:   Timer registration handler function
*
*       Desc:  This function is called by the timer registration interface
*              functions, and does the actual handling for timer
*              registration.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes:
*
*       File:  ss_timer.c
*
*/

/* ss015.301 Changed the timer activation function type as all timer activation
 * functions are enclosed in a union.
 */

#ifndef SS_MULTIPLE_PROCS

#ifdef ANSI
PRIVATE S16 STmrRegHndlr
(
Ent ent,                    /* entity */
Inst inst,                  /* instance */
S16 period,                 /* period */
S16 units,                  /* period units */
SsTmrActvFn ssTmrActvFn               /* timer function, typically SActvTmr */
)
#else
PRIVATE S16 STmrRegHndlr(ent, inst, period, units, ssTmrActvFn)
Ent ent;                    /* entity */
Inst inst;                  /* instance */
S16 period;                 /* period */
S16 units;                  /* period units*/
SsTmrActvFn ssTmrActvFn;              /* timer function, typically SActvTmr */
#endif
/* ss015.301: Removed the timer handler prototypes guarded
 * under SS_MT_TMR and handled mtFlag in existing timer handlers.
 */

#else /* SS_MULTIPLE_PROCS */

#ifdef ANSI
PRIVATE S16 STmrRegHndlr
(
ProcId proc,                /* processor */
Ent ent,                    /* entity */
Inst inst,                  /* instance */
S16 period,                 /* period */
S16 units,                  /* period units */
SsTmrActvFn ssTmrActvFn     /* timer function */
)
#else
PRIVATE S16 STmrRegHndlr(proc, ent, inst, period, units, ssTmrActvFn)
ProcId proc;                /* processor */
Ent ent;                    /* entity */
Inst inst;                  /* instance */
S16 period;                 /* period */
S16 units;                  /* period units*/
SsTmrActvFn ssTmrActvFn;         /* timer function */
#endif

#endif /* SS_MULTIPLE_PROCS */
{
#if (ERRCLASS & ERRCLS_INT_PAR)
   U8 i;
#endif
   S16 ret;
   SsTmrEntry *tmr;
#ifdef SS_MULTIPLE_PROCS
#if (ERRCLASS & ERRCLS_INT_PAR)
   U16 procIdIdx;
#endif /* ERRCLASS & ERRCLS_INT_PAR */
#endif /* SS_MULTPLE_PROCS */

   TRC1(STmrRegHndlr);

#if (ERRCLASS & ERRCLS_INT_PAR)

#ifdef SS_MULTIPLE_PROCS
   if ((proc == SS_INV_PROCID) || (ent >= SS_MAX_ENT) ||  (inst >= SS_MAX_INST))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS528, ERRZERO, "Invalid processor/entity/instance");
      RETVALUE(RFAILED);
   }
#else /* SS_MULTIPLE_PROCS */
   if (ent >= SS_MAX_ENT ||  inst >= SS_MAX_INST)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS529, ERRZERO, "Invalid entity/instance");
      RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */

   /* check period */
   if (period <= 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS530, ERRZERO, "Invalid period");
      RETVALUE(RFAILED);
   }

   /* check period units*/
   if ((units < 1) || (units > SS_TICKS_SEC))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS531, ERRZERO, "Invalid period units");
      RETVALUE(RFAILED);
   }

   if(ssTmrActvFn.mtFlag == TRUE) 
   { 
   /* ss015.301 Enclosed all timer activation functions in a union. */
#ifndef SS_MULTIPLE_PROCS
#ifdef SS_MT_TMR
      if (ssTmrActvFn.actvFnc.tmrActvFnMt == NULLP)  
      {
         SSLOGERROR(ERRCLS_INT_PAR, ESS532, ERRZERO, "Null pointer");
         RETVALUE(RFAILED);
      }
#else
      RETVALUE(RFAILED);
#endif
#else
      RETVALUE(RFAILED);
#endif
   }
   else
   { 
      if (ssTmrActvFn.actvFnc.tmrActvFn == NULLP)  
      {
          SSLOGERROR(ERRCLS_INT_PAR, ESS532, ERRZERO, "Null pointer");
          RETVALUE(RFAILED);
      }
   } 

#ifdef SS_MULTIPLE_PROCS
   /* check if the procId has been registered with SSI */
   procIdIdx = SGetProcIdIdx(proc);

   if (procIdIdx == SS_INV_PROCID_IDX)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS533, ERRZERO,
                     "Could not find proc id index");
      RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */


   /* check task ID */
   /* lock TAPA task table */
   SS_ACQUIRE_SEMA(&osCp.tTskTblSem, ret);
   if (ret != ROK)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS534, ERRZERO,
                     "Could not lock TAPA task table");
      RETVALUE(RFAILED);
   }

#ifdef SS_MULTIPLE_PROCS
   if (osCp.tTskIds[procIdIdx][ent][inst] == SS_TSKNC)
#else /* SS_MULTIPLE_PROCS */
   if (osCp.tTskIds[ent][inst] == SS_TSKNC)
#endif /* SS_MULTIPLE_PROCS */
   {
      if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS535, ERRZERO,
                     "Could not release the semaphore");
      RETVALUE(RFAILED);
#endif
      }
      SSLOGERROR(ERRCLS_INT_PAR, ESS536, ERRZERO, "Unknown task");
      RETVALUE(RFAILED);
   }
   if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS537, ERRZERO,
                     "Could not release the semaphore");
   RETVALUE(RFAILED);
#endif
   }

#endif

   /* lock the timer table */
   ret = SLock(&osCp.tmrTblLock);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS538, (ErrVal) ret,
                     "Could not lock timer table");
#endif
      RETVALUE(ret);
   }


   /* check if we've got room for another timer */
   if (osCp.numTmrs == SS_MAX_TMRS)
   {
      if ( SUnlock(&osCp.tmrTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS539, ERRZERO,
                     "Could not unlock the semaphore");
         RETVALUE(RFAILED);
#endif
      }

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS540, ERRZERO, "Too many timers");
#endif

      RETVALUE(ROUTRES);
   }

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check through the timer table for a matching timer entry */
   for (i = 0; i < SS_MAX_TMRS; i++)
   {   
      if ((osCp.tmrTbl[i].ownerEnt == ent)
#ifdef SS_MULTIPLE_PROCS
            &&  (osCp.tmrTbl[i].ownerProc == proc)
#endif /* SS_MULTIPLE_PROCS */
            && (osCp.tmrTbl[i].ownerInst == inst)
            /* ss041.103 - Added mtFlag check */
            /* ss015.301 Enclosed all timer activation functions in a union. */
#ifndef SS_MULTIPLE_PROCS
#ifdef SS_MT_TMR
            && (osCp.tmrTbl[i].ssTmrActvFn.mtFlag == ssTmrActvFn.mtFlag)
            && ((ssTmrActvFn.mtFlag == FALSE
                  && osCp.tmrTbl[i].ssTmrActvFn.actvFnc.tmrActvFn == ssTmrActvFn.actvFnc.tmrActvFn)  
               || osCp.tmrTbl[i].ssTmrActvFn.actvFnc.tmrActvFnMt == ssTmrActvFn.actvFnc.tmrActvFnMt)
#else
            && (osCp.tmrTbl[i].ssTmrActvFn.actvFnc.tmrActvFn == ssTmrActvFn.actvFnc.tmrActvFn)
#endif
#else
            && (osCp.tmrTbl[i].ssTmrActvFn.actvFnc.tmrActvFn == ssTmrActvFn.actvFnc.tmrActvFn)
#endif
            && (osCp.tmrTbl[i].interval == (U32) ((period * SS_TICKS_SEC) / units)))
      {
         /* is this timer in use ? (unexpired) */
         if (osCp.tmrTbl[i].used == TRUE)
         {  
            /* to prevent the same timer to be registered with SS  UNLOCK and */
            /* then RFAIL */
            if (SUnlock(&osCp.tmrTblLock) != ROK)
            {
#if (ERRCLASS & ERRCLS_DEBUG)
   SSLOGERROR(ERRCLS_DEBUG, ESS541, ERRZERO, "Could not unlock the semaphore");
   RETVALUE(RFAILED);
#endif
            }
            RETVALUE(RFAILED);
         }
      }
   }
#endif

   /* fill in the information we have into the timer entry */
   tmr = &osCp.tmrTbl[osCp.nxtTmrEntry];
   tmr->tmrId     = osCp.nxtTmrEntry;
#ifdef SS_MULTIPLE_PROCS
   tmr->ownerProc = proc;
#endif /* SS_MULTIPLE_PROCS */
   tmr->ownerEnt  = ent;
   tmr->ownerInst = inst;
   tmr->interval  = (U32) ((period * SS_TICKS_SEC) / units);
   tmr->ssTmrActvFn.mtFlag = ssTmrActvFn.mtFlag;

   /* ss041.103 */
   /* ss015.301 Enclosed all timer activation functions in a union. */
#ifndef SS_MULTIPLE_PROCS
#ifdef SS_MT_TMR
   if (ssTmrActvFn.mtFlag == TRUE)
   {
      tmr->ssTmrActvFn.actvFnc.tmrActvFnMt = ssTmrActvFn.actvFnc.tmrActvFnMt;  
   }
   else
#endif
#endif
   {
      tmr->ssTmrActvFn.actvFnc.tmrActvFn = ssTmrActvFn.actvFnc.tmrActvFn;
   }


   /* ask the implementation to start the timer */
   ret = ssdRegTmr(tmr);
   if (ret != ROK)
   {
      tmr->tmrId = 0;
#ifdef SS_MULTIPLE_PROCS
      tmr->ownerProc = PROCNC;
#endif /* SS_MULTIPLE_PROCS */
      tmr->ownerEnt = ENTNC;
      tmr->ownerInst = INSTNC;
      tmr->interval = 0;
      /* ss015.301 Enclosed all timer activation functions in a union. */
      tmr->ssTmrActvFn.mtFlag = FALSE;
      tmr->ssTmrActvFn.actvFnc.tmrActvFn = NULLP;
#ifndef SS_MULTIPLE_PROCS
#ifdef SS_MT_TMR
      tmr->ssTmrActvFn.actvFnc.tmrActvFnMt = NULLP;
#endif
#endif
   }
   else
   {
      tmr->used = TRUE;
      osCp.nxtTmrEntry = tmr->nxt;
      osCp.numTmrs++;
   }


   /* unlock the timer table */
   if ( SUnlock(&osCp.tmrTblLock) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS542, ERRZERO,
                     "Could not unlock the semaphore");
      RETVALUE(RFAILED);
#endif
   }

   RETVALUE(ret);
}



/*
*
*       Fun:   SDeregCfgTmr  
*
*       Desc:  This function is used to deregister a timer function.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_timer.c
*
*/
/* ss029.103: addition: procId added and timer function type modified */ 
#ifndef SS_MULTIPLE_PROCS

#ifdef ANSI
PUBLIC S16 SDeregCfgTmr
(
Ent ent,                    /* entity */
Inst inst,                  /* instance */
S16 period,                 /* period */
S16 units,                  /* period units */
PFS16 tmrFnct               /* timer function */
)
#else
PUBLIC S16 SDeregCfgTmr(ent, inst, period, units, tmrFnct)
Ent ent;                    /* entity */
Inst inst;                  /* instance */
S16 period;                 /* period */
S16 units;                  /* period units*/
PFS16 tmrFnct;              /* timer function */
#endif
{
   S16 ret;
   /* ss015.301 Enclosed all timer activation functions in a union. */
   SsTmrActvFn ssTmrActvFn = {0};
   /* ss041.103 - Moved handling to STmrDeregHndlr */

   TRC1(SDeregCfgTmr);

   ssTmrActvFn.mtFlag = FALSE;
   ssTmrActvFn.actvFnc.tmrActvFn = tmrFnct;  
   ret = STmrDeregHndlr(ent, inst, period, units, ssTmrActvFn);

   RETVALUE(ret);
}

#else /* SS_MULTIPLE_PROCS */

#ifdef ANSI
PUBLIC S16 SDeregCfgTmr
(
ProcId proc,                /* processor */
Ent ent,                    /* entity */
Inst inst,                  /* instance */
S16 period,                 /* period */
S16 units,                  /* period units */
PAIFTMRS16 tmrFnct               /* timer function */
)
#else
PUBLIC S16 SDeregCfgTmr(proc, ent, inst, period, units, tmrFnct)
ProcId proc;                /* processor */
Ent ent;                    /* entity */
Inst inst;                  /* instance */
S16 period;                 /* period */
S16 units;                  /* period units*/
PAIFTMRS16 tmrFnct;              /* timer function */
#endif
{
   S16 ret;
   /* ss015.301 Enclosed all timer activation functions in a union. */ 
   SsTmrActvFn ssTmrActvFn;

   /* ss041.103 - Moved handling to STmrDeregHndlr */

   TRC1(SDeregCfgTmr);

   ssTmrActvFn.mtFlag = FALSE;
   ssTmrActvFn.actvFnc.tmrActvFn = tmrFnct;  
   ret = STmrDeregHndlr(proc, ent, inst, period, units, ssTmrActvFn);

   RETVALUE(ret);
}

#endif /* SS_MULTIPLE_PROCS */


/* ss041.103 - Addition to support MT timer dereg */
#ifndef SS_MULTIPLE_PROCS
#ifdef SS_MT_TMR
/*
*
*       Fun:   SDeregCfgTmrMt
*
*       Desc:  This function is used to deregister an MT timer function.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_timer.c
*
*/
#ifdef ANSI
PUBLIC S16 SDeregCfgTmrMt
(
Ent ent,                    /* entity */
Inst inst,                  /* instance */
S16 period,                 /* period */
S16 units,                  /* period units */
PAIFTMRS16 tmrFnctMt               /* timer function */
)
#else
PUBLIC S16 SDeregCfgTmrMt(ent, inst, period, units, tmrFnctMt)
Ent ent;                    /* entity */
Inst inst;                  /* instance */
S16 period;                 /* period */
S16 units;                  /* period units*/
PAIFTMRS16 tmrFnctMt;              /* timer function */
#endif
{
   S16 ret;
   /* ss015.301 Enclosed all timer activation functions in a union. */
   SsTmrActvFn ssTmrActvFn;

   TRC1(SDeregCfgTmrMt);

   ssTmrActvFn.actvFnc.tmrActvFnMt = tmrFnctMt;
   ssTmrActvFn.mtFlag = TRUE;

   ret = STmrDeregHndlr(ent, inst, period, units, ssTmrActvFn);

   RETVALUE(ret);
}
#endif /* SS_MT_TMR */
#endif /* not SS_MULTIPLE_PROCS */


/* ss041.103 - Addition of STmrDeregHndlr */
/*
*
*       Fun:   STmrDeregHndlr  
*
*       Desc:  This function is used to deregister a timer function.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_timer.c
*
*/
/* ss029.103: addition: procId added and timer function type modified */ 

/* ss015.301 Changed the timer activation function type as all timer activation
 * functions are enclosed in a union.
 */
#ifndef SS_MULTIPLE_PROCS
#ifdef ANSI
PRIVATE S16 STmrDeregHndlr
(
Ent ent,                    /* entity */
Inst inst,                  /* instance */
S16 period,                 /* period */
S16 units,                  /* period units */
SsTmrActvFn ssTmrActvFn           /* timer function */
)
#else
/* ss017.301: Modified the prototype of STmrDeregHndlr for Non-ANSI
 * compilation.
 */
PRIVATE S16 STmrDeregHndlr(ent, inst, period, units, ssTmrActvFn)
Ent ent;                    /* entity */
Inst inst;                  /* instance */
S16 period;                 /* period */
S16 units;                  /* period units*/
SsTmrActvFn ssTmrActvFn;          /* timer function */
#endif
/* ss015.301: Removed the timer handler prototypes guarded under SS_MT_TMR
 * and handled mtFlag in existing timer handlers.
 */

#else /* SS_MULTIPLE_PROCS */

#ifdef ANSI
PRIVATE S16 STmrDeregHndlr
(
ProcId proc,                /* processor */
Ent ent,                    /* entity */
Inst inst,                  /* instance */
S16 period,                 /* period */
S16 units,                  /* period units */
SsTmrActvFn ssTmrActvFn          /* timer function */
)
#else
PRIVATE S16 STmrDeregHndlr(proc, ent, inst, period, units, ssTmrActvFn)
ProcId proc;                /* processor */
Ent ent;                    /* entity */
Inst inst;                  /* instance */
S16 period;                 /* period */
S16 units;                  /* period units*/
SsTmrActvFn ssTmrActvFn;         /* timer function */
#endif

#endif /* SS_MULTIPLE_PROCS */
{
   S16 ret;
   S16 idx;
   SsTmrEntry *tmr;
#ifdef SS_MULTIPLE_PROCS
#if (ERRCLASS & ERRCLS_INT_PAR)
   U16 procIdIdx;
#endif /* ERRCLASS & ERRCLS_INT_PAR */
#endif /* SS_MULTIPLE_PROCS */


   TRC1(STmrDeregHndlr);


#if (ERRCLASS & ERRCLS_INT_PAR)

#ifdef SS_MULTIPLE_PROCS
   if ((proc == SS_INV_PROCID) || (ent >= SS_MAX_ENT) ||  (inst >= SS_MAX_INST))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS543, ERRZERO, "Invalid processor/entity/instance");
      RETVALUE(RFAILED);
   }

#else /* SS_MULTIPLE_PROCS */
   if (ent >= SS_MAX_ENT ||  inst >= SS_MAX_INST)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS544, ERRZERO, "Invalid entity/instance");
      RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */
   /* check period */
   if (period <= 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS545, ERRZERO, "Invalid period");
      RETVALUE(RFAILED);
   }

   /* check period units */
   if ((units < 1) || (units > SS_TICKS_SEC))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS546, ERRZERO, "Invalid period units");
      RETVALUE(RFAILED);
   }

   /* check timer function */
   if(ssTmrActvFn.mtFlag == TRUE)
   {
#ifndef SS_MULTIPLE_PROCS
#ifdef SS_MT_TMR
   if (ssTmrActvFn.actvFnc.tmrActvFnMt == NULLP)  
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS547, ERRZERO, "Null pointer");
      RETVALUE(RFAILED);
   }
#else
    RETVALUE(RFAILED);
#endif
#else
    RETVALUE(RFAILED);
#endif
 
   }
   else
   {
   if (ssTmrActvFn.actvFnc.tmrActvFn == NULLP)  
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS547, ERRZERO, "Null pointer");
      RETVALUE(RFAILED);
   }
  }

#ifdef SS_MULTIPLE_PROCS
   /* check if the procId has been registered with SSI */
   procIdIdx = SGetProcIdIdx(proc);

   if (procIdIdx == SS_INV_PROCID_IDX)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS548, ERRZERO,
                     "Could not find proc id index");
      RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */

   /* check task ID */
   /* lock TAPA task table */
   SS_ACQUIRE_SEMA(&osCp.tTskTblSem, ret);
   if (ret != ROK)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS549, ERRZERO,
                     "Could not lock TAPA task table");
      RETVALUE(RFAILED);
   }

#ifdef SS_MULTIPLE_PROCS
   if (osCp.tTskIds[procIdIdx][ent][inst] == SS_TSKNC)
#else /* SS_MULTIPLE_PROCS */
   if (osCp.tTskIds[ent][inst] == SS_TSKNC)
#endif /* SS_MULTIPLE_PROCS */
   {
      if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS550, ERRZERO,
                     "Could not release the semaphore");
         RETVALUE(RFAILED);
#endif
      }
      SSLOGERROR(ERRCLS_INT_PAR, ESS551, ERRZERO, "Unknown task");
      RETVALUE(RFAILED);
   }
   if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS552, ERRZERO,
                     "Could not release the semaphore");
      RETVALUE(RFAILED);
#endif
    }

#endif

   /* lock the timer table */
   ret = SLock(&osCp.tmrTblLock);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS553, (ErrVal) ret,
                     "Could not lock timer table");
#endif
      RETVALUE(ret);
   }


   /* Note: Right now, we're using ent, inst and tmrActvFn to locate
    *       the timer,, this will change to using tmrId, some day.
    */

   /* locate the timer to delete in the timer table */
   for (idx = 0;  idx < SS_MAX_TMRS;  idx++)
   {
      /* ss021.103 - Modification find timer by ent, inst, func, and period */
      /* ss029.103: addition: multiple procId related changes */ 
      if (osCp.tmrTbl[idx].ownerEnt == ent
#ifdef SS_MULTIPLE_PROCS
            &&  osCp.tmrTbl[idx].ownerProc == proc 
#endif /* SS_MULTIPLE_PROCS */
            &&  osCp.tmrTbl[idx].ownerInst == inst
#ifndef SS_MULTIPLE_PROCS
#ifdef SS_MT_TMR
           /*
	    *  ss015.301 - Modifed as timer activation functions
	    *  enclosed in a union. 
	    */
            &&  osCp.tmrTbl[idx].ssTmrActvFn.mtFlag == ssTmrActvFn.mtFlag
            && ((ssTmrActvFn.mtFlag == FALSE
                  &&  osCp.tmrTbl[idx].ssTmrActvFn.actvFnc.tmrActvFn == ssTmrActvFn.actvFnc.tmrActvFn)
               || osCp.tmrTbl[idx].ssTmrActvFn.actvFnc.tmrActvFnMt == ssTmrActvFn.actvFnc.tmrActvFnMt)
#else
            &&  osCp.tmrTbl[idx].ssTmrActvFn.actvFnc.tmrActvFn == ssTmrActvFn.actvFnc.tmrActvFn
#endif
#else
            &&  osCp.tmrTbl[idx].ssTmrActvFn.actvFnc.tmrActvFn == ssTmrActvFn.actvFnc.tmrActvFn
#endif
            &&  osCp.tmrTbl[idx].interval == (U32) ((period * SS_TICKS_SEC) / units))
      {
         break;
      }
   }

   if (idx == SS_MAX_TMRS)
   {
      if ( SUnlock(&osCp.tmrTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS554, ERRZERO,
                     "Could not unlock the semaphore");
         RETVALUE(RFAILED);
#endif
      }

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS555, ERRZERO, "Could not locate timer");
#endif

      RETVALUE(RFAILED);
   }


   /* ask the implementation to shut down this timer */
   tmr = &osCp.tmrTbl[idx];
   ret = ssdDeregTmr(tmr);
   if (ret == ROK)
   {
      tmr->used = FALSE;
      tmr->tmrId = 0;
#ifdef SS_MULTIPLE_PROCS
      tmr->ownerProc = PROCNC;
#endif /* SS_MULTIPLE_PROCS */
      tmr->ownerEnt = ENTNC;
      tmr->ownerInst = INSTNC;
      tmr->interval = 0;
      /*
       *  ss015.301: Modifed as timer activation functions enclosed in a union. 
       */
      tmr->ssTmrActvFn.mtFlag = FALSE;
      tmr->ssTmrActvFn.actvFnc.tmrActvFn = NULLP;
#ifndef SS_MULTIPLE_PROCS
#ifdef SS_MT_TMR
      tmr->ssTmrActvFn.actvFnc.tmrActvFnMt = NULLP;
#endif
#endif

      tmr->nxt = osCp.nxtTmrEntry;
      osCp.nxtTmrEntry = (SsIdx)idx;
      osCp.numTmrs--;
   }


   /* unlock the timer table */
   if ( SUnlock(&osCp.tmrTblLock) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS556, ERRZERO,
                     "Could not unlock the semaphore");
      RETVALUE(RFAILED);
#endif
   }


   RETVALUE(ret);
}




/********************************************************************30**
  
         End of file:     sm_timer.c@@/main/1 - Mon Nov 17 15:54:38 2008
  
*********************************************************************31*/
  
  
/********************************************************************40**
  
        Notes: 
  
*********************************************************************41*/
  
/********************************************************************50**

*********************************************************************51*/

   
/********************************************************************60**
  
        Revision history:
  
*********************************************************************61*/
  
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.1          ---      kp   1. initial release
  
1.2          ---      bsr  1. Regenerated the error codes

1.3          ---      kp   1. Regenerated error codes
1.3+        ss006.13  jn   2. Compile warning - "Value computed
                              is not used" removed for
                              SS_RELEASE_SEMA and SUnlock.
1.3+        ss021.103 bjp  3. Modification to find a timer by ent, inst,
                                 func, and period in SDeregTmr
                              Check for duplicate timer in SRegTmr
1.3+        ss028.103 bjp  1. Modification for SRegCfgTmr support
1.3+        ss029.103 kkj  1. Multiple proc ids support added
1.3+        ss041.103 apany 1. Multithreading support: a new
                                timer actv function that has ent
                                and inst passed as arguments.
/main/1      ---       rp   1. SSI enhancements for Multi-core architecture
                               support
/main/1      ss002.301 rss  1. Added mtFlag variable in STmrDeregHndlr function
                               argument to cater Non Ansi compilation

/main/1       ss015.301 akapoor  1. Enclosed all timer activation functions in
                                    a union.
                                 2. Removed the timer handler prototypes guarded
                                    under SS_MT_TMR and handled mtFlag in existing
                                    timer handlers.
/main/1       ss017.301 akapoor  1. Modified the prototype of STmrDeregHndlr for
                                    Non-ANSI compilation.
*********************************************************************91*/
