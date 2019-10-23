

/********************************************************************20**
 
     Name:     System Services -- Driver
 
     Type:     C source file
 
     Desc:     Source code for those functions in System Services
               that exist for driver support.
 
     File:     ss_drvr.c
 
     Sid:      sm_drvr.c@@/main/1 - Mon Nov 17 15:54:34 2008
 
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


#ifdef SS_DRVR_SUPPORT



/*
*
*       Fun:   SRegDrvrTsk
*
*       Desc:  This function is used to register a driver task.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes:
*
*       File:  ss_drvr.c
*
*/
#ifdef ANSI
PUBLIC S16 SRegDrvrTsk
(
Inst channel,                   /* channel instance */
ProcId low,                     /* processor ID -- low */
ProcId high,                    /* processor ID -- high */
ActvTsk actvTsk,                /* activation function */
ISTsk isTsk                     /* interrupt service function */
)
#else
PUBLIC S16 SRegDrvrTsk(channel, low, high, actvTsk, isTsk)
Inst channel;                   /* channel instance */
ProcId low;                     /* processor ID -- low */
ProcId high;                    /* processor ID -- high */
ActvTsk actvTsk;                /* activation function */
ISTsk isTsk;                    /* interrupt service function */
#endif
{
   S16 ret;
#if (ERRCLASS & ERRCLS_INT_PAR)

/* ss029.103: modification: multiple procId related changes */ 
#ifndef SS_MULTIPLE_PROCS
   ProcId thisProcId;
#endif

/* ss029.103: modification: multiple procId related changes */ 
#ifdef SS_MULTIPLE_PROCS
   U16 count;
   U16 i;
   ProcId procIdLst[SS_MAX_PROCS];
#endif /* SS_MULTIPLE_PROCS */

#endif

   TRC1(SRegDrvrTsk);

#if (ERRCLASS & ERRCLS_INT_PAR)

/* ss029.103: modification: multiple procId related changes */ 
#ifdef SS_MULTIPLE_PROCS
   if (SGetProcIdLst(&count, procIdLst) != ROK)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS001, ERRZERO, "Null procId list");
      RETVALUE(RFAILED);
   }

   for (i = 0; i < count; i++)
   {
      if (procIdLst[i] >= low  &&  procIdLst[i] <= high)
      {
       SSLOGERROR(ERRCLS_INT_PAR, ESS002, ERRZERO, "Invalid procId range");
       RETVALUE(RFAILED);
      }
   }
#else /* SS_MULTIPLE_PROCS */
   thisProcId = SFndProcId();
   if (thisProcId >= low  &&  thisProcId <= high)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS003, ERRZERO, "Invalid procId range");
      RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */

   if (channel >= SS_MAX_DRVRTSKS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS004, channel, "Invalid channel");
      RETVALUE(RFAILED);
   }

   /* check activation functions */
   if (actvTsk == NULLP  ||  isTsk == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS005, ERRZERO, "Null pointer");
      RETVALUE(RFAILED);
   }

   /* check if already registered */
   if (osCp.drvrTskTbl[channel].used == TRUE)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS006, ERRZERO,
                  "Driver task already registered");
      RETVALUE(RFAILED);
   }
#endif


#if (ERRCLASS & ERRCLS_DEBUG)
   /* check count of tasks */
   if (osCp.numDrvrTsks == SS_MAX_DRVRTSKS)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS007, ERRZERO, "Too many tasks");
      RETVALUE(ROUTRES);
   }
#endif


   if (SInitLock(&osCp.drvrTskTbl[channel].lock, SS_DRVRENTRY_LOCK) != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS008, ERRZERO, "Could not initialize lock");
#endif

      RETVALUE(RFAILED);
   }

   osCp.drvrTskTbl[channel].channel = channel;
   osCp.drvrTskTbl[channel].actvTsk = actvTsk;
   osCp.drvrTskTbl[channel].isTsk = isTsk;
   osCp.drvrTskTbl[channel].low = low;
   osCp.drvrTskTbl[channel].high = high;

   ret = ssdRegDrvrTsk(&osCp.drvrTskTbl[channel]);
   if (ret != ROK)
   {
      osCp.drvrTskTbl[channel].channel = 0;
      osCp.drvrTskTbl[channel].actvTsk = NULLP;
      osCp.drvrTskTbl[channel].isTsk = NULLP;
      osCp.drvrTskTbl[channel].low = 0;
      osCp.drvrTskTbl[channel].high = 0;
      SDestroyLock(&osCp.drvrTskTbl[channel].lock);
   }
   else
   {
      osCp.drvrTskTbl[channel].used = TRUE;
      osCp.numDrvrTsks++;
   }


   RETVALUE(ret);
}

/*  ss001.301: Additions */
/*
*
*       Fun:   SDeregDrvrTsk
*
*       Desc:  This function is used to de-register a driver task.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes:
*
*       File:  ss_drvr.c 
*
*/
#ifdef ANSI
PUBLIC S16 SDeregDrvrTsk
(
Inst channel                   /* channel instance */
)
#else
PUBLIC S16 SDeregDrvrTsk(channel)
Inst channel;
#endif
{
	/* ss002.301 Modifications */
   TRC1(SRegDrvrTsk);

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (channel >= SS_MAX_DRVRTSKS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESSXXX, channel, "Invalid channel");
      RETVALUE(RFAILED);
   }

   /* check if already registered */
   if (osCp.drvrTskTbl[channel].used != TRUE)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS477, ERRZERO,
                  "Driver task is not registered");
      RETVALUE(RFAILED);
   }
#endif


   if(SLock(&osCp.drvrTskTbl[channel].lock) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS477, ERRZERO,
                     "Could not lock driver task lock");
#endif
      RETVALUE(RFAILED);
   }
   ssdDeregDrvrTsk(&osCp.drvrTskTbl[channel]);

   osCp.drvrTskTbl[channel].channel = 0;
   osCp.drvrTskTbl[channel].actvTsk = NULLP;
   osCp.drvrTskTbl[channel].isTsk = NULLP;
   osCp.drvrTskTbl[channel].low = 0;
   osCp.drvrTskTbl[channel].high = 0;

   osCp.drvrTskTbl[channel].used = FALSE;
   osCp.numDrvrTsks--;
   if(SUnlock(&osCp.drvrTskTbl[channel].lock) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS477, ERRZERO,
                     "Could not unlock driver task lock");
#endif
      RETVALUE(RFAILED);
   }
   SDestroyLock(&osCp.drvrTskTbl[channel].lock);
   /* ss002.301 Modifications */
   RETVALUE(ROK);
}
#endif /* SS_DRVR_SUPPORT */
 


/********************************************************************30**
  
         End of file:     sm_drvr.c@@/main/1 - Mon Nov 17 15:54:34 2008
  
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

1.2          ---      kp   1. cosmetic changes, error codes regenerated
1.2+        ss029.103 kkj  1. Multiple proc ids support added
/main/1      ---      rp   1. SSI enhancements for Multi-core architecture
                               support
/main/1+    ss001.301 schandra1 1. Additions of Driver deregistration function
/main/1+    ss002.301 krkX      1. Fixed compilation warning unused variable 
*********************************************************************91*/
