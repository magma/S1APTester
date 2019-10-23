
/********************************************************************20**

     Name:     common functions - 5

     Type:     C source file

     Desc:     C source code for common timer routines;

     File:     cm_bdy5.c

     Sid:      cm_bdy5.c@@/main/21 - Wed Feb 10 20:04:21 2010

     Prg:      na

*********************************************************************21*/


/* header include files -- defines (.h) */

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common functions */

/* header/extern include files (.x) */

#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm5.x"           /* common functions */


/* local defines */

#define CM_RMV_TQCP(tqEnt, tgt)                            \
{                                                          \
   ((tgt)->prev) ? ((tgt)->prev->next = (tgt)->next):      \
                  ((tqEnt)->first = (tgt)->next);          \
   ((tgt)->next) ? ((tgt)->next->prev = (tgt)->prev):      \
                  ((tqEnt)->tail = (tgt)->prev);           \
   (tgt)->prev = NULLP;                                    \
   (tgt)->next = NULLP;                                    \
   (tgt)->ent2bUpd = FALSE;                                \
}
 
#define CM_PLC_TQCP(tqEnt, tgt)                            \
{                                                          \
   if ((tqEnt)->tail)                                      \
   {                                                       \
      (tqEnt)->tail->next = tgt;                           \
      (tgt)->prev = (tqEnt)->tail;                         \
      (tqEnt)->tail = tgt;                                 \
   }                                                       \
   else                                                    \
   {                                                       \
      (tqEnt)->first = (tqEnt)->tail = tgt;                \
   }                                                       \
}

/* local externs */

/* forward references */

/* functions in other modules */


/*
*
*       Fun:   cmPrcTmr
*
*       Desc:  Handle a timer entry
*
*       Ret:   RETVOID
*
*       Notes: 
*
*       File:  cm_bdy5.c
*
*/
 
#ifdef SS_FAP
#ifdef ANSI
PUBLIC Void cmPrcTmr
(
CmTqCp   *tqCp,          /* timing que control point */
CmTqType *tq,            /* timing queue */
PFV      func            /* function */
)
#else
PUBLIC Void cmPrcTmr(tqCp, tq, func)
CmTqCp   *tqCp;          /* connection control block */
CmTqType *tq;            /* message buffer */
PFV      func;           /* function */
#endif
{
/**/
   U32 expire;
   U32 entry;
   S16 event;
   PTR cb;
   CmTimer *tmp1;
   CmTimer **tmp2;
 
   TRC2(cmPrcTmr)

#ifdef CMDBG
{
   DateTime dt;
   Txt prntBuf[PRNTSZE];

   SGetDateTime(&dt);
   /* Here the year was being printed as 2 letter value and hence did
    * not represent accurate information.  It has been modified as
    * recommended to include the offset of year 1900 used in all Trillium
    * SSI implementations. Patch cmbdy5c_001.113
    */
   sprintf(prntBuf,"%s: date: %02d/%02d/%04d time: %02d:%02d:%02d\n",
           msArgv[0],dt.month,dt.day,(int)(dt.year + 1900), dt.hour,
           dt.min, dt.sec);
   SPrint(prntBuf);
}
#endif

   ++tqCp->nxtEnt;
   expire = tqCp->nxtEnt;
   /* cm_bdy5_c_002.113 - Modification for SRegCfgTmr support */
   entry = (U32) (expire % (U32)(tqCp->tmrLen));

   tmp2 = &tq[entry].first;
   while ((tmp1 = *tmp2) != NULLP)
   {
      if (tmp1->tqExpire == expire)
      {
         event = tmp1->tmrEvnt;
         cb = tmp1->cb;
         /* remove and reset this timer control block */
         (*tmp2) = tmp1->next;
         tmp1->tmrEvnt = TMR_NONE;
         tmp1->tqExpire = 0;
         tmp1->cb = NULLP;
         tmp1->next = NULLP;
         func(cb, event);
      }
      else
         tmp2 = &tmp1->next;
   }
   RETVOID;
} /* end of cmPrcTmr */

#else /* not defined SS_FAP */

#ifdef ANSI
PUBLIC Void cmPrcTmr
(
CmTqCp   *tqCp,          /* timing que control point */
CmTqType *tq,            /* timing queue */
PFV      func            /* function */
)
#else
PUBLIC Void cmPrcTmr(tqCp, tq, func)
CmTqCp   *tqCp;          /* connection control block */
CmTqType *tq;            /* message buffer */
PFV      func;           /* function */
#endif
{
/**/
   U32 expire;
   U32 entry, entry1;
   S16 event;
   CmTqType *tqEnt, *tqEnt1; 
   PTR cb;
   CmTimer *tmp1;
 
   TRC2(cmPrcTmr)
 
#ifdef CMDBG
{
   DateTime dt;
   Txt prntBuf[PRNTSZE];
 
   SGetDateTime(&dt);
   /* Here the year was being printed as 2 letter value and hence did
    * not represent accurate information.  It has been modified as
    * recommended to include the offset of year 1900 used in all Trillium
    * SSI implementations.
    */
   sprintf(prntBuf,"%s: date: %02d/%02d/%04d time: %02d:%02d:%02d\n",
           msArgv[0],dt.month,dt.day,(int)(dt.year + 1900), dt.hour, 
           dt.min, dt.sec);
   SPrint(prntBuf);
}
#endif
 
   ++tqCp->nxtEnt;
   expire = tqCp->nxtEnt;
   entry = (U32) (expire % (U32)(tqCp->tmrLen));
  
   tqCp->tmp = (tqEnt = &tq[entry])->first;
   while ((tmp1 = tqCp->tmp) != NULLP)
   {
      tqCp->tmp = tmp1->next;
 
      if ((tmp1->tqExpire == expire) || (tmp1->ent2bUpd))
      {
         event = tmp1->tmrEvnt;
         cb = tmp1->cb;
 
         if (!(tmp1->ent2bUpd))
         {
            CM_RMV_TQCP(tqEnt, tmp1);
 
            tmp1->tmrEvnt = TMR_NONE; 
            tmp1->tqExpire = 0;     
            tmp1->cb = NULLP;      
 
            func(cb, event);
         }
         else
         {
            entry1 = (U32) (tmp1->tqExpire % (U32)(tqCp->tmrLen));
            tqEnt1 = &tq[entry1];
            CM_RMV_TQCP(tqEnt, tmp1);
            tmp1->entIdx = entry1; 
            CM_PLC_TQCP(tqEnt1, tmp1);
         }
      }
   }
   RETVOID;
} /* end of cmPrcTmr */
#endif /* SS_FAP */



/*
*
*       Fun:   cmInitTimers
*
*       Desc:  initialize timers
*
*       Ret:   RETVOID
*
*       Notes: Connection Oriented Control
*
*       File:  cm_bdy5.c
*
*/
#ifdef ANSI
PUBLIC Void cmInitTimers
(
CmTimer *timers,     /* timer list */
U8 max               /* maximum tmrs */
)
#else
PUBLIC Void cmInitTimers(timers, max)
CmTimer *timers;     /* timer list */
U8 max;              /* maximum tmrs */
#endif
{
   CmTimer *tPtr;
   REG1 U8 i;

   TRC2(cmInitTimers)

   for (i = 0, tPtr = timers; i < max; i++, tPtr++)
   {
      tPtr->tmrEvnt = TMR_NONE;
      tPtr->tqExpire = 0;
      tPtr->cb = 0;
      tPtr->next = (struct cmTimer *)NULLP;
      tPtr->prev = (struct cmTimer *)NULLP;
      tPtr->ent2bUpd = FALSE;
   }
   RETVOID;
} /* end of cmInitTimers */

/*
*
*       Fun:    cmPlcCbTq
*
*       Desc:   Places Control Block on Timing Queue
*
*       Ret:    RETVOID
*
*       Notes:  None
*
*       File:   cm_bdy5.c
*
*/
  
#ifdef ANSI
PUBLIC Void cmPlcCbTq
(
CmTmrArg *arg
)
#else
PUBLIC Void cmPlcCbTq(arg)
CmTmrArg *arg;
#endif
{
/*added FAP modifications*/
#ifdef SS_FAP
   REG1 U8 tmrNum;
   /* cm_bdy5_c_001.main_20 - Modification for SRegCfgTmr support */
   U32 ent;
   U32 expire;
   CmTimer **tmp;

   TRC2(cmPlcCbTq)

   expire = (arg->tqCp->nxtEnt + arg->wait);
   /* cm_bdy5_c_002.113 - Modification for SRegCfgTmr support */
   ent = (U32)(expire % (U32)(arg->tqCp->tmrLen));

   for (tmrNum = 0; tmrNum < arg->max; tmrNum++)
   {
      if (arg->timers[tmrNum].tmrEvnt == TMR_NONE)
      {
         arg->timers[tmrNum].tmrEvnt = arg->evnt;
         arg->timers[tmrNum].tqExpire = expire;
         arg->timers[tmrNum].cb = arg->cb;
         arg->timers[tmrNum].next = NULLP;

         tmp = &(arg->tq[ent].first);
         while (*tmp)
            tmp = &((*tmp)->next);
         *tmp = &arg->timers[tmrNum];

         RETVOID;
      }
   }
   RETVOID;
#else
   REG1 U8 tmrNum;
   U32 ent;
   CmTqType *tq;
   CmTimer  *target;
   U32 expire;
 
   TRC2(cmPlcCbTq)
 
   expire = (arg->tqCp->nxtEnt + arg->wait);
   ent = (U32)(expire % (U32)(arg->tqCp->tmrLen));
 
   for (tmrNum = 0; tmrNum < arg->max; tmrNum++)
   {
      if (arg->timers[tmrNum].tmrEvnt == TMR_NONE)
      {
         target = &arg->timers[tmrNum];
         tq = &arg->tq[ent]; 
 
         target->tmrEvnt = arg->evnt;
         target->tqExpire = expire;
         target->cb = arg->cb;
         target->ent2bUpd = FALSE;
         target->entIdx   = ent;
 
         /* Place the timer block in the timer list */
         CM_PLC_TQCP(tq, target); 
 
         RETVOID;
      }
   }
   RETVOID;
#endif
} /* end of cmPlcCbTq */
 
/*
*
*       Fun:    cmRstCbTq
*
*       Desc:   Places Control Block on Timing Queue
*
*       Ret:    RETVOID
*
*       Notes:  None
*
*       File:   cm_bdy5.c
*
*/
  
#ifdef ANSI
PUBLIC Void cmRstCbTq
(
CmTmrArg *arg
)
#else
PUBLIC Void cmRstCbTq(arg)
CmTmrArg *arg;
#endif
{
   TRC2(cmRstCbTq)
 
   arg->timers[arg->tNum].tqExpire = arg->tqCp->nxtEnt + arg->wait;
   arg->timers[arg->tNum].ent2bUpd = TRUE; 
 
   RETVOID;
} /* end of cmRstCbTq */

/*
*
*       Fun:    cmRmvCbTq
*
*       Desc:   Removes control block from Timing Queue
*
*       Ret:    RETVOID
*
*       Notes:  None
*
*       File:   cm_bdy5.c
*
*/
  
#ifdef ANSI
PUBLIC Void cmRmvCbTq
(
CmTmrArg *arg
)
#else
PUBLIC Void cmRmvCbTq(arg)
CmTmrArg *arg;
#endif
{
/*Added FAP modifications*/
#ifdef SS_FAP
/* cm_bdy5_c_002.113 - Modification for SRegCfgTmr support */
   U32 ent;
   CmTimer *target;
   CmTimer *tmp1;
   CmTimer **tmp2;

   TRC2(cmRmvCbTq)

   target = &arg->timers[arg->tNum];
   if (target->tmrEvnt != TMR_NONE)
   {
      /* cm_bdy5_c_002.113 - Modification for SRegCfgTmr support */
      ent = (U32) (target->tqExpire % (U32)(arg->tqCp->tmrLen));
      tmp2 = &arg->tq[ent].first;

      while ((tmp1 = *tmp2) != NULLP)
      {
         if (tmp1 == target)
         {
            /* find the timer control block to be removed */
            (*tmp2) = tmp1->next;
            tmp1->tmrEvnt = TMR_NONE;
            tmp1->tqExpire = 0;
            tmp1->cb = NULLP;
            tmp1->next = NULLP;
            break;
         }
         else
            /* find the next timer control block */
            tmp2 = &tmp1->next;
      }
   }
   RETVOID;
#else
   U32 ent;
   CmTimer  *target;
   CmTqType *tq;
   
 
   TRC2(cmRmvCbTq)
 
   target = &arg->timers[arg->tNum];
   if (target->tmrEvnt != TMR_NONE)
   {
      ent = (U32) (target->entIdx);
      tq = &arg->tq[ent];
 
      /* 
       * Update the timer pointer in the for correct processing in
       * CmPrcTmr.
       */
      if (target == arg->tqCp->tmp)
         arg->tqCp->tmp = target->next;
 
      /* Remove the entru from the list */
      CM_RMV_TQCP( tq , target);
      target->tmrEvnt = TMR_NONE;
      target->tqExpire = 0;
      target->cb = NULLP;
 
   }
   RETVOID;
#endif
} /* end of cmRmvCbTq */
 


/********************************************************************30**
  
         End of file:     cm_bdy5.c@@/main/21 - Wed Feb 10 20:04:21 2010
   
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
 
  version    pat  init                   description
----------- ----- ----  ------------------------------------------------
1.1          ---  fmg   1. initial release

1.2          ---  fmg   1. fixed inconsistent use of Void/RETVOID
             ---  mc    1. replace (tqCp->tmrLen -1) with (tqCp->tmrLen)
                           when using % operator.
             ---  fmg   2. add ERRCHK to cmPlcCbTq
             ---  fmg   3. add CMDBG to cmPrcTmr

1.3          ---  mc    1. remove lm_pt.h and lm_pt.x include files.
             ---  mc    2. replace ss_pt.? and ss_ms.? with ssi.?.

1.4          ---  mc    1. change the order of include files ssi.[hx] and
                           gen.[hx].
1.5          ---  fmg   1. removed redundant function prototypes

1.6          ---  mc    1. declared event to be S16 in cmPrcTmr.

1.7          ---  rg    1. change cmPlcCbTq to add new timer to the end of
                           the list, to preserve order of expiry of timers.

1.8         ---   aa    1. Removed the checks for param inconsistency
                           and hence the SErrors. The caller of such 
                           functions now should ensure that it is not 
                           passing the bad value to the routines. 

1.9         ---   ada   1. In cmPrcTmr the next entry is increamented
                           *++tqCp->nxtEnt* and then used in *expire*

*********************************************************************81*/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.10         ---      bbk  1. Changed copyright header date.
  
1.12         ---      ada  1. Corrected file for chksrc utility

1.13         ---      kp   1. Removed include of cm_err.h, not
                              required

1.14         ---      tej  1. Changed copyright header date.
1.15         ---      rm   1. Implement doubly link list for managing timer 
                              blocks and new primitive for restarting timer.
             ---      rm   2. Uses temp timer pointer in TqCp, to traverse the
                              timer link list to be processed in cmPrcTmr.
                              This is done, to solve the problem of timer
                              block deletion consecutive to the current expired
                              timer in the expiry routine.
             ---      kpr  3. Fixed the Y2K problem in printing the year
                              value.
/main/17     ---    vt   1. 1ms timer related changes
/main/18     ---      st   1. Update for MAP Release 2.3
/main/19     ---      ad   1. Updated for Release SIP 2.2 Beta
/main/20     ---      ch   1. Updated copyright SSI Multicore Support release.
/main/21     ---      cm_bdy5_c_001.main_20      akulkarni 1. added functionality for cmPrcTmr.
*********************************************************************91*/
