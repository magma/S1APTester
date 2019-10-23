/**********************************************************************

    Name:  LTE S1SIM - ENODEB Application Module 

    Type:  C include file

    Desc:  C source code for ENODEB Application

    File:  nb_smm_tucl.c
               
    Sid:   

    Prg:   

**********************************************************************/

#include "nb.h"
#include "rl_interface.h"
#include "rl_common.h"
#include "lhi.h"
#include "fw_tst.h"
#include "nb_smm_init.h"
#include "nbt.h"
#include "nb_log.h"

#include "lhi.x"
#include "nbt.x"

PRIVATE U8 nbHiCfg = 0;
PRIVATE U8 nbHiTSapCnt = 0;
/*
*
*       Fun:   Initialize TUCL task.
*
*       Desc:  Invoked to create TUCL Tapa task.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  wr_sm_hi_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smHiInit
(
SSTskId    sysTskId
)
#else
PUBLIC S16 smHiInit(sysTskId)
SSTskId    sysTskId;
#endif
{

   TRC2(smHiInit)

   /* Register TUCL TAPA Task */
   if (SRegTTsk((Ent)ENTHI, (Inst)0, (Ttype)TTNORM, (Prior)PRIOR0,
                 hiActvInit, (ActvTsk)hiActvTsk) != ROK) 
   {
      RETVALUE(RFAILED);
   }

   /* Attach TUCL TAPA Task */
   if (SAttachTTsk((Ent)ENTHI, (Inst)0, sysTskId)!= ROK) 
   {
      RETVALUE(RFAILED);
   }
   NB_LOG_DEBUG(&nbCb,"TUCL Tapa Task successfully registered and attached to [%d]",
      sysTskId);

   RETVALUE(ROK);
} /* end of smHiInit */

/*
 *
 *       Fun:    nbSmHiCfg - configure HI
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *      File:    wr_sm_hi_cntrl.c
 *
 */

#ifdef ANSI
PUBLIC Void nbSmHiCfg
(  
Void
)
#else
PUBLIC Void nbSmHiCfg()
#endif /* ANSI */ 
{  
   TRC2(nbSmHiCfg)

    nbHiCfg = 0;
    nbHiTSapCnt = 0;

   smBuildHiGenCfg();
   smBuildHiTSapCfg(SB_HI_SPID);
   smBuildHiTSapCfg(EG_HI_SPID);
   RETVOID;
} /* end of nbSmHiCfg */

/*
 *
 *       Fun:    smBuildHiGenCfg - fill in default genCfg for HI
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *
 */

#ifdef ANSI
PUBLIC Void smBuildHiGenCfg
(
Void
)
#else
PUBLIC Void smBuildHiGenCfg()
#endif /* ANSI */
{

   HiMngmt     hiMgt;
   HiGenCfg    *cfg = NULLP;
   Pst         pst;

   TRC2(smBuildHiGenCfg)

   SM_SET_ZERO(&hiMgt, sizeof(HiMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg = &hiMgt.t.cfg.s.hiGen;

   cfg->numSaps = NBSM_HI_NUMBSAPS;
   cfg->numCons = NBSM_HI_NMBCONS;
   cfg->numFdsPerSet = NBSM_HI_FDS;
   cfg->numFdBins = NBSM_HI_FDBINS;

   cfg->selTimeout = NBSM_HI_SELTIMEOUT;
   cfg->numRawMsgsToRead = 80;

#if (defined(HI_LKSCTP) && defined(HIAC_LKSCTP))
   cfg->numAssocBins   =  5;
   cfg->maxInitReTx    =  5; 
   cfg->maxAssocReTx   =  8;
   cfg->maxPathReTx    =  4; 
#endif

   cfg->permTsk = NBSM_HI_PERM_TSK_FLAG;
   cfg->schdTmrVal = NBSM_HI_SCHDTMR_VAL;
   cfg->poolStrtThr = NBSM_HI_STRT_THRESH;
   cfg->poolDropThr = NBSM_HI_DRP_THRESH;
   cfg->poolStopThr = NBSM_HI_STP_THRESH;
   cfg->timeRes = NBSM_HI_TIME_RES;
   
   /* Madhur Adding pool configuration */
   cfg->initPool = 1;

#ifdef HI_TLS
   cfg->initOpenSSL = TRUE;
   cfg->numContexts = 2;
#ifdef HI_ACC_TLS_PRNG_FILE
   cfg->prng.option = LHI_OSSL_PRNG_FILE;
   cmMemcpy((U8 *)cfg.t.cfg.s.hiGen.prng.u.file, (U8 *)"/dev/urandom", 13);
#else
   cfg->prng.option =  LHI_OSSL_PRNG_SEED;
   for (i = 0;  i < LHI_OSSL_PRNG_SEED_LEN;  i++)
   {
      SRandom(&rnd);
      cfg->prng.u.seed[i] = (U8)rnd;
   }
#endif /* HI_ACC_TLS_PRNG_FILE */
#endif

   cfg->lmPst.srcProcId = SM_HI_PROC;
   cfg->lmPst.dstProcId = SM_SM_PROC;
   cfg->lmPst.srcEnt = (Ent)ENTHI;
   cfg->lmPst.dstEnt = (Ent)ENTSM;
   cfg->lmPst.srcInst = (Inst)0;
   cfg->lmPst.dstInst = (Inst)0;
   cfg->lmPst.prior = (Prior)NBSM_MSGPRIOR;
   cfg->lmPst.route = (Route)RTESPEC;
   cfg->lmPst.event = (Event)EVTNONE;
   cfg->lmPst.region = DFLT_REGION;
   cfg->lmPst.pool = HI_POOL;
   cfg->lmPst.selector = (Selector)NBSM_HISMSEL;

 /* Fill Header */
   hiMgt.hdr.msgType             = TCFG;
   hiMgt.hdr.msgLen              = 0;
   hiMgt.hdr.entId.ent           = ENTHI;
   hiMgt.hdr.entId.inst          = SM_INST_ZERO;
   hiMgt.hdr.elmId.elmnt         = STGEN;
   hiMgt.hdr.elmId.elmntInst1    = 0;
   hiMgt.hdr.elmId.elmntInst2    = 0;
   hiMgt.hdr.elmId.elmntInst3    = 0;
   hiMgt.hdr.seqNmb              = 0;
   hiMgt.hdr.version             = 0;
   hiMgt.hdr.transId             = 0;

   hiMgt.hdr.response.prior      = PRIOR0;
   hiMgt.hdr.response.route      = RTESPEC;
   hiMgt.hdr.response.mem.region = DFLT_REGION;
   hiMgt.hdr.response.mem.pool   = HI_POOL;
   hiMgt.hdr.response.selector   = SM_SELECTOR_LC;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.srcProcId = SM_SM_PROC;
   pst.dstEnt    = ENTHI;
   pst.dstProcId = SM_HI_PROC;

   NB_LOG_DEBUG(&nbCb,"TUCL Gen Cfg Req sent");
   (Void)SmMiLhiCfgReq(&pst, &hiMgt);
  
   RETVOID;
} /* end of smBuildHiGenCfg() */


/*
 *
 *       Fun:    smBuildHiTSapCfg - fill in default HI SAP
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *
 */

#ifdef ANSI
PUBLIC Void smBuildHiTSapCfg
(
SpId        spId
)
#else
PUBLIC Void smBuildHiTSapCfg(spId)
SpId        spId;
#endif /* ANSI */
{
   HiMngmt     hiMgt;
   HiSapCfg    *cfg;
   Pst         pst;

   TRC2(smBuildHiTSapCfg)

   SM_SET_ZERO(&hiMgt, sizeof(HiMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg = &hiMgt.t.cfg.s.hiSap;

   cfg->spId = spId;
   cfg->uiSel = 0;
   cfg->flcEnb = FALSE;
   cfg->txqCongStrtLim = NBSM_HI_CONG_STRT;
   cfg->txqCongDropLim  = NBSM_HI_CONG_DRP;
   cfg->txqCongStopLim = NBSM_HI_CONG_STP;
   cfg->numBins = NBSM_HI_NMB_HLBINS;
     
   cfg->uiMemId.region =  DFLT_REGION;
   cfg->uiMemId.pool   =  HI_POOL;
   /* Fix: Reducing the priority of data plane packets to 
    * reduce control plane packet delay */
   if (spId == EG_HI_SPID)
   {
      cfg->uiPrior        = PRIOR3;
   }
   else
   {
      cfg->uiPrior        = PRIOR0;
   }
   cfg->uiRoute        = RTESPEC;

    /* profile_1 : srvcType value = 3 (GTP header format) */
   cfg->hdrInf[0].hdrLen = 20;
   cfg->hdrInf[0].offLen = 2;
   cfg->hdrInf[0].lenLen = 2;
   cfg->hdrInf[0].flag   = 0;

   /* profile_2 : srvcType value = 4 (LDP header format) */
   cfg->hdrInf[1].hdrLen = 10;
   cfg->hdrInf[1].offLen = 2;
   cfg->hdrInf[1].lenLen = 2;
   cfg->hdrInf[1].flag   = 0;

#if (defined(HI_LKSCTP) && defined(HIAC_LKSCTP))
   cfg->type = HI_SCT_SAP;        
#endif

    /* Fill Header */
   hiMgt.hdr.msgType             = TCFG;
   hiMgt.hdr.msgLen              = 0;
   hiMgt.hdr.entId.ent           = ENTHI;
   hiMgt.hdr.entId.inst          = SM_INST_ZERO;
   hiMgt.hdr.elmId.elmnt         = STTSAP;
 
      /* Fill Pst */
   pst.selector  = SM_SELECTOR_LC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTHI;
   pst.srcProcId = SM_SM_PROC;
   pst.dstProcId = SM_HI_PROC;

   NB_LOG_DEBUG(&nbCb,"TUCL TSap Cfg Req sent");
   (Void)SmMiLhiCfgReq(&pst, &hiMgt);

   RETVOID;
} /* end of smBuildHiTSapCfg() */
 

/*
*
*       Fun:   Activate Task - initialize
*
*       Desc:  Invoked by system services to initialize a task.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  smhiexms.c
*
*/

#ifdef ANSI
PUBLIC S16 smHiActvInit
(
Ent ent,                      /* entity */
Inst inst,                    /* instance */
Region region,                /* region */
Reason reason                 /* reason */
)
#else
PUBLIC S16 smHiActvInit(ent, inst, region, reason)
Ent ent;                      /* entity */
Inst inst;                    /* instance */
Region region;                /* region */
Reason reason;                /* reason */
#endif
{
   TRC3(smHiActvInit)

   UNUSED(ent);
   UNUSED(inst);
   UNUSED(region);
   UNUSED(reason);
   RETVALUE(ROK);
}
/*
*
*       Fun:    activate task
*
*       Desc:   Processes received event from TUCL
*
*       Ret:    ROK  - ok
*
*       Notes:  None
*
*       File:     wr_sm_hi_exms.c
*
*/
  
#ifdef ANSI
PUBLIC S16 smHiActvTsk
(
Pst    *spst,               /* post structure */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 smHiActvTsk(spst, mBuf)
Pst    *spst;               /* post structure */
Buffer *mBuf;               /* message buffer */
#endif
{
   S16           ret = ROK; /* return value from the function */

   /* wr002.102: Added trace macro */
   TRC2(smHiActvTsk)

   switch(spst->event)
   {
#ifdef LCSMHIMILHI
      case EVTLHICFGCFM:             /* Configuration Confirm */
         if ((ret = cmUnpkLhiCfgCfm(SmMiLhiCfgCfm, spst, mBuf)) != ROK)
         {
            RETVALUE(ret);
         }
         break;
      
      case EVTLHISTSCFM:             /* Statistics Confirm */
         if ((ret = cmUnpkLhiStsCfm(SmMiLhiStsCfm, spst, mBuf)) != ROK)
         {
            RETVALUE(ret);
         }
         break;

      case EVTLHICNTRLCFM:           /* Conntrol Confirm */
         if ((ret = cmUnpkLhiCntrlCfm(SmMiLhiCntrlCfm, spst, mBuf)) != ROK)
         {
            RETVALUE(ret);
         }
         break;

      case EVTLHISTACFM:             /* Status Confirm */
         if ((ret = cmUnpkLhiStaCfm(SmMiLhiStaCfm, spst, mBuf)) != ROK)
         {
            RETVALUE(ret);
         }
         break;

     case EVTLHISTAIND:             /* Status Indication */
         if ((ret = cmUnpkLhiStaInd(SmMiLhiStaInd, spst, mBuf)) != ROK)
         {
            RETVALUE(ret);
         }
         break;

      case EVTLHITRCIND:             /* Trace Indication */
         if ((ret = cmUnpkLhiTrcInd(SmMiLhiTrcInd, spst, mBuf)) != ROK)
         {
            RETVALUE(ret);
         }
         break;
#endif
      default:
        (Void)SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_DEBUG)
        SLogError(spst->dstEnt, spst->dstInst, spst->dstProcId, __FILE__, \
                   __LINE__, (ErrCls) ERRCLS_DEBUG, (ErrVal)WR_EWR001, 
                   (ErrVal)spst->event, "smHiActvTsk () Failed"); 
#endif
         break;
   }

   SExitTsk();

   RETVALUE(ret);
}/* end of smHiActvTsk() */

#define  MAXHIMI  2
#ifndef  LCSMHIMILHI
#define  PTSMHIMILHI
#else
#ifndef   HI
#define  PTSMHIMILHI
#endif
#endif


#ifdef PTSMHIMILHI
PRIVATE S16 PtMiLhiCfgReq    (Pst *pst, HiMngmt *cfg);
PRIVATE S16 PtMiLhiStsReq    (Pst *pst, Action action, HiMngmt *sts);
PRIVATE S16 PtMiLhiCntrlReq  (Pst *pst, HiMngmt *cntrl);
PRIVATE S16 PtMiLhiStaReq    (Pst *pst, HiMngmt *sta);
#endif


/*
the following matrices define the mapping between the primitives
called by the layer management interface of TCP UDP Convergence Layer
and the corresponding primitives in TUCL
 
The parameter MAXHIMI defines the maximum number of layer manager
entities on top of TUCL . There is an array of functions per primitive
invoked by TCP UDP Conbvergence Layer. Every array is MAXHIMI long
(i.e. there are as many functions as the number of service users).

The dispatching is performed by the configurable variable: selector.
The selector is configured during general configuration.

The selectors are:

   0 - loosely coupled (#define LCSMHIMILHI) 2 - Lhi (#define HI)

*/


/* Configuration request primitive */
 
PRIVATE LhiCfgReq SmMiLhiCfgReqMt[MAXHIMI] =
{
#ifdef LCSMHIMILHI
   cmPkLhiCfgReq,          /* 0 - loosely coupled  */
#else
   PtMiLhiCfgReq,          /* 0 - tightly coupled, portable */
#endif
#ifdef HI
   HiMiLhiCfgReq,          /* 1 - tightly coupled, layer management */
#else
   PtMiLhiCfgReq,          /* 1 - tightly coupled, portable */
#endif
};


/* Control request primitive */
 
PRIVATE LhiCntrlReq SmMiLhiCntrlReqMt[MAXHIMI] =
{
#ifdef LCSMHIMILHI
   cmPkLhiCntrlReq,          /* 0 - loosely coupled  */
#else
   PtMiLhiCntrlReq,          /* 0 - tightly coupled, portable */
#endif
#ifdef HI
   HiMiLhiCntrlReq,          /* 1 - tightly coupled, layer management */
#else
   PtMiLhiCntrlReq,          /* 1 - tightly coupled, portable */
#endif
};


/* Statistics request primitive */
 
PRIVATE LhiStsReq SmMiLhiStsReqMt[MAXHIMI] =
{
#ifdef LCSMHIMILHI
   cmPkLhiStsReq,          /* 0 - loosely coupled  */
#else
   PtMiLhiStsReq,          /* 0 - tightly coupled, portable */
#endif
#ifdef HI
   HiMiLhiStsReq,          /* 1 - tightly coupled, layer management */
#else
   PtMiLhiStsReq,          /* 1 - tightly coupled, portable */
#endif
};


/* Status request primitive */
 
PRIVATE LhiStaReq SmMiLhiStaReqMt[MAXHIMI] =
{
#ifdef LCSMHIMILHI
   cmPkLhiStaReq,          /* 0 - loosely coupled  */
#else
   PtMiLhiStaReq,          /* 0 - tightly coupled, portable */
#endif
#ifdef HI
   HiMiLhiStaReq,          /* 1 - tightly coupled, layer management */
#else
   PtMiLhiStaReq,          /* 1 - tightly coupled, portable */
#endif
};


/*
*     layer management interface functions 
*/
 
/*
*
*       Fun:   Configuration request
*
*       Desc:  This function is used to configure  TUCL
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:     wr_sm_hi_ptmi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SmMiLhiCfgReq
(
Pst *spst,                /* post structure */
HiMngmt *cfg              /* configure */
)
#else
PUBLIC S16 SmMiLhiCfgReq(spst, cfg)
Pst *spst;                /* post structure */   
HiMngmt *cfg;             /* configure */
#endif
{
   TRC3(SmMiLhiCfgReq)
   /* jump to specific primitive depending on configured selector */
   (*SmMiLhiCfgReqMt[spst->selector])(spst, cfg); 
   RETVALUE(ROK);
} /* end of SmMiLhiCfgReq */



/*
*
*       Fun:   Statistics request
*
*       Desc:  This function is used to request statistics from 
*              TUCL
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  
*
*/
  
#ifdef ANSI
PUBLIC S16 SmMiLhiStsReq
(
Pst *spst,                /* post structure */
Action action,
HiMngmt *sts              /* statistics */
)
#else
PUBLIC S16 SmMiLhiStsReq(spst, action, sts)
Pst *spst;                /* post structure */   
Action action;
HiMngmt *sts;             /* statistics */
#endif
{
   TRC3(SmMiLhiStsReq)
   /* jump to specific primitive depending on configured selector */
   (*SmMiLhiStsReqMt[spst->selector])(spst, action, sts); 
   RETVALUE(ROK);
} /* end of SmMiLhiStsReq */


/*
*
*       Fun:   Control request
*
*       Desc:  This function is used to send control request to 
*              TUCL
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:     wr_sm_hi_ptmi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SmMiLhiCntrlReq
(
Pst *spst,                 /* post structure */
HiMngmt *cntrl            /* control */
)
#else
PUBLIC S16 SmMiLhiCntrlReq(spst, cntrl)
Pst *spst;                 /* post structure */   
HiMngmt *cntrl;           /* control */
#endif
{
   TRC3(SmMiLhiCntrlReq)
   /* jump to specific primitive depending on configured selector */
   (*SmMiLhiCntrlReqMt[spst->selector])(spst, cntrl); 
   RETVALUE(ROK);
} /* end of SmMiLhiCntrlReq */


/*
*
*       Fun:   Status request
*
*       Desc:  This function is used to send a status request to 
*              TUCL
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:   
*
*/
  
#ifdef ANSI
PUBLIC S16 SmMiLhiStaReq
(
Pst *spst,                /* post structure */
HiMngmt *sta              /* status */
)
#else
PUBLIC S16 SmMiLhiStaReq(spst, sta)
Pst *spst;                /* post structure */   
HiMngmt *sta;             /* status */
#endif
{
   TRC3(SmMiLhiStaReq)
   /* jump to specific primitive depending on configured selector */
   (*SmMiLhiStaReqMt[spst->selector])(spst, sta); 
   RETVALUE(ROK);
} /* end of SmMiLhiStaReq */

#ifdef PTSMHIMILHI

/*
 *             Portable Functions
 */

/*
*
*       Fun:   Portable configure Request- TUCL
*
*       Desc:  
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:     wr_sm_hi_ptmi.c
*
*/
  
#ifdef ANSI
PRIVATE S16 PtMiLhiCfgReq
(
Pst *spst,                  /* post structure */
HiMngmt *cfg                /* configure */
)
#else
PRIVATE S16 PtMiLhiCfgReq(spst, cfg)
Pst *spst;                  /* post structure */
HiMngmt *cfg;               /* configure */
#endif
{
  TRC3(PtMiLhiCfgReq) 

  UNUSED(spst);
  UNUSED(cfg);

  RETVALUE(ROK);
} /* end of PtMiLhiCfgReq */



/*
*
*       Fun:   Portable statistics Request TUCL
*
*       Desc:  
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:     
*
*/
#ifdef ANSI
PRIVATE S16 PtMiLhiStsReq
(
Pst *spst,                  /* post structure */
Action action,
HiMngmt *sts                /* statistics */
)
#else
PRIVATE S16 PtMiLhiStsReq(spst, action, sts)
Pst *spst;                  /* post structure */
Action action;
HiMngmt *sts;               /* statistics */
#endif
{
  TRC3(PtMiLhiStsReq) 

  UNUSED(spst);
  UNUSED(action);
  UNUSED(sts);

  RETVALUE(ROK);
} /* end of PtMiLhiStsReq */


/*
*
*       Fun:   Portable control Request TUCL
*
*       Desc:  
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:     wr_sm_hi_ptmi.c
*
*/
#ifdef ANSI
PRIVATE S16 PtMiLhiCntrlReq
(
Pst *spst,                  /* post structure */
HiMngmt *cntrl              /* control */
)
#else
PRIVATE S16 PtMiLhiCntrlReq(spst, cntrl)
Pst *spst;                  /* post structure */
HiMngmt *cntrl;             /* control */
#endif
{
  TRC3(PtMiLhiCntrlReq)

  UNUSED(spst);
  UNUSED(cntrl);

  RETVALUE(ROK);
} /* end of PtMiLhiCntrlReq */


/*
*
*       Fun:   Portable status Request TUCL
*
*       Desc:  
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:     
*
*/
  
#ifdef ANSI
PRIVATE S16 PtMiLhiStaReq
(
Pst *spst,                  /* post structure */
HiMngmt *sta                /* status */
)
#else
PRIVATE S16 PtMiLhiStaReq(spst, sta)
Pst *spst;                  /* post structure */
HiMngmt *sta;               /* status */
#endif
{
  TRC3(PtMiLhiStaReq);

  UNUSED(spst);
  UNUSED(sta);

  RETVALUE(ROK);
} /* end of PtMiLhiStaReq */

#endif /* PTSMHIMILHI */

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
*       File:  
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLhiCfgCfm
(
Pst     *pst,          /* post structure */
HiMngmt *cfm           /* configuration */
)
#else
PUBLIC S16 SmMiLhiCfgCfm(pst, cfm)
Pst     *pst;          /* post structure */
HiMngmt *cfm;          /* configuration */
#endif
{
   TRC2(SmMiLhiCfgCfm)
  
  /*-- Update Event --*/
   UNUSED(pst);

   if (cfm->cfm.status == LCM_PRIM_OK)
   {
      switch(cfm->hdr.elmId.elmnt)
      {
         case STGEN:
            nbHiCfg |= NB_HI_GEN_CFG;
            break;
         case STTSAP:
            nbHiCfg |= NB_HI_TSAP_CFG;
            nbHiTSapCnt++;
            break;
         default:
            NB_LOG_DEBUG(&nbCb,"TUCL Cfg Cfm received with invalid element [%d]",
               cfm->hdr.elmId.elmnt);
            break;
      } /* end of switch statement */
      NB_LOG_DEBUG(&nbCb,"TUCL Cfg Cfm received for the element [%d]",
         cfm->hdr.elmId.elmnt);

      /* Wait for two Tsap confirms one for SCTP provider Sap
         and the other egtp provider Sap */
      if (nbHiCfg == NB_SM_HI_CONFIGURED && nbHiTSapCnt == 2)
      {
         /* Initiate SCTP configuration after TUCL configuration. 
            So send EVTWRSCTPCFG */
         smCfgCb.smState = NB_SM_STATE_TUCL_CFG_DONE;
         smNbProcSm(EVTNBSCTPCFG);
      } /* end of if statement  wrHiCfg == WR_SM_HI_CONFIGURED */

   }
   /* end of if statement  cfm->cfm.status == LCM_PRIM_OK */
  else if(cfm->cfm.status == LCM_PRIM_OK_NDONE)
  {
     nbUiSendConfigFailIndToUser(NB_TUCL_CFG_FAILED);  
     smCfgCb.smState               = NB_SM_STATE_INIT;
  }
   RETVALUE(ROK);
} /* end of SmMiLhiCfgCfm */


/*
 *
 *       Fun:   Control Confirm
 *
 *       Desc:  This function is used by to present control confirm
 *              information to Layer Manager.
 *
 *       Ret:   None
 *
 *       Notes: None
 *
 *       File:  smhiptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLhiCntrlCfm
(
 Pst     *pst,          /* post structure */
 HiMngmt *cfm           /* configuration */
 )
#else
PUBLIC S16 SmMiLhiCntrlCfm(pst, cfm)
   Pst     *pst;          /* post structure */
   HiMngmt *cfm;          /* configuration */
#endif
{
   TRC2(SmMiLhiCntrlCfm);
   
   if(cfm->cfm.status != LCM_PRIM_OK)
   {
      NB_LOG_ERROR(&nbCb,"SmMiLhiCntrlCfm failed!");
   }

   RETVALUE(ROK);
} /* end of SmMiLhiCntrlCfm */

/*
*
*       Fun:   Statistics Confirm
*
*       Desc:  This function is used by to present statistics confirm
*              information to Layer Manager.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smhiptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLhiStsCfm
(
Pst     *pst,          /* post structure */
HiMngmt *cfm           /* configuration */
)
#else
PUBLIC S16 SmMiLhiStsCfm(pst, cfm)
Pst     *pst;          /* post structure */
HiMngmt *cfm;          /* configuration */
#endif
{
    TRC2(SmMiLhiStsCfm)

    RETVALUE(ROK);
} /* end of SmMiLhiStsCfm */

/*
*
*       Fun:   Status Confirm
*
*       Desc:  This function is used by to present status confirm
*              information to Layer Manager.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smhiptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLhiStaCfm
(
Pst     *pst,          /* post structure */
HiMngmt *cfm           /* configuration */
)
#else
PUBLIC S16 SmMiLhiStaCfm(pst, cfm)
Pst     *pst;          /* post structure */
HiMngmt *cfm;          /* configuration */
#endif
{
    TRC2(SmMiLhiStaCfm)

    RETVALUE(ROK);
} /* end of SmMiLhiStaCfm */

/*
*
*       Fun:   Status Indication
*
*       Desc:  This function is used by to present status indication
*              information to Layer Manager.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smhiptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLhiStaInd
(
Pst     *pst,          /* post structure */
HiMngmt *cfm           /* configuration */
)
#else
PUBLIC S16 SmMiLhiStaInd(pst, cfm)
Pst     *pst;          /* post structure */
HiMngmt *cfm;          /* configuration */
#endif
{
    TRC2(SmMiLhiStaInd)

    RETVALUE(ROK);
} /* end of SmMiLhiStaInd*/

/*
*
*       Fun:   Trace Indication
*
*       Desc:  This function is used by to present trace indication
*              information to Layer Manager.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smhiptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLhiTrcInd
(
Pst     *pst,          /* post structure */
HiMngmt *cfm,           /* configuration */
Buffer  *mBuf
)
#else
PUBLIC S16 SmMiLhiTrcInd(pst, cfm, mBuf)
Pst     *pst;          /* post structure */
HiMngmt *cfm;          /* configuration */
Buffer  *mBuf;
#endif
{
    TRC2(SmMiLhiStaInd)

    RETVALUE(ROK);
} /* end of SmMiLhiTrcInd*/

