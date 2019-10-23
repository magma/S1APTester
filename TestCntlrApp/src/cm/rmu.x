
/********************************************************************20**

     Name:     ENB APP Layer

     Type:     C source file

     Desc:     C Source code for ENB APP - RRM interface structures

     File:     rmu.x

     Sid:      rmu.x@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/T2K_MergeTemp_BR/1 - Mon Sep  2 16:44:23 2013

     Prg:      rb

*********************************************************************21*/

#ifndef __RMUX__
#define __RMUX__

#include "cm_lte_rrm.x"
#ifdef __cplusplus
EXTERN "C" {
#endif

/***** Structures and enums for Interface function parameters *****/

typedef enum rmuS1apCause
{
   RMU_CAUSE_UNSPECIFIED,
   RMU_CAUSE_TX2_RELOC_OVERALL_EXP,
   RMU_CAUSE_SUCC_HANDOVER,
   RMU_CAUSE_REL_EUTRAN_REASON,
   RMU_CAUSE_HANDOVER_CANCELLED,
   RMU_CAUSE_PARTIAL_HANDOVER,
   RMU_CAUSE_HANDOVER_FAILURE_TRGT_SYS,
   RMU_CAUSE_HANDOVER_TRGT_NOT_ALLOWED,
   RMU_CAUSE_TS1_RELOCOVERALL_EXP,
   RMU_CAUSE_TS1_RELOCPREP_EXP,
   RMU_CAUSE_CELL_NOTAVAILABLE,
   RMU_CAUSE_UNKNOWN_TRGT_ID,
   RMU_CAUSE_NO_RESOURCES_IN_TRGT_CELL,
   RMU_CAUSE_UNKNOWN_ALLOC_MME_UE_S1AP_ID,
   RMU_CAUSE_UNKNOWN_ALLOC_ENB_UE_S1AP_ID,
   RMU_CAUSE_UNKNOWN_INCONSIST_PAIR_UE_S1AP_ID,
   RMU_CAUSE_HANDOVER_DESIRABLE_RADIO_REASON,
   RMU_CAUSE_TIME_CRITICAL_HANDOVER,
   RMU_CAUSE_RESOURCE_OPTIMIZE_HANDOVER,
   RMU_CAUSE_REDUCE_LOAD_IN_SERV_CELL,
   RMU_CAUSE_USR_INACTIVITY,
   RMU_CAUSE_RADIO_CON_UE_LOST,
   RMU_CAUSE_LOAD_BLNC_TAU_REQD,
   RMU_CAUSE_CS_FALLBACK_TRIGGERED,
   RMU_CAUSE_UE_NOTAVAILABLE_PS_SER,
   RMU_CAUSE_RADIO_RESOURCE_NOT_AVAIL,
   RMU_CAUSE_FAIL_RADIO_INTF_PROC,
   RMU_CAUSE_INVALID_QOS_COMB,
   RMU_CAUSE_INTER_RAT_REDIRECT,
   RMU_CAUSE_INTERACT_ITHER_PROC,
   RMU_CAUSE_UNKNOWN_ERAB_ID,
   RMU_CAUSE_MULT_ERAB_ID_INSTANCES,
   RMU_CAUSE_ENCRYPT_INTEGRITY_NOT_SUPPORT,
   RMU_CAUSE_S1_INTRA_SYS_HANDOVER_TRIGGERED,
   RMU_CAUSE_S1_INTER_SYS_HANDOVER_TRIGGERED,
   RMU_CAUSE_X2_HANDOVER_TRIGGERED,
   RMU_CAUSE_REDIRECT_1XRTT,
   RMU_CAUSE_NOT_SUPPORT_QCI,
   RMU_CAUSE_INVALID_CSG_ID,
   RMU_CAUSE_BH_BW_NOT_AVAILABLE,
   RMU_CAUSE_MAX_QCI_REACHED,
   RMU_CAUSE_CHECK_PRB_REQ
}RmuS1apCause;


/* SPS changes starts */
/*----- AccessStratumRelease ------- */
typedef enum rmuAccessStratumRls
{                                                                 
   RMU_ACCESS_STRATUM_REL8,
   RMU_ACCESS_STRATUM_REL9,
   RMU_ACCESS_STRATUM_REL9HIGHER
} RmuAccessStratumRls;
/* SPS changes ends */

typedef struct rmuAcbParamInd
{
  CmRrmAcbInfo stAcbInfo;
} CM_PACK_STRUCT RmuAcbParamInd;

typedef enum rmuCellRecfgType
{
   RMU_CELL_RECFG_ACB_IND
}RmuCellRecfgType;

typedef struct rmuCellRecfgInd
{
   RmuAcbParamInd             stAcbParamInd;
   RmuCellRecfgType           enCellRecfgType;       /* Cell reconfig type */
   U8                         bCellId;               /* Cell Identifier */
} CM_PACK_STRUCT RmuCellRecfgInd;

/******* WR_RM_FSM_STATUS_IND (FSM->RRM)*******************/

typedef enum rmuEnbStatus
{
   RMU_ENB_STATUS_UP,
   RMU_ENB_STATUS_DOWN
}RmuEnbStatus;

typedef enum rmuMmeStatus
{
   RMU_MME_STATUS_UP = 0,
   RMU_MME_STATUS_DOWN
}RmuMmeStatus;

typedef struct rmuMmeStatusInd
{
  RmuMmeStatus            enMmeStatus; /* MME status */
  U16                     usMmeId;     /* MME ID */
} CM_PACK_STRUCT RmuMmeStatusInd;

typedef struct rmuEnbStatusInd
{
  U8                      bCellId;     /* Cell Identifier */
  RmuEnbStatus            enEnbStatus; /* ENB status */
} CM_PACK_STRUCT RmuEnbStatusInd;



typedef enum rmuFsmStatusType
{
   RMU_FSM_STATUS_MME,
   RMU_FSM_STATUS_ENB
}RmuFsmStatusType;

typedef struct rmuFsmStatusInd
{
  RmuFsmStatusType        enStatusType;    /*Status type*/
  union {
      RmuMmeStatusInd     stMmeStatusInd;  /*Mme status indication*/ 
      RmuEnbStatusInd     stEnbStatusInd;  /*Enb status indication */
  }u;
} CM_PACK_STRUCT RmuFsmStatusInd;

/******* WR_RM _MME_OVERLOAD_START_IND (FSM->RRM) *********/

typedef enum rmuMmeOvldStatus
{
   RMU_MME_REJECT_MODATA,
   RMU_MME_REJECT_MOSIG_MODATA,
   RMU_MME_PERMITONLY_EMG_MTACCESS,
   RMU_MME_PERMITONLY_HIGHPRI_MTACCESS,
   RMU_MME_REJECT_DELAY_TOLERNT_ACCESS,
   RMU_MME_OVLD_STATUS_NORMAL
}RmuMmeOvldStatus;

typedef struct rmuMmeOvldStartInd
{
   RmuMmeOvldStatus           enMmeOvldStatus;    /* MME overload status Info */
   U16                        usMmeId;            /* MME ID  */
} CM_PACK_STRUCT RmuMmeOvldStartInd;

/******* WR_RM_MME_OVERLOAD_STOP_IND (FSM->RRM) *********/
typedef struct rmuMmeOvldStopInd
{
   U16                        usMmeId;            /* MME ID          */
} CM_PACK_STRUCT RmuMmeOvldStopInd;

/******* WR_RM_UE_ADMIT_REQ (FSM->RRM) *********/
typedef enum rmuConEstCause
{
   RMU_EST_CAUSE_EMERGENCY,
   RMU_EST_CAUSE_HIGH_PRIORTY_ACCESS,
   RMU_EST_CAUSE_MT_ACCESS,
   RMU_EST_CAUSE_MO_SIGNALLING,
   RMU_EST_CAUSE_MO_DATA,
   RMU_EST_CAUSE_DELAY_TOLERANT,
   RMU_EST_CAUSE_HO_REQ, /*RRM Is using this for HO->RAC communication*/
   RMU_MAX_EST_CAUSE
} RmuConEstCause;

typedef struct rmuUeAdmitReq
{
   RmuConEstCause             enConEstabCause;   /* Con estb cause value */
   U32                        uiTransId;         /* Transaction ID */
   U16                        usCrnti;           /* UE Crnti value */   
   U8                         bCellId;           /* Cell Identifier */
} CM_PACK_STRUCT RmuUeAdmitReq;

/******* RM_WR_UE_ADMIT_RSP (RRM->FSM) *********/
typedef enum rmuRrcCause
{
   RMU_CAUSE_CELLID_UNKNOWN,
   RMU_CAUSE_MMEID_UNKNOWN,
   RMU_CAUSE_UEID_UNKNOWN,
   RMU_CAUSE_OUT_OF_RESOURCE,
   RMU_CAUSE_MAX_UE_REACHED,
   RMU_CAUSE_CELL_ALREADY_EXISTS,
   RMU_CAUSE_MME_ALREADY_EXISTS,
   RMU_CAUSE_UEID_ALREADY_EXISTS,
   RMU_CAUSE_ENB_ALREADY_UP,
   RMU_CAUSE_NOT_APP,
   RMU_CAUSE_MAX_CSG_UE_REACHED,
   RMU_CAUSE_MAX_NON_CSG_UE_REACHED,
   RMU_CAUSE_MAX_EXTRA_UE_REACHED,
   RMU_CAUSE_OTHER
} RmuRrcCause;

typedef enum rmuStatus
{
   RMU_FAILURE,
   RMU_SUCCESS,
   RMU_REDIRECT
} RmuStatus;

typedef struct rmuStatusInfo
{
   RmuRrcCause                 enCause;         /* Cause value in case of FAILURE */
   RmuStatus                   enStatus;        /* Response is failure or success */
} CM_PACK_STRUCT RmuStatusInfo;


/******* WR_RM_UE_HO_REQ (FSM->RRM) *********/
typedef enum rmuHandOverType
{
   RMU_HO_TYPE_IntraLTE,
   RMU_HO_TYPE_LTEtoUTRAN,
   RMU_HO_TYPE_LTEtoGERAN,
   RMU_HO_TYPE_UTRANtoLTE,
   RMU_HO_TYPE_GERANtoLTE,
   RMU_HO_TYPE_S1,
   RMU_HO_TYPE_X2
} RmuHandOverType;

typedef enum rmuErabAction
{
   RMU_ADD_ERAB,
   RMU_MOD_ERAB,
   RMU_DEL_ERAB
} RmuErabAction;

/*Post structure for NPk interface*/
typedef struct rmuPst
{
  U16 usDstProcId;
  U16 usSrcProcId;
  U8  bDstEnt;
  U8  bSstInst;
  U8  bSrcEnt;
  U8  bSrcInst;
  U8  bPrior;
  U8  bRoute;
  U8  bEvent;
} CM_PACK_STRUCT RmuPst;

typedef struct rmuUEAggreMaxBitRateIe 
{
   U32              uiAggUEMaxBitRateUL;   /* UE agg max bit rate UP link */
   U32              uiAggUEMaxBitRateDL;   /* UE agg max bit rate DOWN link */
} CM_PACK_STRUCT RmuUEAggreMaxBitRateIe;

typedef struct rmuErabGbrInfoIe 
{
   U32              uiErabDlMbr;   /* ERAB max bit rate DOWN link */
   U32              uiErabUlMbr;   /* ERAB max bit rate UP link */
   U32              uiErabDlGbr;   /* ERAB max bit rate DOWN link */
   U32              uiErabUlGbr;   /* ERAB max bit rate UP link */
} CM_PACK_STRUCT RmuErabGbrInfoIe;

typedef struct rmuErabArpInfoIe 
{
   U8              bErabPrioLvl;      /* ERAB priority */
   Bool            bErabPreemptCap;   /* ERAB preempt capability */
   Bool            bErabPreemptVul;   /* ERAB preempt vulnerability */
} CM_PACK_STRUCT RmuErabArpInfoIe;

typedef struct rmuErabQosInfoIe 
{
   RmuErabArpInfoIe            stErabArpInfo;    /* ERAB ARP information */
   RmuErabGbrInfoIe            stErabGbrInfo;    /* ERAB GBR information */
   U8                          bErabQCI;        /* Indicates the Quality 
                                                   Class Index of the Bearer */
} CM_PACK_STRUCT RmuUErabQosInfoIe;

typedef struct rmuErabAddModIe 
{
   RmuUErabQosInfoIe            stErabQosInfo;    /* ERAB QOS structure indicating 
                                                      QOS info of the bearer */
   U8                           bErabId;         /* E-RAB ID of the E-RAB needs 
                                                      to be added/modified */
} CM_PACK_STRUCT RmuUErabAddModIe;

typedef struct rmuErabRelIe
{
   RmuS1apCause            enErabRelCause;  /* Reason for releasing the ERAB */
   U8                      bErabId;         /* E-RAB ID of the E-RAB needs 
                                             to be released */
} CM_PACK_STRUCT RmuErabRelIe;

typedef struct rmuErabConfigIe 
{
   RmuUErabAddModIe        stErabAddModLst[RMU_MAX_NUM_ERABS];
   RmuErabRelIe            stErabRelLst[RMU_MAX_NUM_ERABS]; 
   RmuUEAggreMaxBitRateIe  stUeAmbrInfo;
   RmuErabAction           enErabAction;         /* ERAB action add or mod */
   U16                     usNoErabsToAddMod;    /* Number of ERABs to add or modify */
   U8                      bNoErabsToRel;        /* Number of E-RABs To Be Released */
   U8                      bIsUeAmbrPres;         /* Represents if UE AMBR value are valid or not.
                                                    If FALSE,  values should not be accessed */
} CM_PACK_STRUCT RmuErabConfigIe;

/**
 * @brief  Structure to hold the Release bearer information.
 * 
 * @details
 * - stErabRelLst : List of pre-empted bearers information.
 * - bNoErabsToRel : Number of berarers triggered for release. 
 */
typedef struct rmuErabRelLst
{
   RmuErabRelIe            stErabRelLst[RMU_MAX_NUM_ERABS]; 
   U8                      bNoErabsToRel;   
} CM_PACK_STRUCT RmuErabRelLst;
typedef enum rmuPcqiFormatInd
{
   RMU_PCQI_FMT_WIDEBAND,
   RMU_PCQI_FMT_SUBBAND
} RmuPcqiFormatInd;

typedef enum rmuPucchReportMode
{
   RMU_CQI_MODE10,
   RMU_CQI_MODE11,
   RMU_CQI_MODE20,
   RMU_CQI_MODE21
} RmuPucchReportMode;

typedef enum rmuPuschReportMode
{
   RMU_APRD_CQI_MODE12,
   RMU_APRD_CQI_MODE20,
   RMU_APRD_CQI_MODE22,
   RMU_APRD_CQI_MODE30,
   RMU_APRD_CQI_MODE31
} RmuPuschReportMode;

typedef struct rmuRiConfigIndex
{
   Bool         bPres;
   U16          usRiConfigIndex;       /* RI config Index */
}CM_PACK_STRUCT RmuRiConfigIndex;   

typedef enum rmuSubbandCqiPeriodicityFactor
{
	RMU_PERIODICITY_FACTOR_N2,
	RMU_PERIODICITY_FACTOR_N4
}RmuSubbandCqiPeriodicityFactor;

typedef struct rmuPCqiReportCfg
{
   U8                          type;                  /* Setup or Release, 1 or 0 */
   RmuPcqiFormatInd            enCqiFormatInd;        /* CQI format Indicator Value */
   RmuPucchReportMode          enPucchReportMode;     /* Crnti value     */   
   U16                         usCqiResourceIndex;    /* Cell Identifier */
   U16                         usCqiConfigIndex;      /* CQI config Index Value */

   RmuRiConfigIndex            riConfigIndex;         /*!< ri-ConfigIndex    (0..1023)  */
   U8                          bFactorK;              /* Value of Factor "K" configured,
                                                         for reporting the number of sub bands
                                                         per Bandwidth part */
	RmuSubbandCqiPeriodicityFactor sBCqiPeriodicityFactor;                                                         
   U8                          bSimulAckNackCqi;      /* Indicates whether HARQ Indication
                                                         (ACK/ NACK for DL Data) can be transmitted */
   U16                         srCfgIdx;              /* syed : Ideally shoould come from RRM */
} CM_PACK_STRUCT RmuPCqiReportCfg;

typedef struct rmuApCqiReportCfg
{
   Bool                        enbld; /* TRUE: If aperiodic CQI reporting is enabled */
   RmuPuschReportMode          enPuschReportMode; /* Aperiodic Reporting Mode */   
} CM_PACK_STRUCT RmuApCqiReportCfg;

typedef struct rmuUeCqiReportCfg
{
   RmuPCqiReportCfg           stPrdCqiRepCfg;
   RmuApCqiReportCfg          stAPrdCqiRepCfg;
} CM_PACK_STRUCT RmuUeCqiReportCfg;

typedef struct rmuUeSrCfg
{
   U16                        usSrIdx;
   U16                        usSrResIdx;
   CmRrmDsrTransMax           enDsrTransMax;
} CM_PACK_STRUCT RmuUeSrCfg;

typedef enum
{
   RMU_TXN_MODE1,
   RMU_TXN_MODE2,
   RMU_TXN_MODE3,
   RMU_TXN_MODE4,
   RMU_TXN_MODE5,
   RMU_TXN_MODE6,
   RMU_TXN_MODE7
} RmuTxnMode;

typedef struct rmuAntInfo
{
   RmuTxnMode         eTxnMode;        /*Enum*/
   U16                stcodebookSubset; /*union*/
   U8                 ueTxnAntSel;  /*TOKEN TO-DO*/  
} CM_PACK_STRUCT RmuAntInfo;

#ifdef LTE_ADV
typedef struct rmuUePucchCfg
{
   U8  sCellAckN1ResTb1Count;
   U8  sCellAckN1ResTb2Count;
   U16 sCellAckN1ResTb1[RM_RCM_MAX_SCELL_ACK_N1_PUCCH];
   U16 sCellAckN1ResTb2[RM_RCM_MAX_SCELL_ACK_N1_PUCCH];
} CM_PACK_STRUCT RmuUePucchCfg;
#endif
typedef struct rmuUeDedPhyCfg
{
   U8                        bPhyCfgDedResBitMap;
   RmuUeCqiReportCfg         stCqiRepCfg;
   RmuAntInfo                stAntInfo;
	RmuUeSrCfg                stSrCfg;
#ifdef LTE_ADV
   /* Sprint3: Add support for F1b */
  /* Add PUCCH Ded Cfg */
   RmuUePucchCfg             pucchCfgDed;
#endif
} CM_PACK_STRUCT RmuUeDedPhyCfg;


typedef struct rmuUeMacMainCfg
{
   U8                         bMacMainCfgBitMap;
   CmRrmDrxCfg                stRmDrxCfg; 
} CM_PACK_STRUCT RmuUeMacMainCfg;

/* SPS changes starts */
typedef struct rmuSpsP0Persistent
{
      S8	 	sP0NominalPUSCHPersistent;
      S8		sP0UEPuschPersistent;
} RmuSpsP0Persistent;

typedef enum
{
   RMU_SPS_E2,
   RMU_SPS_E3,
   RMU_SPS_E4,
   RMU_SPS_E8 
} RmuSpsImplctRelAftr;

typedef enum
{
   RMU_SPS_UL_INTERVAL_E10,
   RMU_SPS_UL_INTERVAL_E20,
   RMU_SPS_UL_INTERVAL_E32,
   RMU_SPS_UL_INTERVAL_E40,
   RMU_SPS_UL_INTERVAL_E64,
   RMU_SPS_UL_INTERVAL_E80,
   RMU_SPS_UL_INTERVAL_E128,
   RMU_SPS_UL_INTERVAL_E160,
   RMU_SPS_UL_INTERVAL_E320,
   RMU_SPS_UL_INTERVAL_E640,
   RMU_SPS_UL_INTERVAL_SPARE6,
   RMU_SPS_UL_INTERVAL_SPARE5,
   RMU_SPS_UL_INTERVAL_SPARE4,
   RMU_SPS_UL_INTERVAL_SPARE3,
   RMU_SPS_UL_INTERVAL_SPARE2,
   RMU_SPS_UL_INTERVAL_SPARE1
}RmuSpsIntervalUl;

typedef enum
{
   RMU_SPS_DL_INTERVAL_E10,
   RMU_SPS_DL_INTERVAL_E20,
   RMU_SPS_DL_INTERVAL_E32,
   RMU_SPS_DL_INTERVAL_E40,
   RMU_SPS_DL_INTERVAL_E64,
   RMU_SPS_DL_INTERVAL_E80,
   RMU_SPS_DL_INTERVAL_E128,
   RMU_SPS_DL_INTERVAL_E160,
   RMU_SPS_DL_INTERVAL_E320,
   RMU_SPS_DL_INTERVAL_E640,
   RMU_SPS_DL_INTERVAL_SPARE6,
   RMU_SPS_DL_INTERVAL_SPARE5,
   RMU_SPS_DL_INTERVAL_SPARE4,
   RMU_SPS_DL_INTERVAL_SPARE3,
   RMU_SPS_DL_INTERVAL_SPARE2,
   RMU_SPS_DL_INTERVAL_SPARE1
}RmuSpsIntervalDl;

typedef struct rmuSpsConfigUl
{
    Bool 		            bIsSpsEnabled;
    RmuSpsIntervalUl        eSpsIntervalUl;
    RmuSpsImplctRelAftr     eImplctRelAftr;
    Bool                    bTwoIntervalCfg; /* For TDD */
    Bool                    bP0PersistentPres;
    RmuSpsP0Persistent      stP0Persistent;
} CM_PACK_STRUCT RmuSpsConfigUl;

typedef struct rmuSpsConfigDl
{
    Bool 		             bIsSpsEnabled;
    RmuSpsIntervalDl         eSpsIntervalDl;
    U16                      usExplctRelAftr;
    U8		                 usNumOfConfSpsProc;
    U8		                 usNumN1Pucch;
    U16                      usN1Pucch[RM_RCM_SPS_MAX_N1_PUCCH];
} CM_PACK_STRUCT RmuSpsConfigDl;

typedef struct rmuUeSpsCfg
{
    RmuSpsConfigDl    stSpsConfigDl;
    RmuSpsConfigUl    stSpsConfigUl;
} CM_PACK_STRUCT RmuUeSpsCfg;
/* SPS changes ends */

typedef struct rmuUeRadioResCfg
{
   U8                         bRadioResDedBitMap;
   RmuUeDedPhyCfg             stPhyCfgDed;
   RmuUeMacMainCfg            stMacMainCfg;
   /* SPS changes starts */
   RmuUeSpsCfg                stSpsCfg;
   /* SPS changes ends */
} CM_PACK_STRUCT RmuUeRadioResCfg;

typedef struct rmuUeAdmitRsp
{
   RmuStatusInfo          stStatusInfo;
   RmuUeRadioResCfg       stUeRadioResCfg;
   U32                    uiTransId;      /* Transaction ID   */
   U16                    usCrnti;        /* UE Crnti value     */   
   U8                     bCellId;        /* Cell Identifier */
   U8                     bWaitTime;      /* In case of Status is FAILURE, The Wait time
                                                  should include in RRC Connection Reject message */
} CM_PACK_STRUCT RmuUeAdmitRsp;



typedef enum rmuScellAction
{
   RMU_SCELL_ADD,
   RMU_SCELL_MOD_COMMON,
   RMU_SCELL_MOD_DEDICATED,
   RMU_SCELL_RELEASE
} RmuScellAction;

typedef struct rmuSCellInfo
{

   RmuScellAction      action;
   CmLteCellId         sCellId;        /*!< Secondary Cell ID */
   U8                  sCellIdx;       /*!< Index of this Sec Cell configured at
                                         UE*/
}RmuSCellInfo;
typedef struct rmuUeScellInfoReq
{
   U32                    uiTransId;      /*!<  Transaction ID   */
   U8                     pCellId;        /*!<  Cell Identifier */
   U8                     numOfScell;     /*!<  numOfSCells */
   RmuSCellInfo           sCellIInfo[RMU_MAX_SCELL_PER_UE];  /*!<  sCell Index */
} CM_PACK_STRUCT RmuUeScellInfoReq;

typedef struct rmuUeSCellDedInfo
{
   RmuStatusInfo          stStatusInfo;
   U8                     sCellIdx;
   RmuUeCqiReportCfg      stCqiRepCfg;
}CM_PACK_STRUCT RmuUeSCellDedInfo;

typedef struct rmuUeSCellInfoRsp
{
   U8                     numSCells;     /*!<  numOfSCells */
   RmuUeSCellDedInfo      sCellDedInfo[RMU_MAX_SCELL_PER_UE];  /*!<  sCell Dedicated Info */
} CM_PACK_STRUCT RmuUeSCellInfoRsp;

typedef struct rmuEutraCapInfo 
{
   U32                       uiFeatureGrpIndicator;   /* Bit Map Indicating the support of
                                                       different features supported in UE */
   U32                       uiUeCategory;            /* UE category */
   /* SPS changes starts */
   RmuAccessStratumRls       uiUeAccessStratumRls;   /* UE Access Stratus Release */
   /* SPS changes ends */
} CM_PACK_STRUCT RmuEutraCapInfo;

typedef struct rmuUeCapInfoIe 
{
   RmuEutraCapInfo stEutraCapInfo;           /* EUTRA capability info */
} CM_PACK_STRUCT RmuUeCapInfoIe;

typedef struct rmuUeHoReq
{
   RmuErabConfigIe            stErabConfInfo;   
   RmuUeCapInfoIe             stUeCapInfo;   
   RmuUeRadioResCfg           stUeRadioResCfg;
   RmuHandOverType            enHoType;           /* HO Type value */
   RmuS1apCause               enHoS1apCause;      /* S1 AP cause */
   U32                        uiTransId;          /* Transaction ID */
   U16                        usCrnti;            /* Crnti value     */   
   U8                         bCellId;            /* Cell Identifier */
   Bool                       isEmrgncyBrersPsnt; /*!< determined by ARP */
   U8                         isMember;           /*!< CSG membership */
} CM_PACK_STRUCT RmuUeHoReq;

/******* RM_WR_UE_HO_RESP(RRM->FSM) *********/
typedef struct rmuErabAdmitted
{
   U8                          bErabId;        /* ERAB Identifier */
   /* SPS changes starts */
   Bool                        bIsDlSpsEnabled;
   Bool                        bIsUlSpsEnabled;
   /* SPS changes ends */
} CM_PACK_STRUCT RmuErabAdmitted;

typedef struct rmuErabRejected
{
   RmuS1apCause                enCause;        /* Cause Value     */
   U8                          bErabId;        /* ERAB Identifier */
} CM_PACK_STRUCT RmuErabRejected;

typedef struct rmuUeHoRsp
{
   RmuErabAdmitted             stErabAdmitLst[RMU_MAX_NUM_ERABS];
   RmuErabRejected             stErabRejectLst[RMU_MAX_NUM_ERABS];
   RmuUeRadioResCfg            stUeRadioResCfg;
   RmuStatusInfo               stStatusInfo;           /* Response is failure or success */
   U32                         uiTransId;          /* Transaction ID   */
   U16                         usCrnti;             /* Crnti value      */   
   U8                          bCellId;            /* Cell Identifier  */
   U8                          bNoErabsAdmitted;    /* Number of ERABs that are admitted at RRM */
   U8                          bNoErabsRejected;     /* Number of ERABs that are Rejected at RRM */
   Bool                        isGBRBearerExists;
} CM_PACK_STRUCT RmuUeHoRsp;

/******* WR_RM_UE_REL_REQ (FSM->RRM) *********/
typedef struct rmuUeRelReq 
{
   U32                        uiTransId;          /* Transaction ID   */
   U16                        usCrnti;            /* Crnti value      */   
   U8                         bCellId;            /* Cell Identifier  */
} CM_PACK_STRUCT RmuUeRelReq;

/******* RM_WR_UE_REL_RESP(RRM->FSM) *********/
typedef struct rmuUeRelRsp
{
   RmuStatusInfo               stStatusInfo;
   U32                         uiTransId;       /* Transaction ID   */
   U16                         usCrnti;         /* Crnti value     */   
   U8                          bCellId;         /* Cell Identifier */
} CM_PACK_STRUCT RmuUeRelRsp;

/******* RM_WR_UE_REL_IND (RRM->FSM) *********/
typedef struct rmuUeRelInd
{
   RmuRrcCause                 enRelCause;    /* Cause Value */
   U16                         usCrnti;       /* Crnti value     */   
   U8                          bCellId;      /* Cell Identifier */
} CM_PACK_STRUCT RmuUeRelInd;

/******* RM_WR_UE_ERAB_REL_IND (RRM->FSM) *********/
/**
 * @brief  Structure to hold the Release beareris Indication information.
 *         which triggers from RRM to FSM.
 * 
 * @details
 * - stErabRelInfo : Pre-empted ERABs information.
 * - usCrnti : CRNTI of the UE. 
 * -bCellId  : cell Identity for which this UE is belongs.
 */
typedef struct rmuUeERabRelInd
{
   RmuErabRelLst           stErabRelInfo;
   U16                     usCrnti; 
   U8                      bCellId; 
} CM_PACK_STRUCT RmuUeERabRelInd;
/******* WR_RM_UE_RECONFIG_REQ (FSM->RRM) *********/

typedef struct rmuUeRecfgReq 
{
   RmuErabConfigIe            stErabConfInfo;
   RmuUeCapInfoIe             stUeCapInfo;
   RmuUeScellInfoReq          stSCellInfoReq;
   U32                        uiTransId;         /* Transaction ID   */
   U16                        usCrnti;           /* Crnti value      */   
   U16                        usUeNewCrnti;      /* New Crnti value  */   
   U8                         bCellId;           /* Cell Identifier  */
   U8                         bRecfgBitMap;      /* Indicates the reconfig info
                                                    included in this structure */
   U8                         isMember;          /* Indicates if UE is a 
                                                    member */
#ifdef LTE_ADV
   Bool                       bIsUeCaCap;        /* Indicates the CA capability of
                                                    Ue*/
#endif
} CM_PACK_STRUCT RmuUeRecfgReq;

/*RRM_SP3*/
typedef struct rmuUeInactInd
{
   CmLteRnti   uiCrnti;    /*!< UE Crnti*/
   CmLteCellId uiCellId;   /*!< Cell Identity*/
   U8          uiInactEvt; /*!< Inactivity event*/
}CM_PACK_STRUCT RmuUeInactInd;
/******* RM_WR_UE_RECONFIG_RESP (RRM->FSM) *********/

typedef struct rmuUeRecfgRsp
{
   RmuErabAdmitted            stErabAcceptLst[RMU_MAX_NUM_ERABS];
   RmuErabRejected            stErabRejectLst[RMU_MAX_NUM_ERABS];
   RmuUeRadioResCfg           stUeRadioResCfg;
   RmuUeSCellInfoRsp          stUeSCellResCfg;
   RmuStatusInfo              stStatusInfo;
   U32                        uiTransId;            /* Transaction ID  */
   U16                        usCrnti;              /* Crnti value     */   
   U8                         bCellId;              /* Cell Identifier */
   U8                         bRecfgBitMap;         /* Indicates the reconfig info
                                                       included in this structure */
   U8                         bNoErabsAccepted;     /* Number of ERABs that are admitted at RRM */
   U8                         bNoErabsRejected;     /* Number of ERABs that are Rejected at RRM */
   Bool                       isGBRBearerExists;
} CM_PACK_STRUCT RmuUeRecfgRsp;

typedef RmuUeRecfgRsp RmuUeRecfgInd;

/* SPS changes starts */
typedef struct rmuUeSpsDisInd
{
   U8    cellId;
   U16   usCrnti;
} CM_PACK_STRUCT RmuUeSpsDisInd;   
/* SPS changes ends */

typedef union 
{
	RmuUeAdmitReq	  stRmuUeAdmitReq;
	RmuUeAdmitRsp 	  stRmuUeAdmitRsp;
	RmuUeRecfgReq 	  stRmuUeRecfgReq;
	RmuUeRecfgRsp 	  stRmuUeRecfgRsp;
	RmuUeRelReq	     stRmuUeRelReq;
	RmuUeRelRsp	     stRmuUeRelRsp;	
	RmuUeHoReq       stRmuUeHoReq;
	RmuUeHoRsp	     stRmuUeHoRsp;
	RmuCellRecfgInd  stRmuCellRecfgInd;
	RmuFsmStatusInd  stRmuFsmStatusInd;
	RmuUeRelInd	     stRmuUeRelInd;
   RmuUeERabRelInd  stRmuUeERabRelInd; /*!< ERAB Release indication(RRM_>FSM) */
   RmuMmeOvldStartInd stRmuOverLoadStartInd;
   RmuMmeOvldStopInd  stRmuOverLoadStopInd;	
   /* SPS changes starts */
   RmuUeSpsDisInd     stRmuSpsDisInd;
   /* SPS changes ends */
   /*RRM_SP3*/
   RmuUeInactInd   stRmuUeInactInd; /*!< UE inactivity indication (FSM->RRM) */
   RmuUeRecfgInd     stRmuUeReCfgInd;
} CM_PACK_STRUCT RmuCommonMsg;

/*** Function pointers for Loosely and tightly coupled primitives ***/

typedef S16 (*RmuFsmStatusIndFPtr)  ARGS((
        Pst *pst,
        SuId suId,
        RmuFsmStatusInd  *statusInd
        ));

typedef S16 (*RmuMmeOvldStartIndFPtr)   ARGS((
        Pst *pst, 
        SuId suId, 
        RmuMmeOvldStartInd *startInfo
        ));

typedef S16 (*RmuMmeOvldStopIndFPtr)   ARGS((
        Pst *pst, 
        SuId suId, 
        RmuMmeOvldStopInd *stopInfo
        ));
typedef S16 (*RmuUeAdmitReqFPtr)   ARGS((
        Pst *pst, 
        SuId suId, 
        RmuUeAdmitReq *admitInfo
        ));
typedef S16 (*RmuUeHoReqFPtr)    ARGS((
        Pst *pst, 
        SuId suId, 
        RmuUeHoReq *hoInfo
        ));
typedef S16 (*RmuUeRelReqFPtr)   ARGS((
        Pst *pst, 
        SuId suId, 
        RmuUeRelReq *relInfo
        ));
typedef S16 (*RmuUeRecfgReqFPtr)   ARGS((
        Pst *pst, 
        SuId suId, 
        RmuUeRecfgReq *reconfiginfo
        ));
/*RRM_SP3*/
typedef S16 (*RmuUeInactIndFPtr) ARGS((
        Pst *pst,
        SuId suId,
        RmuUeInactInd   *rrmUeInactInd
        ));
/* SPS changes starts */
typedef S16 (*RmuUeSpsDisIndFPtr)   ARGS((
        Pst *pst, 
        SuId suId, 
        RmuUeSpsDisInd *ueSpsDisInd
        ));
/* SPS changes ends */

typedef S16 (*RmuBndReqFPtr) ARGS((
        Pst *pst, 
        SuId suId,  
        SpId spId 
        ));

typedef S16 (*RmuCellRecfgIndFPtr) ARGS((
        Pst *pst, 
        SuId suId, 
        RmuCellRecfgInd *cellRecfgInfo
        ));

typedef S16 (*RmuUeRecfgIndFPtr) ARGS((
        Pst *pst, 
        SuId suId, 
        RmuUeRecfgInd *ueRecfgInfo
        ));
typedef S16 (*RmuUeAdmitRspFPtr) ARGS((
        Pst *pst, 
        SuId suId, 
        RmuUeAdmitRsp *admitRspinfo
        ));
typedef S16 (*RmuUeHoRspFPtr) ARGS((
        Pst *pst, 
        SuId suId, 
        RmuUeHoRsp *hoRspinfo
        ));
typedef S16 (*RmuUeRelRspFPtr) ARGS((
        Pst *pst, 
        SuId suId, 
        RmuUeRelRsp *relrspinfo
        ));
typedef S16 (*RmuUeRelIndFPtr) ARGS((
        Pst *pst, 
        SuId suId, 
        RmuUeRelInd *relIndinfo
        ));

/*!< UE ERAB release Indication API from RRM to FSM */
typedef S16 (*RmuUeERabRelIndFPtr) ARGS((
        Pst *pst, 
        SuId suId, 
        RmuUeERabRelInd *relIndinfo
        ));
typedef S16 (*RmuUeRecfgRspFPtr) ARGS((
        Pst *pst, 
        SuId suId,  
        RmuUeRecfgRsp *recfgRspinfo
        ));
typedef S16 (*RmuBndCfmFPtr) ARGS((
        Pst *pst, 
        SuId suId,  
        U8   status
        ));

/******* PACKED LOOSELY COUPLED (FSM->RRM) *********/
EXTERN S16 cmPkRmuFsmStatusInd ARGS((Pst *pst, SuId suId, RmuFsmStatusInd *statusInd));
EXTERN S16 cmPkRmuMmeOverloadStartInd ARGS((Pst *pst, SuId suId, RmuMmeOvldStartInd *startInfo));
EXTERN S16 cmPkRmuMmeOverloadStopInd ARGS((Pst *pst, SuId suId, RmuMmeOvldStopInd *stopinfo));
EXTERN S16 cmPkRmuUeAdmitReq ARGS((Pst *pst, SuId suId, RmuUeAdmitReq *admitinfo));
EXTERN S16 cmPkRmuUeHoReq ARGS((Pst *pst, SuId suId, RmuUeHoReq *hoinfo));
EXTERN S16 cmPkRmuUeRelReq ARGS((Pst *pst, SuId suId, RmuUeRelReq *relinfo));
EXTERN S16 cmPkRmuUeRecfgReq ARGS((Pst *pst, SuId suId, RmuUeRecfgReq *reconfiginfo));
/* SPS changes starts */
EXTERN S16 cmPkRmuUeSpsDisInd ARGS((Pst *pst, SuId suId, RmuUeSpsDisInd *ueSpsDisInd));
/* SPS changes ends */

/*RRM_SP3*/
EXTERN S16 cmPkRmuUeInactInd ARGS((Pst *pst, SuId suId, RmuUeInactInd
                                   *rrmUeInactInd));

EXTERN S16 cmPkRmuBndReq ARGS((Pst *pst, SuId suId, SpId spId));

EXTERN S16 cmUnpkRmuCellRecfgInd ARGS((RmuCellRecfgIndFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkRmuUeRecfgInd ARGS((RmuUeRecfgIndFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkRmuUeAdmitRsp ARGS((RmuUeAdmitRspFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkRmuUeHoRsp ARGS((RmuUeHoRspFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkRmuUeRelRsp ARGS((RmuUeRelRspFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkRmuUeRelInd ARGS((RmuUeRelIndFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkRmuUeERabRelInd ARGS((RmuUeERabRelIndFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkRmuUeRecfgRsp ARGS((RmuUeRecfgRspFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkRmuBndCfm ARGS((RmuBndCfmFPtr func, Pst* pst, Buffer* mBuf));

#ifdef RMU_LWLC
EXTERN S16 cmPkLwLcRmuFsmStatusInd ARGS((Pst *pst, SuId suId, RmuFsmStatusInd *statusInd));
EXTERN S16 cmPkLwLcRmuMmeOverloadStartInd ARGS((Pst *pst, SuId suId, RmuMmeOvldStartInd *startInfo));
EXTERN S16 cmPkLwLcRmuMmeOverloadStopInd ARGS((Pst *pst, SuId suId, RmuMmeOvldStopInd *stopinfo));
EXTERN S16 cmPkLwLcRmuUeAdmitReq ARGS((Pst *pst, SuId suId, RmuUeAdmitReq *admitinfo));
EXTERN S16 cmPkLwLcRmuUeHoReq ARGS((Pst *pst, SuId suId, RmuUeHoReq *hoinfo));
EXTERN S16 cmPkLwLcRmuUeRelReq ARGS((Pst *pst, SuId suId, RmuUeRelReq *relinfo));
EXTERN S16 cmPkLwLcRmuUeRecfgReq ARGS((Pst *pst, SuId suId, RmuUeRecfgReq *reconfiginfo));
/* SPS changes starts */
EXTERN S16 cmPkLwLcRmuUeSpsDisInd ARGS((Pst *pst, SuId suId, RmuUeSpsDisInd *ueSpsDisInd));
/* SPS changes ends */

/*RRM_SP3*/
EXTERN S16 cmPkLwLcRmuUeInactInd ARGS((Pst *pst, SuId suId, RmuUeInactInd
                                       *rrmUeInactInd));

EXTERN S16 cmPkLwLcRmuBndReq ARGS((Pst *pst, SuId suId, SpId spId));

EXTERN S16 cmUnpkLwLcRmuCellReCfgInd ARGS((RmuCellRecfgIndFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkLwLcRmuUeReCfgInd ARGS((RmuUeRecfgIndFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkLwLcRmuUeAdmitRsp ARGS((RmuUeAdmitRspFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkLwLcRmuUeHoRsp ARGS((RmuUeHoRspFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkLwLcRmuUeRelRsp ARGS((RmuUeRelRspFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkLwLcRmuUeRelInd ARGS((RmuUeRelIndFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkLwLcRmuUeERabRelInd ARGS((RmuUeERabRelIndFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkLwLcRmuUeRecfgRsp ARGS((RmuUeRecfgRspFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkLwLcRmuBndCfm ARGS((RmuBndCfmFPtr func, Pst* pst, Buffer* mBuf));

EXTERN S16 cmPkLwLcRmuUeAdmitRsp ARGS((Pst *pst, SuId suId, RmuUeAdmitRsp *admitRspInfo));
EXTERN S16 cmPkLwLcRmuUeHoRsp ARGS((Pst *pst, SuId suId, RmuUeHoRsp *hoRspInfo));
EXTERN S16 cmPkLwLcRmuUeRelRsp ARGS((Pst *pst, SuId suId, RmuUeRelRsp *ueRelRspInfo));
EXTERN S16 cmPkLwLcRmuUeRelInd ARGS((Pst *pst, SuId suId, RmuUeRelInd *ueRelIndInfo));
EXTERN S16 cmPkLwLcRmuUeERabRelInd ARGS((Pst *pst, SuId suId, RmuUeERabRelInd *rabRelIndInfo));
EXTERN S16 cmPkLwLcRmuUeRecfgRsp ARGS((Pst *pst, SuId suId, RmuUeRecfgRsp *ueRecfgRspInfo));
EXTERN S16 cmPkLwLcRmuCellRecfgInd ARGS((Pst *pst, SuId suId, RmuCellRecfgInd *cellRecfgInd));
EXTERN S16 cmPkLwLcRmuUeRecfgInd ARGS((Pst *pst, SuId suId, RmuUeRecfgInd *ueRecfgInd));
EXTERN S16 cmPkLwLcRmuBndCfm ARGS((Pst *pst, SuId suId, U8 status));

EXTERN S16 cmUnpkLwLcRmuBndReq ARGS((RmuBndReqFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkLwLcRmuUeAdmitReq ARGS((RmuUeAdmitReqFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkLwLcRmuUeHoReq ARGS((RmuUeHoReqFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkLwLcRmuUeRelReq ARGS((RmuUeRelReqFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkLwLcRmuUeRelReq ARGS((RmuUeRelReqFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkLwLcRmuUeRecfgReq ARGS((RmuUeRecfgReqFPtr func, Pst* pst, Buffer* mBuf));
/* SPS changes starts */
EXTERN S16 cmUnpkLwLcRmuUeSpsDisInd ARGS((RmuUeSpsDisIndFPtr func, Pst* pst, Buffer* mBuf));
/* SPS changes ends */
/*RRM_SP3*/
EXTERN S16 cmUnpkLwLcRmuUeInactInd ARGS((RmuUeInactIndFPtr func,Pst* pst,Buffer* mBuf)); 
EXTERN S16 cmUnpkLwLcRmuMmeOvldStartInd ARGS((RmuMmeOvldStartIndFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkLwLcRmuMmeOvldStopInd ARGS((RmuMmeOvldStopIndFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkLwLcRmuFsmStatusInd ARGS((RmuFsmStatusIndFPtr func, Pst* pst, Buffer* mBuf));
#endif

#ifdef RMU_LC
EXTERN S16 cmPkRmuUeAdmitRsp ARGS((Pst *pst, SuId suId, RmuUeAdmitRsp *admitRspInfo));
EXTERN S16 cmPkRmuUeHoRsp ARGS((Pst *pst, SuId suId, RmuUeHoRsp *hoRspInfo));
EXTERN S16 cmPkRmuUeRelRsp ARGS((Pst *pst, SuId suId, RmuUeRelRsp *ueRelRspInfo));
EXTERN S16 cmPkRmuUeRelInd ARGS((Pst *pst, SuId suId, RmuUeRelInd *ueRelIndInfo));
EXTERN S16 cmPkRmuUeERabRelInd ARGS((Pst *pst, SuId suId, RmuUeERabRelInd *rabRelIndInfo));
EXTERN S16 cmPkRmuUeRecfgRsp ARGS((Pst *pst, SuId suId, RmuUeRecfgRsp *ueRecfgRspInfo));
EXTERN S16 cmPkRmuCellRecfgInd ARGS((Pst *pst, SuId suId, RmuCellRecfgInd *cellRecfgInd));
EXTERN S16 cmPkRmuUeRecfgInd ARGS((Pst *pst, SuId suId, RmuUeRecfgInd *ueRecfgInd));
EXTERN S16 cmPkRmuBndCfm ARGS((Pst *pst, SuId suId, U8 status));

EXTERN S16 cmUnpkRmuUeAdmitReq ARGS((RmuUeAdmitReqFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkRmuUeHoReq ARGS((RmuUeHoReqFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkRmuUeRelReq ARGS((RmuUeRelReqFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkRmuUeRelReq ARGS((RmuUeRelReqFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkRmuUeRecfgReq ARGS((RmuUeRecfgReqFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkRmuMmeOvldStartInd ARGS((RmuMmeOvldStartIndFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkRmuMmeOvldStopInd ARGS((RmuMmeOvldStopIndFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkRmuFsmStatusInd ARGS((RmuFsmStatusIndFPtr func, Pst* pst, Buffer* mBuf));



#endif

/******* UNPACKED LOOSELY COUPLED (FSM->RRM) *********/
#ifdef RMU_NPLC
EXTERN S16 cmNoPkRmuFsmStatusInd ARGS((Pst *pst, SuId suId, RmuFsmStatusInd *statusInd));
EXTERN S16 cmNoPkRmuMmeOverloadStartInd ARGS((Pst *pst, SuId suId, RmuMmeOvldStartInd *startInfo));
EXTERN S16 cmNoPkRmuMmeOverloadStopInd ARGS((Pst *pst, SuId suId, RmuMmeOvldStopInd *stopinfo));
EXTERN S16 cmNoPkRmuUeAdmitReq ARGS((Pst *pst, SuId suId, RmuUeAdmitReq *admitinfo));
EXTERN S16 cmNoPkRmuUeHoReq ARGS((Pst *pst, SuId suId, RmuUeHoReq *hoinfo));
EXTERN S16 cmNoPkRmuUeRelReq ARGS((Pst *pst, SuId suId, RmuUeRelReq *relinfo));
EXTERN S16 cmNoPkRmuUeRecfgReq ARGS((Pst *pst, SuId suId, RmuUeRecfgReq *reconfiginfo));
/* SPS changes starts */
EXTERN S16 cmNoPkRmuUeSpsDisInd ARGS((Pst *pst, SuId suId, RmuUeSpsDisInd *ueSpsDisInd));
/* SPS changes ends */

/*RRM_SP3*/
EXTERN S16 cmNoPkRmuUeInactInd ARGS((Pst *pst, SuId suId, RmuUeInactInd
                                     *rrmUeInactInd));

EXTERN S16 cmNoPkRmuBndReq ARGS((Pst *pst, SuId suId, SpId spId));

EXTERN S16 cmUnpkNoPkRmuCellRecfgInd ARGS((RmuCellRecfgIndFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkNoPkRmuUeRecfgInd ARGS((RmuUeRecfgIndFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkNoPkRmuUeAdmitRsp ARGS((RmuUeAdmitRspFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkNoPkRmuUeHoRsp ARGS((RmuUeHoRspFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkNoPkRmuUeRelRsp ARGS((RmuUeRelRspFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkNoPkRmuUeRelInd ARGS((RmuUeRelIndFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkNoPkRmuUeERabRelInd ARGS((RmuUeERabRelIndFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkNoPkRmuUeRecfgRsp ARGS((RmuUeRecfgRspFPtr func, Pst* pst, Buffer* mBuf));
EXTERN S16 cmUnpkNoPkRmuBndCfm ARGS((RmuBndCfmFPtr func, Pst* pst, Buffer* mBuf));
#endif /*RMU_NPLC*/

EXTERN S16 WrLiRmuFsmStatusInd ARGS((Pst *pst, SuId suId, RmuFsmStatusInd *statusInd));
EXTERN S16 WrLiRmuMmeOverloadStartInd ARGS((Pst *pst, SuId suId, RmuMmeOvldStartInd *startInfo));
EXTERN S16 WrLiRmuMmeOverloadStopInd ARGS((Pst *pst, SuId suId, RmuMmeOvldStopInd *stopinfo));
EXTERN S16 WrLiRmuUeAdmitReq ARGS((Pst *pst, SuId suId, RmuUeAdmitReq *admitinfo));
EXTERN S16 WrLiRmuUeHoReq ARGS((Pst *pst, SuId suId, RmuUeHoReq *hoinfo));
EXTERN S16 WrLiRmuUeRelReq ARGS((Pst *pst, SuId suId, RmuUeRelReq *relinfo));
EXTERN S16 WrLiRmuUeRecfgReq ARGS((Pst *pst, SuId suId, RmuUeRecfgReq *reconfiginfo));
/* SPS changes starts */
EXTERN S16 WrLiRmuUeSpsDisInd ARGS((Pst *pst, SuId suId, RmuUeSpsDisInd *ueSpsDisInd));
/* SPS changes ends */
/*RRM_SP3*/
EXTERN S16 WrLiRmuUeInactInd ARGS((Pst *pst, SuId suId,RmuUeInactInd *rrmUeInactInd)); 

EXTERN S16 WrLiRmuBndReq ARGS((Pst *pst, SuId suId, SpId spId));

EXTERN S16 WrLiRmuCellRecfgInd ARGS((Pst *pst, SuId suId, RmuCellRecfgInd *cellRecfgInfo));
EXTERN S16 WrLiRmuUeRecfgInd ARGS((Pst *pst, SuId suId, RmuUeRecfgInd *ueRecfgInfo));
EXTERN S16 WrLiRmuUeAdmitRsp ARGS((Pst *pst, SuId suId, RmuUeAdmitRsp *admitRspinfo));
EXTERN S16 WrLiRmuUeHoRsp ARGS((Pst *pst, SuId suId, RmuUeHoRsp *hoRspinfo));
EXTERN S16 WrLiRmuUeRelRsp ARGS((Pst *pst, SuId suId, RmuUeRelRsp *relrspinfo));
EXTERN S16 WrLiRmuUeRelInd ARGS((Pst *pst, SuId suId, RmuUeRelInd *relIndinfo));
EXTERN S16 WrLiRmuUeERabRelInd ARGS((Pst *pst, SuId suId, RmuUeERabRelInd *relIndinfo));
EXTERN S16 WrLiRmuUeRecfgRsp ARGS((Pst *pst, SuId suId, RmuUeRecfgRsp *recfgRspinfo));
EXTERN S16 WrLiRmuBndCfm ARGS((Pst *pst, SuId suId, U8 status));

#ifdef RM_INTF
EXTERN S16 RmUiRmuBndReq ARGS((Pst *pst, SuId suId, SpId spId));
EXTERN S16 RmUiRmuFsmStatusInd ARGS((Pst *pst, SuId suId, RmuFsmStatusInd *statusInd));
EXTERN S16 RmUiRmuUeAdmitReq ARGS((Pst *pst, SuId suId, RmuUeAdmitReq *admitinfo));
EXTERN S16 RmUiRmuUeHoReq ARGS((Pst *pst, SuId suId, RmuUeHoReq *hoinfo));
EXTERN S16 RmUiRmuUeRelReq ARGS((Pst *pst, SuId suId, RmuUeRelReq *relinfo));
EXTERN S16 RmUiRmuUeRecfgReq ARGS((Pst *pst, SuId suId, RmuUeRecfgReq *reconfiginfo));
/* SPS changes starts */
EXTERN S16 RmUiRmuUeSpsDisInd ARGS((Pst *pst, SuId suId, RmuUeSpsDisInd *ueSpsDisInd));
/* SPS changes ends */
/*RRM_SP3*/
EXTERN S16 RmUiRmuUeInactInd ARGS((Pst *pst, SuId suId, RmuUeInactInd
                                   *rrmUeInactInd));

EXTERN S16 RmUiRmuMmeOvldStartInd ARGS((Pst *pst, SuId suId, RmuMmeOvldStartInd *startInfo));
EXTERN S16 RmUiRmuMmeOvldStopInd ARGS((Pst *pst, SuId suId,RmuMmeOvldStopInd *stopinfo));

EXTERN S16 RmUiRmuCellRecfgInd ARGS((Pst *pst, SuId suId, RmuCellRecfgInd *cellRecfgInfo));
EXTERN S16 RmUiRmuUeRecfgInd ARGS((Pst *pst, SuId suId, RmuUeRecfgInd *pstUeRecfgInd));
EXTERN S16 RmUiRmuUeAdmitRsp ARGS((Pst *pst, SuId suId, RmuUeAdmitRsp *admitRspinfo));
EXTERN S16 RmUiRmuUeHoRsp ARGS((Pst *pst, SuId suId, RmuUeHoRsp *hoRspinfo));
EXTERN S16 RmUiRmuUeRelRsp ARGS((Pst *pst, SuId suId, RmuUeRelRsp *relrspinfo));
EXTERN S16 RmUiRmuUeRelInd ARGS((Pst *pst, SuId suId, RmuUeRelInd *relIndinfo));
EXTERN S16 RmUiRmuUeERabRelInd ARGS((Pst *pst, SuId suId, RmuUeERabRelInd *relIndinfo));
EXTERN S16 RmUiRmuUeRecfgRsp ARGS((Pst *pst, SuId suId, RmuUeRecfgRsp *recfgRspinfo));
EXTERN S16 RmUiRmuBndCfm ARGS((Pst *pst, SuId suId, U8 status));
#endif

#ifdef RMU_ACC
EXTERN S16 DmUiRmuFsmStatusInd ARGS((Pst *pst, SuId suId, RmuFsmStatusInd *statusInd));
EXTERN S16 DmUiRmuMmeOverloadStartInd ARGS((Pst *pst, SuId suId, RmuMmeOvldStartInd *startInfo));
EXTERN S16 DmUiRmuMmeOverloadStopInd ARGS((Pst *pst, SuId suId, RmuMmeOvldStopInd *stopinfo));
EXTERN S16 DmUiRmuUeAdmitReq ARGS((Pst *pst, SuId suId, RmuUeAdmitReq *admitinfo));
EXTERN S16 DmUiRmuUeHoReq ARGS((Pst *pst, SuId suId, RmuUeHoReq *hoinfo));
EXTERN S16 DmUiRmuUeRelReq ARGS((Pst *pst, SuId suId, RmuUeRelReq *relinfo));
EXTERN S16 DmUiRmuUeRecfgReq ARGS((Pst *pst, SuId suId, RmuUeRecfgReq *reconfiginfo));
/* SPS changes starts */
EXTERN S16 DmUiRmuUeSpsDisInd ARGS((Pst *pst, SuId suId, RmuUeSpsDisInd *ueSpsDisInd));
/* SPS changes ends */
/*RRM_SP3*/
EXTERN S16 DmUiRmuUeInactInd ARGS((Pst *pst, SuId suId, RmuUeInactInd
                                   *rrmUeInactInd));

EXTERN S16 DmUiRmuBndReq ARGS((Pst *pst, SuId suId, SpId spId));
#endif

#if !(defined(RMU_LWLC)  && defined(RMU_LC)&& defined(RMU_TC)&& defined(RMU_NPLC))
#define PTRMUIRMU
#endif
#ifdef PTRMUIRMU
EXTERN S16 PtPkRmuUeAdmitRsp ARGS((Pst *pst, SuId suId, RmuUeAdmitRsp *admitRspInfo));
EXTERN S16 PtPkRmuUeHoRsp ARGS((Pst *pst, SuId suId, RmuUeHoRsp *hoRspInfo));
EXTERN S16 PtPkRmuUeRelRsp ARGS((Pst *pst, SuId suId, RmuUeRelRsp *ueRelRspInfo));
EXTERN S16 PtPkRmuUeRelInd ARGS((Pst *pst, SuId suId, RmuUeRelInd *ueRelIndInfo));
EXTERN S16 PtPkRmuUeERabRelInd ARGS((Pst *pst, SuId suId, RmuUeERabRelInd *rabRelIndInfo));
EXTERN S16 PtPkRmuUeRecfgRsp ARGS((Pst *pst, SuId suId, RmuUeRecfgRsp *ueRecfgRspInfo));
EXTERN S16 PtPkRmuCellRecfgInd ARGS((Pst *pst, SuId suId, RmuCellRecfgInd *cellRecfgInd));
EXTERN S16 PtPkRmuUeRecfgInd ARGS((Pst *pst, SuId suId, RmuUeRecfgInd *ueRecfgInd));
EXTERN S16 PtPkRmuBndCfm ARGS((Pst *pst, SuId suId, U8 status));
#endif

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* __RMUX__ */

/********************************************************************30**

         End of file:     rmu.x@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/T2K_MergeTemp_BR/1 - Mon Sep  2 16:44:23 2013

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
*********************************************************************91*/
