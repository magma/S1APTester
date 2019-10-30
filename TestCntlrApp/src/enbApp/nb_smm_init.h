/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef __NB_SM_INIT_H__
#define __NB_SM_INIT_H__

#ifdef __cplusplus
extern "C" {
#endif

#define HI_POOL     0
#define SB_POOL     0
#define SZ_POOL     0
#define NB_POOL     0
#define EG_POOL     0

#define MAXARGS        20

#define NB_SZ_SPID                      0
#define NB_EG_SUID                      5
#define NB_EG_SPID                      0

#define SB_HI_SUID                      0
#define SB_HI_SPID                      0

#define EG_HI_SUID                      0
#define EG_HI_SPID                      1

#define SZ_SB_SUID                      0
#define SZ_SB_SPID                      0

#define NB_SZ_GEN_CFG                  1 
#define NB_SZ_PROT_CFG                 2
#define NB_SZ_SZT_SAP_CFG              4
#define NB_SZ_SCT_SAP_CFG              8
#define NB_SZ_PEER_CFG                16

#define MAX_NUM_PEER                   2

#define NB_SB_GEN_CFG                  1
#define NB_SB_TSAP_CFG                 2
#define NB_SB_SCT_SAP_CFG              4 

#define NB_EG_GEN_CFG                  1
#define NB_EG_EGT_SAP_CFG              2
#define NB_EG_TSAP_CFG                 4
#define NB_EG_TSRV_CFG                 8
#define NB_EG_IPADDR_CFG              16

#define MAX_ENB_NAME_LEN 20

#define NB_NB_GEN_CFG                  1 
#define NB_NB_EGT_CFG                  16 
#define NB_NB_SZT_CFG                  32 
#define NB_NB_ENBCFG_CFG               256
#define NB_NB_MME_CFG                  1024


#define   NB_SMM_MAX_NBR_ENB          16
#define   NB_SMM_INVALID_PEERID       0

#define NB_SM_NB_CONFIGURED  (NB_NB_GEN_CFG | \
                               NB_NB_SZT_CFG| \
                               NB_NB_ENBCFG_CFG)
                              
                              
#define NB_HI_GEN_CFG        1
#define NB_HI_TSAP_CFG       2

#define NB_SM_HI_CONFIGURED  (NB_HI_GEN_CFG | NB_HI_TSAP_CFG)
#define NB_SM_SB_CONFIGURED  (NB_SB_GEN_CFG | NB_SB_TSAP_CFG | NB_SB_SCT_SAP_CFG)
#define NB_SM_SZ_CONFIGURED  (NB_SZ_GEN_CFG | NB_SZ_PROT_CFG | NB_SZ_SZT_SAP_CFG | \
                              NB_SZ_SCT_SAP_CFG | NB_SZ_PEER_CFG)


#define NB_SM_EG_CONFIGURED  (NB_EG_GEN_CFG | NB_EG_EGT_SAP_CFG | \
                              NB_EG_TSAP_CFG | NB_EG_TSRV_CFG | NB_EG_IPADDR_CFG)

#define NBSM_ALLOC(_buf, _size)         \
   {                                                     \
      if (SGetSBuf(smCfgCb.init.region, DFLT_POOL, (Data **)(_buf),      \
               _size) == ROK)                        \
      {                                                  \
         SM_SET_ZERO((*_buf), _size);                    \
      }                                                  \
      else                                               \
      {                                                  \
         (*_buf) = NULLP;                                \
      }                                                  \
   }

#define NB_FILL_PST(_pst,_srcProc,_dstEnt,_srcEnt,_event,_pool,_selector) \
{                                                                \
   cmMemset((U8 *)&(_pst), 0, sizeof(Pst));                      \
   _pst.dstProcId = SM_SM_PROC;                                  \
   _pst.srcProcId = _srcProc;                                    \
   _pst.dstEnt = _dstEnt;                                        \
   _pst.srcEnt = _srcEnt;                                        \
   _pst.dstInst = 0;                                             \
   _pst.srcInst = 0;                                             \
   _pst.event  = _event;                                         \
   _pst.pool   = _pool;                                          \
   _pst.selector= _selector;                                     \
}

#define SM_SET_ZERO(_buf, _size)   \
    cmMemset((U8 *)(_buf), 0, _size);

#define SM_FREE(_region, _pool, _buf, _size)          \
{                                                     \
   if (_buf != NULLP)                                 \
   {                                                  \
   (Void) SPutSBuf(_region, _pool, (Data *) _buf,     \
   (Size) _size);                                     \
   (_buf) = NULLP;                                    \
   }                                                  \
}

#define SM_DFLT_MEM_UPPER_THR_CFG   9
#define SM_DFLT_MEM_LOWER_THR_CFG   2
#define SM_DFLT_MSEC_TMR_CFG        10

#define SM_INST_ZERO   0
#define SM_ZERO_VAL    0


#define SM_SELECTOR_LC      0
#define SM_SELECTOR_TC      1
#define SM_SELECTOR_LWLC    2


#define NB_SZ_SPID                      0
#define NB_SZ_SUID                      0


#define NBSM_LSZ_MAX_SZTSAP   10
/* Multi eNB support */
#ifdef MULTI_ENB_SUPPORT
#define NBSM_LSZ_MAX_SCTSAP   MAX_ENB_INST
#else
#define NBSM_LSZ_MAX_SCTSAP   10
#endif

#define NBSM_LSZ_TIMERES      10


#define NBSM_MSGPRIOR        PRIOR0    


/* SZ ---->SM posts */
#define NBSM_SZSMSEL           0
/* SM ---->SZ posts */
#define NBSM_SMSZSEL           0
 
 
/* SB ----> SM selector */
#define NBSM_SBSMSEL           0
/* SM ----> SB selector */
#define NBSM_SMSBSEL           0

/* HI ----> SM selector */
#define NBSM_HISMSEL           0
/* SM ----> HI selector */
#define NBSM_SMHISEL           0


/* nb ----> SZ selector */
#define NBSM_NBSZSEL           2
/* SZ ----> nb selector */
#define NBSM_SZNBSEL           2



/* SZ ----> SB selector */
#define NBSM_SZSBSEL           0
/* SB ----> SZ selector */
#define NBSM_SBSZSEL           0


/* SB ----> HI selector */
#define NBSM_SBHISEL           0
/* HI ----> SB selector */
#define NBSM_HISBSEL           0

/* EG ----> HI selector */
#define NBSM_EGHISEL           1
/* HI ----> EG selector */
#define NBSM_HIEGSEL           0

/* nb ----> SM selector */
#define NBSM_NBSMSEL           1
/* SM ----> nb selector */
#define NBSM_SMNBSEL           1


/* nb ----> EG selector */
#define NBSM_NBEGSEL           2
/* EG ----> nb selector */
#define NBSM_EGNBSEL           2

#define NBSM_LSZ_VAL_3        3
#define NBSM_LSZ_VAL_5        5
#define NBSM_LSZ_VAL_10       10 
#define NBSM_LSZ_VAL_50       50

#ifndef CNE_UE_SIM_TEST
#define NBSM_ENB_IPADDR       0x0A010101
#define NBSM_MME_IPADDR       0x0A010102
#define NBSM_SCTP_IP_ADDR     0x0A010102
#else
#define NBSM_ENB_IPADDR       0xAC19005E
#define NBSM_MME_IPADDR       0xAC1A0006
#define NBSM_SCTP_IP_ADDR     0xAC19005E
#endif
#define NBSM_LSZ_ENB_SCTPORT  36412
#define NBSM_LSZ_MME_SCTPORT  36412

#define NBSM_LSZ_ENB_PRC0     0

#define NBSM_LSZ_MME_PRC1     1

/* Peer Cfg */
#define NBSM_LSZ_NUM_PEERS       1
#define NBSM_LSZ_OUT_STRMS       3


/* Peer cntrl */
#define NBSM_LSZ_PEERID       0

#define NBSM_LSZ_MAX_PEER     10 
#define NB_MAX_UES_PER_CELL   10


#define NBSM_HI_NUMBSAPS           10
#define NBSM_HI_NMBCONS            1000

#ifdef HI_MULTI_THREADED
#define NBSM_HI_FDS                1024
#else
#define NBSM_HI_FDS                64
#endif /* HI_MULTI_THREADED */
#define NBSM_HI_FDBINS             4

#define NBSM_HI_SELTIMEOUT         2
#define NBSM_HI_UDP_MSGS_TOREAD    20
#define NBSM_HI_NUMCL_TOACCEPT     5

#define NBSM_HI_PERM_TSK_FLAG           FALSE
#define NBSM_HI_SCHDTMR_VAL             1
/* timer resolution unused */
#define NBSM_HI_TIME_RES                0
#define NBSM_HI_STRT_THRESH             1
#define NBSM_HI_DRP_THRESH              1
#define NBSM_HI_STP_THRESH              1

#define NBSM_HI_CONG_STRT                15000
#define NBSM_HI_CONG_DRP                 20000
#define NBSM_HI_CONG_STP                 10000
#define NBSM_HI_NMB_HLBINS               16


#define NBSM_LNB_VAL_10                 100 
#define NBSM_LNB_MAX_BND_RETRY           3

#define NBSM_CELLID                      1

/* nb002.102: Added sm layer name and print buf */
#if (NB_SM_LOG_TO_FILE && DEBUGP)
#define SMLAYERNAME                      "EnodeB Sm"
#define SM_PRNT_BUF                      smCfgCb.init.prntBuf
#else
#ifndef NB_DBG_CIRLOG
#define SM_PRNT_BUF                      smCfgCb.init.prntBuf
#else
/* Currently passing index as zero, when multiple system tasks are used then 
 * retrieve the corresponding circular buffer for that system task.
 */
#define SM_PRNT_BUF                      nbCb.init.prntCirBuf, MAX_LOG_BUF_SIZE 
#endif /* NB_DBG_CIRLOG */
#endif
  
#define SM_GETSBUF(_size, _datPtr, _ret)               \
{                                                      \
   _ret = SGetSBuf(smCfgCb.init.region,           \
                   DFLT_POOL,             \
                   (Data**)&_datPtr, _size);           \
}

/* _logLevel applicable only when enabling the log otherwise even level 0 will
 * be disabled
 * _logLevel 0 will be represented by 1st bit in the _logMask and so on
 */
#define SM_SND_DIAG_CNTRL_REQ(_logLevel, _logState, _logMask, _lyr, _maskIdx)\
{\
   _logMask = 0x01;\
   if(_logState == TRUE)\
   {\
      for(_maskIdx = 0; _maskIdx <= _logLevel; _maskIdx++)\
      {\
         _logMask = (_logMask | (0x01 << _maskIdx));\
      }\
      smSendDiagCntrlReq(NB_ON, _lyr, logMask);\
   }\
   else\
   {\
      _logMask = 0x0;\
      smSendDiagCntrlReq(NB_OFF, _lyr, logMask);\
   }\
}
#define     EVNTNBINITCFG      7
#define     EVTNBTUCLCFG       8
#define     EVTNBSCTPCFG       9
#define     EVTNBS1APCFG       10
#define     EVTNBEGTPCFG       11
#define     EVTNBAPPCFG        12
#define     EVTNBS1APSTKBND    13
#define     EVTNBEGTPSTKBND    14
#define     EVTNBENBDEBUGS     15
#define     EVTNBINITS1SETUP   16
#define     EVTNBCELLCFG       17
#define     EVTNBCELLCFGDONE   18 
#define     EVTNBENBLOG        19
#define     EVTNBTUCLSHUT      20 
#define     EVTNBSCTPSHUT      21
#define     EVTNBS1APSHUT      22
#define     EVTNBEGTPSHUT      23
#define     EVTNBAPPSHUT       24
#define     EVTNBEGTPSTKUNBND  25
#define     EVTNBS1APSTKUNBND  26

typedef enum  {
    NB_SM_STATE_INIT = 0,
    NB_SM_STATE_INIT_DONE,
    NB_SM_STATE_TUCL_CFG_DONE,
    NB_SM_STATE_SCTP_CFG_DONE,
    NB_SM_STATE_S1AP_CFG_DONE,
    NB_SM_STATE_EGTP_CFG_DONE,
    NB_SM_STATE_APP_CFG_DONE,
    NB_SM_STATE_S1AP_STK_BND_DONE,
    NB_SM_STATE_EGTP_STK_BND_DONE,
    NB_SM_STATE_ENB_DEBUGS_DONE,
    NB_SM_STATE_AWAIT_S1_CON,
    NB_SM_STATE_AWAIT_CELL_UP,
    NB_SM_STATE_CELL_UP,
    NB_SM_STATE_ENB_LOG_DONE,
    NB_SM_STATE_REBOOT_REQUIRED,
    NB_SM_STATE_DINIT,
    NB_SM_STATE_TUCL_SHUTDWN_DONE,
    NB_SM_STATE_SCTP_SHUTDWN_DONE,
    NB_SM_STATE_S1AP_SHUTDWN_DONE,
    NB_SM_STATE_EGTP_SHUTDWN_DONE,
    NB_SM_STATE_APP_SHUTDWN_DONE,
    NB_SM_STATE_EGTP_STK_UNBND_DONE,
    NB_SM_STATE_S1AP_STK_UNBND_DONE
}nbSmState;

typedef enum 
{
   APP = 1,
   S1AP,
   SCTP,
   TUCL,
   EGTP,
   ALL
}nbLyrDbg;     

#define NB_SM_HI_DBG_MASK 0x01
#define NB_SM_SB_DBG_MASK 0x02
#define NB_SM_SZ_DBG_MASK 0x04
#define NB_SM_EG_DBG_MASK 0x08
#define NB_SM_NB_DBG_MASK 0x10


#ifdef E_TM
#define ETM_CELL_STATE_IDLE  0
#define ETM_CELL_STATE_CFG   1
#define ETM_CELL_STATE_UP    2
#endif /* E_TM */
#define NB_MAX_LOG_PATH_VALUE  21

#define SZ_MEM_REGION        0
#define EG_MEM_REGION        0
#define CZ_MEM_REGION        0
#define SB_MEM_REGION        0
#define NH_MEM_REGION        0
#define SM_MEM_REGION        0
#define NB_MEM_REGION        0

typedef struct _smDiagInfo
{
   U32  diagLvl;   /*!< log level */
   Bool diagState; /*!< log state (enable/disable) */
}SmDiagInfo;

/**
 * @brief Structure to store log level and log state of all the layer
 */

typedef struct _smLyrDiagInfo
{
  SmDiagInfo tucl;
  SmDiagInfo sctp;
  SmDiagInfo s1ap;
  SmDiagInfo egtp;
  SmDiagInfo app;
}SmLyrDiagInfo;

typedef struct _tstTkn
{
   TknStr    tok;
   U16       nmbArgs;
   TknStr    args[MAXARGS];
} TstTkn;

typedef struct _smCfgCb
{
   TskInit init; 
   U16 cellId;
   U16 trackAreaCode;
   U32 enbIpAddr; /* used directly from here while s1ap: not required in gen cfg */
   U32 sctpIpAddr;
   U8  noOfCfg;         /* num MME configurations */
   LnbSmMmeCfg  *mmeCfg[MAX_NUM_PEER];
   LnbSctpParamCfg lnbSctpParamCfg; /* will be directly used from here in sctp */
   NbPlmnId plmnId;
   NbSuppTAList suppTAs; /* Supported TAs */
   NbEnodeBType eNodeBType; /* Macro eNodeB or Home eNodeB */
   NbCsgIdList csgIdList; /* CSG Id List */
   U8 sctpUdpServiceType; /*not clear */
   U8 enbName[NB_ENB_NAME];  /* eNB Name */
   U32 s1PrepTimerVal;             /* Preparation Timer Value */
   U32 s1OvrAllTimerVal;           /* Overall Timer Value */
   nbSmState smState;    /* state for state machine */
   Bool cellState;  /* Cell State*/
   Bool reCfg;  /* Configuration already done or not */
   U8 enbNameLen;
   U32 inactvTmrVal;
   U32 maxExpires;
   U16 s1SetupTmrVal;
   U16 noOfSctpInStreams;
   U16 noOfSctpOutStreams;
#ifdef MULTI_ENB_SUPPORT
   U32 numOfEnbs;
#endif
}smCb;

#if (NB_SM_LOG_TO_FILE && DEBUGP)
EXTERN Void nbSmCreateDbgFile(Void);
EXTERN S16 nbGetSId (SystemId *s);
#endif

/* Prototypes of Init functions */
EXTERN S16 smnbInit (SSTskId sysTskId);
EXTERN S16 smSzInit (SSTskId sysTskId);

EXTERN S16 smEgInit (SSTskId sysTskId);
EXTERN S16 smEuInit (SSTskId sysTskId);
EXTERN S16 smSbInit (SSTskId sysTskId);
EXTERN S16 smHiInit (SSTskId sysTskId);
EXTERN smCb smCfgCb;  

/* Prototypes of state machine functions */
/*IPSec*/
EXTERN Void smnbShutdownSm     (U8 event);
EXTERN Void smnbProcSm          (U8 event);
EXTERN S16  nbSmSelfPstMsg      (Pst *pst);
EXTERN Void nbSmHdlTuclCfgEvent (U8 event);
EXTERN Void nbSmHdlSctpCfgEvent (U8 event);
EXTERN Void nbSmHdlS1apCfgEvent (U8 event);
EXTERN Void nbSmHdlEgtpCfgEvent (U8 event);
EXTERN Void nbSmHdlAppCfgEvent  (U8 event);
EXTERN Void nbSmHdlBndS1apStack (U8 event);
EXTERN Void nbSmHdlBndEgtpStack (U8 event);


/* Actv Task  and Actv Init*/

EXTERN S16 egActvTsk (Pst *, Buffer *);
EXTERN S16 egActvInit (Ent, Inst, Region, Reason);

EXTERN S16 smEgActvTsk (Pst *, Buffer *);
EXTERN S16 smHiActvTsk (Pst *, Buffer *);
EXTERN S16 smSbActvTsk (Pst *, Buffer *);
EXTERN S16 smSzActvTsk (Pst *, Buffer *);


/* Config functions */
EXTERN Void nbSmHiCfg (Void);
EXTERN Void nbSmSbCfg (Void);
EXTERN Void nbSmSzCfg (Void);
EXTERN Void nbSmEgCfg (Void);
EXTERN Void nbSmNbCfg (Void);

/* HI(TUCL) Build Functions */
EXTERN Void smBuildHiGenCfg     (Void);
EXTERN Void smBuildHiTSapCfg    (SpId spId);
EXTERN Void smBuildHiDbgCntrl   (Void);
EXTERN Void smBuildHiLogCntrl   (Bool actType, U32 mask);

/* SB(SCTP) Build Functions */
EXTERN Void smBuildSbGenCfg     (Void);
EXTERN Void smBuildSbTSapCfg    (SpId spId, SuId suId);
EXTERN Void smBuildSbSctSapCfg  (SpId spId);
EXTERN Void smBindUnBindSbToLSap(SpId spId,U8 action);
EXTERN Void smBuildSbDbgCntrl   (Void);
EXTERN Void smBuildSbLogCntrl   (Bool actType, U32 mask);

/* SZ(S1AP) Build Functions */
EXTERN S16 smBuildSzGenCfg     (Void);
EXTERN S16 smBuildSzLSapCfg    (SpId spId, SuId suId);
EXTERN S16 smBuildSzUSapCfg    (SpId spId);
EXTERN S16 smBuildSzProtCfg    (Void);
EXTERN S16 smBuildSzPeerCfg    (Void);
EXTERN S16 smBldSzPeerDelCntrlReq(U8 peerId, U8 dbIndex);
EXTERN S16 smBindUnBindSzToLSap  (U8 action);
EXTERN S16 smBuildSzGenCntrl   (Void);
EXTERN S16 smBuildSzDbgCntrl   (Void);
EXTERN S16 smBuildSzLogCntrl   (Bool actType, U32 mask);

/* EG(EGTP) Build Functions */
EXTERN S16  smBuildEgGenCfg     (Void);
EXTERN S16  smBuildEgGenCntrl    (Void);
EXTERN S16  smBuildEgUSapCfg    (SpId spId);
EXTERN S16  smBuildEgLSapCfg    (SpId spId, SuId suId);
/* Shwetha - adding IP Address configuration for EGTP-U */
EXTERN S16  smBuildEgIpAddrCfg  (SpId  spId);
EXTERN S16  smBuildTServerCfg   (Void);
EXTERN Void smBindUnBindEgToHitSap  (SpId spId,U8 action);
EXTERN Void  smBuildEgDbgCntrl   (Void);
EXTERN Void  smBuildEgLogCntrl   (Bool actType, U32 mask);


/* nb(APP) Build Functions */
EXTERN S16 smBuildnbGenCfg     (Void);
EXTERN S16 smBuildnbCtfLSapCfg (SpId spId, SuId suId);

EXTERN S16 smBuildnbMmeCfg (LnbMngmt *lnbMng, LnbSmMmeCfg *mmeCfg);
EXTERN Void smGetS1apStats(Void);

#ifdef EU_DAT_APP
EXTERN S16 smBuildnbEgtLSapCfg (SpId spId, SuId suId);
EXTERN S16 smBuildnbPjuLSapCfg (SpId spId, SuId suId);
EXTERN S16 smBindUnBindnbToEgtSap(U8 action);
EXTERN S16 smBindUnBindnbToPjuSap    (Inst inst,U8 action);
#endif

EXTERN S16 smBindUnBindnbToSztSap    (U8 action);
EXTERN S16 smBindUnBindnbToNhuSap    (U8 action);
EXTERN S16 smBuildNbGenCntrl   (Void);
EXTERN S16 smBuildNbS1InitCntrl   (Void);

/*IPSec support */

EXTERN S16 smBuildEgShutDownCntrl   (Void);
EXTERN S16 smBuildSzShutDownCntrl   (Void);
EXTERN S16 smBuildSbShutDownCntrl   (Void);
EXTERN S16 smBuildnbShutDownCntrl   (Void);
EXTERN S16 smBuildGenCfg(LnbMngmt *lnbMng);

EXTERN Void smBuildShutRestart(Void);

EXTERN Void smNbProcSm
(
U8 event
);
EXTERN Void nbSmHdlInitCfg 
(
 U8 event
);
EXTERN Void  nbSmHdlInitS1Setup
(
 U8 event
 );
EXTERN S16 smNbInit
(
SSTskId    sysTskId
);
EXTERN Void smBuildNbSztLSapCfg
(
SuId        suId,             /* RRC App Sap ID */
SpId        spId              /* Service Provider Sap ID */
);
EXTERN S16 smBindUnBindNbToSztSap
(
U8 action
);
EXTERN S16 smBindUnBindNbToEgtSap
(
U8 action
);



#ifdef __cplusplus
}
#endif

#ifdef SS_DIAG
 /** @details Macro definition for nb level 0 logs
 *
*/
#define SM_DIAG_LVL0(_tknId, _splArg, _string, _arg1, _arg2, _arg3, _arg4)                      \
{                                                                                              \
   if(smCfgCb.init.logMask & SS_DIAG_LVL0)                                                         \
   {                                                                                           \
      ssDiagFix(_tknId, 0, ENTSM, smCfgCb.init.inst, SS_DIAG_LVL0, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }                                                                                           \
}

/** @details Macro definition for nb level 1 logs
 *  
*/
#define SM_DIAG_LVL1(_tknId, _splArg, _string, _arg1, _arg2, _arg3, _arg4)            \
{                                                                 \
   if(smCfgCb.init.logMask & SS_DIAG_LVL1)                             \
   {                                                              \
      ssDiagFix(_tknId, _splArgEnum, ENTSM, smCfgCb.init.inst, SS_DIAG_LVL1, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }                                                              \
}

/** @details Macro definition for nb level 2 logs
 *  
*/
#define SM_DIAG_LVL2(_tknId, _splArg, _string, _arg1, _arg2, _arg3, _arg4)       \
{                                                              \
   if(smCfgCb.init.logMask & SS_DIAG_LVL2)                            \
   {                                                              \
      ssDiagFix(_tknId, _splArgEnum, ENTSM, smCfgCb.init.inst, SS_DIAG_LVL2, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }                                                              \
}

/** @details Macro definition for nb  level 3 logs 
 *  
*/
#define SM_DIAG_LVL3(_tknId, _splArg, _string, _arg1, _arg2, _arg3, _arg4)        \
{                                                              \
   if(smCfgCb.init.logMask & SS_DIAG_LVL3)                            \
   {                                                              \
      ssDiagFix(_tknId, _splArgEnum, ENTSM, smCfgCb.init.inst, SS_DIAG_LVL3, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }                                                              \
}

/** @details Macro definition for nb  level 4 logs
 *  
*/
#define SM_DIAG_LVL4(_tknId, _splArg, _string, _arg1, _arg2, _arg3, _arg4)        \
{                                                              \
   if(smCfgCb.init.logMask & SS_DIAG_LVL4)                            \
   {                                                              \
      ssDiagFix(_tknId, _splArgEnum, ENTSM, smCfgCb.init.inst, SS_DIAG_LVL4, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }                                                              \
}
#else

#define SM_DIAG_LVL0(_tknId, _splArg, _string, _arg1, _arg2, _arg3, _arg4)        
#define SM_DIAG_LVL1(_tknId, _splArg, _string, _arg1, _arg2, _arg3, _arg4)       
#define SM_DIAG_LVL2(_tknId, _splArg, _string, _arg1, _arg2, _arg3, _arg4)      
#define SM_DIAG_LVL3(_tknId, _splArg, _string, _arg1, _arg2, _arg3, _arg4)     
#define SM_DIAG_LVL4(_tknId, _splArg, _string, _arg1, _arg2, _arg3, _arg4)    
#endif
 

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __NB_SM_INIT_H__ */

