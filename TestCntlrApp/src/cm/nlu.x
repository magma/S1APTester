

/********************************************************************20**

     Name:     ESON Layer management

     Type:     

     Desc:     This file contains the 
               

     File:     nlu.x

     Sid:      nlu.x@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 15:11:19 2014

     Prg:      subhamay 

*********************************************************************21*/
#ifndef NLU_X_
#define NLU_X_

#ifdef __cplusplus
extern "C" {
#endif

/** @brief
    This Structure contains the PLMN information*/
typedef struct nluPlmnId
{
   U8      numMncDigits;       /*!< number of MNC digit, either 2 or 3 */
   U8      mcc[3];             /*!< MCC value */
   U8      mnc[3];             /*!< MNC value */
}NluPlmnId;

/** @brief
    This Structure contains the ECGI information*/
typedef struct nluEcgi
{
   NluPlmnId   plmn;            /*!< PLMN Id details */
   U32         cellId;          /*!< cell Id */
}NluEcgi;

/** @brief
    This Structure contains the PCI modification indication confirmation which will
    be sent to SON*/

typedef struct nluPciModIndCfm
{
   NluEcgi              ecgi;
   U16                  pci;
}NluPciModIndCfm;

/** @brief
    This Structure contains the neighbor information*/
typedef struct nluNghCellInfo
{
   NluEcgi     ecgi;            /*!< ECGI */
   U16         pci;             /*!< Physical cell Id */
   U16         dlEarfcn;        /*!< uplink frequency*/
   U16         ulEarfcn;        /*!< downlink frequency*/
}NluNghCellInfo;

typedef struct nluNghCellModInfo
{
   NluEcgi          oldEcgi;
   NluNghCellInfo   nghCellInfo;
   U8               numNghNgh;
   NluNghCellInfo   nghNghCellInfo[NLU_MAX_NGH_NGH_CELL_INFO];

}NluNghCellModInfo;

typedef struct nluNghCellMod
{
   U8                  numNgh;
   NluNghCellModInfo   nghCellModInfo[NLU_MAX_NGH_CELL_INFO];

}NluNghCellMod;

typedef struct nluNghCellDel
{
   U8                  numNgh;
   NluEcgi             ecgi[NLU_MAX_NGH_CELL_INFO];
}NluNghCellDel;

typedef struct nluNghCellAddInfo
{
   NluNghCellInfo   nghCellInfo;
   U8               numNghNgh;
   NluNghCellInfo   nghNghCellInfo[NLU_MAX_NGH_NGH_CELL_INFO];
}NluNghCellAddInfo;

typedef struct nluNghCellAdd
{
   U8                  numNgh;
   NluNghCellAddInfo   nghCellAddInfo[NLU_MAX_NGH_CELL_INFO];

}NluNghCellAdd;

typedef enum nluNghCfgType
{
   NLU_NGH_ADD,
   NLU_NGH_DEL,
   NLU_NGH_MOD
}NluNghCfgType;

typedef struct nluNghCellCfgParam
{
   NluNghCfgType   cfgType;
   union
   {
      NluNghCellAdd     nghCellAdd;
      NluNghCellDel     nghCellDel;
      NluNghCellMod     nghCellMod;
   }u;

}NluNghCellCfgParam;

typedef struct nluNghEnbCellCfg
{
   U32                nghEnbId;
   NluNghCellCfgParam nghCellParam;
}NluNghEnbCellCfg;

typedef enum nluNghMsgType
{
   NLU_X2SETUP_REQ_NGH_RPT,
   NLU_X2SETUP_RSP_NGH_RPT,
   NLU_ENB_CFG_UPD_NGH_RPT,
   NLU_ENB_ANR_NGH_RPT,
   NLU_ENB_DEL_NGH_RPT  
}NluNghMsgType;

/** @brief
    This Structure contains the neighbor report information*/
typedef struct nluNeighborReport
{
   NluNghMsgType      msgType;
   U32                servCellId;
   U8                 numNghEnb;
   NluNghEnbCellCfg   nghEnbCellCfg[NLU_MAX_NGH_ENB_CFG];
}NluNeighborReport;

/* Periodic REM for TPM */
typedef struct nluPeriodicRemCellInfo {
   U16                     pci;
   U8                      rsrp;
   U8                      dlBw;
   U8                      numTx;
}NluPeriodicRemCellInfo;

typedef struct nluPeriodicRemCellSearchRsp {
   U8    numCells;       /* Number of Cells */
   NluPeriodicRemCellInfo   cellInfo[NLU_REM_MAX_CELL_SEARCH];
}NluPeriodicRemCellSearchRsp;
/* Periodic REM for TPM End */

/*****************************************************************************/
/****************************** UE management ********************************/
/*****************************************************************************/
/** @brief
    TODO: re-write this documentation*/
typedef enum nluUeEvent
{
   NLU_UE_ADDED,    /*!< New UE added in APP*/
   NLU_UE_DELETED,   /*!< Existing UE deleted from APP*/
   NLU_UE_CRNTI_CHANGED   /*!< when UE CRNTI got changed 
                               due to Re-Establishment*/
}NluUeEvent;
/** @brief
    This Structure contains the UE information like UE addition/ deletion and send
    from APP to SON */
typedef struct nluUeInfo
{
   NluUeEvent         event;  /*!< indicate what type of events either add new 
                                   UE or delete UE*/
   NluEcgi            ecgi;   /*!< ECGI, cell to which the UE is attached */
   U16                crnti;  /*!< Unique identity of the UE */
   U16                oldCrnti;  /*!< Old Unique identity of the UE */
}NluUeInfo;

EXTERN S16 NlUiNluUeInd   ARGS((
   Pst                  *pst,      /*!< post structure*/
   SuId                  suId,     /*!< service user Id*/
   NluUeInfo            *ueInfo    /*!< UE information structure*/  
));


/*****************************************************************************/
/********************** UE Measurement reports management ********************/
/*****************************************************************************/

/** @brief
    This Structure contains the UE measurement information for neighbor cells
    send from APP to SON */
typedef struct nluNghCellMeasRpt
{
   NluEcgi   ecgi;         /*!< ECGI of neighbor cell*/
   S16       nghCellRsrp;  /*!< RSRP of neighbor cell*/
   S16       nghCellRsrq;  /*!< RSRQ of neighbor cell*/
   U16       pci;          /*!< PCI of neighbor cell*/
   U32       dlEarfcn;     /*!< DL-EARFCN of neighbor cell*/
}NluNghCellMeasRpt;

/** @brief
    This Structure contains the UE measurement information and send
    from APP to SON */
typedef struct nluUeMeasRpt
{
   NluEcgi            ecgi;   /*!< ECGI, unique Identity of the eNB */
   U16                crnti;  /*!< Unique identity of the UE */
#if 0   
   S16                nghCellRsrp;  /*!< RSRP of neighbor cell*/
   S16                servCellRsrp;  /*!< serv cell RSRP*/
   S8                 servCellRsrq;  /*!< serv cell RSRQ*/
#else
   U32                noNghCell;      /*!< number of neighbor cell*/
   NluNghCellMeasRpt  nghCellMeasRpt[NLU_MAX_NGH_CELL_INFO]; /*!< neighbor cell measurement reports*/
   U32                servCellRsrp;  /*!< serv cell RSRP*/
   U32                servCellRsrq;  /*!< serv cell RSRQ*/
#endif
}NluUeMeasRpt;

EXTERN S16 NlUiNluUeMeasReportInd   ARGS((
   Pst                  *pst,      /*!< post structure*/
   SuId                  suId,     /*!< service user Id*/
   NluUeMeasRpt         *measRpt   /*!< measurement report structure*/
));

/*****************************************************************************/
/************************* UE CQI reports management *************************/
/*****************************************************************************/
//#ifdef RGR_CQI_REPT
typedef struct rgrStaIndInfo   NluUeCqiRpt;
//#endif

EXTERN S16 NlUiNluUeCqiReportInd   ARGS((
   Pst                  *pst,     /*!< post structure*/
   SuId                  suId,    /*!< service user Id*/
   NluUeCqiRpt          *cqiRpt   /*!< UE CQI reporting structure*/
));

/** @brief
    pointer to function for sending bind request from eNB application to SON
    over NLU interface*/
typedef S16 (*NluBndReq) ARGS((
   Pst            *pst,   /*!< post structure */
   SuId           suId,   /*!< service user Id */
   SpId           spId    /*!< service provider Id */
));

/** @brief
    pointer to function for sending bind response from SON to eNB application
    over NLU interface*/
typedef S16 (*NluBndCfm) ARGS((
   Pst            *pst,   /*!< post structure */
   SuId           suId,   /*!< service user Id */
   SpId           spId,   /*!< service provider Id */
   U8             status  /*!< bind request status */
));

/** @brief
    pointer to function for sending report about new neighbor request 
    from eNB application to SON module over NLU interface*/
typedef S16 (*NluNeighborReq) ARGS((
   Pst                  *pst,      /*!< post structure */
   SuId                 suId,      /*!< service user Id */
   NluNeighborReport    *nhbr   /*!< message structure */
));

/** @brief
    pointer to function for sending PCI modification cfm
    from eNB application to SON module over NLU interface*/
typedef S16 (*NluPciModCfm) ARGS((
   Pst                  *pst,      /*!< post structure */
   SuId                 suId,      /*!< service user Id */
   NluPciModIndCfm      *pciMod    /*!< message structure */
));

/** @brief
    pointer to function for sending UE measurement report
    from eNB application to SON module over NLU interface*/

typedef S16 (*NluUeMeasRptInd) ARGS((
   Pst                  *pst,      /*!< post structure */
   SuId                 suId,      /*!< service user Id */
   NluUeMeasRpt         *measRpt   /*!< message structure */
));

/** @brief
    pointer to function for sending UE indication
    from eNB application to SON module over NLU interface*/

typedef S16 (*NluUeInd)   ARGS((
   Pst                  *pst,      /*!< post structure */
   SuId                 suId,      /*!< service user Id */
   NluUeInfo            *ueInfo    /*!< message structure */
));
/** @brief
    pointer to function for sending UE CQI report
    from eNB application to SON module over NLU interface*/
#ifdef RGR_CQI_REPT
typedef S16 (*NluUeCqiRptInd)   ARGS((
   Pst                  *pst,      /*!< post structure */
   SuId                 suId,      /*!< service user Id */
   NluUeCqiRpt          *cqiRpt    /*!< message structure */
));
#endif

/** @brief This primitive send bind request from
  * eNB application to SON over NLU interface
  * @details This primitive is used to bind bind the NLU interface 
  * between eNB application and SON
  */

EXTERN S16 WrLiNluBndReq ARGS((
   Pst *pst,     /*!< post structure */
   SuId suId,    /*!< service user Id */
   SpId spId     /*!< service provider Id */
));

/** @brief This primitive send PCI mod indication confirm from
  * eNB application to SON over NLU interface
  */
EXTERN S16 WrLiNluPciModIndCfm ARGS((
   Pst                 *pst,    /*!< post structure*/
   SuId                suId,    /*!< service user Id*/
   NluPciModIndCfm     *pciMod  /*!< PCI modification Indication structure*/
));

EXTERN S16 WrLiNluUeCqiRptInd   ARGS((
   Pst           *pst,      /*!< post structure*/
   SuId           suId,     /*!< service user Id*/
   NluUeCqiRpt   *cqiRpt    /*!< UE CQI Report Indication structure*/
));

EXTERN S16 WrLiNluUeMeasRptInd   ARGS((
   Pst           *pst,      /*!< post structure*/
   SuId           suId,     /*!< service user Id*/
   NluUeMeasRpt   *measRpt    /*!< UE Measurement Report Indication structure*/
));

/** @brief This primitive send neighbor request from
  * eNB application to SON over NLU interface
  * @details This primitive is used to send add new neighbor request over the NLU interface
  * between eNB application and SON
  */
EXTERN S16 WrLiNluNeighborReq ARGS((
   Pst                  *pst,      /*!< post structure*/
   SuId                  suId,     /*!< service user Id*/
   NluNeighborReport    *ueRep     /*!< new neighbor message structure*/
));

EXTERN S16 WrLiNluUeInd   ARGS((
   Pst           *pst,
   SuId           suId,
   NluUeInfo     *ueInfo
));


/** @brief This primitive pack the bind request sent from
  * eNB application to SON over NLU interface
  * @details This primitive is used to pack the bind request.bind request
  * is used to bind the NLU interface between eNB application and SON
  */
EXTERN S16 cmPkNluBndReq ARGS((
   Pst    *pst,    /*!< post structure */
   SuId    suId,   /*!< service user Id */
   SpId    spId    /*!< service provider Id */
));

/** @brief This primitive unpack the bind request sent from
  * eNB application to SON over NLU interface
  * @details This primitive is used to unpack the bind request.bind request
  * is used to bind the NLU interface between eNB application and SON
  */
EXTERN S16 cmUnpkNluBndReq ARGS((
   NluBndReq      func,    /*!< unpacking function to invoke */ 
   Pst            *pst,    /*!< post structure */
   Buffer         *mBuf    /*!< message buffer to be unpacked */
));

/** @brief This primitive pack the bind request sent from
  * eNB application to third party SON module over NLU interface
  * @details This primitive is used to pack the bind request.bind request
  * is used to bind the NLU interface between eNB application and SON
  */
EXTERN S16 ptUiNluBndReq ARGS((
Pst                 *pst,    /*!< post structure */
SuId                suId,    /*!< service user Id */
SpId                spId     /*!< service provider Id */
));

EXTERN S16 cmPkNluBndCfm ARGS((
Pst                 *pst,    /*!< post structure */
SuId                suId,    /*!< service user Id */
SpId                spId,    /*!< service provider Id*/
U8                  status   /*!< bind request status */
));

/** @brief This primitive unpack the bind confirm sent from
  * SON to eNB application over NLU interface
  * @details This primitive is used to unpack the bind confirm.bind confirm
  * is used to verify the success or failuer of the NLU interface binding 
  * between eNB application and SON
  */
EXTERN S16 cmUnpkNluBndCfm ARGS((
   NluBndCfm      func,    /*!< unpacking function to invoke */ 
   Pst            *pst,    /*!< post structure */
   Buffer         *mBuf    /*!< message buffer to be unpacked */
));

/** @brief This primitive pack the new neighbor report request sent from
  * eNB application to SON over NLU interface
  * @details This primitive is used to pack the new neighbor report request.
  */
EXTERN S16 cmPkNluNeighborReq ARGS((
Pst                   *pst,     /*!< post structure */
SuId                   suId,    /*!< service user Id */
NluNeighborReport     *nhbr     /*!< Report new neighbor message structure */
));

/** @brief This primitive pack the new neighbor report request sent from
  * eNB application to third party SON module over NLU interface
  * @details This primitive is used to pack the new neighbor report request.
  */
EXTERN S16 ptUiNluNeighborReq ARGS((
Pst                   *pst,     /*!< post structure */
SuId                   suId,    /*!< service user Id */
NluNeighborReport     *nhbr     /*!< Report new neighbor message structure */
));

/** @brief This primitive unpack the new neighbor report request sent from
  * eNB application to SON over NLU interface
  * @details This primitive is used to unpack the new neighbor report request.
  */
EXTERN S16 cmUnpkNluNeighborReq ARGS((
   NluNeighborReq      func,    /*!< unpacking function to invoke */
   Pst                 *pst,    /*!< post structure */
   Buffer              *mBuf    /*!< message buffer to be unpacked */
));

EXTERN S16 cmPkNluPciModIndCfm ARGS((
   Pst                 *pst,        /*!< post structure */
   SuId                suId,        /*!< service user Id */
   NluPciModIndCfm     *pciMod      /*!< Pci mod confirm message structure */
));


EXTERN S16 ptUiNluPciModIndCfm ARGS((
   Pst                 *pst,        /*!< post structure */
   SuId                 suId,       /*!< service user Id */
   NluPciModIndCfm      *pciMod     /*!< Pci mod confirm message structure */
));


/** @brief This primitive process the bind confirm message 
  * received from SON
  * @details This primitive process the bind confirm message
  * received from SON and stop the bind request timer
  */
EXTERN S16 WrLiNluBndCfm ARGS((
   Pst            *pst,   /*!< post structure */ 
   SuId           suId,   /*!< service user Id */
   SpId           spId,   /*!< service provider Id */
   U8             status  /*!< bind request status */
));

/** @brief This primitive process the bind request message
  * received from eNB APP
  * @details This primitive process the bind request message
  * received from eNB APP
  */
EXTERN S16 NlUiNluBndReq ARGS((
   Pst            *pst,   /*!< post structure */
   SuId           suId,   /*!< service user Id */
   SpId           spId    /*!< service provider Id */
));

/** @brief This primitive process the bind confirm message
  * received from SON
  * @details This primitive process the bind confirm message
  * received from SON and stop the bind request timer
  */
EXTERN S16 NlUiNluBndCfm ARGS((
   Pst            *pst,   /*!< post structure */
   SuId           suId,   /*!< service user Id */
   SpId           spId,   /*!< service provider Id */
   U8             status  /*!< bind request status */
));

/** @brief This primitive process the bind confirm message
  * received from SON
  * @details This primitive process the bind confirm message
  * received from SON and stop the bind request timer
  */
EXTERN S16 PtLiNluBndCfm ARGS((
   Pst            *pst,   /*!< post structure */
   SuId           suId,   /*!< service user Id */
   SpId           spId,   /*!< service provider Id*/
   U8             status  /*!< bind request status */
));

/** @brief This primitive process the new neighbor report request
  * received from eNodeB App
  * @details This primitive process the new neighbor report request from
  * eNB app and call the specific SON module mapping function
  * to inform the SON server
  */
EXTERN S16 NlUiNluNeighborReq ARGS((
   Pst                  *pst,     /*!< post structure */
   SuId                 suId,     /*!< service user Id */
   NluNeighborReport    *newNhbr  /*!< new neighbor report structure */
));

/** @brief This primitive unpack the PCI mod cfm sent from
  * eNB application to SON over NLU interface
  * @details This primitive is used to unpack the PCI mod cfm.
  */
EXTERN S16 cmUnpkNluPciModIndCfm ARGS((
   NluPciModCfm              func,    /*!< unpacking function to invoke */
   Pst                       *pst,    /*!< post structure */
   Buffer                    *mBuf    /*!< message buffer to be unpacked */
));

/** @brief This primitive process the PCI mod confirm
  * received from eNodeB App
  */
EXTERN S16 NlUiNluPciModIndCfm ARGS((
   Pst                  *pst,     /*!< post structure */
   SuId                 suId,     /*!< service user Id */
   NluPciModIndCfm      *pciMod   /*!< PCI mod confirm structure */
));

EXTERN S16 cmPkNluUeMeasReportInd   ARGS((
   Pst              *pst,      /*!< post structure */
   SuId             suId,      /*!< service user Id */
   NluUeMeasRpt     *measRpt   /*!< UE measurement report message structure */
));

EXTERN S16 cmUnpkNluUeMeasReportInd   ARGS((
   NluUeMeasRptInd     func,  /*!< primitive to call */
   Pst                 *pst,  /*!< post structure */
   Buffer              *mBuf  /*!< message buffer */
));


EXTERN S16 ptUiNluUeMeasReportInd   ARGS((
   Pst                 *pst,      /*!< post structure */
   SuId                suId,      /*!< service user Id */
   NluUeMeasRpt        *measRpt   /*!<UE measurement report message structure */
));

EXTERN S16 cmPkNluUeInd   ARGS((
   Pst              *pst,      /*!< post structure */
   SuId             suId,      /*!< service user Id */
   NluUeInfo        *ueInfo   /*!< UE indication message structure */
));

EXTERN S16 cmUnpkNluUeInd   ARGS((
   NluUeInd            func,  /*!< primitive to call */
   Pst                 *pst,  /*!< post structure */
   Buffer              *mBuf  /*!< message buffer */
));


EXTERN S16 ptUiNluUeInd   ARGS((
   Pst                 *pst,      /*!< post structure */
   SuId                suId,      /*!< service user Id */
   NluUeInfo           *ueInfo    /*!<UE indication message structure */
));

EXTERN S16 cmPkNluUeCqiReportInd   ARGS((
   Pst              *pst,      /*!< post structure */
   SuId             suId,      /*!< service user Id */
   NluUeCqiRpt      *cqiRpt    /*!< UE CQI report message structure */
));
#ifdef RGR_CQI_REPT
EXTERN S16 cmUnpkNluUeCqiReportInd   ARGS((
   NluUeCqiRptInd      func,  /*!< primitive to call */
   Pst                 *pst,  /*!< post structure */
   Buffer              *mBuf  /*!< message buffer */
));
#endif

EXTERN S16 ptUiNluUeCqiReportInd   ARGS((
   Pst                 *pst,      /*!< post structure */
   SuId                suId,      /*!< service user Id */
   NluUeCqiRpt         *cqiRpt    /*!<UE CQI report message structure */
));

/* Periodic REM scan for TPM */
/** @brief This primitive sends periodic REM scan results from
  * eNB application to SON over NLU interface
  * @details This primitive is used to send periodic REM scan results for TPM over the NLU interface
  * between eNB application and SON
  */
#if 0
EXTERN S16 cmUnpkNluPerCellSrchRsp ARGS((
   NluPeriodicRemCellSearchRsp    *cellSrchRsp,   /*!< cell search Response message structure*/
   Pst                            *pst,          /*!< post structure */
   Buffer                         *mBuf          /*!< message buffer to be unpacked */
));
#endif

/** @brief
    pointer to function for sending periodic REM scan results for TPM from SON
    to eNB application module over NLU interface*/
typedef S16 (*NluPerCellSrchRsp) ARGS((
   Pst                            *pst,          /*!< post structure*/
   SuId                           suId,          /*!< service user Id*/
   NluPeriodicRemCellSearchRsp    *cellSrchRsp   /*!< cell search Response message structure*/
));

EXTERN S16 cmUnpkNluPerCellSrchRsp ARGS((
NluPerCellSrchRsp   func,  /* primitive to call */
Pst                 *pst,  /* post structure */
Buffer              *mBuf  /* message buffer */
));

EXTERN S16 cmPkNluPerCellSrchRsp ARGS ((
Pst                             *pst,      /* post structure */
SuId                            suId,      /* service user Id */
NluPeriodicRemCellSearchRsp     *cellInfo  /* Report cell Info for Periodic REM */
));

EXTERN S16 WrLiNluPerCellSrchRsp ARGS ((
Pst *pst,
SuId suId,
NluPeriodicRemCellSearchRsp *cellSrchRsp
));

EXTERN S16 ptUiNluPerCellSrchRsp   ARGS((
Pst                             *pst,     /* post structure */
SuId                            suId,    /* service user Id */
NluPeriodicRemCellSearchRsp     *cellInfo  /* Report cell Info for Periodic REM */
));

EXTERN S16 NlUiNluPerdCellSrchRsp   ARGS((
Pst                           *pst,            /* post structure  */
SuId                          suId,            /* service user Id */
NluPeriodicRemCellSearchRsp   *cellSrchRsp     /* cell search response structure */
));

/* Periodic REM scan for TPM End */


#endif /* NLU_X_ */
/********************************************************************30**

           End of file:     nlu.x@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 15:11:19 2014

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
