
/********************************************************************20**

     Name:     TCP/UDP Convergence Layer 

     Type:     C header file

     Desc:     Structures, variables, typedefs and prototypes
               required at the management interface.

     File:     lhi.x

     Sid:      lhi.x@@/main/10 - Tue Feb  1 16:04:21 2011

     Prg:      asa

*********************************************************************21*/



#ifndef __LHIX__
#define __LHIX__

#ifdef __cplusplus
extern "C" {
#endif


/* TCP application header specification.
 */
typedef struct hiHdrInfo
{
   U32          hdrLen;         /* header length */
   U32          offLen;         /* offset of packet length  */
   U32          lenLen;         /* num of bytes for length field */
   U32          flag;           /* additonal information */

} HiHdrInfo;


#ifdef HI_TLS

/* TLS/OpenSSL pseudo-random number generator configuration.
 */
typedef struct hiPRNG
{
   U8           option;         /* which choice? */
   union
   {
      S8        file[LHI_OSSL_PATHLEN];
      U8        seed[LHI_OSSL_PRNG_SEED_LEN];
   } u;

} HiPRNG;

#endif /* HI_TLS */


/* General configuration.
 */
typedef struct hiGenCfg
{
   U16          numSaps;        /* number of SAPs */
   U32          numCons;        /* maximum num of connections */
   U16          numFdsPerSet;   /* maximum num of fds to use per set */
   U16          numFdBins;      /* for fd hash lists */
   U8           numClToAccept;  /* clients to accept simultaneously */
   Bool         permTsk;        /* schedule as perm task or timer */
   U16          schdTmrVal;     /* if !permTsk */
   U32          selTimeout;     /* select() timeout */

#ifdef HI_LKSCTP
   U16          numAssocBins;   /* for fd hash lists */
   U8           maxInitReTx;    /* Reconfigurable */ /* Maximum Association Init Retransmits */
   U8           maxAssocReTx;   /* Reconfigurable */ /* Maximum Retransmissions for an association */
   U8           maxPathReTx;    /* Reconfigurable */ /* Maximum Retransmission for a destination Address */
#endif
   /* number of raw/UDP messages to read in one iteration */
   U8           numRawMsgsToRead;
   U8           numUdpMsgsToRead;

   /* thresholds for congestion on the memory pool */
   Status       poolStrtThr;
   Status       poolDropThr;
   Status       poolStopThr;

   Ticks        timeRes;        /* time resolution */ 
   Pst          lmPst;          /* for layer manager */ 

#ifdef HI_SPECIFY_GENSOCK_ADDR 
   CmIpv4TptAddr ipv4GenSockAddr;
#ifdef IPV6_SUPPORTED
   CmIpv6TptAddr ipv6GenSockAddr;
#endif
#endif

#ifdef HI_TLS
   Bool         initOpenSSL;    /* initialize OpenSSL? */
   U16          numContexts;    /* maximum num of OpenSSL contexts */
   HiPRNG       prng;           /* PRNG configuration */
#endif /* HI_TLS */
   /* lhi_x_001.main_8 Modified the initialized region and pool */
   Region       initRegion;
   Pool         initPool;
} HiGenCfg;

/* Transport SAP configuration.
 */
typedef struct hiSapCfg
{
   SpId         spId;           /* service provider SAP id */
   Bool         flcEnb;         /* flow control enabled? */
   U32          txqCongStrtLim; /* flc start memory limit in bytes */
   U32          txqCongDropLim; /* flc drop memory limit in bytes */
   U32          txqCongStopLim; /* flc stop memory limit in bytes */
   U16          numBins;        /* for the conn block hash list */
#ifdef HI_LKSCTP
   U8           type;        /* type of the sap  */
   Bool         hBeatEnable; /* Enabling Heart Beat through LM*/
/* lhi_x_007.main_1 : Updated for the support of configurable RTO parameters, 
  HBeat value Max retransmissions (Init, Path, Association)*/

   /* lhi_x_001.main_9: Updated the varibale type to U32 from U16 for follwing variables rtoInitial, rtoMin,
    * rtoMax,cookieLife, intervalTm*/
   U32          rtoInitial;  /* Reconfigurable */ /* Initial value of RTO */
   U32          rtoMin;      /* Reconfigurable */ /* Minimum RTO */
   U32          rtoMax;      /* Reconfigurable */ /* Maximum RTO */
   U16          t1Init;      /* Reconfigurable */ /* T1 init */
   U32          cookieLife;  /* Reconfigurable */ /* Life time for a Valid Cookie */
   U32          intervalTm;  /* Reconfigurable */ /* Default Heartbeat interval timer value */
#ifdef HI_LKSCTP_USER_CONFIG
   /* lhi_x_001.main_7 : Handling of instream and outstream */
   U16          maxNmbInStrms;  /* Maximum no. of in streams Per
                                   Association */
   U16          maxNmbOutStrms; /* Maximum no. of out streams Per
                                   Association */
#endif
#endif

   /* For Pst to upper interface */
   Priority     uiPrior;
   Route        uiRoute;
   Selector     uiSel;
   MemoryId     uiMemId;

   /* TCP application headers supported on this TSAP */
   HiHdrInfo    hdrInf[LHI_MAX_HDR_TYPE];

#ifdef TDS_ROLL_UPGRADE_SUPPORT
   Bool         remIntfValid;   /* remote i/f version num valid? */
   CmIntfVer    remIntfVer;     /* remote i/f version num */
#endif

} HiSapCfg;


#ifdef HI_TLS

/* TLS/OpenSSL context configuration.
 */
typedef struct hiCtxCfg
{
   S16          ctxId;
   S8           caPath[LHI_OSSL_PATHLEN];
   S8           caFile[LHI_OSSL_PATHLEN];
   S8           certFile[LHI_OSSL_PATHLEN];
   S8           privKeyFile[LHI_OSSL_PATHLEN];
   U32          privKeyFileType;
   U32          verifyMode;
   S8           ciphers[LHI_OSSL_CIPHERLEN];
   Bool         cacheSessions;
   U8           sessIdCtx[LHI_OSSL_SESSIDCTXLEN];
   U8           sessIdCtxLen;
   U32          sessTimeout;
/* lhi_x_003.main_1 : To make verification depth and TLS method as 
                     configurable parameter */
#ifdef HI_VERIFY_DEPTH
   U8           verifyDepth;
#endif   
#ifdef HI_TLS_METHOD
   U8           method;
#endif   
} HiCtxCfg;

#endif /* HI_TLS */


/* General statistics.
 */
typedef struct hiGenSts
{
   StsCntr      numCons;        /* total number of connections */
   StsCntr      sockTxErr;      /* socket transmit error */
   StsCntr      sockRxErr;      /* socket receive error */
   StsCntr      sockOpenErr;    /* socket open error */
   StsCntr      sockBindErr;    /* socket bind error */
   StsCntr      sockCnctErr;    /* socket connect error */
   StsCntr      sockLstnErr;    /* socket listen error */
   StsCntr      sockSOptErr;    /* socket set-option error */
   StsCntr      sockClosErr;    /* socket close error */
   StsCntr      sockShutErr;    /* socket shutdown error */
   StsCntr      rxMsgVerErr;    /* version number error */
   StsCntr      numFlcInd;      /* num of flow control indications */
   StsCntr      numTxbytes;     /* num of bytes transmitted */
   StsCntr      numRxbytes;     /* num of bytes received */
   StsCntr      numTxTcpMsg;    /* num of transmitted TCP messages */
   StsCntr      numRxTcpMsg;    /* num of received TCP messages */
   StsCntr      numTxUdpMsg;    /* num of transmitted UDP messages */
   StsCntr      numRxUdpMsg;    /* num of received UDP messages */
   StsCntr      numTxRawMsg;    /* num of transmitted raw messages */
   StsCntr      numRxRawMsg;    /* num of received raw messages */
#ifdef HI_LKSCTP
   StsCntr      numTxSctpMsg;   /* num of transmitted SCTP messages */
   StsCntr      numRxSctpMsg;   /* num of received SCTP messages */
#endif

#ifdef HI_TLS
   StsCntr      numTxTlsMsg;    /* num of transmitted TLS messages */
   StsCntr      numRxTlsMsg;    /* num of received TLS messages */
#endif

} HiGenSts;


/* SAP statistics.
 */
typedef struct hiSapSts
{
   SpId         sapId;          /* sap Id */
   StsCntr      numCons;        /* num of connections in the SAP */
   StsCntr      numTxbytes;     /* num of bytes transmitted */
   StsCntr      numRxbytes;     /* num of bytes received */
   StsCntr      numTxTcpMsg;    /* num of transmitted TCP messages */
   StsCntr      numRxTcpMsg;    /* num of received TCP messages */
   StsCntr      numTxUdpMsg;    /* num of transmitted UDP messages */
   StsCntr      numRxUdpMsg;    /* num of received UDP messages */
   StsCntr      numTxRawMsg;    /* num of transmitted raw messages */
   StsCntr      numRxRawMsg;    /* num of received raw messages */
#ifdef HI_LKSCTP
   StsCntr      numTxSctpMsg;   /* num of transmitted SCTP messages */
   StsCntr      numRxSctpMsg;   /* num of received SCTP messages */
#endif

#ifdef HI_TLS
   StsCntr      numTxTlsMsg;    /* num of transmitted TLS messages */
   StsCntr      numRxTlsMsg;    /* num of received TLS messages */
#endif

} HiSapSts;


/* Solicited status.
 */
typedef struct hiSapSta
{
   SpId         spId;           /* sap Id */
   State        state;          /* sap state */

#ifdef TDS_ROLL_UPGRADE_SUPPORT  
   Bool         remIntfValid;   /* remote i/f version valid? */
   CmIntfVer    remIfVer;       /* remote i/f version of this sap */
   CmIntfVer    selfIfVer;      /* self i/f version of this sap */
#endif

} HiSapSta;

/* Unsolicited status indication.
 */
typedef struct hiAlarmInfo
{
   SpId         spId;           /* sap Id */
   U8           type;           /* which member of inf is present */
  /*lhi_x_001.main_9: Added new elements*/
#ifdef HI_LKSCTP
   U16          error;
   U32          assocId; 
#endif
   union
   {
      State     state;          /* TSAP state */
      State     conState;       /* connection state */
      Mem       mem;            /* region/pool (resource related) */
      U8        parType;        /* parameter type */
#ifdef HI_TLS
      S32       osslError;      /* OpenSSL error code */
#endif

   } inf;

} HiAlarmInfo;


#ifdef DEBUGP
/* Debug control.
 */
typedef struct hiDbgCntrl
{
   U32          dbgMask;        /* Debug mask */

} HiDbgCntrl;
#endif


/* Trace control.
 */
typedef struct hiTrcCntrl
{
   SpId         sapId;          /* sap Id */
   S16          trcLen;         /* length to trace */

} HiTrcCntrl;



/* Configuration.
 */
typedef struct hiCfg
{
   union
   {
      HiGenCfg  hiGen;          /* general configuration */
      HiSapCfg  hiSap;          /* sap configuration */

#ifdef HI_TLS
      HiCtxCfg  hiCtx;          /* TLS/OpenSSL context config */
#endif

   } s;

} HiCfg;


/* lhi_x_004.main_1  1. modified statistics req to include messages
                              Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS 
typedef struct hiConSts
{
   StsCntr      numTxBytes;     /* num of bytes transmitted */
   StsCntr      numRxBytes;     /* num of bytes received */

}HiConSts;

typedef struct hiThrConSts
{
   U32 numCons;
   HiConSts *conSts;
  
}HiThrConSts;

typedef struct hiThrSts
{
   U32 numRcvThrds;
   HiThrConSts *thrConSts;     

}HiThrSts;

#endif /*LHI_THR_STS */


/* Statistics.
 */
typedef struct hiSts
{
   DateTime     dt;             /* date and time */
   Duration     dura;           /* duration */

   union
   {
      HiGenSts  genSts;         /* general statistics */
      HiSapSts  sapSts;         /* sap statistics */

/* lhi_x_004.main_1  1. modified statistics req to include messages
                              Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS 
      HiThrSts  thrSts;         /* Thread statistics */
#endif /*LHI_THR_STS */

   } s;

} HiSts;
/* Solicited status.
 */
typedef struct hiSsta
{
   DateTime     dt;             /* date and time */

   union
   {
      SystemId  sysId;          /* system id */
      HiSapSta  sapSta;         /* sap status */

   } s;

} HiSsta;


/* Unsolicited status.
 */
typedef struct hiUsta
{
   CmAlarm      alarm;          /* alarm */
   HiAlarmInfo  info;           /* alarm information */

} HiUsta;


/* Trace.
 */
typedef struct hiTrc
{
   DateTime     dt;            /* date and time */
   U16          evnt;          /* event */
   /* lhi_x_001.main_1 (hi023.104) */
#ifdef HI_ENB_SAP_TRC
   SpId         sap;
#endif
} HiTrc;


/* Control.
 */
typedef struct hiCntrl
{
   DateTime     dt;             /* date and time */
   U8           action;         /* action */
   U8           subAction;      /* sub action */

   union
   {
      HiTrcCntrl        trcDat;         /* trace length */
      ProcId            dstProcId;      /* destination procId */
      Route             route;          /* route */
      Priority          priority;       /* priority */
      SpId              sapId;          /* sap Id */

#ifdef DEBUGP
      HiDbgCntrl        hiDbg;          /* debug printing control */
#endif
      U32               logMask;         /* logging printing control vsk */

   } ctlType;

} HiCntrl;


/* Management.
 */
typedef struct hiMngmt
{
   Header       hdr;            /* header */
   CmStatus     cfm;            /* response status/confirmation */

   union
   {
      HiCfg     cfg;            /* configuration */
      HiSts     sts;            /* statistics */
      HiSsta    ssta;           /* solicited status */
      HiUsta    usta;           /* unsolicited status */
      HiTrc     trc;            /* trace */
      HiCntrl   cntrl;          /* control */

   } t;

} HiMngmt;



/* Layer management interface primitive types.
 */
typedef S16  (*LhiCfgReq)       ARGS((Pst *pst, HiMngmt *cfg));
typedef S16  (*LhiCfgCfm)       ARGS((Pst *pst, HiMngmt *cfg));
typedef S16  (*LhiCntrlReq)     ARGS((Pst *pst, HiMngmt *cntrl));
typedef S16  (*LhiCntrlCfm)     ARGS((Pst *pst, HiMngmt *cntrl));
typedef S16  (*LhiStsReq)       ARGS((Pst *pst, Action action,
                                      HiMngmt *sts));
typedef S16  (*LhiStsCfm)       ARGS((Pst *pst, HiMngmt *sts));
typedef S16  (*LhiStaReq)       ARGS((Pst *pst, HiMngmt *sta));
typedef S16  (*LhiStaInd)       ARGS((Pst *pst, HiMngmt *sta));
typedef S16  (*LhiStaCfm)       ARGS((Pst *pst, HiMngmt *sta));
typedef S16  (*LhiTrcInd)       ARGS((Pst *pst, HiMngmt *trc,
                                      Buffer *mBuf));


/* Layer management interface primitives.
 */
#ifdef HI
EXTERN S16  HiMiLhiCfgReq       ARGS((Pst *pst, HiMngmt *cfg));
EXTERN S16  HiMiLhiCfgCfm       ARGS((Pst *pst, HiMngmt *cfg));
EXTERN S16  HiMiLhiCntrlReq     ARGS((Pst *pst, HiMngmt *cntrl));
EXTERN S16  HiMiLhiCntrlCfm     ARGS((Pst *pst, HiMngmt *cntrl));
EXTERN S16  HiMiLhiStsReq       ARGS((Pst *pst, Action action,
                                      HiMngmt *sts));
EXTERN S16  HiMiLhiStsCfm       ARGS((Pst *pst, HiMngmt *sts));
EXTERN S16  HiMiLhiStaReq       ARGS((Pst *pst, HiMngmt *sta));
EXTERN S16  HiMiLhiStaCfm       ARGS((Pst *pst, HiMngmt *sta));
EXTERN S16  HiMiLhiStaInd       ARGS((Pst *pst, HiMngmt *sta));
EXTERN S16  HiMiLhiTrcInd       ARGS((Pst *pst, HiMngmt *trc,
                                      Buffer *mBuf));
#endif /* HI */

#ifdef SM
EXTERN S16  SmMiLhiCfgReq       ARGS((Pst *pst, HiMngmt *cfg));
EXTERN S16  SmMiLhiCfgCfm       ARGS((Pst *pst, HiMngmt *cfg));
EXTERN S16  SmMiLhiCntrlReq     ARGS((Pst *pst, HiMngmt *cntrl));
EXTERN S16  SmMiLhiCntrlCfm     ARGS((Pst *pst, HiMngmt *cntrl));
EXTERN S16  SmMiLhiStsReq       ARGS((Pst *pst, Action action,
                                      HiMngmt *sts));
EXTERN S16  SmMiLhiStsCfm       ARGS((Pst *pst, HiMngmt *sts));
EXTERN S16  SmMiLhiStaReq       ARGS((Pst *pst, HiMngmt *sta));
EXTERN S16  SmMiLhiStaInd       ARGS((Pst *pst, HiMngmt *sta));
EXTERN S16  SmMiLhiStaCfm       ARGS((Pst *pst, HiMngmt *sta));
EXTERN S16  SmMiLhiTrcInd       ARGS((Pst *pst, HiMngmt *trc,
                                      Buffer *mBuf));
#endif /* SM */


/* Packing and unpacking functions.
 */
#ifdef LCLHI
EXTERN S16  cmPkLhiCfgReq       ARGS((Pst *pst, HiMngmt *cfg));
EXTERN S16  cmPkLhiCfgCfm       ARGS((Pst *pst, HiMngmt *cfg));
EXTERN S16  cmPkLhiCntrlReq     ARGS((Pst *pst, HiMngmt *cntrl));
EXTERN S16  cmPkLhiCntrlCfm     ARGS((Pst *pst, HiMngmt *cntrl));
EXTERN S16  cmPkLhiStsReq       ARGS((Pst *pst, Action action, HiMngmt *sts));
EXTERN S16  cmPkLhiStsCfm       ARGS((Pst *pst, HiMngmt *sts));
EXTERN S16  cmPkLhiStaReq       ARGS((Pst *pst, HiMngmt *sta));
EXTERN S16  cmPkLhiStaInd       ARGS((Pst *pst, HiMngmt *sta));
EXTERN S16  cmPkLhiTrcInd       ARGS((Pst *pst, HiMngmt *trc, Buffer *mBuf));
EXTERN S16  cmPkLhiStaCfm       ARGS((Pst *pst, HiMngmt *sta));

/* lhi_x_004.main_1  1. modified statistics req to include messages
                              Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS

EXTERN S16  cmPkHiThrConSts     ARGS((HiThrConSts *sts, Pst *pst, Buffer *mBuf));
EXTERN S16  cmPkHiConSts        ARGS((HiConSts *sts, Buffer *mBuf));

EXTERN S16  cmUnpkHiThrConSts   ARGS((HiThrConSts *sts, Pst *pst, Buffer *mBuf));
EXTERN S16  cmUnpkHiConSts      ARGS((HiConSts *sts, Buffer *mBuf));
#endif /*LHI_THR_STS */

EXTERN S16  cmUnpkLhiCfgReq     ARGS((LhiCfgReq func, Pst *pst,
                                      Buffer *mBuf));
EXTERN S16  cmUnpkLhiCfgCfm     ARGS((LhiCfgCfm func, Pst *pst,
                                    Buffer *mBuf));
EXTERN S16  cmUnpkLhiCntrlReq   ARGS((LhiCntrlReq func, Pst *pst,
                                      Buffer *mBuf));
EXTERN S16  cmUnpkLhiCntrlCfm   ARGS((LhiCntrlCfm func, Pst *pst,
                                      Buffer *mBuf));
EXTERN S16  cmUnpkLhiStsReq     ARGS((LhiStsReq func, Pst *pst,
                                      Buffer *mBuf));
EXTERN S16  cmUnpkLhiStsCfm     ARGS((LhiStsCfm func, Pst *pst,
                                      Buffer *mBuf));
EXTERN S16  cmUnpkLhiStaReq     ARGS((LhiStaReq func, Pst *pst,
                                      Buffer *mBuf));
EXTERN S16  cmUnpkLhiStaInd     ARGS((LhiStaInd func, Pst *pst,
                                      Buffer *mBuf));
EXTERN S16  cmUnpkLhiStaCfm     ARGS((LhiStaCfm func, Pst *pst,
                                      Buffer *mBuf));
EXTERN S16  cmUnpkLhiTrcInd     ARGS((LhiTrcInd func, Pst *pst,
                                      Buffer *mBuf));
#endif /* LCLHI */


/* Layer manager activation functions.
 */
EXTERN S16  smHiActvTsk         ARGS((Pst *pst, Buffer *mBuf)); 
EXTERN S16  smHiActvInit        ARGS((Ent ent, Inst inst,
                                      Region region, Reason reason));
/* lhi_x_002.main_1 : Decleration of hiActvInit and hiActvTsk is moved from
                      hi.x to lhi.x */ 
                      
#ifdef SS_MULTIPLE_PROCS
EXTERN S16 hiActvInit       ARGS((ProcId procId,
                                  Ent entity, 
                                  Inst inst, 
                                  Region region,
                                  Reason reason,
                                  Void **xxCb));
#else /* SS_MULTIPLE_PROCS */

EXTERN S16  hiActvInit          ARGS((Ent ent, Inst inst,
                                      Region region, Reason reason));
#endif /* SS_MULTIPLE_PROCS */
EXTERN S16  hiActvTsk           ARGS((Pst *pst, Buffer *mBuf));

#ifdef __cplusplus
}
#endif

#endif /* __LHIX__ */
 

/********************************************************************30**
 
         End of file:     lhi.x@@/main/10 - Tue Feb  1 16:04:21 2011
 
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

    ver       pat     init                  description
----------- --------- ---- -----------------------------------------------
1.1         ---       asa  1. initial release.
1.1+        hi002.11  asa  1. changed HiGenCfg.numCons to U32 from U16.
                           2. added HiHdrInfo in HiSapCfg.
/main/2     ---       cvp  1. added numFdsPerSet and numFdBins in 
                              HiGenCfg structure.
                           2. changed the copyright header.
/main/4               sb   1. changes for Raw socket support. 
/main/4+    hi005.13  cvp  1. Added numUdpMsgsToRead, numRawMsgsToRead,
                              numClToAccept and selTimeout general 
                              configuration variables.
/main/4+    hi009.104 mmh  1. Rolling upgrade changes under compile flag
                              TDS_ROLL_UPGRADE_SUPPORT, as per tcr0020.txt:
                              - added new fields remIntfValid, remIntfVer in
                                the structure HiSapCfg for RUG.
                              - added new fields remIntfValid, selfIfVer and 
                                remIfVer in the struct HiSapSta for RUG.
                           2. added new fields to specify the addr to use to 
                              bind generic sockin HiGenCfg structure under
                              HI_SPECIFY_GENSOCK_ADDR flag.
/main/1      ---       kp   1. Updated for release 1.5. Added TLS related
                              configuration structures.
/main/5  lhi_x_001.main_1   ss   1. Add Sap Id in Trace
/main/1  lhi_x_002.main_1   ss   1. Decleration of hiActvInit and hiActvTsk 
                                    is moved from hi.x to lhi.x.

/main/1  lhi_x_003.main_1   ss   1. To make TLS method and certificate 
                                    verification depth as a configurable 
                                    parameter.
/main/1   lhi_x_004.main_1 svp  1. modified statistics req to include messages
                              Tx/Rx in bytes per con per thread 
/main/6      ---       hs   1. Updated for release of 2.1
/main/7   lhi_x_007.main_1 cs   1. Updated for the support of configurable RTO parameters, HBeat value,
                               Max retransmissions (Init, Path, Association)
/main/8   lhi_x_001.main_7 rcs 1. Instream and outstream parameters added in lsapcfg
/main/9      ---      lhi_x_001.main_8 rss 1. Modified the initialized region and pool
/main/10     ---      lhi_x_001.main_9 ragrawal 1. Updated the varibale type to U32 from U16 
                                       for variables rtoInitial, rtoMin, rtoMax,
                                       cookieLife, intervalTm.
                                    2. Added new elements error and assocId under 
                                       hiAlarmInfo structure. 
*********************************************************************91*/

