


/**********************************************************************
 
    Name:  
 
    Type:  
 
    Desc:  
 
    File:  cm_tenb_stats.x 
 
    Sid:      cm_tenb_stats.x@@/main/tenb_5.0_RIB/3 - Tue Oct 27 14:21:20 2015
 
    Prg:   sm
 
**********************************************************************/
 
/** @file cm_tenb_stats.x
@brief This file contains .
*/

/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*
*/
#ifdef TENB_STATS
 
#include "cm_tenb_stats.h"
#include "l2_tenb_stats.h"

#ifndef __TENBSTATSINFX__
#define __TENBSTATSINFX__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct tsInfL2CellStats
{
   U32   cellId;
   struct schCellStats{ 
      U32   msg4Fail;
      U32   msg3Fail;
      U32   dlSumCw0Cqi;
      U32   dlNumCw0Cqi;
      U32   dlSumCw1Cqi;
      U32   dlNumCw1Cqi;
      U32   dlSumCw0iTbs;
      U32   dlNumCw0iTbs;
      U32   dlSumCw1iTbs;
      U32   dlNumCw1iTbs;
      U32   riCnt[4]; /* Rank = 1..4 */
      U32   dlNack[2][4];
      U32   dlAckNack[2][4]; /* [CW_CNT][RV_CNT] */
      U32   dlDtx[2][4];
      U32   ulNack[4];
      U32   ulAckNack[4];    /* [RV_CNT] */
      U32   ulDtx[4];
      U32   dlPrbUsage[10]; /* dlPrbUsage[0] to have overall PRB usage */
      U32   ulPrbUsage[10]; /* dlPrbUsage[0] to have overall PRB usage */
      U32   dlPdbRatio[10];
      U32   avgTtiProcTime; /* In us */
      U32   cntTtiProcTime1000; /* Count of instances where TTI proc time was
      greater than 1000us */
      U32   cntTtiProcTime900; /* Count of instances where TTI proc time was
      greater than 900us and less than 1000us */
      U32   cntTtiProcTime800;
      U32   cntTtiProcTime700;
      U32   cntTtiProcTime600;
      U32   cntTtiProcTime500;
      U32   ulSumCqi;
      U32   ulNumCqi;
      U32   ulSumiTbs;
      U32   ulNumiTbs;
      U32   dlTtlTpt;
      U32   ulTtlTpt;
   }sch;
   struct rlcCellStats{ 
      U32   maxRlcSrbRetxFail;
      U32   maxRlcDrbRetxFail;
      U32   reOdrTmrExp;
   }rlc;
}TSInfL2CellStats;

typedef struct tsInfL2UeStats
{
   U32 rnti;
   struct nonPersistentUeStats{
      struct schUeStats{
         U32 dlTxOccns;
         U32 dlRetxOccns;
         U32 dlPrbUsg;
         U32 dlNackCnt[2]; /* [CW_CNT] */
         U32 dlAckNackCnt[2]; /* [CW_CNT] */
         U32 dlDtxCnt[2]; /* [CW_CNT] */
         U32 dlSumCw0Cqi;
         U32 dlNumCw0Cqi;
         U32 dlSumCw1Cqi;
         U32 dlNumCw1Cqi;
         U32 dlSumCw0iTbs;
         U32 dlNumCw0iTbs;
         U32 dlSumCw1iTbs;
         U32 dlNumCw1iTbs;
         U32 cqiDropCnt;
         U32 dlPdbLvl[5]; /* PDB Levels */ 
         U32 riCnt[4]; /* Rank = 1..4 */
         U32 dlBo;
         U32 dlTpt;
         U32 ulTxOccns;
         U32 ulRetxOccns;
         U32 ulPrbUsg;
         U32 ulAckNackCnt;
         U32 ulNackCnt;
         U32 ulDtxCnt;
         U32 ulSumCqi;
         U32 ulNumCqi;
         U32 ulSumiTbs;
         U32 ulNumiTbs;
         U32 ulTpt;
      }sch[L2_STATS_MAX_CELLS];
      struct pdcpUeStats{
         U32 dlPdcpDropCnt;
         U32 dlPdcpAckWaitDropCnt;
         U32 dlFlowCtrlDropCnt;
      }pdcp;
      struct rlcUeStats{
         U32 ulReOdrTmrExpCnt;
         U32 dlMaxPktsInSduQ;
         U32 dlMaxWindowSz;
      }rlc;
   }nonPersistent;
   struct persistentUeStats{
      U32 activatedSCells;
      U32 numActivation;
      U32 numDeactivation;
   }persistent;
}TSInfL2UeStats;

typedef struct tsInfStatsCb
{
   Bool initDone;
   Bool sockSend;
   Bool fileSend;
   Bool consPrint;
   U32  statsPer;
   U32  sockPort;
   Bool startSockSend;
   U8   cmdForFileStats;
   char fileName[100];
   FILE *fptr;
   U32  enbIp;
}TSInfStatsCb;

typedef Void (*TSInfL2UeStatsInd) ARGS((
 Pst *, 
 SuId , 
 TSInfL2UeStats *
));
EXTERN Void TSInfHdlL2UeStatsInd ARGS((
 Pst               *pst,
 SuId              suId,
 TSInfL2UeStats     *stats 
));
EXTERN Void TSInfUnpkL2UeStats ARGS((
 TSInfL2UeStatsInd   func,
 Pst                *pst,
 Buffer             *mBuf
));
typedef Void (*TSInfL2CellStatsInd) ARGS((
 Pst *, 
 SuId , 
 TSInfL2CellStats *
));
EXTERN Void TSInfHdlL2CellStatsInd ARGS((
 Pst                 *pst,
 SuId                suId,
 TSInfL2CellStats    *stats 
));
EXTERN Void TSInfUnpkL2CellStats ARGS((
 TSInfL2CellStatsInd   func,
 Pst                  *pst,
 Buffer               *mBuf
));
EXTERN Void TSInfPkSndL2UeStats ARGS((
 Pst               *pst,
 SuId              suId,
 TSInfL2UeStats     *stats 
));
EXTERN Void TSInfPkSndL2CellStats ARGS((
 Pst                 *pst,
 SuId                suId,
 TSInfL2CellStats     *stats 
));
EXTERN Void TSInfTrigStats ARGS((
 Region    region,
 Pool      pool
));

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __TENBSTATSINFX__ */
#endif /* TENB_STATS */

/**********************************************************************
         End of file:     cm_tenb_stats.x@@/main/tenb_5.0_RIB/3 - Tue Oct 27 14:21:20 2015
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------

*********************************************************************91*/
