/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */


/**********************************************************************

     Name:     S1SIM TFW API Interface

     Type:     C header file

     Desc:     This file contains the structures for Test Framework Interface.

     File:     fw_api_int.x

     Prg:

**********************************************************************/

#ifndef __FWAPIINTX__
#define __FWAPIINTX__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "fw_api_int.h"

#define FW_ESM_MAX_LEN_PROT_CFG_OPT 247
#define FW_ESM_MAX_PROTO_ID 4
#define FW_ESM_MAX_CONT_ID 10

typedef enum {
   UE_APPL_CONFIG = 1,
   UE_APP_CONFIG_COMPLETE_IND,
   UE_CONFIG,
   UE_CONFIG_COMPLETE_IND,
   UE_ATTACH_REQUEST,
   UE_END_TO_END_ATTACH_REQUEST,
   UE_AUTH_REQ_IND,
   UE_AUTH_RESP,
   UE_SEC_MOD_CMD_IND,
   UE_SEC_MOD_COMPLETE,
   UE_SEC_MOD_REJECT,
   UE_ATTACH_ACCEPT_IND,
   UE_ATTACH_COMPLETE,
   UE_ATTACH_FAIL_IND,
   UE_DETACH_REQUEST,
   UE_DETACH_ACCEPT_IND,
   UE_IDENTITY_REQ_IND,
   UE_IDENTITY_RESP,
   UE_TAU_REQ,
   UE_TAU_ACCEPT_IND,
   UE_TAU_REJECT_IND,
   UE_TAU_COMPLETE,
   UE_ATTACH_REJECT_IND,
   UE_SERVICE_REQUEST,
   UE_SERVICE_REJECT_IND,
   UE_CNTXT_REL_REQUEST,
   UE_PDN_CONN_REQ,
   UE_PDN_CONN_RSP_IND,
   UE_PARM_QRY,
   UE_PARM_QRY_RESP,
   UE_APPP_PARM_QRY,
   UE_APP_PARM_QRY_RESP,
   ENB_CONFIG,
   ENB_CONFIG_CONFIRM,
   ENB_PARM_QRY,
   ENB_PARM_QRY_RESP,
   ENB_S1_SETUP_REQ,
   ENB_S1_SETUP_RESP,
   ENB_S1_SETUP_TIMEOUT_IND,
   UE_PAGING_IND,
   UE_RAD_CAP_UPDATE_REQ,
   UE_PDN_CONN_REQ_TIMEOUT_IND,
   UE_FLUSH,
   RESET_REQ,
   RESET_ACK,
   UE_NW_INIT_DETACH_REQUEST,
   UE_TRIGGERED_DETACH_ACCEPT,
   ENB_ERR_IND_MSG,
   ERAB_REL_IND,
   ERAB_REL_CMD,
   ERAB_REL_RSP,
   UE_CTX_REL_IND,
   INT_CTX_SETUP_IND,
   UE_BER_RES_ALLOC_REQ,
   UE_ACT_DED_BER_REQ,
   UE_ACT_DED_BER_ACC,
   UE_ACT_DED_BER_REJ,
   SCTP_ABORT_REQ,
   SCTP_SHUTDOWN_REQ,
   UE_SET_NAS_NON_DELIVERY,
   UE_NAS_NON_DELIVERY_IND,
   UE_SET_INIT_CTXT_SETUP_FAIL,
   UE_SET_DROP_ICS,
   UE_ICS_DROPD_IND,
   UE_SET_DELAY_ICS_RSP,
   UE_SET_CTXT_REL_REQ_FOR_ICS,
   ENB_INACTV_TMR_CFG,
   UE_EMM_INFORMATION,
   UE_AUTH_REJ_IND,
   UE_SET_DELAY_UE_CTXT_REL_CMP,
   UE_EMM_STATUS = 71,
   UE_ACTV_DEFAULT_EPS_BEARER_CNTXT_REJECT,
   UE_ESM_INFORMATION_REQ,
   UE_ESM_INFORMATION_RSP = 74,
   MULTIPLE_ENB_CONFIG_REQ,
   UE_DEACTIVATE_BER_REQ,
   UE_DEACTIVATE_BER_ACC,
   X2_HO_TRIGGER_REQ,
   PATH_SW_REQ_ACK,
   ENB_CONFIGURATION_TRANSFER,
   MME_CONFIGURATION_TRANSFER = 81,
   UE_PDN_DISCONNECT_REQ,
   UE_PDN_DISCONNECT_TIMEOUT_IND,
   UE_PDN_DISCONNECT_REJ,
   UE_FW_ERAB_SETUP_REQ_FAILED_FOR_ERABS,
   UE_AUTH_FAILURE
}tfwCmd;

typedef enum
{
   UE_ATTACH_REQUEST_DONE = 1,
   UE_IDENTITY_REQ_IND_DONE,
   UE_IDENTITY_RESP_DONE,
   UE_AUTH_REQ_IND_DONE,
   UE_AUTH_RESP_DONE,
   UE_SEC_MOD_CMD_IND_DONE,
   UE_SEC_MOD_COMPLETE_DONE,
   UE_ATTACH_ACCEPT_IND_DONE,
   UE_ATTACH_COMPLETE_DONE
}attachState;


typedef enum ue_state
{
   UE_DEREGISTERED = 0,
   UE_REGISTERED
}Ue_State;

typedef enum ue_mode
{
   UE_IN_IDLE_MODE = 0,
   UE_IN_CONNECTED_MODE
}Ue_Mode;

typedef enum eps_Updt_type
{
   TFW_TA_UPDATING = 0,
   TFW_COMB_TALA_UPDATING,
   TFW_COMB_TALA_UPDATING_IMSI,
   TFW_PERIODIC_UPDATING
}Eps_Updt_Type;

typedef enum rrc_Cause
{
   TFW_EMERGENCY = 0,
   TFW_HIGHPRIORITY_ACCESS,
   TFW_MT_ACCESS,
   TFW_MO_SIGNALLING,
   TFW_MO_DATA,
   TFW_DELAY_TOLERANT_ACCESSv1020,
   TFW_MO_VOICE_CALLv1280
}Rrc_Cause;

/* Attach request optional parameters */
typedef struct lastTAI
{
   U8 mcc[3];
   U8 mnc[3];
   U16 tac;
}LastTAI;

typedef struct Last_TAI
{
   Bool pres;
   LastTAI last_tai;
}last_TAI;

typedef struct Pdn_Type
{
   Bool pres;
   U32 pdn_type;
}pdn_Type;

typedef struct Pdn_APN
{
   Bool pres;
   U8 len;
   U8 pdn_apn[MAX_LEN_ACCESS_PTNAME];
}pdn_APN;

typedef struct Add_UpdTyp
{
   Bool pres;
   U8 type;
}add_UpdTyp;

/* Protocol configuration options */
typedef struct Prot_CfgOpts
{
   Bool pres;

   U8 len;        /* Length of protocol config. options contents */
   U8 cfgProt;    /* configuration protocol. bits 1-3 of 3rd oct */
   U8 ext;        /* extension. bit 8 of 3rd oct */
   U8 numProtId;  /* Number of Protocol configurations */
   U8 numContId;  /* Number of Containers */
   struct pId
   {
      U16 pid;       /* Protocol ID */
      U8 len;        /* Length of protocol ID contents */
      U8 val[FW_ESM_MAX_LEN_PROT_CFG_OPT];   /* Protocol ID contents */
   }p[FW_ESM_MAX_PROTO_ID];

   struct cId
   {
      U16 cid;       /* Container ID */
      U8 len;        /* Length of ContainerID contents */
      U8 val[FW_ESM_MAX_LEN_PROT_CFG_OPT];   /* ContainerID contents */
   }c[FW_ESM_MAX_CONT_ID];
}prot_CfgOpts;

typedef struct Drx_Prm
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
}drx_Prm;

/* enodeb config request optional parameters */

typedef struct Cell_Id
{
   Bool pres;
   U16 cell_id;
}cell_Id;

typedef enum cfg_sts
{
   CFG_DONE,
   CFG_FAILED
}CfgStatus;

typedef enum nbCfg_FailCause
{
   TUCL_CFG_FAILED,
   SCTP_CFG_FAILED,
   EGTP_CFG_FAILED,
   S1AP_CFG_FAILED,
   ENBAPP_CFG_FAILED,
   LSAP_BINDING_FAILED,
   PCAP_CFG_FAILED,
   UNKNOWN_ERR
}NbCfgFailCause;

typedef struct fail_Cause
{
  U8 pres;
  U32 val;
  U8 type;
}S1FailCause;

typedef struct time_ToWaitIe
{
   Bool  pres;
   U32 val;
}Time_ToWait_Ie;

typedef enum S1Setup_Res
{
  S1_SETUP_SUCCESS,
  S1_SETUP_FAILED
}S1_setp_Result;

typedef struct Tac
{
   Bool pres;
   U16 tac;
}tac;

typedef struct Enb_Ip_Addr
{
   Bool pres;
   U32 enb_ip_addr;
}enb_Ip_Addr;

typedef struct Mme_Id
{
   Bool pres;
   U16 mme_id;
}mme_Id;

typedef struct Mme_Addr
{
   Bool pres;
   U32 mme_addr;
}mme_Addr;

typedef struct Sctp_Ip_Addr
{
   Bool pres;
   U32 sctp_ip_addr;
}sctp_Ip_Addr;

typedef struct Enb_Name
{
   Bool pres;
   U8 enb_name[MAX_ENB_NAME_LEN];
}enb_Name;

typedef struct Plmn_Id
{
   Bool pres;
   U8 plmn_id[MAX_PLMN_ID];
}plmn_Id;

typedef struct _fwPlmnId
{
   U8 numMncDigits;
   U8 mcc[3];
   U8 mnc[3];
}FwPlmnId;

typedef struct _fwBPlmnList
{
   U8 numBPlmns;
   FwPlmnId bPlmn[TFW_MAX_NUM_BPLMNS];
}FwBPlmnList;

typedef struct _fwSuppTA
{
   U16 tac;
   FwBPlmnList bPlmnList; /* Broadcasted PLMNs */
}FwSuppTA;

/* Supported TA List */
typedef struct _fwSuppTAList
{
   U8 pres;
   U8 numTAs;
   FwSuppTA suppTA[TFW_MAX_NUM_TAC];
}FwSuppTAList;

typedef struct _fwMmeName
{
   U8 len;
   U8 val[150];
}FwMmeName;

/* EnodeB type: Macro or Home EnodeB */
typedef struct _fwEnodeBType
{
   U8 pres;
   U8 val;
}FwEnodeBType;

/* CSG ID List */
typedef struct _fwCsgIdList
{
   U8 pres;
   U8 numCsgIds;
   U32 csgId[TFW_MAX_NUM_CSG_ID]; /* Bit string, size(27), lower 27 bits used */
}FwCsgIdList;

typedef struct Heartbeat_Interval
{
   Bool pres;
   U32 heartbeat_interval;
}heartbeat_Interval;

typedef struct Rto_Initial
{
   Bool pres;
   U32 rto_initial;
}rto_Initial;

typedef struct Rto_Min
{
   Bool pres;
   U32 rto_min;
}rto_Min;

typedef struct Rto_max
{
   Bool pres;
   U32 rto_max;
}rto_Max;

typedef struct S1_Prep_Timer_Val
{
   Bool pres;
   U32 s1_prepimer_val;
}s1_Prep_Timer_Val;

typedef struct S1_Overall_Timer_Val
{
   Bool pres;
   U32 s1_overallimer_val;
}s1_Overall_Timer_Val;

typedef struct Sctp_Udp_Service_Type
{
   Bool pres;
   U32 sctp_udp_service_type;
}sctp_Udp_Service_Type;

typedef struct Inactv_Tmr_Val
{
   Bool pres;
   U32 val;
}inactv_Tmr_Val;

typedef struct Max_Expires
{
   Bool pres;
   U32 val;
}max_Expires;

typedef struct _s1SetUpTmr
{
   Bool pres;
   U16  val;
}s1_SetUp_Tmr;

typedef struct _noOfInSctpStreams
{
   Bool pres;
   U16 val;
}no_Of_Sctp_In_Streams;
typedef struct _noOfOutSctpStreams
{
   Bool pres;
   U16 val;
}no_Of_Sctp_Out_Streams;
/* ue attach accept optional parameters */

typedef struct T3412
{
   Bool pres;
   U16 t3412;
}t3412;

typedef struct CmGUTI
{
   U8 mcc[3];
   U8 mnc[3];
   U16 mmeGrdId;
   U8 mmeCode;
   U32 mTmsi;
}cmGUTI;

typedef struct Guti
{
   Bool pres;
   cmGUTI guti;
}guti;

typedef struct CmEmmLAI
{
   U8 mcc[3];
   U8 mnc[3];
   U16 lac;
}cmEmmLai;

typedef struct Lai
{
   Bool pres;
   cmEmmLai lai;
}lai;

typedef struct Ms_Id
{
   Bool pres;
   U8 ms_id[EMM_MAX_MOBILE_ID_DIGS];
}ms_Id;

#if 0
typedef struct _cause
{
   Bool pres;
   U8   val;
}Failure;
#endif
typedef struct T3402
{
   Bool pres;
   U8 t3402;
}t3402;

typedef struct T3423
{
   Bool pres;
   U8 t3423;
}t3423;

typedef struct CmEmmPlmnID
{
   U8 mcc[3];
   U8 mnc[3];
}cmEmmPlmnID;

typedef struct Plmn_List
{
   Bool pres;
   cmEmmPlmnID plmn_lst[6];
}plmn_List;

/* security mode command indication optional parameters*/

/* typedef struct nas_Cyph_Cfg,typedef struct nas_Int_prot_cfg and typedef struct kasme
 * is already defined */

typedef struct Knas_Enc
{
   Bool pres;
   U8 knas_enc;
}knas_Enc;

typedef struct Knas_Int
{
   Bool pres;
   U8 knas_int;
}knas_Int;

/* Auth request indication request optional parameters*/
/* GUTI is defined in attach accept indication */
typedef struct Rand
{
   Bool pres;
   U8 randm[16];
}randm;

typedef struct Autn
{
   Bool pres;
   U8 autn[16];
}autn;

typedef struct Kasme
{
   Bool pres;
   U8 kasme;
}kasme;

typedef struct Recvd_Xres
{
   Bool pres;
   U8 recvd_xres;
}recvd_Xres;

typedef struct Res
{
   Bool pres;
   U8 res;
}res;

/* ue config optional typedef structure feilds parameters*/
typedef struct Nas_Cyp_Cfg
{
   Bool pres;
   U8 nas_cyp_cfg;
}nas_Cyp_Cfg;

typedef struct Nas_Int_Prot_Cfg
{
   Bool pres;
   U8 nas_int_prot_cfg;
}nas_Int_Prot_Cfg;

typedef struct Srv_Plmn
{
   Bool pres;
   U8 srv_plmn[6];
}srv_Plmn;

typedef struct Algo_Type
{
   Bool pres;
   U8 algo_type;
}algo_Type;

typedef struct Op_Id
{
   Bool pres;
   U32 op_id;
}op_Id;

typedef struct Auth_Type
{
   Bool pres;
   U8 auth_type;
}auth_Type;

typedef struct Ue_Nw_Cap
{
   Bool pres;
   Bool eea2_128;
   Bool eea1_128;
   Bool eea0;

   Bool eia2_128;
   Bool eia1_128;
   Bool eia0;
}ue_Nw_Cap;

typedef struct Op_Key
{
   Bool pres;
   U32 op_key[MAX_OPKEY_LEN];
}op_Key;

typedef struct Shared_Key
{
   Bool pres;
   U32 shared_key[MAX_SHAREDKEY_LEN];
}shared_Key;

/* ue app config typedef structure feilds optional parameters*/

typedef struct Trf_Gen_Ip_Addr
{
   Bool pres;
   U32 trf_gen_ip_addr;
}trf_Gen_Ip_Addr;

typedef struct Nas_Proc_Guard_Timer
{
   Bool pres;
   U8 nas_proc_guard_timer;
}nas_Proc_Guard_Timer;

typedef struct Num_Of_ue
{
   Bool pres;
   U8 num_of_ue;
}num_Of_ue;

typedef struct Radio_Cpblty
{
   Bool pres;
   U16  len;
   U8 *radioCapMsg;
}radio_Cpblty;

/*ESM Information Transfer Flag*/
typedef struct _esm_Info_Trans_flag
{
   Bool pres;
   Bool esm_info_transfer_flag;
}esm_Info_Trans_flag;

typedef struct ueAppConfig
{
   trf_Gen_Ip_Addr trfGenIPAddr_pr;
   nas_Proc_Guard_Timer nasProcGuardTimer_pr;
   num_Of_ue numOfUe_pr;
}ueAppConfig_t;

typedef struct ueAppConfigCompleteInd
{
   U8 status;
}ueAppConfigCompleteInd_t;

typedef struct ueConfig
{
   U8 ue_id;
   U8 imsiLen;
   U8 imsi[15];
   U8 imei[16];
   U32 auth_key;
   algo_Type algoType_pr;
   op_Id opId_pr;
   ue_Nw_Cap ueNwCap_pr;
   auth_Type authType_pr;
   op_Key   opKey_pr;
   shared_Key sharedKey_pr;
   nas_Cyp_Cfg nasCypCfg_pr;
   nas_Int_Prot_Cfg nasIntProtCfg_pr;
   srv_Plmn srvPlmn_pr;
}ueConfig_t;

typedef struct ueRadCapConfig
{
   U8 ue_id;
   Bool snd_ueCapInd;
   Bool upd_ueCapInfo;
   U16 rrcMsgLen;
   U8 *ueRadCapRrcmsg;
}ueRadCapConfig_t;


typedef struct ueConfigCompleteInd
{
   U8 status;
}ueConfigCompleteInd_t;

typedef struct ueAttachRequest
{
   U8 ue_Id;
   U8 mIdType;
   U8 epsAttachType;
   U8 useOldSecCtxt;
   guti guti_pr;
   last_TAI lastTAI_pr;
   pdn_Type pdnType_pr;
   pdn_APN pdnAPN_pr;
   add_UpdTyp addUpdTyp_pr;
   prot_CfgOpts protCfgOpts_pr;
   drx_Prm drxParm_pr;
   esm_Info_Trans_flag eti;
}ueAttachRequest_t;

typedef struct ueAuthReqInd
{
   U8 ue_Id;
   U8 randm[16];
   U8 autn[16];
   U8 sqn[6];
   U8 kasme[32];
   U8 recvd_xres[16];
   U8 res[16];
   U8 knas_Vrfy_Sts;
} ueAuthReqInd_t;

typedef struct ueSqnRcvd
{
   Bool pres;
   U8 sqn[6];
}ueSqnRcvd_t;
typedef struct ueRandRcvd
{
   Bool pres;
   U8   val[16];
}ueRandRcvd_t;

typedef struct ueAuthResp
{
   U8 ue_Id;
   ueSqnRcvd_t sqnRcvd;
   ueSqnRcvd_t maxSqnRcvd;
   Bool nonEPSAuthFail; /* Simulate Auth Resp with Cause #26 - non-EPS authentication unacceptable*/
   ueRandRcvd_t randRcvd;
}ueAuthResp_t;

typedef struct ueSecModeCmdInd
{
   U8 ue_Id;
   U8 nas_cyp_cfg;
   U8 nas_int_prot_cfg;
   U8 kasme[MAX_KASME_KEY];
   U8 knas_enc[MAX_NAS_ENC_KEY];
   U8 knas_int[MAX_NAS_INT_KEY];
   U8 knas_Vrfy_Sts;
}ueSecModeCmdInd_t;

typedef struct ueSecModeComplete
{
   U8 ue_Id;
}ueSecModeComplete_t;

typedef struct ueSecModeReject
{
   U8 ue_Id;
   U8 cause;
}ueSecModeReject_t;

typedef struct ueEsmPdnAdd
{
   U8 pdnType; /* PDN type value. bit 1 to 3 bits (oct 3) */
   U8 addrInfo[MAX_LEN_PDN_ADDRESS]; /* PDN address information */
}ue_Esm_PdnAdd;

typedef struct _ueEsmEpsQos
{
   U8 pres;
   U8 qci;
   U8 lenQosCont;
   U8 maxBitRateUL;     /* Maximum bit rate for uplink 8th oct */
   U8 maxBitRateDL;     /* Maximum bit rate for downlink 9th oct */
   U8 guaraBitRateUL;   /* Guaranteed bit rate for uplink 12th oct */
   U8 guaraBitRateDL;   /* Guaranteed bit rate for downlink 13th oct */
}ue_Esm_Eps_Qos;

/* ESM QoS */
typedef struct _ueEsmQoS
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
}ue_Esm_Qos;

typedef struct ueEsmApnAmbr
{
   U8 len;     /* Length of APN aggregate maximum bit rate contents */
   U8 dl;      /* APN-AMBR for downlink */
   U8 ul;      /* APN-AMBR for uplink */
}ue_Esm_ApnAmbr;

typedef struct ueEsmAPN
{
   U8 len;     /* Length of access point name contents */
   U8 apn[MAX_LEN_ACCESS_PTNAME];/* Access point name value */
}ue_Esm_APN;

typedef struct ueEsmInfo
{
   U8 epsBearerId;
   ue_Esm_Eps_Qos qos;
   ue_Esm_APN apn;
   ue_Esm_PdnAdd pAddr;
   ue_Esm_ApnAmbr apnAmbr;
   prot_CfgOpts protCfgOpts_pr;
}ue_Esm_Info;

typedef struct ueAttachAccept
{
   U8 ue_Id;
   U8 eps_Atch_resp;
   U16 t3412;
   cmGUTI guti;
   cmEmmLai lai;
   U8 ms_id[EMM_MAX_MOBILE_ID_DIGS];
   U8 cause;
   U8 t3402;
   U8 t3423;
   cmEmmPlmnID plmn_lst[6];
   ue_Esm_Info esmInfo;
}ueAttachAccept_t;

typedef struct ueAttachComplete
{
   U8 ue_Id;
}ueAttachComplete_t;
/*This message sent along with attach complete */
typedef struct ueActvDfltEpsBearerCtxtRej
{
   U8 ue_Id;
   U8 bearerId;
   U8 cause;
}ueActvDfltEpsBearerCtxtRej_t;
typedef struct ueAttachFail
{
   U8 ueId;
   U8 ueState;
   U16 reason;
}ueAttachFail_t;

typedef enum ueDetachType
{
   UE_NORMAL_DETACH = 1,
   UE_SWITCHOFF_DETACH
}ueDetachType_t;

typedef struct ueDetachReq
{
   U8 ue_Id;
   ueDetachType_t ueDetType;
}uedetachReq_t;

typedef enum ueNwInitDetType
{
   TFW_RE_ATTACH_REQUIRED=1,
   TFW_RE_ATTACH_NOT_REQUIRED,
   TFW_IMSI_DETACH
}ueNwInitDetType_t;

typedef struct ueNwInitDetachReq
{
   U8 ue_Id;
   ueNwInitDetType_t Type;
   U8 cause;
}ueNwInitdetachReq_t;

typedef struct ueMtmsi
{
   Bool pres;
   U32 mTmsi;
}ueMtmsi_t;

typedef struct ueServiceReq
{
   U8 ue_Id;
   ueMtmsi_t ueMtmsi;
   U8 rrcCause;
}ueserviceReq_t;

typedef struct _relCause
{
   U8 causeType;
   U32 causeVal;
}RelCause;

typedef struct ueCntxtRelReq
{
   U8 ue_Id;
   RelCause cause;
}ueCntxtRelReq_t;

typedef struct uepdnConReq {
  U8 ue_Id;
  U8 reqType;
  pdn_Type pdnType_pr;
  pdn_APN pdnAPN_pr;
  prot_CfgOpts protCfgOpts_pr;
} uepdnConReq_t;

typedef struct uepdnDisconnectReq {
  U8 ue_Id;
  U8 epsBearerId;
} uepdnDisconnectReq_t;

typedef struct _errCause
{
   U8 pres;
   U8   causeType;
   U8   causeVal;
}ErrCause;

typedef struct _fwCriticalityDiag_IE_Item
{
   U8 pres;
   U32 iECriticality;
   U32 iE_ID;
   U32 TypOfErr;
}FwCriticalityDiag_IE_Item;

typedef struct _fwCriticalityDiag_IE_Lst
{
   U16 noComp;
   FwCriticalityDiag_IE_Item *member;
}FwCriticalityDiag_IE_Lst;
typedef struct _fwCriticalityDiag
{
   U8  pres;
   U8  procCodePres;
   U8  proCriticalityPres;
   U8  trigMsgPres;
   U32 procedureCode;
   U32 triggeringMsg;
   U32 procedureCriticality;
   FwCriticalityDiag_IE_Lst ieLst;
}FwCriticalityDiag;
typedef struct fwNbErrIndMsg
{
   U8   isUeAssoc;
   U8   ue_Id;
   ErrCause cause;
   FwCriticalityDiag criticalityDiag;
}fwNbErrIndMsg_t;

typedef struct _pdnConRejInfo
{
   U8 epsBearerId;
   U8 cause;
}pdnConRejInfo_t;

typedef struct _ue_Pdn_Info
{
   U8 epsBearerId;
   ue_Esm_APN apn;
   ue_Esm_PdnAdd pAddr;
   ue_Esm_ApnAmbr apnAmbr;
}Ue_Pdn_Info;

typedef struct uepdnConRsp
{
   U8 ue_Id;
   U8 status;
   union
   {  pdnConRejInfo_t conRejInfo;
      Ue_Pdn_Info pdnInfo;
   }m;
}uePdnConRsp_t;

typedef struct uePdnConTimeOutInd
{
   U8 ue_Id;
}uePdnConTimeOutInd_t;

typedef struct ueServiceRejInd
{
   U8 ue_Id;
   U8 cause;
}ueServiceRejInd_t;

typedef struct ueDetachAcceptInd
{
   U8 ue_Id;
}ueDetachAcceptInd_t;

typedef struct ueTrigDetachAcceptInd
{
   U8 ue_Id;
}ueTrigDetachAcceptInd_t;

typedef struct ueAttachRejInd
{
   U8 ue_Id;
   U8 cause;
}ueAttachRejInd_t;

typedef struct ueIdentityReqInd
{
   U8 ue_Id;
   U8 idType;
}ueIdentityReqInd_t;

typedef struct ueIdentityResp
{
   U8 ue_Id;
   U8 idType;
}ueIdentityResp_t;

typedef struct ueTauReq
{
   U8 ue_Id;
   ueMtmsi_t ueMtmsi;
   Eps_Updt_Type type;
   U8 Actv_flag;
}ueTauReq_t;

typedef struct ueTauAccept
{
   U8 ue_Id;
   cmGUTI guti;
   U8 epsUpdateRes;
   U8 gutiChanged;
}ueTauAccept_t;

typedef struct ueTauRejInd
{
   U8 ue_Id;
   U8 cause;
}ueTauRejInd_t;

typedef struct uePagingInd
{
   U8 ue_Id;
   U8 domain_Type;
}uePagingInd_t;

typedef struct ueTauComplete
{
   U8 ue_Id;
}ueTauComplete_t;

typedef struct ueFlush
{
   U8 noOfUe;
}ueFlush_t;


typedef struct _ueEsmTftPfIpv4
{
   U8          pres;
   U8          ip4[UE_ESM_IPV4_SIZE];
}ue_Esm_Tft_Pf_Ipv4;

/*Ipv6 Remote Addr type */
typedef struct _ueEsmTftPfIpv6
{
   U8          pres;
   U8          ip6[UE_ESM_IPV6_SIZE];
}ue_Esm_Tft_Pf_Ipv6;

typedef struct _ueEsmTftProtIden
{
   U8    pres;
   U8           protType;
}ue_Esm_Tft_Prot_Iden;


typedef struct _ueEsmTftPort
{
   U8    pres;
   U16          port;
}ue_Esm_Tft_Port;

typedef struct _ueEsmTftPortRange
{
   U8           pres;
   U16          rangeLow;
   U16          rangeHigh;
}ue_Esm_Tft_Port_Range;

typedef struct _ueEsmTftSecParam
{
   U8          pres;
   U8          params[UE_ESM_IP_SEC_SIZE];
}ue_Esm_Tft_Sec_Param;

typedef struct _ueEsmTftTos
{
   U8   pres;
   U8          tos;
   U8          mask;
}ue_Esm_Tft_Tos;

typedef struct _ueEsmTftIpv6FlowLbl
{
   U8          pres;
   U8          buf[UE_ESM_IPV6_FLOW_LABEL_SIZE];
}ue_Esm_Tft_Ipv6_FlowLbl;

typedef struct _ueEsmTftPf
{
   U8            pres;         /* present or Not*/
   U8                   id;           /* Packet Filter idenntifier*/
   U8                   dir;          /* Direction */
   U8                   preced;       /* Precedence */
   U8                  len;          /* Length */
   U32                 ipv4Mask;
   ue_Esm_Tft_Pf_Ipv4       ipv4;         /* Ipv4 Address */
   ue_Esm_Tft_Pf_Ipv6       ipv6;         /* Ipv6 Address */
   ue_Esm_Tft_Prot_Iden     protId;       /* Protocol Identifier */
   ue_Esm_Tft_Port         localPort;    /* Local  Port Idemtifier */
   ue_Esm_Tft_Port         remotePort;   /* Remote Port Idemtifier */
   ue_Esm_Tft_Port_Range    locPortRange; /* Port Range */
   ue_Esm_Tft_Port_Range    remPortRange; /* Port Range */
   ue_Esm_Tft_Sec_Param     secParam;     /* Security  Param */
   ue_Esm_Tft_Tos          tos;          /* Type of Service  Param */
   ue_Esm_Tft_Ipv6_FlowLbl  flowLabel;    /* Flow Label   */
}ue_Esm_Tft_Pf;

typedef enum  _ueEsmTftParamType
{
   CM_ESM_TFT_PARAM_AUTH_TOKEN= 0x1,
   CM_ESM_TFT_PARAM_FLOW_ID,
   CM_ESM_TFT_PARAM_FILTER_ID
}ue_Esm_Tft_Param_Type;

typedef struct _ueEsmTftParam
{
   ue_Esm_Tft_Param_Type      paramType;
   U8                     len;
   U8                     buf [UE_ESM_TFT_MAX_PARAM_BUF];
}ue_Esm_Tft_Param;
typedef struct _ueEsmTft
{
   U8    pres;                                           /* Present or not */
   U8    len;
   U8    opCode;                             /* TFT Operation Code*/
   U8    eBit ;                                        /* param List presnt */
   U8    noOfPfs;                                      /* No  Of packet Filters */
   U8    noOfParams;                                   /* No Of packet Filters */
   ue_Esm_Tft_Pf  *pfList;  /* Pf List */
   ue_Esm_Tft_Param      *params;       /* Tft Params */
}ue_Esm_Tft;

typedef struct ueBearerAllocReq
{
   U8              ue_Id;
   U8              bearerId;
   U8              lnkEpsBearerId;
   ue_Esm_Eps_Qos  qos;
   ue_Esm_Tft      tft;
}ueBearerAllocReq_t;

/* LLC service access point identifier */
typedef struct _ueEsmLLCSerPt
{
   U8  pres;
   U8 ieVal;   /* LLC SAPI value */
}ue_Esm_LLC_SerPt;

/* Radio priority */
typedef struct _ueEsmRadioPrio
{
   U8  pres;
   U8 ieVal;      /* Radio priority level value bits 1-3 of 1st oct */
}ue_Esm_Radio_Prio;

/* Packet Flow Identifier */
typedef struct _ueEsmPktFlowId
{
   U8 pres;
   U8 len;     /* Length of Packet Flow Identifier IE */
   U8 ieVal;   /* Packet Flow Identifier value bits 1-7 of 3rd oct */
}ue_Esm_Pkt_FlowId;

typedef struct _EsmTxnId
{
   U8  pres;

   U8 len;        /* Length of Linked TI IE */
   U8 tiVal;      /* TI value occupy bits 5 - 7 of the first oct */
   U8 tiFlag;     /* TI flag occupy bit 8 of the first oct */
   U8 tie;        /* TIE occupy bits 1 - 7 of the second oct */
   U8 tiExt;      /* TI extended occupy bit 8 of the second oct */

}ue_Esm_TxnId;
typedef struct ueActDedBearCtxtReq
{
   U8                   ue_Id;
   U8                   bearerId;
   ue_Esm_Eps_Qos       epsQos;
   ue_Esm_Tft           tft;
   ue_Esm_TxnId         txnId;
   ue_Esm_Qos           qos;
   ue_Esm_LLC_SerPt     llc;
   ue_Esm_Radio_Prio    radioPrio;
   ue_Esm_Pkt_FlowId    pktFlowId;
   U8                   lnkBearerId;
   // UeEsmProtCfgOpt   protCfgOpt;
}UeActDedBearCtxtReq_t;

typedef struct ueActDedBearCtxtAcc
{
   U8                   ue_Id;
   U8                   bearerId;
}UeActDedBearCtxtAcc_t;

typedef struct ueActDedBearCtxtRej
{
   U8                   ue_Id;
   U8                   bearerId;
   U8                   esmCause;
}UeActDedBearCtxtRej_t;

typedef struct ueDeActvBearCtxtReq
{
   U8 ue_Id;
   U8 bearerId;
   U8 esmCause;
}UeDeActvBearCtxtReq_t;

typedef struct ueDeActvBearCtxtAcc
{
   U8 ue_Id;
   U8 bearerId;
}UeDeActvBearCtxtAcc_t;

typedef enum
{
   TFW_CAUSE_RADIONW,
   TFW_CAUSE_TRANSPORT,
   TFW_CAUSE_NAS,
   TFW_CAUSE_PROTOCOL,
   TFW_CAUSE_MISC
}NasNonDelCauseType;

typedef enum
{
   TfwCauseRadioNwunspecifiedEnum,
   TfwCauseRadioNwtx2relocoverall_expiryEnum,
   TfwCauseRadioNwsuccessful_handoverEnum,
   TfwCauseRadioNwrelease_due_to_eutran_generated_reasonEnum,
   TfwCauseRadioNwhandover_cancelledEnum,
   TfwCauseRadioNwpartial_handoverEnum,
   TfwCauseRadioNwho_failure_in_target_EPC_eNB_or_target_systemEnum,
   TfwCauseRadioNwho_target_not_allowedEnum,
   TfwCauseRadioNwtS1relocoverall_expiryEnum,
   TfwCauseRadioNwtS1relocprep_expiryEnum,
   TfwCauseRadioNwcell_not_availableEnum
}NasNonDelCauseValRadioNw;

typedef enum
{
        SztCauseNasnormal_releaseEnum,
        SztCauseNasauthentication_failureEnum,
        SztCauseNasdetachEnum,
        SztCauseNasunspecifiedEnum,
        SztCauseNascsg_subscription_expiryEnum
}NasNonDelCauseValNas;

typedef enum
{
        SztCauseTporttransport_resource_unavailableEnum,
        SztCauseTportunspecifiedEnum
}NasNonDelCauseValTport;
typedef struct ueNasNonDel
{
   U8 ue_Id;
   Bool flag;
   NasNonDelCauseType causeType;
   U32 causeVal;
}UeNasNonDel;
typedef struct ueInitCtxtSetupFail
{
   U8 ue_Id;
   Bool flag;
   U8 causeType;
   U32 causeVal;
}ueInitCtxtSetupFail;
typedef struct ueDropInitCtxtSetup
{
   U8 ue_Id;
   Bool flag;
   U32 tmrVal;
}UeDropInitCtxtSetup;
typedef struct ueDelayInitCtxtSetupRsp
{
   U8 ue_Id;
   U32 tmrVal;
   Bool flag;
}UeDelayInitCtxtSetupRsp;
typedef struct ueDelayUeCtxtRelCmp
{
   U8 ue_Id;
   U32 tmrVal;
   Bool flag;
}UeDelayUeCtxtRelCmp;
typedef struct ueSetCtxtRelForInitCtxtSetup
{
   U8 ue_Id;
   U8 causeType;
   U32 causeVal;
   Bool flag;
}UeSetCtxtRelForInitCtxtSetup;
typedef struct ueNasNonDelRsp
{
   U8 ue_Id;
}ueNasNonDelRsp_t;

typedef struct _num_Of_Enbs
{
   Bool pres;
   U8   numOfEnb;
}num_Of_Enbs_t;

typedef struct _fwNbConfigReq
{
   cell_Id cellId_pr;
   tac tac_pr;
   enb_Ip_Addr enbIpAddr_pr;
   mme_Id mmeId_pr;
   mme_Addr mmeAddr_pr;
   sctp_Ip_Addr sctpIpAddr_pr;
   enb_Name enbName_pr;
   plmn_Id plmnId_pr;
   FwSuppTAList suppTAs; /* Supported TAs */
   FwEnodeBType eNodeBType; /* Macro eNodeB or Home eNodeB */
   FwCsgIdList csgIdList; /* CSG Id List */
   heartbeat_Interval heratbeatInterval_pr;
   rto_Initial rtoInitial_pr;
   rto_Min rtoMin_pr;
   rto_Max rtoMax_pr;
   s1_Prep_Timer_Val s1PrepTimerVal_pr;
   s1_Overall_Timer_Val s1OverallTimerVal_pr;
   sctp_Udp_Service_Type sctpUdpServiceType_pr;
   inactv_Tmr_Val  inactvTmrVal_pr;
   max_Expires     maxExpires_pr;
   s1_SetUp_Tmr    s1SetUpTmr_pr;
   no_Of_Sctp_In_Streams   noOfSctpInStreams_pr;
   no_Of_Sctp_Out_Streams   noOfSctpOutStreams_pr;
   num_Of_Enbs_t numOfEnbs;
}FwNbConfigReq_t;

typedef struct _fwNbConfigCfm
{
   CfgStatus  status;
   NbCfgFailCause cause;
}FwNbConfigCfm_t;

typedef struct _fwSctpAbortReq
{
   U8 cause;
}FwSctpAbortReq_t;

typedef struct _fwNbS1SetupRsp
{
   S1_setp_Result res;
   S1FailCause    cause;
   Time_ToWait_Ie waitIe;
   U8             numPlmnIds;
   FwPlmnId       plmnIds[TFW_MAX_PLMNS_PER_MME];
   U16            numGrpIds;
   U16            groupIds[TFW_MAX_GRPS_PER_MME];
   U16            numCodes;
   U8             codes[TFW_MAX_CODES_PER_MME];
   U8             relCapacity;
   FwMmeName      mmeName;
   U32            mmeRelaySuppInd;
}FwNbS1setupRsp_t;

typedef struct ueRadCapUpd
{
   U8 ue_Id;
   Bool snd_S1AP;
   radio_Cpblty radioCap_pr;
}ueRadCapUpd_t;

typedef enum
{
   COMPLETE_RESET = 0,
   PARTIAL_RESET
}resetType;

typedef struct _CompleteReset
{
   U32 s1IntfId;
   U32 enbId;
}CompleteReset;

typedef struct _PartialReset
{
   U16 numOfConn;
   U8 *ueIdLst;
}PartialReset;

typedef struct _cause
{
   U8 causeType;
   U32 causeVal;
}ResetCause;

typedef struct _resetReq
{
   resetType rstType;
   ResetCause cause;
   union
   {
      CompleteReset completeRst;
      PartialReset partialRst;
   }r;
}ResetReq;

typedef struct _fwNbS1ResetAck
{
   U8 status;
   U16 numOfUes;
   U8 *ueIdLst;
}FwNbS1ResetAck_t;

typedef struct _fwErabRelInd_t
{
   U8 ueId;
   U8 numOfErabIds;
   U8 *erabIdLst;
}FwErabRelInd_t;

typedef struct _fwFwErabRelCmd_t
{
   U8 ueId;
   U32 enbUeS1apId;
   U32 mmeUeS1apId;
   U8 numOfErabIds;
   U8 *erabIdLst;
}FwErabRelCmd_t;

typedef struct _fwNbUeCtxRelInd
{
   U8 ueId;
}FwNbUeCtxRelInd_t;

typedef struct _fwNbIntCtxSetupInd
{
   U8 ueId;
   U8 status;
}FwNbIntCtxSetupInd_t;

typedef struct _fwNbIntCtxSetupDrpdInd
{
   U8 ueId;
}FwNbIntCtxSetupDrpdInd_t;

typedef struct UeEmmInformation
{
   U8 ue_Id;
}ueEmmInformation_t;

typedef struct UeAuthRejInd
{
   U8 ue_Id;
}ueAuthRejInd_t;

typedef struct UeAuthFailure {
  U8 ue_Id;
  U8 cause;
  U8 auts[TFW_AUTS_LEN];
} ueAuthFailure_t;

typedef struct UeEmmStatus
{
   U8 ue_Id;
   U8 cause;
}ueEmmStatus_t;

typedef struct UeEsmInformationReq
{
   U8 ue_Id;
   U8 tId;
}ueEsmInformationReq_t;

typedef struct UeEsmInformationRsp
{
   U8 ue_Id;
   U8 tId;
   pdn_APN  pdnAPN_pr;
}ueEsmInformationRsp_t;
typedef struct multiEnbCfgParam
{
   U32 cell_id;
   U32 tac;
   U8 plmn_id[MAX_PLMN_ID];
   U32 enbType;
   U8  plmn_length;
}multiEnbCfgParam_t;

typedef struct MultiEnbConfigReq
{
   U32 numOfEnbs;
   multiEnbCfgParam_t multiEnbCfgParam[MAX_NUM_OF_ENBS];
}multiEnbConfigReq_t;

typedef struct _fwNbPathSwReqAck
{
   U8 ueId;
}FwNbPathSwReqAck_t;

typedef struct _fwNbMmeConfigTrnsf
{
   union
   {
      U8 req;
      U8 reply;
   }u;
}FwNbMmeConfigTrnsf_t;

typedef struct uePdnDisconnFail
{
   U8 ueId;
}uePdnDisconnFail_t;

typedef struct _FwFailedErablist {
  U8 erabId;
  U8 qci;
  U8 cause;
} FwFailedErablist;

typedef struct _FwErabSetupFailedTosetup {
  U8 ueId;
  U8 noOfFailedErabs;
  FwFailedErablist failedErablist[MAX_FAILED_ERABS];
} FwErabSetupFailedTosetup;

typedef FwErabRelCmd_t FwErabRelRsp_t;

typedef void (*TestCnrlrCallBack)(short int, void *, short int);

/**< Api function declaration */
S16 tfwApi(tfwCmd type, void *msg);
void initTestFrameWork(TestCnrlrCallBack func);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __FWAPIINTX__ */
