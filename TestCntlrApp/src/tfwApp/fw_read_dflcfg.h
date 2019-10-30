/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#define MAX_ENB_NAME_LEN  20
#define APN_LEN 6 
#define MAX_OP_KEY_LEN 16
#define MAX_SHARED_KEY_LEN 16
#define MAX_UE_NW_CAP_SUPPORTED_ALGO 6

EXTERN Void readDfltCfgs(Void);
typedef enum
{
   AUTH_TYPE_XOR = 0,
   AUTH_TYPE_MILENAGE
}AuthType;

typedef enum
{
   ALGO_TYPE_AES=1,
   ALGO_TYPE_SNOW3G
}AlgoType;
typedef struct _ueNetwCap
{
   Bool eea2_128;
   Bool eea1_128;
   Bool eea0;

   Bool eia2_128;
   Bool eia1_128;
   Bool eia0;
}UeNetwCap;
typedef struct  _tfwAppCfgCb
{
   U32 tfwIpAddr;
}TfwAppCfgCb;

typedef struct _ueAppCfgCb
{
   U32 trfGenIPAddr;      /*IP address of eth port connected to traffic 
                             generator*/
   U8 NASProcGuardTimer;   /*timer value*/
   U8 numOfUE;             /*number of ues to simulate*/
}UeAppCfgCb;

typedef struct _ueCfgCb
{
   U8 ueId;       /*ue identity*/
   U8 imsi[16];       /*Mobile subscriber identity*/
   U8 imei[16];       /*Mobile equipment identity*/
   U8 NASCyphCfg;          /*eea0, eea1, eea2*/
   U8 NASIntProtCfg;       /*eia1, eia2*/
   AlgoType algoType;   /*Identifies the sucurity alogoritm supported*/
   U32 opId;      /*operator identity*/
   AuthType authType;   /*Auth type- XOR, Milenage*/
   UeNetwCap ueNwCap;   /*ue network capability*/
   U32 opKey[MAX_OP_KEY_LEN];
   U32 sharedKey[MAX_SHARED_KEY_LEN];
   U8 srvPlmn[6];
   /* Last TAI */
   U8 lastMcc[3];
   U8 lastMnc[3];
   U16 lastTac;
   /* GUTI */
   U8 mcc[3];
   U8 mnc[3];
   U16 mmeGrpId;
   U8 mmeCode;
   U32 mTmsi;
   /* PDN Type */
   U32 pdnType;
   /* PDN APN */
   U8 pdnAPN[APN_LEN];
   U16 ueRadCapRrcPduLen;
   U32 *ueRadCapRrcPdu;
}UeCfgCb;

typedef struct _nbAppCfgCb
{
   U32 cellId;                   /*cell id*/
   U16 tac;                      /*tracking area code*/
   U32 enbIPAddr;                /*enodeb address*/
   U32 mmeId;                    /*mme id*/
   U32 mmeAddr;                  /*mme code*/
   U32 sctpIPAddr;               /*sctp address*/
   U8 enbName[MAX_ENB_NAME_LEN]; /*enodeb name*/
   U8 plmnId[6];                 /*plmn*/
   U32 heartBeatInterval;        /*sctp heartbeat timer value*/
   U32 rtoInitial;               /*sctp rto initial*/
   U32 rtoMin;                   /*sctp rto min*/
   U32 rtoMax;                   /*sctp rto max*/
   U32 s1PrepTimerVal;           /*s1 preparation timer value*/
   U32 s1OverallTimerVal;        /*s1 overall timer value*/
   U8 sctpUdpServiceType;        /*sctp server type*/
   U32  inactvTmrVal;            /* inactivity timer value */
   U32  maxExpires;              /* maximum number of timer expiry */ 
   U16  s1SetupTmr;              /* s1 setup timer */
   U16  noOfSctpInStreams;       /* No of In SCTP Streams */
   U16  noOfSctpOutStreams;      /* No of Out SCTP Streams */
   S8   ueEthIntf[10];
   U32  numOfEnbs; /* Max number of enbs supported */
}NbAppCfgCb;

typedef enum {
   TFW_IP_ADDR,
   MAX_TFW_CFG_PARAM
}tfwAppCfgTagNum;

typedef enum {
   TRF_GEN_IP_ADDR,
   NAS_PROC_GUARD_TIMER,
   NUM_OF_UE,
   MAX_UE_APP_CFG_PARAM
}ueAppCfgTagNum;

typedef enum {
   CELL_ID,
   TAC,
   ENB_IP_ADDR,
   MME_ID,
   MME_ADDR,
   SCTP_IP_ADDR,
   ENB_NAME,
   PLMN_ID,
   HEARTBEAT_INTERVAL,
   RTO_INITIAL,
   RTO_MIN,
   RTO_MAX,
   S1_PREP_TIMER_VAL,
   S1_OVERALL_TIMER_VAL,
   SCTP_UDP_SERVICE_TYPE,
   INACTIVITY_TIMER_VAL,
   MAX_EXPIRY,
   S1_SETUP_TMR_VAL,
   NO_OF_SCTP_IN_STREAMS,
   NO_OF_SCTP_OUT_STREAMS,
   UE_ETH_INTF,
   VS_IP_ADDR,
   MAX_NB_CFG_PARAM
}nbAppCfgTagNum;

typedef enum {
   ALGO_TYPE,
   OP_ID,
   UE_NW_CAP,
   AUTH_TYPE,
   OP_KEY,
   SHARED_KEY,
   NAS_CYPH_CFG,
   NAS_INT_PROT_CFG,
   SRV_PLMN,
   LAST_MCC,
   LAST_MNC,
   LAST_TAC,
   MCC,
   MNC,
   MME_GRP_ID,
   MME_CODE,
   MTMSI,
   PDN_TYPE,
   PDN_APN,
   UE_RAD_CAP_RRC_PDU_LEN,
   UE_RAD_CAP_RRC_PDU,
   MAX_UE_CFG_PARAM
}ueCfgTagNum;
