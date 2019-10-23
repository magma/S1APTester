
/********************************************************************20**

     Name:     eGTP Layer

     Type:     C source file

     Desc:     Interface Definition for eGTP Layer Manager interface

     File:     leg.x

     Sid:      leg.x@@/main/12 - Wed Jun  5 16:33:53 2013

     Prg:      an

*********************************************************************21*/

#ifndef __LEGX__
#define __LEGX__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm_tkns.h"       /* common tokens */
#include "cm_mblk.h"       /* Memory Link List */
#include "leg.h"           /* Event structure file */

/* header include files (.x) */
#include"gen.x"           /* general layer */
#include"ssi.x"           /* system services */
#include"cm_tkns.x"       /* common tokens */
#include"cm_mblk.x"       /* Memory Link List typedefs */
#include"cm_lib.x"        /* common ss7 */

/** @file leg.x
    @brief LEG Interface File (leg.x) 
*/


#ifdef EGTP_U
typedef struct _legStr
{
    U16    length; /* Length of string */
    Data   buff[LEG_MAX_STRING]; /* string value */
}LegStr;
#endif /* EGTP_U */

/***********************
 * EUTRAN Entity types *
 ***********************/
typedef enum _legEntity
{
   LEG_GTP_ENT_UNKNWN,
   LEG_GTP_ENT_MME,
   LEG_GTP_ENT_SGW,
   LEG_GTP_ENT_PGW,
   LEG_GTP_ENT_SGSN
#ifdef EG_REL_930
   ,
   LEG_GTP_ENT_MBMSGW
#endif /* EG_REL_930 */
/* leg_x_001.main_10 -Added for S2B */
#ifdef EG_S2B_SUPP
   ,
   LEG_GTP_ENT_EPDG = 7
#endif
/* leg_x_001.main_10 -Added for S2A */
#ifdef EG_S2A_SUPP
   ,
   LEG_GTP_ENT_TWAN = 8
#endif
}LegEntity;

/**********************************************
 * eGTP IE Entry Structure                    *
 **********************************************/

typedef struct _legIeEntry
{
   U8                   ieType;                 /**< IE Code */
   U8                   dataType;               /**< Data type of IE */
   U16                   minLen;                /**< min Length */
   U16                   maxLen;                /**< max Length */
}LegIeEntry; /* end of typedef struct lgeIeEntry */

typedef struct _legIeProperties LegIeProperties;
typedef struct _legGroupedIe LegGroupedIe;

/**********************************************
 * eGTP Grouped IE Structure                  *
 **********************************************/

struct _legGroupedIe
{
   U8                   nmbGrpIe;            /**< Number of grouped IEs  */
   U8                   posIndex[LEG_MAX_INSTANCES][LEG_MAX_IES];  /**< Store the position index */
   LegIeProperties      *ieProperties; /**< LEG_MAX_IES_PER_GRPIE  Maximum IEs per grouped IE */
};

/**********************************************
 * eGTP Message IE Properties Structure       *
 **********************************************/

struct _legIeProperties
{
   U8                  ieType;       /**< IE Code    */
   U8                  ieClass;      /**< IE Class MANDATORY/OPTIONAL/CONDITIONAL */
   Bool                ieList;       /**< IE can be a list */ 
   U8                  ieInst;       /**< Instance  */
   LegGroupedIe        *groupedIe;    /**< List of IEs in Grouped IE */
};

/**********************************************
 * eGTP Message Entry Structure               *
 **********************************************/
typedef S16 (*EscFun) ARGS((Void *,U8 ));
typedef struct _legMsgEntry
{
   U8                  msgType;               /**< code of the Message  */
   U8                  posIndex[LEG_MAX_INSTANCES][LEG_MAX_IES];  /**< Store the position index */
   U8                  nmbIeProp;             /**< Number of IE Properties */
   LegIeProperties     ieProperties[LEG_MAX_IES_PER_MSG]; /**< Maximum IEs per message  */
   EscFun              validateIe;             /* Escape Funtion for each Message */
}LegMsgEntry;

/**********************************************
 * eGTP IE Dictionary Configuration           *
 **********************************************/

typedef struct _egIeDictCfg
{
  LegIeEntry    ieEntry[LEG_MAX_IES_ALL_MSGS];         /**< IE Entry Structure */
  U16            posIdx[LEG_MAX_IES];  /**< Postion index storage */
  U8            nmbIe;                 /**< Number of Ie Entries */
 
}EgIeDictCfg;

/**********************************************
 * eGTP Message Dictionary Configuration      *
 **********************************************/

typedef struct _egGmDictCfg
{
  U8            intfType;        /**< Interface Type */
  U8            nmbMsg;          /**< Number of Messages */
  LegMsgEntry   *gmEntry;        /**< Message Entry */ 
}EgGmDictCfg;

#ifdef EGTP_U
#ifdef EGTP_U_MULTI_THREADED
/**********************************************
 * eGTP Thread Information                    *
 **********************************************/
typedef struct _egThrdInfo
{
   Region      regionId;
   Pool         pool;
}EgThrdInfo;
#endif /* EGTP_U_MULTI_THREADED */
#endif /* EGTP_U */

/**********************************************
 * eGTP General Configuration Structure       *
 **********************************************/
/**@struct _egGenCfg
   @brief eGTP General Configuration */

/* leg_x_001.main_3  EGTP_C Path management functionality */
/* leg_x_001.main_6  Support of local Echo support  */
/* leg_x_001.main_8  Echo Seq Number Start/End var type updated to 32 bit */
typedef struct _egGenCfg
{
#ifdef EGTP_C
   U8           nodeType;       /**< Node Type Identifier, SGSN/PGW/..etc. */
   U8           nmbIntfs;       /**< Maximum number on interfaces */
   U32          nmbMaxTnls;     /**< Maximum Number of Tunnels; system wide */
   U16          maxTunlArrSz;   /**< Maximum Tunnel Array Size */
   U8           n3Requests;     /**< Maximum Number of attempts for signaling requests */
#ifdef EGTP_C_PTH_MGT
   TmrCfg       pathTmr;         /**< Echo timer values */
   TmrCfg       pathT3Timer;     /**< Path T3 Timer value */ 
   U8           pathN3Retries;   /**< Number of retries for N3 request */
#ifdef LEGV4
   U32          echoSeqNumStart; /**< Echo Request Sequence Number Range Start */
   U32          echoSeqNumEnd;   /**< Echo Request Sequence Number Range End */
#else
   U16          echoSeqNumStart; /**< Echo Request Sequence Number Range Start */
   U16          echoSeqNumEnd;   /**< Echo Request Sequence Number Range End */
#endif
  /* leg_x_001.main_11 : added timer parameter */
#ifdef LEGV5
   TmrCfg       timeToWaitPbTmr; /**< Time to wait for piggyback message */
#endif
   U8           rstCnt;          /**< Restart Counter */
#endif
#endif /* #ifdef EGTP_C */ 
#ifdef EGTP_U
   TmrCfg       eguT3Timer;      /**< EGTP_U T3N3 Timer value */ 
   U8           nmbRetries;    /**< Number of retries for N3 request */
   TmrCfg       echoTmr;         /**< Echo timer values */
   TmrCfg       reOrderTmr;     /**< reOrdering timer */
   U16          pvtExtId;        /**< Private extnesion Id need to be included    *
                                   * while building echo request                  */
   U32          pduWindSize;     /**< Reordering window size */
   U8           maxNumOfIp;      /**< Maximum number of Ips */
   U8           nodeArch;        /**< Node architecture : whether UMTS or LTE */
	Bool         lclEchoSup;      /**< Local port echo request support */
#ifdef EGTP_U_MULTI_THREADED
   U8           nmbWorkerThread; /**< Number of worker threads needed */
   EgThrdInfo  *thrdInfo;       /**< Threads information */
   TmrCfg       loadDistTmr;    /**< Load distribution timer values */
#endif /* EGTP_U_MULTI_THREADED */
#endif /* EGTP_U */
/*leg_x_001.main_7 Fix timerRes datatype changed from U16 to S16 as per SRegCfgTmr() params */
   S16          timerRes;       /**< Timer resolution */
   U16          nmbUSaps;       /**< Maximum Number of Upper SAP */
   U16          maxNmbTSaps;    /**< Maximum Number of  TSAP, currently its 1 */
   U16          nmbSrvs;        /**< Number of servers; system wide */
   Status       resThreshUpper; /**< Resource upper threshold */
   Status       resThreshLower; /**< Resource upper threshold */
   Pst          lmPst;          /**< Layer manager post structure */
/*leg_x_001.main_7 Change for eGTP-C PSF Upgrade */
#ifdef LEGV3
   Bool         conventionalNode; /**< Flag to determine PSF node type */
   Bool         RtxAllowed; /*--*< Added to support ReTx from STANDBY node on switchover */
#endif
}EgGenCfg;

/**********************************************
 * eGTP Layer USAP Configuration Structure    *
 **********************************************/

/**@struct _egUSapCfg
   @brief eGTP Layer USAP Configuration */
typedef struct _egUSapCfg
{
   SpId         sapId;           /**< SAP identifier */
#ifdef EGTP_C
   Bool         echo;            /**< TRUE if the USAP is meant for echo*/
   U8           intfType;        /**< Interface type supported, S5/S8/S11 */
#endif /* EGTP_C */
   Selector     selector;        /**< Coupling selector for GTP User */
   MemoryId     mem;             /**< Memory region and pool ID */
   Priority     priority;        /**< Priority */
   Route        route;           /**< Route for pst */
   Ent          dstEnt;          /**< Entity */
   Inst         dstInst;         /**< Instance */
   ProcId       dstProcId;       /**< Destination processor ID */
   U8           flag;            /**< Flag defining EGTP-C ot EGTP-U */
/*leg_x_001.main_7 Change for eGTP-C PSF Upgrade */
#ifdef TDS_ROLL_UPGRADE_SUPPORT
   Bool remIntfValid;          /* validity of remote interface version num */
   CmIntfVer remIntfVer;       /* remote interface version number */
#endif /* TDS_ROLL_UPGRADE_SUPPORT */

}EgUSapCfg;

/********************************************************
 * eGTP Layer TSAP Configuration Structure (STTSAP)     *
 *******************************************************/

/**@struct _egTSapCfg
   @brief eGTP Layer TSAP Configuration */
typedef struct _egTSapCfg
{
   SuId         tSapId;      /**< ID of the SAP being configured */
   SpId         spId;        /**< SAP identifier */
   U16          tptType;     /**< Transport type TUCL/DTUCL      */
   Selector     selector;    /**< Selector for GTP User */
   MemoryId     mem;         /**< Memory region and pool ID */
   Priority     priority;    /**< Priority */
   Route        route;       /**< Route for pst */
   Ent          dstEnt;      /**< Entity */
   Inst         dstInst;     /**< Instance */
   ProcId       dstProcId;   /**< Destination processor ID */
   TmrCfg       tInitTmr;    /**< Bind timer configuation */
   CmTptParam   tptParam;    /**< Tpt params for client connections */
/*leg_x_001.main_7 Change for eGTP-C PSF Upgrade */
#ifdef TDS_ROLL_UPGRADE_SUPPORT
   Bool remIntfValid;          /* validity of remote interface version num */
   CmIntfVer remIntfVer;       /* remote interface version number */
#endif /* TDS_ROLL_UPGRADE_SUPPORT */

}EgTSapCfg;

/**@struct _egTSapReCfg
   @brief eGTP Transport SAP Re Configuration */
typedef struct _egTSapReCfg
{
   CmTptParam   tPar;         /**< Client transport parameters        */
                              /* (optional)                         */
   U8           maxBndRetry;  /**< Maximum number of bind retries    */
   TmrCfg       bndTmCfg;     /**< Bind timer configuration           */
} EgTSapReCfg;

#ifdef EGTP_U

/**********************************************
 * eGTP-U IP Info Structure    *
 **********************************************/

/**@struct _egIpInfo
   @brief eGTP-U Each IP Address Information*/

typedef struct _egIpInfo
{
   CmTptAddr   srcIpAddr;             /**< Maximum number of retries                   */
   SpId        spId;                  /**< Sap Id to which this Ip belong to           */
   U8          nodeType;              /**< Private extnesion Value need to be included */
   Bool        cfmStatus;             /**< Status of Each Ip configuration */
   U16         reason;                /**< Reason of Ip configuration failure */
   LegStr      echoReqPvtExtVal;      /**< Private extnesion Value need to be included *
                                       * while building echo request */
   LegStr      echoRspPvtExtVal;      /**< Private extnesion Value need to be included *
                                       * while building echo response                 */
   LegStr      errIndPvtExtVal;       /**< Private extnesion Value need to be included *
                                       * while building echo response                 */
}EgIpInfo;


/**********************************************
 * eGTP-U IP Address Configuration Structure    *
 **********************************************/

/**@struct _egIpAddrCfg
   @brief eGTP-U IP Address Configuration */

typedef struct _egIpAddrCfg
{
   U8             nmbIpAddr;  /**< Maximum number of retries */
   EgIpInfo      *ipInfo;    /**< Maximum number of retries */
}EgIpAddrCfg;

#endif /* EGTP_U */


/**********************************************
 * eGTP Tpt Server Configuration Structure    *
 **********************************************/

/**@struct _egTptSrvCfg
   @brief eGTP Tpt Server Configuration */
typedef struct _egTptSrvCfg
{
   SpId         uSapId;        /**< SAP identifier                  */
   U32          tptSrvId;      /**< Transport server Identifier     */
   SuId         tSapId;        /**< Transport SAP Identifier        */
   CmTptAddr    tptAddr;       /**< Transport address of the server */
   CmTptParam   tptParam;      /**< Transport parameters */
   S16          opnSrvRetryCnt;/**< Number of times EGTP retries  *
                                * Transport Server Connection    */
   TmrCfg       opnSrvTmr;     /**< Timer to wait before retrying   */

#ifdef EGTP_C
   Bool         isDfltSrv;     /**< TRUE, if this is default server with port *
                                * 2123, and there can be only one default server */
#endif
   TknStrOSXL   hostName;      /**< Server's host/domain name(host.domain)*/
   U8           gtp_C_Or_U;    /**< Flag defining whether this tpt belongs to 
                                 * EGTP_C or EGTP_U */
}EgTptSrvCfg;



/**********************************************
 * eGTP Layer Configuration Structure         *
 **********************************************/
/**@struct _egCfg
   @brief eGTP Layer Configuration */

/* leg_x_001.main_1  1. Egtpu release changes */
typedef struct _egCfg
{
  union
   {
      EgGenCfg      gen;         /**< General configuration */
      EgUSapCfg     uSap;        /**< Upper SAP configuration */
      EgTSapCfg     tSap;        /**< Transport SAP configuration */
#ifdef EGTP_U
      EgIpAddrCfg   ipAddr;      /**< Ip Address Configuration */
#endif /* EGTP_U */
      EgTptSrvCfg   tptSrv;      /**< Tptp Server configuration */
#ifdef EGTP_C
      EgGmDictCfg   gmDictCfg;   /**< Message Dictionary Configuration */
      EgIeDictCfg   ieDictCfg;   /**< IE Dictionary Configuration */
#endif /* EGTP_C */
   } s;

   union
   {
      EgTSapReCfg   tSapReCfg;   /**< Transport SAP reconfig */
   }r;

}EgCfg;

/**********************************************
 * eGTP Layer Debug Control Structure         *
 **********************************************/

/**@struct _egDbgCntrl
   @brief eGTP Layer Debug Control */
typedef struct _egDbgCntrl
{
   U32          genDbgMask;      /**< Non entity related debug mask */
}EgDbgCntrl;

/**********************************************
 * eGTP Layer Trace Control Structure         *
 **********************************************/

/**@struct _egTrcCntrl
   @brief eGTP Layer Trace Control */
typedef struct _egTrcCntrl
{
   union
   {
      SpId      tSapId;          /**< TSAP ID */
   }t;
   S16          trcLen;          /**< Trace length */
   U32          trcMask;         /**< Trace mask */
}EgTrcCntrl;

#ifdef EGTP_U
/********************************************
 * eGTP Layer Ip Address Control Structure      *
 ********************************************/
/**@struct egIpAddrCntrl
   @brief eGTP Ip Address Control */
typedef struct egIpAddrCntrl
{
   CmTptAddr    ipAddr;        /**< Ip Address on which control operation should be taken */
   SpId          fromSpId;     /**< SapId from which Ip need to be delete or move */
   SpId          toSpId;       /**< SapId to which Ip needs to be moved */
}EgIpAddrCntrl;
#endif /* EGTP_U */

/********************************************
 * eGTP Layer Server Control Structure      *
 ********************************************/
/**@struct egServerCntrl
   @brief eGTP Server Control */
/* leg_x_001.main_9:tSapId in Mgmt Struct to index TSAP from TSapLst */
typedef struct egServerCntrl
{
   U8           type;          /**< The type of the element present : Server */
#ifdef LEGV5
   SuId        tSapId;        /**< Transport SAP Identifier        */
#endif
                               /**< Id (LEG_SRV_ID) or Address(LEG_SRV_ADDR) */
   union
   {
     U32          tptSrvId;      /**< Transport server Identifier */
     CmTptAddr    tptAddr;       /**< Transport address */
   }t;
}EgServerCntrl;

/********************************************
 * eGTP Layer SAP Control Structure         *
 ********************************************/
/**@struct egSapCntrl
   @brief eGTP Layer SAP Control */
typedef struct egSapCntrl
{
   SpId    sapId;           /**< SAP identifier */
}EgSapCntrl;

/********************************************
 * eGTP Layer Control Structure             *
 ********************************************/

/**@struct _egCntrl
   @brief eGTP Layer Control */
typedef struct _egCntrl
{
   DateTime     dt;              /**< Date */
   U8           action;          /**< Action to be performed */
   U8           subAction;       /**< Subaction to be performed */
   Bool         flag;            /**< Flag defines whether the control req
                                   *  is for EGTP_U or EGPT_C */
   union
   {
      EgServerCntrl server;      /**< Server control */
      EgSapCntrl    sap;         /**< SAP control structure */
      EgTrcCntrl    trcCntrl;    /**< Trace control */
#ifdef DEBUGP
      EgDbgCntrl    dbgCntrl;    /**< Debug printing control */
#endif
#ifdef EGTP_U
      EgIpAddrCntrl ipAddress;      /**< Ip Address Control */
#endif /* EGTP_U */
/*leg_x_001.main_11: added Logging mask */
      U32            logMask;      
 }s;
}EgCntrl;

/********************************************
 * eGTP Layer General Status Structure      *
 ********************************************/

/**@struct _egGenSta
   @brief eGTP Layer General Status */
typedef struct _egGenSta
{
   U32          memSize;   /**< Total static mem size reserved by eGTP */
   U32          memAlloc;  /**< Total static mem allocated by eGTP */
   Bool         resCong;   /**< Flag to indicate resource congestion status */
}EgGenSta;

/********************************************
 * eGTP Layer Lower SAP Status Structure    *
 ********************************************/

/**@struct _egTSapSta
   @brief eGTP Layer Lower SAP Status */
typedef struct _egTSapSta
{
   SpId         tSapId;          /**<SAP ID */
   S16          state;           /**<SAP state */
/*leg_x_001.main_7 Change for eGTP-C PSF Upgrade
 *-Variables added for self and remote interface vesrion 
 *-Flag for validity of remote interface version num
 */
#ifdef TDS_ROLL_UPGRADE_SUPPORT
   Bool remIntfValid;         /* validity of remote interface version num */
   CmIntfVer selfIfVer;       /* self interface version number */
   CmIntfVer remIfVer;        /* remote interface version number */
#endif /* TDS_ROLL_UPGRADE_SUPPORT */

}EgTSapSta;

/********************************************
 * eGTP Layer Upper SAP Status Structure    *
 ********************************************/
/**@struct _egUSapSta
   @brief eGTP Layer Upper SAP Status */
typedef struct _egUSapSta
{
   SpId         uSapId;          /**< SAP ID */
   S16          state;           /**< SAP state */
}EgUSapSta;

/**@struct _egTptSrvSta 
   @brief eGTP Layer TptServer Status */
typedef struct _egTptSrvSta
{
   SpId         tSapId;          /**<SAP ID */
   U32           tptSrvId;        /**< ServerId used to retrive the ServerCb from TSap */
   Bool         status;          /**< Active or not */
   U8           state;           /**< state of TPT server */
}EgTptSrvSta;

/**@struct _egTnlSta 
   @brief eGTP Layer Tunnel Status */
typedef struct _egTnlSta
{
   U32        teId;           /**<Tunnel Id */
   SpId       spId;           /**< Sap Id to which Tunnel belongs to */
   CmTptAddr  srcIpAddr;      /**< Source Ip Address to which Tunnel belongs to 
                                 (It is an input parameter) */ 
   CmTptAddr  destIpAddr;     /**< Destination to which the tunnerl belongs to 
                                 ( It is an input parameter */ 
   Bool       reOrderPrsnt;   /**<Reodrering is present or not */
}EgTnlSta;


/********************************************
 * eGTP Layer Solicited Status Structure    *
 ********************************************/

/**@struct _egSta
   @brief eGTP Layer Solicited Status */
typedef struct _egSta
{
   DateTime     dt;              /**< Date */
   union
   {
      SystemId    sysId;         /**< System ID status */
      EgGenSta    genSta;        /**< General status */
      EgUSapSta   uSapSta;       /**< Status of the Upper SAP */
      EgTSapSta   tSapSta;       /**< Status of the Lower SAP */
#ifdef EGTP_U
      EgTptSrvSta tSrvrSta;       /**< Status of the Tpt Server */
      EgTnlSta    tnlSta;         /**< Status of tunnel */
#endif /* EGTP_U */
   } s;
}EgSta;

/********************************************
 * eGTP Layer General Statistics Structure  *
 ********************************************/

/**@struct _egGenSts
   @brief eGTP Layer General Statistics */
typedef struct _egErrSts
{
   Cntr invVerRx;  /*Invalid version received*/
   Cntr invProtTypeRx; /*Invalid Protocol Type received*/
   Cntr invMsgRx;  /*Invalid Message received*/
   Cntr invMsgLenRx; /*Invalid Message Length received*/
   Cntr invIeOrderRx;  /*Ies received out of order*/
   Cntr invIeLenRx;  /*Ie received with invalid length*/
   Cntr invIeFormatRx;  /*Ie format is invalid*/
   Cntr invManIeLenRx;  /*Mandatory IE received with invalid length*/
   Cntr missMandIeRx;  /*Message received with missing  mandatory IE*/
   Cntr unSuppExtHdrRx; /*Extension Header received is unsupported*/
   Cntr wrngExtHdrRx;  /*Wrong extension header received*/
   Cntr msgUnableCompRx;  /*Message received unable to comply*/
   Cntr msgUnableCompTx;  /*Message received from application unable to comply*/
   Cntr missMandIeTx;  /*Message received from application with missing  mandatory IE*/
   Cntr memAllocFldTx;  /*Message received from application for which memory allocation failed*/
   Cntr invMsgTx;  /*Invalid Message received from application*/
   Cntr invTeidTx;  /*Invalid teid received from application*/
   Cntr invTeidRx;  /*Invalid teid received */
   Cntr errSeqNoTx;  /*Error in sequence number received from application*/
   Cntr errSeqNoRx;  /*Error in sequence number received*/
   Cntr tpduExcdTx;  /*TPDU size exceeded received from application*/
   Cntr invDatTypeTx;  /*TPDU size exceeded received from application*/
}EgErrSts;

typedef struct _egGenSts      
{
   Cntr         numTxMsg;       /**< Number of messages transmitted */
   Cntr         numRxMsg;       /**< Number of messages received  */
   Cntr         numActvTnls;    /**< Number of active tunnels */
/*leg_x_001.main_5    Adding Stat indicators for Normal & Fwd data tunnels*/
#ifdef LEGV2  
   Cntr         numNrmlDataTunn; /**< Number of Normal data tunnels
                                      i.e. non-forwarding Tunnel */
   Cntr         numFwdDataTunn;  /**< Number of Forwarding data tunnels
                                      (required for data forwarding in Handover) */
#endif
   Cntr         numErrInd;      /**< Number of Error Indications */
   /*leg_x_001.main_11:fix for ERR IND in periodic reporting */
   Cntr         cntInvldTeidInd; /**< Number of Invalid teid Error Indications */
   Cntr         rxDesgMsg;      /**< Number of disgard messages received in invalid 
                                 * state of tunnel (unexpected messages) */
   EgErrSts     errSts;         /**< Error Statistics*/
}EgGenSts;

/********************************************
 * eGTP Layer SAP PDU Tx/Rx Stats Structure *
 ********************************************/

/**@struct MsgSts
   @brief eGTP Layer General Statistics */
typedef struct MsgSts 
{
   Cntr         Tx;                 /**< Transmitted */
   Cntr         Rx;                 /**< Received */
}EgMsgSts;

/********************************************
 * eGTP Layer SAP Statistics Structure      *
 ********************************************/

/**@struct _egSapSts
   @brief eGTP Layer Sap Statistics */
typedef struct _egSapSts  
{
   SpId         sapId;          /**< SAP identifier */
   Cntr         totalMsgsTx;    /**< Total number of messages transmitted */
   Cntr         totalMsgsRx;    /**< Total number of messages received */
   EgMsgSts     msgType[LEG_MAX_NUM_OF_MSGS]; /**< Total of each message 
                                                 transmitted/received */
}EgSapSts;


#ifdef EGTP_U
#ifdef EGTP_U_MULTI_THREADED

/********************************************
 * eGTP Layer threades Info Structure      *
 ********************************************/

typedef struct _egThrStsInfo
{
   U32   thrId;               /**< Thread Id */
   Cntr  totalMsgsTx;         /**< Total number of messages transmitted */
   Cntr  totalMsgsRx;         /**< Total number of messages received */
   U32   nmbOfReorderTnl;            /**< number of tunnels handled by the thread */
}EgThrStsInfo;

/********************************************
 * eGTP Layer Threades Statistics Structure      *
 ********************************************/

/**@struct _egThrSts
   @brief eGTP Layer Threads Statistics */
typedef struct _egThrSts  
{
   U8                nmbThrd;        /** < Number of worker threads */
   EgThrStsInfo      *threadInfo;    /** < Threads Info */
}EgThrdSts;

#endif /* EGTP_U_MULTI_THREADED */

/********************************************
 * eGTP Layer Tunnel Statistics Structure      *
 ********************************************/

/**@struct _egTnlSts
   @brief eGTP Layer Tunnel Statistics */
typedef struct _egTnlSts  
{
   U32        teId;           /**<Tunnel Id */
   SpId       spId;           /**< Sap Id to which Tunnel belongs to */
   CmTptAddr  srcIpAddr;      /**< Source Ip Address to which Tunnel belongs to 
                                 (It is an input parameter) */ 
   CmTptAddr  destIpAddr;     /**< Destination to which the tunnerl belongs to 
                                 ( It is an input parameter */ 
   Cntr       totalMsgsTx;    /**<Total number of messages transmitted */
   Cntr       totalMsgsRx;    /**<Total number of messages received */
   Bool       reOrderPrsnt;   /**<Reodrering is present or not */
}EgTnlSts;


/********************************************
 * eGTP Layer transport server Statistics Structure      *
 ********************************************/

/**@struct _egTptSrvrSts
   @brief eGTP Layer Tpt Server Statistics */
typedef struct _egTptSrvrSts  
{
   SpId       spId;           /**< SapId */
   CmTptAddr  lclAddr;        /**< Local Ip Address and port*/
   Cntr       totalMsgsTx;    /**< Total number of messages transmitted */
   Cntr       totalMsgsRx;    /**< Total number of messages received */
}EgTptSrvrSts;

/********************************************
 * eGTP Layer Ip Address Statistics Structure      *
 ********************************************/

/**@struct _egIpSts
   @brief eGTP Layer General Statistics */
typedef struct _egIpSts  
{
   CmTptAddr    IpAddr;         /**< Ip address */
   SpId         spId;           /**< Sap Id */
   U32          nmbPorts;       /**< Number of ports */ 
   U32          *portsLst;      /**< list of port number*/ 
   U32          nmbActvSrvrs;   /** < Active servers */
   U32          nmbInactvSrvr;   /**< InActive servers */
   Cntr         totalMsgsTx;    /**< Total number of messages transmitted */
   Cntr         totalMsgsRx;    /**< Total number of messages received */
}EgIpSts;
#endif /* End of EGTP_U */
/********************************************
 * eGTP Layer Statistics Structure          *
 ********************************************/

/**@struct _egSts
   @brief eGTP Layer Statistics */
typedef struct _egSts
{
   DateTime      dt;             /**< Date and time */
   union
   {
     EgGenSts      gen;            /**< General statistics */
     EgSapSts      usap;           /**< USAP statistics */
     EgSapSts      tsap;           /**< TSAP statistics */
#ifdef EGTP_U
     EgIpSts       ipSts;
     EgTptSrvrSts  tptSrvrSts;
     EgTnlSts      tnlSts;
#ifdef EGTP_U_MULTI_THREADED 
     EgThrdSts     thrdSts;
#endif /* EG_MULTI_THREADED */
#endif /* EGTP_U */
   }s;
}EgSts;

/********************************************
 * eGTP Layer Unsolicited Status Structure  *
 ********************************************/

/**@struct _egUstaDgnVal
   @brief eGTP Layer Unsolicited Status */
/* Unsolicited status */
typedef struct _egUstaDgnVal  /**< Alarm Diagnostics */
{
   U8 type;
   union
   {
      Event    event;        /**< Event identifier */
      SpId     sapId;        /**< SAP ID */
      U32      connId;       /**< Connection identifier */
      U8       choice;       /**< Choice of connection identifier */
      U8       ieType;       /**< Type of the IE */
      CmTptAddr ipAddr;
      MemoryId mem;          /**< Memory region and pool ID for GTP */
   } t;
}EgUstaDgnVal;

/**@struct _egUstaDgn
   @brief eGTP Layer alarm diagnostic */  
typedef struct _egUstaDgn      /**< Alarm diagnostics structure */
{
   EgUstaDgnVal dgnVal[LEG_USTA_MAX_DGNVAL]; /**< Diagnostic value list */
}EgUstaDgn;

/**@struct _egUsta
   @brief eGTP Layer Unsolicited status */  
typedef struct _egUsta
{
   CmAlarm       alarm;          /**< Alarm */
   DateTime      dt;             /**< Date and time */
   EgUstaDgn     dgn;            /**< Alarm diagnostics */
}EgUsta;

/********************************************
 * eGTP Layer Trace Indication Structure    *
 ********************************************/

/**@struct _egTrc
   @brief eGTP Layer Trace Indication */  
typedef struct _egTrc
{
   DateTime      dt;             /**< Date and time */
   U16           evnt;           /**< Event: message type */
   S16           length;         /**< Length of included trace buffer */
   CmTptAddr     *srcAddr;       /**< Src Address of the node */
   CmTptAddr     *remAddr;       /**< Dst Address of the node */
}EgTrc;

/********************************************
 * eGTP Layer Management Structure          *
 ********************************************/
/**@struct _egMngmt
   @brief eGTP Layer Management */
typedef struct _egMngmt
{
   Header      hdr;
   CmStatus    cfm;
   union
   {
      EgCfg      cfg;            /**< Configuration */
      EgCntrl    cntrl;          /**< Control */
      EgSts      sts;            /**< Statistics */
      EgSta      ssta;           /**< Solicited Status */
      EgUsta     usta;           /**< UnSolicited Status */
      EgTrc      trc;            /**< Trace */
   }u;
}EgMngmt;


/******************************************************************************************
 *                                                                                        *
 *                              Interface Primitives                                      *
 *                                                                                        *
 *****************************************************************************************/

typedef S16 (*LegCfgReq) ARGS(( Pst     *pst,   /* Post structure */
                                EgMngmt *cfgReq  /* management structure */
                              ));

typedef S16 (*LegCfgCfm) ARGS((
                               Pst     *pst,      /* Post structure */
                               EgMngmt *cfgCfm    /* management structure */
                             ));

typedef S16 (*LegStsReq) ARGS((
                               Pst     *pst,      /* Post structure */
                               Action  action,    /* action to be performed */
                               EgMngmt *stsReq          /* management structure */
                             ));

typedef S16 (*LegStsCfm) ARGS((
                               Pst     *pst,            /* Post structure */
                               EgMngmt *stsCfm          /* management structure */
                             ));

typedef S16 (*LegStaReq) ARGS((
                               Pst     *pst,            /* Post structure */
                               EgMngmt *staReq          /* management structure */
                             ));

typedef S16 (*LegStaCfm) ARGS((
                               Pst     *pst,            /* Post structure */
                               EgMngmt *staCfm          /* management structure */
                             ));

typedef S16 (*LegStaInd) ARGS((
                               Pst     *pst,            /* Post structure */
                               EgMngmt *staInd          /* management structure */
                             ));

typedef S16 (*LegCntrlReq) ARGS((
                               Pst     *pst,            /* Post structure */
                               EgMngmt *cntrlReq        /* management structure */
                             ));

typedef S16 (*LegCntrlCfm) ARGS((
                               Pst     *pst,            /* Post structure */
                               EgMngmt *cntrlCfm        /* management structure */
                             ));

typedef S16 (*LegTrcInd) ARGS((
                               Pst     *pst,            /* Post structure */
                               EgMngmt *trcInd,         /* management structure */
                               Buffer  *mBuf            /* trace buffer */
                             ));


/** @defgroup InterfacePrimitives
* @{
*/
   /**
    * @brief  This function is invoked in the layer manager and the request is
    * processed in the eGTP layer.
    *
    * @details The layer manager configures the various elements of the eGTP layer
    * using  the management configuration procedure, which the layer manager 
    * initiates. This eGTP configuration request primitive can be called more than
    * once. It is called before the bind primitives are called. The configuration
    * request primitive type is specified by the "egMngmt.hdr.elmId.elmnt" field.
    *
    * @param[in] pst Pointer to the post structure. System services uses it for 
    * loosely coupled, inter-task communication.
    *
    * @param[in] cfg  Pointer to the configuration structure. 
    *
    *
    * @return  ROK - Success <br> RFAILED - Failure 

      @see EgCfg
    */
PUBLIC S16 EgMiLegCfgReq ARGS((
                               Pst     *pst,            /* Post structure */
                               EgMngmt *cfgReq          /* management structure */
                             ));

   /**
    * @brief  This function is invoked in the eGTP layer and the request is
    * processed in the layer manager.
    *
    * @details This primitive is issued by the eGTP layer in response to EgMiLegCfgReq
    * and indicate whether the configuration was successful. The layer manager must
    * repeat the configuration request until it receives a confirmation. 
    *
    * @param[in] pst Pointer to the post structure. System services uses it for 
    * loosely coupled, inter-task communication.
    *
    * @param[in] cfg  Pointer to the configuration structure. 
    *
    *
    * @return  ROK - Success <br> RFAILED - Failure 

      @see EgCfg
    */
PUBLIC S16 EgMiLegCfgCfm ARGS((
                               Pst     *pst,            /* Post structure */
                               EgMngmt *cfgCfm          /* management structure */
                             ));

   /**
    * @brief  The layer manager uses this function to solicit statistics
    * information. This is invoked in the layer manager and the request is
    * processed in the eGTP layer.
    *
    * @details This primitive is issued by layer manager to gather statistics
    * information of various elements like general (layerwide), USAP and TSAP.
    * The statistics request primitive type is specified by the 
    * mgmnt.hdr.elmId field. The statistics counters can be zeroed using the
    * action parameter. If this primitive request is lost, the layer manager
    * must repeat the statistics request until it receives a confirmation.
    *
    * @param[in] pst Pointer to the post structure. System services uses it for 
    * loosely coupled, inter-task communication.
    *
    * @param[in] action Action to be performed. Action is either ZEROSTS(Zero 
    * Statistical counters) or NOZEROSTS.
    *
    * @param[in] sts  Pointer to the solicited statistics structure. 
    *
    *
    * @return  ROK - Success <br> RFAILED - Failure 

      @see EgSts
    */
PUBLIC S16 EgMiLegStsReq ARGS((
                               Pst     *pst,            /* Post structure */
                               Action  action,          /* action to be performed */
                               EgMngmt *stsReq          /* management structure */
                             ));

   /**
    * @brief  This function is invoked in the eGTP layer and this confirm 
    * primitive is processed in the layer manager. It provides the
    * layer manager with solicited statistics information.
    *
    * @details This primitive is issued by the eGTP layer in response
    * to EgMiLegStsReq and indicate whether the configuration was successful.
    * It provides the layer manager with solicited statistics information.
    * The layer manager must resend the configuration request until it
    * receives a confirmation. 
    *
    * @param[in] pst Pointer to the post structure. System services uses it for 
    * loosely coupled, inter-task communication.
    *
    * @param[in] sts  Pointer to the solicited statistics structure.
    *
    *
    * @return  ROK - Success <br> RFAILED - Failure 

      @see EgSts
    */
PUBLIC S16 EgMiLegStsCfm ARGS((
                               Pst     *pst,            /* Post structure */
                               EgMngmt *stsCfm          /* management structure */
                             ));

   /**
    * @brief  This function is invoked in the layer manager and is processed 
    * by the eGTP layer. This function request for solicited status 
    * information about various elements of the eGTP layer.

    * @details  The layer manager uses the management - solicited status procedure
    * to gather solicited status information about the various elements of the eGTP
    * software. The eGTP status request primitive (EgMiLegStaReq) can be called
    * more than once, any time after the management - configuration procedure.
    * The eg.Mngmt.hdr.elmId field specifies the status request primitive type.
    * The status confirm (EgMiLegStaCfm) primitive and other system service
    * primitives are called during the status procedure to return the status
    * value. 
    *
    * @param[in] pst Pointer to the post structure. System services uses it for 
    * loosely coupled, inter-task communication.
    *
    * @param[in] sta  Pointer to the solicited status structure. 
    *
    *
    * @return  ROK - Success <br> RFAILED - Failure 

      @see EgSta
    */
PUBLIC S16 EgMiLegStaReq ARGS((
                               Pst     *pst,            /* Post structure */
                               EgMngmt *staReq          /* management structure */
                             ));

   /**
    * @brief  This function is invoked in the eGTP layer and is processed by the
    * layer manager.It returns solicited status information.
    *
    * @details This primitive is issued by the eGTP layer in response to EgMiLegStaReq.
    * It provides the layer manager with solicited status information.
    * The layer manager must resend the configuration request until it
    * receives a confirmation. 
    *
    * @param[in] pst Pointer to the post structure. System services uses it for 
    * loosely coupled, inter-task communication.
    *
    * @param[in] sta  Pointer to the solicited status structure. 
    *
    *
    * @return  ROK - Success <br> RFAILED - Failure 

      @see EgSta
    */
PUBLIC S16 EgMiLegStaCfm ARGS((
                               Pst     *pst,            /* Post structure */
                               EgMngmt *staCfm          /* management structure */
                             ));

   /**
    * @brief  This function is invoked in the eGTP layer and is processed by the
    * layer manager.It returns unsolicited status information.
    *
    * @details This primitive is issued by the eGTP layer and is used to alert
    * the layer manager to a significant change in the software state, or when
    * an error is encountered while processing a primitive. The eGTP layer status
    * indication primitive (EgMiLegStaInd) can be called more than once and any time
    * after the configuration procedure, if the unsolicited status is enabled.
    * The unsolicited status can be enabled or disabled with the management -
    * control procedure.

    * @param[in] pst Pointer to the post structure. System services uses it for 
    * loosely coupled, inter-task communication.
    *
    * @param[in] sta  Pointer to the solicited status structure. 
    *
    *
    * @return  ROK - Success <br> RFAILED - Failure 

      @see EgSta
    */

PUBLIC S16 EgMiLegStaInd ARGS((
                               Pst     *pst,            /* Post structure */
                               EgMngmt *staInd          /* management structure */
                             ));
   /**
    * @brief  This function is invoked in the layer manager and is processed
    * by the eGTP layer. This function is used to control the various elements
    * of the eGTP layer.
    *
    * @details  The layer manager uses the management - control procedure
    * to control the various elements of the eGTP layer, It can be called
    * more than once, any time after the management - configuration procedure.
    * The eg.Mngmt.t.cntrl.action field specifies the control request primitive type.
    * The eg.Mngmt.t.cntrl.subaction field specifies the controlled element.
    * 
    * The eGTP software provides the following control functions to the layer
    * manager: Enable/Disable trace indications, enable/disable unsolicited
    * status indications, unconfigures the upper SAP, enable/disable debug
    * printing, enable a configure server.
    *
    * @param[in] pst Pointer to the post structure. System services uses it for 
    * loosely coupled, inter-task communication.
    *
    * @param[in] sta  Pointer to the control structure. 
    *
    *
    * @return  ROK - Success <br> RFAILED - Failure 

      @see EgCntrl
    */

PUBLIC S16 EgMiLegCntrlReq ARGS((
                               Pst     *pst,            /* Post structure */
                               EgMngmt *cntrlReq        /* management structure */
                             ));

   /**
    * @brief  This function is invoked in the eGTP layer and is processed by the
    * layer manager. It returns confirmation after successful control
    * operations.
    *
    * @details This primitive is issued by the eGTP layer in response to 
    * EgMiLegCntrlReq.
    *
    * @param[in] pst Pointer to the post structure. System services uses it for 
    * loosely coupled, inter-task communication.
    *
    * @param[in] cntrl  Pointer to the control structure. 
    *
    *
    * @return  ROK - Success <br> RFAILED - Failure 

      @see EgCntrl
    */
PUBLIC S16 EgMiLegCntrlCfm ARGS((
                               Pst     *pst,            /* Post structure */
                               EgMngmt *cntrlCfm        /* management structure */
                             ));

   /**
    * @brief  This function is invoked in the eGTP layer and is processed by the
    * layer manager.It returns trace information from the eGTP layer.
    *
    * @details This primitive is issued by the eGTP layer and is used to 
    * presents the trace information from the eGTP layer to the layer manager. The
    * eGTP trace primitive (EgMiLegTRcInd) can be called more than once and
    * any time after the management configuration procedure and if the tracing
    * is enabled. It is not called if tracing is disabled. Tracing can be
    * enabled/disabled with the management control procedure.
    * The egMngmt.t.egTrc structure specifies the parameters used by the trace
    * indication primitive.

    * @param[in] pst Pointer to the post structure. System services uses it for 
    * loosely coupled, inter-task communication.
    *
    * @param[in] trcInd  Pointer to the trace structure. 
    *
    * @param[in] mBuf  Buffer Received
 
    * @return  ROK - Success <br> RFAILED - Failure 

      @see EgTrc
    */
PUBLIC S16 EgMiLegTrcInd ARGS((
                               Pst     *pst,            /* Post structure */
                               EgMngmt *trcInd,         /* management structure */
                               Buffer  *mBuf            /* trace buffer */
                             ));


#ifdef SM

PUBLIC S16 SmMiLegCfgReq ARGS((
                               Pst     *pst,            /* Post structure */
                               EgMngmt *cfgReq          /* management structure */
                             ));

PUBLIC S16 SmMiLegCfgCfm ARGS((
                               Pst     *pst,            /* Post structure */
                               EgMngmt *cfgCfm          /* management structure */
                             ));

PUBLIC S16 SmMiLegStsReq ARGS((
                               Pst     *pst,            /* Post structure */
                               Action  action,          /* action to be performed */
                               EgMngmt *stsReq          /* management structure */
                             ));

PUBLIC S16 SmMiLegStsCfm ARGS((
                               Pst     *pst,            /* Post structure */
                               EgMngmt *stsCfm          /* management structure */
                             ));

PUBLIC S16 SmMiLegStaReq ARGS((
                               Pst     *pst,            /* Post structure */
                               EgMngmt *staReq          /* management structure */
                             ));

PUBLIC S16 SmMiLegStaCfm ARGS((
                               Pst     *pst,            /* Post structure */
                               EgMngmt *staCfm          /* management structure */
                             ));

PUBLIC S16 SmMiLegStaInd ARGS((
                               Pst     *pst,            /* Post structure */
                               EgMngmt *staInd          /* management structure */
                             ));

PUBLIC S16 SmMiLegCntrlReq ARGS((
                               Pst     *pst,            /* Post structure */
                               EgMngmt *cntrlReq        /* management structure */
                             ));

PUBLIC S16 SmMiLegCntrlCfm ARGS((
                               Pst     *pst,            /* Post structure */
                               EgMngmt *cntrlCfm        /* management structure */
                             ));

PUBLIC S16 SmMiLegTrcInd ARGS((
                               Pst     *pst,            /* Post structure */
                               EgMngmt *trcInd,         /* management structure */
                               Buffer  *mBuf            /* trace buffer */
                             ));

#endif /* end of SM */

#ifdef LCLEG 
EXTERN S16 cmPkLegCfgReq    ARGS((Pst* pst, EgMngmt * cfgReq));
EXTERN S16 cmPkLegCntrlReq  ARGS((Pst* pst, EgMngmt * cntrlReq));
EXTERN S16 cmPkLegStaReq    ARGS((Pst* pst, EgMngmt * staReq));
EXTERN S16 cmPkLegStsReq    ARGS((Pst* pst, Action action, EgMngmt * stsReq));


EXTERN S16 cmUnpkLegCfgReq    ARGS((LegCfgReq func, Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLegCntrlReq  ARGS((LegCntrlReq func, Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLegStaReq    ARGS((LegStaReq func, Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLegStsReq    ARGS((LegStsReq func, Pst *pst, Buffer *mBuf));

EXTERN S16 cmPkLegCfgCfm    ARGS((Pst* pst, EgMngmt * cfgCfm));
EXTERN S16 cmPkLegCntrlCfm  ARGS((Pst* pst, EgMngmt * cntrlCfm));
EXTERN S16 cmPkLegStsCfm    ARGS((Pst* pst, EgMngmt * stsCfm));
EXTERN S16 cmPkLegStaCfm    ARGS((Pst* pst, EgMngmt * staCfm));

EXTERN S16 cmUnpkLegCfgCfm    ARGS((LegCfgCfm func, Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLegCntrlCfm  ARGS((LegCntrlCfm func, Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLegStsCfm    ARGS((LegStsCfm func, Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLegStaCfm    ARGS((LegStaCfm func, Pst *pst, Buffer *mBuf));

EXTERN S16 cmPkLegStaInd    ARGS((Pst* pst, EgMngmt * staInd));
EXTERN S16 cmPkLegTrcInd    ARGS((Pst* pst, EgMngmt * trcInd, Buffer  * uBuf));

EXTERN S16 cmUnpkLegStaInd  ARGS((LegStaInd func, Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLegTrcInd  ARGS((LegTrcInd func, Pst *pst, Buffer *mBuf));

EXTERN S16 cmPkEgGenCfg     ARGS((EgGenCfg *genCfg, Buffer *mBuf, Pst *pst));
EXTERN S16 cmPkEgUSapCfg    ARGS((EgUSapCfg *usapCfg, Buffer *mBuf));
EXTERN S16 cmPkEgTSapReCfg  ARGS((EgTSapReCfg *tsapReCfg, Buffer *mBuf));
EXTERN S16 cmPkEgTSapCfg    ARGS((EgTSapCfg *tsapCfg, Buffer *mBuf));
EXTERN S16 cmPkEgTptSrvCfg  ARGS((EgTptSrvCfg *tsrvCfg, Buffer *mBuf));
EXTERN S16 cmPkEgGmDictCfg  ARGS((EgGmDictCfg *msgCfg, Buffer *mBuf));
EXTERN S16 cmPkEgIeDictCfg  ARGS((EgIeDictCfg *ieCfg, Buffer *mBuf));

#ifdef EGTP_U
EXTERN S16 cmPkEgIpAddrCfg ARGS((EgIpAddrCfg *ipAddrCfg, Buffer *mBuf, Pst *pst));
EXTERN S16 cmUnpkEgIpAddrCfg ARGS((EgIpAddrCfg *ipAddrCfg, Buffer *mBuf, Pst *pst));
#endif /* EGTP_U */



EXTERN S16 cmPkLegMsgEntry     ARGS((LegMsgEntry *msg, Buffer *mBuf));
EXTERN S16 cmPkLegIeProperties ARGS((LegIeProperties *ieProp, Buffer *mBuf));
EXTERN S16 cmPkLegGroupedIe    ARGS((LegGroupedIe *grpIe, Buffer *mBuf));
EXTERN S16 cmPkLegIeEntry      ARGS((LegIeEntry *ieEnt, Buffer *mBuf));

EXTERN S16 cmUnpkEgGenCfg    ARGS((EgGenCfg *genCfg, Buffer *mBuf, Pst *pst));
EXTERN S16 cmUnpkEgUSapCfg   ARGS((EgUSapCfg *usapCfg, Buffer *mBuf));
EXTERN S16 cmUnpkEgTSapReCfg ARGS((EgTSapReCfg *tsapReCfg, Buffer *mBuf));
EXTERN S16 cmUnpkEgTSapCfg   ARGS((EgTSapCfg *tsapCfg, Buffer *mBuf));
EXTERN S16 cmUnpkEgTptSrvCfg ARGS((EgTptSrvCfg *tsrvCfg, Buffer *mBuf));
EXTERN S16 cmUnpkEgGmDictCfg ARGS((EgGmDictCfg *msgCfg, Buffer *mBuf));
EXTERN S16 cmUnpkEgIeDictCfg ARGS((EgIeDictCfg *ieCfg, Buffer *mBuf));

EXTERN S16 cmUnpkLegMsgEntry     ARGS((LegMsgEntry *msg, Buffer *mBuf));
EXTERN S16 cmUnpkLegIeProperties ARGS((LegIeProperties *ieProp, Buffer *mBuf));
EXTERN S16 cmUnpkLegGroupedIe    ARGS((LegGroupedIe *grpIe, Buffer *mBuf));
EXTERN S16 cmUnpkLegIeEntry      ARGS((LegIeEntry *ieEnt, Buffer *mBuf));

EXTERN S16 cmPkEgTrcCntrl    ARGS((EgTrcCntrl *trcCntrl, Buffer *mBuf));
EXTERN S16 cmPkEgDbgCntrl    ARGS((EgDbgCntrl *dbgCntrl, Buffer *mBuf));
EXTERN S16 cmPkEgSapCntrl    ARGS((EgSapCntrl *sapCntrl, Buffer *mBuf));
EXTERN S16 cmPkEgServerCntrl ARGS((EgServerCntrl *srvCntrl, Buffer *mBuf));

EXTERN S16 cmUnpkEgTrcCntrl    ARGS((EgTrcCntrl *trcCntrl, Buffer *mBuf));
EXTERN S16 cmUnpkEgDbgCntrl    ARGS((EgDbgCntrl *dbgCntrl, Buffer *mBuf));
EXTERN S16 cmUnpkEgSapCntrl    ARGS((EgSapCntrl *sapCntrl, Buffer *mBuf));
EXTERN S16 cmUnpkEgServerCntrl ARGS((EgServerCntrl *srvCntrl, Buffer *mBuf));

EXTERN S16 cmPkEgGenSta    ARGS((EgGenSta *genSta, Buffer *mBuf));
EXTERN S16 cmPkEgUSapSta   ARGS((EgUSapSta *usapSta, Buffer *mBuf));
EXTERN S16 cmPkEgTSapSta   ARGS((EgTSapSta *tsapSta, Buffer *mBuf));

EXTERN S16 cmUnpkEgGenSta    ARGS((EgGenSta *genSta, Buffer *mBuf));
EXTERN S16 cmUnpkEgUSapSta   ARGS((EgUSapSta *usapSta, Buffer *mBuf));
EXTERN S16 cmUnpkEgTSapSta   ARGS((EgTSapSta *tsapSta, Buffer *mBuf));

EXTERN S16 cmPkEgGenSts    ARGS((EgGenSts *genSts, Buffer *mBuf));
EXTERN S16 cmPkEgMsgSts    ARGS((EgMsgSts *msgSts, Buffer *mBuf));
EXTERN S16 cmPkEgSapSts    ARGS((EgSapSts *sapSts, Buffer *mBuf));

EXTERN S16 cmUnpkEgGenSts    ARGS((EgGenSts *genSts, Buffer *mBuf));
EXTERN S16 cmUnpkEgMsgSts    ARGS((EgMsgSts *msgSts, Buffer *mBuf));
EXTERN S16 cmUnpkEgSapSts    ARGS((EgSapSts *sapSts, Buffer *mBuf));

EXTERN S16 cmPkEgUstaDgnVal  ARGS((EgUstaDgnVal *dgnVal, Buffer *mBuf));
EXTERN S16 cmPkEgUstaDgn     ARGS((EgUstaDgn *dgn, Buffer *mBuf));

EXTERN S16 cmUnpkEgUstaDgnVal ARGS((EgUstaDgnVal *dgnVal, Buffer *mBuf));
EXTERN S16 cmUnpkEgUstaDgn    ARGS((EgUstaDgn *dgn, Buffer *mBuf));

#ifdef EGTP_U
EXTERN S16 cmPkLegStr ARGS((LegStr *legStr, Buffer *mBuf));
EXTERN S16 cmUnpkLegStr ARGS((LegStr *legStr, Buffer *mBuf));
EXTERN S16 cmPkEgIpAddrCntrl ARGS((EgIpAddrCntrl *ipCntrl, Buffer *mBuf));
EXTERN S16 cmUnpkEgIpAddrCntrl ARGS((EgIpAddrCntrl *ipCntrl, Buffer *mBuf));
EXTERN S16 cmPkEgIpAddrStsCfm ARGS((EgIpSts *ipSts, Buffer *mBuf, Pst *pst));
EXTERN S16 cmPkEgSrvrStsCfm ARGS((EgTptSrvrSts *tSrvrSts, Buffer *mBuf));
EXTERN S16 cmUnpkEgTnlStsCfm ARGS((EgTnlSts *tnlSts, Buffer *mBuf));
EXTERN S16 cmUnpkEgSrvrStsCfm ARGS((EgTptSrvrSts *tSrvrSts, Buffer *mBuf));
EXTERN S16 cmUnpkEgIpAddrStsCfm ARGS((EgIpSts *ipSts, Buffer *mBuf, Pst *pst));
EXTERN S16 cmPkEgTnlStsCfm ARGS((EgTnlSts *tnlSts, Buffer *mBuf));
EXTERN S16 cmPkEgIpAddrStsReq ARGS((EgIpSts *ipSts, Buffer *mBuf));
EXTERN S16 cmPkEgSrvrStsReq ARGS((EgTptSrvrSts *tSrvrSts, Buffer *mBuf));
EXTERN S16 cmPkEgTnlStsReq ARGS((EgTnlSts *tnlSts, Buffer *mBuf));
EXTERN S16 cmUnpkEgIpAddrStsReq ARGS((EgIpSts *ipSts, Buffer *mBuf));
EXTERN S16 cmUnpkEgSrvrStsReq ARGS((EgTptSrvrSts *tSrvrSts, Buffer *mBuf));
EXTERN S16 cmUnpkEgTnlStsReq ARGS((EgTnlSts *tnlSts, Buffer *mBuf));
EXTERN S16 cmPkEgSrvrStaReq ARGS((EgTptSrvSta *tserverSta, Buffer *mBuf));
EXTERN S16 cmUnpkEgSrvrStaReq ARGS((EgTptSrvSta *tserverSta, Buffer *mBuf));
EXTERN S16 cmPkEgTnlStaReq ARGS((EgTnlSta *tnlSta, Buffer *mBuf));
EXTERN S16 cmUnpkEgTnlStaReq ARGS((EgTnlSta *tnlSta, Buffer *mBuf));
EXTERN S16 cmUnpkEgTnlStaReq ARGS((EgTnlSta *tnlSta, Buffer *mBuf));
EXTERN S16 cmUnpkEgSrvrStaCfm ARGS((EgTptSrvSta *tserverSta, Buffer *mBuf));
EXTERN S16 cmPkEgTnlStaCfm ARGS((EgTnlSta  *tnlSta, Buffer *mBuf));
EXTERN S16 cmUnpkEgTnlStaCfm ARGS((EgTnlSta  *tnlSta, Buffer *mBuf));
PUBLIC S16 cmPkEgSrvrStaCfm  ARGS((EgTptSrvSta *tserverSta, Buffer *mBuf));
#ifdef EGTP_U_MULTI_THREADED
EXTERN S16 cmPkEgThrdStsCfm ARGS((EgThrdSts *thrdSts, Buffer *mBuf, Pst *pst));
EXTERN S16 cmUnpkEgThrdStsCfm ARGS((EgThrdSts *thrdSts, Buffer *mBuf, Pst *pst));
#endif /* EGTP_U_MULTI_THREADED */
#endif /* EGTP_U */
#endif

/* Layer manager activation functions.
 */
EXTERN S16  smEgActvTsk         ARGS((Pst *pst, Buffer *mBuf));
#ifdef SS_MULTIPLE_PROCS
EXTERN S16  smEgActvInit        ARGS((ProcId proc, Ent ent, Inst inst,
                                      Region region, Reason reason, void **xxCb));
#else
EXTERN S16  smEgActvInit        ARGS((Ent ent, Inst inst,
                                      Region region, Reason reason));
#endif


#ifdef EG
#ifdef SS_MULTIPLE_PROCS
EXTERN S16 egActvInit ARGS((ProcId proc, Ent ent, Inst inst, Region region,
                           Reason reason, Void **xxCb));
#else
EXTERN S16 egActvInit ARGS((Ent ent, Inst inst, Region region, Reason reason));
#endif
EXTERN S16 egActvTsk ARGS((Pst *pst, Buffer *mBuf));
#endif


#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* __LEGX__ */

/********************************************************************30**

         End of file:     leg.x@@/main/12 - Wed Jun  5 16:33:53 2013

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

     ver       pat               init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---                   an              1. initial release.
/main/2      leg_x_001.main_1      rss             1. Egtpu release changes
/main/3      ---                  akulkarni Header updation for eGTP-U release
/main/4      leg_x_001.main_3     rss   1. Multithreaded performance changes 
                                           gaurded under SS_MT_CB flag.
                                        2. EGTP_C Path management functionality
                                           is introduced
/main/5      ---      pmacharla         Initial for eGTP release 2.1
/main/6       leg_x_001.main_5   asaurabh 1. Adding Stat indicators for Normal & Fwd data tunnels 
/main/7      ---      leg_x_001.main_6    psingh  1. Added lclEchoSup for EgGenCfg
/main/8      ---      leg_x_001.main_7    magnihotri  1. Fix timerRes datatype changed from U16 to 
                                                       S16 as per SRegCfgTmr() params
                                                    2. Change for eGTP-C PSF Upgrade
                                                        -Variables added for self and remote interface vesrion 
                                                        -Flag for validity of remote interface version num
/main/9      ---      leg_x_001.main_8     psingh     1. Seq Number Start/End indicator updated to 32bit 
/main/10     ---      leg_x_001.main_9     psingh     1. tSapId added in EgMgmt Struct to index TSAP from TSapLst
/main/11     ---      leg_x_001.main_10    asaurabh   1. Added for S2B and S2A.
/main/12     ---      leg_x_001.main_11    shpandey   1. In structure EgCntrl:Added logMask variable for logging mask 
                                                      2. In structure EgGenSts:fix for ERR IND in periodic reporting 
                                                      3. Added timeToWaitPbTmr in GenCfg                                                      
*********************************************************************91*/
