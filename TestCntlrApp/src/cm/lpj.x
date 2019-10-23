

/********************************************************************20**
  
        Name:    PDCP Layer Manager Interface: LPJ
    
        Type:    C include file
  
        Desc:    This file Contains the Data structures and prototypes
                 for LPJ Interface
 
        File:    lpj.x

        Sid:      lpj.x@@/main/2 - Fri Sep  2 19:23:36 2011
  
        Prg:    rbabu 
  
*********************************************************************21*/

#ifndef __LPJ_X__
#define __LPJ_X__

#ifdef __cplusplus
EXTERN "C" {
#endif  /* __cplusplus */

#if (defined(KW_PDCP) || defined(TENB_SPLIT_ARCH))
/*typedef U32  CntrSts;*/
#if (defined(PJ_SEC_ASYNC) || defined (PJ_CMP_ASYNC))

/** @struct PjOBPst
 *  Post Info for Off-board Entities */
typedef struct pjObdPst
{
   Pst           cmpPst;                    /*!< Service user post structure
                                                 for compression */
   Pst           secPst;                    /*!< Service user post structure
                                                 for security algorithm */
}PjObdPst;
#endif /* PJ_SEC_ASYNC || PJ_CMP_ASYNC */

/** @brief
    General Configuration Structure. */
typedef struct pjGenCfg
{
   Pst               lmPst;         /*!< Post structure for communicating
                                         with LM. */
   Ticks             timeRes;       /*!< Time resolution. */
   U8                mode;      /*!< Pdcp mode DL / UL */
   U8                maxPjuSaps;    /*!< Number of PDCP Data SAPs */
   U8                maxKwuSaps;    /*!< Number of PDCP Data SAPs */
   U8                maxUdxSaps;    /*!< Number of Udx  SAPs */
   U8                nmbUlBins;     /*!< Number of bins which is used for 
                                         RxBuff to store */
   U8                nmbDlBins;     /*!< Number of bins which is used for 
                                         RxBuff to store */
   U32               maxUe;
#if (defined(PJ_SEC_ASYNC) || defined (PJ_CMP_ASYNC))
   S32               obdTmrInt;     /*!< Timer Interval used while 
                                         waiting for an output data from 
                                         Off-board entities */
   S32               obdWtTmrInt;   /*!< OBD wait timer used while opening
                                         and closing the context with 
                                         Off-board entities */
   PjObdPst          obdPst;        /*!< Post Information for off-board Interface */
#endif /* PJ_SEC_ASYNC || PJ_CMP_ASYNC */
}PjGenCfg;

/** @brief
    SAP Configuration Structure */
typedef struct pjSapCfg
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
}PjSapCfg;

/** @brief 
*   Configuration Structure 
*/
typedef struct pjCfg
{
   union
   {
      PjGenCfg       gen;           /*!< General configuraton. */
      PjSapCfg       sap;           /*!< SAP configuration. */
   }s;
}PjCfg;

/** @brief 
    General Statistics Structure */
typedef struct pjGenSts
{
   CntrSts           numUe;
   CntrSts           numOfRb;       /*!< Total number of RBs in PDCP */
   CntrSts           rxPdus;        /*!< Number of PDUs received Layer from RLC. */
   CntrSts           txPdus;        /*!< Number of PDUs sent to RLC. */
   CntrSts           errorPdusRecv; /*!< Format error PDUs received from RLC. */
   CntrSts           numSdusDisc;   /*!< Number of SDUs discarded due to PDCP
                                         discard timer expiry. */
   CntrSts           numCmpFails;     /*!< Number of Compression fails */
   CntrSts           numDecmpFails;   /*!< Number of Decompression fails */
   CntrSts           numIntgPrtFails; /*!< Number of Integration Protection fails */
   CntrSts           numIntgVrfFails; /*!< Number of Integration Verification fails */
   CntrSts           numCiphFails;    /*!< Number of Ciphering fails */
   CntrSts           numDeciphFails;  /*!< Number of Deciphering fails */
   CntrSts           numPdusDiscObdTmrExp;   /*!< Number of PDUs discarded in UL
                                                  due to Off-board timer expiry. */
   CntrSts           numSdusDiscObdTmrExp;   /*!< Number of SDUs discarded in DL
                                                  due to Off-board timer expiry. */
   CntrSts           numPktsFrwd;   /*!< Number of Packets forwarded to X2
                                         interface */
   CntrSts           numPktsRcvd;   /*!< Number of Packets recieved to X2
                                         interface */
}PjGenSts;

/** @brief 
    General Statistics Structure */
typedef struct pjPjuSts
{
   /* lpj_x_001.main_1 modified from suId to spId */
   SpId              spId;          /*!< Service provider ID. */
   CntrSts           rxSdus;        /*!< Number of SDUs received Layer from UL. */
   CntrSts           txSdus;        /*!< Number of SDUs sent to UL. */
}PjPjuSts;
/** @brief 
    Statistics Structure */
typedef struct pjSts
{
   DateTime       dt;               /*!< Date and Time structure. */
   union
   {
      PjGenSts       gen;           /*!< General Statistics. */
      PjPjuSts       pjuSap;        /*!< PJU SAP Statistics. */
   }s;
}PjSts;

/** @brief 
    PDCP Data Plane Upper SAP Status Structure */
typedef struct pjPjuSapSta
{
   SpId              spId;          /*!< Service provider ID. */
   State             state;         /*!< State of the SAP. */
}PjPjuSapSta;

/** @brief 
    PDCP Uplink Downlink SAP Status Structure */
typedef struct pjUdxSapSta
{
   SpId              spId;          /*!< Service provider ID. */
   State             state;         /*!< State of the SAP. */
}PjUdxSapSta;


/** @brief 
    PDCP Data Plane Upper SAP Status Structure */
typedef struct pjKwuSapSta
{
   SpId              spId;          /*!< Service provider ID. */
   State             state;         /*!< State of the SAP. */
}PjKwuSapSta;

/** @brief 
    PDCP Control Plane SAP Status Structure */
typedef struct pjCpjSapSta
{
   SpId              spId;          /*!< Service provider ID. */
   State             state;         /*!< State of the SAP. */
}PjCpjSapSta;

/** @brief 
    Status Structure */
typedef struct pjSSta
{
   DateTime          dt;            /*!< Date and Time structure. */
   union
   {
      SystemId       sysId;         /*!< System ID. */
      PjCpjSapSta    cpjSap;        /*!< PDCP Control plane Upper SAP Status. */
      PjPjuSapSta    pjuSap;        /*!< PDCP Data plane Upper SAP status. */
      PjKwuSapSta    kwuSap;        /*!< PDCP Data plane Upper SAP status. */
      PjUdxSapSta    udxSap;        /*!< PDCP Data plane Upper SAP status. */
   }s;
}PjSSta;

/** @brief 
    Trace Control Structure */
typedef struct pjTrcCntrl
{
   U8                trcMask;       /*!< Trace mask. */
   S16               trcLen;        /*!< Trace length. */
}PjTrcCntrl;

/** @brief 
    Debug Control Structure */
typedef struct pjDbgCntrl
{
   U32               dbgMask;       /*!< Debug mask. Assign non zero value to enable
                                          and zero to disable debug */
}PjDbgCntrl;

/** @brief 
    SAP Control Structure */
typedef struct pjSapCntrl
{
   SuId              suId;          /*!< Service user ID. */
   SpId              spId;          /*!< Service provider ID. */
}PjSapCntrl;

/** @brief 
    Control Structure */
typedef struct pjCntrl
{
   DateTime          dt;            /*!< Date and Time structure. */
   U8                action;        /*!< Action. */
   U8                subAction;     /*!< Sub action. */
   union
   {
      PjTrcCntrl     trcCntrl;      /*!< Trace Control Structure. */
      PjDbgCntrl     dbgCntrl;      /*!< Debug Control Structure. */
#ifdef SS_DIAG
      U32            logMask;       /*!< Logging Control Structure. */
#endif
      PjSapCntrl     sapCntrl;      /*!< Debug Control Structure. */
   }s;
}PjCntrl;

/** @brief 
    Unsolicited Status Structure */
typedef struct pjUSta
{
   DateTime          dt;            /*!< Date and Time structure. */
   CmAlarm           alarm;         /*!< Alarm. */
   SuId              suId;          /*!< Service user ID. */
   U32               ueId;          /*!< Urnti UE ID. */
  /* lpj_x_001.main_1 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
   U8                qci;           /*!< QCI */
#endif
}PjUSta;

/** @brief 
    Trace Structure */
typedef struct pjTrc
{
   DateTime          dt;            /*!< Date and Time structure. */
   U16               event;         /*!< Event. Events defined in the different PDCP
                                         interfaces are possible values here.*/
}PjTrc;

/** @brief 
    Layer Management Structure */
typedef struct _pjMngmt
{
   Header            hdr;           /*!< common header. */
   CmStatus          cfm;           /*!< Status of confirmation. */
   union 
   {
      PjCfg          cfg;           /*!< General Configuration. */
      PjCntrl        cntrl;         /*!< Control Structure. */
      PjSts          sts;           /*!< Statistics. */
      PjSSta         ssta;          /*!< Status. */
      PjUSta         usta;          /*!< Unsolicited Status. */
      PjTrc          trc;           /*!< Trace Structre. */
   }t;
}PjMngmt;

/* lpj_x_001.main_1 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
/** @brief Measurement Request Params Structure. */
typedef struct pjL2MeasReqInfo
{
   U16  measType;            /*!< Type of measurement */
   U8   numQci;              /*!< Number of qCI to take measurement for */
   U8   qci[LPJ_MAX_QCI];    /*!< QCI for the measurement */
}PjL2MeasReqInfo;

/** @brief Measurement Request Structure. */
typedef struct pjL2MeasReqEvt
{
   U32              transId;    /*!< Transaction identifier */
   U16              measPeriod; /*!< Time period of measurement */
   PjL2MeasReqInfo  measReq;    /*!< Measurement request */
}PjL2MeasReqEvt;

/** @brief Measurement Confirm Params Structure. */
typedef struct pjL2MeasCfmInfo
{
   U8     qci;      /*!< Qci */
   U32    dlDelay;  /*!< DL Delay */
   U32    dlDisc;   /*!< DL Discard */
   U32    ulLoss;   /*!< UL Loss */
   U32    ulBitRate; /*!< UL Data Plane Bit Rate*/
   U32    dlBitRate; /*!< DL Data Plane Bit Rate*/
   U32    dlCpBitRate;/*!<Dl Control Plane Bit Rate*/
   U32    ulCpBitRate;/*!<Ul Control Plane Bit Rate*/
}PjL2MeasCfmInfo;

/** @brief Measurement Confirm Structure. */
typedef struct pjL2MeasCfmEvt
{
   U32              transId; /*!< Transaction identifier */
   CmStatus         status;  /*!<Status */
   U16              measType; /*!< Measurement type */
   CmLteMemInfo     memoryInfo;
   U16              numQciCfm;  /*!< Number of confirm */
   PjL2MeasCfmInfo  measCfm[LPJ_MAX_QCI]; /*!< Measurement confirm */
   U16              numCores;
   CmLteCpuUtilInfo cmLteCpuInfo[CM_MAX_CPU_CORES]; 
}PjL2MeasCfmEvt;
#endif /*  LTE_L2_MEAS */

/* Control primitives towards LTE PDCP */
/* Pointer functions to pack/unpack primitives */
typedef S16 (*LpjCfgReq)   ARGS((Pst *pst, PjMngmt *cfg));
typedef S16 (*LpjCfgCfm)   ARGS((Pst *pst, PjMngmt *cfgCfm));

typedef S16 (*LpjCntrlReq) ARGS((Pst *pst, PjMngmt *cntl));
typedef S16 (*LpjCntrlCfm) ARGS((Pst *pst, PjMngmt *cntlCfm));

typedef S16 (*LpjStaInd)   ARGS((Pst *pst, PjMngmt *staInd)); 
typedef S16 (*LpjStaReq)   ARGS((Pst *pst, PjMngmt *staReq));
typedef S16 (*LpjStaCfm)   ARGS((Pst *pst, PjMngmt *staCfm));

typedef S16 (*LpjStsReq)   ARGS((Pst *pst, Action, PjMngmt *sts));
typedef S16 (*LpjStsCfm)   ARGS((Pst *pst, Action, PjMngmt *stsCfm));

typedef S16 (*LpjTrcInd)   ARGS((Pst *pst, PjMngmt *trc, Buffer *mBuf));

/* lpj_x_001.main_1 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
typedef S16 (*LpjL2MeasReq)   ARGS((Pst *pst, PjL2MeasReqEvt *measEvt));
typedef S16 (*LpjL2MeasCfm)   ARGS((Pst *pst, PjL2MeasCfmEvt *measEvt));
typedef S16 (*LpjL2MeasStopReq)   ARGS((Pst *pst, U16 measType));
typedef S16 (*LpjL2MeasSendReq)   ARGS((Pst *pst, U16 measType));
typedef S16 (*LpjL2MeasStopCfm)   ARGS((Pst *pst, U16 measType,U8 status));
#endif /*  LTE_L2_MEAS */
/* Layer primitives */
/** @details This function processes configuration requests received from the
 * layer manager.The configuration requests are general configuration, or
 * configuration of RGU, PJU, and PJU SAPs. The type of the configuration request is determined from the elmId field in the header of the layer manager message.This function is called by the layer manager to configure PDCP.

@param[in] pst  - Pointer to post structure
@param[in] cfg  - Configuration management structure
@return ROK if success , RFAILED if failure

*/
EXTERN S16 PjMiLpjCfgReq ARGS((Pst *pst, PjMngmt *cfg));

/**
@details This function is called by the PjMiLpjCfgReq function for responding to configuration requests.The cfm field in the PjMngmt structure contains the response value.

@param[in] pst  - Pointer to post structure
@param[in] cfm  - Configuration management structure
@return ROK if success, RFAILED if failure
*/
EXTERN S16 PjMiLpjCfgCfm ARGS((Pst *pst, PjMngmt *cfgCfm));

/**
@details
The layer manager initiates and uses the management-control procedure to control
PDCP elements.The PDCP control request primitive (PjMiLpjCntrlReq) can be called
more than once and at any time after the management-configuration procedure.The
control request primitive is confirmed by a PjMiLpjCntrlCfm primitive.

@param[in] pst  - Pointer to post structure
@param[in] cntl - Configuration management structure
@return ROK if success , RFAILED if failure
*/
EXTERN S16 PjMiLpjCntrlReq ARGS((Pst *pst, PjMngmt *cntl));

/**
@details
This function is called by the PjMiLpjCntrlReq function to send a control confirm to the layer management module.

@param[in] pst  - Pointer to post structure
@param[in] cfm  - Configuration management structure
@return ROK if success , RFAILED if failure
*/
EXTERN S16 PjMiLpjCntrlCfm ARGS((Pst *pst, PjMngmt *cntlCfm));

/**
@details
This function processes solicited status requests received from the layer manage
r.The layer manager can request status information regarding the system ID, RGSA
P,KWSAP, or CKSAP.

@param[in] pst  - Pointer to post structure
@param[in] cfg  - Configuration management structure
@return ROK if success , RFAILED if failure
*/
EXTERN S16 PjMiLpjStaReq ARGS((Pst *pst, PjMngmt *staInd));

/**
@details
This function is called by the PjMiLpjStaReq function to send the requested stat
us information to the layer manager.

@param[in] pst   - Pointer to post structure
@param[in] stacfm - Configuration management structure
@return ROK if success , RFAILED if failure
*/
EXTERN S16 PjMiLpjStaCfm ARGS((Pst *pst, PjMngmt *staCfm));

/**
@details
This function processes statistics requests received from the layer manager. Aft
er collecting the statistics, this function calls the statistics confirm functio
n to send the statistics to the layer manager.

@param[in] pst   - Pointer to post structure  
@param[in] acton - action 
@param[in] sts   - Configuration management structure
@return ROK if success , RFAILED if failure
*/
EXTERN S16 PjMiLpjStsReq ARGS((Pst *pst, Action, PjMngmt *sts));
/**
@details
This function is called by the PjMiLpjStsReq function for responding to statisti
cs requests.

@param[in] pst   - Pointer to post structure
@param[in] action - action 
@param[in] cfg  - Configuration management structure
@return ROK if success , RFAILED if failure
*/
EXTERN S16 PjMiLpjStsCfm ARGS((Pst *pst, Action action, PjMngmt *stsCfm));
/**
@details
This function can be used by PDCP module to send unsolicited trace indications to
the layer manager, when tracing is enabled by the layer manager through a previo
us control request.

@param[in] pst  - Pointer to post structure
@param[in] cfg  - Configuration management structure
@param[in] buf  - buffer 
@return ROK if success , RFAILED if failure
*/
EXTERN S16 PjMiLpjTrcInd ARGS ((Pst *pst, PjMngmt *trc, Buffer *mBuf));

/**
@details This function can be used by PDCP to send unsolicited status information t
o the layer manager, when the unsolicited status flag is enabled by the layer ma
nager through a previous control request.

@param[in] pst  - Pointer to post structure
@param[in] staReq - Configuration management structure
@return ROK if success , RFAILED if failure
*/
EXTERN S16 PjMiLpjStaInd ARGS((Pst *pst, PjMngmt *staReq));

/* lpj_x_001.main_1 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
/**
@details This function is called by the Layer Manger function to request 
for Measurement  responding to statisti cs requests.

@param[in] pst  - Pointer to post structure
@param[in] measEvt - Measurement Request structure
@return ROK if success , RFAILED if failure
*/
EXTERN S16 PjMiLpjL2MeasReq ARGS((Pst *pst, PjL2MeasReqEvt *measEvt));
EXTERN S16 PjMiLpjL2MeasStopReq ARGS((Pst *pst, U16 measType));
EXTERN S16 PjMiLpjL2MeasSendReq ARGS((Pst *pst, U16 measType));
EXTERN S16 PjMiLpjL2MeasStopCfm ARGS((Pst *pst, U16 measType, U8 status));
/**
@details This function can be used by PDCP to send the measurement values
after doing L2 measurement that was requested by the layer manager.

@param[in] pst  - Pointer to post structure
@param[in] measEvt - Measurement confirmation structure
@return ROK if success , RFAILED if failure
*/
EXTERN S16 PjMiLpjL2MeasCfm ARGS((Pst *pst, PjL2MeasCfmEvt *measCfm));
EXTERN S16 SmMiLpjL2MeasStopCfm ARGS((
Pst     *pst,          
U16      measType,
U8      status
));
EXTERN S16 PjMiLpjL2MeasStopCfm ARGS((  
Pst *pst,
U16  measType,
U8  status
));
#endif /*  LTE_L2_MEAS */

EXTERN Void pjSendLmAlarm ARGS ((U16 category,
      U16  event,
      U16 cause,
      SuId suId,
      U32 ueId));

#ifdef SM
EXTERN S16 SmMiLpjCfgCfm   ARGS((
       Pst *,
       PjMngmt *
       ));

EXTERN S16 SmMiLpjCntrlCfm ARGS((
       Pst *,
       PjMngmt *
       ));

EXTERN S16 SmMiLpjStaInd   ARGS((
       Pst *,
       PjMngmt *
       ));

EXTERN S16 SmMiLpjStaCfm   ARGS((
       Pst *,
       PjMngmt *
       ));

EXTERN S16 SmMiLpjStsCfm   ARGS((
       Pst *,
       Action,
       PjMngmt *
       ));

EXTERN S16 SmMiLpjTrcInd   ARGS((
       Pst *,
       PjMngmt *,
       Buffer *
       ));

EXTERN S16 SmMiLpjStsReq   ARGS((
       Pst *,
       Action,
       PjMngmt *
       ));

EXTERN S16 SmMiLpjStaReq   ARGS((
       Pst *,
       PjMngmt *
       ));

EXTERN S16 SmMiLpjCntrlReq ARGS((
       Pst *,
       PjMngmt *
       ));

EXTERN S16 SmMiLpjCfgReq   ARGS((
       Pst *,
       PjMngmt *
       ));

/* lpj_x_001.main_1 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
EXTERN S16 SmMiLpjL2MeasReq   ARGS((
       Pst *,
       PjL2MeasReqEvt *
       ));
EXTERN S16 SmMiLpjL2MeasCfm   ARGS((
       Pst *,
       PjL2MeasCfmEvt *
       ));
EXTERN S16 SmMiLpjL2MeasStopReq   ARGS((
       Pst *pst,
       U16  measType
       ));

EXTERN S16 SmMiLpjL2MeasSendReq   ARGS((
       Pst *pst,
       U16  measType
       ));
EXTERN S16 SmMiLpjL2MeasStopCfm   ARGS((
       Pst *pst,
       U16 measType,
       U8 stauts
       ));
#endif /*  LTE_L2_MEAS */
#endif

EXTERN S16 smPjActvInit    ARGS((Ent ent, Inst inst, Region region, Reason reason));
EXTERN S16 smPjActvTsk     ARGS((Pst *pst, Buffer *mBuf));

/* pack/unpack functions */
#ifdef LCLPJ 

EXTERN S16 cmPkLpjCfgReq ARGS((
Pst * pst,
PjMngmt * cfg
));
EXTERN S16 cmUnpkLpjCfgReq ARGS((
LpjCfgReq func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmPkLpjCfgCfm ARGS((
Pst * pst,
PjMngmt * cfgCfm
));
EXTERN S16 cmUnpkLpjCfgCfm ARGS((
LpjCfgCfm func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmPkLpjCntrlReq ARGS((
Pst * pst,
PjMngmt * cntl
));
EXTERN S16 cmUnpkLpjCntrlReq ARGS((
LpjCntrlReq func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmPkLpjCntrlCfm ARGS((
Pst * pst,
PjMngmt * cntlCfm
));
EXTERN S16 cmUnpkLpjCntrlCfm ARGS((
LpjCntrlCfm func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmPkLpjStaInd ARGS((
Pst * pst,
PjMngmt * staInd
));
EXTERN S16 cmUnpkLpjStaInd ARGS((
LpjStaInd func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmPkLpjStaReq ARGS((
Pst * pst,
PjMngmt * staReq
));
EXTERN S16 cmUnpkLpjStaReq ARGS((
LpjStaReq func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmPkLpjStaCfm ARGS((
Pst * pst,
PjMngmt * staCfm
));
EXTERN S16 cmUnpkLpjStaCfm ARGS((
LpjStaCfm func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmPkLpjStsReq ARGS((
Pst * pst,
Action actn,
PjMngmt * sts
));
EXTERN S16 cmUnpkLpjStsReq ARGS((
LpjStsReq func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmPkLpjStsCfm ARGS((
Pst * pst,
Action actn,
PjMngmt * stsCfm
));
EXTERN S16 cmUnpkLpjStsCfm ARGS((
LpjStsCfm func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmPkLpjTrcInd ARGS((
Pst * pst,
PjMngmt * trc,
Buffer * mBuf
));
EXTERN S16 cmUnpkLpjTrcInd ARGS((
LpjTrcInd func,
Pst *pst,
Buffer *mBuf
));
/* lpj_x_001.main_1 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
EXTERN S16 cmPkLpjL2MeasReq ARGS((
Pst * pst,
PjL2MeasReqEvt * measReqEvt
));
EXTERN S16 cmUnpkLpjL2MeasReq ARGS((
LpjL2MeasReq func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmPkLpjL2MeasStopReq ARGS((
Pst * pst,
U16 measType
));
EXTERN S16 cmUnpkLpjL2MeasStopReq ARGS((
LpjL2MeasStopReq func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmPkLpjL2MeasSendReq ARGS((
Pst * pst,
U16 measType
));
EXTERN S16 cmUnpkLpjL2MeasSendReq ARGS((
LpjL2MeasSendReq func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmPkLpjL2MeasCfm ARGS((
Pst * pst,
PjL2MeasCfmEvt *measCfmEvt
));
EXTERN S16 cmUnpkLpjL2MeasCfm ARGS((
LpjL2MeasCfm func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmPkPjL2MeasReqInfo ARGS((
PjL2MeasReqInfo * measReqInfo,
Buffer *mBuf
));
EXTERN S16 cmUnpkPjL2MeasReqInfo ARGS((
PjL2MeasReqInfo * measReqInfo,
Buffer *mBuf
));
EXTERN S16 cmPkPjL2MeasCfmInfo ARGS((
PjL2MeasCfmInfo * measCfmInfo,
Buffer *mBuf
));
EXTERN S16 cmPkPjL2MeasCpuCfmInfo ARGS((
CmLteCpuUtilInfo * measCpuCfmInfo,
Buffer *mBuf
)); 

EXTERN S16 cmPkPjL2MeasMemoryCfmInfo ARGS((
CmLteMemInfo *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkPjL2MeasCpuCfmInfo ARGS((
CmLteCpuUtilInfo * measCpuCfmInfo,
Buffer *mBuf
));
EXTERN S16 cmUnpkPjL2MeasMemoryCfmInfo ARGS((
CmLteMemInfo *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkPjL2MeasCfmInfo ARGS((
PjL2MeasCfmInfo * measCfmInfo,
Buffer *mBuf
));
EXTERN S16 cmPkLpjL2MeasStopReq ARGS((
Pst * pst,
U16  measType
));
EXTERN S16 cmUnpkLpjL2MeasStopReq ARGS((
LpjL2MeasStopReq func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmPkLpjL2MeasSendReq ARGS((
Pst * pst,
U16  measType
));
EXTERN S16 cmUnpkLpjL2MeasSendReq ARGS((
LpjL2MeasSendReq func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmPkLpjL2MeasStopCfm ARGS((
Pst * pst,
U16 measType,
U8 status
));
EXTERN S16 cmUnpkLpjL2MeasStopCfm ARGS((
LpjL2MeasStopCfm func,
Pst *pst,
Buffer *mBuf
));
#endif /*  LTE_L2_MEAS */

#if (defined(PJ_SEC_ASYNC) || defined (PJ_CMP_ASYNC))
EXTERN S16 cmPkPjObdPst ARGS((
PjObdPst *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkPjObdPst ARGS((
PjObdPst *param,
Buffer *mBuf
));
#endif /* PJ_SEC_ASYNC || PJ_CMP_ASYNC */

EXTERN S16 cmPkPjGenCfg ARGS((
PjGenCfg *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkPjGenCfg ARGS((
PjGenCfg *param,
Buffer *mBuf
));
EXTERN S16 cmPkPjSapCfg ARGS((
PjSapCfg *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkPjSapCfg ARGS((
PjSapCfg *param,
Buffer *mBuf
));
EXTERN S16 cmPkPjCfg ARGS((
PjMngmt *cfg,
Elmnt elmnt,
Buffer *mBuf
));
EXTERN S16 cmUnpkPjCfg ARGS((
PjMngmt *cfg,
Elmnt elmnt,
Buffer *mBuf
));
EXTERN S16 cmPkPjGenSts ARGS((
PjGenSts *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkPjGenSts ARGS((
PjGenSts *param,
Buffer *mBuf
));
EXTERN S16 cmPkPjPjuSts ARGS((
PjPjuSts *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkPjPjuSts ARGS((
PjPjuSts *param,
Buffer *mBuf
));
EXTERN S16 cmPkPjSts ARGS((
PjMngmt *sts,
Elmnt elmnt,
Buffer *mBuf
));
EXTERN S16 cmUnpkPjSts ARGS((
PjMngmt *sts,
Elmnt elmnt,
Buffer *mBuf
));
EXTERN S16 cmPkPjPjuSapSta ARGS((
PjPjuSapSta *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkPjPjuSapSta ARGS((
PjPjuSapSta *param,
Buffer *mBuf
));
EXTERN S16 cmPkPjCpjSapSta ARGS((
PjCpjSapSta *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkPjCpjSapSta ARGS((
PjCpjSapSta *param,
Buffer *mBuf
));
EXTERN S16 cmPkPjSSta ARGS((
PjMngmt *ssta,
Elmnt elmnt,
Event eventType,
Buffer *mBuf
));
EXTERN S16 cmUnpkPjSSta ARGS((
PjMngmt *ssta,
Elmnt elmnt,
Event eventType,
Buffer *mBuf
));
EXTERN S16 cmPkPjTrcCntrl ARGS((
PjTrcCntrl *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkPjTrcCntrl ARGS((
PjTrcCntrl *param,
Buffer *mBuf
));
EXTERN S16 cmPkPjDbgCntrl ARGS((
PjDbgCntrl *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkPjDbgCntrl ARGS((
PjDbgCntrl *param,
Buffer *mBuf
));
EXTERN S16 cmPkPjCntrl ARGS((
PjMngmt *cntrl,
Elmnt elmnt,
Buffer *mBuf
));
EXTERN S16 cmUnpkPjCntrl ARGS((
PjMngmt *cfm,
Elmnt elmnt,
Buffer *mBuf
));
EXTERN S16 cmPkPjUSta ARGS((
PjMngmt *usta,
Elmnt elmnt,
Buffer *mBuf
));
EXTERN S16 cmUnpkPjUSta ARGS((
PjMngmt *usta,
Elmnt elmnt,
Buffer *mBuf
));
EXTERN S16 cmPkPjTrc ARGS((
PjMngmt *trc,
Buffer *mBuf
));
EXTERN S16 cmUnpkPjTrc ARGS((
PjMngmt *trc,
Buffer *mBuf
));
EXTERN S16 cmPkPjMngmt ARGS((
PjMngmt *param,
Event eventType,
Buffer *mBuf
));
EXTERN S16 cmUnpkPjMngmt ARGS((
PjMngmt *param,
Event eventType,
Buffer *mBuf
));

#endif
#endif /* TENB_SPLIT_ARCH */
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __LPJ_X__ */

  
/********************************************************************30**
         End of file:     lpj.x@@/main/2 - Fri Sep  2 19:23:36 2011
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
