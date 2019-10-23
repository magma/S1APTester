

/********************************************************************20**
 
     Name:     System Services -- general
 
     Type:     C include file
 
     Desc:     Macro definitions that are used by all implementations
               of system services.
 
     File:     ss_gen.h
 
     Sid:      ss_gen.h@@/main/4 - Mon Nov 17 15:54:16 2008
 
     Prg:      kp
 
*********************************************************************21*/


#ifndef __SSGENH__
#define __SSGENH__

#ifdef __cplusplus
extern "C" {
#endif

/* ss040.103: addition */
/* ss002.301 : errno.h is required for all */
#include <errno.h>   

/* the new driver support define */
#ifdef ENB_RELAY
#ifndef SS_DRVR_SUPPORT
#define SS_DRVR_SUPPORT
#endif
#endif



/* general */
#ifndef SS_PROC_ID
#error "SS_PROC_ID undefined!"
#endif

#ifndef SS_MAX_ENT
#error "SS_MAX_ENT undefined!"
#endif

#ifndef SS_MAX_INST
#error "SS_MAX_INST undefined!"
#endif


/* ss029.103: modification: the data type of array modified */ 
#ifndef SS_MULTIPLE_PROCS
#define SS_INVALID_IDX                  0xFF
#else /* SS_MULTIPLE_PROCS */
#define SS_INVALID_IDX                  0xFFFF
#endif /* SS_MULTIPLE_PROCS */


/* task related */
#ifndef SS_MAX_TTSKS
#error "SS_MAX_TTSKS undefined!"
#endif

#ifndef SS_MAX_STSKS
#error "SS_MAX_STSKS undefined!"
#endif

#ifdef SS_DRVR_SUPPORT
#ifndef SS_MAX_DRVRTSKS
#error "SS_MAX_DRVRTSKS undefined!"
#endif
#endif /* SS_DRVR_SUPPORT */

#ifdef SS_RTR_SUPPORT
#ifndef SS_MAX_RTRTSKS
#error "SS_MAX_RTRTSKS undefined!"
#endif
#endif /* SS_RTR_SUPPORT */

/* ss029.103: modification: the data type of array modified */ 
#ifndef SS_MULTIPLE_PROCS
#define SS_TSKNC                        0xFF
#else /* SS_MULTIPLE_PROCS */
#define SS_TSKNC                        0xFFFF
#endif /* SS_MULTIPLE_PROCS */


/* timer related */
#ifndef SS_MAX_TMRS
#error "SS_MAX_TMRS undefined!"
#endif



/* memory related */
#ifndef SS_MAX_REGS
#error "SS_MAX_REGS undefined!"
#endif

#ifndef SS_MAX_POOLS_PER_REG
#error "SS_MAX_POOLS_PER_REG undefined!"
#endif


/* event types */
#define SS_EVNT_DATA                    0
#define SS_EVNT_TIMER                   1
#define SS_EVNT_TERM                    2
#define SS_EVNT_PERMTICK                3
/*
 * SDeRegTTsk patch
 */
#define SS_EVNT_TTSK_TERM 					 4

/* ss001.301: SSI Phase 2 watchdog feature additions */
#ifdef SS_WATCHDOG 
#define SS_MAX_WD_NODES 256
#define SS_WD_HB_MSG_VER "1.0"
#define SS_WD_HB_REQ 0x0001
#define SS_WD_HB_RSP 0x0010
#define SS_WD_HB_MSG_SIZE 24
#define SS_WD_WDPORT 8888
#define SS_WD_WDPROC 99
#endif /* SS_WATCHDOG */

/* Logger support */
#ifdef SS_LOGGER_SUPPORT
#ifndef SS_MAX_LOGBUF_SIZE
#define SS_MAX_LOGBUF_SIZE 8192
#endif
#ifndef SS_MAX_PATH
#define SS_MAX_PATH 1024
#endif
#endif /* SS_LOGGER_SUPPORT */


/* object lock types */
#if (!defined(SS_STSKTBL_LOCK) \
        ||  !defined(SS_STSKENTRY_LOCK) \
        ||  !defined(SS_TMRTBL_LOCK) \
        ||  !defined(SS_DMNDQ_LOCK) \
        ||  !defined(SS_DRVRENTRY_LOCK) \
        ||  !defined(SS_RTRENTRY_LOCK))
#error "SS_?_LOCK undefined!"
#endif



   /* ss040.103 changed how ssWaitSema is called */
  /* ss013.13: addition */
/* locking macros */
/*ss014.301 SSI-4GMX specific changes*/    
#ifndef SS_4GMX_LCORE
#define SS_ACQUIRE_ALL_SEMA(s, ret) \
   { \
      S16 q; \
      ret = ROK; \
      for (q = 0;  q < SS_MAX_STSKS;  q++) \
      { \
         while ((ret = ssWaitSema(s) != ROK) && (errno == EINTR)) \
            continue; \
         if ( ret != ROK)\
         {\
             SSLOGERROR(ERRCLS_DEBUG, ESSXXX, ERRZERO,\
                        "Could not lock the Semaphore");\
         }\
         if (ret != ROK) \
         { \
            while (q > 0) \
            { \
               ret = ssPostSema(s); \
               if ( ret != ROK)\
               {\
                   SSLOGERROR(ERRCLS_DEBUG, ESSXXX, ERRZERO,\
                           "Could not unlock the Semaphore");\
               }\
               q--; \
            } \
            break; \
         } \
      } \
      if (q == 0) \
         ret = RFAILED; \
   }


  /* ss006.13: addition */
#define SS_RELEASE_ALL_SEMA(s) \
   { \
      S16 q; \
      for (q = 0;  q < SS_MAX_STSKS;  q++) \
      {\
         if ( (ssPostSema(s)) != ROK)\
         {\
            SSLOGERROR(ERRCLS_DEBUG, ESSXXX, ERRZERO,\
                         "Could not unlock the Semaphore");\
            RETVALUE(RFAILED);\
         }\
      }\
   }

/* ss040.103 changed how ssWaitSema is called */
#define SS_ACQUIRE_SEMA(s, ret) \
   while ((ret = ssWaitSema(s) != ROK) && (errno == EINTR)) \
      continue;\
/* ss041.103 removed exta lines */



  /* ss006.13: addition */
#define SS_RELEASE_SEMA(s) \
   ssPostSema(s)

/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
#define SS_INV_PROCID_IDX 0xFFFF /* invalid index in procId table */
#define SS_INV_PROCID     0xFFFF /* invalid proc id */ 

#define SS_HASH_IDX(_proc) (_proc % SS_MAX_PROCS)

#endif /* SS_MULTIPLE_PROCS */
#else
#define SS_ACQUIRE_ALL_SEMA(s, ret) \
   { \
      ret = ssWaitSema(s); \
   }


#define SS_RELEASE_ALL_SEMA(s) \
   { \
         ssPostSema(s);\
   }

#define SS_ACQUIRE_SEMA(s, ret) \
      ret = ssWaitSema(s)

#define SS_RELEASE_SEMA(s) \
   ssPostSema(s)
#endif  /* SS_4GMX_LCORE  */

#ifdef __cplusplus
}
#endif

#endif  /*  __SSGENH__  */



/********************************************************************30**
 
         End of file:     ss_gen.h@@/main/4 - Mon Nov 17 15:54:16 2008
 
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
  
1.2          ---      ag   1. Moved Lock types to ssi.h
             ---      bsr  2. Deleted reference to variable ret in 
                              SS_RELEASE_ALL_SEMA and q in SS_RELEASE_SEMA
             ---      kp   3. Added check for SS_PROC_ID definition

1.3          ---      kp   1. Added in Message Router support
1.3+        ss006.13  jn   2. Removed compile warning
1.3+        ss013.13  jn   2. Corrected the error introduced in the patch
                              ss006.13 for SS_ACQUIRE_ALL_SEMA. If there
                              is failure in the ssWaitSema, the ssPostSema
                              was not being called. This has been corrected.
1.3+        ss029.103 kkj  1. Multiple proc ids support added
1.3+        ss040.103 bn   1.  changed how ssWaitSema is called
1.3+        ss041.103 bn   1.  removed extra lines from SS_ACQUIRE_SEMA
/main/4      ---       rp   1. SSI enhancements for Multi-core architecture
                              support
/main/4+    ss001.301 schandra1 1. SSI Ph2 value added feature additions
/main/4+    ss002.301 prasanna  SDeRegTTsk fix
                      pmacharla errno.h is required for all platforms
							           as we are using EINTR
/main/4+    ss014.301 ssahniX   1 Changed SS_ACQUIRE_SEMA SS_ACQUIRE_ALL_SEMA
                                 SS_RELEASE_SEMA SS_RELEASE_ALL_SEMA for SSI-4GMX 
*********************************************************************91*/
