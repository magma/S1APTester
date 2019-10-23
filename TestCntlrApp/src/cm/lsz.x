

/********************************************************************20**

     Name:     S1AP Layer 
  
     Type:     C include file
  
     Desc:     Structures, variables and typedefs required by the S1AP
               Layer Management Interface

     File:     lsz.x

     Sid:      lsz.x@@/main/9 - Thu Apr 26 19:09:03 2012

     Prg:      nm 

*********************************************************************21*/


/*
 *     The structures and variables declared in this file
 *     correspond to structures and variables used by
 *     the following TRILLIUM software:
 *
 *     part no.             description
 *     --------     ----------------------------------------------
 *     1000361      S1AP
 *
*/
 
#ifndef __LSZX__
#define __LSZX__

#ifdef __cplusplus
EXTERN "C" {
#endif

/**********************************************************************
 Configuration Structure Definition
**********************************************************************/

typedef U32 SzeNbId;     /* eNodeB Identifier */

typedef struct szMmeId
{
   U8              plmn[LSZ_MAX_PLMN_SIZE];       /* PLMN Identifier */
   U8              mmeGroupId[LSZ_MME_GROUP]; /* MME Group Id */
   U8              mmeCode[LSZ_MME_CODE];     /* MME Code */
} SzMmeId;

typedef struct szSctpAddr
{
   SctNetAddrLst   ipAddr;      /* Ip Address */
   SctPort         sctPort;     /* Port Number */
} SzSctpAddr; 

/* General Configuration */
typedef struct szGenConfig
{
   S16             nmbSztSaps;    /* Maximum Number of Upper SAPs */
   S16             nmbSctSaps;    /* Maximum Number of Lower SAPs */
   U32             nmbConn;       /* Maximum Number of S1 Connections */
   U32             nmbPeer;       /* Maximum Number of Peers */
   S16             timeRes;       /* Timer resolution */
#ifdef SZ_MME 
/* lsz_x_001.main_1 for dynamic peer configuration */
   Bool            dynamPeerFlag; /* To enable/disable the dynamic peer configuration */
/* lsz_x_001.main_2 for dynamic peer configuration */
   SpId            defDPeerUSapId; /* Default Dynamic Peer U Sap Id*/
/* lsz_x_001.main_8 for avtecs fixes */
#endif /* SZ_MME */
   Pst             lmPst;         /* Post structure for layer manager */
} SzGenCfg;

/* Upper SAP Configuration */
typedef struct szSztSapConfig
{
   SpId            spId;             /* Upper Sap ID */
   Selector        selector;         /* Coupling */
   MemoryId        mem;              /* Memory pool */
   Priority        priority;         /* priority */
   Route           route;            /* Route */
} SzSztSapCfg;


/* Lower SAP Configuration */
typedef struct szSctSapConfig
{
   SuId        suId;             /* S1AP Sap ID */
   SpId        spId;             /* Service Provider Sap ID */
   Selector    selector;         /* Coupling */
   MemoryId    mem;              /* Memory pool */
   Priority    priority;         /* priority */
   Route       route;            /* Route */
   ProcId      dstProcId;        /* destination processor Id */
   Ent         dstEntId;         /* destination entity Id */
   Inst        dstInstId;        /* destination instance Id */
   TmrCfg      tBndTmr;          /* bind timer configuation */
   U8          maxBndRetry;      /* Maximum number of bind retries allowed */
/*lsz_x_001.main_5: Updated for S1AP Release 3.1 */
#ifdef LSZV1
   SzSctpAddr      srcAddr;          /* Source Addr list and port number */
#endif /* LSZV1 */
} SzSctSapCfg;

/* Protocol Parameters */
typedef struct szProtConfig
{
/*lsz_x_001.main_5: Updated for S1AP Release 3.1 */
#ifndef LSZV1
   SzSctpAddr      srcAddr;          /* Source Addr list and port number */ 
#endif /* LSZV1 */
   U8              nodeType;         /* eNB or MME */

   union
   {
#ifdef SZ_ENB
      SzeNbId   eNbId;       /* eNodeB Identifier */
#endif /* SZ_ENB */

#ifdef SZ_MME
      SzMmeId   mmeId;       /* MME Identifier */
#endif /* SZ_MME */
   } u;

} SzProtCfg;

typedef struct szAssocCfg
{
   SctStrmId       locOutStrms;    /* num of outgoing streams */
   TknU16          comProcStrm;    /* Stream reserved for common procedures */
   CmNetAddr       priDstAddr;     /* primary destination addr */
   SctPort         dstPort;        /* destination port */
   SctNetAddrLst   dstAddrLst;     /* destination addr list */
   U16             nmbRetry;       /* number of retries allowed
                                      to recover association. If set to 0
                                      indicates infinite number of retries */
   TmrCfg          tmrAssocRecov;  /* association recovery timer */
} SzAssocCfg;

typedef struct szPeerInfo
{
   U8              type;        /* Peer node type */
   TknU32          peerId;      /* Peer Identifier */
   SpId            uSapId;       /*upper szt SAP id */ 
   SpId            sapId;       /* lower SAP id */ 
   SzAssocCfg      assocCfg;    /* SCTP Association configuration */
/*lsz_x_001.main_5: Updated for S1AP Release 3.1 */
#ifdef LSZV1
   Bool            skipUeSm;    /* Bypass the UE state machine */
#endif /* LSZV1 */
} SzPeerInfo;

typedef struct szPeerConfig
{
   U32             nmbPeers;    /* Number of Peers */
   SzPeerInfo      *peerInfo;   /* Peer Config */
} SzPeerCfg;

typedef struct szCfg
{
   union
   {
      SzGenCfg     gen;         /* General Configuration */
      SzSztSapCfg  sztSap;      /* SZT Interface SAP */
      SzSctSapCfg  sctSap;      /* SCT Interface SAP */
      SzProtCfg    prot;        /* Protocol Configuration */
      SzPeerCfg    peer;        /* Peer Configuration */
   } u;
} SzCfg;

/**********************************************************************
 Control Structure Definition
**********************************************************************/
typedef struct szSapCntrl    /* SAP Control */
{
   SpId         id;       /* SAP Identifier */
} SzSapCntrl;

#ifdef DEBUGP
typedef struct szDbgCntrl    /* Debug control */
{
   U32           dbgMask;    /* Debug mask */
} SzDbgCntrl;
#endif /* DEBUGP */

/* Trace control */
typedef struct szLSapTrcCntrl  /* Trace control */
{
   SpId            lSapId;     /* Lower SAP Identifier */
   U32             trcMask;    /* Trace Mask */
   S32             trcLen;     /* Trace Length */
} SzLSapTrcCntrl;

typedef struct szPNodeTrcCntrl  /* Trace control */
{
   TknU32          peerId;      /* Peer Identifier */
   U32             trcMask;     /* trace direction Mask */
   S32             trcLen;      /* trace Length */
} SzPNodeTrcCntrl;

typedef struct szPeerControl
{
   U32         nmbPeers;           /* Number of peers */
   TknU32      *peerId;            /* Array of Peer Identifiers */
}SzPeerCntrl;

typedef struct szCntrl       
{
   Action             action;      /* action */
   Action             subAction;   /* sub action */
   union
   {
      SzSapCntrl       sap;      /* SAP Control */
      SzLSapTrcCntrl   lSapTrc;  /* Lower SAP Trace control */
      SzPNodeTrcCntrl  pNodeTrc; /* Peer Node Trace control */
#ifdef DEBUGP
      SzDbgCntrl       dbg;      /* debug printing control */
#endif /* DEBUGP */
#ifdef SS_DIAG
/* lsz_x_001.main_9 : Change for Diagnostics */
      U32              logMask;  /* Logging Mask */
#endif
      SzPeerCntrl      peer;     /* Peer Control */
   } u;
} SzCntrl;        


/**********************************************************************
 Status Structure Definition
**********************************************************************/
typedef struct szGenSta              /* general status */
{
   U32             memSize;          /* Total static mem size reserved by S1AP */
   U32             memAlloc;         /* Total static mem allocated by S1AP */
   Cntr            nmbActvPeerConn;  /* number of active peer connections */
   U32             nmbPeer;          /* Number of peers */
} SzGenSta;

typedef struct szSapSta
{
   SpId            sapId;           /* SAP Identifier */
   U8              status;          /* Bound / Unbound / Binding */
} SzSapSta;

typedef struct szPeerStaInfo
{
   TknU32          peerId;        /* Peer Identifier */
   U8              peerState;     /* State of the peer */
   UConnId         spAssocId;     /* Association ID */
   Bool            connected;     /* connected ? */
   /* lsz_x_001.main_6: Removed the unused statistics counter */
#ifndef LSZV2
   U16             nmbRetries;    /* Number of retires to bring up an
                                     association that went down */
#endif /* LSZV2 */
}SzPeerStaInfo;

typedef struct szPeerSta
{
   U32             nmbPeer;       /* Number of peers */
   SzPeerStaInfo   *peerStaInfo;  /* List of Peers */
} SzPeerSta; 

typedef struct szSsta        /* Solicited status */
{
   union
   {
      SzSapSta   sap;         /* SAP Status */
      SystemId   sysId;       /* system id */
      SzGenSta   gen;         /* general status */
      SzPeerSta  peer;        /* Peer status */
   } s;
} SzSsta;                     /* solicited status */


/**********************************************************************
 Statistics Structure Definition
**********************************************************************/

typedef struct szCntr
{
   Cntr  tx;        /* number of messages transmitted */
   Cntr  rx;        /* number of messages received */
} SzCntr;

typedef struct szPduSts
{
   SzCntr eRABSetupReq;           /* E-RAB setup request */
   SzCntr eRABSetupResp;          /* E-RAB setup response */
   SzCntr eRABModReq;             /* E-RAB modify request */
   SzCntr eRABModResp;            /* E-RAB modify response */
   SzCntr eRABRelCmd;             /* E-RAB release command */
   SzCntr eRABRelComp;            /* E-RAB release complete */
   SzCntr eRABRelReq;             /* E-RAB release request */
   SzCntr initCxtSetup;           /* Initial Context setup request */
   SzCntr initCxtSetupResp;       /* Initial Context setup response */
   SzCntr initCxtSetupFail;       /* Initial Context setup failure */
   SzCntr ueCxtRelReq;            /* UE Context release request */
   SzCntr ueCxtRelCmd;            /* UE Context release command */
   SzCntr ueCxtRelComp;           /* UE Context release complete */
   SzCntr ueCxtModReq;            /* UE Context Modification request */
   SzCntr ueCxtModResp;           /* UE Context Modification response */
   SzCntr ueCxtModFail;           /* UE Context Modification failure */
   SzCntr initUEMsg;              /* Initial UE Message */
   SzCntr dwnNASTpt;              /* Downlink NAS transport */
   SzCntr upNASTpt;               /* Uplink NAS transport */
   SzCntr nonDelIndNAS;           /* NAS non delivery indication */
   SzCntr errInd;                 /* Error Indication */
   SzCntr noData;                 /* No Data */
   SzCntr reset;                  /* Reset */
   SzCntr resetAck;               /* Reset Acknowledge */
   SzCntr setupReq;               /* S1 Setup request */
   SzCntr setupResp;              /* S1 Setup response */
   SzCntr setupFail;              /* S1 Setup Failure */
   SzCntr paging;                 /* Paging */
   SzCntr handReqd;               /* Handover required */
   SzCntr handCmd;                /* Handover command */
   SzCntr handPrepFail;           /* Handover preparation failure */
   SzCntr handReq;                /* Handover Request */
   SzCntr handReqAck;             /* Handover Request Acknowledge */
   SzCntr handFail;               /* Handover Failure */
   SzCntr handNtfy;               /* Handover notify */
   SzCntr pathSwchReq;            /* Path Switch request */
   SzCntr pathSwchReqAck;         /* Path Switch request acknowledge */
   SzCntr pathSwchReqFail;        /* Path Switch request failure */
   SzCntr handCan;                /* Handover cancel */
   SzCntr handCanAck;             /* Handover cancel acknowledge */
   SzCntr eNBStaTrans;            /* eNB status transfer */
   SzCntr mmeStaTrans;            /* MME status transfer */
   SzCntr deactTrace;             /* De activate Trace */
   SzCntr traceStart;             /* Trace Start*/
   SzCntr traceFailInd;           /* Trace Failure Indication*/
   SzCntr locReportCntrl;         /* Location Report Control */
   SzCntr locReportFailInd;       /* Location Report Failure Indication */
   SzCntr locReport;              /* Location Report */
   SzCntr enbCfgUpd;              /* ENB Configuration Update */
   SzCntr enbCfgUpdAck;           /* ENB Configuration Update Ack */
   SzCntr enbCfgUpdFail;          /* ENB Configuration Update Fail */
   SzCntr mmeCfgUpd;              /* MME Configuration Update */
   SzCntr mmeCfgUpdAck;           /* MME Configuration Update Ack */
   SzCntr mmeCfgUpdFail;          /* MME Configuration Update Fail */
   SzCntr upS1CDMA2000Tunn;       /* Uplink S1 CDMA2000 Tunneling */
   SzCntr dnS1CDMA2000Tunn;       /* Downlink S1 CDMA2000 Tunneling */
   SzCntr ueCapInfoInd;           /* UE Capability Info Indication */
   SzCntr overloadStart;          /* Overload Start */
   SzCntr overloadStop;           /* Overload Stop */
   SzCntr writeRepWarnReq;        /* Write Replace Warning Request */
   SzCntr writeRepWarnRsp;        /* Write Replace Warning Responst */
   SzCntr enbDirInfoTrans;        /* eNB direct Information Transfer */
   SzCntr mmeDirInfoTrans;        /* mme Direct Information Transfer */
   SzCntr privMsg;                /* Private Message */
   SzCntr eNBConfigTfr;           /* ENB Configuration Transfer */
   SzCntr mmeConfigTfr;           /* MME Configuration Transfer */
   SzCntr cellTrafficTrace;       /* Cell Traffic Trace */
/*lsz_x_001.main_5: Updated for S1AP Release 3.1 */
#ifdef LSZV1
   SzCntr killReq;                /* Kill Request */
   SzCntr killResp;               /* Kill Response */
   SzCntr dwlnkUeAssocLPPaTprt;   /* Downlink UE Associated LPPa Transport */
   SzCntr uplnkUeAssocLPPaTprt;   /* Uplink UE Associated LPPa Transport */
   SzCntr dwlnkNonUeAssocLPPaTprt;/* Downlink Non-UE Associated LPPa Transport */
   SzCntr uplnkNonUeAssocLPPaTprt;/* Uplink Non-UE Associated LPPa Transport */
#endif /* LSZV1 */
} SzPduSts;

/* lsz_x_001.main_3 Added SCT sap level statistics */
typedef struct szSctSapSts     /* SCT SAP Statistics */
{
   SuId         suId;            /* S1AP SCT SAP Id */
   struct
   {
      SzPduSts  pdu;             /* PDU statistics */
      SzCntr    szDedProcSts;    /* Number of messages exchanged for dedicated procedure */
      SzCntr    szComProcSts;    /* Number of messages exchanged for common procedure */
   }cfm;

} SzSctSapSts;

/*lsz_x_001.main_5: Updated for S1AP Release 3.1 */
#ifdef LSZV1
typedef struct szRadioNwErrSts /* Err sts for radio nw type err causes */
{
   StsCntr unknownMmeUeS1apId;  /* Unknown or invalid mme ue s1ap id */
   StsCntr unknownEnbUeS1apId;  /* Unknown or invalid enb ue s1ap id */
   StsCntr unknownPairUeS1apId; /* Unknown or invalid pair ue s1ap id */

}SzRadioNwErrSts;

typedef struct szProtErrSts /* Error statistics for protocol type err causes */
{
   /* Transfer syntax error */
   StsCntr transferSyntaxErr; 

   /* Abs syntax err with crit reject */
   StsCntr absSyntaxErrRej;
   
   /* Abs syntax error with criticality ignore and notify */
   StsCntr absSyntaxErrIgnAndNtfy;
   
   /* Msg not compatible with receiver state */
   StsCntr msgNotCompWithRcvrState;

   /* Semantic error */  
   StsCntr semanticErr;                     
   
   /* Abs syntax err falsely constructed msg */
   StsCntr absSyntaxErrFalslyConsMsg;

   /* Protunspecified constructed msg */
   StsCntr protunspecified;

}SzProtErrSts;

typedef struct szErrSts             /* S1AP Error Statistics */
{
   SzRadioNwErrSts   radioNwErrSts; /* Statistics for radio nw errors */
   SzProtErrSts      protErrSts;    /* Statistics for protocol errors */

}SzErrSts;
#endif   /* LSZV1 */

typedef struct szPeerNodeSts  /* General Peer Node Statistics */
{
   TknU32       peerId;       /* Peer Identifier */
   struct
   {
      Cntr      nmbUnexpEvt;  /* number of Unexpected events received */
      /* lsz_x_001.main_6: Removed the unused statistics counter */
#ifndef LSZV2
      Cntr      nmbTRafExp;   /* number of Timer wait for reset ack expiry */
#endif /* LSZV2 */
      SzPduSts  pdu;          /* PDU statistics */
      SzCntr    szDedProcSts; /* No. of msgs exchanged for dedicated procedure */
      SzCntr    szComProcSts; /* No. of msgs exchanged for common procedure */
/*lsz_x_001.main_5: Updated for S1AP Release 3.1 */
#ifdef LSZV1
      SzErrSts  errSts;       /* Error statistics */
#endif  /* LSZV1 */
   }cfm;

} SzPeerNodeSts;

typedef struct szAudSts
{
   Cntr  nmbAudReq;         /* Number of Times Audit initiated */
   Cntr  nmbAudConn;        /* Number of connections scanned during audit */
   Cntr  nmbAudPeer;        /* Number of connecitons audited during audit */
   Cntr  nmbAudFlc;         /* Number of connections deleted after audit */

}SzAudSts;

typedef struct szGenSts
{
   Cntr nmbConn;              /* total number of connections established */
   Cntr nmbFailConn;          /* number of failed connection establishments */
   U32  maxMemAlloc;          /* maximum memory allocated */
   Cntr nmbDecErr;            /* number of Erroneous messages received */
   Cntr nmbEncErr;            /* number of encode messages errors */
   SzAudSts audSts;           /* Audit Statistics */
} SzGenSts;

typedef struct szSts         /* Statistics structure */
{
   union
   {
      SzGenSts      gen;      /* general statistics */
      SzPeerNodeSts node;     /* peer node statistics */
      SzSctSapSts   sctSap;   /* SCT SAP statistics */
   } u;
} SzSts;     


/********************************************************************RA**
 Alarms Structure Definition
*********************************************************************RA*/
typedef struct szUstaDgn     /* Alarm diagnostics structure */
{
   U8 type;
   union
   {
      MemoryId     mem;          /* Memory pool and region */
      SpId         sapId;        /* SAP ID on which event received */
      TknU32       peerId;       /* Peer Identifier */
      UConnId      connId;       /* Connection Identifier */
      U8           data[LSZ_USTA_MAX_DGNVAL]; /* Data Buffer */
   }u;
} SzUstaDgn;

typedef struct szUsta
{
   DateTime        dt;          /* date and time */
   CmAlarm         alarm;       /* alarm */
   SzUstaDgn       dgn;         /* alarm diagnostics */
} SzUsta;                       /* unsolicited status */

/**********************************************************************
 Trace Structure Definition
**********************************************************************/
typedef struct szTrc
{
   DateTime        dt;          /* date and time */
   U16             event;       /* Event */
   SzSctpAddr      srcAddr;     /* Source Address */  
   SzSctpAddr      dstAddr;     /* Destination Address */  
   SpId            sapId;       /* SAP Identifier */
   UConnId         suConnId;    /* S1AP connection identifier */
} SzTrc;

/**********************************************************************
 General Structure Definition
**********************************************************************/
typedef struct szMngmt
{
   Header      hdr;           /* header */

   CmStatus    cfm;           /* primitive's status/conf. */

   union 
   {
      SzCfg    cfg;           /* configuration */
      SzCntrl  cntrl;         /* control */
      SzSsta   ssta;          /* solicited status */
      SzUsta   usta;          /* unsolicited status */
      SzSts    sts;           /* statistics */
      SzTrc    trc;           /* Trace */
   } u;
} SzMngmt;

/**********************************************************************
 Interface Primitives
**********************************************************************/

typedef S16 (*LszCfgReq)   ARGS((
   Pst *pst,
   SzMngmt *cfg
   ));

typedef S16 (*LszCfgCfm)   ARGS((
   Pst *pst,
   SzMngmt *cfg
   ));

typedef S16 (*LszCntrlReq) ARGS((
   Pst *pst,
   SzMngmt *cntrl
   ));

typedef S16 (*LszCntrlCfm) ARGS((
   Pst *pst,
   SzMngmt *cntrl
   ));

typedef S16 (*LszStsReq)   ARGS((
   Pst *pst,
   Action action,
   SzMngmt *sts
   ));

typedef S16 (*LszStsCfm)   ARGS((
   Pst *pst,
   SzMngmt *sts
   ));

typedef S16 (*LszStaReq)   ARGS((
   Pst *pst,
   SzMngmt *sta
   ));

typedef S16 (*LszStaCfm)   ARGS((
   Pst *pst,
   SzMngmt *sta
   ));

typedef S16 (*LszStaInd)   ARGS((
   Pst *pst,
   SzMngmt *usta
   ));

typedef S16 (*LszTrcInd)   ARGS((
   Pst *pst,
   SzMngmt *trc,
   Buffer *mBuf
   ));

#ifdef SZ       
EXTERN S16 SzMiLszCfgReq   ARGS((Pst *pst, SzMngmt *cfg));
EXTERN S16 SzMiLszCfgCfm   ARGS((Pst *pst, SzMngmt *cfg));
EXTERN S16 SzMiLszCntrlReq ARGS((Pst *pst, SzMngmt *cntrl));
EXTERN S16 SzMiLszCntrlCfm ARGS((Pst *pst, SzMngmt *cntrl));
EXTERN S16 SzMiLszStaInd   ARGS((Pst *pst, SzMngmt *sta));
EXTERN S16 SzMiLszTrcInd   ARGS((Pst *pst, SzMngmt *trc, Buffer *mBuf));
EXTERN S16 SzMiLszStaReq   ARGS((Pst *pst, SzMngmt *sta));
EXTERN S16 SzMiLszStaCfm   ARGS((Pst *pst, SzMngmt *sta));
EXTERN S16 SzMiLszStsReq   ARGS((Pst *pst, Action action, SzMngmt *sts));
EXTERN S16 SzMiLszStsCfm   ARGS((Pst *pst, SzMngmt *sts));
/* lsz_x_001.main_7: Updated for PSF-S1AP 1.1 release */
#ifdef SZ_FTHA
EXTERN S16 SzMiShtCntrlReq ARGS((Pst *pst, ShtCntrlReqEvnt *reqInfo));
EXTERN S16 SzMiShtCntrlCfm ARGS((Pst *pst, ShtCntrlCfmEvnt *cfmInfo));
#endif /* SZ_FTHA */
#endif /* SZ */

#ifdef SM       
EXTERN S16 SmMiLszCfgReq   ARGS((Pst *pst, SzMngmt *cfg));
EXTERN S16 SmMiLszCfgCfm   ARGS((Pst *pst, SzMngmt *cfg));
EXTERN S16 SmMiLszStaCfm   ARGS((Pst *pst, SzMngmt *sta));
EXTERN S16 SmMiLszStaReq   ARGS((Pst *pst, SzMngmt *sta));
EXTERN S16 SmMiLszStaInd   ARGS((Pst *pst, SzMngmt *sta));
EXTERN S16 SmMiLszCntrlReq ARGS((Pst *pst, SzMngmt *cntrl));
EXTERN S16 SmMiLszCntrlCfm ARGS((Pst *pst, SzMngmt *cntrl));
EXTERN S16 SmMiLszStsReq   ARGS((Pst *pst, Action action,SzMngmt *sts));
EXTERN S16 SmMiLszStsCfm   ARGS((Pst *pst, SzMngmt *sts));
EXTERN S16 SmMiLszTrcInd   ARGS((Pst *pst, SzMngmt *trc, Buffer *mBuf));
#endif /* SM */

#ifdef SS_MULTIPLE_PROCS
EXTERN S16 smSzActvInit    ARGS((ProcId proc, Ent ent, Inst inst,
                                 Region region, 
                                 Reason reason, Void **xxCb));
EXTERN S16 szActvInit      ARGS((ProcId proc, Ent ent, Inst inst,
                                 Region region, 
                                 Reason reason, Void **xxCb));
#else /* SS_MULTIPLE_PROCS */
EXTERN S16 smSzActvInit    ARGS((Ent ent, Inst inst, Region region,
                                 Reason reason));
EXTERN S16 szActvInit      ARGS((Ent ent, Inst inst, Region region,
                                 Reason reason));
#endif /* SS_MULTIPLE_PROCS */

EXTERN S16 smSzActvTsk     ARGS((Pst *pst, Buffer *mBuf));
EXTERN S16 szActvTsk       ARGS((Pst *pst, Buffer *mBuf));

/**********************************************************************
 Pack/Unpack Declarations 
**********************************************************************/
#ifdef LCLSZ
EXTERN S16 cmPkSzMmeId ARGS((
         SzMmeId *param,
         Buffer *mBuf
         ));
EXTERN S16 cmPkSzSctpAddr ARGS((
         SzSctpAddr *param,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkSzMmeId ARGS((
         SzMmeId *param,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkSzSctpAddr ARGS((
         SzSctpAddr *param,
         Buffer *mBuf
         ));
EXTERN S16 cmPkSzGenCfg ARGS((
         SzGenCfg *param,
         Buffer *mBuf
         ));
EXTERN S16 cmPkSzProtCfg ARGS((
         SzProtCfg *param,
         Buffer *mBuf
         ));
EXTERN S16 cmPkSzSztSapCfg ARGS((
         SzSztSapCfg *param,
         Buffer *mBuf
         ));
EXTERN S16 cmPkSzSctSapCfg ARGS((
         SzSctSapCfg *param,
         Buffer *mBuf
         ));
EXTERN S16 cmPkSzAssocCfg ARGS((
         SzAssocCfg *param,
         Buffer *mBuf
         ));
EXTERN S16 cmPkSzPeerInfo ARGS((
         SzPeerInfo *param,
         Buffer *mBuf
         ));
EXTERN S16 cmPkSzPeerCfg ARGS((
         Pst *pst,
         SzPeerCfg *param,
         Buffer *mBuf
         ));
EXTERN S16 cmPkSzCfg ARGS((
         SzCfg *param,
         Elmnt elmnt,
         Buffer *mBuf,
         Pst *pst
         ));
EXTERN S16 cmUnpkSzGenCfg ARGS((
         SzGenCfg *param,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkSzProtCfg ARGS((
         SzProtCfg *param,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkSzSztSapCfg ARGS((
         SzSztSapCfg *param,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkSzSctSapCfg ARGS((
         SzSctSapCfg *param,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkSzAssocCfg ARGS((
         SzAssocCfg *param,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkSzPeerInfo ARGS((
         SzPeerInfo *param,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkSzPeerCfg ARGS((
         Pst *pst,
         SzPeerCfg *param,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkSzCfg ARGS((
         SzCfg *param,
         Elmnt elmnt,
         Buffer *mBuf,
         Pst *pst
         ));
EXTERN S16 cmPkSzSapCntrl ARGS((
         SzSapCntrl *param,
         Buffer *mBuf
         ));
#ifdef DEBUGP
EXTERN S16 cmPkSzDbgCntrl ARGS((
         SzDbgCntrl *param,
         Buffer *mBuf
         ));  
#endif /* DEBUGP */
EXTERN S16 cmPkSzLSapTrcCntrl ARGS((
         SzLSapTrcCntrl *param,
         Buffer *mBuf
         ));
EXTERN S16 cmPkSzPNodeTrcCntrl ARGS((
         SzPNodeTrcCntrl *param,
         Buffer *mBuf
         ));
EXTERN S16 cmPkSzPeerCntrl ARGS((
         Pst *pst,
         SzPeerCntrl *param,
         Buffer *mBuf
         ));
EXTERN S16 cmPkSzCntrl ARGS((
         SzCntrl *param,
         Elmnt elmnt,
         Buffer *mBuf,
         Pst *pst
         ));
EXTERN S16 cmPkSzTrc ARGS((
         SzTrc *param,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkSzSapCntrl ARGS((
         SzSapCntrl *param,
         Buffer *mBuf
         ));
#ifdef DEBUGP
EXTERN S16 cmUnpkSzDbgCntrl ARGS((
         SzDbgCntrl *param,
         Buffer *mBuf
         ));
#endif /* DEBUGP */
EXTERN S16 cmUnpkSzLSapTrcCntrl ARGS((
         SzLSapTrcCntrl *param,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkSzPNodeTrcCntrl ARGS((
         SzPNodeTrcCntrl *param,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkSzPeerCntrl ARGS((
         Pst *pst,
         SzPeerCntrl *param,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkSzCntrl ARGS((
         SzCntrl *param,
         Elmnt elmnt,
         Buffer *mBuf,
         Pst *pst
         ));
EXTERN S16 cmUnpkSzTrc ARGS((
         SzTrc *param,
         Buffer *mBuf
         ));
EXTERN S16 cmPkSzUstaDgn ARGS((
         SzUstaDgn *param,
         Buffer *mBuf
         ));
EXTERN S16 cmPkSzUsta ARGS((
         SzUsta *param,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkSzUstaDgn ARGS((
         SzUstaDgn *param,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkSzUsta ARGS((
         SzUsta *param,
         Buffer *mBuf
         ));
EXTERN S16 cmPkSzGenSta ARGS((
         SzGenSta *param,
         Buffer *mBuf
         ));
EXTERN S16 cmPkSzSapSta ARGS((
         SzSapSta *param,
         S16 eventType,
         Buffer *mBuf
         ));
EXTERN S16 cmPkSzPeerStaInfo ARGS((
         SzPeerStaInfo  *param,          
         Buffer         *mBuf            
         ));
EXTERN S16 cmPkSzPeerSta ARGS((
         Pst        *pst,
         SzPeerSta  *param,  
         Buffer     *mBuf        
         ));
EXTERN S16 cmPkSzSsta ARGS((
         SzSsta *param,
         Elmnt elmnt,
         S16 eventType,
         Buffer *mBuf,
         Pst *pst
         ));
EXTERN S16 cmUnpkSzGenSta ARGS((
         SzGenSta *param,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkSzSapSta ARGS((
         SzSapSta *param,
         S16 eventType,
         Buffer *mBuf
         ));   
EXTERN S16 cmUnpkSzPeerStaInfo ARGS((
         SzPeerStaInfo  *param,
         Buffer         *mBuf
         ));
EXTERN S16 cmUnpkSzPeerSta ARGS((
         Pst        *pst,
         SzPeerSta  *param,
         Buffer     *mBuf
         ));
EXTERN S16 cmUnpkSzSsta ARGS((
         SzSsta *param,
         Elmnt elmnt,
         S16 eventType,
         Buffer *mBuf,
         Pst    *pst
         ));
EXTERN S16 cmPkSzCntr ARGS((
         SzCntr *param,
         Buffer *mBuf
         ));
EXTERN S16 cmPkSzPduSts ARGS((
         SzPduSts *param,
         Buffer *mBuf
         ));
/*lsz_x_001.main_5: Updated for S1AP Release 3.1 */
#ifdef LSZV1
EXTERN S16 cmPkSzErrSts ARGS((
         SzErrSts *param,
         Buffer *mBuf
         ));
#endif   /* LSZV1 */
EXTERN S16 cmPkSzSctSapSts ARGS((
         SzSctSapSts *param,
         S16 eventType,
         Buffer *mBuf
         ));
EXTERN S16 cmPkSzPeerNodeSts ARGS((
         SzPeerNodeSts *param,
         S16 eventType,
         Buffer *mBuf
         ));
EXTERN S16 cmPkSzAudSts ARGS((
         SzAudSts *param,
         Buffer *mBuf
         ));
EXTERN S16 cmPkSzGenSts ARGS((
         SzGenSts *param,
         Buffer *mBuf
         ));
EXTERN S16 cmPkSzSts ARGS((
         SzSts *param,
         Elmnt elmnt,
         S16 eventType,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkSzCntr ARGS((
         SzCntr *param,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkSzPduSts ARGS((
         SzPduSts *param,
         Buffer *mBuf
         ));
/*lsz_x_001.main_5: Updated for S1AP Release 3.1 */
#ifdef LSZV1
EXTERN S16 cmUnpkSzErrSts ARGS((
         SzErrSts *param,
         Buffer *mBuf
         ));
#endif   /* LSZV1 */
EXTERN S16 cmUnpkSzSctSapSts ARGS((
         SzSctSapSts *param,
         S16 eventType,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkSzPeerNodeSts ARGS((
         SzPeerNodeSts *param,
         S16 eventType,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkSzAudSts ARGS((
         SzAudSts *param,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkSzGenSts ARGS((
         SzGenSts *param,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkSzSts ARGS((
         SzSts *param,
         Elmnt elmnt,
         S16 eventType,
         Buffer *mBuf
         ));
EXTERN S16 cmPkSzMngmt ARGS((
         SzMngmt *param,
         S16 eventType,
         Ent entity,
         Buffer *mBuf,
         Pst *pst
         ));
EXTERN S16 cmUnpkSzMngmt ARGS((
         SzMngmt *param,
         S16 eventType,
         Ent entity,
         Buffer *mBuf,
         Pst *pst
         ));
EXTERN S16 cmPkLszCfgReq ARGS((
         Pst *pst,
         SzMngmt *cfg
         ));
EXTERN S16 cmPkLszCfgCfm ARGS((
         Pst *pst,
         SzMngmt *cfg
         ));
EXTERN S16 cmPkLszCntrlReq ARGS((
         Pst *pst,
         SzMngmt *cntrl
         ));
EXTERN S16 cmPkLszCntrlCfm ARGS((
         Pst *pst,
         SzMngmt *cntrl
         ));
EXTERN S16 cmPkLszStsReq ARGS((
         Pst *pst,
         Action action,
         SzMngmt *sts
         ));
EXTERN S16 cmPkLszStsCfm ARGS((
         Pst *pst,
         SzMngmt *sts
         ));
EXTERN S16 cmPkLszStaReq ARGS((
         Pst *pst,
         SzMngmt *sta
         ));
EXTERN S16 cmPkLszStaCfm ARGS((
         Pst *pst,
         SzMngmt *sta
         ));
EXTERN S16 cmPkLszStaInd ARGS((
         Pst *pst,
         SzMngmt *usta
         ));
EXTERN S16 cmPkLszTrcInd ARGS((
         Pst *pst,
         SzMngmt *trc,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkLszCfgReq ARGS((
         LszCfgReq func,
         Pst *pst,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkLszCfgCfm ARGS((
         LszCfgCfm func,
         Pst *pst,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkLszCntrlReq ARGS((
         LszCntrlReq func,
         Pst *pst,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkLszCntrlCfm ARGS((
         LszCntrlCfm func,
         Pst *pst,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkLszStsReq ARGS((
         LszStsReq func,
         Pst *pst,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkLszStsCfm ARGS((
         LszStsCfm func,
         Pst *pst,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkLszStaReq ARGS((
         LszStaReq func,
         Pst *pst,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkLszStaCfm ARGS((
         LszStaCfm func,
         Pst *pst,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkLszStaInd ARGS((
         LszStaInd func,
         Pst *pst,
         Buffer *mBuf
         ));
EXTERN S16 cmUnpkLszTrcInd ARGS((
         LszTrcInd func,
         Pst *pst,
         Buffer *mBuf
         ));
#endif /* LCLSZ */

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* __LSZX__ */

/*********************************************************************

         End of file:     lsz.x@@/main/9 - Thu Apr 26 19:09:03 2012

**********************************************************************/

/**********************************************************************

        Notes:

**********************************************************************/

/**********************************************************************

**********************************************************************/

/********************************************************************

        Revision history:

**********************************************************************/

/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     nm   Initial release
/main/1+     lsz_x_001.main_1 sn Dynamic peer addition feature added
/main/3      ---     ng   lsz_x_001.main_2 1. Updated for S1AP Release 2.1
/main/4      lsz_x_001.main_3 hsingh Added SCT sap level statistics
/main/5      ---     ajainx lsz_x_001.main_4 1. Updated for S1AP Release 2.2.
/main/6     lsz_x_001.main_5 pkaX Updated for S1AP Release 3.1.
/main/7      ---      lsz_x_001.main_6  pkaX 1. Removed the unused statistics counter.
/main/8      ---      lsz_x_001.main_7   pka   1. Updated for PSF-S1AP release.
/main/9      ---      lsz_x_001.main_8   va   1. Updated for S1AP Release 4.1.
$SID$               lsz_x_001.main_9  akaranth 1.Change for Diagnostics.
*********************************************************************91*/
