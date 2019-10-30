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
               
    File:  nb_lmm.c

    Sid:   

    Prg:   

**********************************************************************/
#include "nb.h"
#include "rl_interface.h"
#include "rl_common.h"
#include "nb_smm_init.h"
#include "nb_log.h"
#include "nb_utils.h"
#include "nb_ifm_egtp.h"
#include "nb_ifm_dam.h"
#include "nb_enb_db.h"
#include "nb_enb_db.x"

EXTERN S16 nbGenerateCfm (Pst *pst, CmStatus  *cfmSts, U8 prim, LnbMngmt *cfm);
PUBLIC S16 NbMiLwrStaReq(Pst *pst,LnbMngmt *cntrl);
EXTERN NbEnbDB nbEnbDB;

/*
 *       Fun:     nbActvInit
 *
 *       Desc:    
 *
 *       Ret:     ROK   - ok
 *
 *       Notes :  The task initializes its global variables.
 */
PUBLIC S16 nbActvInit
(
Ent                          entity,
Inst                         inst,
Region                       region,
Reason                       reason
)
{
   U8 offset = 0;
   U8 nbOffset = 0;
   NbUeCb tmpUeCb;
   EnbCb tmpEnbCb;
/* Multi eNB support */
   cmMemset((U8 *)&nbCb, 0, sizeof(NbCb));

   nbCb.init.procId  = SFndProcId();
   nbCb.init.ent     = entity;
   nbCb.init.inst    = inst;
   nbCb.init.region  = region;
   nbCb.init.reason  = reason;
   nbCb.init.cfgDone = FALSE;
   nbCb.init.pool    = 1;
   nbCb.init.acnt    = FALSE;
   nbCb.init.trc     = FALSE; 
   nbCb.init.usta    = TRUE;
   nbCb.mem.region = DFLT_REGION;
   nbCb.mem.pool = DFLT_POOL;
#ifdef DEBUGP
   nbCb.init.dbgMask = LNB_LOGLVL_DEBUG;
/* Initialize sap between nb and Dam */
#endif
   nbCb.nbDamPst.srcProcId = SFndProcId();
   nbCb.nbDamPst.srcEnt = ENTNB;
   nbCb.nbDamPst.srcInst = 0;
   nbCb.nbDamPst.dstProcId = SFndProcId();
   nbCb.nbDamPst.dstEnt = ENTEU;
   nbCb.nbDamPst.dstInst = 0;
   nbCb.nbDamPst.prior = 0;
   nbCb.nbDamPst.route = 0;
   nbCb.nbDamPst.selector = 0;
   nbCb.nbDamPst.region = region;

   offset = (U8) ((PTR)&tmpUeCb.ueHashEnt - (PTR)&tmpUeCb); 
/* initialize the ueCbLst */
   if( ROK != (cmHashListInit(&(nbCb.ueCbLst), /* messages */
                        NB_MAX_HASH_SIZE,     /* HL bins for the msgs */
                        offset,               /* Offset of HL Entry */
                        FALSE,                /* Allow dup. keys ? */
                        CM_HASH_KEYTYPE_ANY,  /* HL key type */
                        nbCb.init.region,     /* Mem region for HL */
                        nbCb.init.pool)))      /* Mem pool for HL */
   {
      NB_LOG_ERROR(&nbCb,"Failed to initialized UeCb List");
      RETVALUE(RFAILED);

   }  
 
   nbOffset = (U8) ((PTR)&tmpEnbCb.nbHashEnt - (PTR)&tmpEnbCb); 
/* initialize the eNBCbLst */
   if( ROK != (cmHashListInit(&(nbCb.eNBCbLst), /* messages */
                        NB_MAX_HASH_SIZE,     /* HL bins for the msgs */
                        nbOffset,               /* Offset of HL Entry */
                        FALSE,                /* Allow dup. keys ? */
                        CM_HASH_KEYTYPE_ANY,  /* HL key type */
                        nbCb.init.region,     /* Mem region for HL */
                        nbCb.init.pool)))      /* Mem pool for HL */
   {
      NB_LOG_ERROR(&nbCb,"Failed to initialized eNBCb List");
      RETVALUE(RFAILED);

   }  
   RETVALUE(ROK);
} /* nbActvInit */

/*
 *       Fun:     wrGenerateCfm 
 *
 *       Desc:    To generate confirms
 *
 *       Ret:     ROK   - ok
 *
 *       Notes :  None.
 */
PUBLIC S16  nbGenerateCfm
(
Pst          *pst,
CmStatus     *cfmSts,
U8           prim,
LnbMngmt     *cfm
)
{
   Pst       cPst;
   Header    *hdr;

   /* Fill the pst structure for LM i/f */
   cPst.srcEnt    = nbCb.init.ent;
   cPst.srcInst   = nbCb.init.inst;

   cPst.srcProcId = SFndProcId();

   /*
    * If genconfig is done, fill the destn identity
    * from the pst configured, else use the incoming
    * pst structure for destination identity.
    */
   if (NULLP == pst) 
   {  
      cPst.dstEnt    = nbCb.init.lmPst.dstEnt;
      cPst.dstInst   = nbCb.init.lmPst.dstInst;
      cPst.dstProcId = nbCb.init.lmPst.dstProcId;
   }
   else
   {  
      cPst.dstEnt    = pst->srcEnt;
      cPst.dstInst   = pst->srcInst;
      cPst.dstProcId = pst->srcProcId;
   }

   /* we are sending cfg as cfm back by filling properly values */
   hdr = &(cfm->hdr);
   cPst.selector  = hdr->response.selector;
   cPst.prior     = hdr->response.prior;
   cPst.route     = hdr->response.route;
   cPst.region    = hdr->response.mem.region;
   cPst.pool      = hdr->response.mem.pool;

   /* Fill the Header in cfm structure */
/* cmMemset ((U8 *)&cfm->hdr, '\0', sizeof(Header));*/
/* cfm->hdr.elmId.elmnt = hdr->elmId.elmnt;*/
/* Fill the transcation for which the cfm is being sent */
/* cfm->hdr.transId = hdr->transId;*/

   cfm->hdr.entId.ent   = nbCb.init.ent;
   cfm->hdr.entId.inst  = nbCb.init.inst;

   cfm->cfm.status = cfmSts->status; 
   cfm->cfm.reason = cfmSts->reason;
   switch (prim)
   {  
      case TCFG:
       /*  cmMemset ((U8 *)&cfm->t.cfg, 0, sizeof(LwrCfg));*/
         cPst.event = EVTLNBCFGCFM;
         NbMiLnbCfgCfm (&cPst, cfm);
         break;   

      case TCNTRL:
         cPst.event = EVTLNBCNTRLCFM;
         NbMiLnbCntrlCfm (&cPst, cfm);
         break;
   }  

   RETVALUE(ROK);
} /* nbGenerateCfm */

/********************************************************************IB**
 Layer Management Incoming Primitives
*********************************************************************IB*/

/*
 *       Fun:     wrUbndLSap
 *
 *       Desc:    This function is invoked to unbind & disable a SAP 
 *                A disconnect is sent and the SAP state is changed
 *                to WR_SAP_CFG without sending a unbind request.
 *
 *       Ret:     ROK or LCM_REASON_INVALID_STATE
 *
 *       Notes :  This function provides run time support for the
 *                stack reinitialization procedure.
 */
PRIVATE S16 nbUbndLSap
(
NbLiSapCb                    *sapCb
)
{
   S16                       retVal;

   TRC2(nbUbndLSap);

   switch(sapCb->sapState)
   {
      case LNB_SAP_BINDING:
      {
         sapCb->sapState = LNB_SAP_UNBOUND;
         retVal = ROK;
         break;
      }
      case LNB_SAP_BOUND:
      {
         sapCb->sapState = LNB_SAP_UNBOUND;
         retVal = ROK;
         break;
      }
      default:
      {
         retVal = LCM_REASON_INVALID_STATE;
         break;
      }
   }

   RETVALUE(retVal);
} /* nbUbndLSap */

/*
 *       Fun:     nbBndLSap
 *
 *       Desc:    This function binds the lower sap.
 *
 *       Ret:     ROK   - ok
 *
 *       Notes :  This function is a state transition action handler
 *                for lower SAP ABND_ENA control request. 
 */
PRIVATE S16 nbBndLSap
(
NbLiSapCb                    *sapCb,
CmStatus                     *status,
Elmnt                        elmnt
)
{
   if (LNB_SAP_UNBOUND == sapCb->sapState)
   {
      status->status = LCM_PRIM_OK_NDONE;
      sapCb->sapState = LNB_SAP_BINDING;
      sapCb->bndRetryCnt = 0;

      switch(elmnt)
      {
         case STNBSZTSAP:
         {
            nbStartTmr ((PTR)sapCb, NB_TMR_SZT_SAP_BND, sapCb->bndTmr.val);
            NbIfmS1apBndReq(&sapCb->pst, sapCb->suId, sapCb->spId);
            break;
         }
#ifdef EU_DAT_APP
         case STNBEGTSAP:
         {
            nbStartTmr ((PTR)sapCb, NB_TMR_EGT_SAP_BND, sapCb->bndTmr.val);
            NbIfmEgtpBndReq(&sapCb->pst, sapCb->suId, sapCb->spId);
            break;
         }
#endif 
         default:
            break;
      }
   }
   else
   {
      status->status = LCM_PRIM_NOK;
      status->reason = LCM_REASON_INVALID_STATE;
   }


   RETVALUE (ROK);
} /* wrBndLSap */

/*
 *       Fun:     wrLSapCntrl
 *
 *       Desc:    This function processes control request for the
 *                Lower SAP.
 *
 *       Ret:     ROK - Ok/RFAILED - Failure 
 *
 *       Notes :  This function implements the State transition
 *                for Lower SAP control requests. The function
 *                is the entry point for all control request
 *                events defined.
 *
 */
PRIVATE S16 nbLSapCntrl
(
LnbCntrl                      *sapCntrl,
CmStatus                     *status,
Elmnt                        elmnt
)
{
   NbLiSapCb                 *lSapCb = NULLP;
   S16                       retVal;

   retVal = ROK;

   switch (elmnt) {
      case STNBSZTSAP:
      {
         lSapCb = nbCb.sztSap[0];
         break;
      }
      default:
      {
         status->status = LCM_PRIM_NOK;
         status->reason = LCM_REASON_INVALID_PAR_VAL;
         RETVALUE(RFAILED);
      }
   }

   /* Initialize the status members to success */
   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

   switch (sapCntrl->action)
   {
      case ABND_ENA:
      {
         /* Bind Lower Sap  */
         nbBndLSap(lSapCb, status, elmnt);
         retVal = ROK;
         break;
      }
      case AUBND_DIS:
      {
         /* Disconnect PVC and DONT send Unbind Request */
         retVal = nbUbndLSap(lSapCb);
         if (ROK != retVal)
         {
            NB_LOG_ERROR(&nbCb,"NbLSapCntrl: Invalid Receiver\
                     State in call to nuUbndLSap");
            status->status = LCM_PRIM_NOK;
            status->reason = retVal;
         }
         break;
      }
      default:
      {
         NB_LOG_ERROR(&nbCb,"NbLSapCntrl: Invalid Action Value");
         status->status = LCM_PRIM_NOK;
         status->reason = LCM_REASON_INVALID_ACTION;
         retVal = RFAILED;
         break;
      }
   }

   RETVALUE(retVal);
} /* nbLSapCntrl */

/*
 *       Fun:     nbGenCfg
 *
 *       Desc:    This function is invoked to do the general 
 *                configuration for RRC User Layer.
 *
 *       Ret:     ROK     - ok
 *                RFAILED - Failure
 *                ROUTRES - Memory Allocation Failure due to resource
 *                          crunch.
 *
 *       Notes :  The general configuration configures the lmPst
 *                to use in all calls to the Stack Manager. This
 *                function reserwrs the static memory requirements
 *                for the layer and configures the static data strs. 
 */
PRIVATE S16 nbGenCfg 
(
LnbGenCfg                     *gen,
CmStatus                     *status
)
{
   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;
   S16                       retVal;

   if (TRUE != nbCb.init.cfgDone)
   {
      cmMemcpy((U8 *)&(nbCb.init.lmPst), (U8 *)&(gen->lmPst),
            (PTR)sizeof(Pst));

      nbCb.init.lmPst.srcProcId = gen->lmPst.srcProcId;
      nbCb.init.lmPst.srcEnt    = gen->lmPst.srcEnt;
      nbCb.init.lmPst.srcInst   = gen->lmPst.srcInst;
      nbCb.init.lmPst.event     = EVTNONE;
      nbCb.init.cfgDone = TRUE;
   }
   nbCb.tac    = gen->trackAreaCode;
   nbCb.cellId = gen->cellId;
   nbCb.timeRes = gen->timeRes;
   nbCb.tmrCfg.s1SetupTmr = gen->s1SetUpTmrVal;

   nbCb.mmeInfo.mmeId    = gen->mmeId;
   nbCb.mmeInfo.peerId   = gen->mmeId;
   nbCb.mmeInfo.mmeAddr  = gen->mmeAddr;
   cmInitTimers(&nbCb.mmeInfo.timer, 1);
   nbCb.plmnId.mcc[0] = gen->plmnId.mcc[0];
   nbCb.plmnId.mcc[1] = gen->plmnId.mcc[1];
   nbCb.plmnId.mcc[2] = gen->plmnId.mcc[2];
   nbCb.plmnId.mnc[0] = gen->plmnId.mnc[0];
   nbCb.plmnId.mnc[1] = gen->plmnId.mnc[1];
   nbCb.plmnId.mnc[2] = gen->plmnId.mnc[2];
   nbCb.plmnId.numMncDigits  = gen->plmnId.numMncDigits;
#ifdef MULTI_ENB_SUPPORT
   nbCb.enbId = 0; /* Multi eNB support, changed from 2 -> 0*/
   nbCb.numOfEnbs = smCfgCb.numOfEnbs ; /* Multi eNB support, changed from 2 -> 0*/
#else
   nbCb.enbId = 2; /* Multi eNB support, changed from 2 -> 0*/
#endif
   nbCb.enbType = 1;
   NB_SET_ZERO(&nbCb.ueAppPst, sizeof(Pst));
   nbCb.ueAppPst.selector  = 0;
   nbCb.ueAppPst.srcEnt    = ENTNB;
   nbCb.ueAppPst.dstEnt    = ENTUE;
   nbCb.ueAppPst.srcProcId = 0;
   nbCb.ueAppPst.dstProcId = 0;
   nbCb.ueAppPst.region = 0; 
   nbCb.ueAppPst.pool = 0;
   nbCb.ueAppPst .srcInst = 0;
   if (nbRegInitTmr() != ROK)
   {
      NB_LOG_ERROR(&nbCb,"nbGenCfg: nbRegInitTmr Failed");
      RETVALUE (RFAILED);
   }              
   nbCpyCmTptAddr(&nbCb.datAppAddr,&gen->dataAppAddr);
   /*Initialize S1-U interface Reachibility as 1[Default : Reachable]*/
   nbCb.s1UStatus = TRUE;

   nbCb.init.cfgDone = TRUE;   
   /* Allocate memory */
   NB_ALLOC(&nbCb.sztSap, (sizeof(NbLiSapCb *) * NB_NUM_SZT_SAPS));
   if(nbCb.sztSap == NULLP)
   {       
      NB_LOG_ERROR(&nbCb,"Failure in the allocation sap");
      RETVALUE(RFAILED);
   } /* end of if statement */

   RETVALUE(ROK);
} /* nbGenCfg */

/*
 *       Fun:     wrLSapCfg
 * 
 *       Desc:    This function is used to configure the Lower SAP.
 * 
 *       Ret:     ROK - ok / RFAILED - Failure 
 *                / ROUTRES - Memory out of resources.
 *
 *       Notes :  None.
 */
PRIVATE S16 nbLSapCfg
(     
LnbMngmt                      *cfg,
CmStatus                     *status
)
{
   NbLiSapCb *sap = NULLP;
   LnbLSapCfg *lSap = &cfg->t.cfg.t.lSap;

   TRC2(nbLSapCfg);

   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

   if (NULLP == lSap)
   {
      NB_LOG_ERROR(&nbCb,"nbLSapCfg: Invalid Sap Cfg");
      status->status = LCM_PRIM_NOK;
      status->reason = LCM_REASON_INVALID_PAR_VAL;
      RETVALUE(RFAILED);
   }

   switch(cfg->hdr.elmId.elmnt)
   {
      case STNBSZTSAP:
      {
         NB_ALLOC(&nbCb.sztSap[0], sizeof(NbLiSapCb));
         if(NULLP == nbCb.sztSap[0])
         {
            NB_LOG_ERROR(&nbCb,"nbLSapCfg: Failed to allocate Memory");
            RETVALUE(RFAILED);
         }
         sap = nbCb.sztSap[0];
         break;
      }
      default:
      {
         NB_LOG_ERROR(&nbCb,"nbLSapCfg: Invalid Sap Element");
         RETVALUE(RFAILED);
         break;
      }
   }

   sap->suId = lSap->suId;
   sap->spId = lSap->spId;
   sap->pst.srcProcId = SFndProcId();
   sap->pst.srcEnt = lSap->srcEnt;
   sap->pst.srcInst = lSap->srcInst;
   sap->pst.dstProcId = lSap->dstProcId;
   sap->pst.dstEnt = lSap->dstEnt;
   sap->pst.dstInst = lSap->dstInst;
   sap->pst.prior = lSap->dstPrior;
   sap->pst.route = lSap->dstRoute;
   sap->pst.selector = lSap->dstSel;
   sap->mem.region = lSap->mem.region;
   sap->mem.pool = lSap->mem.pool;
   sap->maxBndRetry = lSap->maxBndRetry;
   sap->bndTmr.val = lSap->bndTmr.val;
   sap->bndTmr.enb = lSap->bndTmr.enb;
   sap->sapState = LNB_SAP_UNBOUND;
   cmInitTimers(&sap->timer , 1);

   RETVALUE(ROK);
} /* nbLSapCfg */


/*
 *       Fun:     NbMiLwrCfgReq
 *
 *       Desc:    This primitive is called by LM to configure the 
 *                Framing Protocol User 
 *
 *       Ret:     ROK/RFAILED
 *
 *       Notes :  All configuration requests are handled from this
 *                function. 
 */
PUBLIC S16 NbMiLnbCfgReq
(
Pst                          *pst,
LnbMngmt                      *cfg
)
{
   S16               retVal;
   CmStatus          cfmStatus;    
   Bool              cfmWait;

   TRC3(NbMiLwrCfgReq);

   if (NULLP == cfg)
   {
      NB_LOG_ERROR(&nbCb,"NbMiLnbCfgReq: NULL Management structure");
      RETVALUE(RFAILED);
   }
   NB_LOG_DEBUG(&nbCb,"NBMiLnbCfgReq(pst, elmnt(%d))", cfg->hdr.elmId.elmnt);
   /* Check if general configuration is already done */
   if ((!nbCb.init.cfgDone) && (STNBGEN != cfg->hdr.elmId.elmnt))
   {
      NB_LOG_ERROR(&nbCb,"NbMiLwrCfgReq: General configuration not done");

      /* Send Config Confirm to LM with NOK status */
      cfmStatus.status = LCM_PRIM_NOK;
      cfmStatus.reason = LCM_REASON_GENCFG_NOT_DONE;
      nbGenerateCfm(pst, &cfmStatus , TCFG, cfg);

      RETVALUE(RFAILED);
   }

   cfmWait = FALSE;
   retVal = ROK;
   switch (cfg->hdr.elmId.elmnt)
   {
      case STNBGEN:
      {
         retVal = nbGenCfg(&cfg->t.cfg.t.genCfg, &cfmStatus);
         if(retVal != RFAILED)
         {
            nbIfmDamCfgReq(cfg);
            cfmWait = TRUE;
         }
         break;
      }
      case STNBSZTSAP:
      {
         retVal = nbLSapCfg(cfg, &cfmStatus);
         break;
      }
#ifdef EU_DAT_APP
      case STNBEGTSAP:
      {
         retVal = nbIfmDamCfgReq(cfg);
         cfmWait = TRUE;
         break;
      }
#endif
      default:
      {
         /* Send Config Confirm to LM with NOK status */
         NB_LOG_ERROR(&nbCb,"NbMiLwrCfgReq: Invalid Element");
         cfmStatus.status = LCM_PRIM_NOK;
         cfmStatus.reason = LCM_REASON_INVALID_ELMNT;
         retVal = RFAILED;
         break;
      }
   }

   if (!cfmWait)
   {
      nbGenerateCfm(pst, &cfmStatus, TCFG, cfg);
   }

   RETVALUE(retVal);
} /* NbMiLnbCfgReq */

/*
 *       Fun:     NbMiLnbCntrlReq
 *
 *       Desc:    This primitive is called by LM to issue control 
 *                requests to the RRC User layer
 *
 *       Ret:     ROK   - OK / RFAILED - Failure
 *
 *       Notes :  None.
 */
PUBLIC S16 NbMiLnbCntrlReq
(
Pst                          *pst,
LnbMngmt                      *cntrl
)
{
   S16                        retVal = ROK;
   U16                        mmeIdx = 0;
   CmStatus                   cfmStatus;    
   Bool                       cfmWait;
#ifdef MULTI_ENB_SUPPORT
   U32 inst = 0;
#endif

   TRC3(NbMiLnbCntrlReq);

   /*   cmMemset((U8 *) &cntrlCfm, (U8) 0, (PTR) sizeof(LwrMngmt));*/

   /* validate input parameters */
   if (NULLP == cntrl)
   {
      NB_LOG_ERROR(&nbCb,"NbMiLwrCntrlReq: NULL Management structure");

      RETVALUE(RFAILED);
   }
   NB_LOG_DEBUG(&nbCb,"NbMiLwrCntrlReq(pst, elmnt(%d))", cntrl->hdr.elmId.elmnt);

   /* Is genconfig done  */
   if (TRUE != nbCb.init.cfgDone) 
   {
      NB_LOG_ERROR(&nbCb,"NbLnbCntrlReq: General configuration not done");
      cfmStatus.status = LCM_PRIM_NOK;
      cfmStatus.reason = LCM_REASON_GENCFG_NOT_DONE;
      nbGenerateCfm (pst, &cfmStatus, TCNTRL, cntrl);
      RETVALUE(RFAILED);
   }

   cfmStatus.status = LCM_PRIM_OK;
   cfmStatus.reason = LCM_REASON_NOT_APPL;

   cfmWait = FALSE;

   /* Identify the element for control */
   switch (cntrl->hdr.elmId.elmnt)
   { 
      case STNBGEN: 
         {
            switch (cntrl->t.cntrl.action)
            {
               case AENA:
                  {
                     if(cntrl->t.cntrl.subAction == SAUSTA)
                     {
                        /* Sub Action Unsolicited Status Alarm */
                        nbCb.init.usta = TRUE;
                     }
                     else if (cntrl->t.cntrl.subAction == SADBG)
                     {
                        /* Sub Action DEBUG */
                     }
                     break;
                  }
               case ADISIMM:        /* Action DISABLE */
                  {
                     if(cntrl->t.cntrl.subAction == SAUSTA)
                     {
                        nbCb.init.usta = FALSE;
                     }
                     else if (cntrl->t.cntrl.subAction == SADBG)
                     {
                        /* Sub Action DEBUG */
                     }
                     break;
                  }
            }

            break;
         } /* end of  case STWRGEN */
      case STNBSZTSAP:
         {
            retVal = nbLSapCntrl(&cntrl->t.cntrl, &cfmStatus,
                  cntrl->hdr.elmId.elmnt);
            break;
         }
#ifdef EU_DAT_APP
      case STNBEGTSAP:
         {
            retVal = nbIfmDamCntrlReq (cntrl); 
            cfmWait = TRUE;
            break;
         }
#endif
      case STNBS1CONSETUP:
         {
            /* Triggering S1 Setup Request  */
            while (mmeIdx <= cntrl->t.cntrl.numConn)
            {
/*Sending multiple S1 setup request*/
#ifdef MULTI_ENB_SUPPORT
               NB_LOG_DEBUG(&nbCb, "Number of ENB configured = %d\n", smCfgCb.numOfEnbs);
               if (nbCb.multiEnbCfgInfo.pres == TRUE)
               {
                  smCfgCb.numOfEnbs = nbCb.multiEnbCfgInfo.numOfEnbs;
               }
               else
               {
                  smCfgCb.numOfEnbs = 1;
               }
               for(inst=0; inst < smCfgCb.numOfEnbs; inst++)
               {
#endif
               if (nbBuildAndSendS1SetupReq((U16)(cntrl->t.cntrl.idLst[mmeIdx])) != ROK)
               {
                  RETVALUE(RFAILED);
               }
#ifdef MULTI_ENB_SUPPORT
               }
#endif
               mmeIdx++;
            }
            break;
         }
      default:
         {
            NB_LOG_DEBUG(&nbCb,"NbMiLnbCntrlReq: Invalid Element");
            retVal = RFAILED;
            break;
         }
   }

   if(retVal == RFAILED)
   {
      NB_LOG_DEBUG(&nbCb,"NbMiLwrCntrlReq: Action Failed");
      cfmStatus.status = LCM_PRIM_NOK;
      cfmStatus.reason = LCM_REASON_INVALID_ELMNT;
   }
/* cntrlCfm.t.cntrl.action = cntrl->t.cntrl.action;
   cntrlCfm.t.cntrl.subAction = cntrl->t.cntrl.subAction;*/

   if (!cfmWait)
   {
      nbGenerateCfm(pst, &cfmStatus, TCNTRL, cntrl);
   }

/*   WR_FREE(cntrl, sizeof(LwrMngmt));*/
   RETVALUE(retVal);
} /* NbMiLwrCntrlReq */




PUBLIC S16 NbMiLnbStaReq
(
Pst                          *pst,
LnbMngmt                     *cntrl
)
{
   LnbMngmt     cntrlCfm;

   TRC2(NbMiLnbStaReq)


      cmMemset((U8 *)&cntrlCfm, 0, sizeof(LnbMngmt));
   cntrlCfm.hdr.elmId.elmnt = cntrl->hdr.elmId.elmnt;
   /*  status indication fix */
   cntrlCfm.hdr.response.selector = cntrl->hdr.response.selector;

   /* Check if General Config Done */
   if (TRUE != nbCb.init.cfgDone) 
   {
      NB_LOG_DEBUG(&nbCb,"NbMiLwrCntrlReq: General configuration not done");
      cntrlCfm.cfm.status = LCM_PRIM_NOK;
      cntrlCfm.cfm.reason = LCM_REASON_GENCFG_NOT_DONE;

      /*TODO*/
      cntrlCfm.t.cntrl.action = 0;
      cntrlCfm.t.cntrl.subAction = 0;
      /*TODO*/

      nbGenerateCfm (pst, &cntrl->cfm, TCNTRL, &cntrlCfm);
      RETVALUE(RFAILED);
   }

   cntrlCfm.cfm.status = LCM_PRIM_OK;

   RETVALUE(ROK);
}




/*
* Fun:     nbSendLmAlarm
*
*  Desc:    Function trigger alarm
*
*    Ret:     ROK   - ok
*
*      Notes :  None
*/
PUBLIC Void nbSendLmAlarm
(
 U16                          category,           
 U16                          event,             
 U16                          cause            
 )
{
   LnbMngmt      *usta = NULLP;
   if (nbCb.init.usta == FALSE)
   {
      RETVOID;
   }

   NB_ALLOC(&usta, sizeof(LnbMngmt));
   if(usta == NULLP)
   { 
      RETVOID;
   }
   /* Initialize the management structure */
   /*   (Void)cmMemset((U8 *) &usta, '\0', (PTR)sizeof(LwrMngmt));*/

   usta->hdr.elmId.elmnt = STNBGEN;
   usta->hdr.entId.ent   = nbCb.init.ent;
   usta->hdr.entId.inst  = nbCb.init.inst;
   usta->t.usta.alarm.category = category;
   usta->t.usta.alarm.event    = event;
   usta->t.usta.alarm.cause    = cause;

   /* Send an unsolicited status indication */
   NbMiLnbStaInd(&nbCb.init.lmPst, usta);
   RETVOID;
} /* nbSendLmAlarm */
