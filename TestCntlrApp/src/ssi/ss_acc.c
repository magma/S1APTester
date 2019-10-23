


/********************************************************************20**
  
     Name:     System Services -- acceptance test
  
     Type:     C source file
  
     Desc:     Positive Acceptance Tests
 
     File:     ss_acc.c

     Sid:      ss_acc.c@@/main/3 - Mon Nov 17 15:54:12 2008
  
     Prg:      ag
  
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
 /* ss017.13: addition */
#ifdef SS_LINUX
#include <sys/time.h>
/*ss013.301: Fixed Warnings for 32/64 bit compilation*/
#include <unistd.h>
#endif

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


/* local defines */

#define PERMENT1     5
#define PERMENT2     6
#define MAXTSTCNT    0
#define TSTTIMES     10         /* number of test for certain function */
#define BSIZE        100
#define MAXMSGLEN    256        /* maximum message length */
#define MAXSMEMLEN   0x20       /* maximum static memory length */
#define TSK1TMR      10
#define TSK2TMR      100
#define NMBTMRTSKS   2
#define TSKCNT       1000
/* ss036.103 - addition of macros for header size and heap block & header */
#ifdef SSI_DEBUG_LEVEL1
#define BKTMEMBLKHDRSIZE   16  /* size of the mem blk header in bucket */
#define HEAPMEMBLKHDRSIZE  20  /* size of the mem blk header in heap */
#define HEAPMEMSAMPLESIZE  280 /* set this higher to max bkt blk size */
#endif /* SSI_DEBUG_LEVEL1 */

/* ss029.103: modification: multiple proc ids related modifications */
#ifdef SS_MULTIPLE_PROCS
#define SFndProcId() PROC_MP_ID0
#endif /* SS_MULTIPLE_PROCS */

/* local typedefs */
typedef struct tstCp
{
   S32 tskCnt[SS_MAX_TTSKS];    /* individual tsk count */
   S32 tstCnt;                  /* tst count */

} TstCp;


#ifdef SS_SINGLE_THREADED

#define TST0ENT      ENTSS+ 1  /* test 0 entity */
#define TST1ENT      ENTSS+ 2  /* test 1 entity */
#define TST2ENT      ENTSS+ 3  /* test 2 entity */
#define TSTPERMENT   ENTSS+ 4  /* test permanent entity */
#define TSTINST0     0         /* test instance 0 */
#define TSTINST1     1         /* test instance 1 */

#define SMSTASID     0
#define SMSTASPOOL   1
#define SMSTADPOOL   2
#define SMSTADQ      3
#define SMSTAENT     4
#define SMSTSLOOP    5
#define SMSTSDQ      6
#define SMSTSENT     7
#define NMBPRIOR     1

#define NMBTSKS      4
#define TST3ENT      ENTSS + 5  /* test 3 entity */
Route rte[5];

/* ss019.103 - Addition SS_SINGLE_THREADED */
#else
#define TST0ENT      ENTSS+ 1  /* test 0 entity */
#define TSTINST0     0         /* test instance 0 */
#define TSTINST1     1         /* test instance 1 */
#define TSTINST2     2         /* test instance 2 */
#define TSTINST3     3         /* test instance 3 */
#define TSTINST4     4         /* test instance 4 */
#define TSTINST5     5         /* test instance 5 */

SSTskId sTskId[5];
S16 ACKCount;
#endif /* SS_SINGLE_THREADED */

/* ss029.103: modification: multiple proc ids related modifications */
#ifdef SS_MULTIPLE_PROCS

/* tapa tasks */
#define TST_MP_TTSKS 10

/* proc Ids */
#define PROC_MP_ID0 1000

/* entity ids */
#define ENT_MP_0   100
#define ENT_MP_1   101
#define ENT_MP_2   102
#define ENT_MP_3   103
#define ENT_MP_4   104
#define ENT_MP_5   105
#define ENT_MP_6   106
#define ENT_MP_7   107
#define ENT_MP_8   108
#define ENT_MP_9   109

/* instance Ids */
#define INST_MP_0   1
#define INST_MP_1   2
#define INST_MP_2   3
#define INST_MP_3   4
#define INST_MP_4   5

#define TST_ADD_PROCID_LST(_n, _lst)\
   if (SAddProcIdLst((_n), (_lst)) != ROK)\
      RETVALUE(RFAILED);

#define TST_GET_PROCID_LST(_n, _lst)\
   if (SGetProcIdLst((_n), (_lst)) != ROK)\
      RETVALUE(RFAILED);

#define TST_REM_PROCID_LST(_n, _lst)\
   if (SRemProcIdLst((_n), (_lst)) != ROK)\
      RETVALUE(RFAILED);

#define TST_REG_TTSK(_proc, _ent, _inst, _type, _prio, _f1, _f2)\
   if (SRegTTsk(_proc, (_ent), (_inst), (_type), (_prio), (_f1), (_f2)) != ROK)\
      RETVALUE(RFAILED);

#define TST_CRE_STSK(_prio, _id)\
   if (SCreateSTsk((_prio), (_id)) != ROK)\
      RETVALUE(RFAILED);

#define TST_ATT_TTSK(_proc, _ent, _inst, _id)\
   if (SAttachTTsk((_proc), (_ent), (_inst), (_id)) != ROK)\
      RETVALUE(RFAILED);

#define TST_DET_TTSK(_proc, _ent, _inst)\
   if (SDetachTTsk((_proc), (_ent), (_inst)) != ROK)\
      RETVALUE(RFAILED);

#define TST_DEREG_TTSK(_proc, _ent, _inst)\
   if (SDeregTTsk((_proc), (_ent), (_inst)) != ROK)\
      RETVALUE(RFAILED);

#define TST_GET_XXCB(_proc, _ent, _inst, _cb)\
   if (SGetXxCb((_proc), (_ent), (_inst), (_cb)) != ROK)\
      RETVALUE(RFAILED);

#endif /* SS_MULTIPLE_PROCS */

/* local typedefs */
  
/* local externs */


  
/* forward references */

/* ss029.103: modification: multiple proc ids related modifications */
EXTERN S16 startTest(S16 );
#ifdef SS_MULTIPLE_PROCS
PRIVATE S16 tstMp ARGS ((Void));
PRIVATE S16 tstMpProcLst ARGS ((Void));
PRIVATE S16 tstMpTskFunc ARGS ((Void));
PUBLIC TskInit tskCb[SS_MAX_TTSKS];
PUBLIC S16 tstMpActvTsk0 ARGS ((Pst *pst, Buffer *mBuf));
PUBLIC S16 tstMpInitFunc ARGS ((ProcId proc,
                                Ent ent,
                                Inst inst,
                                Region region,
                                Reason reason,
                                Void **xxCb));
#endif /* SS_MULTIPLE_PROCS */

/* local function definition */
#ifndef SS_SINGLE_THREADED
PRIVATE Void tskEnd  ARGS((U8 tskId));
PRIVATE S16 permTsk1 ARGS((Pst *pst, Buffer *mBuf));
PRIVATE S16 permTsk2 ARGS((Pst *pst, Buffer *mBuf));
PRIVATE S16 permTsk3 ARGS((Pst *pst, Buffer *mBuf));
PRIVATE S16 permTsk4 ARGS((Pst *pst, Buffer *mBuf));
PRIVATE S16 permTsk5 ARGS((Pst *pst, Buffer *mBuf));
PRIVATE S16 permTsk6 ARGS((Pst *pst, Buffer *mBuf));
PRIVATE S16 permTsk7 ARGS((Pst *pst, Buffer *mBuf));
PRIVATE S16 permTsk8 ARGS((Pst *pst, Buffer *mBuf));
#endif /* SS_SINGLE_THREADED */

/* ss029.103: modification: multiple proc ids related modifications */
#ifndef SS_MULTIPLE_PROCS 
PRIVATE S16 tst1ActvTmr ARGS((void));
PRIVATE S16 tst2ActvTmr ARGS((void));
#else /* SS_MULTIPLE_PROCS */
PRIVATE S16 tst1ActvTmr ARGS((ProcId proc, Ent ent, Inst inst));
PRIVATE S16 tst2ActvTmr ARGS((ProcId proc, Ent ent, Inst inst));
#endif /* SS_MULTIPLE_PROCS */

#ifdef SS_SINGLE_THREADED

/* ss029.103: modification: multiple proc ids related modifications */
#ifdef SS_MULTIPLE_PROCS

EXTERN  S16 tst0ActvInit ARGS((ProcId proc, 
                               Ent ent,
                               Inst inst,
                               Region region, 
                               Reason reason, 
                               Void **xxCb));
EXTERN  S16 tst1ActvInit ARGS((ProcId proc, 
                               Ent ent,
                               Inst inst,
                               Region region, 
                               Reason reason, 
                               Void **xxCb));
EXTERN  S16 tst2ActvInit ARGS((ProcId proc, 
                               Ent ent,
                               Inst inst,
                               Region region, 
                               Reason reason, 
                               Void **xxCb));
EXTERN  S16 tst3ActvInit ARGS((ProcId proc, 
                               Ent ent,
                               Inst inst,
                               Region region, 
                               Reason reason, 
                               Void **xxCb));

#else /* SS_MULTIPLE_PROCS */

EXTERN  S16 tst0ActvInit ARGS((Ent ent,Inst inst,Region region, Reason reason));
EXTERN  S16 tst1ActvInit ARGS((Ent ent,Inst inst,Region region, Reason reason));
EXTERN  S16 tst2ActvInit ARGS((Ent ent,Inst inst,Region region, Reason reason));
 /* ss010.13: Addition */
EXTERN  S16 tst3ActvInit ARGS((Ent ent,Inst inst,Region region, Reason reason));

#endif /* SS_MULTIPLE_PROCS */

/* ss029.103: modification: multiple proc ids related modifications */
#ifndef SS_MULTIPLE_PROCS 
EXTERN  S16 tst1fnc ARGS((void));
EXTERN  S16 tst2fnc ARGS((void));
#else /* SS_MULTIPLE_PROCS */
EXTERN  S16 tst1fnc ARGS((ProcId proc, Ent ent, Inst inst));
EXTERN  S16 tst2fnc ARGS((ProcId proc, Ent ent, Inst inst));
#endif /* SS_MULTIPLE_PROCS */

EXTERN  S16 tst0ActvTsk ARGS((Pst *pst,Buffer *mBuf));
EXTERN  S16 tst1ActvTsk ARGS((Pst *pst,Buffer *mBuf));
EXTERN  S16 tst2ActvTsk ARGS((Pst *pst,Buffer *mBuf));
 /* ss010.13: Addition */
EXTERN  S16 tst3ActvTsk ARGS((Pst *pst,Buffer *mBuf));
EXTERN  S16 tstRtrTsk ARGS((Pst *pst,Buffer *mBuf));

EXTERN  S16 tst0PermActvTsk ARGS((Pst *pst,Buffer *mBuf));
EXTERN  S16 tst1PermActvTsk ARGS((Pst *pst,Buffer *mBuf));

/* ss019.103 - Addition SS_SINGLE_THREADED */
#else
EXTERN  S16 tst0mtActvTsk ARGS((Pst *pst,Buffer *mBuf));
EXTERN  S16 tst1mtActvTsk ARGS((Pst *pst,Buffer *mBuf));
EXTERN  S16 tst2mtActvTsk ARGS((Pst *pst,Buffer *mBuf));
EXTERN  S16 tst3mtActvTsk ARGS((Pst *pst,Buffer *mBuf));
EXTERN  S16 tst4mtActvTsk ARGS((Pst *pst,Buffer *mBuf));
EXTERN  S16 tst5mtActvTsk ARGS((Pst *pst,Buffer *mBuf));
#endif /* SS_SINGLE_THREADED */

  /* ss016.13: Addition */
#if defined(SS_VW) && defined(SS_ZEROCOPY)
EXTERN  S16 tstZeroCopyTrans ARGS((Void));
#endif

/* functions in other modules */
#ifdef __cplusplus
extern "C" Void exit ARGS((int status));
#endif

/* public variable declarations */

/* control variables for testing */

/* private variable declarations */
#ifndef SS_SINGLE_THREADED   
PRIVATE S32    tCnt;
#endif /* SS_SINGLE_THREADED */
PRIVATE TstCp  tCp;              /* test control point */
PRIVATE Region region;
PRIVATE Pool   pool;
PRIVATE Ticks  sTicks;           /* start ticks */
PRIVATE MsgLen mLen = 1;
#ifndef SS_SINGLE_THREADED   
PRIVATE Pool   sPool0;
#endif /* SS_SINGLE_THREADED */
PRIVATE Bool   tskTmrCnt[NMBTMRTSKS]={0,0};   /* task timer flag */

#ifdef SS_SINGLE_THREADED
PRIVATE S16 ssTstState;            /* test state */
PRIVATE U32 ssTstCnt;              /* test count */
PRIVATE Ticks sysTime1;            /* system time 1 */
 /* ss005.13: addition */
#ifdef UNIX
PRIVATE Ticks Time1, Time2;
#endif /* UNIX */
PRIVATE S16 sysTimeCnt;            /* system time count */
PRIVATE Random value1;             /* random number */
PRIVATE S16 valueCnt;              /* random number count */
PRIVATE Pool sPool;                /* pool id */
PRIVATE Bool tskInitCnt[NMBTSKS];  /* task initialization flag */
PRIVATE Bool tskActvCnt[NMBTSKS];  /* task activation flag */
PRIVATE S16  tskLen[NMBTSKS];      /* task message length */
PRIVATE S16  tmrTimeCnt[NMBTSKS];  /* timer time count */
PRIVATE Bool prntFlg;              /* print flag */
#endif /* SS_SINGLE_THREADED */
PRIVATE Txt  prntBuf[PRNTSZE];     /* print buffer */
 /* ss005.13: addition */
/* ss026.103 - Modification to fix warning */
#ifdef SS_SINGLE_THREADED
#ifdef UNIX
PRIVATE struct timespec mytime1, mytime2;
 /* ss017.13: addition */
#ifdef SS_LINUX
PRIVATE struct timeval  mytimeval1, mytimeval2;
#endif
#endif /* UNIX */ 
#endif /* SS_SINGLE_THREADED */
  
/*
 * support functions
 */


  
/*
*
*       Fun:   rdConQ
*
*       Desc:  Reads the console queue.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  ss_acc.c
*
*/
  
#ifdef ANSI
PUBLIC S16 rdConQ
(
Data data
) 
#else
PUBLIC S16 rdConQ(data)
Data data;
#endif
{
   TRC2(rdConQ)

   /* check if control-c */
   if (data == 0x03)
   {
#ifdef NU
      ExitProcess(1);
#endif
   }

   RETVALUE(ROK);

} /* end of rdConQ */

/*
*
*       Fun:   tst
*
*       Desc:  entry point for task registration
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: None
*
*       File:  ss_acc.c
*
*/
#ifdef ANSI
PUBLIC S16 tst
(
void
)
#else
PUBLIC S16 tst()
#endif
{
   S16 i;
/* ss029.103: modification: multiple proc ids related modifications */
/* ss031.103: modification: flag correction */
#if defined(SS_MULTIPLE_PROCS) || (!defined(SS_SINGLE_THREADED))
   S16 ret;
#endif

/* ss019.103 - Addition SS_SINGLE_THREADED */
#ifndef SS_SINGLE_THREADED
   Buffer *m[TSTTIMES];
   Pst ourPst;
#endif
/* ss029.103: modification: multiple proc ids related modifications */
#ifdef SS_MULTIPLE_PROCS
   ProcId tstPrc[2]; 
   SSTskId sTskId1[8];
#ifndef SS_SINGLE_THREADED
   Inst j;
#endif
#endif /* SS_MULTIPLE_PROCS */

   TRC1(tst)

   SGetSysTime(&sTicks);
   for(i = 0; i < SS_MAX_TTSKS;  i++)
      tCp.tskCnt[i] = 0;
   tCp.tstCnt = 0;
   region = SS_DFLT_REGION;
   pool   = SS_DFLT_POOL;

/* ss029.103: add: execute multiple procs related test cases first */
#ifdef SS_MULTIPLE_PROCS
   tstMp();
#endif /* SS_MULTIPLE_PROCS */

/* ss029.103: add: register test proc id with SSI */ 
#ifdef SS_MULTIPLE_PROCS
   /* Add first proc Id */
   tstPrc[0] = PROC_MP_ID0;
   if (SAddProcIdLst(1, tstPrc) != ROK)
   {
      SSLOGERROR( ERRCLS_DEBUG, ESS557, 87, "Could not add procId to the list");
   }
#endif /* SS_MULTIPLE_PROCS */

#ifdef SS_SINGLE_THREADED

   ssTstState = 0;
   ssTstCnt = 0;
   sysTimeCnt = 0;
   valueCnt = 0;
 /* ss005.13: addition */
#ifdef UNIX
 /* ss017.13: addition */
#ifndef SS_LINUX
   clock_gettime(CLOCK_REALTIME, &mytime1);
#else
   gettimeofday(&mytimeval1,NULL);
   mytime1.tv_sec = mytimeval1.tv_sec;
   mytime1.tv_nsec = mytimeval1.tv_usec * 1000;
#endif

   SGetSysTime(&Time1);
#endif /* UNIX */
   SGetSysTime(&sysTime1);
   SRandom(&value1);
   mLen = 0;
   for (i = 0; i < NMBTSKS; i++)
   {
      tskInitCnt[i] = 0;
      tskActvCnt[i] = 0;
      tskLen[i] = 0;
      tmrTimeCnt[i] = 0;
   }
   for (i = 0;  i < NMBTMRTSKS;  i++)
   {
      tskTmrCnt[i] = 0;
   }
   prntFlg = FALSE;

/* ss029.103: modification: SRegInit function is not supported */ 
#ifndef SS_MULTIPLE_PROCS
   /* Register the initialization address of the test task 0 */
   SRegInit(TST0ENT, TSTINST0, tst0ActvInit); 

   if (tskInitCnt[0] != 1)
   {
      SSLOGERROR( ERRCLS_DEBUG, ESS558, 87, "" );
   }

   /* Register the initialization address of the test task 1 */
   SRegInit(TST1ENT, TSTINST0, tst1ActvInit); 

   if (tskInitCnt[1] != 1)
   {
      SSLOGERROR( ERRCLS_DEBUG, ESS559, 88, "" );
   }

   /* Register the initialization address of the test task 2 */
   SRegInit(TST2ENT, TSTINST0, tst2ActvInit); 

   if (tskInitCnt[2] != 1)
   {
      SSLOGERROR( ERRCLS_DEBUG, ESS560, 89, "" );
   }
 /* ss010.13: addition */
   /* Register the initialization address of the test task 3 */
   SRegInit(TST3ENT, TSTINST0, tst3ActvInit); 

   if (tskInitCnt[3] != 1)
   {
      SSLOGERROR( ERRCLS_DEBUG, ESS561, ERRZERO, "" );
   }

   /* Register the activation address of the test task 0, instance 0 */
   SRegActvTsk(TST0ENT, TSTINST0, TTNORM, PRIOR0, tst0ActvTsk);

   /* Register the activation address of the test task 1, instance 0 */
   SRegActvTsk(TST1ENT, TSTINST0, TTNORM, PRIOR0, tst1ActvTsk);

   /* Register the activation address of the test task 2, instance 0 */
   SRegActvTsk(TST2ENT, TSTINST0, TTNORM, PRIOR0, tst2ActvTsk);

 /* ss010.13: addition */
   /* Register the activation address of the test task 3, instance 0 */
   SRegActvTsk(TST3ENT, TSTINST0, TTNORM, PRIOR0, tst3ActvTsk);

   /* Register the activation address of the first timer task */
   SRegTmr(TST1ENT, TSTINST0, TSK1TMR, tst1ActvTmr);

   /* Register the activation address of the second timer task */
   SRegTmr(TST2ENT, TSTINST0, TSK2TMR, tst2ActvTmr);

   /* Register the activation address of the first test permanent task */
   SRegActvTsk(TSTPERMENT, TSTINST0, TTPERM, PRIOR0, tst0PermActvTsk);
 
   /* Register the activation address of the second test permanent task */
   SRegActvTsk(TSTPERMENT, TSTINST1, TTPERM, PRIOR0, tst1PermActvTsk);
 
   /* This section manipulates the static memory */

   SGetSMem(DFLT_REGION, (Size) ((TSTTIMES + 1) * MAXSMEMLEN), &sPool); 
#else /* SS_MULTIPLE_PROCS */
   /* Register first TAPA task */ 
   ret = SCreateSTsk(SS_NORM_TSK_PRI, &sTskId1[0]); 
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS562, (ErrVal) ret,
                     "Could not create system task");
#endif
      RETVALUE(ret);
   }
 
   SRegTTsk(PROC_MP_ID0, TST0ENT, TSTINST0, TTNORM, PRIOR0, 
               tst0ActvInit, tst0ActvTsk);

   if (tskInitCnt[0] != 1)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS563, 87, "Error in registering TAPA Task1" );
   }

   /* Register second TAPA task */ 
   SRegTTsk(PROC_MP_ID0, TST1ENT, TSTINST0, TTNORM, PRIOR0, 
               tst1ActvInit, tst1ActvTsk);

   if (tskInitCnt[1] != 1)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS564, 87, "Error in registering TAPA Task2" );
   }

   /* Register third TAPA task */ 
   SRegTTsk(PROC_MP_ID0, TST2ENT, TSTINST0, TTNORM, PRIOR0, 
               tst2ActvInit, tst2ActvTsk);

   if (tskInitCnt[2] != 1)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS565, 87, "Error in registering TAPA Task3" );
   }

   /* Register fourth TAPA task */ 
   SRegTTsk(PROC_MP_ID0, TST3ENT, TSTINST0, TTNORM, PRIOR0, 
               tst3ActvInit, tst3ActvTsk);

   if (tskInitCnt[3] != 1)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS566, 87, "Error in registering TAPA Task4" );
   }

   /* attach all registered TAPA tsks to the system task we created */
   SAttachTTsk(PROC_MP_ID0, TST0ENT, TSTINST0, sTskId1[0]);
   SAttachTTsk(PROC_MP_ID0, TST1ENT, TSTINST0, sTskId1[0]);
   SAttachTTsk(PROC_MP_ID0, TST2ENT, TSTINST0, sTskId1[0]);
   SAttachTTsk(PROC_MP_ID0, TST3ENT, TSTINST0, sTskId1[0]);

   /* Register the activation address of the first timer task */
   SRegTmr(PROC_MP_ID0, TST1ENT, TSTINST0, TSK1TMR, tst1ActvTmr);

   /* Register the activation address of the second timer task */
   SRegTmr(PROC_MP_ID0, TST2ENT, TSTINST0, TSK2TMR, tst2ActvTmr);

   /* Register the activation address of the first test permanent task */
   SRegTTsk(PROC_MP_ID0, TSTPERMENT, TSTINST0, TTPERM, PRIOR0, NULLP, tst0PermActvTsk);

   /* Register the activation address of the second test permanent task */
   SRegTTsk(PROC_MP_ID0, TSTPERMENT, TSTINST1, TTPERM, PRIOR0, NULLP, tst1PermActvTsk);

   /* attach perm tasks to the system task we created */
   SAttachTTsk(PROC_MP_ID0, TSTPERMENT, TSTINST0, sTskId1[0]);
   SAttachTTsk(PROC_MP_ID0, TSTPERMENT, TSTINST1, sTskId1[0]);
 
   /* This section manipulates the static memory */
   SGetSMem(DFLT_REGION, (Size) ((TSTTIMES + 1) * MAXSMEMLEN), &sPool); 

#endif /* SS_MULTIPLE_PROCS */

#else /* SS_SINGLE_THREADED */

/* ss029.103: modification: 
   SRegActvTsk is not supported in case multiple procs */ 
#ifndef SS_MULTIPLE_PROCS
   /* ss019.103 - Addition for initializing ACK count */
   ACKCount = 5;

   /* This section manipulates the static memory */

   SGetSMem(DFLT_REGION, (Size) ((TSTTIMES + 1) * MAXSMEMLEN), &sPool0);   

   SRegActvTsk(PERMENT2, (Inst)tCnt++, TTPERM, PRIOR0, permTsk1);
   SRegActvTsk(PERMENT2, (Inst)tCnt++, TTPERM, PRIOR0, permTsk2);
   SRegActvTsk(PERMENT2, (Inst)tCnt++, TTPERM, PRIOR0, permTsk3);
   SRegActvTsk(PERMENT2, (Inst)tCnt++, TTPERM, PRIOR0, permTsk4);
   SRegActvTsk(PERMENT2, (Inst)tCnt++, TTPERM, PRIOR0, permTsk5);
   SRegActvTsk(PERMENT2, (Inst)tCnt++, TTPERM, PRIOR0, permTsk6);
   SRegActvTsk(PERMENT2, (Inst)tCnt++, TTPERM, PRIOR0, permTsk7);
   SRegActvTsk(PERMENT2, (Inst)tCnt++, TTPERM, PRIOR0, permTsk8);

   /* Register the activation address of the first timer task */
   SRegTmr(PERMENT2, 1, TSK1TMR, tst1ActvTmr);

   /* Register the activation address of the second timer task */
   SRegTmr(PERMENT2, 2, TSK2TMR, tst2ActvTmr);

   /* ss019.103 - Addition for multithreaded task test */

   ret = SRegTTsk(TST0ENT, TSTINST0, TTNORM, PRIOR0, NULL, tst0mtActvTsk);
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS567, (ErrVal) ret,
                     "Could not register task");
#endif
      RETVALUE(ret);
   }

   ret = SCreateSTsk(SS_NORM_TSK_PRI, &sTskId[0]); 
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS568, (ErrVal) ret,
                     "Could not create system task");
#endif
      SDeregTTsk(TST0ENT, TSTINST0);
      RETVALUE(ret);
   }
   
   ret = SAttachTTsk(TST0ENT, TSTINST0, sTskId[0]);
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS569, (ErrVal) ret,
                     "Could not attach TAPA task to system task");
#endif
      SDestroySTsk(sTskId[0]);
      SDeregTTsk(TST0ENT, TSTINST0);
   }
   
   /* Get message */
   SGetMsg(region, sPool0, &m[0]);

   ourPst.event     = 0;               /* event */
   ourPst.prior     = 0;              /* priority */
   ourPst.route     = 0;               /* route */
   ourPst.dstProcId = SFndProcId();    /* destination processor id */
   ourPst.dstEnt    = TST0ENT;         /* destination entity */
   ourPst.dstInst   = TSTINST0;        /* destination instance */
   ourPst.srcProcId = SFndProcId();    /* source processor id */
   ourPst.srcEnt    = PERMENT2;        /* source entity */
   ourPst.srcInst   = TSTINST0;        /* source instance */
   if (SPstTsk(&ourPst, m[0]) != ROK)
   {
      SSLOGERROR( ERRCLS_DEBUG, ESS570, ERRZERO, "" );
   }
   
#else /* SS_MULTIPLE_PROCS */

   /* ss019.103 - Addition for initializing ACK count */
   ACKCount = 5;

   /* This section manipulates the static memory */

   SGetSMem(DFLT_REGION, (Size) ((TSTTIMES + 1) * MAXSMEMLEN), &sPool0);   

   /* create 8 system tasks */
   for (i = 0; i < 8; i++)
      SCreateSTsk(SS_NORM_TSK_PRI, &sTskId1[i]); 
   
   /* register eight perm tasks */
   j = tCnt;
   /* ss031.103: modification: compilation correction */
   SRegTTsk(PROC_MP_ID0, PERMENT2, (Inst)tCnt++, TTPERM, PRIOR0, NULLP, permTsk1);
   SRegTTsk(PROC_MP_ID0, PERMENT2, (Inst)tCnt++, TTPERM, PRIOR0, NULLP, permTsk2);
   SRegTTsk(PROC_MP_ID0, PERMENT2, (Inst)tCnt++, TTPERM, PRIOR0, NULLP, permTsk3);
   SRegTTsk(PROC_MP_ID0, PERMENT2, (Inst)tCnt++, TTPERM, PRIOR0, NULLP, permTsk4);
   SRegTTsk(PROC_MP_ID0, PERMENT2, (Inst)tCnt++, TTPERM, PRIOR0, NULLP, permTsk5);
   SRegTTsk(PROC_MP_ID0, PERMENT2, (Inst)tCnt++, TTPERM, PRIOR0, NULLP, permTsk6);
   SRegTTsk(PROC_MP_ID0, PERMENT2, (Inst)tCnt++, TTPERM, PRIOR0, NULLP, permTsk7);
   SRegTTsk(PROC_MP_ID0, PERMENT2, (Inst)tCnt++, TTPERM, PRIOR0, NULLP, permTsk8);

   /* attach all above taks to a separate system task */
   /* ss031.103: modification: compilation correction */
   for (i = 0; i < 8; i++)
      SAttachTTsk(PROC_MP_ID0, PERMENT2, j++, sTskId1[i++]); 

   /* Register the activation address of the first timer task */
   SRegTmr(PROC_MP_ID0, PERMENT2, 1, TSK1TMR, tst1ActvTmr);

   /* Register the activation address of the second timer task */
   SRegTmr(PROC_MP_ID0, PERMENT2, 2, TSK2TMR, tst2ActvTmr);

   /* ss019.103 - Addition for multithreaded task test */

   ret = SRegTTsk(PROC_MP_ID0, TST0ENT, TSTINST0, TTNORM, PRIOR0, NULL, tst0mtActvTsk);
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS571, (ErrVal) ret,
                     "Could not register task");
#endif
      RETVALUE(ret);
   }

   ret = SCreateSTsk(SS_NORM_TSK_PRI, &sTskId[0]); 
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS572, (ErrVal) ret,
                     "Could not create system task");
#endif
      /* ss031.103: modification: compilation correction */
      SDeregTTsk(PROC_MP_ID0, TST0ENT, TSTINST0);
      RETVALUE(ret);
   }
   
   ret = SAttachTTsk(PROC_MP_ID0, TST0ENT, TSTINST0, sTskId[0]);
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS573, (ErrVal) ret,
                     "Could not attach TAPA task to system task");
#endif
      SDestroySTsk(sTskId[0]);
      SDeregTTsk(PROC_MP_ID0, TST0ENT, TSTINST0);
   }
   
   /* Get message */
   SGetMsg(region, sPool0, &m[0]);

   ourPst.event     = 0;               /* event */
   ourPst.prior     = 0;               /* priority */
   ourPst.route     = 0;               /* route */
   ourPst.dstProcId = PROC_MP_ID0;      /* destination processor id */
   ourPst.dstEnt    = TST0ENT;         /* destination entity */
   ourPst.dstInst   = TSTINST0;        /* destination instance */
   ourPst.srcProcId = PROC_MP_ID0;      /* source processor id */
   ourPst.srcEnt    = PERMENT2;        /* source entity */
   ourPst.srcInst   = TSTINST0;        /* source instance */
   if (SPstTsk(&ourPst, m[0]) != ROK)
   {
      SSLOGERROR( ERRCLS_DEBUG, ESS574, ERRZERO, "" );
   }
#endif /* SS_MULTIPLE_PROCS */

#endif /* SS_SINGLE_THREADED */

   /* Register the activation address for the stack manager */
   /*SRegActvTsk(ENTSM, 0, TTNORM, PRIOR0, smActvTsk);*/

   RETVALUE(ROK);

} /* end of tst */

#ifdef SS_SINGLE_THREADED


/*                                     
*
*       Fun:   tst0ActvInit
*
*       Desc:  Sample function for test task 0 initialization.
*
*       Ret:   ROK       - ok
*
*       Notes: None
*
*       File:  ss_acc.c
*
*/
 
/* ss029.103: modification: procId and control cb parameter added */ 
#ifndef SS_MULTIPLE_PROCS

#ifdef ANSI
PUBLIC S16 tst0ActvInit
(
Ent ent,                    /* entity */
Inst inst,                  /* instance */
Region reg,                 /* region */
Reason reason               /* reason */
)
#else
PUBLIC S16 tst0ActvInit(ent, inst, reg, reason)
Ent ent;                    /* entity */
Inst inst;                  /* instance */
Region reg;                 /* region */
Reason reason;              /* reason */
#endif

#else /* SS_MULTIPLE_PROCS */

#ifdef ANSI
PUBLIC S16 tst0ActvInit
(
ProcId proc,                /* processor */
Ent ent,                    /* entity */
Inst inst,                  /* instance */
Region reg,                 /* region */
Reason reason,              /* reason */
Void **xxCb                 /* control block */
)
#else
PUBLIC S16 tst0ActvInit(proc, ent, inst, reg, reason, xxCb)
ProcId proc;                /* processor */
Ent ent;                    /* entity */
Inst inst;                  /* instance */
Region reg;                 /* region */
Reason reason;              /* reason */
Void **xxCb;                /* control block */
#endif

#endif /* SS_MULTIPLE_PROCS */
{
   TRC2(tst0ActvInit)

/* ss029.103: modification: procId parameter added */ 
#ifdef SS_MULTIPLE_PROCS 
   UNUSED(proc);
#endif
   UNUSED(ent);
   UNUSED(inst);
#ifndef SS_MULTICORE_SUPPORT
   UNUSED(reg);
#endif
   UNUSED(reason);

#ifdef SS_MULTIPLE_PROCS 
   *xxCb = (Void *) 100; /* magic number */
#endif

   tskInitCnt[0]++;
#ifdef SS_MULTICORE_SUPPORT
/*Verification added as part of memory management test case */
/* TAPA tasks attached sTsk[0] will get the region parameter 
 * as 0 in their respective ActvInit() function
 */
 if(reg != 0)
 {
    SSLOGERROR( ERRCLS_DEBUG, ESS575, ERRZERO, "System task to region mapping failed\n");
 }
#endif
   RETVALUE(ROK);

} /* end of tst0ActvInit */


/*                                     
*
*       Fun:   tst1ActvInit
*
*       Desc:  Sample function for test task 0 initialization.
*
*       Ret:   ROK       - ok
*
*       Notes: None
*
*       File:  ss_acc.c
*
*/
 
/* ss029.103: modification: procId and control cb parameter added */ 
#ifndef SS_MULTIPLE_PROCS

#ifdef ANSI
PUBLIC S16 tst1ActvInit
(
Ent ent,                    /* entity */
Inst inst,                  /* instance */
Region reg,                 /* region */
Reason reason               /* reason */
)
#else
PUBLIC S16 tst1ActvInit(ent, inst, reg, reason)
Ent ent;                    /* entity */
Inst inst;                  /* instance */
Region reg;                 /* region */
Reason reason;              /* reason */
#endif

#else /* SS_MULTIPLE_PROCS */

#ifdef ANSI
PUBLIC S16 tst1ActvInit
(
ProcId proc,                /* processor */
Ent ent,                    /* entity */
Inst inst,                  /* instance */
Region reg,                 /* region */
Reason reason,              /* reason */
Void **xxCb                 /* control block */
)
#else
PUBLIC S16 tst1ActvInit(proc, ent, inst, reg, reason, xxCb)
ProcId proc;                /* processor */
Ent ent;                    /* entity */
Inst inst;                  /* instance */
Region reg;                 /* region */
Reason reason;              /* reason */
Void **xxCb;                /* control block */
#endif

#endif /* SS_MULTIPLE_PROCS */
{
   TRC2(tst1ActvInit)

/* ss029.103: modification: procId parameter added */ 
#ifdef SS_MULTIPLE_PROCS 
   UNUSED(proc);
#endif
   UNUSED(ent);
   UNUSED(inst);
   UNUSED(reg);
   UNUSED(reason);

#ifdef SS_MULTIPLE_PROCS 
   *xxCb = (Void *) 100; /* magic number */
#endif

   tskInitCnt[1]++;
   RETVALUE(ROK);

} /* end of tst1ActvInit */


/*                                     
*
*       Fun:   tst2ActvInit
*
*       Desc:  Sample function for test task 0 initialization.
*
*       Ret:   ROK       - ok
*
*       Notes: None
*
*       File:  ss_acc.c
*
*/
 
/* ss029.103: modification: procId and control cb parameter added */ 
#ifndef SS_MULTIPLE_PROCS

#ifdef ANSI
PUBLIC S16 tst2ActvInit
(
Ent ent,                    /* entity */
Inst inst,                  /* instance */
Region reg,                 /* region */
Reason reason               /* reason */
)
#else
PUBLIC S16 tst2ActvInit(ent, inst, reg, reason)
Ent ent;                    /* entity */
Inst inst;                  /* instance */
Region reg;                 /* region */
Reason reason;              /* reason */
#endif

#else /* SS_MULTIPLE_PROCS */

#ifdef ANSI
PUBLIC S16 tst2ActvInit
(
ProcId proc,                /* processor */
Ent ent,                    /* entity */
Inst inst,                  /* instance */
Region reg,                 /* region */
Reason reason,              /* reason */
Void **xxCb                 /* control block */
)
#else
PUBLIC S16 tst2ActvInit(proc, ent, inst, reg, reason, xxCb)
ProcId proc;                /* processor */
Ent ent;                    /* entity */
Inst inst;                  /* instance */
Region reg;                 /* region */
Reason reason;              /* reason */
Void **xxCb;                /* control block */
#endif

#endif /* SS_MULTIPLE_PROCS */
{
   TRC2(tst2ActvInit)

/* ss029.103: modification: procId parameter added */ 
#ifdef SS_MULTIPLE_PROCS 
   UNUSED(proc);
#endif
   UNUSED(ent);
   UNUSED(inst);
   UNUSED(reg);
   UNUSED(reason);

/* ss029.103: modification: control CB parameter initialized */ 
#ifdef SS_MULTIPLE_PROCS 
   *xxCb = (Void *) 100; /* magic number */
#endif

   tskInitCnt[2]++;
   RETVALUE(ROK);

} /* end of tst2ActvInit */


/*                                     
*
*       Fun:   tst3ActvInit
*
*       Desc:  Sample function for test task 0 initialization.
*
*       Ret:   ROK       - ok
*
*       Notes: None
*
*       File:  ss_acc.c
*
*/
 
/* ss029.103: modification: procId and control cb parameter added */ 
#ifndef SS_MULTIPLE_PROCS

#ifdef ANSI
PUBLIC S16 tst3ActvInit
(
Ent ent,                    /* entity */
Inst inst,                  /* instance */
Region reg,                 /* region */
Reason reason               /* reason */
)
#else
PUBLIC S16 tst3ActvInit(ent, inst, reg, reason)
Ent ent;                    /* entity */
Inst inst;                  /* instance */
Region reg;                 /* region */
Reason reason;              /* reason */
#endif

#else /* SS_MULTIPLE_PROCS */

#ifdef ANSI
PUBLIC S16 tst3ActvInit
(
ProcId proc,                /* processor */
Ent ent,                    /* entity */
Inst inst,                  /* instance */
Region reg,                 /* region */
Reason reason,              /* reason */
Void **xxCb                 /* control block */
)
#else
PUBLIC S16 tst3ActvInit(proc, ent, inst, reg, reason, xxCb)
ProcId proc;                /* processor */
Ent ent;                    /* entity */
Inst inst;                  /* instance */
Region reg;                 /* region */
Reason reason;              /* reason */
Void **xxCb;                /* control block */
#endif

#endif /* SS_MULTIPLE_PROCS */
{
   TRC2(tst3ActvInit)

/* ss029.103: modification: procId parameter added */ 
#ifdef SS_MULTIPLE_PROCS 
   UNUSED(proc);
#endif
   UNUSED(ent);
   UNUSED(inst);
   UNUSED(reg);
   UNUSED(reason);

/* ss029.103: modification: control cb parameter added */ 
#ifdef SS_MULTIPLE_PROCS 
   *xxCb = (Void *) 100; /* magic number */
#endif

   tskInitCnt[3]++;
   RETVALUE(ROK);

} /* end of tst3ActvInit */


/*                                     
*
*       Fun:   tst0ActvTsk
*
*       Desc:  Sample function for test task 0 activation.
*
*       Ret:   ROK       - ok
*
*       Notes: None
*
*       File:  ss_acc.c
*
*/
 
#ifdef ANSI
PUBLIC S16 tst0ActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 tst0ActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   S16 j;
   Data uData;
   MsgLen mlng;
 
   TRC2(tst0ActvTsk)
 
   /* check received message */
   tskLen[0]++;
   if (tskLen[0] > MAXMSGLEN)
      tskLen[0] = 1;
 
   SFndLenMsg(mBuf,&mlng);
   if ( mlng != tskLen[0] )
      SSLOGERROR( ERRCLS_DEBUG, ESS576,1,"" );
  
   for ( j = 0; j < tskLen[0]; j++ )
   {
      SExamMsg(&uData,mBuf,(MsgLen) j);
      if ( uData != (Data) j )
         SSLOGERROR( ERRCLS_DEBUG, ESS577,2, "" );
   }
   if(pst->event != 0 || pst->route != 0)
      SSLOGERROR( ERRCLS_DEBUG, ESS578,3, "" );
 
   /* Post the message to the test task 1 */
   pst->event     = 1;               /* event */
   /* pst->prior     = 1; */               /* priority */
   pst->route     = 1;               /* route */
   pst->dstProcId = SFndProcId();    /* destination processor id */
   pst->dstEnt    = TST1ENT;         /* destination entity */
   pst->dstInst   = TSTINST0;        /* destination instance */
   pst->srcProcId = SFndProcId();    /* source processor id */
   pst->srcEnt    = TST0ENT;         /* source entity */
   pst->srcInst   = TSTINST0;        /* source instance */
   if (SPstTsk(pst, mBuf) != ROK)
   {
      SSLOGERROR( ERRCLS_DEBUG, ESS579,ERRZERO, "" );
   }
         
   /* pass test */
   ssTstState = 82;
 
   SExitTsk();
   RETVALUE(ROK);

} /* end of tst0ActvTsk */


/*                                     
*
*       Fun:   tst1ActvTsk
*
*       Desc:  Sample function for test task 1 activation.
*
*       Ret:   ROK       - ok
*
*       Notes: None
*
*       File:  ss_acc.c
*
*/
 
#ifdef ANSI
PUBLIC S16 tst1ActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 tst1ActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   S16 j;
   Data uData;
   MsgLen mlng;
 
   TRC2(tst1ActvTsk)
 
   /* check received message */
   tskLen[1]++;
   if (tskLen[1] > MAXMSGLEN)
      tskLen[1] = 1;
 
   SFndLenMsg(mBuf,&mlng);
   if ( mlng != tskLen[1] )
      SSLOGERROR( ERRCLS_DEBUG, ESS580,90, "" );
  
   for ( j = 0; j < tskLen[1]; j++ )
   {
      SExamMsg(&uData,mBuf,(MsgLen) j);
      if ( uData != (Data) j )
         SSLOGERROR( ERRCLS_DEBUG, ESS581,91, "" );
   }
   if(pst->event != 1 || pst->route != 1)
      SSLOGERROR( ERRCLS_DEBUG, ESS582,92, "" );
 
   /* Post the message to the test task 2 */
   pst->event     = 2;               /* event */
   /* pst->prior     = 2;               /* priority */
   pst->route     = 2;               /* route */
   pst->dstProcId = SFndProcId();    /* destination processor id */
   pst->dstEnt    = TST2ENT;         /* destination entity */
   pst->dstInst   = TSTINST0;        /* destination instance */
   pst->srcProcId = SFndProcId();    /* source processor id */
   pst->srcEnt    = TST1ENT;         /* source entity */
   pst->srcInst   = TSTINST0;        /* source instance */
   if (SPstTsk(pst, mBuf) != ROK)
   {
      SSLOGERROR( ERRCLS_DEBUG, ESS583, ERRZERO, "" );
   }
         
   /* pass test */
   sleep(10);
   ssTstState = 83;
 
   SExitTsk();
   RETVALUE(ROK);

} /* end of tst1ActvTsk */


/*                                     
*
*       Fun:   tst2ActvTsk
*
*       Desc:  Sample function for first test task activation.
*
*       Ret:   ROK       - ok
*
*       Notes: None
*
*       File:  ss_acc.c
*
*/
 
#ifdef ANSI
PUBLIC S16 tst2ActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 tst2ActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(tst2ActvTsk)
 
   if(pst->event != 2 || pst->route != 2)
      SSLOGERROR( ERRCLS_DEBUG, ESS584, ERRZERO, "" );

   /* return received message to pool */
   SPutMsg(mBuf);
 
   /* pass test */
   ssTstState = 84;
 
   SExitTsk();
   RETVALUE(ROK);

} /* end of tst2ActvTsk */

 /* ss010.13:addition */

/*                                     
*
*       Fun:   tst3ActvTsk
*
*       Desc:  Sample function for test task activation.
*
*       Ret:   ROK       - ok
*
*       Notes: None
*
*       File:  ss_acc.c
*
*/
 
#ifdef ANSI
PUBLIC S16 tst3ActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 tst3ActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   S16 j;
   Data uData;
   MsgLen mlng;

   TRC2(tst3ActvTsk)

   SFndLenMsg(mBuf,&mlng);
   if ( (pst->route == RTESPEC) || (pst->route == RTEFRST))
   {
  
     for ( j = 0; j < mlng; j++ )
     {
       SExamMsg(&uData,mBuf,(MsgLen) j);
       if ( uData != (Data) (mlng-j ))
          SSLOGERROR( ERRCLS_DEBUG, ESS585, ERRZERO, "" );
     }
     ssTstState = 98;
   }
   else
   {

     for ( j = 0; j < mlng; j++ )
     {
       SExamMsg(&uData,mBuf,(MsgLen) j);
       if ( uData != (Data) j )
          SSLOGERROR( ERRCLS_DEBUG, ESS586, ERRZERO, "" );
     }
#ifndef SS_MULTICORE_SUPPORT
     ssTstState = 121;
#else
     ssTstState = 101;
#endif
   }

   /* return received message to pool */
   SPutMsg(mBuf);
 
   /* pass test */
 
   SExitTsk();
   RETVALUE(ROK);

} /* end of tst3ActvTsk */

/*                                     
*
*       Fun:   tstRtrTsk
*
*       Desc:  Sample function for router task activation.
*
*       Ret:   ROK       - ok
*
*       Notes: None
*
*       File:  ss_acc.c
*
*/
 
#ifdef ANSI
PUBLIC S16 tstRtrTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 tstRtrTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   S16 j;
   Data uData, src[10];
   MsgLen mlng;
   
   TRC2(tstRtrTsk)
 

   SFndLenMsg(mBuf,&mlng);
  
   for ( j = 0; j < mlng; j++ )
   {
      SExamMsg(&uData,mBuf,(MsgLen) j);
      if ( uData != (Data) j )
         SSLOGERROR( ERRCLS_DEBUG, ESS587,0, "" );
   }
   SRemPstMsgMult(src, mlng, mBuf);
   /* Add Data to end of message */
   for (j = 0; j < 10; j++)
      SAddPstMsg( (Data)(10 - j), mBuf);
  
   /* ss019.103 - Addition for router task test */ 
   pst->dstInst   = TSTINST0;        /* destination instance */
   pst->dstEnt    = TST3ENT;         /* destination entity */

   /* pass test */
 
   SExitTsk();
   RETVALUE(ROK);

} /* end of tstRtrTsk */


/*
*
*       Fun:   tst0PermActvTsk
*
*       Desc:  Sample function for test permanent task activation.
*
*       Ret:   ROK       - ok
*
*       Notes: None
*
*       File:  ss_acc.c
*
*/
 
#ifdef ANSI
PUBLIC S16 tst0PermActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 tst0PermActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   Queue q;
   Queue q1;
   MsgLen mlng;
   MsgLen mlng1;
   QLen qlng;
   QLen qlng1;
   QLen idx;
   QLen size;
   S16 ret1;
   S16 ret2;
   S16 i;
   S16 j;
   Buffer *bufPtr;
   Buffer *m[TSTTIMES];
   Buffer *n[TSTTIMES];
   Data uData;
   Data sData;
   S8 s8;
   S16 s16;
   S32 s32;
   U8 u8;
   U16 u16;
   U32 u32;
#ifndef WIN32
#ifndef UNIX
   VectNmb vectNmb;
   PIF vectFnct,vectFnct1;
#endif /* UNIX */
#endif /* WIN32 */
   DateTime dt;
   Ticks sysTime2;
   Status status;
   Random value2;
   Data *sBuf[TSTTIMES];
   Data *s;
   Region regionn;
   Pool pooll;
   Pst ourPst;
 /* ss005.13: addition */
   Data src[BSIZE]; 
 /* ss007.13: addition */
#ifdef UNIX
   U32 time_int;
#endif /* UNIX */

#ifdef BIT_64
#ifdef SS_THREAD_PROFILE
   Txt buf[256];
   SSTskId sTskId;
   Ent ent;
   Inst inst;
#ifdef SS_MULTIPLE_PROCS
   ProcId procId;
#endif
   Event evnt;
   U32 timetaken;
   U64 totTime;
#endif /* SS_THREAD_PROFILE */
#endif /* BIT_64 */

#ifdef SS_WATCHDOG
/*ss013.301: Fixed Warnings for 32/64 bit compilation*/
   U8  *addr[2] = {(U8 *)"172.25.0.19",(U8 *)"172.25.0.39"};
   U16  port[2]    = {SS_WD_WDPORT,SS_WD_WDPORT};
#endif /* SS_WATCHDOG */
   TRC2(tst0PermActvTsk)

   if (mBuf != NULLP)
   {
      /* return message */
      SPutMsg(mBuf);
   }

   regionn = 0;
   pooll = SP_POOL;

/*ss013.301: Fixed Warnings for 32/64 bit compilation*/
#ifdef ALIGN_64BIT
   sprintf(prntBuf, "ss_acc: SS tst count %u case %02d\r", 
          ssTstCnt, ssTstState); 
#else
   sprintf(prntBuf, "ss_acc: SS tst count %lu case %02d\r", 
          ssTstCnt, ssTstState);
#endif 
   if (prntFlg == FALSE)
   {
      SDisplay(0,prntBuf);
      prntFlg = TRUE;
   }
   else
   {
      SDisplay(0, prntBuf);
      prntFlg = FALSE;
   }

   /* perform test case */
   switch(ssTstState)
   {
      case 0:               /* test statistics */
      {
         ++ssTstCnt;

         mLen++;
         if (mLen > MAXMSGLEN)
            mLen = 1;
	#ifdef SS_FBSED_TSK_REG
	  startTest(9); 
	#endif /* SS_FBSED_TSK_REG */
         ssTstState = 5;
         break;
      }
      case 5:
      {
/*ss013.301: Fixed Warnings for 32/64 bit compilation*/
         Data buf_log[200];
         MsgLen cnt;
         
         SGetMsg(regionn,pooll,&m[0]);
         for (i = 0; i < 150; i++)
         {
            SAddPstMsg((Data)i, m[0]);
         }

         SCpyMsgFix(m[0], 0, 150, buf_log, &cnt);
         if (cnt != 150)
            SSLOGERROR( ERRCLS_DEBUG, ESS588,ERRZERO, "" );
         
         for (i = 0; i < 150; i++)
         {
            if (buf_log[i] != (Data)i)
               SSLOGERROR( ERRCLS_DEBUG, ESS589, ERRZERO, "" );
            else
               buf_log[i] = 0;
         }
         
         SCpyMsgFix(m[0], 75, 75, buf_log, &cnt);

         if (cnt != 75)
            SSLOGERROR( ERRCLS_DEBUG, ESS590, ERRZERO, "" );

         for (i = 0; i < 75; i++)
         {
            if (buf_log[i] != (Data)i + 75)
               SSLOGERROR( ERRCLS_DEBUG, ESS591, ERRZERO, "" );
         }

         SCpyMsgFix(m[0], 149, 1, buf_log, &cnt);
         if (cnt != 1)
            SSLOGERROR( ERRCLS_DEBUG, ESS592, ERRZERO, "" );

         for (i = 0; i < 1; i++)
         {
            if (buf_log[i] != (Data)i+149)
               SSLOGERROR( ERRCLS_DEBUG, ESS593, ERRZERO, "" );
         }
         SPutMsg(m[0]);
         ssTstState = 10;
         break;
      }
      case 10:              /* queue initialization */
      {
         SInitQueue(&q);

         SFndLenQueue(&q, &qlng);
         if ( qlng != 0 )
            SSLOGERROR( ERRCLS_DEBUG, ESS594,5, "" );
         if (((ret1 = SDequeueFirst(&bufPtr, &q)) != ROKDNA) || 
            ((ret2 = SDequeueLast(&bufPtr, &q)) != ROKDNA))    
            SSLOGERROR( ERRCLS_DEBUG, ESS595,6, "" );
         idx = 0;
         if (((ret1 = SExamQueue(&bufPtr, &q, idx)) != ROKDNA) ||
            ((ret2 = SRemQueue(&bufPtr, &q, idx)) != ROKDNA))
            SSLOGERROR( ERRCLS_DEBUG, ESS596,7, "" );

         ssTstState = 11;
         break;
      }
      case 11:          /* queue and dequeue from front, find queue length */
      {
         SInitQueue(&q);

         for (i = 0; i < TSTTIMES; i++)
         {
            SGetMsg(regionn,pooll,&m[i]);
            SQueueFirst(m[i],&q);
            SFndLenQueue(&q, &qlng);
            if ( qlng != (QLen)(i+1) )
               SSLOGERROR( ERRCLS_DEBUG, ESS597,8, "" );
         }
         for (i = (TSTTIMES-1); i >= 0; i--)
         {
            SDequeueFirst(&m[i], &q);
            SFndLenQueue(&q, &qlng);
            if ( qlng != (QLen)i )
               SSLOGERROR( ERRCLS_DEBUG, ESS598,9, "" );
            SPutMsg(m[i]);
         }
   
         ssTstState =12;
         break;
      }
      case 12:           /* queue and dequeue from back, find queue length */
      {
         SInitQueue(&q);

         for (i = 0; i < TSTTIMES; i++)
         {
            SGetMsg(regionn,pooll,&m[i]);
            SQueueLast(m[i],&q);
            SFndLenQueue(&q, &qlng);
            if ( qlng != (QLen)(i+1) )
               SSLOGERROR( ERRCLS_DEBUG, ESS599, 10, "" );
         }
         for (i = (TSTTIMES-1); i >= 0; i--)
         {
            SDequeueLast(&m[i], &q);
            SFndLenQueue(&q, &qlng);
            if ( qlng != (QLen)i )
               SSLOGERROR( ERRCLS_DEBUG, ESS600, 11, "" );
            SPutMsg(m[i]);
         }

         for (i = 0; i < TSTTIMES; i++)
         {
            SGetMsg(regionn,pooll,&m[i]);
            SQueueFirst(m[i],&q);
         }
         for (i = 0; i < TSTTIMES; i++)
         {
            SDequeueLast(&n[i], &q);
            SFndLenQueue(&q,&qlng);
            if ( qlng != (QLen)(TSTTIMES-i-1) )
               SSLOGERROR( ERRCLS_DEBUG, ESS601, 12, "" );
            SPutMsg(n[i]);
         }   

         ssTstState = 13;
         break;
      }
      case 13:              /* flush queue */
         SInitQueue(&q);

         for (i = 0; i < TSTTIMES; i++)
         {
            SGetMsg(regionn,pooll,&m[i]);
            SQueueLast(m[i],&q);
         }
         SFlushQueue(&q);
         SFndLenQueue(&q,&qlng);
         if ( qlng != 0 )
            SSLOGERROR( ERRCLS_DEBUG, ESS602, 13, "" );

         if (((ret1 = SDequeueFirst(&bufPtr, &q)) != ROKDNA) || 
            ((ret2 = SDequeueLast(&bufPtr, &q)) != ROKDNA))    
            SSLOGERROR( ERRCLS_DEBUG, ESS603, 14, "" );
         ssTstState = 14;
         break;

      case 14:              /* concatenate queue */
         SInitQueue(&q);
         SInitQueue(&q1);

         for ( i = 1;i <= 2;i++ )
         {
            SGetMsg(regionn,pooll,&m[0]);
            SQueueLast(m[0],&q);
            SFndLenQueue(&q,&qlng);
           
            SGetMsg(regionn,pooll,&n[0]);
            SQueueFirst(n[0],&q1);
            SFndLenQueue(&q1,&qlng1);
         
            size = qlng+qlng1;
            if ( i == Q1Q2 )
            {
               SCatQueue(&q,&q1,Q1Q2);
               if ( size != q.crntSize )
                  SSLOGERROR( ERRCLS_DEBUG, ESS604, 15, "" );
               SDequeueFirst(&m[1],&q);
               if ( m[1] != m[0] )
                  SSLOGERROR( ERRCLS_DEBUG, ESS605, 16, "" );
               SDequeueLast(&n[1],&q);
               if ( n[1] != n[0] )
                  SSLOGERROR( ERRCLS_DEBUG, ESS606, 17, "" );
               SDequeueFirst(&n[2],&q1);
               if ( n[2] != NULLP )
                  SSLOGERROR( ERRCLS_DEBUG, ESS607, 18, "" );
               SPutMsg(m[0]);
               SPutMsg(n[0]);
            }
            else
            {
               SCatQueue(&q,&q1,Q2Q1);
               if ( size != q.crntSize )
                 SSLOGERROR( ERRCLS_DEBUG, ESS608, 19, "" );
               SDequeueFirst(&n[1],&q);
               if ( n[1] != n[0] )
                  SSLOGERROR( ERRCLS_DEBUG, ESS609, 20, "" );
               SDequeueLast(&m[1],&q);
               if ( m[1] != m[0] )
                  SSLOGERROR( ERRCLS_DEBUG, ESS610, 21, "" );
               SDequeueFirst(&n[2],&q1);
               if ( n[2] != NULLP )
                  SSLOGERROR( ERRCLS_DEBUG, ESS611, 22, "" );
               SPutMsg(m[0]);
               SPutMsg(n[0]);
            }               
         }

         ssTstState = 15;
         break;

      case 15:              /* examine queue */
         SInitQueue(&q);

         for (i = 0; i < TSTTIMES; i++)
         {
            SGetMsg(regionn,pooll,&m[i]);
            SQueueLast(m[i],&q);
         }

         idx = 0;
         SExamQueue(&bufPtr, &q, idx);
         if ( bufPtr != m[idx] )
            SSLOGERROR( ERRCLS_DEBUG, ESS612, 23, "" );
         idx = TSTTIMES-1;
         SExamQueue(&bufPtr, &q, idx);
         if ( bufPtr != m[idx] )
            SSLOGERROR( ERRCLS_DEBUG, ESS613, 24, "" );

         for (i = 0; i < TSTTIMES; i++)
            SPutMsg(m[i]);            

         ssTstState = 16;
         break;
            
      case 16:              /* add/remove to/from queue */
         SInitQueue(&q);
         SGetMsg(regionn,pooll,&n[0]);

         idx = 0;
         SAddQueue(n[0],&q,idx);
         SExamQueue(&n[1],&q,idx);
         SFndLenQueue(&q,&qlng);
         if ( (n[1] != n[0]) || (qlng != 1) )
            SSLOGERROR( ERRCLS_DEBUG, ESS614, 25, "" );
         SRemQueue(&n[2],&q,idx);
         SFndLenQueue(&q,&qlng);
         if ( (n[2] != n[0]) || (qlng != 0) )
            SSLOGERROR( ERRCLS_DEBUG, ESS615, 26, "" );
 
         for (i = 0; i < TSTTIMES; i++)
         {
            SGetMsg(regionn,pooll,&m[i]);
            SQueueLast(m[i],&q);
         }

         idx = (QLen) TSTTIMES / 2;
         SAddQueue(n[0],&q,idx);
         SExamQueue(&n[1],&q,idx);
         SRemQueue(&n[2],&q,idx);
         if ( (n[1] != n[0]) || (n[2] != n[0]) )
            SSLOGERROR( ERRCLS_DEBUG, ESS616, 27, "" );
         
         idx = TSTTIMES;
         SAddQueue(n[0],&q,idx);
         SExamQueue(&n[1],&q,idx);
         SRemQueue(&n[2],&q,idx);
         if ( (n[1] != n[0]) || (n[2] != n[0]) )
            SSLOGERROR( ERRCLS_DEBUG, ESS617, 28, "" );
   
         for (i = 0; i < TSTTIMES; i++)
            SPutMsg(m[i]);            
         SPutMsg(n[0]);

         ssTstState = 20;
         break;

      case 20:              /* get message */
         SGetMsg(regionn,pooll,&m[0]);

         SFndLenMsg(m[0],&mlng);
         if ( mlng != 0 )
            SSLOGERROR( ERRCLS_DEBUG, ESS618, 29, "" );
         if (((ret1 = SRemPreMsg(&uData,m[0])) != ROKDNA) ||
            ((ret2 = SRemPstMsg(&uData,m[0])) != ROKDNA))
            SSLOGERROR( ERRCLS_DEBUG, ESS619, 30, "" );
         idx = 0;
         if (((ret1 = SExamMsg(&uData,m[0],(MsgLen)idx)) != ROKDNA) ||
            ((ret2 = SRepMsg(uData,m[0],(MsgLen)idx)) != ROKDNA))
            SSLOGERROR( ERRCLS_DEBUG, ESS620, 31, "" );
   
         SPutMsg(m[0]);   

         ssTstState = 21;
         break;

      case 21:              /* packing and unpacking */
         SGetMsg(regionn,pooll,&m[0]);

         SPkS8((S8) 0x01,m[0]);
         SPkU8((U8) 0x02,m[0]);
         SPkS16((S16) 0x0304,m[0]);
         SPkU16((U16) 0x0506,m[0]);
         SPkS32((S32) 0x0708090aL,m[0]);
         SPkU32((U32) 0x0b0c0d0eL,m[0]);

         SUnpkU32(&u32,m[0]);
         if ( u32 != (U32) 0x0b0c0d0eL )
            SSLOGERROR( ERRCLS_DEBUG, ESS621, 32, "" );
         SUnpkS32(&s32,m[0]);
         if ( s32 != (S32) 0x0708090aL )
            SSLOGERROR( ERRCLS_DEBUG, ESS622, 33, "" );
         SUnpkU16(&u16,m[0]);
         if ( u16 != (U16) 0x0506 )
            SSLOGERROR( ERRCLS_DEBUG, ESS623, 34, "" );
         SUnpkS16(&s16,m[0]);
         if ( s16 != (S16) 0x0304 )
            SSLOGERROR( ERRCLS_DEBUG, ESS624, 35, "" );
         SUnpkU8(&u8,m[0]);
         if ( u8 != (U8) 0x02 )
            SSLOGERROR( ERRCLS_DEBUG, ESS625, 36, "" );
         SUnpkS8(&s8,m[0]);
         if ( s8 != (S8) 0x01 )
            SSLOGERROR( ERRCLS_DEBUG, ESS626, 37, "" );

         SPutMsg(m[0]);

         ssTstState = 22;
         break;

      case 22:              /* add pre message */
         SGetMsg(regionn,pooll,&m[0]);
      
         for ( j = 0; j < mLen; j++ )
            SAddPreMsg((Data) j,m[0]);
         for ( j = 0; j < mLen; j++ )
         {
            SExamMsg(&uData,m[0],(MsgLen) j);
            if ( uData != (Data) ((mLen - 1)-j) )
               SSLOGERROR( ERRCLS_DEBUG, ESS627, 38, "" );
         }

         for ( j = 0; j < mLen; j++ )
            SRepMsg((Data) j,m[0],(MsgLen) j);
         for ( j = 0; j < mLen; j++ )
         {
            SExamMsg(&uData,m[0],(MsgLen) j);
            if ( uData != (Data) j )
               SSLOGERROR( ERRCLS_DEBUG, ESS628, 39, "" );
         }

         SFndLenMsg(m[0],&mlng);
         if ( mlng != mLen )
            SSLOGERROR( ERRCLS_DEBUG, ESS629, 40, "" );

         for ( j = 0; j < mLen; j++ )
         {
            SRemPreMsg(&uData,m[0]); 
            SFndLenMsg(m[0],&mlng);
            if ( (uData != (Data) j) || (mlng != ((mLen - 1)-j)) )
               SSLOGERROR( ERRCLS_DEBUG, ESS630, 41, "" );
         }
    
         SPutMsg(m[0]);

         ssTstState = 23;
         break;

      case 23:              /* add post message */
         SGetMsg(regionn,pooll,&m[0]);
      
         for ( j = 0; j < mLen; j++ )
            SAddPstMsg((Data) j,m[0]);
         for ( j = 0; j < mLen; j++ )
         {
            SExamMsg(&uData,m[0],(MsgLen) j);
            if ( uData != (Data) j )
               SSLOGERROR( ERRCLS_DEBUG, ESS631, 42, "" );
         }
         for ( j = 0; j < mLen; j++ )
            SRepMsg((Data) j,m[0],(MsgLen) ((mLen - 1)-j));
         for ( j = 0; j < mLen; j++ )
         {
            SExamMsg(&uData,m[0],(MsgLen) j);
            if ( uData != (Data) ((mLen - 1)-j) )
               SSLOGERROR( ERRCLS_DEBUG, ESS632, 43, "" );
         }

         SFndLenMsg(m[0],&mlng);
         if ( mlng != mLen )
            SSLOGERROR( ERRCLS_DEBUG, ESS633, 44, "" );
         for ( j = 0; j < mLen; j++ )
         {
            SRemPstMsg(&uData,m[0]); 
            SFndLenMsg(m[0],&mlng);
            if ( (uData != (Data) j) || (mlng != ((mLen - 1)-j)) )
               SSLOGERROR( ERRCLS_DEBUG, ESS634, 45, "" );
         }
    
         SPutMsg(m[0]);
         ssTstState = 24;

         break;

     case 24:              /* initialize message */
         SGetMsg(regionn,pooll,&m[0]);
      
         for ( j = 0; j < mLen; j++ )
            SAddPstMsg((Data) j,m[0]);
         SInitMsg(m[0]);
         SFndLenMsg(m[0],&mlng);
         if( mlng != 0 )
            SSLOGERROR( ERRCLS_DEBUG, ESS635, 46, "" );
         
         if (((ret1 = SRemPreMsg(&uData,m[0])) != ROKDNA) ||
            ((ret2 = SRemPstMsg(&uData,m[0])) != ROKDNA))
            SSLOGERROR( ERRCLS_DEBUG, ESS636, 47, "" );
         idx = 0;
         if (((ret1 = SExamMsg(&uData,m[0],(MsgLen)idx)) != ROKDNA) ||
            ((ret2 = SRepMsg(uData,m[0],(MsgLen)idx)) != ROKDNA))
            SSLOGERROR( ERRCLS_DEBUG, ESS637, 48, "" );
   
         SPutMsg(m[0]);
               
         ssTstState = 25;
         break;
      
      case 25:              /* concatenate message */
         SGetMsg(regionn,pooll,&m[0]);
         SGetMsg(regionn,pooll,&m[1]);
         
         for ( j = 0; j < 2*TSTTIMES; j++ )
         {
            SAddPstMsg((Data) j,m[0]);
            SAddPreMsg((Data) j,m[1]);
         }
         
         for ( i = 0; i <= 1; i++ )
         {
            if ( i == M1M2 )
            {
               SCatMsg(m[0],m[1],i);
               SFndLenMsg(m[0],&mlng);
               SFndLenMsg(m[1],&mlng1);
               if ((mlng != 4*TSTTIMES) || (mlng1 != 0))
                  SSLOGERROR( ERRCLS_DEBUG, ESS638, 49, "" );
               SRemPstMsg(&uData,m[0]);
               if ( uData != (Data) 0 )
                  SSLOGERROR( ERRCLS_DEBUG, ESS639, 50, "" );
               SAddPstMsg(uData,m[0]);
               if (((ret1 = SRemPreMsg(&uData,m[1])) != ROKDNA) ||
                  ((ret2 = SRemPstMsg(&uData,m[1])) != ROKDNA) || (uData != (Data) 0))                  
                  SSLOGERROR( ERRCLS_DEBUG, ESS640, 51, "" );
            }
            else
            {
               SCatMsg(m[1],m[0],i);
               SFndLenMsg(m[0],&mlng);
               SFndLenMsg(m[1],&mlng1);
               if ((mlng1 != 4*TSTTIMES) || (mlng != 0))
                  SSLOGERROR( ERRCLS_DEBUG, ESS641, 52, "" );
               SRemPstMsg(&uData,m[1]);
               if ( uData != (Data) 0 )
                  SSLOGERROR( ERRCLS_DEBUG, ESS642, 53, "" );
               SAddPstMsg(uData,m[1]);
               if (((ret1 = SRemPreMsg(&uData,m[0])) != ROKDNA) ||
                  ((ret2 = SRemPstMsg(&uData,m[0])) != ROKDNA) ||
                  (uData != (Data) 0))                  
                  SSLOGERROR( ERRCLS_DEBUG, ESS643, 54, "" );
            }
         }

         SPutMsg(m[0]);
         SPutMsg(m[1]);
                     
         ssTstState = 26;
         break;

      case 26:              /* segment message */
         SGetMsg(regionn,pooll,&m[0]);

         for ( j = 0; j < 128; j++ )
            SAddPstMsg((Data) j,m[0]);

         idx = 0;
         SSegMsg(m[0],(MsgLen)idx,&m[1]); 
      /* ss021.103 - Addition to test SSwapMsg */
      SSwapMsg(m[0],m[1]);
      SSwapMsg(m[0],m[1]);
         for ( j = 0; j < 128; j++ )
         {
            SExamMsg(&uData,m[1],(MsgLen)j);
            if ( uData != (Data) j )
               SSLOGERROR( ERRCLS_DEBUG, ESS644, 55, "" );
         }
         if ((ret1 = SRepMsg(uData,m[0],(MsgLen)idx)) != ROKDNA)
            SSLOGERROR( ERRCLS_DEBUG, ESS645, 56, "" );

         SPutMsg(m[0]);
                    
         idx = 128;
         SSegMsg(m[1],(MsgLen)idx,&m[0]);
         SFndLenMsg(m[1],&mlng1);
         if ((m[0] != NULLP) || (mlng1 != (MsgLen)idx))
            SSLOGERROR( ERRCLS_DEBUG, ESS646, 57, "" );

         idx = 64;
         SSegMsg(m[1],(MsgLen)idx,&m[0]);
         SFndLenMsg(m[0],&mlng);
         SFndLenMsg(m[1],&mlng1);
         if ((mlng != (MsgLen)idx) || (mlng1 != (MsgLen)idx))
            SSLOGERROR( ERRCLS_DEBUG, ESS647, 58, "" );
         for ( j = 0; j < (S16)(128-idx); j++ )
         {
            SExamMsg(&uData,m[0],(MsgLen) j);
            if ( uData != (Data) (idx+j) )
               SSLOGERROR( ERRCLS_DEBUG, ESS648, 59, "" );
         }
         SCatMsg(m[1],m[0],M1M2);

         SPutMsg(m[0]);

         idx = 63;
         SSegMsg(m[1],(MsgLen)idx,&m[0]);
         SFndLenMsg(m[0],&mlng);
         SFndLenMsg(m[1],&mlng1);
         if ((mlng != (MsgLen)idx+2) || (mlng1 != (MsgLen)idx))
            SSLOGERROR( ERRCLS_DEBUG, ESS649, 60, "" );
         for ( j = 0; j < (S16)(128-idx); j++)
         {
            SExamMsg(&uData,m[0],(MsgLen) j);
            if ( uData != (Data) (idx+j) )
               SSLOGERROR( ERRCLS_DEBUG, ESS650, 61, "" );
         }

         SPutMsg(m[0]);
         SPutMsg(m[1]);

         ssTstState = 27;
         break;
         
      case 27:              /* pack and unpack message */
         SGetMsg(regionn,pooll,&m[0]);
         
         for ( j = 0, sData = 0; j < mLen; j++, sData++ )
            SPkS8((S8) sData,m[0]);
         for ( j = 0; j < mLen; j++ )
         {
            SExamMsg(&sData,m[0],(MsgLen) j);
            if ( sData != (Data) ((mLen - 1)-j) )
               SSLOGERROR( ERRCLS_DEBUG, ESS651, 62, "" );
         }
         for ( j = 0; j < mLen; j++ )
         {
            SUnpkS8(&s8,m[0]);
            if ( s8 != (S8) ((mLen - 1)-j) )
               SSLOGERROR( ERRCLS_DEBUG, ESS652, 63, "" );
         }

         SPutMsg(m[0]);

         ssTstState = 28;
         break;

      case 28:              /* pack and unpack message */
         SGetMsg(regionn,pooll,&m[0]);
         
         for ( j = 0, uData = (Data) 0; j < mLen; j++, uData++ )
            SPkU8((U8) uData,m[0]);
         for ( j = 0; j < mLen; j++ )
         {
            SExamMsg(&uData,m[0],(MsgLen) j);
            if ( uData != (Data)((mLen - 1)-j) )
               SSLOGERROR( ERRCLS_DEBUG, ESS653, 64, "" );
         }
         for ( j = 0; j < mLen; j++ )
         {        
            SUnpkU8(&uData,m[0]);
            if ( uData != (Data)((mLen - 1)-j) )
               SSLOGERROR( ERRCLS_DEBUG, ESS654, 65, "" );
         }

         SPutMsg(m[0]);

         ssTstState = 29;
         break;

      case 29:              /* compress message */
         SGetMsg(regionn,pooll,&m[0]);

         for ( j = 0; j < mLen; j++ )
            SAddPreMsg((Data) j,m[0]);

         SCompressMsg(m[0]);

         for ( j = 0; j < mLen; j++ )
         {
            SExamMsg(&uData,m[0],(MsgLen) j);
            if ( uData != (Data) ((mLen - 1)-j) )
               SSLOGERROR( ERRCLS_DEBUG, ESS655, 66, "" );
         }

         SPutMsg(m[0]);

         ssTstState = 30;
         break;
        
      case 30:              /* copy message to message */
         SGetMsg(regionn,pooll,&m[0]);
      
         for ( j = 0; j < mLen; j++ )
            SAddPreMsg((Data) j,m[0]);

         SCpyMsgMsg(m[0],regionn,pooll,&m[1]);

         for ( j = 0; j < mLen; j++ )
         {
            SExamMsg(&uData,m[1],(MsgLen) j);
            if ( uData != (Data) ((mLen - 1)-j) )
               SSLOGERROR( ERRCLS_DEBUG, ESS656, 67, "" );
         }

         SPutMsg(m[0]);
         SPutMsg(m[1]);

         /* ss036.103 - addition to take the SSI enhancement related testcases */
#ifdef SSI_DEBUG_LEVEL1
         ssTstState = 31;
#else
         ssTstState = 40;
#endif /* SSI_DEBUG_LEVEL1 */
         break;
/* ss036.103 - addition of test cases for SSI enhancements */
#ifdef SSI_DEBUG_LEVEL1
      case 31:           /* memory trampling in bucket */
      {
         /* allocate TSTSTIMES mem blocks */
         for (i = 0; i < TSTTIMES; i++)
         {
            SGetMsg(regionn,pooll,&m[i]);
         }

         if (ssTstCnt == 1)
         {
            /* choose the 4th, 5th, 6th and 7th block */
            for (s16 = 4; s16 < 8; s16++)
            {
               s = (Data *)(m[s16]) - BKTMEMBLKHDRSIZE;
            #ifdef DEBUGP
               sprintf(prntBuf, "\n[31]Block at %8p is Trampled\n", s);
               SDisplay(0,prntBuf);
            #endif /* DEBUGP */
               /* trample it by accessing the 5th block */
               for (i=0; i < BKTMEMBLKHDRSIZE; i++, s++)
              {
                 *s = 0;
              }
            }
         }

         /* free TSTTIMES mem blocks */
         for (i = 0; i < TSTTIMES; i++)
         {
            SPutMsg(m[i]);
         }

      #ifdef DEBUGP
         if (ssTstCnt == 1)
         {
            SPrintRegMemProfile(regionn);
            SPrintRegMemStatusInfo(regionn, SS_MEM_BLK_SIZE_PROFILE);
            SPrintRegMemStatusInfo(regionn, SS_MEM_BKT_ALLOC_PROFILE);
         }
      #endif /* DEBUGP */

         ssTstState = 32;
         break;
      }

      case 32:           /* memory trampling in heap */
      {
         /* allocate TSTSTIMES mem blocks */
         for ( j = 0; j < TSTTIMES; j++ )
         {
            /* Get static buffer from static memory */
            SGetSBuf(regionn, sPool, &sBuf[j], (Size) HEAPMEMSAMPLESIZE);
         }

         if (ssTstCnt == 1)
         {
            /* choose the 5th, 6th, 7th and 8th block */
            for (s16 = 5; s16 < 9; s16++)
            {
               s = (Data *)(sBuf[s16]) - HEAPMEMBLKHDRSIZE;
            #ifdef DEBUGP
               sprintf(prntBuf, "\n[32]Block at %8p is Trampled\n", s);
               SDisplay(0,prntBuf);
            #endif /* DEBUGP */
               /* trample it by accessing the 5th block */
               for (i=0; i < HEAPMEMBLKHDRSIZE; i++, s++)
               {
                  *s = 0;
               }
            }
         }

         for ( j = 0; j < TSTTIMES; j++ )
         {
            /* Put static buffer to static memory */
            SPutSBuf(regionn, sPool, sBuf[j], (Size) HEAPMEMSAMPLESIZE);
         }

      #ifdef DEBUGP
         if (ssTstCnt == 1)
         {
            SPrintRegMemProfile(regionn);
            SPrintRegMemStatusInfo(regionn, SS_MEM_BLK_SIZE_PROFILE);
            SPrintRegMemStatusInfo(regionn, SS_MEM_BKT_ALLOC_PROFILE);
         }
      #endif /* DEBUGP */

         ssTstState = 33;
         break;
      }

      case 33:           /* double deallocation in heap */
      {

         if (ssTstCnt == 1)
         {
            SGetSBuf(regionn, sPool, &sBuf[0], (Size) HEAPMEMSAMPLESIZE);

            /* free the memory */
            ret1 = SPutSBuf(regionn, sPool, sBuf[0], (Size) HEAPMEMSAMPLESIZE);
            if (ret1 == ROK)
            {
               /* Double free */
               ret1 = SPutSBuf(regionn, sPool, sBuf[0], (Size) HEAPMEMSAMPLESIZE);
               if (ret1 == RDBLFREE)
               {
               #ifdef DEBUGP
                  sprintf(prntBuf, "\n[33]Double Deallocation in heap at %8p is caught\n", sBuf[0]);
                  SDisplay(0,prntBuf);
               #endif /* DEBUGP */
               }
            }
         }

         ssTstState = 34;
         break;
      }

      case 34:           /* double deallocation in bucket */
      {

         if (ssTstCnt == 1)
         {
            SGetMsg(regionn,pooll,&m[0]);

            /* free the memory */
            ret1 = SPutMsg(m[0]);
            if (ret1 == ROK)
            {
               /* Double free, a print will be printed in SRegMemErrHdlr */
               ret1 = SPutMsg(m[0]);
               if (ret1 == ROK)
               {
               #ifdef DEBUGP
                  sprintf(prntBuf, "\n[34]Double Deallocation in bucket at %8p is caught\n", m[0]);
                  SDisplay(0,prntBuf);
               #endif /* DEBUGP */
               }
            }
         }

         ssTstState = 40;
         break;
      }
#endif /* SSI_DEBUG_LEVEL1 */

      case 40:
#ifndef SS_NIC
         SDisInt();
         SHoldInt();
         SRelInt();
         SEnbInt();
#endif /* SS_NIC */
         ssTstState = 41;
         break;

      case 41:
#ifndef SS_NIC
         SDisInt();
         SDisInt();
         SDisInt();
         SEnbInt();
         SEnbInt();
         SEnbInt();
#endif /* SS_NIC */
         ssTstState = 42;
         break;

      case 42:
#ifndef WIN32
#ifndef UNIX
         vectNmb = 0;
         SGetVect(vectNmb, &vectFnct);
         SPutVect(vectNmb, vectFnct);
         SGetVect(vectNmb, &vectFnct1);
         if ( vectFnct1 != vectFnct )
            SSLOGERROR( ERRCLS_DEBUG, ESS657, 68, "" );
#endif /* UNIX */
#endif /* WIN32 */

         ssTstState = 50;
         break;
            
      case 50:    /* get system time */
         SGetSysTime(&sysTime2);
         if ( sysTime2 == sysTime1 )
         {
            /* ss026.103 - Modification to adjust test case */
            if (sysTimeCnt >= 1000)
               SSLOGERROR( ERRCLS_DEBUG, ESS658, 69, "" );
            else
               sysTimeCnt++;
         }
         else
         {
            SGetSysTime(&sysTime1);
            sysTimeCnt = 0;
         }

         ssTstState = 51;
         break;

      case 51:    /* check resources */
         SGetMsg(regionn,pooll,&m[0]);

         SChkRes(regionn, pooll, &status);
         if ( status == 0 )
            SSLOGERROR( ERRCLS_DEBUG, ESS659, 70, "" );

         SPutMsg(m[0]);

         ssTstState = 52;
         break;

      case 52:     /* test random number generator */
         SRandom(&value2);
         if ( value2 == value1 )
         {
             if (valueCnt >= 100)
                SSLOGERROR( ERRCLS_DEBUG, ESS660, 71, "" );
             else
                valueCnt++;
         }
         else
         {
            SRandom(&value1);
            valueCnt = 0;
         }

         ssTstState = 63;
         break;

      case 53:    /* set date time and get date time */

         if ((ret1 = SGetDateTime(&dt)) != ROK)
            SSLOGERROR( ERRCLS_DEBUG, ESS661, 72, "" );

         ssTstState = 60;
         break;

      case 60:     /* get even size static memory, alternating */

         for ( j = 0; j < TSTTIMES; j++ )
         {
            /* Get static buffer from static memory */
            SGetSBuf(regionn, sPool, &sBuf[j], (Size) MAXSMEMLEN);

            s = sBuf[j];
            for (i = 0; i < MAXSMEMLEN; i++)
            {
               *s = (Data) j;
               s++;
            }

            s = sBuf[j];
            for (i = 0; i < MAXSMEMLEN; i++)
            {
               if (*s != (Data) j)
                  SSLOGERROR( ERRCLS_DEBUG, ESS662, 73, "" );
               s++;
            }

            /* Put static buffer to static memory */
            SPutSBuf(regionn, sPool, sBuf[j], (Size) MAXSMEMLEN);
         }

         ssTstState = 61;
         break;

      case 61:     /* get even size static memory, consecutive */

         for ( j = 0; j < TSTTIMES; j++ )
         {
            /* Get static buffer from static memory */
            SGetSBuf(regionn, sPool, &sBuf[j], (Size) MAXSMEMLEN);

            s = sBuf[j];
            for (i = 0; i < MAXSMEMLEN; i++)
            {
               *s = (Data) j;
               s++;
            }
         }

         for ( j = 0; j < TSTTIMES; j++ )
         {
            s = sBuf[j];
            for (i = 0; i < MAXSMEMLEN; i++)
            {
               if (*s != (Data) j)
                  SSLOGERROR( ERRCLS_DEBUG, ESS663, 74, "" );
               s++;
            }

            /* Put static buffer to static memory */
            SPutSBuf(regionn, sPool, sBuf[j], (Size) MAXSMEMLEN);
         }

         ssTstState = 62;
         break;

      case 62:     /* get odd size static memory, alternating */

         for ( j = 0; j < TSTTIMES; j++ )
         {
            /* Get static buffer from static memory */
            SGetSBuf(regionn, sPool, &sBuf[j], (Size) (MAXSMEMLEN - 1));

            s = sBuf[j];
            for (i = 0; i < (MAXSMEMLEN - 1); i++)
            {
               *s = (Data) j;
               s++;
            }

            s = sBuf[j];
            for (i = 0; i < (MAXSMEMLEN - 1); i++)
            {
               if (*s != (Data) j)
                  SSLOGERROR( ERRCLS_DEBUG, ESS664, 75, "" );
               s++;
            }

            /* Put static buffer to static memory */
            SPutSBuf(regionn, sPool, sBuf[j], (Size) (MAXSMEMLEN - 1));
         }

         ssTstState = 63;
         break;

      case 63:     /* get odd size static memory, consecutive */

         for ( j = 0; j < TSTTIMES; j++ )
         {
            /* Get static buffer from static memory */
            SGetSBuf(regionn, sPool, &sBuf[j], (Size) (MAXSMEMLEN - 1));

            s = sBuf[j];
            for (i = 0; i < (MAXSMEMLEN - 1); i++)
            {
               *s = (Data) j;
               s++;
            }
         }

         for ( j = 0; j < TSTTIMES; j++ )
         {
            s = sBuf[j];
            for (i = 0; i < (MAXSMEMLEN - 1); i++)
            {
               if (*s != (Data) j)
                  SSLOGERROR( ERRCLS_DEBUG, ESS665, 76, "" );
               s++;
            }

            /* Put static buffer to static memory */
            SPutSBuf(regionn, sPool, sBuf[j], (Size) (MAXSMEMLEN - 1));
         }

         ssTstState = 70;
         break;

      case 70:
  /* ss016.13: Addition */
#if defined(SS_VW) && defined(SS_ZEROCOPY)
           if (tstZeroCopyTrans() != ROK)
           {
              SSLOGERROR( ERRCLS_DEBUG, ESS666, ERRZERO, "" );
           }
#endif
         ssTstState = 71;
         break;

      case 71:

         if (tskTmrCnt[0] == 0)
         {
            if (tmrTimeCnt[0] > (1000 * TSK1TMR))
               SSLOGERROR( ERRCLS_DEBUG, ESS667, 77, "" );
            else
               tmrTimeCnt[0]++;
         }
         else
            tmrTimeCnt[0] = 0;
 
         ssTstState = 72;
         break;

      case 72:
         if (tskTmrCnt[1] == 0)
         {
            if (tmrTimeCnt[1] > (200 * TSK2TMR))
               SSLOGERROR( ERRCLS_DEBUG, ESS668, 78, "" );
            else
               tmrTimeCnt[1]++;
         }
         else
            tmrTimeCnt[1] = 0;

         ssTstState = 73;
         break;

      case 73:
/* ss029.103: modification: SFndProcId is not supported in multiple procs case */ 
#ifndef SS_MULTIPLE_PROCS
         if(osCp.procId != SFndProcId())
            SSLOGERROR( ERRCLS_DEBUG, ESS669, 79, "" );
#endif /* SS_MULTIPLE_PROCS */

         ssTstState = 80;
         break;

      case 80:
      {
         PRIVATE Prior pr = 0;

         /* Get message */
         SGetMsg(regionn, pooll, &m[0]);
  
         /* Add Data to end of message */
         for (i = 0; i < mLen; i++)
            SAddPstMsg((Data) i, m[0]);

         /* Post the message to the first test task */
         ourPst.event     = 0;               /* event */
         ourPst.prior     = pr;              /* priority */
         ourPst.route     = 0;               /* route */
         ourPst.dstProcId = SFndProcId();    /* destination processor id */
         ourPst.dstEnt    = TST0ENT;         /* destination entity */
         ourPst.dstInst   = TSTINST0;        /* destination instance */
         ourPst.srcProcId = SFndProcId();    /* source processor id */
         ourPst.srcEnt    = TSTPERMENT;      /* source entity */
         ourPst.srcInst   = TSTINST0;        /* source instance */
         if (SPstTsk(&ourPst, m[0]) != ROK)
         {
            SSLOGERROR( ERRCLS_DEBUG, ESS670, ERRZERO, "" );
         }

         /* Upon receipt of the message the first test task will post the
            message to the second test task which will then put the message
            back to memory */

         pr++;
         if (pr == NMBPRIOR)
            pr = 0;
         ssTstState = 81;
         break;
      }
      case 81:
         /* wait for test task 0 (tst0ActvTskXXX) to modify "ssTstState" */
         break;

      case 82:
         /* wait for test task 1 (tst1ActvTskXXX) to modify "ssTstState" */
         break;

      case 83:
         /* wait for test task 2 (tst2ActvTskXXX) to modify "ssTstState" */
         break;

      case 84:
         SInitQueue(&q);
         SGetMsg(regionn,pooll,&m[0]);
         SGetMsg(regionn,pooll,&m[1]);
         SQueueLast(m[0],&q);
         SQueueLast(m[1],&q);
         idx = 0;
         ret1 = SRemQueue(&bufPtr, &q, 0);
         if (ret1 != ROK)
            SSLOGERROR( ERRCLS_DEBUG, ESS671, 79, "" );
         if (bufPtr != m[0])
            SSLOGERROR( ERRCLS_DEBUG, ESS672, 80, "" );
         SPutMsg(bufPtr);
         ret1 = SRemQueue(&bufPtr, &q, 0);
         if (ret1 != ROK)
            SSLOGERROR( ERRCLS_DEBUG, ESS673, 81, "" );
         if (bufPtr != m[1])
            SSLOGERROR( ERRCLS_DEBUG, ESS674, 82, "" );
         SPutMsg(bufPtr);

         ssTstState = 85;
         break;

      case 85:
         SInitQueue(&q);
         SGetMsg(regionn,pooll,&m[0]);
         SGetMsg(regionn,pooll,&m[1]);
         SQueueLast(m[0],&q);
         SQueueLast(m[1],&q);
         idx = 0;
         ret1 = SRemQueue(&bufPtr, &q, 1);
         if (ret1 != ROK)
            SSLOGERROR( ERRCLS_DEBUG, ESS675, 83, "" );
         if (bufPtr != m[1])
            SSLOGERROR( ERRCLS_DEBUG, ESS676, 84, "" );
         SPutMsg(bufPtr);
         ret1 = SRemQueue(&bufPtr, &q, 0);
         if (ret1 != ROK)
            SSLOGERROR( ERRCLS_DEBUG, ESS677, 85, "" );
         if (bufPtr != m[0])
            SSLOGERROR( ERRCLS_DEBUG, ESS678, 86, "" );
         SPutMsg(bufPtr);

         ssTstState = 86;
         break;

      case 86:
         SGetMsg(regionn,pooll,&m[0]);
         for ( j = 0; j < 6; j++ )
            SAddPstMsg((Data) j,m[0]);
         for ( j = 0; j < 3; j++ )
            SAddPreMsg((Data) j,m[0]);
         SSegMsg(m[0],8,&m[1]); 
         if(SFndLenMsg(m[0],&mlng) != ROK || mlng != 8)
            SSLOGERROR( ERRCLS_DEBUG, ESS679, 94, "" );
         if(SExamMsg(&uData,m[0],(MsgLen) 0) != ROK || uData != (Data) 2 ||
            SExamMsg(&uData,m[0],(MsgLen) 1) != ROK || uData != (Data) 1 ||
            SExamMsg(&uData,m[0],(MsgLen) 2) != ROK || uData != (Data) 0 ||
            SExamMsg(&uData,m[0],(MsgLen) 3) != ROK || uData != (Data) 0 ||
            SExamMsg(&uData,m[0],(MsgLen) 4) != ROK || uData != (Data) 1 ||
            SExamMsg(&uData,m[0],(MsgLen) 5) != ROK || uData != (Data) 2 ||
            SExamMsg(&uData,m[0],(MsgLen) 6) != ROK || uData != (Data) 3 ||
            SExamMsg(&uData,m[0],(MsgLen) 7) != ROK || uData != (Data) 4)
            SSLOGERROR( ERRCLS_DEBUG, ESS680, 95, "" );
         if(m[1] == NULLP)
            SSLOGERROR( ERRCLS_DEBUG, ESS681, 96, "" );
         SPutMsg(m[0]);
         SPutMsg(m[1]);

         ssTstState = 87;
         break;

      case 87:
         SGetMsg(regionn,pooll,&m[0]);
         for ( j = 0; j < 15; j++ )
            SAddPreMsg((Data) j,m[0]);
         for ( j = 0; j < 23; j++ )
            SAddPstMsg((Data) j,m[0]);
         SSegMsg(m[0],28,&m[1]); 
         if(SFndLenMsg(m[0],&mlng) != ROK || mlng != 28)
            SSLOGERROR( ERRCLS_DEBUG, ESS682, 97, "" );
         if(SExamMsg(&uData,m[0],(MsgLen)  0) != ROK || uData != (Data) 14 ||
            SExamMsg(&uData,m[0],(MsgLen)  1) != ROK || uData != (Data) 13 ||
            SExamMsg(&uData,m[0],(MsgLen)  2) != ROK || uData != (Data) 12 ||
            SExamMsg(&uData,m[0],(MsgLen)  3) != ROK || uData != (Data) 11 ||
            SExamMsg(&uData,m[0],(MsgLen)  4) != ROK || uData != (Data) 10 ||
            SExamMsg(&uData,m[0],(MsgLen)  5) != ROK || uData != (Data)  9 ||
            SExamMsg(&uData,m[0],(MsgLen)  6) != ROK || uData != (Data)  8 ||
            SExamMsg(&uData,m[0],(MsgLen)  7) != ROK || uData != (Data)  7 ||
            SExamMsg(&uData,m[0],(MsgLen)  8) != ROK || uData != (Data)  6 ||
            SExamMsg(&uData,m[0],(MsgLen)  9) != ROK || uData != (Data)  5 ||
            SExamMsg(&uData,m[0],(MsgLen) 10) != ROK || uData != (Data)  4 ||
            SExamMsg(&uData,m[0],(MsgLen) 11) != ROK || uData != (Data)  3 ||
            SExamMsg(&uData,m[0],(MsgLen) 12) != ROK || uData != (Data)  2 ||
            SExamMsg(&uData,m[0],(MsgLen) 13) != ROK || uData != (Data)  1 ||
            SExamMsg(&uData,m[0],(MsgLen) 14) != ROK || uData != (Data)  0 ||
            SExamMsg(&uData,m[0],(MsgLen) 15) != ROK || uData != (Data)  0 ||
            SExamMsg(&uData,m[0],(MsgLen) 16) != ROK || uData != (Data)  1 ||
            SExamMsg(&uData,m[0],(MsgLen) 17) != ROK || uData != (Data)  2 ||
            SExamMsg(&uData,m[0],(MsgLen) 18) != ROK || uData != (Data)  3 ||
            SExamMsg(&uData,m[0],(MsgLen) 19) != ROK || uData != (Data)  4 ||
            SExamMsg(&uData,m[0],(MsgLen) 20) != ROK || uData != (Data)  5 ||
            SExamMsg(&uData,m[0],(MsgLen) 21) != ROK || uData != (Data)  6 ||
            SExamMsg(&uData,m[0],(MsgLen) 22) != ROK || uData != (Data)  7 ||
            SExamMsg(&uData,m[0],(MsgLen) 23) != ROK || uData != (Data)  8 ||
            SExamMsg(&uData,m[0],(MsgLen) 24) != ROK || uData != (Data)  9 ||
            SExamMsg(&uData,m[0],(MsgLen) 25) != ROK || uData != (Data) 10 ||
            SExamMsg(&uData,m[0],(MsgLen) 26) != ROK || uData != (Data) 11 ||
            SExamMsg(&uData,m[0],(MsgLen) 27) != ROK || uData != (Data) 12)
            SSLOGERROR( ERRCLS_DEBUG, ESS683, 98, "" );
         if(SFndLenMsg(m[1],&mlng) != ROK || mlng != 10)
            SSLOGERROR( ERRCLS_DEBUG, ESS684, 99, "" );
         if(SExamMsg(&uData,m[1],(MsgLen)  0) != ROK || uData != (Data) 13 ||
            SExamMsg(&uData,m[1],(MsgLen)  1) != ROK || uData != (Data) 14 ||
            SExamMsg(&uData,m[1],(MsgLen)  2) != ROK || uData != (Data) 15 ||
            SExamMsg(&uData,m[1],(MsgLen)  3) != ROK || uData != (Data) 16 ||
            SExamMsg(&uData,m[1],(MsgLen)  4) != ROK || uData != (Data) 17 ||
            SExamMsg(&uData,m[1],(MsgLen)  5) != ROK || uData != (Data) 18 ||
            SExamMsg(&uData,m[1],(MsgLen)  6) != ROK || uData != (Data) 19 ||
            SExamMsg(&uData,m[1],(MsgLen)  7) != ROK || uData != (Data) 20 ||
            SExamMsg(&uData,m[1],(MsgLen)  8) != ROK || uData != (Data) 21 ||
            SExamMsg(&uData,m[1],(MsgLen)  9) != ROK || uData != (Data) 22)
            SSLOGERROR( ERRCLS_DEBUG, ESS685, 100, "" );
         SPutMsg(m[0]);
         SPutMsg(m[1]);

         ssTstState = 91;
         break;

      case 91:
      {
         PRIVATE S16 cnt = 5;
/* ss029.103: modification: procId parameter added */ 
#ifdef SS_MULTIPLE_PROCS
         SRegTmr(PROC_MP_ID0, TST1ENT, TSTINST0, cnt, tst1fnc);
         if(SDeregTmr(PROC_MP_ID0, TST1ENT, TSTINST0, cnt, tst1fnc) != ROK )
#else /* SS_MULTIPLE_PROCS */
         SRegTmr(TST1ENT, TSTINST0, cnt, tst1fnc);
         if( SDeregTmr(TST1ENT, TSTINST0, cnt, tst1fnc) != ROK )
#endif /* SS_MULTIPLE_PROCS */
         {
            SSLOGERROR( ERRCLS_DEBUG, ESS686, ERRZERO, "" );
         }
         cnt = (cnt == 5)?20:5;

 /* ss002.13: addition */
         ssTstState = 92;
         break;
      }
  /* ss002.13: addition  */
      case 92:  /* Test for SAddPstMsgMult  */             
      {
      SGetMsg(regionn,pooll,&m[0]);
      
         for (j = 0; j< BSIZE; j++)
      src[j] = j; 
      SAddPstMsgMult(src, BSIZE, m[0]);

         for ( j = 0; j < BSIZE; j++ ) 
         {
            SExamMsg(&uData,m[0],(MsgLen) j);
            if ( uData != (Data) j )
               SSLOGERROR( ERRCLS_DEBUG, ESS687, 0, "SAddPstMsgMult Test:failure in adding string of bytes to the end of message " );
         }

         for (j = 0; j< BSIZE; j++)
      src[j] = ((BSIZE - 1 ) - j); 

      SAddPstMsgMult(src, BSIZE, m[0]);
        
         for ( j = 0; j < BSIZE; j++ ) 
         {
            SExamMsg(&uData,m[0],(MsgLen) (j + BSIZE) );
            if ( uData != (Data) src[j] )
               SSLOGERROR( ERRCLS_DEBUG, ESS688, 0, "SAddPstMsgMult Test: failure in adding string of bytes to the end of message" );
         }

         SFndLenMsg(m[0],&mlng);
         if ( mlng != 2*BSIZE )
            SSLOGERROR( ERRCLS_DEBUG, ESS689, 0, "SAddPstMsgMult Test: failure in adding string of bytes to the end of message" );
        
         SRemPstMsgMult(src,BSIZE,m[0]);

         SFndLenMsg(m[0],&mlng);

         if ( mlng != BSIZE )
            SSLOGERROR( ERRCLS_DEBUG, ESS690, 0, "" );
    
         for ( j = 0; j < BSIZE; j++ ) 
         {
            SExamMsg(&uData,m[0],(MsgLen) j);
            if ( uData != (Data) j )
               SSLOGERROR( ERRCLS_DEBUG, ESS691, 0, " SAddPstMsgMult Test: failure in removing the string of bytes at the end of the message" );
         }
         SPutMsg(m[0]);
      
         ssTstState = 93;
         break;

        }


      case 93:  /* Test for SGetPstMsgMult */            
      {
      SGetMsg(regionn,pooll,&m[0]);
      
         SGetPstMsgMult(BSIZE, m[0]);

         for ( j = 0; j < BSIZE; j++ ) 
         {
            SExamMsg(&uData,m[0],(MsgLen) j);
            if ( uData != (Data) 0 )
               SSLOGERROR( ERRCLS_DEBUG, ESS692, 0, " SGetPstMsgMult Test: Failure in appending null array" );
         }

         SGetPstMsgMult(BSIZE, m[0]);
        
         for ( j = 0; j < BSIZE; j++ ) 
         {
            SExamMsg(&uData,m[0],(MsgLen) (j + BSIZE) );
            if ( uData != (Data) '\0' )
               SSLOGERROR( ERRCLS_DEBUG, ESS693, 0, "SGetPstMsgMult Test: Failure in appending null array");
         }

         SFndLenMsg(m[0],&mlng);
         if ( mlng != 2*BSIZE )
            SSLOGERROR( ERRCLS_DEBUG, ESS694, 0, " SGetPstMsgMult Test: failure in appending null array" );
        
           SRemPstMsgMult(src,BSIZE,m[0]);

         SFndLenMsg(m[0],&mlng);

         if ( mlng != BSIZE )
            SSLOGERROR( ERRCLS_DEBUG, ESS695, 0, " SGetPstMsgMult Test: Failure in removing null array from the message" );


         SPutMsg(m[0]);
      
         ssTstState = 94;
         break;

     }


      case 94:    /*  Test for SRemPreMsgMult  */
         SGetMsg(regionn,pooll,&m[0]);
      
         for ( j = 0; j < BSIZE; j++ )
           src[j] = j;
     
      SAddPreMsgMult(src,BSIZE,m[0]);
 
         for ( j = 0; j < BSIZE; j++ )
         {
            SExamMsg(&uData,m[0],(MsgLen) j);
            if ( uData != (Data) ((BSIZE - 1)-j) )
               SSLOGERROR( ERRCLS_DEBUG, ESS696, 0, "SRemPreMsgMult Test: Failure in adding multiple bytes to the beginning of message" );
         }

         SFndLenMsg(m[0],&mlng);
         if ( mlng != BSIZE )
            SSLOGERROR( ERRCLS_DEBUG, ESS697, 0, "SRemPreMsgMult Test: Failure in adding multiple bytes to the beginning of message" );

      SRemPreMsgMult(src,BSIZE,m[0]);

         SFndLenMsg(m[0],&mlng);
         if ( mlng != 0 )
            SSLOGERROR( ERRCLS_DEBUG, ESS698, 0, "SRemPreMsgMult Test: Failure in removing multiple bytes from the beginning of message" );
         
      for ( j = 0; j < BSIZE; j++ )
         {
            if ( src[j] != (Data) ((BSIZE - 1)-j) )
               SSLOGERROR( ERRCLS_DEBUG, ESS699, 0, "" );
         }
    
         SPutMsg(m[0]);
 /* ss005.13: addition */
         ssTstState = 95;
         break;

 /* ss005.13: addition */
     case 95:
        {
#ifdef UNIX
        double t1,t2;

        /*  mytime2 = time(NULL); */
 /* ss017.13: addition */
#ifndef SS_LINUX
           clock_gettime(CLOCK_REALTIME, &mytime2);
#else
           gettimeofday(&mytimeval2,NULL);
           mytime2.tv_sec = mytimeval2.tv_sec;
           mytime2.tv_nsec= mytimeval2.tv_usec * 1000;
#endif

           t1 = ((double) mytime1.tv_sec * (double) 1000000000 + (double) mytime1.tv_nsec);
           t2 = ((double) mytime2.tv_sec * (double) 1000000000 + (double) mytime2.tv_nsec);
           t2 = (t2-t1)/(double)1000000000;
           time_int = (U32) t2;
           if ((time_int) ==  10)        
           {
              SGetSysTime(&Time2);
              /* ss026.103 - Modification to adjust test case */
              if ( ( (Time2-Time1) > 105) || ( (Time2-Time1) < 95) )
              {
/*ss013.301: Fixed Warnings for 32/64 bit compilation*/
#ifdef ALIGN_64BIT
                  printf("\nss_acc: Difference between MTSS Ticks and Unix Ticks. MTSS ticks = %d\n", Time2-Time1 );
#else
                  printf("\nss_acc: Difference between MTSS Ticks and Unix Ticks. MTSS ticks = %ld\n", Time2-Time1 );
#endif 
                 /*  SSLOGERROR( ERRCLS_DEBUG, ESS700, 0, "Error in SGetSysTime computation"); */
              }
              Time1 = Time2;
              mytime1.tv_sec  = mytime2.tv_sec;
               mytime1.tv_nsec  = mytime2.tv_nsec;
           }
#endif /* UNIX */
 /* ss006.13: addition */
#ifdef SS_RTR_SUPPORT
         ssTstState = 96;
#else
#ifndef SS_MULTICORE_SUPPORT
         ssTstState = 121;
#else
      ssTstState = 101;
#endif /* SS_MULTICORE_SUPPORT */
#endif /* SS_RTR_SUPPORT */

          break;
        }
 /* ss010.13: addition */
#ifdef SS_RTR_SUPPORT
        case 96:
        {
           /* Register the router function */
           rte[0] = RTESPEC;
           rte[1] = RTEFRST;
           SRegRtrTsk(rte, 2, tstRtrTsk);

           /* Get message */
           SGetMsg(regionn, pooll, &m[0]);
  
           /* Add Data to end of message */
           for (i = 0; i < 10; i++)
              SAddPstMsg((Data) i, m[0]);

           /* Post the message to the first test task */
           ourPst.event     = 0;               /* event */
           ourPst.prior     = 0;              /* priority */
           ourPst.route     = RTESPEC;               /* route */
           ourPst.dstProcId = SFndProcId();    /* destination processor id */
           /* ss019.103 - Modification to test router task */
           ourPst.dstEnt    = TST3ENT + 1;     /* destination entity */
           ourPst.dstInst   = TSTINST0 + 1;    /* destination instance */
           ourPst.srcProcId = SFndProcId();    /* source processor id */
           ourPst.srcEnt    = TSTPERMENT;      /* source entity */
           ourPst.srcInst   = TSTINST0;        /* source instance */
           if (SPstTsk(&ourPst, m[0]) != ROK)
           {
              SSLOGERROR( ERRCLS_DEBUG, ESS701, ERRZERO, "" );
           }
           ssTstState = 97;
           break;
         }
         case 97:
           /* wait for test task 3 (tst3ActvTskXXX) to modify "ssTstState" */
           break;
         case 98:
         {
           /* De-Register a router function */
           SDeregRtrTsk(rte, 2);

           /* Get message */
           SGetMsg(regionn, pooll, &m[0]);
  
           /* Add Data to end of message */
           for (i = 0; i < 10; i++)
              SAddPstMsg((Data) i, m[0]);

           /* Post the message to the first test task */
           ourPst.event     = 0;               /* event */
           ourPst.prior     = 0;              /* priority */
        /* ss021.103 - Modification to set route properly */
           ourPst.route     = RTEALL;               /* route */
           ourPst.dstProcId = SFndProcId();    /* destination processor id */
           ourPst.dstEnt    = TST3ENT;         /* destination entity */
           ourPst.dstInst   = TSTINST0;        /* destination instance */
           ourPst.srcProcId = SFndProcId();    /* source processor id */
           ourPst.srcEnt    = TSTPERMENT;      /* source entity */
           ourPst.srcInst   = TSTINST0;        /* source instance */
           if (SPstTsk(&ourPst, m[0]) != ROK)
           {
              SSLOGERROR( ERRCLS_DEBUG, ESS702, ERRZERO, "" );
           }
           ssTstState = 99;
         break;
        }
         case 100:
           /* wait for test task 3 (tst3ActvTskXXX) to modify "ssTstState" */
           break;
#endif /* SS_RTR_SUPPORT */
 /* addition for Multicore specific changes */
#ifdef SS_MULTICORE_SUPPORT
        case 101:     /* Test SRegCpuInfo with Number of cores set to zero */
        {
          if (ssTstCnt == 1) {
                SCpuInfo cpuInfo = { 0, 2, {0,1,2,1,0,1,2,1}};
                if (SRegCpuInfo(&cpuInfo) != ROK)
                {
                     SSLOGERROR( ERRCLS_DEBUG, ESS703, ERRZERO, "SRegCpuinfo failed because of Invalid number of cores\n");      
                }
          }
          ssTstState = 102;
          break;
        }
        case 102:     /* Test SRegCpuInfo with Number of cores set to > SS_MAX_CORES */
        {
          if (ssTstCnt == 1) {
                SCpuInfo cpuInfo = { 69, 2, {0,1,2,1,0,1,2,1}};
                if (SRegCpuInfo(&cpuInfo) != ROK)
                {
                       SSLOGERROR( ERRCLS_DEBUG, ESS704, ERRZERO, "SRegCpuinfo failed because of Invalid number of cores\n"); 
                }
          }
          ssTstState = 103;
          break;
        }
        case 103:     /* Test SRegCpuInfo with Number of threads per core set to -1 */
        {
          if (ssTstCnt == 1) {
                SCpuInfo cpuInfo = { 8, -1, {0,1,2,1,0,1,2,1}};
                if (SRegCpuInfo(&cpuInfo) != ROK)
                {
               SSLOGERROR( ERRCLS_DEBUG, ESS705, ERRZERO, "SRegCpuinfo failed because of Invalid number of cores\n"); 
                }
          }
          ssTstState = 104;
          break;
        }
        case 104:     /* Test SRegCpuInfo with all Valid values */
        {
          if (ssTstCnt == 1) {
                SCpuInfo cpuInfo = { 8, 2, {0,1,2,1,2,1,2,1}};
                int loopCounter;
                if (SRegCpuInfo(&cpuInfo) != ROK)
                {
                        SSLOGERROR( ERRCLS_DEBUG, ESS706, ERRZERO, "SRegCpuinfo failed\n");
                }
                if ( (cpuInfo.numCores != osCp.mCInfo.cpuInfo.numCores) \
                         || (cpuInfo.threadsPerCore != osCp.mCInfo.cpuInfo.threadsPerCore) )
                {
                        SSLOGERROR( ERRCLS_DEBUG, ESS707, ERRZERO, "SRegCpuinfo didnot register numCores and threadsPerCores properly\n ");
                }
                for (loopCounter = 0; (cpuInfo.threadRegister[loopCounter] == osCp.mCInfo.cpuInfo.threadRegister[loopCounter]) && \
                        loopCounter < osCp.mCInfo.cpuInfo.numCores; loopCounter++);
                if (loopCounter != osCp.mCInfo.cpuInfo.numCores)
                {
                        SSLOGERROR( ERRCLS_DEBUG, ESS708, ERRZERO, "SRegCpuinfo didnot register threadRegister properly\n");
                }
          }
          ssTstState = 105;
          break;
        }
        case 105:     /* Test SSetAffinity with Invalid task ID */
        {
          if (ssTstCnt == 1) {
                SsIdx tskID = 98;
                if(SSetAffinity(&tskID,SS_AFFINITY_MODE_DEFAULT,1,0) != ROK)
                {
               SSLOGERROR( ERRCLS_DEBUG, ESS709, ERRZERO, "SSetAffinity failed because of Invalid STskId\n");
                }
          }
          ssTstState = 106;
          break;
        }
        case 106:     /* Test SSetAffinity with Invalid Mode */
        {
          if (ssTstCnt == 1)
          {
                SsIdx tskID = 0;
                if(SSetAffinity(&tskID,6,1,0) != ROK)
                {
                       SSLOGERROR( ERRCLS_DEBUG, ESS710, ERRZERO, "SSetAffinity failed because of Invalid mode\n"); 
                }
          }
          ssTstState = 107;
          break;
        }
        case 107:     /* Test SSetAffinity with valid mode : SS_AFFINITY_MODE_DEFAULT */
        {
          if (ssTstCnt == 1)
          {
                U32 coreId = 0;
                SsIdx tskID = -1;
                SCpuInfo cpuInfo = { 8, 2, {0,1,2,1,2,1,2,1}};

                if (SRegCpuInfo(&cpuInfo) != ROK)
                {
                        SSLOGERROR( ERRCLS_DEBUG, ESS711, ERRZERO, "SRegCpuinfo failed\n");
                }
                if(SCreateSTsk(SS_NORM_TSK_PRI, &tskID) != ROK)
                {
                        SSLOGERROR( ERRCLS_DEBUG, ESS712, ERRZERO, "SCreateSTsk failed\n");
                }
                if (SSetAffinity(&tskID,SS_AFFINITY_MODE_DEFAULT,1,0) != ROK)
                {
                       SSLOGERROR( ERRCLS_DEBUG, ESS713, ERRZERO, "SSetAffinity  failed\n"); 
                }
                if (SGetAffinity(&tskID,&coreId) != ROK)
                {
                       SSLOGERROR( ERRCLS_DEBUG, ESS714, ERRZERO, "SGetAffinity failed\n"); 
                }
                if (coreId != 1)
                {
                       SSLOGERROR( ERRCLS_DEBUG, ESS715, ERRZERO, "SSetAffinity did not assign correctly\n"); 
                }

          }
          ssTstState = 108;
          break;
        }
        case 108:     /* Test SSetAffinity with valid mode : SS_AFFINITY_MODE_SPECIFIC */
        {
          if(ssTstCnt == 1)
          {
                U32 coreId = 0;
                SsIdx tskID = -1;
                SCpuInfo cpuInfo = { 8, 2, {0,1,2,1,2,1,2,1}};

                if (SRegCpuInfo(&cpuInfo) != ROK)
                {
                        SSLOGERROR( ERRCLS_DEBUG, ESS716, ERRZERO, "SRegCpuinfo failed\n");
                }
                if(SCreateSTsk(SS_NORM_TSK_PRI, &tskID) != ROK)
                {
                        SSLOGERROR( ERRCLS_DEBUG, ESS717, ERRZERO, "SCreateSTsk failed\n");
                }
                if(SSetAffinity(&tskID,SS_AFFINITY_MODE_SPECIFIC,2,0) != ROK)
                {
                       SSLOGERROR( ERRCLS_DEBUG, ESS718, ERRZERO, "SSetAffinity  failed\n"); 
                }
                if (SGetAffinity(&tskID,&coreId) != ROK)
                {
                       SSLOGERROR( ERRCLS_DEBUG, ESS719, ERRZERO, "SGetAffinity failed\n"); 
                }
                if (coreId != 2)
                {
                       SSLOGERROR( ERRCLS_DEBUG, ESS720, ERRZERO, "SSetAffinity did not set affinity properly\n"); 
                }

          }
          ssTstState = 109;
          break;
        }
        case 109:     /* Test SSetAffinity with valid mode : SS_AFFINITY_MODE_ASSOC */
        {
          if(ssTstCnt == 1)
          {
                U32 coreId = 0;
                SsIdx tskID[2] = {-1,-1};
                SCpuInfo cpuInfo = { 8, 2, {0,1,2,1,2,1,2,1}};

                if (SRegCpuInfo(&cpuInfo) != ROK)
                {
                     SSLOGERROR( ERRCLS_DEBUG, ESS721, ERRZERO, "SRegCpuinfo failed\n");     
                }
                if(SCreateSTsk(SS_NORM_TSK_PRI, &tskID[0]) != ROK)
                {
                        SSLOGERROR( ERRCLS_DEBUG, ESS722, ERRZERO, "SCreateSTsk failed\n");
                }
                if(SCreateSTsk(SS_NORM_TSK_PRI, &tskID[1]) != ROK)
                {
                        SSLOGERROR( ERRCLS_DEBUG, ESS723, ERRZERO, "SCreateSTsk failed\n");
                }
                if(SSetAffinity(&tskID[0],SS_AFFINITY_MODE_SPECIFIC,2,0) != ROK)
                {
                          SSLOGERROR( ERRCLS_DEBUG, ESS724, ERRZERO, "SSetAffinity  failed\n"); 
                }
                if(SSetAffinity(&tskID[1],SS_AFFINITY_MODE_ASSOC,0,&tskID[0]) != ROK)
                {
                       SSLOGERROR( ERRCLS_DEBUG, ESS725, ERRZERO, "SSetAffinity  failed\n"); 
                }
                if (SGetAffinity(&tskID[1],&coreId) != ROK)
                {
                        SSLOGERROR( ERRCLS_DEBUG, ESS726, ERRZERO, "SGetAffinity failed\n"); 
                }
                if (coreId != 2)
                {
                            SSLOGERROR( ERRCLS_DEBUG, ESS727, ERRZERO, "SSetAffinity did not set affinity properly\n"); 
                }
          }
          ssTstState = 110;
          break;
        }
        case 110:     /* Test SSetAffinity with valid mode : SS_AFFINITY_MODE_EXCL */
        {
          if(ssTstCnt == 1)
          {
                U32 coreId = 0;
                SsIdx tskID = -1;
                SCpuInfo cpuInfo = { 8, 2, {0,1,2,1,2,1,2,1}};

                if (SRegCpuInfo(&cpuInfo) != ROK)
                {
                     SSLOGERROR( ERRCLS_DEBUG, ESS728, ERRZERO, "SRegCpuinfo failed\n"); 
                }
                if(SCreateSTsk(SS_NORM_TSK_PRI, &tskID) != ROK)
                {
               SSLOGERROR( ERRCLS_DEBUG, ESS729, ERRZERO, "SCreateSTsk failed\n");
                }
                if (SSetAffinity(&tskID,SS_AFFINITY_MODE_EXCL,6,0) != ROK)
                {
                     SSLOGERROR( ERRCLS_DEBUG, ESS730, ERRZERO, "SSetAffinity  failed\n"); 
                }
                if (SGetAffinity(&tskID,&coreId) != ROK)
                {
                     SSLOGERROR( ERRCLS_DEBUG, ESS731, ERRZERO, "SGetAffinity  failed\n"); 
                }
                if (coreId != 6)
                {
                        SDisplay(0,"SSetAffinity did not assign correctly for SS_AFFINITY_MODE_ASSOC \n");
                }

          }
          ssTstState = 111;
          break;
        }
        case 111:     /* Test SSetAffinity with SS_DEFAULT_CORE parameter for SS_AFFINITY_MODE_EXCL */
        {
          if(ssTstCnt == 1)
          {
                SsIdx tskID = -1;
                SCpuInfo cpuInfo = { 8, 2, {0,1,2,1,2,1,2,1}};

                if (SRegCpuInfo(&cpuInfo) != ROK)
                {
                        SSLOGERROR( ERRCLS_DEBUG, ESS732, ERRZERO, "SRegCpuinfo failed\n"); 
                }
                if(SCreateSTsk(SS_NORM_TSK_PRI, &tskID) != ROK)
                {
                     SSLOGERROR( ERRCLS_DEBUG, ESS733, ERRZERO, "SCreateSTsk failed\n");        
                }
                if (SSetAffinity(&tskID,SS_AFFINITY_MODE_EXCL,SS_DEFAULT_CORE,0) != ROK)
                {
                     SSLOGERROR( ERRCLS_DEBUG, ESS734, ERRZERO, "SSetAffinity  failed\n"); 
                }
          }
          ssTstState = 112;
          break;
        }
        case 112:     /* Test SSetAffinity with Invalid Core Id for SS_AFFINITY_MODE_SPECIFIC */
        {
          if(ssTstCnt == 1)
          {
                SsIdx tskID = -1;
                SCpuInfo cpuInfo = { 8, 2, {0,1,2,1,2,1,2,1}};

                if (SRegCpuInfo(&cpuInfo) != ROK)
                {
                        SSLOGERROR( ERRCLS_DEBUG, ESS735, ERRZERO, "SRegCpuinfo failed\n"); 
                }
                if(SCreateSTsk(SS_NORM_TSK_PRI, &tskID) != ROK)
                {
               SSLOGERROR( ERRCLS_DEBUG, ESS736, ERRZERO, "SCreateSTsk failed\n");
                }
                if(SSetAffinity(&tskID,SS_AFFINITY_MODE_SPECIFIC,9,0) != ROK )
                {
                     SSLOGERROR( ERRCLS_DEBUG, ESS737, ERRZERO, "SSetAffinity  failed\n"); 
                }

          }
          ssTstState = 113;
          break;
        }
        case 113:     /* Test SSetAffinity with Exclsively setting a core and then trying to set the same core in Specific mode */ 
        {
          if(ssTstCnt == 1)
          {
                SsIdx tskID[2] = {-1,-1};
                SCpuInfo cpuInfo = { 8, 2, {0,1,2,1,2,1,2,1}};

                if (SRegCpuInfo(&cpuInfo) != ROK)
                {
                        SSLOGERROR( ERRCLS_DEBUG, ESS738, ERRZERO, "SRegCpuinfo failed\n"); 
                }
                if(SCreateSTsk(SS_NORM_TSK_PRI, &tskID[0]) != ROK)
                {
               SSLOGERROR( ERRCLS_DEBUG, ESS739, ERRZERO, "SCreateSTsk failed\n");
                }
                if(SCreateSTsk(SS_NORM_TSK_PRI, &tskID[1]) != ROK)
                {
                        SSLOGERROR( ERRCLS_DEBUG, ESS740, ERRZERO, "SCreateSTsk failed\n");
                }
                if(SSetAffinity(&tskID[0],SS_AFFINITY_MODE_EXCL,2,0) != ROK )
                {
                     SSLOGERROR( ERRCLS_DEBUG, ESS741, ERRZERO, "SSetAffinity  failed\n"); 
                }
                if(SSetAffinity(&tskID[1],SS_AFFINITY_MODE_SPECIFIC,2,0) != ROK )
                {
                     SSLOGERROR( ERRCLS_DEBUG, ESS742, ERRZERO, "SSetAffinity  failed\n"); 
                }
          }
          ssTstState = 114;
          break;
        }
        case 114:     /* Test SSetAffinity by passing an invalid STsk ID for associated mode */ 
        {
          if(ssTstCnt == 1)
          {
                SsIdx tskID[2] = {-1, 254};
                SCpuInfo cpuInfo = { 8, 2, {0,1,2,1,2,1,2,1}};

                if (SRegCpuInfo(&cpuInfo) != ROK)
                {
                        SSLOGERROR( ERRCLS_DEBUG, ESS743, ERRZERO, "SRegCpuinfo failed\n"); 
                }
                if(SCreateSTsk(SS_NORM_TSK_PRI, &tskID[0]) != ROK)
                {
                     SSLOGERROR( ERRCLS_DEBUG, ESS744, ERRZERO, "SCreateSTsk failed\n"); 
                }
                if(SSetAffinity(&tskID[0],SS_AFFINITY_MODE_ASSOC,7,&tskID[1]) != ROK )
                {
                     SSLOGERROR( ERRCLS_DEBUG, ESS745, ERRZERO, "SSetAffinity  failed\n"); 
                }
          }
          ssTstState = 115;
          break;
        }
        case 115:       /* Test SSetAffinity by giving an exclusively set Stsk Id for associated mode */ 
        {
          if(ssTstCnt == 1)
          {
                SsIdx tskID[2] = { -1, -1};
                SCpuInfo cpuInfo = { 8, 2, {0,1,2,1,2,1,2,1}};

                if (SRegCpuInfo(&cpuInfo) != ROK)
                {
                        SSLOGERROR( ERRCLS_DEBUG, ESS746, ERRZERO, "SRegCpuinfo failed\n"); 
                }
                if(SCreateSTsk(SS_NORM_TSK_PRI, &tskID[0]) != ROK)
                {
                     SSLOGERROR( ERRCLS_DEBUG, ESS747, ERRZERO, "SCreateSTsk failed\n"); 
                }
                if(SCreateSTsk(SS_NORM_TSK_PRI, &tskID[1]) != ROK)
                {
                     SSLOGERROR( ERRCLS_DEBUG, ESS748, ERRZERO, "SCreateSTsk failed\n"); 
                }
                if(SSetAffinity(&tskID[0],SS_AFFINITY_MODE_EXCL,2,0) != ROK)
                {
                     SSLOGERROR( ERRCLS_DEBUG, ESS749, ERRZERO, "SSetAffinity  failed\n"); 
                }
                if(SSetAffinity(&tskID[1],SS_AFFINITY_MODE_ASSOC,0,&tskID[0]) != ROK)
                {
                     SSLOGERROR( ERRCLS_DEBUG, ESS750, ERRZERO, "SSetAffinity  failed\n"); 
                }
         }
         ssTstState = 116;
         break;
        }
        case 116:      /* Test SSetAffinity by assigning the exclusive core to another stask exclusively */ 
        {
          if(ssTstCnt == 1)
          {
                SsIdx tskID[2] = {-1,-1};
                SCpuInfo cpuInfo = { 8, 2, {0,1,2,1,2,1,2,1}};

                if (SRegCpuInfo(&cpuInfo) != ROK)
                {
                        SSLOGERROR( ERRCLS_DEBUG, ESS751, ERRZERO, "SRegCpuinfo failed\n"); 
                }
                if(SCreateSTsk(SS_NORM_TSK_PRI, &tskID[0]) != ROK)
                {
                     SSLOGERROR( ERRCLS_DEBUG, ESS752, ERRZERO, "SCreateSTsk failed\n");        
                }
                if(SCreateSTsk(SS_NORM_TSK_PRI, &tskID[1]) != ROK)
                {
                     SSLOGERROR( ERRCLS_DEBUG, ESS753, ERRZERO, "SCreateSTsk failed\n"); 
                }
                if(SSetAffinity(&tskID[0],SS_AFFINITY_MODE_EXCL,2,0) != ROK )
                {
                     SSLOGERROR( ERRCLS_DEBUG, ESS754, ERRZERO, "SSetAffinity  failed\n"); 
                }
                if(SSetAffinity(&tskID[1],SS_AFFINITY_MODE_EXCL,2,0) != ROK )
                {
                     SSLOGERROR( ERRCLS_DEBUG, ESS755, ERRZERO, "SSetAffinity  failed\n"); 
                }
          }
          ssTstState = 117;
          break;
        }
        case 117:     /* Test SSetAffinity by setting an exclusive mode for an already set specific mode */
        {
          if(ssTstCnt == 1)
          {
                SsIdx tskID[2] = { -1, -1};
                SCpuInfo cpuInfo = { 8, 2, {0,1,2,1,2,1,2,1}};

                if (SRegCpuInfo(&cpuInfo) != ROK)
                {
                       SSLOGERROR( ERRCLS_DEBUG, ESS756, ERRZERO, "SRegCpuinfo failed\n"); 
                }
                if(SCreateSTsk(SS_NORM_TSK_PRI, &tskID[0]) != ROK)
                {
                     SSLOGERROR( ERRCLS_DEBUG, ESS757, ERRZERO, "SCreateSTsk failed\n"); 
                }
                if(SCreateSTsk(SS_NORM_TSK_PRI, &tskID[1]) != ROK)
                {
                     SSLOGERROR( ERRCLS_DEBUG, ESS758, ERRZERO, "SCreateSTsk failed\n"); 
                }
                if(SSetAffinity(&tskID[0],SS_AFFINITY_MODE_SPECIFIC,2,0) != ROK)
                {
                     SSLOGERROR( ERRCLS_DEBUG, ESS759, ERRZERO, "SSetAffinity  failed\n"); 
                }
                if(SSetAffinity(&tskID[1],SS_AFFINITY_MODE_EXCL,2,0) != ROK)
                {
                     SSLOGERROR( ERRCLS_DEBUG, ESS760, ERRZERO, "SSetAffinity  failed\n"); 
                }
          }
          ssTstState = 118;
          break;
        }
        case 118:     /* Test SGetAffinity with proper values */
        {
          if(ssTstCnt == 1)
          {
                U32 coreId = 0;
                SsIdx tskID = -1;
                SCpuInfo cpuInfo = { 8, 2, {0,1,2,1,2,1,2,1}};

                if (SRegCpuInfo(&cpuInfo) != ROK)
                {
                       SSLOGERROR( ERRCLS_DEBUG, ESS761, ERRZERO, "SRegCpuinfo failed\n"); 
                }
                if(SCreateSTsk(SS_NORM_TSK_PRI, &tskID) != ROK)
                {
                     SSLOGERROR( ERRCLS_DEBUG, ESS762, ERRZERO, "SCreateSTsk failed\n"); 
                }
                if(SSetAffinity(&tskID,SS_AFFINITY_MODE_DEFAULT,2,0) != ROK)
                {
                     SSLOGERROR( ERRCLS_DEBUG, ESS763, ERRZERO, "SSetAffinity  failed\n"); 
                }
                if(SGetAffinity(&tskID,&coreId) != ROK)
                {
                     SSLOGERROR( ERRCLS_DEBUG, ESS764, ERRZERO, "SGetAffinity  failed\n"); 
                }

          }
          ssTstState = 119;
          break;
        }
        case 119:     /* Test SGetAffinity with Improper Task Id */
        {
          if(ssTstCnt == 1)
          {
                U32 coreId = 0;
                SsIdx tskID = -1;
                SCpuInfo cpuInfo = { 8, 2, {0,1,2,1,2,1,2,1}};

                if (SRegCpuInfo(&cpuInfo) != ROK)
                {
                       SSLOGERROR( ERRCLS_DEBUG, ESS765, ERRZERO, "SRegCpuinfo failed\n"); 
                }
                if(SGetAffinity(&tskID,&coreId) != ROK)
                {
                     SSLOGERROR( ERRCLS_DEBUG, ESS766, ERRZERO, "SGetAffinity  failed\n"); 
                }

          }
          ssTstState = 120;
          break;
        }
        case 120:     /* Cores should be overloaded when there are more threads than available cores */
        {
          if (ssTstCnt == 1)
          {
                SsIdx tskID[6];
                SCpuInfo cpuInfo = { 8, 2, {0,2,0,2,0,2,0,1}};

                if (SRegCpuInfo(&cpuInfo) != ROK)
                {
                       SSLOGERROR( ERRCLS_DEBUG, ESS767, ERRZERO, "SRegCpuinfo failed\n"); 
                }
                for ( i = 0; i < 6; i++ )
                {
                    if(SCreateSTsk(SS_NORM_TSK_PRI, &tskID[i]) != ROK)
                    {
                         SSLOGERROR( ERRCLS_DEBUG, ESS768, ERRZERO, "SCreateSTsk failed\n"); 
                    }
                    if( SSetAffinity(&tskID[i],SS_AFFINITY_MODE_DEFAULT,1,0) != ROK )
                    {
                         SSLOGERROR( ERRCLS_DEBUG, ESS769, ERRZERO, "SSetAffinity  failed\n"); 
                    }
                }

          }
	}
          ssTstState = 121;
          break;
#endif /*  end of ifdef SS_MULTICORE_SUPPORT */
          case 121:
	  {
	#ifdef SS_WATCHDOG
                if( SInitWatchdog(SS_WD_WDPORT) != ROK )
		{
                         SSLOGERROR( ERRCLS_DEBUG, ESSXXX, ERRZERO, "SInitWatchdog failed\n"); 
		}
		if( SStopHrtBt() != ROK )
		{
                         SSLOGERROR( ERRCLS_DEBUG, ESSXXX, ERRZERO, "SStopHrtBt failed\n"); 
			
		}
   		if( SRegCfgWd(1, addr,port , 10, 0,"SSI got killed ") != ROK ) /* numNodes, addr, port, timeout, callback, data */
		{
                         SSLOGERROR( ERRCLS_DEBUG, ESSXXX, ERRZERO, "SRegCfgWd failed\n"); 
		}
   		if( SStartHrtBt(5) != ROK )
		{
                         SSLOGERROR( ERRCLS_DEBUG, ESSXXX, ERRZERO, "SStartHrtBt failed\n"); 
		}
        #endif
	  }
          ssTstState = 122;
          break;
	  case 122:
          {
        #ifdef SS_WATCHDOG
		if( SInitWatchdog(SS_WD_WDPORT) != ROK )
                {
                         SSLOGERROR( ERRCLS_DEBUG, ESSXXX, ERRZERO, "SInitWatchdog failed\n");
                }
		if( SStopHrtBt() != ROK )
                {
                         SSLOGERROR( ERRCLS_DEBUG, ESSXXX, ERRZERO, "SStopHrtBt failed\n");
                        
                }
                if( SRegCfgWd(2, addr,port , 10, 0,"SSI got killed ")!= ROK )  /* numNodes, addr, port, timeout, callback, data */
                {
                         SSLOGERROR( ERRCLS_DEBUG, ESSXXX, ERRZERO, "SRegCfgWd failed\n");
                }
                if(SStartHrtBt(5)!= ROK )
                {
                         SSLOGERROR( ERRCLS_DEBUG, ESSXXX, ERRZERO, "SStartHrtBt failed\n");
                }
        #endif
          ssTstState = 123;
          break;
        }
	case 123:
          {
        #ifdef SS_LOGGER_SUPPORT
		SStopLogger();
		if( SDeregLogCfg() != ROK )
		{
                         SSLOGERROR( ERRCLS_DEBUG, ESSXXX, ERRZERO, "SDeregLogCfg failed\n");
		}
		SPrint("Registering the logger support,logging to file ss_log");
		if( SRegLogCfg(SS_LOG_TO_FILE,"ssi_log",102400,"172.25.0.39",0 != ROK )) /* mode,filepath,filesize,IPaddr,port */
		{
                         SSLOGERROR( ERRCLS_DEBUG, ESSXXX, ERRZERO, "SRegLogCfg failed\n");
		}
		SStartLogger();
        #endif
          }
          ssTstState = 124;
          break;
	  case 124:
          {
        #ifdef SS_LOGGER_SUPPORT
		SStopLogger();
		if( SDeregLogCfg() != ROK )
		{
                         SSLOGERROR( ERRCLS_DEBUG, ESSXXX, ERRZERO, "SDeregLogCfg failed\n");
		}
                SPrint("Registering the logger support,logging to socket");
                if( SRegLogCfg(SS_LOG_TO_SOCKET,"ssi_log",102400,"172.25.0.39",12345) != ROK ) /* mode,filepath,filesize,IPaddr,port */
		{
                         SSLOGERROR( ERRCLS_DEBUG, ESSXXX, ERRZERO, "SRegLogCfg failed\n");
		}
		SStartLogger();
        #endif
          }
          ssTstState = 125;
          break;
	  case 125:
          {
        #ifdef SS_LOGGER_SUPPORT
		SStopLogger();
                if( SDeregLogCfg() != ROK )
		{
                         SSLOGERROR( ERRCLS_DEBUG, ESSXXX, ERRZERO, "SDeregLogCfg failed\n");
		}
                SPrint("Registering the logger support,logging to socket");                
		if( SRegLogCfg(SS_LOG_ALL,"ssi_log",102400,"172.25.0.39",12345) != ROK ) /* mode,filepath,filesize,IPaddr,port */
		{
                         SSLOGERROR( ERRCLS_DEBUG, ESSXXX, ERRZERO, "SRegLogCfg failed\n");
		}
		SStartLogger();
        #endif
          }
          ssTstState = 126;
          break;
	 case 126:
          {
        #ifdef SS_LOGGER_SUPPORT
		SStopLogger();
                if( SDeregLogCfg()  != ROK )
		{
                         SSLOGERROR( ERRCLS_DEBUG, ESSXXX, ERRZERO, "SDeregLogCfg failed\n");
		}
                SPrint("Registering the logger support,logging to socket");
                if(SRegLogCfg(-1,"ssi_log",102400,"172.25.0.39",12345) != ROK ) /* mode,filepath,filesize,IPaddr,port */
		{
			SSLOGERROR( ERRCLS_DEBUG, ESSXXX, ERRZERO, "SRegLogCfg failed\n");
		}
		SStartLogger();
        #endif
          }
          ssTstState = 127;
          break;
	 case 127:
	 {
	#ifdef SS_HISTOGRAM_SUPPORT
		U8 tmp;
		if( SRegForHstGrm(TST0ENT) != ROK )
		{
			SSLOGERROR( ERRCLS_DEBUG, ESSXXX, ERRZERO, "SRegForHstGrm failed\n");
		}
		tmp = TST0ENT;
 		if( SHstGrmInfoShow(&tmp) != ROK )
		{
			SSLOGERROR( ERRCLS_DEBUG, ESSXXX, ERRZERO, "SHstGrmInfoShow failed\n");
		}        
	#endif
	 }
	 ssTstState = 128;
	 break;
	 case 128:
         {
        #ifdef SS_HISTOGRAM_SUPPORT
                if( SHstGrmInfoShow(0) != ROK )
		{
			SSLOGERROR( ERRCLS_DEBUG, ESSXXX, ERRZERO, "SHstGrmInfoShow failed\n");
		}   
        #endif
         }
         ssTstState = 129;
         break;
	 case 129:
         {
        #ifdef SS_HISTOGRAM_SUPPORT
	#ifdef SS_LOGGER_SUPPORT
		SStopLogger();
		if( SDeregLogCfg() != ROK )
		{
			SSLOGERROR( ERRCLS_DEBUG, ESSXXX, ERRZERO, "SDeregLogCfg failed\n");
		}
                SPrint("Registering the logger support,logging to file");
                if( SRegLogCfg(SS_LOG_TO_FILE,"ssi_log",102400,NULLP,0) != ROK ) /* mode,filepath,filesize,IPaddr,port */
		{
			SSLOGERROR ( ERRCLS_DEBUG, ESSXXX, ERRZERO, "SRegLogCfg failed\n");
		}                
		SStartLogger();
		if( SHstGrmInfoShow(0) != ROK )
		{
			SSLOGERROR(ERRCLS_DEBUG, ESSXXX, ERRZERO, "SHstGrmInfoShow failed\n");   
		}
	#endif /* SS_LOGGER_SUPPORT */
        #endif /* SS_HISTOGRAM_SUPPORT */
         }
         ssTstState = 130;
         break;
	 case 130:
	 {
	#ifdef BIT_64 
       	#ifdef SS_THREAD_PROFILE
/*TST1ENT, TSTINST0 TSTPERMENT*/
	ent =  2;/*TST1ENT;i */
	inst = TSTINST0;

	#ifdef SS_MULTIPLE_PROCS
   		procId = SFndProcId();
   		 ret1 = SGetThrdProf(&sTskId,procId ,ent,inst,&evnt,&timetaken,&totTime); 
	#else
   		  ret1 = SGetThrdProf(&sTskId,ent,inst,&evnt,&timetaken,&totTime); 
	#endif

   	if ( ret1 != ROK )
   	{
  	      sprintf(buf,"\n SGetThrdProf failed for Entity:%d and Instance:%d\n",ent,inst );
   	}
   	else
   	{
#ifdef SS_MULTIPLE_PROCS
/*ss013.301: Fixed Warnings for 32/64 bit compilation*/
#ifdef ALIGN_64BIT
       		sprintf(buf,"\n ThreadId:%d ProcId:%d Entity:%d Instance:%d Event:%d Timetaken:%d Totaltime:%d\n",sTskId,procId,ent,inst,evnt,timetaken,totTime);
#else
       		sprintf(buf,"\n ThreadId:%d ProcId:%d Entity:%d Instance:%d Event:%d Timetaken:%ld Totaltime:%ld\n",sTskId,procId,ent,inst,evnt,timetaken,totTime);
#endif
#else
#ifdef ALIGN_64BIT
       		sprintf(buf,"\n ThreadId:%d Entity:%d Instance:%d Event:%d Timetaken:%d Totaltime:%ld\n",sTskId,ent,inst,evnt,timetaken,totTime);
#else
       		sprintf(buf,"\n ThreadId:%d Entity:%d Instance:%d Event:%d Timetaken:%ld Totaltime:%ld\n",sTskId,ent,inst,evnt,timetaken,totTime);
#endif
#endif
   	}
   		SPrint(buf);
	#endif /* SS_THREAD_PROFILE */
	#endif /* BIT_64 */
	 }
	 ssTstState = 0;
	 break;
   }
   SExitTsk();
   RETVALUE(ROK);

} /* end of tst0PermActvTsk */


/*
*
*       Fun:   tst1PermActvTsk
*
*       Desc:  Sample function for test permanent task activation.
*
*       Ret:   ROK       - ok
*
*       Notes: None
*
*       File:  ss_acc.c
*
*/
 
#ifdef ANSI
PUBLIC S16 tst1PermActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 tst1PermActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(tst1PermActvTsk)
 
   if (mBuf != NULLP)
   {
      /* return message */
      SPutMsg(mBuf);
   }
 
   SExitTsk();
   RETVALUE(ROK);

} /* end of tst1PermActvTsk */

/* ss029.103: modification: procId, ent and inst added */
#ifndef SS_MULTIPLE_PROCS 

#ifdef ANSI
PUBLIC S16 tst1fnc
(
void
)
#else
PUBLIC S16 tst1fnc()
#endif

#else /* SS_MULTIPLE_PROCS */

#ifdef ANSI
PUBLIC S16 tst1fnc
(
ProcId proc,
Ent ent,
Inst inst
)
#else
PUBLIC S16 tst1fnc(proc, ent, inst)
ProcId proc;
Ent ent;
Inst inst;
#endif

#endif /* SS_MULTIPLE_PROCS */
{
   TRC2(tst1fnc)
   RETVALUE(ROK);
}

/* ss029.103: modification: procId, ent and inst added */
#ifndef SS_MULTIPLE_PROCS 

#ifdef ANSI
PUBLIC S16 tst2fnc
(
void
)
#else
PUBLIC S16 tst2fnc()
#endif

#else /* SS_MULTIPLE_PROCS */

#ifdef ANSI
PUBLIC S16 tst2fnc
(
ProcId proc,
Ent ent,
Inst inst
)
#else
PUBLIC S16 tst2fnc(proc, ent, inst)
ProcId proc;
Ent ent;
Inst inst;
#endif

#endif /* SS_MULTIPLE_PROCS */
{
   TRC2(tst2fnc)
   RETVALUE(ROK);
}





#endif /* SS_SINGLE_THREADED */


/*
*
*       Fun:   tskEnd
*
*       Desc:  Task End
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: 
*
*       File:  ss_acc.c
*
*/
#ifndef SS_SINGLE_THREADED
#ifdef ANSI
PRIVATE Void tskEnd
(
U8   tskId
)
#else
PRIVATE Void tskEnd(tskId)
U8   tskId;
#endif
{
   TRC2(tskEnd)

   ++tCp.tskCnt[tskId];

   if(tCp.tskCnt[tskId] % TSKCNT == 0)
   {
      sprintf(prntBuf, "permanent task %d  run count= %ld\n", tskId, tCp.tskCnt[tskId]);
      /* SDisplay(0,prntBuf); */
   }

   RETVOID;

} /* end of tskEnd */
#endif /* SS_SINGLE_THREADED */


/*                                     
*
*       Fun:   tst1ActvTmr
*
*       Desc:  Sample function for first test timer activation.
*
*       Ret:   ROK       - ok
*
*       Notes: None
*
*       File:  ss_acc.c
*
*/
/* ss029.103: modification: procId, ent and inst added */
#ifndef SS_MULTIPLE_PROCS 

#ifdef ANSI
PUBLIC S16 tst1ActvTmr
(
void
)
#else
PUBLIC S16 tst1ActvTmr()
#endif

#else /* SS_MULTIPLE_PROCS */

#ifdef ANSI
PUBLIC S16 tst1ActvTmr
(
ProcId proc,
Ent ent,
Inst inst
)
#else
PUBLIC S16 tst1ActvTmr(proc, ent, inst)
ProcId proc;
Ent ent;
Inst inst;
#endif

#endif /* SS_MULTIPLE_PROCS */
{
   TRC2(tst1ActvTmr)

/* ss029.103: modification: procId, ent and inst added */
#ifdef SS_MULTIPLE_PROCS 
   UNUSED(proc);
   UNUSED(ent);
   UNUSED(inst);
#endif /* SS_MULTIPLE_PROCS */

   tskTmrCnt[0]++;
   SExitTsk();
   RETVALUE(ROK);

} /* end of tst1ActvTmr */


/*                                     
*
*       Fun:   tst2ActvTmr
*
*       Desc:  Sample function for first test timer activation.
*
*       Ret:   ROK       - ok
*
*       Notes: None
*
*       File:  ss_acc.c
*
*/
/* ss029.103: modification: procId, ent and inst added */
#ifndef SS_MULTIPLE_PROCS 

#ifdef ANSI
PUBLIC S16 tst2ActvTmr
(
void
)
#else
PUBLIC S16 tst2ActvTmr()
#endif

#else /* SS_MULTIPLE_PROCS */

#ifdef ANSI
PUBLIC S16 tst2ActvTmr
(
ProcId proc,
Ent ent,
Inst inst
)
#else
PUBLIC S16 tst2ActvTmr(proc, ent, inst)
ProcId proc;
Ent ent;
Inst inst;
#endif

#endif /* SS_MULTIPLE_PROCS */

{
   TRC2(tst2ActvTmr)

/* ss029.103: modification: procId, ent and inst added */
#ifdef SS_MULTIPLE_PROCS 
   UNUSED(proc);
   UNUSED(ent);
   UNUSED(inst);
#endif /* SS_MULTIPLE_PROCS */

   tskTmrCnt[1]++;
   SExitTsk();
   RETVALUE(ROK);

} /* end of tst2ActvTmr */

#ifndef SS_SINGLE_THREADED

/*
*
*       Fun:   permTsk1
*
*       Desc:  Queue tests
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: None
*
*       File:  ss_acc.c
*
*/
#ifdef ANSI
PRIVATE S16 permTsk1
(
Pst *pst,                       /* pst structure */
Buffer *mBuf                    /* buffer */
)
#else
PRIVATE S16 permTsk1(pst, mBuf)
Pst *pst;                       /* pst structure */
Buffer *mBuf;                   /* buffer */
#endif
{
   REG1 S32 i;
   Buffer *m[TSTTIMES];
   Buffer *n[TSTTIMES];
   Queue q;
   Queue q1;
   QLen qlng;
   QLen qlng1;
   S16 ret1;
   S16 ret2;
   Buffer *bufPtr;
   QLen idx;
   QLen size;
   
   TRC2(permTsk1)

   if (mBuf)
      SPutMsg(mBuf);
   
   SInitQueue(&q);
   
   SFndLenQueue(&q, &qlng);
   if ( qlng != 0 )
      SSLOGERROR( ERRCLS_DEBUG,ESS770,5, "" );
   if (((ret1 = SDequeueFirst(&bufPtr, &q)) != ROKDNA) || 
       ((ret2 = SDequeueLast(&bufPtr, &q)) != ROKDNA))    
      SSLOGERROR( ERRCLS_DEBUG,ESS771,6 , "");
   idx = 0;
   if (((ret1 = SExamQueue(&bufPtr, &q, idx)) != ROKDNA) ||
       ((ret2 = SRemQueue(&bufPtr, &q, idx)) != ROKDNA))
      SSLOGERROR( ERRCLS_DEBUG,ESS772,7, "" );
   
   SInitQueue(&q);
   
   for (i = 0; i < TSTTIMES; i++)
   {
      SGetMsg(region,pool,&m[i]);
      SQueueFirst(m[i],&q);
      SFndLenQueue(&q, &qlng);
      if ( qlng != (QLen)(i+1) )
         SSLOGERROR( ERRCLS_DEBUG,ESS773,8, "" );
   }
   for (i = (TSTTIMES-1); i >= 0; i--)
   {
      SDequeueFirst(&m[i], &q);
      SFndLenQueue(&q, &qlng);
      if ( qlng != (QLen)i )
         SSLOGERROR( ERRCLS_DEBUG,ESS774,9, "" );
      SPutMsg(m[i]);
   }
   
   SInitQueue(&q);

   for (i = 0; i < TSTTIMES; i++)
   {
      SGetMsg(region,pool,&m[i]);
      SQueueLast(m[i],&q);
      SFndLenQueue(&q, &qlng);
      if ( qlng != (QLen)(i+1) )
         SSLOGERROR( ERRCLS_DEBUG,ESS775,10, "" );
         }
   for (i = (TSTTIMES-1); i >= 0; i--)
   {
      SDequeueLast(&m[i], &q);
      SFndLenQueue(&q, &qlng);
      if ( qlng != (QLen)i )
         SSLOGERROR( ERRCLS_DEBUG,ESS776,11, "" );
      SPutMsg(m[i]);
   }
   
   for (i = 0; i < TSTTIMES; i++)
   {
      SGetMsg(region,pool,&m[i]);
      SQueueFirst(m[i],&q);
   }
   for (i = 0; i < TSTTIMES; i++)
   {
      SDequeueLast(&n[i], &q);
      SFndLenQueue(&q,&qlng);
      if ( qlng != (QLen)(TSTTIMES-i-1) )
         SSLOGERROR( ERRCLS_DEBUG,ESS777,12, "" );
      SPutMsg(n[i]);
   }   
   
   SInitQueue(&q);
   
   for (i = 0; i < TSTTIMES; i++)
   {
      SGetMsg(region,pool,&m[i]);
      SQueueLast(m[i],&q);
   }
   SFlushQueue(&q);
   SFndLenQueue(&q,&qlng);
   if ( qlng != 0 )
      SSLOGERROR( ERRCLS_DEBUG,ESS778,13, "" );
   
   if (((ret1 = SDequeueFirst(&bufPtr, &q)) != ROKDNA) || 
       ((ret2 = SDequeueLast(&bufPtr, &q)) != ROKDNA))    
      SSLOGERROR( ERRCLS_DEBUG,ESS779,14, "" );
   
   SInitQueue(&q);
   SInitQueue(&q1);
   
   for ( i = 1;i <= 2;i++ )
   {
      SGetMsg(region,pool,&m[0]);
      SQueueLast(m[0],&q);
      SFndLenQueue(&q,&qlng);
      
      SGetMsg(region,pool,&n[0]);
      SQueueFirst(n[0],&q1);
      SFndLenQueue(&q1,&qlng1);
      
      size = qlng+qlng1;
      if ( i == Q1Q2 )
      {
         SCatQueue(&q,&q1,Q1Q2);
         if ( size != q.crntSize )
            SSLOGERROR( ERRCLS_DEBUG,ESS780,15, "" );
         SDequeueFirst(&m[1],&q);
         if ( m[1] != m[0] )
            SSLOGERROR( ERRCLS_DEBUG,ESS781,16, "" );
         SDequeueLast(&n[1],&q);
         if ( n[1] != n[0] )
            SSLOGERROR( ERRCLS_DEBUG,ESS782,17, "" );
         SDequeueFirst(&n[2],&q1);
         if ( n[2] != NULLP )
            SSLOGERROR( ERRCLS_DEBUG,ESS783,18, "" );
         SPutMsg(m[0]);
         SPutMsg(n[0]);
      }
      else
      {
         SCatQueue(&q,&q1,Q2Q1);
         if ( size != q.crntSize )
            SSLOGERROR( ERRCLS_DEBUG,ESS784,19, "" );
         SDequeueFirst(&n[1],&q);
         if ( n[1] != n[0] )
            SSLOGERROR( ERRCLS_DEBUG,ESS785,20, "" );
         SDequeueLast(&m[1],&q);
         if ( m[1] != m[0] )
            SSLOGERROR( ERRCLS_DEBUG,ESS786,21, "" );
         SDequeueFirst(&n[2],&q1);
         if ( n[2] != NULLP )
            SSLOGERROR( ERRCLS_DEBUG,ESS787,22, "" );
         SPutMsg(m[0]);
         SPutMsg(n[0]);
      }               
   }

   SInitQueue(&q);
   
   for (i = 0; i < TSTTIMES; i++)
   {
      SGetMsg(region,pool,&m[i]);
      SQueueLast(m[i],&q);
   }
   
   idx = 0;
   SExamQueue(&bufPtr, &q, idx);
   if ( bufPtr != m[idx] )
      SSLOGERROR( ERRCLS_DEBUG,ESS788,23, "" );
   idx = TSTTIMES-1;
   SExamQueue(&bufPtr, &q, idx);
   if ( bufPtr != m[idx] )
      SSLOGERROR( ERRCLS_DEBUG,ESS789,24, "" );
   
   for (i = 0; i < TSTTIMES; i++)
      SPutMsg(m[i]);            
   
   SInitQueue(&q);
   SGetMsg(region,pool,&n[0]);

   idx = 0;
   SAddQueue(n[0],&q,idx);
   SExamQueue(&n[1],&q,idx);
   SFndLenQueue(&q,&qlng);
   if ( (n[1] != n[0]) || (qlng != 1) )
      SSLOGERROR( ERRCLS_DEBUG,ESS790,25, "" );
   SRemQueue(&n[2],&q,idx);
   SFndLenQueue(&q,&qlng);
   if ( (n[2] != n[0]) || (qlng != 0) )
      SSLOGERROR( ERRCLS_DEBUG,ESS791,26, "" );
   
   for (i = 0; i < TSTTIMES; i++)
   {
      SGetMsg(region,pool,&m[i]);
      SQueueLast(m[i],&q);
   }
   
   idx = (QLen) TSTTIMES / 2;
   SAddQueue(n[0],&q,idx);
   SExamQueue(&n[1],&q,idx);
   SRemQueue(&n[2],&q,idx);
   if ( (n[1] != n[0]) || (n[2] != n[0]) )
      SSLOGERROR( ERRCLS_DEBUG,ESS792,27, "" );
         
   idx = TSTTIMES;
   SAddQueue(n[0],&q,idx);
   SExamQueue(&n[1],&q,idx);
   SRemQueue(&n[2],&q,idx);
   if ( (n[1] != n[0]) || (n[2] != n[0]) )
      SSLOGERROR( ERRCLS_DEBUG,ESS793,28, "" );
   
   for (i = 0; i < TSTTIMES; i++)
      SPutMsg(m[i]);            
   SPutMsg(n[0]);
   tskEnd(1);
   RETVALUE(ROK);

} /* end of permTsk1 */



/*
*
*       Fun:   permTsk2
*
*       Desc:  Message tests
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: None
*
*       File:  ss_acc.c
*
*/
#ifdef ANSI
PRIVATE S16 permTsk2
(
Pst *pst,                       /* pst structure */
Buffer *mBuf                    /* message buffer */
)
#else
PRIVATE S16 permTsk2(pst, mBuf)
Pst *pst;                       /* pst structure */
Buffer *mBuf;                   /* message buffer */
#endif
{
   Buffer *m[TSTTIMES];
   MsgLen mlng;
   MsgLen mlng1;
   S16 ret1;
   S16 ret2;
   Data uData;
   Data sData;
   MsgLen idx;
   U32 u32;
   S32 s32;
   U16 u16;
   S16 s16;
   U8 u8;
   S8 s8;
   REG1 S32 i;
   REG2 S32 j;
   
   TRC2(permTsk2)
      
   if (mBuf)
      SPutMsg(mBuf);

   SGetMsg(region,pool,&m[0]);

   SFndLenMsg(m[0],&mlng);
   if ( mlng != 0 )
      SSLOGERROR( ERRCLS_DEBUG,ESS794,29, "" );
   if (((ret1 = SRemPreMsg(&uData,m[0])) != ROKDNA) ||
       ((ret2 = SRemPstMsg(&uData,m[0])) != ROKDNA))
      SSLOGERROR( ERRCLS_DEBUG,ESS795,30 , "");
   idx = 0;
   if (((ret1 = SExamMsg(&uData,m[0],idx)) != ROKDNA) ||
       ((ret2 = SRepMsg(uData,m[0],idx)) != ROKDNA))
      SSLOGERROR( ERRCLS_DEBUG,ESS796,31 , "");
   
   SPutMsg(m[0]);   
   
   SGetMsg(region,pool,&m[0]);

   SPkS8((S8) 0x01,m[0]);
   SPkU8((U8) 0x02,m[0]);
   SPkS16((S16) 0x0304,m[0]);
   SPkU16((U16) 0x0506,m[0]);
   SPkS32((S32) 0x0708090aL,m[0]);
   SPkU32((U32) 0x0b0c0d0eL,m[0]);
   
   SUnpkU32(&u32,m[0]);
   if ( u32 != (U32) 0x0b0c0d0eL )
      SSLOGERROR( ERRCLS_DEBUG,ESS797,32 , "");
   SUnpkS32(&s32,m[0]);
   if ( s32 != (S32) 0x0708090aL )
      SSLOGERROR( ERRCLS_DEBUG,ESS798,33, "" );
   SUnpkU16(&u16,m[0]);
   if ( u16 != (U16) 0x0506 )
      SSLOGERROR( ERRCLS_DEBUG,ESS799,34, "" );
   SUnpkS16(&s16,m[0]);
   if ( s16 != (S16) 0x0304 )
      SSLOGERROR( ERRCLS_DEBUG,ESS800,35, "" );
   SUnpkU8(&u8,m[0]);
   if ( u8 != (U8) 0x02 )
      SSLOGERROR( ERRCLS_DEBUG,ESS801,36, "" );
   SUnpkS8(&s8,m[0]);
   if ( s8 != (S8) 0x01 )
      SSLOGERROR( ERRCLS_DEBUG,ESS802,37, "" );
   
   SPutMsg(m[0]);
   
   SGetMsg(region,pool,&m[0]);
   
   for ( j = 0; j < mLen; j++ )
      SAddPreMsg((Data) j,m[0]);
   for ( j = 0; j < mLen; j++ )
   {
      SExamMsg(&uData,m[0],(MsgLen) j);
      if ( uData != (Data) ((mLen - 1)-j) )
         SSLOGERROR( ERRCLS_DEBUG,ESS803,38 , "");
   }
   
   for ( j = 0; j < mLen; j++ )
      SRepMsg((Data) j,m[0],(MsgLen) j);
   for ( j = 0; j < mLen; j++ )
   {
      SExamMsg(&uData,m[0],(MsgLen) j);
      if ( uData != (Data) j )
         SSLOGERROR( ERRCLS_DEBUG,ESS804,39 , "");
   }
   
   SFndLenMsg(m[0],&mlng);
   if ( mlng != mLen )
      SSLOGERROR( ERRCLS_DEBUG,ESS805,40 , "");
   
   for ( j = 0; j < mLen; j++ )
   {
      SRemPreMsg(&uData,m[0]); 
      SFndLenMsg(m[0],&mlng);
      if ( (uData != (Data) j) || (mlng != ((mLen - 1)-j)) )
         SSLOGERROR( ERRCLS_DEBUG,ESS806,41 , "");
   }
   
   SPutMsg(m[0]);

   SGetMsg(region,pool,&m[0]);
   
   for ( j = 0; j < mLen; j++ )
      SAddPstMsg((Data) j,m[0]);
   for ( j = 0; j < mLen; j++ )
   {
      SExamMsg(&uData,m[0],(MsgLen) j);
      if ( uData != (Data) j )
         SSLOGERROR( ERRCLS_DEBUG,ESS807,42 , "");
   }
   for ( j = 0; j < mLen; j++ )
      SRepMsg((Data) j,m[0],(MsgLen) ((mLen - 1)-j));
   for ( j = 0; j < mLen; j++ )
   {
      SExamMsg(&uData,m[0],(MsgLen) j);
      if ( uData != (Data) ((mLen - 1)-j) )
         SSLOGERROR( ERRCLS_DEBUG,ESS808,43 , "");
   }
   
   SFndLenMsg(m[0],&mlng);
   if ( mlng != mLen )
      SSLOGERROR( ERRCLS_DEBUG,ESS809,44 , "");
   for ( j = 0; j < mLen; j++ )
   {
      SRemPstMsg(&uData,m[0]); 
      SFndLenMsg(m[0],&mlng);
      if ( (uData != (Data) j) || (mlng != ((mLen - 1)-j)) )
         SSLOGERROR( ERRCLS_DEBUG,ESS810,45 , "");
   }
   
   SPutMsg(m[0]);
   
   SGetMsg(region,pool,&m[0]);
   
   for ( j = 0; j < mLen; j++ )
      SAddPstMsg((Data) j,m[0]);
   SInitMsg(m[0]);
   SFndLenMsg(m[0],&mlng);
   if( mlng != 0 )
      SSLOGERROR( ERRCLS_DEBUG,ESS811,46 , "");
   
   if (((ret1 = SRemPreMsg(&uData,m[0])) != ROKDNA) ||
       ((ret2 = SRemPstMsg(&uData,m[0])) != ROKDNA))
      SSLOGERROR( ERRCLS_DEBUG,ESS812,47 , "");
   idx = 0;
   if (((ret1 = SExamMsg(&uData,m[0],idx)) != ROKDNA) ||
       ((ret2 = SRepMsg(uData,m[0],idx)) != ROKDNA))
      SSLOGERROR( ERRCLS_DEBUG,ESS813,48 , "");
   
   SPutMsg(m[0]);
   
   SGetMsg(region,pool,&m[0]);
   SGetMsg(region,pool,&m[1]);
   
   for ( j = 0; j < 2*TSTTIMES; j++ )
   {
      SAddPstMsg((Data) j,m[0]);
      SAddPreMsg((Data) j,m[1]);
   }
   
   for ( i = 0; i <= 1; i++ )
   {
      if ( i == M1M2 )
      {
         SCatMsg(m[0],m[1],(Order)i);
         SFndLenMsg(m[0],&mlng);
         SFndLenMsg(m[1],&mlng1);
         if ((mlng != 4*TSTTIMES) || (mlng1 != 0))
            SSLOGERROR( ERRCLS_DEBUG,ESS814,49 , "");
         SRemPstMsg(&uData,m[0]);
         if ( uData != (Data) 0 )
            SSLOGERROR( ERRCLS_DEBUG,ESS815,50 , "");
         SAddPstMsg(uData,m[0]);
         if (((ret1 = SRemPreMsg(&uData,m[1])) != ROKDNA) ||
             ((ret2 = SRemPstMsg(&uData,m[1])) != ROKDNA) || 
             (uData != (Data) 0))                  
            SSLOGERROR( ERRCLS_DEBUG,ESS816,51 , "");
      }
      else
      {
         SCatMsg(m[1],m[0],(Order)i);
         SFndLenMsg(m[0],&mlng);
         SFndLenMsg(m[1],&mlng1);
         if ((mlng1 != 4*TSTTIMES) || (mlng != 0))
            SSLOGERROR( ERRCLS_DEBUG,ESS817,52 , "");
         SRemPstMsg(&uData,m[1]);
         if ( uData != (Data) 0 )
            SSLOGERROR( ERRCLS_DEBUG,ESS818,53 , "");
         SAddPstMsg(uData,m[1]);
         if (((ret1 = SRemPreMsg(&uData,m[0])) != ROKDNA) ||
             ((ret2 = SRemPstMsg(&uData,m[0])) != ROKDNA) || 
             (uData != (Data) 0))                  
            SSLOGERROR( ERRCLS_DEBUG,ESS819,54 , "");
      }
   }
   
   SPutMsg(m[0]);
   SPutMsg(m[1]);
   
   SGetMsg(region,pool,&m[0]);
   
   for ( j = 0; j < 128; j++ )
      SAddPstMsg((Data) j,m[0]);
   
   idx = 0;
   SSegMsg(m[0],idx,&m[1]); 
   for ( j = 0; j < 128; j++ )
   {
      SExamMsg(&uData,m[1],(MsgLen) j);
      if ( uData != (Data) j )
         SSLOGERROR( ERRCLS_DEBUG,ESS820,55 , "");
   }
   if ((ret1 = SRepMsg(uData,m[0],idx)) != ROKDNA)
      SSLOGERROR( ERRCLS_DEBUG,ESS821,56 , "");
   
   SPutMsg(m[0]);
   
   idx = 128;
   SSegMsg(m[1],idx,&m[0]);
   SFndLenMsg(m[1],&mlng1);
   if ((m[0] != NULLP) || (mlng1 != idx))
      SSLOGERROR( ERRCLS_DEBUG,ESS822,57 , "");
   
   idx = 64;
   SSegMsg(m[1],idx,&m[0]);
   SFndLenMsg(m[0],&mlng);
   SFndLenMsg(m[1],&mlng1);
   if ((mlng != idx) || (mlng1 != idx))
      SSLOGERROR( ERRCLS_DEBUG,ESS823,58 , "");
   for ( j = 0; j < (128-idx); j++ )
   {
      SExamMsg(&uData,m[0],(MsgLen) j);
      if ( uData != (Data) (idx+j) )
         SSLOGERROR( ERRCLS_DEBUG,ESS824,59 , "");
   }
   SCatMsg(m[1],m[0],M1M2);
   
   SPutMsg(m[0]);
   
   idx = 63;
   SSegMsg(m[1],idx,&m[0]);
   /* ss021.103 - Addition to test SSwapMsg */
   SSwapMsg(m[0],m[1]);
   SSwapMsg(m[1],m[0]);
   SFndLenMsg(m[0],&mlng);
   SFndLenMsg(m[1],&mlng1);
   if ((mlng != idx+2) || (mlng1 != idx))
      SSLOGERROR( ERRCLS_DEBUG,ESS825,60 , "");
   for ( j = 0; j < (128-idx); j++)
   {
      SExamMsg(&uData,m[0],(MsgLen) j);
      if ( uData != (Data) (idx+j) )
         SSLOGERROR( ERRCLS_DEBUG,ESS826,61 , "");
   }
   
   SPutMsg(m[0]);
   SPutMsg(m[1]);
   
   SGetMsg(region,pool,&m[0]);
   
   for ( j = 0, sData = 0; j < mLen; j++, sData++ )
      SPkS8((S8) sData,m[0]);
   for ( j = 0; j < mLen; j++ )
   {
      SExamMsg(&sData,m[0],(MsgLen) j);
      if ( sData != (Data) ((mLen - 1)-j) )
         SSLOGERROR( ERRCLS_DEBUG,ESS827,62 , "");
   }
   for ( j = 0; j < mLen; j++ )
   {
      SUnpkS8(&s8,m[0]);
      if ( s8 != (S8) ((mLen - 1)-j) )
         SSLOGERROR( ERRCLS_DEBUG,ESS828,63 , "");
   }
   
   SPutMsg(m[0]);
   
   SGetMsg(region,pool,&m[0]);
   
   for ( j = 0, uData = (Data) 0; j < mLen; j++, uData++ )
      SPkU8((U8) uData,m[0]);
   for ( j = 0; j < mLen; j++ )
   {
      SExamMsg(&uData,m[0],(MsgLen) j);
      if ( uData != (Data)((mLen - 1)-j) )
         SSLOGERROR( ERRCLS_DEBUG,ESS829,64 , "");
   }
   for ( j = 0; j < mLen; j++ )
   {        
      SUnpkU8(&uData,m[0]);
      if ( uData != (Data)((mLen - 1)-j) )
         SSLOGERROR( ERRCLS_DEBUG,ESS830,65 , "");
   }
   
   SPutMsg(m[0]);
   
   SGetMsg(region,pool,&m[0]);
   
   for ( j = 0; j < mLen; j++ )
      SAddPreMsg((Data) j,m[0]);
   
   SCpyMsgMsg(m[0],region,pool,&m[1]);
   
   for ( j = 0; j < mLen; j++ )
   {
      SExamMsg(&uData,m[1],(MsgLen) j);
      if ( uData != (Data) ((mLen - 1)-j) )
         SSLOGERROR( ERRCLS_DEBUG,ESS831,67 , "");
   }
   
   SPutMsg(m[0]);
   SPutMsg(m[1]);

   tskEnd(2);
   RETVALUE(ROK);

} /* end of permTsk2 */


/*
*
*       Fun:   permTsk3
*
*       Desc:  Miscellaneous test
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: 
*
*       File:  ss_acc.c
*
*/
#ifdef ANSI
PRIVATE S16 permTsk3
(
Pst *pst,                       /* pst structure */
Buffer *mBuf                    /* message buffer */
)
#else
PRIVATE S16 permTsk3(pst, mBuf)
Pst *pst;                       /* pst structure */
Buffer *mBuf;                   /* message buffer */
#endif
{
   Buffer *m[TSTTIMES];
   PRIVATE Ticks sTime1 = 0;
   /* ss026.103 - Modification to fix warning */
   PRIVATE S16 sTimeCnt = 0;
   PRIVATE Random val1;
   PRIVATE S16 valCnt = 0;
   Random value2;
   DateTime dt;
   S16 ret1;
   Ticks sTime2;
   Status status;
   
   TRC2(permTsk3)

   if (mBuf)
      SPutMsg(mBuf);

   SGetSysTime(&sTime2);
   if (sTime2 == sTime1 )
   {
      /* ss019.103 - Modified for more latency */
      if (sTimeCnt >= 10000)
      {
         SSLOGERROR( ERRCLS_DEBUG,ESS832,69 , "");
      }
      else
         sTimeCnt++;
   }
   else
   {
      SGetSysTime(&sTime1);
      sTimeCnt = 0;
   }
   
   SGetMsg(region,pool,&m[0]);
   SChkRes(region, pool, &status);
   if ( status == 0 )
      SSLOGERROR( ERRCLS_DEBUG,ESS833,70 , "");
   SPutMsg(m[0]);

   SRandom(&value2);
   if ( value2 == val1 )
   {
      if (valCnt >= 100)
         SSLOGERROR( ERRCLS_DEBUG,ESS834,71 , "");
      else
         valCnt++;
   }
   else
   {
      SRandom(&val1);
      valCnt = 0;
   }
   
   if ((ret1 = SGetDateTime(&dt)) != ROK)
      SSLOGERROR( ERRCLS_DEBUG,ESS835,72 , "");
   
   tskEnd(3);
   
   RETVALUE(ROK);

} /* end of permTsk3 */


/*
*
*       Fun:   permTsk4
*
*       Desc:  static memory tests
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: 
*
*       File:  ss_acc.c
*
*/
#ifdef ANSI
PRIVATE S16 permTsk4
(
Pst *pst,                       /* pst structure */
Buffer *mBuf                    /* message buffer */
)
#else
PRIVATE S16 permTsk4(pst, mBuf)
Pst *pst;                       /* pst structure */
Buffer *mBuf;                   /* message buffer */
#endif
{
   REG1 S32 i;
   REG2 S32 j;
   Data *sBuf[TSTTIMES];
   Data *s;

   TRC2(permTsk4)

   if (mBuf)
      SPutMsg(mBuf);

   for ( j = 0; j < TSTTIMES; j++ )
   {
      /* Get static buffer from static memory */
      SGetSBuf(region, sPool0, &sBuf[j], (Size) MAXSMEMLEN);
      
      s = sBuf[j];
      for (i = 0; i < MAXSMEMLEN; i++)
      {
         *s = (Data) j;
         s++;
      }
      
      s = sBuf[j];
      for (i = 0; i < MAXSMEMLEN; i++)
      {
         if (*s != (Data) j)
            SSLOGERROR( ERRCLS_DEBUG,ESS836,73 , "");
         s++;
      }
      
      /* Put static buffer to static memory */
      SPutSBuf(region, sPool0, sBuf[j], (Size) MAXSMEMLEN);
   }

   
   for ( j = 0; j < TSTTIMES; j++ )
   {
      /* Get static buffer from static memory */
      SGetSBuf(region, sPool0, &sBuf[j], (Size) MAXSMEMLEN);
      
      s = sBuf[j];
      for (i = 0; i < MAXSMEMLEN; i++)
      {
         *s = (Data) j;
         s++;
      }
   }
   
   for ( j = 0; j < TSTTIMES; j++ )
   {
      s = sBuf[j];
      for (i = 0; i < MAXSMEMLEN; i++)
      {
         if (*s != (Data) j)
            SSLOGERROR( ERRCLS_DEBUG,ESS837,74 , "");
         s++;
      }
      
      /* Put static buffer to static memory */
      SPutSBuf(region, sPool0, sBuf[j], (Size) MAXSMEMLEN);
   }
   
   
   for ( j = 0; j < TSTTIMES; j++ )
   {
      /* Get static buffer from static memory */
      SGetSBuf(region, sPool0, &sBuf[j], (Size) (MAXSMEMLEN - 1));
      
      s = sBuf[j];
      for (i = 0; i < (MAXSMEMLEN - 1); i++)
      {
         *s = (Data) j;
         s++;
      }
      
      s = sBuf[j];
      for (i = 0; i < (MAXSMEMLEN - 1); i++)
      {
         if (*s != (Data) j)
            SSLOGERROR( ERRCLS_DEBUG,ESS838,75 , "");
         s++;
      }
      
      /* Put static buffer to static memory */
      SPutSBuf(region, sPool0, sBuf[j], (Size) (MAXSMEMLEN - 1));
   }
   
   
   for ( j = 0; j < TSTTIMES; j++ )
   {
      /* Get static buffer from static memory */
      SGetSBuf(region, sPool0, &sBuf[j], (Size) (MAXSMEMLEN - 1));
      
      s = sBuf[j];
      for (i = 0; i < (MAXSMEMLEN - 1); i++)
      {
         *s = (Data) j;
         s++;
      }
   }
   
   for ( j = 0; j < TSTTIMES; j++ )
   {
      s = sBuf[j];
      for (i = 0; i < (MAXSMEMLEN - 1); i++)
      {
         if (*s != (Data) j)
            SSLOGERROR( ERRCLS_DEBUG,ESS839,76 , "");
         s++;
      }
      
      /* Put static buffer to static memory */
      SPutSBuf(region, sPool0, sBuf[j], (Size) (MAXSMEMLEN - 1));
   }
   
   tskEnd(4);
   RETVALUE(ROK);

} /* end of permTsk4 */

/*
*
*       Fun:   permTsk5
*
*       Desc:  timer tests
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: 
*
*       File:  ss_acc.c
*
*/
#ifdef ANSI
PRIVATE S16 permTsk5
(
Pst *pst,                       /* pst structure */
Buffer *mBuf                    /* message buffer */
)
#else
PRIVATE S16 permTsk5(pst, mBuf)
Pst *pst;                       /* pst structure */
Buffer *mBuf;                   /* message buffer */
#endif
{
   /* ss026.103 - Modification to fix warning */
   PRIVATE S32 tmrTCnt[NMBTMRTSKS]={0,0};

   TRC2(permTsk5)

   if (mBuf)
      SPutMsg(mBuf);


   if (tskTmrCnt[0] == 0)
   {
      /* ss019.103 - Modified for more latency */
      if (tmrTCnt[0] > (100000 * TSK1TMR))
      {
         SSLOGERROR( ERRCLS_DEBUG,ESS840,77 , "");
      }
      else
         tmrTCnt[0]++;
   }
   else
      tmrTCnt[0] = 0;
   
   if (tskTmrCnt[1] == 0)
   {
      if (tmrTCnt[1] > (10000 * TSK2TMR))
         SSLOGERROR( ERRCLS_DEBUG,ESS841,78 , "");
      else
         tmrTCnt[1]++;
   }
   else
      tmrTCnt[1] = 0;
   
   tskEnd(5);
   RETVALUE(ROK);

} /* end of permTsk5 */


/*
*
*       Fun:   permTsk6
*
*       Desc:  
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: 
*
*       File:  ss_acc.c
*
*/
#ifdef ANSI
PRIVATE S16 permTsk6
(
Pst *pst,                       /* pst structure */
Buffer *mBuf                    /* message buffer */
)
#else
PRIVATE S16 permTsk6(pst, mBuf)
Pst *pst;                       /* pst structure */
Buffer *mBuf;                   /* message buffer */
#endif
{
   Buffer *m[TSTTIMES];
   Buffer *n[TSTTIMES];
   Queue q;
   Queue q1;
   QLen qlng;
   QLen qlng1;
   QLen size;
   REG1 S32 i;

   TRC2(permTsk6)

   if (mBuf)
      SPutMsg(mBuf);

   /* concatenate queue */
   SInitQueue(&q);
   SInitQueue(&q1);
   
   for ( i = 1;i <= 2;i++ )
   {
      SGetMsg(region,pool,&m[0]);
      SQueueLast(m[0],&q);
      SFndLenQueue(&q,&qlng);
      
      SGetMsg(region,pool,&n[0]);
      SQueueFirst(n[0],&q1);
      SFndLenQueue(&q1,&qlng1);
         
      size = qlng+qlng1;
      if ( i == Q1Q2 )
      {
         SCatQueue(&q,&q1,Q1Q2);
         if ( size != q.crntSize )
            SSLOGERROR( ERRCLS_DEBUG,ESS842,17 , "");
         SDequeueFirst(&m[1],&q);
         if ( m[1] != m[0] )
            SSLOGERROR( ERRCLS_DEBUG,ESS843,18 , "");
         SDequeueLast(&n[1],&q);
         if ( n[1] != n[0] )
            SSLOGERROR( ERRCLS_DEBUG,ESS844,19 , "");
         SDequeueFirst(&n[2],&q1);
         if ( n[2] != NULLP )
            SSLOGERROR( ERRCLS_DEBUG,ESS845,20 , "");
         SPutMsg(m[0]);
         SPutMsg(n[0]);
      }
      else
      {
         SCatQueue(&q,&q1,Q2Q1);
         if ( size != q.crntSize )
            SSLOGERROR( ERRCLS_DEBUG,ESS846,21 , "");
         SDequeueFirst(&n[1],&q);
         if ( n[1] != n[0] )
            SSLOGERROR( ERRCLS_DEBUG,ESS847,22 , "");
         SDequeueLast(&m[1],&q);
         if ( m[1] != m[0] )
            SSLOGERROR( ERRCLS_DEBUG,ESS848,23 , "");
         SDequeueFirst(&n[2],&q1);
         if ( n[2] != NULLP )
            SSLOGERROR( ERRCLS_DEBUG,ESS849,24 , "");
         SPutMsg(m[0]);
         SPutMsg(n[0]);
      }               
   }

   tskEnd(6);
   RETVALUE(ROK);
} /* end of permTsk6 */


/*
*
*       Fun:   permTsk7
*
*       Desc:  
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: 
*
*       File:  ss_acc.c
*
*/
#ifdef ANSI
PRIVATE S16 permTsk7
(
Pst *pst,                       /* pst structure */
Buffer *mBuf                    /* message buffer */
)
#else
PRIVATE S16 permTsk7(pst, mBuf)
Pst *pst;                       /* pst structure */
Buffer *mBuf;                   /* message buffer */
#endif
{
   REG1 S32 i;
   Buffer *m[TSTTIMES];
   Queue q;
   Buffer *bufPtr;
   QLen idx;
   
   TRC2(permTsk7)

   if (mBuf)
      SPutMsg(mBuf);

   /* examine queue */
   SInitQueue(&q);
   
   for (i = 0; i < TSTTIMES; i++)
   {
      SGetMsg(region,pool,&m[i]);
      SQueueLast(m[i],&q);
   }
   
   idx = 0;
   SExamQueue(&bufPtr, &q, idx);
   if ( bufPtr != m[idx] )
      SSLOGERROR( ERRCLS_DEBUG,ESS850,25 , "");
   idx = TSTTIMES-1;
   SExamQueue(&bufPtr, &q, idx);
   if ( bufPtr != m[idx] )
      SSLOGERROR( ERRCLS_DEBUG,ESS851,26 , "");
   
   for (i = 0; i < TSTTIMES; i++)
      SPutMsg(m[i]);            
   
   tskEnd(7);
   RETVALUE(ROK);

} /* end of permTsk7 */


/*
*
*       Fun:   permTsk8
*
*       Desc:  
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: 
*
*       File:  ss_acc.c
*
*/
#ifdef ANSI
PRIVATE S16 permTsk8
(
Pst *pst,                       /* pst structure */
Buffer *mBuf                    /* message buffer */
)
#else
PRIVATE S16 permTsk8(pst, mBuf)
Pst *pst;                       /* pst structure */
Buffer *mBuf;                   /* message buffer */
#endif
{
   REG1 S32 i;
   Buffer *m[TSTTIMES];
   Buffer *n[TSTTIMES];
   Queue q;
   QLen idx;
   QLen qlng;
   
   TRC2(permTsk8)

   if (mBuf)
      SPutMsg(mBuf);


   /* add/remove to/from queue */
   SInitQueue(&q);
   SGetMsg(region,pool,&n[0]);

   idx = 0;
   SAddQueue(n[0],&q,idx);
   SExamQueue(&n[1],&q,idx);
   SFndLenQueue(&q,&qlng);
   if ( (n[1] != n[0]) || (qlng != 1) )
      SSLOGERROR( ERRCLS_DEBUG,ESS852,27 , "");
   SRemQueue(&n[2],&q,idx);
   SFndLenQueue(&q,&qlng);
   if ( (n[2] != n[0]) || (qlng != 0) )
      SSLOGERROR( ERRCLS_DEBUG,ESS853,28 , "");
   
   for (i = 0; i < TSTTIMES; i++)
   {
      SGetMsg(region,pool,&m[i]);
      SQueueLast(m[i],&q);
   }
   
   idx = (QLen) TSTTIMES / 2;
   SAddQueue(n[0],&q,idx);
   SExamQueue(&n[1],&q,idx);
   SRemQueue(&n[2],&q,idx);
   if ( (n[1] != n[0]) || (n[2] != n[0]) )
      SSLOGERROR( ERRCLS_DEBUG,ESS854,29 , "");
   
   idx = TSTTIMES;
   SAddQueue(n[0],&q,idx);
   SExamQueue(&n[1],&q,idx);
   SRemQueue(&n[2],&q,idx);
   if ( (n[1] != n[0]) || (n[2] != n[0]) )
      SSLOGERROR( ERRCLS_DEBUG,ESS855,30 , "");
   
   for (i = 0; i < TSTTIMES; i++)
      SPutMsg(m[i]);            
   SPutMsg(n[0]);
   
   tskEnd(8);
   RETVALUE(ROK);

} /* end of permTsk8 */

/* ss019.103 - Addition for multithreaded task test activation functions */
/*                                     
*
*       Fun:   tst0mtActvTsk
*
*       Desc:  Sample function for test task 0 activation.
*
*       Ret:   ROK       - ok
*
*       Notes: None
*
*       File:  ss_acc.c
*
*/
 
#ifdef ANSI
PUBLIC S16 tst0mtActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 tst0mtActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   /* ss026.103 - Deletion to fix warnings */
   S16 ret;
   Buffer *n[TSTTIMES];
   Pool pooll;
   Region regionn;

   TRC2(tst0mtActvTsk)
 


   switch(pst->srcInst)
   {
      case TSTINST1:
           {
            SPutMsg(mBuf);
        /* ss031.103: modification: multiple proc related enhancements */
#ifdef SS_MULTIPLE_PROCS
            SDetachTTsk(PROC_MP_ID0, TST0ENT,TSTINST1);
            SDeregTTsk(PROC_MP_ID0, TST0ENT,TSTINST1);
#else
            SDetachTTsk(TST0ENT,TSTINST1);
            SDeregTTsk(TST0ENT,TSTINST1);
#endif /* SS_MULTIPLE_PROCS */

            SDestroySTsk(sTskId[1]);
                  ACKCount++;
            break;
           }
      case TSTINST2:
           {
            SPutMsg(mBuf);
        /* ss031.103: modification: multiple proc related enhancements */
#ifdef SS_MULTIPLE_PROCS
            SDetachTTsk(PROC_MP_ID0, TST0ENT,TSTINST2);
            SDeregTTsk(PROC_MP_ID0, TST0ENT,TSTINST2);
#else
            SDetachTTsk(TST0ENT,TSTINST2);
            SDeregTTsk(TST0ENT,TSTINST2);
#endif /* SS_MULTIPLE_PROCS */

            SDestroySTsk(sTskId[2]);
                  ACKCount++;
            break;
           }
      case TSTINST3:
           {
            SPutMsg(mBuf);
        /* ss031.103: modification: multiple proc related enhancements */
#ifdef SS_MULTIPLE_PROCS
            SDetachTTsk(PROC_MP_ID0, TST0ENT,TSTINST3);
            SDeregTTsk(PROC_MP_ID0, TST0ENT,TSTINST3);
#else
            SDetachTTsk(TST0ENT,TSTINST3);
            SDeregTTsk(TST0ENT,TSTINST3);
#endif /* SS_MULTIPLE_PROCS */

            SDestroySTsk(sTskId[3]);
                  ACKCount++;
            break;
           }
      case TSTINST4:
           {
            SPutMsg(mBuf);
        /* ss031.103: modification: multiple proc related enhancements */
#ifdef SS_MULTIPLE_PROCS
            SDetachTTsk(PROC_MP_ID0, TST0ENT,TSTINST4);
            SDeregTTsk(PROC_MP_ID0, TST0ENT,TSTINST4);
#else
            SDetachTTsk(TST0ENT,TSTINST4);
            SDeregTTsk(TST0ENT,TSTINST4);
#endif /* SS_MULTIPLE_PROCS */

            SDestroySTsk(sTskId[4]);
                  ACKCount++;
            break;
           }
      case TSTINST5:
           {
            SPutMsg(mBuf);
        /* ss031.103: modification: multiple proc related enhancements */
#ifdef SS_MULTIPLE_PROCS
            SDetachTTsk(PROC_MP_ID0, TST0ENT,TSTINST5);
            SDeregTTsk(PROC_MP_ID0, TST0ENT,TSTINST5);
#else
            SDetachTTsk(TST0ENT,TSTINST5);
            SDeregTTsk(TST0ENT,TSTINST5);
#endif /* SS_MULTIPLE_PROCS */

            SDestroySTsk(sTskId[5]);
                  ACKCount++;
                  break;
           }

   };
   
   if(ACKCount == 5)
   {
      pooll = SP_POOL;
      regionn = 0;
      ACKCount = 0;

/* ss029.103: modification: procId added */
#ifdef SS_MULTIPLE_PROCS
      ret = SRegTTsk(PROC_MP_ID0, TST0ENT, TSTINST1, TTNORM, PRIOR0, NULL, tst1mtActvTsk);
#else /* SS_MULTIPLE_PROCS */
      ret = SRegTTsk(TST0ENT, TSTINST1, TTNORM, PRIOR0, NULL, tst1mtActvTsk);
#endif /* SS_MULTIPLE_PROCS */
      if (ret != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS856, (ErrVal) ret,
                     "Could not register task");
#endif
         RETVALUE(ret);
      }
      ret = SCreateSTsk(SS_NORM_TSK_PRI, &sTskId[1]);
      if (ret != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS857, (ErrVal) ret,
                     "Could not create system task");
#endif
/* ss029.103: modification: procId added */
#ifdef SS_MULTIPLE_PROCS
         SDeregTTsk(PROC_MP_ID0, TST0ENT, TSTINST1);
#else /* SS_MULTIPLE_PROCS */
         SDeregTTsk(TST0ENT, TSTINST1);
#endif /* SS_MULTIPLE_PROCS */
         RETVALUE(ret);
      }     
/* ss029.103: modification: procId added */
#ifdef SS_MULTIPLE_PROCS
      ret = SAttachTTsk(PROC_MP_ID0, TST0ENT, TSTINST1,sTskId[1]);
#else /* SS_MULTIPLE_PROCS */
      ret = SAttachTTsk(TST0ENT, TSTINST1,sTskId[1]);
#endif /* SS_MULTIPLE_PROCS */
      if (ret != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS858, (ErrVal) ret,
                     "Could not attach TAPA task to system task");
#endif
         SDestroySTsk(sTskId[1]);
/* ss029.103: modification: procId added */
#ifdef SS_MULTIPLE_PROCS
         SDeregTTsk(PROC_MP_ID0, TST0ENT, TSTINST1);
#else /* SS_MULTIPLE_PROCS */
         SDeregTTsk(TST0ENT, TSTINST1);
#endif /* SS_MULTIPLE_PROCS */
      }

/* ss029.103: modification: procId added */
#ifdef SS_MULTIPLE_PROCS
      ret = SRegTTsk(PROC_MP_ID0, TST0ENT, TSTINST2, TTNORM, PRIOR0, NULL, tst2mtActvTsk);
#else /* SS_MULTIPLE_PROCS */
      ret = SRegTTsk(TST0ENT, TSTINST2, TTNORM, PRIOR0, NULL, tst2mtActvTsk);
#endif /* SS_MULTIPLE_PROCS */
      if (ret != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS859, (ErrVal) ret,
                     "Could not register task");
#endif
         RETVALUE(ret);
      }
      
      ret = SCreateSTsk(SS_NORM_TSK_PRI, &sTskId[2]);
      if (ret != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS860, (ErrVal) ret,
                     "Could not create system task");
#endif
/* ss029.103: modification: procId added */
#ifdef SS_MULTIPLE_PROCS
         SDeregTTsk(PROC_MP_ID0, TST0ENT, TSTINST2);
#else /* SS_MULTIPLE_PROCS */
         SDeregTTsk(TST0ENT, TSTINST2);
#endif /* SS_MULTIPLE_PROCS */
         RETVALUE(ret);
      }     
      
/* ss029.103: modification: procId added */
#ifdef SS_MULTIPLE_PROCS
      ret = SAttachTTsk(PROC_MP_ID0, TST0ENT, TSTINST2, sTskId[2]);
#else /* SS_MULTIPLE_PROCS */
      ret = SAttachTTsk(TST0ENT, TSTINST2, sTskId[2]);
#endif /* SS_MULTIPLE_PROCS */
      if (ret != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS861, (ErrVal) ret,
                     "Could not attach TAPA task to system task");
#endif
         SDestroySTsk(sTskId[2]);
/* ss029.103: modification: procId added */
#ifdef SS_MULTIPLE_PROCS
         SDeregTTsk(PROC_MP_ID0, TST0ENT, TSTINST2);
#else /* SS_MULTIPLE_PROCS */
         SDeregTTsk(TST0ENT, TSTINST2);
#endif /* SS_MULTIPLE_PROCS */
      }

/* ss029.103: modification: procId added */
#ifdef SS_MULTIPLE_PROCS
      ret = SRegTTsk(PROC_MP_ID0, TST0ENT, TSTINST3, TTNORM, PRIOR0, NULL, tst3mtActvTsk);
#else /* SS_MULTIPLE_PROCS */
      ret = SRegTTsk(TST0ENT, TSTINST3, TTNORM, PRIOR0, NULL, tst3mtActvTsk);
#endif /* SS_MULTIPLE_PROCS */
      if (ret != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS862, (ErrVal) ret,
                     "Could not register task");
#endif
         RETVALUE(ret);
      }
      ret = SCreateSTsk(SS_NORM_TSK_PRI, &sTskId[3]);
      if (ret != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS863, (ErrVal) ret,
                     "Could not create system task");
#endif
/* ss029.103: modification: procId added */
/* ss031.103: modification: compilation correction */
#ifdef SS_MULTIPLE_PROCS
         SDeregTTsk(PROC_MP_ID0, TST0ENT, TSTINST3);
#else /* SS_MULTIPLE_PROCS */
         SDeregTTsk(TST0ENT, TSTINST3);
#endif /* SS_MULTIPLE_PROCS */
         RETVALUE(ret);
      }     
/* ss029.103: modification: procId added */
#ifdef SS_MULTIPLE_PROCS
      ret = SAttachTTsk(PROC_MP_ID0, TST0ENT, TSTINST3, sTskId[3]);
#else
      ret = SAttachTTsk(TST0ENT, TSTINST3, sTskId[3]);
#endif
      if (ret != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS864, (ErrVal) ret,
                     "Could not attach TAPA task to system task");
#endif
         SDestroySTsk(sTskId[3]);
/* ss029.103: modification: procId added */
#ifdef SS_MULTIPLE_PROCS
         SDeregTTsk(PROC_MP_ID0, TST0ENT, TSTINST3);
#else
         SDeregTTsk(TST0ENT, TSTINST3);
#endif
      }

/* ss029.103: modification: procId added */
#ifdef SS_MULTIPLE_PROCS
      ret = SRegTTsk(PROC_MP_ID0, TST0ENT, TSTINST4, TTNORM, PRIOR0, NULL, tst4mtActvTsk);
#else
      ret = SRegTTsk(TST0ENT, TSTINST4, TTNORM, PRIOR0, NULL, tst4mtActvTsk);
#endif
      if (ret != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS865, (ErrVal) ret,
                     "Could not register task");
#endif
         RETVALUE(ret);
      }
      ret = SCreateSTsk(SS_NORM_TSK_PRI, &sTskId[4]);
      if (ret != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS866, (ErrVal) ret,
                     "Could not create system task");
#endif
/* ss029.103: modification: procId added */
#ifdef SS_MULTIPLE_PROCS
         SDeregTTsk(PROC_MP_ID0, TST0ENT, TSTINST4);
#else
         SDeregTTsk(TST0ENT, TSTINST4);
#endif
         RETVALUE(ret);
      }     
/* ss029.103: modification: procId added */
#ifdef SS_MULTIPLE_PROCS
      ret = SAttachTTsk(PROC_MP_ID0, TST0ENT, TSTINST4, sTskId[4]);
#else
      ret = SAttachTTsk(TST0ENT, TSTINST4, sTskId[4]);
#endif
      if (ret != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS867, (ErrVal) ret,
                     "Could not attach TAPA task to system task");
#endif
         SDestroySTsk(sTskId[4]);
/* ss029.103: modification: procId added */
#ifdef SS_MULTIPLE_PROCS
         SDeregTTsk(PROC_MP_ID0, TST0ENT, TSTINST4);
#else
         SDeregTTsk(TST0ENT, TSTINST4);
#endif
      }

/* ss029.103: modification: procId added */
#ifdef SS_MULTIPLE_PROCS
      ret = SRegTTsk(PROC_MP_ID0, TST0ENT, TSTINST5, TTNORM, PRIOR0, NULL, tst5mtActvTsk);
#else
      ret = SRegTTsk(TST0ENT, TSTINST5, TTNORM, PRIOR0, NULL, tst5mtActvTsk);
#endif
      if (ret != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS868, (ErrVal) ret,
                     "Could not register task");
#endif
         RETVALUE(ret);
      }
      ret = SCreateSTsk(SS_NORM_TSK_PRI, &sTskId[5]);
      if (ret != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS869, (ErrVal) ret,
                     "Could not create system task");
#endif
/* ss029.103: modification: procId added */
#ifdef SS_MULTIPLE_PROCS
         SDeregTTsk(PROC_MP_ID0, TST0ENT, TSTINST5);
#else
         SDeregTTsk(TST0ENT, TSTINST5);
#endif
         RETVALUE(ret);
      }     
/* ss029.103: modification: procId added */
#ifdef SS_MULTIPLE_PROCS
      ret = SAttachTTsk(PROC_MP_ID0, TST0ENT, TSTINST5, sTskId[5]);
#else
      ret = SAttachTTsk(TST0ENT, TSTINST5, sTskId[5]);
#endif
      if (ret != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS870, (ErrVal) ret,
                     "Could not attach TAPA task to system task");
#endif
         SDestroySTsk(sTskId[5]);
/* ss029.103: modification: procId added */
#ifdef SS_MULTIPLE_PROCS
         SDeregTTsk(PROC_MP_ID0, TST0ENT, TSTINST5);
#else
         SDeregTTsk(TST0ENT, TSTINST5);
#endif
      }

      SGetMsg(regionn, pooll, &n[0]);
      /* Post the message to the test task 1 */
      pst->event     = 1;               /* event */
      pst->prior     = 0;               /* priority */
      pst->route     = 0;               /* route */
      pst->dstProcId = SFndProcId();    /* destination processor id */
      pst->dstEnt    = TST0ENT;         /* destination entity */
      pst->dstInst   = TSTINST1;        /* destination instance */
      pst->srcProcId = SFndProcId();    /* source processor id */
      pst->srcEnt    = TST0ENT;         /* source entity */
      pst->srcInst   = TSTINST0;        /* source instance */
      if (SPstTsk(pst, n[0]) != ROK)
      {
         SSLOGERROR( ERRCLS_DEBUG, ESS871,ERRZERO, "" );
      }            
         
      SGetMsg(regionn, pooll, &n[1]);
      /* Post the message to the test task 2 */
      pst->event     = 2;               /* event */
      pst->prior     = 0;               /* priority */
      pst->route     = 0;               /* route */
      pst->dstProcId = SFndProcId();    /* destination processor id */
      pst->dstEnt    = TST0ENT;         /* destination entity */
      pst->dstInst   = TSTINST2;        /* destination instance */
      pst->srcProcId = SFndProcId();    /* source processor id */
      pst->srcEnt    = TST0ENT;         /* source entity */
      pst->srcInst   = TSTINST0;        /* source instance */
      if (SPstTsk(pst, n[1]) != ROK)
      {
         SSLOGERROR( ERRCLS_DEBUG, ESS872,ERRZERO, "" );
      }
         
      SGetMsg(regionn, pooll, &n[2]);
      /* Post the message to the test task 3 */
      pst->event     = 3;               /* event */
      pst->prior     = 0;               /* priority */
      pst->route     = 0;               /* route */
      pst->dstProcId = SFndProcId();    /* destination processor id */
      pst->dstEnt    = TST0ENT;         /* destination entity */
      pst->dstInst   = TSTINST3;        /* destination instance */
      pst->srcProcId = SFndProcId();    /* source processor id */
      pst->srcEnt    = TST0ENT;         /* source entity */
      pst->srcInst   = TSTINST0;        /* source instance */
      if (SPstTsk(pst, n[2]) != ROK)
      {
         SSLOGERROR( ERRCLS_DEBUG, ESS873,ERRZERO, "" );
      }
         
      SGetMsg(regionn, pooll, &n[3]);
      /* Post the message to the test task 4 */
      pst->event     = 4;               /* event */
      pst->prior     = 0;               /* priority */
      pst->route     = 0;               /* route */
      pst->dstProcId = SFndProcId();    /* destination processor id */
      pst->dstEnt    = TST0ENT;         /* destination entity */
      pst->dstInst   = TSTINST4;        /* destination instance */
      pst->srcProcId = SFndProcId();    /* source processor id */
      pst->srcEnt    = TST0ENT;         /* source entity */
      pst->srcInst   = TSTINST0;        /* source instance */
      if (SPstTsk(pst, n[3]) != ROK)
      {
         SSLOGERROR( ERRCLS_DEBUG, ESS874,ERRZERO, "" );
      }
      SGetMsg(regionn, pooll, &n[4]);
      /* Post the message to the test task 5 */
      pst->event     = 5;               /* event */
      pst->prior     = 0;               /* priority */
      pst->route     = 0;               /* route */
      pst->dstProcId = SFndProcId();    /* destination processor id */
      pst->dstEnt    = TST0ENT;         /* destination entity */
      pst->dstInst   = TSTINST5;        /* destination instance */
      pst->srcProcId = SFndProcId();    /* source processor id */
      pst->srcEnt    = TST0ENT;         /* source entity */
      pst->srcInst   = TSTINST0;        /* source instance */
      if (SPstTsk(pst, n[4]) != ROK)
      {
         SSLOGERROR( ERRCLS_DEBUG, ESS875,ERRZERO, "" );
      }
   }
   SExitTsk();
   RETVALUE(ROK);

} /* end of tst0ActvTsk */

/*                                     
*
*       Fun:   tst1ActvTsk
*
*       Desc:  Sample function for test task 1 activation.
*
*       Ret:   ROK       - ok
*
*       Notes: None
*
*       File:  ss_acc.c
*
*/
 
#ifdef ANSI
PUBLIC S16 tst1mtActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 tst1mtActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   /* ss026.103 - Deletion to fix warnings */
 
   TRC2(tst1mtActvTsk)

   /* Post the message to the test task 0 */
   pst->event     = 1;               /* event */
   pst->prior     = 0;               /* priority */
   pst->route     = 0;               /* route */
   pst->dstProcId = SFndProcId();    /* destination processor id */
   pst->dstEnt    = TST0ENT;         /* destination entity */
   pst->dstInst   = TSTINST0;        /* destination instance */
   pst->srcProcId = SFndProcId();    /* source processor id */
   pst->srcEnt    = TST0ENT;         /* source entity */
   pst->srcInst   = TSTINST1;        /* source instance */
   if (SPstTsk(pst, mBuf) != ROK)
   {
      SSLOGERROR( ERRCLS_DEBUG, ESS876, ERRZERO, "" );
   }

   SExitTsk();
   RETVALUE(ROK);

} /* end of tst1mtActvTsk */

/*                                     
*
*       Fun:   tst2mtActvTsk
*
*       Desc:  Sample function for first test task activation.
*
*       Ret:   ROK       - ok
*
*       Notes: None
*
*       File:  ss_acc.c
*
*/
 
#ifdef ANSI
PUBLIC S16 tst2mtActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 tst2mtActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(tst2mtActvTsk)

   /* Post the message to the test task 0 */
   pst->event     = 2;               /* event */
   pst->prior     = 0;               /* priority */
   pst->route     = 0;               /* route */
   pst->dstProcId = SFndProcId();    /* destination processor id */
   pst->dstEnt    = TST0ENT;         /* destination entity */
   pst->dstInst   = TSTINST0;        /* destination instance */
   pst->srcProcId = SFndProcId();    /* source processor id */
   pst->srcEnt    = TST0ENT;         /* source entity */
   pst->srcInst   = TSTINST2;        /* source instance */
   if (SPstTsk(pst, mBuf) != ROK)
   {
      SSLOGERROR( ERRCLS_DEBUG, ESS877, ERRZERO, "" );
   }
   
   SExitTsk();
   RETVALUE(ROK);

} /* end of tst2mtActvTsk */

/*                                     
*
*       Fun:   tst3mtActvTsk
*
*       Desc:  Sample function for test task activation.
*
*       Ret:   ROK       - ok
*
*       Notes: None
*
*       File:  ss_acc.c
*
*/
 
#ifdef ANSI
PUBLIC S16 tst3mtActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 tst3mtActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(tst3mtActvTsk)

   /* Post the message to the test task 0 */
   pst->event     = 3;               /* event */
   pst->prior     = 0;               /* priority */
   pst->route     = 0;               /* route */
   pst->dstProcId = SFndProcId();    /* destination processor id */
   pst->dstEnt    = TST0ENT;         /* destination entity */
   pst->dstInst   = TSTINST0;        /* destination instance */
   pst->srcProcId = SFndProcId();    /* source processor id */
   pst->srcEnt    = TST0ENT;         /* source entity */
   pst->srcInst   = TSTINST3;        /* source instance */
   if (SPstTsk(pst, mBuf) != ROK)
   {
      SSLOGERROR( ERRCLS_DEBUG, ESS878, ERRZERO, "" );
   }
   
   SExitTsk();
   RETVALUE(ROK);

} /* end of tst3mtActvTsk */

/*                                     
*
*       Fun:   tst4mtActvTsk
*
*       Desc:  Sample function for test task activation.
*
*       Ret:   ROK       - ok
*
*       Notes: None
*
*       File:  ss_acc.c
*
*/
 
#ifdef ANSI
PUBLIC S16 tst4mtActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 tst4mtActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(tst4mtActvTsk)

   /* Post the message to the test task 0 */
   pst->event     = 4;               /* event */
   pst->prior     = 0;               /* priority */
   pst->route     = 0;               /* route */
   pst->dstProcId = SFndProcId();    /* destination processor id */
   pst->dstEnt    = TST0ENT;         /* destination entity */
   pst->dstInst   = TSTINST0;        /* destination instance */
   pst->srcProcId = SFndProcId();    /* source processor id */
   pst->srcEnt    = TST0ENT;         /* source entity */
   pst->srcInst   = TSTINST4;        /* source instance */
   if (SPstTsk(pst, mBuf) != ROK)
   {
      SSLOGERROR( ERRCLS_DEBUG, ESS879, ERRZERO, "" );
   }
   
   SExitTsk();
   RETVALUE(ROK);

} /* end of tst4mtActvTsk */

/*                                     
*
*       Fun:   tst5mtActvTsk
*
*       Desc:  Sample function for test task activation.
*
*       Ret:   ROK       - ok
*
*       Notes: None
*
*       File:  ss_acc.c
*
*/
 
#ifdef ANSI
PUBLIC S16 tst5mtActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 tst5mtActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(tst5mtActvTsk)

   /* Post the message to the test task 0 */
   pst->event     = 0;               /* event */
   pst->prior     = 0;               /* priority */
   pst->route     = 0;               /* route */
   pst->dstProcId = SFndProcId();    /* destination processor id */
   pst->dstEnt    = TST0ENT;         /* destination entity */
   pst->dstInst   = TSTINST0;        /* destination instance */
   pst->srcProcId = SFndProcId();    /* source processor id */
   pst->srcEnt    = TST0ENT;         /* source entity */
   pst->srcInst   = TSTINST5;        /* source instance */
   if (SPstTsk(pst, mBuf) != ROK)
   {
      SSLOGERROR( ERRCLS_DEBUG, ESS880, ERRZERO, "" );
   }

   SExitTsk();
   RETVALUE(ROK);

} /* end of tst5mtActvTsk */

#endif /* SS_SINGLE_THREADED */


/* ss029.103: addition: 
  test functions to test multiple proc functionality */ 
#ifdef SS_MULTIPLE_PROCS

/*                                     
*
*       Fun:   tstMpProcLst
*
*       Desc:  To test process list functionality after introducing multiple
*              processor IDs in single SSI 
*
*       Ret:   ROK       - ok
*
*       Notes: None
*
*       File:  ss_acc.c
*
*/
 
#ifdef ANSI
PRIVATE S16 tstMpProcLst
(
Void
)
#else
PRIVATE S16 tstMpProcLst(Void)
#endif
{
   ProcId procId1[SS_MAX_PROCS];
   ProcId procId2[SS_MAX_PROCS];
   S16 i;
   U16 count;

   TRC2(tstMpProcLst);

   /* initialize the two arrays */
   for (i = 0; i < SS_MAX_PROCS; i++)
   {
      procId1[i] = 1000 + i;
   }

   /* register one proc Id */

   TST_ADD_PROCID_LST(1, &procId1[0]);

   /* retrieve the proc list */
   TST_GET_PROCID_LST(&count, procId2);
   
   if (count != 1)
      RETVALUE(RFAILED);

   if (procId2[0] != procId1[0])
      RETVALUE(RFAILED);

   /* remove proc Id */
   TST_REM_PROCID_LST(1, &procId1[0]);

   /* add SS_MAX_PROCS */
   TST_ADD_PROCID_LST(SS_MAX_PROCS, procId1);

   /* get the list */
   TST_GET_PROCID_LST(&count, procId2);

   if (count != SS_MAX_PROCS)
      RETVALUE(RFAILED);

   for (i = 0; i < SS_MAX_PROCS; i++)
      if (procId1[i] != procId2[i])
         RETVALUE(RFAILED);

   /* remove the proc Ids */
   TST_REM_PROCID_LST(SS_MAX_PROCS, procId1);

   RETVALUE(ROK);
} /* end of tstMpProcLst */


/*                                     
*
*       Fun:   tstMpInitFunc
*
*       Desc:  To test new functionalities introduced for multiple processors in
*              single SSI instance
*
*       Ret:   ROK       - ok
*
*       Notes: None
*
*       File:  ss_acc.c
*
*/
 
#ifdef ANSI
PUBLIC S16 tstMpInitFunc
(
ProcId proc,
Ent ent,
Inst inst,
Region reg,
Reason reason,
Void **xxCb
)
#else
PUBLIC S16 tstMpInitFunc(proc, ent, inst, reg, reason, xxCb)
ProcId proc;
Ent ent;
Inst inst;
Region reg;
Reason reason;
Void **xxCb;
#endif
{
   PRIVATE S16 count = 0;

   /*ss013.301 :Fix for TRACE5 feature crash due to missing TRC MACRO*/
   TRC2(tstMpInitFunc)
   tskCb[count].proc = proc;
   tskCb[count].ent = ent;
   tskCb[count].inst = inst;

   *xxCb = (Void *) &tskCb[count];
   count++;

   RETVALUE(ROK);
}


/*                                     
*
*       Fun:   tstMpActvTsk0
*
*       Desc:  To test new functionalities introduced for multiple processors in
*              single SSI instance
*
*       Ret:   ROK       - ok
*
*       Notes: None
*
*       File:  ss_acc.c
*
*/
 
#ifdef ANSI
PUBLIC S16 tstMpActvTsk0
(
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 tstMpActvTsk0(pst, mBuf)
Pst *pst;
Buffer *mBuf;
#endif
{
   for (;;) 
;
}
 

/*                                     
*
*       Fun:   tstMpTskFunc
*
*       Desc:  To test task functionality after introducing multiple
*              processor IDs in single SSI 
*
*       Ret:   ROK       - ok
*
*       Notes: None
*
*       File:  ss_acc.c
*
*/
 
#ifdef ANSI
PRIVATE S16 tstMpTskFunc
(
Void
)
#else
PRIVATE S16 tstMpTskFunc(Void)
#endif
{
   ProcId procId1[SS_MAX_PROCS];
   S16 i, j, k;
   SSTskId tskIdMp[TST_MP_TTSKS];
   TskInit *tskCb1;
   S16 count;

   TRC2(tstMpTskFunc);

   /** add proc Ids to the list **/

   /* initialize the two arrays */
   for (i = 0; i < SS_MAX_PROCS; i++)
      procId1[i] = PROC_MP_ID0 + i;

   /* add SS_MAX_PROCS */
   TST_ADD_PROCID_LST(SS_MAX_PROCS, procId1);

   /** create a system task **/
   TST_CRE_STSK(SS_NORM_TSK_PRI, &tskIdMp[0]);
    
   /** 1. Register, Attach and Detach TAPA tasks: P1,E1,I1..P1,E1,I5 */  

   /* register TAPA tasks */
   for (i = 0; i < 5; i++)
      TST_REG_TTSK(procId1[0], ENT_MP_0, INST_MP_0 + i, TTNORM, PRIOR0, 
                     NULL, tstMpActvTsk0);

   /* attach TAPA tasks */
   for (i = 0; i < 5; i++)
      TST_ATT_TTSK(procId1[0], ENT_MP_0, INST_MP_0 + i, tskIdMp[0]);

   /* detach TAPA tasks */
   for (i = 0; i < 5; i++)
      TST_DET_TTSK(procId1[0], ENT_MP_0, INST_MP_0 + i);

   /* deregister TAPA tasks */
   for (i = 0; i < 5; i++)
      TST_DEREG_TTSK(procId1[0], ENT_MP_0, INST_MP_0 + i);

   /** register, Attach and Detach TAPA tasks: P1,E1,I1..P1,E5,I1 **/
   /* register TAPA tasks */
   for (i = 0; i < 5; i++)
      TST_REG_TTSK(procId1[0], ENT_MP_0 + i, INST_MP_0, TTNORM, PRIOR0, 
                     NULL, tstMpActvTsk0);

   /* attach TAPA tasks */
   for (i = 0; i < 5; i++)
      TST_ATT_TTSK(procId1[0], ENT_MP_0 + i, INST_MP_0, tskIdMp[0] );

   /* detach TAPA tasks */
   for (i = 0; i < 5; i++)
      TST_DET_TTSK(procId1[0], ENT_MP_0 + i, INST_MP_0);
   
   /* deregister TAPA tasks */
   for (i = 0; i < 5; i++)
      TST_DEREG_TTSK(procId1[0], ENT_MP_0 + i, INST_MP_0);
   
   /** register, Attach and Detach TAPA tasks: P1,E1,I1..P25,E5,I5 **/
   /* register */
   count = 0;
   for (i = 0; i < 25; i++)
      for (j = 0; j < 5; j++)
         for (k = 0; k < 5; k++, count++)
            TST_REG_TTSK(procId1[0] + i, ENT_MP_0 + j, INST_MP_0 + k, TTNORM, 
                           PRIOR0, tstMpInitFunc, tstMpActvTsk0);

   /* retrieve control block */
   count = 0;
   for (i = 0; i < 25; i++)
      for (j = 0; j < 5; j++)
         for (k = 0; k < 5; k++, count++)
         {
            TST_GET_XXCB(procId1[0] + i, ENT_MP_0 + j, INST_MP_0 + k, 
                           (Void **) &tskCb1);
            
            if (tskCb1 != &tskCb[count])
               SSLOGERROR(ERRCLS_DEBUG, ESS881, ERRZERO, "Wrong control block");
         }

   /* attach TAPA tasks */
   for (i = 0; i < 25; i++)
      for (j = 0; j < 5; j++)
         for (k = 0; k < 5; k++)
            TST_ATT_TTSK(procId1[0] + i, ENT_MP_0 + j, INST_MP_0 + k,
                           tskIdMp[0]); 

   /* detach TAPA tasks */
   for (i = 0; i < 25; i++)
      for (j = 0; j < 5; j++)
         for (k = 0; k < 5; k++)
            TST_DET_TTSK(procId1[0] + i, ENT_MP_0 + j, INST_MP_0 + k);
 
   /* deregister TAPA tasks */
   for (i = 0; i < 25; i++)
      for (j = 0; j < 5; j++)
         for (k = 0; k < 5; k++)
            TST_DEREG_TTSK(procId1[0] + i, ENT_MP_0 + j, INST_MP_0 + k);
 
   TST_REM_PROCID_LST(SS_MAX_PROCS, procId1);

   RETVALUE(ROK);
} /* end of tstMpTskFunc */


/*                                     
*
*       Fun:   tstMp
*
*       Desc:  To test new functionalities introduced for multiple processors in
*              single SSI instance
*
*       Ret:   ROK       - ok
*
*       Notes: None
*
*       File:  ss_acc.c
*
*/
 
#ifdef ANSI
PRIVATE S16 tstMp
(
Void
)
#else
PRIVATE S16 tstMp(Void)
#endif
{
   /*ss013.301 :Fix for TRACE5 feature crash due to missing TRC MACRO*/
   TRC2(tstMp)

   tstMpProcLst();
   tstMpTskFunc();

   RETVALUE(ROK);
} /* end of tstMp */


#endif /* SS_MULTIPLE_PROCS */
  
/********************************************************************30**
  
         End of file:     ss_acc.c@@/main/3 - Mon Nov 17 15:54:12 2008

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
1.1          ---      ag   1. initial release.

1.2          ---      ada  1. Removed 'exit'

1.2+         --       jn   1. Added tests for SAddPstMsgMult, 
                              SGetPstMsgMult & SRemPreMsgMult
1.2+         ss005.13 jn   2. Added tests for checking the 
                              difference between MTSS Ticks and 
                              real Unix time.
                           3. The array size allocation of src
                              was corrected.
1.2+         ss007.13 jn   4. Removed compile warnings
             ss011.13 jn   5. The SRegRtrTsk and SDeregRtrTsk tests
                              are enabled only if the SS_RTR_SUPPORT
                              is enabled.
             ss016.13 zo   6. Added the tests for the Zero Copy functions.
             ss017.13 ada/ 7. Changes to compile on Linux captured
                      jn      under flag SS_LINUX
             ss019.103 bp  8. Added tests for multithreaded task functions.
                              Added test for router task.
1.3+         ss021.103 bjp 1. Added test for SSwapMsg
                              Initialize route properly
1.3+         ss026.103 bjp 1. Modifications to fix warnings
                           2. Modifications to adjust timer test cases
1.3+         ss029.103 kkj 1. Multiple proc ids support added
1.3+         ss031.103 kkj 1. Compilation fixes 
1.3+         ss036.103 vk  1. Changes for SSI enhancements
/main/3      ---       rp  1. SSI enhancements for Multi-core 
                              architecture support
/main/3+     ss001.301 schandra1  1. Additions for SSI Phase 2
/main/3+     ss013.301 ssahniX    1. Fix for TRACE5 feature crash due
                                     to missing TRC MACRO
								  2. Fixed Warnings for 32/64 bit compilation 
*********************************************************************91*/
