/**********************************************************************

     Name:     LTE-RRC Layer 
  
     Type:     C include file
  
     Desc:     Structures, variables and typedefs required by the LTE-RRC
               layer management interface.

     File:     lnh.x

     Sid:      lnh.x@@/main/3 - Thu Jun 30 15:53:13 2011

     Prg:      manu

**********************************************************************/
/*
 *     The structures and variables declared in this file
 *     correspond to structures and variables used by
 *     the following TRILLIUM software:
 *
 *     part no.             description
 *     --------     ----------------------------------------------
 *     1000369      LTE-RRC
 *
*/
 
#ifndef __LNHX__
#define __LNHX__

#ifdef __cplusplus
extern "C" {
#endif


/* typedefs */

/**
 * @struct nhGenCfg 
 * General Configuration parameters that apply to the entire RRC software.
   It can be called only once.
   As part of general configuration multiple number of RRC lower SAPs can 
   be specified. Multiple lower SAPs can be configured depending upon 
   the number of cells supported in RRC. RRC supports cell-based distribution
   of traffic on lower interface. The actual lower SAP IDs to be used for the
   cell is specified during cell configuration.
 */

/** @brief General Configuration structure parameters */
typedef struct nhGenConfig
{
   Pst            lmPst;          /*!< Layer manager post structure.
                                    <BR><b> Reconfigurable: </b>  Yes */
   U32            maxCell;        /*!< Maximum number of cells 
                                    <BR><b> Reconfigurable:</b>  Yes */
   U8             minTransLstLen; /*!< Minimum number of elements that must
                                   * be created by default in the Transaction
                                   * list for every UE.
                                   *  <BR><b> Reconfigurable:</b> Yes */
   U8             minMuiLstLen;   /*!< Minimum number of elements that must
                                   * be created by default in the Message Unit
                                   * Idenfier list for every UE. 
                                   * <BR><b> Reconfigurable:</b> Yes */
   U16            msecTmrRes;     /*!< Timer Resolution in Ticks. 
                                   * This parameter indicates the number of
                                     system ticks elapsed between successive
                                     timer monitoring events; for example, if
                                     the system tick is one millisecond and a 
                                     timer event is desired after one second, 
                                     the value of the timerRes must be 1000. 
                                     <b> Allowed values</b>: 1 to 32767 
                                   * <BR><b> Reconfigurable: </b> No */
   TmrCfg         cfgTmr;         /*!< Configuration Timer. This timer is used
                                       to start a timer for the configuration 
                                       transactions with the lower layers.
                                       <BR><b> Reconfigurable:</b> Yes */

   U8             nmbKwuSaps;     /*!< Number of RLC data SAPs.  
                                       <BR><b> Reconfigurable:</b> No */
   U8             nmbCkwSaps;     /*!< Number of RLC cntrol SAPs. 
                                       <BR><b> Reconfigurable:</b> No */
   U8             nmbCrgSaps;     /*!< Number of MAC cntrol SAPs. 
                                       <BR><b> Reconfigurable:</b> No */
   U8             nmbCpjSaps;     /*!< Number of PDCP cntrol SAPs. 
                                       <BR><b> Reconfigurable:</b> No */
   U8             nmbPjuSaps;     /*!< Number of PDCP data SAPs. 
                                       <BR><b> Reconfigurable:</b> No */
#ifdef RRC_PHY_CFG_SUPP
   U8             nmbCtfSaps;     /*!< Number of PHY control SAPs. 
                                       <BR><b> Reconfigurable:</b> No */
#endif /* RRC_PHY_CFG_SUPP */
#ifdef DEBUGP
   U32            dbgMsk;         /*!< Initial debug mask for layer.  
                                       <BR><b> Reconfigurable:</b> No */
#endif /* DEBUGP */
   /*shivani*/
   U32 portNumber;
   U8 ipAddress[16];
   U8 rrcLogEnable;
} NhGenCfg;

/**
 * @struct nhGenSts 
 * General RRC statistics counters
 */

/* @brief General RRC Statistics procedure level */
typedef struct nhGenSts
{
   U32       numEstbCon;        /*!< Number of established RRC Connections. 
                                   <BR> Trigger: Reception of RRC Connection
                                   Setup Complete message. */
   U32       numFailCon;        /*!< Number of Failed RRC Connections.
                                   <BR> Trigger: Reception of UE Cancel request
                                   primitive before receiving RRC Connection
                                   Setup Complete message. */
   U32       numReConfigSucc;   /*!< Number of successful RRC Reconfiguration.
                                  <BR> Trigger: Reception of RRC Reconfiguration
                                  Complete message. */
   U32       numReConfigFail;   /*!< Number of Failed RRC Reconfiguration.
                                   <BR> Trigger: Reception of RRC
                                   Reestablishment Request message with cause
                                   reconfiguration failure. */
   U32       numUnExptMsg;      /*!< Number of Unexpected Messages received.
                                   <BR> Trigger: Reception of RRC messages which
                                   are not implemented in RRC. */
   U32       numLwLyFail;       /*!< Number of lower layer failures.
                                   <BR> Trigger: Reception of negative confirm
                                   primitive from lower layers. */
   U32       numDecErr;         /*!< Number of Erroneous Messages received. */
   U32       numEncErr;         /*!< Number of messages with encoding errors. */
   U32       numPdcpErr;        /*!< Number of PDCP Errors.
                                   <BR> Triggers: SDU discard timer expiry,
                                   integrity verification failure and
                                   deciphering failure. */
   U32       numRlcErr;         /*!< Number of RLC Errors.
                                     <BR> Trigger: RLC maximum retransmission
                                     exceeded. */
} NhGenSts;


/**
 * @struct nhPduSts
 * RRC PDU Statistics
 */
/* @brief RRC PDU Statistics structure parameters */
typedef struct nhPduSts
{
   U32      dlInfoTransfer;      /*!< DL Information Transfer message. */
   U32      ulInfoTransfer;      /*!< UL Information Transfer message. */
   U32      connReconfig;        /*!< RRC Connection Reconfiguration message. */
   U32      connReconfigCom;     /*!< RRC Connection Reconfiguration Complete message. */
   U32      connSetupComplete;   /*!< RRC Connection Setup Complete message. */
   U32      connRel;             /*!< RRC Connection Release message. */
   U32      secModCmd;           /*!< Security Mode Command. */
   U32      secModCmpl;          /*!< Security Mode Complete message. */
   U32      secModFail;          /*!< Security Mode Failure message. */
   U32      ueCapEnq;            /*!< UE Capability Enquiry message. */
   U32      ueCapInfo;           /*!< UE Capability Information message. */
   U32      cntChk;              /*!< Counter Check message. */
   U32      cntChkRes;           /*!< Counter Check Response message. */
   U32      mobFrmEUTRACmd;      /*!< Mobility From EUTRA Command message. */
   U32      hoFrmEUTRAPrepReq;   /*!< HO From EUTRA Preparation Request message. */
   U32      ulHOPrepTfr;         /*!< UL Handover Prepartion Tranfer message. */
   U32      csfbParamReqCDMA;    /*!< CSFB Parameters Request CDMA2000 message. */
   U32      csfbParamResCDMA;    /*!< CSFB Parameters Response CDMA2000 message. */
   U32      connReestabCom;      /*!< RRC Connection Reestablishment Request message. */
/* lnh_x_001.main_2: Added ueinforeq, ueinfoRsp and proximity indication sts*/
#ifdef LNH_VER1
   U32      ueInfoReq;           /*!< UE Information Request message. */
   U32      ueInfoRsp;           /*!< UE Information Response message. */
   U32      prxmtyInd;           /*!< Proximity Indication message. */
#endif /* LNH_VER1 */
} NhPduSts;

/**
 * @struct nhCellSts 
 * Cell-specific statistics
 */

/* @brief Cell-specific Statistics structure parameters */
typedef struct nhCellSts
{
   U16         cellId;             /*!< Cell ID */
   U32         pag;                /*!< Paging message. */
   U32         connSetup;          /*!< RRC Connection Setup message. */
   U32         connReject;         /*!< RRC Connection Reject message. */
   U32         connReq;            /*!< RRC Connection Request message. */
   U32         connReestabReq;     /*!< RRC Connection Reestablishment Request message. */
   U32         connReestab;        /*!< RRC Connection Reestablishment Message */
   U32         connReestabRej;     /*!< RRC Connection Reestablishment Reject message. */
   U32         numUEs;             /*!< Number of UEs. */
   U32         hoToEUTRASucc;      /*!< successful HO to EUTRAN. */
   U32         hoFromEUTRAFail;    /*!< unsuccessful HO from EUTRAN. */  
} NhCellSts;

/**
 * @struct nhCellSts 
 *  UE Statistics
 */
/** @brief UE Statistics structure parameters */
typedef struct nhUeSts
{
   U16   cellId;                 /*!< Cell ID */
   U16   crnti;                  /*!< C-RNTI */
   struct
   {
      NhPduSts    pdu;           /*!< PDU statistics */
   } cfm;
} NhUeSts;

/**
 * @struct nhSts
 * Statistics Structure 
 */

/** @brief Statistics structure parameters */
typedef struct nhSts
{
   DateTime dt;                /*!< Date and time */
   union
   {
      NhGenSts      genSts;    /*!< General statistics */
#ifndef NH_NO_STS
      NhUeSts       ueSts;     /*!< UE statistics */
      NhCellSts     cellSts;   /*!< Cell statistics */
#endif /* NH_NO_STS */
   } u;
} NhSts;

/**
 * @struct nhSapSta
 *  SAP Status structure 
 */

/** @brief SAP Status structure parameters */
typedef struct nhSapSta
{
   SpId       sapId;           /*!< SAP ID */
   U8         sapState;        /*!< State of the SAP */
} NhSapSta;

/**
 * @struct nhGenSta
 *  General Status structure
 */
/** @brief General Status structure parameters */
typedef struct nhGenSta
{
   U32        memSize;         /*!< Total static memory size. */
   U32        memAlloc;        /*!< Total static memory allocated. */
   U32        numCon;          /*!< Number of active UE connections. */
} NhGenSta;


/**
 * @struct nhSsta
 * Solicited Status structure 
 */
/** @brief Solicited Status structure parameters */
typedef struct nhSsta
{
   DateTime dt;                /*!< Date and time */
   union
   {
      NhSapSta  sap;           /*!< SAP Status */
      SystemId  sysId;         /*!< System ID */
      NhGenSta  genSta;        /*!< General status */
   } u;
} NhSsta;

/**
 * @struct nhSapInfo
 * SAP ID and SAP type
 */
/** @brief SAP ID and SAP type structure parameters */
typedef struct nhSapInfo
{
   SpId       sapId;        /*!< SAP ID on which event is received */
   U16        sapElmId;     /*!< SAP Entity */
} NhSapInfo;

/** @brief Cell and UE ID structure parameters */
typedef struct nhCellUEId
{
   U16        ueId;         /*!< UE ID */
   U16        cellId;       /*!< Cell ID */
}NhCellUEId;
/**
 * @struct nhUstaDgn
 * Alarm diagnostics structure
 */
/** @brief Alarm diagnostics structure parameters */

typedef struct nhUstaDgn
{
   U8         type;            /*!< Type of USTA alarm */
   union
   {
      Mem        mem;          /*!< Memory pool and region */
      NhSapInfo  sapInfo;      /*!< SapInfo - SAP ID and type */
      U8         tId;          /*!< Timer ID */
      U8         msgType;      /*!< Message Type */
      U8         data[LNH_USTA_MAX_DGNVAL]; /*!< Data Buffer */
      NhCellUEId cellUeId;     /* Cell and UE ID */
   }u;
} NhUstaDgn;

/**
 * @struct nhUsta
 * Unsolicited Status structure
 */
/** @brief Unsolicited Status structure parameters */

typedef struct nhUsta
{
   CmAlarm   alarm;            /*!< Alarms */
   NhUstaDgn dgn;              /*!< Alarm diagnostics */
} NhUsta;

/**
 * @struct nhSapCntrl
 * SAP Control structure
 */
 /** @brief SAP Control structure parameters */
typedef struct nhSapCntrl 
{
   SpId      sapId;           /*!< SAP ID. 
                             <b> Allowed values: </b> 0 to (maxSAP -1)
                             <br> maxSAP = numLSaps, if elmnt is:
                             - STNHKWUSAP
                             - STNHCKWSAP
                             - STNHCRGSAP
                             - STNHCPJSAP
                             - STNHPJUSAP
                             - STNHCTFSAP
                             <br> maxSAP=numUSaps, if elmnt is STNHUSAP.*/

} NhSapCntrl;

#ifdef DEBUGP
/**
 * @struct nhDbgCntrl
 * Debug printing control. RRC layer implementation supports debug logging in
 * two versions:
   - Console output - Debug prints are directed to a console.
   - File output - Debug prints are directed to a file. This option expects
                   the file path and number of debug lines per debug file as 
                   a part of the debug control request.

 */
 /** @brief Debug Printing Control structure parameters*/
typedef struct nhDbgCntrl 
{
   U32       dbgMsk;                       /*!< Debug Mask parameter. 
                                            This field can be set to a 
                                            combination of the below allowed 
                                            values by using OR "|" operator.
                                            For example, if the 
                                            debug and info debugging prints  
                                            to be enabled/disabled, the dbgMask
                                            is set to "LNH_DBGMASK_INFO|
                                            LNH_DBGMASK_DBG".
                                              <b> Allowed values </b>
                                                - LNH_DBGMASK_INFO
                                                   To print specific behaviour
                                                   /logic flow.
                                                - LNH_DBGMASK_DBG
                                                   To print extensive logs.
                                                - LNH_DBGMASK_PARAM
                                                   To print function
                                                   parameters values.
                                                - LNH_DBGMASK_ERROR
                                                   To print in error legs.
                                                - LNH_DBGMASK_FATAL
                                                   To print any system effecting
                                                   errors such as resouce
                                                   unavailability.
                                            */

#ifdef NH_LOG_TO_FILE
   Bool      fileLogEnb;                   /*!< To Enable/Disable file logging. */
   Txt       filePath[LNH_MAX_FILE_PATH];  /*!< Path to store log files. */  
   U32       nmbDbgLines;                  /*!< Number of lines per Debug file. */
#endif /* NH_LOG_TO_FILE */
} NhDbgCntrl;
#endif /* DEBUGP */

/**
 * @struct nhCntrl
 * Management Control Structure 
 */
/** @brief Management Control structure parameters */
typedef struct nhCntrl
{
   Action action;                 /*!< This field specifies the action that the
                                    RRC layer must take. */
   Action subAction;              /*!< This field specifies the protocol element
                                    on which the RRC layer takes the specified
                                    action. */
   union
   {
      NhSapCntrl      sap;        /*!< The layer manager can selectively bind or
                                    unbind the different SAPs and also to
                                    enable or disable tracing of incoming/
                                    outgoing messages on the lower interface. */
#ifdef DEBUGP
      NhDbgCntrl      dbg;        /*!< The layer manager can selectively enable
                                     or disable various levels of debug 
                                     printing. */
#endif /* DEBUGP */
#ifdef SS_DIAG
      U32            logMask;        /* Logging Mask */
#endif
   }u;
} NhCntrl;

/**
 * @struct nhTrc
 * Trace indication structure
 */
 /** @brief Trace Indication structure parameters */
typedef struct nhTrc
{
   DateTime   dt;                            /*!< Date and time structure */
   U16        evnt;                          /*!< Event code 
                                               <b> Allowed values:</b>
                                               - LNH_PDU_RX PDU received
                                               - LNH_PDU_TX PDU transmitted */
   U16        len;                           /*!< Trace length */
   U8         evntParm[LNH_MAX_TRACE_LEN];   /*!< Event parameters */
}NhTrc;

/**
 * @struct nhProtCfg
 *  Protocol configuration parameters. Passes protocol-specific parameters, such as the maximum number of connections.
 */
/** @brief Protocol configuration parameters */
typedef struct nhProtConfig
{
   U32            maxConn;        /*!< Maximum number of simultaneous or
                                   * active UE RRC connections allowed.
                                   * <BR><b> Reconfigurable:</b> Yes */
} NhProtCfg;

/**
 * @struct nhUSapCfg
 * Upper SAP configuration parameters. Typically, there is one upper SAP
 * for each application that needs to use LTE RRC layer.
 */
/** @brief Upper SAP configuration parameters */
typedef struct nhUSapConfig
{
   Selector     selector;            /*!< Coupling at the upper interface with
                                        RRC user. 
                                        <b> Allowed values</b>
                                        - LNH_SEL_LC - Loose coupling
                                        - LNH_SEL_TC - Tight coupling
                                        - LNH_SEL_LWLC - Light-weight loose coupling
                                     * <BR><b> Reconfigurable:</b> No */
   MemoryId     mem;                 /*!< Dynamic memory pool for the messages
                                        sent in the loosely coupled mode at the
                                        upper interface.
                                     * <BR><b> Reconfigurable:</b> Yes */
   Priority     prior;               /*!< Priority of messages sent through 
                                        this SAP. 
                                        <b> Allowed values: </b> 0 to 3 
                                        (0 indicates the highest priority and
                                        3 indicates the lowest priority).
                                     * <BR><b> Reconfigurable:</b> Yes */
   ProcId       procId;              /*!< Destination processor ID. 
                                        <b> Allowed values: </b> 0 to 255
                                     * <BR><b> Reconfigurable:</b> No */
   Ent          ent;                 /*!< Destination entity ID.
                                        <b> Allowed values: </b> ENTXX, where
                                        XX is the two-letter prefix for the user
                                        of this layer.
                                     * <BR><b> Reconfigurable:</b> No */
   Inst         inst;                /*!< Destination instance ID. 
                                        <b> Allowed values: </b> 0 
                                     * <BR><b> Reconfigurable:</b> No */
   Route        route;               /*!< Route.
                                        <b> Allowed values: </b> RTESPEC for
                                        conventional and distributed upper layer
                                     * <BR><b> Reconfigurable:</b> No */
   SpId         spId;                /*!< Service provider ID.
                                     * <BR><b> Reconfigurable:</b> No */
} NhUSapCfg;


/**
 * @struct nhLSapCfg
 * Lower SAP Configuration parameters that apply to a specific interface
   (KWU, CKW, CRG, CPJ, PJU, CTF) SAP. It primarily configures the post 
   structure, SpId and SuId of the SAP.

   Multiple lower SAPs can be configured depending upon 
   the number of cells supported in RRC. RRC supports cell based distribution
   of traffic on lower interface. The actual lower SAP IDs to be used for the
   cell is specified during cell configuration.
 */
/** @brief Lower SAP Configuration parameters */
typedef struct nhLSapConfig
{
   Selector     selector;            /*!< Coupling at the lower interface with
                                        RRC service provider. 
                                        <b> Allowed values:</b>
                                        - LNH_SEL_LC - Loose coupling
                                        - LNH_SEL_TC - Tight coupling
                                        - LNH_SEL_LWLC - Light-weight loose coupling
                                     * <BR><b> Reconfigurable:</b> No */
   MemoryId     mem;                 /*!< Dynamic memory pool for the messages
                                        sent in the loosely coupled mode at the
                                        upper interface.
                                     * <BR><b> Reconfigurable:</b> Yes */
   Priority     prior;               /*!< Priority of messages sent through 
                                        this SAP. 
                                        <b> Allowed values: </b> 0 to 3 
                                        (0 indicates the highest priority; 
                                        3 indicates the lowest priority).
                                     * <BR><b> Reconfigurable:</b> Yes */
   ProcId       procId;              /*!< Destination processor ID. 
                                        <b> Allowed values: </b> 0 to 255
                                     * <BR><b> Reconfigurable:</b> No */
   Ent          ent;                 /*!< Destination entity ID. 
                                        <b> Allowed values: </b> ENTXX, where
                                        XX is defined the user of this layer.
                                     * <BR><b> Reconfigurable:</b> No */
   Inst         inst;                /*!< Destination instance ID. 
                                        <b> Allowed values: </b> 0 
                                     * <BR><b> Reconfigurable:</b> No */
   Route        route;               /*!< Route. 
                                        <b> Allowed values: </b> RTESPEC for
                                        conventional and distributed upper layer.
                                     * <BR><b> Reconfigurable:</b> No */
   SpId         spId;                /*!< Service provider ID. 
                                     * <BR><b> Reconfigurable:</b> No */
   SuId        suId;                 /*!< Service user ID. 
                                        <b> Allowed values: </b> 0 to (maximum 
                                        service provider SAPs minus 1).
                                     * <BR><b> Reconfigurable:</b> No */
   U32         bndRetryCnt;          /*!< Number of retries for the bind 
                                        operation over this SAP.
                                     * <BR><b> Reconfigurable:</b> Yes */
   TmrCfg      bndTmr;               /*!< Bind timer configuration.
                                     * <BR><b> Reconfigurable:</b> Yes */ 
   TmrCfg      GrdTmr;               /*!< Guard timer configuration.
                                     * <b> Reconfigurable:</b> Yes */ 
} NhLSapCfg;

/**
 * @struct nhCfg
 * Configuration Structure parameters. 
 */
/** @brief Configuration Structure parameters. */
typedef struct nhCfg
{
   union
   {
      NhGenCfg    gen;           /*!< General configuration */
      NhUSapCfg   uSap;          /*!< Upper SAP configuration */
      NhLSapCfg   lSap;          /*!< Lower SAP configuration */
      NhProtCfg   prot;          /*!< Protocol-specific configuration */
   }u;
} NhCfg;

/**
 * @struct nhMngmt
 * Management Structure
 */

typedef struct nhMngmt
{
   Header       hdr;           /*!< Header structure. */
   CmStatus     cfm;           /*!< Primitive Status/Confirm, the acknowledgment
                                    for request to RRC is returned in cfm structure.
                                */
   union
   {
      NhCfg     cfg;           /*!< Configuration structure, hdr.elmId.elmnt
                                    indicates type of configuration request. */
      NhCntrl   cntrl;         /*!< Control structure, elmnt in Header and 
                                     action/subAction on NhCntrl indicate type
                                     of control request. */
      NhSsta    ssta;          /*!< Solicited status. */
      NhUsta    usta;          /*!< Unsolicited status, that is, alarms raised by RRC. */
      NhSts     sts;           /*!< RRC Statistics structure. */
      NhTrc     trc;           /*!< RRC Trace structure for the PDU sent and
                                    received by RRC. */
   } u;
} NhMngmt;

/* Interface primitives */
typedef S16 (*LnhCfgReq) ARGS((Pst *pst, NhMngmt *cfg));

typedef S16 (*LnhCfgCfm) ARGS((Pst *pst, NhMngmt *cfm));

typedef S16 (*LnhStsReq) ARGS((Pst *pst, Action action, NhMngmt *sts));

typedef S16 (*LnhStsCfm) ARGS((Pst *pst, NhMngmt *cfm));

typedef S16 (*LnhStaReq) ARGS((Pst *pst, NhMngmt *sta));

typedef S16 (*LnhStaCfm) ARGS((Pst *pst, NhMngmt *cfm));

typedef S16 (*LnhStaInd) ARGS((Pst *pst, NhMngmt *sta));

typedef S16 (*LnhCntrlReq) ARGS((Pst *pst, NhMngmt *cntrl));

typedef S16 (*LnhCntrlCfm) ARGS((Pst *pst, NhMngmt *cfm));

typedef S16 (*LnhTrcInd) ARGS((Pst *pst, NhMngmt *trc));

EXTERN S16 cmPkNhGenCfg ARGS((NhGenCfg *param, Buffer *mBuf));
EXTERN S16 cmUnpkNhGenCfg ARGS((NhGenCfg *param, Buffer *mBuf));
EXTERN S16 cmPkNhGenSts ARGS((NhGenSts *param, Buffer *mBuf));
EXTERN S16 cmUnpkNhGenSts ARGS((NhGenSts *param, Buffer *mBuf));
EXTERN S16 cmPkU32 ARGS((U32 *param, Buffer *mBuf));
EXTERN S16 cmUnpkU32 ARGS((U32 *param, Buffer *mBuf));
EXTERN S16 cmPkNhPduSts ARGS((NhPduSts *param, Buffer *mBuf));
EXTERN S16 cmUnpkNhPduSts ARGS((NhPduSts *param, Buffer *mBuf));
EXTERN S16 cmPkNhCellSts ARGS((NhCellSts *param, Buffer *mBuf));
EXTERN S16 cmUnpkNhCellSts ARGS((NhCellSts *param, Buffer *mBuf));
EXTERN S16 cmPkNhUeSts ARGS((NhUeSts *param, Buffer *mBuf));
EXTERN S16 cmUnpkNhUeSts ARGS((NhUeSts *param, Buffer *mBuf));
EXTERN S16 cmPkNhSts ARGS((NhSts *param, U16 elmnt, Buffer *mBuf));
EXTERN S16 cmUnpkNhSts ARGS((NhSts *param, U16 elmnt, Buffer *mBuf));
EXTERN S16 cmPkNhSapSta ARGS((NhSapSta *param, Buffer *mBuf));
EXTERN S16 cmUnpkNhSapSta ARGS((NhSapSta *param, Buffer *mBuf));
EXTERN S16 cmPkNhGenSta ARGS((NhGenSta *param, Buffer *mBuf));
EXTERN S16 cmUnpkNhGenSta ARGS((NhGenSta *param, Buffer *mBuf));
EXTERN S16 cmPkNhSsta ARGS((NhSsta *param, U16 elmnt, Buffer *mBuf));
EXTERN S16 cmUnpkNhSsta ARGS((NhSsta *param, U16 elmnt, Buffer *mBuf));
EXTERN S16 cmPkNhUstaDgn ARGS((NhUstaDgn *param, Buffer *mBuf));
EXTERN S16 cmUnpkNhUstaDgn ARGS((NhUstaDgn *param, Buffer *mBuf));
EXTERN S16 cmPkNhUsta ARGS((NhUsta *param, Buffer *mBuf));
EXTERN S16 cmUnpkNhUsta ARGS((NhUsta *param, Buffer *mBuf));
EXTERN S16 cmPkNhSapCntrl ARGS((NhSapCntrl *param, Buffer *mBuf));
EXTERN S16 cmUnpkNhSapCntrl ARGS((NhSapCntrl *param, Buffer *mBuf));
#ifdef DEBUGP
EXTERN S16 cmPkNhDbgCntrl ARGS((NhDbgCntrl *param, Buffer *mBuf));
EXTERN S16 cmUnpkNhDbgCntrl ARGS((NhDbgCntrl *param, Buffer *mBuf));
#endif
EXTERN S16 cmPkNhCntrl ARGS((NhCntrl *param, U16 elmnt, Buffer *mBuf));
EXTERN S16 cmUnpkNhCntrl ARGS((NhCntrl *param, U16 elmnt, Buffer *mBuf));
EXTERN S16 cmPkNhTrc ARGS((NhTrc *param, Buffer *mBuf));
EXTERN S16 cmUnpkNhTrc ARGS((NhTrc *param, Buffer *mBuf));
EXTERN S16 cmPkNhProtCfg ARGS((NhProtCfg *param, Buffer *mBuf));
EXTERN S16 cmUnpkNhProtCfg ARGS((NhProtCfg *param, Buffer *mBuf));
EXTERN S16 cmPkNhUSapCfg ARGS((NhUSapCfg *param, Buffer *mBuf));
EXTERN S16 cmUnpkNhUSapCfg ARGS((NhUSapCfg *param, Buffer *mBuf));
EXTERN S16 cmPkNhLSapCfg ARGS((NhLSapCfg *param, Buffer *mBuf));
EXTERN S16 cmUnpkNhLSapCfg ARGS((NhLSapCfg *param, Buffer *mBuf));
EXTERN S16 cmPkNhCfg ARGS((NhCfg *param, U16 elmnt, Buffer *mBuf));
EXTERN S16 cmUnpkNhCfg ARGS((NhCfg *param, U16 elmnt, Buffer *mBuf));
EXTERN S16 cmPkNhMngmt ARGS((NhMngmt *param, U8 evnt, Buffer *mBuf));
EXTERN S16 cmUnpkNhMngmt ARGS((NhMngmt *param, U8 evnt, Ptr ptr, Buffer *mBuf));

EXTERN S16 nhActvInit ARGS((Ent entity, Inst inst, Region region, 
                                                           Reason reason));
 
#ifdef SM
EXTERN S16 smNhActvTsk ARGS(( Pst *pst, Buffer *mBuf));
EXTERN S16 smNhActvInit ARGS((Ent entity, Inst inst, Region region, 
                                                           Reason reason));

EXTERN S16 SmMiLnhCfgReq ARGS((Pst *pst, NhMngmt *cfg));
EXTERN S16 SmMiLnhCfgCfm ARGS((Pst *pst, NhMngmt *cfm));

EXTERN S16 SmMiLnhStsReq ARGS((Pst *pst, Action action, NhMngmt *sts));
EXTERN S16 SmMiLnhStsCfm ARGS((Pst *pst, NhMngmt *cfm));

EXTERN S16 SmMiLnhStaReq ARGS((Pst *pst, NhMngmt *sta));
EXTERN S16 SmMiLnhStaCfm ARGS((Pst *pst, NhMngmt *cfm));
EXTERN S16 SmMiLnhStaInd ARGS((Pst *pst, NhMngmt *sta));

EXTERN S16 SmMiLnhCntrlReq ARGS((Pst *pst, NhMngmt *cntrl));
EXTERN S16 SmMiLnhCntrlCfm ARGS((Pst *pst, NhMngmt *cfm));

EXTERN S16 SmMiLnhTrcInd ARGS((Pst *pst, NhMngmt *trc));
#endif /* SM */

#ifdef NH

/**
*@defgroup lnhprim Layer manager primitives
@{
*/
/**
 * @details 

    The layer manager configures the various elements of RRC using the 
    management configuration procedure, which the layer manager 
    initiates. The RRC configuration request primitive (@ref NhMiLnhCfgReq)
    can be called more than once. NhMiLnhCfgReq primitives must be
    called before the bind primitives are called. Below is the lists of the
    RRC configuration request primitive types.

    To operate properly, the configuration request primitive types must be
    called in the following order:
      -# General configuration - @ref nhGenCfg
      -# Protocol configuration - @ref nhProtCfg
      -# Upper SAP configuration - @ref nhUSapCfg
      -# Each lower SAP configuration - @ref nhLSapCfg

      The general configuration must be done before any other configuration is done.
      The protocol configuration is done at least once for each self-node type. This
      configuration must also be done before the upper SAP configurations.

      The upper SAP configuration is sent at least once for each upper SAP:
      -   There is only one upper SAP (NHUSAP) for the RRC user.
      -   The lower SAP configuration is sent at least once for each lower SAP.
      -   When multiple lower SAP feature is enabled (by enabling the 
          TENB_MULT_CELL_SUPPRT flag at NHU interface), then multiple sets of lower 
          SAPs may be configured. Each set belonging to each cell.
      -   There are six lower SAPs. 
          - PJUSAP and KWUSAP are for data SAPs, while
          - CKWSAP, CRGSAP, CTFSAP, and CPJSAP are control SAPs.
      - The lower SAP configurations such as PJUSAP, KWUSAP, CKWSAP, CTFSAP,
      CRGSAP, and CPJSAP may be configured in any order. However, these 
      configurations must be performed only after the general and protocol 
      configuration.


* @param[in] pst Post structure.
* @param[in] cfg Management structure.

  In the header of the configuration request, the values of <b> hdr.elmId.elmnt
  </b> are set,  as shown below:
    -  STNHGEN        - General configuration
    -  STNHUSAP       - Upper SAP configuration
    -  STNHKWUSAP     - Lower KWU SAP configuration
    -  STNHCKWSAP     - Lower CKW SAP configuration
    -  STNHCRGSAP     - Lower CRG SAP configuration
    -  STNHCPJSAP     - Lower CPJ SAP configuration
    -  STNHPJUSAP     - Lower PJU SAP configuration
    -  STNHCTFSAP     - Lower CTF SAP configuration
    -  STNHPROT       - Protocol configuration

*/
EXTERN S16 NhMiLnhCfgReq ARGS((Pst *pst, NhMngmt *cfg));
/**
 * @details 
    This primitive is issued by RRC in response to the NhMiLnhCfgReq and 
    indicates whether the configuration was successful.

* @param[in] pst Post structure.
* @param[in] cfm Layer management structure. The configuration confirm
  contains only the header and the common status.

  Valid Status values of the configuration confirm primitive are:
  - LCM_PRIM_OK  - Successful request.
  - LCM_PRIM_NOK - Unsuccessful request.

  When the status is set to LCM_PRIM_OK, the reason field is set to
  LCM_REASON_NOT_APPL. For failure, the valid values of reason are:

  - LCM_REASON_MEM_NOAVAIL      - Memory is not available.
  - LCM_REASON_INVALID_ELMNT    - Invalid value of element field in the header.
  - LCM_REASON_REGTMR_FAIL      - Timer registration failed.
  - LCM_REASON_GENCFG_NOT_DONE  - General configuration is not done.
  - LCM_REASON_INVALID_PAR_VAL  - Invalid parameter values.
  - LNH_REASON_PROTCFG_NOT_DONE - Protocol configuration is not done.
  - LNH_REASON_LSAPCFG_NOT_DONE - Lower SAP configuration is not done.
  - LCM_REASON_EXCEED_CONF_VAL  - The number exceeds the value in general 
                                  configuration.
  - LNH_REASON_HASHINIT_FAIL    - Hash initialization failed.

  SmMiLnhCfgCfm is the function that processes this confirm primitive in the
  layer manager.

*/

EXTERN S16 NhMiLnhCfgCfm ARGS((Pst *pst, NhMngmt *cfm));

/**
 * @details 
    The layer manager gathers statistics information about the elements of RRC 
    using the management statistics procedure initiated by the layer manager. 
    The RRC statistics request primitive @ref NhMiLnhStsReq can be called more 
    than once and at any time after the management configuration procedure.
    The statistics values are returned by the @ref NhMiLnhStsCfm primitive. 
    The statistics counters can be reset using the action parameter. If the
    statistics counters are not explicitly reset, they can be reset when the
    count exceeds the size of the data structure used to store the statistics
    (currently 2^16 - 1). These RRC statistics request primitive types are
    called peer node statistics. They provide the count of each kind
    of message transmitted or received from the peer node. They also provide 
    the count of unexpected or error messages received and the number of times 
    each kind of timer expired when executing the procedures with the peer node.

* @param[in] pst Pointer to the pst structure.
* @param[in] sts Pointer to management structure. 
* @param[in] action This defines action by the layer after reading the statistics 
        The possible values are:
           - ZEROSTS   - Read and reset (set to zero) statistics.
           - NOZEROSTS - Does not reset the counters.

  In the header of the statistics request, the values of elmId.elmnt field are:
           - STNHGEN - General.
           - STNHPROT - Protocol.

*/
EXTERN S16 NhMiLnhStsReq ARGS((Pst *pst, Action action, NhMngmt *sts));
/**
 * @details 

  This primitive is used to convey the statistics as requested by the layer 
  manager in the NhMiLnhStsReq request.

* @param[in] pst Post structure.
* @param[in] sts Management structure. 

  In the header of the statistics confirm, the values of cfm.hdr.elmId.elmnt field are:
           - STNHGEN - General.
           - STNHPROT - Protocol.

  The status information is returned in the CmStatus data structure. 
  The status values are:
     - LCM_PRIM_OK  - Successful request.
     - LCM_PRIM_NOK - Unsuccessful request.

  When the status is set to LCM_PRIM_OK, the reason field is set to
  LCM_REASON_NOT_APPL. The other valid values are:
     - LRR_REASON_INVALID_ID - Invalid node identifier.
     - LCM_REASON_INVALID_ELMNT - Invalid value of element field in the header.

  SmMiLnhStsCfm is the function that processes this confirm primitive in the
  layer manager.
*/
EXTERN S16 NhMiLnhStsCfm ARGS((Pst *pst, NhMngmt *cfm));

/**
 * @details 

   The layer manager gathers solicited status information about the various 
   elements of RRC by using the management solicited status procedure, which 
   the layer manager initiates. The RRC status request primitive (@ref NhMiLnhStaReq)
   can be called more than once and at any time after the management
   configuration procedure.

   The following RRC status request primitive types are called:
      -  General
      -  System ID
      -  SAP status
   The nhMngmt.hdr.elmId field specifies the status request primitive type.
   The status confirm (@ref NhMiLnhStaCfm) and other system services primitives are 
   called during the status procedure to return the status value.
   The status request and status confirm primitives (@ref NhMiLnhStaReq and
   @ref NhMiLnhStaCfm, respectively), use the nhMngmt.u.ssta structure to specify
   the parameters.

* @param[in] pst Post structure.
* @param[in] sta Layer management structure. 

   In the header of the statistics request, the values of elmId.elmnt fields 
   are:

   -# STNHGEN - General
   -# STNHSID - System ID
   -# STNHUSAP - Upper SAP
   -# STNHKWUSAP - Lower KWU SAP
   -# STNHCKWSAP - Lower CKW SAP
   -# STNHCRGSAP - Lower CRG SAP
   -# STNHCPJSAP - Lower CPJ SAP
   -# STNHPJUSAP - Lower PJU SAP
   -# STNHCTFSAP - Lower CTF SAP

    Parameters of the NhSsta structure: 

    -# SAP status.
      The sapId needs to be filled, if the elmId.elmnt is one of the
      following:
      -#   STNHUSAP
      -#   STNHKWUSAP
      -#   STNHCKWSAP
      -#   STNHCRGSAP
      -#   STNHCPJSAP
      -#   STNHPJUSAP
      -#   STNHCTFSAP

  The other fields are filled and returned by RRC in the status confirm
      primitive. 

*/
EXTERN S16 NhMiLnhStaReq ARGS((Pst *pst, NhMngmt *sta));

/**
 * @details 

 This primitive is used by RRC to return solicited status information to the 
 layer manager. 

* @param[in] pst Post structure.
* @param[in] cfm Layer management structure.

        In the header of the statistics request, the values of elmId.elmnt are:
        -# STNHGEN: General
        -# STNHSID: System ID
        -# STNHUSAP: Upper SAP
        -# STNHKWUSAP: Lower KWU SAP
        -# STNHCKWSAP: Lower CKW SAP
        -# STNHCRGSAP: Lower CRG SAP
        -# STNHCPJSAP: Lower CPJ SAP
        -# STNHPJUSAP: Lower PJU SAP
        -# STNHCTFSAP: Lower CTF SAP

  The status information is returned in the CmStatus data structure. 
  The status values are:
     - LCM_PRIM_OK  - Successful request.
     - LCM_PRIM_NOK - Unsuccessful request.
    
  When the status is set to LCM_PRIM_OK, the reason field is set to
  LCM_REASON_NOT_APPL. The other valid values are:

  - LRR_REASON_INVALID_ID - Invalid node identifier.
  - LCM_REASON_INVALID_ELMNT - Invalid value of element field in the header.

  SmMiLnhStaCfm is the function that processes this confirm primitive in the
  layer manager.
    
*/
EXTERN S16 NhMiLnhStaCfm ARGS((Pst *pst, NhMngmt *cfm));

/**
 * @details 
 The management unsolicited status procedure provides unsolicited status
 information about RRC elements to the layer manager. RRC initiates this 
 procedure. The RRC status indication primitive (NhMiLnhStaInd) can be called 
 more than once and, if the unsolicited status is enabled, at any time after 
 the configuration procedure. The RRC status indication primitive is not called
 if the unsolicited status is disabled. The unsolicited status can be enabled 
 or disabled with the management control procedure.
 The nhMngmt.u.usta structure specifies parameters that are used by the status
 indication (NhMiLnhStaInd) primitive.

* @param[in] pst Post structure.
* @param[in] cfm Layer management structure.
 
  SmMiLnhStaInd is the function that processes this confirm primitive in the
  layer manager.

    The list of each alarms generated by the RRC layer are provided below:<br>
    @image html alarms.jpg
*/
EXTERN S16 NhMiLnhStaInd ARGS((Pst *pst, NhMngmt *sta));
/**
 * @details 

The management trace indication procedure presents RRC trace information to the
layer manager. RRC initiates this procedure. If tracing is enabled,
NhMiLnhTrcInd can be called at any time upon receipt or transmission of the RRC
PDU, after the management configuration procedure. NhMiLnhTrcInd is not called
if tracing is disabled. Tracing can be enabled or disabled with the management
control procedure.
The NhMngmt.u.nhTrc structure specifies the parameters that are used by the
trace indication (NhMiLnhTrcInd) primitive.

* @param[in] pst Post structure.
* @param[in] cfm Layer management structure. 

  SmMiLnhTrcInd is the function that processes this confirm primitive in the
  layer manager.
 */
EXTERN S16 NhMiLnhTrcInd ARGS((Pst *pst, NhMngmt *trc));

/**
 * @details 
 *
The layer manager uses the management control procedure to control RRC
elements. The layer manager initiates this procedure. The RRC control request
primitive (NhMiLnhCntrlReq) can be called more than once and at any time after
the management configuration procedure.
The following RRC control request primitive types can be called:
    -# Trace control
    -# Debug control
    -# SAP control

The cntrl.u.cntrl.action field specifies the control request primitive type.
The cntrl.u.cntrl.subaction field specifies the element to be controlled.
The cntrl.u.cntrl structure specifies the parameters that are used by the
control request (NhMiLnhCntrlReq) primitive.

* @param[in] pst Pointer to the pst structure.
* @param[in] cntrl Pointer to management structure. 

  In the header of the contrl request, the values of elmId.elmnt are:
  -# STNHGEN - General.
  -# STNHPROT - Protocol.
  -# STNHUSAP - Upper SAP.
  -# STNHKWUSAP - Lower KWU SAP.
  -# STNHCKWSAP - Lower CKW SAP.
  -# STNHCRGSAP - Lower CRG SAP.
  -# STNHCPJSAP - Lower CPJ SAP.
  -# STNHPJUSAP - Lower PJU SAP.
  -# STNHCTFSAP - Lower CTF SAP.

Allowed action values for the action, subaction, and elmnt fields are
provided in the below table:

   @image html control-1.jpg
   @image html control-2.jpg
   @image html control-3.jpg

 */
EXTERN S16 NhMiLnhCntrlReq ARGS((Pst *pst, NhMngmt *cntrl));

/**
 * @details 
 *

This primitive is used by RRC to confirm the NhMiLnhCntrlReq primitive.
 *
* @param[in] pst Pointer to the pst structure.
* @param[in] cfm Pointer to management structure. 

The status information is returned in the CmStatus data structure of
NhMngmt. 

The valid values of the status parameter are:

   - LCM_PRIM_OK - Successful request.
   - LCM_PRIM_NOK - Unsuccessful request.

   When the status is set to LCM_PRIM_OK, the reason field is set to
   LCM_REASON_NOT_APPL. The other valid values are:

   - LRR_REASON_INVALID_ID        - Invalid node identifier. 
   - LCM_REASON_INVALID_ELMNT     - Invalid value of element field in the header.
   - LCM_REASON_INVALID_ACTION    - Invalid action in the control request.
   - LCM_REASON_INVALID_SUBACTION - Invalid subaction in the control request.
   - LCM_REASON_INVLID_PAR_VAL    - Invalid parameter value in the control request.
   - LCM_REASON_GENCFG_NOT_DONE   - The request failed because the general
                                  configuration is not done.

  SmMiLnhCntrlCfm is the function that processes this confirm primitive in the
  layer manager.
*/

EXTERN S16 NhMiLnhCntrlCfm ARGS((Pst *pst, NhMngmt *cfm));

/** @} */
#endif  /* NH */

#ifdef LCSMNHMILNH
EXTERN S16 cmUnpkLnhCfgCfm    ARGS((LnhCfgCfm func, Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLnhCntrlCfm  ARGS((LnhCntrlCfm func, Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLnhStaCfm    ARGS((LnhStaCfm func, Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLnhStaInd    ARGS((LnhStaInd func, Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLnhStsCfm    ARGS((LnhStsCfm func, Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLnhTrcInd    ARGS((LnhTrcInd func, Pst *pst, Buffer *mBuf));
#endif

#ifdef LCNHMILNH
EXTERN S16 cmUnpkLnhCfgReq    ARGS((LnhCfgReq func,Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLnhCntrlReq  ARGS((LnhCntrlReq func, Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLnhStaReq    ARGS((LnhStaReq func, Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLnhStsReq    ARGS((LnhStsReq func, Pst *pst, Buffer *mBuf));
#endif /* LCNHMILNH */

#ifdef LCSMNHMILNH
EXTERN S16 cmPkLnhCfgReq    ARGS((Pst *pst, NhMngmt *cfg));
EXTERN S16 cmPkLnhCntrlReq  ARGS((Pst *pst, NhMngmt *cntrl));
EXTERN S16 cmPkLnhStaReq    ARGS((Pst *pst, NhMngmt *sta));
EXTERN S16 cmPkLnhStsReq    ARGS((Pst *pst, Action action, NhMngmt *sts));
#endif /* LCSMNHMILNH */

#ifdef LCNHMILNH
EXTERN S16 cmPkLnhStaInd ARGS ((Pst *pst, NhMngmt *staInd));
EXTERN S16 cmPkLnhStaCfm ARGS ((Pst *pst, NhMngmt *cfm));
EXTERN S16 cmPkLnhStsCfm ARGS ((Pst *pst, NhMngmt *cfm));
EXTERN S16 cmPkLnhCfgCfm ARGS ((Pst *pst, NhMngmt *cfm));
EXTERN S16 cmPkLnhCntrlCfm ARGS ((Pst *pst, NhMngmt *cfm));
EXTERN S16 cmPkLnhTrcInd ARGS ((Pst *pst, NhMngmt *trcInd));
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __LNHX__ */



/********************************************************************30**

         End of file:     lnh.x@@/main/3 - Thu Jun 30 15:53:13 2011

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/

/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---              mc     1. LTE RRC release, version 2.1
/main/3      ---      lnh_x_001.main_2 mpatel 1. LTE RRC release, version 3.1
/main/4      ---           lnh_002.main_3 1.Added SS_DIAG. 
*********************************************************************91*/
