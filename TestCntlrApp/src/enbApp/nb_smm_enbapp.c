/**********************************************************************

    Name:  LTE S1SIM - ENODEB Application Module 

    Type:  C include file
               
    Desc:  C source code for ENODEB Application

     File:     nb_smm_enbapp.c

     Sid:      

     Prg:      

**********************************************************************/

#include "nb.h"
#include "rl_interface.h"
#include "rl_common.h"
#include "fw_tst.h"
#include "nb_smm_init.h"
#include "nb_lnb.h"
#include "nbt.h"
#include "nb_log.h"
#include "nbt.x"


#ifdef LWLCSMMILNB
#define  MAXNBMI  3
#if (!defined(LCSMMILNB) || !defined(NB) ||!defined(LWLCSMMILNB))
#define PTSMMILNB
#endif
#else
#define  MAXNBMI  2
#if (!defined(LCSMMILNB) || !defined(NB))
#define PTSMMILNB
#endif
#endif

#if (!defined(LCSMMILNB)) && (!defined(NB)) && (!defined(LWLCSMMILNB))  
PRIVATE S16 PtMiLnbCfgReq    (Pst *pst, LnbMngmt *cfg);
#endif
#if (!defined(LCSMMILNB)) && (!defined(NB)) && (!defined(LWLCSMMILNB))  
PRIVATE S16 PtMiLnbCntrlReq  (Pst *pst, LnbMngmt *cntrl);
#endif
EXTERN S16 nbDamActvInit
(
Ent                          entity,
Inst                         inst,
Region                       region,
Reason                       reason
);
EXTERN S16 nbDamActvTsk
(
Pst      *pst,
Buffer   *mBuf
);
PUBLIC S16 smBuildNbEgtLSapCfg
(
SuId        suId,             /* RRC App Sap ID */
SpId        spId              /* Service Provider Sap ID */
);
PRIVATE U32 nbNbCfg = 0;
/* extern declarations */
EXTERN S16 SReInitTmr(void);
PUBLIC S16 smBuildNbGenCfg
(
Void
);
/*
*
*       Fun:   Initialize RRC App task.
*
*       Desc:  Invoked to create RRC App TAPA task.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 smNbInit
(
SSTskId    sysTskId
)
#else
PUBLIC S16 smNbInit(sysTskId)
SSTskId    sysTskId;
#endif
{

   TRC2(smNbInit)

   /* Register ENB TAPA Task */
   if (SRegTTsk((Ent)ENTNB, (Inst)0, (Ttype)TTNORM, (Prior)PRIOR2,
                 nbActvInit, (ActvTsk)nbActvTsk) != ROK) 
   {
      RETVALUE(RFAILED);
   }

   NB_LOG_DEBUG(&nbCb,"App Tapa Task successfully registered and attached to %d\n",
      sysTskId);
   /* Attach RRM TAPA Task */
   if (SAttachTTsk((Ent)ENTNB, (Inst)0, sysTskId)!= ROK) 
   {
      RETVALUE(RFAILED);
   } /* end of if statement */

   RETVALUE(ROK);
} /* end of smNbInit */

#ifdef EU_DAT_APP

/*
*
*       Fun:   Initialize Data App task.
*
*       Desc:  Invoked to create Data App TAPA task.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nb_smm_enbapp.c
*
*/
#ifdef ANSI
PUBLIC S16 smEuInit
(
SSTskId    sysTskId
)
#else
PUBLIC S16 smEuInit(sysTskId)
SSTskId    sysTskId;
#endif
{

   TRC2(smEuInit)
    /* Register Data APP TAPA Task */
   if (SRegTTsk((Ent)ENTEU, (Inst)0, (Ttype)TTNORM, (Prior)PRIOR1,
                 nbDamActvInit , (ActvTsk)nbDamActvTsk) != ROK) 
   {
      RETVALUE(RFAILED);
   }


   /* Attach RRC APP TAPA Task */
   if (SAttachTTsk((Ent)ENTEU, (Inst)0, sysTskId)!= ROK)
   {
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* end of smEuInit */

#endif /* EU_DAT_APP */

/*
 *
 *       Fun:    nbSmNbCfg - configure NB 
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *      File:    
 *
 */

#ifdef ANSI
PUBLIC Void nbSmNbCfg
(
Void
)
#else
PUBLIC Void nbSmNbCfg(Void)
#endif /* ANSI */
{
   
   TRC2(nbSmNbCfg)
   nbNbCfg = 0;  

   smBuildNbGenCfg();
   smBuildNbSztLSapCfg(NB_SZ_SUID, NB_SZ_SPID);
    smBuildNbEgtLSapCfg(NB_EG_SUID, NB_EG_SPID);
   RETVOID;
} /* end of nbSmNbCfg */


/*
*
*       Fun:   smBuildNbGenCfg
*
*       Desc:  fill in genCfg for NB
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:   
*
*/
#ifdef ANSI
PUBLIC S16 smBuildNbGenCfg
(
Void
)
#else
PUBLIC S16 smBuildNbGenCfg(Void)
#endif
{
   LnbMngmt  *nbMgt = NULLP;
   LnbGenCfg    *cfg = NULLP;
   Pst       pst;
   
   TRC2(smBuildNbGenCfg)
   
   NB_ALLOC(&nbMgt, sizeof(LnbMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
   if(nbMgt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   cfg   = &(nbMgt->t.cfg.t.genCfg);

   if(cfg == NULLP)
   {
      NB_FREE(nbMgt, sizeof(LnbMngmt));
      RETVALUE(RFAILED);
   }

   smBuildGenCfg(nbMgt);

   cfg->lmPst.srcProcId = SM_SM_PROC;
   cfg->lmPst.dstProcId = SM_NB_PROC;
   cfg->lmPst.srcEnt = (Ent)ENTNB;
   cfg->lmPst.dstEnt = (Ent)ENTSM;
   cfg->lmPst.srcInst = (Inst)0;
   cfg->lmPst.dstInst = (Inst)0;
   cfg->lmPst.prior = (Prior)NBSM_MSGPRIOR;
   cfg->lmPst.route = (Route)RTESPEC;
   cfg->lmPst.event = (Event)EVTNONE;

   cfg->lmPst.srcProcId = SM_SM_PROC;
   cfg->lmPst.dstProcId = SM_NB_PROC;
   cfg->lmPst.srcEnt = (Ent)ENTNB;
   cfg->lmPst.dstEnt = (Ent)ENTSM;
   cfg->lmPst.srcInst = (Inst)0;
   cfg->lmPst.dstInst = (Inst)0;
   cfg->lmPst.prior = (Prior)NBSM_MSGPRIOR;
   cfg->lmPst.route = (Route)RTESPEC;
   cfg->lmPst.event = (Event)EVTNONE;
   cfg->lmPst.region = NB_MEM_REGION;
   cfg->lmPst.pool   =  NB_POOL;
   cfg->lmPst.selector = SM_SELECTOR_LWLC;
   cfg->timeRes = 10;
   
   /* Fill Header */
   nbMgt->hdr.msgType             = TCFG;
   nbMgt->hdr.msgLen              = 0;
   nbMgt->hdr.entId.ent           = ENTNB;
   nbMgt->hdr.entId.inst          = SM_INST_ZERO;
   nbMgt->hdr.elmId.elmnt         = STNBGEN;
   nbMgt->hdr.elmId.elmntInst1    = 0;
   nbMgt->hdr.elmId.elmntInst2    = 0;
   nbMgt->hdr.elmId.elmntInst3    = 0;
   nbMgt->hdr.seqNmb              = 0;
   nbMgt->hdr.version             = 0;
   nbMgt->hdr.transId             = LNB_TRANSID_GEN;

   nbMgt->hdr.response.prior      = PRIOR0;
   nbMgt->hdr.response.route      = RTESPEC;
   nbMgt->hdr.response.selector   = SM_SELECTOR_LWLC;
   nbMgt->hdr.response.mem.region = NB_MEM_REGION;
   nbMgt->hdr.response.mem.pool   = NB_POOL;

    /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTNB;
   pst.dstProcId = SM_NB_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCfgCb.init.region;

   NB_LOG_DEBUG(&nbCb,"APP Gen Cfg sent");
   /* Send the request to the LM */
   (Void) SmMiLnbCfgReq(&pst, nbMgt);
 
   RETVALUE(ROK);
}/* smBuildNbGenCfg */

                                                       
/*
*
*       Fun:   smBuildNbSztLSapCfg
*
*       Desc:  Call handler for SZT LSAP Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  
*
*/
#ifdef ANSI
PUBLIC Void smBuildNbSztLSapCfg
(
SuId        suId,             /* RRC App Sap ID */
SpId        spId              /* Service Provider Sap ID */
)
#else
PUBLIC Void smBuildNbSztLSapCfg( suId, spId)
SuId        suId;             /* RRC App Sap ID */
SpId        spId;             /* Service Provider Sap ID */
#endif
{
   LnbMngmt    *nbMgt = NULLP;
   LnbLSapCfg  *cfg = NULLP;
   Pst        pst;

   TRC2(smBuildNbSztLSapCfg)

   NB_ALLOC(&nbMgt, sizeof(LnbMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg   = &(nbMgt->t.cfg.t.lSap);

   if(cfg == NULLP)
   {
      NB_FREE(nbMgt, sizeof(LnbMngmt));
      RETVOID;
   }
   cfg->suId   = suId;
   cfg->spId   = spId;

   cfg->dstProcId    = SM_SZ_PROC;
   cfg->dstEnt       = ENTSZ;
   cfg->dstInst      = (Inst)0;
   cfg->dstPrior     = PRIOR0;
   cfg->dstRoute     = RTESPEC;
   cfg->dstSel       = NBSM_NBSZSEL;
   cfg->srcEnt       = ENTNB;
   cfg->srcInst      = (Inst)0;
   cfg->mem.region   = NB_MEM_REGION;
   cfg->mem.pool     = NB_POOL;

   cfg->maxBndRetry = NBSM_LNB_MAX_BND_RETRY;
   cfg->bndTmr.enb = TRUE;
   cfg->bndTmr.val = NBSM_LNB_VAL_10;
   
   if(nbMgt == NULLP)
   {
      RETVOID;
   }
   /* Fill Header */
   nbMgt->hdr.msgType             = TCFG;
   nbMgt->hdr.msgLen              = 0;
   nbMgt->hdr.entId.ent           = ENTNB;
   nbMgt->hdr.entId.inst          = SM_INST_ZERO;
   nbMgt->hdr.elmId.elmnt         = STNBSZTSAP;
   nbMgt->hdr.transId             = LNB_TRANSID_SZT;
   nbMgt->hdr.response.selector   = SM_SELECTOR_LWLC;
   nbMgt->hdr.response.mem.region = NB_MEM_REGION;
   nbMgt->hdr.response.mem.pool   = NB_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTNB;
   pst.dstProcId = SM_NB_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCfgCb.init.region;

   NB_LOG_DEBUG(&nbCb,"Szt LSap Cfg sent");
   /* Send the request to the LM */
   (Void) SmMiLnbCfgReq(&pst, nbMgt);

   RETVOID;
}/* smBuildNbSztLSapCfg */

#ifdef EU_DAT_APP
#if 1
/*
*
*       Fun:   smBuildBrEgtLSapCfg
*
*       Desc:  Call handler for EGT LSAP Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nb_sm_wr_cntrl.c
*
*/
#ifdef ANSI
PUBLIC S16 smBuildNbEgtLSapCfg
(
SuId        suId,             /* RRC App Sap ID */
SpId        spId              /* Service Provider Sap ID */
)
#else
PUBLIC S16 smBuildNbEgtLSapCfg( suId, spId)
SuId        suId;             /* RRC App Sap ID */
SpId        spId;             /* Service Provider Sap ID */
#endif
{
   LnbMngmt    *nbMgt = NULLP;
   LnbLSapCfg  *cfg = NULLP;
   Pst        pst;
 
   TRC2(smBuildNbEgtLSapCfg)

   NB_ALLOC(&nbMgt, sizeof(LnbMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   cfg   = &(nbMgt->t.cfg.t.lSap);

   if(cfg == NULLP)
   {
      NB_FREE(nbMgt, sizeof(LnbMngmt));
      RETVALUE(RFAILED);
   }
   cfg->suId   = suId;
   cfg->spId   = spId;

   cfg->dstProcId    = SM_EG_PROC;
   cfg->dstEnt       = ENTEG;
   cfg->dstInst      = (Inst)0;
   cfg->dstPrior     = PRIOR0;
   cfg->dstRoute     = RTESPEC;
   cfg->dstSel       = NBSM_NBEGSEL;
   cfg->srcEnt       = ENTVE;
   cfg->srcInst      = (Inst)0;
   cfg->mem.region   = 0;
   cfg->mem.pool     = NB_POOL;

   cfg->maxBndRetry = NBSM_LNB_MAX_BND_RETRY;
   cfg->bndTmr.enb = TRUE;
   cfg->bndTmr.val = NBSM_LNB_VAL_10;

   if(nbMgt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /* Fill Header */
   nbMgt->hdr.msgType             = TCFG;
   nbMgt->hdr.msgLen              = 0;
   nbMgt->hdr.entId.ent           = ENTNB;
   nbMgt->hdr.entId.inst          = SM_INST_ZERO;
   nbMgt->hdr.elmId.elmnt         = STNBEGTSAP;
   nbMgt->hdr.transId             = LNB_TRANSID_EGT;
   nbMgt->hdr.response.selector   = SM_SELECTOR_LWLC;
   nbMgt->hdr.response.mem.region = NB_MEM_REGION;
   nbMgt->hdr.response.mem.pool   = NB_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTNB;
   pst.dstProcId = SM_NB_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCfgCb.init.region;

   NB_LOG_DEBUG(&nbCb,"RRM Egt LSap Cfg sent");
   /* Send the request to the LM */
   (Void) SmMiLnbCfgReq(&pst, nbMgt);
 
   RETVALUE(ROK);
}/* smBuildNbEgtLSapCfg */
#endif
#endif  /* EU_DAT_APP  */


/*
*      FUN:   smBindUnBindNbToSztSap
*
*      Desc:  Bind and Unbind NB with SCT LSAP. 
*
*      Ret:   Void
*
*       Notes: None
*              
*       File:  
*
*
*/
#ifdef ANSI
PUBLIC S16 smBindUnBindNbToSztSap
(
U8 action
)
#else
PUBLIC S16 smBindUnBindNbToSztSap(U8 action)
#endif /* ANSI */
{
   LnbMngmt  *cntrl = NULLP;
   Pst        pst;
   S16      ret = ROK;
 
   TRC2(smBindUnBindNbToSztSap)

   NB_ALLOC(&cntrl, sizeof(LnbMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));
 
   if(cntrl == NULLP)
   {
      RETVALUE(RFAILED);
   }
   cntrl->t.cntrl.action        = action;
   cntrl->t.cntrl.subAction    = 0;
   cntrl->t.cntrl.u.sapId       = NB_SZ_SUID; 

   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTNB;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STNBSZTSAP;
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;
   cntrl->hdr.response.mem.region = NB_MEM_REGION;
   cntrl->hdr.response.mem.pool   = NB_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTNB;
   pst.dstProcId = SM_NB_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCfgCb.init.region;

   if (action == ABND_ENA)
   {
      NB_LOG_DEBUG(&nbCb,"Bind Cntrl Req to nb for S1AP");
   }
   else
   {
      NB_LOG_ERROR(&nbCb,"UnBind Cntrl Req to nb for S1AP");
   }
      
    /* Send the control request to the APP */
   (Void)SmMiLnbCntrlReq(&pst, cntrl);

   RETVALUE(ret);
} /* smBindUnBindNbToSztSap */


/*
 *      FUN:   smBindUnBindNbToEgtSap
 *
 *      Desc:  Bind and Unbind NB with EGT LSAP. 
*
*      Ret:   Void
*
*       Notes: None
*              
*       File:  
*
 *
*/
#ifdef ANSI
PUBLIC S16 smBindUnBindNbToEgtSap
(
U8 action
)
#else
PUBLIC S16 smBindUnBindNbToEgtSap(U8 action)
#endif /* ANSI */
{
   LnbMngmt  *cntrl = NULLP;
   Pst        pst;
   S16      ret = ROK;
 
   TRC2(smBindUnBindNbToEgtSap)

   NB_ALLOC(&cntrl, sizeof(LnbMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(cntrl == NULLP)
   {
      RETVALUE(RFAILED);
   }
   cntrl->t.cntrl.action        = action;
   cntrl->t.cntrl.subAction    = 0;
   cntrl->t.cntrl.u.sapId       = NB_EG_SUID; 

   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTNB;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STNBEGTSAP;
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;
   cntrl->hdr.response.mem.region = NB_MEM_REGION;
   cntrl->hdr.response.mem.pool   = NB_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTNB;
   pst.dstProcId = SM_NB_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCfgCb.init.region;

   if (action == ABND_ENA)
   {
      NB_LOG_DEBUG(&nbCb,"Bnd Cntrl Req to nb for EGTP");
   }
   else
   {
      NB_LOG_ERROR(&nbCb,"UnBnd Cntrl Req to nb for EGTP");
   }

    /* Send the control request to the NB*/
   (Void)SmMiLnbCntrlReq(&pst, cntrl);
 
   RETVALUE(ret);
} /* smBindUnBindNbToEgtSap */

/*
 *
*       Fun:   smBuildNbGenCntrl
 *
*       Desc:  Invoked to Enable Alarms at APP
*
*       Ret:   ROK
 *
 *      Notes: None
 *
 *      File:  
 *
 */
#ifdef ANSI
PUBLIC S16 smBuildNbGenCntrl
(
)
#else
PUBLIC S16 smBuildNbGenCntrl(Void)
#endif
{
   LnbMngmt *cntrl = NULLP;
   Pst      pst;

   /* wr002.102: Corrected function name in trace macro */
   TRC2(smBuildNbGenCntrl)

   NB_ALLOC(&cntrl, sizeof(LnbMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(cntrl == NULLP)
   {
      RETVALUE(RFAILED);
   }
   cntrl->t.cntrl.action        =  AENA;
   cntrl->t.cntrl.u.sapId       =  0;
   cntrl->t.cntrl.subAction     =  SAUSTA;

   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTNB;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STNBGEN;
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;
   cntrl->hdr.response.mem.region = NB_MEM_REGION;
   cntrl->hdr.response.mem.pool   = NB_POOL;

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTNB;
   pst.dstProcId = SM_NB_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCfgCb.init.region;
   
   NB_LOG_DEBUG(&nbCb,"Gen Cntrl Req to nb sent");
   /* Send the request to the APP */
   SmMiLnbCntrlReq(&pst, cntrl);

   RETVALUE(ROK);
} /* end of smBuildNbGenCntrl */


/*
 *
*       Fun:   smBuildNbS1InitCntrl
 *
*       Desc:  Invoked to intimate the APP that Binding is DONE.
*              APP should initiate the S1AP association
*
*       Ret:   ROK
 *
 *      Notes: None
 *
 *      File:  
 *
 */
#ifdef ANSI
PUBLIC S16 smBuildNbS1InitCntrl
(
)
#else
PUBLIC S16 smBuildNbS1InitCntrl(Void)
#endif
{
   LnbMngmt *cntrl = NULLP;
   Pst pst;
   U8 noOfCfg = 0;
   
   TRC2(smBuildNbS1InitCntrl)

   NB_ALLOC(&cntrl, sizeof(LnbMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

   if(cntrl == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTNB;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STNBS1CONSETUP;
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;
   cntrl->hdr.response.mem.region = NB_MEM_REGION;
   cntrl->hdr.response.mem.pool   = NB_POOL;
   for ( noOfCfg=0; noOfCfg<smCfgCb.noOfCfg; noOfCfg++)
   {
     cntrl->t.cntrl.peerId[noOfCfg] = smCfgCb.mmeCfg[noOfCfg]->mmeId;;
     cntrl->t.cntrl.idLst[noOfCfg] = smCfgCb.mmeCfg[noOfCfg]->mmeId;;
   }
     cntrl->t.cntrl.numConn = noOfCfg;
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTNB;
   pst.dstProcId = SM_NB_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.region = smCfgCb.init.region;
   
   /* Send the request to the APP */
   SmMiLnbCntrlReq(&pst, cntrl);

   RETVALUE(ROK);
} /* end of smBuildNbInitCntrl */


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
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 smNbActvInit
(
Ent ent,                      /* entity */
Inst inst,                    /* instance */
Region region,                /* region */
Reason reason                 /* reason */
)
#else
PUBLIC S16 smNbActvInit(ent, inst, region, reason)
Ent ent;                      /* entity */
Inst inst;                    /* instance */
Region region;                /* region */
Reason reason;                /* reason */
#endif
{
   TRC3(smNbActvInit)

   UNUSED(ent);
   UNUSED(inst);
   UNUSED(reason);
   smCfgCb.init.region = region;
   smCfgCb.init.pool  = 0;
   RETVALUE(ROK);
}


/*
*
*       Fun:    activate task
*
*       Desc:   Processes received event from 
*
*       Ret:    ROK  - ok
*
*       Notes: None
*
*       File:   
*
*/
#ifdef ANSI
PUBLIC S16 smNbActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 smNbActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   S16 ret;

   TRC2(smNbActvTsk)

   ret = ROK;

   switch(pst->event)
   {
#if (defined (LCNBMILNB) || defined(LWLCNBMILNB))
      case EVTLNBCFGCFM:             /* Config confirm */
         ret = cmUnpkLnbCfgCfm(SmMiLnbCfgCfm, pst, mBuf);
         break;
      case EVTLNBCNTRLCFM:           /* Control confirm */
         ret = cmUnpkLnbCntrlCfm(SmMiLnbCntrlCfm, pst, mBuf);
         break;
      case EVTLNBSTAIND:
         ret = cmUnpkLnbStaInd(SmMiLnbStaInd, pst,mBuf);
         break;
#endif
      case EVTNBSCTPCFG:
      case EVTNBS1APCFG:
      case EVTNBAPPCFG:
      case EVTNBS1APSTKBND:
      case EVTNBTUCLCFG:
         smNbProcSm(pst->event);
         (Void)SPutMsg(mBuf);
         break;

      default:
         SPutMsg(mBuf);
         ret = RFAILED;
         NB_LOG_ERROR(&nbCb,"Invalid event [%d] received", pst->event);
         break;
   }

   RETVALUE(ret);
   
} /* end of smNbActvTsk */

/*

Layer management provides the necessary functions to control and
monitor the condition of each protocol layer.
   
The following functions are provided in this file:

     SmMiLwrCfgReq      Configure Request
     SmMiLwrCntrlReq    Control Request

It is assumed that the following functions are provided in the
stack management body files:

     SmMiLwrStaInd      Status Indication
     SmMiLwrStaCfm      Status Confirm
     SmMiLwrStsCfm      Statistics Confirm
     SmMiLwrTrcInd      Trace Indication

*/

#ifdef LWLCSMMILNB
#define  MAXNBMI  3
#else
#define  MAXNBMI  2
#endif

#ifndef  LCSMMILNB
#ifndef  PTSMMILNB
#define  PTSMMILNB
#endif
#else
#ifndef   NB
#ifndef  PTSMMILNB
#define  PTSMMILNB
#endif
#endif
#endif

/***************************************************************************
 *  layer management Confirmation handling
 **************************************************************************/

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
*       File:     
*
*/
  
#ifdef ANSI
PUBLIC S16 SmMiLnbCfgCfm
(
Pst     *pst,          /* post structure */
LnbMngmt *cfm           /* configuration */
)
#else
PUBLIC S16 SmMiLnbCfgCfm(pst,cfm)
Pst     *pst;          /* post structure */
LnbMngmt *cfm;          /* configuration */
#endif
{
   Pst      nbPst;

   TRC2(SmMiLnbCfgCfm);

   SM_SET_ZERO(&nbPst, sizeof(Pst));
   NB_LOG_DEBUG(&nbCb,"APP Cfg Cfm received for the element=%d",cfm->hdr.elmId.elmnt);
   if(cfm->cfm.status == LCM_PRIM_OK)
   {
      nbNbCfg++;
      if(nbNbCfg == 2)
      {
         smCfgCb.smState = NB_SM_STATE_APP_CFG_DONE;
         smNbProcSm(EVTNBS1APSTKBND);
      }
   }
   else if(cfm->cfm.status == LCM_PRIM_OK_NDONE)
   {
      nbUiSendConfigFailIndToUser(NB_ENBAPP_CFG_FAILED);  
      smCfgCb.smState  = NB_SM_STATE_INIT;
   }
   else 
   {
      NB_LOG_DEBUG(&nbCb,"APP Cfg Cfm received for"
            "the element = %d is NOT OK",cfm->hdr.elmId.elmnt);
   }
   RETVALUE(ROK);
} /* end of SmMiLnbCfgCfm */


/*
 *
 *       Fun:    SmMiLnbCntrlCfm - control confirm
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
PUBLIC S16 SmMiLnbCntrlCfm
(
Pst         *pst,
LnbMngmt     *cntrl
)
#else
PUBLIC S16 SmMiLnbCntrlCfm(pst, cntrl)
Pst         *pst;
LnbMngmt     *cntrl;
#endif /* ANSI */
{
   Pst  nbPst;

   /* wr002.102: Added trace macro */

   TRC2(SmMiLnbCntrlCfm)

      SM_SET_ZERO(&nbPst, sizeof(Pst));
   if( cntrl->hdr.elmId.elmnt == STNBS1CONSETUP)
   {
      NB_LOG_DEBUG(&nbCb,"Received Cntrl Confirm for S1 Setup");

   } 
   RETVALUE(ROK);

} /* end of SmMiLnbCntrlCfm() */


/*
 *
 *       Fun:    SmMiLnbStaInd - status indication
 *
 *       Desc:   Received the Status Indication
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
PUBLIC S16 SmMiLnbStaInd
(
Pst         *pst,
LnbMngmt      *usta
)
#else
PUBLIC S16 SmMiLnbStaInd(pst, usta)
Pst         *pst;
LnbMngmt      *usta;
#endif /* ANSI */
{
   /* wr002.102: Added trace macro */
   TRC2(SmMiLnbStaInd)

      if (usta->t.usta.alarm.category == LCM_CATEGORY_INTERFACE)
      {
         if (usta->t.usta.alarm.event == LCM_EVENT_BND_OK)
         {
            switch (usta->t.usta.alarm.cause)
            {
               case LNB_CAUSE_SZT_SAP_BOUND:
                  {
                     if (smCfgCb.smState == NB_SM_STATE_APP_CFG_DONE)
                     {
                        NB_LOG_DEBUG(&nbCb,"BIND OF S1AP STACK SUCCESSFUL");
                        smCfgCb.smState = NB_SM_STATE_S1AP_STK_BND_DONE;
                        smNbProcSm(EVTNBEGTPSTKBND);
                        /* Perform the bind of APP and SCTP */
                     }
                     break;
                  }
               case LNB_CAUSE_EGT_SAP_BOUND:
                  {
                     NB_LOG_DEBUG(&nbCb,"BIND OF RRM TO EGTP IS SUCCESSFUL ");
                     if (smCfgCb.smState == NB_SM_STATE_S1AP_STK_BND_DONE)
                     {
                        smCfgCb.smState = NB_SM_STATE_EGTP_STK_BND_DONE;
                        NB_LOG_DEBUG(&nbCb,"BIND OF EGTP STACK SUCCESSFUL");
                        smNbProcSm(EVTNBINITS1SETUP);
                     }
                     break;
                  }
               default:
                  break;

            } 
         }
         else if(usta->t.usta.alarm.event == LCM_EVENT_BND_FAIL)
         {
            smCfgCb.smState   = NB_SM_STATE_INIT;
            switch (usta->t.usta.alarm.cause)
            {
               case LNB_CAUSE_SZT_SAP_BOUND:
                  {
                     nbUiSendConfigFailIndToUser(NB_S1AP_BINDING_FAILED);
                     break;
                  }  
               case LNB_CAUSE_EGT_SAP_BOUND:
                  {
                     nbUiSendConfigFailIndToUser(NB_EGTP_BINDING_FAILED);
                     break;
                  }
               default:
                  {
                     NB_LOG_ERROR(&nbCb,"Invalid Sap");
                     break;
                  }
            }

         }  
      }
   RETVALUE(ROK);
} /* end of SmMiLnbStaInd() */

/****************************************************************************
 * layer management interface functions
 ****************************************************************************/

/*
*
*       Fun:   Configuration request
*
*       Desc:  Twrs function is used to configure  TUCL
*
*       Ret:   ROK      - ok
*
*       Notes: None
*              
*       File:     
*
*/
  
#ifdef ANSI
PUBLIC S16 SmMiLnbCfgReq
(
Pst *spst,                /* post structure */
LnbMngmt *cfg              /* configure */
)
#else
PUBLIC S16 SmMiLnbCfgReq(spst, cfg)
Pst *spst;                /* post structure */   
LnbMngmt *cfg;             /* configure */
#endif
{
   TRC3(SmMiLnbCfgReq)
   NbMiLnbCfgReq(spst,cfg); 
   RETVALUE(ROK);
} /* end of SmMiLwrCfgReq */


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
*       File:     
*
*/
  
#ifdef ANSI
PUBLIC S16 SmMiLnbCntrlReq
(
Pst *spst,                 /* post structure */
LnbMngmt *cntrl            /* control */
)
#else
PUBLIC S16 SmMiLnbCntrlReq(spst, cntrl)
Pst *spst;                 /* post structure */   
LnbMngmt *cntrl;           /* control */
#endif
{
   TRC3(SmMiLnbCntrlReq)
   NbMiLnbCntrlReq(spst,cntrl);
   RETVALUE(ROK);
} /* end of SmMiLnbCntrlReq */

/*
 * 
 *        Fun:   smBuildGenCfg
 * 
 *        Desc:  fill in cellCfg for WR
 * 
 *        Ret:   ROK
 * 
 *        Notes: None
 *               
 *        File:  wr_smm_enbapp_utils.c  
 */
#ifdef ANSI
PUBLIC S16 smBuildGenCfg
(
  LnbMngmt *lnbMng 
  )
#else /* if ANSI not defined*/
PUBLIC S16 smBuildGenCfg(lwrMng)
   LwrMngmt *lwrMng
#endif /* end of ANSI*/
{
   LnbGenCfg    *cfg = NULLP;
   cfg = &(lnbMng->t.cfg.t.genCfg);
   /*----------- Fill General Configuration Parameters ---------*/
   /* CELL Configuration  */
   cfg->cellId               =  smCfgCb.cellId;
   cfg->trackAreaCode        =  smCfgCb.trackAreaCode;

   cfg->plmnId.numMncDigits  =  smCfgCb.plmnId.numMncDigits;
   cfg->plmnId.mcc[0]        =  smCfgCb.plmnId.mcc[0];
   cfg->plmnId.mcc[1]        =  smCfgCb.plmnId.mcc[1];
   cfg->plmnId.mcc[2]        =  smCfgCb.plmnId.mcc[2];
   cfg->plmnId.mnc[0]        =  smCfgCb.plmnId.mnc[0];
   cfg->plmnId.mnc[1]        =  smCfgCb.plmnId.mnc[1];
   cfg->plmnId.mnc[2]        =  smCfgCb.plmnId.mnc[2];
   cfg->inactvTmrVal         =  smCfgCb.inactvTmrVal;
   cfg->expiryCnt            =  smCfgCb.maxExpires;
   cfg->s1SetUpTmrVal        =  smCfgCb.s1SetupTmrVal; 
   /* Filling the ENB Type */
   cfg->dataAppAddr.type                     = CM_TPTADDR_IPV4;
   cfg->dataAppAddr.u.ipv4TptAddr.port       = NB_DFLT_EGTP_PORT;
   cfg->dataAppAddr.u.ipv4TptAddr.address    = smCfgCb.enbIpAddr;
   cfg->mmeId                                = smCfgCb.mmeCfg[0]->mmeId;
   cfg->mmeAddr                              = smCfgCb.mmeCfg[0]->mmeAddr[0];

   /* Filling UE Inactivity Timer */
   RETVALUE(ROK);

}/*end of smBuildGenCfg*/

/*
 * 
 *        Fun:  nbSmSelfPstMsg 
 * 
 *        Desc:  This function is used by  Layer to self post 
 *               a message
 * 
 *        Ret:   None
 * 
 *        Notes: None
 * 
 *        File:  nb_smm_init.c
 * 
 * */
#ifdef ANSI
PUBLIC S16 nbSmSelfPstMsg
(
 Pst   *pst
 )
#else
PUBLIC S16 nbSmSelfPstMsg(pst)
   Pst   *pst;
#endif
{
   Buffer *mBuf;          /* message buffer */

   TRC2(nbSmSelfPstMsg);

   if(SGetMsg(DFLT_REGION, NB_POOL, &mBuf) != ROK)
   {
      RETVALUE(RFAILED);
   } /* end of if statement */

   RETVALUE(SPstTsk(pst, mBuf));

} /* end of nbSmSelfPstMsg */
 
/*****************************************************************************
 * Portable function definitions
 *****************************************************************************/


/*
*
*       Fun:   Portable configure Request- 
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
#if (!defined(LCSMMILNB)) && (!defined(NB)) && (!defined(LWLCSMMILNB))  
#ifdef ANSI
PRIVATE S16 PtMiLnbCfgReq
(
Pst *spst,                  /* post structure */
LnbMngmt *cfg                /* configure */
)
#else
PRIVATE S16 PtMiLnbCfgReq(spst, cfg)
Pst *spst;                  /* post structure */
LnbMngmt *cfg;               /* configure */
#endif
{
  TRC3(PtMiLnbCfgReq) 

  UNUSED(spst);
  UNUSED(cfg);
   
   RETVALUE(ROK);
} /* end of PtMiLnbCfgReq */
#endif


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
*       File:  
*
*/
#if (!defined(LCSMMILNB)) && (!defined(NB)) && (!defined(LWLCSMMILNB))  
#ifdef ANSI
PRIVATE S16 PtMiLnbCntrlReq
(
Pst *spst,                  /* post structure */
LnbMngmt *cntrl              /* control */
)
#else
PRIVATE S16 PtMiLnbCntrlReq(spst, cntrl)
Pst *spst;                  /* post structure */
LnbMngmt *cntrl;             /* control */
#endif
{
  TRC3(PtMiLnbCntrlReq)

  UNUSED(spst);
  UNUSED(cntrl);

 RETVALUE(ROK);
} /* end of PtMiLnbCntrlReq */
#endif
