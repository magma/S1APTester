
/********************************************************************20**

    Name:   EGTP layer

    Type:   C include file

    Desc:   Structures, variables and typedefs required by EGTP

    File:   eg.x

    Sid:      eg.x@@/main/TeNB_Main_BR/TeNB_4.0_OAM_CR/2 - Wed Dec 10 19:13:45 2014

    Prg:    sn

*********************************************************************21*/

#ifndef __EGX__
#define __EGX__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* eg005.201: PSF flag to avoid eNodeB compile error --*/
#ifdef HW
#include "sht.h"
#include "sht.x"
#endif


/** @file eg.x
    @brief EG Include File (eg.x)
*/
#ifdef TIME_MES
#ifdef SS_MT_CB
struct euTime
{
   U32 call;
   struct timespec time[MAX_MSG];
};
struct euTime entryTx[MAX_THREAD];
struct euTime exitTx[MAX_THREAD];
struct euTime entryRx[MAX_THREAD];
struct euTime exitRx[MAX_THREAD];
#else
struct timespec entryTx1[MAX_MSG];
struct timespec exitTx1[MAX_MSG];
struct timespec entryTx2[MAX_MSG];
struct timespec exitTx2[MAX_MSG];
struct timespec entryRx1[MAX_MSG];
struct timespec exitRx1[MAX_MSG];
struct timespec entryRx2[MAX_MSG];
struct timespec exitRx2[MAX_MSG];
#endif
#endif

typedef struct egTSapCb EgTSapCb;
typedef struct egUSapCb EgUSapCb;
typedef struct egTunnCb EgTunnCb;
typedef struct egTptSrvCb EgTptSrvCb;
typedef struct _destAddrCb EgDestAddrCb;
typedef struct _ipCb EgIpCb;




/*----------- EGTP Timer Control Block ---------------*/
typedef struct egTimer
{
   CmTimer        tmr;         /* common timer control block */
   PTR            egCbPtr;     /* pointer to Cb which ownes this EgTimer */
} EgTimer;



#ifdef EGTP_U

typedef struct _teIdCb EgTeIdCb;
typedef struct _egUThreadCb EgUThreadCb;

typedef struct _seqInfo
{
   Bool reOrder;         /**< Reording is currently going or not */
   U32  expSeqNmb;       /**< Expecting sequence number */
   U32  curLastSeq;
   U32 lastRcvdSeq;
   U32  numRcvdPdus;     /**< Algo1 Number of received gpdus */
   U32  winStart;        /**< Algo1 Reording window, start sequence numb */
   EgtUEvnt **pduArray;   /**< Reordering buffer, list of egtUiMsg pointers */
}SeqInfo;


struct _teIdCb
{
   CmHashListEnt        destTeIdEnt;         /**< Key for teId entity in the teIdLst hashlist *
                                               *  maintained in destAddrCb */
   CmHashListEnt        egTeIdEnt;         /**< Key for teId entity in the teIdLst hashlist *
                                               *  maintained in egCb */

/* eg001.201 Adding parameter for determining tunnelType */
#ifdef EGTP_U_REL_9
   U8         tunnelType;      /**<Indicates if tunnel is forwarding or Normal data tunnel */
#endif
   U8         dscp;           /*DS code to be filled in the ip header*/
   U8         reordAlgo;
   EgTimer    reOrderTimer;            /**< Packet Reorder Timer */
   U32        teId;      /**< Tunnel Id established with the destination*/
   SeqInfo    *seqInfo;         /**< Sequence numbers information */
   Bool       endMarker;
   Bool       reOrdering;  /**< This flag represent whether reordering is required or not */
   Cntr       totalMsgsTx;    /**< Total number of messages transmitted */
   Cntr       totalMsgsRx;    /**< Total number of messages received */
   EgUSapCb   *uSapCb;     /**< Associated Upper SAP Cb */
#ifdef REVIEW
   EgDestAddrCb   *dstAddrCb; /*Destination CB*/
   EgTptSrvCb     *tptSrvrCb;
   EgIpCb         *ipCb;
   struct
   {
      U8 hdr[EGU_MSG_MAX_HDR_LEN];
      U8 cnt;
   }preEncHdr;
   U32             remTeid;
#endif /* REVIEW */

};

struct _destAddrCb
{
   CmHashListEnt        destEnt;             /**< Key for destAddrCbLst */
   U32                  echoReqSent;          /**< Cnt about number of echo req sent for this destination */
   U8                   intfType;            /**< Interface Type--*/
/* eg001.201 Adding parameter for keeping stats for Fwd & Normal data tunnel */
   #ifdef EGTP_U_REL_9
   U32 forwardingTunnCnt;                    /**< Number of forwarding tunnels*/
   U32 normaldataTunnCnt;                    /**< Number of normal data tunnels*/
   #endif
   CmTptAddr            destIpAddr;             /**< destination IpAddr */
   Bool                 destReachable;          /*--Destination reachability

                                                  info set by Echo Request*/
   Bool  multicastAddr; /*Multicast Address or not*/
   CmHashListCp         teIdLst;              /**< Hash list containing the list of TEID CB*/
   U16                  maxTPduSize;           /** < Maximum TPDU size for each Ip */
   S32                  channel;               /*Used for multiple Serving-GW and Security-GW support */                  
};

struct _ipCb
{
   CmHashListEnt        ipCbOnUSapEnt;       /**< Key for IpCb Hash list */
   EgIpInfo             ipAddrInfo;          /**< Info about Ip Address */
   CmHashListCp         tptServCbLst;          /**< Hash list of transport contol block */
   EgIpSts               ipStats;            /**< Src Ip statistics */
   U16                  status;                 /**< Info about serOpenReq */
   CmHashListCp          destAddrCbLst;       /**< Hash List about destination  control block */
   Bool                 dfltPort;
   Bool                 encEchoAvail;        /**< Tells whether the decoded buffer is available or not */
};

typedef struct _egUEchoReqCb
{
   CmHashListEnt   echoEnt;       /**< Key for IpCb Hash list */
   U32 seqNo;
   SpId   uSapId;
   Buffer *echoReqBuff;
   EgTptSrvCb *tptServerCb;
   CmTptAddr srcAddr;
   CmTptAddr destAddr;
}EgUEchoReqCb;

typedef struct egTptStat
{
   Cntr         totalMsgsTx;    /* Total number of messages transmitted */
   Cntr         totalMsgsRx;    /* Total number of messages received */
}EgTptStat;


typedef struct _egUcb
{
   CmHashListCp   echoReqHashList;            /**< Hash list maintained to store the echCb */
   CmTimer        echoTimers;                  /**< Echo timer */
   CmTimer        n3t3Timers;                  /**< Echo timer */
   EgUEdmCb       edmUCb;                     /**< Encoder-Decoder Cb */
   Bool           echoTmrStarted;             /**< Falg representing the echo timer is started
                                                  * or not */
   U8             echoReqCntr;                /**< Number of Echo Re-transmission */
}EgUcb;


/* GTP-U Message Types */
#define EGU_ECHO_REQ          1
#define EGU_ECHO_RSP          2
#define EGU_ERROR_IND         26
#define EGU_SUPP_EXT_HDR_NTF  31
#define EGU_END_MARKER        254

/* GTP-U IEs */
#define EGU_RECOVERY_IETYPE   14
#define EGU_TEID_IETYPE       16
#define EGU_GSN_ADDR_IETYPE   133
#define EGU_EXT_HDR_LST_IETYPE 141
#define EGU_PVT_EXTN_IETYPE   255

#endif /* EGTP_U */


/************* ENUMS ************************************************/

typedef enum _egtMsgCat
{
   EG_GTPC_MSGCAT_REQUEST,
   EG_GTPC_MSGCAT_RESPONSE,
   EG_GTPC_MSGCAT_NOTFN,
   EG_GTPC_MSGCAT_ACKN,
   EG_GTPC_MSGCAT_COMMAND,
   EG_GTPC_MSGCAT_IND,
   EG_GTPC_MSGCAT_FAILIND,
   EG_GTPC_MSGCAT_RSP_ACK,
   EG_GTPC_MSGCAT_OTHER
}EgtMsgCat;


/* EGTP Modules Name */
typedef enum _egModuleName
{
   EG_MOD_PCM,
   EG_MOD_PCM_USAP,
   EG_MOD_TPT,
   EG_MOD_EDM_GM,
   EG_MOD_EDM_IE,
   EG_MOD_CPM,
   EG_MOD_INVALID
}EgModuleName;

/* Actions posssible on transport server (in fn egTptProcessTsapServers) */
typedef enum _egTptSrvAct
{
   EG_TPT_TPTSRV_INVLD,
   EG_TPT_TPTSRV_CLOSE,
   EG_TPT_TPTSRV_OPEN,
   EG_TPT_TPTSRV_DISABLE,
   EG_TPT_TPTSRV_FREE
}EgTptSrvAct;



/* Upper SAP Control Block */
struct egUSapCb
{
   State         state;          /* SAP state */
   SuId          suId;           /* service user SAP id */
   Pst           pst;            /* post structure */
   EgUSapCfg     cfg;            /* configuration for this SAP */
   EgSapSts      sts;            /* Statistics */
   EgTSapCb      *tSapCb;        /* Associated TSAP */
#ifdef EGTP_U
   CmHashListCp  ipCbHashList;          /* List of IpCbs */
#endif /* EGTP_U */
/*eg004.201 Modified for PSF RUG: New variables introduced
 *remIntfValid - TRUE/FALSE, if TRUE, remote interface version number stored within pst is valid
 *verContEnt - interface version controlling entity
 */
#ifdef EG_RUG
   Bool remIntfValid;          /* TRUE/FALSE, if TRUE, remote interface
      						  version number stored within pst is valid */
   Ent verContEnt;             /* interface version controlling entity */
#endif /* EG_RUG */
#ifdef HW
   CmPFthaRsetMap egHwCb;
#endif
};



/*********************************************************************
* Transport Module structures                                        *
**********************************************************************/
/**
    @ingroup TPTMOD
    @struct egTSapCb
    @brief Control Block for Transport SAP
 */
/*eg007.201: TSapCb updated to accomodate list of destination as dstCbLst
             and IP addr indicator to the tSapCb */
struct egTSapCb
{
   Pst           pst;                 /**< Post structure */
   Ent           contEnt;             /**< Controlling entity */
   Bool          cfgDone;             /**< Config done */
   SuId          suId;                /**< Service user SAP id */
   SpId          spId;                /**< Service provider id */
   State         state;               /**< State of this SAP */
   EgTSapCfg     cfg;                 /**< Transport SAP configuration   */
   EgSapSts      sts;                 /**< Statistics */
   EgTSapReCfg   reCfg;               /**< Transport SAP reconfiguration */
   U8            bndRetryCnt;         /**< Current bind retry count */
   U8            numSrvr;             /**< Number of active servers */
   UConnId       lastSuConnId;        /**< Last suConnId generated on this SAP */
   EgTptSrvCb    **tptSrvCbLst;       /**< Tpt Server CB List - key SuConnId */
   CmTimer       timers[EG_MAX_TMRS]; /**< Max simultenous timers */
   EgTimer        bndTmr;             /**< Bind timer control block*/
   U32            trcMask;            /**< Trace mask */
   S16            trcLen;             /**< Trace length */
   Pst            cfmPst;             /**< Post structure used for LM confirms       */
   Header         ctrlHdr;            /**< Header from pending control request       */
   CmTptAddr     tSapIpAddr;          /**< IP addr identifier for tSap */
   Bool          ipCfgDone;           /**< Indicator for IP existing in tSap */
};


/**
  @ingroup TPTMOD
  @struct egTptSrvCb
  @brief Control Block for Transport Server */
struct egTptSrvCb
{
#ifdef EGTP_U
   CmHashListEnt  transportEnt;  /* Key to get the transport Cb in transCbHashList *
                                  * of IpCb */
   EgIpCb         *ipCbPtr;              /* Ip Control block Pointer */
   EgTptStat      stats;                /* Statistics of transCb */
   U16            portNum;
   U32            uSapId;               /* upper Sap Id */
   Bool          portStatus; /*Set by echo Request*/
   Bool          isdftlTptSrv; /* Is this default server? */
#endif /* EGTP_U */
   UConnId        suConnId;      /**< Server connection id */
   UConnId        spConnId;      /**< Server connection id */
   U8             state;         /**< Transport state */
   TknStrOSXL     hostName;     /**< Server's host/domain name(host.domain)*/
   EgTptSrvCfg    cfg;           /**< Server configuration */
   EgUSapCb       *uSapCb;       /**< Associated USAP */
   EgTSapCb       *tSapCb;       /**< Associated TSAP */
   EgTimer        opnSrvTmrNode; /**< Open Server Timer control block*/
#ifdef S1SIMAPP
   EgTimer        tstSrvTmrNode; /**< Open Server Timer control block*/
#endif

   S16            opnSrvCurRetryCnt; /**< Tpt Srv open current retry     *
                                       *  attempt                       */
/*eg004.201 Modified for PSF :PSF Control block added*/
#ifdef HW
   CmPFthaRsetMap  egHwCb;
#endif
};

/*eg004.201 Modified for PSF RUG:EgVerInfoCb structure to control Rolling Upgrade
 *introduced with interfaceInfo and PSF control block object
 */
#ifdef TDS_ROLL_UPGRADE_SUPPORT
#ifdef EG_RUG
typedef struct _egVerInfoCb
{
   ShtVerInfo intfInfo;
#ifdef HW
   CmPFthaRsetMap egHwCb;
#endif /* HW */
}EgVerInfoCb;
#endif /* EG_RUG */
#endif /* TDS_ROLL_UPGRADE_SUPPORT */

/******* EGTP Global Control Block *******/
/**
    @struct _egCb
    @brief Control block for EGTP global control block
 */
/* eg006.201: Parameter, echoSeqNum, indictes Echo Sequence Number */
/*eg007.201: egCb updated to accomodate list of tSaps as tSapLst
             dstCbList, and echoSap ptr is removed --*/
typedef struct _egCb
{
   TskInit         init;               /**< Task initialization info. */
   EgGenCfg        genCfg;             /**< general configuration */
   EgGenSts        genSts;             /**< general statistics */
   EgGenSta        genSta;             /**< General status */
   EgUSapCb        **egtSapLst;        /**< Array of pointers to upper SAPs */
#ifdef EG_MULTI_IP
   EgTSapCb       **tSapLst;         /**< Pointer to Transport SAP Control Block */
#else
   EgTSapCb        *tSapCb;            /**< Pointer to Transport SAP Control Block */
#endif
#ifdef SS_MULTIPLE_PROCS
   U8            used;
#endif
   CmTqCp          egTqCp;             /**< timing queue control point */
   CmTqType        egTq[EG_TQSIZE];    /**< timing queue */
   U8              outOfRsrc;          /**< out of resources */
   Bool            shutdown;           /**< Layer is shutting down             */
   Bool            ieCfgDone;          /**< IE Config is done or not? */
#ifdef EGTP_U
  EgUcb          egUCb;                /**< EGTP-U Control Block */
#endif /* EGTP_U */
/*eg004.201 Added for PSF RUG- New variables introduced
 *numIntfInfo - Number of stored interface information
 *egVerInfoCb - Interface Version information store
 */
#ifdef EG_RUG
   U16           numIntfInfo;    /* Number of stored interface information */
   EgVerInfoCb   *egVerInfoCb;   /* Interface Version information store */
#endif /* EG_RUG */
#ifdef HW
   CmPFthaRsetMap  egHwCb;
#ifdef SS_MULTIPLE_PROCS
   Void *psfCb;
#endif
#endif
#ifdef REVIEW
CmHashListCp  egTeidHashListCp;          /* List of IpCbs */
#endif /* REVIEW */
} EgCb;



#ifdef EGTP_U
/* In case of multi threading this structure is used by main threaed to  *
 * send information to worker threaded */
typedef struct _eguEvnt
{
   U8           msgType;    /**< Msg Type */
   U16          seqNumber;  /**< Sequence Number */
   U32          teid;    /**< Local Tunnel Identifier */
   CmTptAddr    localAddr; /**< Local node address */
   CmTptAddr    remAddr;   /**< Remote node address */
   EgTptSrvCb   *srvCb;
   U8           intfType;   /**< This info will be used by EDM */
   S16          resultType; /**< Stores the result for sending to application */
   Region       region;
   Pool         pool;
   U8           failedIeInst;       /**< stores the failed IE Inst */
   U8           failedIeType;       /**< stores the failed IE type */
   U8           failedMsgType;      /**< stores the failed msg type */
   U16          maxTPduSize;
   U16          tPduSize;
   Bool         isEnc;
   U8           eventType;  /**< Event Type */
   EgTeIdCb     *teIdCb;
   EgDestAddrCb *destAddrCb;
   EgIpCb       *ipCb;
   EgUSapCb     *usap;
   EgTSapCb     *tsap;
   EgMngmt      *lmInfo;    /**< confirm structure */
   Bool         errInd;   /*<Flag to tell if Error Indication needs to be
                           generated>*/
   Bool         suppExtHdrNtf; /*<Flag to tell whether Supp Ext Hdr Not message is
                                 generated by GTP-U later or Application>*/
   Buffer    *mBuf;        /**< Msg Buffer -- For Decoding */
   EgUMsg    *egMsg;       /**< Msg -- For Encoding */
}EgUEvnt;

#endif /* EGTP_U */

#ifdef SS_MULTIPLE_PROCS
EXTERN EgCb  egCbLst[EG_MAX_INSTANCES];
EXTERN EgCb  *egCbPtr;
#else
EXTERN EgCb  egCb;
#endif /* SS_MULTIPLE_PROCS */


/**
    * @ingroup TPTMOD
    * @brief This function initializse the Transport Module of EGTP
    * @details This function initializse the Transport Module of EGTP
    *
    * @return  ROK - Success, RFAILED - Failure
    */

EXTERN S16  egTptInit ARGS (( Void ));
/**
    * @ingroup TPTMOD
    * @brief This function deinitializse the Transport Module of EGTP
    * @details This function deinitializse the Transport Module of EGTP
    *
    * @return  ROK - Success, RFAILED - Failure
    */

EXTERN Void egTptDeInit ARGS (( Void ));
/**
    * @ingroup TPTMOD
    * @brief This function receive the EGTP Message from Lower layer
    * @details This function is called by Lower Layer when ever a new
    * EGTP messages is received from TUCL.
    *
    * @param[in] localAddr Pointer to the Transport Server Address.
    *
    * @param[out] state  Pointer to the State of Tranport Server
    *
    * @return  ROK - Success, RFAILED - Failure
    */

EXTERN S16  egTptState ARGS (( CmTptAddr  localAddr, TknU8 *state));

/**
    * @ingroup TPTMOD
    * @brief This function perform the given action on Transport Servers
    * @details This function perform the given action on Transport Servers
    *           in  Given Tranport SAP.
    *
    * @param[in] tsapCb Pointer to the Transport SAP Control Block.
    *
    * @param[in] srvAction  Action to be performed on Transport Servers
    *
    * @return  ROK - Success, RFAILED - Failure
    */

EXTERN S16  egTptProcessTsapServers ARGS ((
                             EgTSapCb    *tsapCb,
                             EgTptSrvAct srvAction));

/**
    * @ingroup TPTMOD
    * @brief This function handles the opening of Transport Server
    * @details This function handles the opening of Transport Servert
    *
    * @param[in] serverCb Pointer to the Transport Server Control Block.
    *
    * @param[in] reason  Pointer to the reason
    *
    * @return  ROK - Success, RFAILED - Failure
    */

EXTERN S16  egTptOpenServer ARGS ((
                             EgTptSrvCb    *serverCb,
                             U16           *reason));

/**
    * @ingroup TPTMOD
    * @brief This function handles closing of Transport Server
    * @details This function handles closing of Transport Server
    *
    * @param[in] serverCb Pointer to the Transport Server Control Block.
    *
    * @return  Void
    */

EXTERN Void  egTptCloseServer ARGS ((
                             EgTptSrvCb    *serverCb ));

/**
    * @ingroup TPTMOD
    * @brief This function frees the Transport Server
    * @details This function frees the Transport Server
    *
    * @param[in] serverCb Pointer to the Transport Server Control Block.
    *
    * @return  Void
    */

EXTERN Void  egTptFreeServer ARGS ((
                             EgTptSrvCb    *serverCb ));

/*********************************************************************
 **************************** MI Module ***************************
 ********************************************************************/
/**
  @brief The indication of transport server open is handled.

  @details This Function handles the sending of unsolicited status alarm towards layer
manager indicating the success of server open event.

  @param[in] srvCb The transport server control block. <br>
  It is an IN parameter for this method.

  @return   void <br>

  */

EXTERN Void egMiTptSrvOpenInd ARGS((
               EgTptSrvCb   *srvCb
               ));

/**
  @brief The indication of transport server close is handled.

  @details This Function handles the sending of unsolicited status alarm towards layer
manager indicating the success of server close event.

  @param[in] srvCb The transport server control block. <br>
  It is an IN parameter for this method.

  @return   void <br>

  */

EXTERN Void egMiTptSrvCloseInd  ARGS ((
                                   EgTptSrvCb   *serverCb,
                                   Bool            fromLMI  ));

/**
  @brief The memory for the requested size is allocated.

  @details This Function handles the allocation and initialization of memory from the
reserved memory for the layer. The memory avalability is checked before allocation.

  @param[in] size The number of bytes to be allocated. <br>
  It is an IN parameter for this method.

  @return   Pointer - Static buffer pointer <br>
            NULLP - Memory allocation failure <br>

  */

EXTERN Data *egAlloc ARGS
((
Size size                                  /* size of the buffer required */
));

/**
  @brief The memory for the requested size is deallocated.

  @details This Function handles the deallocation of memory from the specified memory
location.

  @param[in] pCb The start of the memory location. <br>
  It is an IN parameter for this method.

  @param[in] size The number of bytes to be deallocated. <br>
  It is an IN parameter for this method.

  @return   ROK - Deallocation success. <br>

  */

EXTERN S16 egFree ARGS
((
Data *pCb,                                 /* pointer to the buffer to be deallocated */
Size size                                  /* size of the buffer */
));

/**
  @brief The unsolicited status indications are sent to layer manager.

  @details This Function handles the sending of unsolicited status towards layer manager.
The function is called only when unsolicited status is enabled for the layer.

  @param[in] category The category of unsolicited event. <br>
  It is an IN parameter for this method.

  @param[in] event The unsolicited event occurred. <br>
  It is an IN parameter for this method.

  @param[in] cause The cause for the unsolicited event. <br>
  It is an IN parameter for this method.

  @param[in] dgn The diagnostic parameters for the alarm. <br>
  It is an IN parameter for this method.

  @return   ROK - Alarm sending success. <br>

  */

EXTERN S16 egSendLmAlarm ARGS
((
U16           category,                    /**< category */
U16           event,                       /**< event */
U16           cause,                       /**< cause */
EgUstaDgn     *dgn                         /**< diagnostics structure */
));

/**
  @brief The confirms for the layer manager requests are sent.

  @details This Function handles the sending of solicited confirms towards layer manager.
It sends the confirms for configuration, control, status, statistics requests sent from
layer manager.

  @param[in] pst The layer manager post structure. <br>
  It is an IN parameter for this method.

  @param[in] hdr The header for the confirm. <br>
  It is an IN parameter for this method.

  @param[in] type The type of confirm. <br>
  It is an IN parameter for this method.

  @param[in] cfm The confirmation parameters. <br>
  It is an IN parameter for this method.

  @return   ROK - Alarm sending success. <br>
            RFAILED - Alarm sending failure. <br>

  */

EXTERN S16 egSendLmCfm ARGS
((
Pst              *pst,                     /* post structure */
Header           *hdr,                     /* header */
U8               type,                     /* type of confirm */
EgMngmt          *cfm                      /* confirm structure */
));

/**
  @brief The control confirm for the layer manager requests is sent.

  @details This Function handles the sending of solicited control confirm towards layer
manager.

  @param[in] pst The layer manager post structure. <br>
  It is an IN parameter for this method.

  @param[in] status The status of control request event for the confirm. <br>
  It is an IN parameter for this method.

  @param[in] reason The reason of control request event for the confirm. <br>
  It is an IN parameter for this method.

  @param[in] hdr The header for the control confirm. <br>
  It is an IN parameter for this method.

  @return   void <br>

  */

EXTERN Void egSendLmCntrlCfm  ARGS((Pst      *pst,
                                    U16      status,
                                    U16      reason,
                                    Header   *hdr));

/**
  @brief The message trace indications are sent towards the layer manager.

  @details This Function handles the sending of message trace indications towards layer
manager. It also provides the event information and the source and remote addresses.

  @param[in] tsapCb Pointer to the Transport SAP Control Block.

  @param[in] elmnt The type of element. <br>
  It is an IN parameter for this method.

  @param[in] srcAddr The source address. <br>
  It is an IN parameter for this method.

  @param[in] destAddr The destination address. <br>
  It is an IN parameter for this method.

  @param[in] evnt The trace event type indication. <br>
  It is an IN parameter for this method.

  @param[in] mBuf The message sent or received. <br>
  It is an IN parameter for this method.

  @return   void <br>

  */

/* eg009.201: Modified proc to accept TSAP cb as argument */
EXTERN Void egGenTrcInd ARGS
((
EgTSapCb *tSapCb,                          /* TSap associated          */
S16      elmnt,                            /* type of element to trace */
CmTptAddr *srcAddr,                        /* Destination IP-address/port */
CmTptAddr *destAddr,                       /* Destination IP-address/port */
U16      evnt,                             /* trace event type */
Buffer   *mBuf                             /* message being traced */
));


/*********************************************************************
 **************************** TIMER Module ***************************
 ********************************************************************/
EXTERN S16   egSchedTmr       ARGS ((Ptr egHandle,
                                     S16 tmrEvnt,
                                     Action action, U32 tmrVal));

EXTERN Void   egTmrEvnt       ARGS ((Ptr cb,
                                     S16 event));

EXTERN Void egCmInitTimer          ARGS((EgTimer *tmr));

EXTERN S16 egRegInitTmr          ARGS((Void));

EXTERN Void egRmvTmr ARGS (( PTR      cbp,
                             CmTimer  *pTimerStruct,
                             U8       tmrNum,
                             U8       maxNmbTmrs));

/*********************************************************************
 **************************** Debug Prints ***************************
 ********************************************************************/
EXTERN Void egCmPrntDbg ARGS(( U8    ptrType,
                               void  *ptr,
                               S8    *name
                               ));

EXTERN Void PrintEGTPStats ARGS ((void 
                                ));

EXTERN Void ResetEGTPStats ARGS ((void
                                ));

/*********************************************************************
*             ENCODER     AND       DECODER       FUNTIONS           *
 ********************************************************************/

EXTERN S16  egEdmDeInit ARGS
((
Void
));

EXTERN S16  egAllocIntfLst ARGS
((
U8   nmbIntf          /* Contains the number of interfaces         */
));


EXTERN Size  egGetIntfMem ARGS
((
Void
));


/**
 @brief The function egCpyCmTptAddr is the utility to copy the CmTptAddr
        from source to destination.
 @param[in] dst The pointer to the destination CmTptAddr.
 @param[in] src The pointer to the source CmTptAddr.
 @return
          - ROK      - If the procedure was successful.
          - ROUTRES  - If the procedure failed due to resource failure.
          - RFAILED  - If the procedure failed due to internal reasons.
*/
EXTERN S16 egCpyCmTptAddr ARGS((
                                CmTptAddr *dst,
                                CmTptAddr *src
                                ));

 /**
    * @ingroup TPTMOD
    * @brief This function compares two Transport Addresses
    * @details This function compares two Transport Addresses
    *
    * @param[in] one Pointer to the Transport Address
    * @param[in] two Pointer to the Transport Address
    * @param[out] addressMatch Pointer to result indicating whether addresses
    *                          matches or not
    *
    * @return  Void
    */

EXTERN S16 egCmpTptAddr            ARGS((CmTptAddr  *one,
                                         CmTptAddr  *two,
                                         Bool       *addressMatch));

/*********************************************************************
                  Timer Functions
**********************************************************************/

#ifndef SS_MULTIPLE_PROCS
EXTERN S16 egActvTmr ARGS((Void));
#else
EXTERN S16 egActvTmr ARGS((ProcId proc, Ent ent, Inst inst));
#endif

EXTERN S16 egTptSendMsg ARGS ((EgTptSrvCb *serverCb, CmTptAddr *destAddr, Buffer *mBuf, Pst *pst));

EXTERN S16 egCpmInit ARGS((EgMngmt *cfgReq, EgModuleName module));

EXTERN S16 egCpmDeinit ARGS((Void));

EXTERN S16 egInitExt ARGS((Void));

EXTERN S16 egGetSId ARGS((SystemId *sysId));
/**
  @ingroup TUNNMNGMT
  @brief The function egUpdateTxStatistics is an utility to update the
        SAP statistics for transmitted message.
  @param[in] msgType The msgType is the type of the sent messasge.
  @param[in] sts The sts is the pointer to the Sap statistics on which the
                message was sent.
*/
EXTERN Void egUpdateTxStatistics ARGS ((
                                   EgtMsgType msgType,
                                   EgSapSts *sts
                                   ));

/**
  @ingroup TUNNMNGMT
  @brief The function egUpdateRxStatistics is an utility to update the
        SAP statistics for received message.
  @param[in] msgType The msgType is the type of the received messasge.
  @param[in] sts The sts is the pointer to the Sap statistics on which the
                message was received.
*/
EXTERN Void egUpdateRxStatistics ARGS ((
                                        EgtMsgType msgType,
                                        EgSapSts *sts
                                        ));


EXTERN S16 egTptUdpServerDatReq ARGS ((
                           EgTptSrvCb      *serverCb,
                           CmTptAddr       *destAddr,
                           Buffer          *mBuf,
                           Pst             *pst,
                           U8               tos     ));

#ifdef EGTP_U
EXTERN  S16 egUCpmProcLiMsg
(
 EgUEvnt *eguEvnt,          /* Event structure --*/
 Pst     *pst
 );


EXTERN  S16 egFTunProcEguDatReq
(
EgtUEvnt *egtUEvnt,       /* Event from UI --*/
EgUSapCb *usap,            /*Upper Sap CB*/
Pst      *pst
);

EXTERN Void egUCpmProcUiMsg
(
EgUEvnt *eguEvnt,          /* Event structure */
Pst     *pst
);    

EXTERN Void egFUCpmProcUiMsg
(
EgTeIdCb     *teIdCb,
EgUMsg       *egMsg,
Pst          *pst
);


EXTERN S16 egUFEncodeGmHdr
(
   U8 *preEncHdr,
   EgUMsgHdr *statHdr,
   U8 *hdrIndex
);

EXTERN S16 egFpTunProcFwdEguDatReq
(
U32 lclTeid,
U32 remTeid,
U32 tPduSise,
Buffer *mBuf,
U32 pdcpSduId,
U32 pdcpSeqNo
);

EXTERN S16 egFTunProcEguDatReq
(
EgtUEvnt *egtUEvnt,       /* Event from UI --*/
EgUSapCb *usap,            /*Upper Sap CB*/
Pst      *pst
);

EXTERN S16 egFUEncMsgReq
(
   EgtUEvnt *evntMsg,        /* Event message having the Msg to encode msg
--*/
   EgTeIdCb *teIdCb,
   Buffer   **mBuffer
);
EXTERN S16 egLiPrcBndCfm 
(
SuId        suId,
EgTSapCb    *tsapCb,
U16         result
);   


/**
 * @defgroup EDMMOD Encoder-Decoder Module
 */
/**
 * @ingroup EDMMOD
 * @brief This function encodes the EGTP-U Message
 * @details  This function is entry function for EDM module on
 *           Encoding side. It is called by CPM module for encoding
 *           a message received from the application.
 *
 * @param[in] evntMsg Event structure containing the EGTP-U message
 *                    to be encoded
 *
 * @return  ROK - Success, Error Code for Failure
 */

EXTERN S16 egUEncMsgReq ARGS((EgUEvnt *evntMsg));

    /**
    * @ingroup EDMMOD
    * @brief This function decodes the EGTP-U Message
    * @details  This function is entry function for EDM module on
    *           Decoding side. It is called by CPM module for decoding
    *           a message received from the lower layer.
    *
    * @param[in] evntMsg Event structure containing the mBuf to be encoded
    *
    * @return  ROK - Success, Error Code for Failure
    */
EXTERN S16 egUDecMsgReq ARGS((EgUEvnt *evntMsg));

EXTERN S16 egUTptGetMsg ARGS((EgTptSrvCb *serverCb, CmTptAddr *srcAddr, Buffer *mBuf, Pst *pst));
EXTERN S16 egUCmCreateEvent ARGS((EgUEvnt **newEvent));
EXTERN S16 egTunProcEguDatReq ARGS((EgtUEvnt *egtUEvnt, EgUSapCb *usap, Pst *pst));
EXTERN S16 egTunProcEguTnlMgmtReq ARGS((EgtUEvnt *egtUEvnt, EgUSapCb *usap));
EXTERN S16 egUTunnTeidMod ARGS ((EgtUEvnt *egtUEvnt, EgIpCb *ipCb));
EXTERN S16 egUTunnTeidDel ARGS((EgtUEvnt *egtUEvnt, EgIpCb *ipCb, EgUSapCb *usap));
EXTERN S16 egUTunnTeidReordEna ARGS((EgtUEvnt *egtUEvnt, EgIpCb *ipCb));
EXTERN S16 egUTunnTeidReordDis ARGS((EgtUEvnt *egtUEvnt, EgIpCb *ipCb, EgUSapCb *usap));
EXTERN S16 egUTunnTeidAdd ARGS((EgtUEvnt *egtUEvnt, EgIpCb *ipCb));
EXTERN S16 egTunProcEguStaReq ARGS((EgtUEvnt *egtUEvnt, EgUSapCb *usap));
EXTERN S16 egUFreeUiEvnt ARGS((EgtUEvnt *egtUEvnt));
EXTERN S16 egUCpmHdlEvt ARGS((EgUEvnt *eguEvnt, Pst *pst));
EXTERN S16 egTnlFreeReOrderQReq ARGS((Inst  threadId));
EXTERN S16 egUTunnDeleteTunnel ARGS((EgUEvnt *eguEvnt));
EXTERN S16 egUCmFreeEvent ARGS ((EgUEvnt *event));


EXTERN S16 egUPlatTunnTeidAdd ARGS((EgDestAddrCb *dstCb));
EXTERN S16 egUPlatTunnTeidDel ARGS((EgDestAddrCb *dstCb));

EXTERN S16 egReordRcvdEguMsgs ARGS((EgTeIdCb *teidCb, EgtUEvnt *egtuEvt));

EXTERN Void egUCpmProcMsg ARGS((EgUEvnt *eguEvnt, Pst *pst));

EXTERN S16 egUCpmHdlTeid ARGS((EgUEvnt *eguEvnt));

EXTERN S16 egGetThrdId ARGS((EgTeIdCb **egTeidCb, S16 event, EgUThreadCb **pThrCb));

EXTERN S16 egAssignThrd ARGS((EgTeIdCb  *egTeidCb));

EXTERN S16 egLdDistribute ARGS((Void));

EXTERN S16 egFlushReordRcvdGtpuPdus ARGS((EgTeIdCb *teidCb));
EXTERN S16 egFlushAllPackets ARGS((EgTeIdCb *teidCb));
EXTERN S16 egFlushTillHole ARGS((EgTeIdCb *teidCb));

EXTERN S16 egDeleteTun ARGS((EgTeIdCb *teidCb));
EXTERN S16 egSchedreOrdTmr ARGS((Ptr egHandle, S16 tmrEvnt, Action action, U32 tmrVal));
EXTERN S16 egUTunnReordCfm ARGS((EgUEvnt *eguEvnt));
EXTERN S16 egUHndlT3N3TmrExpiry ARGS((Void));
/* eg012.201 : Modified prototype of egUSendEchoReqOnLclPort,removed EchoReqCb */
EXTERN S16 egUSendEchoReqOnLclPort ARGS((EgIpCb *ipCb, EgUEvnt *echoEvnt,
                                    U16 *echoSeqNo));
EXTERN S16 egUSendEchoReq ARGS((Void));
EXTERN S16 egMiProcIpCb ARGS((EgIpCb *ipCb, SpId spId));
EXTERN Void egUCpmProcEguDatReq ARGS((EgtUEvnt *egtUEvnt, EgUSapCb *usap, Pst *pst));
EXTERN Void egUCpmProcEguStaReq ARGS((EgtUEvnt *egtUEvnt, EgUSapCb *usap));
EXTERN Void egUCpmProcEguTnlMgmtReq ARGS((EgtUEvnt *egtUEvnt, EgUSapCb *usap ));
EXTERN S16 EgMiHdlCntrlCfmFrmWrkr ARGS((EgUEvnt *eguEvnt));
EXTERN S16 egMiRmvEchoCb ARGS((EgUSapCb *uSapCb, EgIpCb *ipCb, EgTptSrvCb *srvCb,
                                                         EgTSapCb *tSapCb, U8 type));
EXTERN S16 egMiGetIpCb ARGS((EgUSapCb *uSapCb, EgMngmt *cntrlReq, U8 eventType, U8 *nmbReq));
EXTERN S16 egMiIpCbDeInit ARGS((CmHashListCp *IpCbHashList, Bool del));
EXTERN S16 egHndlRecvFb ARGS ((U8 *buf, U32 bufLen ));
#endif /* EGTP_U */

/************************************************
 * eg007.201: TsapCb reference                  *
*************************************************/
/**
  @ingroup TPTMOD
  @brief The function egTptGetTsapFrmAddr provides tSapCb from the IP address
         assocciated
 @param[in] tptSrvAddr The Ip address for which associated TSapCb needs to be found
 @param[in] tSapCb     The TSapCb ptr which will be updated with tSapCb associated to
                       given IP
 @return
   - ROK      - If the procedure was successful.
   - RFAILED  - If the procedure failed due to internal reasons.
 */


/*eg007.201: dstCbList, and echoSap ptr is removed --*/
PUBLIC S16 egTptGetTsapFrmAddr  ARGS (( CmTptAddr   tptSrvAddr, EgTSapCb **tSapCb));


EXTERN S16 SGetReadPtr(Buffer *mBuf, U8** data, MsgLen *len);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __EGX__ */


/**********************************************************************

         End of file:     eg.x@@/main/TeNB_Main_BR/TeNB_4.0_OAM_CR/2 - Wed Dec 10 19:13:45 2014

**********************************************************************/

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
/main/1      ---      sn                1. Created for Initial Release 1.1
/main/2      ---      rss               1. Initial for eGTP 1.2 Release
/main/2      eg001.102    snatarajan        1. EGTP_C Path management functionality is introduced.
                          rss               2. Multithreaded performance changes gaurded under SS_MT_CB flag.
/main/3      ---      pmacharla       Initial Release of eGTP 2.1 release
/main/3      eg001.201    asaurabh      1.  Adding parameter for determining tunnelType
                                        2.  Adding parameter for keeping stats for Fwd & Normal data tunnel
/main/3      eg004.201    magnihotri  1.Modified for PSF RUG: New variables introduced
                                        remIntfValid - TRUE/FALSE, if TRUE, remote interface version number stored
                                        within pst is valid
                                        verContEnt - interface version controlling entity
                                      2.Modified for PSF RUG: New variables introduced
                                        remIntfValid - TRUE/FALSE, if TRUE, remote interface version number store
                                      3.Modified for PSF:PSF Control block added
                                      4.Modified for PSF RUG:EgVerInfoCb structure to control Rolling Upgrade
                                        introduced with interfaceInfo and PSF control block object
                                      5.Modified for PSF RUG:local teid added to associate the respective egIncReq
                                        with the teid;egHwCb added as the PSF control block
                                      6.Modified for PSF:PSF Control block object introduced in EgTECCb
                                      7.Added for PSF RUG:New function to get the interface version
                                      8.Added for PSF - RUG: New variables introduced
                                        numIntfInfo - Number of stored interface information
                                        egVerInfoCb - Interface Version information store
                                      9.Function Prototype qualifier changed from PUBLIC to EXTERN
/main/3      eg005.201    psingh       1.PSF flag added to avoid eNodeB build error
/main/3      eg006.201    psingh       1. Parameter connTunnCnt introduced to keep track of
                                          number of connected tunnels per destination
                                       2. Parameter to keep the count of  echo request sent
/main/3      eg007.201    psingh       1. dstCblist moved from egCB to egTSapCb
                                       2. USapCb ptr, echoSap, inside egCb removed
                                       3. egTSapCb updated with tSapIPAddress & ipConfig flag
/main/3      eg009.201    asaurabh     1. Modified proc to accept TSAP cb as argument
/main/3      eg010.201    asaurabh     1. Buffer to store message to be piggybacked
/main/3      eg012.201    shpandey     1. Modified prototype of egUSendEchoReqOnLclPort,removed EchoReqCb
                                       2. Enhanced the piggy backing feature by adding the Timer
*********************************************************************91*/
