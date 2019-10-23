

/**********************************************************************
 
    Name:   LTE RRM layer
 
    Type:   C include file
 
    Desc:   Defines required by LTE RRM
 
    File:   lrm.x
 
    Sid:      lrm.x@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/T2K_MergeTemp_BR/1 - Mon Sep  2 16:44:24 2013
 
    Prm:    sm
 
**********************************************************************/
 

/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*     1000372       LTE RRM
*
*/

/* lrm_x_001.main_3 */
/**
  @file lrm.x
  @brief Structure declarations and definitions for LRM interface.
  */

#ifndef __LRMX__
#define __LRMX__

#include "cm_lte_rrm.x"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** 
 * @brief
   This structure holds configuration parameters for RRM General Configuration. */
typedef struct rmGenCfg
{
   Pst      lmPst;      /*!< Layer manager post structure */
   MemoryId mem;        /*!< Region and pool ID */
   U8       tmrRes;     /*!< Timer resolution for Low SAP Bind Timer */
   U8       maxRmuSaps; /*!< Maximum number of RM Upper SAP's */
} LRM_PACK_STRUCT RmGenCfg;

/** 
 * @brief
   This structure holds configuration parameters for RRM Upper SAP Configuration. */
typedef struct rmUSapCfg
{
   Selector selector;   /*!< Selector */
   MemoryId mem;        /*!< Region and pool ID */
   Priority prior;      /*!< Priority */
   ProcId   procId;     /*!< Processor ID */
   Ent      ent;        /*!< Entity ID */
   Inst     inst;       /*!< Instance ID */
   Route    route;      /*!< Route */
   SpId     spId;       /*!< Service provider ID */
   SuId     suId;       /*!< Service user ID */
} LRM_PACK_STRUCT RmUSapCfg;

/** 
 * @brief
   This structure holds configuration parameters for RRM Lower SAP Configuration. */
typedef struct rmLSapCfg
{
   Selector selector;   /*!< Selector */
   MemoryId mem;        /*!< Region and pool ID */
   Priority prior;      /*!< Priority */
   ProcId   procId;     /*!< Processor ID */
   Ent      ent;        /*!< Entity ID */
   Inst     inst;       /*!< Instance ID */
   Route    route;      /*!< Route */
   SpId     spId;       /*!< Service provider ID */
   SuId     suId;       /*!< Service user ID */
   TmrCfg   bndTmr;     /*!< Bind Timer Value */
} LRM_PACK_STRUCT RmLSapCfg;

/** 
 * @brief
   This structure holds configuration parameters for RRM. */
typedef struct rmCfg
{
   union
   {
      RmGenCfg    genCfg;  /*!< General Configuration */
      /* SAPs for the RRM layer */
      RmUSapCfg   rmuSap;  /*!< RMU interface SAP */
      RmLSapCfg   rgmSap;  /*!< RMU interface SAP */
   }s;
} LRM_PACK_STRUCT RmCfg;

/** 
 * @brief
   This structure holds RRM's SAP Control information. */
typedef struct rmSapCntrl
{
   SuId suId;            /*!< Service user ID */
   SpId spId;            /*!< Service provider ID */
} LRM_PACK_STRUCT RmSapCntrl;

/** 
 * @brief
   This structure holds RRM's Control information. */
typedef struct rmCntrl
{
   DateTime      dt;          /*!< Date and Time */
   U8            action;      /*!< Action */
   U8            subAction;   /*!< Sub-action */
   U8            instId;      /*!< Scheduler instance ID */
   union
   {
      RmSapCntrl rmSapCntrl;  /*!< SAP Control */
   }u;
   
} LRM_PACK_STRUCT RmCntrl; 


typedef enum lrmCfgAction
{
	LRM_CFG_ADD = 1, 
   LRM_CFG_MOD, 
   LRM_CFG_DEL
} LrmCfgAction;

typedef enum lrmCellBandwidth
{
   LRM_BANDWIDTH_6,
   LRM_BANDWIDTH_15,
   LRM_BANDWIDTH_25,
   LRM_BANDWIDTH_50,
   LRM_BANDWIDTH_75,
   LRM_BANDWIDTH_100,
   LRM_BANDWIDTH_MAX
}LrmCellBandwidth;

/* SPS changes starts */
typedef struct lrmSpsCellConfigData
{
   Bool                       bIsSpsEnabled;       /*!< TRUE = SPS is Enabled and FALSE = SPS is diabled */
   U16                        usMaxDlSpsUePerTti;  /*!< Number of DL SPS User per TTI for new transmission */
   U16                        usMaxUlSpsUePerTti;  /*!< Number of UL SPS User per TTI for new transmission */
} LrmSpsCellConfigData;  
/* SPS changes ends */

typedef enum lrmSplSfConfig
{
   LRM_SPL_SF_CONFIG_0,
   LRM_SPL_SF_CONFIG_1,
   LRM_SPL_SF_CONFIG_2,
   LRM_SPL_SF_CONFIG_3,
   LRM_SPL_SF_CONFIG_4,
   LRM_SPL_SF_CONFIG_5,
   LRM_SPL_SF_CONFIG_6,
   LRM_SPL_SF_CONFIG_7,
   LRM_SPL_SF_CONFIG_8
}LrmSplSfConfig;
typedef enum lrmUlDlConfig
{
   LRM_UL_DL_CONFIG_0,
   LRM_UL_DL_CONFIG_1,
   LRM_UL_DL_CONFIG_2,
   LRM_UL_DL_CONFIG_3,
   LRM_UL_DL_CONFIG_4,
   LRM_UL_DL_CONFIG_5,
   LRM_UL_DL_CONFIG_6,
   LRM_UL_DL_CONFIG_MAX
}LrmUlDlConfig;
#ifdef LTE_TDD
typedef enum lrmCqiPrdcty
{
   LRM_CQI_PRDCTY_1,
   LRM_CQI_PRDCTY_5,
   LRM_CQI_PRDCTY_10,
   LRM_CQI_PRDCTY_20,
   LRM_CQI_PRDCTY_40,
   LRM_CQI_PRDCTY_80,
   LRM_CQI_PRDCTY_160,
   LRM_CQI_PRDCTY_MAX
}LrmCqiPrdcty;
#else
typedef enum lrmCqiPrdcty
{
   LRM_CQI_PRDCTY_2,
   LRM_CQI_PRDCTY_5,
   LRM_CQI_PRDCTY_10,
   LRM_CQI_PRDCTY_20,
   LRM_CQI_PRDCTY_40,
   LRM_CQI_PRDCTY_80,
   LRM_CQI_PRDCTY_160,
   LRM_CQI_PRDCTY_32,
   LRM_CQI_PRDCTY_64,
   LRM_CQI_PRDCTY_128,
   LRM_CQI_PRDCTY_MAX
}LrmCqiPrdcty;
#endif
typedef enum lrmSrPrdcty
{
   LRM_SR_PRDCTY_5,
   LRM_SR_PRDCTY_10,
   LRM_SR_PRDCTY_20,
   LRM_SR_PRDCTY_40,
   LRM_SR_PRDCTY_80,
   LRM_SR_PRDCTY_2,
   LRM_SR_PRDCTY_1,
   LRM_SR_PRDCTY_MAX
}LrmSrPrdcty;


typedef struct lrmCellConfigData
{
   CmRrmCellDrxCfg      stRmCellDrxCfg;
	LrmCellBandwidth		enCellDlBandWidth;
   CmRrmAcbInfo         stAcbInfo; /*!< ACB information */
	U16						usMaxUlBroadbandBw;
	U16						usMaxDlBroadbandBw;
   U16                  usN1Pucch;                    
	U8						   bNRbCqi; /* N2Rb */
	U8						   bNCsAn;/*N1Cs */
	U8					      bMaxActiveUesServed;
	U8						   bMaxSigUesServed;
	U8						   flagDlfsScheduling;
	U8						   flagTransMode;
	U8						   bWaitTime;
	U8						   bCellId;
   U8                   bRcmAlgoType;
	U8 						bNumTxAnt;
   LrmSrPrdcty          enSrPrdcty;
   LrmCqiPrdcty         enCqiPrdcty;
   U16                  usNumSrResPerTti;
   U16                  usNumCqiResPerTti;
   LrmUlDlConfig        enUlDlConfig;
   LrmSplSfConfig       enSplSfCfg;
   CmRrmDsrTransMax     enDsrTransMax;
   Bool                 bSimulCqiAckNack;
   U8                   bArpForEmergencyBearer;
   LrmSpsCellConfigData stSpsCellCfg;
   U32                  utNumOfPrbRpts;  /*number of PRB reports received */
   U32                  utPrbRptInterval;/*PRB report interval for MAC/SCH to
                                         report to RRM*/
   U8                   bMaxAvgGbrPrbUsage; /* maximum average PRB Usage limit */
   U16                   bRbcQci1TmngReq; /* QCI-1 Timing Requirment in ms */
   U8                   bRbcQci2TmngReq; /* QCI-2 Timing Requirment in ms */
   U8                   bRbcQci3TmngReq; /* QCI-3 Timing Requirment in ms */
   U8                   bRbcQci4TmngReq; /* QCI-4 Timing Requirment in ms */
   U8                   bRbcQci4TmngReqEnable; /* To enable od disable the QCI-4 Timing Requirment*/
   U8                   bNumDlNewUesPerTti;
   U8                   bNumUlNewUesPerTti;
   U8                   bNumDlReTxUesPerTti;
   U8                   bNumUlReTxUesPerTti;
   U8                   bDuplexMode;
   U8                    usAccessMode;
   U16                   usMaxNonCsgUes;
   U16                   usMaxCsgUes;
   U16                   usMaxExtraUes;
   /*CA dev Start*/
   U8                    usMaxDlUePerTti;
   Bool                  bIsCaEnabled;
   /*CA dev End*/
} LRM_PACK_STRUCT LrmCellConfigData;


typedef struct lrmCellConfiguration
{
	LrmCfgAction		 	 enCellAddModDel;
	LrmCellConfigData		 stCellCfgInfo;
	U16						 usReCfgType;
} LRM_PACK_STRUCT LrmCellConfiguration;

typedef struct lrmCellCfgRsp
{
	LrmStatusCause			 statusInfo;
	U8 						 bCellId;
} LRM_PACK_STRUCT LrmCellCfgRsp;

typedef struct lrmEnodebCfgResp
{
	LrmStatusCause		statusInfo;
} LRM_PACK_STRUCT LrmEnodebCfgResp;


#define LRM_PROTOCFG_ADD_CELL   1
#define LRM_PROTOCFG_MOD_CELL   2
#define LRM_PROTOCFG_DEL_CELL   3

/** @brief This structure contains the MME configuration Information.
 *
 * - LrmCfgAction addModOrDel: Action to be taken - Addition, Modification
 *                               or Deletion
 * - U16 mmeId:                  MME Identifier
 */
typedef struct lrmMmeCfg
{
   LrmCfgAction               enMmeAddModOrDel;
   U16                        usMmeId;
} LRM_PACK_STRUCT LrmMmeCfg;

#define RRM_ENB_CFG_SYS_CFG	1
#define RRM_ENB_CFG_MME_CFG	2

typedef struct lrmEnbConfiguration
{
	U8						 bCfgType; /* Configuration add or Mod */
   union
   {
	   U8						 bMaxNumCells;
	   LrmMmeCfg          stMmeCfg;
   } u;
} LRM_PACK_STRUCT LrmEnbConfiguration;

typedef enum lrmCfgType
{
	LRM_ENB_CONFIG,
	LRM_CELL_CONFIG
}LrmCfgType;

typedef struct rmProtoCfg
{
	LrmCfgType					  bCfgType;/* Cell level or system level configuration */
	union
	{
		LrmCellConfiguration   stCellCfg;
		LrmEnbConfiguration	  stEnbCfg;
	} u;
} LRM_PACK_STRUCT RmProtoCfg;


/** 
 * @brief
   This structure holds RRM diagnostics information. */
typedef struct rmUstaDgn
{
  U8  bType;
  union {
     Mem    stMem;
  }u;
} LRM_PACK_STRUCT RmUstaDgn;

/** 
 * @brief
   This structure holds RRM alarm information. */
typedef struct lrmRmUsta
{
   CmAlarm     alarm;
   RmUstaDgn   stDgn;
} LRM_PACK_STRUCT LrmRmUsta;

/** @enum LrmEnbStaType
 *
 * Indicates the ENB Status indication type. Only either CPU Load or MME status
 * can be indicated to RRM in a status indication message.
 *
 * - RRM_WR_ENBSTATYPE_CPULOAD   0
 * - RRM_WR_ENBSTATYPE_MMESTA    1
 */
typedef enum lrmEnbStaType
{
   LRM_ENBSTATYPE_CELLUP,
   LRM_ENBSTATYPE_CPULOAD
}LrmEnbStaType;

/** @brief This structure contains the eNodeB status indication parameters.
 * 
 * - LrmEnbStaType staType:    eNodeB status indication type. i.e cpu load
 *                               indication or mme overload indication.
 * - U8 cpuLoad:                 CPU load of eNodeB
 * - LrmMmeStaInfo mmeStatus:  MME status Information structure.
 */
typedef struct lrmEnbStaInd
{
   LrmEnbStaType              enStaType;
   union {
      U8                      bCpuLoad;
      U8                      bCellId;
   }u;
} LRM_PACK_STRUCT LrmEnbStaInd;

/** 
 * @brief
   This structure holds status and alaram information. */
typedef struct rmUsta
{
   U8   bStaType;                
   union {
      LrmEnbStaInd     stEnbStaInfo;
      LrmRmUsta        stAlarm;
   }u;
} LRM_PACK_STRUCT RmUsta;



/** 
 * @brief
   This structure holds RRM's Configuration and Control Management Information. */
typedef struct rmMngmt
{
   Header     hdr;       /*!< Header */
   CmStatus   cfm;       /*!< Confirmation */
   union
   {
      RmCfg       cfg;       /*!< Configuration */
      RmCntrl     cntrl;     /*!< Control */
      RmProtoCfg  protoCfg;  /*!< Protocol configuration*/
      RmUsta      usta;      /*!< Unsolicited status */ 
   }t;
} LRM_PACK_STRUCT RmMngmt;


/* 
   Function Prototype Typedefs 
. */
typedef S16 (*LrmCfgReq) ARGS((
        Pst        *pst,               /* Post Structure */
        RmMngmt    *cfg                /* Management Structure */
     ));

typedef S16 (*LrmCfgCfm)     ARGS((
        Pst        *pst,               /* Post Structure */
        RmMngmt    *cfg                /* Management Structure */
     ));

typedef S16 (*LrmCntrlReq)     ARGS((
        Pst         *pst,               /* Post Structure */
        RmMngmt     *cntrl              /* Management Structure */
     ));

typedef S16 (*LrmEnbStatusInd)     ARGS((
        Pst         *pst,               /* Post Structure */
        RmMngmt     *usta                /* Management Structure */
     ));


typedef S16 (*LrmStaInd)     ARGS((
        Pst         *pst,               /* Post Structure */
        RmMngmt     *usta                /* Management Structure */
     ));

typedef S16 (*LrmCntrlCfm)     ARGS((
        Pst         *pst,               /* Post Structure */
        RmMngmt     *usta                /* Management Structure */
     ));

/* 
   Function Prototypes.
 */
#ifdef RM_INTF
/* lrm_x_001.main_3 - ADD -  Added the comments for the following function */
 /** @brief This primitive is sent from Layer manager to RRM. It carries
  * configuration information towards RRM.
  * @details This primitive can be used by layer manager to configure the
  * following entities at RRM.
  * -# General configuration
  * -# RMU SAP i.e. SAP towards RLC
  * -# CRM SAP i.e. SAP towards RRC
  * -# TFU SAP i.e. SAP towards Physical layer
  * 
  * @param pst pointer to Pst
  * @param cfg pointer to RmMngmt
  * @return ROK/RFAILED
  */
EXTERN S16 RmMiLrmCfgReq ARGS((Pst *pst, RmMngmt *cfg));

/* lrm_x_001.main_3 - ADD -  Added the comments for the following function */
 /** @brief This primitive is sent from Layer manager to RRM. It carries
  * control information towards RRM.
  * @details This primitive can be used by layer manager to control the
  * following entities at RRM.
  * -# Bind Request 
  * -# RMU SAP i.e. SAP towards RLC
  * -# CRM SAP i.e. SAP towards RRC
  * -# TFU SAP i.e. SAP towards Physical layer
  * 
  * @param pst pointer to Pst
  * @param cfg pointer to RmMngmt
  * @return ROK/RFAILED
  */
EXTERN S16 RmMiLrmCntrlReq ARGS((Pst *pst, RmMngmt *cntrl));

 /** @brief This primitive carries the Confirmation for a Configuration Request
  * sent from the layer manager to RRM.
  * @details This primitive is used by RRM to inform Layer manager about the
  * status of a Configuration Request.
  * @param pst Pointer to the post structure.
  * @param cfm pointer to RmMngmt 
  * @return ROK/RFAILED
  */
EXTERN S16 RmMiLrmCfgCfm ARGS((Pst *pst, RmMngmt *cfm));

 /** @brief This primitive carries the control request sent from the layer
  * manager to RRM layer.
  * @details This primitive is sent from the layer manager to control the RRM
  * layer. The following entities could be controlled using this primitive.
  * -# Binding of lower SAPs
  * @param pst Pointer to the post structure.
  * @param cfm pointer to RmMngmt 
  * @return ROK/RFAILED
  */
EXTERN S16 RmMiLrmCntrlReq ARGS((Pst *pst, RmMngmt *cntrl));
 /** @brief This primitive carries the Confirmation for a Control Request
  * sent from the layer manager to RRM.
  * @details This primitive is used by RRM to inform Layer manager about the
  * status of a Control Request.
  * @param pst Pointer to the post structure.
  * @param cfm pointer to RmMngmt 
  * @return ROK/RFAILED
  */
EXTERN S16 RmMiLrmCntrlCfm ARGS(( Pst *pst, RmMngmt *cfm));


 /** @brief This primitive carries the Unsolicited status indications from RRM
  * to the layer manager i.e. Alarms.
  * @details This primitive is used by RRM to inform Layer manager about some
  * error conditions or bind confirmations.
  * @param pst Pointer to the post structure.
  * @param usta pointer to RmMngmt 
  * @return ROK/RFAILED
  */
EXTERN S16 RmMiLrmEnbStaInd ARGS((Pst *pst,  RmMngmt *usta));


 /** @brief This primitive carries the Unsolicited status indications from RRM
  * to the layer manager i.e. Alarms.
  * @details This primitive is used by RRM to inform Layer manager about some
  * error conditions or bind confirmations.
  * @param pst Pointer to the post structure.
  * @param usta pointer to RmMngmt 
  * @return ROK/RFAILED
  */
EXTERN S16 RmMiLrmStaInd ARGS((Pst *pst,  RmMngmt *usta));

#endif /* RM. */





#ifdef SM 
EXTERN S16 smRmActvInit ARGS((Ent ent,Inst inst, Region region,Reason reason));
EXTERN S16 smRmActvTsk ARGS((Pst *pst, Buffer *mBuf));
EXTERN S16 SmMiLrmCfgReq ARGS((Pst *pst, RmMngmt *cfg));
EXTERN S16 SmMiLrmCfgCfm ARGS((Pst *pst, RmMngmt *cfm));
EXTERN S16 SmMiLrmStaInd ARGS((Pst *pst, RmMngmt *usta));
EXTERN S16 SmMiLrmEnbStaInd ARGS((Pst *pst, RmMngmt *usta));
EXTERN S16 SmMiLrmCntrlReq ARGS((Pst *pst, RmMngmt *cntrl));
EXTERN S16 SmMiLrmCntrlCfm ARGS(( Pst *pst, RmMngmt *cfm));
#endif /* SM. */


/*
   Function Prototypes for Packing and Unpacking the primitives.
 */
#ifdef LWLCSMRMMILRM 
/** @brief This API is used to send a 
Config Request from LM to RRM.*/
EXTERN S16 cmPkLwLcLrmCfgReq ARGS((
   Pst *                pst,
   RmMngmt *            cfg
));


/** @brief This API is used to send a 
Configuration Request from LM to RRM. */
EXTERN S16 cmUnpkLwLcLrmCfgReq ARGS((
   LrmCfgReq            func,
   Pst                  *pst,
   Buffer               *mBuf
));

/** @brief This API is used to send a 
Configuration Confirm from RRM to LM. */
EXTERN S16 cmPkLwLcLrmCfgCfm ARGS((
   Pst *                pst,
   RmMngmt *            cfm
));
/** @brief This API is used to send a 
Configuration Confirm from RRM to LM. */
EXTERN S16 cmUnpkLwLcLrmCfgCfm ARGS((
   LrmCfgCfm            func,
   Pst *                pst,
   Buffer               *mBuf
));

/** @brief This API is used to send a 
Control Request from LM to RRM. */
EXTERN S16 cmUnpkLwLcLrmCntrlReq ARGS((
   LrmCntrlReq           func,
   Pst *                 pst,
   Buffer               *mBuf
));

/** @brief This API is used to send a 
control Request from LM to RRM.*/
EXTERN S16 cmPkLwLcLrmCntrlReq ARGS((
   Pst *                pst,
   RmMngmt *            cntrl
));
/** @brief This API is used to send a 
Control Confirm from RRM to LM.*/
EXTERN S16 cmPkLwLcLrmCntrlCfm ARGS((
   Pst *                pst,
   RmMngmt *            cfm
));
/** @brief This API is used to send a 
Control Confirm from RRM to LM. */
EXTERN S16 cmUnpkLwLcLrmCntrlCfm ARGS((
   LrmCntrlCfm          func,
   Pst *                pst,
   Buffer               *mBuf
));

/** @brief This API is used to send a 
Status Indication from RRM to LM. */
EXTERN S16 cmPkLwLcLrmEnbStaInd ARGS((
   Pst *                pst,
   RmMngmt *            usta
));

/** @brief This API is used to send a 
Status Indication from RRM to LM. */
EXTERN S16 cmPkLwLcLrmStaInd ARGS((
   Pst *                pst,
   RmMngmt *            usta
));
/** @brief This API is used to send a 
Status Indication from RRM to LM. */
EXTERN S16 cmUnpkLwLcLrmEnbStaInd ARGS((
   LrmEnbStatusInd            func,
   Pst *                pst,
   Buffer               *mBuf
));
/** @brief This API is used to send a 
Status Indication from RRM to LM. */
EXTERN S16 cmUnpkLwLcLrmStaInd ARGS((
   LrmStaInd            func,
   Pst *                pst,
   Buffer               *mBuf
));
#endif


/*
   Function Prototypes for Packing and Unpacking the primitives.
 */
#if (defined(LCSMRMMILRM))
/** @brief This API is used to send a 
Config Request from LM to RRM.*/
EXTERN S16 cmPkLrmCfgReq ARGS((
   Pst *                pst,
   RmMngmt *            cfg
));
/** @brief This API is used to send a 
Configuration Request from LM to RRM. */
EXTERN S16 cmUnpkLrmCfgReq ARGS((
   LrmCfgReq            func,
   Pst *                pst,
   Buffer               *mBuf
));

/** @brief This API is used to send a 
Configuration Confirm from RRM to LM. */
EXTERN S16 cmPkLrmCfgCfm ARGS((
   Pst *                pst,
   RmMngmt *            cfm
));
/** @brief This API is used to send a 
Configuration Confirm from RRM to LM. */
EXTERN S16 cmUnpkLrmCfgCfm ARGS((
   LrmCfgCfm            func,
   Pst *                pst,
   Buffer               *mBuf
));

/** @brief This API is used to send a 
Control Request from LM to RRM. */
EXTERN S16 cmUnpkLrmCntrlReq ARGS((
   LrmCntrlReq           func,
   Pst *                 pst,
   Buffer               *mBuf
));

/** @brief This API is used to send a 
Status Indication from RRM to LM. */
EXTERN S16 cmPkLrmEnbStaInd ARGS((
   Pst *                pst,
   RmMngmt *            usta
));
/** @brief This API is used to send a 
Status Indication from RRM to LM. */
EXTERN S16 cmUnpkLrmEnbStaInd ARGS((
   LrmStaInd            func,
   Pst *                pst,
   Buffer               *mBuf
));

/** @brief This API is used to send a 
Status Indication from RRM to LM. */
EXTERN S16 cmPkLrmStaInd ARGS((
   Pst *                pst,
   RmMngmt *            usta
));
/** @brief This API is used to send a 
Status Indication from RRM to LM. */
EXTERN S16 cmUnpkLrmStaInd ARGS((
   LrmStaInd            func,
   Pst *                pst,
   Buffer               *mBuf
));
/** @brief This API is used to send a 
Control Request from LM to RRM. */
EXTERN S16 cmPkLrmCntrlReq ARGS((
   Pst *                pst,
   RmMngmt *            cntrl
));
/** @brief This API is used to send a 
Control Request from LM to RRM. */
EXTERN S16 cmUnpkLrmCntrlReq ARGS((
   LrmCntrlReq          func,
   Pst *                pst,
   Buffer               *mBuf
));
/** @brief This API is used to send a 
Control Confirm from RRM to LM.*/
EXTERN S16 cmPkLrmCntrlCfm ARGS((
   Pst *                pst,
   RmMngmt *            cfm
));
/** @brief This API is used to send a 
Control Confirm from RRM to LM. */
EXTERN S16 cmUnpkLrmCntrlCfm ARGS((
   LrmCntrlCfm          func,
   Pst *                pst,
   Buffer               *mBuf
));
EXTERN S16 cmPkRmGenCfg ARGS((
   RmGenCfg             *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkRmGenCfg ARGS((
   RmGenCfg             *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkRmUpSapCfg ARGS((
   RmUSapCfg           *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkRmUpSapCfg ARGS((
   RmUSapCfg           *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkRmLowSapCfg ARGS((
   RmLSapCfg          *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkRmLowSapCfg ARGS((
   RmLSapCfg          *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkRmCfg ARGS((
   RmCfg                *param,
   S16                  elmnt,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkRmCfg ARGS((
   RmCfg                *param,
   S16                  elmnt,
   Buffer               *mBuf
));
EXTERN S16 cmPkRmCntrl ARGS((
   RmCntrl              *param,
   S16                  elmnt,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkRmCntrl ARGS((
   RmCntrl              *param,
   S16                  elmnt,
   Buffer               *mBuf
));
EXTERN S16 cmPkRmMngmt ARGS((
   Pst *pst,
   RmMngmt *param,
   U8 eventType,
   Buffer *mBuf
));
EXTERN S16 cmUnpkRmMngmt ARGS((
   Pst *pst,
   RmMngmt *param,
   U8 eventType,
   Buffer *mBuf
));
#endif

EXTERN S16 rrmInit(U8 itfType);
EXTERN S16 rmActvTsk(Pst      *pst,Buffer   *mBuf);
EXTERN S16 rmActvInit( Ent entity,            /* entity */
                       Inst inst,             /* instance */
                       Region region,         /* region */
                       Reason reason          /* reason */
                     ); 


#ifdef __cplusplus
}
#endif

#endif /* __LRMX__. */


/**********************************************************************
**********************************************************************/

