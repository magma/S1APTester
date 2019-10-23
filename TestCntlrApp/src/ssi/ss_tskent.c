


/********************************************************************20**
 
     Name:     Common Task Manager 
 
     Type:     C source file
 
     Desc:     C source code for the Commom Task Manager module. 
 
     File:     cm_tskent.c
 
     Sid:      ss_tskent.c@@/main/3 - Fri May 15 12:07:35 2009
 
     Prg:      rp
 
*********************************************************************21*/


/************************************************************************

This file contains the mapping having entity Id, actvInit and actvTsk
 
************************************************************************/



#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "ss_task.h"        /* system services task management */
#include "ss_gen.h"         /* system initialization parameters */
#include "ss_err.h"

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

#include "cm_task.h"

#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "ss_dep.x"        /* implementation-specific */
#include "ss_queue.x"      /* queues */
#include "ss_task.x"       /* tasking */
#include "ss_timer.x"      /* timers */
#include "ss_strm.x"       /* STREAMS */
#include "ss_msg.x"        /* messaging */
#include "ss_mem.x"        /* memory management interface */
#include "ss_drvr.x"       /* driver tasks */
#include "ss_gen.x"        /* general */
#include "cm_task.x"


#ifndef INST0
#define INST0 0
#endif
#define ENTTSTX 20
#define EVNT 9
#define PERMENT2     26
#define TSTTIMES     10
#define MAXSMEMLEN   0x20 
#define NMBTMRTSKS   2

#ifdef WIN32
#define sleep(x) Sleep(x*1000)
#define usleep(x) Sleep(x)
#endif /*WIN32 */

/*ss013.301: Fixed Warnings for 32/64 bit compilation*/
PRIVATE Region   region;
PRIVATE Pool     pool;
PRIVATE MsgLen mLen = 1;
PRIVATE Pool   sPool0;

/*ss013.301: Fixed Warnings for 32/64 bit compilation*/
PUBLIC S16 startTest ARGS((S16 source));
PUBLIC S16 FbtstEntActvInit ARGS ((Ent    ent,Inst   inst,Region reg,Reason reason));
PUBLIC S16 FbtstEnt1ActvInit ARGS ((Ent    ent,Inst   inst,Region reg,Reason reason));
PUBLIC S16 FbtstEnt2ActvInit ARGS ((Ent ent,Inst inst, Region reg,Reason reason));
PUBLIC S16 FbtstEntActvTsk ARGS ((Pst *pst,Buffer *mBuf));
PUBLIC S16 FbtstEnt1ActvTsk ARGS ((Pst *pst,Buffer *mBuf));
PUBLIC S16 FbtstEnt2ActvTsk ARGS ((Pst *pst,Buffer *mBuf));
PUBLIC S16 FbtstEnt3ActvTsk ARGS ((Pst *pst,Buffer *mBuf));
PUBLIC S16 FbPerm2ActvInit ARGS ((Ent ent,Inst inst, Region reg,Reason reason));
PUBLIC S16 FbpermTsk1 ARGS ((Pst *pst,Buffer *mBuf));
PUBLIC S16 FbpermTsk2 ARGS ((Pst *pst,Buffer *mBuf));
PUBLIC S16 FbpermTsk3 ARGS ((Pst *pst,Buffer *mBuf));
PUBLIC S16 FbpermTsk4 ARGS ((Pst *pst,Buffer *mBuf));
PUBLIC S16 FbpermTsk5 ARGS ((Pst *pst,Buffer *mBuf));
PUBLIC S16 FbpermTsk6 ARGS ((Pst *pst,Buffer *mBuf));
PUBLIC S16 FbpermTsk7 ARGS ((Pst *pst,Buffer *mBuf));
EXTERN Void SLogLkInfo          ARGS((Void));


PUBLIC S16 startTest(S16 source)
{
   S16 retCode;
   Pst     pst;
   Buffer *mBuf;
   Txt buf[255]={'\0'};
   /*ss013.301: Fixed Warnings for 32/64 bit compilation*/
   Ent ent;
#ifdef SS_HISTOGRAM_SUPPORT
   Ent a, b;
#endif
   Inst inst;
#ifdef BIT_64
#ifdef SS_THREAD_PROFILE  
#ifdef SS_MULTIPLE_PROCS
   ProcId procId;
#endif
#endif /* SS_THREAD_PROFILE */
#endif /* BIT_64 */

  if (SGetMsg(0, 0, &mBuf) != ROK)
   {
      RETVALUE(RFAILED);
   }


   /* pst->selector  = SS_LOOSE_COUPLING;  */
   pst.prior     = 10;
   pst.route     = 1;
   pst.event     = EVNT;
   pst.region    = 0;
   pst.pool      = 0;
   pst.selector  = 1;
   if( source == 0 ){
   pst.dstEnt    = ent  = ENTTSTX+1;
   pst.dstInst   = inst = INST0;
   pst.srcEnt    = ENTTSTX ;
   pst.srcInst   = INST0;
#ifndef SS_MULTIPLE_PROCS
   pst.dstProcId = SFndProcId();
   pst.srcProcId = SFndProcId();
#else
   pst.dstProcId = 1;
   pst.srcProcId = 0;
#endif

   }
   else if(source == 1){
   pst.dstEnt    = ent  = ENTTSTX+2;
   pst.dstInst   = inst = INST0;
   pst.srcEnt    = ENTTSTX+1;
   pst.srcInst   = INST0;
#ifndef SS_MULTIPLE_PROCS
   pst.dstProcId = SFndProcId();
   pst.srcProcId = SFndProcId();
#else
   pst.dstProcId = 2;
   pst.srcProcId = 1;
#endif
   }
   else if(source == 2){
   pst.dstEnt    = ent  = PERMENT2;
   pst.dstInst   = inst = 0;
   pst.srcEnt    = ENTTSTX+2;
   pst.srcInst   = INST0;
#ifndef SS_MULTIPLE_PROCS
   pst.dstProcId = SFndProcId();
   pst.srcProcId = SFndProcId();
#else
   pst.dstProcId = 3;
   pst.srcProcId = 2;
#endif
   }
   else if(source == 3){
   pst.dstEnt    = ent  = PERMENT2;
   pst.dstInst   = inst = 1;
   pst.srcEnt    = PERMENT2;
   pst.srcInst   = 0;
#ifndef SS_MULTIPLE_PROCS
   pst.dstProcId = SFndProcId();
   pst.srcProcId = SFndProcId();
#else
   pst.dstProcId = 4;
   pst.srcProcId = 3;
#endif
   }
   else if(source == 4){
   pst.dstEnt    = ent  = PERMENT2;
   pst.dstInst   = inst = 2;
   pst.srcEnt    = PERMENT2;
   pst.srcInst   = 1;
#ifndef SS_MULTIPLE_PROCS
   pst.dstProcId = SFndProcId();
   pst.srcProcId = SFndProcId();
#else
   pst.dstProcId = 5;
   pst.srcProcId = 4;
#endif
   }
   else if(source == 5){
   pst.dstEnt    = ent  = PERMENT2;
   pst.dstInst   = inst = 3;
   pst.srcEnt    = PERMENT2;
   pst.srcInst   = 2;
#ifndef SS_MULTIPLE_PROCS
   pst.dstProcId = SFndProcId();
   pst.srcProcId = SFndProcId();
#else
   pst.dstProcId = 6;
   pst.srcProcId = 5;
#endif
   }
   else if(source == 6){
   pst.dstEnt    = ent  = PERMENT2;
   pst.dstInst   = inst = 4;
   pst.srcEnt    = PERMENT2;
   pst.srcInst   = 3;
#ifndef SS_MULTIPLE_PROCS
   pst.dstProcId = SFndProcId();
   pst.srcProcId = SFndProcId();
#else
   pst.dstProcId = 7;
   pst.srcProcId = 6;
#endif
   }
   else if(source == 7){
   pst.dstEnt    = ent  = PERMENT2;
   pst.dstInst   = inst = 5;
   pst.srcEnt    = PERMENT2;
   pst.srcInst   = 4;
#ifndef SS_MULTIPLE_PROCS
   pst.dstProcId = SFndProcId();
   pst.srcProcId = SFndProcId();
#else
   pst.dstProcId = 8;
   pst.srcProcId = 7;
#endif
   }
   else if(source == 8){
   pst.dstEnt    = ent  = PERMENT2;
   pst.dstInst   = inst = 6;
   pst.srcEnt    = PERMENT2;
   pst.srcInst   = 5;
#ifndef SS_MULTIPLE_PROCS
   pst.dstProcId = SFndProcId();
   pst.srcProcId = SFndProcId();
#else
   pst.dstProcId = 9;
   pst.srcProcId = 8;
#endif
   }
   else {
   pst.dstEnt    = ent  = ENTTSTX;
   pst.dstInst   = inst = INST0;
   pst.srcEnt    = PERMENT2;
   pst.srcInst   = 6;
#ifndef SS_MULTIPLE_PROCS
   pst.dstProcId = SFndProcId();
   pst.srcProcId = SFndProcId();
#else
   pst.dstProcId = 0;
   pst.srcProcId = 9;
#endif
   }

   retCode = SPstTsk(&pst,mBuf);
   if ( retCode != ROK ){
        sprintf(buf,"Post Failed for SrcEnt:%d SrcInst:%d and DstEnt:%d DstInst:%d\n",pst.srcEnt,pst.srcInst,pst.dstEnt,pst.dstInst);
        SPrint(buf);
   }
#ifdef SS_MEM_LEAK_STS
    SLogLkInfo();
#endif
#ifdef SS_HISTOGRAM_SUPPORT
 a = ENTTSTX;
 b = PERMENT2;
 SRegForHstGrm(ENTTSTX);
 SRegForHstGrm(PERMENT2);
 SHstGrmInfoShow(&a);
 SHstGrmInfoShow(&b);
#endif

   RETVALUE(ROK);
}

/*ss013.301: Fixed Warnings for 32/64 bit compilation*/
#ifdef ANSI
PUBLIC S16 FbtstEntActvInit
(
Ent    ent,                   /* entity */
Inst   inst,                  /* instance */
Region reg,                /* region */
Reason reason                 /* reason */
)
#else
PUBLIC S16 FbtstEntActvInit(ent, inst, reg, reason)
Ent    ent;                   /* entity */
Inst   inst;                  /* instance */
Region reg;                /* region */
Reason reason;                /* reason */
#endif
{
   TRC3(FbtstEntActvInit)

   UNUSED(ent);
   UNUSED(inst);
   UNUSED(reg);
   UNUSED(reason);

   RETVALUE(ROK);

}

/*ss013.301: Fixed Warnings for 32/64 bit compilation*/
#ifdef ANSI
PUBLIC S16 FbtstEnt1ActvInit
(
Ent    ent,                   /* entity */
Inst   inst,                  /* instance */
Region reg,                /* region */
Reason reason                 /* reason */
)
#else
PUBLIC S16 FbtstEnt1ActvInit(ent, inst, reg, reason)
Ent    ent;                   /* entity */
Inst   inst;                  /* instance */
Region reg;                /* region */
Reason reason;                /* reason */
#endif
{
   TRC3(FbtstEnt1ActvInit)

   UNUSED(ent);
   UNUSED(inst);
   UNUSED(reg);
   UNUSED(reason);

   RETVALUE(ROK);

}

/*ss013.301: Fixed Warnings for 32/64 bit compilation*/
#ifdef ANSI
PUBLIC S16 FbtstEnt2ActvInit
(
Ent    ent,                   /* entity */
Inst   inst,                  /* instance */
Region reg,                /* region */
Reason reason                 /* reason */
)
#else
PUBLIC S16 FbtstEnt2ActvInit(ent, inst, reg, reason)
Ent    ent;                   /* entity */
Inst   inst;                  /* instance */
Region reg;                /* region */
Reason reason;                /* reason */
#endif
{
   TRC3(FbtstEnt2ActvInit)

   UNUSED(ent);
   UNUSED(inst);
   UNUSED(reg);
   UNUSED(reason);

   RETVALUE(ROK);

}

/*ss013.301: Fixed Warnings for 32/64 bit compilation*/
#ifdef ANSI
PUBLIC S16 FbPerm2ActvInit
(
Ent    ent,                   /* entity */
Inst   inst,                  /* instance */
Region reg,                /* region */
Reason reason                 /* reason */
)
#else
PUBLIC S16 FbPerm2ActvInit(ent, inst, reg, reason)
Ent    ent;                   /* entity */
Inst   inst;                  /* instance */
Region reg;                /* region */
Reason reason;                /* reason */
#endif
{
   Buffer *mBuf;
   TRC3(FbPerm2ActvInit)

   UNUSED(ent);
   UNUSED(inst);
   UNUSED(reg);
   UNUSED(reason);

   if (SGetMsg(0, 0, &mBuf) != ROK)
   {
      RETVALUE(RFAILED);
   }


   /* pst->selector  = SS_LOOSE_COUPLING;  */
  /*
   pst.dstProcId = SFndProcId();
   pst.srcProcId = SFndProcId();
   pst.prior     = 10;
   pst.route     = 1;
   pst.event     = EVNT;
   pst.region    = 0;
   pst.pool      = 0;
   pst.selector  = 1;
   pst.dstEnt    = ent  = ENTTSTX+1;
   pst.dstInst   = inst = INST0;
   pst.srcEnt    = ENTTSTX ;
   pst.srcInst   = INST0;
    if( SPstTsk(&pst,mBuf) != ROK )
   {
        sprintf(buf,"Post Failed for SrcEnt:%d SrcInst:%d and DstEnt:%d DstInst:%d\n",pst.srcEnt,pst.srcInst,pst.dstEnt,pst.dstInst);
        SPrint(buf);
   }
   */


   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 FbtstEntActvTsk
(
Pst    *pst,                /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 FbtstEntActvTsk(pst, mBuf)
Pst    *pst;                /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   Txt buf[255]={'\0'};
   switch(pst->event)
   {
      case EVNT:
           sprintf(buf,"\n FbtstEntActvTsk:Received an event:%d from the Entity %d \n",pst->event,pst->srcEnt);
            SPrint(buf);
           if(mBuf)
              SPutMsg(mBuf);
           sleep(1);
           startTest(0);
           break;

      default: break;
   }

   SExitTsk();

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 FbtstEnt1ActvTsk
(
Pst    *pst,                /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 FbtstEnt1ActvTsk(pst, mBuf)
Pst    *pst;                /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   Txt buf[255]={'\0'};

   switch(pst->event)
   {
      case EVNT:
           sprintf(buf,"\n FbtstEnt1ActvTsk:Received an event:%d from the Entity %d \n",pst->event,pst->srcEnt);
            SPrint(buf);
           if(mBuf)
              SPutMsg(mBuf);
           sleep(1);
            startTest(1);
           break;

      default: break;
   }

   SExitTsk();

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 FbtstEnt2ActvTsk
(
Pst    *pst,                /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 FbtstEnt2ActvTsk(pst, mBuf)
Pst    *pst;                /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   Txt buf[255]={'\0'};
   switch(pst->event)
   {
      case EVNT:
           sprintf(buf,"\n FbtstEnt2ActvTsk:Received an event:%d from the Entity %d \n",pst->event,pst->srcEnt);
           SPrint(buf);
/*
           if(mBuf)
              SPutMsg(mBuf);
*/
           sleep(1);
           startTest(2);
           break;

      default: break;
   }

   SExitTsk();

   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 FbpermTsk1
(
Pst *pst,                       /* pst structure */
Buffer *mBuf                    /* buffer */
)
#else
PUBLIC S16 FbpermTsk1(pst, mBuf)
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
   Txt buf[255]={'\0'};

   TRC2(FbpermTsk1)
   sprintf(buf,"\n FbpermTsk1:Received an event:%d from the Entity %d Inst:%d\n",pst->event,pst->srcEnt,pst->srcInst);
  SPrint(buf);

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
           sleep(2);
   startTest(3);
   RETVALUE(ROK);

} /* end of FbpermTsk1 */

#ifdef ANSI
PUBLIC S16 FbpermTsk2
(
Pst *pst,                       /* pst structure */
Buffer *mBuf                    /* message buffer */
)
#else
PUBLIC S16 FbpermTsk2(pst, mBuf)
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
   Txt buf[255]={'\0'};

   TRC2(FbpermTsk2)

   sprintf(buf,"\n FbpermTsk2:Received an event:%d from the Entity %d Inst:%d\n",pst->event,pst->srcEnt,pst->srcInst);
  SPrint(buf);
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

           sleep(2);
   startTest(4);
   RETVALUE(ROK);

} /* end of FbpermTsk2 */

#ifdef ANSI
PUBLIC S16 FbpermTsk3
(
Pst *pst,                       /* pst structure */
Buffer *mBuf                    /* message buffer */
)
#else
PUBLIC S16 FbpermTsk3(pst, mBuf)
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
   Txt buf[255]={'\0'};

   TRC2(FbpermTsk3)

   sprintf(buf,"\n FbpermTsk3:Received an event:%d from the Entity %d Inst:%d\n",pst->event,pst->srcEnt,pst->srcInst);
  SPrint(buf);
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

           sleep(2);
   startTest(5);

   RETVALUE(ROK);

} /* end of FbpermTsk3 */

#ifdef ANSI
PUBLIC S16 FbpermTsk4
(
Pst *pst,                       /* pst structure */
Buffer *mBuf                    /* message buffer */
)
#else
PUBLIC S16 FbpermTsk4(pst, mBuf)
Pst *pst;                       /* pst structure */
Buffer *mBuf;                   /* message buffer */
#endif
{
   REG1 S32 i;
   REG2 S32 j;
   Data *sBuf[TSTTIMES];
   Data *s;
   Txt buf[255]={'\0'};

   TRC2(FbpermTsk4)

   sprintf(buf,"\n FbpermTsk4:Received an event:%d from the Entity %d Inst:%d\n",pst->event,pst->srcEnt,pst->srcInst);
  SPrint(buf);
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

           sleep(2);
   startTest(6);
   RETVALUE(ROK);

} /* end of FbpermTsk4 */

#ifdef ANSI
PUBLIC S16 FbpermTsk5
(
Pst *pst,                       /* pst structure */
Buffer *mBuf                    /* message buffer */
)
#else
PUBLIC S16 FbpermTsk5(pst, mBuf)
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
   Txt buf[255]={'\0'};

/*ss013.301: Fixed Warnings for 32/64 bit compilation*/
   TRC2(FbpermTsk5)

   sprintf(buf,"\n FbpermTsk5:Received an event:%d from the Entity %d Inst:%d\n",pst->event,pst->srcEnt,pst->srcInst);
  SPrint(buf);
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

           sleep(2);
   startTest(7);
   RETVALUE(ROK);
} /* end of FbpermTsk6 */

#ifdef ANSI
PUBLIC S16 FbpermTsk6
(
Pst *pst,                       /* pst structure */
Buffer *mBuf                    /* message buffer */
)
#else
PUBLIC S16 FbpermTsk6(pst, mBuf)
Pst *pst;                       /* pst structure */
Buffer *mBuf;                   /* message buffer */
#endif
{
   REG1 S32 i;
   Buffer *m[TSTTIMES];
   Queue q;
   Buffer *bufPtr;
   QLen idx;
   Txt buf[255]={'\0'};

/*ss013.301: Fixed Warnings for 32/64 bit compilation*/
   TRC2(FbpermTsk6)

   sprintf(buf,"\n FbpermTsk6:Received an event:%d from the Entity %d Inst:%d\n",pst->event,pst->srcEnt,pst->srcInst);
  SPrint(buf);
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

           sleep(2);
   startTest(8);
   RETVALUE(ROK);

} /* end of FbpermTsk7 */

/*
*
*       Fun:   FbpermTsk8
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
PUBLIC S16 FbpermTsk7
(
Pst *pst,                       /* pst structure */
Buffer *mBuf                    /* message buffer */
)
#else
PUBLIC S16 FbpermTsk7(pst, mBuf)
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
   Txt buf[255]={'\0'};

/*ss013.301: Fixed Warnings for 32/64 bit compilation*/
   TRC2(FbpermTsk7)

   sprintf(buf,"\n FbpermTsk7:Received an event:%d from the Entity %d Inst:%d\n",pst->event,pst->srcEnt,pst->srcInst);
  SPrint(buf);
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

           sleep(2);
   startTest(9);
   RETVALUE(ROK);

} /* end of FbpermTsk8 */



CmTskStrEntry   cmTskFnEntry[CM_TSK_MAX_ENT_MAP_SIZE] =
{
/*ss013.301: Fixed Warnings for 32/64 bit compilation*/
{"ENTTST", ENTTSTX,FbtstEntActvInit,FbtstEntActvTsk},
{"ENTTST1", ENTTSTX+1, FbtstEnt1ActvInit,FbtstEnt1ActvTsk},
{"ENTTST2", ENTTSTX+2, FbtstEnt2ActvInit,FbtstEnt2ActvTsk},
{"PERMENT1", PERMENT2, FbPerm2ActvInit, FbpermTsk1},
{"PERMENT2", PERMENT2, FbPerm2ActvInit, FbpermTsk2},
{"PERMENT3", PERMENT2, FbPerm2ActvInit, FbpermTsk3},
{"PERMENT4", PERMENT2, FbPerm2ActvInit, FbpermTsk4},
{"PERMENT5", PERMENT2, FbPerm2ActvInit, FbpermTsk5},
{"PERMENT6", PERMENT2, FbPerm2ActvInit, FbpermTsk6},
{"PERMENT7", PERMENT2, FbPerm2ActvInit, FbpermTsk7}
};


/********************************************************************30**
 
         End of file:     ss_tskent.c@@/main/3 - Fri May 15 12:07:35 2009
 
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
------------ -------- ---- -----------------------------------------------
1.1          ---      rp   1. initial release

/main/1+     ss013.301 ssahniX    1. Fixed Warnings for 32/64 bit compilation 
*********************************************************************91*/
