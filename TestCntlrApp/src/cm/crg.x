
/**********************************************************************

  Name:     LTE-MAC layer 
  
  Type:     C Include File 
  
  Desc:     Structures, variables and typedefs required by the LTE MAC-RRC
            Control (CRG) interface.

  File:     crg.x 

  Sid:      crg.x@@/main/6 - Wed Jul 27 12:44:19 2011

  Prg:      sdass 

**********************************************************************/

#ifndef __CRG_X__
#define __CRG_X__

/** 
  @file crg.x 
  @brief Structure declarations and definitions for CRG interface.
  */

#ifdef __cplusplus
extern "C" {
#endif

/* Enumertaions for CRG */

/* Data Structures for CRG */

/** 
  @brief Transaction ID between MAC and RRC. */
typedef struct crgCfgTransId
{
   U8 trans[CRG_CFG_TRANSID_SIZE]; /*!< RRC transaction ID */
} CrgCfgTransId;

/** 
  @brief Bandwidth configuration per cell. */
typedef struct crgBwCfg
{
   U8 dlTotalBw;            /*!< Total Dowlink Bandwidth */
   U8 ulTotalBw;            /*!< Total Uplink Bandwidth  */
} CrgBwCfg;

/** 
  @brief RACH configuration per cell. */
typedef struct crgRachCfg
{
   U8  maxMsg3Tx;            /*!< Maximum number of message 3 transmissions */
} CrgRachCfg;

#ifdef LTE_ADV
/** @brief UE secondary cell config params to MAC*/
typedef struct crgUeSCellInfo
{
  U16                  sCellId;       /*!< This will be secondary cellId */
  Inst                 macInst;       /*!< MAC instance for SCell */
  SuId                 rguUlSapId;    /*!< MAC-RLC UL Sap ID */ 
  SuId                 rguDlSapId;    /*!< MAC-RLC DL SAP ID */
}CrgUeSCellInfo;


/** @brief Configuration information of Secondary cells for a UE*/
typedef struct crgUeSecCellInfo 
{
  Bool                 isSCellCfgPres; /*!<  Bool indicates whether configuration
                                   is present */
  U8                   numSCells;                        /*!< Number of SCells
                                                          */
  CrgUeSCellInfo       ueSCellCfg[CRG_MAX_SCELL_PER_UE]; /*!< Secondary cell 
                                                           configuration per UE */
}CrgUeSecCellInfo;

#endif /* LTE_ADV */

/** 
  @brief Cell configuration. */
typedef struct crgCellCfg
{
   CmLteCellId   cellId;       /*!< Cell ID */
   CrgRachCfg    rachCfg;      /*!< RACH Configuration */
   CrgBwCfg      bwCfg;        /*!< Bandwidth Configuration */
#ifdef TENB_MULT_CELL_SUPPRT
   SpId          rguUlSapId;   /*!< RLC UL SAP Id for common channels */
   SpId          rguDlSapId;   /*!< RLC DL SAP Id for common channels */
#endif
} CrgCellCfg;

/** 
  @brief Uplink HARQ configuration per UE. */
typedef struct crgUeUlHqCfg
{
   U8 maxUlHqTx;           /*!< Maximum number of UL HARQ transmissions */
} CrgUeUlHqCfg;

/* crg_x_001.main_3 - Changes for MIMO feature addition */
/* crg_x_001.main_4 - Changes for MIMO feature addition */
/** 
 * @enum UE Transmission Modes */
typedef enum crgTxMode
{
   CRG_UE_TM_1 = 1,    /** Transmission Mode 1 */
   CRG_UE_TM_2,        /** Transmission Mode 2 */
   CRG_UE_TM_3,        /** Transmission Mode 3 */
   CRG_UE_TM_4,        /** Transmission Mode 4 */
   CRG_UE_TM_5,        /** Transmission Mode 5 */
   CRG_UE_TM_6,        /** Transmission Mode 6 */
   CRG_UE_TM_7         /** Transmission Mode 7 */
} CrgTxMode;

/** 
  @brief UE Transmission mode configuration */
typedef struct crgTxModeCfg
{
   Bool      pres;  /*!< TRUE if Transmission mode is being CFG/RECFG ed */
   CrgTxMode tm;    /*!< Transmission mode */
}CrgTxModeCfg;
/** 
  @brief UE configuration. */
typedef struct crgUeCfg
{
   CmLteCellId    cellId;      /*!< Cell ID */
   CmLteRnti      crnti;       /*!< UE ID: CRNTI */ 
   CrgUeUlHqCfg   ueUlHqCfg;   /*!< UE related UL HARQ configuration */
   CrgTxModeCfg   txMode;      /*!< UE Transmission mode Cfg */
#ifdef TENB_MULT_CELL_SUPPRT
   SpId           rguUlSapId;   /*!< RLC UL SAP Id for common channels */
   SpId           rguDlSapId;   /*!< RLC DL SAP Id for common channels */
#endif
#if 0
#ifdef LTE_ADV
   CrgUeSecCellInfo crgSCellCfg;    /*!< Secondary cell dedicated informaton
                                             per UE */
#endif
#endif
} CrgUeCfg;

/** 
  @brief Logical channel configuration information for downlink logical channels. */
typedef struct crgDlLchCfg 
{
   U8             dlTrchType; /*!< Indicates type of DL transport channel:
                                   Validated only for BCCH at MAC. DL Transport
                                   channel type can take following values:<br>
                                   CM_LTE_TRCH_BCH<br> 
                                   CM_LTE_TRCH_PCH<br>
                                   CM_LTE_TRCH_DL_SCH  */
} CrgDlLchCfg;

/** 
  @brief Logical channel configuration information for uplink logical channels. */
typedef struct crgUlLchCfg
{
   U8             ulTrchType; /*!< Indicates type of UL transport channel:
                                   Validated only for BCCH at MAC. 
                                   UL Transport channel type can take following values:<br>
                                   CM_LTE_TRCH_RACH<br>
                                   CM_LTE_TRCH_UL_SCH */  
   U8             lcgId;      /*!< Logical channel group ID */
} CrgUlLchCfg;

/* crg_x_001.main_2: Documentation update */
/** 
  @brief Logical channel configuration information for common and dedicated channels. */
typedef struct crgLchCfg
{
   CmLteCellId   cellId;     /*!< Cell ID */
   CmLteRnti     crnti;      /*!< CRNTI for DTCH and DCCH */
   CmLteLcId     lcId;       /*!< Logical channel ID */
   CmLteLcType   lcType;     /*!< Identifies the Logical channel type. lcType can take the following values:<br>                                            
                                      CM_LTE_LCH_BCCH<br>
                                      CM_LTE_LCH_PCCH<br>
                                      CM_LTE_LCH_CCCH<br>
                                      CM_LTE_LCH_DCCH<br>
                                      CM_LTE_LCH_DTCH */  
                            
   U8            dir;        /*!< Indicates Direction. Direction can take following 
                                  values:<br>
                                  CRG_DIR_TX<br>
                                  CRG_DIR_RX<br>
                                  CRG_DIR_TX_RX */  

   CrgDlLchCfg   dlInfo;     /*!< Downlink logical channel configuration info */
   CrgUlLchCfg   ulInfo;     /*!< Uplink logical channel configuration info */
   /* crg_x_001.main_5 - ADD - Members corresponding to LTE_L2_MEAS */
#ifdef LTE_L2_MEAS
   U8 qci;                   /*!< QCI for the logical channel.
                                  Valid Range:[0-255] (Actual QCI - 1). */

#endif /* LTE_L2_MEAS */
} CrgLchCfg;

/** 
  @brief Basic configuration information for MAC. */
typedef struct crgCfg
{
   U8 cfgType;               /*!< Indicates configuration type */
   union crgCfgU  
   {
      CrgCellCfg  cellCfg;   /*!< Cell configuration */
      CrgUeCfg    ueCfg;     /*!< UE configuration */ 
      CrgLchCfg   lchCfg;    /*!< Logical channel configuration */
   } u;                      /*!< Union of Cell/UE/Lch configuration */
} CrgCfg;


/** 
  @brief Activation time information. */
typedef struct crgActvTime
{
   Bool            pres;      /*!< Indicates the presence of activation time */
   CmLteTimingInfo actvTime;  /*!< Activation time information */ 
} CrgActvTime;


/** 
  @brief Cell reconfiguration information. */
typedef struct crgCellRecfg
{
   CmLteCellId     cellId;         /*!< Cell ID */
   CrgRachCfg      rachRecfg;      /*!< RACH Configuration */
} CrgCellRecfg;

/** 
  @brief UE reconfiguration information. */
typedef struct crgUeRecfg
{
   CmLteCellId       cellId;          /*!< Cell ID */
   CmLteRnti         oldCrnti;        /*!< Old UE ID */
   CmLteRnti         newCrnti;        /*!< New UE ID: This value must match
                                        'oldCrnti',if no CRNTI change during
                                         reconfiguration */
   CrgUeUlHqCfg      ueUlHqRecfg;     /*!< UE UL HARQ information */
   CrgTxModeCfg      txMode;          /*!< UE Transmission mode ReCfg */
#ifdef LTE_ADV
   CrgUeSecCellInfo crgSCellCfg;    /*!< Secondary cell dedicated informaton
                                             per UE */
#endif
} CrgUeRecfg;

/** 
  @brief Logical channel reconfiguration information for dedicated channels only. */
typedef struct crgLchRecfg
{
   CmLteCellId cellId;       /*!< Cell ID */
   CmLteRnti   crnti;        /*!< CRNTI for DTCH and DCCH */
   CmLteLcId   lcId;         /*!< Logical channel ID */
   
   struct ulRecfgS 
   {
      U8             lcgId;  /*!< Logical channel group ID */
   } ulRecfg;                /*!< Uplink logical channel reconfiguration information */

} CrgLchRecfg;

/** 
  @brief Basic reconfiguration information for MAC. */
typedef struct crgRecfg
{
   U8 recfgType;                /*!< Indicates reconfiguration type */
   union crgRecfgU
   {
      CrgCellRecfg  cellRecfg;  /*!< Cell Reconfig information */
      CrgUeRecfg    ueRecfg;    /*!< UE Reconfig information */ 
      CrgLchRecfg   lchRecfg;   /*!< Logical channel reconfiguration information */
   } u;                         /*!< Union of Cell/UE/Lch reconfiguration information
                                  */
} CrgRecfg;

/** 
  @brief Basic Delete information for MAC. */
typedef struct crgDel
{
   U8 delType;               /*!< Indicates configuration item to be deleted */
   union crgDelU
   {
      struct cellDelS 
      {
         CmLteCellId cellId; /*!< Cell ID */
      } cellDel;             /*!< Cell Delete information */

      struct ueDelS 
      {
         CmLteCellId cellId; /*!< Cell ID */
         CmLteRnti   crnti;  /*!< UE ID: CRNTI */
      } ueDel;               /*!< UE Delete information */
      
      struct lchDelS
      {
         CmLteCellId cellId; /*!< Cell ID */
         CmLteRnti   crnti;  /*!< CRNTI for DTCH and DCCH */
         CmLteLcId   lcId;   /*!< Logical channel ID */
         U8          dir;    /*!< Indicates Direction. Direction can take following 
                                  values:<br>
                                  CRG_DIR_TX<br>
                                  CRG_DIR_RX<br>
                                  CRG_DIR_TX_RX */ 
      } lchDel;              /*!< Logical channel delete information */
   } u;                      /*!< Union of Cell/UE/Lch delete information */
} CrgDel;

/** 
  @brief UE RESET information for MAC. */
typedef struct crgRst
{
   CmLteCellId cellId; /*!< Cell ID */
   CmLteRnti   crnti;  /*!< UE ID: CRNTI tobe RESET */
} CrgRst;
/** 
  @brief Config/Reconfig/Delete information for MAC. */
typedef struct crgCfgReqInfo 
{
   U8  action;               /*!< Determines cfg/recfg/del/reset */
   union cfgReqInfoU
   {
      CrgCfg   cfgInfo;      /*!< Configuration related infomation */
      CrgRecfg recfgInfo;    /*!< Reconfiguration related information */
      CrgDel   delInfo;      /*!< Deletion related information */
      CrgRst   rstInfo;      /*!< Reset related information */
   } u;                      /*!< Union of config/re-config/delete information */
} CrgCfgReqInfo;

/* 
   Function Prototypes 
 */
/** @brief Request from RRC to MAC to bind the interface SAPs. */
typedef S16 (*CrgBndReq) ARGS((
   Pst*                 pst,
   SuId                 suId,
   SpId                 spId));
/** @brief Confirmation from MAC to RRC for the bind/unbind 
 * request for the interface SAPs. */
typedef S16 (*CrgBndCfm) ARGS((
   Pst*                 pst,
   SuId                 suId,
   U8                   status));
/** @brief Request from RRC to MAC to unbind the interface SAPs. */
typedef S16 (*CrgUbndReq) ARGS((
   Pst*                 pst,
   SpId                 spId,
   Reason               reason));
/** @brief Configuration Request from RRC to MAC for 
 * configuring Cell/Ue/Lch. */
typedef S16 (*CrgCfgReq) ARGS((
   Pst*                 pst,
   SpId                 spId,
   CrgCfgTransId        transId,
   CrgCfgReqInfo  *     cfgReqInfo));
/** @brief Configuration Confirm from MAC to RRC. */
typedef S16 (*CrgCfgCfm) ARGS((
   Pst*                 pst,
   SuId                 suId,
   CrgCfgTransId        transId,
   U8                   status));

/** @brief Request from RRC to MAC to bind the interface SAPs. */
EXTERN S16 RgUiCrgBndReq ARGS((
   Pst*                 pst,
   SuId                 suId,
   SpId                 spId
));
/** @brief Confirmation from MAC to RRC for the bind/unbind 
 * request for the interface SAPs. */
EXTERN S16 RgUiCrgBndCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   U8                   status
));
/** @brief Request from RRC to MAC to Unbind the interface SAPs. */
EXTERN S16 RgUiCrgUbndReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   Reason               reason
));
/** @brief Configuration Request from RRC to MAC for 
 * configuring Cell/Ue/Lch. */
EXTERN S16 RgUiCrgCfgReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   CrgCfgTransId        transId,
   CrgCfgReqInfo  *     cfgReqInfo
));
/** @brief Configuration Confirm from MAC to RRC. */
EXTERN S16 RgUiCrgCfgCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   CrgCfgTransId        transId,
   U8                   status
));

#ifdef NH
/** @brief Request from RRC to MAC to bind the interface SAPs. */
EXTERN S16 NhLiCrgBndReq ARGS((
   Pst*                 pst,
   SuId                 suId,
   SpId                 spId
));
/** @brief Confirmation from MAC to RRC for the bind/unbind 
 * request for the interface SAPs. */
EXTERN S16 NhLiCrgBndCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   U8                   status
));
/** @brief Request from RRC to MAC to Unbind the interface SAPs. */
EXTERN S16 NhLiCrgUbndReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   Reason               reason
));
/** @brief Configuration Request from RRC to MAC for 
 * configuring Cell/Ue/Lch. */
EXTERN S16 NhLiCrgCfgReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   CrgCfgTransId        transId,
   CrgCfgReqInfo  *     cfgReqInfo
));
/** @brief Configuration Confirm from MAC to RRC. */
EXTERN S16 NhLiCrgCfgCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   CrgCfgTransId        transId,
   U8                   status
));
#endif

#ifdef LCCRG
/** @brief Request from RRC to MAC to bind the interface SAPs. */
EXTERN S16 cmPkCrgBndReq ARGS((
   Pst*                 pst,
   SuId                 suId,
   SpId                 spId
));
/** @brief Request from RRC to MAC to bind the interface SAPs. */
EXTERN S16 cmUnpkCrgBndReq ARGS((
   CrgBndReq            func,
   Pst*                 pst,
   Buffer               *mBuf
));
/** @brief Confirmation from MAC to RRC for the bind/unbind 
 * request for the interface SAPs. */
EXTERN S16 cmPkCrgBndCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   U8                   status
));
/** @brief Confirmation from MAC to RRC for the bind/unbind 
 * request for the interface SAPs. */
EXTERN S16 cmUnpkCrgBndCfm ARGS((
   CrgBndCfm            func,
   Pst*                 pst,
   Buffer               *mBuf
));
/** @brief Request from RRC to MAC to unbind the interface SAPs. */
EXTERN S16 cmPkCrgUbndReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   Reason               reason
));
/** @brief Request from RRC to MAC to unbind the interface SAPs. */
EXTERN S16 cmUnpkCrgUbndReq ARGS((
   CrgUbndReq           func,
   Pst*                 pst,
   Buffer               *mBuf
));
/** @brief Configuration Request from RRC to MAC for 
 * configuring Cell/Ue/Lch. */
EXTERN S16 cmPkCrgCfgReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   CrgCfgTransId        transId,
   CrgCfgReqInfo  *     cfgReqInfo
));
/** @brief Configuration Request from RRC to MAC for 
 * configuring Cell/Ue/Lch. */
EXTERN S16 cmUnpkCrgCfgReq ARGS((
   CrgCfgReq            func,
   Pst*                 pst,
   Buffer               *mBuf
));
/** @brief Configuration Confirm from MAC to RRC. */
EXTERN S16 cmPkCrgCfgCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   CrgCfgTransId        transId,
   U8                   status
));
/** @brief Configuration Confirm from MAC to RRC. */
EXTERN S16 cmUnpkCrgCfgCfm ARGS((
   CrgCfgCfm            func,
   Pst*                 pst,
   Buffer               *mBuf
));
EXTERN S16 cmPkCrgCfgTransId ARGS((
   CrgCfgTransId        *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCrgCfgTransId ARGS((
   CrgCfgTransId        *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCrgBwCfg ARGS((
   CrgBwCfg             *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCrgBwCfg ARGS((
   CrgBwCfg             *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCrgRachCfg ARGS((
   CrgRachCfg           *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCrgRachCfg ARGS((
   CrgRachCfg           *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCrgCellCfg ARGS((
   CrgCellCfg           *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCrgCellCfg ARGS((
   CrgCellCfg           *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCrgUeUlHqCfg ARGS((
   CrgUeUlHqCfg         *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCrgUeUlHqCfg ARGS((
   CrgUeUlHqCfg         *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCrgUeCfg ARGS((
   CrgUeCfg             *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCrgUeCfg ARGS((
   CrgUeCfg             *param,
   Buffer               *mBuf
));

#ifdef LTE_ADV
EXTERN S16 cmPkCrgUeSecCellInfo ARGS((
CrgUeSecCellInfo *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkCrgUeSecCellInfo ARGS((
CrgUeSecCellInfo *param,
Buffer *mBuf
));
#endif /* LTE_ADV */

EXTERN S16 cmPkCrgDlLchCfg ARGS((
   CrgDlLchCfg          *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCrgDlLchCfg ARGS((
   CrgDlLchCfg          *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCrgUlLchCfg ARGS((
   CrgUlLchCfg          *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCrgUlLchCfg ARGS((
   CrgUlLchCfg          *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCrgLchCfg ARGS((
   CrgLchCfg            *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCrgLchCfg ARGS((
   CrgLchCfg            *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCrgCfg ARGS((
   CrgCfg               *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCrgCfg ARGS((
   CrgCfg               *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCrgActvTime ARGS((
   CrgActvTime          *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCrgActvTime ARGS((
   CrgActvTime          *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCrgCellRecfg ARGS((
   CrgCellRecfg         *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCrgCellRecfg ARGS((
   CrgCellRecfg         *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCrgUeRecfg ARGS((
   CrgUeRecfg           *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCrgUeRecfg ARGS((
   CrgUeRecfg           *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCrgLchRecfg ARGS((
   CrgLchRecfg          *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCrgLchRecfg ARGS((
   CrgLchRecfg          *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCrgRecfg ARGS((
   CrgRecfg             *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCrgRecfg ARGS((
   CrgRecfg             *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCrgDel ARGS((
   CrgDel               *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCrgDel ARGS((
   CrgDel               *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCrgRst ARGS((
   CrgRst               *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCrgRst ARGS((
   CrgRst               *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCrgCfgReqInfo ARGS((
   CrgCfgReqInfo        *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCrgCfgReqInfo ARGS((
   CrgCfgReqInfo        *param,
   Buffer               *mBuf
));
#endif

#ifdef DM
/** @brief Request from RRC to MAC to bind the interface SAPs. */
EXTERN S16 DmUiCrgBndReq ARGS((
   Pst*                 pst,
   SuId                 suId,
   SpId                 spId
));
/** @brief Confirmation from MAC to RRC for the bind/unbind 
 * request for the interface SAPs. */
EXTERN S16 DmUiCrgBndCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   U8                   status
));
/** @brief Request from RRC to MAC to unbind the interface SAPs. */
EXTERN S16 DmUiCrgUbndReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   Reason               reason
));
/** @brief Configuration Request from RRC to MAC for 
 * configuring Cell/Ue/Lch. */
EXTERN S16 DmUiCrgCfgReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   CrgCfgTransId        transId,
   CrgCfgReqInfo  *     cfgReqInfo
));
/** @brief Configuration Confirm from MAC to RRC. */
EXTERN S16 DmUiCrgCfgCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   CrgCfgTransId        transId,
   U8                   status
));
#endif

#ifdef __cplusplus
}
#endif
#endif /* __CRG_X__ */

/**********************************************************************
  
         End of file:     crg.x@@/main/6 - Wed Jul 27 12:44:19 2011
  
**********************************************************************/

/**********************************************************************
  
        Notes:
  
**********************************************************************/

/**********************************************************************
Put notes here
**********************************************************************/


/**********************************************************************
  
        Revision history:
  
**********************************************************************/
  
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---   sdass 1. initial release.
/main/3      --- crg_x_001.main_2   sm 1. Documentation update
/main/4      --- crg_x_001.main_3   gvj 1. Added Support for MIMO
/main/5      --- crg_x_001.main_4   rsharon   1. Removed dependency on MIMO flag.
/main/6      --- crg_x_001.main_5   gvj             1. Updated for LTE MAC Rel 3.1
*********************************************************************91*/
