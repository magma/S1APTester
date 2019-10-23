


/********************************************************************20**
 
     Name:     Common Memory Manager 
 
     Type:     C source file
 
     Desc:     C source code for the Commom Memory Manager module. 
 
     File:     cm_mem_wl.c
 
     Sid:      cm_mem_wl.c@@/main/TeNB_Main_BR/6 - Tue Jul  8 12:01:57 2014
 
     Prg:      rm
 
*********************************************************************21*/


/************************************************************************

The following functions are provided in this file.
 
    cmMmRegInit     Memory Region Initialization.
    cmMmRegDeInit   Memory Region Deinitialization.

************************************************************************/

#ifndef SS_RBUF

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
 
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_mem.h"        /* Common memory manager cm_mem_c_001.main_15 */ 
#include <stdlib.h>
#ifdef SS_MEM_LEAK_STS
#include <stdio.h>
#include <string.h>
#ifdef SS_MEM_LEAK_SOL
#include <ucontext.h>
#include <dlfcn.h>
#include <sys/machelf.h>
#else /* SS_MEM_LEAK_SOL */
#include <execinfo.h>
#endif /* SS_MEM_LEAK_SOL */
#include <sys/types.h>
#endif /* SS_MEM_LEAK_STS */
#include "cm_hash.h" 

#ifdef SS_MULTICORE_SUPPORT /* cm_mem_c_001.main_14 */
#include "ss_dep.h"        /* implementation-specific */
#include "ss_queue.h"      /* queues */
#include "ss_task.h"       /* tasking */
#endif 
#ifdef SS_MULTICORE_SUPPORT
#include "ss_dep.h"        /* implementation-specific */
#include "ss_queue.h"      /* queues */
#include "ss_task.h"       /* tasking */
#endif
#include "cm_llist.h"

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#ifdef SS_MULTICORE_SUPPORT
#include "ss_dep.x"        /* implementation-specific */
#include "ss_queue.x"      /* queues */
#include "ss_task.x"           /* system services */
#endif
#include "cm_hash.x"       /* common hash functions */
#include "cm_llist.x"
#include "cm_mem_wl.x"        /* Common memory manager */ 
/* cm_mem_c_001.main_15: Addition  */
#include "cm_lib.x"        /* common library functions */


#ifdef USE_PURE
#include <stdlib.h>
#endif /* USE_PURE */
#ifdef SS_MULTICORE_SUPPORT
#include "ss_dep.x"        /* implementation-specific */
#include "ss_queue.x"      /* queues */
#include "ss_task.x"           /* system services */
#endif

#ifdef USE_PURE
#include <stdlib.h>
#endif /* USE_PURE */

#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#ifdef SS_USE_ICC_MEMORY
#include "icc_lib.h"
#endif /* SS_USE_ICC_MEMORY */

#ifdef L2_L3_SPLIT     
#include "mt_plat_t33.h"
extern S32 clusterMode;
#endif

#include "cm_lte.x"


/* local defines */
/*ccpu00142274 - UL mem based flow control changes */
#ifdef TENB_T2K3K_SPECIFIC_CHANGES
/* selva */
U32 gMemoryAlarm;
PRIVATE U32 memoryCheckCounter;

#define NUM_CALLS_TO_CHECK_MEM_AGAIN      80 /* Number of calls after which need to check mem */
#ifndef L2_L3_SPLIT
#ifdef T2200_2GB_DDR_CHANGES
#define ICC_MEM_UPPER_THRESHOLD 20 /* Only 20% of the available memory blocks are free */
#define ICC_MEM_LOWER_THRESHOLD 10 /* Only 10% of the available memory blocks are free */
#else
#define ICC_MEM_UPPER_THRESHOLD 10 /* Only 20% of the available memory blocks are free */
#define ICC_MEM_LOWER_THRESHOLD 8 /* Only 10% of the available memory blocks are free */
#endif
#else
#define ICC_MEM_UPPER_THRESHOLD 9 /* Only 20% of the available memory blocks are free */
#define ICC_MEM_LOWER_THRESHOLD 12 /* Only 30% of the available memory blocks are free */
#endif
#define ICC_POOL_ZERO_SIZE 384
#define ICC_POOL_ONE_SIZE  1920
#define ICC_POOL_TWO_SIZE  3968
#ifdef T2200_2GB_DDR_CHANGES
#define ICC_POOL_THREE_SIZE  16256
#else
#define ICC_POOL_THREE_SIZE  8064
#endif
#ifndef L2_L3_SPLIT
#ifdef T2200_2GB_DDR_CHANGES
#define ICC_POOL_ZERO_TOTAL_BLKS  139809 /* this and the next should be dynamic*/
#define ICC_POOL_ONE_TOTAL_BLKS   209714
#define ICC_POOL_TWO_TOTAL_BLKS   27961 
#define ICC_POOL_THREE_TOTAL_BLKS 27961 
#else
#define ICC_POOL_ZERO_TOTAL_BLKS  55106 /* this and the next should be dynamic*/
#define ICC_POOL_ONE_TOTAL_BLKS   68567
#define ICC_POOL_TWO_TOTAL_BLKS   13819 
#define ICC_POOL_THREE_TOTAL_BLKS 10902 
#endif
#else
/* The below configuration used for icc_part_size=573M in boot args, if icc part
 * size changes then need to change the below configuration values*/
#ifndef LTE_ADV
#define ICC_POOL_ZERO_TOTAL_BLKS  78232  
#define ICC_POOL_ONE_TOTAL_BLKS  117349
#define ICC_POOL_TWO_TOTAL_BLKS   15645
#define ICC_POOL_THREE_TOTAL_BLKS 15645
#else
#define ICC_POOL_ZERO_TOTAL_BLKS 61165 
#define ICC_POOL_ONE_TOTAL_BLKS  91749
#define ICC_POOL_TWO_TOTAL_BLKS   12232
#define ICC_POOL_THREE_TOTAL_BLKS 12232
#endif
#endif
#endif

/* local typedefs */
 
/* local externs */
 
/* forward references */
/* cm_mem_c_001.main_12 - prototype is changed to accept memType(static/dynamic) */
/* cm_mem_c_001.main_15: Addition */
/* cm_mem_c_001.main_22: Fixing warnings on GCC compiler*/
#ifdef __cplusplus
 extern "C" {
#endif

CmHashListCp    memDoubleFree;           /* Added to find the double free */
SLockId         memDoubleFreeLock;
#define NUM_BT_TRACES 12
typedef struct cmMemFreeInfo
{
  PTR             ptr;
  size_t          btSize;
  void           *btArr[NUM_BT_TRACES]; 
  struct timeval  timeStamp;
  
} CmMemFreeInfo;

#define NUM_FREE_BUFFERS    128
typedef struct cmBtInfo
{
  U32 btInfoIdx;
  CmMemFreeInfo  btInfo[NUM_FREE_BUFFERS];
} CmBtInfo;

CmBtInfo    *regBtInfo;
CmBtInfo    *allocBtInfo;

typedef struct cmMemDoubleFree
{
   CmHashListEnt  tmpListEnt;
   CmMemFreeInfo  traceInfo;
   PTR            memBlkPtr;
}CmMemDoubleFree;

PTR prvAllocPtr[8];
PUBLIC U8 stopBtInfo = FALSE;
PUBLIC Buffer *palBuffer;
EXTERN Buffer *mtTskBuffer1;
EXTERN Buffer *mtTskBuffer2;

#ifdef SS_USE_ICC_MEMORY
PRIVATE pthread_mutex_t iccAllocFreeLock;
#else
PRIVATE pthread_mutex_t dynAllocFreeLock;
#endif /* SS_USE_ICC_MEMORY */

#ifdef SS_MEM_WL_DEBUG 
PRIVATE S16  cmInitBtInfo ARGS((void));
#endif

#ifdef SS_USE_ICC_MEMORY
#ifdef T2K_MEM_LEAK_DBG
PRIVATE S16  cmIccAlloc ARGS((Void *regionCb, Size *size, U32 flags, Data **ptr, char*, U32));
PRIVATE S16  cmIccFree ARGS((Void *regionCb, Data *ptr, Size size,char*, U32));
PRIVATE S16  cmIccAllocWithLock ARGS((Void *regionCb, Size *size, U32 flags, Data **ptr, char*, U32));
PRIVATE S16  cmIccFreeWithLock ARGS((Void *regionCb, Data *ptr, Size size,char*, U32));
PUBLIC void InsertToT2kMemLeakInfo ARGS((U32 address, U32 size, U32 lineNo, char* fileName));
void RemoveFromT2kMemLeakInfo ARGS((U32 address, char *file, U32 line));
PRIVATE U32 getT2kMemLeakIndex ARGS((U32 address));
#else
PRIVATE S16  cmIccAlloc ARGS((Void *regionCb, Size *size, U32 flags, Data **ptr));
PRIVATE S16  cmIccFree ARGS((Void *regionCb, Data *ptr, Size size));
PRIVATE S16  cmIccAllocWithLock ARGS((Void *regionCb, Size *size, U32 flags, Data **ptr));
PRIVATE S16  cmIccFreeWithLock ARGS((Void *regionCb, Data *ptr, Size size));
#endif
#else  /* SS_USE_ICC_MEMORY */
PRIVATE S16  cmDynAllocWithLock ARGS((Void   *regionCb,Size   *size,U32     flags,Data  **ptr));
PRIVATE S16  cmDynFreeWithLock ARGS((Void   *regionCb,Data   *ptr, Size    size));
PRIVATE S16  cmDynAlloc ARGS((Void   *regionCb,Size   *size,U32     flags,Data  **ptr));
PRIVATE S16  cmDynFree ARGS((Void   *regionCb,Data   *ptr, Size    size));
#endif /* SS_USE_ICC_MEMORY */


#ifdef T2K_MEM_LEAK_DBG
PRIVATE S16 cmAllocWL ARGS((Void *regionCb, Size *size, U32 flags, Data **ptr,char*,U32));
PRIVATE S16 cmFreeWL  ARGS((Void *regionCb, Data *ptr, Size size,char*, U32));

PRIVATE S16 cmAlloc ARGS((Void *regionCb, Size *size, U32 flags, Data **ptr,char*,U32));
PRIVATE S16 cmFree  ARGS((Void *regionCb, Data *ptr, Size size,char*, U32));
#else
PRIVATE S16 cmAllocWL ARGS((Void *regionCb, Size *size, U32 flags, Data **ptr));
PRIVATE S16 cmFreeWL  ARGS((Void *regionCb, Data *ptr, Size size));

PRIVATE S16 cmAlloc ARGS((Void *regionCb, Size *size, U32 flags, Data **ptr));
PRIVATE S16 cmFree  ARGS((Void *regionCb, Data *ptr, Size size));
#endif
#ifdef T2K_MEM_LEAK_DBG
PRIVATE S16 cmAllocWL ARGS((Void *regionCb, Size *size, U32 flags, Data **ptr,char*,U32));
PRIVATE S16 cmFreeWL  ARGS((Void *regionCb, Data *ptr, Size size,char*, U32));
#else
PRIVATE S16 cmAllocWL ARGS((Void *regionCb, Size *size, U32 flags, Data **ptr));
PRIVATE S16 cmFreeWL  ARGS((Void *regionCb, Data *ptr, Size size));
#endif
PRIVATE S16 cmHeapAlloc ARGS((CmMmHeapCb *heapCb, Data **ptr, Size *size));
PRIVATE S16 cmHeapFree  ARGS((CmMmHeapCb *heapCb, Data *ptr, Size size));
PRIVATE S16 cmCtl   ARGS((Void *regionCb, Event event, SMemCtl *memCtl));
PRIVATE Void cmMmHeapInit ARGS((Data *memAddr, CmMmHeapCb *heapCb, Size size));
#if 0
#ifdef SS_HISTOGRAM_SUPPORT
#ifdef SSI_DEBUG_LEVEL1
PRIVATE S16 cmAlloc ARGS((Void *regionCb, Size *size, U32 flags, Data **ptr, 
            U32 memType, U32 line, U8 *fileName, U8 entId, Bool hstReg));
PRIVATE S16 cmHeapAlloc ARGS((CmMmHeapCb *heapCb, Data **ptr, Size *size, U32 memType, U32 line, U8 *fileName, U8 entId, Bool hstReg));
/*cm_mem_c_001.main_20-added new functionto allocate memory from new region*/
#else
PRIVATE S16 cmHeapAlloc ARGS((CmMmHeapCb *heapCb, Data **ptr, Size *size,
       U32 line, U8 *fileName, U8 entId, Bool hstReg));
PRIVATE S16 cmAlloc ARGS((Void *regionCb, Size *size, U32 flags, Data **ptr, 
            U32 line, U8 *fileName, U8 entId, Bool hstReg));
#endif /* SSI_DEBUG_LEVEL1 */

PRIVATE S16 cmFree  ARGS((Void *regionCb, Data *ptr, Size size, U32 line, 
            U8 *fileName, U8 entId, Bool hstReg));

PRIVATE S16 cmHeapFree  ARGS((CmMmHeapCb *heapCb, Data *ptr, Size size,
            U32 line, U8 *fileName, U8 entId, Bool hstReg));
#else /* no histogram support */
/* cm_mem_c_001.main_12 - prototype is changed to accept memType(static/dynamic) */
#ifdef SSI_DEBUG_LEVEL1
PRIVATE S16 cmHeapAlloc ARGS((CmMmHeapCb *heapCb, Data **ptr, Size *size, U32 memType));
#else
PRIVATE S16 cmHeapAlloc ARGS((CmMmHeapCb *heapCb, Data **ptr, Size *size));
#endif /* SSI_DEBUG_LEVEL1 */
PRIVATE S16 cmHeapFree  ARGS((CmMmHeapCb *heapCb, Data *ptr, Size size));
/*  cm_mem_c_001.main_15 :Additions */
#ifdef SSI_DEBUG_LEVEL1
PRIVATE S16 cmAlloc ARGS((Void *regionCb, Size *size, U32 flags, Data **ptr, U32 memType));
#else
PRIVATE S16 cmAlloc ARGS((Void *regionCb, Size *size, U32 flags, Data **ptr));
#endif /* SSI_DEBUG_LEVEL1 */
PRIVATE S16 cmFree  ARGS((Void *regionCb, Data *ptr, Size size));
#endif /* SS_HISTOGRAM_SUPPORT */

/*cm_mem_c_001.main_23 Removed support of SSI_DEBUG_LEVEL1 and SS_HISTOGRAM_SUPPORT for SS_FAP*/
#ifdef SS_FAP
PRIVATE S16 cmAllocWL ARGS((Void *regionCb, Size *size, U32 flags, Data **ptr));
PRIVATE S16 cmFreeWL  ARGS((Void *regionCb, Data *ptr, Size size));
#endif


PRIVATE Void cmMmBktInit ARGS((Data **memAddr, CmMmRegCb *regCb, 
                              CmMmRegCfg *cfg, U16 bktIdx, U16 *lstMapIdx));

/* cm_mem_c_001.main_12 - addition of protoypes for sanity check and hash list functions */
#ifdef SSI_DEBUG_LEVEL1
PRIVATE S16 cmMmBktSanityChk ARGS((CmMmBkt *bkt));
PRIVATE S16 cmMmHeapSanityChk ARGS((CmMmHeapCb *heapCb));
PRIVATE S16 cmMmHashFunc ARGS((CmMmHashListCp *hashListCp, U32 key, U16 *idx ));
PRIVATE S16 cmMmHashListInit ARGS((CmMmHashListCp *hashListCp, U16 nmbBins,
                                  Region region, Pool pool));
PRIVATE S16 cmMmHashListDeinit ARGS((CmMmHashListCp *hashListCp, Region region, Pool pool));
PRIVATE S16 cmMmHashListInsert ARGS((CmMmHashListCp *hashListCp, U32 key));
#endif /* SSI_DEBUG_LEVEL1 */
/*   cm_mem_c_001.main_15 : Addtions */
#ifdef SS_HISTOGRAM_SUPPORT
PRIVATE S16 cmHstGrmAllocInsert ARGS((CmHstGrmHashListCp *hashListCp, U32 blkSz, U32 *reqSz, U32 line, U8 *fileName, U8 entId));
PRIVATE S16 cmHstGrmFreeInsert ARGS((CmHstGrmHashListCp* hashListCp, U32 blkSz, U32 line, U8 *fileName, U8 entId));
PRIVATE S16 cmHstGrmHashListInit ARGS((CmHstGrmHashListCp *hashListCp));
PRIVATE S16 cmHstGrmHashListDeInit ARGS((CmHstGrmHashListCp *hashListCp));
PRIVATE S16 cmHstGrmGetHashIdxAndKey ARGS((U8 *fileName, U32 line, U32 *binIdx, U32 *key));
PRIVATE S16 cmHstGrmFindEntry ARGS((CmHstGrmHashListCp *hashListCp, U32 key, U32 *binIdx, CmMemEntries **entry));
PRIVATE S16 cmHstGrmFillEntry ARGS((CmMemEntries *entry, U32 key, U32 line, U8 *fileName, U8 entId));
#endif /* SS_HISTOGRAM_SUPPORT */
#endif

/* cm_mem_c_001.main_22: Fixing warnings on GCC compiler */
#ifdef __cplusplus
}
#endif

/* public variable declarations */
#ifdef USE_PURE
Size avail_size;
#endif /* USE_PURE */
/*  cm_mem_c_001.main_15:Additions */
#ifdef SS_MEM_LEAK_STS 
MemUsrMdlStr   memUsrMdlStr[]=
{
   MEMRAW2STR(DEFAULT, STACK),
   MEMRAW2STR(tc, PDCP_LAYER),
   MEMRAW2STR(Tc, PDCP_LAYER),
   MEMRAW2STR(mg, GCP_LAYER),
   MEMRAW2STR(Mg, GCP_LAYER),
   {NULLP, NULLP}
};

MemLkCb memLkCb;
#endif /* SS_MEM_LEAK_STS */

/* cm_mem_c_008.104 - Addition for memory calculator tool */
#ifdef MEMCAL_DEBUG
PRIVATE Txt prntBuf[200];        /* print buffer */
PRIVATE U8 tryHeap=0;
#endif 

/* cm_mem_c_001.main_12 - addition for ssi enhancements prints */
/* cm_mem_c_001.main_20 Additions */
#if (defined(SSI_DEBUG_LEVEL1) || defined(SS_HISTOGRAM_SUPPORT))
#ifdef DEBUGP
PRIVATE Txt dbgPrntBuf[200];        /* print buffer */
#endif /* DEBUGP */
#endif /*SSI_DEBUG_LEVEL1 || SS_HISTOGRAM_SUPPORT */

#ifdef T2K_MEM_LEAK_DBG
 /* convert to decimal (0x(end_addr - start_addr)>>8)*2 */
#define T2K_MEM_LEAK_INFO_TABLE_SIZE 3670014  /* New Sercomm Board*/
//#define T2K_MEM_LEAK_INFO_TABLE_SIZE 3145726 /*Old Sercomm Board*/
   /* 0x94200000 is the starting address allocated by ICC,
    * whenever that changes pleasse change here */
//#define T2K_MEM_LEAK_START_ADDR 0x9d400000 /*Old Sercomm Board*/
#define T2K_MEM_LEAK_START_ADDR 0x9d200000  /*New Sercomm Board*/
#endif

U32 num_times = 0;
EXTERN pthread_t tmpRegTidMap[20];
#if 0
EXTERN pthread_t tmpMainTid;
#endif
extern Bool g_usettitmr;
PUBLIC void DumpLayersDebugInformation()
{
   DumpSSIDemandQDebugInformation();
   /* dump layers information only after we start receiving the TTIs */
   if(g_usettitmr)
   {
#ifdef L2_L3_SPLIT     
      if (clusterMode == RADIO_CLUSTER_MODE)
      {
         DumpRLCDlDebugInformation();

#ifndef UL_RLC_NET_CLUSTER
         DumpRLCUlDebugInformation();
#endif
         printSchCellInfo();
      }
      else
      {
#ifdef UL_RLC_NET_CLUSTER
         DumpRLCUlDebugInformation();
#endif
         DumpPDCPDlDebugInformation();
         DumpPDCPUlDebugInformation();   
      }
#else
      DumpPDCPDlDebugInformation();
      DumpPDCPUlDebugInformation();   
      DumpRLCDlDebugInformation();
      DumpRLCUlDebugInformation();
      printSchCellInfo();
#endif      
   }
}

/* private variable declarations */
/*
*
*       Fun:   cmMmStatBktInit
*
*       Desc:  Initialize the bucket and the map table.
*
*
*       Ret:   ROK     - successful, 
*              RFAILED - unsuccessful.
*
*       Notes: This function is called by the cmMmRegInit. 
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PRIVATE Void cmMmStatBktInit
(
Data      **memAddr,
CmMmRegCb  *regCb,
CmMmRegCfg *cfg,
U16         bktIdx,
U16        *lstMapIdx
)
#else
PRIVATE Void cmMmStatBktInit (memAddr, regCb, cfg, bktIdx, lstMapIdx)
Data      **memAddr;
CmMmRegCb  *regCb;
CmMmRegCfg *cfg;
U16         bktIdx;
U16        *lstMapIdx;
#endif
{
   U32   cnt;
   U16   idx;
   U32   numBlks;
   Size  size;
/* cm_mem_c_001.main_12 - addition for temporary variables */
#ifdef SSI_DEBUG_LEVEL1
   CmMmBlkHdr **nextBlk;
   U32 sigCnt;
#else
   Data **next;
#endif /* SSI_DEBUG_LEVEL1 */

   TRC2(cmMmStatBktInit);


   size = cfg->bktCfg[bktIdx].size; 
   numBlks = cfg->bktCfg[bktIdx].numBlks; 

/* cm_mem_c_001.main_12 - addition for header initialization */
#ifdef SSI_DEBUG_LEVEL1
   /* Reset the next block pointer */
   regCb->bktTbl[bktIdx].nextBlk = NULLP;

   /* Initialize the link list of the memory block */
   nextBlk = &(regCb->bktTbl[bktIdx].nextBlk);

   for (cnt = 0; cnt < numBlks; cnt++)
   {
      *nextBlk = (CmMmBlkHdr *)*memAddr;

      /* initialize the memory block header */
      for (sigCnt=0; sigCnt < CMM_TRAMPLING_SIGNATURE_LEN; sigCnt++)
      {
         (*nextBlk)->trSignature[sigCnt] = 0xAB;
      }

      CMM_SET_FREE_FLAG((*nextBlk)->memFlags);
      (*nextBlk)->requestedSize = 0;
      *memAddr = (Data *)((*memAddr) + ((sizeof(CmMmBlkHdr)) + size));
      nextBlk = &((*nextBlk)->nextBlk);
   }

   *nextBlk = NULLP;

#else
   /* Initialize the bucket linked list */

   /* Reset the next pointer */
   regCb->bktTbl[bktIdx].next = NULLP; 

   /* Initialize the link list of the memory block */
   next = &(regCb->bktTbl[bktIdx].next); 
   for (cnt = 0; cnt < numBlks; cnt++)
   {
      *next     = *memAddr;
      next      = (CmMmEntry **)(*memAddr);
      *memAddr  = (*memAddr) + size;

   }
   *next = NULLP;

#endif /* SSI_DEBUG_LEVEL1 */

   /* Initialize the Map entry */
   idx = size / cfg->bktQnSize;

   /* 
    * Check if the size is multiple of quantum size. If not we need to initialize
    * one more map table entry.
    */ 
   if(size % cfg->bktQnSize)
   {
      idx++;
   }
   
   while ( *lstMapIdx < idx)
   {
      regCb->mapTbl[*lstMapIdx].bktIdx = bktIdx;

#if (ERRCLASS & ERRCLS_DEBUG)
      regCb->mapTbl[*lstMapIdx].numReq     = 0;
      regCb->mapTbl[*lstMapIdx].numFailure = 0;
#endif

      (*lstMapIdx)++;
   } 

   /* Initialize the bucket structure */
   regCb->bktTbl[bktIdx].size     = size; 
   regCb->bktTbl[bktIdx].numBlks  = numBlks; 
   regCb->bktTbl[bktIdx].numAlloc = 0;
   regCb->bktTbl[bktIdx].maxAlloc = 0;

   /* Update the total bucket size */
/* cm_mem_c_001.main_12 - addition for considering the header size */
#ifdef SSI_DEBUG_LEVEL1
   regCb->bktSize += ((size + sizeof(CmMmBlkHdr)) * numBlks);
#else
   regCb->bktSize += (size * numBlks); 
#endif /* SSI_DEBUG_LEVEL1 */

   regCb->bktTbl[bktIdx].bktFailCnt = 0;
   regCb->bktTbl[bktIdx].bktNoFitCnt = 0;

/* cm_mem_c_001.main_12 - addition for statistics related variable initialization */
#ifdef SSI_DEBUG_LEVEL1
   /* Initialize other required pointers */
   regCb->bktTbl[bktIdx].bktStartPtr = (Data *)(regCb->bktTbl[bktIdx].nextBlk);
   regCb->bktTbl[bktIdx].numAllocAttempts = 0;
   regCb->bktTbl[bktIdx].numDeallocAttempts = 0;
   regCb->bktTbl[bktIdx].staticMemUsed = 0;
   regCb->bktTbl[bktIdx].dynamicMemUsed = 0;
   regCb->bktTbl[bktIdx].trampleCount = 0;
#endif /*SSI_DEBUG_LEVEL1*/
/*  cm_mem_c_001.main_15 : Additions */
#ifdef SS_HISTOGRAM_SUPPORT 
   /* Initialise the memory histogram hash list */
   cmHstGrmHashListInit(&(regCb->bktTbl[bktIdx].hstGrmHashListCp));
#endif /* SS_HISTOGRAM_SUPPORT */

   RETVOID;
} /* end of cmMmStatBktInit */

/*
*
*       Fun:   cmMmStatRegInit
*
*       Desc:  Configure the memory region for allocation. The function 
*              registers the memory region with System Service by calling
*              SRegRegion.
*
*
*       Ret:   ROK     - successful, 
*              RFAILED - unsuccessful.
*
*       Notes: The memory owner calls this function to initialize the memory 
*              manager with the information of the memory region. Before 
*              calling this function, the memory owner should allocate memory 
*              for the memory region. The memory owner should also provide the 
*              memory for the control block needed by the memory manager. The 
*              memory owner should allocate the memory for the region control 
*              block as cachable memory. This may increase the average 
*              throughput in allocation and deallocation as the region control
*              block is mostly accessed by the CMM.
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PUBLIC S16 cmMmStatRegInit
(
Region       region,
CmMmRegCb   *regCb,
CmMmRegCfg  *cfg
)
#else
PUBLIC S16 cmMmStatRegInit(region, regCb, cfg)
Region       region;
CmMmRegCb   *regCb;
CmMmRegCfg  *cfg;
#endif
{
   Data *memAddr;
   U16   bktIdx;
   U16   lstMapIdx;

#if (ERRCLASS & ERRCLS_INT_PAR)
   Size  lstQnSize;
   Size  bktBlkSize;
	Txt   errMsg[256] = {'\0'};
#endif

   TRC2(cmMmRegInit);

#if (ERRCLASS & ERRCLS_INT_PAR)

   /* error check on parameters */
   if ((regCb == NULLP) || (cfg == NULLP)) 
   {
      RETVALUE(RFAILED);
   }
   
   /* Error check on the configuration fields */
   if ((!cfg->size) || (cfg->vAddr == NULLP) || 
        (cfg->numBkts > CMM_MAX_BKT_ENT)) 
   {
      RETVALUE(RFAILED);
   }
   /* Check if the quantum size is power of 2 */
   if ((cfg->numBkts) &&
       ((cfg->bktQnSize - 1) & (cfg->bktQnSize)))
   {
      /* cm_mem_c_001.main_20 Addition */
		sprintf(errMsg,"\n cmMmRegInit() failed, check if BktQuantum size might not be power of 2 \n");
		SPrint(errMsg);
      RETVALUE(RFAILED);
   }

   /* 
    * Check if the size of the memory region is enough, whether bucket sizes
    * are multiples of quantumn size, and also whether two consecutive buckets
    *  falls within same quanta.
    */
   lstQnSize      = cfg->bktQnSize;
   regCb->bktSize = 0;

   for ( bktIdx =0; bktIdx < cfg->numBkts; bktIdx++)
   {
      /* check if bucket size is mutiple of quantum size */
      if (cfg->bktCfg[bktIdx].size % cfg->bktQnSize)
      {
          /* cm_mem_c_001.main_20 Addition */
/*cm_mem_c_001.main_23 Fix for specifier mismatch warnings in 64BIT compilation*/          
#ifdef ALIGN_64BIT          
			 sprintf(errMsg,"\n cmMmRegInit() failed, Bkt:%d size:%u not multiple of quantum size:%u\
			 				\n",bktIdx,cfg->bktCfg[bktIdx].size,cfg->bktQnSize);
#else                     
			 sprintf(errMsg,"\n cmMmRegInit() failed, Bkt:%d size:%lu not multiple of quantum size:%lu\
			 				\n",bktIdx,cfg->bktCfg[bktIdx].size,cfg->bktQnSize);
#endif                     
			 SPrint(errMsg);
          RETVALUE(RFAILED);
      }

      if ((bktBlkSize = cfg->bktCfg[bktIdx].size) < lstQnSize)
      {
         /* 
          * Two consecutive buckets are not separated by quantum size.
          */
          /* cm_mem_c_001.main_20 Addition */
			 sprintf(errMsg,"\n cmMmRegInit() failed, Two consecutive buckets are not separated by quantum size \n");
			 SPrint(errMsg);
          RETVALUE(RFAILED);
      }
      /* cm_mem_c_001.main_20 Addition */
		if (((cfg->bktCfg[bktIdx].size) /\
				cfg->bktQnSize) > CMM_MAX_MAP_ENT)
		{
   		  /* Error check whether the size of the mapping table is sufficient */
/*cm_mem_c_001.main_23 Fix for specifier mismatch warnings in 64BIT compilation*/          
#ifdef ALIGN_64BIT          
			  sprintf(errMsg,"\n cmMmRegInit() failed, check maxBucketSize/BktQuantumSize(%u)\
				\n	should be less than CMM_MAX_MAP_ENT:%d \n",cfg->bktQnSize,CMM_MAX_MAP_ENT);
#else                     
			  sprintf(errMsg,"\n cmMmRegInit() failed, check maxBucketSize/BktQuantumSize(%lu)\
				\n	should be less than CMM_MAX_MAP_ENT:%d \n",cfg->bktQnSize,CMM_MAX_MAP_ENT);
#endif                     
				SPrint(errMsg);
		  	  RETVALUE(RFAILED);
		}


      regCb->bktSize += (cfg->bktCfg[bktIdx].size * 
                         cfg->bktCfg[bktIdx].numBlks); 
    
      if (regCb->bktSize > cfg->size)
      {
         /* Size of the memory region is less than the required size */
		
			sprintf(errMsg,"\n cmMmRegInit() failed, Size of the memory region is less than the required size \n");
			SPrint(errMsg);
         RETVALUE(RFAILED);
      }

      lstQnSize = ((bktBlkSize / cfg->bktQnSize) + 1) * cfg->bktQnSize;
   }

#endif

   /* Initialize the region control block */
   regCb->region = region;
   regCb->regInfo.regCb = regCb;
   regCb->regInfo.start = cfg->vAddr;
   regCb->regInfo.size  = cfg->size;

#ifdef USE_PURE
   avail_size = cfg->size;
#endif /* USE_PURE */

   if ( cfg->chFlag & CMM_REG_OUTBOARD)
   {
      /* Out_of_board memory */
      regCb->regInfo.flags = CMM_REG_OUTBOARD;
   } 
  else
   {
      regCb->regInfo.flags = 0;
   }


#if 1
   if(region == SS_MAX_REGS - 1)
   {
      regCb->regInfo.alloc = cmAlloc;
      regCb->regInfo.free  = cmFree;
      regCb->regInfo.ctl   = cmCtl;   
   }
   else
   {
      regCb->regInfo.alloc = cmAllocWL;
      regCb->regInfo.free  = cmFreeWL;
      regCb->regInfo.ctl   = cmCtl;   
   }
#else
   regCb->regInfo.alloc = cmAlloc;
   regCb->regInfo.free  = cmFree;
   regCb->regInfo.ctl   = cmCtl;
#endif

   /* Initialize the physical address */
   if ((regCb->chFlag = cfg->chFlag) & CMM_REG_PHY_VALID)
   {
      regCb->pAddr = cfg->pAddr;
   }

   /* Initial address of the memory region block */
   memAddr    = cfg->vAddr;

   /* Initialize the fields related to the bucket pool */
   regCb->bktMaxBlkSize = 0;
   regCb->bktSize       = 0; 

   if (cfg->numBkts)
   {
      /* Last bucket has the maximum size */
      regCb->bktMaxBlkSize = cfg->bktCfg[cfg->numBkts - 1].size;
   
      /* Get the power of the bktQnSize */
      regCb->bktQnPwr = 0; 
      while( !((cfg->bktQnSize >> regCb->bktQnPwr) & 0x01))
      {
         regCb->bktQnPwr++;
      }
    
      /* Initilaize the bktIndex of the map entries to FF */
      for ( lstMapIdx = 0; lstMapIdx < CMM_MAX_MAP_ENT; lstMapIdx++)
      {
         regCb->mapTbl[lstMapIdx].bktIdx = 0xFF;
      }
  
      lstMapIdx = 0;
      for ( bktIdx = 0; bktIdx < cfg->numBkts; bktIdx++)
      {
         /* Allocate the lock for the bucket pool */
         cmMmStatBktInit( &memAddr, regCb, cfg, bktIdx, &lstMapIdx); 
      }

      /* Used while freeing the bktLock in cmMmRegDeInit */
      regCb->numBkts = cfg->numBkts;
   }

   /* 
    * Initialize the heap pool if size the memory region region is more
    * than the size of the bucket pool 
    */
    regCb->heapSize = 0;
    regCb->heapFlag = FALSE;

    /* Align the memory address */
    memAddr = (Data *)(PTRALIGN(memAddr));

    regCb->heapSize = cfg->vAddr + cfg->size - memAddr;  

    /* 
     * Round the heap size so that the heap size is multiple 
     * of CMM_MINBUFSIZE 
     */
    regCb->heapSize -= (regCb->heapSize %  CMM_MINBUFSIZE);

    if (regCb->heapSize)
    {
       /* Allocate the lock for the heap pool */
       regCb->heapFlag = TRUE;
       cmMmHeapInit(memAddr, &(regCb->heapCb), regCb->heapSize); 
    }

    /* Call SRegRegion to register the memory region with SSI */
    if (SRegRegion(region, &regCb->regInfo) != ROK)
    {
       RETVALUE(RFAILED);
    }

    RETVALUE(ROK);
} /* end of cmMmRegInit*/

#if 0
/*
*
*       Fun:   ssPutDynBufSet
*
*       Desc:  Puts the set of dynamic buffers into the global region
*
*
*       Ret:   ROK     - successful, 
*              RFAILED - unsuccessful.
*
*       Notes: 
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PUBLIC S16 ssPutDynBufSet
(
U8                 bktIdx,
CmMmBktLstCb      *bktLstCb
)
#else
PUBLIC S16 ssPutDynBufSet(bktIdx, bktLstCb)
U8                 bktIdx;
CmMmBktLstCb      *bktLstCb;
#endif
{
   CmMmGlobRegCb  *globReg;
   CmMmDynBktCb   *bktCb;

   TRC1(ssPutDynBufSet);

   globReg = &osCp.globRegCb;

   if(bktIdx > CMM_MAX_BKT_ENT)
   {
      RETVALUE(RFAILED);
   }

   bktCb = &(globReg->bktTbl[bktIdx]);

   /* Lock the global region first */
   SLock(&(globReg->regLock));

   cmLListAdd2Tail(&(bktCb->listBktSet), bktLstCb);

   SUnlock(&(globReg->regLock));

   RETVALUE(ROK);
}

/*
*
*       Fun:   ssGetDynBufSet
*
*       Desc:  Gets the set of dynamic buffers into the global region
*
*
*       Ret:   ROK     - successful, 
*              RFAILED - unsuccessful.
*
*       Notes: 
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PUBLIC S16 ssGetDynBufSet
(
U8                  bktIdx,
CmMmBktLstCb      **bktLstCb
)
#else
PUBLIC S16 ssGetDynBufSet(bktIdx, bktLstCb)
U8                  bktIdx;
CmMmBktLstCb      **bktLstCb;
#endif
{
   CmMmGlobRegCb  *globReg;
   CmMmDynBktCb   *bktCb;
   CmLList        *lstNode;

   TRC1(ssGetDynBufSet);

   globReg = &osCp.globRegCb;

   if(bktIdx > CMM_MAX_BKT_ENT)
   {
      RETVALUE(RFAILED);
   }

   *bktLstCb = NULLP;
   bktCb = &(globReg->bktTbl[bktIdx]);

   /* Lock the global region first */
   SLock(&(globReg->regLock));

   lstNode = cmLListFirst(&(bktCb->listBktSet));

   if(lstNode == NULLP)
   {
      SUnlock(&(globReg->regLock));
      RETVALUE(RFAILED);
   }

   cmLListDelFrm(&(bktCb->listBktSet), lstNode);
   SUnlock(&(globReg->regLock));

   *bktLstCb = (CmMmBktLstCb *)lstNode->node;

   RETVALUE(ROK);
}
#endif


/*
*
*       Fun:   cmMmGlobRegInit
*
*       Desc:  Configure the memory region for allocation. The function 
*              registers the memory region with System Service by calling
*              SRegRegion.
*
*
*       Ret:   ROK     - successful, 
*              RFAILED - unsuccessful.
*
*       Notes: 
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PUBLIC S16 cmMmGlobRegInit
(
CmMmGlobRegCb   *regCb
)
#else
PUBLIC S16 cmMmGlobRegInit(regCb)
CmMmGlobRegCb   *regCb;
#endif
{
   Data **memAddr;
   Data **next;
   U16   bktIdx;
   U16   bucketSetSize;
   U16   cnt;
   Size  size;
   CmMmBlkSetElement *blkLstElem;
   U16   numBlks;

#if (ERRCLASS & ERRCLS_INT_PAR)
   Size  lstQnSize;
   Size  bktBlkSize;
	Txt   errMsg[256] = {'\0'};
#endif

   TRC2(cmMmGlobRegInit);

#ifdef SS_MEM_WL_DEBUG 
   if (cmInitBtInfo() == RFAILED)
   {
     RETVALUE(RFAILED);
   }
#endif
   for ( bktIdx = 0; bktIdx < regCb->numBkts; bktIdx++)
   {
      /* Initial address of the memory region block */
      memAddr    = &regCb->bktTbl[bktIdx].startAddr;
      bucketSetSize  = regCb->bktTbl[bktIdx].bucketSetSize;
      size = regCb->bktTbl[bktIdx].size;

      /* Initialize the bucket linked list */
      cmLListInit(&regCb->bktTbl[bktIdx].listValidBktSet);
      cmLListInit(&regCb->bktTbl[bktIdx].listFreeBktSet);
      SInitLock(&(regCb->bktTbl[bktIdx].bucketLock), SS_LOCK_MUTEX);

      /* Initialize the link list of the memory block */
      next = &(regCb->bktTbl[bktIdx].next); 

      numBlks = regCb->bktTbl[bktIdx].numBlks;
      for (cnt = 1; cnt <= numBlks; cnt++)
      {
         *next     = *memAddr;
         next      = (CmMmEntry **)(*memAddr);
         *memAddr  = (*memAddr) + size;

         /* Maintain the list Cb */
         if(!(cnt % bucketSetSize))
         {
            blkLstElem = calloc(1, sizeof(CmMmBlkSetElement));
            blkLstElem->nextBktPtr = (CmMmEntry *)regCb->bktTbl[bktIdx].next;
            blkLstElem->numFreeBlks = bucketSetSize;
            blkLstElem->memSetNode.node = (PTR)blkLstElem;
            cmLListAdd2Tail((&regCb->bktTbl[bktIdx].listValidBktSet), (&blkLstElem->memSetNode));
            next = &(regCb->bktTbl[bktIdx].next);
         }
      }
      *next = NULLP;
   }

    RETVALUE(ROK);
} /* end of cmMmGlobRegInit*/

#ifdef SS_USE_ICC_MEMORY
/*
*
*       Fun:   cmIccAllocWithLock
*
*       Desc:  Allocate a memory block for use by dynamic buffers.
*              This handler uses the lock to avoid the two thread
*              trying to allocate the memory at same time. This
*              handler must be used only for non-data plane thread
*              it causes delay due to lock.
*
*
*       Ret:   ROK     - successful
*              RFAILED - unsuccessful.
*
*       Notes: 
*
*       File:  cm_mem_wl.c
*
*/
#ifdef T2K_MEM_LEAK_DBG
#ifdef ANSI
PRIVATE S16  cmIccAllocWithLock
(
Void   *regionCb,    /* Pointer to a region */
Size   *size,        /* size needs to be allocated */
U32     flags,       /* Flags used */
Data  **ptr,          /* Reference to pointer for which need to be allocate */
char *file,
U32 line
)
#endif
#else
#ifdef ANSI
PRIVATE S16  cmIccAllocWithLock
(
Void   *regionCb,    /* Pointer to a region */
Size   *size,        /* size needs to be allocated */
U32     flags,       /* Flags used */
Data  **ptr          /* Reference to pointer for which need to be allocate */
)
#else
PRIVATE S16  cmIccAllocWithLock(regionCb, size, flags, ptr)
Void   *regionCb;    /* Pointer to a region */
Size   *size;        /* size needs to be allocated */
U32     flags;       /* Flags used */
Data  **ptr;         /* Reference to pointer for which need to be allocate */
#endif
#endif
{
   CmMmDynRegCb        *regCb;
   Data                *memPtr;

   TRC2(cmIccAllocWithLock);

   regCb = (CmMmDynRegCb *)regionCb;

   if((SLock(&iccAllocFreeLock)) != ROK)
   {
      printf("cmIccAllocWithLock: Failed to get the ICC lock\n");
      RETVALUE(RFAILED);
   }

   memPtr = (Data *)TL_Alloc(regCb->iccHdl, *size);

   if((SUnlock(&iccAllocFreeLock)) != ROK)
   {
      printf("cmIccAllocWithLock: Failed to unlock the ICC lock\n");
      RETVALUE(RFAILED);
   }

   if ((memPtr) == NULLP)
   {
      int *p = 0;
      printf("\n*****************Region(%d) is out of memory size = %ld******************\n",regCb->region, *size);
      printf("Exiting...\n");
      /* crash here */
      *p = 10;
   }

#ifdef T2K_MEM_LEAK_DBG
   if(((U32)(memPtr - T2K_MEM_LEAK_START_ADDR) & 0xff) != 0)
   {
      printf("Address returned is %p size = %ld\n",memPtr,*size);
   }

   InsertToT2kMemLeakInfo((U32)memPtr,*size,line,file);
#endif
   *ptr = memPtr;

   RETVALUE(ROK);

} /* end of cmIccAllocWithLock */

/*
*
*       Fun:   cmIccFreeWithLock
*
*       Desc:  Return the Dynamic memory block for the memory region.
*              This handler uses the lock to avoid the two thread
*              trying to free the memory at same time. This
*              handler must be used only for non-data plane thread
*              it causes delay due to lock.
*
*       Ret:   ROK     - successful
*              RFAILED - unsuccessful.
*
*       Notes:
*
*
*       File:  cm_mem_wl.c
*
*/
#ifdef T2K_MEM_LEAK_DBG
#ifdef ANSI
PRIVATE S16  cmIccFreeWithLock
(
Void   *regionCb,   /* Pointer to region cb */
Data   *ptr,        /* Memory block needs to be freed */
Size    size,        /* Size of the block */
char *file,
U32 line
)
#endif
#else
#ifdef ANSI
PRIVATE S16  cmIccFreeWithLock
(
Void   *regionCb,   /* Pointer to region cb */
Data   *ptr,        /* Memory block needs to be freed */
Size    size        /* Size of the block */
)
#else
PRIVATE S16  cmIccFreeWithLock(regionCb, ptr, size)
Void   *regionCb;   /* Pointer to region cb */
Data   *ptr;        /* Memory block needs to be freed */
Size    size;       /* Size of the block */
#endif
#endif
{
   CmMmDynRegCb       *regCb;

   TRC2(cmIccFreeWithLock);

   regCb = (CmMmDynRegCb *)regionCb;

   if((SLock(&iccAllocFreeLock)) != ROK)
   {
      printf("cmIccFreeWithLock: Failed to get the ICC lock\n");
      RETVALUE(RFAILED);
   }

#ifdef T2K_MEM_LEAK_DBG
   RemoveFromT2kMemLeakInfo((U32)ptr - ((U32)ptr % 512),file,line);

#endif
   TL_Free(regCb->iccHdl, ptr);

   if((SUnlock(&iccAllocFreeLock)) != ROK)
   {
      printf("cmIccFreeWithLock: Failed to unlock the ICC lock\n");
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* end of cmIccFree */

/*
*
*       Fun:   cmIccAlloc
*
*       Desc:  Allocate a memory block for use by dynamic buffers
*
*
*       Ret:   ROK     - successful
*              RFAILED - unsuccessful.
*
*       Notes: 
*
*       File:  cm_mem_wl.c
*
*/
#ifdef T2K_MEM_LEAK_DBG
#ifdef ANSI
PRIVATE S16  cmIccAlloc
(
Void   *regionCb,    /* Pointer to a region */
Size   *size,        /* size needs to be allocated */
U32     flags,       /* Flags used */
Data  **ptr,          /* Reference to pointer for which need to be allocate */
char *file,
U32 line
)
#else
#endif
#else
#ifdef ANSI
PRIVATE S16  cmIccAlloc
(
Void   *regionCb,    /* Pointer to a region */
Size   *size,        /* size needs to be allocated */
U32     flags,       /* Flags used */
Data  **ptr          /* Reference to pointer for which need to be allocate */
)
#else
PRIVATE S16  cmIccAlloc(regionCb, size, flags, ptr)
Void   *regionCb;    /* Pointer to a region */
Size   *size;        /* size needs to be allocated */
U32     flags;       /* Flags used */
Data  **ptr;         /* Reference to pointer for which need to be allocate */
#endif

#endif
{
   CmMmDynRegCb        *regCb;
   Data                *memPtr;

   TRC2(cmIccAlloc);

   regCb = (CmMmDynRegCb *)regionCb;

   memPtr = (Data *)TL_Alloc(regCb->iccHdl, *size);

   if ((memPtr) == NULLP)
   {
      int *p = 0;
      printf("\n*****************Region(%d) is out of memory size = %ld******************\n",regCb->region, *size);
      printf("Exiting...\n");
      /* crash here */
      *p = 10;
   }
#ifdef T2K_MEM_LEAK_DBG
   if(((U32)(memPtr - T2K_MEM_LEAK_START_ADDR) & 0xff) != 0)
   {
      printf("Address returned is %p size = %ld\n",memPtr,*size);
   }
  
   InsertToT2kMemLeakInfo((U32)memPtr,*size,line,file);
#endif
#ifdef YS_PHY_3_8_2
   *ptr = memPtr;/*TL_VA2TRUEVA(regCb->iccHdl, memPtr); */
#else
   *ptr = memPtr; /*TL_VA2TRUEVA(regCb->iccHdl, memPtr); */
#endif

   RETVALUE(ROK);

} /* end of cmIccAlloc */

/*
*
*       Fun:   cmIccFree
*
*       Desc:  Return the Dynamic memory block for the memory region.
*
*
*       Ret:   ROK     - successful
*              RFAILED - unsuccessful.
*
*       Notes:
*
*
*       File:  cm_mem_wl.c
*
*/
#ifdef T2K_MEM_LEAK_DBG
PRIVATE S16  cmIccFree
(
Void   *regionCb,   /* Pointer to region cb */
Data   *ptr,        /* Memory block needs to be freed */
Size    size,        /* Size of the block */
char* file,
U32 line
)
#else
#ifdef ANSI
PRIVATE S16  cmIccFree
(
Void   *regionCb,   /* Pointer to region cb */
Data   *ptr,        /* Memory block needs to be freed */
Size    size        /* Size of the block */
)
#else
PRIVATE S16  cmIccFree(regionCb, ptr, size)
Void   *regionCb;   /* Pointer to region cb */
Data   *ptr;        /* Memory block needs to be freed */
Size    size;       /* Size of the block */
#endif
#endif
{
   CmMmDynRegCb       *regCb;
   TRC2(cmIccFree);

   regCb = (CmMmDynRegCb *)regionCb;

#ifdef YS_PHY_3_8_2
   // memPtr = TL_TRUEVA2VA(regCb->iccHdl, ptr);
   {
#ifdef T2K_MEM_LEAK_DBG
      RemoveFromT2kMemLeakInfo((U32)ptr - ((U32)ptr % 512),file,line);
#endif
   }

   TL_Free(regCb->iccHdl, ptr);
#else
/*   memPtr = TL_TRUEVA2VA(regCb->iccHdl, ptr); */
   memPtr = ptr;
   TL_Free(regCb->iccHdl, memPtr); 
#endif
   /*TL_Free(regCb->iccHdl, ptr);*/

#if 0
   if(a < 10)
   printf("FREE -ICC Addr Before PA2VA %x After PA2VA %x\n", memPtr, ptr);
   a++;
#endif

   RETVALUE(ROK);
} /* end of cmIccFree */

/*
*
*       Fun:   cmMmDynRegInit
*
*       Desc:  Configure the memory region for allocation. The function 
*              registers the memory region with System Service by calling
*              SRegRegion.
*
*
*       Ret:   ROK     - successful, 
*              RFAILED - unsuccessful.
*
*       Notes: The memory owner calls this function to initialize the memory 
*              manager with the information of the memory region. Before 
*              calling this function, the memory owner should allocate memory 
*              for the memory region. The memory owner should also provide the 
*              memory for the control block needed by the memory manager. The 
*              memory owner should allocate the memory for the region control 
*              block as cachable memory. This may increase the average 
*              throughput in allocation and deallocation as the region control
*              block is mostly accessed by the CMM.
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PUBLIC S16 cmMmDynRegInit
(
CmMmDynRegCb   *regCb
)
#else
PUBLIC S16 cmMmDynRegInit(regCb)
CmMmDynRegCb   *regCb;
#endif
{
   SRegInfo regInfo;
#ifdef T2200_2GB_DDR_CHANGES
   Txt      regIccStr[10] = {'\0'};
#else
   Txt      regIccStr[64] = {'\0'};
#endif

   TRC2(cmMmDynRegInit);

   /* Register the region/memory with ICC and get the handler for same. The id is starting
    * from region+1 as the zero is used by PHY code */
#ifdef T2200_2GB_DDR_CHANGES
   sprintf(regIccStr, "RxID=%d", (regCb->region + 1));
#else
#if 0
   sprintf(regIccStr, "RxID=%d", (regCb->region + 1));
#else
   //snprintf(regIccStr, sizeof(regIccStr), "QueueSize=%u RxID=%u", 1024, (regCb->region + 1));
   
  // snprintf(regIccStr, sizeof(regIccStr), "QueueSize=%u RxID=%u", 2048, (regCb->region + 1));
#ifdef L2_L3_SPLIT     
  if(clusterMode == RADIO_CLUSTER_MODE)  
  {
     if(regCb->region == 3)
     {/* ICC packet receiver */
         snprintf(regIccStr, sizeof(regIccStr), "QueueSize=%u RxID=%u", 4096, (regCb->region + 1));
     }else
     {
         //snprintf(regIccStr, sizeof(regIccStr), "QueueSize=%u RxID=%u", 2048, (regCb->region + 1));
        sprintf(regIccStr, "RxID=%d", (regCb->region + 1));
     }
  }else
  {/* NET CLUSTER */
     snprintf(regIccStr, sizeof(regIccStr), "QueueSize=%u RxID=%u", 2048, (regCb->region + 1));
     //snprintf(regIccStr, sizeof(regIccStr), "QueueSize=%u RxID=%u", 1024, (regCb->region + 1));
     //snprintf(regIccStr, sizeof(regIccStr), "RXID=%u", (regCb->region + 1));
  }
#else
#ifdef T2200_2GB_DDR_CHANGES
  sprintf(regIccStr, "RxID=%d", (regCb->region + 1));
#else
  sprintf (regIccStr, "queuesize=%d rxid=%d", 512, (regCb->region) + 1);
#endif
#endif
#endif
#endif
   printf(" %s \n",regIccStr);
   regCb->iccHdl = TL_Open(regIccStr, 0);

   /* Call SRegRegion to register the memory region with SSI */
   cmMemset((U8*)&regInfo, 0, sizeof(regInfo));

   /* Register the lock region for SS_MAX_REGS - 1 region */
   if((SS_MAX_REGS - 1) == regCb->region)
   {
      regInfo.alloc = cmIccAllocWithLock;
      regInfo.free  = cmIccFreeWithLock;
      regInfo.regCb = regCb;
      if((SInitLock((&iccAllocFreeLock), SS_LOCK_MUTEX)) != ROK)
      {
         printf("Failed to initialize the lock region lock\n");
      }
   }
   else
   {
      regInfo.alloc = cmIccAlloc;
      regInfo.free  = cmIccFree;
      regInfo.regCb = regCb;
   }

   if (SRegDynRegion(regCb->region, &regInfo) != ROK)
   {
      RETVALUE(RFAILED);
   }

    RETVALUE(ROK);
} /* end of cmMmDynRegInit*/

#else /* SS_USE_ICC_MEMORY */

/*
*
*       Fun:   cmMmDynRegInit
*
*       Desc:  Configure the memory region for allocation. The function 
*              registers the memory region with System Service by calling
*              SRegRegion.
*
*
*       Ret:   ROK     - successful, 
*              RFAILED - unsuccessful.
*
*       Notes: The memory owner calls this function to initialize the memory 
*              manager with the information of the memory region. Before 
*              calling this function, the memory owner should allocate memory 
*              for the memory region. The memory owner should also provide the 
*              memory for the control block needed by the memory manager. The 
*              memory owner should allocate the memory for the region control 
*              block as cachable memory. This may increase the average 
*              throughput in allocation and deallocation as the region control
*              block is mostly accessed by the CMM.
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PUBLIC S16 cmMmDynRegInit
(
CmMmDynRegCb   *regCb
)
#else
PUBLIC S16 cmMmDynRegInit(regCb)
CmMmDynRegCb   *regCb;
#endif
{
   Region region;
   U16    lstMapIdx;
   U16   cnt;
   Size  size;
   CmMmBlkSetElement *blkLstElem;
   SRegInfo regInfo;
   Size   bktQnSize = MT_BKTQNSIZE;
   U16    idx;
   U16    idx1;
   U16    numBkts;

   TRC2(cmMmDynRegInit);

   /* Initialize the region control block */
   region = regCb->region;
   numBkts = regCb->numBkts;

   /* Initilaize the bktIndex of the map entries to FF */
   for ( lstMapIdx = 0; lstMapIdx < CMM_MAX_MAP_ENT; lstMapIdx++)
   {
      regCb->mapTbl[lstMapIdx].bktIdx = 0xFF;
   }

   lstMapIdx = 0;

   for(cnt = 0; cnt < numBkts; cnt++)
   {
      /* Initialize the Map entry */
      size = regCb->bktTbl[cnt].size;
      idx = size / bktQnSize;
   
      /* 
       * Check if the size is multiple of quantum size. If not we need to initialize
       * one more map table entry.
       */ 
      if(size % bktQnSize)
      {
         idx++;
      }
   
      while ( lstMapIdx < idx)
      {
         regCb->mapTbl[lstMapIdx].bktIdx = cnt;
         lstMapIdx++;
      } 
   }

   regCb->bktQnPwr = 0; 

   while( !((bktQnSize >> regCb->bktQnPwr) & 0x01))
   {
      regCb->bktQnPwr++;
   }

   /* Initialize the bucket structure */
#if 0
   regCb->bktTbl[bktIdx].numAlloc = 0;
   regCb->bktTbl[bktIdx].maxAlloc = 0;

   /* Update the total bucket size */
   regCb->bktSize += (regCb->bktTbl[bktIdx].size * regCb->bktTbl[bktIdx].numBkt); 

   regCb->bktTbl[bktIdx].bktFailCnt = 0;
   regCb->bktTbl[bktIdx].bktNoFitCnt = 0;

   if(regCb->bktMaxBlkSize < regCb->bktTbl[bktIdx].size)
   {
      regCb->bktMaxBlkSize = regCb->bktTbl[bktIdx].size;
   }
#endif

   for(idx = 0; idx < numBkts; idx++)
   {
      regCb->bktTbl[idx].crntMemBlkSetElem = NULLP;

      for(idx1 = 0; idx1 < CMM_MAX_NUMBER_BKT_NODE; idx1++)
      {
          blkLstElem = calloc(1, sizeof(CmMmBlkSetElement));
          blkLstElem->memSetNode.node = (PTR)blkLstElem;
          cmLListAdd2Tail((&regCb->bktTbl[idx].memBlkSetElem), (&blkLstElem->memSetNode));
      }
   }

   /* Call SRegRegion to register the memory region with SSI */
   cmMemset((U8*)&regInfo, 0, sizeof(regInfo));
#if 1
   if((SS_MAX_REGS - 1) == regCb->region)
   {
      regInfo.alloc = cmDynAllocWithLock;
      regInfo.free  = cmDynFreeWithLock;
      if((SInitLock((&dynAllocFreeLock), SS_LOCK_MUTEX)) != ROK)
      {
         printf("Failed to initialize the lock region lock\n");
      }
   }
   else
#endif
   {
#if 0
      static dynLockCreated;
      regInfo.alloc = cmDynAllocWithLock;
      regInfo.free  = cmDynFreeWithLock;
      if ( dynLockCreated == 0)
      {
         if((SInitLock((&dynAllocFreeLock), SS_LOCK_MUTEX)) != ROK)
         {
            printf("Failed to initialize the lock region lock\n");
         }
         dynLockCreated = 1;
      }
#endif

#if 1
       regInfo.alloc = cmDynAlloc;
       regInfo.free = cmDynFree;
#endif
   }

   regInfo.regCb = regCb;

   if (SRegDynRegion(region, &regInfo) != ROK)
   {
      RETVALUE(RFAILED);
   }

    RETVALUE(ROK);
} /* end of cmMmDynRegInit*/

#endif /* SS_USE_ICC_MEMORY */


/*
*
*       Fun:   cmMmRegDeInit
*
*       Desc:  Deinitialize the memory region. The function call SDeregRegion
*              to deregister the memory region with System Service.
*
*
*       Ret:   ROK     - successful
*              RFAILED - unsuccessful.
*
*       Notes: The memory owner calls this function to deinitialize the region.
*              The memory manager does not return the memory to the system. 
*              Before calling this function, the memory owner must be sure that 
*              no layer is using any memory block from this region. On 
*              successful return from the function, any request to the memory 
*              manager to allocate/deallocate memory will fail. The memory owner
*              can reuse the memory for other region or return the memory to the
*              system memory pool.
*
*
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PUBLIC S16 cmMmRegDeInit
(
CmMmRegCb   *regCb
)
#else
PUBLIC S16 cmMmRegDeInit(regCb)
CmMmRegCb   *regCb;
#endif
{
   U16  bktIdx; 

   TRC2(cmMmRegDeInit);

#if (ERRCLASS & ERRCLS_INT_PAR)
  
   /* error check on parameters */
   if (regCb == NULLP)
   {
      RETVALUE(RFAILED);
   }

#endif

/* cm_mem_c_001.main_12 - addition for deinitializing the hash table */
#ifdef SSI_DEBUG_LEVEL1
    /* Deinitialize the hash table used for debug info storage at region level */
    if (cmMmHashListDeinit(&regCb->hashListCp, regCb->region, 0) != ROK)
    {
        RETVALUE(RFAILED);
    }
#endif /* SSI_DEBUG_LEVEL1 */

   /* Call SDeregRegion first to deregister the memory region with SSI */
   (Void) SDeregRegion (regCb->region);

   if (regCb->bktSize)
   {
      /* Bucket pool is configured */

      /* Free the initialzed locks of the buckets */
      for ( bktIdx = regCb->numBkts; bktIdx > 0;)
      {
          /* cm_mem_c_001.main_13: Replaced SDestroyLock with
             WTDestroyLock for NT */
          /*  cm_mem_c_001.main_24 fix for memory corruption*/
          --bktIdx;
#ifdef SS_WIN
          WTDestroyLock(&(regCb->bktTbl[bktIdx].bktLock));
#else
          SDestroyLock(&(regCb->bktTbl[bktIdx].bktLock));
#endif
/*  cm_mem_c_001.main_15:Additions */
#ifdef SS_HISTOGRAM_SUPPORT 
   /* De-initialise the memory histogram hash list */
   cmHstGrmHashListDeInit(&(regCb->bktTbl[bktIdx].hstGrmHashListCp));
#endif /* SS_HISTOGRAM_SUPPORT */
      }
   }

   if (regCb->heapFlag)
   {
      /* Heap pool is configured */

      /* cm_mem_c_001.main_13: Replaced SDestroyLock with
         WTDestroyLock for NT */
#ifdef SS_WIN
      WTDestroyLock(&regCb->heapCb.heapLock);
#else
      SDestroyLock(&regCb->heapCb.heapLock);
#endif
   }

   RETVALUE(ROK);

} /* end of cmMmRegDeInit */

#ifndef USE_PURE 
#ifndef SS_USE_ICC_MEMORY
/*
*
*       Fun:   cmGetMemBlkSetForAlloc
*
*       Desc:  Retruns the pointer to the element which is used for 
*              allocating the buffer. Also, it does the threshold check
*              and get the additional memory block set from the global
*              region
*
*
*       Ret:   Pointer to memory block set     - successful
*              NULL                            - unsuccessful.
*
*       Notes: 
*       Current implementation of the is function is made assuming that
*       there will maximum two set of nodes only.
*
*       File:  cm_mem_wl.c
*
*/

#ifdef ANSI
PRIVATE CmMmBlkSetElement* cmGetMemBlkSetForAlloc
(
U8             bucketIndex, /* Index to the bucket list */
CmMmDynBktCb  *bkt        /* Bucket list control block */
)
#else
PRIVATE CmMmBlkSetElement*  cmGetMemBlkSetForAlloc(bucketIndex, bkt)
U8             bucketIndex; /* Index to the bucket list */
CmMmDynBktCb  *bkt;        /* Bucket list control block */
#endif
{
   CmMmBlkSetElement  *memBlkSetElem;
   CmMmBlkSetElement  *nextMemBlkSetElem;
   CmLList            *memSetNode;
   CmLList            *nextMemSetNode;

   /* Check if we are coming here for the first time, if yes get a new
    * block set from global region */
   if(bkt->crntMemBlkSetElem == NULLP)
   {
      /* set the current index to initial one and get the bucket set from
       * global region */
      memSetNode = cmLListFirst(&bkt->memBlkSetElem);

      /* Check if the element exits or not */
      if((memSetNode == NULLP) || (memSetNode->node == NULLP))
      {
         RETVALUE(NULLP);
      }

      bkt->crntMemBlkSetElem = (CmMmBlkSetElement *)memSetNode->node;
      /* Get the new block set from the gloabl region and return the same */
      ssGetDynMemBlkSet(bucketIndex, bkt->crntMemBlkSetElem, 0);
      RETVALUE(bkt->crntMemBlkSetElem);
   }
   /* If this is not the first time, take the bucket list CB from the 
    * current index */
   memBlkSetElem = bkt->crntMemBlkSetElem;
   /* If the current index doesnot have any free buckets, it check in
    * the next bucket node */
   if(memBlkSetElem->numFreeBlks == 0)
   {
      /* Get the next element in the list and if it is not present, then 
       * get the first node */
      memSetNode = cmLListNext(&bkt->memBlkSetElem);

      if(memSetNode == NULLP)
      {
         memSetNode = cmLListFirst(&bkt->memBlkSetElem);
      }
      memBlkSetElem = (CmMmBlkSetElement *)memSetNode->node;

      /* if next node also empty, return failure */
      if(memBlkSetElem->numFreeBlks == 0)
      {
         RETVALUE(NULLP);
      }
      /* store the new index in the current node which will be
       * used in the next time. */
      bkt->crntMemBlkSetElem = memBlkSetElem;
   }

#if 0
   if(memBlkSetElem->nextBktPtr == NULLP)
   {
      ssGetDynMemBlkSet(bucketIndex, memBlkSetElem);
   }
#endif
   /* If we have reached the threshold value, get the next set of buckets from
    * the global region and place it */
   if(memBlkSetElem->numFreeBlks < bkt->blkSetAcquireThreshold)
   {
      /* Get the next element for the threshold check. If next is not present, 
       * get the first one. Here, we are not using the cmLList macros to get
       * to the next node or first node as those macros are working on the crnt
       * node and will change the crnt. As we dont want to change the crnt node
       * at this point, we are directly using the listCp prameter to get next
       * first nodes */
      nextMemSetNode = memBlkSetElem->memSetNode.next;

      if(nextMemSetNode == NULLP)
      {
         nextMemSetNode =  bkt->memBlkSetElem.first;
      }

      nextMemBlkSetElem = (CmMmBlkSetElement *)nextMemSetNode->node;

      if(nextMemBlkSetElem->numFreeBlks == 0)
      {
         /* The last parameter is used wheather to block for the block set aquiring
            or not. Here, the logic is such that, when the current node number of 
            free blocks becomes one and the next node has zero free blocks, 
            we must get the block set from global region.
            For example, if acquire threashold is 20 and current node has only one 
            free block and next node has zero free blocks we block to aquire lock 
            and get the set from global region else, we try for lock, if we get 
            the lock, the get the block set else it is get in next go
         */
         ssGetDynMemBlkSet(bucketIndex, nextMemBlkSetElem, 
                           (memBlkSetElem->numFreeBlks - 1));
      }
   }
   
   /* On successful, return the bucket node to calling function */
   RETVALUE(memBlkSetElem);
} /* cmGetMemBlkSetForAlloc */


/*
*
*       Fun:   cmGetMemBlkSetForFree
*
*       Desc:  Retruns the pointer to the element which is used for 
*              freeing the buffer. Also, it does the threshold check
*              and release the additional memory block set to the global
*              region
*
*
*       Ret:   Pointer to memory block set     - successful
*              NULL                            - unsuccessful.
*
*       Notes: 
*       Current implementation of the is function is made assuming that
*       there will maximum two set of nodes only.
*
*       File:  cm_mem_wl.c
*
*/

#ifdef ANSI
PRIVATE CmMmBlkSetElement* cmGetMemBlkSetForFree
(
U8             bucketIndex, /* Index to the bucket list */
CmMmDynBktCb  *bkt        /* Bucket list control block */
)
#else
PRIVATE CmMmBlkSetElement*  cmGetMemBlkSetForFree(bucketIndex, bkt)
U8             bucketIndex; /* Index to the bucket list */
CmMmDynBktCb  *bkt;        /* Bucket list control block */
#endif
{
   CmMmBlkSetElement  *memBlkSetElem;
   CmMmBlkSetElement  *nextMemBlkSetElem;
   CmLList            *memSetNode;
   CmLList            *nextMemSetNode;

   /* Check if we are coming here for the first time, if yes get a new
    * block set from global region */
   if(bkt->crntMemBlkSetElem == NULLP)
   {
      /* set the current index to initial one */
      memSetNode = cmLListFirst(&bkt->memBlkSetElem);

      /* Check if the element exits or not */
      if((memSetNode == NULLP) || (memSetNode->node == NULLP))
      {
         RETVALUE(NULLP);
      }
      bkt->crntMemBlkSetElem = (CmMmBlkSetElement *)memSetNode->node;
      RETVALUE(bkt->crntMemBlkSetElem);
   }
   /* If this is not the first time, take the bucket list CB from the 
    * current index */
   memBlkSetElem = bkt->crntMemBlkSetElem;
   /* If the current index doesnot have any free buckets, it check in
    * the next bucket node */
   if(memBlkSetElem->numFreeBlks >= bkt->bucketSetSize)
   {
      /* Get the next element in the list and if it is not present, then 
       * get the first node */
      nextMemSetNode = cmLListNext(&bkt->memBlkSetElem);

      if(nextMemSetNode == NULLP)
      {
         nextMemSetNode =  cmLListFirst(&bkt->memBlkSetElem);
      }
      memBlkSetElem = (CmMmBlkSetElement *)nextMemSetNode->node;

      /* if next node also empty, return failure */
      if(memBlkSetElem->numFreeBlks >= bkt->bucketSetSize)
      {
         RETVALUE(NULLP);
      }
      /* store the new index in the current node which will be
       * used in the next time. */
      bkt->crntMemBlkSetElem = memBlkSetElem;
   }

   /* If we have reached the threshold value and have additional block set,
    * release the additional block set back to global region */
   if(memBlkSetElem->numFreeBlks > bkt->blkSetRelThreshold) 
   {
      /* Get the next element for the threshold check. If next is not present, 
       * get the first one. Here, we are not using the cmLList macros to get
       * to the next node or first node as those macros are working on the crnt
       * node and will change the crnt. As we dont want to change the crnt node
       * at this point, we are directly using the listCp prameter to get next
       * first nodes */
      nextMemSetNode = memBlkSetElem->memSetNode.next;
      if(nextMemSetNode == NULLP)
      {
         nextMemSetNode =  bkt->memBlkSetElem.first;
      }

      nextMemBlkSetElem = (CmMmBlkSetElement *)nextMemSetNode->node;
      if(nextMemBlkSetElem->numFreeBlks == bkt->bucketSetSize)
      {
         /* The last parameter is used wheather to block for the block set aquiring
            or not. Here, the logic is such that, when the current node number of 
            free blocks becomes one less than the bucket set size and the next node
            is has full free blocks, we must free the block set back to global region
            For example, if bucket set size if 100 and release threashold is 80 and
            current node has number of free blocks 99 and next node has 100 free blocks
            we block to aquire lock and free it back to global region else, we try for
            lock, if we get the lock, the block set is freed else its freed in next go 
           */
         ssPutDynMemBlkSet(bucketIndex, nextMemBlkSetElem, 
                           (bkt->bucketSetSize - memBlkSetElem->numFreeBlks - 1));
#if 0
         nextMemBlkSetElem->numFreeBlks = 0;
         nextMemBlkSetElem->nextBktPtr = NULLP;
#endif
      }
   }
   
   /* On successful, return the bucket node to calling function */
   RETVALUE(memBlkSetElem);
}
#endif /* SS_USE_ICC_MEMORY */
#endif /* USE_PURE */

#ifdef SS_MEM_WL_DEBUG
/*
*
*       Fun:   cmRemoveAllocPtrFromList
*
*       Desc:  Remove a node with Free PTR from hashlist. The memory
*              of the node is Freed to the same region
*
*
*       Ret:   ROK     - successful
*              RFAILED - unsuccessful.
*
*       Notes: 
*
*       File:  cm_mem_wl.c
*
*/

#ifdef ANSI
PRIVATE S16  cmRemoveAllocPtrFromList
(
CmMmDynRegCb    *regionCb,    /* Pointer to a region */
PTR              ptr
)
#else
PRIVATE S16  cmRemoveAllocPtrFromList(regionCb, ptr)
CmMmDynRegCb    *regionCb;    /* Pointer to a region */
PTR              ptr;
#endif
{

   CmMemDoubleFree   *memNode = NULLP;

   SLock(&memDoubleFreeLock);
   if((cmHashListFind(&(memDoubleFree), (U8*)&ptr,
       sizeof(U32), 0, (PTR *)&memNode)) != ROK)
   {
      Void    *tmpBtArr[10];
      U16     tmpBtSize;
      S8      **strings;
      U16     idx;

      tmpBtSize = backtrace(tmpBtArr, 10);
      strings = backtrace_symbols(tmpBtArr, tmpBtSize);
      printf("**** Trying to free non allocated block BT is: \n");
      for(idx = 0; idx < tmpBtSize; idx++)
      {
           printf("%s\n", strings[idx]);
      }
      printf("*****************************************\n");
      printf("Analysis from Array storing BT for freeing and allocation\n");
      cmAnalyseBtInfo(ptr, regionCb->region);
      SUnlock(&memDoubleFreeLock);
      RETVALUE(RFAILED);
   }

   if((cmHashListDelete(&(memDoubleFree), (PTR)memNode)) != ROK)
   {
      SUnlock(&memDoubleFreeLock);
      RETVALUE(RFAILED);
   }
   SUnlock(&memDoubleFreeLock);
   SPutSBuf(regionCb->region, 0, (Data *)memNode, sizeof(CmMemDoubleFree));

   RETVALUE(ROK);
}

/*
*
*       Fun:   cmInsertAllocPtrToList
*
*       Desc:  Insert a node with allocated PTR into hashlist. The memory
*              for the node is allocated from the same region
*
*
*       Ret:   ROK     - successful
*              RFAILED - unsuccessful.
*
*       Notes: 
*
*       File:  cm_mem_wl.c
*
*/

#ifdef ANSI
PRIVATE S16  cmInsertAllocPtrToList
(
CmMmDynRegCb    *regionCb,    /* Pointer to a region */
PTR              ptr
)
#else
PRIVATE S16  cmInsertAllocPtrToList(regionCb, ptr)
CmMmDynRegCb    *regionCb;    /* Pointer to a region */
PTR              ptr;
#endif
{

   CmMemDoubleFree   *memNode;

   SGetSBuf(regionCb->region, 0, (Data **)&memNode, sizeof(CmMemDoubleFree));
   if(memNode == NULLP)
   {
       RETVALUE(RFAILED);
   }

   memNode->memBlkPtr = ptr;
   SLock(&memDoubleFreeLock);
   if((cmHashListInsert(&(memDoubleFree), (PTR)memNode, (U8*)&memNode->memBlkPtr,
       sizeof(PTR))) != ROK)
   {
       SUnlock(&memDoubleFreeLock);
       RETVALUE(RFAILED);
   }
   SUnlock(&memDoubleFreeLock);

   RETVALUE(ROK);
}
#endif


#ifndef SS_USE_ICC_MEMORY
/*
*
*       Fun:   cmDynAllocWithLock
*
*       Desc:  Allocate a memory block for use by dynamic buffers
*
*
*       Ret:   ROK     - successful
*              RFAILED - unsuccessful.
*
*       Notes: 
*
*       File:  cm_mem_wl.c
*
*/
/* cm_mem_c_001.main_15 : Additions */

#ifdef ANSI
PRIVATE S16  cmDynAllocWithLock
(
Void   *regionCb,    /* Pointer to a region */
Size   *size,        /* size needs to be allocated */
U32     flags,       /* Flags used */
Data  **ptr          /* Reference to pointer for which need to be allocate */
)
#else
PRIVATE S16  cmDynAllocWithLock(regionCb, size, flags, ptr)
Void   *regionCb;    /* Pointer to a region */
Size   *size;        /* size needs to be allocated */
U32     flags;       /* Flags used */
Data  **ptr;         /* Reference to pointer for which need to be allocate */
#endif
{
   S16 ret;

   TRC2(cmDynAlloc);

   if((SLock(&dynAllocFreeLock)) != ROK)
   {
      printf("cmDynAllocWithLock: Failed to get the dyn lock\n");
      RETVALUE(RFAILED);
   }

   ret =  cmDynAlloc (regionCb, size,flags,ptr);

   if((SUnlock(&dynAllocFreeLock)) != ROK)
   {
      printf("cmDynAllocWithLock: Failed to unlock the Dyn lock\n");
      RETVALUE(RFAILED);
   }
 
   RETVALUE(ret);
} /* end of cmDynAlloc */

/*
*
*       Fun:   cmDynAlloc
*
*       Desc:  Allocate a memory block for use by dynamic buffers
*
*
*       Ret:   ROK     - successful
*              RFAILED - unsuccessful.
*
*       Notes: 
*
*       File:  cm_mem_wl.c
*
*/
/* cm_mem_c_001.main_15 : Additions */

#ifdef ANSI
PRIVATE S16  cmDynAlloc
(
Void   *regionCb,    /* Pointer to a region */
Size   *size,        /* size needs to be allocated */
U32     flags,       /* Flags used */
Data  **ptr          /* Reference to pointer for which need to be allocate */
)
#else
PRIVATE S16  cmDynAlloc(regionCb, size, flags, ptr)
Void   *regionCb;    /* Pointer to a region */
Size   *size;        /* size needs to be allocated */
U32     flags;       /* Flags used */
Data  **ptr;         /* Reference to pointer for which need to be allocate */
#endif
{
   CmMmDynRegCb        *regCb;

   TRC2(cmDynAlloc);

   regCb = (CmMmDynRegCb *)regionCb;

#ifdef SS_MEM_WL_DEBUG
      if((tmpRegTidMap[regCb->region] != (pthread_self())) )
      {
         **ptr = 10;
      }
#endif

#if (ERRCLASS & ERRCLS_INT_PAR)

   /* error check on parameters */
   if ((regCb == NULLP) || (size == NULLP) || !(*size) || (ptr == NULLP))
   {
      RETVALUE(RFAILED);
   }
#endif
  
#ifndef USE_PURE

   /* 
    * Check if the requested size is less than or equal to the maximum block 
    * size in the bucket. 
    */
   
#ifdef SS_MEM_WL_DEBUG
   if ( (*size + 4) <= regCb->bktMaxBlkSize)
#else
   if ( (*size) <= regCb->bktMaxBlkSize)
#endif
   {
      U32                  idx;
      CmMmBlkSetElement   *dynMemElem;
      U32                  bktIdx;
      CmMmDynBktCb        *bkt;

      /* Get the map to the mapping table */
#ifdef SS_MEM_WL_DEBUG
      idx = (((*size + 4) - 1) >> regCb->bktQnPwr);
#else
      idx = (((*size) - 1) >> regCb->bktQnPwr);
#endif

#if (ERRCLASS & ERRCLS_DEBUG)
      if (regCb->mapTbl[idx].bktIdx == 0xFF)
      { 
         printf("Failed to get the buffer of size %d\n", *size);
         /* Some fatal error in the map table initialization. */
         RETVALUE(RFAILED);
      }
#endif

      /* Dequeue the memory block and return it to the user */
      bktIdx = regCb->mapTbl[idx].bktIdx;
      bkt = &(regCb->bktTbl[bktIdx]);
#ifdef SS_MEM_WL_DEBUG
      if(bkt->size < (*size+4))
#else
      if(bkt->size < (*size))
#endif
      {
         idx++;
         bkt = &(regCb->bktTbl[bktIdx = regCb->mapTbl[idx].bktIdx]);
      }

      dynMemElem = cmGetMemBlkSetForAlloc(bktIdx, bkt);

      /* Check if the bucket index, if its not valid, return failure */
      if(dynMemElem == NULLP)
      {
         printf("Failed to get the buffer of size %ld\n", *size);
         RETVALUE(RFAILED);
      }

#ifdef SS_MEM_WL_DEBUG
      if(dynMemElem->nextBktPtr == prvAllocPtr[regCb->region])
      {
          U32    *tmpDump;
          *tmpDump = 100;
      }
#endif
      /* Get the bucket node from the index returned and allocate the memory */
      *ptr = dynMemElem->nextBktPtr;
      dynMemElem->nextBktPtr = *((CmMmEntry **)(*ptr));
      dynMemElem->numFreeBlks--;

#ifdef SS_MEM_WL_DEBUG
      prvAllocPtr[regCb->region] = *ptr;
#if 0
      if(regCb->region == 6)
         printf("cmDynAlloc: PTR = %x\n", *ptr);
      **ptr = (U32) ((bktIdx << 4) | 0x0f);
#endif

      **ptr = (U8) bktIdx;
      *(*ptr+1) = 0xde;
      *(*ptr+2) = 0xad;
      *(*ptr+3) = 0xbe;
      *ptr += sizeof (U32);

      if ((bktIdx == 0) && (!stopBtInfo))
      {
         CmBtInfo *btInfo;
         U32      btIdx;
         btInfo  = &allocBtInfo[regCb->region];
         btIdx = btInfo->btInfoIdx;
         btInfo->btInfo[btIdx].ptr = (PTR) *ptr;
         {
            btInfo->btInfo[btIdx].btSize  = backtrace(btInfo->btInfo[btIdx].btArr, NUM_BT_TRACES);
         }
         gettimeofday(&(btInfo->btInfo[btIdx].timeStamp), NULLP);
#if 0
         cmInsertAllocPtrToList(regCb, (PTR)*ptr);
#endif
   
         btIdx++;
         btIdx &= (NUM_FREE_BUFFERS - 1); 
   
         btInfo->btInfo[btIdx].ptr = (PTR)0;
         btInfo->btInfo[btIdx].btSize = 0;
         cmMemset(btInfo->btInfo[bktIdx].btArr, 0, sizeof (btInfo->btInfo[bktIdx].btArr));
         btInfo->btInfoIdx = btIdx;
      }
#endif

      RETVALUE(ROK);
   }

   /* If the size is not matching, return failure to caller */
   printf("Failed to get the buffer of size %ld\n", *size);
   RETVALUE(RFAILED);
   
#else /* use pure is on */

#ifdef SS_4GMX_LCORE
   *ptr = (Data*) MxHeapAlloc(SsiHeap, *size);
   cmMemset((U8*)ptr, 0, *size);
#else
/*   *ptr = (Data*) malloc(*size); */
#endif
#ifndef USE_PURE
   *ptr = (Data *)tcmalloc(*size);
#else
   *ptr = (Data*) malloc(*size);
#endif

   if ( (*ptr) == NULLP)
       RETVALUE(RFAILED);
   /* avail_size -= *size; */
   RETVALUE(ROK);
#endif /* USE_PURE */

} /* end of cmDynAlloc */
#endif /* SS_USE_ICC_MEMORY */


#define OVERUSED(_bkt) (((_bkt)->numAlloc * 100) / (_bkt)->numBlks > 80)

int g_overused[5] = {0};


/*
*
*       Fun:   cmAlloc
*
*       Desc:  Allocate a memory block for the memory region.
*
*
*       Ret:   ROK     - successful
*              RFAILED - unsuccessful.
*
*       Notes: 
*              The function allocates a memory block of size atleast equal to 
*              the requested size. The size parameter will be updated with the 
*              actual size of the memory block allocated for the request. The 
*              CMM tries to allocate the memory block form the bucket pool. If
*              there is no memory in the bucket the CMM allocates the memory 
*              block form the heap pool. This function is always called by the
*              System Service module.
*    
*              The caller of the function should try to use the out value of 
*              the size while returning the memory block to the region. However 
*              the current design of the memory manager does not enforce to pass
*              the actual size of the memory block.  (Due to the SGetSBuf 
*              semantics the layer will not able to pass the correct size of the
*              memory block while calling SPutSBuf).
*
*
*       File:  cm_mem_wl.c
*
*/
/* cm_mem_c_001.main_12 - addition to accept new parameter memType(static/dynamic) */

/* cm_mem_c_001.main_15 : Additions */
#ifdef T2K_MEM_LEAK_DBG
PRIVATE S16  cmAlloc
(
 Void   *regionCb,
 Size   *size,
 U32     flags,
 Data  **ptr ,
 char* file,
 U32 line
 )
#else
#ifdef SS_HISTOGRAM_SUPPORT
#ifdef SSI_DEBUG_LEVEL1
#ifdef ANSI
PRIVATE S16  cmAlloc
(
Void   *regionCb,
Size   *size,
U32     flags,
Data  **ptr,
U32     memType,
U32     line,
U8     *fileName,
U8      entId,
Bool    hstReg
)
#else
PRIVATE S16  cmAlloc(regionCb, size, flags, ptr, memType, line, fileName, entId, hstReg)
Void   *regionCb;
Size   *size;
U32     flags;
Data  **ptr;
U32     memType;
U32     line;
U8     *fileName;
U8      entId;
Bool    hstReg;
#endif
#else
#ifdef ANSI
PRIVATE S16  cmAlloc
(
Void   *regionCb,
Size   *size,
U32     flags,
Data  **ptr,
U32     line,
U8     *fileName,
U8      entId,
Bool    hstReg
)
#else
PRIVATE S16  cmAlloc(regionCb, size, flags, ptr, line, fileName, entId, hstReg)
Void   *regionCb;
Size   *size;
U32     flags;
Data  **ptr;
U32     line;
U8     *fileName;
U8      entId;
Bool    hstReg;
#endif
#endif /* SSI_DEBUG_LEVEL1 */

#else

#ifdef SSI_DEBUG_LEVEL1
#ifdef ANSI
PRIVATE S16  cmAlloc
(
Void   *regionCb,
Size   *size,
U32     flags,
Data  **ptr,
U32     memType
)
#else
PRIVATE S16  cmAlloc(regionCb, size, flags, ptr, memType)
Void   *regionCb;
Size   *size;
U32     flags;
Data  **ptr;
U32     memType;
#endif
#else
#ifdef ANSI
PRIVATE S16  cmAlloc
(
Void   *regionCb,
Size   *size,
U32     flags,
Data  **ptr 
)
#else
PRIVATE S16  cmAlloc(regionCb, size, flags, ptr)
Void   *regionCb;
Size   *size;
U32     flags;
Data  **ptr;
#endif

#endif
#endif /* SSI_DEBUG_LEVEL1 */
/* cm_mem_c_001.main_15: Additions */
#endif /* SS_HISTOGRAM_SUPPORT */

{
/* cm_mem_c_001.main_26 : Fixes for Compilation Warnings */
#ifndef USE_PURE
   U16        idx;
   CmMmBkt   *bkt;
   U16   bktIdx;
#endif
   CmMmRegCb *regCb;
/* cm_mem_c_001.main_26 : Fixes for Compilation Warnings */
#ifndef USE_PURE
   U16        cnt;
#endif
/*   cm_mem_c_001.main_15 : Additions */
#ifdef SS_MEM_LEAK_STS
   Size       reqSz;
#endif /* SS_MEM_LEAK_STS */
/* cm_mem_c_001.main_12 - addition to hold the allocated block */
#ifdef SSI_DEBUG_LEVEL1
   CmMmBlkHdr *alocBlk;
#endif /* SSI_DEBUG_LEVEL1 */
/*   cm_mem_c_001.main_15 : Additions */
#ifdef SS_HISTOGRAM_SUPPORT
	S8 hstGrmBuf[256];
#endif /* SS_HISTOGRAM_SUPPORT */

   TRC2(cmAlloc);

#ifndef USE_MEMCAL
   UNUSED(flags);
#endif
/*  cm_mem_c_001.main_15 : Additions */
#ifdef SS_MEM_LEAK_STS 
   reqSz = *size;
#endif /* SS_MEM_LEAK_STS */

   regCb = (CmMmRegCb *)regionCb;

#if (ERRCLASS & ERRCLS_INT_PAR)

   /* error check on parameters */
   if ((regCb == NULLP) || (size == NULLP) || !(*size) || (ptr == NULLP))
   {
      RETVALUE(RFAILED);
   }
#endif
  
/* cm_mem_c_001.main_12 - addition for checking memType parameter */
#ifdef SSI_DEBUG_LEVEL1
#if (ERRCLASS & ERRCLS_INT_PAR)
      if ((memType != CMM_STATIC_MEM_FLAG) && (memType != CMM_DYNAMIC_MEM_FLAG))
      {
         RETVALUE(RFAILED);
      }
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */
#endif /* SSI_DEBUG_LEVEL1 */

#ifndef USE_PURE

   if (flags)
      num_times++;

/* cm_mem_c_001.main_12 - addition to insert the size into hash list */
#ifdef SSI_DEBUG_LEVEL1
   /* Update the hash list */
   if (cmMmHashListInsert(&(regCb->hashListCp), *size) != ROK)
   {
      /* display that, this entry could not be made in the hash list */
#ifdef DEBUGP
      /* display an error message here */
/*cm_mem_c_001.main_23 Fix for specifier mismatch warnings in 64BIT compilation*/          
#ifdef ALIGN_64BIT          
      sprintf(dbgPrntBuf, "\n Could not make an entry for size %u in hash table of region %d \n",
                           *size, regCb->region);
#else                           
      sprintf(dbgPrntBuf, "\n Could not make an entry for size %lu in hash table of region %d \n",
                           *size, regCb->region);
#endif                           
      SDisplay(0, dbgPrntBuf);
#endif /* DEBUGP */
   }
#endif /* SSI_DEBUG_LEVEL1 */

   /* 
    * Check if the requested size is less than or equal to the maximum block 
    * size in the bucket. 
    */
   if ( *size <= regCb->bktMaxBlkSize)
   {
      /* Get the map to the mapping table */
      idx = ((*size - 1) >> regCb->bktQnPwr);

#if (ERRCLASS & ERRCLS_DEBUG)
      if (regCb->mapTbl[idx].bktIdx == 0xFF)
      { 
         /* Some fatal error in the map table initialization. */
         RETVALUE(RFAILED);
      }
#endif

      /* Dequeue the memory block and return it to the user */
      bkt = &(regCb->bktTbl[bktIdx = regCb->mapTbl[idx].bktIdx]);

      cnt = 0;
      /* While loop is introduced to use the "break statement inside */
      while (cnt < 1)
      {
         /*
          * Check if the size request is not greater than the size available
          * in the bucket
          */
         if (*size > bkt->size)
         {
            /* Try to go to the next bucket if available */
            if((idx < (CMM_MAX_MAP_ENT - 1)) &&
               (regCb->mapTbl[++idx].bktIdx != 0xFF))
            {
               bkt = &(regCb->bktTbl[bktIdx = regCb->mapTbl[idx].bktIdx]);
            }
            else
            {
               /* This is the last bucket, try to allocate from heap */
               break;
            }
         }

         /* Acquire the bucket lock */
         /* cm_mem_c_001.main_13 : Replaced SLock with WTLock for NT */
#ifdef SS_WIN
         (Void) WTLock(&(bkt->bktLock));
#else
         (Void) SLock(&(bkt->bktLock));
#endif

#if (ERRCLASS & ERRCLS_DEBUG)
         regCb->mapTbl[idx].numReq++;
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

/* cm_mem_c_001.main_12 - addition for sanity check before allocation */
#ifdef SSI_DEBUG_LEVEL1
      /* increment the allocation attempt counter at bucket level */
      bkt->numAllocAttempts++;

      /* detect trampling if any and call sanity check. This is done for (bkt->nextBlk) as
         the allocation is always from (bkt->nextBlk) */
      if (bkt->nextBlk)
      {
         if (cmMmRegIsBlkSane(bkt->nextBlk) != ROK)
         {
               /* detected a trampled memory block in this bucket */
            #ifdef DEBUGP
               /* display an error message here */
/*cm_mem_c_001.main_23 Fix for specifier mismatch warnings in 64BIT compilation*/          
#ifdef ALIGN_64BIT          
               sprintf(dbgPrntBuf, "Memory Trampling at: %8p, Bucket Id:%03d, size %u bytes \n",
                                    (void *)bkt->nextBlk, regCb->mapTbl[idx].bktIdx, *size);
#else                                    
               sprintf(dbgPrntBuf, "Memory Trampling at: %8p, Bucket Id:%03d, size %lu bytes \n",
                                    (void *)bkt->nextBlk, regCb->mapTbl[idx].bktIdx, *size);
#endif                                    
               SDisplay(0, dbgPrntBuf);
            #endif /* DEBUGP */

               if (cmMmBktSanityChk(bkt) == RTRAMPLINGNOK)
               {
                  /* Release the lock */
                  /* cm_mem_c_001.main_13: Replaced SUnlock with WTUnlock for NT */
#ifdef SS_WIN
                  (Void) WTUnlock(&(bkt->bktLock));
#else
                  (Void) SUnlock(&(bkt->bktLock));
#endif
                  /* handle RTRAMPLINGNOK in SAlloc/SGetSBuf */
                  RETVALUE(RTRAMPLINGNOK);
               }
               else
               {
                  /* Release the lock */
                  /* cm_mem_c_001.main_13: Replaced SUnlock with WTUnlock for NT */
#ifdef SS_WIN
                  (Void) WTUnlock(&(bkt->bktLock));
#else
                  (Void) SUnlock(&(bkt->bktLock));
#endif
                  /* return RFAILED */
                  RETVALUE(RFAILED);
               }
         }
      }

      if ((bkt->nextBlk) && (*ptr = (Data *)(bkt->nextBlk) + (sizeof(CmMmBlkHdr))))
#else
         if ((*ptr = bkt->next))
#endif /* SSI_DEBUG_LEVEL1 */
         {
/* cm_mem_c_001.main_12 - addition for header */
#ifdef SSI_DEBUG_LEVEL1
      /* point to next block header */
         alocBlk = bkt->nextBlk;
         bkt->nextBlk = (CmMmBlkHdr *)(bkt->nextBlk->nextBlk);
#else
            bkt->next = *((CmMmEntry **)(bkt->next));
#endif /* SSI_DEBUG_LEVEL1 */

            /* 
             * Increment the statistics variable of number of memory block 
             * allocated 
             */
            bkt->numAlloc++;
            if (bkt->numAlloc > bkt->maxAlloc)
            {
               bkt->maxAlloc = bkt->numAlloc;
            }
            {
               if (g_overused[bktIdx] == 0 && OVERUSED(bkt))
               {
                  g_overused[bktIdx] = 1;
                  /*printf("cmAlloc: bktIdx %u overused %u numAlloc %u\n", bktIdx, g_overused[bktIdx], bkt->numAlloc); */
               }
            }
#if 0
            if(bkt->numAlloc < 100)
	    printf("cmAlloc: Allocated PTR = %x size = %d\n", *ptr, *size);
#endif

/* cm_mem_c_001.main_12 - addition for header manipulation */
#ifdef SSI_DEBUG_LEVEL1
      /* update the size for which this memory block has been allocated */
      alocBlk->requestedSize = *size;
      /* update the memory block header */
      CMM_RESET_FREE_FLAG(alocBlk->memFlags);
      if (memType == CMM_STATIC_MEM_FLAG)
      {
         CMM_SET_STATIC_FLAG(alocBlk->memFlags);
         /* add it to the static memory allocated */
         bkt->staticMemUsed += bkt->size;
      }
      else
      {
         CMM_SET_DYNAMIC_FLAG(alocBlk->memFlags);
         /* add it to the dynamic memory allocated */
         bkt->dynamicMemUsed += bkt->size;
      }
#endif /* SSI_DEBUG_LEVEL1 */

            if (((bkt->size - (*size)) >> regCb->bktQnPwr) && flags)
            {
               bkt->bktNoFitCnt++;
#ifdef MEMCAL_DEBUG
/*cm_mem_c_001.main_23 Fix for specifier mismatch warnings in 64BIT compilation*/          
#ifdef ALIGN_64BIT          
               sprintf(prntBuf,
   "[MEM_CAL_CNTA] %u bytes request not fitted in bkt %d [size %u bytes] %u times\n", *size, regCb->mapTbl[idx].bktIdx, bkt->size, bkt->bktNoFitCnt++);
#else   
               sprintf(prntBuf,
   "[MEM_CAL_CNTA] %lu bytes request not fitted in bkt %d [size %lu bytes] %lu times\n", *size, regCb->mapTbl[idx].bktIdx, bkt->size, bkt->bktNoFitCnt++);
#endif   
               SDisplay(0, prntBuf);
#endif
            }

#ifdef MEMCAL_DEBUG
            if (flags)
            {
               sprintf(prntBuf,
    "SGetSBuf:%08lu:Size Bucket Id:%03d  Times:%05lu  Pointer: %8p\n",
                    *size, regCb->mapTbl[idx].bktIdx, num_times, *ptr);
               SDisplay(0, prntBuf);
            }
#endif /* MEMCAL_DEBUG */
 /*  cm_mem_c_001.main_15 : Additions */
#ifdef SS_HISTOGRAM_SUPPORT
            /* If If Tapa task (entId)is registerd for histogram then insert Memrory allocated
             * information into the hash list */
            if(hstReg)
            {
               if (cmHstGrmAllocInsert(&(bkt->hstGrmHashListCp), bkt->size, size, line, fileName, entId) != ROK)
               {
                 sprintf(hstGrmBuf, "Unable to Insert into the histgram hash list\n");
					  SPrint(hstGrmBuf);
               }
            }/* End of if */

#endif /* SS_HISTOGRAM_SUPPORT */
        
            /* Update the size parameter */
            *size = bkt->size;
#ifdef SS_MEM_LEAK_STS
        /* cm_mem_c_001.main_25 - Fixed compilation warnings 32/64 bit */
         cmStorAllocBlk((PTR)*ptr, (Size) reqSz, (Size) *size,
                          regCb->mapTbl[idx].bktIdx);
#endif /* SS_MEM_LEAK_STS */

      /* cm_mem_c_008.104 - Addition for memory calculator tool */

            /* Release the lock */
            /* cm_mem_c_001.main_13: Replaced SUnlock with WTUnlock for NT */
#ifdef SS_WIN
            (Void) WTUnlock(&(bkt->bktLock));
#else
            (Void) SUnlock(&(bkt->bktLock));
#endif

            RETVALUE(ROK);
         }
         else if (flags)
         {
            bkt->bktFailCnt++;
#ifdef MEMCAL_DEBUG
/*cm_mem_c_001.main_23 Fix for specifier mismatch warnings in 64BIT compilation*/          
#ifdef ALIGN_64BIT          
 sprintf(prntBuf,
            "[MEM_CAL_CNTB] Allocation failed in bucket %d [ size %u bytes], %u times\n", regCb->mapTbl[idx].bktIdx, bkt->size, bkt->bktFailCnt);
#else            
 sprintf(prntBuf,
            "[MEM_CAL_CNTB] Allocation failed in bucket %d [ size %lu bytes], %lu times\n", regCb->mapTbl[idx].bktIdx, bkt->size, bkt->bktFailCnt);
#endif            
            SDisplay(0, prntBuf);
#endif
         }

#if (ERRCLASS & ERRCLS_DEBUG)
         regCb->mapTbl[idx].numFailure++;
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

         /* Release the lock */
         /* cm_mem_c_001.main_13: Replaced SUnlock with WTUnlock for NT */
#ifdef SS_WIN
            (Void) WTUnlock(&(bkt->bktLock));
#else
            (Void) SUnlock(&(bkt->bktLock));
#endif
         cnt = cnt + 1;
      }
   }
   else
   {
      if (flags)
      {
         regCb->heapCb.heapAllocCnt++;
#ifdef MEMCAL_DEBUG
/*cm_mem_c_001.main_23 Fix for specifier mismatch warnings in 64BIT compilation*/          
#ifdef ALIGN_64BIT          
         sprintf(prntBuf,
                 "[MEM_CAL_CNTC]  No bucket block configured for %u bytes \n Number of blocks allocated from heap = %u\n",*size,
                 regCb->heapCb.heapAllocCnt);
#else                 
         sprintf(prntBuf,
                 "[MEM_CAL_CNTC]  No bucket block configured for %lu bytes \n Number of blocks allocated from heap = %lu\n",*size,
                 regCb->heapCb.heapAllocCnt);
#endif                 
         SDisplay(0, prntBuf);
#endif
      }
   }

   /* Memory not available in the bucket pool */
   if (regCb->heapFlag &&  (*size < regCb->heapSize))
   {
#ifdef MEMCAL_DEBUG
      if (flags) tryHeap = 1;
#endif
      /* 
       * The heap memory block is available. Allocate the memory block from
       * heap pool.
       */ 
/* cm_mem_c_001.main_15: Additions */
#ifdef SS_HISTOGRAM_SUPPORT  
/* cm_mem_c_001.main_12 - addition for passing an extra parameter */
#ifdef SSI_DEBUG_LEVEL1
       RETVALUE(cmHeapAlloc(&(regCb->heapCb), ptr, size, memType, line, fileName, entId, hstReg));
#else
       RETVALUE(cmHeapAlloc(&(regCb->heapCb), ptr, size, line, fileName, entId, hstReg));
#endif /* SSI_DEBUG_LEVEL1 */
#else
/* cm_mem_c_001.main_12 - addition for passing an extra parameter */
#ifdef SSI_DEBUG_LEVEL1
       RETVALUE(cmHeapAlloc(&(regCb->heapCb), ptr, size, memType));
#else
       RETVALUE(cmHeapAlloc(&(regCb->heapCb), ptr, size));
#endif /* SSI_DEBUG_LEVEL1 */
#endif /* SS_HISTOGRAM_SUPPORT */
   }

   /* No memory available */
   RETVALUE(RFAILED);
#else /* use pure is on */
/*cm_mem_c_001.main_27 SSI-4GMX specfic changes*/   
#ifdef SS_4GMX_LCORE
   *ptr = (Data*) MxHeapAlloc(SsiHeap, *size);
   cmMemset((U8*)ptr, 0, *size);
#else
   *ptr = (Data*) malloc(*size);
#endif
   if ( (*ptr) == NULLP)
       RETVALUE(RFAILED);
   avail_size -= *size;
   RETVALUE(ROK);
#endif /* USE_PURE */

} /* end of cmAlloc */

#ifdef SS_MEM_WL_DEBUG
/*
*
*       Fun:   cmInitDoubleFreeList
*
*       Desc:  Initialize the hashlist used for detecting double free
*
*       Ret:   ROK     - successful
*              RFAILED - unsuccessful.
*
*       Notes:
*
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PUBLIC S16  cmInitDoubleFreeList
(
Void
)
#else
PUBLIC S16  cmInitDoubleFreeList()
#endif
{
    U16              offset;
    CmMemDoubleFree  memNode;

    TRC2(cmInitDoubleFreeList);

    offset = (U16)((PTR)(&memNode.tmpListEnt) - (PTR)&memNode);

    if((cmHashListInit(&(memDoubleFree), 1000, offset, 0,
        CM_HASH_KEYTYPE_U32MOD, 0, 0)) != ROK);
    {
        RETVALUE(RFAILED);
    }
    SInitLock(&memDoubleFreeLock, SS_LOCK_MUTEX);

    RETVALUE(ROK);
}

#ifdef SS_MEM_WL_DEBUG 
/*
*
*       Fun:   cmInitBtInfo
*
*       Desc:  Return the Dynamic memory block for the memory region.
*
*
*       Ret:   ROK     - successful
*              RFAILED - unsuccessful.
*
*       Notes:
*
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PRIVATE S16  cmInitBtInfo
(
)
#else
PRIVATE S16  cmInitBtInfo (Void)
#endif
{
   regBtInfo = (CmBtInfo *)calloc(1, 8 * sizeof (CmBtInfo));
   if (regBtInfo == NULLP)
   {
      RETVALUE(RFAILED);
   }
   allocBtInfo = (CmBtInfo *)calloc(1, 8 * sizeof (CmBtInfo));
   if(allocBtInfo == NULLP)
   {
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}
#endif /* SS_MEM_WL_DEBUG */
/*
*
*       Fun:   cmAnalyseBtInfo
*
*       Desc:  Return the Dynamic memory block for the memory region.
*
*
*       Ret:   ROK     - successful
*              RFAILED - unsuccessful.
*
*       Notes:
*
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PUBLIC Void  cmAnalyseBtInfo
(
PTR   ptr,       /* Memory block needs to be freed */
U32   idx
)
#else
PUBLIC Void  cmAnalyseBtInfo (ptr,idx)
PTR   ptr;        /* Memory block needs to be freed */
U32   idx;
#endif
{
   U32  tmpCnt;
   U32  btIdx;
   CmBtInfo  *btInfo;
   U8    regIdx;

#if 0
   for(regIdx = 0; regIdx < 8; regIdx++)
   {
      btInfo = & regBtInfo[regIdx];
      btIdx = btInfo->btInfoIdx;
   
      for (tmpCnt = 0; tmpCnt < NUM_FREE_BUFFERS; tmpCnt++)  
      {
#if 0
         if ((btInfo->btInfo[btIdx].ptr >= ptr) &&   
             (btInfo->btInfo[btIdx].ptr + 128 ) >= ptr)    
   
#endif
         if(btInfo->btInfo[btIdx].btSize != 0)
         {
           U32 i;
           char **strings;
           strings = backtrace_symbols( btInfo->btInfo[btIdx].btArr,btInfo->btInfo[btIdx].btSize);
           printf("*** Last Free Region = %d PTR %x Timestamp sec = (%ld) usec = (%ld) ***\n", idx, ptr, btInfo->btInfo[btIdx].timeStamp.tv_sec, btInfo->btInfo[btIdx].timeStamp.tv_usec);
           for (i=0; i < btInfo->btInfo[btIdx].btSize; i++)
           {
              printf("%s\n", strings[i]); 
           }
           printf("*******************************************************\n");
           
           free(strings);
         }
   
         btIdx--; 
         if (btIdx == 0)
         {
            btIdx = NUM_FREE_BUFFERS - 1;
         }
      }
   }
#endif


/*   for(regIdx = 0; regIdx < 8; regIdx++)
   { */
   idx = 2;
      btInfo = &allocBtInfo[idx];
      btIdx = btInfo->btInfoIdx;
   
      for (tmpCnt = 0; tmpCnt < NUM_FREE_BUFFERS; tmpCnt++)  
      {
/*         if ((btInfo->btInfo[btIdx].ptr >= ptr) &&   
             (btInfo->btInfo[btIdx].ptr + 128 ) >= ptr)    */
         if(btInfo->btInfo[btIdx].btSize != 0)
         {
           U32 i;
           char **strings;
           strings = backtrace_symbols( btInfo->btInfo[btIdx].btArr,btInfo->btInfo[btIdx].btSize);
           printf("*** Last Allocation Region = %d PTR %x Timestamp sec = (%ld) usec = (%ld) ***\n", idx, ptr, btInfo->btInfo[btIdx].timeStamp.tv_sec, btInfo->btInfo[btIdx].timeStamp.tv_usec);
           for (i=0; i < btInfo->btInfo[btIdx].btSize; i++)
           {
              printf("%s\n", strings[i]); 
           }
           printf("*******************************************************\n");
           
           free(strings);
         }
   
         btIdx--; 
         if (btIdx == 0)
         {
            btIdx = NUM_FREE_BUFFERS - 1;
         }
      }
/*    } */

   RETVOID;
}
#endif

#ifndef SS_USE_ICC_MEMORY
/*
*
*       Fun:   cmDynFreeWithLock
*
*       Desc:  Return the Dynamic memory block for the memory region.
*
*
*       Ret:   ROK     - successful
*              RFAILED - unsuccessful.
*
*       Notes:
*
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PRIVATE S16  cmDynFreeWithLock
(
Void   *regionCb,   /* Pointer to region cb */
Data   *ptr,        /* Memory block needs to be freed */
Size    size        /* Size of the block */
)
#else
PRIVATE S16  cmDynFreeWithLock(regionCb, ptr, size)
Void   *regionCb;   /* Pointer to region cb */
Data   *ptr;        /* Memory block needs to be freed */
Size    size;       /* Size of the block */
#endif
{
   S16 ret;

   if((SLock(&dynAllocFreeLock)) != ROK)
   {
      printf("dynAllocWithLock: Failed to get the DYN lock\n");
      RETVALUE(RFAILED);
   }

   ret = cmDynFree(regionCb, ptr,size);

   if((SUnlock(&dynAllocFreeLock)) != ROK)
   {
      printf("dynAllocWithLock: Failed to unlock the dyn lock\n");
      RETVALUE(RFAILED);
   }

   RETVALUE(ret);

} /* end of cmDynFree */

/*
*
*       Fun:   cmDynFree
*
*       Desc:  Return the Dynamic memory block for the memory region.
*
*
*       Ret:   ROK     - successful
*              RFAILED - unsuccessful.
*
*       Notes:
*
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PRIVATE S16  cmDynFree
(
Void   *regionCb,   /* Pointer to region cb */
Data   *ptr,        /* Memory block needs to be freed */
Size    size        /* Size of the block */
)
#else
PRIVATE S16  cmDynFree(regionCb, ptr, size)
Void   *regionCb;   /* Pointer to region cb */
Data   *ptr;        /* Memory block needs to be freed */
Size    size;       /* Size of the block */
#endif
{
   U32                 idx;
   U32                 bktIdx;
   CmMmDynBktCb       *bkt = NULLP;
   CmMmDynRegCb       *regCb;
   CmMmBlkSetElement  *dynMemElem;
#ifdef SS_MEM_WL_DEBUG
   U8                 tmpBktIdx;
   U8                 tmpVal;
#endif

   TRC2(cmDynFree);

   regCb = (CmMmDynRegCb *)regionCb;
#ifdef SS_MEM_WL_DEBUG
   if((tmpRegTidMap[regCb->region] != (pthread_self())))
   {
      bkt->size = 10;
   }
#endif

#ifndef USE_PURE
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* error check on parameters */
   if ((regCb == NULLP) || (!size) || (ptr == NULLP))
   {
      RETVALUE(RFAILED);
   }

   /* Check if the memory block is from the memory region */
   if (ptr >= ((CmMmRegCb *)regCb)->regInfo.start +
               ((CmMmRegCb *)regCb)->regInfo.size) 
   {
      RETVALUE(RFAILED);
   }
	/* cm_mem_c_001.main_20 Addition */
	if (ptr < regCb->regInfo.start)
	{
	  RETVALUE(RFAILED);
	}

#endif

#ifdef SS_MEM_WL_DEBUG
   ptr -= sizeof (U32);
   size += 4;
#endif
   /* The memory block was allocated from the bucket pool */

   /* Get the map to the mapping table */
   idx = ((size - 1) >> regCb->bktQnPwr);

#if (ERRCLASS & ERRCLS_DEBUG)
   if (regCb->mapTbl[idx].bktIdx == 0xFF)
   { 
      /* Some fatal error in the map table initialization. */
      RETVALUE(RFAILED);
   }
#endif

   /* Enqueue the memory block and return it to the user */
   bkt = &(regCb->bktTbl[bktIdx = regCb->mapTbl[idx].bktIdx]);

   /*
    * Check if the size is not greater than the size available
    * in the bucket. If so, then the buffer must have been allocated
    * from next bucket.  We don't need to check the validity of the
    * next bucket, otherwise buffer must have been allocated from heap
    * pool.
    */
#ifdef SS_MEM_WL_DEBUG
   if (size > bkt->size)
   {
      printf("Size = %d bucket size = %d\n", size, bkt->size);
      exit(-1);
      bkt = &(regCb->bktTbl[bktIdx = regCb->mapTbl[++idx].bktIdx]);
   }
   if(size > bkt->size)
   {
      printf("2nd time Size = %d bucket size = %d\n", size, bkt->size);
      exit(-1);
      U8 *tmpptr = NULLP;
      printf("Bucket Size wrong \n");
      *tmpptr =  10;
   }
#endif

   dynMemElem = cmGetMemBlkSetForFree(bktIdx, bkt);

   /* Check if the bucket index, if its not valid, return failure */
   if(dynMemElem == NULLP)
   {
      RETVALUE(RFAILED);
   }

#ifdef SS_MEM_WL_DEBUG
   tmpBktIdx = (U8)*ptr;
   tmpVal  =  (U8)*(ptr+1);

   if ((tmpBktIdx != bktIdx) || (tmpVal != 0xde))
   {
      U8 *tmpptr = NULLP;
      printf("bktIdx wrong \n");
      *tmpptr =  10;
   }

   if ((bktIdx == 0) && (!stopBtInfo))
   {
      CmBtInfo *btInfo;
      U32      btIdx;
      btInfo  = &regBtInfo[regCb->region];
      btIdx = btInfo->btInfoIdx;
      btInfo->btInfo[btIdx].ptr = (PTR) ptr;
      {
         btInfo->btInfo[btIdx].btSize  = backtrace(btInfo->btInfo[btIdx].btArr, NUM_BT_TRACES);
      }
#if 0
       cmRemoveAllocPtrFromList(regCb, (ptr + sizeof(U32)));
#endif
      gettimeofday(&(btInfo->btInfo[btIdx].timeStamp), NULLP);

      btIdx++;
      btIdx &= (NUM_FREE_BUFFERS - 1); 

      btInfo->btInfo[btIdx].ptr = (PTR)0;
      btInfo->btInfo[btIdx].btSize = 0;
      cmMemset(btInfo->btInfo[bktIdx].btArr, 0, sizeof (btInfo->btInfo[bktIdx].btArr));
      btInfo->btInfoIdx = btIdx;
   }
   
   if(prvAllocPtr[regCb->region] == ptr)
   {
      prvAllocPtr[regCb->region] = NULLP;
   }

   cmMemset(ptr, (regCb->region+1), bkt->size); 
#endif

   /* Get the bucket node from the index returned and allocate the memory */
   *((CmMmEntry **)ptr) =  dynMemElem->nextBktPtr;
   dynMemElem->nextBktPtr = ptr;
   dynMemElem->numFreeBlks++;

   RETVALUE(ROK);

#else /* use pure is on */
   TRC2(cmDynFree);
/*cm_mem_c_001.main_27 SSI-4GMX specfic changes*/   
#ifdef SS_4GMX_LCORE
   (Void)MxHeapFree(SsiHeap, ptr);
#else
   /* (Void)free(ptr); */
#endif
/*   avail_size += size; */
#ifndef USE_PURE
   tcfree(ptr);
#else
   (Void)free(ptr);
#endif

   RETVALUE(ROK);
#endif /* USE_PURE */


} /* end of cmDynFree */
#endif /* SS_USE_ICC_MEMORY */



/*
*
*       Fun:   cmFree
*
*       Desc:  Return the memory block for the memory region.
*
*
*       Ret:   ROK     - successful
*              RFAILED - unsuccessful.
*
*       Notes: The user calls this function to return the previously allocated 
*              memory block to the memory region. The memory manager does not 
*              check the validity of the state of the memory block(like whether 
*              it was allocated earlier). The caller must be sure that, the 
*              address specified in the parameter 'ptr' is valid and was 
*              allocated previously from same region.
*
*
*       File:  cm_mem_wl.c
*
*/

/*  cm_mem_c_001.main_15 : Additions */
#ifdef T2K_MEM_LEAK_DBG
PRIVATE S16  cmFree
(
 Void   *regionCb,
 Data   *ptr,
 Size    size,
 char* file,
 U32 line
)
#else
#ifdef SS_HISTOGRAM_SUPPORT
#ifdef ANSI
PRIVATE S16  cmFree
(
Void   *regionCb,
Data   *ptr,
Size    size,
U32     line,
U8     *fileName,
U8      entId,
Bool    hstReg
)
#else
PRIVATE S16  cmFree(regionCb, ptr, size, line, fileName, entId, hstReg)
Void   *regionCb;
Data   *ptr;
Size    size;
U32     line;
U8     *fileName;
U8      entId;
Bool    hstReg;
#endif

#else

#ifdef ANSI
PRIVATE S16  cmFree
(
Void   *regionCb,
Data   *ptr, 
Size    size
)
#else
PRIVATE S16  cmFree(regionCb, ptr, size)
Void   *regionCb;
Data   *ptr;
Size    size;
#endif
#endif
/*  cm_mem_c_001.main_15 : Additions */
#endif /* SS_HISTOGRAM_SUPPORT */ 

{
/* cm_mem_c_001.main_26 : Fixes for Compilation Warnings */
#ifndef USE_PURE
   U16        idx;
   CmMmBkt   *bkt;
   U16   bktIdx;
#endif
   CmMmRegCb *regCb;
/* cm_mem_c_001.main_12 - addition for holding the free pointer */
#ifdef SSI_DEBUG_LEVEL1
   CmMmBlkHdr *ptrHdr;
#endif /* SSI_DEBUG_LEVEL1 */
/*  cm_mem_c_001.main_15 : Additions */
#ifdef SS_HISTOGRAM_SUPPORT 
	S8 hstGrmBuf[256];
#endif /* SS_HISTOGRAM_SUPPORT */

   TRC2(cmFree);

   regCb = (CmMmRegCb *)regionCb;

#ifndef USE_PURE
#if (ERRCLASS & ERRCLS_INT_PAR)

   /* error check on parameters */
   if ((regCb == NULLP) || (!size) || (ptr == NULLP))
   {
      RETVALUE(RFAILED);
   }

   /* Check if the memory block is from the memory region */
   if (ptr >= ((CmMmRegCb *)regCb)->regInfo.start +
               ((CmMmRegCb *)regCb)->regInfo.size) 
   {
      RETVALUE(RFAILED);
   }
	/* cm_mem_c_001.main_20 Addition */
	if (ptr < regCb->regInfo.start)
	{
	  RETVALUE(RFAILED);
	}

#endif

   /* 
    * Check if the memory block was allocated from the bucket pool. 
    */
   if(ptr < regCb->regInfo.start)
   {
      Buffer *tmpBuffer = NULLP;
      tmpBuffer->b_cont = NULLP;
   }

   if (ptr < (regCb->regInfo.start + regCb->bktSize))
   {
      /* The memory block was allocated from the bucket pool */

      /* Get the map to the mapping table */
      idx = ((size - 1) >> regCb->bktQnPwr);

#if (ERRCLASS & ERRCLS_DEBUG)
      if (regCb->mapTbl[idx].bktIdx == 0xFF)
      { 
         /* Some fatal error in the map table initialization. */
         RETVALUE(RFAILED);
      }
#endif

      /* Enqueue the memory block and return it to the user */
      bkt = &(regCb->bktTbl[bktIdx = regCb->mapTbl[idx].bktIdx]);

      /*
       * Check if the size is not greater than the size available
       * in the bucket. If so, then the buffer must have been allocated
       * from next bucket.  We don't need to check the validity of the
       * next bucket, otherwise buffer must have been allocated from heap
       * pool.
       */
       if (size > bkt->size)
       {
          bkt = &(regCb->bktTbl[bktIdx = regCb->mapTbl[++idx].bktIdx]);
       }

      /* Acquire the bucket lock */
      /* cm_mem_c_001.main_13 : Replaced SLock with WTLock for NT */
#ifdef SS_WIN
      (Void) WTLock(&(bkt->bktLock));
#else
      (Void) SLock(&(bkt->bktLock));
#endif

/* cm_mem_c_001.main_12 - addition for sanity check and free */
#ifdef SSI_DEBUG_LEVEL1
      /* increment the dealloc attempt counter at bucket level */
      bkt->numDeallocAttempts++;

      /* Check the memFlags to see whether this block was allocated */
      ptrHdr = (CmMmBlkHdr *) (ptr - sizeof(CmMmBlkHdr));

      /* validate the block to be freed for trampling */
      if (cmMmRegIsBlkSane(ptrHdr) != ROK)
      {
          /* Handle error case of Memory trampling */
      #ifdef  DEBUGP
          /* display an error message here */
/*cm_mem_c_001.main_23 Fix for specifier mismatch warnings in 64BIT compilation*/          
#ifdef ALIGN_64BIT          
          sprintf(dbgPrntBuf, "Memory Trampling at: %8p, Bucket Id:%03d, size %u bytes \n",
                               ptr, regCb->mapTbl[idx].bktIdx, bkt->size);
#else                               
          sprintf(dbgPrntBuf, "Memory Trampling at: %8p, Bucket Id:%03d, size %lu bytes \n",
                               ptr, regCb->mapTbl[idx].bktIdx, bkt->size);
#endif                               
          SDisplay(0, dbgPrntBuf);
      #endif /* DEBUGP */
           /* 
           * if sanity check returns RTRAMPLINGOK then there is nothing to do
           * as the memory blk is already invalidated in cmMmBktSanityChk
           */
           if (cmMmBktSanityChk(bkt) == RTRAMPLINGOK)
           {
              bkt->numAlloc--;

              /* Release the lock */
              /* cm_mem_c_001.main_13: Replaced SUnlock with WTUnlock for NT */
#ifdef SS_WIN
              (Void) WTUnlock(&(bkt->bktLock));
#else
              (Void) SUnlock(&(bkt->bktLock));
#endif

              RETVALUE(ROK);
           }
           else
           {
               /* 
               * this is the case where in the entire bucket has been made unusable
               * Release the lock 
               */
               /* cm_mem_c_001.main_13: Replaced SUnlock with WTUnlock for NT */
#ifdef SS_WIN
               (Void) WTUnlock(&(bkt->bktLock));
#else
               (Void) SUnlock(&(bkt->bktLock));
#endif

                /* handle RTRAMPLINGNOK in SFree/SPutSBuf */
                RETVALUE(RTRAMPLINGNOK);
           }
      }

      /* reset the size */
      ptrHdr->requestedSize = 0;
      /* check if the block to be freed is already having the state as FREE */
      if (CMM_IS_FREE(ptrHdr->memFlags))
      {
            /* Handle double deallocation error case */
      #ifdef DEBUGP
            /* display an error message here */
/*cm_mem_c_001.main_23 Fix for specifier mismatch warnings in 64BIT compilation*/          
#ifdef ALIGN_64BIT          
         sprintf(dbgPrntBuf, "Attempt to double deallocate memory at: %8p, Bucket Id:%03d, size %u bytes \n",
                              ptr, regCb->mapTbl[idx].bktIdx, bkt->size);
#else                              
         sprintf(dbgPrntBuf, "Attempt to double deallocate memory at: %8p, Bucket Id:%03d, size %lu bytes \n",
                              ptr, regCb->mapTbl[idx].bktIdx, bkt->size);
#endif                              
         SDisplay(0, dbgPrntBuf);
      #endif /* DEBUGP */

          /* Release the lock */
          /* cm_mem_c_001.main_13: Replaced SUnlock with WTUnlock for NT */
#ifdef SS_WIN
          (Void) WTUnlock(&(bkt->bktLock));
#else
          (Void) SUnlock(&(bkt->bktLock));
#endif

          /* handle RDBLFREE in SFree/SPutSBuf */
          RETVALUE(RDBLFREE);
      }
      if (CMM_IS_STATIC(ptrHdr->memFlags))
      {
         CMM_SET_FREE_FLAG(ptrHdr->memFlags);
         CMM_RESET_STATIC_FLAG(ptrHdr->memFlags);
         /* deduct it from the static memory count */
         bkt->staticMemUsed -= bkt->size;
      }
      else if (CMM_IS_DYNAMIC(ptrHdr->memFlags))
      {
         CMM_SET_FREE_FLAG(ptrHdr->memFlags);
         CMM_RESET_DYNAMIC_FLAG(ptrHdr->memFlags);
         /* deduct it from the dynamic memory count */
         bkt->dynamicMemUsed -= bkt->size;
      }
      else
      {
         /* This is a case similar to trampled memory */
      #ifdef  DEBUGP
/*cm_mem_c_001.main_23 Fix for specifier mismatch warnings in 64BIT compilation*/          
#ifdef ALIGN_64BIT          
         sprintf(dbgPrntBuf, "Invalid memory flag: %u !!!\n", ptrHdr->memFlags);
#else         
         sprintf(dbgPrntBuf, "Invalid memory flag: %lu !!!\n", ptrHdr->memFlags);
#endif         
         SDisplay(0, dbgPrntBuf);
      #endif /* DEBUGP */
         if (cmMmBktSanityChk(bkt) == RTRAMPLINGOK)
         {
            /* do not add to the free list */
            bkt->numAlloc--;

            /* Release the lock */
            /* cm_mem_c_001.main_13: Replaced SUnlock with WTUnlock for NT */
#ifdef SS_WIN
            (Void) WTUnlock(&(bkt->bktLock));
#else
            (Void) SUnlock(&(bkt->bktLock));
#endif
            RETVALUE(ROK);
         }
         else
         {
            /* 
            * this is the case where in the entire bucket has been made unusable
            * Release the lock 
            */
            /* cm_mem_c_001.main_13: Replaced SUnlock with WTUnlock for NT */
#ifdef SS_WIN
            (Void) WTUnlock(&(bkt->bktLock));
#else
            (Void) SUnlock(&(bkt->bktLock));
#endif

            /* handle RTRAMPLINGNOK in SFree/SPutSBuf */
            RETVALUE(RTRAMPLINGNOK);
         }
      }

      /* Return the block to memory */
      ptrHdr->nextBlk = bkt->nextBlk;
      bkt->nextBlk = ptrHdr;
#else
      /* MS_REMOVE */
#if 0
      /* sriky: For debugging double deallocation */
      cmMemset(ptr, 0, 50);
#endif
      *((CmMmEntry **)ptr) =  bkt->next; 
      bkt->next = (CmMmEntry *)ptr;
#endif /* SSI_DEBUG_LEVEL1 */

#if 0
      if(bkt->numAlloc <= 0 || bkt->numAlloc > 12000)
      {
         void *array[10];
         size_t tmpsize, i;
         char **strings;

         printf("\n cmFree: Freed pointer = %x and backtrace:\n", ptr);
         printf("****************************************\n");
         tmpsize = backtrace(array, 10);
         strings = backtrace_symbols(array, tmpsize);
         for(i = 0; i < tmpsize; i++)
           printf("%s\n", strings[i]);
         printf("****************************************\n");
         free(strings);
      }
#endif
      /* 
      * Decrement the statistics variable of number of memory block 
      * allocated 
      */
      if(bkt->numAlloc)
      {
         bkt->numAlloc--;
      }
      {
        if (g_overused[bktIdx] == 1 && !OVERUSED(bkt))
        {
           g_overused[bktIdx] = 0;
           /*printf("cmFree: bktIdx %u overused %u numAlloc %u\n", bktIdx, g_overused[bktIdx], bkt->numAlloc); */
        }
      }
/*  cm_mem_c_001.main_15 : Additions */
#ifdef SS_HISTOGRAM_SUPPORT
        /* If If Tapa task (entId)is registerd for histogram then insert Memrory Freed
         * information into the hash list */
        if(hstReg)
        {
            if (cmHstGrmFreeInsert(&bkt->hstGrmHashListCp, bkt->size, line, fileName, entId) != ROK)
            {
                 sprintf(hstGrmBuf, "Unable to Insert into the histgram hash list\n");
					  SPrint(hstGrmBuf);
            }
         }/* End of if */
#endif /* SS_HISTOGRAM_SUPPORT */

#ifdef SS_MEM_LEAK_STS
      /* cm_mem_c_001.main_25 - Fixed compilation warnings 32/64 bit */
      cmRlsAllocBlk((PTR)ptr);
#endif /* SS_MEM_LEAK_STS */

      /* Release the lock */
      /* cm_mem_c_001.main_13: Replaced SUnlock with WTUnlock for NT */
#ifdef SS_WIN
      (Void) WTUnlock(&(bkt->bktLock));
#else
      (Void) SUnlock(&(bkt->bktLock));
#endif

      RETVALUE(ROK);
   }

   /* The memory block was allocated from the heap pool */ 
/*  cm_mem_c_001.main_15 : Additions */
#ifdef SS_HISTOGRAM_SUPPORT 
   RETVALUE(cmHeapFree (&(regCb->heapCb), ptr, size, line, fileName, entId, hstReg));
#else
   RETVALUE(cmHeapFree (&(regCb->heapCb), ptr, size));
#endif /* SS_HISTOGRAM_SUPPORT */
#else /* use pure is on */
   TRC2(cmFree);
/*cm_mem_c_001.main_27 SSI-4GMX specfic changes*/   
#ifdef SS_4GMX_LCORE
   (Void)MxHeapFree(SsiHeap, ptr);
#else
   (Void)free(ptr);
#endif
   avail_size += size;
   RETVALUE(ROK);
#endif /* USE_PURE */


} /* end of cmFree */


/*
*
*       Fun:   cmAllocWL
*
*       Desc: alloc without lock 
*
*
*       Ret:   ROK     - successful
*              RFAILED - unsuccessful.
*
*
*       File:  cm_mem_wl.c
*
*/
/*cm_mem_c_001.main_21-added new function*/
/*cm_mem_c_001.main_23 Removed support of SSI_DEBUG_LEVEL1 and SS_HISTOGRAM_SUPPORT for SS_FAP*/
#ifdef T2K_MEM_LEAK_DBG
PRIVATE S16  cmAllocWL
(
Void   *regionCb,
Size   *size,
U32     flags,
Data  **ptr ,
char* file,
U32 line
)
#else
#ifdef ANSI
PRIVATE S16  cmAllocWL
(
Void   *regionCb,
Size   *size,
U32     flags,
Data  **ptr 
)
#else
PRIVATE S16  cmAllocWL(regionCb, size, flags, ptr)
Void   *regionCb;
Size   *size;
U32     flags;
Data  **ptr;
#endif
#endif
{
   U16        idx;
   CmMmBkt   *bkt = NULLP;
   CmMmRegCb *regCb;
   /*cm_mem_c_001.main_23 Removed support of SSI_DEBUG_LEVEL1 and SS_HISTOGRAM_SUPPORT for SS_FAP*/

   TRC2(cmAllocWL);

   /*cm_mem_c_001.main_23 Removed support of  USE_MEMCAL and MEMCAL_DEBUG support for  SS_FAP*/

   regCb = (CmMmRegCb *)regionCb;

#ifdef SS_MEM_WL_DEBUG
   if((tmpRegTidMap[regCb->region] != (pthread_self())))
   {
      bkt->size = 10;
   }
#endif

#if (ERRCLASS & ERRCLS_INT_PAR)

   /* error check on parameters */
   if ((regCb == NULLP) || (size == NULLP) || !(*size) || (ptr == NULLP))
   {
      RETVALUE(RFAILED);
   }
#endif
  
   /*cm_mem_c_001.main_23 Removed support of SSI_DEBUG_LEVEL1 and SS_HISTOGRAM_SUPPORT for SS_FAP*/

#ifndef USE_PURE 

   /* 
    * Check if the requested size is less than or equal to the maximum block 
    * size in the bucket. 
    */
#ifdef MSPD_T2K_TRACK_BUG
   *size += 4;
#endif
   /* cm_mem_c_001.main_23 Adding check to compair size with Maximum block size*/
   if ( *size <= regCb->bktMaxBlkSize)
   {
      /* Get the map to the mapping table */
      idx = ((*size - 1) >> regCb->bktQnPwr);

      /* Dequeue the memory block and return it to the user */
      bkt = &(regCb->bktTbl[regCb->mapTbl[idx].bktIdx]); 

      {
         /*
          * Check if the size request is not greater than the size available
          * in the bucket
          */
         /* cm_mem_c_001.main_23 combined If(*size <= bkt->size) and if(*ptr = bkt->next)*/
         if ((*size <= bkt->size)&&(*ptr = bkt->next))
         {
            /* Try to go to the next bucket if available */
            bkt->next = *((CmMmEntry **)(bkt->next));

            /* 
             * Increment the statistics variable of number of memory block 
             * allocated 
             */
            bkt->numAlloc++;
            if (bkt->numAlloc > bkt->maxAlloc)
            {
               bkt->maxAlloc = bkt->numAlloc;
            }

#ifdef MSPD_T2K_TRACK_BUG
            *(*ptr + 0) = 0xDE;
            *(*ptr + 1) = 0xAD;
            *(*ptr + 2) = 0xBE;
            *(*ptr + 3) = 0xEF;

            (*ptr) += 4;
#endif

            /* Update the size parameter */
            *size = bkt->size;

            RETVALUE(ROK);
         }
      }
   }

   /* Memory not available in the bucket pool */
   if (regCb->heapFlag &&  (*size < regCb->heapSize))
   {
      /*cm_mem_c_001.main_23 Removed support of  and MEMCAL_DEBUG support for  SS_FAP*/
      /* 
       * The heap memory block is available. Allocate the memory block from
       * heap pool.
       */ 
       /*cm_mem_c_001.main_23 Removed support of SSI_DEBUG_LEVEL1 and SS_HISTOGRAM_SUPPORT for SS_FAP*/
       RETVALUE(cmHeapAlloc(&(regCb->heapCb), ptr, size));
   }

   /* No memory available */
   RETVALUE(RFAILED);
#else /* use pure is on */
/*cm_mem_c_001.main_27 SSI-4GMX specfic changes*/   
#ifdef SS_4GMX_LCORE
   *ptr = (Data*) MxHeapAlloc(SsiHeap, *size);
   cmMemset((U8*)ptr, 0, *size);
#else
/*   *ptr = (Data*) malloc(*size); */
#endif

#ifndef USE_PURE
   *ptr = (Data *)tcmalloc(*size);
#else
   *ptr = (Data*) malloc(*size);
#endif

   if ( (*ptr) == NULLP)
       RETVALUE(RFAILED);
/*   avail_size -= *size; */
   RETVALUE(ROK);
#endif /* USE_PURE */

} /* end of cmAllocWL */


/*
*
*       Fun:   cmfree
*
*       Desc: free without lock 
*
*
*       Ret:   ROK     - successful
*              RFAILED - unsuccessful.
*
*
*       File:  cm_mem_wl.c
*
*/

#ifdef T2K_MEM_LEAK_DBG
PRIVATE S16  cmFreeWL
(
Void   *regionCb,
Data   *ptr, 
Size    size,
char* file,
U32 line
)
#else
#ifdef ANSI
PRIVATE S16  cmFreeWL
(
Void   *regionCb,
Data   *ptr, 
Size    size
)
#else
PRIVATE S16  cmFreeWL(regionCb, ptr, size)
Void   *regionCb;
Data   *ptr;
Size    size;
#endif
#endif
{
   U16        idx;
   CmMmBkt   *bkt = NULLP;
   CmMmRegCb *regCb;
   /*cm_mem_c_001.main_23 Removed support of SSI_DEBUG_LEVEL1 and SS_HISTOGRAM_SUPPORT for SS_FAP*/

   TRC2(cmFreeWL);

   regCb = (CmMmRegCb *)regionCb;

#ifdef SS_MEM_WL_DEBUG
   if(tmpRegTidMap[regCb->region] != (pthread_self()))
   {
      bkt->size = 10;
   }
#endif

#ifndef USE_PURE
#if (ERRCLASS & ERRCLS_INT_PAR)

   /* error check on parameters */
   if ((regCb == NULLP) || (!size) || (ptr == NULLP))
   {
      RETVALUE(RFAILED);
   }

   /* Check if the memory block is from the memory region */
   if (ptr >= ((CmMmRegCb *)regCb)->regInfo.start +
               ((CmMmRegCb *)regCb)->regInfo.size) 
   {
      RETVALUE(RFAILED);
   }

#endif

   /* 
    * Check if the memory block was allocated from the bucket pool. 
    */
#if 0
   if(ptr < regCb->regInfo.start)
   {
      Buffer *tmpbuf = NULLP;
      tmpbuf->b_cont = NULLP;
   }
#endif

#ifdef MSPD_T2K_TRACK_BUG
   size += 4;
#endif

   if (ptr < (regCb->regInfo.start + regCb->bktSize))
   {
      /* The memory block was allocated from the bucket pool */

      /* Get the map to the mapping table */
      idx = ((size - 1) >> regCb->bktQnPwr);

#if (ERRCLASS & ERRCLS_DEBUG)
      if (regCb->mapTbl[idx].bktIdx == 0xFF)
      { 
         /* Some fatal error in the map table initialization. */
         RETVALUE(RFAILED);
      }
#endif

      /* Enqueue the memory block and return it to the user */
      bkt = &(regCb->bktTbl[regCb->mapTbl[idx].bktIdx]); 

#ifdef MSPD_T2K_TRACK_BUG
      ptr -= 4;
      if((ptr[0] != 0xDE) || (ptr[1] != 0xAD) || (ptr[2] != 0xBE) || (ptr[3] != 0xEF))
      {
          char *abc = NULLP;
          *abc = 100;
      }
#endif
      /*
       * Check if the size is not greater than the size available
       * in the bucket. If so, then the buffer must have been allocated
       * from next bucket.  We don't need to check the validity of the
       * next bucket, otherwise buffer must have been allocated from heap
       * pool.
       */
       if (size > bkt->size)
       {
          bkt = &(regCb->bktTbl[regCb->mapTbl[++idx].bktIdx]);
       }

      /*cm_mem_c_001.main_23 Removed support of SSI_DEBUG_LEVEL1 and SS_HISTOGRAM_SUPPORT for SS_FAP*/
      *((CmMmEntry **)ptr) =  bkt->next; 
      bkt->next = (CmMmEntry *)ptr;

      /* 
      * Decrement the statistics variable of number of memory block 
      * allocated 
      */
      bkt->numAlloc--;

#if 0
      if ((regCb->region == 2) && (bkt->numAlloc < 50))
      {
         CmBtInfo *btInfo;
         U32      btIdx;
         btInfo  = &allocBtInfo[regCb->region];
         btIdx = btInfo->btInfoIdx;
         btInfo->btInfo[btIdx].ptr = (PTR) *ptr;
         {
            btInfo->btInfo[btIdx].btSize  = backtrace(btInfo->btInfo[btIdx].btArr, NUM_BT_TRACES);
         }
#if 0
         gettimeofday(&(btInfo->btInfo[btIdx].timeStamp), NULLP);
         cmInsertAllocPtrToList(regCb, (PTR)*ptr);
#endif
   
         btIdx++;
         btIdx &= (NUM_FREE_BUFFERS - 1); 
   
         btInfo->btInfo[btIdx].ptr = (PTR)0;
         btInfo->btInfo[btIdx].btSize = 0;
         cmMemset(btInfo->btInfo[regCb->mapTbl[idx].bktIdx].btArr, 0, sizeof (btInfo->btInfo[regCb->mapTbl[idx].bktIdx].btArr));
         btInfo->btInfoIdx = btIdx;
      }
#endif

      RETVALUE(ROK);
   }

   /* The memory block was allocated from the heap pool */ 
   RETVALUE(cmHeapFree (&(regCb->heapCb), ptr, size));
#else /* use pure is on */
   TRC2(cmFree);
/*cm_mem_c_001.main_27 SSI-4GMX specfic changes*/   
#ifdef SS_4GMX_LCORE
   (Void)MxHeapFree(SsiHeap, ptr);
#else
/*   (Void)free(ptr); */
#endif
/*   avail_size += size; */
#ifndef USE_PURE
   tcfree(ptr);
#else
   (Void)free(ptr);
#endif

   RETVALUE(ROK);
#endif /* USE_PURE */


} /* end of cmFreeWL */


/*
*
*       Fun:   cmCtl
*
*       Desc:  Control request function. 
*
*
*       Ret:   ROK     - successful
*              RFAILED - unsuccessful.
*
*       Notes: The current semantics of the control function is defined for two 
*              types of events: virtual address to physical address translation 
*              and memory resource check. 
*
*              The physical address translation is valid only for the memory 
*              region physically contiguous and non pagable.
*
*
*
*       File:  cm_mem_wl.c
*
*/

#ifdef ANSI
PRIVATE S16  cmCtl
(
Void    *regionCb,
Event    event, 
SMemCtl *memCtl
)
#else
PRIVATE S16  cmCtl(regionCb, event, memCtl)
Void    *regionCb;
Event    event;
SMemCtl *memCtl;
#endif
{
   CmMmRegCb *regCb;

   TRC2(cmCtl);

   regCb = (CmMmRegCb *)regionCb;

#if (ERRCLASS & ERRCLS_INT_PAR)

   /* error check on parameters */
   if ((regCb == NULLP) || (memCtl == NULLP))
   {
      RETVALUE(RFAILED);
   }

#endif

   switch (event)
   {
      case SS_MEM_V_TO_P:
      {
         Size       offset;
  
#if (ERRCLASS & ERRCLS_INT_PAR)
         if ((memCtl->u.vtop.vaddr == NULLP) || 
             (memCtl->u.vtop.paddr == NULLP))
         {
            RETVALUE(RFAILED);
         }
#endif
   
         /* Check if the virtual to physical address translation is valid */
         if (regCb->chFlag & CMM_REG_PHY_VALID) 
         {
            offset = memCtl->u.vtop.vaddr - regCb->regInfo.start;
            *(memCtl->u.vtop.paddr) = regCb->pAddr + offset;
   
            RETVALUE(ROK);
         }
         break;
      }

      case SS_MEM_CHK_RES:
      {

#if (ERRCLASS & ERRCLS_INT_PAR)
         if (!(memCtl->u.chkres.size) || 
            (memCtl->u.chkres.status == NULLP))
         {
            RETVALUE(RFAILED);
         }
#endif
#ifndef USE_PURE
         /* Check if the Bucket pool is configured */
         if (regCb->bktSize)
         {
            U16        idx;
            CmMmBkt   *bkt;
            U32        avlSize, totSize;
            /* 
             * The bucket pool is configured. The status value returned
             * does reflect on the memory availabilty in the bucket pool. 
             * The value does not consider the available memory in the
             * heap pool. 
             */
             idx = ((memCtl->u.chkres.size - 1) >> regCb->bktQnPwr);
             bkt = &(regCb->bktTbl[regCb->mapTbl[idx].bktIdx]); 
             avlSize = (bkt->numBlks - bkt->numAlloc) * bkt->size;
             avlSize += regCb->heapCb.avlSize;
             totSize = (bkt->numBlks * bkt->size) + regCb->heapSize;
             *(memCtl->u.chkres.status) = (avlSize/(totSize/10)); 
         }
         else
         {
            /* Bucket pool not configured */

            /* 
             * Find the percentage memory available in the heap pool. The value
             * does not consider the fragmentation of the heap pool.
             */
            *(memCtl->u.chkres.status) = ((regCb->heapCb.avlSize) /
                                          (regCb->heapSize/10)); 
         }

         RETVALUE(ROK);
#else /* use pure is on */
            *(memCtl->u.chkres.status) = ((avail_size) /
                                          (regCb->regInfo.size/10));
         RETVALUE(ROK);
#endif /* USE_PURE */

      }

      default:
      {
         /* No other event is supported currently */
         RETVALUE(RFAILED);
      }
   }

   /* shouldn't reach here */
   RETVALUE(RFAILED);
} /* end of cmCtl */


#if 0
/*
*
*       Fun:   cmMmBktInit
*
*       Desc:  Initialize the bucket and the map table.
*
*
*       Ret:   ROK     - successful, 
*              RFAILED - unsuccessful.
*
*       Notes: This function is called by the cmMmRegInit. 
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PRIVATE Void cmMmBktInit
(
Data      **memAddr,
CmMmRegCb  *regCb,
CmMmRegCfg *cfg,
U16         bktIdx,
U16        *lstMapIdx
)
#else
PRIVATE Void cmMmBktInit (memAddr, regCb, cfg, bktIdx, lstMapIdx)
Data      **memAddr;
CmMmRegCb  *regCb;
CmMmRegCfg *cfg;
U16         bktIdx;
U16        *lstMapIdx;
#endif
{
   U32   cnt;
   U16   idx;
   U32   numBlks;
   Size  size;
   Data **next;
   U16   blkSetRelThreshold;
   CmMmBktLstCb *bktLstCb;

   TRC2(cmMmBktInit);


   size = cfg->bktCfg[bktIdx].size; 
   numBlks = cfg->bktCfg[bktIdx].numBlks; 

   regCb->bktTbl[bktIdx].blkSetRelThreshold = cfg->bktCfg[bktIdx].blkSetRelThreshold;
   regCb->bktTbl[bktIdx].blkSetAcquireThreshold = cfg->bktCfg[bktIdx].blkSetAcquireThreshold;
   blkSetRelThreshold = cfg->bktCfg[bktIdx].blkSetRelThreshold;

   /* Initialize the bucket linked list */
   cmLListInit(&regCb->bktTbl[bktIdx].listBktSet);

   /* Reset the next pointer */
   regCb->bktTbl[bktIdx].next = NULLP; 

   /* Initialize the link list of the memory block */
   next = &(regCb->bktTbl[bktIdx].next); 
   for (cnt = 0; cnt < numBlks; cnt++)
   {
      *next     = *memAddr;
      next      = (CmMmEntry **)(*memAddr);
      *memAddr  = (*memAddr) + size;

      /* Maintain the list Cb */
      if((cnt != 0) && (!(cnt % blkSetRelThreshold)))
      {
         bktLstCb = calloc(1, sizeof(CmMmBktLstCb));
         bktLstCb->nextBktPtr = regCb->bktTbl[bktIdx].next;
         bktLstCb->numBkt = blkSetRelThreshold;
         cmLListAdd2Tail((&regCb->bktTbl[bktIdx].listBktSet), (&bktLstCb->memSetNode));
         next = &(regCb->bktTbl[bktIdx].next);
         regCb->numBkts++;
      }
   }
   *next = NULLP;

   bktLstCb = cmLListFirst((&regCb->bktTbl[bktIdx].listBktSet));
   regCb->bktTbl[bktIdx].next = bktLstCb->nextBktPtr;
   cmLListDelFrm((&regCb->bktTbl[bktIdx].listBktSet), bktLstCb);
   free(bktLstCb);

   /* Initialize the Map entry */
   idx = size / cfg->bktQnSize;

   /* 
    * Check if the size is multiple of quantum size. If not we need to initialize
    * one more map table entry.
    */ 
   if(size % cfg->bktQnSize)
   {
      idx++;
   }
   
   while ( *lstMapIdx < idx)
   {
      regCb->mapTbl[*lstMapIdx].bktIdx = bktIdx;

#if (ERRCLASS & ERRCLS_DEBUG)
      regCb->mapTbl[*lstMapIdx].numReq     = 0;
      regCb->mapTbl[*lstMapIdx].numFailure = 0;
#endif

      (*lstMapIdx)++;
   } 

   /* Initialize the bucket structure */
   regCb->bktTbl[bktIdx].size     = size; 
   regCb->bktTbl[bktIdx].numBlks  = numBlks; 
   regCb->bktTbl[bktIdx].numAlloc = 0;
   regCb->bktTbl[bktIdx].maxAlloc = 0;

   /* Update the total bucket size */
   regCb->bktSize += (size * numBlks); 

   regCb->bktTbl[bktIdx].bktFailCnt = 0;
   regCb->bktTbl[bktIdx].bktNoFitCnt = 0;

   RETVOID;
} /* end of cmMmBktInit */
#endif


/*
*
*       Fun:   cmMmHeapInit
*
*       Desc:  Initialize the heap pool. 
*
*
*       Ret:   ROK     - successful
*              RFAILED - unsuccessful.
*
*       Notes: This function is called by the cmMmRegInit. 
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PRIVATE Void  cmMmHeapInit 
(
Data        *memAddr,
CmMmHeapCb  *heapCb,
Size         size 
)
#else
PRIVATE Void  cmMmHeapInit (memAddr, heapCb, size)
Data        *memAddr;
CmMmHeapCb  *heapCb;
Size         size;
#endif
{
/* cm_mem_c_001.main_12 - addition for ssi enhancements */
#ifdef SSI_DEBUG_LEVEL1
   U16 idx;
#endif /* SSI_DEBUG_LEVEL1 */
   TRC2(cmMmHeapInit);

   /* Initialize the heap control block */
   heapCb->vStart      = memAddr;
   heapCb->vEnd        = memAddr + size;
   heapCb->avlSize    = size; 
   heapCb->minSize    = CMM_MINBUFSIZE; 

   heapCb->next       = (CmHEntry *)memAddr;
   heapCb->next->next = NULLP;
/* cm_mem_c_001.main_12 - addition for header initialization */
#ifdef SSI_DEBUG_LEVEL1
   heapCb->next->size = size - sizeof(CmHEntry);
   heapCb->next->requestedSize = 0;
   for (idx=0; idx < CMM_TRAMPLING_SIGNATURE_LEN; idx++)
   {
      heapCb->next->trSignature[idx] = 0xAB;
   }
   CMM_SET_FREE_FLAG(heapCb->next->memFlags);
   heapCb->staticHeapMemUsed = 0;
   heapCb->dynamicHeapMemUsed = 0;
   heapCb->nextOffset = sizeof(heapCb->next->trSignature) +
                        sizeof(heapCb->next->memFlags) +
                        sizeof(heapCb->next->requestedSize);
   heapCb->numAllocAttempts = 0;
   heapCb->numDeallocAttempts = 0;
   heapCb->trampleCount = 0;
#else
   heapCb->next->size = size; 
#endif /* SSI_DEBUG_LEVEL1 */

#if (ERRCLASS & ERRCLS_DEBUG)
   heapCb->numFragBlk  = 0;
   heapCb->numReq      = 0;
   heapCb->numFailure  = 0;
#endif

   heapCb->heapAllocCnt = 0;
/*  cm_mem_c_001.main_15 : Additions */
#ifdef SS_HISTOGRAM_SUPPORT 
   /* Initialise the memory histogram hash list */
   cmHstGrmHashListInit(&(heapCb->heapHstGrmHashListCp));
#endif /* SS_HISTOGRAM_SUPPORT */
   RETVOID;

} /* end of cmMmHeapInit */


/*
*
*       Fun:   cmHeapAlloc
*
*       Desc:  Allocates the memory block from the heap pool. 
*
*
*       Ret:   ROK     - successful
*              RFAILED - unsuccessful.
*
*       Notes: This function is called by the cmAlloc. cmAlloc calls this
*              function when there is no memory block available in the bucket 
*              and the  heap pool is configured.
*
*
*
*       File:  cm_mem_wl.c
*
*/
/* cm_mem_c_001.main_12 - addition for taking another parameter memType(static/dynamic) */
/*  cm_mem_c_001.main_15 : Additions */
#ifdef SS_HISTOGRAM_SUPPORT 
#ifdef SSI_DEBUG_LEVEL1
#ifdef ANSI
PRIVATE S16  cmHeapAlloc
(
CmMmHeapCb  *heapCb,
Data       **ptr,
Size        *size,
U32        memType,
U32     line,
U8     *fileName,
U8      entId,
Bool    hstReg
)
#else
PRIVATE S16  cmHeapAlloc (heapCb, ptr, size, memType, line, fileName, entId, hstReg)
CmMmHeapCb  *heapCb;
Data       **ptr;
Size        *size;
U32        memType;
U32     line;
U8     *fileName;
U8      entId;
Bool    hstReg;
#endif
#else
#ifdef ANSI
PRIVATE S16  cmHeapAlloc 
(
CmMmHeapCb  *heapCb,
Data       **ptr,
Size        *size,
U32     line,
U8     *fileName,
U8      entId,
Bool    hstReg
)
#else
PRIVATE S16  cmHeapAlloc (heapCb, ptr, size, line, fileName, entId, hstReg)
CmMmHeapCb  *heapCb;
Data       **ptr;
Size        *size;
U32     line;
U8     *fileName;
U8      entId;
Bool    hstReg;
#endif
#endif /* SSI_DEBUG_LEVEL1 */
#else
#ifdef SSI_DEBUG_LEVEL1
#ifdef ANSI
PRIVATE S16  cmHeapAlloc
(
CmMmHeapCb  *heapCb,
Data       **ptr,
Size        *size,
U32        memType
)
#else
PRIVATE S16  cmHeapAlloc (heapCb, ptr, size, memType)
CmMmHeapCb  *heapCb;
Data       **ptr;
Size        *size;
U32        memType;
#endif
#else
#ifdef ANSI
PRIVATE S16  cmHeapAlloc 
(
CmMmHeapCb  *heapCb,
Data       **ptr,
Size        *size 
)
#else
PRIVATE S16  cmHeapAlloc (heapCb, ptr, size)
CmMmHeapCb  *heapCb;
Data       **ptr;
Size        *size;
#endif
#endif /* SSI_DEBUG_LEVEL1 */
/*  cm_mem_c_001.main_15 : Additions */
#endif /* SS_HISTOGRAM_SUPPORT */ 
{
   CmHEntry  *prvHBlk;    /* Previous heap block */
   CmHEntry  *curHBlk;    /* Current heap block */ 
   Size       tmpSize;
/*  cm_mem_c_001.main_15 : Additions */
#ifdef SS_MEM_LEAK_STS 
   Size       reqSz;
#endif /* SS_MEM_LEAK_STS */
/* cm_mem_c_001.main_12 - addition for ssi enhancements */
#ifdef SSI_DEBUG_LEVEL1
   CmHEntry *alocHeapBlk;
   Size requestedSize;
   Size hdr;
   U16 idx;
#endif /* SSI_DEBUG_LEVEL1 */
/*  cm_mem_c_001.main_15 : Additions */
#ifdef SS_HISTOGRAM_SUPPORT 
	S8 hstGrmBuf[256];
#endif /* SS_HISTOGRAM_SUPPORT */

   TRC2(cmHeapAlloc);
/*  cm_mem_c_001.main_15 : Additions */
   /* Acquire the heap lock */ 
   /* cm_mem_c_001.main_13 : Replaced SLock with WTLock for NT */
#ifdef SS_WIN
   (Void) WTLock (&(heapCb->heapLock));
#else
   (Void) SLock (&(heapCb->heapLock));
#endif

#ifdef SS_MEM_LEAK_STS
   reqSz = *size;
#endif /* SS_MEM_LEAK_STS */
/* cm_mem_c_001.main_12 - addition for manipulation of statistics related data */
#ifdef SSI_DEBUG_LEVEL1
   heapCb->numAllocAttempts++;
   requestedSize = *size;
#endif /* SSI_DEBUG_LEVEL1 */

   /* Roundup the requested size */
   *size = CMM_DATALIGN(*size, (heapCb->minSize));
   
   /* Check if the available total size is adequate. */
   if ((*size) >= heapCb->avlSize)
   {
/*  cm_mem_c_001.main_15 : Additions */
#ifdef SS_WIN
                        (Void) WTUnlock (&(heapCb->heapLock));
#else
                        (Void) SUnlock (&(heapCb->heapLock));
#endif
      RETVALUE(ROUTRES);
   }


/* cm_mem_c_001.main_12 - addition for aligning the header size */
#ifdef SSI_DEBUG_LEVEL1
   hdr = PTRALIGN(sizeof(CmHEntry));
#endif /* SSI_DEBUG_LEVEL1 */

   /* 
    * Search through the heap block list in the heap pool of size 
    * greater than or equal to the requested size.
    *
    */ 
/* cm_mem_c_001.main_12 - addition for accessing the heapCb->next */
#ifdef SSI_DEBUG_LEVEL1
   prvHBlk = (CmHEntry *)((Data *)&(heapCb->next) - heapCb->nextOffset);
#else
   prvHBlk = (CmHEntry *)&(heapCb->next);
#endif /* SSI_DEBUG_LEVEL1 */
   for (curHBlk = prvHBlk->next; curHBlk; curHBlk = curHBlk->next,
                                                   prvHBlk = prvHBlk->next)
   {
      /*
       * Since the size of the block is always multiple of CMM_MINBUFSIZE 
       * and the requested size is rounded to the size multiple of
       * CMM_MINBUFSIZE, the difference between the size of the heap block
       * and the size to allocate will be either zero or multiple of
       * CMM_MINBUFSIZE. 
       */
      if ((*size) <= curHBlk->size) 
      {
/* cm_mem_c_001.main_12 - addition for block size calculation */
#ifdef SSI_DEBUG_LEVEL1
      tmpSize = curHBlk->size - (*size);
      if (tmpSize != 0)
         tmpSize = tmpSize - hdr;
      if (tmpSize)
#else
         if ((tmpSize = (curHBlk->size - (*size))))
#endif /* SSI_DEBUG_LEVEL1 */
         {
            /* Heap block of bigger size */
/* cm_mem_c_001.main_12 - addition for allocating memory */
#ifdef SSI_DEBUG_LEVEL1
            *ptr = (Data *)curHBlk + hdr + tmpSize + hdr;
            alocHeapBlk = (CmHEntry *) ((Data *)curHBlk + hdr + tmpSize);
            /*
            * No need to look for memory trampling as this is a new block altogether
            * Update the header only for this case as it is new block formed 
            */
            for (idx=0; idx < CMM_TRAMPLING_SIGNATURE_LEN; idx++)
            {
               alocHeapBlk->trSignature[idx] = 0xAB;
            }
            alocHeapBlk->size = *size;
#else
            *ptr = (Data *)curHBlk + tmpSize;             
#endif /* SSI_DEBUG_LEVEL1 */
             curHBlk->size = tmpSize;
         } 
         else
         {
            /* Heap block is same size of the requested size */
/* cm_mem_c_001.main_12 - addition for sanity check and allocation. This is a fresh block */
#ifdef SSI_DEBUG_LEVEL1
            /* look for memory trampling as this is a pure block*/
            if (curHBlk)
            {
               if (cmMmRegIsBlkSane((CmMmBlkHdr *)curHBlk) != ROK)
               {
                     /* detected a trampled memory block in this bucket */
                  #ifdef DEBUGP
                     /* display an error message here */
/*cm_mem_c_001.main_23 Fix for specifier mismatch warnings in 64BIT compilation*/          
#ifdef ALIGN_64BIT          
                     sprintf(dbgPrntBuf, "Memory Trampling in heap at: %8p, size %u bytes \n", (void *)curHBlk, requestedSize);
#else                     
                     sprintf(dbgPrntBuf, "Memory Trampling in heap at: %8p, size %lu bytes \n", (void *)curHBlk, requestedSize);
#endif                     
                     SDisplay(0, dbgPrntBuf);
                  #endif /* DEBUGP */

                     if (cmMmHeapSanityChk(heapCb) == RTRAMPLINGNOK)
                     {
                        /* Release the lock */
                        /* cm_mem_c_001.main_13: Replaced SUnlock with
                           WTUnlock for NT */
#ifdef SS_WIN
                        (Void) WTUnlock (&(heapCb->heapLock));
#else
                        (Void) SUnlock (&(heapCb->heapLock));
#endif
                        /* handle RTRAMPLINGNOK in SAlloc/SGetSBuf */
                        RETVALUE(RTRAMPLINGNOK);
                     }
                     else
                     {
                        /* Release the lock */
                        /* cm_mem_c_001.main_13: Replaced SUnlock with
                           WTUnlock for NT */
#ifdef SS_WIN
                        (Void) WTUnlock (&(heapCb->heapLock));
#else
                        (Void) SUnlock (&(heapCb->heapLock));
#endif
                        RETVALUE(RFAILED);
                     }
               }
            }

            *ptr = (Data *)curHBlk + hdr;
            alocHeapBlk =  curHBlk;
            *size = curHBlk->size;
#else
            *ptr = (Data *)curHBlk;
#endif /* SSI_DEBUG_LEVEL1 */
             prvHBlk->next = curHBlk->next;
         }

/* cm_mem_c_001.main_12 - addition for header updation */
#ifdef SSI_DEBUG_LEVEL1
         /* update the header fields */
         alocHeapBlk->requestedSize = requestedSize;
         alocHeapBlk->memFlags = 0;
         if (memType == CMM_STATIC_MEM_FLAG)
         {
            CMM_SET_STATIC_FLAG(alocHeapBlk->memFlags);
            heapCb->staticHeapMemUsed += (*size + hdr);
         }
         else
         {
            CMM_SET_DYNAMIC_FLAG(alocHeapBlk->memFlags);
            heapCb->dynamicHeapMemUsed += (*size + hdr);
         }
         heapCb->avlSize -= ((*size) + hdr);
#else
         heapCb->avlSize -= (*size); 
#endif /* SSI_DEBUG_LEVEL1 */

#ifdef MEMCAL_DEBUG
        if (tryHeap)
        {
            sprintf(prntBuf,
                 "SGetSBuf:%08lu:Size  Heap Alloc Times:%05lu  Pointer: %8p\n",
                 *size, num_times, *ptr);
            SDisplay(0, prntBuf);
            tryHeap = 0;
        }
#endif
/*  cm_mem_c_001.main_15 : Additions */
#ifdef SS_MEM_LEAK_STS 
        /* cm_mem_c_001.main_25 - Fixed compilation warnings 32/64 bit */
         cmStorAllocBlk((PTR)*ptr, (Size) reqSz, (Size) *size, MT_MAX_BKTS);
#endif /* SS_MEM_LEAK_STS */
         /* Release the lock */
/*  cm_mem_c_001.main_16 : cm_mem_c_001.main_18  Additions */
#ifdef SS_WIN
   (Void) WTUnlock (&(heapCb->heapLock));
#else
   (Void) SUnlock (&(heapCb->heapLock));
#endif

#ifdef SS_HISTOGRAM_SUPPORT
            /* If If Tapa task (entId)is registerd for histogram then insert Memrory allocated
             * information into the hash list */
            if(hstReg)
            {
               if (cmHstGrmAllocInsert(&(heapCb->heapHstGrmHashListCp), *size, size, line, fileName, entId) != ROK)
               {
                 sprintf(hstGrmBuf, "Unable to Insert into the histgram hash list\n");
					  SPrint(hstGrmBuf);
               }
            }/* End of if */

#endif /* SS_HISTOGRAM_SUPPORT */

         RETVALUE(ROK);
      }
   }

/* cm_mem_c_008.104 - Addition for memory calculator tool */
#ifdef MEMCAL_DEBUG
        tryHeap = 0;
#endif
   

   /* Release the lock */
   /* cm_mem_c_001.main_13: Replaced SUnlock with WTUnlock for NT */
#ifdef SS_WIN
   (Void) WTUnlock (&(heapCb->heapLock));
#else
   (Void) SUnlock (&(heapCb->heapLock));
#endif

   RETVALUE(ROUTRES);

} /* end of cmHeapAlloc */


/*
*
*       Fun:   cmHeapFree
*
*       Desc:  Return the memory block from the heap pool. 
*
*
*       Ret:   ROK     - successful
*              RFAILED - unsuccessful.
*
*       Notes: This function returns the memory block to the heap  pool. This 
*              function is called by cmFree. The function does not check the 
*              validity of the memory block. The caller must be sure that the 
*              block was previously allocated and belongs to the heap pool. The 
*              function maintain the sorting order of the memory block on the
*              starting address of the block. This function also do compaction 
*              if the neighbouring blocks are already in the heap. 
*
*
*
*       File:  cm_mem_wl.c
*
*/
/*  cm_mem_c_001.main_15 : Additions */
#ifdef SS_HISTOGRAM_SUPPORT  
#ifdef ANSI
PRIVATE S16  cmHeapFree 
(
CmMmHeapCb  *heapCb,
Data        *ptr,
Size         size,
U32     line,
U8     *fileName,
U8      entId,
Bool    hstReg
)
#else
PRIVATE S16  cmHeapFree (heapCb, ptr, size, line, fileName, entId, hstReg)
CmMmHeapCb  *heapCb;
Data        *ptr;
Size         size;
U32     line;
U8     *fileName;
U8      entId;
Bool    hstReg;
#endif
#else
#ifdef ANSI
PRIVATE S16  cmHeapFree 
(
CmMmHeapCb  *heapCb,
Data        *ptr,
Size         size 
)
#else
PRIVATE S16  cmHeapFree (heapCb, ptr, size)
CmMmHeapCb  *heapCb;
Data        *ptr;
Size         size;
#endif
/*  cm_mem_c_001.main_15 : Additions */
#endif /* SS_HISTOGRAM_SUPPORT */ 
{
   CmHEntry  *p;    
   CmHEntry  *curHBlk;    /* Current heap block */ 
/* cm_mem_c_001.main_12 - addition for ssi enhancements */
#ifdef SSI_DEBUG_LEVEL1
   Size  hdr;
#endif /* SSI_DEBUG_LEVEL1 */
/*  cm_mem_c_001.main_15 : Additions */
#ifdef SS_HISTOGRAM_SUPPORT 
   Size allocSize = size;
	S8 hstGrmBuf[256];
#endif /* SS_HISTOGRAM_SUPPORT */

   TRC2(cmHeapFree);

   /* Roundup the requested size */
   size = CMM_DATALIGN(size, (heapCb->minSize));
/*  cm_mem_c_001.main_15: Additions */
#ifdef SS_HISTOGRAM_SUPPORT  
   allocSize = size;
#endif /* SS_HISTOGRAM_SUPPORT */

   /* Acquire the heap lock */
   /* cm_mem_c_001.main_13 : Replaced SLock with WTLock for NT */
#ifdef SS_WIN
   (Void) WTLock (&(heapCb->heapLock));
#else
   (Void) SLock (&(heapCb->heapLock));
#endif

   /* increase the avlSize */
/* cm_mem_c_001.main_12 - addition for manipulation of statistics related data */
#ifdef SSI_DEBUG_LEVEL1
   hdr = PTRALIGN(sizeof(CmHEntry));
   heapCb->avlSize += (size + hdr);
   heapCb->numDeallocAttempts++;
#else
   heapCb->avlSize += size;
#endif /* SSI_DEBUG_LEVEL1 */
   
/* cm_mem_c_001.main_12 - addition for pointing to the block */
#ifdef SSI_DEBUG_LEVEL1
   p = (CmHEntry *)(ptr - hdr);
#else
   p = (CmHEntry *)ptr; 
/*  cm_mem_c_001.main_15 : Additions */
#ifdef SS_MEM_LEAK_STS
   /* cm_mem_c_001.main_25 - Fixed compilation warnings 32/64 bit */
   cmRlsAllocBlk((PTR)ptr);
#endif /* SS_MEM_LEAK_STS */
#endif /* SSI_DEBUG_LEVEL1 */


/* cm_mem_c_001.main_12 - addition for sanity and double-free checks */
#ifdef SSI_DEBUG_LEVEL1
   /* look for memory trampling */
   if (cmMmRegIsBlkSane((CmMmBlkHdr *)p) != ROK)
   {
      /* detected a trampled memory block in heap */
   #ifdef DEBUGP
      /* display an error message here */
/*cm_mem_c_001.main_23 Fix for specifier mismatch warnings in 64BIT compilation*/          
#ifdef ALIGN_64BIT          
      sprintf(dbgPrntBuf, "Memory Trampling in heap at: %8p, size %u bytes \n", (void *)p, size);
#else      
      sprintf(dbgPrntBuf, "Memory Trampling in heap at: %8p, size %lu bytes \n", (void *)p, size);
#endif      
      SDisplay(0, dbgPrntBuf);
   #endif /* DEBUGP */

      if (cmMmHeapSanityChk(heapCb) == RTRAMPLINGNOK)
      {
         /* Release the lock */
         /* cm_mem_c_001.main_13: Replaced SUnlock with WTUnlock for NT */
#ifdef SS_WIN
         (Void) WTUnlock (&(heapCb->heapLock));
#else
         (Void) SUnlock (&(heapCb->heapLock));
#endif
         /* handle RTRAMPLINGNOK in SAlloc/SGetSBuf */
         RETVALUE(RTRAMPLINGNOK);
      }
      else
      {
         /* do not add to the free heap */
         heapCb->avlSize -= (size + hdr);
         /* Release the heap lock */
         /* cm_mem_c_001.main_13: Replaced SUnlock with WTUnlock for NT */
#ifdef SS_WIN
         (Void) WTUnlock (&(heapCb->heapLock));
#else
         (Void) SUnlock (&(heapCb->heapLock));
#endif

         RETVALUE(ROK);
      }
   }

   /* look for any double free */
   if (CMM_IS_FREE(p->memFlags))
   {
   #ifdef DEBUGP
/*cm_mem_c_001.main_23 Fix for specifier mismatch warnings in 64BIT compilation*/          
#ifdef ALIGN_64BIT          
      sprintf(dbgPrntBuf, "DOUBLE FREE at %8p for size %u in HEAP \n", (void *)p, size);
#else
      sprintf(dbgPrntBuf, "DOUBLE FREE at %8p for size %lu in HEAP \n", (void *)p, size);
#endif      
      SDisplay(0, dbgPrntBuf);
   #endif /* DEBUGP */

      heapCb->avlSize -= (size + hdr);
/*  cm_mem_c_001.main_15 : Additions */
#ifdef SS_WIN 
         (Void) WTUnlock (&(heapCb->heapLock));
#else
         (Void) SUnlock (&(heapCb->heapLock));
#endif

      RETVALUE(RDBLFREE);
   }
#endif /* SSI_DEBUG_LEVEL1 */

   for ( curHBlk = heapCb->next; curHBlk; curHBlk = curHBlk->next)
   {
      /* 
       * The block will be inserted to maintain the sorted order on the
       * starting address of the block.
       */
      if (p > curHBlk)
      {
         if (!(curHBlk->next) || 
             (p < (curHBlk->next)))
         {
            /* Heap block should be inserted here */

            /* 
             * Check if the block to be returned can be merged with the
             * current block.
             */
/* cm_mem_c_001.main_12 - addition for header consideration */
#ifdef SSI_DEBUG_LEVEL1
             if (((Data *)curHBlk + hdr + curHBlk->size) == (Data *)p)
#else
             if (((Data *)curHBlk + curHBlk->size) == (Data *)p)
#endif /* SSI_DEBUG_LEVEL1 */
             {
                 /* Merge the block */
/* cm_mem_c_001.main_12 - addition for updating statistics related data */
#ifdef SSI_DEBUG_LEVEL1
                  /* update the flags */
                  if (CMM_IS_STATIC(p->memFlags))
                     heapCb->staticHeapMemUsed -= (size + hdr);
                  else if (CMM_IS_DYNAMIC(p->memFlags))
                     heapCb->dynamicHeapMemUsed -= (size + hdr);
                  size = (curHBlk->size += (size + hdr));
#else
                  size = (curHBlk->size += size);
#endif /*SSI_DEBUG_LEVEL1*/
                  p = curHBlk;
             }
             else
             {
/* cm_mem_c_001.main_12 - addition for double-free check */
#ifdef SSI_DEBUG_LEVEL1
                /* Check for double deallocation in heap */
                if ((Data *)p < ((Data *)curHBlk + curHBlk->size))
                {
                   /* Release the lock */
                   /* cm_mem_c_001.main_13: Replaced SUnlock with WTUnlock for NT */
#ifdef SS_WIN
                   (Void) WTUnlock (&(heapCb->heapLock));
#else
                   (Void) SUnlock (&(heapCb->heapLock));
#endif

                   /* This block is already freed in the heap */
                   RETVALUE(RDBLFREE);
                }
                /* update the flags as it is a new node */
                if (CMM_IS_STATIC(p->memFlags))
                {
                   heapCb->staticHeapMemUsed -= (size + hdr);
                   CMM_RESET_STATIC_FLAG(p->memFlags);
                }
                else if (CMM_IS_DYNAMIC(p->memFlags))
                {
                   heapCb->dynamicHeapMemUsed -= (size + hdr);
                   CMM_RESET_DYNAMIC_FLAG(p->memFlags);
                }
                CMM_SET_FREE_FLAG(p->memFlags);
                p->requestedSize = 0;
#endif /*SSI_DEBUG_LEVEL1*/
                /* insert the block */
                p->next = curHBlk->next;
                p->size = size; 
                curHBlk->next = p;
             }

            /* Try to merge with the next block in the chain */
/* cm_mem_c_001.main_12 - addition for ssi enhancements */
#ifdef SSI_DEBUG_LEVEL1
            if (((Data *)p + hdr + size) == (Data *)(p->next))
#else
            if (((Data *)p + size) == (Data *)(p->next))
#endif /*SSI_DEBUG_LEVEL1*/
            {
               /* p->next can not be NULL */
/* cm_mem_c_001.main_12 - addition for header consideration */
#ifdef SSI_DEBUG_LEVEL1
               p->size += (p->next->size + hdr);
#else
               p->size += p->next->size; 
#endif /*SSI_DEBUG_LEVEL1*/
               p->next  = p->next->next;
            }

            /* Release the lock */
            /* cm_mem_c_001.main_13: Replaced SUnlock with WTUnlock for NT */
#ifdef SS_WIN
            (Void) WTUnlock (&(heapCb->heapLock));
#else
            (Void) SUnlock (&(heapCb->heapLock));
#endif
/*  cm_mem_c_001.main_15 : Additions */             
#ifdef SS_HISTOGRAM_SUPPORT 
        /* If If Tapa task (entId)is registerd for histogram then insert 
		   Memrory Freed information into the hash list */
        if(hstReg)
        {
            if (cmHstGrmFreeInsert(&heapCb->heapHstGrmHashListCp, allocSize, line, 
				           fileName, entId) != ROK)
            {
               sprintf(hstGrmBuf, "Unable to Insert into the histgram hash list\n");
					SPrint(hstGrmBuf);
            }
         }/* End of if */
#endif /* SS_HISTOGRAM_SUPPORT */
            RETVALUE(ROK);
         }
      }
      else if (p < curHBlk)
      {
         /*
         * Check if the block to be returned can be merged with the
         * current block.
         */
/* cm_mem_c_001.main_12 - addition for header consideration */
#ifdef SSI_DEBUG_LEVEL1
         if (((Data *)p + hdr + size) == (Data *)curHBlk)
#else
         if (((Data *)p + size) == (Data *)curHBlk)
#endif /* SSI_DEBUG_LEVEL1 */
         {
            /* Merge the block */
/* cm_mem_c_001.main_12 - addition for header consideration */
#ifdef SSI_DEBUG_LEVEL1
            p->size = size + (curHBlk->size + hdr);
#else
            p->size = size + curHBlk->size;
#endif /* SSI_DEBUG_LEVEL1 */
            p->next = curHBlk->next;
         }
         else
         {
            /* insert the block */
            p->next = curHBlk;
            p->size = size;
         }
/* cm_mem_c_001.main_12 - addition for header updation */
#ifdef SSI_DEBUG_LEVEL1
         /* update the flags in both cases as they are new start nodes*/
         if (CMM_IS_STATIC(p->memFlags))
         {
            heapCb->staticHeapMemUsed -= (size + hdr);
            CMM_RESET_STATIC_FLAG(p->memFlags);
         }
         else if (CMM_IS_DYNAMIC(p->memFlags))
         {
            heapCb->dynamicHeapMemUsed -= (size + hdr);
            CMM_RESET_DYNAMIC_FLAG(p->memFlags);
         }
         CMM_SET_FREE_FLAG(p->memFlags);
         p->requestedSize = 0;
#endif /* SSI_DEBUG_LEVEL1 */

         heapCb->next = p;

         /* Release the lock */
         /* cm_mem_c_001.main_13: Replaced SUnlock with WTUnlock for NT */
#ifdef SS_WIN
         (Void) WTUnlock (&(heapCb->heapLock));
#else
         (Void) SUnlock (&(heapCb->heapLock));
#endif
/*  cm_mem_c_001.main_15 : Additions */
#ifdef SS_HISTOGRAM_SUPPORT  
        /* If If Tapa task (entId)is registerd for histogram then insert 
		   Memrory Freed information into the hash list */
        if(hstReg)
        {
            if (cmHstGrmFreeInsert(&heapCb->heapHstGrmHashListCp, allocSize, line, 
				           fileName, entId) != ROK)
            {
               sprintf(hstGrmBuf, "Unable to Insert into the histgram hash list\n");
					SPrint(hstGrmBuf);
            }
         }/* End of if */
#endif /* SS_HISTOGRAM_SUPPORT */
         RETVALUE(ROK);
      }

   }

   if (heapCb->next == NULLP)
   {
      /* Heap block is empty. Insert the block in the head. */
      heapCb->next = p;
      p->next = NULLP;
      p->size = size;

/* cm_mem_c_001.main_12 - addition for header updation */
#ifdef SSI_DEBUG_LEVEL1
      if (CMM_IS_STATIC(p->memFlags))
      {
         heapCb->staticHeapMemUsed -= (size + hdr);
         CMM_RESET_STATIC_FLAG(p->memFlags);
      }
      else if (CMM_IS_DYNAMIC(p->memFlags))
      {
         heapCb->dynamicHeapMemUsed -= (size + hdr);
         CMM_RESET_DYNAMIC_FLAG(p->memFlags);
      }
      CMM_SET_FREE_FLAG(p->memFlags);
      p->requestedSize = 0;
#endif /* SSI_DEBUG_LEVEL1 */

      /* Release the heap lock */
      /* cm_mem_c_001.main_13: Replaced SUnlock with WTUnlock for NT */
#ifdef SS_WIN
      (Void) WTUnlock (&(heapCb->heapLock));
#else
      (Void) SUnlock (&(heapCb->heapLock));
#endif
/*  cm_mem_c_001.main_15 : Additions */
#ifdef SS_HISTOGRAM_SUPPORT 
        /* If If Tapa task (entId)is registerd for histogram then insert 
		   Memrory Freed information into the hash list */
        if(hstReg)
        {
            if (cmHstGrmFreeInsert(&heapCb->heapHstGrmHashListCp, allocSize, line, 
				           fileName, entId) != ROK)
            {
               sprintf(hstGrmBuf, "Unable to Insert into the histgram hash list\n");
					SPrint(hstGrmBuf);
            }
         }/* End of if */
#endif /* SS_HISTOGRAM_SUPPORT */
      RETVALUE(ROK);
   }

   /* Release the lock */
   /* cm_mem_c_001.main_13: Replaced SUnlock with WTUnlock for NT */
#ifdef SS_WIN
   (Void) WTUnlock (&(heapCb->heapLock));
#else
   (Void) SUnlock (&(heapCb->heapLock));
#endif

   RETVALUE(RFAILED);
} /* end of cmHeapFree */
/*  cm_mem_c_001.main_15 : Additions */
#ifdef SS_MEM_LEAK_STS 
/*
*
*       Fun:   cmInitMemLeakMdl
*
*       Desc:  Initializes the memory leak detection module
*
*
*       Ret:   RETVOID
*
*       Notes: This function initializes the memory leak detection module.
*
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PUBLIC Void cmInitMemLeakMdl
(
Void
)
#else
PUBLIC Void cmInitMemLeakMdl (Void)
#endif
{
   U8   memMdl;
	U8   hashIdx;

   TRC3(cmInitMemLeakMdl);

   memLkCb.memLkMdlInit = FALSE;
   for(memMdl = 0; memMdl < CM_MEM_USR_MDL; memMdl++)
   {
	   for (hashIdx = 0; hashIdx < CM_MAX_HASH_PER_TSK; hashIdx++)
		{
       SInitLock(&memLkCb.memUsrMdl[memMdl][hashIdx].memLck, 1);
       cmHashListInit(&memLkCb.memUsrMdl[memMdl][hashIdx].memHashCp,
                      500, 0, FALSE, CM_HASH_KEYTYPE_U32MOD, 0, 0);
       memLkCb.memUsrMdl[memMdl][hashIdx].used = FALSE;
		}
   }
   if(memLkCb.fileLkLog == NULLP)
   {
      memLkCb.fileLkLog = (FILE *) stdout;
   }
   memLkCb.memLkMdlInit = TRUE;

   RETVOID;
} /* cmInitMemLeakMdl */
/* cm_mem_c_002.main_21 Added for shutdown procedure */
/*
 *
 * Fun:   cmDeinitMemLeakMdl
 * 
 * Desc:  De-initializes the memory leak detection module
 * 
 * 
 * Ret:   RETVOID
 * 
 * Notes: This function de-initializes the memory leak detection module.
 * 
 * 
 * File:  cm_mem_wl.c
 * 
 **/
#ifdef ANSI
PUBLIC Void cmDeinitMemLeakMdl
(
Void
)
#else
PUBLIC Void cmDeinitMemLeakMdl (Void)
#endif
{
  U8   memMdl;
  U8   hashIdx;

  TRC3(cmDeinitMemLeakMdl);

  memLkCb.memLkMdlInit = FALSE;
  for(memMdl = 0; memMdl < CM_MEM_USR_MDL; memMdl++)
  {
	 for (hashIdx = 0; hashIdx < CM_MAX_HASH_PER_TSK; hashIdx++)
	 {
		SDestroyLock(&memLkCb.memUsrMdl[memMdl][hashIdx].memLck);
		cmHashListDeinit(&memLkCb.memUsrMdl[memMdl][hashIdx].memHashCp);
		memLkCb.memUsrMdl[memMdl][hashIdx].used = FALSE;
	 }
  }
  RETVOID;
}
/*
*
*       Fun:   cmMemOpenMemLkFile
*
*       Desc:  Initializes the memory leak detection module
*
*
*       Ret:   RETVOID
*
*       Notes: This function initializes the memory leak detection module.
*
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PUBLIC Void cmMemOpenMemLkFile
(
S8 *arg
)
#else
PUBLIC Void cmMemOpenMemLkFile (arg)
S8 *msOptArg;
#endif
{
   TRC3(cmMemOpenMemLkFile);
   memLkCb.fileLkLog = NULLP;
   memLkCb.fileLkLog = fopen(arg, "w");
   RETVOID;
}

/*
*
*       Fun:   SLogLkInfo
*
*       Desc:  Initializes the memory leak detection module
*
*
*       Ret:   RETVOID
*
*       Notes: This function initializes the memory leak detection module.
*
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PUBLIC Void SLogLkInfo
(
Void
)
#else
PUBLIC Void SLogLkInfo (Void)
#endif
{

   MemAllocInfo      *oldMemInfo;
   MemAllocInfo      *newMemInfo;
   U8                 memMdl;  
   U8                 hashIdx;  
   U8                 idx;
   Txt                prntBuf[255];
   S8                 **funcNm;
   TRC3(SLogLkInfo);
   if( memLkCb.memLkMdlInit == FALSE)
   {
     RETVOID;
   }
   sprintf(prntBuf, "\n------- START OF LEAK LOG -------\n");
   fwrite(prntBuf, strlen(prntBuf), 1, memLkCb.fileLkLog);

   for(memMdl = 0; memMdl < CM_MEM_USR_MDL; memMdl++)
   {
	   for (hashIdx = 0; hashIdx < CM_MAX_HASH_PER_TSK; hashIdx++)
		{
         if(memLkCb.memUsrMdl[memMdl][hashIdx].used == FALSE)
         {
            continue;
         }
         oldMemInfo = NULLP;
         newMemInfo = NULLP;
         SLock(&memLkCb.memUsrMdl[memMdl][hashIdx].memLck);
         while(cmHashListGetNext(&memLkCb.memUsrMdl[memMdl][hashIdx].memHashCp,
                                 (PTR)oldMemInfo, (PTR *)&newMemInfo) == ROK)
         {
             sprintf(prntBuf, "[LBIS]\n");
             fwrite(prntBuf, strlen(prntBuf), 1, memLkCb.fileLkLog);
             /* cm_mem_c_001.main_25 - Fixed compilation warnings 32/64 bit */
#ifdef ALIGN_64BIT
             sprintf(prntBuf, "Address: 0x%u\n", newMemInfo->memAddr);
#else
             sprintf(prntBuf, "Address: 0x%lu\n", newMemInfo->memAddr);
#endif
             fwrite(prntBuf, strlen(prntBuf), 1, memLkCb.fileLkLog);
             sprintf(prntBuf, "Module Name: %s\n", 
                     memUsrMdlStr[newMemInfo->moduleId].mdlStr);
             fwrite(prntBuf, strlen(prntBuf), 1, memLkCb.fileLkLog);
             sprintf(prntBuf, "Requested Size: %d\n", (S16)newMemInfo->reqSz);
             fwrite(prntBuf, strlen(prntBuf), 1, memLkCb.fileLkLog);
             sprintf(prntBuf, "Allocated Size: %d\n", (S16)newMemInfo->allocSz);
             fwrite(prntBuf, strlen(prntBuf), 1, memLkCb.fileLkLog);
             sprintf(prntBuf, "Bucket Idx: %d\n", newMemInfo->bktIdx);
             fwrite(prntBuf, strlen(prntBuf), 1, memLkCb.fileLkLog);
             sprintf(prntBuf,"Memory Allocation Path:\n");
             fwrite(prntBuf, strlen(prntBuf), 1, memLkCb.fileLkLog);
             funcNm = (S8 **)newMemInfo->backTrace;
             for(idx = 0; idx < newMemInfo->bTrcSz; idx ++)
             {
                sprintf(prntBuf,"==> %s\n", funcNm[idx]);
                fwrite(prntBuf, strlen(prntBuf), 1, memLkCb.fileLkLog);
             }
             sprintf(prntBuf, "[LBIE]\n\n");
             fwrite(prntBuf, strlen(prntBuf), 1, memLkCb.fileLkLog);
             fflush(memLkCb.fileLkLog);
             oldMemInfo = newMemInfo;
             newMemInfo = NULLP;
         } 
         SUnlock(&memLkCb.memUsrMdl[memMdl][hashIdx].memLck);
		}
   }
   sprintf(prntBuf, "\n------- END OF LEAK LOG -------\n");
   fwrite(prntBuf, strlen(prntBuf), 1, memLkCb.fileLkLog);
   RETVOID;
}

/*
*
*       Fun:   SFlushLkInfo
*
*       Desc:  Initializes the memory leak detection module
*
*
*       Ret:   RETVOID
*
*       Notes: This function initializes the memory leak detection module.
*
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PUBLIC Void SFlushLkInfo
(
Void
)
#else
PUBLIC Void SFlushLkInfo (Void)
#endif
{
   MemAllocInfo      *newMemInfo;
   U8                 memMdl;
   U8                 hashIdx;
   S8                 **funcNm;
#ifdef SS_MEM_LEAK_SOL
   U8                 i;
#endif /* SS_MEM_LEAK_SOL */

   TRC3(SFlushLkInfo);
   if( memLkCb.memLkMdlInit == FALSE)
   {
     RETVOID;
   }

   for(memMdl = 0; memMdl < CM_MEM_USR_MDL; memMdl++)
   {
	   for(hashIdx = 0; hashIdx < CM_MAX_HASH_PER_TSK; hashIdx++)
		{
         if(memLkCb.memUsrMdl[memMdl][hashIdx].used == FALSE)
         {
            continue;
         }
         newMemInfo = NULLP;
         SLock(&memLkCb.memUsrMdl[memMdl][hashIdx].memLck);
         while(cmHashListGetNext(&memLkCb.memUsrMdl[memMdl][hashIdx].memHashCp,
                                 (PTR)NULLP, (PTR *)&newMemInfo) == ROK)
         {
             funcNm = (S8 **)newMemInfo->backTrace;
#ifdef SS_MEM_LEAK_SOL
             for(i = 0; i < newMemInfo->bTrcSz; i++)
             {
/*cm_mem_c_001.main_27 SSI-4GMX specfic changes*/   
#ifdef SS_4GMX_LCORE
                MxHeapFree(SsiHeap, funcNm[i]); 
#else
                free(funcNm[i]); 
#endif
				    /* SPutSBuf(DFLT_REGION, DFLT_POOL, funcNm[i], sizeof(U32) * CM_MAX_STACK_TRACE); */
             }
#endif /* SS_MEM_LEAK_SOl */
/*cm_mem_c_001.main_27 SSI-4GMX specfic changes*/   
#ifdef SS_4GMX_LCORE
             MxHeapFree(SsiHeap, funcNm);
             MxHeapFree(SsiHeap, newMemInfo);
#else
             free(funcNm);
             free(newMemInfo);
#endif
         }
         SUnlock(&memLkCb.memUsrMdl[memMdl][hashIdx].memLck);
		}
    }
    RETVOID;
}

/*
*
*       Fun:   cmStorAllocBlk
*
*       Desc:  Initializes the memory leak detection module
*
*
*       Ret:   RETVOID
*
*       Notes: This function initializes the memory leak detection module.
*
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PUBLIC Void cmStorAllocBlk
(
U32    addr,
Size   reqSz,
Size   allocSz,
U16    bktIdx
)
#else
PUBLIC Void cmStorAllocBlk (addr, reqSz, allocSz, bktIdx)
U32    addr;
Size   reqSz;
Size   allocSz;
U16    bktIdx;
#endif /* ANSI */
{
#ifndef SS_MEM_LEAK_SOL
   Ptr           trace[CM_MAX_STACK_TRACE];
#endif  /* SS_MEM_LEAK_SOL */
   S8            **funcNm;
   S32           traceSize;
   MemAllocInfo  *allocInfo;
   U8            moduleId;

   TRC3(cmStorAllocBlk); 
   if( memLkCb.memLkMdlInit == FALSE)
   {
     RETVOID;
   }

#ifdef SS_MEM_LEAK_SOL
   /* I need to do this for solaris, because it does not implement 
    * backtrace. Here backtrace is my function. See below for the 
    * implementation. */
/*cm_mem_c_001.main_27 SSI-4GMX specfic changes*/   
#ifdef SS_4GMX_LCORE
   funcNm = (S8 **)MxHeapAlloc(SsiHeap, (sizeof(U32) * CM_MAX_STACK_TRACE));
   cmMemset((U8*)funcNm, 0, (sizeof(U32) * CM_MAX_STACK_TRACE));
#else
   funcNm = (S8 **)calloc(1, (sizeof(U32) * CM_MAX_STACK_TRACE));
#endif
	/* SGetSBuf(DFLT_REGION, DFLT_POOL, &funcNm, sizeof(U32) * CM_MAX_STACK_TRACE); */
   traceSize = backtrace((Void **)funcNm, CM_MAX_STACK_TRACE);
#else /* SS_MEM_LEAK_SOL */
   traceSize = backtrace(trace, CM_MAX_STACK_TRACE);
   funcNm = backtrace_symbols(trace, traceSize); 
#endif /* SS_MEM_LEAK_SOL */
   
   moduleId = cmMemGetModuleId(funcNm, traceSize);

   (Void)SLock(&(memLkCb.memUsrMdl[moduleId][addr & 0x3].memLck));
/*cm_mem_c_001.main_27 SSI-4GMX specfic changes*/   
#ifdef SS_4GMX_LCORE
   allocInfo = (MemAllocInfo *)MxHeapAlloc(SsiHeap, sizeof(MemAllocInfo)); 
   cmMemset((U8*)allocInfo, 0, sizeof(MemAllocInfo));
#else
   allocInfo = (MemAllocInfo *)calloc(1, sizeof(MemAllocInfo)); 
#endif
	/* SGetSBuf(DFLT_REGION, DFLT_POOL, &allocInfo,  sizeof(MemAllocInfo)); */
   allocInfo->memAddr    = addr;
   allocInfo->reqSz      = reqSz;
   allocInfo->allocSz    = allocSz;
   allocInfo->bktIdx     = bktIdx;
   allocInfo->backTrace  = (PTR) funcNm;
   allocInfo->moduleId   = moduleId;
   allocInfo->bTrcSz     = traceSize;

   cmHashListInsert(&memLkCb.memUsrMdl[moduleId][addr & 0x3].memHashCp, 
                    (PTR)allocInfo, (U8 *)&(allocInfo->memAddr),
                    sizeof(allocInfo->memAddr));
   memLkCb.memUsrMdl[moduleId][addr & 0x3].used = TRUE;

   (Void) SUnlock(&(memLkCb.memUsrMdl[moduleId][addr & 0x3].memLck));
   RETVOID;
} /* cmStorAllocBlk */

/*
*
*       Fun:   cmMemGetModuleId
*
*       Desc:  Initializes the memory leak detection module
*
*
*       Ret:   RETVOID
*
*       Notes: This function initializes the memory leak detection module.
*
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PUBLIC U8 cmMemGetModuleId
(
S8     **funNm,
S32    traceSize
)
#else
PUBLIC U8 cmMemGetModuleId (funNm, traceSize)
S8     **funNm;
S32    traceSize;
#endif /* ANSI */
{
   U8    idx;
   U8    memStrIdx;
   U32   len;
   S32   retVal;
   S16   memReqIdx;
   S16   mdlFunStrIdx;

   Txt   *memFn[]={"SGetMsg", "SGetSBuf", "SGetDBuf", NULLP};
                 
   /*cm_mem_c_001.main_25 : Fix for TRACE5 feature crash due to missing TRC MACRO*/
   TRC3(cmMemGetModuleId)
   for(idx = 0; idx < traceSize; idx++)
   {
      memReqIdx = -1;
      memStrIdx = 0;
      while((memReqIdx < 0) && (memFn[memStrIdx] != NULLP))
      {
         memReqIdx = cmMemGetStrMtchIdx(0, traceSize, memFn[memStrIdx], 
                                        funNm);
         memStrIdx++;
      }
      mdlFunStrIdx = 0;
      while(memUsrMdlStr[mdlFunStrIdx].fPStr != NULLP)
      {
         len = strlen((const S8 *)memUsrMdlStr[mdlFunStrIdx].fPStr);
         memReqIdx = cmMemGetStrMtchIdx((memReqIdx + 1), traceSize, 
                                        memUsrMdlStr[mdlFunStrIdx].fPStr,
                                        funNm);
         if(memReqIdx >= 0)
         {
            RETVALUE(mdlFunStrIdx);
         }
         mdlFunStrIdx++;
      }
      mdlFunStrIdx = 0;
      while(memUsrMdlStr[mdlFunStrIdx].fPStr != NULLP)
      {
          retVal = strcmp((const S8 *)"DEFAULT", 
                               (const S8 *)memUsrMdlStr[mdlFunStrIdx].fPStr);
         if(retVal == NULLD)
         {
            RETVALUE(mdlFunStrIdx);
         } 
         mdlFunStrIdx++;
      }
   }

   RETVALUE(0);
} /* cmMemGetModuleId */

/*
*
*       Fun:   cmMemGetStrMtchIdx
*
*       Desc:  Initializes the memory leak detection module
*
*
*       Ret:   RETVOID
*
*       Notes: This function initializes the memory leak detection module.
*
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PUBLIC S16 cmMemGetStrMtchIdx  
(
U8 strtIdx, 
U8 endIdx,
S8 *str, 
S8 **strLst
)
#else
PUBLIC S16 cmMemGetStrMtchIdx(strtIdx, endIdx, str, strLst)
U8 strtIdx;
U8 endIdx;
S8 *str;
S8 **strLst;
#endif
{

   S8   cmpStr[255];
   U32  len;
   Bool found;
   U32  tempLen;
   U8   idx;
   S32  retVal;
   TRC3(cmMemGetStrMtchIdx);

   len = strlen((const S8 *)str);
   cmpStr[0] = '(';
   strncpy((S8 *)&cmpStr[1], (const S8 *)str, len);
   cmpStr[len + 1] = '\0';
   len++;
   found = FALSE;
   for(;strtIdx < endIdx && !found; strtIdx++)
   {
       idx = 0;
       tempLen = strlen((const S8 *)strLst[strtIdx]);
       if(tempLen < len)
         continue;

       while(*(strLst[strtIdx] + idx + len) != '\0')
       {
         retVal = strncmp((const S8 *)cmpStr, 
                         ((const S8 *)strLst[strtIdx] + idx), len);
         if(0 == retVal)
         {
           found = TRUE;
           break;
         }
         idx++;
       }
   }

   if(!found)
   {
     RETVALUE(-1); 
   }
   RETVALUE(strtIdx);

}  /* cmMemGetStrMtchIdx */

/*
*
*       Fun:   cmRlsAllocBlk
*
*       Desc:  Initializes the memory leak detection module
*
*
*       Ret:   RETVOID
*
*       Notes: This function initializes the memory leak detection module.
*
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PUBLIC Void cmRlsAllocBlk
(
U32    addr
)
#else
PUBLIC Void cmRlsAllocBlk(addr)
U32    addr;
#endif
{
    Ptr           trace[CM_MAX_STACK_TRACE];
    S8            **funcNm;
    U8            idx;
    U8            i;
    S16           retVal;
    S32           traceSize;
    MemAllocInfo  *memAllocInfo;

    TRC3(cmRlsAllocBlk);
    if( memLkCb.memLkMdlInit == FALSE)
    {
      RETVOID;
    }


    for(idx = 0; idx < CM_MEM_USR_MDL; idx++)
    {
       SLock(&memLkCb.memUsrMdl[idx][addr & 0x3].memLck);
       retVal = cmHashListFind(&memLkCb.memUsrMdl[idx][addr & 0x3].memHashCp,
                               (U8 *)&addr, sizeof(U32), 0,
                               (PTR *)&memAllocInfo);                              
       if(retVal == ROK)
       {
         cmHashListDelete(&memLkCb.memUsrMdl[idx][addr & 0x3].memHashCp,
                          (PTR)memAllocInfo);
         SUnlock(&memLkCb.memUsrMdl[idx][addr & 0x3].memLck);
         funcNm = (S8 **) memAllocInfo->backTrace;
#ifdef SS_MEM_LEAK_SOL
         for(i = 0; i < memAllocInfo->bTrcSz; i++)
         {
/*cm_mem_c_001.main_27 SSI-4GMX specfic changes*/   
#ifdef SS_4GMX_LCORE
            MxHeapFree(SsiHeap, funcNm[i]);
#else
            free(funcNm[i]);
#endif
         }
#endif /* SS_MEM_LEAK_SOL */
#ifdef SS_MEM_LEAK_FREE_TRACE
         {

            Txt   prntBuf[255];
            sprintf( prntBuf, "\n==============================\n");
            SPrint(prntBuf);
            /* cm_mem_c_001.main_25 - Fixed compilation warnings 32/64 bit */
#ifdef ALIGN_64BIT
            sprintf( prntBuf, "Address: [%x]\n", addr);
#else
            sprintf( prntBuf, "Address: [%lx]\n", addr);
#endif
            SPrint(prntBuf);
            traceSize = backtrace(trace, CM_MAX_STACK_TRACE);
            funcNm    = backtrace_symbols(trace, traceSize);
            sprintf( prntBuf, "[bt] Execution path:\n");
            SPrint(prntBuf);
            for (i=0; i < traceSize; ++i)
            {
              sprintf( prntBuf, "[bt] %s\n", funcNm[i]);
              SPrint(prntBuf);
            }
            sprintf( prntBuf, "\n==============================\n");
            SPrint(prntBuf);
         }
#endif   /* SS_MEM_LEAK_FREE_TRACE */
/*cm_mem_c_001.main_27 SSI-4GMX specfic changes*/   
#ifdef SS_4GMX_LCORE
         MxHeapFree(SsiHeap, funcNm);
         MxHeapFree(SsiHeap, memAllocInfo);
#else
         free(funcNm);
         free(memAllocInfo);
#endif
         break;
       }
       SUnlock(&memLkCb.memUsrMdl[idx][addr & 0x3].memLck);
    }

#ifndef SS_MEM_LEAK_SOL
     if(idx == CM_MEM_USR_MDL)
     {
       Txt   prntBuf[255];
       sprintf( prntBuf,"\nPossible Double-Deallocation.\n");
       SPrint(prntBuf);
/*cm_mem_c_001.main_23 Fix for specifier mismatch warnings in 64BIT compilation*/          
#ifdef ALIGN_64BIT          
       sprintf( prntBuf, "Address: [%u]\n", addr);
#else       
       sprintf( prntBuf, "Address: [%lu]\n", addr);
#endif       
       SPrint(prntBuf);
       traceSize = backtrace(trace, CM_MAX_STACK_TRACE);
       funcNm    = backtrace_symbols(trace, traceSize);
       sprintf( prntBuf,"[bt] Execution path:\n");
       SPrint(prntBuf);
       for (i=0; i < traceSize; ++i)
       {
             sprintf( prntBuf,"[bt] %s\n", funcNm[i]);
             SPrint(prntBuf);
       }
       printf("\n==============================\n");
/*cm_mem_c_001.main_27 SSI-4GMX specfic changes*/   
#ifdef SS_4GMX_LCORE
       MxHeapFree(SsiHeap, funcNm);
#else
       free(funcNm);
#endif
     }
#endif /* SS_MEM_LEAK_SOL */

   /*cm_mem_c_001.main_25 : */
   RETVOID;
} /* cmRlsAllocBlk */


#ifdef SS_MEM_LEAK_SOL
/*
*
*       Fun:   cmAddrToSymStr
*
*       Desc:  Initializes the memory leak detection module
*
*
*       Ret:   RETVOID
*
*       Notes: This function initializes the memory leak detection module.
*
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PUBLIC S32 cmAddrToSymStr
(
Void   *pc, 
S8     *buffer, 
S32    size
)
#else
PUBLIC S32 cmAddrToSymStr(pc, buffer, size)
Void   *pc;
S8     *buffer;
S32    size;
#endif
{

   Dl_info info;
   Sym *sym;

   TRC3(cmAddrToSymStr);

   if (dladdr1(pc, &info, (Void **)&sym, RTLD_DL_SYMENT) == 0)
   {
       RETVALUE(snprintf(buffer, size, "[0x%p]", pc));
   }

   if ((info.dli_fname != NULLP && info.dli_sname != NULLP) &&
       ((uintptr_t)pc - (uintptr_t)info.dli_saddr < sym->st_size))
   {
      RETVALUE(snprintf(buffer, size, "%s(%s+0x%x) [0x%p]",
                       info.dli_fname,
                       info.dli_sname,
                       (unsigned long)pc - (unsigned long)info.dli_saddr, pc));
   }
   else
   {
      RETVALUE(snprintf(buffer, size, "%s(0x%p [0x%p]",
                      info.dli_fname,
                      (unsigned long)pc - (unsigned long)info.dli_fbase, pc));
   }

} /* cmAddrToSymStr */

/*
*
*       Fun:   cmLeakCallBack
*
*       Desc:  Initializes the memory leak detection module
*
*
*       Ret:   RETVOID
*
*       Notes: This function initializes the memory leak detection module.
*
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PUBLIC S32 cmLeakCallBack
(
uintptr_t pc,
S32       sigNo, 
Void      *arg
)
#else
PUBLIC S32 cmLeakCallBack(pc, sigNo, arg)
uintptr_t pc;
S32       sigNo;
Void      *arg;
#endif
{
    S8   *buffer;
    TRC3(cmLeakCallBack);

    Backtrace_t *bt = (Backtrace_t *)arg;
    if (bt->bt_actcount >= bt->bt_maxcount)
         RETVALUE(-1);
/*cm_mem_c_001.main_27 SSI-4GMX specfic changes*/   
#ifdef SS_4GMX_LCORE
    buffer = (S8 *)MxHeapAlloc(SsiHeap, 510); 
    cmMemset((U8*)buffer, 0, 510);
#else
    buffer = (S8 *)calloc(1, 510); 
#endif
	 /* SGetSBuf(DFLT_REGION, DFLT_POOL, &buffer, 510); */
    (void) cmAddrToSymStr((void *)pc, buffer, 505);
    bt->bt_buffer[bt->bt_actcount++] = (S8 *)buffer;

    RETVALUE(0);
} /* cmLeakCallBack */

/*
*
*       Fun:   backtrace
*
*       Desc:  Initializes the memory leak detection module
*
*
*       Ret:   RETVOID
*
*       Notes: This function initializes the memory leak detection module.
*
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PUBLIC S32 backtrace
(
Void      **buffer,
S32       count
)
#else
PUBLIC S32 backtrace(buffer, count)
Void      **buffer;
S32       count;
#endif
{
    TRC3(backtrace);

    Backtrace_t  bt;
    ucontext_t   u;

    bt.bt_buffer = buffer;
    bt.bt_maxcount = count;
    bt.bt_actcount = 0;

    if (getcontext(&u) < 0)
       RETVALUE(0);
    (Void) walkcontext(&u, cmLeakCallBack, &bt);
    RETVALUE(bt.bt_actcount);

} /* backtrace */

#endif /* SS_MEM_LEAK_SOL */

#endif /* SS_MEM_LEAK_STS */
/* cm_mem_c_001.main_12 - addition related to SSI enhancemens
* These include sanity check functions for bucket and heap,
* for printing several memory related statistics 
*/
#ifdef SSI_DEBUG_LEVEL1
/*
*
*       Fun:   cmMmBktSanityChk
*
*       Desc:  Performs the sanity check for the memory blocks in a memory bucket.
*              This API gets called when trampling is detected in a memory block.
*
*       Ret:   RTRAMPLINGNOK - Trampling, serious error
*              RTRAMPLINGOK  - Trampling, but OK to proceed
*
*       Notes: This function performs the memory block sanity in a bucket. This
*              function is called by cmAlloc and cmFree as part of error handling mechanism.
*              Performs sanity check for the whole bucket by traversing each
*              of the memory blocks using the pointer bktStartPtr.
*              Keeps track of number of tramplings happened. If the count
*              exceeds the threshold decided, then invalidates this bucket.
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PRIVATE S16  cmMmBktSanityChk
(
CmMmBkt  *bkt
)
#else
PRIVATE S16  cmMmBktSanityChk(bkt)
CmMmBkt  *bkt;
#endif
{
   CmMmBlkHdr *ptrBlk;
   U32 blkCnt;

   TRC2(cmMmBktSanityChk);

   bkt->trampleCount = 0;

   /* scan the entire memory list of the bucket */
   for (blkCnt = 0, ptrBlk = (CmMmBlkHdr *)bkt->bktStartPtr;
         blkCnt < (bkt->numBlks); blkCnt++)
   {
      if (cmMmRegIsBlkSane(ptrBlk) != ROK)
      {
         bkt->trampleCount++;
         if (bkt->trampleCount > CMM_TRAMPLING_THRESHOLD)
         {
            /* Take action to invalidate the entire bucket */
            RETVALUE(RTRAMPLINGNOK);
         }
      }
      /* reach next memory block in this bucket manually */
      ptrBlk = (CmMmBlkHdr *)((Data *)ptrBlk + ((bkt->size) + (sizeof(CmMmBlkHdr))));
   }

 #ifdef  DEBUGP
   /* display an error message here */
   sprintf(dbgPrntBuf, " %d Memory tramplings detected in the bucket!\n", bkt->trampleCount);
   SDisplay(0, dbgPrntBuf);
 #endif /* DEBUGP */

   RETVALUE(RTRAMPLINGOK);
}

/*
*
*       Fun:   cmMmHeapSanityChk
*
*       Desc:  Performs the sanity check for the memory blocks in the memory heap.
*              This API gets called when trampling is detected in heap(Alloc/Free).
*
*       Ret:   RTRAMPLINGNOK - Trampling, serious error
*              RTRAMPLINGOK  - Trampling, but OK to proceed
*
*       Notes: This function performs the memory block sanity in the heap. This
*              function is called by cmHeapAlloc and cmHeapFree as part of error
*              handling mechanism. Keeps track of number of tramplings happened.
*              If the count exceeds the threshold then return RTRAMPLINGNOK. If the
*              count is less than threshold, then return RTRAMPLINGOK.
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PRIVATE S16  cmMmHeapSanityChk
(
CmMmHeapCb  *heapCb
)
#else
PRIVATE S16  cmMmHeapSanityChk(heapCb)
CmMmHeapCb  *heapCb;
#endif
{

   TRC2(cmMmHeapSanityChk);

   /* increment the trample count */
   heapCb->trampleCount++;

   if (heapCb->trampleCount > CMM_TRAMPLING_THRESHOLD)
   {
      RETVALUE(RTRAMPLINGNOK);
   }

   RETVALUE(RTRAMPLINGOK);
}

/*
*
*       Fun:   cmMmRegIsBlkSane
*
*       Desc:  Performs the sanity check for the memory block by checking its header.
*
*       Ret:   ROK - If no trampling is detected in the block
*              RFAILED  - If trampling is detected in the block
*
*       Notes: This function performs the memory block sanity in a block.
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PUBLIC S16 cmMmRegIsBlkSane
(
CmMmBlkHdr *blkPtr
)
#else
PUBLIC S16 cmMmRegIsBlkSane(blkPtr)
CmMmBlkHdr *blkPtr;
#endif
{
   U32 sigCnt;

   TRC2(cmMmRegIsBlkSane);

   for ( sigCnt=0; sigCnt < CMM_TRAMPLING_SIGNATURE_LEN; sigCnt++)
   {
      if (blkPtr->trSignature[sigCnt] != 0xAB)
      {
         RETVALUE(RFAILED);
      }
   }

   RETVALUE(ROK);
}

/*
*
*       Fun:   cmMmHashFunc
*
*       Desc:  Computes the hash list index (bin number) for a specified
*              key of type (x % 101).
*
*       return (idx % hash_table_size);
*
*       Ret:   ROK     - successful, *idx contains computed index
*
*       Notes: None.
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PRIVATE S16 cmMmHashFunc
(
CmMmHashListCp *hashListCp,
U32 key,
U16 *idx
)
#else
PRIVATE S16 cmMmHashFunc (hashListCp, key, idx)
CmMmHashListCp *hashListCp; /* hash list control point */
U32 key; /* key string */
U16 *idx; /* idx to return */
#endif
{
   TRC2(cmMmHashFunc);

   *idx = (U16)(key % hashListCp->numOfbins);

   RETVALUE(ROK);

} /* end of cmMmHashFunc () */

/*
*
*       Fun:   cmMmHashListInit
*
*       Desc:  Initializes a hash list. Parameters are:
*
*              hashListCp   control point for hash list
*              nmbBins      number of bins in the hash list. Storage will
*                           be allocated for them from the indicated memory
*                           region and pool.
*              region
*              pool         for allocating storage for bins.
*
*       Ret:   ROK      - initialization successful
*              RFAILED  - initialization failed, lack of memory
*
*       Notes: None
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PRIVATE S16 cmMmHashListInit
(
CmMmHashListCp *hashListCp,  /* hash list to initialize */
U16          nmbBins,      /* number of hash list bins */
Region       region,       /* memory region to allocate bins */
Pool         pool          /* memory pool to allocate bins */
)
#else
PRIVATE S16 cmMmHashListInit(hashListCp, nmbBins, region, pool)
CmMmHashListCp *hashListCp;  /* hash list to initialize */
U16          nmbBins;      /* number of hash list bins */
Region       region;       /* memory region to allocate bins */
Pool         pool;         /* memory pool to allocate bins */
#endif
{
   U16 i;
   CmMmHashListEnt *hl;

   TRC2(cmMmHashListInit);

   /* initialize control point fields */
   hashListCp->hashList = NULLP;
   hashListCp->numOfbins = 0;
   hashListCp->numOfEntries  = 0;

   /* allocate memory for bins */
   if (nmbBins)
   {
      if (SGetSBuf(region, pool, (Data **) &hashListCp->hashList,
               (Size)(nmbBins * sizeof(CmMmHashListEnt))) != ROK)
      RETVALUE(RFAILED);

      /* initialize bin pointers */
      hl = hashListCp->hashList;
      for(i = 0; i < nmbBins; i++)
      {
         hl[i].size = hl[i].numAttempts = 0;
      }

      /* initialize bin size */
      hashListCp->numOfbins = nmbBins;
   }

   RETVALUE(ROK);
}

/*
*
*       Fun:   cmMmHashListDeinit
*
*       Desc:  Deinitializes a hash list. Deallocates memory for bins
*              and resets header fields. Parameters are:
*
*              hashListCp   control point for hash list
*              region
*              pool         for allocating storage for bins.
*
*       Ret:   ROK      - successful
*              RFAILED - failure, invalid parameters
*
*       Notes: None
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PRIVATE S16 cmMmHashListDeinit
(
CmMmHashListCp *hashListCp,   /* hash list to deinitialize */
Region       region,       /* memory region to allocate bins */
Pool         pool          /* memory pool to allocate bins */
)
#else
PRIVATE S16 cmMmHashListDeinit(hashListCp, region, pool)
CmMmHashListCp *hashListCp;  /* hash list to deinitialize */
Region       region;       /* memory region to allocate bins */
Pool         pool;         /* memory pool to allocate bins */
#endif
{
   TRC2(cmMmHashListDeinit);

   /* deallocate memory for bins */
   if (hashListCp->numOfbins)
      (Void) SPutSBuf(region, pool,
                      (Data *) hashListCp->hashList,
                      (Size) (hashListCp->numOfbins * sizeof(CmMmHashListEnt)));

   /* deinitialize control point fields */
   hashListCp->hashList = NULLP;
   hashListCp->numOfbins = 0;
   hashListCp->numOfEntries = 0;

   RETVALUE(ROK);
} /* end of cmMmHashListDeinit */

/*
*
*       Fun:   cmMmHashListInsert
*
*       Desc:  Inserts a new entry in the hash list. Parameters are:
*
*              hashListCp   control point for hash list
*              key          pointer to key string in the new entry
*
*       Ret:   ROK      - insertion successful
*              RFAILED  - insertion failed (incorrect parameter values)
*
*       Notes: None
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PRIVATE S16 cmMmHashListInsert
(
CmMmHashListCp *hashListCp,  /* hash list to add to */
U32           key         /* pointer to key */
)
#else
PRIVATE S16 cmMmHashListInsert(hashListCp, key)
CmMmHashListCp *hashListCp;  /* hash list to add to */
U32           key;         /* pointer to key */
#endif
{
   CmMmHashListEnt *hashListEnt;    /* pointer to hash list entry header */
   U16 idx;                       /* index for insertion into hash list */
   U16 i;

   TRC2(cmMmHashListInsert);

   /* check if hashListCp is initialised yet */
   if ( hashListCp->numOfbins == 0)
      RETVALUE(ROK);

   /* compute index for insertion */
   if (cmMmHashFunc(hashListCp, key, &idx) != ROK)
      RETVALUE(RFAILED);

   hashListEnt = hashListCp->hashList;

   if (hashListEnt[idx].numAttempts == 0)
   {
      /* new entry, insert here */
      hashListEnt[idx].size = key;
      hashListEnt[idx].numAttempts++;
      /* increment count of entries in hash list */
      hashListCp->numOfEntries++;
   }
   else
   {
      /* this hash is occupied, re-hash it using linear probing */
      for (i=idx; i < CMM_STAT_HASH_TBL_LEN; i++)
      {
         if (hashListEnt[i].size == key)
         {
            hashListEnt[i].numAttempts++;
            break;
         }

         if (hashListEnt[i].numAttempts == 0)
         {
            hashListEnt[i].size = key;
            hashListEnt[i].numAttempts++;
            /* increment count of entries in hash list */
            hashListCp->numOfEntries++;
            break;
         }
   }

   if (i == CMM_STAT_HASH_TBL_LEN)
   {
      /* there is no free slot for this key */
      RETVALUE(RFAILED);
   }
   }

   RETVALUE(ROK);
} /* end of cmMmHashListInsert */

#endif /* SSI_DEBUG_LEVEL1 */
/*  cm_mem_c_001.main_15 : Additions */
#ifdef SS_HISTOGRAM_SUPPORT  
/*
*
*       Fun:   cmHstGrmHashListInit
*
*       Desc:  Initializes a hash list. Parameters are:
*
*              hashListCp   control point for hash list
*       Ret:   ROK      - initialization successful
*              RFAILED  - initialization failed, lack of memory
*
*       Notes: None
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PRIVATE S16 cmHstGrmHashListInit
(
CmHstGrmHashListCp *hashListCp  /* hash list to initialize */
)
#else
PRIVATE S16 cmHstGrmHashListInit(hashListCp)
CmHstGrmHashListCp *hashListCp;  /* hash list to initialize */
#endif
{
   /*cm_mem_c_001.main_25 : Fix for TRACE5 feature crash due to missing TRC MACRO*/
   TRC2(cmHstGrmHashListInit)
#ifdef  DEBUGP
   /* display an error message here */
   /*cm_mem_c_001.main_25: Fixed Warnings for 32/64 bit compilation*/ 
#ifdef ALIGN_64BIT
    sprintf(dbgPrntBuf, " %lu size of memory histogram hash List\n", sizeof(CmHstGrmHashListCp));
#else
    sprintf(dbgPrntBuf, " %d size of memory histogram hash List\n", sizeof(CmHstGrmHashListCp));
#endif
    SDisplay(0, dbgPrntBuf);
#endif /* DEBUGP */
    memset(hashListCp, 0, sizeof(CmHstGrmHashListCp));
    RETVALUE(ROK);
}

/*
*
*       Fun:   cmHstGrmHashListDeInit
*
*       Desc:  De-initializes a hash list. Parameters are:
*
*              hashListCp   control point for hash list
*       Ret:   ROK      - initialization successful
*              RFAILED  - initialization failed, lack of memory
*
*       Notes: None
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PRIVATE S16 cmHstGrmHashListDeInit
(
CmHstGrmHashListCp *hashListCp  /* hash list to initialize */
)
#else
PRIVATE S16 cmHstGrmHashListDeInit(hashListCp)
CmHstGrmHashListCp *hashListCp;  /* hash list to initialize */
#endif
{
   /*cm_mem_c_001.main_25 : Fix for TRACE5 feature crash due to missing TRC MACRO*/
   TRC2(cmHstGrmHashListDeInit)
#ifdef  DEBUGP
   /* display an error message here */
   /*cm_mem_c_001.main_25: Fixed Warnings for 32/64 bit compilation*/ 
#ifdef ALIGN_64BIT
    sprintf(dbgPrntBuf, " %lu size of memory histogram hash List\n", sizeof(CmHstGrmHashListCp));
#else
    sprintf(dbgPrntBuf, " %d size of memory histogram hash List\n", sizeof(CmHstGrmHashListCp));
#endif
    SDisplay(0, dbgPrntBuf);
#endif /* DEBUGP */
    memset(hashListCp, 0, sizeof(CmHstGrmHashListCp));
    RETVALUE(ROK);
}

/*
*
*       Fun:   cmHstGrmFreeInsert
*
*       Desc:  Inserts a Freed information in into the hash list. Parameters are:
*
*              bkt : pointer to bucket for which memory is freed.
*              line : Line where memory is freed.
*              file : file where memory is freed.
*              entId : Tapa task which releases the memory.
*
*       Ret:   ROK      - insertion successful
*              RFAILED  - insertion failed (incorrect parameter values)
*
*       Notes: None
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PRIVATE S16 cmHstGrmFreeInsert
(
CmHstGrmHashListCp* hashListCp, /* hash list cp */
U32        blkSz, /* size of the block freed */
U32       line, /* Line number */
U8        *fileName, /* file name */
U8        entId    /* Tapa task which free the memory */
)
#else
PRIVATE S16 cmHstGrmFreeInsert(hashListCp, blkSz, line, fileName, entId)
CmHstGrmHashListCp* hashListCp; /* hash list cp */
U32        blkSz; /* size of the block freed */
U32       line; /* line number */
U8        *fileName; /* file Name */
U8        entId; /* Tapa task which frees the memory */
#endif
{
   U32                    binIdx = 0; /* Bin index to insert the entry into the hash list */
   U32                    key = 0; /* Key to fine the bin index */
   U32                    ret = 0; /* Return value */
   CmMemEntries           *entry = NULLP; /* Entry which contains the information */


   TRC2(cmHstGrmFreeInsert);

   /* check for the total number of entries in the hash list. *
    * If there is no place for new entry return failure */
    cmHstGrmGetHashIdxAndKey(fileName, line, &binIdx, &key);

   /* After comuting the hash bind and key, check the entity already *
      existing or not. if we found the entry then update the information */
   ret = cmHstGrmFindEntry(hashListCp, key, &binIdx, &entry);
   if(ret == ROK)
   {
		entry->freedBytes += blkSz;
      entry->bucketFreeReq++;
      RETVALUE(ROK);
   } /* End of if */

   /* If hash list is full then print the error tna continue */
   if(hashListCp->totalNumEntries == (CMM_HIST_MAX_MEM_BIN * CMM_HIST_MAX_MEM_ENTRY_PER_BIN))
   {
        printf("No place in the hash list. Increase the value of macro CMM_HIST_MAX_MEM_BIN and CMM_HIST_MAX_MEM_ENTRY_PER_BIN \n");
        RETVALUE(RFAILED);
   } /* End of if */

   /* Take the address of next free entry in the hash bin */
   entry = &(hashListCp->hashList[binIdx].entries[hashListCp->hashList[binIdx].numOfEntries]);

   /* Increase the number of time frees called */
   entry->bucketFreeReq++;
	entry->freedBytes += blkSz;

   /* Fill the information into the entry structure */
   cmHstGrmFillEntry(entry, key, line, fileName, entId);
   /* Increase the total numbet of entries in the bin */
   hashListCp->hashList[binIdx].numOfEntries++;

   /* Increase the total number of entries in the hash list */
   hashListCp->totalNumEntries++;

   RETVALUE(ROK);
} /* end of cmHstGrmFreeInsert */


/*
*
*       Fun:  ret = cmHstGrmAllocInsert
*
*       Desc:  Inserts a memory allocated information in the hash list. Parameters are:
*
*              hashListCp   control point for hash list
*              key          pointer to key string in the new entry
*
*       Ret:   ROK      - insertion successful
*              RFAILED  - insertion failed (incorrect parameter values)
*
*       Notes: None
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PRIVATE S16 cmHstGrmAllocInsert
(
CmHstGrmHashListCp     *hashListCp,
U32       blkSz,
U32       *reqSz,
U32       line,
U8        *fileName,
U8        entId
)
#else
PRIVATE  S16 cmHstGrmAllocInsert(hashListCp, blkSz, reqSz, line, fileName, entId)
CmHstGrmHashListCp     *hashListCp;
U32       blkSz;
U32       *reqSz;
U32       line;
U8        *fileName;
U8        entId;
#endif
{
   U32                    binIdx = 0;
   U32                    key = 0;
   U32                    ret = 0;
   CmMemEntries           *entry = NULLP;

   TRC2(cmHstGrmAllocInsert);

   /* check for the total number of entries in the hash list. *
    * If there is no place for new entry return failure */
   cmHstGrmGetHashIdxAndKey(fileName, line, &binIdx, &key);

   /* After comuting the hash bind and key, check the entity already *
      existing or not. if we found the entry then update the information */
   ret = cmHstGrmFindEntry(hashListCp, key, &binIdx, &entry);

   if(ret == ROK)
   {
	   entry->allocBytes += blkSz;
      entry->bucketAllocReq++;
      entry->wastedBytes += (blkSz - *reqSz);
      RETVALUE(ROK);
   } /* End of if */

   if(hashListCp->totalNumEntries == (CMM_HIST_MAX_MEM_BIN * CMM_HIST_MAX_MEM_ENTRY_PER_BIN))
   {
        printf("No place in the hash list. Increase the value of macro CMM_HIST_MAX_MEM_BIN and CMM_HIST_MAX_MEM_ENTRY_PER_BIN\n");
        RETVALUE(RFAILED);
   } /* End of if */

   /* Take the address of next free entry in the hash bin */
   entry = &(hashListCp->hashList[binIdx].entries[hashListCp->hashList[binIdx].numOfEntries]);

   /* Clauculae the wasted bytes */
   /* Here wasted byte is differnce between the byte user
    * has requested and the byte the ssi allocated */
   entry->wastedBytes += (blkSz - *reqSz);
   entry->bucketAllocReq++;
	entry->allocBytes += blkSz;

   /* Fill the information into the entry structure */
   cmHstGrmFillEntry(entry, key, line, fileName, entId);
   /* Increase the total numbet of entries in the bin */
   hashListCp->hashList[binIdx].numOfEntries++;

   /* Increase the total number of entries in the hash list */
   hashListCp->totalNumEntries++;

   RETVALUE(ROK);
} /* end of cmHstGrmAllocInsert */


/*
*
*       Fun:   cmHstGrmGetHashIdxAndKey
*
*       Desc:  Finds an entry in the hash list. Parameters are:
*
*              hashListCp   control point for hash list
*              key          pointer to key string in the new entry
*
*       Ret:   ROK      - insertion successful
*              RFAILED  - insertion failed (incorrect parameter values)
*
*       Notes: None
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PRIVATE S16 cmHstGrmGetHashIdxAndKey
(
U8                 *fileName,
U32                line,
U32                *binIdx,
U32                *key
)
#else
PRIVATE  S16 cmHstGrmGetHashIdxAndKey(fileName, line, binIdx, key)
U8                 *fileName;
U32                line;
U32                *binIdx;
U32                *key;
#endif
{

   U32  i = 0;
   TRC2(cmHstGrmGetHashIdxAndKey);

   /* Calculate the key using file name and line number */
   for(i = 0 ; fileName[i] != '\0'; i++)
   {
       *key += fileName[i];
   }/* End of for */
       *key += line;
   *binIdx = ( *key % CMM_HIST_MAX_MEM_BIN);
   RETVALUE(ROK);
} /* end of cmHstGrmFillEntry */

/*
*
*       Fun:   cmHstGrmFillEntry
*
*       Desc:  Insert the entry into the hash list.
*
*              entry : Infornation which will be inserted into the hash list
*              key   : Which will be used ti find the entry.
*              line  : Line number
*              fileName : File name
*              entId   : Tapa task Id
*
*       Ret:   ROK      - insertion successful
*              RFAILED  - insertion failed (incorrect parameter values)
*
*       Notes: None
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PRIVATE S16 cmHstGrmFillEntry
(
CmMemEntries       *entry,
U32                key,
U32                line,
U8                 *fileName,
U8                 entId
)
#else
PRIVATE  S16 cmHstGrmFillEntry(entry, key, line, fileName, entId)
CmMemEntries       *entry;
U32                key;
U32                line;
U8                 *fileName;
U8                 entId;
#endif
{

   U32       idx = 0;
   TRC2(cmHstGrmFillEntry);
   entry->key = key;
   entry->line = line;
   entry->entId = entId;
   for(idx = 0; fileName[idx] != '\0'; idx++)
   {
      entry->fileName[idx] = fileName[idx];
   }
   entry->fileName[idx] = '\0';
   RETVALUE(ROK);
} /* end of cmHstGrmFillEntry */

/*
*
*       Fun:  cmHstGrmFindEntry
*
*       Desc:  Finds an entry in the hash list. Parameters are:
*
*              hashListCp   control point for hash list
*              key          pointer to key string in the new entry
*
*       Ret:   ROK      - insertion successful
*              RFAILED  - insertion failed (incorrect parameter values)
*
*       Notes: None
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PRIVATE S16 cmHstGrmFindEntry
(
CmHstGrmHashListCp  *hashListCp,
U32                 key,
U32                 *binIdx,
CmMemEntries        **entry
)
#else
PRIVATE  S16 cmHstGrmFindEntry(hashListCp, key, binIdx, entry)
CmHstGrmHashListCp  *hashListCp;
U32                 key;
U32                 *binIdx;
CmMemEntries        **entry;
#endif
{

   U32                  numEnt = 0;
   U32                  numBin = 0;
   CmHstGrmHashListEnt  *tmpBin = NULLP;

   TRC2(cmHstGrmFindEntry);


   for(numBin = 0; numBin < CMM_HIST_MAX_MEM_BIN; numBin++)
   {
      /* find for the entry in the bin */
      tmpBin = &(hashListCp->hashList[*binIdx]);
      for(numEnt = 0; numEnt < tmpBin->numOfEntries; numEnt++)
      {
         /* If key supplied is matched with the stored key then
          * return that entity */
         if(tmpBin->entries[numEnt].key == key)
         {
            *entry = &(tmpBin->entries[numEnt]);
            RETVALUE(ROK);
         }/* End of if (tmpBin->entries[numEnt].key) */
      }/* end of for (numEnt = 0) */

      /* Here we are checking for any room left in the bin. If the room *
         exists its mean that there is no entry with the Key. so return *
         failure.
         If there is no room in the bin, then check the other bins to find *
         the entry */
      if(numEnt == CMM_HIST_MAX_MEM_ENTRY_PER_BIN)
      {
        if(*binIdx == CMM_HIST_MAX_MEM_BIN)
        {
            *binIdx = 0;
        }/* End of if (binIdx) */
        else
        {
            *binIdx++;
        }/* End of else (binIdx) */
      } /* End of if (numEnt) */
      else
      {
         printf ("Unable to find the entry in hash list\n");
         RETVALUE(RFAILED);
      }/* End of else (numEnt) */
   }/* end of for (numBin = 0) */

   printf("Unable to find the entry in the hash list\n");
   RETVALUE(RFAILED);
} /* end of cmHstGrmFindEntry */

#endif /* SS_HISTOGRAM_SUPPORT */
#ifdef T2K_MEM_LEAK_DBG
T2kMeamLeakInfo gMemLeakInfo[T2K_MEM_LEAK_INFO_TABLE_SIZE];
U32 getT2kMemLeakIndex(U32 address)
{
#if 0
   /*
      1   2   3   4   5   6  7  

      XOR 7 with 3 and remove 7
      XOR 1 with 5 and remove 1
   */
   
   address -= T2K_MEM_LEAK_START_ADDR;

   U8 Nib7 = address &  0x0000000f;
   U8 Nib1 = (address & 0x0f000000) >>24;
   U8 Nib3 = (address & 0x000f0000) >> 16;
   U8 Nib5 = (address & 0x00000f00) >> 8;

   /* store 8 ^ 3 in 8Nib */
   Nib7 = Nib7 ^ Nib3;
   /* store 1 ^ 6 in 6Nib */
   Nib5 = Nib5 ^ Nib1;

   return(((address & 0x000fff00) | (Nib7 << 20) | (Nib5 << 4)) >> 4);
   
#endif
   return ((address - T2K_MEM_LEAK_START_ADDR) >> 8);
}

static U32 t2kMemAllocTick;
static U32 smallTick;

void InsertToT2kMemLeakInfo(U32 address, U32 size, U32 lineNo, char* fileName)
{
   U32 idx = getT2kMemLeakIndex(address);

   if(((U32)(address - T2K_MEM_LEAK_START_ADDR) & 0xff) !=0)
   {
     printf("address in InsertToT2kMemLeakInfo is %lx size = %ld file is %s"
           "line is %ld \n", address, size, fileName, lineNo);
   }

   if(gMemLeakInfo[idx].address == 0)
   {
      gMemLeakInfo[idx].address = address;
      gMemLeakInfo[idx].size = size;
      gMemLeakInfo[idx].lineNo = lineNo;
      gMemLeakInfo[idx].fileName = fileName;
      gMemLeakInfo[idx].age = t2kMemAllocTick; 
      gMemLeakInfo[idx].prevRemLineNo = 0;
      gMemLeakInfo[idx].prevRemFileName = '\0';

      if(smallTick++ == 4096)
      {
         smallTick = 0;
	      gMemLeakInfo[idx].age = (++t2kMemAllocTick); 
      }
   }
   else
   {
         printf("Something is wrong, trying to insert %lx idx = %ld file is %s"
               "line is %ld \n",address, idx, fileName, lineNo);
         printf("Address present :%lx, from File:%s, Line:%ld, Size:%ld,"
               "Age:%ld, differnce in Age:%ld",
               gMemLeakInfo[idx].address, gMemLeakInfo[idx].fileName,
               gMemLeakInfo[idx].lineNo, gMemLeakInfo[idx].size,
               gMemLeakInfo[idx].age, (t2kMemAllocTick-gMemLeakInfo[idx].age));
#if 0
      /* Try inserting into some other location */
      int i;
      int lastIndex = idx  + 1;
      Bool inserted = FALSE;
      for(i = 2; lastIndex < T2K_MEM_LEAK_INFO_TABLE_SIZE && i < 30; i++)
      {
         if(gMemLeakInfo[lastIndex].address == 0)
         {
            gMemLeakInfo[lastIndex].address = address;
            gMemLeakInfo[lastIndex].size = size;
            gMemLeakInfo[lastIndex].lineNo = lineNo;
            gMemLeakInfo[lastIndex].fileName = fileName;
            gMemLeakInfo[lastIndex].age = (++t2kMemAllocTick) >> 14; /*For every  16384 memory block allocations,Alloc Tick is incremented by 1*/
            inserted = TRUE;
            break;
         }
         lastIndex = idx + (i * i * i);
      }
#if 1
      if(!inserted)
      {
         printf("Something is wrong, trying to insert %x idx = %d no free i = %d\n",address, idx, i);
      }
#endif
#endif
   }
}


void RemoveFromT2kMemLeakInfo(U32 address, char *file, U32 line)
{
   U32 idx = getT2kMemLeakIndex(address);

   if(idx >= T2K_MEM_LEAK_INFO_TABLE_SIZE)
   {
      printf("Idx out of range = %ld address is %lx file = %s line = %ld. We are going to crash!!!\n",
              idx,
              address,
              file,
              line);
   }
   if(gMemLeakInfo[idx].address == address)
   {
      gMemLeakInfo[idx].address = 0;
      gMemLeakInfo[idx].age = 0; 
      gMemLeakInfo[idx].prevRemLineNo = gMemLeakInfo[idx].lineNo;
      gMemLeakInfo[idx].prevRemFileName = gMemLeakInfo[idx].fileName; 

      gMemLeakInfo[idx].lastDelLineNum = line;
      gMemLeakInfo[idx].lastDelFileName = file; 
      /*printf("Something is wrong, Trying to double free Address = %x, Idx = %d \n",address,idx);*/
   }
   else
   {
         printf("Something is wrong, trying to remove %lx idx = %ld  from"
               "File=%s, line=%ld address present is %lx\n",address, idx, file,line, 
                   gMemLeakInfo[idx].address);


         printf("\n Last Del file %s line %ld\n",gMemLeakInfo[idx].lastDelFileName,
                 gMemLeakInfo[idx].lastDelLineNum);

         if(gMemLeakInfo[idx].prevRemFileName != NULLP)
         {
            printf("Previous File:%s, Previous Line:%ld\n",
                  gMemLeakInfo[idx].prevRemFileName, gMemLeakInfo[idx].prevRemLineNo);
         }
#if 0
      /* Try removing from some other location where it might have been stored*/
      int i;
      int lastIndex = idx + 1;
      Bool removed = FALSE;
      for(i = 2; lastIndex < T2K_MEM_LEAK_INFO_TABLE_SIZE && i < 30; i++)
      {
         if(gMemLeakInfo[lastIndex].address == address)
         {
            gMemLeakInfo[lastIndex].address = 0;
            gMemLeakInfo[lastIndex].size = 0;
            gMemLeakInfo[lastIndex].lineNo = 0;
            gMemLeakInfo[lastIndex].fileName = 0;
            gMemLeakInfo[lastIndex].age = 0; /*For every  16384 memory block allocations,Alloc Tick is incremented by 1*/
            removed = TRUE;
            break;
         }
         lastIndex = idx + (i*i*i);
      }
#if 1
      if(!removed)
      {
         printf("Something is wrong, trying to remove %x idx = %d  lastIndex = %d FreeCalled from File=%s, line=%d\n",address, idx, lastIndex,file,line);
      }
#endif
#endif
   }
}

PUBLIC void DumpT2kMemLeakInfoToFile()
{
   int i;
  
   FILE *fp = fopen("memLeakInfo.txt","wb");

   if(fp == NULL)
   {
      printf("Could not open file for dumping mem leak info\n");
      return;
   }

   for(i = 0; i< T2K_MEM_LEAK_INFO_TABLE_SIZE; i++)
   {
      if(gMemLeakInfo[i].address != 0)
      {
         char* onlyFileName = rindex(gMemLeakInfo[i].fileName,'/');
         if(onlyFileName == NULL)
         {
            onlyFileName = gMemLeakInfo[i].fileName;
         }

         fprintf(fp, "%ld  s=%ld  a=%ld  l=%ld  f=%s\n",gMemLeakInfo[i].address,
                                            gMemLeakInfo[i].size,
                                            gMemLeakInfo[i].age,
                                            gMemLeakInfo[i].lineNo,
                                            onlyFileName);
      }
   }

   fprintf(fp,"Current t2kMemAllocTick = %ld\n",t2kMemAllocTick);

   fclose(fp);
}
#endif

#ifdef TENB_T2K3K_SPECIFIC_CHANGES

/* For Updating SOC Specific Memory Information */
#ifdef ANSI
PUBLIC S16 UpdateSocMemInfo
(
U8 areaIndex,
CmLteMemInfo *mInfo
)
#else
PUBLIC S16 UpdateSocMemInfo(areaIndex,mInfo)
U8 areaIndex;
CmLteMemInfo *mInfo;
#endif
{
   U8  idxReg;
   U8  idxPool;
   U16  numPool;
   void *iccHdl = NULLP;
   U32 poolFreeCnt[4];
   U32 poolUsedCnt[4];
   U32 poolSize[4];
   U32 poolTotAvail[4];

   idxReg = mInfo->numRegions;
   mInfo->numRegions = mInfo->numRegions + 1;
   /* Calling Soc specific API to get shared memory status */
   numPool = 4; /* For Intel it is fixed to 4. Change to API call when available */
   iccHdl = ssGetIccHdl(areaIndex);

   /* Populating global memory information */
   mInfo->regInfo[idxReg].numPools = numPool;
   mInfo->regInfo[idxReg].regionId = areaIndex;
   mInfo->regInfo[idxReg].regionType = 1; /* 1 - SHARED REGION */

   /* Calling INTEL API's to Get Free MEM BLOCKS */
   poolFreeCnt[0] = TL_GetFreeBlocks(iccHdl, ICC_POOL_ZERO_SIZE);
   poolFreeCnt[1] = TL_GetFreeBlocks(iccHdl, ICC_POOL_ONE_SIZE);
   poolFreeCnt[2] = TL_GetFreeBlocks(iccHdl, ICC_POOL_TWO_SIZE);
   poolFreeCnt[3] = TL_GetFreeBlocks(iccHdl, ICC_POOL_THREE_SIZE);

   poolUsedCnt[0] = ICC_POOL_ZERO_TOTAL_BLKS - poolFreeCnt[0];
   poolUsedCnt[1] = ICC_POOL_ONE_TOTAL_BLKS - poolFreeCnt[1];
   poolUsedCnt[2] = ICC_POOL_TWO_TOTAL_BLKS - poolFreeCnt[2];
   poolUsedCnt[3] = ICC_POOL_THREE_TOTAL_BLKS - poolFreeCnt[3];
     
   poolSize[0] = ICC_POOL_ZERO_SIZE;
   poolSize[1] = ICC_POOL_ONE_SIZE;
   poolSize[2] = ICC_POOL_TWO_SIZE;
   poolSize[3] = ICC_POOL_THREE_SIZE;

   poolTotAvail[0] = ICC_POOL_ZERO_TOTAL_BLKS;
   poolTotAvail[1] = ICC_POOL_ONE_TOTAL_BLKS;
   poolTotAvail[2] = ICC_POOL_TWO_TOTAL_BLKS;
   poolTotAvail[3] = ICC_POOL_THREE_TOTAL_BLKS;

   for(idxPool=0; idxPool<numPool;idxPool++)
   {
      mInfo->regInfo[idxReg].poolInfo[idxPool].poolSize = poolSize[idxPool];
      mInfo->regInfo[idxReg].poolInfo[idxPool].totAvailable = 
                                                poolTotAvail[idxPool];
      mInfo->regInfo[idxReg].poolInfo[idxPool].crntUsed = poolUsedCnt[idxPool];
      if(mInfo->regInfo[idxReg].poolInfo[idxPool].crntUsed > 
                   mInfo->regInfo[idxReg].poolInfo[idxPool].maxUsed)
      {
         mInfo->regInfo[idxReg].poolInfo[idxPool].maxUsed = 
                         mInfo->regInfo[idxReg].poolInfo[idxPool].crntUsed;
      }
   }

   RETVALUE(ROK);
}

/*
*
*       Fun:   isMemUsageBelowLowerThreshold
*
*       Desc:  Checks for the Lower threshold of ICC memory.
*
*              region       region for obtaining the ICC handle
*
*       Ret:   TRUE      - Threshold has reached
*              FALSE     - Threshold has not reached
*
*       Notes: None
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PRIVATE U32 isMemUsageBelowLowerThreshold(
Region region
)
#else
PRIVATE U32 isMemUsageBelowLowerThreshold(region)
Region region;
#endif
{
   void * iccHdl = ssGetIccHdl(region);

   U32 poolZeroFreeCnt = TL_GetFreeBlocks(iccHdl, ICC_POOL_ZERO_SIZE);
   U32 poolOneFreeCnt = TL_GetFreeBlocks(iccHdl, ICC_POOL_ONE_SIZE);
   U32 poolTwoFreeCnt = TL_GetFreeBlocks(iccHdl, ICC_POOL_TWO_SIZE);
   U32 poolThreeFreeCnt = TL_GetFreeBlocks(iccHdl, ICC_POOL_THREE_SIZE);

   /* We are below the threshold if free count in BOTH of the pools
    * is above the ICC_MEM_LOWER_THRESHOLD % */
   if(((poolZeroFreeCnt * 100) > 
      (ICC_MEM_LOWER_THRESHOLD * ICC_POOL_ZERO_TOTAL_BLKS)) &&
      ((poolOneFreeCnt * 100) >
       (ICC_MEM_LOWER_THRESHOLD * ICC_POOL_ONE_TOTAL_BLKS)) &&
      ((poolTwoFreeCnt * 100) >
       (ICC_MEM_LOWER_THRESHOLD * ICC_POOL_TWO_TOTAL_BLKS)) &&
      ((poolThreeFreeCnt * 100) >
       (ICC_MEM_LOWER_THRESHOLD * ICC_POOL_THREE_TOTAL_BLKS)))
     {
        RETVALUE(TRUE);
     }

   RETVALUE(FALSE);
}

/*
*
*       Fun:   isMemUsageAboveUpperThreshold
*
*       Desc:  Checks for the Upper threshold of ICC memory.
*
*              region       region for obtaining the ICC handle
*
*       Ret:   TRUE      - Threshold has reached
*              FALSE     - Threshold has not reached
*
*       Notes: None
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PRIVATE U32 isMemUsageAboveUpperThreshold(
Region region
)
#else
PRIVATE U32 isMemUsageAboveUpperThreshold(region)
Region region;
#endif
{
   void * iccHdl = ssGetIccHdl(region);

   U32 poolZeroFreeCnt = TL_GetFreeBlocks(iccHdl, ICC_POOL_ZERO_SIZE);
   U32 poolOneFreeCnt = TL_GetFreeBlocks(iccHdl, ICC_POOL_ONE_SIZE);
   U32 poolTwoFreeCnt = TL_GetFreeBlocks(iccHdl, ICC_POOL_TWO_SIZE);
   U32 poolThreeFreeCnt = TL_GetFreeBlocks(iccHdl, ICC_POOL_THREE_SIZE);

   /* We are above the threshold if free count in either of the pools
    * is below the ICC_MEM_UPPER_THRESHOLD % */
   if(((poolZeroFreeCnt * 100) < 
      (ICC_MEM_UPPER_THRESHOLD * ICC_POOL_ZERO_TOTAL_BLKS)) ||
      ((poolOneFreeCnt * 100) <
       (ICC_MEM_UPPER_THRESHOLD * ICC_POOL_ONE_TOTAL_BLKS)) ||
      ((poolTwoFreeCnt * 100) <
       (ICC_MEM_UPPER_THRESHOLD * ICC_POOL_TWO_TOTAL_BLKS)) ||
      ((poolThreeFreeCnt * 100) <
       (ICC_MEM_UPPER_THRESHOLD * ICC_POOL_THREE_TOTAL_BLKS)))
     {
        RETVALUE(TRUE);
     }

   RETVALUE(FALSE);
}

/* ccpu00142274- Function to check if we have reached the 
 * Threshold for dropping UL packets at the RLC. This function
 * measures the free count of the ICC memory and based on the 
 * volume of packets it sets an alarm to drop packets. 
 * In DL, the PDCP packets are dropped at Admission Control, but 
 * at UL we need to check if its an AM(Data only and 
 * not Status PDU) or UM packet and free the PDU 
 * Note: With the current design, we have PDCP DL and RLC UL
 * running in the same thread and the below function will be 
 * accessed in tandem. But if PDCP DL and RLC UL are made to run 
 * in different threads then there might be a race condition.
 * Please revisit this function in such a case.
 * */
/*
*
*       Fun:   isMemThreshReached
*
*       Desc:  Checks whether the system has reached the 
*              designated threshold of ICC memory.
*
*              region       region for obtaining the ICC handle
*
*       Ret:   ROK         - Threshold has not reached
*              RFAILED     - Threshold has reached
*
*       Notes: None
*
*       File:  cm_mem_wl.c
*
*/
#ifdef ANSI
PUBLIC U32 isMemThreshReached(
Region reg
)
#else
PUBLIC U32 isMemThreshReached(reg)
Region reg;
#endif
{
   TRC3(isMemThreshReached)
   if(gMemoryAlarm)
   {
      gMemoryAlarm = !(isMemUsageBelowLowerThreshold(reg));
      RETVALUE(RFAILED);
   }
   else
   {
      if(memoryCheckCounter++ >= NUM_CALLS_TO_CHECK_MEM_AGAIN)
      {
         gMemoryAlarm = isMemUsageAboveUpperThreshold(reg);
         memoryCheckCounter = 0;
      }
   }
   RETVALUE(ROK);
}
#endif
#endif /* SS_LOCKLESS_MEMORY */
#if 0
T2kMeamLeakInfo gMemLeakInfo[T2K_MEM_LEAK_INFO_TABLE_SIZE];
U32 getT2kMemLeakIndex(U32 address)
{
#if 0
   /*
      1   2   3   4   5   6  7  

      XOR 7 with 3 and remove 7
      XOR 1 with 5 and remove 1
   */
   
   address -= T2K_MEM_LEAK_START_ADDR;

   U8 Nib7 = address &  0x0000000f;
   U8 Nib1 = (address & 0x0f000000) >>24;
   U8 Nib3 = (address & 0x000f0000) >> 16;
   U8 Nib5 = (address & 0x00000f00) >> 8;

   /* store 8 ^ 3 in 8Nib */
   Nib7 = Nib7 ^ Nib3;
   /* store 1 ^ 6 in 6Nib */
   Nib5 = Nib5 ^ Nib1;

   return(((address & 0x000fff00) | (Nib7 << 20) | (Nib5 << 4)) >> 4);
   
#endif
   return ((address - T2K_MEM_LEAK_START_ADDR) >> 8);
}

static U32 t2kMemAllocTick;
static U32 smallTick;

void InsertToT2kMemLeakInfo(U32 address, U32 size, U32 lineNo, char* fileName)
{
   U32 index = getT2kMemLeakIndex(address);

   if(((U32)(address - T2K_MEM_LEAK_START_ADDR) & 0xff) !=0)
   {
     printf("address in InsertToT2kMemLeakInfo is %x size = %d file is %s line is %d \n", address, size, fileName, lineNo);
   }

   if(gMemLeakInfo[index].address == 0)
   {
      gMemLeakInfo[index].address = address;
      gMemLeakInfo[index].size = size;
      gMemLeakInfo[index].lineNo = lineNo;
      gMemLeakInfo[index].fileName = fileName;
      gMemLeakInfo[index].age = t2kMemAllocTick; 
      gMemLeakInfo[index].prevRemLineNo = 0;
      gMemLeakInfo[index].prevRemFileName = '\0';

      if(smallTick++ == 4096)
      {
         smallTick = 0;
	      gMemLeakInfo[index].age = (++t2kMemAllocTick); 
      }
   }
   else
   {
         printf("Something is wrong, trying to insert %x index = %d file is %s line is %d \n",address, index, fileName, lineNo);
         printf("Address present :%x, from File:%s, Line:%d, Size:%d, Age:%d",
               gMemLeakInfo[index].address, gMemLeakInfo[index].fileName,
               gMemLeakInfo[index].lineNo, gMemLeakInfo[index].size,
               gMemLeakInfo[index].age);
#if 0
      /* Try inserting into some other location */
      int i;
      int lastIndex = index  + 1;
      Bool inserted = FALSE;
      for(i = 2; lastIndex < T2K_MEM_LEAK_INFO_TABLE_SIZE && i < 30; i++)
      {
         if(gMemLeakInfo[lastIndex].address == 0)
         {
            gMemLeakInfo[lastIndex].address = address;
            gMemLeakInfo[lastIndex].size = size;
            gMemLeakInfo[lastIndex].lineNo = lineNo;
            gMemLeakInfo[lastIndex].fileName = fileName;
            gMemLeakInfo[lastIndex].age = (++t2kMemAllocTick) >> 14; /*For every  16384 memory block allocations,Alloc Tick is incremented by 1*/
            inserted = TRUE;
            break;
         }
         lastIndex = index + (i * i * i);
      }
#if 1
      if(!inserted)
      {
         printf("Something is wrong, trying to insert %x index = %d no free i = %d\n",address, index, i);
      }
#endif
#endif
   }
}


void RemoveFromT2kMemLeakInfo(U32 address, char *file, U32 line)
{
   U32 index = getT2kMemLeakIndex(address);

   if(index >= T2K_MEM_LEAK_INFO_TABLE_SIZE)
   {
      printf("Index out of range = %d address is %x file = %s line = %d. We are going to crash!!!\n",
              index,
              address,
              file,
              line);
   }
   if(gMemLeakInfo[index].address == address)
   {
      gMemLeakInfo[index].address = 0;
      gMemLeakInfo[index].age = 0; 
      gMemLeakInfo[index].prevRemLineNo = gMemLeakInfo[index].lineNo;
      gMemLeakInfo[index].prevRemFileName = gMemLeakInfo[index].fileName; 

      /*printf("Something is wrong, Trying to double free Address = %x, Index = %d \n",address,index);*/
   }
   else
   {
         printf("Something is wrong, trying to remove %x index = %d  from File=%s, line=%d address present is %x\n",address, index, file,line, 
                   gMemLeakInfo[index].address);
         if(gMemLeakInfo[index].prevRemFileName != NULLP)
         {
            printf("Previous File:%s, Previous Line:%d\n",
                  gMemLeakInfo[index].prevRemFileName, gMemLeakInfo[index].prevRemLineNo);
         }
#if 0
      /* Try removing from some other location where it might have been stored*/
      int i;
      int lastIndex = index + 1;
      Bool removed = FALSE;
      for(i = 2; lastIndex < T2K_MEM_LEAK_INFO_TABLE_SIZE && i < 30; i++)
      {
         if(gMemLeakInfo[lastIndex].address == address)
         {
            gMemLeakInfo[lastIndex].address = 0;
            gMemLeakInfo[lastIndex].size = 0;
            gMemLeakInfo[lastIndex].lineNo = 0;
            gMemLeakInfo[lastIndex].fileName = 0;
            gMemLeakInfo[lastIndex].age = 0; /*For every  16384 memory block allocations,Alloc Tick is incremented by 1*/
            removed = TRUE;
            break;
         }
         lastIndex = index + (i*i*i);
      }
#if 1
      if(!removed)
      {
         printf("Something is wrong, trying to remove %x index = %d  lastIndex = %d FreeCalled from File=%s, line=%d\n",address, index, lastIndex,file,line);
      }
#endif
#endif
   }
}

void DumpT2kMemLeakInfoToFile()
{
   int i;
  
   FILE *fp = fopen("memLeakInfo.txt","wb");

   if(fp == NULL)
   {
      printf("Could not open file for dumping mem leak info\n");
      return;
   }

   for(i = 0; i< T2K_MEM_LEAK_INFO_TABLE_SIZE; i++)
   {
      if(gMemLeakInfo[i].address != 0)
      {
         char* onlyFileName = rindex(gMemLeakInfo[i].fileName,'/');
         if(onlyFileName == NULL)
         {
            onlyFileName = gMemLeakInfo[i].fileName;
         }

         fprintf(fp, "%p  s=%d  a=%d  l=%d  f=%s\n",gMemLeakInfo[i].address,
                                            gMemLeakInfo[i].size,
                                            gMemLeakInfo[i].age,
                                            gMemLeakInfo[i].lineNo,
                                            onlyFileName);
      }
   }

   fprintf(fp,"Current t2kMemAllocTick = %d\n",t2kMemAllocTick);

   fclose(fp);
}
#endif


/********************************************************************30**
 
         End of file:     cm_mem_wl.c@@/main/TeNB_Main_BR/6 - Tue Jul  8 12:01:57 2014
 
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
1.1          ---      rm   1. initial release

1.2          ---      kr   1. Fixed a bug in function cmMmRegInit
             ---      kp   2. Fixed miscellaneous GCC compile warnings
             ---      kp   3. Bug fix in cmHeapFree

1.3          ---      rm   1. Implement separate locks for each configured
                              bucket.

1.4          ---      ada  1. Removed chksrc generated error

1.5          ---      ada  1. Bug fix in cmAlloc

             ---      ada  2. In cmCtl, corrected resource check in heap
                              to return available memory
             ---      ada  3. In cmMmRegInit, only allow bucket size to
                              be a multiple of quantumn size
1.6          ---      dvs  1. updated copyright
1.7          ---      bbk  1. Fixed bug in for loop in cmHeapAlloc
/main/9      ---      jjn  1. Initialize regInfo->flag in cmMmRegInit
                           2. cmCtl has been modified for the memory
                              resource status to indicate the available
                              bucket memory of the requested size plus the
                              heap.
                           3. The cmHeapFree was not freeing memory
                              for the case after all memory is allocated
                           4. cmAlloc, cmFree and cmCtl have been mapped
                              to use malloc and free if USE_PURE is defined.
                              This is to run memory leak detection tool.
/main/10     ---      bdu  1. Changes have been made in order to support
                              huge memory allocation.
                           2. Modify the cmHeapFree to merge the memory
                              block correctly.
/main/11     ---     rbabu 1.Updated copy right information.
/main/12     ---     pdb   1. Changes made to accomodate memory calculator
                              tool support
/main/12  cm_mem_c_001.main_12     vk    1. Modifications for SSI enhancements
/main/14     ---      cm_mem_c_001.main_13     rks   1. Replaced mutex related calls for 
                                            Windows
/main/15     ---      cm_mem_c_001.main_14        ch    1. Updated for SSI Multicore.
/main/16     ---      ch   1.Multicore Support.
/main/17     ---      cm_mem_c_001.main_15 schandra1 1. SSI Phase-2 value added feature additions
/main/19  cm_mem_c_001.main_18 schandra1 1. Correction in cmHeapAlloc and patch Id correction
/main/20  cm_mem_c_001.main_20 pmacharla 1.Added cmMmRegInit() debug prints
                                         2.dbgPrntBuf is guarded under SSI_DEBUG_LEVEL1
                                           or SS_HISTOGRAM_SUPPORT
/main/21  cm_mem_c_001.main_21 akulkarni 1. Added prototyp and definition for
                                            cmAllocWL and cmFreeWL
                                         2. Modified cmMmRegInit to register allocatio free function
                                            for new region add for FAP
/main/21    cm_mem_c_002.main_21 pmacharla 1.Added cmDeinitMemLeakMdl
/main/22     ---      cm_mem_c_003.main_21 pmacharla 1.Patch for SID Correction
/main/23     ---      cm_mem_c_001.main_22 svenkat  1. Fixing warnings on GCC compiler. ccpu00106125.
/main/24     ---      cm_mem_c_001.main_23 ssahniX   1. Removed support of SSI_DEBUG_LEVEL1, SS_HISTOGRAM_SUPPORT,
                                              USE_MEMCAL and MEMCAL_DEBUG for SS_FAP
                                           2. Fix for specifier mismatch warnings in 64BIT compilation  
                                           3. Adding check to compair size with Maximum block size 
                                              in cmAllocWL
/main/25     ---      cm_mem_c_001.main_24 ssahniX   1. Fix for memory corruption
/main/26     ---      cm_mem_c_001.main_25 ssahniX   1.Fix for TRACE5 feature crash due to
                                                        missing TRC MACRO
                                                     2. Fixed compilation warnings 32/64 bit
/main/27     ---      cm_mem_c_001.main_26 spoovalingam   1. Fixes for Compilation Warnings 
/main/28     ---      cm_mem_c_001.main_27 ssahniX        1. SSI-4GMX related memory fixes
*********************************************************************91*/

 

