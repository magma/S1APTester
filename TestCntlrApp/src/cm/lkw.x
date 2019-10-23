

/********************************************************************20**
  
        Name:    LKW RLC Layer Manager Interface
    
        Type:    C include file
  
        Desc:    This file Contains the Data structures and prototypes
                 for LKW Interface
 
        File:    lkw.x

        Sid:      lkw.x@@/main/3 - Fri Sep  2 18:24:17 2011
  
        Prg:     chakrapani
  
*********************************************************************21*/

#ifndef __LKW_X__
#define __LKW_X__

#ifdef __cplusplus
EXTERN "C" {
#endif  /* __cplusplus */


/** @brief
    General Configuration Structure. */
typedef struct kwGenCfg
{
   Pst               lmPst;         /*!< Post structure for communicating
                                      with LM. */
   U32               maxUe;         /*!< Maximum number of UEs supported
                                      by RLC. */
   U16               maxKwuSaps;    /*!< Maximum KWU SAPs. */
/* Supported by SPLIT Architecture */
   U16               maxUdxSaps;    /*!< Maximum Udx SAPs. */
/* Supported by SPLIT Architecture ends */
   Ticks             timeRes;       /*!< Time resolution. */
/* Supported by SPLIT Architecture */
   U8                rlcMode;       /*!< RLC_DL or RLC_UL */
/* Supported by SPLIT Architecture ends */
   U16               maxRguSaps;    /*!< Maximum RGU SAPs. */
}KwGenCfg;

/** @brief
    SAP Configuration Structure */
typedef struct kwSapCfg
{
   Selector          selector;      /*!< Selector for LC/TC. */
   MemoryId          mem;           /*!< Region and pool. */
   ProcId            procId;        /*!< Processor ID. */
   Ent               ent;           /*!< Entity ID. */
   Inst              inst;          /*!< Instance ID. */
   SpId              sapId;         /*!< SAP ID. */
   U16               bndTmrIntvl;   /*!< Bind timer interval. */
   Priority          priority;      /*!< Priority. */
   Route             route;         /*!< Route. */
}KwSapCfg;

/** @brief 
*   Configuration Structure 
*/
typedef struct kwCfg
{
   union
   {
      KwGenCfg       gen;           /*!< General configuraton. */
      KwSapCfg       sap;           /*!< SAP configuration. */
   }s;
}KwCfg;

/** @brief 
    General Statistics Structure */
typedef struct kwGenSts
{
   CntrSts           numUe;         /*!< Total number of UEs. */
   CntrSts           pdusRecv;      /*!< Number of PDUs received. */
   CntrSts           pdusSent;      /*!< Number of PDUs sent. */
   CntrSts           pdusRetx;      /*!< Number of PDUs retransmitted. */
   CntrSts           bytesRecv;     /*!< Number of bytes received. */
   CntrSts           bytesSent;     /*!< Number of bytes sent. */
   CntrSts           unexpPdusRecv; /*!< Unexpected PDU received. */
   CntrSts           errorPdusRecv; /*!< Format error pdus received. */
   CntrSts           protTimeOut;   /*!< Number of protocol time outs leading
                                         to retransmission. */
   CntrSts           numOfRb;       /*!< Total number of RBs in RLC. */
   CntrSts           numSduDisc;    /*!< Number of SDUs discarded. */
}KwGenSts;

/** @brief 
    RLC Upper SAP statistics */
typedef struct kwKwuSapSts 
{
   /* lkw_x_001.main_2, changed from suId to spId */
   SpId              spId;          /*!< Service  Provider ID. */
   CntrSts           sduRx;         /*!< Number of SDUs received. */
   CntrSts           sduTx;         /*!< Number of tranxmitted SDUs. */
}KwKwuSapSts;

/** @brief 
           RRC Control SAP Statistics */
typedef struct kwCkwCntSts
{
   CntrSts           statMsgs;      /*!< Number of Status Messages send. */
}KwCkwCntSts;

/** @brief 
    Statistics Structure */
typedef struct kwSts
{
   DateTime dt;                     /*!< Date and Time structure. */
   union
   {
      KwGenSts       gen;           /*!< General Statistics. */
      KwKwuSapSts    kwuSap;        /*!< RLC upper SAP statistics. */
      KwCkwCntSts    ckwSap;        /*!< RRC control SAP. */
   }s;
}KwSts;

/** @brief 
            MAC Upper SAP Status Structure */
typedef struct kwRguSapSta
{
   SuId              suId;          /*!< Service user ID. */
   State             state;         /*!< State of the SAP. */
}KwRguSapSta;

/** @brief 
    RLC Upper SAP Status Structure */
typedef struct kwKwuSapSta
{
   SpId              spId;          /*!< Service provider ID. */
   State             state;         /*!< State of the SAP. */
}KwKwuSapSta;

/** @brief 
    RRC Control SAP Status Structure */
typedef struct kwCkwCntSapSta
{
   SpId              spId;          /*!< Service provider ID. */
   State             state;         /*!< State of the SAP. */
}KwCkwCntSapSta;

/** @brief 
    Status Structure */
typedef struct kwSSta
{
   DateTime          dt;            /*!< Date and Time structure. */
   union
   {
      SystemId       sysId;         /*!< System ID. */
      KwRguSapSta    rguSap;        /*!< RLC lower SAP (MAC) status. */
      KwKwuSapSta    kwuSap;        /*!< RLC Upper SAP status. */
      KwCkwCntSapSta ckwSap;        /*!< RRC Control SAP Status. */
   }s;
}KwSSta;

/** @brief 
    Trace Control Structure */
typedef struct kwTrcCntrl
{
   U8                trcMask;       /*!< Trace mask. */
   S16               trcLen;        /*!< Trace length. */
}KwTrcCntrl;

/** @brief 
    Debug Control Structure */
typedef struct kwDbgCntrl
{
   U32               dbgMask;       /*!< Debug mask. Assign non zero value to enable 
                                         and zero to disable debug */
}KwDbgCntrl;

/** @brief 
    SAP Control Structure */
typedef struct kwSapCntrl
{
   SuId              suId;          /*!< Service user ID. */
   SpId              spId;          /*!< Service provider ID. */
}KwSapCntrl;

/** @brief 
    Control Structure */
typedef struct kwCntrl
{
   DateTime          dt;            /*!< Date and Time structure. */
   U8                action;        /*!< Action. */
   U8                subAction;     /*!< Sub action. */
   union
   {
      KwTrcCntrl     trcCntrl;      /*!< Trace Control Structure. */
      KwDbgCntrl     dbgCntrl;      /*!< Debug Control Structure. */
      KwSapCntrl     sapCntrl;      /*!< SAP Control Structure. */
#ifdef SS_DIAG
      U32            logMask;       /*!< Logging Control Structure. */
#endif
   }s;
}KwCntrl;

/** @brief 
    Unsolicited Status Structure */
typedef struct kwUSta
{
   DateTime          dt;            /*!< Date and Time structure. */
   CmAlarm           alarm;         /*!< Alarm. */
   SuId              suId;          /*!< Service user ID. */
   U32               ueId;          /*!< Urnti UE ID. */
  /* lkw_x_001.main_2, added support for L2 measurement */
#ifdef LTE_L2_MEAS
   U8                qci;           /*!< Qci value */
#endif
}KwUSta;

/** @brief 
    Trace Structure */
typedef struct kwTrc
{
   DateTime          dt;            /*!< Date and Time structure. */
   U16               event;         /*!< Event. Events defined in the differenct RLC
                                         interfaces are pssible values here.*/
}KwTrc;

/** @brief 
    Layer Management Structure */
typedef struct _kwMngmt
{
   Header            hdr;           /*!< Common header. */
   CmStatus          cfm;           /*!< Status of confirmation. */
   union 
   {
      KwCfg          cfg;           /*!< General Configuration. */
      KwCntrl        cntrl;         /*!< Control Structure. */
      KwSts          sts;           /*!< Statistics. */
      KwSSta         ssta;          /*!< Status. */
      KwUSta         usta;          /*!< Unsolicited Status. */
      KwTrc          trc;           /*!< Trace Structre. */
   }t;
}KwMngmt;

/* lkw_x_001.main_2, added support for L2 measurement */
#ifdef LTE_L2_MEAS

/** @brief Measurement Request Params Structure. */
typedef struct kwL2MeasReqInfo
{
   U8        measType;          /*!< Measurement type, bit 1 to 4 (LSB nibble) 
                                  will be used for non IP Throughput and 
                                  bit 5 and 6 will be used for DL and UL 
                                  Ipthroughput respectively */
   union
   {
      struct 
      {
         U16          numSamples;       /*!<Sampling period: */
         U8           numQci;           /*!<number of qCI to take measurement for */
         U8           qci[LKW_MAX_QCI]; /*!<QCI for the measurement */
      }nonIpThMeas;

      struct 
      {
         U16 numUes;
         struct 
         {
            U8           numQci;           /*!<number of qCI to take measurement for */
            U8           qci[LKW_MAX_QCI]; /*!<QCI for the measurement */
            CmLteRnti    ueId;             /*!< UE ID (Used only for IP Throughput in UL/DL */
            CmLteCellId  cellId;           /*!< Cell ID (Used only for IP Throughput in UL/DL */
         }ueInfoLst[LKW_MAX_UE];
      }ipThMeas;

   }val;
}KwL2MeasReqInfo;

/** @brief Measurement Request Exvent  Structure. */
typedef struct kwL2MeasReqEvt
{
   U32              transId;     /*!< Transaction Identifier */
   U16              measPeriod;  /*!< Measurement Period */
   KwL2MeasReqInfo  measReq;     /*!< Measurement request structure */
}KwL2MeasReqEvt;

/** @brief Measurement Confirm Params Structure. */
typedef struct kwL2MeasCfmInfo
{
   U8              qci;     /*!< QCI value */
   union
   {
      struct
      {
         U32   numActUe;   /*!< num of Active UEs*/
         U32   uuLoss;     /*!< Uu Loss Rate */
         /* Discard new changes starts */
         U32   dlDiscRate; /*!< DL Discard rate to be reported */
         /* Discard new changes ends */
         U32  dlSduDelay;
      }nonIpThrput;

      struct              /*!< Structure for IP throughput*/
      {
         F32   dlIpThPut; /*!< Scheduled DL IP throughput */
         F32   ulIpThPut; /*!< Scheduled UL IP throughput */
      }ipThrput;

   }val;
}KwL2MeasCfmInfo;

typedef struct kwL2MeasCfmUeInfoLst
{
   CmLteRnti       ueId;    /*!< UE Id used for DL/UL Ipthroughput*/
   CmLteCellId     cellId;  /*!< Cell Id used for DL/UL Ipthroughput*/
   KwL2MeasCfmInfo measCfm[LKW_MAX_QCI]; /*!< Measurement confirm structure*/
   U16             numCfm; /*!< Number of Measurement confirm*/
}KwL2MeasCfmUeInfoLst;

typedef struct kwL2MeasCfmIpThMeas
{
   U16                  numUes; /*!< Number of Ue Info*/
   KwL2MeasCfmUeInfoLst ueInfoLst[LKW_MAX_UE]; /*!< UE info list*/
}KwL2MeasCfmIpThMeas;

typedef struct kwL2MeasCfmNonIpThMeas
{
   U16             numCfm; /*!< Number of confirm */
   KwL2MeasCfmInfo measCfm[LKW_MAX_QCI]; /*!< Confirmation info */
}KwL2MeasCfmNonIpThMeas;

typedef union kwL2MeasCfmIpNonIp
{
   KwL2MeasCfmIpThMeas    ipThMeas;    /*!< Ip thrupt measurements*/
   KwL2MeasCfmNonIpThMeas nonIpThMeas; /*!< Non-Ip thrupt measurements*/
}KwL2MeasCfmIpNonIp;

/** @brief Measurement Confirm Event  Structure. */
typedef struct kwL2MeasCfmEvt
{
   U32             transId; /*!< Transaction id */
   CmStatus        status;  /*!< Status is for all QCIs */
   U8              measType; /*!< Measurement type, bit 1 to 4 (LSB nibble) 
                               will be used for non IP Throughput and 
                               bit 5 and 6 will be used for DL and UL 
                               Ipthroughput respectively. It is same for
                               all qci in this Cfm event. */
   KwL2MeasCfmIpNonIp val;
}KwL2MeasCfmEvt;

#endif /* LTE_L2_MEAS */

/* Control primitives towards LTE RLC */
/* Pointer functions to pack/unpack primitives */
typedef S16 (*LkwCfgReq)   ARGS((Pst *pst, KwMngmt *cfg));
typedef S16 (*LkwCfgCfm)   ARGS((Pst *pst, KwMngmt *cfgCfm));

typedef S16 (*LkwCntrlReq) ARGS((Pst *pst, KwMngmt *cntl));
typedef S16 (*LkwCntrlCfm) ARGS((Pst *pst, KwMngmt *cntlCfm));

typedef S16 (*LkwStaInd)   ARGS((Pst *pst, KwMngmt *staInd)); 
typedef S16 (*LkwStaReq)   ARGS((Pst *pst, KwMngmt *staReq));
typedef S16 (*LkwStaCfm)   ARGS((Pst *pst, KwMngmt *staCfm));

typedef S16 (*LkwStsReq)   ARGS((Pst *pst, Action, KwMngmt *sts));
typedef S16 (*LkwStsCfm)   ARGS((Pst *pst, Action, KwMngmt *stsCfm));

typedef S16 (*LkwTrcInd)   ARGS((Pst *pst, KwMngmt *trc, Buffer *mBuf));

/* lkw_x_001.main_2, added support for L2 measurement */
#ifdef LTE_L2_MEAS
typedef S16 (*LkwL2MeasReq)   ARGS((Pst *pst, KwL2MeasReqEvt *measEvt));
typedef S16 (*LkwL2MeasCfm)   ARGS((Pst *pst, KwL2MeasCfmEvt *measEvt));
typedef S16 (*LkwL2MeasSendReq)   ARGS((Pst *pst, U8 measType));
typedef S16 (*LkwL2MeasStopReq)   ARGS((Pst *pst, U8 measType));
typedef S16 (*LkwL2MeasStopCfm)   ARGS((Pst *pst, U8 measType,U8 status));
#endif /*  LTE_L2_MEAS */

/* Layer primitives */
/** @details This function processes configuration requests received from the layer manager.The configuration requests are general configuration, or configuration of RGU, KWU, and CKW SAPs. The type of the configuration request is determined from the elmId field in the header of the layer manager message.This function is called by the layer manager to configure RLC.

@param[in] pst  - Pointer to post structure
@param[in] cfg  - Configuration management structure
@return ROK if success , RFAILED if failure

*/
EXTERN S16 KwMiLkwCfgReq ARGS((Pst *pst, KwMngmt *cfg));

/**
@details This function is called by the KwMiLkwCfgReq function for responding to configuration requests.The cfm field in the KwMngmt  structure contains the response value.

@param[in] pst  - Pointer to post structure
@param[in] cfm  - Configuration management structure
@return ROK if success , RFAILED if failure
*/
EXTERN S16 KwMiLkwCfgCfm ARGS((Pst *pst, KwMngmt *cfgCfm));

/**
@details
The layer manager initiates and uses the management-control procedure to control
RLC elements.The RLC control request primitive (KwMiLkwCntrlReq) is called
more than once and at any time after the management-configuration procedure.The
control request primitive is confirmed by a KwMiLkwCntrlCfm primitive.

@param[in] pst  - Pointer to post structure
@param[in] cntl - Configuration management structure
@return ROK if success , RFAILED if failure
*/
EXTERN S16 KwMiLkwCntrlReq ARGS((Pst *pst, KwMngmt *cntl));

/**
@details
This function is called by the KwMiLkwCntrlReq function to send a control confirm to the layer management module.

@param[in] pst  - Pointer to post structure
@param[in] cfm  - Configuration management structure
@return ROK if success , RFAILED if failure
*/
EXTERN S16 KwMiLkwCntrlCfm ARGS((Pst *pst, KwMngmt *cntlCfm));

/**
@details
This function processes solicited status requests received from the layer manager.The layer manager can request status information regarding the system ID, RGSA
P,KWSAP, or CKSAP.

@param[in] pst  - Pointer to post structure
@param[in] cfg  - Configuration management structure
@return ROK if success , RFAILED if failure
*/
EXTERN S16 KwMiLkwStaReq ARGS((Pst *pst, KwMngmt *staInd));

/**
@details
This function is called by the KwMiLkwStaReq function to send the requested stat
us information to the layer manager.

@param[in] pst   - Pointer to post structure
@param[in] stacfm - Configuration management structure
@return ROK if success , RFAILED if failure
*/
EXTERN S16 KwMiLkwStaCfm ARGS((Pst *pst, KwMngmt *staCfm));

/**
@details
This function processes statistics requests received from the layer manager. After collecting the statistics, this function calls the statistics confirm function to send the statistics to the layer manager.

@param[in] pst   - Pointer to post structure  
@param[in] acton - action 
@param[in] sts   - Configuration management structure
@return ROK if success , RFAILED if failure
*/
EXTERN S16 KwMiLkwStsReq ARGS((Pst *pst, Action, KwMngmt *sts));
/**
@details
This function is called by the KwMiLkwStsReq function for responding to statisti
cs requests.

@param[in] pst   - Pointer to post structure
@param[in] action - action 
@param[in] cfg  - Configuration management structure
@return ROK if success , RFAILED if failure
*/
EXTERN S16 KwMiLkwStsCfm ARGS((Pst *pst, Action action, KwMngmt *stsCfm));
/**
@details
This function is used by RLC module to send unsolicited trace indications to
the layer manager, when tracing is enabled by the layer manager through a previous control request.

@param[in] pst  - Pointer to post structure
@param[in] cfg  - Configuration management structure
@param[in] buf  - buffer 
@return ROK if success , RFAILED if failure
*/
EXTERN S16 KwMiLkwTrcInd ARGS ((Pst *pst, KwMngmt *trc, Buffer *mBuf));

/**
@details This function is used by RLC to send unsolicited status information to the layer manager, when the unsolicited status flag is enabled by the layer manager through a previous control request.

@param[in] pst  - Pointer to post structure
@param[in] staReq - Configuration management structure
@return ROK if success , RFAILED if failure
*/
/* lkw_x_001.main_2, added support for L2 measurement */
#ifdef LTE_L2_MEAS
/**
@details This function is called by the Layer Manger function to request 
for Measurement  responding to statisti cs requests.

@param[in] pst  - Pointer to post structure
@param[in] measEvt - Measurement Request structure
@return ROK if success , RFAILED if failure
*/
EXTERN S16 KwMiLkwL2MeasReq ARGS((Pst *pst, KwL2MeasReqEvt *measEvt));
EXTERN S16 KwMiLkwL2MeasStopReq ARGS((Pst *pst,U8 measType));
EXTERN S16 KwMiLkwL2MeasSendReq ARGS((Pst *pst,U8 measType));
/**
@details This function can be used by PDCP to send the measurement values
after doing L2 measurement that was requested by the layer manager.

@param[in] pst  - Pointer to post structure
@param[in] measEvt - Measurement confirmation structure
@return ROK if success , RFAILED if failure
*/
EXTERN S16 KwMiLkwL2MeasCfm ARGS((Pst *pst, KwL2MeasCfmEvt *measCfm));
EXTERN S16 KwMiLkwL2MeasStopCfm ARGS((Pst *pst, U8 measType, U8 status));
#endif /*  LTE_L2_MEAS */

EXTERN S16 KwMiLkwStaInd ARGS((Pst *pst, KwMngmt *staReq));

EXTERN Void kwSendLmAlarm ARGS ((
      U16 category,
      U16  event,
      U16 cause,
      SuId suId,
      U32 ueId));

#ifdef SM
EXTERN S16 SmMiLkwCfgCfm   ARGS((
       Pst *,
       KwMngmt *
       ));

EXTERN S16 SmMiLkwCntrlCfm ARGS((
       Pst *,
       KwMngmt *
       ));

EXTERN S16 SmMiLkwStaInd   ARGS((
       Pst *,
       KwMngmt *
       ));

EXTERN S16 SmMiLkwStaCfm   ARGS((
       Pst *,
       KwMngmt *
       ));

EXTERN S16 SmMiLkwStsCfm   ARGS((
       Pst *,
       Action,
       KwMngmt *
       ));

EXTERN S16 SmMiLkwTrcInd   ARGS((
       Pst *,
       KwMngmt *,
       Buffer *
       ));

EXTERN S16 SmMiLkwStsReq   ARGS((
       Pst *,
       Action,
       KwMngmt *
       ));

EXTERN S16 SmMiLkwStaReq   ARGS((
       Pst *,
       KwMngmt *
       ));

EXTERN S16 SmMiLkwCntrlReq ARGS((
       Pst *,
       KwMngmt *
       ));

EXTERN S16 SmMiLkwCfgReq   ARGS((
       Pst *,
       KwMngmt *
       ));

/* lkw_x_001.main_2, added support for L2 measurement */
#ifdef LTE_L2_MEAS
EXTERN S16 SmMiLkwL2MeasReq   ARGS((
         Pst *,
         KwL2MeasReqEvt *
         ));
EXTERN S16 SmMiLkwL2MeasStopReq ARGS((
       Pst            *pst,
       U8             measType
      ));

EXTERN S16 SmMiLkwL2MeasSendReq ARGS((
         Pst            *pst,
         U8             measType
         ));
EXTERN S16 SmMiLkwL2MeasCfm   ARGS((
         Pst *,
         KwL2MeasCfmEvt *
         ));
EXTERN S16 SmMiLkwL2MeasStopCfm ARGS((
         Pst     *pst,          
         U8      measType,
         U8      status
         ));
#endif /*  LTE_L2_MEAS */
#endif

EXTERN S16 smKwActvInit    ARGS((Ent ent, Inst inst, Region region, Reason reason));
EXTERN S16 smKwActvTsk     ARGS((Pst *pst, Buffer *mBuf));

/* pack/unpack functions */
#ifdef LCLKW 
EXTERN S16 cmPkLkwCfgReq     ARGS((
       Pst *,
       KwMngmt *
       ));

EXTERN S16 cmPkLkwCfgCfm     ARGS((
       Pst *,
       KwMngmt *
       ));


EXTERN S16 cmPkLkwCntrlReq   ARGS((
       Pst *,
       KwMngmt *
       ));

EXTERN S16 cmPkLkwCntrlCfm   ARGS((
       Pst *,
       KwMngmt *
       ));

EXTERN S16 cmPkLkwStaInd     ARGS((
       Pst *,
       KwMngmt *
       ));

EXTERN S16 cmPkLkwStaReq     ARGS((
       Pst *,
       KwMngmt *
       ));

EXTERN S16 cmPkLkwStaCfm     ARGS((
       Pst *,
       KwMngmt *
       ));

EXTERN S16 cmPkLkwStsReq     ARGS((
       Pst *,
       Action,
       KwMngmt *
       ));

EXTERN S16 cmPkLkwStsCfm     ARGS((
       Pst *,
       Action,
       KwMngmt *
       ));

EXTERN S16 cmPkLkwTrcInd     ARGS((
       Pst *,
       KwMngmt *,
       Buffer *
       ));

EXTERN S16 cmUnpkLkwCfgReq   ARGS((
       LkwCfgReq,
       Pst *,
       Buffer *
       ));

EXTERN S16 cmUnpkLkwCfgCfm   ARGS((
       LkwCfgCfm,
       Pst *,
       Buffer *
       ));

EXTERN S16 cmUnpkLkwCntrlReq ARGS((
       LkwCfgReq,
       Pst *,
       Buffer *
       ));

EXTERN S16 cmUnpkLkwCntrlCfm ARGS((
       LkwCfgCfm,
       Pst *,
       Buffer *
       ));

EXTERN S16 cmUnpkLkwStaInd   ARGS((
       LkwStaInd,
       Pst *,
       Buffer *
       ));

EXTERN S16 cmUnpkLkwStaReq   ARGS((
       LkwStaReq,
       Pst *,
       Buffer *
       ));

EXTERN S16 cmUnpkLkwStaCfm   ARGS((
       LkwStaCfm,
       Pst *,
       Buffer *
       ));

EXTERN S16 cmUnpkLkwStsReq   ARGS((
       LkwStsReq,
       Pst *,
       Buffer *
       ));

EXTERN S16 cmUnpkLkwStsCfm   ARGS((
       LkwStsCfm,
       Pst *, Buffer *
       ));


EXTERN S16 cmUnpkLkwTrcInd   ARGS((
       LkwTrcInd,
       Pst *,
       Buffer *));

/* lkw_x_001.main_2, added support for L2 measurement */
#ifdef LTE_L2_MEAS
EXTERN S16 cmPkLkwL2MeasReq ARGS((
         Pst * pst,
         KwL2MeasReqEvt * measReqEvt
         ));
EXTERN S16 cmUnpkLkwL2MeasReq ARGS((
         LkwL2MeasReq func,
         Pst *pst,
         Buffer *mBuf
         ));
EXTERN S16 cmPkLkwL2MeasCfm ARGS((
         Pst * pst,
         KwL2MeasCfmEvt *measCfmEvt
         ));
EXTERN S16 cmUnpkLkwL2MeasCfm ARGS((
         LkwL2MeasCfm func,
         Pst *pst,
         Buffer *mBuf
         ));
EXTERN S16 cmPkKwL2MeasReqInfo ARGS((
         KwL2MeasReqInfo * measReqInfo,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkKwL2MeasReqInfo ARGS((
         KwL2MeasReqInfo * measReqInfo,
         Buffer *mBuf
         ));
EXTERN S16 cmPkKwL2MeasCfmInfo ARGS((
         KwL2MeasCfmInfo * measCfmInfo,
         Buffer *mBuf,
         U8 measType
         ));
EXTERN S16 cmUnpkKwL2MeasCfmInfo ARGS((
         KwL2MeasCfmInfo * measCfmInfo,
         Buffer *mBuf,
         U8 measType
         ));
EXTERN S16 cmPkLkwL2MeasStopReq ARGS((
         Pst * pst,
         U8 measType
         ));
EXTERN S16 cmUnpkLkwL2MeasStopReq ARGS((
         LkwL2MeasStopReq func,
         Pst *pst,
         Buffer *mBuf
         ));
EXTERN S16 cmPkLkwL2MeasSendReq ARGS((
         Pst * pst,
         U8 measType
         ));
EXTERN S16 cmUnpkLkwL2MeasSendReq ARGS((
         LkwL2MeasSendReq func,
         Pst *pst,
         Buffer *mBuf
         ));
EXTERN S16 cmPkLkwL2MeasStopCfm ARGS((
         Pst * pst,
         U8 measType,
         U8 status
         ));
EXTERN S16 cmUnpkLkwL2MeasStopCfm ARGS((
         LkwL2MeasStopCfm func,
         Pst *pst,
         Buffer *mBuf
         ));
#endif /*  LTE_L2_MEAS */

#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __LKW_X__ */

  
/********************************************************************30**
         End of file:     lkw.x@@/main/3 - Fri Sep  2 18:24:17 2011
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
/main/1      ---      avl         1. LTE RLC GA 3.1 Initial release.
*********************************************************************91*/
