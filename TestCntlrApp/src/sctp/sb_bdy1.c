

/********************************************************************20**

     Name:    SCTP Layer (SCTP)

     Type:    C source file

     Desc:    Code for Upper Interface and Management Interface
              primitives supplied by TRILLIUM

     File:    sb_bdy1.c

     Sid:      sb_bdy1.c@@/main/tenb_5.0_SIB_KNOWNSENSE/2 - Thu Nov 12 17:21:47 2015

     Prg:     asa

*********************************************************************21*/

/***********************************************************************

    Functions contained in sb_bdy1.c

    PUBLIC S16 sbActvInit(entity, inst, region, reason)
    PUBLIC S16 sbActvTmr()
    PUBLIC S16 sbTmrEvnt(cb, evnt)

    PUBLIC S16 SbMiLsbCfgReq(pst, cfg)
    PUBLIC S16 SbMiLsbCntrlReq(pst, cntrl)
    PUBLIC S16 SbMiLsbStaReq(pst, sta)
    PUBLIC S16 SbMiLsbStsReq(pst, action, sts)

    PUBLIC S16 SbUiSctBndReq(pst, suId, spId)
    PUBLIC S16 SbUiSctEndpOpenReq(pst, spId, suEndpId, port, intfNAddr)
    PUBLIC S16 SbUiSctEndpCloseReq(pst, spId, endpId, endpIdType)
    PUBLIC S16 SbUiSctAssocReq(pst, spId, spEndpId, suAssocId, priDstNAddr,
    PUBLIC S16 SbUiSctAssocRsp(pst, spId, suId, spEndpId, assocIndParams,
                               result)
    PUBLIC S16 SbUiSctTermReq(pst, spId, assocId, assocIdType, abortFlg)
    PUBLIC S16 SbUiSctSetPriReq(pst, spId, spAssocId, dstNAddr)
    PUBLIC S16 SbUiSctHBeatReq(pst, spId, spAssocId, dstNAddr, intervalTime,
                               status)
    PUBLIC S16 SbUiSctDatReq(pst, spId, spAssocId, dstNAddr, strmId,
                             unorderFlg, nobundleFlg, lifeTime, protId, mBuf)
    PUBLIC S16 SbUiSctStaReq(pst, spId, spAssocId, dstNAddr, staType)

    PUBLIC S16 SbLiHitConCfm(pst, suId, cntrl, suConId, spConId, localAddr)
    * Patch sb031.102 IPV6 Support Added *
    PUBLIC S16 SbLiHitUDatInd(pst, suId, suConId, srcAddr, dstAddr, hdrParm,
#ifdef LOCAL_INTF
                              localIf, 
#endif
                              mBuf)
    PUBLIC S16 SbLiHitDiscInd(pst, suId, choice, conId, reason)
    PUBLIC S16 SbLiHitDiscCfm(pst, suId, choice, conId, action)
    PUBLIC S16 SbLiHitConInd(pst, suId, servConId, spConId, peerAddr)
    PUBLIC S16 SbLiHitFlcInd(pst, suId, reason)
    PUBLIC S16 SbLiHitDatInd(pst, suId, suConId, mBuf)
    PUBLIC S16 SbLiHitBndCfm(pst, suId, status)

***********************************************************************/


/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_hash.h"       /* common hashing */
#include "cm_llist.h"      /* common linked list */
#include "cm5.h"           /* common timer */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"        /* Common DNS library */
#ifdef SB_FTHA
#include "sht.h"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "lsb.h"           /* layer management, SCTP  */
#include "sct.h"           /* SCT interface */
#include "hit.h"           /* HIT interface */
#include "sb_port.h"
#include "sb_mtu.h"
#include "sb.h"            /* SCTP internal defines */
#include "sb_err.h"        /* SCTP error */

/* header/extern include files (.x) */

#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_hash.x"       /* common hashing */
#include "cm_llist.x"      /* common linked list */
#include "cm_lib.x"        /* common library */
#include "cm5.x"           /* common timer */
#include "cm_tpt.x"        /* common transport */
#include "cm_dns.x"        /* Common DNS library */
#ifdef SB_FTHA
#include "sht.x"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "sct.x"           /* SCT interface */
#include "lsb.x"           /* layer management SCTP */
#include "hit.x"           /* HIT interface */
#include "sb_port.x"
#include "sb_mtu.x"
#include "sb.x"            /* SCTP internal typedefs */

/* Public variable declarations */
#ifdef SS_MULTIPLE_PROCS
PUBLIC SbGlobalCb sbGlobalCbLst[SB_MAX_INSTANCES];
PUBLIC SbGlobalCb *sbGlobalCbPtr;
#else
PUBLIC SbGlobalCb  sbGlobalCb;  /* SCTP control block */
#endif /* SS_MULTIPLE_PROCS */

/*sb009.103: SOL10 change: function prototypes */
#ifdef SB_SOL10_MULTIPORT
PRIVATE Void sbEndpOpenCleanup ARGS((SbSctEndpCb *endpCb, U8 nmb));
#endif

/* functions */

/* ------------------------------------------------------------------*/
/* Interface Functions to System Services
 */

/*
*
*      Fun:   Activate Task - initialize
*
*      Desc:  Invoked by system services to initialize a task.
*
*      Ret:   ROK
*
*      Notes: None
*
*      File:  sb_bdy1.c
*
*/

#ifdef SS_MULTIPLE_PROCS
#ifdef ANSI
PUBLIC S16 sbActvInit
(
ProcId  proc,           /* procId */
Ent     entity,         /* entity */
Inst    inst,           /* instance */
Region  region,         /* region */
Reason  reason,         /* reason */
Void    **xxCb          /* protocol control block */
)
#else  
PUBLIC S16 sbActvInit(proc, entity, inst, region, reason, xxCb)
ProcId  proc;           /* procId */
Ent     entity;         /* entity */
Inst    inst;           /* instance */
Region  region;         /* region */
Reason  reason;         /* reason */
Void    **xxCb;         /* protocol control block */
#endif
#else  /* SS_MULTIPLE_PROCS */
#ifdef ANSI
PUBLIC S16 sbActvInit
(
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason          /* reason */
)
#else
PUBLIC S16 sbActvInit(entity, inst, region, reason)
Ent entity;            /* entity */
Inst inst;             /* instance */
Region region;         /* region */
Reason reason;         /* reason */
#endif
#endif  /* SS_MULTIPLE_PROCS */
{
   /* local variables */
#ifdef SS_MULTIPLE_PROCS
   U16 i = 0;
   /*sb085.102: changes for de-registration of TAPA task  */
   /*sb087.102: correction of typo*/
   static Bool sbFirstCall = FALSE;
#endif /* SS_MULTIPLE_PROCS */
   U8                idx;
 
   TRC2(sbActvInit)

#ifdef SS_MULTIPLE_PROCS

   /*sb085.102: changes for de-registration of TAPA task*/
   if(reason == SHUTDOWN)
   {
      sbGlobalCbPtr->used = TRUE;
   }
   else if(reason == NRM_TERM)
   {
      sbGlobalCbPtr->used = FALSE;
      RETVALUE(ROK);
   }
   else
   {
      if (!sbFirstCall)
      {
         sbFirstCall = TRUE;
         for(i=0;i<SB_MAX_INSTANCES;i++)
         {
            SB_ZERO((Data *)&sbGlobalCbLst[i],(S32)sizeof(SbGlobalCb));
         }
         idx = 0;
      }
      else
      {

         for(i=0;i<SB_MAX_INSTANCES;i++)
         {
            if(sbGlobalCbLst[i].used == FALSE)
            {
               sbGlobalCbPtr = &sbGlobalCbLst[i];
               idx = i;
               break;
            }
         }
      }

      if(idx==SB_MAX_INSTANCES)
         RETVALUE(FALSE);

         sbGlobalCbPtr = &sbGlobalCbLst[idx];
         *xxCb = (void *)&sbGlobalCbLst[idx];
         sbGlobalCbPtr->used = TRUE;

   }

#endif /*SS_MULTIPLE_PROCS*/

   SBDBGP(DBGMASK_SI, (sbGlobalCb.sbInit.prntBuf,
          "sbActvInit(Ent(%d), Inst(%d), Region(%d), Reason(%d))\n",
           entity, inst, region, reason));

   /* Initialize the SCTP control block */

   SB_ZERO(&sbGlobalCb, sizeof(sbGlobalCb));

   sbGlobalCb.sbInit.ent = entity;
   sbGlobalCb.sbInit.inst = inst;
   sbGlobalCb.sbInit.region = region;
   sbGlobalCb.sbInit.reason = reason;
   sbGlobalCb.sbInit.cfgDone = FALSE;

   /* Pool Id is obtained after SGetSMem in general configuration */
   sbGlobalCb.sbInit.pool = 0;

#ifndef SS_MULTIPLE_PROCS
   sbGlobalCb.sbInit.procId = SFndProcId();
#else
   sbGlobalCb.sbInit.procId = proc;
#endif /*SS_MULTIPLE_PROCS*/

   sbGlobalCb.sbInit.acnt = FALSE;
   sbGlobalCb.sbInit.usta = TRUE;
   sbGlobalCb.sbInit.trc = FALSE;

   /* Initialize timing queue */
   sbGlobalCb.sbTqCp.nxtEnt = 0;
   sbGlobalCb.sbTqCp.tmrLen = SB_TQSIZE;

   for (idx = 0; idx < SB_TQSIZE; idx++)
   {
      sbGlobalCb.sbTq[idx].first = NULLP;
   }

#ifdef DEBUGP
/* sb018.102 dbgMask initialized to 0 */
   sbGlobalCb.sbInit.dbgMask = 0x0;
#endif /* DEBUGP */

/* sb048.102 dbgMask initialized to ffffffff *
 * if the code is compiled with SB_DEBUGP    */
#ifdef DEBUGP
#ifdef SB_DEBUGP
   sbGlobalCb.sbInit.dbgMask = 0xffffffff;
#endif /* SB_DEBUGP */
#endif /* DEBUGP */

#ifdef SS_DIAG
   sbGlobalCb.sbInit.logMask = 0x0;
#endif
/* sb012.103: Assigning GetHostByName function */
   sbGlobalCb.funcGetHostByName =cmInetGetHostByName;

   /* sbInit.lmPst is initialised in general configuration */
   /* perform external initialization, if needed */
   sbInitExt();

   RETVALUE(ROK);
}/* end of sbActvInit */

/*
*
*       Fun:   Activate Task - timer
*
*       Desc:  Invoked by system services to activate a task with
*              a timer tick.
*
*       Ret:   ROK      - ok
*
*       Notes: <none>
*
*       File:  sb_bdy1.c
*
*/
#ifdef SS_MULTIPLE_PROCS
#ifdef ANSI
PUBLIC S16 sbActvTmr
(
ProcId proc,
Ent    ent,
Inst   inst
)
#else
PUBLIC S16 sbActvTmr(proc, ent, inst)
ProcId proc;
Ent    ent;
Inst   inst;
#endif
#else  /* SS_MULTIPLE_PROCS */
#ifdef ANSI
PUBLIC S16 sbActvTmr
(
Void
)
#else
PUBLIC S16 sbActvTmr()
#endif
#endif  /* SS_MULTIPLE_PROCS */
{
   TRC2(sbActvTmr)
#ifdef SS_MULTIPLE_PROCS

   if(SGetXxCb(proc, ent, inst, (void **)&sbGlobalCbPtr) != ROK)
   {
     SBLOGERROR(ERRCLS_DEBUG, ESB001, 0,
               "sbActvTmr () failed, cannot derive sbCbPtr");
     RETVALUE(FALSE);
   }

   SBDBGP(DBGMASK_SI, (sbGlobalCb.sbInit.prntBuf,
         "-------SCTP------(proc(%d), ent(%d), inst(%d))--------\n",
         proc, ent, inst));

#endif /* SS_MULTIPLE_PROCS */

   cmPrcTmr(&sbGlobalCb.sbTqCp, sbGlobalCb.sbTq, (PFV)sbTmrEvnt);

   RETVALUE(ROK);
}


/*
*
*       Fun:   sbTmrEvnt
*
*       Desc:  This function is used to process the expiry of SCTP
*              timer events.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: <none>
*
*       File:  sb_bdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 sbTmrEvnt
(
PTR  cb,                  /* control block */
S16 evnt                  /* timer number */
)
#else
PUBLIC S16 sbTmrEvnt(cb, evnt)
PTR  cb;                  /* control block */
S16 evnt;                 /* timer number */
#endif
{
   S16 err;

   TRC2(sbTmrEvnt);

   SBDBGP(SB_DBGMASK_GEN, (sbGlobalCb.sbInit.prntBuf,\
          "sbTmrEvnt(Evnt(%d))\n", evnt));

   err = ROK;

   /* sb064.102 : Remove compiler warnings */

   switch (evnt)
   {
      case SB_TMR_LIFETIME:
         err = sbSqLifetimeTO((SbQueuedChunk *)cb);
         break;
      case SB_TMR_T3RTX:
         err = sbAcRTO((SbAddrCb *)cb);
         break;
      case SB_TMR_ACKDELAY:
         err = sbAcSackTO((SbSctAssocCb  *)cb);
         break;
      case SB_TMR_SHUTDOWN:
         err = sbAsSDownTO((SbSctAssocCb *)cb);
         break;
      case SB_TMR_INIT:
         err = sbAsInitTO((SbSctAssocCb *)cb);
         break;
      case SB_TMR_COOKIE:
         err = sbAsCookieTO((SbSctAssocCb *)cb);
         break;
      case SB_TMR_HBEAT:
         err = sbPmHBeatTO((SbAddrCb *)cb);
         break;
      case SB_TMR_KEY:
         err = sbAsKeyTO();
         break;
      case SB_TMR_TSAP_BND:
         err = sbLiBndTO((SbTSapCb *)cb);
         break;
      case SB_TMR_FREEZE:
         err = sbAsFreezeTO((SbSctAssocCb *)cb);
         break;
      case SB_TMR_MTU_INC:
         err = sbMtuIncMtu((SbMtuCp *)cb);
         SB_START_TMR(&(sbGlobalCb.mtuIncTmr),  &(sbGlobalCb.mtuCp),
                      SB_TMR_MTU_INC, SB_MTU_INC_MTU)
         break;
      case SB_TMR_MTU_INC_UP:
         err = sbMtuIncMtuUpper((SbMtuCp *)cb);
         SB_START_TMR(&(sbGlobalCb.mtuIncTmrUp),  &(sbGlobalCb.mtuCp),
                      SB_TMR_MTU_INC_UP, SB_MTU_INC_MTU_UPPER)
         break;

      case SB_TMR_SHUTDOWNACK:
         err = sbAsSDownAckTO((SbSctAssocCb *)cb);
         break;
      
      case SB_TMR_AWT_DNS_RSP:
         err = sbAsDnsRspTO((SbSctAssocCb *)cb);
         break;

     /* sb054.102 : Addition - Bundling Changes */
#ifdef LSB4
      case SB_TMR_BUNDLE:
         err = sbAsBundleTO((SbSctAssocCb *)cb);
         break;
#endif
      /* RFC 4460 */
      case SB_TMR_SDOWNGUARD:
         err = sbAsSdownGuardTO((SbSctAssocCb *)cb);
         break;
/* sb009.103: SOL10 changes: Addedd Endp Open timer */
#ifdef SB_SOL10_MULTIPORT
      case SB_TMR_ENDP_OPEN:
         err = sbEndpOpenTO((SbSctEndpCb *)cb);
         break;
#endif

      default:

#if (ERRCLASS & ERRCLS_DEBUG)

         SBLOGERROR( ERRCLS_DEBUG,
                     ESB002,
                     (ErrVal) 0,
                     "sbTmrEvnt(): Invalid timer event" );

         RETVALUE( RFAILED );

#endif /* ERRRCLS_DEBUG */

         break;
   }

#if (ERRCLASS & ERRCLS_DEBUG)

   if (err != ROK)
   {
      SBLOGERROR( ERRCLS_DEBUG,
                  ESB003,
                  (ErrVal) evnt,
                  "sbTmrEvnt(): Timer function call failed" );

      RETVALUE( RFAILED );
   }

#endif /* ERRRCLS_DEBUG */


   RETVALUE(ROK);
}/* end of  sbTmrEvnt() */


/****************************************************************************/
/*  Layer Management interface LSB primitives                               */
/****************************************************************************/

/*
*
*       Fun:   SbMiLsbCfgReq
*
*       Desc:  This function is used by the Layer Management to
*              configure the layer. The SCTP layer responds with a
*              Configuration Confirm to the layer manager. This primitive
*              can also be used to reconfigure the layer.
*
*       Ret:   Success: ROK
*              Failure: RFAILED
*
*       Notes: Configuration must be performed in the following
*              sequence:
*              1) general configuration (STGEN);
*              2) sap configuration (STSCTSAP and/or STTSAP).
*
*       File:  sb_bdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 SbMiLsbCfgReq
(
Pst     *pst,                /* post structure */
SbMgmt  *cfg                 /* configuration structure */
)
#else
PUBLIC S16 SbMiLsbCfgReq(pst, cfg)
Pst     *pst;                /* post structure */
SbMgmt  *cfg;                /* configuration structure */
#endif
{
   Header      *hdr;               /* Header structure */
   SbMgmt      cfmMsg;             /* configuration confirm */
   S16         ret;                /* return code */

   TRC3(SbMiLsbCfgReq)

#ifdef SS_MULTIPLE_PROCS

   if(SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                          (void **)&sbGlobalCbPtr) != ROK)
   {
     SBLOGERROR(ERRCLS_DEBUG, ESB004, 0,
               "SbMiLsbCfgReq() failed, cannot derive sbGlobalCbPtr");
     RETVALUE(FALSE);
   }

   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
         "-------SCTP------(proc(%d), ent(%d), inst(%d))--------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));

#endif /* SS_MULTIPLE_PROCS */

   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
          "SbMiLsbCfgReq(pst, elmnt(%d))\n", cfg->hdr.elmId.elmnt));

   /* obtain the header structure from the configuration */
   hdr = &(cfg->hdr);

   /* zero out the confirm structure */
   SB_ZERO(&cfmMsg, sizeof(SbMgmt));

   /* Check if general configuration has been done */
   if ( (hdr->elmId.elmnt != STSBGEN) &&
        (sbGlobalCb.sbInit.cfgDone == FALSE) )
   {
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
             "SbMiLsbCfgReq: general configuration not done yet\n"));

      sbLmSendCfm(pst, TCFG, hdr, LCM_PRIM_NOK, LCM_REASON_GENCFG_NOT_DONE,
                  &cfmMsg);
      RETVALUE(RFAILED);
   }

   /* Check if currently busy servicing a layer manager request */
   if ( sbGlobalCb.sbMgmt.hdr.elmId.elmnt != 0 )
   {
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
             "SbMiLsbCfgReq: currently servicing a layer manager request\n"));

      sbLmSendCfm(pst, TCFG, hdr, LCM_PRIM_NOK, LSB_REASON_LMI_BUSY,
                  &cfmMsg);
      RETVALUE(RFAILED);
   }

   /* choose the element (ie. which type of configuration) */
   switch (hdr->elmId.elmnt)
   {
      case STSBGEN:               /* general configuration */
         ret = sbCfgGen(&cfg->t.cfg.s.genCfg);
         break;

      case STSBSCTSAP:              /* upper SCT SAP configuration */
         ret = sbCfgSctSap(&cfg->t.cfg.s.sctSapCfg);
         break;

      case STSBTSAP:                /* transport SAP configuration */
         ret = sbCfgTSap(cfg);
         break;

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
      case STSBPATHPROF:              /* Path Profile configuration */
         ret = sbCfgPathProf(&cfg->t.cfg.s.pathProfCfg);
         break;

      case STSBDSTADDR:                /* Destination Address configuration */
         ret = sbCfgDstAddr(&cfg->t.cfg.s.dstAddrCfg);
         break;
#endif /* SB_SATELLITE */

      default:                  /* invalid */
#if (ERRCLASS & ERRCLS_INT_PAR)
         SBLOGERROR(ERRCLS_INT_PAR, ESB005, (ErrVal) hdr->elmId.elmnt,
                    "SbMiLsbCfgReq: Bad Element in control request");
#endif
         ret = LCM_REASON_INVALID_ELMNT;
         break;

   }

   /* In normal cases, LCM_REASON_NOT_APPL is returned, in all error
    * cases appropriate reason is returned by the above functions */

   /* send the layer manager confirm */
   if (ret != LCM_REASON_NOT_APPL)
   {
      sbLmSendCfm(pst, TCFG, hdr, LCM_PRIM_NOK, ret,
                  &cfmMsg);
      RETVALUE(RFAILED);
   }

   sbLmSendCfm(pst, TCFG, hdr, LCM_PRIM_OK, LCM_REASON_NOT_APPL,
               &cfmMsg);
   RETVALUE(ROK);
} /* end of SbMiLsbCfgReq() */

/*
*
*       Fun:   Control Request Primitive
*
*       Desc:  This primitive is used to control the specified element.
*              It can be used to enable or disable the general elements
*              (trace, alarm and debug prints.)
*              It can also be used to: delete or disable a SAP or a group of
*              SAPs; bind or enable a SAP or group of SAPs or
*              Shutdown all the operations.
*              A control confirm is sent to acknowledge the request
*
*       Ret:   Success:       ROK
*              Failure:       RFAILED
*
*       Notes: <none>
*
*       File:  sb_bdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 SbMiLsbCntrlReq
(
Pst    *pst,                   /* post structure */
SbMgmt *cntrl                  /* pointer to control structure */
)
#else
PUBLIC S16 SbMiLsbCntrlReq(pst, cntrl)
Pst    *pst;                   /* post structure */
SbMgmt *cntrl;                 /* pointer to control structure */
#endif
{
   Header      *hdr;                /* Header structure */
   /* sb004.12 - Change - cfmMsg is taken as Pointer to minimise stack memory */
   SbMgmt      *cfmMsg;             /* configuration confirm */
   S16          ret;                /* return code */
   SbTSapCb    *tSap;

   TRC3(SbMiLsbCntrlReq)

#ifdef SS_MULTIPLE_PROCS

   if(SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                         (void **)&sbGlobalCbPtr) != ROK)
   {
     SBLOGERROR(ERRCLS_DEBUG, ESB006, 0,
               "SbMiLsbCntrlReq() failed, cannot derive sbGlobalCbPtr");
     RETVALUE(FALSE);
   }

   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
         "-------SCTP------(proc(%d), ent(%d), inst(%d))--------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));

#endif /* SS_MULTIPLE_PROCS */

   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
          "SbMiLsbCntrlReq(pst, elmnt(%d))\n", cntrl->hdr.elmId.elmnt));

#ifndef SS_MULTIPLE_PROCS
   UNUSED(pst);
#endif

   /* obtain the header structure from the configuration */
   hdr = &(cntrl->hdr);

    /* sb004.12 - Addition : Allocate memory for Response msg  */
    SB_ALLOC(sizeof(SbMgmt), cfmMsg, ret);
    if ( ret != ROK )
    {
        SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
               "SbMiLsbCntrlReq: could not allocate memory for Response Structure\n"));
        RETVALUE(RFAILED);
     }

   /* sb004.12 - Change : cfmMsg is already a pointer */
   /* zero out the confirm structure */
   SB_ZERO(cfmMsg, sizeof(SbMgmt));

   /* set the current time */
   (Void) SGetDateTime(&(cfmMsg->t.cntrl.dt));

   /* Check if configuration has been done */
   if ( (sbGlobalCb.sbInit.cfgDone == FALSE) && (hdr->elmId.elmnt != STSBGEN) )
   {
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
             "SbMiLsbCntrlReq: general configuration not done yet\n"));

      sbLmSendCfm(pst, TCNTRL, hdr, LCM_PRIM_NOK, LCM_REASON_GENCFG_NOT_DONE,
                  cfmMsg);
      /* sb004.12 - Addition : deallocate cfmMsg structure */
      SB_FREE(sizeof(SbMgmt), cfmMsg);
      RETVALUE(RFAILED);
   }

   /* Check if currently busy servicing a layer manager request */
   if ( sbGlobalCb.sbMgmt.hdr.elmId.elmnt != 0 )
   {
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
             "SbMiLsbCntrlReq: currently servicing a layer manager request\n"));

      sbLmSendCfm(pst, TCNTRL, hdr, LCM_PRIM_NOK, LSB_REASON_LMI_BUSY,
                  cfmMsg);
      /* sb004.12 - Addition : deallocate cfmMsg structure */
      SB_FREE(sizeof(SbMgmt), cfmMsg);
      RETVALUE(RFAILED);
   }

   /* check element */
   switch(hdr->elmId.elmnt)
   {
      case STSBGEN:                               /* General control */
         ret = sbCntrlGen(cntrl);
         break;

      case STSBSCTSAP:
         ret = sbCntrlSctSap(cntrl);             /* SCT SAP control */
         break;

      case STSBTSAP:                              /* Transport SAP control */
         if ( cntrl->t.cntrl.action == ABND_ENA )
         {
            /* set the current time for when the bind request was received */
            (Void) SGetDateTime(&(cntrl->t.cntrl.dt));

            /* Store current Management structure */
            (Void) cmMemcpy((U8 *) &(sbGlobalCb.sbMgmt), (U8 *) cntrl,
                           (PTR) sizeof(SbMgmt));
         }
/* sb003.103: Moved from GenCfg to General reConfig structure */ 
/* sb004.103: Protected under compile-time flag */
#ifdef LSB9
         cmMemcpy((U8 *)&(sbGlobalCb.genCfg.reConfig.smPst), (U8 *)pst, sizeof(Pst));
#else
         cmMemcpy((U8 *)&(sbGlobalCb.genCfg.smPst), (U8 *)pst, sizeof(Pst));
#endif
         ret = sbCntrlTSap(cntrl);
         break;

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
      case STSBPATHPROF:              /* Path Profile control */
         ret = sbCntrlPathProf(cntrl);
         break;

      case STSBDSTADDR:                /* Destination Address control */
         ret = sbCntrlDstAddr(cntrl);
         break;
#endif /* SB_SATELLITE */

      default:
#if (ERRCLASS & ERRCLS_DEBUG)
         SBLOGERROR(ERRCLS_DEBUG, ESB007, (ErrVal) hdr->elmId.elmnt,
                    "SbMiLsbCntrlReq: Bad Element in control request");
         /* element must be one of the above */
#endif
         ret = LCM_REASON_INVALID_ELMNT;
         break;
   } /* end switch */

   /* In normal cases, LCM_REASON_NOT_APPL is returned, in all error
    * cases appropriate reason is returned by the above functions */

   /* send the layer manager confirm */
   if (ret != LCM_REASON_NOT_APPL)
   {
      SB_ZERO( &(sbGlobalCb.sbMgmt), sizeof(SbMgmt) );
      sbLmSendCfm(pst, TCNTRL, hdr, LCM_PRIM_NOK, ret, cfmMsg);
      /* sb004.12 - Addition : deallocate cfmMsg structure */
      SB_FREE(sizeof(SbMgmt), cfmMsg);
      RETVALUE(RFAILED);
   }

   /* we need to store the sbMgmt struct if binding a TSAP */
   /* the confirm is also slightly different */
   if ( (hdr->elmId.elmnt == STSBTSAP) && (cntrl->t.cntrl.action == ABND_ENA) )
   {
      tSap = sbGlobalCb.tSaps[cntrl->t.cntrl.sapId];
      if (tSap->sapState != SB_SAPSTATE_BND)
      {
         sbLmSendCfm(pst, TCNTRL, hdr, LCM_PRIM_OK_NDONE, LCM_REASON_NOT_APPL,
                     cfmMsg);
      }
      /* sb004.12 - Addition : deallocate cfmMsg structure */
      SB_FREE(sizeof(SbMgmt), cfmMsg);
      RETVALUE(ROK);
   }

   sbLmSendCfm(pst, TCNTRL, hdr, LCM_PRIM_OK, LCM_REASON_NOT_APPL,
               cfmMsg);
  
   /* sb004.12 - Addition : deallocate cfmMsg structure */
   SB_FREE(sizeof(SbMgmt), cfmMsg);

   RETVALUE(ROK);
}/* end of SbMiLsbCntrlReq() */



/* ------------------------------------------------------------------*
 * Interface Functions for SHT Interface                           *
 * ------------------------------------------------------------------*/

/* sb042.102 - Added change for SHT interface and Rolling Up Grade */
#ifdef SB_FTHA  

/*
*
*       Fun  :  System agent control Request 
*
*       Desc :  Processes system agent control request primitive
*
*       Ret  :  ROK  - ok
*
*       Notes:  <None>
*
*       File :  sb_bdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 SbMiShtCntrlReq
(
Pst               *pst,       /* post structure          */
ShtCntrlReqEvnt   *reqInfo    /* system agent control request event */
)
#else
PUBLIC S16 SbMiShtCntrlReq(pst, reqInfo)
Pst               *pst;       /* post structure          */
ShtCntrlReqEvnt   *reqInfo;   /* system agent control request event */
#endif
{
   Pst               repPst;  /* reply post structure */
   ShtCntrlCfmEvnt   cfmInfo; /* system agent control confirm event */
   SbSctSapCb        *sctSap; /* SCT Sap control Block */
   SbTSapCb          *tSap;   /* TSap control Block */
   S16               i;

   TRC3(SbMiShtCntrlReq)

#ifdef SS_MULTIPLE_PROCS

   if(SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                          (void **)&sbGlobalCbPtr) != ROK)
   {
     SBLOGERROR(ERRCLS_DEBUG, ESB008, 0,
               "SbMiShtCntrlReq () failed, cannot derive sbGlobalCbPtr");
     RETVALUE(FALSE);
   }

   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
         "-------SCTP------(proc(%d), ent(%d), inst(%d))--------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));

#endif /* SS_MULTIPLE_PROCS */

   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf, "SbMiShtCntrlReq at SHT "
     "interface \n"));

   /* fill reply pst structure */
   repPst.dstProcId = pst->srcProcId;
   repPst.dstEnt    = pst->srcEnt;
   repPst.dstInst   = pst->srcInst;
   repPst.prior     = reqInfo->hdr.response.prior;
   repPst.route     = reqInfo->hdr.response.route;
   repPst.selector  = reqInfo->hdr.response.selector;
   repPst.event     = EVTNONE;
   repPst.srcProcId = sbGlobalCb.sbInit.procId;
   repPst.srcEnt    = ENTSB;
   repPst.srcInst   = sbGlobalCb.sbInit.inst;
   repPst.region    = reqInfo->hdr.response.mem.region; 
   repPst.pool      = reqInfo->hdr.response.mem.pool; 

   /* fill reply transaction Id */
   cfmInfo.transId = reqInfo->hdr.transId;

#ifdef SB_RUG
   cfmInfo.reqType = reqInfo->reqType;
#endif 

   /* check if general configuration done */
   if (sbGlobalCb.sbInit.cfgDone != TRUE)
   {
      cfmInfo.status.status = LCM_PRIM_NOK;
      cfmInfo.status.reason = LCM_REASON_GENCFG_NOT_DONE;

      SbMiShtCntrlCfm(&repPst, &cfmInfo);
      RETVALUE(ROK); 
   }

   /* fill status value */
   cfmInfo.status.reason = LCM_REASON_NOT_APPL;
/* sb003.103: Moved from GenCfg to General reConfig structure */ 
/* sb004.103: Protected under compile-time flag */
#ifdef LSB9
   sbGlobalCb.genCfg.reConfig.smPst.srcEnt = ENTSM;
   /* sb023.103: Assign correct value to smPst */
   sbGlobalCb.genCfg.reConfig.smPst.srcInst = sbGlobalCb.sbInit.lmPst.dstInst;
   sbGlobalCb.genCfg.reConfig.smPst.srcProcId = sbGlobalCb.sbInit.lmPst.dstProcId;
#else
   sbGlobalCb.genCfg.smPst.srcEnt = ENTSM;
    /* sb023.103: Assign correct value to smPst */
   sbGlobalCb.genCfg.smPst.srcInst = sbGlobalCb.sbInit.lmPst.dstInst;
   sbGlobalCb.genCfg.smPst.srcProcId = sbGlobalCb.sbInit.lmPst.dstProcId;
#endif

   switch (reqInfo->reqType)
   {
      case SHT_REQTYPE_BND_ENA:   /* system agent control bind enable */
         switch (reqInfo->s.bndEna.grpType)
         {
            case SHT_GRPTYPE_ALL:
               /* 
                * go through all the sap control blocks and start bind  
                * enable procedure on those SAPs for which              
                * (tPst->dstProcId == reqInfo->s.bndEna.dstProcId) && 
                * (tPst->dstEnt == reqInfo->s.bndEna.dstEnt) &&       
                * (tPst->dstInst == reqInfo->s.bndEna.dstInst)        
                */
                
                /* call function for all SAPs */
                for (i = 0; i < sbGlobalCb.genCfg.maxNmbTSaps; i++)
                {
                   tSap = sbGlobalCb.tSaps[i];
                   if (tSap != (SbTSapCb *) NULLP)
                   {
                      if ((tSap->tPst.dstProcId == reqInfo->s.bndEna.dstProcId)
                         && (tSap->tPst.dstEnt == reqInfo->s.bndEna.dstEnt.ent)
                         && (tSap->tPst.dstInst == 
                             reqInfo->s.bndEna.dstEnt.inst))
                      {
                         /* tSap found, bind it */
                         if (tSap->contEnt != ENTSM)
                         {
                            sbGlobalCb.sbMgmt.hdr.elmId.elmnt = STSBTSAP;
/* sb010.103: Resetting the elmId in the case of failure */
                            if (sbLiBindSap(tSap->tSapCfg.suId, (SbMgmt*)NULLP)
                                  != LCM_REASON_NOT_APPL)
                            {
                              sbGlobalCb.sbMgmt.hdr.elmId.elmnt = 0;
                            }
                         }
                      }
                   }
                }
                break;

             case SHT_GRPTYPE_ENT:
                /* 
                 * go through all the sap control blocks and start bind  
                 * enable procedure on those SAPs for which              
                 * (tPst->dstEnt == reqInfo->s.bndEna.dstEnt) &&       
                 * (tPst->dstInst == reqInfo->s.bndEna.dstInst)        
                 */
                
                /* call function for all SAPs */
                for (i = 0; i < sbGlobalCb.genCfg.maxNmbTSaps; i++)
                {
                   tSap = sbGlobalCb.tSaps[i];
                   if (tSap != (SbTSapCb *) NULLP)
                   {
                      if ((tSap->tPst.dstEnt == reqInfo->s.bndEna.dstEnt.ent) 
                         && (tSap->tPst.dstInst == 
                             reqInfo->s.bndEna.dstEnt.inst))
                      {
                         /* tSap found, bind it */
                         if (tSap->contEnt != ENTSM)
                         {
                            sbLiBindSap(tSap->tSapCfg.suId, (SbMgmt*)NULLP);
                         }
                      }
                   }
                }
                break;
             default:
                cfmInfo.status.reason = LCM_REASON_INVALID_PAR_VAL;
                break;
          }
          break;

       case SHT_REQTYPE_UBND_DIS:  /* system agent control unbind disable */
          /* sb042.102 - Added change for rolling upgrade */
#ifdef SB_RUG
          /* Delete the stored version information for that SAP
           * Loop in the stored version information store and
           * delete all version information entries to that dest */
          for(i = sbGlobalCb.numIntfInfo - 1; i >= 0; i--)
          {
             if(sbGlobalCb.intfInfo[i].grpType == reqInfo->s.ubndDis.grpType)
             {
                switch(sbGlobalCb.intfInfo[i].grpType)
                {
                   case SHT_GRPTYPE_ALL:
                      if (sbGlobalCb.intfInfo[i].dstProcId == 
                               reqInfo->s.ubndDis.dstProcId &&
                          sbGlobalCb.intfInfo[i].dstEnt.ent == 
                               reqInfo->s.ubndDis.dstEnt.ent &&
                          sbGlobalCb.intfInfo[i].dstEnt.inst == 
                               reqInfo->s.ubndDis.dstEnt.inst)
                      {
                         /* delete the stored version information by copying the
                          * last version info into current location
                          */
                         cmMemcpy((U8*) &sbGlobalCb.intfInfo[i],
                           (U8*) &sbGlobalCb.intfInfo[sbGlobalCb.numIntfInfo-1],
                           sizeof(ShtVerInfo));
                         sbGlobalCb.numIntfInfo--;
                      }
                      break;
                   case SHT_GRPTYPE_ENT:
                      if (sbGlobalCb.intfInfo[i].dstEnt.ent == 
                               reqInfo->s.ubndDis.dstEnt.ent &&
                          sbGlobalCb.intfInfo[i].dstEnt.inst == 
                               reqInfo->s.ubndDis.dstEnt.inst)
                      {
                         /* delete the version information by copying the
                          * last version info into current location
                          */
                         cmMemcpy((U8*) &sbGlobalCb.intfInfo[i],
                           (U8*) &sbGlobalCb.intfInfo[sbGlobalCb.numIntfInfo-1],
                           sizeof(ShtVerInfo));
                         sbGlobalCb.numIntfInfo--;
                      }
                      break;
                    default:
                       cfmInfo.status.reason = LCM_REASON_INVALID_PAR_VAL;
                       break;

                } /* switch sbGlobalCb.numIntfInfo */
             } /* end of if sbGlobalCb.numIntfInfo */
          } /* for (i = 0) */
#endif /* SB_RUG */

          switch (reqInfo->s.ubndDis.grpType)
          {
             case SHT_GRPTYPE_ALL:
                /* 
                 * go through all the sap control blocks and start unbind 
                 * disable procedure on those SAPs for which              
                 * (tPst->dstProcId == reqInfo->s.ubndDis.dstProcId) && 
                 * (tPst->dstEnt == reqInfo->s.ubndDis.dstEnt) &&       
                 * (tPst->dstInst == reqInfo-.s.ubndDis.dstInst)        
                 */
                
                /* call function for all TSAPs */
                for (i = 0; i < sbGlobalCb.genCfg.maxNmbTSaps; i++)
                {
                   tSap = sbGlobalCb.tSaps[i];
                   if (tSap != (SbTSapCb *) NULLP)
                   {
                      if ((tSap->tPst.dstProcId == reqInfo->s.bndEna.dstProcId)
                         && (tSap->tPst.dstEnt == reqInfo->s.bndEna.dstEnt.ent) 
                         && (tSap->tPst.dstInst == 
                             reqInfo->s.bndEna.dstEnt.inst))
                      {
                         if (tSap->sapState == SB_SAPSTATE_BND)
                         {
                            sbLiUnbindSap(tSap->tSapCfg.suId);
                         }
                      }
                   }
                }
                /* call function for all SCT SAPs */
                for (i = 0; i < sbGlobalCb.genCfg.maxNmbSctSaps; i++)
                {
                   sctSap = sbGlobalCb.sctSaps[i];
                   if (sctSap != (SbSctSapCb *) NULLP)
                   {
                      if ((sctSap->sctPst.dstProcId == reqInfo->s.bndEna.dstProcId)
                         && (sctSap->sctPst.dstEnt == reqInfo->s.bndEna.dstEnt.ent)
                         && (sctSap->sctPst.dstInst == 
                             reqInfo->s.bndEna.dstEnt.inst))
                      {
                         if (sctSap->sapState != SB_SAPSTATE_UBND)
                         {
                            sbUiUnbindSap(sctSap->sctSapCfg.spId);
                         }
                      }
                   }
                }


                break;

             case SHT_GRPTYPE_ENT:
                /* 
                 * go through all the sap control blocks and start unbind 
                 * disable procedure on those SAPs for which              
                 * (tPst->dstEnt == reqInfo->s.ubndDis.dstEnt) &&       
                 * (tPst->dstInst == reqInfo-.s.ubndDis.dstInst)        
                 */
                
                /* call function for all NSAPs */
                for (i = 0; i < sbGlobalCb.genCfg.maxNmbTSaps; i++)
                {
                   tSap = sbGlobalCb.tSaps[i];
                   if (tSap != (SbTSapCb *) NULLP)
                   {
                      if ((tSap->tPst.dstEnt == reqInfo->s.bndEna.dstEnt.ent) 
                         && (tSap->tPst.dstInst == 
                             reqInfo->s.bndEna.dstEnt.inst))
                      {
                         if (tSap->sapState == SB_SAPSTATE_BND)
                         {
                            sbLiUnbindSap(tSap->tSapCfg.suId);
                         }
                      }
                   }
                }

                /* call function for all SCT SAPs */
                for (i = 0; i < sbGlobalCb.genCfg.maxNmbSctSaps; i++)
                {
                   sctSap = sbGlobalCb.sctSaps[i];
                   if (sctSap != (SbSctSapCb *) NULLP)
                   {
                      if ((sctSap->sctPst.dstEnt == reqInfo->s.bndEna.dstEnt.ent) 
                         && (sctSap->sctPst.dstInst == 
                             reqInfo->s.bndEna.dstEnt.inst))
                      {
                         if (sctSap->sapState != SB_SAPSTATE_UBND)
                         {
                            sbUiUnbindSap(sctSap->sctSapCfg.spId);
                         }
                      }
                   }
                }

                break;

             default:
                cfmInfo.status.reason = LCM_REASON_INVALID_PAR_VAL;
                break;
           }
           break;

        /* sb042.102 - Added change for rolling upgrade */
#ifdef SB_RUG
       case SHT_REQTYPE_GETVER:      /* system agent get version */
          sbGetVer(&cfmInfo.t.gvCfm);
          break;

       case SHT_REQTYPE_SETVER:      /* system agent set version */
          sbSetVer(&reqInfo->s.svReq, &cfmInfo.status);
          break;
#endif /* SB_RUG */

       default:
          cfmInfo.status.reason = LCM_REASON_INVALID_PAR_VAL;
          break;
   }

   if (cfmInfo.status.reason != LCM_REASON_NOT_APPL)
   {
      cfmInfo.status.status = LCM_PRIM_NOK;
   }
   else
   {
      cfmInfo.status.status = LCM_PRIM_OK;
   }

   /* send the response */
   SbMiShtCntrlCfm(&repPst, &cfmInfo);
      
   RETVALUE(ROK);
} /* end SbMiShtCntrlReq */
#endif /* SB_FTHA */
/*
*
*       Fun:   Status Request Primitive
*
*       Desc:  This primitive is used by the Layer Manager to solicit
*              status information. The information is returned via the
*              SbMiLsbStaCfm primitive.
*
*       Ret:   ROK      - ok
*
*       Notes: <none>
*
*       File:  sb_bdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 SbMiLsbStaReq
(
Pst    *pst,                   /* post structure */
SbMgmt *sta                    /* status structure */
)
#else
PUBLIC S16 SbMiLsbStaReq(pst, sta)
Pst    *pst;                   /* post structure */
SbMgmt *sta;                   /* status structure */
#endif
{
   Header      *hdr;               /* Header structure */
   SbMgmt      cfmMsg;             /* configuration confirm */
   S16         ret;                /* return code */
   SbSctSapCb *sctSap;             /* SAP pointer */
   SpId        spId;               /* spId */
   SbTSapCb   *tSap;               /* SAP pointer */
   SuId        suId;               /* suId */
   U32         i;

   TRC3(SbMiLsbStaReq);
#ifdef SS_MULTIPLE_PROCS

   if(SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                         (void **)&sbGlobalCbPtr) != ROK)
   {
     SBLOGERROR(ERRCLS_DEBUG, ESB009, 0,
               "SbMiLsbStaReq () failed, cannot derive sbGlobalCbPtr");
     RETVALUE(FALSE);
   }

   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
         "-------SCTP------(proc(%d), ent(%d), inst(%d))--------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));

#endif /* SS_MULTIPLE_PROCS */


   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
          "SbMiLsbStaReq(pst, elmnt(%d))\n", sta->hdr.elmId.elmnt));

#ifndef SS_MULTIPLE_PROCS
   UNUSED(pst);
#endif  /* SS_MULTIPLE_PROCS */

   /* obtain the header structure from the configuration */
   hdr = &(sta->hdr);

   /* zero out the confirm structure */
   SB_ZERO(&cfmMsg, sizeof(SbMgmt));

   /* Check if configuration has been done */
   if ( (sbGlobalCb.sbInit.cfgDone == FALSE) )
   {
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
             "SbMiLsbStaReq: general configuration not done yet\n"));

      sbLmSendCfm(pst, TSSTA, hdr, LCM_PRIM_NOK, LCM_REASON_GENCFG_NOT_DONE,
                  &cfmMsg);
      RETVALUE(RFAILED);
   }

   /* Check if currently busy servicing a layer manager request */
   if ( sbGlobalCb.sbMgmt.hdr.elmId.elmnt != 0 )
   {
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
             "SbMiLsbStaReq: currently servicing a layer manager request\n"));
      sbLmSendCfm(pst, TSSTA, hdr, LCM_PRIM_NOK, LSB_REASON_LMI_BUSY,
                  &cfmMsg);
      RETVALUE(RFAILED);
   }

   /* default value */
   ret = LCM_REASON_NOT_APPL;

   /* check element */
   switch (hdr->elmId.elmnt)
   {
      case STSBSID:                   /* get the system id information */
      {
         (Void) sbGetSid(&cfmMsg.t.ssta.s.sysId);
         break;
      }

      case STSBGEN:                 /* get the general layer status */
      {
         cfmMsg.t.ssta.s.genSta.memSize  = sbGlobalCb.genSta.memSize;
         cfmMsg.t.ssta.s.genSta.memAlloc = sbGlobalCb.genSta.memAlloc;
         cfmMsg.t.ssta.s.genSta.nmbAssoc = 0;
         for ( i = 0; i < sbGlobalCb.genCfg.maxNmbAssoc; i++ )
         {
            if ( sbGlobalCb.assocCb[i] != (SbSctAssocCb *) NULLP )
            {
               cfmMsg.t.ssta.s.genSta.nmbAssoc++;
            }
         }
         cfmMsg.t.ssta.s.genSta.nmbEndp = 0;
         for ( i = 0; i < sbGlobalCb.genCfg.maxNmbEndp; i++ )
         {
            if ( sbGlobalCb.endpCb[i] != (SbSctEndpCb *) NULLP )
            {
               cfmMsg.t.ssta.s.genSta.nmbEndp++;
            }
         }

         cfmMsg.t.ssta.s.genSta.nmbLocalAddr = sbGlobalCb.genSta.nmbLocalAddr;
         cfmMsg.t.ssta.s.genSta.nmbPeerAddr = sbGlobalCb.genSta.nmbPeerAddr;

         break;
      }

      case STSBSCTSAP:                /* get status of a SCT SAP */
      {
         /* get the spId to look up status for */
         spId = sta->t.ssta.sapId;

         /* validate the sapId */
         /* SCTP Upgrade: Taking out for robustness */
         if( (spId >= sbGlobalCb.genCfg.maxNmbSctSaps) || (spId < 0) )
         {
#if (ERRCLASS & ERRCLS_INT_PAR)
            SBLOGERROR(ERRCLS_INT_PAR, ESB010, (ErrVal) spId,
                       "SbMiLsbStaReq: spId out of range");
#endif /* ERRCLS_INT_PAR */
            ret = LCM_REASON_INVALID_SAP;
            break;
         }

         /* get the SCT SAP control block */
         sctSap = sbGlobalCb.sctSaps[spId];

         /* SCTP Upgrade: Taking out for robustness */
         if ( sctSap == (SbSctSapCb *) NULLP)
         {
#if (ERRCLASS & ERRCLS_INT_PAR)
         /* check to see if the SAP exists */
            SBLOGERROR(ERRCLS_INT_PAR, ESB011, (ErrVal) spId,
                       "SbMiLsbStaReq: Sap not configured");
#endif /* ERRCLS_INT_PAR */
            ret = LCM_REASON_INVALID_SAP;
            break;
         }

         /* get the status of the SCT SAP */
         cfmMsg.t.ssta.s.sapSta.swtch    = sctSap->sctSapCfg.swtch;
         cfmMsg.t.ssta.s.sapSta.hlSt     = sctSap->sapState;
         cfmMsg.t.ssta.sapId             = spId;
         /* sb042.102 - Added change for rolling upgrade */
#ifdef SB_RUG
         cfmMsg.t.ssta.s.sapSta.remIntfValid = sctSap->remIntfValid;
         cfmMsg.t.ssta.s.sapSta.selfIfVer    = SCTIFVER;
         cfmMsg.t.ssta.s.sapSta.remIfVer     = sctSap->sctPst.intfVer;
#endif
         break;
      }

      case STSBTSAP:                  /* get status of a Transport SAP */
      {
         /* get the spId to look up status for */
         suId = sta->t.ssta.sapId;

         /* validate the sapId */
         /* SCTP Upgrade: Taking out for robustness */
         if((suId >= (SuId) sbGlobalCb.genCfg.maxNmbTSaps) || (suId < 0))
         {
#if (ERRCLASS & ERRCLS_INT_PAR)
            SBLOGERROR(ERRCLS_INT_PAR, ESB012, (ErrVal) suId,
                       "SbMiLsbStaReq: suId out of range");
#endif /* ERRCLS_INT_PAR */
            ret = LCM_REASON_INVALID_SAP;
            break;
         }
         /* get the SCT SAP control block */
         tSap = sbGlobalCb.tSaps[suId];

         /* check to see if the SAP exists */
         /* SCTP Upgrade: Taking out for robustness */
         if (tSap == (SbTSapCb *) NULLP)
         {
#if (ERRCLASS & ERRCLS_INT_PAR)
            SBLOGERROR(ERRCLS_INT_PAR, ESB013, (ErrVal) suId,
                       "SbMiLsbStaReq: Sap not configured");
#endif /* ERRCLS_INT_PAR */
            ret = LCM_REASON_INVALID_SAP;
            break;
         }

         /* get the status of the Transport SAP */
         cfmMsg.t.ssta.s.sapSta.swtch    = tSap->tSapCfg.swtch;
         cfmMsg.t.ssta.s.sapSta.hlSt     = tSap->sapState;
         cfmMsg.t.ssta.sapId             = suId;
         /* sb042.102 - Added change for rolling upgrade */
#ifdef SB_RUG
         cfmMsg.t.ssta.s.sapSta.remIntfValid = tSap->remIntfValid;
         cfmMsg.t.ssta.s.sapSta.selfIfVer    = HITIFVER;
         cfmMsg.t.ssta.s.sapSta.remIfVer     = tSap->tPst.intfVer;
#endif
         break;
      }
      case STSBASSOC:               /* get status of an association */
      {
         ret = sbLmAssocSta(sta->t.ssta.s.assocSta.assocId, &(cfmMsg));
         break;
      }

      case STSBDTA:                 /* get status of a dest. tpt addr. */
      {
         ret = sbLmDtaSta(&(sta->t.ssta.s.dtaSta), &(cfmMsg));
         break;
      }
/* sb011.103: Placed  Timer traversing under SB_TMR_TST flag */
/* sb012.103: Replaced the SB_TMR_TST flag with LSB12 */
#ifdef LSB12
      case STSBTMR:
      {
         CmTimer *tmr;
         SbTmrSta *tmrSta;

         tmrSta = &(cfmMsg.t.ssta.s.tmrSta);

         for (i = 0; i < SB_TQSIZE; i++)
         {
            tmr = sbGlobalCb.sbTq[i].first;
            while (tmr != (CmTimer *)NULLP)
            {
               switch (tmr->tmrEvnt)
               {
                  case SB_TMR_LIFETIME:
                     tmrSta->lifetimeTmr++;
                     break;
                  case SB_TMR_T3RTX:
                     tmrSta->t3rtx++;
                     break;
                  case SB_TMR_ACKDELAY:
                     tmrSta->ackDelayTmr++;
                     break;
                  case SB_TMR_SHUTDOWN:
                     tmrSta->t2Shutdown++;
                     break;
                  case SB_TMR_INIT:
                     tmrSta->t1InitTmr++;
                     break;
                  case SB_TMR_COOKIE:
                     tmrSta->cookieTmr++;
                     break;
                  case SB_TMR_HBEAT:
                     tmrSta->hBeat++;
                     break;
                  case SB_TMR_KEY:
                     tmrSta->keyTmr++;
                     break;
                  case SB_TMR_TSAP_BND:
                     tmrSta->tIntTmr++;
                     break;
                  case SB_TMR_FREEZE:
                     tmrSta->freezeTmr++;
                     break;
/* sb054.102 : Addition - Bundling Changes */
#ifdef LSB4
                  case SB_TMR_BUNDLE:
                     tmrSta->bundleTmr++;
                     break;
#endif

                  default:
                     break;
               }
               tmr = tmr->next;
            }
         }
         break;
      }
#endif /* LSB12 */

      default:
      {
#if (ERRCLASS & ERRCLS_INT_PAR)
         SBLOGERROR(ERRCLS_INT_PAR, ESB014, (ErrVal) hdr->elmId.elmnt,
                    "SbMiLsbStaReq: Invalid Element in Status request");
         ret = LCM_REASON_INVALID_ELMNT;
#endif /* ERRCLS_INT_PAR */
         break;
      }

   } /* end switch */

   /* fill the date and time */
   (Void) SGetDateTime(&cfmMsg.t.ssta.dt);

   /* In normal cases, LCM_REASON_NOT_APPL is returned, in all error
    * cases appropriate reason is returned by the above functions */

   /* send the layer manager confirm */
   if (ret != LCM_REASON_NOT_APPL)
   {
      sbLmSendCfm(pst, TSSTA, hdr, LCM_PRIM_NOK, ret, &cfmMsg);
      RETVALUE(RFAILED);
   }

   sbLmSendCfm(pst, TSSTA, hdr, LCM_PRIM_OK, LCM_REASON_NOT_APPL, &cfmMsg);
   RETVALUE(ROK);
}/* end of SbMiLsbStaReq() */

/*
*
*       Fun:   Statistics Request Primitive
*
*       Desc:  This primitive is used by the Layer Manager to solicit
*              statistics information. The statistics values are
*              returned by SbMiLsbStsCfm primitive.The statistics
*              counters can be initialized to NULL using the "action"
*              parameter. The possible values for "action" are:
*
*              ZEROSTS:    zero statistics counters
*              NOZEROSTS:  do not zero statistics counters
*
*       Ret:   ROK
*
*       Notes: <none>
*
*       File:  sb_bdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 SbMiLsbStsReq
(
Pst     *pst,                /* post structure */
Action  action,              /* action to be done */
SbMgmt *sts                  /* statistics structure */
)
#else
PUBLIC S16 SbMiLsbStsReq(pst, action, sts)
Pst     *pst;                /* post structure */
Action  action;              /* action to be done */
SbMgmt *sts;                 /* statistics structure */
#endif
{
   Header      *hdr;               /* Header structure */
   SbMgmt       cfmMsg;            /* configuration confirm */
   SbSctSapCb  *sctSap;            /* SCT SAP */
   SbTSapCb    *tSap;              /* transport SAP */
   DateTime     lastTime;          /* date and time of last stats report */
   DateTime     currentTime;       /* current date and time*/
   S16          ret;

   TRC3(SbMiLsbStsReq)

#ifdef SS_MULTIPLE_PROCS

   if(SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                         (void **)&sbGlobalCbPtr) != ROK)
   {
     SBLOGERROR(ERRCLS_DEBUG, ESB015, 0,
               "SbMiLsbStsReq () failed, cannot derive sbGlobalCbPtr");
     RETVALUE(FALSE);
   }

   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
         "-------SCTP------(proc(%d), ent(%d), inst(%d))--------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));

#endif /* SS_MULTIPLE_PROCS */

   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
          "SbMiLsbStsReq(pst, action(%d), elmnt(%d))\n",
           action, sts->hdr.elmId.elmnt));
#ifndef SS_MULTIPLE_PROCS
   UNUSED(pst);
#endif  /* SS_MULTIPLE_PROCS */

   /* obtain the header structure from the configuration */
   hdr = &(sts->hdr);

   /* zero out the confirm structure */
   SB_ZERO(&cfmMsg, sizeof(SbMgmt));
   
   /* sb020.103:  zero out the lastTime structure */
   SB_ZERO(&lastTime, sizeof(DateTime));
   /* sb035.103: Fix for KlockWorks issue*/
   SB_ZERO(&currentTime, sizeof(DateTime));
   
   /* Check if configuration has been done */
   if ( (sbGlobalCb.sbInit.cfgDone == FALSE) )
   {
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
             "SbMiLsbStsReq: general configuration not done yet\n"));

      sbLmSendCfm(pst, TSTS, hdr, LCM_PRIM_NOK, LCM_REASON_GENCFG_NOT_DONE,
                  &cfmMsg);
      RETVALUE(RFAILED);
   }

   /* Check if currently busy servicing a layer manager request */
   if ( sbGlobalCb.sbMgmt.hdr.elmId.elmnt != 0 )
   {
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
             "SbMiLsbStsReq: currently servicing a layer manager request\n"));
      sbLmSendCfm(pst, TSTS, hdr, LCM_PRIM_NOK, LSB_REASON_LMI_BUSY,
                  &cfmMsg);
      RETVALUE(RFAILED);
   }

   /* get the current date and time for when the request is made */
   SGetDateTime(&currentTime);

   /* default value */
   ret = LCM_REASON_NOT_APPL;

   switch (hdr->elmId.elmnt)
   {
      case STSBGEN:               /* general statistics */
         /* copy the general statistics from the control block */
         cmMemcpy((U8 *)&cfmMsg.t.sts.u.genSts, (U8 *) &sbGlobalCb.genSts,
                  (PTR)sizeof(SbGenSts));

         /* save the last date/time a report was requested */
         cmMemcpy((U8 *)&lastTime, (U8 *) &(sbGlobalCb.genSts.dt),
                  (PTR)sizeof(DateTime));

         if (action == ZEROSTS)
         {
            SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
                   "SbMiLsbStsReq: statistics counters cleared\n"));
            /* zero out the stored statistics */
            SB_ZERO(&sbGlobalCb.genSts, sizeof(SbGenSts));
            /* set time for zeroing action */
            SGetDateTime(&(sbGlobalCb.genSts.dt));
         }

         break;

      case STSBSCTSAP:              /* sap statistics */
      {
         /* verify the SpId */
         /* SCTP Upgrade: Taking out for robustness */
         if ( (sts->t.sts.sapId >= sbGlobalCb.genCfg.maxNmbSctSaps) ||
              (sts->t.sts.sapId < 0) )
         {
#if (ERRCLASS & ERRCLS_INT_PAR)
            SBLOGERROR(ERRCLS_INT_PAR, ESB016, (ErrVal) sts->t.sts.sapId,
                       "SbMiLsbStsReq: sapId out of range");
#endif /* ERRCLS_INT_PAR */
            ret = LCM_REASON_INVALID_SAP;
            break;
         }

         sctSap = sbGlobalCb.sctSaps[sts->t.sts.sapId];

         /* SCTP Upgrade: Taking out for robustness */
         if ( sctSap == (SbSctSapCb *) NULLP )
         {
#if (ERRCLASS & ERRCLS_INT_PAR)
            SBLOGERROR(ERRCLS_INT_PAR, ESB017, (ErrVal) sts->t.sts.sapId,
                       "SbMiLsbStsReq: SAP not configured");
#endif /* ERRCLS_INT_PAR */
            ret = LCM_REASON_INVALID_SAP;
            break;
         }

         /* copy the statistics from the sap to the management structure */
         (Void) cmMemcpy((U8 *) &cfmMsg.t.sts.u.sctSts, (U8 *) &sctSap->sctSts,
                          sizeof(SbSctSapSts));

         /* save the last date/time a report was requested */
         (Void) cmMemcpy((U8 *)&lastTime, (U8 *) &(sctSap->sctSts.dt),
                         sizeof(DateTime));

         if (action == ZEROSTS)
         {
            SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
                   "SbMiLsbStsReq: statistics counters cleared\n"));
            /* zero out the stored statistics in the sap structure */
            SB_ZERO(&sctSap->sctSts, sizeof(SbSctSapSts));
            /* set time for zeroing action */
            SGetDateTime(&(sctSap->sctSts.dt));
         }

         /* sb036.102: Filling in the sap information in the *
          * response message                                 */
         cfmMsg.t.sts.sapId = sts->t.sts.sapId;
         

         break;
      }

       case STSBTSAP:              /* sap statistics */
         /* verify the SuId */
         /* SCTP Upgrade: Taking out for robustness */
         if ( (sts->t.sts.sapId >= sbGlobalCb.genCfg.maxNmbTSaps) ||
              (sts->t.sts.sapId < 0) )
         {
#if (ERRCLASS & ERRCLS_INT_PAR)
            SBLOGERROR(ERRCLS_INT_PAR, ESB018, (ErrVal) sts->t.sts.sapId,
                       "SbMiLsbStsReq: sapId out of range");
#endif /* ERRCLS_INT_PAR */
            ret = LCM_REASON_INVALID_SAP;
            break;
         }

         tSap = sbGlobalCb.tSaps[sts->t.sts.sapId];

         /* SCTP Upgrade: Taking out for robustness */
         if ( tSap == (SbTSapCb *) NULLP )
         {
#if (ERRCLASS & ERRCLS_INT_PAR)
            SBLOGERROR(ERRCLS_INT_PAR, ESB019, (ErrVal) sts->t.sts.sapId,
                       "SbMiLsbStsReq: SAP not configured");
#endif /* ERRCLS_INT_PAR */
            ret = LCM_REASON_INVALID_SAP;
            break;
         }

         /* copy the statistics from the sap to the management structure */
         cmMemcpy((U8 *) &cfmMsg.t.sts.u.tSts, (U8 *) &(tSap->tSts),
                  sizeof(SbTSapSts));

         /* save the last date/time a report was requested */
         cmMemcpy((U8 *) &lastTime, (U8 *) &(tSap->tSts.dt), sizeof(DateTime));

         if (action == ZEROSTS)
         {
            SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
                   "SbMiLsbStsReq: statistics counters cleared\n"));
            /* zero out the stored statistics in the sap structure */
            SB_ZERO(&(tSap->tSts), sizeof(SbTSapSts));
            /* set time for zeroing action */
            SGetDateTime(&(tSap->tSts.dt));
         }
         /* sb036.102: Filling in the sap information in the *
          * response message                                 */
         cfmMsg.t.sts.sapId = sts->t.sts.sapId;
         break;

      default:
#if (ERRCLASS & ERRCLS_INT_PAR)
         SBLOGERROR(ERRCLS_INT_PAR, ESB020, (ErrVal) hdr->elmId.elmnt,
                    "SbMiLsbStsReq: Bad Element in statistics request");
#endif /* ERRCLS_INT_PAR */
         ret = LCM_REASON_INVALID_ELMNT;
         break;
   } /* end of switch statement */

   /* determine the duration since the counters were zeroed */
   sbDetDuration(&lastTime, &currentTime, &(cfmMsg.t.sts.dura));

   /* set the current date/time */
   cmMemcpy((U8 *) &(cfmMsg.t.sts.dt), (U8 *) &currentTime, sizeof(DateTime));

   /* In normal cases, LCM_REASON_NOT_APPL is returned, in all error
    * cases appropriate reason is returned by the above functions */

   /* send the layer manager confirm */
   if (ret != LCM_REASON_NOT_APPL)
   {
      sbLmSendCfm(pst, TSTS, hdr, LCM_PRIM_NOK, ret, &cfmMsg);
      RETVALUE(RFAILED);
   }

   /* Issue a statistics confirm */
   sbLmSendCfm(pst, TSTS, hdr, LCM_PRIM_OK, LCM_REASON_NOT_APPL, &cfmMsg);

   RETVALUE(ROK);
}/* end of SbMiLsbStsReq() */

/****************************************************************************/
/* SCT upper interface primitives                                           */
/****************************************************************************/

/*
*
*       Fun:   SbUiSctBndReq
*
*       Desc:  Bind Request Primitive
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: This function binds a User to the SCTP Layer.
*              The SCTP Layer allocates a service access point for this
*              bind and records the identity of the service user. If the
*              SAP is already bound then it is first unbound and then rebound.
*              It also issues a SbUiSctBndCfm to the service user
*              after completing a successful bind.
*
*       File:  sb_bdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 SbUiSctBndReq
(
Pst        *pst,              /* Post structure */
SuId        suId,             /* service user id */
SpId        spId              /* service provider id */
)
#else
PUBLIC S16 SbUiSctBndReq(pst, suId, spId)
Pst        *pst;              /* Post Structure */
SuId        suId;             /* service user id */
SpId        spId;             /* service provider id */
#endif
{
   SbSctSapCb *sctSap;         /* pointer to current SAP */
   S16         ret;
#ifdef SB_RUG
   Bool        found;
   S16         i;
#endif /* SB_RUG */

   TRC3(SbUiSctBndReq)

#ifdef SS_MULTIPLE_PROCS

   if(SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                         (void **)&sbGlobalCbPtr) != ROK)
   {
     SBLOGERROR(ERRCLS_DEBUG, ESB021, 0,
               "SbUiSctBndReq () failed, cannot derive sbGlobalCbPtr");
     RETVALUE(FALSE);
   }

   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
         "-------SCTP------(proc(%d), ent(%d), inst(%d))--------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));

#endif /* SS_MULTIPLE_PROCS */

   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctBndReq(pst, suId(%d), spId(%d))\n", suId, spId));

   /* Validation of Input parameters */
   ret = ROK;

   /* sb041.102: remove the errcls parameter check flag */
   /* check the SpId. If it fails then no bind confirm sent */

   if ( (spId >= (SpId) sbGlobalCb.genCfg.maxNmbSctSaps) ||
        (spId < 0) )
   {
      /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
      SB_LM_GEN_ALARM((U16)LCM_CATEGORY_INTERFACE, \
                  (U16)LCM_EVENT_UI_INV_EVT,\
                  (U16)LCM_CAUSE_INV_SPID, \
                  spId, LSB_SW_RFC_REL0);
      ret = RFAILED;
   }
   else if ( sbGlobalCb.sctSaps[spId] == (SbSctSapCb *) NULLP )
   {
    /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
      SB_LM_GEN_ALARM((U16)LCM_CATEGORY_INTERFACE, \
                  (U16)LCM_EVENT_UI_INV_EVT, \
                  (U16)LCM_CAUSE_INV_SAP, \
                  spId, LSB_SW_RFC_REL0);
      ret = RFAILED;
   }

   if ( ret != ROK )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB022, (ErrVal)spId,
                 "SbUiSctBndReq: Invalid spId");
      RETVALUE(RFAILED);
   }

   /* Check if the SAP is already bound. If it is then first unbind it */
   sctSap = sbGlobalCb.sctSaps[spId];
   if (sctSap->sapState == SB_SAPSTATE_BND)
   {
      sbUiUnbindSap(spId);
   }

#ifdef SB_RUG
   /* For upper interface SAP, we look up the version info from the stored
    * information if it is available already at first bound request
    */
   found = FALSE;
   if (sctSap->remIntfValid == FALSE)
   {
      for (i = 0; i < sbGlobalCb.numIntfInfo && found == FALSE; i++)
      {
         if (sbGlobalCb.intfInfo[i].intf.intfId == SCTIF)
         {
            switch (sbGlobalCb.intfInfo[i].grpType)
            {
               case SHT_GRPTYPE_ALL:
                  if (sbGlobalCb.intfInfo[i].dstProcId == pst->srcProcId &&
                      sbGlobalCb.intfInfo[i].dstEnt.ent == pst->srcEnt &&
                      sbGlobalCb.intfInfo[i].dstEnt.inst == pst->srcInst)
                     found = TRUE;
                  break;
               case SHT_GRPTYPE_ENT:
                  if (sbGlobalCb.intfInfo[i].dstEnt.ent == pst->srcEnt &&
                      sbGlobalCb.intfInfo[i].dstEnt.inst == pst->srcInst)
                     found = TRUE;
                  break;
            }
         }
      }
      if (found == TRUE)
      {
         sctSap->sctPst.intfVer = sbGlobalCb.intfInfo[i-1].intf.intfVer;
         sctSap->remIntfValid = TRUE;
      }
      else
      {
         /* send a NACK back to the user */
         (Void) SbUiSctBndCfm(&(sctSap->sctPst), suId, CM_BND_NOK);

         SBLOGERROR(ERRCLS_INT_PAR, ESB023, (ErrVal)spId,
                    "SbUiSctBndReq: Failed, remote ver info not available");
          /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
         SB_LM_GEN_ALARM(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT, \
                      LCM_CAUSE_SWVER_NAVAIL, spId, LSB_SW_RFC_REL0);
         RETVALUE(ROK);
      }
   }
#endif /* SB_RUG */

   /* next we bind the SAP */
   /* SAP is configured already */
   /* copy the necessary parameters in the SAP */
   sctSap->suId             = suId;
   sctSap->sctPst.dstProcId = pst->srcProcId;
   sctSap->sctPst.dstEnt    = pst->srcEnt;
   sctSap->sctPst.dstInst   = pst->srcInst;

   /* don't know if these are required */
   sctSap->sctPst.event     = EVTNONE;
   /* sb017.102: Code removed for spare1 */

   /* set SAP state to bound */
   sctSap->sapState         = SB_SAPSTATE_BND;

   /* Update the date and time for statistics */
   (Void) SGetDateTime(&(sctSap->sctSts.dt));

   /* send an acknowledgement back to the user */
   (Void) SbUiSctBndCfm(&(sctSap->sctPst), suId, CM_BND_OK);

   RETVALUE(ROK);
}/* end of SbUiSctBndReq() */

/*
*
*       Fun:   SbUiSctEndpOpenReq
*
*       Desc:  Primitive to Open an Endpoint Server.
*
*       Ret:   ROK
*              ROKDUP
*              RFAILED
*
*       Notes: This function opens an endpoint on the SCTP Layer. An unused
*              spEndpId is found and the necessary structures are created
*              and initialised.
*
*       File:  sb_bdy1.c
*
*/

/* sb046.102: Multiple IP address per Endp */
/* sb082.102: Changes for Non-ANSI compilation */
#ifdef SCT_ENDP_MULTI_IPADDR
#ifdef ANSI
PUBLIC S16 SbUiSctEndpOpenReq
(
Pst           *pst,              /* Post structure */
SpId           spId,             /* Service provider Id */
UConnId        suEndpId,         /* Service user Endpoint ID */
SctPort        port,             /* Port number */
SctNetAddrLst *intfNAddrLst      /* Interface IP address list */
)
#else
PUBLIC S16 SbUiSctEndpOpenReq(pst, spId, suEndpId, port, intfNAddrLst)
Pst           *pst;              /* Post structure */
SpId           spId;             /* Service provider Id */
UConnId        suEndpId;         /* Service user Endpoint ID */
SctPort        port;             /* Port number */
SctNetAddrLst *intfNAddrLst;     /* Interface IP address list */
#endif
#else /* SCT_ENDP_MULTI_IPADDR */
#ifdef ANSI
PUBLIC S16 SbUiSctEndpOpenReq
(
Pst           *pst,              /* Post structure */
SpId           spId,             /* Service provider Id */
UConnId        suEndpId,         /* Service user Endpoint ID */
SctPort        port,             /* Port number */
CmNetAddr     *intfNAddr         /* Interface IP address */
)
#else
PUBLIC S16 SbUiSctEndpOpenReq(pst, spId, suEndpId, port, intfNAddr)
Pst           *pst;              /* Post structure */
SpId           spId;             /* Service provider Id */
UConnId        suEndpId;         /* Service user Endpoint ID */
SctPort        port;             /* Port number */
CmNetAddr     *intfNAddr;        /* Interface IP address */
#endif
#endif /* SCT_ENDP_MULTI_IPADDR */
{
   /* local parameters */
   U32            i;
   UConnId        spEndpId;
   SbSctEndpCb   *endpCb;
   SbSctSapCb    *sctSap;
   CmNetAddr      tmpAddr;
   S16            ret;
/* sb009.103 : SOL10 changes */
#ifndef SB_SOL10_MULTIPORT
   SbLocalAddrCb  *localAddr;
#endif
   /* RFC 4460 -- RTR */
#if ((ERRCLASS & ERRCLS_INT_PAR) || (defined(SCT_ENDP_MULTI_IPADDR)))
   U32            j;
#endif
   /* sb005.103: adding IPV6 debug traces */ 
#ifdef SB_IPV6_SUPPORTED
   S8             ipv6Addr[SB_IPV6STR_SIZE]; /* To  generate ipv6 traces */
   U8             *tempIpv6Addr;
#endif
/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   SbTSapHashCb   *tsapHashCb;
   SbTSapCb       *tSapCb;
   U32            k;
#endif

   TRC3(SbUiSctEndpOpenReq)

#ifdef SS_MULTIPLE_PROCS

   if(SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                         (void **)&sbGlobalCbPtr) != ROK)
   {
     SBLOGERROR(ERRCLS_DEBUG, ESB024, 0,
               "SbUiSctEndpOpenReq () failed, cannot derive sbGlobalCbPtr");
     RETVALUE(FALSE);
   }

   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
         "-------SCTP------(proc(%d), ent(%d), inst(%d))--------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));

#endif /* SS_MULTIPLE_PROCS */

   /* Patch sb031.102 IPV6 Support Added */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef SCT_ENDP_MULTI_IPADDR
#ifdef BIT_64
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
      "SbUiSctEndpOpenReq(pst, spId(%d), suEndpId(%d), port(%d), intfNAddrType(%d))\n",
      spId, suEndpId, port, intfNAddrLst->nAddr[0].type));
#else
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
      "SbUiSctEndpOpenReq(pst, spId(%d), suEndpId(%ld), port(%d), intfNAddrType(%d))\n",
      spId, suEndpId, port, intfNAddrLst->nAddr[0].type));
#endif /* BIT_64 */
#else /* SCT_ENDP_MULTI_IPADDR */
#ifdef BIT_64
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
      "SbUiSctEndpOpenReq(pst, spId(%d), suEndpId(%d), port(%d), intfNAddrType(%d))\n",
      spId, suEndpId, port, intfNAddr->type));
#else
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
      "SbUiSctEndpOpenReq(pst, spId(%d), suEndpId(%ld), port(%d), intfNAddrType(%d))\n",
      spId, suEndpId, port, intfNAddr->type));
#endif /* BIT_64 */
#endif /* SCT_ENDP_MULTI_IPADDR */


   /* sb051.102 - debug prints added */
#ifdef SCT_ENDP_MULTI_IPADDR
/*sb005.103: IPV6 address print added */
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf, "SbUiSctEndpOpenReq: Defined SCT_ENDP_MULTI_IPADDR, intfNAddrLst->nmb = %d\n",intfNAddrLst->nmb));
   for( i = 0; i < intfNAddrLst->nmb; i++ )
   {
#ifdef SB_IPV6_SUPPORTED
     if (intfNAddrLst->nAddr[i].type == CM_NETADDR_IPV6 )
     {
        tempIpv6Addr = intfNAddrLst->nAddr[i].u.ipv6NetAddr;
        SB_CPY_IPV6ADSTR(ipv6Addr, tempIpv6Addr)
/* sb028.103: Fix for compilation warnings */
#ifdef ALIGN_64BIT
        SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
           "SbUiSctEndpOpenReq: intfNAddrLst->nAddr[%d] = %s\n", i, ipv6Addr));
#else
 SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
           "SbUiSctEndpOpenReq: intfNAddrLst->nAddr[%ld] = %s\n", i, ipv6Addr));
#endif /* ALIGN_64BIT */

     }
#endif /* SB_IPV6_SUPPORTED */
     if (intfNAddrLst->nAddr[i].type == CM_NETADDR_IPV4 )
     {
/* sb028.103: Fix for compilation warnings */
#ifdef ALIGN_64BIT
     SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
         "SbUiSctEndpOpenReq: intfNAddrLst->nAddr[%d] = %x\n", i, intfNAddrLst->nAddr[i].u.ipv4NetAddr));
#else
SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
         "SbUiSctEndpOpenReq: intfNAddrLst->nAddr[%ld] = %ld\n", i, intfNAddrLst->nAddr[i].u.ipv4NetAddr));
#endif /* ALIGN_64BIT */

     }
   }
#else /* SCT_ENDP_MULTI_IPADDR */

#ifdef SB_IPV6_SUPPORTED
   if (intfNAddr->type == CM_NETADDR_IPV6 )
   {
      tempIpv6Addr = intfNAddr->u.ipv6NetAddr;
      SB_CPY_IPV6ADSTR(ipv6Addr, tempIpv6Addr)
      SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
         "SbUiSctEndpOpenReq: Undefined SCT_ENDP_MULTI_IPADDR, intfNAddr = %s\n", ipv6Addr));
   }
#endif /* SB_IPV6_SUPPORTED */
   if (intfNAddr->type == CM_NETADDR_IPV4 )
   {
      /* sb034.103: Fixed gcc compilation warnings */
#ifdef ALIGN_64BIT
       SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
         "SbUiSctEndpOpenReq: Undefined SCT_ENDP_MULTI_IPADDR, intfNAddr = %x\n", intfNAddr->u.ipv4NetAddr)); 
#else
      SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
         "SbUiSctEndpOpenReq: Undefined SCT_ENDP_MULTI_IPADDR, intfNAddr = %lx\n", intfNAddr->u.ipv4NetAddr)); 
#endif
   }
#endif /* SCT_ENDP_MULTI_IPADDR */

   UNUSED(pst);
/* sb009.103 : SOL10 changes */
#ifndef SB_SOL10_MULTIPORT
   localAddr = (SbLocalAddrCb  *)NULLP;
#endif
     /* Validation of Input parameters */

   /* sb001.12: Addition initalize tmpAddr before hash-list operation */
   SB_ZERO((U8 *) &tmpAddr, sizeof(CmNetAddr));


   /* SCTP Upgrade: Taking out for robustness */
   /* check the SpId. */
   SB_CHK_SPID(spId, LCM_EVENT_UI_INV_EVT, ret);
   if(ret != ROK)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB025, (ErrVal)spId,
                 "SbUiSctEndpOpenReq: Invalid spId");
#endif /* ERRCLS_INT_PAR */
      RETVALUE(RFAILED);
   }

   /* get the SAP to operate on */
   sctSap = sbGlobalCb.sctSaps[spId];

/* sb009.103 : SOL10 changes */
#ifndef SB_SOL10_MULTIPORT
#if (ERRCLASS & ERRCLS_INT_PAR)

   /* sb046.102: Multiple IP address per Endp */
#ifdef SCT_ENDP_MULTI_IPADDR
   for ( i = 0; i < intfNAddrLst->nmb; i++ )
   {
      SB_CPY_NADDR(&(tmpAddr), &(intfNAddrLst->nAddr[i]));
      
      /* sanity check on the interface address */
      ret = cmHashListFind(&(sbGlobalCb.localAddrHl),
                           (U8 *) &(tmpAddr),
                           (U16) sizeof(CmNetAddr), 0,
                           (PTR *) &localAddr);
      
      if (ret != ROK)
      {
         SBLOGERROR(ERRCLS_INT_PAR, ESB026, (ErrVal)0,
            "SbUiSctEndpOpenReq: Invalid interface address, address "
            "not configured for TSAP");
         SbUiSctEndpOpenCfm( &(sctSap->sctPst), sctSap->suId, suEndpId,
                             0, SCT_NOK, SCT_CAUSE_INV_PAR_VAL);
         RETVALUE(RFAILED);
      }
   } 
#else /* SCT_ENDP_MULTI_IPADDR */
   SB_CPY_NADDR(&(tmpAddr), intfNAddr);

   /* sanity check on the interface address */
   ret = cmHashListFind(&(sbGlobalCb.localAddrHl),
                        (U8 *) &(tmpAddr),
                        (U16) sizeof(CmNetAddr), 0,
                        (PTR *) &localAddr);

   if (ret != ROK)
   {
      /* Try to find an IP_ANY if no specific match is found */
      SB_ZERO((U8 *) &tmpAddr, sizeof(CmNetAddr))
      tmpAddr.type = intfNAddr->type;
      ret = cmHashListFind(&(sbGlobalCb.localAddrHl),
                           (U8 *) &(tmpAddr),
                           (U16) sizeof(CmNetAddr), 0,
                           (PTR *) &localAddr);
   }
   if (ret != ROK)
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB027, (ErrVal)0,
         "SbUiSctEndpOpenReq: Invalid interface address, address not configured for TSAP");
      SbUiSctEndpOpenCfm( &(sctSap->sctPst), sctSap->suId, suEndpId,
                          0, SCT_NOK, SCT_CAUSE_INV_PAR_VAL);
      RETVALUE(RFAILED);
   }
#endif /* SCT_ENDP_MULTI_IPADDR */
#endif /* ERRCLS_INT_PAR */
#endif /* SB_SOL10_MULTIPORT */

   /* check to see if the endpoint exists using suEndpId as a lookup field */
   endpCb = (SbSctEndpCb *) NULLP;
   spEndpId = 0;

   for ( i = 0; i < sbGlobalCb.genCfg.maxNmbEndp; i++ )
   {
      if ( sbGlobalCb.endpCb[i] != (SbSctEndpCb *) NULLP )
      {
         endpCb = sbGlobalCb.endpCb[i];
         if ( (endpCb->suEndpId != suEndpId) || (endpCb->spId != spId) )
         {
            endpCb = (SbSctEndpCb *) NULLP;
         }
         else
         {
            /* if we are here then the endpoint exists */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
            SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
               "SbUiSctEndpOpenReq: endpoint exists for suEndpId(%d) and spId(%d)\n",
               suEndpId, spId));
#else
            SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
               "SbUiSctEndpOpenReq: endpoint exists for suEndpId(%ld) and spId(%d)\n",
               suEndpId, spId));
#endif /* BIT_64 */
            spEndpId = i;
            i = sbGlobalCb.genCfg.maxNmbEndp;      /* set to exit the loop */
         }
      }
   }

   if ( endpCb == (SbSctEndpCb *) NULLP )
   {
      /* if we are here then the endpoint does not already exist */
      SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
             "SbUiSctEndpOpenReq: suEndpId not used\n"));
      /* look for empty slot in list */
      for ( i = 0; i < sbGlobalCb.genCfg.maxNmbEndp; i++ )
      {
         if ( sbGlobalCb.endpCb[i] == (SbSctEndpCb *) NULLP )
         {
            break;
         }
      }
      spEndpId = i;

      /* check to see if config. maximum is reached */
      if ( spEndpId >= sbGlobalCb.genCfg.maxNmbEndp )
      {
         SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                "SbUiSctEndpOpenReq: endpoint config. max reached\n"));
         SbUiSctEndpOpenCfm( &(sctSap->sctPst), sctSap->suId, suEndpId,
                             0, SCT_NOK, SCT_CAUSE_EXCEED_CONF_VAL);
         RETVALUE(RFAILED);
      }

      /* create new endpoint structure */
      SB_ALLOC(sizeof(SbSctEndpCb), endpCb, ret);
      if ( ret != ROK )
      {
         SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                "SbUiSctEndpOpenReq: could not allocate new endpoint\n"));
         SbUiSctEndpOpenCfm( &(sctSap->sctPst), sctSap->suId, suEndpId,
                             0, SCT_NOK, SCT_CAUSE_OUTRES);
         RETVALUE(RFAILED);
      }

      endpCb->suEndpId  = suEndpId;
      endpCb->spEndpId  = spEndpId;
      endpCb->spId      = spId;
      
      /* sb046.102: Multiple IP address per Endp */
#ifdef SCT_ENDP_MULTI_IPADDR
      SB_CPY_NADDRLST(&(endpCb->localAddrLst), intfNAddrLst);
   
      /* sb051.102 - debug prints added */
/*sb005.103: IPV6 address print added */
      for( i = 0; i < endpCb->localAddrLst.nmb; i++ )
      {
#ifdef SB_IPV6_SUPPORTED
         if (endpCb->localAddrLst.nAddr[i].type == CM_NETADDR_IPV6 )
         {
            tempIpv6Addr = endpCb->localAddrLst.nAddr[i].u.ipv6NetAddr;
            SB_CPY_IPV6ADSTR(ipv6Addr, tempIpv6Addr)
 /* sb028.103: Fix for compilation warnings */
#ifdef ALIGN_64BIT
            SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
               "SbUiSctEndpOpenReq: endpCb->localAddrLst.nAddr[%d] = %s\n", i, ipv6Addr));
#else
SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
               "SbUiSctEndpOpenReq: endpCb->localAddrLst.nAddr[%ld] = %s\n", i, ipv6Addr));
#endif /* ALIGN_64BIT */
         }
#endif /* SB_IPV6_SUPPORTED */
         if (endpCb->localAddrLst.nAddr[i].type == CM_NETADDR_IPV4 )
         {
 /* sb028.103: Fix for compilation warnings */

#ifdef ALIGN_64BIT           
            SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                   "SbUiSctEndpOpenReq: endpCb->localAddrLst.nAddr[%d] = %x\n",
                    i, endpCb->localAddrLst.nAddr[i].u.ipv4NetAddr));
#else
            SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                  "SbUiSctEndpOpenReq: endpCb->localAddrLst.nAddr[%ld] = %ld\n",
                   i, endpCb->localAddrLst.nAddr[i].u.ipv4NetAddr));
#endif /* ALIGN_64BIT */
         }
      }
#else /* SCT_ENDP_MULTI_IPADDR */
      endpCb->localAddrLst.nmb = 1;
      SB_CPY_NADDR(&(endpCb->localAddrLst.nAddr[0]), intfNAddr);
#ifdef SB_IPV6_SUPPORTED
      if (endpCb->localAddrLst.nAddr[0].type == CM_NETADDR_IPV6 )
      {
         tempIpv6Addr = endpCb->localAddrLst.nAddr[0].u.ipv6NetAddr;
         SB_CPY_IPV6ADSTR(ipv6Addr, tempIpv6Addr)
         SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
            "SbUiSctEndpOpenReq: endpCb->localAddrLst.nAddr[0] = %s\n", ipv6Addr));
      }
#endif /* SB_IPV6_SUPPORTED */
      if (endpCb->localAddrLst.nAddr[0].type == CM_NETADDR_IPV4 )
      {
         /* sb034.103: Fixed gcc compilation warnings */
#ifdef ALIGN_64BIT           
          SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
         "SbUiSctEndpOpenReq: endpCb->localAddrLst.nAddr[0] = %x\n",endpCb->localAddrLst.nAddr[0].u.ipv4NetAddr));
#else
         SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
         "SbUiSctEndpOpenReq: endpCb->localAddrLst.nAddr[0] = %lx\n",endpCb->localAddrLst.nAddr[0].u.ipv4NetAddr));
#endif
      }
#endif /* SCT_ENDP_MULTI_IPADDR */

      /* choose the port */
      if ( port == SB_PORT_ANY )
      {
         /* choose a port */
         endpCb->port = sbAsChoosePort(&(endpCb->localAddrLst.nAddr[0]));
      }
      else
      {
         endpCb->port = port;
      }

      /* insert into array list */
      sbGlobalCb.endpCb[spEndpId] = endpCb;

      /* Insert the IP address + port number combination into the hash list */
      for ( i = 0; i < endpCb->localAddrLst.nmb; i++ )
      {
         SbAddrPortCb *addrPortCb=NULLP;
/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
         SbLocalAddrCb    *localAddrCb = NULLP;

         ret = ROK;

         /* look for an empty spot for a new localAddrCb */
         for ( k = 0; k < (sbGlobalCb.genCfg.maxNmbEndp * SCT_MAX_NET_ADDRS); k++)
         {
            if ( sbGlobalCb.localAddrCb[k] == (SbLocalAddrCb *) NULLP )
            {
               /* empty spot in list found */
               break;
            }
         }

         if ( k >= (sbGlobalCb.genCfg.maxNmbEndp * SCT_MAX_NET_ADDRS))
         {
            SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                 "SbUiSctEndpOpenReq: max configuration reached for localAddCb\n"));
            SbUiSctEndpOpenCfm( &(sctSap->sctPst), sctSap->suId, suEndpId,
                                0, SCT_NOK, SCT_CAUSE_OUTRES);
            sbEndpOpenCleanup(endpCb, i);
            RETVALUE(RFAILED);
         }

         /* create a new localAddrCb */
         SB_ALLOC(sizeof(SbLocalAddrCb), localAddrCb, ret);
         if ( ret != ROK )
         {
            SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                 "SbUiSctEndpOpenReq: could not allocate new SbLocalAddrCb\n"));
            SbUiSctEndpOpenCfm( &(sctSap->sctPst), sctSap->suId, suEndpId,
                                0, SCT_NOK, SCT_CAUSE_OUTRES);
            sbEndpOpenCleanup(endpCb, i);
            RETVALUE(RFAILED);
         }

         SB_CPY_NADDR(&(localAddrCb->ownAddr), &(endpCb->localAddrLst.nAddr[i]));
         localAddrCb->port            = endpCb->port;
         localAddrCb->spEndpId        = spEndpId;
         localAddrCb->spConId         = 0;
         localAddrCb->suConId         = k;
         localAddrCb->spOtherConId    = 0;
         localAddrCb->suOtherConId    = k + (sbGlobalCb.genCfg.maxNmbEndp * SCT_MAX_NET_ADDRS);
         localAddrCb->connected       = FALSE;
         localAddrCb->conRetryAttempt = 0;

         ret = cmHashListFind(&(sbGlobalCb.tsapHl),
                              (U8 *) &(localAddrCb->ownAddr),
                              (U16) sizeof(CmNetAddr), 0,
                              (PTR *) &tsapHashCb);
         if (ret != ROK)
         {
            SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
              "SbUiSctEndpOpenReq: Invalid interface address, address not configured for TSAP\n"));
            SbUiSctEndpOpenCfm( &(sctSap->sctPst), sctSap->suId, suEndpId,
                                0, SCT_NOK, SCT_CAUSE_INV_PAR_VAL);

            SB_FREE(sizeof(SbLocalAddrCb), localAddrCb);
            sbEndpOpenCleanup(endpCb, i);
            RETVALUE(RFAILED);
         }

         localAddrCb->suId = tsapHashCb->suId;

         /* insert into the global array list */
         sbGlobalCb.localAddrCb[localAddrCb->suConId] = localAddrCb;
#endif

         /* create new address/port structure */
         SB_ALLOC(sizeof(SbAddrPortCb), addrPortCb, ret);
         if ( ret != ROK )
         {
            SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                 "SbUiSctEndpOpenReq: could not allocate new SbAddrPortCb\n"));
            SbUiSctEndpOpenCfm( &(sctSap->sctPst), sctSap->suId, suEndpId,
                                0, SCT_NOK, SCT_CAUSE_OUTRES);
/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
            sbGlobalCb.localAddrCb[localAddrCb->suConId] = NULLP;
            SB_FREE(sizeof(SbLocalAddrCb), localAddrCb);
            sbEndpOpenCleanup(endpCb, i);
#endif
            RETVALUE(RFAILED);
         }

         addrPortCb->spEndpId  = endpCb->spEndpId;
         /* sb048.102: set addressCb entry to zero */
         cmMemset((U8 *)&(addrPortCb->sbAddrPortEntry),
                        0, sizeof(SbAddrPortEntry));
/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
         addrPortCb->localAddrCb  = localAddrCb;
         addrPortCb->sbAddrPortEntry.port = endpCb->port;
#else
         addrPortCb->sbAddrPortEntry.port = port;
#endif
         /*sb080.102:Adjusting the macro call to single line*/
         SB_CPY_NADDR(&(addrPortCb->sbAddrPortEntry.localAddr),&(endpCb->localAddrLst.nAddr[i]));
         ret = cmHashListInsert(&(sbGlobalCb.addrPortHl), (PTR) addrPortCb,
                                (U8 *) &(addrPortCb->sbAddrPortEntry),
                                sizeof(SbAddrPortEntry));
/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
         if ( ret != ROK )
         {
            SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                 "SbUiSctEndpOpenReq: failed to insert addrport cb into hashlist\n"));
            SbUiSctEndpOpenCfm( &(sctSap->sctPst), sctSap->suId, suEndpId,
                                0, SCT_NOK, SCT_CAUSE_ENDP_OPEN);

            SB_FREE(sizeof(SbAddrPortCb), addrPortCb);

            sbGlobalCb.localAddrCb[localAddrCb->suConId] = NULLP;
            SB_FREE(sizeof(SbLocalAddrCb), localAddrCb);
            sbEndpOpenCleanup(endpCb, i);
            RETVALUE(RFAILED);
         }


         tSapCb = sbGlobalCb.tSaps[localAddrCb->suId];

         if ((ret = sbLiOpenServer(tSapCb, localAddrCb)) != ROK)
         {
            SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                 "SbUiSctEndpOpenReq: could not open server\n"));
            SbUiSctEndpOpenCfm( &(sctSap->sctPst), sctSap->suId, suEndpId,
                                0, SCT_NOK, SCT_CAUSE_ENDP_OPEN);

            cmHashListDelete(&(sbGlobalCb.addrPortHl), (PTR)addrPortCb);
            SB_FREE(sizeof(SbAddrPortCb), addrPortCb);

            sbGlobalCb.localAddrCb[localAddrCb->suConId] = NULLP;
            SB_FREE(sizeof(SbLocalAddrCb), localAddrCb);
            sbEndpOpenCleanup(endpCb, i);
            RETVALUE(RFAILED);
         }

#else

#if (ERRCLASS & ERRCLS_INT_PAR)
         /* check if there is address/port overlapping */
         if ( ret != ROK )
         {
            for ( j = 0; j < i; j++ )
            {

               SbAddrPortCb *tmpAddrPortCb=NULLP;
               SbAddrPortEntry tmpAddrPortEntry;

               /* sb048.102: set addressCb entry to zero */
               cmMemset((U8 *)&tmpAddrPortEntry, 0, sizeof(SbAddrPortEntry));
               tmpAddrPortEntry.port = port;
          /*sb080.102:Adjusting the macro call to single line*/
               SB_CPY_NADDR(&(tmpAddrPortEntry.localAddr), &(endpCb->localAddrLst.nAddr[j]));

               /* sb048.102: pass the tmpAddrPortCb address */
               /* sb031.103: Checking the return value of cmHashListFind and 
                * if you have any entries delete the entry first and then 
                * free the memory allocated to that entry. */
               ret = cmHashListFind(&(sbGlobalCb.addrPortHl),
                     (U8 *) &(tmpAddrPortEntry),
                     (U16) sizeof(SbAddrPortEntry), 0,
                     (PTR *) &tmpAddrPortCb);
               if (ret == ROK)
               {
                  /* sb032.103: Type casted the argument tmpAddrPortCb by PTR */
                  cmHashListDelete(&(sbGlobalCb.addrPortHl),(PTR) tmpAddrPortCb);

                  /* remove the addrPortCb that was inserted in this primitive */
                  SB_FREE(sizeof(SbAddrPortCb), tmpAddrPortCb);
               }
            }
         
            /* endpoint has been allocated so delete it */
            SB_FREE(sizeof(SbSctEndpCb), endpCb);
            sbGlobalCb.endpCb[spEndpId] = (SbSctEndpCb *) NULLP;
         
            SBLOGERROR(ERRCLS_INT_PAR, ESB028, (ErrVal)0,
                       "SbUiSctEndpOpenReq: Interface-port combination overlap");
            SbUiSctEndpOpenCfm( &(sctSap->sctPst), sctSap->suId, suEndpId,
                                0, SCT_NOK, SCT_CAUSE_ENDP_OPEN);
            RETVALUE(RFAILED);
         }
#endif /* ERRCLS_INT_PAR */
#endif
      }
      SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
             "SbUiSctEndpOpenReq: inserted addr/port entry into HL\n"));

/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
      /* initialize the end point open cfm timer structure */
      cmInitTimers(&(endpCb->timer), 1);

      /* start the end point open cfm timer */
      SB_START_TMR( &(endpCb->timer),
                    endpCb,
                    SB_TMR_ENDP_OPEN,
                    SB_ENDP_OPEN_TMR_VAL);
#else
      SbUiSctEndpOpenCfm( &(sctSap->sctPst), sctSap->suId, suEndpId,
                          spEndpId, SCT_OK, SCT_CAUSE_NOT_APPL);
#endif
      RETVALUE(ROK);
   } /* if ( endpCb == (SbSctEndpCb *) NULLP ) */
   else
   {
      Bool duplicateAddr = FALSE;
      /* compare if there is any address change */
#ifdef SCT_ENDP_MULTI_IPADDR
      U8 commonAddr = 0;
      for ( i = 0; i < intfNAddrLst->nmb; i++ )
      {
         for ( j = 0; j < endpCb->localAddrLst.nmb; j++ )
         {
            if (cmMemcmp((U8 *) &(intfNAddrLst->nAddr[i]), 
                         (U8 *) &(endpCb->localAddrLst.nAddr[j]), 
                         sizeof(CmNetAddr)) == 0)
            {
               commonAddr++;
               break;
            }
         }
      }
      if (commonAddr == intfNAddrLst->nmb)
      {
         duplicateAddr = TRUE;
      }
#else /* SCT_ENDP_MULTI_IPADDR */
      SB_CPY_NADDR(&(tmpAddr), intfNAddr);
      if (cmMemcmp((U8 *) &tmpAddr, (U8 *) &(endpCb->localAddrLst.nAddr[0]), 
                   sizeof(CmNetAddr)) == 0)
      {
         duplicateAddr = TRUE;
      }
#endif /* SCT_ENDP_MULTI_IPADDR */

      /* sb006.102: Updation - modified for alignment */
      if ( (endpCb->spId != spId) ||
           (endpCb->port != port) ||
           (duplicateAddr != TRUE) )
      {
         /* if we are here then the endpoint is trying to be reopened with
          * different values */

#if (ERRCLASS & ERRCLS_INT_PAR)
         SBLOGERROR(ERRCLS_INT_PAR, ESB029, (ErrVal)0,
                    "SbUiSctEndpOpenReq: trying to reopen endpoint");
#endif

         SbUiSctEndpOpenCfm( &(sctSap->sctPst), sctSap->suId, suEndpId,
                             spEndpId, SCT_NOK, SCT_CAUSE_ENDP_OPEN);
         RETVALUE(RFAILED);
      }
      else
      {
/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
         if (endpCb->timer.tmrEvnt == TMR_NONE)
#endif
         SbUiSctEndpOpenCfm( &(sctSap->sctPst), sctSap->suId, suEndpId,
                             spEndpId, SCT_OK, SCT_CAUSE_NOT_APPL);
      }
   }
   RETVALUE(ROK);
}/* SbUiSctEndpOpenReq() */

/*
*
*       Fun:   SbUiSctEndpCloseReq
*
*       Desc:  Primitive to Close an Endpoint Server.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: This function closes an endpoint on the SCTP Layer.
*
*       File:  sb_bdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 SbUiSctEndpCloseReq
(
Pst           *pst,              /* Post structure */
SpId           spId,             /* Service provider Id */
UConnId        endpId,           /* endpoint ID */
U8             endpIdType        /* service user/provider */
)
#else
PUBLIC S16 SbUiSctEndpCloseReq(pst, spId, endpId, endpIdType)
Pst           *pst;              /* Post structure */
SpId           spId;             /* Service provider Id */
UConnId        endpId;           /* endpoint ID */
U8             endpIdType;       /* service user/provider */
#endif
{
   /* local parameters */
   U32            i;
   SbSctEndpCb   *endpCb;
   SbSctSapCb    *sctSap;
   SbSctAssocCb  *assocCb;
   S16            ret;
   /* patch sb009.102 for endpoint close problem */
   U32            endpIndex;
   Bool           endpFound;
   /* sb068.102 for sending suEndpId in SbUiSctEndpCloseCfm if endpIdType = SCT_ENDPID_SP */ 
   /*sb084.102: Compilation warning*/
   UConnId        suEndpId=0;
/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   SbLocalAddrCb  *localAddrCb;
   SbTSapCb       *tSapCb;
   CmTptParam     tPar;
#endif

   TRC3(SbUiSctEndpCloseReq)

#ifdef SS_MULTIPLE_PROCS

   if(SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                         (void **)&sbGlobalCbPtr) != ROK)
   {
     SBLOGERROR(ERRCLS_DEBUG, ESB030, 0,
               "SbUiSctEndpCloseReq () failed, cannot derive sbGlobalCbPtr");
     RETVALUE(FALSE);
   }

   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
         "-------SCTP------(proc(%d), ent(%d), inst(%d))--------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));

#endif /* SS_MULTIPLE_PROCS */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctEndpCloseReq(pst, spId(%d), endpId(%d), endpIdType(%d))\n",
          spId, endpId, endpIdType));
#else
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctEndpCloseReq(pst, spId(%d), endpId(%ld), endpIdType(%d))\n",
          spId, endpId, endpIdType));
#endif /* BIT_64 */
#ifndef SS_MULTIPLE_PROCS
   UNUSED(pst);
#endif  /* SS_MULTIPLE_PROCS */

   /* patch sb009.102 for endpoint close problem */
   endpIndex = 0;
   endpFound = FALSE;

   /* check the SpId. *
    *sb081.102: Removing the check out of ERRCLASS*/
   SB_CHK_SPID(spId, LCM_EVENT_UI_INV_EVT, ret);

   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB031, (ErrVal)spId,
                 "SbUiSctEndpCloseReq: Invalid spId");
#endif /* ERRCLS_INT_PAR */
      RETVALUE(RFAILED);
   }

   /* get the SAP to operate on */
   sctSap = sbGlobalCb.sctSaps[spId];
   endpCb = (SbSctEndpCb *)NULLP;

   /* check the endpIdType *
    *sb081.102: Removing the check out of ERRCLASS*/
   if ( (endpIdType != SCT_ENDPID_SU) && (endpIdType != SCT_ENDPID_SP) )
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB032, (ErrVal)endpIdType,
                 "SbUiSctEndpCloseReq: Invalid endpIdType");
#endif /* ERRCLS_INT_PAR */
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
      SB_LM_GEN_ALARM(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT, \
                   LCM_CAUSE_INV_PAR_VAL, spId, LSB_SW_RFC_REL0);
      RETVALUE(RFAILED);
   }

   if ( endpIdType == SCT_ENDPID_SP )
   {

      /* check if the endpoint exists *
       *sb081.102:Removing the check out of ERRCLASS*/
      SB_CHK_SPENDPID(endpId, ret)
      if ( ret !=ROK )
      {
#if (ERRCLASS & ERRCLS_INT_PAR)
         SBLOGERROR(ERRCLS_INT_PAR, ESB033, (ErrVal)endpId,
                    "SbUiSctEndpCloseReq: Invalid spEndpId");
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */
      /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */    
         SB_LM_GEN_ALARM(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT, \
                      LCM_CAUSE_INV_PAR_VAL, spId, LSB_SW_RFC_REL0);
         RETVALUE(RFAILED);
      }

      /* get the endpoint control block */
      endpCb = sbGlobalCb.endpCb[endpId];
      /* sb017.102: Endpoint close problem while using multiple endpoint */
      endpFound = TRUE;
      endpIndex = endpId;

      /* sb068.102 for sending suEndpId in SbUiSctEndpCloseCfm if endpIdType = SCT_ENDPID_SP */ 
      suEndpId = endpCb->suEndpId;
   }
   else /* assocIdType == SCT_ENDPID_SU */
   {

      /* find an open endpoint with a matching spId and suEndpId */
      /* patch sb009.102 for endpoint close problem */
      for ( i = 0; (i < sbGlobalCb.genCfg.maxNmbEndp) && (endpFound == FALSE); i++ )
      {
         if ( sbGlobalCb.endpCb[i] != (SbSctEndpCb *) NULLP )
         {
            endpCb = sbGlobalCb.endpCb[i];
            if ( (endpCb->suEndpId == endpId) && (endpCb->spId == spId) )
            {
               /* if we are here then the endpoint exists */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
               SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                  "SbUiSctEndpCloseReq: endpoint exists for suEndpId(%d) and spId(%d)\n",
                  endpId, spId));
#else
               SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                  "SbUiSctEndpCloseReq: endpoint exists for suEndpId(%ld) and spId(%d)\n",
                  endpId, spId));
#endif /* BIT_64 */

               /* patch sb009.102 for endpoint close problem */
               endpFound = TRUE;
               endpIndex = i;
            }
         }
      }

      /* patch sb009.102 for endpoint close problem */
      if ( !endpFound )
      {
         /* endpoint isn't open yet */
         /* send confirm */
         SbUiSctEndpCloseCfm( &(sctSap->sctPst), sctSap->suId, endpId,
                              SCT_OK, SCT_CAUSE_NOT_APPL);
         RETVALUE(ROK);
      }
   }

   /* if we are here then a matching endpoint was found and we must close it */

   /* abort and remove all associations on this endpoint */
   for ( i = 0; i < sbGlobalCb.genCfg.maxNmbAssoc; i++ )
   {
      assocCb = sbGlobalCb.assocCb[i];
      if ( assocCb != (SbSctAssocCb *) NULLP )
      {
         if ( assocCb->endpId == endpId )
         {
            ret = sbAsAbortAssoc(assocCb, TRUE);

            sbGlobalCb.assocCb[i] = (SbSctAssocCb *) NULLP;
            SB_FREE(sizeof(SbSctAssocCb), assocCb);

            if ( ret != ROK )
            {
               /* could not send ABORT chunk */
               SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                      "SbUiSctEndpCloseReq: could not send ABORT chunk\n"));
               if ( ret == ROUTRES )
               {
                  /* send alarm since the abort request is still being
                   * processed and we cant send a negative confirm *
                  *sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
                  SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, \
                               LCM_EVENT_DMEM_ALLOC_FAIL,\
                               LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
               }
               /* continue anyway */
            }
         }
      }
   }

   /* remove the endpoint from the hash list, array and free its memory */
   if (endpCb != (SbSctEndpCb *)NULLP)
   {
      /* sb046.102: Multiple IP address per Endp */
      for ( i = 0; i < endpCb->localAddrLst.nmb; i++ )
      {
         SbAddrPortCb *tmpAddrPortCb=NULLP;
         SbAddrPortEntry tmpAddrPortEntry;

         /* sb048.102: memset tmpAddrPortEntry to zero  */
         cmMemset((U8 *)&tmpAddrPortEntry, 0, sizeof(SbAddrPortEntry));
         tmpAddrPortEntry.port = endpCb->port;
         SB_CPY_NADDR(&(tmpAddrPortEntry.localAddr), &(endpCb->localAddrLst.nAddr[i]));

         /* sb048.102: Pass the address of tmpAddrPrtCb */
         ret = cmHashListFind(&(sbGlobalCb.addrPortHl),
                              (U8 *) &(tmpAddrPortEntry),
                              (U16) sizeof(SbAddrPortEntry), 0,
                              (PTR *) &tmpAddrPortCb);
#if (ERRCLASS & ERRCLS_INT_PAR)
         if (ret != ROK)
         {
            SBLOGERROR(ERRCLS_INT_PAR, ESB034, (ErrVal)0,
               "SbUiSctEndpCloseReq: Invalid interface address/port, "
               "no addr/port found ");
            /* sb049 : If the hash list find fails */
            SbUiSctEndpCloseCfm( &(sctSap->sctPst), sctSap->suId, endpId,
                              SCT_NOK, SCT_CAUSE_NOT_APPL);
            RETVALUE(RFAILED);
         }
#endif /* ERRCLASS & ERRCLS_INT_PAR */
         if (tmpAddrPortCb != (SbAddrPortCb *)NULLP)
         {
/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
            localAddrCb = tmpAddrPortCb->localAddrCb;

            if (localAddrCb != NULLP)
            {
               tSapCb = sbGlobalCb.tSaps[localAddrCb->suId];

               SB_ZERO(&tPar, sizeof(CmTptParam));
               tPar.type = CM_TPTPARAM_NOTPRSNT;

               /* send the disconnect request */
               ret = SbLiHitDiscReq( &(tSapCb->tPst),
                         tSapCb->tSapCfg.reConfig.spId,
                         HI_USER_CON_ID, localAddrCb->suConId,
                         HI_CLOSE, &tPar );
               if (ret != ROK)
               {
                  SBLOGERROR(ERRCLS_INT_PAR, ESB034, (ErrVal)0,
                     "SbUiSctEndpCloseReq: failed to send disconnect request\n");
                  SbUiSctEndpCloseCfm( &(sctSap->sctPst), sctSap->suId, endpId,
                                    SCT_NOK, SCT_CAUSE_NOT_APPL);
                  RETVALUE(RFAILED);
               }

               tmpAddrPortCb->localAddrCb = NULLP;

   
               /* delete the local address control block */
               sbGlobalCb.localAddrCb[localAddrCb->suConId] = (SbLocalAddrCb *)NULLP;
               SB_FREE( sizeof(SbLocalAddrCb), localAddrCb )
            }
            else
            {
               SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                  "SbUiSctEndpCloseReq: local connection is already deleted\n"));
            }
#endif

            ret = cmHashListDelete(&(sbGlobalCb.addrPortHl), (PTR) tmpAddrPortCb);
         }

#if (ERRCLASS & ERRCLS_DEBUG)
         if ( ret == RFAILED )
         {
            /* couldn't delete endpoint from hashlist */
            SBLOGERROR(ERRCLS_DEBUG, ESB035, (ErrVal)ret,
                 "SbUiSctEndpCloseReq: could not delete endpoint from HL");
            /* sb049 : If the hash list delete fails */
            SbUiSctEndpCloseCfm( &(sctSap->sctPst), sctSap->suId, endpId,
                              SCT_NOK, SCT_CAUSE_NOT_APPL);
            RETVALUE(RFAILED);
         }
#endif /* ERRCLS_DEBUG */
         SB_FREE(sizeof(SbAddrPortCb), tmpAddrPortCb);
      }
   }

   /* patch sb009.102 for endpoint close problem */
   sbGlobalCb.endpCb[endpIndex] = (SbSctEndpCb *) NULLP;
   SB_FREE(sizeof(SbSctEndpCb), endpCb);

   /* sb068.102 for sending suEndpId in SbUiSctEndpCloseCfm if endpIdType = SCT_ENDPID_SP */  
   if ( endpIdType == SCT_ENDPID_SP )
   {
      /* send confirm */
      SbUiSctEndpCloseCfm( &(sctSap->sctPst), sctSap->suId, suEndpId,
                        SCT_OK, SCT_CAUSE_NOT_APPL);
   }
   else /* if ( endpIdType == SCT_ENDPID_SU ) */
   {
      /* send confirm */
      SbUiSctEndpCloseCfm( &(sctSap->sctPst), sctSap->suId, endpId,
                        SCT_OK, SCT_CAUSE_NOT_APPL);
   }
   RETVALUE(ROK);

} /* SbUiSctEndpCloseReq() */

/*
*
*       Fun:   SbUiSctAssocReq
*
*       Desc:  Primitive to Open an Association
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: This function tries to establish an association with a peer.
*              Termination indications are sent if something goes wrong.
*
*       File:  sb_bdy1.c
*
*/

/* sb021.102: Modification for TOS parameter */
#ifdef SCT3
#ifdef ANSI
PUBLIC S16 SbUiSctAssocReq
(
Pst           *pst,              /* Post structure */
SpId           spId,             /* Service provider Id */
UConnId        spEndpId,         /* Service provider Endpoint ID */
UConnId        suAssocId,        /* Service user Association ID */
CmNetAddr     *priDstNAddr,      /* Primary destination network address */
SctPort        dstPort,          /* Destination port number */
SctStrmId      outStrms,         /* no. outgoing streams */
SctNetAddrLst *dstNAddrLst,      /* destination network address list */
SctNetAddrLst *srcNAddrLst,      /* source network address list */
SctTos         tos,              /* TOS Parameter */
Buffer        *vsInfo            /* VsInfo - not used anymore */
)
#else
PUBLIC S16 SbUiSctAssocReq(pst, spId, spEndpId, suAssocId, priDstNAddr,
                           dstPort, outStrms, dstNAddrLst, srcNAddrLst, 
                           tos, vsInfo)
Pst           *pst;              /* Post structure */
SpId           spId;             /* Service provider Id */
UConnId        spEndpId;         /* Service provider Endpoint ID */
UConnId        suAssocId;        /* Service user Association ID */
CmNetAddr     *priDstNAddr;      /* Primary destination network address */
SctPort        dstPort;          /* Destination port number */
SctStrmId      outStrms;         /* no. outgoing streams */
SctNetAddrLst *dstNAddrLst;      /* destination network address list */
SctNetAddrLst *srcNAddrLst;      /* source network address list */
SctTos         tos;              /* TOS Parameter */
Buffer        *vsInfo;           /* VsInfo - not used anymore */
#endif /* ANSI */
#else
#ifdef ANSI
PUBLIC S16 SbUiSctAssocReq
(
Pst           *pst,              /* Post structure */
SpId           spId,             /* Service provider Id */
UConnId        spEndpId,         /* Service provider Endpoint ID */
UConnId        suAssocId,        /* Service user Association ID */
CmNetAddr     *priDstNAddr,      /* Primary destination network address */
SctPort        dstPort,          /* Destination port number */
SctStrmId      outStrms,         /* no. outgoing streams */
SctNetAddrLst *dstNAddrLst,      /* destination network address list */
SctNetAddrLst *srcNAddrLst,      /* source network address list */
Buffer        *vsInfo            /* VsInfo - not used anymore */
)
#else
PUBLIC S16 SbUiSctAssocReq(pst, spId, spEndpId, suAssocId, priDstNAddr,
                           dstPort, outStrms, dstNAddrLst, srcNAddrLst, 
                           vsInfo)
Pst           *pst;              /* Post structure */
SpId           spId;             /* Service provider Id */
UConnId        spEndpId;         /* Service provider Endpoint ID */
UConnId        suAssocId;        /* Service user Association ID */
CmNetAddr     *priDstNAddr;      /* Primary destination network address */
SctPort        dstPort;          /* Destination port number */
SctStrmId      outStrms;         /* no. outgoing streams */
SctNetAddrLst *dstNAddrLst;      /* destination network address list */
SctNetAddrLst *srcNAddrLst;      /* source network address list */
Buffer        *vsInfo;           /* VsInfo - not used anymore */
#endif /* ANSI */
#endif /* SCT3 */
{
   /* local parameters */
   U32            i;
   SbSctEndpCb   *endpCb;
   UConnId        spAssocId;
   SbSctSapCb    *sctSap;
   SbSctAssocCb  *assocCb;
   S16            ret;
   SctRtrvInfo    rtrv;
   /* sb004.12 - addition : Added to check the retvalue of sbPmAddAddr */
   SbAddrCb       *addrCb;
   /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
   Bool           addrIpv4;
#endif /* SCT3 */
   /* Patch sb031.102 IPV6 Support Added */
   U32            addrCount;
   /* sb049.102: Warnings removed */
#ifdef SB_IPV6_SUPPORTED
   Bool           isAny; 
#endif /* SB_IPV6_SUPPORTED */
   /* RFC 4460 -- moved up to remove the warning */ 
   /* sb086.102: Accessing TSAP initially was done inside the source address check.*/
   SbTSapCb          *tSap;                     /* local variable */

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   CmNetAddr           tmpAddr1;
   SbDstAddrCb        *dstAddr;
   SbPathProfCb        *pathProf;
#endif /* SB_SATELLITE */
/* sb009.103:IPV4IP6 changes */
#ifdef SB_IPV4IPV6_COMBINED
   U32            j;
#endif

   TRC3(SbUiSctAssocReq)

#ifdef SS_MULTIPLE_PROCS

   if(SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                         (void **)&sbGlobalCbPtr) != ROK)
   {
     SBLOGERROR(ERRCLS_DEBUG, ESB036, 0,
               "SbUiSctAssocReq () failed, cannot derive sbGlobalCbPtr");
     RETVALUE(FALSE);
   }

   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
         "-------SCTP------(proc(%d), ent(%d), inst(%d))--------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));

#endif /* SS_MULTIPLE_PROCS */

   /* SCTPv13 - vendor specific information removed */

/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctAssocReq(pst, spId(%d), spEndpId(%d), suAssocId(%d), \
          priDstNAddr, dstPort(%d), outStrms(%d), dstNAddrLst, srcNAddrLst, \
          sInfo)\n",
          spId, spEndpId, suAssocId, dstPort, outStrms));
#else
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctAssocReq(pst, spId(%d), spEndpId(%ld), suAssocId(%ld), \
          priDstNAddr, dstPort(%d), outStrms(%d), dstNAddrLst, srcNAddrLst, \
          sInfo)\n",
          spId, spEndpId, suAssocId, dstPort, outStrms));
#endif /* BIT_64 */

#ifndef SS_MULTIPLE_PROCS
   UNUSED(pst);
#endif  /* SS_MULTIPLE_PROCS */
   SB_CHK_PUTMSG(vsInfo);

   /* SCTP Upgrade: Taking out for robustness */
   /* check the SpId. */
   SB_CHK_SPID(spId, LCM_EVENT_UI_INV_EVT, ret);
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB037, (ErrVal)spId,
                 "SbUiSctAssocReq: Invalid spId");

#endif /* ERRCLS_INT_PAR */
      RETVALUE(RFAILED);
   }

   /* get the SAP to operate on */
   sctSap = sbGlobalCb.sctSaps[spId];

   SB_ZERO(&rtrv, sizeof(SctRtrvInfo));

   /* SCTP Upgrade: Taking out for robustness */
   /* check if the endpoint exists */
   SB_CHK_SPENDPID(spEndpId, ret)
   if ( ret != ROK )
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB038, (ErrVal)spEndpId,
                 "SbUiSctAssocReq: Invalid spEndpId");

#endif /* (ERRCLASS & ERRCLS_INT_PAR) */
      SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId, suAssocId,
                      SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_INV_PAR_VAL,
                      &rtrv);
      RETVALUE(RFAILED);
   }

   /* get the endpoint control block */
   endpCb = sbGlobalCb.endpCb[spEndpId];
   
   /* sb020.103: If number of addresses in list exceed the limit, send TermInd */
#if (ERRCLASS & ERRCLS_INT_PAR)
   if( srcNAddrLst->nmb > SCT_MAX_NET_ADDRS ) 
   {
      SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
         "SbUiSctAssocReq:Number of Addresses exceed max limit of %d\n",
          SCT_MAX_NET_ADDRS));
 
      SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId, suAssocId,
                      SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_INV_PAR_VAL,
                      &rtrv);
      
      RETVALUE(RFAILED);
   }

   /* sb020.103: NULL check for priDstNAddr */
   if( priDstNAddr == (CmNetAddr *)NULLP )
   {
      SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
         "SbUiSctAssocReq: priDstNAddr is NULL\n" ));
     
      SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId, suAssocId,
                      SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_INV_PAR_VAL,
                      &rtrv);

      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

/* sb005.103: Move the sanity checks outside ERRCLASS */
   /* check the out streams parameter */
#ifndef S1SIMAPP
   if ( (outStrms > sbGlobalCb.genCfg.maxNmbOutStrms) || (outStrms == 0) )
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB039, (ErrVal)outStrms,
                 "SbUiSctAssocReq: Invalid outStrm");
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */

      SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId, suAssocId,
                      SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_INV_PAR_VAL,
                      &rtrv);
      RETVALUE(RFAILED);
   }
#endif
   /* check to see if association ID exists */
   for ( i = 0; i < sbGlobalCb.genCfg.maxNmbAssoc; i++ )
   {
      assocCb = sbGlobalCb.assocCb[i];
      if ( assocCb != (SbSctAssocCb *) NULLP )
      {
         /* sb020.102: suAssocId should be unique per SAP */
         if ( ( assocCb->suAssocId == suAssocId ) && (assocCb->spId == spId) )
         {
            /* the association already exists */

#if (ERRCLASS & ERRCLS_INT_PAR)
            SBLOGERROR(ERRCLS_INT_PAR, ESB040, (ErrVal)suAssocId,
                       "SbUiSctAssocReq: Invalid association ID");
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */

/* sb028.103: Send StaInd to the SCTP user layer if duplicate association 
              request is received */

#ifdef SCT7
            SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,\
                  assocCb->spAssocId, priDstNAddr,\
                  SCT_STATUS_DUP_ASSOC, SCT_CAUSE_NOT_APPL, SCT_PROTID_NONE ,\
                  (Buffer *) NULLP);
#else
            SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,\
                  assocCb->spAssocId, priDstNAddr,\
                  SCT_STATUS_DUP_ASSOC, SCT_CAUSE_NOT_APPL,\
                  (Buffer *) NULLP);
#endif
            SB_LM_GEN_ALARM(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT, \
                  LCM_CAUSE_INV_PAR_VAL, spId, LSB_SW_RFC_REL0);
            RETVALUE(RFAILED);

         }
      }
   }

   /* check the primary destination transport address */
   SB_CHK_DTA(spEndpId, priDstNAddr, dstPort, ret);
   if ( ret == ROK )
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB041, (ErrVal)0,
                 "SbUiSctAssocReq: primary destination address overlaps");
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */

      SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId, suAssocId,
                      SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_INV_PAR_VAL,
                      &rtrv);
      RETVALUE(RFAILED);
   }

   /* check the destination address list to see if DTA is already in use*/
   for ( i = 0; i < dstNAddrLst->nmb; i++ )
   {
      SB_CHK_DTA(spEndpId, &(dstNAddrLst->nAddr[i]), dstPort, ret);
      if ( ret == ROK )
      {
#if (ERRCLASS & ERRCLS_INT_PAR)
         /* the DTA exists if we are here */
         SBLOGERROR(ERRCLS_INT_PAR, ESB042, (ErrVal)0,
                    "SbUiSctAssocReq: overlap in destination address list");
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */

         SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId, suAssocId,
                         SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_INV_PAR_VAL,
                         &rtrv);
         RETVALUE(RFAILED);
      }
   }

   /* find the first unused association entry in the array */
   i = 0;
   while ( (i < sbGlobalCb.genCfg.maxNmbAssoc) &&
           (sbGlobalCb.assocCb[i] != (SbSctAssocCb *) NULLP) )
   {
      i++;
   }
   spAssocId = i;

   /* see if there is space for a new association */
   if ( spAssocId == sbGlobalCb.genCfg.maxNmbAssoc )
   {
      /* association array full */
      SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
             "SbUiSctAssocReq: config. max reached for number of assocs\n"));

      SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId, suAssocId,
                      SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_OUTRES,
                      &rtrv);
      RETVALUE(RFAILED);
   }

   /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
   /* tos parameter is supported only in IPV4 */
   addrIpv4 = TRUE;  
   for ( i = 0; i < srcNAddrLst->nmb; i++ )
      if ( srcNAddrLst->nAddr[i].type != CM_NETADDR_IPV4 )
         addrIpv4 = FALSE;

   if ( addrIpv4 == FALSE )
   {
      /* address type is not IPV4 */
      SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
             "SbUiSctAssocReq: tos parameter supportd only in IPV4\n"));

      SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId, suAssocId,
                      SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_INV_PAR_VAL,
                      &rtrv);
      RETVALUE(RFAILED);
   }
#endif /* SCT3 */

   /* create new association control block */
   SB_ALLOC(sizeof(SbSctAssocCb), assocCb, ret);
   if ( ret != ROK )
   {
      SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
             "SbUiSctAssocReq: could not allocate new association\n"));

      SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId, suAssocId,
                      SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_OUTRES,
                      &rtrv);
      RETVALUE(RFAILED);
   }

   assocCb->spId        = spId;
   assocCb->endpId      = spEndpId;
   assocCb->suAssocId   = suAssocId;
   assocCb->spAssocId   = spAssocId;
   assocCb->assocState  = SB_ST_CLOSED;
   /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
   assocCb->tos         = tos; 
#endif /* SCT3 */
   assocCb->peerInitTag = 0;
   sbRand32(0, &(assocCb->ownInitTag));
/* sb030.103:  Added to support 64 Bit compilation.  */
#ifdef BIT_64
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctAssocReq: assocCb->ownInitTag=%u\n",
           assocCb->ownInitTag));
#else
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctAssocReq: assocCb->ownInitTag=%lu\n",
           assocCb->ownInitTag));
#endif /* BIT_64 */
   /* sb006.102: Updation - modified for alignment */
   /* sb046.102: Multiple IP address per Endp */
   assocCb->localPort   = endpCb->port;
   assocCb->peerPort    = dstPort;

   /* RFC 4460 */
   /* Generate the tie-tags */
   sbRand32(SB_RAND_GEN, &(assocCb->localTieTag));
   sbRand32(SB_RAND_GEN, &(assocCb->peerTieTag));

   /* get the local address control block */
   SB_GET_LOCAL_CONN(spEndpId, assocCb->localConn, ret);
/* sb019.103: Fix for the ERRCLASS issue */
   if ( ret != ROK )
   {
      SB_FREE(sizeof(SbSctAssocCb), assocCb);

#if ( ERRCLASS & ERRCLS_DEBUG )
      SBLOGERROR(ERRCLS_DEBUG, ESB043, (ErrVal)0,
                 "SbUiSctAssocReq: could not find local address CB in HL");
#endif /* ERRCLS_DEBUG */
      SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId, suAssocId,
                      SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_UNKNOWN,
                      &rtrv);
      RETVALUE(RFAILED);
   }
#ifdef S1SIMAPP
   assocCb->sbSqCb.nmbOutStreams   = sbGlobalCb.genCfg.maxNmbOutStrms;/*outStrms;*/
#else
   assocCb->sbSqCb.nmbOutStreams   = outStrms;
#endif
   assocCb->sbSqCb.nmbInStreams    = sbGlobalCb.genCfg.maxNmbInStrms;
   assocCb->sbSqCb.inStreamSeqNum  = (SctStrmId *) NULLP;
   assocCb->sbSqCb.outStreamSeqNum = (SctStrmId *) NULLP;
   /* sb033.103 : Initialized the sbSqCb.rcvfrag to null under SB_FRAG_TSN_CHK flag.*/ 
#ifdef SB_FRAG_TSN_CHK
   assocCb->sbSqCb.rcvfrag         = (SctStrmId *) NULLP;   
#endif

   assocCb->sbAcCb.nextLocalTsn = assocCb->ownInitTag;
   assocCb->sbAcCb.cumTsn       = assocCb->ownInitTag - 1;
   assocCb->sbAcCb.cumPeerTsn   = 0;
   /* sb020.102: Double SACK problem */
   assocCb->sbAcCb.cumPeerTsnAcked   = 0;
   assocCb->sbAcCb.rwnd         = 0;
   assocCb->sbAcCb.rtxCnt       = 0;
   assocCb->sbAcCb.sinceSack    = sctSap->sctSapCfg.reConfig.maxAckDelayDg - 1;
   assocCb->sbAcCb.bytesOut     = 0;
   assocCb->sbAcCb.pri          = (SbAddrCb *) NULLP;
   assocCb->sbAcCb.tsnLstSz     = 0;
   assocCb->sbAcCb.rcvDupTsnFlg = FALSE;
   assocCb->sbAcCb.dupTsnLstSz  = 0;
   assocCb->sbAcCb.ownRWnd      = sbGlobalCb.genCfg.initARwnd;
   /* RFC 4460 section 2.8: fast retransmission */
   assocCb->sbAcCb.fastRecFlg   = FALSE;
   assocCb->sbAcCb.fastRecExtPt = 0;
   /* sb015.102: DNS timer problem */
   assocCb->sbDnsCb.dnsTmrInit  = FALSE;
   /* RFC 4460 section 2.15: receiver's SWS avoidance */
#ifdef SB_SWS
   assocCb->sbAcCb.reduction    = 0;
#endif 
   /* RFC 4460 section 2.15: zero window probing */
   assocCb->sbAcCb.zeroWndP     = FALSE;
   assocCb->sbAcCb.zWndPLastTsnRcvd = 0;
/* SB_SCTP_3 */
/* sb013.103: Dual Checksum Fix */
#if defined (SB_CHECKSUM_CRC)
   assocCb->checksumType        = SB_CRC32;
#elif defined (SB_CHECKSUM_DUAL)
   assocCb->checksumType        = sctSap->sctSapCfg.reConfig.checksumType; 
#else
    assocCb->checksumType       = SB_ADLER32;
#endif
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
   assocCb->sbAcCb.ecnFlg       = FALSE;
#endif /* SB_ECN */

   /* Initialize the ack delay timer */
   cmInitTimers(&(assocCb->sbAcCb.ackDelayTmr), 1);
#ifdef LSB4
   /* Initialize the bundle delay timer */
   cmInitTimers(&(assocCb->sbAsCb.bundleTimer), 1);
#endif/* LSB4 */
   /* sb005.103: Initialize the T5-ShutdownGuard timer */
   cmInitTimers(&(assocCb->sbAsCb.t5SdownGrdTmr), 1);

   /* Initialize the address linked lists */
   (Void) cmLListInit(&(assocCb->sbAcCb.addrLst));
   
   if ( assocCb->localConn == NULLP)
   {
      SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
             "SbUiSctAssocReq: assocCb->localConn is NULL\n"));
      RETVALUE(RFAILED);
   }
   tSap = sbGlobalCb.tSaps[assocCb->localConn->suId];


   /* source network address list stuff */
   /* sb086.102: IP_ANY changes*/ 

   if (( srcNAddrLst->nmb == 0) || (( srcNAddrLst->nmb == 1) && (tSap->ipv4_any == TRUE)))
   {
      /* User didn't specify so use endpoint configured value */
      /* sb046.102: Multiple IP address per Endp. If IP_ANY is used, only one
       * IP address is in the Endpoint address list */
      if ( (endpCb->localAddrLst.nmb == 1 ) &&
           (endpCb->localAddrLst.nAddr[0].type == CM_NETADDR_IPV4) &&
           (endpCb->localAddrLst.nAddr[0].u.ipv4NetAddr == 0) )
      {

         if (sbGlobalCb.genCfg.useHstName  == TRUE) 
         {
            /* If useHstName is TRUE, then set localAddrLst to 0 */
            assocCb->sbAsCb.localAddrLst.nmb=0;
            /* sb087.102: Host name changes*/
            assocCb->sbAsCb.localAddrLst.nAddr[0].type = CM_NETADDR_IPV4;
            assocCb->sbAsCb.localAddrLst.nAddr[0].u.ipv4NetAddr = 0;
            assocCb->incldHstName  = TRUE;
         }
         else
         {
            /* Patch sb031.102 IPV6 Support Added */
            /* copy the src address list */
            for(addrCount=0; addrCount < tSap->tSapCfg.srcNAddrLst.nmb; addrCount++)
            {
               if(tSap->tSapCfg.srcNAddrLst.nAddr[addrCount].type == CM_NETADDR_IPV4)
               {
         /*sb080.102:Adjusting the macro call to single line*/
                   SB_CPY_NADDR(&(assocCb->sbAsCb.localAddrLst.nAddr[assocCb->sbAsCb.localAddrLst.nmb]), \
            &(tSap->tSapCfg.srcNAddrLst.nAddr[addrCount]));
                   assocCb->sbAsCb.localAddrLst.nmb++;
               }
           }

           /* remove the last address if this is TSAP 0 because then 
            * the last address is IP_ANY */
            /* Patch sb031.102 IPV6 Support Added */
           /* if (tSap->ipv4_any == TRUE)*/
           /* sb046.102: Multiple IP address per Endp.*/
            if ((tSap->ipv4_any == TRUE) && (assocCb->localConn->suId == 0)) 
            {
              /* sb002.12 : check nmb==0 case before decrementing it */
              if (assocCb->sbAsCb.localAddrLst.nmb > 0)
              {
                 assocCb->sbAsCb.localAddrLst.nmb--;
              }
            }

         }
      }
      /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
      /* Copy the IPV6 addresses from TSAP configuration */
      else if ( (endpCb->localAddrLst.nmb == 1 ) &&
                (endpCb->localAddrLst.nAddr[0].type == CM_NETADDR_IPV6) )
      {
         SB_INET6_ISANY(endpCb->localAddrLst.nAddr[0].u.ipv6NetAddr, &isAny)
         if(isAny == TRUE)
         {
/* sb005.103: Removed multiple tSap declaration - compilation warning */

         /* IP_ANY so fill in the config. values for the TSAP */

         if (sbGlobalCb.genCfg.useHstName  == TRUE) 
         {
            /* If useHstName is TRUE, then set localAddrLst to 0 */
            assocCb->sbAsCb.localAddrLst.nmb=0;
            /* sb087.102: Host name changes*/
            SB_CPY_NADDR(&(assocCb->sbAsCb.localAddrLst.nAddr[0]),(CmNetAddr *)NULLP);
            assocCb->sbAsCb.localAddrLst.nAddr[0].type = CM_NETADDR_IPV6;
            assocCb->incldHstName  = TRUE;
         }
         else
         {
            /* copy the src address list */
            for(addrCount=0; addrCount < tSap->tSapCfg.srcNAddrLst.nmb; addrCount++)
            {
               if(tSap->tSapCfg.srcNAddrLst.nAddr[addrCount].type == CM_NETADDR_IPV6)
               {
         /*sb080.102:Adjusting the macro call to single line*/
                   SB_CPY_NADDR(&(assocCb->sbAsCb.localAddrLst.nAddr[assocCb->sbAsCb.localAddrLst.nmb]), \
                         &(tSap->tSapCfg.srcNAddrLst.nAddr[addrCount]));
                   assocCb->sbAsCb.localAddrLst.nmb++;
               }
          }

           /* remove the last address if this is TSAP 0 because then 
            * the last address is IP_ANY */
           /* if (assocCb->localConn->suId == 0) */
            if (tSap->ipv6_any == TRUE)
            {
              if (assocCb->sbAsCb.localAddrLst.nmb > 0)
              {
                 assocCb->sbAsCb.localAddrLst.nmb--;
              }
            }

         }
       }
      }
#endif
      else
      {
         /* sb046.102: Multiple IP address per Endp. *
    *sb080.102:Adjusting the macro call to single line*/
         SB_CPY_NADDRLST(&(assocCb->sbAsCb.localAddrLst), &(endpCb->localAddrLst));
      }
   }
   else
   {
      /* use the user supplied addresses *
       *sb080.102: If the source address list received is different from endpCb.localAddrlst*/
      SB_CPY_NADDR(&(assocCb->sbAsCb.localAddrLst.nAddr[0]), &(assocCb->localConn->ownAddr));
      assocCb->sbAsCb.localAddrLst.nmb++;

      for ( i = 0; i < srcNAddrLst->nmb; i++)
      {
            if( srcNAddrLst->nAddr[i].u.ipv4NetAddr != assocCb->localConn->ownAddr.u.ipv4NetAddr)
            {
             SB_CPY_NADDR(&(assocCb->sbAsCb.localAddrLst.nAddr[assocCb->sbAsCb.localAddrLst.nmb]), &(srcNAddrLst->nAddr[i]));
             assocCb->sbAsCb.localAddrLst.nmb++;

            }
      }

   }

   /* sb009.103: IP4IPv6 changes: verify that at least one address in source
    *  and destination address lists  shall have same address type 
    */
#ifdef SB_IPV4IPV6_COMBINED
   if (assocCb->incldHstName != TRUE)
   {
      for (i = 0; i < assocCb->sbAsCb.localAddrLst.nmb; i++)
	 if (priDstNAddr->type == assocCb->sbAsCb.localAddrLst.nAddr[i].type)
	    break;

      if (i == assocCb->sbAsCb.localAddrLst.nmb)
      {
	 for (i = 0; i < assocCb->sbAsCb.localAddrLst.nmb; i++)
	 {
	    for (j = 0; j < dstNAddrLst->nmb; j++)
	    {
	       if (dstNAddrLst->nAddr[j].type == assocCb->sbAsCb.localAddrLst.nAddr[i].type)
		  break;
	    }
            if (j != dstNAddrLst->nmb)
               break;
	 }
      }

      if (i == assocCb->sbAsCb.localAddrLst.nmb)
      {
	 SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
		  "SbUiSctAssocReq: src addr list and dst addr list don't have single address of same type\n"));

	 SB_FREE(sizeof(SbSctAssocCb), assocCb);

	 SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId, suAssocId,
	       SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_INV_PAR_VAL,
	       &rtrv);
         RETVALUE(RFAILED);
      }
   }
#endif

   /* initialize the "general purpose timer" */
   (Void) cmInitTimers(&(assocCb->sbAsCb.timer), 1);

   /* set up the queues */
   assocCb->sbDbCb.sequencedQ = (CmLListCp *) NULLP;
   /* Performance fix */
   assocCb->sbDbCb.newPkt = NULLP; 
   cmLListInit(&(assocCb->sbDbCb.tsnWaitingQOrd));
   cmLListInit(&(assocCb->sbDbCb.tsnWaitingQUnord));
   cmLListInit(&(assocCb->sbDbCb.assemblyQ));
   cmLListInit(&(assocCb->sbDbCb.congestionQ));

   /* insert new association control block into global array list */
   sbGlobalCb.assocCb[spAssocId] = assocCb;

   /* add addresses (they have all been checked already) */
   addrCb = sbPmAddAddr(sctSap, assocCb, priDstNAddr);
   
   /* sb004.12 - Addition : If sbPmAddAddr function fails then we will send
    * TermInd to the upper layer  */
   if ( addrCb == NULLP )
   {
      SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
             "SbUiSctAssocReq: Failure from sbPmAddAddr, Terminating Assoc\n"));
      
      /* sb020.102: Association control block freed */
      sbGlobalCb.assocCb[spAssocId] = (SbSctAssocCb *) NULLP;
      SB_FREE(sizeof(SbSctAssocCb), assocCb);

      SBLOGERROR(ERRCLS_DEBUG, ESB044, (ErrVal)0,
                 "SbUiSctAssocReq: Failure returned from function sbPmAddAddr\n ");
      SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId, suAssocId,
                      SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_UNKNOWN,
                      &rtrv);
      RETVALUE(RFAILED);
   }
   /* RFC 4460 section 2.36: Mark it as confirmed, given by upper layer */
   addrCb->confirmed = TRUE;

   for ( i = 0; i < dstNAddrLst->nmb; i++ )
   {
     /* sb004.12 - Modification : If sbPmAddAddr function fails then we will send
      * TermInd to the upper layer  */
      /* sb020.102: Primary destination address should not come in address list */
      if (sbPmCompNAddr(priDstNAddr,(CmNetAddr *) &(dstNAddrLst->nAddr[i])) == ROK)
         continue;
      addrCb = sbPmAddAddr(sctSap, assocCb,
                         (CmNetAddr *) &(dstNAddrLst->nAddr[i]));
      if ( addrCb == NULLP )
      {
      
         SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
             "SbUiSctAssocReq: Failure from sbPmAddAddr, Terminating Assoc\n"));

         /* sb020.102: Association control block freed */
         sbGlobalCb.assocCb[spAssocId] = (SbSctAssocCb *) NULLP;
         SB_FREE(sizeof(SbSctAssocCb), assocCb);

         SBLOGERROR(ERRCLS_DEBUG, ESB045, (ErrVal)0,
                  "SbUiSctAssocReq: Failure returned from function sbPmAddAddr\n ");
         SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId, suAssocId,
                        SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_UNKNOWN,
                        &rtrv);
         RETVALUE(RFAILED);
      }
      /* RFC 4460 section 2.36: Mark it as confirmed, given by upper layer */
      addrCb->confirmed = TRUE;
   }

   /* set the dest address screening flag here */
   if (dstNAddrLst->nmb == 0)
   {
      assocCb->sbAcCb.pAddrScrnFlg = FALSE;
   }
   else
   {
      assocCb->sbAcCb.pAddrScrnFlg = TRUE;
   }

   /* Finished creating new association */

   /* send an INIT chunk to the peer */
   /* sb017.103: Added supported address types in init chunk */
#ifdef SB_SUPPORTED_ADDRTYPE
    for( i = 0; i < endpCb->localAddrLst.nmb; i++ )
      {
         if( endpCb->localAddrLst.nAddr[i].type == CM_NETADDR_IPV4 )
            assocCb->supAddr |= ( 1 << SB_SUP_ADDRS_IPV4 );

         else if( endpCb->localAddrLst.nAddr[i].type == CM_NETADDR_IPV6 )
            assocCb->supAddr |= ( 1 << SB_SUP_ADDRS_IPV6 );
      }
     ret = sbAsSendInit( assocCb, 0, assocCb->supAddr );
#else
     ret = sbAsSendInit( assocCb, 0, 0 );

#endif /* SB_SUPPORTED_ADDRTYPE */

   if ( ret != ROK )
   {
      /* undo everything */

      /* no ABORT chunk sent so no need to check output */
      (Void) sbAsAbortAssoc(assocCb, FALSE);
      sbGlobalCb.assocCb[spAssocId] = (SbSctAssocCb *) NULLP;
      SB_FREE(sizeof(SbSctAssocCb), assocCb);

      if ( ret == RFAILED )            /* ret from the SendInit */
      {
         SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
             "SbUiSctAssocReq: could not send INIT chunk\n"));
         SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId, suAssocId,
                         SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_INIT_FAILED,
                         &rtrv);
         RETVALUE(RFAILED);
      }
      else if ( ret == ROUTRES )       /* ret from the SendInit */
      {
         SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
             "SbUiSctAssocReq: could not build INIT chunk\n"));
         SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId, suAssocId,
                         SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_OUTRES,
                         &rtrv);
         RETVALUE(RFAILED);
      }

      RETVALUE(ROK);
   }

   /* INIT sent so enter COOKIE_WAIT state and start Init-timer */
   assocCb->assocState = SB_ST_COOKIE_WAIT;

   assocCb->sbAsCb.rtxCnt = 0;                  /* one INIT sent */

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   /* get the destination address from the Address Control block */
   SB_CPY_NADDR(&(tmpAddr1), &(assocCb->sbAcCb.pri->addr));

   /* get the destination address configuration */
   ret = cmHashListFind(&(sbGlobalCb.dstAddrHl),
                     (U8 *) &(tmpAddr1),
                     (U16) sizeof(CmNetAddr), 0,
                     (PTR *) &dstAddr);

   /* Get the Path Profile */
   if (ret == ROK)
   {
      pathProf = sbGlobalCb.pathProfs[dstAddr->profId];
   }

   /* If Destination address configured, AND the path profile exists */
   if( (pathProf != (SbPathProfCb *)NULLP) && (ret == ROK))
   {
      SB_START_TMR(&(assocCb->sbAsCb.timer), assocCb, SB_TMR_INIT,
                pathProf->pathProfCfg.reConfig.rtoInitial);
   }
   else
   {
      SB_START_TMR(&(assocCb->sbAsCb.timer), assocCb, SB_TMR_INIT,
                sctSap->sctSapCfg.reConfig.rtoInitial);
   }
#else
   SB_START_TMR(&(assocCb->sbAsCb.timer), assocCb, SB_TMR_INIT,
                sctSap->sctSapCfg.reConfig.rtoInitial);
#endif /* SB_SATELLITE */

   RETVALUE(ROK);
}/* SbUiSctAssocReq() */

/*
*
*       Fun:   SbUiSctAssocRsp
*
*       Desc:  Primitive to Respond to an Open an Association Indication
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: This function tries to establish an association with a peer.
*              Termination indications are sent if something goes wrong.
*
*       File:  sb_bdy1.c
*
*/

/* sb021.102: Modification for TOS parameter */
#ifdef SCT3
#ifdef ANSI
PUBLIC S16 SbUiSctAssocRsp
(
Pst                  *pst,              /* Post structure */
SpId                  spId,             /* Service provider SAP ID */
UConnId               spEndpId,         /* Service provider endpoint ID */
SctAssocIndParams    *assocIndParams,   /* interface specific params */
SctTos                tos,              /* TOS parameter */
SctResult             result,          /* result */
Buffer               *vsInfo           /* VsInfo - not used any more */
)
#else 
PUBLIC S16 SbUiSctAssocRsp(pst, spId, spEndpId, assocIndParams, 
                           tos, result, vsInfo)
Pst                  *pst;              /* Post structure */
SpId                  spId;             /* Service provider SAP ID */
UConnId               spEndpId;         /* Service provider endpoint ID */
SctAssocIndParams    *assocIndParams;   /* interface specific params */
SctTos                tos;              /* TOS parameter */
SctResult             result;           /* result */
Buffer               *vsInfo;          /* VsInfo - not used any more */
#endif /* ANSI */
#else
#ifdef ANSI
PUBLIC S16 SbUiSctAssocRsp
(
Pst                  *pst,              /* Post structure */
SpId                  spId,             /* Service provider SAP ID */
UConnId               spEndpId,         /* Service provider endpoint ID */
SctAssocIndParams    *assocIndParams,   /* interface specific params */
SctResult             result,           /* result */
Buffer               *vsInfo           /* VsInfo - not used any more */
)
#else
PUBLIC S16 SbUiSctAssocRsp(pst, spId, spEndpId, assocIndParams, 
                           result, vsInfo)
Pst                  *pst;              /* Post structure */
SpId                  spId;             /* Service provider SAP ID */
UConnId               spEndpId;         /* Service provider endpoint ID */
SctAssocIndParams    *assocIndParams;   /* interface specific params */
SctResult             result;           /* result */
Buffer               *vsInfo;          /* VsInfo - not used any more */
#endif /* ANSI */
#endif /* SCT3 */
{
   /* local parameters */
   S16             ret;
   SbSctSapCb     *sctSap;
   SbLocalAddrCb  *localAddrCb;
   SbSctEndpCb    *endpCb;
   SbSctAssocCb   *assocCb;
   SbQueuedChunk  *chunk;
   SbAddrCb       *addrCb;
   CmLList        *n;
   CmLListCp      *l;
   U32             i;
   U32             j;
   SbTcb           tcb;
   SctRtrvInfo     rtrv;
   /*sb070.102 Multi-Homing changes */
   CmNetAddr temp;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   CmNetAddr           tmpAddr1;
   SbDstAddrCb       *dstAddr;
   SbPathProfCb        *pathProf;
   Bool                hBeatEnable;
#endif /* SB_SATELLITE */
/* sb005.103: For IPV6 debug prints */
#ifdef SB_IPV6_SUPPORTED
   S8             ipv6Addr[SB_IPV6STR_SIZE]; /* To  generate ipv6 traces */
   U8             *tempIpv6Addr;
#endif
/* sb013.103: Dual Checksum Fix */
   U8             checksumType = 0;

   TRC3(SbUiSctAssocRsp)

#ifdef SS_MULTIPLE_PROCS

   if(SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                         (void **)&sbGlobalCbPtr) != ROK)
   {
     SBLOGERROR(ERRCLS_DEBUG, ESB046, 0,
               "SbUiSctAssocRsp () failed, cannot derive sbGlobalCbPtr");
     RETVALUE(FALSE);
   }

   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
         "-------SCTP------(proc(%d), ent(%d), inst(%d))--------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));

#endif /* SS_MULTIPLE_PROCS */

  /* SCTPv13  - Vendor specific info removed */

/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctAssocRsp(pst, spId(%d), spEndpId(%d))\n",
          spId, spEndpId));
#else
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctAssocRsp(pst, spId(%d), spEndpId(%ld))\n",
          spId, spEndpId));
#endif /* BIT_64 */

#ifndef SS_MULTIPLE_PROCS
   UNUSED(pst);
#endif  /* SS_MULTIPLE_PROCS */
   SB_CHK_PUTMSG(vsInfo);

   /* sb001.103: UMR Fix */
   cmMemset((U8 *)&tcb,0,sizeof(SbTcb));

   /* sb030.103: Initializing the localAddrCb. */
   localAddrCb = NULLP;

   /* Sanity checks */
   /* SCTP Upgrade: Taking out for robustness */
   /* check the SpId. */
   SB_CHK_SPID(spId, LCM_EVENT_UI_INV_EVT, ret);
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB047, (ErrVal)spId,
                 "SbUiSctAssocRsp: Invalid spId");
#endif /* ERRCLS_INT_PAR */
      RETVALUE(RFAILED);
   }

   sctSap = sbGlobalCb.sctSaps[spId];

   SB_ZERO(&rtrv, sizeof(SctRtrvInfo));

   /* SCTP Upgrade: Taking out for robustness */
   SB_CHK_SPENDPID(spEndpId, ret)

   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check if the endpoint exists */
      SBLOGERROR(ERRCLS_INT_PAR, ESB048, (ErrVal)spEndpId,
                 "SbUiSctAssocRsp: Invalid spEndpId");

      if ( assocIndParams->type == SCT_ASSOC_IND_COOKIE )
      {
         SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId,
                         assocIndParams->t.cookieParams.suAssocId,
                         SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_INV_PAR_VAL,
                         &rtrv);
      }
      else
      {
         /* no confirm so send alarm *
         *sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
         SB_LM_GEN_ALARM(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT, \
                      LCM_CAUSE_INV_PAR_VAL, spId, LSB_SW_RFC_REL0);
      }

#endif /* (ERRCLASS & ERRCLS_INT_PAR) */
      RETVALUE(RFAILED);
   }

   /* get the endpoint control block */
   endpCb = sbGlobalCb.endpCb[spEndpId];

   /* get link through to TSAP */
   SB_GET_LOCAL_CONN(spEndpId, localAddrCb, ret);
/* sb019.103: Fix for the ERRCLASS issue */
   if ( ret != ROK )
   {
#if ( ERRCLASS & ERRCLS_DEBUG )
      SBLOGERROR(ERRCLS_DEBUG, ESB049, (ErrVal)0,
                 "SbUiSctAssocRsp: could not find local address CB in HL");

#endif /* ERRCLS_DEBUG */

      if ( assocIndParams->type == SCT_ASSOC_IND_COOKIE )
      {
         SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId,
                         assocIndParams->t.cookieParams.suAssocId,
                         SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_UNKNOWN,
                         &rtrv);
      }

      RETVALUE(RFAILED);
   }

   /* Distinguish between INIT and COOKIE processing */
   if ( assocIndParams->type == SCT_ASSOC_IND_INIT )               /* INIT */
   {
      SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
             "SbUiSctAssocRsp: assocIndParams->type = SCT_ASSOC_IND_INIT\n"));

      /*sb070.102 - Multi-homing changes */
      SB_ZERO(&(temp), sizeof(CmNetAddr));
      SB_CPY_NADDR(&temp,&(assocIndParams->t.initParams.localAddrLst.nAddr[0]));
/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
      SB_GET_LOCAL_ADDR(&temp, endpCb->port, localAddrCb, ret);
#else
      SB_GET_LOCAL_ADDR(&temp, localAddrCb, ret);
#endif
/* sb019.103: Fix for the ERRCLASS issue */
      if ( ret != ROK )
      {
#if ( ERRCLASS & ERRCLS_DEBUG )
           SBLOGERROR(ERRCLS_DEBUG, ESB050, (ErrVal)0,
                 "SbUiSctAssocRsp: could not find local address CB in HL");
#endif /* ERRCLS_DEBUG */   
           RETVALUE(RFAILED);
      } 
/* sb013.103: Dual Checksum Fix */
#ifdef SB_CHECKSUM
#ifdef SCT5
        checksumType = assocIndParams->t.initParams.checksumType;
#elif defined (SB_CHECKSUM_CRC) 
        checksumType = SB_CRC32;
#else
        checksumType = SB_ADLER32;
#endif
#endif

      /* Check result of previous assoc indication */
      if ( result != SCT_OK )
      {
/* sb021.102: Modification for TOS parameter */
/* sb013.103: Dual Checksum Fix  */
         /* sb029.103: Send User initiated abort, because user don't want this association. */
#ifdef SCT3
         ret = sbAsSendUserAbort(assocIndParams->t.initParams.iTag, localAddrCb,
               &(assocIndParams->t.initParams.peerAddrLst.nAddr[0]),
               assocIndParams->t.initParams.localPort,
               assocIndParams->t.initParams.peerPort, 0, FALSE, tos,
               checksumType);
#else
         ret = sbAsSendUserAbort(assocIndParams->t.initParams.iTag, localAddrCb,
               &(assocIndParams->t.initParams.peerAddrLst.nAddr[0]),
               assocIndParams->t.initParams.localPort,
               assocIndParams->t.initParams.peerPort, 0, FALSE,
               checksumType);
#endif /* SCT3 */

         if ( ret == ROUTRES )
         {
            SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                   "SbUiSctAssocRsp: could not build ABORT chunk\n"));

            /* we send an alarm since the abort process still continues and
            * there are no positive confirms that cover resource failure *
            *sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
            SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, \
                         LCM_EVENT_DMEM_ALLOC_FAIL, \
                         LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);

            /* continue anyway */
         }
         else if ( ret == RFAILED )
         {
            SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                "SbUiSctAssocRsp: could not send ABORT chunk\n"));
            /* continue anyway */
         }

      }
      else              /* result == SCT_OK */
      {


#if (ERRCLASS & ERRCLS_INT_PAR)
         /* check the streams */
         /* Alarms sent since no confirms here */

         if ( (assocIndParams->t.initParams.outStrms == 0) ||
              (assocIndParams->t.initParams.outStrms >
               sbGlobalCb.genCfg.maxNmbOutStrms) )
         {
            SBLOGERROR(ERRCLS_INT_PAR, ESB051,
                       (ErrVal)assocIndParams->t.initParams.outStrms,
                       "SbUiSctAssocRsp: Invalid outStrms");
            /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
            SB_LM_GEN_ALARM(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT, \
                         LCM_CAUSE_INV_PAR_VAL, spId, LSB_SW_RFC_REL0);

            RETVALUE(RFAILED);
         }

         if ( (assocIndParams->t.initParams.inStrms == 0) ||
              (assocIndParams->t.initParams.inStrms >
               sbGlobalCb.genCfg.maxNmbInStrms) )
         {
            SBLOGERROR(ERRCLS_INT_PAR, ESB052,
                       (ErrVal)assocIndParams->t.initParams.inStrms,
                       "SbUiSctAssocRsp: Invalid inStrms");
             /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
            SB_LM_GEN_ALARM(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT, \
                         LCM_CAUSE_INV_PAR_VAL, spId, LSB_SW_RFC_REL0);

            RETVALUE(RFAILED);
         }
#endif /* ERRCLS_INT_PAR */

         /* build and send an INIT ACK */
         sbRand32(SB_RAND_GEN, &j);
         if ( j == 0 )
         {
            j++;
         }
         tcb.tcbInitAck.iTag = j;
         if ( sbGlobalCb.genCfg.reConfig.altAcceptFlg == FALSE)
         {
            assocIndParams->t.initParams.cookieLife = 0;
         }

/* sb021.102: Modification for TOS parameter */
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
         ret = sbAsSendInitAck(spId, assocIndParams, &tcb, localAddrCb,
                               tos, checksumType, (Buffer *)NULLP);
#else
         ret = sbAsSendInitAck(spId, assocIndParams, &tcb, localAddrCb,
                               checksumType, (Buffer *)NULLP);
#endif
         if ( ret != ROK )
         {
            SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                   "SbUiSctAssocRsp: could not build/send INIT ACK chunk\n"));
            if ( ret == ROUTRES )
            {
               /* no confirm covers this so send layer manager alarm *
               *sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
               SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                            LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
            }
            /* continue anyway */
         }
      }

   }
   else if ( assocIndParams->type == SCT_ASSOC_IND_COOKIE )        /* COOKIE */
   {
      SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
             "SbUiSctAssocRsp: assocIndParams->type = SCT_ASSOC_IND_COOKIE\n"));

      /* sb001.103: validate the spAssocId */
      SB_CHK_SPASSOCID(assocIndParams->t.cookieParams.spAssocId, ret);
      if ( ret != ROK )
      {
#if (ERRCLASS & ERRCLS_INT_PAR)
         SBLOGERROR(ERRCLS_INT_PAR, ESB065, (ErrVal)assocIndParams->t.cookieParams.spAssocId,
                 "SbUiSctAssocRsp: Invalid association ID");
      /* can't send confirm since assoc CB can't be resolved */
      /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */     
#endif
         SB_LM_GEN_ALARM(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT, \
                   LCM_CAUSE_INV_PAR_VAL, spId, LSB_SW_RFC_REL0);
         RETVALUE(RFAILED);
      }

      /* get the assoc CB */
      assocCb = sbGlobalCb.assocCb[assocIndParams->t.cookieParams.spAssocId];

      /* sb030.103:  Check the freeze timer is running or not,if ABORT chunk
         bundled after COOKIE-ECHO chunk. */
      if ( assocCb->sbAsCb.timer.tmrEvnt != TMR_NONE )
      {
            SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                   "SbUiSctAssocRsp: Abort chunk bundled after COOIKE-ECHO chunk \n"));
            RETVALUE(RFAILED);
      }      
      if ( result != SCT_OK )
      {
         /* sb029.103: Send User initiated abort, because user don't want this association. */
#ifdef SCT3
         ret = sbAsSendUserAbort(assocCb->peerInitTag, assocCb->localConn,
               &(assocIndParams->t.cookieParams.peerAddrLst.nAddr[0]),
               assocCb->localPort,assocCb->peerPort,0,FALSE, tos,
               assocCb->checksumType);
#else
         ret = sbAsSendUserAbort(assocCb->peerInitTag, assocCb->localConn,
               &(assocIndParams->t.cookieParams.peerAddrLst.nAddr[0]),
               assocCb->localPort,assocCb->peerPort,0,FALSE,
               assocCb->checksumType);
#endif
         /* sb031.103: moved the sbAsAbortAssoc to the below of 
          * "if (ret != ROK)" check */ 
         if ( ret != ROK )
         {
            SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                     "SbUiSctAssocRsp: could not build ABORT chunk\n"));
            if ( ret == ROUTRES )
            {
               /* we send an alarm since the abort process still continues and
                * there are no positive confirms that cover resource failure */
               /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
               SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, \
                     LCM_EVENT_DMEM_ALLOC_FAIL, \
                     LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
            }
            /* continue anyway */
         }
         /* sb031.103: Ret value check is not required. Because sbAsAbortAssoc
          * always returns ROK if "Send Abort chunk to peer flag" set to FALSE 
          * in the arguments */
         sbAsAbortAssoc(assocCb, FALSE);
         /* remove from the list and free the memory */
         sbGlobalCb.assocCb[assocIndParams->t.cookieParams.spAssocId] =
               (SbSctAssocCb *) NULLP;
         SB_FREE(sizeof(SbSctAssocCb), assocCb);

      }
      else                                /* result == SCT_OK */
      {

         /* user wants this association */
         assocCb->suAssocId = assocIndParams->t.cookieParams.suAssocId;

/* sb056.102 : Addition - In case of primary dest address failure
                          try assoc on alternate dest addr of
                          address list 
*/
          /* reset the addrlist and redefine as per peer */
          l = &(assocCb->sbAcCb.addrLst);
          n = cmLListFirst(l);
          for ( i = 0; i < cmLListLen(l); i++ )
          {
             addrCb = (SbAddrCb *)(n->node);
             if ( addrCb != (SbAddrCb *) NULLP )
             {
                addrCb->sndTo = FALSE;
             }
             n = cmLListNext(l);
          }
 
         if ( assocIndParams->t.cookieParams.peerAddrLst.nmb == 0 )
         {
            /* user wants to use configured address list */
            l = &(assocCb->sbAcCb.addrLst);
            n = cmLListFirst(l);
            for ( i = 0; i < cmLListLen(l); i++ )
            {
               addrCb = (SbAddrCb *)(n->node);
               if ( addrCb != (SbAddrCb *) NULLP )
               {
                  addrCb->sndTo = TRUE;
                  addrCb->rcvFrom = TRUE;
               }
               n = cmLListNext(l);
            }
         }
         else
         {
            /* user has selected address list subset */
            for ( i = 0; i < assocIndParams->t.cookieParams.peerAddrLst.nmb; \
                  i++ )
            {
               addrCb = sbPmGetAddrCb(assocCb, &(assocIndParams-> \
                                      t.cookieParams.peerAddrLst.nAddr[i]));
               if ( addrCb != (SbAddrCb *) NULLP )
               {
                  addrCb->sndTo = TRUE;
                  addrCb->rcvFrom = TRUE;
               }
#if (ERRCLASS & ERRCLS_INT_PAR)
               else
               {
                  /* address is invalid, send error notification */
                  SBLOGERROR(ERRCLS_INT_PAR, ESB053, (ErrVal)0,
                             "SbUiSctAssocRsp: Invalid peer address");

                  /* sb036.102: remove the association control block */
                  sbGlobalCb.assocCb[assocIndParams->t.cookieParams.spAssocId] =
                        (SbSctAssocCb *) NULLP;
                  SB_FREE(sizeof(SbSctAssocCb), assocCb);

                  SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId,
                                  assocIndParams->t.cookieParams.suAssocId,
                                  SCT_ASSOCID_SU, SCT_STATUS_INV,
                                  SCT_CAUSE_INV_PAR_VAL, &rtrv);
                  RETVALUE(RFAILED);
               }
#endif /* ERRCLS_INT_PAR */

            }  /* for */
         } /* if peerAddrLst.nmb */

         /* send COOKIE ACK */
         /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
         assocCb->tos = tos;              /* TOS parameter */
#endif /* SCT3 */
         ret = sbAsSendCookieAck(assocCb, &(assocCb->sbAcCb.pri->addr));
         if ( ret != ROK )
         {
            SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                   "SbUiSctAssocRsp: could not send COOKIE ACK chunk\n"));
            /* get resource error */
            if ( ret == ROUTRES )
            {
                /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
               SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                            LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
            }
            RETVALUE(RFAILED);
         }

		 /* send COMM UP notification */
		 /* sb024.103: Included protId parameter in status indication */ 
#ifdef SCT7
		 SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
				 assocCb->spAssocId, &(assocCb->sbAcCb.pri->addr),
				 SCT_STATUS_COMM_UP, SCT_CAUSE_NOT_APPL, SCT_PROTID_NONE ,
				 (Buffer *) NULLP);
#else
		 SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
				 assocCb->spAssocId, &(assocCb->sbAcCb.pri->addr),
				 SCT_STATUS_COMM_UP, SCT_CAUSE_NOT_APPL,
				 (Buffer *) NULLP);
#endif		 

         /* association now established */
         assocCb->assocState = SB_ST_ESTABLISHED;


         /* look for chunks that arrived with the cookie */
         for ( i = 0; i < assocCb->sbSqCb.nmbInStreams; i++ )
         {
            chunk = sbDbOrdered(assocCb, (SctStrmId)i,
                                assocCb->sbSqCb.inStreamSeqNum[i]);
            while ( chunk != (SbQueuedChunk *) NULLP )
            {
               /* send them up to the user */
               ret = sbSqInSendUp(assocCb, chunk, SCT_PEER_DAT);
               if ( ret != ROK )
               {
                  SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                         "SbUiSctAssocRsp: could not send chunks to user\n"));
               }
               assocCb->sbSqCb.inStreamSeqNum[i]++;

               chunk = sbDbOrdered(assocCb, (SctStrmId)i,
                                   assocCb->sbSqCb.inStreamSeqNum[i]);
            }
         }
         /* sb028.103: Send sack for data chunk received with cookie */
         if(( assocCb->sbAcCb.sinceSack > 0 ) && \
               (assocCb->sbAcCb.firstDataRcvd == TRUE))
         {
            sbAcSendSack(assocCb);
         }
         /*sb075.102*/
        /*Path management functionality added here after the setp up of association.*/
        /*Each source-destination combination pair will now be a path and an*/
        /*individual addr Cb will be maintained for it. HB will be started on it.*/
        /*Populate the source-destination pair now*/

/* sb009.103: IPV4IPV6 changes */
#ifdef SB_IPV4IPV6_COMBINED
        sbPmMakePaths(assocCb);
#else
        {
          SbAddrCb *destAddr[SCT_MAX_NET_ADDRS];
          U8      numPeerCb = 0;
          U8      srcAddrCount = 0;
          SbSctEndpCb    *tmpEndpCb;                                            
          CmNetAddr  tmpAddr;                                                   
          tmpEndpCb = sbGlobalCb.endpCb[assocCb->endpId];  
          l = &(assocCb->sbAcCb.addrLst);
          srcAddrCount = tmpEndpCb->localAddrLst.nmb;
          n = cmLListFirst(l);
        
          /* sb020.103: If number of addresses in address list exceed 
           * the limit discard the remaining */
#if (ERRCLASS & ERRCLS_INT_PAR)
          if ( cmLListLen(l) > SCT_MAX_NET_ADDRS )
          {
              SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
              "SbUiSctAssocRsp: Number of Addresses exceed max limit of %d\n",
               SCT_MAX_NET_ADDRS));
          }
#endif/* (ERRCLASS & ERRCLS_DEBUG) */
          for ( i = 0; ((i < cmLListLen(l)) && ( i < SCT_MAX_NET_ADDRS)); i++)
          {
             addrCb = (SbAddrCb *)(n->node);
             if ( addrCb != (SbAddrCb *) NULLP )
             {
                destAddr[numPeerCb++] = addrCb;
             }
             n = cmLListNext(l);
          }
          /*Now use the destAddr to populate the src-dest pair in assocCb*
      *sb080.102:use all the address of local address list */
          for(i = 0; i < srcAddrCount; i++)
          {
             U8 k;
             SB_ZERO(&(tmpAddr), sizeof(CmNetAddr));
             SB_CPY_NADDR(&(tmpAddr), &(tmpEndpCb->localAddrLst.nAddr[i]));
             for(k=0; k < numPeerCb; k++)
             {
                sbPmAddPathCb(assocCb,&tmpAddr,destAddr[k]);
             }
          }
        }
#endif

         /* RFC 4460 section 2.36: Path Initialization */
         sbPmProbe(assocCb);

/* sb003.103: SATELLITE SCTP feature */
#ifndef SB_SATELLITE
        /* HBEAT - Here check if heartbeat is to be enabled by default the do it */
        if(sctSap->sctSapCfg.reConfig.hBeatEnable == TRUE )
#endif /* SB_SATELLITE */
        {
            SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                   "SbUiSctAssocRsp: Enabling HeartBeat By Default \n"));

            l = &(assocCb->sbAcCb.addrLst);
            n = cmLListFirst(l);

            /* enable/disable on an association */
            for ( i = 0; i < cmLListLen(l); i++)
            {
               addrCb = (SbAddrCb *)n->node;
/*sb005.103: IPV6 address print added */
#ifdef SB_IPV6_SUPPORTED
               if ( addrCb->addr.type == CM_NETADDR_IPV6 )
               {
                  tempIpv6Addr = addrCb->addr.u.ipv6NetAddr;
                  SB_CPY_IPV6ADSTR(ipv6Addr, tempIpv6Addr)
                  SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
                  "SbUiSctAssocRsp:  Srcaddr.type(%d), Srcaddr.u.ipv6(%s)\n",
                   addrCb->addr.type, ipv6Addr));

                  tempIpv6Addr = addrCb->localConn->ownAddr.u.ipv6NetAddr;
                  SB_CPY_IPV6ADSTR(ipv6Addr, tempIpv6Addr)
                  SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
                  "SbUiSctAssocRsp:  Destaddr.type(%d), Destaddr.u.ipv6(%s)\n",
                  addrCb->localConn->ownAddr.type, ipv6Addr));
               }
#endif /* SB_IPV6_SUPPORTED */
               if ( addrCb->addr.type == CM_NETADDR_IPV4 )
               {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
                  SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
                  "SbUiSctAssocRsp:  Srcaddr.type(%d), Srcaddr.u.ipv4(%08X)\n",
                  addrCb->addr.type, addrCb->addr.u.ipv4NetAddr));
                  SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
                  "SbUiSctAssocRsp:  Destaddr.type(%d), Destaddr.u.ipv4(%08X)\n",
                  addrCb->localConn->ownAddr.type, addrCb->localConn->ownAddr.u.ipv4NetAddr));
#else
                  SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
                  "SbUiSctAssocRsp:  Srcaddr.type(%d), Srcaddr.u.ipv4(%08lX)\n",
                  addrCb->addr.type, addrCb->addr.u.ipv4NetAddr));
                  SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
                  "SbUiSctAssocRsp:  Destaddr.type(%d), Destaddr.u.ipv4(%08lX)\n",
                  addrCb->localConn->ownAddr.type, addrCb->localConn->ownAddr.u.ipv4NetAddr));
#endif /* BIT_64 */
               }
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
               /* get the destination address from the Address Control block */
               SB_CPY_NADDR(&(tmpAddr1), &(addrCb->addr));

               /* get the destination address configuration */
               ret = cmHashListFind(&(sbGlobalCb.dstAddrHl),
                           (U8 *) &(tmpAddr1),
                           (U16) sizeof(CmNetAddr), 0,
                           (PTR *) &dstAddr);

               /* Get the Path Profile */
               if (ret == ROK)
               {
                  pathProf = sbGlobalCb.pathProfs[dstAddr->profId];
               }

               /* If Destination address configured, AND the path profile exists */
               if( (pathProf != (SbPathProfCb *)NULLP) && (ret == ROK))
               {
                  hBeatEnable = pathProf->pathProfCfg.reConfig.hBeatEnable;
               }
               else
               {
                  hBeatEnable = sctSap->sctSapCfg.reConfig.hBeatEnable;
               }

               if(hBeatEnable == TRUE)
#endif /* SB_SATELLIE */

               if (addrCb->sndTo == TRUE)
               {
                  sbPmHBeatEnb(addrCb, 0);
               }
               n = cmLListNext(l);
            }
         }
      }
   }

   RETVALUE(ROK);
}/* SbUiSctAssocRsp() */

/*
*
*       Fun:   SbUiSctTermReq
*
*       Desc:  Primitive to Request Termination of an Association
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: This function tries to terminate an association with a peer.
*              Termination confirmation is sent on successful completion with
*              positive status, and with negative status if something went
*              wrong. The termination procedure can be graceful or ungraceful.
*
*       File:  sb_bdy1.c
*
*/

#ifdef ANSI
#ifdef S1SIMAPP
PUBLIC S16 SbUiSctTermReq
(
Pst                  *pst,              /* Post structure */
SpId                  spId,             /* Service provider SAP ID */
UConnId               assocId,          /* Association ID */
U8                    assocIdType,      /* Association ID type */
Bool                  abortFlg,          /* Termination type */
U8                    cause
)
#else
PUBLIC S16 SbUiSctTermReq
(
Pst                  *pst,              /* Post structure */
SpId                  spId,             /* Service provider SAP ID */
UConnId               assocId,          /* Association ID */
U8                    assocIdType,      /* Association ID type */
Bool                  abortFlg          /* Termination type */
)
#endif
#else
#ifdef S1SIMAPP
PUBLIC S16 SbUiSctTermReq(pst, spId, assocId, assocIdType, abortFlg,cause)
Pst                  *pst;              /* Post structure */
SpId                  spId;             /* Service provider SAP ID */
UConnId               assocId;          /* Association ID */
U8                    assocIdType;      /* Association ID type */
Bool                  abortFlg;         /* Termination type */
U8                    cause;
#else
PUBLIC S16 SbUiSctTermReq(pst, spId, assocId, assocIdType, abortFlg)
Pst                  *pst;              /* Post structure */
SpId                  spId;             /* Service provider SAP ID */
UConnId               assocId;          /* Association ID */
U8                    assocIdType;      /* Association ID type */
Bool                  abortFlg;         /* Termination type */
#endif
#endif
{
   /* local parameters */
   SbSctSapCb     *sctSap;
   SbSctAssocCb   *assocCb;
   U32             i;
   S16             ret;
   UConnId         suAssocId;
   /* sb032.103 Changed the dstNAddr type from pointer to the local variable.*/
   CmNetAddr       dstNAddr;
   TRC3(SbUiSctTermReq)

#ifdef SS_MULTIPLE_PROCS

   if(SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                         (void **)&sbGlobalCbPtr) != ROK)
   {
     SBLOGERROR(ERRCLS_DEBUG, ESB054, 0,
               "SbUiSctTermReq () failed, cannot derive sbGlobalCbPtr");
     RETVALUE(FALSE);
   }

   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
         "-------SCTP------(proc(%d), ent(%d), inst(%d))--------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));

#endif /* SS_MULTIPLE_PROCS */

/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
       "SbUiSctTermReq(pst, spId(%d), assocId(%d), assocIdType(%d), \
       abortFlg(%d))\n",
       spId, assocId, assocIdType, abortFlg));
#else
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
       "SbUiSctTermReq(pst, spId(%d), assocId(%ld), assocIdType(%d), \
       abortFlg(%d))\n",
       spId, assocId, assocIdType, abortFlg));
#endif /* BIT_64 */

#ifndef SS_MULTIPLE_PROCS
   UNUSED(pst);
#endif  /* SS_MULTIPLE_PROCS */

   /* Sanity checks */

   /* check the SpId. *
    *sb081.102:Removing the check from the ERRCLASS*/
   SB_CHK_SPID(spId, LCM_EVENT_UI_INV_EVT, ret);
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB055, (ErrVal)spId,
                 "SbUiSctTermReq: Invalid spId");
#endif /* ERRCLS_INT_PAR */
      RETVALUE(RFAILED);
   }

   /* get the SCT SAP control block */
   sctSap = sbGlobalCb.sctSaps[spId];

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* validate the assocIdType */
   if ( (assocIdType != SCT_ASSOCID_SU) && (assocIdType != SCT_ASSOCID_SP) )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB056, (ErrVal)assocIdType,
                 "SbUiSctTermReq: Invalid assocIdType");
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */  
      SB_LM_GEN_ALARM(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT, \
                   LCM_CAUSE_INV_PAR_VAL, spId, LSB_SW_RFC_REL0);
      RETVALUE(RFAILED);
   }
#endif /* ERRCLS_INT_PAR */

   /* the validation check for the assocIdType is at the bottom */
   if ( assocIdType == SCT_ASSOCID_SU)                 /* service user ID */
   {
      for (i = 0; i < sbGlobalCb.genCfg.maxNmbAssoc; i++ )
      {
         assocCb = sbGlobalCb.assocCb[i];
         if ( assocCb != (SbSctAssocCb *) NULLP )
         {
            /* find a match for the suAssocId */
            /* sb020.102: suAssocId should be unique per SAP */
            if ( (assocCb->suAssocId == assocId ) && (assocCb->spId == spId) )
            {
               /* Only Abort Permitted, no graceful shutdown */
/* RFC 4460 */
   /* sb021.102: Modification for TOS parameter */
   /*sb070.102 Multi-Homing changes */
  /* sb013.103: Dual Checksum Fix */
#ifdef SCT3
               ret = sbAsSendUserAbort(assocCb->peerInitTag,assocCb->sbAcCb.pri->localConn,
                                       &(assocCb->sbAcCb.pri->addr),assocCb->localPort,
                                       assocCb->peerPort,0,FALSE,assocCb->tos,
                                       assocCb->checksumType);
#else
               ret = sbAsSendUserAbort(assocCb->peerInitTag,assocCb->sbAcCb.pri->localConn,
                                       &(assocCb->sbAcCb.pri->addr),assocCb->localPort,
                                       assocCb->peerPort,0,FALSE, assocCb->checksumType);
#endif /* SCT3 */
               if ( ret != ROK )
               {
                  /* could not send ABORT chunk */
                  SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf, \
                         "SbUiSctTermReq: could not send ABORT chunk\n"));
                  if ( ret == ROUTRES )
                  {
                     /* send alarm since the abort request is still being
                      * processed and we cant send a negative confirm */
                    /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
                     SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, \
                                  LCM_EVENT_DMEM_ALLOC_FAIL, \
                                  LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
                  }
                  /* continue anyway */
               }

               ret = sbAsAbortAssoc(assocCb, FALSE);
               sbGlobalCb.assocCb[i] = (SbSctAssocCb *) NULLP;
               SB_FREE(sizeof(SbSctAssocCb), assocCb);

               /* return with positive status */
               SbUiSctTermCfm(&(sctSap->sctPst), sctSap->suId, assocId,
                              SCT_OK, SCT_CAUSE_NOT_APPL);
               RETVALUE(ROK);
            }
         }
      }

      /* sb031.103:Sending SbUiSctTermCfm to upper layer even, user requested 
       * SuAssocId/SpAssocId match not found in any SbSctAssocCb's.*/
      if (i == sbGlobalCb.genCfg.maxNmbAssoc)
      {
         /* if we are here then the association does not exist */
         SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,\
                  "Association not found. Still send TermCfm to Upper layer\n"));
         SbUiSctTermCfm(&(sctSap->sctPst), sctSap->suId, assocId,
               SCT_NOK, SCT_CAUSE_UNKNOWN);
      }

#if (ERRCLASS & ERRCLS_INT_PAR)
      /* if we are here then the association does not exist */
      SBLOGERROR(ERRCLS_INT_PAR, ESB057, (ErrVal)assocId,
            "SbUiSctTermReq: Invalid suAssocId");
      /* alarm sent since we don't know where to send a confirm */
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */      
      SB_LM_GEN_ALARM(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT, \
                   LCM_CAUSE_INV_PAR_VAL, spId, LSB_SW_RFC_REL0);
      RETVALUE(RFAILED);
#endif
   }

   if ( assocIdType == SCT_ASSOCID_SP )              /* service provider ID */
   {

      /* validate the assocId *
       *sb081.102: Removing the check from the ERRCLASS*/
      SB_CHK_SPASSOCID(assocId, ret);
      if ( ret != ROK )
      {
         /* sb032.103 Changed the dstNAddr type from pointer to the local variable.*/
         /* sb031.103Sending SbUiSctTermCfm to upper layer even, user requested
          * SuAssocId/SpAssocId match not found in any SbSctAssocCb's.*/
         dstNAddr.type = CM_NETADDR_NOTPRSNT;
         /* if we are here then the association does not exist*/
         SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,\
                  "Association not found. Still send TermCfm to Upper layer\n"));
         SbUiSctTermCfm(&(sctSap->sctPst), sctSap->suId, 0,
               SCT_NOK, SCT_CAUSE_NO_ASSOC);
#ifdef SCT7
         /* sb032.103 Fixed the compilation issue, changes protId to SCT_PROTID_NONE.*/
         SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, 0, assocId, &dstNAddr,
               SCT_STATUS_INV, SCT_CAUSE_NO_ASSOC, SCT_PROTID_NONE, (Buffer *)NULLP );
#else
         SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, 0, assocId, &dstNAddr,
               SCT_STATUS_INV, SCT_CAUSE_NO_ASSOC, (Buffer *)NULLP );
#endif


#if (ERRCLASS & ERRCLS_INT_PAR)
         SBLOGERROR(ERRCLS_INT_PAR, ESB058, (ErrVal)assocId,
               "SbUiSctTermReq: Invalid spAssocId (assoc. not found)");
#endif/*ERRCLS_INT_PAR*/
         /* alarm sent since we don't know where to send a confirm */
         /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
         SB_LM_GEN_ALARM(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT, \
               LCM_CAUSE_INV_PAR_VAL, spId, LSB_SW_RFC_REL0);
         RETVALUE(RFAILED);
      }

      /* get the association CB */
      assocCb = sbGlobalCb.assocCb[assocId];

      /* check the state of the association */
      if ( assocCb->assocState == SB_ST_ESTABLISHED )
      {
         if ( abortFlg == TRUE )
         {
            /* ungraceful shutdown (abort) */
/* RFC 4460 */
   /* sb021.102: Modification for TOS parameter */
   /*sb070.102 Multi-Homing changes */
  /* sb013.103: Dual Checksum Fix */
#ifdef SCT3
#ifdef S1SIMAPP
               ret = sbAsSendUserAbort(assocCb->peerInitTag,assocCb->sbAcCb.pri->localConn,
                                       &(assocCb->sbAcCb.pri->addr),assocCb->localPort,
                                       assocCb->peerPort,cause,FALSE,assocCb->tos,
                                       assocCb->checksumType);
#else
               ret = sbAsSendUserAbort(assocCb->peerInitTag,assocCb->sbAcCb.pri->localConn,
                                       &(assocCb->sbAcCb.pri->addr),assocCb->localPort,
                                       assocCb->peerPort,0,FALSE,assocCb->tos,
                                       assocCb->checksumType);
#endif
#else
#ifdef S1SIMAPP
               ret = sbAsSendUserAbort(assocCb->peerInitTag,assocCb->sbAcCb.pri->localConn,
                                       &(assocCb->sbAcCb.pri->addr),assocCb->localPort,
                                       assocCb->peerPort,cause,FALSE, assocCb->checksumType);
#else
               ret = sbAsSendUserAbort(assocCb->peerInitTag,assocCb->sbAcCb.pri->localConn,
                                       &(assocCb->sbAcCb.pri->addr),assocCb->localPort,
                                       assocCb->peerPort,0,FALSE, assocCb->checksumType);
#endif
#endif /* SCT3 */
               if ( ret != ROK )
               {
                  /* could not send ABORT chunk */
                  SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf, \
                         "SbUiSctTermReq: could not send ABORT chunk\n"));
                  if ( ret == ROUTRES )
                  {
                     /* send alarm since the abort request is still being
                      * processed and we cant send a negative confirm */
                    /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
                     SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, \
                                  LCM_EVENT_DMEM_ALLOC_FAIL, \
                                  LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
                  }
                  /* continue anyway */
               }

               ret = sbAsAbortAssoc(assocCb, FALSE);

            SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                   "SbUiSctTermReq: completed assoc Abort\n"));

            /* send positive confirmation */
            ret = SbUiSctTermCfm(&(sctSap->sctPst), sctSap->suId,
                                 assocCb->suAssocId, SCT_OK,
                                 SCT_CAUSE_NOT_APPL);

            /* remove association and free the memory */
            sbGlobalCb.assocCb[assocId] = (SbSctAssocCb *) NULLP;
            SB_FREE(sizeof(SbSctAssocCb), assocCb);

            RETVALUE(ROK);

         }
         else /* abrtFlg != TRUE */
         {

            /* graceful shutdown */
            /* send SHUTDOWN */
            assocCb->assocState = SB_ST_SDOWN_PEND;
            if ( (assocCb->sbAcCb.cumTsn + 1) == assocCb->sbAcCb.nextLocalTsn )
            {
               ret = sbAsShutdown(assocCb);
               if ( ret == ROUTRES )
               {
                  /* error should be logged */
                  SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                         "SbUiSctTermReq: could not build SHUTDOWN\n"));

                  /* sb010.102 suAssocId in Termination Indication */
                  SbUiSctTermCfm(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                                 SCT_NOK, SCT_CAUSE_OUTRES);
                  RETVALUE(RFAILED);
               }
               else if ( ret == RFAILED )
               {
                  /* error should be logged */
                  SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                         "SbUiSctTermReq: could not send SHUTDOWN\n"));
                  SbUiSctTermCfm(&(sctSap->sctPst), sctSap->suId,
                                 assocCb->suAssocId,
                                 SCT_NOK, SCT_CAUSE_TERM_FAILED);
                  RETVALUE(RFAILED);
               }

               RETVALUE(ROK);
            }
         }

      }
      else /* assocCb->assocState != SB_ST_ESTABLISHED */
      {
         SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
            "SbUiSctTermReq: assoc. state not ESTABLISHED, aborting instead\n"));

/* RFC 4460 */
   /* sb021.102: Modification for TOS parameter */
   /*sb070.102 Multi-Homing changes */
  /* sb013.103: Dual Checksum Fix */
#ifdef SCT3
               ret = sbAsSendUserAbort(assocCb->peerInitTag,assocCb->sbAcCb.pri->localConn,
                                       &(assocCb->sbAcCb.pri->addr),assocCb->localPort,
                                       assocCb->peerPort,0,FALSE,assocCb->tos,
                                       assocCb->checksumType);
#else
               ret = sbAsSendUserAbort(assocCb->peerInitTag,assocCb->sbAcCb.pri->localConn,
                                       &(assocCb->sbAcCb.pri->addr),assocCb->localPort,
                                       assocCb->peerPort,0,FALSE, assocCb->checksumType);
#endif /* SCT3 */
               if ( ret != ROK )
               {
                  /* could not send ABORT chunk */
                  SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf, \
                         "SbUiSctTermReq: could not send ABORT chunk\n"));
                  if ( ret == ROUTRES )
                  {
                     /* send alarm since the abort request is still being
                      * processed and we cant send a negative confirm */
                    /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
                     SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, \
                                  LCM_EVENT_DMEM_ALLOC_FAIL, \
                                  LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
                  }
                  /* continue anyway */
               }

               ret = sbAsAbortAssoc(assocCb, FALSE);

         /* remove association and free the memory */
         suAssocId = assocCb->suAssocId;
         sbGlobalCb.assocCb[assocId] = (SbSctAssocCb *) NULLP;
         SB_FREE(sizeof(SbSctAssocCb), assocCb);

         /* send positive confirmation */
         SbUiSctTermCfm(&(sctSap->sctPst), sctSap->suId,
                        suAssocId, SCT_OK, SCT_CAUSE_NOT_APPL);
      }
   }

   RETVALUE(ROK);
}/* SbUiSctTermReq() */

/*
*
*       Fun:   SbUiSctSetPriReq
*
*       Desc:  Primitive to Set a New Primary Address on an Association
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: <none>
*
*       File:  sb_bdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 SbUiSctSetPriReq
(
Pst                  *pst,              /* Post structure */
SpId                  spId,             /* Service provider SAP ID */
UConnId               spAssocId,        /* Service provider association ID */
CmNetAddr            *dstNAddr          /* New primary network address */
)
#else
PUBLIC S16 SbUiSctSetPriReq(pst, spId, spAssocId, dstNAddr)
Pst                  *pst;              /* Post structure */
SpId                  spId;             /* Service provider SAP ID */
UConnId               spAssocId;        /* Service provider association ID */
CmNetAddr            *dstNAddr;         /* New primary network address */
#endif
{
   /* local parameters */
   S16             ret;
   SbSctSapCb     *sctSap;
   SbSctAssocCb   *assocCb;
   SbAddrCb       *addrCb;
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   S8             ipv6Addr1[SB_IPV6STR_SIZE]; /* To  generate ipv6 traces */
   S8             ipv6Addr2[SB_IPV6STR_SIZE];
   S8             ipv6Addr3[SB_IPV6STR_SIZE];
   U8             *tempIpv6Addr;
#endif

   TRC3(SbUiSctSetPriReq)

#ifdef SS_MULTIPLE_PROCS

   if(SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                         (void **)&sbGlobalCbPtr) != ROK)
   {
     SBLOGERROR(ERRCLS_DEBUG, ESB059, 0,
               "SbUiSctSetPriReq () failed, cannot derive sbGlobalCbPtr");
     RETVALUE(FALSE);
   }

   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
         "-------SCTP------(proc(%d), ent(%d), inst(%d))--------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));

#endif /* SS_MULTIPLE_PROCS */

/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
       "SbUiSctSetPriReq(pst, spId(%d), spAssocId(%d), dstNAddr)\n",
       spId, spAssocId));
#else
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
       "SbUiSctSetPriReq(pst, spId(%d), spAssocId(%ld), dstNAddr)\n",
       spId, spAssocId));
#endif /* BIT_64 */

#ifndef SS_MULTIPLE_PROCS
   UNUSED(pst);
#endif  /* SS_MULTIPLE_PROCS */
   ret = ROK;

   /* Sanity checks */

   /* SCTP Upgrade: Taking out for robustness */
   /* check the SpId. */
   SB_CHK_SPID(spId, LCM_EVENT_UI_INV_EVT, ret);
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB060, (ErrVal)spId,
                 "SbUiSctSetPriReq: Invalid spId");
#endif /* ERRCLS_INT_PAR */
      RETVALUE(RFAILED);
   }

   /* get the SCT SAP control block */
   sctSap = sbGlobalCb.sctSaps[spId];

   /* validate the assocId */
   /* SCTP Upgrade: Taking out for robustness */
   SB_CHK_SPASSOCID(spAssocId, ret);
   if ( ret != ROK )
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB061, (ErrVal)spAssocId,
                 "SbUiSctSetPriReq: Invalid association ID");
#endif
      SbUiSctSetPriCfm(&(sctSap->sctPst), sctSap->suId, spAssocId,
                       SCT_NOK, SCT_CAUSE_INV_PAR_VAL);
      RETVALUE(RFAILED);
   }

   /* get the association control block */
   assocCb = sbGlobalCb.assocCb[spAssocId];

   /* get the address control block */
   addrCb = sbPmGetAddrCb(assocCb, dstNAddr);
   /* validate the address */
   if ( addrCb == (SbAddrCb *) NULLP )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB062, (ErrVal)0,
                 "SbUiSctSetPriReq: primary destination address invalid");
      SbUiSctSetPriCfm(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                       SCT_NOK, SCT_CAUSE_INV_PAR_VAL);
      RETVALUE(RFAILED);
   }
 
#if (ERRCLASS & ERRCLS_INT_PAR)
/* sb009.103: IPV4IPV6 changes */
#ifdef SB_IPV4IPV6_COMBINED
   if (addrCb->localConn->ownAddr.type != addrCb->addr.type)
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB062, (ErrVal)0,
                 "SbUiSctSetPriReq: can not set this address as primary");
      SbUiSctSetPriCfm(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                       SCT_NOK, SCT_CAUSE_INV_PAR_VAL);
      RETVALUE(RFAILED);
   }
#endif
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */

   /* Patch sb031.102 IPV6 Support Added */
   if((assocCb->sbAcCb.pri->addr.type == CM_NETADDR_IPV4) && (addrCb->addr.type == CM_NETADDR_IPV4) && (dstNAddr->type == CM_NETADDR_IPV4))
   {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
       "SbUiSctSetPriReq: Old = %u, New = %u, requested = %u\n",
       assocCb->sbAcCb.pri->addr.u.ipv4NetAddr, addrCb->addr.u.ipv4NetAddr,
       dstNAddr->u.ipv4NetAddr));
#else
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
       "SbUiSctSetPriReq: Old = %lu, New = %lu, requested = %lu\n",
       assocCb->sbAcCb.pri->addr.u.ipv4NetAddr, addrCb->addr.u.ipv4NetAddr,
       dstNAddr->u.ipv4NetAddr));
#endif /* BIT_64 */
   }
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   if((assocCb->sbAcCb.pri->addr.type == CM_NETADDR_IPV6) && (addrCb->addr.type == CM_NETADDR_IPV6) && (dstNAddr->type == CM_NETADDR_IPV6))
   {
      tempIpv6Addr = assocCb->sbAcCb.pri->addr.u.ipv6NetAddr;
      SB_CPY_IPV6ADSTR(ipv6Addr1, tempIpv6Addr)

      tempIpv6Addr = addrCb->addr.u.ipv6NetAddr;
      SB_CPY_IPV6ADSTR(ipv6Addr2, tempIpv6Addr)

      tempIpv6Addr = dstNAddr->u.ipv6NetAddr;
      SB_CPY_IPV6ADSTR(ipv6Addr3, tempIpv6Addr)

   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
       "SbUiSctSetPriReq: Old = %s, New = %s, requested = %s\n",
       ipv6Addr1, ipv6Addr2, ipv6Addr3)); 
   }
#endif

   /* set the new value on the association CB */
   assocCb->sbAcCb.pri = addrCb;

   SbUiSctSetPriCfm(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                    SCT_OK, SCT_CAUSE_NOT_APPL);
   RETVALUE(ROK);
}/* SbUiSctSetPriReq() */

/*
*
*       Fun:   SbUiSctHBeatReq
*
*       Desc:  Primitive to Request enable/disable Heartbeat Information.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: Heartbeat can be enabled/disabled per association or per
*              destination address.
*
*       File:  sb_bdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 SbUiSctHBeatReq
(
Pst                  *pst,              /* Post structure */
SpId                  spId,             /* Service provider SAP ID */
UConnId               spAssocId,        /* Service provider association ID */
CmNetAddr            *dstNAddr,         /* New primary network address */
U16                   intervalTime,     /* heartbeat periodicity value */
SctStatus             status            /* Type of request to process */
)
#else
PUBLIC S16 SbUiSctHBeatReq(pst, spId, spAssocId, dstNAddr, intervalTime, status)
Pst                  *pst;              /* Post structure */
SpId                  spId;             /* Service provider SAP ID */
UConnId               spAssocId;        /* Service provider association ID */
CmNetAddr            *dstNAddr;         /* New primary network address */
U16                   intervalTime;     /* heartbeat periodicity value */
SctStatus             status;           /* Type of request to process */
#endif
{
   /* local parameters */
   SbSctSapCb           *sctSap;
   SbSctAssocCb         *assocCb;
   SbAddrCb             *addrCb;
   S16                   ret;
   CmLListCp            *l;
   CmLList              *n;
   U32                   i;
/* sb009.103: IPV4IPV6 changes */
#ifdef SB_IPV4IPV6_COMBINED
   Bool                  hbAddrFlag;
#endif

   TRC3(SbUiSctHBeatReq)

#ifdef SS_MULTIPLE_PROCS

   if(SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                         (void **)&sbGlobalCbPtr) != ROK)
   {
     SBLOGERROR(ERRCLS_DEBUG, ESB063, 0,
               "SbUiSctHBeatReq () failed, cannot derive sbGlobalCbPtr");
     RETVALUE(FALSE);
   }

   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
         "-------SCTP------(proc(%d), ent(%d), inst(%d))--------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));

#endif /* SS_MULTIPLE_PROCS */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctHBeatReq(pst, spId(%d), spAssocId(%d), dstNAddr, \
          intervalTime(%d), status(%d))\n",
          spId, spAssocId, intervalTime, status));
#else
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctHBeatReq(pst, spId(%d), spAssocId(%ld), dstNAddr, \
          intervalTime(%d), status(%d))\n",
          spId, spAssocId, intervalTime, status));
#endif /* BIT_64*/

#ifndef SS_MULTIPLE_PROCS
   UNUSED(pst);
#endif /* SS_MULTIPLE_PROCS */

   ret = ROK;

   /* Sanity checks */
   /* SCTP Upgrade: Taking out for robustness */
   /* check the SpId. */
   SB_CHK_SPID(spId, LCM_EVENT_UI_INV_EVT, ret);
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB064, (ErrVal)spId,
                 "SbUiSctHBeatReq: Invalid spId");
#endif /* ERRCLS_INT_PAR */
      RETVALUE(RFAILED);
   }

   /* get the SCT SAP control block */
   sctSap = sbGlobalCb.sctSaps[spId];

   /* SCTP Upgrade: Taking out for robustness */
   /* validate the assocId */
   SB_CHK_SPASSOCID(spAssocId, ret);
   if ( ret != ROK )
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB065, (ErrVal)spAssocId,
                 "SbUiSctHBeatReq: Invalid association ID");
      /* can't send confirm since assoc CB can't be resolved */
      /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */     
#endif
      SB_LM_GEN_ALARM(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT, \
                   LCM_CAUSE_INV_PAR_VAL, spId, LSB_SW_RFC_REL0);
      RETVALUE(RFAILED);
   }

   /* get the association control block */
   assocCb = sbGlobalCb.assocCb[spAssocId];

   addrCb = (SbAddrCb *)NULLP;

/* sb009.103: IPV4IPV6 changes */
#ifdef SB_IPV4IPV6_COMBINED
   hbAddrFlag = FALSE;
#else
   if ( (status == SCT_HBEAT_ENB_DTA) || (status == SCT_HBEAT_DIS_DTA) )
   {
      /* get the address control block */
      addrCb = sbPmGetAddrCb(assocCb, dstNAddr);
      /* validate the address */
      if ( addrCb == (SbAddrCb *) NULLP )
      {
         SBLOGERROR(ERRCLS_INT_PAR, ESB066, (ErrVal)0,
                    "SbUiSctHBeatReq: primary destination address invalid");
         SbUiSctHBeatCfm(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                         dstNAddr, status, SCT_NOK, SCT_CAUSE_INV_PAR_VAL);
         RETVALUE(RFAILED);
      }

      if (addrCb->sndTo != TRUE)
      {
         SbUiSctHBeatCfm(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                         dstNAddr, status, SCT_NOK, SCT_CAUSE_INV_PAR_VAL);
         RETVALUE(RFAILED);
      }

   }
#endif
     /*sb075.102: Enable/disable on all paths of this destination*/
   /* enable/disable on one destination address */
   if ( (status == SCT_HBEAT_ENB_DTA) || (status == SCT_HBEAT_DIS_DTA) )
   {
       l = &(assocCb->sbAcCb.addrLst);
       n = cmLListFirst(l);
    
       /* enable/disable on an association */
       for ( i = 0; i < cmLListLen(l); i++)
       {
          addrCb = (SbAddrCb *)n->node;
          if ( addrCb != (SbAddrCb *) NULLP )
          {
              ret = sbPmCompNAddr(dstNAddr, &(addrCb->addr));
              if (ret == ROK)
              {
                  if (addrCb->sndTo == TRUE)
                  {
/* sb009.103: IPV4IPV6 changes */
#ifdef SB_IPV4IPV6_COMBINED
                     hbAddrFlag = TRUE;
#endif
                     if ( status == SCT_HBEAT_ENB_DTA )
                     {
                        sbPmHBeatEnb(addrCb, intervalTime);
                     }
                     else if ( status == SCT_HBEAT_DIS_DTA )
                     {
                        sbPmHBeatDis(addrCb);
                     }
                  }
              }
          }
          n = cmLListNext(l);
       }
/* sb009.103: IPV4IPV6 changes */
#ifdef SB_IPV4IPV6_COMBINED
      if (hbAddrFlag != TRUE)
      {
         SbUiSctHBeatCfm(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                         dstNAddr, status, SCT_NOK, SCT_CAUSE_INV_PAR_VAL);
         RETVALUE(RFAILED);
      }
#endif
      SbUiSctHBeatCfm(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                      dstNAddr, status, SCT_OK, SCT_CAUSE_NOT_APPL);
      RETVALUE(ROK);
   }

   l = &(assocCb->sbAcCb.addrLst);
   n = cmLListFirst(l);

   /* enable/disable on an association */
   for ( i = 0; i < cmLListLen(l); i++)
   {
      addrCb = (SbAddrCb *)n->node;
      if (addrCb->sndTo == TRUE)
      {
         if ( status == SCT_HBEAT_ENB_ASSOC )
         {
            sbPmHBeatEnb(addrCb, intervalTime);
         }
         else if ( status == SCT_HBEAT_DIS_ASSOC )
         {
            sbPmHBeatDis(addrCb);
         }
      }

      n = cmLListNext(l);
   }

   SbUiSctHBeatCfm(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                   dstNAddr, status, SCT_OK, SCT_CAUSE_NOT_APPL);
   RETVALUE(ROK);
}/* SbUiSctHBeatReq() */

/*
*
*       Fun:   SbUiSctDatReq
*
*       Desc:  Primitive Request to send Data to a peer.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: <none>
*
*       File:  sb_bdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 SbUiSctDatReq
(
Pst                  *pst,              /* Post structure */
SpId                  spId,             /* Service provider SAP ID */
UConnId               spAssocId,        /* Service provider association ID */
CmNetAddr            *dstNAddr,         /* New primary network address */
SctStrmId             strmId,           /* Stream ID */
Bool                  unorderFlg,       /* unordered delivery */
Bool                  nobundleFlg,      /* no bundling  */
U16                   lifeTime,         /* datagram lifetime value */
U32                   protId,           /* Protocol ID */
Buffer               *mBuf              /* message buffer */
)
#else
PUBLIC S16 SbUiSctDatReq(pst, spId, spAssocId, dstNAddr, strmId, unorderFlg,
                         nobundleFlg, lifeTime, protId, mBuf)
Pst                  *pst;              /* Post structure */
SpId                  spId;             /* Service provider SAP ID */
UConnId               spAssocId;        /* Service provider association ID */
CmNetAddr            *dstNAddr;         /* New primary network address */
SctStrmId             strmId;           /* Stream ID */
Bool                  unorderFlg;       /* unordered delivery */
Bool                  nobundleFlg;      /* no bundling  */
U16                   lifeTime;         /* datagram lifetime value */
U32                   protId;           /* Protocol ID */
Buffer               *mBuf;             /* message buffer */
#endif
{
   /* local parameters */
   SbSctSapCb           *sctSap;
   SbSctAssocCb         *assocCb;
   SbAddrCb             *addrCb;
   S16                   ret;
   SbQueuedChunk        *chunk;
   U32                   nmbQPkt;
   /* sb034.103: Initialized bufLen variable to zero */
   MsgLen                bufLen = 0;
   U16                   mtu = 0;
   U16                   numChunks = 0;
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   S8                    ipv6Addr1[SB_IPV6STR_SIZE];
   S8                    ipv6Addr2[SB_IPV6STR_SIZE];
   U8                    *tempIpv6Addr;
#endif

   TRC3(SbUiSctDatReq)

#ifdef SS_MULTIPLE_PROCS

   if(SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                         (void **)&sbGlobalCbPtr) != ROK)
   {
     SBLOGERROR(ERRCLS_DEBUG, ESB067, 0,
               "SbUiSctDatReq () failed, cannot derive sbGlobalCbPtr");
     RETVALUE(FALSE);
   }

   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
         "-------SCTP------(proc(%d), ent(%d), inst(%d))--------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));

#endif /* SS_MULTIPLE_PROCS */

/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
       "SbUiSctDatReq(pst, spId(%d), spAssocId(%d), dstNAddr, strmId(%d), \
       unorderFlg(%d), nobundleFlg(%d), lifeTime(%d), protId(%d), mBuf)\n",
       spId, spAssocId, strmId, unorderFlg, nobundleFlg, lifeTime, protId));
#else
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
       "SbUiSctDatReq(pst, spId(%d), spAssocId(%ld), dstNAddr, strmId(%d), \
       unorderFlg(%d), nobundleFlg(%d), lifeTime(%d), protId(%ld), mBuf)\n",
       spId, spAssocId, strmId, unorderFlg, nobundleFlg, lifeTime, protId));
#endif /* BIT_64 */

#ifndef SS_MULTIPLE_PROCS
   UNUSED(pst);
#endif  /* SS_MULTIPLE_PROCS */

   /* Sanity checks */

   /* check the SpId. *
    * sb080.102: removing the sap id check out of ERRCLASS*/
   SB_CHK_SPID(spId, LCM_EVENT_UI_INV_EVT, ret);
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB068, (ErrVal)spId,
                 "SbUiSctDatReq: Invalid spId");
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }

   /* get the SCT SAP control block */
   sctSap = sbGlobalCb.sctSaps[spId];

   /*sb077.102: Removing the association validity check out of ERRCLS_INT_PAR*
   * validate the assocId */
   SB_CHK_SPASSOCID(spAssocId, ret);
   if ( ret != ROK )
   {
/*sb080.102:Including the debug print in the ERRCLASS*/
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB069, (ErrVal)spAssocId,
                 "SbUiSctDatReq: Invalid association ID");
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */
      /* sb024.103: Included protId parameter in status indication */
#ifdef SCT7
      /* sb031.103:Added new cause SCT_CAUSE_NO_ASSOC, when user requested 
       * SuAssocId match not found in any SbSctAssocCb's*/ 
      SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, 0, spAssocId, dstNAddr,
            SCT_STATUS_SND_FAIL, SCT_CAUSE_NO_ASSOC, protId, mBuf);
#else
      SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, 0, spAssocId, dstNAddr,
            SCT_STATUS_SND_FAIL, SCT_CAUSE_NO_ASSOC, mBuf);
#endif
      RETVALUE(RFAILED);
   }

   /* get the association control block */
   assocCb = sbGlobalCb.assocCb[spAssocId];

   /* sb020.103: NULL check for dstNAddr */
#if (ERRCLASS & ERRCLS_DEBUG)
   if ( dstNAddr == (CmNetAddr *)NULLP )
   {
      SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
      "SbUiSctDatReq: dstNAddr is NULLL\n"));
	  /* sb024.103: Included protId parameter in status indication */
#ifdef SCT7
	  SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
			  spAssocId,dstNAddr,SCT_STATUS_INV, SCT_CAUSE_INV_PAR_VAL,
			  protId, mBuf);
#else
	  SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
			  spAssocId,dstNAddr,SCT_STATUS_INV, SCT_CAUSE_INV_PAR_VAL,
			  mBuf);
#endif	   
	  RETVALUE( RFAILED );
   }
#endif/* (ERRCLASS & ERRCLS_DEBUG) */   

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* sb023.102 -  Check is dstNAddress is not NULLP before accessing it */
   if ( (dstNAddr != (CmNetAddr *)NULLP ) &&
        (dstNAddr->type != CM_NETADDR_NOTPRSNT ) )
   {
      /* validate the address */
      addrCb = sbPmGetAddrCb(assocCb, dstNAddr);
      if ( addrCb == (SbAddrCb *) NULLP )
      {
         SBLOGERROR(ERRCLS_INT_PAR, ESB070, (ErrVal)0,
                    "SbUiSctDatReq: Invalid destination address");
		 /* sb024.103: Included protId parameter in status indication */
#ifdef SCT7
		 SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
				 spAssocId, dstNAddr, SCT_STATUS_SND_FAIL,
				 SCT_CAUSE_INV_PAR_VAL, protId, mBuf);
#else
		 SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
				 spAssocId, dstNAddr, SCT_STATUS_SND_FAIL,
				 SCT_CAUSE_INV_PAR_VAL, mBuf);
#endif
		 RETVALUE(RFAILED);
	  }
   }
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */

   /* get the best address control block */
   /* sb023.102 - Performance Change, If dstNAddress is not specified or if
    * specified and not present then select the primary destination address if
    * it is active */

   if (dstNAddr == (CmNetAddr *)NULLP )
      RETVALUE(RFAILED);
   /*sb075.102: Changes to choose a addressCb for which the rtxCount is zero
    because if the rtxCount has not reached max value the path is still active 
    The path is fine only if the rtxCount=0.*/
  /* sb019.103: Added NULL check for localConn */
   if ( ((dstNAddr == (CmNetAddr *)NULLP )   ||
        ((dstNAddr != (CmNetAddr *)NULLP) &&
        (dstNAddr->type == CM_NETADDR_NOTPRSNT))) &&
        (assocCb->sbAcCb.pri->active == SCT_PATH_ACTIVE) && 
        (assocCb->sbAcCb.pri->sndTo == TRUE) && 
        (assocCb->sbAcCb.pri->rtxCnt == 0) &&
     /* RFC 4460 section 2.36 */
        (assocCb->sbAcCb.pri->confirmed == TRUE) &&
        (assocCb->sbAcCb.pri->localConn != (SbLocalAddrCb *)NULLP) && 
        (assocCb->sbAcCb.pri->localConn->connected == TRUE) )
   {
       addrCb = assocCb->sbAcCb.pri;
   }
   else
   {
       addrCb = sbPmGetBestAddrCb(assocCb, dstNAddr);
       /*sb035.103: Fix for KlockWorks issue*/
#if ( ERRCLASS & ERRCLS_DEBUG )
       if(addrCb == NULLP) 
          RETVALUE(RFAILED);
#endif /* ERRCLS_DEBUG */

   }
   /* Patch sb031.102 IPV6 Support Added */
   if((dstNAddr->type == CM_NETADDR_IPV4) && (addrCb->addr.type == CM_NETADDR_IPV4))
   {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctDatReq: requestedAddr = %u, selectedAddress = %u, type = %d\n",
          dstNAddr->u.ipv4NetAddr, addrCb->addr.u.ipv4NetAddr, dstNAddr->type));
#else
      SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctDatReq: requestedAddr = %lu, selectedAddress = %lu, type = %d\n",
          dstNAddr->u.ipv4NetAddr, addrCb->addr.u.ipv4NetAddr, dstNAddr->type));
#endif /* BIT_64 */
   }
#ifdef SB_IPV6_SUPPORTED
   if((dstNAddr->type == CM_NETADDR_IPV6) && (addrCb->addr.type == CM_NETADDR_IPV6))
   {
      tempIpv6Addr = dstNAddr->u.ipv6NetAddr;
      SB_CPY_IPV6ADSTR(ipv6Addr1, tempIpv6Addr)

      tempIpv6Addr = addrCb->addr.u.ipv6NetAddr;
      SB_CPY_IPV6ADSTR(ipv6Addr2, tempIpv6Addr)

      /* Patch sb031.102 IPV6 Support Added */
      SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctDatReq: requestedAddr = %s, selectedAddress = %s, type = %d\n",
          ipv6Addr1, ipv6Addr2, dstNAddr->type));

   }
#endif

   /* shouldn't be necessary to validate since if an address can't be found
    * then the assoc should have been aborted anyway */

#if ( ERRCLASS & ERRCLS_DEBUG )
   /* neg. return for above function only occurs in ERRCLS_DEBUG */
   if ( addrCb == (SbAddrCb *) NULLP )
   {
      SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
             "SbUiSctDatReq: could not find best addr. to send DATA on\n"));
	  /* sb024.103: Included protId parameter in status indication */
#ifdef SCT7
	  SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
			  spAssocId, dstNAddr, SCT_STATUS_SND_FAIL,
			  SCT_CAUSE_UNKNOWN, protId, mBuf);
#else
	  SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
			  spAssocId, dstNAddr, SCT_STATUS_SND_FAIL,
			  SCT_CAUSE_UNKNOWN, mBuf);
#endif
	  RETVALUE(RFAILED);
   }
#endif

   /* check the out streams parameter */
#if (ERRCLASS & ERRCLS_INT_PAR)
   if ( strmId >= sbGlobalCb.genCfg.maxNmbOutStrms )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB071, (ErrVal)strmId,
                 "SbUiSctDatReq: Invalid strmId");
	  /* sb024.103: Included protId parameter in status indication */
#ifdef SCT7
	  SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
			  spAssocId, dstNAddr, SCT_STATUS_SND_FAIL,
			  SCT_CAUSE_INV_PAR_VAL, protId, mBuf);
#else
	  SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
			  spAssocId, dstNAddr, SCT_STATUS_SND_FAIL,
			  SCT_CAUSE_INV_PAR_VAL, mBuf);
#endif	  

	  RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */

   /* sb023.102 - Check the established state first & later check the rest of
    * the states - performance change */
   if (assocCb->assocState != SB_ST_ESTABLISHED)
   {
       /* check the state */
       if ( (assocCb->assocState == SB_ST_SDOWN_PEND) ||
            (assocCb->assocState == SB_ST_SDOWN_SENT) ||
            (assocCb->assocState == SB_ST_SDOWN_RCVD) ||
            (assocCb->assocState == SB_ST_SDOWNACK_SENT) )
       {
          SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                 "SbUiSctDatReq: SHUTDOWN in progress\n"));
		  /* sb024.103: Included protId parameter in status indication */
#ifdef SCT7
		  SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
				  spAssocId, dstNAddr, SCT_STATUS_SND_FAIL,
				  SCT_CAUSE_SHUTDOWN_PRGS, protId, mBuf);
#else
		  SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
				  spAssocId, dstNAddr, SCT_STATUS_SND_FAIL,
				  SCT_CAUSE_SHUTDOWN_PRGS, mBuf );
#endif		  

		  RETVALUE(RFAILED);
	   }
	   if ( (assocCb->assocState == SB_ST_CLOSED) ||
			   (assocCb->assocState == SB_ST_OPEN) ||
			   (assocCb->assocState == SB_ST_COOKIE_WAIT))
       {
          SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                 "SbUiSctDatReq: Invalid state\n"));
		  /* sb024.103: Included protId parameter in status indication */
#ifdef SCT7
		  SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
				  spAssocId, dstNAddr, SCT_STATUS_SND_FAIL,
				  SCT_CAUSE_INV_STATE, protId, mBuf);
#else
		  SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
				  spAssocId, dstNAddr, SCT_STATUS_SND_FAIL,
				  SCT_CAUSE_INV_STATE, mBuf);
#endif

		  RETVALUE(RFAILED);
	   }
   }

   /* sb023.102 - Get the number of Qed packets directly, don't call any
    * functions - performance change */
   /* Flow control */
   nmbQPkt = cmLListLen(&(assocCb->sbDbCb.congestionQ))    + 
             cmLListLen(&(assocCb->sbDbCb.tsnWaitingQOrd)) +
             cmLListLen(&(assocCb->sbDbCb.tsnWaitingQUnord));

   /* sb023.102  - Performance Fix, Instead of SB_QUERY_MTU, we will directly
    * get the mtu from the mtuIndex  in AddrCb */
   SB_GET_MTU(addrCb, mtu, ret);
   /* sb051.102: Cheking for MTU discovery error */  
/* sb019.103: Fix for the  ERRCLASS issue */
      if ( ret != ROK )
      {
 #if ( ERRCLASS & ERRCLS_DEBUG )
         SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                "SbUiSctDatReq: Path MTU discovery failed\n"));
 #endif /* ERRCLS_DEBUG */
         mtu = sbGlobalCb.genCfg.mtuInitial;
      }

   /* sb051.102: Checking the error for SSI function call */
   ret = SFndLenMsg(mBuf, &(bufLen));
   if (ret != ROK)
   {
      SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                 "SbUiSctDatReq: Find length message failed\n"));
	  /* sb024.103: Included protId parameter in status indication */
#ifdef SCT7	  
	  SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
			  spAssocId, dstNAddr, SCT_STATUS_SND_FAIL,
			  SCT_CAUSE_UNKNOWN, protId, mBuf);
#else
	  SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
			  spAssocId, dstNAddr, SCT_STATUS_SND_FAIL,
			  SCT_CAUSE_UNKNOWN, mBuf);
#endif
	  RETVALUE( RFAILED );
   }
   /* If the user data is larger than the maximum size defined by the upper layer, drop it */
#ifdef SB_ETSI
   if( bufLen > sctSap->sctSapCfg.reConfig.maxDataSize )
   {
      SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf, \
                 "SbUiSctDatReq: user data size is greater than maxDataSize\n"));
	  /* sb024.103: Included protId parameter in status indication */
#ifdef SCT7     
	  SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
			  spAssocId, dstNAddr, SCT_STATUS_SND_FAIL,
			  SCT_CAUSE_UNKNOWN, protId, mBuf);
#else
	  SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
			  spAssocId, dstNAddr, SCT_STATUS_SND_FAIL,
			  SCT_CAUSE_UNKNOWN, mBuf);

#endif	  
	  RETVALUE( RFAILED );
   }
#endif /* SB_ETSI */

   numChunks = (U16)((bufLen / mtu) + 1);

   if ( (numChunks + sbGlobalCb.txChunks) >= sbGlobalCb.genCfg.maxNmbTxChunks )
   {
      /* queues are full */
      SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
             "SbUiSctDatReq: queues are full, flow control dropping\n"));
	  /* sb024.103: Included protId parameter in status indication */
#ifdef SCT7
	  SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
			  spAssocId, dstNAddr, SCT_STATUS_SND_FAIL, SCT_CAUSE_QFULL, protId,
			  mBuf);
#else
	  SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
			  spAssocId, dstNAddr, SCT_STATUS_SND_FAIL, SCT_CAUSE_QFULL,
			  mBuf);
#endif	  
	  SbUiSctFlcInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
			  SCT_FLC_DROP);

      RETVALUE(RFAILED);
   }

   if ( nmbQPkt >= sctSap->sctSapCfg.reConfig.flcUpThr )
   {
      /* breached FLC upper threshold */
      if ( assocCb->flcFlg == FALSE )
      {
         SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
             "SbUiSctDatReq: flow control started\n"));

         SbUiSctFlcInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                       SCT_FLC_START);
         assocCb->flcFlg = TRUE;
      }
   }

   /* create new chunk */
   /* sb023.102 - To reduce number of cmMemset operations we are directly
    * allocating SbQueuedChunk sturture, It is anyway initialised field by
    * field so there is no need for cmMemSet - performance change */
   SB_GETSBUF(sizeof(SbQueuedChunk), chunk, ret);
   if ( ret != ROK )
   {
      SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
             "SbUiSctDatReq: could not alloc. mem. for new chunk\n"));
	  /* sb024.103: Included protId parameter in status indication */
#ifdef SCT7
	  SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
			  spAssocId, dstNAddr, SCT_STATUS_SND_FAIL, SCT_CAUSE_OUTRES,
			  protId, mBuf);
#else
	  SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
			  spAssocId, dstNAddr, SCT_STATUS_SND_FAIL, SCT_CAUSE_OUTRES,
			  mBuf);
#endif

	  RETVALUE(RFAILED);
   }

   /* set new chunk values */
   chunk->noBundleFlg  = nobundleFlg;
   chunk->resendFlg    = FALSE;
   chunk->sendFlg      = FALSE;
   chunk->startFlg     = TRUE;
   chunk->endFlg       = TRUE;
   chunk->dfFlg        = FALSE;
   chunk->rttInProg    = FALSE;
   chunk->unorderedFlg = unorderFlg;
   chunk->qState       = SB_DB_INVALQ;
   chunk->tsn          = 0;
   chunk->seqNum       = 0;
   chunk->stream       = strmId;
   chunk->holeCnt      = 0;
   chunk->lifetime     = lifeTime;
   chunk->time         = 0;
   chunk->addrCb       = addrCb;
   chunk->spAssocId    = spAssocId;
   chunk->mBuf         = mBuf;
   chunk->protId       = protId;
   /* sb029.102: Duplicate Retransmission */
   chunk->dlvrCfmChunk = FALSE; /* default value, not confirmed */
   /* RFC 4460 section 2.8: Fast Retransmit only once */
   chunk->fastRtrFlg   = FALSE;

   /* initialize the lifetime timer */
   cmInitTimers(&(chunk->lifetimeTmr), 1);

   /* deliver to sequenced delivery */
   ret = sbSqDeliver(assocCb, chunk);
   if ( ret != ROK )
   {
      /* lose the chunk */
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "SbUiSctDatReq: Could not send chunk to Sequ. Deliv.\n"));

      RETVALUE(RFAILED);
   }

   /* update statistics counterts */
   sbGlobalCb.genSts.sbByteSts.bytesRx += bufLen;
   sctSap->sctSts.sbByteSts.bytesRx    += bufLen;

   /* no confirm */
   RETVALUE(ROK);
}/* SbUiSctDatReq() */

/*
*
*       Fun:   SbUiSctStaReq
*
*       Desc:  Primitive Request for Status Information.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: <none>
*
*       File:  sb_bdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 SbUiSctStaReq
(
Pst                  *pst,              /* Post structure */
SpId                  spId,             /* Service provider SAP ID */
UConnId               spAssocId,        /* Service provider association ID */
CmNetAddr            *dstNAddr,         /* New primary network address */
U8                    staType           /* Status type */
)
#else
PUBLIC S16 SbUiSctStaReq(pst, spId, spAssocId, dstNAddr, staType)
Pst                  *pst;              /* Post structure */
SpId                  spId;             /* Service provider SAP ID */
UConnId               spAssocId;        /* Service provider association ID */
CmNetAddr            *dstNAddr;         /* New primary network address */
U8                    staType;          /* Status type */
#endif
{
   /* local parameters */
   SbSctSapCb           *sctSap;
   SbSctAssocCb         *assocCb;
   SbAddrCb             *addrCb;
   S16                   ret;
   CmLListCp            *l;
   CmLList              *n;
   U32                   i;
   SctStaInfo            staInfo;

   TRC3(SbUiSctStaReq)

#ifdef SS_MULTIPLE_PROCS

   if(SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                         (void **)&sbGlobalCbPtr) != ROK)
   {
     SBLOGERROR(ERRCLS_DEBUG, ESB072, 0,
               "SbUiSctStaReq () failed, cannot derive sbGlobalCbPtr");
     RETVALUE(FALSE);
   }

   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
         "-------SCTP------(proc(%d), ent(%d), inst(%d))--------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));

#endif /* SS_MULTIPLE_PROCS */

/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
       "SbUiSctStaReq(pst, spId(%d), spAssocId(%u), dstNAddr, staType(%d))\n",
       spId, spAssocId, staType));
#else
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
       "SbUiSctStaReq(pst, spId(%d), spAssocId(%lu), dstNAddr, staType(%d))\n",
       spId, spAssocId, staType));
#endif /* BIT_64 */

#ifndef SS_MULTIPLE_PROCS
   UNUSED(pst);
#endif  /* SS_MULTIPLE_PROCS */

   ret = ROK;

   /* Sanity Checks */
   /* SCTP Upgrade: Taking out for robustness */
   /* check the SpId. */
   SB_CHK_SPID(spId, LCM_EVENT_UI_INV_EVT, ret);
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB073, (ErrVal)spId,
                 "SbUiSctStaReq: Invalid spId");
#endif /* ERRCLS_INT_PAR */
      RETVALUE(RFAILED);
   }

   /* get the SCT SAP control block */
   sctSap = sbGlobalCb.sctSaps[spId];

   SB_ZERO(&staInfo, sizeof(SctStaInfo));

   staInfo.staType = staType;

   /* SCTP Upgrade: Taking out for robustness */
   /* validate the assocId */
   SB_CHK_SPASSOCID(spAssocId, ret);
   if ( ret != ROK )
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB074, (ErrVal)spAssocId,
                 "SbUiSctDatReq: Invalid association ID");
#endif
      SbUiSctStaCfm(&(sctSap->sctPst), sctSap->suId, 0, dstNAddr,
                    SCT_NOK, SCT_CAUSE_INV_PAR_VAL, &staInfo);
      RETVALUE(RFAILED);
   }

   /* get the association control block */
   assocCb = sbGlobalCb.assocCb[spAssocId];

   /* get the address control block */
   addrCb = sbPmGetAddrCb(assocCb, dstNAddr);

/* sb019.103: Added NULL check for localConn */   
/* validate the address */
   if ( ((addrCb == (SbAddrCb *) NULLP)  ||
        (addrCb->localConn == (SbLocalAddrCb *) NULLP)) && \
        (staType == SCT_GET_ADDR_INFO))
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB075, (ErrVal)0,
                 "SbUiSctDatReq: Invalid address");
      SbUiSctStaCfm(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                    dstNAddr, SCT_NOK, SCT_CAUSE_INV_PAR_VAL,
                    &staInfo);
      RETVALUE(RFAILED);
   }

   switch ( staType )
   {
      case SCT_RTRV_UNSENT_DGMS:
         (Void) sbSqRtrvUnsent(assocCb);
         break;

      case SCT_RTRV_UNACK_DGMS:
         (Void) sbAcRtrvUnack(assocCb);
         break;

      case SCT_RTRV_UNDEL_DGMS:
         (Void) sbSqRtrvUndel(assocCb);
         break;

      case SCT_GET_ASSOC_INFO:
      {
         /*sb075.102: Changes for path enhancements. Populate only unique dest
          addresses from the list as we have all possible pairs now, but space 
          is there only for unique addresses in staInfo.u.assocInfo.dstAddrLst.nAddr */
          U8      srcAddrCount = 0;
          U8      destAddrCount = 0;
          SbSctEndpCb    *tmpEndpCb;                                            
          tmpEndpCb = sbGlobalCb.endpCb[assocCb->endpId];  
          srcAddrCount = tmpEndpCb->localAddrLst.nmb;

         staInfo.u.assocInfo.rwnd       = assocCb->sbAcCb.rwnd;
         staInfo.u.assocInfo.connSta    = assocCb->assocState;
         /*sb075.102: Copy the original primary address*/
         /*sb080.102:Adjusting the macro call to single line*/
         SB_CPY_NADDR(&(staInfo.u.assocInfo.priDstAddr), &(assocCb->priOrig->addr));
         staInfo.u.assocInfo.dstPort    = assocCb->peerPort;

         l = &(assocCb->sbAcCb.addrLst);
         n = cmLListFirst(l);
         staInfo.u.assocInfo.dstAddrLst.nmb = 0;
         /*sb075.102: Since we have source address count we can find unique
          dest addresses as all unique are there with first source in the list*/
         /*sb035.103: Fix for KlockWorks issue*/
         destAddrCount = (U8)((cmLListLen(l))/srcAddrCount);
         for (i = 0; i < destAddrCount; i++ )
         {
            addrCb = (SbAddrCb *)(n->node);
            SB_CPY_NADDR(&(staInfo.u.assocInfo.dstAddrLst.nAddr \
                         [staInfo.u.assocInfo.dstAddrLst.nmb]), \
                         &(addrCb->addr));
            staInfo.u.assocInfo.dstAddrLst.nmb++;
            n = cmLListNext(l);
         }

         SbUiSctStaCfm(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                       dstNAddr, SCT_OK, SCT_CAUSE_NOT_APPL,
                       &staInfo);
         break;
      }

      case SCT_GET_ADDR_INFO:
      {
         staInfo.u.addrInfo.rtt    = addrCb->srtt;
         staInfo.u.addrInfo.rto    = addrCb->rto;
         staInfo.u.addrInfo.cwnd   = addrCb->cwnd;
         staInfo.u.addrInfo.active = addrCb->active;
         SbUiSctStaCfm(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                       dstNAddr, SCT_OK, SCT_CAUSE_NOT_APPL,
                       &staInfo);
         break;
      }

      case SCT_GET_RTRV_INFO:
      {
         staInfo.u.rtrvInfo.lastAckTsn    = assocCb->sbAcCb.cumTsn;
         staInfo.u.rtrvInfo.lastSentTsn   = assocCb->sbAcCb.nextLocalTsn - 1;
         staInfo.u.rtrvInfo.nmbUnsentDgms =
            (U16)sbDbQPackets(assocCb, SB_DB_TSNWAITINGQ);
         staInfo.u.rtrvInfo.nmbUnackDgms  =
            (U16)sbDbQPackets(assocCb, SB_DB_CONGESTIONQ);
         staInfo.u.rtrvInfo.nmbUndelDgms  =
            (U16)( sbDbQPackets(assocCb, SB_DB_SEQUENCEDQ) +
              sbDbQPackets(assocCb, SB_DB_ASSEMBLYQ) );
         SbUiSctStaCfm(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                       dstNAddr, SCT_OK, SCT_CAUSE_NOT_APPL,
                       &staInfo);
         break;
      }

      case SCT_GET_FLC_INFO:
         if (assocCb->flcFlg == TRUE)
         {
            SbUiSctFlcInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                          SCT_FLC_ACTIVE);
         }
         else
         {
            SbUiSctFlcInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                          SCT_FLC_INACTIVE);
         }
         break;

      default:
#if (ERRCLASS & ERRCLS_INT_PAR)
         SBLOGERROR(ERRCLS_INT_PAR, ESB076, (ErrVal) staType,
                    "SbUiSctDatReq: Invalid status type");
         SbUiSctStaCfm(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                       dstNAddr, SCT_NOK, SCT_CAUSE_INV_PAR_VAL,
                       &staInfo);
#endif
         break;
   }

   /* All the confirms have been sent by now */
   RETVALUE(ROK);
}/* SbUiSctStaReq() */

/****************************************************************************/
/* HIT lower interface primitives                                           */
/****************************************************************************/


/*
*
*       Fun:   SbLiHitConCfm
*
*       Desc:  This function is received from the layer below in
*              responce to a ServOpen request.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes:
*
*       File:  sb_bdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 SbLiHitConCfm
(
Pst     *pst,    /* Post structure containing INFO on the src and dst */
SuId    suId,    /* ID of the TSAP in SCTP layer*/
UConnId suConId, /* Connection ID used by SCTP */
UConnId spConId, /* Connection used by service provider */
CmTptAddr *localAddr /* Address that was connected to */
)
#else
PUBLIC S16 SbLiHitConCfm(pst, suId, suConId, spConId, localAddr)
Pst     *pst;    /* Post structure containing INFO on the src and dst */
SuId    suId;    /* ID of the TSAP */
UConnId suConId; /* Connection ID used by SCTP */
UConnId spConId; /* Connection used by service provider */
CmTptAddr *localAddr; /* Address that was connected to */
#endif
{
   SbTSapCb *tSap;
   SbLocalAddrCb *localAddrCb;
   U16 i;
   U16 cnt;
   S16 err;
/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   SbAddrPortCb    *addrPortCb;
   SbAddrPortEntry addrPortEntry;
   UConnId         spEndpId;
   SbSctEndpCb     *endpCb;
   SbSctSapCb      *sctSap;
#else
   CmNetAddr addr;
#endif
   Mem sMem;

#ifndef SS_MULTIPLE_PROCS
   UNUSED( pst );
#endif

   TRC3( SbLiHitConCfm )

#ifdef SS_MULTIPLE_PROCS

   if(SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                         (void **)&sbGlobalCbPtr) != ROK)
   {
     SBLOGERROR(ERRCLS_DEBUG, ESB077, 0,
               "SbLiHitConCfm () failed, cannot derive sbGlobalCbPtr");
     RETVALUE(FALSE);
   }

   SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
         "-------SCTP------(proc(%d), ent(%d), inst(%d))--------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));

#endif /* SS_MULTIPLE_PROCS */

/* sb030.103: Initialization of spEndpId. */
#ifdef SB_SOL10_MULTIPORT
   spEndpId = 0;
#endif 

/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP( DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
      "SbLiHitConCfm(pst, suId(%d), suConId(%d), spConId(%d), localAddr)\n",
      suId, suConId, spConId ) );
#else
   SBDBGP( DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
      "SbLiHitConCfm(pst, suId(%d), suConId(%ld), spConId(%ld), localAddr)\n",
      suId, suConId, spConId ) );
#endif /* BIT_64 */
   /* Sanity Checks */
#if ( ERRCLASS & ERRCLS_INT_PAR )
   if( (suId >= (SuId) sbGlobalCb.genCfg.maxNmbTSaps) || (suId < 0) )
   {
      SBLOGERROR( ERRCLS_INT_PAR, ESB078, (ErrVal) suId,
                  "SbLiHitConCfm: suId out of range");
                /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
                   SB_LM_GEN_ALARM( (U16)LCM_CATEGORY_INTERFACE, \
                    (U16)LCM_EVENT_LI_INV_EVT, \
                    (U16)LCM_CAUSE_INV_SUID, \
                    suId, \
                    LSB_SW_RFC_REL0 );
      RETVALUE( RFAILED );
   }
#endif /* ERRCLS_INT_PAR */

   /* get the SCT SAP control block */
   tSap = *(sbGlobalCb.tSaps + suId);

   /* check to see if the SAP exists */
#if ( ERRCLASS & ERRCLS_INT_PAR )
   if ( tSap == (SbTSapCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_INT_PAR, ESB079, (ErrVal) suId,
                  "SbLiHitConCfm: Sap not configured" );
                    /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */     
                   SB_LM_GEN_ALARM( (U16)LCM_CATEGORY_INTERFACE, \
                    (U16)LCM_EVENT_LI_INV_EVT, \
                    (U16)LCM_CAUSE_INV_SAP, \
                    suId, \
                    LSB_SW_RFC_REL0 );
      RETVALUE( RFAILED );
   }
#endif /* ERRCLS_INT_PAR */

/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   SB_ZERO(&addrPortEntry, sizeof(SbAddrPortEntry));

   localAddrCb = NULLP;

   if ( localAddr == (CmTptAddr *)NULLP )
   {
      addrPortEntry.localAddr.type = CM_NETADDR_IPV4;
   }
   else
   {

      if ( localAddr->type == CM_TPTADDR_IPV4 )
      {
         addrPortEntry.localAddr.type = CM_NETADDR_IPV4;
         addrPortEntry.localAddr.u.ipv4NetAddr = localAddr->u.ipv4TptAddr.address;
         addrPortEntry.port = localAddr->u.ipv4TptAddr.port;
      }
      else if ( localAddr->type == CM_TPTADDR_IPV6 )
      {
         addrPortEntry.localAddr.type = CM_NETADDR_IPV6;
         (Void) cmMemcpy((U8 *) &(addrPortEntry.localAddr.u.ipv6NetAddr),
                         (U8 *)&(localAddr->u.ipv6TptAddr.ipv6NetAddr),
                         (PTR) CM_IPV6ADDR_SIZE);
         addrPortEntry.port = localAddr->u.ipv6TptAddr.port;
      }

#if ( ERRCLASS & ERRCLS_INT_PAR )
      else
      {
         SBLOGERROR( ERRCLS_INT_PAR, ESB080, (ErrVal) 0,
                     "SbLiHitConCfm(): invalid address type" );
      /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */    
         SB_LM_GEN_ALARM( (U16)LCM_CATEGORY_INTERFACE, \
                    (U16)LCM_EVENT_LI_INV_EVT, \
                    (U16)LCM_CAUSE_INV_PAR_VAL, \
                    suId, \
                    LSB_SW_RFC_REL0 );
         RETVALUE( RFAILED );
      }
#endif /* ERRCLS_INT_PAR */

   }

   err = cmHashListFind(&(sbGlobalCb.addrPortHl),
                        (U8 *)&addrPortEntry, sizeof(SbAddrPortEntry), 0,
                        (PTR *)&addrPortCb);

   if ((err == ROK) && (addrPortCb != NULLP))
   {
      localAddrCb = addrPortCb->localAddrCb;
      spEndpId    = addrPortCb->spEndpId;
   }

#else

   SB_ZERO( &addr, sizeof(CmNetAddr) );

   if ( localAddr == (CmTptAddr *)NULLP )
   {
      addr.type = CM_NETADDR_IPV4;
   }
   else
   {

      if ( localAddr->type == CM_TPTADDR_IPV4 )
      {
         addr.u.ipv4NetAddr = localAddr->u.ipv4TptAddr.address;
         addr.type = CM_NETADDR_IPV4;
      }
      else if ( localAddr->type == CM_TPTADDR_IPV6 )
      {
         addr.type = CM_NETADDR_IPV6;
         (Void) cmMemcpy((U8 *) &(addr.u.ipv6NetAddr),
                         (U8 *)&(localAddr->u.ipv6TptAddr.ipv6NetAddr),
                         (PTR) CM_IPV6ADDR_SIZE);
      }

#if ( ERRCLASS & ERRCLS_INT_PAR )
      else
      {
         SBLOGERROR( ERRCLS_INT_PAR, ESB080, (ErrVal) 0,
                     "SbLiHitConCfm(): invalid address type" );
      /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */    
         SB_LM_GEN_ALARM( (U16)LCM_CATEGORY_INTERFACE, \
                    (U16)LCM_EVENT_LI_INV_EVT, \
                    (U16)LCM_CAUSE_INV_PAR_VAL, \
                    suId, \
                    LSB_SW_RFC_REL0 );
         RETVALUE( RFAILED );
      }
#endif /* ERRCLS_INT_PAR */

   }

   err = cmHashListFind(&(sbGlobalCb.localAddrHl),
                        (U8 *)&addr, sizeof(CmNetAddr), 0,
                        (PTR *)&localAddrCb);
#endif

/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   if (localAddrCb != (SbLocalAddrCb *)NULLP)
#else
   if ( (err == ROK) && (localAddrCb != (SbLocalAddrCb *)NULLP) )
#endif
   {
      if ( (localAddrCb->suId == suId) &&
           (localAddrCb->suConId == suConId) &&
           (localAddrCb->connected == FALSE) )
      {
         localAddrCb->spConId = spConId;
         localAddrCb->connected = TRUE;
         /* sb044.102: Connection Confirm received */
         localAddrCb->conRetryAttempt = 0;
      }
      else if ( (localAddrCb->suId == suId) &&
                (localAddrCb->suOtherConId == suConId) &&
                (localAddrCb->otherConnected == FALSE) )
      {
         localAddrCb->spOtherConId = spConId;
         localAddrCb->otherConnected = TRUE;
         /* sb044.102: Connection Confirm received */
         localAddrCb->conRetryAttempt = 0;
      }
      else  if ( (sbGlobalCb.dnsInfo.suId == suId) &&
                 (sbGlobalCb.dnsInfo.suConId == suConId) )
      {
         /* don't fail just continue */
      }
      
#if (ERRCLASS & ERRCLS_DEBUG)
      else
      {
         SBLOGERROR(ERRCLS_DEBUG, ESB081, (ErrVal) 0,
                 "SbLiHitConCfm: Inconsistancy with conn. IDs and addresses");
      }
#endif /* ERRCLS_DEBUG */

   }

   cnt = 0;

/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   if (!((tSap->tSapCfg.reConfig.sbDnsCfg.useDnsLib == TRUE) && 
       (sbGlobalCb.dnsInfo.suId == suId) &&
       (sbGlobalCb.dnsInfo.suConId == suConId)))
   {
   for ( i = 0; i < (sbGlobalCb.genCfg.maxNmbEndp * SCT_MAX_NET_ADDRS); i++)
#else
   for ( i = 0; i < sbGlobalCb.genCfg.maxNmbSrcAddr; i++)
#endif
   {
      localAddrCb = *(sbGlobalCb.localAddrCb + i);

      if ( localAddrCb != (SbLocalAddrCb *)NULLP )
      {
#ifdef SB_SOL10_MULTIPORT
         if ( localAddrCb->spEndpId == spEndpId )
#else
         if ( localAddrCb->suId == tSap->tSapCfg.suId )
#endif
         {
#if SB_OLD_SERVER_MODE
            if ( localAddrCb->connected == FALSE )
            {
               cnt++;
            }
            if ( localAddrCb->otherConnected == FALSE )
            {
               cnt++;
            }
#else
            /* sb008.12 - Condition for UDP has been removed from here as 
             * for UDP also now connected flag will be used */
            if (localAddrCb->connected == FALSE) 
            {
               if (localAddrCb->ownAddr.type == CM_NETADDR_IPV4)
               {
                  if (((tSap->ipv4_any == TRUE) &&
                     (localAddrCb->ownAddr.u.ipv4NetAddr
                     == CM_INET_INADDR_ANY)) ||
                     (tSap->ipv4_any == FALSE))
                  {
                     cnt++;
                  }
               }
               else if (localAddrCb->ownAddr.type == CM_TPTADDR_IPV6)
               {
                  Bool isAny;
                  SB_INET6_ISANY(localAddrCb->ownAddr.u.ipv6NetAddr,
                     &isAny)
                  if (((tSap->ipv6_any == TRUE) && (isAny == TRUE)) ||
                     (tSap->ipv6_any == FALSE))
                  {
                     cnt++;
                  }
               }
            }
#endif /* !SB_OLD_SERVER_MODE */
         }
      }
   }
/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
      if ( cnt == 0)
      {
         /* inop fix */
         endpCb = sbGlobalCb.endpCb[spEndpId];

         /* stop end point open cfm timer, if running */
         if (endpCb->timer.tmrEvnt != TMR_NONE)
         {
            SB_STOP_TMR(&(endpCb->timer));
         }

         sctSap = sbGlobalCb.sctSaps[endpCb->spId];

         /* send endpopencfm to upper layer */
         SbUiSctEndpOpenCfm( &(sctSap->sctPst), sctSap->suId, endpCb->suEndpId,
                             endpCb->spEndpId, SCT_OK, SCT_CAUSE_NOT_APPL);
      }
   }
#endif

/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   if ((tSap->tSapCfg.reConfig.sbDnsCfg.useDnsLib == TRUE) && 
       (sbGlobalCb.dnsInfo.suId == suId) &&
       (sbGlobalCb.dnsInfo.suConId == suConId))
#else
   /* In case  of Version 13 we will always open the DNS server at last */

   /* sb051.102 - DNS server is opened only when useDnsLib is TRUE for
    * this TSAP. */
   if ( ((tSap->tSapCfg.reConfig.sbDnsCfg.useDnsLib == TRUE) && 
         ( cnt == 0 ) && (sbGlobalCb.dnsInfo.suId == suId) &&
         (sbGlobalCb.dnsInfo.suConId == suConId)) ||
        ((tSap->tSapCfg.reConfig.sbDnsCfg.useDnsLib != TRUE)&&
         (cnt == 0)) )
#endif
    {
/* sb009.103 : SOL10 changes */
#ifndef SB_SOL10_MULTIPORT
       /* sb051.102 - Check if useDnsLib is TRUE */
       if(tSap->tSapCfg.reConfig.sbDnsCfg.useDnsLib == TRUE)
       {
#endif
       SBDBGP(DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
          "SbLiHitConCfm: Connection Cfm Received for DNS Server\n"));

       sbGlobalCb.dnsInfo.spConId = spConId;
       sbGlobalCb.dnsInfo.dnsState = SB_DNS_SERV_OPEN;
     
       /* sb051.102 - Moved the condition for useDnsLib */ 
         SB_ALLOC(sizeof(CmDnsCb),sbGlobalCb.dnsInfo.dnsCb, err)
         cmDnsDeInitDnsCb(sbGlobalCb.dnsInfo.dnsCb); 

         if( err != ROK )
         {
           SBLOGERROR( ERRCLS_INT_PAR, ESB082, (ErrVal) 0,
                     "SbLiHitConCfm(): Memory Allocation Failure for DNSCB" );
        /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */      
           SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, \
                            LCM_EVENT_DMEM_ALLOC_FAIL, \
                            LCM_CAUSE_MEM_ALLOC_FAIL, suId, LSB_SW_RFC_REL0);
           RETVALUE(LCM_REASON_MEM_NOAVAIL);
         }
          sMem.region = tSap->tPst.region;
          sMem.pool = tSap->tPst.pool;

         err = sbInitDnsCb(sbGlobalCb.dnsInfo.dnsCb, SB_DNS_RQSTLST_SZ, 
                   &sMem, &tSap->tSapCfg.reConfig.sbDnsCfg.dnsAddr);
         if(err != ROK)
         {
            SBDBGP(DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
                "SbLiHitConCfm: Failure returned from sbInitDnsCb \n"));
            RETVALUE(RFAILED);
         }
/* sb009.103 : SOL10 changes */
#ifndef SB_SOL10_MULTIPORT
       }
#endif


      /* stop bind timer if running */
      if (tSap->timer.tmrEvnt != TMR_NONE)
      {
         SB_STOP_TMR(&(tSap->timer));
      }

      if ( sbGlobalCb.sbMgmt.hdr.elmId.elmnt == STSBTSAP )
      {
         /* sb004.12 - Change - cfmMsg is taken as Pointer to minimise stack memory */
         SbMgmt      *cfmMsg;             /* control confirm */
         U16         ret;

         /* sb004.12 - Addition : Allocate memory for Response msg  */
         SB_ALLOC(sizeof(SbMgmt), cfmMsg, ret);
         if ( ret != ROK )
         {
            SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                 "SbLiHitConCfm: could not allocate memory for Response Structure\n"));
            RETVALUE(RFAILED);
         }

         /* zero out the confirm structure */
         SB_ZERO(cfmMsg, sizeof(SbMgmt));

         /* set the current time */
         (Void) SGetDateTime(&(cfmMsg->t.cntrl.dt));

         SBDBGP(DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
                "SbLiHitConCfm: sending CntrlCfm\n"));

/* sb003.103: Moved from GenCfg to General reConfig structure */ 
/* sb004.103: Protected under compile-time flag */
#ifdef LSB9
         sbLmSendCfm(&(sbGlobalCb.genCfg.reConfig.smPst), TCNTRL,
                     &(sbGlobalCb.sbMgmt.hdr), LCM_PRIM_OK,
                     LCM_REASON_NOT_APPL, cfmMsg);
#else
         sbLmSendCfm(&(sbGlobalCb.genCfg.smPst), TCNTRL,
                     &(sbGlobalCb.sbMgmt.hdr), LCM_PRIM_OK,
                     LCM_REASON_NOT_APPL, cfmMsg);
#endif
      
          /* sb004.12 - Addition : deallocate cfmMsg structure */
          SB_FREE(sizeof(SbMgmt), cfmMsg);

         /* zero this out so that lyr man. can process other instructions */
          SB_ZERO( &(sbGlobalCb.sbMgmt), sizeof(SbMgmt) );
      }
   }

   SBDBGP(DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
          "SbLiHitConCfm: Returning ROK\n"));

   RETVALUE( ROK );
}


/*
*
*       Fun:   SbLiHitUDatInd
*
*       Desc:  This function is received from the layer below whenever
*              data arrives at the lower interface from the peer.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes:
*
*       File:  sb_bdy1.c
*
*/

/* Patch sb031.102 IPV6 Support Added */
#ifdef LOCAL_INTF
#ifdef ANSI
PUBLIC S16 SbLiHitUDatInd
(
Pst     *pst,          /* Post structure containing INFO on the src and dst */
SuId    suId,          /* ID of the TSAP in SCTP layer*/
UConnId suConId,       /* Connection ID used by SCTP */
CmTptAddr *srcAddr,    /* Address that the data arrived from */
CmTptAddr *dstAddr,    /* Address interface on which the data arrived */
CmIpHdrParm *hdrParm,  /* IP Header parameters */
CmTptLocalInf *localIf, /* Local interface parameter */
Buffer *mBuf           /* Message Buffer */
)
#else
PUBLIC S16 SbLiHitUDatInd(pst, suId, suConId, srcAddr, dstAddr, hdrParm, localIf, mBuf)
Pst     *pst;    /* Post structure containing INFO on the src and dst */
SuId    suId;    /* ID of the TSAP in SCTP layer*/
UConnId suConId; /* Connection ID used by SCTP */
CmTptAddr *srcAddr; /* Address that the data arrived from */
CmTptAddr *dstAddr; /* Address interface on which the data arrived */
CmIpHdrParm *hdrParm; /* IP Header parameters */
CmTptLocalInf *localIf; /* Local interface parameter */
Buffer *mBuf;    /* Message Buffer */
#endif /* ANSI */
#else
#ifdef ANSI
PUBLIC S16 SbLiHitUDatInd
(
Pst     *pst,          /* Post structure containing INFO on the src and dst */
SuId    suId,          /* ID of the TSAP in SCTP layer*/
UConnId suConId,       /* Connection ID used by SCTP */
CmTptAddr *srcAddr,    /* Address that the data arrived from */
CmTptAddr *dstAddr,    /* Address interface on which the data arrived */
CmIpHdrParm *hdrParm,  /* IP Header parameters */
Buffer *mBuf           /* Message Buffer */
)
#else
PUBLIC S16 SbLiHitUDatInd(pst, suId, suConId, srcAddr, dstAddr, hdrParm, mBuf)
Pst     *pst;    /* Post structure containing INFO on the src and dst */
SuId    suId;    /* ID of the TSAP in SCTP layer*/
UConnId suConId; /* Connection ID used by SCTP */
CmTptAddr *srcAddr; /* Address that the data arrived from */
CmTptAddr *dstAddr; /* Address interface on which the data arrived */
CmIpHdrParm *hdrParm; /* IP Header parameters */
Buffer *mBuf;    /* Message Buffer */
#endif /* ANSI */
#endif /* LOCAL_INTF */
{
   CmNetAddr srcNetAddr;
   CmNetAddr dstNetAddr;
   SbTSapCb *tSap;
   S16 err;
   MsgLen len;
   U8 ver;
   /* sb060.102 - TOS enhancement */
#ifdef SCT4
   U8 incomingTos = 0;
#endif /* SCT4 */
      /* Patch sb031.102 IPV6 Support Added */
#ifdef LOCAL_INTF
   CmTptLocalInf *intfAddr;
#endif

   TRC3( SbLiHitUDatInd );
#ifdef SS_MULTIPLE_PROCS

   if(SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                         (void **)&sbGlobalCbPtr) != ROK)
   {
     SBLOGERROR(ERRCLS_DEBUG, ESB083, 0,
               "SbLiHitUDatInd () failed, cannot derive sbGlobalCbPtr");
     RETVALUE(FALSE);
   }

   SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
         "-------SCTP------(proc(%d), ent(%d), inst(%d))--------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));

#endif /* SS_MULTIPLE_PROCS */

/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP( DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
           "SbLiHitUDatInd(pst, suId(%d), suConId(%d))\n",
           suId, suConId ) );
#else
   SBDBGP( DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
           "SbLiHitUDatInd(pst, suId(%d), suConId(%ld))\n",
           suId, suConId ) );
#endif /* BIT_64 */

   /*sb081.102 : Check for genereal configuration*/
   if ( sbGlobalCb.sbInit.cfgDone == FALSE )
   {
        SBDBGP( DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf, \
              "SbLiHitUDatInd: General configuration not done\n"));
      RETVALUE( RFAILED );
   }
#ifndef SS_MULTIPLE_PROCS
   UNUSED( pst );
#endif  /* SS_MULTIPLE_PROCS */
   len = 0;
      /* Patch sb031.102 IPV6 Support Added */
#ifdef LOCAL_INTF
   intfAddr = localIf; 
   if(localIf->intfPrsnt == TRUE)
   {
      if(dstAddr != NULL)
      {
          if(localIf->localIfAddr.type == CM_NETADDR_IPV4)
          {
             dstAddr->type = CM_TPTADDR_IPV4;
             dstAddr->u.ipv4TptAddr.address = localIf->localIfAddr.u.ipv4NetAddr;
          }
          if(localIf->localIfAddr.type == CM_NETADDR_IPV6)
          {
             dstAddr->type = CM_TPTADDR_IPV6;
             cmMemcpy((U8*)dstAddr->u.ipv6TptAddr.ipv6NetAddr, (U8 *)localIf->localIfAddr.u.ipv6NetAddr, CM_IPV6ADDR_SIZE); 
          }
      }
   }
#endif
   if (hdrParm->type == CM_HDRPARM_IPV4)
   {
      if ( (hdrParm->u.hdrParmIpv4.proto.pres == TRUE) &&
           (sbGlobalCb.genCfg.performMtu == TRUE) )
      {
         if ( (hdrParm->u.hdrParmIpv4.proto.val == CM_PROTOCOL_ICMP) &&
              (sbGlobalCb.genCfg.performMtu == TRUE) )
         {
            if (srcAddr->type == CM_TPTADDR_IPV4)
            {
               ver = 4;
            }
            else if (srcAddr->type == CM_TPTADDR_IPV6)
            {
               ver = 6;
            }
            else
            {
               ver = 0;
               SBLOGERROR( ERRCLS_INT_PAR, ESB084, (ErrVal) srcAddr->type,
                           "SbLiHitUDatInd: Incorrect address type" );

               RETVALUE( RFAILED );
            }

            if(NULLP == mBuf)
            {
               SBLOGERROR( ERRCLS_INT_PAR, ESB084, (ErrVal) srcAddr->type,
                           "mBuf is NULL" );
               RETVALUE( RFAILED );
            }
            err = sbMtuRcvIcmp(&(sbGlobalCb.mtuCp), mBuf, ver);
            SB_CHK_PUTMSG( mBuf );
            RETVALUE( err );
         }
      }
      /* sb060.102 - TOS enhancement */
#ifdef SCT4
      if (hdrParm->u.hdrParmIpv4.tos.pres == TRUE)
      {
         incomingTos = hdrParm->u.hdrParmIpv4.tos.val;
      }
#endif /* SCT4 */
   }
      /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   /* process the received ICMP6 message */
   else if (hdrParm->type == CM_HDRPARM_ICMP6)
   {
      if(sbGlobalCb.genCfg.performMtu == TRUE)
      {
         if (srcAddr->type == CM_TPTADDR_IPV4)
         {
            ver = 4;
         }
         else if (srcAddr->type == CM_TPTADDR_IPV6)
         {
            ver = 6;
         }
         else
         {
            ver = 0;
            SBLOGERROR( ERRCLS_INT_PAR, ESB085, (ErrVal) srcAddr->type,
                  "SbLiHitUDatInd: Incorrect address type" );

            RETVALUE( RFAILED );
         }

         if(NULLP == mBuf)
         {
            SBLOGERROR( ERRCLS_INT_PAR, ESB084, (ErrVal) srcAddr->type,
                        "mBuf is NULL" );
            RETVALUE( RFAILED );
         }
         err = sbMtuRcvIcmp(&(sbGlobalCb.mtuCp), mBuf, ver);
         SB_CHK_PUTMSG( mBuf );
         RETVALUE( err );

      }
   }
#endif

   if (sbGlobalCb.sbInit.trc == TRUE)
   {
      /* sb052.102 Provide ethereal like logs */
      sbTrcBuf(suId, LSB_MSG_RECVD, mBuf, srcAddr, dstAddr);
   }

   /* sanity checks */
#if ( ERRCLASS & ERRCLS_INT_PAR )

   if( (suId >= (SuId) sbGlobalCb.genCfg.maxNmbTSaps) || (suId < 0) )
   {
      SBLOGERROR( ERRCLS_INT_PAR, ESB086, (ErrVal) suId,
            "SbLiHitUDatInd: suId out of range" );
      /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
      SB_LM_GEN_ALARM( (U16)LCM_CATEGORY_INTERFACE, \
            (U16)LCM_EVENT_LI_INV_EVT, \
            (U16)LCM_CAUSE_INV_SUID, \
            suId, \
            LSB_SW_RFC_REL0 );
      RETVALUE( RFAILED );
   }
#endif /* ERRCLS_INT_PAR */

   /* get the SCT SAP control block */
   tSap = *(sbGlobalCb.tSaps + suId);

   /* check to see if the SAP exists *
    * sb080.102: removing the NULL check for TSAP out of ERRCLASS */
   if ( tSap == (SbTSapCb *)NULLP )
   {
#if ( ERRCLASS & ERRCLS_INT_PAR )

      SBLOGERROR( ERRCLS_INT_PAR, ESB087, (ErrVal) suId,
            "SbLiHitUDatInd: Sap not configured" );
#endif /* ERRCLS_INT_PAR */
      /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */  
      SB_LM_GEN_ALARM( (U16)LCM_CATEGORY_INTERFACE, \
            (U16)LCM_EVENT_LI_INV_EVT, \
            (U16)LCM_CAUSE_INV_SAP, \
            suId, \
            LSB_SW_RFC_REL0 );
      RETVALUE( RFAILED );
   }

#if ( ERRCLASS & ERRCLS_INT_PAR )
   /* Check if the message buffer is of an acceptable length */
   if ( mBuf == (Buffer *)NULLP )
   {
      SBLOGERROR( ERRCLS_INT_PAR, ESB088, (ErrVal) 0,
            "SbLiHitUDatInd: NULL message" );
      /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */     
      SB_LM_GEN_ALARM( (U16)LCM_CATEGORY_INTERFACE, \
            (U16)LCM_EVENT_LI_INV_EVT, \
            (U16)LCM_CAUSE_INV_PAR_VAL, \
            suId, \
            LSB_SW_RFC_REL0 );
      RETVALUE( RFAILED );
   }
   else
   {
      /* sb051.102: Checking the error for SSI function call */
      err = SFndLenMsg(mBuf, &len);
      if (err != ROK)
      {
         SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
                  "SbLiHitUDatInd: Find length message failed\n"));
         SB_CHK_PUTMSG( mBuf );
         RETVALUE( RFAILED );
      }
      /* Sb035.103: Fixed the warnings when LONG_MSG is enabled.*/
#ifdef LONG_MSG
      SBDBGP(DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
               "SbLiHitUDatInd: Message length is %ld bytes)\n", len));
#else
      SBDBGP(DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
               "SbLiHitUDatInd: Message length is %d bytes)\n", len));
#endif
      if ( len < 4 )
      {
/* Sb035.103: Fixed the warnings when LONG_MSG is enabled.*/
#ifdef LONG_MSG
         SBDBGP(DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
                  "SbLiHitUDatInd: Message too short: (%ld) bytes)\n", len ));
#else
         SBDBGP(DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
                  "SbLiHitUDatInd: Message too short: (%d) bytes)\n", len ));
#endif
         SB_CHK_PUTMSG( mBuf );
         RETVALUE( ROK );
      }
   }

   if ( srcAddr == (CmTptAddr *)NULLP )
   {
      SBLOGERROR( ERRCLS_INT_PAR, ESB089, (ErrVal) 0,
                  "SbLiHitUDatInd: Source address NULL" );
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */     
      SB_LM_GEN_ALARM( (U16)LCM_CATEGORY_INTERFACE, \
                    (U16)LCM_EVENT_LI_INV_EVT, \
                    (U16)LCM_CAUSE_INV_PAR_VAL, \
                    suId, \
                    LSB_SW_RFC_REL0 );

      SB_CHK_PUTMSG( mBuf );
      RETVALUE( RFAILED );
   }

   if ( dstAddr == (CmTptAddr *)NULLP)
   {
      SBLOGERROR( ERRCLS_INT_PAR, ESB090, (ErrVal) 0,
                  "SbLiHitUDatInd: Destination address NULL" );
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */     
      SB_LM_GEN_ALARM( (U16)LCM_CATEGORY_INTERFACE, \
                    (U16)LCM_EVENT_LI_INV_EVT, \
                    (U16)LCM_CAUSE_INV_PAR_VAL, \
                    suId, \
                    LSB_SW_RFC_REL0 );

      SB_CHK_PUTMSG( mBuf );
      RETVALUE( RFAILED );
   }
#endif /* ERRCLS_INT_PAR */

   /* Zero and convert the source address to a network address */
   SB_ZERO( &srcNetAddr, sizeof(CmNetAddr) );

   if ( srcAddr->type == CM_TPTADDR_IPV4 )
   {
      srcNetAddr.u.ipv4NetAddr = srcAddr->u.ipv4TptAddr.address;
      srcNetAddr.type = CM_NETADDR_IPV4;
   }
   else if ( srcAddr->type == CM_TPTADDR_IPV6 )
   {
      srcNetAddr.type = CM_NETADDR_IPV6;
      (Void) cmMemcpy( (U8 *) &(srcNetAddr.u.ipv6NetAddr),
                       (U8 *)&(srcAddr->u.ipv6TptAddr.ipv6NetAddr),
                       (PTR) CM_IPV6ADDR_SIZE );
   }

#if ( ERRCLASS & ERRCLS_INT_PAR )
   else
   {
      SBLOGERROR( ERRCLS_INT_PAR, ESB091, (ErrVal) srcAddr->type,
                  "SbLiHitUDatInd: invalid source address type" );
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */     
      SB_LM_GEN_ALARM( (U16)LCM_CATEGORY_INTERFACE, \
                    (U16)LCM_EVENT_LI_INV_EVT, \
                    (U16)LCM_CAUSE_INV_PAR_VAL, \
                    suId, \
                    LSB_SW_RFC_REL0 );

      SB_CHK_PUTMSG( mBuf );
      RETVALUE( RFAILED );
   }
#endif /* ERRCLS_INT_PAR */


   if ((tSap->tSapCfg.reConfig.sbDnsCfg.useDnsLib == TRUE) &&  
         (suId == sbGlobalCb.dnsInfo.suId) && 
         (suConId == sbGlobalCb.dnsInfo.suConId))
   {
      SBDBGP( DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
              "sbLiHitUDatInd: Dns Response Received From Server" ));

      cmDnsPrcDnsRsp(sbGlobalCb.dnsInfo.dnsCb, srcAddr, mBuf);

      /* Free Message Buffer */
      if (mBuf != NULLP)
          SPutMsg(mBuf);

      RETVALUE(ROK);
   }

   /* Zero and convert the destination address to a network address */
   SB_ZERO( &dstNetAddr, sizeof(CmNetAddr) );
   
   /* sb008.12 - The change done for UDP, if service type is UDP then search
    * the  correct localAddrCb and copy the own Address from that block in the
    * destination address */
   if( sbGlobalCb.genCfg.serviceType  == HI_SRVC_UDP) 
   {
      S16 i;
      SbLocalAddrCb *localConn;
/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
      for (i = 0; i < (sbGlobalCb.genCfg.maxNmbEndp * SCT_MAX_NET_ADDRS); i++)
#else
      for (i = 0; i < sbGlobalCb.genCfg.maxNmbSrcAddr; i++)
#endif
      {
         localConn = *(sbGlobalCb.localAddrCb + i);
         if( (localConn != (SbLocalAddrCb *)NULLP ) &&
             ( localConn->connected == TRUE)  &&
             ( localConn->suId == suId ) && 
             ( localConn->suConId ==  suConId ) ) 
         {
            if(localConn->ownAddr.type == CM_NETADDR_IPV4)
            {
              dstAddr->type = CM_TPTADDR_IPV4;
              dstAddr->u.ipv4TptAddr.address = localConn->ownAddr.u.ipv4NetAddr;

/* sb065.102: compile time flag to make udp port as configurable parameter */
#ifdef LSB5
              dstAddr->u.ipv4TptAddr.port =  sbGlobalCb.genCfg.dstUdpPort;
#else
              dstAddr->u.ipv4TptAddr.port =  SB_UDP_PORT;
#endif /* LSB5 */
            }
            else
            {
              S16 j;
              dstAddr->type = CM_NETADDR_IPV6;
/* sb065.102: compile time flag to make udp port as configurable parameter */
#ifdef LSB5
              dstAddr->u.ipv4TptAddr.port =  sbGlobalCb.genCfg.dstUdpPort;
#else
              dstAddr->u.ipv6TptAddr.port =  SB_UDP_PORT;
#endif /* LSB5 */
              for (j = 0; j < CM_IPV6ADDR_SIZE; j++)                    
              {                                                          
                dstAddr->u.ipv6TptAddr.ipv6NetAddr[j] = 
                   localConn->ownAddr.u.ipv6NetAddr[j];
              }                                                        
            }
            break;
         }
      }
   }

   if ( dstAddr->type == CM_TPTADDR_IPV4 )
   {
      dstNetAddr.u.ipv4NetAddr = dstAddr->u.ipv4TptAddr.address;
      dstNetAddr.type = CM_NETADDR_IPV4;
   }
   else if ( dstAddr->type == CM_TPTADDR_IPV6 )
   {
      dstNetAddr.type = CM_NETADDR_IPV6;
      (Void) cmMemcpy( (U8 *) &(dstNetAddr.u.ipv6NetAddr),
                       (U8 *)&(dstAddr->u.ipv6TptAddr.ipv6NetAddr),
                       (PTR) CM_IPV6ADDR_SIZE );
   }

#if ( ERRCLASS & ERRCLS_INT_PAR )
   else
   {
      SBLOGERROR( ERRCLS_INT_PAR, ESB092, (ErrVal) dstAddr->type,
                  "SbLiHitUDatInd: invalid destination address type" );
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */     
      SB_LM_GEN_ALARM( (U16)LCM_CATEGORY_INTERFACE, \
                    (U16)LCM_EVENT_LI_INV_EVT, \
                    (U16)LCM_CAUSE_INV_PAR_VAL, \
                    suId, \
                    LSB_SW_RFC_REL0 );

      SB_CHK_PUTMSG( mBuf );
      RETVALUE( RFAILED );
   }
#endif /* ERRCLS_INT_PAR */

  /* sb060.102 - TOS enhancement. */
#ifdef SCT4
   err = sbVaDatInd( &srcNetAddr, &dstNetAddr, suConId, mBuf, incomingTos );
#else
   err = sbVaDatInd( &srcNetAddr, &dstNetAddr, suConId, mBuf );
#endif /* SCT4 */
   if ( err != ROK )
   {
      SBDBGP( DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
              "sbLiHitUDatInd: message validation failed\n" ));
   }

   SBDBGP( DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
           "sbLiHitUDatInd: RETVALUE( ROK )\n" ));
   /* mBuf is released on error above and sbVaDatInd releases it on success */
   RETVALUE( ROK );
}


/*
*
*       Fun:   SbLiHitDiscInd
*
*       Desc:  This function is received when the service provider can
*              no longer provide the requested service on the specified
*              connection.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes:
*
*       File:  sb_bdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 SbLiHitDiscInd
(
Pst     *pst,    /* Post structure containing INFO on the src and dst */
SuId    suId,    /* ID of the TSAP in SCTP layer*/
U8      choice,  /* Selction of either a SU or a SP ConId */
UConnId conId,   /* Connection ID used by SCTP */
Reason  reason   /* Reason for the diconnection */
)
#else
PUBLIC S16 SbLiHitDiscInd(pst, suId, choice, conId, reason)
Pst     *pst;    /* Post structure containing INFO on the src and dst */
SuId    suId;    /* ID of the TSAP in SCTP layer*/
U8      choice;  /* Selction of either a SU or a SP ConId */
UConnId conId;   /* Connection ID used by SCTP */
Reason  reason;  /* Reason for the diconnection */
#endif
{
   SbTSapCb *tSap;
   SbLocalAddrCb *localAddrCb;
   SbSctAssocCb *assocCb;
   SctRtrvInfo rtrvInfo;
   SbSctSapCb *sctSap;
   
   /* sb077.102 - Removing unused variables */
   U16 i;
   /* Patch sb028.102: changes required for freeze timer */
   UConnId tempSuAssocId;
   /* Patch sb044.102: Retry Attempt */
   S16 ret=ROK; 
/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   SbAddrPortCb      *addrPortCb = NULLP;
   SbAddrPortEntry   addrPortEntry;
#endif

   TRC3( SbLiHitDiscInd );

#ifdef SS_MULTIPLE_PROCS

   if(SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                         (void **)&sbGlobalCbPtr) != ROK)
   {
     SBLOGERROR(ERRCLS_DEBUG, ESB093, 0,
               "SbLiHitDiscInd () failed, cannot derive sbGlobalCbPtr");
     RETVALUE(FALSE);
   }

   SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
         "-------SCTP------(proc(%d), ent(%d), inst(%d))--------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));

#endif /* SS_MULTIPLE_PROCS */

/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP( DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
         "SbLiHitDiscInd(pst, suId(%d), choice(%d), conId(%d), reason(%d))\n",
         suId, choice, conId, reason ) );
#else
   SBDBGP( DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
         "SbLiHitDiscInd(pst, suId(%d), choice(%d), conId(%ld), reason(%d))\n",
         suId, choice, conId, reason ) );
#endif /* BIT_64 */

#ifndef SS_MULTIPLE_PROCS
   UNUSED( pst );
#endif  /* SS_MULTIPLE_PROCS */

#ifndef DEBUGP

   UNUSED( reason );

#endif

   /* sanity checks */
#if ( ERRCLASS & ERRCLS_INT_PAR )
   if( (suId >= (SuId) sbGlobalCb.genCfg.maxNmbTSaps) || (suId < 0) )
   {
      SBLOGERROR( ERRCLS_INT_PAR, ESB094, (ErrVal) suId,
                  "SbLiHitDiscInd: suId out of range" );
                    /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */     
                   SB_LM_GEN_ALARM( (U16)LCM_CATEGORY_INTERFACE, \
                    (U16)LCM_EVENT_LI_INV_EVT,\
                    (U16)LCM_CAUSE_INV_SUID, \
                    suId, \
                    LSB_SW_RFC_REL0 );
     RETVALUE( RFAILED );
   }
#endif /* ERRCLS_INT_PAR */

   /* get the SCT SAP control block */
   tSap = *(sbGlobalCb.tSaps + suId);

   /* check to see if the SAP exists */
#if ( ERRCLASS & ERRCLS_INT_PAR )
   if ( tSap == (SbTSapCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_INT_PAR, ESB095, (ErrVal) suId,
                  "SbLiHitDiscInd: Sap not configured" );
                /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
                   SB_LM_GEN_ALARM( (U16)LCM_CATEGORY_INTERFACE, \
                    (U16)LCM_EVENT_LI_INV_EVT, \
                    (U16)LCM_CAUSE_INV_SAP, \
                    suId, \
                    LSB_SW_RFC_REL0 );
      RETVALUE( RFAILED );
   }
#endif /* ERRCLS_INT_PAR */

   localAddrCb = (SbLocalAddrCb *)NULLP;

   if ( choice == HI_USER_CON_ID )
   {
/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
      if (conId < (sbGlobalCb.genCfg.maxNmbEndp * SCT_MAX_NET_ADDRS))
#else
      if (conId < sbGlobalCb.genCfg.maxNmbSrcAddr)
#endif
      {
         localAddrCb = *(sbGlobalCb.localAddrCb + conId);
      }
      else
      {
/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
         localAddrCb = *( sbGlobalCb.localAddrCb +
                          (conId - (sbGlobalCb.genCfg.maxNmbEndp * SCT_MAX_NET_ADDRS)) );
#else
         localAddrCb = *( sbGlobalCb.localAddrCb +
                          (conId - sbGlobalCb.genCfg.maxNmbSrcAddr) );
#endif
      }

   }
   else if ( choice == HI_PROVIDER_CON_ID )
   {
/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
      for ( i = 0; i < (sbGlobalCb.genCfg.maxNmbEndp * SCT_MAX_NET_ADDRS); i++ )
#else
      for ( i = 0; i < sbGlobalCb.genCfg.maxNmbSrcAddr; i++ )
#endif
      {
         localAddrCb = *(sbGlobalCb.localAddrCb + i);

         if ( localAddrCb != (SbLocalAddrCb *)NULLP )
         {
            if ( (localAddrCb->spConId == conId) ||
                 (localAddrCb->spOtherConId == conId) )
            {
/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
               i = (sbGlobalCb.genCfg.maxNmbEndp * SCT_MAX_NET_ADDRS);
#else
               i = sbGlobalCb.genCfg.maxNmbSrcAddr;
#endif
            }
            else
            {
               localAddrCb = (SbLocalAddrCb *)NULLP;
            }
         }
      }
   }

   if ( localAddrCb != (SbLocalAddrCb *)NULLP )
   {
    /* sb070.102 - Local interface failure */
      if( localAddrCb->conRetryAttempt == 0)
      {
/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
          if (conId < (sbGlobalCb.genCfg.maxNmbEndp * SCT_MAX_NET_ADDRS))
#else
          if (conId < sbGlobalCb.genCfg.maxNmbSrcAddr)
#endif
         {
             /* sb046.102: Multiple IP address per Endp */
             localAddrCb->connected = FALSE;

             /* remove all associations (we assume they abort properly) */
             for ( i = 0; i < sbGlobalCb.genCfg.maxNmbAssoc; i++ )
             {
                 assocCb = sbGlobalCb.assocCb[i];

                 if ( assocCb != (SbSctAssocCb *) NULLP )
                 {
                    if ( assocCb->localConn == localAddrCb )
                    {
                       /* try to find another local address control block in the
                       * same endpCb */
                       SB_GET_LOCAL_CONN(assocCb->endpId, assocCb->localConn, ret);
                       if ( ret != ROK )
                       {
                          sctSap = *(sbGlobalCb.sctSaps + assocCb->spId);
                          if ( sctSap != (SbSctSapCb *)NULLP)
           {
                             rtrvInfo.lastAckTsn = assocCb->sbAcCb.cumTsn;
                             rtrvInfo.lastSentTsn = assocCb->sbAcCb.nextLocalTsn - 1;
                             rtrvInfo.nmbUnsentDgms = sbDbQPackets(assocCb,SB_DB_TSNWAITINGQ);
                             rtrvInfo.nmbUnackDgms = sbDbQPackets(assocCb,SB_DB_CONGESTIONQ);
                             rtrvInfo.nmbUndelDgms = sbDbQPackets(assocCb,SB_DB_SEQUENCEDQ)
                                                     + sbDbQPackets(assocCb,SB_DB_ASSEMBLYQ);
                             /* start freeze timer */
                             if ( assocCb->sbAsCb.timer.tmrEvnt != TMR_NONE )
                             {
                                SB_STOP_TMR(&(assocCb->sbAsCb.timer));
                             }
                             /* sb028: changes for freeze timer, allow timer to be zero */
                             if ( sctSap->sctSapCfg.reConfig.freezeTm > 0)
                             {
                                SB_START_TMR(&(assocCb->sbAsCb.timer), assocCb,
                                      SB_TMR_FREEZE,sctSap->sctSapCfg.reConfig.freezeTm);
                             }
                     
                             assocCb->assocState = SB_ST_CLOSED;
                     
                             tempSuAssocId = assocCb -> suAssocId;
                             if (sctSap -> sctSapCfg.reConfig.freezeTm == 0 )
                             {
                                (Void) sbAsAbortAssoc (assocCb, FALSE);
                                sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
                                SB_FREE(sizeof(SbSctAssocCb), assocCb);
                             }

                             /* sb045.102: New Cause added */
                             /* sb046.102: notify user the rtrvInfo */
                             SbUiSctTermInd(&(sctSap->sctPst), sctSap->suId,
                                           tempSuAssocId, SCT_ASSOCID_SU,
                                           SCT_STATUS_COMM_LOST, SCT_CAUSE_SOCK_ERR,
                                                       &rtrvInfo);
                          }
                       }
             /* sb075.102 - Following logic to change the sorce is not required*/
                    }
                 } 
             }
         }
         else
         {
            localAddrCb->otherConnected = FALSE;
         }
      }

      /* sb044.102: Try to reconnect once disconnect indication is received */
      if (localAddrCb->connected == FALSE)
      {
         if (localAddrCb->conRetryAttempt < MAX_CON_RETRY_ATTMPT)
         {
            if ((ret = sbLiOpenServer(tSap, localAddrCb)) != ROK)
            {
                 SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
                      "SbLiHitBndCfm: could not open server\n"));
                 RETVALUE(ret);
            }
         }
         else
         {
             /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
            SB_LM_GEN_ALARM(LCM_CATEGORY_INTERFACE, LSB_EVENT_TUCLCONNECT_FAIL, \
                   LSB_CAUSE_EXCEED_CONF_VAL, tSap->tSapCfg.suId, LSB_SW_RFC_REL0);
        /* sb019.103: Do Not make localAddrCb NULL and also Do Not remove it from
         * Hash List After DiscInd is Received */
        /*  (sbGlobalCb.localAddrCb + localAddrCb->suId) = (SbLocalAddrCb *)NULLP;*/
        /* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT

            SB_ZERO(&addrPortEntry, sizeof(SbAddrPortEntry));
            addrPortEntry.port = localAddrCb->port;
            SB_CPY_NADDR(&(addrPortEntry.localAddr), &(localAddrCb->ownAddr));

            ret = cmHashListFind(&(sbGlobalCb.addrPortHl),
                                 (U8 *) &(addrPortEntry),
                                 (U16) sizeof(SbAddrPortEntry), 0,
                                 (PTR *) &addrPortCb);
            if (ret != ROK)
            {
               SBLOGERROR(ERRCLS_INT_PAR, ESB034, (ErrVal)0,
                     "SbLiHitDiscInd(): failed to find addrPortCb\n" );
            }
            else
               addrPortCb->localAddrCb = NULLP;

            SB_FREE( sizeof(SbLocalAddrCb), localAddrCb );
#endif

/* sb009.103 : SOL10 changes */
#ifndef SB_SOL10_MULTIPORT
    /* sb019.103: Do Not remove it from Hash List After DiscInd is Received */   
    /*  (Void) cmHashListDelete(&(sbGlobalCb.localAddrHl), (PTR)localAddrCb);*/
#endif
         }
      }
   }

#if ( ERRCLASS & ERRCLS_DEBUG )
   else
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB096, (ErrVal) conId,
                  "SbLiHitDiscInd: Invalid conId" );
                /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
                   SB_LM_GEN_ALARM( (U16)LCM_CATEGORY_INTERFACE, \
                    (U16)LCM_EVENT_LI_INV_EVT, \
                    (U16)LCM_CAUSE_INV_PAR_VAL, \
                    (SuId)suId, \
                    LSB_SW_RFC_REL0 );
      RETVALUE( RFAILED );
   }
#endif /* ERRCLS_DEBUG */

   RETVALUE( ROK );
}


/*
*
*       Fun:   SbLiHitDiscCfm
*
*       Desc:  This function is received in responce to a Disconnect
*              request when the Sap is being removed.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes:
*
*       File:  sb_bdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 SbLiHitDiscCfm
(
Pst     *pst,    /* Post structure containing INFO on the src and dst */
SuId    suId,    /* ID of the TSAP in SCTP layer*/
U8      choice,  /* Selction of either a SU or a SP ConId */
UConnId conId,   /* Connection ID used by SCTP */
Action  action   /* Reason for the diconnection */
)
#else
PUBLIC S16 SbLiHitDiscCfm(pst, suId, choice, conId, action)
Pst     *pst;    /* Post structure containing INFO on the src and dst */
SuId    suId;    /* ID of the TSAP in SCTP layer*/
U8      choice;  /* Selction of either a SU or a SP ConId */
UConnId conId;   /* Connection ID used by SCTP */
Action  action;  /* Reason for the diconnection */
#endif
{
   SbTSapCb *tSap;
   SbLocalAddrCb *localAddrCb;
   SbSctAssocCb *assocCb;
   SctRtrvInfo rtrvInfo;
   SbSctSapCb *sctSap;
   U16 i;
   /* Patch sb028: allow freeze timer to be zero */
   UConnId tempSuAssocId;
   /* sb046.102: Multiple IP address per Endp */
   S16               ret=ROK;
/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   SbAddrPortCb      *addrPortCb = NULLP;
   SbAddrPortEntry   addrPortEntry;
#endif

   TRC3( SbLiHitDiscCfm );

#ifdef SS_MULTIPLE_PROCS

   if(SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                         (void **)&sbGlobalCbPtr) != ROK)
   {
     SBLOGERROR(ERRCLS_DEBUG, ESB097, 0,
               "SbLiHitDiscCfm () failed, cannot derive sbGlobalCbPtr");
     RETVALUE(FALSE);
   }

   SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
         "-------SCTP------(proc(%d), ent(%d), inst(%d))--------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));

#endif /* SS_MULTIPLE_PROCS */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP( DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
         "SbLiHitDiscCfm(pst, suId(%d), choice(%d), conId(%d), action(%d))\n",
         suId, choice, conId, action ) );
#else
   SBDBGP( DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
         "SbLiHitDiscCfm(pst, suId(%d), choice(%d), conId(%ld), action(%d))\n",
         suId, choice, conId, action ) );
#endif /* BIT_64 */

#ifndef SS_MULTIPLE_PROCS
   UNUSED( pst );
#endif  /* SS_MULTIPLE_PROCS */

#ifndef DEBUGP

   UNUSED( action );

#endif

   /* sb022.102: Fix for layer shutdown */
   if (sbGlobalCb.sbInit.cfgDone == FALSE)
   {
      SBDBGP( DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf, 
              "sbLiHitDiscCfm: General configuration not done\n"));
      RETVALUE( RFAILED );
   }

#if ( ERRCLASS & ERRCLS_INT_PAR )

   if( (suId >= (SuId) sbGlobalCb.genCfg.maxNmbTSaps) || (suId < 0) )
   {
       SBLOGERROR( ERRCLS_INT_PAR,
                  ESB098,
                  (ErrVal) suId,
                  "SbLiHitDiscCfm(): suId out of range" );
        /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
       SB_LM_GEN_ALARM( (U16)LCM_CATEGORY_INTERFACE, \
                    (U16)LCM_EVENT_LI_INV_EVT, \
                    (U16)LCM_CAUSE_INV_SUID, \
                    suId, \
                    LSB_SW_RFC_REL0 );

       RETVALUE( RFAILED );
   }

#endif /* ERRCLS_INT_PAR */

   /* get the SCT SAP control block */
   tSap = *(sbGlobalCb.tSaps + suId);

   /* check to see if the SAP exists */
#if ( ERRCLASS & ERRCLS_INT_PAR )

   if ( tSap == (SbTSapCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_INT_PAR,
                  ESB099,
                  (ErrVal) suId,
                  "SbLiHitDiscCfm(): Sap not configured" );
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
      SB_LM_GEN_ALARM( (U16)LCM_CATEGORY_INTERFACE, \
                    (U16)LCM_EVENT_LI_INV_EVT, \
                    (U16)LCM_CAUSE_INV_SAP, \
                    suId, \
                    LSB_SW_RFC_REL0 );

      RETVALUE( RFAILED );
   }

#endif /* ERRCLS_INT_PAR */

   localAddrCb = (SbLocalAddrCb *)NULLP;

   if ( choice == HI_USER_CON_ID )
   {
/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
      if (conId < (sbGlobalCb.genCfg.maxNmbEndp * SCT_MAX_NET_ADDRS))
#else
      if (conId < sbGlobalCb.genCfg.maxNmbSrcAddr)
#endif
      {
         localAddrCb = *(sbGlobalCb.localAddrCb + conId);
      }
      else
      {
/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
         localAddrCb = *( sbGlobalCb.localAddrCb +
                          (conId - (sbGlobalCb.genCfg.maxNmbEndp * SCT_MAX_NET_ADDRS)) );
#else
      /* sb034.103: Fixed logical error in calculating the DNS control block.*/
         localAddrCb = *( sbGlobalCb.localAddrCb +
                          ((conId / 2) - sbGlobalCb.genCfg.maxNmbSrcAddr) );
#endif
      }
   }
   else if ( choice == HI_PROVIDER_CON_ID )
   {
/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
      for ( i = 0; i < (sbGlobalCb.genCfg.maxNmbEndp * SCT_MAX_NET_ADDRS); i++ )
#else
      for ( i = 0; i < sbGlobalCb.genCfg.maxNmbSrcAddr; i++ )
#endif
      {
         localAddrCb = *(sbGlobalCb.localAddrCb + i);

         if ( localAddrCb != (SbLocalAddrCb *)NULLP )
         {
            if ( (localAddrCb->spConId == conId) ||
                 (localAddrCb->spOtherConId == conId) )
            {
/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
               i = (sbGlobalCb.genCfg.maxNmbEndp * SCT_MAX_NET_ADDRS);
#else
               i = sbGlobalCb.genCfg.maxNmbSrcAddr;
#endif
            }
            else
            {
               localAddrCb = (SbLocalAddrCb *)NULLP;
            }
         }
      }
   }

   if ( localAddrCb != (SbLocalAddrCb *)NULLP )
   {
/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
      if (conId < (sbGlobalCb.genCfg.maxNmbEndp * SCT_MAX_NET_ADDRS))
#else
      if (conId < sbGlobalCb.genCfg.maxNmbSrcAddr)
#endif
      {
         /* sb046.102: Multiple IP address per Endp */
         localAddrCb->connected = FALSE;

         /* remove all associations (we assume they abort properly) */
         for ( i = 0; i < sbGlobalCb.genCfg.maxNmbAssoc; i++ )
         {
            assocCb = sbGlobalCb.assocCb[i];

            if ( assocCb != (SbSctAssocCb *) NULLP )
            {
               if ( assocCb->localConn == localAddrCb )
               {
                  /* try to find another local address control block in the
                   * same endpCb */
                  SB_GET_LOCAL_CONN(assocCb->endpId, assocCb->localConn, ret);
                  if ( ret != ROK )
                  {
                     sctSap = *(sbGlobalCb.sctSaps + assocCb->spId);
                     if ( sctSap != (SbSctSapCb *)NULLP)
                     {
                        rtrvInfo.lastAckTsn = assocCb->sbAcCb.cumTsn;
                        rtrvInfo.lastSentTsn = assocCb->sbAcCb.nextLocalTsn - 1;
                        rtrvInfo.nmbUnsentDgms = sbDbQPackets(assocCb,
                                                              SB_DB_TSNWAITINGQ);
                        rtrvInfo.nmbUnackDgms = sbDbQPackets(assocCb,
                                                             SB_DB_CONGESTIONQ);
                        rtrvInfo.nmbUndelDgms = sbDbQPackets(assocCb,
                                                             SB_DB_SEQUENCEDQ) +
                                                             sbDbQPackets(assocCb,
                                                             SB_DB_ASSEMBLYQ);
                     
                        /* start freeze timer */
                        if ( assocCb->sbAsCb.timer.tmrEvnt != TMR_NONE )
                        {
                           SB_STOP_TMR(&(assocCb->sbAsCb.timer));
                        }
                        /* sb028.102 : allow freeze timer to be zero */
                        if (sctSap -> sctSapCfg.reConfig.freezeTm > 0)
                        {
                           SB_START_TMR(&(assocCb->sbAsCb.timer), assocCb,
                                     SB_TMR_FREEZE,
                                     sctSap->sctSapCfg.reConfig.freezeTm);
                        }
                     
                        assocCb->assocState = SB_ST_CLOSED;
                     
                        tempSuAssocId = assocCb->suAssocId;
                     
                        /* sb036.102: Remove assocCb in case of freezeTm ZERO */
                        if (sctSap -> sctSapCfg.reConfig.freezeTm == 0 )
                        {
                           (Void) sbAsAbortAssoc (assocCb, FALSE);
                           sbGlobalCb.assocCb[i] = (SbSctAssocCb *) NULLP;
                           SB_FREE(sizeof(SbSctAssocCb), assocCb);
                        }

                        /* sb046.102: notify user the rtrvInfo */
                        SbUiSctTermInd(&(sctSap->sctPst), sctSap->suId,
                                    tempSuAssocId, SCT_ASSOCID_SU,
                                    SCT_STATUS_COMM_LOST, SCT_CAUSE_NOT_APPL,
                                    &rtrvInfo);
                     }
                  }
               }
            }
         }
      }
      else
      {
         localAddrCb->otherConnected = FALSE;
      }

      if ( (localAddrCb->connected == FALSE) &&
           (localAddrCb->otherConnected == FALSE) )
      {
  /* sb012.103: Making LocalAddrCb to NULL is shifted down */
/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT

         SB_ZERO(&addrPortEntry, sizeof(SbAddrPortEntry));
         addrPortEntry.port = localAddrCb->port;
         SB_CPY_NADDR(&(addrPortEntry.localAddr), &(localAddrCb->ownAddr));

         ret = cmHashListFind(&(sbGlobalCb.addrPortHl),
                              (U8 *) &(addrPortEntry),
                              (U16) sizeof(SbAddrPortEntry), 0,
                              (PTR *) &addrPortCb);
         if (ret != ROK)
         {
            SBLOGERROR(ERRCLS_INT_PAR, ESB034, (ErrVal)0,
                  "SbLiHitDiscCfm(): failed to find addrPortCb\n" );
         }
         else
            addrPortCb->localAddrCb = NULLP;
         /* sb030.103: Make the localAddrCb in globallist as NULL. */
         sbGlobalCb.localAddrCb[localAddrCb->suConId] = (SbLocalAddrCb *)NULLP;
         SB_FREE( sizeof(SbLocalAddrCb), localAddrCb );
#endif

/* sb009.103 : SOL10 changes */
#ifndef SB_SOL10_MULTIPORT
  /* sb012.103: Making LocalAddrCb to NULL is shifted here from above */
         /* sb030.103: Corrected the index from suId to suConId. */
         sbGlobalCb.localAddrCb[localAddrCb->suConId] = (SbLocalAddrCb *)NULLP;
         (Void) cmHashListDelete(&(sbGlobalCb.localAddrHl), (PTR)localAddrCb);
  /* sb012.103: Freeing the localAddrCb */
         SB_FREE( sizeof(SbLocalAddrCb), localAddrCb);
#endif
      }

   }

#if ( ERRCLASS & ERRCLS_DEBUG )
   else
   {
      SBDBGP( DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
                            "SbLiHitDiscCfm: Connection already deleted\n") );
      RETVALUE( ROK );
   }
#endif /* ERRCLS_DEBUG */

   RETVALUE( ROK );
}


/*
*
*       Fun:   SbLiHitBndCfm
*
*       Desc:  This function is received from the layer below in
*              response to a Bind request. This function must inform
*              the layer manager that the bind has succeeded or failed.
*              A server open request is sent to the TUCL layer for each
*              configured source address. The bind confirm timer is only
*              stopped once all these requests are confirmed.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes:
*
*       File:  sb_bdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 SbLiHitBndCfm
(
Pst            *pst,     /* Post structure */
SuId            suId,    /* Service user SAP ID */
U8              status   /* Status of the Bind requested */
)
#else
PUBLIC S16 SbLiHitBndCfm(pst, suId, status)
Pst            *pst;     /* Post structure */
SuId            suId;    /* Service user SAP ID */
U8              status;  /* Status of the Bind requested */
#endif
{
   SbTSapCb         *tSap;
/* sb009.103 : SOL10 changes */
#ifndef SB_SOL10_MULTIPORT
   SbLocalAddrCb    *localAddrCb;
   U16               i;
   U16               j=0;  /* sb001.12 : modification - warning removed */
#endif
   S16               ret;
   TRC3(SbLiHitBndCfm)

#ifdef SS_MULTIPLE_PROCS

   if(SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                         (void **)&sbGlobalCbPtr) != ROK)
   {
     SBLOGERROR(ERRCLS_DEBUG, ESB100, 0,
               "SbLiHitBndCfm () failed, cannot derive sbGlobalCbPtr");
     RETVALUE(FALSE);
   }

   SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
         "-------SCTP------(proc(%d), ent(%d), inst(%d))--------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));

#endif /* SS_MULTIPLE_PROCS */

   SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
          "SbLiHitBndCfm(pst, suId(%d), status(%d))\n", suId, status));

#ifndef SS_MULTIPLE_PROCS
   UNUSED(pst);
#endif  /* SS_MULTIPLE_PROCS */

   /* sanity check on suId */
#if (ERRCLASS & ERRCLS_INT_PAR)
   if ( (suId >= (SuId) sbGlobalCb.genCfg.maxNmbTSaps) || (suId < 0) )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB101, (ErrVal) suId,
                 "SbLiHitBndCfm(): suId out of range");
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
      SB_LM_GEN_ALARM((U16)LCM_CATEGORY_INTERFACE, (U16)LCM_EVENT_LI_INV_EVT, \
                   (U16)LCM_CAUSE_INV_SUID, suId, LSB_SW_RFC_REL0);
      RETVALUE(RFAILED);
   }
#endif /* ERRCLS_INT_PAR */

   /* get the transport SAP control block */
   tSap = sbGlobalCb.tSaps[suId];

   /* check to see if the SAP exists */
#if (ERRCLASS & ERRCLS_INT_PAR)
   if (tSap == (SbTSapCb *)NULLP )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB102, (ErrVal) suId,
                 "SbLiHitBndCfm(): Sap not configured");
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */     
      SB_LM_GEN_ALARM((U16)LCM_CATEGORY_INTERFACE, (U16)LCM_EVENT_LI_INV_EVT, \
                   (U16)LCM_CAUSE_INV_SAP, suId, LSB_SW_RFC_REL0);
      RETVALUE(RFAILED);
   }
#endif /* ERRCLS_INT_PAR */

   if ( status == CM_BND_OK )
   {
      /* SAP bound OK */
      /* set the SAP state */
      tSap->sapState = SB_SAPSTATE_BND;

/* sb009.103 : SOL10 changes */
#ifndef SB_SOL10_MULTIPORT
      /* loop through the configured src address list */
      for ( i = 0; i < tSap->tSapCfg.srcNAddrLst.nmb; i++ )
      {
         /* see if src address is already in a localAddrCb */
         /* this is really a sanity check */
         localAddrCb = (SbLocalAddrCb *)NULLP;
         ret = cmHashListFind(&(sbGlobalCb.localAddrHl),
                             (U8 *) &(tSap->tSapCfg.srcNAddrLst.nAddr[i]),
                             sizeof(CmNetAddr), 0, (PTR *) &localAddrCb);

#if (ERRCLASS & ERRCLS_INT_PAR)
         if ( ret == ROK )
         {
            /* src address already put into localAddrCb */
            SBLOGERROR(ERRCLS_INT_PAR, ESB103, (ErrVal)0,
                       "SbLiHitBndCfm(): local address overlap");
            break;
         }
#endif /*(ERRCLASS & ERRCLS_INT_PAR)*/

         /* look for an empty spot for a new localAddrCb */
         for ( j = 0; j < sbGlobalCb.genCfg.maxNmbSrcAddr; j++)
         {
            if ( sbGlobalCb.localAddrCb[j] == (SbLocalAddrCb *) NULLP )
            {
               /* empty spot in list found */
               break;
            }
         }

         if ( j >= sbGlobalCb.genCfg.maxNmbSrcAddr)
         {
            /* Resource Error */
#if (ERRCLASS & ERRCLS_INT_PAR)
            SBLOGERROR(ERRCLS_INT_PAR, ESB104, (ErrVal)0,
                       "SbLiHitBndCfm: config. max reached for localAddrCb");
#endif
         }
         else
         {
            /* create a new localAddrCb */
            SB_ALLOC(sizeof(SbLocalAddrCb), localAddrCb, ret);
            if ( ret != ROK )
            {
               SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
                      "SbLiHitBndCfm: could not alloc mem for localAddrCb\n"));
            }
            else
            {
          /*sb080.102:Adjusting the macro call to single line*/
               SB_CPY_NADDR(&(localAddrCb->ownAddr), &(tSap->tSapCfg.srcNAddrLst.nAddr[i]));
               localAddrCb->suId = suId;
               localAddrCb->connected = FALSE;
               localAddrCb->spConId = 0;
               localAddrCb->suConId = j;
               localAddrCb->spOtherConId = 0;
               localAddrCb->suOtherConId = j + sbGlobalCb.genCfg.maxNmbSrcAddr;
               /* sb044.102: Try to reconnect */
               localAddrCb->conRetryAttempt = 0;

               /* insert into the global hash list */
               ret = cmHashListInsert(&(sbGlobalCb.localAddrHl),
                                      (PTR) localAddrCb,
                                      (U8 *) &(localAddrCb->ownAddr),
                                      sizeof(CmNetAddr));
               if ( ret != ROK )
               {
                  /* couldn't insert localAddrCb into hashlist */
                  SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
                      "SbLiHitBndCfm: could not insert localAddrCb into HL\n"));
                  /* localAddrCb has been allocated so delete it */
                  SB_FREE(sizeof(SbLocalAddrCb), localAddrCb);
                  RETVALUE(RFAILED);
               }

               /* insert into the global array list */
               sbGlobalCb.localAddrCb[localAddrCb->suConId] = localAddrCb;

               if ((ret = sbLiOpenServer(tSap, localAddrCb)) != ROK)
               {
                  SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
                        "SbLiHitBndCfm: could not open server\n"));
                  RETVALUE(ret);
               }
            }
         } /* end else */
      } /* end for */
#endif

     sbGlobalCb.dnsInfo.suId = suId;
     sbGlobalCb.dnsInfo.dnsState = SB_DNS_SERV_CLOSED;
     /* Set the suConId to the next available Running number */
     /* sb044.102: Don not open DNS server if dns is not configured */
     if(tSap->tSapCfg.reConfig.sbDnsCfg.useDnsLib == TRUE)
     {
/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
        sbGlobalCb.dnsInfo.suConId  = 3 * sbGlobalCb.genCfg.maxNmbSrcAddr;
#else
        sbGlobalCb.dnsInfo.suConId  = 2 * (j + sbGlobalCb.genCfg.maxNmbSrcAddr);
#endif
        ret = sbOpenDnsServer(tSap);
        if(ret != ROK)
        {
           SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
              "SbLiHitBndCfm: could not open  DNS Server\n"));
           RETVALUE(ret);
        }
      }
/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
      else
      {
         if ( sbGlobalCb.sbMgmt.hdr.elmId.elmnt == STSBTSAP )
         {
            /* stop bind confirm timer */
            if (tSap->timer.tmrEvnt != TMR_NONE)
            {
               SB_STOP_TMR(&(tSap->timer));
            }

            sbGlobalCb.sbMgmt.cfm.status = LCM_PRIM_OK;
            sbGlobalCb.sbMgmt.cfm.reason = LCM_REASON_NOT_APPL;
            SbMiLsbCntrlCfm(&(sbGlobalCb.sbInit.lmPst), &(sbGlobalCb.sbMgmt));
   
            /* clear this so that other layer manager requests can proceed */
            SB_ZERO(&(sbGlobalCb.sbMgmt), sizeof(SbMgmt));
         }
      }
#endif
   }
   else
   {
      /* SAP did not Bind */
      SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
             "SbLiHitBndCfm: bind was unsuccessful\n"));

/* sb009.103 : SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
      if ( sbGlobalCb.sbMgmt.hdr.elmId.elmnt == STSBTSAP )
#else
      if ( sbGlobalCb.sbMgmt.hdr.elmId.elmnt == STTSAP )
#endif
      {
         /* stop bind confirm timer */
         if (tSap->timer.tmrEvnt != TMR_NONE)
         {
            SB_STOP_TMR(&(tSap->timer));
         }

         sbGlobalCb.sbMgmt.cfm.status = LCM_PRIM_NOK;
         sbGlobalCb.sbMgmt.cfm.reason = LCM_REASON_NEG_CFM;
         SbMiLsbCntrlCfm(&(sbGlobalCb.sbInit.lmPst), &(sbGlobalCb.sbMgmt));

         /* clear this so that other layer manager requests can proceed */
         SB_ZERO(&(sbGlobalCb.sbMgmt), sizeof(SbMgmt));
      }

      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}/* SbLiHitBndCfm() */

/* sb009.103 : SOL10 changes : Added new function sbEndpOpenCleanup  */
#ifdef SB_SOL10_MULTIPORT
/*
*
*       Fun:   sbEndpOpenCleanup
*
*       Desc:  This function is invoked when SCTP fails to process the
*              end point open request and cleaup is required to free the
*              allocated resources. 
*
*       Ret:   ROK
*              RFAILED
*
*       Notes:
*
*       File:  sb_bdy1.c
*
*/

#ifdef ANSI
PRIVATE Void sbEndpOpenCleanup
(
SbSctEndpCb   *endpCb,
U8            nmb
)
#else
PRIVATE Void sbEndpOpenCleanup(endpCb, nmb)
SbSctEndpCb   *endpCb;
U8            nmb;
#endif
{
   U16             i;
   SbAddrPortCb    *tmpAddrPortCb=NULLP;
   SbAddrPortEntry tmpAddrPortEntry;
   CmTptParam      tPar;
   SbLocalAddrCb   *lAddrCb;
   SbTSapCb        *tSapCb;
 /* sb033.103 : Added TRC macro  */
   TRC2(sbEndpOpenCleanup)
   for ( i = 0; i < nmb; i++ )
   {
      cmMemset((U8 *)&tmpAddrPortEntry, 0, sizeof(SbAddrPortEntry));
      tmpAddrPortEntry.port = endpCb->port;

      SB_CPY_NADDR(&(tmpAddrPortEntry.localAddr), &(endpCb->localAddrLst.nAddr[i]));

      cmHashListFind(&(sbGlobalCb.addrPortHl),
	    (U8 *) &(tmpAddrPortEntry),
	    (U16) sizeof(SbAddrPortEntry), 0,
	    (PTR *) &tmpAddrPortCb);

      lAddrCb = tmpAddrPortCb->localAddrCb;

      /* remove the addrPortCb that was inserted in this primitive */
      cmHashListDelete(&(sbGlobalCb.addrPortHl), (PTR)tmpAddrPortCb);
      SB_FREE(sizeof(SbAddrPortCb), tmpAddrPortCb);

      tSapCb = sbGlobalCb.tSaps[lAddrCb->suId];

      SB_ZERO(&tPar, sizeof(CmTptParam));
      tPar.type = CM_TPTPARAM_NOTPRSNT;

      SbLiHitDiscReq( &(tSapCb->tPst),
	    tSapCb->tSapCfg.reConfig.spId,
	    HI_USER_CON_ID, lAddrCb->suConId,
	    HI_CLOSE, &tPar );

      sbGlobalCb.localAddrCb[lAddrCb->suConId] = NULLP;
      SB_FREE(sizeof(SbLocalAddrCb), lAddrCb);
   }

   /* endpoint has been allocated so delete it */
   sbGlobalCb.endpCb[endpCb->spEndpId] = (SbSctEndpCb *) NULLP;
   SB_FREE(sizeof(SbSctEndpCb), endpCb);

   RETVOID;
}
#endif

/********************************************************************30**

         End of file:     sb_bdy1.c@@/main/tenb_5.0_SIB_KNOWNSENSE/2 - Thu Nov 12 17:21:47 2015

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

    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
 /main/2     ---   wvdl,      1. initial release.
 /main/2     ---    sb        1. Modified for SCTP release based on 
                                 RFC-2960 'Oct 2000.
         sb001.12   sb        1. Memory Initialisation problem fix.
         sb002.12   nj        1. Added a defensive check for 0 value.
         sb004.12   sb        1. Memory for Confirm structure allocated 
                                 from heap.
                              2. Return value of sbPmAddAddr is checked.
         sb006.102  rs        1. Updation - modified for alignment in
                                 sbSctEndpEntry
         sb008.12   sb        1. For UDP, In UDatInd primitive copy the
                                 own address for localConnAddrCb. Only 
                                 when this is done SCTP will be able to 
                                 find association. 
                              2. Condition modified in ConCfm for UDP case.
         sb009.102  rs        1. Closing endpoint with SU id
         sb010.102  rs        1. suAssocId in Termination Indication.
         sb015.102  rs        1. DNS Timer is Enabled flag is implemented. 
         sb017.102  rs        1. Endpoint close problem removed. 
                              2. spare1 removed.
         sb018.102  ab        1. dbgMask initialized to 0.
         sb020.102  ab        1. suAssocId should be unique per SAP.
                    rs        2. Association control block freed.
                    rs        3. Destination Network addresslist problem
                                 with maxNmbDestAddr = 1 solved.
                    rs        4. Double SACK problem.
         sb021.102  rs        1. Modification for TOS parameter.
         sb022.101  ab        1. Fix for layer shutdown.
         sb023.102  sb        1. Changes done in Mtu procedure
         sb027.102  hm        1. Removed TAB
         sb028.102  hm        1. Changes to allow freeze timer to be zero
         sb029.102  hm        1. dlvrCfmChunk is set to FALSE, default value
         sb031.102  hm        1. IPV6 Support Added 
         sb036.102  rs        1. Dump the data if assoc is not established
         sb041.102  hl        1. remove the errcls parameter check flag 
         sb042.102  hl        1. Added change for SHT interface and Rolling
                                 Up Grade
         sb044.102  rs        1. Added reconnect once disconnect indication is
                                 received
         sb045.102  rs        1. New Cause value added in disconnect indication.
         sb046.102  hl        1. Multiple IP address per endpoint support
                              2. Alwasy notify retrievel info to user in case
                                 of abort.
         sb048.102  rs        1. New compile time option SB_DEBUGP will
                                 enable the debug prints by default.
                              2. Endpoint hash list problem resolved.
         sb049.102  rs        1. Warnings removed.
                              2. Hash list problems resolved.
         sb051.102  ag        1. System Services Returns checked.
                              2. DNS Server is opened only when useDNS is True
         sb052.102  ag        1. Provide ethereal like message trace. 
         sb054.102  rk        1. Bundling Changes.
         sb056.102  rk        1. In case of primary dest address failure
                                 try assoc on alternate dest addr of
                                 address list 
         sb057.102  pr        1. Multiple proc ids support added.
         sb060.102  pr        1. TOS enhancement.
         sb064.102  pr        1. Remove compiler warnings.
         sb065.102  kp        1. UDP port as configurable parameter.
         sb068.102  kp        1. For sending suEndpId in SbUiSctEndpCloseCfm 
                                 if endpIdType = SCT_ENDPID_SP 
         sb070.102  kp        1.Multi-Homing enhancements.
         sb075.102  pc        1.Path Management enhancements.
         sb076.102  kp        1.changed sbLmGenAlarm to macro due to the 
                                addition of new feild info for path alarm.
         sb077.102  kp        1.Removing the association validity check out 
                                of ERRCLS_INT_PAR validate the assocId
         sb080.102  kp        1.Adjusting the macro call to single line
                              2.Copying of localConn first in the list
                              3.Removal of some checks out of ERRCLASS
         sb081.102  kp        1.Removal of some checks out of ERRCLASS.
                              2.Gen-configuration check for incoming 
                                message when layer ShutDown. 
         sb082.102  kp        1.Changes for Non-ANSI compilation.
         sb084.102  kp        1.Changes for removal of compilation
                                warnings.
         sb085.102  kp        1.Changes for de-registration of TAPA task.
         sb086.102  rsr       1.IP_ANY support
         sb087.102  kp        1.Hostname changes for INIT/INIT-ACK
/main/3      ---    rsr/ag    1. Updated for Release of 1.3
         sb001.103  ag        1. spAssocId validation added in SbUiSctAssocRsp.
                              2. UMR Fix.
         sb003.103  ag        1. Satellite SCTP feature (under compile-time
                                 flags SB_ECN & SB_SATELLITE).
                              2. Moved the smPst structure from genCfg to 
                                 reConfig structure of general configuration.
         sb004.103  ag        1. Protected the changes for making smPst structure
                                 reconfigurable under a new compile time flag LSB9.
         sb005.103  ag        1. Removed compilation warning - multiple tSap 
                                 declaration in sbUiSctAssocReq().
                              2. Moved the stream Id and DTA sanity checks for 
                                 association request outside ERRCLASS falgs.
                              3. Initialized the T5 ShutdownGuard timer during the 
                                 association control block creation.
                              4. IPV6 changes: added debug prints for IPV6.
                              5. Replaced macro SB_PUTMSG with SB_CHK_PUTMSG.
        sb009.103 nuX         1. changes made for SOL10 and IPV4IPV6 upgrade and 
                                 all the changes are made under SB_SOL10_MULTIPORT
                                 or SB_IPV4IPV6_COMBINED flag.
        sb010.103 nuX         1. Resetting the elmId in the case of failure of
                                 sbLiBindSap premitive.
        sb011.103 nuX         1. Placed Timer check under SB_TMR_TST flag.
        sb012.103 pkaX        1. Replaced the SB_TMR_TST flag with LSB12.
                              2. Fixed TSAP Unbind issue.
        sb013.103 pkaX        1. Dual Checksum Fix.
        sb017.103 pkaX        1. Added supported address type parameter 
                                 in init chunk.
        sb019.103 krkX        1. Fix for the ERRCLASS issue.
                              2. Added Defensive NULL checks for localConn.
                              3. The addrCb is not made NULL and not removed
                                 from hash list when we get discInd.
/main/3 sb020.103 krkX        1. Fix for the KlockWorks issue.
/main/3 sb023.103 ajainx      1. Assign correct value to smPst.
/main/3 sb024.103 ajainx      1. Included protId parameter in status indication.
/main/3 sb028.103 ajainx      1. Send StaInd to the SCTP user layer if
                                 duplicate association request is received.
                              2. Send sack for data chunk received with cookie.
                              3. Fix for compilation warnings.
/main/3 sb029.103 krkX        1. If SCTP user does not want the association
                                 (sent assocRsp with SCT_NOK), send User initated abort
                                 instead of abort.
/main/3 sb030.103 krkX        1. If the ABORTchunk is bundled after COOKIE-ECHO
                                 chunk return RFAILED,if freeze timer is running.
                              2. Corrected the suId to suConId in cleanup of
                                 localAddrCb for DiscCfm.
                              3. Fixed the warnings during 64-BIT compilation.
/main/3 sb031.103 vsk         1. Added a Check for the return value of cmHashListFind and
                                 if we have any entries in hash list, delete the entries 
                                 first and then free the memory allocated to that entry 
                                 in the case of the same address and same port provided 
                                 for endpoint opening.
                              2. Moved the sbAsAbortAssoc function call below the ret check
                                 of sbAsSendUserAbort.
                              3. Sending SbUiSctTermCfm to upper layer even, user requested
                                 SuAssocId/SpAssocId match not found in any SbSctAssocCb's.
/main/3 sb032.103 vsk         1. Fixed the compilation issues and warnings. 
                              2. Changed the dstNAddr type from pointer to the local variable
/main/3 sb033.103 sdey        1. Initialized the sbSqCb.rcvfrag to null under 
                                 SB_FRAG_TSN_CHK flag.
                              2. Added TRC macro inside sbEndpOpenCleanup function.
/main/3 sb034.103 vsk         1. Initialized bufLen variables to zero in 
                                 primitive SbUiSctDatReq to fix compilation 
                                 errors on VxWorks-6.7.
                              2. Fixed logical error in calculating the DNS 
                                 control block in SbLiHitDiscCfm primitive. 
                              3. Fixed gcc compilation warnings in 
                                 SbUiSctEndpOpenReq primitive.
/main/3 sb035.103 vsk         1. Fixed the warnings for LONG_MSG flag enabled.
                              2. Fix for KlockWorks warnings. 
*********************************************************************91*/
