

/********************************************************************20**
 
     Name:     System Services -- Task Management
 
     Type:     C source file
 
     Desc:     Source code for System Services functions for task mgmt.
 
     File:     ss_task.c
 
     Sid:      sm_task.c@@/main/1 - Mon Nov 17 15:54:37 2008
 
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
#include "ss_task.h"       /* tasking */
#include "ss_msg.h"        /* messaging */
#include "ss_mem.h"        /* memory management interface */
#include "ss_gen.h"        /* general */

#ifdef SS_FBSED_TSK_REG
#include "cm_task.h"
#endif /* SS_FBSED_TSK_REG */

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
#include "cm_lib.x"        /* general */

/* ss001.301: additions */
#ifdef SS_LOGGER_SUPPORT 
/* ss002.301: Fixed warings */
#ifdef SS_MT 
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif /* SS_MT */
#ifdef WIN32
#include <stdio.h>
#include "winsock2.h"
#include "ws2tcpip.h"
#endif /* WIN32 */
#endif /*  SS_LOGGER_SUPPORT */

/* ss001.301: additions */
#ifdef SS_WATCHDOG 
#include <stdio.h>
#ifdef SS_MT 
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/poll.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#elif WIN32
#include "winsock2.h"
#include "ws2tcpip.h"
#endif /* WIN32 */
#endif /* SS_WATCHDOG */

/* ss001.301: additions */
#ifdef SS_FBSED_TSK_REG 
#include "cm_task.x"
#endif /* SS_FBSED_TSK_REG */
/* ss004.301 : Cavium changes */
#ifdef SS_SEUM_CAVIUM
/* cvmx includes files */
#include "cvmx-config.h"
#include "cvmx.h"
#include "cvmx-pow.h"
#include "cvmx-tim.h"
#include "cvmx-fpa.h"
#include "cvmx-helper-fpa.h"
#include "cvmx-malloc.h"
#endif /* SS_SEUM_CAVIUM */

/* ss029.103: modification: 
   Old SSI functions are not supported with multiple procIds */ 
#ifndef SS_MULTIPLE_PROCS

/*
*
*       Fun:   SRegInit
*
*       Desc:  This function is used to register an initialization function
*              for the layer. The system services will invoke the function
*              passed to it one time. The initialization function will be
*              used by the layer to initilize the layer.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_task.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SRegInit
(
Ent ent,                    /* entity */
Inst inst,                  /* instance */
PAIFS16 initFnct            /* initialization function */
)
#else
PUBLIC S16 SRegInit(ent, inst, initFnct)
Ent ent;                    /* entity */
Inst inst;                  /* instance */
PAIFS16 initFnct;           /* initialization function */
#endif
{
   /* ss021.103 - Addition for return value and pointer */
   S16         ret;     /* return value */
   SsTTskEntry *tTsk;

   TRC1(SRegInit);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check entity and instance ranges */
   if (ent >= SS_MAX_ENT ||  inst >= SS_MAX_INST)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS350, ERRZERO, "Invalid entity/instance");
      RETVALUE(RFAILED);
   }

   /* check initialization function */
   if (initFnct == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS351, ERRZERO, "Null pointer");
      RETVALUE(RFAILED);
   }
#endif

   /* ss021.103 - Modification to store initialization function */
   /* Acquire the counting semaphore for all other system
    *  tasks (this call is either running in one system task's
    *  context, or in SInit()'s context). Once we have all of
    *  them, SPstTsk() cannot run, so we can do things to the
    *  TAPA task table.
    */

   /* ss025.103 - Addition of lock around counting semaphore */
   /* lock system task table */
   ret = SLock(&osCp.sTskTblLock);
   if (ret != ROK)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS352, ERRZERO,
                     "Could not lock system task table");
      RETVALUE(RFAILED);
   }

   SS_ACQUIRE_ALL_SEMA(&osCp.tTskTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS353, ERRZERO,
                 "Could not lock TAPA task table");
#endif

      RETVALUE(RFAILED);
   }


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check count of tasks */
   if (osCp.numTTsks == SS_MAX_TTSKS)
   {
      SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);
      SSLOGERROR(ERRCLS_INT_PAR, ESS354, ERRZERO, "Too many tasks");

      /* ss025.103 - Addition of unlock around counting semephore */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS355, ERRZERO,
                      "Could not give the Semaphore");
         RETVALUE(RFAILED);
#endif
      }

      RETVALUE(ROUTRES);
   }

   /* check if entity and instance already registered */
   if (osCp.tTskIds[ent][inst] != SS_TSKNC)
   {
      SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);
      SSLOGERROR(ERRCLS_INT_PAR, ESS356, ERRZERO,
                 "Entity and instance already registered");

      /* ss025.103 - Addition of unlock around counting semaphore */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS357, ERRZERO,
                         "Could not give the Semaphore");
         RETVALUE(RFAILED);
#endif
      }

      RETVALUE(RFAILED);
   }
#endif

   tTsk = &osCp.tTskTbl[osCp.nxtTTskEntry];

   tTsk->used     = TRUE;
   tTsk->ent      = ent;
   tTsk->inst     = inst;
   tTsk->tskType  = (Ttype)NULLD;
   tTsk->tskPrior = (Prior)NULLD;
   tTsk->initTsk  = initFnct;
   tTsk->actvTsk  = (ActvTsk)NULLP;
   tTsk->sTsk     = NULLP;

   osCp.tTskIds[ent][inst] = osCp.nxtTTskEntry;
   osCp.nxtTTskEntry = tTsk->nxt;
   osCp.numTTsks++;

   /* Activate initialization function, if present. Like
    *  SRegInit(), we use hard-coded parameters. Note: we
    *  assume that the initialization function is not
    *  going to call SRegTTsk() or SPstTsk(). If it does,
    *  this thread will freeze up as we are holding the
    *  TAPA task table counting semaphore.
    */
   /* ss024.103 - Modification for memory calculator tool */
#ifndef USE_MEMCAL
   (Void)(*initFnct)(ent, inst, DFLT_REGION, PWR_UP);
#else
   (Void)(*initFnct)(ent, inst, SS_STATIC_REGION, PWR_UP);
#endif /* USE_MEMCAL */

   /* unlock the table */
   SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);

   /* ss025.103 - Addition of unlock around counting semaphore */
   if ( SUnlock(&osCp.sTskTblLock) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS358, ERRZERO,
                      "Could not give the Semaphore");
      RETVALUE(RFAILED);
#endif
   }

   RETVALUE(ROK);
} /* SRegInit */



/*
*
*       Fun:   SRegActvTsk
*
*       Desc:  This function is used to register an activation function
*              for the layer. The system services will invoke the
*              function passed to it whenever a task buffer is received.
*              The activation function will be used by the layer to receive
*              messages from other entities.  It allows a priority to be
*              associated with the task so that it can be preempted if
*              necessary.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: We pass NULLP for the initialization function, because
*              it is assumed that whoever is using this call will also
*              be calling SRegInit().
*
*       File:  ss_task.c
*
*/
#ifdef ANSI
PUBLIC S16 SRegActvTsk
(
Ent ent,                       /* entity */
Inst inst,                     /* instance */
Ttype ttype,                   /* task type */
Prior prior,                   /* task priority */
ActvTsk actvTsk                /* activate task function */
)
#else
PUBLIC S16 SRegActvTsk(ent, inst, ttype, prior, actvTsk)
Ent ent;                       /* entity */
Inst inst;                     /* instance */
Ttype ttype;                   /* task type */
Prior prior;                   /* task priority */
ActvTsk actvTsk;               /* activate task function */
#endif
{
   S16 ret;
   SSTskId sTskId;
   Prior spri;
   /* ss021.103 - Addition for pointer */
   SsTTskEntry *tTsk;

   TRC1(SRegActvTsk);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check entity and instance ranges */
   if (ent >= SS_MAX_ENT ||  inst >= SS_MAX_INST)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS359, ERRZERO, "Invalid entity/instance");
      RETVALUE(RFAILED);
   }

   /* check activation function */
   if (actvTsk == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS360, ERRZERO, "Null pointer");
      RETVALUE(RFAILED);
   }

   /* check task type */
   if (ttype != TTNORM  &&  ttype != TTPERM)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS361, ERRZERO, "Invalid task type");
      /* ss021.103 - Addition of return fail for invalid task type */
      RETVALUE(RFAILED);
   }

   /* check task priority */
   if (prior > PRIOR3)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS362, ERRZERO, "Invalid task priority");
      RETVALUE(RFAILED);
   }
#endif

   /* lock system task table */
   ret = SLock(&osCp.sTskTblLock);
   if (ret != ROK)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS363, ERRZERO,
                     "Could not lock system task table");
      RETVALUE(RFAILED);
   }

   /* lock TAPA task table */
   SS_ACQUIRE_ALL_SEMA(&osCp.tTskTblSem, ret);
   if (ret != ROK)
   {
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS364, ERRZERO,
                         "Could not give the Semaphore");
         RETVALUE(RFAILED);
#endif
      }
 
      SSLOGERROR(ERRCLS_DEBUG, ESS365, ERRZERO,
                     "Could not lock TAPA task table");
      RETVALUE(RFAILED);
   }
   /* ss021.103 - Modification for SRegInit not called yet */
   /* check if entity and instance already registered */
   if (osCp.tTskIds[ent][inst] == SS_TSKNC)
   {

#if (ERRCLASS & ERRCLS_INT_PAR)
      /* check count of tasks */
      if (osCp.numTTsks == SS_MAX_TTSKS)
      {
         SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);

         /* ss025.103 - Addition of unlock around counting semaphore */
         if ( SUnlock(&osCp.sTskTblLock) != ROK)
         {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS366, ERRZERO,
                         "Could not give the Semaphore");
            RETVALUE(RFAILED);
#endif
         }
         SSLOGERROR(ERRCLS_INT_PAR, ESS367, ERRZERO, "Too many tasks");
         RETVALUE(ROUTRES);
      }
#endif

      tTsk = &osCp.tTskTbl[osCp.nxtTTskEntry];
      tTsk->used     = TRUE;
      tTsk->ent      = ent;
      tTsk->inst     = inst;
      tTsk->initTsk  = (PAIFS16)NULLP;
      tTsk->actvTsk  = (ActvTsk)NULLP;
      tTsk->sTsk     = NULLP;

      osCp.tTskIds[ent][inst] = osCp.nxtTTskEntry;
      osCp.nxtTTskEntry = tTsk->nxt;
      osCp.numTTsks++;
   }


   /* check and bump the priority if it is a permanent task */
   if(ttype == TTPERM)
   {
      prior = PRIOR3;
   }

   /* ss021.103 - Modification to register task information */
   /*  We fill up the current available slot with all the
    *  information we've been given. Update table information,
    *  and the task is registered.
    */

   tTsk = &osCp.tTskTbl[osCp.tTskIds[ent][inst]];
   
#if (ERRCLASS & ERRCLS_INT_PAR)
   if (tTsk->actvTsk != (ActvTsk)NULLP)
   {
      SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);

      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS368, ERRZERO,
                    "Could not give the Semaphore");
         RETVALUE(RFAILED);
#endif
      }

      SSLOGERROR(ERRCLS_INT_PAR, ESS369, ERRZERO, 
                 "ActvTask already registered");
      RETVALUE(RFAILED);
   }
#endif

   tTsk->tskType  = ttype;
   tTsk->tskPrior = prior;
   tTsk->actvTsk  = actvTsk;

   /* unlock the table */
   SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);

   if ( SUnlock(&osCp.sTskTblLock) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS370, ERRZERO,
                      "Could not give the Semaphore");
      RETVALUE(RFAILED);
#endif
   }

   /*  Now we create a system task--one per TAPA task is the
    *  semantics of SRegActvTsk().
    */
   if (ttype == TTNORM)
      spri = SS_NORM_TSK_PRI;
   else
      spri = SS_PERM_TSK_PRI;

   ret = SCreateSTsk(spri, &sTskId);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS371, (ErrVal) ret,
                     "Could not create system task");
#endif

      SDeregTTsk(ent, inst);
      RETVALUE(ret);
   }


   /*  Attach the TAPA task we just registered, to the system
    *  task we just created.
    */
   ret = SAttachTTsk(ent, inst, sTskId);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS372, (ErrVal) ret,
                     "Could not attach TAPA task to system task");
#endif
      SDestroySTsk(sTskId);
      SDeregTTsk(ent, inst);
   }


   RETVALUE(ret);

} /* SRegActvTsk */
 

/*
*
*       Fun:   Deregister Initialize, task buffer and timer
*
*       Desc:  This function is used to deregister the initialization,
*              activation and timer functions for a task.
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  ss_task.c
*
*/
#ifdef ANSI
PUBLIC S16 SDeregInitTskTmr
(
Ent ent,                       /* entity */
Inst inst                      /* instance */
)
#else
PUBLIC S16 SDeregInitTskTmr(ent, inst)
Ent ent;                       /* entity */
Inst inst;                     /* instance */
#endif
{
   SsTTskEntry *tTsk;
   SsSTskEntry *sTsk;
   S16         ret;
   SSTskId     sTskId;
   SsIdx       idx;
   Bool        destroySTsk;


   TRC1(SDeregInitTskTmr);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check entity and instance ranges */
   if (ent >= SS_MAX_ENT  ||  inst >= SS_MAX_INST)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS373, ERRZERO, "Invalid entity/instance");
      RETVALUE(RFAILED);
   }
#endif

   /* ss025.103 - Addition of lock around counting semaphore */
   /* lock system task table */
   ret = SLock(&osCp.sTskTblLock);
   if (ret != ROK)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS374, ERRZERO,
                     "Could not lock system task table");
      RETVALUE(RFAILED);
   }

   /* lock the TAPA task table */
   SS_ACQUIRE_ALL_SEMA(&osCp.tTskTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS375, ERRZERO,
                     "Could not lock TAPA task table");
#endif

      RETVALUE(RFAILED);
   }


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check whether this entity is registered */
   if (osCp.tTskIds[ent][inst] == SS_TSKNC)
   {
      SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);
      SSLOGERROR(ERRCLS_INT_PAR, ESS376, ERRZERO, "Unknown task");

      /* ss025.103 - Addition of unlock around counting semaphore */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS377, ERRZERO,
                         "Could not give the Semaphore");
         RETVALUE(RFAILED);
#endif
      }

      RETVALUE(RFAILED);
   }
#endif


   /* get out the TAPA task entry */
   tTsk = &osCp.tTskTbl[osCp.tTskIds[ent][inst]];

   /* get out the system task that's running this TAPA task */
   sTsk = tTsk->sTsk;

   /* get out the ID of this system task */
   if (sTsk != NULLP)
   {
      sTskId = sTsk->tskId;
   }
   else 
      sTskId = 0;

   /* unlock the TAPA task table */
   SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);

   /* ss025.103 - Addition of unlock around counting semaphore */
   if ( SUnlock(&osCp.sTskTblLock) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS378, ERRZERO,
                      "Could not give the Semaphore");
      RETVALUE(RFAILED);
#endif
   }


   /* deregister the TAPA task */
   if (SDeregTTsk(ent, inst) != ROK)
   {
      RETVALUE(RFAILED);
   }


   /* Now, if the TAPA task was attached, and nobody else is using that
    *  system task, we should destroy it.
    */
   if (sTsk != NULLP)
   {
      destroySTsk = FALSE;

      /* lock the system task table */
      ret = SLock(&osCp.sTskTblLock);
      if (ret != ROK)
      {

#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS379, (ErrVal) ret,
                        "Could not lock system task table");
#endif

         RETVALUE(RFAILED);
      }

      idx = (SsIdx) sTskId;
      sTsk = &osCp.sTskTbl[idx];

      /* check if the system task is still around */
      if (sTsk->used != TRUE)
      {

/* ss006.13: addition */
         if ( SUnlock(&osCp.sTskTblLock) != ROK)
         {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS380, ERRZERO,
                         "Could not give the Semaphore");
            RETVALUE(RFAILED);
#endif
         }

         RETVALUE(ROK);
      }

      /* check if the system task is dying already */
      if (sTsk->termPend)
      {

  /* ss006.13: addition */
         if ( SUnlock(&osCp.sTskTblLock) != ROK)
         {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS381, ERRZERO,
                         "Could not give the Semaphore");
            RETVALUE(RFAILED);
#endif
         }
         RETVALUE(ROK);
      }


      /* If this system task entry has no more TAPA tasks attached,
       *  we destroy it, otherwise we do nothing.
       */
      if (sTsk->numTTsks == 0)
      {
         sTsk->termPend = TRUE;
         destroySTsk = TRUE;
      }


      /* unlock */

  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS382, ERRZERO,
                      "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
      }

      /* If we're destroying the system task, ask the implementation
       *  to do it.
       */
      if (destroySTsk)
      {
         ret = ssdDestroySTsk(sTsk);
         if (ret != ROK)
         {
            /* oops? */

#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS383, (ErrVal) ret,
                        "Could not destroy system task");
#endif

            RETVALUE(RFAILED);
         }
      }
   }


   RETVALUE(ROK);
} /* SDeregInitTskTmr */

#endif /* SS_MULTIPLE_PROCS */


/*
*
*       Fun:   Register a TAPA task
*
*       Desc:  This function is used to register a TAPA task,
*              and its initialization and activation functions.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes:
*
*       File:  ss_task.c
*
*/
/* ss029.103: modification: procId added */ 
#ifndef SS_MULTIPLE_PROCS

#ifdef ANSI
PUBLIC S16 SRegTTsk
(
Ent ent,                        /* entity */
Inst inst,                      /* instance */
Ttype type,                     /* task type */
Prior prior,                    /* task priority */
PAIFS16 initTsk,                /* initialization function */
ActvTsk actvTsk                 /* activation function */
)
#else
PUBLIC S16 SRegTTsk(ent, inst, type, prior, initTsk, actvTsk)
Ent ent;                        /* entity */
Inst inst;                      /* instance */
Ttype type;                     /* task type */
Prior prior;                    /* task priority */
PAIFS16 initTsk;                /* initialization function */
ActvTsk actvTsk;                /* activation function */
#endif

#else /* SS_MULTIPLE_PROCS */

#ifdef ANSI
PUBLIC S16 SRegTTsk
(
ProcId proc,                    /* processor */
Ent ent,                        /* entity */
Inst inst,                      /* instance */
Ttype type,                     /* task type */
Prior prior,                    /* task priority */
PAIFS16 initTsk,                /* initialization function */
ActvTsk actvTsk                 /* activation function */
)
#else
PUBLIC S16 SRegTTsk(proc, ent, inst, type, prior, initTsk, actvTsk)
ProcId proc;                    /* processor */
Ent ent;                        /* entity */
Inst inst;                      /* instance */
Ttype type;                     /* task type */
Prior prior;                    /* task priority */
PAIFS16 initTsk;                /* initialization function */
ActvTsk actvTsk;                /* activation function */
#endif

#endif /* SS_MULTIPLE_PROCS */

{
   S16 ret = ROK;
   SsTTskEntry *tTsk;
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   U16 procIdIdx;
#endif

   TRC1(SRegTTsk);


#if (ERRCLASS & ERRCLS_INT_PAR)

   /* check entity and instance ranges */
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   if ((proc == SS_INV_PROCID) || (ent >= SS_MAX_ENT) ||  (inst >= SS_MAX_INST))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS384, ERRZERO, "Invalid proc/entity/instance");
      RETVALUE(RFAILED);
   }
#else /* SS_MULTIPLE_PROCS */
   if (ent >= SS_MAX_ENT ||  inst >= SS_MAX_INST)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS385, ERRZERO, "Invalid entity/instance");
      RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */

   /* check activation function */
   if (actvTsk == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS386, ERRZERO, "Null pointer");
      RETVALUE(RFAILED);
   }

   /* check task type */
   if (type != TTNORM  &&  type != TTPERM)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS387, ERRZERO, "Invalid task type");
      /* ss021.103 - Addition of return fail for invalid task type */
      RETVALUE(RFAILED);
   }

   /* check task priority */
   if (prior > PRIOR3)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS388, ERRZERO, "Invalid task priority");
      RETVALUE(RFAILED);
   }
#endif

/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   /* retrieve proc id index in the proc id table */
   procIdIdx = SGetProcIdIdx(proc); 

   /* Check whether the proc id exist in the proc id table */
   if (procIdIdx == SS_INV_PROCID_IDX)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
       SSLOGERROR(ERRCLS_INT_PAR, ESS389, ERRZERO,
                     "Could not find proc table index");
#endif

      RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */



   /* Acquire the counting semaphore for all other system
    *  tasks (this call is either running in one system task's
    *  context, or in SInit()'s context). Once we have all of
    *  them, SPstTsk() cannot run, so we can do things to the
    *  TAPA task table.
    */

   /* ss025.103 - Addition of lock around counting semaphore */
   /* lock system task table */
   ret = SLock(&osCp.sTskTblLock);
   if (ret != ROK)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS390, ERRZERO,
                     "Could not lock system task table");
      RETVALUE(RFAILED);
   }

   SS_ACQUIRE_ALL_SEMA(&osCp.tTskTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS391, ERRZERO,
                     "Could not lock TAPA task table");
#endif

      /* ss025.103 - Addition of unlock around counting semaphore */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS392, ERRZERO,
                      "Could not give the Semaphore");
         RETVALUE(RFAILED);
#endif
      }

      RETVALUE(RFAILED);
   }


#if (ERRCLASS & ERRCLS_DEBUG)
   /* check count of tasks */
   if (osCp.numTTsks == SS_MAX_TTSKS)
   {
      SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);
      SSLOGERROR(ERRCLS_DEBUG, ESS393, ERRZERO, "Too many tasks");

      /* ss025.103 - Addition of unlock around counting semaphore */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS394, ERRZERO,
                      "Could not give the Semaphore");
         RETVALUE(RFAILED);
#endif
      }

      RETVALUE(ROUTRES);
   }

   /* check if entity and instance already registered */
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   if (osCp.tTskIds[procIdIdx][ent][inst] != SS_TSKNC)
#else
   if (osCp.tTskIds[ent][inst] != SS_TSKNC)
#endif /* SS_MULTIPLE_PROCS */
   {
      SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);
      SSLOGERROR(ERRCLS_DEBUG, ESS395, ERRZERO,
                  "Entity and instance already registered");

      /* ss025.103 - Addition of unlock around counting semaphore */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS396, ERRZERO,
                      "Could not give the Semaphore");
         RETVALUE(RFAILED);
#endif
      }

      RETVALUE(RFAILED);
   }
#endif


   /*  We fill up the current available slot with all the
    *  information we've been given. Update table information,
    *  and the task is registered.
    */
   tTsk = &osCp.tTskTbl[osCp.nxtTTskEntry];
   tTsk->used     = TRUE;
/* ss029.103: addition: procId added */ 
#ifdef SS_MULTIPLE_PROCS
   tTsk->proc     = proc;
#endif /* SS_MULTIPLE_PROCS */
   tTsk->ent      = ent;
   tTsk->inst     = inst;
   tTsk->tskType  = type;
   tTsk->tskPrior = prior;
   tTsk->initTsk  = initTsk;
   tTsk->actvTsk  = actvTsk;
   tTsk->sTsk     = NULLP;

/* ss001.301: additions */
#ifdef SS_HISTOGRAM_SUPPORT 
   tTsk->hstReg   = 0;
#endif /* SS_HISTOGRAM_SUPPORT */

/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   osCp.tTskIds[procIdIdx][ent][inst] = osCp.nxtTTskEntry;
#else
   osCp.tTskIds[ent][inst] = osCp.nxtTTskEntry;
#endif /* SS_MULTIPLE_PROCS */
   osCp.nxtTTskEntry = tTsk->nxt;
   osCp.numTTsks++;


   /* Activate initialization function, if present. Like
    *  SRegInit(), we use hard-coded parameters. Note: we
    *  assume that the initialization function is not
    *  going to call SRegTTsk() or SPstTsk(). If it does,
    *  this thread will freeze up as we are holding the
    *  TAPA task table counting semaphore.
    */
   /* ss024.103 - Modification for memory calculator tool */
   if (initTsk != NULLP)
   {
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
      SsIdx idx;
      Void *xxCb = NULLP;
#endif /* SS_MULTIPLE_PROCS */

/* ss029.103: addition: multiple procIds related changes */ 
#ifndef SS_MULTIPLE_PROCS

#ifndef USE_MEMCAL
#ifndef SS_MULTICORE_SUPPORT
      (Void)(*initTsk)(ent, inst, DFLT_REGION, PWR_UP);
#endif
#else
      (Void)(*initTsk)(ent, inst, SS_STATIC_REGION, PWR_UP);
#endif /* USE_MEMCAL */

#else /* SS_MULTIPLE_PROCS */

#ifndef USE_MEMCAL
#ifndef SS_MULTICORE_SUPPORT
      (Void)(*initTsk)(proc, ent, inst, DFLT_REGION, PWR_UP, &xxCb);
#endif /* SS_MULTICORE_SUPPORT */
#else
      (Void)(*initTsk)(proc, ent, inst, SS_STATIC_REGION, PWR_UP, &xxCb);
#endif /* USE_MEMCAL */

      /*
       * store the control block. The control block may be NULL in some cases
       */
      idx = osCp.tTskIds[procIdIdx][ent][inst]; 

      osCp.tTskTbl[idx].xxCb = xxCb;

      /* ss032.103 do a debug print if xxCb is NULLP */
      if (xxCb == NULLP)
      {
         SSLOGERROR(ERRCLS_INT_PAR, ERRZERO, ERRZERO, "Null pointer");
      }
#endif /* SS_MULTIPLE_PROCS */
   }

   /* unlock the table */
   SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);

   /* ss025.103 - Addition of unlock around counting semaphore */
   if ( SUnlock(&osCp.sTskTblLock) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS397, ERRZERO,
                      "Could not give the Semaphore");
#endif
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* SRegTTsk */
 /* ss002.301 Additions */
/*
*
*       Fun:   Register a call back function with SSI
*
*       Desc:  This function is used to register a callback function
*              
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  sm_task.c
*
**/
#ifndef SS_MULTIPLE_PROCS
#ifdef ANSI
PUBLIC S16 SRegCbTsk
(
Ent ent,                        /* entity */
Inst inst,                      /* instance */
ActvTsk cbTsk                   /* Callback Function */
)
#else
PUBLIC S16 SRegCbTsk(ent, inst, cbTsk)
Ent ent;                        /* entity */
Inst inst;                      /* instance */
ActvTsk cbTsk;
#endif

#else /* SS_MULTIPLE_PROCS */

#ifdef ANSI
PUBLIC S16 SRegCbTsk 
(
ProcId proc,                    /* processor */
Ent ent,                        /* entity */
Inst inst,                       /* instance */
ActvTsk cbTsk 
)
#else
PUBLIC S16 SRegCbTsk(proc, ent, inst, cbTsk)
ProcId proc;                    /* processor */
Ent ent;                        /* entity */
Inst inst;                      /* instance */
ActvTsk cbTsk;
#endif
#endif /* SS_MULTIPLE_PROCS */
{
   SsTTskEntry *tTsk;
   SsIdx idx;
	S16   ret = ROK;
#ifdef SS_MULTIPLE_PROCS
   U16 procIdIdx;
#endif /* SS_MULTIPLE_PROCS */

   TRC1(SRegCbTsk);

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (ent >= SS_MAX_ENT ||  inst >= SS_MAX_INST)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESSXXX, ERRZERO, "SRegCbTsk() : Invalid entity/instance");
      RETVALUE(RFAILED);
   }

   if (cbTsk == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESSXXX, ERRZERO, " SRegCbTsk() : Null pointer");
      RETVALUE(RFAILED);
   }
#endif

#ifdef SS_MULTIPLE_PROCS
   /* retrieve proc id index in the proc id table */
   procIdIdx = SGetProcIdIdx(proc); 

   /* Check whether the proc id exist in the proc id table */
   if (procIdIdx == SS_INV_PROCID_IDX)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
       SSLOGERROR(ERRCLS_INT_PAR, ESSXXX, ERRZERO,
                     " SRegCbTsk() : Could not find proc table index");
#endif

      RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */

   SS_ACQUIRE_ALL_SEMA(&osCp.tTskTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESSXXX, ERRZERO,
                     "SRegCbTsk() : Could not lock TAPA task table");
#endif
      RETVALUE(RFAILED);
   }

#ifdef SS_MULTIPLE_PROCS
   idx = osCp.tTskIds[procIdIdx][ent][inst];
#else /* SS_MULTIPLE_PROCS */
   idx = osCp.tTskIds[ent][inst];
#endif /* SS_MULTIPLE_PROCS */

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (idx == SS_TSKNC)
   {
      SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);
      SSLOGERROR(ERRCLS_INT_PAR, ESSXXX, ERRZERO, "SRegCbTsk() : Unknown task");
      RETVALUE(RFAILED);
   }
#endif
   tTsk = &osCp.tTskTbl[idx];
   tTsk->cbTsk  = cbTsk;

   /* unlock the table */
   SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);
   RETVALUE(ROK);
}


/*
*
*       Fun:   Deregister TAPA task
*
*       Desc:  This function is used to deregister a TAPA task.
*              All information about the task is removed from the
*              task table.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_task.c
*
*/
/* ss029.103: addition: procId added */ 
#ifndef SS_MULTIPLE_PROCS

#ifdef ANSI
PUBLIC S16 SDeregTTsk
(
Ent ent,                        /* entity */
Inst inst                       /* instance */
)
#else
PUBLIC S16 SDeregTTsk(ent, inst)
Ent ent;                        /* entity */
Inst inst;                      /* instance */
#endif

#else /* SS_MULTIPLE_PROCS */

#ifdef ANSI
PUBLIC S16 SDeregTTsk
(
ProcId proc,                    /* processor */
Ent ent,                        /* entity */
Inst inst                       /* instance */
)
#else
PUBLIC S16 SDeregTTsk(proc, ent, inst)
ProcId proc;                    /* processor */
Ent ent;                        /* entity */
Inst inst;                      /* instance */
#endif
#endif /* SS_MULTIPLE_PROCS */
{
   S16          ret;
   /* ss029.103: modification: The subscript should be consistent type */
   SsIdx        idx;
   SsTTskEntry *tTsk;
   SsTmrEntry  *tmr;
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   U16 procIdIdx;
#endif /* SS_MULTIPLE_PROCS */
 /* ss002.301 Additions */
   Buffer *mBuf;
   SsMsgInfo *mInfo;

   TRC1(SDeregTTsk);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check entity and instance ranges */
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   if ((proc == SS_INV_PROCID) || (ent >= SS_MAX_ENT) ||  (inst >= SS_MAX_INST))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS398, ERRZERO, "Invalid processor/entity/instance");
      RETVALUE(RFAILED);
   }
#else /* SS_MULTIPLE_PROCS */
   if (ent >= SS_MAX_ENT ||  inst >= SS_MAX_INST)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS399, ERRZERO, "Invalid entity/instance");
      RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */

#endif

/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   /* Find the proc table index */
   procIdIdx = SGetProcIdIdx(proc);

   if (procIdIdx == SS_INV_PROCID)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS400, ERRZERO,
                             "Could not find proc id index");
#endif
      RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */

   /* We deregister all timers for this TAPA task, since it's going
    *  away now. Lock the timer table and iterate through it, removing
    *  all timers owned by this task.
    */
   if (SLock(&osCp.tmrTblLock) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS401, ERRZERO,
                             "Could not lock timer table");
#endif
      RETVALUE(RFAILED);
   }

   for (idx = 0;  idx < SS_MAX_TMRS;  idx++)
   {
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
      if ((osCp.tmrTbl[idx].ownerProc == proc) &&  
          (osCp.tmrTbl[idx].ownerEnt == ent) &&  
          (osCp.tmrTbl[idx].ownerInst == inst))
#else /* SS_MULTIPLE_PROCS */
      if ((osCp.tmrTbl[idx].ownerEnt == ent) &&  
          (osCp.tmrTbl[idx].ownerInst == inst))
#endif /* SS_MULTIPLE_PROCS */
      {
         /* shut down this timer */
         tmr = &osCp.tmrTbl[idx];
         if (ssdDeregTmr(tmr) == ROK)
         {
            tmr->used      = FALSE;
            tmr->tmrId     = 0;
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
            tmr->ownerProc  = PROCNC;
            /*
             *  ss015.301 - Modifed in initialization as timer activation 
             *  functions enclosed in a union. Also initialized the mtFlag
             *  to FALSE 
             */
#endif /* SS_MULTIPLE_PROCS */
            tmr->ownerEnt  = ENTNC;
            tmr->ownerInst = INSTNC;
            tmr->interval  = 0;
            tmr->ssTmrActvFn.actvFnc.tmrActvFn = NULLP;
#ifndef SS_MULTIPLE_PROCS
#ifdef SS_MT_TMR 
            tmr->ssTmrActvFn.mtFlag = FALSE; 
            tmr->ssTmrActvFn.actvFnc.tmrActvFnMt = NULLP;
#endif
#endif
            tmr->nxt = osCp.nxtTmrEntry;
            osCp.nxtTmrEntry = (SsIdx)idx;
            osCp.numTmrs--;
         }
         else
         {

  /* ss006.13: addition */
          if ( SUnlock(&osCp.tmrTblLock) != ROK)
          {
#if (ERRCLASS & ERRCLS_DEBUG)
             SSLOGERROR(ERRCLS_DEBUG, ESS402, ERRZERO,
                      "Could not give the Semaphore");
             RETVALUE(RFAILED);
#endif
          }

#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS403, ERRZERO,
                        "Could not deregister task's timer(s)");
#endif
            RETVALUE(RFAILED);

         }
      }
   }


  /* ss006.13: addition */
          if ( SUnlock(&osCp.tmrTblLock) != ROK)
          {
#if (ERRCLASS & ERRCLS_DEBUG)
             SSLOGERROR(ERRCLS_DEBUG, ESS404, ERRZERO,
                      "Could not give the Semaphore");
             RETVALUE(RFAILED);
#endif
          }
 /* ss002.301 Additions */
   /* Acquire the counting semaphore for all TAPA tasks. Once
    *  we have all of them, both SPstTsk() and SRegTTsk() cannot
    *  run, so we can do things to the TAPA task table.
    */
   SS_ACQUIRE_ALL_SEMA(&osCp.tTskTblSem, ret);
   if (ret != ROK)
   {
 /* ss002.301 Additions */

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS411, ERRZERO,
                     "Could not lock TAPA task table");
#endif

      RETVALUE(RFAILED);
   }


   /* get out the TAPA task entry */
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   idx = osCp.tTskIds[procIdIdx][ent][inst];
#else /* SS_MULTIPLE_PROCS */
   idx = osCp.tTskIds[ent][inst];
#endif /* SS_MULTIPLE_PROCS */


   /* make sure this TAPA task exists */
   if (idx == SS_TSKNC)
   {
      SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);

      SSLOGERROR(ERRCLS_INT_PAR, ESS412, ERRZERO, "Unknown task");
 /* ss002.301 Additions */
      RETVALUE(RFAILED);
   }

   tTsk = &osCp.tTskTbl[idx];

   /* unlock the TAPA task table */
   SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);

   /*Check whether the thread calling this funtion is the same as the system task to which the 
     TAPA task detremined by passed entity and instance is attached*/
   /* 100178 */
   
/*ss014.301 SSI-4GMX specific changes*/   
#ifndef SS_4GMX_LCORE
   if((tTsk->sTsk == NULLP) || (SS_CHECK_CUR_STSK(tTsk->sTsk)))
   { 
#ifdef SS_MULTIPLE_PROCS
      ssdProcTTskTerm(procIdIdx, tTsk, idx);
#else
      ssdProcTTskTerm(tTsk, idx);
#endif

   }
   else
   {
   	/*Allocate memory*/
   	if (SGetMsg(SS_DFLT_REGION, SS_DFLT_POOL, &mBuf) != ROK)
   	{

#if (ERRCLASS & ERRCLASS_DEBUG)
      	SSLOGERROR(ERRCLS_DEBUG, ESS415, ERRZERO, "Could not get a message");
#endif

      	RETVALUE(RFAILED);
   	}

   	/* Update message*/
   	mInfo = (SsMsgInfo *)mBuf->b_rptr;
   	mInfo->eventInfo.event = SS_EVNT_TTSK_TERM;

   	mInfo->pst.dstEnt = ent;
   	mInfo->pst.dstInst = inst;

   	/* we dont care who is calling SDeregTTsk()
      	so we dont fill srcEnt and dstInst in mInfo->pst */
 
	/* mt028.201: modification: multiple procs support related changes */
	/* source proc id is not needed so we dont fill it */
#ifndef SS_MULTIPLE_PROCS
   	mInfo->pst.dstProcId = SFndProcId();
#else /* SS_MULTIPLE_PROCS */
    	mInfo->pst.dstProcId = proc;
#endif /* SS_MULTIPLE_PROCS */
 /* ss002.301 Additions */
   	mInfo->pst.selector = SEL_LC_NEW;
   	mInfo->pst.region = DFLT_REGION;
   	mInfo->pst.pool = DFLT_POOL;
   	mInfo->pst.prior = PRIOR0;
   	mInfo->pst.route = RTESPEC;
   	mInfo->pst.event = 0;
   /* write the timer message to the queue of the destination task */
   	if (ssDmndQPutLast(&tTsk->sTsk->dQ, mBuf,
               	(tTsk->tskPrior * SS_MAX_MSG_PRI) + PRIOR0) != ROK)
   	{
      	SS_RELEASE_SEMA(&osCp.tTskTblSem);
      	SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_DEBUG)
      	SSLOGERROR(ERRCLS_INT_PAR, ESS416, ERRZERO, "Could not write to demand queue");
#endif
      	RETVALUE(RFAILED);
   	}
   }
#endif

   RETVALUE(ROK);
} /* SDeregTTsk */


/*
*
*       Fun:   Create system task
*
*       Desc:  This function is used to create a system task. An
*              entry is located in the system task table and the
*              implementation-specific function is called.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes:
*
*       File:  ss_task.c
*
*/
#ifdef ANSI
PUBLIC S16 SCreateSTsk
(
SSTskPrior tskPrior,            /* task priority */
SSTskId *tskId                  /* filled in with system task ID */
)
#else
PUBLIC S16 SCreateSTsk(tskPrior, tskId)
SSTskPrior tskPrior;            /* task priority */
SSTskId *tskId;                 /* filled in with system task ID */
#endif
{
   S16 ret;
   SsSTskEntry *sTsk;


   TRC1(SCreateSTsk);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check task ID pointer */
   if (tskId == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS417, ERRZERO, "Null pointer");
      RETVALUE(RFAILED);
   }

   /* check system task priority */
   if (tskPrior > SS_LOWEST_STSK_PRIOR)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS418, ERRZERO,
                     "Invalid system task priority");
      RETVALUE(RFAILED);
   }
#endif


   /* lock the system task table */ 
   ret = SLock(&osCp.sTskTblLock);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS419, (ErrVal) ret,
                     "Could not lock system task table");
#endif

      RETVALUE(RFAILED);
   }


#ifdef SS_SINGLE_THREADED
   /* When singlethreaded, we only need to create one... */
/* ss001.301: additions */
#ifndef SS_WATCHDOG 
#ifndef SS_MULTICORE_SUPPORT
   if (osCp.numSTsks == 1)
#else
   if (osCp.numSTsks == 2)
#endif /* SS_MULTICORE_SUPPORT */
#else
#ifndef SS_MULTICORE_SUPPORT
   if (osCp.numSTsks == 3)
#else      
   if (osCp.numSTsks == 4)
#endif /* SS_MULTICORE_SUPPORT */
#endif /* SS_WATCHDOG */
   {
/* ss001.301: additions */
#ifndef SS_WATCHDOG 
#ifndef SS_MULTICORE_SUPPORT
      *tskId = 0;
      osCp.sTskTbl[0].termPend = FALSE;
#else
      *tskId = 1;
      osCp.sTskTbl[1].termPend = FALSE;
#endif /* SS_MULTICORE_SUPPORT */
#else
#ifndef SS_MULTICORE_SUPPORT
      *tskId = 2;
      osCp.sTskTbl[2].termPend = FALSE;
#else 
      *tskId = 3;
      osCp.sTskTbl[3].termPend = FALSE;
#endif /* SS_MULTICORE_SUPPORT */
#endif /* SS_WATCHDOG */

  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
           SSLOGERROR(ERRCLS_DEBUG, ESS420, ERRZERO,
                       "Could not give the Semaphore");
           RETVALUE(RFAILED);
#endif
      }
      RETVALUE(ROK);
   }
#endif /* SS_SINGLE_THREADED */


   /* check count of system tasks */
   if (osCp.numSTsks == SS_MAX_STSKS)
   {

  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
           SSLOGERROR(ERRCLS_DEBUG, ESS421, ERRZERO,
                       "Could not give the Semaphore");
           RETVALUE(RFAILED);
#endif
      }

#if (ERRCLASS & ERRCLS_ADD_RES)
      SSLOGERROR(ERRCLS_ADD_RES, ESS422, ERRZERO, "Too many system tasks");
#endif

      RETVALUE(ROUTRES);
   }


   /* initialize the system task entry with the information we have */
   sTsk = &osCp.sTskTbl[osCp.nxtSTskEntry];

   /* store the system task priority */
   sTsk->tskPrior = tskPrior;

/*ss014.301 SSI-4GMX specific changes*/   
#ifndef SS_4GMX_LCORE
   /* initialize the demand queue */
   if (ssInitDmndQ(&sTsk->dQ) != ROK)
   {

  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
           SSLOGERROR(ERRCLS_DEBUG, ESS423, ERRZERO,
                       "Could not give the Semaphore");
           RETVALUE(RFAILED);
#endif
      }

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS424, (ErrVal) ret,
                  "Could not initialize demand queue");
#endif

      RETVALUE(RFAILED);
   }

   /* initialize the system task entry lock */
   if (SInitLock(&sTsk->lock, SS_STSKENTRY_LOCK) != ROK)
   {
      ssDestroyDmndQ(&sTsk->dQ);

  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
           SSLOGERROR(ERRCLS_DEBUG, ESS425, ERRZERO,
                       "Could not give the Semaphore");
           RETVALUE(RFAILED);
#endif
      }

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS426, (ErrVal) ret,
                  "Could not initialize system task entry lock");
#endif

      RETVALUE(RFAILED);
   }
#endif

   /* we ask the implementation to start this system task */
   ret = ssdCreateSTsk(sTsk);
   if (ret != ROK)
   {
      /* failed, clean up */
      SDestroyLock(&sTsk->lock);
/*ss014.301 SSI-4GMX specific changes*/   
#ifndef SS_4GMX_LCORE
      ssDestroyDmndQ(&sTsk->dQ);
#endif
      sTsk->tskPrior = 0;


  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
           SSLOGERROR(ERRCLS_DEBUG, ESS427, ERRZERO,
                       "Could not give the Semaphore");
           RETVALUE(RFAILED);
#endif
      }

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS428, (ErrVal) ret,
                  "Could not create system task");
#endif

      RETVALUE(RFAILED);
   }

   /* success, update the table */
   *tskId = osCp.nxtSTskEntry;
   sTsk->tskId       = osCp.nxtSTskEntry;
   sTsk->used        = TRUE;
   sTsk->termPend    = FALSE;
   osCp.nxtSTskEntry = sTsk->nxt;
   osCp.numSTsks++;

   /* unlock the system task table */

  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
           SSLOGERROR(ERRCLS_DEBUG, ESS429, ERRZERO,
                       "Could not give the Semaphore");
           RETVALUE(RFAILED);
#endif
      }

   RETVALUE(ROK);

} /* SCreateSTsk */

/* ss001.301: additions */
#ifdef SS_LOGGER_SUPPORT 
/*
*
*       Fun:   Register logger configuration 
*
*       Desc:  This function is used to configure the config information
*              of the logger.The log file name, path and the size limits
*              of the log file are updated in the SSI control block. 
*
*
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes:
*
*       File:  ss_task.c
*
*/
#ifdef ANSI
PUBLIC S16 SRegLogCfg
(
U8 mode,
S8 *path,
U32 size,
S8 *IPA,
U16 port
)
#else
PUBLIC S16 SRegLogCfg(mode, path, size, IPA, port)
U8 mode;
S8 *path;
U32 size;
S8 *IPA;
U16 port
#endif
{

#ifdef WIN32
   WSADATA wsaData;
	U32 iRes;
#endif

   /*ss013.301: Fixed Warnings for 32/64 bit compilation*/ 
   struct sockaddr_in localAddr={0};
   struct sockaddr_in remoteAddr ={0};

   TRC1(SRegLogCfg);

#if (ERRCLASS & ERRCLS_INT_PAR)
#endif

   /* Initialize the lock, return on failure */
   if( SInitLock(&(osCp.logger.bufLock),SS_LOCK_MUTEX) != ROK)
	{
      RETVALUE(RFAILED);
   } /* if */

   SLock(&osCp.logger.bufLock);

	/* Initialize the logger configuration flag */
	osCp.logger.configured = FALSE;

   if( osCp.logger.started == TRUE)
   {
      (Void)SUnlock(&(osCp.logger.bufLock));
      RETVALUE(RFAILED);
   }

	/* set the mode of the logging */
	switch (mode)
	{
	   case SS_LOG_TO_FILE: 
		   osCp.logger.opt |= 0x01; 
		   break;
	   case SS_LOG_TO_SOCKET: 
		   osCp.logger.opt |= 0x02; 
		   break;
	   case SS_LOG_ALL: 
		default:  
		   osCp.logger.opt |= 0x03; break;
	}
    
   /*Open log file*/
	if (osCp.logger.opt & 0x01)
	{
      osCp.logger.filep = fopen(path, "wb");
      if(osCp.logger.filep == NULLP)
      {
         SDisplay(0,"Error Opening Log File \n");
         (Void)SUnlock(&(osCp.logger.bufLock));
         RETVALUE(RFAILED);
      }
      strcpy(osCp.logger.filePath,path);
	}

   /*Open socket */
	if (osCp.logger.opt & 0x02)
	{
#ifdef WIN32
			if ((iRes = WSAStartup(MAKEWORD(2,2), &wsaData)) != NO_ERROR)
			{
			   SDisplay(0, "Error at WSAStartup!\n");
            (Void)SUnlock(&(osCp.logger.bufLock));
				RETVALUE(RFAILED);
			}
#endif
      osCp.logger.socketdes = socket(AF_INET, SOCK_DGRAM, 0);
      if(osCp.logger.socketdes == -1)
      {
         SDisplay(0,"Error Opening Log Socket  \n");
#ifdef WIN32
			WSACleanup();
#endif
         (Void)SUnlock(&(osCp.logger.bufLock));
         RETVALUE(RFAILED);
      }
		/* bind to local address */
		localAddr.sin_family = AF_INET;
		localAddr.sin_port = port;
		localAddr.sin_addr.s_addr = INADDR_ANY;
		if (bind(osCp.logger.socketdes, (struct sockaddr*)&localAddr, sizeof(struct sockaddr)) < 0)
		{
         SDisplay(0,"Error binding to local port \n");
#ifdef WIN32
			closesocket(osCp.logger.socketdes);
			WSACleanup();
#else
			close(osCp.logger.socketdes);
#endif
         (Void)SUnlock(&(osCp.logger.bufLock));
         RETVALUE(RFAILED);
		}
		/* remote address */
		remoteAddr.sin_family = AF_INET;
		remoteAddr.sin_port = htons(port);
		if (!IPA)
		{
         SDisplay(0,"Invalid remote IP Address \n");
#ifdef WIN32
			closesocket(osCp.logger.socketdes);
			WSACleanup();
#else
			close(osCp.logger.socketdes);
#endif
         (Void)SUnlock(&(osCp.logger.bufLock));
         RETVALUE(RFAILED);
		}
		remoteAddr.sin_addr.s_addr = inet_addr(IPA);
		osCp.logger.remoteAddr = remoteAddr;

	}

   cmMemset((U8*)osCp.logger.buffer, '\0', sizeof(osCp.logger.buffer));
   
   osCp.logger.maxBufSiz = SS_MAX_LOGBUF_SIZE;
   osCp.logger.curBufSiz = 0;

   osCp.logger.maxNumFlush = size/osCp.logger.maxBufSiz;
   osCp.logger.curNumFlush = 0;


   osCp.logger.started = FALSE;
	osCp.logger.configured = TRUE;

   (Void)SUnlock(&(osCp.logger.bufLock));

   RETVALUE(ROK);
} /* SRegLogCfg */

/*
*
*       Fun:   SFlushBufToLog
*
*       Desc:  This function is used flush the buffer to file/socket.
*
*       Ret:   ROK
*
*       Notes:
*
*       File:  ss_task.c
*
--*/
#ifdef ANSI
PUBLIC S16 SFlushBufToLog 
(
S8 *logBuf
)
#else
PUBLIC S16 SFlushBufToLog(logBuf)
S8 *logBuf
#endif
{
   S8 *buffer;
   PRIVATE U16 logFileCnt = 0;
   S8 newFileName[SS_MAX_PATH];
#ifdef WIN32
   size_t writeNum;
#else
   ssize_t writeNum;
#endif
   FILE* oldFileP;
   /*ss013.301 :Fix for TRACE5 feature crash due to missing TRC MACRO*/
   TRC1(SFlushBufToLog)

   buffer = logBuf;

	if (osCp.logger.opt & 0x01)
	{
      writeNum = fwrite(buffer, sizeof(U8), cmStrlen((U8 *)buffer), 
		                  osCp.logger.filep);
	}
	if (osCp.logger.opt & 0x02)
	{
      writeNum = sendto(osCp.logger.socketdes, buffer, cmStrlen((U8 *)buffer), 0, (struct sockaddr*)&osCp.logger.remoteAddr, sizeof(osCp.logger.remoteAddr));
      /*ss013.301 : Returned after sending to socket*/
      RETVALUE(ROK);
	}
   osCp.logger.curNumFlush++;
   if(osCp.logger.curNumFlush == osCp.logger.maxNumFlush)
   {
      cmMemset((U8 *)newFileName,'\0',sizeof(newFileName));
      /*Store the current File*/
      oldFileP = osCp.logger.filep;
      /*Open a new file and use it as a new log file*/
      osCp.logger.curNumFlush = 0;
      logFileCnt++;
      sprintf(newFileName, "%s%d", osCp.logger.filePath, logFileCnt);
      osCp.logger.filep = fopen(newFileName, "wb");
      if(osCp.logger.filep == NULLP)
      {
          /*MTLOGERROR(ERRCLS_DEBUG, EMTXXX, ERRZERO, "Error Opening Log File. \n");*/
      }

      fclose(oldFileP);
   }
   /*SPutSBuf(DFLT_REGION,DFLT_POOL,
            (Data *)buffer, (Size)(osCp.logger.maxBufSiz * sizeof(S8)));*/
 
   RETVALUE(ROK);
} /* SFlushBufToLog */

/*
*
*       Fun:   SCleanUp
*
*       Desc:  This function is used to clean up the logger info.
*
*       Ret:   task id
*
*       Notes:
*
*       File:  ss_task.c
*
--*/
#ifdef ANSI
PUBLIC S16 SCleanUp
(
Void
)
#else
PUBLIC S16 SCleanUp()
#endif
{

   TRC1(SCleanUp);
   /*Flush the remaining data in the log file*/
   SLock(&osCp.logger.bufLock);
   if(osCp.logger.started == FALSE)
   {
      (Void)SUnlock(&(osCp.logger.bufLock));
      RETVALUE(ROK);
   }
   if(osCp.logger.curBufSiz)
   {
      SFlushBufToLog(osCp.logger.buffer);
      osCp.logger.curBufSiz = 0;

   }
	if (osCp.logger.opt & 0x01)
	{
      fclose(osCp.logger.filep);
	}
	if (osCp.logger.opt & 0x02)
	{
#ifdef WIN32
      closesocket(osCp.logger.socketdes);
#else
      close(osCp.logger.socketdes);
#endif
	}
   osCp.logger.started = FALSE;

   (Void)SUnlock(&(osCp.logger.bufLock));
   
   RETVALUE(ROK);

} /* end of SCleanUp */

/*
*
*       Fun:   Unregister the logger.
*
*       Desc:  This function is used to deregister a logger task. 
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes:
*
*       File:  ss_task.c
*
*/
#ifdef ANSI
PUBLIC S16 SDeregLogCfg
(
)
#else
PUBLIC S16 SDeregLogCfg()
#endif
{


   TRC1(SDeregLogCfg);
 
   SCleanUp();   

   RETVALUE(ROK);

} /* SDeregLogCfg */

/*
*
*       Fun:   SStartLogger
*
*       Desc:  To start logger.
*
*       Ret:   Void
*
*       Notes:
*
*       File:  ss_task.c
*
*/
#ifdef ANSI
PUBLIC Void SStartLogger
(
void
)
#else
PUBLIC Void SStartLogger()
#endif
{
	if (osCp.logger.configured == TRUE)
	{
      osCp.logger.started = TRUE;
	}
}


/*
*
*       Fun:   SStopLogger
*
*       Desc:  To stop logging to file/socket.
*
*       Ret:   Void
*
*       Notes:
*
*       File:  ss_task.c
*
*/
#ifdef ANSI
PUBLIC Void SStopLogger
(
void
)
#else
PUBLIC Void SStopLogger()
#endif
{
   osCp.logger.started = FALSE;
}
#endif /* SS_LOGGER_SUPPORT */

/** for multi-core support **/
/*ss013.301 : changes related to SS_AFFINITY_SUPPORT*/
#if defined(SS_MULTICORE_SUPPORT) || defined(SS_AFFINITY_SUPPORT)

/*
*
*       Fun:   Register the CPU information
*
*       Desc:  This function is used to register the number of cores
*              present and the number of threads which can be run on
*              each core.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_task.c
*
*/
#ifdef ANSI
PUBLIC S16 SRegCpuInfo 
(
SCpuInfo *cpuInfo    /* Information about the cores/threads per core */
)
#else
PUBLIC S16 SRegCpuInfo (cpuInfo)
SCpuInfo *cpuInfo;  /* Information about the cores/threads per core */
#endif
{
   U32 coreCount = 0;

   /*ss013.301 :Fix for TRACE5 feature crash due to missing TRC MACRO*/
   TRC1(SRegCpuInfo)
   /* check the number of cores */
   if ( cpuInfo->numCores > SS_MAX_CORES || 
        cpuInfo->threadsPerCore > SS_MAX_THREADS_PER_CORE || 
        cpuInfo->numCores < 1 || cpuInfo->threadsPerCore < 1 )
   {
       SSLOGERROR(ERRCLS_INT_PAR, ESS430, ERRZERO, "Invalid number of cores\n");
       RETVALUE(RFAILED);
   }

   /* lock mCInfo */
   SLock(&osCp.mCILock);
   osCp.mCInfo.cpuInfo.numCores = cpuInfo->numCores;
   osCp.mCInfo.cpuInfo.threadsPerCore = cpuInfo->threadsPerCore;
   /* if the cpu register is supplied then use it */
   for (; coreCount < cpuInfo->numCores; coreCount++)
   {
      U32 thrCnt = 0;
      for (;thrCnt < SS_MAX_THREADS_PER_CORE;thrCnt++)
      {
         osCp.mCInfo.coreInfo[coreCount].tskPerCoreLst[thrCnt] = -1;
      } /* for */
      osCp.mCInfo.coreInfo[coreCount].exclusive = FALSE;
      osCp.mCInfo.coreInfo[coreCount].thrs = osCp.mCInfo.cpuInfo.threadRegister[coreCount] 
      = cpuInfo->threadRegister[coreCount];
   }
   /* unlock mCInfo */
   SUnlock(&osCp.mCILock);

   RETVALUE(ROK);

} /* SRegCpuInfo */



/*
*
*       Fun:   Get the current core/cpu affinity for a thread/lwp
*
*       Desc:  This function is used to get the current processor/core 
*              affinity for a a system task (thread/lwp). It sets the 
*              affinity based on the mode supplied by the caller. 
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_task.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetAffinity
(
SSTskId *tskId,                  /* filled in with system task ID */
U32 *coreId                      /* the core/processor id to which the affinity is set */
)
#else
PUBLIC S16 SGetAffinity(tskId, coreId)
SSTskId *tskId;                 /* filled in with system task ID */
U32 *coreId;                    /* the core/processor id to which the affinity is set */
#endif
{
   S16 ret;

    /*ss013.301 :Fix for TRACE5 feature crash due to missing TRC MACRO*/
    TRC1(SGetAffinity)
    /* implementation specific */
    ret = ssdGetAffinity(tskId, coreId);

    if (ret != ROK)
    {
       SSLOGERROR(ERRCLS_INT_PAR, ESS431, ERRZERO, "Failed to get affinity\n");
       RETVALUE(RFAILED);
    } /* end if */

   RETVALUE(ROK);
} /* SGetAffinity */


/*
*
*       Fun:   Set the core/cpu affinity for a thread/lwp
*
*       Desc:  This function is used to set processor/core affinity for a 
*              a system task (thread/lwp). It sets the affinity based on the
*              mode supplied by the caller. 
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_task.c
*
*/
#ifdef ANSI
PUBLIC S16 SSetAffinity
(
SSTskId *tskId,                  /* filled in with system task ID */
SsAffinityMode mode,             /* the mode according to which the affinty is set */
U32 coreId,                      /* the core/processor id to which the affinity has to be set */
SSTskId *tskAssociatedTskId      /* filled in with system task ID of the associated layer */
)
#else
PUBLIC S16 SSetAffinity(tskId, mode, coreId, tskAssociatedTskId)
SSTskId *tskId;                 /* filled in with system task ID */
SsAffinityMode mode;            /* the mode according to which the affinty is set */
U32 coreId;                     /* the core/processor id to which the affinity has to be set */
SSTskId *tskAssociatedTskId;    /* filled in with system task ID of the associated layer */
#endif
{
   S16 ret;
  
   /*ss013.301 :Fix for TRACE5 feature crash due to missing TRC MACRO*/
   TRC1(SSetAffinity)
   /* validate the mode */
   if (mode < SS_AFFINITY_MODE_DEFAULT || 
       mode > SS_AFFINITY_MODE_EXCL)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS432, ERRZERO, "Invalid mode for setting core affinity\n");
      RETVALUE(RFAILED);
   } /* end if */

   /* check the value of core id */
   if (SS_AFFINITY_MODE_SPECIFIC == mode && 
       (coreId > osCp.mCInfo.cpuInfo.numCores || coreId < 0))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS433, ERRZERO, "Invalid core id\n");
      RETVALUE(RFAILED);
   } /* end if */

   /* set affinity according to the mode supplied */
   switch (mode)
   {
       case SS_AFFINITY_MODE_DEFAULT:
       {
           U32 coreCounter = 0, coreIndex = 0;
           S8 repeatFlag = 1;
           SEARCH_FOR_CORE:
              /*ss013.301: Fixed Warnings for 32/64 bit compilation*/ 
              for (coreIndex = osCp.mCInfo.currentCore;  
                   coreCounter < osCp.mCInfo.cpuInfo.numCores; 
                   coreCounter++ )
                  {
                     /* again start from core 0 */ 
                     ++coreIndex;
                     coreIndex = (coreIndex)%osCp.mCInfo.cpuInfo.numCores;
                     if (!osCp.mCInfo.coreInfo[coreIndex].exclusive 
                         && osCp.mCInfo.cpuInfo.threadRegister[coreIndex])
                     {
                         if (osCp.mCInfo.coreInfo[coreIndex].thrs || !repeatFlag)  
                         {
                             /* call the implementation specific affinity function */
                             ret = ssdSetAffinity(tskId, coreIndex);
     
                             if (ret != ROK)
                             {
                                 SSLOGERROR(ERRCLS_INT_PAR, ESS434, ERRZERO, \
                                            "Failed to set core affinity\n");
                                 RETVALUE(RFAILED);
                             } /* end if */
  
                             /* lock mCInfo */
                             SLock(&osCp.mCILock);

                             /* move the current core index */
                             osCp.mCInfo.currentCore = (coreIndex+1)%osCp.mCInfo.cpuInfo.numCores;
  
                             /* save the tskId in tskList */
                              osCp.mCInfo.coreInfo[coreIndex].tskPerCoreLst[
                              osCp.mCInfo.cpuInfo.threadRegister[coreIndex] - 
                              osCp.mCInfo.coreInfo[coreIndex].thrs] = *tskId;

                             /* decrement the available thread count in the thread register */
                              osCp.mCInfo.coreInfo[coreIndex].thrs--;

                             /* unlock mCInfo */
                              SUnlock(&osCp.mCILock);
  
                              break;
                          } /* end if there are threads available in the core */    
                      } /* end if the core is not exclusive flagged and 
                           the core has threads for SSI use */
                  } /* end for */
                 if (coreCounter == osCp.mCInfo.cpuInfo.numCores && repeatFlag)
                 {
                     repeatFlag = 0;
                     SSLOGERROR(ERRCLS_INT_PAR, ESS435, ERRZERO, "Overloading of threads per core!!\n");
                     goto SEARCH_FOR_CORE; 
                 } /* end if no thrs on cores available and overallocation is needed */
              break;
          } /* end case SS_AFFINITY_MODE_DEFAULT */
          case SS_AFFINITY_MODE_SPECIFIC:
          {
              /* check if the core is used exclusively for any task */
              if (osCp.mCInfo.coreInfo[coreId].exclusive)
              {
                  SSLOGERROR(ERRCLS_INT_PAR, ESS436, ERRZERO,\
                             "Can not set core affinity, core is exclusively used for other task\n");
                  RETVALUE(RFAILED);
              } /* end if */
              /* call the implementation specific affinity function with the core id supplied by caller */
              ret = ssdSetAffinity(tskId, coreId);

              if (ret != ROK)
              {
                  SSLOGERROR(ERRCLS_INT_PAR, ESS437, ERRZERO, "Failed to set core affinity\n");
                  RETVALUE(RFAILED);
              } /* end if */

              /* lock mCInfo */
              SLock(&osCp.mCILock);

              /* move the current core index */
               osCp.mCInfo.currentCore = (coreId+1)%osCp.mCInfo.cpuInfo.numCores;

              /* save the tskId in tskList */
              osCp.mCInfo.coreInfo[coreId].tskPerCoreLst[
              osCp.mCInfo.cpuInfo.threadRegister[coreId] - 
              osCp.mCInfo.coreInfo[coreId].thrs] = *tskId;
 
              /* decrement the available thread count in the thread register */
              osCp.mCInfo.coreInfo[coreId].thrs--;
 
              /* unlock mCInfo */
              SUnlock(&osCp.mCILock);

              if (osCp.mCInfo.coreInfo[coreId].thrs < 0)
              {
                  SSLOGERROR(ERRCLS_INT_PAR, ESS438, ERRZERO, "Overloading of threads per core!!\n");
              } /* end else */

             break;
          } /* end case SS_AFFINITY_MODE_SPECIFIC */
          case SS_AFFINITY_MODE_ASSOC:
          {
              /* search for the associated tsk id in osCp */
              U32 coreIndex = 0, threadIndex = 0;
              Bool tskNotFound = TRUE;
              for (;tskNotFound && coreIndex < SS_MAX_CORES; coreIndex++)
              {
                  for (threadIndex = 0; threadIndex < SS_MAX_THREADS_PER_CORE; threadIndex++)
                  {
                      if (osCp.mCInfo.coreInfo[coreIndex].tskPerCoreLst[threadIndex] == *tskAssociatedTskId)
                      {
                          if (!osCp.mCInfo.coreInfo[coreIndex].exclusive)
                          {
                              /* set the affinity for the given task on to the core coreIndex */
                              ret = ssdSetAffinity(tskId, coreIndex);
                              if (ret != ROK)
                              {
                                  SSLOGERROR(ERRCLS_INT_PAR, ESS439, ERRZERO, "Failed to set core affinity\n");
                                  RETVALUE(RFAILED);
                              } /* end if */
    
                              /* lock mCInfo */
                              SLock(&osCp.mCILock);

                             /* move the current core index */
                              osCp.mCInfo.currentCore = (coreIndex+1)%osCp.mCInfo.cpuInfo.numCores;
    
                             /* save the tskId in tskList */
                             osCp.mCInfo.coreInfo[coreIndex].tskPerCoreLst[               
                             osCp.mCInfo.cpuInfo.threadRegister[coreIndex] - 
                             osCp.mCInfo.coreInfo[coreIndex].thrs] = *tskId;
 
                            /* decrement the available thread count in the thread register */
                             osCp.mCInfo.coreInfo[coreIndex].thrs--;
 
                            /* unlock mCInfo */
                            SUnlock(&osCp.mCILock);

                            if (osCp.mCInfo.coreInfo[coreIndex].thrs < 0) 
                            {
                                SSLOGERROR(ERRCLS_INT_PAR, ESS440, ERRZERO, 
                                           "Overloading of threads per core!!\n");
                            } /* end if */

                         } /* end if */
                         else
                         {
                             SSLOGERROR(ERRCLS_INT_PAR, ESS441, ERRZERO, 
                                        "Can not set core affinity, core is exclusively used for other task\n");
                             RETVALUE(RFAILED);
                         } /* end else */
                         tskNotFound = FALSE;
                           break;
                      } /* end if */
                  } /* end inner for */
               } /* end for */

               /* check if tskAssociatedTskId is valid or not */
               if (coreIndex == SS_MAX_CORES)
                {
                    SSLOGERROR(ERRCLS_INT_PAR, ESS442, ERRZERO, "Invalid core id\n");
                    RETVALUE(RFAILED);
                } /* if */
             break;
          } /* end case SS_AFFINITY_MODE_ASSOC */
          case SS_AFFINITY_MODE_EXCL:
          {
             /* check if any thread is already running on the core */
             if (coreId != SS_DEFAULT_CORE && 
                 osCp.mCInfo.coreInfo[coreId].thrs == osCp.mCInfo.cpuInfo.threadRegister[coreId] &&
                !osCp.mCInfo.coreInfo[coreId].exclusive)
              {
                 /* call the implementation specific affinity function */
                 ret = ssdSetAffinity(tskId, coreId);
    
                 if (ret != ROK)
                 {
                    SSLOGERROR(ERRCLS_INT_PAR, ESS443, ERRZERO, "Failed to set core affinity\n");
                    RETVALUE(RFAILED);
                 } /* end if */

                 /* lock mCInfo */
                 SLock(&osCp.mCILock);

                 /* set the exclusive flag so that the core will not be used for other system tasks */
                  osCp.mCInfo.coreInfo[coreId].exclusive = TRUE;
 
                  /* save the tskId in tskList */
                  osCp.mCInfo.coreInfo[coreId].tskPerCoreLst[osCp.mCInfo.cpuInfo.threadRegister[coreId] - 
                  osCp.mCInfo.coreInfo[coreId].thrs] = *tskId;

                  /* decrement the available thread count in the thread register */
                  osCp.mCInfo.coreInfo[coreId].thrs--;
 
                 /* unlock mCInfo */
                  SUnlock(&osCp.mCILock);

             } /* end if */
             else if (coreId == SS_DEFAULT_CORE)
             {
                 U32 coreCounter = 0;
                 U32 coreIndex = 0;
                 /*ss013.301: Fixed Warnings for 32/64 bit compilation*/ 
                 for (coreIndex = osCp.mCInfo.currentCore;  
                      coreCounter < osCp.mCInfo.cpuInfo.numCores; 
                      coreCounter++)
                     {
                        ++coreIndex;
                        coreIndex = (coreIndex)%osCp.mCInfo.cpuInfo.numCores;
                        if (!osCp.mCInfo.coreInfo[coreIndex].exclusive 
                            && osCp.mCInfo.cpuInfo.threadRegister[coreIndex])
                        {
                            if ( osCp.mCInfo.coreInfo[coreIndex].thrs == 
                                 osCp.mCInfo.cpuInfo.threadRegister[coreIndex] &&
                                 osCp.mCInfo.coreInfo[coreIndex].thrs)  
                            {
                               /* call the implementation specific affinity function */
                                ret = ssdSetAffinity(tskId, coreIndex);
        
                                if (ret != ROK)
                                 {
                                    SSLOGERROR(ERRCLS_INT_PAR, ESS444, ERRZERO, "Failed to set core affinity\n");
                                    RETVALUE(RFAILED);
                                 } /* end if */
     
                                 /* lock mCInfo */
                                 SLock(&osCp.mCILock);

                                 /* move the current core index */
                                 osCp.mCInfo.currentCore = (coreIndex+1)%osCp.mCInfo.cpuInfo.numCores;
      
                                 /* save the tskId in tskList */
                                 osCp.mCInfo.coreInfo[coreIndex].tskPerCoreLst[               
                                 osCp.mCInfo.cpuInfo.threadRegister[coreIndex] - 
                                 osCp.mCInfo.coreInfo[coreIndex].thrs] = *tskId;
 
                                /* decrement the available thread count in the thread register */
                                 osCp.mCInfo.coreInfo[coreIndex].thrs--;
 
                               /* set the exclusive flag so that the core will not 
                                  be used for other system tasks */
                                  osCp.mCInfo.coreInfo[coreIndex].exclusive = TRUE;

                                  /* unlock mCInfo */
                                  SUnlock(&osCp.mCILock);

                                  break;
                               } /* end if there are threads available in the core */    
                            } /* end if the core is not exclusive flagged and 
                                 the core has threads for SSI use */
                         } /* end for */
                  if (coreCounter == osCp.mCInfo.cpuInfo.numCores)
                  {
                     SSLOGERROR(ERRCLS_INT_PAR, ESS445, ERRZERO, 
                                "Failed to set core affinity, no threads on cores available\n");
                     RETVALUE(RFAILED);
                  } /* end if no thrs on cores available */

              } /* else if */
              else
              {
                 SSLOGERROR(ERRCLS_INT_PAR, ESS446, ERRZERO, "Can not set exclusive affinity for the core\n");
                 RETVALUE(RFAILED);
              } /* end else */
            break;
         } /* end case SS_AFFINITY_MODE_EXCL */
         default:
         {
            SSLOGERROR(ERRCLS_INT_PAR, ESS447, ERRZERO, "Invalid mode for setting core affinity\n");
            RETVALUE(RFAILED);
         } /* end default case */
    } /* end of switch */

    RETVALUE(ROK);
               

} /* SSetAffinity */

#endif /* SS_MULTICORE_SUPPORT || SS_AFFINITY_SUPPORT*/

/** end multi-core support **/


/*
*
*       Fun:   Destroy system task
*
*       Desc:  This function is used to destroy a system task. The
*              entry is located in the system task table and the
*              implementation-specific function is called.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_task.c
*
*/
#ifdef ANSI
PUBLIC S16 SDestroySTsk
(
SSTskId tskId                   /* system task to be destroyed */
)
#else
PUBLIC S16 SDestroySTsk(tskId)
SSTskId tskId;                  /* system task to be destroyed */
#endif
{
   S16 ret;
   /* ss029.103: modification: the subscript should be of same type */
   SsIdx i;
   SsIdx idx;
   SsSTskEntry *sTsk;
	/* ss002.301 Additions */
/*ss013.301 : changes related to SS_AFFINITY_SUPPORT*/
#if defined(SS_MULTICORE_SUPPORT) || defined(SS_AFFINITY_SUPPORT)
   U32 tskInd = 0;
#endif /* SS_MULTICORE_SUPPORT || SS_AFFINITY_SUPPORT*/


   TRC1(SDestroySTsk);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* validate the system task ID */
   if (tskId >= SS_MAX_STSKS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS448, (ErrVal) tskId, "Invalid task ID");
      RETVALUE(RFAILED);
   }
#endif


   /* lock the system task table */
   ret = SLock(&osCp.sTskTblLock);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS449, (ErrVal) ret,
                     "Could not lock system task table");
#endif

      RETVALUE(RFAILED);
   }


   idx = (SsIdx) tskId;
   sTsk = &osCp.sTskTbl[idx];


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* 
    * check to see this system task exists and it is not already scheduled
    *  for termination 
    */
   if (sTsk->used != TRUE)
   {

  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
           SSLOGERROR(ERRCLS_DEBUG, ESS450, ERRZERO,
                       "Could not give the Semaphore");
           RETVALUE(RFAILED);
#endif
      }

      SSLOGERROR(ERRCLS_INT_PAR, ESS451, (ErrVal) idx,
                        "Invalid system task ID");
      RETVALUE(RFAILED);
   }
   else if (sTsk->termPend != FALSE)
   {

  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
           SSLOGERROR(ERRCLS_DEBUG, ESS452, ERRZERO,
                       "Could not give the Semaphore");
           RETVALUE(RFAILED);
#endif
      }

      SSLOGERROR(ERRCLS_INT_PAR, ESS453, (ErrVal) idx,
                        "Invalid system task ID");
      RETVALUE(RFAILED);
   }
#endif


   /* lock this system task entry */
   if (!SS_CHECK_CUR_STSK(sTsk))
   {
      ret = SLock(&sTsk->lock);
      if (ret != ROK)
      {

  /* ss006.13: addition */
         if ( SUnlock(&osCp.sTskTblLock) != ROK)
         {
#if (ERRCLASS & ERRCLS_DEBUG)
             SSLOGERROR(ERRCLS_DEBUG, ESS454, ERRZERO,
                       "Could not give the Semaphore");
             RETVALUE(RFAILED);
#endif
         }

#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS455, (ErrVal) ret,
                        "Could not lock system task entry");
#endif

         RETVALUE(RFAILED);
      }
   }

   /* lock the TAPA task table */
   SS_ACQUIRE_ALL_SEMA(&osCp.tTskTblSem, ret);
   if (ret != ROK)
   {
      if (!SS_CHECK_CUR_STSK(sTsk))
      {

  /* ss006.13: addition */
         if ( SUnlock(&sTsk->lock) != ROK)
         {
#if (ERRCLASS & ERRCLS_DEBUG)
             SSLOGERROR(ERRCLS_DEBUG, ESS456, ERRZERO,
                       "Could not give the Semaphore");
             RETVALUE(RFAILED);
#endif
         }
      }

  /* ss006.13: addition */
         if ( SUnlock(&osCp.sTskTblLock) != ROK)
         {
#if (ERRCLASS & ERRCLS_DEBUG)
             SSLOGERROR(ERRCLS_DEBUG, ESS457, ERRZERO,
                       "Could not give the Semaphore");
             RETVALUE(RFAILED);
#endif
         }

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS458, ERRZERO,
                     "Could not lock TAPA task table");
#endif

      RETVALUE(RFAILED);
   }


   /* If this system task entry has any TAPA tasks attached,
    *  we have to detach them
    */
   if (sTsk->numTTsks)
   {
      /* detach all TAPA tasks that are attached here */
      for (i = 0;  i < SS_MAX_TTSKS;  i++)
      {
         if (sTsk->tTsks[i] == SS_INVALID_IDX)
            continue;

         osCp.tTskTbl[sTsk->tTsks[i]].sTsk = NULLP;
         sTsk->tTsks[i] = SS_INVALID_IDX;
         sTsk->numTTsks--;
      }
   }


   /* set the termination pending flag to TRUE */
   sTsk->termPend = TRUE;


   /* unlock everything */
   SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);

   if (!SS_CHECK_CUR_STSK(sTsk))
   {

  /* ss006.13: addition */
      if ( SUnlock(&sTsk->lock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS459, ERRZERO,
                       "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
      }
   }


  /* ss006.13: addition */
   if ( SUnlock(&osCp.sTskTblLock) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
        SSLOGERROR(ERRCLS_DEBUG, ESS460, ERRZERO,
                     "Could not give the Semaphore");
        RETVALUE(RFAILED);
#endif
    }


   /* We call this after unlocking because it is possible that the
    *  caller is this very system task and we need to take care of
    *  that. The actual mechanism of notifying the thread that it
    *  has to die, or actually killing the thread is left to the
    *  implementation.
    */
   ret = ssdDestroySTsk(sTsk);
   if (ret != ROK)
   {
      /* Here, we're a little messed up. We've pretty much made this
       *  system task unusable, but now, its not going to die. So..??
       */

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS461, (ErrVal) ret,
                  "Could not destroy system task");
#endif

      RETVALUE(RFAILED);
   }
   
   /* multi-core support */
/*ss013.301 : changes related to SS_AFFINITY_SUPPORT*/
#if defined(SS_MULTICORE_SUPPORT) || defined(SS_AFFINITY_SUPPORT)

   /* Remove CPU affinity if any */
   for (tskInd = 0;  tskInd < SS_MAX_STSKS;  tskInd++)
   {
      if (osCp.sTskTbl[tskInd].tskId == sTsk->tskId)
      {
          /* search for the tskId in coreInfo */
          U32 coreId = 0;
          for (coreId = 0; coreId < SS_MAX_CORES; coreId++)
          {
             U32 thrId = 0;
             for (thrId = 0; thrId < SS_MAX_THREADS_PER_CORE; thrId++)
             {
                if (sTsk->tskId == osCp.mCInfo.coreInfo[coreId].tskPerCoreLst[thrId])
                 {
                    /* lock mCInfo */
                    SLock(&osCp.mCILock);

                    /* increment the available threads */
                    osCp.mCInfo.coreInfo[coreId].thrs++;

                    /* reset the thread id */
                    osCp.mCInfo.coreInfo[coreId].tskPerCoreLst[thrId] = 0;

                    /* if exclusive flag is set then remove it */
                   if (osCp.mCInfo.coreInfo[coreId].exclusive)
                   {
                      osCp.mCInfo.coreInfo[coreId].exclusive = FALSE;
                   } /* end if excl set */

                   /* unlock mCInfo */
                   SUnlock(&osCp.mCILock);

                   break;
                } /* end if sTsk matched a thread */
             } /* end for loop of thread Ids */
          } /* for */
          break;
      } /* end if */
   } /* end for */

#endif /* SS_MULTICORE_SUPPORT || SS_AFFINITY_SUPPORT*/
/* end multi-core support */

   /* ss019.103 - added to release semaphore for system task */
#ifndef NS
   if (ssPostSema(&osCp.dep.ssStarted) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
       SSLOGERROR(ERRCLS_DEBUG, ESS462, ERRZERO,
                         "Could not unlock the Semaphore");
       RETVALUE(RFAILED);
#endif
   }
#endif
   
   RETVALUE(ROK);
} /* SDestroySTsk */



/*
*
*       Fun:   Attach TAPA task
*
*       Desc:  This function is used to attach a TAPA task to a
*              system task. The system task will begin to execute
*              the TAPA task.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes:
*
*       File:  ss_task.c
*
*/
/* ss029.103: addition: procId added */ 
#ifndef SS_MULTIPLE_PROCS

#ifdef ANSI
PUBLIC S16 SAttachTTsk
(
Ent ent,                        /* entity ID of the task */
Inst inst,                      /* instance ID of the task */
SSTskId sTskId                  /* system task to use */
)
#else
PUBLIC S16 SAttachTTsk(ent, inst, sTskId)
Ent ent;                        /* entity ID of the task */
Inst inst;                      /* instance ID of the task */
SSTskId sTskId;                 /* system task to use */
#endif

#else /* SS_MULTIPLE_PROCS */

#ifdef ANSI
PUBLIC S16 SAttachTTsk
(
ProcId proc,                    /* processor ID of the task */
Ent ent,                        /* entity ID of the task */
Inst inst,                      /* instance ID of the task */
SSTskId sTskId                  /* system task to use */
)
#else
PUBLIC S16 SAttachTTsk(proc, ent, inst, sTskId)
ProcId proc;                    /* processor ID of the task */
Ent ent;                        /* entity ID of the task */
Inst inst;                      /* instance ID of the task */
SSTskId sTskId;                 /* system task to use */
#endif

#endif /* SS_MULTIPLE_PROCS */

{
   S16 ret;
   S16 i;
   SsIdx idx;
   SsSTskEntry *sTsk;
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   U16 procIdIdx;
#endif /* SS_MULTIPLE_PROCS */
#ifdef SS_MULTICORE_SUPPORT
   SsTTskEntry *tTsk;
#ifdef SS_MULTIPLE_PROCS
   void *xxCb;
#endif /* SS_MULTIPLE_PROCS */
#endif


   TRC1(SAttachTTsk);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check entity and instance range */
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   /* check proc, entity and instance range */
   if ((proc == SS_INV_PROCID) || (ent >= SS_MAX_ENT) ||  (inst >= SS_MAX_INST))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS463, ERRZERO, "Invalid processor/entity/instance");
      RETVALUE(RFAILED);
   }
#else /* SS_MULTIPLE_PROCS */
   /* check entity and instance range */
   if (ent >= SS_MAX_ENT ||  inst >= SS_MAX_INST)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS464, ERRZERO, "Invalid entity/instance");
      RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */

   /* check the system task index */
   if ((SsIdx)sTskId >= SS_MAX_STSKS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS465, (ErrVal) sTskId,
                  "Invalid system task ID");
      RETVALUE(RFAILED);
   }
#endif

/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   /* get the proc id idx */
   procIdIdx = SGetProcIdIdx(proc);

   if (procIdIdx == SS_INV_PROCID)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS466, ERRZERO,
                             "Could not find proc id index");
#endif
      RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */

   /* lock the system task table */
   ret = SLock(&osCp.sTskTblLock);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS467, (ErrVal) ret,
                     "Could not lock system task table");
#endif

      RETVALUE(RFAILED);
   }


   sTsk = &osCp.sTskTbl[(SsIdx)sTskId];


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* verify that this system task exists */
   if (sTsk->used == FALSE)
   {

  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS468, ERRZERO,
                     "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
      }

      SSLOGERROR(ERRCLS_INT_PAR, ESS469, (ErrVal) sTskId,
                     "Unknown system task ID");
      RETVALUE(RFAILED);
   }
#endif


   /* lock the system task entry */
   if (!SS_CHECK_CUR_STSK(sTsk))
   {
      ret = SLock(&sTsk->lock);
      if (ret != ROK)
      {

  /* ss006.13: addition */
        if ( SUnlock(&osCp.sTskTblLock) != ROK)
        {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS470, ERRZERO,
                     "Could not give the Semaphore");
            RETVALUE(RFAILED);
#endif
        }

#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS471, (ErrVal) ret,
                        "Could not lock system task entry");
#endif

         RETVALUE(RFAILED);
      }
   }


   /* if this system task is about to die, we don't attach */
   if (sTsk->termPend == TRUE)
   {
      if (!SS_CHECK_CUR_STSK(sTsk))
      {

  /* ss006.13: addition */
        if ( SUnlock(&sTsk->lock) != ROK)
        {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS472, ERRZERO,
                     "Could not give the Semaphore");
            RETVALUE(RFAILED);
#endif
        }
      }

  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS473, ERRZERO,
                     "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
      }

      RETVALUE(RFAILED);
   }


   /* lock the TAPA task table */
   SS_ACQUIRE_ALL_SEMA(&osCp.tTskTblSem, ret);
   if (ret != ROK)
   {
      if (!SS_CHECK_CUR_STSK(sTsk))
      {

  /* ss006.13: addition */
        if ( SUnlock(&sTsk->lock) != ROK)
        {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS474, ERRZERO,
                     "Could not give the Semaphore");
            RETVALUE(RFAILED);
#endif
        }
      }


  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS475, ERRZERO,
                     "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
      }

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS476, ERRZERO,
                     "Could not lock TAPA task table");
#endif

      RETVALUE(RFAILED);
   }


   /* get the index of the TAPA task entry in the table */
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   idx = osCp.tTskIds[procIdIdx][ent][inst];
#else /* SS_MULTIPLE_PROCS */
   idx = osCp.tTskIds[ent][inst];
#endif /* SS_MULTIPLE_PROCS */

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check out the TAPA task ID */
   if (idx == SS_TSKNC)
   {
      SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);
      if (!SS_CHECK_CUR_STSK(sTsk))
      {

  /* ss006.13: addition */
        if ( SUnlock(&sTsk->lock) != ROK)
        {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS477, ERRZERO,
                     "Could not give the Semaphore");
            RETVALUE(RFAILED);
#endif
        }
      }

  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS478, ERRZERO,
                     "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
      }

      SSLOGERROR(ERRCLS_INT_PAR, ESS479, ERRZERO, "Unknown task");
      RETVALUE(RFAILED);
   }
#endif


   /* verify that this TAPA task is not already attached */
   if (osCp.tTskTbl[idx].sTsk != NULLP)
   {
      SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);
      if (!SS_CHECK_CUR_STSK(sTsk))
      {

  /* ss006.13: addition */
        if ( SUnlock(&sTsk->lock) != ROK)
        {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS480, ERRZERO,
                     "Could not give the Semaphore");
            RETVALUE(RFAILED);
#endif
        }
      }

  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS481, ERRZERO,
                     "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
      }

      RETVALUE(RFAILED);
   }


   /* verify that there is space for another TAPA task */
   if (sTsk->numTTsks == SS_MAX_TTSKS)
   {
      SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);
      if (!SS_CHECK_CUR_STSK(sTsk))
      {

  /* ss006.13: addition */
        if ( SUnlock(&sTsk->lock) != ROK)
        {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS482, ERRZERO,
                     "Could not give the Semaphore");
            RETVALUE(RFAILED);
#endif
        }
      }

  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS483, ERRZERO,
                     "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
      }

      RETVALUE(ROUTRES);
   }


   /*  Find place for this TAPA task in the system task's list
    *  of TAPA tasks to run. Plug in this TAPA task.
    */
   for (i = 0;  i < SS_MAX_TTSKS;  i++)
   {
      if (sTsk->tTsks[i] == SS_INVALID_IDX)
      {
         sTsk->tTsks[i] = idx;
         sTsk->numTTsks++;
         break;
      }
   }


   /* Fill in the system task info in the TAPA task entry, so
    *  the TAPA task knows who's running it.
    */
   osCp.tTskTbl[idx].sTsk = sTsk;
#ifdef SS_MULTICORE_SUPPORT
   tTsk = &osCp.tTskTbl[idx];
   if(tTsk->initTsk != NULLP)
   {
#ifndef SS_MULTIPLE_PROCS 
       (Void)(tTsk->initTsk)(tTsk->ent, tTsk->inst, sTsk->region, PWR_UP);
#else
          /* retrieve proc id index in the proc id table */
        procIdIdx = SGetProcIdIdx(tTsk->proc);

        /* Check whether the proc id exist in the proc id table */
        if (procIdIdx == SS_INV_PROCID_IDX)
        {
#if (ERRCLASS & ERRCLS_INT_PAR)
                SSLOGERROR(ERRCLS_INT_PAR, ESS389, ERRZERO,
                     "Could not find proc table index");
#endif

              RETVALUE(RFAILED);
        }
       (Void)(tTsk->initTsk)(tTsk->proc, tTsk->ent, tTsk->inst, sTsk->region, PWR_UP, &xxCb);
       /* 
        * store the control block. The control block may be NULL in some cases
        */
       idx = osCp.tTskIds[procIdIdx][tTsk->ent][tTsk->inst];
#if (ERRCLASS & ERRCLS_INT_PAR)
       if ( xxCb == NULLP )
       {
                SSLOGERROR(ERRCLS_INT_PAR, ERRZERO, ERRZERO,
                                         "Null pointer");
       }
#endif
        osCp.tTskTbl[idx].xxCb = xxCb;
#endif /* SS_MULTIPLE_PROCS */
   }
#endif /* SS_MULTICORE_SUPPORT */


   /* call the implementation to do anything implementation-specific */
   ret = ssdAttachTTsk(&osCp.tTskTbl[idx]);


   /* unlock the tables; we're done */
   SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);
   if (!SS_CHECK_CUR_STSK(sTsk))
   {

  /* ss006.13: addition */
      if ( SUnlock(&sTsk->lock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS484, ERRZERO,
                     "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
      }
   }

  /* ss006.13: addition */
   if ( SUnlock(&osCp.sTskTblLock) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
        SSLOGERROR(ERRCLS_DEBUG, ESS485, ERRZERO,
                     "Could not give the Semaphore");
        RETVALUE(RFAILED);
#endif
   }


   /* If the implementation didn't succeed, we have to undo everything.
    *  We call SDetachTTsk, to make it easier.
    */
   if (ret != ROK)
   {
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
      SDetachTTsk(proc, ent, inst);
#else /* SS_MULTIPLE_PROCS */
      SDetachTTsk(ent, inst);
#endif /* SS_MULTIPLE_PROCS */
      RETVALUE(RFAILED);
   }


   RETVALUE(ROK);
} /* SAttachTTsk */


/*
*
*       Fun:   Detach TAPA task
*
*       Desc:  This function is used to detach a TAPA task from a
*              system task. The system task will stop executing
*              the TAPA task.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_task.c
*
*/
/* ss029.103: addition: procId added */ 
#ifndef SS_MULTIPLE_PROCS

#ifdef ANSI
PUBLIC S16 SDetachTTsk
(
Ent ent,                        /* entity ID of the task */
Inst inst                       /* instance ID of the task */
)
#else
PUBLIC S16 SDetachTTsk(ent, inst)
Ent ent;                        /* entity ID of the task */
Inst inst;                      /* instance ID of the task */
#endif

#else /* SS_MULTIPLE_PROCS */

#ifdef ANSI
PUBLIC S16 SDetachTTsk
(
ProcId proc,                    /* processor ID of the task */
Ent ent,                        /* entity ID of the task */
Inst inst                       /* instance ID of the task */
)
#else
PUBLIC S16 SDetachTTsk(proc, ent, inst)
ProcId proc;                    /* processor ID of the task */
Ent ent;                        /* entity ID of the task */
Inst inst;                      /* instance ID of the task */
#endif

#endif /* SS_MULTIPLE_PROCS */

{
   S16 ret;
   S16 i;
   SsIdx idx;
   SsTTskEntry *tTsk;
   SsSTskEntry *sTsk;
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   U16 procIdIdx;
#endif /* SS_MULTIPLE_PROCS */

   TRC1(SDetachTTsk);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check entity and instance ranges */
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   /* check entity and instance ranges */
   if ((proc == SS_INV_PROCID) || (ent >= SS_MAX_ENT) ||  (inst >= SS_MAX_INST))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS486, ERRZERO, "Invalid processor/entity/instance");
      RETVALUE(RFAILED);
   }
#else /* SS_MULTIPLE_PROCS */
   /* check entity and instance ranges */
   if (ent >= SS_MAX_ENT ||  inst >= SS_MAX_INST)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS487, ERRZERO, "Invalid entity/instance");
      RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */
#endif

/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   /* get the proc id idx */
   procIdIdx = SGetProcIdIdx(proc);

   if (procIdIdx == SS_INV_PROCID)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS488, ERRZERO,
                             "Could not find proc id index");
#endif
      RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */


   /* Lock the system task table. We do this to prevent
    *  the system task from being destroyed and confusing
    *  matters before we detach.
    */
   ret = SLock(&osCp.sTskTblLock);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS489, (ErrVal) ret,
                     "Could not lock system task table");
#endif

      RETVALUE(RFAILED);
   }


   /* lock the TAPA task table */
   SS_ACQUIRE_ALL_SEMA(&osCp.tTskTblSem, ret);
   if (ret != ROK)
   {

  /* ss006.13: addition */
    if ( SUnlock(&osCp.sTskTblLock) != ROK)
    {
#if (ERRCLASS & ERRCLS_DEBUG)
        SSLOGERROR(ERRCLS_DEBUG, ESS490, ERRZERO,
                     "Could not give the Semaphore");
        RETVALUE(RFAILED);
#endif
    }

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS491, ERRZERO,
                     "Could not lock TAPA task table");
#endif

      RETVALUE(RFAILED);
   }


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* Check this TAPA task. We do this with the TAPA task table
    *  locked, coz we don't want the task to be found, but then
    *  be deregistered before we lock
    */
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   if (osCp.tTskIds[procIdIdx][ent][inst] == SS_TSKNC)
#else /* SS_MULTIPLE_PROCS */
   if (osCp.tTskIds[ent][inst] == SS_TSKNC)
#endif /* SS_MULTIPLE_PROCS */
   {
      SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);

  /* ss006.13: addition */
     if ( SUnlock(&osCp.sTskTblLock) != ROK)
     {
#if (ERRCLASS & ERRCLS_DEBUG)
        SSLOGERROR(ERRCLS_DEBUG, ESS492, ERRZERO,
                     "Could not give the Semaphore");
        RETVALUE(RFAILED);
#endif
     }

      SSLOGERROR(ERRCLS_INT_PAR, ESS493, ERRZERO, "Unknown task");
      RETVALUE(RFAILED);
   }
#endif

/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   idx = osCp.tTskIds[procIdIdx][ent][inst];
#else /* SS_MULTIPLE_PROCS */
   idx = osCp.tTskIds[ent][inst];
#endif /* SS_MULTIPLE_PROCS */

   tTsk = &osCp.tTskTbl[idx];

   /* check if this TAPA task is attached to anyone */
   if (tTsk->sTsk == NULLP)
   {
      SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);

  /* ss006.13: addition */
     if ( SUnlock(&osCp.sTskTblLock) != ROK)
     {
#if (ERRCLASS & ERRCLS_DEBUG)
        SSLOGERROR(ERRCLS_DEBUG, ESS494, ERRZERO,
                     "Could not give the Semaphore");
        RETVALUE(RFAILED);
#endif
     }
      RETVALUE(ROK);
   }


   /* we get the system task entry out */
   sTsk = tTsk->sTsk;


   /* We unlock the TAPA task table here, and then re-lock it later
    *  because of lock sequencing--we have to lock the system task
    *  entry first, and then the TAPA task table. Note, the system
    *  task table is locked, so nobody can sneak in and destroy the
    *  system task while we're doing this.
    */
   SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);


   /* lock the system task entry */
   if (!SS_CHECK_CUR_STSK(sTsk))
   {
      ret = SLock(&sTsk->lock);
      if (ret != ROK)
      {

  /* ss006.13: addition */
       if ( SUnlock(&osCp.sTskTblLock) != ROK)
       {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS495, ERRZERO,
                     "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
       }

#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS496, (ErrVal) ret,
                        "Could not lock system task entry");
#endif

         RETVALUE(RFAILED);
      }
   }


   /* now we lock the TAPA task table */
   SS_ACQUIRE_ALL_SEMA(&osCp.tTskTblSem, ret);
   if (ret != ROK)
   {

  /* ss006.13: addition */
      if ( SUnlock(&sTsk->lock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS497, ERRZERO,
                     "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
      }
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS498, ERRZERO,
                     "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
      }

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS499, ERRZERO,
                     "Could not lock TAPA task table");
#endif

      RETVALUE(RFAILED);
   }


   /* Now, we can safely update both the system task entry
    *  and the TAPA task entry. First, we update the TAPA
    *  task entry--nobody is running it now.
    */
   tTsk->sTsk = NULLP;


   /*  Remove this TAPA task from the system task's list of
    *  TAPA tasks to run.
    */
   for (i = 0;  i < SS_MAX_TTSKS;  i++)
   {
      if (sTsk->tTsks[i] == idx)
      {
         sTsk->tTsks[i] = SS_INVALID_IDX;
         sTsk->numTTsks--;
         break;
      }
   }


   /* call the implementation to do anything it needs to */
   ret = ssdDetachTTsk(tTsk);


   /* unlock the TAPA task table */
   SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);

   /* unlock the system task entry */
   if (!SS_CHECK_CUR_STSK(sTsk))
   {

  /* ss006.13: addition */
      if ( SUnlock(&sTsk->lock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS500, ERRZERO,
                     "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
      }
   }

   /* unlock the system task table */

  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS501, ERRZERO,
                     "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
      }


   /* If the implementation couldn't detach the task, we just
    *  return an error, nothing else we can do.
    */
   if (ret != ROK)
   {
      RETVALUE(RFAILED);
   }


   RETVALUE(ROK);
} /* SDetachTTsk */


/*
*
*       Fun:   Post a message to a task
*
*       Desc:  This function is used to post a message to a TAPA
*              task. The message is delivered to the demand queue
*              of the system task that is running the specified
*              destination task.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_task.c
*
*/
#ifdef ANSI
PUBLIC S16 SPstTsk
(
Pst *pst,                       /* post information */
Buffer *mBuf                    /* message to post */
)
#else
PUBLIC S16 SPstTsk(pst, mBuf)
Pst *pst;                       /* post information */
Buffer *mBuf;                   /* message to post */
#endif
{
   S16 r;
   S16 i;
#if (defined(SS_DRVR_SUPPORT))
   S16 j;
#endif
   SsIdx dstIdx;
   SsIdx srcIdx;
   Prior prior;
   SsTTskEntry *tTsk;
   SsMsgInfo *msgInfo;
#if (defined(SS_DRVR_SUPPORT)  ||  defined(SS_RTR_SUPPORT))
   Pst nPst;
   Bool nPstUsed = FALSE;
#endif
#if (defined(SS_RTR_SUPPORT))
   Route rte;
#endif
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   U16 srcProcIdIdx;
   U16 dstProcIdIdx;
#endif /* SS_MULTIPLE_PROCS */
/*ss004.301: Cavium changes */
#ifdef SS_SEUM_CAVIUM
   Buffer  *wqBuf;
   S16     ret;
   cvmx_wqe_t *workPtr;
#endif /* SS_SEUM_CAVIUM */

	S16  retValue = 0; 
   Pst  tempPst;
 
   TRC1(SPstTsk);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check the message buffer */
   if (mBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS502, ERRZERO, "Invalid message buffer");
      RETVALUE(RFAILED);
   }

   /* check the pst structure */
   if (pst == NULLP)
   {
      SPutMsg(mBuf);
      SSLOGERROR(ERRCLS_INT_PAR, ESS503, ERRZERO, "Null pointer");
      RETVALUE(RFAILED);
   }
   /* ss021.103 - Addition to check for valid route */
   /* ss023.103 - Modification to fix bug in route validation */
   /* check the route */
   if (pst->route == RTENC)
   {
      SPutMsg(mBuf);
      SSLOGERROR(ERRCLS_INT_PAR, ESS504, ERRZERO, "No route defined");
      RETVALUE(RFAILED);
   }
#endif


   /* lock the TAPA task table */
   SS_ACQUIRE_SEMA(&osCp.tTskTblSem, r);
   if (r != ROK)
   {
      SPutMsg(mBuf);

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS505, ERRZERO,
                     "Could not lock TAPA task table");
#endif

      RETVALUE(RFAILED);
   }


#if (ERRCLASS & ERRCLS_INT_PAR)
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   if (pst->srcProcId == SS_INV_PROCID || pst->srcEnt >= SS_MAX_ENT       ||
       pst->srcInst >= SS_MAX_INST     || pst->dstProcId == SS_INV_PROCID ||
       pst->dstEnt >= SS_MAX_ENT       ||  pst->dstInst >= SS_MAX_INST)
#else /* SS_MULTIPLE_PROCS */
   if (pst->srcEnt >= SS_MAX_ENT       ||  pst->srcInst >= SS_MAX_INST    ||
       pst->dstEnt >= SS_MAX_ENT       ||  pst->dstInst >= SS_MAX_INST)
#endif /* SS_MULTIPLE_PROCS */
   {
 /* ss006.13: addition */
      if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS506, ERRZERO,
                     "Could not release the semaphore");
      RETVALUE(RFAILED);
#endif
      }

      SPutMsg(mBuf);

      SSLOGERROR(ERRCLS_INT_PAR, ESS507, ERRZERO,
                  "Invalid source/destination entity/instance");

      RETVALUE(RFAILED);
   }
#endif

   /* ss019.103 - modified for use with message router in virtual/physical
    * configuration */

#ifdef SS_RTR_SUPPORT
   /* check if we have a router task registered for this route */
   if (pst->route < RTENC  &&  osCp.rtrTskTbl[pst->route] != NULLP)
   {
      /* copy the Pst structure into a local duplicate */
      for (i = 0;  i < (S16)sizeof(Pst);  i++)
      {
         *(((U8 *)(&nPst)) + i) = *(((U8 *) pst) + i);
      }
      pst = &nPst;
      nPstUsed = TRUE;


      /* lock the router task entry */
      rte = pst->route;
      r = SLock(&osCp.rtrTskLocks[rte]);
      if (r != ROK)
      {
 /* ss006.13: addition */
         if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
         {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS508, ERRZERO,
                     "Could not release the semaphore");
            RETVALUE(RFAILED);
#endif
          }
         SPutMsg(mBuf);

#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS509, ERRZERO,
                     "Could not lock router task entry");
#endif

         RETVALUE(RFAILED);
      }

      /* call the router activation function */
      r = (*osCp.rtrTskTbl[rte])(pst, mBuf);

      /* unlock the router task entry */

  /* ss006.13: addition */
      if ( SUnlock(&osCp.rtrTskLocks[rte]) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS510, ERRZERO,
                     "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
      }

      if (r == RFAILED  ||  r == ROKIGNORE)
      {
 /* ss006.13: addition */
         if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
         {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS511, ERRZERO,
                     "Could not release the semaphore");
            RETVALUE(RFAILED);
#endif
          }
         RETVALUE((r == RFAILED) ? RFAILED : ROK);
      }
   }
#endif  /* SS_RTR_SUPPORT */

/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS

   /* get proc id index */
   srcProcIdIdx = SGetProcIdIdx(pst->srcProcId);
   dstProcIdIdx = SGetProcIdIdx(pst->dstProcId);

   if (srcProcIdIdx != SS_INV_PROCID_IDX)
      srcIdx = osCp.tTskIds[srcProcIdIdx][pst->srcEnt][pst->srcInst];

   if (dstProcIdIdx != SS_INV_PROCID_IDX)
      dstIdx = osCp.tTskIds[dstProcIdIdx][pst->dstEnt][pst->dstInst];

   if (((srcProcIdIdx != SS_INV_PROCID_IDX) && (srcIdx == SS_TSKNC)) || 
       ((dstProcIdIdx != SS_INV_PROCID_IDX) && (dstIdx == SS_TSKNC)))
   {
      if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS512, ERRZERO,
                     "Could not release the semaphore");
      RETVALUE(RFAILED);
#endif
      }

      SPutMsg(mBuf);

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS513, ERRZERO, "Unknown task");
#endif

      RETVALUE(RFAILED);
   }

#else /* SS_MULTIPLE_PROCS */
   /* ss019.103 - modified for use with message router in virtual/physical
    * configuration */

   /* get the src and destination task */
   srcIdx = osCp.tTskIds[pst->srcEnt][pst->srcInst];
   dstIdx = osCp.tTskIds[pst->dstEnt][pst->dstInst];


   /* If the source/destination processor ID is local, the
    *  source/destination TAPA task must be local.
    */
   if ((pst->srcProcId == osCp.procId  &&  srcIdx == SS_TSKNC) 
      ||  (pst->dstProcId == osCp.procId  &&  dstIdx == SS_TSKNC))
   {
 /* ss006.13: addition */
      if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS514, ERRZERO,
                     "Could not release the semaphore");
      RETVALUE(RFAILED);
#endif
      }
      SPutMsg(mBuf);

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS515, ERRZERO, "Unknown task");
#endif

      RETVALUE(RFAILED);
   }

#endif /* SS_MULTIPLE_PROCS */

#ifdef SS_DRVR_SUPPORT
   /* Check for the destination procId. If it is non-local,
    *  we need to find the driver task that will handle this
    *  message.
    */
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   if (dstProcIdIdx == SS_INV_PROCID_IDX)
#else /* SS_MULTIPLE_PROCS */
   if (pst->dstProcId != osCp.procId)
#endif /* SS_MULTIPLE_PROCS */
   {
      /*  Need to optimize this search.
       */
      for (i = 0;  i < SS_MAX_DRVRTSKS;  i++)
      {
         if (osCp.drvrTskTbl[i].used
               &&  pst->dstProcId >= osCp.drvrTskTbl[i].low
               &&  pst->dstProcId <= osCp.drvrTskTbl[i].high)
         {
            /* Copy the Pst structure into a local duplicate if not
             *  already done.
             */
            if (!nPstUsed)
            {
               for (j = 0;  j < (S16)sizeof(Pst);  j++)
               {
                  *(((U8 *)(&nPst)) + j) = *(((U8 *) pst) + j);
               }
               pst = &nPst;
               nPstUsed = TRUE;
            }


            /* lock the driver task entry */
            r = SLock(&osCp.drvrTskTbl[i].lock);
            if (r != ROK)
            {
 /* ss006.13: addition */
               if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
               {
#if (ERRCLASS & ERRCLS_DEBUG)
                  SSLOGERROR(ERRCLS_DEBUG, ESS516, ERRZERO,
                     "Could not release the semaphore");
                  RETVALUE(RFAILED);
#endif
               }
               SPutMsg(mBuf);

#if (ERRCLASS & ERRCLS_DEBUG)
               SSLOGERROR(ERRCLS_DEBUG, ESS517, ERRZERO,
                           "Could not lock driver task entry");
#endif

               RETVALUE(RFAILED);
            }
/*ss014.301 SSI-4GMX specific change*/
#ifndef SS_4GMX_LCORE
            CMCHKPKLOG(cmPkInst, osCp.drvrTskTbl[i].channel, mBuf, ESS518, pst);
#endif

            (osCp.drvrTskTbl[i].actvTsk)(pst, mBuf);

            /* unlock */

  /* ss006.13: addition */
            if ( SUnlock(&osCp.drvrTskTbl[i].lock) != ROK)
            {
#if (ERRCLASS & ERRCLS_DEBUG)
              SSLOGERROR(ERRCLS_DEBUG, ESS519, ERRZERO,
                     "Could not give the Semaphore");
              RETVALUE(RFAILED);
#endif
            }
 /* ss006.13: addition */
            if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
            {
#if (ERRCLASS & ERRCLS_DEBUG)
               SSLOGERROR(ERRCLS_DEBUG, ESS520, ERRZERO,
                     "Could not release the semaphore");
               RETVALUE(RFAILED);
#endif
            }
            RETVALUE(ROK);
         }
      }

 /* ss006.13: addition */
      if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
           SSLOGERROR(ERRCLS_DEBUG, ESS521, ERRZERO,
                     "Could not release the semaphore");
            RETVALUE(RFAILED);
#endif
      }
      SPutMsg(mBuf);

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS522, ERRZERO,
                  "Could not find a driver task to handle this proc ID");
#endif

      RETVALUE(RFAILED);
   }
#endif  /* SS_DRVR_SUPPORT */
 /* ss002.301 Modifications */
   /*  Write the message to the demand queue of the system
    *  task which is running the destination task
    */
   tTsk = &osCp.tTskTbl[dstIdx];

	cmMemcpy((U8*)&tempPst, (U8*)pst, sizeof(Pst));
   if(tTsk->cbTsk != NULLP)
   {
      retValue = tTsk->cbTsk(&tempPst,mBuf);
		if(retValue != ROK)
		{
	      if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
   	   {
#if (ERRCLASS & ERRCLS_DEBUG)
      		SSLOGERROR(ERRCLS_DEBUG, ESS512, ERRZERO,
                     "Could not release the semaphore");
      		RETVALUE(RFAILED);
#endif
      	}

#if (ERRCLASS & ERRCLS_DEBUG)
      	SSLOGERROR(ERRCLS_DEBUG, ESS513, ERRZERO, "call back function failed\n");
#endif
			RETVALUE(ROK);
		}
#ifdef SS_MULTIPLE_PROCS
		dstIdx = osCp.tTskIds[dstProcIdIdx][tempPst.dstEnt][tempPst.dstInst];
#else
      dstIdx = osCp.tTskIds[tempPst.dstEnt][tempPst.dstInst];
#endif 
      tTsk = &osCp.tTskTbl[dstIdx];
   }

   /* plug the Pst structure into the message information portion */
   msgInfo = (SsMsgInfo *) (mBuf->b_rptr);
   for (i = 0;  i < (S16 )sizeof(Pst);  i++)
      *(((U8 *)(&msgInfo->pst)) + i) = *(((U8 *) &(tempPst)) + i);

/* ss004.301 : Cavium cahnges */
#ifdef SS_SEUM_CAVIUM
   if (pst->dstProcId != osCp.procId)
   {
      if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
   	    "Could not release the semaphore");
         RETVALUE(RFAILED);
#endif
      }

      /* Copy the message to the FPA region */
      ret = SCpyMsgFpa(mBuf, &wqBuf);
      if( ret != ROK )
      {
         /* No need to free the buffer, its already done in called fun */
         RETVALUE(RFAILED);
      }

      /* Allocate for the mBuf */
      /* ss010.301: Cavium 32 bit changes */
      workPtr = cvmx_fpa_alloc(SS_CVMX_WQE_POOL);
      if( workPtr == NULLP )
      {
         SPutFpaMsg(wqBuf);
         RETVALUE(RFAILED);
      }

      /* Convert the pointers to physical address */
      ret = SConvPtrPhy(&wqBuf);
      if( ret != ROK )
      {
         SPutFpaMsg(wqBuf);
         RETVALUE(RFAILED);
      }

      /* Assign the values for work ptr */
      workPtr->qos      = 0;
      workPtr->grp      = pst->dstProcId;
      workPtr->tag_type = CVMX_POW_TAG_TYPE_NULL;
      workPtr->tag      = SS_CVMX_MBUF_TAG;

      workPtr->packet_ptr.ptr = (Void*)wqBuf;

      cvmx_pow_work_submit(workPtr, workPtr->tag, workPtr->tag_type, \
            workPtr->qos, workPtr->grp);

      RETVALUE(ROK);
   }
#endif /* SS_SEUM_CAVIUM */


   /*  Write the message to the demand queue of the system
    *  task which is running the destination task
    */
   tTsk = &osCp.tTskTbl[dstIdx];
   prior = tTsk->tskPrior;

   if (tTsk->sTsk == NULLP)
   {
 /* ss006.13: addition */
      if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
           SSLOGERROR(ERRCLS_DEBUG, ESS523, ERRZERO,
                     "Could not release the semaphore");
            RETVALUE(RFAILED);
#endif
      }
      SPutMsg(mBuf);

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS524, (ErrVal) 0,
                 "Destination TAPA task is not attached");
#endif

      RETVALUE(RFAILED);
   }


/*ss014.301 SSI-4GMX specific changes*/   
#ifndef SS_4GMX_LCORE
   r = ssDmndQPutLast(&tTsk->sTsk->dQ, mBuf,
                           ((prior * SS_MAX_MSG_PRI) + tempPst.prior));
#else
   if(tTsk->actvTsk != NULLP)
   {
       if(tTsk->cbTsk != NULLP)
       {
           r = rbICorePstTsk(&tempPst, mBuf, tTsk);
       }
       else
       {
           r = rbICorePstTsk(pst, mBuf, tTsk);
       }
   }
   else
   {
       r = RFAILED;
   }
#endif
   if (r != ROK)
   {
 /* ss006.13: addition */
      if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
           SSLOGERROR(ERRCLS_DEBUG, ESS525, ERRZERO,
                     "Could not release the semaphore");
            RETVALUE(RFAILED);
#endif
      }
      SPutMsg(mBuf);

#if (ERRCLASS & ERRCLS_ADD_RES)
      SSLOGERROR(ERRCLS_ADD_RES, ESS526, (ErrVal) r,
                     "Could not write to demand queue");
#endif

      RETVALUE(RFAILED);
   }


   /* unlock, we're done */
 /* ss006.13: addition */
   if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
        SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
                  "Could not release the semaphore");
        RETVALUE(RFAILED);
#endif
   }


   /* If the implementation has anything to do... note that
    *  we call it unlocked at this time.
    */
   ssdPstTsk(tempPst, mBuf, tTsk);

   RETVALUE(ROK);
} /* SPstTsk */

/* ss001.301: additions */
#ifdef SS_HISTOGRAM_SUPPORT 
/*
*
*       fun :  SGetTapaTskEntIds
*
*       Desc:  Get the tapa task entity id, which are registerd for SSI.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes:
*
*       File:  ss_task.c
*
*/
/* ss029.103: modification: procId added */

#ifdef ANSI
PUBLIC S16 SGetTapaTskEntIds
(
Ent *ent                        /* entity */
)
#else
PUBLIC S16 SGetTapaTskEntIds(ent)
Ent *ent;                        /* entity */
#endif
{

   U32 tskCnt = 0;

   TRC1(SGetTapaTskEntIds);
   /* Get the tapa task entity Ids from the osCp structure */
   for(tskCnt = 0; tskCnt < osCp.numTTsks; tskCnt++)
   {
      ent[tskCnt] = osCp.tTskTbl[tskCnt].ent;
   }

   RETVALUE(ROK);
} /* SGetTapaTskEntIds */

/*
*
*       Fun:   SRegForHstGrm
*
*       Desc:  This function is used to register a TAPA task,
*              for histogram facilty.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes:
*
*       File:  ss_task.c
*
*/
/* ss029.103: modification: procId added */

#ifdef ANSI
PUBLIC S16 SRegForHstGrm
(
Ent ent                        /* entity */
)
#else
PUBLIC S16 SRegForHstGrm(ent)
Ent ent;                        /* entity */
#endif
{

   U32 tskCnt = 0;
   S16 r = 0;

   TRC1(SRegForHstGrm);

   SS_ACQUIRE_SEMA(&osCp.tTskTblSem, r);
   if (r != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS623, ERRZERO,
                     "Could not lock TAPA task table");
#endif

      RETVALUE(RFAILED);
   }

   for(tskCnt = 0; tskCnt < osCp.numTTsks; tskCnt++)
   {
      if(osCp.tTskTbl[tskCnt].ent == ent)
      {
         osCp.tTskTbl[tskCnt].hstReg = TRUE;
         break;
      }
   }

   if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS639, ERRZERO,
                   "Could not release the semaphore");
          RETVALUE(RFAILED);
#endif
    }

   RETVALUE(ROK);
} /* SGetTapaTskEntIds */

/*
*
*       Fun:   SGetHstGrmInfo
*
*       Desc : Get the Histogram registration for TAPA task
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes:
*
*       File:  ss_task.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetHstGrmInfo
(
Ent   *entId,
Bool  *hstReg                        /* entity */
)
#else
PUBLIC S16 SGetHstGrmInfo(entId, hstReg)
Ent   *entId;
Bool  *hstReg;                        /* entity */
#endif
{

   U32 tskCnt = 0;
   Bool found = FALSE;
   *hstReg = 0;

   TRC1(SGetHstGrmInfo);
   for(tskCnt = 0; tskCnt < osCp.numTTsks; tskCnt++)
   {
      if( *entId == osCp.tTskTbl[tskCnt].ent)
      {
         *hstReg = osCp.tTskTbl[tskCnt].hstReg;
         found = TRUE;
          break;
      }
   }

   if(!found)
   {
      *entId = ENTNC;
      *hstReg = TRUE;
   }

   RETVALUE(ROK);
} /* SGetTapaTskEntIds */

#endif /* SS_HISTOGRAM_SUPPORT */

#ifdef SS_WATCHDOG
#ifdef ANSI
PUBLIC S16 SInitWatchdog
(
U16 port
)
#else
PUBLIC S16 SInitWatchdog(port)
U16 port;
#endif
{
 return ssdInitWatchDog(port);
}

#ifdef ANSI
PUBLIC S16 SRegCfgWd
(
U32 numNodes,
U8  *addr[],
U16 port[],
U32 timeout,
WdUserCallback callback,
void *data
)
#else
PUBLIC S16 SRegCfgWd(numNodes, addr, port, timeout, callback, data)
U32 numNodes;
U8  *addr[];
U16 port[];
U32 timeout;
WdUserCallback callback;
void *data;
#endif
{
   Txt prntBuf[PRNTSZE];
   int i = 0;

   /*ss013.301 :Fix for TRACE5 feature crash due to missing TRC MACRO*/
   TRC1(SRegCfgWd)

   osCp.wdCp.globWd.timeout = timeout;
   osCp.wdCp.globWd.callback = callback;
   osCp.wdCp.globWd.data = data;
   osCp.wdCp.globWd.numNodes = numNodes;

   SLock(&osCp.wdCp.wdLock);
   for(i = 0; i < SS_MAX_WD_NODES && i < numNodes; i++)
   {
#ifdef SS_WATCHDOG_IPV6
 /* ss002.301 Modifications */
      inet_pton(AF_INET6,(const char *)addr[i],osCp.wdCp.globWd.wdsta[i].addr);
#else
      osCp.wdCp.globWd.wdsta[i].addr.s_addr = inet_addr((const char *)addr[i]);
#endif /* SS_WATCHDOG_IPV6 */
      osCp.wdCp.globWd.wdsta[i].port = htons(port[i]);
      sprintf(prntBuf, "Configured [%s:%d] for watchdog\n", addr[i], port[i]);
      SPrint(prntBuf);
   }
   SUnlock(&osCp.wdCp.wdLock);
 /* ss002.301 Compilation fixes */
   /*ss013.301: Fixed Warnings for 32/64 bit compilation*/
#ifdef ALIGN_64BIT
   sprintf(prntBuf, "Configured %d nodes with timeout %u for Watchdog\n", osCp.wdCp.globWd.numNodes, osCp.wdCp.globWd.timeout);
#else
   sprintf(prntBuf, "Configured %d nodes with timeout %lu for Watchdog\n", osCp.wdCp.globWd.numNodes, osCp.wdCp.globWd.timeout);
#endif
   SPrint(prntBuf);

   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 SDeregCfgWd
(
void
)
#else
PUBLIC S16 SDeregCfgWd(void)
void;
#endif
{
   Txt prntBuf[PRNTSZE];
   int i = 0;

   /*ss013.301 :Fix for TRACE5 feature crash due to missing TRC MACRO*/
   TRC1(SDeregCfgWd)

   osCp.wdCp.globWd.timeout = 0;
   osCp.wdCp.globWd.callback = 0;
   osCp.wdCp.globWd.data = 0;
   osCp.wdCp.globWd.numNodes = 0;

   SLock(&osCp.wdCp.wdLock);
   for(i = 0; i < SS_MAX_WD_NODES; i++)
   {
	   /* ss002.301 Modifications */
      sprintf(prntBuf, "Deregister [%s:%d] for watchdog\n", inet_ntoa(osCp.wdCp.globWd.wdsta[i
].addr), osCp.wdCp.globWd.wdsta[i].port);
      osCp.wdCp.globWd.wdsta[i].addr.s_addr = 0;
       osCp.wdCp.globWd.wdsta[i].port = 0;
      SPrint(prntBuf);
   }
   SUnlock(&osCp.wdCp.wdLock);

   /* Implicit watchdog stop during dereg */
   SStopHrtBt();

   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 SStartHrtBt
(
U8 timeInterval /* time interval */
)
#else
PUBLIC S16 SStartHrtBt(timeInterval)
U8 timeInterval;
#endif
{
   TRC1(SStartHrtBt);

   ssdStartWatchDgTmr(NULLP, SS_TMR_HRTBT, timeInterval);
   ssdSndHrtBtMsg(TRUE, SS_WD_HB_REQ);

   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 SStopHrtBt
(
void
)
#else
PUBLIC S16 SStopHrtBt()
void
#endif
{
   TRC1(SStopHrtBt);

   osCp.wdCp.globWd.watchdogStop = 1;

   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 watchDgActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 watchDgActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
/* ss002.301 Fixed warnings */
#ifdef DEBUGP
   DateTime dt;
   Txt prntBuf[PRNTSZE];
#endif /* DEBUGP */

   TRC3(watchDgActvTsk)
#ifdef DEBUGP
   SGetDateTime(&dt);
   sprintf(prntBuf,"watchDgActvTsk: Time: %02d:%02d:%02d\n",dt.hour,dt.min, dt.sec
);
   SPrint(prntBuf);
#endif /* DEBUGP */
	RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 watchDgRcvrActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 watchDgRcvrActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
#ifdef DEBUGP
   DateTime dt;
#endif /* DEBUGP */
   Txt prntBuf[PRNTSZE];
   U16           n;
   S16			  err;
   struct sockaddr_in tmpaddr;
   Txt           hbMsg[SS_WD_HB_MSG_SIZE];
 /* ss002.301 Modifications */
#ifdef SS_LINUX
	socklen_t 	  socklen = sizeof(struct sockaddr);
#else
   int           socklen = sizeof(struct sockaddr);
#endif

   TRC3(watchDgActvTsk)

#ifdef DEBUGP
   SGetDateTime(&dt);
   sprintf(prntBuf,"watchDgRcvrActvTsk: Time: %02d:%02d:%02d\n",dt.hour, dt.min, dt.sec);
   SPrint(prntBuf);
#endif /* DEBUGP */

   while(!osCp.wdCp.globWd.watchdogStop)
   {
      err = recvfrom(osCp.wdCp.globWd.sock, hbMsg, SS_WD_HB_MSG_SIZE, 0, (struct sockaddr *)&tmpaddr, &socklen);
      if(err == -1)
      {
         sprintf(prntBuf,"watchDgRcvrActvTsk: recvfrom failed, errno %d\n", errno);
         SPrint(prntBuf);
         continue;
      }

      if(strcmp(hbMsg, "<HB>REQ</HB>") == 0)
      {
         /* Send back the reply */
#ifdef DEBUGP
         sprintf(prntBuf,"watchDgRcvrActvTsk: Recvd HB REQ message from [%s:%d]\n", inet_ntoa(tmpaddr.sin_addr), ntohs(tmpaddr.sin_port));
         SPrint(prntBuf);
#endif /* DEBUGP */

         strcpy(hbMsg, "<HB>RSP</HB>");
         sendto(osCp.wdCp.globWd.sock, hbMsg, strlen(hbMsg), 0, (struct sockaddr *)&tmpaddr, sizeof(tmpaddr));
      }
      else if(strcmp(hbMsg, "<HB>RSP</HB>") == 0)
      {
         /* Got a HB RSP, set the status for the correcponding node */
#ifdef DEBUGP
         sprintf(prntBuf,"watchDgRcvrActvTsk: Recvd HB RSP message from [%s:%d]\n", inet_ntoa(tmpaddr.sin_addr), ntohs(tmpaddr.sin_port)); 
         SPrint(prntBuf);
#endif /* DEBUGP */

         SLock(&osCp.wdCp.wdLock);
         for(n = 0; n < osCp.wdCp.globWd.numNodes; n++)
         {
            if(osCp.wdCp.globWd.wdsta[n].addr.s_addr == tmpaddr.sin_addr.s_addr)
            {
               osCp.wdCp.globWd.wdsta[n].status = 1;
            }
         }
         SUnlock(&osCp.wdCp.wdLock);
      }
      else
      {
#ifdef DEBUGP
         sprintf(prntBuf,"watchDgRcvrActvTsk: Rcvd invalid message\n");
         SPrint(prntBuf);
#endif /* DEBUGP */
      }
   }
	RETVALUE(ROK);
}

#endif /* SS_WATCHDOG */

/* ss002.301 Modifications */
#ifdef SS_THREAD_PROFILE
/*
*
*       Fun:   SGetThrdProf
*
*       Desc:  This function gets the current profile of a system task
*              The function sets the Entity, Instance, Event and time taken
*              for that thread to execurte the activate function of
*              that entity.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: This function may be called by the OS or Layer 1
*              hardware drivers.
*
*       File:  mt_ss.c
*
*/
#ifdef SS_MULTIPLE_PROCS
#ifdef ANSI
PUBLIC S16 SGetThrdProf
(
SSTskId *sTskId,
ProcId procId,
Ent ent,                       /* entity */
Inst inst,
Event *curEvent,
U32 *curEvtTime,
U64 *totTime
)
#else
PUBLIC S16 SGetThrdProf(sTskId, procId, ent, inst, evnt, curEvent, curEvtTime, totTime)
SSTskId *sTskId;
ProcId procId;
Ent ent;                      /* entity */
Inst inst;
Event *curEvent;
U32 *curEvtTime;
U64 *totTime;
#endif
#else
#ifdef ANSI
PUBLIC S16 SGetThrdProf
(
SSTskId *sTskId,
Ent ent,                       /* entity */
Inst inst,
Event *curEvent,
U32 *curEvtTime,
U64 *totTime
)
#else
PUBLIC S16 SGetThrdProf(sTskId, ent, inst, curEvent,curEvtTime, totTime)
SSTskId *sTskId;
Ent ent;                      /* entity */
Inst inst;
Event *curEvent;
U32 *curEvtTime;
U64 *totTime;
#endif
#endif /* SS_MULTIPLE_PROCS */
{
  S16 ret;
   SsIdx idx;
   SsTTskEntry *tTsk;
#ifdef SS_MULTIPLE_PROCS
   U16 procIdIdx;
#endif


   TRC1(SGetThrdProf);

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check entity and instance range */
#ifdef SS_MULTIPLE_PROCS
   /* check proc, entity and instance range */
   if ((procId == SS_INV_PROCID) || (ent >= SS_MAX_ENT) ||  (inst >= SS_MAX_INST))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS463, ERRZERO, "Invalid processor/entity/instance");
      RETVALUE(RFAILED);
   }
#else /* SS_MULTIPLE_PROCS */
   /* check entity and instance range */
   if (ent >= SS_MAX_ENT ||  inst >= SS_MAX_INST)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS464, ERRZERO, "Invalid entity/instance");
      RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */
#endif


   ret = SLock(&osCp.sTskTblLock);
   if (ret != ROK)
   {
      RETVALUE(RFAILED);
   }


#ifdef SS_MULTIPLE_PROCS
    procIdIdx = SGetProcIdIdx(procId);

    if (procIdIdx == SS_INV_PROCID_IDX)
    {
      RETVALUE(RFAILED);
    }

    idx = osCp.tTskIds[procIdIdx][ent][inst];
#else /* SS_MULTIPLE_PROCS */
    idx = osCp.tTskIds[ent][inst];
#endif /* SS_MULTIPLE_PROCS */

    tTsk = &osCp.tTskTbl[idx];
    if(tTsk == NULLP )
    {
             SUnlock(&osCp.sTskTblLock);
             RETVALUE(RFAILED);
    }
    *curEvent      = osCp.tTskTbl[idx].curEvent;
    *curEvtTime    = osCp.tTskTbl[idx].curEvtTime;
    *totTime       = osCp.tTskTbl[idx].totTime;
    *sTskId        = osCp.tTskTbl[idx].sTsk->tskId;

   SUnlock(&osCp.sTskTblLock);
   RETVALUE(ROK);
}
#endif /* SS_THREAD_PROFILE */

#ifdef SS_FBSED_TSK_REG
/*
*
*       Fun:   SRegTskInfo
*
*       Desc:  This function is used to register tasks based on cfg file.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*
*       File:  ss_task.c
*
*/
#ifdef ANSI
PUBLIC S16 SRegTskInfo
(
U8 *cfgFile
)
#else
PUBLIC S16 SRegTskInfo(cfgFile)
U8 *cfgFile;
#endif
{
   return cmCfgrTskReg(cfgFile); 
}
#endif /* SS_FBSED_TSK_REG */


/********************************************************************30**
  
         End of file:     sm_task.c@@/main/1 - Mon Nov 17 15:54:37 2008
  
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

1.2          ---      ag   1. Added ssdPstTsk() function in SPstTsk
             ---      ag   2. Fixed a bug in function SPstTsk
             ---      bsr  3. moved code from ssdDeregInitTskTmr to 
                              SDeregInitTskTmr.
             ---      bsr  4. Added timer deregistration to SDeregTTsk
             ---      bsr  5. Added a check in SPstTsk to see if the
                              destination tapa task is attached to a
                              system task.
             ---      bsr  6. packed channel id into mBuf instead
                              of passing it via route field in post
                              strucure before calling DrvrActvTsk
             ---      kp   7. Fixed bug in SDeregInitTskTmr
             ---      kp   8. Fixed bug in SDeregTTsk
             ---      kp   9. Changed parameters for ssdPstTsk
             ---      kp   9. Cosmetic changes

1.3          ---      kp   1. Added in Message Router support

1.3+         ss001.13 kp   1. Compile warning removed.
1.3+         ss006.13 jn   2. Compile warning "Value computed
                              is not used" removed for
                              SUnlock and SS_RELEASE_SEMA.
1.3+         ss019.103 bp   3. Modification for Message Router support
                              Addition of release of system task semaphore
1.3+         ss021.103 bjp  4. Return fail if invalid task type in SRegActvTsk
                                  and SRegTTsk
                               Check for valid route in SPstTsk
                               Modify SRegInit and SRegActvTsk
             ss023.103 bjp  5. Bug fix in validation of route for SPstTsk\
             ss024.103 bjp  6. Modifications for memory calculator tool 
1.3+         ss025.103      7. Added locks around counting semaphores
1.3+         ss029.103 kkj  1. Multiple proc ids support added
1.3+         ss032.103 kkj  1. Changes for calling the init function while
                               deregistering the TAPA task
/main/1      ---       rp   1. SSI enhancements for Multi-core architecture 
                               support
/main/1+     ss001.301 schandra1 1. SSI phase-2 valude added feature additions
/main/1+     ss002.301 prasanna     SDeRegTTsk fix
                       snatarajan   SRegCbTsk, to register a callback
                                    function with SSI
                       pmacharla    1. Fixed compilation warnings in SReg/SDereg CfgWd												
                                    2. Removed BIT_64 flag for thread profile
                       rss			   1. Call back functions registration facility
                                     added to SPstTsk
/main/1+     ss004.301 pmacharla    1. Cavium user mode related changes
/main/1+     ss010.301 rk           1. Cavium 32 bit changes
/main/1+     ss013.301 ssahniX      1. Fix for TRACE5 feature crash due
                                        to missing TRC MACRO
									2. Fixed Warnings for 32/64 bit compilation
                                    3. Addition of SS_AFFINITY_SUPPORT 
/main/1+     ss014.301 ssahniX      1. change in SPstTsk() (used  rbICorePstTsk()
                                      insted of ssDmndQPutLast) for SSI-4GMX
                                    2. change in INITMBLK for SSI-4GMX  
/main/1+     ss015.301 akapoor   1. Modifed in initialization as timer activation
                                    functions enclosed in a union .
                                    Also initialized the mtFlag to FALSE 
*********************************************************************91*/
