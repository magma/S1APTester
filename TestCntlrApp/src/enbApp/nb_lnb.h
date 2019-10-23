/**********************************************************************

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     nb_lnb.h

     Sid:      

     Prg:      

*********************************************************************21*/
#ifndef __NB_LNB_H__
#define __NB_LNB_H__

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */
/* LwrAddModMmeCfg bitmaps for structure elements */
#define LNB_MME_INDEX                             1
#define LNB_PLMN_ID                               2
#define LNB_MME_GROUP_ID                          4
#define LNB_MME_CODES                             8
#define LNB_MME_IPADDR                            16
#define LNB_MME_SECIP_ADDR                        32
#define LNB_MME_STATE                             64
#define LNB_ADMIN_STATE                           128
#define LNB_MAX_IP_PER_MME                        5 

/*****************************************************************************
 ****************************************************************************/ 
#define LNB_SEL_LC 1
#define LNB_SEL_LWLC 2
/* Element types */

#define LNB_MAX_PLMNS_PER_MME                     32 
#define LNB_MAX_GROUPS_PER_MME                    6
#define LNB_MAX_CODES_PER_MME                     6 
#define LNB_MAX_ENODEB_POOLS                      6
#define LNB_MAX_MMES                              16
#define LNB_MAX_PLMN_IDS                          6
   
#define LNB_SM_MAX_MMES                           16
#define LNB_SM_MAX_EAIDS                          15
#define LNB_SM_MAX_PLMN_IDS                       6

/*Protocol Configuration Count*/
#define LNB_MAX_PROTOCOL_CFG_COUNT  7

/* Interface Events */
#define EVTLNBCFGREQ                              1       /* Config request */
#define EVTLNBCFGCFM                              2       /* Config Confirm */
#define EVTLNBCNTRLREQ                            3       /* Control Request */
#define EVTLNBCNTRLCFM                            4       /* Control Confirm */
#define EVTLNBSTAIND                              5       /* Status Indication */
#define EVTSMSTATICCFG                            6      /* send static cfg req */
  
/*----------------- State Of SAP ------------------*/

#define LNB_SAP_UNBOUND                           1
#define LNB_SAP_BINDING                           2
#define LNB_SAP_BOUND                             3

#define EWRXXX 0



/**********************************************************************
 cause field values in cmAlarm
**********************************************************************/
#define LNB_CAUSE_SZT_SAP_BOUND          (LCM_CAUSE_LYR_SPECIFIC + 4)
#define LNB_CAUSE_EGT_SAP_BOUND          (LCM_CAUSE_LYR_SPECIFIC + 5)
#define LNB_EVENT_S1CON_SET_SUCCESS      (LCM_CAUSE_LYR_SPECIFIC + 3)
#define LNB_EVENT_S1CON_SET_FAIL         (LCM_CAUSE_LYR_SPECIFIC + 4)
#define LNB_EVENT_ERRIND_FROM_PEER       (LCM_CAUSE_LYR_SPECIFIC + 7)
#define LNB_EVENT_ERR_IND_RCVD           (LCM_CAUSE_LYR_SPECIFIC + 8)
/*S1-U Interface Related Events*/
#define LNB_EVENT_SEND_ALARM             (LCM_CAUSE_LYR_SPECIFIC + 27)


#define LNB_TIMER_CFG_S1SETUP             1       /* S1 setup */

   
/*----------------- State Of SAP ------------------*/

#define LNB_SAP_UNBOUND             1
#define LNB_SAP_BINDING             2
#define LNB_SAP_BOUND               3

#define ELWRXXX         0
/********************************************************
 *           Transation Id for static configuration     *
 *******************************************************/
#define LNB_TRANSID_GEN                       1000
#define LNB_TRANSID_EGT                       (LNB_TRANSID_GEN + 4)
#define LNB_TRANSID_SZT                       (LNB_TRANSID_GEN + 5)
#define LNB_TRANSID_MME                       (LNB_TRANSID_GEN + 10)
/***************************************************************
 *                       Element Macros                        *
 ***************************************************************/
#define STNBGEN                                   1
#define STNBSZTSAP                                5
#define STNBS1CONSETUP                            7
#define STNBEGTSAP                                8

/*******************************************************
 *         Protocol macros                             *
 *******************************************************/

 
#define LNB_MAX_GU_GRP_IDS                        16


 
/* operations */
#define LNB_CELLCONFIG  1

#define LNB_USTA_DGNVAL_SAP  0
#define LNB_USTA_DGNVAL_CELLUEID  1
#define LNB_USTA_DGNVAL_ALARM     2

#define LNB_CAUSE_CELL_UP  100
/* operations */
#define LNB_CELLCONFIG  1

/* lve_h_001.main_2: Added maximum file path */
#ifdef NB_SM_LOG_TO_FILE
#define LNB_MAX_FILE_PATH 256
#endif

#define MAX_GP_PREF                        16

#define ELWRXXX         0

#define ERRLWR          0

#define   ELWR001              (ERRLWR + 1)
#define   ELWR002              (ERRLWR + 2)
#define   ELWR003              (ERRLWR + 3)
#define   ELWR004              (ERRLWR + 4)
#define   ELWR005              (ERRLWR + 5)
#define   ELWR006              (ERRLWR + 6)
#define   ELWR007              (ERRLWR + 7)
#define   ELWR008              (ERRLWR + 8)
#define   ELWR009              (ERRLWR + 9)
#define   ELWR010              (ERRLWR + 10)
#define   ELWR011              (ERRLWR + 11)
#define   ELWR012              (ERRLWR + 12)
#define   ELWR013              (ERRLWR + 13)
#define   ELWR014              (ERRLWR + 14)
#define   ELWR015              (ERRLWR + 15)
#define   ELWR016              (ERRLWR + 16)
#define   ELWR017              (ERRLWR + 17)
#define   ELWR018              (ERRLWR + 18)
#define   ELWR019              (ERRLWR + 19)
#define   ELWR020              (ERRLWR + 20)
#define   ELWR021              (ERRLWR + 21)
#define   ELWR022              (ERRLWR + 22)
#define   ELWR023              (ERRLWR + 23)
#define   ELWR024              (ERRLWR + 24)
#define   ELWR025              (ERRLWR + 25)
#define   ELWR026              (ERRLWR + 26)
#define   ELWR027              (ERRLWR + 27)
#define   ELWR028              (ERRLWR + 28)
#define   ELWR029              (ERRLWR + 29)
#define   ELWR030              (ERRLWR + 30)
#define   ELWR031              (ERRLWR + 31)
#define   ELWR032              (ERRLWR + 32)
#define   ELWR033              (ERRLWR + 33)
#define   ELWR034              (ERRLWR + 34)


#define NB_MAX_PLMN           6 
#define LNB_MAX_CONN          16


//#define SM_MAX_CFG_SIZE 20000
//#define SM_MAX_CFG_SIZE 30000

#define LNB_GEN_TRANSID(_transId, _cfg, _trans)                   \
{                                                                 \
   _trans ++;                                                     \
  _transId = ((_cfg & 0x0000ffff) << 16) | (_trans & 0x0000ffff); \
}
typedef struct  lnbSctpParamCfg
{
   U32 mmeFailoverTimer;
   U32 heartBeatInterval;
   U32 numPathReTx;
   U32 rtoInitial;
   U32 rtoMin;
   U32 rtoMax;
   U32 connectInterval;
}LnbSctpParamCfg;

typedef struct _lnbSmMmeCfg
{  
   U16          mmeId;
   U8           noOfIps;
   U32          mmeAddr[LNB_MAX_IP_PER_MME];
} LnbSmMmeCfg;


typedef struct lnbPlmnId
{
   U8             numMncDigits;   /*!< Number of digits in the MNC */
   U8             mcc[3];   /*!< Mobile country code */
   U8             mnc[3];   /*!< Mobile country code */
} LnbPlmnId;

typedef struct lnbMmePlmnCfg
{
   TknPres        pres;   /*!< Presence for fields below */
} LnbMmePlmnCfg;

/** @brief This structure has the information necessary for the addition or
 * Reconfiguration of a MME to the EnodeB. 
 * @todo the first parameter i.e. the mmeIndex is the value that should be know
 * by both the EnodeB Application and the stack manager the reason for this
 * extra parameter is that all other identities such as mmeGi, mmeCode can
 * potentially be reconfigured hence we do need a unique identification for the
 * MME and this is the purpose served by the mmeIndex. 
 */

 typedef enum lnbMmeState
 {
    NB_MME_STATE_ACTIVE,   /*!< MME state is Active */
    NB_MME_STATE_INACTIVE     /*!< MME state is inactive */
 }LnbMmeState;

typedef struct lnbAddModMmeCfg
{
   U32               reCfgType;
   U8                mmeIndex;   /*!< Index of the MME being (re)configured */
   U8                peerId;   /*!< Index of the MME being (re)configured */
   U8                noOfIps; /*!< Total number of IP addresses configured */ 
   CmTptAddr         ipAddr[LNB_MAX_IP_PER_MME];     /*!< Primary IP address */
   LnbMmeState       mmeState;   /*!< State of MME */
} LnbAddModMmeCfg;

typedef enum lwrEnbType
{
   NB_ENODEB_TYPE_MACRO,
   NB_ENODEB_TYPE_HOME
} LwrEnbType;

typedef struct lnbGenCfg
{
   Pst      lmPst;  
   CmTptAddr dataAppAddr;
   U8          eNBType;
   U16         noOfNghInfo;
   U8          noOfguGrp; /* MAX of 16 group items are possible */
   U32         inactvTmrVal;/* UE Inactivity timer value */
   U32         expiryCnt; /* UE Inactivity timer expiry count */
   U32         endMrkTmrVal;/* End Marker timer value */
   Ticks       timeRes;       /* Time resolution */
   U16         cellId;
   U8          mmeId;
   U32         mmeAddr;
   U16         trackAreaCode;
   LnbPlmnId   plmnId;
   U16         s1SetUpTmrVal;
} LnbGenCfg;


typedef struct lnbLSapCfg
{
   SuId        suId;      
   SpId        spId;   
   Ent         srcEnt;
   Inst        srcInst;
   ProcId      dstProcId; 
   Ent         dstEnt;    
   Inst        dstInst;   
   Priority    dstPrior;  
   Route       dstRoute;  
   Selector    dstSel;    
   Mem         mem;
   U8          maxBndRetry;
   TmrCfg      bndTmr;    
   TmrCfg      connTmr;   
} LnbLSapCfg;

typedef struct lnbCfg
{
   union
   {
      LnbGenCfg    genCfg;   /*!< General configuration */
      LnbLSapCfg   lSap;   /*!< General configuration */
   }t;
} LnbCfg;
typedef struct lnbDbgCntrl 
{
   U32       dbgMsk;                       /*!< Debug Mask parameter. 
                                             This field can be set to a 
                                             combination of the below allowed 
                                             values by using OR "|" operator.
                                             For example, if the 
                                             debug and info debugging prints  
                                             to be enabled/disabled, the dbgMask
                                             is set to "LNB_DBGMASK_INFO|
                                             LNB_DBGMASK_DBG".
                                             <b> Allowed values </b>
                                             - LNB_DBGMASK_INFO
                                             To print specific behaviour
                                             /logic flow.
                                             - LNB_DBGMASK_DBG
                                             To print extensive logs.
                                             - LNB_DBGMASK_PARAM
                                             To print function
                                             parameters values.
                                             - LNB_DBGMASK_ERROR
                                             To print in error legs.
                                             - LNB_DBGMASK_FATAL
                                             To print any system effecting
                                             errors such as resouce
                                             unavailability.
                                             */

#ifdef NB_SM_LOG_TO_FILE
   Txt       filePath[LNB_MAX_FILE_PATH];  /*!< Path to store log files. */  
   U32       nmbDbgLines;                  /*!< Number of lines per Debug file. */
#endif /* NB_SM_LOG_TO_FILE */
} LwrDbgCntrl;

typedef struct _lnbCntrl
{
   Action    action;    
   Action    subAction; 
   U8        numConn;
   U32       peerId[LNB_MAX_CONN];
   U32       idLst[LNB_MAX_CONN];
   
   union
   {
      SpId       sapId; 
#ifdef DEBUGP
      U32        dbgMask;
      LwrDbgCntrl dbg;/*!< The layer manager can selectively enable
                                          or disable various levels of debug 
                                          printing. */
#endif
      U8         oper;
      U32        logMask; /* logging Mask control */
   } u;

} LnbCntrl;

typedef struct lwrUstaDgn
{
   U8    type;
   union
   {
      SpId     sapId;
      struct {
         U16     udId;
         U16     cellId;
      }s;
      struct{
         U32 alarmId;
         U8  severity;     
         U8  causeType;
         U8  causeVal;
      }alarm;
   }u;
} LwrUstaDgn;

typedef struct lwrUsta
{
   CmAlarm     alarm;
   LwrUstaDgn   dgn;   /*!< Diagnostic */
} LwrUsta;


typedef enum nbMmeStatus
{
    NB_MME_IDLE = 0,
   NB_MME_ACTIVE
}NbMmeStatus;


typedef struct nbMmeSta
{  U32             numMme;
   U32             mmeIdx[16]; //TODO replace by NB_MAX_MMES
   NbMmeStatus     mmeUsageState[16];
}NbMmeSta;


typedef struct nbS1USta
{
    U32 s1UStat;
}NbS1USta;

/**
 * @brief
   This structure holds Wr's solicited status information. */
typedef struct lnbSta
{
   DateTime dt;             /*!< Date and time */
   U8       sapInst;        /*!< SAP instance */
   union
   {
      NbMmeSta nbMmeSta;
      NbS1USta  nbS1Usta;
   }s;
}LnbSta;


/**
 * @brief
   This structure holds Wr's statistical information. */
typedef struct lnbSts
{
   DateTime dt;          /*!< Date and Time. */
   U8       sapInst;     /*!< SAP instance. */
   Action   action;      /*!< Action on Trafffic load related statistic values.
                              ARST: To reset the statistic values. */
}LnbSts;

typedef struct lnbUstaDgn
{
   U8    type;
   union
   {
      SpId     sapId;
      struct {
         U16     udId;
         U16     cellId;
      }s;
      struct{
         U32 alarmId;
         U8  severity;     
         U8  causeType;
         U8  causeVal;
      }alarm;
   }u;
} LnbUstaDgn;
typedef struct lnbUsta
{
   CmAlarm     alarm;
   LnbUstaDgn   dgn;   /*!< Diagnostic */
} LnbUsta;

typedef struct _lnbMngmt
{
   Header            hdr;    /*!< Header for struct */
   CmStatus          cfm;    /*!< Confirmation of the result of operation */
   union
   {
      LnbCfg          cfg;     /*!< Configuration for WR in terms TAPA */
      LnbCntrl        cntrl;   /*!< Control for WR in terms of TAPA */
      LnbUsta         usta;    /*!< Alarms etc */
      LnbSts          sts;     /*!< Statistics */
      LnbSta          sta;     /*!< Solicited Status */
   }t;
}LnbMngmt;

typedef S16 (*LnbCfgReq)   (
Pst      *pst, 
LnbMngmt *cfg
);

typedef S16 (*LnbCfgCfm)   (
Pst      *pst, 
LnbMngmt *cfg
);

typedef S16 (*LnbCntrlReq) (
Pst      *pst, 
LnbMngmt *cntrl
);

typedef S16 (*LnbCntrlCfm) (
Pst      *pst, 
LnbMngmt *cntrl
);

typedef S16 (*LnbStaInd) (
Pst      *pst,
LnbMngmt *sta
);

EXTERN S16 NbMiLnbCfgReq      (Pst *pst, LnbMngmt *cfg);
EXTERN S16 cmPkLnbCfgReq      (Pst *pst, LnbMngmt *cfg);

EXTERN S16 NbMiLnbCfgCfm      (Pst *pst, LnbMngmt *cfg);
EXTERN S16 cmPkLnbCfgCfm      (Pst *pst, LnbMngmt *cfg);

EXTERN S16 NbMiLnbCntrlReq    (Pst *pst, LnbMngmt *cntrl);
EXTERN S16 cmPkLnbCntrlReq    (Pst *pst, LnbMngmt *cntrl);

EXTERN S16 NbMiLnbCntrlCfm    (Pst *pst, LnbMngmt *cntrl);
EXTERN S16 cmPkLnbCntrlCfm    (Pst *pst, LnbMngmt *cntrl);

EXTERN S16 NbMiLnbStaInd      (Pst *pst, LnbMngmt *sta);
EXTERN S16 cmPkLnbStaInd      (Pst *pst, LnbMngmt *sta);



/*---- Layer manager interface primitives ----*/
#ifdef EU_DAT_APP
EXTERN S16 NbMiLnbCfgReq      (Pst *pst, LnbMngmt *cfg);
EXTERN S16 NbMiLnbCfgCfm      (Pst *pst, LnbMngmt *cfg);
EXTERN S16 NbMiLnbCntrlReq    (Pst *pst, LnbMngmt *cntrl);
EXTERN S16 NbMiLnbCntrlCfm    (Pst *pst, LnbMngmt *cntrl);
EXTERN S16 NbMiLwrStaInd      (Pst *pst, LnbMngmt *sta);
#endif

EXTERN S16 cmPkLnbCfgCfm      (Pst *pst, LnbMngmt *cfg);
EXTERN S16 cmPkLnbCntrlCfm    (Pst *pst, LnbMngmt *cntrl);

EXTERN S16 cmUnpkLnbCfgCfm    (LnbCfgCfm func, Pst *pst, Buffer *mBuf);
EXTERN S16 cmUnpkLnbCntrlCfm  (LnbCntrlCfm func, Pst *pst, Buffer *mBuf);
EXTERN S16 cmUnpkLnbStaInd    (LnbStaInd func, Pst *pst, Buffer *mBuf);

#ifdef SM
EXTERN S16 SmMiLnbCfgReq      (Pst *pst, LnbMngmt *cfg);
EXTERN S16 SmMiLnbCfgCfm      (Pst *pst, LnbMngmt *cfg);
EXTERN S16 SmMiLnbCntrlReq    (Pst *pst, LnbMngmt *cntrl);
EXTERN S16 SmMiLnbCntrlCfm    (Pst *pst, LnbMngmt *cntrl);
EXTERN S16 SmMiLnbStaInd      (Pst *pst, LnbMngmt *sta);
#endif /* SM */


#ifdef SM
/*-- stack manager initialization function ---*/
EXTERN S16 smNbActvInit   (Ent ent, Inst inst,
                                Region region, Reason reason);
/*---- stack manager activation function -----*/
EXTERN S16 smNbActvTsk    (Pst *pst, Buffer *mBuf);
#endif

#ifdef NB
/*-- stack manager initialization function ---*/
EXTERN S16 nbActvInit   (Ent ent, Inst inst,
                                Region region, Reason reason);
/*---- stack manager activation function -----*/
EXTERN S16 nbActvTsk    (Pst *pst, Buffer *mBuf);

EXTERN S16 cmUnpkLnbCfgReq(LnbCfgReq func,Pst *psti,Buffer *mBuf);
EXTERN S16 cmUnpkLnbCntrlReq(LnbCntrlReq func,Pst *pst,Buffer *mBuf);

EXTERN S16 cmUnpkNbMngmt
(
LnbMngmt *param,
U8 evnt,
Ptr ptr,
Buffer *mBuf,
Pst *pst
);

EXTERN S16 cmUnpkNbCfg
(
LnbCfg *param,
U16 elmnt,
Buffer *mBuf,
Pst *pst
);
EXTERN S16 cmUnpkNbLSapCfg
(
LnbLSapCfg *param,
Buffer *mBuf
);

EXTERN S16 cmUnpkNbCntrl
(
LnbCntrl *param,
U16 elmnt,
Buffer *mBuf
);
EXTERN S16 cmUnpkNbUsta
(
LnbUsta *param,
Buffer *mBuf
);
EXTERN S16 cmUnpkNbUstaDgn
(
LnbUstaDgn *param,
Buffer *mBuf
);
EXTERN S16 cmUnpkNbGenCfg
(
LnbGenCfg *param,
Buffer *mBuf,
Pst *pst
);
EXTERN S16 cmPkNbMngmt
(
LnbMngmt *param,
U8 evnt,
Buffer *mBuf
);
EXTERN S16 cmPkNbCfg
(
LnbCfg *param,
U16 elmnt,
Buffer *mBuf
);
EXTERN S16 cmPknbLSapCfg
(
LnbLSapCfg *param,
Buffer *mBuf
);
EXTERN S16 cmPkNbCntrl
(
LnbCntrl *param,
U16 elmnt,
Buffer *mBuf
); 
EXTERN S16 cmPkNbGenCfg
(
LnbGenCfg *param,
Buffer *mBuf
);
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __LNB_H__ */ 
