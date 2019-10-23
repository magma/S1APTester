

/********************************************************************20**
 
     Name:     S1AP - Management Interface Module
  
     Type:     C source file
  
     Desc:     C source code for LM Module
  
     File:     sz_mi.c
  
     Sid:      sq_mi.c@@/main/4 - Mon Jan 10 22:17:01 2011
  
     Prg:      nm
  
*********************************************************************21*/

/************************************************************************
 
     Note: 
 
************************************************************************/


/* header include files -- defines (.h) */
#include "envopt.h"        /* Environment options             */
#include "envdep.h"        /* Environment dependent options   */
#include "envind.h"        /* Environment independent options */
#include "gen.h"           /* General layer                   */
#include "ssi.h"           /* System service interface        */
#include "cm5.h"           /* Common timer library            */
#include "cm_llist.h"      /* Common linked list library      */
#include "cm_hash.h"       /* Common hash library             */
#include "cm_tpt.h"        /* Common transport library        */
#include "cm_tkns.h"       /* Common tokens                   */
#include "cm_mblk.h"       /* Common memory allocation        */
#include "cm_inet.h"       /* Common socket library           */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#include "cm_pasn.h"
#ifdef SZ_FTHA
#include "cm_psfft.h"
#include "cm_ftha.h"
#include "cm_pftha.h"
#include "cm_psf.h"
#ifdef SS_DIAG
/* sz008.301 : Change for Diagnostics */
#include "ss_diag.h"        /* Common log file */
#endif
#endif /* SZ_FTHA */

#include "sct.h"           /* SCT interface defines           */
#include "szt.h"           /* SZT interface defines           */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "sht.h"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.h"           /* S1AP Layer management           */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef YT
#include "lyt.h"            /* S1AP-PSF                        */
#include "yt.h"            /* S1AP-PSF                        */
#endif /* YT */
#include "sz.h"            /* S1AP layer defines              */
#include "sz_err.h"        /* S1AP - error                    */
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.h"
#endif

/* header/extern include files (.x) */
#include "gen.x"           /* General layer                   */
#include "ssi.x"           /* System services interface       */
#include "cm5.x"           /* Common timer module             */
#include "cm_lib.x"        /* Common linrary function         */
#include "cm_llist.x"      /* Common link list library        */
#include "cm_hash.x"       /* Common hash list library        */
#include "cm_tkns.x"       /* Common tokens                   */
#include "cm_tpt.x"        /* Common transport library        */
#include "cm_mblk.x"       /* Common memory allocation        */
#include "cm_inet.x"       /* Common socket library           */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#include "cm_pasn.x"
#ifdef SZ_FTHA
#include "cm_ftha.x"
#include "cm_pftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#include "sht.x"           /* System Agent */
#endif /* SZ_FTHA */
/* sz006.301: Removed un-necessary include files  */
#include"szt_asn.x"        /* common ss7 */
#ifndef SZ_ENC_DEC
#include "szt_pk.x"
#include "szt_unpk.x"
#endif /* SZ_ENC_DEC */

#include "sct.x"           /* SCT interface defines           */
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.x"
#endif
#include "szt.x"           /* SZT interface structures        */
#include "lsz.x"           /* S1AP Layer management           */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef YT
#include "lyt.x"            /* S1AP-PSF                        */
#include "yt.x"            /* S1AP-PSF                        */
#endif /* YT */
#include "sz.x"            /* S1AP layer structures           */


/* Public variable declarations */

#ifdef SS_MULTIPLE_PROCS
   PUBLIC SzCb szCbLst[SZ_MAX_INSTANCES];
   PUBLIC SzCb *szCbPtr;
#else /* SS_MULTIPLE_PROCS */
   PUBLIC SzCb szCb;
#endif /* SS_MULTIPLE_PROCS */

/* Private function declarations */

PRIVATE S16 szSendLmCfm ARGS((
      Pst *pst,                           
      Header *hdr,                           
      U8 type,                               
      SzMngmt *cfm                           
      ));
PRIVATE S16 szGenCfg ARGS((
      SzGenCfg *gen,       
      CmStatus *status     
      ));
PRIVATE S16 szValidateGenCfg ARGS((
      SzGenCfg *gen        
      ));
PRIVATE S16 szProtCfg ARGS((
      SzProtCfg *prot,     
      CmStatus *status     
      ));
PRIVATE S16 szValidateProtCfg ARGS((
      SzProtCfg *prot      
      ));
PRIVATE S16 szSztSapCfg ARGS((
      SzSztSapCfg *sztSap,     
      CmStatus *status         
      ));
PRIVATE S16 szValidateSztSapCfg ARGS((
      SzSztSapCfg *sztSap      
      ));
PRIVATE S16 szSctSapCfg ARGS((
      SzSctSapCfg *sctSap,     
      CmStatus *status         
      ));
PRIVATE S16 szValidateSctSapCfg ARGS((
      SzSctSapCfg *sctSap      
      ));
PRIVATE S16 szPeerCfg ARGS((
      SzPeerCfg *peer,     
      CmStatus *status,
      Header   *hdr
      ));
PRIVATE S16 szValidatePeerCfg ARGS((
      SzPeerCfg *peer      
      ));
PRIVATE S16 szGenCntrl ARGS((
      SzCntrl *cntrl,         
      CmStatus *status        
      ));
PRIVATE S16 szSztSapCntrl ARGS((
      SzCntrl *cntrl,         
      CmStatus *status        
      ));
PRIVATE S16 szValidateSztSapCntrl ARGS((
      SzCntrl  *cntrl         
      ));
   /* sz003.301: szDelSztSap is made as Global as it used in PSF
    * layer */
PRIVATE S16 szSctSapCntrl ARGS((
      SzCntrl *cntrl,         
      CmStatus *status        
      ));
PRIVATE S16 szValidateSctSapCntrl ARGS((
      SzCntrl  *cntrl         
      ));
PRIVATE S16 szEnaSctSap ARGS((
      SpId  lSapId         
      ));
PRIVATE S16 szUbndSctSap ARGS((
      SpId  lSapId,        
      U8    opn,
      U8    contEnt        
      ));
   /* sz003.301: szDelSztSap is made as Global as it used in PSF
    * layer */
PRIVATE S16 szPeerCntrl ARGS((
      SzCntrl *cntrl,         
      CmStatus *status        
      ));
PRIVATE S16 szValidatePeerCntrl ARGS((
      SzCntrl  *cntrl         
      ));
PRIVATE S16 szDelPeer ARGS((
      SzPeerCb *peerCb     
      ));
PRIVATE S16 szGetGenSts ARGS((
      SzGenSts *sts,              
      CmStatus *status,           
      Action action               
      ));
PRIVATE S16 szValidateGenSts ARGS((
      SzGenSts  *sts,         
      Action action           
      ));
PRIVATE S16 szGetPeerNodeSts ARGS((
      SzPeerNodeSts *sts,         
      CmStatus *status,           
      Action action               
      ));
PRIVATE S16 szValidatePNodeSts ARGS((
      SzPeerNodeSts  *sts,         
      Action action                
      ));
PRIVATE S16 szGetSctSapSts ARGS((
      SzSctSapSts *sts,         
      CmStatus *status,           
      Action action               
      ));
PRIVATE S16 szValidateSctSapSts ARGS((
      SzSctSapSts  *sts,         
      Action action                
      ));
PRIVATE S16 szGetGenSta ARGS((
      SzGenSta *sta,         
      CmStatus *status       
      ));     
PRIVATE S16 szGetSztSapSta ARGS((
      SzSapSta *sta,         
      CmStatus *status       
      ));
PRIVATE S16 szValidateSztSapSta ARGS((
      SzSapSta *sta          
      ));
PRIVATE S16 szGetSctSapSta ARGS((
      SzSapSta *sta,         
      CmStatus *status       
      ));
PRIVATE S16 szValidateSctSapSta ARGS((
      SzSapSta *sta          
      ));
PRIVATE S16 szGetPeerSta ARGS((
      SzPeerSta *sta,         
      CmStatus *status        
      ));
PRIVATE S16 szValidatePeerSta ARGS((
      SzPeerSta *sta         
      ));
/* sz003.301: Added new functions for PSF-S1AP */
#ifdef SZ_FTHA
PRIVATE S16 szFillRepPost ARGS((
      Pst *pst,
      ShtCntrlReqEvnt *reqInfo,
      Pst *repPst
      ));
PRIVATE S16 szEnbDisSap ARGS((
      ShtCntrlReqEvnt *reqInfo,
      ShtCntrlCfmEvnt  *cfmInfo
      ));
#ifdef SZ_RUG
PRIVATE S16 szGetVer ARGS(( 
      ShtGetVerCfm  *getVerCfmInfo 
      ));
PRIVATE S16 szUpdVer ARGS((
      ShtVerInfo *shtVerInfo
      ));
#endif /* SZ_RUG */
#endif /* SZ_FTHA */

/******************************************************************************/
/*                   Management Primitives                                    */
/******************************************************************************/

/******************************************************************************/
/*                   Configuration Request Primitive                          */
/******************************************************************************/
/*
 *
 *       Fun:   SzMiLszCfgReq - Configuration Request
 *
 *       Desc:  This function is used by the layer manager to configure
 *              the S1AP layer. The layer responds with a Configuration
 *              Confirm "SzMiLszCfgCfm" to the layer manager after
 *              completing the configuration.
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: Configuration must be performed in the following
 *              sequence:
 *              1) General configuration (STSZGEN)
 *              2) Protocol configuration (STSZPROT)
 *              3) Upper sap configuration (STSZSZTSAP)
 *              4) Lower sap configuration (STSZSCTSAP)
 *              5) Peer configuration (STSZPEER)
 *              
 *       File:  sz_mi.c
 *
 */
#ifdef ANSI
PUBLIC S16 SzMiLszCfgReq
(
Pst *pst,
SzMngmt *cfg            /* Config structure */
)
#else
PUBLIC S16 SzMiLszCfgReq(pst, cfg)
Pst *pst;
SzMngmt *cfg;           /* Config structure */
#endif
{
   S16 ret = ROK;       /* Return Value */
   SzMngmt cfgCfm;      /* Config confirm */

   TRC3(SzMiLszCfgReq);

   cmMemset ((U8 *)&cfgCfm, 0, sizeof (SzMngmt));

#ifdef SS_MULTIPLE_PROCS
   if( ((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&szCbPtr)) 
                 != ROK) || (szCbPtr == NULLP) )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SLOGERROR(pst->dstEnt, pst->dstInst, pst->dstProcId,__FILE__, __LINE__,\
                ERRCLS_DEBUG,ESZ075,0,
                 "SzMiLszCfgReq() failed, cannot derive szCb");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

      RETVALUE(RFAILED);
   }
#ifdef DEBUGP
   SZDBGP(DBGMASK_MI,(szCb.init.prntBuf,
         "--------SzMiLszCfgReq-----(proc(%d),ent(%d),inst(%d))-------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));
#endif
#endif /*SS_MULTIPLE_PROCS */

   SZDBGP(DBGMASK_MI, (szCb.init.prntBuf,
      "SzMiLszCfgReq (pst, elmId (%d))\n", cfg->hdr.elmId.elmnt));

   /* Check if General Configuration is done */
   if ((!szCb.init.cfgDone) && (cfg->hdr.elmId.elmnt != STSZGEN))
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SZLOGERROR(ERRCLS_DEBUG,ESZ076,0,
                 "SzMiLszCfgReq: General configuration not done ");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

      if (cfg->hdr.elmId.elmnt == STSZPEER)
      {
         if(cfg->u.cfg.u.peer.peerInfo != NULLP)
         {
            /* sz002.201 Performance related changes */
            (Void)SPutSBuf(szCb.init.region, szCb.init.pool, 
                  (Data*)(cfg->u.cfg.u.peer.peerInfo), 
                  (sizeof(SzPeerInfo) *  cfg->u.cfg.u.peer.nmbPeers));       

            cfg->u.cfg.u.peer.peerInfo    =  NULLP;
         }
      }
      cfgCfm.cfm.status = LCM_PRIM_NOK;
      cfgCfm.cfm.reason = LCM_REASON_GENCFG_NOT_DONE;
      szSendLmCfm (pst, &cfg->hdr, TCFG, &cfgCfm);

      RETVALUE(ROK);
   }

   switch (cfg->hdr.elmId.elmnt)
   {
      case STSZGEN:       /* general config */
      {
         ret = szGenCfg (&cfg->u.cfg.u.gen, &cfgCfm.cfm);
         break;
      }
      case STSZPROT:       /* protocol config */
      {
         ret = szProtCfg (&cfg->u.cfg.u.prot, &cfgCfm.cfm);
         break;
      }
      case STSZSZTSAP:      /* Upper Sap config */
      {
         ret = szSztSapCfg (&cfg->u.cfg.u.sztSap, &cfgCfm.cfm);
         break;
      }
      case STSZSCTSAP:      /* network sap config */
      {
         ret = szSctSapCfg (&cfg->u.cfg.u.sctSap, &cfgCfm.cfm);
         break;
      }
      case STSZPEER:
      {
         ret = szPeerCfg (&cfg->u.cfg.u.peer, &cfgCfm.cfm, &cfg->hdr);
         break;
      }
      default:
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SZLOGERROR(ERRCLS_DEBUG, ESZ077, (ErrVal) cfg->hdr.elmId.elmnt,
                    "SzMiLszCfgReq: invalid elmnt");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */

         cfgCfm.cfm.status = LCM_PRIM_NOK;
         cfgCfm.cfm.reason = LCM_REASON_INVALID_ELMNT;
      }
   }

   szSendLmCfm(pst, &cfg->hdr, TCFG, &cfgCfm);

   RETVALUE(ret); 
    

} /* SzMiLszCfgReq */

/******************************************************************************/
/*                   Control Request Primitive                                */
/******************************************************************************/
/*
*
*       Fun:   SzMiLszCntrlReq - Control Request
*
*       Desc:  This primitive is used to control the specified element.
*              It can be used to enable or disable trace and alarm
*              (unsolicited status) generation. It can also be used
*              to delete a SAP or a group of SAPs. The control request
*              is also used for debug printing control.
*
*       Ret:   ROK     - ok
*              RFAILED - failure
*
*       Notes: None
*
*       File:  sz_mi.c
*/
#ifdef ANSI
PUBLIC S16 SzMiLszCntrlReq
(
Pst     *pst,               
SzMngmt *cntrl              /* Control structure */
)
#else
PUBLIC S16 SzMiLszCntrlReq(pst, cntrl)
Pst     *pst;               
SzMngmt *cntrl;             /* Control structure */
#endif
{
   S16 ret = ROK;           /* Return value */
   SzMngmt cntrlCfm;        /* Control confirm */

   TRC3(SzMiLszCntrlReq);

   cmMemset ((U8 *)&cntrlCfm, 0, sizeof (SzMngmt));

#ifdef SS_MULTIPLE_PROCS
   if( ((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&szCbPtr))
                 != ROK) || (szCbPtr == NULLP) )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SLOGERROR(pst->dstEnt, pst->dstInst, pst->dstProcId,__FILE__, __LINE__,\
                ERRCLS_DEBUG,ESZ078,0,
                 "SzMiLszCntrlReq() failed, cannot derive szCb");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */

      RETVALUE(RFAILED);
   }
#ifdef DEBUGP
   SZDBGP(DBGMASK_MI,(szCb.init.prntBuf,
         "--------SzMiLszCntrlReq-----(proc(%d),ent(%d),inst(%d))-------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));
#endif
#endif /*SS_MULTIPLE_PROCS */

#ifdef DEBUGP
   SZDBGP(DBGMASK_MI, (szCb.init.prntBuf,
      "SzMiLszCntrlReq (pst, elmId (%d))\n", cntrl->hdr.elmId.elmnt));
#endif

#if (ERRCLASS & ERRCLS_DEBUG)
   /* Check if General Configuration is done */
   if (!szCb.init.cfgDone) 
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SZLOGERROR(ERRCLS_DEBUG,ESZ079,0,
                 "SzMiLszCntrlReq: General configuration not done ");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */

      cntrlCfm.cfm.status = LCM_PRIM_NOK;
      cntrlCfm.cfm.reason = LCM_REASON_GENCFG_NOT_DONE;
      szSendLmCfm (pst, &cntrl->hdr, TCNTRL, &cntrlCfm);

      RETVALUE(ROK);
   }
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

   /* check element */
   switch(cntrl->hdr.elmId.elmnt)
   {
      case STSZGEN:
      {
         /* general (applicable layer-wide) control */
         ret = szGenCntrl(&cntrl->u.cntrl, &cntrlCfm.cfm);
         break;
      }
      case STSZSZTSAP:
      {
         /* S1AP's upper SAP */
         ret = szSztSapCntrl(&cntrl->u.cntrl, &cntrlCfm.cfm);
         break;
      }
      case STSZSCTSAP:
      {
         /* S1AP's lower SAP */
         ret = szSctSapCntrl(&cntrl->u.cntrl, &cntrlCfm.cfm);
         break;
      }
      case STSZPEER:
      {
         /* Peer control */
         ret = szPeerCntrl(&cntrl->u.cntrl, &cntrlCfm.cfm);
         break;
      }
      default:
      {
         /* invalid element */
#if (ERRCLASS & ERRCLS_DEBUG)
         SZLOGERROR(ERRCLS_DEBUG, ESZ080, (ErrVal) cntrl->hdr.elmId.elmnt,
                    "SzMiLszCntrlReq: Invalid Element in control request");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */

         cntrlCfm.cfm.status = LCM_PRIM_NOK;
         cntrlCfm.cfm.reason = LCM_REASON_INVALID_ELMNT;
         break;
      }
   } /* end switch */

   szSendLmCfm(pst, &cntrl->hdr, TCNTRL, &cntrlCfm);

   /* sz003.301: Added hooks for PSF-S1AP */
   /* Flush the update messages */
#ifdef YT
   YT_UPD_PEER();
#endif /* YT */

   RETVALUE(ret);

} /* SzMiLszCntrlReq */

/******************************************************************************/
/*                   Statistics Request Primitive                             */
/******************************************************************************/
/*
*
*       Fun:   SzMiLszStsReq - Statistics Request
*
*       Desc:  This primitive is used by the Layer Manager to solicit 
*              statistics information. The statistics are returned
*              in the  SzMiLszStsCfm primitive.
*
*       Ret:   ROK     - ok
*              RFAILED - failure
*
*       Notes: None
*
*       File:  sz_mi.c
*
*/

#ifdef ANSI
PUBLIC S16 SzMiLszStsReq
(
Pst     *pst,                
Action  action,              
SzMngmt *sts                 /* Statistics structure */
)
#else
PUBLIC S16 SzMiLszStsReq(pst, action, sts)
Pst     *pst;                
Action  action;              
SzMngmt *sts;                /* Statistics structure */
#endif
{
   S16 ret = ROK;            /* Return value */  
   SzMngmt stsCfm;           /* Statistics confirm */

   TRC3(SzMiLszStsReq);
  
   cmMemset ((U8 *)&stsCfm, 0, sizeof (SzMngmt));

#ifdef SS_MULTIPLE_PROCS
   if( ((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&szCbPtr))
                 != ROK) || (szCbPtr == NULLP) )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SLOGERROR(pst->dstEnt, pst->dstInst, pst->dstProcId,__FILE__, __LINE__,\
                ERRCLS_DEBUG,ESZ081,0,
                 "SzMiLszStsReq() failed, cannot derive szCb");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */

      RETVALUE(RFAILED);
   }
#ifdef DEBUGP
   SZDBGP(DBGMASK_MI,(szCb.init.prntBuf,
         "--------SzMiLszStsReq-----(proc(%d),ent(%d),inst(%d))-------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));
#endif
#endif /*SS_MULTIPLE_PROCS */

#ifdef DEBUGP
   SZDBGP(DBGMASK_MI, (szCb.init.prntBuf,
          "SzMiLszStsReq (pst, action(%d), elmId (%d)) \n", 
           action, sts->hdr.elmId.elmnt));
#endif

#if (ERRCLASS & ERRCLS_DEBUG)
   /* Check if General Configuration is done */
   if (!szCb.init.cfgDone) 
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SZLOGERROR(ERRCLS_DEBUG,ESZ082,0,
                 "SzMiLszStsReq: General configuration not done ");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */

      stsCfm.cfm.status = LCM_PRIM_NOK;
      stsCfm.cfm.reason = LCM_REASON_GENCFG_NOT_DONE;
      szSendLmCfm (pst, &sts->hdr, TSTS, &stsCfm);

      RETVALUE(ROK);
   }
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

   /* check element */
   switch (sts->hdr.elmId.elmnt)
   {
      case STSZGEN:              /* General statistics */
      {
         ret = szGetGenSts (&stsCfm.u.sts.u.gen, &stsCfm.cfm, action);
         break;
      }
      case STSZPEER:            /* Peer node statistics */
      {
         cmMemcpy ((U8 *)&stsCfm.u.sts.u.node, (U8 *)&sts->u.sts.u.node,
               sizeof(sts->u.sts.u.node));
         cmMemset ((U8 *)&stsCfm.u.sts.u.node.cfm.pdu, 0, sizeof (SzPduSts));
         cmMemset ((U8 *)&stsCfm.u.sts.u.node.cfm, 0, sizeof (stsCfm.u.sts.u.node.cfm));
         ret = szGetPeerNodeSts (&stsCfm.u.sts.u.node, &stsCfm.cfm, action);
         if (ret == RFAILED)
         {
#if (ERRCLASS & ERRCLS_INT_PAR)
            SZLOGERROR(ERRCLS_INT_PAR, ESZ083, ERRZERO,
                       "SzMiLszStsReq: Failed to get Peer node statistics");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */
         }
         break;
      }
      /* sz001.201 Added SCT SAP level statistics */
      case STSZSCTSAP:            /* SCT SAP statistics */
      {
         cmMemset((U8 *)&stsCfm.u.sts.u.sctSap, 0, sizeof(SzSctSapSts));
         stsCfm.u.sts.u.sctSap.suId = sts->u.sts.u.sctSap.suId;

         ret = szGetSctSapSts (&stsCfm.u.sts.u.sctSap, &stsCfm.cfm, action);
         if (ret == RFAILED)
         {
#if (ERRCLASS & ERRCLS_INT_PAR)
            SZLOGERROR(ERRCLS_INT_PAR, ESZ084, ERRZERO,
                       "SzMiLszStsReq: Failed to get sct sap statistics");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */
         }
         break;
      }
      default:
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SZLOGERROR(ERRCLS_DEBUG, ESZ085, (ErrVal) sts->hdr.elmId.elmnt,
                    "SzMiLszStsReq: Invalid element in statistics request");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

         stsCfm.cfm.status = LCM_PRIM_NOK;
         stsCfm.cfm.reason = LCM_REASON_INVALID_ELMNT;
         break;
      }
   } 

   /* Issue a statistics confirm */
   szSendLmCfm(pst, &sts->hdr, TSTS, &stsCfm);

   RETVALUE(ret);

} /* SzMiLszStsReq */

/******************************************************************************/
/*                   Status  Request Primitive                                */
/******************************************************************************/
/*
*
*       Fun:   Status Request
*
*       Desc:  This primitive is used by the Layer Manager to solicit
*              status information. The information is returned via the
*              SzMiLszStaCfm primitive.
*
*       Ret:   ROK     - ok
*              RFAILED - failure
*
*       Notes: None
*
*       File:  sz_mi.c
*
*/
#ifdef ANSI
PUBLIC S16 SzMiLszStaReq
(
Pst     *pst,                
SzMngmt *sta                 /* Status structure */
)
#else
PUBLIC S16 SzMiLszStaReq(pst, sta)
Pst     *pst;                
SzMngmt *sta;                /* Status structure */
#endif
{
   S16 ret = ROK;            /* Return value */
   SzMngmt staCfm;           /* Status confirm */

   TRC3(SzMiLszStaReq)

   cmMemset ((U8 *)&staCfm, 0, sizeof (SzMngmt));

#ifdef SS_MULTIPLE_PROCS
   if( ((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&szCbPtr))
                 != ROK) || (szCbPtr == NULLP) )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SLOGERROR(pst->dstEnt, pst->dstInst, pst->dstProcId,__FILE__, __LINE__,\
                ERRCLS_DEBUG,ESZ086,0,
                 "SzMiLszStaReq() failed, cannot derive szCb");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */

      RETVALUE(RFAILED);
   }
#ifdef DEBUGP
   SZDBGP(DBGMASK_MI,(szCb.init.prntBuf,
         "--------SzMiLszStaReq-----(proc(%d),ent(%d),inst(%d))-------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));
#endif
#endif /*SS_MULTIPLE_PROCS */

#ifdef DEBUGP
   SZDBGP(DBGMASK_MI, (szCb.init.prntBuf,
          "SzMiLszStaReq (pst, elmId (%d)) \n", sta->hdr.elmId.elmnt));
#endif
#if (ERRCLASS & ERRCLS_DEBUG)
   /* Check if General Configuration is done */
   if (!szCb.init.cfgDone)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SZLOGERROR(ERRCLS_DEBUG,ESZ087,0,
                 "SzMiLszStaReq: General configuration not done ");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */

      staCfm.cfm.status = LCM_PRIM_NOK;
      staCfm.cfm.reason = LCM_REASON_GENCFG_NOT_DONE;
      szSendLmCfm (pst, &sta->hdr, TSSTA, &staCfm);

      RETVALUE(ROK);
   }
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

   switch (sta->hdr.elmId.elmnt)
   {
      case STSZSID:
      {
         staCfm.cfm.status = LCM_PRIM_OK;
         staCfm.cfm.reason = LCM_REASON_NOT_APPL;
         (Void) szGetSId (&staCfm.u.ssta.s.sysId);
         break;
      }
      case STSZGEN:
      {
         ret = szGetGenSta (&staCfm.u.ssta.s.gen, &staCfm.cfm);
         break;
      }
      case STSZSZTSAP:
      {
         cmMemcpy ((U8 *)&staCfm.u.ssta.s.sap, (U8 *)&sta->u.ssta.s.sap,
               sizeof (SzSapSta));
         ret = szGetSztSapSta (&staCfm.u.ssta.s.sap, &staCfm.cfm);
         break;
      }
      case STSZSCTSAP:
      {
         cmMemcpy ((U8 *)&staCfm.u.ssta.s.sap, (U8 *)&sta->u.ssta.s.sap,
               sizeof (SzSapSta));
         ret = szGetSctSapSta (&staCfm.u.ssta.s.sap, &staCfm.cfm);
         break;
      }
      case STSZPEER:
      {
         cmMemcpy ((U8 *)&staCfm.u.ssta.s.peer, (U8 *)&sta->u.ssta.s.peer,
               sizeof (SzPeerSta));
         ret = szGetPeerSta (&staCfm.u.ssta.s.peer, &staCfm.cfm);
         break;
      }
      default:
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SZLOGERROR(ERRCLS_DEBUG, ESZ088, (ErrVal) sta->hdr.elmId.elmnt,
                    "SzMiLszStaReq: Invalid element in Status request");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

         staCfm.cfm.status = LCM_PRIM_NOK;
         staCfm.cfm.reason = LCM_REASON_INVALID_ELMNT;

         break;
      }

   } /* end switch */

   szSendLmCfm(pst, &sta->hdr, TSSTA, &staCfm);

   RETVALUE(ret);

} /* SzMiLszStaReq */


/******************************************************************************/
/*                  Indication Generation Functions                           */
/******************************************************************************/
/*
 *
 *      Fun:   szSendLmAlarm
 *
 *      Desc:  This function is used to send an Alarm / Unsolicited Status
 *             Indication to the Layer Manager
 *
 *      Ret:   ROK     - ok
 *             RFAILED - failure
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PUBLIC Void szSendLmAlarm
(
U16 category,           /* category */
U16 event,              /* event generated */
U16 cause,              /* cause */
SzUstaDgn *dgn          /* Diagnostics */
)
#else
PUBLIC Void szSendLmAlarm(category, event, cause, dgn)
U16 category;           /* category */
U16 event;              /* event generated */
U16 cause;              /* cause */
SzUstaDgn *dgn;         /* Diagnostics */
#endif
{
   SzMngmt usta;

   TRC2(szSendLmAlarm);

#if (ERRCLASS & ERRCLS_DEBUG)
   /* Check if general configuration is done */
   if (szCb.init.cfgDone == FALSE)
   {
      SZLOGERROR(ERRCLS_DEBUG, ESZ089, (ErrVal)0,
           "Status Indication requested; general configuration not done.");
      RETVOID;
   }
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

   if (szCb.init.usta == FALSE)
      RETVOID;

   /* initialize the management structure */
   (Void)cmMemset((U8 *) &usta, '\0', (PTR)sizeof(usta));

   usta.hdr.elmId.elmnt = STSZGEN;
   usta.hdr.entId.ent = szCb.init.ent;
   usta.hdr.entId.inst = szCb.init.inst;

   usta.u.usta.alarm.category = category;
   usta.u.usta.alarm.event = event;
   usta.u.usta.alarm.cause = cause;

   /* copy the usta structure */
   cmMemcpy((U8 *)&usta.u.usta.dgn, (U8 *)dgn, (PTR)sizeof(SzUstaDgn));

   /* update the date and time */
   (Void) SGetDateTime(&usta.u.usta.alarm.dt);

   SzMiLszStaInd(&szCb.init.lmPst, &usta);

   RETVOID;

} /* end of szSendLmAlarm */

/*
 *
 *      Fun:   szSendLmTrc
 *
 *      Desc:  This function is used to send Trace Indication to
 *             the Layer Manager. 
 *
 *      Ret:   ROK     - ok
 *             RFAILED - failure
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PUBLIC S16 szSendLmTrc
(
S32 trcLen,          /* Trace length */
SzTrc *trcParam,     /* trace data */
Buffer *mBuf         /* message buffer */
)
#else
PUBLIC S16 szSendLmTrc(trcLen, trcParam, mBuf)
S32 trcLen;          /* Trace length */
SzTrc *trcParam;     /* trace data */
Buffer *mBuf;        /* message buffer */
#endif
{

   S16 ret;
   MsgLen ml = 0;
   SzMngmt trc;
   Buffer *trcBuf = NULLP;

   TRC2(szSendLmTrc);

#if (ERRCLASS & ERRCLS_DEBUG)
   /* Check if general configuration is done */
   if (szCb.init.cfgDone == FALSE)
   {
      SZLOGERROR(ERRCLS_DEBUG, ESZ090, (ErrVal)0,
           "Trace Indication requested; general configuration not done.");
      RETVALUE(ROK);
   }
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

   if (trcLen == 0)
   {
      RETVALUE(ROK);
   }

   cmMemset((U8 *)&trc, 0, sizeof(SzMngmt));
   cmMemcpy((U8 *)&trc.u.trc, (U8 *)trcParam, sizeof(SzTrc));

   trcBuf = NULLP;

   if (mBuf != NULLP)
   {
      Buffer *tmpBuf = NULLP;

      (Void)SFndLenMsg(mBuf, &ml);
      if(ml == 0)
      {
         RETVALUE(ROK);
      }

      if((ret = SCpyMsgMsg(mBuf, szCb.init.lmPst.region, 
                  szCb.init.lmPst.pool, &trcBuf)) != ROK)
      {
         /* Error message will be send from the SSI fn */
#if (ERRCLASS & ERRCLS_ADD_RES)
         SZLOGERROR(ERRCLS_ADD_RES, ESZ091, (ErrVal)0, "SCpyMsgMsg() failed.");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */
         SZ_FREE_BUF(trcBuf);
         RETVALUE(RFAILED);
      }

      if (trcLen > 0  &&  trcLen < ml)
      {
         ml = (S16) trcLen;
         if((ret = SSegMsg(trcBuf, ml, &tmpBuf)) != ROK)
         {
#if (ERRCLASS & ERRCLS_ADD_RES)
            SZLOGERROR(ERRCLS_ADD_RES, ESZ092, (ErrVal)0, "SSegMsg() failed.");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */
            SZ_FREE_BUF(trcBuf);
            SZ_FREE_BUF(tmpBuf);
            RETVALUE(RFAILED);
         }
         /* free the temporary buffer */
         SZ_FREE_BUF(tmpBuf);
      }
   }

   trc.hdr.elmId.elmnt = STSZGEN;
   SGetDateTime(&trc.u.trc.dt);

   SzMiLszTrcInd(&szCb.init.lmPst, &trc, trcBuf);

   RETVALUE(ROK);

} /* end of szSendLmTrc */


/******************************************************************************/
/*                   Management Interface Support Functions                   */
/******************************************************************************/

/******************************************************************************/
/*                   Layer Manager Confirm  Function                          */
/******************************************************************************/
/*
 *
 *      Fun:   szSendLmCfm
 *
 *      Desc:  Generate the Confirm to the Layer Manager
 *
 *      Ret:   ROK   - ok
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szSendLmCfm
(
Pst *pst,                           
Header *hdr,                           /* Pointer to the Header structure */
U8 type,                               /* Confirmation Type */
SzMngmt *cfm                           /* Management Structure */
)
#else
PRIVATE S16 szSendLmCfm(pst, hdr, type, cfm)
Pst *pst;
Header *hdr;                           /* Pointer to the Header structure */
U8 type;                               /* Confirmation Type */
SzMngmt *cfm;                          /* Management Structure */
#endif
{

   Pst cfmPst;                         /* Confirmation Post Structure */

   TRC2(szSendLmCfm);

   /* Fill up the header in the confirm structure */
   cmMemset( (U8 *)&cfm->hdr, '\0', sizeof(cfm->hdr));       
   cfm->hdr.elmId.elmnt = hdr->elmId.elmnt;
   cfm->hdr.entId.ent = szCb.init.ent;
   cfm->hdr.entId.inst = szCb.init.inst;
   cfm->hdr.transId = hdr->transId;

   /* Fill up the post struct for comfirm */
   cfmPst.srcEnt = szCb.init.ent;
   cfmPst.srcInst = szCb.init.inst;
#ifdef SS_MULTIPLE_PROCS
   cfmPst.srcProcId = szCb.init.procId;
#else
   cfmPst.srcProcId = SFndProcId();
#endif
   cfmPst.dstEnt = pst->srcEnt;
   cfmPst.dstInst = pst->srcInst;
   cfmPst.dstProcId = pst->srcProcId;
   cfmPst.selector = hdr->response.selector;
   cfmPst.prior = hdr->response.prior;
   cfmPst.route = hdr->response.route;
   cfmPst.region = hdr->response.mem.region;
   cfmPst.pool= hdr->response.mem.pool;
 
   /* Send the corresponding confirm */
   switch (type)
   {
      case TCFG:
         SZDBGP(DBGMASK_MI, (szCb.init.prntBuf,
               "szSendLmCfm: sent SzMiLszCfgCfm (cfmType: %d) \n", type));
         /* Send Configuration Confirm */
         SzMiLszCfgCfm (&cfmPst, cfm);
         break;

      case TCNTRL:
         SZDBGP(DBGMASK_MI, (szCb.init.prntBuf,
               "szSendLmCfm: sent SzMiLszCntrlCfm (cfmType: %d) \n", type));
         /* Send Control Confirm */
         SzMiLszCntrlCfm (&cfmPst, cfm);
         break;

      case TSTS:
         SZDBGP(DBGMASK_MI, (szCb.init.prntBuf,
               "szSendLmCfm: sent SzMiLszStsCfm (cfmType: %d) \n", type));
         /* Send Statistics Confirm */
         SzMiLszStsCfm (&cfmPst, cfm);
         break;

      case TSSTA:
         SZDBGP(DBGMASK_MI, (szCb.init.prntBuf,
               "szSendLmCfm: sent SzMiLszStaCfm (cfmType: %d) \n", type));
         /* Send Status Confirm */
         SzMiLszStaCfm (&cfmPst, cfm);
         break;

      default:
#if (ERRCLASS & ERRCLS_DEBUG)
         SZDBGP(DBGMASK_MI, (szCb.init.prntBuf, "szSendLmCfm : Invalid Type \n"));
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
         break;
   }

   RETVALUE(ROK); 

} /* szSendLmCfm */


/******************************************************************************/
/*                   Configuration Request Support Functions                  */
/******************************************************************************/

/******************************************************************************/
/*                   General Configuration Support Functions                  */
/******************************************************************************/
/*
 *
 *      Fun:   szGenCfg
 *
 *      Desc:  Stores the general S1AP configuration. It calculates the 
 *             memory requirement and reserves it. It also initializes the
 *             control blocks, the hash lists and registers the timers. In
 *             case of error it rolls back and reports error in the confirm.
 *             If the general configuration is already done it is treated as
 *             reconfiguration. Not all parameters are reconfigurable. 
 *
 *      Ret:   ROK     - ok
 *             RFAILED - failure
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szGenCfg
(
SzGenCfg *gen,       /* General configuration */
CmStatus *status     /* Return status */
)
#else
PRIVATE S16 szGenCfg(gen, status)
SzGenCfg *gen;       /* General configuration */
CmStatus *status;    /* Return status */
#endif
{
   Size memSize;
   S16  ret;
   U32  cnt;
   U16  offset;
   SzConCb conCb;

   TRC2(szGenCfg);

   /* Validate the general configuration elements */
   ret = szValidateGenCfg(gen);   

   if (ret != LCM_REASON_NOT_APPL)
   {
      status->status = LCM_PRIM_NOK;
      status->reason = ret;
      RETVALUE(RFAILED);
   }

   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

   if (szCb.init.cfgDone == TRUE) /* Reconfiguration */
   {

      (Void) cmMemcpy((U8 *)&szCb.init.lmPst, (U8 *) &gen->lmPst,
                      (PTR)sizeof(Pst));
      szCb.init.lmPst.srcProcId = szCb.init.procId;
      szCb.init.lmPst.srcEnt    = szCb.init.ent;
      szCb.init.lmPst.srcInst   = szCb.init.inst;
      szCb.init.lmPst.event     = EVTNONE;

      RETVALUE(ROK);
   } /* end of reconfiguration */

   cmMemset((U8 *)&szCb.genCfg,0,sizeof(SzGenCfg));
   cmMemcpy ((U8 *)&szCb.genCfg, (U8 *)gen, sizeof (SzGenCfg));

   /* sz003.301: Allocate the memory for storing the Interface version */
#ifdef SZ_RUG
   szCb.nmbIntfInfo = 0;
   SZ_ALLOC(szCb.intfInfo, ((szCb.genCfg.nmbSztSaps + szCb.genCfg.nmbSctSaps) * sizeof(ShtVerInfo)));
   if(szCb.intfInfo == NULLP)
   {
      status->status = LCM_PRIM_NOK;
      status->reason = LCM_REASON_MEM_NOAVAIL;
      RETVALUE (RFAILED);
   }
#endif /* SZ_RUG */

   /* Calculate the memory requirement */
   memSize =  szCb.genCfg.nmbSztSaps * (sizeof(SzSztSapCb) + sizeof(SzSztSapCb *));
   memSize += szCb.genCfg.nmbSctSaps * (sizeof(SzSctSapCb) + sizeof(SzSctSapCb *));
   memSize += szCb.genCfg.nmbPeer    * (sizeof(SzPeerCb)   + sizeof(SzPeerCb *));
   memSize += szCb.genCfg.nmbConn    * (sizeof(SzConCb)   + sizeof(SzConCb *));

   /* Reserve the memory */
   ret = SGetSMem(szCb.init.region, (Size) memSize, &szCb.init.pool);
   if (ret != ROK)
   {
      status->status = LCM_PRIM_NOK;
      status->reason = LCM_REASON_MEM_NOAVAIL;
      RETVALUE (ret);
   }

   szCb.genSta.memSize = memSize;
   
   /* Allocate Upper SAP list */
   SZ_ALLOC(szCb.sztSapLst, (gen->nmbSztSaps * sizeof(SzSztSapCb *)));
   if ((SzSztSapCb *)szCb.sztSapLst == (SzSztSapCb *)NULLP)
   {
      (Void) SPutSMem(szCb.init.region, szCb.init.pool);

      status->status=LCM_PRIM_NOK;
      status->reason=LCM_CAUSE_MEM_ALLOC_FAIL;
      RETVALUE(RFAILED);
   }

   /* Allocate Lower SAP list */  
   SZ_ALLOC(szCb.sctSapLst, (gen->nmbSctSaps * sizeof(SzSctSapCb *)));
   if ((SzSctSapCb *)szCb.sctSapLst == (SzSctSapCb *)NULLP)
   {
      SZ_FREE(szCb.sztSapLst, (gen->nmbSztSaps * sizeof(SzSztSapCb *)));

      (Void) SPutSMem(szCb.init.region, szCb.init.pool);

      status->status=LCM_PRIM_NOK;
      status->reason=LCM_CAUSE_MEM_ALLOC_FAIL;
      RETVALUE(RFAILED);
   }
 
   /* Register the timers */
   ret = szRegInitTmr();

#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
   {
      SZ_FREE(szCb.sctSapLst, (gen->nmbSctSaps * sizeof(SzSctSapCb *)));
      SZ_FREE(szCb.sztSapLst, (gen->nmbSztSaps * sizeof(SzSztSapCb *)));
      
      (Void) SPutSMem(szCb.init.region, szCb.init.pool);

      status->status = LCM_PRIM_NOK;
      status->reason = LCM_REASON_REGTMR_FAIL;
      RETVALUE (ret);
   }
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
   
   /* Initialize the elements of SzCb */ 
  
   for (cnt = 0; cnt < (U32) szCb.genCfg.nmbSztSaps; cnt++)
   {
      *(szCb.sztSapLst + cnt) = NULLP;
   }

   for (cnt = 0; cnt < (U32) szCb.genCfg.nmbSctSaps; cnt++)
   {
      *(szCb.sctSapLst + cnt) = NULLP;
   }

   ret = szNdbInitPeerLst();
 
   if(ret == ROK)
   {
      offset = (U16)((PTR)&conCb.lclConHlEnt - (PTR)&conCb);
      /* sz002.201 Performance related changes */
      ret = cmHashListInit(&szCb.lclConCp,      /* hash list Cp */
            (U16)szCb.genCfg.nmbConn,                /* HL bins */
            offset,                             /* Offset of HL Entry */
            FALSE,                              /* Allow dup. keys ? */
            SZ_HASH_KEYTYPE,                    /* HL key type */
            szCb.init.region,                   /* Mem region for HL */
            szCb.init.pool);                    /* Mem pool for HL */
   }

#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
   {
#ifdef SS_MULTIPLE_PROCS
      SDeregTmr(szCb.init.procId, szCb.init.ent, szCb.init.inst, (S16)szCb.genCfg.timeRes,
            (PAIFTMRS16)szActvTmr);
#else
      SDeregTmr(szCb.init.ent, szCb.init.inst, (S16)szCb.genCfg.timeRes,
            (PFS16)szActvTmr);
#endif

      SZ_FREE(szCb.sctSapLst, (gen->nmbSctSaps * sizeof(SzSctSapCb *)));
      SZ_FREE(szCb.sztSapLst, (gen->nmbSztSaps * sizeof(SzSztSapCb *)));

      /* DeInit the hashlists in SzCb */ 
      cmHashListDeinit(&szCb.peerLst);
      /* sz002.201 Added peer hashlist for performance */
      cmHashListDeinit(&szCb.peerAddrPortLst);
      cmHashListDeinit(&szCb.lclConCp);

      (Void) SPutSMem(szCb.init.region, szCb.init.pool);
   
      status->status = LCM_PRIM_NOK;
      status->reason = LSZ_REASON_HASHINIT_FAIL;
      RETVALUE (ret);
   }
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

   (Void) cmMemcpy((U8 *)&szCb.init.lmPst, (U8 *) &gen->lmPst,
                   (PTR)sizeof(Pst));

   szCb.init.lmPst.srcProcId = szCb.init.procId;
   szCb.init.lmPst.srcEnt    = szCb.init.ent;
   szCb.init.lmPst.srcInst   = szCb.init.inst;
   szCb.init.lmPst.event     = EVTNONE;

   szCb.init.cfgDone = TRUE;

   /* Reset the shutdown flag */
   szCb.shutdown = FALSE;

   RETVALUE(ROK);

} /* szGenCfg */

/*
 *
 *      Fun:   szValidateGenCfg
 *
 *      Desc:  Validates the S1AP general configuration. 
 *
 *      Ret:   LCM_REASON_NOT_APPL - ok
 *             LCM_REASON_INVALID_PAR_VAL - failure
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szValidateGenCfg
(
SzGenCfg *gen        /* General configuration */
)
#else
PRIVATE S16 szValidateGenCfg(gen)
SzGenCfg *gen;       /* General configuration */
#endif
{
   TRC2(szValidateGenCfg);

   if (gen->nmbSctSaps <= 0)
   {
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if (gen->nmbSztSaps <= 0)
   {
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if (gen->nmbPeer == 0)
   {
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if (gen->nmbConn == 0)
   {
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if (gen->timeRes <= 0)
   {
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }


   RETVALUE(LCM_REASON_NOT_APPL);

} /* szValidateGenCfg */

/******************************************************************************/
/*                   Protocol Configuration Support Functions                 */
/******************************************************************************/
/*
 *
 *      Fun:   szProtCfg
 *
 *      Desc:  Stores the S1AP protocol configuration. 
 *             
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szProtCfg
(
SzProtCfg *prot,     /* Protocol configuration */
CmStatus *status     /* Return status */
)
#else
PRIVATE S16 szProtCfg(prot, status)
SzProtCfg *prot;     /* Protocol configuration */
CmStatus *status;    /* Return status */
#endif
{
   S16 ret;

   TRC2(szProtCfg);

   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

#ifdef SS_DIAG
  /* sz008.301 : Change for Diagnostics */
  SZ_DIAG_LVL0(0x03090001, SZ_DIAG_NA, SS_DIAG_INV_ARG,
        "In the prot configuration %d", 1, 0, 0, 0);
#endif
   /* Validate the protocol configuration elements */
   ret = szValidateProtCfg(prot);

   if (ret != LCM_REASON_NOT_APPL)
   {
      status->status = LCM_PRIM_NOK;
      status->reason = ret;
      RETVALUE(RFAILED);
   }

   if (szCb.nodeCb.cfgDone == TRUE)
   {
      /* Reconfiguration */
      cmMemset((U8 *)&szCb.nodeCb.protCfg,0,sizeof(SzProtCfg));
      cmMemcpy ((U8 *)&szCb.nodeCb.protCfg, (U8 *)prot, sizeof (SzProtCfg));
         
      RETVALUE(ROK);
   } 

   cmMemset((U8 *)&szCb.nodeCb.protCfg,0,sizeof(SzProtCfg));
   cmMemcpy ((U8 *)&szCb.nodeCb.protCfg, (U8 *)prot, sizeof (SzProtCfg));

#ifndef LSZV1   
   szCb.nodeCb.nodeAddr = prot->srcAddr;
#endif /* LSZV1 */

   szCb.nodeCb.nodeType = prot->nodeType;
   szCb.nodeCb.cfgDone = TRUE;

   switch(szCb.nodeCb.nodeType)
   {
#ifdef SZ_ENB
      case LSZ_NODE_ENB:
         cmMemcpy(szCb.nodeDbg, (CONSTANT U8*)"S1AP: eNB", SZ_DBGSIZE);
         break;
#endif /* SZ_ENB */
#ifdef LSZV1
      case LSZ_NODE_GW:
         cmMemcpy(szCb.nodeDbg, (CONSTANT U8*)"S1AP: GW ", SZ_DBGSIZE);
         break;
#endif /* LSZV1 */
      default:
         cmMemcpy(szCb.nodeDbg, (CONSTANT U8*)"S1AP:    ", SZ_DBGSIZE);
         break;
   }

   /* sz003.301: Added hooks for PSF-S1AP */
   /* Add mapping for SCT SAP CB */
#ifdef YT
   YT_ADD_MAPPING(YT_UPD_NODE_CB, &szCb.nodeCb);
#endif /* YT */

   RETVALUE(ROK);

} /* szProtCfg */

/*
 *
 *      Fun:   szValidateProtCfg
 *
 *      Desc:  Validates the S1AP protocol configuration. 
 *
 *      Ret:   LCM_REASON_NOT_APPL - ok
 *             LCM_REASON_INVALID_PAR_VAL - failure
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szValidateProtCfg
(
SzProtCfg *prot      /* Protocol configuration */
)
#else
PRIVATE S16 szValidateProtCfg(prot)
SzProtCfg *prot;     /* Protocol configuration */
#endif
{

   TRC2(szValidateProtCfg);

   if ((prot->nodeType != LSZ_NODE_ENB) && (prot->nodeType != LSZ_NODE_MME) &&
       (prot->nodeType != LSZ_NODE_GW))
   {
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }


   RETVALUE(LCM_REASON_NOT_APPL); 

} /* szValidateProtCfg */

/******************************************************************************/
/*                   SZT SAP Configuration Support Functions                  */
/******************************************************************************/
/*
 *
 *      Fun:   szSztSapCfg
 *
 *      Desc:  Stores the S1AP upper SAP configuration. 
 *
 *      Ret:   ROK     - ok
 *             RFAILED - failure
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szSztSapCfg
(
SzSztSapCfg *sztSap,     /* Upper SAP configuration */
CmStatus *status         /* Return status */
)
#else
PRIVATE S16 szSztSapCfg(sztSap, status)
SzSztSapCfg *sztSap;     /* Upper SAP configuration */
CmStatus *status;        /* Return status */
#endif
{
   S16   ret;
   U16  offset;
   SzSztSapCb    *sztSapCb;
   SzConCb conCb;

   TRC2(szSztSapCfg);

   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

   /* Validate SZT SAP configuration elements */
   ret = szValidateSztSapCfg(sztSap);

   if (ret != LCM_REASON_NOT_APPL)
   {
      status->status = LCM_PRIM_NOK;
      status->reason = ret;
      RETVALUE(RFAILED);
   }


   /* Get Sap control block */
   sztSapCb = szCb.sztSapLst[sztSap->spId];

   if (sztSapCb != NULLP)
   {
      /* Reconfiguration */
      sztSapCb->pst.selector  = sztSap->selector;
      sztSapCb->pst.prior     = sztSap->priority;
      sztSapCb->pst.region    = sztSap->mem.region;
      sztSapCb->pst.pool      = sztSap->mem.pool;

      RETVALUE(ROK);
   }
   
   /* Allocate SAP Control Block */
   SZ_ALLOC(sztSapCb ,sizeof(SzSztSapCb)); 
   if (sztSapCb == NULLP)
   {
      status->status = LCM_PRIM_NOK;
      status->reason = LCM_REASON_MEM_NOAVAIL;
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)sztSapCb,0,sizeof(SzSztSapCb));

   /* Initialize the elements of SzSztSapCb */
   sztSapCb->suId = 0;
#ifdef SS_MULTIPLE_PROCS
   sztSapCb->pst.srcProcId = szCb.init.procId;
#else
   sztSapCb->pst.srcProcId = SFndProcId();
#endif
   sztSapCb->pst.srcEnt = szCb.init.ent;
   sztSapCb->pst.srcInst = szCb.init.inst;
   sztSapCb->pst.prior = sztSap->priority;
   sztSapCb->pst.route = sztSap->route;
   sztSapCb->pst.region = sztSap->mem.region;
   sztSapCb->pst.pool = sztSap->mem.pool;
   sztSapCb->pst.selector = sztSap->selector;
   sztSapCb->state = LSZ_SAP_CFG;
   sztSapCb->spId  = sztSap->spId;

   /* 
    * Initialize the Hashlist of connections
    * based on SuConnId 
    */
   offset = (U16)((PTR)&conCb.suConHlEnt - (PTR)&conCb);
   ret = cmHashListInit(&sztSapCb->suConnLst,  /* hash list Cp */
            (U16)szCb.genCfg.nmbConn,                /* HL bins */
            offset,                             /* Offset of HL Entry */
            FALSE,                              /* Allow dup. keys ? */
            SZ_HASH_KEYTYPE,                    /* HL key type */
            szCb.init.region,                   /* Mem region for HL */
            szCb.init.pool);                    /* Mem pool for HL */

#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
   {
      SZ_FREE (sztSapCb ,sizeof(SzSztSapCb)); 
      status->status = LCM_PRIM_NOK;
      status->reason = LSZ_REASON_HASHINIT_FAIL;
      RETVALUE (ret);
   }
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

   /* Place sztSapCb in szCb's SztSap list */
   szCb.sztSapLst[sztSap->spId] = sztSapCb;

   /* sz003.301: Added hooks for PSF-S1AP */
   /* Add mapping for SZT SAP CB */
#ifdef YT
   YT_ADD_MAPPING(YT_UPD_SZT_SAP_CB, sztSapCb);
#endif /* YT */

   RETVALUE(ROK);

} /* szSztSapCfg */

/*
 *
 *      Fun:   szValidateSztSapCfg
 *
 *      Desc:  Validates the S1AP SZT SAP configuration. 
 *
 *      Ret:   ROK     - ok
 *             RFAILED - failure
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szValidateSztSapCfg
(
SzSztSapCfg *sztSap      /* Upper SAP configuration */
)
#else
PRIVATE S16 szValidateSztSapCfg(sztSap)
SzSztSapCfg *sztSap;     /* Upper SAP configuration */
#endif
{
   TRC2(szValidateSztSapCfg);

   if (szCb.nodeCb.cfgDone != TRUE)
   {
      RETVALUE(LSZ_REASON_PROTCFG_NOT_DONE);
   }

   if ( (sztSap->spId <  0) || (sztSap->spId >= szCb.genCfg.nmbSztSaps) )
   {
      RETVALUE(LCM_REASON_EXCEED_CONF_VAL);
   }

   RETVALUE(LCM_REASON_NOT_APPL);

} /* szValidateSztSapCfg */

/******************************************************************************/
/*                   SCT SAP Configuration Support Functions                 */
/******************************************************************************/
/*
 *
 *      Fun:   szSctSapCfg
 *
 *      Desc:  Stores the S1AP lower SAP configuration. 
 *
 *      Ret:   ROK   - ok
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szSctSapCfg
(
SzSctSapCfg *sctSap,     /* lower SAP configuration */
CmStatus *status         /* Return status */
)
#else
PRIVATE S16 szSctSapCfg(sctSap, status)
SzSctSapCfg *sctSap;     /* lower SAP configuration */
CmStatus *status;        /* Return status */
#endif
{
   S16      ret;
   SzSctSapCb *sctSapCb;

   TRC2(szSctSapCfg);

   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

   /* Validate the protocol parameters */
   ret = szValidateSctSapCfg(sctSap);

   if (ret != LCM_REASON_NOT_APPL)
   {
      status->status = LCM_PRIM_NOK;
      status->reason = ret;
      RETVALUE(RFAILED);
   }

   /* Get Sap control block */
   sctSapCb = szCb.sctSapLst[sctSap->suId];

   if (sctSapCb != NULLP)
   {
      /* Reconfiguration */
      sctSapCb->pst.prior = sctSap->priority;
      sctSapCb->pst.region = sctSap->mem.region;
      sctSapCb->pst.pool = sctSap->mem.pool;
      sctSapCb->maxBndRetry  = sctSap->maxBndRetry;

      RETVALUE(ROK);
   }

   /* Allocate SAP Control Block */
   SZ_ALLOC(sctSapCb, sizeof(SzSctSapCb));
   if (sctSapCb == NULLP)
   {
      status->status = LCM_PRIM_NOK;
      status->reason = LCM_REASON_MEM_NOAVAIL;
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)sctSapCb,0,sizeof(SzSctSapCb));

   /* Initialize the elements of SzSctSapCb */
   sctSapCb->suId = sctSap->suId;
   sctSapCb->spId = sctSap->spId;

   sctSapCb->pst.selector = sctSap->selector;
   sctSapCb->pst.region = sctSap->mem.region;
   sctSapCb->pst.pool = sctSap->mem.pool;
   sctSapCb->pst.prior = sctSap->priority;
   sctSapCb->pst.route = sctSap->route;
#ifdef SS_MULTIPLE_PROCS
   sctSapCb->pst.srcProcId = szCb.init.procId;
#else /* SS_MULTIPLE_PROCS */
   sctSapCb->pst.srcProcId = SFndProcId();
#endif /* SS_MULTIPLE_PROCS */

   /* sz003.301: procId will be set to zero in case of the PSF is enabled */
#ifdef YT
   if (ytCb.cmPsfCb.init.cfgDone)
   {
      sctSapCb->pst.srcProcId = CMFTHA_RES_RSETID;
   }
#endif /* YT */
   sctSapCb->pst.srcEnt = szCb.init.ent;
   sctSapCb->pst.srcInst = szCb.init.inst;
   sctSapCb->pst.dstProcId = sctSap->dstProcId;
   sctSapCb->pst.dstEnt = sctSap->dstEntId;
   sctSapCb->pst.dstInst = sctSap->dstInstId;
   cmMemcpy ((U8 *)&sctSapCb->tBndTmr, (U8 *)&sctSap->tBndTmr, sizeof(TmrCfg));
   sctSapCb->maxBndRetry  = sctSap->maxBndRetry;
   sctSapCb->trcMask = 0;
   sctSapCb->trcLen = 0;
   sctSapCb->retryCnt = 0;
   cmInitTimers(sctSapCb->timers, SZ_MAX_SCTSAP_TMRS);

   /* sz003.301: contEnt will be set to ENTNC in case of the PSF is enabled */
#ifdef SZ_FTHA
   sctSapCb->contEnt = ENTNC;
#else
   sctSapCb->contEnt = ENTSM;
#endif

   sctSapCb->endpCfgDone = FALSE;
   sctSapCb->state = LSZ_SAP_CFG;

   /* Update EndpCb with srcAddrLst and port */
   if (sctSapCb->endpCfgDone != TRUE)
   {
#ifndef LSZV1
      sctSapCb->endpCb.port = szCb.nodeCb.protCfg.srcAddr.sctPort;
      cmMemcpy((U8 *)&(sctSapCb->endpCb.srcAddrLst),
         (U8 *)&(szCb.nodeCb.protCfg.srcAddr.ipAddr), sizeof(SctNetAddrLst));
#else
      sctSapCb->endpCb.port = sctSap->srcAddr.sctPort;
      cmMemcpy((U8 *)&(sctSapCb->endpCb.srcAddrLst),
            (U8 *)&(sctSap->srcAddr.ipAddr), sizeof(SctNetAddrLst));
#endif /* LSZV1 */

      sctSapCb->endpCb.epState = SZ_ENDP_CFG;
      sctSapCb->endpCfgDone = TRUE;
   }

   /* Place sctSapCb in SzCb's SctSap list */
   szCb.sctSapLst[sctSap->suId] = sctSapCb;

   /* sz003.301: Added hooks for PSF-S1AP */
   /* Add mapping for SCT SAP CB */
#ifdef YT
   YT_ADD_MAPPING(YT_UPD_SCT_SAP_CB, sctSapCb);
   YT_ADD_MAPPING(YT_UPD_ENDP_CB, &sctSapCb->endpCb);
#endif /* YT */

   RETVALUE(ROK);

} /* szSctSapCfg */

/*
 *
 *      Fun:   szValidateSctSapCfg
 *
 *      Desc:  Validates the S1AP lower SAP configuration. 
 *
 *      Ret:   ROK   - ok
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szValidateSctSapCfg
(
SzSctSapCfg *sctSap      /* Lower SAP configuration */
)
#else
PRIVATE S16 szValidateSctSapCfg(sctSap)
SzSctSapCfg *sctSap;     /* Lower SAP configuration */
#endif
{
   TRC2(szValidateSctSapCfg);

   if (szCb.nodeCb.cfgDone != TRUE)
   {
      RETVALUE(LSZ_REASON_PROTCFG_NOT_DONE);
   }

   if (sctSap->suId >= szCb.genCfg.nmbSctSaps)
   {
      RETVALUE(LCM_REASON_EXCEED_CONF_VAL);
   }
   /* Range checking for timer */
   if ((sctSap->tBndTmr.val <= 0) ||
       (sctSap->tBndTmr.enb == FALSE))
   {
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   RETVALUE(LCM_REASON_NOT_APPL);

} /* end of szValidateSctSapCfg */

/******************************************************************************/
/*                   Peer Configuration Support Functions                     */
/******************************************************************************/
/*
 *
 *      Fun:   szPeerCfg
 *
 *      Desc:  Stores the S1AP p configuration. 
 *             
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szPeerCfg
(
SzPeerCfg *peer,     /* Peer configuration */
CmStatus  *status,   /* Return status */
Header    *hdr       /* Header information */
)
#else
PRIVATE S16 szPeerCfg(peer, status, hdr)
SzPeerCfg *peer;     /* Peer configuration */
CmStatus  *status;   /* Return status */
Header    *hdr;      /* Header information */
#endif
{
   S16 ret;             /* return value */
   SzPeerCb *peerCb;    /* Peer control block */
   U32 loopCnt;               /* index */
   SzUstaDgn  dgn;      /* unsolicited status diagnostics structure */

   TRC2(szPeerCfg);

   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;
   
   peerCb = NULLP;

   /* Validate the peer configuration elements */
   ret = szValidatePeerCfg(peer);

   if (ret != LCM_REASON_NOT_APPL)
   {
      if(peer->nmbPeers)
      {
         SZ_FREE_STA(peer->peerInfo, (sizeof(SzPeerInfo) * peer->nmbPeers),
                     hdr->response.mem.region, hdr->response.mem.pool);
      }
      status->status = LCM_PRIM_NOK;
      status->reason = ret;
      RETVALUE(RFAILED);
   }

   for (loopCnt = 0; loopCnt < peer->nmbPeers;loopCnt++)
   {
      /* Get Peer control block */
      ret = szNdbChkPeer(peer->peerInfo[loopCnt].peerId, &peerCb);

      if (peerCb != NULLP)
      {
         /* Reconfiguration */
         if (peer->peerInfo[loopCnt].assocCfg.locOutStrms < 2)
         {
#if (ERRCLASS & ERRCLS_INT_PAR)
            SZLOGERROR(ERRCLS_INT_PAR, ESZ093, (ErrVal)peerCb->peerId,
                  "szPeerCfg, Atleast 2 streams should be configured");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

            dgn.type    = LSZ_USTA_DGNVAL_PEER;
            dgn.u.sapId = (S16) peerCb->peerId;

            szSendLmAlarm(LCM_CATEGORY_PROTOCOL, LCM_EVENT_LYR_SPECIFIC, 
                  LCM_CAUSE_LYR_SPECIFIC, &dgn);

            ret = RFAILED;
         }

         cmMemcpy ((U8 *)peerCb->assocCb->assocCfg, 
               (U8 *)&peer->peerInfo[loopCnt].assocCfg, sizeof (SzAssocCfg));

         ret = ROK;
         continue;
      }

      /* Allocate Peer Control Block */
      if ((ret = szNdbAllocPeerCb(peer->peerInfo[loopCnt].peerId.val, &peerCb)) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SZLOGERROR(ERRCLS_DEBUG, ESZ094, ERRZERO,
               "szPeerCfg, Failed to allocate the peer");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */
         status->status = LCM_PRIM_NOK;
         status->reason = ret;

         SZ_FREE_STA(peer->peerInfo, (sizeof(SzPeerInfo) * peer->nmbPeers),
                     hdr->response.mem.region, hdr->response.mem.pool);
         peer->peerInfo = NULLP;

         RETVALUE(RFAILED);
      }

      ret = szNdbFillPeerAssocParams(peerCb, &peer->peerInfo[loopCnt].assocCfg);
      if (ret != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SZLOGERROR(ERRCLS_DEBUG, ESZ095, ERRZERO,
               "szPeerCfg, Failed to allocate the peer");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */
         status->status = LCM_PRIM_NOK;
         status->reason = ret;

         SZ_FREE_STA(peer->peerInfo, (sizeof(SzPeerInfo) * peer->nmbPeers),
                     hdr->response.mem.region, hdr->response.mem.pool);
         peer->peerInfo = NULLP;

         RETVALUE(RFAILED);
      }

      peerCb->peerId   = peer->peerInfo[loopCnt].peerId.val;
      peerCb->state    = SZT_ND_ST_IDLE;
      peerCb->sctSapCb = szCb.sctSapLst[peer->peerInfo[loopCnt].sapId]; 
      peerCb->setupReq = NULLP;
      peerCb->resetPdu = NULLP;
      peerCb->sztSapCb = szCb.sztSapLst[peer->peerInfo[loopCnt].uSapId]; 

      /* Store the peer node type */
      peerCb->nodeType = peer->peerInfo[loopCnt].type;

      if (peer->peerInfo[loopCnt].assocCfg.comProcStrm.pres)
      {
         peerCb->comStreamId = peer->peerInfo[loopCnt].assocCfg.comProcStrm.val;
      }
      else
      {
         peerCb->comStreamId = 0;
      }
      peerCb->trcMask = 0;
      peerCb->trcLen = 0;

      /* sz002.301: Update the suAssocId */
      peerCb->assocCb->suAssocId = peerCb->peerId;

#ifdef LSZV1
      peerCb->skipUeSm =  peer->peerInfo[loopCnt].skipUeSm;
#endif /* LSZV1 */

   /* sz003.301: Added hooks for PSF-S1AP */
    /* Add mapping for PeerCb and AssocCb */
#ifdef YT
   YT_ADD_MAPPING(YT_UPD_PEER_CB, peerCb);
   YT_ADD_MAPPING(YT_UPD_ASSOC_CB, peerCb->assocCb);
#endif /* YT */
   }

   /* Free the memory for peerInfo */
   SZ_FREE_STA(peer->peerInfo, (sizeof(SzPeerInfo) * peer->nmbPeers),
               hdr->response.mem.region, hdr->response.mem.pool);
   peer->peerInfo = NULLP;

   RETVALUE(ret);

} /* szPeerCfg */

/*
 *
 *      Fun:   szValidatePeerCfg
 *
 *      Desc:  Validates the S1AP Peer configuration. 
 *
 *      Ret:   ROK     - ok
 *             RFAILED - failure
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szValidatePeerCfg
(
SzPeerCfg *peer      /* Peer configuration */
)
#else
PRIVATE S16 szValidatePeerCfg(peer)
SzPeerCfg *peer;     /* Peer configuration */
#endif
{
   SzAssocCfg *assocCfg;
   U32 loopCnt;

   TRC2(szValidatePeerCfg);

   if (szCb.nodeCb.cfgDone != TRUE)
   {
      RETVALUE(LSZ_REASON_PROTCFG_NOT_DONE);
   }

   /* sz002.201 Correction made in peer config validation */
   if ((peer->nmbPeers == 0) || (peer->nmbPeers > szCb.genCfg.nmbPeer) ||
       (szCb.genSta.nmbPeer >= szCb.genCfg.nmbPeer) ||
       ((szCb.genSta.nmbPeer + peer->nmbPeers) > szCb.genCfg.nmbPeer))
   {
      RETVALUE(LCM_REASON_EXCEED_CONF_VAL);       
   }

   for (loopCnt = 0; loopCnt < peer->nmbPeers; loopCnt++)
   {
      if ( (peer->peerInfo[loopCnt].sapId <  0) || 
           (peer->peerInfo[loopCnt].uSapId <  0) || 
           (peer->peerInfo[loopCnt].sapId >= szCb.genCfg.nmbSctSaps) ||
           (peer->peerInfo[loopCnt].uSapId >= szCb.genCfg.nmbSztSaps) )
      {
         RETVALUE(LCM_REASON_EXCEED_CONF_VAL);
      }
     
      if ( (szCb.sctSapLst[peer->peerInfo[loopCnt].sapId] == NULLP) ||
           (szCb.sztSapLst[peer->peerInfo[loopCnt].uSapId] == NULLP) )
      {
         RETVALUE(LSZ_REASON_LSAPCFG_NOT_DONE);         
      }

      if ( ((peer->peerInfo[loopCnt].type != LSZ_NODE_ENB) &&
           (peer->peerInfo[loopCnt].type != LSZ_NODE_MME )) ||
           (peer->peerInfo[loopCnt].type == szCb.nodeCb.protCfg.nodeType))
      {
         RETVALUE(LCM_REASON_INVALID_PAR_VAL);
      }

      if (szCb.nodeCb.nodeType == peer->peerInfo[loopCnt].type )
      {
         RETVALUE(LCM_REASON_INVALID_PAR_VAL);
      }

      /* validate stream id for common procedures */ 
      assocCfg = &(peer->peerInfo[loopCnt].assocCfg);

      if ((assocCfg->comProcStrm.pres) &&
          (assocCfg->comProcStrm.val != 0) &&
          (assocCfg->comProcStrm.val != (assocCfg->locOutStrms - 1)))
      {
         RETVALUE(LCM_REASON_INVALID_PAR_VAL);
      }

#ifdef LSZV1
      if((peer->peerInfo[loopCnt].skipUeSm != TRUE) &&
         (peer->peerInfo[loopCnt].skipUeSm != FALSE))
      {
         RETVALUE(LCM_REASON_INVALID_PAR_VAL);
      }
#endif /* LSZV1 */
   }

   RETVALUE(LCM_REASON_NOT_APPL);

} /* szValidatePeerCfg */

/******************************************************************************/
/*                   Control Request Support Functions                        */
/******************************************************************************/

/******************************************************************************/
/*                   General Control Support Functions                        */
/******************************************************************************/
/*
 *
 *      Fun:   szGenCntrl
 *
 *      Desc:  Process the general control request
 *
 *      Ret:   ROK     - ok
 *             RFAILED - failure
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szGenCntrl
(
SzCntrl *cntrl,         /* Control structure */
CmStatus *status        /* Return status */
)
#else
PRIVATE S16 szGenCntrl(cntrl, status)
SzCntrl *cntrl;          /* Control structure */
CmStatus *status;        /* Return status */
#endif
{
   S16   ret;

   TRC2(szGenCntrl);

   status->status = LCM_PRIM_NOK;

   switch (cntrl->action)
   {
      case AENA:
      {
         switch (cntrl->subAction)
         {
#ifdef DEBUGP
            case SADBG:
            {
               szCb.init.dbgMask |= cntrl->u.dbg.dbgMask;
               break;
            }
#endif /* DEBUGP */
            case SAUSTA: 
            {
               szCb.init.usta = TRUE;

               /* sz003.301: Added hooks for PSF-S1AP */
               /* Update the status indication enable to peer */
#ifdef YT
               YT_RTUPD_MOD(YT_UPD_GLOB_CB, &szCb);
#endif /* YT */
               break;
            }
#ifdef SS_DIAG
            /* sz008.301 : Change for Diagnostics */
            case SALOG:
            {
               szCb.init.logMask = cntrl->u.logMask;
               break;
            }
#endif
            default:
            {
               status->reason = LCM_REASON_INVALID_SUBACTION;
               RETVALUE(RFAILED);
            }
         }
         break;
      }
      case ADISIMM:
      {
         switch (cntrl->subAction)
         {
#ifdef DEBUGP
            case SADBG:
            {
               szCb.init.dbgMask &= ~(cntrl->u.dbg.dbgMask);
               break;
            }
#endif /* DEBUGP */
            case SAUSTA:
            {
               szCb.init.usta = FALSE;
               /* sz003.301: Added hooks for PSF-S1AP */
               /* Update the status indication enable to peer */
#ifdef YT
               YT_RTUPD_MOD(YT_UPD_GLOB_CB, &szCb);
#endif /* YT */
               break;
            }
#ifdef SS_DIAG
            /* sz008.301 : Change for Diagnostics */
            case SALOG:
            {
               szCb.init.logMask = cntrl->u.logMask;
               break;
            }
#endif
            default:
            {
               status->reason = LCM_REASON_INVALID_SUBACTION;
               RETVALUE(RFAILED);
            }
         }
         break;
      }
      case ASHUTDOWN:
      {
         if ( (ret = szShutdown()) != ROK)
         {
            status->reason = ret;
            RETVALUE(RFAILED);
         } 
         break;
      }
      default:
      {
         status->reason = LCM_REASON_INVALID_ACTION; 
         RETVALUE(RFAILED);
      }
   } 

   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

   RETVALUE(ROK);

} /* szGenCntrl */

/*
 *
 *      Fun:   szShutdown
 *
 *      Desc:  Shutdown the S1AP layer
 *
 *      Ret:   ROK     - ok
 *             RFAILED - failure
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PUBLIC S16 szShutdown
(
Void
)
#else
PUBLIC S16 szShutdown()
#endif
{
   S16 loopCnt;
   SzPeerCb *peerCb = NULLP;
   SzPeerCb *prev   = NULLP;

   TRC2(szShutdown);

   if (szCb.init.cfgDone != TRUE)
   {
	   RETVALUE(ROK);
   }

    /* Check if previous shutdown request is pending */ 
   if (szCb.shutdown)
   {
#ifdef DEBUGP
      SZDBGP(DBGMASK_MI, (szCb.init.prntBuf,
               "szShutdown: Layer already SHUT DOWN) \n"));
#endif
      RETVALUE (ROK);
   }

   szCb.shutdown  = TRUE;

   /* Deregister the timers */
#ifdef SS_MULTIPLE_PROCS
   SDeregTmr(szCb.init.procId,szCb.init.ent, szCb.init.inst, (S16)szCb.genCfg.timeRes,
         (PAIFTMRS16)szActvTmr);
#else
   SDeregTmr(szCb.init.ent, szCb.init.inst, (S16)szCb.genCfg.timeRes,
         (PFS16)szActvTmr);
#endif

    /* Remove SCT Sap Cb */
   for (loopCnt = 0; loopCnt < szCb.genCfg.nmbSctSaps; loopCnt++)
   {
      if (szCb.sctSapLst[loopCnt] != (SzSctSapCb *)NULLP)
      {
/* sz005.301 Modified for sctsap insertion and deletion id mismatch */
         szDelSctSap(szCb.sctSapLst[loopCnt]->suId,SZ_SHUT_DOWN);
      }
   }

   /* Remove SZT Sap Cb */   
   for (loopCnt = 0; loopCnt < szCb.genCfg.nmbSztSaps; loopCnt++)
   {
      if (szCb.sztSapLst[loopCnt] != (SzSztSapCb *)NULLP)
      {
         szDelSztSap(szCb.sztSapLst[loopCnt]->spId, SZ_SHUT_DOWN);
      }
   }

   if (szCb.sztSapLst != (SzSztSapCb **)NULLP)
   {
      SZ_FREE(szCb.sztSapLst, (szCb.genCfg.nmbSztSaps * sizeof(SzSztSapCb *)));
   }

   if (szCb.sctSapLst != (SzSctSapCb **)NULLP)
   {
      SZ_FREE(szCb.sctSapLst, (szCb.genCfg.nmbSctSaps * sizeof(SzSctSapCb *)));
   }

   /* Deallocate peerCbs */
   while (cmHashListGetNext(&szCb.peerLst,
            (PTR)prev,
            (PTR *)&peerCb) == ROK)
   {
      (Void)szNdbDeallocPeerCb(peerCb);
      prev = NULLP;
      peerCb = NULLP;
   }

   /* Reset all S1AP control blocks and system parameters */

   /* DeInit the hashlists in SzCb */ 
   cmHashListDeinit(&szCb.peerLst);
   /* sz002.201 Added peer hashlist for performance */
   cmHashListDeinit(&szCb.peerAddrPortLst);
   cmHashListDeinit(&szCb.lclConCp);

   szCb.nodeCb.cfgDone = FALSE;

   /* call szActvInit with reason SHUTDOWN to de-initialize the szCb */

#ifdef SS_MULTIPLE_PROCS
   szActvInit (szCb.init.procId, szCb.init.ent, szCb.init.inst,
               szCb.init.region, SHUTDOWN , (Void **) NULLP);
#else
   szActvInit (szCb.init.ent, szCb.init.inst,
               szCb.init.region, SHUTDOWN);
#endif

   RETVALUE(ROK);

} /* szShutdown */


/******************************************************************************/
/*                   SZT SAP  Control Support Functions                       */
/******************************************************************************/
/*
 *
 *      Fun:   szSztSapCntrl
 *
 *      Desc:  Process the upper SAP control request
 *
 *      Ret:   ROK     - ok
 *             RFAILED - failure
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szSztSapCntrl
(
SzCntrl *cntrl,         /* Control structure */
CmStatus *status        /* Return status */
)
#else
PRIVATE S16 szSztSapCntrl(cntrl, status)
SzCntrl *cntrl;          /* Control structure */
CmStatus *status;        /* Return status */
#endif
{
   S16 ret;

   TRC2(szSztSapCntrl);

   ret = szValidateSztSapCntrl (cntrl);

   if (ret != LCM_REASON_NOT_APPL)
   {
      status->status = LCM_PRIM_NOK;
      status->reason = ret;
      RETVALUE(RFAILED);
   }

   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

   switch (cntrl->action)
   {
      case AUBND_DIS:
      {
         if ((ret = szUbndSztSap (cntrl->u.sap.id, SZ_UBND_SAP)) != ROK)
         {
#if (ERRCLASS & ERRCLS_ADD_RES)
            SZLOGERROR(ERRCLS_DEBUG, ESZ096, ERRZERO,
                       "szSztSapCntrl, Failed to unbind and disable the SZT SAP");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */
            RETVALUE(ret);

         }
         break;
      }
      case ADEL:
      {
         if ((ret = szDelSztSap (cntrl->u.sap.id,SZ_DEL_SAP)) != ROK)
         {
#if (ERRCLASS & ERRCLS_ADD_RES)
            SZLOGERROR(ERRCLS_DEBUG, ESZ097, ERRZERO,
                       "szSztSapCntrl, Couldn't delete the SZT SAP");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */
            RETVALUE(ret);
         }
         break;
      }
      default:
      {
         break;
      }
   } 

   RETVALUE(ROK);

} /* szSztSapCntrl */

/*
 *
 *      Fun:   szValidateSztSapCntrl
 *
 *      Desc:  Validates the S1AP SZT SAP control parameters. 
 *
 *      Ret:   ROK     - ok
 *             RFAILED - failure
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szValidateSztSapCntrl
(
SzCntrl  *cntrl         /* general control structure */
)
#else
PRIVATE S16 szValidateSztSapCntrl(cntrl)
SzCntrl  *cntrl;        /* general control structure */
#endif
{
   S16 ret = LCM_REASON_NOT_APPL;

   SzSztSapCb *sztSapCb = NULLP;

   TRC2(szValidateSztSapCntrl);

   switch (cntrl->action)
   {
      case AUBND_DIS:
      case ADEL:
      {
         if (cntrl->u.sap.id < szCb.genCfg.nmbSztSaps)
         {
            sztSapCb = szCb.sztSapLst[cntrl->u.sap.id]; 
            if (sztSapCb == NULLP)
            {
               ret = LCM_REASON_INVALID_PAR_VAL;  
            }
         }
         else
         {
            ret = LCM_REASON_INVALID_PAR_VAL;
         }
         break;
      }
      default:
      {
         ret = LCM_REASON_INVALID_ACTION;
         break;
      }
   }

   RETVALUE(ret);

} /* szValidateSztSapCntrl */

/*
 *
 *      Fun:   szUbndSztSap
 *
 *      Desc:  Unbind and disable the SZT SAP 
 *
 *      Ret:   ROK     - ok
 *             RFAILED - failure
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PUBLIC S16 szUbndSztSap
(
SpId  sapId,         /* SAP Id */
U8    opn        /* Delete Peer CB or not */
)
#else
PUBLIC S16 szUbndSztSap(sapId,opn)
SpId  sapId;        /* SAP Id */
U8    opn;       /* Delete Peer CB or not */
#endif
{
   S16 ret = ROK;
   SzSztSapCb *sztSapCb;

   TRC2(szUbndSztSap);
  
   /* Remove all S1 connections associated with this SAP */
   ret = szNdbDeallocAllPeerCb(sapId,SZ_UI, opn);

   sztSapCb = szCb.sztSapLst[sapId];
   sztSapCb->state = LSZ_SAP_CFG;
   
   /* sz003.301: Added hooks for PSF-S1AP */
   /* Send runtime update for SZT SAP state updation */
#ifdef YT
   YT_RTUPD_MOD(YT_UPD_SZT_SAP_CB, sztSapCb);
#endif /* YT */

   RETVALUE(ret);

} /* szUbndSztSap */

/* sz003.301: Made the function as PUBLIC as it is used by PSF */
/*
 *
 *      Fun:   szDelSztSap
 *
 *      Desc:  Delete the SZT SAP
 *
 *      Ret:   ROK     - ok
 *             RFAILED - failure
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PUBLIC S16 szDelSztSap
(
SpId  sapId,         /* SAP Id */
U8    opn
)
#else
PUBLIC S16 szDelSztSap(sapId,opn)
SpId  sapId;        /* SAP Id */
U8    opn;        /* SAP Id */
#endif
{
   S16 ret = ROK; 
   SzSztSapCb  *uSapCb;
   SzPeerCb *prev = NULLP;
   SzPeerCb *peer = NULLP; 
   TRC2(szDelSztSap);

   uSapCb = szCb.sztSapLst[sapId];

   /* sz008.301: kwork fix: capturing ret value from the 
    * szUbndSztSap funtion. */
   if (uSapCb->state == LSZ_SAP_ISBOUND)
   {
     ret = szUbndSztSap(sapId,opn);
   }

   while (cmHashListGetNext(&szCb.peerLst, (PTR)prev,
            (PTR *)&peer) == ROK)
   {
      if((peer->sztSapCb != NULLP) &&
         (peer->sztSapCb->spId == sapId))
      {
         peer->sztSapCb =  NULLP;
      }
      prev = peer;
   }

   /* sz003.301: Added hooks for PSF-S1AP */
   /* Delete the mapping from the Resouce set */
#ifdef YT
   YT_RTUPD_DEL(YT_UPD_SZT_SAP_CB, uSapCb);
   YT_DEL_MAPPING(YT_UPD_SZT_SAP_CB, uSapCb);
#endif /* YT */

   /* DeInit the hashlists in SzCb */ 
   cmHashListDeinit(&uSapCb->suConnLst);
   SZ_FREE(szCb.sztSapLst[sapId], sizeof(SzSztSapCb)); 

   /* sz008.301: kwork fix: changed return value from ROK to ret. */ 
   RETVALUE(ret);

} /* szDelSztSap */

/******************************************************************************/
/*                   SCT SAP  Control Support Functions                       */
/******************************************************************************/
/*
 *
 *      Fun:   szSctSapCntrl
 *
 *      Desc:  Process the SCT SAP control request
 *
 *      Ret:   ROK     - ok
 *             RFAILED - failure
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szSctSapCntrl
(
SzCntrl *cntrl,         /* Control structure */
CmStatus *status        /* Return status */
)
#else
PRIVATE S16 szSctSapCntrl(cntrl, status)
SzCntrl *cntrl;          /* Control structure */
CmStatus *status;        /* Return status */
#endif
{
   S16 ret;
   SzSctSapCb *sctSapCb;

   TRC2(szSctSapCntrl);

   ret = szValidateSctSapCntrl (cntrl);

   if (ret != LCM_REASON_NOT_APPL)
   {
      status->status = LCM_PRIM_NOK;
      status->reason = ret;
      RETVALUE(RFAILED);
   }

   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

   switch (cntrl->action)
   {
      case AENA:
      {
         /* Enable the trace for sctSap */
         sctSapCb = szCb.sctSapLst[cntrl->u.lSapTrc.lSapId];
         sctSapCb->trcLen = cntrl->u.lSapTrc.trcLen;
         sctSapCb->trcMask |= cntrl->u.lSapTrc.trcMask;
         break; 
      }
      case ADISIMM:
      {
         /* Disable the trace for sctSap */
         sctSapCb = szCb.sctSapLst[cntrl->u.lSapTrc.lSapId];
         sctSapCb->trcLen = cntrl->u.lSapTrc.trcLen;
         sctSapCb->trcMask &= ~(cntrl->u.lSapTrc.trcMask);
         break; 
      } 
      case ABND_ENA:
      {
         if ((ret = szEnaSctSap (cntrl->u.sap.id)) != ROK)
         {
#if (ERRCLASS & ERRCLS_ADD_RES)
            SZLOGERROR(ERRCLS_DEBUG, ESZ098, ERRZERO,
                       "szSctSapCntrl, Failed to bind and enable the SCT SAP");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */
         }
         break; 
      }
      case AUBND_DIS:
      {
         if ((ret = szUbndSctSap (cntrl->u.sap.id,SZ_UBND_SAP, ENTSM)) != ROK)
         {
#if (ERRCLASS & ERRCLS_ADD_RES)
            SZLOGERROR(ERRCLS_DEBUG, ESZ099, ERRZERO,
                       "szSctSapCntrl, Failed to Unbind and disable the SCT SAP");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */
         }
         break;
      }
      case ADEL:
      {
         if ((ret = szDelSctSap (cntrl->u.sap.id, SZ_DEL_SAP)) != ROK)
         {
#if (ERRCLASS & ERRCLS_ADD_RES)
            SZLOGERROR(ERRCLS_DEBUG, ESZ100, ERRZERO,
                       "szSctSapCntrl, Couldn't delete the SCT SAP");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */
            RETVALUE(ret);
         }
         break;
      }
      default:
      {
         break;
      }
   }
   
   RETVALUE(ROK);

} /* szSctSapCntrl */

/*
 *
 *      Fun:   szValidateSctSapCntrl
 *
 *      Desc:  Validates the S1AP's SCT SAP control parameters. 
 *
 *      Ret:   ROK     - ok
 *             RFAILED - failure
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szValidateSctSapCntrl
(
SzCntrl  *cntrl         /* general control structure */
)
#else
PRIVATE S16 szValidateSctSapCntrl(cntrl)
SzCntrl  *cntrl;        /* general control structure */
#endif
{
   S16        ret = LCM_REASON_NOT_APPL; /* Return value */
   SpId       sapId;                     /* Lower SAP Identifier */
   SzSctSapCb *sctSapCb;                 /* SCT Sap control block */

   sctSapCb = NULLP;

   TRC2(szValidateSctSapCntrl);

   switch (cntrl->action)
   {
      case AENA:
      case ADISIMM:
      {
         if (cntrl->subAction == SATRC)
         {
            sapId = cntrl->u.lSapTrc.lSapId; 
         }
         else 
         {
            ret = LCM_REASON_INVALID_SUBACTION;
            RETVALUE(ret);
         }
         break;
      }
      case ADEL:
      case ABND_ENA:
      case AUBND_DIS:
      {
         sapId = cntrl->u.sap.id;
         break;
      }
      default:
      {
         ret = LCM_REASON_INVALID_ACTION;
         RETVALUE(ret);
      }
   }

   if (sapId < szCb.genCfg.nmbSctSaps)
   {
      sctSapCb = szCb.sctSapLst[sapId];
      if (sctSapCb == NULLP)
      { 
         ret = LCM_REASON_INVALID_PAR_VAL;
      }
   }
   else
   {
      ret = LCM_REASON_INVALID_PAR_VAL;
   }

   RETVALUE(ret);

} /* szValidateSctSapCntrl */

/*
 *
 *      Fun:   szEnaSctSap
 *
 *      Desc:  Enable the lower SAP 
 *
 *      Ret:   ROK   - ok
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szEnaSctSap
(
SpId  lSapId         /* SAP Id */
)
#else
PRIVATE S16 szEnaSctSap(lSapId)
SpId  lSapId;        /* SAP Id */
#endif
{
   SzSctSapCb *sctSapCb;

   TRC2(szEnaSctSap);

   sctSapCb = szCb.sctSapLst[lSapId];

   if (sctSapCb->state == LSZ_SAP_ISBOUND || 
       sctSapCb->state == LSZ_SAP_BINDING)
   {
#ifdef DEBUGP        
      SZDBGP(DBGMASK_MI, (szCb.init.prntBuf,
                "szEnaSctSap: SAP is already bound / waiting for bind confirm \n"));
#endif
      RETVALUE(ROK);
   } 

   /* Send Bind Request */

   /* start timer to wait for bind confirm */
   szStartTmr(sctSapCb->timers, (PTR)sctSapCb, SZ_TMR_WAIT_BNDCFM, &sctSapCb->tBndTmr);

   sctSapCb->state = LSZ_SAP_BINDING;
   sctSapCb->contEnt = ENTNC;

   (Void)SzLiSctBndReq(&sctSapCb->pst, sctSapCb->suId, sctSapCb->spId);
   
   RETVALUE(ROK);

} /* szEnaSctSap */

/*
 *
 *      Fun:   szUbndSctSap
 *
 *      Desc:  Unbind and disable the lower SAP 
 *
 *      Ret:   ROK     - ok
 *             RFAILED - failure
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szUbndSctSap
(
SpId  lSapId,        /* SAP Id */
U8    opn,        /* Delete Peer CB or not */
U8    contEnt        /* Controlling Entity */
)
#else
PRIVATE S16 szUbndSctSap(lSapId, opn,contEnt)
SpId  lSapId;        /* SAP Id */
U8    opn;        /* Delete Peer CB or not*/
U8    contEnt;       /* Controlling Entity */
#endif
{
   S16 ret = ROK;
   SzSctSapCb *sctSapCb; 
   
   TRC2(szUbndSctSap);

   sctSapCb = szCb.sctSapLst[lSapId];

   if (sctSapCb->state == LSZ_SAP_UBND ||
       sctSapCb->state == LSZ_SAP_CFG)
   {
#ifdef DEBUGP        
     SZDBGP(DBGMASK_MI, (szCb.init.prntBuf,
                "szUbndSctSap: SAP already unbound \n"));
#endif
      RETVALUE(ROK);
   }

   /* Remove all logical connections associated with this SCT Sap */
   ret = szNdbDeallocAllPeerCb(lSapId,SZ_LI, opn);


   /* Close the endpoint */
   if (sctSapCb->endpCb.epState == SZ_ENDP_OPEN)
   {
      SzLiSctEndpCloseReq(&sctSapCb->pst, sctSapCb->spId, 
                          sctSapCb->endpCb.locSpEndpId, SCT_ENDPID_SP);
   }

   sctSapCb->state = LSZ_SAP_CFG;
  
   /* sz003.301: Added hooks for PSF-S1AP */
   /* Send the runtime update for SCT SAP for state change */
#ifdef YT
   YT_RTUPD_MOD(YT_UPD_SCT_SAP_CB, sctSapCb);
#endif /* YT */

   RETVALUE(ret);

} /* szUbndSctSap */

/* sz003.301: Made the function as PUBLIC as it is used by PSF */
/*
 *
 *      Fun:   szDelSctSap
 *
 *      Desc:  Delete the lower SAP 
 *
 *      Ret:   ROK   - ok
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PUBLIC S16 szDelSctSap
(
SuId  lSapId,  /* SAP Id */
U8    opn
)
#else
PUBLIC S16 szDelSctSap(lSapId,opn)
SuId  lSapId;        /* SAP Id */
U8    opn;
#endif
{

   S16 ret = ROK;
   
   TRC2(szDelSctSap);

   if(szCb.sctSapLst[lSapId]->state == LSZ_SAP_ISBOUND)
   {
      ret = szUbndSctSap (lSapId,opn,ENTSM);
   }

   /* sz003.301: Added hooks for PSF-S1AP */
   /* Delete the SCT SAP mapping from resource set CB */
#ifdef YT
   YT_RTUPD_DEL(YT_UPD_SCT_SAP_CB, szCb.sctSapLst[lSapId]);
   YT_DEL_MAPPING(YT_UPD_SCT_SAP_CB, szCb.sctSapLst[lSapId]);
#endif /* YT */

   SZ_FREE(szCb.sctSapLst[lSapId], sizeof (SzSctSapCb));

   RETVALUE(ret);

} /* szDelSctSap */

/******************************************************************************/
/*                   Peer  Control Support Functions                          */
/******************************************************************************/
/*
 *
 *      Fun:   szPeerCntrl
 *
 *      Desc:  Process the Peer control request
 *
 *      Ret:   ROK     - ok
 *             RFAILED - failure
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szPeerCntrl
(
SzCntrl *cntrl,         /* Control structure */
CmStatus *status        /* Return status */
)
#else
PRIVATE S16 szPeerCntrl(cntrl, status)
SzCntrl *cntrl;          /* Control structure */
CmStatus *status;        /* Return status */
#endif
{
   S16 ret;
   U32 loopCnt;
   SzPeerCb *peerCb;

   TRC2(szPeerCntrl);

   ret = szValidatePeerCntrl (cntrl);

   if (ret != LCM_REASON_NOT_APPL)
   {
      status->status = LCM_PRIM_NOK;
      status->reason = ret;
      RETVALUE(RFAILED);
   }

   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

   switch (cntrl->action)
   {
      case AENA:
      {
         /* Enable the trace for Peer */
         szNdbChkPeer(cntrl->u.pNodeTrc.peerId, &peerCb);
         if(peerCb != NULLP)
         {
            peerCb->trcLen = cntrl->u.pNodeTrc.trcLen;
            peerCb->trcMask |= cntrl->u.pNodeTrc.trcMask;
         }
         break;
      }
      case ADISIMM:
      {
         /* Disable the trace for Peer */
         szNdbChkPeer(cntrl->u.pNodeTrc.peerId, &peerCb);
         if(peerCb != NULLP)
         {
            peerCb->trcLen = cntrl->u.pNodeTrc.trcLen;
            peerCb->trcMask &= ~(cntrl->u.pNodeTrc.trcMask);
         }
         break;
      }
      case ADEL:
      {
         for (loopCnt = 0; loopCnt < cntrl->u.peer.nmbPeers; loopCnt++) 
         {
            szNdbChkPeer(cntrl->u.peer.peerId[loopCnt], &peerCb);
            if (peerCb == NULLP)
            {
#if (ERRCLASS & ERRCLS_ADD_RES)
              SZLOGERROR(ERRCLS_DEBUG, ESZ101,  cntrl->u.peer.peerId[loopCnt].val,
                    "szPeerCntrl, Peer not present");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */
               continue;
            }
            /* sz008.301: Rearrenging the checks */
            /* sz004.301: Removed the validation check for the peer state */
            ret = szDelPeer(peerCb);
            if(ret == ROKPENDING)
            {
               status->status = LCM_PRIM_OK_NDONE;
               status->reason = LCM_REASON_NOT_APPL;
            }
            else if (ret == ROK)
            {
               status->status = LCM_PRIM_OK;
               status->reason = LCM_REASON_NOT_APPL;
            }
            else
            {
#if (ERRCLASS & ERRCLS_ADD_RES)
               SZLOGERROR(ERRCLS_DEBUG, ESZ103, ERRZERO,
                     "szPeerCntrl, Couldn't delete the peer");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */
               continue;
            }
         }
        if (cntrl->u.peer.nmbPeers > 0)
         {
            /* Free the memory for peerInfo */
            SZ_FREE(cntrl->u.peer.peerId, (sizeof(TknU32) * cntrl->u.peer.nmbPeers));
            cntrl->u.peer.peerId = NULLP;
         }
         break;    
      }      
      default:
      {
         break;
      }
   }

   RETVALUE(ret);

} /* szPeerCntrl */

/*
 *
 *      Fun:   szValidatePeerCntrl
 *
 *      Desc:  Validates the Peer control parameters
 *
 *      Ret:   ROK     - ok
 *             RFAILED - failure
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szValidatePeerCntrl
(
SzCntrl  *cntrl         /* general control structure */
)
#else
PRIVATE S16 szValidatePeerCntrl(cntrl)
SzCntrl *cntrl;         /* general control structure */
#endif
{
   SzPeerCb *peerCb = NULLP;
   S16 ret = LCM_REASON_NOT_APPL;

   TRC2(szValidatePeerCntrl);

   switch (cntrl->action)
   {
      case AENA:
      case ADISIMM:
      {
         switch (cntrl->subAction)
         {
            case SATRC:
            {
               szNdbChkPeer(cntrl->u.pNodeTrc.peerId, &peerCb);
               if (peerCb == NULLP)
               {
                  ret = LCM_REASON_INVALID_PAR_VAL;
               }
               break;
            }
            default:
            {
               ret = LCM_REASON_INVALID_SUBACTION;
               break;
            }
         }
         break;
      }
      case ADEL:
      {
         switch (cntrl->subAction)
         {
            case SAELMNT:
            {
               if ((cntrl->u.peer.nmbPeers <= 0) || 
                   (cntrl->u.peer.peerId == NULLP))
               {
                  ret = LCM_REASON_INVALID_PAR_VAL;
               }
               break;
            }
            default:
            {
               ret = LCM_REASON_INVALID_SUBACTION;
               if (cntrl->u.peer.nmbPeers > 0)
               {
                  /* Free the memory for peerInfo */
                  SZ_FREE(cntrl->u.peer.peerId, 
                        (sizeof(TknU32) * cntrl->u.peer.nmbPeers));
                  cntrl->u.peer.peerId = NULLP;
               }
               break;
            }
         }
         break;
      }
      default:
      {
         ret = LCM_REASON_INVALID_ACTION;
         break;
      }
   }

   RETVALUE(ret);

} /* szValidatePeerCntrl */

/*
 *
 *      Fun:   szDelPeer
 *
 *      Desc:  Delete the Peer
 *
 *      Ret:   ROK   - ok
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szDelPeer
(
SzPeerCb *peerCb     /* Peer control block */
)
#else
PRIVATE S16 szDelPeer(peerCb)
SzPeerCb *peerCb;    /* Peer control block */
#endif
{

   TRC2(szDelPeer);

   peerCb->delPcb = TRUE;

   /* Terminate the association */
   /* sz008.301 : Removed redundant code and 
    * removed the double checking of ret values */
#ifdef S1SIMAPP
   RETVALUE(szLiTermAssoc(&peerCb, FALSE,FALSE));
#else
   RETVALUE(szLiTermAssoc(&peerCb, FALSE));
#endif
   

} /* szDelPeer */


/******************************************************************************/
/*                   Statistics Request Support Functions                     */
/******************************************************************************/
/*
 *
 *      Fun:   szGetGenSts
 *
 *      Desc:  Gather the general statistics
 *
 *      Ret:   ROK     - ok
 *             RFAILED - failure
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szGetGenSts
(
SzGenSts *sts,              /* general statistics structure */
CmStatus *status,           /* Return status */
Action action               /* Action */
)
#else
PRIVATE S16 szGetGenSts(sts, status, action)
SzGenSts *sts;              /* general statistics structure */
CmStatus *status;           /* Return status */
Action action;              /* Action */
#endif
{
   S16 ret;

   TRC2(szGetGenSts);

   ret = szValidateGenSts (sts, action);

   if (ret != LCM_REASON_NOT_APPL)
   {
      status->status = LCM_PRIM_NOK;
      status->reason = ret;
      RETVALUE(RFAILED);
   }

   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

   cmMemcpy ((U8 *)sts, (U8 *)&szCb.genSts, sizeof (SzGenSts));
   if (action == ZEROSTS)
   {
      cmMemset ((U8 *)&szCb.genSts, 0, sizeof (SzGenSts));
   }

   RETVALUE(ROK);

} /* szGetGenSts */

/*
 *
 *      Fun:   szValidateGenSta
 *
 *      Desc:  Validates the S1AP general statistics request
 *
 *      Ret:   ROK   - ok
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szValidateGenSts
(
SzGenSts  *sts,         /* general statistics  structure */
Action action           /* action */
)
#else
PRIVATE S16 szValidateGenSts(sts, action)
SzGenSts *sts;         /* general statistics structure */
Action action;         /* action */
#endif
{
   S16 ret = LCM_REASON_NOT_APPL;

   TRC2(szValidateGenSts);

   if (action != ZEROSTS && action != NOZEROSTS)
   {
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   RETVALUE(ret);

} /* end of szValidateGenSts */

/*
 *
 *      Fun:   szGetPeerNodeSts
 *
 *      Desc:  Gather the peer node statistics
 *
 *      Ret:   ROK     - ok
 *             RFAILED - failure
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szGetPeerNodeSts
(
SzPeerNodeSts *sts,         /* Node statistics structure */
CmStatus *status,           /* Return status */
Action action               /* Action */
)
#else
PRIVATE S16 szGetPeerNodeSts(sts, status, action)
SzPeerNodeSts *sts;         /* Node statistics structure */
CmStatus *status;           /* Return status */
Action action;              /* Action */
#endif
{
   S16 ret;

   SzPeerCb *peerCb = NULLP;

   TRC2(szGetPeerNodeSts);

   ret = szValidatePNodeSts (sts, action);

   if (ret != LCM_REASON_NOT_APPL)
   {
      status->status = LCM_PRIM_NOK;
      status->reason = ret;
      RETVALUE(RFAILED);
   }

   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

   if ((ret = szNdbChkPeer(sts->peerId, &peerCb)) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SZLOGERROR(ERRCLS_DEBUG, ESZ105, ERRZERO,
                 "szGetPeerNodeSts: peerCb is NULLP");
#endif /* (ERRCLASS & ERRCLS_ADD_RES) */
      RETVALUE(RFAILED);
   }

   cmMemcpy((U8 *)&sts->cfm, (U8 *)&peerCb->peerSts.cfm, sizeof (peerCb->peerSts.cfm));
   if (action == ZEROSTS)
   {
      cmMemset ((U8 *)&peerCb->peerSts.cfm, 0, sizeof (peerCb->peerSts.cfm));
   }

   RETVALUE(ROK); 

} /* szGetPeerNodeSts */

/*
 *
 *      Fun:   szValidatePNodeSts
 *
 *      Desc:  Validates the S1AP Peer node statistics
 *
 *      Ret:   ROK   - ok
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szValidatePNodeSts
(
SzPeerNodeSts  *sts,         /* Node statistics  structure */
Action action                /* action */
)
#else
PRIVATE S16 szValidatePNodeSts(sts, action)
SzPeerNodeSts *sts;         /* Node statistics structure */
Action action;              /* action */
#endif
{
   S16 ret = LCM_REASON_NOT_APPL;
   SzPeerCb *peerCb = NULLP;

   TRC2(szValidatePNodeSts);

   if (action != ZEROSTS && action != NOZEROSTS)
   {
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   szNdbChkPeer(sts->peerId, &peerCb); 

   if (peerCb == NULLP)
   {
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   RETVALUE(ret);

} /* szValidatePNodeSts */

/* sz001.201 Added SCT SAP level statistics */
/*
 *
 *      Fun:   szGetSctSapSts
 *
 *      Desc:  Gather the SCT SAP statistics
 *
 *      Ret:   ROK     - ok
 *             RFAILED - failure
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szGetSctSapSts
(
SzSctSapSts *sts,         /* statistics structure for sct sap */
CmStatus *status,         /* Return status */
Action action             /* Action */
)
#else
PRIVATE S16 szGetSctSapSts(sts, status, action)
SzSctSapSts *sts;         /* statistics structure for sct sap */
CmStatus *status;         /* Return status */
Action action;            /* Action */
#endif
{
   SzSctSapCb *sctSapCb;
   S16         ret;

   TRC2(szGetSctSapSts);

   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

   ret = szValidateSctSapSts(sts, action);

   if (ret != LCM_REASON_NOT_APPL)
   {
      status->status = LCM_PRIM_NOK;
      status->reason = ret;

      RETVALUE(RFAILED);
   }

   sctSapCb = szCb.sctSapLst[sts->suId];

   cmMemcpy((U8 *)&sts->cfm, (U8 *)&sctSapCb->sts.cfm, sizeof(sctSapCb->sts.cfm));

   if (action == ZEROSTS)
   {
      cmMemset((U8 *)&sctSapCb->sts.cfm, 0, sizeof(sctSapCb->sts.cfm));
   }

   RETVALUE(ROK); 

} /* szGetSctSapSts */

/*
 *
 *      Fun:   szValidateSctSapSts
 *
 *      Desc:  Validates the S1AP Peer node statistics
 *
 *      Ret:   ROK   - ok
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szValidateSctSapSts
(
SzSctSapSts  *sts,         /* statistics structure for sct sap */
Action action              /* action */
)
#else
PRIVATE S16 szValidateSctSapSts(sts, action)
SzSctSapSts *sts;         /* statistics structure for sct sap */
Action action;            /* action */
#endif
{
   S16 ret = LCM_REASON_NOT_APPL;

   TRC2(szValidateSctSapSts);

   if ((action != ZEROSTS) && (action != NOZEROSTS))
   {
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if ((sts->suId >= szCb.genCfg.nmbSctSaps) || 
       (szCb.sctSapLst[sts->suId] == NULLP))
   {
      RETVALUE(LCM_REASON_INVALID_SAP);
   }

   RETVALUE(ret);

} /* szValidateSctSapSts */

/******************************************************************************/
/*                   Status Request Support Functions                         */
/******************************************************************************/
/*
 *
 *      Fun:   szGetGenSta
 *
 *      Desc:  Gather the general S1AP status
 *
 *      Ret:   ROK   - ok
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szGetGenSta
(
SzGenSta *sta,         /* General status */
CmStatus *status       /* Return status */
)     
#else    
PRIVATE S16 szGetGenSta(sta, status)
SzGenSta *sta;         /* General status */
CmStatus *status;      /* Return status */
#endif
{        
   TRC2(szGetGenSta);
      
   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

   cmMemcpy ((U8 *)sta, (U8 *)&szCb.genSta, sizeof (SzGenSta));

   RETVALUE(ROK);

} /* end of szGetGenSta */

/*
 *
 *      Fun:   szGetSztSapSta
 *
 *      Desc:  Gather the general S1AP's Upper Sap status
 *
 *      Ret:   ROK     - ok
 *             RFAILED - failure
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szGetSztSapSta
(
SzSapSta *sta,         /* upper sap status */
CmStatus *status       /* Return status */
)
#else
PRIVATE S16 szGetSztSapSta(sta, status)
SzSapSta *sta;         /* upper sap status */
CmStatus *status;      /* Return status */
#endif
{
   S16 ret;

   TRC2(szGetSztSapSta);

   ret = szValidateSztSapSta (sta);

   if (ret != LCM_REASON_NOT_APPL)
   {
      status->status = LCM_PRIM_NOK;
      status->reason = ret;
      RETVALUE(RFAILED);
   }

   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

   sta->status = szCb.sztSapLst[sta->sapId]->state;

   RETVALUE(ROK);

} /* end of szGetSztSapSta */

/*
 *
 *      Fun:   szValidateSztSapSta
 *
 *      Desc:  Validates the S1AP's Upper SAP status
 *
 *      Ret:   ROK     - ok
 *             RFAILED - failure
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szValidateSztSapSta
(
SzSapSta *sta          /* upper sap status */
)
#else
PRIVATE S16 szValidateSztSapSta(sta)
SzSapSta *sta;         /* upper sap status */
#endif
{
   S16 ret = LCM_REASON_NOT_APPL;

   TRC2(szValidateSztSapSta);

   if (sta->sapId >= szCb.genCfg.nmbSztSaps)
   {
      ret = LCM_REASON_INVALID_PAR_VAL;
   }
   else
   {
      if (szCb.sztSapLst[sta->sapId] == NULLP)
      {
         ret = LCM_REASON_INVALID_PAR_VAL;
      }
   }

   RETVALUE(ret);

} /* szValidateSztSapSta */

/*
 *
 *      Fun:   szGetSctSapSta
 *
 *      Desc:  Gather the S1AP's lower SAP status
 *
 *      Ret:   ROK     - ok
 *             RFAILED - failure
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szGetSctSapSta
(
SzSapSta *sta,         /* lower sap status */
CmStatus *status       /* Return status */
)
#else
PRIVATE S16 szGetSctSapSta(sta, status)
SzSapSta *sta;         /* lower sap status */
CmStatus *status;      /* Return status */
#endif
{
   S16 ret;

   TRC2(szGetSctSapSta);

   ret = szValidateSctSapSta (sta);

   if (ret != LCM_REASON_NOT_APPL)
   {
      status->status = LCM_PRIM_NOK;
      status->reason = ret;
      RETVALUE(RFAILED);
   }

   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

   sta->status = szCb.sctSapLst[sta->sapId]->state;

   RETVALUE(ROK);

} /* szGetSctSapSta */

/*
 *
 *      Fun:   szValidateSctSapSta
 *
 *      Desc:  Validates the S1AP's Lower SAP status
 *
 *      Ret:   ROK     - ok
 *             RFAILED - failure
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szValidateSctSapSta
(
SzSapSta *sta          /* lower sap status */
)
#else
PRIVATE S16 szValidateSctSapSta(sta)
SzSapSta *sta;         /* lower sap status */
#endif
{
   S16 ret = LCM_REASON_NOT_APPL;

   TRC2(szValidateSctSapSta);

   if (sta->sapId >= szCb.genCfg.nmbSctSaps)
   {
      ret = LCM_REASON_INVALID_PAR_VAL;
   }
   else
   {
      if (szCb.sctSapLst[sta->sapId] == NULLP)
      {
         ret = LCM_REASON_INVALID_PAR_VAL;
      }
   }

   RETVALUE(ret);

} /* szValidateSctSapSta */
 
/*
 *
 *       Fun:   szGetPeerSta 
 *
 *       Desc:  This function is used to return the peer status
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: N/A
 *
 *       File:  sz_mi.c
 *
 */
#ifdef ANSI
PRIVATE S16 szGetPeerSta
(
SzPeerSta *sta,         /* Peer status */
CmStatus *status        /* Return status */
)
#else
PRIVATE S16 szGetPeerSta(sta, status)
SzPeerSta *sta;         /* Peer status */
CmStatus *status;       /* Return status */  
#endif
{
   S16 ret;
   SzPeerCb *peerCb = NULLP;
   U32 loopCnt;

   TRC2(szGetPeerSta);   

   ret = szValidatePeerSta(sta);

   if (ret != LCM_REASON_NOT_APPL)
   {
      status->status = LCM_PRIM_NOK;
      status->reason = ret;
      RETVALUE(RFAILED);
   }

   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

   for (loopCnt = 0; loopCnt < sta->nmbPeer; loopCnt++)  
   {
      szNdbChkPeer(sta->peerStaInfo[loopCnt].peerId, &peerCb);
    
      if (peerCb != NULLP) 
      {
         sta->peerStaInfo[loopCnt].peerState = peerCb->state;
         /* sz002.301: Update the spAssocId instead of suAssocId */
         sta->peerStaInfo[loopCnt].spAssocId = peerCb->assocCb->spAssocId;
         if (peerCb->assocCb->assocState == SZ_ASSOC_UP)
         {
            sta->peerStaInfo[loopCnt].connected = TRUE;
         }
         else
         {
            sta->peerStaInfo[loopCnt].connected = FALSE;
         }
         /* sz002.301: Removed the unused code */
      }
   }

   RETVALUE(ROK);

} /* szGetPeerSta */

/*
 *
 *      Fun:   szValidatePeerSta
 *
 *      Desc:  Validates the S1AP Peer Status.
 *
 *      Ret:   ROK     - ok
 *             RFAILED - failure
 *
 *      Notes: None.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef ANSI
PRIVATE S16 szValidatePeerSta
(
SzPeerSta *sta          /* Peer status */
)
#else
PRIVATE S16 szValidatePeerSta(sta)
SzPeerSta *sta;        /* Peer status */
#endif
{
   SzPeerCb *peerCb = NULLP;
   U32 loopCnt;

   TRC2(szValidatePeerSta);

   if (sta->nmbPeer >= szCb.genCfg.nmbPeer)
   {
      RETVALUE(LCM_REASON_EXCEED_CONF_VAL);
   }

   for (loopCnt = 0; loopCnt < sta->nmbPeer; loopCnt++)
   {
      szNdbChkPeer(sta->peerStaInfo[loopCnt].peerId, &peerCb);
      if (peerCb == NULLP)
      {
         RETVALUE(LCM_REASON_INVALID_PAR_VAL);
      }
   }

   RETVALUE(LCM_REASON_NOT_APPL);

} /* szValidatePeerSta*/

/***********************************************************************
                      System Service Interface Functions
 ***********************************************************************/
/*
 *
 *      Fun:   szActvInit
 *
 *      Desc:  Activate Task - Initialize. 
 *
 *      Ret:   ROK   - ok
 *
 *      Notes: Invoked by system services to initialize a task.
 *
 *      File:  sz_mi.c
 *
*/
#ifdef SS_MULTIPLE_PROCS
#ifdef ANSI
PUBLIC S16 szActvInit
(
ProcId procId,
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason,          /* reason */
Void **xxCb           /* Protocol control Block */
)
#else
PUBLIC S16 szActvInit(procId, entity, inst, region, reason,xxCb)
ProcId procId;         /* Proc Id */
Ent entity;            /* entity */
Inst inst;             /* instance */
Region region;         /* region */
Reason reason;         /* reason */
Void **xxCb;           /* protocol control block */
#endif

#else /* SS_MULTIPLE_PROCS */
#ifdef ANSI 
PUBLIC S16 szActvInit
(
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason          /* reason */
)
#else
PUBLIC S16 szActvInit(entity, inst, region, reason)
Ent entity;            /* entity */
Inst inst;             /* instance */
Region region;         /* region */
Reason reason;         /* reason */
#endif
#endif /*SS_MULTIPLE_PROCS */
{

#ifdef SS_MULTIPLE_PROCS
   U16 loopCnt=0;
   PRIVATE U16 szFirstCall = FALSE;
   U16 idx=0;
#endif /* SS_MULTIPLE_PROCS */

   TRC3(szActvInit);

   /* sz003.301: Added hooks for PSF-S1AP */
#ifdef SS_MULTIPLE_PROCS
   if(reason == SHUTDOWN)
   {
#ifdef YT
      Void *tmpPsfCb = szCb.psfCb;
#endif /* YT */
      cmMemset ((U8 *)&szCb, 0, sizeof(SzCb));
      szCb.used = TRUE;
      szCb.shutdown = TRUE;
      szCb.init.proc  = procId;
      szCb.init.procId=procId;
#ifdef YT
      szCb.psfCb = tmpPsfCb;
#endif /* YT */
   }
   else if(reason == NRM_TERM)
   {
      cmMemset ((U8 *)*xxCb, 0, sizeof(SzCb));
      ((SzCb*)(*xxCb))->used = FALSE;

      RETVALUE(ROK);
   }
   else
   {
      if(!szFirstCall)
      {
         szFirstCall = TRUE;
         for(loopCnt=0;loopCnt<SZ_MAX_INSTANCES;loopCnt++)
         {
           SZ_ZERO(&szCbLst[loopCnt],sizeof(SzCb));
         }
         idx = 0;
         loopCnt = 0;
      }
      else
      {
         for(loopCnt=0;loopCnt<SZ_MAX_INSTANCES;loopCnt++)
         {
            if(szCbLst[loopCnt].used == FALSE)
            {
               szCbPtr=&szCbLst[loopCnt];
               idx = loopCnt;
               break;
            }
         }
      }

      if(loopCnt == SZ_MAX_INSTANCES)
         RETVALUE(FALSE);

      szCbLst[idx].used=TRUE;
      szCbPtr=&szCbLst[idx];
      *xxCb=(Void *)&szCbLst[idx];
      szCb.shutdown = FALSE;
      szCb.init.proc   = procId;
      szCb.init.procId = procId;
#ifdef DEBUGP
      szCb.init.dbgMask &= 0x00000002;
#endif
   /* sz003.301: Added hooks for PSF-S1AP */
#ifdef YT
      szCb.psfCb = (Void *)&(ytCbLst[idx]);
#endif /* YT */
   }
#else /* SS_MULTIPLE_PROCS */
   cmMemset ((U8 *)&szCb, 0, sizeof(SzCb));
   if(reason == SHUTDOWN)
   {
      szCb.shutdown = TRUE;
   }
   szCb.init.procId = SFndProcId();
#endif /* SS_MULTIPLE_PROCS */

   szCb.init.ent = entity;
   szCb.init.inst = inst;
   szCb.init.region = region;
   szCb.init.reason = reason;
   szCb.init.cfgDone = FALSE;
   szCb.init.pool = 0;
   szCb.init.acnt = FALSE;
   szCb.init.trc = FALSE;

#ifdef SZ_USTA
   szCb.init.usta = TRUE;
#else
   szCb.init.usta = FALSE;
#endif /* SZ_USTA */

#ifdef DEBUGP
#ifdef SZ_DEBUG
   szCb.init.dbgMask = 0xffffffff;
#else
   szCb.init.dbgMask = 0x00000000;
#endif /* SZ_DEBUG */
#endif /* DEBUGP */

   /* sz003.301: Added hooks for PSF-S1AP */
#ifdef YT
   if(reason != SHUTDOWN)
   {
      ytActvInit(entity, inst, region, reason);
   }
#endif /* YT */
#ifdef SS_DIAG
   /* sz008.301 : Change for Diagnostics */
   szCb.init.logMask = 0x0;
#endif

   RETVALUE(ROK);

} /* szActvInit */

/* sz003.301: Added new functions used by PSF */
#ifdef SZ_FTHA

/**********************************************************
 *
 *       Fun:   szFillRepPost - Filling reply  post structure
 *
 *       Desc:  This function prepares the post structure required for 
 *              sending the conformtion message
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *
 *       File:  sq_mi.c
 *
 **********************************************************/
#ifdef ANSI
PRIVATE S16 szFillRepPost
(
 Pst               *pst,         /* post structure */
 ShtCntrlReqEvnt   *reqInfo,     /* system agent control request event */
 Pst               *repPst       /* reply post structure */
 )
#else
PRIVATE S16 szFillRepPost(pst,reqInfo,repPst)
Pst               *pst;         /* post structure */
ShtCntrlReqEvnt   *reqInfo;     /* system agent control request event */
Pst               *repPst;      /* reply post structure */
#endif
{
   TRC3 (szFillRepPost);

   SZDBGP(DBGMASK_MI, (szCb.init.prntBuf, 
            " In szFillRepPost: Fillin the reply pst structure \n"));

   /* fill reply post structure */
   repPst->dstProcId = pst->srcProcId;
   repPst->dstEnt    = pst->srcEnt;
   repPst->dstInst   = pst->srcInst;
   repPst->prior     = reqInfo->hdr.response.prior;
   repPst->route     = reqInfo->hdr.response.route;
   repPst->selector  = reqInfo->hdr.response.selector;
   repPst->event     = EVTSHTCNTRLCFM;
#ifdef SS_MULTIPLE_PROCS
   repPst->srcProcId = szCb.init.procId;
#else
   repPst->srcProcId = SFndProcId();
#endif
   repPst->srcEnt    = ENTSZ;
   repPst->srcInst   = szCb.init.inst;
   repPst->region    = pst->region;
   repPst->pool      = pst->pool;

   RETVALUE(ROK);
}


/**********************************************************
 *
 *       Fun:   szEnbDisSap - Bind Enable or Unbind Disable function
 *
 *       Desc:  This function enable or disable the bind between 
 *              S1AP and SCTP
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *
 *       File:  sq_mi.c
 *
 **********************************************************/
#ifdef ANSI
PRIVATE S16 szEnbDisSap
(
 ShtCntrlReqEvnt   *reqInfo,     /* system agent control request event */
 ShtCntrlCfmEvnt   *cfmInfo      /* system agent control confirm event */
)
#else
PRIVATE S16 szEnbDisSap(reqInfo,cfmInfo)
ShtCntrlReqEvnt   *reqInfo;     /* system agent control request event */
ShtCntrlCfmEvnt   *cfmInfo;     /* system agent control confrim event */
#endif
{
   S16            i;            /* local counter */
   SzSctSapCb     *sctSapCb;    /* local pointer */
   SzSztSapCb     *sztSapCb;    /* local pointer */

   TRC3 (szEnbDisSap);

   SZDBGP(DBGMASK_MI, (szCb.init.prntBuf, 
            " In szEnbDisSap: Enable/Disable the Sap \n"));

   if( (reqInfo->s.bndEna.grpType != SHT_GRPTYPE_ALL) &&
         (reqInfo->s.bndEna.grpType != SHT_GRPTYPE_ENT) )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SZLOGERROR(ERRCLS_DEBUG,ESZXXX,0,"Invalid parameter value");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
      /* unregcognised group type */
      cfmInfo->status.reason = LCM_REASON_INVALID_PAR_VAL;
      RETVALUE(RFAILED);
   }

   /* call function for all SAPS */
   for (i = 0; i < szCb.genCfg.nmbSctSaps; i++)
   {
      if (szCb.sctSapLst[i] != (SzSctSapCb *) NULLP)
      {
         sctSapCb = szCb.sctSapLst[i]; /* we have a configured SctSap */

         if ((sctSapCb->pst.dstEnt == reqInfo->s.bndEna.dstEnt.ent) &&
               (sctSapCb->pst.dstInst == reqInfo->s.bndEna.dstEnt.inst) &&
               (sctSapCb->contEnt != ENTSM))
         {
            if ((reqInfo->s.bndEna.grpType == SHT_GRPTYPE_ALL) &&
                  (sctSapCb->pst.dstProcId != reqInfo->s.bndEna.dstProcId))
            {
               continue;
            }
            if (reqInfo->reqType == SHT_REQTYPE_BND_ENA)
            {
               if (szEnaSctSap(sctSapCb->suId) != ROK)
               {
#if (ERRCLASS & ERRCLS_DEBUG)
                  SZLOGERROR(ERRCLS_DEBUG,ESZXXX,0,
                        "SzMiShtCntrlReq,Failed to bind & enb the SCTP SAP");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
                  RETVALUE(RFAILED);
               }
               sctSapCb->retryCnt = 0; /* Reset bind retry count */
            }
            else
            {
               if(szUbndSctSap(sctSapCb->suId,SZ_UBND_SAP,sctSapCb->contEnt)
                     != ROK)
               {
#if (ERRCLASS & ERRCLS_DEBUG)
                  SZLOGERROR(ERRCLS_DEBUG,ESZXXX,0,"SzMiShtCntrlReq,\
                        Failed to unbind and disable the SCTP SAP");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
                  RETVALUE(RFAILED);
               }
            }
         }
         else
         {
            SZDBGP(DBGMASK_MI,(szCb.init.prntBuf,"Invalid parameter value\n"));
            /* unregcognised group type */
            cfmInfo->status.reason = LCM_REASON_INVALID_PAR_VAL;
            RETVALUE(RFAILED);
         }
      }
   }
   
   if( reqInfo->reqType == SHT_REQTYPE_UBND_DIS )
   {
      /*-- Disable Upper SAPs --*/
      for (i = 0; i < szCb.genCfg.nmbSztSaps; i++)
      {
         sztSapCb = szCb.sztSapLst[i];
         if ((sztSapCb != (SzSztSapCb *)NULLP) &&
               (sztSapCb->pst.dstEnt == reqInfo->s.ubndDis.dstEnt.ent) &&
               (sztSapCb->pst.dstInst == reqInfo->s.ubndDis.dstEnt.inst))
         {
            if ((reqInfo->s.ubndDis.grpType == SHT_GRPTYPE_ALL) &&
                  (sztSapCb->pst.dstProcId != reqInfo->s.ubndDis.dstProcId))
            {
               continue;
            }
            if(szUbndSztSap (sztSapCb->suId,SZ_UBND_SAP) != ROK )
            {
#if (ERRCLASS & ERRCLS_DEBUG)
               SZLOGERROR(ERRCLS_DEBUG,ESZXXX,0,
                     "SzMiShtCntrlReq,Failed to unbind and disable the USAP");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
               RETVALUE(RFAILED);
            }
         }
      }
   }
    RETVALUE(ROK);
} /* End of szEnbDisSap */


#ifdef SZ_RUG

/************************************************************************
 *
 *       Fun  :  Get Interface Version handling
 *
 *       Desc :  Processes system agent control request 
 *               primitive to get interface version for all
 *               intefaces implemented by the protocol
 *
 *       Ret  :  ROK  - ok
 *
 *       Notes:  None
 *
 *       File :  sq_mi.c
 *
 ***********************************************************************/
#ifdef ANSI
PRIVATE S16 szGetVer
(
ShtGetVerCfm *getVerCfmInfo   /* to return intf ver info */
)
#else
PRIVATE S16 szGetVer(getVerCfmInfo)
ShtGetVerCfm *getVerCfmInfo;  /* to return intrf ver info */
#endif
{
   TRC2(szGetVer);

   SZDBGP(DBGMASK_MI, (szCb.init.prntBuf, 
            " In szGetVer: Getting the version \n"));

              
   /* Fill list of upper interfaces IDs and their ver number */
   getVerCfmInfo->numUif = 1;
   getVerCfmInfo->uifList[0].intfId  = SZTIF;
   getVerCfmInfo->uifList[0].intfVer = SZTIFVER;
              
   /* Fill list of lower interfaces IDs and their ver number */
   getVerCfmInfo->numLif = 1;
   getVerCfmInfo->lifList[0].intfId  = SCTIF;
   getVerCfmInfo->lifList[0].intfVer = SCTIFVER;
   
#ifdef YT   
   /* Fill peer interfaces ID and version number */
   ytGetVer(&getVerCfmInfo->pif);
#endif /* ifdef YT */
              
   RETVALUE(ROK);
}/* End of szGetVer */

 
/**********************************************************
 *
 *       Fun:   szUpdVer  - Update Version
 *
 *       Desc:  Update the version of the layer as well as the PSF of the layer
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *
 *       File:  sq_mi.c
 *
 **********************************************************/
#ifdef ANSI
PRIVATE S16 szUpdVer
(
ShtVerInfo *shtVerInfo     /* interface version information */
 )
#else
PRIVATE S16 szUpdVer(shtVerInfo)
ShtVerInfo *shtVerInfo;     /* interface version information */
#endif
{
   SzSctSapCb *sctSapCb;
   SzSztSapCb *sztSapCb;
   U16        i;

   TRC2 (szUpdVer);

   SZDBGP (DBGMASK_MI, (szCb.init.prntBuf, 
            " In szUpdVer: Updating the version \n"));

   /* update interface version info in pst within SAPs */
   switch(shtVerInfo->intf.intfId)
   {
      case SZTIF:
         for(i = 0; i < szCb.genCfg.nmbSztSaps; i++)
         {
            /* find SztSap cb */
            if((sztSapCb = szCb.sztSapLst[i]) != NULLP)
            {
               /* update interface version in pst only if SAP is bound */
               if(sztSapCb->state == LSZ_SAP_ISBOUND)
               {
                  switch(shtVerInfo->grpType)
                  {
                     case SHT_GRPTYPE_ALL:
                        if((shtVerInfo->dstProcId == sztSapCb->pst.dstProcId) &&
                           (shtVerInfo->dstEnt.ent == sztSapCb->pst.dstEnt) &&
                           (shtVerInfo->dstEnt.inst == sztSapCb->pst.dstInst))
                        {
                           sztSapCb->pst.intfVer = shtVerInfo->intf.intfVer;
                           sztSapCb->remIntfValid = TRUE;
                        }
                        break;
                     case SHT_GRPTYPE_ENT:
                        if((shtVerInfo->dstEnt.ent == sztSapCb->pst.dstEnt) &&
                           (shtVerInfo->dstEnt.inst == sztSapCb->pst.dstInst))
                        {
                           sztSapCb->pst.intfVer = shtVerInfo->intf.intfVer;
                           sztSapCb->remIntfValid = TRUE;
                        }
                        break;
                  } /* end switch(shtVerInfo->grpType) */
               } /* end if(sztSapCb->status == LSZ_SAP_ISBOUND) */
            } /* end if(sztSapCb != NULLP) */
         } /* end for(i = 0; ...) */
         break;

      case SCTIF:
         for(i = 0; i < szCb.genCfg.nmbSctSaps; i++)
         {
            /* find SctSap cb */
            if((sctSapCb = szCb.sctSapLst[i]) != NULLP)
            {
               switch(shtVerInfo->grpType)
               {
                  case SHT_GRPTYPE_ALL:
                     if((shtVerInfo->dstProcId == sctSapCb->pst.dstProcId) &&
                        (shtVerInfo->dstEnt.ent == sctSapCb->pst.dstEnt) &&
                        (shtVerInfo->dstEnt.inst == sctSapCb->pst.dstInst))
                     {
                        sctSapCb->pst.intfVer = shtVerInfo->intf.intfVer;
                        sctSapCb->remIntfValid = TRUE;
                     }
                     break;
                  case SHT_GRPTYPE_ENT:
                     if((shtVerInfo->dstEnt.ent == sctSapCb->pst.dstEnt) &&
                        (shtVerInfo->dstEnt.inst == sctSapCb->pst.dstInst))
                     {
                        sctSapCb->pst.intfVer = shtVerInfo->intf.intfVer;
                        sctSapCb->remIntfValid = TRUE;
                     }
                     break;
               } /* end switch(shtVerInfo->grpType) */
            } /* end if(sctSapCb != NULLP) */
         } /* end for(i = 0; ...) */
      }
   RETVALUE(ROK);
} /* End of szUpdVer */


/**********************************************************************
 *
 *       Fun:   szSetVer
 *
 *       Desc:  Set interface version request handling, processes system agent 
 *              control request primitive to set interface version number
 *
 *       Ret:   ROK     - Success
 *              RFAILED - Failed
 *
 *       Notes: None
 *
 *       File:  sq_mi.c
 *
 *********************************************************************/
#ifdef ANSI
PUBLIC S16 szSetVer
(
ShtVerInfo *shtVerInfo,     /* interface version information */
CmStatus   *status          /* status */
)
#else
PUBLIC S16 szSetVer(shtVerInfo, status)
ShtVerInfo *shtVerInfo;     /* interface version information */
CmStatus   *status;         /* status */
#endif
{
   U16        i;
   Bool       found;
   ShtVerInfo *intfInfo;

   TRC2(szSetVer);

   SZDBGP(DBGMASK_MI,(szCb.init.prntBuf,"szSetVer:Setting the version as %d\n", 
            shtVerInfo->intf.intfVer));


   found = FALSE;

   status->reason = LCM_REASON_NOT_APPL;

   /* validate interface version information, if interface version number in
      set request is greater than self interface version then return reason 
      as version mismatch */
   switch(shtVerInfo->intf.intfId)
   {
      case SZTIF:
         if(shtVerInfo->intf.intfVer > SZTIFVER)
            status->reason = LCM_REASON_VERSION_MISMATCH;
         break;
      case SCTIF:
         if(shtVerInfo->intf.intfVer > SCTIFVER)
            status->reason = LCM_REASON_VERSION_MISMATCH;
         break;
#ifdef YT
      case YTPIF:
         if(shtVerInfo->intf.intfVer > YTPIFVER)
            status->reason = LCM_REASON_VERSION_MISMATCH;
         break;
#endif /* YT */
      default:
         status->reason = LCM_REASON_VERSION_MISMATCH;
         break;
   } /* end switch(shtVerInfo->intf.intfId) */
   
   if(status->reason != LCM_REASON_NOT_APPL)
   {
      RETVALUE(RFAILED);
   }

#ifdef YT
   /* check if this is applicable to PSF, if version info is for peer
      interface, then return RFAILED . For peer interface, runtime update will 
      be done from within ytSetVer itself */
   if(ytSetVer(&shtVerInfo->intf, status) == RFAILED)
   {
      RETVALUE(RFAILED);
   }
#endif /* YT */
   /* check if stored information already exists */
   for(i = 0; i < szCb.nmbIntfInfo && found == FALSE; i++)
   {
      intfInfo = &szCb.intfInfo[i];
      if(intfInfo->intf.intfId == shtVerInfo->intf.intfId)
      {
         if(intfInfo->grpType == shtVerInfo->grpType)
         {
            /* if stored information found, replace version info with new info
               specified in set version request */
            switch(shtVerInfo->grpType)
            {
               case SHT_GRPTYPE_ALL:
                  if((intfInfo->dstProcId == shtVerInfo->dstProcId) &&
                     (intfInfo->dstEnt.ent == shtVerInfo->dstEnt.ent) &&
                     (intfInfo->dstEnt.inst == shtVerInfo->dstEnt.inst))
                  {
                     intfInfo->intf.intfVer = shtVerInfo->intf.intfVer;
                     found = TRUE;
                  }
                  break;
               case SHT_GRPTYPE_ENT:
                  if((intfInfo->dstEnt.ent == shtVerInfo->dstEnt.ent) &&
                     (intfInfo->dstEnt.inst == shtVerInfo->dstEnt.inst))
                  {
                     intfInfo->intf.intfVer = shtVerInfo->intf.intfVer;
                     found = TRUE;
                  }
                  break;
            } /* end switch(shtVerInfo->grpType) */
         } /* end if(intfInfo->grpType == shtVerInfo->grpType) */
      } /* end if(intfInfo->intf.intfId == shtVerInfo->intf.intfId) */
   } /* end for(i = 0; ...) */

   /* in worst case we need to store one intf version info for each SAP */
   if(found == FALSE)
   {
      /* check if version info can be appended to the list */
      if(szCb.nmbIntfInfo < ((Size)szCb.genCfg.nmbSztSaps + 
                            (Size)szCb.genCfg.nmbSctSaps))
      {
         /* store version info at the end of the list */
         (void) cmMemcpy( (U8 *)&szCb.intfInfo[szCb.nmbIntfInfo],
               (U8 *)shtVerInfo, sizeof(ShtVerInfo));

         /* increase number of interface information stored */
         szCb.nmbIntfInfo++;

      } /* end if(nmbIntfInfo < total number of SAPs) */
      else
      {
         status->reason = LCM_REASON_EXCEED_CONF_VAL;
         RETVALUE(RFAILED);
      } /* end else */
   } /* end (found == FALSE) */

   szUpdVer(shtVerInfo);
   
   RETVALUE(ROK);
} /* szSetVer */
#endif


/**********************************************************
 *
 *       Fun:   SzMiShtCntrlReq - System Agent Control Request
 *
 *       Desc:  Processes system agent control request primitive
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *
 *       File:  sq_mi.c
 *
 **********************************************************/
#ifdef ANSI
PUBLIC S16 SzMiShtCntrlReq
(
Pst               *pst,         /* post structure */
ShtCntrlReqEvnt   *reqInfo      /* system agent control request event */
)
#else
PUBLIC S16 SzMiShtCntrlReq(pst, reqInfo)
Pst               *pst;         /* post structure */
ShtCntrlReqEvnt   *reqInfo;     /* system agent control request event */
#endif
{
   Pst               repPst;    /* reply post structure */
   ShtCntrlCfmEvnt   cfmInfo;   /* system agent control confirm event */
   U16               reason ;   /* Reason to return to LM */

   TRC3(SzMiShtCntrlReq);

   cmMemset((U8*)&cfmInfo, 0, sizeof(ShtCntrlCfmEvnt));

#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId, pst->dstEnt,
                  pst->dstInst, (Void **)&szCbPtr)!=ROK) || (szCbPtr ==  NULLP))
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SZLOGERROR(ERRCLS_DEBUG,ESZXXX,0,
            "SzMiShtCntrlReq() failed, cannot derive szCb");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
      RETVALUE (RFAILED);
   }
#endif    /*SS_MULTIPLE_PROCS        */
   SZDBGP(DBGMASK_MI, (szCb.init.prntBuf,
            "-----S1AP-----(proc(%d), entt(%d), inst(%d))------\
            \n Mi System Agent Control Req\n", 
            pst->dstProcId, pst->dstEnt, pst->dstInst));

   reason = LCM_REASON_NOT_APPL;

   szFillRepPost(pst,reqInfo,&repPst);

   cfmInfo.transId = reqInfo->hdr.transId;
#ifdef SZ_RUG
   cfmInfo.reqType = reqInfo->reqType;
#endif /* SZ_RUG */

   /* check if general configuration done */
   if (szCb.init.cfgDone != TRUE)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SZLOGERROR(ERRCLS_DEBUG,ESZXXX,0,
            "General Configuration not done");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
      cfmInfo.status.status = LCM_PRIM_NOK;
      cfmInfo.status.reason = LCM_REASON_GENCFG_NOT_DONE;

      SzMiShtCntrlCfm(&repPst, &cfmInfo);
      RETVALUE(ROK);
   }
   /* fill status value */
   cfmInfo.status.reason = LCM_REASON_NOT_APPL;

#ifdef YT
   if(YT_IS_ACTV() == FALSE)  
   {
      cfmInfo.status.reason = LCM_REASON_INVALID_INSTANCE;
      cfmInfo.status.status = LCM_PRIM_OK;
      SzMiShtCntrlCfm(&repPst, &cfmInfo);  /* send the response */
      RETVALUE(RFAILED);
   }
#endif

   switch (reqInfo->reqType)
   {
      case SHT_REQTYPE_BND_ENA:      /* system agent control bind enable */
      case SHT_REQTYPE_UBND_DIS:     /* system agent control unbind disable */
         szEnbDisSap(reqInfo,&cfmInfo);

         break;
#ifdef SZ_RUG
      case SHT_REQTYPE_GETVER:  /* system agent control get interface version */
         szGetVer(&cfmInfo.t.gvCfm);
         break;
      case SHT_REQTYPE_SETVER:  /* system agent control set interface version */
         szSetVer(&reqInfo->s.svReq, &cfmInfo.status);

         /* Update the version to peer stand by node */
         YT_RTUPD_MOD(YT_UPD_VER_CB, &reqInfo->s.svReq);
         break;
#endif /* SZ_RUG */

      default:
         SZDBGP(DBGMASK_MI, (szCb.init.prntBuf, "Invalid parameter value\n"));
         cfmInfo.status.reason = LCM_REASON_INVALID_PAR_VAL;
         break;
   }

   /* response is sent without waiting for bind or unbind to complete */
   /* even if no SAPs are bound or unbound we still send success */
   if (cfmInfo.status.reason != LCM_REASON_NOT_APPL)
   {
      SZDBGP(DBGMASK_MI, (szCb.init.prntBuf, "Status NOK\n"));
      cfmInfo.status.status = LCM_PRIM_NOK;
   }
   else
   {
      cfmInfo.status.status = LCM_PRIM_OK;
   }

   SzMiShtCntrlCfm(&repPst, &cfmInfo); /* send the response */

   RETVALUE(ROK);
} /* end SzMiShtCntrlReq */
#endif /* SZ_FTHA */

/**********************************************************************

         End of file:     sq_mi.c@@/main/4 - Mon Jan 10 22:17:01 2011

**********************************************************************/

/**********************************************************************
        Revision History:

**********************************************************************/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/4      ---        pkaX   1. Updated for S1AP release 3.1
/main/4     sz002.301   pkaX   1. Removed the unused member in the 
                                  structure
                               2. suAssocId is updated during peer 
                                  configuration itself.
                               3. spAssocId is assigned instead of suAssocId in
                                  peerSta.
/main/4   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
/main/4   sz004.301   va    1. Removed the validation check for peer state
/main/4   sz005.301   va    1. Updated for sctsap insertion and deletion
                                 id mismatch
/main/4   sz006.301   ve    1. Removed un-necessary include files
/main/4   sz008.301  akaranth 1.Support for source RNC to target RNC.
                              2.Change for Diagnostics.
                              3.Removed the redundant code.
*********************************************************************91*/
