

/********************************************************************20**
  
        Name:    Common LTE
    
        Type:    C include file
  
        Desc:    This file Contains the Data structures for Common LTE
 
        File:    cm_lte.h

        Sid:      cm_lte.h@@/main/2 - Fri Nov 13 14:09:17 2009
  
        Prg:     chakrapani
  
*********************************************************************21*/

#ifndef __CM_LTE_H__
#define __CM_LTE_H__

#ifdef __cplusplus
EXTERN "C" {
#endif  /*__cplusplus*/

/** @file cm_lte.h
    @brief CM_LTE Interface File (cm_lte.h)
*/
 
#define CM_LTE_MAX_LOGCH_PER_RB 2   /*!< Maximum Logical Channel per RB */

/* Mode of RLC entity */
#define CM_LTE_MODE_TM        1     /*!< TM mode */
#define CM_LTE_MODE_UM        2     /*!< UM mode */
#define CM_LTE_MODE_AM        3     /*!< AM mode */

/* Logical Channel Type */
#define CM_LTE_LCH_BCCH      1      /*!< BCCH Logical Channel */
#define CM_LTE_LCH_PCCH      2      /*!< PCCH Logical Channel */
#define CM_LTE_LCH_CCCH      3      /*!< CCCH Logical Channel */
#define CM_LTE_LCH_DTCH      4      /*!< DTCH Logical Channel */
#define CM_LTE_LCH_DCCH      5      /*!< DCCH Logical Channel */

/* Transport Channel Type */
#define CM_LTE_TRCH_BCH      1      /*!< BCH Transport Channel */ 
#define CM_LTE_TRCH_PCH      2      /*!< PCH Transport Channel */
#define CM_LTE_TRCH_DL_SCH   3      /*!< DL-SCH Transport Channel */
#define CM_LTE_TRCH_RACH     4      /*!< RACH Transport Channel */
#define CM_LTE_TRCH_UL_SCH   5      /*!< UL-SCH Transport Channel */

#define CM_LTE_DIR_UL        1      /*!< Uplink Direction */
#define CM_LTE_DIR_DL        2      /*!< Downlink Direction */
#define CM_LTE_DIR_DL_UL     3      /*!< Bi-Directional */


#define CM_LTE_SRB           0      /*!< Signalling Radio Bearer */
#define CM_LTE_DRB           1      /*!< Data Radio Bearer */
#define CM_MAX_UE_CAT_SUPP   8      /*!< CA dev changes*/
#define CM_LTE_MAX_CELLS     8      /*!< Max Number of Cells. One primary
                                         seven secondary cells */    
  
#define CM_MAX_CPU_CORES     10     /*!< Maximum number of cores */
#define CM_L2_CPU_UTIL          0     /*!<  Get L2 CPU Utilization */
#define CM_L3_CPU_UTIL          1     /*!<  Get L3 CPU Utilization */
#define CM_L2_MEM_UTIL_AREAIDX 0     /*!< Get L2 MEM utilization */
#define CM_L3_MEM_UTIL_AREAIDX 1     /*!< Get L3 MEM utilization */
#define CM_MEM_CPU_UITL_INFO_TMR_VAL 1000 /*!< timer value */
#ifdef TENB_T2K3K_SPECIFIC_CHANGES
#define CM_NUM_L2_CORES     1     /*!< number of L2 cores */
#define CM_NUM_L3_CORES     1     /*!< number of L3 cores */
#else
#define CM_NUM_L2_CORES     4     /*!< number of L2 cores */
#define CM_NUM_L3_CORES     1     /*!< number of L3 cores */
#endif   
#ifdef TENB_TTI_PERF
/*#define TTI_THRESHOLD_VALUE 800*/

#define displayTtiCounters(cellId) \
RLOG_ARG4(L_ALWAYS,DBG_CELLID, (cellId),"avgTtiProcessingTime = [%d] maxTtiProcessingTime = [%d] ttiThresholdExceedCount = [%d] ttiStretchCount = [%d]",(ttiProc.totTtiProcessingTime/ttiProc.numOfTti),ttiProc.maxTtiProcessingTime,ttiProc.ttiThresholdExceedCount,ttiProc.ttiStretchCount) 
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __CM_LTE_H__ */

/********************************************************************30**
  
         End of file:     cm_lte.h@@/main/2 - Fri Nov 13 14:09:17 2009
  
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
----------- -------- ---- -----------------------------------------------
/main/1      ---      cp   1. initial release.
*********************************************************************91*/
