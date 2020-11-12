/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

/**********************************************************************

    Name:  LTE S1SIM - ENODEB Application Module

     Type:     C include file

    Desc:  C source code for ENODEB Application

    File:  nb.h

    Sid:

    Prg:

**********************************************************************/

#ifndef __NB_H__
#define __NB_H__

#ifdef __cplusplus
extern "C" {
#endif

/* header include files (.h) */
#include "envopt.h"        /* Environment options */
#include "envdep.h"        /* Environment dependent */
#include "envind.h"        /* Environment independent */

#include "gen.h"           /* General */
#include "ssi.h"           /* System services */
#include "cm5.h"           /* Common timer defines */
#include "cm_tkns.h"       /* Common tokens defines */
#include "cm_mblk.h"       /* Common memory allocation library defines */
#include "cm_llist.h"      /* Common link list  defines  */
#include "cm_hash.h"       /* Common hashlist  defines */
#include "cm_lte.h"        /* Common LTE defines */
#include "cm_inet.h"
#include "cm_tpt.h"
#include "cm_dns.h"

/* header/extern include files (.x) */
#include "gen.x"           /* General */
#include "ssi.x"           /* System services */

#include "cm5.x"           /* Common timer library */
#include "cm_tkns.x"       /* Common tokens */
#include "cm_mblk.x"       /* Common memory allocation */
#include "cm_llist.x"      /* Common link list */
#include "cm_hash.x"       /* Common hashlist */
#include "cm_lte.x"       /*  Common UMTS includes */
#include "cm_lib.x"
#include "cm_inet.x"
#include "cm_tpt.x"
#include "hit.h"
#include "sct.h"
/* header include files related to lower layer interfaces */
#include "szt.h"           /* S1AP RRM control Interface */
#include "szt_asn.h"
#include "nb_lnb.h"
#include "egt.h"           /* DATA app, GTP interface   */
#include "nbu.h"
#ifdef SZTV3
#include "szt_3gasn.h"
#endif

#include "cm_lte.x"
#include "sct.x"
#include "szt_asn.x"       /* S1AP RRM control Interface */
#ifndef SZ_ENC_DEC
#include "szt_pk.x"
#include "szt_unpk.x"
#endif /* SZ_ENC_DEC */
#ifdef SZTV3
#include "szt_3gasn.x"
#endif
#include "szt.x"           /* S1AP RRM control Interface */

#include "egt.x"           /* DATA app, GTP interface   */
#include "nbu.x"
#include "ss_diag.h"


#define NB_MAX_HASH_SIZE        1024
#if (defined(NB_DBG_CIRLOG) || defined(SS_SEGV_SIG_HDLR))
#include "wr_dbg_log.h"
#endif /* WR_DBG_LOGS */
#ifdef RLOG_REDIRECT
#define NB_REDIRECT_RLOGS 1
#endif /* NB_DBG_LOGS */
typedef U32                  NbMmeId;
#define NB_ENB_NAME          151
#define NB_MAX_MMES          16
#define NB_MME_INITED        0
#define NB_MME_IN_PROG       1
#define NB_MME_UP            2
/* macros(#defines) */
#define NB_SRC_PROC_ID                 1
#define NB_DST_PROC_ID                 0
#define NB_MAX_PLMNS_PER_MME 32
#define NB_MAX_GRPS_PER_MME  256
#define NB_MAX_CODES_PER_MME 256

#define NB_MAX_GUMMEI_PER_MME 256
#define NB_PLMNID_IE_LEN     3          /* Octets */
#define NB_LAC_IE_LEN        2
#define NB_NUM_TQENTRY                 100
#define NB_MAX_SAPS                    10
#define NB_MEM_REGION                  0
#define NB_MEM_POOL                    0

#define NBLAYERNAME                    "EnodeB APP"

#define NB_CALC_WAIT_TIME(_delay) (_delay/((1000/SS_TICKS_SEC) * nbCb.timeRes))

#define NB_NUM_EGT_SAPS  1
#define NB_NUM_SZT_SAPS  1

#define NB_TMR_INITIAL_CTX_REQ_TMR_VAL 10000
#define NB_TMR_UE_CTX_REL_VAL          10000
#define NB_MAX_TMR_PER_UE              1
#define NB_DFLT_EGTP_PORT              2152

#define NB_INIT_STATE                  0

#define NB_SI_CNT                      4

#define NB_BYTE_LEN                    8
#define NB_TRAC_LEN                    16

#define NB_MEM_PDU_SIZE                4084

#define NB_MAX_SRBS                    2

#define NB_S1_SETUP_DONE               1
#define NB_S1_CONNECTING               2
#define NB_S1_CONNECTED                3
/* Multi eNB support */
#ifdef MULTI_ENB_SUPPORT
#define NB_MAX_S1AP_CON                MAX_UE_INST
#define NB_MAX_UE_SUPPORTED            MAX_UE_INST
#else
#define NB_MAX_S1AP_CON                100
#define NB_MAX_UE_SUPPORTED            32
#endif

#define NB_MAX_TUNN_PER_UE             2

/*#define SZ_MAX_MSG_ID                  63*/
#define SZ_MEM_SDU_SIZE                2048
#define NB_SZ_MEM_SDU_SIZE             2048
#define WR_PLMNID_IE_LEN     3          /* Octets */


#define NB_S1AP_NOT_CONNECTED          0
#define NB_S1AP_CONNECTING             1
#define NB_S1AP_CONNECTED              2

/* incoming msgtype for ue s1ap handling */

#define NB_S1_CON_CFM  1
#define NB_S1_DAT_IND  2
#define NB_S1_REL_IND 3

#define NB_UE_CTXT_REL_INACTIVITY 0

#define NB_CAUSE_RADIONW     0
#define NB_CAUSE_TRANSPORT   1
#define NB_CAUSE_NAS         2
#define NB_CAUSE_PROTOCOL    3
#define NB_CAUSE_MISC        4

#define NB_ZERO  0
#define NB_ONE   1
#define NB_TWO   2
#define NB_THREE 3
#define NB_100   100
#define NB_200   200

/* Maximum PAGING tti reference time. This is used when difference is taken
 * between the current time and the time in which paging message has been
 * received. Once we reach this value, will be starting from zero.
 * */
#define NB_PAGING_TTI_TIME        10240
#define NB_DEFAULT_PAGING_PRI        255

#define NB_MAX_PLMN_ID               6
#define NB_MAX_NUM_BPLMNS            5
#define NB_MAX_NUM_CSG_ID          256
#define NB_MAX_NUM_TAC             256

/* eNodeB types */
#define NB_ENODEB_TYPE_MACRO      0x00
#define NB_ENODEB_TYPE_HOME       0x01

#define NB_MAX_PLMNS_PER_MME        32
#define NB_MAX_GRPS_PER_MME        256
#define NB_MAX_CODES_PER_MME       256

/* PDN types */
#define NB_PDN_IPV4 1
#define NB_PDN_IPV6 2
#define NB_PDN_IPV4V6 3
#define NB_IPV6_ADDRESS_LEN 16
#define NB_IPV4_VERSION 4
#define NB_IPV6_VERSION 6
// NB_TMR_ROUTER_SOLICIT_VAL in seconds
#define NB_RTR_SOLICITATION_INTERVAL 4000
#define NB_MAX_RTR_SOLICITATIONS_RETRY 2

EXTERN U16 szElmSize[][SZT_MAX_PROC_ID];
typedef struct _nbUeCb _nbUeCb;

typedef struct _nbErabCb
{
 U8            erabId;
 U32           lclTeid;
 U32           remTeid;
 TknStrOSXL   *nasPdu;
}NbErabCb;

typedef struct _nbUeMsgCause
{
   U32    causeTyp;
   U32    causeVal;
}NbUeMsgCause;
typedef struct _nbErabLst
{
   U8 noOfComp;
   NbErabCb *erabs;
}NbErabLst;

typedef struct NbFailedErab {
  U8 erabId;
  U8 qci;
#define CAUSE_RADIONW_QCI_UNSUPPORTED 37
  NbUeMsgCause cause;
} NbFailedErab;

typedef struct _nbFailedErabLst {
  U8 noOfComp;
  NbFailedErab *failedErabs;
} NbFailedErabLst;

typedef struct _nbErabRelLst
{
   U32 ueId;
   U32 mmeUeS1apId;
   U32 enbUeS1apId;
   U8 numOfErabIds;
   U8 *erabIdLst;
   TknStrOSXL nasPdu;
}NbErabRelLst;

typedef struct _nbDelayICSRspCb
{
 U32 ueId;
 NbErabLst *erabInfo;
 CmTimer   timer;
}NbDelayICSRspCb;

typedef struct _nbDelayUeCtxtRelCmpCb
{
 U32 ueId;
 CmTimer   timer;
}NbDelayUeCtxtRelCmpCb;

typedef enum nbTmr
{
   NB_TMR_SZT_SAP_BND = 1,
   NB_TMR_EGT_SAP_BND,
   NB_TMR_INACTIVITY,
   NB_TMR_S1_RELOC_TMR,
   NB_TMR_S1_OVRL_TMR,
   NB_TMR_MME_SETUP_RSP,
   NB_TMR_MME_SETUP_WAIT,
   NB_TMR_INITIAL_CTX_REQ,
   NB_TMR_END_MARKER_TMR,
   NB_TMR_UE_CTX_REL_REQ,
   NB_TMR_LCL_UE_CTXT_REL_REQ,
   NB_TMR_DELAY_ICS_RSP,
   NB_TMR_DELAY_UE_CTX_REL_COMP,
   NB_TMR_ROUTER_SOLICIT
} enNbTimer;

typedef struct _nbS1ConnCb
{
   UConnId                   suConnId;
   UConnId                   spConnId;
   U32                       mme_ue_s1ap_id;
   U32                       enb_ue_s1ap_id;
   U8                        s1apConnState;
   U32                       nmbERAB;
   _nbUeCb                    *ueCb;
   SztCause                  cause;
}NbS1ConCb;

typedef struct _nbUeTunInfo
{
  CmHashListEnt  ueHashEnt;
  U32            lclTeId;
  U32            remTeId;
  U32            bearerId;
  CmTptAddr      sgwAddr;
}NbUeTunInfo;

struct _nbUeCb
{
   CmHashListEnt ueHashEnt;
   U32 ueId;
   U32  ueIdx;
   NbS1ConCb   *s1ConCb;
   U8 tunnIdx;
#if 0
   NbUeTunInfo *tunnInfo[11];
#else
   CmHashListCp   tunnInfo;
#endif
   CmTimer   timer;
   /* Multi eNB support */
   U32 enbId;
#ifdef MULTI_ENB_SUPPORT
   U16 encryptionAlgo;//Updated from ICS Req
   U16 integrityAlgo;//Updated from ICS Req
#endif
};

typedef struct _nbUeCb NbUeCb;

/** @brief This structure contains information about the Application's lower
 * SAP.
 - Pst        pst          Post structure
 - SuId       suId         Service user ID
 - SpId       spId         Service provider ID
 - State      sapState     SAP State (Bound/Unbound)
 - Mem        mem          Region/Pool
 - CmTimer    timer        Timer for Bind
 - U8         bndRetryCnt  Number of Bind Retrys
 - U8         maxBndRetry  Max number of Bind Retrys
 - TmrCfg     bndTmr       Bind Timer configuration
 */
typedef struct NbLiSapCb
{
   Pst                       pst;
   SuId                      suId;
   SpId                      spId;
   State                     sapState;
   Mem                       mem;
   CmTimer                   timer;
   U8                        bndRetryCnt;
   U8                        maxBndRetry;
   TmrCfg                    bndTmr;
} NbLiSapCb;
typedef struct _nbPlmnId
{
   U8                        numMncDigits;
   U8                        mcc[3];
   U8                        mnc[3];
}NbPlmnId;
typedef struct _nbTai
{
   NbPlmnId                  plmnId;
   U16                       tac;
} NbTai;

typedef struct _NbTmrCfg
{
   U32                       s1SetupTmr;
}NbTmrCfg;

typedef struct _nbMmeName
{
   U8 len;
   U8 val[150];
}NbMmeName;

typedef struct _NbmmeCb
{
   NbMmeId mmeId;
   U32  mmeAddr;
   U32 peerId;
   CmTimer   timer;
   U8 state;
   U8                        numPlmnIds;
   NbPlmnId                  plmnIds[NB_MAX_PLMNS_PER_MME];
   U16                       numGrpIds;
   U16                       groupIds[NB_MAX_GRPS_PER_MME];
   U16                       numCodes;
   U8                        codes[NB_MAX_CODES_PER_MME];
   U8                        relCapacity;
   NbMmeName                 mmeName;
   U32                       mmeRelaySuppInd;
}NbMmeCb;

typedef struct _nbMmeCont
{
   U8         numMmes;
   NbMmeCb    mmes[2];
}NbMmeCont;

typedef struct _nasNonDelCfg
{
   U8 flag;
   U32 causeType;
   U32 causeVal;
}NasNonDelCfg;
typedef struct _initCtxtSetupFailCfg
{
   Bool initCtxtSetupFailInd;
   U32 causeType;
   U32 causeVal;
}InitCtxtSetupFailCfg;
typedef struct _dropInitCtxtSetupCfg
{
   CmTimer   timer;
   Bool isDropICSEnable;
   Bool isICSReqDropped; /* if the ICS request is already dropped,do not process retransmitted ICS Req */
   U32   tmrVal; /* timer to release the UE Context on expiration */
}DropInitCtxtSetupCfg;
typedef struct _delayInitCtxtSetupRspCfg
{
   Bool delayICSRsp;
   U32   tmrVal; /* timer to release the UE Context on expiration */
}DelayInitCtxtSetupRspCfg;

typedef struct _delayUeCtxtRelCmpCfg
{
   Bool delayUeCtxRelComp;
   U32   tmrVal; /* timer to release the UE Context on expiration */
}DelayUeCtxtRelCmpCfg;
typedef struct _dropICSSndCtxtRelCfg
{
   Bool sndICSRspUeCtxtRel;
   U32 causeType;
   U32 causeVal;
}DropICSSndCtxtRelCfg;

typedef struct _InitCtxtSetupFailedErabs {
#define MAX_FAILED_ERABS 11
#define CAUSE_TRANSPORT_RESOURCE_UNAVAILABLE 0
  U8 numFailedErabs;
  U8 failedErabs[MAX_FAILED_ERABS];
  NbUeMsgCause cause;
} InitCtxtSetupRspFailedErabs;

typedef struct _EnbCb
{
   CmHashListEnt nbHashEnt;
   U32 enbId;
   U32 cell_id;
   U32 tac;
   NbPlmnId plmnId;
   U32 enbType;
   U8 plmn_length;
} EnbCb;
typedef struct _mutilEnbCfgInfo
{
   Bool pres;
   U8   numOfEnbs;
}MutilEnbCfgInfo;

typedef struct _dropRA {
   Bool isDropRA;
} DropRA;

typedef struct _nbRouterSolicitCb {
#define NB_EGTP_MSG_SZ   1024
  U32 ueId;
  U8 *ip6Addr;
  U32 epsBearId;
  Void *tnlCb;
  U8 rs_buff[NB_EGTP_MSG_SZ];
  U8 rs_len;
  U8 counter;
  CmTimer timer;
} NbRouterSolicitCb;


typedef struct _nbCb
{
   Mem mem; /* memory pool info */
   TskInit                   init;
   Header                    lmHdr;
   UConnId                   s1apConId; /* Last used connection id; counter */
   Pst                       ueAppPst;
   NbLiSapCb                 **sztSap;
   CmTqCp                    tqCp;           /* Timing Queue Control point    */
   CmTqType                  tq[NB_NUM_TQENTRY]; /* Timing Queue for a resln. */
   Ticks                     timeRes;       /* Time resolution */
   U32                       s1UStatus;
   CmTptAddr                 datAppAddr;
   NbMmeCb                   mmeInfo;
   U32                       cellId;
   NbTmrCfg                  tmrCfg;
   U8                        enbType;
   U8                        numOfEnbs;
   U32                       enbId;
   MutilEnbCfgInfo           multiEnbCfgInfo;
#if 0
   NbUeCb                    *ueCbLst[NB_MAX_UE_SUPPORTED];
   U8                        crntUeIdx;
#endif
   CmHashListCp              ueCbLst;
   CmHashListCp              eNBCbLst;
   U16                       tac;
   NbPlmnId                  plmnId;
   Pst                       nbDamPst;
   NasNonDelCfg              nasNonDel[NB_MAX_UE_SUPPORTED];
   InitCtxtSetupFailCfg      initCtxtSetupFail[NB_MAX_UE_SUPPORTED];
   DropInitCtxtSetupCfg      dropInitCtxtSetup[NB_MAX_UE_SUPPORTED];
   DelayInitCtxtSetupRspCfg  delayInitCtxtSetupRsp[NB_MAX_UE_SUPPORTED];
   DropICSSndCtxtRelCfg      dropICSSndCtxtRel[NB_MAX_UE_SUPPORTED];
   DelayUeCtxtRelCmpCfg      delayUeCtxtRelCmp[NB_MAX_UE_SUPPORTED];
   InitCtxtSetupRspFailedErabs  initCtxtSetupFailedErabs[NB_MAX_UE_SUPPORTED];
   DropRA                       dropRA[NB_MAX_UE_SUPPORTED];
   NbRouterSolicitCb            *rsCb[NB_MAX_UE_SUPPORTED];
#ifdef MULTI_ENB_SUPPORT
   Bool                      x2HoDone;
#endif
}NbCb;
/** @brief This structure is temparerly store on stack which contains
 * UE specific Paging Message information.
 */
typedef struct _nbPagingMsgInfo
{
   U8      ueIdenType;    /*!< UE-identity in paging record is
                               either IMSI type or S-TMSI type */
   union
   {
      NbuSTmsi  sTMSI;      /*!< S-TMSI of the UE*/
      U8       imsi[22];   /*!< IMSI of the UE. IMSI size is
                             min-6 Integer digits and
                             max-21 Integer Digits.As we are using
                             the first index for the storing
                             the length of IMSI */
   } ueIden;     /*!< It contians either IMSI or S-TMSI */
   U32     ue_Id;   /*!< UE-Id used for paging frame calculation*/
   Bool    pagingDrxPres;   /*!< set to TRUE, if UE specific DRX cycle present,
                                 otherwise set to FALSE */
   U8      ueSpcPagDrx; /* UE specific DRX Cycle */
   U8      domIndType;   /*!< Domain indication is either PS or CS
                              which is received thru S1-AP paging message*/
   U8      pagPriority;  /*!< Priority of paging Message */
} NbPagingMsgInfo;

typedef struct _nbResetMsgInfo
{
   U8 type;
   NbUeMsgCause cause;
   U32 s1apIdCnt;
   U32 *enbUeS1apIdLst;
   U32 *mmeUeS1apIdLst;
   U32 enbId;
}NbResetMsgInfo;

typedef struct _nbResetAck
{
   U8 status;
   U32 numOfUes;
   U32 *ueIdLst;
}NbResetAck;

#define NB_GET_S1AP_CON_ID(_suConId,_ptr) {\
       _suConId = ((nbCb.cellId & 0xFFFF) << 16)\
                  |(_ptr->ueId & 0xFFFF);\
}

#define NB_FREE(_buf, _size)          \
{\
      (Void) SPutSBuf(NB_MEM_REGION, NB_MEM_POOL, (Data *) _buf, (Size) _size); \
      (_buf) = NULLP;\
}
/* allocate memory for members in the event structure */
#define NB_GET_MEM(_memPtr, _size, _allocPtr)\
{\
   (*_allocPtr) = NULLP;    \
   if(cmGetMem((U8 *)_memPtr, _size, (Ptr *)_allocPtr) != ROK)    \
   {                                                              \
      RETVALUE(RFAILED);                                         \
   }                                                              \
}
#ifndef NB_DBG_CIRLOG
#define NB_PRNT_BUF                    nbCb.init.prntBuf
#else
/* Currently passing index as zero, when multiple system tasks are used then
 * retrieve the corresponding circular buffer for that system task.
 */
#define NB_PRNT_BUF                    nbCb.init.prntCirBuf, MAX_LOG_BUF_SIZE
#endif /* NB_DBG_CIRLOG */
#define DBGMASK_SM                     1
#define NB_EVEBASE                     0
#define NB_ERRVE                       (NB_EVEBASE + 0)  /* reserved */
#define NB_EVE001                      (NB_ERRVE + 1) /* ve_sm_hi_exms.c: 241 */

#define NB_PRSNT      1
#define NB_NOTPRSNT   0

/*129311 : Scheduler default k value for Wideband Cqi report should be non zero*/
#define NB_DFLT_K_VAL_FOR_SCH 1

/* ccpu00133012:The UL Carrier Frequency is derived for DL Carrier Frequency. The
   difference is sepc defined gievn in 36.101. But this specific requirement is to
   cater the KT requirement.
*/
#define NB_SET_ZERO(_buf, _size) \
{\
      cmMemset((U8 *)(_buf), 0, _size);\
}
#define NB_ALLOC(_buf, _size)         \
{\
      if (SGetSBuf(NB_MEM_REGION, NB_MEM_POOL, (Data **)(_buf), _size) == ROK)\
      {                                                         \
               NB_SET_ZERO((*_buf), _size);                           \
      } \
}
#define NB_FREEMBUF(_mBuf)                            \
   do{                                                   \
      if (_mBuf != NULLP)                                \
      {                                                  \
         (Void)SPutMsg((_mBuf));                            \
         (_mBuf) = NULLP;                                   \
      }                                                  \
   }while(0)
/* free allocated memory for an event structure */
#define NB_FREE_EVNT(_evntPtr)  \
{   \
      cmFreeMem((Ptr *)(_evntPtr));   \
      (_evntPtr) = NULLP;  \
}

/** Defines Logging Levels */
#define LNB_LOGLVL_DISABLE  0
#define LNB_LOGLVL_FATAL    1
#define LNB_LOGLVL_ERROR    2
#define LNB_LOGLVL_WARN     3
#define LNB_LOGLVL_INFO     4
#define LNB_LOGLVL_DEBUG    5
#define LNB_LOGLVL_TRACE    6
#define LNB_ERR_INV_LOG_LVL 7
#define LNB_LOGLVL_ALL   LNB_LOGLVL_TRACE
#define LNB_LOGLVL_TRACE    6
#define LNB_LOGLVL_ALL   LNB_LOGLVL_TRACE
/*************************************************************************
* Debug print                                                            *
*************************************************************************/
#define NB_ERROR 1

#ifdef NB_DBG_CIRLOG
#define NB_DBGP(_msgClass, _arg) \
{\
   DBGP_CIRLOG(&(nbCb.init), NBLAYERNAME": ", _msgClass, _arg); \
}
#else /* NB_DBG_CIRLOG */

#ifdef DEBUGP
#if (NB_SM_LOG_TO_FILE && DEBUGP)
#define NB_DBGP(_msgClass, _args)                               \
   do                                                             \
   {                                                              \
      if(smCfgCb.init.dbgMask)                                       \
      {                                                           \
         if((smCfgCb.dbgFp == NULLP) ||                              \
               (smCfgCb.nmbDbgLines == smCfgCb.cfgDbgLines))            \
         {                                                        \
            nbSmCreateDbgFile();                                  \
         }                                                        \
         sprintf(SM_PRNT_BUF, "[%s 0x%x:%x] %s:%d ",              \
               SMLAYERNAME,smCfgCb.init.ent, smCfgCb.init.inst,         \
               __FILE__, __LINE__);                               \
         fwrite((SM_PRNT_BUF),cmStrlen((U8*)SM_PRNT_BUF), 1,      \
               (smCfgCb.dbgFp));                                     \
         sprintf _args;                                           \
         fwrite((SM_PRNT_BUF),                                    \
               cmStrlen((U8*)SM_PRNT_BUF), 1,                     \
               (smCfgCb.dbgFp));                                     \
         smCfgCb.nmbDbgLines++;                                      \
      }                                                           \
   }                                                              \
   while(0)

#else /* (NB_SM_LOG_TO_FILE && DEBUGP) */
#define NB_DBGP(_msgClass, _arg) \
   {\
      DBGP(&nbCb.init, NBLAYERNAME": ", _msgClass, _arg); \
   }
#endif /* (NB_SM_LOG_TO_FILE && DEBUGP) */
#else
#define NB_DBGP(_msgClass, _arg)
#endif
#endif /* NB_DBG_CIRLOG */
/* initialize the memCp & allocate memory for the event structure */
#define NB_ALLOCEVNT(_evntPtr, _size)\
{\
      (*_evntPtr) = NULLP; \
      cmAllocEvnt((Size) _size, NB_MEM_PDU_SIZE, &nbCb.mem,   \
                                 (Ptr *)(_evntPtr));  \
}

EXTERN NbCb                 nbCb;
/*ccpu00129785*/
EXTERN Bool                 memAlarm;

EXTERN S16 nbActvTmr(Void);

EXTERN S16 nbRegInitTmr(Void);

EXTERN S16 nbStartTmr(PTR cb, S16 tmrEvnt, U32 delay);

EXTERN Void nbStopTmr(PTR cb, S16 event);

EXTERN Bool nbIsTmrRunning(CmTimer *tmr, S16 event);

EXTERN  Void nbHandleUeIpInfoReq(U32 ueId,U8 bearerId);

EXTERN Void nbSendLmAlarm(U16 category, U16 event, U16 cause);

EXTERN S16 nbGenerateCfm (Pst *pst, CmStatus  *cfmSts, U8 prim, LnbMngmt *cfm);

EXTERN NbMmeCb *nbGetMmeByPeerId(U8 mmeId);

EXTERN S16 nbUiBuildAndSendDlNasMsg(NbUeCb *ueCb, SztNAS_PDU *nasPdu);

EXTERN S16 nbUiBuildAndSendPagingMsg(NbPagingMsgInfo *pagMsgInfo);

EXTERN S16 nbSendInitCtxtSetupRcvInd(NbUeCb *ueCb, NbErabLst *erabInfo,
      Bool ueRadCapRcvd);

EXTERN S16 nbSendS1RelIndToUeApp(U32 ueId);

EXTERN S16 nbBuildAndSendS1SetupReq(NbMmeId mmeId);

EXTERN S16 nbBuildAndSendResetRequest(NbResetMsgInfo *resetMsgInfo);

EXTERN S16 nbBuildAndSendErabRelInd(U32 enbUeS1apId, U32 mmeUeS1apId,
      U8 numOfErabIds, U8 *erabIdLst);

EXTERN S16 nbBuildAndSendErabRelRsp(NbUeCb *ueCb, U32 enbUeS1apId,
                                    U32 mmeUeS1apId, U8 numOfErabIdsRlsd,
                                    U8 *rlsdErabIdLst, U8 numOfErabIdsRlsFld,
                                    U8 *rlsFldErabLst);

EXTERN S16 nbBuildAndSendS1AbortReq(NbMmeId mmeId, U8 cause);

EXTERN S16 nbBuildAndSendS1ShutdownReq(NbMmeId mmeId);

EXTERN S16 nbPrcRcvdPdu(U32 peerId, S1apPdu *pdu);

EXTERN S16 nbPrcS1SetupFail(U16 peerId,S1apPdu *pdu);

EXTERN Void  nbSztFillTAC(U16 tac, S1apPdu *pdu, SztTAC *tAC);
#ifdef MULTI_ENB_SUPPORT
EXTERN S16 nbS1apBldUlNasPdu(NbUeCb *ueCb, TknStrOSXL *nasPdu, S1apPdu **pdu, EnbCb   *enbCb);
#else
EXTERN S16 nbS1apBldUlNasPdu(NbUeCb *ueCb, TknStrOSXL *nasPdu, S1apPdu **pdu);
#endif

EXTERN S16 nbS1apBldUeCapIndPdu(NbUeCb *ueCb, TknStrOSXL *capInfo,
      S1apPdu **pdu);

EXTERN S16 nbPrcIncS1apMsg(NbUeCb *ueCb, S1apPdu *pdu, U8 msgType);

EXTERN S16 nbPrcS1apRelInd(SztRelInd *relInd);

EXTERN S16 nbPrcS1apConCfm(SztConCfm *conCfm);

EXTERN S16 nbPrcS1DatInd(SztDatEvntInd *s1DatInd);

EXTERN S16 nbHandleS1SetupReq(NbMmeId mmeId);

EXTERN S16 nbPrcS1SetupRsp(U32 peerId, S1apPdu *pdu);

EXTERN S16 nbPrcResetAck(U32 peerId, S1apPdu *pdu);

EXTERN S16 nbMmeSetupWaitTmrExpiry(PTR mmeCb);

EXTERN Void  nbParsePlmnIe(SztPLMNidentity *plmnIe, NbPlmnId *plmnId);

EXTERN Void nbAddPlmnId(NbMmeCb *mmeCb, NbPlmnId *plmnId);

EXTERN S16 NbIfmS1apBndReq(Pst *pst, SuId suId, SpId spId);

EXTERN S16 NbIfmS1apUbndReq(Pst *pst, SpId spId, Reason reason);

EXTERN S16 NbIfmS1apSndMgmtMsg(SztUDatEvnt *uDatEvnt);

EXTERN S16 NbIfmS1apSndAbortMsg(SztAbortS1 *abortS1);

EXTERN S16 NbIfmS1apConReq(SztConReq *conReq);

EXTERN S16 NbIfmS1apDatReq(SztDatEvntReq *datEvnt);
#ifdef MULTI_ENB_SUPPORT
EXTERN S16 nbIfmS1apSndUeMsg(U32 spConnId, S1apPdu *s1pdu, U32 enbId);
#else
EXTERN S16 nbIfmS1apSndUeMsg(U32 spConnId, S1apPdu *s1pdu);
#endif

EXTERN S16 NbIfmS1apRelRsp(SztRelRsp *relRsp);

EXTERN S16 NbMiLnbStaReq(Pst *pst, LnbMngmt *cntrl);

#ifdef MULTI_ENB_SUPPORT
EXTERN S16 nbS1apFillEutranCgi(S1apPdu *pdu, SztEUTRAN_CGI *cgiIe, EnbCb*);
#else
EXTERN S16 nbS1apFillEutranCgi(S1apPdu *pdu, SztEUTRAN_CGI *cgiIe);
#endif
EXTERN S16 nbSendErabsInfo(NbUeCb *ueCb, NbErabLst *erabInfo,
                           NbFailedErabLst *failedErabInfo, Bool ueRadCapRcvd);

EXTERN Void nbUiNbuHandleUeInactivity(U32 ueId);

EXTERN Void nbDamSetDatFlag(U32 ueId);

EXTERN S16 nbFillTknStrOSXL1(TknStrOSXL *ptr, U16 len, U32 val,
      CmMemListCp *mem);

EXTERN S16 nbS1apFillCtxtRelReq(NbUeCb *ueCb, S1apPdu **pdu,
      NbUeMsgCause *cause);

EXTERN Void nbHandleUeDelReq(NbUeCb *ueCb);

EXTERN S16 nbSndCtxtRelReq(U32 ueId, NbUeMsgCause *relCause);

EXTERN S16 NbIfmS1apRelReq(SztRelReq *relReq);

EXTERN Void nbUiSendS1TimeOutInd(Void);

EXTERN Void nbUiSendS1TimeOutInd(Void);

EXTERN Void nbUiSendS1SetupFailInd(U8 causeType,U32 causeVal,U32 wait);

EXTERN Void nbRelCntxtInTrafficHandler(U32 ueId);
EXTERN S16 nbHandleDelayTimerForICSExpiry(NbDelayICSRspCb *icsRspCb);

EXTERN S16 nbPrcInitPdu(U32 peerId, S1apPdu *pdu);

PUBLIC S16 nbProcPagingMsg(S1apPdu *s1apPagMsg);

PUBLIC S16 nbProcErabRelCmd(S1apPdu *s1apErabRlsCmd, NbUeCb *ueCb);

PUBLIC Bool nbIsTaiPresent(SztTAILst *taiLst);

PUBLIC Bool nbPlmnPlmnsEqual(NbPlmnId *plmnId1, NbPlmnId *plmnId2);

PUBLIC S16 nbUpdateUePagInfo(S1apPdu *s1apPagMsg, NbPagingMsgInfo *uePagingInfo,
      SztTAILst **pagMsgTAILst, SztCSG_IdLst **pagMsgCSG_IdLst);

PUBLIC S16 nbUiBuildAndSendNasNonDlvryIndToTfw( U32 ueId );

EXTERN S16 nbSendErabsRelInfo(NbErabRelLst *erabInfo, U8 ueId);

EXTERN  S16 nbNotifyPlmnInfo(U32 ueId, NbPlmnId plmnId);
/* Broadcasted PLMN List */
typedef struct _nbBPlmnList
{
   U8 numBPlmns;
   NbPlmnId plmnIds[NB_MAX_NUM_BPLMNS];
}NbBPlmnList;

typedef struct _nbSuppTA
{
   U16 tac;
   NbBPlmnList bPlmnList; /* Broadcasted PLMNs */
}NbSuppTA;

/* ENodeB Type : MAcro NB or Home NB */
typedef struct _nbEnodeBType
{
   U8 pres;
   U8 val;
}NbEnodeBType;

typedef struct _nbSuppTAList
{
   U8 pres;
   U8 numTAs;
   NbSuppTA suppTA[NB_MAX_NUM_TAC];
}NbSuppTAList;

/* CSG Id List */
typedef struct _nbCsgIdList
{
   U8 pres;
   U8 numCsgIds;
   U32 csgId[NB_MAX_NUM_CSG_ID]; /* Bit string, size(27), lower 27 bits used */
}NbCsgIdList;

EXTERN S16 nbPrcInitPdu(U32 peerId, S1apPdu *pdu);

#ifdef SS_DIAG
EXTERN S16 wrDiagPrntIpAddr(U32 ipAddr, U32 diagLvl);
   /* Note: Any changes to these enums should reflect to */
   /** @details Enums for special argument
 *
   */
typedef enum
{
   NB_DIAG_CELLID,
   NB_DIAG_CRNTI,
   NB_DIAG_MMEID,
   NB_DIAG_UEID,
   NB_DIAG_PEERID,
   NB_DIAG_ENBID,
   NB_DIAG_NA
} NbDiagSplArg;

/**
 * @details Macro definition for WR level 0 logs
*/
#define NB_DIAG_LVL0(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)                                                         \
{                                                                                                                                               \
   if(nbCb.init.logMask & SS_DIAG_LVL0)                                                                                                         \
   {                                                                                                                                            \
      ssDiagFix(_tknId, _splArgEnum, ENTNB, nbCb.init.inst, SS_DIAG_LVL0, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }                                                                                                                                            \
}

/**
 * @details Macro definition for WR level 1 logs
*/
#define NB_DIAG_LVL1(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)                                                         \
{                                                                                                                                               \
   if(wrCb.init.logMask & SS_DIAG_LVL1)                                                                                                         \
   {                                                                                                                                            \
      ssDiagFix(_tknId, _splArgEnum, ENTWR, wrCb.init.inst, SS_DIAG_LVL1, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }                                                                                                                                            \
}

/**
 * @details Macro definition for WR level 2 logs
*/
#define NB_DIAG_LVL2(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)                                                         \
{                                                                                                                                               \
   if(wrCb.init.logMask & SS_DIAG_LVL2)                                                                                                         \
   {                                                                                                                                            \
      ssDiagFix(_tknId, _splArgEnum, ENTWR, wrCb.init.inst, SS_DIAG_LVL2, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }                                                                                                                                            \
}

/**
 * @details Macro definition for WR  level 3 logs
*/
#define NB_DIAG_LVL3(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)                                                         \
{                                                                                                                                               \
   if(wrCb.init.logMask & SS_DIAG_LVL3)                                                                                                         \
   {                                                                                                                                            \
      ssDiagFix(_tknId, _splArgEnum, ENTWR, wrCb.init.inst, SS_DIAG_LVL3, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }                                                                                                                                            \
}

/**
 * @details Macro definition for WR  level 4 logs
*/
#define NB_DIAG_LVL4(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)                                                         \
{                                                                                                                                               \
   if(wrCb.init.logMask & SS_DIAG_LVL4)                                                                                                         \
   {                                                                                                                                            \
      ssDiagFix(_tknId, _splArgEnum, ENTWR, wrCb.init.inst, SS_DIAG_LVL4, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }                                                                                                                                            \
}

/**
 * @details Macro definition for TeNB APP Varible length logs
*/
#define NB_DIAG_VAR(_tknId, _splArgEnum, _splArg, _string, _stringPtr)                                                         \
{                                                                                                                              \
   if(wrCb.init.logMask & SS_DIAG_VAR)                                                                                         \
   {                                                                                                                           \
      ssDiagFix(_tknId, _splArgEnum, ENTWR, wrCb.init.inst, SS_DIAG_VAR, SS_DIAG_MSG_TYPE_FIXED, _splArg, 0, 0, 0, 0, _string);\
      ssDiagVarible(ENTWR, wrCb.init.inst, SS_DIAG_VAR, SS_DIAG_MSG_TYPE_VAR, _tknId, _splArg, (S8*)_stringPtr);                    \
   }                                                                                                                           \
}
#else
#define NB_DIAG_LVL0(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)
#define NB_DIAG_LVL1(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)
#define NB_DIAG_LVL2(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)
#define NB_DIAG_LVL3(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)
#define NB_DIAG_LVL4(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)
#define NB_DIAG_VAR(_tknId, _splArgEnum, _splArg, _string, _stringPtr)
#endif

/* TODO - This needs to be improved to use LWR to send ARM to LM */
#define ALARM printf
#define NB_ALLOC_SHAREBLE_BUF(_buf, _size)         \
{\
   if (SGetSBuf(NB_MEM_REGION, NB_MEM_POOL, (Data **)(_buf), \
            _size) == ROK)\
   {                                                         \
      NB_SET_ZERO((*_buf), _size);                           \
   }                                                         \
   else                                                      \
   {                                                         \
      NB_DIAG_LVL0(0x0ff00001, NB_DIAG_NA, SS_DIAG_INV_ARG,\
            "SSI memory allocation of %d \
            bytes %d failed in :%d",_size, __LINE__, 0, 0)   \
      (*_buf) = NULLP;                                       \
    }                                                         \
}

#define NB_MME_GET_TIME_TO_WAIT_VAL(_rcvdVal, _tmrVal)     \
{                                                      \
   switch(_rcvdVal)                                    \
   {                                                   \
      /* 1Sec */                                       \
      case 0:                                          \
         _tmrVal = (1 * 1000);                 \
      break;                                           \
      /* 2Sec */                                       \
      case 1:                                          \
         _tmrVal = (2 * 1000);                 \
      break;                                           \
      /* 5Sec */                                       \
      case 2:                                          \
         _tmrVal = (5 * 1000);                 \
      break;                                           \
      /* 10Sec */                                      \
      case 3:                                          \
         _tmrVal = (10 * 1000);                \
      break;                                           \
      /* 20Sec */                                      \
      case 4:                                          \
         _tmrVal = (20 * 1000);                \
      break;                                           \
      /* 60Sec */                                      \
      case 5:                                          \
         _tmrVal = (60 * 1000);                \
      break;                                           \
      default:                                         \
         break;                                        \
   }                                                   \
}
#define NB_GET_PLMN(_encPlmn,_len,_plmnVal) \
{ \
   \
   if(_len == 5) \
   {\
      _encPlmn[0] = (((_plmnVal/1000)%10)<<4)|((_plmnVal/10000)%10);\
      _encPlmn[1] = 0xF0|((_plmnVal/100)%10);\
      _encPlmn[2] = ((_plmnVal%10)<<4)|((_plmnVal/10)%10);\
   }\
   else if(_len == 6)\
   {\
      _encPlmn[0] = (((_plmnVal/10000)%10)<<4)|((_plmnVal/100000)%10);\
      _encPlmn[1] = (((_plmnVal/100)%10)<<4)|((_plmnVal/1000)%10);\
      _encPlmn[2] = ((_plmnVal%10)<<4)|((_plmnVal/10)%10);\
   }\
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __NB__H__ */
