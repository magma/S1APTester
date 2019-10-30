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

    File:  nb_smm_s1ap.c

     Sid:      

     Prg:       

**********************************************************************/

/* header include files (.h) */
#include "nb.h"
#include "rl_interface.h"
#include "rl_common.h"
#include "sct.h"
#include "lsz.h"
#include "fw_tst.h"
#include "nb_smm_init.h"
#include "nbt.h"
#include "nb_log.h"

#include "sct.x"
#include "lsz.x"
#include "nbt.x"

EXTERN Bool nbEmmGetMmeStatus(U32 mmeId);


PRIVATE U8 nbSzCfg = 0;

/*
*
*       Fun:   Initialize S1AP task.
*
*       Desc:  Invoked to create S1AP Tapa task.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_sz_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smSzInit
(
SSTskId    sysTskId
)
#else
PUBLIC S16 smSzInit(sysTskId)
SSTskId    sysTskId;
#endif
{
   TRC2(smSzInit)
 
   /* Register S1AP TAPA Task */
   if (SRegTTsk((Ent)ENTSZ, (Inst)0, (Ttype)TTNORM, (Prior)PRIOR2,
                 szActvInit, (ActvTsk)szActvTsk) != ROK) 
   {
      RETVALUE(RFAILED);
   }

   /* Attach S1AP TAPA Task */
   if (SAttachTTsk((Ent)ENTSZ, (Inst)0, sysTskId)!= ROK) 
   {
      RETVALUE(RFAILED);
   }

   NB_LOG_DEBUG(&nbCb,"S1AP Tapa Task successfully registered and attached to %d",
      sysTskId);

   RETVALUE(ROK);
} /* end of smSzInit */

/*
 *
 *       Fun:    nbSmSzCfg - configure SZ 
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *      File:    wr_sm_sz_cntrl.c
 *
 */

#ifdef ANSI
PUBLIC Void nbSmSzCfg
(
Void
)
#else
PUBLIC Void nbSmSzCfg()
#endif /* ANSI */
{
#ifdef MULTI_ENB_SUPPORT
   S16 inst = 0;
#endif
   TRC2(nbSmSzCfg)
   nbSzCfg = 0;
   smBuildSzGenCfg();
   smBuildSzProtCfg();
#ifdef MULTI_ENB_SUPPORT
   for(inst = 0; inst < smCfgCb.numOfEnbs; inst++) 
   {
      smBuildSzLSapCfg((SZ_SB_SPID+inst), (SZ_SB_SUID+inst));
   }
#else
   smBuildSzLSapCfg(SZ_SB_SPID, SZ_SB_SUID);
#endif
   smBuildSzUSapCfg(NB_SZ_SPID);
   smBuildSzPeerCfg();

   RETVOID;
} /* end of nbSmSzCfg */


/*
*
*       Fun:   smBuildSzGenCfg
*
*       Desc:  fill in genCfg for SZ
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_sz_cntrl.c 
*
*/
#ifdef ANSI
PUBLIC S16 smBuildSzGenCfg
(
Void
)
#else
PUBLIC S16 smBuildSzGenCfg()
#endif
{
   SzMngmt  szMgt;
   SzGenCfg    *cfg = NULLP;
   Pst       pst;

   TRC2(smBuildSzGenCfg)

   SM_SET_ZERO(&szMgt, sizeof(SzMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg   = &(szMgt.u.cfg.u.gen);

   /*----------- Fill General Configuration Parameters ---------*/
   cfg->nmbSztSaps = (S16)NBSM_LSZ_MAX_SZTSAP;
#ifdef MULTI_ENB_SUPPORT
   cfg->nmbSctSaps = (S16)smCfgCb.numOfEnbs;
#else
   cfg->nmbSctSaps = (S16)NBSM_LSZ_MAX_SCTSAP;
#endif
#ifdef MULTI_ENB_SUPPORT
   cfg->nmbConn = (U32)MAX_UE_INST;
#else
   cfg->nmbConn = (U32)(NBSM_LSZ_MAX_PEER * NB_MAX_UES_PER_CELL);
#endif 
   cfg->nmbPeer = (U32)NBSM_LSZ_MAX_PEER;
   cfg->timeRes = (S16)NBSM_LSZ_TIMERES; /* wr004.102 : klock warning fixed */

   cfg->lmPst.srcProcId = SM_SZ_PROC;
   cfg->lmPst.dstProcId = SM_SM_PROC;
   cfg->lmPst.srcEnt = (Ent)ENTSZ;
   cfg->lmPst.dstEnt = (Ent)ENTSM;
   cfg->lmPst.srcInst = (Inst)0;
   cfg->lmPst.dstInst = (Inst)0;
   cfg->lmPst.prior = (Prior)NBSM_MSGPRIOR;
   cfg->lmPst.route = (Route)RTESPEC;
   cfg->lmPst.event = (Event)EVTNONE;
   cfg->lmPst.region = SZ_MEM_REGION;
   cfg->lmPst.pool =  SZ_POOL;
   cfg->lmPst.selector = (Selector)NBSM_SZSMSEL;

   /* Fill Header */
   szMgt.hdr.msgType             = TCFG;
   szMgt.hdr.msgLen              = 0;
   szMgt.hdr.entId.ent           = ENTSZ;
   szMgt.hdr.entId.inst          = SM_INST_ZERO;
   szMgt.hdr.elmId.elmnt         = STSZGEN;
   szMgt.hdr.elmId.elmntInst1    = 0;
   szMgt.hdr.elmId.elmntInst2    = 0;
   szMgt.hdr.elmId.elmntInst3    = 0;
   szMgt.hdr.seqNmb              = 0;
   szMgt.hdr.version             = 0;
   szMgt.hdr.transId             = 0;

   szMgt.hdr.response.prior      = PRIOR0;
   szMgt.hdr.response.route      = RTESPEC;
   szMgt.hdr.response.mem.region = SZ_MEM_REGION;
   szMgt.hdr.response.mem.pool   = SZ_POOL;
   szMgt.hdr.response.selector   = SM_SELECTOR_LC;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTSZ;
   pst.dstProcId = SM_SZ_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCfgCb.init.region;

   NB_LOG_DEBUG(&nbCb,"S1AP Gen Cfg sent");

   /* Send the request to the LM */
   (Void) SmMiLszCfgReq(&pst, &szMgt);
 
   RETVALUE(ROK);
}/* smBuildSzGenCfg */

/*
*
*       Fun:   smBuildSzLSapCfg
*
*       Desc:  Call handler for TSAP Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_sz_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildSzLSapCfg
(
SuId        suId,             /* S1AP Sap ID */
SpId        spId              /* Service Provider Sap ID */
)
#else
PUBLIC S16 smBuildSzLSapCfg(suId, spId)
SuId        suId;             /* S1AP Sap ID */
SpId        spId;             /* Service Provider Sap ID */
#endif
{
   SzMngmt  szMgt;
   SzSctSapCfg  *cfg = NULLP;
   Pst       pst;
 
   TRC2(smBuildSzLSapCfg)

   SM_SET_ZERO(&szMgt, sizeof(SzMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg   = &(szMgt.u.cfg.u.sctSap);

   cfg->suId   = suId;
   cfg->spId   = spId;

   cfg->selector     = NBSM_SZSBSEL;
   cfg->mem.region   = SZ_MEM_REGION;
   cfg->mem.pool     = SZ_POOL;
   cfg->priority     = PRIOR0;
   cfg->route        = RTESPEC;
   cfg->dstProcId    = SM_SB_PROC;
   cfg->dstEntId     = ENTSB;
   cfg->dstInstId    = (Inst)0;

   cfg->tBndTmr.enb = TRUE; /* Multi ENB support */
   cfg->tBndTmr.val = 1000; /* NBSM_LSZ_VAL_10;*/
   cfg->maxBndRetry = NBSM_LSZ_VAL_3;

#ifdef LSZV1
   /* wr004.102: Fill source address info */
#ifdef MULTI_ENB_SUPPORT
   cfg->srcAddr.sctPort = (NBSM_LSZ_ENB_SCTPORT + suId);
#else 
   cfg->srcAddr.sctPort = NBSM_LSZ_ENB_SCTPORT;
#endif
   cfg->srcAddr.ipAddr.nmb = 1;
   cfg->srcAddr.ipAddr.nAddr[0].type = CM_IPV4ADDR_TYPE;
   cfg->srcAddr.ipAddr.nAddr[0].u.ipv4NetAddr = smCfgCb.enbIpAddr;
#endif /* LSZV1 */

   /* Fill Header */
   szMgt.hdr.msgType             = TCFG;
   szMgt.hdr.msgLen              = 0;
   szMgt.hdr.entId.ent           = ENTSZ;
   szMgt.hdr.entId.inst          = SM_INST_ZERO;
   szMgt.hdr.elmId.elmnt         = STSZSCTSAP;
   szMgt.hdr.response.mem.region = SZ_MEM_REGION;
   szMgt.hdr.response.mem.pool   = SZ_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTSZ;
   pst.dstProcId = SM_SZ_PROC;
   pst.srcProcId = SM_SM_PROC;

   NB_LOG_DEBUG(&nbCb,"S1AP LSap Cfg sent");

   pst.region = smCfgCb.init.region;
   /* Send the request to the LM */
   (Void) SmMiLszCfgReq(&pst, &szMgt);
 
   RETVALUE(ROK);
}/* smBuildSzLSapCfg */


/*
*
*       Fun:   smBuildSzUSapCfg
*
*       Desc:  Call handler for SSAP Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_sz_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildSzUSapCfg
(
SpId        spId              /* Service Provider Sap ID */
)
#else
PUBLIC S16 smBuildSzUSapCfg(spId)
SpId        spId;             /* Service Provider Sap ID */
#endif
{
   SzMngmt  szMgt;
   SzSztSapCfg    *cfg = NULLP;
   Pst      pst;
 
   TRC2(smBuildSzUSapCfg)

   SM_SET_ZERO(&szMgt, sizeof(SzMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg = &(szMgt.u.cfg.u.sztSap);

   cfg->spId   = spId;
   cfg->selector     = NBSM_SZNBSEL;
   cfg->mem.region   = SZ_MEM_REGION;
   cfg->mem.pool     = SZ_POOL;
   cfg->priority     = PRIOR0;
   cfg->route        = RTESPEC;

   /* Fill Header */
   szMgt.hdr.msgType             = TCFG;
   szMgt.hdr.msgLen              = 0;
   szMgt.hdr.entId.ent           = ENTSZ;
   szMgt.hdr.entId.inst          = SM_INST_ZERO;
   szMgt.hdr.elmId.elmnt         = STSZSZTSAP;
   szMgt.hdr.response.mem.region = SZ_MEM_REGION;
   szMgt.hdr.response.mem.pool   = SZ_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTSZ;
   pst.dstProcId = SM_SZ_PROC;
   pst.srcProcId = SM_SM_PROC;
   
   NB_LOG_DEBUG(&nbCb,"S1AP USap Cfg sent");

   pst.region = smCfgCb.init.region;
   /* Send the request to the LM */
   (Void) SmMiLszCfgReq(&pst, &szMgt);
 
   RETVALUE(ROK);
}/* smBuildSzUSapCfg */


/*
*
*       Fun:   smBuildSzProtCfg
*
*       Desc:  Call handler for Protocol Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_sz_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildSzProtCfg
(
Void
)
#else
PUBLIC S16 smBuildSzProtCfg()
#endif
{
   SzMngmt  szMgt;
   SzProtCfg *protCfg = NULLP;
   Pst      pst;
 
   TRC2(smBuildSzProtCfg)

   SM_SET_ZERO(&szMgt, sizeof(SzMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   protCfg = &(szMgt.u.cfg.u.prot);

#ifndef LSZV1   
   /* wr004.102: Compilation error fix */
   protCfg->srcAddr.ipAddr.nmb  =   1;
   protCfg->srcAddr.ipAddr.nAddr[0].type  =   CM_IPV4ADDR_TYPE;
   protCfg->srcAddr.ipAddr.nAddr[0].u.ipv4NetAddr   =  smCfgCb.enbIpAddr;
   protCfg->srcAddr.sctPort =   NBSM_LSZ_ENB_SCTPORT;
#endif /* LSZV1 */
#ifdef SZ_ENB   
   protCfg->nodeType =   LSZ_NODE_ENB;
   protCfg->u.eNbId     =   NBSM_LSZ_ENB_PRC0;
#endif /* SZ_ENB */   

   /* Fill Header */
   szMgt.hdr.msgType             = TCFG;
   szMgt.hdr.msgLen              = 0;
   szMgt.hdr.entId.ent           = ENTSZ;
   szMgt.hdr.entId.inst          = SM_INST_ZERO;
   szMgt.hdr.elmId.elmnt         = STSZPROT;
   szMgt.hdr.response.mem.region = SZ_MEM_REGION;
   szMgt.hdr.response.mem.pool   = SZ_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTSZ;
   pst.dstProcId = SM_SZ_PROC;
   pst.srcProcId = SM_SM_PROC;
 
   NB_LOG_DEBUG(&nbCb,"S1AP Protocol Cfg sent");

   pst.region = smCfgCb.init.region;
   /* Send the request to the LM */
   (Void) SmMiLszCfgReq(&pst, &szMgt);
 
   RETVALUE(ROK);
}/* smBuildSzProtCfg */

/*
*
*       Fun:   smBuildSzPeerCfg
*
*       Desc:  Call handler for Peer Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_sz_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildSzPeerCfg
(
Void
)
#else
PUBLIC S16 smBuildSzPeerCfg()
#endif
{
   SzMngmt  szMgt;
   SzPeerCfg *cfg = NULLP;
   SctNetAddrLst *addrLst = NULLP;
   U16      cnt;
   Pst      pst;
   U8       idx; 
   TRC2(smBuildSzPeerCfg)

   SM_SET_ZERO(&szMgt, sizeof(SzMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg = &(szMgt.u.cfg.u.peer);

   cfg->nmbPeers = (U32)smCfgCb.noOfCfg;
   if(0 == cfg->nmbPeers)
   {
      nbSzCfg |= NB_SZ_PEER_CFG;
      NB_LOG_DEBUG(&nbCb,"There are no S1AP Peer Cfg present now");
      RETVALUE(ROK);
   }

   if(cfg->nmbPeers >= NBSM_LSZ_MAX_PEER)
   {
      nbSzCfg |= NB_SZ_PEER_CFG;
      NB_LOG_DEBUG(&nbCb,"There are more than cfged S1AP Peers present now.");
      RETVALUE(ROK);
   }
   
   NBSM_ALLOC(&cfg->peerInfo, sizeof(SzPeerInfo)* cfg->nmbPeers);
   /* wr004.102 : klock warning fixed */
   if(cfg->peerInfo == NULLP)
   {
      nbSzCfg |= NB_SZ_PEER_CFG;
      NB_LOG_ERROR(&nbCb,"Failure in the allocation of cfg");
      RETVALUE(RFAILED);
   } /* end of if statement */

   for (cnt= 0 ; ((cnt < cfg->nmbPeers) && (cnt < MAX_NUM_PEER)); cnt++)
   {
#ifdef SZ_ENB
      cfg->peerInfo[cnt].type                   =  LSZ_NODE_MME;   
      cfg->peerInfo[cnt].peerId.pres            =  TRUE; 
      cfg->peerInfo[cnt].peerId.val             =  smCfgCb.mmeCfg[cnt]->mmeId; 
      cfg->peerInfo[cnt].uSapId                 =  NB_SZ_SPID;  
      cfg->peerInfo[cnt].sapId                  =  NB_SZ_SUID;  
      cfg->peerInfo[cnt].assocCfg.locOutStrms   =  NBSM_LSZ_OUT_STRMS;

      cfg->peerInfo[cnt].assocCfg.priDstAddr.type    =  CM_IPV4ADDR_TYPE;
      cfg->peerInfo[cnt].assocCfg.priDstAddr.u.ipv4NetAddr = smCfgCb.mmeCfg[cnt]->mmeAddr[0] ;
      addrLst = &cfg->peerInfo[cnt].assocCfg.dstAddrLst;
      addrLst->nmb     = 1;
      for(idx = 0; idx < (addrLst->nmb ); idx++)
      {
         addrLst->nAddr[idx].type  =  CM_IPV4ADDR_TYPE;
         addrLst->nAddr[idx].u.ipv4NetAddr = smCfgCb.mmeCfg[cnt]->mmeAddr[0];
      }
      cfg->peerInfo[cnt].assocCfg.dstPort            =  NBSM_LSZ_MME_SCTPORT;
      cfg->peerInfo[cnt].assocCfg.nmbRetry           =  NBSM_LSZ_VAL_3;
      cfg->peerInfo[cnt].assocCfg.tmrAssocRecov.enb  =  TRUE;
      cfg->peerInfo[cnt].assocCfg.tmrAssocRecov.val  =  NBSM_LSZ_VAL_50;

#endif /* SZ_ENB */
  } 

   /* Fill Header */
   szMgt.hdr.msgType             = TCFG;
   szMgt.hdr.msgLen              = 0;
   szMgt.hdr.entId.ent           = ENTSZ;
   szMgt.hdr.entId.inst          = SM_INST_ZERO;
   szMgt.hdr.elmId.elmnt         = STSZPEER;
   szMgt.hdr.response.mem.region = SZ_MEM_REGION;
   szMgt.hdr.response.mem.pool   = SZ_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTSZ;
   pst.dstProcId = SM_SZ_PROC;
   pst.srcProcId = SM_SM_PROC;
 
   NB_LOG_DEBUG(&nbCb,"S1AP Peer Cfg sent");

   pst.region = smCfgCb.init.region;
   /* Send the request to the LM */
   (Void) SmMiLszCfgReq(&pst, &szMgt);
 
   RETVALUE(ROK);
}/* smBuildSzPeerCfg */


 /*
 *      FUN:   smBldSzPeerDelCntrlReq
 *
 *      Desc:  Builds the delete peer control request and sends it to
 *             S1AP
 *
 *      Ret:   void
 *
 *      Notes: None
 *
 *      File:  wr_smm_s1ap.c
 *
 *
 */
#ifdef ANSI
PUBLIC S16 smBldSzPeerDelCntrlReq
(
U8    peerId,
U8    dbIndex
)
#else
PUBLIC S16 smBldSzPeerDelCntrlReq()
U8    peerId;
U8    dbIndex;
#endif /* ANSI */
{
   SzMngmt  cntrl;
   Pst      pst;
   
   TRC2(smBldSzPeerDelCntrlReq)
   
   SM_SET_ZERO(&cntrl, sizeof(SzMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   cntrl.u.cntrl.action        = ADEL;
   cntrl.u.cntrl.subAction    = SAELMNT;
   /* At present we are deleting only one peer at a time */
   cntrl.u.cntrl.u.peer.nmbPeers = 1;
   NBSM_ALLOC(&(cntrl.u.cntrl.u.peer.peerId), ((sizeof(TknU32)) * cntrl.u.cntrl.u.peer.nmbPeers));
   if(cntrl.u.cntrl.u.peer.peerId == NULLP)
   {
      NB_LOG_ERROR(&nbCb,"Failure in the allocation of cfg");
      RETVALUE(RFAILED);
   } /* end of if statement */
 
   /* Fill the peerid value which needs to be deleted */
   cntrl.u.cntrl.u.peer.peerId[0].pres = PRSNT_NODEF;
   cntrl.u.cntrl.u.peer.peerId[0].val = peerId;

   /* Fill the index which will be used when we receive the confirmation
    * for the delete peer request */
   cntrl.hdr.transId             = dbIndex;
   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTSZ;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt         = STSZPEER;
   cntrl.hdr.response.mem.region = SZ_MEM_REGION;
   cntrl.hdr.response.mem.pool   = SZ_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTSZ;
   pst.dstProcId = SM_SZ_PROC;
   pst.srcProcId = SM_SM_PROC;

   NB_LOG_DEBUG(&nbCb,"Delete S1AP Peer Cfg sent for Dynamic MME Delete");

    /* Send the control request to the S1AP */
   (Void)SmMiLszCntrlReq(&pst, &cntrl);
   RETVALUE(ROK);
} /* end of smBldSzPeerDelCntrlReq */
 


/*
 *      FUN:   smBindUnBindSzToLSap
 *
 *      Desc:  Bind and unbind S1AP to lower SAP
 *
 *      Ret:   void
 *
 *      Notes: None
 *
 *      File:  wr_smm_s1ap.c
 *
 *
 */
#ifdef ANSI
PUBLIC S16 smBindUnBindSzToLSap
(
U8 action
)
#else
PUBLIC S16 smBindUnBindSzToLSapp(action)
U8 action;
#endif /* ANSI */
{
   SzMngmt  cntrl;
   Pst      pst;
   S16      ret = ROK;
#ifdef MULTI_ENB_SUPPORT
   S16      inst = 0;
#endif
   
   TRC2(smBindUnBindSzToLSap)
   
   SM_SET_ZERO(&cntrl, sizeof(SzMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   
   cntrl.u.cntrl.action        = action;
   cntrl.u.cntrl.subAction    = 0;
#ifndef MULTI_ENB_SUPPORT
   cntrl.u.cntrl.u.sap.id       = NB_SZ_SUID;
#endif

   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTSZ;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt         = STSZSCTSAP;
   cntrl.hdr.response.mem.region = SZ_MEM_REGION;
   cntrl.hdr.response.mem.pool   = SZ_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTSZ;
   pst.dstProcId = SM_SZ_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCfgCb.init.region;
#ifdef MULTI_ENB_SUPPORT
   for(inst = 0; inst < smCfgCb.numOfEnbs; inst++)
   {
      cntrl.u.cntrl.u.sap.id = (NB_SZ_SUID+inst);
#endif

      if (action == ABND_ENA)
      {
         NB_LOG_DEBUG(&nbCb,"S1AP Cntrl Req to bind with lower sap (sapId = %d)",
            cntrl.u.cntrl.u.sap.id);
      }
      else
      {
        NB_LOG_ERROR(&nbCb,"S1AP Cntrl Req to unbind with lower sap");
      }

      /* Send the control request to the S1AP */
      (Void)SmMiLszCntrlReq(&pst, &cntrl);
#ifdef MULTI_ENB_SUPPORT
   }
#endif

   RETVALUE(ret);
} /* end of smBindUnBindSzToLSap */

/*
*
*       Fun:   smBuildSzGenCntrl
*
*       Desc:  Invoked to Enable Alarms at S1AP
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_sz_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildSzGenCntrl
(
)
#else
PUBLIC S16 smBuildSzGenCntrl(Void)
#endif
{
   SzMngmt cntrl;
   Pst      pst;
   
   TRC2(smBuildSzGenCntrl)
   
   SM_SET_ZERO(&cntrl, sizeof(SzMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cntrl.u.cntrl.action        =  AENA;
   cntrl.u.cntrl.u.sap.id      =  0;
   cntrl.u.cntrl.subAction     =  SAUSTA;

   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTSZ;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt         = STSZGEN;
   cntrl.hdr.response.mem.region = SZ_MEM_REGION;
   cntrl.hdr.response.mem.pool   = SZ_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTSZ;
   pst.dstProcId = SM_SZ_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCfgCb.init.region;
   
   NB_LOG_DEBUG(&nbCb,"S1AP Gen Cntrl Req to sz sent");

   /* Send the request to the S1AP */
   SmMiLszCntrlReq(&pst, &cntrl);

   RETVALUE(ROK);
} /* end of smBuildSzGenCntrl */

/*
*
*       Fun:   smBuildSzDbgCntrl
*
*       Desc:  Invoked to Enable Debugs at S1AP
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_sz_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildSzDbgCntrl
(
)
#else
PUBLIC S16 smBuildSzDbgCntrl(Void)
#endif
{
   SzMngmt cntrl;
   Pst      pst;

   TRC2(smBuildSzDbgCntrl)
   
   SM_SET_ZERO(&cntrl, sizeof(SzMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cntrl.u.cntrl.action        =  AENA;
   cntrl.u.cntrl.subAction     =  SADBG;
#ifdef DEBUGP
   cntrl.u.cntrl.u.dbg.dbgMask =  0xffffffff;
#endif

   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTSZ;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt         = STSZGEN;
   cntrl.hdr.response.mem.region = SZ_MEM_REGION;
   cntrl.hdr.response.mem.pool   = SZ_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTSZ;
   pst.dstProcId = SM_SZ_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCfgCb.init.region;
   
   NB_LOG_DEBUG(&nbCb,"S1AP Dbg Cntrl Req to sz sent");

   /* Send the request to the S1AP */
   SmMiLszCntrlReq(&pst, &cntrl);

   RETVALUE(ROK);
} /* end of smBuildSzGenCntrl */

/* IPSec Recovery */
/*
*
*       Fun:   smBuildSzShutDownCntrl
*
*       Desc:  Invoked to shut down S1AP
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_sz_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildSzShutDownCntrl
(
)
#else
PUBLIC S16 smBuildSzShutDownCntrl(Void)
#endif
{
   SzMngmt cntrl;
   Pst      pst;
   
   TRC2(smBuildSzShutDownCntrl)
   
   SM_SET_ZERO(&cntrl, sizeof(SzMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cntrl.u.cntrl.action        =  ASHUTDOWN;
   /* cntrl.u.cntrl.u.sap.id      =  0; */ /* Needed? */
   cntrl.u.cntrl.subAction     =  NULLD;

   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTSZ;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt         = STSZGEN;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTSZ;
   pst.dstProcId = SM_SZ_PROC;
   pst.srcProcId = SM_SM_PROC;
   
   NB_LOG_DEBUG(&nbCb,"S1AP shut down Cntrl Req to sz sent");

   /* Send the request to the S1AP */
   SmMiLszCntrlReq(&pst, &cntrl);

   RETVALUE(ROK);
} /* end of smBuildSzGenCntrl */

/* IPSec Recovery */


/*
*
*       Fun:    activate task
*
*       Desc:   Processes received event from SZ
*
*       Ret:    ROK  - ok
*
*       Notes:  None
*
*       File:   wr_sm_sz_exms.c
*
*/

#ifdef ANSI
PUBLIC S16 smSzActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 smSzActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   S16 ret;

   TRC2(smSzActvTsk)

   ret = ROK;

   switch(pst->event)
   {
#ifdef LCSMMILSZ
      case EVTLSZCFGCFM:             /* Config confirm */
         ret = cmUnpkLszCfgCfm(SmMiLszCfgCfm, pst, mBuf);
         break;
      case EVTLSZCNTRLCFM:           /* Control confirm */
         ret = cmUnpkLszCntrlCfm(SmMiLszCntrlCfm, pst, mBuf);
         break;
      case EVTLSZSTAIND:             /* Status Indication */
         ret = cmUnpkLszStaInd(SmMiLszStaInd, pst, mBuf);
         break;
#endif
      default:
         NB_FREEMBUF(mBuf);
         ret = RFAILED;
         NB_LOG_ERROR(&nbCb,"Received invalid event %d", pst->event);
         break;
   }

   RETVALUE(ret);

} /* end of smSzActvTsk */

/*local defines */
#define SM_MAX_SZ_SEL 4


/*local typedefs */

/*forward references */
PUBLIC S16 PtMiLszCfgReq      (Pst *post, SzMngmt *cfg);
PUBLIC S16 PtMiLszStsReq      (Pst *post, Action action, SzMngmt *sts);
PUBLIC S16 PtMiLszStaReq      (Pst *post, SzMngmt *ssta);
PUBLIC S16 PtMiLszCntrlReq    (Pst *post, SzMngmt *cntrl);

/* public variable declarations */

/* public variable definitions */

/* private variable definitions */

/* public routines */

/* Following matrices define the mapping between the primitives called by the
 * layer manager (as SmMiLszXXXReq) and the corresponding primitives of the 
 * S1AP layer (layer management service provider) (as SzMiLszXXXReq).
 * Each primitive is mapped to one of SM_MAX_SZ_SEL functions in the array.
 * The mapping is based on post->selector.
 * Selector          #define     Coupling      Primitive
 * 0 (SEL_LC_NEW)   LCSMMILSZ    loose         cmPkMiLszXXXReq
 * 1                 MG          tight         SzMiLszXXXReq
 * 2+                            tight         PtMiLszXXXReq
 */

PRIVATE LszCfgReq smMiLszCfgReqMt[] =
{
#ifdef LCSMMILSZ
   cmPkLszCfgReq,
#else
   PtMiLszCfgReq,
#endif

#ifdef SZ
   SzMiLszCfgReq,
#else
   PtMiLszCfgReq,
#endif

};


PRIVATE LszStsReq smMiLszStsReqMt[] =
{
#ifdef LCSMMILSZ
   cmPkLszStsReq,
#else
   PtMiLszStsReq,
#endif

#ifdef SZ
   SzMiLszStsReq,
#else
   PtMiLszStsReq,
#endif

};


PRIVATE LszStaReq smMiLszStaReqMt[] =
{
#ifdef LCSMMILSZ
   cmPkLszStaReq,
#else
   PtMiLszStaReq,
#endif

#ifdef SZ
   SzMiLszStaReq,
#else
   PtMiLszStaReq,
#endif

};


PRIVATE LszCntrlReq smMiLszCntrlReqMt[] =
{
#ifdef LCSMMILSZ
   cmPkLszCntrlReq,
#else
   PtMiLszCntrlReq,
#endif

#ifdef SZ
   SzMiLszCntrlReq,
#else
   PtMiLszCntrlReq,
#endif

};


/*
 *
 *       Fun:    SmMiLszCfgReq - Configuration request
 *
 *       Desc:  
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   wr_sm_sz_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLszCfgReq
(
Pst     *post,       /* post structure */
SzMngmt *cfg        /* management structure */
)
#else
PUBLIC S16 SmMiLszCfgReq(post, cfg)
Pst     *post;       /* post structure */
SzMngmt *cfg;       /* management structure */
#endif
{

   TRC3(SmMiLszCfgReq)

#if (ERRCLASS & ERRCLS_DEBUG)
   if (post == (Pst *) NULLP || post->selector >= SM_MAX_SZ_SEL)
   {
      RETVALUE(RFAILED);
   }
#endif

   RETVALUE((*(smMiLszCfgReqMt[post->selector]))(post, cfg));
} /* end of SmMiLszCfgReq() */

/*
 *
 *       Fun:    SmMiLszStsReq - Statistics request
 *
 *       Desc:  
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   wr_sm_sz_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLszStsReq
(
Pst     *post,       /* post structure */
Action action,
SzMngmt *sts        /* management structure */
)
#else
PUBLIC S16 SmMiLszStsReq(post, action, sts)
Pst     *post;       /* post structure */
Action action;
SzMngmt *sts;       /* management structure */
#endif
{
   TRC3(SmMiLszStsReq)

#if (ERRCLASS & ERRCLS_DEBUG)
   if (post == (Pst *) NULLP || post->selector >= SM_MAX_SZ_SEL)
   {
      RETVALUE(RFAILED);
   }
#endif

   RETVALUE((*(smMiLszStsReqMt[post->selector]))(post, action, sts));
} /* end of SmMiLszStsReq() */

/*
 *
 *       Fun:    SmMiLszStaReq - Status request
 *
 *       Desc:  
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   wr_sm_sz_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLszStaReq
(
Pst     *post,       /* post structure */
SzMngmt *ssta        /* management structure */
)
#else
PUBLIC S16 SmMiLszStaReq(post, ssta)
Pst     *post;       /* post structure */
SzMngmt *ssta;       /* management structure */
#endif
{
   TRC3(SmMiLszStaReq)

#if (ERRCLASS & ERRCLS_DEBUG)
   if (post == (Pst *) NULLP || post->selector >= SM_MAX_SZ_SEL)
   {
      RETVALUE(RFAILED);
   }
#endif

   RETVALUE((*(smMiLszStaReqMt[post->selector]))(post, ssta));
} /* end of SmMiLszStaReq() */

/*
 *
 *       Fun:    SmMiLszCntrlReq - Control request
 *
 *       Desc:  
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   wr_sm_sz_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLszCntrlReq
(
Pst     *post,       /* post structure */
SzMngmt *cntrl        /* management structure */
)
#else
PUBLIC S16 SmMiLszCntrlReq(post, cntrl)
Pst     *post;       /* post structure */
SzMngmt *cntrl;       /* management structure */
#endif
{
   TRC3(SmMiLszCntrlReq)

#if (ERRCLASS & ERRCLS_DEBUG)
   if (post == (Pst *) NULLP || post->selector >= SM_MAX_SZ_SEL)
   {
      RETVALUE(RFAILED);
   }
#endif

   RETVALUE((*(smMiLszCntrlReqMt[post->selector]))(post, cntrl));
} /* end of SmMiLszCntrlReq() */

/*
 *
 *       Fun:    PtMiLszCfgReq - portable configuration request
 *
 *       Desc:  
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   wr_sm_sz_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 PtMiLszCfgReq
(
Pst     *post,       /* post structure */
SzMngmt *cfg        /* management structure */
)
#else
PUBLIC S16 PtMiLszCfgReq(post, cfg)
Pst     *post;       /* post structure */
SzMngmt *cfg;       /* management structure */
#endif
{
   TRC3(PtMiLszCfgReq)

   UNUSED(post);
   UNUSED(cfg);
   RETVALUE(RFAILED);
} /* end of PtMiLszCfgReq() */

/*
 *
 *       Fun:    PtMiLszStsReq - portable statistics request
 *
 *       Desc:  
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   wr_sm_sz_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 PtMiLszStsReq
(
Pst     *post,       /* post structure */
Action action,
SzMngmt *sts        /* management structure */
)
#else
PUBLIC S16 PtMiLszStsReq(post, action, sts)
Pst     *post;       /* post structure */
Action action;
SzMngmt *sts;       /* management structure */
#endif
{
   TRC3(PtMiLszStsReq)

   UNUSED(post);
   UNUSED(action);
   UNUSED(sts);
   RETVALUE(RFAILED);
} /* end of PtMiLszStsReq() */

/*
 *
 *       Fun:    PtMiLszStaReq - portable status request
 *
 *       Desc:  
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   wr_sm_sz_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 PtMiLszStaReq
(
Pst     *post,       /* post structure */
SzMngmt *ssta        /* management structure */
)
#else
PUBLIC S16 PtMiLszStaReq(post, ssta)
Pst     *post;       /* post structure */
SzMngmt *ssta;       /* management structure */
#endif
{
   TRC3(PtMiLszStaReq)

   UNUSED(post);
   UNUSED(ssta);
   RETVALUE(RFAILED);
} /* end of PtMiLszStaReq() */

/*
 *
 *       Fun:    PtMiLszCntrlReq - portable control request
 *
 *       Desc:  
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   wr_sm_sz_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 PtMiLszCntrlReq
(
Pst     *post,       /* post structure */
SzMngmt *cntrl        /* management structure */
)
#else
PUBLIC S16 PtMiLszCntrlReq(post, cntrl)
Pst     *post;       /* post structure */
SzMngmt *cntrl;       /* management structure */
#endif
{
   TRC3(PtMiLszCntrlReq)

   UNUSED(post);
   UNUSED(cntrl);
   RETVALUE(RFAILED);
} /* end of PtMiLszCntrlReq() */

/*
*
*       Fun:   Configuration Confirm
*
*       Desc:  This function is used by to present configuration confirm
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  wr_sm_sz_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLszCfgCfm
(
Pst     *pst,          /* post structure */
SzMngmt *cfm           /* configuration */
)
#else
PUBLIC S16 SmMiLszCfgCfm(pst, cfm)
Pst     *pst;          /* post structure */
SzMngmt *cfm;          /* configuration */
#endif
{
#ifdef MULTI_ENB_SUPPORT
   PRIVATE U32 inst = 0;
#endif
   Pst      szPst;

   TRC2(SmMiLszCfgCfm);

   SM_SET_ZERO(&szPst, sizeof(Pst));
   NB_LOG_DEBUG(&nbCb,"S1AP Cfg Cfm received for the element %d",
         cfm->hdr.elmId.elmnt);

   if (cfm->cfm.status == LCM_PRIM_OK)
   {
      switch (cfm->hdr.elmId.elmnt)
      {
         case STSZGEN:
            nbSzCfg |= NB_SZ_GEN_CFG;
            break;      
         case STSZPROT:
            nbSzCfg |= NB_SZ_PROT_CFG;
            break;
         case STSZSZTSAP:
            nbSzCfg |= NB_SZ_SZT_SAP_CFG;
            break;
         case STSZSCTSAP:
#ifdef MULTI_ENB_SUPPORT
            inst++;
            if(inst >= smCfgCb.numOfEnbs)
            {
               nbSzCfg |= NB_SZ_SCT_SAP_CFG;
               inst = 0;
            }
#else
            nbSzCfg |= NB_SZ_SCT_SAP_CFG;
#endif
            break;
         case STSZPEER:
            nbSzCfg |= NB_SZ_PEER_CFG;
            break;
         default:
            break;
      } /* end of switch statement */

      if (nbSzCfg == NB_SM_SZ_CONFIGURED)
      {
         smCfgCb.smState = NB_SM_STATE_S1AP_CFG_DONE;
         smNbProcSm(EVTNBEGTPCFG);
      }
   }  
   else if(cfm->cfm.status == LCM_PRIM_OK_NDONE)
   {
      nbUiSendConfigFailIndToUser(NB_S1AP_CFG_FAILED);  
      smCfgCb.smState  = NB_SM_STATE_INIT;
   }
   else
   {
      NB_LOG_ERROR(&nbCb,"S1AP Configuration confirm not OK");

   }

   RETVALUE(ROK);
} /* end of SmMiLszCfgCfm */

/*
 *
 *       Fun:    SmMiLszCntrlCfm - control confirm
 *
 *       Desc:   prints the control confirm status
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_sm_sz_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLszCntrlCfm
(
 Pst         *pst,
 SzMngmt     *cntrl
 )
#else
PUBLIC S16 SmMiLszCntrlCfm(pst, cntrl)
   Pst         *pst;
   SzMngmt     *cntrl;
#endif /* ANSI */
{
#ifdef MULTI_ENB_SUPPORT
   PRIVATE U32 inst = 0;
#endif
   Pst  szPst;

   TRC2(SmMiLszCntrlCfm);

   SM_SET_ZERO(&szPst, sizeof(Pst));

   /* Initiate control request for binding App to S1AP */
   if(cntrl->hdr.elmId.elmnt == STSZSCTSAP)
   {
      /* Due to unbind */
      if (smCfgCb.smState == NB_SM_STATE_EGTP_STK_UNBND_DONE)
      {
         if (cntrl->cfm.status == LCM_PRIM_OK)
         {
            NB_LOG_DEBUG(&nbCb,"UNBIND OF S1AP WITH SCTP SUCCESSFUL");
            /* Unbind SCTP with TUCL */
            smBindUnBindSbToLSap(SB_HI_SPID,AUBND);
         }
         RETVALUE(ROK);
      }
      else
      {
         NB_LOG_DEBUG(&nbCb,"Bind of S1AP LSap with SCTP Done");
#ifdef MULTI_ENB_SUPPORT
         inst++;
         if(inst >= smCfgCb.numOfEnbs)
         {
            smBindUnBindNbToSztSap(ABND_ENA);
         }
#else
         smBindUnBindNbToSztSap(ABND_ENA);
#endif
      }
   } /* end of if statement */

   if( STSZPEER == cntrl->hdr.elmId.elmnt)
   {
         RETVALUE(ROK);
   }
   RETVALUE(ROK);
} /* end of SmMiLszCntrlCfm() */

/*
 *
 *       Fun:    SmMiLszStaInd - status indication
 *
 *       Desc:   Received the Status Indication
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_sm_sz_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLszStaInd
(
Pst         *pst,
SzMngmt      *staInd
)
#else
PUBLIC S16 SmMiLszStaInd(pst, staInd)
Pst         *pst;
SzMngmt      *staInd;
#endif /* ANSI */
{
   Pst  szPst;
   SzUsta  *usta= NULLP;
   SzUstaDgn *dgn;

   TRC2(SmMiLszStaInd)

   SM_SET_ZERO(&szPst, sizeof(Pst));
   usta = &(staInd->u.usta);
   dgn = &(usta->dgn);

   if (usta->alarm.event == LSZ_EVENT_LI_ASSOC_CFM  
         && usta->alarm.cause == LSZ_CAUSE_ASSOC_UP) 
   {
      NB_LOG_DEBUG(&nbCb,"S1AP ASSOCIATION SUCCESSFULLY ESTABLISHED");
   }
   else if (usta->alarm.category == LCM_CATEGORY_INTERFACE)
   {
      if (usta->alarm.event == LCM_EVENT_BND_OK)
      {
         NB_LOG_DEBUG(&nbCb,"BIND OF S1AP lsap id[%d] IS SUCCESSFUL", dgn->u.sapId);
         smBindUnBindNbToSztSap(ABND_ENA); 
      }
      else if (usta->alarm.event == LCM_EVENT_BND_FAIL) 
      {
         NB_LOG_ERROR(&nbCb,"BIND OF S1AP lsap id[%d] FAILED", dgn->u.sapId);
      }
      else if (usta->alarm.event == LSZ_EVENT_LI_TERM_IND)
      {
         NB_LOG_DEBUG(&nbCb,"Term Indication Recvd. lsap id[%d] FAILED",
               dgn->u.sapId);
         /* Updating Stack Manager's state */
         smCfgCb.smState = NB_SM_STATE_AWAIT_S1_CON;
      }
      else
         NB_LOG_DEBUG(&nbCb,
           "Rcvd S1AP ALARM, category %d, event %d, cause %d\n",
           staInd->u.usta.alarm.category,
           staInd->u.usta.alarm.event,
           staInd->u.usta.alarm.cause);
   } /* end of LCM_CATEGORY_INTERFACE */

   RETVALUE(ROK);
} /* end of SmMiLszStaInd() */

/*
 *
 *       Fun:    SmMiLszTrcInd - trace indication
 *
 *       Desc:   Received the Trace Indication
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_sm_sz_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLszTrcInd
(
Pst         *pst,
SzMngmt      *trcInd,
Buffer      *mBuf
)
#else
PUBLIC S16 SmMiLszTrcInd(pst, trcInd, mBuf)
Pst         *pst;
SzMngmt     *trcInd;
Buffer      *mBuf;
#endif /* ANSI */
{
   TRC2(SmMiLszTrcInd)
   NB_LOG_DEBUG(&nbCb,"Received S1AP TrcInd");
   RETVALUE(ROK);

} 
/* end of SmMiLszTrcInd */

/*
 *
 *       Fun:    SmMiLszStaCfm - status confirm
 *
 *       Desc:   Received the Status Confirm
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_sm_sz_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLszStaCfm
(
Pst         *pst,
SzMngmt      *staCfm
)
#else
PUBLIC S16 SmMiLszStaCfm(pst, staCfm)
Pst         *pst;
SzMngmt      *staCfm;
#endif /* ANSI */
{
   TRC2(SmMiLszStaCfm)

   NB_LOG_DEBUG(&nbCb,"Received S1AP StaCfm");
   RETVALUE(ROK);
} /* end of SmMiLszStaCfm() */

/*
 *
 *       Fun:    SmMiLszStsCfm - statistic indication
 *
 *       Desc:   Received the statistic Indication
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_sm_sz_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLszStsCfm
(
Pst         *pst,
SzMngmt      *staInd
)
#else
PUBLIC S16 SmMiLszStsCfm(pst, staInd)
Pst         *pst;
SzMngmt      *staInd;
#endif /* ANSI */
{
   RETVALUE(ROK);
}
