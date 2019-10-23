

/********************************************************************20**
  
     Name:     system services - portable service provider
  
     Type:     C source file
  
     Desc:     Prototype C source code for the System Service
               service provider primitives that must be supplied
               by the customer.
  
     File:     ss_ptsp.c
  
     Sid:      ss_ptsp.c@@/main/64 - Thu Nov 24 21:13:43 2011
   
     Prg:      na
  
*********************************************************************21*/
  

/*
  
System services are the functions required by the protocol
layer for buffer management, timer management, date/time
management, resource checking and initialization.

The following functions are provided in this file for the
system services service user:

     SPkS8          Pack signed 8 bit
     SPkU8          Pack unsigned 8 bit
     SPkS16         Pack signed 16 bit
     SPkU16         Pack unsigned 16 bit
     SPkS32         Pack signed 32 bit
     SPkU32         Pack unsigned 32 bit
     SUnpkS8        Unpack signed 8 bit
     SUnpkU8        Unpack unsigned 8 bit  
     SUnpkS16       Unpack signed 16 bit
     SUnpkU16       Unpack unsigned 16 bit
     SUnpkS32       Unpack signed 32 bit
     SUnpkU32       Unpack unsigned 32 bit
     SPrint         Print
     SDisplay       Display
     SPrntMsg       Print Message
   
     SInitQueue     Initialize Queue
     SQueueFirst    Queue to First Place
     SQueueLast     Queue to Last Place
     SDequeueFirst  Dequeue from First Place
     SDequeueLast   Dequeue from Last Place
     SFlushQueue    Flush Queue
     SCatQueue      Concatenate Queue
     SFndLenQueue   Find Length of Queue
     SExamQueue     Examine Queue
     SAddQueue      Add Queue
     SRemQueue      Remove Queue
     
     SGetDBuf       Get Dynamic Buffer
     SPutDBuf       Put Dynamic Buffer
     SGetSBuf       Get Static Buffer
     SPutSBuf       Put Static Buffer
     SGetSMem       Get Static Memory
     SPutSMem       Put Static Memory
  
     SGetMsg        Get Message
     SPutMsg        Put Message
     SInitMsg       Initialize Message
  
     SAddPreMsg     Add Pre Message
     SAddPstMsg     Add Post Message
     SRemPreMsg     Remove Pre Message
     SRemPstMsg     Remove Post Message
     SAddPreMsgMult Add Pre Message Multiple
     SAddPstMsgMult Add Post Message Multiple
     SRemPreMsgMult Remove Pre Message Multiple
     SRemPstMsgMult Remove Post Message Multiple
     SRepMsg        Replace Message
     SExamMsg       Examine Message
     SFndLenMsg     Find Length of Message
     SCatMsg        Concatenate Message
     SSegMsg        Segment Message
  
     SCpyMsgFix     Copy from Message to Fixed Buffer
     SCpyFixMsg     Copy from Fixed Buffer to Message
     SCompressMsg   Compress Message
     SCpyMsgMsg     Copy from Message to Message
     SAddMsgRef     Copy from Message to Message
  
     SChkRes        Check Resources
     SSwapMsg       Swap contents of two messages
     SGetDateTime   Get Date and Time
     SGetSysTime    Get System Time
     SGetRefTime    Get referenced time
     SRandom        Get Random Number
     SError         Error
     SLogError      Log  error.
  
     SRegInit       Register Activate Task - initialize
     SRegCfgTmr     Register Activate Task - configurable timer
     SDeregCfgTmr   Deregister Activate Task - configurable timer
     SRegTsk        Register Activate Task - task buffer - non preemptive (old)
     SRegPTsk       Register Activate Task - task buffer - non preemptive or preemptive (old)
     SRegActvTsk    Register Activate Task - task buffer - non preemptive or preemptive (new)
     SRegDrvr       Register Driver
     SDeregDrvr     Deregister Driver
     SDeregInitTskTmr  Deregister initialize, task buffer and timer
     SPostTsk       Post task (old)
     SPstTsk        Post task (new)
     SExitTsk       Exit task

     SFndProcId     Find Processor Id
     SExitInt       Exit Interrupt
     SHoldInt       Hold Interrupt
     SRelInt        Release Interrupt
     SEnbInt        Enable Interrupt
     SDisInt        Disable Interrupt
     SGetVect       Get Vector
     SPutVect       Put Vector
     SGetEntInst    Get Entity and Instance
     SSetEntInst    Get Entity and Instance
     SInitSema      Initialize Semaphore
     SRelSema       Release Semaphore
     SGetSema       Get Semaphore
     SAddDBufPst    Add Data Buffer to End of Message
     SAddDBufPre    Add Data Buffer to Front of Message
     SRemDBufPst    Remove Data Buffer from End of Message
     SRemDBufPre    Remove Data Buffer from Front of Message
     SGetDataRx     Get Data Pointer and Length (receive)
     SGetDataTx     Get Data Pointer and Length (transmit)
     SUpdMsg        Update Message with New Data Buffer
     SAlignDBufEven Align Data Buffer on Even Boundary
     SInitNxtDBuf   Initialize a Message's Next Data Buffer Pointer
     SGetNxtDBuf    Get the Next Data Buffer in a Message
     SChkNxtDBuf    Check the Next Data Buffer in a Message


     SAlignDBuf    Align data portion of a data buffer on the specified
                   boundary.
     SGetBufRegionPool Returns the region and pool of the message buffer
     SSetAehDpr   This function creates the DPR (Deferred processing) task.
                  This task is meant for deferred processing of the Interrupts
                  DPR communicates with ISR using semaphore mechanism.  
     SRemoveAehDpr This function removes a previously set DPR interrupt handler
     SInitLock    Initialize Mutex
     SLock        Lock the mutex
     SUnlock      Unlock the mutex
     SDestroyLock Destroy the lock
     SInitSemaphore Initialize Semaphore
     SWaitSemaphore Acquire or wait for semaphore
     SPostSemaphore Increment the count of a semaphore
     SDestroySemaphore Destroy the semaphore
     SRegRtrTsk   This function is used to register a router task
     SDeregRtrTsk This Function is used to deregister a router task
     SRegTTsk     This function is used to register a TAPA task
     SDeregTTsk   This function is used to deregister a TAPA task
     SCreateSTsk  This function is used to create a system task
     SDestroySTsk This function is used to destroy a system task
     SAttachTTsk  This function is used to attach a TAPA task to a
                  system task
     SDetachTTsk  This function is used to detach a TAPA task from a
                  system task.
     SThreadYield The function is used to deschedule a system task

It should be noted that not all of these functions may be required
by a particular system services service user.

It is assumed that the following functions are provided in the
system services service user file:
  
     SActvInit      Activate layer - initialize
     SActvTmr       Activate layer - timer
     SActvTsk       Activate layer - task (old)
     SActvTask      Activate layer - task (new)

*/
  


/*
*     The functions provided in this file correspond to the functions
*     provided in the following TRILLIUM software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*     1000011     Multiprocessor Operating System
*     1000035     68302 MOS/SCC
*
*/
  
/*
*     This software may be combined with the following TRILLIUM
*     software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*     1000001     Physical Layer - SCC
*     1000002     Data Link Layer - LAPB
*     1000003     Data Link Layer - LAPD
*     1000004     Data Link Layer - Multilink
*     1000005     Data Link Layer - LAPB & LAPD
*     1000006     Network Layer - X.25 Intermediate System
*     1000007     Network Layer - X.25 End System
*     1000008     Network Layer - X.75
*     1000009     Network Layer - Q.930/Q.931
*     1000010     Application Layer - Asynchronous PAD
*     1000014     Network Layer - X.25 End & Intermediate System
*     1000017     Data Link Layer - Basic Frame Relay
*     1000018     Data Link Layer - Extended Frame Relay
*     1000023     Network Layer - X.31
*     1000024     Signalling System 7 (SS7)
*     1000026     TCP/IP
*     1000027     Signalling System 7 - MTP Level 2
*     1000028     Signalling System 7 - MTP Level 3
*     1000029     Signalling System 7 - ISUP
*     1000030     Signalling System 7 - SCCP
*     1000031     Signalling System 7 - TCAP
*     1000034     Physical Layer - ISAC-S
*     1000040     UDP/IP
*     1000041     ESCC
*     1000042     Signalling System 7 - TUP
*     1000043     Network Layer - Q.93B
*     1000044     Data Link Layer - Q.SAAL
*
*/
 

/* header include files (.h) */
  
#include "envopt.h"        /* environment options */  
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
  
/* header/extern include files (.x) */
  
#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */


/* local defines */
  
/* local typedefs */
  
/* local externs */
  
/* forward references */
  
/* functions in other modules */
  
/* public variable declarations */

/* private variable declarations */
  

/*
*     interface functions to system services service user
*/
 

/*
*
*       Fun:   Pack signed 8 bit
*
*       Desc:  This function packs a signed 8 bit value into a message.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
   
#ifdef ANSI
PUBLIC S16 SPkS8
(
S8 val,                     /* value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SPkS8(val, mBuf)
S8 val;                     /* value */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(SPkS8)
   SAddPreMsg((Data) val, mBuf);
   RETVALUE(ROK);
} /* end of SPkS8 */

/*  ss_ptsp_c_001.main_63: Added functions for packing and unpacking
 *  of Float32 and Float64. */
#ifdef SS_FLOAT

/*
*
*       Fun:   Unpack float 32 bit
*
*       Desc:  This function packs a signed 8 bit value into a message.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
   
#ifdef ANSI
PUBLIC S16 SUnpkF32
(
F32 *val,                     /* value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SUnpkF32(val, mBuf)
F32 *val;                     /* value */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(SUnpkF32)
   RETVALUE(ROK);
} /* end of SUnpkF32 */

/*
*
*       Fun:   Unpack float 64 bit
*
*       Desc:  This function packs a signed 8 bit value into a message.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
   
#ifdef ANSI
PUBLIC S16 SUnpkF64
(
F64 *val,                     /* value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SUnpkF64(val, mBuf)
F64 *val;                     /* value */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(SUnpkF64)
   RETVALUE(ROK);
} /* end of SUnpkF64 */

/*
*
*       Fun:   Pack float 32 bit
*
*       Desc:  This function packs a signed 8 bit value into a message.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
   
#ifdef ANSI
PUBLIC S16 SPkF32
(
F32 val,                     /* value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SPkF32(val, mBuf)
F32 val;                     /* value */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(SPkF32)
   RETVALUE(ROK);
} /* end of SPkF32 */

/*
*
*       Fun:   Pack float 64 bit
*
*       Desc:  This function packs a signed 8 bit value into a message.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
   
#ifdef ANSI
PUBLIC S16 SPkF64
(
F64 val,                     /* value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SPkF64(val, mBuf)
F64 val;                     /* value */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(SPkF64)
   RETVALUE(ROK);
} /* end of SPkF64 */
#endif /* SS_FLOAT */


/*
*
*       Fun:   Pack unsigned 8 bit
*
*       Desc:  This function packs an unsigned 8 bit value into a message.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SPkU8
(
U8 val,                     /* value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SPkU8(val, mBuf)
U8 val;                     /* value */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(SPkU8)
   SAddPreMsg((Data) val, mBuf);
   RETVALUE(ROK);
} /* end of SPkU8 */


/*
*
*       Fun:   Pack signed 16 bit
*
*       Desc:  This function packs a signed 16 bit value into a message.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SPkS16
(
S16 val,                    /* value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SPkS16(val, mBuf)
S16 val;                    /* value */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(SPkS16)
   RETVALUE(ROK);
} /* end of SPkS16 */
  

/*
*
*       Fun:   Pack unsigned 16 bit
*
*       Desc:  This function packs an unsigned 16 bit value into a message.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/

#ifdef ANSI
PUBLIC S16 SPkU16
(
U16 val,                    /* value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SPkU16(val, mBuf)
U16 val;                    /* value */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(SPkU16)
   RETVALUE(ROK);
} /* end of SPkU16 */
  

/*
*
*       Fun:   Pack signed 32 bit
*
*       Desc:  This function packs a signed 32 bit value into a message.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SPkS32
(
S32 val,                    /* value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SPkS32(val, mBuf)
S32 val;                    /* value */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(SPkS32)
   RETVALUE(ROK);
} /* end of SPkS32 */
  

/*
*
*       Fun:   Pack unsigned 32 bit
*
*       Desc:  This function packs an unsigned 32 bit value into a message.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
   
#ifdef ANSI
PUBLIC S16 SPkU32
(
U32 val,                    /* value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SPkU32(val, mBuf)
U32 val;                    /* value */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(SPkU32)
   RETVALUE(ROK);
} /* end of SPkU32 */
  

/*
*
*       Fun:   Unpack signed 8 bit
*
*       Desc:  This function unpacks a signed 8 bit value from a message.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
   
#ifdef ANSI
PUBLIC S16 SUnpkS8
(
S8 *val,                    /* pointer to value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SUnpkS8(val, mBuf)
S8 *val;                    /* pointer to value */
Buffer *mBuf;               /* message buffer */
#endif
{
   Data tmp;                /* temporary value */

   TRC2(SUnpkS8)
   SRemPreMsg(&tmp, mBuf);
   *val = (S8) tmp;
   RETVALUE(ROK);
} /* end of SUnpkS8 */
  

/*
*
*       Fun:   Unpack unsigned 8 bit
*
*       Desc:  This function unpacks an unsigned 8 bit value from a message.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
   
#ifdef ANSI
PUBLIC S16 SUnpkU8
(
U8 *val,                    /* pointer to value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SUnpkU8(val, mBuf)
U8 *val;                    /* pointer to value */
Buffer *mBuf;               /* message buffer */
#endif
{
   Data tmp;                /* temporary value */

   TRC2(SUnpkS8)
   SRemPreMsg(&tmp, mBuf);
   *val = tmp;
   RETVALUE(ROK);
} /* end of SUnpkU8 */
  

/*
*
*       Fun:   Unpack signed 16 bit
*
*       Desc:  This function unpacks a signed 16 bit value from a message.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
   
#ifdef ANSI
PUBLIC S16 SUnpkS16
(
S16 *val,                   /* pointer to value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SUnpkS16(val, mBuf)
S16 *val;                   /* pointer to value */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(SUnpkS16)
   RETVALUE(ROK);
} /* end of SUnpkS16 */
  

/*
*
*       Fun:   Unpack unsigned 16 bit
*
*       Desc:  This function unpacks an unsigned 16 bit value from a message.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
   
#ifdef ANSI
PUBLIC S16 SUnpkU16
(
U16 *val,                   /* pointer to value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SUnpkU16(val, mBuf)
U16 *val;                   /* pointer to value */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(SUnpkU16)
   RETVALUE(ROK);
} /* end of SUnpkU16 */
  

/*
*
*       Fun:   Unpack signed 32 bit
*
*       Desc:  This function unpacks a signed 32 bit value from a message.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
   
#ifdef ANSI
PUBLIC S16 SUnpkS32
(
S32 *val,                   /* pointer to value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SUnpkS32(val, mBuf)
S32 *val;                   /* pointer to value */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(SUnpkS32)
   RETVALUE(ROK);
} /* end of SUnpkS32 */
  

/*
*
*       Fun:   Unpack unsigned 32 bit
*
*       Desc:  This function unpacks an unsigned 32 bit value from a message.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
   
#ifdef ANSI
PUBLIC S16 SUnpkU32
(
U32 *val,                   /* pointer to value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SUnpkU32(val, mBuf)
U32 *val;                   /* pointer to value */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(SUnpkU32)
   RETVALUE(ROK);
} /* end of SUnpkU32 */


/*
*
*       Fun:   Print
*
*       Desc:  This function prints a string.
*
*              This function should be used for debugging only.
*
*       Ret:   ROK      - ok
*
*       Notes: Buffer should be null terminated.
*
*              SDisplay will replace SPrint.
*
*              Typical usage consists of a call to sprintf to
*              format the string into a buffer followed by a
*              call to SPrint
*
*       File:  ss_ptsp.c
*
*/
   
#ifdef ANSI
PUBLIC S16 SPrint
(
Txt *buf                    /* buffer */
)
#else
PUBLIC S16 SPrint(buf)
Txt *buf;                   /* buffer */
#endif
{
   SDisplay(0, buf);
   RETVALUE(ROK);
} /* end of SPrint */


/*
*
*       Fun:   Display
*
*       Desc:  This function displays a string to a given output
*              channel.
*
*              This function should be used for debugging only.
*
*       Ret:   ROK      - ok
*
*       Notes: Buffer should be null terminated.
*
*              SDisplay will replace SPrint.
*
*              Channel 0 is reserved for backwards compatibility
*              with SPrint
*
*              Typical usage consists of a call to sprintf to
*              format the string into a buffer followed by a
*              call to SDisplay
*
*       File:  ss_ptsp.c
*
*/
   
#ifdef ANSI
PUBLIC S16 SDisplay
(
S16 chan,                   /* channel */
Txt *buf                    /* buffer */
)
#else
PUBLIC S16 SDisplay(chan, buf)
S16 chan;                   /* channel */
Txt *buf;                   /* buffer */
#endif
{
   RETVALUE(ROK);
} /* end of SDisplay */


/*
*
*       Fun:   Print Message
*
*       Desc:  This function prints the contents of a message. The
*              following information is printed: queue length,
*              message length, direction, hexadecimal and ASCII
*              (if appropriate) values of all bytes in the message.
*
*              This function should be used for debugging only.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
   
#ifdef ANSI
PUBLIC S16 SPrntMsg
(
Buffer *mBuf,               /* message buffer */
S16 src,                    /* source id */
S16 dst                     /* destination id */
)
#else
PUBLIC S16 SPrntMsg(mBuf, src, dst)
Buffer *mBuf;               /* message buffer */
S16 src;                    /* source id */
S16 dst;                    /* destination id */
#endif
{
   RETVALUE(ROK);
} /* end of SPrntMsg */
     

/*
*
*       Fun:   Initialize Queue
*
*       Desc:  This function initializes a queue.
*
*       Ret:   ROK      - ok
*
*       Notes: no assumptions are made about the previous state
*              of the queue.
*
*              queue size is set to zero.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SInitQueue
(
REG1 Queue *q               /* queue */
)
#else
PUBLIC S16 SInitQueue(q)
REG1 Queue *q;              /* queue */
#endif
{
   TRC2(SInitQueue)
   RETVALUE(ROK);
} /* end of SInitQueue */


/*
*
*       Fun:   Queue at the First Place
*
*       Desc:  This function queues a data or message buffer to the
*              front of the specified queue.
*
*       Ret:   ROK      - ok
*
*       Notes: if queue is empty: buffer is placed in the queue. queue
*              length is incremented.
*
*              if queue is not empty: buffer is placed in front of all
*              other buffers in queue. queue length is incremented.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC INLINE S16 SQueueFirst
(
REG2 Buffer *buf,           /* buffer */
REG1 Queue *q               /* queue */
)
#else
PUBLIC INLINE S16 SQueueFirst(buf, q)
REG2 Buffer *buf;           /* buffer */
REG1 Queue *q;              /* queue */
#endif
{
   TRC2(SQueueFirst)
   RETVALUE(ROK);
} /* end of SQueueFirst */


/*
*
*       Fun:   Queue at the Last Place
*
*       Desc:  This function queues a data or message buffer to the
*              back of the specified queue.
*
*       Ret:   ROK      - ok
*
*       Notes: if queue is empty: buffer is placed in the queue.
*              queue length is incremented.
*
*              if queue is not empty: buffer is placed behind all
*              other buffers in queue. queue length is incremented.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC INLINE S16 SQueueLast
(
REG2 Buffer *buf,           /* buffer */
REG1 Queue *q               /* queue */
)
#else
PUBLIC INLINE S16 SQueueLast(buf, q)
REG2 Buffer *buf;           /* buffer */
REG1 Queue *q;              /* queue */
#endif
{
   TRC2(SQueueLast)
   RETVALUE(ROK);
} /* end of SQueueLast */


/*
*
*       Fun:   Dequeue from the First Place
*
*       Desc:  This function dequeues a data or message buffer from
*              the front of the specified queue.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*
*       Notes: if queue is empty: pointer to buffer is set to null and
*              return is ok, data not available. queue length is unchanged.
*
*              if queue is not empty: pointer to buffer is set to first
*              buffer in queue, first buffer in queue is removed and
*              return is ok. queue length is decremented.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC INLINE S16 SDequeueFirst
(
Buffer **bufPtr,            /* pointer to buffer */
REG1 Queue *q               /* queue */
)
#else
PUBLIC INLINE S16 SDequeueFirst(bufPtr, q)
Buffer **bufPtr;            /* pointer to buffer */
REG1 Queue *q;              /* queue */
#endif
{
   TRC2(SDequeueFirst)
   RETVALUE(ROK);
} /* end of SDequeueFirst */


/*
*
*       Fun:   Dequeue from the Last Place
*
*       Desc:  This function dequeues a data or message buffer from the
*              back of the specified queue.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*
*       Notes: if queue is empty: pointer to buffer is set to null and
*              return is ok, data not available. queue length is unchanged.
*
*              if queue is not empty: pointer to buffer is set to last
*              buffer in queue, last buffer in queue is removed and
*              return is ok. queue length is decremented.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC INLINE S16 SDequeueLast
(
Buffer **bufPtr,            /* pointer to buffer */
REG1 Queue *q               /* queue */
)
#else
PUBLIC INLINE S16 SDequeueLast(bufPtr, q)
Buffer **bufPtr;            /* pointer to buffer */
REG1 Queue *q;              /* queue */
#endif
{
   TRC2(SDequeueLast)
   RETVALUE(ROK);
} /* end of SDequeueLast */


/*
*
*       Fun:   Flush a Queue
*
*       Desc:  This function will release all of the data or message
*              buffers on the specified queue.
*
*       Ret:   ROK      - ok
*
*       Notes: if queue is empty: no action is taken.
*
*              if queue is not empty: all buffers in queue are returned
*              to memory. queue length is set to zero.
*
*              if the dequeued buffer is a message buffer no action will
*              be taken with any data buffers attached to the message
*              buffer.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SFlushQueue
(
REG1 Queue *q               /* queue */
)
#else
PUBLIC S16 SFlushQueue(q)
REG1 Queue *q;              /* queue */
#endif
{
   TRC2(SFlushQueue)
   RETVALUE(ROK);
} /* end of SFlushQueue */


/*
*
*       Fun:   Concatenate Two Queues
*
*       Desc:  This function will concatenate the two specified queues
*              into one queue.
*
*       Ret:   ROK      - ok
*
*       Notes: if order equal Q1Q2: all buffers attached to queue 2 are
*              moved to the end of queue 1. queue 2 is set to empty.
*              queue 1 length is increased by length of queue 2. queue
*              2 length is set to zero. return is ok.
*
*              if order equal Q2Q1: all buffers attached to queue 2 are
*              moved to the front of queue 1. queue 2 is set to empty.
*              queue 1 length is increased by length of queue 2. queue
*              2 length is set to zero. return is ok.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SCatQueue
(
REG1 Queue *q1,             /* queue 1 */
REG2 Queue *q2,             /* queue 2 */
REG3 Order order            /* order */
)
#else
PUBLIC S16 SCatQueue(q1, q2, order)
REG1 Queue *q1;             /* queue 1 */
REG2 Queue *q2;             /* queue 2 */
REG3 Order order;           /* order */
#endif
{
   TRC2(SCatQueue)
   RETVALUE(ROK);
} /* end of SCatQueue */


/*
*
*       Fun:   Find Length of Queue
*
*       Desc:  This function determines the length of a queue.
*
*       Ret:   ROK      - ok
*
*       Notes: length of queue is determined, queue is unchanged
*              and length is returned via pointer to length. return is ok.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SFndLenQueue
(
REG1 Queue *q,              /* queue */
QLen *lngPtr                /* pointer to length */
)
#else
PUBLIC S16 SFndLenQueue(q, lngPtr)
REG1 Queue *q;              /* queue */
QLen *lngPtr;               /* pointer to length */
#endif
{
   TRC2(SFndLenQueue)
   RETVALUE(ROK);
} /* end of SFndLenQueue */


/*
*
*       Fun:   Examine Queue
*
*       Desc:  This function examines the queue at the desired index.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*
*       Notes: index is 0 based and indicates location in queue.
*
*              if queue is empty: pointer to buffer is set to null and
*              return is ok, data not available. queue length is unchanged.
*
*              if queue is not empty: pointer to buffer is set to indexed
*              buffer in queue. return is ok. queue length is unchanged.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SExamQueue
(
Buffer **bufPtr,            /* pointer to buffer */
REG1 Queue *q,              /* queue */
QLen idx                    /* index */
)
#else
PUBLIC S16 SExamQueue(bufPtr, q, idx)
Buffer **bufPtr;            /* pointer to buffer */
REG1 Queue *q;              /* queue */
QLen idx;                   /* index */
#endif
{
   TRC2(SExamQueue)
   RETVALUE(ROK);
} /* end of SExamQueue */


/*
*
*       Fun:   Add to Queue
*
*       Desc:  This function inserts into the queue before the desired index.
*
*       Ret:   ROK      - ok
*
*       Notes: index is 0 based and indicates location in queue.
*
*              if queue is empty: buffer is placed in the queue.
*              queue length is incremented.
*
*              if queue is not empty: if index is less than or equal to
*              the queue length, buffer is inserted before the desired index;
*              otherwise, buffer is placed behind all other buffers in queue.
*              queue length is incremented.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SAddQueue
(
Buffer *buf,                /* buffer */
REG1 Queue *q,              /* queue */
QLen idx                    /* index */
)
#else
PUBLIC S16 SAddQueue(buf, q, idx)
Buffer *buf;                /* buffer */
REG1 Queue *q;              /* queue */
QLen idx;                   /* index */
#endif
{
   TRC2(SAddQueue)
   RETVALUE(ROK);
} /* end of SAddQueue */


/*
*
*       Fun:   Remove from Queue
*
*       Desc:  This function removes from the queue at the desired index.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*
*       Notes: index is 0 based and indicates location in queue.
*
*              if queue is empty: pointer to buffer is set to null and
*              return is ok, data not available. queue length is unchanged.
*
*              if queue is not empty: pointer to buffer is set to indexed
*              buffer in queue. return is ok. queue length is decremented.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SRemQueue
(
Buffer **bufPtr,            /* pointer to buffer */
REG1 Queue *q,              /* queue */
QLen idx                    /* index */
)
#else
PUBLIC S16 SRemQueue(bufPtr, q, idx)
Buffer **bufPtr;            /* pointer to buffer */
REG1 Queue *q;              /* queue */
QLen idx;                   /* index */
#endif
{
   TRC2(SRemQueue)
   RETVALUE(ROK);
} /* end of SRemQueue */


/*
*
*       Fun:   Get dynamic buffer
*
*       Desc:  This function allocates a buffer from the dynamic
*              memory pool indicated by the caller.
*
*       Ret:   ROK      - ok
*
*       Notes: The dynamic memory pools are used to create and
*              manipulate messages.
*
*              SGetDBuf is never called by a protocol layer.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC INLINE S16 SGetDBuf
(
REG1 Region region,         /* region id */
REG2 Pool pool,             /* pool id */
Buffer **bufPtr             /* pointer to buffer */
)
#else
PUBLIC INLINE S16 SGetDBuf(region, pool, bufPtr)
REG1 Region region;         /* region id */
REG2 Pool pool;             /* pool id */
Buffer **bufPtr;            /* pointer to buffer */
#endif
{
   TRC2(SGetDBuf)
   RETVALUE(ROK);
} /* end of SGetDBuf */


/*
*
*       Fun:   Put dynamic buffer
*
*       Desc:  This function deallocates a buffer back to the
*              dynamic memory pool indicated by the caller.
*
*       Ret:   ROK      - ok
*
*       Notes: The dynamic memory pools are used to create and
*              manipulate messages.
*
*              SPutDBuf is never called by a protocol layer.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC INLINE S16 SPutDBuf
(
REG2 Region region,         /* region id */
REG3 Pool pool,             /* pool id */
REG1 Buffer *buf            /* buffer */
)
#else
PUBLIC INLINE S16 SPutDBuf(region, pool, buf)
REG2 Region region;         /* region id */
REG3 Pool pool;             /* pool id */
REG1 Buffer *buf;           /* buffer */
#endif
{
   TRC2(SPutDBuf)
   RETVALUE(ROK);
} /* end of SPutDBuf */


/*
*
*       Fun:   Get static buffer
*
*       Desc:  This function allocates a buffer from the static
*              memory pool indicated by the caller.
*
*       Ret:   ROK      - ok
*
*       Notes: The static memory pools provide variable sized
*              buffers. The buffers from the static pools are
*              typically used for control points.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SGetSBuf
(
REG1 Region region,         /* region id */
REG2 Pool pool,             /* pool id */
Data **bufPtr,              /* pointer to buffer */
REG3 Size size              /* size */
)
#else
PUBLIC S16 SGetSBuf(region, pool, bufPtr, size)
REG1 Region region;         /* region id */
REG2 Pool pool;             /* pool id */
Data **bufPtr;              /* pointer to buffer */
REG3 Size size;             /* size */
#endif
{
   TRC2(SGetSBuf)
   RETVALUE(ROK);
} /* end of SGetSBuf */


/*
*
*       Fun:   Put static buffer
*
*       Desc:  This function deallocates a buffer back to the
*              static memory pool indicated by the caller.
*
*       Ret:   ROK      - ok
*
*       Notes: The static memory pools provide variable sized
*              buffers. The buffers from the static pools are
*              typically used for control points.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SPutSBuf
(
REG2 Region region,         /* region id */
REG3 Pool pool,             /* pool id */
REG1 Data *buf,             /* buffer */
REG4 Size size              /* size */
)
#else
PUBLIC S16 SPutSBuf(region, pool, buf, size)
REG2 Region region;         /* region id */
REG3 Pool pool;             /* pool id */
REG1 Data *buf;             /* buffer */
REG4 Size size;             /* size */
#endif
{
   TRC2(SPutSBuf)
   RETVALUE(ROK);
} /* end of SPutSBuf */


/*
*
*       Fun:   Get Static Memory
*
*       Desc:  This function allocates a static buffer pool within the
*              specified memory region.
*
*       Ret:   ROK      - ok
*
*       Notes: The static memory pools provide variable sized
*              buffers. The buffers from the static pools are
*              typically used for control points.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SGetSMem
(
REG1 Region region,         /* region id */
REG3 Size size,             /* size */
REG2 Pool *pool             /* pointer to pool id */
)
#else
PUBLIC S16 SGetSMem(region, size, pool)
REG1 Region region;         /* region id */
REG3 Size size;             /* size */
REG2 Pool *pool;            /* pointer to pool id */
#endif
{
   TRC2(SGetSMem)
   RETVALUE(ROK);
} /* end of SGetSMem */


/*
*
*       Fun:   Put Static Memory
*
*       Desc:  This function deallocates a static buffer pool within the
*              specified memory region.
*
*       Ret:   ROK      - ok
*
*       Notes: The static memory pools provide variable sized
*              buffers. The buffers from the static pools are
*              typically used for control points.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SPutSMem
(
REG1 Region region,         /* region id */
REG2 Pool pool              /* pool id */
)
#else
PUBLIC S16 SPutSMem(region, pool)
REG1 Region region;         /* region id */
REG2 Pool pool;             /* pool id */
#endif
{
   TRC2(SPutSMem)
   RETVALUE(ROK);
} /* end of SPutSMem */


/*
*
*       Fun:   Get Message
*
*       Desc:  This function gets a message
*
*       Ret:   ROK      - ok
*
*       Notes: message is created. message is set to empty.
*              message is returned via message buffer pointer.
*              return is ok.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SGetMsg
(
REG1 Region region,         /* region id */
REG2 Pool pool,             /* pool id */
Buffer **mBufPtr            /* pointer to message buffer */
)
#else
PUBLIC S16 SGetMsg(region, pool, mBufPtr)
REG1 Region region;         /* region id */
REG2 Pool pool;             /* pool id */
Buffer **mBufPtr;           /* pointer to message buffer */
#endif
{
   TRC2(SGetMsg)
   RETVALUE(ROK);
} /* end of SGetMsg */


/*
*
*       Fun:   Put Message
*
*       Desc:  This function deallocates a message back.
*
*       Ret:   ROK      - ok
*
*       Notes: all data attached to message is returned to memory.
*              message is returned to memory. return is ok.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SPutMsg
(
REG1 Buffer *mBuf           /* message buffer */
)
#else
PUBLIC S16 SPutMsg(mBuf)
REG1 Buffer *mBuf;          /* message buffer */
#endif
{
   TRC2(SPutMsg)
   RETVALUE(ROK);
} /* end of SPutMsg */


/*
*
*       Fun:   Initialize Message
*
*       Desc:  This function deallocates a message back and then
*              reinitializes the message.
*
*       Ret:   ROK      - ok
*
*       Notes: all data attached to message is returned to memory.
*              message is set to empty. message is not returned to
*              memory. return is ok.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SInitMsg
(
REG1 Buffer *mBuf           /* message buffer */
)
#else
PUBLIC S16 SInitMsg(mBuf)
REG1 Buffer *mBuf;          /* message buffer */
#endif
{
   TRC2(SInitMsg)
   RETVALUE(ROK);
} /* end of SInitMsg */


/*
*
*       Fun:   Add pre message
*
*       Desc:  This function copies one byte of data to the
*              beginning of a message.
*
*       Ret:   ROK      - ok
*
*       Notes: if message is empty: data is placed in the message. message
*              length is incremented. return is ok.
*
*              if message is not empty: data is placed in front of all
*              other data in message. message length is incremented.
*              return is ok.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SAddPreMsg
(
Data data,                  /* data */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SAddPreMsg(data, mBuf)
Data data;                  /* data */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(SAddPreMsg)
   RETVALUE(ROK);
} /* end of SAddPreMsg */


/*
*
*       Fun:   Add post message
*
*       Desc:  This function copies one byte of data to the
*              end of a message.
*
*       Ret:   ROK      - ok
*
*       Notes: if message is empty: data is placed in the message. message
*              length is incremented. return is ok.
*
*              if message is not empty: data is placed in back of all
*              other data in message. message length is incremented.
*              return is ok.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SAddPstMsg 
(
Data data,                  /* data */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SAddPstMsg (data, mBuf)
Data data;                  /* data */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(SAddPstMsg )
   RETVALUE(ROK);
} /* end of SAddPstMsg */


/*
*
*       Fun:   Remove pre message
*
*       Desc:  This function copies and then removes one byte of
*              data from the beginning of a message.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*
*       Notes: if message is empty: message is unchanged. return is ok,
*              data not available.
*
*              if message is not empty: data is removed from front of
*              message, data is returned via pointer to data. message
*              length is decremented. return is ok.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SRemPreMsg
(
Data *dataPtr,              /* pointer to data */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SRemPreMsg(dataPtr, mBuf)
Data *dataPtr;              /* pointer to data */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(SRemPreMsg)
   RETVALUE(ROK);
} /* end of SRemPreMsg */


/*
*
*       Fun:   Remove post message
*
*       Desc:  This function copies and then removes one byte of
*              data from the end of a message.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*
*       Notes: if message is empty: message is unchanged. return is ok,
*              data not available.
*
*              if message is not empty: data is removed from back of
*              message, data is returned via pointer to data. message
*              length is decremented. return is ok.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SRemPstMsg
(
Data *dataPtr,              /* pointer to data */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SRemPstMsg(dataPtr, mBuf)
Data *dataPtr;              /* pointer to data */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(SRemPstMsg)
   RETVALUE(ROK);
} /* end of SRemPstMsg */


/*
*
*       Fun:   Add pre message multiple
*
*       Desc:  This function copies consecutive bytes of data to the
*              beginning of a message.
*
*       Ret:   ROK      - ok
*
*       Notes: if message is empty: data is placed in the message. message
*              length is incremented. return is ok.
*
*              if message is not empty: data is read by source pointer, 
*              data is placed in front of all other data in message.
*              message length is incremented. return is ok.
*
*              the first byte of data pointed to by the source pointer will
*              be placed at the front of the message first, the last byte of
*              data pointed to by the source pointer will be placed at the
*              front of the message last (i.e. it will become the first
*              byte of the message).
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SAddPreMsgMult
(
Data *src,                  /* source */
MsgLen cnt,                 /* count */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SAddPreMsgMult(src, cnt, mBuf)
Data *src;                  /* source */
MsgLen cnt;                 /* count */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(SAddPreMsgMult)
   RETVALUE(ROK);
} /* end of SAddPreMsgMult */


/*
*
*       Fun:   Add post message multiple
*
*       Desc:  This function copies consecutive bytes of data to the
*              end of a message.
*
*       Ret:   ROK      - ok
*
*       Notes: if message is empty: data is placed in the message. message
*              length is incremented. return is ok.
*
*              if message is not empty: data is read by source pointer, 
*              data is placed in back of all other data in message.
*              message length is incremented. return is ok.
*
*              the first byte of data pointed to by the source pointer will
*              be placed at the back of the message first, the last byte of
*              data pointed to by the source pointer will be placed at the
*              back of the message last (i.e. it will become the last
*              byte of the message).
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SAddPstMsgMult
(
Data *src,                  /* source */
MsgLen cnt,                 /* count */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SAddPstMsgMult(src, cnt, mBuf)
Data *src;                  /* source */
MsgLen cnt;                 /* count */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(SAddPstMsgMult)
   RETVALUE(ROK);
} /* end of SAddPstMsgMult */


/*
*
*       Fun:   Get post message multiple
*
*       Desc:  This function allocates consecutive bytes of data at the
*              end of a message.
*
*       Ret:   ROK      - ok
*
*       Notes: if message is empty: data is placed in the message. message
*              length is incremented. return is ok.
*              
*              if message is not empty: data is read by source pointer, 
*              space is allocated in back of all other data in message.
*              message length is incremented. return is ok.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SGetPstMsgMult
(
MsgLen cnt,                 /* count */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SGetPstMsgMult(cnt, mBuf)
MsgLen cnt;                 /* count */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(SGetPstMsgMult)
   RETVALUE(ROK);
} /* end of SGetPstMsgMult */


/*
*
*       Fun:   Remove pre message multiple
*
*       Desc:  This function copies and then removes consecutive bytes of
*              data from the beginning of a message.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*
*       Notes: if message is empty: message is unchanged. return is ok,
*              data not available.
*
*              if message is not empty: data is removed from front of
*              message, data is returned by destination pointer. message
*              length is decremented. return is ok.
*
*              the first byte of data read from the message will be placed 
*              in the destination buffer first (i.e. this was the first byte
*              of the message), the last byte of data read from the message
*              will be placed in the destination buffer last.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SRemPreMsgMult
(
Data *dst,                  /* destination */
MsgLen cnt,                 /* count */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SRemPreMsgMult(dst, cnt, mBuf)
Data *dst;                  /* destination */
MsgLen cnt;                 /* count */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(SRemPreMsgMult)
   RETVALUE(ROK);
} /* end of SRemPreMsgMult */


/*
*
*       Fun:   Remove post message multiple
*
*       Desc:  This function copies and then removes consecutive bytes of
*              data from the end of a message.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*
*       Notes: if message is empty: message is unchanged. return is ok,
*              data not available.
*
*              if message is not empty: data is removed from front of
*              message, data is returned by destination pointer. message
*              length is decremented. return is ok.
*
*              the first byte of data read from the message will be placed 
*              in the destination buffer first (i.e. this was the last byte
*              of the message), the last byte of data read from the message
*              will be placed in the destination buffer last.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SRemPstMsgMult
(
Data *dst,                  /* destination */
MsgLen cnt,                 /* count */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SRemPstMsgMult(dst, cnt, mBuf)
Data *dst;                  /* destination */
MsgLen cnt;                 /* count */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(SRemPstMsgMult)
   RETVALUE(ROK);
} /* end of SRemPstMsgMult */


/*
*
*       Fun:   Replace message
*
*       Desc:  This function replaces one byte of data in a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed
*
*       Notes: index is 0 based and indicates location in message
*
*              if index is less than the length of the message:
*              data is replaced at specified index. message length
*              is unchanged. return is ok.
*
*              if index is greater than or equal to
*              the length of the message: message is unchanged.
*              return is ok, data not available.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SRepMsg
(
Data data,                  /* data */
Buffer *mBuf,               /* message buffer */
MsgLen idx                  /* index */
)
#else
PUBLIC S16 SRepMsg(data, mBuf, idx)
Data data;                  /* data */
Buffer *mBuf;               /* message buffer */
MsgLen idx;                 /* index */
#endif
{
   TRC2(SRepMsg)
   RETVALUE(ROK);
} /* end of SRepMsg */


/*
*
*       Fun:   Examine message
*
*       Desc:  This function copies one byte of data from a message
*              without modifying the message.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*
*       Notes: index is 0 based and indicates location in message
*
*              if index is less than the length of the message:
*              message is unchanged and data is examined at specified
*              index and returned via pointer to data. message length
*              is unchanged. return is ok.
*
*              if index is greater than or equal to
*              the length of the message: message is unchanged and 0
*              is returned via pointer to data. return is ok, data
*              not available.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SExamMsg
(
Data *dataPtr,              /* pointer to data */
Buffer *mBuf,               /* message buffer */
MsgLen idx                  /* index */
)
#else
PUBLIC S16 SExamMsg(dataPtr, mBuf, idx)
Data *dataPtr;              /* pointer to data */
Buffer *mBuf;               /* message buffer */
MsgLen idx;                 /* index */
#endif
{
   TRC2(SExamMsg)
   RETVALUE(ROK);
} /* end of SExamMsg */


/*
*
*       Fun:   Find length of message
*
*       Desc:  This function determines the length of data within
*              a message.
*
*       Ret:   ROK      - ok
*
*       Notes: length of message is determined, message is unchanged
*              and length is returned via pointer to length. return is ok.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SFndLenMsg
(
REG1 Buffer *mBuf,          /* message buffer */
MsgLen *lngPtr              /* pointer to length */
)
#else
PUBLIC S16 SFndLenMsg(mBuf, lngPtr)
REG1 Buffer *mBuf;          /* message buffer */
MsgLen *lngPtr;             /* pointer to length */
#endif
{
   TRC2(SFndLenMsg)
   RETVALUE(ROK);
} /* end of SFndLenMsg */


/*
*
*       Fun:   Concatenate Two Messages
*
*       Desc:  This function will concatenate the two specified messages
*              into one message.
*
*       Ret:   ROK      - ok
*
*       Notes: if order equal M1M2: all data attached to message 2 is
*              moved to the end of message 1. message 2 is set to empty.
*              message 1 length is increased by length of message 2.
*              message 2 length is set to zero. message 2 is not returned
*              to memory. return is ok.
*
*              if order equal M2M1: all data attached to message 2 is
*              moved to the front of message 1. message 2 is set to empty.
*              message 1 length is increased by length of message 2.
*              message 2 length is set to zero. message 2 is not returned
*              to memory. return is ok.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SCatMsg
(
REG1 Buffer *mBuf1,         /* message 1 */
REG2 Buffer *mBuf2,         /* message 2 */
Order order                 /* order */
)
#else
PUBLIC S16 SCatMsg(mBuf1, mBuf2, order)
REG1 Buffer *mBuf1;         /* message 1 */
REG2 Buffer *mBuf2;         /* message 2 */
Order order;                /* order */
#endif
{
   TRC2(SCatMsg)
   RETVALUE(ROK);
} /* end of SCatMsg */


/*
*
*       Fun:   SSegMsg
*
*       Desc:  This function will segment one specified message into two
*              messages.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*
*       Notes: message 1 is the original message.
*
*              message 2 is the new message.
*
*              index is 0 based and indicates location in message 1
*              from which message 2 will be created.
*
*              if index equal 0: message 2 is created and all data
*              attached to message 1 is moved to message 2. message 1
*              is not returned to memory. return is ok.
*
*              if index is not equal to 0 and less than the length of
*              the message minus 1: message 2 is created, all data
*              attached to message 1 from index (inclusive) is moved to
*              message 2. message 1 contains data from index 0 to index
*              minus 1. return is ok.
*
*              if index is not equal to 0 and greater than or equal to
*              the length of the message: message 1 is unchanged.
*              message 2 is set to null. return is ok, data not available.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SSegMsg
(
REG1 Buffer *mBuf1,         /* message 1 */
MsgLen idx,                 /* index */
REG2 Buffer **mBuf2         /* message 2 */
)
#else
PUBLIC S16 SSegMsg(mBuf1, idx, mBuf2)
REG1 Buffer *mBuf1;         /* message 1 */
MsgLen idx;                 /* index */
REG2 Buffer **mBuf2;        /* message 2 */
#endif
{
   TRC2(SSegMsg)
   RETVALUE(ROK);
} /* end of SSegMsg */


/*
*
*       Fun:   Copy from message to fixed buffer
*
*       Desc:  This function copies data from a message
*              into a fixed buffer.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SCpyMsgFix
(
Buffer *srcMbuf,            /* source message buffer */
MsgLen srcIdx,              /* source index */
MsgLen cnt,                 /* count */
Data *dstBuf,               /* destination buffer */
MsgLen *cCnt                /* copied count */
)
#else
PUBLIC S16 SCpyMsgFix(srcMbuf, srcIdx, cnt, dstBuf, cCnt)
Buffer *srcMbuf;            /* source message buffer */
MsgLen srcIdx;              /* source index */
MsgLen cnt;                 /* count */
Data *dstBuf;               /* destination buffer */
MsgLen *cCnt;               /* copied count */
#endif
{
   TRC2(SCpyMsgFix)
   RETVALUE(ROK);
} /* end of SCpyMsgFix */


/*
*
*       Fun:   Copy from fixed buffer to message
*
*       Desc:  This function copies data from a fixed buffer to a
*              message.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SCpyFixMsg
(
Data *srcBuf,               /* source buffer */
Buffer *dstMbuf,            /* destination message buffer */
MsgLen dstIdx,              /* destination index */
MsgLen cnt,                 /* count */
MsgLen *cCnt                /* copied count */
)
#else
PUBLIC S16 SCpyFixMsg(srcBuf, dstMbuf, dstIdx, cnt, cCnt)
Data *srcBuf;               /* source buffer */
Buffer *dstMbuf;            /* destination message buffer */
MsgLen dstIdx;              /* destination index */
MsgLen cnt;                 /* count */
MsgLen *cCnt;               /* copied count */
#endif
{
   TRC2(SCpyFixMsg)
   RETVALUE(ROK);
} /* end of SCpyFixMsg */


/*
*
*       Fun:   Compress Message
*
*       Desc:  This function is used to compress a message into
*              the minimum number of data buffers needed.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SCompressMsg
(
Buffer *mBuf                     /* message buffer */
)
#else
PUBLIC S16 SCompressMsg(mBuf)
Buffer *mBuf;                    /* message buffer */
#endif
{
   TRC2(SCompressMsg)
   RETVALUE(ROK);
}  /* end of SCompressMsg */


/*
*
*       Fun:   SCpyMsgMsg
*
*       Desc:  This function is used to copy a message into
*              a new region and or pool of memory.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SCpyMsgMsg
(
Buffer *srcBuf,                   /* source message buffer */
Region region,                    /* destination region */
Pool pool,                        /* destination pool */
Buffer **dstBuf                   /* pointer to destination message buffer */
)
#else
PUBLIC S16 SCpyMsgMsg(srcBuf, region, pool, dstBuf)
Buffer *srcBuf;                   /* source message buffer */
Region region;                    /* destination region */
Pool pool;                        /* destination pool */
Buffer **dstBuf;                  /* pointer to destination message buffer */
#endif
{
   TRC2(SCpyMsgMsg)
   RETVALUE(ROK);
} /* end of SCpyMsgMsg */


/*
*
*       Fun:   SAddMsgRef
*
*       Desc:  This function is used to copy a message into
*              a new region and or pool of memory.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SAddMsgRef
(
Buffer *srcBuf,                   /* source message buffer */
Region region,                    /* destination region */
Pool pool,                        /* destination pool */
Buffer **dstBuf                   /* pointer to destination message buffer */
)
#else
PUBLIC S16 SAddMsgRef(srcBuf, region, pool, dstBuf)
Buffer *srcBuf;                   /* source message buffer */
Region region;                    /* destination region */
Pool pool;                        /* destination pool */
Buffer **dstBuf;                  /* pointer to destination message buffer */
#endif
{
   TRC2(SAddMsgRef)
   RETVALUE(ROK);
} /* end of SAddMsgRef */


/*
*
*       Fun:   Check resources
*
*       Desc:  This function is used to check available system
*              resources (e.g. memory). The availability of
*              system resources determines the types of flow
*              control used by the protocol layer.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SChkRes
(
REG1 Region region,         /* region id */
REG2 Pool pool,             /* pool id */
Status *status              /* pointer to status */
)
#else
PUBLIC S16 SChkRes(region, pool, status)
REG1 Region region;         /* region id */
REG2 Pool pool;             /* pool id */
Status *status;             /* pointer to status */
#endif
{
   TRC2(SChkRes)
   RETVALUE(ROK);
} /* end of SChkRes */

/*
*
*       Fun:   SSwapMsg
*
*       Desc:  This function will swap two message data contents.
*              The original mBuf pointers are unchanged.
*
*       Ret:   ROK     - ok
*              RFAILED - failed
*
*       Notes: 
*
*       File:  ss_ptsp.c
*
*/


#ifdef ANSI
PUBLIC S16 SSwapMsg
(
Buffer *mBuf1,              /* message 1 */
Buffer *mBuf2               /* message 2 */
)
#else
PUBLIC S16 SSwapMsg(mBuf1, mBuf2)
Buffer *mBuf1;              /* message 1 */
Buffer *mBuf2;              /* message 2 */
#endif
{
   TRC1(SSwapMsg)
   RETVALUE(ROK);
}
   

/*
*
*       Fun:   Set date and time
*
*       Desc:  This function is used to set the calendar
*              date and time.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SSetDateTime
(
REG1 DateTime *dt           /* date and time */
)
#else
PUBLIC S16 SSetDateTime(dt)
REG1 DateTime *dt;          /* date and time */
#endif
{
   TRC2(SSetDateTime)
   RETVALUE(ROK);
} /* end of SSetDateTime */
 

/*
*
*       Fun:   Get date and time
*
*       Desc:  This function is used to determine the calendar
*              date and time. This information may be used for
*              some management functions.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SGetDateTime
(
REG1 DateTime *dt           /* date and time */
)
#else
PUBLIC S16 SGetDateTime(dt)
REG1 DateTime *dt;          /* date and time */
#endif
{
   TRC2(SGetDateTime)
   RETVALUE(ROK);
} /* end of SGetDateTime */


/*
*
*       Fun:   Get system time
*
*       Desc:  This function is used to determine the system
*              time. This information may be used for
*              some management functions.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SGetSysTime
(
Ticks *sysTime              /* system time */
)
#else
PUBLIC S16 SGetSysTime(sysTime)
Ticks *sysTime;             /* system time */
#endif
{
   TRC2(SGetSysTime)
   RETVALUE(ROK);
} /* end of SGetSysTime */

/*
*
*       Fun:   Get referenced time
*
*       Desc:  This function is used to determine the time in seconds
*              and microseconds from a reference time.  The reference
*              time is expressed in seconds from UTC EPOC, January 1,
*              1970.
*
*       Ret:   ROK      - ok
*              RFAILED  - fail
*
*       Notes: Macros are defined for reference times:
*                 SS_REFTIME_01_01_1970
*                 SS_REFTIME_01_01_2002
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetRefTime
(
U32 refTime,             /* reference time */
U32 *sec,
U32 *usec
)
#else
PUBLIC S16 SGetRefTime(refTime, sec, usec)
U32 refTime;             /* reference time */
U32 *sec;
U32 *usec;
#endif
{

   TRC2(SGetRefTime);

   RETVALUE(ROK);

}/* end of SGetRefTime */


/*
*
*       Fun:   Get Random Number
*
*       Desc:  Invoked by layer when a pseudorandom number
*              is required.
*
*       Ret:   ROK      - ok
*
*       Notes: Suggested approach uses shuffled Linear Congruential
*              Operators as described in Byte magazine October
*              1984; "Generating and Testing Pseudorandom Numbers"
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SRandom
(
Random *value               /* random number */
)
#else
PUBLIC S16 SRandom(value)
Random *value;              /* random number */
#endif
{
   TRC2(SRandom)
   RETVALUE(ROK);
} /* end of SRandom */


/*
*
*       Fun:   Error
*
*       Desc:  Invoked by layer when an unrecoverable
*              software error is detected. This function should
*              never return.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SError
(
Seq seq,                    /* sequence */
Reason reason               /* reason */
)
#else
PUBLIC S16 SError(seq, reason)
Seq seq;                    /* sequence */
Reason reason;              /* reason */
#endif
{
   TRC2(SError)
   RETVALUE(ROK);
} /* end of SError */


/*
*
*       Fun:   SLogError
*
*       Desc:  Invoked by layer when a software error is detected.
*
*       Ret:   Void
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
 
#ifdef ANSI
PUBLIC Void SLogError
(
Ent ent,                    /* Calling layer's entity id */
Inst inst,                  /* Calling layer's instance id */
ProcId procId,              /* Calling layer's processor id */
Txt *file,                  /* file name where error occured */
S32 line,                   /* line in file where error occured */
ErrCls errCls,              /* error class */
ErrCode errCode,            /* layer unique error code */
ErrVal errVal,              /* error value */
Txt *errDesc                /* description of error */
)
#else
PUBLIC Void SLogError(ent, inst, procId, file, line, errCls, errCode, errVal, errDesc)
Ent ent;                    /* Calling layer's entity id */
Inst inst;                  /* Calling layer's instance id */
ProcId procId;              /* Calling layer's processor id */
Txt *file;                  /* file name where error occured */
S32 line;                   /* line in file where error occured */
ErrCls errCls;              /* error class */
ErrCode errCode;            /* layer unique error code */
ErrVal errVal;              /* error value */
Txt *errDesc;               /* description of error */
#endif
{
   TRC2(SLogError)
   RETVOID;
} /* end of SLogError */

/* modification: with multiple procs, the function is no more supported */
#ifndef SS_MULTIPLE_PROCS

/*
*
*       Fun:   Register Activate Task - initialize
*
*       Desc:  This function is used to register an initialization function
*              for the layer. The system services will invoke the function
*              passed to it one time. The initialization function will be
*              used by the layer to initilize the layer.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SRegInit
(
Ent ent,                    /* entity */
Inst inst,                  /* instance */
PAIFS16 initFnct            /* initialization function, typically SActvInit */
)
#else
PUBLIC S16 SRegInit(ent, inst, initFnct)
Ent ent;                    /* entity */
Inst inst;                  /* instance */
PAIFS16 initFnct;           /* initialization function, typically SActvInit */
#endif
{
   TRC2(SRegInit)
   RETVALUE(ROK);
} /* end of SRegInit */

#endif /* SS_MULTIPLE_PROCS */

/*
*
*       Fun:   Register Activate Task - timer
*
*       Desc:  This function is used to register a configurable timer function
*              for the layer. The system services will periodically invoke the
*              function passed to it. The timer function will be used by the
*              layer to manage the layers internal protocol timers.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
/* procId added and type of timer function modified */ 
#ifndef SS_MULTIPLE_PROCS

#ifdef ANSI
PUBLIC S16 SRegCfgTmr
(
Ent ent,                    /* entity */
Inst inst,                  /* instance */
S16 period,                 /* period */
S16 units,                  /* period units */
PFS16 tmrFnct               /* timer function, typically SActvTmr */
)
#else
PUBLIC S16 SRegCfgTmr(ent, inst, period, units, tmrFnct)
Ent ent;                    /* entity */
Inst inst;                  /* instance */
S16 period;                 /* period */
S16 units;                  /* period units */
PFS16 tmrFnct;              /* timer function, typically SActvTmr */
#endif

#else /* SS_MULTIPLE_PROCS */

#ifdef ANSI
PUBLIC S16 SRegCfgTmr
(
ProcId proc,                /* processor */
Ent ent,                    /* entity */
Inst inst,                  /* instance */
S16 period,                 /* period */
S16 units,                  /* period units */
PAIFTMRS16 tmrFnct          /* timer function, typically SActvTmr */
)
#else
PUBLIC S16 SRegCfgTmr(proc, ent, inst, period, units, tmrFnct)
ProcId proc;                /* processor */
Ent ent;                    /* entity */
Inst inst;                  /* instance */
S16 period;                 /* period */
S16 units;                  /* period units */
PAIFTMRS16 tmrFnct;         /* timer function, typically SActvTmr */
#endif

#endif /* SS_MULTIPLE_PROCS */
{
   TRC2(SRegCfgTmr)
   RETVALUE(ROK);
} /* end of SRegCfgTmr */


/*
*
*       Fun:   SDeregCfgTmr
*
*       Desc:  This function is used to deregister a configurable timer function
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
/* procId added and type of timer function modified */ 
#ifndef SS_MULTIPLE_PROCS

#ifdef ANSI
PUBLIC S16 SDeregCfgTmr
(
Ent ent,                    /* entity */
Inst inst,                  /* instance */
S16 period,                 /* period */
S16 units,                  /* period units */
PFS16 tmrFnct               /* timer function, typically 'SActvTmr' */
)
#else
PUBLIC S16 SDeregCfgTmr(ent, inst, period, units, tmrFnct)
Ent ent;                    /* entity */
Inst inst;                  /* instance */
S16 period;                 /* period */
S16 units;                  /* period units */
PFS16 tmrFnct;              /* timer function, typically 'SActvTmr'*/
#endif

#else /* SS_MULTIPLE_PROCS */

#ifdef ANSI
PUBLIC S16 SDeregCfgTmr
(
ProcId proc,                /* processor */
Ent ent,                    /* entity */
Inst inst,                  /* instance */
S16 period,                 /* period */
S16 units,                  /* period units */
PAIFTMRS16 tmrFnct          /* timer function, typically SActvTmr */
)
#else
PUBLIC S16 SDeregCfgTmr(proc, ent, inst, period, units, tmrFnct)
ProcId proc;                /* processor */
Ent ent;                    /* entity */
Inst inst;                  /* instance */
S16 period;                 /* period */
S16 units;                  /* period units */
PAIFTMRS16 tmrFnct;         /* timer function, typically SActvTmr */
#endif

#endif /* SS_MULTIPLE_PROCS */
{
   TRC2(SDeregCfgTmr)
   RETVALUE(ROK);
} /* end of SDeregCfgTmr */

/* modification: with multiple procs, the function is no more supported */
#ifndef SS_MULTIPLE_PROCS

/*
*
*       Fun:   SRegActvTsk
*
*       Desc:  This function is used to register an activation function
*              for the layer. The system services will invoke the
*              function passed to it whenever a task buffer is received.
*              The activation function will be used by the layer to receive
*              messages from other entities.  It allows a priority to be
*              associated with the task so that it can be preempted if
*              necessary.
*
*       Ret:   ROK      - ok
*
*       Notes: SRegActvTsk will replace SRegTsk and SRegPTsk.
*
*       File:  ss_ptsp.c
*
*
*/
#ifdef ANSI
PUBLIC S16 SRegActvTsk
(
Ent ent,                    /* entity */
Inst inst,                  /* instance */
Ttype ttype,                /* task type */
Prior prior,                /* task priority */
ActvTsk actvTsk             /* activation function, typically 'SActvTask' */
)
#else
PUBLIC S16 SRegActvTsk(ent, inst, ttype, prior, actvTsk)
Ent ent;                    /* entity */
Inst inst;                  /* instance */
Ttype ttype;                /* task type */
Prior prior;                /* task priority */
ActvTsk actvTsk;            /* activation function, typically 'SActvTask' */
#endif
{
   TRC2(SRegActvTsk)
   RETVALUE(ROK);
} /* end of SRegActvTsk */

#endif /* SS_MULTIPLE_PROCS */

#ifdef ENB_RELAY

/*
*
*       Fun:   SRegDrvrTsk
*
*       Desc:  register a driver task for a previously unknown
*              processor
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: MOS Loadable driver interface.
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SRegDrvrTsk
(
Inst inst,
ProcId low,
ProcId high,
ActvTsk actvTsk, 
ISTsk isTsk
)
#else
PUBLIC S16 SRegDrvrTsk(inst, low, high, actvTsk, isTsk)
Inst inst;
ProcId low;
ProcId high;
ActvTsk actvTsk; 
ISTsk isTsk;
#endif
{
   TRC2(SRegDrvrTsk)
   RETVALUE(ROK);
} /* end of SRegDrvrTsk */

/* ss_ptsp_c_001.main_57 : added function */

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
   TRC2(SDeregDrvrTsk)
   RETVALUE(ROK);
}/*SDeregDrvrTsk*/
#endif /* ENB_RELAY */


/*
*
*       Fun:   Deregister Initialize, task buffer and timer
*
*       Desc:  This function is used to deregister the initialization,
*              activation and timer functions for a task.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SDeregInitTskTmr
(
Ent ent,                    /* entity */
Inst inst                   /* instance */
)
#else
PUBLIC S16 SDeregInitTskTmr(ent, inst)
Ent ent;                    /* entity */
Inst inst;                  /* instance */
#endif
{
   TRC2(SDeregInitTskTmr)
   RETVALUE(ROK);
} /* end of SDeregInitTskTmr */


/*
*
*       Fun:   Post Task
*
*       Desc:  This function posts a task buffer to a task.
*
*       Ret:   ROK      - ok
*
*       Notes: SPstTsk will replace SPostTsk
*
*       File:  ss_ptsp.c
*
*/

#ifdef ANSI
PUBLIC S16 SPstTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SPstTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(SPstTsk)
   RETVALUE(ROK);
} /* end of SPstTsk */


/*
*
*       Fun:   Exit Task
*
*       Desc:  This function exits from a task.
*
*       Ret:   ROK      - ok
*
*       Notes: This function should be called at the end of
*              any task activation by either a message or timer. It should
*              not be called by any task activation by initialization.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SExitTsk
(
void
)
#else
PUBLIC S16 SExitTsk()
#endif
{
   TRC2(SExitTsk)
   RETVALUE(ROK);
} /* end of SExitTsk */

/* modification: with multiple procs, the function is no more supported */
#ifndef SS_MULTIPLE_PROCS

/*
*
*       Fun:   SFndProcId
*
*       Desc:  This function finds the local processor id.
*
*       Ret:   local processor id
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC ProcId SFndProcId
(
void
)
#else
PUBLIC ProcId SFndProcId()
#endif
{
   TRC2(SFndProcId)
   RETVALUE(0);
} /* end of SFndProcId */


/*
*
*       Fun:   SSetProcId
*
*       Desc:  This function finds the local processor id.
*
*       Ret:   ROK      - ok
*
*       Notes: 
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC Void SSetProcId
(
ProcId pId
)
#else
PUBLIC Void SSetProcId(pId)
ProcId pId;
#endif
{
   TRC2(SSetProcId)
   RETVOID;
} /* end of SSetProcId */

#endif /* SS_MULTIPLE_PROCS */


/*
*
*       Fun:   Exit Interrupt
*
*       Desc:  This function exits from an interrupt.
*
*       Ret:   ROK      - ok
*
*       Notes: This function may be called by the OS
*              or layer1 hardware drivers
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SExitInt
(
void
)
#else
PUBLIC S16 SExitInt()
#endif
{
   TRC2(SExitInt)
   RETVALUE(ROK);
} /* end of SExitInt */


/*
*
*       Fun:   Hold Interrupt
*
*       Desc:  This function prohibits interrupts from being enabled until
*              release interrupt, and should be called only under certain 
*              pre-conditions:
*
*              1) in an interrupt service routine (ISR), i.e. in a routine 
*                 installed by SPutVect.  
*              2) before any call to SDisInt, SEnbInt.
*
*       Ret:   ROK      - ok
*
*       Notes: The first pre-condition implies that SHoldInt will not be 
*              called from the system services
*
*              This function may be called by the OS
*              or layer1 hardware drivers
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SHoldInt
(
void
)
#else
PUBLIC S16 SHoldInt()
#endif
{
   TRC2(SHoldInt)
   RETVALUE(ROK);
} /* end of SHoldInt */


/*
*
*       Fun:   Release Interrupt
*
*       Desc:  This function allows interrupts to be enabled, and should
*              be called only under certain pre-conditions:
*
*              1) in an interrupt service routine (ISR), i.e. in a routine
*                 installed by SPutVect.
*              2) before returning from the ISR.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: The first pre-condition implies that SRelInt will not be 
*              called in the system services
*
*              This function may be called by the OS
*              or layer1 hardware drivers
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SRelInt
(
void
)
#else
PUBLIC S16 SRelInt()
#endif
{
   TRC2(SRelInt)
   RETVALUE(ROK);
} /* end of SRelInt */
 

/*
*
*       Fun:   Enable interrupt
*
*       Desc:  This function enables interrupts.
*
*       Ret:   ROK      - ok
*
*       Notes: This function may be called by the OS
*              or layer1 hardware drivers
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC INLINE S16 SEnbInt
(
void
)
#else
PUBLIC INLINE S16 SEnbInt()
#endif
{
   TRC2(SEnbInt)
   RETVALUE(ROK);
} /* end of SEnbInt */


/*
*
*       Fun:   Disable interrupt
*
*       Desc:  This function disables interrupts.
*
*       Ret:   ROK      - ok
*
*       Notes: This function may be called by the OS
*              or layer1 hardware drivers
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC INLINE S16 SDisInt
(
void
)
#else
PUBLIC INLINE S16 SDisInt()
#endif
{
   TRC2(SDisInt)
   RETVALUE(ROK);
} /* end of SDisInt */


/*
*
*       Fun:   Get Vector
*
*       Desc:  This function gets the function address stored at the
*              specified interrupt vector.
*
*       Ret:   ROK      - ok
*
*       Notes: This function may be called by the OS
*              or layer1 hardware drivers
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SGetVect
(
VectNmb vectNmb,            /* vector number */
PIF *vectFnct               /* vector function */
)
#else
PUBLIC S16 SGetVect(vectNmb, vectFnct)
VectNmb vectNmb;            /* vector number */
PIF *vectFnct;              /* vector function */
#endif
{
   TRC2(SGetVect)
   RETVALUE(ROK);
} /* end of SGetVect */


/*
*
*       Fun:   Put Vector
*
*       Desc:  This function puts the function address at the
*              specified interrupt vector.
*
*       Ret:   ROK      - ok
*
*       Notes: This function may be called by the OS
*              or layer1 hardware drivers
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SPutVect
(
VectNmb vectNmb,            /* vector number */
PIF vectFnct                /* vector function */
)
#else
PUBLIC S16 SPutVect(vectNmb, vectFnct)
VectNmb vectNmb;            /* vector number */
PIF vectFnct;               /* vector function */
#endif
{
   TRC2(SPutVect)
   RETVALUE(ROK);
} /* end of SPutVect */

#ifdef WINNT_KERN

/*
*
*       Fun:   Put ISR, DPR
*
*       Desc:  This function associates the function address of the ISR 
*              and the DPR routines with the specified interrupt vector.
*
*       Ret:   ROK      - ok
*
*       Notes: This function may be called by the OS
*              or layer1 hardware drivers
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SPutIsrDpr
(
VectNmb vectNmb,            /* vector number */
Void    *context,           /* context passed to ISR and DPR */
PIF     isrFnct,            /* ISR vector function */
PIF     dprFnct             /* DPR vector function */
)
#else
PUBLIC S16 SPutIsrDpr(vectNmb, context, isrFnct, dprFnct)
VectNmb vectNmb;            /* vector number */
Void    *context;           /* context passed to ISR and DPR */
PIF     isrFnct;            /* ISR vector function */
PIF     dprFnct;            /* DPR vector function */
#endif
{
   TRC2(SPutIsrDpr)
   RETVALUE(ROK);
} /* end of SPutIsrDpr */


/*
*
*       Fun:   Synchornize with Interrupt
*
*       Desc:  This function synchronizes access to shared data strucures
*              between ISR and non-ISR routines.
*
*       Ret:   ROK      - ok
*
*       Notes: This function may be called by the OS
*              or layer1 hardware drivers
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SSyncInt
(
U16     adapterNmb,         /* Adapter number */
PFVOID  syncFnct,           /* ISR vector function */
Void    *syncContext        /* Synchronization function */
)
#else
PUBLIC S16 SSyncInt(adapterNmb, syncFnct, syncContext)
U16     adapterNmb;         /* Adapter number */
PFVOID  syncFnct;           /* ISR vector function */
Void    *syncContext;       /* Synchronization function */
#endif
{
   TRC2(SSyncInt)
   RETVALUE(ROK);
} /* end of SSyncInt */
#endif /* WINNT_KERN */

/* modification: with multiple procs, the function is no more supported */
#ifndef SS_MULTIPLE_PROCS

/*
*
*       Fun:   SGetEntInst
*
*       Desc:  This function gets the current entity and instance.
*
*       Ret:   ROK      - ok
*
*       Notes: This function may be called by the OS
*              or layer1 hardware drivers
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SGetEntInst
(
Ent *ent,                    /* entity */
Inst *inst                   /* instance */
)
#else
PUBLIC S16 SGetEntInst(ent, inst)
Ent *ent;                    /* entity */
Inst *inst;                  /* instance */
#endif
{
   TRC2(SGetEntInst)
   RETVALUE(ROK);
} /* end of SGetEntInst */


/*
*
*       Fun:   SSetEntInst
*
*       Desc:  This function sets the current entity and instance.
*
*       Ret:   ROK      - ok
*
*       Notes: This function may be called by the OS
*              or layer1 hardware drivers
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SSetEntInst
(
Ent ent,                    /* entity */
Inst inst                   /* instance */
)
#else
PUBLIC S16 SSetEntInst(ent, inst)
Ent ent;                    /* entity */
Inst inst;                  /* instance */
#endif
{
   TRC2(SSetEntInst)
   RETVALUE(ROK);
} /* end of SSetEntInst */

#endif /* SS_MULTIPLE_PROCS */


/*
*
*       Fun:   SAddDBufPre
*
*       Desc:  This function queues a data buffer to the
*              front of the specified message buffer.
*
*       Ret:   ROK     - ok
*              RFAILED - failed, general (optional)
*
*       Notes: if buffer queue is empty: buffer is placed in the queue. queue
*              length is incremented.
*              
*              if buffer queue is not empty: buffer is placed in front of all
*              other buffers in queue. queue length is incremented.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC INLINE S16 SAddDBufPre
(
Buffer *mBuf,                   /* message buffer */
Buffer *dBuf                    /* data buffer */
)
#else
PUBLIC INLINE S16 SAddDBufPre(mBuf, dBuf)
Buffer *mBuf;                    /* message buffer */
Buffer *dBuf;                   /* data buffer */
#endif
{
  
   TRC1(SAddDBufPre)
   RETVALUE(ROK);
} /* end of SAddDBufPre */

  
/*
*
*       Fun:   SAddDBufPst
*
*       Desc:  This function queues a data buffer to the
*              back of the specified message buffer .
*
*       Ret:   ROK     - ok
*              RFAILED - failed, general (optional)
*
*       Notes: if queue is empty: buffer is placed in the queue.
*              queue length is incremented.
*              
*              if queue is not empty: buffer is placed behind all
*              other buffers in queue. queue length is incremented.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC INLINE S16 SAddDBufPst
(
Buffer *mBuf,                   /* message buffer */
Buffer *dBuf                    /* data buffer */
)
#else
PUBLIC INLINE S16 SAddDBufPst(mBuf, dBuf)
Buffer *mBuf;                   /* message buffer */
Buffer *dBuf;                   /* data buffer */
#endif
{
   TRC1(SAddDBufPst)
   RETVALUE(ROK);
} /* end of SAddDBufPst */

  
/*
*
*       Fun:   SRemDBufPre
*
*       Desc:  This function dequeues a data buffer from
*              the front of the specified message buffer.
*
*       Ret:   ROK     - ok
*              ROKDNA  - ok, data not available
*              RFAILED - failed, general (optional)
*
*       Notes: if queue is empty: pointer to buffer is set to null and
*              return is ok, data not available. queue length is unchanged.
*              
*              if queue is not empty: pointer to buffer is set to first
*              buffer in queue, first buffer in queue is removed and
*              return is ok. queue length is decremented.
*
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC INLINE S16 SRemDBufPre
(
Buffer *mBuf,                   /* message buffer */
Buffer **dBufPtr                /* pointer to data buffer */
)
#else
PUBLIC INLINE S16 SRemDBufPre(mBuf, dBufPtr)
Buffer *mBuf;                   /* message buffer */
Buffer **dBufPtr;               /* pointer to data buffer */
#endif
{
   TRC1(SRemDBufPre)
   RETVALUE(ROK);
} /* end of SRemDBufPre */

  
/*
*
*       Fun:   SRemDBufPst
*
*       Desc:  This function dequeues a data or message buffer from the
*              back of the specified message buffer.
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
*       File:  ss_ptsp.c
*
*/
  
#ifdef ANSI
PUBLIC INLINE S16 SRemDBufPst
(
Buffer *mBuf,                   /* message buffer */
Buffer **dBufPtr                /* pointer to data buffer */
)
#else
PUBLIC INLINE S16 SRemDBufPst(mBuf, dBufPtr)
Buffer *mBuf;                   /* message buffer */
Buffer **dBufPtr;               /* pointer to data buffer */
#endif
{
   TRC1(SRemDBufPst)
   RETVALUE(ROK);
} /* end of SRemDBufPst */


/*
*
*       Fun:   SGetDataRx
*
*       Desc:  Given a data buffer, return a pointer to the
*              data payload, and the length of the payload
*
*
*       Ret:   ROK ok
*              RFAILED error
*
*       Notes: This assumes an uninitialized dBuf
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC INLINE S16 SGetDataRx
(
Buffer *dBuf,                   /* data buffer */
MsgLen pad,                     /* pad */
Data **retDatPtr,               /* return data pointer */
MsgLen *retDatLen               /* return data length */
)
#else
PUBLIC INLINE S16 SGetDataRx(dBuf, pad, retDatPtr, retDatLen)
Buffer *dBuf;                   /* data buffer */
MsgLen pad;                     /* pad */
Data **retDatPtr;               /* return data pointer */
MsgLen *retDatLen;              /* return data length */
#endif
{
   TRC2(SGetDataRx)
   RETVALUE(ROK);
} /* end of SGetDataRx */


/*
*
*       Fun:   SGetDataTx
*
*       Desc:  Given a data buffer, return a pointer to the
*              data payload, and the length of the payload
*
*
*       Ret:   ROK ok
*              RFAILED error
*
*       Notes: This assumes an initialized dBuf
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC INLINE S16 SGetDataTx
(
Buffer *dBuf,                   /* data buffer */
Data **retDatPtr,               /* return data pointer */
MsgLen *retDatLen               /* return data length */
)
#else
PUBLIC INLINE S16 SGetDataTx(dBuf, retDatPtr, retDatLen)
Buffer *dBuf;                   /* data buffer */
Data **retDatPtr;               /* return data pointer */
MsgLen *retDatLen;              /* return data length */
#endif
{

   TRC2(SGetDataTx)
   RETVALUE(ROK);

} /* end of SGetDataTx */


/*
*
*       Fun:   SUpdMsg
*
*       Desc:  Update a message with a new dBuf
*
*       Ret:   ROK/RFAILED
*
*       Notes: 
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC INLINE S16 SUpdMsg
(
Buffer *mBuf,                   /* message buffer */
Buffer *dBuf,                   /* data buffer */
MsgLen dLen                     /* data length */
)
#else
PUBLIC INLINE S16 SUpdMsg(mBuf, dBuf, dLen)
Buffer *mBuf;                   /* message buffer */
Buffer *dBuf;                   /* data buffer */
MsgLen dLen;                    /* data length */
#endif
{

   TRC2(SUpdMsg)

   RETVALUE(ROK);
} /* end of SUpdMsg */


/*
*
*       Fun:   SInitNxtDBuf
*
*       Desc:  Initialize next Data Buffer Id
*
*       Ret:   ROK
*
*       Notes: Must be called prior to SGetNxtDBuf
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC INLINE S16 SInitNxtDBuf
(
Buffer *mBuf                    /* message buffer */
)
#else
PUBLIC INLINE S16 SInitNxtDBuf(mBuf)
Buffer *mBuf;                   /* message buffer */
#endif
{

   TRC2(SInitNxtDBuf)
   RETVALUE(ROK);
} /* end of SInitNxtDBuf */


/*
*
*       Fun:   SGetNxtDBuf
*
*       Desc:  Get next dBuf in message chain
*
*       Ret:   ROK/RFAILED
*
*       Notes: Must be called after SInitNxtDBuf
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC INLINE S16 SGetNxtDBuf
(
Buffer *mBuf,                   /* message buffer */
Buffer **dBuf                   /* data buffer return */
)
#else
PUBLIC INLINE S16 SGetNxtDBuf(mBuf, dBuf)
Buffer *mBuf;                   /* message buffer */
Buffer **dBuf;                  /* data buffer return */
#endif
{
   TRC2(SGetNxtDBuf)
   RETVALUE(ROK);
} /* end of SGetNxtDBuf */


/*
*
*       Fun:   SAlignDBufEven
*
*       Desc:  align data portion of a data buffer on an even
*              byte boundary.
*
*       Ret:   ROK/RFAILED
*
*       Notes: required for SS7 microcode on the 68302
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SAlignDBufEven
(
Buffer *dBuf                      /* data buffer */
)
#else
PUBLIC S16 SAlignDBufEven(dBuf)
Buffer *dBuf;                   /* data buffer  */
#endif
{
   TRC2(SAlignDBufEven)
   RETVALUE(ROK);
} /* end of SAlignDBufEven */


/*
*
*       Fun:   SChkNxtDBuf
*
*       Desc:  check if next data buffer exists.
*
*       Ret:   ROK/ROKDNA/RFAILED
*
*       Notes: doesn't modify nxtDBuf
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC INLINE S16 SChkNxtDBuf
(
Buffer *mBuf                    /* message buffer */
)
#else
PUBLIC INLINE S16 SChkNxtDBuf(mBuf)
Buffer *mBuf;                   /* message buffer */
#endif
{

   TRC2(SChkNxtDBuf)
   
   RETVALUE(ROK);
} /* end of SChkNxtDBuf */


/*
*
*       Fun:   SSetIntPend
*
*       Desc: 
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: 
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC INLINE S16 SSetIntPend
(
U16 id,                         /* relay id */
Bool flag                       /* flag */
)
#else
PUBLIC INLINE S16 SSetIntPend(id, flag)
U16 id;                         /* relay id */
Bool flag;                      /* flag */
#endif
{

   TRC2(SSetIntPend)
   
   RETVALUE(ROK);
} /* end of SSetIntPend */


/*
*
*       Fun:   SChkMsg
*
*       Desc:  Check Message for length and alignment
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: 
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SChkMsg
(
Buffer *mBuf
)
#else
PUBLIC S16 SChkMsg(mBuf)
Buffer *mBuf;
#endif
{

   TRC2(SChkMsg)
   
   RETVALUE(ROK);
} /* end of SChkMsg */

#ifdef MT

/*
*
*       Fun:   SGetMutex
*
*       Desc:  create and initialize a mutex
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: create a mutex
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetMutex
(
MtMtxId *mId                    /* mutex (returned) */
)
#else
PUBLIC S16 SGetMutex(mId)
MtMtxId *mId;                   /* mutex (returned) */
#endif
{
   TRC2(SGetMutex)

   RETVALUE(RFAILED);
} /* end of SGetMutex */
   

/*
*
*       Fun:   SPutMutex
*
*       Desc:  destroy any state associated with a mutex
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: Destroy a mutex 
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SPutMutex
(
MtMtxId mId                     /* mutex id */
)
#else
PUBLIC S16 SPutMutex(mId)
MtMtxId mId;                    /* mutex id */
#endif
{

   TRC2(SPutMutex)

   RETVALUE(ROK);
} /* end of SPutMutex */


/*
*
*       Fun:   SLockMutex
*
*       Desc:  lock a mutex
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: 
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SLockMutex
(
MtMtxId mId                     /* mutex id */
)
#else
PUBLIC S16 SLockMutex(mId)
MtMtxId mId;
#endif
{
   TRC2(SLockMutex)

   RETVALUE(RFAILED);
} /* end of SLockMutex */


/*
*
*       Fun:   SUnlockMutex
*
*       Desc:  Unlock a mutex
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: 
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SUnlockMutex
(
MtMtxId mId
)
#else
PUBLIC S16 SUnlockMutex(mId)
MtMtxId mId;
#endif
{

   TRC2(SUnlockMutex)
      
   RETVALUE(ROK);
} /* end of SUnlockMutex */


/*
*
*       Fun:   SGetCond
*
*       Desc:  create and initialize a condition variable
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: 
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetCond
(
MtCondId *cId                    /* condition id (returned) */
)
#else
PUBLIC S16 SGetCond(cId)
MtCondId *cId;                   /* condition id (returned) */
#endif
{
   TRC2(SGetCond)

   RETVALUE(RFAILED);
} /* end of SGetCond */
   

/*
*
*       Fun:   SPutCond
*
*       Desc:  destroy any state associated with a Cond
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: 
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SPutCond
(
MtCondId cId                     /* Cond id */
)
#else
PUBLIC S16 SPutCond(cId)
MtCondId cId;                    /* Cond id */
#endif
{
   
   TRC2(SPutCond)

   RETVALUE(ROK);
} /* end of SPutCond */


/*
*
*       Fun:   SCondWait
*
*       Desc:  condition wait
*
*       Ret:   ROK on success
*              
*              RFAILED on error
*
*       Notes: 
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SCondWait
(
MtMtxId mId,
MtCondId cId
)
#else
PUBLIC S16 SCondWait(mId, cId)
MtMtxId mId;
MtCondId cId;
#endif
{
   S32 ret;
   
   TRC2(SCondWait)

   RETVALUE(ROK);
} /* end of SCondWait */


/*
*
*       Fun:   SCondSignal
*
*       Desc:  Condition Signal
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: 
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SCondSignal
(
MtCondId cId
)
#else
PUBLIC S16 SCondSignal(cId)
MtCondId cId;
#endif
{

   TRC2(SCondSignal)

   RETVALUE(ROK);
} /* end of SCondSignal */

/*
*
*       Fun:   SCondBroadcast
*
*       Desc:  Send a condition signal to all threads waiting on this
*              condition
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: Condition Broadcast
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SCondBroadcast
(
MtCondId cId
)
#else
PUBLIC S16 SCondBroadcast(cId)
MtCondId cId;
#endif
{

   TRC2(SCondBroadcast)

   RETVALUE(ROK);
} /* end of SCondBroadcast */


/*
*
*       Fun:   SGetThread
*
*       Desc:  Get Thread 
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: Creates a thread of execution
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetThread
(
MtThrd thrd,                    /* thread function */
MtThrdFlags thr_flgs,           /* thread flags */
Ptr arg,                        /* thread function argument */
MtThrdId *thrdId                /* thread function id */
)
#else
PUBLIC S16 SGetThread(thrd, thr_flgs, arg, thrdId)
MtThrd thrd;                    /* thread function */
MtThrdFlags thr_flgs;           /* thread flags */
Ptr arg;                        /* thread function argument */
MtThrdId *thrdId;               /* thread function id */
#endif
{
   TRC2(SGetThread)
      
   RETVALUE(RFAILED);
} /* end of SGetThread */


/*
*
*       Fun:   SPutThread
*
*       Desc:  Free a thread
*
*       Ret:   None
*
*       Notes: SPutThread must be called by the same thread which 
*              is being freed. It is assumed that all shared resources
*              (i.e. mutexes, etc) have been freed prior to this call.
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SPutThread
(
MtThrdId tId                /* thread function id */
)
#else
PUBLIC S16 SPutThread(tId)
MtThrdId tId;               /* thread function id */
#endif
{
   TRC2(SPutThread)
   
   RETVALUE(ROK);               /* NOTREACHED */
} /* end of SPutThread */


/*
*
*       Fun:   SThreadYield
*
*       Desc:  yield to another thread of equal or higher priority
*
*       Ret:   None
*
*       Notes: 
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC INLINE Void SThreadYield
(
void
)
#else
PUBLIC INLINE Void SThreadYield()
#endif
{

   TRC2(SThreadYield)

   RETVOID;
} /* end of SThreadYield */


/*
*
*       Fun:   SThreadExit
*
*       Desc:  let thread exit...
*
*       Ret:   None
*
*       Notes: 
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC Void SThreadExit
(
Ptr *status                     /* exit status */
)
#else
PUBLIC Void SThreadExit(status)
Ptr *status;                   /* exit status */
#endif
{
   TRC2(SThreadExit)

   RETVOID;
} /* end of SThreadExit */


/*
*
*       Fun:   SSetThrdPrior
*
*       Desc:  set a threads priority
*
*       Ret:   None
*
*       Notes: 
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC Void SSetThrdPrior
(
MtThrdId tId,                   /* thread id */
MtThrdPrior tPr                 /* new priority  */
)
#else
PUBLIC Void SSetThrdPrior(tId, tPr)
MtThrdId tId;                   /* thread id */
MtThrdPrior tPr;                /* new priority */
#endif
{

   TRC2(SSetThrdPrior)

   RETVOID;
} /* end of SSetThrdPrior */


/*
*
*       Fun:   SGetThrdPrior
*
*       Desc:  get a threads priority
*
*       Ret:   None
*
*       Notes: 
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC Void SGetThrdPrior
(
MtThrdId tId,                   /* thread id */
MtThrdPrior *tPr                /* priority (returned) */
)
#else
PUBLIC Void SGetThrdPrior(tId, tPr)
MtThrdId tId;                   /* thread id */
MtThrdPrior *tPr;               /* priority (returned) */
#endif
{

   TRC2(SGetThrdPrior)

   RETVOID;
} /* end of SGetThrdPrior */


/*
*
*       Fun:   SExit
*
*       Desc:  call all the registered exit functions then exit
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: 
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC Void SExit
(
void
)
#else
PUBLIC Void SExit()
#endif
{

   TRC2(SExit)
      
   RETVOID;
} /* end of SExit */
#endif /* MT */

#ifdef SS_AEHDPR_SUPPORT

/* init of semaphore done in initialisation similarly for initializing lock
   for the table which stores the ISR,isrContext,DPR,dprContext and so on */
/*
*
*       Fun:   SSetAehDpr
*
*       Desc:  This function sets the ISR-DPR mechanism.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed
*
*       Notes: This function creates the DPR (Deferred processing) task.This
*              task is meant for deferred processing of the Interrupts.
*              DPR communicates with ISR using semaphore mechanism.
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SSetAehDpr
(
ProcId chipNum,                 /* which chip/processor */
VectNmb vectNmb,                /* interrupt id,processor dependent */
PISR isr,                       /* ISR function pointer */
PTR isrContext,                 /* ISR context,isr called as isr(isrContext) */
PDPR dpr,                       /* DPR function pointer */
PTR dprContext                  /* DPR context */
)
#else
PUBLIC S16 SSetAehDpr(chipNum,vectNmb,isr,isrContext,dpr,dprContext)
ProcId chipNum;                 /* which chip/processor */
VectNmb vectNmb;                /* interrupt id,processor dependent */
PISR isr;                       /* ISR function pointer */
PTR isrContext;                 /* ISR context,isr called as isr(isrContext) */
PDPR dpr;                       /* DPR function pointer */
PTR dprContext;                 /* DPR context */
#endif
{
    TRC1(SSetAehDpr);

    RETVALUE(ROK);
}

/*
*
*       Fun:   SRemoveAehDpr
*
*       Desc:  This function removes a previously set DPR interrupt handler
*
*       Ret:   ROK      - ok
*              RFAILED  - failed
*
*       Notes:
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SRemoveAehDpr
(
ProcId               chipNum,    /* which chip/processor */
VectNmb              vectNmb     /* interrupt id,processor dependent */
)
#else
PUBLIC S16 SRemoveAehDpr(chipNum, vectNmb)
ProcId               chipNum;    /* which chip/processor */
VectNmb              vectNmb;    /* interrupt id,processor dependent */
#endif
{

   TRC1(SRemoveAehDpr);

   RETVALUE(ROK);
}
#endif /* SS_AEHDPR_SUPPORT */

/*
*
*       Fun:   SAlignDBuf
*
*       Desc:  Align data portion of a data buffer on the specified
*              boundary. No restriction is imposed on the alignment.
*
*       Ret:   ROK/RFAILED
*
*       Notes: required by drivers (68360, 860)
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SAlignDBuf
(
Buffer *dBuf,                      /* data buffer */
U32    align                       /* alignemnt required */
)
#else
PUBLIC S16 SAlignDBuf(dBuf, align)
Buffer *dBuf;                      /* data buffer  */
U32    align;                      /* alignemnt required */
#endif
{
   TRC1(SAlignDBuf)

   RETVALUE(ROK);
}


#ifndef SS_ENABLE_MACROS
/*
*
*       Fun:   SGetBufRegionPool
*
*       Desc:  returns the region and pool of the message buffer
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: None
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetBufRegionPool
(
Buffer *mBuf,                   /* message buffer */
Region *region,                 /* region */
Pool   *pool                    /* pool */
)
#else
PUBLIC S16 SGetBufRegionPool(mBuf, region, pool)
Buffer *mBuf;                   /* message buffer */
Region *region;                 /* region */
Pool   *pool;                   /* pool */
#endif
{

   TRC1(SGetBufRegionPool)

   RETVALUE(ROK);
}
#endif /* SS_ENABLE_MACROS */
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
*       File:  ss_ptsp.c
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

   TRC1(SRegRtrTsk);

   RETVALUE(ROK);

}


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
*       File:  ss_ptsp.c
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

   TRC1(SDeregRtrTsk)

   RETVALUE(ROK);
}
#endif /* SS_RTR_SUPPORT */
/*
*
*       Fun:   Register a TAPA task
*
*       Desc:  This function is used to register a TAPA task,
*              and its initialization and activation functions.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes:
*
*       File:  ss_ptsp.c
*
*/
/* procId added */
#ifndef SS_MULTIPLE_PROCS
#ifdef ANSI
PUBLIC S16 SRegTTsk
(
Ent ent,                        /* entity */
Inst inst,                      /* instance */
Ttype type,                     /* task type */
Prior prior,                    /* task priority */
PAIFS16 initTsk,                /* initialization function */
ActvTsk actvTsk                 /* activation function */
)
#else
PUBLIC S16 SRegTTsk(ent, inst, type, prior, initTsk, actvTsk)
Ent ent;                        /* entity */
Inst inst;                      /* instance */
Ttype type;                     /* task type */
Prior prior;                    /* task priority */
PAIFS16 initTsk;                /* initialization function */
ActvTsk actvTsk;                /* activation function */
#endif
#else /* SS_MULTIPLE_PROCS */
#ifdef ANSI
PUBLIC S16 SRegTTsk
(
ProcId proc,                    /* processor */
Ent ent,                        /* entity */
Inst inst,                      /* instance */
Ttype type,                     /* task type */
Prior prior,                    /* task priority */
PAIFS16 initTsk,                /* initialization function */
ActvTsk actvTsk                 /* activation function */
)
#else
PUBLIC S16 SRegTTsk(proc, ent, inst, type, prior, initTsk, actvTsk)
ProcId proc;                    /* processor */
Ent ent;                        /* entity */
Inst inst;                      /* instance */
Ttype type;                     /* task type */
Prior prior;                    /* task priority */
PAIFS16 initTsk;                /* initialization function */
ActvTsk actvTsk;                /* activation function */
#endif
#endif /* SS_MULTIPLE_PROCS */
{

   TRC1(SRegTTsk)

   RETVALUE(ROK);
}

/*
*
*       Fun:   Deregister TAPA task
*
*       Desc:  This function is used to deregister a TAPA task.
*              All information about the task is removed from the
*              task table.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_ptsp.c
*
*/
/* procId added */ 
#ifndef SS_MULTIPLE_PROCS

#ifdef ANSI
PUBLIC S16 SDeregTTsk
(
Ent ent,                        /* entity */
Inst inst                       /* instance */
)
#else
PUBLIC S16 SDeregTTsk(ent, inst)
Ent ent;                        /* entity */
Inst inst;                      /* instance */
#endif

#else /* SS_MULTIPLE_PROCS */

#ifdef ANSI
PUBLIC S16 SDeregTTsk
(
ProcId proc,                    /* processor */
Ent ent,                        /* entity */
Inst inst                       /* instance */
)
#else
PUBLIC S16 SDeregTTsk(proc, ent, inst)
ProcId proc;                    /* processor */
Ent ent;                        /* entity */
Inst inst;                      /* instance */
#endif

#endif /* SS_MULTIPLE_PROCS */
{
   TRC1(SDeregTTsk)

   RETVALUE(ROK);
}

/*
*
*       Fun:   Create system task
*
*       Desc:  This function is used to create a system task. An
*              entry is located in the system task table and the
*              implementation-specific function is called.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes:
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SCreateSTsk
(
SSTskPrior tskPrior,            /* task priority */
SSTskId *tskId                  /* filled in with system task ID */
)
#else
PUBLIC S16 SCreateSTsk(tskPrior, tskId)
SSTskPrior tskPrior;            /* task priority */
SSTskId *tskId;                 /* filled in with system task ID */
#endif
{

   TRC1(SCreateSTsk)

   RETVALUE(ROK);
}


/*
*
*       Fun:   Destroy system task
*
*       Desc:  This function is used to destroy a system task. The
*              entry is located in the system task table and the
*              implementation-specific function is called.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SDestroySTsk
(
SSTskId tskId                   /* system task to be destroyed */
)
#else
PUBLIC S16 SDestroySTsk(tskId)
SSTskId tskId;                  /* system task to be destroyed */
#endif
{

   TRC1(SDestroySTsk)

   RETVALUE(ROK);
}

/*
*
*       Fun:   Attach TAPA task
*
*       Desc:  This function is used to attach a TAPA task to a
*              system task. The system task will begin to execute
*              the TAPA task.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes:
*
*       File:  ss_ptsp.c
*
*/
/* procId added */ 
#ifndef SS_MULTIPLE_PROCS

#ifdef ANSI
PUBLIC S16 SAttachTTsk
(
Ent ent,                        /* entity ID of the task */
Inst inst,                      /* instance ID of the task */
SSTskId sTskId                  /* system task to use */
)
#else
PUBLIC S16 SAttachTTsk(ent, inst, sTskId)
Ent ent;                        /* entity ID of the task */
Inst inst;                      /* instance ID of the task */
SSTskId sTskId;                 /* system task to use */
#endif

#else /* SS_MULTIPLE_PROCS */

#ifdef ANSI
PUBLIC S16 SAttachTTsk
(
ProcId proc,                    /* processor */
Ent ent,                        /* entity ID of the task */
Inst inst,                      /* instance ID of the task */
SSTskId sTskId                  /* system task to use */
)
#else
PUBLIC S16 SAttachTTsk(proc, ent, inst, sTskId)
ProcId proc;                    /* processor */
Ent ent;                        /* entity ID of the task */
Inst inst;                      /* instance ID of the task */
SSTskId sTskId;                 /* system task to use */
#endif

#endif /* SS_MULTIPLE_PROCS */
{

   TRC1(SAttachTTsk)

   RETVALUE(ROK);
}

/*
*
*       Fun:   Detach TAPA task
*
*       Desc:  This function is used to detach a TAPA task from a
*              system task. The system task will stop executing
*              the TAPA task.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_ptsp.c
*
*/
/* procId added */ 
#ifndef SS_MULTIPLE_PROCS

#ifdef ANSI
PUBLIC S16 SDetachTTsk
(
Ent ent,                        /* entity ID of the task */
Inst inst                       /* instance ID of the task */
)
#else
PUBLIC S16 SDetachTTsk(ent, inst)
Ent ent;                        /* entity ID of the task */
Inst inst;                      /* instance ID of the task */
#endif

#else /* SS_MULTIPLE_PROCS */

#ifdef ANSI
PUBLIC S16 SDetachTTsk
(
ProcId proc,                    /* processor */
Ent ent,                        /* entity ID of the task */
Inst inst                       /* instance ID of the task */
)
#else
PUBLIC S16 SDetachTTsk(proc, ent, inst)
ProcId proc;                    /* processor */
Ent ent;                        /* entity ID of the task */
Inst inst;                      /* instance ID of the task */
#endif

#endif /* SS_MULTIPLE_PROCS */
{
   TRC1(SDetachTTsk)

   RETVALUE(ROK);
}

#ifndef SS_OLD_THREAD
/*
*
*       Fun:  SThreadYield 
*
*       Desc:  This function defers thread exection to any other ready
*              thread.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed
*
*       Notes:
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SThreadYield
(
void
)
#else
PUBLIC S16 SThreadYield()
#endif
{
   TRC0(SThreadYield)

   RETVALUE(ROK);
}
#else /* SS_OLD_THREAD */
/*
*
*       Fun:  SThreadYield 
*
*       Desc:  This function defers thread exection to any other ready
*              thread.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed
*
*       Notes:
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC INLINE Void SThreadYield
(
void
)
#else
PUBLIC INLINE Void SThreadYield()
#endif
{
   TRC01(SThreadYield)

   RETVOID;
}
#endif /* SS_OLD_THREAD */

/*
*
*       Fun:   Initialize the lock
*
*       Desc:  This function is used to Initialize the locks. 
*              This function returns the lock id which used by the
*              protocol layers to lock and unlock a thread.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SInitLock
(
SLockId *lock,                  /* Lock Id */
U8       type                   /* Type of the lock */
)
#else
PUBLIC S16 SInitLock(lock, type)
SLockId *lock;                  /* Lock Id */
U8       type;                  /* Type of the lock */
#endif
{
   TRC1(SInitLock)

   RETVALUE(ROK);
} /* SInitLock */


/*
*
*       Fun:   System service lock call
*
*       Desc:  This function is used to lock a thread for the lock id
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SLock
(
SLockId *lock                   /* Lock Id */
)
#else
PUBLIC S16 SLock(lock)
SLockId *lock;                  /* Lock Id */
#endif
{
   TRC1(SLock)

   RETVALUE(ROK);
} /* SLock */

/*
*
*       Fun:   System services Unlock call
*
*       Desc:  This function is used to Unlock the thread for the 
*              lock id given in the parameter.                  
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SUnlock
(
SLockId *lock                   /* Lock Id */
)
#else
PUBLIC S16 SUnlock(lock)
SLockId *lock;                  /* Lock Id */
#endif
{
   TRC1(SUnlock)

   RETVALUE(ROK);
} /* SUnlock */

/*
*
*       Fun:   System services Destroy call
*
*       Desc:  This function is used to destroy the locks.       
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SDestroyLock
(
SLockId *lock                   /* Lock Id */
)
#else
PUBLIC S16 SDestroyLock(lock)
SLockId *lock;                  /* Lock Id */
#endif
{
   TRC1(SDestroyLock)

   RETVALUE(ROK);
} /* SDestroyLock */

/*
*
*       Fun:   Initialize the semaphore 
*
*       Desc:  This function is used to Initialize the semaphore 
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SInitSemaphore
(
SsSemaId *sem,                  /* semaphore id */
U8       value                  /* value  of the semaphore */
)
#else
PUBLIC S16 SInitSemaphore(sem, value)
SsSemaId *sem;                  /* semaphore id */
U8       value;                 /* value of the semaphore */
#endif
{
   TRC1(SInitSemaphore)

   RETVALUE(ROK);
} /* SInitSemaphore */

/*
*
*       Fun:   Wait for the semaphore call
*
*       Desc:  This functions is used to suspend a thread for the 
*              semaphore id untill the same semaphore is posted a 
*              a signal from other threads. 
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SWaitSemaphore
(
SsSemaId *sem                   /* semaphore id */
)
#else
PUBLIC S16 SWaitSemaphore(sem)
SsSemaId *sem;                  /* semaphore id */
#endif
{
   TRC1(SWaitSemaphore)

   RETVALUE(ROK);
} /* SWaitSemaphore */

/*
*
*       Fun:   Post a signal to the semaphore
*
*       Desc:  This function is used to post a signal for the semaphore
*              id given in the argument.                        
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SPostSemaphore
(
SsSemaId *sem                   /* semaphore id */
)
#else
PUBLIC S16 SPostSemaphore(sem)
SsSemaId *sem;                  /* semaphore Id */
#endif
{
   TRC1(SPostSemaphore)

   RETVALUE(ROK);
} /* SPostSemaphore */

/*
*
*       Fun:   Destroy the semaphore 
*
*       Desc:  This function is used to destroy the semaphore.   
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SDestroySemaphore
(
SsSemaId *sem                   /* semaphore id */
)
#else
PUBLIC S16 SDestroySemaphore(sem)
SsSemaId *sem;                  /* semaphore id */
#endif
{
   TRC1(SDestroySemaphore)

   RETVALUE(ROK);
} /* SDestroySemaphore */


/* new SSI function added */ 
#ifdef SS_MULTIPLE_PROCS
/*
*
*       Fun:   Add processor ids to list 
*
*       Desc:  This function is used to add processor ids to the list 
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SAddProcIdLst
(
U16 numPIds,
ProcId *pIdLst
)
#else
PUBLIC S16 SAddProcIdLst(numPIds, pIdLst)
U16 numPIds;          /* number of pids */
ProcId *pIdLst;       /* list of proc ids */
#endif
{
   TRC1(SAddProcIdLst)

   RETVALUE(ROK);
} /* SAddProcIdLst */


/*
*
*       Fun:   Remove processor ids from the list 
*
*       Desc:  This function is used to removes processor ids frim the list 
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SRemProcIdLst
(
U16 numPIds,
ProcId *pIdLst
)
#else
PUBLIC S16 SRemProcIdLst(numPIds, pIdLst)
U16 numPIds;          /* number of pids */
ProcId *pIdLst;       /* list of proc ids */
#endif
{
   TRC1(SRemProcIdLst)

   RETVALUE(ROK);
} /* SAddProcIdLst */


/*
*
*       Fun:   get processor ids from the list 
*
*       Desc:  This function is used to retrieve processor ids from the list 
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetProcIdLst
(
U16 *numPIds,
ProcId *pIdLst
)
#else
PUBLIC S16 SGetProcIdLst(numPIds, pIdLst)
U16 *numPIds;          /* number of pids */
ProcId *pIdLst;       /* list of proc ids */
#endif
{
   TRC1(SGetProcIdLst)

   RETVALUE(ROK);
} /* SGetProcIdLst */


/*
*
*       Fun:   get protocol control block 
*
*       Desc:  This function is used to retrieve protocol control block 
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_ptsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetXxCb
(
ProcId proc, 
Ent    ent, 
Inst   inst, 
Void **xxCb
)
#else
PUBLIC S16 SGetXxCb(proc, ent, inst, xxCb)
ProcId proc; 
Ent    ent; 
Inst   inst;
Void **xxCb;
#endif
{
   TRC1(SGetXxCb)

   RETVALUE(ROK);
} /* SGetXxCb */

#endif /* SS_MULTIPLE_PROCS */

/* ss_ptsp_c_001.main_54 */
/*
*
*       Fun:   Get SGetSystemTsk
*
*       Desc:  This function is used to Get sytem task id
*
*       Ret:   task id
*
*       Notes:
*
*       File:  ss_ptsp.c
*
--*/
#ifdef ANSI
PUBLIC U32 SGetSystemTsk
(
Void
)
#else
PUBLIC U32 SGetSystemTsk()
#endif
{
   TRC1(SGetSystemTsk);
   /* ss_ptsp_c_001.main_55 putting dummy impl */
   RETVALUE(ROK);

} /* end of SGetSystemTsk */

/* ss_ptsp_c_001.main_56: Added SGetTimeStamp */
/*
*
*       Fun:   SGetTimeStamp
*
*       Desc:  This function is used to Get time stamp
*
*       Ret:   ROK      - OK
*              RFAILED  - error
*
*       Notes:
*
*       File:  ss_ptsp.c
*
--*/
#ifdef ANSI
PUBLIC S16 SGetTimeStamp
(
S8    *ts /* A char array to hold the time stamp */
)
#else
PUBLIC S16 SGetTimeStamp(ts)
S8    *ts;
#endif
{
   TRC1(SGetTimeStamp);
   /* ss_ptsp_c_001.main_56:  putting dummy impl */
   RETVALUE(ROK);

} /* end of SGetTimeStamp*/


/*
*
*       Fun:   Register a Call back function 
*
*       Desc:  This function is used to register a call back function,
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes:
*
*       File:  ss_ptsp.c
*
*/
/* ss_ptsp_c_001.main_59:  putting dummy SRegCbTsk */
#ifndef SS_MULTIPLE_PROCS
#ifdef ANSI
PUBLIC S16 SRegCbTsk 
(
Ent ent,                        /* entity */
Inst inst,                       /* instance */
ActvTsk cbTsk 
)
#else
PUBLIC S16 SRegCbTsk(ent, inst, cbTsk)
Ent ent;                        /* entity */
Inst inst;                      /* instance */
ActvTsk cbTsk;
#endif

#else /* SS_MULTIPLE_PROCS */

#ifdef ANSI
PUBLIC S16 SRegCbTsk 
(
ProcId proc,                    /* processor */
Ent ent,                        /* entity */
Inst inst,                       /* instance */
ActvTsk cbTsk 
)
#else
PUBLIC S16 SRegCbTsk(proc, ent, inst, cbTsk)
ProcId proc;                    /* processor */
Ent ent;                        /* entity */
Inst inst;                      /* instance */
ActvTsk cbTsk;
#endif
#endif /* SS_MULTIPLE_PROCS */
{
   TRC1(SRegCbTsk);

   RETVALUE(ROK);
} /* end of SGetTimeStamp*/

/* ss_ptsp_c_001.main_60:  Gaurding functions under SS_LOCK_SUPPORT */
#ifdef SS_LOCK_SUPPORT
/*
*
*       Fun:   SLockNew 
*
*       Desc:  This function is used to aquire the read write lock
*
*       Ret:   ROK   OK
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 SLockNew 
(
SLockInfo *lockId,
U8         lockType

)
#else
PUBLIC S16 SLockNew(lockId, lockType)
SLockInfo *lockId;
U8         lockType;
#endif
{
  TRC1(SLockNew);

  RETVALUE(ROK);
}

/*
*
*       Fun:   SInitLockNew 
*
*       Desc:  This function is used to aquire the read write lock
*
*       Ret:   ROK   OK
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 SInitLockNew 
(
SLockInfo *lockId,
U8         lockType
)
#else
PUBLIC S16 SInitLockNew(lockId, lockType)
SLockInfo *lockId;
U8         lockType;
#endif
{
  TRC1(SInitLockNew);
  RETVALUE(ROK);
}

/*
*
*       Fun:   SUnlockNew 
*
*       Desc:  This function is used to Unlock the read write lock 
*
*       Ret:   ROK   OK
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 SUnlockNew 
(
SLockInfo *lockId,
U8         lockType
)
#else
PUBLIC S16 SUnlockNew(lockId, lockType)
SLockInfo *lockId;
U8         lockType;
#endif
{
  TRC1(SUnlockNew);

  RETVALUE(ROK);
}

/*
*
*       Fun:   SDestroyLockNew 
*
*       Desc:  This function is used to destroy the read write lock 
*
*       Ret:   ROK   OK
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 SDestroyLockNew 
(
SLockInfo *lockId,
U8         lockType
)
#else
PUBLIC S16 SDestroyLockNew(lockId, lockType)
SLockInfo *lockId;
U8         lockType;
#endif
{
  TRC1(SDestroyLockNew);
  RETVALUE(ROK);
}

#endif /* SS_LOCK_SUPPORT */
/*
*
*       Fun:   SGetDataFrmMsg
*
*       Desc:  This function copies requested byte of data from a message
*              without modifying the message.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*              RFAILED  - failed, general (optional)
*
*       Notes: index is 0 based and indicates location in message
*
*              if index is less than the length of the message:
*              message is unchanged and data is examined at specified
*              index and returned via pointer to data. message length
*              is unchanged. return is ok.
*
*              if index is greater than or equal to
*              the length of the message: message is unchanged and 0
*              is returned via pointer to data. return is ok, data
*              not available.
*
*       File:  ss_msg.c
*
*/


#ifdef ANSI
PUBLIC S16 SGetDataFrmMsg 
(
Buffer *mBuf,               /* message buffer */
Data *dataPtr,              /* pointer to data */
MsgLen idx,
MsgLen dataLen
)
#else
PUBLIC S16 SGetDataFrmMsg(mBuf, dataPtr, idx, dataLen)
Buffer *mBuf;               /* message buffer */
Data *dataPtr;              /* pointer to data */
MsgLen idx;                 /* index */
MsgLen dataLen;
#endif
{
   TRC1(SGetDataFrmMsg)
	RETVALUE(ROK);
}



/* ss_ptsp_c_001.main_58: Added SRegCfgTmrMt and  SDeregCfgTmrMt*/
#ifndef SS_MULTIPLE_PROCS
#ifdef SS_MT_TMR
/*
*
*       Fun:   SRegCfgTmrMt
*
*       Desc:  This function is used to Register a timer in MT environment
*
*       Ret:   ROK      - OK
*              RFAILED  - error
*
*       Notes:
*
*       File:  ss_ptsp.c
*
--*/
#ifdef ANSI
PUBLIC S16 SRegCfgTmrMt
(
Ent ent,                    /* entity */
Inst inst,                  /* instance */
S16 period,                 /* period */
S16 units,                  /* period units */
PAIFTMRS16 tmrFnctMt        /* timer function, typically xxActvTmr */
)
#else
PUBLIC S16 SRegCfgTmrMt(ent, inst, period, units, tmrFnctMt)
Ent ent;                    /* entity */
Inst inst;                  /* instance */
S16 period;                 /* period */
S16 units;                  /* period units*/
PAIFTMRS16 tmrFnctMt;       /* timer function, typically xxActvTmr */
#endif
{
   TRC1(SRegCfgTmrMt);
   /* ss_ptsp_c_001.main_58:  putting dummy impl */
   RETVALUE(ROK);

} /* end of SRegCfgTmrMt*/

/*
*
*       Fun:   SDeregCfgTmrMt
*
*       Desc:  This function is used to De-Register a timer in MT environment
*
*       Ret:   ROK      - OK
*              RFAILED  - error
*
*       Notes:
*
*       File:  ss_ptsp.c
*
--*/
#ifdef ANSI
PUBLIC S16 SDeregCfgTmrMt
(
Ent ent,                    /* entity */
Inst inst,                  /* instance */
S16 period,                 /* period */
S16 units,                  /* period units */
PAIFTMRS16 tmrFnctMt        /* timer function */
)
#else
PUBLIC S16 SDeregCfgTmrMt(ent, inst, period, units, tmrFnctMt)
Ent ent;                    /* entity */
Inst inst;                  /* instance */
S16 period;                 /* period */
S16 units;                  /* period units*/
PAIFTMRS16 tmrFnctMt;       /* timer function */

#endif
{
   TRC1(SDeregCfgTmrMt);
   /* ss_ptsp_c_001.main_58:  putting dummy impl */
   RETVALUE(ROK);

} /* end of SDeregCfgTmrMt*/
#endif /* ifdef SS_MT_TMR */
#endif /* ifndef SS_MULTIPLE_PROCS */
/* ss_ptsp_c_001.main_61 : Added new buffer management APIs */
/*
 * 
 *       Fun:   SCpyPartMsg
 *
 *       Desc:  This function is used to copy a portion of message(srcBuf) into
 *              another msg(dstBuf)
 *
 *       Ret:   ROK      - ok
 *              RFAILED  - failed, general (optional)
 *              ROUTRES  - failed, out of resources (optional) - In this case
 *                         caller shall reclaim the resources allocated for dstBuf.
 *
 *       Notes: None
 *
 *       File:  ss_ptsp.c
 *
 **/
#ifdef ANSI
PUBLIC S16 SCpyPartMsg
(
Buffer *srcBuf,
MsgLen idx,
MsgLen cnt,
Buffer *dstBuf
)
#else
PUBLIC S16 SCpyPartMsg(srcBuf, idx, cnt, dstBuf)
Buffer *srcBuf;
MsgLen idx;
MsgLen cnt;
Buffer *dstBuf;
#endif
{
  TRC2(SCpyPartMsg);
  RETVALUE(ROK);
}
/*
 *
 *      Fun:   SRepPartMsg
 *
 *      Desc:  This function is used to replace a portion of message(mBuf) with the
 *             given data
 *
 *      Ret:   ROK      - ok
 *             RFAILED  - failed, general (optional)
 *
 *      Notes: None
 *
 *      File:  ss_ptsp.c
 *
 **/

#ifdef ANSI
PUBLIC S16 SRepPartMsg
(
Buffer *srcBuf,
MsgLen idx,
MsgLen cnt,
Buffer *dstBuf
)
#else
PUBLIC S16 SRepPartMsg(srcBuf, idx, cnt, dstBuf)
Buffer *srcBuf;
MsgLen idx;
MsgLen cnt;
Buffer *dstBuf;
#endif
{
  TRC2(SRepPartMsg);
  RETVALUE(ROK);
}
/*
 *
 *      Fun:   SMovPartMsg
 *
 *      Desc:  This function will move a portion of the first msg to second msg
 *
 *      Ret:   ROK     - ok
 *             ROKDNA  - ok, data not available
 *             RFAILED - failed, general (optional)
 *             ROUTRES - failed, out of resources (optional)
 *
 *      Notes: message 1 is the message from which the segment will be copied 
 *
 *             message 2 is the updated message.
 *
 *             index is 0 based and indicates location in message 1
 *             up to which the data will be copied to message 2 
 *
 *             if index is equal to 0, message 1 will not be changed and no data 
 *             shall be copied to message 2.
 *             message 1 is not returned to memory. return is ok.
 *
 *             if index is not equal to 0 and less than the length of
 *             the message minus 1: data upto index, shall be copied to message 2 
 *             and read/write pointers of message 1 will be updated accordingly              
 *
 *             if index is not equal to 0 and greater than or equal to
 *             the length of the message minus 1: all of the message 1 data.
 *             shall be copied to message 2. return is ok.
 *
 *	      File:  ss_ptsp.c
 *
 **/
#ifdef ANSI
PUBLIC S16 SMovPartMsg
(
Buffer *srcBuf,              /* message 1 */
MsgLen idx,                 /* index */
Buffer *dstBuf              /* message 2 */
)
#else
PUBLIC S16 SMovPartMsg(srcBuf, idx, dstBuf)
  Buffer *srcBuf;              /* message 1 */
  MsgLen idx;                 /* index */
  Buffer *dstBuf;             /* message 2 */
#endif
{
  TRC2(SMovPartMsg);
  RETVALUE(ROK);
}


/* 
 *
 *      Fun:   SPkMsgMult
 *
 *      Desc:  This function copies consecutive bytes of data to the
 *             beginning of a message.
 *
 *      Ret:   ROK      - ok
 *             RFAILED  - failed, general (optional)
 *             ROUTRES  - failed, out of resources (optional)
 *
 *      Notes: if message is empty: data is placed in the message. message
 *             length is incremented. return is ok.
 *
 *             if message is not empty: data is read by source pointer,
 *             data is placed in front of all other data in message.
 *             message length is incremented. return is ok.
 *
 *             the first byte of data pointed to by the source pointer 
 *             will be placed at the front of the message first (i.e. it 
 *             will become the first byte of the message) and the last 
 *             byte will be placed in front of the existing msg contents,
 *             i.e. order of the source is preserved.
 *
 *      File:  ss_ptsp.c
 *
 **/

#ifdef ANSI
PUBLIC S16 SPkMsgMult
(
 Data *src,
 MsgLen cnt,
 Buffer *mBuf
 )
#else
PUBLIC S16 SPkMsgMult(src, cnt, mBuf)
  Data *src;
  MsgLen cnt;
  Buffer *mBuf;
#endif
{

  TRC2(SPkMsgMult)
  RETVALUE(ROK);
}

/* ss_ptsp_c_001.main_62 : added function */
/*
* Get time from epoch in milliseconds
*
*       Fun:   Get time from epoch in milliseconds
*
*       Desc:  This function is used to get the time from epoch in milli seconds.
*              This information may be used for calculating a layer's activation function
*              execution time used for thread profiling.
*
*       Ret:   ROK      - ok
*              RFAILED  - error
*
*       Notes:
*
*       File:  ss_ptsp.c
*/
#ifdef ANSI
PUBLIC S16 SGetEpcTime
(
EpcTime *et           /* date and time */
)
#else
PUBLIC S16 SGetEpcTime(et)
EpcTime *et;          /* date and time */
#endif
{
  TRC2(SGetEpcTime)
  RETVALUE(ROK);
}
/********************************************************************30**
  
         End of file:     ss_ptsp.c@@/main/64 - Thu Nov 24 21:13:43 2011
  
*********************************************************************31*/
  

/********************************************************************40**
  
        Notes:
  
*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/

 
/********************************************************************60**
  
        Revision history:
  
*********************************************************************61*/
  
/********************************************************************70**
  
  version    initials                   description
-----------  ---------  ------------------------------------------------
1.1.0.0         jrl     1. initial release.

1.2.0.0         jrl     1. miscellaneous changes.

1.3.0.0         jrl     1. remove elif to improve portability.

1.4.0.0         jrl     1. add additional functions.

1.5.0.0         jrl     1. add body to pack and unpack functions

1.6.0.0         jrl     1. add return type declarations for pack and
                           unpack functions
                        2. text changes

1.7.0.0         jrl     1. add SSegMsg function to segment messages

1.8.0.0         jrl     1. add SPrntMsg function to print messages
                        2. text changes

1.9.0.0         jrl     1. add SAddPreMsgMult, SAddPstMsgMult,
                           SRemPreMsgMult, SRemPstMsgMult functions
                        2. correct mBuf2 declaration in SSegMsg prototype

1.10            jrl     1. add SCompress, SCpyMsgMsg, SRegPTsk, SInitSema,
                           SRelSema, SGetSema functions
                jrl     2. text changes
                jrl     2. replace TRC1 and TRC0 with TRC2
                jrl     3. trillium development system checkpoint (dvs)
                           at version: 1.9.0.0

1.11            jrl     1. text changes
                        2. add ANSI function declarations
                        3. add SExamQueue, SAddQueue, SRmvQueue functions
                        4. add envopt.h include file

1.12            nkk     1. change SRmvQueue to SRemQueue

1.13            jrl     1. add cast S16 to SUnpkS16, add cast S32 to
                           SUnpkS32 and remove cast S32 from SUnpkU32
                        2. change typedef Data to Txt in SPrint

1.14            nkk     1. change typedef Data to Txt in SPrint when 
                           ifdef ANSI

*********************************************************************71*/

/********************************************************************80**

  version    pat  init                   description
----------- ----- ----  ------------------------------------------------
1.15         ---  jrl   1. text changes

1.16         ---  jrl   1. add S16 in declaration of SPrint

1.17         ---  jrl   1. add SDisplay function

1.18         ---  jrl   1. text changes

1.19         ---  nkk   1. change U8 to Data for SAddSSetIntPend and 
                           SRemSSetIntPend calls

1.20         ---  mc    1. cast U16 for PutHiByte and PutLoByte.

1.21         ---  nkk   1. rename ent to dstEnt and inst to dstInst
                           for SPostTsk
             ---  nkk   2. add SPstTsk for future use

1.22         ---  jrl   1. text changes
             ---  nkk   2. add SSetEntInst and SGetEntInst
             ---  jrl   3. text changes
             ---  jrl   4. add SGetPstMsgMult

1.23         ---  jrl   1. add SRegActvTsk
             ---  jrl   2. change parameters to use Pst for SPstTsk

1.24         ---  nkk   1. correct SRegActvTsk by removing procId
             ---  nkk   2. change return to RETVALUE

1.25         ---  jrl   1. change ss_??.[hx] to ssi.[hx]

1.26         ---  fmg   1. add SRegDrvr and SPstTsk functions

1.27         ---  jrl   1. add SSINT2

1.28         ---  jrl   1. add RETVALUE for SRegDrvrTsk

1.29         ---  fmg   1. added support for system service functions
                           that provide needed functionality to drivers.

1.30         ---  fmg   1. fixed syntax errors in ANSI parameter lists

1.31         ---  fmg   1. removed FCSPKINT code.

1.32         ---  fmg   1. added SSetIntProc, SChkMsg
             ---  fmg   2. Added INLINE declaration for compilers that
                           can use it.
1.33         ---  fmg   1. fixed places where INLINE replaced S16 instead
                           if preceded it.

1.34         ---   mc   1. corrected typo in SUpdMsg in K&R declaration.

1.35         ---   ks   1. added INLINE to functions SDequeueLast, SEnbInt
                           and SDisInt

1.36         ---   fmg  1. fixed parameters for SRegDrvrTsk

1.37         ---   fmg  1. commented out token at end of endif

1.38         ---   mb   1. add SLogError and SDeregTmr functions

1.39         ---   mjp  1. Fixed parameters in SLogError

1.40         ---   kr   1. added two new routines "SPutIsrDpr" and 
                           "SSyncInt" for system services on WINNT.

1.41         ---   rg   1. removes unused variables in SPk* and SUnpk*
                           functions to remove compiler warnings.
             ---   mb   2. Added SAddMsgRef.

1.42         ---   mb   1. Removed SSINT

1.43         ---   mb   1. Removed SInitSema, SRelSema, SGetSema

1.44         ---   mb   1. Defines SSetProcId.

1.45         ---   ada  1. Added defines for MTSS.

*********************************************************************81*/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.46         ---      bbk  1. Changed copyright header date.
  
1.47         ---      tej  1. Change in header

/main/39        ---      jjn  1. Added the following functions:
                           SAlignDBuf, SGetBufRegion,
                           SSetAehDpr, SRegRtrTsk, SDeregRtrTsk, 
                           SRegTTsk, SDeregTTsk, SCreateSTsk, 
                           SDestroySTsk, SAttachTTsk, SDetachTTsk. 

/main/40        ---      ssk  1. Added the following functions:
                           SInitLock, SDestroyLock,
                           SLock, SUnlock, SInitSemaphore, 
                           SDestroySemaphore, SWaitSemaphore, SPostSemaphore.
/main/42     ---     jjn  2. Added SRemoveAehDpr. 

/main/42     ---     ash  1. Removed hidden syntax error just before
                           SRegRtrTsk function
/main/43     ---      cv  1. Updated comments between ANSI-nonANSI pars in 
                             fns SDeregTmr, and SRegActvTsk
                          2. Fixed mismatch in non ANSI par list for fn
                             SGetThread
/main/44     ---      dvs  1. ClearCase release
/main/45     ---      cvp  1. Changed the copyright header date.
/main/46     ---      bjp  1. Added SSwapMsg
/main/47     ---      bjp  1. Modification for MPC8260 Release 2.1
/main/49     ---      jie  1. Added SGetRefTime function prototype.
/main/50     ---      bjp  1. Added SThreadYield
/main/51     ---      bjp  1. 1ms Timer related changes
/main/52     ---      kkj  1. Multiple proc ids support added
/main/53     ---      kkj  1. Multiple proc ids support corrected 
/main/54     ---      st   1. Update for MAP Release 2.3
/main/55     ---      rer  1. Added SGetSystemTsk(ss_ptsp_c_001.main_54)
/main/56     ---      rer  1. corrected SGetSystemTsk(ss_ptsp_c_001.main_55)
/main/57     ---      ve   1. Added SGetTimeStamp(ss_ptsp_c_001.main_56)
/main/58     ---      bn   1. Added SDeregDrvrTsk(ss_ptsp_c_001.main_57)
/main/59     ---      rer  1. Added SRegCfgTmrMt and SDeregCfgTmrMt
                              (ss_ptsp_c_001.main_58)
/main/60     ---      rss  1. putting dummy SRegCbTsk 
                              (ss_ptsp_c_001.main_59)
/main/61     ---      rss  1. Gaurding Lock functions under the flag SS_LOCK_SUPPORT
                              (ss_ptsp_c_001.main_60)
/main/62     ---      vsrao 1.Added new buffer management APIs
                              (ss_ptsp_c_001.main_61)
/main/63     ---      ap     1.Added function definition for SGetEpcTime
                               (ss_ptsp_c_001.main_62)
/main/64     ---  vvashishth 1. Added functions for packing and unpacking of
                                Float32 and Float64 (ss_ptsp_c_001.main_63). 
*********************************************************************91*/
