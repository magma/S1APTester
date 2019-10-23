

/********************************************************************20**
 
     Name:     MTSS -- implementation specific definitions
 
     Type:     C include file
 
     Desc:     Various macro definitions demanded by systems services.
               The contents of these are for the MTSS implementation.
 
     File:     mt_ss.h
 
     Sid:      mt_ss.h@@/main/2 - Mon Nov 17 15:54:12 2008
 
     Prg:      kp
 
*********************************************************************21*/


#ifndef __MTSSH__
#define __MTSSH__


/* --- interface to SS --- */

/* general */
#define SS_PROC_ID                      PID_STK(1)

/* task related */
/* mt028.201: addition: multiple procs support related changes */
#ifdef SS_MULTIPLE_PROCS
#define SS_MAX_PROCS                    100 /* max entries for proc list */
#endif /* SS_MULTIPLE_PROCS */

#define SS_MAX_ENT                      255
#define SS_MAX_INST                     8

/* mt028.201: modification: multiple procs support related changes */
#ifndef SS_MULTIPLE_PROCS
#define SS_MAX_TTSKS                    30

#ifndef SS_MULTICORE_SUPPORT
#define SS_MAX_STSKS                    30
#else
/* mt001.301 : Additions */
#define SS_MAX_STSKS                    30 
#endif /* SS_MULTICORE_SUPPORT */

#else /* SS_MULTIPLE_PROCS */
#define SS_MAX_TTSKS                    1000 
#define SS_MAX_STSKS                    30
#endif /* SS_MULTIPLE_PROCS */

#ifdef SS_DRVR_SUPPORT
#define SS_MAX_DRVRTSKS                 70
#endif

#ifdef SS_RTR_SUPPORT
   /* mt0012.21 : Addition */
#define SS_MAX_RTRTSKS                  255
#endif


/* timer related */
#define SS_MAX_TMRS                     45

/* memory related */
/* mt022.201 - Modification for shared memory relay and memcal regions */
#if (defined(RY_ENBS5SHM) && defined(USE_MEMCAL))
#define SS_MAX_REGS			3
#define RY_SHM_REGION			(SS_MAX_REGS - 2)
#define SS_STATIC_REGION		(SS_MAX_REGS - 1)
#else

#if (defined(RY_ENBS5SHM) || defined(USE_MEMCAL))
#define SS_MAX_REGS			2
#ifdef RY_ENBS5SHM
#define RY_SHM_REGION			(SS_MAX_REGS - 1)
#endif
#ifdef USE_MEMCAL
#define SS_STATIC_REGION		(SS_MAX_REGS - 1)
#endif
#else
#ifndef SS_MULTICORE_SUPPORT
/*mt004.301-changed no of regioni for FAP*/
#ifndef SS_FAP
#define SS_MAX_REGS			1
#else
#define SS_MAX_REGS			2
#endif
#else
#define SS_MAX_REGS                    SS_MAX_STSKS 
#endif /* SS_MULTICORE_SUPPORT */
#endif
#endif

#ifdef CMM_MAX_BKT_ENT
#define SS_MAX_POOLS_PER_REG            CMM_MAX_BKT_ENT
#else
#define SS_MAX_POOLS_PER_REG            5
#endif
/* mt001.301 : Additions */
#ifdef SS_WATCHDOG 
#define ENTDW                           0xcd
#define ENTHB                           0xce
#define INST0                           0x00
#define SS_TMR_HRTBT                    0x00
#define EVTSSHRTBTREQ                   0x00
#define EVTSSHRTBTRSP                   0x01
#define SS_LOOSE_COUPLING               0x00
#endif /* SS_WATCHDOG */

/* locks */
#define SS_STSKTBL_LOCK                 SS_LOCK_MUTEX
#define SS_STSKENTRY_LOCK               SS_LOCK_MUTEX
#define SS_TMRTBL_LOCK                  SS_LOCK_MUTEX
#define SS_DMNDQ_LOCK                   SS_LOCK_MUTEX
#define SS_DRVRENTRY_LOCK               SS_LOCK_MUTEX
#define SS_RTRENTRY_LOCK                SS_LOCK_MUTEX


/* types needed by common SSI code */
#define SsSemaId                        sem_t
#define SLockId                         pthread_mutex_t


/* calls needed by common SSI code */
#define SInitLock(l, t)                 pthread_mutex_init(l, NULL)
#define SLock(l)                        pthread_mutex_lock(l)
#define SUnlock(l)                      pthread_mutex_unlock(l)
#define SDestroyLock(l)                 pthread_mutex_destroy(l)

#define ssInitSema(s, c)                sem_init(s, 0, c)
#define ssWaitSema(s)                   sem_wait(s)
#define ssPostSema(s)                   sem_post(s)
#define ssDestroySema(s)                sem_destroy(s)

#define SS_CHECK_CUR_STSK(t)            (pthread_equal(pthread_self(), \
                                          (t)->dep.tId))
 /* mt013.21: Addition */
#define SInitSemaphore(s, c)            sem_init(s, 0, c)
#define SWaitSemaphore(s)               sem_wait(s)                   
#define SPostSemaphore(s)               sem_post(s) 
#define SDestroySemaphore(s)            sem_destroy(s)
                
#define ssdPstTsk(p, m, t)

/* added SExit() for exiting process : mt017.21 */
/* mt001.301 : Additions */
#ifndef SS_LOGGER_SUPPORT 
#define SExit()                         exit(0)	
#else
#define SExit()  \
{ \
SCleanUp(); \
exit(0); \
}
#endif /* SS_LOGGER_SUPPORT  */

  /* mt007.21 addition */ 
/* calls needed by Message Functions */
#define SMemCpy(d,s,c)	memcpy(d,s,c)
#define SMemSet(s,c,n)  memset(s,c,n)
/* --- internal to MTSS-Solaris --- */


/*mt041.201 Value of MT_TICK_CNT changed*/
/*mt004.301- defining the MT_TICK_CNT in Micro seconds (usecs) */
/* mt010.301  Removed #ifdef SS_FAP portion and enabled oroginal code */
#define MT_TICK_CNT             (((U32)0x0F4240)/SS_TICKS_SEC)

#define MT_MAX_TICK_CNT_VAL     35
#define MT_MIN_TICK_CNT_VAL     1


/* interrupt service flags */
#define MT_IS_SET               0
#define MT_IS_UNSET             1
#define MT_IS_RESET             2

/******************************************************************
 mt018.201 - Memory Configuration. 

Memory block sizes and counts for memory manager configuration 
There is no restriction in the size of each block for the bucket.
However, it is recommended that the bucket size should be word aligned.
The CMM (Common Memory Manager) also create a look up table which map 
the size to the bucket index. 
The number of entry in the lookup table  (CMM_MAX_MAP_ENT, defined in
cm_mem.h) = ((maximum bucket size)/(bucket quantum size)) + 1. 
The CMM_MAX_MAP_ENT should be changed depending on the bucket sizes
that are configured below.
*******************************************************************/ 

/* Bucket 0 configuration */ 
/* mt032.201 changed  MT_BKT_0_DSIZE from 120 to 128 for 64k compilation */
#define MT_BKT_0_DSIZE          128
/*mt004.301-changed for FAP*/
#ifndef SS_FAP
#define MT_BKT_0_NUMBLKS        3500
#else
#define MT_BKT_0_NUMBLKS        10000
#endif

/* Bucket 1 configuration */ 
/*mt004.301-changed for FAP*/
#ifndef SS_FAP
#define MT_BKT_1_DSIZE          256
#define MT_BKT_1_NUMBLKS        10500
#else
/*mt010.301*/
#define MT_BKT_1_DSIZE          256
#define MT_BKT_1_NUMBLKS        2000
#endif

/* Bucket 2 configuration */ 
/*mt010.301*/
#ifdef SS_FAP
#define MT_BKT_2_DSIZE      1376      /* Fill in this value as required */ 
#define MT_BKT_2_NUMBLKS    4000        /* Fill in this value as required */ 
#else
#define MT_BKT_2_DSIZE 320
#define MT_BKT_2_NUMBLKS 1
#endif


/* Bucket 3 configuration */ 
/*mt010.301*/
#ifdef SS_FAP
#define MT_BKT_3_DSIZE     2592      /* Fill in this value as required */ 
#define MT_BKT_3_NUMBLKS   1500     /* Fill in this value as required */ 
#else
#define MT_BKT_3_DSIZE     640      /* Fill in this value as required */ 
#define MT_BKT_3_NUMBLKS   1        /* Fill in this value as required */ 
#endif


/*mt010.301*/
#ifdef SS_FAP
#define MT_MAX_BKTS             4
#else
#define MT_MAX_BKTS             2
#endif

/* mt029.201 corrected typos */
/* memory pool data size definitions for pool-to-size mapping table */
#define MT_POOL_3_DSIZE        (MT_BKT_3_DSIZE-(sizeof(SsMblk)+sizeof(SsDblk)))
#define MT_POOL_2_DSIZE        (MT_BKT_2_DSIZE-(sizeof(SsMblk)+sizeof(SsDblk)))
#define MT_POOL_1_DSIZE        (MT_BKT_1_DSIZE-(sizeof(SsMblk)+sizeof(SsDblk)))
#define MT_POOL_0_DSIZE        (MT_BKT_0_DSIZE-(sizeof(SsMblk)+sizeof(SsDblk)))

      

/* mt026.201 - Modification to increase default heap size */
/* memory size used for heap by the memory manager (2MB) */
/* mt001.301 : Additions */
/*mt004.301- changed heap size for FAP */
#ifdef SS_FAP
#define MT_HEAP_SIZE            5242880U 
#else
#define MT_HEAP_SIZE            4194304U 
#endif

#ifndef USE_MEMCAL
#define STATIC_MEM_CFG
#endif

/* mt022.201 - definition of MT_BKTQNSIZE */
/*mt010.301*/
#define MT_BKTQNSIZE 32


/* mt021.201 - Addition for setting stack size for threads */
/* Configuration for stack size (in bytes) of spawned threads
 * Size of zero gives default of 1 MB or 2 MB for 32 bit or 64 bit
 * compilers, respectively */
#define MT_TASK_STACK		NULLD	/* stack size for task handler */
#define MT_ISTASK_STACK		NULLD	/* stack size for IS task handler */
#define MT_TMRTASK_STACK	NULLD	/* stack size for timer handler */
#define MT_CONSOLE_STACK	NULLD	/* stack size for console handler */

/* mt001.301 : Additions Logger support */ 
#ifdef SS_LOGGER_SUPPORT
#ifndef SS_MAX_LOGBUF_SIZE
#define SS_MAX_LOGBUF_SIZE 8192
#endif
#ifndef SS_MAX_PATH
#define SS_MAX_PATH 1024
#endif
#endif /* SS_LOGGER_SUPPORT */
/* mt005.301: Cavium changes: */
#ifdef SS_SEUM_CAVIUM
/* Cavium related hashdefines */
#define SS_CVMX_GRP_MASK   (1 << osCp.procId)

#define SS_CVMX_NUM_PKT_BUFFERS   0
#define SS_CVMX_NUM_WQE_BUFFERS   100
#define SS_CVMX_NUM_PKO_BUFFERS   0
#define SS_CVMX_NUM_TIM_BUFFERS   1000
#define SS_CVMX_NUM_DFA_BUFFERS   0

/* fpa pool 0 configuration */
#define SS_CVMX_POOL_0_NUMBLKS        3000

/* fpa pool 1 configuration */
#define SS_CVMX_POOL_1_NUMBLKS        100

/* fpa pool 2 configuration */
#define SS_CVMX_POOL_2_NUMBLKS        10        /* Fill in this value as required */ 

/* fpa pool 3 configuration */
#define SS_CVMX_POOL_3_NUMBLKS        2500      /* Fill in this value as required */ 

#define SS_CVMX_TICK_TIME   1000  /* the value is in micorsec */
#define SS_CVMX_MAX_TICKS   1000
#define SS_CVMX_TICKS       500

#define SS_CVMX_TMR_TAG     1000
#define SS_CVMX_MBUF_TAG    1001
#endif /* SS_SEUM_CAVIUM */

/* mt011.301: Pool definition for both 64 bit and 32 bit Cavium */
#ifndef SS_CVMX_WQE_POOL
#ifdef BIT_64
#define SS_CVMX_WQE_POOL CVMX_FPA_WQE_POOL
#else
#define SS_CVMX_WQE_POOL SS_CVMX_POOL_0
#endif
#endif

#endif  /*  __MTSSH__  */


  
/********************************************************************30**

         End of file:     mt_ss.h@@/main/2 - Mon Nov 17 15:54:12 2008

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
1.1          ---      kp   1. MTSS-Solaris release 2.1

1.1+         ---      ada  1. Changed common memory bucket size to
                              improve efficiency  

            mt007.21  jn   2. Defined Macros SMemCpy & SMemSet for
                              multiple byte copy
            mt012.21  jn   3. Defined the macro SS_MAX_RTRTSTS to 255
            mt013.21  jn   4. Defined the following macros:
                              SInitSemaphore,
                              SWaitSemaphore,
                              SPostSemaphore,
                              SDestroySemaphore. 
            mt014.21  jn   5. Corrected the typo in Macro definition for
                              SDestroySemaphore
            mt015.21  ada  6. Changed SS_MAX_TMRS from 15 to 45
                      ada  7. Changes to code to run on Linux
            mt016.21  ada  7. Increased MT_DBUF_NMB_BUFS and MT_HEAP_SIZE
                              to work with H.323 acceptance test
	    mt017.21  bdu  8. Added SExit() for exiting use		      
           mt018.201  bdu  9. Remove several macro defines, and change
                              the name of some macros.
           mt021.201  bjp 10. Added macro definition for stack sizes
	   mt022.201  bjp 11. Modifications for shared memory relay
	                      Modifications for memory calculation tool
1.1+  mt026.201  bjp  1. Modification to increase default heap size
1.1+  mt027.201  bjp  1. Modification for SRegCfgTmr support
2.1+  mt028.201  kkj  1. Support of multiple procs added
      mt029.201 bn    2. corrected typose in memory calculation.
      mt031.201 bn    1. changed  MT_BKT_0_DSIZE from 80 to 120 for 64k 
                         compilation 
      mt032.201 bn    2. changed  MT_BKT_0_DSIZE from 120 to 128 for 64k 
                         compilation 
2.1+  mt041.201 ch    1. MT_TICK_CNT value changed.
/main/2      ---        rp    1. SSI enhancements for Multi-core architecture support
/main/2+   mt001.301 schandra1  1. SSI Phase 2 Value added feature additions
/main/2+   mt004.301 akulkarni  1. Changed bucket configuration for FAP
                                2. Changed no of region for FAP
/main/2+   mt005.301 pmacharla 1. Cavium user mode related changes
/main/2+   mt010.301 akulkarni 1. Removed #ifdef SS_FAP portion and enabled oroginal code
                               2. Configuration changes W.R.T. FAP 
/main/2+   mt011.301 rk        1. Cavium 32 bit changes
*********************************************************************91*/
