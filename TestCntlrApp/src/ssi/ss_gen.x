

/********************************************************************20**
 
     Name:     System Services -- general
 
     Type:     C include file
 
     Desc:     Data structure definitions that are used by all
               implementations of system services.
 
     File:     ss_gen.x
 
     Sid:      ss_gen.x@@/main/4 - Mon Nov 17 15:54:16 2008
 
     Prg:      kp
 
*********************************************************************21*/


#ifndef __SSGENX__
#define __SSGENX__

#ifdef __cplusplus
extern "C" {
#endif

/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
typedef struct {
   U16 free;
   ProcId procId[SS_MAX_PROCS];
} ProcIdLst;
#endif /* SS_MULTIPLE_PROCS */

/* multi-core enhancements */
/*ss013.301 : changes for SS_AFFINITY_SUPPORT*/
#if defined(SS_MULTICORE_SUPPORT) || defined(SS_AFFINITY_SUPPORT)

typedef struct {
  SCpuInfo cpuInfo; /* the info about the cores/threads per core */


  /* the currently used core */
  U32 currentCore;
  
  /*COMMENT: add the thread id for use on hyperthreading machines */
  struct {
    U32 thrs;                     /* available no. of threads per core */
    S8 exclusive;                 /* exclusive flag */
    SSTskId tskPerCoreLst[SS_MAX_THREADS_PER_CORE]; /* System tasks running on this core */
  } coreInfo[SS_MAX_CORES];
} SMultiCoreInfo;
#endif /* SS_MULTICORE_SUPPORT || SS_AFFINITY_SUPPORT */

/* ss001.301: additions */
/* ss002.301: Modifications */
#ifdef SS_THREAD_PROFILE
#ifdef SS_MULTIPLE_PROCS
EXTERN S16 SGetThrdProf(SSTskId *sTskId,ProcId procId,Ent ent,Inst inst,Event *curEvent,U32 *curEvtTime,U64 *totTime);
#else
EXTERN S16 SGetThrdProf(SSTskId *sTskId,Ent ent,Inst inst,Event *curEvent,U32 *curEvtTime,U64 *totTime);
#endif /* SS_MULTIPLE_PROCS */
#endif /* SS_THERAD_PROFILE */

#ifdef SS_WATCHDOG

typedef void (*WdUserCallback)(void *);

typedef struct {
#ifdef SS_WATCHDOG_IPV6
   struct in6_addr  addr;
#else
   struct in_addr addr;       /* configured node addr */
#endif /* SS_WATCHDOG_IPV6 */
   U16 port;       /* configured watchdog port */
   U8 status;      /* HB ACK status */
} watchDogStatus;

typedef struct ssWd {
   U32            timeout;                 /* configured HB timer */
   U8             watchdogStop;            /* watchdog stop flag */
   int            numNodes;                /* configured nodes */
#ifdef SS_WIN
   unsigned int   sock;                    /* HB socket descriptor */
#else
   int            sock;
#endif /* SS_WIN */

   watchDogStatus wdsta[SS_MAX_WD_NODES];  /* node config or status */
   WdUserCallback callback;                /* user callback */
   void           *data;                   /* user callback data */
} SsWd;

typedef struct ssWdCp{
   SSTskId               watchDgTskId;
   SSTskId               watchDgRcvrTskId;
   Pst                   watchDgPst;
   CmTqCp                watchDgTqCp;  /* timing queue control point : WatchDog */
   CmTqType              watchDgTs[2]; /*timing queue */ 
   CmTimer               watchDgTmr[2];         
   ProcId                watchDgprocId;
   SsWd                  globWd;
   SLockId               wdLock;
} SsWdCp;
EXTERN S16 SInitWatchdog(U16 port);
EXTERN S16 SRegCfgWd(U32 numNodes, U8 *addr[], U16 port[], U32 timeout, WdUserCallback callback, void *data);
EXTERN S16 SDeregCfgWd(void);
EXTERN S16 SStartHrtBt(U8 timeInterval);
EXTERN S16 SStopHrtBt(void);
#endif /* SS_WATCHDOG */

#ifdef SS_LOGGER_SUPPORT
/* Logger Info */
typedef struct sloggerInfo
{
     Bool            started;      /* flag to indicate logger status */

     Bool            configured;   /* flag to indicate whether logger is configured */

     Bool            opt;               /* write to file/socket based on the flags provided*/      
   
     FILE*           filep;
     S8              filePath[SS_MAX_PATH];
   
     S32             socketdes;
     struct sockaddr_in remoteAddr;
   
     U16             curNumFlush;
     U16             maxNumFlush;
     
     S8              buffer[SS_MAX_LOGBUF_SIZE];
     U32             maxBufSiz;        /*The size of this is determined by the 
                                            system on which its running.*/
     U32             curBufSiz;
     SLockId         bufLock;            /* lock for global buffer access */
} SLoggerInfo;
#endif /*  SS_LOGGER_SUPPORT  */

/* SS control point */
typedef struct ssos
{
   
   SsdOs                dep;                    /* implementation specific */

/* ss029.103: modification: 
   with multiple procId support, SSI shall keep list of registered procIds  */
#ifndef SS_MULTIPLE_PROCS
   ProcId               procId;                 /* processor ID */

    /* TAPA task info */
   SsIdx                tTskIds[SS_MAX_ENT][SS_MAX_INST];
#else
   ProcIdLst            procLst;                /* processor ID list */
   SsIdx                tTskIds[SS_MAX_PROCS][SS_MAX_ENT][SS_MAX_INST];
   /* TAPA task info */
#endif /* SS_MULTIPLE_PROCS */
                                               /* index table */
   SsTTskEntry          tTskTbl[SS_MAX_TTSKS];  /* task table */
   SsCntr               numTTsks;               /* count of tasks */
   SsIdx                nxtTTskEntry;           /* next available slot */

   SsSemaId             tTskTblSem;             /* lock for table access */


   /* system task info */
   SsSTskEntry          sTskTbl[SS_MAX_STSKS];  /* task table */
   SsCntr               numSTsks;               /* count of tasks */
   SsIdx                nxtSTskEntry;           /* next available slot */

   SLockId              sTskTblLock;            /* lock for table access */


   U8                   dmndQLookupTbl[256];    /* demand queue lookup table */


#ifdef SS_DRVR_SUPPORT

   /* driver task info */
   SsDrvrTskEntry       drvrTskTbl[SS_MAX_DRVRTSKS];
                                                /* task table */
   SsCntr               numDrvrTsks;            /* count of tasks */

#endif  /* SS_DRVR_SUPPORT */


#ifdef SS_RTR_SUPPORT

   /* router task info */
   ActvTsk              rtrTskTbl[SS_MAX_RTRTSKS];
   SLockId              rtrTskLocks[SS_MAX_RTRTSKS];

#endif  /* SS_RTR_SUPPORT */


   /* timer info */
   SsTmrEntry           tmrTbl[SS_MAX_TMRS];    /* timer table */
   SsCntr               numTmrs;                /* count of timers */
   SsIdx                nxtTmrEntry;            /* next available slot */

   SLockId              tmrTblLock;             /* lock for table access */


   /* memory info */
   SsRegionEntry        regionTbl[SS_MAX_REGS]; /* region table */
   SsCntr               numRegions;             /* count of regions */

   SsSemaId             regionTblSem;           /* lock for table access */

   /* ss028.103 - Addition of lock for mBuf reference count */
	/* ss007.301 - moved the lock to RegionTbl */
   /* SLockId              mBufRefLock; */            /* lock for mBuf ref access */

/*ss013.301 : changes for SS_AFFINITY_SUPPORT*/
#if defined(SS_MULTICORE_SUPPORT) || defined(SS_AFFINITY_SUPPORT)
   /* the Information about the CPU */
   SMultiCoreInfo mCInfo;

   SLockId mCILock;                             /* Lock for mCInfo access */

#endif /* SS_MULTICORE_SUPPORT || SS_AFFINITY_SUPPORT */

/* ss001.301: additions */
#ifdef SS_WATCHDOG 
   SsWdCp                wdCp;
#endif /* SS_WATCHDOG */

#ifdef SS_HISTOGRAM_SUPPORT
   U8                    entId[26][26];
#endif /* SS_HISTOGRAM_SUPPORT */

#ifdef SS_LOGGER_SUPPORT
 SLoggerInfo logger;
#endif /*  SS_LOGGER_SUPPORT  */

} SsOs;



/* configuration data structures */

/* pool configuration */
typedef struct ssPoolCfg
{
   SsPoolType   type;                   /* dynamic or static */
   Size         size;                   /* size to use (for dynamic pools) */

} SsPoolCfg;


/* region content--pools in a region */
typedef struct ssRegCfg
{
   Region       region;                      /* region ID */
   SsCntr       numPools;                    /* count of pools */
   SsPoolCfg    pools[SS_MAX_POOLS_PER_REG]; /* pools configuration */

} SsRegCfg;



/* external variable declaration */
/*ss014.301  EXTERN osCp as VOLATILE for SSI-4GMX*/
#ifdef  SS_4GMX_LCORE
EXTERN VOLATILE SsOs osCp;
#else
EXTERN SsOs osCp;
#endif


/* functions */
EXTERN S16 SInit ARGS((void));
/*ss009.301*/
EXTERN S16 SFini ARGS((void));
/* ss034.103 */
EXTERN S16 SDeInit ARGS((void));

/* implementation-specific functions */
EXTERN S16 ssdInitGen ARGS((void));
EXTERN S16 ssdInitMem ARGS((void));
EXTERN S16 ssdInitTsk ARGS((void));
EXTERN S16 ssdInitDrvr ARGS((void));
EXTERN S16 ssdInitTmr ARGS((void));
/* ss005.301: ssdInitFinal changed to ssdInitLog */
EXTERN S16 ssdInitLog ARGS((void));

EXTERN Void ssdDeinitGen ARGS((void));
EXTERN Void ssdDeinitMem ARGS((void));
EXTERN Void ssdDeinitTsk ARGS((void));
EXTERN Void ssdDeinitDrvr ARGS((void));
EXTERN Void ssdDeinitTmr ARGS((void));
/* ss005.301: ssdDeinitFinal changed to ssdDeinitLog */
EXTERN Void ssdDeinitLog ARGS((void));

EXTERN Void ssdStart ARGS((void));

EXTERN S16 ssdAttachTTsk ARGS((SsTTskEntry *));
EXTERN S16 ssdDetachTTsk ARGS((SsTTskEntry *));
EXTERN S16 ssdCreateSTsk ARGS((SsSTskEntry *));
EXTERN S16 ssdDestroySTsk ARGS((SsSTskEntry *));
EXTERN S16 ssdPstTsk ARGS((Pst *, Buffer *, SsTTskEntry *));
EXTERN S16 ssdRegTmr ARGS((SsTmrEntry *));
EXTERN S16 ssdDeregTmr ARGS((SsTmrEntry *));
EXTERN S16 ssdError ARGS((Seq, Reason));
EXTERN Void ssdLogError ARGS((Ent, Inst, ProcId, Txt *, S32, \
                              ErrCls, ErrCode, ErrVal, Txt *));
/*
 * SDeRegTTsk patch
 */
/* for TTask Dereg */
#ifdef SS_MULTIPLE_PROCS
EXTERN S16 ssdProcTTskTerm ARGS((ProcId proc, SsTTskEntry *tTsk, SsIdx idx));
#else
EXTERN S16 ssdProcTTskTerm ARGS((SsTTskEntry *tTsk, SsIdx idx));
#endif /* SS_MULTIPLE_PROCS */

#ifdef SS_DRVR_SUPPORT
EXTERN S16 ssdRegDrvrTsk ARGS((SsDrvrTskEntry *));
/*ss001.301: Additions */
EXTERN S16 ssdDeregDrvrTsk ARGS((SsDrvrTskEntry *));
#endif

/* ss029.103: addition: support function to implement multiple procIds */ 
#ifdef SS_MULTIPLE_PROCS
EXTERN U16 SGetProcIdIdx ARGS((ProcId proc));
#endif /* SS_MULTIPLE_PROCS */

/* multi-core support */
/*ss013.301 : changes for SS_AFFINITY_SUPPORT*/
#if defined(SS_MULTICORE_SUPPORT) || defined(SS_AFFINITY_SUPPORT)
 
EXTERN S16 ssdSetAffinity ARGS((SSTskId *tskId, U32 coreId));
EXTERN S16 ssdGetAffinity ARGS((SSTskId *tskId, U32 *coreId));
#endif /* SS_MULTICORE_SUPPORT || SS_AFFINITY_SUPPORT */

/* ss001.301: additions */
#ifdef SS_LOGGER_SUPPORT 
EXTERN S16 ssdInitLogger ARGS((void));
EXTERN S16 SFlushBufToLog ARGS (( S8 *logBuf));
/* ss02.301: additions */
EXTERN S16 SCleanUp ARGS ((Void ));
EXTERN Void SStartLogger ARGS ((Void ));
EXTERN Void SStopLogger ARGS ((Void ));
#endif /* SS_LOGGER_SUPPORT  */
/* ss02.301: additions */
#ifdef SS_WATCHDOG 
#ifdef SS_MULTIPLE_PROCS
EXTERN S16 ssdWatchDgActvTmr ARGS(( ProcId proc, Ent ent, Inst instVoid));
#else
EXTERN S16 ssdWatchDgActvTmr ARGS(( Void ));
#endif /* SS_MULTIPLE_PROCS */
EXTERN Void ssdWatchDgTmrEvt ARGS(( PTR cb, S16 event ));
EXTERN S16 watchDgActvTsk ARGS(( Pst *pst, Buffer *mBuf));
EXTERN S16 watchDgRcvrActvTsk ARGS(( Pst *pst, Buffer *mBuf ));
EXTERN S16 ssdSndHrtBtMsg ARGS(( Bool  restart, U32 type));
EXTERN Void ssdStartWatchDgTmr ARGS(( void *cb, S16 event, U16 wait));
EXTERN Void ssdStopWatchDgTmr ARGS(( void *cb, S16 event));
EXTERN S16 ssdInitWatchDgPst ARGS((Pst *pst)); 	
EXTERN S16 ssdInitWatchDog ARGS((U16 port));
#endif

#ifdef SS_FBSED_TSK_REG
EXTERN S16 SRegTskInfo ARGS((U8 *cfgFile));  
#endif
/* ss002.301 Readwrite lock additions */
#ifdef SS_LOCK_SUPPORT
EXTERN S16 ssdLockNew ARGS((SLockInfo *LockId, U8 locktype));
EXTERN S16 ssdInitLockNew ARGS((SLockInfo *LockId, U8 lockType));
EXTERN S16 ssdUnlockNew ARGS((SLockInfo *LockId, U8 lockType));
EXTERN S16 ssdDestroyLockNew ARGS((SLockInfo *LockId, U8 lockType));
#endif /* SS_LOCK_SUPPORT */
#ifdef __cplusplus
}
#endif

#endif  /*  __SSGENX__  */



/********************************************************************30**
 
         End of file:     ss_gen.x@@/main/4 - Mon Nov 17 15:54:16 2008
 
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

1.2          ---      bsr  1. moved lock types to ssi.h
             ---      bsr  2. Added prototypes for ssdDeinit* functions 
             ---      kp   1. Prototype for ssdPstTsk added

1.3          ---      kp   1. Added in Message Router support
1.3+        ss028.103 bjp  1. Addition of lock for mBuf reference count
1.3+        ss029.103 kkj  1. Multiple proc ids support added
1.3+        ss034.103 pdb  1. Prototype for SDeInit API is added.
/main/4      ---      rp   1. SSI enhancements for Multi-core architecture
                              support
/main/4+    ss001.301 schandra1 1. SSI phase-2 value added feature additions
/main/4+    ss002.301 prasanna  1. SDeRegTTsk fix
                      pmacharla 2. Moved SS_LOGGER declarions to here
                                3. SS_WATCHDOG declarions to here
                                4. BIT_64 flag has been removed for thread profiling
                      rss       1. Readwrite lock added
/main/4+    ss005.301 pmacharla 1. ssdInitLog changed to ssdInitLog
                                2. ssdDeinitFinal changed to ssdDeinitLog
/main/4+    ss007.301 pmacharla 1. mBufRefLock moved to RegionTable
/main/4+    ss009.301 ssahniX   1. Prototype for SFini API is added
/main/4+    ss013.301 ssahniX   1. Added SS_AFFINITY_SUPPORT
/main/4+    ss014.301 ssahniX   1. EXTERN osCp as VOLATILE for SSI-4GMX
*********************************************************************91*/
