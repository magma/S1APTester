
/********************************************************************20**
  
     Name:     common functions - 5
  
     Type:     C include file
  
     Desc:     Structures, variables and typedefs required for
               common timer routines
  
     File:     cm5.x
  
     Sid:      cm5.x@@/main/12 - Mon Nov 17 15:55:43 2008
  
     Prg:      na
  
*********************************************************************21*/

#ifndef __CM5X__
#define __CM5X__

#ifdef __cplusplus
extern "C" {
#endif


/* typedefs */

typedef struct cmTimer         /* timer structure */
{
   S16 tmrEvnt;                /* Timer Event */
   U32 tqExpire;               /* Timing Queue Expiry */
   PTR cb;                     /* Pointer to start of control block list */
   struct cmTimer *next;       /* Next item in the timing queue */
   struct cmTimer *prev;       /* Previous item in the timing queue */
   U8     ent2bUpd;            /* TRUE, if the timer block is not in the
                                  proper bin */
   U16   entIdx;                /* Current entry index */
} CmTimer;

typedef struct cmTqCp          /*  timing queue control point */
{
   U32 nxtEnt;                 /* next Entry */
   U32 tmrLen;                 /* length of timer (MODULO is -1) */
   CmTimer *tmp;               /* Temporary  variable used in cmPrcTmr */
} CmTqCp;

typedef struct cmTqType
{
   CmTimer *first;             /* First Entry */
   CmTimer *tail;              /* Last Entry */
} CmTqType;

typedef struct cmTmrArg
{
   CmTqCp     *tqCp;           /* timing queue control point */
   CmTqType   *tq;             /* timing queue point */
   CmTimer    *timers;         /* timers array */
   PTR        cb;              /* control block pointer */
   S16        evnt;            /* event */
   U32        wait;            /* wait */
   U8         tNum;            /* timer number */
   U8         max;             /* max timers */
} CmTmrArg;


/* trillium supplied functions */

typedef Void (*PFV) ARGS((PTR, S16));

extern Void cmInitTimers ARGS((CmTimer* timers, U8 max));
extern Void cmPlcCbTq ARGS((CmTmrArg* arg));
extern Void cmRmvCbTq ARGS((CmTmrArg* arg));
extern Void cmPrcTmr ARGS((CmTqCp* tqCp, CmTqType* tq, PFV func));
extern Void cmRstCbTq ARGS((CmTmrArg* arg));

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __CM3X__ */


/********************************************************************30**
  
         End of file:     cm5.x@@/main/12 - Mon Nov 17 15:55:43 2008
  
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
1.1          ---  fmg   1. initial release.

1.2          ---  mc    1. replace U8 with S16 in PFV function typedef.

1.3          ---  mc    1. changed tmrEvnt and event type from U8 to S16 
                           in cmTimer and cmTmrArg.

*********************************************************************81*/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.4          ---      bbk  1. Changed copyright header date.

1.5          ---      ns   1. Added extern "C" for making this file C++
                              compatible

1.6          ---      tej  1. Changed copyright header date.
1.7          ---      rm   1. Added new fields in CmTqCp and CmTqType for
                              the implementation of double link list timer list.
             ---      rm   2. Add a new parameter entIdx to CmTimer.
             ---      rm   3. Add prototype for cmRstCbTq
             ---      rm   4. Added a new parameter in CmTqCp for
                              timer list traversal in CmPrcTmr.
/main/9      ---      vt   1. Changes for 1 ms timer
/main/10     ---      st   1. Update for MAP Release 2.3
/main/11     ---      ad   1. Updated for Sip Release 2.2 Beta.
/main/12     ---      ch   1. Updated copyright SSI Multicore Support release.
*********************************************************************91*/
