

/********************************************************************20**
 
     Name:     System Services -- Router
 
     Type:     C source file
 
     Desc:     Source code for router support in System Services.
 
     File:     ss_rtr.c
 
     Sid:      sm_rtr.c@@/main/1 - Mon Nov 17 15:54:36 2008
 
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


#ifdef SS_RTR_SUPPORT



/*
*
*       Fun:   SRegRtrTsk
*
*       Desc:  This function is used to register a router task.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes:
*
*       File:  ss_rtr.c
*
*/
#ifdef ANSI
PUBLIC S16 SRegRtrTsk
(
Route *routes,                  /* route IDs */
Cntr count,                     /* number of route IDs */
ActvTsk rtrTsk                  /* router activation task */
)
#else
PUBLIC S16 SRegRtrTsk(routes, count, rtrTsk)
Route *routes;                  /* route IDs */
Cntr count;                     /* number of route IDs */
ActvTsk rtrTsk;                 /* router activation task */
#endif
{
   S16 i;


   TRC1(SRegRtrTsk);


#if (ERRCLASS & ERRCLS_INT_PAR)
   for (i = 0;  i < count;  i++)
   {
      /* check for valid route ID */
      if (routes[i] == RTENC)
      {
         SSLOGERROR(ERRCLS_INT_PAR, ESS316, ERRZERO, "Invalid route ID");
         RETVALUE(RFAILED);
      }
/* ss029.103: modification: following check removed for multiple proc support */
#ifndef SS_MULTIPLE_PROCS
      /* check if route already registered */
      if (osCp.rtrTskTbl[routes[i]] != NULLP)
      {
         SSLOGERROR(ERRCLS_INT_PAR, ESS317, ERRZERO,
                     "Route already registered");
         RETVALUE(RFAILED);
      }
#endif /* SS_MULTIPLE_PROCS */
   }

   /* check activation function */
   if (rtrTsk == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS318, ERRZERO, "Null pointer");
      RETVALUE(RFAILED);
   }
#endif


   /* install this router task, for all requested routes */
   for (i = 0;  i < count;  i++)
   {
      if (SInitLock(&osCp.rtrTskLocks[routes[i]], SS_RTRENTRY_LOCK) != ROK)
      {

#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS319, ERRZERO,
                     "Could not initialize router task lock");
#endif

         break;
      }

      osCp.rtrTskTbl[routes[i]] = rtrTsk;
   }

   if (i != count)
   {
      for (--i;  i >= 0;  i--)
      {
         SDestroyLock(&osCp.rtrTskLocks[routes[i]]);
         osCp.rtrTskTbl[routes[i]] = NULLP;
      }


      RETVALUE(RFAILED);
   }


   RETVALUE(ROK);
}

 /* ss010.13: Addition */
/*
*
*       Fun:   SDeregRtrTsk
*
*       Desc:  This function is used to De-register a router task.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes:
*
*       File:  ss_rtr.c
*
*/
#ifdef ANSI
PUBLIC S16 SDeregRtrTsk
(
Route *routes,                  /* route IDs */
Cntr count                      /* number of route IDs */
)
#else
PUBLIC S16 SDeregRtrTsk(routes, count)
Route *routes;                  /* route IDs */
Cntr count;                     /* number of route IDs */
#endif
{
   S16 i;


   TRC1(SDeregRtrTsk);


#if (ERRCLASS & ERRCLS_INT_PAR)
   for (i = 0;  i < count;  i++)
   {
      /* check for valid route ID */
      if (routes[i] == RTENC)
      {
         SSLOGERROR(ERRCLS_INT_PAR, ESS320, ERRZERO, "Invalid route ID");
         RETVALUE(RFAILED);
      }

      /* check if route is not registered */
      if (osCp.rtrTskTbl[routes[i]] == NULLP)
      {
         SSLOGERROR(ERRCLS_INT_PAR, ESS321, ERRZERO,
                     "Route not registered");
         RETVALUE(RFAILED);
      }
   }
#endif

   /* We deregister all the requested routes, so lock the 
      router table remove the router task owned by it. */
   for (i = 0;  i < count;  i++)
   {
      if (SLock(&osCp.rtrTskLocks[routes[i]]) != ROK)
      {

#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS322, ERRZERO,
                     "Could not lock router task lock");
#endif

         RETVALUE(RFAILED);
      }

      osCp.rtrTskTbl[routes[i]] = NULLP;

      if (SUnlock(&osCp.rtrTskLocks[routes[i]]) != ROK)
      {

#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS323, ERRZERO,
                     "Could not unlock router task lock");
#endif

         RETVALUE(RFAILED);
      }
      if (SDestroyLock(&osCp.rtrTskLocks[routes[i]]) != ROK)
      {

#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS324, ERRZERO,
                     "Could not Destroy router task lock");
#endif

         RETVALUE(RFAILED);
      }

   } /* for loop */


   RETVALUE(ROK);
}

#endif /* SS_RTR_SUPPORT */
 


/********************************************************************30**
  
         End of file:     sm_rtr.c@@/main/1 - Mon Nov 17 15:54:36 2008
  
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
1.1+         ss010.13 jn   2. Added SDeregRtrTsk
1.1+         ss029.13 kkj  1. Multiple proc related changes
/main/1      ---      rp   1. SSI enhancements for Multi-core architecture
                              support
*********************************************************************91*/

