/**********************************************************************

    Name:  LTE S1SIM - ENODEB Application Module 

    Type:  C include file

    Desc:  C source code for ENODEB Application
               
    File:  nb_smm_egtp.c

    Sid:   

    Prg:   

**********************************************************************/

/* header include files (.h) */

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timers defines */
#include "cm_hash.h"       /* common hash list defines */
#include "cm_inet.h"       /* common INET defines */
#include "cm_llist.h"      /* common linked list defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport defines */

#include "leg.h"           /* layer management defines for EGCP */
#include "egt.h"            /* defines and macros for EG */

#ifdef HI
#include "lhi.h"
#include "hit.h"           /* HI layer */
#if 0
#include "hi.h"
#endif
#endif
#include "nbt.h"
/* header/extern include files (.x) */

#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_inet.x"       /* common INET */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_tpt.x"        /* common transport types */

#include "egt.x"           /* EGT Interface Structures */
#include "leg.x"           /* layer management typedefs for EGCP */

#ifdef HI
#include "lhi.x"
#include "hit.x"           /* HI layer */
#if 0
#include "hi.x"
#endif
#endif
#include "nb_lnb.h"
#include "nb.h"
#include "rl_interface.h"
#include "rl_common.h"
#include "nb_smm_init.h"
#include "fw_tst.h"
#include "nbt.x"
#include "nb_log.h"

PRIVATE U8 nbEgCfg = 0;
/*
*
*       Fun:   Initialize E-GTP task.
*
*       Desc:  Invoked to create E-GTP Tapa task.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_eg_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smEgInit
(
SSTskId    sysTskId
)
#else
PUBLIC S16 smEgInit(sysTskId)
SSTskId    sysTskId;
#endif
{
   TRC2(smEgInit)

   /* Register e-gtp TAPA Task */
   if (SRegTTsk((Ent)ENTEG, (Inst)0, (Ttype)TTNORM, (Prior)PRIOR1,
                 egActvInit, (ActvTsk)egActvTsk) != ROK) 
   {
      RETVALUE(RFAILED);
   }

   /* Attach e-gtp TAPA Task */
   if (SAttachTTsk((Ent)ENTEG, (Inst)0, sysTskId)!= ROK) 
   {
      RETVALUE(RFAILED);
   }

   /*RLOG1(L_INFO, "EGTP Tapa Task successfully registered and attached to %d",sysTskId);*/

   RETVALUE(ROK);
} /* end of smEgInit */



/*
*
*       Fun:   smBuildEgGenCntrl
*
*       Desc:  Invoked to Enable Alarms at EgtpU Layer
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_smm_egtp.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildEgGenCntrl
(
)
#else
PUBLIC S16 smBuildEgGenCntrl(Void)
#endif
{
   EgMngmt cntrl;
   Pst      pst;

   /* wr002.102: Corrected function name in trace macro */
   TRC2(smBuildEgGenCntrl)

   SM_SET_ZERO(&cntrl, sizeof(EgMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cntrl.u.cntrl.action        =  AENA;
   cntrl.u.cntrl.subAction     =  SAUSTA;

   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTEG;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt         = STEGGEN;
   cntrl.hdr.response.selector   = SM_SELECTOR_TC;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTEG;
   pst.dstProcId = SM_EG_PROC;
   pst.srcProcId = SM_SM_PROC;

   /*RLOG0(L_EVENT, "RRM Gen Cntrl Req to EG sent");*/

   /* Send the request to the APP */
   SmMiLegCntrlReq(&pst, &cntrl);

   RETVALUE(ROK);
} /* end of smBuildEgGenCntrl */


/*
 *
 *       Fun:    nbSmEgCfg - configure EG
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *      File:    wr_sm_eg_cntrl.c
 *
 */

#ifdef ANSI
PUBLIC Void nbSmEgCfg
(
Void
)
#else
PUBLIC Void nbSmEgCfg()
#endif /* ANSI */
{
   TRC2(nbSmEgCfg)
   nbEgCfg = 0;

#ifdef WR_RSYS_OAM  
   smStartTmr((PTR)&(smCfgCb),SM_TMR_STATIC_CFG_TMR, SM_TMR_STATIC_CFG_TMR_VAL);
#endif
   smBuildEgGenCfg();
   smBuildEgLSapCfg(EG_HI_SUID, EG_HI_SPID);
   smBuildEgUSapCfg(NB_EG_SPID);
   smBuildEgIpAddrCfg(NB_EG_SPID);
   smBuildTServerCfg();

   RETVOID;
} /* end of nbSmEgCfg */



/*
*
*       Fun:   smBuildEgGenCfg
*
*       Desc:  fill in genCfg for EG
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_eg_cntrl.c 
*
*/
#ifdef ANSI
PUBLIC S16 smBuildEgGenCfg
(
Void
)
#else
PUBLIC S16 smBuildEgGenCfg()
#endif
{
   EgMngmt  egMgt;
   EgGenCfg    *cfg = NULLP;
   Pst       pst;

   TRC2(smBuildEgGenCfg)

   SM_SET_ZERO(&egMgt, sizeof(EgMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg   = &(egMgt.u.cfg.s.gen);

   /*----------- Fill General Configuration Parameters ---------*/

   cfg->nmbUSaps     = 5;
   cfg->maxNmbTSaps  = 5;
   cfg->nmbSrvs      = 15;
   cfg->timerRes     = 1; /* 1sec unit */
   cfg->resThreshUpper= 9;
   cfg->resThreshLower= 1;
   cfg->lmPst.dstProcId  = SM_SM_PROC;
   cfg->lmPst.srcProcId  = SM_EG_PROC;
   cfg->lmPst.dstEnt     = ENTSM;
   cfg->lmPst.srcEnt     = ENTEG;
   cfg->lmPst.dstInst    = 0;
   cfg->lmPst.srcInst    = 0;
   cfg->lmPst.prior      = 0;
   cfg->lmPst.route      = 0;
   cfg->lmPst.event      = 0;
   cfg->lmPst.region     = EG_MEM_REGION;
   cfg->lmPst.pool       = 0;
   cfg->lmPst.selector   = SM_SELECTOR_LC;

#ifdef EGTP_U
   cfg->eguT3Timer.enb           = TRUE;
   cfg->eguT3Timer.val           = 14;
   cfg->nmbRetries               = 3;
   cfg->echoTmr.enb              = TRUE;
   cfg->echoTmr.val              = 60;
   cfg->reOrderTmr.enb           = TRUE;
   cfg->reOrderTmr.val           = 20;
   cfg->pvtExtId                 = 10;
   cfg->pduWindSize              = 20;
   cfg->maxNumOfIp               =  1;
   cfg->nodeArch                 =  1;
#ifdef EGTP_U_MULTI_THREADED
   cfg->nmbWorkerThread          =   3;
   cfg->loadDistTmr.enb           = TRUE;
   cfg->loadDistTmr.val           =  1;
#endif /* EGTP_U_MULTI_THREADED */
#endif /* EGTP_U */

   /* Fill Header */
   egMgt.hdr.msgType             = TCFG;
   egMgt.hdr.msgLen              = 0;
   egMgt.hdr.entId.ent           = ENTEG;
   egMgt.hdr.entId.inst          = SM_INST_ZERO;
   egMgt.hdr.elmId.elmnt         = STEGGEN;
   egMgt.hdr.elmId.elmntInst1    = 0;
   egMgt.hdr.elmId.elmntInst2    = 0;
   egMgt.hdr.elmId.elmntInst3    = 0;
   egMgt.hdr.seqNmb              = 0;
   egMgt.hdr.version             = 0;
   egMgt.hdr.transId             = 0;

   egMgt.hdr.response.prior      = PRIOR0;
   egMgt.hdr.response.route      = RTESPEC;
   egMgt.hdr.response.mem.region = EG_MEM_REGION;
   egMgt.hdr.response.mem.pool   = EG_POOL;
   egMgt.hdr.response.selector   = SM_SELECTOR_LC;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTEG;
   pst.srcProcId = SM_SM_PROC;
   pst.dstProcId = SM_EG_PROC;
   pst.region = smCfgCb.init.region;

   /*RLOG0(L_EVENT, "EGTP Gen Cfg Req sent");*/

   /* Send the request to the LM */
   (Void) SmMiLegCfgReq(&pst, &egMgt);
 
   RETVALUE(ROK);
}/* smBuildEgGenCfg */


/*
*
*       Fun:   smBuildEgUSapCfg
*
*       Desc:  Call handler for SSAP Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_eg_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildEgUSapCfg
(
SpId        spId              /* Service Provider Sap ID */
)
#else
PUBLIC S16 smBuildEgUSapCfg(spId)
SpId        spId;             /* Service Provider Sap ID */
#endif
{
   EgMngmt  egMgt;
   EgUSapCfg    *cfg = NULLP;
   Pst      pst;

   TRC2(smBuildEgUSapCfg)
 
   SM_SET_ZERO(&egMgt, sizeof(EgMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg = &(egMgt.u.cfg.s.uSap);

   cfg->sapId      = 0;

#ifdef EGTP_C
   cfg->echo       = FALSE;
   cfg->intfType   = EGT_GTP_INT_S11;
#endif
   cfg->selector   =  SM_SELECTOR_LWLC; /* PRASANNA: */
   cfg->mem.region =  EG_MEM_REGION;
   cfg->mem.pool   =  EG_POOL;
   cfg->priority   =  PRIOR0;
   cfg->route      =  RTESPEC;
   cfg->dstProcId  =  SM_NB_PROC;
   cfg->dstEnt     = ENTNB;
   cfg->dstInst    = 0;
   cfg->flag       = LEG_EGTP_U;

   /* Fill Header */
   egMgt.hdr.msgType             = TCFG;
   egMgt.hdr.msgLen              = 0;
   egMgt.hdr.entId.ent           = ENTEG;
   egMgt.hdr.entId.inst          = SM_INST_ZERO;
   egMgt.hdr.elmId.elmnt         = STEGUSAP;
   egMgt.hdr.response.mem.region = EG_MEM_REGION;
   egMgt.hdr.response.mem.pool   = EG_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTEG;
   pst.srcProcId = SM_SM_PROC;
   pst.dstProcId = SM_EG_PROC;
   pst.region = smCfgCb.init.region;
   
   /*RLOG0(L_EVENT, "Egtp USap Cfg Req sent");*/

   /* Send the request to the LM */
   (Void) SmMiLegCfgReq(&pst, &egMgt);
 
   RETVALUE(ROK);
}/* smBuildEgUSapCfg */

/*
*
*       Fun:   smBuildEgLSapCfg
*
*       Desc:  Call handler for TSAP Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_eg_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildEgLSapCfg
(
SuId        suId,             /* E-GTP Sap ID */
SpId        spId              /* Service Provider Sap ID */
)
#else
PUBLIC S16 smBuildEgLSapCfg(suId, spId)
SuId        suId;             /* E-GTP Sap ID */
SpId        spId;             /* Service Provider Sap ID */
#endif
{
   EgMngmt  egMgt;
   EgTSapCfg  *cfg = NULLP;
   EgTSapReCfg *reCfg = NULLP;
   Pst       pst;

   TRC2(smBuildEgLSapCfg)
  
   SM_SET_ZERO(&egMgt, sizeof(EgMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg   = &(egMgt.u.cfg.s.tSap);
   reCfg = &(egMgt.u.cfg.r.tSapReCfg);

   cfg->tSapId  = suId;
   cfg->spId    = spId;
   cfg->tptType = LEG_TSAP_TYPE_TUCL;

   cfg->selector     = NBSM_EGHISEL;
   cfg->mem.region   = EG_MEM_REGION;
   cfg->mem.pool     = EG_POOL;
   cfg->priority     = PRIOR0;
   cfg->route        = RTESPEC;
   cfg->dstProcId    = SM_HI_PROC;
   cfg->dstEnt       = ENTHI;
   cfg->dstInst      = (Inst)0;

   cfg->tInitTmr.enb = TRUE;
   cfg->tInitTmr.val = 10;

   cfg->tptParam.type = CM_TPTPARAM_SOCK;
   cfg->tptParam.u.sockParam.listenQSize = 5;
   cfg->tptParam.u.sockParam.numOpts     = 0;

   reCfg->tPar.type = CM_TPTPARAM_SOCK;
   reCfg->tPar.u.sockParam.listenQSize = 5;
   reCfg->tPar.u.sockParam.numOpts     = 0;
   reCfg->maxBndRetry  = 3;
   reCfg->bndTmCfg.enb = TRUE;
   reCfg->bndTmCfg.val = 300;

   /* Fill Header */
   egMgt.hdr.msgType             = TCFG;
   egMgt.hdr.msgLen              = 0;
   egMgt.hdr.entId.ent           = ENTEG;
   egMgt.hdr.entId.inst          = SM_INST_ZERO;
   egMgt.hdr.elmId.elmnt         = STEGTSAP;
   egMgt.hdr.response.mem.region = EG_MEM_REGION;
   egMgt.hdr.response.mem.pool   = EG_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTEG;
   pst.srcProcId = SM_SM_PROC;
   pst.dstProcId = SM_EG_PROC;
   pst.region = smCfgCb.init.region;

   /*RLOG0(L_EVENT, "Egtp LSap Cfg Req sent");*/

   /* Send the request to the LM */
   (Void) SmMiLegCfgReq(&pst, &egMgt);
 
   RETVALUE(ROK);
}/* smBuildEgLSapCfg */


/*
*
*       Fun:   smBuildEgIpAddrCfg
*
*       Desc:  Call handler for IP Address Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wr_sm_eg_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildEgIpAddrCfg
(
SpId        spId              /* Service Provider Sap ID */
)
#else
PUBLIC S16 smBuildEgIpAddrCfg(spId)
SpId        spId;             /* Service Provider Sap ID */
#endif
{
   EgMngmt  egMgt;
   EgIpAddrCfg *cfg = NULLP;
   Pst       pst;

   TRC2(smBuildEgIpAddrCfg)

   SM_SET_ZERO(&egMgt, sizeof(EgMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   /* Fill Header */
   egMgt.hdr.msgType             = TCFG;
   egMgt.hdr.msgLen              = 0;
   egMgt.hdr.entId.ent           = ENTEG;
   egMgt.hdr.entId.inst          = SM_INST_ZERO;
   egMgt.hdr.elmId.elmnt         = STEGIPADDR;
   egMgt.hdr.response.mem.region = EG_MEM_REGION;
   egMgt.hdr.response.mem.pool   = EG_POOL;

   cfg = &(egMgt.u.cfg.s.ipAddr);

   cfg->nmbIpAddr = 1;

   NB_ALLOC(&(cfg->ipInfo), sizeof(EgIpInfo));
   /* wr004.102 : klock warning fixed */
   if((cfg->ipInfo) == NULLP)
   {
      /*RLOG0(L_ERROR, "Failure in the allocation of cfg");*/
      RETVALUE(RFAILED);
   } /* end of if statement */

   cfg->ipInfo[0].srcIpAddr.type                  = CM_TPTADDR_IPV4;
   cfg->ipInfo[0].srcIpAddr.u.ipv4TptAddr.port    = 0;
   cfg->ipInfo[0].srcIpAddr.u.ipv4TptAddr.address = smCfgCb.enbIpAddr;
   cfg->ipInfo[0].spId                            = spId;
   cfg->ipInfo[0].nodeType                        = TRUE;
   cfg->ipInfo[0].cfmStatus                       = FALSE;
   cfg->ipInfo[0].echoReqPvtExtVal.length         = 1;
   cfg->ipInfo[0].echoReqPvtExtVal.buff[0]        = 0x01;
   cfg->ipInfo[0].echoRspPvtExtVal.length         = 1;
   cfg->ipInfo[0].echoRspPvtExtVal.buff[0]        = 0x07;
   cfg->ipInfo[0].errIndPvtExtVal.length          = 1;
   cfg->ipInfo[0].errIndPvtExtVal.buff[0]         = 0x05;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTEG;
   pst.srcProcId = SM_SM_PROC;
   pst.dstProcId = SM_EG_PROC;
   pst.region = smCfgCb.init.region;

   /*RLOG0(L_EVENT, "Egtp IpAddr Cfg sent");*/

   /* Send the request to the LM */
   /* Send the request to the LM */
   (Void) SmMiLegCfgReq(&pst, &egMgt);

   RETVALUE(ROK);

}/* smBuildEgIpAddrCfg */

                                                                
/*
*
*       Fun:   smBuildTServerCfg
*
*       Desc:  Call handler for Transport server Cfg Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_leghdl.c 
*
*/
#ifdef ANSI
PUBLIC S16 smBuildTServerCfg
(
Void
)
#else
PUBLIC S16 smBuildTServerCfg()
#endif
{
   EgMngmt  egMgt;
   Pst      pst;
   EgTptSrvCfg  *cfg = NULLP;

   TRC2(smBuildTServerCfg)

   SM_SET_ZERO(&egMgt, sizeof(EgMngmt));   
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg = &(egMgt.u.cfg.s.tptSrv);

   cfg->tptSrvId                         = 0;
   cfg->tSapId                           = 0;
   cfg->uSapId                           = 0;
   cfg->tptAddr.type                     = CM_TPTADDR_IPV4;
   cfg->tptAddr.u.ipv4TptAddr.port       = NB_DFLT_EGTP_PORT; 
   /* Shwetha - giving the self address configured for this eNodeB for local endpoint */
   cfg->tptAddr.u.ipv4TptAddr.address = smCfgCb.enbIpAddr;  /* 0xAC1A001C */
   /* cmInetAddr ((S8 *)"127.0.0.1", &(cfg->tptAddr.u.ipv4TptAddr.address)); */
   /* cfg->tptAddr.u.ipv4TptAddr.address = CM_INET_NTOH_U32(cfg->tptAddr.u.ipv4TptAddr.address); */
   cfg->tptParam.u.sockParam.numOpts     = 0; /* 0 */
   cfg->tptParam.u.sockParam.listenQSize = 5; /* 5 */
   cfg->opnSrvRetryCnt                   = 3;
   cfg->opnSrvTmr.enb                    = TRUE;
   cfg->opnSrvTmr.val                    = 10;
#ifdef EGTP_C
   cfg->isDfltSrv                        = FALSE;
#endif
   cfg->hostName.pres                    = FALSE;
   /* kworks fix */
   cfg->hostName.len                     = (U16)((PTR) cmStrlen((CONSTANT U8 *) "host.domain.com"));
   cfg->gtp_C_Or_U                       = LEG_EGTP_U;

  /* Fill Header */
   egMgt.hdr.msgType             = TCFG;
   egMgt.hdr.msgLen              = 0;
   egMgt.hdr.entId.ent           = ENTEG;
   egMgt.hdr.entId.inst          = SM_INST_ZERO;
   egMgt.hdr.elmId.elmnt         = STEGSRVR;
   egMgt.hdr.response.mem.region = EG_MEM_REGION;
   egMgt.hdr.response.mem.pool   = EG_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTEG;
   pst.srcProcId = SM_SM_PROC;
   pst.dstProcId = SM_EG_PROC;
   pst.region = smCfgCb.init.region;

   /*RLOG0(L_EVENT, "Egtp TServ Cfg sent");*/

   /* Send the request to the LM */
   (Void) SmMiLegCfgReq(&pst, &egMgt);

   RETVALUE(ROK);
} /* end of smBuildTServerCfg */ 

/*
 *
 *       Fun:    smBindUnBindEgToHitSap
 *
 *       Desc:   Bind and Unbind EGTP with TUCL
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *       File:   wr_smm_egtp.c
 *
 */

#ifdef ANSI
PUBLIC Void smBindUnBindEgToHitSap
(
SpId        spId,
U8          action
)
#else
PUBLIC Void smBindUnBindEgToHitSap(spId,action)
SpId        spId;
U8          action;
#endif /* ANSI */
{
   EgMngmt              egMgt;
   Pst                  pst;

   TRC2(smBindUnBindEgToHitSap)

   SM_SET_ZERO(&egMgt, sizeof(EgMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   egMgt.hdr.msgType             = TCNTRL;
   egMgt.hdr.entId.ent           = ENTEG;
   egMgt.hdr.entId.inst          = SM_INST_ZERO;
   egMgt.hdr.elmId.elmnt         = STEGTSAP;
   egMgt.hdr.response.mem.region = EG_MEM_REGION;
   egMgt.hdr.response.mem.pool   = EG_POOL;

   egMgt.u.cntrl.action  = action;
   egMgt.u.cntrl.subAction  = SAELMNT;
   egMgt.u.cntrl.s.sap.sapId    = spId;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTEG;
   pst.dstProcId = SM_EG_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCfgCb.init.region;

   if (action == ABND_ENA)
   {
      /*RLOG0(L_EVENT, "Bnd Cntrl to eg for Hit sent");*/
   }
   else
   {
      /*RLOG0(L_EVENT, "UnBnd Cntrl to eg for Hit sent");*/
   }

   (Void)SmMiLegCntrlReq(&pst, &egMgt);

   RETVOID;
} /* end of smBindUnBindEgToHitSap */
 
 
/**
 * @brief This function is used to send enable/disable control request to 
 * the EGTP layers.
 *
 * @details
 *
 * Function: smBuildEgLogCntrl
 *
 * @param[in] actType
 * @param[in] mask
 *
 * @return Void
 */

#ifdef ANSI
PUBLIC Void smBuildEgLogCntrl
(
 Bool actType,
 U32  mask
)
#else
PUBLIC Void smBuildEgLogCntrl(actType, mask)
 Bool actType;
 U32  mask;
#endif /* ANSI */
{
   EgMngmt              egMgt;
   Pst                  pst;

   TRC2(smBuildEgLogCntrl)

   SM_SET_ZERO(&egMgt, sizeof(EgMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   egMgt.hdr.msgType             = TCNTRL;
   egMgt.hdr.entId.ent           = ENTEG;
   egMgt.hdr.entId.inst          = SM_INST_ZERO;
   egMgt.hdr.elmId.elmnt         = STEGGEN;
   egMgt.hdr.response.mem.region = EG_MEM_REGION;
   egMgt.hdr.response.mem.pool   = EG_POOL;

   if(actType == 0) /*NB_ON)*/
   {
      egMgt.u.cntrl.action          =  AENA;
   }
   else
   {
      egMgt.u.cntrl.action          =  ADISIMM;
   }
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTEG;
   pst.dstProcId = SM_EG_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCfgCb.init.region;

   (Void)SmMiLegCntrlReq(&pst, &egMgt);

   RETVOID;
} /* end of smBuildEgLogCntrl*/
 
/*
 *
 *       Fun:    smBuildEgDbgCntrl
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *       File:   wr_sm_eg_cntrl.c
 *
 */

#ifdef ANSI
PUBLIC Void smBuildEgDbgCntrl
(
Void
)
#else
PUBLIC Void smBuildEgDbgCntrl()
#endif /* ANSI */
{
   EgMngmt              egMgt;
   Pst                  pst;

   TRC2(smBuildEgDbgCntrl)

   SM_SET_ZERO(&egMgt, sizeof(EgMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   egMgt.hdr.msgType             = TCNTRL;
   egMgt.hdr.entId.ent           = ENTEG;
   egMgt.hdr.entId.inst          = SM_INST_ZERO;
   egMgt.hdr.elmId.elmnt         = STEGGEN;
   egMgt.hdr.response.mem.region = EG_MEM_REGION;
   egMgt.hdr.response.mem.pool   = EG_POOL;
   egMgt.u.cntrl.action          = AENA;
   egMgt.u.cntrl.subAction       = SADBG;
#ifdef DEBUGP
   egMgt.u.cntrl.s.dbgCntrl.genDbgMask = 0xffffffff;
#endif

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTEG;
   pst.dstProcId = SM_EG_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCfgCb.init.region;

   /*RLOG0(L_EVENT, "EGTP Dbg Cntrl to eg");*/

   (Void)SmMiLegCntrlReq(&pst, &egMgt);

   RETVOID;
} /* end of smBuildEgDbgCntrl*/


/*
*
*       Fun:    activate task
*
*       Desc:   Processes received event from EG
*
*       Ret:    ROK  - ok
*
*       Notes:  None
*
*       File:   wr_sm_eg_exms.c
*
*/

#ifdef ANSI
PUBLIC S16 smEgActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 smEgActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   S16 ret;

   /* wr002.102: Added trace macro */
   TRC2(smEgActvTsk)

   ret = ROK;

   switch(pst->event)
   {
#ifdef LCSMMILEG
      case EVTLEGCFGCFM:             /* Config confirm */
         ret = cmUnpkLegCfgCfm(SmMiLegCfgCfm, pst, mBuf);
         break;
      case EVTLEGCNTRLCFM:           /* Control confirm */
         ret = cmUnpkLegCntrlCfm(SmMiLegCntrlCfm, pst, mBuf);
         break;

      case EVTLEGSTACFM:             /* Status Confirm */
         ret = cmUnpkLegStaCfm(SmMiLegStaCfm, pst, mBuf);
         break;

      case EVTLEGSTSCFM:             /* Statistics Confirm */
         ret = cmUnpkLegStsCfm(SmMiLegStsCfm, pst, mBuf);
         break;

      case EVTLEGSTAIND:             /* Status Indication */
         ret = cmUnpkLegStaInd(SmMiLegStaInd, pst, mBuf);
         break;

      case EVTLEGTRCIND:             /* Trace Indication */
         ret = cmUnpkLegTrcInd(SmMiLegTrcInd, pst, mBuf);
         break;
#endif /* LCSMMILEG */
      default:
         NB_FREEMBUF(mBuf);
         ret = RFAILED;
         /*RLOG1(L_ERROR, "Invalid event [%d] received", pst->event);*/
         break;
   }

   RETVALUE(ret);

} /* end of smEgActvTsk */

/*
*
*       Fun:   smBuildEgShutDownCntrl
*
*       Desc:  Invoked to shut down the EGTP
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_smm_egtp.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildEgShutDownCntrl
(
)
#else
PUBLIC S16 smBuildEgShutDownCntrl(Void)
#endif
{
   EgMngmt cntrl;
   Pst      pst;

   TRC2(smBuildEgShutDownCntrl)

   SM_SET_ZERO(&cntrl, sizeof(EgMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cntrl.u.cntrl.action        =  ASHUTDOWN;
   cntrl.u.cntrl.subAction     =  NULLD;

   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTEG;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.elmId.elmnt         = STEGGEN;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTEG;
   pst.dstProcId = SM_EG_PROC;
   pst.srcProcId = SM_SM_PROC;

   /*RLOG0(L_EVENT, "EGTP ShutDown Cntrl Req to cz sent");*/
   /* Send the request to the EGTP */
   SmMiLegCntrlReq(&pst, &cntrl);
   RETVALUE(ROK);
} /* end of smBuildCzShutDownCntrl */    

/* IPSec Recovery */
/*local defines */
#define SM_MAX_EG_SEL 4

/*local typedefs */

/*forward references */

PUBLIC S16 PtMiLegCfgReq      (Pst *post, EgMngmt *cfg);
PUBLIC S16 PtMiLegStsReq      (Pst *post, Action action, EgMngmt *sts);
PUBLIC S16 PtMiLegStaReq      (Pst *post, EgMngmt *ssta);
PUBLIC S16 PtMiLegCntrlReq    (Pst *post, EgMngmt *cntrl);

/* public variable declarations */

/* public variable definitions */

/* private variable definitions */

/* public routines */

/* Following matrices define the mapping between the primitives called by the
 * layer manager (as SmMiLegXXXReq) and the corresponding primitives of the 
 * S1AP layer (layer management service provider) (as EgMiLegXXXReq).
 * Each primitive is mapped to one of SM_MAX_EG_SEL functions in the array.
 * The mapping is based on post->selector.
 * Selector          #define     Coupling      Primitive
 * 0 (SEL_LC_NEW)   LCSMMILEG    loose         cmPkMiLegXXXReq
 * 1                 MG          tight         EgMiLegXXXReq
 * 2+                            tight         PtMiLegXXXReq
 */

PRIVATE LegCfgReq smMiLegCfgReqMt[] =
{
#ifdef LCSMMILEG
   cmPkLegCfgReq,
#else
   PtMiLegCfgReq,
#endif

#ifdef EG
   EgMiLegCfgReq,
#else
   PtMiLegCfgReq,
#endif

};


PRIVATE LegStsReq smMiLegStsReqMt[] =
{
#ifdef LCSMMILEG
   cmPkLegStsReq,
#else
   PtMiLegStsReq,
#endif

#ifdef EG
   EgMiLegStsReq,
#else
   PtMiLegStsReq,
#endif

};


PRIVATE LegStaReq smMiLegStaReqMt[] =
{
#ifdef LCSMMILEG
   cmPkLegStaReq,
#else
   PtMiLegStaReq,
#endif

#ifdef EG
   EgMiLegStaReq,
#else
   PtMiLegStaReq,
#endif

};


PRIVATE LegCntrlReq smMiLegCntrlReqMt[] =
{
#ifdef LCSMMILEG
   cmPkLegCntrlReq,
#else
   PtMiLegCntrlReq,
#endif

#ifdef EG
   EgMiLegCntrlReq,
#else
   PtMiLegCntrlReq,
#endif

};


/*
 *
 *       Fun:    SmMiLegCfgReq - Configuration request
 *
 *       Desc:  
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   wr_sm_eg_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLegCfgReq
(
Pst     *post,       /* post structure */
EgMngmt *cfg        /* management structure */
)
#else
PUBLIC S16 SmMiLegCfgReq(post, cfg)
Pst     *post;       /* post structure */
EgMngmt *cfg;       /* management structure */
#endif
{

   TRC3(SmMiLegCfgReq)

#if (ERRCLASS & ERRCLS_DEBUG)
   if (post == (Pst *) NULLP || post->selector >= SM_MAX_EG_SEL)
   {
      RETVALUE(RFAILED);
   }
#endif

   RETVALUE((*(smMiLegCfgReqMt[post->selector]))(post, cfg));
} /* end of SmMiLegCfgReq() */

/*
 *
 *       Fun:    SmMiLegStsReq - Statistics request
 *
 *       Desc:  
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   wr_sm_eg_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLegStsReq
(
Pst     *post,       /* post structure */
Action action,
EgMngmt *sts        /* management structure */
)
#else
PUBLIC S16 SmMiLegStsReq(post, action, sts)
Pst     *post;       /* post structure */
Action action;
EgMngmt *sts;       /* management structure */
#endif
{
   TRC3(SmMiLegStsReq)

#if (ERRCLASS & ERRCLS_DEBUG)
   if (post == (Pst *) NULLP || post->selector >= SM_MAX_EG_SEL)
   {
      RETVALUE(RFAILED);
   }
#endif

   RETVALUE((*(smMiLegStsReqMt[post->selector]))(post, action, sts));
} /* end of SmMiLegStsReq() */

/*
 *
 *       Fun:    SmMiLegStaReq - Status request
 *
 *       Desc:  
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   wr_sm_eg_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLegStaReq
(
Pst     *post,       /* post structure */
EgMngmt *ssta        /* management structure */
)
#else
PUBLIC S16 SmMiLegStaReq(post, ssta)
Pst     *post;       /* post structure */
EgMngmt *ssta;       /* management structure */
#endif
{
   TRC3(SmMiLegStaReq)

#if (ERRCLASS & ERRCLS_DEBUG)
   if (post == (Pst *) NULLP || post->selector >= SM_MAX_EG_SEL)
   {
      RETVALUE(RFAILED);
   }
#endif

   RETVALUE((*(smMiLegStaReqMt[post->selector]))(post, ssta));
} /* end of SmMiLegStaReq() */

/*
 *
 *       Fun:    SmMiLegCntrlReq - Control request
 *
 *       Desc:  
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   eg_sm_eg_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLegCntrlReq
(
Pst     *post,       /* post structure */
EgMngmt *cntrl        /* management structure */
)
#else
PUBLIC S16 SmMiLegCntrlReq(post, cntrl)
Pst     *post;       /* post structure */
EgMngmt *cntrl;       /* management structure */
#endif
{
   TRC3(SmMiLegCntrlReq)

#if (ERRCLASS & ERRCLS_DEBUG)
   if (post == (Pst *) NULLP || post->selector >= SM_MAX_EG_SEL)
   {
      RETVALUE(RFAILED);
   }
#endif

   RETVALUE((*(smMiLegCntrlReqMt[post->selector]))(post, cntrl));
} /* end of SmMiLegCntrlReq() */

/*
 *
 *       Fun:    PtMiLegCfgReq - portable configuration request
 *
 *       Desc:  
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   eg_sm_eg_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 PtMiLegCfgReq
(
Pst     *post,       /* post structure */
EgMngmt *cfg        /* management structure */
)
#else
PUBLIC S16 PtMiLegCfgReq(post, cfg)
Pst     *post;       /* post structure */
EgMngmt *cfg;       /* management structure */
#endif
{
   TRC3(PtMiLegCfgReq)

   UNUSED(post);
   UNUSED(cfg);
   RETVALUE(RFAILED);
} /* end of PtMiLegCfgReq() */

/*
 *
 *       Fun:    PtMiLegStsReq - portable statistics request
 *
 *       Desc:  
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   eg_sm_eg_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 PtMiLegStsReq
(
Pst     *post,       /* post structure */
Action action,
EgMngmt *sts        /* management structure */
)
#else
PUBLIC S16 PtMiLegStsReq(post, action, sts)
Pst     *post;       /* post structure */
Action action;
EgMngmt *sts;       /* management structure */
#endif
{
   TRC3(PtMiLegStsReq)

   UNUSED(post);
   UNUSED(action);
   UNUSED(sts);
   RETVALUE(RFAILED);
} /* end of PtMiLegStsReq() */

/*
 *
 *       Fun:    PtMiLegStaReq - portable status request
 *
 *       Desc:  
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   wr_sm_eg_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 PtMiLegStaReq
(
Pst     *post,       /* post structure */
EgMngmt *ssta        /* management structure */
)
#else
PUBLIC S16 PtMiLegStaReq(post, ssta)
Pst     *post;       /* post structure */
EgMngmt *ssta;       /* management structure */
#endif
{
   TRC3(PtMiLegStaReq)

   UNUSED(post);
   UNUSED(ssta);
   RETVALUE(RFAILED);
} /* end of PtMiLegStaReq() */


/*
 *
 *       Fun:    PtMiLegCntrlReq - portable control request
 *
 *       Desc:  
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   wr_sm_eg_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 PtMiLegCntrlReq
(
Pst     *post,       /* post structure */
EgMngmt *cntrl        /* management structure */
)
#else
PUBLIC S16 PtMiLegCntrlReq(post, cntrl)
Pst     *post;       /* post structure */
EgMngmt *cntrl;       /* management structure */
#endif
{
   TRC3(PtMiLegCntrlReq)

   UNUSED(post);
   UNUSED(cntrl);
   RETVALUE(RFAILED);
} /* end of PtMiLegCntrlReq() */

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
*       File:  wr_sm_eg_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLegCfgCfm
(
Pst     *pst,          /* post structure */
EgMngmt *cfm           /* configuration */
)
#else
PUBLIC S16 SmMiLegCfgCfm(pst, cfm)
Pst     *pst;          /* post structure */
EgMngmt *cfm;          /* configuration */
#endif
{
   Pst      egPst;

   TRC2(SmMiLegCfgCfm);

   SM_SET_ZERO(&egPst,  sizeof(Pst));

   if (cfm->cfm.status == LCM_PRIM_OK)
   {
       switch (cfm->hdr.elmId.elmnt)
       {
          case STEGGEN:
               nbEgCfg |= NB_EG_GEN_CFG;
               break;      
          case STEGUSAP:
               nbEgCfg |= NB_EG_EGT_SAP_CFG;
               break;
          case STEGTSAP:
               nbEgCfg |= NB_EG_TSAP_CFG;
               break;
          case STEGSRVR:
               nbEgCfg |= NB_EG_TSRV_CFG;
               break;
          case STEGIPADDR:
               nbEgCfg |= NB_EG_IPADDR_CFG;
               break;
          default:
               /*RLOG1(L_ERROR, "EGTP Cfg Cfm received for invalid element %d",
                cfm->hdr.elmId.elmnt); */
               break;
       } /* end of switch statement */


       if (nbEgCfg == NB_SM_EG_CONFIGURED)
       {
          smCfgCb.smState = NB_SM_STATE_EGTP_CFG_DONE;
          smNbProcSm(EVTNBAPPCFG); 

       }  
   } /* end of if statement cfm->cfm.status == LCM_PRIM_OK */
   else if(cfm->cfm.status == LCM_PRIM_OK_NDONE)
   {
      nbUiSendConfigFailIndToUser(NB_EGTP_CFG_FAILED);  
      smCfgCb.smState  = NB_SM_STATE_INIT;
   }
   else
   {
      NB_LOG_DEBUG(&nbCb,"eGTP Configuration confirm received with NOK.");
   }

   RETVALUE(ROK);
} /* end of SmMiLegCfgCfm */

/*
 *
 *       Fun:    SmMiLegCntrlCfm - control confirm
 *
 *       Desc:  
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
PUBLIC S16 SmMiLegCntrlCfm
(
 Pst         *pst,
 EgMngmt     *cntrl
 )
#else
PUBLIC S16 SmMiLegCntrlCfm(pst, cntrl)
   Pst         *pst;
   EgMngmt     *cntrl;
#endif /* ANSI */
{

   TRC2(SmMiLegCntrlCfm)

   if (cntrl->cfm.status == LCM_PRIM_OK && cntrl->hdr.elmId.elmnt == STEGTSAP)
   {
      smBindUnBindNbToEgtSap(ABND_ENA);
   } /* end of if statement cntrl->cfm.status == LCM_PRIM_OK */
   RETVALUE(ROK);
} /* end of SmMiLegCntrlCfm() */

/*
 *
 *       Fun:    SmMiLegStsCfm - Statistics confirm
 *
 *       Desc:   prints the statistics confirm status
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_sm_eg_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLegStsCfm
(
Pst         *pst,
EgMngmt     *sts
)
#else
PUBLIC S16 SmMiLegStsCfm(pst, sts)
Pst         *pst;
EgMngmt     *sts;
#endif /* ANSI */
{
   TRC2(SmMiLegStsCfm)

   RETVALUE(ROK);
} /* end of SmMiLegStsCfm() */

/*
 *
 *       Fun:    SmMiLegStaCfm - status confirm
 *
 *       Desc:   prints the status confirm status
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_sm_eg_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLegStaCfm
(
Pst         *pst,
EgMngmt     *sta
)
#else
PUBLIC S16 SmMiLegStaCfm(pst, sta)
Pst         *pst;
EgMngmt     *sta;
#endif /* ANSI */
{
   TRC2(SmMiLegStaCfm)

   RETVALUE(ROK);
} /* end of SmMiLegStaCfm() */

/*i
 *
 *       Fun:    SmMiLegStaInd - status indication
 *
 *       Desc:   prints the status indication
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_sm_eg_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLegStaInd
(
Pst         *pst,
EgMngmt     *ind
)
#else
PUBLIC S16 SmMiLegStaInd(pst, ind)
Pst         *pst;
EgMngmt     *ind;
#endif /* ANSI */
{
   TRC2(SmMiLegStaInd)

   /*Update S1-U interface State*/
   if(ind->u.usta.alarm.category ==LCM_CATEGORY_INTERFACE 
         && ind->u.usta.alarm.event == LCM_EVENT_UI_INV_EVT
         && ind->u.usta.alarm.cause == LEG_CAUSE_DST_IP_REACHABLE)

   {
      /*smCfgCb.s1UStatus = TRUE;
      wrSendLmAlarm(LCM_CATEGORY_PROTOCOL, LWR_EVENT_S1U_PATH_REACHABLE,
                                     LCM_CAUSE_UNKNOWN);*/
   }
   else if (ind->u.usta.alarm.category ==LCM_CATEGORY_INTERFACE 
      && ind->u.usta.alarm.event == LEG_CAUSE_DST_IP_NOT_REACHABLE)
   {
      /*smCfgCb.s1UStatus = FALSE;
      wrSendLmAlarm(LCM_CATEGORY_PROTOCOL, LWR_EVENT_S1U_PATH_UNREACHABLE,
                                     LCM_CAUSE_UNKNOWN);*/
   }

   RETVALUE(ROK);
} /* end of SmMiLegStaInd() */

/*
 *
 *       Fun:    SmMiLegTrcInd - Trace indication
 *
 *       Desc:   prints the trace indication
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_sm_eg_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLegTrcInd
(
Pst         *pst,
EgMngmt     *ind,
Buffer      *mBuf
)
#else
PUBLIC S16 SmMiLegTrcInd(pst, ind, mBuf)
Pst         *pst;
EgMngmt     *ind;
Buffer      *mBuf;
#endif /* ANSI */
{
   TRC2(SmMiLegTrcInd)

   RETVALUE(ROK);
} /* end of SmMiLegTrcInd() */

