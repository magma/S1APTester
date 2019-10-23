

/********************************************************************20**
  
     Name:    Ring Buffer 
  
     Type:     C include file
  
     Desc:     This file implements the funcitons required to isolate
               freeing of packer buffers from Main stack processing. This will be 
               usefull in a hyper threaded environment where the freeing can be
               done from low priority thread
  
     File:    ss_rbuf.h 
  
     Sid:      ss_rbuf.h@@/main/TeNB_Main_BR/tenb_brcm_fdd_3.0.1_to_tdd_GA_4.0_merge/1 - Fri Sep 12 10:55:22 2014
   
     Prg:      
  
*********************************************************************21*/
#ifndef __SS_RBUF_H__
#define __SS_RBUF_H__

#ifdef __cplusplus
extern "C" {
#endif


#define SS_RNG_TX                    1
#define SS_RNG_RX                    0

/* Ring Size Defines, powers of 2 only  */
/*#define SS_RNG_ICPU_TO_DLPDCP_SIZE      128 */
#define SS_RNG_ICPU_TO_DLPDCP_SIZE      512
 /* ccpu00143253: Changing SS_RNG_DLPDCP_TO_DLRLC_SIZE from 128 to 512, as the 
  * forwarded data packet drop observed during Handover */
#define SS_RNG_DLPDCP_TO_DLRLC_SIZE     1024
/*#define SS_RNG_L2_RT_TO_FREE_MGR_SIZE   512 */ 
/*#define SS_RNG_L2_NRT_TO_FREE_MGR_SIZE  640 */
/* Increasing from 512 to 1024
   Increasing from 1024 to 2048 to handle free after re-est */ 
#define SS_RNG_L2_RT_TO_FREE_MGR_SIZE   2048
#define SS_RNG_L2_NRT_TO_FREE_MGR_SIZE  2048 
#define SS_RNG_L2_DLRLC_TO_FREE_MGR_SIZE  2048 
#define SS_RNG_PRC_L1D_TO_CL_SIZE       32
#define SS_RNG_PRC_FREE_TO_CL_SIZE      256
#define SS_RNG_ICPU_TO_DAM_SIZE         1024
#define SS_RNG_PDCP_TO_CIPH_SIZE        2048
#define SS_RNG_CIPH_TO_PDCP_SIZE        1024
#define SS_RNG_ULMAC_TO_ULRLC_SIZE      128
#define SS_RNG_DL_SMSG_REUSE_SIZE       384
#ifdef BRDCM_61755
#define SS_RNG_DLRLC_TO_DLMAC_SIZE      512
#define SS_RNG_BUF_MAC_HARQ_SIZE        256
#endif
/* Ring Element Size Defines */
#define SS_RNG_BUF_ELEM           sizeof(SsRngBufElem)
#ifdef BRDCM_61755
#define BC_BATCH_MGR_MAX_BKT 6 
#else
#define BC_BATCH_MGR_MAX_BKT 5 
#endif

extern U32 ssRngBufStatus;

/* Ring Buffer Structure */
typedef struct
{
   U32 size;    /* Number of elements in a ring */
   U32 read;    /* Read Index incremented by Deque operation */
   U32 write;   /* Write index incremented by Enque operation */
   U32 type;    /* sizeof user specified ring element structure */
   Void* elem;  /* pointer to the allocated ring Elements */
}SsRngBuf;

/* Ring Cfg Table */
typedef struct
{
   U32 rngSize;
   U32 elemSize;
} SsRngCfg;

/* Global Ring Buffer Info structure */
typedef struct
{
   SsRngBuf* r_addr;   /* Address of allocated ring */
   U32 txEnt;          /* Tx Entity id */
   U32 rxEnt;          /* Rx Entity id */
   U32 n_write;        /* Number of Enque operations */
   U32 n_read;         /* Number of Deque operations */
   U32 nReadFail;      /* Number of Deque failures due to ring empty */
   U32 nWriteFail;     /* Number of Enque failures due to ring full */
   U32 rngState;       /* Ring Buffer State */
   U32 pktDrop;        /* Number of pkts dropped due to  buffer full */
   U32 nPktProc;       /* Debug counter for pkts processed per tti */
   U32 pktRate;        /* Debug counter for icpu pkt rate */
} SsRngBufTbl;

/* Ring Buffer Id Enum */
typedef enum
{
  SS_RNG_BUF_DEBUG_COUNTER,
  SS_RNG_BUF_ICPU_TO_DLPDCP,
  SS_RNG_BUF_DLPDCP_TO_DLRLC,
  SS_RNG_BUF_L2_RT_TO_FREE_MGR,
  SS_RNG_BUF_L2_NRT_TO_FREE_MGR,
  SS_RNG_BUF_PRC_L1D_TO_CL,
  SS_RNG_BUF_PRC_FREE_TO_CL,
  SS_RNG_BUF_ICPU_TO_DAM,
#ifdef BRDCM_61755
  SS_RNG_BUF_L2_NRT_DLRLC_TO_FREE_MGR,
#endif
  SS_RNG_BUF_ICPU_BATCH_START,
  SS_RNG_BUF_ICPU_BATCH_END = SS_RNG_BUF_ICPU_BATCH_START + BC_BATCH_MGR_MAX_BKT,
#ifdef CIPH_BATCH_PROC
  SS_RNG_BUF_DLPDCP_TO_CIPH,
  SS_RNG_BUF_CIPH_TO_DLPDCP,
  SS_RNG_BUF_ULPDCP_TO_CIPH,
  SS_RNG_BUF_CIPH_TO_ULPDCP,
#endif
  SS_RNG_BUF_ULMAC_TO_ULRLC,
  SS_RNG_BUF_DL_SMSG_REUSE,
  SS_RNG_BUF_DLRLC_TO_DLMAC,
  SS_RNG_BUF_MAC_HARQ,
  SS_RNG_BUF_MAX
} SsRngBufId;

/* Ring Buffer User Entity Enum */
typedef enum
{
   SS_RBUF_ENT_ICPU,
   SS_RBUF_ENT_DLPDCP,
   SS_RBUF_ENT_DLRLC,
   SS_RBUF_ENT_L2_RT,
   SS_RBUF_ENT_L2_NRT,
   SS_RBUF_ENT_FREE_MGR,
   SS_RBUF_ENT_CL,
   SS_RBUF_ENT_PRC_L1D,
   SS_RBUF_ENT_PRC_FREE,
   SS_RBUF_ENT_DAM
#ifdef CIPH_BATCH_PROC
   ,
   SS_RBUF_ENT_DLCIPH,
   SS_RBUF_ENT_ULPDCP,
   SS_RBUF_ENT_ULCIPH
#endif
   ,SS_RBUF_ENT_ULMAC,
   SS_RBUF_ENT_ULRLC

}SsRngUserEnt;
/* Ring Buffer State Enum   */

typedef enum
{
   SS_RNG_DESTROYED,
   SS_RNG_CREATED,
   SS_RNG_TX_ATTACHED,
   SS_RNG_RX_ATTACHED,
   SS_RNG_READY,
   SS_RNG_EMPTY,
   SS_RNG_FULL
}SsRngBufState;

/* User defined Ring Element structures */
typedef struct
{
  Buffer* mBuf;
} SsRngBufElem;

#ifdef __cplusplus
}
#endif

#endif

