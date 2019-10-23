

/**********************************************************************

     Name:     ESM 
  
     Type:     C include file
  
     Desc:     Defines required by LTE CNE ESM

     File:     cm_esm.x

     Sid:      cm_esm.x@@/main/4 - Thu Jul  5 10:53:31 2012

     Prg:      rk

**********************************************************************/

/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*      
*
*/


#ifndef __ESMX__
#define __ESMX__

#include "ue_esm.h"

#ifdef __cplusplus
EXTERN "C" {
#endif /* __cplusplus */

/* ESM message index */
typedef enum cmEsmMsgIndx
{
   CM_ESM_EVNT_ACTI_DEF_BEAR_REQ = 0,
   CM_ESM_EVNT_ACTI_DEF_BEAR_ACC,
   CM_ESM_EVNT_ACTI_DEF_BEAR_REJ,
   CM_ESM_EVNT_ACTI_DED_BEAR_REQ,
   CM_ESM_EVNT_ACTI_DED_BEAR_ACC,
   CM_ESM_EVNT_ACTI_DED_BEAR_REJ,
   CM_ESM_EVNT_MODI_BEAR_CTXT_REQ,
   CM_ESM_EVNT_MODI_BEAR_CTXT_ACC,
   CM_ESM_EVNT_MODI_BEAR_CTXT_REJ,
   CM_ESM_EVNT_DEACT_BEAR_CTXT_REQ,
   CM_ESM_EVNT_DEACT_BEAR_CTXT_ACC,
   CM_ESM_EVNT_PDN_CONN_REQ,
   CM_ESM_EVNT_PDN_CONN_REJ,
   CM_ESM_EVNT_PDN_DISCONN_REQ,
   CM_ESM_EVNT_PDN_DISCONN_REJ,
   CM_ESM_EVNT_BEAR_RES_ALLOC_REQ,
   CM_ESM_EVNT_BEAR_RES_ALLOC_REJ,
   CM_ESM_EVNT_BEAR_RES_MODI_REQ,
   CM_ESM_EVNT_BEAR_RES_MODI_REJ,
   CM_ESM_EVNT_ESM_INFO_REQ,
   CM_ESM_EVNT_ESM_INFO_RES,
   CM_ESM_EVNT_ESM_STATUS,
   CM_ESM_MAX_MSG_TYPE
}CmEsmMsgIndx;

/* cm_esm_x_001.main_1: TFT Operation Code */
typedef enum cmEsmTftOpCode
{
   CM_ESM_TFT_OPCODE_SPARE = 0,
   CM_ESM_TFT_OPCODE_NEWTFT ,
   CM_ESM_TFT_OPCODE_DELTFT ,
   CM_ESM_TFT_OPCODE_ADD_FILTER,
   CM_ESM_TFT_OPCODE_REP_FILTER,
   CM_ESM_TFT_OPCODE_DEL_FILTER,
   CM_ESM_TFT_OPCODE_NOTFTOP ,
   CM_ESM_TFT_OPCODE_RESERVED 
}CmEsmTftOpCode;

/* TFT Parameter Type */
typedef enum cmEsmTftParamType
{
   CM_ESM_TFT_PARAM_AUTH_TOKEN= 0x1,
   CM_ESM_TFT_PARAM_FLOW_ID,
   CM_ESM_TFT_PARAM_FILTER_ID
}CmEsmTftParamType;


/*******************CmEdmInit***************************************************
 Structures and definations for ESM IEs
**********************************************************************/
typedef U8 CmEsmProtDis;            /* protocol discriminator */
typedef U8 CmEsmBearerId;           /* EPS bearer identity */
typedef U8 CmEsmLinkedBearId;       /* cm_esm_x_001.main_1: EPS bearer identity */
typedef U8 CmEsmProcTxnId;          /* Procedure transaction identity */
typedef U8 CmEsmMsgType;            /* Message type */
typedef U8 CmEsmPres;               /* presence indicator */

/* EPS QoS */
typedef struct cmEsmEpsQos
{
   CmEsmPres pres;

   U8 lenQosCont;          /* Length of EPS quality of service contents */
   U8 qci;                 /* QCI */
   U8 maxBitRateUL;        /* Maximum bit rate for uplink */
   U8 maxBitRateDL;        /* Maximum bit rate for downlink */
   U8 guaraBitRateUL;      /* Guaranteed bit rate for uplink */
   U8 guaraBitRateDL;      /* Guaranteed bit rate for downlink */
   U8 maxBitRateULExt;     /* Maximum bit rate for uplink (extended) */
   U8 maxBitRateDLExt;     /* Maximum bit rate for downlink (extended) */
   U8 guaraBitRateULExt;   /* Guaranteed bit rate for uplink (extended) */
   U8 guaraBitRateDLExt;   /* Guaranteed bit rate for downlink (extended) */

}CmEsmEpsQos;

#ifndef CM_MME
/* cm_esm_x_001.main_1: Add all the variabled required for TFT encoding/decoding */
/*Ipv4 Remote Addr type */
typedef struct cmEsmTftPfIpv4
{
   CmEsmPres   pres;
   U8          ip4[CM_ESM_IPV4_SIZE];
}CmEsmTftPfIpv4;

/*Ipv6 Remote Addr type */
typedef struct cmEsmTftPfIpv6
{
   CmEsmPres   pres;
   U8          ip6[CM_ESM_IPV6_SIZE];
}CmEsmTftPfIpv6;

typedef struct cmEsmTftProtIden
{
   CmEsmPres    pres;
   U8           protType;  
}CmEsmTftProtIden;


typedef struct cmEsmTftPort
{
   CmEsmPres    pres;
   U16          port;  
}CmEsmTftPort;

typedef struct cmEsmTftPortRange
{
   CmEsmPres    pres;
   U16          rangeLow;  
   U16          rangeHigh;  
}CmEsmTftPortRange;

typedef struct cmEsmTftSecParam
{
   CmEsmPres   pres;
   U8          params[CM_ESM_IP_SEC_SIZE];  
}CmEsmTftSecParam;

typedef struct cmEsmTftTos
{
   CmEsmPres   pres;
   U8          tos;  
   U8          mask;  
}CmEsmTftTos;

typedef struct cmEsmTftIpv6FlowLbl
{
   CmEsmPres   pres;
   U8          buf[CM_ESM_IPV6_FLOW_LABEL_SIZE];  
}CmEsmTftIpv6FlowLbl;

typedef struct cmEsmTftPf
{
   CmEsmPres            pres;         /* present or Not*/ 
   U8                   id;           /* Packet Filter idenntifier*/   
   U8                   dir;          /* Direction */ 
   U8                   preced;       /* Precedence */
   U32                  ipv4Mask;     /* Ipv4 mask to indicate the range of IPs*/
   U8                  len;          /* Length */
   CmEsmTftPfIpv4       ipv4;         /* Ipv4 Address */
   CmEsmTftPfIpv6       ipv6;         /* Ipv6 Address */
   CmEsmTftProtIden     protId;       /* Protocol Identifier */
   CmEsmTftPort         localPort;    /* Local  Port Idemtifier */
   CmEsmTftPort         remotePort;   /* Remote Port Idemtifier */
   CmEsmTftPortRange    locPortRange; /* Port Range */
   CmEsmTftPortRange    remPortRange; /* Port Range */
   CmEsmTftSecParam     secParam;     /* Security  Param */
   CmEsmTftTos          tos;          /* Type of Service  Param */
   CmEsmTftIpv6FlowLbl  flowLabel;    /* Flow Label   */
}CmEsmTftPf;

typedef struct cmEsmTftParam
{
   CmEsmTftParamType      paramType;
   U8                     len;
   U8                     buf [CM_ESM_TFT_MAX_PARAM_BUF]; 
}CmEsmTftParam;
#endif

typedef struct cmEsmTft
{
   CmEsmPres pres;                                     /* Present or not */  
   U8             len;  
#ifdef CM_MME
   U8              buf [CM_ESM_TFT_MAX_TFT_BUF]; 
#else
   CmEsmTftOpCode  opCode;                             /* TFT Operation Code*/
   U8    eBit ;                                        /* param List presnt */
   U8    noOfPfs;                                      /* No  Of packet Filters */
   U8    noOfParams;                                   /* No Of packet Filters */
   CmEsmTftPf  pfList[CM_ESM_MAX_PKT_FILTERS];  /* Pf List */
   CmEsmTftParam      params[CM_ESM_MAX_PARAMS];       /* Tft Params */  
#endif
}CmEsmTft;

/* Access point name */
typedef struct cmEsmAccessPtName
{
   CmEsmPres pres;
   U8 len;     /* Length of access point name contents */
   U8 apn[CM_ESM_MAX_LEN_ACCESS_PTNAME];/* Access point name value */

}CmEsmAccessPtName;

/* PDN address */
typedef struct cmEsmPdnAdd
{
   CmEsmPres pres;

   U8 len;     /* Length of PDN address contents */
   U8 pdnType; /* PDN type value. bit 1 to 3 bits (oct 3) */
   U8 addrInfo[CM_ESM_MAX_LEN_PDN_ADDRESS]; /* PDN address information */
}CmEsmPdnAdd;

/* Transaction Identifier */
typedef struct cmEsmTxnId
{
   CmEsmPres pres;

   U8 len;        /* Length of Linked TI IE */
   U8 tiVal;      /* TI value occupy bits 5 - 7 of the first oct */
   U8 tiFlag;     /* TI flag occupy bit 8 of the first oct */
   U8 tie;        /* TIE occupy bits 1 - 7 of the second oct */
   U8 tiExt;      /* TI extended occupy bit 8 of the second oct */

}CmEsmTxnId;

/* ESM QoS */
typedef struct cmEsmQoS
{
   CmEsmPres pres;

   U8 lenQosCont;       /* Length of quality of service IE 2nd oct */
   U8 relClass;         /* Reliability class bits 1-3 of 3rd oct */
   U8 delayClass;       /* Delay class bits 4-6 of 3rd oct */
   U8 precClass;        /* Precedence class bits 1-3 of 4th oct */
   U8 peakTp;           /* Peak throughput bits 5-8 of 4th oct */
   U8 meanTp;           /* Mean throughput bits 1-5 of 5th oct */
   U8 deliveryErrSdu;   /* Delivery of erroneous SDU bits 1-3 of 6th oct */
   U8 deliveryOrder;    /* Delivery order bits 4-5 of 6th oct */
   U8 trafficClass;     /* Traffic Class bits 6-8 of 6th oct */
   U8 maxSdu;           /* Maximum SDU size 7th oct */
   U8 maxBitRateUL;     /* Maximum bit rate for uplink 8th oct */
   U8 maxBitRateDL;     /* Maximum bit rate for downlink 9th oct */
   U8 sduErrRatio;      /* SDU error ratio bits 1-4 of 10th oct */
   U8 residualBer;      /* Residual BER bits 5-8 of 10th oct */
   U8 trafHandPrio;     /* Traffic Handling priority bits 1-2 of 11th oct */
   U8 transferDelay;    /* Transfer delay bits 3-8 of 11th oct */
   U8 guaraBitRateUL;   /* Guaranteed bit rate for uplink 12th oct */
   U8 guaraBitRateDL;   /* Guaranteed bit rate for downlink 13th oct */
   U8 srcStatDesc;      /* Src Stat Descriptor bits 1-4 of 14th oct */
   U8 signalInd;        /* Signalling Indication bit 5 of 14th oct */
   U8 maxBitRateDLExt;  /* Maximum bit rate for downlink(ext) 15th oct */
   U8 guaraBitRateDLExt;/* Guaranteed bit rate for downlink(ext) 16th oct */
   U8 maxBitRateULExt;  /* Maximum bit rate for uplink(ext) 17th oct */
   U8 guaraBitRateULExt;/* Guaranteed bit rate for uplink(ext) 18th oct */

}CmEsmQoS;


/* LLC service access point identifier */
typedef struct cmEsmLLCSerPt
{
   CmEsmPres pres;

   U8 ieVal;   /* LLC SAPI value */
}CmEsmLLCSerPt;

/* Radio priority */
typedef struct cmEsmRadioPrio
{
   CmEsmPres pres;

   U8 ieVal;      /* Radio priority level value bits 1-3 of 1st oct */
}CmEsmRadioPrio;

/* Packet Flow Identifier */
typedef struct cmEsmPktFlowId
{
   CmEsmPres pres;

   U8 len;     /* Length of Packet Flow Identifier IE */
   U8 ieVal;   /* Packet Flow Identifier value bits 1-7 of 3rd oct */
}CmEsmPktFlowId;

/* APN aggregate maximum bit rate */
typedef struct cmEsmApnAmbr
{
   CmEsmPres pres;

   U8 len;     /* Length of APN aggregate maximum bit rate contents */
   U8 dl;      /* APN-AMBR for downlink */
   U8 ul;      /* APN-AMBR for uplink */
   U8 dlExt;   /* APN-AMBR for downlink (extended) */
   U8 ulExt;   /* APN-AMBR for uplink (extended) */
   U8 dlExt2;  /* APN-AMBR for downlink (extended-2) */
   U8 ulExt2;  /* APN-AMBR for uplink (extended-2) */

}CmEsmApnAmbr;

/* ESM cause */
typedef struct cmEsmCause
{
   CmEsmPres pres;

   U8 val;     /* Cause value */
}CmEsmCause;

/* Protocol configuration options */
typedef struct cmEsmProtCfgOpt
{
   CmEsmPres pres;

   U8 len;        /* Length of protocol config. options contents */
   U8 cfgProt;    /* configuration protocol. bits 1-3 of 3rd oct */
   U8 ext;        /* extension. bit 8 of 3rd oct */
   U8 numProtId;  /* Number of Protocol configurations */
   U8 numContId;  /* Number of Containers */
   
   struct pId
   {
      U16 pid;       /* Protocol ID */
      U8 len;        /* Length of protocol ID contents */
      U8 val[CM_ESM_MAX_LEN_PROT_CFG_OPT];   /* Protocol ID contents */
   }p[CM_ESM_MAX_PROTO_ID];

   struct cId
   {
      U16 cid;       /* Container ID */
      U8 len;        /* Length of ContainerID contents */
      U8 val[CM_ESM_MAX_LEN_PROT_CFG_OPT];   /* ContainerID contents */
   }c[CM_ESM_MAX_CONT_ID];
}CmEsmProtCfgOpt;

/* Request type */
typedef struct cmEsmReqType
{
   CmEsmPres pres;

   U8 val;        /* Request type value. bits 1-3 of 1st oct */
}CmEsmReqType;

/* PDN type */
typedef struct cmEsmPdnType
{
   CmEsmPres pres;

   U8 val;        /* PDN type value. bits 1-3 of 1st oct */
}CmEsmPdnType;

/* ESM information transfer flag */
typedef struct cmEsmInfoTranFlg
{
   CmEsmPres pres;

   U8 val;  /* EIT value. bit 1 of 1st oct */
}CmEsmInfoTranFlg;


/**********************************************************************
 Strucures for ESM messages
**********************************************************************/

/* Activate default EPS bearer context accept message */
typedef struct cmEsmActDefBearCtxtAcc
{
   CmEsmProtCfgOpt   protCfgOpt;
}CmEsmActDefBearCtxtAcc;

/* Activate dedicated EPS bearer context accept message */
typedef struct cmEsmActDedBearCtxtAcc
{
   CmEsmProtCfgOpt   protCfgOpt;
}CmEsmActDedBearCtxtAcc;
/* Activate default EPS bearer context reject message */
typedef struct cmEsmActDefBearCtxtRej
{
   CmEsmCause        cause;
   CmEsmProtCfgOpt   protCfgOpt;
}CmEsmActDefBearCtxtRej;

/* cm_esm_x_001.main_1: Activate dedicated EPS bearer context reject message */
typedef struct cmEsmActDedBearCtxtRej
{
   CmEsmCause        cause;
   CmEsmProtCfgOpt   protCfgOpt;
}CmEsmActDedBearCtxtRej;

/* Bearer Resource Allocation  reject message */
typedef struct  cmEsmdBearResAllocRej
{
   CmEsmCause        cause;
   CmEsmProtCfgOpt   protCfgOpt;
} CmEsmdBearResAllocRej;

/* Activate default EPS bearer context request */
typedef struct cmEsmActDefBearCtxtReq
{
   CmEsmEpsQos       epsQos;
   CmEsmAccessPtName apn;
   CmEsmPdnAdd       pAddr;
   CmEsmTxnId        txnId;
   CmEsmQoS          qos;
   CmEsmLLCSerPt     llc;
   CmEsmRadioPrio    radioPrio;
   CmEsmPktFlowId    pktFlowId;
   CmEsmApnAmbr      apnAmbr;
   CmEsmCause        cause;
   CmEsmProtCfgOpt   protCfgOpt;
}CmEsmActDefBearCtxtReq;

/* cm_esm_x_001.main_1: Activate dedicated EPS bearer context request */
typedef struct cmEsmActDedBearCtxtReq
{
   CmEsmBearerId     bearerId;
   CmEsmLinkedBearId lnkBearerId;  
   CmEsmEpsQos       epsQos;
   CmEsmTft          tft;
   CmEsmTxnId        txnId;
   CmEsmQoS          qos;
   CmEsmLLCSerPt     llc;
   CmEsmRadioPrio    radioPrio;
   CmEsmPktFlowId    pktFlowId;
   CmEsmProtCfgOpt   protCfgOpt;
}CmEsmActDedBearCtxtReq;

/* Activate dedicated EPS bearer context request */
typedef struct cmEsmBearResAllocReq
{
   CmEsmBearerId     bearerId;
   CmEsmLinkedBearId lnkBearerId;  
   CmEsmTxnId        txnId;
   CmEsmEpsQos          epsQos;
   /* Agregate TFT is equivalen to the regular TFT that we fill. Only that the
    * bearer Identifier to be filled as 0 */
   CmEsmTft             tft;
   CmEsmProtCfgOpt      protCfgOpt;
}CmEsmBearResAllocReq;

/* PDN connectivity reject */
typedef struct cmEsmPdnConnRej
{
   CmEsmCause        cause;
   CmEsmProtCfgOpt   protCfgOpt;
}CmEsmPdnConnRej;

/* PDN connectivity request */
typedef struct cmEsmPdnConnReq
{
   CmEsmReqType      reqType;
   CmEsmPdnType      pdnType;
   CmEsmInfoTranFlg  infoTransFlg;
   CmEsmAccessPtName apn;
   CmEsmProtCfgOpt   protCfgOpt;
}CmEsmPdnConnReq;
/*  cm_esm_x_001.main_2: Added deactivate EPS bearer context request */
typedef struct cmEsmDeActBearCtxtReq
{
   CmEsmCause         cause;
   CmEsmProtCfgOpt    protCfgOpt;
}CmEsmDeActBearCtxtReq;
typedef struct cmEsmBearResModRej
{
   CmEsmCause         cause;
   CmEsmProtCfgOpt    protCfgOpt;
}CmEsmBearResModRej;
/*  DeActivate  EPS bearer context accept */
typedef struct cmEsmDeActBearCtxtAcc
{
   CmEsmProtCfgOpt    protCfgOpt;
}CmEsmDeActBearCtxtAcc;
/* Bearer resource  modification request */
typedef struct cmEsmBearResModReq
{
   CmEsmBearerId      bearerId;
   CmEsmLinkedBearId  lnkBearerId;
   CmEsmTxnId         txnId;
   CmEsmTft           tft;
   CmEsmEpsQos        epsQos;
   CmEsmCause         cause;
   CmEsmProtCfgOpt    protCfgOpt;

}CmEsmBearResModReq;

/* Esm information request */
typedef struct cmEsmInfoReq
{
   U8 ueId;
}CmEsmInfoReq;

/* Esm information response */
typedef struct cmEsmInfoResp
{
   CmEsmAccessPtName apn;
   CmEsmProtCfgOpt   protCfgOpt;
} CmEsmInfoResp;

/* ESM Message */
/* cm_esm_x_001.main_2: Updated cmEsmMsg structure */
typedef struct cmEsmMsg
{
   CmEsmProtDis      protDisc;   /* Protocol discriminator */
   CmEsmBearerId     bearerId;   /* EPS bearer identity */
   CmEsmProcTxnId    prTxnId;    /* Procedure transaction identity */
   CmEsmMsgType      msgType;    /* message type */
   union
   {
      CmEsmActDefBearCtxtReq  actReq;
      CmEsmActDedBearCtxtReq  actDedBearReq;
      CmEsmActDefBearCtxtAcc  actAcc;
      CmEsmActDedBearCtxtAcc  actDedBearAcc;
      CmEsmActDefBearCtxtRej  actRej;
      CmEsmActDedBearCtxtRej  actDedBearRej;
      CmEsmBearResAllocReq    bearAllocReq;
      CmEsmdBearResAllocRej   bearAllocRej;
      CmEsmPdnConnReq         conReq;
      CmEsmPdnConnRej         conRej;
      CmEsmDeActBearCtxtReq   deactBearReq;
      CmEsmDeActBearCtxtAcc   deactBearAcc;
      CmEsmBearResModReq      bearModReq;
      CmEsmBearResModRej      bearModRej;
      CmEsmInfoReq            infoReq;
      CmEsmInfoResp           esmInfoResp;
   }u;
}CmEsmMsg;


/* Typedefs for function pointers */
typedef S16 (*CondFuncPtr) ARGS ((CmEsmMsg *pdu));
typedef S16 (*DecFunctPtr) ARGS ((U8* buf, U32 *indx, CmEsmMsg *msg, U32 ieLen));
typedef S16 (*EncFunctPtr) ARGS ((U8* buf, U32 *indx, CmEsmMsg *msg, U32 *ieLen));

/**********************************************************************
   It contains all the info related to an IE. A message shall contain a series of IEs in this format. 
   All the messages shall be populated with the information of the IEs which are present in those messages. 
   The codec fetches this info for encoding and decoding. It contains,
   -# iei : IE Identifier which is a local hash define
   -# presType : Says whether this IE is mandatory/optional/conditional
   -# format : Says whether the IE is in the format of T/V/TV/LV/TLV
   -# length : Specifies the length value field in bits for IE.
   -# cFunc : Function pointer that checks for the condition for a conditional IE.
   -# decFunc : Function pointer that decodes the IE.
   -# encFunc : Function pointer that encodes the IE.
   -# lastIE : If its the last IE in message set to TRUE.

**********************************************************************/
typedef struct cmEsmEdmMsgFormat
{
   U8 iei;      /* Specifies the identifier as local hash define
                 * for the IE */
   U8 presType; /* Indicates Presence Type
                 *    1. EDM_PRES_MANDATORY   - IE is mandatory
                 *    2. EDM_PRES_OPTIONAL    - IE is optional
                 *    3. EDM_PRES_CONDITIONAL - IE is conditional
                 */
   U8 format;    /* Indicates the format of IE
                  *   1. EDM_FMTV   - Value
                  *   2. EDM_FMTTV  - Tag+Value
                  *   3. EDM_FMTTLV - Tag+Length+Value
                  *   4. EDM_FMTT   - Tag
                  *   5. EDM_FMTLV  - Length+Value
                  */
   Bool lastIE;  /* If its the last IE in message set to TRUE */
   U32 length;   /* Specifies the length in bits for IE that have following
                  * format EDM_FMTV, EDM_FMTTV. For rest it is ZERO.
                  */

   CondFuncPtr cFunc; /* Function pointer that check for the condition
                       * associated with IE in this message. Applicable
                       * only for IE's with presType as EDM_PRES_CONDITIONAL
                       */

   EncFunctPtr encFunc; /* Function pointer that encodes the IE */
   DecFunctPtr decFunc; /* Function pointer that decodes the IE */

} CmEsmEdmMsgFormat;


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ESMX__ */


/**********************************************************************
  
         End of file:     cm_esm.x@@/main/4 - Thu Jul  5 10:53:31 2012
   
**********************************************************************/

/**********************************************************************
        Revision History:

**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      rk              1. LTE-CNE Initial Release.
/main/2      ---      cm_esm_x_001.main_1   rk    1. Updated for eNodeB 2.1 release.
/main/3      ---        cm_esm_x_001.main_2  ragrawal 1. Added deactivate EPS 
                                                       bearer context request. 
                                                    2. Updated cmEsmMsg structure.
/main/4      ---      cm_esm_x_001.main_3 akaranth           1. Added security feature enhancement.
*********************************************************************91*/
