
/**********************************************************************
     Name:     LTE-MAC layer 
  
     Type:     C include file 
  
     Desc:     Defines required by the LTE MAC-RRM control (RGR) interface.

     File:     rgr.h 

     Sid:      rgr.h@@/main/9 - Wed Jul 27 13:44:32 2011

     Prg:      sdass

**********************************************************************/

#ifndef __RGR_H__
#define __RGR_H__
#include "nlu.h"
/** 
  @file rgr.h 
  @brief Macros for RGR interface.
  */
#define RGR_LTEU_MAX_EARFCN 10
#define RGR_MAX_SUBBANDS 110
#define RGR_MIN_CMN_LC_PER_CELL 4 /*!< BCCH-BCH, BCCH-DLSCH , PCCH,
                                       CCCH (bi-directional) */ 
#define RGR_MAX_CMN_LC_PER_CELL 6 /*!< BCCH-BCH, BCCH-DLSCH (can be 2), PCCH,
                           CCCH (can be 2 - UL and DL, if given differently) */ 
#define RGR_MAX_NUM_QCI 9         /*!< Maximum number of Supported QCIs */

/* LTE_ADV_FLAG_REMOVED_START */
#define RGR_ABS_PATTERN_LEN   40

#define RGR_MAX_NBR_ENB       2      /*Maximum there can be 2 neighbours who will have different Edge RB Range*/
/* LTE_ADV_FLAG_REMOVED_END */

/*rgr_h_001.main_8 ADD added changes for L2 Measurements*/
#ifdef LTE_L2_MEAS
#define RGR_MAX_LC_PER_LCG      10 /*!< Number of Logical Channels per LCG */
#endif /* LTE_L2_MEAS*/

/* Configuration/Reconfiguration MACROs*/
#define RGR_CONFIG   1      /*!< Macro for Configuration Request*/
#define RGR_RECONFIG 2      /*!< Macro for Reconfiguration Request*/
#define RGR_DELETE   3      /*!< Macro for Delete Request*/
#define RGR_RESET    4      /*!< Macro for Reset Request*/
#define RGR_SON_CFG   5      /*!< Macro for SON configuration Request*/
#ifdef LTE_ADV
#define RGR_SCELL_ACT 6      /*!< Macro for Activation of SCell */
#define RGR_SCELL_DEACT 7      /*!< Macro for De-activation of SCell */
#define RGR_SCELL_READY 8      /*!< Macro Indicating that SCELL is ready for activation */
#endif /* LTE_ADV */
/* Cell/UE specific MACROs*/
#define RGR_CELL_CFG  1     /*!< Macro for Cell Configuration Type */ 
#define RGR_UE_CFG    2     /*!< Macro for UE Configuration Type */ 
#define RGR_LCH_CFG   3     /*!< Macro for Logical Channel Configuration Type */ 
#define RGR_LCG_CFG   4     /*!< Macro for Logical Group Configuration Type */
#define RGR_SCELL_UE_CFG 5  /*!< MACRO for Scell release */
#define RGR_ENB_CFG   6     /*!< MACRO for ENB Scheduler Configuration Type */

/* Cell-wide reconfiguration MACROs */
#define RGR_CELL_DL_CMNRATE_RECFG (1<<0)  /*!< Macro for Downlink Common Coderate Reconfiguration */
#define RGR_CELL_CFI_RECFG        (1<<1)  /*!< Macro for CFI Reconfiguration */
#define RGR_CELL_TRGCQI_RECFG     (1<<2)  /*!< Macro for Target CFI Reconfiguration */
#define RGR_CELL_PUSCH_SB_RECFG   (1<<3)  /*!< Macro for PUSCH SB Reconfiguration */
#define RGR_CELL_UL_CMNRATE_RECFG (1<<4)  /*!< Macro for Uplink Common Coderate Reconfiguration */
#define RGR_CELL_DL_HARQ_RECFG    (1<<5)  /*!< Macro for Downlink HARQ Reconfiguration */
#define RGR_CELL_PUCCH_RECFG      (1<<6)  /*!< Macro for PUCCH Reconfiguration */
#define RGR_CELL_SRS_RECFG        (1<<7)  /*!< Macro for SRS Reconfiguration */
#define RGR_CELL_RACH_RECFG       (1<<8)  /*!< Macro for RACH Reconfiguration */
#define RGR_CELL_DLFS_RECFG       (1<<9)  /*!< Macro for DLFS Reconfiguration */
#define RGR_CELL_PWR_RECFG        (1<<10) /*!< Macro for Power Reconfiguration */
/* rgr_h_001.main_3:ADD-Added for SI Enhancement. */
/** @name RGR_SI_SCH */
/** @{ */
#ifdef RGR_SI_SCH
#define RGR_CELL_SI_RECFG   (1<<11) /*!< Hash define for SI Re-cfg */
/* ccpu00136659: CMAS ETWS design changes */
#define RGR_MAX_WARNING_SI_SEG     64 /*!< Max no of SI Warning Segements */
#endif /*RGR_SI_SCH*/
/** @} */
#define RGR_CELL_TMRS_RECFG       (1<<12) /*!< t300 Timer reconfiguration */

/* LTE_ADV_FLAG_REMOVED_START */
#define RGR_CELL_LTEA_FEATURE_RECFG (1<<13)    /*!<Macro for Power LTE-Adv Feature Reconfiguration */
/* LTE_ADV_FLAG_REMOVED_END */

#define RGR_CELL_DYN_CFI_RECFG  (1<<14)  /*!< Macro for Dynamic CFI Reconfiguration */ 
#define RGR_CELL_CNTRL_CMD_RECFG  (1<<15) /*!< Macro for Cell Control Command Cfg*/
#define RGR_CELL_AUTO_CFG_MODE_RECFG  (1<<16) /*!< Macro for Auto Config Mode chnage Reconfiguration */
#define RGR_CELL_CSG_PARAM_RECFG  (1<<17) /*!< CSG Parameter reconfiguration */

/* UE Reconfiguration related MACROs */
#define RGR_UE_TXMODE_RECFG     (1<<0)    /*!< Macro for UE TX Mode Reconfiguration */
#define RGR_UE_APRD_DLCQI_RECFG (1<<1)    /*!< Macro for UE Aperiodic DLCQI Reconfiguration */
#ifndef TFU_UPGRADE
#define RGR_UE_PRD_DLCQI_RECFG  (1<<2)    /*!< Macro for UE Periodic DLCQI Reconfiguration */
#endif
#define RGR_UE_ULHARQ_RECFG     (1<<3)    /*!< Macro for UE Uplink HARQ Reconfiguration*/
#define RGR_UE_QOS_RECFG        (1<<4)    /*!< Macro for UE QOS Reconfiguration */
#define RGR_UE_TATMR_RECFG      (1<<5)    /*!< Macro for UE TATIMER Rec */
#define RGR_UE_ULPWR_RECFG      (1<<6)    /*!< Macro for UE Uplink Power Reconfiguration */
#define RGR_UE_ACKNACK_RECFG    (1<<7)    /*!< Macro for UE ack-nack repetition Reconfiguration */
#define RGR_UE_MEASGAP_RECFG    (1<<8)    /*!< Macro for UE measurement gap Reconfiguration */
/*rgr_h_001.main_8 ADD added change for ACKNACK or MEASGAP reconfig*/
#define RGR_UE_ACKNACK_MEASGAP_RECFG  (RGR_UE_ACKNACK_RECFG | RGR_UE_MEASGAP_RECFG)
/** @name RGR_V1 */
/** @{ */
#ifdef RGR_V1
   /* rgr_h_001.main_4: [ccpu00112398] Added periodicBSR-Timer and 
   retxBSR-Timer config/re-config */
#define RGR_UE_BSRTMR_RECFG    (1<<9)    /*!< Macro for UE BSR timers 
                                           re-configuration */
#endif

#define   RGR_CPU_OVRLD_DL_TPT_DOWN           (1<<0)
#define   RGR_CPU_OVRLD_DL_TPT_UP             (1<<1)
#define   RGR_CPU_OVRLD_UL_TPT_DOWN           (1<<2)
#define   RGR_CPU_OVRLD_UL_TPT_UP             (1<<3)
#define   RGR_CPU_OVRLD_DL_DEC_NUM_UE_PER_TTI (1<<4)
#define   RGR_CPU_OVRLD_DL_INC_NUM_UE_PER_TTI (1<<5)
#define   RGR_CPU_OVRLD_UL_DEC_NUM_UE_PER_TTI (1<<6)
#define   RGR_CPU_OVRLD_UL_INC_NUM_UE_PER_TTI (1<<7)
#define   RGR_CPU_OVRLD_RESET                  0xFF
#define   RGR_MAX_PERC_NUM_UE_PER_TTI_RED      9

#define RGR_UE_CDBKSBST_RECFG   (1<<9)    /*!< Macro for CodeBook subset Reconfiguration */
#define RGR_UE_ULTXANTSEL_RECFG (1<<10)   /*!< Macro for UL TX Antenna Selection Reconfiguration */
/* rgr_h_001.main_6 - Added support for UE Reconfiguration */
#define RGR_UE_UECAT_RECFG      (1<<11)   /*!< Macro for UE Category Reconfiguration */
/** @} */
/*rgr_h_001.main_6 - Added support for SPS*/

/*rgr_h_001.main_7 - Added support for TFU Upgrade*/
#ifdef TFU_UPGRADE

#define RGR_UE_PCQI_RECFG    (1<<12)     /*!< UE Periodic CQI Reconfiguration */
#define RGR_UE_SRS_RECFG     (1<<13)    /*!< UE UL SRS Reconfiguration */
#define RGR_UE_SR_RECFG      (1<<14)    /*!< UE SR Reconfiguration */
#endif

/*rgr_h_001.main_6 - Added support for SPS*/
#define RGR_UE_DLSPS_RECFG      (1<<15)    /*!< UE DL SPS Reconfiguration */
#define RGR_UE_ULSPS_RECFG      (1<<16)    /*!< UE UL SPS Reconfiguration */
#define RGR_UE_SPS_RECFG        (RGR_UE_DLSPS_RECFG || RGR_UE_ULSPS_RECFG)


#ifdef TFU_UPGRADE

#define RGR_UE_PCQI_WB_REP       1       /*!< UE Periodic CQI Wideband Report */
#define RGR_UE_PCQI_SB_REP       2       /*!< UE Periodic CQI Subband Report */

/* Periodic CQI Cfg Values */
#define RGR_SCH_PCQI_REL   0
#define RGR_SCH_PCQI_SETUP   1

/* Periodic SRS Cfg Values */
#define RGR_SCH_SRS_REL   0
#define RGR_SCH_SRS_SETUP   1

/* Periodic SR Cfg Values */
#define RGR_SCH_SR_REL   0
#define RGR_SCH_SR_SETUP   1

#endif

#define RGR_MAX_SPS_LC 10  /*!< Maximum number of SPS LCs per UE */

/* Re-configuration type for DL LC */
#define RGR_DL_LC_QOS_RECFG     (1<<0)    /*!< Macro for DL LC QoS re-configuration*/
#define RGR_DL_LC_SPS_RECFG     (1<<1)    /*!< Macro for DL LC SPS re-configuration */

/*rgr_h_001.main_8 ADD added changes for DRX*/
#define RGR_UE_DRX_RECFG        (1<<17)    /*!<Macro for Reconfiguration of DRX params */
/** @name RGR_CQI_REPT */
/** @{ */
/*rgr_h_001.main_8 ccpu00117452 - MOD - Changed macro name from
   RGR_RRM_DLPWR_CNTRL to RGR_CQI_REPT */
#ifdef RGR_CQI_REPT
#define RGR_UE_CQIREPT_RECFG     (1<<18)
#endif
/** @} */
#define RGR_UE_PA_RECFG          (1<<19)
/* [ccpu00123958]-ADD- Bit mask for PUSCH related Reconfig  */
#define RGR_UE_PUSCH_RECFG       (1<<20)    /*!< UE PUSCH Reconfiguration */

/* LTE_ADV_FLAG_REMOVED_START */
#define RGR_UE_LTEA_RECFG      (1<<21)    /*!< UE LTE Adv Reconfiguration */
/* LTE_ADV_FLAG_REMOVED_END */

/*fib_sprint3 */
#define RGR_UE_SCELL_PUCCH_RECFG   (1<<22)    /*!< UE SCELL PUCCH Reconfiguration */
/*fib_sprint3 */
#define RGR_UE_SCELL_ADD_RECFG   (1<<23)    /*!< UE SCELL ADD Reconfiguration */
#define RGR_UE_SCELL_DEL_RECFG   (1<<24)    /*!< UE SCELL DEL Reconfiguration */
#define RGR_UE_UE_ACCESS_STRATUM_REL_RECFG   (1<<25)    /*!< UE Access Stratum Release Reconfiguration */

#define RGR_UE_CSG_PARAM_RECFG  (1<<26) /*! CSG related parameter Reconfiguration */
/* SON ICIC Changes */
#define RG_SCH_MAX_UE            16
#define RGR_SCH_MAX_PA_PER_PRB   110
/* SON ICIC Changes End */

/* Different Scheduler Type */
#define RGR_SCH_TYPE_SC1    0           /*!< Macro for Basic Scheduler */
#define RGR_SCH_TYPE_PFS    1           /*!< Macro for Profession Fair Scheduler */
#define RGR_SCH_TYPE_RR     2           /*!< Macro for Round Robin Scheduler */
#define RGR_SCH_TYPE_MAXCI  3           /*!< Macro for Max CQI Scheduler */

/* CRG-related MAX Size MACROs */  
#define RGR_MAX_SUBFRAME_NUM 10           /*!< Maximum Subframe Number */
#define RGR_CFG_TRANSID_SIZE 12           /*!< Maximum transId Size */

/* Transmit/Recieve Direction */
#define RGR_DIR_TX    (1<<0)             /*!< For Transmitting Direction */
#define RGR_DIR_RX    (1<<1)             /*!< For Receiveing Direction */
#define RGR_DIR_TX_RX RGR_DIR_TX | RGR_DIR_RX /*!< For both Receiving/Transmitting Direction */

/** @name LTE_TDD */
/** @{ */
#ifdef LTE_TDD
/* TDD-related Declarations */
#define RGR_TDD_MAX_FREQ_RSRC 6         /*!< Maximum number of frequencty resources */
#define RGR_TDD_SPL_UL_IDX    10        /*!< PRACH uplink index for special configuration */
#endif /* LTE_TDD */
/** @} */

/* Confirm Status related MACROs */
#define RGR_CFG_CFM_OK   0x00  /*!< Positive confirmation: configuration successful */
#define RGR_CFG_CFM_NOK  0x0F  /*!< Negative confirmation: configuration failed */
#define RGR_CFG_CFM_TX_COMPLETE  0x01  /*!< Negative confirmation: configuration failed */

/* Event corresponding to each primitive at this interface */
#define EVTRGRBNDREQ   1     /*!< Bind Request */
#define EVTRGRBNDCFM   2     /*!< Bind Confirm */
#define EVTRGRUBNDREQ  3     /*!< Unbind Request */
#define EVTRGRCFGREQ   4     /*!< Configuration Request */
#define EVTRGRCFGCFM   5     /*!< Configuration Confirm */
/* rgr_h_001.main_2: Added TTI indication from MAC to RGR user */
/** @name RGR_RRM_TICK */
/** @{ */
#define EVTRGRTTIIND   6     /*!< TTI Tick to RRM */
/** @} */
/* rgr_h_001.main_3-ADD-Added for SI Enhancement. */
/** @name RGR_SI_SCH */
/** @{ */
#ifdef RGR_SI_SCH
#define EVTRGRSICFGREQ 7     /*!< SI Configuration Request */
#define EVTRGRSICFGCFM 8     /*!< SI Configuration Confirm */
#endif /*RGR_SI_SCH*/
/** @} */
/*rgr_h_001.main_8 ADD added changes for CQI Management*/
/** @name RGR_CQI_REPT */
/** @{ */
/* ccpu00117452 - MOD - Changed macro name from
   RGR_RRM_DLPWR_CNTRL to RGR_CQI_REPT */
#ifdef RGR_CQI_REPT
#define EVTRGRSTAIND 9       /*!< RGR Status Indication */
#endif
/** @} */
#define EVTRGRUESTAIND 10       /*!< RGR UE Status Indication */

#ifdef RGR_SI_SCH
#define EVTRGRWARNINGSICFGREQ 11    /*!< Warning SI Configuration Request */
#define EVTRGRWARNINGSISTOPREQ 12   /*!< Warning SI Stop Request */
#define EVTRGRWARNINGSICFGCFM 13     /*!< Warning SI Configuration Confirm */
#endif /*RGR_SI_SCH*/
/** @} */

/** @{ */
/* LTE_ADV_FLAG_REMOVED_START */
#define EVTRGRLOADINFIND 14  /*!< LOAD INF Indication (SCTP -> SCH -> APP) (Received at X2AP)*/

#define EVTRGRLOADINFREQ 15  /*!< LOAD INF Request (APP -> MAC -> SCTP) (To Remote X2AP) */
/* LTE_ADV_FLAG_REMOVED_END */
/** @} */
/* Activation time limit in terms of number of frames */
#define RGR_ACTV_WIN_SIZE 20 /*!< Size of activation time window
                                (in terms of number of frames) */

/* rgr_h_001.main_3-ADD-Added for SI Enhancement. */
/** @name RGR_SI_SCH */
/** @{ */
#ifdef RGR_SI_SCH
/*SI Scheduling Specific */
#define RGR_MAX_NUM_SI           16 /*!< Maximum Number of SI */
#endif /*RGR_SI_SCH*/
/** @} */
/*CA-Dev */
#define RGR_MAX_SCELL_PER_UE     7
/*rgr_h_001.main_8 ADD added changes for CQI Management*/
/** @name RGR_CQI_REPT */
/** @{ */
/* DL Power Control Constants/Macros */
/* ccpu00117452 - MOD - Changed macro name from
   RGR_RRM_DLPWR_CNTRL to RGR_CQI_REPT */
#ifdef RGR_CQI_REPT
#define RGR_CQIRPTS_MAXN     16  /*!< Maximum number of CQI report collation
                                      allowed */
#endif
#define RGR_MAX_DL_CQI_SUBBAND   13 /*!< Maximum number of Sub-Bands */
/** @} */
/* Selector(coupling) values */
#define RGR_SEL_TC              1   /*!< For Tight Coupling */
#define RGR_SEL_LC              0   /*!< For Loose coupling */

/* Pack/ Unpack error code */
#define ERGRXXX                 0
#define ERRRGR                  0
/*rgr_h_001.main_8 ADD added changes for ERR Val*/

#define   ERGR001      (ERRRGR +    1)    /*        rgr.c: 155 */
#define   ERGR002      (ERRRGR +    2)    /*        rgr.c: 163 */
#define   ERGR003      (ERRRGR +    3)    /*        rgr.c: 172 */
#define   ERGR004      (ERRRGR +    4)    /*        rgr.c: 221 */
#define   ERGR005      (ERRRGR +    5)    /*        rgr.c: 230 */
#define   ERGR006      (ERRRGR +    6)    /*        rgr.c: 276 */
#define   ERGR007      (ERRRGR +    7)    /*        rgr.c: 284 */
#define   ERGR008      (ERRRGR +    8)    /*        rgr.c: 293 */
#define   ERGR009      (ERRRGR +    9)    /*        rgr.c: 343 */
#define   ERGR010      (ERRRGR +   10)    /*        rgr.c: 352 */
#define   ERGR011      (ERRRGR +   11)    /*        rgr.c: 397 */
#define   ERGR012      (ERRRGR +   12)    /*        rgr.c: 405 */
#define   ERGR013      (ERRRGR +   13)    /*        rgr.c: 414 */
#define   ERGR014      (ERRRGR +   14)    /*        rgr.c: 463 */
#define   ERGR015      (ERRRGR +   15)    /*        rgr.c: 472 */
#define   ERGR016      (ERRRGR +   16)    /*        rgr.c: 520 */
#define   ERGR017      (ERRRGR +   17)    /*        rgr.c: 529 */
#define   ERGR018      (ERRRGR +   18)    /*        rgr.c: 539 */
#define   ERGR019      (ERRRGR +   19)    /*        rgr.c: 549 */
#define   ERGR020      (ERRRGR +   20)    /*        rgr.c: 559 */
#define   ERGR021      (ERRRGR +   21)    /*        rgr.c: 611 */
#define   ERGR022      (ERRRGR +   22)    /*        rgr.c: 620 */
#define   ERGR023      (ERRRGR +   23)    /*        rgr.c: 628 */
#define   ERGR024      (ERRRGR +   24)    /*        rgr.c: 641 */
#define   ERGR025      (ERRRGR +   25)    /*        rgr.c: 756 */
#define   ERGR026      (ERRRGR +   26)    /*        rgr.c: 764 */
#define   ERGR027      (ERRRGR +   27)    /*        rgr.c: 774 */
#define   ERGR028      (ERRRGR +   28)    /*        rgr.c: 825 */
#define   ERGR029      (ERRRGR +   29)    /*        rgr.c: 834 */
#define   ERGR030      (ERRRGR +   30)    /*        rgr.c: 849 */
#define   ERGR031      (ERRRGR +   31)    /*        rgr.c: 897 */
#define   ERGR032      (ERRRGR +   32)    /*        rgr.c: 905 */
#define   ERGR033      (ERRRGR +   33)    /*        rgr.c: 914 */
#define   ERGR034      (ERRRGR +   34)    /*        rgr.c: 923 */
#define   ERGR035      (ERRRGR +   35)    /*        rgr.c: 973 */
#define   ERGR036      (ERRRGR +   36)    /*        rgr.c: 982 */
#define   ERGR037      (ERRRGR +   37)    /*        rgr.c: 991 */
#define   ERGR038      (ERRRGR +   38)    /*        rgr.c:1040 */
#define   ERGR039      (ERRRGR +   39)    /*        rgr.c:1048 */
#define   ERGR040      (ERRRGR +   40)    /*        rgr.c:1057 */
#define   ERGR041      (ERRRGR +   41)    /*        rgr.c:1066 */
#define   ERGR042      (ERRRGR +   42)    /*        rgr.c:1117 */
#define   ERGR043      (ERRRGR +   43)    /*        rgr.c:1126 */
#define   ERGR044      (ERRRGR +   44)    /*        rgr.c:1135 */
#define   ERGR045      (ERRRGR +   45)    /*        rgr.c:7376 */
#define   ERGR046      (ERRRGR +   46)    /*        rgr.c:7386 */
#define   ERGR047      (ERRRGR +   47)    /*        rgr.c:7397 */
#define   ERGR048      (ERRRGR +   48)    /*        rgr.c:7408 */
#define   ERGR049      (ERRRGR +   49)    /*        rgr.c:7420 */
#define   ERGR050      (ERRRGR +   50)    /*        rgr.c:7471 */
#define   ERGR051      (ERRRGR +   51)    /*        rgr.c:7480 */
#define   ERGR052      (ERRRGR +   52)    /*        rgr.c:7489 */
#define   ERGR053      (ERRRGR +   53)    /*        rgr.c:7503 */
#define   ERGR054      (ERRRGR +   54)    /*        rgr.c:7721 */
#define   ERGR055      (ERRRGR +   55)    /*        rgr.c:7733 */
#define   ERGR056      (ERRRGR +   56)    /*        rgr.c:7745 */
#define   ERGR057      (ERRRGR +   57)    /*        rgr.c:7759 */
#define   ERGR058      (ERRRGR +   58)    /*        rgr.c:7808 */
#define   ERGR059      (ERRRGR +   59)    /*        rgr.c:7819 */
#define   ERGR060      (ERRRGR +   60)    /*        rgr.c:7833 */
#define   ERGR061      (ERRRGR +   61)    /*        rgr.c:7703 */
#define   ERGR062      (ERRRGR +   62)    /*        rgr.c:7714 */
#define   ERGR063      (ERRRGR +   63)    /*        rgr.c:7727 */
#define   ERGR064      (ERRRGR +   64)    /*        rgr.c:7740 */
#define   ERGR065      (ERRRGR +   65)    /*        rgr.c:7757 */
#define   ERGR066      (ERRRGR +   66)    /*        rgr.c:7811 */
#define   ERGR067      (ERRRGR +   67)    /*        rgr.c:7822 */
#define   ERGR068      (ERRRGR +   68)    /*        rgr.c:7833 */
#define   ERGR069      (ERRRGR +   69)    /*        rgr.c:7851 */
#define   ERGR070      (ERRRGR +   70)    /*        rgr.c:8023 */
#define   ERGR071      (ERRRGR +   71)    /*        rgr.c:8035 */
#define   ERGR072      (ERRRGR +   72)    /*        rgr.c:8083 */
#define   ERGR073      (ERRRGR +   73)    /*        rgr.c:7833 */
#define   ERGR074      (ERRRGR +   74)    /*        rgr.c:8138 */
#define   ERGR075      (ERRRGR +   75)    /*        rgr.c:8148 */
#define   ERGR076      (ERRRGR +   76)    /*        rgr.c:8159 */
#define   ERGR077      (ERRRGR +   77)    /*        rgr.c:8170 */
#define   ERGR078      (ERRRGR +   78)    /*        rgr.c:8181 */
#define   ERGR079      (ERRRGR +   79)    /*        rgr.c:8234 */
#define   ERGR080      (ERRRGR +   80)    /*        rgr.c:8245 */
#define   ERGR081      (ERRRGR +   81)    /*        rgr.c:8256 */
#define   ERGR082      (ERRRGR +   82)    /*        rgr.c:8038 */
#define   ERGR083      (ERRRGR +   83)    /*        rgr.c:8110 */

#endif /* __RGR_H__ */


/**********************************************************************

         End of file:     rgr.h@@/main/9 - Wed Jul 27 13:44:32 2011
  
**********************************************************************/

/**********************************************************************
  
        Notes:
  
**********************************************************************/

/**********************************************************************

**********************************************************************/


/**********************************************************************
  
        Revision history:
  
**********************************************************************/
  
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---       sdass 1. Initial Release.
/main/2      ---       sdass 1. LTE MAC 2.1 release
/main/3      ---  rgr_h_001.main_2 sm    1. ccpu00107561: Fixing a compilation issue.   
                                         2. Added TTI indication from MAC to RGR 
                                             user.
/main/4      ---  rgr_h_001.main_3  rnt  1. Modified for SI Enhancement.
/main/5      ---  rgr_h_001.main_4  sd   1. [ccpu00112398]Added BSR timers and 
                                          contention resolution timer
                                          configuration/re-configuration.
/main/6      ---      rgr_h_001.main_5   ap  1. Added support for MIMO
/main/7      ---      rgr_h_001.main_6 rsharon  1. Added support for SPS
/main/8      ---      rgr_h_001.main_7 dv  1. Added changes of TFU_UPGRADE. 
/main/9      ---      rgr_h_001.main_8 gvj  1. Updated for LTE MAC Rel 3.1
*********************************************************************91*/
