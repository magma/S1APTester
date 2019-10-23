

/**********************************************************************
 
    Name:   LTE RRC layer
 
    Type:   C include file
 
    Desc:   Defines required by LTE RRC user.
 
    File:   nhu.x
 
    Sid:      nhu.x@@/main/6 - Thu Jan  5 15:32:14 2012
 
    Prg:    dsahoo
 
**********************************************************************/
/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*     1000369       LTE RRC
*
*/

/** @defgroup nhu_grp NHU Interface Module
 *  @{
 */


#ifndef __NHUX__
#define __NHUX__


#ifdef __cplusplus
extern "C" {
#endif

/* include files */
#include "nhu_asn.x"         
#include "cm_mblk.x"         
#include "cm_lte.x"        
#include "cm_mblk.x" 
#include "nhu_3gasn.x"

/**
 * @brief NhuRbId 
   Radio Bearer Id.
*/
typedef struct nhuRbId
{
   U8     rbId;
   U8     rbTyp; /* Uses cm_lte defines: CM_LTE_SRB(0), CM_LTE_DRB(1) */
}NhuRbId;

/**
 * @brief NhuPdcpId
   PDCP Entity Id. 
*/
typedef U8 NhuPdcpId;      

/**
 * @brief NhuCrnti
   Crnti. Required to create an UE context. 
*/
typedef U16 NhuCrnti;      

/**
 * @brief NhuCellId
   CellId. Required to create the Cell Cb. RRC user must map the actual 
CellId (bit string of size 28) into the U16.
*/
typedef U16 NhuCellId;     

/**
 * @enum nhuRbType
   Radio Bearer type whether common or dedicated. 
*/
typedef enum nhuRbType     
{
   NHU_RB_COMMON,    
   NHU_RB_DEDICATED  
} NhuRbType;

/**
 * @enum nhuTargetRatTyp
   This enum contains the target RAT type information.
*/
typedef enum nhuTargetRatTyp
{
   NHU_RAT_TGT_UTRA,
   NHU_RAT_TGT_GERAN,
   NHU_RAT_TGT_CDMA2K_1XRTT,
   NHU_RAT_TGT_CDMA2K_HRPD
} NhuTargetRatTyp;

/**
 * @enum nhuSIWindowLen
   This enum contains the SI window length in milli seconds required for 
scheduling purpose.
*/
typedef enum nhuSIWindowLen
{
   NHU_SI_WINDOW_LEN_MS1,
   NHU_SI_WINDOW_LEN_MS2,
   NHU_SI_WINDOW_LEN_MS5,
   NHU_SI_WINDOW_LEN_MS10,
   NHU_SI_WINDOW_LEN_MS15,
   NHU_SI_WINDOW_LEN_MS20,
   NHU_SI_WINDOW_LEN_MS40
} NhuSIWindowLen;

/**
 * @enum nhuSIPeriodicity
   This enum contains the periodicity of the SI messages in Radio Frames.
*/
typedef enum nhuSIPeriodicity
{
   NHU_SI_PERIOD_RF8,
   NHU_SI_PERIOD_RF16,
   NHU_SI_PERIOD_RF32,
   NHU_SI_PERIOD_RF64,
   NHU_SI_PERIOD_RF128,
   NHU_SI_PERIOD_RF256,
   NHU_SI_PERIOD_RF512
} NhuSIPeriodicity;

/**
 * @enum nhuAntPortCnt
This enum contains the enumeration value for the number of Antenna ports.
*/
typedef enum nhuAntPortCnt
{
   NHU_ANT_PORT_CNT1 = 1,
   NHU_ANT_PORT_CNT2 = 2,
   NHU_ANT_PORT_CNT4 = 4
} NhuAntPortCnt;

/**
 * @enum nhuAntTxMode
   This enum contains the enumeration value for the Antenna Tx mode.
*/
typedef enum nhuAntTxMode
{
   NHU_ANT_TM1 = 1,
   NHU_ANT_TM2,
   NHU_ANT_TM3,
   NHU_ANT_TM4,
   NHU_ANT_TM5,
   NHU_ANT_TM6,
   NHU_ANT_TM7
} NhuAntTxMode;

/**
 * @enum nhuAprdCqiRptMode
   This enum contains the enumeration value for the Aperiodic CQI Reporting mode.
*/
typedef enum nhuAprdCqiRptMode
{
   NHU_CQI_RPT_MODE_APERD_12,
   NHU_CQI_RPT_MODE_APERD_20,
   NHU_CQI_RPT_MODE_APERD_22,
   NHU_CQI_RPT_MODE_APERD_30,
   NHU_CQI_RPT_MODE_APERD_31
} NhuAprdCqiRptMode;

/**
 * @enum nhuPrdCqiRptMode
   This enum contains the enumeration value for the Periodic CQI Reporting mode.
*/
typedef enum nhuPrdCqiRptMode
{
   NHU_CQI_RPT_MODE_PERD_10, 
   NHU_CQI_RPT_MODE_PERD_11, 
   NHU_CQI_RPT_MODE_PERD_20, 
   NHU_CQI_RPT_MODE_PERD_21 
} NhuPrdCqiRptMode;


/**
 * @enum nhuCqiRptPeriodicity
   This enum contains the enumeration value for the CQI Reporting Periodic Periodicity.
*/
typedef enum nhuCqiRptPeriodicity
{
   NHU_CQI_PERIODICITY_MS2 = 2,
   NHU_CQI_PERIODICITY_MS5 = 5,
   NHU_CQI_PERIODICITY_MS10 = 10,
   NHU_CQI_PERIODICITY_MS20 = 20,
   NHU_CQI_PERIODICITY_MS32 = 32,
   NHU_CQI_PERIODICITY_MS40 = 40,
   NHU_CQI_PERIODICITY_MS64 = 64,
   NHU_CQI_PERIODICITY_MS80 = 80,
   NHU_CQI_PERIODICITY_MS128 = 128,
   NHU_CQI_PERIODICITY_MS160 = 160,
   NHU_CQI_PERIODICITY_MS256 = 256,
   NHU_CQI_PERIODICITY_MSOFF
} NhuCqiRptPeriodicity;

/**
 * @enum nhuLogChPbr
   This enum contains the enumeration value for the Logical Channel Prioritized Bit Rate.
*/
typedef enum nhuLogChPbr
{
   NHU_LOGCH_PBR_KB0 = 0,
   NHU_LOGCH_PBR_KB8 = 8,
   NHU_LOGCH_PBR_KB16 = 16 ,
   NHU_LOGCH_PBR_KB32 = 32,
   NHU_LOGCH_PBR_KB64 = 64,
   NHU_LOGCH_PBR_KB128 = 128,
   NHU_LOGCH_PBR_KB256 = 256,
   NHU_LOGCH_PBR_INF
} NhuLogChPbr;

/**
 * @enum nhuDlSemiPerSchedIntvl
   This enum conatains the enumeration value for the Downlink Semi-persistent Scheduling Interval.
*/
typedef enum nhuDlSemiPerSchedIntvl
{
   NHU_DL_SEMIP_SCHED_INT_SF10,
   NHU_DL_SEMIP_SCHED_INT_SF20,
   NHU_DL_SEMIP_SCHED_INT_SF32,
   NHU_DL_SEMIP_SCHED_INT_SF40,
   NHU_DL_SEMIP_SCHED_INT_SF64,
   NHU_DL_SEMIP_SCHED_INT_SF80,
   NHU_DL_SEMIP_SCHED_INT_SF128,
   NHU_DL_SEMIP_SCHED_INT_SF160,
   NHU_DL_SEMIP_SCHED_INT_SF320,
   NHU_DL_SEMIP_SCHED_INT_SF640
} NhuDlSemiPerSchedIntvl;

/**
 * @enum nhuUlSemiPerSchedIntvl
   This enum contains the enumeration value for the Uplink Semi-persistent Scheduling Interval.
*/
typedef enum nhuUlSemiPerSchedIntvl
{
   NHU_UL_SEMIP_SCHED_INT_SF10,
   NHU_UL_SEMIP_SCHED_INT_SF20,
   NHU_UL_SEMIP_SCHED_INT_SF32,
   NHU_UL_SEMIP_SCHED_INT_SF40,
   NHU_UL_SEMIP_SCHED_INT_SF64,
   NHU_UL_SEMIP_SCHED_INT_SF80,
   NHU_UL_SEMIP_SCHED_INT_SF128,
   NHU_UL_SEMIP_SCHED_INT_SF160,
   NHU_UL_SEMIP_SCHED_INT_SF320,
   NHU_UL_SEMIP_SCHED_INT_SF640
} NhuUlSemiPerSchedIntvl;

/**
 * @enum nhuMaxHarqTx
   This enum contains the enumeration value for the maximum HARQ TX.
*/
typedef enum nhuMaxHarqTx
{
   NHU_MAX_HARQ_TX_N1 = 1,
   NHU_MAX_HARQ_TX_N2 = 2,
   NHU_MAX_HARQ_TX_N3 = 3,
   NHU_MAX_HARQ_TX_N4 = 4,
   NHU_MAX_HARQ_TX_N5 = 5,
   NHU_MAX_HARQ_TX_N6 = 6,
   NHU_MAX_HARQ_TX_N7 = 7,
   NHU_MAX_HARQ_TX_N8 = 8,
   NHU_MAX_HARQ_TX_N10 = 10,
   NHU_MAX_HARQ_TX_N12 = 12,
   NHU_MAX_HARQ_TX_N16 = 16,
   NHU_MAX_HARQ_TX_N20 = 20,
   NHU_MAX_HARQ_TX_N24 = 24,
   NHU_MAX_HARQ_TX_N28 = 28
} NhuMaxHarqTx;

/**
 * @enum nhuPrdPHRTmr
   This enum contains the enumeration values for the PDCP Periodic PHR timer.
*/
typedef enum nhuPrdPHRTmr
{
   NHU_PRD_PHR_TMR_SF10,
   NHU_PRD_PHR_TMR_SF20,
   NHU_PRD_PHR_TMR_SF50,
   NHU_PRD_PHR_TMR_SF100,
   NHU_PRD_PHR_TMR_SF200,
   NHU_PRD_PHR_TMR_SF1000,
   NHU_PRD_PHR_TMR_INF
} NhuPrdPHRTmr;

/**
 * @enum nhuProhPHRTmr
   This enum contains the enumeration values for the PDCP Prohibit PHR timer.
*/
typedef enum nhuProhPHRTmr
{
   NHU_PROH_PHR_TMR_SF10,
   NHU_PROH_PHR_TMR_SF100,
   NHU_PROH_PHR_TMR_SF200,
   NHU_PROH_PHR_TMR_SF1000
} NhuProhPHRTmr;

/**
 * @enum nhuPdcpDiscardTmr
   This enum contains the enumeration values for the PDCP DISCARD timer. 
*/
typedef enum nhuPdcpDiscardTmr
{
   NHU_PDCP_DISCARD_TMR_MS50 = 50,
   NHU_PDCP_DISCARD_TMR_MS100 = 100,
   NHU_PDCP_DISCARD_TMR_MS150 = 150,
   NHU_PDCP_DISCARD_TMR_MS300 = 300,
   NHU_PDCP_DISCARD_TMR_MS500 = 500,
   NHU_PDCP_DISCARD_TMR_MS750 = 750,
   NHU_PDCP_DISCARD_TMR_MS1500 = 1500,
   NHU_PDCP_DISCARD_TMR_MSINF = -1
} NhuPdcpDiscardTmr;

/**
 * @enum nhuPdcpFlushTmr
   This enum contains the enumeration values for the PDCP Flush timer.
*/
typedef enum nhuPdcpFlushTmr
{
   NHU_PDCP_FLUSH_TMR_MS10,
   NHU_PDCP_FLUSH_TMR_MS50,
   NHU_PDCP_FLUSH_TMR_MS100,
   NHU_PDCP_FLUSH_TMR_MS150,
   NHU_PDCP_FLUSH_TMR_MS200,
   NHU_PDCP_FLUSH_TMR_MS250,
   NHU_PDCP_FLUSH_TMR_MS500
} NhuPdcpFlushTmr;

/**
 * @enum nhuPdcpSnSize
   This enum contains the enumeration values for the PDCP SN size.
*/
typedef enum nhuPdcpSnSize
{
   NHU_PDCP_SN_SIZE_7BITS = 7,
   NHU_PDCP_SN_SIZE_12BITS = 12,
   NHU_PDCP_SN_SIZE_15BITS = 15
} NhuPdcpSnSize;

/**
 * @enum nhuPucchDeltaShift
   This enum contains the enumeration values for the PUCCH Configuration Delta Shift.
*/
typedef enum nhuPucchDeltaShift
{
   NHU_PUCCH_DS1 = 1,
   NHU_PUCCH_DS2,
   NHU_PUCCH_DS3
} NhuPucchDeltaShift;

/**
 * @enum nhuMaxRetxThres
   This enum contains the enumeration values for the Re-transmission threshold value 
of a radio bearer.
RRC maps these enumerations into proper values for configuration at the lower layers.
*/
typedef enum nhuMaxRetxThres
{
   NHU_MAX_RETX_THRES_T1 = 1,
   NHU_MAX_RETX_THRES_T2 = 2,
   NHU_MAX_RETX_THRES_T3 = 3,
   NHU_MAX_RETX_THRES_T4 = 4,
   NHU_MAX_RETX_THRES_T6 = 6,
   NHU_MAX_RETX_THRES_T8 = 8,
   NHU_MAX_RETX_THRES_T16 = 16,
   NHU_MAX_RETX_THRES_T32 = 32
} NhuMaxRetxThres;

/**
 * @enum nhuTPollReTx
 This enum contains the enumeration values for the Poll Re-transmission of a 
radio bearer.
RRC maps these enumerations into proper values for configuration at the lower 
layers.
*/
typedef enum nhuTPollReTx
{
   NHU_TPOLL_RETX_MS5 = 5,
   NHU_TPOLL_RETX_MS10 = 10,
   NHU_TPOLL_RETX_MS15 = 15,
   NHU_TPOLL_RETX_MS20 = 20,
   NHU_TPOLL_RETX_MS25 = 25,
   NHU_TPOLL_RETX_MS30 = 30,
   NHU_TPOLL_RETX_MS35 = 35,
   NHU_TPOLL_RETX_MS40 = 40,
   NHU_TPOLL_RETX_MS45 = 45,
   NHU_TPOLL_RETX_MS50 = 50,
   NHU_TPOLL_RETX_MS55 = 55,
   NHU_TPOLL_RETX_MS60 = 60,
   NHU_TPOLL_RETX_MS65 = 65,
   NHU_TPOLL_RETX_MS70 = 70,
   NHU_TPOLL_RETX_MS75 = 75,
   NHU_TPOLL_RETX_MS80 = 80,
   NHU_TPOLL_RETX_MS85 = 85,
   NHU_TPOLL_RETX_MS90 = 90,
   NHU_TPOLL_RETX_MS95 = 95,
   NHU_TPOLL_RETX_MS100 = 100,
   NHU_TPOLL_RETX_MS105 = 105,
   NHU_TPOLL_RETX_MS110 = 110,
   NHU_TPOLL_RETX_MS115 = 115,
   NHU_TPOLL_RETX_MS120 = 120,
   NHU_TPOLL_RETX_MS125 = 125,
   NHU_TPOLL_RETX_MS130 = 130,
   NHU_TPOLL_RETX_MS135 = 135,
   NHU_TPOLL_RETX_MS140 = 140,
   NHU_TPOLL_RETX_MS145 = 145,
   NHU_TPOLL_RETX_MS150 = 150,
   NHU_TPOLL_RETX_MS155 = 155,
   NHU_TPOLL_RETX_MS160 = 160,
   NHU_TPOLL_RETX_MS165 = 165,
   NHU_TPOLL_RETX_MS170 = 170,
   NHU_TPOLL_RETX_MS175 = 175,
   NHU_TPOLL_RETX_MS180 = 180,
   NHU_TPOLL_RETX_MS185 = 185,
   NHU_TPOLL_RETX_MS190 = 190,
   NHU_TPOLL_RETX_MS195 = 195,
   NHU_TPOLL_RETX_MS200 = 200,
   NHU_TPOLL_RETX_MS205 = 205,
   NHU_TPOLL_RETX_MS210 = 210,
   NHU_TPOLL_RETX_MS215 = 215, 
   NHU_TPOLL_RETX_MS220 = 220,
   NHU_TPOLL_RETX_MS225 = 225,
   NHU_TPOLL_RETX_MS230 = 230,
   NHU_TPOLL_RETX_MS235 = 235,
   NHU_TPOLL_RETX_MS240 = 240,
   NHU_TPOLL_RETX_MS245 = 245,
   NHU_TPOLL_RETX_MS250 = 250,
   NHU_TPOLL_RETX_MS300 = 300,
   NHU_TPOLL_RETX_MS350 = 350,
   NHU_TPOLL_RETX_MS400 = 400,
   NHU_TPOLL_RETX_MS450 = 450,
   NHU_TPOLL_RETX_MS500 = 500
} NhuTPollReTx;

/**
 * @enum nhuPollPdu
   This enum contains the enumeration values for the Poll PDU of a radio bearer.
RRC maps these enumerations into proper values for configuration at the 
lower layers.
*/
typedef enum nhuPollPdu
{
   NHU_POLL_PDU_P4 = 4,
   NHU_POLL_PDU_P8 = 8,
   NHU_POLL_PDU_P16 = 16,
   NHU_POLL_PDU_P32 = 32,
   NHU_POLL_PDU_P64 = 64,
   NHU_POLL_PDU_P128 = 128,
   NHU_POLL_PDU_P256 = 256,
   NHU_POLL_PDU_P384 = 384,
   NHU_POLL_PDU_INF
} NhuPollPdu;

/**
 * @enum nhuRlcPollByte
   This enum contains the enumeration values for the Poll Byte of a radio 
bearer.
   RRC maps these enumerations into proper values for configuration at the 
lower layers.
*/
typedef enum nhuRlcPollByte
{
   NHU_POLL_BYTE_KB25 = 25,
   NHU_POLL_BYTE_KB50 = 50,
   NHU_POLL_BYTE_KB75 = 75,
   NHU_POLL_BYTE_KB100 = 100,
   NHU_POLL_BYTE_KB125 = 125,
   NHU_POLL_BYTE_KB250 = 250,
   NHU_POLL_BYTE_KB375 = 375,
   NHU_POLL_BYTE_KB500 = 500,
   NHU_POLL_BYTE_KB750 = 750,
   NHU_POLL_BYTE_KB1000 = 1000,
   NHU_POLL_BYTE_KB1250 =1250,
   NHU_POLL_BYTE_KB1500 = 1500,
   NHU_POLL_BYTE_KB2000 = 2000,
   NHU_POLL_BYTE_KB3000 = 3000,
   NHU_POLL_BYTE_INF
} NhuRlcPollByte;

/**
 * @enum nhuTReOrdering
   This enum contains the enumeration values for the T-Reodrering timer of a 
radio bearer.
   RRC maps these enumerations into proper values for configuration at the 
lower layers.
*/
typedef enum nhuTReOrdering
{
   NHU_TREORD_MS0 = 0,
   NHU_TREORD_MS5 = 5,
   NHU_TREORD_MS10 = 10,
   NHU_TREORD_MS15 = 15,
   NHU_TREORD_MS20 = 20,
   NHU_TREORD_MS25 = 25,
   NHU_TREORD_MS30 = 30,
   NHU_TREORD_MS35 = 35,
   NHU_TREORD_MS40 = 40,
   NHU_TREORD_MS45 = 45,
   NHU_TREORD_MS50 = 50,
   NHU_TREORD_MS55 = 55,
   NHU_TREORD_MS60 = 60,
   NHU_TREORD_MS65 = 65,
   NHU_TREORD_MS70 = 70,
   NHU_TREORD_MS75 = 75,
   NHU_TREORD_MS80 = 80,
   NHU_TREORD_MS85 = 85,
   NHU_TREORD_MS90 = 90,
   NHU_TREORD_MS95 = 95,
   NHU_TREORD_MS100 = 100,
   NHU_TREORD_MS110 = 110,
   NHU_TREORD_MS120 = 120,
   NHU_TREORD_MS130 = 130,
   NHU_TREORD_MS140 = 140,
   NHU_TREORD_MS150 = 150,
   NHU_TREORD_MS160 = 160,
   NHU_TREORD_MS170 = 170,
   NHU_TREORD_MS180 = 180,
   NHU_TREORD_MS190 = 190,
   NHU_TREORD_MS200 = 200
} NhuTReOrdering;

/**
 * @enum nhuTStatusProh
   This enum contains the enumeration values for the Status Prohibit timer of a
 radio bearer.
   RRC maps these enumerations into proper values for configuration at the 
 lower layers.
*/
typedef enum nhuTStatusProh
{
   NHU_STATUS_PROH_MS0 = 0,
   NHU_STATUS_PROH_MS5 = 5,
   NHU_STATUS_PROH_MS10 = 10,
   NHU_STATUS_PROH_MS15 = 15,
   NHU_STATUS_PROH_MS20 = 20,
   NHU_STATUS_PROH_MS25 = 25,
   NHU_STATUS_PROH_MS30 = 30,
   NHU_STATUS_PROH_MS35 = 35,
   NHU_STATUS_PROH_MS40 = 40,
   NHU_STATUS_PROH_MS45 = 45,
   NHU_STATUS_PROH_MS50 = 50,
   NHU_STATUS_PROH_MS55 = 55,
   NHU_STATUS_PROH_MS60 = 60,
   NHU_STATUS_PROH_MS65 = 65,
   NHU_STATUS_PROH_MS70 = 70,
   NHU_STATUS_PROH_MS75 = 75,
   NHU_STATUS_PROH_MS80 = 80,
   NHU_STATUS_PROH_MS85 = 85,
   NHU_STATUS_PROH_MS90 = 90,
   NHU_STATUS_PROH_MS95 = 95,
   NHU_STATUS_PROH_MS100 = 100,
   NHU_STATUS_PROH_MS105 = 105,
   NHU_STATUS_PROH_MS110 = 110,
   NHU_STATUS_PROH_MS115 = 115,
   NHU_STATUS_PROH_MS120 = 120,
   NHU_STATUS_PROH_MS125 = 125,
   NHU_STATUS_PROH_MS130 = 130,
   NHU_STATUS_PROH_MS135 = 135,
   NHU_STATUS_PROH_MS140 = 140,
   NHU_STATUS_PROH_MS145 = 145,
   NHU_STATUS_PROH_MS150 = 150,
   NHU_STATUS_PROH_MS155 = 155,
   NHU_STATUS_PROH_MS160 = 160,
   NHU_STATUS_PROH_MS165 = 165,
   NHU_STATUS_PROH_MS170 = 170,
   NHU_STATUS_PROH_MS175 = 175,
   NHU_STATUS_PROH_MS180 = 180,
   NHU_STATUS_PROH_MS185 = 185,
   NHU_STATUS_PROH_MS190 = 190,
   NHU_STATUS_PROH_MS195 = 195,
   NHU_STATUS_PROH_MS200 = 200,
   NHU_STATUS_PROH_MS205 = 205,
   NHU_STATUS_PROH_MS210 = 210,
   NHU_STATUS_PROH_MS215 = 215,
   NHU_STATUS_PROH_MS220 = 220,
   NHU_STATUS_PROH_MS225 = 225,
   NHU_STATUS_PROH_MS230 = 230,
   NHU_STATUS_PROH_MS235 = 235, 
   NHU_STATUS_PROH_MS240 = 240,
   NHU_STATUS_PROH_MS245 = 245,
   NHU_STATUS_PROH_MS250 = 250,
   NHU_STATUS_PROH_MS300 = 300,
   NHU_STATUS_PROH_MS350 = 350,
   NHU_STATUS_PROH_MS400 = 400,
   NHU_STATUS_PROH_MS450 = 450,
   NHU_STATUS_PROH_MS500 = 500
} NhuTStatusProh;

/**
 * @enum nhuSrsBwCfgCmn
   This enum contains the common SRS bandwidth information.
*/
typedef enum nhuSrsBwCfgCmn
{
   NHU_SRS_BW0,
   NHU_SRS_BW1,
   NHU_SRS_BW2,
   NHU_SRS_BW3,
   NHU_SRS_BW4,
   NHU_SRS_BW5,
   NHU_SRS_BW6,
   NHU_SRS_BW7
} NhuSrsBwCfgCmn;

/**
 * @enum nhuSrsBwCfgDed
   This enum contains the dedicated SRS bandwidth information.
*/
typedef enum nhuSrsBwCfgDed
{
   NHU_SRSDED_BW0,
   NHU_SRSDED_BW1,
   NHU_SRSDED_BW2,
   NHU_SRSDED_BW3
} NhuSrsBwCfgDed;


/**
 * @enum nhuSrsSubFrmCfg
   This enum contains the subframe configuration information.
*/
typedef enum nhuSrsSubFrmCfg
{
   NHU_SRS_SC0,
   NHU_SRS_SC1,
   NHU_SRS_SC2,
   NHU_SRS_SC3,
   NHU_SRS_SC4,
   NHU_SRS_SC5,
   NHU_SRS_SC6,
   NHU_SRS_SC7,
   NHU_SRS_SC8,
   NHU_SRS_SC9,
   NHU_SRS_SC10,
   NHU_SRS_SC11,
   NHU_SRS_SC12,
   NHU_SRS_SC13,
   NHU_SRS_SC14,
   NHU_SRS_SC15
} NhuSrsSubFrmCfg;

/**
 * @enum nhuSrsPeriodicity
   This enum contains the SRS periodicity information.
*/
typedef enum nhuSrsPeriodicity
{
   NHU_SRS_PRD_MS2,
   NHU_SRS_PRD_MS5,
   NHU_SRS_PRD_MS10,
   NHU_SRS_PRD_MS20,
   NHU_SRS_PRD_MS40,
   NHU_SRS_PRD_MS80,
   NHU_SRS_PRD_MS160,
   NHU_SRS_PRD_MS320
} NhuSrsPeriodicity;

/**
 * @enum nhuSrsCShift
   This enum contains the SRS cyclic shift information.
*/
typedef enum nhuSrsCShift
{
   NHU_SRS_CS0,
   NHU_SRS_CS1,
   NHU_SRS_CS2,
   NHU_SRS_CS3,
   NHU_SRS_CS4,
   NHU_SRS_CS5,
   NHU_SRS_CS6,
   NHU_SRS_CS7
} NhuSrsCShift;

/**
 * @enum nhuSrsCfgPrd
   This enum contains the SRS period configuration.
*/
typedef enum nhuSrsCfgPrd
{
   SRS_CFG_PRD_1 = 1,
   SRS_CFG_PRD_2 = 2,
   SRS_CFG_PRD_5 = 5,
   SRS_CFG_PRD_10 = 10,
   SRS_CFG_PRD_INF
} NhuSrsCfgPrd;

/**
 * @enum nhuCipherAlgo
 * This enum describes the ciphering alogorithm type.
*/
typedef enum nhuCipherAlgo
{
   NHU_CIPHER_ALGO_EEA0,
   NHU_CIPHER_ALGO_EEA1,
   NHU_CIPHER_ALGO_EEA2,
   NHU_CIPHER_ALGO_EEA3
} NhuCipherAlgo;

/**
 * @enum nhuIntgAlgo
 * This enum describes the integrity alogorithm type.
*/
typedef enum nhuIntgAlgo
{
/* nhu_x_001.main_4: added an element for NULL IP algo*/
#ifdef NHU_VER1
   NHU_INTG_ALGO_EIA0,
#endif
   NHU_INTG_ALGO_EIA1,
   NHU_INTG_ALGO_EIA2,
   NHU_INTG_ALGO_EIA3
} NhuIntgAlgo;

/**
 * @enum nhuReEstCause
    This enum describes the re-establsihment cause. 
*/
typedef enum nhuReEstCause
{
   NHU_REST_CAUSE_RECONFIG_FAIL,
   NHU_REST_CAUSE_HO_FAIL,
   NHU_REST_CAUSE_OTHER_FAIL
} NhuReEstCause;

/**
 * @enum nhuPdschPaParam
 * This element enumerates the parameter PA for PDSCH configuration at PHY.
 * Each enum value maps to a PA value in dBs.
*/
typedef enum nhuPdschPaParam
{
   NHU_PDSCH_PA_MINUS_6,
   NHU_PDSCH_PA_MINUS_4DOT77,
   NHU_PDSCH_PA_MINUS_3,
   NHU_PDSCH_PA_MINUS_1DOT77,
   NHU_PDSCH_PA_ZERO,
   NHU_PDSCH_PA_ONE,
   NHU_PDSCH_PA_TWO,
   NHU_PDSCH_PA_THREE
} NhuPdschPaParam;

/**
 * @struct nhuHdr
    @brief NHU Header
    @details 
   This structure contains the CellId, UeId, and PdcpId. All the NHU
interface primitives carry this information. 
*/
typedef struct nhuHdr
{
   NhuCellId      cellId;   /*!< Cell ID (Value starts from 1)*/
   NhuCrnti       ueId;     /*!< Ue ID */
   U32            transId;  /*!< Transaction identifier for simultaneous 
                                 procedures */
   Bool           isUlDatFwdReq;  /*!< To indicate whether UL Data Forwarding 
                                       is required or not */
} NhuHdr;

/**
 * @brief NhuErrType
   This is the configuration error type in the error indication to the RRC user.
*/
typedef U8 NhuErrType;  
/**
 * @brief NhuErrCause
   This is the configuration error cause in the error indication to the RRC user.
*/
typedef U8 NhuErrCause; 

/**
 * @struct nhuErrorInfo
    @brief  Error Information.
   @details This structure contains the error information that RRC sends to the RRC user in the error indication.
*/
typedef struct nhuErrorInfo
{
   Bool          errPres;    /*!< Indicates whether errorInfo is present */
   NhuErrType    errType;    /*!< Error type */
   NhuErrCause   errCause;   /*!< Error cause */
} NhuErrorInfo;
/**
 * @struct nhuNewUeInfo
    @brief  New UE Information.
   @details This is the UE ID information that the RRC user gives to RRC in NhUiNhuCfgReq,
   whenever it allocates a new CRNTI, so that RRC can reconfigure the 
   lower layers with the new CRNTI information.
*/ 
typedef struct nhuNewUeInfo
{
   NhuCrnti    newCrnti;  /*!< New CRNTI which needs to be configured at RRC */
}NhuNewUeInfo;

/**
 * @struct nhuPdcpRohcInfo
    @brief  Pdcp Rohc Information.
   @details This structure contains the configuration information related to ROHC for 
PDCP header compression associated with a radio bearer.
*/
typedef struct nhuPdcpRohcInfo
{
   U16 maxCid;                   /*!< MAX CID */
   U8  rohcProfileList[NHU_MAX_ROHC_PROF_LST_LEN]; /*!< Profile lists to be 
                                                        configured */
}NhuPdcpRohcInfo;

/**
 * @struct nhuPdcpHdrComprInfo
    @brief  Pdcp Header Compression Information.
   @details This structure contains the PDCP header compression information. 
Presently, it contains only the ROHC configuration details.
*/
typedef struct nhuPdcpHdrComprInfo
{
   NhuPdcpRohcInfo rohcInfo; /*!< ROHC configuration */
} NhuPdcpHdrComprInfo;

/**
 * @struct  nhuHoPdcpSduInfo 
    @brief  Handover information.
   @details This structure contains PDCP SDU status information to be provided to PDCP during handover. This information is required at target eNB.
*/
typedef struct nhuHoPdcpSduInfo
{
   U8  isHoPres;       /*!< To convey handover information is present or
                            not. Use last 2bits (from LSB). 
                            Allowed values are:
                               -# NHU_HO_NOT_PRSNT  0x00
                               -# NHU_HO_UL         0x01
                               -# NHU_HO_DL         0x02    nhu_x_001.main_5:117414: corrected
                       */
   U8  snLen;          /*!< PDCP-SN length 12/15 bits */
   U32 ulCountVal;     /*!< PDCP-SN and HFN of first missing UL PDCP SDU */
   U32 dlCountVal;     /*!< PDCP-SN and HFN that the target should 
                            assign for the next DL SDU not having an SN yet */
   U16  numBits;        /*!< Number of bits in UL bitmap */
   U8  *ulBitMap;      /*!< UL PDCP SDU Status */
}NhuHoPdcpSduInfo;

/**
 * @struct nhuPdcpCfg
    @brief  Pdcp Configuration.
  @details This structure contains the PDCP configuration information associated with a 
PDCP ID. This information in the configuration indicates that PDCP is to be configured for the associated radio bearer/PDCP ID.
*/
typedef struct nhuPdcpCfg 
{
   Bool                intgReqd;       /*!< Integrity required */
   U8                  pdcpCfgType;    /*!< Explicit/Default */
   U8                  pdcpCfgBitMsk;  /*!< Bitmask indicates configuration presence */
   NhuPdcpDiscardTmr   discardTmr;     /*!< PDCP Discard timer */
   NhuPdcpFlushTmr     flushTmr;       /*!< PDCP Flush timer */
   NhuPdcpSnSize       snSize;         /*!< PDCP SN size */
   Bool                statusRptReq;   /*!< PDCP Status Reprot Required flag */
   NhuPdcpHdrComprInfo hdrComprInfo;   /*!< PDCP Header Compression information */
   NhuHoPdcpSduInfo    hoPdcpSduStaInfo; /*!< This contains the PDCP SDU status
                                              information required at target eNB
                                              during handover */
   Bool                cfmReqd;          /*!< Confirm required/not for SDUs
                                              received by the peer PDCP entity */
}NhuPdcpCfg;

/**
  * @struct nhuLogChId
    @brief  Logical Channel Id.
  @details This structure contains a combination of the logical channel type and the instance identifier resulting in unique identification of a logical channel within the
context of a logical channel type.
*/
typedef struct nhuLogChId    
{
   CmLteLcType logChType;     /*!< Channel Type */
   U8           lcId;          /*!< Logical Channel Instance */
} NhuLogChId;


/**
 * @struct nhuLogChCfg
    @brief  Logical Channel Configuration.
 @details This structure contains the logical channel configuration information 
 for a radio bearer. 
 It contains logical channel priority, PBR, and logical channel group information.
*/
typedef struct nhuLogChCfg
{
   U8              logChCfgpres; /*!< Bitmask indicates Logical Channel */
   U8              logChGrp;     /*!< Logical Channel group */
}NhuLogChCfg;

/**
 * @struct nhuUlLogChMap
    @brief  Uplink Logical Channel Mapping.
 @details This structure contains the logical channel mapping information in the 
uplink for a radio bearer. 
 It contains logical channel configuration and QOS configuration information.
*/
typedef struct nhuUlLogChMap
{
   CmLteTrchType     trChType;     /*!< Transport Channel type */
   U8              lcCfgType;    /*!< Logical Channel Explicit/Default */
   NhuLogChCfg     lcCfg;        /*!< UL Logical Channel configuration */
}NhuUlLogChMap;

/**
 * @struct nhuDlUmRlcModeInfo
    @brief  Downlink UM Rlc Mode.
   @details This structure contains the Downlink UM RLC mode configuration. 
Currently, it contains only the snField length.
*/
typedef struct nhuDlUmRlcModeInfo
{
   U8 snFieldLen;             /*!< SN field length */
}NhuDlUmRlcModeInfo;

/**
 * @struct nhuDlAmRlcModeInfo
    @brief  Downlink AM Rlc Mode.
   @details This structure contains the Downlink AM RLC mode configuration. 
*/
typedef struct nhuDlAmRlcModeInfo
{
   NhuMaxRetxThres  maxRetxThresh; /*!< Maximum Re-transmission Threshold */
   NhuRlcPollByte   pollByte;      /*!< Poll Byte */
   NhuPollPdu       pollPdu;       /*!< Poll PDU */
   NhuTPollReTx     tPollRetx;     /*!< T-Poll Re-transmission */
}NhuDlAmRlcModeInfo;

/**
 * @struct nhuDlTmRlcModeInfo
    @brief  Downlink TM Rlc Mode.
   @details This structure contains the Downlink TM RLC mode configuration. This
   structure is not used in the current version.
*/
typedef struct nhuDlTmRlcModeInfo
{
   U32  bufferSize;               /*!< Buffer size */
}NhuDlTmRlcModeInfo;

/**
 * @struct nhuUlUmRlcModeInfo
    @brief  Uplink UM Rlc Mode.
   @details This structure contains the Uplink UM RLC mode configuration. 
Currently, it contains only the SN Field length and T-Reordering.
*/
typedef struct nhuUlUmRlcModeInfo
{
   U8             snFieldLen;    /*!< SN field length */
   NhuTReOrdering tReordring;    /*!< T-Reordering */
}NhuUlUmRlcModeInfo;

/**
 * @struct nhuUlAmRlcModeInfo
    @brief  Uplink AM Rlc Mode.
   @details This structure contains the Uplink AM RLC mode configuration.
*/
typedef struct nhuUlAmRlcModeInfo
{
   NhuTStatusProh  tStatusProh;  /*!< T-Status Prohibit */
   NhuTReOrdering  tReordring;   /*!< T-Reordering */
}NhuUlAmRlcModeInfo;

/**
 * @struct nhuUlRlcMode
    @brief  Uplink Rlc Mode.
  @details This structure contains the Uplink RLC mode configuration information of a 
radio bearer used at the RLC. 
*/
typedef struct nhuUlRlcMode
{
   U8              rlcCfgType;      /*!< Explicit/Default */
   U8              mode;            /*!< MODE indicates the RLC mode to be configured */ 
   union
   {
      NhuUlUmRlcModeInfo umRlc;   /*!< UM RLC Mode */
      NhuUlAmRlcModeInfo amRlc;   /*!< AM RLC Mode */
   }m;
} NhuUlRlcMode;

/**
 * @struct nhuUlRbCfg
    @brief  Uplink Rb Configuration.
  @details This structure contains the Uplink radio bearer configuration information 
for configuring a radio bearer at the lower layers such as logical channel mapping 
information and RLC mode specific configuration information. 
The field ulBitMsk must be set suitably to indicate the other fields present 
in this structure.
*/
typedef struct nhuUlRbCfg
{
   U8             ulRbBitMsk; /*!< Uplink Rb bitmask */
   NhuUlLogChMap  ulLogChMap; /*!< Uplink Logical Channel Mapping information */
   NhuUlRlcMode   ulRlcMode;  /*!< Uplink RLC mode */
}NhuUlRbCfg;

/**
 * @struct nhuDlLogChMap
    @brief  Downlink Logical Channel Map.
   @details This structure contains the logical channel mapping information in the 
downlink for a radio bearer. 
   It contains logical channel QOS configuration details.
*/
typedef struct nhuDlLogChMap
{
   CmLteTrchType     trChType;    /*!< Transport Channel type */
}NhuDlLogChMap;

/**
 * @struct nhuDlRlcMode
    @brief  Downlink Rlc Mode.
   @details This structure contains the downlink RLC mode configuration information of a 
radio bearer used at the RLC. 
*/
typedef struct nhuDlRlcMode
{
   U8 rlcCfgType;    /*!< Explicit/Default */
   U8 mode;          /*!< MODE indicates the RLC mode to be configured */ 
   union
   {
      NhuDlUmRlcModeInfo umRlc;    /*!< UM RLC mode */
      NhuDlAmRlcModeInfo amRlc;    /*!< AM RLC mode */
      NhuDlTmRlcModeInfo tmRlc;    /*!< TM RLC mode */
   }m;
} NhuDlRlcMode;

/**
 * @struct nhuDlRbCfg
    @brief  Downlink Rb Configuration.
  @details This structure contains the downlink radio bearer configuration information 
for configuring a radio bearer at the lower layers such as logical channel mapping 
information and RLC mode specific configuration information. 
The field dlRbBitMsk must be set suitably to indicate the other fields in 
this structure.
*/
typedef struct nhuDlRbCfg
{
   U8             dlRbBitMsk; /*!< Downlink Rb bitmask */
   NhuDlLogChMap  dlLogChMap; /*!< Downlink Logical Channel Mapping information */
   NhuDlRlcMode   dlRlcMode;  /*!< Downlink RLC mode information */
}NhuDlRbCfg;


/**
 * @struct nhuRbCfgInfo
    @brief  Rb Configuration.
    @details
 -# This structure contains the radio bearer configuration related information. 
 -# It contains the Radio Bearer identifier to be configured, Uplink radio 
bearer configuration information and Downlink radio bearer configuration information.
 -#  It may contain Uplink, Downlink, or both the configurations information. 
Based on whether the RRC user wants to setup, release, or modify; the 
number of elements in this may vary which is set using the field rbCfgBitMsk.
*/
typedef struct nhuRbCfgInfo
{
   NhuRbId       rbId;         /*!< Radio Bearer ID and type */
   NhuLogChId    lcId;         /*!< Logical Channel ID */
   U8            rbCfgBitMsk;  /*!< Bitmask indicates the presence 
                                    of configuration */
   NhuUlRbCfg    ulRbCfg;      /*!< Uplink RB configuration */
   NhuDlRbCfg    dlRbCfg;      /*!< Downlink RB configuration */
   NhuPdcpCfg    pdcpCfg;      /*!< PDCP configuration */
   /* nhu_x_001.main_6 - ADD - Members corresponding to LTE_L2_MEAS */
//#ifdef LTE_L2_MEAS /* sri: needed to send value to TIP LL2 RLC */
   U8            qci;          /*!< QCI for the logical channel.
                                  Valid Range:[0-255] (Actual QCI - 1). */
//#endif /* LTE_L2_MEAS */
}NhuRbCfgInfo;

/**
 * @struct nhuRbCfgList
    @brief  Rb Configuration List.
  @details This structure contains the list of configuration information for the radio bearers to be configured at the lower layers.
*/
typedef struct nhuRbCfgList
{
   U8           numOfRbCfgInfo; /*!< Number of Rbs to configure */
   NhuRbCfgInfo *rbCfgInfoList; /*!< Linked list of NhuRbMapInfo */
   U8           isHO; /* To indicate DRB cfg during HO or Normal attach */
}NhuRbCfgList;

/**
 * @struct nhuRbRlsCfgList
    @brief  Rb Release List.
  @details This sturcture contains the list of radio bearers to be released. 
The field numOfRbCfgInfo indicates the number of elements in this array of 
RBs to be released. 
*/
typedef struct nhuRbRlsCfgList
{
   U8            numOfRbCfgInfo;/*!< Number of Rbs to release */
   NhuRbId       *rbsToRel;     /*!< Linked list of RBs to release */
}NhuRbRlsCfgList;


/**
 * @struct nhuRbCfgAllList
    @brief  Rb Configuration All List.
   @details This structure contains the set of all the configuration information 
(Add, Modify, and Release) for the radio bearers to be applied at the lower layers.
The rbCfgTypBitMsk indicates one or more elements being present in this 
structure. 
*/
typedef struct nhuRbCfgAllList
{
   U8               rbCfgTypBitMsk;   /*!< RB configuration bitmask */
   NhuRbCfgList     rbToAddCfgList;   /*!< RB configuration for Add */
   NhuRbCfgList     rbToModCfgList;   /*!< RB configuration for Modify */
   NhuRbRlsCfgList  rbToRlsCfgList;   /*!< RB configuration for Release */
}NhuRbCfgAllList;

/**
 * @struct nhuUlHarqCfg
    @brief  Uplink Harq Configuration.
   @details This structure contains the Uplink HARQ configuration information. It is required for MAC. 
*/
typedef struct nhuUlHarqCfg        
{
   NhuMaxHarqTx            ulMaxHarqTx;      /*!< Max HARQ Transmission */
   U8                      deltaHarqOffset;  /*!< HARQ Delta Offset */
}NhuUlHarqCfg;

/**
 * @struct nhuTrChCfg
    @brief  Transport Channel Configuration.
    @details
-# This structure contains the transport channel configuration for the MAC.
-# It contains HARQ configuration and Time Alignment timer.
*/
typedef struct nhuTrChCfg
{
   U8                   trChCfgType;   /*!< Explicit/Default */
   U8                   trChBitMsk;    /*!< Transport channel bitmask */
   NhuUlHarqCfg         ulHarqCfg;     /*!< Uplink HARQ configuration information */ 
}NhuTrChCfg;

/**
 * @struct nhuIntgKeyAlgoInfo
    @brief  Integrity Key Algorithm.
  @details This structure contains the integrity related configuration information like 
algorithms and keys to be applied at the PDCP layer.
*/
typedef struct nhuIntgKeyAlgoInfo
{
   U8             action;                    /*!< Add/ Modify */
   NhuIntgAlgo    intgAlgo;                  /*!< Integrity Algorithm */
   U8             intgKey[NHU_INTG_KEY_LEN]; /*!< Integrity key */ 
} NhuIntgKeyAlgoInfo;

/**
 * @struct nhuCiphKeyAlgoInfo
    @brief  Ciphering Key Algorithm.
   @details This structure contains the ciphering related configuration information 
like algorithms and keys to be applied at the PDCP layer.
*/
typedef struct nhuCiphKeyAlgoInfo
{
   NhuCipherAlgo ciphAlgo;                      /*!< Ciphering Algorigthm */
   U8            cipherCpKey[NHU_CIPH_KEY_LEN]; /*!< Ciphering control plane key */ 
   U8            cipherUpKey[NHU_CIPH_KEY_LEN]; /*!< Ciphering user plane key*/
} NhuCiphKeyAlgoInfo;

/**
 * @struct nhuSecurityCfg
    @brief  Security Configuration.
  @details This structure contains the security (ciphering and integrity) related configuration information.
This structure must be provided when the RRC user wants to configure ciphering and
integrity at the RRC and the lower layers. It may or may not be associated with
other structures in NhuUeCfgInfo.
*/
typedef struct nhuSecurityCfg
{
   U8                  secCfgBitMsk; /*!< Bitmask indicates presence of 
                                          Integrity or Ciphering information */
   NhuIntgKeyAlgoInfo  intgCfgInfo;  /*!< Integrity configuration information */
   NhuCiphKeyAlgoInfo  cipherCfgInfo;/*!< Ciphering configuration information */
} NhuSecurityCfg;

#ifdef RRC_PHY_CFG_SUPP
/** @enum nhuRepFactor 
This enum contains the enumeration values for Reptition factor.
*/
typedef enum nhuRepFactor
{
   NHU_N2, 
   NHU_N4, 
   NHU_N6
}NhuRepFactor;

#ifdef NHU_VER3
/* nhu_x_001.main_5: 115549: */
 /**
  * @enum NhuTddAckNackFBMode
  * This element enumerates the TDD ACk/NACK Feedback mode configuration at PHY.
 */
 typedef enum nhuTddAckNackFBMode
 {
    NHU_TDD_ACKNACK_FB_BUNDLING,
    NHU_TDD_ACKNACK_FB_MUXING
 }NhuTddAckNackFBMode;
#endif /* NHU_VER3 */


/**
 * @enum NhuUeTxAntType
 * This element enumerates the UE TX Antenna Selection configuration at PHY.
*/
typedef enum nhuUeTxAntType
{
   NHU_UE_TX_ANT_CLOSEDLOOP, /*!< Closed loop selection */
   NHU_UE_TX_ANT_OPENLOOP    /*!< Open loop selection */
} NhuUeTxAntType;

/**
 * @enum NhuCqiRptModeAperiodic
 * This element enumerates the Aperiodic CQI reporting configuration at PHY.
*/
typedef enum nhuCqiRptModeAperiodic
{
   NHU_CQI_RPT_MODE_APERIODIC_RM12, /*!< corresponds to Mode 1-2 */
   NHU_CQI_RPT_MODE_APERIODIC_RM20, /*!< corresponds to Mode 2-0 */
   NHU_CQI_RPT_MODE_APERIODIC_RM22, /*!< corresponds to Mode 2-2 */
   NHU_CQI_RPT_MODE_APERIODIC_RM30, /*!< corresponds to Mode 3-0 */
   NHU_CQI_RPT_MODE_APERIODIC_RM31  /*!< corresponds to Mode 3-1 */
} NhuCqiRptModeAperiodic;

/**
 * @enum NhuDedAntCfgTxMode
 * This element enumerates the Transmission Mode for the Antenna 
 * configuration at PHY for a UE.
*/
typedef enum nhuDedAntCfgTxMode
{
   NHU_DED_ANT_CFG_TX_MODE_TM1, /*!< corresponds to TX Mode 1 */
   NHU_DED_ANT_CFG_TX_MODE_TM2, /*!< corresponds to TX Mode 2 */
   NHU_DED_ANT_CFG_TX_MODE_TM3, /*!< corresponds to TX Mode 2 */
   NHU_DED_ANT_CFG_TX_MODE_TM4, /*!< corresponds to TX Mode 2 */
   NHU_DED_ANT_CFG_TX_MODE_TM5, /*!< corresponds to TX Mode 2 */
   NHU_DED_ANT_CFG_TX_MODE_TM6, /*!< corresponds to TX Mode 2 */
   NHU_DED_ANT_CFG_TX_MODE_TM7  /*!< corresponds to TX Mode 2 */
/* nhu_x_001.main_4: added an element TX mode 8*/
#ifdef NHU_VER1
   ,NHU_DED_ANT_CFG_TX_MODE_TM8 /*!< corresponds to TX Mode 2 */
#endif
} NhuDedAntCfgTxMode;


/**
 * @struct nhuDedSRCfg
    @brief  Dedicated SR Configuration.
   @details This structure contains the dedicated SRS configuration.
*/
typedef struct nhuDedSRCfg
{
   U8       cfgTyp;        /*!< Default/Explicit */
   U8       dedSRCfgType;  /*!< Setup/Release */
   struct
   {
      U16      srPUCCHRi;  /*!< SR PUCCH Resource Index, n(1)PUCCH,SRI (0..2047) */
      U8       srCfgIdx;   /*!< SR configuration index, Isr (0..155) */
   } setup;
} NhuDedSRCfg;

/**
 * @struct nhuPdschCfg
    @brief  Dedicated PDSCH Configuration.
   @details This structure contains the dedicated PDSCH configuration.
*/
typedef struct nhuPdschCfg
{
   U8                   cfgTyp;   /*!< Explicit/Default=dB0 */
   NhuPdschPaParam      pa;       /*!< Pa (in dB) */
}NhuPdschCfg;

/**
 * @struct nhuDedPuschCfg
    @brief  Dedicated PUSCH Configuration.
   @details This structure contains the dedicated PUSCH configuration.
*/
typedef struct nhuDedPuschCfg
{
   U8          cfgTyp;              /*!< Explicit/Default*/
   U8          betaOffsetAckIdx;    /*!< (0..15) */
   U8          betaOffsetRiIdx;     /*!< (0..15) */
   U8          betaOffsetCqiIdx;    /*!< (0..15) */
}NhuDedPuschCfg;

/**
 * @struct  nhuDedSRSUlCfg 
    @brief  SRS UL dedicated configuration.
   @details This structure contains SRS UL dedicated configuration.
*/
typedef struct nhuDedSRSUlCfg
{
   U8         cfgTyp;           /*!< Explicit/Default*/   
   U8         choice;           /*!< setup/ Release*/
   struct 
   {
      U8           srsBwCfg;    /*!< SRS bandwidth(0,1,2,3) */
      U8           srsHopBwCfg; /*!< SRS hopping bandwidth (0,1,2,3) */
      U8           freqDomPos;  /*!< frequency domain position (0..23) */
      Bool         duration;    /*!< FALSE:single, TRUE:indefinite */
      U16          srsCfgIndx;  /*!< SRS configuration index (0..1023) */
      U8           transComb;   /*!< transmission comb (0..1) */
      U8           cycleshft;   /*!< (0..7) */
   }setup;
}NhuDedSRSUlCfg;

/**
 * @struct  nhuDedPucchCfg 
    @brief  PUCCH dedicated configuration.
   @details This structure contains dedicated PUCCH configuration.
*/
typedef struct nhuDedPucchCfg
{
  U8            cfgTyp;                   /*!< Explicit/Default*/
  U8            choice;                   /*!< Setup/Release */
  struct 
  {
#ifdef NHU_VER3
/* nhu_x_001.main_5 : 115549: */
     Bool               repFactorPres;    /*!< Indicates if repetition factor
                                               is to be configured */
#endif /*NHU_VER3*/
     NhuRepFactor       factor;           /*!< ACK/NACK repetition factor */
     U16                n1PUCCH_AN_Rep;   /*!< PUCCH resource to repeat the 
                                           transmission of corresponding ACK/NAK
                                           response */
  }setup;
#ifdef NHU_VER3
/* nhu_x_001.main_5 : 115549: */
  Bool           tddAckNackCfgPres;           /*!< TDD ACk/NACK config present. */
  NhuTddAckNackFBMode tddAckNackFeedbackMode; /*!< TDD ACK/NACK feedback mode
                                                      (bundling, Multiplexing) */
#endif /*NHU_VER3*/
}NhuDedPucchCfg;

/* nhu_x_001.main_4: Code book subset retri is added under NHU_VER2*/
#ifdef NHU_VER2
/**
 * @enum NhuCdBkSubsetRestnType
 * This element enumerates the Code Book Subset Restriction 
 * configuration at PHY for a UE.
*/
typedef enum nhuCdBkSubsetRestnType
{
   N2TX_ANTENNA_TM3,     /*!< 2 Antenna Ports for transmissiom mode 3*/
   N4TX_ANTENNA_TM3,     /*!< 4 Antenna Ports for transmissiom mode 3*/
   N2TX_ANTENNA_TM4,     /*!< 2 Antenna Ports for transmissiom mode 4*/
   N4TX_ANTENNA_TM4,     /*!< 4 Antenna Ports for transmissiom mode 4*/
   N2TX_ANTENNA_TM5,     /*!< 2 Antenna Ports for transmissiom mode 5*/
   N4TX_ANTENNA_TM5,     /*!< 4 Antenna Ports for transmissiom mode 5*/
   N2TX_ANTENNA_TM6,     /*!< 2 Antenna Ports for transmissiom mode 6*/
   N4TX_ANTENNA_TM6      /*!< 4 Antenna Ports for transmissiom mode 6*/
}NhuCdBkSubsetRestnType;

/**
 * @struct  NhuDedAntCodeBkSubsetRes
 * @brief Code Book Subset Restriction Configuration.
 * @details This structure contains the information for 
 *          codeBookSubsetRestriction  configuration specific to 
 *          transmission mode of a UE Phy.
*/
typedef struct nhuDedAntCodeBookSubsetRestn
{
  NhuCdBkSubsetRestnType nhuCdBkRestType;
  union
  {
      U8   n2TxAntTm3;     /*!< 2 Antenna Ports for transmissiom mode 3*/
      U8   n4TxAntTm3;     /*!< 4 Antenna Ports for transmissiom mode 3*/
      U8   n2TxAntTm4;     /*!< 2 Antenna Ports for transmissiom mode 4*/
      U8   n4TxAntTm4[8];  /*!< 4 Antenna Ports for transmissiom mode 4*/
      U8   n2TxAntTm5;     /*!< 2 Antenna Ports for transmissiom mode 5*/
      U16  n4TxAntTm5;     /*!< 4 Antenna Ports for transmissiom mode 5*/
      U8   n2TxAntTm6;     /*!< 2 Antenna Ports for transmissiom mode 6*/
      U16  n4TxAntTm6;     /*!< 4 Antenna Ports for transmissiom mode 6*/
  }codeBookSubsetRestn;
}NhuDedAntCodeBkSubsetRes;
#endif /* NHU_VER2 */

/**
 * @struct  nhuDedAntCfgInfo
 * @brief Dedicated Antenna Configuration.
 * @details This structure contains the information for antenna related
 *          configuration specific to an UE at PHY.
*/
typedef struct nhuDedAntCfgInfo
{
   U8                   cfgTyp;              /*!< Default/Explicit */
   NhuDedAntCfgTxMode   txMode;              /*!< Transmission Mode: 36.213,7.1 */
   U8                   txAntSelectchoice;   /*!< Setup/Release */
   NhuUeTxAntType       txAntSelect;         /*!< Closed/Open, Valid only if
                                               cfgType is setup:36.213, 8.7 */
/* nhu_x_001.main_4: Code book subset restri is added*/
#ifdef NHU_VER2
   NhuDedAntCodeBkSubsetRes codeBookSubsetRes;
#endif /* NHU_VER2 */
} NhuDedAntCfgInfo;

/* nhu_x_001.main_4: added pmiRiRpt and cqiMask*/
#ifdef NHU_VER1
/*
 * @enum nhuPmiRiRptSetup
 * This element enumerates the CQI PMI Report setup configuration at PHY.
*/
typedef enum nhuPmiRiRptSetup
{
   NHU_CQI_PMI_RPT_SETUP  /*!< PMI Report setup */
} NhuPmiRiRptSetup;

/*
 * @struct nhuPmiRiRpt
 * This element contains the enum CQI PMI Report setup configuration at PHY.
*/
typedef struct nhuPmiRiRpt
{
   Bool              pres;           /*!< Indicates presence of Pmi Ri Rpt */
   NhuPmiRiRptSetup  pmiRiRptSetup;  /*!< PMI Report setup */
} NhuPmiRiRpt;


/*
 * @enum nhuCqiMaskSetup
 * This element enumerates the CQI reporting setup configuration at PHY.
*/
typedef enum nhuCqiMaskSetup
{
   NHU_CQI_RPT_SETUP  /*!< Cqi report setup */
} NhuCqiMaskSetup;


/*
 * @struct nhuCqiMask
 * This element contains the CQI reporting setup configuration at PHY.
*/
typedef struct nhuCqiMask
{
   Bool             pres;         /*!< Indicates presence of Cqi Mask Setup */
   NhuCqiMaskSetup  cqiMaskSetup; /*!< Cqi report setup */
} NhuCqiMask;
#endif /* NHU_VER1 */

/* nhu_x_001.main_4: periodic and aperiodic both reports can be configured
 * simultaneously when NHU_VER2 flag is enabled */
#ifdef NHU_VER2
/**
 * @struct NhuCqiRptModeAprd
    @brief  CQI Aperiodic Reporting Mode.
   @details This structure contains the Aperiodic CQI Reporting mode 
            configuration details.
*/
typedef struct nhuCqiReportModeAprd
{
    Bool pres;
    NhuCqiRptModeAperiodic aPeriodicRptMode; /*!< Aperiodic CQI Report */
}NhuCqiRptModeAprd;
#endif /* NHU_VER2 */

/**
 * @struct  nhuCqiRptModePeriodic
 * @brief Periodic CQI Report Configuration.
 * @details This structure contains the information for periodic CQI report
 *          related configuration specific to an UE.
*/
typedef struct nhuCqiRptModePeriodic
{
#ifdef NHU_VER2
   Bool  pres;
#endif /* NHU_VER2 */
   U8    cqiPeriodicCfgType;     /*!< Configuration type: Setup/Release  */
   struct
   {
      U16   cqiPUCCHRsrcIndx;    /*!< Range (0..1185) */
      U16   cqiPmiCfgIndx;       /*!< Range (0..1023) */
      U8    formatIndicator;     /*!< Type: Wideband/Subband */
      struct
      {
         U8    k;                /*!< Range (1..4) */
      } subbandCqi;              /*!< Valid only if formatIndicator is Subband*/ 

      Bool  riCfgPres;           /*!< RI Configuration index is present or absent */
      U16   riCfgIndx;           /*!< Range (0..1023) */
      Bool  simultaneousAckNack; /*!< Simultaneous ACK/NACK with CQI support.
                                      TRUE:YES, FALSE:NO */
#ifdef NHU_VER1
   NhuCqiMask   cqiMask;         /*!< Cqi mask */
#endif /* NHU_VER1 */
   } setup;                      /*! Valid only if cqiPeriodicCfgType is Setup
*/
} NhuCqiRptModePeriodic;


/**
 * @struct  nhuCqiRptCfg 
 * @brief CQI Report Configuration.
 * @details This structure contains the information for CQI report
 *          related configuration specific to an UE.
*/
typedef struct nhuCqiRptCfg 
{
   U8    cfgType;             /*!< Default/Explicit */
#ifdef NHU_VER2
   /* 
    * Changed union to struct as both aPeriodic and
    * periodic reporting mode can be configured simultaneously
    */
   struct
   {
      NhuCqiRptModeAprd       aPeriodicRpt;
      NhuCqiRptModePeriodic   periodicRpt;
   } reportMode;
#else /* NHU_VER2 */
   U8    reportingMode;       /*!< Reporting mode: Periodic/Aperiodic */
   union
   {
      NhuCqiRptModeAperiodic  aPeriodicRpt;
      NhuCqiRptModePeriodic   periodicRpt;
   } reportMode;
#endif /* NHU_VER2 */
#ifdef NHU_VER1
   NhuPmiRiRpt  pmiRiRpt;     /*!< Pmi Ri Report */
#endif /* NHU_VER1 */
} NhuCqiRptCfg;



/** @struct nhuPhyCfg 
    @brief  Physical layer Configuration for UE.
   @details This structure contains the explicit configuration information for
configuring the physical layer. RRC user provides this information.
*/
typedef struct nhuPhyCfg
{
   U8                  bitMask;        /*!< Bit mask */
   CmLteUeCategory     ueCategory;     /*!< UE category, setup/modify case */
   NhuPdschCfg         pdschCfg;       /*!< PDSCH configuration information */
   NhuDedPucchCfg      pucchCfg;       /*!< Per UE PUCCH configuration*/  
   NhuDedPuschCfg      puschCfg;       /*!< PUSCH configuration information */
   NhuCqiRptCfg        cqiCfg;         /*!< CQI reporting configuration information,
                                            valid only in setup case */
   NhuDedSRSUlCfg      srsUlCfg;       /*!< Per UE SRS configuration*/
   NhuDedSRCfg         srCfg;          /*!< Per UE SR configuration*/
   NhuDedAntCfgInfo    antCfg;         /*!< Dedicated antenna config,
                                            valid only in setup case */
}NhuPhyCfg;
#endif /* RRC_PHY_CFG_SUPP */

#ifdef LTE_ADV
/** @brief UE secondary cell config params to MAC*/
typedef struct nhuUeSCellInfo
{
  U16                  sCellId;         /*!< This will be secondary cellId */
  Inst                 macInst;          /*!< MAC instance for SCell */
  SuId                 rguUlSapId;             /*!< MAC-RLC UL Sap ID for SCell */
  SuId                 rguDlSapId;             /*!< MAC-RLC DL Sap ID for SCell */ 
}NhuUeSCellInfo;


/** @brief Configuration information of Secondary cells for a UE*/
typedef struct nhuUeSecCellInfo 
{
  U8                   numSCells;                        /*!< Number of SCells
                                                          */
  NhuUeSCellInfo       ueSCellCfg[NHU_MAX_SCELL_PER_UE]; /*!< Secondary cell 
                                                           configuration per UE */
}NhuUeSecCellInfo;

#endif /* LTE_ADV */
/**
 * @struct nhuLLyrSapIdInfo
    @brief  Msap Configuration.
   @details This structure contains the lower SAP configuration information during the multiple lower SAP support.
*/ 
#ifdef TENB_MULT_CELL_SUPPRT
typedef struct nhuUeLLyrSapIdInfo 
{
/* RRC-> RLC,MAC, PDCP */
   SuId        kwuSapId;      /*!< KWU SAP ID */
   SuId        ckwSapId;      /*!< CKW SAP ID */
   SuId        crgSapId;      /*!< CRG SAP ID */
   SuId        cpjSapId;      /*!< CPJ SAP ID */
   SuId        pjuSapId;      /*!< PJU SAP ID */
   SpId        macRguUlSapId;   /*!< MAC-RLC  , RGU SAP ID */
   SpId        macRguDlSapId;   /*!< MAC-RLC  , RGU SAP ID */
   SpId        rlcRguSapId;     /*!< MAC-RLC  , RGU SAP ID */
   SpId        rlcKwuUlSapId;   /*!< RLC-PDCP , KWU SAP ID */
   SpId        rlcKwuDlSapId;   /*!< RLC-PDCP , KWU SAP ID */
} NhuUeLLyrSapIdInfo;

/**
 * @struct nhuLLyrSapIdInfo
    @brief  Msap Configuration.
   @details This structure contains the lower SAP configuration information during the multiple
    lower/upper Sap between RLC-MAC-PDCP interfaces
*/ 
typedef struct nhuLLyrSapIdInfo 
{
   SuId        kwuSapId;      /*!< KWU SAP ID */
   SuId        ckwSapId;      /*!< CKW SAP ID */
   SuId        crgSapId;      /*!< CRG SAP ID */
   SuId        cpjSapId;      /*!< CPJ SAP ID */
   SuId        pjuSapId;      /*!< PJU SAP ID */

   SpId        rguUlSapId;  /* MAC-RLC RGU Interface SpId */
   SpId        rguDlSapId; /* MAC-RLC RGU Interface SpId */
   
   SpId        rguSapId;  /* RLC-MAC RGU SapId */
#ifdef RRC_PHY_CFG_SUPP
   SuId        ctfSapId;      /*!< CTF SAP ID */
#endif
} NhuLLyrSapIdInfo;
#endif

/**
 * @struct nhuUeCfgInfo
    @brief  UE Configuration.
    @details
-# This structure contains the configuration SDU as given by the RRC user to 
 request the RRC to configure the lower layers using NhUiNhuCfgReq.
-# It contains the explicit configuration information to be used. 
-# RRC processes the explicit configuration to derive information required 
   to configure the lower layers. 
-# The result of configuration is indicated in NhUiNhuCfgCfm. 
*/ 
typedef struct nhuUeCfgInfo        
{
   U8               conReCfgCause; /*!< NHU_CONN_RECFG_AT_HNDOVR: indicates that
                                         this configuration message is during
                                         handover and no "Selective Security 
                                         Mode Configuration" is to be 
                                         applied. 
                                         NHU_CONN_RECFG_AFTER_RESTBL: indicats 
                                         that this is first reconfiguration request
                                         after re-estblishment
                                         NHU_CONN_RESTB_EVNT */
   U8                ueCfgBitMsk;   /*!< Bitmask to know which configurations 
                                           are present */
   NhuRbCfgAllList   rbCfgAllList;  /*!< RB configuration information */
   NhuTrChCfg        trChCfg;       /*!< Transport Channel related 
                                         configuration */
   NhuSecurityCfg    secCfg;        /*!< Security configuration */
   NhuNewUeInfo      ueInfo;        /*!< This is present only when the RRC 
                                         user allocates a new CRNTI and all other
                                         layer needs to be reconfigured 
                                         with this */
#ifdef RRC_PHY_CFG_SUPP
   NhuPhyCfg         phyCfg;             /*!< Physical layer specific configuration */
#endif
#ifdef TENB_MULT_CELL_SUPPRT
   NhuUeLLyrSapIdInfo  uellyrSapIdInfo;  /*!< Lower SAP ID information */   
#endif
#ifdef LTE_ADV
  NhuUeSecCellInfo     ueSCellCfgInfo;    /*!< Secondary cell dedicated informaton
                                              per UE */
#endif
} NhuUeCfgInfo;

/** 
 * @struct nhuUlDcchMsg
    @brief  Uplink Dcch Message.
    @details This structure contains the UL-DCCH message to be sent to UE along with PDCP ID.
*/
typedef struct nhuUlDcchMsg
{
   U8                 pdcpId;       /*!< PDCP ID */
   NhuUL_DCCH_Msg     dcchMsg;      /*!< DL-DCCH SDU */
}NhuUlDcchMsg;

/**
 * @struct nhuDlDcchMsg
    @brief  Downlink Dcch Message.
    @details This structure contains the DL-DCCH message to be sent to UE along with the PDCP ID.
*/
typedef struct nhuDlDcchMsg
{
   U8              pdcpId;     /*!< PDCP ID */
   Bool            isMsgEncoded; /*!< Indicates whether the message is already encoded. 
                                   If encoded, RRC does not encode and directly 
                                   sends it to UE. This is required at source eNB 
                                   during handover because DL-DCCH (Recfg msg) is 
                                   encoded at target eNB and sent to source eNB in
                                   Handover Command as transparent container for 
                                   transmission to UE. RRC user at source eNB can 
                                   inform RRC to send this message to UE without 
                                   encoding(as it is already encoded) by setting 
                                   this flag. */
   union
   {
      NhuDL_DCCH_Msg     dcchMsg;    /*!< DL-DCCH SDU */
      Buffer             *mBuf;      /*!< Encoded DL-DCCH message. mBuf will 
                                       be present when isMsgEncded is set. */
   } m;
}NhuDlDcchMsg;

/**
 * @struct nhuDedMsg
    @brief  Dcch Message.
    @details
-# This structure contains the DCCH messages to be sent to UE.
-# The message is ASN encoded at RRC.
*/
typedef struct nhuDedMsg
{
   NhuDlDcchMsg        dlDcchMsg;     /*!< DL-DCCH SDU */
} NhuDedMsg;

/**
 * @struct nhuTimingInfo
    @brief  Timing Information.
    @details This structure contains the the Timing information such as sfn and subFrmNo.
*/
typedef struct nhuTimingInfo
{
   U16                sfn;                  /* System Frame Number */
   U8                 subframe;             /* Sub Frame Number */
} NhuTimingInfo;

/**
 * @struct nhuCmnMsgInfo
    @brief  Common Message Information.
 @details This structure contains the the common message information such as rbId,
   timing information, and PDU size.
*/
typedef struct nhuCmnMsgInfo
{
   U8                 rbId;       /*!< Radio Bearer ID */
   NhuTimingInfo      timingInfo; /*!< SFN and Sub Frame Number */
#ifndef NHU_VER2
   U32                tbsSize;    /*!< The size this message must use for transmission (in octets) */
#endif /* NHU_VER2 */
} NhuCmnMsgInfo;

/**
 * @struct nhuCmnMsg
    @brief  Common Message Type.
    @details
-# This structure contains the BCCH and PCCH messages to be sent to UE.
-# The message is ASN encoded at RRC.
-# Timing information and PDU size are passed to MAC for scheduling purpose.
*/
typedef struct nhuCmnMsg
{
   NhuCmnMsgInfo      cmnMsgInfo;     /*!< NHU common message information */
   U8                 cmnMsgCategory; /*!< PCCH/BCCH-BCH/BCCH-DLSCH */
   union
   {
      NhuPCCH_Msg          pcchMsg;       /*!< DL-PCCH-PCH SDU */
      NhuBCCH_BCH_Msg      bcchBchMsg;    /*!< DL-BCCH-BCH SDU */
      NhuBCCH_DL_SCH_Msg   bcchDlSchMsg;  /*!< DL-BCCH-DLSCH SDU */
   } cmn;
} NhuCmnMsg;

/**
 * @struct nhuDatReqUeMsg
    @brief  Data Request Information.
    @details
-# This structure contains the message to be sent to UE on the 
   @ref NhUiNhuDatReq primitive. 
-# It can be any of the message among messages on the 
   BCCH-BCH/BCCH-DL-SCH/PCCH/DCCH in the Downlink. 
-# The field msgCategory indicates one of these messages. 
-# This is processed at RRC to encode and send to the UE. 
-# This may/may not be associated with a configuration information to be 
   applied at eNodeB for the UE in NhUiNhuDatReq.
*/
typedef struct nhuDatReqUeMsg      
{
   Bool           isMsgDed;     /*!< Dedicated message present */
   union
   {
      NhuDedMsg   dedMsg;       /*!< Nhu dedicated message */
      NhuCmnMsg   cmnMsg;       /*!< Nhu common message */
   } msg;
} NhuDatReqUeMsg;


/**
 * @struct nhuDatReqSdus
    @brief  Data Request SDU.
    @details
-# This structure is an event structure which is used by the RRC user to trigger sending of 
an RRC message to UE also associated with configuration information for the lower layers at eNodeB. 
-# RRC in turn encodes the message in this event structure and sends to the peer whereas the configuration information is used to configure the lower layers at eNodeB.
-# RRC user may also use this event structure to send a RRC message to the UE 
when there is no associated configuration (for example, Downlink information transfer). 
-# The bitmask in the SDU structure indicates presence (absence) of its 
elements. However, the RRC user cannot use this event structure to configure 
the lower layers only. 
-# The SDU header typically is populated with UE ID, Cell ID, RB ID, PDCP ID, and Transaction ID.
*/
typedef struct nhuDatReqSdus      
{
   CmMemListCp          memCp;
   NhuHdr               hdr;         /*!< SDU Header */
   struct
   {
      NhuDatReqUeMsg   ueMsg;       /*!<  UE message to be sent */
      Bool             isUeCfgPres; /*!<  Bool indicates whether configuration
                                          is present */
      NhuUeCfgInfo     ueCfg;       /*!<  Configurations that must be 
                                          applied at the lower layers */
   } sdu;
} NhuDatReqSdus;

/**
 * @struct nhuUlCcchMsg
    @brief  Uplink CCCH Message.
    @details
-# This structure contains the UL-CCCH message to be sent to UE along with RB ID.
*/
typedef struct nhuUlCcchMsg
{
   U8                 rbId;      /*!< RB ID */
   NhuCrnti           tmpCrnti;  /*!< Temporary CRNTI */  
   NhuUL_CCCH_Msg     ccchMsg;   /*!< UL-CCCH SDU */
}NhuUlCcchMsg;

/**
 * @struct nhuDlCcchMsg
    @brief  Downlink CCCH Message.
    @details
This structure contains the DL-CCCH message to be sent to UE along with RB ID.
*/
typedef struct nhuDlCcchMsg
{
   NhuCrnti        tmpCrnti;                    /*!< Temporary CRNTI */
   U8              rbId;                        /*!< RB ID */
   NhuDL_CCCH_Msg  ccchMsg;                     /*!< DL-CCCH SDU */
}NhuDlCcchMsg;


/**
 * @struct nhuDatRspSdus
    @brief  Data Response SDU.
    @details
-# This event structure is used by the RRC user to send a RRC message to the UE. 
-# This message is sent in response to a request from the UE. 
-# This contains the Downlink CCCH/DCCH message. 
-# The SDU header is typically populated with UE ID, Cell ID, RB ID, PDCP ID, 
and Transaction ID.   
*/
typedef struct nhuDatRspSdus      
{
   CmMemListCp          memCp;
   NhuHdr               hdr;         /*!< SDU Header */
   struct
   {
      U8              msgCategory;       /*!< Message category */
      union
      {
         NhuDlCcchMsg     dlCcchMsg;    /*!< DL-CCCH Message */
         NhuDlDcchMsg     dlDcchMsg;    /*!< DL-DCCH SDU */
      } m;
      U8               isUeCfgPres;  /*!< Bitmask to indicate whether UeCfg is
                                          present or not */
      NhuUeCfgInfo     ueCfg;        /*!< Configurations that must be 
                                          applied at the lower layers */
   }sdu;
} NhuDatRspSdus;

/**
 * @struct nhuDatIndSdus
    @brief  Data Indication SDUs.
    @details
-# This event structure is used by RRC to pass the decoded message received 
on the uplink CCCH (DCCH) from UE to the RRC user. The SDU header is typically
populated with UE ID, Cell ID, RB ID (PDCP ID), and transId.
-# It contains errInfo structure to inform the RRC user about any kind errorneous 
     condition like Decoding Failure.
*/
typedef struct nhuDatIndSdus     
{
   CmMemListCp          memCp;
   NhuHdr               hdr;         /*!< SDU Header */
   NhuErrorInfo         err;         /*!< Error value */
   struct
   {
      U8              msgCategory;       /*!< Message category */
      union
      {
         NhuUlCcchMsg     ulCcchMsg;     /*!< UL-CCCH SDU */
         NhuUlDcchMsg     ulDcchMsg;     /*!< UL-DCCH SDU */
      } m;
   }sdu;
} NhuDatIndSdus;

/**
 * @enum nhuSysBw
 This enum describes the Downlink system bandwidth required for MIB.
*/
typedef enum nhuSysBw
{
   NHU_SYS_BW_N6 = 6,
   NHU_SYS_BW_N15 = 15,
   NHU_SYS_BW_N25 = 25,
   NHU_SYS_BW_N50 = 50,
   NHU_SYS_BW_N75 = 75,
   NHU_SYS_BW_N100 = 100
} NhuSysBw;

/* PHICH Configuration */

/**
 * @enum nhuPhichDur
   This enum contains the PHICH duration whether normal or extended.
*/
typedef enum nhuPhichDur
{
   NHU_PHICH_DUR_NORMAL,
   NHU_PHICH_DUR_EXTEND
} NhuPhichDur;

/**
 * @enum nhuPhichResrc
   This enum contains the PHICH resource (NG value) configurations.
*/
typedef enum nhuPhichResrc
{
   NHU_NG_ONESIXTH,
   NHU_NG_HALF,
   NHU_NG_ONE,
   NHU_NG_TWO
} NhuPhichResrc;

/**
 * @struct nhuPhichCfg
    @brief  Phich Configuration.
   @details This structure contains the PHICH configuration.
*/
typedef struct nhuPhichCfg
{
   NhuPhichResrc  resrc;      /*!< NG value for PHICH */
   NhuPhichDur    duration;  /*!< PHICH duration: TRUE-normal/FALSE-extended */
} NhuPhichCfg;

/**
 * @struct nhuPucchCfg
    @brief  Pucch Configuration.
  @details This structure contains the PUCCH configuration information.
It is used during the Cell configuration.
*/
typedef struct nhuPucchCfg
{
   U8                  pucchFixBw; /*!< PUCCH Resource Size or N^(2)_RB(in RBs)*/
   U16                 n1PucchAn;  /*!< N^(1)_PUCCH  */
   NhuPucchDeltaShift  deltaShift; /*!< PUCCH Delta Shift */
   U8                  cyclShift;  /*!< Cyclic Shift for PUCCH (N^(1)_CS): a
                                     value in range [0-7] */
}NhuPucchCfg;


/**
 * @enum nhuNumRaPreamble
  This enum contains the enumeration values for the Number of RA Preambles.
*/
typedef enum nhuNumRaPreamble
{
   NHU_RA_PREAMBLE_N4 = 4,
   NHU_RA_PREAMBLE_N8 = 8,
   NHU_RA_PREAMBLE_N12 = 12,
   NHU_RA_PREAMBLE_N16 = 16,
   NHU_RA_PREAMBLE_N20 = 20,
   NHU_RA_PREAMBLE_N24 = 24,
   NHU_RA_PREAMBLE_N28 = 28,
   NHU_RA_PREAMBLE_N32 = 32,
   NHU_RA_PREAMBLE_N36 = 36,
   NHU_RA_PREAMBLE_N40 = 40,
   NHU_RA_PREAMBLE_N44 = 44,
   NHU_RA_PREAMBLE_N48 = 48,
   NHU_RA_PREAMBLE_N52 = 52,
   NHU_RA_PREAMBLE_N56 = 56,
   NHU_RA_PREAMBLE_N60 = 60,
   NHU_RA_PREAMBLE_N64 = 64
} NhuNumRaPreamble;

/**
 * @enum nhuSizeRaPreambleGrpA
  This enum contains the enumeration values for the Preamble group size A.
*/
typedef enum nhuSizeRaPreambleGrpA
{
   NHU_SIZE_RA_PREAMBLE_GRPA_N4 = 4,
   NHU_SIZE_RA_PREAMBLE_GRPA_N8 = 8,
   NHU_SIZE_RA_PREAMBLE_GRPA_N12 = 12,
   NHU_SIZE_RA_PREAMBLE_GRPA_N16 = 16,
   NHU_SIZE_RA_PREAMBLE_GRPA_N20 = 20,
   NHU_SIZE_RA_PREAMBLE_GRPA_N24 = 24,
   NHU_SIZE_RA_PREAMBLE_GRPA_N28 = 28,
   NHU_SIZE_RA_PREAMBLE_GRPA_N32 = 32,
   NHU_SIZE_RA_PREAMBLE_GRPA_N36 = 36,
   NHU_SIZE_RA_PREAMBLE_GRPA_N40 = 40,
   NHU_SIZE_RA_PREAMBLE_GRPA_N44 = 44,
   NHU_SIZE_RA_PREAMBLE_GRPA_N48 = 48,
   NHU_SIZE_RA_PREAMBLE_GRPA_N52 = 52,
   NHU_SIZE_RA_PREAMBLE_GRPA_N56 = 56,
   NHU_SIZE_RA_PREAMBLE_GRPA_N60 = 60,
   NHU_SIZE_RA_PREAMBLE_GRPA_N64 = 64
} NhuSizeRaPreambleGrpA;

/**
 * @enum nhuPrmblRspWinSize
   This enum contains the enumeration values for the Preamble Response Window size.
*/
typedef enum nhuPrmblRspWinSize
{
   NHU_PRMBL_RSP_WIN_SIZE_SF2 = 2,
   NHU_PRMBL_RSP_WIN_SIZE_SF3 = 3,
   NHU_PRMBL_RSP_WIN_SIZE_SF4 = 4,
   NHU_PRMBL_RSP_WIN_SIZE_SF5 = 5,
   NHU_PRMBL_RSP_WIN_SIZE_SF6 = 6,
   NHU_PRMBL_RSP_WIN_SIZE_SF7 = 7,
   NHU_PRMBL_RSP_WIN_SIZE_SF8 = 8,
   NHU_PRMBL_RSP_WIN_SIZE_SF10 = 10
} NhuPrmblRspWinSize;

/** @enum nhuRaSfn
This enum contains the enumeration values for Random access system frame number.
*/
typedef enum nhuRaSfn
{
   NHU_SFN_EVEN,
   NHU_SFN_ANY,
   NHU_SFN_NA
} NhuRaSFN;

/**
 * @enum nhuDuplexMode
   This element enumerates the duplex modes supported, namely, TDD and FDD.
*/
typedef enum nhuDuplexMode
{
   NHU_MODE_FDD=1,   /*!< FDD mode */
   NHU_MODE_TDD      /*!< TDD mode */
} NhuDuplexMode;

/**
 * @struct nhuRaOccasion
    @brief  Random access occasions.
   @details This structure contains the Random access occasions.
*/
typedef struct nhuRaOccasion
{
   U8       size;         /*!< Size of the Sub Frame Number */
   NhuRaSFN sfnEnum;      /*!< System Frame Number */
   U8       subFrameNum[NHU_MAX_SUB_FRAME_NUM]; /*!< Maximum Sub Frame Numbers */
}NhuRaOccasion;

/**
 * @struct nhuRachCfg
    @brief  Rach Configuration.
   @details This structure contains the RACH configuration details which are 
configured during the establishment of a cell.
*/
typedef struct nhuRachCfg
{
   U8                    maxMsg3Tx;       /*!< Maximum number of message 3 transmissions */
}NhuRachCfg; 

/**
 * @struct nhuCmnMacCfg
    @brief  MAC common configuration.
   @details This structure contains the common channel configurations related 
            to MAC required during establishment of a cell on CRG interface.
*/
typedef struct nhuCmnMacCfg
{
   NhuRachCfg  rachCfg; /*!< Rach configuration */
} NhuCmnMacCfg;

/* nhu_x_001.main_3 : moving this out of PHY_SUPP as this is required 
                      by both MAC and PHY. */
/**
 * @struct nhuBwCfg
    @brief  Bandwidth Configuration.
   @details This structure contains the bandwidth configuration for both Downlink and Uplink direction.
*/
typedef struct nhuBwCfg
{
   NhuSysBw  ulSysBw;     /*!< Uplink system bandWidth configuration */
   NhuSysBw  dlSysBw;     /*!< Downlink system bandWidth configuration */

   /* nhu_x_001.main_3 : moving eUtraBand inside NhuCmnPhyCfg */
}NhuSysBwCfg;

#ifdef RRC_PHY_CFG_SUPP
/**
 * @struct nhuTxSchmCfg 
    @brief  Transmit schema Configuration.
   @details This structure contains the Transmit schema configuration.
*/
typedef struct nhuTxSchmCfg
{
   U8           scSpacing;         /*!< sub-carrier spacing, 
                                        refer nhu.h for values */
}NhuTxSchmCfg;

/**
 * @struct nhuCmnSrsUlCfg 
    @brief  Common SRS UL Configuration.
   @details This structure contains the common SRS UL configuration.
*/
typedef struct nhuCmnSrsUlCfg
{
   U8                srsCfgType; /*!< Setup/Release*/
   struct
   {
       NhuSrsBwCfgCmn        bwCfg;         /*!< SRS bandwidth config (0..7) */
       NhuSrsSubFrmCfg       subfrmCfg;     /*!< SRS sub-frame config (0..15) */
       Bool                  srsANSimultTx; /*!< simultaneous transmisson
                                               of SRS and ACK/NACK */
       Bool                  srsMaxUpPts;   /*!< SRS MaxUpPTS: TRUE/FALSE. 
                                                 This field is valid only in TDD */
   }setup;
}NhuCmnSrsUlCfg;

/**
 * @struct nhuCmnPdschCfg 
    @brief  Common PDSCH Configuration.
   @details This structure contains the common PDSCH configuration.
*/
typedef struct nhuCmnPdschCfg
{
   S8             refSigPower; /*!< provides downlink reference signal EPRE,
                                  in (-60..50)dBm */
   U8             pb;          /*!< (0..3)*/
}NhuCmnPdschCfg; 

/**
 * @struct nhuUlRefSigPUSCH 
    @brief  PUSCH UL Reference signal Configuration.
   @details This structure contains the PUSCH UL Reference signal configuration.
*/
typedef struct nhuUlRefSigPUSCH
{
   Bool        grpHoppngEnb;
   U8          grpAssignPUSCH; /*!< (0..29) */
   Bool        seqHoppingEnb;
   U8          cyclicShift; /*!< (0..7)*/
}NhuUlRefSigPUSCH;

/**
 * @struct nhuPrachCfg 
    @brief  Prach Configuration.
   @details This structure contains the PRACH configuration.
*/
typedef struct nhuPrachCfg
{
   U16      rootSequenceIndex;      /*!< (0..837) */   
   U8       prachCfgIndex;          /*!< PRACH Configuration Index, (0..63) */   
   U8       zeroCorrelationZoneCfg; /*!< (0..15), used for preamble sequence 
                                         generation (36.211, 5.7.2) */   
   Bool     highSpeedFlag;          /*!< TRUE: Restricted set, 
                                         FALSE: Unrestricted Set */   
   U8       prachFreqOffset;        /*!< (0..94) */ 
}NhuPrachCfg;

/**
 * @struct nhuPhyCellIdCfg 
    @brief  Physical cell Id structure.
   @details This structure contains physical cell identities.
*/
typedef struct nhuPhyCellIdCfg
{
   U8                cellIdGrpId;/*!< Cell Identity Group Id (0..167) */   
   U8                physCellId; /*!< Cell Id (0..2) */
}NhuPhyCellIdCfg;

/**
 * @struct nhuCmnPuschCfg 
    @brief  Common PUSCH Configuration.
   @details This structure contains the common PUSCH configuration.
*/
typedef struct nhuCmnPuschCfg
{
   U8                nSB;                 /*!< (1..4) */
   U8                hoppingMode;         /*!< Hopping mode */
   U8                puschHoppingOffset;  /*!< (0..98) */
   Bool              enable64QAM;         /*!< TRUE:enabled, FALSE:disabled*/
   NhuUlRefSigPUSCH  refSig;
}NhuCmnPuschCfg;

/**
 * @struct nhuTddSfCfgInfo 
    @brief  TDD subframe Configuration.
   @details This structure contains the TDD subframe configuration.
*/
typedef struct nhuTddSfCfgInfo
{
   U8    sfAssignment;     /*!< UL-DL subframe assignment: (0..6),
                                36.211, Table 4.2-2 */
   U8    spclSfPatterns;   /*!< Special subframe configuration: (0..8),
                                36.211, Table 4.2-1 */

}NhuTddSfCfgInfo;


/* nhu_x_001.main_3 - moving this structure out of PHY_SUPP */


/**
 * @struct nhuCmnPhyCfg 
    @brief  Common Physical channel Configuration.
   @details This structure contains the Common Physical channel configuration.
*/
typedef struct nhuCmnPhyCfg
{
   NhuPhyCellIdCfg  pcellCfg;       /*!< Physical cell Id configuration*/
   U8               numOfTxAnt;     /*!< Number of Antenna ports */
   /* nhu_x_001.main_3 - moving NhuSysBwCfg outside this structure. 
                         Retaining eUtraBand */
   U8               eUtraBand;      /*!< EUTRA Operating Band - 36.104 (5.5).
                                         FDD:(1..14), TDD:(33..40) */
   NhuTxSchmCfg     schmCfg;        /*!< Basic transmission scheme configuration */
   U8               bitmask;        /*!< Bit mask */
   NhuPrachCfg      prachCfg;       /*!< PRACH configuration information */
   NhuCmnPdschCfg   cmnPdschCfg;    /*!< COMMON PDSCH configuration information */
   NhuCmnPuschCfg   cmnPuschCfg;    /*!< COMMON PUSCH configuration information */
   NhuPhichCfg      cmnPhichCfg;    /*!< PHICH configuration */
   NhuPucchCfg      cmnPucchCfg;    /*!< PUCCH configuration */
   NhuCmnSrsUlCfg   srsUlCfg;       /*!< COMMON UL SRS configuration information */
   NhuTddSfCfgInfo  tddSfCfg;       /*!< SubFrame Configuration for TDD */
}NhuCmnPhyCfg;

/**
 * @struct nhuCmnPhyRecfg 
    @brief Common Physical Channel Reconfiguration.
   @details This structure contains the Common Physical channel configuration
            for reconfiguration.
*/
typedef struct nhuCmnPhyRecfg
{
   CmLteTimingInfo  actvTime;       /*!< Activation time - cell reconfiguration only*/
   U8               bitmask;        /*!< Bit mask */
   NhuPrachCfg      prachCfg;       /*!< PRACH configuration information */
   NhuCmnPdschCfg   cmnPdschCfg;    /*!< COMMON PDSCH configuration information */
   NhuCmnPuschCfg   cmnPuschCfg;    /*!< COMMON PUSCH configuration information */
   NhuPhichCfg      cmnPhichCfg;    /*!< PHICH configuration */
   NhuPucchCfg      cmnPucchCfg;    /*!< PUCCH configuration */
   NhuCmnSrsUlCfg   srsUlCfg;       /*!< COMMON UL SRS configuration information */
   NhuTddSfCfgInfo  tddSfCfg;       /*!< SubFrame Configuration for TDD */
}NhuCmnPhyRecfg;
#endif /* RRC_PHY_CFG_SUPP */

/**
 * @struct nhuCellCfgInfo
    @brief  Cell Configuration.
    @details
-# This structure contains the cell configuration information which comprises 
of all the common radio bearers (example: CCCH), logical channels, and the 
associated transport channels for both Uplink and Downlink. 
-# Once the configuration is successful at RRC, all the uplink and downlink 
activities supported in a cell are possible. 
-# The field cellCfgBitMsk indicates the other fields present in this structure.
*/
typedef struct nhuCellCfgInfo     
{
   NhuDuplexMode    duplexMode;     /*!< Duplex mode - TDD/FDD */
   /* nhu_x_001.main_3 - moving this info outside, as it is required by both MAC
                         and PHY */
   NhuSysBwCfg      sysBwCfg;       /*!< Bandwidth configuration */
   U8               cellCfgBitMsk;  /*!< Bitmask indicates the presence of 
                                         Cell configuration information */
   NhuRbCfgList     rbToAddCfgList; /*!< RB configuration information */
   NhuCmnMacCfg     macCmnCfg;      /*!< MAC common configuration information */
#ifdef RRC_PHY_CFG_SUPP
   NhuCmnPhyCfg     phyCellCfg;     /*!< Physical layer cell configuration */
#endif
#ifdef TENB_MULT_CELL_SUPPRT
   NhuLLyrSapIdInfo llyrSapIdInfo;  /*!< Lower SAP ID information */   
#endif
} NhuCellCfgInfo;

/**
 * @struct nhuCellReCfgInfo
    @brief Cell Reconfiguration.
    @details
-# This structure contains the cell reconfiguration information.
-# Once the configuration is successful at RRC, all the uplink and downlink 
activities supported in a cell are possible. 
-# The field cellCfgBitMsk indicates the other fields present in this structure.
*/
typedef struct nhuCellReCfgInfo     
{
   CmLteTimingInfo  actvnTime;      /*!< Activation time, only SFN is valid */
   U8               cellCfgBitMsk;  /*!< Bitmask indicates the presence of 
                                         Cell configuration information */
   NhuCmnMacCfg     macCmnCfg;      /*!< MAC common configuration information */
#ifdef RRC_PHY_CFG_SUPP
   NhuCmnPhyRecfg   phyCellCfg;     /*!< Physical layer cell configuration */
#endif
} NhuCellReCfgInfo;

/**
 * @struct nhuCellRlsInfo
    @brief  Cell Configuration release.
    @details This structure contains the cell configuration release information.
*/
typedef struct nhuCellRlsInfo     
{
   NhuCellId      cellId;   /*!< Cell ID */
} NhuCellRlsInfo;


/**
 * @struct nhuCellCfgReqSdus
    @brief  Cell Configuration Request SDU.
   @details This sturucture contains the cell configuration SDU used for configuring a 
Cell-specific logical and transport channels. The configurations can be modified 
and also released whenver the RRC user decides to do so. RRC user must set 
appropriate value of the cfgType.
*/
typedef struct nhuCellCfgReqSdus 
{
   CmMemListCp     memCp;
   NhuHdr          hdr;          /*!< SDU Header */
   struct
   {
      U8              cfgType;   /*!< Setup/Modify/Release */
      union
      {
         NhuCellCfgInfo    cfgInfo;    /*!< Cell configuration information */
         NhuCellReCfgInfo  reCfgInfo;  /*!< Cell reconfiguration information */
         NhuCellRlsInfo    rlsInfo;    /*!< Cell configuration release information */
      } u;
   } sdu;
} NhuCellCfgReqSdus;

/**
 * @struct nhuCellCfgCfmSdus
    @brief  Cell Configuration Confirm SDU.
   @details This structure contains the result of a cell configuration as 
requested by the Cell configuration request primitive. The confirm SDU is sent in 
NhUiNhuCellCfgCfmSdus. 
*/
typedef struct nhuCellCfgCfmSdus 
{
   NhuHdr            hdr;          /*!< SDU Header */
   struct
   {
      Bool           isCfgSuccess; /*!< Success/failure */    
      NhuErrorInfo   cfgError;     /*!< Valid only when the result is failure */
   } sdu;
} NhuCellCfgCfmSdus;

/**
 * @struct nhuStaIndSdus
    @brief  Status Indication SDU.
    @details
-# This structure contains the status information for UL-DCCH RRC messages. The
status is indicated to the RRC user in NhUiNhuStaInd.
-# This is used by RRC to indicate to the RRC user of any errors occurred during
reception of UL RRC messsages at PDCP with deciphering failure or integrity
verification failure.
-# Based on the information present in this SDU, the RRC user might choose to take
different actions. 
*/
typedef struct nhuStaIndSdus          
{
   NhuHdr               hdr;              /*!< SDU Header */
   U8                   pdcpId;           /*!< PDCP ID */
   U8                   cause;            /*!< Failure Cause */
} NhuStaIndSdus;

/**
 * @struct nhuDatCfmSdus
    @brief  Data Confirm SDU.
@details
-# This structure contains the status information for DL-DCCH RRC messages. The
status is indicated to the RRC user in NhUiNhuDatCfm.
-# This is used by RRC to indicate to the RRC user of any errors occurred during
PDCP or RLC transmission of the DL-DCCH RRC message. The error causes are:
 -# RLC maximum transmissions reached, but the message is not sent to UE.
 -# PDCP SDU discard timer expired before sending the message to UE.
-# Based on the information present in this SDU, the RRC user might choose to take
different actions. 
*/
typedef struct nhuDatCfmSdus          
{
   NhuHdr               hdr;              /*!< SDU Header */
   U8                   pdcpId;           /*!< PDCP ID */
   U8                   datCfmStatus;     /*!< Data Confirm Status */
} NhuDatCfmSdus;

/**
 * @struct nhuErrIndSdus
    @brief  Error Indication SDU.
    @details
-# This structure contains the error information to be indicated to the RRC 
user in NhUiNhuErrInd.
-# This is used by RRC to indicate to the RRC user of any errors occurred during
the processing of primitives received from the RRC user to RRC.
-# Based on the information present in this SDU, the RRC user might choose to take 
different actions. 
*/
typedef struct nhuErrIndSdus          
{
   NhuHdr               hdr;              /*!< SDU Header */
   NhuErrorInfo         sdu;              /*!< RRC error */
} NhuErrIndSdus;

/**
 * @struct nhuCfgReqSdus
    @brief  Configuration Request SDU.
    @details
-# This structure contains the configuration SDU as given by the RRC user to 
request RRC to configure the lower layers using NhUiNhuCfgReq. 
-# It can contain explicit configuration information to be used.
-# The RRC processes the explicit configuration to derive information required 
to configure the lower layers. 
The result of configuration is indicated in NhUiNhuCfgCfm. 
*/
typedef struct nhuCfgReqSdus        
{
   CmMemListCp      memCp;
   NhuHdr           hdr;         /*!< SDU Header */
   NhuUeCfgInfo     cfgInfo;     /*!< Configuration information */
} NhuCfgReqSdus;

/**
 * @struct nhuCfgCfmSdus
    @brief  Configuration Confirm SDU.
  @details This structure contains the RRC user configuration information as reported 
by RRC to the RRC user in response to the configuration request.
*/
typedef struct nhuCfgCfmSdus    
{
   NhuHdr             hdr;          /*!< SDU Header */
   struct
   {
      Bool            isCfgSuccess; /*!< Success/failure */
      NhuErrorInfo    cfgError;     /*!< Valid only when the result is failure */
   } sdu;
} NhuCfgCfmSdus;

/**
 * @struct nhuEncSdusReq
   @brief  Encode RRC message Request.
   @details This structure contains the message structure which RRC encodes.
     It supports encoding of the following messages:
     -# DL-DCCH Message - This must contain RRC Connection Reconfiguration message. This is required because, during handover to E-UTRAN, this message is sent to UE via other RAT. The source eNB sends this message to UE. 
     -# Handover Command Message - Contains the entire DL-DCCH message including the RRCConnectionReconfiguration message used to perform handover to E-UTRAN, generated (entirely) by the target eNB. This message is encoded by the target eNB and decoded at source eNB.
     -# UE Radio Access Capability Information - This message is used to transfer UE radio access capability information. Encoding this is supported, as eNB sends this as transparent container in UE CAPABILITY INFO INDICATION message to MME.
     -# UE Capability Information - This message is used to transfer UE capability information message sent by UE including E-UTRA, GERAN, UTRA, and CDMA2000-1xRTT Bandclass radio access capabilities (separated). Encoding is supported as this is sent as octet string in UE Radio Access Capability Information message. This is the message received from UE.
     -# Handover Preparation Message - This message is used to transfer the E-UTRA RRC information used by the target eNB during handover preparation, including UE capability information.
*/
typedef struct nhuEncSdusReq            
{
   CmMemListCp   memCp;                 /*!< Memory Control point for Sdu */
   NhuHdr        hdr;                   /*!< NHU header for the request */
   struct                              
   {
      U8         msgCategory;           /*!< Message category */
      union                             /*!< Pdu to be encoded */
      {
         NhuDL_DCCH_Msg          dcchMsg;        /*!< DL-DCCH SDU */
         NhuHovrCmd              hovrCmd;        /*!< Handover Command */
         NhuUERadioAccessCapInfo ueRadioCapInfo; /*!< UE Radio Access Capability 
                                                      -formation */
         NhuUECapInfo            ueCapInfo;      /*!< UE Capability information 
                                                      including E-UTRA, GERAN, 
                                                      UTRA and CDMA2000-1xRTT 
                                                      Bandclass radio access 
                                                      capabilities */
         NhuHovrPrepInfo         hovrPrepInfo;   /*!< Handover Preparation Information */
         /* IRAT_HO */
         NhuToTgtRNC_Cont        nhuIntRatHoInfoWithUeCap; /* hoToUTRAN RRC Cont */
/* nhu_x_001.main_4: octect aligned encoding of ShortMAC-Input */
#ifdef NHU_VER2
         NhuVarShortMAC_Input    varShortMacInput; /*!< VarShortMAC-Input */
#endif /* NHU_VER2 */
      } u;
   }sdu;
}NhuEncReqSdus;

/**
 * @struct nhuEncSdusCfm
   @brief  Encode RRC message Confirm. 
   @details This structure contains the encoded RRC message in mBuf.
*/
typedef struct nhuEncSdusCfm    
{
   NhuHdr        hdr;           /*!< NHU header for the request */
   struct
   {
      U8         msgCategory;   /*!< Message category */
      U32        msgLen;        /*!< size of encoded data in bits */
      Status     status;        /*!< status of encode */
      Buffer     *mBuf;         /*!< encoded data */
   } sdu;
} NhuEncCfmSdus;

/**
 * @struct nhuRcvStaOfUlPdcpSdus 
   @brief  Receive status of the UL PDCP SDUs.
   @details This structure contains the Receive status of the UL PDCP SDUs and number of bits indicating the status. The MSB of the first octet of the ulBitMap indicates whether or not the PDCP SDU with the SN (FMS + 1) modulo 4096 is received. The LSB of the first octet of the ulBitMap indicates whether or not the PDCP SDU with the SN (FMS + 8) modulo 4096 is received correctly.
 
*/
typedef struct nhuRcvStaOfUlPdcpSdus
{
   U16    numBits;                /*!< Number of bits in UL bitmap */
   U8    *ulBitMap;              /*!< string which indicates receive status of PDCP SDUs */
} NhuRcvStaOfUlPdcpSdus;

/**
 * @struct nhuPdcpSduStaInfo 
   @brief  PDCP SN Status Information.
   @details This structure contains PDCP SN status values required to support data forwarding.
*/
typedef struct nhuPdcpSduStaInfo
{
   U8  drbId;          /*!< Data RbId */
   U8  dir;            /*!< Direction of the RB */
   U8  snLen;          /*!< PDCP-SN length 12/15 bits */
   U32 ulCountVal;     /*!< PDCP-SN and HFN of first missing UL PDCP SDU */
   U32 dlCountVal;     /*!< PDCP-SN and HFN that the target must 
                                    assign for the next DL SDU not having an SN yet */
   NhuRcvStaOfUlPdcpSdus rcvStaOfUlPdcpSdus; /*!< PDCP Sequence Number = 
                                                  (First Missing SDU Number + bit position)
                                                  modulo 4096 */
} NhuPdcpSduStaInfo;

/**
 * @struct nhuPdcpSduStaCfm
   @brief  PDCP SDU Status Confirm.
   @details This structure contains list of PDCP SDU status parameters for all data radio bearers established for UE. This is required to support data forwarding during handover from E-UTRAN.
*/
typedef struct nhuPdcpSduStaCfm
{
   CmMemListCp        memCp;
   NhuHdr             hdr;               /*!< NHU Header */
   U16                numRbId;           /*!< Number of Radio bearers */
   NhuPdcpSduStaInfo  *pdcpSduStaInfo;   /*!< List of PDCP SDU Status
                                              parameters for numRbId */
   Status             status;            /*!< Status - ROK or RFAILED */
   Reason             reason;            /*!< Reason for failure */ 
} NhuPdcpSduStaCfm;


/**
 * @struct nhuPdcpDatResumeCfm
   @brief  PDCP Data Resume Confirm.
   @details This structure contains list of PDCP SDU status parameters for Data Resume Confirm from PDCP. 
*/
typedef struct nhuPdcpDatResumeCfm
{
   CmMemListCp        memCp;
   NhuHdr             hdr;               /*!< NHU Header */
   Status             status;            /*!< Status - ROK or RFAILED */
   Reason             reason;            /*!< Reason for failure */ 
} NhuPdcpDatResumeCfm;
/**
  * @struct nhuDecodeSduReq
    @brief  Decode E-UTRAN/UTRAN Capability Infromation and Handover Preparation Information.  
    @details This structure contains the UE capability information and Handover Preparation Information to be decoded.
*/

typedef struct nhuDecodeSduReq
{
   NhuHdr   hdr;        /*!< NHU Header */
   U16      sduType;    /*!< Type of the IE or messaage that needs to be decoded */
   Buffer   *mbuf;      /*!< Encoded data */
} NhuDecodeSduReq;

/**
  * @struct nhuDecode3GUECapOctStr
    @brief  Decoded UTRAN Capability Information and UTRA Handover related messages. 
    @details This structure contains the decoded UE capability information and Handover Preparation Information.
*/

#if 0 /* IRAT_HO : Not required */
typedef struct nhuDecode3GUECapOctStr
{
   U8       containsUECap; /* If TRUE, then its element nhuUE_UTRACap is valid */
   NhuUTRANInterRATHovrInfo      nhuUE_UTRAHovrInfo; /* UTRA Inter-RAT Handover Message */
   NhuUTRANUE_RadioAccessCapInfo nhuUE_UTRACap; /* UTRA UE Capability Information */
}NhuDecode3GUECapOctStr;
#endif

/**
  * @struct nhuDecodeSduCfm
    @brief  Decoded E-UTRAN/UTRAN Capability Information and Handover related messages. 
    @details This structure contains the decoded UE capability information and Handover related messages.
*/

typedef struct nhuDecodeSduCfm
{
   CmMemListCp    memCp;
   NhuHdr         hdr;               /*!< NHU Header */
   U16            sduType;
   Bool           status;
   union
   {
         NhuUE_EUTRA_Cap   nhuUE_EUTRA_Cap;   /*!< Decoded E-UTRA UE Capability. */
         NhuHovrCmd      hovrCmd;         /*!< Handover Command. Decode required at source eNB/RAN. */
         NhuUECapInfo    ueCapInfo;       /*!< UE Capability information including E-UTRA, GERAN, UTRA and CDMA2000-1xRTT Bandclass radio access capabilities. Decode required when EPC sends this message to eNB in NhuUERadioAccessCapInfo structure. */
         NhuHovrPrepInfo nhuHovrPrepInfo; /*!< Decoded Handover Preparation Information. Decode required at target eNB. */
         NhuUERadioAccessCapInfo ueRadioCapInfo; /*!< Decoded UE Radio Access Capability Information. Decode required when EPC sends this message to eNB. */
         /* SPS changes starts */
         NhuUE_EUTRA_Cap_v9a0_IEs  eUTRA_Cap_v9a0;
         /* SPS changes ends */
         /* IRAT_HO */
         NhuToTgtRNC_Cont nhuIntRatHoInfoWithUeCap;
   }ie;
} NhuDecodeSduCfm;

/**
  * @struct nhuDRBCountInfo
    @brief Count values of a DRB.  
    @details This structure contains UL and DL count values of one DRB.
*/

typedef struct nhuDRBCountInfo
{
   U8    drbId;         /*!< DRB Identity */
   U8    drbDirection;  /*!< DRB direction, specifically in case of UM */
   U32   ulCount;       /*!< UL Count value*/
   U32   dlCount;       /*!< DL count value*/
} NhuDrbCountInfo;

/**
  * @struct nhuDRBCountInfoLst
    @brief Count values for list of DRBs.  
    @details This structure contains count values for one or more number of DRBs.
*/

typedef struct nhuDRBCountInfoLst
{
   CmMemListCp    memCp;
   NhuHdr   countHdr;
   U8       numDrbs;         /*!< Number of DRBs in this list*/
   U8       status;
   NhuDrbCountInfo *member;         /*!< DRB count information element*/
} NhuDRBCountInfoLst;


typedef S16 (*NhuBndReq)    ARGS((
               Pst          *pst,     /* Post structure */
               SuId         suId,     /* NHU serivce user SAP ID */ 
               SpId         spId));   /* NHU SAP ID */

typedef S16 (*NhuBndCfm)    ARGS((
               Pst          *pst,     /* Post structure */       
               SuId         suId,     /* NHU service user SAP ID */
               U8           status)); /* Status structure for Bind confirm */

typedef S16 (*NhuUbndReq)   ARGS((
               Pst          *pst,     /* Post structure */
               SpId         spId,     /* NHU SAP ID */
               Reason       reason)); /* Reason for Unbind */

typedef S16 (*NhuDatReq)    ARGS((
               Pst            *pst,            /* Post structure */
               SpId           spId,            /* RRC service provider SAP ID */
               NhuDatReqSdus  *nhuDatReqSdus  /* SDU */
               ));

typedef S16 (*NhuDatRsp)    ARGS((
               Pst            *pst,            /* Post structure */
               SpId           spId,            /* RRC service provider SAP ID */
               NhuDatRspSdus  *nhuDatRspSdus  /* SDU */
               ));


typedef S16 (*NhuDatInd)    ARGS((
               Pst            *pst,            /* Post structure */
               SuId           suId,            /* RRC service user SAP ID */
               NhuDatIndSdus  *nhuDatIndSdus  /* SDU */
               ));

typedef S16 (*NhuDatCfm)    ARGS((
               Pst               *pst,          /* Post structure */
               SuId              suId,          /* RRC service user SAP ID */
               NhuDatCfmSdus     *nhuDatCfmSdus /* SDU */
               ));
typedef S16 (*NhuStaInd)    ARGS((
               Pst               *pst,          /* Post structure */
               SuId              suId,          /* RRC service user SAP ID */
               NhuStaIndSdus     *nhuStaIndSdus /* SDU */
               ));

typedef S16 (*NhuErrInd)    ARGS((
               Pst            *pst,            /* Post structure */
               SuId           suId,            /* RRC service user SAP ID */
               NhuErrIndSdus  *nhuErrIndSdus  /* SDU */
               ));

typedef S16 (*NhuCfgReq)    ARGS((
               Pst            *pst,            /* Post structure */
               SpId           spId,            /* RRC service provider SAP ID */
               NhuCfgReqSdus  *nhuCfgReqSdus  /* SDU */
               ));

typedef S16 (*NhuCfgCfm)    ARGS((
               Pst            *pst,            /* Post structure */
               SuId           suId,            /* RRC service user SAP ID */
               NhuCfgCfmSdus  *nhuCfgCfmSdus  /* SDU */
               ));

typedef S16 (*NhuCnclUeReq)    ARGS((
               Pst            *pst,            /* Post structure */
               SpId           spId,            /* RRC service provider SAP ID */
               NhuCellId      cellId,
               NhuCrnti       crnti
               ));

typedef S16 (*NhuCellCfgReq)    ARGS((
               Pst            *pst,            /* Post structure */
               SpId           spId,            /* RRC service provider SAP ID */
               NhuCellCfgReqSdus   *nhuCellCfgReqSdus  /* SDU */
               ));

typedef S16 (*NhuCellCfgCfm)    ARGS((
               Pst            *pst,            /* Post structure */
               SuId           suId,            /* RRC service user SAP ID */
               NhuCellCfgCfmSdus   *nhuCellCfgCfmSdus  /* SDU */
               ));

typedef S16 (*NhuDeleteTransReq)    ARGS((
               Pst            *pst,            /* Post structure */
               SpId           spId,            /* RRC service provider SAP ID */
               NhuCellId      cellid,
               NhuCrnti       ueId,            /* Ue ID */
               U32            transId          /* Transaction ID */
               ));

typedef S16 (*NhuEncReq)    ARGS((
               Pst            *pst,            /* Post structure */
               SpId           spId,            /* RRC service provider SAP ID */
               NhuEncReqSdus  *nhuEncReqSdus   /* RRC SDU to be encoded */
               ));

typedef S16 (*NhuEncCfm)    ARGS((
               Pst            *pst,            /* Post structure */
               SuId           suId,            /* RRC service user SAP ID */
               NhuEncCfmSdus  *nhuEncCfmSdus   /* Encoded RRC SDU */
               ));

typedef S16 (*NhuSduStaReq)    ARGS((
               Pst            *pst,            /* Post structure */
               SpId           spId,            /* RRC service provider SAP ID */
               NhuHdr         hdr              /* SDU Header */
               ));

typedef S16 (*NhuSduStaCfm)    ARGS((
               Pst            *pst,            /* Post structure */
               SuId           suId,            /* RRC service user SAP ID */
               NhuPdcpSduStaCfm *pdcpSduStaCfm /* PDCP SDU Status Confirm */
               ));

typedef S16 (*NhuDecodeReq)    ARGS((
               Pst            *pst,            /* Post structure */
               SpId           spId,            /* RRC service provider SAP ID */
               NhuDecodeSduReq *nhuDecodeSduReq  /* Message that needs to be decoded */
               ));

typedef S16 (*NhuDecodeCfm)    ARGS((
               Pst            *pst,            /* Post structure */
               SuId           suId,            /* RRC service user SAP ID */
               NhuDecodeSduCfm *nhuDecodeSduCfm  /* Decoded Message */
               ));

typedef S16 (*NhuCountReq)    ARGS((
               Pst            *pst,            /* Post structure */
               SpId           spId,            /* RRC service provider SAP ID */
               NhuHdr         *countHdr        /* Header contained UeID, CellId, and TransID */
               ));

typedef S16 (*NhuCountCfm)    ARGS((
               Pst            *pst,            /* Post structure */
               SuId           suId,            /* RRC service provider SAP ID */
               NhuDRBCountInfoLst   *nhuDRBCountInfoLst      /* List of DRBs along with Count values of each of them */
               ));

typedef S16 (*NhuDataFwdReq)    ARGS((
               Pst            *pst,            /* Post structure */
               SpId           spId,            /* RRC service provider SAP ID */
               NhuHdr         dataFwdHdr      /* Header contained UeID, CellId, and TransID */
               ));

typedef S16 (*NhuDatResumeReq)    ARGS((
               Pst            *pst,            /* Post structure */
               SpId           spId,            /* RRC service provider SAP ID */
               NhuHdr         dataFwdHdr        /* Header contained UeID, CellId, and TransID */
               ));

typedef S16 (*NhuDatResumeCfm)    ARGS((
               Pst            *pst,            /* Post structure */
               SuId           suId,            /* RRC service user SAP ID */
               NhuPdcpDatResumeCfm *pdcpDatResumeCfm /* PDCP Data Resume Confirm */
               ));

#ifdef NX /* For RRC User */
   EXTERN S16 NxLiNhuBndCfm ARGS((Pst *pst, SuId suId, U8 status));
   EXTERN S16 NxLiNhuDatCfm ARGS((Pst *pst, SuId suId, 
                                  NhuDatCfmSdus *nhuDatCfmSdus)); 
   EXTERN S16 NxLiNhuStaInd ARGS((Pst *pst, SuId suId, 
                                  NhuStaIndSdus *nhuStaIndSdus)); 
   EXTERN S16 NxLiNhuDatInd ARGS((Pst *pst, SuId suId, NhuDatIndSdus *nhuDatIndSdus));
   EXTERN S16 NxLiNhuErrInd ARGS((Pst *pst, SuId suId, NhuErrIndSdus *nhuErrIndSdus));
   EXTERN S16 NxLiNhuCfgCfm ARGS((Pst *pst, SuId suId, NhuCfgCfmSdus *nhuCfgCfmSdus));
   EXTERN S16 NxLiNhuCellCfgCfm ARGS((Pst *pst, SuId suId, NhuCellCfgCfmSdus *nhuCellCfgCfmSdus));
   EXTERN S16 NxLiNhuEncodeCfm ARGS((Pst *pst, SuId suId, NhuEncCfmSdus *nhuEncCfmSdus));
   EXTERN S16 NxLiNhuPdcpSduStaCfm ARGS((Pst *pst, SuId suId, 
                                         NhuPdcpSduStaCfm *nhuPdcpSduStaCfm));
   EXTERN S16 NxLiNhuDecodeCfm ARGS((Pst *pst, SuId suId, NhuDecodeSduCfm *nhuDecodeSduCfm));
   EXTERN S16 NxLiNhuCountCfm ARGS((Pst *pst, SuId suId, NhuDRBCountInfoLst *nhuDRBCountInfoLst));
   EXTERN S16 NxLiNhuPdcpDatResumeCfm ARGS((Pst *pst, SuId suId, 
                                         NhuPdcpDatResumeCfm *nhuPdcpDatResumeCfm));

#endif /* NX */
   
#ifdef NH
   
   /* RRC to RRC user */

/** 
@brief Data Indication to RRC User.
@details 
* This primitive is used to indicate the RRC user about the uplink message.
* @param[in]  pst Pointer to the post structure. System
services uses pst for loosely coupled intertask communication.
* @param[in]  suId The service user SAP ID.
* @param[in]  nhuDatIndSdus Pointer to the data indication SDU
structure containing the decoded message from UE.
*
* @return S16
*  -# ROK
*  -# RFAILED
*/   

   EXTERN S16 NhUiNhuDatInd ARGS((Pst *pst, SuId suId, NhuDatIndSdus *nhuDatIndSdus));

/** 
@brief Error Indication to RRC User.
@details 
* This primitive is used to indicate an error to the RRC user (NHU). Each error is
* coded into an error type and a cause. A set of errors ranging from RRC 
internal errors, protocol related errors, invalid parameter errors, and so on 
are defined. RRC user based on these error types and causes can take 
relevant action to counterfeit any error scenario. If an error indication 
results in response to an operation triggered by the RRC user, then the 
corresponding transaction identifier is expected in the primitive
header. UE ID, Cell ID, are also expected in the primitive header.

RRC allocates the @ref nhuErrIndSdus and the RRC user needs to free this buffer.

* @param[in]  pst Pointer to the post structure. System
services uses pst for loosely coupled intertask communication.
* @param[in]  suId The service user SAP ID.
* @param[in]  nhuErrIndSdus Pointer to the error indication SDU structure.
*
* @return S16
*  -# ROK
*  -# RFAILED
*/   
   EXTERN S16 NhUiNhuErrInd ARGS((Pst *pst, SuId suId, NhuErrIndSdus *nhuErrIndSdus));

/** 
@brief Configuration Confirm to RRC User.
@details 
* This primitive is used to indicate the status of configuration done at
* the lower layers (MAC, RLC, and PDCP) to the RRC user in response to a 
configuration request. This primitive contains the success (failure) 
information. A configuration is treated as success, only if it is successful 
at all the lower layers. The primitive header contains the transaction 
identifier that is received in the request and the UE ID.
* @param[in]  pst Pointer to the post structure. System
services uses pst for loosely coupled intertask communication.
* @param[in]  suId The service user SAP ID.
* @param[in]  nhuCfgCfmSdus Pointer to the lower layer configuration status SDU structure.
*
* @return S16
*  -# ROK
*  -# RFAILED
*/      
   EXTERN S16 NhUiNhuCfgCfm ARGS((Pst *pst, SuId suId, NhuCfgCfmSdus *nhuCfgCfmSdus));

/**
@brief Cell Configuration Confirm to RRC User.
@details 
* This primitive is used to provide the RRC user with the status of 
configuration at the lower layers during the Cell establishment. 
The primitive carries the success (failure) information of the configuration 
transaction. The configuration is treated as success
only if the configurations at all the lower layers are successful. 
The primitive header contains the transaction identifier and the cell identifier as mentioned in the cell configuration request.
* @param[in]  pst Pointer to the post structure. System
services uses pst for loosely coupled intertask communication.
* @param[in]  suId The service provider SAP ID. 
* @param[in]  nhuCfgCellCfmSdus Pointer to the configuration status for the cell.
*
* @return S16
*  -# ROK
*  -# RFAILED
*/   
   EXTERN S16 NhUiNhuCellCfgCfm ARGS((Pst *pst, SuId suId, NhuCellCfgCfmSdus *nhuCfgCellCfmSdus));

   
   /* RRC user to RRC */
   
/**
@brief Bind Request from RRC User.
@details 
* -# This primitive is used to bind a user to the RRC upper interface (NHU). 
*RRC layer software registers this new user and allocates a 
*Service Access Point for this bind and records the identity
*of the service user.
* -# It also issues a @ref NhUiNhuBndCfm to the service user after
* completing a successful bind.
* @param[in] pst Pointer to the post structure. System
services uses pst for loosely coupled intertask communication.
* @param[in] suId The service user SAP ID. The service user uses this
reference number to identify a SAP. The service user provides this ID and 
the service provider retains it. The service provider provides this
reference number in any further primitives that the service provider sends
 to the service user.
* @param[in] spId The service provider SAP ID. The service provider uses this
reference number to identify its SAP. The service user provides this 
reference number in any further primitives that the service user sends to the service provider.
*
* @return S16
*  -# ROK
*  -# RFAILED
*/
   EXTERN S16 NhUiNhuBndReq ARGS((Pst *pst, SuId suId, SpId spId));

/**
@brief UnBind Request from RRC User.
@details 
* This primitive is used to unbind the user SAP. The service access point
* is not deallocated, so a new bind request can be issued
* on this SAP (without reconfiguring the SAP in the service
* provider).
* @param[in] pst Pointer to the post structure. System
services uses pst for loosely coupled intertask communication.
* @param[in] spId The service provider SAP ID. The service provider
uses this reference number to identify the SAP.
* @param[in] reason Defines the reason for the unbind.
*
* @return S16
*  -# ROK
*  -# RFAILED
*/   
   EXTERN S16 NhUiNhuUbndReq ARGS((Pst *pst, SpId spId, Reason reason));

/** 
@brief Bind Confirm to RRC User.
@details 
This primitive is used to recover from the loss of a bind request.
If the service user does not receive a bind confirm primitive, it must stop
trying to bind after a limited number of retries.
The service provider must send a bind confirm upon receiving a bind request
primitive from the service user. These status values are requested:
- CM_BND_OK: This status is reported when the bind request is successful.
- CM_BND_NOK: This status is reported when the bind is unsuccessful.
* @param[in] pst Pointer to the post structure. System
services uses pst for loosely coupled intertask communication.
* @param[in] suId The service user SAP ID. The service user uses this
reference number to identify its lower control block.
* @param[in] status Status. The allowed values of status are:
                     CM_BND_OK 1 
                     CM_BND_NOK 2 
*
* @return S16
*  -# ROK
*  -# RFAILED
*/   

   EXTERN S16 NhUiNhuBndCfm ARGS((Pst *pst, SuId suId, U8 status));

/** 
@brief Data Request from RRC User.
@details 
* This primitive is used to request RRC to send a UE message in the
downlink. In addition, the RRC user might also provide the lower layer
configuration information at the eNodeB complementary to the UE message sent.
* @param[in] pst Pointer to the service user task configuration structure.
* @param[in] spId The service provider SAP ID.
* @param[in] nhuDatReqSdus Pointer to the Data SDU structure
containing the UE message and the configuration data related to the
message, if any.
*
* @return S16
*  -# ROK
*  -# RFAILED
*/   

   EXTERN S16 NhUiNhuDatReq ARGS((Pst *pst, SpId spId, NhuDatReqSdus *nhuDatReqSdus));

/**  
@brief Data Response from RRC User.
@details 
* This primitive is used to send data response from the RRC user carrying either DL-CCCH message or both DL-CCCH message and configurations.
* @param[in] pst Pointer to the service user task configuration structure.
* @param[in] spId The service provider SAP ID.
* @param[in] nhuDatRspSdus Pointer to the data response SDU structure.
*
* @return S16
*  -# ROK
*  -# RFAILED
*/   
   EXTERN S16 NhUiNhuDatRsp ARGS((Pst *pst, SpId spId, NhuDatRspSdus *nhuDatRspSdus));

/** 
@brief Configuration Request from RRC User.
@details 
* This primitive is used to configure the lower layers (MAC, RLC, and
PDCP) at the RNC by providing configuration information to the RRC. With this
primitive, the RRC user needs to send the UE message using data request and then
use this primitive to configure the lower layers with the information
complementary to the configuration present in the UE message. Each configuration
request is associated by means of a transaction identifier, UE ID, as indicated in its primitive header.
* @param[in] pst Pointer to the service user task configuration structure.
* @param[in] spId The service provider SAP ID.
* @param[in] nhuCfgReqSdu Pointer to the lower layer configuration request SDU structure.
*
* @return S16
*  -# ROK
*  -# RFAILED
*/   
   EXTERN S16 NhUiNhuCfgReq ARGS((Pst *pst, SpId spId, NhuCfgReqSdus *nhuCfgReqSdu));

/** 
@brief Cancel UE Request from RRC User to RRC.
@details 
* This primitive is used to request RRC to release all resources held
* by an UE and clean up the UE context. The typical scenario when this is used are timer 
expiry in RRC connection setup procedure or any error scenarios wherein the
RRC user might want to clean-up the UE context.
* @param[in] pst Pointer to the service user task configuration structure.
* @param[in] spId The service provider SAP ID.
* @param[in] cellId The identifier of the CELL at RRC.
* @param[in] crnti The identifier of the UE at RRC whose context must be removed. This field must be present always.
*
* @return S16
*  -# ROK
*  -# RFAILED
*/   
   EXTERN S16 NhUiNhuCnclUeReq ARGS((Pst *pst, SpId spId, NhuCellId cellId, NhuCrnti crnti));

/**  
@brief Cell Configuration Request from RRC User to RRC.
@details 
* This primitive is used to provide RRC with the common channel
resource configuration information in the cell (such as CCCH, PCCH,
BCCH, PUCCH,PHICH, RACH, and so on). It provides necessary configuration 
information to configure the lower layers for common channel reception and 
transmission. The associated transport channels and radio bearer resources are 
established. Modification of the existing configuration is allowed 
through this primitive. The primitive header contains transaction identifier 
and cell identifier.

RRC user should configure the cell with one Radio bearer for each of these
following: UL_CCCH-UL_SCH, DL_CCCH-DL_SCH, BCCH-BCH, BCCCH-DL_SCH, PCCH-PCH
logical channel to transport channel mapping.

The modification of the existing RB for a cell is not allowed. Only SRS,
PUCCH, RACH configuration can be modified.
* @param[in] pst Pointer to the service user task configuration structure.
* @param[in] spId The service provider SAP ID.
* @param[in] nhuCellCfgReqSdu Pointer to the configuration information for the
cell. The SDUs must be present always.
*
* @return S16
*  -# ROK
*  -# RFAILED
*/   
   EXTERN S16 NhUiNhuCellCfgReq ARGS((Pst *pst, SpId spId, NhuCellCfgReqSdus *nhuCellCfgReqSdu));

/** 
@brief Delete Transaction Request from RRC user to RRC.
@details 
* This primitive is used to send a delete transaction request from the RRC user to RRC. The RRC user uses this primitive to request RRC to terminate an ongoing transaction. RRC releases the configurations related to this transaction and provides a configuration confirm in response.
* @param[in] pst Pointer to the service user task configuration structure.
* @param[in] spId The service provider SAP ID.
* @param[in] cellId Cell ID of the UE at RRC 
* @param[in] crnti UE ID of the UE at RRC whose context must be removed. This field must be present always.
* @param[in] transId Transaction ID which must be terminated. This is a U32.
*
* @return S16
*  -# ROK
*  -# RFAILED
*/   
   EXTERN S16 NhUiNhuDeleteTransReq ARGS((Pst *pst, SpId spId, NhuCellId cellId,
                                              NhuCrnti crnti, U32 transId));

/** 
@brief Data Confirm from RRC to RRC user.
@details 
* This primitive is used to send the data confirm received from PDCP to the RRC
* user. This informs the RRC user whether a message is sent successfully.
*
* @param[in] pst          Pointer to the service user task configuration structure.
* @param[in] suId         The service user SAP ID.
* @param[in] nhuDatCfmSdus Success or Failure. 
*
* @return S16
*  -# ROK
*  -# RFAILED
*/   
   EXTERN S16 NhUiNhuDatCfm ARGS((Pst *pst, SuId suId, 
                                    NhuDatCfmSdus *nhuDatCfmSdus));

/** 
@brief Status Indication from RRC to RRC user.
@details 
* This primitive is used to send the status indication received from PDCP to the RRC user. This informs the RRC user whether a message is sent successfully.
The @ref nhuStaIndSdus will be allocated by RRC and the RRC user must free this.
*
* @param[in] pst Pointer to the service user task configuration structure.
* @param[in] suId The service provider SAP ID.
* @param[in] nhStaInd Status indication containg the status, pdcpId.
*
* @return S16
*  -# ROK
*  -# RFAILED
*/   

EXTERN S16 NhUiNhuStaInd ARGS((Pst *pst, SuId suId,
                                    NhuStaIndSdus *nhStaInd));

/**
@brief Encode RRC SDU request from RRC user to RRC.
@details
* This primitive is used to request RRC to encode the RRC SDU.
*
* @param[in] pst            Pointer to the service user task configuration structure.
* @param[in] spId           The service provider SAP ID.
* @param[in] nhuEncReqSdus  Pointer to nhuEncReqSdus structure. This structure contains the RRC messages/IEs to be encoded. 
*
* @return S16
*  -# ROK
*  -# RFAILED
*/

EXTERN S16 NhUiNhuEncodeReq ARGS((Pst *pst, SpId spId,
                               NhuEncReqSdus *nhuEncReqSdus));

/**
@brief Encode RRC SDU confirm from RRC to RRC user.
@details
* This primitive is used to send encoded RRC SDU to RRC user.
*
* @param[in] pst            Pointer to the service user task configuration structure.
* @param[in] suId           The service user SAP ID.
* @param[in] nhuEncCfmSdus  Pointer to nhuEncCfmSdus structure. This structure contains the encoded RRC message/IE. 
*
* @return S16
*  -# ROK
*  -# RFAILED
*/

EXTERN S16 NhUiNhuEncodeCfm ARGS((Pst *pst, SuId suId,
                               NhuEncCfmSdus *nhuEncCfmSdus));

/**
@brief PDCP SDU status request from RRC user to RRC. 
@details
* This primitive is used to request RRC to fetch PDCP SDU status from PDCP. This is required to support data forwarding during handover from E-UTRAN. RRC user on getting this status, sends the status to target node. 
*
* @param[in] pst            Pointer to the service user task configuration structure.
* @param[in] spId           The service provider SAP ID.
* @param[in] nhuHdr         The SDU header.
*
* @return S16
*  -# ROK
*  -# RFAILED
*/

EXTERN S16 NhUiNhuPdcpSduStaReq ARGS((Pst *pst, SpId spId, NhuHdr nhuHdr));

/**
@brief PDCP Data Forward request from RRC user to RRC. 
@details
* This primitive is used to request RRC to send PDCP start Data Forwarding request.  
*
* @param[in] pst            Pointer to the service user task configuration structure.
* @param[in] spId           The service provider SAP ID.
* @param[in] nhuHdr         The SDU header.
*
* @return S16
*  -# ROK
*  -# RFAILED
*/

EXTERN S16 NhUiNhuStartPdcpDataFwdReq ARGS((Pst *pst, SpId spId, NhuHdr nhuHdr));


/**
@brief PDCP Data Resume request from RRC user to RRC. 
@details
* This primitive is used to request RRC to send PDCP data resume request.  
*
* @param[in] pst            Pointer to the service user task configuration structure.
* @param[in] spId           The service provider SAP ID.
* @param[in] nhuHdr         The SDU header.
*
* @return S16
*  -# ROK
*  -# RFAILED
*/

EXTERN S16 NhUiNhuPdcpDatResumeReq ARGS((Pst *pst, SpId spId, NhuHdr nhuHdr));
/**
@brief PDCP SDU status confirm from RRC to RRC user. 
@details
* This primitive is used to send PDCP SDU status to RRC. RRC gets the status from PDCP and passes it to RRC user. This confirm is in response to the request from RRC user.
*
* @param[in] pst            Pointer to the service user task configuration structure.
* @param[in] suId           The service user SAP ID.
* @param[in] nhuPdcpSduStaCfm  Pointer to nhuPdcpSduStaCfm structure. This structure contains the status of PDCP SDUs for all the data RBs established for the given UeID in hdr structure. The status is fetched from PDCP on getting the request from RRC user. 
*
* @return S16
*  -# ROK
*  -# RFAILED
*/

EXTERN S16 NhUiNhuPdcpSduStaCfm ARGS((Pst *pst, SuId suId, 
                               NhuPdcpSduStaCfm *nhuPdcpSduStaCfm));

EXTERN S16 NhUiNhuPdcpDatResumeCfm
ARGS((
Pst  *pst,
SuId suId,
NhuPdcpDatResumeCfm *nhuPdcpDatResumeCfm
));

/**
 *
 * @brief UE Capability Decode Request Primitive from the RRC service user to RRC.
 * 
 * @details 
 * This funtion supports decoding to UE Capability IE only if RAT type is either of 
 * E-URAN or UTRAN. For UTRAN, the Inter RAT Handover Message is decoded as per TS 25.331 v7.3.0(2006-12).
 * This function does the following:
 * -# Receives the msg/Ie decode request primitive from RRC user. 
 * -# Calls validate functions to validate the incoming primtive and contents.
 * -# Calls "NhUiNhuDecodeCfm" to send decoded msg/Ie to RRC User.
 * @param[in]  pst Pst       Post structure
 * @param[in]  spId SpId     Service provider ID
 * @param[in]  nhuDecodeSduReq NhuDecodeSduReq containing the message that must be
 *                           decoded
 *
 * @return S16
 *  -# ROK
 *  -# RFAILED
*/
EXTERN S16 NhUiNhuDecodeReq ARGS((Pst  *pst, SpId spId, NhuDecodeSduReq *nhuDecodeSduReq));


/**
 *
 * @brief UE Capability Decode Request Confirm Primitive from the RRC to RRC service user
 * 
 * @details 
 * This function sends the Decoded UE Capability IE to RRC User.
 * @param[in]  pst Pst       Post structure
 * @param[in]  suId SuId     Service user ID
 * @param[in]  nhuDecodeSduCfm NhuDecodeSduCfm containing the decoded message
 *
 * @return S16
 *  -# ROK
 *  -# RFAILED
*/
EXTERN S16 NhUiNhuDecodeCfm ARGS((Pst  *pst, SuId suId, NhuDecodeSduCfm *nhuDecodeSduCfm));


/*
   Counter Check :
   ==============
*/

/**
 *
 * @brief Count Request Primitive from the RRC service user to RRC.
 * 
 * @details 
 * This function does the following:
 * -# Receives the Count Request premitive from RRC user. 
 * -# Calls validate functions to validate the incoming primtive and contents.
 * -# Invokes relevant module handler using UIM state machines.
 * @param[in]  pst Pst     Post structure
 * @param[in]  spId SpId      Service provider ID
 * @param[in]  countHdr NhuHdr  Header containing UE ID, Cell ID, and trans ID
 *
 * @return S16
 *  -# ROK
 *  -# RFAILED
*/
EXTERN S16 NhUiNhuCountReq ARGS((Pst *pst, SpId spId, NhuHdr *countHdr));


/**
 *
 * @brief Count Request Confirm Primitive from the RRC service user to RRC.
 * 
 * @details 
 * This function does the following:
 * -# Calls validate functions to validate the incoming primtive and contents.
 * -# Send the Count Request Confirm Premitive from RRC to RRC user. 
 * @param[in]  pst Pst     Post structure
 * @param[in]  suId SuId      Service user ID
 * @param[in]  nhuDRBCountInfoLst NhuDRBCountInfoLst List of DRBs along with Count values of each of them
 *
 * @return S16
 *  -# ROK
 *  -# RFAILED
*/
EXTERN S16 NhUiNhuCountCfm ARGS((Pst *pst, SuId suId, NhuDRBCountInfoLst *nhuDRBCountInfoLst));

#endif /* NH */

/* Extern declarations */
/* Extern for Pack functions */
#if (defined(LCNHU) || defined(LWLCNHU))

#ifdef TENB_MULT_CELL_SUPPRT
EXTERN S16 cmPkNhuLLyrSapIdInfo ARGS ((
NhuLLyrSapIdInfo *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuUeLLyrSapIdInfo ARGS ((
NhuUeLLyrSapIdInfo *param,
Buffer *mBuf
));

#endif /* TENB_MULT_CELL_SUPPRT */

#ifdef LTE_ADV
EXTERN S16 cmPkNhuUeSecCellInfo ARGS((
NhuUeSecCellInfo *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkNhuUeSecCellInfo ARGS((
NhuUeSecCellInfo *param,
Buffer *mBuf
));
#endif /* LTE_ADV */


EXTERN S16 cmPkNhuBndCfm ARGS ((
Pst *pst,
SuId suId,
U8 status
));
EXTERN S16 cmPkNhuDatInd ARGS((
Pst *pst,
SuId suId,
NhuDatIndSdus *nhuDatIndSdus
));
EXTERN S16 cmPkNhuErrInd ARGS((
Pst *pst,
SuId suId,
NhuErrIndSdus *nhuErrIndSdus
));
EXTERN S16 cmPkNhuDatCfm ARGS((
Pst *pst,
SuId suId,
NhuDatCfmSdus *nhuDatCfmSdus
));
EXTERN S16 cmPkNhuCfgCfm ARGS((
Pst *pst,
SuId suId,
NhuCfgCfmSdus *nhuCfgCfmSdus
));
EXTERN S16 cmPkNhuCellCfgCfm ARGS((
Pst *pst,
SuId suId,
NhuCellCfgCfmSdus *nhuCellCfgCfmSdus
));
EXTERN S16 cmPkNhuDecodeCfm ARGS((
Pst *pst,
SuId suId,
NhuDecodeSduCfm *nhuDecodeSduCfm
));
EXTERN S16 cmPkNhuCountCfm ARGS((
Pst *pst,
SuId suId,
NhuDRBCountInfoLst *nhuDRBCountInfoLst
));
EXTERN S16 cmPkNhuHdr ARGS((
NhuHdr *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuErrorInfo ARGS((
NhuErrorInfo *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuNewUeInfo ARGS((
NhuNewUeInfo *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuPdcpRohcInfo ARGS((
NhuPdcpRohcInfo *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuPdcpHdrComprInfo ARGS((
NhuPdcpHdrComprInfo *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuPdcpCfg ARGS((
NhuPdcpCfg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuLogChId ARGS((
NhuLogChId *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuLogChCfg ARGS((
NhuLogChCfg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuUlLogChMap ARGS((
NhuUlLogChMap *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuDlUmRlcModeInfo ARGS((
NhuDlUmRlcModeInfo *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuDlAmRlcModeInfo ARGS((
NhuDlAmRlcModeInfo *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuDlTmRlcModeInfo ARGS((
NhuDlTmRlcModeInfo *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuUlUmRlcModeInfo ARGS((
NhuUlUmRlcModeInfo *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuUlAmRlcModeInfo ARGS(( 
NhuUlAmRlcModeInfo *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuUlRlcMode ARGS((
NhuUlRlcMode *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuUlRbCfg ARGS((
NhuUlRbCfg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuDlLogChMap ARGS((
NhuDlLogChMap *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuDlRlcMode ARGS((
NhuDlRlcMode *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuDlRbCfg ARGS((
NhuDlRbCfg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuRbCfgInfo ARGS((
NhuRbCfgInfo *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuRbCfgList ARGS((
NhuRbCfgList *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuRbRlsCfgList ARGS((
NhuRbRlsCfgList *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuRbCfgAllList ARGS((
NhuRbCfgAllList *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuUlHarqCfg ARGS((
NhuUlHarqCfg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuTrChCfg ARGS((
NhuTrChCfg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuIntgKeyAlgoInfo
ARGS ((
NhuIntgKeyAlgoInfo *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuCiphKeyAlgoInfo
ARGS ((
NhuCiphKeyAlgoInfo *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuSecurityCfg
ARGS ((
NhuSecurityCfg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuUeCfgInfo
ARGS ((
NhuUeCfgInfo *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuUlDcchMsg
ARGS ((
NhuUlDcchMsg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuDlDcchMsg
ARGS ((
NhuDlDcchMsg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuDedMsg
ARGS ((
NhuDedMsg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuCmnMsgInfo
ARGS ((
NhuCmnMsgInfo *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuCmnMsg
ARGS ((
NhuCmnMsg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuDatReqUeMsg
ARGS ((
NhuDatReqUeMsg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuDatReqSdus
ARGS ((
NhuDatReqSdus *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuUlCcchMsg
ARGS ((
NhuUlCcchMsg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuDlCcchMsg
ARGS ((
NhuDlCcchMsg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuDatRspSdus
ARGS ((
NhuDatRspSdus *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuDatIndSdus
ARGS ((
NhuDatIndSdus *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuRaOccasion
ARGS ((
NhuRaOccasion *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuRachCfg
ARGS ((
NhuRachCfg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuCmnMacCfg
ARGS ((
NhuCmnMacCfg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuCellCfgInfo
ARGS ((
NhuCellCfgInfo *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuCellCfgReqSdus
ARGS ((
NhuCellCfgReqSdus *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuCellCfgCfmSdus
ARGS ((
NhuCellCfgCfmSdus *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuStaIndSdus
ARGS ((
NhuStaIndSdus *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuDatCfmSdus
ARGS ((
NhuDatCfmSdus *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuErrIndSdus
ARGS ((
NhuErrIndSdus *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuCfgReqSdus
ARGS ((
NhuCfgReqSdus *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuCfgCfmSdus
ARGS ((
NhuCfgCfmSdus *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuBndReq
ARGS ((
Pst *pst,
SuId suId,
SpId spId
));
EXTERN S16 cmPkNhuUbndReq
ARGS ((
Pst *pst,
SpId spId,
Reason reason
));
EXTERN S16 cmPkNhuDatReq
ARGS ((
Pst *pst,
SpId spId,
NhuDatReqSdus *nhuDatReqSdus
));
EXTERN S16 cmPkNhuCfgReq
ARGS ((
Pst *pst,
SpId spId,
NhuCfgReqSdus *nhuCfgReqSdus
));
EXTERN S16 cmPkNhuCnclUeReq
ARGS ((
Pst *pst,
SpId spId,
NhuCellId cellId,
NhuCrnti crnti
));
EXTERN S16 cmPkNhuCellCfgReq
ARGS ((
Pst *pst,
SpId spId,
NhuCellCfgReqSdus *nhuCellCfgReqSdus
));
EXTERN S16 cmPkNhuDeleteTransReq
ARGS ((
Pst *pst,
SpId spId,
NhuCellId cellId,
NhuCrnti ueId,
U32 transId
));
EXTERN S16 cmPkNhuDatRsp
ARGS ((
Pst *pst,
SpId spId,
NhuDatRspSdus *nhuDatRspSdus
));
EXTERN S16 cmPkNhuStaInd
ARGS((
Pst *pst,
SuId suId,
NhuStaIndSdus *nhuStaIndSdus
));
EXTERN S16 cmPkNhuDecodeReq
ARGS ((
Pst *pst,
SpId spId,
NhuDecodeSduReq *nhuDecodeSduReq
));
EXTERN S16 cmPkNhuCountReq
ARGS ((
Pst *pst,
SpId spId,
NhuHdr *nhuHdr
));
EXTERN S16 cmPkNhuEncodeReq
ARGS ((
Pst  *pst,
SpId spId,
NhuEncReqSdus *nhuEncReqSdus
));
EXTERN S16 cmPkNhuEncReqSdus
ARGS ((
NhuEncReqSdus *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuEncodeCfm
ARGS ((
Pst *pst,
SuId suId,
NhuEncCfmSdus *nhuEncSdusCfm
));
EXTERN S16 cmPkNhuEncCfmSdus
ARGS ((
NhuEncCfmSdus *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuPdcpSduStaReq
ARGS ((
Pst  *pst,
SpId spId,
NhuHdr hdr
));

EXTERN S16 cmPkNhuStartPdcpDataFwdReq 
ARGS ((
Pst  *pst,
SpId spId,
NhuHdr hdr
));

EXTERN S16 cmPkNhuPdcpDatResumeReq 
ARGS ((
Pst  *pst,
SpId spId,
NhuHdr hdr
));

EXTERN S16 cmPkNhuPdcpSduStaCfm
ARGS ((
Pst  *pst,
SuId suId,
NhuPdcpSduStaCfm *nhuPdcpSduStaCfm
));
EXTERN S16 cmPkNhuPdcpSduStaCfmSdus
ARGS ((
NhuPdcpSduStaCfm *param,
Buffer *mBuf
));

EXTERN S16 cmPkNhuPdcpDatResumeCfm
ARGS ((
Pst  *pst,
SuId suId,
NhuPdcpDatResumeCfm *nhuPdcpDatResumeCfm
));
EXTERN S16 cmPkNhuPdcpSduStaInfo
ARGS ((
NhuPdcpSduStaInfo *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuPdcpCfgSduStaInfo
ARGS ((
NhuHoPdcpSduInfo *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuDecodeSduReq
ARGS ((
NhuDecodeSduReq  *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuDecodeSduCfm
ARGS ((
NhuDecodeSduCfm *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuDRBCountInfoLst
ARGS ((
NhuDRBCountInfoLst *param,
Buffer *mBuf
));


EXTERN S16 cmPkNhuUL_DCCH_Msg ARGS ((NhuUL_DCCH_Msg *param, Buffer *mBuf));
EXTERN S16 cmPkNhuDL_DCCH_Msg ARGS ((NhuDL_DCCH_Msg *param, Buffer *mBuf));
EXTERN S16 cmPkNhuBCCH_BCH_Msg ARGS ((NhuBCCH_BCH_Msg *param, Buffer *mBuf));
EXTERN S16 cmPkNhuBCCH_DL_SCH_Msg ARGS ((NhuBCCH_DL_SCH_Msg *param, Buffer
*mBuf));
EXTERN S16 cmPkNhuPCCH_Msg ARGS ((NhuPCCH_Msg *param, Buffer *mBuf));
EXTERN S16 cmPkNhuUL_CCCH_Msg ARGS ((NhuUL_CCCH_Msg *param, Buffer *mBuf));
EXTERN S16 cmPkNhuDL_CCCH_Msg ARGS ((NhuDL_CCCH_Msg *param, Buffer *mBuf));

#ifdef TENB_MULT_CELL_SUPPRT
EXTERN S16 cmUnpkNhuLLyrSapIdInfo ARGS ((
NhuLLyrSapIdInfo *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuUeLLyrSapIdInfo ARGS ((
NhuUeLLyrSapIdInfo *param,
Buffer *mBuf
));

#endif

EXTERN S16 cmUnpkNhuHdr
ARGS ((
NhuHdr *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuErrorInfo
ARGS ((
NhuErrorInfo *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuNewUeInfo
ARGS ((
NhuNewUeInfo *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuPdcpRohcInfo
ARGS ((
NhuPdcpRohcInfo *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuPdcpHdrComprInfo
ARGS ((
NhuPdcpHdrComprInfo *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuPdcpCfg
ARGS ((
NhuPdcpCfg *param,
Buffer *mBuf,
Ptr ptr
));
EXTERN S16 cmUnpkNhuLogChId
ARGS ((
NhuLogChId *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuLogChCfg
ARGS ((
NhuLogChCfg *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuUlLogChMap
ARGS ((
NhuUlLogChMap *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuDlUmRlcModeInfo
ARGS ((
NhuDlUmRlcModeInfo *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuDlAmRlcModeInfo
ARGS ((
NhuDlAmRlcModeInfo *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuDlTmRlcModeInfo
ARGS ((
NhuDlTmRlcModeInfo *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuUlUmRlcModeInfo
ARGS ((
NhuUlUmRlcModeInfo *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuUlAmRlcModeInfo
ARGS ((
NhuUlAmRlcModeInfo *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuUlRlcMode
ARGS ((
NhuUlRlcMode *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuUlRbCfg
ARGS ((
NhuUlRbCfg *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuDlLogChMap
ARGS ((
NhuDlLogChMap *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuDlRlcMode
ARGS ((
NhuDlRlcMode *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuDlRbCfg
ARGS ((
NhuDlRbCfg *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuRbCfgInfo
ARGS ((
NhuRbCfgInfo *param,
Buffer *mBuf,
Ptr ptr
));
EXTERN S16 cmUnpkNhuRbCfgList
ARGS ((
NhuRbCfgList *param,
Ptr    ptr,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuRbRlsCfgList
ARGS ((
NhuRbRlsCfgList *param,
Ptr    ptr,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuRbCfgAllList
ARGS ((
NhuRbCfgAllList *param,
Ptr    ptr,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuUlHarqCfg
ARGS ((
NhuUlHarqCfg *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuTrChCfg
ARGS ((
NhuTrChCfg *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuIntgKeyAlgoInfo
ARGS ((
NhuIntgKeyAlgoInfo *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuCiphKeyAlgoInfo
ARGS ((
NhuCiphKeyAlgoInfo *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuSecurityCfg
ARGS ((
NhuSecurityCfg *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuUeCfgInfo
ARGS ((
NhuUeCfgInfo *param,
Ptr    ptr,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuUlDcchMsg
ARGS ((
NhuUlDcchMsg *param,
Ptr    ptr,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuDlDcchMsg
ARGS ((
NhuDlDcchMsg *param,
Ptr    ptr,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuDedMsg
ARGS ((
NhuDedMsg *param,
Ptr    ptr,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuCmnMsgInfo
ARGS ((
NhuCmnMsgInfo *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuCmnMsg
ARGS ((
NhuCmnMsg *param,
Ptr    ptr,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuDatReqUeMsg
ARGS ((
NhuDatReqUeMsg *param,
Ptr    ptr,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuDatReqSdus
ARGS ((
NhuDatReqSdus *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuUlCcchMsg
ARGS ((
NhuUlCcchMsg *param,
Ptr    ptr,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuDlCcchMsg
ARGS ((
NhuDlCcchMsg *param,
Ptr    ptr,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuDatRspSdus
ARGS ((
NhuDatRspSdus *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuDatIndSdus
ARGS ((
NhuDatIndSdus *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuRaOccasion
ARGS ((
NhuRaOccasion *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuRachCfg
ARGS ((
NhuRachCfg *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuCmnMacCfg
ARGS ((
NhuCmnMacCfg *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuCellCfgInfo
ARGS ((
NhuCellCfgInfo *param,
Ptr    ptr,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuCellCfgReqSdus
ARGS ((
NhuCellCfgReqSdus *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuCellCfgCfmSdus
ARGS ((
NhuCellCfgCfmSdus *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuDatCfmSdus
ARGS ((
NhuDatCfmSdus *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuStaIndSdus
ARGS ((
NhuStaIndSdus *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuErrIndSdus
ARGS ((
NhuErrIndSdus *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuCfgReqSdus
ARGS ((
NhuCfgReqSdus *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuCfgCfmSdus
ARGS ((
NhuCfgCfmSdus *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuBndReq
ARGS ((
NhuBndReq func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuBndCfm
ARGS ((
NhuBndCfm func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuUbndReq
ARGS ((
NhuUbndReq func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuDatReq
ARGS ((
NhuDatReq func,
Pst *pst,
Buffer *mBuf,
Mem *sMem,
Size maxBlkSize
));
EXTERN S16 cmUnpkNhuDatRsp
ARGS ((
NhuDatRsp func,
Pst *pst,
Buffer *mBuf,
Mem *sMem,
Size maxBlkSize
));
EXTERN S16 cmUnpkNhuDatInd
ARGS ((
NhuDatInd func,
Pst *pst,
Buffer *mBuf,
Mem *sMem,
Size maxBlkSize
));
EXTERN S16 cmUnpkNhuDatCfm
ARGS ((
NhuDatCfm func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuErrInd
ARGS ((
NhuErrInd func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuCfgReq
ARGS ((
NhuCfgReq func,
Pst *pst,
Buffer *mBuf,
Mem *sMem,
Size maxBlkSize
));
EXTERN S16 cmUnpkNhuCfgCfm
ARGS ((
NhuCfgCfm func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuCnclUeReq
ARGS ((
NhuCnclUeReq func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuCellCfgReq
ARGS ((
NhuCellCfgReq func,
Pst *pst,
Buffer *mBuf,
Mem *sMem,
Size maxBlkSize
));
EXTERN S16 cmUnpkNhuCellCfgCfm
ARGS ((
NhuCellCfgCfm func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuDeleteTransReq
ARGS ((
NhuDeleteTransReq func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmUnpkNhuStartPdcpDataFwdReq
ARGS ((
NhuSduStaReq func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuPdcpDatResumeReq
ARGS((
NhuDatResumeReq func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmUnpkNhuStaInd
ARGS((
NhuStaInd func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuDecodeReq
ARGS ((
NhuDecodeReq func,
Pst *pst,
Buffer *mBuf,
Mem *sMem,
Size maxBlkSize
));
EXTERN S16 cmUnpkNhuCountReq
ARGS ((
NhuCountReq func,
Pst *pst,
Buffer *mBuf,
Mem *sMem,
Size maxBlkSize
));
EXTERN S16 cmUnpkNhuDecodeCfm
ARGS((
NhuDecodeCfm func,
Pst *pst,
Buffer *mBuf,
Mem *sMem,
Size maxBlkSize
));
EXTERN S16 cmUnpkNhuCountCfm
ARGS((
NhuCountCfm func,
Pst *pst,
Buffer *mBuf,
Mem *sMem,
Size maxBlkSize
));
EXTERN S16 cmUnpkNhuEncodeReq
ARGS ((
NhuEncReq func,
Pst *pst,
Buffer *mBuf,
Mem *sMem,
Size maxBlkSize
));
EXTERN S16 cmUnpkNhuEncReqSdus
ARGS ((
NhuEncReqSdus *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuEncodeCfm
ARGS ((
NhuEncCfm func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuEncCfmSdus
ARGS ((
NhuEncCfmSdus *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuPdcpSduStaReq
ARGS ((
NhuSduStaReq func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuPdcpSduStaCfm
ARGS ((
NhuSduStaCfm func,
Pst *pst,
Buffer *mBuf,
Mem *sMem,
Size maxBlkSize
));
EXTERN S16 cmUnpkNhuPdcpSduStaCfmSdus
ARGS ((
NhuPdcpSduStaCfm *param,
Buffer *mBuf,
Pst *pst
));
EXTERN S16 cmUnpkNhuRbId
ARGS ((
NhuRbId *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuRbId
ARGS ((
NhuRbId *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuCellReCfgInfo
ARGS ((
NhuCellReCfgInfo *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuCellReCfgInfo
ARGS ((
NhuCellReCfgInfo *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuCellRlsInfo
ARGS ((
NhuCellRlsInfo *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuCellRlsInfo
ARGS ((
NhuCellRlsInfo *param,
Buffer *mBuf
));
EXTERN S16 cmPkBuf
ARGS ((
 Pst    *pst,
 Buffer *buf,
 Buffer **mBuf
));
EXTERN S16 cmUnpkBuf
ARGS ((
 Buffer **buf,
 Buffer *mBuf
));
/* nhu_x_002.main_1 : moving pack/unpack of NhuSysBwCfg outside PHY_CFG_SUPP */
EXTERN S16 cmPkNhuSysBwCfg
ARGS ((
NhuSysBwCfg *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuSysBwCfg
ARGS ((
NhuSysBwCfg *param,
Buffer *mBuf
));

#ifdef RRC_PHY_CFG_SUPP
EXTERN S16 cmUnpkNhuCmnPhyCfg
ARGS ((
NhuCmnPhyCfg *param,
Buffer *mBuf
));
/* nhu_x_002.main_1 : moving pack/unpack of NhuSysBwCfg outside PHY_CFG_SUPP */
EXTERN S16 cmPkNhuPhichCfg
ARGS ((
NhuPhichCfg *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuPhichCfg
ARGS ((
NhuPhichCfg *param,
Buffer *mBuf
));

EXTERN S16 cmPkNhuCqiRptCfg
ARGS ((
NhuCqiRptCfg *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuCqiRptCfg
ARGS ((
NhuCqiRptCfg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuCqiRptModePeriodic
ARGS ((
NhuCqiRptModePeriodic *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuCqiRptModePeriodic
ARGS ((
NhuCqiRptModePeriodic *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuDedAntCfgInfo
ARGS ((
NhuDedAntCfgInfo *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuDedAntCfgInfo
ARGS ((
NhuDedAntCfgInfo *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuDedSRCfg
ARGS ((
NhuDedSRCfg *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuDedSRCfg
ARGS ((
NhuDedSRCfg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuDedPucchCfg
ARGS ((
NhuDedPucchCfg *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuDedPucchCfg
ARGS ((
NhuDedPucchCfg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuDedSRSUlCfg
ARGS ((
NhuDedSRSUlCfg *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuDedSRSUlCfg
ARGS ((
NhuDedSRSUlCfg *param,
Buffer *mBuf
));

EXTERN S16 cmPkNhuDedPuschCfg
ARGS ((
NhuDedPuschCfg *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuDedPuschCfg
ARGS ((
NhuDedPuschCfg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuPdschCfg
ARGS ((
NhuPdschCfg *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuPdschCfg
ARGS ((
NhuPdschCfg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuTddSfCfgInfo
ARGS ((
NhuTddSfCfgInfo *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuTddSfCfgInfo
ARGS ((
NhuTddSfCfgInfo *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuTxSchmCfg
ARGS ((
NhuTxSchmCfg *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuTxSchmCfg
ARGS ((
NhuTxSchmCfg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuCmnSrsUlCfg
ARGS ((
NhuCmnSrsUlCfg *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuCmnSrsUlCfg
ARGS ((
NhuCmnSrsUlCfg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuCmnPdschCfg
ARGS ((
NhuCmnPdschCfg *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuCmnPdschCfg
ARGS ((
NhuCmnPdschCfg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuCmnPuschCfg
ARGS ((
NhuCmnPuschCfg *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuCmnPuschCfg
ARGS ((
NhuCmnPuschCfg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuUlRefSigPUSCH
ARGS ((
NhuUlRefSigPUSCH *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuUlRefSigPUSCH
ARGS ((
NhuUlRefSigPUSCH *param,
Buffer *mBuf
));

EXTERN S16 cmPkNhuPhyCellIdCfg
ARGS ((
NhuPhyCellIdCfg *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuPhyCellIdCfg
ARGS ((
NhuPhyCellIdCfg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuPrachCfg
ARGS ((
NhuPrachCfg *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuPrachCfg
ARGS ((
NhuPrachCfg *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkNhuPucchCfg
ARGS ((
NhuPucchCfg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuPucchCfg
ARGS ((
NhuPucchCfg *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuPhyCfg
ARGS ((
NhuPhyCfg *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuCmnPhyReCfg
ARGS ((
NhuCmnPhyRecfg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuCmnPhyReCfg
ARGS ((
NhuCmnPhyRecfg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuCmnPhyCfg
ARGS ((
NhuCmnPhyCfg *param,
Buffer *mBuf
));
EXTERN S16 cmPkNhuPhyCfg
ARGS ((
NhuPhyCfg *param,
Buffer *mBuf
));
#endif
EXTERN S16 cmUnpkNhuPdcpCfgSduStaInfo
ARGS ((
NhuHoPdcpSduInfo *param,
Buffer *mBuf,
Ptr ptr
));

EXTERN S16 cmUnpkNhuPdcpSduStaInfo
ARGS ((
NhuPdcpSduStaInfo *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuDecodeSduReq
ARGS ((
NhuDecodeSduReq *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuDecodeSduCfm
ARGS ((
NhuDecodeSduCfm *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkNhuDRBCountInfoLst
ARGS ((
NhuDRBCountInfoLst *param,
Buffer *mBuf
));


EXTERN S16 cmPkNhuPdcpDatResumeCfmSdus
ARGS ((
NhuPdcpDatResumeCfm *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkNhuStartPdcpDataFwdReq
ARGS ((
NhuSduStaReq func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmUnpkNhuPdcpDatResumeReq
ARGS ((
NhuDatResumeReq func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmUnpkNhuUL_DCCH_Msg ARGS ((NhuUL_DCCH_Msg *param, Ptr ptr, Buffer
*mBuf));
EXTERN S16 cmUnpkNhuDL_DCCH_Msg ARGS ((NhuDL_DCCH_Msg *param, Ptr ptr, Buffer
*mBuf));
EXTERN S16 cmUnpkNhuBCCH_BCH_Msg ARGS ((NhuBCCH_BCH_Msg *param, Ptr ptr, Buffer
*mBuf));
EXTERN S16 cmUnpkNhuBCCH_DL_SCH_Msg ARGS ((NhuBCCH_DL_SCH_Msg *param, Ptr ptr,
Buffer *mBuf));
EXTERN S16 cmUnpkNhuPCCH_Msg ARGS ((NhuPCCH_Msg *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkNhuUL_CCCH_Msg ARGS ((NhuUL_CCCH_Msg *param, Ptr ptr, Buffer
*mBuf)); 
EXTERN S16 cmUnpkNhuDL_CCCH_Msg ARGS ((NhuDL_CCCH_Msg *param, Ptr ptr, Buffer
*mBuf)); 

#endif
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __NHUX__ */
/** @} */
   
/**********************************************************************
         End of file:     nhu.x@@/main/6 - Thu Jan  5 15:32:14 2012
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      ds       1. LTE RRC Initial Release.
/main/2      ---      nhu_x_001.main_1  mc     1. logical channel type hash defines made same
                                  as defined in cm_lte.h
/main/4      ---      nhu_x_001.main_3  vkulkarni    1.Making NhuSysBwCfg common to MAC and PHY.
/main/5      ---      nhu_x_001.main_4  sbalakrishna 1. Updated for Release of 3.1.
/main/6      ---      nhu_x_001.main_5   mpatel    1. corrected the comment of NHU_HO_DL
                                       2. Added enum` nhuTddAckNackFBMode
                                       3. added repFactorPres in nhuDedPucchCfg
                                       4. added TDD ACk/NACK config present and mode in nhuDedPucchCfg 
*********************************************************************91*/
