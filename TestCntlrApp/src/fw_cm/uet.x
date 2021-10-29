/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

/*******************************************************************************

     Name:   Ue Application

     Type:   C Header file

     Desc:   Difined used by the Ue Interface

     File:   ue_primitives.x

     Sid:


*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif   /* __cplusplus  */

#define UE_IMSI_LENGTH 15
#define UE_IMEISV_LENGTH 16
#define CM_EMM_MAX_MOBILE_ID_DIGS 15
#define MAX_APN_LEN 50
#define OP_KEY_LEN 16
#define SHARED_KEY_LEN 16
#define EVTUEMSGREQ 0
#define UE_ESM_MAX_LEN_ACCESS_PTNAME 100
#define UE_ESM_MAX_LEN_PDN_ADDRESS 13
#define EVTUEMSGRSP 1
#define UE_ESM_MAX_LEN_ACCESS_PTNAME 100
#define UE_ESM_MAX_LEN_PDN_ADDRESS 13
#define UE_APP_KASME_KEY 32
#define UE_APP_NAS_ENC_KEY 16
#define UE_APP_NAS_INT_KEY 16

#define UE_ESM_MAX_LEN_PROT_CFG_OPT 247
#define UE_ESM_MAX_PROTO_ID 4
#define UE_ESM_MAX_CONT_ID 10

#define CM_ESM_IPV4_SIZE   4
#define CM_ESM_IPV6_SIZE 16
#define CM_ESM_IP_SEC_SIZE  4
#define CM_ESM_IPV6_FLOW_LABEL_SIZE 3
#define CM_ESM_TFT_MAX_PARAM_BUF 10
#define CM_ESM_MAX_PKT_FILTERS 10
#define CM_ESM_TFT_MAX_TFT_BUF 50
#define CM_ESM_MAX_PARAMS   10

typedef enum
{
   XOR_TYPE = 0,
   MILENAGE_TYPE
}AuthType_e;

typedef enum
{
   AES_TYPE = 1,
   SNOW3G_TYPE
}AlgoType_e;

/* UE Network capability */
typedef struct _ueEmmNwCap
{
   U8 len;

   U8 eea7;
   U8 eea6;
   U8 eea5;
   U8 eea4;
   U8 eea3;
   U8 eea2_128;
   U8 eea1_128;
   U8 eea0;

   U8 eia7;
   U8 eia6;
   U8 eia5;
   U8 eia4;
   U8 eia3;
   U8 eia2_128;
   U8 eia1_128;
   U8 eia0;

   U8 uea7;
   U8 uea6;
   U8 uea5;
   U8 uea4;
   U8 uea3;
   U8 uea2;
   U8 uea1;
   U8 uea0;

   U8 uia7;
   U8 uia6;
   U8 uia5;
   U8 uia4;
   U8 uia3;
   U8 uia2;
   U8 uia1;
   U8 ucs2;

   U8 vcc_1xsr;

}UeEmmNwCap;

typedef struct _ueUetErrInd
{
   U32            msgType;
   U32            errCode;
   U32            ueId[UE_IMSI_LENGTH];
}UeUetErrInd;

typedef struct _ueUetAppCfReq
{
   U32 trfGenIPAddr;      /*IP address of eth port connected to traffic
                             generator*/
   U8 NASProcGuardTimer;   /*timer value*/
   U8 numOfUE;             /*number of ues to simulate*/
}UeUetAppCfReq;

typedef struct _ueUetAppCfgCompInd
{
  U32 ueId;
  U8 cfgStatus;
  U8 cause;
}UeUetAppCfgCompInd;

typedef struct _ueUetCfgReq
{
   U32 ueId;       /*ue identity*/
   U8 imsiLen;     /* len of IMSi inclusive of MCC+MNC+MSIN */
   U8 imsi[15];       /*Mobile subscriber identity*/
   U8 imei[16];       /*Mobile equipment identity*/
   U8 NASCyphCfg;          /*eea0, eea1, eea2*/
   U8 NASIntProtCfg;       /*eia1, eia2*/
   AlgoType_e algoType;   /*Identifies the sucurity alogoritm supported*/
   U32 opId;      /*operator identity*/
   AuthType_e authType;   /*Auth type- XOR, Milenage*/
   UeEmmNwCap ueNwCap;   /*ue network capability*/
   U32 opKey[OP_KEY_LEN];
   U32 sharedKey[SHARED_KEY_LEN];
   U8 srvPlmn[6];
   U16 radCapIndRrcPdulen;
   U8  *radCapIndRrcPdu;
}UeUetCfgReq;

typedef struct _ueUetCfgCompInd
{
  U32 ueId;
  U8 cfgStatus;
  U8 cause;
}UeUetCfgCompInd;

typedef enum _ueMsgTypes
{
   UE_APP_CONFIG_REQ_TYPE,
   UE_CONFIG_REQ_TYPE,
   UE_APP_CONFIG_COMPLETE_TYPE,
   UE_CONFIG_COMPLETE_TYPE,
   UE_ATTACH_REQ_TYPE,
   UE_IDENTITY_REQ_IND_TYPE,
   UE_IDENTITY_RES_TYPE,
   UE_AUTH_REQ_IND_TYPE,
   UE_AUTH_RES_TYPE,
   UE_SEC_MOD_CMD_IND_TYPE,
   UE_SEC_MOD_CMP_TYPE,
   UE_SEC_MOD_REJ_TYPE,
   UE_ATTACH_ACCEPT_IND_TYPE,
   UE_ATTACH_COMPLETE_TYPE,
   UE_ATTACH_FAIL_TYPE,
   UE_DETACH_REQUEST_TYPE,
   UE_NW_INIT_DETACH_REQUEST_TYPE,
   UE_DETACH_ACCEPT_IND_TYPE,
   UE_TRIG_DETACH_ACCEPT_TYPE,
   UE_TAU_REQUEST_TYPE,
   UE_TAU_COMPLETE_TYPE,
   UE_TAU_REJECT_TYPE,
   UE_TAU_ACCEPT_TYPE,
   UE_ATTACH_REJ_TYPE,
   UE_SERVICE_REQUEST_TYPE,
   UE_SERVICE_REJ_TYPE,
   UE_CNTXT_REL_REQ_TYPE,
   UE_PDN_CON_REQ_TYPE,
   UE_PDN_CON_RSP_TYPE,
   UE_PAGING_MSG_TYPE,
   UE_RAD_CAP_UPD_TYPE,
   UE_FLUSH_TYPE,
   UE_BEAR_RES_ALLOC_REQ,
   UE_EPS_DED_BER_REQ,
   UE_EPS_DED_BER_ACC,
   UE_EPS_DED_BER_REJ,
   UE_ERAB_REL_IND,
   UE_EMM_INFORMATION_TYPE,
   UE_AUTH_REJ_IND_TYPE,
   UE_EMM_STATUS_TYPE,
   UE_EPS_DEFAULT_BER_REJ,
   UE_ESM_INFORMATION_REQ_TYPE,
   UE_ESM_INFORMATION_RSP_TYPE,
   UE_EPS_DEACTIVATE_BER_REQ,
   UE_EPS_DEACTIVATE_BER_ACC,
   UE_PDN_DISCONNECT_REQ_TYPE,
   UE_PDN_DISCONNECT_REJ_TYPE,
   UE_ERAB_SETUP_REQ_FAILED_FOR_ERABS,
   UE_AUTH_FAILURE_TYPE,
   UE_ICMPV6_ROUTER_ADV_TYPE,
   UE_STANDALONE_DEFAULT_EPS_BER_REJ,
   UE_DROP_ACT_DEFAULT_EPS_BER_CTXT_REQ,
}UeMsgTypes;

typedef struct _ueEmmEpsAtchType
{
   U8 type;
}UeEmmEpsAtchType;

typedef struct cmLai
{
   U8 mcc[3];
   U8 mnc[3];
   U16 lac;
}LAI;

typedef struct CmEmmPlmnId
{
   U8 mcc[3];
   U8 mnc[3];
}cmEmmPlmnId;

typedef struct _ueEmmOldGuti
{
   U8 gutiId[CM_EMM_MAX_MOBILE_ID_DIGS];
}UeEmmOldGuti;

/* GUTI */
typedef struct _guti
{
   U8 mcc[3];
   U8 mnc[3];
   U16 mmeGrpId;
   U8 mmeCode;
   U32 mTMSI;
}Guti;

typedef struct _ueEmmLastTai
{
   U8 mcc[3];
   U8 mnc[3];
   U16 tac;
}UeEmmLastTai;

typedef struct _ueEmmNasPdnApn
{
   U8 len;
   U8 apn[MAX_APN_LEN];
}UeEmmNasPdnApn;

typedef struct _ueEmmNasAddUpdType
{
   Bool pres;
   U8 type;
}UeEmmNasAddUpdType;

/* Protocol configuration options */
typedef struct _ueEsmProtCfgOpt
{
   U8 pres;

   U8 len;        /* Length of protocol config. options contents */
   U8 cfgProt;    /* configuration protocol. bits 1-3 of 3rd oct */
   U8 ext;        /* extension. bit 8 of 3rd oct */
   U8 numProtId;  /* Number of Protocol configurations */
   U8 numContId;  /* Number of Containers */

   struct uepId
   {
      U16 pid;       /* Protocol ID */
      U8 len;        /* Length of protocol ID contents */
      U8 val[UE_ESM_MAX_LEN_PROT_CFG_OPT];   /* Protocol ID contents */
   }p[UE_ESM_MAX_PROTO_ID];

   struct uecId
   {
      U16 cid;       /* Container ID */
      U8 len;        /* Length of ContainerID contents */
      U8 val[UE_ESM_MAX_LEN_PROT_CFG_OPT];   /* ContainerID contents */
   }c[UE_ESM_MAX_CONT_ID];
}UeEsmProtCfgOpt;

typedef struct _ueEmmDrxPrm
{
   U8 pres;
   U16 spltPGCycle;
   U8 nonDrxTmr;
   U8 spltOnCcch;
   union
   {
      U8 drxVal;              /* in S1 mode " DRX value" */
      U8 cnSpDrxCyclLenCoeff; /* in Iu mode "CN specific DRX cycle length" */
   } u;
}UeEmmDrxPrm;

typedef struct _ueUetAttachReq
{
 /* UeId, Attach type, Old GUTI, Last TAI,PDN type,
PDN APN */
   U32 ueId;
   U8 mIdType;
   U8 useOldSecCtxt;
   U32 pdnType;
   UeEmmEpsAtchType epsAtchType;
   Bool gutiMI_pres;
   Guti gutiMI;
   Guti oldGuti;
   U8 imsi_len;
   U8 imsi[15];
   UeEmmLastTai ueLastTai;
   UeEmmNasPdnApn nasPdnApn;
   UeEmmNasAddUpdType addUpdType;
   UeEsmProtCfgOpt protCfgOpt;
   UeEmmDrxPrm   drxParm;
   Bool eti; /*Esm Information Transfer Flag*/
}UeUetAttachReq;

typedef struct _ueUetPdnConReq {
  U32 ueId;
  U32 pdnType;
  UeEmmNasPdnApn nasPdnApn;
  U8 reqType;
  UeEsmProtCfgOpt protCfgOpt;
} UeUetPdnConReq;

typedef struct _uePdnRejectInfo
{
 U8 esmCause;
 U8 epsBearerId;
}UePdnRejectInfo;

typedef struct _ueUetAttachRej
{
   U32 ueId;
   U8 cause;
}UeUetAttachRej;

typedef struct _ueUetTauReject
{
   U32 ueId;
   U8 cause;
}UeUetTauReject;

typedef struct _ueUetIdentReqInd
{
   U32 ueId;
   U8 idType;
}UeUetIdentReqInd;

typedef struct _ueUetIdentRsp {
  U32 ueId;
  U8 idType;
  Bool idValPres;
  /* As of now we consider only IMSI/IMEI/IMEISV
   * so UE_IMEISV_LENGTH=16 should be sufficient
   */
  U8 idVal[UE_IMEISV_LENGTH];
}UeUetIdentRsp;

typedef struct _ueUetAuthReqInd
{
   U32 ueId;
   U8 rand[16];
   U8 autn[16];
   U8 sqn[6];
   U8 KASME[UE_APP_KASME_KEY];
   U8 resXres[16];
   U8 res[16];
   U8 KNASVrfySts;
   /* TODO */
}UeUetAuthReqInd;

typedef struct _ueUetSqnRcvd
{
   Bool pres;
   U8 sqn[6];
}UeUetSqnRcvd;

typedef struct _ueUetRandRcvd
{
   Bool pres;
   U8 val[16];
}UeUetRandRcvd;

typedef struct _ueUetAuthRsp
{
   U32 ueId;
   UeUetSqnRcvd sqnRcvd;
   UeUetSqnRcvd maxSqnRcvd;
   UeUetRandRcvd randRcvd;
   Bool nonEPSAuthFail; /* Simulate Auth Resp with Cause #26 - non-EPS authentication unacceptable*/
}UeUetAuthRsp;

typedef struct _ueUetSecModeCmdInd
{
   U32 ueId;
   U8 NasCyphCfg;
   U8 NasIntProtCfg;
   U8 Kasme[UE_APP_KASME_KEY];
   U8 KNasEnc[UE_APP_NAS_ENC_KEY];
   U8 KNasInt[UE_APP_NAS_INT_KEY];
   U8 KNasVrfySts;
}UeUetSecModeCmdInd;

typedef struct _ueUetSecModeComplete {
  U32 ueId;
  /* Flag to indicate if the imeisv
   * value provided in the test to be
   * used or it should be taken from
   * ueCb
   */
  Bool imeisvPres;
  /* Flag to indicate if imeisv should
   * be included in the msg or not
   */
  Bool noImeisv;
  U8 imeisv[UE_IMEISV_LENGTH];
}UeUetSecModeComplete;

typedef struct _ueUetSecModeReject
{
   U32 ueId;
   U8 cause;
}UeUetSecModeReject;

typedef struct _ueEsmPdnAdd
{
   U8 pdnType; /* PDN type value. bit 1 to 3 bits (oct 3) */
   U8 addrInfo[UE_ESM_MAX_LEN_PDN_ADDRESS]; /* PDN address information */
}UeEsmPdnAdd;

typedef struct ueEsmEpsQos
{
   U8 pres;
   U8 qci;
   U8 lenQosCont;
   U8 maxBitRateUL;     /* Maximum bit rate for uplink 8th oct */
   U8 maxBitRateDL;     /* Maximum bit rate for downlink 9th oct */
   U8 guaraBitRateUL;   /* Guaranteed bit rate for uplink 12th oct */
   U8 guaraBitRateDL;   /* Guaranteed bit rate for downlink 13th oct */
}UeEsmEpsQos;

/* ESM QoS */
typedef struct ueEsmQoS
{
   U8 pres;
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
}UeEsmQos;

typedef struct _ueEsmApnAmbr
{
   U8 len;     /* Length of APN aggregate maximum bit rate contents */
   U8 dl;      /* APN-AMBR for downlink */
   U8 ul;      /* APN-AMBR for uplink */
}UeEsmApnAmbr;

typedef struct _ueEsmAPN
{
   U8 len;     /* Length of access point name contents */
   U8 apn[UE_ESM_MAX_LEN_ACCESS_PTNAME];/* Access point name value */
}UeEsmAPN;

typedef struct _ueEsmInfo
{
   U8 epsBearerId;
  UeEsmEpsQos qos;
  UeEsmAPN apn;
  UeEsmPdnAdd pAddr;
  UeEsmApnAmbr apnAmbr;
  UeEsmProtCfgOpt protCfgOpt;
}UeEsmInfo;

typedef struct _uePdnInfo
{
   U8 epsBearerId;
   UeEsmAPN apn;
   UeEsmPdnAdd pAddr;
}UePdnInfo;

typedef struct _ueUetPdnConRsp
{
   U32             ueId;
   U8             status; /* ROK/RFAILED */
   union
   {
      UePdnRejectInfo pdnConRejInfo;
      UePdnInfo       pdnInfo;
   }m;
}UeUetPdnConRsp;

typedef struct _ueUetAttachAcceptInd
{
   U32 ueId;
   U8 epsAtchRes;
   U16 t3412;
   Guti guti;
   LAI lai;
   U8 msId[CM_EMM_MAX_MOBILE_ID_DIGS];
   U8 cause;
   U8 t3402;
   U8 t3423;
   cmEmmPlmnId plmnList[6];
   UeEsmInfo esmInfo;
}UeUetAttachAcceptInd;

typedef struct _ueUetAttachComplete
{
   U32 ueId;
}UeUetAttachComplete;

typedef struct _ueUetAttachFail
{
   U32 ueId;
}UeUetAttachFail;

typedef enum _ueUetDetachType
{
   UET_NORMAL_DETACH = 1,
   UET_SWITCHOFF_DETACH
}UeUetDetachType;

typedef enum _ueUetNwInitDetachType
{
   UET_RE_ATTACH_REQ = 1,
   UET_RE_ATTACH_NOT_REQ,
   UET_IMSI_DETACH
}UeUetNwInitDetachType;

typedef struct _ueUetDetachReq
{
   U32 ueId;
   UeUetDetachType ueDetType;
}UeUetDetachReq;

typedef struct _ueUetNwInitDetachReq
{
   U32 ueId;
   UeUetNwInitDetachType ueNwInitDetType;
   U8 cause;
}UeUetNwInitDetachReq;

typedef struct _ueUetMtmsi
{
   Bool pres;
   U32 mTmsi;
}UeUetMtmsi;

typedef struct _ueUetServiceReq {
  U32 ueId;
  UeUetMtmsi ueMtmsi;
  U8 rrcCause;
  Bool noMac;
}UeUetServiceReq;

typedef struct _ueUetServiceRej
{
   U32 ueId;
   U8 cause;
}UeUetServiceRej;
typedef struct _ueUetRadCapUpdReq
{
   U32 ueId;
   Bool send_s1ap_msg;
   Bool upd_ueRadCap;
   U16 len;
   U8 *radCapMsg;
}UeUetRadCapUpdReq;

typedef struct _ueUetPagingMsg
{
   U32 ueId;
   U8 domainType;
}UeUetPagingMsg;

typedef struct _ueUetDetachReqAccept
{
   U32 ueId;
}UeUetDetachAcceptInd;

typedef struct _ueUetUeTrigDetachAccept
{
   U32 ueId;
}UeUetUeTrigDetachAccept;

typedef struct _ueUetTauRequest
{
   U32 ueId;
   UeUetMtmsi ueMtmsi;
   U8 epsUpdtType;
   U8 ActvFlag;
   // Indicates the state of each EPS bearer context
   U16 epsBearerCtxSts;
}UeUetTauRequest;

typedef struct _ueUetTauAccept
{
   U32 ueId;
   U8 epsUpdateRes;
   U8 gutiChanged;
   Guti guti;
}UeUetTauAccept;

typedef struct _ueUetTauComplete
{
   U32 ueId;
}UeUetTauComplete;

typedef struct _ueUetFlush
{
   U8 noOfUe;
}UeUetFlush;

typedef struct ueEsmTftPfIpv4
{
   U8 pres;
   U8          ip4[CM_ESM_IPV4_SIZE];
}UeEsmTftPfIpv4;

/*Ipv6 Remote Addr type */
typedef struct ueEsmTftPfIpv6
{
   U8          pres;
   U8          ip6[CM_ESM_IPV6_SIZE];
}UeEsmTftPfIpv6;

typedef struct ueEsmTftProtIden
{
   U8    pres;
   U8           protType;
}UeEsmTftProtIden;


typedef struct ueEsmTftPort
{
   U8    pres;
   U16   port;
}UeEsmTftPort;

typedef struct ueEsmTftPortRange
{
   U8           pres;
   U16          rangeLow;
   U16          rangeHigh;
}UeEsmTftPortRange;

typedef struct ueEsmTftSecParam
{
   U8          pres;
   U8          params[CM_ESM_IP_SEC_SIZE];
}UeEsmTftSecParam;

typedef struct ueEsmTftTos
{
   U8   pres;
   U8          tos;
   U8          mask;
}UeEsmTftTos;

typedef struct ueEsmTftIpv6FlowLbl
{
   U8          pres;
   U8          buf[CM_ESM_IPV6_FLOW_LABEL_SIZE];
}UeEsmTftIpv6FlowLbl;

typedef struct ueEsmTftPf
{
   U8            pres;         /* present or Not*/
   U8                   id;           /* Packet Filter idenntifier*/
   U8                   dir;          /* Direction */
   U8                   preced;       /* Precedence */
   U8                  len;          /* Length */
   U32                 ipv4Mask;
   UeEsmTftPfIpv4       ipv4;         /* Ipv4 Address */
   UeEsmTftPfIpv6       ipv6;         /* Ipv6 Address */
   UeEsmTftProtIden     protId;       /* Protocol Identifier */
   UeEsmTftPort         localPort;    /* Local  Port Idemtifier */
   UeEsmTftPort         remotePort;   /* Remote Port Idemtifier */
   UeEsmTftPortRange    locPortRange; /* Port Range */
   UeEsmTftPortRange    remPortRange; /* Port Range */
   UeEsmTftSecParam     secParam;     /* Security  Param */
   UeEsmTftTos          tos;          /* Type of Service  Param */
   UeEsmTftIpv6FlowLbl  flowLabel;    /* Flow Label   */
}UeEsmTftPf;

/* TFT Parameter Type */
typedef enum ueEsmTftParamType
{
   UE_ESM_TFT_PARAM_AUTH_TOKEN= 0x1,
   UE_ESM_TFT_PARAM_FLOW_ID,
   UE_ESM_TFT_PARAM_FILTER_ID
}UeEsmTftParamType;

typedef struct ueEsmTftParam
{
   UeEsmTftParamType      paramType;
   U8                     len;
   U8                     buf [CM_ESM_TFT_MAX_PARAM_BUF];
}UeEsmTftParam;

typedef struct ueEsmTft
{
   U8    pres;                                           /* Present or not */
   U8    len;
   U8    opCode;                             /* TFT Operation Code*/
   U8    eBit ;                                        /* param List presnt */
   U8    noOfPfs;                                      /* No  Of packet Filters */
   U8    noOfParams;                                   /* No Of packet Filters */
   UeEsmTftPf         pfList[CM_ESM_MAX_PKT_FILTERS];
   UeEsmTftParam      params[CM_ESM_MAX_PARAMS];       /* Tft Params */
}UeEsmTft;
typedef struct _ueUetBearerAllocReq
{
   U32                 ueId;
   U8                  bearerId;
   U8                  lnkEpsBearerId;
   UeEsmEpsQos         epsQos;
   UeEsmTft            tft;
}UeUetBearerAllocReq;
/*Erab Release Indication*/
typedef struct UeErabRelInd
{
   U32 ueId;
   U8 numOfErabIds;
   U8 *erabIdLst;
}UeErabRelInd;
/* LLC service access point identifier */
typedef struct ueEsmLLCSerPt
{
  U8  pres;

   U8 ieVal;   /* LLC SAPI value */
}UeEsmLLCSerPt;

/* Radio priority */
typedef struct ueEsmRadioPrio
{
   U8  pres;

   U8 ieVal;      /* Radio priority level value bits 1-3 of 1st oct */
}UeEsmRadioPrio;

/* Packet Flow Identifier */
typedef struct ueEsmPktFlowId
{
   U8 pres;

   U8 len;     /* Length of Packet Flow Identifier IE */
   U8 ieVal;   /* Packet Flow Identifier value bits 1-7 of 3rd oct */
}UeEsmPktFlowId;

/* Transaction Identifier */
typedef struct _ueEsmTxnId
{
   U8  pres;

   U8 len;        /* Length of Linked TI IE */
   U8 tiVal;      /* TI value occupy bits 5 - 7 of the first oct */
   U8 tiFlag;     /* TI flag occupy bit 8 of the first oct */
   U8 tie;        /* TIE occupy bits 1 - 7 of the second oct */
   U8 tiExt;      /* TI extended occupy bit 8 of the second oct */

}UeEsmTxnId;

/* cm_esm_x_001.main_1: Activate dedicated EPS bearer context request */
typedef struct ueUetActDedBearCtxtReq
{
   U32               ueId;
   U8                bearerId;
   U8                lnkBearerId;
   UeEsmEpsQos       epsQos;
   UeEsmTft          tft;
   UeEsmTxnId        txnId;
   UeEsmQos          qos;
   UeEsmLLCSerPt     llc;
   UeEsmRadioPrio    radioPrio;
   UeEsmPktFlowId    pktFlowId;
#if 0
   UeEsmProtCfgOpt   protCfgOpt;
#endif
}UeUetActDedBearCtxtReq;

/* Activate dedicated EPS bearer context accept message */
typedef struct ueEsmActDedBearCtxtAcc
{
   U32 ueId;
   U8 bearerId;
# if 0
   UeEsmProtCfgOpt   protCfgOpt;
#endif
}UeEsmActDedBearCtxtAcc;
typedef struct ueEsmActDedBearCtxtRej
{
   U32 ueId;
   U8 bearerId;
   U8 esmCause;
# if 0
   UeEsmProtCfgOpt   protCfgOpt;
#endif
}UeEsmActDedBearCtxtRej;

/* cm_esm_x_001.main_1: De-Activate EPS bearer context request */
typedef struct ueUetDeActvBearCtxtReq
{
   U32 ueId;
   U8 bearerId;
   U8 esmCause;
}UeUetDeActvBearCtxtReq;

/* cm_esm_x_001.main_1: De-Activate EPS bearer context accept */
typedef struct ueUetDeActvBearCtxtAcc
{
   U32 ueId;
   U8 bearerId;
}UeUetDeActvBearCtxtAcc;

typedef struct ueEsmActDfltBearCtxtRej
{
   U32 ueId;
   U8 bearerId;
   U8 esmCause;
# if 0
   UeEsmProtCfgOpt   protCfgOpt;
#endif
}UeEsmActDfltBearCtxtRej;

typedef struct ueDropActDfltEpsBearCtxtReq {
  U32 ueId;
  Bool dropActDfltEpsBearCtxtReq;
} UeDropActDfltEpsBearCtxtReq;

typedef struct _ueUetEmmInformation
{
   U32 ueId;
}UeUetEmmInformation;

typedef struct _ueUetAuthRejInd
{
   U32 ueId;
}UeUetAuthRejInd;

typedef struct _ueUetAuthFailure {
  U32 ueId;
  U8 cause;
  U8 auts[14];
} UeUetAuthFailure;

typedef struct _ueUetEmmStatus
{
   U32 ueId;
   U8 cause;
}UeUetEmmStatus;

typedef struct _ueUetEsmInformationReq
{
   U32 ueId;
   U8 tId;
}UeUetEsmInformationReq;

typedef struct _ueUetEsmInformationRsp
{
   U32 ueId;
   U8 tId;
   UeEmmNasPdnApn  nasPdnApn;
}UeUetEsmInformationRsp;

/* PDN Disconnect Request message */
typedef struct _ueUetPdnDisconnectReq {
  U32 ueId;
  U8 bearerId;
} UeUetPdnDisconnectReq;

/* PDN Disconnect Reject*/
typedef struct _ueUetPdnDisconnectRej
{
  U32 ueId;
  U8 cause;
}UeUetPdnDisconnectRej;

typedef struct _uetFailedErablist {
  U8 erabId;
  U8 cause;
  U8 qci;
} UetFailedErablist;

typedef struct _ueUetErabSetupFailedTosetup {
  U32 ueId;
#define MAX_FAILED_ERABS 11
  U8 noOfFailedErabs;
  UetFailedErablist failedErablist[MAX_FAILED_ERABS];
} UeUetErabSetupFailedTosetup;

typedef struct _ueUetRouterAdv {
  U8 ueId;
  U8 bearerId;
  U8 ipv6Addr[CM_ESM_IPV6_SIZE];
} UeUetRouterAdv;

typedef struct _uetMessage
{
   UeMsgTypes    msgType;
   union _tfwMsg
   {
     UeUetErrInd          ueErrInd;
     UeUetAppCfReq        ueAppCfgReq;
     UeUetAppCfgCompInd   ueAppCfgCompInd;
     UeUetCfgReq          ueCfgReq;
     UeUetCfgCompInd      ueCfgCompInd;
     UeUetAttachReq       ueUetAttachReq;
     UeUetAttachRej       ueUetAttachRej;
     UeUetIdentReqInd     ueUetIdentReqInd;
     UeUetIdentRsp        ueUetIdentRsp;
     UeUetAuthReqInd      ueUetAuthReqInd;
     UeUetAuthRsp         ueUetAuthRsp;
     UeUetSecModeCmdInd   ueUetSecModeCmdInd;
     UeUetSecModeComplete ueUetSecModeComplete;
     UeUetSecModeReject   ueUetSecModeReject;
     UeUetAttachAcceptInd ueUetAttachAcceptInd;
     UeUetAttachComplete  ueUetAttachComplete;
     UeUetDetachReq       ueUetDetachReq;
     UeUetNwInitDetachReq ueUetNwInitDetachReq;
     UeUetUeTrigDetachAccept ueUetUeTrigDetachAcc;
     UeUetAttachFail      ueUetAttachFail;
     UeUetDetachAcceptInd ueUetDetachAcceptInd;
     UeUetTauRequest      ueUetTauRequest;
     UeUetTauAccept       ueUetTauAccept;
     UeUetTauComplete     ueUetTauComplete;
     UeUetTauReject       ueUetTauReject;
     UeUetServiceReq      ueUetServiceReq;
     UeUetServiceRej      ueUetServiceRej;
     UeUetPdnConReq       ueUetPdnConReq;
     UeUetPdnConRsp       ueUetPdnConRsp;
     UeUetPagingMsg       ueUetPagingMsg;
     UeUetRadCapUpdReq    ueUetRadCapUpdReq;
     UeUetFlush           ueUetFlush;
     UeUetBearerAllocReq  ueBearerAllocReq;
     UeUetActDedBearCtxtReq ueActDedBerReq;
     UeEsmActDedBearCtxtAcc ueActDedBerAcc;
     UeEsmActDedBearCtxtRej ueActDedBerRej;
     UeErabRelInd   ueErabRelInd;
     UeUetEmmInformation ueEmmInformation;
     UeUetAuthRejInd         ueUetAuthRejInd;
     UeUetEmmStatus          ueUetEmmStatus;
     UeEsmActDfltBearCtxtRej ueActDfltBerRej;
     UeUetEsmInformationReq  ueEsmInformationReq;
     UeUetEsmInformationRsp  ueEsmInformationRsp;
     UeUetDeActvBearCtxtReq ueDeActvBerReq;
     UeUetDeActvBearCtxtAcc ueDeActvBerAcc;
     UeUetPdnDisconnectReq  ueUetPdnDisconnectReq;
     UeUetPdnDisconnectRej  ueUetPdnDisconnectRej;
     UeUetErabSetupFailedTosetup ueErabsFailedToSetup;
     UeUetAuthFailure ueUetAuthFailure;
     UeUetRouterAdv ueUetRouterAdv;
     UeDropActDfltEpsBearCtxtReq ueDropActDfltBerReq;
   }msg;
}UetMessage;
/* Ue Interface general Structure declerations */
typedef UetMessage   UetRequest;

typedef UetMessage   UetResponse;

typedef UetMessage   UetIndication;

typedef UetMessage   UetConfirm;
/*****************************************************************************
 *                              Interface Primitives                         *
 ****************************************************************************/
typedef S16 (*UetMsgInd) ARGS((
                                 Pst           *pst,              /* Post structure */
                                 UetIndication  *reqMsg            /* indication message */
                               ));
typedef S16 (*UetMsgRsp) ARGS((
                                 Pst        *pst,              /* Post structure */
                                 UetResponse *rspMsg           /* response message */
                               ));
typedef S16 (*UetMsgReq) ARGS((
                                 Pst        *pst,              /* Post structure */
                                 UetRequest  *reqMsg           /* request  message */
                             ));
typedef S16 (*UetMsgCfm) ARGS((
                                 Pst        *pst,              /* Post structure */
                                 UetConfirm *rspMsg           /* response message */
                               ));


PUBLIC S16 cmPkUetMsgReq ARGS
((
Pst        *pst,        /* post structure */
UetRequest *ueMsg       /* Response message */
));

PUBLIC S16 cmPkUetMsgRsp ARGS
((
Pst            *pst,        /* post structure */
UetResponse   *ueMsg        /* Response message */
));

PUBLIC S16 cmUnpkUetMsgRsp ARGS
((
UetMsgRsp     func,        /* response Ue message handling function pointer */
Pst           *pst,        /* post structure */
Buffer        *mBuf        /* buffer to be unpacked */
));

PUBLIC S16 cmUnpkUetMsgCfm ARGS
((
UetMsgCfm     func,        /* Ue Confirm message handling function pointer */
Pst           *pst,        /* post structure */
Buffer        *mBuf        /* buffer to be unpacked */
));

PUBLIC S16 cmUnpkUetMsgReq ARGS
((
UetMsgReq    func,        /* Ue Request message handling function pointer */
Pst           *pst,        /* post structure */
Buffer        *mBuf        /* buffer to be unpacked */
));

PUBLIC S16 UeUiUetMsgReq ARGS
((
Pst           *pst,            /* Post structure */
UetRequest   *ueMsg          /* request message */
));

PUBLIC S16 UeUiUetMsgRsp ARGS
((
Pst           *pst,            /* Post structure */
UetResponse  *ueMsg          /* response message */
));

PUBLIC S16 UeUiUetMsgInd ARGS
((
Pst            *pst,          /* Post structure */
SuId           suId,          /* service user id */
UetIndication *abMsg         /* indication message */
));

PUBLIC S16 UeUiUetMsgCfm ARGS
((
Pst            *pst,          /* Post structure */
SuId           suId,          /* service user id */
UetConfirm    *abMsg        /* confirm message */
));

#ifdef __cplusplus
}
#endif /* extern "C" */
