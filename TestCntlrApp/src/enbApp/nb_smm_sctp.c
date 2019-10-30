/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

/**********************************************************************

    Name:  LTE S1SIM - ENODEB Application Module 

    Type:  C include file

    Desc:  C source code for ENODEB Application

    File:  nb_smm_sctp.c
               
    Sid:   

    Prg:   

**********************************************************************/

#include "nb.h"
#include "rl_interface.h"
#include "rl_common.h"
#include "fw_tst.h"
#include "nb_smm_init.h"
#include "lsb.h"
#include "nb_log.h"
#include "nbt.h"

#include "lsb.x"
#include "nbt.x"

PRIVATE U8      nbSbCfg = 0;
/*
*
*       Fun:   Initialize SCTP task.
*
*       Desc:  Invoked to create SCTP TAPA task.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_sb_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smSbInit
(
SSTskId    sysTskId
)
#else
PUBLIC S16 smSbInit(sysTskId)
SSTskId    sysTskId;
#endif
{
   TRC2(smSbInit)

   /* Register SCTP TAPA Task */
   if (SRegTTsk((Ent)ENTSB, (Inst)0, (Ttype)TTNORM, (Prior)PRIOR2,
                 sbActvInit, (ActvTsk)sbActvTsk) != ROK) 
   {
      RETVALUE(RFAILED);
   }

   /* Attach SCTP TAPA Task */
   if (SAttachTTsk((Ent)ENTSB, (Inst)0, sysTskId)!= ROK) 
   {
      RETVALUE(RFAILED);
   }

   NB_LOG_DEBUG(&nbCb,"SCTP Tapa Task successfully registered and attached to [%d]",
      sysTskId);

   RETVALUE(ROK);
} /* end of smSbInit */

/*
 *
 *       Fun:    nbSmSbCfg - configure SB 
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *      File:  wr_sm_sb_cntrl.c
 *
 */

#ifdef ANSI
PUBLIC Void nbSmSbCfg
(
Void
)
#else
PUBLIC Void nbSmSbCfg()
#endif /* ANSI */
{
#ifdef SS_MULTIPLE_PROCS
   U16   cnt;
#endif
   /* Multi eNB support */
#ifdef MULTI_ENB_SUPPORT
   S16   inst = 0;
#endif

   TRC2(nbSmSbCfg)
   nbSbCfg = 0;

   smBuildSbGenCfg();
   smBuildSbTSapCfg(SB_HI_SPID, SB_HI_SUID);
   /* Multi eNB support */
#ifdef MULTI_ENB_SUPPORT
   for(inst = 0; inst < smCfgCb.numOfEnbs; inst++)
   {
      smBuildSbSctSapCfg(SZ_SB_SPID+inst);
   }
#else 
   smBuildSbSctSapCfg(SZ_SB_SPID);
#endif
   RETVOID;
}


/*
 *
 *       Fun:    smBuildSbGenCfg - fill in default genCfg for SB
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
         File:   wr_sm_sb_cntrl.c
 *
 */

#ifdef ANSI
PUBLIC Void smBuildSbGenCfg
(
Void
)
#else
PUBLIC Void smBuildSbGenCfg()
#endif /* ANSI */
{
   SbMgmt      sbMgt;
   SbGenCfg    *cfg = NULLP;
   Pst         pst;

   TRC2(smBuildSbGenCfg)

   SM_SET_ZERO(&sbMgt, sizeof(SbMgmt));
   SM_SET_ZERO(&pst, sizeof(Pst));


   cfg = &sbMgt.t.cfg.s.genCfg;
   /*S1-MME connection is IP/SCTP*/
   cfg->serviceType   = HI_SRVC_RAW_SCTP_PRIOR;
#ifdef LSB5
   cfg->srcUdpPort = 9898;
   cfg->dstUdpPort = 9898;
#endif /*LSB5*/
#ifdef MULTI_ENB_SUPPORT
   cfg->maxNmbSctSaps     = smCfgCb.numOfEnbs;
   cfg->maxNmbAssoc       = smCfgCb.numOfEnbs;
   cfg->maxNmbEndp        = smCfgCb.numOfEnbs;
#else 
   cfg->maxNmbSctSaps     = 10;
   cfg->maxNmbAssoc       = 100;
   cfg->maxNmbEndp        = 10;
#endif
   cfg->maxNmbTSaps       = 5;
   cfg->maxNmbDstAddr     = (U16)(2 * cfg->maxNmbAssoc);
   cfg->maxNmbSrcAddr     = 10;
   cfg->maxNmbTxChunks    = 95000;
   cfg->maxNmbRxChunks    = 95000;
   cfg->maxNmbInStrms     = smCfgCb.noOfSctpInStreams;
   cfg->maxNmbOutStrms    = smCfgCb.noOfSctpOutStreams;

   NB_LOG_DEBUG(&nbCb,"==========In Streams: %d",cfg->maxNmbInStrms);
   NB_LOG_DEBUG(&nbCb,"==========Out Streams: %d",cfg->maxNmbOutStrms);
   cfg->initARwnd         = 48000; /* S1AP Warning message as size can go up to 16k 
                                     if EAID list has 5000 IE's 
                                     to transmit all segements need more time,
                                     we are increasing SCTP window size from 16k to 48k
                                   */ 
   cfg->mtuInitial        = 1500;
   cfg->mtuMinInitial     = 1500;
   cfg->mtuMaxInitial     = 1500;
   cfg->performMtu        = FALSE;
   /* Changed from 1 to 10 as timer tick is reduced to 10ms */
   cfg->timeRes           = 10; /* timer resolution is 1 i.e 100ms unit */
   cfg->reConfig.maxInitReTx   = 25;
   cfg->reConfig.maxAssocReTx  = 25;
   cfg->reConfig.maxPathReTx   = 5;
   cfg->reConfig.altAcceptFlg  = FALSE;
   cfg->reConfig.keyTm         = 600;
   cfg->reConfig.alpha         = 12;
   cfg->reConfig.beta          = 25;

   cfg->smPst.srcProcId = SM_SM_PROC;
   cfg->smPst.dstProcId = SM_SB_PROC;
   cfg->smPst.srcEnt = (Ent)ENTSB;
   cfg->smPst.dstEnt = (Ent)ENTSM;
   cfg->smPst.srcInst = (Inst)0;
   cfg->smPst.dstInst = (Inst)0;

   cfg->smPst.prior = (Prior)NBSM_MSGPRIOR;
   cfg->smPst.route = (Route)RTESPEC;
   cfg->smPst.event = (Event)EVTNONE;
   cfg->smPst.region = SB_MEM_REGION;
   cfg->smPst.pool =  SB_POOL;
   cfg->smPst.selector = (Selector)NBSM_SBSMSEL;

    /* Fill Header */
   sbMgt.hdr.msgType             = TCFG;
   sbMgt.hdr.msgLen              = 0;
   sbMgt.hdr.entId.ent           = ENTSB;
   sbMgt.hdr.entId.inst          = SM_INST_ZERO;
   sbMgt.hdr.elmId.elmnt         = STSBGEN;
   sbMgt.hdr.elmId.elmntInst1    = 0;
   sbMgt.hdr.elmId.elmntInst2    = 0;
   sbMgt.hdr.elmId.elmntInst3    = 0;
   sbMgt.hdr.seqNmb              = 0;
   sbMgt.hdr.version             = 0;
   sbMgt.hdr.transId             = 0;

   sbMgt.hdr.response.prior      = PRIOR0;
   sbMgt.hdr.response.route      = RTESPEC;
   sbMgt.hdr.response.mem.region = SB_MEM_REGION;
   sbMgt.hdr.response.mem.pool   = SB_POOL;
   sbMgt.hdr.response.selector   = SM_SELECTOR_LC;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTSB;
   pst.dstProcId = SM_SB_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCfgCb.init.region;

   NB_LOG_DEBUG(&nbCb,"SCTP Gen Cfg sent");

   (Void)SmMiLsbCfgReq(&pst, &sbMgt);

   RETVOID;
} /* end of smBuildSbGenCfg() */

/*
 *
 *       Fun:    smBuildSbTSapCfg - fill in default SCTP TSAP
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *       File:   wr_sm_sb_cntrl.c
 *
 */

#ifdef ANSI
PUBLIC Void smBuildSbTSapCfg
(
SpId        spId,
SuId        suId
)
#else
PUBLIC Void smBuildSbTSapCfg(spId, suId)
SpId        spId;
SuId        suId;
#endif /* ANSI */
{
   SbMgmt      sbMgt;
   SbTSapCfg   *cfg = NULLP;
   Pst          pst;

   TRC2(smBuildSbTSapCfg)

   SM_SET_ZERO(&sbMgt, sizeof(SbMgmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   cfg = &(sbMgt.t.cfg.s.tSapCfg);

   cfg->swtch        = LSB_SW_RFC_REL0;
   cfg->sel          = NBSM_SBHISEL;      /* Loosely coupled upper layer */
   cfg->ent          = ENTHI;              /* Loosely coupled upper layer */
   cfg->inst         = 0;                  /* Loosely coupled upper layer */
   cfg->procId       = SM_HI_PROC;       /* Loosely coupled upper layer */
   cfg->memId.region = SB_MEM_REGION;
   cfg->memId.pool   = SB_POOL;
   cfg->prior        = PRIOR0;
   cfg->route        = RTESPEC;
   cfg->suId         = suId;
   cfg->srcNAddrLst.nmb = 1;
   cfg->srcNAddrLst.nAddr[0].type = CM_NETADDR_IPV4;
   cfg->srcNAddrLst.nAddr[0].u.ipv4NetAddr = smCfgCb.sctpIpAddr;
   cfg->reConfig.spId         = spId;
   cfg->reConfig.tIntTmr      = 200;
   cfg->reConfig.maxBndRetry  = 2;

   /* Fill Header */
   sbMgt.hdr.msgType             = TCFG;
   sbMgt.hdr.msgLen              = 0;
   sbMgt.hdr.entId.ent           = ENTSB;
   sbMgt.hdr.entId.inst          = SM_INST_ZERO;
   sbMgt.hdr.elmId.elmnt         = STSBTSAP;
   sbMgt.hdr.response.mem.region = SB_MEM_REGION;
   sbMgt.hdr.response.mem.pool   = SB_POOL;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTSB;
   pst.dstProcId = SM_SB_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCfgCb.init.region;

   NB_LOG_DEBUG(&nbCb,"SCTP TCfg sent");

   (Void)SmMiLsbCfgReq(&pst, &sbMgt);

   RETVOID;
} /* end of smBuildSbTSapCfg */

/*
 *
 *       Fun:    smBuildSbSctSapCfg - fill in default SCTP SAP
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *       File:   wr_sm_sb_cntrl.c
 *
 */

#ifdef ANSI
PUBLIC Void smBuildSbSctSapCfg
(
SpId          spId
)
#else
PUBLIC Void smBuildSbSctSapCfg(spId)
SpId          spId;
#endif /* ANSI */
{
   SbMgmt               sbMgt;
   SbSctSapCfg   *cfg = NULLP;
   Pst           pst;

   TRC2(smBuildSbSctSapCfg)

   SM_SET_ZERO(&sbMgt, sizeof(SbMgmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg = &(sbMgt.t.cfg.s.sctSapCfg);
   cfg->swtch        = LSB_SW_RFC_REL0;
   cfg->sel          = NBSM_SZSBSEL;     /* Loosely coupled upper layer */
   cfg->memId.region =  SB_MEM_REGION;
   cfg->memId.pool   =  SB_POOL;
   cfg->prior = PRIOR0;
   cfg->route = RTESPEC;
   cfg->spId  = spId;
   cfg->reConfig.maxAckDelayTm = 2; /* 200 ms*/
   cfg->reConfig.maxAckDelayDg = 5;

/* Amit: SCTP Param Configuration Support */
   cfg->reConfig.rtoInitial = smCfgCb.lnbSctpParamCfg.rtoInitial;
   cfg->reConfig.rtoMin     = smCfgCb.lnbSctpParamCfg.rtoMin;
   cfg->reConfig.rtoMax     = smCfgCb.lnbSctpParamCfg.rtoMax;
   cfg->reConfig.intervalTm = smCfgCb.lnbSctpParamCfg.heartBeatInterval;    /* Heartbeat timer,5 seconds */
/* Amit: SCTP Param Configuration Support-OLD Values */
   cfg->reConfig.freezeTm   = 15;  /* 1.5 seconds */
#ifdef LSB4
   cfg->reConfig.bundleTm = 0;
#endif /* LSB4 */
   cfg->reConfig.cookieLife = 50000;   /* 5000 seconds */
#ifdef LSB8
   cfg->reConfig.maxBurst = 4;
   cfg->reConfig.maxHbBurst = 1;
   cfg->reConfig.t5SdownGrdTm = (SctRTT)(5 * cfg->reConfig.rtoMax);
#endif /* LSB8 */
   cfg->reConfig.handleInitFlg = TRUE; 
   cfg->reConfig.negAbrtFlg = FALSE;
   cfg->reConfig.hBeatEnable= FALSE;
   cfg->reConfig.flcUpThr   = 80000;    /* number of packets */
   cfg->reConfig.flcLowThr  = 30000;
 
   /* Fill Header */
   sbMgt.hdr.msgType             = TCFG;
   sbMgt.hdr.msgLen              = 0;
   sbMgt.hdr.entId.ent           = ENTSB;
   sbMgt.hdr.entId.inst          = SM_INST_ZERO;
   sbMgt.hdr.elmId.elmnt         = STSBSCTSAP;
   sbMgt.hdr.response.mem.region = SB_MEM_REGION;
   sbMgt.hdr.response.mem.pool   = SB_POOL;

  /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTSB;
   pst.dstProcId = SM_SB_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCfgCb.init.region;
 
   NB_LOG_DEBUG(&nbCb,"SCTP Sct Sap Cfg sent");

   (Void)SmMiLsbCfgReq(&pst, &sbMgt);

   RETVOID;
} /* end of smBuildSbSctSapCfg */

/*
 *
 *       Fun:    smBindUnBindSbToLSap
 *
 *       Desc:   Bind and Unbind SCTP with lower SAP
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *       File:   
 *
 */

#ifdef ANSI
PUBLIC Void smBindUnBindSbToLSap
(
SpId        spId,
U8          action
)
#else
PUBLIC Void smBindUnBindSbToLSap(spId,action)
SpId        spId;
U8          action;
#endif /* ANSI */
{
   SbMgmt               sbMgt;
   Pst                  pst;

   TRC2(smBindUnBindSbToLSap)

   SM_SET_ZERO(&sbMgt, sizeof(SbMgmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   sbMgt.hdr.msgType             = TCNTRL;
   sbMgt.hdr.entId.ent           = ENTSB;
   sbMgt.hdr.entId.inst          = SM_INST_ZERO;
   sbMgt.hdr.elmId.elmnt         = STSBTSAP;
   sbMgt.hdr.response.mem.region = SB_MEM_REGION;
   sbMgt.hdr.response.mem.pool   = SB_POOL;

   sbMgt.t.cntrl.action  = action;
   sbMgt.t.cntrl.subAction  = SAELMNT;
   sbMgt.t.cntrl.sapId    = spId;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTSB;
   pst.dstProcId = SM_SB_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCfgCb.init.region;

   if (action == ABND_ENA)
   {
      NB_LOG_DEBUG(&nbCb,"Sending Bnd Cntrl Req to sb Lsap");
   }
   else
   {
      NB_LOG_DEBUG(&nbCb,"Sending UnBnd Cntrl Req to sb Lsap");
   }

   (Void)SmMiLsbCntrlReq(&pst, &sbMgt);

   RETVOID;
} /* end of smBindUnBindSbToLSap */
 

#ifdef ANSI
PUBLIC S16 smSbActvInit
(
Ent ent,                      /* entity */
Inst inst,                    /* instance */
Region region,                /* region */
Reason reason                 /* reason */
)
#else
PUBLIC S16 smSbActvInit(ent, inst, region, reason)
Ent ent;                      /* entity */
Inst inst;                    /* instance */
Region region;                /* region */
Reason reason;                /* reason */
#endif
{
   TRC3(smSbActvInit)

   UNUSED(ent);
   UNUSED(inst);
   UNUSED(region);
   UNUSED(reason);
   RETVALUE(ROK);
} /* end of smSbActvInit */

EXTERN  S16 smSbActvTsk     (Pst *pst, Buffer *mBuf);

/*
*
*       Fun:    activate task
*
*       Desc:   Processes received event from SCTP layer
*
*       Ret:    ROK  - ok
*
*       Notes:  None
*
*       File:     
*
*/

#ifdef ANSI
PUBLIC S16 smSbActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 smSbActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   S16 ret;
   TRC3(smSbActvTsk)
   ret = ROK;
  
   switch(pst->event)
   {
#ifdef LCSMSBMILSB
    
      case LSB_EVTCFGCFM:             /* Config confirm */
         ret = cmUnpkLsbCfgCfm(SmMiLsbCfgCfm, pst, mBuf);
         break;
      case LSB_EVTCNTRLCFM:           /* Control confirm */
         ret = cmUnpkLsbCntrlCfm(SmMiLsbCntrlCfm, pst, mBuf);
         break;
      case LSB_EVTSTACFM:             /* Status Confirm */
         ret = cmUnpkLsbStaCfm(SmMiLsbStaCfm, pst, mBuf);
         break;
      case LSB_EVTSTSCFM:             /* Statistics Confirm */
         ret = cmUnpkLsbStsCfm(SmMiLsbStsCfm, pst, mBuf);
         break;
      case LSB_EVTSTAIND:             /* Status Indication */
           /*sb085.102: Removed the debug prints*/

            ret = cmUnpkLsbStaInd(SmMiLsbStaInd, pst, mBuf);
         break;
      case LSB_EVTTRCIND:             /* Trace Indication */
         ret = cmUnpkLsbTrcInd(SmMiLsbTrcInd, pst, mBuf);
         break;
#endif
      default:
         NB_FREEMBUF(mBuf);
         ret = RFAILED;
         NB_LOG_DEBUG(&nbCb,"smSbActvTsk : Received invalid event");
         break;
   }
   SExitTsk();
   RETVALUE(ret);
} /* end of smSbActvTsk */
/* local defines */

#define MAXSBMI                2

#ifndef LCSMSBMILSB
#define PTSMSBMILSB
#else
#ifndef SB
#define PTSMSBMILSB
#else
#endif
#endif

/* forward references */
#ifdef PTSMSBMILSB
PRIVATE S16 PtMiLsbCfgReq   (Pst *pst, SbMgmt *cfg );
PRIVATE S16 PtMiLsbStaReq   (Pst *pst, SbMgmt *sta );
PRIVATE S16 PtMiLsbStsReq   (Pst *pst, Action action, SbMgmt *sts );
PRIVATE S16 PtMiLsbCntrlReq (Pst *pst, SbMgmt *cntrl );
#endif

/* functions in other modules */

/* public variable declarations */

/* private variable declarations */


/*
The following matrices define the mapping between the primitives
called by the layer management interface of SCTP layer and the corresponding
primitives in the driver.

The parameter MAXSBMI defines the maximum number of layer manager entities
on top of the driver. There is an array of functions per primitive insbked by
the driver. Every array is MAXSBMI long (i.e. there are as many functions as the
number of service users).

The dispatching is performed by the configurable variable: selector.
The selector is configured during general configuration.

The selectors are:

   0 - loosely coupled (#define LCSMSBMILSB)
   1 - Lsb (#define SB)

*/

/* Configuration request primitive */

PRIVATE LsbCfgReq SmMiLsbCfgReqMt[MAXSBMI] =
{
#ifdef LCSMSBMILSB
   cmPkLsbCfgReq,        /* 0 - loosely coupled - bc */
#else
   PtMiLsbCfgReq,          /* 0 - tightly coupled, portable */
#endif
#ifdef SB
   SbMiLsbCfgReq,          /* 1 - tightly coupled, layer management */
#else
   PtMiLsbCfgReq,          /* 1 - tightly coupled, portable */
#endif
};

/* Statistics request primitive */

PRIVATE LsbStsReq SmMiLsbStsReqMt[MAXSBMI] =
{
#ifdef LCSMSBMILSB
   cmPkLsbStsReq,        /* 0 - loosely coupled - bc */
#else
   PtMiLsbStsReq,          /* 0 - tightly coupled, portable */
#endif
#ifdef SB
   SbMiLsbStsReq,          /* 1 - tightly coupled, layer management */
#else
   PtMiLsbStsReq,          /* 1 - tightly coupled, portable */
#endif
};

/* Status request primitive */

PRIVATE LsbStaReq SmMiLsbStaReqMt[MAXSBMI] =
{
#ifdef LCSMSBMILSB
   cmPkLsbStaReq,        /* 0 - loosely coupled - bc */
#else
   PtMiLsbStaReq,          /* 0 - tightly coupled, portable */
#endif
#ifdef SB
   SbMiLsbStaReq,          /* 1 - tightly coupled, layer management */
#else
   PtMiLsbStaReq,          /* 1 - tightly coupled, portable */
#endif
};

/* Control request primitive */

PRIVATE LsbCntrlReq SmMiLsbCntrlReqMt[MAXSBMI] =
{
#ifdef LCSMSBMILSB
   cmPkLsbCntrlReq,        /* 0 - loosely coupled - bc */
#else
   PtMiLsbCntrlReq,          /* 0 - tightly coupled, portable */
#endif
#ifdef SB
   SbMiLsbCntrlReq,          /* 1 - tightly coupled, layer management */
#else
   PtMiLsbCntrlReq,          /* 1 - tightly coupled, portable */
#endif
};

/*
*     layer management interface functions
*/

/*
*
*       Fun:   Configuration request
*
*       Desc:  This function is used to configure SCTP layer
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:     wr_sm_sb_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLsbCfgReq
(
Pst *pst,                 /* post structure */
SbMgmt *cfg              /* configure */
)
#else
PUBLIC S16 SmMiLsbCfgReq(pst, cfg)
Pst *pst;                 /* post structure */
SbMgmt *cfg;             /* configure */
#endif
{
   TRC3(SmMiLsbCfgReq)
   /* jump to specific primitive depending on configured selector */
   (*SmMiLsbCfgReqMt[pst->selector])(pst, cfg);
   RETVALUE(ROK);
} /* end of SmMiLsbCfgReq */

/*
*
*       Fun:   Status request
*
*       Desc:  This function is used to send a status request to SCTP layer
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:     wr_sm_sb_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLsbStaReq
(
Pst *pst,                 /* post structure */
SbMgmt *sta              /* status */
)
#else
PUBLIC S16 SmMiLsbStaReq(pst, sta)
Pst *pst;                 /* post structure */
SbMgmt *sta;             /* status */
#endif
{
   TRC3(SmMiLsbStaReq)
   /* jump to specific primitive depending on configured selector */
   (*SmMiLsbStaReqMt[pst->selector])(pst, sta);
   RETVALUE(ROK);
} /* end of SmMiLsbStaReq */

/*
*
*       Fun:   Statistics request
*
*       Desc:  This function is used to request statistics from SCTP layer
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:     wr_sm_sb_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLsbStsReq
(
Pst *pst,                 /* post structure */
Action action,
SbMgmt *sts              /* statistics */
)
#else
PUBLIC S16 SmMiLsbStsReq(pst, action, sts)
Pst *pst;                 /* post structure */
Action action;
SbMgmt *sts;             /* statistics */
#endif
{
   TRC3(SmMiLsbStsReq)
   /* jump to specific primitive depending on configured selector */
   (*SmMiLsbStsReqMt[pst->selector])(pst, action, sts);
   RETVALUE(ROK);
} /* end of SmMiLsbStsReq */

/*
*
*       Fun:   Control request
*
*       Desc:  This function is used to send control request to SCTP layer
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:     wr_sm_sb_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLsbCntrlReq
(
Pst *pst,                 /* post structure */
SbMgmt *cntrl            /* control */
)
#else
PUBLIC S16 SmMiLsbCntrlReq(pst, cntrl)
Pst *pst;                 /* post structure */
SbMgmt *cntrl;           /* control */
#endif
{
   TRC3(SmMiLsbCntrlReq)
   /* jump to specific primitive depending on configured selector */
   (*SmMiLsbCntrlReqMt[pst->selector])(pst, cntrl);
   RETVALUE(ROK);
} /* end of SmMiLsbCntrlReq */


#ifdef PTSMSBMILSB
/*
*
*       Fun:   Portable configure Request SCTP layer
*
*       Desc:
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:     wr_sm_sb_ptmi.c
*
*/

#ifdef ANSI
PRIVATE S16 PtMiLsbCfgReq
(
Pst *pst,                   /* post structure */
SbMgmt *cfg                /* configure */
)
#else
PRIVATE S16 PtMiLsbCfgReq(pst, cfg)
Pst *pst;                   /* post structure */
SbMgmt *cfg;               /* configure */
#endif
{
   TRC3(PtMiLsbCfgReq);

   UNUSED(pst);
   UNUSED(cfg);
   RETVALUE(ROK);
} /* end of PtMiLsbCfgReq */


/*
*
*       Fun:   Portable status Request SCTP layer
*
*       Desc:
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:     wr_sm_sb_ptmi.c
*
*/

#ifdef ANSI
PRIVATE S16 PtMiLsbStaReq
(
Pst *pst,                   /* post structure */
SbMgmt *sta                /* status */
)
#else
PRIVATE S16 PtMiLsbStaReq(pst, sta)
Pst *pst;                   /* post structure */
SbMgmt *sta;               /* status */
#endif
{
   TRC3(PtMiLsbStaReq);
   UNUSED(pst);
   UNUSED(sta);
   RETVALUE(ROK);
} /* end of PtMiLsbStaReq */


/*
*
*       Fun:   Portable statistics Request SCTP layer
*
*       Desc:
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:     wr_sm_sb_ptmi.c
*
*/

#ifdef ANSI
PRIVATE S16 PtMiLsbStsReq
(
Pst *pst,                   /* post structure */
Action action,
SbMgmt *sts                /* statistics */
)
#else
PRIVATE S16 PtMiLsbStsReq(pst, action, sts)
Pst *pst;                   /* post structure */
Action action;
SbMgmt *sts;               /* statistics */
#endif
{
   TRC3(PtMiLsbStsReq);
   UNUSED(pst);
   UNUSED(action);
   UNUSED(sts);
   RETVALUE(ROK);
} /* end of PtMiLsbStsReq */


/*
*
*       Fun:   Portable control Request SCTP layer
*
*       Desc:
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:     wr_sm_sb_ptmi.c
*
*/

#ifdef ANSI
PRIVATE S16 PtMiLsbCntrlReq
(
Pst *pst,                   /* post structure */
SbMgmt *cntrl              /* control */
)
#else
PRIVATE S16 PtMiLsbCntrlReq(pst, cntrl)
Pst *pst;                   /* post structure */
SbMgmt *cntrl;             /* control */
#endif
{
   TRC3(PtMiLsbCntrlReq);
   UNUSED(pst);
   UNUSED(cntrl);
   RETVALUE(ROK);
} /* end of PtMiLsbCntrlReq */

#endif

/*
*
*       Fun:   Configuration Confirm
*
*       Desc:  This function is used by to present configuration confirm
*              information to Layer Manager.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smsbptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLsbCfgCfm
(
Pst     *pst,          /* post structure */
SbMgmt *cfm           /* configuration */
)
#else
PUBLIC S16 SmMiLsbCfgCfm(pst, cfm)
Pst     *pst;          /* post structure */
SbMgmt *cfm;          /* configuration */
#endif
{
#ifdef MULTI_ENB_SUPPORT
   PRIVATE U32 inst = 0;
#endif

   TRC2(SmMiLsbCfgCfm);

   if (cfm->cfm.status == LCM_PRIM_OK)
   {
      switch(cfm->hdr.elmId.elmnt)
      {
         case STSBGEN:
            nbSbCfg |=  NB_SB_GEN_CFG;
            break;
         case STSBTSAP:
            nbSbCfg |=  NB_SB_TSAP_CFG;
            break;
         case STSBSCTSAP:
#ifdef MULTI_ENB_SUPPORT
            inst++;
            if(inst >= smCfgCb.numOfEnbs)
            {
               nbSbCfg |=  NB_SB_SCT_SAP_CFG;
               inst = 0;
            }
#else
            nbSbCfg |=  NB_SB_SCT_SAP_CFG;
#endif
            break;
         default:
            break; 
      } /* end of switch */ 
      NB_LOG_DEBUG(&nbCb,"SCTP Cfg Cfm received for the element [%d]",
            cfm->hdr.elmId.elmnt);

      if (nbSbCfg == NB_SM_SB_CONFIGURED)
      {
         /* Initiate S1AP configuration after SCTP configuration. 
            So send EVTWRS1APCFG */
         smCfgCb.smState = NB_SM_STATE_SCTP_CFG_DONE;
         smNbProcSm(EVTNBS1APCFG);
      }  

   }
  else if(cfm->cfm.status == LCM_PRIM_OK_NDONE)
  {
     nbUiSendConfigFailIndToUser(NB_SCTP_CFG_FAILED);  
     smCfgCb.smState  = NB_SM_STATE_INIT;
  }
   RETVALUE(ROK);
} /* end of SmMiLsbCfgCfm */

/*
 *
 *       Fun:    SmMiLsbCntrlCfm - control confirm
 *
 *       Desc:   prints the control confirm status
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLsbCntrlCfm
(
Pst         *pst,
SbMgmt     *cntrl
)
#else
PUBLIC S16 SmMiLsbCntrlCfm(pst, cntrl)
Pst         *pst;
SbMgmt     *cntrl;
#endif /* ANSI */
{
   Pst  sbPst;

   TRC2(SmMiLsbCntrlCfm)

   SM_SET_ZERO(&sbPst, sizeof(Pst));
   if (cntrl->hdr.elmId.elmnt == STSBTSAP) 
   {
      if (cntrl->cfm.status == LCM_PRIM_OK)
      {
          NB_LOG_DEBUG(&nbCb,"BIND OF SCTP TSAP WITH TUCL SUCCESSFUL");

         /* initiate the bind control request for S1AP and SCTP Saps */
         smBindUnBindSzToLSap(ABND_ENA);
      }
      else if (cntrl->cfm.status == LCM_PRIM_OK_NDONE)
      {
         NB_LOG_DEBUG(&nbCb,"Bind of SCTP TSap with TUCL is in progress");
      } /* end of if statement */
      else 
      {
         NB_LOG_ERROR(&nbCb,"Bind of SCTP TSap with TUCL failed");
      }
   }
   RETVALUE(ROK);
} /* end of SmMiLsbCntrlCfm() */

/*
 *
 *       Fun:    SmMiLsbStsCfm - statistics confirm
 *
 *       Desc:   prints the statistics confirm status
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_sm_sb_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLsbStsCfm
(
Pst         *pst,
SbMgmt     *sts
)
#else
PUBLIC S16 SmMiLsbStsCfm(pst, sts)
Pst         *pst;
SbMgmt     *sts;
#endif /* ANSI */
{
   TRC2(SmMiLsbStsCfm)

   RETVALUE(ROK);
} /* end of SmMiLsbStsCfm() */

/*
 *
 *       Fun:    SmMiLsbStaCfm - status confirm
 *
 *       Desc:   prints the status confirm 
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_sm_sb_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLsbStaCfm
(
Pst         *pst,
SbMgmt     *sta
)
#else
PUBLIC S16 SmMiLsbStaCfm(pst, sta)
Pst         *pst;
SbMgmt     *sta;
#endif /* ANSI */
{
   TRC2(SmMiLsbStaCfm)

   RETVALUE(ROK);
} /* end of SmMiLsbStaCfm() */

/*
 *
 *       Fun:    SmMiLsbStaInd - status indication
 *
 *       Desc:   prints the status indication
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_sm_sb_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLsbStaInd
(
Pst         *pst,
SbMgmt     *ind
)
#else
PUBLIC S16 SmMiLsbStaInd(pst, ind)
Pst         *pst;
SbMgmt     *ind;
#endif /* ANSI */
{
   TRC2(SmMiLsbStaInd);

   RETVALUE(ROK);
} /* end of SmMiLsbStaInd() */

/*
 *
 *       Fun:    SmMiLsbTrcInd - trace indication
 *
 *       Desc:   prints the trace indication
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_sm_sb_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLsbTrcInd
(
Pst         *pst,
SbMgmt     *trc
)
#else
PUBLIC S16 SmMiLsbTrcInd(pst, trc)
Pst         *pst;
SbMgmt     *trc;
#endif /* ANSI */
{
   TRC2(SmMiLsbTrcInd)

   RETVALUE(ROK);
} /* end of SmMiLsbTrcInd() */

