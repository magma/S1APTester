

/********************************************************************20**
  
     Name:     system services interface
  
     Type:     C include file
  
     Desc:     Structures, variables and typedefs required by the
               System Services service user.
  
     File:     ssi.x
  
     Sid:      ssi.x@@/main/71 - Thu Feb 16 17:43:25 2012
  
     Prg:      nkk
  
*********************************************************************21*/
  
#ifndef __SSIX__
#define __SSIX__
  
  
/*
*     The structures and variables declared in this file
*     correspond to structures and variables used by
*     the following TRILLIUM software:
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
*     1000005     Data Link Layer - LAPB & LAPD
*     1000006     Network Layer - X.25 Intermediate System
*     1000007     Network Layer - X.25 End System
*     1000008     Network Layer - X.75
*     1000009     Network Layer - Q.930/Q.931
*     1000010     Application Layer - Asynchronous PAD
*     1000011     Multiprocessor Operating System (MOS)
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


#ifdef __cplusplus
extern "C" {
#endif


   
/* typedefs */

typedef S16 Status;               /* status */

typedef U32 Ticks;                /* system clock ticks */

#ifdef LONG_MSG
typedef S32 MsgLen;               /* message length */
#else
typedef S16 MsgLen;               /* message length */
#endif

typedef S16 Order;                /* message or queue order */

#ifdef DOS
typedef U16 Size;                 /* size (for number of bytes per region or per s-pool) */
#else
typedef U32 Size;                 /* size (for number of bytes per region or per s-pool) */
typedef S32 PtrOff;               /* signed pointer offset */
#endif

typedef U32 QLen;                 /* queue length */

typedef QLen BufQLen;             /* buffer queue length */

typedef S16 RegSize;              /* region size (for number of regions per processor) */

typedef S16 DPoolSize;            /* dynamic pool size (for number of buffers per d-pool) */

typedef U16 Random;               /* random number */

typedef S16 Seq;                  /* sequence */
/* ssi_x_001.main_64 Additions */
typedef U32 CoreId;               /* core id */

/* Error */
typedef U32 ErrCls;               /* Error Class */

typedef U32 ErrCode;              /* Error Code  */

typedef U32 ErrVal;               /* Error Value */

typedef S16 VectNmb;              /* vector number */

typedef S16 Ttype;                /* task type */

typedef S8 Sema;                  /* semaphore */


/* post */


/*
   This section contains specific typedefs, structures and
   prototypes for the following operating systems:

   MOS      - MOSVER
   MOS, v2  - MSVER2
   psos     - PS
   vrtxsa   - VX
   vxworks  - VW
   sslib    - system service library for elvis
   other    - 
 
   The defines PORTVER, MOSVER and MSVER2 are mutually exclusive. The define PORTVER
   must be set in conjunction with the define PS, VX, VW or other.

*/


#ifdef MOSVER                     /* mos version */
/* mos typedefs, structures and prototypes */

/* forward definitions */
 
#ifndef CMFILE_REORG_1
typedef struct ss_buffer Buffer;  /* forward definition - buffer */
#endif
 
typedef struct ss_queue Queue;    /* forward definition - queue */

/* chain */
 
typedef struct chn                /* chain */
{
   Buffer *fwd;                   /* forward */
   Buffer *bck;                   /* backward */
} Chn;
 
typedef Chn Chain;                /* chain */
 
/* queue - typdef'd earlier */

struct ss_queue                   /* queue - typdef'd earlier */
{
   Chn chn;                       /* chain */
   QLen crntSize;                 /* current size */
   QLen maxSize;                  /* maximum size */
};
  
/* buffer - typedef'd earlier */
  
struct ss_buffer                  /* buffer - typdef'd earlier */
{
   Chn chn;                       /* chain */
   Mem mem;                       /* memory */
   S8 bufType;                    /* buffer type */
   union {
  
      struct
      {
         MsgLen strtIdx;          /* start index */
         MsgLen endIdx;           /* end index */
         MsgLen size;             /* size */
         Data data[DSIZE];        /* data */
      } dat;                      /* data buffer */
  
      struct
      {
         Queue bq;                /* buffer queue */
         MsgLen msgLen;           /* message length */
         S16 refCnt;              /* reference count */
         Pst pst;                 /* post (optional) */
         U32 wsU32[2];            /* workspace unsigned 32 bit values (optional) */
         U16 wsU16[1];            /* workspace unsigned 16 bit values (optional) */
         U8  wsU8[2];             /* workspace unsigned 8 bit values (optional) */
      } msg;                      /* message buffer */
  
      struct
      {
         Buffer *entry[MAXEXTENT];/* entry */
      } ext;                      /* extension buffer */
 
      struct
      {
         Size size;               /* size */
      } stc;                      /* static buffer */
 
      struct
      {
         MsgLen strtIdx;          /* start index */
         MsgLen endIdx;           /* end index */
         MsgLen size;             /* size */
         Data *data;              /* data pointer */
      } dma;                      /* dma buffer */
 
   } t;
};

EXTERN  S16 msOptInd;
EXTERN  S8  *msOptArg;
EXTERN  Txt **msArgv;
EXTERN  S16 msArgc;

#else 
#ifdef MSVER2                     /* mos version 2 */

/* forward definitions */
#ifndef CMFILE_REORG_1
typedef struct ss_buffer Buffer;  /* forward definition - buffer */
#endif
 
typedef struct sBuf SBuf;         /* forward definition - static buffer */
 
typedef struct ss_queue Queue;    /* forward definition - queue */

/* buffer identifier */

/* dynamic chain (4b ALIGNED) */
 
typedef struct dChn               /* dynamic chain */
{
   Buffer *prev;                  /* previous */
   Buffer *crnt;                  /* current */
   Buffer *next;                  /* next */
} DChn;
 
/* static chain (4b ALIGNED)*/
 
typedef struct sChn               /* static chain */
{
   SBuf *fwd;                     /* forward */
} SChn;
 
/* buffer queue (4b ALIGNED) */
  
typedef struct bufQ               /* buffer queue */
{
   DChn dChn;                     /* dynamic chain */
   BufQLen crntSize;              /* current size */
} BufQ;
/* queue (4b ALIGNED) */
  
struct ss_queue                   /* queue - typdef'd earlier */
{
   DChn dChn;                     /* dynamic chain */
   QLen crntSize;                 /* current size */
};
  
/* 4Byte aligned */
typedef struct ss_dat             /* data buffer */
{
   MsgLen strtIdx;                /* start index (2b) */
   MsgLen endIdx;                 /* end index (2b) */
   MsgLen size;                   /* size (2b) */
   Pool pool;                     /* size (1b); Not used for MOS as of now */
   U8 spare;                      /* spare for alignment (1b) */
   Data data[DSIZE];              /* data (4b) */
} Dat;

/* 4Byte aligned */
typedef struct ss_msg             /* message buffer */
{
   Queue bufQ;                    /* buffer queue */
   Buffer *nxtDBuf;               /* next DBuf */
   MsgLen msgLen;                 /* message length */
   Pool pool;                     /* size (1b); Not used for MOS as of now */
   U8 spare;                      /* spare for alingment */
} Msg;
  
/* buffer - typedef'd earlier */
  
struct ss_buffer                  /* buffer - typedef'd earlier */
{
   DChn dChn;                     /* dynamic chain */
   S8 bufType;                    /* buffer type */
   U8 spare1;                     /* spare for alignment */
   U16 spare2;                    /* spare for alignment */
   union {
      Dat dat;                    /* data buffer */
      Msg msg;                    /* message buffer */
   } t;
};

/* static buffer - typedef'd earlier */
  
struct sBuf                       /* static buffer - typedef'd earlier */
{
   SChn sChn;                     /* static chain */
   Size size;                     /* size */
   S8 bufType;                    /* buffer type */
   U8 spare1;                     /* spare 1 */
   U16 spare2;                    /* spare 2 */
};

EXTERN  S16 msOptInd;
EXTERN  S8  *msOptArg;
EXTERN  Txt **msArgv;
EXTERN  S16 msArgc;

#else
#ifdef PS                         /* psos version */
/* psos typedefs, structures and prototypes */

/* forward definitions */
 
#ifndef CMFILE_REORG_1
typedef struct ss_buffer Buffer;  /* forward definition - buffer */
#endif
 
typedef struct ss_queue Queue;       /* forward definition - queue */

/* chain */
 
typedef struct chn                /* chain */
{
   Buffer *fwd;                   /* forward */
   Buffer *bck;                   /* backward */
} Chn;

/* queue - typdef'd earlier */

struct ss_queue                   /* queue - typdef'd earlier */
{
   Chn chn;                       /* chain */
   QLen crntSize;                 /* current size */
   QLen maxSize;                  /* maximum size */
};

/* buffer - typedef'd earlier */
  
struct ss_buffer                  /* buffer - typedef'd earlier */
{
   Chn chn;                       /* chain */
   Mem mem;                       /* memory */
   S8 bufType;                    /* buffer type */
   union {
  
      struct
      {
         MsgLen strtIdx;          /* start index */
         MsgLen endIdx;           /* end index */
         MsgLen size;             /* size */
         Data data[DSIZE];        /* data */
      } dat;                      /* data buffer */
  
      struct
      {
         Queue bq;                /* buffer queue */
         MsgLen msgLen;           /* message length */
         S16 refCnt;              /* reference count */
      } msg;                      /* message buffer */
  
      struct
      {
         Buffer *entry[MAXEXTENT];/* entry */
      } ext;                      /* extension buffer */
 
      struct
      {
         Size size;               /* size */
      } stc;                      /* static buffer */

      struct
      {
         MsgLen strtIdx;          /* start index */
         MsgLen endIdx;           /* end index */
         MsgLen size;             /* size */
         Data *data;              /* data pointer */
      } dma;                      /* dma buffer */
 
   } t;
};

#else
#ifdef VX                         /* vrtxsa version */
/* vrtxsa typedefs, structures and prototypes */

/* forward definitions */
 
#ifndef CMFILE_REORG_1
typedef struct ss_buffer Buffer;  /* forward definition - buffer */
#endif
 
typedef struct ss_queue Queue;       /* forward definition - queue */

/* buffer - typedef'd earlier */

struct ss_buffer                  /* buffer - typedef'd earlier */
{
   Buffer *fwd;                   /* forward chain pointer for queues */
   Buffer *bck;                   /* backward chain pointer for queues */
   U16 mPid;                      /* VRTXsa memory partition ID */
   S16 start;                     /* starting index of message in byte array */
   S16 end;                       /* ending index of message in byte array */
   U16 status;                    /* buffer status */
};

/* chain */
 
typedef struct chn                /* chain */
{
   Buffer *fwd;                   /* forward */
   Buffer *bck;                   /* backward */
} Chn;

/* queue - typdef'd earlier */
 
struct ss_queue                   /* queue - typdef'd earlier */
{
   Chn chn;                       /* chain */
   QLen crntSize;                 /* current size */
   QLen maxSize;                  /* maximum size */
};

#else
#ifdef VW                         /* vxworks version */
/* vxworks typedefs, structures and prototypes */

/* forward definitions */
 
#ifndef CMFILE_REORG_1
typedef struct ss_buffer Buffer;  /* forward definition - buffer */
#endif
 
typedef struct ss_queue Queue;    /* forward definition - queue */

typedef struct dChn               /* dynamic chain */
{
   Buffer *prev;                    /* previous */
   Buffer *crnt;                    /* current */
   Buffer *next;                    /* next */
} DChn;
 
/* static chain (4b ALIGNED)*/
 
/* buffer queue (4b ALIGNED) */
  
typedef struct bufQ               /* buffer queue */
{
   DChn dChn;                     /* dynamic chain */
   BufQLen crntSize;              /* current size */
} BufQ;
  
/* queue (4b ALIGNED) */
  
struct ss_queue                   /* queue - typdef'd earlier */
{
   DChn dChn;                     /* dynamic chain */
   QLen crntSize;                 /* current size */
};
  
typedef struct ss_dat             /* data buffer */
{
   MsgLen strtIdx;                /* start index */
   MsgLen endIdx;                 /* end index */
   MsgLen size;                   /* size */
   Pool pool;                     /* pool id */
   U8 spare;                      /* spare */
   Data *data;                    /* data */
} Dat;

typedef struct ss_msg             /* message buffer */
{
   Queue bufQ;                    /* buffer queue */
   Buffer *nxtDBuf;               /* next DBuf */
   MsgLen msgLen;                 /* message length */
   Pool pool;                     /* pool id */
   U8 spare;                      /* spare */
} Msg;
  
/* buffer - typedef'd earlier */
  
struct ss_buffer                  /* buffer - typedef'd earlier */
{
   DChn dChn;                     /* dynamic chain */
   S8 bufType;                    /* buffer type */
   U8 spare1;                     /* spare for alignment */
   U16 spare2;                    /* spare for alignment */
   union {
      Dat dat;                    /* data buffer */
      Msg msg;                    /* message buffer */
   } t;
};

#else
#ifdef SSLIB                      /* system service library */
/* forward definitions */
#ifndef CMFILE_REORG_1
typedef struct ss_buffer Buffer;  /* forward definition - buffer */
#endif
 
typedef struct sBuf SBuf;         /* forward definition - static buffer */
 
typedef struct ss_queue Queue;    /* forward definition - queue */


/* queue - typdef'd earlier */
 
struct ss_queue                   /* queue - typdef'd earlier */
{
   S16 dummy;                     /* dummy placeholder */
};

/* buffer - typedef'd earlier */
  
struct ss_buffer                  /* buffer - typedef'd earlier */
{
   S32 sIdx;                      /* start index */
   S32 len;                       /* buffer length */
   S8 dat[MAXBUFSIZ];             /* data */
};

#else                             /* portable/other version */
#ifdef SSRYLIB                      /* system service library */
/* forward definitions */
#ifndef CMFILE_REORG_1
typedef struct ss_buffer Buffer;  /* forward definition - buffer */
#endif
 
typedef struct sBuf SBuf;         /* forward definition - static buffer */
 
typedef struct ss_queue Queue;    /* forward definition - queue */

 
typedef S16 RyBufId;
/* dynamic chain (aligned) */
typedef struct ryDChn                 /* dynamic chain */
{
   RyBufId back;                      /* backward (2b) */
   RyBufId crnt;                      /* current  (2b) */
   RyBufId next;                      /* next     (2b) */
   RyBufId pad;                       /* pad      (2b) */
} RyDChn;
/* 
 * queue - typdef'd earlier 
 * This is exactly same as RyBufQ
 */
struct ss_queue                   /* queue - typdef'd earlier */
{
   RyDChn dChn;
   QLen crntSize;                 /* current size */
   U16  ryChanId;                 /* relay channel Id */
};

/* buffer - typedef'd earlier */
  
struct ss_buffer                  /* buffer - typedef'd earlier */
{
   S32 sIdx;                      /* start index */
   S32 len;                       /* buffer length */
   S8 dat[MAXBUFSIZ];             /* data */
};

#else                             /* portable/other version */
#ifdef WINNT_IATM                 /* Windows NT Integrated ATM */

#ifndef CMFILE_REORG_1
#ifndef CFG_APP                   /* Don't include ndis.h for config app. */ 
#include "ndis.h"                 /* to support NDIS calls (listed above) */
#endif /* CFG_APP */

typedef struct _NDIS_PACKET Buffer; /* forward definition - buffer */

#endif /* CMFILE_REORG_1 */

typedef struct ss_queue Queue;      /* forward definition - queue */

/* Trillium Queue is built upon the NDIS library list functions.
 * No spin locks are applied for queues.
 */

struct ss_queue {
   LIST_ENTRY ListHead;           /* LIST_ENTRY to support NDIS list calls */
   QLen CurQLen;                  /* current queue length */
   QLen MaxQLen;                  /* maximum queue length */
};
#else  /* WINNT_IATM */
#ifdef MT                         /* multi-threaded version */
/* multi-threaded typedefs, structures and prototypes */

/* forward definitions */
 
#ifndef CMFILE_REORG_1
typedef struct ss_buffer Buffer;  /* forward definition - buffer */
#endif
 
typedef struct ss_queue Queue;    /* forward definition - queue */

typedef struct sBuf      SBuf;    /* forward definition - static buffer */

typedef struct dChn               /* dynamic chain */
{
   Buffer *prev;                    /* previous */
   Buffer *crnt;                    /* current */
   Buffer *next;                    /* next */
} DChn;

/* static chain (4b ALIGNED)*/
typedef struct sChn
{
   SBuf *fwd;                     /* forward */
} SChn;
 
/* static chain (4b ALIGNED)*/
 
/* buffer queue (4b ALIGNED) */
  
/* queue (4b ALIGNED) */
  
struct ss_queue                   /* queue - typdef'd earlier */
{
   DChn dChn;                     /* dynamic chain */
   QLen crntSize;                 /* current size */
};
  
typedef struct ss_dat             /* data buffer */
{
   MsgLen strtIdx;                /* start index */
   MsgLen endIdx;                 /* end index */
   MsgLen size;                   /* size */
   Pool pool;                     /* pool id */
   U8 spare;                      /* spare */
   Data *data;                    /* data */
} Dat;

typedef struct ss_msg             /* message buffer */
{
   Queue bufQ;                    /* buffer queue */
   Buffer *nxtDBuf;               /* next DBuf */
   MsgLen msgLen;                 /* message length */
   Pool pool;                     /* pool id */
   U8 spare;                      /* spare */
} Msg;
  
/* buffer - typedef'd earlier */
  
struct ss_buffer                  /* buffer - typedef'd earlier */
{
   DChn dChn;                     /* dynamic chain */
   S8 bufType;                    /* buffer type */
   U8 spare1;                     /* spare for alignment */
   U16 spare2;                    /* spare for alignment */
   union {
      Dat dat;                    /* data buffer */
      Msg msg;                    /* message buffer */
   } t;
};

/* static buffer - typedef'd earlier */
  
struct sBuf
{
   SChn sChn;                     /* static chain */
   Size size;                     /* size */
   S8 bufType;                    /* buffer type */
   U8 spare1;                     /* spare 1 */
   U16 spare2;                    /* spare 2 */
};

typedef S32 MtRwLockId;
typedef S32 MtSemaId;
typedef S32 MtCondId;
typedef S32 MtMtxId;
typedef S32 MtThrdId;
typedef S32 MtThrdFlags;
typedef S32 MtThrdPrior;

typedef Void *(MtThrd) ARGS((Void *)); 

#else  /* not MT */
#ifdef PORTVER
/* portable typedefs, structures and prototypes */

/* forward definitions */
 
#ifndef CMFILE_REORG_1
typedef struct ss_buffer Buffer;  /* forward definition - buffer */
#endif
 
typedef struct ss_queue Queue;       /* forward definition - queue */

/* queue - typdef'd earlier */
 
struct ss_queue                   /* queue - typdef'd earlier */
{
   S16 dummy;                     /* dummy placeholder */
};
 
/* buffer - typedef'd earlier */
  
struct ss_buffer                  /* buffer - typedef'd earlier */
{
   S16 dummy;                     /* dummy placeholder */
};

/* task related stuff */
/* data range modified */
#ifndef SS_MULTIPLE_PROCS
typedef U8  SSTskId;             /* System Task Id */
#else /* SS_MULTIPLE_PROCS */
typedef U16 SSTskId;             /* System Task Id */
#endif /* SS_MULTIPLE_PROCS */

typedef S32 SSTskPrior;          /* System Task Priority */
#ifdef SS_AEHDPR_SUPPORT
typedef Void (*PISR) ARGS((PTR cxt)); /* pointer to ISR function handler */
typedef Void (*PDPR) ARGS((PTR cxt)); /* pointer to DPR function handler */
#endif /* SS_AEHDPR_SUPPORT */
#else  /* not PORTVER */
#ifdef SS                        /* Common System Services */

/* for SGetOpt() */
EXTERN  S16 msOptInd;
EXTERN  S8  *msOptArg;
EXTERN  Txt **msArgv;
EXTERN  S16 msArgc;

/* task related stuff */
/* data range modified */
#ifndef SS_MULTIPLE_PROCS
typedef U8  SSTskId;             /* System Task Id */
#else /* SS_MULTIPLE_PROCS */
typedef U16 SSTskId;             /* System Task Id */
#endif /* SS_MULTIPLE_PROCS */

typedef S32 SSTskPrior;          /* System Task Priority */

#ifndef CMFILE_REORG_1

/* Buffer type is necessary */
typedef struct ssmsgb Buffer;

#endif /* CMFILE_REORG_1 */

/* message block */
struct ssmsgb
{
   S8                   refCnt;     /* Counter to Free Buff */
   struct ssmsgb        *b_next;     /* next message */
   struct ssmsgb        *b_prev;     /* previous message */
   struct ssmsgb        *b_cont;     /* next message block */
   U8                   *b_rptr;     /* 1st unread data byte of buffer */
   U8                   *b_wptr;     /* 1st unwritten data byte of buffer */
   struct ssdatab       *b_datap;    /* pointer to data block */
};

/* Queue data structure */
typedef struct ssQueue
{
   Buffer *head;                     /* head of queue */
   Buffer *tail;                     /* tail of queue */
   QLen   crntSize;                  /* current szie of queue */

} Queue;


/* Memory CTL operations structure */
typedef struct sMemCtl
{
   U8 op;                           /* operation */

   union
   {
      struct
      {
         Data *vaddr;               /* virtual address */
         Data **paddr;              /* physical address */
      } vtop;

      struct
      {
         Size size;                 /* size */
         Status *status;            /* status */
      } chkres;
   } u;

} SMemCtl;


/* memory management handler function types */
/* ssi_x_001.main_47 - addition for introducing additional parameter memType(static/dynamic) */
/* ssi_x_001.main_57 : Additions */
#ifdef SS_HISTOGRAM_SUPPORT 
#ifdef SSI_DEBUG_LEVEL1
typedef S16 (*SsAlloc) ARGS((Void *, Size *, U32, Data **, U32, U32, U8*, U8, Bool));
#else
typedef S16 (*SsAlloc) ARGS((Void *, Size *, U32, Data **, U32, U8*, U8, Bool));
#endif /* SSI_DEBUG_LEVEL1 */
typedef S16 (*SsFree) ARGS((Void *, Data *, Size, U32, U8*, U8, Bool));
typedef S16 (*SsCtl) ARGS((Void *, Event, SMemCtl *));
#elif defined(SS_LIGHT_MEM_LEAK_STS)
typedef S16 (*SsAlloc) ARGS((Void *, Size *, U32 , Data **, U32, U32 , U8 *));
typedef S16 (*SsFree) ARGS((Void *, Data *, Size, U32, U8 *));
typedef S16 (*SsCtl) ARGS((Void *, Event, SMemCtl *));
#else
#ifdef SSI_DEBUG_LEVEL1
typedef S16 (*SsAlloc) ARGS((Void *, Size *, U32, Data **, U32));
#else
#ifdef T2K_MEM_LEAK_DBG
typedef S16 (*SsAlloc) ARGS((Void *, Size *, U32, Data **,char*, U32));
#else
typedef S16 (*SsAlloc) ARGS((Void *, Size *, U32, Data **));
#endif
#endif /* SSI_DEBUG_LEVEL1 */
#ifdef T2K_MEM_LEAK_DBG
typedef S16 (*SsFree) ARGS((Void *, Data *, Size,char*, U32));
#else
typedef S16 (*SsFree) ARGS((Void *, Data *, Size));
#endif
typedef S16 (*SsCtl) ARGS((Void *, Event, SMemCtl *));
#endif /* SS_HISTOGRAM_SUPPORT */


/* region information structure -- passed to SRegRegion() */
typedef struct sRegInfo
{
   Void         *regCb;            /* region control block pointer */
   U32          flags;             /* region characteristics flags  */
/* ssi_x_001.main_64 Additions */
#ifdef SS_CAVIUM
   cvmx_arena_list_t  regArena;    /* arena for the region */
#endif
   Data         *start;            /* start address of region */
   Size         size;              /* size of region */
   SsAlloc      alloc;             /* allocation function pointer */
   SsFree       free;              /* deallocation function pointer */
   SsCtl        ctl;               /* control request function pointer */

} SRegInfo;


#ifdef SS_OLD_THREAD

/* types for SGetThread(), SGetMutex, etc. */
typedef Void    *(SThrd) ARGS((Void *));

typedef S32     SThrdId;           /* thread Id */
typedef S32     SMtxId;            /* mutex Id */
typedef S32     SCondId;           /* condition Id */

#endif /* SS_OLD_THREAD */

/*ssi_x_001.main_63 ss_dep.x guarded under flag*/
#ifdef SS_CAVIUM
#include "jz_dep.x"
#else
#ifdef SS_4GMX_LCORE
#include "ss_dep.x"
#else
#include "ss_dep.x"
#endif /* SS_4GMX_LCORE */
#endif/*SS_CAVIUM*/

#endif /* SS */
#endif /* PORTVER */
#endif /* MT */
#endif /* WINNT_IATM */
#endif /* SSRYLIB */
#endif /* SSLIB */
#endif /* VW */
#endif /* VX */
#endif /* PS */
#endif /* MSVER2 */
#endif /* MOSVER */
/* ssi_x_001.main_57 : Additions */
#ifdef SS_HISTOGRAM_SUPPORT  
/*
typedef struct entInfo
{
   U8                 entid;
}EntInfo;

typedef struct secondIndex
{
    EntInfo           info[26];
}SecondIndex;

typedef struct firstIndex
{
    SecondIndex       info[26];
}FirstIndex; */
#endif /* SS_HISTOGRAM_SUPPORT */


/* functions */

/* procId and control block added */ 
#ifndef SS_MULTIPLE_PROCS
typedef S16  (*PAIFS16) ARGS((Ent ent,Inst inst,Region region,Reason reason ));
/* ssi_x_001.main_54 */
/* ssi_x_001.main_53 */
/* ssi_x_001.main_69: Removed the SS_MT_TMR guard from PAIFTMRS16
                      timer activation function typedef. */

typedef S16  (*PAIFTMRS16) ARGS((Ent ent, Inst inst));
#else
typedef S16  (*PAIFS16) ARGS((ProcId proc, 
                              Ent ent,
                              Inst inst,
                              Region region,
                              Reason reason,
                              Void **xxCb));

/* time activation function typedef */
typedef S16  (*PAIFTMRS16) ARGS((ProcId proc, 
                                 Ent ent,
                                 Inst inst));
#endif /* SS_MULTIPLE_PROCS */

#ifndef VX
typedef S16  (*PATFS16) ARGS((Prior prior,Route route,Ent ent,Inst inst,Buffer *mBuf));
#else
typedef void  (*PATFS16) ARGS((void *vPtr));
#endif
typedef S16  (*ActvTsk) ARGS((Pst *pst, Buffer *mBuf));
#ifdef ENB_RELAY
typedef struct uProc UProc;  /* forward definition - uproc */
#ifdef RYINT1
typedef void (*ISTsk) ARGS((Inst inst));
#else  /* for backward compatibility */
typedef void (*ISTsk) ARGS((UProc *uProc));
#endif /* RYINT1 */

struct uProc
{
   Inst inst;                         /* instance */
   ProcId low;                        /* procId low value */
   ProcId high;                       /* procId high value */
   ActvTsk actvTsk;                   /* activation function for drvr task */ 
   U16 isFlag;                        /* interrupt service flag */
   ISTsk isTsk;                       /* interrupt service task */
};
 

#endif /* ENB_RELAY */


/* functions */
EXTERN S16 SChekMemUtilization ARGS((Region region,Bool *memAlarm));

EXTERN  Void prntMem ARGS((Data *strtAdr,S16 len));
EXTERN  Void prntMsg ARGS((Buffer *mBuf));
EXTERN  Void prntMsg1 ARGS((Buffer *mBuf,S16 src,S16 dst));
EXTERN  S16 tst ARGS((void ));
EXTERN  S16 rdConQ ARGS((Data data));

EXTERN  S16 SPkS8 ARGS((S8 val,Buffer *mBuf));
EXTERN  S16 SPkU8 ARGS((U8 val,Buffer *mBuf));
EXTERN  S16 SPkS16 ARGS((S16 val,Buffer *mBuf));
EXTERN  S16 SPkU16 ARGS((U16 val,Buffer *mBuf));
EXTERN  S16 SPkS32 ARGS((S32 val,Buffer *mBuf));
EXTERN  S16 SPkU32 ARGS((U32 val,Buffer *mBuf));
/* ssi_x_001.main_49 : added packing of F32 and F64*/
#ifdef SS_FLOAT
EXTERN  S16 SPkF32 ARGS((F32 val,Buffer *mBuf));
EXTERN  S16 SPkF64 ARGS((F64 val,Buffer *mBuf));
#endif /* SS_FLOAT */
EXTERN  S16 SUnpkS8 ARGS((S8 *val,Buffer *mBuf));
EXTERN  S16 SUnpkU8 ARGS((U8 *val,Buffer *mBuf));
EXTERN  S16 SUnpkS16 ARGS((S16 *val,Buffer *mBuf));
EXTERN  S16 SUnpkU16 ARGS((U16 *val,Buffer *mBuf));
EXTERN  S16 SUnpkS32 ARGS((S32 *val,Buffer *mBuf));
EXTERN  S16 SUnpkU32 ARGS((U32 *val,Buffer *mBuf));
/* ssi_x_001.main_49 : added unpacking of F32 and F64*/
#ifdef SS_FLOAT
EXTERN  S16 SUnpkF32 ARGS((F32 *val,Buffer *mBuf));
EXTERN  S16 SUnpkF64 ARGS((F64 *val,Buffer *mBuf));
#endif /* SS_FLOAT */
EXTERN  S16 SPrint ARGS((Txt *buf));
EXTERN  S16 SDisplay ARGS((S16 chan,Txt *buf));
EXTERN  S16 SPrntMsg ARGS((Buffer *mBuf,S16 src,S16 dst));
EXTERN  S16 SInitQueue ARGS((Queue *q));
#ifndef SS_ENABLE_MACROS
EXTERN  S16 SQueueFirst ARGS((Buffer *buf,Queue *q));
EXTERN  S16 SQueueLast ARGS((Buffer *buf,Queue *q));
EXTERN  S16 SDequeueFirst ARGS((Buffer * *bufPtr,Queue *q));
EXTERN  S16 SDequeueLast ARGS((Buffer * *bufPtr,Queue *q));
#endif /* SS_ENABLE_MACROS */
EXTERN  S16 SFlushQueue ARGS((Queue *q));
EXTERN  S16 SCatQueue ARGS((Queue *q1,Queue *q2,Order order));
EXTERN  S16 SFndLenQueue ARGS((Queue *q,QLen *lngPtr));
EXTERN  S16 SExamQueue ARGS((Buffer **bufPtr,Queue *q,QLen idx));
EXTERN  S16 SAddQueue ARGS((Buffer *buf,Queue *q,QLen idx));
EXTERN  S16 SRemQueue ARGS((Buffer **bufPtr,Queue *q,QLen idx));
#ifndef SS_ENABLE_MACROS
#ifdef T2K_MEM_LEAK_DBG
#define SGetDBuf(region,pool,buf) SGetDBufNew(region,pool,buf,__FILE__,__LINE__)
#define SPutDBuf(region,pool,buf) SPutDBufNew(region,pool,buf,file,line)
EXTERN  S16 SGetDBufNew ARGS((Region region,Pool pool,Buffer * *bufPtr,char*,U32));
EXTERN  S16 SPutDBufNew ARGS((Region region,Pool pool,Buffer *buf,char*,U32));
EXTERN  S16 SAttachPtrToBufNew ARGS((Region   region, Pool     pool, Data
         *ptr, MsgLen   totalLen, Buffer** mBuf, char* file, U32 line));
#define SAttachPtrToBuf(region,pool,ptr,totalLen,mBuf) SAttachPtrToBufNew(region,pool,ptr,totalLen,mBuf,__FILE__,__LINE__)
#define SPutZbcDBuf(region,buf) SPutZbcDBufNew(region,buf,__FILE__,__LINE__)
#elif SS_LIGHT_MEM_LEAK_STS
EXTERN  S16 SGetDBufNew ARGS((Region region,Pool pool,Buffer * *bufPtr,U32 line,U8 *fnName));
EXTERN  S16 SPutDBufNew ARGS((Region region,Pool pool,Buffer *buf, U32 line, U8 *fnName));
#else

EXTERN  S16 SGetDBuf ARGS((Region region,Pool pool,Buffer * *bufPtr));
EXTERN  S16 SPutDBuf ARGS((Region region,Pool pool,Buffer *buf));
#endif
#else /* SS_ENABLE_MACROS */
#ifdef T2K_MEM_LEAK_DBG
#define SGetDBuf(region,pool,buf) SGetDBufNew(region,pool,buf,__FILE__,__LINE__)
#define SPutDBuf(region,pool,buf) SPutDBufNew(region,pool,buf,__FILE__,__LINE__)
EXTERN  S16 SGetDBufNew ARGS((Region region,Pool pool,Buffer * *bufPtr,char*,U32));
EXTERN  S16 SPutDBufNew ARGS((Region region,Pool pool,Buffer *buf,char*,U32));
#elif SS_LIGHT_MEM_LEAK_STS
EXTERN  S16 SGetDBufNew ARGS((Region region,Pool pool,Buffer * *bufPtr,U32 line,U8 *fnName));
EXTERN  S16 SPutDBufNew ARGS((Region region,Pool pool,Buffer *buf, U32 line, U8 *fnName));
#else
EXTERN  S16 SGetDBuf ARGS((Region region,Pool pool,Buffer * *bufPtr));
EXTERN  S16 SPutDBuf ARGS((Region region,Pool pool,Buffer *buf));
#endif
#endif /* SS_ENABLE_MACROS */
EXTERN S16 SPutMsgToRegion ARGS((Region region, Buffer *buf));
#ifdef SS_USE_ICC_MEMORY
EXTERN Void *ssGetIccHdl ARGS((Region region));
#endif /* SS_USE_ICC_MEMORY */

/* ssi_x_001.main_57 : Additions */
/* ssi_x_001.main_59 : Added compile time flag */
#ifdef SS_LIGHT_MEM_LEAK_STS
EXTERN  S16 SGetMsgNew ARGS((Region region, Pool pool, Buffer * *mBufPtr, U32 line, U8 *fnName));
EXTERN  S16 SGetSBufNew ARGS((Region region,Pool pool, Data * *bufPtr, Size size, U32 line, U8* fnName));
EXTERN  S16 SPutMsgNew ARGS((Buffer *mBuf, U32 line,  U8 *fnName));
EXTERN  S16 SPutSBufNew ARGS((Region region, Pool pool, Data *buf, Size size, U32 line, U8 *fnName));
#else /*SS_LIGHT_MEM_LEAK_STS */
#ifdef SS_HISTOGRAM_SUPPORT 
EXTERN  S16 SPutMsgNew ARGS((Buffer *mBuf, U32 line,  U8 *fileName));
EXTERN  S16 SGetMsgNew ARGS((Region region, Pool pool, Buffer * *mBufPtr, U32 line,  U8 *fileName));
EXTERN  S16 SGetSBufNew ARGS((Region region,Pool pool, Data * *bufPtr, Size size, U32 line, U8 *fileName));
EXTERN  S16 SPutSBufNew ARGS((Region region, Pool pool, Data *buf, Size size, U32 line, U8 *fileName));
#else
/*ssi_x_001.main_67 : RMIOS specific changes*/
#ifndef SS_RMIOS
#ifdef T2K_MEM_LEAK_DBG
#define SPutMsg(mBuf) SPutMsgNew(mBuf,__FILE__,__LINE__)
#define SGetMsg(region,pool,mBuf) SGetMsgNew(region,pool,mBuf,__FILE__,__LINE__)
EXTERN  S16 SPutMsgNew ARGS((Buffer *mBuf,char*, U32));
EXTERN  S16 SGetMsgNew ARGS((Region region, Pool pool, Buffer * *mBufPtr, char*,U32));
#else
EXTERN  S16 SPutMsg ARGS((Buffer *mBuf));
EXTERN  S16 SGetMsg ARGS((Region region, Pool pool, Buffer * *mBufPtr));
#endif
#else
#define SPutMsg(m) SPutMsgRmi(__FILE__, __LINE__, m)
#define SGetMsg(r, p, m)    SGetMsgRmi(__FILE__, __LINE__, r, p, m)
EXTERN  S16 SPutMsgRmi ARGS((char *file, int line, Buffer *mBuf));
EXTERN  S16 SGetMsgRmi ARGS((char *file, int line, Region region, Pool pool, Buffer * *mBufPtr));
#endif
#if (defined(SSI_STATIC_MEM_LEAK_DETECTION)|| defined(T2K_MEM_LEAK_DBG))
#define SGetSBuf(region,pool,bufPtr,size) SGetSBuf1(region,pool,bufPtr,size,__FILE__,__LINE__)
EXTERN  S16 SGetSBuf1 ARGS((Region region,Pool pool, Data * *bufPtr, Size size, char* file, U32 line));
EXTERN void DumpStaticMemLeakFiles ARGS((void));
EXTERN void DumpT2kMemLeakInfoToFile ARGS((void)); 
#define SPutSBuf(region,pool,buf,size) SPutSBuf1(region,pool,buf,size,__FILE__,__LINE__)
EXTERN  S16 SPutSBuf1 ARGS((Region region, Pool pool, Data *buf, Size size, char*, U32));
#else
EXTERN  S16 SGetSBuf ARGS((Region region,Pool pool, Data * *bufPtr, Size size));
EXTERN  S16 SPutSBuf ARGS((Region region, Pool pool, Data *buf, Size size));
#endif
#endif /* SS_HISTOGRAM_SUPPORT */
#endif /*SS_LIGHT_MEM_LEAK_STS */
#ifdef T2K_MEM_LEAK_DBG
#define SGetStaticBuffer(region,pool,bufPtr,size,memType) SGetStaticBufferNew(region,pool,bufPtr,size,memType,__FILE__,__LINE__)
#define SPutStaticBuffer(region,pool,bufPtr,size,memType) SPutStaticBufferNew(region,pool,bufPtr,size,memType,__FILE__,__LINE__)
EXTERN  S16 SGetStaticBufferNew ARGS((Region region,Pool pool, Data * *bufPtr, Size size, U8 memType,char*,U32));
EXTERN  S16 SPutStaticBufferNew ARGS((Region region, Pool pool, Data *buf, Size size, U8 memType,char*,U32));
#else
EXTERN  S16 SGetStaticBuffer ARGS((Region region,Pool pool, Data * *bufPtr, Size size, U8 memType));
EXTERN  S16 SPutStaticBuffer ARGS((Region region, Pool pool, Data *buf, Size size, U8 memType));
#endif
/* ssi_x_001.main_65: Additions */
#ifdef SS_SEUM_CAVIUM
EXTERN S16 ssInitRcvWork ARGS((void));
EXTERN S16 SConvPtrPhy ARGS(( Buffer  **mBuf));
EXTERN S16 SConvPhyPtr ARGS((Buffer  **workPtr));
EXTERN S16 SCpyFpaMsg ARGS((Buffer *srcBuf, Region dstRegion,Pool dstPool, Buffer **dstBuf));
EXTERN S16 SCpyMsgFpa ARGS(( Buffer *srcBuf, Buffer **dstBuf));
EXTERN S16 SPutFpaMsg ARGS(( Buffer *fpaBuf));
#endif /* SS_SEUM_CAVIUM */

EXTERN  S16 SGetSMem ARGS((Region region,Size size,Pool *poolPtr));
EXTERN  S16 SPutSMem ARGS((Region region,Pool pool));
EXTERN  S16 SInitMsg ARGS((Buffer *mBuf));
EXTERN  S16 SAddPreMsg ARGS((Data data,Buffer *mBuf));
EXTERN  S16 SAddPstMsg ARGS((Data data,Buffer *mBuf));
/* ssi_x_001.main_70 - Added prototype for SAddPreMsgMultInOrder */
EXTERN  S16 SAddPreMsgMultInOrder ARGS((Data *src,MsgLen cnt,Buffer *mBuf));
EXTERN  S16 SRemPreMsg ARGS((Data *dataPtr,Buffer *mBuf));
EXTERN  S16 SRemPreMsgRegion ARGS((Region region, Data *dataPtr,Buffer *mBuf));
EXTERN  S16 SCatMsgRegion ARGS((Region region, Buffer *mBuf1,Buffer *mBuf2,Order order));
EXTERN  S16 SSegMsgRegion ARGS((Region region, Buffer *mBuf1,MsgLen idx,Buffer **mBuf2));
EXTERN  int SCreatePThread ARGS((pthread_t* tid, pthread_attr_t* attr, void *(*start_routine) (void *), void* arg));
EXTERN  S16 SRemPstMsg ARGS((Data *dataPtr,Buffer *mBuf));
#ifdef T2K_MEM_LEAK_DBG
#define SAddPreMsgMult(src, cnt, mBuf) SAddPreMsgMult1(src, cnt, mBuf, __FILE__,__LINE__)
#define SAddPstMsgMult(src, cnt, mBuf) SAddPstMsgMult1(src, cnt, mBuf, __FILE__,__LINE__)

EXTERN  S16 SAddPreMsgMult1 ARGS((Data *src,MsgLen cnt,Buffer *mBuf, char *file, U32 line));
EXTERN  S16 SAddPstMsgMult1 ARGS((Data *src,MsgLen cnt,Buffer *mBuf, char *file, U32 line));
#else
EXTERN  S16 SAddPreMsgMult ARGS((Data *src,MsgLen cnt,Buffer *mBuf));
EXTERN  S16 SAddPstMsgMult ARGS((Data *src,MsgLen cnt,Buffer *mBuf));
#endif
EXTERN  S16 SGetPstMsgMult ARGS((MsgLen cnt,Buffer *mBuf));
EXTERN  S16 SRemPreMsgMult ARGS((Data *dst,MsgLen cnt,Buffer *mBuf));
EXTERN  S16 SRemPstMsgMult ARGS((Data *dst,MsgLen cnt,Buffer *mBuf));
EXTERN  S16 SRepMsg ARGS((Data data,Buffer *mBuf,MsgLen idx));
EXTERN  S16 SExamMsg ARGS((Data *dataPtr,Buffer *mBuf,MsgLen idx));
/*ssi_x_001.main_60 */
EXTERN S16 SGetDataFrmMsg ARGS ((Buffer *mBuf, Data *dataPtr, MsgLen idx, MsgLen dataLen));
EXTERN  S16 SFndLenMsg ARGS((Buffer *mBuf,MsgLen *lngPtr));
EXTERN  S16 SCatMsg ARGS((Buffer *mBuf1,Buffer *mBuf2,Order order));
#ifdef T2K_MEM_LEAK_DBG
#define SSegMsg(mBuf1, idx, mBuf2) SSegMsgNew(mBuf1, idx, mBuf2, __FILE__, __LINE__)
EXTERN  S16 SSegMsgNew ARGS((Buffer *mBuf1,MsgLen idx,Buffer **mBuf2,char*,U32));
#else
EXTERN  S16 SSegMsg ARGS((Buffer *mBuf1,MsgLen idx,Buffer **mBuf2));
#endif
EXTERN  S16 SSwapMsg ARGS((Buffer *mBuf1, Buffer *mBuf2));
EXTERN  S16 SCpyMsgFix ARGS((Buffer *srcMbuf,MsgLen srcIdx,MsgLen cnt,
            Data *dstBuf,MsgLen *cCnt));
EXTERN  S16 SCpyFixMsg ARGS((Data *srcBuf,Buffer *dstMbuf,
            MsgLen dstIdx,MsgLen cnt,MsgLen *cCnt));
EXTERN  S16 SCompressMsg ARGS((Buffer *mBuf));
#ifdef T2K_MEM_LEAK_DBG
#define SAddMsgRef(mBuf,region,pool,dstBuf) SAddMsgRefNew(mBuf,region,pool,dstBuf,__FILE__,__LINE__)
#define SCpyMsgMsg(mBuf,region,pool, dstBuf) SCpyMsgMsgNew(mBuf,region,pool, dstBuf, __FILE__, __LINE__)
EXTERN  S16 SAddMsgRefNew ARGS((Buffer *mBuf, Region region, Pool pool, 
            Buffer **dstBuf,char*,U32));
EXTERN  S16 SCpyMsgMsgNew ARGS((Buffer *mBuf, Region region, Pool pool, 
            Buffer **dstBuf,char* , U32));
#else
EXTERN  S16 SCpyMsgMsg ARGS((Buffer *mBuf, Region region, Pool pool, 
            Buffer **dstBuf));
EXTERN  S16 SAddMsgRef ARGS((Buffer *mBuf, Region region, Pool pool, 
            Buffer **dstBuf));
EXTERN  S16 SIncMsgRef(Buffer *srcBuf, Region dstRegion, Pool dstPool, Buffer **dstBuf);

#ifdef SS_RBUF
/* EXTERN  S16 SIncMsgRef ARGS((Buffer *srcBuf, Buffer **dstBuf)); */
EXTERN Void SIncMsgLen ARGS((Buffer *mBuf));
#endif
#endif
EXTERN  S16 SChkRes ARGS((Region region,Pool pool,Status *status));
EXTERN  S16 SChkResUtl ARGS((Region region,U8 *wSum));
EXTERN  S16 SSetDateTime ARGS((DateTime *dt));
EXTERN  S16 SGetDateTime ARGS((DateTime *dt));
#ifdef L2_OPTMZ
EXTERN Void SResetMBuf ARGS ((Buffer *mBuf));
#endif
 /* ssi_x_001.main_57 : Additions */
 /* ssi_x_001.main_58 : Additions */
 /* ssi_x_001.main_60 : Modifications */
EXTERN  S16 SGetEpcTime ARGS((EpcTime *et));  
/* ssi_x_001.main_48: Added Timestamp changes */
EXTERN  S16 SGetTimeStamp ARGS(( S8    *ts));
EXTERN  S16 SGetSysTime ARGS((Ticks *sysTime));
EXTERN  S16 SGetRefTime ARGS((U32 refTime, U32 *sec, U32 *usec));
EXTERN  S16 SRandom ARGS((Random *value));
EXTERN  S16 SError ARGS((Seq seq,Reason reason));
EXTERN  Void SLogError ARGS((Ent ent, Inst inst, ProcId procId, Txt *file,
                       S32 line, ErrCls errCls, ErrCode errCode,
                       ErrVal errVal, Txt *errDesc));
/* ssi_x_001.main_49 : added prototype for SGetSystemTsk() */
EXTERN U32 SGetSystemTsk ARGS ((Void));
/* changes to support multiple processors in single SSI */
/* multiple proc id changes: 
   these functions are not supported with multiple proc Ids */ 
#ifndef SS_MULTIPLE_PROCS
EXTERN  S16 SRegInit ARGS((Ent ent,Inst inst,PAIFS16 initFnct));
EXTERN  S16 SRegActvTsk ARGS((Ent ent,Inst inst,Ttype ttype,Prior prior,
                              ActvTsk actvTsk));
#endif /* SS_MULTIPLE_PROCS */

/* multiple proc id changes: procId added and time function type modified */ 
#ifndef SS_MULTIPLE_PROCS
EXTERN  S16 SRegCfgTmr ARGS((Ent ent,
                             Inst inst,
                             S16 period,
                             S16 units,
                             PFS16 tmrFnct));
#ifdef SS_MT_TMR
/* ssi_x_001.main_53 */
EXTERN  S16 SRegCfgTmrMt ARGS((Ent ent,
                               Inst inst,
                               S16 period,
                               S16 units,
                               PAIFTMRS16 tmrFnctMt));
#endif
EXTERN  S16 SDeregCfgTmr ARGS((Ent ent,
                               Inst inst,
                               S16 period,
                               S16 units,
                               PFS16 tmrFnct));
#ifdef SS_MT_TMR
/* ssi_x_001.main_53 */
EXTERN  S16 SDeregCfgTmrMt ARGS((Ent ent,
                                 Inst inst,
                                 S16 period,
                                 S16 units,
                                 PAIFTMRS16 tmrFnctMt));
#endif
#else
EXTERN  S16 SRegCfgTmr ARGS((ProcId proc, 
                             Ent ent,
                             Inst inst,
                             S16 period,
                             S16 units,
                             PAIFTMRS16 tmrFnct));
EXTERN  S16 SDeregCfgTmr ARGS((ProcId proc, 
                               Ent ent,
                               Inst inst,
                               S16 period,
                               S16 units,
                               PAIFTMRS16 tmrFnct));
#endif /* SS_MULTIPLE_PROCS */

EXTERN  S16 SPstTsk ARGS((Pst *pst, Buffer *mBuf));

#ifdef SS_ROUTE_MSG_CORE1
EXTERN  S16 SPstTskIcpu ARGS((Pst *pst, Buffer *mBuf));
#endif

#ifdef ENB_RELAY
EXTERN  S16 SRegDrvrTsk ARGS((Inst inst, ProcId low, ProcId high, 
                              ActvTsk actvTsk, ISTsk isTsk));
/*ssi_x_001.main_56*/
EXTERN S16 SDeregDrvrTsk ARGS((Inst channel));
#endif

#ifdef SS_RTR_SUPPORT
EXTERN  S16 SRegRtrTsk ARGS((Route *, Cntr, ActvTsk));
EXTERN  S16 SDeregRtrTsk ARGS((Route *, Cntr));
#endif /* SS_RTR_SUPPORT */

#ifdef SS_USE_ZBC_MEMORY
EXTERN S16 SAttachPtrToBuf ARGS((
Region   region,
Pool     pool,
Data    *ptr,
MsgLen   totalLen,
Buffer** mBuf
));
#endif
/* multi-core support ssi_x_001.main_55 */
/*ssi_x_001.main_68 Added SS_AFFINITY_SUPPORT*/
#if defined(SS_MULTICORE_SUPPORT) || defined(SS_AFFINITY_SUPPORT)

typedef S8 SsAffinityMode;


typedef struct {
  U32 numCores;                   /* total number of cores available */
  U32 threadsPerCore;             /* total number of threads available per core */
  U32 threadRegister[SS_MAX_CORES]; /* available threads per core */
} SCpuInfo;

EXTERN S16 SRegCpuInfo ARGS((SCpuInfo *cpuInfo));
EXTERN S16 SSetAffinity ARGS((SSTskId *tskId, SsAffinityMode mode, U32 coreId, SSTskId *tskAssociatedTskId));
EXTERN S16 SGetAffinity ARGS((SSTskId *tskId, U32 *coreId));

#endif /* SS_MULTICORE_SUPPORT || SS_AFFINITY_SUPPORT*/

#ifdef SS_AEHDPR_SUPPORT
EXTERN  S16 SSetAehDpr ARGS((ProcId procId, VectNmb vectNmb,PISR pisr,PTR ptr1,PDPR pdpr,PTR ptr2));
EXTERN S16 SRemoveAehDpr ARGS((ProcId chipNum, VectNmb vectNmb));
#endif
EXTERN S16 SAddDBufPst ARGS((Buffer *mBuf, Buffer *dBuf));
EXTERN S16 SAddDBufPre ARGS((Buffer *mBuf, Buffer *dBuf));
EXTERN S16 SRemDBufPst ARGS((Buffer *mBuf, Buffer **dBuf));
EXTERN S16 SRemDBufPre ARGS((Buffer *mBuf, Buffer **dBuf));
EXTERN S16 SGetDataRx ARGS((Buffer *dBuf, MsgLen pad, Data **dat, MsgLen *mLen));
EXTERN S16 SGetDataTx ARGS((Buffer *dBuf, Data **dat, MsgLen *mLen));
EXTERN S16 SUpdMsg ARGS((Buffer *mBuf, Buffer *dBuf, MsgLen mLen));
EXTERN S16 SCacheFlush ARGS( (U16 cache_type, Data *addr, Size size));
EXTERN S16 SCacheInvalidate ARGS( (U16 cache_type, Data *addr, Size size));
EXTERN S16 SAlignDBufEven ARGS((Buffer *dBuf));
EXTERN S16 SAlignDBuf ARGS((Buffer *dBuf, U32 align));
EXTERN S16 SInitNxtDBuf ARGS((Buffer *mBuf));
EXTERN S16 SGetNxtDBuf ARGS((Buffer *mBuf, Buffer **dBuf));
EXTERN S16 SChkNxtDBuf ARGS((Buffer *mBuf));
EXTERN S16 SSetIntPend ARGS((U16 id, Bool flag));
EXTERN S16 SChkMsg ARGS((Buffer *mBuf));
EXTERN  S16 SDeregInitTskTmr ARGS((Ent ent,Inst inst));
EXTERN  S16 SExitTsk ARGS((void ));
EXTERN  S16 SExitInt ARGS((void ));
EXTERN  S16 SHoldInt ARGS((void ));
EXTERN  S16 SRelInt ARGS((void ));
EXTERN  S16 SEnbInt ARGS((void ));
EXTERN  S16 SDisInt ARGS((void ));
EXTERN  S16 SGetVect ARGS((VectNmb vectNmb,PIF *vectFnct));
EXTERN  S16 SPutVect ARGS((VectNmb vectNmb,PIF vectFnct));
#ifdef WINNT_KERN
EXTERN  S16 SPutIsrDpr ARGS((VectNmb vectNmb, Void *context, PIF isrFnct, 
                             PIF dprFnct));
EXTERN  S16 SSyncInt   ARGS((U16 adapterNmb, PFVOID syncFnct, 
                             Void *syncContext));
#endif
EXTERN  S16 SInitSema ARGS((Region region, Sema *sema));
EXTERN  S16 SRelSema ARGS((Region region, Sema sema));
EXTERN  S16 SGetSema ARGS((Region region, Sema sema));
EXTERN  S16 SActvInit ARGS((Ent ent,Inst inst,Region region,Reason reason));
EXTERN  S16 SActvTsk ARGS((Prior prior,Route route,Ent srcEnt,
            Inst srcInst,Buffer *mBuf));
EXTERN  S16 SActvTmr ARGS((void ));
EXTERN  S16 SGetOpt ARGS((int argc,char **argv,char *opts));
/* multiple proc id changes: 
   These functions not supported with multiple procIds */
#ifndef SS_MULTIPLE_PROCS
EXTERN  S16 SGetEntInst ARGS((Ent *ent, Inst *inst));
EXTERN  S16 SSetEntInst ARGS((Ent ent, Inst inst));
EXTERN  ProcId SFndProcId ARGS((void));
EXTERN  Void SSetProcId ARGS((ProcId pId));
#endif /* SS_MULTIPLE_PROCS */

EXTERN S16 SGetDBufSiz ARGS((Region region, Pool pool, S16 *size));
EXTERN S16 SGetStrtIdx ARGS((Region region, Pool pool,  S16 *idx));
EXTERN S16 SGetEndIdx ARGS((Region region, Pool pool,  S16 *idx));
EXTERN S16 SGetStrtPad ARGS((Region region, Pool pool,  S16 *pad));
/* multiple proc id changes: control block retrieval function */
#ifdef SS_MULTIPLE_PROCS
EXTERN S16 SGetXxCb ARGS((ProcId proc, Ent ent, Inst inst, Void **xxCb));
#endif /* SS_MULTIPLE_PROCS */

#ifdef MT
/*
 * These routines are only available for multi-threaded
 * system service implementations
 */
EXTERN S16 SGetMutex ARGS((MtMtxId *mId));
EXTERN S16 SPutMutex ARGS((MtMtxId mId));
EXTERN S16 SLockMutex ARGS((MtMtxId mId));
EXTERN S16 SUnlockMutex ARGS((MtMtxId mId));
EXTERN S16 SGetCond ARGS((MtCondId *cId));
EXTERN S16 SPutCond ARGS((MtCondId cId));
EXTERN S16 SCondWait ARGS((MtMtxId mId,MtCondId cId));
EXTERN S16 SCondSignal ARGS((MtCondId cId));
EXTERN S16 SCondBroadcast ARGS((MtCondId cId));
EXTERN S16 SGetThread ARGS((MtThrd thrd, MtThrdFlags thr_flgs, 
                            Ptr arg, MtThrdId *thrdId));
EXTERN S16 SPutThread ARGS((MtThrdId thrdId));
EXTERN Void SThreadYield ARGS((void));
EXTERN Void SThreadExit ARGS((Ptr *status));
EXTERN Void SSetThrdPrior ARGS((MtThrdId tId, MtThrdPrior tPr));
EXTERN Void SGetThrdPrior ARGS((MtThrdId tId, MtThrdPrior *tPr));
#endif /* MT */

EXTERN Void SExit ARGS((Void));
#ifdef SS
/* multiple proc id changes: procId added */ 
#ifndef SS_MULTIPLE_PROCS

EXTERN S16 SRegTTsk ARGS((Ent ent, 
                          Inst inst, 
                          Ttype type, 
                          Prior prior, 
                          PAIFS16 initTsk, 
                          ActvTsk actvTsk));
/* ssi_x_001.main_60 */
EXTERN S16 SRegCbTsk ARGS((Ent ent, 
                          Inst inst, 
                          ActvTsk actvTsk));
EXTERN S16 SDeregTTsk ARGS((Ent ent, Inst inst));

#else

EXTERN S16 SRegTTsk ARGS((ProcId proc, 
                          Ent ent, 
                          Inst inst, 
                          Ttype type, 
                          Prior prior, 
                          PAIFS16 initTsk, 
                          ActvTsk actvTsk));
EXTERN S16 SDeregTTsk ARGS((ProcId proc, Ent ent, Inst inst));

EXTERN S16 SRegCbTsk ARGS((ProcId proc,
								  Ent ent, 
                          Inst inst, 
                          ActvTsk actvTsk));
#endif /* SS_MULTIPLE_PROCS */

EXTERN S16 SCreateSTsk ARGS((SSTskPrior tskPrior, SSTskId *tskId));
EXTERN S16 SDestroySTsk ARGS((SSTskId tskId));
/* multiple proc id changes: procId added */ 
#ifndef SS_MULTIPLE_PROCS

EXTERN S16 SAttachTTsk ARGS((Ent ent, Inst inst, SSTskId tskId));
EXTERN S16 SDetachTTsk ARGS((Ent ent, Inst inst));

#else

EXTERN S16 SAttachTTsk ARGS((ProcId proc, Ent ent, Inst inst, SSTskId tskId));
EXTERN S16 SDetachTTsk ARGS((ProcId proc, Ent ent, Inst inst));

#endif /* SS_MULTIPLE_PROCS */
EXTERN S16 SRegRegion ARGS((Region region, SRegInfo *regInfo));
EXTERN S16 SDeregRegion ARGS((Region region));
EXTERN S16 SRegDynRegion ARGS((Region region, SRegInfo *regInfo)); 
/*ssi_x_001.main_62-prototype for SAlloc and SFree, gaurded under flag*/
#ifndef SS_FAP
 /* ssi_x_001.main_57 : Additions */
#ifdef SS_HISTOGRAM_SUPPORT 
EXTERN S16 SAlloc ARGS((Region region, Size *size, U32 flags, Data **ptr,U32 line, U8 *fileName, U8 entId));
EXTERN S16 SFree ARGS((Region region, Data *ptr, Size size, U32 line, U8 *fileName, U8 entId));
#else
#ifdef T2K_MEM_LEAK_DBG
#define SAlloc(region,size,flags,ptr) SAllocNew(region,size,flags,ptr,file,line)
#define SFree(region,ptr,size) SFreeNew(region,ptr,size,file,line)
EXTERN S16 SAllocNew ARGS((Region region, Size *size, U32 flags, Data **ptr,char*,U32));
EXTERN S16 SFreeNew ARGS((Region region, Data *ptr, Size size,char*,U32));
#elif defined(SS_LIGHT_MEM_LEAK_STS)
EXTERN S16 SAlloc ARGS((Region region, Size *size, U32 flags, Data **ptr,U32 line, U8 *fnName));
EXTERN S16 SFree ARGS((Region region, Data *ptr, Size size, U32 line, U8 *fnName));
#else
EXTERN S16 SAlloc ARGS((Region region, Size *size, U32 flags, Data **ptr));
EXTERN S16 SFree ARGS((Region region, Data *ptr, Size size));
#endif
#endif
EXTERN S16 SGetBufRegionPool ARGS((Buffer *mBuf, Region *region, Pool *pool));
#endif /* SS_ENABLE_MACROS */

#ifdef SS_OLD_THREAD
EXTERN S16 SGetMutex      ARGS((SMtxId *mId));
EXTERN S16 SPutMutex      ARGS((SMtxId mId));
EXTERN S16 SLockMutex     ARGS((SMtxId mId));
EXTERN S16 SUnlockMutex   ARGS((SMtxId mId));
EXTERN S16 SGetCond       ARGS((SCondId *cId));
EXTERN S16 SPutCond       ARGS((SCondId cId));
EXTERN S16 SCondWait      ARGS((SMtxId mId,SCondId cId));
EXTERN S16 SCondSignal    ARGS((SCondId cId));
EXTERN S16 SCondBroadcast ARGS((SCondId cId));
EXTERN S16 SGetThread     ARGS((SThrd thrd, S32 thr_flgs, 
                                                 Ptr arg, SThrdId *thrdId));
EXTERN S16 SPutThread     ARGS((SThrdId thrdId));
EXTERN Void SThreadYield  ARGS((void));
EXTERN Void SThreadExit   ARGS((Ptr status));
EXTERN Void SSetThrdPrior ARGS((SThrdId tId, S32 tPr));
EXTERN Void SGetThrdPrior ARGS((SThrdId tId, S32 *tPr));
EXTERN Void SExit         ARGS((void));
#else /* SS_OLD_THREAD */
EXTERN S16 SThreadYield  ARGS((void));
#endif /* SS_OLD_THREAD */

EXTERN S16 SInitLock     ARGS((SLockId *lock,U8 type));
EXTERN S16 SLock         ARGS((SLockId *lock));
EXTERN S16 SUnlock       ARGS((SLockId *lock));
EXTERN S16 SDestroyLock  ARGS((SLockId *lock));


EXTERN S16 SInitSemaphore ARGS((SsSemaId *sem, U8 value));
EXTERN S16 SWaitSemaphore ARGS((SsSemaId *sem));
EXTERN S16 SPostSemaphore ARGS((SsSemaId *sem));
EXTERN S16 SDestroySemaphore ARGS((SsSemaId *sem));

/* multiple proc id changes: 
   new function required to implement multiple procIds */
#ifdef SS_MULTIPLE_PROCS
EXTERN S16 SAddProcIdLst ARGS((U16 numPIds, ProcId *pIdLst));
EXTERN S16 SRemProcIdLst ARGS((U16 numPIds, ProcId *pIdLst));
EXTERN S16 SGetProcIdLst ARGS((U16 *numPIds, ProcId *pIdLst));
#endif /* SS_MULTIPLE_PROCS */

#endif /* SS */

#ifdef SS_SEGV_SIG_HDLR
#ifndef SS_MULTIPLE_PROCS
EXTERN S16 SRegIntrptHdlr ARGS((Ent ent, Inst inst, PFS16 intrptActvFn));
#else
EXTERN S16 SRegIntrptHdlr ARGS((ProcId proc, Ent ent, Inst inst, PFS16 intrptActvFn));
#endif/*SS_MULTIPLE_PROCS*/
#endif /* SS_SEGV_SIG_HDLR */

#ifdef PORTVER
/* procId added */ 
#ifndef SS_MULTIPLE_PROCS
EXTERN S16 SRegTTsk ARGS((Ent ent, 
                          Inst inst, 
                          Ttype type, 
                          Prior prior, 
                          PAIFS16 initTsk, 
                          ActvTsk actvTsk));
/* ssi_x_001.main_60 */
EXTERN S16 SRegCbTsk ARGS((Ent ent, 
                          Inst inst, 
                          ActvTsk actvTsk));
EXTERN S16 SDeregTTsk ARGS((Ent ent, Inst inst));
EXTERN S16 SAttachTTsk ARGS((Ent ent, Inst inst, SSTskId tskId));
EXTERN S16 SDetachTTsk ARGS((Ent ent, Inst inst));
#else
EXTERN S16 SRegTTsk ARGS((ProcId proc, 
                          Ent ent, 
                          Inst inst, 
                          Ttype type, 
                          Prior prior, 
                          PAIFS16 initTsk, 
                          ActvTsk actvTsk));
EXTERN S16 SRegCbTsk ARGS((ProcId proc,
								  Ent ent, 
                          Inst inst, 
                          ActvTsk actvTsk));
EXTERN S16 SDeregTTsk ARGS((ProcId proc, Ent ent, Inst inst));
EXTERN S16 SAttachTTsk ARGS((ProcId proc, Ent ent, Inst inst, SSTskId tskId));
EXTERN S16 SDetachTTsk ARGS((ProcId proc, Ent ent, Inst inst));
#endif /* SS_MULTIPLE_PROCS */

EXTERN S16 SCreateSTsk ARGS((SSTskPrior tskPrior, SSTskId *tskId));
EXTERN S16 SDestroySTsk ARGS((SSTskId tskId));
#ifndef SS_ENABLE_MACROS
EXTERN S16 SGetBufRegionPool ARGS((Buffer *mBuf, Region *region, Pool *pool));
#endif /* SS_ENABLE_MACROS */

EXTERN S16 SInitLock     ARGS((SLockId *lock,U8 type));
EXTERN S16 SLock         ARGS((SLockId *lock));
EXTERN S16 SUnlock       ARGS((SLockId *lock));
EXTERN S16 SDestroyLock  ARGS((SLockId *lock));

EXTERN S16 SInitSemaphore ARGS((SsSemaId *sem, U8 value));
EXTERN S16 SWaitSemaphore ARGS((SsSemaId *sem));
EXTERN S16 SPostSemaphore ARGS((SsSemaId *sem));
EXTERN S16 SDestroySemaphore ARGS((SsSemaId *sem));
/* functions required to implement multiple procIds */ 
#ifdef SS_MULTIPLE_PROCS
EXTERN S16 SAddProcIdLst ARGS((U16 numPIds, ProcId *pIdLst));
EXTERN S16 SRemProcIdLst ARGS((U16 numPIds, ProcId *pIdLst));
EXTERN S16 SGetProcIdLst ARGS((U16 *numPIds, ProcId *pIdLst));
#endif /* SS_MULTIPLE_PROCS */

#endif /* PORTVER */

  
/* function prototypes */
 
/* stack manager initialization function */
/* multiple proc id changes: procId added */ 
#ifndef SS_MULTIPLE_PROCS
EXTERN S16 smActvInit ARGS((Ent ent, Inst inst, Region region, Reason reason));
#else /* SS_MULTIPLE_PROCS */
EXTERN S16 smActvInit ARGS((ProcId proc, 
                            Ent ent, 
                            Inst inst, 
                            Region region, 
                            Reason reason,
                            Void **xxCb));
#endif /* SS_MULTIPLE_PROCS */

/* stack manager external initialization function */
EXTERN S16 smInitExt ARGS((void));
 
/* stack manager activation function */
EXTERN S16 smActvTsk ARGS((Pst *pst, Buffer *mBuf));

/* ssi_x_001.main_54 */
#ifdef SS_SID_CHANGE
/* ssi_x_001.main_53 */
EXTERN  S16 SGetInDepSId ARGS((SystemId *s));
EXTERN  S16 SGetDepSId ARGS((SystemId *s));
#endif

/* Macros... */
 
#define SS_INITDCHN(chn) (chn)->next = NULLP; (chn)->prev = NULLP
#define SS_INITQUE(qu) \
   SS_INITDCHN(&(qu)->dChn); (qu)->crntSize = 0
#define SS_QLEN(bq)  ((bq)->crntSize)
#define SS_MLEN(mb) ((mb)->t.msg.msgLen)

/* ssi_x_001.main_50 : Added declarations for mutex related functions
 * to protect demand queue and memory allocation 
 */
/* ssi_x_001.main_51 : Added control flag as these are only used by windows */
#ifdef SS_WIN
EXTERN S16 WTInitLock     ARGS((SLockId *lock,U8 type));
EXTERN S16 WTLock         ARGS((SLockId *lock));
EXTERN S16 WTUnlock       ARGS((SLockId *lock));
EXTERN S16 WTDestroyLock  ARGS((SLockId *lock));
#endif /* End of SS_WIN */
 /* ssi_x_001.main_57 : Additions */
#ifdef SS_LOGGER_SUPPORT  
EXTERN S16 SRegLogCfg ARGS(( U8 mode, S8 *path, U32 size, S8 *IPA, U16 port));
EXTERN S16 SWrtLogBuf ARGS(( Txt *buf ));
/* ssi_x_001.main_60 */
EXTERN S16 SDeregLogCfg ARGS((Void ));
#endif /* SS_LOGGER_SUPPORT */

#ifdef SS_HISTOGRAM_SUPPORT
EXTERN S16 SRegForHstGrm ARGS((Ent ent));
EXTERN S16 SHstGrmInfoShow ARGS((Ent *entId));
EXTERN S16 SFillEntIds ARGS((Void));
EXTERN S16 SGetEntInd ARGS((Ent *entId, U8 *fileName));
#endif /* SS_HISTOGRAM_SUPPORT */
/* ssi_x_001.main_68  Multiple declaration removed , one already in cm_task.x */
/* ssi_x_001.main_61: Lock support guraded under the flag */
#ifdef SS_LOCK_SUPPORT
EXTERN S16 SLockNew ARGS((SLockInfo *LockId, U8 lockType));
EXTERN S16 SInitLockNew ARGS((SLockInfo *LockId, U8 lockType));
EXTERN S16 SUnlockNew ARGS((SLockInfo *LockId, U8 lockType));
EXTERN S16 SDestroyLockNew ARGS((SLockInfo *LockId, U8 lockType));
#endif /* SS_LOCK_SUPPORT */
EXTERN S8* SGetConfigPath ARGS((Void));

/* ssi_x_001.main_66 : Added new Buffer manegement APIs */
EXTERN S16 SCpyPartMsg ARGS((Buffer *srcBuf, MsgLen idx, MsgLen cnt, Buffer *dstBuf));
EXTERN S16 SRepPartMsg ARGS((Buffer *srcBuf, MsgLen idx, MsgLen cnt, Buffer *dstBuf));
EXTERN S16 SMovPartMsg ARGS((Buffer *srcBuf, MsgLen idx, Buffer *dstBuf));
EXTERN S16 SPkMsgMult ARGS((Data *src, MsgLen cnt, Buffer *mBuf));
EXTERN S16 SGetReadPtr ARGS((Buffer *mBuf, U8** data, MsgLen *len));

typedef enum
{
   SS_SHARABLE_MEMORY,
   SS_NON_SHARABLE_MEMORY
}ssMemoryType;
#ifdef TENB_T2K3K_SPECIFIC_CHANGES                              
EXTERN S16 SReInitTmr ARGS((Void ));                            
#endif
/* ssi_x_001.main_69: Added MSPD debug macro */
#ifdef MSPD
extern U32 ysGT;
extern char ys_global_printbuf[256];
EXTERN Void rbCallstackShow ARGS((Void));
EXTERN Void rbCallstackShowForCore ARGS((U32 coreId));
EXTERN U32 MacGetTick ARGS ((void));
#endif /* MSPD */
#ifdef LTE_L2_MEAS
extern U64  glblTtiCnt;
#endif

EXTERN S16 SStartTask ARGS((VOLATILE U32 *startTime, U32 tarkId));
EXTERN S16 SStopTask ARGS((VOLATILE U32 startTime,U32 taskId));
#ifdef MSPD_MLOG_NEW
/* Removed for C++ Compilation
EXTERN unsigned int MLogTask (unsigned int taskid, unsigned int resourceid , 
                       unsigned int ticksstart,unsigned int ticksstop);
--*/
#endif

#if defined(MSPD) && defined(MSPD_DBG_ENABLE)
#define MSPD_DBG_RLC(...) 
#ifdef TENB_T2K3K_SPECIFIC_CHANGES
#define MSPD_DBG(...) do { \
   char _local_printbuf[SS_MEMLOG_MAXSTRLEN]; \
   int _len1 = snprintf(_local_printbuf, SS_MEMLOG_MAXSTRLEN, "%s():%u @%lu ", __func__, __LINE__, ysGT); \
   int _len2 = snprintf(&_local_printbuf[_len1],SS_MEMLOG_MAXSTRLEN - _len1, __VA_ARGS__) + _len1; \
   ssMemlog(_local_printbuf, _len2); \
} while (0)
#define MSPD_DBG_RAW(...) do { \
   char _local_printbuf[SS_MEMLOG_MAXSTRLEN]; \
   int _len = snprintf(_local_printbuf,SS_MEMLOG_MAXSTRLEN, __VA_ARGS__); \
   ssMemlog(_local_printbuf, _len); \
} while (0)
#define MSPD_LOG(...) do { \
   char _local_printbuf[SS_MEMLOG_MAXSTRLEN]; \
   int _len1 = snprintf(_local_printbuf, SS_MEMLOG_MAXSTRLEN,"%s():%u @%lu ", __func__, __LINE__, ysGT); \
   int _len2 = snprintf(&_local_printbuf[_len1],SS_MEMLOG_MAXSTRLEN - _len1, __VA_ARGS__) + _len1; \
   ssMemlog(_local_printbuf, _len2); \
} while (0)
#define MSPD_ERR(...) do { \
   char _local_printbuf[SS_MEMLOG_MAXSTRLEN]; \
   int _len1 = snprintf(_local_printbuf, SS_MEMLOG_MAXSTRLEN, "ERROR: %s():%u @%lu ", __func__, __LINE__, ysGT); \
   int _len2 = snprintf(&_local_printbuf[_len1],SS_MEMLOG_MAXSTRLEN - _len1, __VA_ARGS__) + _len1; \
   ssMemlog(_local_printbuf, _len2); \
} while (0)
#if 0
#define MSPD_ERR(...) do { \
   sprintf(ys_global_printbuf, "ERROR: %s():%u @%lu ", __func__, __LINE__, ysGT); \
   sprintf(&ys_global_printbuf[strlen(ys_global_printbuf)], __VA_ARGS__); \
   SPrint(ys_global_printbuf); \
} while (0)	
#endif

EXTERN Void ssMlogInit(Void);
EXTERN Void ssMlogIncrCounter(Void);
EXTERN Void ssMemlogInit(Void);
EXTERN Void ssMemlog(char *, U32 size);
EXTERN Void ssMemlogWrite(Void);

#endif /* TENB_T2K3K_SPECIFIC_CHANGES */
#endif

#ifdef __cplusplus
}
#endif

EXTERN Void SIncrementTtiCount(Void);
EXTERN Ticks SGetTtiCount(Void);
#ifdef TENB_T2K3K_SPECIFIC_CHANGES
EXTERN Void mtStopHndlr(Void);
#if 0
#ifdef SS_LOCKLESS_MEMORY   
#ifdef USE_MALLOC
EXTERN S16 ssGetDynMemBlkSet  ARGS((U8 bktIdx, CmMmBlkSetElement *dynMemSetElem));
EXTERN S16 ssPutDynMemBlkSet  ARGS((U8 bktIdx, CmMmBlkSetElement *dynMemSetElem));
#endif /* USE_MALLOC */
#endif /* SS_LOCKLESS_MEMORY */
#endif
#endif

#ifdef TENB_RTLIN_CHANGES
EXTERN Void ysPrntBkTrace(Void);
EXTERN Void ssMlogInit(Void);
EXTERN Void ssMlogIncrCounter(Void);
#endif
#ifdef SS_THR_REG_MAP
EXTERN Void ssRegMainThread(Void);
#endif

#ifdef T2K_MEM_LEAK_DBG
#define ssGetDBufOfSize(region,size,dBuf) ssGetDBufOfSizeNew(region,size,dBuf,__FILE__,__LINE__)
PUBLIC S16 ssGetDBufOfSizeNew ARGS((Region region, Size size, Buffer **dBuf,char*,U32));
#else
EXTERN  S16 ssGetDBufOfSize(Region region,Size size,Buffer **dBuf);
#endif

/* ssi_x_001.main_69: Added MSPD debug macro */
#ifdef MSPD
EXTERN void SEND_DBG_MSG(U8 *str, ...);
#endif

#endif /* __SSIX__ */


/********************************************************************30**
  
         End of file:     ssi.x@@/main/71 - Thu Feb 16 17:43:25 2012
  
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
2.1          ---  nkk   1. initial release

2.2          ---  jrl   1. move some typedefs from ssi.x to support
                           reordering of ssi and gen includes
             ---  nkk   2. add Chn definition in VX section.

2.3          ---  fmg   1. add SRegDrvr prototype

2.4          ---  jrl   1. add ifdef SSINT2

2.5          ---  fmg   1. add spare elements for alignment to processor
                           boundaries

2.6          ---  jrl   1. add Buffer and Queue typedef for portable

2.7          ---  mc    1. add forward definitions - buffer and queue for
                           pSOS and VRTXsa cases.

2.8          ---  fmg   1. changed struct buffer to struct ss_buffer,
                           struct queue to struct ss_queue, struct dat
                           to struct ss_dat, and struct msg to struct ss_msg
                           to avoid conflicts with system include for other
             ---  mc    2. add ss_queue and ss_buffer typedefs for VxWorks

2.9          ---  fmg   1. compressed SS structures to remove unused fields
                           Aligned on 4byte boundaries and ordered Pst.
             ---  fmg   2. Changed extern to EXTERN
             ---  fmg   3  Added INLINE to some function definitions
             ---  fmg   4. Added Pk/Unpk macros.
             ---  fmg   5. Changed Ticks from S32 to U32

2.10         ---  fmg   1. removed Pk macros for simplicity.

2.11         ---  fmg   1. added new system service primitive prototypes
                           for functions that provide needed functionality 
                           to drivers.
             ---  fmg   2. modified MSVER2 msg structure to track next
                           data buffer in a message

2.12         ---  fmg   1. converted vxWorks buffer structure from large
                           byte arrays to chains (ala MSVER2).
2.13         ---  fmg   2. added SSetProcId for VW case

2.14         ---  fmg   1. modified SGetDatRx
             ---  fmg   2. added SSetIntProc, SChkMsg
             ---  fmg   3. Converted MSVER2 to use pointers
             ---  fmg   4. Added INLINE declaration for compilers that
                           can use it.

2.15         ---  vk    1. Added WINNT changes

2.16         ---  mb    1. Made structures ss_dat and ss_msg similar
                           for VxWorks and MOS.
             ---  mb    2. Moved MACROS MS_INIDCHN, MS_INITQUE, MS_QLEN,
                           MS_MLEN from ms.x. Replaced the prefix "MS_"
                           by "SS_"
             ---  mb    3. New typedefs ErrCls, ErrCode and ErrVal
             ---  mb    4. Prototype for SLogError, SDeregTmr, 
                           SGetDBufSize, SGetStrtIdx, SGetEndIdx, 
                           SGetStrtPad.

2.17         ---  kish  1. Fixed a compiler warning

2.18         ---  fmg   1. text changes
             ---  fmg   2. re-introduce PORTVER

2.19         ---  kr    1. added two new routines "SPutIsrDpr" and 
                           "SSyncInt" for system services on WINNT.
2.20         ---  mb    1. moved struct def uProc from ms.x
                  mb    2. moved Buffer and Queue def from gen.x
                  mb    3. Removed SSINT stuff.

2.21         ---  mb    1. Removed #ifdef VW for SSetProcId Prototype

2.22         ---  mb    1. Changed BufQLen data type
                        2. Removed spare fields after QLen/BufQLen fields
                           in Queue and BufQ structure.

*********************************************************************81*/


/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
2.23         ---      kvm  1. Moved out typedefs DateTime, Duration, Mem,
                              and MemoryId to gen.x
             ---      kvm  2. moved out forward definition of Buffer to 
                              ssi.x

2.24         ---      kvm  1. renamed CMATM2 as CMFILE_REORG_1

2.25         ---      kr   1. changed MsgLen typedef to S32
2.26         ---      bbk  1. Changed copyright header date.
2.27         ---      ag   1. Relocated #ifdef WINNT section and 
                              excluded this section for NTSS
             ---      ag   2. Added declaration for basic SS types
                              under #ifdef SS section
             ---      ag   3. Added new definition for ISTsk under
                              RYINT1 flag 

2.28         ---      kr   1. Corrected the order of #ifndef NS 
                              and #ifdef WINNT

2.29         ---      kr   1. Added define SS_ENABLE_MACROS
             ---      kr   2. Moved SGETBUFREGION and SGETBUFPOOL to ssi.h
             ---      kr   3. Added nsRegDevice and nsDeregDevice 
                              prototypes
             ---      bsr  1. Chaged WINNT to WINNT_IATM
             ---      bsr  2. Added NsDevCtl and device control function
                              prototypes.

2.30         ---      kp   1. Added extern "C" for making this file C++
                              compilable
             ---      kr   2. Removed Windows NT specific prototypes

2.31         ---      kp   1. Added in prototype for SRegRtrTsk()
                           2. Added in extern declarations of msArg* for
                              SGetOpt() functionality

2.32         ---      tej  1. Change in header

/main/33        ---      jjn  1. Added the prototypes for following:
                              SDeregRtrTsk, SSetAehDpr, SAlignDBuf, 
                              SInitSemaphore, SWaitSemaphore, 
                              SPostSemaphore, SDestroySemaphore

/main/34        ---      ada  1. Added prototypes under the PORTVER flag
/main/36     ---      sv   1. changed parameter name for SSetAehDpr  
                           2. Added SRemoveAehDpr 
                           3. Added datatype PISR and PDPR
/main/37     ---      cvp  1. Changed the copyright header date.
/main/38     ---      bjp  1. Added SSwapMsg prototype
/main/39     ---      bjp  1. Added SGetRefTime prototype
/main/42     ---      jjn  1. Added SCacheFlush & SCacheInvalidate.
/main/43     ---      bjp  1. Added Prototype for SThreadYield
/main/44     ---      bjp  1. 1ms Timer related changes
/main/45     ---      kkj  1. Multile procId related changes
/main/46     ---      st   1. Update for MAP Release 2.3
/main/47     ---      sm   1. Protected the INLINE definitions of 
                              SgetDBuf and SputDBuf.

/main/47     ssi_x_001.main_47      vk   1. Changes for SSI enhancements
/main/49     ---      ssi_x_001.main_48      ss   1. Added Timestamp changes
/main/50     ---      ssi_x_001.main_49 : 1. added packing and unpacking of F32 and F64
                                 2. added prototype for SGetSystemTsk() 
/main/51    ssi_x_001.main_50       rks  1. Added declaration for mutex related
                                            functions
/main/52    ssi_x_001.main_51       rks  1. Added flag to control mutex related 
                                            function declarations
/main/53     ---      st  1. Added support for newly introduced
                             timer activation changes.
/main/53+    ssi_x_001.main_53      bn   1. Added prototypes for functions
                                             SGetInDepSId and SGetDepSId
                                 apany  2. New timer reg/dereg functions
                                           for multthreading
/main/55     ---      ssi_x_001.main_54   apany  1. New functions added in last patch
                                             protected under flags
/main/56     ---      ssi_x_001.main_55      ch    1. Updated for SSI Multicore.
/main/57     ---      ssi_x_001.main_56      bn    1. Added for SDeregDrvrTsk.
/main/58     ---      ssi_x_001.main_57 schandra1  1. SSI-ph-2 value added feature additions
/main/59     ---   ssi_x_001.main_58   schandra1 1. SSI-Phse-2 Thread profile EpcTime guarded under 64 bit flag.
/main/60     ---   ssi_x_001.main_59   rkumar    1. SSI-Phase-2 Added flag to correct 
                                                    compilation and to support old SSI
/main/61     ---   ssi_x_001.main_60  snatarajan 1. SRegCbTsk to register a call back function
                                   pmacharla  1. Fixed compilation errors for SDeregLogCfg
                                              2. Removed BIT_64 protection for EpcTime 
                                   rss		  1. Readwrite lock added			  
/main/62     --- ssi_x_001.main_61 rss        1. Readwrite locks guarded under flag 
/main/63     --- ssi_x_001.main_62 akulkarni  1. prototype for SAlloc and SFree,
                                                 gaurded under flag
/main/64     --- ssi_x_001.main_63 ssahniX  1. ss_dep.x guarded under flag
/main/65     --- ssi_x_001.main_64 pmacharla 1.Cavium related additions guarded under SS_CAVIUM
/main/66     --- ssi_x_001.main_65 pmacharla 1.Cavium related additions guarded under SS_SEUM_CAVIUM
/main/67     --- ssi_x_001.main_66 vsrao     1.Added new buffer management APIs
/main/68     --- ssi_x_001.main_67 ssahniX     1. RMIOS related changes
/main/69     --- ssi_x_001.main_68 ssahniX     1. Multiple declaration removed.
/main/70     --- ssi_x_001.main_69 akapoor     1. Removed the SS_MT_TMR guard from PAIFTMRS16
                                                  timer activation function typedef.
/main/71     --- ssi_x_001.main_70 akapoor     1. Added prototype for SAddPreMsgMultInOrder.
/main/72     --- ssi_x_001.LPR     sasahni     1. Added prototype for SRegIntrptHdlr.
*********************************************************************91*/
