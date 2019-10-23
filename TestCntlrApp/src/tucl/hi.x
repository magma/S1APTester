

/********************************************************************20**

     Name:     TCP/UDP Convergence Layer

     Type:     C include file

     Desc:     Structures, variables, types and prototypes.

     File:     hi.x
  
     Sid:      hi.x@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:38:58 2015

     Prg:      kp

*********************************************************************21*/



#ifndef __HIX__
#define __HIX__


#ifdef __cplusplus
extern "C" {
#endif


/* Reception statistics.
 */
typedef struct hiRxSts
{
   StsCntr      numCons;
   StsCntr      numRxBytes;
   StsCntr      numRxTcpMsg;
   StsCntr      numRxUdpMsg;
   StsCntr      numRxRawMsg;
   StsCntr      numRxTlsMsg;
#ifdef HI_LKSCTP
   StsCntr      numRxSctpMsg;
#endif

} HiRxSts;


/* Transmission statistics.
 */
typedef struct hiTxSts
{
   StsCntr      numCons;
   StsCntr      numTxBytes;
   StsCntr      numTxTcpMsg;
   StsCntr      numTxUdpMsg;
   StsCntr      numTxRawMsg;
   StsCntr      numTxTlsMsg;
#ifdef HI_LKSCTP
   StsCntr      numTxSctpMsg;
#endif

} HiTxSts;


/* Error statistics.
 */
typedef struct hiErrSts
{
   StsCntr      sockTxErr;
   StsCntr      sockRxErr;
   StsCntr      sockOpenErr;
   StsCntr      sockBindErr;
   StsCntr      sockCnctErr;
   StsCntr      sockLstnErr;
   StsCntr      sockSOptErr;
   StsCntr      sockClosErr;
   StsCntr      sockShutErr;
   StsCntr      rxMsgVerErr;
   StsCntr      numFlcInd;

} HiErrSts;


#ifdef HI_TLS

/* TLS connection parameters */
typedef struct hiTlsConCb
{
   S16          ctxId;                  /* OpenSSL context Id */
   BIO          *bio;                   /* BIO for this connection */
   SSL          *ssl;                   /* the connection */
   Bool         recving, sending;       /* for retry logic */
   Data         *rBuf;                  /* message being received */
   MsgLen       rBufLen;                /*  "  "   length */

} HiTlsConCb;


/* Context information */
typedef struct hiCtx
{
    HiCtxCfg    cfg;                    /* context configuration */
    SSL_CTX     *ctx;                   /* OpenSSL context */

} HiCtx;

#endif /* HI_TLS */


/* Layer manager control requests can be pending on a SAP when
 * communication with the HI threads are required before a confirm
 * can be sent.
 */
typedef struct hiPendOp
{
   Bool         flag;           /* operation pending? */
   Header       hdr;            /* control request header */
   U8           action;         /*    "       "    action */
   Elmnt        elmnt;          /* STTSAP or STGRTSAP */
   U16          numRem;         /* for ASHUTDOWN/STGRTSAP requests */
   Pst          lmPst;          /* for response */

} HiPendOp;


#ifdef HI_MULTI_THREADED

/* Upper interface primitives can be invoked by multiple threads.
 * Each primitive must therefore have its own Pst.
 */
typedef struct hiUiPsts
{
   Pst          uiConCfmPst;
   Pst          uiConIndPst;
   Pst          uiFlcIndPst;
   Pst          uiDatIndPst;
   Pst          uiUDatIndPst;
   Pst          uiDiscIndPst;
   Pst          uiDiscCfmPst;

} HiUiPsts;

#endif /* HI_MULTI_THREADED */


/* Transport SAP.
 */
typedef struct hiSap
{
   SpId         spId;           /* service provider Id */
   SuId         suId;           /* service user Id */
   State        state;          /* SAP state */
#ifdef HI_LKSCTP
   U8           type;           /* SAP type */
#endif

   Bool         resCongStrt;    /* resource congestion */
   Bool         resCongDrop;    /* sever resource congestion */

   UConnId      lstSpConId;     /* used to generate the next spConnId */

   HiSapCfg     cfg;            /* configuration for this SAP */
   HiTxSts      txSts;          /* SAP transmit statistics */
   Bool         trc;            /* trace enabled flag */
   S16          trcLen;         /* trace length */

   Pst          uiPst;          /* upper interface (HI user) post structure */
   CmHashListCp conCbHlCp;      /* connection block hash list */

   HiPendOp     pendOp;         /* control request pending */

#ifdef HI_MULTI_THREADED
   HiUiPsts     uiPsts;         /* post structures for primitives */
   SLockId      conCbHlLock;    /* for MT access to sapHlCp */
   SLockId      resCongLock;    /* for MT access to congestion flags */
#ifdef HI_STS_LOCKS
   SLockId      txStsLock;      /* for MT access to txSts */
#endif
#endif

   Ent          contEnt;        /* controlling entity */

#ifdef HI_RUG
   Bool         remIntfValid;   /* version number valid? */ 
   Ent          verContEnt;     /* version controller */
#endif
   /*hi005.201 rss  1. Added timer based resource checking in the case of congestion*/ 
   CmTimer       congTimers[HICONGTMRS]; /* Congestion timers for sap*/
} HiSap;

/* Connection control block.
 */
typedef struct hiConCb
{
   CmHashListEnt        conCbHlEnt;         /* conCbHlCp in SAP */
/* hi032.201: Added new variables to support filteration of ICMP messages 
 * as per user request and protected this changes under CM_ICMP_FILTER_SUPPORT flag */
#ifdef CM_ICMP_FILTER_SUPPORT
   CmHashListEnt        icmpConCbHlEnt;         /* conCbHlCp in SAP */
#endif
   CmHashListEnt        rdFdHlEnt;         /* rdFdHlCp in fd group */
   CmHashListEnt        wrFdHlEnt;        /* wrFdHlCp in fd group */
   CmLList              icmpLstEnt;    /* for ICMP linked list in hiCb */

   HiSap        *sap;           /* SAP pointer */
   UConnId      suConId;        /* service user connection Id */
   UConnId      spConId;        /* HI connection Id */

   State        state;          /* connection state */
   U8           srvcType;       /* connection service type */
   U32          flag;           /* for service type */
   U8           protocol;       /* protocol value */
   Bool         priority;       /* priority profile? */
   U8           flc;            /* flow control status */
   U16          fdGrpNum;       /* group this conn belongs to */

   CmInetFd     conFd;          /* socket descriptor */
   CmTptAddr    peerAddr;       /* address of the peer entity */
   CmTptAddr    locTptAddr;     /* local transport address */

   Queue        txQ;            /* pending transmit buffers */
   U32          txQSize;        /* size (in bytes) of txQ */

   Bool         awaitHdr;       /* indicates header arrival */
   U32          rxLen;          /* length of received TCP data */
   U32          pendLen;        /* length of pending TCP data */
   Buffer       *rxBuf;         /* receive buffer */
   Bool         hdrIncldFlag;   /* IP header include option */

   U8           ipParamMask;    /* mask of DF & TOS bits */
   U8           ipTos;          /* IP TOS value */
   U8           ipTtl;          /* IP time to live value */
   U8           mCastTtl;       /* multicast TTL */

   U8           icmpType;       /* ICMP filter version (v4/v6) */
   U16          icmpMask;       /* mask for distribution of ICMP msgs */
   U8           filterProtocol; /* filtering on protocol */
   U8           numFilters;     /* number of filters */
   CmIcmpError  *icmpError;     /* ICMP filter errors */

#ifdef IPV4_OPTS_SUPPORTED 
   Bool         ipv4OptionSet;  /* IP options is set on the socket */
#endif

#ifdef IPV6_SUPPORTED
   U16           icmp6Mask;     /* for distribution of ICMPv6 msgs */
#ifdef IPV6_OPTS_SUPPORTED
   Bool          ipv6OptsReq;   /* user wants to receive IPv6 opts */
#endif
#endif

#ifdef HI_MULTI_THREADED     
   SLockId      lock;           /* access lock */
   SLockId      txQLock;        /* transmit queue lock */

#ifdef HI_TLS
   HiTlsConCb   tlsConCb;       /* TLS connection information */

/* hi013.105 :  Added two new HIT primitives. HiUiHitTlsEstReq(), HiUiHitTlsEstCfm().*/
#ifdef HITV2
#ifdef HI_TCP_TLS
   U8           mode;           /* mode of operation of TUCL */
#endif /*HI_TCP_TLS*/
#endif /*HITV2*/

#endif /*HI_TLS*/
#endif

/*hi014.105 1. modified statistics req to include messages
                              Tx/Rx in bytes per con per thread*/
#ifdef LHI_THR_STS 
   StsCntr   numTxBytes;   
   StsCntr   numRxBytes;   
#endif /*LHI_THR_STS */

#ifdef HI_LKSCTP
   U8            type;             /* mode of operation of TUCL */
   UConnId       assocSpEndpId;    /* HI connection Id */
   UConnId       sysAssocId;       /* HI connection Id */
   UConnId       suEndpId;         /* HI connection Id */
   UConnId       suAssocId;        /* HI connection Id */
   CmHashListCp  assocMapHlCp;     /* assoc map hash list */
   SctPort       dstPort;          /* destination port no. */
   SctNetAddrLst dstNAddrLst;      /* destination network address list */
   /* hi024.201 : ntfyCnt added. This is 1 for LINUX and is equal to no. of 
                  addresses in the dstAddrLst for SOLARIS */
   U8            ntfyCnt;          /* no. of notifications to be received 
                                      for connect */
#endif

/* hi032.201: Added new variables to support filteration of ICMP messages 
 * as per user request and protected this changes under CM_ICMP_FILTER_SUPPORT flag */

#ifdef CM_ICMP_FILTER_SUPPORT
   U16                  idx;
   U32                  filterData;
#ifdef IPV6_SUPPORTED
   CmInetIcmp6Filter    ipv6FilterData;
#endif
#endif /* CM_ICMP_FILTER_SUPPORT */
} HiConCb;

#ifdef HI_LKSCTP
typedef struct _HiAssocMapEntry
{
   SctPort     port;                    /* SCTP port of peer endpoint */
   CmNetAddr   peerAddr;                /* Net address of peer endpoint */
} HiAssocMapEntry;

typedef struct _HiAssocMapCb
{
   CmHashListEnt      assocMapHlEnt;   
   HiAssocMapEntry    assocMapEntry;
   HiConCb           *assocConCbPtr;
} HiAssocMapCb;
#endif

/* Message to a group thread.
 */
typedef struct hiThrMsg
{
/* hi032.201: Added new variables to support filteration of ICMP messages 
 * as per user request and protected this changes under CM_ICMP_FILTER_SUPPORT flag */
#ifdef CM_ICMP_FILTER_SUPPORT
   U16          idx;
#endif
   S16          type;           /* message type */
   SpId         spId;           /* for the relevant SAP */
   UConnId      spConId;        /* for the relevant connection */
   union
   {
      Reason    reason;         /* for indications */
      Action    action;         /* for confirms */

   } disc;
#ifdef HI_LKSCTP
   struct 
   {
      SctStatus     status;
      SctCause      cause;
      SctRtrvInfo   rtrvInfo;
   }sctDiscInd;
#endif
} HiThrMsg;


/* fd group (per thread).
 */
typedef struct hiFdGrp
{
   U16                  fdGrpNum;       /* group number */
   Bool                 procIcmp;       /* process ICMP? */
#ifdef IPV6_SUPPORTED 
   Bool                 procIcmp6;      /* process ICMPv6? */
#endif

   U32                  numFds;         /* number of fds in group */
   U16                  numWrFds;       /* number of write fds set */
   CmHashListCp         rdFdHlCp;       /* read hash list */
   CmHashListCp         wrFdHlCp;       /* write hash list */
   CmInetFdSet          readFdSet;      /* read fd set */
   CmInetFdSet          writeFdSet;     /* write fd set */
   CmInetFdSetInfo      fdSetInfo;      /* fd set information */

   HiRxSts              genRxSts;       /* general reception stats */
   HiRxSts              *rxSts;         /* SAP reception stats */

   CmInetFd             servFd;         /* reserved UDP server */
   CmInetAddr           servAddr;       /* address of the UDP server */

#ifdef HI_MULTI_THREADED
   SLockId              lock;           /* to protect numFds */
#endif

/*hi014.105  1. modified statistics req to include messages
                              Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS 
   Cntr                 numCons;        /* To store the number of connections
                                           handled by this group */ 
#endif /*LHI_THR_STS */

} HiFdGrp;



/* hi032.201: Added new structure to support filteration of ICMP messages 
 * as per user request and protected this changes under CM_ICMP_FILTER_SUPPORT flag */
#ifdef CM_ICMP_FILTER_SUPPORT 
typedef struct hiIcmpSockInfo
{
   CmInetFd     icmpConFd;      /* ICMP socket */
   U8           icmpUsers;      /* num of users listening to ICMP */
   CmLListCp    icmpLstCp;      /* ICMP users linked list */
   Bool          usedFlag;
   CmHashListCp  conCbHlCp;      /* connection block hash list */
   CmInetIpAddr  ipv4Addr;
   U16           icmpFdGrpNum;       /* group number */
    Bool          procIcmp;
#ifdef IPV6_SUPPORTED
   CmInetFd     icmp6ConFd;     /* ICMPv6 socket */
   U8           icmp6Users;     /* num of users listening to ICMPv6 */
   CmLListCp    icmp6LstCp;     /* ICMPv6 users linked list */
   CmInetIpAddr6 ipv6Addr;
   Bool                 procIcmp6;
   CmInetIcmp6Filter    icmp6Filter;
#endif /* IPV6_SUPPORTED*/
} HiIcmpSockInfo;
#endif /* CM_ICMP_FILTER_SUPPORT */

/* HI layer control block.
 */
typedef struct _hiCb
{
   /* hi002.105(hi025.104) :Addition - Support for multiple Instances  */
#ifdef SS_MULTIPLE_PROCS /* SS_MULTIPLE_PROCS */
   U8            used;              /* flag to indicate if the instance is in use */
#endif /* SS_MULTIPLE_PROCS */

   TskInit      init;           /* task initialization structure */
   HiSap        **saps;         /* HI layer transport SAPs */

   HiGenCfg     cfg;            /* general configuration */
   HiErrSts     errSts;         /* general error statistics */

   U16          numFdGrps;      /* num of fd groups */
   HiFdGrp      **fdGrps;       /* fd groups */

   CmInetFd     resvConFd;      /* generic UDP socket */


/* hi032.201: Added new variables to support filteration of ICMP messages 
 * as per user request and protected this changes under CM_ICMP_FILTER_SUPPORT flag */
#ifndef CM_ICMP_FILTER_SUPPORT
   CmInetFd     icmpConFd;      /* ICMP socket */
   U8           icmpUsers;      /* num of users listening to ICMP */
   CmLListCp    icmpLstCp;      /* ICMP users linked list */

#ifdef IPV6_SUPPORTED
   CmInetFd     icmp6ConFd;     /* ICMPv6 socket */
   U8           icmp6Users;     /* num of users listening to ICMPv6 */
   CmLListCp    icmp6LstCp;     /* ICMPv6 users linked list */
#endif

#else
   HiIcmpSockInfo icmpInfo[CM_MAX_ICMP_SOCKET];
#endif /* CM_ICMP_FILTER_SUPPORT */
   /* ICMPv6 filters and filter errors */

/* hi010.201  1. since windows doesn't has icmpv6 filter so the icmpv6 filter 
					  feature is supported under the flag ICMPV6_FILTER_SUPPORTED.
					  User has to enable the above flag to get the feature */
#ifdef IPV6_SUPPORTED
   CmInetFd     resv6ConFd;     /* IPv6 generic UDP socket */
#ifdef ICMPV6_FILTER_SUPPORTED
   CmInetIcmp6Filter    icmp6Filter;
   U8                   icmp6FiltArr[CM_MAX_ICMP_ERROR];
#endif /* ICMPV6_FILTER_SUPPORTED */
#endif

   HiPendOp     pendOp;         /* control request pending */
   U16          lastGrp;        /* last group used */

#ifdef HI_MULTI_THREADED

   SLockId      pendLock;       /* for pendOp */

  /* hi028.201: Added new element lmPstLock to support locking
     mechanism fot lmPst*/
   SLockId      lmPstLock;       /* for lmPst */
   SSTskId      *tskIds;        /* of system task Ids */
   SLockId      icmpLstLock;    /* for ICMP linked list */

#ifdef IPV6_SUPPORTED
   SLockId      icmp6LstLock;   /* for ICMPv6 linked list */
#endif

#ifdef HI_STS_LOCKS
   SLockId      errStsLock;     /* for error stats */
#endif

#ifdef HI_TLS
   HiCtx        *tlsContexts;           /* TLS/OpenSSL contexts */
   SLockId      *tlsMutexes;            /* for multi-threading */
#endif

#else /* HI_MULTI_THREADED */

   CmTimer      timers[HIGENTMRS];      /* timers */

#endif /* HI_MULTI_THREADED */

/*hi005.201 Added timer based resource checking in case of conjestion*/
/*pervious to this patch these were used only in single thread.
 *now this is used for both single and multi threaded */
   CmTqCp       tqCp;                   /* timer queue control point */
   CmTqType     tq[HIQNUMENT];          /* timer queue */


#ifdef HI_RUG
   U16          numIntfInfo;    /* number of i/f versions */
   ShtVerInfo   *intfInfo;      /* i/f versions info */
#endif

} HiCb;

/* hi002.105 (hi025.104) : Addition - Support for multiple instances */
#ifdef SS_MULTIPLE_PROCS 
/* Define an array of Control Block */
EXTERN HiCb hiCbLst[HI_MAX_INSTANCES];
EXTERN HiCb *hiCbPtr;
#else /* SS_MULTIPLE_PROCS */
/* global TUCL control block */
EXTERN HiCb hiCb;
#endif /* SS_MULTIPLE_PROCS */


/* hack for LOCAL_INTF strangeness */
#ifdef LOCAL_INTF
typedef CmTptLocalInf   HiLocalInf;
#else
typedef S8              HiLocalInf;
#endif



/* Prototypes.
 */


#ifdef HI_TLS
/* customer provided functions */
EXTERN long hiOSSLPostConCheck  ARGS((SSL *ssl, CmTptAddr *peerAddr));
EXTERN int  hiOSSLPasswdCb      ARGS((char *, int, int, void *));
#ifdef HI_TLS_EXT_SESS_CACHE
EXTERN int  hiOSSLNewSessCb     ARGS((SSL_CTX *ctx,
                                      SSL_SESSION *session));
EXTERN void hiOSSLDelSessCb     ARGS((SSL_CTX *ctx,
                                      SSL_SESSION *session));
EXTERN SSL_SESSION *
            hiOSSLGetSessCb     ARGS((SSL_CTX *ctx, unsigned char *id,
                                      int len, int *ref));
#endif
/* hi008.105 : added extra ssl callback function */
#ifdef HI_TLS_EXT_CALLBACK
EXTERN void hiOSSLGetMsg        ARGS((int write_p,int vers, int  content_type,
                                       CONSTANT void  *buf,size_t len,SSL *ssl, 
                                       void *arg));
EXTERN void hiOSSLGetInfo       ARGS((CONSTANT SSL *ssl,int where, int ret));
EXTERN int  hiOSSLVerifyCb      ARGS((int ok, X509_STORE_CTX  *store));
#endif /* HI_TLS_EXT_CALLBACK */
#endif

/* TAPA related */
/* hi002.105 (hi025.104) */
/* hi007.105 : Decleration of hiActvInit and hiActvTsk is moved from
                      hi.x to lhi.x */

EXTERN S16  hiRecvTsk           ARGS((Pst *pst, Buffer *mBuf));
EXTERN S16  hiGetSid            ARGS((SystemId *sid));


/* timer/permanent task related */
/* hi002.105 (hi025.104) */
#ifdef SS_MULTIPLE_PROCS
EXTERN S16  hiActvTmr       ARGS((ProcId procId, Ent ent, Inst inst));
#else /* SS_MULTIPLE_PROCS */
EXTERN S16  hiActvTmr           ARGS((Void));
#endif /* SS_MULTIPLE_PROCS */

EXTERN S16  hiTmrEvnt           ARGS((PTR cb, S16 evnt));
EXTERN S16  hiScanPermTsk       ARGS((Pst *tPst, Buffer *mBuf));


/* management related */
EXTERN Void hiSendLmCfm         ARGS((Pst *pst, U8 cfmType,
                                      Header *hdr, U16 status,
                                      U16 reason, HiMngmt *cfm));
EXTERN Void hiSendAlarm         ARGS((U16 cgy, U16 evnt, U16 cause,
                                      HiAlarmInfo *info));
EXTERN S16  hiCfgGen            ARGS((HiGenCfg *hiGen));
EXTERN S16  hiCfgSap            ARGS((HiSapCfg *cfg));
#ifdef HI_TLS
EXTERN S16  hiCfgCtx            ARGS((HiCtxCfg *cfg));
#endif
EXTERN S16  hiShutdown          ARGS((Void));
EXTERN S16  hiCntrlGen          ARGS((Pst *pst, HiMngmt *cntrl, Header *hdr));
EXTERN S16  hiCntrlSap          ARGS((Pst *pst, HiMngmt *cntrl, Header *hdr));
EXTERN S16  hiCntrlSapGrp       ARGS((Pst *pst, HiMngmt *cntrl, Header *hdr));
EXTERN S16  hiGetGenSts         ARGS((HiGenSts *genSts));
EXTERN S16  hiZeroGenSts        ARGS((Void));
EXTERN S16  hiGetSapSts         ARGS((HiSapSts *sapSts, HiSap *sap));
EXTERN S16  hiZeroSapSts        ARGS((HiSap *sap));
EXTERN Void hiTrcBuf            ARGS((HiSap *sap, U16 evnt, Buffer *mBuf));


/*hi014.105  1. modified statistics req to include messages
                              Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS
EXTERN S16  hiGetThrSts         ARGS((Pst *pst, HiThrSts *thrSts));
EXTERN S16  hiZeroThrSts        ARGS((Void));
#endif /*LHI_THR_STS*/

/* connection control block related */
EXTERN S16  hiAllocConCb        ARGS((HiSap *sap, UConnId suConId,
                                      U8 srvcType, U8 *type,
                                      HiConCb **conCb));
EXTERN S16  hiCompleteConCb     ARGS((HiConCb *conCb));
EXTERN S16  hiAssignConCb       ARGS((HiConCb *conCb, U8 type));
EXTERN S16  hiFindConCb         ARGS((HiSap *sap, UConnId spConId,
                                      HiConCb **conCb));
EXTERN S16  hiFindConCbSuConId  ARGS((HiSap *sap, UConnId suConId,
                                      HiConCb **conCb));
EXTERN Void hiDoneWithConCb     ARGS((HiConCb *conCb));
EXTERN S16  hiEnqueueForTx      ARGS((HiConCb *conCb, Buffer *mBuf));


/* thread related */
EXTERN Void hiProcThrDelCon     ARGS((HiFdGrp *fdGrp, HiThrMsg *tMsg,
                                      CmInetFdSet *selRdFdSet,
                                      CmInetFdSet *selWrFdSet, S16 *setFds));
EXTERN S16  hiSendThrMsg        ARGS((U16 fdGrpNum, HiThrMsg *tMsg));
EXTERN S16  hiProcThrMsg        ARGS((HiFdGrp *fdGrp, CmInetFdSet *selRdFdSet,
                                      CmInetFdSet *selWrFdSet, S16 *setFds));


/* miscellaneous */
EXTERN S16  hiChkRes            ARGS((HiSap *sap));
EXTERN Void hiChkFlc            ARGS((HiConCb *conCb, U32 posLen, U32 negLen));


/* socket related */
EXTERN S16  hiCreateSock        ARGS((Bool server, U8 type,
                                      CmTptAddr *tptAddr, CmTptParam *tPar,
                                      HiConCb *conCb));


/* hi032.201: Added new function to support filteration of ICMP messages 
 * as per user request and protected this changes under CM_ICMP_FILTER_SUPPORT flag */
#ifdef CM_ICMP_FILTER_SUPPORT
EXTERN S16  hiCreateIcmpSock        ARGS((Bool server, U8 type,
                                      CmTptAddr *tptAddr,
                                      HiConCb *conCb));
EXTERN S16 hiSetIcmpSockOpt      ARGS((HiConCb *conCb));
#endif /* CM_ICMP_FILTER_SUPPORT */
EXTERN S16  hiSetSockOpt        ARGS((HiConCb *conCb, CmTptParam *tPar));
EXTERN S16  hiTxMsg             ARGS((HiConCb *conCb, Buffer *mBuf,
                                      MsgLen *txLen, Buffer **qBuf,
                                      HiThrMsg *tMsg));


/* protocol related */
EXTERN S16  hiProcessIcmpReq    ARGS((HiConCb *conCb, 
                                      CmIcmpFilter *icmpFilter));
EXTERN S16  hiAddTPKTHdr        ARGS((Buffer *mBuf, MsgLen *newLen));
EXTERN S16  hiProcHdrParm       ARGS((HiConCb *conCb, CmTptAddr *srcAddr,
                                      CmTptAddr *remAddr,
                                      CmIpHdrParm *hdrParm,
                                      Buffer *mBuf, MsgLen mLen));


#ifdef HI_TLS
/* TLS related */
EXTERN S16  hiInitOpenSSL       ARGS((Void));
EXTERN Void hiTLSAddMem         ARGS((Size *size));
EXTERN S16  hiSetupTLSThreads   ARGS((Void));
EXTERN Void hiCloseTLSThreads   ARGS((Void));
EXTERN S16  hiCreateTLSCtx      ARGS((HiCtx *ctx));
EXTERN Void hiDestroyTLSCtx     ARGS((HiCtx *ctx));
EXTERN S16  hiPrepareTLSCon     ARGS((struct hiConCb *conCb, Bool server));
EXTERN S16  hiAcceptTLSCon      ARGS((struct hiConCb *conCb));
EXTERN S16  hiConnectTLS        ARGS((struct hiConCb *conCb));
EXTERN S16  hiDisconnectTLS     ARGS((struct hiConCb *conCb));
EXTERN S16  hiSendTLS           ARGS((struct hiConCb *conCb, Buffer *mBuf,
                                      MsgLen *txLen));
EXTERN S16  hiRecvTLS           ARGS((struct hiConCb *conCb, Buffer **recvBuf,
                                      MsgLen *rxLen));
#endif


#ifdef FTHA
EXTERN S16  HiMiShtCntrlReq     ARGS((Pst *pst, ShtCntrlReqEvnt *reqInfo));
EXTERN S16  HiMiShtCntrlCfm     ARGS((Pst *pst, ShtCntrlCfmEvnt *cfmInfo));
#endif


#ifdef HI_RUG
EXTERN S16  hiGetVer            ARGS((ShtGetVerCfm *getVerCfmInfo));
EXTERN Void hiSetVer            ARGS((ShtVerInfo *setVerInfo,
                                      CmStatus *status));
#endif

#ifdef HI_LKSCTP
EXTERN S16 hiSctpCmpCmNetAddr  ARGS((CmNetAddr *addr1, CmNetAddr *addr2));
EXTERN S16 hiSctpRemAssocMap   ARGS((HiConCb *endpConCb, HiConCb *assocConCb));
EXTERN S16 hiGetSockOpt        ARGS((HiConCb *conCb, CmTptParam *tPar));
EXTERN S16 hiCreateSctpSock    ARGS((HiConCb* conCb, SctNetAddrLst *intfNAddrLst, 
                                    SctPort port));
EXTERN S16 hiSctpConnect       ARGS((HiConCb *conCb, CmNetAddr *priDstNAddr, 
                                     SctPort dstPort, 
                                     SctNetAddrLst *dstNAddrLst));
EXTERN Void hiSctpTermAssoc    ARGS((HiConCb *assocConCb, SctStatus status));
EXTERN S16 hiSctpSetPriReq     ARGS((HiConCb *conCb, CmNetAddr *dstNAddr));
EXTERN S16 hiSctpHbeatReq      ARGS((HiConCb *conCb, CmNetAddr *dstNAddr,
                                     U16 intervalTime, SctStatus status));
EXTERN S16 hiSctpSndMsg        ARGS((HiConCb *conCb, CmNetAddr *dstNAddr,
                                     SctStrmId strmId, Bool unorderFlg,
                                     Bool nobundleFlg, U16 lifeTime, 
                                     U32 protId, Buffer *mBuf));
EXTERN S16 hiSctpGetAssocInfo  ARGS((HiConCb *conCb, SctStaInfo *pStaInfo));
EXTERN S16 hiSctpGetAddrInfo   ARGS((HiConCb *conCb, CmNetAddr *dstNAddr, 
                                     SctStaInfo *pStaInfo));
#endif


#ifdef __cplusplus
}
#endif

#endif /* __HIX__ */

/********************************************************************30**

         End of file:     hi.x@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:38:58 2015

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
----------- -------- ---- -----------------------------------------------
1.1         ---      asa  1. initial release.
1.1+        hi002.11 asa  1. Changes for the loopback mode.
                          2. Added a srvcType to HiConCb.
/main/2     ---      cvp  1. Added support for multiple file 
                             descriptor sets.
                          2. Added prototypes for hiFdSet and 
                             hiFdClr functions.
                          3. Changed the copyright header.
/main/4     ---      sb   1. Changes to support Raw socket.
                          2. added hashlist entry of conCb for ICMP 
                             users.
                          3. fields added in conCb for Raw socket 
                             support & icmp message filtering.
                     cvp  4. Added sht interface functions prototypes.
/main/4     hi003.13 cvp  1. Added a flag to indicate transmit queue
                             congestion has started.
/main/4+    hi005.13 cvp  1. Added fd_set information in hiFdInfo.
/main/4     ---      cvp  1. Multi-threaded TUCL related changes.
                          2. IPv6/ICMPv6 support related changes.
                          3. Changed the copyright header.
            hi004.104 mmh 1. TOS parameter added to the structure.
/main/4+    hi007.104 mmh 1. Change the name of third argument of
                             hiDelFrmFdGrp to conList.
/main/4+    hi009.104 mmh 1. Rolling upgrade changes, under compile flag
                             HI_RUG as per tcr0020.txt:                         
                           - Field numIntfInfo is added in spCb to indicate
                             number of interface ver info stored in spCb.
                           - Boolean to indicate validity of remote interface 
                             version number (within pst) is added in hiSap and
                             hiCb structures
                           - Function prototypes for new defined functions
                             hiGetVer and hiSetVer added.
                          2. added fields ipv6OptsReq and ipv4OptionSet in
                             the structure HiConCb
                          3. changed prototypes of hiHndlUdpData(),
                             hiHndlRawMsg(), hiHndlIpv6RawMsg() for
                             LOCAL_INTF flag
                          4. added hdrParm param in hiUnpkIpv4Hdr()
/main/4+    hi018.104 zmc 1. Add a new parameter for sock failure handling
                          2. Add utility to process sock faliure
/main/5      ---       kp  1. Updated for release 1.5.
/main/5     hi002.105 ss  1. SS_MULTIPLE_PROCS flag added.
/main/5     hi007.105 ss  1.  Decleration of hiActvInit and hiActvTsk 
                              is moved from hi.x to lhi.x.
/main/5+    hi008.105 ss  1. Added extra ssl callback function decleration. 
/main/5+    hi013.105 svp  1. Added two new HIT primitives.
                              HiUiHitTlsEstReq(), HiUiHitTlsEstCfm().
/main/5+    hi014.105 svp  1. modified statistics req to include messages
                              Tx/Rx in bytes per con per thread 
                           2. done perfomance optimization
/main/6+      ---       hs   1. Updated for release of 2.1
/main/6+    hi005.201  rss 1.Added Conjestion timer for sap in HiSap Structure 
/main/6+    hi010.201  rss 1. since windows doesn't has icmpv6 filter so the icmpv6 filter 
					               feature is supported under the flag ICMPV6_FILTER_SUPPORTED.
					               User has to enable the above flag to get the feature
/main/6+    hi024.201  rshekar 1. ntfyCnt added in HiConCb.
/main/6+    hi028.201 ragrawal 1. Added new element lmPstLock to support locking
                                  mechanism for lmPst.
/main/6+    hi032.201 ragrawal 1. Added new function and new variables to support 
                                  filteration of ICMP messageas per user request 
                                  and protected this changes under CM_ICMP_FILTER_SUPPORT 
                                  compile time flag.
*********************************************************************91*/

