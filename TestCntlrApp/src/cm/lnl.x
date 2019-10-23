

/********************************************************************20**

     Name:     ESON application

     Type:     

     Desc:     This file contains the 
               

     File:     lnl.x

     Sid:      lnl.x@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 15:08:07 2014

     Prg:      subhamay 

*********************************************************************21*/
#ifndef LNL_X_
#define LNL_X_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @breif
   This structure contains the SON module memory pool and region info */
typedef struct nlMemMngr
{
   U32   nlPool;
   U32   nlRegion;
}NlMemMngr;

typedef enum nlPciSelType
{
   NL_PCI_SEL_DISABLE,
   NL_PCI_SEL_DSON,
   NL_PCI_SEL_CSON
}NlPciSelType;

typedef enum nlPrachSelType
{
   NL_PRACH_SEL_DISABLE,
   NL_PRACH_SEL_DSON,
   NL_PRACH_SEL_CSON
}NlPrachSelType;

typedef enum nlEarfcnSelType
{
   NL_EARFCN_SEL_DISABLE,
   NL_EARFCN_SEL_DSON,
   NL_EARFCN_SEL_CSON
}NlEarfcnSelType;

typedef enum nlTxPowerSelType
{
   NL_TXPOWER_SEL_DISABLE,
   NL_TXPOWER_SEL_DSON,
   NL_TXPOWER_SEL_CSON
}NlTxPowerSelType;

/** 
 * @brief
   This structure holds configuration parameters for SON General Configuration. */
typedef struct nlGenCfg
{
   Pst                lmPst;              /*!< Layer manager post structure */
   MemoryId           mem;                /*!< Region and pool ID */
   U8                 tmrRes;             /*!< Timer resolution for Low SAP Bind Timer */
   U8                 maxNluSaps;         /*!< Maximum number of NL Upper SAP's */
   NlPciSelType       pciSelType;         /*!< whether PCI conflict/confusion detection enabled or not*/
   NlPrachSelType     prachSelType;       /*!< whether Prach config enabled or not*/
   NlEarfcnSelType    earfcnSelType;      /*!< whether earfcn config enabled or not*/
   NlTxPowerSelType   txPowerSelType;     /*!< whether txPower config enabled or not*/
   U32                maxUeSupp;          /*!< maximum number of UE supported by eNodeB*/
   U32                maxUePerTti;        /*!< maximum number of UE can be scheduled per TTI*/
}NlGenCfg;

/** 
 * @brief
   This structure holds configuration parameters for SON Upper SAP Configuration. */
typedef struct nlUSapCfg
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
}NlUSapCfg;

/** @brief
    This Structure contains the PLMN information*/
typedef struct lnlPlmnId
{
   U8      numMncDigits;       /*!< number of MNC digit, either 2 or 3 */
   U8      mcc[3];             /*!< MCC value */
   U8      mnc[3];             /*!< MNC value */
}LnlPlmnId;

/** @brief
    This Structure contains the ECGI information*/
typedef struct lnlEcgi
{
   LnlPlmnId   plmn;            /*!< PLMN Id details */
   U32         cellId;          /*!< cell Id */
}LnlEcgi;

/** 
 * @brief
   This structure holds configuration parameters for SON. */
typedef struct nlCfg
{
   union
   {
      NlGenCfg       genCfg;    /*!< General Configuration */
      /* SAPs for the ESON layer */
      NlUSapCfg      nluSap;    /*!< NLU interface SAP ENB Application */
   }u;
}NlCfg;

/** 
 * @brief
   This structure holds SON's Control information. */
typedef struct nlCntrl
{
   U8   action;   
}NlCntrl;

typedef enum lnlCfgType
{
   LNL_CELL_CFG,        /*!< Cell configuration in SON module*/
   LNL_NGH_CELL_CFG,    /*!< Neighbor cell configuration*/
   LNL_CELL_RECFG       /*!< cell reconfiguration*/
}LnlCfgType;

/** 
   * Ng values for PHICH For more details refer to 36.211 Sec 6.9*/
typedef enum lnlPhichNg
{
   LNL_NG_ONESIXTH, /**< PHICH Ng Values 1/6 */
   LNL_NG_HALF,     /**< PHICH Ng Values 1/2 */
   LNL_NG_ONE,      /**< PHICH Ng Values 1 */
   LNL_NG_TWO       /**< PHICH Ng Values 2 */
}LnlPhichNg;

typedef struct lnlNghPrachCfg
{
   U16       nghRootSeqIdx;
   U8        nghPrachCfgIdx;
   U8        nghZeroCorrelationZoneCfg;
   U8        nghPrachFreqOffset;
   Bool      highSpeedFlag;
}LnlNghPrachCfg;

typedef struct lnlPrachCfg
{
   U16       servRootSeqIdx;
   U8        servPrachCfgIdx;
   U8        servZeroCorrelationZoneCfg;
   U8        servPrachFreqOffset;
   Bool      highSpeedFlag;

   U8        numRootSeqIndex;
   U16       rootSeqIdx[LNL_MAX_ROOTSEQ_INDX];
   U8        numPrachCfgIdx;
   U8        prachConfigIdx[LNL_MAX_PRACH_CFG_IDX];
   U8        numZeroCorrCfgZone;
   U8        zeroCorrelationZoneCfg[LNL_MAX_ZERO_CORR_CFG_ZONE];
   U8        numFreqOffset;
   U8        freqOffset[LNL_MAX_NUM_FREQ_OFFSET];
}LnlPrachCfg;


typedef struct lnlRemScanEarfcn
{
   U32       dlEarfcn;
   S32       rssi;
}LnlRemScanEarfcn;


/** 
 * @brief
   This structure holds PUCCH configuration for Serving Cell. Its used for
   Prach Freq-Offset calculation. */
typedef struct lnlPucchCfg
{
   U8          pucchCqiResIdx;             /*!< N2-PUCCH */
   U16         n1PucchAn;                  /*!< N1-PUCCH */
   U8          deltaShift;                 /*!< Delta Shift for PUCCH: a value
                                             in set {1,2,3} */ 
   U8          cyclicShift;                /*!< Cyclic Shift for PUCCH (
                                             N^(1)_CS): range [0-7] */
}LnlPucchCfg;


/** 
 * @brief
   This structure is used to inform Tx Power configuration for Serving Cell 
   from SM to SON. */
typedef struct lnlTxPwrCfg
{
   U8	    refSignalPwrCnt;                           /*!< Number Parameters to be configured for Reference signal power */
   S8       referenceSignalPwr[LNL_MAX_RS_TXPWR_CNT];  /*!< Array of Reference signal power {-60..50} */
   U8	    pBCnt;			               /*!< Num Parameters to be configured for pB */
   U8       pB[LNL_MAX_PB_CNT];                        /*!< Array of p-b values */
   U8	    pACnt;		           	       /*!< Num Parameters to be configured for pA */
   U8       pA[LNL_MAX_PA_CNT];                        /*!< Array of p-a values */ 
   U8	    pschPowerOffCnt;                           /*!< Number of PschPowerOffset count */
   U8	    sschPowerOffCnt;                           /*!< Number of sschPowerOffset count */
   U8	    pbchPowerOffCnt;                           /*!< Number of PbchPowerOffset count */
   S8       pschPowerOffset[LNL_MAX_POWER_OFFSET_CNT]; /*!< power offset of PSCH w.r.t ReferenceSignalPower */ 
   S8       sschPowerOffset[LNL_MAX_POWER_OFFSET_CNT]; /*!< power offset of SSCH w.r.t ReferenceSignalPower */
   S8       pbchPowerOffset[LNL_MAX_POWER_OFFSET_CNT]; /*!< power offset of PBCH w.r.t ReferenceSignalPower */
}LnlTxPwrCfg;

/** 
 * @brief
   This structure is used to configure the Rsys TPM module 
   from SM to SON. */
typedef struct lnlTpmCfg
{
   S8       tgtRsrp;      /*!< Target RSRP of the Cell */
   U8       attnConstIdx;      /*!< Index of Attenuation factor [0 - 5]*/ 
   S8       minRsrp;       /*!< Min Rsrp value */
   S8       maxRsrp;       /*!< Max Rsrp value */
}LnlTpmCfg;


/** 
 * @brief
   This structure holds PHICH configuration for Serving Cell. Its used for
   Prach Freq-Offset calculation. */
typedef struct lnlPhichCfg
{
   LnlPhichNg    ngEnum;        /*!< Ng value for PHICH */
   Bool          isDurExtend;   /*!< PHICH Duration:
                                  TRUE-extended/FALSE-normal */
}LnlPhichCfg;

typedef enum lnlCsgAccessMode
{
   LNL_ENB_OPEN_ACCESS = 1,
   LNL_ENB_CLOSED_ACCESS,
   LNL_ENB_HYBRID_ACCESS
}LnlCsgAccessMode;

typedef struct lnlCsgPciCfg
{
   Bool                isCsgPciCfg;
   U16                 csgStartPci;
   U16                 csgPciRange;
   LnlCsgAccessMode    accessMode;
}LnlCsgPciCfg;

typedef struct lnlSmallCellPciCfg
{
   Bool  isSmallCellPciCfg;
   U16   smallCellStartPci;
   U16   maxSmallCellPci;
}LnlSmallCellPciCfg;


typedef struct lnlCellCfg
{
   U32                cellId;                           /*!< cell Identity*/
   U8                 bandWidth;                        /*!< Bandwidth */
   U8                 numTxAntPorts;                    /*!< Num Antenna ports */
   U32                txPower;                          /*!< eNodeB Transmission power */
   U8                 subFrameCfg;                      /*!< Sub-frame config */
   U8                 duplexMode;                       /*!< TDD or FDD */
   U16                pci;                              /*!< PCI value */
   U32                numPci;                           /*!< number of PCI present in PCI List*/
   U16                pciList[LNL_MAX_PCI_CFG];         /*!< List of alternative PCI*/
   LnlCsgPciCfg       csgPciCfg;                        /*!< PCI list configuration related to CSG*/
   LnlSmallCellPciCfg smallCellPciCfg;                  /*!< small cell PCI Cfg */
   LnlEcgi            ecgi;                             /*!< ECGI*/
   U8                 numDlEarfcn;                      /*!< number of DL Earfcn COnfigured*/
   U16                dlEarfcnList[LNL_MAX_NUM_EARFCN]; /*!< DL-EARFCN number */
   U8                 numUlEarfcn;                      /*!< number of UL Earfcn*/
   U16                ulEarfcnList[LNL_MAX_NUM_EARFCN]; /*!< UL-EARFCN number */
   U8                 numRemScanEarfcn;                 /*!< REM scaned number of EARFCN*/
   LnlRemScanEarfcn   remScanEarfcn[LNL_MAX_NUM_EARFCN];/*!< REM scaned EARFCN*/
   Bool               isCpUlExtend;       /*!< Cyclic prefix :
                                            TRUE-extended/FALSE-normal */
   LnlPrachCfg        prachCfgInfo;       /*!< Lists for Prach Configuration
                                            from which to choose the Prach
                                            Configuration */
   LnlPucchCfg        pucchResCfg;        /*!< Pucch Resource Configuration
                                            for serving cell */
   LnlPhichCfg        phichCfg;           /*!< PHICH Configuration for serving
                                            cell */
   LnlTxPwrCfg	       txPwrCfg;		  /*!< Tx Power Configurartion for serving cell */
   LnlTpmCfg	       tpmCfg;		     /*!< Rsys TPM Configurartion */
}LnlCellCfg;

typedef struct lnlCellReCfg
{
   U32         cellId;            /*!< cell Identity*/
   LnlEcgi     ecgi;              /*!< serving cell ECGI*/
   U32         numPci;            /*!< number of PCI present in PCI List*/
   U16         pciList[LNL_MAX_PCI_CFG];  /*!< List of alternative PCI*/
}LnlCellReCfg;

typedef struct lnlNghCellInfo
{
   LnlEcgi         ecgi;           /*!< neighbor ECGI*/
   U16             pci;            /*!< neighbor physical cell Id*/
   U16             dlEarfcn;       /*!< downlink frequency*/
   U16             ulEarfcn;       /*!< uplink frequency*/
   U16		   lteBand;	   /*!< Band of the LTE cell */
   U16             tac;		   /*!< Tracking Area Code */
   U8              ulBw; 	   /*!< UL Bandwidth of the neighbor 0=6,1=15,2=25,3=50,4=75,5=100 */
   U8              dlBw; 	   /*!< DL Bandwidth of the neighbor 0=6,1=15,2=25,3=50,4=75,5=100 */
   S8              RSTxPower;      /*!< The downlink reference-signal transmit power*/
   U8              csgAccessMode;  /*!< Indicates the type of access mode the FAP operates in */
   U32             csgId;          /*!< Identity of the Closed Subscriber Group the cell belongs to. */
   S16             rsrp; 	   /*!< RSRP in the range of -128 to 0 */
   S16             rssi; 	   /*!< RSSI in the range of 0 to 256 */
   Bool		   isCellBarred;   /*!< Indicates if cell is barred or not */
   Bool            isNghPrachInfo; /*!< Indicates if Prach Info configuration is present */
   LnlNghPrachCfg  prachCfgInfo;   /*!< Prach Configuration */
}LnlNghCellInfo;

typedef struct lnlNghCellModInfo
{
   LnlEcgi          oldEcgi;
   LnlNghCellInfo   nghCellInfo;
   U8               numNghNgh;
   LnlNghCellInfo   nghNghCellInfo[LNL_MAX_NGH_NGH_CELL_INFO];
}LnlNghCellModInfo;

typedef struct lnlNghCellMod
{
   U8                  numNgh;
   LnlNghCellModInfo   nghCellModInfo[LNL_MAX_NGH_CELL_INFO];

}LnlNghCellMod;

typedef struct lnlNghCellDel
{
   U8                numNgh;
   LnlEcgi           ecgi[LNL_MAX_NGH_CELL_INFO];
}LnlNghCellDel;

typedef struct lnlNghCellAddInfo
{
   LnlNghCellInfo   nghCellInfo;
   U8               numNghNgh;
   LnlNghCellInfo   nghNghCellInfo[LNL_MAX_NGH_NGH_CELL_INFO];
}LnlNghCellAddInfo;

typedef struct lnlNghCellAdd
{
   U8                    numNgh;
   LnlNghCellAddInfo     nghCellAddInfo[LNL_MAX_NGH_CELL_INFO];
}LnlNghCellAdd;

typedef enum lnlNghCfgType
{
   LNL_NGH_ADD,
   LNL_NGH_DEL,
   LNL_NGH_MOD
}LnlNghCfgType;

typedef struct lnlNghCellCfgParam
{
   LnlNghCfgType      cfgType;
   union 
   {
      LnlNghCellAdd   nghCellAdd;
      LnlNghCellDel   nghCellDel;
      LnlNghCellMod   nghCellMod;
   }u;
}LnlNghCellCfgParam;

typedef struct lnlNghEnbCellCfg
{
   U32                nghEnbId;
   LnlNghCellCfgParam nghCellParam;
}LnlNghEnbCellCfg;

typedef struct lnlNghCellCfg
{
   U32                servCellId;
   U8                 numNghEnb;
   LnlNghEnbCellCfg   nghEnbCellCfg[LNL_MAX_NGH_ENB_CFG];
}LnlNghCellCfg;

typedef struct nlProtoCfg
{
   LnlCfgType   bCfgType;
   union
   {
      LnlCellCfg     cellCfg;     /*!< serving cell config information*/
      LnlNghCellCfg  nghCellCfg;  /*!< neighbor cell config information*/
      LnlCellReCfg   cellReCfg;   /*!< serving cell reconfiguration information*/ 
   }u;
}NlProtoCfg;

typedef enum lnlDgnType
{
   LNL_PCI_CONFLICT,
   LNL_PCI_CONFUSION

}LnlDgnType;

typedef enum lnlDgnSeverity
{
   LNL_ALARM_SEVERITY_CLEARED,
   LNL_ALARM_SEVERITY_WARNING,
   LNL_ALARM_SEVERITY_MINOR,
   LNL_ALARM_SEVERITY_MAJOR,
   LNL_ALARM_SEVERITY_CRITICAL

}LnlDgnSeverity;

typedef enum lnlDgnAlarm
{
   LNL_ALARM_PCI_CONFLICT,
   LNL_ALARM_PCI_CONFUSION
}LnlDgnAlarm;

typedef enum lnlAddInfoAction
{
   LNL_ALARM_MANUAL_INTER_REQ,
   LNL_ALARM_AUTO_RESOLVE
}LnlAddInfoAction;

typedef struct lnlDgnAddInfo
{
   U16                pci;
   U32                cellId;
   LnlAddInfoAction   action;
}LnlDgnAddInfo;

typedef struct lnlUstaDgn
{
   LnlDgnType      type;
   LnlDgnAlarm     alarmId;
   LnlDgnSeverity  severity;     
   U8              causeType;
   U8              causeVal;
   union
   {
      LnlDgnAddInfo   addInfo;
   }u;
}LnlUstaDgn;

/**
 * @brief
   This structure holds SON alarm information. */
typedef struct lnlNlUsta
{
   CmAlarm      alarm;
   LnlUstaDgn   dgn;   /*!< Diagnostic */
}LnlNlUsta;

/** @enum LnlEnbStaType
 *
 * Indicates the ENB Status indication type. Only either CPU Load or Cell UP status
 * can be indicated to SON in a status indication message.
 *
 */
typedef enum lnlEnbStaType
{
   LNL_ENBSTATYPE_CELLUP,
   LNL_ENBSTATYPE_CPULOAD
}LnlEnbStaType;

/** @brief This structure contains the eNodeB status indication parameters.
 *
 * - LnlEnbStaType staType:      eNodeB status indication type. i.e cpu load
 *                               indication or cell up indication.
 * - U32 cpuLoad:                CPU load of eNodeB
 * - U32 cellId :                Cell Id
 */
typedef struct lnlEnbStaInd
{
   LnlEnbStaType              enStaType;
   union {
      U32                      cpuLoad;
      U32                      cellId;
   }u;
}LnlEnbStaInd;

typedef enum lnlStaType
{
   LNL_STAT_ENB,
   LNL_STAT_ALARM
}LnlStaType;

/** 
 * @brief
 * This structure holds the types of alarm as well as eNodeB status*/

typedef struct nlUsta
{
   LnlStaType  staType;
   union {
      LnlEnbStaInd     stEnbStaInfo;
      LnlNlUsta        stAlarm;
   }u;
}NlUsta;

/** 
 * @brief
 * This structure holds the SON Configuration and Control Management Information. 
 * This structure will be used to sending and receiving messages in between stack
 * manager and SON */
typedef struct nlMngmt
{
   Header     hdr;          /*!< Header */
   CmStatus   cfm;          /*!< Confirmation */
   union
   {
      NlCfg       cfg;       /*!< Configuration */
      NlCntrl     cntrl;     /*!< Control */
      NlProtoCfg  protoCfg;  /*!< Protocol configuration*/
      NlUsta      usta;      /*!< Unsolicited status */ 
   }u;
}NlMngmt;

/**
 * @brief
 * This structure holds the PCI update by SON module.
 * This structure will be used to sending the updated PCI from SON module to stack
 * manager*/

typedef struct nlUpdatePciCfgInd
{
   U16   pci;                /*!< PCI updated by SON module*/
   U32   cellId;             /*!< Serving cell Id*/
   U32   cellCfgIdx;         /*!< Cell Cfg Idx determining the cell*/
}NlUpdatePciCfgInd;

/**
 * @brief
 * This structure holds the EARFCN update by SON module.
 * This structure will be used to sending the updated EARFCN from SON module to stack
 * manager*/

typedef struct nlUpdateEarfcnCfgInd
{
   U16   dlEarfcn;           /*!< downlink EARFCN*/
   U16   ulEarfcn;           /*!< uplink EARFCN*/
   U32   cellCfgIdx;         /*!< Cell Cfg Idx determining the cell*/
}NlUpdateEarfcnCfgInd;

typedef enum lnlCfgUpdateTye
{
   LNL_CFG_UPDATE_PCI = 1,
   LNL_CFG_UPDATE_EARFCN,
   LNL_CFG_UPDATE_PRACH,
   LNL_CFG_UPDATE_TXPWR
}LnlCfgUpdateType;


/**
 * @brief
 * This structure holds the PRACH Configuration update by SON module.
 * This structure will be used to sending the updated prach configuration from SON module to stack
 * manager*/

typedef struct nlUpdatePrachCfgInd
{
   U16   rootSequenceIndx;       /*!< ROOT sequence for preambles */
   U8    prachCfgIdx;            /*!< PRACH config index determines format and RA
                                      occassions */
   Bool  highSpeedFlag;          /*!< High Speed Flag */
   U8    zeroCorrelationZoneCfg; /*!< Zero Correlation zone */  
   U8    prachFreqOffset;        /*!< PRACH frequency offset */   
   U32   cellCfgIdx;         /*!< Cell Cfg Idx determining the cell*/
}NlUpdatePrachCfgInd;


/**
 * @brief
 * This structure holds the Tx Power Configuration update by SON module.
 * This structure will be used to sending the updated Tx Power Information from SON module to stack
 * manager*/
typedef struct nlUpdateTxPwrCfgInd
{
   S8	    refSignalTxPwr;        /*!< Selected Reference signal Tx Power */
   S16	    pssPowerOffset;        /*!< PSS Power offset value */
   S16	    sssPowerOffset;        /*!< PSS Power offset value */
   S16	    pbchPowerOffset;       /*!< PBCH Power offset value */
   U8       pB;                     /*!< p-b value */
   S8       pout;                  /*!< Pout. Max Tx Power */
   U32   cellCfgIdx;         /*!< Cell Cfg Idx determining the cell*/
}NlUpdateTxPwrCfgInd;


typedef struct nlCfgUpdateInd
{
   LnlEcgi            ecgi;
   LnlCfgUpdateType   cfgType;
   union
   {
      NlUpdatePciCfgInd     pciCfgInd;
      NlUpdateEarfcnCfgInd  earfcnCfgInd;
      NlUpdatePrachCfgInd   prachCfgInd;
      NlUpdateTxPwrCfgInd   txPwrCfgInd;
   }u;
}NlCfgUpdateInd;

/**
 * @brief
 * This enum contains whether SON configures measuremnt interval or scheduler
 * */
typedef enum lnlSonCfgType
{
   LNL_SON_PERD_UE_MEAS_INTERVAL_CFG,
   LNL_SON_SCHD_CFG,
   LNL_SON_PERD_REM_SCAN_CFG
}LnlSonCfgType;

/**
 * @brief
 * This structure contains the SON configured UE measurement reporting interval. 
 * */
typedef struct lnlSonMeasRptIntervalCfg
{
   U16   periodicUeMeasInterval;    /*!< SON configured periodic 
                                     measurement reporting interval */
}LnlSonMeasRptIntervalCfg;

/**
 * @brief
 * This structure contains the SON configured Periodical Scan Information. 
 * */
typedef struct lnlSonPerdREMScanCfg
{
   U16   perdREMScanInterval; /*!< SON configured periodic REM Scan Interval */ 
   U16   perdREMScanCount;    /*!< SON configured periodic REM Scan Count */
}LnlSonPerdREMScanCfg;

/**
 * @brief
 * This enum contains SON configured PA enum value for PRB
 * */
typedef enum lnlSonPrbPaLevel
{
   LNL_SON_CFG_PA_LEVEL_NORMAL,
   LNL_SON_CFG_PA_LEVEL_LOW,
   LNL_SON_CFG_PA_LEVEL_HIGH
}LnlSonPrbPaLevel;
/**
 * @brief
 * This enum contains SON configured PA enum values
 * */
typedef enum lnlSonPa
{
   LNL_SON_CFG_PA_DB_NEG_6 ,
   LNL_SON_CFG_PA_DB_NEG_4_77,
   LNL_SON_CFG_PA_DB_NEG_3 ,
   LNL_SON_CFG_PA_DB_NEG_1_77 ,
   LNL_SON_CFG_PA_DB_0 ,
   LNL_SON_CFG_PA_DB_1 ,
   LNL_SON_CFG_PA_DB_2 ,
   LNL_SON_CFG_PA_DB_3 ,
   LNL_SON_CFG_PA_NEGTIVE_INF 
}LnlSonPa;

/**
 * @brief
 * This structure contains the SON configured UE information, 
 * wheter the UE is cell edge or non cell edge 
 */

typedef struct lnlSonUeCfg
{
   U16            crnti;        /*!< CRNTI value of the UE*/
   Bool           isCellEdge;   /*!< Indicate whether the UE is cell edge 
         or non cell edge, 0- means non cell edge and 1-means cell edge*/
}LnlSonUeCfg;

/**
 * @brief
 * This structure contains the SON configured scheduler 
 * related configuration. SON configures PRB configuration and 
 * cell edge and non cell edge UE PA values
 * */
typedef struct lnlSonSchdCfg
{
   U8                           numUeCfg;   /*!< number of active UE configured by SON*/
   LnlSonUeCfg                  ueCfg[LNL_SON_CFG_MAX_UE];   /*!< cell edge or non cell edge 
                                                           UE configuration from SON*/
   LnlSonPrbPaLevel             paLevelPerPrb[LNL_MAX_PRB_CNT]; /*!< PA level for each PRB*/
   LnlSonPa                     pa;   /*!< Pa value used to calculate PDSCH power for reuse 1 region*/
   LnlSonPa                     paLow;   /*!< Pa value used to calculate PDSCH 
                                            power for low power in the FFR region*/
   LnlSonPa                     paHigh;   /*!< Pa value used to calculate PDSCH power 
                                             for high power in the FFR region*/
   U8                           pb;   /*!< PDSCH Pb values*/
}LnlSonSchdCfg;

/**
 * @brief
 * This structure contains the SON configuration for scheduler
 * and UE measurement reporting interval.
 * */
typedef struct lnlSonCfg
{
   LnlEcgi             ecgi;   /*!< unique identity of eNodeB*/
   LnlSonCfgType       cfgType;   /*!< SON configuration type, 
   whether UE measurent reporting interval or scheduler configuration*/   
   union
   {
      LnlSonMeasRptIntervalCfg    measCfg;   /*!< measurement interval for how frequently 
                                                  UE reports measurement report to eNodeB */
      LnlSonSchdCfg               schdCfg;   /*!< scheduler related configuration from SON*/
      LnlSonPerdREMScanCfg        remScanCfg;  /*!< periodical REM Scan configuration from SON*/
   }u;
}LnlSonCfg;

EXTERN NlMemMngr nlMemMngr;


/* 
   Function Prototype Typedefs 
. */
typedef S16 (*LnlCfgReq)            ARGS((
        Pst        *pst,               /* Post Structure */
        NlMngmt    *cfg                /* Management Structure */
     ));

typedef S16 (*LnlCfgCfm)            ARGS((
        Pst        *pst,               /* Post Structure */
        NlMngmt    *cfg                /* Management Structure */
     ));

typedef S16 (*LnlCntrlReq)          ARGS((
        Pst         *pst,               /* Post Structure */
        NlMngmt     *cntrl              /* Management Structure */
     ));

typedef S16 (*LnlStatInd)          ARGS((
        Pst         *pst,               /* Post Structure */
        NlMngmt     *cntrl              /* Management Structure */
     ));

typedef S16 (*LnlCntrlCfm)          ARGS((
        Pst         *pst,               /* Post Structure */
        NlMngmt     *cntrl              /* Management Structure */
     ));

typedef S16 (*LnlCfgUpdateInd)   ARGS((
        Pst                    *pst,           /* Post Structure */
        NlCfgUpdateInd         *cfgUpdateInd   /* update config structure */
     ));

typedef S16 (*LnlSonCfgInd)   ARGS((
         Pst                    *pst,     /*!< Post Structure */
         LnlSonCfg              *sonCfg   /*!< SON config structure */
     ));

EXTERN S16 nlActvInit ARGS((
   Ent entity, 
   Inst inst, 
   Region region,
   Reason reason
));

EXTERN S16 nlActvTsk ARGS((
   Pst *pst, 
   Buffer *mBuf
));


EXTERN S16 smNlInit ARGS ((
   SSTskId    sysTskId
));

EXTERN S16 smNlActvTsk ARGS(( 
   Pst *pst, 
   Buffer *mBuf
));

EXTERN S16 smNlActvInit ARGS((
   Ent entity, 
   Inst inst, 
   Region region,
   Reason reason
));
 
EXTERN S16 SmMiLnlCfgReq ARGS((
   Pst         *pst, 
   NlMngmt     *cfg
));

EXTERN S16 SmMiLnlCfgCfm ARGS((
   Pst         *pst, 
   NlMngmt     *cfm
));

EXTERN S16 SmMiLnlCntrlReq ARGS((
   Pst         *pst, 
   NlMngmt     *cntrl
));

EXTERN S16 SmMiLnlCntrlCfm ARGS(( 
   Pst          *pst, 
   NlMngmt      *cfm
));

EXTERN S16 SmMiLnlUpdateTxPwrCfgInd ARGS((
   NlUpdateTxPwrCfgInd *txPwrInd
));

EXTERN S16 SmMiLnlUpdatePciCfgInd ARGS((
   NlUpdatePciCfgInd   *pciCfgInd
));

EXTERN S16 SmMiLnlUpdateEarfcnCfgInd ARGS((
   NlUpdateEarfcnCfgInd   *earfcnCfgInd
));

EXTERN S16 SmMiLnlCfgUpdateInd   ARGS((
   Pst                     *pst,
   NlCfgUpdateInd          *cfgUpdateInd
));

EXTERN S16 SmMiLnlSonCfgInd   ARGS((
   Pst                     *pst,
   LnlSonCfg               *sonCfg
));

EXTERN S16 SmMiLnlUpdatePrachCfgInd ARGS((
   NlUpdatePrachCfgInd *prachCfgInd
));

EXTERN S16 SmMiLnlUpdateTxPwrCfgInd ARGS((
NlUpdateTxPwrCfgInd     *txPwrCfgInd
));


EXTERN S16 SmMiLnlEnbStatInd ARGS((
   Pst        *pst,
   NlMngmt    *cellUpInd
));
/*function prototypes for packing all the interface messages*/

/** @brief This API is used to pack the config request send from LM to SON.*/
EXTERN S16 cmPkLnlCfgReq ARGS((
   Pst *                pst,
   NlMngmt *            cfg
));

/** @brief This API is used to handle config request send from LM to 
 * third party SON module */
EXTERN S16 PtMiLnlCfgReq ARGS((
   Pst *                pst,
   NlMngmt *            cfg
));

/** @brief This API is used to unpack the config request send from LM to SON.*/
EXTERN S16 cmUnpkLnlCfgReq ARGS((
   LnlCfgReq            func,
   Pst                  *pst,
   Buffer               *mBuf
));

/** @brief This API is used to pack the Configuration Confirm from SON to LM. */
EXTERN S16 cmPkLnlCfgCfm ARGS((
   Pst *                pst,
   NlMngmt *            cfm
));

/** @brief This API is used to pack the Configuration Confirm from SON to LM. */
EXTERN S16 PtMiLnlCfgCfm ARGS((
   Pst *                pst,
   NlMngmt *            cfm
));

/** @brief This API is used to unpack the Configuration Confirm from SON to LM. */
EXTERN S16 cmUnpkLnlCfgCfm ARGS((
   LnlCfgCfm            func,
   Pst *                pst,
   Buffer               *mBuf
));

/** @brief This API is used to pack the control request send from LM to SON.*/
EXTERN S16 cmPkLnlCntrlReq ARGS((
   Pst *                pst,
   NlMngmt *            cfg
));

/** @brief This API is used to handle control request send from LM to 
 * third party SON module */
EXTERN S16 PtMiLnlCntrlReq ARGS((
   Pst *                pst,
   NlMngmt *            cfg
));

/** @brief This API is used to unpack the control request send from LM to SON.*/
EXTERN S16 cmUnpkLnlCntrlReq ARGS((
   LnlCntrlReq          func,
   Pst                  *pst,
   Buffer               *mBuf
));

/** @brief This API is used to pack the Control Confirm from SON to LM. */
EXTERN S16 cmPkLnlCntrlCfm ARGS((
   Pst *                pst,
   NlMngmt *            cfm
));

EXTERN S16 cmUnpkLnlCntrlCfm ARGS ((
   LnlCntrlCfm          func,   /* primitive to be called after unpack the message */
   Pst                  *pst,   /* post structure */
   Buffer               *mBuf   /* message buffer */
));

/** @brief This API is used to pack the Control Confirm from SON to LM. */
EXTERN S16 PtMiLnlCntrlCfm ARGS((
   Pst *                pst,
   NlMngmt *            cfm
));

/** @brief This API is used to unpack the Control Confirm from SON to LM. */
EXTERN S16 cmUnpkLnlCfgCfm ARGS((
   LnlCntrlCfm          func,
   Pst *                pst,
   Buffer               *mBuf
));

/** @brief This API is used to pack the update Configuration from SON to LM. */
EXTERN S16 cmPkLnlCfgUpdateInd ARGS((
   Pst                     *pst,
   NlCfgUpdateInd          *cfgUpdateInd
));

/** @brief This API is used to pack the update Configuration from SON to LM. */
EXTERN S16 PtMiLnlCfgUpdateInd ARGS((
   Pst                      *pst,
   NlCfgUpdateInd           *cfgUpdateInd
));

/** @brief This API is used to unpack the update Configuration from SON to LM. */
EXTERN S16 cmUnpkLnlCfgUpdateInd ARGS((
   LnlCfgUpdateInd           func,
   Pst *                     pst,
   Buffer                    *mBuf
));

/** @brief This API is used to pack the cell up indication send from LM to SON.*/
EXTERN S16 cmPkLnlStatInd ARGS((
   Pst *                pst,
   NlMngmt *            cfg
));

/** @brief This API is used to handle cell up indication send from LM to
 * third party SON module */
EXTERN S16 PtMiLnlStatInd ARGS((
   Pst *                pst,
   NlMngmt *            cfg
));

/** @brief This API is used to unpack the cell up indication send from LM to SON.*/
EXTERN S16 cmUnpkLnlStatInd ARGS((
   LnlStatInd            func,
   Pst                   *pst,
   Buffer                *mBuf
));

EXTERN S16 cmPkLnlSonCfgInd   ARGS((
   Pst         *pst,        /* post structure */
   LnlSonCfg   *sonCfg      /* SON config message structure */
));

EXTERN S16 cmUnpkLnlSonCfgInd   ARGS((
   LnlSonCfgInd            func,   /* primitive to be called after unpack the message */
   Pst                     *pst,   /* post structure */
   Buffer                  *mBuf   /* message buffer */
));

EXTERN S16 PtMiLnlSonCfgInd   ARGS((
   Pst                    *pst,         /* post structure */
   LnlSonCfg              *sonCfg       /* SON config message structure */
));

/** @brief This primitive is sent from Layer manager to SON. It carries
  * configuration information towards SON.
  * @details This primitive can be used by layer manager to configure the
  * following entities at SON.
  * -# General configuration
  * -# NLU SAP i.e. SAP towards SON
  * 
  * @param pst pointer to Pst
  * @param cfg pointer to NlMngmt
  * @return ROK/RFAILED
  */
EXTERN S16 NlMiLnlCfgReq ARGS((
    Pst     *pst, 
    NlMngmt *cfg
));

/** @brief This primitive carries the Confirmation for a Configuration Request
  * sent from the layer manager to SON.
  * @details This primitive is used by SON to inform Layer manager about the
  * status of a Configuration Request.
  * @param pst Pointer to the post structure.
  * @param cfm pointer to NlMngmt 
  * @return ROK/RFAILED
  */
EXTERN S16 NlMiLnlCfgCfm ARGS((
    Pst     *pst, 
    NlMngmt *cfm
));

/** @brief This primitive is sent from Layer manager to SON. It carries
  * control information towards SON.
  * @details This primitive can be used by layer manager to send the control
  * information to SON.
  * 
  * @param pst pointer to Pst
  * @param cfg pointer to NlMngmt
  * @return ROK/RFAILED
  */
EXTERN S16 NlMiLnlCntrlReq ARGS((
    Pst     *pst, 
    NlMngmt *cfg
));

/** @brief This primitive carries the Confirmation for a Control Request
  * sent from the layer manager to SON.
  * @details This primitive is used by SON to inform Layer manager about the
  * status of a Control Request.
  * @param pst Pointer to the post structure.
  * @param cfm pointer to NlMngmt
  * @return ROK/RFAILED
  */

EXTERN S16 NlMiLnlCntrlCfm ARGS((
   Pst      *pst,
   NlMngmt  *cntrl
));

/** @brief This primitive carries the Cell Up Indication 
  * sent from the layer manager to SON.
  * @details This primitive is used by SON to inform inform SON server about eNodeB is ready
  * @param pst Pointer to the post structure.
  * @param cfm pointer to NlMngmt
  * @return ROK/RFAILED
  */

EXTERN S16 NlMiLnlStatInd ARGS((
   Pst      *pst,
   NlMngmt  *cellUpInd
));

/** @brief This primitive is sent from SON to stack manager. It carries
  * updated PCI/EARFCN/PRACH config information
  * @details This primitive can be used by SON module to send update PCI/EARFCN/PRACH config
  * information to Stack manager
  *
  * @param pst pointer to Pst
  * @param cfgUpdateInd pointer to NlCfgUpdateInd
  * @return ROK/RFAILED
  */
EXTERN S16 NlMiLnlCfgUpdateInd ARGS((
    Pst                     *pst,
    NlCfgUpdateInd          *cfgUpdateInd
));

EXTERN S16 NlMiLnlAlarmInd   ARGS((
   Pst                      *pst,        /* post structure */
   NlMngmt                  *nlMngmt     /* interface structure */
));

EXTERN S16 SmMiLnlStatInd ARGS((
   Pst                     *pst,
   NlMngmt                 *mngmt
));
EXTERN S16 NlMiLnlBrdcmSonCfgInd ARGS((
      Pst         *pst,     /*!< post structure */
      LnlSonCfg   *sonCfg   /*!< BRDCM-SON config structure */
      ));


#endif /* LNL_X_ */
/********************************************************************30**

           End of file:     lnl.x@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 15:08:07 2014

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
