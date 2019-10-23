

/********************************************************************20**

     Name:     Layer Manager Interface - SCTP

     Type:     C include file

     Desc:     Structures, variables and typedefs required by the
               layer manager

     File:     lsb.x

     Sid:      lsb.x@@/main/11 - Thu Jul 31 10:16:46 2008

     Prg:      wvdl, bk

*********************************************************************21*/

#ifndef __LSBX__
#define __LSBX__

#ifdef __cplusplus
extern "C" {
#endif


/*
*     The defines declared in this file correspond to defines
*     used by the following TRILLIUM software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*     1000xxx     SIGTRAN - SCTP
*
*/

/*
*     This software may be combined with the following TRILLIUM
*     software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*     1000xxx     SIGTRAN - Adaptation Layers
*
*/


/* typedefs */

/* SCTP General Reconfigurable Structure */
typedef struct _sbGenReCfg         /* SCTP General Reconfiguration */
{
   U8              maxInitReTx;    /* Maximum Association Init Retransmits */
   U8              maxAssocReTx;   /* Maximum Retransmissions for an
                                    * association */
   U8              maxPathReTx;    /* Maximum Retransmission for a destination
                                    * address */
   Bool            altAcceptFlg;   /* Accept or don't accept additional life
                                      time parameter for init from peer */
   U16             keyTm;          /* Initial value for MD5 key expiry timer */
   SctRTT          alpha;          /* Used in RTT calculations */
   SctRTT          beta;           /* Used in RTT calculations */
/* lsb_x_001.main_6: SATELLITE SCTP feature */
#ifdef SB_ECN
   Bool            ecnFlg;         /* Enable/Disable ECN Feature */
#endif /* SB_ECN */
/* lsb_x_001.main_6: Moved from GenCfg to General reConfig structure */
/* lsb_x_001.main_7: Protected under compile-time flag */
#ifdef LSB9
   Pst         smPst;              /* layer manager post structure for alarms */
#endif
} SbGenReCfg;


/* SCTP General Configuration Structure */
typedef struct _sbGenCfg       /* SCTP General Configuration */
{
/* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   U8          ipv6SrvcReqdFlg; /* IPV6 service required for sctp */ 
#endif
   U8          serviceType;     /* TUCL transport protocol (IP/UDP) */
   U16         maxNmbSctSaps;   /* max no. SCT SAPS */
   U16         maxNmbTSaps;     /* max no. Transport SAPS */
   U16         maxNmbEndp;      /* max no. endpoints */
   U16         maxNmbAssoc;     /* max no. associations */
   U16         maxNmbDstAddr;   /* max no. dest. addresses */
   U16         maxNmbSrcAddr;   /* max no. src. addresses */
/* lsb_x_001.main_6: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   U16         maxNmbPathProfs; /* max no. path profiles */
#endif /* SB_SATELLITE */
   U32         maxNmbTxChunks;  /* max no. outgoing chunks */
   U32         maxNmbRxChunks;  /* max no. recv chunks */
   SctStrmId   maxNmbInStrms;   /* max no. in streams PER ASSOCIATION */
   SctStrmId   maxNmbOutStrms;  /* max no. out streams PER ASSOCIATION */
   U32         initARwnd;       /* max receiver window space */
   U16         mtuInitial;      /* Initial MTU size */
   U16         mtuMinInitial;   /* Initial minimum MTU size */
   U16         mtuMaxInitial;   /* Initial maximum MTU size */
   Bool        performMtu;      /* Perform path MTU discovery */
   U16         timeRes;         /* timer resolution */
/* lsb_x_001.main_6: Moved to General reConfig structure */ 
/* lsb_x_001.main_7: Protected under compile-time flag */
#ifndef LSB9
    Pst         smPst;           /* layer manager post structure for alarms */
#endif
   U8          hostname[CM_DNS_DNAME_LEN]; /* Own Domain Name */
   Bool        useHstName;      /* Flag whether hostname is to be used in 
                                 *  INIT and INITACK msg */
   SbGenReCfg  reConfig;        /* reconfigurable params */

/* lsb_x_002.main_2: compile time flag to make udp port as configurable parameter */
#ifdef LSB5
  U16          srcUdpPort;
  U16          dstUdpPort;
#endif /* LSB5 */
} SbGenCfg;

/* SCTP Upper SAP Reconfiguration Structure */
typedef struct _sbSctSapReCfg /* SCT SAP Reconfiguration */
{
   U16             maxAckDelayTm;     /* Maximum time delay for generating
                                       * Acks */
   U16             maxAckDelayDg;     /* Maximum # of datagrams after which an
                                       * Ack shall be sent */
   SctRTT          rtoInitial;        /* Initial value of RTO */
   SctRTT          rtoMin;            /* Minimum RTO */
   SctRTT          rtoMax;            /* Maximum RTO */
   U16             freezeTm;          /* Default Freeze timer value */
/* lsb_x_001.main_2: Addition - Bundling Changes */
#ifdef LSB4
   U16             bundleTm;          /* Default Bundle timer value */
#endif /* LSB4 */
   U16             cookieLife;        /* Life time for a Valid Cookie */
   U16             intervalTm;        /* Default Heartbeat interval timer
                                       * value */
   /* lsb_x_001.main_5: RFC 4460 related members have been added */
/* RFC 4460 -- TO enable the RFC 4460 features, Layer Manager MUST enable the LSB8 flag */
#ifdef LSB8
   U16             maxBurst;          /* RFC 4460 section 2.14: new protocol
               parameter defined */
   U16             maxHbBurst;        /* RFC 4460 section 2.36: new protocol
               parameter defined */
   SctRTT          t5SdownGrdTm;      /* RFC 4460 -- T5 Shutdown Guard Timer value */
#endif /* LSB8 */
   Bool            handleInitFlg;     /* Flag to indicate whether SCTP should
                                       * handle INIT itself */
   Bool            negAbrtFlg;        /* Negotiate or Abort the init if MIS is
                                       * less than OS */
   Bool            hBeatEnable;       /* Enable HeartBeat by Default */
   U32             flcUpThr;          /* Flow Control upper threshold */
   U32             flcLowThr;         /* Flow Control lower threshold */
   /* sb042.102 - Added change for rolling upgrade */
#ifdef TDS_ROLL_UPGRADE_SUPPORT
   Bool            remIntfValid;  /* remote interface version is valid */
   CmIntfVer       remIntfVer;    /* remote interface version */
#endif
#ifdef SB_ETSI
   U16             maxDataSize;     /* Maximum user data size that can be sent/received on an endpoint */
#endif /* SB_ETSI */
#ifdef SB_CHECKSUM_DUAL
   U8             checksumType;     /* type of checksum to be used in this SAP related Associations */
#endif /* SB_CHECKSUM_DUAL */
  
} SbSctSapReCfg;

/* SCTP Upper SAP Configuration Structure */
typedef struct _sbSctSapCfg    /* SCT SAP Configuration */
{
   Swtch           swtch;         /* Protocol Switch */
   SpId            spId;          /* Service Provider SAP Id */
   Selector        sel;           /* Coupling selector for SCTP user */
   MemoryId        memId;         /* Memory region and pool id for SCTP user */
   Prior           prior;         /* Message priority for SCTP user messages */
   Route           route;         /* Route */
   SbSctSapReCfg   reConfig;      /* Reconfigurable parameters */
} SbSctSapCfg;


/* DNS Configuration  */
typedef struct _sbDnsCfg
{
   CmTptAddr    dnsAddr;          /* DNS Query Transport Address */
   Bool         useDnsLib;        /* Use DNS library */
   U16          dnsTmOut;         /* DNS Timer Value */
   U8           maxRtxCnt;        /* Maximum number of retransmissions */
} SbDnsCfg;


/* SCTP Lower SAP Reconfiguration Structure */
typedef struct _sbTSapReCfg    /* Transport SAP Reonfiguration */
{
   SpId            spId;          /* Service provider SAP ID */
   U8              maxBndRetry;   /* Maximum number of bind retries allowed */
   U16             tIntTmr;       /* Default time to wait for bind confirm */
   SbDnsCfg        sbDnsCfg;      /* Dns Configuration structure */
   /* sb042.102 - Added change for rolling upgrade */
#ifdef TDS_ROLL_UPGRADE_SUPPORT
   Bool            remIntfValid;   /* remote interface version is valid */
   CmIntfVer       remIntfVer;     /* remote interface version */
#endif
} SbTSapReCfg;

/* SCTP Lower SAP Configuration Structure */
typedef struct _sbTSapCfg      /* Transport SAP Configuration */
{
   Swtch           swtch;          /* Protocol Switch */
   SuId            suId;           /* Service User SAP Id */
   Selector        sel;            /* Coupling selector for SCTP provider */
   Ent             ent;            /* Service Provider Entity */
   Inst            inst;           /* Service Provider Instance */
   ProcId          procId;         /* Service Provider Processor Id */
   MemoryId        memId;          /* Memory region and pool id for SCTP
                                    * provider */
   Prior           prior;          /* Message priority for SCTP provider
                                    * messages */
   Route           route;          /* Route */
   SctNetAddrLst   srcNAddrLst;    /* Source Network Address List */
   SbTSapReCfg     reConfig;       /* Reconfigurable parameters */
} SbTSapCfg;

/* lsb_x_001.main_6: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
/* SCTP Path Profile Reconfiguration Structure */
typedef struct _sbPathProfReCfg    /* Transport SAP Reonfiguration */
{
   SctWinSize   initCwnd;       /* Initial Congestion Window Size */
   SctWinSize   initSsthresh;   /* Initial ssthresh value */
   SctRTT       rtoInitial;     /* Initial RTO */
   SctRTT       rtoMin;         /* Minimum RTO */
   SctRTT       rtoMax;         /* Maximum RTO */
   SctRTT       alpha;          /* Used in RTT calculations */
   SctRTT       beta;           /* Used in RTT calculations */
   U16          intervalTm;     /* Default Heartbeat interval timer */
#ifdef LSB4
   U16          bundleTm;       /* Default Bundle timer value */
#endif
   SctStrmId    minOutStrms;    /* Minimum number of outgoing streams */
   U8           bcl;            /* Byte Counting Limit */
   U8           idleCwndRate;   /* Idle Congestion Window Rate */
   U8           frCwndRate;     /* Fast-Retransmit Congestion Window Rate */
   U8           rtrCwndRate;    /* Retransmission Congestion Window Rate */
   U8           maxPathReTx;    /* Maximum Retransmission for a destination */
   Bool         hBeatEnable;    /* Enable HeartBeat by Default */
} SbPathProfReCfg;

/* SCTP Path Profile Configuration Structure */
typedef struct _sbPathProfCfg      /* Path Profile Configuration */
{
   S16               profId;     /* Profile ID */
   SbPathProfReCfg   reConfig;   /* Reconfigurable Parameters */
} SbPathProfCfg;

/* SCTP Destination Address Configuration */
typedef struct _sbDstAddrCfg   /* Destination Address Configuration */
{
   S16         profId;    /* Profile ID */
   CmNetAddr   dstAddr;   /* Destination Network Address */
} SbDstAddrCfg;
#endif /* SB_SATELLITE */

/* SCTP Configuration Structure */
typedef struct _sbCfg          /* Configuration */
{
  union
  {
     SbGenCfg      genCfg;         /* General Configuration */
     SbSctSapCfg   sctSapCfg;      /* SCT SAP Configuration */
     SbTSapCfg     tSapCfg;        /* Transport SAP Configuration */
/* lsb_x_001.main_6: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
     SbPathProfCfg pathProfCfg;    /* Path Profile Configuration */
     SbDstAddrCfg  dstAddrCfg;     /* Destination Address Configuration */
#endif /* SB_SATELLITE */
  } s;
} SbCfg;

/* SCTP Control Structure */
typedef struct _sbCntrl        /* Control */
{
   DateTime       dt;             /* date and time */
   U16            action;         /* action */
   U16            subAction;      /* sub action */
   SpId           sapId;          /* SAP Id */

#ifdef DEBUGP
   U32            dbgMask;        /* Debug Mask */
#endif
   U32            logMask;        /* Logging Mask */
/* lsb_x_001.main_6: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   S16             profId;     /* Profile ID */
   CmNetAddr       dstAddr;    /* Destination Network Address */
#endif /* SB_SATELLITE */
} SbCntrl;

/* SCTP SAP status */
typedef struct _sbSapSta       /* SAP Status */
{
   Swtch  swtch;                   /* Protocol Switch */
   U8     hlSt;                    /* SAP State */
   /* sb042.102 - Added change for rolling upgrade */
#ifdef TDS_ROLL_UPGRADE_SUPPORT
   Bool      remIntfValid;     /* remote version valid in cfm ?*/
   CmIntfVer selfIfVer;        /* self version on this SAP     */
   CmIntfVer remIfVer;         /* remote version on this SAP   */
#endif 
} SbSapSta;

/* SCTP General Status */
typedef struct _sbGenSta       /* General Solicited Status */
{
   U8              status;         /* Status */
   Size            memSize;        /* Memory Size Reserved */
   Size            memAlloc;       /* Memory Size Allocated */
   U16             nmbAssoc;       /* Number of open associations */
   U16             nmbEndp;        /* Number of open endpoints */
   U16             nmbLocalAddr;   /* Number of local addresses in use */
   U16             nmbPeerAddr;    /* Number of peer addresses in use */
} SbGenSta;
/* lsb_x_001.main_9: Adding new structure for timer status */
#ifdef LSB11
typedef struct _sbAddr
{
  CmNetAddr       localAddr; /* Source address of the path */
  CmNetAddr       peerAddr;  /* Destination Address of the path */
} SbAddr;
typedef struct _sbAssocTmrSta
{
   Bool		   state;         /* Timer state: whether running or not */
   U32             tmrVal;        /* Timer expiry time */
   U8		   numPaths;      /* For t3rtx and hbeat timer:Number of instances */
   SbAddr          path[LSB_MAX_PATH]; /* To store all the path on which tmr is running */
} SbAssocTmrSta;
#endif

typedef struct _sbAssocSta     /* Association related solicited status */
{
   UConnId         assocId;        /* association identifier */
   U8              assocState;     /* association state */
   SctNetAddrLst   dstNAddrLst;    /* destination network address list */
   SctNetAddrLst   srcNAddrLst;    /* source network address list */
   CmNetAddr       priNAddr;       /* primary network address */
   SctPort         dstPort;        /* destination port */
   SctPort         srcPort;        /* source port */
/*lsb_x_001.main_8: new members included*/
#ifdef LSB11 
   U32             nmbUnsentDgms;   /* Number of unsent datagrams */
   U32             nmbUnackDgms;    /* Number of unacked datagrams */
   U32             nmbUndelDgms;    /* Number of undelivered datagrams */
   SctWinSize      rwnd;            /* Receiver window size */
   U32             rtxCnt;          /* Association Retransmission count */
/*lsb_x_001.main_9: Timer status is added */
  SbAssocTmrSta   tmr[LSB_MAX_TMRS]; /* Timer Status */
#endif 
} SbAssocSta;

typedef struct _sbDtaSta       /* Destination transport address status */
{
   CmNetAddr       dstNAddr;       /* destination network address */
   SctPort         dstPort;        /* destination port */
   UConnId         assocId;        /* association ID */
   U8              state;          /* destination transport address state */
   U16             mtu;            /* path MTU */
   SctRTT          rto;            /* retransmission timeout */
/* lsb_x_001.main_6: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   S16             profId;         /* Profile ID */
   SctWinSize      initCwnd;       /* Initial Congestion Window Size */
   SctWinSize      initSsthresh;   /* Initial ssthresh value */
   SctRTT          rtoInitial;     /* Initial RTO */
   SctRTT          rtoMin;         /* Minimum RTO */
   SctRTT          rtoMax;         /* Maximum RTO */
   SctRTT          alpha;          /* Used in RTT calculations */
   SctRTT          beta;           /* Used in RTT calculations */
   U16             intervalTm;     /* Default Heartbeat interval timer */
#ifdef LSB4
   U16             bundleTm;       /* Default Bundle timer value */
#endif
   SctStrmId       minOutStrms;    /* Minimum number of outgoing streams */
   U8              bcl;            /* Byte Counting Limit */
   U8              idleCwndRate;   /* Idle Congestion Window Rate */
   U8              frCwndRate;     /* Fast-Retransmit Congestion Window Rate */
   U8              rtrCwndRate;    /* Retransmission Congestion Window Rate */
   U8              maxPathReTx;    /* Maximum Retransmission for a destination */
   Bool            hBeatEnable;    /* Enable HeartBeat by Default */
#endif /* SB_SATELLITE */
/*lsb_x_001.main_8: new members included*/
#ifdef LSB11
   Bool            confirmed;      /* Probing Status             */
   SctRTT          srtt;           /* Smoothed Round trip time   */
   SctRTT          rttVar;         /* Variation in round trip */
   SctWinSize      cwnd;           /* Congestion window size */
   SctWinSize      ssthresh;       /* Slow Start Threshold       */
   S32             bytesOut;       /* Bytes outstanding          */
   U32             rtxCnt;         /* Association Retransmission count */
#endif
} SbDtaSta;

/* lsb_x_001.main_10: Replaced SB_ACC flag with LSB12 */
#ifdef LSB12 
typedef struct _sbTmrSta       /* Destination transport address status */
{
   U32             lifetimeTmr;    /* Lifetime timer             */
   U32             ackDelayTmr;    /* ackDelay timer             */
   U32             cookieTmr;      /* Cookie retransmit Timer    */
   U32             keyTmr;         /* Generate next Key          */
   U32             freezeTmr;      /* Freeze timer               */
/* lsb_x_001.main_2 : Addition - Bundling Changes */
#ifdef LSB4
   U32             bundleTmr;      /* Bundle timer */
#endif /* LSB4 */
   U32             t1InitTmr;      /* initialization timer */
   U32             t2Shutdown;     /* shutdown timer */
   U32             tIntTmr;        /* interface timerassociation ID / Bind retry Tmr*/
   U32             t3rtx;          /* retransmission timer */
   U32             hBeat;          /* roundtrip time */
} SbTmrSta;

#endif  /*  LSB12 */

/* SCTP Status Structure */
typedef struct _sbSsta         /* Solicited status */
{
   DateTime        dt;             /* date and time */
   SpId            sapId;          /* SAP Id */

   union
   {
      SystemId     sysId;          /* system id */
      SbSapSta     sapSta;         /* SCTP upper/lower SAP status */
      SbGenSta     genSta;         /* General Status */
      SbAssocSta   assocSta;       /* Association Status */
      SbDtaSta     dtaSta;         /* Destination transport address Status */
/* lsb_x_001.main_10: Replaced SB_ACC flag with LSB12 */
#ifdef LSB12  
      SbTmrSta     tmrSta;         /* Timer status for test code */
#endif   /* LSB12 */
   } s;
} SbSsta;

/* Statistics counters for incoming and outgoing chunks */
typedef struct _sbChunkSts     /* Statistics counters for chunks */
{
   StsCntr         noInitTx;       /* number INITs sent */
   StsCntr         noInitReTx;     /* number INITs resent */
   StsCntr         noInitRx;       /* number INITs received */

   StsCntr         noIAckTx;       /* number INIT_ACKs sent */
   StsCntr         noIAckRx;       /* number INIT_ACKs received */

   StsCntr         noShDwnTx;      /* number SHUTDOWNs sent */
   StsCntr         noShDwnReTx;    /* number SHUTDOWNs resent */
   StsCntr         noShDwnRx;      /* number SHUTDOWNs received */

   StsCntr         noShDwnAckTx;   /* number SHUTDOWN_ACKs sent */
   StsCntr         noShDwnAckReTx; /* number SHUTDOWN_ACKSs resent */
   StsCntr         noShDwnAckRx;   /* number SHUTDOWN_ACKs received */

   StsCntr         noCookieTx;     /* number COOKIEs sent */
   StsCntr         noCookieReTx;   /* number COOKIEs resent */
   StsCntr         noCookieRx;     /* number COOKIEs received */

   StsCntr         noCkAckTx;      /* number COOKIE_ACKs sent */
   StsCntr         noCkAckRx;      /* number COOKIE_ACKs received */

   StsCntr         noDataTx;       /* number DATAs sent */
   StsCntr         noDataReTx;     /* number DATAs resent */
   StsCntr         noDataRx;       /* number DATAs received */

   StsCntr         noDAckTx;       /* number SACKs sent */
   StsCntr         noDAckRx;       /* number SACKs received */

   StsCntr         noShDwnCmpltTx; /* number of Shutdown completed sent */
   StsCntr         noShDwnCmpltRx; /* number of Shutdown completed sent */

/* sb018.102 Heartbeat statistics added */
#ifdef LSB2
   StsCntr         noHBeatTx;      /* number of HEARTBEATs sent */
   StsCntr         noHBeatRx;      /* number of HEARTBEATs received */

   StsCntr         noHBAckTx;      /* number of HBEAT_ACKs sent */
   StsCntr         noHBAckRx;      /* number of HBEAT_ACKs received */   
#endif

/* sb052.102 Abort Statistics added */
#ifdef LSB3
   StsCntr         noAbortTx;      /* number of ABORTs sent */   
   StsCntr         noAbortRx;      /* number of ABORTs received */   
#endif
/*lsb_x_003.main_2  Error Statistics added */
#ifdef LSB6
   StsCntr         noErrorTx;      /* number of ERRORs sent */
   StsCntr         noErrorRx;      /* number of ERRORs received */
#endif

/* lsb_x_001.main_6: SATELLITE SCTP feature */
/* ECNE and CWR chunks statistics added */
#ifdef SB_ECN
   StsCntr         noEcneTx;       /* number ECNEs sent */
   StsCntr         noEcneReTx;     /* number ECNEs resent */
   StsCntr         noEcneRx;       /* number ECNEs received */

   StsCntr         noCwrTx;        /* number of CWRs sent */   
   StsCntr         noCwrRx;        /* number of CWRs received */  
#endif /* SB_ECN */
 
} SbChunkSts;

/* Statistics counters for incoming and outgoing bytes */
typedef struct _sbByteSts      /*  Statistics counters for bytes */
{
   StsCntr         bytesTx;        /* bytes sent */
   StsCntr         bytesRx;        /* bytes received */
} SbByteSts;

/* DNS Statistics  */
typedef struct _sbDnsSts 
{
  StsCntr          noQueryTx;     /* Number of DNS Queries Txmitted */
  StsCntr          noQueryReTx;   /* Number of DNS Queries ReTxmitted */
  StsCntr          noQueryRspRx;  /* Number of DNS Query Responses Received  */
} SbDnsSts;


/* SCTP Layer wide statistics */
typedef struct _sbGenSts
{
   DateTime        dt;             /* Date and time when statistics counters
                                    * are initialized to zero */
   SbChunkSts      sbChunkSts;     /* Statistics counters for incoming and
                                    * outgoing chunks */
   SbByteSts       sbByteSts;      /* Statistics counters for total incoming
                                    * and outgoing bytes */
  SbDnsSts         sbDnsSts;       /* Statistics couters for Dns Transations */
} SbGenSts;

/* SCT SAP specific statistics */
typedef struct _sbSctSapSts    /* SCTP Statistics for SCTSAP */
{
   Swtch           swtch;          /* Protocol switch */
   DateTime        dt;             /* date and time when statistics counters
                                    * are initialized to zero */
   SbByteSts       sbByteSts;      /* Statistics counters for total incoming
                                    * and outgoing bytes */
} SbSctSapSts;

/* Transport SAP specific statistics */
typedef struct _sbTSapSts      /* SCTP Statistics for TSAP */
{
   Swtch           swtch;          /* Protocol switch */
   DateTime        dt;             /* date and time when statistics counters
                                    * are initialized to zero */
   SbChunkSts      sbChunkSts;     /* Statistics counters for incoming and
                                    * outgoing chunks */
   SbByteSts       sbByteSts;      /* Statistics counters for total incoming
                                    * and outgoing bytes */
   StsCntr         nmbBndRetry;    /* number of bind retries on the SAP */
} SbTSapSts;

/* SCTP Statistics Structure */
typedef struct _sbSts          /* Statistics */
{
   DateTime        dt;             /* Current date and time */
   Duration        dura;           /* duration as date and time */
   SpId            sapId;          /* SAP Id */
   union
   {
      SbGenSts     genSts;         /* SCTP general statistics */
      SbSctSapSts  sctSts;         /* SCTP SCTSAP Statistics */
      SbTSapSts    tSts;           /* SCTP TSAP Statistics */
   } u;
} SbSts;

/* SCTP Alarm Structure */
typedef struct _sbUsta         /* Unsolicited status */
{
   CmAlarm         alarm;          /* Common Alarm Structure */
   SpId            sapId;          /* SAP Id */
   Swtch           swtch;          /* Protocol Switch */

/* lsb_x_001.main_4: Information feild added */
 #ifdef LSB7
   Txt               info[LSB_MAX_INFO + 1];
 #endif
 
} SbUsta;

/* SCTP Message Trace Structure */
typedef struct _sbTrc          /* Trace */
{
   DateTime        dt;             /* date and time */
   SuId            sapId;          /* TSAP Id */
   U16             evnt;           /* event */
   U16             len;            /* trace length */
   U8              evntParm[LSB_MAX_TRC_LEN];       /* event parameters */
} SbTrc;

typedef struct _sbMgmt        /* Management structure */
{
   Header          hdr;            /* header */
   CmStatus        cfm;            /* Confirm */

   union
   {
      SbCfg        cfg;            /* configuration */
      SbCntrl      cntrl;          /* control */
      SbSsta       ssta;           /* solicited status */
      SbSts        sts;            /* statistics */
      SbUsta       usta;           /* unsolicited status */
      SbTrc        trc;            /* trace */
   }t;
} SbMgmt;

/*
 * Depending on the specific selector in the post structure, a
 * primitive originated from a service provider can be dispatched
 * to any service user. The assumption is that, even if every
 * primitive has a different name depending in which file it
 * resides, every primitive must have the same function prototype,
 * i.e. the same identical set of arguments. These arguments are
 * defined here:
 */

typedef S16 (*LsbCfgReq)   ARGS((Pst *pst, SbMgmt *cfg));
typedef S16 (*LsbCntrlReq) ARGS((Pst *pst, SbMgmt *cntrl));
typedef S16 (*LsbStaReq)   ARGS((Pst *pst, SbMgmt *sta));
typedef S16 (*LsbStsReq)   ARGS((Pst *pst, Action action, SbMgmt *sts));

typedef S16 (*LsbCfgCfm)   ARGS((Pst *pst, SbMgmt *cfm));
typedef S16 (*LsbCntrlCfm) ARGS((Pst *pst, SbMgmt *cfm));
typedef S16 (*LsbStaCfm)   ARGS((Pst *pst, SbMgmt *sta));
typedef S16 (*LsbStsCfm)   ARGS((Pst *pst, SbMgmt *sts));

typedef S16 (*LsbStaInd)   ARGS((Pst *pst, SbMgmt *sta));
typedef S16 (*LsbTrcInd)   ARGS((Pst *pst, SbMgmt *trc));

#ifdef SM
EXTERN  S16 SmMiLsbCfgReq   ARGS((Pst *pst, SbMgmt *cfg));
EXTERN  S16 SmMiLsbCntrlReq ARGS((Pst *pst, SbMgmt *cntrl));
EXTERN  S16 SmMiLsbStaReq   ARGS((Pst *pst, SbMgmt *sta));
EXTERN  S16 SmMiLsbStsReq   ARGS((Pst *pst, Action action, SbMgmt *sts));

EXTERN  S16 SmMiLsbCfgCfm   ARGS((Pst *pst, SbMgmt *cfm));
EXTERN  S16 SmMiLsbCntrlCfm ARGS((Pst *pst, SbMgmt *cfm));
EXTERN  S16 SmMiLsbStaCfm   ARGS((Pst *pst, SbMgmt *sta));
EXTERN  S16 SmMiLsbStsCfm   ARGS((Pst *pst, SbMgmt *sts));

EXTERN  S16 SmMiLsbStaInd   ARGS((Pst *pst, SbMgmt *sta));
EXTERN  S16 SmMiLsbTrcInd   ARGS((Pst *pst, SbMgmt *trc));
#endif /* SM */

#ifdef SB
EXTERN  S16 SbMiLsbCfgReq   ARGS((Pst *pst, SbMgmt *cfg));
EXTERN  S16 SbMiLsbCntrlReq ARGS((Pst *pst, SbMgmt *cntrl));
EXTERN  S16 SbMiLsbStaReq   ARGS((Pst *pst, SbMgmt *sta));
EXTERN  S16 SbMiLsbStsReq   ARGS((Pst *pst, Action action, SbMgmt *sts));

EXTERN  S16 SbMiLsbCfgCfm   ARGS((Pst *pst, SbMgmt *cfm));
EXTERN  S16 SbMiLsbCntrlCfm ARGS((Pst *pst, SbMgmt *cfm));
EXTERN  S16 SbMiLsbStaCfm   ARGS((Pst *pst, SbMgmt *sta));
EXTERN  S16 SbMiLsbStsCfm   ARGS((Pst *pst, SbMgmt *sts));

EXTERN  S16 SbMiLsbStaInd   ARGS((Pst *pst, SbMgmt *sta));
EXTERN  S16 SbMiLsbTrcInd   ARGS((Pst *pst, SbMgmt *trc));
#endif /* SB */

/* PRIMITIVE PACKING/UNPACKING FUNCTIONS */
#ifdef LCLSB
EXTERN S16 cmPkLsbCfgReq    ARGS((Pst *pst, SbMgmt *cfg));
EXTERN S16 cmPkLsbCntrlReq  ARGS((Pst *pst, SbMgmt *cntrl));
EXTERN S16 cmPkLsbStaReq    ARGS((Pst *pst, SbMgmt *sta));
EXTERN S16 cmPkLsbStsReq    ARGS((Pst *pst, Action action, SbMgmt *sts));

EXTERN S16 cmPkLsbCfgCfm    ARGS((Pst *pst, SbMgmt *cfg));
EXTERN S16 cmPkLsbCntrlCfm  ARGS((Pst *pst, SbMgmt *cntrl));
EXTERN S16 cmPkLsbStaCfm    ARGS((Pst *pst, SbMgmt *sta));
EXTERN S16 cmPkLsbStsCfm    ARGS((Pst *pst, SbMgmt *sts));

EXTERN S16 cmPkLsbStaInd    ARGS((Pst *pst, SbMgmt *usta));
EXTERN S16 cmPkLsbTrcInd    ARGS((Pst *pst, SbMgmt *trc));


EXTERN S16 cmUnpkLsbCfgReq   ARGS((LsbCfgReq func, Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLsbCntrlReq ARGS((LsbCntrlReq func, Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLsbStaReq   ARGS((LsbStaReq func,  Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLsbStsReq   ARGS((LsbStsReq func,  Pst *pst, Buffer *mBuf));

EXTERN S16 cmUnpkLsbCfgCfm   ARGS((LsbCfgCfm func, Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLsbCntrlCfm ARGS((LsbCntrlCfm func, Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLsbStaCfm   ARGS((LsbStaCfm func,  Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLsbStsCfm   ARGS((LsbStsCfm func,  Pst *pst, Buffer *mBuf));

EXTERN S16 cmUnpkLsbStaInd   ARGS((LsbStaInd func,  Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkLsbTrcInd   ARGS((LsbTrcInd func,  Pst *pst, Buffer *mBuf));
#endif /* LCLSB */

/* stack manager activation function */
EXTERN S16 smSbActvTsk       ARGS((Pst       *pst,
                                   Buffer    *mBuf));

EXTERN S16 smSbActvInit      ARGS((Ent        ent,
                                   Inst       inst,
                                   Region     region,
                                   Reason     reason));

/* lsb_x_001.main_3 : MOVED from sb.x ,external functions */
EXTERN S16 sbActvTsk ARGS((Pst *pst, Buffer *mBuf));


/* lsb_x_001.main_3 : MOVED from sb.x ,external functions */
#ifdef SS_MULTIPLE_PROCS

EXTERN S16  sbActvInit      ARGS((ProcId proc,
                                  Ent entity,
                                  Inst inst,
                                  Region region,
                                  Reason reason,
                                  Void   **xxCb));

#else /* SS_MULTIPLE_PROCS */

EXTERN S16  sbActvInit      ARGS((Ent entity,
                                  Inst inst,
                                  Region region,
                                  Reason reason));

#endif /* SS_MULTIPLE_PROCS */


#ifdef __cplusplus
}
#endif

#endif /* __LSBX__ */


/********************************************************************30**

         End of file:     lsb.x@@/main/11 - Thu Jul 31 10:16:46 2008

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
1.1          ---      nj     1. initial release.

/main/2      ---      wvdl   1. updated the structures to conform with
                                version sent for first review.
 /main/2     ---      sb     1. Modified for SCTP release based on 
                                RFC-2960 'Oct 2000.
            sb018.102 ab     1. Heartbeat statistics added.
            sb031.102 hm     1. IPV6 Support Added 
            sb052.102 ag     1. Abort statistics added.
     lsb_x_001.main_2 rk     1. Bundling feature added.
     lsb_x_002.main_2 kp     1. Modified for making UDP port as 
                                configurable parameter.
     lsb_x_003.main_2 kp     1. Error Statistics added. 
     lsb_x_001.main_3 kp     1. Moved sbActvTsk and sbAtcvInit from sb.x.
     lsb_x_001.main_4 kp     1. Information feild added in sbMgmt.usta structure
     lsb_x_001.main_5 rsr/ag 1. RFC 4460 related members have been 
                                added in SbSctSapReCfg structure
/main/6      ---      rsr/ag 1. Updated for Release of 1.3
     lsb_x_001.main_6 ag     1. Satellite SCTP feature (under compile-
                                time flag SB_SATELLITE & SB_ECN):
                                - Defined path profile and destination
                                  address configuartion
                                - Added new parameters in GenCfg, Cntrl, Status,
                                  and Statistics.
                             2. Moved the smPst structure from genCfg to 
                                reConfig structure of general configuration.
     lsb_x_001.main_7 ag     1. Protected the changes for making smPst structure
                                reconfigurable under a new compile time flag LSB9.
     lsb_x_001.main_8 ag     1. Added new members in AssocSta and DtaSta under
                                a new compile time flag LSB11.
     lsb_x_001.main_9 nuX    1. Added new member in structure SbAssocSta to get the 
                                timer status with the Assoc Status, under the compilation
				LSB11.	
     lsb_x_001.main_10 pkaX  1. Replaced SB_ACC flag with LSB12
                      
*********************************************************************91*/
