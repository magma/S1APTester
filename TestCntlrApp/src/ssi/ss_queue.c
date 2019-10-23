

/********************************************************************20**
 
     Name:     System Services -- Queueing
 
     Type:     C source file
 
     Desc:     Source code for System Services queuing functions.
 
     File:     ss_queue.c
 
     Sid:      sm_queue.c@@/main/1 - Mon Nov 17 15:54:36 2008
 
     Prg:      bsr
  
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
#include "ss_strm.h"       /* STREAMS */
#include "ss_msg.h"        /* messaging */
#include "ss_mem.h"        /* memory management interface */
#include "ss_gen.h"        /* general */
/* ss040.103: addition */
#include <errno.h>

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


  
/*
*
*       Fun:   SInitQueue
*
*       Desc:  This function initializes a queue.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: no assumptions are made about the previous state
*              of the queue.
*
*              queue size is set to zero.
*
*       File:  ss_queue.c
*
*/
#ifdef ANSI
PUBLIC S16 SInitQueue
(
Queue *q               /* queue */
)
#else
PUBLIC S16 SInitQueue(q)
Queue *q;              /* queue */
#endif
{
   TRC1(SInitQueue)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check queue pointer */
   if (q == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS266, ERRZERO, "Null Ptr");
      RETVALUE(RFAILED);
   }
#endif
   q->head     = NULLP;
   q->tail     = NULLP;
   q->crntSize = 0;

   RETVALUE(ROK);

} /* end of SInitQueue */

  
/*
*
*       Fun:   SFlushQueue
*
*       Desc:  This function will release all of the data or message
*              buffers on the specified queue.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: if queue is empty: no action is taken.
*
*              if queue is not empty: all buffers in queue are returned
*              to memory. queue length is set to zero.
*
*              if dequeud buffer is a message buffer, all data buffers
*              associated with the message buffer are returned to memory
*
*       File:  ss_queue.c
*
*/
#ifdef ANSI
PUBLIC S16 SFlushQueue
(
Queue *q                    /* queue */
)
#else
PUBLIC S16 SFlushQueue(q)
Queue *q;                   /* queue */
#endif
{
   Buffer *tBuf;
   Buffer *mBuf;
   SsMsgInfo *minfo;
  
   TRC1(SFlushQueue)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check queue */
   if (q == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS267, ERRZERO, "Null Q Ptr");
      RETVALUE(RFAILED);
   }
#endif

   tBuf = q->head;
   while (tBuf != NULLP)
   {
      mBuf = tBuf->b_next;
      if (tBuf->b_datap->db_type == SS_M_PROTO)
         SPutMsg(tBuf);
      else
      {
         minfo = (SsMsgInfo *) tBuf->b_rptr;
         SPutDBuf(minfo->region, minfo->pool, tBuf);
      }
      tBuf = mBuf;
   }
   q->crntSize = 0;
   q->head     = NULLP;
   q->tail     = NULLP;

   RETVALUE(ROK);

} /* end of SFlushQueue */

  
/*
*
*       Fun:   SCatQueue
*
*       Desc:  This function will concatenate the two specified queues
*              into one queue.
*
*       Ret:   ROK     - ok
*              RFAILED - failed, general (optional)
*
*       Notes: if order equals Q1Q2: all buffers attached to queue 2 are
*              moved to the end of queue 1. queue 2 is set to empty.
*              queue 1 length is increased by length of queue 2. queue
*              2 length is set to zero. return is ok.
*
*              if order equals Q2Q1: all buffers attached to queue 2 are
*              moved to the front of queue 1. queue 2 is set to empty.
*              queue 1 length is increased by length of queue 2. queue
*              2 length is set to zero. return is ok.
*
*       File:  ss_queue.c
*
*/
#ifdef ANSI
PUBLIC S16 SCatQueue
(
Queue *q1,                  /* queue 1 */
Queue *q2,                  /* queue 2 */
Order order                 /* order */
)
#else
PUBLIC S16 SCatQueue(q1, q2, order)
Queue *q1;                  /* queue 1 */
Queue *q2;                  /* queue 2 */
Order order;                /* order */
#endif
{
   TRC1(SCatQueue)
 
#if (ERRCLASS & ERRCLS_INT_PAR)
   if (q1 == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS268, ERRZERO, "Null Q1 Ptr");
      RETVALUE(RFAILED);
   }
 
   if (q2 == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS269, ERRZERO, "Null Q2 Ptr");
      RETVALUE(RFAILED);
   }
   
   if ((order != Q1Q2) && (order != Q2Q1))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS270, ERRZERO, "Invalid queue order");
      RETVALUE(RFAILED);
   }

   /* ss021.103 - Addition if Q1 is Q2 */
   if (q2 == q1)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS271, ERRZERO, "Q1 == Q2");
      RETVALUE(RFAILED);
   }
   
#endif /* ERRCLASS */
   
   if (q1->crntSize == 0)
   {
      q1->head       = q2->head;
      q1->tail       = q2->tail;
      q1->crntSize   = q2->crntSize;

      q2->head       = NULLP;
      q2->tail       = NULLP;
      q2->crntSize   = 0;
      
      RETVALUE(ROK);
   }

   if (q2->crntSize == 0)
   {
      RETVALUE(ROK);
   }
   
   switch (order)
   {
      case Q1Q2:
      {
         q1->tail->b_next = q2->head;
         q2->head->b_prev = q1->tail;
         q1->tail         = q2->tail;

         break;
      }

      case Q2Q1:
      {
         q2->tail->b_next = q1->head;
         q1->head->b_prev = q2->tail;
         q1->head         = q2->head;

         break;
      }
      default:
         RETVALUE(RFAILED);
   }

   q1->crntSize  += q2->crntSize;

   q2->head       = NULLP;
   q2->tail       = NULLP;
   q2->crntSize   = 0;

   RETVALUE(ROK);

} /* end of SCatQueue */


  
/*
*
*       Fun:   SFndLenQueue
*
*       Desc:  This function determines the length of a queue.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed
*
*       Notes: length of queue is determined, queue is unchanged
*              and length is returned via pointer to length.
*              
*       File:  ss_queue.c
*
*/
#ifdef ANSI
PUBLIC S16 SFndLenQueue
(
Queue *q,                   /* queue */
QLen  *lngPtr               /* pointer to length */
)
#else
PUBLIC S16 SFndLenQueue(q, lngPtr)
Queue *q;                   /* queue */
QLen  *lngPtr;              /* pointer to length */
#endif
{
   TRC1(SFndLenQueue)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check queue */
   if (q == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS272, ERRZERO, "Null Q Ptr");
      RETVALUE(RFAILED);
   }
   /* check length */
   if (lngPtr == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS273, ERRZERO, "Null Q Len Ptr");
      RETVALUE(RFAILED);
   }
#endif

   *lngPtr = q->crntSize;

   RETVALUE(ROK);

} /* end of SFndLenQueue */


/*
*
*       Fun:   SExamQueue
*
*       Desc:  This function examines the queue at the desired index.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*              RFAILED  - failed 
*
*       Notes: index is 0 based and indicates location in queue.
*
*              if queue is empty: pointer to buffer is set to null and
*              return is ok, data not available. queue length is unchanged.
*
*              if queue is not empty: pointer to buffer is set to indexed
*              buffer in queue. return is ok. queue length is unchanged.
*
*       File:  ss_queue.c
*
*/
#ifdef ANSI
PUBLIC S16 SExamQueue
(
Buffer **bufPtr,            /* pointer to buffer */
Queue  *q,                  /* queue */
QLen   idx                  /* index */
)
#else
PUBLIC S16 SExamQueue(bufPtr, q, idx)
Buffer **bufPtr;            /* pointer to buffer */
Queue  *q;                  /* queue */
QLen   idx;                 /* index */
#endif
{
   Buffer *tmpBuf;
   QLen   i;

   TRC1(SExamQueue)
 
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check buffer pointer */
   if (bufPtr == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS274, ERRZERO, "Null Buf Ptr");
      RETVALUE(RFAILED);
   }
 
   /* check index */
   if ((S32)idx < 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS275, ERRZERO, "-ve index ");
      RETVALUE(RFAILED);
   }
 
   /* check queue */
   if (q == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS276, ERRZERO, "Null Q Ptr");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS */
 
   if (idx >= q->crntSize)
   {
      *bufPtr = NULLP;
      RETVALUE(ROKDNA);
   }

   if (idx == 0)
   {
      *bufPtr = q->head;
   }
   else  if (idx == q->crntSize -1)
   {
      *bufPtr = q->tail;
   }
   else 
   {
      tmpBuf = q->head;
      for (i = 0; i < idx; i++)
      {
         tmpBuf = tmpBuf->b_next;
      }
      *bufPtr = tmpBuf;
   }

   RETVALUE(ROK);

} /* end of SExamQueue */


/*
*
*       Fun:   SAddQueue
*
*       Desc:  This function inserts a bufer into the queue before 
*              the desired index.
*
*       Ret:   ROK     - ok
*              RFAILED - failed
*              ROKDNA  - failed - specified index not available
*
*       Notes: index is 0 based and indicates location in queue.
*
*              if queue is empty: buffer is placed in the queue.
*              queue length is incremented.
*
*              if queue is not empty: if index is less than the queue length, 
*              buffer is inserted before the desired index;
*              otherwise, buffer is placed behind all other buffers in queue.
*              queue length is incremented.
*
*       File:  ss_queue.c
*
*/
#ifdef ANSI
PUBLIC S16 SAddQueue
(
Buffer *mBuf,                /* buffer */
Queue  *q,                   /* queue */
QLen   idx                   /* index */
)
#else
PUBLIC S16 SAddQueue(mBuf, q, idx)
Buffer *mBuf;                /* buffer */
Queue  *q;                   /* queue */
QLen   idx;                  /* index */
#endif
{
   Buffer *tBuf;
   QLen   i;

   TRC1(SAddQueue)
 
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check queue */
   if (q == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS277, ERRZERO, "Null Q Ptr");
      RETVALUE(RFAILED);
   }
 
   if (mBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS278, ERRZERO, "Null Buf Ptr");
      RETVALUE(RFAILED);
   }
 
   if ((S32)idx < 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS279, ERRZERO, "-ve index");
      RETVALUE(RFAILED);
   }
   /* ss021.103 - Addition to check buffer type and if duplicate message */
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS280, ERRZERO, 
                 "Incorrect buffer type");
      RETVALUE(RFAILED);
   }
   tBuf = q->head;
   while (tBuf != (Buffer *)NULLP)
   {
      if (tBuf == mBuf)
      {
         SSLOGERROR(ERRCLS_INT_PAR, ESS281, ERRZERO, "Duplicate queued mBuf");
         RETVALUE(RFAILED);
      }
      tBuf = tBuf->b_next;
   }
#endif /* ERRCLASS */

   if (idx > q->crntSize)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS282, ERRZERO, "Invalid index");
      RETVALUE(ROKDNA);
   }
   else if (q->crntSize == 0)
   {
      q->head = mBuf;
      q->tail = mBuf;

      mBuf->b_next = NULLP;
      mBuf->b_prev = NULLP;
   }
   else if (idx == 0)
   {
      mBuf->b_next     = q->head;
      mBuf->b_prev     = NULLP;
      q->head->b_prev  = mBuf;
      q->head          = mBuf;
   }
   else if (idx == q->crntSize)
   {
      mBuf->b_prev    = q->tail;
      mBuf->b_next    = NULLP;
      q->tail->b_next = mBuf;
      q->tail         = mBuf;
   }
   else
   {
      tBuf = q->head;
      for (i = 0; i < idx; i++)
      {
         tBuf = tBuf->b_next;
      }
    
      tBuf->b_prev->b_next = mBuf;
      mBuf->b_prev         = tBuf->b_prev;
      mBuf->b_next         = tBuf;
      tBuf->b_prev         = mBuf;
   }
   q->crntSize++;
   RETVALUE(ROK);

} /* end of SAddQueue */


/*
*
*       Fun:   SRemQueue
*
*       Desc:  This function removes a buffer from the queue at 
*              the desired index.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*              RFAILED  - failed
*
*       Notes: index is 0 based and indicates location in queue.
*
*              if queue is empty: pointer to buffer is set to null and
*              return is ok, data not available. queue length is unchanged.
*
*              if queue is not empty: pointer to buffer is set to indexed
*              buffer in queue. return is ok. queue length is decremented.
*
*       File:  ss_queue.c
*
*/
#ifdef ANSI
PUBLIC S16 SRemQueue
(
Buffer **bufPtr,            /* pointer to buffer */
Queue  *q,                  /* queue */
QLen   idx                  /* index */
)
#else
PUBLIC S16 SRemQueue(bufPtr, q, idx)
Buffer **bufPtr;            /* pointer to buffer */
Queue  *q;                  /* queue */
QLen   idx;                 /* index */
#endif
{
   Buffer *tBuf;
   QLen   i;

   TRC1(SRemQueue)
 
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check buffer pointer */
   if (bufPtr == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS283, ERRZERO, "Null Buf Ptr");
      RETVALUE(RFAILED);
   }
 
   /* check queue */
   if (q == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS284, ERRZERO, "Null Q Ptr");
      RETVALUE(RFAILED);
   }
 
   if ((S32)idx < 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS285, ERRZERO, "-ve Index");
      RETVALUE(RFAILED);
   }      
#endif /* ERRCLASS */   
 
   if (idx >= q->crntSize)
   {
      *bufPtr = NULLP;
      RETVALUE(ROKDNA);
   }
   if (idx == 0)
   {
      *bufPtr = q->head;
      if (q->crntSize == 1)
      {
         q->head = NULLP;
         q->tail = NULLP;
      }
      else
      {
         q->head         = q->head->b_next;
         q->head->b_prev = NULLP;
      }
   }
   else if (idx == q->crntSize -1)
   {
      *bufPtr = q->tail;
      q->tail = q->tail->b_prev;
      q->tail->b_next = NULLP;
   }
   else 
   {
      tBuf = q->head;

      for (i = 0; i < idx; i++)
      {
         tBuf = tBuf->b_next;
      }
      *bufPtr = tBuf;
      
      tBuf->b_prev->b_next = tBuf->b_next;
      tBuf->b_next->b_prev = tBuf->b_prev;
   }
   q->crntSize--;

   RETVALUE(ROK);

} /* end of SRemQueue */


#ifndef SS_ENABLE_MACROS


/*
*
*       Fun:   SQueueFirst
*
*       Desc:  This function queues a data or message buffer to the
*              front of the specified queue.
*
*       Ret:   ROK     - ok
*              RFAILED - failed, general (optional)
*
*       Notes: if queue is empty: buffer is placed in the queue. queue
*              length is incremented.
*              
*              if queue is not empty: buffer is placed in front of all
*              other buffers in queue. queue length is incremented.
*
*       File:  ss_queue.c
*
*/
#ifdef ANSI
PUBLIC INLINE S16 SQueueFirst
(
Buffer *buf,                /* buffer */
Queue *q                    /* queue */
)
#else
PUBLIC INLINE S16 SQueueFirst(buf, q)
Buffer *buf;                /* buffer */
Queue *q;                   /* queue */
#endif
{
   TRC1(SQueueFirst)

   RETVALUE(SAddQueue(buf, q, 0));
} /* end of SQueueFirst */

  
/*
*
*       Fun:   SDequeueFirst
*
*       Desc:  This function dequeues a data or message buffer from
*              the front of the specified queue.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*              RFAILED  - failed, general (optional)
*
*       Notes: if queue is empty: pointer to buffer is set to null and
*              return is ok, data not available. queue length is unchanged.
*              
*              if queue is not empty: pointer to buffer is set to first
*              buffer in queue, first buffer in queue is removed and
*              return is ok. queue length is decremented.
*
*       File:  ss_queue.c
*
*/
#ifdef ANSI
PUBLIC INLINE S16 SDequeueFirst
(
Buffer **bufPtr,            /* pointer to buffer */
Queue *q                    /* queue */
)
#else
PUBLIC INLINE S16 SDequeueFirst(bufPtr, q)
Buffer **bufPtr;            /* pointer to buffer */
Queue *q;                   /* queue */
#endif
{
   TRC2(SDequeueFirst)

   RETVALUE(SRemQueue(bufPtr, q, 0));
} /* end of SDequeueFirst */

  
/*
*
*       Fun:   SQueueLast
*
*       Desc:  This function queues a data or message buffer to the
*              back of the specified queue.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: if queue is empty: buffer is placed in the queue.
*              queue length is incremented.
*              
*              if queue is not empty: buffer is placed behind all
*              other buffers in queue. queue length is incremented.
*
*       File:  ss_queue.c
*
*/
#ifdef ANSI
PUBLIC S16 SQueueLast
(
Buffer *buf,                /* buffer */
Queue *q                    /* queue */
)
#else
PUBLIC S16 SQueueLast(buf, q)
Buffer *buf;                /* buffer */
Queue *q;                   /* queue */
#endif
{
   TRC1(SQueueLast)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check queue */
   if (q == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS286, ERRZERO, "Null Q Ptr");
      RETVALUE(RFAILED);
   }
   /* check queue */
   if (buf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS287, ERRZERO, "Null Buf Ptr");
      RETVALUE(RFAILED);
   }
#endif
   RETVALUE(SAddQueue(buf, (q), ((q)->crntSize)));
}


  
/*
*
*       Fun:   SDequeueLast
*
*       Desc:  This function dequeues a data or message buffer from the
*              back of the specified queue.
*
*       Ret:   ROK     - ok
*              ROKDNA  - ok, data not available
*              RFAILED - failed, general (optional)
*
*       Notes: if queue is empty: pointer to buffer is set to null and
*              return is ok, data not available. queue length is unchanged.
*              
*              if queue is not empty: pointer to buffer is set to last
*              buffer in queue, last buffer in queue is removed and
*              return is ok. queue length is decremented.
*
*       File:  ss_queue.c
*
*/
#ifdef ANSI
PUBLIC S16 SDequeueLast
(
Buffer **bufPtr,            /* pointer to buffer */
Queue *q                    /* queue */
)
#else
PUBLIC S16 SDequeueLast(bufPtr, q)
Buffer **bufPtr;            /* pointer to buffer */
Queue *q;                   /* queue */
#endif
{
   S16   ret;

   TRC1(SDequeueLast)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check buffer pointer */
   if (!bufPtr)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS288, ERRZERO, "Null Buf Ptr");
      RETVALUE(RFAILED);
   }
   /* check queue */
   if (!q)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS289, ERRZERO, "Null Q Ptr");
      RETVALUE(RFAILED);
   }
#endif
   if(q->crntSize > 0)
      ret = SRemQueue(bufPtr, q, q->crntSize-1);
   else
      ret = SRemQueue(bufPtr, q, q->crntSize);

   RETVALUE(ret);
}

#endif /* SS_ENABLE_MACROS */


/*
*
*       Fun:   ssInitDmndQ
*
*       Desc:  This function initializes a Demand Queue
*
*       Ret:   ROK      - ok
*              RFAILED  - failed
*
*       Notes: 
*
*       File:  ss_queue.c
*
*/
#ifdef ANSI
PUBLIC S16 ssInitDmndQ
(
SsDmndQ *dQueue                 /* Demand Queue */
)
#else
PUBLIC S16 ssInitDmndQ(dQueue)
SsDmndQ *dQueue;                /* Demand Queue */
#endif
{
   U8  i;
   S16 ret;

   TRC0(ssInitDmnddQ)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (dQueue == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS290, ERRZERO, "NULL DQ Pointer");
      RETVALUE(RFAILED);
   }
#endif

   for (i = 0; i < SS_MAX_NUM_DQ; i++)
   {
      dQueue->queue[i].head     = NULLP;
      dQueue->queue[i].tail     = NULLP;
      dQueue->queue[i].crntSize = 0;
   }

   for (i = 0; i < SS_DQ_BIT_MASK_LEN; i++)
   {
      dQueue->bitMask[i] =  0;
      /* ss039.103 : Replaced SInitLock with WTInitLock */
#ifdef SS_WIN
      ret = WTInitLock(&dQueue->dmndQLock[i], SS_DMNDQ_LOCK);
#else
      ret = SInitLock(&dQueue->dmndQLock[i], SS_DMNDQ_LOCK);
#endif
      if (ret != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS291, (ErrVal)ret,
                                   "Failed to initialize lock");
#endif
         RETVALUE(RFAILED);
      }
   }

   /* initialize the semaphore */
   ret = ssInitSema(&dQueue->dmndQSema, 0);
   if (ret != ROK)
   {
      for (i = 0; i < SS_DQ_BIT_MASK_LEN; i++)
      {
         /* ss039.103 : Replaced SDestroyLock with WTDestroyLock */
#ifdef SS_WIN
         WTDestroyLock(&dQueue->dmndQLock[i]);
#else
         SDestroyLock(&dQueue->dmndQLock[i]);
#endif
      }
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS292, (ErrVal)ret, 
                                   "Failed to init semaphore");
#endif
      RETVALUE(RFAILED);
   }
   RETVALUE (ROK);

} /* End of ssInitDmndQ */


/*
*
*       Fun:   ssDestroyDmndQ
*
*       Desc:  This function destroys a Demand Queue by releasing all the
*              queued messages and detroying all the associated locks
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: 
*
*       File:  ss_queue.c
*
*/
#ifdef ANSI
PUBLIC S16 ssDestroyDmndQ
(
SsDmndQ *dQueue                        /* demand Queue */
)
#else
PUBLIC S16 ssDestroyDmndQ(dQueue)
SsDmndQ *dQueue;                       /* demand Queue */
#endif
{
   U8     i;
   Buffer *tBuf;
   S16    ret;

   TRC0(ssDestroyDmndQ)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (dQueue == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS293, ERRZERO, "NULL DQ Pointer");
      RETVALUE(RFAILED);
   }
#endif

   for (i = 0; i < SS_DQ_BIT_MASK_LEN; i++)
   {
      /* ss039.103 : Replaced SDestroyLock with WTDestroyLock */
#ifdef SS_WIN
      ret = WTDestroyLock(&dQueue->dmndQLock[i]);
#else
      ret = SDestroyLock(&dQueue->dmndQLock[i]);
#endif
      if (ret != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS294, (ErrVal)ret, "Failed to destroy lock");
#endif
         RETVALUE(RFAILED);
      }
   }
   for (i = 0; i < SS_MAX_NUM_DQ; i++)
   {
      while (dQueue->queue[i].head != NULLP)
      {
         tBuf = dQueue->queue[i].head;
         dQueue->queue[i].head = dQueue->queue[i].head->b_next;
         SPutMsg(tBuf);
      }
   }

/* ss06.13:addition */
   if( ssDestroySema(&dQueue->dmndQSema) != ROK)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS295, ERRZERO,
                         "Could not delete the Semaphore");
      RETVALUE(RFAILED);

   }
   RETVALUE (ROK);

} /* end of ssDestroyDmndQ */


/*
*
*       Fun:   ssDmndQPut
*
*       Desc:  This function adds a message to the head or tail of the 
*              priority queue specified. The priority specified is the 
*              destination Q index i.e 
*              ((dst_Tsk_pri * SS_MAX_MSG_PRI) + msg_pri)
*
*       Ret:   ROK      - ok
*              RFAILED  - failed
*
*       Notes: 
*
*       File:  ss_queue.c
*
*/
#ifdef ANSI
PUBLIC S16 ssDmndQPut
(
SsDmndQ *dQueue,                       /* demand Queue */
Buffer  *mBuf,                         /* message buffer */
Prior   priority,                      /* priority */
Order   order                          /* position */
)
#else
PUBLIC S16 ssDmndQPut(dQueue, mBuf, priority, order)
SsDmndQ *dQueue;                       /* demand Queue */
Buffer  *mBuf;                         /* message buffer */
Prior   priority;                      /* priority */
Order   order;                         /* position */
#endif
{
   U8     maskIndex;                   /* mask Index */
   U8     bitPosition;                 /* bit position in index */
   Queue *queue;                       /* queue in demand queue */
   S16    ret;                         /* return value */
#ifdef SS_PERF
   int    value;
   U32    size;
#endif

   TRC0(ssDmndQPut)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (dQueue == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS296, ERRZERO, "NULL DQ Pointer");
      RETVALUE(RFAILED);
   }

   if (mBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS297, ERRZERO, "NULL mBuf Pointer");
      RETVALUE(RFAILED);
   }

   if ((priority == PRIORNC) || (priority > SS_MAX_DQ_PRIOR))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS298, ERRZERO, "invalid priority ");
      RETVALUE(RFAILED);
   }

   if ((order != SS_DQ_FIRST) && (order != SS_DQ_LAST))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS299, ERRZERO, "invalid order ");
      RETVALUE(RFAILED);
   }
#endif
   
   maskIndex   = priority >> 3;
   bitPosition = 7 - (priority % 8);
   queue       = &dQueue->queue[priority];

   /* ss039.103 : Replaced SLock with WTLock */
#ifdef SS_WIN
   ret = WTLock(&dQueue->dmndQLock[maskIndex]);
#else
   ret = SLock(&dQueue->dmndQLock[maskIndex]);
#endif
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS300, (ErrVal)ret, "Failed to get lock");
#endif
      RETVALUE (RFAILED);
   }

   if (queue->crntSize == 0)
   {
      queue->head   = mBuf;
      queue->tail   = mBuf;
      mBuf->b_next  = NULLP;
      mBuf->b_prev  = NULLP;

      /* Set the corresponding bit in bit mask */
      dQueue->bitMask[maskIndex] |= (1 << bitPosition);
   }
   else
   {
      if (order == SS_DQ_LAST)
      {
         mBuf->b_prev        = queue->tail;
         mBuf->b_next        = NULLP;
         queue->tail->b_next = mBuf;
         queue->tail         = mBuf;
      }
      else
      {
         mBuf->b_next        = queue->head;
         mBuf->b_prev        = NULLP;
         queue->head->b_prev = mBuf;
         queue->head         = mBuf;
      }
   }
   queue->crntSize++;
#ifdef SS_PERF
   size = queue->crntSize;
#endif
    
   /* ss039.103 : Replaced SUnlock with WTUnlock */
#ifdef SS_WIN
   ret = WTUnlock(&dQueue->dmndQLock[maskIndex]);
#else
   ret = SUnlock(&dQueue->dmndQLock[maskIndex]);
#endif
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS301, (ErrVal)ret, "Failed to release lock");
#endif
      /* ss035.103 */
      if (order == SS_DQ_LAST)
      {
         SDequeueLast(&mBuf, queue);
      }
      else
      {
         SDequeueFirst(&mBuf, queue);
      }
      RETVALUE (RFAILED);
   }

   /* increment the counting semaphore */
   /* ss006.13: addition */

/* ss037.103 for Performance enhancement : this is to ensure that semaphore is posted every time the first message is posted to the queue so that permanent tick is picked */
#ifdef SS_PERF
  if (size > 1)
  {
     sem_getvalue(&dQueue->dmndQSema, &value);
     if (value > 0)
           RETVALUE(ROK);
  }
#endif
   if (ssPostSema(&dQueue->dmndQSema) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
       SSLOGERROR(ERRCLS_DEBUG, ESS302, ERRZERO,
                         "Could not unlock the Semaphore");
       /* ss035.103 */
       if (order == SS_DQ_LAST)
       {
          SDequeueLast(&mBuf, queue);
       }
       else
       {
          SDequeueFirst(&mBuf, queue);
       } 
       RETVALUE(RFAILED);
#endif
   }
   RETVALUE(ROK);

} /* End of ssDmndQPut */


/*
*
*       Fun:   ssDmndQGet
*
*       Desc:  This function removes a message from head or tail of the 
*              highest non-empty priority queue message. 
*
*       Ret:   ROK      - ok
*              RFAILED  - failed
*              ROKDNA   - ok, no data available in queue
*
*       Notes:  This is a blocking call
*
*       File:  ss_queue.c
*
*/
#ifdef ANSI
PUBLIC S16 ssDmndQGet
(
SsDmndQ *dQueue,                          /* demand queue */
Buffer  **mBuf,                           /* message buffer */
Order   order                             /* position */ 
)
#else
PUBLIC S16 ssDmndQGet(dQueue, mBuf, order)
SsDmndQ *dQueue;                          /* demand queue */
Buffer  **mBuf;                           /* message buffer */
Order   order;                            /* position */
#endif
{
   Queue *queue;
   S16   ret;
   S16   i;
   U8    bitPosition;
   U8    qIndex;

   TRC0(ssDmndQGet)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (dQueue == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS303, ERRZERO, "NULL DQ Pointer");
      RETVALUE(RFAILED);
   }

   if (mBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS304, ERRZERO, "NULL mBuf Pointer");
      RETVALUE(RFAILED);
   }

   if ((order != SS_DQ_FIRST) && (order != SS_DQ_LAST))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS305, ERRZERO, "invalid order ");
      RETVALUE(RFAILED);
   }
#endif

   /* ss040.103 updating for possible non-fatal retur from sem_wait */
   while ((ret = ssWaitSema(&dQueue->dmndQSema) != ROK) && (errno == EINTR))
      continue;
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS306, (ErrVal)ret, "Failed to get semaphore");
#endif
      RETVALUE (RFAILED);
   }

   for (i = 0; i < SS_DQ_BIT_MASK_LEN; i++)
   {
      /* ss039.103 : Replaced SLock with WTLock */
#ifdef SS_WIN
      ret = WTLock(&dQueue->dmndQLock[i]);
#else
      ret = SLock(&dQueue->dmndQLock[i]);
#endif
      if (ret != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS307, (ErrVal)ret, "Failed to get lock");
#endif
         RETVALUE (RFAILED);
      }

      bitPosition = osCp.dmndQLookupTbl[dQueue->bitMask[i]];
      if (bitPosition != 255)
         break;

      /* ss039.103 : Replaced SUnlock with WTUnlock */
#ifdef SS_WIN
      ret = WTUnlock(&dQueue->dmndQLock[i]);
#else
      ret = SUnlock(&dQueue->dmndQLock[i]);
#endif
      if (ret != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS308, ret, "Failed to release lock");
#endif
         RETVALUE (RFAILED);
      }
   }

   if (i >= SS_DQ_BIT_MASK_LEN)
   {
      /* Demand Queue is empty */
      *mBuf = NULLP;
      RETVALUE (ROKDNA);
   }
   
   qIndex = (i * 8) +  (7 - bitPosition);
   queue = &dQueue->queue[qIndex];

/* ss037.103 For performance enhancement replace the check sequence with simple 
setting the crntSize to 0 and removing the message */
#ifndef SS_PERF
   if (queue->crntSize == 1)
   {
      *mBuf = queue->head;
      queue->head = NULLP;
      queue->tail = NULLP;

      /* Reset the corresponding bit in bit mask */
      dQueue->bitMask[i] &= (~( 1 << (bitPosition)));
   }
   else
   {
      if (order == SS_DQ_FIRST)
      {
         *mBuf = queue->head;
         queue->head = queue->head->b_next;
         queue->head->b_prev = NULLP;
      }
      else
      {
         *mBuf = queue->tail;
         queue->tail = queue->tail->b_prev;
         queue->tail->b_next = NULLP;
      }
   }
   queue->crntSize--;
#else
   queue->crntSize = 0;
   *mBuf = queue->head;
   queue->head = NULLP;
   queue->tail = NULLP;
       
   dQueue->bitMask[i] &= (~( 1 << (bitPosition)));

#endif

   /* ss039.103 : Replaced SUnlock with WTUnlock */
#ifdef SS_WIN
   ret = WTUnlock(&dQueue->dmndQLock[i]); 
#else
   ret = SUnlock(&dQueue->dmndQLock[i]); 
#endif
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS309, (ErrVal)ret, "Failed to release lock");
#endif
      RETVALUE (RFAILED);
   }

   RETVALUE (ROK);

} /* End of ssDmndQGet */


/*
*
*       Fun:   ssFndLenDmndQ 
*
*       Desc:  This function returns the number of messages in a queue
*              If priority is specified, length of the associated Q is 
*              returned otherwise total length of all Qs is returned.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed
*
*       Notes: 
*
*       File:  ss_queue.c
*
*/
#ifdef ANSI
PUBLIC S16 ssFndLenDmndQ
(
SsDmndQ *dQueue,                               /* demand queue */
Prior   priority,                              /* priority */
QLen    *len                                   /* queue length */
)
#else
PUBLIC S16 ssFndLenDmndQ(dQueue, priority, len)
SsDmndQ *dQueue;                               /* demand queue */
Prior   priority;                              /* priority */
QLen    *len;                                  /* queue length */
#endif
{
   
   S16  ret;                                   /* return value */
   U8   i;

   TRC0(ssFndLenDmndQ)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if ((dQueue == NULLP) || (len == NULLP))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS310, ERRZERO, "NULL Pointer");
      RETVALUE(RFAILED);
   }
#endif

   *len = 0;
   if (priority != PRIORNC)
   {
      i = priority >> 3; 
      /* ss039.103 : Replaced SLock with WTLock */
#ifdef SS_WIN
      ret = WTLock(&dQueue->dmndQLock[i]);
#else
      ret = SLock(&dQueue->dmndQLock[i]);
#endif
      if (ret != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS311, (ErrVal)ret, "Failed to get lock");
#endif
         RETVALUE (RFAILED);
      }

      *len = dQueue->queue[priority].crntSize;

      /* ss039.103 : Replaced SUnlock with WTUnlock */
#ifdef SS_WIN
      ret = WTUnlock(&dQueue->dmndQLock[i]);
#else
      ret = SUnlock(&dQueue->dmndQLock[i]);
#endif
      if (ret != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS312, (ErrVal)ret,  \
                                         "Failed to release lock");
#endif
         RETVALUE (RFAILED);
      }
   }
   else
   {
      for (i = 0; i < SS_DQ_BIT_MASK_LEN; i++)
      {
         /* ss039.103 : Replaced SLock with WTLock */
#ifdef SS_WIN
         ret = WTLock(&dQueue->dmndQLock[i]);
#else
         ret = SLock(&dQueue->dmndQLock[i]);
#endif
         if (ret != ROK)
         {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS313, (ErrVal)ret, "Failed to get lock");
#endif
            /* Release all the locks aquired */
            while (i > 0)
            {

/* ss006.13: addition */
                /* ss039.103 : Replaced SUnlock with WTUnlock */
#ifdef SS_WIN
                if( WTUnlock(&dQueue->dmndQLock[i-1]) != ROK)
#else
                if( SUnlock(&dQueue->dmndQLock[i-1]) != ROK)
#endif
                {
#if (ERRCLASS & ERRCLS_DEBUG)
                   SSLOGERROR(ERRCLS_DEBUG, ESS314, ERRZERO,
                         "Could not give the Semaphore");
                   RETVALUE(RFAILED);
#endif
                }

               i--;
            }

            RETVALUE (RFAILED);
         }
      }

      for (i = 0; i  < SS_MAX_NUM_DQ; i++)
         *len  += dQueue->queue[i].crntSize;

      for ( i = 0; i < SS_DQ_BIT_MASK_LEN; i++)
      {
         /* ss039.103 : Replaced SUnlock with WTUnlock */ 
#ifdef SS_WIN
         ret = WTUnlock(&dQueue->dmndQLock[i]);
#else
         ret = SUnlock(&dQueue->dmndQLock[i]);
#endif
         if (ret != ROK)
         {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS315, (ErrVal)ret, "Failed to get lock");
#endif
            RETVALUE (RFAILED);
         }
      }
   }
   RETVALUE(ROK);

} /* End of ssFndLenDmndQ */



/********************************************************************30**
  
         End of file:     sm_queue.c@@/main/1 - Mon Nov 17 15:54:36 2008
  
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
1.1          ---      bsr  1. initial release.
  
1.2          ---      kr   1. defined functions SQueueFirst, 
                              SDequeueFirst, SQueueLast and SDequeueLast
                              under SS_ENABLE_MACROS
             ---      kp   2. Cosmetic changes

1.3          ---      kp   1. Bug fix in ssDmndQGet()
1.3+        ss006.13  jn   2. Compile Warning - "Value computed is not
                              used" removed for ssPostSema and SUnlock.
1.3+       ss021.103 bjp   3. test if q1 == q2 for SCatQueue
                              add test for correct buffer type and
                  if duplicate buffer in SAddQueue
1.3+       ss029.103  kkj  1. Errcodes modifies
1.3+       ss035.103  pdb  1. Add code in ssDmndQPut to remove the mBuf from
                              the demandQueue in case of error.
1.3+       ss037.103  gs   1. SSI enhancements guarded under SS_PERF
1.3+       ss039.103  rks  1. Replaced mutex related calls with WTLock(),
                              WTUnlock(), WTInitLock() and WTDestroyLock()
           ss040.103  bn   1. changed  how ssWaitSema is called.
/main/1      ---       rp   1. SSI enhancements for Multi-core architecture
                              support
*********************************************************************91*/
