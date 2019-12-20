/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

/**********************************************************************

    Name:  LTE UESIM - Sample Application Module 
 
    Type:  C include file
 
    Desc:  C source code for UE Sample Application
 
    File:  ueAppdbm.x 
 
    Sid:      
 
    Prg:    
 
**********************************************************************/
#include "cm_llist.h"      /* cm link list */
#include "cm_llist.x"      /* cm link list */
#include "cm_hash.h"
#include "cm_hash.x"
#include "ue_emm.h"
#include "ue_esm.h"
#include "ue_emm.x"
#include "ue_esm.x"
#include "ue.h"
#include "ue_app_sec.h"
#include "ue_app_sec.x"
#include "ue_usim_auth.h"
#include "ue_usim_auth.x"

#define MAX_NUM_OF_UE_CFD 5
#define MAX_IMSI_LEN 15
#define MAX_IMEI_LEN 16


/* Supported UE Authentication Algorithm structure */
typedef enum
{
   UE_AUTH_XOR, /**< XOR Authentication algorithm >**/
   UE_AUTH_MILENAGE /**< MILENAGE Authentication algorithm >**/
}enumUeAuthAlgo;

/* NAS Procedure Timers configration structure */
typedef struct _nasTmrCfg
{
    Bool enable; /**< Identifies the enabling of timer >**/
    U16 val; /**< timer value >**/
}NasTmrCfg;

typedef enum _cipheringType
{
   UE_CIPHERING_TYPE_EEA0,
   UE_CIPHERING_TYPE_EEA1,
   UE_CIPHERING_TYPE_EEA2
}enumCipheringType;

typedef enum _integrityType
{
   UE_INTEGRITY_TYPE_EEA1,
   UE_INTEGRITY_TYPE_EEA2
}enumIntegrityType;

/* NAS security algorithm configuration for Ciphering and intgerity structure */
typedef struct _nasSecurityCfg
{
      /* Ciphering */
      enumCipheringType cipheringType;
      enumIntegrityType integrityType;
}NasSecurityCfg;

/* UE Network capability */
typedef struct _ueNwCap
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
}UeNwCap;

typedef struct _ueConfigInfo
{
   U8 ueId;       /*ue identity*/
   U8 imsi[MAX_IMSI_LEN];       /*Mobile subscriber identity*/
   U8 imei[MAX_IMEI_LEN];       /*Mobile equipment identity*/
   U8 NASCyphCfg;          /*eea0, eea1, eea2*/
   U8 NASIntProtCfg;       /*eia1, eia2*/
   U8 algoType;   /*Identifies the sucurity alogoritm supported*/
   U32 opId;      /*operator identity*/
   U8 authType;   /*Auth type- XOR, Milenage*/
   U32 authKey;   /*authentication key*/
   UeNwCap ueNwCap;   /*ue network capability*/
}UeConfigInfo;

/* UeEmmState EPS Mobility Management States */
typedef enum _ueEmmState
{
   UE_EMM_UE_NULL = 0,       /* UE NULL */
   UE_EMM_UE_DEREGISTERED ,  /* UE Deregistered */
   UE_EMM_UE_REG_INIT,       /* UE Registration Initiated/In progress */
   UE_EMM_UE_REGISTERED,     /* UE Registered */
   UE_EMM_UE_DEREG_INIT      /* UE Deregister Initiated */
}UeEmmState;

typedef struct ueEmmCb
{
   UeEmmState state; /* State of this UE involved in EMM procedure. */
   Bool       esmPiggyBacked; /* Flag to indicate if Default EPS bearer needs
                                 to be established with ESM piggybacked on
                                 EMM message */
}UeEmmCb;

typedef enum ueEcmState
{
   UE_ECM_IDLE = 0,          /* UE ECM IDLE */
   UE_ECM_CONNECTED          /* UE ECM_CONNECTED */
}UeEcmState;
	
typedef enum ueTransState
{
   UE_DETACHED = 0,              /* UE Detached */
   UE_ATCH_WAIT_AUTH_REQ,        /* UE Attach request sent */
   UE_ATCH_WAIT_SECMODECMD,      /* UE Auth response sent */
   UE_ATCH_WAIT_ATCHACCPT        /* UE Sec mode complete sent */
}UeTransState;

typedef struct ueAppNwId
{
   U8   mcc[3];  /* MCC */
   U8   mnc[3];  /* MNC */
}UeAppNwId;

typedef struct ueAppGUMMEI
{
   UeAppNwId  nwId;           /* Serving Network with PLMN ID */ 
   U8         mmeCode;        /* MME Code */
   U16        mmeGrpId;       /* MME Group ID */ 
}UeAppGUMMEI;

typedef struct ueAppInfo
{
   UeAppGUMMEI   gummei;     /* GUMMEI of serving MME for this UE */
   U8            imsiLen;    /* len of IMSI=MCC+MNC+MSIN */
   U8            ueImsi[CM_EMM_MAX_IMSI_DIGS]; /* IMSI of UE */
   U8            ueImei[CM_EMM_MAX_IMEI_DIGS]; /* Mobile equipment identity */
   GUTI          ueGuti;      /* Guti allocated to this UE from MME  */
   CmEmmTaiLst   *taList;     /* Tracking Area List for this UE from MME */
   CmEmmUeNwCap  ueNwCap;     /* Network capability of UE */
   CmEmmUeSecCap ueSecCap;    /* UE security capability */
   CmEmmUeRadCap ueRadCap;    /* UE Radio capability */
   U8            rnd[16];
   U8            msId[CM_EMM_MAX_MOBILE_ID_DIGS];
   CmInetNetAddr selfAddr;
}UeAppInfo;

typedef struct ueEcmCb
{
   UeEcmState    state;      /* ECM state */
}UeEcmCb;

typedef enum ueEsmBearerCtxtState
{
   UE_ESM_ST_BEARER_CTXT_INACTIVE = 0,   /* Bearer Inactive */
   UE_ESM_ST_BEARER_CTXT_ACTIVE          /* Bearer Active */
}UeEsmBearerCtxtState;

typedef enum ueEsmProcTxnState
{
   UE_ESM_ST_PROC_TXN_INACTIVE = 0,   /* Procedure Transaction Inactive */
   UE_ESM_ST_PROC_TXN_PENDING         /* Procedure Transaction Pending */
}UeEsmProcTxnState;

typedef enum ueAppEsmKeyType
{  UE_ESM_TRANS_KEY,
   UE_ESM_BID_KEY
}UeAppEsmKeyType;

typedef struct ueEsmCb
{
   UeEsmBearerCtxtState bState;  /* EPS Bearer context state */
   UeEsmProcTxnState    pState;  /* Procedure transaction state */
   U8                   bId;     /* EPS bearer identity */
   U8                   tId;     /* Procedure transaction identity */
} UeEsmCb;

typedef struct _ueAppCb_TxId
{
   U32 rrc_con_setupTxId;
   U32 rrc_Sec_ModeTxId;
   U32 rrc_Cap_InfoTxId;
}ueAppCb_TxId;

typedef enum _beareType
{
   DEFAULT_BEARER = 1,
   DEDICATED_BEARER
}BearType;

typedef struct _ueRabCb
{
   U8                drbId;
   BearType          bearerType;
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
   U8                epsBearerId;
   U8                lnkEpsBearId;
   CmEsmTft          tft;
} UeRabCb;

typedef struct _ueCb
{
   UeAppInfo   ueCtxt;       /* Addtional UE Information for this UE */
   UeEmmCb     emmCb;        /* EMM Context for this UE */
   UeEcmCb     ecmCb;        /* ECM Context for this UE */
   /* TRANS List of ESM Cbs. BID range is 5-15 */
   UeEsmCb     *esmTList[CM_ESM_MAX_BEARER_ID];
   /* BID List of ESM Cbs. BID range is 5-15 */
   UeEsmCb     *esmBList[CM_ESM_MAX_BEARER_ID];
   U32         transIdCntr;   /* Transaction counter for sending the 
                                 ESM Procedural transactions. */
   U16         cellId; /* cellId */
   U16         ueId;   /* ueId */
   U8          nasEsmState;  /* NAS State */
   U8          hoState;      /* HO State */
   Bool        drpSecMode;
   U8          epsAtchRes;
   U16          t3412;
   U8          t3402;
   U8          t3423;
   U8          t3346;
   U8          emmCause;
   CmEmmPlmnId plmnLst[CM_EMM_MAX_PLMN_LIST];
   ueAppCb_TxId rcvdTxId;
   UeAppSecCtxtCb    secCtxt;
   UeUsimUeAuthInfo  ueInfo;
   UeUsimAuthKeys    ueAuthKeys;
   U8                srvPlmn[3];
   CmEmmAuthFailure  authFlr;
   CmEmmAuthPrmRES   res;
   UeRabCb ueRabCb[UE_APP_MAX_DRBS];
   U8      numRabs;
   U8      drbs[UE_APP_MAX_DRBS];
   U8      gutiChanged;
   CmHashListEnt     ueHashEnt;
   Bool    is_actv_dflt_eps_ber_ctxt_rej;
   U8      actv_dflt_eps_bear_ctxt_reject_cause;
}UeCb;


typedef struct _ueAppCb
{
   TskInit          init;       
   Pst              nbPst;
   Pst              fwPst;
   U32              trfGenIfAddr; /* IP address of eth port connected to 
                                     traffic generator*/
   U8               NASProcGuardtimer; /* timer value */
   U32              numOfUeCfgd;
#ifdef UEHASHLIST
   CmHashListCp     ueLstCp; /*!< Hashlist of UeCb */
#else
   UeCb             *ueCbLst[UE_APP_MAX_NUM_OF_UES];
   U8               numOfUesInLst;
#endif
}UeAppCb;

PUBLIC UeAppCb gUeAppCb;
