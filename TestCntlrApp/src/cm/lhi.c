
/********************************************************************20**
  
     Name:     TCP UDP Convergence Layer
  
     Type:     C source file
  
     Desc:     C source code for common packing and un-packing functions for
               layer management interface(LHI) supplied by TRILLIUM.
              
     File:     lhi.c
  
     Sid:      lhi.c@@/main/13 - Tue Apr 26 18:11:18 2011

     Prg:      asa
  
*********************************************************************21*/

/*
*     This software may be combined with the following TRILLIUM
*     software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*
*/
  

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "cm_gen.h"        /* common pack/unpack defines */
#include "ssi.h"           /* system services */
#include "lhi.h"           /* layer management, HI Layer */
 
/* header/extern include files (.x) */
#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */
#include "lhi.x"           /* layer management, HI layer */ 
/* hi009.104 - added as HI_ZERO macro calls cmMemset which is defined in
 * cm_lib.x */
#include "cm_lib.x"            /* has the prototype of cmMemset() */

/* local defines */
  
/* local typedefs */
  
/* local externs */
  
/* forward references */



/* functions in other modules */
  
/* public variable declarations */
  
/* private variable declarations */

#ifdef LCLHI


 
/*
*     layer management interface packing functions
*/


/*
*
*       Fun:   Pack Config Request
*
*       Desc:  This function is used to a pack config request
*              to layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  lhi.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPkLhiCfgReq
(
Pst *pst,                 /* post structure */    
HiMngmt *cfg              /* configuration */
)
#else
PUBLIC S16 cmPkLhiCfgReq(pst, cfg)
Pst *pst;                 /* post structure */    
HiMngmt *cfg;             /* configuration */
#endif
{
 
   Buffer *mBuf;            /* message buffer */
   S16    i;

   TRC3(cmPkLhiCfgReq)

   if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
   {
      RETVALUE(RFAILED);
   }
   
   switch (cfg->hdr.elmId.elmnt)
   {
      case STGEN:
      {
         HiGenCfg *gen = &(cfg->t.cfg.s.hiGen);
         
   /* hi009.104 - added to pack the addr & port to bind the generic sock */
#ifdef HI_SPECIFY_GENSOCK_ADDR
#ifdef IPV6_SUPPORTED         
         CMCHKPKLOG(cmPkCmIpv6TptAddr,
                                &gen->ipv6GenSockAddr, mBuf, ELHI001, pst);
#endif /* IPV6_SUPPORTED */         
         CMCHKPKLOG(cmPkCmIpv4TptAddr, 
                                &gen->ipv4GenSockAddr, mBuf, ELHI002, pst);
#endif /* HI_SPECIFY_GENSOCK_ADDR */
         
         CMCHKPKLOG(cmPkPst,    &gen->lmPst,       mBuf, ELHI003, pst);   
         CMCHKPKLOG(cmPkTicks,  gen->timeRes,      mBuf, ELHI004, pst);   
         CMCHKPKLOG(cmPkStatus, gen->poolStopThr, mBuf, ELHI005, pst);   
         CMCHKPKLOG(cmPkStatus, gen->poolDropThr, mBuf, ELHI006, pst);   
         CMCHKPKLOG(cmPkStatus, gen->poolStrtThr, mBuf, ELHI007, pst);   
         CMCHKPKLOG(SPkU16,     gen->schdTmrVal,   mBuf, ELHI008, pst);   
         CMCHKPKLOG(cmPkBool,   gen->permTsk,      mBuf, ELHI009, pst);   
         CMCHKPKLOG(SPkU8, gen->numClToAccept, mBuf, ELHI010, pst);
         CMCHKPKLOG(SPkU8, gen->numUdpMsgsToRead, mBuf, ELHI011, pst);
         CMCHKPKLOG(SPkU8, gen->numRawMsgsToRead, mBuf, ELHI012, pst);
#ifdef HI_LKSCTP
         CMCHKPKLOG(SPkU8,  gen->maxPathReTx,  mBuf, ELHI013, pst);
         CMCHKPKLOG(SPkU8,  gen->maxAssocReTx, mBuf, ELHI014, pst);
         CMCHKPKLOG(SPkU8,  gen->maxInitReTx,  mBuf, ELHI015, pst);
         CMCHKPKLOG(SPkU16, gen->numAssocBins, mBuf, ELHI016, pst);   
#endif
         CMCHKPKLOG(SPkU32, gen->selTimeout, mBuf, ELHI017, pst);
         CMCHKPKLOG(SPkU16, gen->numFdBins, mBuf, ELHI018, pst);   
         CMCHKPKLOG(SPkU16, gen->numFdsPerSet, mBuf, ELHI019, pst);   
         CMCHKPKLOG(SPkU32, gen->numCons, mBuf, ELHI020, pst);   
         CMCHKPKLOG(SPkU16, gen->numSaps, mBuf, ELHI021, pst);   

#ifdef HI_TLS
         CMCHKPKLOG(cmPkBool, gen->initOpenSSL, mBuf, ELHI022, pst);   
         CMCHKPKLOG(SPkU16,   gen->numContexts, mBuf, ELHI023, pst);   
         if (gen->prng.option == LHI_OSSL_PRNG_FILE)
         {
            for (i = 0;  i < LHI_OSSL_PATHLEN;  i++)
            {
               CMCHKPKLOG(SPkS8, gen->prng.u.file[i], mBuf, ELHI024, pst);
            }
         }
         else if (gen->prng.option == LHI_OSSL_PRNG_SEED)
         {
            for (i = 0;  i < LHI_OSSL_PRNG_SEED_LEN;  i++)
            {
               CMCHKPKLOG(SPkU8, gen->prng.u.seed[i], mBuf, ELHI025, pst);
            }
         }
         CMCHKPKLOG(SPkU8,    gen->prng.option, mBuf, ELHI026, pst);   
#endif

         /* lhi_c_001.main_10 1.pack and unpack the region and pool id. */
         /* lhi_c_001.main_12: Replaced CMCHKPK with CMCHKPKLOG macro */
         CMCHKPKLOG(cmPkPool, gen->initPool, mBuf, ELHI637, pst);
         CMCHKPKLOG(cmPkRegion, gen->initRegion, mBuf, ELHI638, pst);
      break;
      }

      case STTSAP:
      {
         HiSapCfg *sap = &(cfg->t.cfg.s.hiSap);
#ifdef TDS_ROLL_UPGRADE_SUPPORT
         /* hi009.104 - addition - packing fields for interface ver info */
         CMCHKPKLOG(cmPkIntfVer, sap->remIntfVer, mBuf, ELHI027, pst);
         CMCHKPKLOG(SPkU8, sap->remIntfValid, mBuf, ELHI028, pst);
#endif /* TDS_ROLL_UPGRADE_SUPPORT */         

         for(i=0; i< LHI_MAX_HDR_TYPE; i++)
         {
            CMCHKPKLOG(SPkU32, sap->hdrInf[i].hdrLen, mBuf, ELHI029, pst);   
            CMCHKPKLOG(SPkU32, sap->hdrInf[i].offLen, mBuf, ELHI030, pst);   
            CMCHKPKLOG(SPkU32, sap->hdrInf[i].lenLen, mBuf, ELHI031, pst);   
            CMCHKPKLOG(SPkU32, sap->hdrInf[i].flag,   mBuf, ELHI032, pst);   
         }

         CMCHKPKLOG(cmPkMemoryId, &sap->uiMemId, mBuf, ELHI033, pst);   
         CMCHKPKLOG(cmPkSelector, sap->uiSel,    mBuf, ELHI034, pst);   
         CMCHKPKLOG(cmPkRoute,    sap->uiRoute,  mBuf, ELHI035, pst);   
         CMCHKPKLOG(cmPkPrior,    sap->uiPrior,  mBuf, ELHI036, pst);   
#ifdef HI_LKSCTP
         /* lhi_c_001.main_9: Handling of instream and outstream */
#ifdef HI_LKSCTP_USER_CONFIG
         CMCHKPKLOG(SPkU16,  sap->maxNmbOutStrms, mBuf, ELHI629, pst);
         CMCHKPKLOG(SPkU16,  sap->maxNmbInStrms,  mBuf, ELHI630, pst);
#endif
         CMCHKPKLOG(SPkU32,       sap->intervalTm,  mBuf, ELHI037, pst);   
/*  lhi_c_007.main_1 : Updated for the support of configurable RTO parameters, 
  HBeat value Max retransmissions (Init, Path, Association)*/
                                                                                                                         
         /* lhi_c_001.main_11: Updated the varibale type to U32 from U16 for follwing 
          * variables rtoInitial, rtoMin, rtoMax,cookieLife, intervalTm*/

         CMCHKPKLOG(SPkU32,       sap->cookieLife,  mBuf, ELHI038, pst);   
         CMCHKPKLOG(SPkU16,       sap->t1Init,      mBuf, ELHI039, pst);   
         CMCHKPKLOG(SPkU32,       sap->rtoMax,      mBuf, ELHI040, pst);   
         CMCHKPKLOG(SPkU32,       sap->rtoMin,      mBuf, ELHI041, pst);   
         CMCHKPKLOG(SPkU32,       sap->rtoInitial,  mBuf, ELHI042, pst);   
         CMCHKPKLOG(cmPkBool,     sap->hBeatEnable, mBuf, ELHI043, pst);   
         CMCHKPKLOG(SPkU8,        sap->type,        mBuf, ELHI044, pst);   
#endif
         CMCHKPKLOG(SPkU16,       sap->numBins,  mBuf, ELHI045, pst);   
         CMCHKPKLOG(SPkU32,       sap->txqCongStopLim,  mBuf, ELHI046, pst);   
         CMCHKPKLOG(SPkU32,       sap->txqCongDropLim,  mBuf, ELHI047, pst);   
         CMCHKPKLOG(SPkU32,       sap->txqCongStrtLim, mBuf, ELHI048, pst);   
         CMCHKPKLOG(cmPkBool,     sap->flcEnb,     mBuf, ELHI049, pst);   
         CMCHKPKLOG(cmPkSpId,     sap->spId,       mBuf, ELHI050, pst);   

      break;
      }

#ifdef HI_TLS
      case STCTX:
      {
         HiCtxCfg *ctx = &cfg->t.cfg.s.hiCtx;

         CMCHKPKLOG(SPkS16,       ctx->ctxId,     mBuf, ELHI051, pst);   
         for (i = 0;  i < LHI_OSSL_PATHLEN;  i++)
            CMCHKPKLOG(SPkS8,     ctx->caPath[i], mBuf, ELHI052, pst);   
         for (i = 0;  i < LHI_OSSL_PATHLEN;  i++)
            CMCHKPKLOG(SPkS8,     ctx->caFile[i], mBuf, ELHI053, pst);   
         for (i = 0;  i < LHI_OSSL_PATHLEN;  i++)
            CMCHKPKLOG(SPkS8,     ctx->certFile[i], mBuf, ELHI054, pst);   
         for (i = 0;  i < LHI_OSSL_PATHLEN;  i++)
            CMCHKPKLOG(SPkS8,     ctx->privKeyFile[i], mBuf, ELHI055, pst);   
         CMCHKPKLOG(SPkU32,       ctx->privKeyFileType, mBuf, ELHI056, pst);   
         CMCHKPKLOG(SPkU32,       ctx->verifyMode, mBuf, ELHI057, pst);   
         /* lhi_c_003.main_1 : To make TLS method and verification depth as 
                        configurable parameter */
#ifdef HI_VERIFY_DEPTH
         CMCHKPKLOG(SPkU8,        ctx->verifyDepth, mBuf, ELHI058, pst);   
#endif 
#ifdef HI_TLS_METHOD         
         CMCHKPKLOG(SPkU8,        ctx->method, mBuf, ELHI059, pst);   
#endif
         for (i = 0;  i < LHI_OSSL_CIPHERLEN;  i++)
            CMCHKPKLOG(SPkS8,     ctx->ciphers[i], mBuf, ELHI060, pst);   
         CMCHKPKLOG(cmPkBool,     ctx->cacheSessions, mBuf, ELHI061, pst);
         for (i = 0;  i < ctx->sessIdCtxLen;  i++)
            CMCHKPKLOG(SPkU8,     ctx->sessIdCtx[i], mBuf, ELHI062, pst);   
         CMCHKPKLOG(SPkU8,        ctx->sessIdCtxLen, mBuf, ELHI063, pst);
         CMCHKPKLOG(SPkU32,       ctx->sessTimeout, mBuf, ELHI064, pst);
      }
      break;
#endif

      default:
#if (ERRCLASS & ERRCLS_DEBUG)
         LHILOGERROR(pst, ELHI065, cfg->hdr.elmId.elmnt, 
                     "cmPkLhiCfgReq() Failed"); 
#endif /* ERRCLS_DEBUG */
         (Void)SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }/* end of switch */

   CMCHKPKLOG(cmPkCmStatus, &cfg->cfm, mBuf, ELHI066, pst);
   CMCHKPKLOG(cmPkHeader, &cfg->hdr, mBuf, ELHI067, pst);
   pst->event = (Event)EVTLHICFGREQ;

/* hi009.104 - fill interface version number in pst */
#ifdef TDS_ROLL_UPGRADE_SUPPORT
      pst->intfVer = (CmIntfVer) LHIIFVER;
#endif /* TDS_ROLL_UPGRADE_SUPPORT */
      
   RETVALUE(SPstTsk(pst, mBuf));
}


/*
*
*       Fun:   Pack Config Confirm
*
*       Desc:  This function is used to a pack config confirm 
*              to layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  lhi.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPkLhiCfgCfm
(
Pst *pst,                 /* post structure */    
HiMngmt *cfm              /* confirm */
)
#else
PUBLIC S16 cmPkLhiCfgCfm(pst, cfm)
Pst *pst;                 /* post structure */    
HiMngmt *cfm;             /* confirm */
#endif
{
   Buffer *mBuf;          /* message buffer */
 
   TRC3(cmPkLhiCfgCfm)
   if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
   {
      RETVALUE(RFAILED);
   }
   CMCHKPKLOG(cmPkCmStatus, &cfm->cfm, mBuf, ELHI068, pst);
   CMCHKPKLOG(cmPkHeader,   &cfm->hdr, mBuf, ELHI069, pst);
   
   pst->event = EVTLHICFGCFM;
   RETVALUE(SPstTsk(pst, mBuf));

} /* end of cmPkLhiCfgCfm */


/*
*
*       Fun:   Pack Control Request
*
*       Desc:  This function is used to pack the control request 
*              to layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  lhi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkLhiCntrlReq
(
Pst *pst,                 /* post structure */    
HiMngmt *ctl              /* configuration */
)
#else
PUBLIC S16 cmPkLhiCntrlReq(pst, ctl)
Pst *pst;                 /* post structure */    
HiMngmt *ctl;             /* configuration */
#endif
{
   Buffer *mBuf;          /* message buffer */
 
   TRC3(cmPkLhiCntrlReq)
   if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
   {
      RETVALUE(RFAILED);
   }
   switch(ctl->hdr.elmId.elmnt) 
   {
      case STGEN:
         if(ctl->t.cntrl.subAction == SADBG)
         {
#ifdef DEBUGP
           CMCHKPKLOG(SPkU32, ctl->t.cntrl.ctlType.hiDbg.dbgMask, 
                      mBuf, ELHI070, pst);
#endif
         }
#ifdef SS_DIAG 
         else if(ctl->t.cntrl.subAction == SALOG)
         {
           CMCHKPKLOG(SPkU32, ctl->t.cntrl.ctlType.logMask, 
                      mBuf, ERRLHI, pst);
         }
#endif
         break;

      case STTSAP:
         if(ctl->t.cntrl.subAction == SATRC)
         {
            CMCHKPKLOG(cmPkSpId, ctl->t.cntrl.ctlType.trcDat.sapId, 
                       mBuf, ELHI071, pst);
            CMCHKPKLOG(SPkS16, ctl->t.cntrl.ctlType.trcDat.trcLen, 
                       mBuf, ELHI072, pst);
         }
         else if(ctl->t.cntrl.subAction == SAELMNT)
         {
            CMCHKPKLOG(cmPkSpId, ctl->t.cntrl.ctlType.sapId, mBuf, 
                       ELHI073, pst);
         }
         else
         {
#if (ERRCLASS & ERRCLS_DEBUG)
         LHILOGERROR(pst, ELHI074,  ctl->t.cntrl.subAction, 
                     "cmPkLhiCntrlReq() : invalid subAction(STTSAP) "); 
#endif /* ERRCLS_DEBUG */
            (Void)SPutMsg(mBuf);
            RETVALUE(RFAILED);
         }
         break;

      case STGRTSAP:
         if(ctl->t.cntrl.subAction == SAGR_PRIORITY)
         {
            CMCHKPKLOG(cmPkPrior, ctl->t.cntrl.ctlType.priority, mBuf, 
                       ELHI075, pst);
         }
         else if(ctl->t.cntrl.subAction == SAGR_ROUTE)
         {
            CMCHKPKLOG(cmPkProcId, ctl->t.cntrl.ctlType.route, mBuf, 
                       ELHI076, pst);
         }
         else if(ctl->t.cntrl.subAction == SAGR_DSTPROCID)
         {
            CMCHKPKLOG(cmPkProcId, ctl->t.cntrl.ctlType.dstProcId, mBuf, 
                       ELHI077, pst);
         }
         else
         {
#if (ERRCLASS & ERRCLS_DEBUG)
         LHILOGERROR(pst, ELHI078, ctl->t.cntrl.subAction, 
                     "cmPkLhiCntrlReq() :invalid subAction(STGRTSAP)"); 
#endif /* ERRCLS_DEBUG */
            (Void)SPutMsg(mBuf);
            RETVALUE(RFAILED);
         }
         break;

      default:
#if (ERRCLASS & ERRCLS_DEBUG)
         LHILOGERROR(pst, ELHI079, ctl->hdr.elmId.elmnt, 
                     "cmPkLhiCntrlReq () Failed : invalid elmnt"); 
#endif /* ERRCLS_DEBUG */
         (Void)SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }/* end of switch */

   CMCHKPKLOG(SPkU8,       ctl->t.cntrl.subAction, mBuf, ELHI080, pst);
   CMCHKPKLOG(SPkU8,       ctl->t.cntrl.action,    mBuf, ELHI081, pst);
   CMCHKPKLOG(cmPkDateTime, &ctl->t.cntrl.dt,       mBuf, ELHI082, pst);

   CMCHKPKLOG(cmPkCmStatus, &ctl->cfm, mBuf, ELHI083, pst);
   CMCHKPKLOG(cmPkHeader,   &ctl->hdr, mBuf, ELHI084, pst);
   pst->event = (Event)EVTLHICNTRLREQ;

/* hi009.104 - fill interface version number in pst */
#ifdef TDS_ROLL_UPGRADE_SUPPORT
   pst->intfVer = (CmIntfVer) LHIIFVER;
#endif /* TDS_ROLL_UPGRADE_SUPPORT */
   
   RETVALUE(SPstTsk(pst, mBuf));
}


/*
*
*       Fun:   Pack Control Confirm
*
*       Desc:  This function is used to pack the control confirm 
*              to layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  lhi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkLhiCntrlCfm
(
Pst *pst,                 /* post structure */    
HiMngmt *cfm              /* confirm */
)
#else
PUBLIC S16 cmPkLhiCntrlCfm(pst, cfm)
Pst *pst;                 /* post structure */    
HiMngmt *cfm;             /* confirm */
#endif
{
   Buffer *mBuf;          /* message buffer */
 
   TRC3(cmPkLhiCntrlCfm)
   if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
   {
      RETVALUE(RFAILED);
   }
   /* pack status */
   CMCHKPKLOG(cmPkCmStatus, &cfm->cfm, mBuf, ELHI085, pst);

   /* pack header */
   CMCHKPKLOG(cmPkHeader, &cfm->hdr, mBuf, ELHI086, pst);
   
   pst->event = EVTLHICNTRLCFM;
   RETVALUE(SPstTsk(pst, mBuf));

} /* end of cmPkLhiCntrlCfm */


 
/*
*
*       Fun:   Pack Statistics Request
*
*       Desc:  This function is used to pack the statistics request
*              primitive to layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  lhi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkLhiStsReq
(
Pst *pst,                 /* post structure */    
Action action,            /* action */
HiMngmt *sts              /* statistics */
)
#else
PUBLIC S16 cmPkLhiStsReq(pst, action, sts)
Pst *pst;                 /* post structure */    
Action action;            /* action */
HiMngmt *sts;             /* statistics */
#endif
{
   Buffer *mBuf;          /* message buffer */
 
   TRC3(cmPkLhiStsReq)
   if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
   {
      RETVALUE(RFAILED);
   }

   switch(sts->hdr.elmId.elmnt)
   {
      case STGEN:
         break;
/*lhi_c_004.main_1  1. modified statistics req to include messages
                              Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS
      case STHITHR:
        break;
#endif /*LHI_THR_STS*/
      case STTSAP:
      {
         CMCHKPKLOG(cmPkSpId, sts->t.sts.s.sapSts.sapId, mBuf, ELHI087, pst);
         break;
      }
      default:
#if (ERRCLASS & ERRCLS_DEBUG)
         LHILOGERROR(pst, ELHI088, sts->hdr.elmId.elmnt, 
                     "cmPkLhiStsReq () Failed : invalid elmnt"); 
#endif /* ERRCLS_DEBUG */
         (Void)SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }
   CMCHKPKLOG(cmPkCmStatus, &sts->cfm, mBuf, ELHI089, pst);
   CMCHKPKLOG(cmPkHeader,   &sts->hdr, mBuf, ELHI090, pst);
   CMCHKPKLOG(cmPkAction,   action,    mBuf, ELHI091, pst);
   pst->event = EVTLHISTSREQ;

/* hi009.104 - fill interface version number in pst */
#ifdef TDS_ROLL_UPGRADE_SUPPORT
      pst->intfVer = (CmIntfVer) LHIIFVER;
#endif /* TDS_ROLL_UPGRADE_SUPPORT */
   
   RETVALUE(SPstTsk(pst, mBuf));
} /* end of cmPkLhiStsReq */

/*lhi_c_004.main_1  1. Modified statistics req to include messages
                              Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS
 
/*
*
*       Fun:   Pack connection Statistics
*
*       Desc:  This function is used to pack the statistics confirm
*              primitive to layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  lhi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkHiConSts
(
HiConSts *sts,              /* statistics */
Buffer  *mBuf              /* to hold the packed buffer */
)
#else
PUBLIC S16 cmPkHiConSts(sts, mBuf)
HiConSts *sts;              /* statistics */
Buffer  *mBuf;             /* to hold the packed buffer */
#endif
{
   /*lhi_c_001.main_11: Added TRC macro for cmPkHiConSts()*/
   TRC3(cmPkHiConSts)
   CMCHKPK(cmPkStsCntr, sts->numTxBytes, mBuf);
   CMCHKPK(cmPkStsCntr, sts->numRxBytes, mBuf);

   RETVALUE(ROK);
}/*cmPkHiConSts*/

 
/*
*
*       Fun:   Pack Con Statistics per thread 
*
*       Desc:  This function is used to pack the statistics confirm
*              primitive to layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  lhi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkHiThrConSts
(
HiThrConSts *sts,              /* statistics */
Pst *pst,
Buffer  *mBuf              /* to hold the packed buffer */
)
#else
PUBLIC S16 cmPkHiThrConSts(sts, pst, mBuf)
HiThrConSts *sts;              /* statistics */
Pst *pst;
Buffer  *mBuf;             /* to hold the packed buffer */
#endif
{
   /* this will hold the temporary index value for number of Threads */
   U8 iThrConIndex = 0;

   /*lhi_c_001.main_11: Added TRC macro for cmPkHiThrConSts()*/
   TRC3(cmPkHiThrConSts)
   /* if connection are present in threads, then only pack them */
   if (sts->numCons)
   {
      /* in a loop pack the thread statistics of all commands */
      for (; iThrConIndex < sts->numCons; iThrConIndex++)
      {
         /* lhi_c_001.main_12: Replaced CMCHKPK with CMCHKPKLOG macro */
         CMCHKPKLOG(cmPkHiConSts, &sts->conSts[iThrConIndex], mBuf, ELHI639, pst);
      } 

     SPutSBuf(pst->region, pst->pool, (Data*)sts->conSts,
                 (Size)(sizeof(HiConSts) * sts->numCons));
     sts->conSts = NULLP;
   } /* end of if threads are present */

   /* lhi_c_001.main_12: Replaced CMCHKPK with CMCHKPKLOG macro */
   CMCHKPKLOG(SPkU32, sts->numCons, mBuf, ELHI640, pst);

   RETVALUE(ROK);
}/*cmPkHiThrConSts*/

#endif /*LHI_THR_STS*/
 
/*
*
*       Fun:   Pack Statistics Confirm
*
*       Desc:  This function is used to pack the statistics confirm
*              primitive to layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  lhi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkLhiStsCfm
(
Pst *pst,                 /* post structure */    
HiMngmt *sts              /* statistics */
)
#else
PUBLIC S16 cmPkLhiStsCfm(pst, sts)
Pst *pst;                 /* post structure */    
HiMngmt *sts;             /* statistics */
#endif

{
   Buffer *mBuf;          /* message buffer */
 
   TRC3(cmPkLhiStsCfm)
   if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
   {
      RETVALUE(RFAILED);
   }

   switch(sts->hdr.elmId.elmnt)
   {
      case STGEN:
      {
         HiGenSts *gSts = &(sts->t.sts.s.genSts);
#ifdef HI_LKSCTP
         CMCHKPKLOG(cmPkStsCntr, gSts->numRxSctpMsg,  mBuf, ELHI092, pst);
         CMCHKPKLOG(cmPkStsCntr, gSts->numTxSctpMsg,  mBuf, ELHI093, pst);
#endif
         CMCHKPKLOG(cmPkStsCntr, gSts->numRxRawMsg,  mBuf, ELHI094, pst);
         CMCHKPKLOG(cmPkStsCntr, gSts->numTxRawMsg,  mBuf, ELHI095, pst);
         CMCHKPKLOG(cmPkStsCntr, gSts->numRxbytes,  mBuf, ELHI096, pst);
         CMCHKPKLOG(cmPkStsCntr, gSts->numTxbytes,  mBuf, ELHI097, pst);
         CMCHKPKLOG(cmPkStsCntr, gSts->numRxUdpMsg, mBuf, ELHI098, pst);
         CMCHKPKLOG(cmPkStsCntr, gSts->numTxUdpMsg, mBuf, ELHI099, pst);
         CMCHKPKLOG(cmPkStsCntr, gSts->numRxTcpMsg, mBuf, ELHI100, pst);
         CMCHKPKLOG(cmPkStsCntr, gSts->numTxTcpMsg, mBuf, ELHI101, pst);
         CMCHKPKLOG(cmPkStsCntr, gSts->numFlcInd,   mBuf, ELHI102, pst);
         CMCHKPKLOG(cmPkStsCntr, gSts->rxMsgVerErr, mBuf, ELHI103, pst);
         CMCHKPKLOG(cmPkStsCntr, gSts->sockShutErr, mBuf, ELHI104, pst);
         CMCHKPKLOG(cmPkStsCntr, gSts->sockClosErr, mBuf, ELHI105, pst);
         CMCHKPKLOG(cmPkStsCntr, gSts->sockSOptErr, mBuf, ELHI106, pst);
         CMCHKPKLOG(cmPkStsCntr, gSts->sockLstnErr, mBuf, ELHI107, pst);
         CMCHKPKLOG(cmPkStsCntr, gSts->sockCnctErr, mBuf, ELHI108, pst);
         CMCHKPKLOG(cmPkStsCntr, gSts->sockBindErr, mBuf, ELHI109, pst);
         CMCHKPKLOG(cmPkStsCntr, gSts->sockOpenErr, mBuf, ELHI110, pst);
         CMCHKPKLOG(cmPkStsCntr, gSts->sockRxErr,   mBuf, ELHI111, pst);
         CMCHKPKLOG(cmPkStsCntr, gSts->sockTxErr,   mBuf, ELHI112, pst);
         CMCHKPKLOG(cmPkStsCntr, gSts->numCons,     mBuf, ELHI113, pst);
         break;
      }
      case STTSAP:
      {
         HiSapSts *sSts = &(sts->t.sts.s.sapSts);
#ifdef HI_LKSCTP
         CMCHKPKLOG(cmPkStsCntr, sSts->numRxSctpMsg,  mBuf, ELHI114, pst);
         CMCHKPKLOG(cmPkStsCntr, sSts->numTxSctpMsg,  mBuf, ELHI115, pst);
#endif
         CMCHKPKLOG(cmPkStsCntr, sSts->numRxRawMsg,  mBuf, ELHI116, pst);
         CMCHKPKLOG(cmPkStsCntr, sSts->numTxRawMsg,  mBuf, ELHI117, pst);
         CMCHKPKLOG(cmPkStsCntr, sSts->numRxbytes,  mBuf, ELHI118, pst);
         CMCHKPKLOG(cmPkStsCntr, sSts->numTxbytes,  mBuf, ELHI119, pst);
         CMCHKPKLOG(cmPkStsCntr, sSts->numRxUdpMsg, mBuf, ELHI120, pst);
         CMCHKPKLOG(cmPkStsCntr, sSts->numTxUdpMsg, mBuf, ELHI121, pst);
         CMCHKPKLOG(cmPkStsCntr, sSts->numRxTcpMsg, mBuf, ELHI122, pst);
         CMCHKPKLOG(cmPkStsCntr, sSts->numTxTcpMsg, mBuf, ELHI123, pst);
         CMCHKPKLOG(cmPkStsCntr, sSts->numCons,     mBuf, ELHI124, pst);
         CMCHKPKLOG(cmPkSpId,    sSts->sapId,       mBuf, ELHI125, pst);
         break;
      }
/*lhi_c_004.main_1  1. modified statistics req to include messages
                              Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS
      case STHITHR:
      {
         HiThrSts *tSts = &(sts->t.sts.s.thrSts);
         /* this will hold the temporary index value for number of Threads */
         U8 iThrIndex = 0;

         /* if threads are present, then only pack them */
         if (tSts->numRcvThrds)
         {
            /* in a loop pack the thread statistics of all commands */
            for (; iThrIndex < tSts->numRcvThrds; iThrIndex++)
            {
               cmPkHiThrConSts(&tSts->thrConSts[iThrIndex], pst, mBuf);
            } 

           SPutSBuf(pst->region, pst->pool, (Data* )tSts->thrConSts,
                       (Size)(sizeof(HiThrConSts) * tSts->numRcvThrds));
           tSts->thrConSts = NULLP;
         } /* end of if threads are present */

         /* lhi_c_001.main_12: Replaced CMCHKPK with CMCHKPKLOG macro */
         CMCHKPKLOG(SPkU32, tSts->numRcvThrds, mBuf, ELHI641, pst);

         break;
      }
#endif /*LHI_THR_STS*/

      default:
#if (ERRCLASS & ERRCLS_DEBUG)
         LHILOGERROR(pst, ELHI126, sts->hdr.elmId.elmnt, 
                     "cmPkLhiStsCfm() : invalid elmnt"); 
#endif /* ERRCLS_DEBUG */
         (Void)SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }
   
   CMCHKPKLOG(cmPkDuration, &sts->t.sts.dura, mBuf, ELHI127, pst);
   CMCHKPKLOG(cmPkDateTime, &sts->t.sts.dt, mBuf, ELHI128, pst);

   CMCHKPKLOG(cmPkCmStatus, &sts->cfm, mBuf, ELHI129, pst);
   CMCHKPKLOG(cmPkHeader,   &sts->hdr, mBuf, ELHI130, pst);
   pst->event = (Event)EVTLHISTSCFM;
   RETVALUE(SPstTsk(pst, mBuf));
}


/*
*
*       Fun:   Pack Status Request
*
*       Desc:  This function is used to pack the status request
*              primitive to layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  lhi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkLhiStaReq
(
Pst *pst,                 /* post structure */     
HiMngmt *sta              /* solicited status */
)
#else
PUBLIC S16 cmPkLhiStaReq(pst, sta)
Pst *pst;                 /* post structure */     
HiMngmt *sta;             /* solicited status */
#endif
{
   Buffer *mBuf;          /* message buffer */
 
   TRC3(cmPkLhiStaReq)
   if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
   {
      RETVALUE(RFAILED);
   }

   switch(sta->hdr.elmId.elmnt)
   {
      case STSID:
         break;
      case STTSAP:
         CMCHKPKLOG(cmPkSpId, sta->t.ssta.s.sapSta.spId, mBuf, ELHI131, pst);
         break;
      default:
#if (ERRCLASS & ERRCLS_DEBUG)
         LHILOGERROR(pst, ELHI132, sta->hdr.elmId.elmnt, 
                     "cmPkLhiStaReq () : invalid elmnt"); 
#endif /* ERRCLS_DEBUG */
         (Void)SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }

   CMCHKPKLOG(cmPkCmStatus, &sta->cfm, mBuf, ELHI133, pst);
   CMCHKPKLOG(cmPkHeader, &sta->hdr, mBuf, ELHI134, pst);
   pst->event = (Event)EVTLHISTAREQ;

   /* hi009.104 - fill interface version number in pst */
#ifdef TDS_ROLL_UPGRADE_SUPPORT
      pst->intfVer = (CmIntfVer) LHIIFVER;
#endif /* TDS_ROLL_UPGRADE_SUPPORT */   
   
   RETVALUE(SPstTsk(pst, mBuf));
}


/*
*
*       Fun:   Pack Status Confirm
*
*       Desc:  This function is used to pack the status confirm
*              primitive to layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  lhi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkLhiStaCfm
(
Pst *pst,                 /* post structure */     
HiMngmt *sta              /* solicited status */
)
#else
PUBLIC S16 cmPkLhiStaCfm(pst, sta)
Pst *pst;                 /* post structure */     
HiMngmt *sta;             /* solicited status */
#endif
{
   Buffer *mBuf;          /* message buffer */
 
   TRC3(cmPkLhiStaCfm)

   if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
   {
      RETVALUE(RFAILED);
   }
   switch(sta->hdr.elmId.elmnt)
   {
      case STSID:
      {
         CMCHKPKLOG(cmPkSystemId, &(sta->t.ssta.s.sysId), mBuf, ELHI135, pst);
         break;
      }
      case STTSAP:
      {
         HiSapSta *sSta = &(sta->t.ssta.s.sapSta);

/* hi009.104 - pcak self and remote interface version num */
#ifdef TDS_ROLL_UPGRADE_SUPPORT
         CMCHKPKLOG(cmPkIntfVer, sSta->remIfVer, mBuf, ELHI136, pst);
         CMCHKPKLOG(cmPkIntfVer, sSta->selfIfVer, mBuf, ELHI137, pst);
         CMCHKPKLOG(cmPkBool, sSta->remIntfValid, mBuf, ELHI138, pst);         
#endif /* TDS_ROLL_UPGRADE_SUPPORT */         

         CMCHKPKLOG(cmPkState, sSta->state, mBuf, ELHI139, pst);
         CMCHKPKLOG(cmPkSpId,  sSta->spId,  mBuf, ELHI140, pst);
         break;
      }
      default:
#if (ERRCLASS & ERRCLS_DEBUG)
         LHILOGERROR(pst, ELHI141, sta->hdr.elmId.elmnt, 
                     "cmPkLhiStaReq () Failed"); 
#endif /* ERRCLS_DEBUG */
         (Void)SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }

   /* date */
   CMCHKPKLOG(cmPkDateTime, &sta->t.ssta.dt, mBuf, ELHI142, pst);

   CMCHKPKLOG(cmPkCmStatus, &sta->cfm, mBuf, ELHI143, pst);
   CMCHKPKLOG(cmPkHeader,   &sta->hdr, mBuf, ELHI144, pst);
   pst->event = EVTLHISTACFM;
   RETVALUE(SPstTsk(pst, mBuf));
} /* end of cmPkLhiStaCfm */


/*
*
*       Fun:   Pack Status Indication
*
*       Desc:  This function is used to pack the status indication
*              primitive to the layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  lhi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkLhiStaInd
(
Pst *pst,                 /* post structure */
HiMngmt *sta              /* unsolicited status */
)
#else
PUBLIC S16 cmPkLhiStaInd(pst, sta)
Pst *pst;                 /* post structure */   
HiMngmt *sta;             /* unsolicited status */
#endif
{
   Buffer *mBuf;          /* message buffer */

   TRC3(cmPkLhiStaInd)

   if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
   {
      RETVALUE(RFAILED);
   }

   if(sta->t.usta.info.type != LHI_ALARMINFO_TYPE_NTPRSNT) 
   {
      switch(sta->t.usta.info.type)
      {
         case LHI_ALARMINFO_PAR_TYPE:
            CMCHKPKLOG(SPkU8, sta->t.usta.info.inf.parType, mBuf, ELHI145, 
                       pst);
            break;

         case LHI_ALARMINFO_MEM_ID:
            CMCHKPKLOG(cmPkPool, sta->t.usta.info.inf.mem.pool, 
                       mBuf, ELHI146, pst);
            CMCHKPKLOG(cmPkRegion, sta->t.usta.info.inf.mem.region, 
                       mBuf, ELHI147, pst);
            break;

         case LHI_ALARMINFO_CON_STATE:
            CMCHKPKLOG(cmPkState, sta->t.usta.info.inf.conState,
                       mBuf, ELHI148, pst);
            break;

         case LHI_ALARMINFO_SAP_STATE:
            CMCHKPKLOG(cmPkState, sta->t.usta.info.inf.state, 
                       mBuf, ELHI149, pst);
            break;

#ifdef HI_TLS
         case LHI_ALARMINFO_OSSL_ERR:
            CMCHKPKLOG(SPkS32, sta->t.usta.info.inf.osslError, mBuf,
                       ELHI150, pst);
            break;
#endif
            /*lhi_c_001.main_11: Added new usta.info.type and protected under
             * HI_LKSCTP flag */
#ifdef HI_LKSCTP 
         case LHI_ALARMINFO_ASSOC_ERR:
            CMCHKPKLOG(SPkU16, sta->t.usta.info.error, mBuf,
                  ELHI633, pst);
            CMCHKPKLOG(SPkU32, sta->t.usta.info.assocId, mBuf,
                  ELHI634, pst);
            break;
#endif 
         default:
#if (ERRCLASS & ERRCLS_DEBUG)
            LHILOGERROR(pst, ELHI151, sta->t.usta.info.type, 
                        "cmPkLhiStaInd () Failed"); 
#endif
            (Void)SPutMsg(mBuf);
            RETVALUE(RFAILED);
      }
   }
   CMCHKPKLOG(SPkU8,   sta->t.usta.info.type, mBuf, ELHI152, pst);
   CMCHKPKLOG(cmPkSpId,    sta->t.usta.info.spId,  mBuf, ELHI153, pst);
   CMCHKPKLOG(cmPkCmAlarm, &sta->t.usta.alarm,     mBuf, ELHI154, pst);

   CMCHKPKLOG(cmPkCmStatus, &sta->cfm, mBuf, ELHI155, pst);
   CMCHKPKLOG(cmPkHeader,   &sta->hdr, mBuf, ELHI156, pst);
   pst->event = (Event)EVTLHISTAIND;
   RETVALUE(SPstTsk(pst, mBuf));
} /* end of cmPkLhiStaInd */
 


/*
*
*       Fun:   Pack Trace Indication
*
*       Desc:  This function is used to pack the trace indication
*              primitive to layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  lhi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkLhiTrcInd
(
Pst *pst,                 /* post */
HiMngmt *trc,             /* trace */
Buffer  *mBuf             /* message buffer */
)
#else
PUBLIC S16 cmPkLhiTrcInd(pst, trc, mBuf)
Pst *pst;                 /* post */
HiMngmt *trc;             /* trace */
Buffer  *mBuf;            /* message buffer */
#endif
{
 
   TRC3(cmPkLhiTrcInd)

   if (mBuf == NULLP)
   {
      if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
      {
         RETVALUE(RFAILED);
      }
   }

 /* lhi_c_002.main_1 (hi023.104) Sap Id in Trace Information */
#ifdef HI_ENB_SAP_TRC
   CMCHKPKLOG(SPkU16, trc->t.trc.sap, mBuf, ELHI157, pst);
#endif

   CMCHKPKLOG(SPkU16, trc->t.trc.evnt, mBuf, ELHI158, pst);
   CMCHKPKLOG(cmPkDateTime, &trc->t.trc.dt, mBuf, ELHI159, pst);

   CMCHKPKLOG(cmPkCmStatus, &trc->cfm, mBuf, ELHI160, pst);
   CMCHKPKLOG(cmPkHeader,   &trc->hdr, mBuf, ELHI161, pst);
   pst->event = EVTLHITRCIND;
   RETVALUE(SPstTsk(pst, mBuf));
} /* end of cmPkLhiTrcInd */


/*
*     layer management interface un-packing functions
*/

/*
*
*       Fun:   Un-pack Config Request
*
*       Desc:  This function is used to a un-pack config request
*              to layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  lhi.c
*
*/

#ifdef ANSI
PUBLIC S16 cmUnpkLhiCfgReq
(
LhiCfgReq func,
Pst *pst,                 /* post structure */    
Buffer *mBuf              /* message buffer */
)
#else
PUBLIC S16 cmUnpkLhiCfgReq(func, pst, mBuf)
LhiCfgReq func;
Pst *pst;                 /* post structure */    
Buffer *mBuf;             /* message buffer */
#endif
{
 
   HiMngmt  mgt;            /* configuration */
   S16      i;
    
   TRC3(cmUnpkLhiCfgReq)

     /* lhi_c_001.main_11: Fix for Klockworks issue */
      cmMemset((U8 *)&mgt, 0, sizeof(HiMngmt));

   /* hi009.104 - call the new MACRO to init struc to all zeros */
   LHI_ZERO((U8 *)&mgt, sizeof(HiMngmt));
   
   CMCHKUNPKLOG(cmUnpkHeader,   &mgt.hdr, mBuf, ELHI162, pst);
   CMCHKUNPKLOG(cmUnpkCmStatus, &mgt.cfm, mBuf, ELHI163, pst);
   
   switch (mgt.hdr.elmId.elmnt)
   {
      case STGEN:
      {
         HiGenCfg *gen = &(mgt.t.cfg.s.hiGen);

         /* lhi_c_001.main_10 1.pack and unpack the region and pool id. */
         /* lhi_c_001.main_12: Replaced CMCHKPK with CMCHKPKLOG macro */
         CMCHKUNPKLOG(cmUnpkRegion, &gen->initRegion, mBuf, ELHI642, pst); 
         CMCHKUNPKLOG(cmUnpkPool, &gen->initPool, mBuf, ELHI643, pst); 
#ifdef HI_TLS
         CMCHKUNPKLOG(SUnpkU8,    &gen->prng.option, mBuf, ELHI164, pst);   
         if (gen->prng.option == LHI_OSSL_PRNG_FILE)
         {
            for (i = LHI_OSSL_PATHLEN - 1;  i >= 0;  i--)
            {
               CMCHKUNPKLOG(SUnpkS8, &gen->prng.u.file[i], mBuf, ELHI165, pst);
            }
         }
         else if (gen->prng.option == LHI_OSSL_PRNG_SEED)
         {
            for (i = LHI_OSSL_PRNG_SEED_LEN - 1;  i >= 0;  i--)
            {
               CMCHKUNPKLOG(SUnpkU8, &gen->prng.u.seed[i], mBuf, ELHI166, pst);
            }
         }
         CMCHKUNPKLOG(SUnpkU16,   &gen->numContexts, mBuf, ELHI167, pst);   
         CMCHKUNPKLOG(cmUnpkBool, &gen->initOpenSSL, mBuf, ELHI168, pst);   
#endif

         CMCHKUNPKLOG(SUnpkU16,     &gen->numSaps, mBuf, ELHI169, pst);   
         CMCHKUNPKLOG(SUnpkU32,     &gen->numCons, mBuf, ELHI170, pst);   
         CMCHKUNPKLOG(SUnpkU16,     &gen->numFdsPerSet, mBuf, ELHI171, pst);   
         CMCHKUNPKLOG(SUnpkU16,     &gen->numFdBins, mBuf, ELHI172, pst);   
         CMCHKUNPKLOG(SUnpkU32,     &gen->selTimeout, mBuf, ELHI173, pst);
#ifdef HI_LKSCTP
         CMCHKUNPKLOG(SUnpkU16,     &gen->numAssocBins,  mBuf, ELHI174, pst);   
         CMCHKUNPKLOG(SUnpkU8,      &gen->maxInitReTx,  mBuf, ELHI175, pst);   
         CMCHKUNPKLOG(SUnpkU8,      &gen->maxAssocReTx,  mBuf, ELHI176, pst);   
         CMCHKUNPKLOG(SUnpkU8,      &gen->maxPathReTx,  mBuf, ELHI177, pst);   
#endif
         CMCHKUNPKLOG(SUnpkU8,     &gen->numRawMsgsToRead, mBuf, ELHI178, pst);
         CMCHKUNPKLOG(SUnpkU8,     &gen->numUdpMsgsToRead, mBuf, ELHI179, pst);
         CMCHKUNPKLOG(SUnpkU8,     &gen->numClToAccept, mBuf, ELHI180, pst);
         CMCHKUNPKLOG(cmUnpkBool,   &gen->permTsk,      mBuf, ELHI181, pst);   
         CMCHKUNPKLOG(SUnpkU16,     &gen->schdTmrVal,   mBuf, ELHI182, pst);   
         CMCHKUNPKLOG(cmUnpkStatus, &gen->poolStrtThr, mBuf, ELHI183, pst);   
         CMCHKUNPKLOG(cmUnpkStatus, &gen->poolDropThr, mBuf, ELHI184, pst);   
         CMCHKUNPKLOG(cmUnpkStatus, &gen->poolStopThr, mBuf, ELHI185, pst);   
         CMCHKUNPKLOG(cmUnpkTicks,  &gen->timeRes,      mBuf, ELHI186, pst);   
         CMCHKUNPKLOG(cmUnpkPst,    &gen->lmPst,        mBuf, ELHI187, pst); 

   /* hi009.104 - added to unpack the addr & port to bind the generic sock */
#ifdef HI_SPECIFY_GENSOCK_ADDR     
         CMCHKUNPKLOG(cmUnpkCmIpv4TptAddr, 
                                &gen->ipv4GenSockAddr, mBuf, ELHI188, pst);
#ifdef IPV6_SUPPORTED         
         CMCHKUNPKLOG(cmUnpkCmIpv6TptAddr,
                                &gen->ipv6GenSockAddr, mBuf, ELHI189, pst);
#endif /* IPV6_SUPPORTED */             
#endif /* HI_SPECIFY_GENSOCK_ADDR */         
      break;
      }

      case STTSAP:
      {
         HiSapCfg *sap = &(mgt.t.cfg.s.hiSap);

         CMCHKUNPKLOG(cmUnpkSpId,&sap->spId,       mBuf, ELHI190, pst);   
         CMCHKUNPKLOG(cmUnpkBool,&sap->flcEnb,     mBuf, ELHI191, pst);   
         CMCHKUNPKLOG(SUnpkU32,  &sap->txqCongStrtLim, mBuf, ELHI192, pst);   
         CMCHKUNPKLOG(SUnpkU32,  &sap->txqCongDropLim,  mBuf, ELHI193, pst);   
         CMCHKUNPKLOG(SUnpkU32,  &sap->txqCongStopLim,  mBuf, ELHI194, pst);   
         CMCHKUNPKLOG(SUnpkU16,  &sap->numBins,  mBuf, ELHI195, pst);   
#ifdef HI_LKSCTP
         CMCHKUNPKLOG(SUnpkU8,   &sap->type,  mBuf, ELHI196, pst);   
         CMCHKUNPKLOG(cmUnpkBool,&sap->hBeatEnable,  mBuf, ELHI197, pst);   
         /* lhi_c_001.main_11: Updated the varibale type to U32 from U16 for follwing
          * variables rtoInitial, rtoMin, rtoMax,cookieLife, intervalTm*/
         CMCHKUNPKLOG(SUnpkU32,  &sap->rtoInitial,  mBuf, ELHI198, pst);   
         CMCHKUNPKLOG(SUnpkU32,  &sap->rtoMin,  mBuf, ELHI199, pst);   
         CMCHKUNPKLOG(SUnpkU32,  &sap->rtoMax,  mBuf, ELHI200, pst);   
         CMCHKUNPKLOG(SUnpkU16,  &sap->t1Init,  mBuf, ELHI201, pst);   
         CMCHKUNPKLOG(SUnpkU32,  &sap->cookieLife,  mBuf, ELHI202, pst);   
         CMCHKUNPKLOG(SUnpkU32,  &sap->intervalTm,  mBuf, ELHI203, pst);   
         /* lhi_c_001.main_9: Handling of instream and outstream */
#ifdef HI_LKSCTP_USER_CONFIG
         CMCHKUNPKLOG(SUnpkU16, &sap->maxNmbInStrms,  mBuf, ELHI631, pst);   
         CMCHKUNPKLOG(SUnpkU16, &sap->maxNmbOutStrms,  mBuf, ELHI632, pst);   
#endif
#endif
         CMCHKUNPKLOG(cmUnpkPrior, &sap->uiPrior,  mBuf, ELHI204, pst);   
         CMCHKUNPKLOG(cmUnpkRoute, &sap->uiRoute,  mBuf, ELHI205, pst);   
         CMCHKUNPKLOG(cmUnpkSelector,&sap->uiSel,    mBuf, ELHI206, pst);   
         CMCHKUNPKLOG(cmUnpkMemoryId,&sap->uiMemId,  mBuf, ELHI207, pst);   
         for(i=LHI_MAX_HDR_TYPE; i >0; i--)
         {
            CMCHKUNPKLOG(SUnpkU32, &sap->hdrInf[i-1].flag,    mBuf, 
                         ELHI208, pst);
            CMCHKUNPKLOG(SUnpkU32, &sap->hdrInf[i-1].lenLen,  mBuf, 
                         ELHI209, pst);
            CMCHKUNPKLOG(SUnpkU32, &sap->hdrInf[i-1].offLen,  mBuf, 
                         ELHI210, pst);
            CMCHKUNPKLOG(SUnpkU32, &sap->hdrInf[i-1].hdrLen,  mBuf, 
                         ELHI211, pst);
         }/* end for loop */

#ifdef TDS_ROLL_UPGRADE_SUPPORT
         /* hi009.104 - addition - unpacking fields for interface ver info */
         CMCHKUNPKLOG(SUnpkU8, &sap->remIntfValid, mBuf, ELHI212, pst);
         CMCHKUNPKLOG(cmUnpkIntfVer, &sap->remIntfVer, mBuf, ELHI213, pst);
#endif /* TDS_ROLL_UPGRADE_SUPPORT */         
      break;
      }

#ifdef HI_TLS
      case STCTX:
      {
         HiCtxCfg *ctx = &mgt.t.cfg.s.hiCtx;

         CMCHKUNPKLOG(SUnpkU32,       &ctx->sessTimeout, mBuf, ELHI214, pst);
         CMCHKUNPKLOG(SUnpkU8,        &ctx->sessIdCtxLen, mBuf, ELHI215, pst);
         for (i = ctx->sessIdCtxLen - 1;  i >= 0;  i--)
            CMCHKUNPKLOG(SUnpkU8,     &ctx->sessIdCtx[i], mBuf, ELHI216, pst);   
         CMCHKUNPKLOG(cmUnpkBool,     &ctx->cacheSessions, mBuf, ELHI217, pst);
         for (i = LHI_OSSL_CIPHERLEN - 1;  i >= 0;  i--)
            CMCHKUNPKLOG(SUnpkS8,     &ctx->ciphers[i], mBuf, ELHI218, pst);   
         
         /* lhi_c_003.main_1 : To make TLS method and verification depth as 
                        configurable parameter */
#ifdef HI_TLS_METHOD        
         CMCHKUNPKLOG(SUnpkU8,        &ctx->method, mBuf, ELHI219, pst);   
#endif
#ifdef HI_VERIFY_DEPTH 
         CMCHKUNPKLOG(SUnpkU8,        &ctx->verifyDepth, mBuf, ELHI220, pst);   
#endif         
         CMCHKUNPKLOG(SUnpkU32,       &ctx->verifyMode, mBuf, ELHI221, pst);   
         CMCHKUNPKLOG(SUnpkU32,       &ctx->privKeyFileType, mBuf, ELHI222, pst);   
         for (i = LHI_OSSL_PATHLEN - 1;  i >= 0;  i--)
            CMCHKUNPKLOG(SUnpkS8,     &ctx->privKeyFile[i], mBuf, ELHI223, pst);   
         for (i = LHI_OSSL_PATHLEN - 1;  i >= 0;  i--)
            CMCHKUNPKLOG(SUnpkS8,     &ctx->certFile[i], mBuf, ELHI224, pst);   
         for (i = LHI_OSSL_PATHLEN - 1;  i >= 0;  i--)
            CMCHKUNPKLOG(SUnpkS8,     &ctx->caFile[i], mBuf, ELHI225, pst);   
         for (i = LHI_OSSL_PATHLEN - 1;  i >= 0;  i--)
            CMCHKUNPKLOG(SUnpkS8,     &ctx->caPath[i], mBuf, ELHI226, pst);   
         CMCHKUNPKLOG(SUnpkS16,       &ctx->ctxId,     mBuf, ELHI227, pst);   
      }
      break;
#endif /* HI_TLS */

      default:
#if (ERRCLASS & ERRCLS_DEBUG)
         LHILOGERROR(pst, ELHI228, mgt.hdr.elmId.elmnt, 
                     "cmUnpkLhiCfgReq () Failed"); 
#endif
         (Void)SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }/* end of switch */

   (Void)SPutMsg(mBuf);
   (*func)(pst, &mgt);

   RETVALUE(ROK);
}


/*
*
*       Fun:   Un-pack Config Confirm
*
*       Desc:  This function is used to a un-pack config confirm 
*              to layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  lhi.c
*
*/

#ifdef ANSI
PUBLIC S16 cmUnpkLhiCfgCfm
(
LhiCfgCfm func,
Pst *pst,                 /* post structure */    
Buffer *mBuf               /* message buffer */
)
#else
PUBLIC S16 cmUnpkLhiCfgCfm(func, pst, mBuf)
LhiCfgCfm func;
Pst *pst;                 /* post structure */    
Buffer *mBuf;              /* message buffer */
#endif
{
 
   HiMngmt  mgt;            /* configuration */

   TRC3(cmUnpkLhiCfgCfm)

   /* hi009.104 - added missing init to 0 */
	/* lhi_c_001.main_8: Modified HI_ZERO to LHI_ZERO */
   LHI_ZERO((U8*)&mgt, sizeof(HiMngmt))
   
   CMCHKUNPKLOG(cmUnpkHeader,   &mgt.hdr, mBuf, ELHI229, pst);
   CMCHKUNPKLOG(cmUnpkCmStatus, &mgt.cfm, mBuf, ELHI230, pst);

   (Void)SPutMsg(mBuf);
   (*func)(pst, &mgt);

   RETVALUE(ROK);
} /* end of cmUnpkLhiCfgCfm */


/*
*
*       Fun:   Un-pack Control Request
*
*       Desc:  This function is used to un-pack the control request 
*              to layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  lhi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkLhiCntrlReq
(
LhiCntrlReq func,
Pst *pst,                 /* post structure */    
Buffer *mBuf              /* message buffer */
)
#else
PUBLIC S16 cmUnpkLhiCntrlReq(func, pst, mBuf)
LhiCntrlReq func;
Pst *pst;                 /* post structure */    
Buffer *mBuf;             /* message buffer */
#endif
{
   HiMngmt  mgt;          /* configuration */

   TRC3(cmUnpkLhiCntrlReq)

      /* lhi_c_001.main_11: Fix for Klockworks issue */
      cmMemset((U8 *)&mgt, 0, sizeof(HiMngmt));
   CMCHKUNPKLOG(cmUnpkHeader,   &mgt.hdr, mBuf, ELHI231, pst);
   CMCHKUNPKLOG(cmUnpkCmStatus, &mgt.cfm, mBuf, ELHI232, pst);

   CMCHKUNPKLOG(cmUnpkDateTime, &mgt.t.cntrl.dt,  mBuf, ELHI233, pst);
   CMCHKUNPKLOG(SUnpkU8, &mgt.t.cntrl.action,    mBuf, ELHI234, pst);
   CMCHKUNPKLOG(SUnpkU8, &mgt.t.cntrl.subAction, mBuf, ELHI235, pst);

   switch(mgt.hdr.elmId.elmnt) 
   {
      case STGEN:
         if(mgt.t.cntrl.subAction == SADBG)
         {
#ifdef DEBUGP
           CMCHKUNPKLOG(SUnpkU32, &(mgt.t.cntrl.ctlType.hiDbg.dbgMask), 
                        mBuf, ELHI236, pst);
#endif
         }   
#ifdef SS_DIAG 
         else if(mgt.t.cntrl.subAction == SALOG)
         {
           CMCHKUNPKLOG(SUnpkU32, &(mgt.t.cntrl.ctlType.logMask), 
                      mBuf, ERRLHI, pst);
         } 
#endif
         break;

      case STTSAP:
         if(mgt.t.cntrl.subAction == SAELMNT)
         {
            CMCHKUNPKLOG(cmUnpkSpId, &(mgt.t.cntrl.ctlType.sapId), mBuf, 
                         ELHI237, pst);
         }
         else if(mgt.t.cntrl.subAction == SATRC)
         {
            CMCHKUNPKLOG(SUnpkS16, &(mgt.t.cntrl.ctlType.trcDat.trcLen), 
                         mBuf, ELHI238, pst);
            CMCHKUNPKLOG(cmUnpkSpId, &(mgt.t.cntrl.ctlType.trcDat.sapId), 
                         mBuf, ELHI239, pst);
         }
         else
         {
#if (ERRCLASS & ERRCLS_DEBUG)
         LHILOGERROR(pst, ELHI240, mgt.t.cntrl.subAction, 
                     "cmUnpkLhiCntrlReq() : invalid subAction(STTSAP)"); 
#endif /* ERRCLS_DEBUG */
            (Void)SPutMsg(mBuf);
            RETVALUE(RFAILED);
         }
         break;

      case STGRTSAP:
         if(mgt.t.cntrl.subAction == SAGR_PRIORITY)
         {
            CMCHKUNPKLOG(cmUnpkPrior, &(mgt.t.cntrl.ctlType.priority), mBuf, 
                         ELHI241, pst);
         }
         else if(mgt.t.cntrl.subAction == SAGR_ROUTE)
         {
            CMCHKUNPKLOG(cmUnpkRoute, &(mgt.t.cntrl.ctlType.route), mBuf, 
                         ELHI242, pst);
         }
         else if(mgt.t.cntrl.subAction == SAGR_DSTPROCID)
         {
            CMCHKUNPKLOG(cmUnpkProcId, &(mgt.t.cntrl.ctlType.dstProcId), mBuf,
                         ELHI243, pst);
         }
         else
         {
#if (ERRCLASS & ERRCLS_DEBUG)
         LHILOGERROR(pst, ELHI244, mgt.t.cntrl.subAction, 
             "cmUnpkLhiCntrlReq () Failed : invalid subAction(STGRTSAP)"); 
#endif
            (Void)SPutMsg(mBuf);
            RETVALUE(RFAILED);
         }
         break;

      default:
#if (ERRCLASS & ERRCLS_DEBUG)
         LHILOGERROR(pst, ELHI245, mgt.hdr.elmId.elmnt, 
                     "cmUnpkLhiCntrlReq () Failed"); 
#endif
         (Void)SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }/* end of switch */

   (Void)SPutMsg(mBuf);
   (*func)(pst, &mgt);
   RETVALUE(ROK);
}


/*
*
*       Fun:   Un-pack Control Confirm
*
*       Desc:  This function is used to un-pack the control confirm 
*              to layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  lhi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkLhiCntrlCfm
(
LhiCntrlCfm func,
Pst *pst,                 /* post structure */    
Buffer *mBuf               /* message buffer */
)
#else
PUBLIC S16 cmUnpkLhiCntrlCfm(func, pst, mBuf)
LhiCntrlCfm func;
Pst *pst;                 /* post structure */    
Buffer *mBuf;              /* message buffer */
#endif
{
   HiMngmt  cfm;            /* configuration */
 
   TRC3(cmUnpkLhiCntrlCfm)

   CMCHKUNPKLOG(cmUnpkHeader,   &cfm.hdr, mBuf, ELHI246, pst);
   CMCHKUNPKLOG(cmUnpkCmStatus, &cfm.cfm, mBuf, ELHI247, pst);

   (Void)SPutMsg(mBuf);
   (*func)(pst, &cfm);
   RETVALUE(ROK);
} /* end of cmUnpkLhiCntrlCfm */


 
/*
*
*       Fun:   Un-pack Statistics Request
*
*       Desc:  This function is used to un-pack the statistics request
*              primitive to layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  lhi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkLhiStsReq
(
LhiStsReq func,
Pst *pst,                 /* post structure */    
Buffer *mBuf               /* message buffer */
)
#else
PUBLIC S16 cmUnpkLhiStsReq(func, pst, mBuf)
LhiStsReq func;
Pst *pst;                 /* post structure */    
Buffer *mBuf;              /* message buffer */
#endif
{
 
   HiMngmt  mgt;            /* configuration */
   /* lhi_c_001.main_11: Fix for Klockworks issue */
   Action   action = 0;         /* action type */

   TRC3(cmUnpkLhiStsReq)

      /* lhi_c_001.main_11: Fix for Klockworks issue */
      cmMemset((U8 *)&mgt, 0, sizeof(HiMngmt));
   CMCHKUNPKLOG(cmUnpkAction,   &action,  mBuf, ELHI248, pst);
   CMCHKUNPKLOG(cmUnpkHeader,   &mgt.hdr, mBuf, ELHI249, pst);
   CMCHKUNPKLOG(cmUnpkCmStatus, &mgt.cfm, mBuf, ELHI250, pst);

   switch(mgt.hdr.elmId.elmnt)
   {
      case STGEN:
        break;

/*lhi_c_004.main_1  1. modified statistics req to include messages
                              Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS
      case STHITHR:
        break;
#endif /*LHI_THR_STS*/

      case STTSAP:
      {
         CMCHKUNPKLOG(cmUnpkSpId, &mgt.t.sts.s.sapSts.sapId, mBuf, ELHI251, 
                      pst);
         break;
      }
      default:
#if (ERRCLASS & ERRCLS_DEBUG)
         LHILOGERROR(pst, ELHI252, mgt.hdr.elmId.elmnt, 
                     "cmUnpkLhiStsReq () Failed"); 
#endif
         (Void)SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }

   (Void)SPutMsg(mBuf);
   (*func)(pst, action, &mgt);
   RETVALUE(ROK);
} /* end of cmUnpkLhiStsReq */

/*lhi_c_004.main_1  1. modified statistics req to include messages
                              Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS
/*
*
*       Fun:   Un Pack connection Statistics
*
*       Desc:  This function is used to un pack the statistics confirm
*              primitive to layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  lhi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkHiConSts
(
HiConSts *sts,              /* statistics */
Buffer  *mBuf              /* to hold the packed buffer */
)
#else
PUBLIC S16 cmUnpkHiConSts(sts, mBuf)
HiConSts *sts;              /* statistics */
Buffer  *mBuf;             /* to hold the packed buffer */
#endif
{
   /*lhi_c_001.main_11: Added TRC macro for cmUnpkHiConSts()*/
   TRC3(cmUnpkHiConSts)
   CMCHKUNPK(cmUnpkStsCntr, &sts->numRxBytes, mBuf);

   CMCHKUNPK(cmUnpkStsCntr, &sts->numTxBytes, mBuf);
   RETVALUE(ROK);

}/*cmunPkHiConSts*/

/*
*
*       Fun:   Un Pack connection Statistics
*
*       Desc:  This function is used to un pack the statistics confirm
*              primitive to layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  lhi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkHiThrConSts
(
HiThrConSts *sts,              /* statistics */
Pst *pst,
Buffer  *mBuf              /* to hold the packed buffer */
)
#else
PUBLIC S16 cmUnpkHiThrConSts(sts, pst, mBuf)
HiThrConSts *sts;              /* statistics */
Pst *pst;
Buffer  *mBuf;             /* to hold the packed buffer */
#endif
{

   /* this will hold the temporary index value for number of threads */
   S16 iConIndex = 0;

   S16 retValue = ROK;

   /*lhi_c_001.main_11: Added TRC macro for cmUnpkHiThrConSts()*/
   TRC3(cmUnpkHiThrConSts)
      /* lhi_c_001.main_12: Replaced CMCHKPK with CMCHKPKLOG macro */
   CMCHKUNPKLOG(SUnpkU32, &sts->numCons, mBuf, ELHI644, pst);
  
   sts->conSts = NULLP;

   /* unpack only if Connections are present */
   if (sts->numCons)
   {
      if ( (retValue = SGetSBuf(pst->region, pst->pool, (Data** )&sts->conSts,
                               (sizeof(HiConSts) * sts->numCons))) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                   (ErrVal)ELHI253, (ErrVal)ERRZERO,
                   "cmUnpkLhiStsCfm: allocating memory for statistics confirm failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(retValue);
      }

      cmMemset( (U8* )sts->conSts, 0, (sizeof(HiConSts) * sts->numCons));

      /* in a loop unpack the statistics of all commands */
      for (iConIndex = sts->numCons - 1; iConIndex >= 0; iConIndex--)
      {
         /* lhi_c_001.main_12: Replaced CMCHKPK with CMCHKPKLOG macro */
         CMCHKUNPKLOG(cmUnpkHiConSts,  &sts->conSts[iConIndex], mBuf, ELHI645, pst);
      } 
   } 

   RETVALUE(ROK);
}/*cmunPkHiThrConSts*/

#endif /*LHI_THR_STS*/
 
/*
*
*       Fun:   Un-pack Statistics Confirm
*
*       Desc:  This function is used to un-pack the statistics confirm
*              primitive to layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  lhi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkLhiStsCfm
(
LhiStsCfm func,
Pst *pst,                 /* post structure */    
Buffer *mBuf               /* message buffer */
)
#else
PUBLIC S16 cmUnpkLhiStsCfm(func, pst, mBuf)
LhiStsCfm func;
Pst *pst;                 /* post structure */    
Buffer *mBuf;              /* message buffer */
#endif
{
 
   HiMngmt  mgt;            /* configuration */

   TRC3(cmUnpkLhiStsCfm)

      /* lhi_c_001.main_11: Fix for Klockworks issue */
      cmMemset((U8 *)&mgt, 0, sizeof(HiMngmt));
   CMCHKUNPKLOG(cmUnpkHeader,   &mgt.hdr, mBuf, ELHI254, pst);
   CMCHKUNPKLOG(cmUnpkCmStatus, &mgt.cfm, mBuf, ELHI255, pst);
   
   CMCHKUNPKLOG(cmUnpkDateTime, &mgt.t.sts.dt,   mBuf, ELHI256, pst);
   CMCHKUNPKLOG(cmUnpkDuration, &mgt.t.sts.dura, mBuf, ELHI257, pst);

   switch(mgt.hdr.elmId.elmnt)
   {
      case STGEN:
      {
         HiGenSts *gSts = &(mgt.t.sts.s.genSts);

         CMCHKUNPKLOG(cmUnpkStsCntr, &gSts->numCons,     mBuf, ELHI258, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &gSts->sockTxErr,   mBuf, ELHI259, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &gSts->sockRxErr,   mBuf, ELHI260, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &gSts->sockOpenErr, mBuf, ELHI261, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &gSts->sockBindErr, mBuf, ELHI262, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &gSts->sockCnctErr, mBuf, ELHI263, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &gSts->sockLstnErr, mBuf, ELHI264, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &gSts->sockSOptErr, mBuf, ELHI265, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &gSts->sockClosErr, mBuf, ELHI266, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &gSts->sockShutErr, mBuf, ELHI267, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &gSts->rxMsgVerErr, mBuf, ELHI268, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &gSts->numFlcInd,   mBuf, ELHI269, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &gSts->numTxTcpMsg, mBuf, ELHI270, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &gSts->numRxTcpMsg, mBuf, ELHI271, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &gSts->numTxUdpMsg, mBuf, ELHI272, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &gSts->numRxUdpMsg, mBuf, ELHI273, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &gSts->numTxbytes,  mBuf, ELHI274, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &gSts->numRxbytes,  mBuf, ELHI275, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &gSts->numTxRawMsg,  mBuf, ELHI276, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &gSts->numRxRawMsg,  mBuf, ELHI277, pst);
#ifdef HI_LKSCTP
         CMCHKUNPKLOG(cmUnpkStsCntr, &gSts->numTxSctpMsg,  mBuf, ELHI278, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &gSts->numRxSctpMsg,  mBuf, ELHI279, pst);
#endif
         break;
      }
      case STTSAP:
      {
         HiSapSts *sSts = &(mgt.t.sts.s.sapSts);

         CMCHKUNPKLOG(cmUnpkSpId,    &sSts->sapId,       mBuf, ELHI280, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &sSts->numCons,     mBuf, ELHI281, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &sSts->numTxTcpMsg, mBuf, ELHI282, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &sSts->numRxTcpMsg, mBuf, ELHI283, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &sSts->numTxUdpMsg, mBuf, ELHI284, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &sSts->numRxUdpMsg, mBuf, ELHI285, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &sSts->numTxbytes,  mBuf, ELHI286, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &sSts->numRxbytes,  mBuf, ELHI287, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &sSts->numTxRawMsg,  mBuf, ELHI288, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &sSts->numRxRawMsg,  mBuf, ELHI289, pst);
#ifdef HI_LKSCTP
         CMCHKUNPKLOG(cmUnpkStsCntr, &sSts->numTxSctpMsg,  mBuf, ELHI290, pst);
         CMCHKUNPKLOG(cmUnpkStsCntr, &sSts->numRxSctpMsg,  mBuf, ELHI291, pst);
#endif
         break;
      }
/*lhi_c_004.main_1  1. modified statistics req to include messages
                              Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS
      case STHITHR:
      {
         HiThrSts *tSts = &(mgt.t.sts.s.thrSts);
         /* this will hold the temporary index value for number of threads */
         S16 iThrIndex = 0;

         S16 retValue = ROK;

         /* lhi_c_001.main_12: Replaced CMCHKPK with CMCHKPKLOG macro */
         CMCHKUNPKLOG(SUnpkU32, &tSts->numRcvThrds, mBuf, ELHI646, pst);

         tSts->thrConSts = NULLP;

         /* unpack only if threads are present */
         if (tSts->numRcvThrds)
         {
            if ( (retValue = SGetSBuf(pst->region, pst->pool, (Data** )&tSts->thrConSts,
                                     (sizeof(HiThrConSts) * tSts->numRcvThrds))) != ROK)
            {
#if (ERRCLASS & ERRCLS_ADD_RES)
               SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                         (ErrVal)ELHI292, (ErrVal)ERRZERO,
                         "cmUnpkLhiStsCfm: allocating memory for statistics confirm failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
               RETVALUE(retValue);
            }

            cmMemset( (U8* )tSts->thrConSts, 0, (sizeof(HiThrConSts) * tSts->numRcvThrds));

            /* in a loop unpack the statistics of all commands */
            for (iThrIndex = tSts->numRcvThrds - 1; iThrIndex >= 0; iThrIndex--)
            {
               cmUnpkHiThrConSts(&tSts->thrConSts[iThrIndex],pst, mBuf);
            } 
         } 

        break;
      }
#endif /*LHI_THR_STS*/
      default:
#if (ERRCLASS & ERRCLS_DEBUG)
         LHILOGERROR(pst, ELHI293, mgt.hdr.elmId.elmnt, 
                     "cmUnpkLhiStsCfm () Failed"); 
#endif /* ERRCLS_DEBUG */
         (Void)SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }
   
   (Void)SPutMsg(mBuf);
   (*func)(pst, &mgt);
   RETVALUE(ROK);
}


/*
*
*       Fun:   Un-pack Status Request
*
*       Desc:  This function is used to un-pack the status request
*              primitive to layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  lhi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkLhiStaReq
(
LhiStaReq func,
Pst *pst,                 /* post structure */     
Buffer *mBuf               /* message buffer */
)
#else
PUBLIC S16 cmUnpkLhiStaReq(func, pst, mBuf)
LhiStaReq func;
Pst *pst;                 /* post structure */     
Buffer *mBuf;              /* message buffer */
#endif
{
   HiMngmt  mgt;            /* configuration */

   TRC3(cmUnpkLhiStaReq)

      /* lhi_c_001.main_11: Fix for Klockworks issue */
      cmMemset((U8 *)&mgt, 0, sizeof(HiMngmt));
   CMCHKUNPKLOG(cmUnpkHeader,   &mgt.hdr, mBuf, ELHI294, pst);
   CMCHKUNPKLOG(cmUnpkCmStatus, &mgt.cfm, mBuf, ELHI295, pst);
   
   switch(mgt.hdr.elmId.elmnt)
   {
      case STSID:
         break;
      case STTSAP:
         CMCHKUNPKLOG(cmUnpkSpId, &mgt.t.ssta.s.sapSta.spId, mBuf, 
                      ELHI296, pst);
         break;
      default:
#if (ERRCLASS & ERRCLS_DEBUG)
         LHILOGERROR(pst, ELHI297, mgt.hdr.elmId.elmnt, 
                     "cmUnpkLhiStaReq () Failed"); 
#endif /* ERRCLS_DEBUG */
         (Void)SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }

   (Void)SPutMsg(mBuf);
   (*func)(pst, &mgt);
   RETVALUE(ROK);
}


/*
*
*       Fun:   Un-pack Status Confirm
*
*       Desc:  This function is used to un-pack the status confirm
*              primitive to layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  lhi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkLhiStaCfm
(
LhiStaCfm func,
Pst *pst,                 /* post structure */     
Buffer *mBuf               /* message buffer */
)
#else
PUBLIC S16 cmUnpkLhiStaCfm(func, pst, mBuf)
LhiStaCfm func;
Pst *pst;                 /* post structure */     
Buffer *mBuf;              /* message buffer */
#endif
{
 
   HiMngmt  mgt;            /* configuration */
   Txt      ptNum[8];       /* part number */
    
   TRC3(cmUnpkLhiStaCfm)

      /* lhi_c_001.main_11: Fix for Klockworks issue */
      cmMemset((U8 *)&mgt, 0, sizeof(HiMngmt));
   CMCHKUNPKLOG(cmUnpkHeader,   &mgt.hdr, mBuf, ELHI298, pst);
   CMCHKUNPKLOG(cmUnpkCmStatus, &mgt.cfm, mBuf, ELHI299, pst);
   CMCHKUNPKLOG(cmUnpkDateTime, &mgt.t.ssta.dt, mBuf, ELHI300, pst);

   switch(mgt.hdr.elmId.elmnt)
   {
      case STSID:
      {
         mgt.t.ssta.s.sysId.ptNmb = ptNum;
         CMCHKUNPKLOG(cmUnpkSystemId, &(mgt.t.ssta.s.sysId), 
                      mBuf, ELHI301, pst);
         break;
      }
      case STTSAP:
      {
         HiSapSta *sSta = &(mgt.t.ssta.s.sapSta);

         CMCHKUNPKLOG(cmUnpkSpId,  &(sSta->spId),  mBuf, ELHI302, pst);
         CMCHKUNPKLOG(cmUnpkState, &(sSta->state), mBuf, ELHI303, pst);
/* hi009.104 - addition - unpacking self and remote interface version num */
#ifdef TDS_ROLL_UPGRADE_SUPPORT
         CMCHKUNPKLOG(SUnpkU8, &sSta->remIntfValid, mBuf, ELHI304, pst);
         CMCHKUNPKLOG(cmUnpkIntfVer, &sSta->selfIfVer, mBuf, ELHI305, pst);   
         CMCHKUNPKLOG(cmUnpkIntfVer, &sSta->remIfVer, mBuf, ELHI306, pst);
#endif /* TDS_ROLL_UPGRADE_SUPPORT */
         break;
      }
      default:
#if (ERRCLASS & ERRCLS_DEBUG)
         LHILOGERROR(pst, ELHI307, mgt.hdr.elmId.elmnt, 
                     "cmUnpkLhiStaReq () Failed"); 
#endif /* ERRCLS_DEBUG */
         (Void)SPutMsg(mBuf);
         RETVALUE(RFAILED);
   }

   (Void)SPutMsg(mBuf);
   (*func)(pst, &mgt);
   RETVALUE(ROK);
} /* end of cmUnpkLhiStaCfm */


/*
*
*       Fun:   Un-pack Status Indication
*
*       Desc:  This function is used to un-pack the status indication
*              primitive to the layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  lhi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkLhiStaInd
(
LhiStaInd func,
Pst *pst,                 /* post structure */
Buffer *mBuf               /* message buffer */
)
#else
PUBLIC S16 cmUnpkLhiStaInd(func, pst, mBuf)
LhiStaInd func;
Pst *pst;                 /* post structure */   
Buffer *mBuf;              /* message buffer */
#endif
{
 
   HiMngmt  mgt;            /* configuration */

   TRC3(cmUnpkLhiStaInd)

   CMCHKUNPKLOG(cmUnpkHeader,   &mgt.hdr, mBuf, ELHI308, pst);
   CMCHKUNPKLOG(cmUnpkCmStatus, &mgt.cfm, mBuf, ELHI309, pst);
   
   CMCHKUNPKLOG(cmUnpkCmAlarm, &mgt.t.usta.alarm,      mBuf, ELHI310, pst);
   CMCHKUNPKLOG(cmUnpkSpId,    &mgt.t.usta.info.spId,  mBuf, ELHI311, pst);
   CMCHKUNPKLOG(SUnpkU8,       &mgt.t.usta.info.type,  mBuf, ELHI312, pst);

   if(mgt.t.usta.info.type != LHI_ALARMINFO_TYPE_NTPRSNT)
   {
      switch(mgt.t.usta.info.type)
      {
         case LHI_ALARMINFO_SAP_STATE:
            CMCHKUNPKLOG(cmUnpkState, &mgt.t.usta.info.inf.state, 
                         mBuf, ELHI313, pst);
            break;

         case LHI_ALARMINFO_CON_STATE:
            CMCHKUNPKLOG(cmUnpkState, &mgt.t.usta.info.inf.conState, 
                       mBuf, ELHI314, pst);
            break;

         case LHI_ALARMINFO_MEM_ID:
            CMCHKUNPKLOG(cmUnpkPool, &mgt.t.usta.info.inf.mem.pool, mBuf, 
                       ELHI315, pst);
            CMCHKUNPKLOG(cmUnpkRegion, &mgt.t.usta.info.inf.mem.region, mBuf, 
                       ELHI316, pst);
            break;

         case LHI_ALARMINFO_PAR_TYPE:
            CMCHKUNPKLOG(SUnpkU8, &mgt.t.usta.info.inf.parType, mBuf, 
                       ELHI317, pst);
            break;

#ifdef HI_TLS
         case LHI_ALARMINFO_OSSL_ERR:
            CMCHKUNPKLOG(SUnpkS32, &mgt.t.usta.info.inf.osslError, mBuf,
                         ELHI318, pst);
            break;
#endif
            /*lhi_c_001.main_11:Added new usta.info.type and protected under
             * HI_LKSCTP flag */
#ifdef HI_LKSCTP
         case LHI_ALARMINFO_ASSOC_ERR:
            CMCHKPKLOG(SPkU32, mgt.t.usta.info.assocId, mBuf,
                  ELHI636, pst);
            CMCHKPKLOG(SPkU16, mgt.t.usta.info.error, mBuf,
                  ELHI635, pst);
            break;
#endif

         default:
#if (ERRCLASS & ERRCLS_DEBUG)
            LHILOGERROR(pst, ELHI319, mgt.t.usta.info.type, 
                        "cmUnpkLhiStaInd () Failed"); 
#endif /* ERRCLS_DEBUG */
            (Void)SPutMsg(mBuf);
            RETVALUE(RFAILED);
      }/* end of switch */
   }

   (Void)SPutMsg(mBuf);
   (*func)(pst, &mgt);
   RETVALUE(ROK);
} /* end of cmUnpkLhiStaInd */
 


/*
*
*       Fun:   Un-pack Trace Indication
*
*       Desc:  This function is used to un-pack the trace indication
*              primitive to layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  lhi.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkLhiTrcInd
(
LhiTrcInd func,
Pst *pst,                 /* post */
Buffer  *mBuf             /* message buffer */
)
#else
PUBLIC S16 cmUnpkLhiTrcInd(func, pst, mBuf)
LhiTrcInd func;
Pst *pst;                 /* post */
Buffer  *mBuf;            /* message buffer */
#endif
{
 
   HiMngmt  mgt;            /* configuration */

   TRC3(cmUnpkLhiTrcInd)

   CMCHKUNPKLOG(cmUnpkHeader,   &mgt.hdr, mBuf, ELHI320, pst);
   CMCHKUNPKLOG(cmUnpkCmStatus, &mgt.cfm, mBuf, ELHI321, pst);

   CMCHKUNPKLOG(cmUnpkDateTime, &mgt.t.trc.dt, mBuf, ELHI322, pst);
   CMCHKUNPKLOG(SUnpkU16, &mgt.t.trc.evnt, mBuf, ELHI323, pst);
   /*lhi_c_002.main_1 (hi023.104) */
	/* lhi_c_001.main_8: Removed warnings and removed hi.h included 
	 *                   header file */
#ifdef HI_ENB_SAP_TRC
   CMCHKUNPKLOG(SUnpkU16, (U16*)&mgt.t.trc.sap, mBuf, ELHI324, pst);
#endif

   (*func)(pst, &mgt, mBuf);
   RETVALUE(ROK);
} /* end of cmUnpkLhiTrcInd */

#endif /* LCLHI */

/********************************************************************30**
 
         End of file:     lhi.c@@/main/13 - Tue Apr 26 18:11:18 2011

*********************************************************************31*/
 
/********************************************************************40**
 
        Notes:
 
*********************************************************************41*/
 
/********************************************************************50**
 
*********************************************************************51*/
 
/********************************************************************60**
 
        Revision history:
 
*********************************************************************61*/
/********************************************************************70**
  
  version    initials                   description
-----------  ---------  ------------------------------------------------
 
*********************************************************************71*/
 
/********************************************************************80**
 
*********************************************************************81*/
/********************************************************************90**
 
    ver       pat     init                  description
----------- --------- ---- -----------------------------------------------
1.1         ---       asa  1. initial release.
1.1+        hi002.11  asa  1. numCons in HiGenCfg changed to U32.
                           2. added HiHdrInfo in HiSapCfg.
1.1+        hi003.11  asa  1. allocating memory before calling
                              cmUnpkSystemId().
/main/2     ---       cvp  1. added new parameters numFdsPerSet and  
                              numFdBins in HiGenCfg structure.
                           2. fixed bug in StsCfm primitive.
                           3. changed the copyright header.
            /main/4   sb   1. changes for Raw socket interface.added 
                              numRxRawMsg & numTxRawMsg.
/main/4+    hi005.13  cvp  1. Added new general configuration parameters
                              selTimeout, numUdpMsgsToRead, 
                              numUdpMsgsToRead and numClToAccept 
                              packing and unpacking functions. The flag
                              name that protect these changes is 
                              HI006_12. The flag name is kept to 
                              preserve backward compatibility with the
                              modifications in the earlier release.
/main/4     ---       cvp  1. Changed the copyright header.
                           2. Updated error codes.
/main/4     hi009.104 mmh  1. added Rolling Upgrade support
                              - call LHI_ZERO macro in cmUnpkLhiCfgReq()
                              - include header file hi.h and cm_lib.x for RUG
                              - in cmPkLhiCfgReq() added packing fields for
                                interface ver info.
                              - in cmPkLhiCfgReq() fill interface version 
                                number in pst.
                              - in cmPkLhiCntrlReq(), cmPkLhiStsReq(), 
                                cmPkLhiStaReq(), fill interface 
                                version number in pst.
                              - in cmPkLhiStaCfm() pcak self and remote 
                                interface version num.
                              - in cmUnpkLhiCfgReq(), cmUnpkLhiStaCfm() added
                                for unpacking fields for interface ver info.
                              - added init of mgt in cmUnpkLhiCfgCfm()
                           2. added the calls to pack/unpack the addr/port
                              to be used to bind generic sockets in functions
                              cmPkLhiCfgReq and cmUnpkLhiCfgReq under the
                              flag HI_SPECIFY_GENSOCK_ADDR
/main/1      ---       kp   1. Updated for release 1.5. Packing TLS
                              related options in configuration.
lhi_c_001.main_1       jc    1. Changed names of packing/unpacking macros
lhi_c_002.main_1       ss   1. Added sap id in trace 
lhi_c_003.main_1       ss   1. Made TLS method and verification depth as 
                               configurable parameter 
/main/1   lhi_c_004.main_1 svp  1. modified statistics req to include messages
                              Tx/Rx in bytes per con per thread 
/main/6      ---       hs   1. Updated for release of 2.1
/main/7   lhi_c_007.main_1 cs   1. Updated for the support of configurable RTO parameters, HBeat value,
                               Max retransmissions (Init, Path, Association)
/main/8   lhi_c_001.main_8 rss 1. Removed warnings and removed hi.h included 
                                  header file.
                               2.Modified HI_ZERO to LHI_ZERO 
/main/9   lhi_c_001.main_9 rcs 1. Instream and outstream parameters added in lsapcfg
/main/11     ---      lhi_c_001.main_10 rss 1.pack and unpack the region and pool id. 
/main/12     ---      lhi_c_001.main_11  ragrawal 1. Updated the varibale type to U32 from 
                                         U16 for variables rtoInitial, rtoMin, 
                                         rtoMax,cookieLife, intervalTm.
                                      2. Added TRC macro for cmUnpkHiThrConSts(),
                                         cmPkHiConSts(), cmPkHiThrConSts() and
                                         cmUnpkHiConSts().
                                      3. Added new usta.info.type and protected under
                                         HI_LKSCTP flag in cmUnpkLhiStaInd() and
                                         cmPkLhiStaInd() functions.
                                      4. Fix for Klockworks issues. 
/main/13 lhi_c_001.main_12 ragrawal 1. Replaced CMCHKPK with CMCHKPKLOG macro in 
                                       functions cmPkLhiCfgReq(), cmPkHiThrConSts,
                                       cmPkLhiStsCfm(), cmUnpkLhiCfgReq(),
                                       cmUnpkHiThrConSts(),cmUnpkLhiStsCfm().
*********************************************************************91*/
