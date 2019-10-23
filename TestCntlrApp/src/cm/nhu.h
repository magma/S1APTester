
/**********************************************************************

    Name:   LTE RRC common hash defines

    Type:   C include file

    Desc:   Defines required by the RRC user.

    File:   nhu.h

    Sid:      nhu.h@@/main/4 - Thu Jun 30 16:22:58 2011

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


#ifndef __NHU_H__
#define __NHU_H__

/* include files */
#include "nhu_asn.h"         /* ASN.1 definitions */

/** @def nhuprimevt NHU Primitive Events */
#define EVTNHUBNDREQ         0x01 /* Bind request */
#define EVTNHUBNDCFM         0x02 /* Bind Confirm */
#define EVTNHUUBNDREQ        0x03 /* Unbind request */
#define EVTNHUDATREQ         0x04 /* Data Request */
#define EVTNHUDATIND         0x05 /* Data Indication */
#define EVTNHUDATRSP         0x06 /* Data Response */
#define EVTNHUERRIND         0x07 /* Error Indication */
#define EVTNHUCFGREQ         0x08 /* Lower Layer Configuration Request */
#define EVTNHUCFGCFM         0x09 /* Lower Layer Configuration Confirm */
#define EVTNHUCNCLUEREQ      0x0A /* Cancel UE request */
#define EVTNHUCELLCFGREQ     0x0B /* Cell Configuration Request */
#define EVTNHUCELLCFGCFM     0x0C /* Cell Configuration Confirm */
#define EVTNHUDELETETRANSREQ 0x0D /* Delete transaction request */
#define EVTNHUDATCFM         0x0E /* Data Confirm */
#define EVTNHUSTAIND         0x0F /* Status Indication */
#define EVTNHUUEIDREQ        0x10 /* UeId Request */
#define EVTNHUUEIDCFM        0x11 /* UeId Confirm */
#define EVTNHUPDCPSDUSTAREQ  0x12 /* PDCP SDU Status Request */
#define EVTNHUPDCPSDUSTACFM  0x13 /* PDCP SDU Status Confirm */
#define EVTNHUCOUNTREQ       0x14  /* Count Request */
#define EVTNHUCOUNTCFM       0x15  /* Count Request Confirm*/
#define EVTNHUDCODEREQ       0x16  /* Decode Request*/
#define EVTNHUDCODECFM       0x17  /* Decode confirm*/
#define EVTNHUENCODEREQ      0x18  /* Encode Request */
#define EVTNHUENCODECFM      0x19  /* Encode Confirm*/
#define EVTNHUSTARTPDCPDATAFWDREQ 0x1A /* Data Fwd Request */
#define EVTNHUPDCPDATRESUMEREQ 0x1B /* Data Resume Request */
#define EVTNHUPDCPDATRESUMECFM  0x1C /* PDCP SDU Status Confirm */

/** @def nhumsgcat NHU Message Category */
#define NHU_MSG_DLDCCH     0x01 /* DL-DCCH message */
#define NHU_MSG_ULDCCH     0x02 /* UL-DCCH message */
#define NHU_MSG_DLCCCH     0x03 /* DL-CCCH message */
#define NHU_MSG_ULCCCH     0x04 /* UL-CCCH message */
#define NHU_MSG_DLPCCH     0x05 /* DL-PCCH message */
#define NHU_MSG_DLBCCHBCH  0x06 /* BCCH on BCH message */
#define NHU_MSG_DLBCCHDLSCH  0x07 /* BCCH on DL-SCH message */
#define NHU_MSG_HOCMD        0x08 /* Handover Command message */ 
#define NHU_MSG_UERACAPINFO 0x09 /* UE Radio Access Capability Information message */
#define NHU_MSG_UECAPINFO    0x0A /* UE Capability Information message */
#define NHU_MSG_HOPREPINFO   0x0B /* Handover Preparatin Information message */

/** @def SDU types for Encode and decode*/
#define NHU_DEC_SDUTYPE_EUTRA_UECAP_IE       0x0C  /* SDU for E-UTRA UE Capability */
#define NHU_DEC_SDUTYPE_UTRA_RRC_CONT       0x0D  /* SDU for UTRA UE Capability */
#define NHU_DEC_SDUTYPE_UTRA_UECAP_IE       0x0E  /* SDU for UTRA UE Capability */
/* nhu_h_001.main_3: Msg type is added for varShorMAC-Input*/
#ifdef NHU_VER2
#define NHU_MSG_VARSHORTMACI 0x0F /* varShortMAC-Input */
#endif /* NHU_VER2 */
#define NHU_ENC_SDUTYPE_UTRA_RRC_CONT 0x10 /* UTRA RRC Container */

/* SPS changes starts */
#define NHU_MSG_UECAPINFO_V9A0 0x10
/* SPS changes ends */

/** @def sibtype SIB types */
#define NHU_SIB_TYPE1      0x01
#define NHU_SIB_TYPE2      0x02
#define NHU_SIB_TYPE3      0x03
#define NHU_SIB_TYPE4      0x04
#define NHU_SIB_TYPE5      0x05
#define NHU_SIB_TYPE6      0x06
#define NHU_SIB_TYPE7      0x07
#define NHU_SIB_TYPE8      0x08
#define NHU_SIB_TYPE9      0x09
#define NHU_SIB_TYPE10     0x0A
#define NHU_SIB_TYPE11     0x0B

/* nhu_h_001.main_3: New SIB types added*/
#ifdef NHU_VER1
#define NHU_SIB_TYPE12     0x0C
#define NHU_SIB_TYPE13     0x0D
#endif /* NHU_VER1 */

/** @def nhudecodesta NHU Decode status*/
#define NHU_DECODE_SUCCESS         0
#define NHU_DECODE_FAIL            1

/** @def nhuencodesta NHU Encode status*/
#define NHU_ENCODE_SUCCESS         0
#define NHU_ENCODE_FAIL            1

/** @def nhumerrtype NHU Error Type */
#define NHU_ERRTYPE_NONE                    0x00 /* reserved, not to be used */
#define NHU_ERRTYPE_RLC_DAT_IND             0x01
#define NHU_ERRTYPE_PDCP_DAT_IND            0x02
#define NHU_ERRTYPE_PDCP_DAT_CFM            0x03
#define NHU_ERRTYPE_INV_DEL_TRANS_REQ       0x04
#define NUU_ERRTYPE_INV_CNCL_UE_REQ         0x05
#define NHU_ERRTYPE_INV_SDU_PARAM           0x06
#define NHU_ERRTYPE_ENC_FAILED              0x07
#define NHU_ERRTYPE_DEC_FAILED              0x08
#define NHU_ERRTYPE_INV_NHU_HDR             0x09
#define NHU_ERRTYPE_INV_UE_MSG_PARAM        0x0a
#define NHU_ERRTYPE_INV_CFG                 0x0b
#define NHU_ERRTYPE_TX_FAILED               0x0c
#define NHU_ERRTYPE_INV_RLS_REQ             0x0d
#define NHU_ERRTYPE_MSG_SEND_FAILED         0x0e
#define NHU_ERRTYPE_UE_CFG                  0x0f
#define NHU_ERRTYPE_CELL_CFG                0x10
#define NHU_ERRTYPE_MAX_CONN                0x11

/** @def nhumerrcause NHU Error Cause */
#define NHU_ERRCAUSE_NONE                       0x00
#define NHU_ERRCAUSE_WRONG_RB_ID                0x01
#define NHU_ERRCAUSE_CELL_NOT_CONFIGURED      0x02
#define NHU_ERRCAUSE_UE_NOT_CONFIGURED        0x03
#define NHU_ERRCAUSE_RB_NOT_CONFIGURED          0x04
#define NHU_ERRCAUSE_CFG_IN_PROGRESS            0x05
#define NHU_ERRCAUSE_INV_HDR_CELLID             0x06
#define NHU_ERRCAUSE_INV_HDR_UEID               0x07
#define NHU_ERRCAUSE_DUPLICATE_RXTRANSID        0x08
#define NHU_ERRCAUSE_DUPLICATE_RRCTRANSID       0x09
#define NHU_ERRCAUSE_TRANSCB_UPD_FAIL           0x0a
#define NHU_ERRCAUSE_LOW_LYR_CFG_FAIL           0x0b
#define NHU_ERRCAUSE_TRANSCB_NOT_FOUND          0x0c
#define NHU_ERRCAUSE_INVALID_CFG_INFO           0x0d
#define NHU_ERRCAUSE_INV_BITMASK                0x0e
#define NHU_ERRCAUSE_INV_SDU_CHOICE_VAL         0x0f
#define NHU_ERRCAUSE_INV_MSG_CATEGORY           0x10
#define NHU_ERRCAUSE_INV_TRCH                   0x11
#define NHU_ERRCAUSE_INV_CFG_TYPE               0x12
#define NHU_ERRCAUSE_RLS_IN_PROGRESS            0x13
#define NHU_ERRCAUSE_FAILED_SENDTORLC           0x14
#define NHU_ERRCAUSE_INV_RB_CFG_INFO            0x15
#define NHU_ERRCAUSE_CFG_PARAM_OUT_OF_BOUNDS    0x16
#define NHU_ERRCAUSE_TIMEOUT                    0x17
#define NHU_ERRCAUSE_INVALID_TBS_SIZE           0x18
#define NHU_ERRCAUSE_WRONG_PDCP_ID              0x19
#define NHU_ERRCAUSE_SRB1_NOT_CONFIGURED        0x1A
#define NHU_ERRCAUSE_SEC_NOT_CONFIGURED         0x1B
#define NHU_ERRCAUSE_DUPLICATE_CELL             0x1C
#define NHU_ERRCAUSE_INVALID_CELLID             0x1D
#define NHU_ERRCAUSE_DAT_CFM_DISCARD            0x1E
#define NHU_ERRCAUSE_CRNTI_NOT_CFG              0x1F
#define NHU_ERRCAUSE_CRNTI_MISMATCH             0x20
#define NHU_ERRCAUSE_INTEGRITY_FAILED           0x21
#define NHU_ERRCAUSE_DECIPHERING_FAILED         0x22
#define NHU_ERRCAUSE_MAX_RLC_TRANS_REACH        0x23
#define NHU_ERRCAUSE_PDCP_SDU_DIS_TMR_EXP       0x24
#define NHU_ERRCAUSE_INVALID_MUI                0x25
#define NHU_ERRCAUSE_UE_CB_CREATE_FAILED        0x26
#define NHU_ERRCAUSE_UE_WRONG_MSG_TYP_SEL       0x27
#define NHU_ERRCAUSE_INV_SDU_TYP                0x28
#ifdef RRC_PHY_CFG_SUPP
#define NHU_ERRCAUSE_INVALID_PHYCFG_INFO        0x29
#define NHU_ERRCAUSE_INV_PHYCFG_BITMASK         0x2A
#endif /* RRC_PHY_CFG_SUPP */
#define NHU_ERRCAUSE_UNPROTECTED_PENDING        0x2B
/* Condition IEs Error Causes*/
#ifdef NH_ASN_COND_VALIDATE
#define NHU_ERRCAUSE_COND_IE_FAIL               0x2C
#endif /* ifdef NH_ASN_COND_VALIDATE */
#define NHU_ERRCAUSE_INV_SEC_CFG                0x2D
#define NHU_ERRCAUSE_MAX_DRB                    0x2E
#define NHU_ERRCAUSE_DECOMPRESSION_FAILED       0x2F
#define NHU_ERRCAUSE_COMPRESSION_FAILED         0x30
#define NHU_ERRCAUSE_INTEG_PROT_FAILED          0x31
#define NHU_ERRCAUSE_CIPHERING_FAILED           0x32
/* nhu_h_001.main_2 - Addition of error cause 
 *  for lower layer SAP not available 
 */
#define NHU_ERRCAUSE_LLYR_SAP_NOT_EXIST         0x33
/* nhu_h_001.main_3: added error cause for SRB2 and DRBs not established*/
#ifdef NHU_VER1
#define NHU_ERRCAUSE_SRB2_NOT_ESTABLISHED       0x34
#define NHU_ERRCAUSE_DRBS_NOT_ESTABLISHED       0x35
#endif /* NHU_VER1 */

/** @def Configuration Type */
#define NHU_CFGTYPE_SETUP      0x01 /* Setup */
#define NHU_CFGTYPE_MODIFY     0x02 /* Modify */
#define NHU_CFGTYPE_RELEASE    0x04 /* Release */


/** @def Bitmask for data request */
#define NHU_DAT_UE_MSG   0x01
#define NHU_DAT_UE_CFG   0x02

/** @def Bitmask for RB configuration list */
#define NHU_CFG_RB_ADD       0x01
#define NHU_CFG_RB_MODIFY    0x02
#define NHU_CFG_RB_RLS       0x04

/** @def NhuCfgErrType */
#define NHU_CFGERRTYPE_RLC   0x01 /* RLC Configuration error */
#define NHU_CFGERRTYPE_MAC   0x02 /* MAC Configuration error */
#define NHU_CFGERRTYPE_PDCP  0x04 /* PDCP Configuration error */
#ifdef RRC_PHY_CFG_SUPP
#define NHU_CFGERRTYPE_PHY  0x08 /* PHY Configuration error */
#endif /* RRC_PHY_CFG_SUPP */

/** @def NhuCfgErrCause */
#define NHU_CFGERRCAUSE_INV_PARAM     0x01 /* Invalid parameters */
#define NHU_CFGERRCAUSE_INV_STATE     0x02 /* invalid state */
#define NHU_CFGERRCAUSE_INCOMPATIBLE  0x03 /* Incompatible configuration */
#define NHU_CFGERRCAUSE_UNKNOWN       0x04 /* Unknown error at layer */
#define NHU_CFGERRCAUSE_TMR_EXPIRED   0x05 /* Timer expired during layer configuration */

/** @def RRC Connection REconfiguration Causes */
#define NHU_CONN_RECFG_AT_HNDOVR      0x01 /*Connection reconfiguration 
                                             during handover*/
#define NHU_CONN_RECFG_AFTER_RESTB    0x02 /*first connection reconfiguration
                                              after re-establishment */
#define NHU_CONN_RESTB_EVNT           0x04 /*Connection re-establishment event*/
#define NHU_CONN_RECFG_FOR_MESR_CFG   0x08 /*Measurement Configuration at UE event*/

/** @def CfgSrc in NhuCfgSdus */
#define NHU_CFG_TYPE_EXPLICIT     0x01 /* Explicit Configuration */
#define NHU_CFG_TYPE_MSAP         0x02 /* Explicit Configuration */

/** @def Default configuration in NhuCfgSdus */
#define NHU_CFG_TYPE_DFLT         0x04 /* Default Configuration */

/** @def Coupling flags */
#define NHU_SEL_LC   0
#define NHU_SEL_TC   1
#define NHU_SEL_LWLC 2

#define NHU_MAX_SUB_FRAME_NUM  10

#define NHU_MAX_ROHC_PROF_LST_LEN 9

#define NHU_CIPH_KEY_LEN 16
#define NHU_INTG_KEY_LEN 16

#define NHU_MAX_DIR          2
#define NHU_DIR_UPLINK       0
#define NHU_DIR_DOWNLINK     1

/** @def Bit Mask For PDCP configuration */
#define NHU_PDCP_DISCARD_TMR     0x01
#define NHU_PDCP_FLUSH_TMR       0x02
#define NHU_PDCP_SN_SIZE         0x04
#define NHU_PDCP_STATUS_RPT      0x08
#define NHU_PDCP_HDR_COMPR_INFO  0x10
#define NHU_PDCP_SDU_STA_INFO    0x20
#define NHU_PDCP_CFM_REQD        0x40

/** @def Security configuration Bitmask */
#define NHU_SEC_CIPHER_ALGO    0x01
#define NHU_SEC_INTG_ALGO      0x02

/** @def Actions that can be used across NHU */
#define NHU_ACTION_ADD         0x01
#define NHU_ACTION_MODIFY      0x02
#define NHU_ACTION_RLS         0x03

/** @def INfo choice for RLC mode */
#define NHU_RLC_MODE_TM        0x01
#define NHU_RLC_MODE_UM        0x02
#define NHU_RLC_MODE_AM        0x03


/** @def BitMask for UL Logical Channel Mapping */
#define NHU_UL_LOGCH_MAP_GRP    0x04

/** @def Bit Mask For Explicit configuration */
#define NHU_EXP_CFG_RB_CFG     0x01
#define NHU_EXP_CFG_TRCH_CFG   0x02
#define NHU_EXP_CFG_SEC_CFG    0x04
#define NHU_EXP_CFG_UE_CFG     0x08
#ifdef LTE_ADV
#define NHU_EXP_CFG_UESEC_CFG  0x10
#endif /* LTE_ADV */
#ifdef RRC_PHY_CFG_SUPP
#define NHU_EXP_CFG_PHY_CFG    0x20
#endif /* RRC_PHY_CFG_SUPP */

/** @def BitMask for Trch configuration */
#define NHU_TRCH_CFG_UL_HARQ  0x01


/** @def BitMask for Cell configuration */
#define NHU_CELL_CFG_RB       0x01
#define NHU_CELL_CFG_MSAP     0x02
#define NHU_CELL_PHY_CFG      0x04
#define NHU_CELL_CFG_MAC_CMN  0x08

/** @def Bitmask for Cell Reconfiguration */
#define NHU_CELL_RECFG_RB       0x01
#define NHU_CELL_RECFG_RACH     0x02
#define NHU_CELL_RECFG_MSAP     0x04


/** @def BitMask for Cell configuration types*/
#define NHU_CELL_CFG_INFO       0x01
#define NHU_CELL_RECFG_INFO     0x02
#define NHU_CELL_RLS_INFO       0x04


/** @def MSAP SAP ID configuration */
#define NHU_KWU_SAP_ID_INFO      0x01
#define NHU_CKW_SAP_ID_INFO      0x02
#define NHU_CRG_SAP_ID_INFO      0x04
#define NhU_CDM_SAP_ID_INFO      0x08
#define NhU_DMU_SAP_ID_INFO      0x10

/** @def Bitmask for NhuUlRbCfg */
#define NHU_RB_CFG_LOGCH_MAP_UL  0x01
#define NHU_RB_CFG_RLC_MODE_UL   0x02

/** @def Bitmask for NhuDlRbCfg */
#define NHU_RB_CFG_LOGCH_MAP_DL  0x01
#define NHU_RB_CFG_RLC_MODE_DL   0x02

/** @def Bitmask for NhuRbCfgInfo */
#define NHU_RB_CFG_UL            0x01
#define NHU_RB_CFG_DL            0x02
#define NHU_RB_CFG_PDCP_INFO     0x04

#define NHU_CONRES_ID_LEN        6

/** @def RAT Types */
#define NHU_RAT_TYP_EUTRA  1     /* E-UTRA RAT */
#define NHU_RAT_TYP_UTRA   2     /* UTRA RAT */


/* Maximum NUmber of DRBs supported per UE */
#define NHU_MAX_DRB        11

#ifdef LTE_ADV
#define NHU_MAX_SCELL_PER_UE      7
#endif /* LTE_ADV */


#ifdef RRC_PHY_CFG_SUPP
/** @def Bitmask flags for common channel PHY configurations */
#define NHU_CMN_PHY_CFG_PRACH        0x01
#define NHU_CMN_PHY_CFG_PDSCH        0x02
#define NHU_CMN_PHY_CFG_PUSCH        0x04
#define NHU_CMN_PHY_CFG_PHICH        0x08
#define NHU_CMN_PHY_CFG_PUCCH        0x10
#define NHU_CMN_PHY_CFG_UL_SRS       0x20
#define NHU_CMN_PHY_CFG_TDD_SF       0x40

/** @def Bitmask flags for UE-specific PHY configurations */
#define NHU_DED_PHY_CFG_UE_CAT       0x01 
#define NHU_DED_PHY_CFG_PDSCH        0x02
#define NHU_DED_PHY_CFG_PUCCH        0x04
#define NHU_DED_PHY_CFG_PUSCH        0x08
#define NHU_DED_PHY_CFG_CQI          0x10
#define NHU_DED_PHY_CFG_UL_SRS       0x20
#define NHU_DED_PHY_CFG_SR           0x40
#define NHU_DED_PHY_CFG_ANT          0x80
/* nhu_h_001.main_3: bit mask added for cqi*/
#ifdef NHU_VER1
#define NHU_DED_PHY_CFG_CQI_R9       0x100
#endif /* NHU_VER1 */

/** @def Macros for CQI report mode configurations */
#define NHU_CQI_RPTMODE_APERIODIC    0x01
#define NHU_CQI_RPTMODE_PERIODIC     0x02

/** @def Macros for Default UE-specific PUSCH configurations
 *       [Ref: 36.331, 9.2.4] 
*/
#define NHU_DED_PUSCH_BETAOFF_ACK_IDX  10
#define NHU_DED_PUSCH_BETAOFF_RI_IDX   12
#define NHU_DED_PUSCH_BETAOFF_CQI_IDX  15

/** @def Macros for sub-carrier spacing values in NhuTxSchmCfg */
#define NHU_TX_SCHM_SC_SPACING_15KHZ      1  /* 15 kHz */
#define NHU_TX_SCHM_SC_SPACING_7DOT5KHZ   2  /* 7.5 kHz */

#endif /* RRC_PHY_CFG_SUPP */

/** @def Macros for filling PDCP SDU status information */
#define NHU_HO_NOT_PRSNT 0x00
#define NHU_HO_UL        0x01
#define NHU_HO_DL        0x02 /*nhu_h_001.main_4 :117414: corrected value*/

/* Error Codes */
#define ENHUXXX                      0
#define ERRNHU                       0

#define   ENHU001      (ERRNHU +    1)    /*        nhu.c:2604 */
#define   ENHU002      (ERRNHU +    2)    /*        nhu.c:2608 */
#define   ENHU003      (ERRNHU +    3)    /*        nhu.c:2609 */
#define   ENHU004      (ERRNHU +    4)    /*        nhu.c:2651 */
#define   ENHU005      (ERRNHU +    5)    /*        nhu.c:2655 */
#define   ENHU006      (ERRNHU +    6)    /*        nhu.c:2656 */
#define   ENHU007      (ERRNHU +    7)    /*        nhu.c:2698 */
#define   ENHU008      (ERRNHU +    8)    /*        nhu.c:2702 */
#define   ENHU009      (ERRNHU +    9)    /*        nhu.c:2703 */
#define   ENHU010      (ERRNHU +   10)    /*        nhu.c:2746 */
#define   ENHU011      (ERRNHU +   11)    /*        nhu.c:2762 */
#define   ENHU012      (ERRNHU +   12)    /*        nhu.c:2771 */
#define   ENHU013      (ERRNHU +   13)    /*        nhu.c:2775 */
#define   ENHU014      (ERRNHU +   14)    /*        nhu.c:2817 */
#define   ENHU015      (ERRNHU +   15)    /*        nhu.c:2835 */
#define   ENHU016      (ERRNHU +   16)    /*        nhu.c:2844 */
#define   ENHU017      (ERRNHU +   17)    /*        nhu.c:2848 */
#define   ENHU018      (ERRNHU +   18)    /*        nhu.c:2890 */
#define   ENHU019      (ERRNHU +   19)    /*        nhu.c:2910 */
#define   ENHU020      (ERRNHU +   20)    /*        nhu.c:2920 */
#define   ENHU021      (ERRNHU +   21)    /*        nhu.c:2924 */
#define   ENHU022      (ERRNHU +   22)    /*        nhu.c:2966 */
#define   ENHU023      (ERRNHU +   23)    /*        nhu.c:2986 */
#define   ENHU024      (ERRNHU +   24)    /*        nhu.c:2996 */
#define   ENHU025      (ERRNHU +   25)    /*        nhu.c:3001 */
#define   ENHU026      (ERRNHU +   26)    /*        nhu.c:3043 */
#define   ENHU027      (ERRNHU +   27)    /*        nhu.c:3063 */
#define   ENHU028      (ERRNHU +   28)    /*        nhu.c:3073 */
#define   ENHU029      (ERRNHU +   29)    /*        nhu.c:3077 */
#define   ENHU030      (ERRNHU +   30)    /*        nhu.c:3120 */
#define   ENHU031      (ERRNHU +   31)    /*        nhu.c:3137 */
#define   ENHU032      (ERRNHU +   32)    /*        nhu.c:3146 */
#define   ENHU033      (ERRNHU +   33)    /*        nhu.c:3150 */
#define   ENHU034      (ERRNHU +   34)    /*        nhu.c:3192 */
#define   ENHU035      (ERRNHU +   35)    /*        nhu.c:3212 */
#define   ENHU036      (ERRNHU +   36)    /*        nhu.c:3222 */
#define   ENHU037      (ERRNHU +   37)    /*        nhu.c:3226 */
#define   ENHU038      (ERRNHU +   38)    /*        nhu.c:3270 */
#define   ENHU039      (ERRNHU +   39)    /*        nhu.c:3274 */
#define   ENHU040      (ERRNHU +   40)    /*        nhu.c:3275 */
#define   ENHU041      (ERRNHU +   41)    /*        nhu.c:3276 */
#define   ENHU042      (ERRNHU +   42)    /*        nhu.c:3319 */
#define   ENHU043      (ERRNHU +   43)    /*        nhu.c:3336 */
#define   ENHU044      (ERRNHU +   44)    /*        nhu.c:3345 */
#define   ENHU045      (ERRNHU +   45)    /*        nhu.c:3349 */
#define   ENHU046      (ERRNHU +   46)    /*        nhu.c:3391 */
#define   ENHU047      (ERRNHU +   47)    /*        nhu.c:3410 */
#define   ENHU048      (ERRNHU +   48)    /*        nhu.c:3420 */
#define   ENHU049      (ERRNHU +   49)    /*        nhu.c:3425 */
#define   ENHU050      (ERRNHU +   50)    /*        nhu.c:3471 */
#define   ENHU051      (ERRNHU +   51)    /*        nhu.c:3488 */
#define   ENHU052      (ERRNHU +   52)    /*        nhu.c:3497 */
#define   ENHU053      (ERRNHU +   53)    /*        nhu.c:3501 */
#define   ENHU054      (ERRNHU +   54)    /*        nhu.c:3559 */
#define   ENHU055      (ERRNHU +   55)    /*        nhu.c:3581 */
#define   ENHU056      (ERRNHU +   56)    /*        nhu.c:3596 */
#define   ENHU057      (ERRNHU +   57)    /*        nhu.c:3602 */
#define   ENHU058      (ERRNHU +   58)    /*        nhu.c:3607 */
#define   ENHU059      (ERRNHU +   59)    /*        nhu.c:3651 */
#define   ENHU060      (ERRNHU +   60)    /*        nhu.c:3657 */
#define   ENHU061      (ERRNHU +   61)    /*        nhu.c:3702 */
#define   ENHU062      (ERRNHU +   62)    /*        nhu.c:3719 */
#define   ENHU063      (ERRNHU +   63)    /*        nhu.c:3728 */
#define   ENHU064      (ERRNHU +   64)    /*        nhu.c:3733 */
#define   ENHU065      (ERRNHU +   65)    /*        nhu.c:3779 */
#define   ENHU066      (ERRNHU +   66)    /*        nhu.c:3783 */
#define   ENHU067      (ERRNHU +   67)    /*        nhu.c:3784 */
#define   ENHU068      (ERRNHU +   68)    /*        nhu.c:3785 */
#define   ENHU069      (ERRNHU +   69)    /*        nhu.c:3786 */
#define   ENHU070      (ERRNHU +   70)    /*        nhu.c:3832 */
#define   ENHU071      (ERRNHU +   71)    /*        nhu.c:3849 */
#define   ENHU072      (ERRNHU +   72)    /*        nhu.c:3858 */
#define   ENHU073      (ERRNHU +   73)    /*        nhu.c:3863 */
#define   ENHU074      (ERRNHU +   74)    /*        nhu.c:6105 */
#define   ENHU075      (ERRNHU +   75)    /*        nhu.c:6124 */
#define   ENHU076      (ERRNHU +   76)    /*        nhu.c:6132 */
#define   ENHU077      (ERRNHU +   77)    /*        nhu.c:7730 */
#define   ENHU078      (ERRNHU +   78)    /*        nhu.c:7731 */
#define   ENHU079      (ERRNHU +   79)    /*        nhu.c:7768 */
#define   ENHU080      (ERRNHU +   80)    /*        nhu.c:7769 */
#define   ENHU081      (ERRNHU +   81)    /*        nhu.c:7806 */
#define   ENHU082      (ERRNHU +   82)    /*        nhu.c:7807 */
#define   ENHU083      (ERRNHU +   83)    /*        nhu.c:7849 */
#define   ENHU084      (ERRNHU +   84)    /*        nhu.c:7868 */
#define   ENHU085      (ERRNHU +   85)    /*        nhu.c:7876 */
#define   ENHU086      (ERRNHU +   86)    /*        nhu.c:7921 */
#define   ENHU087      (ERRNHU +   87)    /*        nhu.c:7941 */
#define   ENHU088      (ERRNHU +   88)    /*        nhu.c:7949 */
#define   ENHU089      (ERRNHU +   89)    /*        nhu.c:7990 */
#define   ENHU090      (ERRNHU +   90)    /*        nhu.c:8003 */
#define   ENHU091      (ERRNHU +   91)    /*        nhu.c:8018 */
#define   ENHU092      (ERRNHU +   92)    /*        nhu.c:8026 */
#define   ENHU093      (ERRNHU +   93)    /*        nhu.c:8067 */
#define   ENHU094      (ERRNHU +   94)    /*        nhu.c:8081 */
#define   ENHU095      (ERRNHU +   95)    /*        nhu.c:8096 */
#define   ENHU096      (ERRNHU +   96)    /*        nhu.c:8104 */
#define   ENHU097      (ERRNHU +   97)    /*        nhu.c:8145 */
#define   ENHU098      (ERRNHU +   98)    /*        nhu.c:8158 */
#define   ENHU099      (ERRNHU +   99)    /*        nhu.c:8173 */
#define   ENHU100      (ERRNHU +  100)    /*        nhu.c:8181 */
#define   ENHU101      (ERRNHU +  101)    /*        nhu.c:8226 */
#define   ENHU102      (ERRNHU +  102)    /*        nhu.c:8245 */
#define   ENHU103      (ERRNHU +  103)    /*        nhu.c:8253 */
#define   ENHU104      (ERRNHU +  104)    /*        nhu.c:8295 */
#define   ENHU105      (ERRNHU +  105)    /*        nhu.c:8308 */
#define   ENHU106      (ERRNHU +  106)    /*        nhu.c:8323 */
#define   ENHU107      (ERRNHU +  107)    /*        nhu.c:8331 */
#define   ENHU108      (ERRNHU +  108)    /*        nhu.c:8373 */
#define   ENHU109      (ERRNHU +  109)    /*        nhu.c:8374 */
#define   ENHU110      (ERRNHU +  110)    /*        nhu.c:8375 */
#define   ENHU111      (ERRNHU +  111)    /*        nhu.c:8418 */
#define   ENHU112      (ERRNHU +  112)    /*        nhu.c:8437 */
#define   ENHU113      (ERRNHU +  113)    /*        nhu.c:8445 */
#define   ENHU114      (ERRNHU +  114)    /*        nhu.c:8491 */
#define   ENHU115      (ERRNHU +  115)    /*        nhu.c:8510 */
#define   ENHU116      (ERRNHU +  116)    /*        nhu.c:8518 */
#define   ENHU117      (ERRNHU +  117)    /*        nhu.c:8559 */
#define   ENHU118      (ERRNHU +  118)    /*        nhu.c:8573 */
#define   ENHU119      (ERRNHU +  119)    /*        nhu.c:8588 */
#define   ENHU120      (ERRNHU +  120)    /*        nhu.c:8596 */
#define   ENHU121      (ERRNHU +  121)    /*        nhu.c:8637 */
#define   ENHU122      (ERRNHU +  122)    /*        nhu.c:8638 */
#define   ENHU123      (ERRNHU +  123)    /*        nhu.c:8681 */
#define   ENHU124      (ERRNHU +  124)    /*        nhu.c:8702 */
#define   ENHU125      (ERRNHU +  125)    /*        nhu.c:8710 */
#define   ENHU126      (ERRNHU +  126)    /*        nhu.c:8750 */
#define   ENHU127      (ERRNHU +  127)    /*        nhu.c:8764 */
#define   ENHU128      (ERRNHU +  128)    /*        nhu.c:8779 */
#define   ENHU129      (ERRNHU +  129)    /*        nhu.c:8787 */
#define   ENHU130      (ERRNHU +  130)    /*        nhu.c:8829 */
#define   ENHU131      (ERRNHU +  131)    /*        nhu.c:8830 */
#define   ENHU132      (ERRNHU +  132)    /*        nhu.c:8831 */
#define   ENHU133      (ERRNHU +  133)    /*        nhu.c:8832 */
#define   ENHU134      (ERRNHU +  134)    /*        nhu.c:9367 */
#define   ENHU135      (ERRNHU +  135)    /*        nhu.c:9384 */
#define   ENHU136      (ERRNHU +  136)    /*        nhu.c:9401 */
#define   ENHU137      (ERRNHU +  137)    /*        nhu.c:9405 */
#define   ENHU138      (ERRNHU +  138)    /*        nhu.c:9409 */
#define   ENHU139      (ERRNHU +  139)    /*        nhu.c:9456 */
#define   ENHU140      (ERRNHU +  140)    /*        nhu.c:9474 */
#define   ENHU141      (ERRNHU +  141)    /*        nhu.c:9484 */
#define   ENHU142      (ERRNHU +  142)    /*        nhu.c:9496 */
#define   ENHU143      (ERRNHU +  143)    /*        nhu.c:9543 */
#define   ENHU144      (ERRNHU +  144)    /*        nhu.c:9561 */
#define   ENHU145      (ERRNHU +  145)    /*        nhu.c:9570 */
#define   ENHU146      (ERRNHU +  146)    /*        nhu.c:9575 */
#define   ENHU147      (ERRNHU +  147)    /*        nhu.c:9620 */
#define   ENHU148      (ERRNHU +  148)    /*        nhu.c:9637 */
#define   ENHU149      (ERRNHU +  149)    /*        nhu.c:9646 */
#define   ENHU150      (ERRNHU +  150)    /*        nhu.c:9650 */
#define   ENHU151      (ERRNHU +  151)    /*        nhu.c:9692 */
#define   ENHU152      (ERRNHU +  152)    /*        nhu.c:9706 */
#define   ENHU153      (ERRNHU +  153)    /*        nhu.c:9720 */
#define   ENHU154      (ERRNHU +  154)    /*        nhu.c:9728 */
#define   ENHU155      (ERRNHU +  155)    /*        nhu.c:9781 */
#define   ENHU156      (ERRNHU +  156)    /*        nhu.c:9797 */
#define   ENHU157      (ERRNHU +  157)    /*        nhu.c:9810 */
#define   ENHU158      (ERRNHU +  158)    /*        nhu.c:9818 */
#define   ENHU159      (ERRNHU +  159)    /*        nhu.c:9864 */
#define   ENHU160      (ERRNHU +  160)    /*        nhu.c:9876 */
#define   ENHU161      (ERRNHU +  161)    /*        nhu.c:9887 */
#define   ENHU162      (ERRNHU +  162)    /*        nhu.c:9897 */
#define   ENHU163      (ERRNHU +  163)    /*        nhu.c:9949 */
#define   ENHU164      (ERRNHU +  164)    /*        nhu.c:9965 */
#define   ENHU165      (ERRNHU +  165)    /*        nhu.c:9977 */
#define   ENHU166      (ERRNHU +  166)    /*        nhu.c:9985 */

#endif /* __NHU_H__ */

/**********************************************************************
         End of file:     nhu.h@@/main/4 - Thu Jun 30 16:22:58 2011
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      ds       1. LTE RRC Initial Release.
/main/3      ---      nhu_h_001.main_2  vkulkarni  1. Addition of error cause 
                                        for lower layer SAP not available
/main/4      ---      nhu_h_001.main_3  sbalakrishna 1. Updated for Release of 3.1.
                                        2. error cause addef for SRB2 and DRBs not established.
                                        3. Msg type is added for varShotMAC-Input.
                                        4. Sib types added for sib12 and sib13
/main/5      ---      nhu_h_001.main_4   mpatel        1. corrected the value of NHU_HO_DL                                                 
*********************************************************************91*/
