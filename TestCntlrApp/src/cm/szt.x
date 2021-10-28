/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */


/********************************************************************20**

     Name:     S1AP Layer

     Type:     C source file

     Desc:     C Source code for S1AP upper interface structures

     File:     szt.c

     Sid:      szt.x@@/main/9 - Thu Apr 26 19:39:43 2012

     Prg:      sn

*********************************************************************21*/

/* szt_x_001.main_6: Added to avoid multiple inclusion  */
#ifndef __SZTX__
#define __SZTX__

#ifdef __cplusplus
EXTERN "C" {
#endif

/*#include "szt_asn.x"*/
#include "szt_3gasn.x"

/*EXTERN U8  SzMsgId[SZT_MAX_PROC_ID][SZT_MAX_MSG_TYPE];*/
/* szt_x_001.main_8: Removed un-necessary include files  */

/* szt_x_001.main_3 S1AP performance related changes */
typedef U16 SztPort;       /* Port number */
#ifdef SZ_MME
/* szt_x_001.main_1 for dynamic peer configuration */
typedef U16 SztStrmId;     /* Stream Id */

typedef struct sztNetAddrLst
{
   U8            nmb;                        /* Number of Network Addresses */
   CmNetAddr     nAddr[SZT_MAX_NET_ADDRS];   /* Network Addresses List */
} SztNetAddrLst;
#endif /* SZ_MME */

typedef struct s1appdu
{
   CmMemListCp  memCp;
   SztS1AP_PDU  pdu;
}S1apPdu;

/* Connection Creation Structures */
typedef struct sztConReq
{
   TknU32               peerId;        /* Peer Identifier */
   union
   {
      UConnId              spConnId;   /* service provider instance identifier */
      UConnId              suConnId;   /* service user instance identifier */
   }u;
   S1apPdu              *pdu;          /* S1AP event structure */ 
/* Multi eNB support */
#ifdef MULTI_ENB_SUPPORT
   U8 enbId;
#endif
}SztConReq;

typedef SztConReq SztConInd;

typedef struct sztConRsp
{
   UConnId              suConnId;      /* service user instance identifier */
   UConnId              spConnId;      /* service provider instance identifier */
   S1apPdu              *pdu;          /* S1AP event structure */ 
/* Multi eNB support */
#ifdef MULTI_ENB_SUPPORT
   U32 enbId;
   U8 cntxtRelForS1Ho;
#endif
}SztConRsp;

/* Connection release Structures */
typedef struct sztRelReq
{
   U8                   connIdType;  /* Conn Id Type - Service User/Service Provider */
   U8                   relType;     /* Type of release */
   UConnId              connId;      /* Service User / Service provider ConnId */
   S1apPdu              *pdu;        /* S1AP event structure */ 
}SztRelReq;

typedef struct sztRelInd
{
   TknU32               suConnId;      /* service user instance identifier */
   UConnId              spConnId;      /* service provider instance identifier */
   S1apPdu              *pdu;          /* S1AP event structure */ 
}SztRelInd;

typedef SztConRsp SztConCfm;

typedef struct sztRelCfm
{
   UConnId              suConnId;     /* Conn Id Type - Ser User/Ser Provider */
   UConnId              spConnId;     /* Type of release */
   U8                   relType;      /* Release type */
   S1apPdu              *pdu;         /* S1AP event structure */ 
}SztRelCfm;

typedef SztConRsp SztRelRsp; 

typedef struct sztDatReq
{
   UConnId              spConnId;      /* service provider instance identifier */
   S1apPdu              *pdu;          /* S1AP event structure */ 
/* Multi eNB support */
#ifdef MULTI_ENB_SUPPORT
   U32 enbId;
#endif
}SztDatEvntReq;

typedef struct sztDatInd
{
   UConnId              suConnId;      /* service provider instance identifier */
   S1apPdu              *pdu;          /* S1AP event structure */
}SztDatEvntInd;

/* common procedure messages */
typedef struct sztUDatEvnt
{
   TknU32               transId;       /* Transaction Id */
   TknU32               peerId;        /* Peer Identifier */
   S1apPdu              *pdu;          /* S1AP event structure */ 
/* Multi eNB support */
#ifdef MULTI_ENB_SUPPORT
   U32 enbId;
#endif
}SztUDatEvnt;

/* UL Audit Message */

typedef struct sztConnSt
{
   UConnId      connId; /* service provider instance identifier */
   State        state;    /* state of UE-associated logical S1-connection */
}SztConnSt;
typedef struct sztAudConn
{
   U8           connIdType;
   U8           nmbConn;                      /* Number of cons to be audited */
   SztConnSt    connSt[SZT_MAX_AUD_CONN];     /* State of the connections */
}SztAudConn;

typedef struct sztAudPeer
{
   U32                  peerId;        /* Peer Identifier */
   State                peerState;     /* State of the peer */
}SztAudPeer;

typedef struct sztReqStatus
{
   U16   status;     /* status of the request */
   U16   cause;      /* cause incase status not ok */
}SztReqStatus;

/* szt_x_001.main_5: Structure which will contain the error Ies received during 
* encoding or decoding */
#ifdef SZ_ENC_DEC
typedef struct sztIeErrInfo
{
   U8     errType;         /* Type of error */
   U16    criticality;     /* Criticality of erroneous/non supported IE */
   U32    ieId;            /* IE id */
}SztIeErrInfo;

typedef struct sztEncDecErr
{
   U16           ieCount;                 /* Erroneous/non-supported IE count */
   SztIeErrInfo  ieInfo[SZT_MAX_ERR_IE];  /* Info present in IE */
}SztEncDecErr;

/* szt_x_001.main_5: Encoding/Decoding statistics */
typedef struct sztEncDecMsgSts
{
   StsCntr eRABSetupReq;        /* E-RAB setup request */
   StsCntr eRABSetupResp;       /* E-RAB setup response */
   StsCntr eRABModReq;          /* E-RAB modify request */
   StsCntr eRABModResp;         /* E-RAB modify response */
   StsCntr eRABRelCmd;          /* E-RAB release command */
   StsCntr eRABRelComp;         /* E-RAB release complete */
   StsCntr eRABRelReq;          /* E-RAB release request */
   StsCntr initCxtSetup;        /* Initial Context setup request */
   StsCntr initCxtSetupResp;    /* Initial Context setup response */
   StsCntr initCxtSetupFail;    /* Initial Context setup failure */
   StsCntr ueCxtRelReq;         /* UE Context release request */
   StsCntr ueCxtRelCmd;         /* UE Context release command */
   StsCntr ueCxtRelComp;        /* UE Context release complete */
   StsCntr ueCxtModReq;        /* UE Context Modification request */
   StsCntr ueCxtModResp;        /* UE Context Modification response */
   StsCntr ueCxtModFail;        /* UE Context Modification failure */
   StsCntr initUEMsg;           /* Initial UE Message */
   StsCntr dwnNASTpt;           /* Downlink NAS transport */
   StsCntr upNASTpt;            /* Uplink NAS transport */
   StsCntr nonDelIndNAS;        /* NAS non delivery indication */
   StsCntr errInd;              /* Error Indication */
   StsCntr noData;              /* No Data */
   StsCntr reset;               /* Reset */
   StsCntr resetAck;            /* Reset Acknowledge */
   StsCntr setupReq;            /* S1 Setup request */
   StsCntr setupResp;           /* S1 Setup response */
   StsCntr setupFail;           /* S1 Setup Failure */
   StsCntr paging;              /* Paging */
   StsCntr handReqd;            /* Handover required */
   StsCntr handCmd;             /* Handover command */
   StsCntr handPrepFail;        /* Handover preparation failure */
   StsCntr handReq;             /* Handover Request */
   StsCntr handReqAck;          /* Handover Request Acknowledge */
   StsCntr handFail;            /* Handover Failure */
   StsCntr handNtfy;            /* Handover notify */
   StsCntr pathSwchReq;         /* Path Switch request */
   StsCntr pathSwchReqAck;      /* Path Switch request acknowledge */
   StsCntr pathSwchReqFail;     /* Path Switch request failure */
   StsCntr handCan;             /* Handover cancel */
   StsCntr handCanAck;          /* Handover cancel acknowledge */
   StsCntr eNBStaTrans;         /* eNB status transfer */
   StsCntr mmeStaTrans;         /* MME status transfer */
   StsCntr deactTrace;          /* De activate Trace */
   StsCntr traceStart;          /* Trace Start*/
   StsCntr traceFailInd;        /* Trace Failure Indication*/
   StsCntr locReportCntrl;      /* Location Report Control */
   StsCntr locReportFailInd;    /* Location Report Failure Indication */
   StsCntr locReport;           /* Location Report */
   StsCntr enbCfgUpd;           /* ENB Configuration Update */
   StsCntr enbCfgUpdAck;        /* ENB Configuration Update Ack */
   StsCntr enbCfgUpdFail;       /* ENB Configuration Update Fail */
   StsCntr mmeCfgUpd;           /* MME Configuration Update */
   StsCntr mmeCfgUpdAck;        /* MME Configuration Update Ack */
   StsCntr mmeCfgUpdFail;       /* MME Configuration Update Fail */
   StsCntr upS1CDMA2000Tunn;    /* Uplink S1 CDMA2000 Tunneling */
   StsCntr dnS1CDMA2000Tunn;    /* Downlink S1 CDMA2000 Tunneling */
   StsCntr ueCapInfoInd;        /* UE Capability Info Indication */
   StsCntr overloadStart;       /* Overload Start */
   StsCntr overloadStop;        /* Overload Stop */
   StsCntr writeRepWarnReq;     /* Write Replace Warning Request */
   StsCntr writeRepWarnRsp;     /* Write Replace Warning Responst */
   StsCntr enbDirInfoTrans;     /* eNB direct Information Transfer */
   StsCntr mmeDirInfoTrans;     /* mme Direct Information Transfer */
   StsCntr pvtMsg;              /* Private message */
   StsCntr enbCfgTrans;         /* ENB Config Transfer */
   StsCntr mmeCfgTrans;         /* MME Config Transfer */
   StsCntr cellTraffTrc;        /* Cell Traffic Trace */
   StsCntr killReq;             /* Kill Request */
   StsCntr killResp;            /* Kill Response */
   StsCntr dwlnkUeAssocLPPaTprt;/* Downlink UE Associated LPPa Transport */
   StsCntr uplnkUeAssocLPPaTprt;/* Uplink UE Associated LPPa Transport */
   StsCntr dwlnkNonUeAssocLPPaTprt;/* Downlink Non-UE Associated LPPa Transport */
   StsCntr uplnkNonUeAssocLPPaTprt;/* Uplink Non-UE Associated LPPa Transport */
   StsCntr numDecErr;           /* Total Number of decode errors */
}SztEncDecMsgSts; /* SztEncDecMsgSts */

typedef struct sztSts
{
   U8               stsType;          /* Type of statistics */
   SztEncDecMsgSts  msgSts;           /* Encode/Decode statistics */
}SztSts;

typedef struct sztEncDecStatus
{
   U16            status;
   U16            cause;
   U16            nmbOct;
   SztEncDecErr   errInfo;
}SztEncDecStatus;

#endif /* SZ_ENC_DEC */

typedef struct sztAudEvnt
{
   U8                type;       /* Audit type */
   union
   {
      SztAudConn      audConn;   /* Audit based on the connection */
      SztAudPeer      audPeer;   /* Audit based on the peer */
   }u;
   SztReqStatus    status;       /* Audit status in cfm */
}SztAudEvnt;

typedef struct sztStaInd 
{
   TknU32       peerId;        /* Peer Identifier */
   U8           type;          /* type */
   U8           status;
   U8           reason;
}SztStaInd;

typedef struct sztLclErrInd
{
   TknU32       suConnId;      /* service provider instance identifier */
   TknU32       spConnId;      /* service user instance identifier */
   TknU32       transId;       /* Transaction identifier to map error ind.*/
   U8           causeType;     /* cause type */
   U8           causeValue;    /* cause value */
}SztLclErrInd;

/* szt_x_001.main_6: Added for TC Dec/Enc  */
/* S1AP IE event structure */
typedef struct szIePdu
{
   CmMemListCp  memCp;
   union
   {
      SztSrceNB_ToTgeteNB_TprntCont  srcToTget;
      SztTgeteNB_ToSrceNB_TprntCont  tgetToSrc;
#ifdef SZTV3
      /* szt_x_001.main_9 : support for Source RNC to Target RNC */
      SztSrcRNC_ToTgetRNC_TprntCont_3gasn   srcRncToTgetRnc;
      SztTgetRNC_ToSrcRNC_TprntCont_3gasn   TgetRncToSrcRnc;
      SztSrcCellID                          utraSrcCellId;
#endif
      SztGlobal_ENB_ID                      globalEnbId;
   }u;
}SzIePdu;

/* all encode decode messages */
typedef struct sztEncDecEvnt
{
   U32                  transId;
   TknU8                type;          /* type */
/* szt_x_001.main_6: Added for TC Dec/Enc  */
#ifdef SZTV1
   TknU8                ieType;        /* PDU type */
#endif /* SZTV1 */
   union
   {
      S1apPdu           *pdu;          /* S1AP event structure */ 
/* szt_x_001.main_6: Added for TC Dec/Enc  */
#ifdef SZTV1
      SzIePdu           *iePdu;        /* S1AP IE event structure */
#endif /* SZTV1 */
      Buffer            *mBuf;
   }u;
}SztEncDecEvnt;

typedef struct sztFlcInd 
{
   TknU32       peerId;    /* Peer Identifier */
   U8           status;    /* status of the congestion */
}SztFlcInd;

#ifdef SZ_MME
/* szt_x_001.main_1 for dynamic peer configuration */
typedef struct sztPeerAssocInd
{
   SztNetAddrLst dstAddrLst;
   SztPort       dstPort;
} SztPeerAssocInd;

typedef struct sztPeerAssocRsp
{
   U32           peerId;
   SztNetAddrLst dstAddrLst;
   SztPort       dstPort;
   CmNetAddr     priDstAddr;
   U16           comProcStrm;
   SztStrmId     locOutStrms;
   SztReqStatus  status;
} SztPeerAssocRsp;
#endif /* SZ_MME */

/*  szt_x_001.main_8: Added for S1 Abort request support by UI */
#ifdef SZTV2
typedef struct _sztAbortS1
{
   TknU32     peerId;
   CmStatus   abortS1Cfm;
   U8         sndAbortFlag;
#ifdef S1SIMAPP
   U8         cause;
#endif
/* Multi eNB support */
#ifdef MULTI_ENB_SUPPORT
   U32 enbId;
#endif
} SztAbortS1;
#endif /* SZTV2 */


/* typedefs for primitives */
typedef S16 (*SztBndReq)       ARGS((
        Pst *pst, 
        SuId suId, 
        SpId spId
        ));

typedef S16 (*SztUbndReq)      ARGS((
        Pst *pst, 
        SpId spId, 
        Reason reason
        ));

typedef S16 (*SztBndCfm)       ARGS((
        Pst *pst, 
        SuId suId, 
        U8 status
        ));

typedef S16 (*SztStatusInd)       ARGS((
        Pst *pst, 
        SuId suId, 
        SztStaInd *sztSta
        ));

typedef S16 (*SztFlowControlInd)  ARGS((
        Pst *pst, 
        SuId suId, 
        SztFlcInd *flcInd
        ));

typedef S16 (*SztErrorInd)       ARGS((
        Pst *pst, 
        SuId suId, 
        SztLclErrInd *sztLclErrInd
        ));

typedef S16 (*SztUDatReq)     ARGS((
        Pst *pst,
        SpId spId, 
        SztUDatEvnt *uDatEvnt
        ));

typedef S16 (*SztUDatInd)     ARGS((
        Pst *pst,
        SuId suId, 
        SztUDatEvnt *uDatEvnt
        ));

typedef S16 (*SztConnReq)     ARGS((
        Pst *pst,
        SpId spId, 
        SztConReq *conReq
        ));

typedef S16 (*SztConnInd)     ARGS((
        Pst *pst,
        SuId suId, 
        SztConInd *conInd
        ));

typedef S16 (*SztConnRsp)     ARGS((
        Pst *pst,
        SpId spId, 
        SztConRsp *conRsp
        ));

typedef S16 (*SztConnCfm)     ARGS((
        Pst *pst,
        SuId suId, 
        SztConCfm *conCfm
        ));

typedef S16 (*SztRelsReq)     ARGS((
        Pst *pst,
        SpId spId, 
        SztRelReq *relReq
        ));

typedef S16 (*SztRelsInd)     ARGS((
        Pst *pst,
        SuId suId, 
        SztRelInd *relInd
        ));

typedef S16 (*SztRelsRsp)     ARGS((
        Pst *pst,
        SpId spId, 
        SztRelRsp *relRsp
        ));

typedef S16 (*SztRelsCfm)     ARGS((
        Pst *pst,
        SuId suId, 
        SztRelCfm *relCfm
        ));

typedef S16 (*SztDatReq)     ARGS((
        Pst *pst,
        SpId spId, 
        SztDatEvntReq *datEvnt
        ));

typedef S16 (*SztDatInd)     ARGS((
        Pst *pst,
        SuId suId, 
        SztDatEvntInd *datEvnt
        ));

typedef S16 (*SztEncDecReq)     ARGS((
        Pst *pst,
        SpId spId, 
        SztEncDecEvnt *sztEncDecEvnt
        ));

typedef S16 (*SztEncDecCfm)     ARGS((
        Pst *pst,
        SuId suId, 
        SztEncDecEvnt *sztEncDecEvnt,
        SztReqStatus *status
        ));

typedef S16 (*SztAudReq)     ARGS((
        Pst *pst,
        SpId spId, 
        SztAudEvnt *audEvnt
        ));

typedef S16 (*SztAudCfm)     ARGS((
        Pst *pst,
        SuId suId, 
        SztAudEvnt *audEvnt
        ));

/*  szt_x_001.main_8: Added for S1 Abort request support by UI */
#ifdef SZTV2
typedef S16 (*SztAbortS1Req)     ARGS((
        Pst *pst,
        SpId spId,
        SztAbortS1 *abortS1
        ));

typedef S16 (*SztAbortS1Cfm)     ARGS((
        Pst *pst,
        SuId suId, 
        SztAbortS1 *abortS1
        ));
#endif /* SZTV2 */        

#ifdef SZ_MME
/* szt_x_001.main_1 for dynamic peer configuration */
typedef S16 (*SztDynamPeerAssocInd) ARGS((
        Pst *pst, 
        SuId suId, 
        SztPeerAssocInd *peerAssocInd 
        ));

typedef S16 (*SztDynamPeerAssocRsp) ARGS((
        Pst *pst, 
        SuId suId, 
        SztPeerAssocRsp *peerAssocRsp
        ));
#endif /* SZ_MME */

/* Pack unpack functions for loose coupling*/
#ifdef LCSZT

/* Primitive packing functions */
EXTERN S16 cmPkS1apPdu ARGS((S1apPdu *param,Buffer *mBuf));
/* szt_x_001.main_6: Added for TC Dec/Enc  */
#ifdef SZTV1
EXTERN S16 cmPkS1apPduIe ARGS((SztEncDecEvnt *param,Buffer *mBuf));
#endif /* SZTV1 */
EXTERN S16 cmPkSztBndReq ARGS((Pst *pst, SuId suId, SpId spId));
EXTERN S16 cmPkSztUbndReq ARGS((Pst *pst, SpId spId, Reason reason));
EXTERN S16 cmPkSztBndCfm ARGS((Pst *pst, SuId suId, U8 status));
EXTERN S16 cmPkSztStaInd ARGS((Pst *pst, SuId suId, SztStaInd *sztSta));
EXTERN S16 cmPkSztFlcInd ARGS((Pst *pst, SuId suId, SztFlcInd *sztSta));
EXTERN S16 cmPkSztLclErrInd ARGS((Pst *pst, SuId suId,
                           SztLclErrInd *sztErrInd));
EXTERN S16 cmPkSztUDatReq ARGS((Pst *pst, SpId spId, SztUDatEvnt *uDatEvnt));
EXTERN S16 cmPkSztUDatInd ARGS((Pst *pst, SuId suId, SztUDatEvnt *uDatEvnt));
EXTERN S16 cmPkSztConReq ARGS((Pst *pst, SpId spId, SztConReq *conReq));
EXTERN S16 cmPkSztConInd ARGS((Pst *pst, SuId suId, SztConInd *conInd));
EXTERN S16 cmPkSztConRsp ARGS((Pst *pst, SpId spId, SztConRsp *conRsp));
EXTERN S16 cmPkSztConCfm ARGS((Pst *pst, SuId suId, SztConCfm *conCfm));
EXTERN S16 cmPkSztRelReq ARGS((Pst *pst, SpId spId, SztRelReq *relReq));
EXTERN S16 cmPkSztRelInd ARGS((Pst *pst, SuId suId, SztRelInd *relInd));
EXTERN S16 cmPkSztRelRsp ARGS((Pst *pst, SpId spId, SztRelRsp *relRsp));
EXTERN S16 cmPkSztRelCfm ARGS((Pst *pst, SuId suId, SztRelCfm *relCfm));
EXTERN S16 cmPkSztDatReq ARGS((Pst *pst, SpId spId, SztDatEvntReq *datEvnt));
EXTERN S16 cmPkSztDatInd ARGS((Pst *pst, SuId suId, SztDatEvntInd *datEvnt));
EXTERN S16 cmPkSztEncDecReq ARGS((Pst *pst, SpId spId,
                                  SztEncDecEvnt *sztEncDecEvnt));
EXTERN S16 cmPkSztEncDecCfm ARGS((Pst *pst, SuId suId,
                                  SztEncDecEvnt *sztEncDecEvnt,
                                  SztReqStatus *status));
EXTERN S16 cmPkSztAudReq ARGS((Pst *pst, SpId spId, SztAudEvnt *audEvnt));
EXTERN S16 cmPkSztAudCfm ARGS((Pst *pst, SuId suId, SztAudEvnt *audEvnt));
EXTERN S16 cmPkSztAudEvnt ARGS(( SztAudEvnt *audEvnt, Buffer *mBuf));
EXTERN S16 cmUnpkSztAudEvnt ARGS(( SztAudEvnt *audEvnt, Buffer *mBuf));

/*  szt_x_001.main_8: Added for S1 Abort request support by UI */
#ifdef SZTV2
EXTERN S16 cmPkSztAbortS1Req ARGS((Pst *pst, SpId spId, SztAbortS1 *abortS1));
EXTERN S16 cmPkSztAbortS1Cfm ARGS((Pst *pst, SuId suId, SztAbortS1 *abortS1));
#endif /* SZTV2 */
#ifdef SZ_MME
/* szt_x_001.main_1 for dynamic peer configuration */
EXTERN S16 cmPkSztPeerAssocInd ARGS((Pst *pst, SuId suId,
                                     SztPeerAssocInd *peerAssocInd));
EXTERN S16 cmPkSztPeerAssocRsp ARGS((Pst *pst, SpId spId,
                                     SztPeerAssocRsp *peerAssocRsp));

EXTERN S16 cmPkSztNetAddrLst   ARGS((SztNetAddrLst *addrLst, Buffer *mBuf));
#endif /* SZ_MME */

/* Primitive unpacking functions */
EXTERN S16 cmUnpkS1apPdu ARGS((S1apPdu *param,Mem *sMem,Buffer *mBuf));
/* szt_x_001.main_6: Added for TC Dec/Enc  */
#ifdef SZTV1
EXTERN S16 cmUnpkS1apPduIe ARGS((SztEncDecEvnt *param,Mem *sMem,Buffer *mBuf));
#endif /* SZTV1 */
EXTERN S16 cmUnpkSztBndReq ARGS((SztBndReq func, Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkSztUbndReq ARGS((SztUbndReq func, Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkSztBndCfm ARGS((SztBndCfm func, Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkSztStaInd ARGS((SztStatusInd func,Pst *pst,Buffer *mBuf));
EXTERN S16 cmUnpkSztFlcInd ARGS((SztFlowControlInd func,Pst *pst,Buffer *mBuf));
EXTERN S16 cmUnpkFlcStaInd ARGS((SztFlowControlInd func,Pst *pst,Buffer *mBuf));
EXTERN S16 cmUnpkSztLclErrInd ARGS((SztErrorInd func, Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkSztUDatReq ARGS((SztUDatReq func,
                                Pst *pst,
                                Buffer *mBuf,
                                Mem *sMem));
EXTERN S16 cmUnpkSztUDatInd ARGS((SztUDatInd func,
                                Pst *pst,
                                Buffer *mBuf,
                                Mem *sMem));
EXTERN S16 cmUnpkSztConReq  ARGS((SztConnReq func,
                                Pst *pst,
                                Buffer *mBuf,
                                Mem *sMem));
EXTERN S16 cmUnpkSztConInd  ARGS((SztConnInd func,
                                Pst *pst,
                                Buffer *mBuf,
                                Mem *sMem));
EXTERN S16 cmUnpkSztConRsp  ARGS((SztConnRsp func,
                                Pst *pst,
                                Buffer *mBuf,
                                Mem *sMem));
EXTERN S16 cmUnpkSztConCfm  ARGS((SztConnCfm func,
                                Pst *pst,
                                Buffer *mBuf,
                                Mem *sMem));
EXTERN S16 cmUnpkSztRelReq  ARGS((SztRelsReq func,
                                Pst *pst,
                                Buffer *mBuf,
                                Mem *sMem));
EXTERN S16 cmUnpkSztRelInd  ARGS((SztRelsInd func,
                                Pst *pst,
                                Buffer *mBuf,
                                Mem *sMem));
EXTERN S16 cmUnpkSztRelRsp  ARGS((SztRelsRsp func,
                                Pst *pst,
                                Buffer *mBuf,
                                Mem *sMem));
EXTERN S16 cmUnpkSztRelCfm  ARGS((SztRelsCfm func,
                                Pst *pst,
                                Buffer *mBuf,
                                Mem *sMem));
EXTERN S16 cmUnpkSztDatReq  ARGS((SztDatReq func,
                                Pst *pst,
                                Buffer *mBuf,
                                Mem *sMem));
EXTERN S16 cmUnpkSztDatInd  ARGS((SztDatInd func,
                                Pst *pst,
                                Buffer *mBuf,
                                Mem *sMem));
EXTERN S16 cmUnpkSztEncDecReq ARGS((SztEncDecReq func,
                                Pst *pst,
                                Buffer *mBuf,
                                Mem *sMem));
EXTERN S16 cmUnpkSztEncDecCfm  ARGS((SztEncDecCfm func,
                                Pst *pst,
                                Buffer *mBuf,
                                Mem *sMem));
EXTERN S16 cmUnpkSztAudReq ARGS((SztAudReq func,
                                 Pst *pst,
                                 Buffer *mBuf,
                                 Mem *sMem));
EXTERN S16 cmUnpkSztAudCfm ARGS((SztAudCfm func, Pst *pst,
                                 Buffer *mBuf,Mem *sMem));
#ifdef SZ_MME
/* szt_x_001.main_1 for dynamic peer configuration */
EXTERN S16 cmUnpkSztPeerAssocInd ARGS((SztDynamPeerAssocInd func, Pst *pst,
                                       Buffer *mBuf, Mem *sMem));
EXTERN S16 cmUnpkSztPeerAssocRsp ARGS((SztDynamPeerAssocRsp func, Pst *pst,
                                       Buffer *mBuf, Mem *sMem));

EXTERN S16 cmUnpkSztNetAddrLst   ARGS((SztNetAddrLst *addrLst, Buffer *mBuf));
#endif /* SZ_MME */
/*  szt_x_001.main_8: Added for S1 Abort request support by UI */
#ifdef SZTV2
EXTERN S16 cmUnpkSztAbortS1Req ARGS((SztAbortS1Req func, Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkSztAbortS1Cfm ARGS((SztAbortS1Cfm func, Pst *pst, Buffer *mBuf));
#endif /* SZTV2 */


#endif /* LCSZT */

/***********************************************************************
             SZT interface primitive definition
 ***********************************************************************/
#ifdef SZ

EXTERN S16 SzUiSztBndReq       ARGS((Pst *pst, SuId suId, SpId spId));
EXTERN S16 SzUiSztUbndReq      ARGS((Pst *pst, SpId spId, Reason reason));
EXTERN S16 SzUiSztBndCfm       ARGS((Pst *pst, SuId suId, U8 status));
EXTERN S16 SzUiSztStaInd       ARGS((Pst *pst, SuId suId, SztStaInd *sztSta));
/* szt_x_001.main_2 Adding Flc Ind */
EXTERN S16 SzUiSztFlcInd       ARGS((Pst *pst, SuId suId, SztFlcInd *flcInd));
EXTERN S16 SzUiSztErrInd       ARGS((Pst *pst, SuId suId,
                                     SztLclErrInd *sztErrInd));
EXTERN S16 SzUiSztUDatReq      ARGS((Pst *pst, SpId spId,
                                     SztUDatEvnt *uDatEvnt));
EXTERN S16 SzUiSztUDatInd      ARGS((Pst *pst, SuId suId,
                                     SztUDatEvnt *uDatEvnt));
EXTERN S16 SzUiSztConReq       ARGS((Pst *pst, SpId spId, SztConReq *conReq));
EXTERN S16 SzUiSztConInd       ARGS((Pst *pst, SuId suId, SztConInd *conInd));
EXTERN S16 SzUiSztConRsp       ARGS((Pst *pst, SpId spId, SztConRsp *conRsp));
EXTERN S16 SzUiSztConCfm       ARGS((Pst *pst, SuId suId, SztConCfm *conCfm));
EXTERN S16 SzUiSztRelReq       ARGS((Pst *pst, SpId spId, SztRelReq *relReq));
EXTERN S16 SzUiSztRelInd       ARGS((Pst *pst, SuId suId, SztRelInd *relInd));
EXTERN S16 SzUiSztRelRsp       ARGS((Pst *pst, SpId spId, SztRelRsp *relRsp));
EXTERN S16 SzUiSztRelCfm       ARGS((Pst *pst, SuId suId, SztRelCfm *relCfm));
EXTERN S16 SzUiSztDatReq       ARGS((Pst *pst, SpId spId,
                                     SztDatEvntReq *datEvnt));
EXTERN S16 SzUiSztDatInd       ARGS((Pst *pst, SuId suId,
                                     SztDatEvntInd *datEvnt));
EXTERN S16 SzUiSztEncDecReq    ARGS((Pst *pst, SpId spId,
                                     SztEncDecEvnt *sztEncDecEvnt));
EXTERN S16 SzUiSztEncDecCfm    ARGS((Pst *pst, SuId suId,
                                     SztEncDecEvnt *encDecEvnt,
                                                   SztReqStatus *status));
EXTERN S16 SzUiSztAudReq       ARGS((Pst *pst, SpId spId, SztAudEvnt *audEvnt));
EXTERN S16 SzUiSztAudCfm       ARGS((Pst *pst, SuId suId, SztAudEvnt *audEvnt));

/*  szt_x_001.main_8: Added for S1 Abort request support by UI */
#ifdef SZTV2
EXTERN S16 SzUiSztAbortS1Req ARGS((Pst *pst, SpId spId, SztAbortS1 *abortS1));
EXTERN S16 SzUiSztAbortS1Cfm ARGS((Pst *pst, SuId suId, SztAbortS1 *abortS1));
#endif /* SZTV2 */

#ifdef SZ_MME
/* szt_x_001.main_1 for dynamic peer configuration */
EXTERN S16 SzUiSztPeerAssocInd ARGS((Pst *pst, SuId suId,
                                     SztPeerAssocInd *peerAssocInd));
EXTERN S16 SzUiSztPeerAssocRsp ARGS((Pst *pst, SpId spId,
                                     SztPeerAssocRsp *peerAssocRsp));
#endif /* SZ_MME */

/* szt_x_001.main_5: New APIs added for encoder-decoder */
#ifdef SZ_ENC_DEC
EXTERN S16 SzUiSztEncReq ARGS((S1apPdu *encPdu, Buffer *mBuf,
                               SztEncDecStatus *status, U8 dbgInfo));
EXTERN S16 SzUiSztDecReq ARGS((S1apPdu *encPdu, Buffer *mBuf,
                               SztEncDecStatus *status, U8 dbgInfo));
EXTERN S16 SzUiSztStsReq ARGS((SztSts *encPdu, U8 action,
                               SztReqStatus *status));
EXTERN S16 SzUiSztInitReq ARGS((Void *initPrams, SztReqStatus *status));
#endif /* SZ_ENC_DEC */

#endif /* SZ */

#ifdef UZ

EXTERN S16 UzLiSztBndReq       ARGS((Pst *pst, SuId suId, SpId spId));
EXTERN S16 UzLiSztUbndReq      ARGS((Pst *pst, SpId spId, Reason reason));
EXTERN S16 UzLiSztBndCfm       ARGS((Pst *pst, SuId suId, U8 status));
EXTERN S16 UzLiSztStaInd       ARGS((Pst *pst, SuId suId, SztStaInd *sztSta));
EXTERN S16 UzLiSztFlcInd       ARGS((Pst *pst, SuId suId, SztFlcInd *flcInd));
EXTERN S16 UzLiSztErrInd       ARGS((Pst *pst, SuId suId,
                                     SztLclErrInd *lclErrInd));
EXTERN S16 UzLiSztUDatReq      ARGS((Pst *pst, SpId spId,
                                     SztUDatEvnt *uDatEvnt));
EXTERN S16 UzLiSztUDatInd      ARGS((Pst *pst, SuId suId,
                                     SztUDatEvnt *uDatEvnt));
EXTERN S16 UzLiSztConReq       ARGS((Pst *pst, SpId spId, SztConReq *conReq));
EXTERN S16 UzLiSztConInd       ARGS((Pst *pst, SuId suId, SztConInd *conInd));
EXTERN S16 UzLiSztConRsp       ARGS((Pst *pst, SpId spId, SztConRsp *conRsp));
EXTERN S16 UzLiSztConCfm       ARGS((Pst *pst, SuId suId, SztConCfm *conCfm));
EXTERN S16 UzLiSztRelReq       ARGS((Pst *pst, SpId spId, SztRelReq *relReq));
EXTERN S16 UzLiSztRelInd       ARGS((Pst *pst, SuId suId, SztRelInd *relInd));
EXTERN S16 UzLiSztRelRsp       ARGS((Pst *pst, SpId spId, SztRelRsp *relRsp));
EXTERN S16 UzLiSztRelCfm       ARGS((Pst *pst, SuId suId, SztRelCfm *relCfm));
EXTERN S16 UzLiSztDatReq       ARGS((Pst *pst, SpId spId,
                                     SztDatEvntReq *datEvnt));
EXTERN S16 UzLiSztDatInd       ARGS((Pst *pst, SuId suId,
                                     SztDatEvntInd *datEvnt));
EXTERN S16 UzLiSztEncDecReq    ARGS((Pst *pst, SpId spId,
                                     SztEncDecEvnt *encDecEvnt));
EXTERN S16 UzLiSztEncDecCfm    ARGS((Pst *pst, SuId suId,
                                     SztEncDecEvnt *encDecEvnt,
                                     SztReqStatus *status));
EXTERN S16 UzLiSztAudReq       ARGS((Pst *pst, SpId spId, SztAudEvnt *audEvnt));
EXTERN S16 UzLiSztAudCfm       ARGS((Pst *pst, SuId suId, SztAudEvnt *audEvnt));
/*  szt_x_001.main_8: Added for S1 Abort request support by UI */
#ifdef SZTV2
EXTERN S16 UzLiSztAbortS1Cfm   ARGS((Pst *pst, SuId suId, SztAbortS1 *abortS1));
EXTERN S16 UzLiSztAbortS1Req   ARGS((Pst *pst, SpId spId, SztAbortS1 *abortS1));
#endif /* SZTV2 */
#ifdef SZ_MME
/* szt_x_001.main_1 for dynamic peer configuration */
EXTERN S16 UzLiSztPeerAssocInd ARGS((Pst *pst, SuId suId,
                                     SztPeerAssocInd *peerAssocInd));
EXTERN S16 UzLiSztPeerAssocRsp ARGS((Pst *pst, SpId spId,
                                     SztPeerAssocRsp *peerAssocRsp));
#endif /* SZ_MME */
#endif /* UZ */

/*#endif*/ /* __SZTX__ */
#ifdef __cplusplus
}
#endif /* extern "C" */
#endif /* __SZTX__ */
/********************************************************************30**

         End of file:     szt.x@@/main/9 - Thu Apr 26 19:39:43 2012

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
/main/1      ---             sn     1. initial release.
/main/1+    szt_x_001.main_1 sn     1. Dynamic peer addition feature added
/main/3     szt_x_001.main_2 ng     1. Updated for S1AP Release 2.1
/main/4     szt_x_001.main_3 hsingh 1. S1AP performance related changes
/main/5     szt_x_001.main_4 ajainx 1. Updated for S1AP Release 2.2.
/main/6     szt_x_001.main_5 pkaX   1. Updated for S1AP Release 3.1.
/main/7     szt_x_001.main_6 va     1. Updated for Transparent Container Dec/Enc
/main/8     szt_x_001.main_7 va     1. Added for S1 Abort request support by UI
/main/9      ---      szt_x_001.main_8 va     1. Updated for S1AP Release 4.1.
$SID$     szt_x_001.main_9 akaranth 1. support for Source RNC to Target RNC.
*********************************************************************91*/
