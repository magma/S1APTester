

/********************************************************************20**
  
        Name:    Common LTE
    
        Type:    C include file
  
        Desc:    This file Contains the Data structures for Common LTE
 
        File:    cm_lte_rrm.x

        Sid:      cm_lte_rrm.x@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/T2K_MergeTemp_BR/1 - Mon Sep  2 16:44:24 2013
  
        Prg:    jbm 
  
*********************************************************************21*/
#ifndef __CM_LTE_RRM_X__
#define __CM_LTE_RRM_X__

#ifdef __cplusplus
EXTERN "C" {
#endif  /*__cplusplus*/

#define DUMMY 


typedef enum cmRrmDsrTransMax
{
   DSR_TRANS_N4,
   DSR_TRANS_N8,
   DSR_TRANS_N16,
   DSR_TRANS_N32,
   DSR_TRANS_N64,
   DSR_TRANS_MAX
}CmRrmDsrTransMax;



/** @brief This structure 
 - U16  usLongDrxCycle   This parameter specifies the Long DRX cycle
 - U16  usDrxStartOffst  This parameter specifies the DRX Start offset
 */
typedef struct cmRrmDrxLongCycleOffst
{
   U16      usLongDrxCycle;
   U16      usDrxStartOffst;
} CM_PACK_STRUCT CmRrmDrxLongCycleOffst;

/** @brief This structure 
 - Bool    bPres        This paramter indicates the presence of short
                       DRX
 - U16     usShortDrxCycle This parameter specifies the short DRX cycle
 - U8      bDrxShortCycleTmr This parameter specifies the short DRX
                            timer value
 */
typedef struct cmRrmDrxShortDrx
{
   Bool    bPres;             /*!< Short cycle is configured or not */
   U16     usShortDrxCycle;    /*!< DRX Short Cycle value in sub-frames*/
   U8      bDrxShortCycleTmr; /*!< Value in multiples of Short DRX Cycles*/
} CM_PACK_STRUCT CmRrmDrxShortDrx;

/** @brief This structure holds the Drx Configuration
 - Bool                    bIsDrxEnabled       Specifies whethere DRX is enabled or not
 - TknS32                  stCqiMask            Specifies the CQI mask
 - U8                      bDrxOnDurTmr        Specifies the Duration of Drx On timer
 - U16                     usDrxInactvTmr       Specifies the Drx Inactivity timer
 - U8                      bDrxRetxTmr         Specifies the DRX Retransmission timer
 - RrmWrDrxLongCycleOffst  stDrxLongCycleOffst  Specifies the long cycle Offset
 - RrmWrDrxShortDrx        stDrxShortDrx        Specifies the short cycle information
 */
typedef struct cmRrmDrxCfg           /* sachin */
{
   Bool                    bIsDrxEnabled;
   TknS32                  stCqiMask;
   U8                      bDrxOnDurTmr;
   U16                     usDrxInactvTmr;
   U8                      bDrxRetxTmr;
   CmRrmDrxLongCycleOffst    stDrxLongCycleOffst;
   CmRrmDrxShortDrx          stDrxShortDrx;
} CM_PACK_STRUCT CmRrmDrxCfg;   

typedef struct cmRrmCellDrxCfg
{
   Bool                    bIsGbrDrxDis;
   Bool                    bIsDrxEnabled;
   U8                      bDrxRetxTmr;  
   U16                     usDrxInactvTmr;
   U16                     usLongDrxCycleGbr;
   U16                     usLongDrxCycleNonGbr;
} CM_PACK_STRUCT CmRrmCellDrxCfg;                       

/** @enum CmRrmAcBarringTime
 *
 * Access class baring time value in seconds. This should be same as
 * ac-BarringTime (SystemInformationBlockType2 IE) defined in TS 36.331.
 *
 * - RM_ACB_TIME_S4        0
 * - RM_ACB_TIME_S8        1
 * - RM_ACB_TIME_S16       2
 * - RM_ACB_TIME_S32       3
 * - RM_ACB_TIME_S64       4
 * - RM_ACB_TIME_S128      5
 * - RM_ACB_TIME_S256      6
 * - RM_ACB_TIME_S512      7
 */
typedef enum cmRrmAcBarringTime
{
	RM_ACB_TIME_S4,
	RM_ACB_TIME_S8,
	RM_ACB_TIME_S16,
	RM_ACB_TIME_S32,
	RM_ACB_TIME_S64,
	RM_ACB_TIME_S128,
	RM_ACB_TIME_S256,
	RM_ACB_TIME_S512
} CmRrmAcBarringTime;

/** @enum CmRrmAcBarringFactor
 *
 * Access class baring factor. This should be same as
 * ac-BarringFactor (SystemInformationBlockType2 IE) defined in TS 36.331.
 *
 * - RM_ACB_FACTOR_P00  0 
 * - RM_ACB_FACTOR_P05  1
 * - RM_ACB_FACTOR_P10  2
 * - RM_ACB_FACTOR_P15  3
 * - RM_ACB_FACTOR_P20  4
 * - RM_ACB_FACTOR_P25  5
 * - RM_ACB_FACTOR_P30  6
 * - RM_ACB_FACTOR_P40  7
 * - RM_ACB_FACTOR_P50  8 
 * - RM_ACB_FACTOR_P60  9
 * - RM_ACB_FACTOR_P70  10
 * - RM_ACB_FACTOR_P75  11
 * - RM_ACB_FACTOR_P80  12
 * - RM_ACB_FACTOR_P85  13
 * - RM_ACB_FACTOR_P90  14
 * - RM_ACB_FACTOR_P95  15
 */
typedef enum cmRrmAcBarringFactor
{
 RM_ACB_FACTOR_P00,
 RM_ACB_FACTOR_P05,
 RM_ACB_FACTOR_P10,
 RM_ACB_FACTOR_P15,
 RM_ACB_FACTOR_P20,
 RM_ACB_FACTOR_P25,
 RM_ACB_FACTOR_P30,
 RM_ACB_FACTOR_P40,
 RM_ACB_FACTOR_P50,
 RM_ACB_FACTOR_P60,
 RM_ACB_FACTOR_P70,
 RM_ACB_FACTOR_P75,
 RM_ACB_FACTOR_P80,
 RM_ACB_FACTOR_P85,
 RM_ACB_FACTOR_P90,
 RM_ACB_FACTOR_P95,
 RM_ACB_FACTOR_NA
} CmRrmAcBarringFactor;


/**
 * @brief  Structure to hold the Access class barring information.
 * 
 * @details
 * - enAcbTime : Access class barring time.
 * - enAcbFactor : Access class barring factor.
 * - bAcbForSpac : Access class barring for special access class
 *                 and The first/leftmost bit is for AC-11,
 *                 the second bit is for AC-12 and so on.
 */
typedef struct cmRrmAcb
{
	CmRrmAcBarringTime     enAcbTime;
   CmRrmAcBarringFactor   enAcbFactor;
   U8                     bAcbForSpac;
} CM_PACK_STRUCT CmRrmAcb;

typedef struct cmRrmAcbInfo
{
   CmRrmAcb                stAcBarringMoData;    /*!< AC barring Parameters For MO Data*/
   CmRrmAcb                stAcBarringMoSig;     /*!< AC barring Parameters For MO Signal*/
   U8                      bAcBarringEmergency;  /*!< ac-BarringForEmergency flag which
                                                      needs to be enabled or disabled in
                                                      SIB2 */
   U8                      bIsacBarringMoSig;    /* Set ac-BarringForMO-Signalling
                                                    in SIB2 if this flag is true */
   U8                      bIsacBarringMoData;   /* Set ac-BarringForMO-Data
                                                    in SIB2 if this flag is true */
} CM_PACK_STRUCT CmRrmAcbInfo;

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __CM_LTE_RRM_X__ */


/********************************************************************30**
  
         End of file:     cm_lte_rrm.x@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/T2K_MergeTemp_BR/1 - Mon Sep  2 16:44:24 2013
  
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
