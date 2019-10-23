


/********************************************************************20**

     Name:     S1AP Layer 
  
     Type:     C source file
  
     Desc:     C Source code

     File:     sz_ex_ms.c

     Sid:      sq_ex_ms.c@@/main/4 - Mon Jan 10 22:16:57 2011

     Prg:      sn

*********************************************************************21*/

/* Header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* General */
#include "ssi.h"           /* System Services */
#include "cm_tkns.h"       /* common tokens */
#include "cm_hash.h"       /* common structs 1 */
#include "cm_mblk.h"       /* common memory */
#include "cm_llist.h"      /* cm link list */
#include "cm5.h"           /* common structs 3 */
#include "cm_inet.h"       /* common tokens  */
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport */
#include "cm_pasn.h"
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_psfft.h"
#include "cm_ftha.h"
#include "cm_pftha.h"
#include "cm_psf.h"
#endif /* SZ_FTHA */

#include "sct.h"           /* SCTP Layer */
#include "szt.h"           /* S1AP Upper Interface */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "sht.h"           /* System Agent */
#endif  /* SZ_FTHA */
#ifdef YT
#include "lyt.h"           /* PSF-S1AP LM Interface */
#include "yt.h"            /* PSF-S1AP Layer */
#endif  /* YT */
#include "lsz.h"           /* S1AP LM Interface */
#include "sz.h"            /* S1AP Layer */
#include "sz_err.h"        /* S1AP Error */
#include "szt_asn.h"       /* S1AP ASN */
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.h"
#endif

/* Header include files (.x) */
#include "gen.x"           /* General */
#include "ssi.x"           /* System Services */
#include "cm_tkns.x"       /* common tokens */
#include "cm_hash.x"       /* common structs 1 */
#include "cm_lib.x"        /* common library */
#include "cm_mblk.x"       /* common memory */
#include "cm_llist.x"      /* cm link list */
#include "cm5.x"           /* common structs 3 */
#include "cm_inet.x"       /* common transport */
#include "cm_tpt.x"        /* common transport */
#include "cm_pasn.x"
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_pftha.x"
#include "cm_psf.x"
#endif /* SZ_FTHA */
/* sz006.301: Removed un-necessary include files  */
#include"szt_asn.x"        /* common ss7 */
#ifndef SZ_ENC_DEC
#include "szt_pk.x"
#include "szt_unpk.x"
#endif /* SZ_ENC_DEC */

#include "sct.x"           /* SCTP Layer */
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.x"
#endif
#include "szt.x"           /* S1AP Upper Interface */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "sht.x"           /* System Agent */
#endif  /* SZ_FTHA */
#ifdef YT
#include "lyt.x"           /* PSF-S1AP LM Interface */
#include "yt.x"            /* PSF-S1AP Layer */
#endif  /* YT */
#include "lsz.x"           /* S1AP LM Interface */
#include "sz.x"            /* S1AP Layer */
#include "szt_asn.x"       /* S1AP ASN */

#ifdef SZ_PHASE2
/* local function definition */
EXTERN S16 szInitExt  ARGS((Void));
#endif

/* functions in other modules */

/* public variable declarations */

/* control variables for testing */

/* private variable declarations */

/*
 * support functions
 */

#ifdef SZ_PHASE2

/*
 *
 *       Fun  : initialize external
 *
 *       Desc : Initializes variables used to interface with Upper/Lower
 *              Layer
 *
 *       Ret  : ROK  - ok
 *
 *       Notes: None
 *
 *       File : ra_ex_ms.c
 *
 */
#ifdef ANSI
PUBLIC S16 szInitExt
(
Void
)
#else
PUBLIC S16 szInitExt()
#endif
{
   TRC2(szInitExt)

   RETVALUE(ROK);

} /* end of szInitExt */

#endif /* SZ_PHASE2 */


/*
 *
 *       Fun  :  activate task
 *
 *       Desc :  All loosely coupled messages that are received by RANAP
 *               arrive at this point. This includes loosely coupled layer 
 *               management requests and loosely coupled messages arriving 
 *               from the service user and service provider(s).
 *
 *       Ret  :  ROK  - ok
 *
 *       Notes:  None
 *
 *       File :  sq_ex_ms.c
 *
 */
#ifdef ANSI
PUBLIC S16 szActvTsk
(
Pst     *pst,                                   /* post structure       */
Buffer  *mBuf                                   /* message buffer       */
)
#else
PUBLIC S16 szActvTsk(pst, mBuf)
Pst     *pst;                                   /* post structure       */
Buffer  *mBuf;                                  /* message buffer       */
#endif
{
   Mem sMem;
   S16 ret = RFAILED;

   TRC3(szActvTsk);

#ifdef SS_MULTIPLE_PROCS
   if(((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&szCbPtr))
                 !=ROK)||( szCbPtr == NULLP))
   {

#if (ERRCLASS & ERRCLS_INT_PAR)
      SLOGERROR(pst->dstEnt, pst->dstInst, pst->dstProcId,__FILE__, __LINE__,\
                ERRCLS_INT_PAR,ESZ001,0,"szActvTsk() failed, cannot derive szCb");
#endif /* ERRCLASS & ERRCLS_INT_PAR */
      SPutMsg(mBuf);
      RETVALUE(FALSE);
   }

#endif /*SS_MULTIPLE_PROCS */

   sMem.region = szCb.init.region;
   sMem.pool = szCb.init.pool;

   switch(pst->srcEnt)
   {
      /* The originator of this message is the stack manager,
       * unpack and go to the respective primitive processing function */
#ifdef LCLSZ
      case ENTSM:
      {
         switch(pst->event)
         {
            case EVTLSZCFGREQ:
               /* Process a config. request */
               cmUnpkLszCfgReq(SzMiLszCfgReq, pst, mBuf);
               break;
            case EVTLSZCNTRLREQ:
               /* Process a control request */
               cmUnpkLszCntrlReq(SzMiLszCntrlReq, pst, mBuf);
               break;
            case EVTLSZSTAREQ:
               /* Process a status request  */
               cmUnpkLszStaReq(SzMiLszStaReq, pst, mBuf);
               break;
            case EVTLSZSTSREQ:
               /* Process a statistics request */
               cmUnpkLszStsReq(SzMiLszStsReq, pst, mBuf);
               break;
            default:
               /* sz003.301: Updted for PSF-S1AP 3.1 release. Added the PSF
                * actv task function for incoming event  */
#ifdef YT      /* If the event is not for the layer then it will fwd to PSF*/
               ytActvTsk(pst, mBuf);
#endif /* YT */
               break;
         }
         break;
      }
#endif /* LCLSZ */

#ifdef LCSCT
      case ENTSB:
      case ENTHI:
      {
         switch(pst->event)
         {   
            /* Bind confirm */
            case SCT_EVTBNDCFM:
               ret = cmUnpkSctBndCfm(SzLiSctBndCfm, pst, mBuf);
               break;
            /* Assoc. Establishment indication */
            case SCT_EVTASSOCIND:
               ret = cmUnpkSctAssocInd(SzLiSctAssocInd, pst, mBuf);
               break;
            /* Assoc. Establishment confirmation */
            case SCT_EVTASSOCCFM:
               ret = cmUnpkSctAssocCfm(SzLiSctAssocCfm, pst, mBuf);
               break;
            /* Association Termination indication */
            case SCT_EVTTERMIND:
               ret = cmUnpkSctTermInd(SzLiSctTermInd, pst, mBuf);
               break;
            /* Assoc. Termination confirmation */
            case SCT_EVTTERMCFM:
               ret = cmUnpkSctTermCfm(SzLiSctTermCfm, pst, mBuf);
               break;
#ifdef SZ_PHASE2 
            /* Set Primary confirmation */
            case SCT_EVTSETPRICFM:
               ret = cmUnpkSctSetPriCfm(SzLiSctSetPriCfm, pst, mBuf);
               break;
            /*Set heartbeat confirmation */
            case SCT_EVTHBEATCFM:
               ret = cmUnpkSctHBeatCfm(SzLiSctHBeatCfm, pst, mBuf);
               break;
            /* Status confirm */
            case SCT_EVTSTACFM:
               ret = cmUnpkSctStaCfm(SzLiSctStaCfm, pst, mBuf);
               break;
#endif /* SZ_PHASE2 */             
            /* Data Indication */
            case SCT_EVTDATIND:
               ret = cmUnpkSctDatInd(SzLiSctDatInd, pst, mBuf);
               break;
            /* Status Indication */
            case SCT_EVTSTAIND:
               ret = cmUnpkSctStaInd(SzLiSctStaInd, pst, mBuf);
               break;
            /* Flow control indication */
            case SCT_EVTFLCIND:
               ret = cmUnpkSctFlcInd(SzLiSctFlcInd, pst, mBuf);
               break;
            /* Endpoint open confirmation */
            case SCT_EVTENDPOPENCFM:
               ret = cmUnpkSctEndpOpenCfm(SzLiSctEndpOpenCfm, pst, mBuf);
               break;
            /* Endpoint close confirmation */
            case SCT_EVTENDPCLOSECFM:
               ret = cmUnpkSctEndpCloseCfm(SzLiSctEndpCloseCfm, pst, mBuf);
               break;

            default:
            {
#if (ERRCLASS & ERRCLS_DEBUG)
               if (pst->event == ENTSB)
               {
                  SZLOGERROR(ERRCLS_DEBUG, ESZ003, (ErrVal) pst->event,
                    "szActvTsk: Invalid event specified for srcEnt (ENTSB).");
               }
               if (pst->event == ENTHI)
               {
                  SZLOGERROR(ERRCLS_DEBUG, ESZ004, (ErrVal) pst->event,
                    "szActvTsk: Invalid event specified for srcEnt (ENTHI).");
               }

#endif /* (ERRCLASS & ERRCLS_DEBUG) */
               SPutMsg(mBuf);
               break;
            }
         }
         break;
      }
#endif /* LCSCT */

#if (defined(LCSZT) || defined(LWLCSZT))
      case ENTUZ:
      {
         switch (pst->event)
         {
            case EVTSZTBNDREQ:
               cmUnpkSztBndReq(SzUiSztBndReq, pst, mBuf);
               break;
            case EVTSZTUBNDREQ:
               cmUnpkSztUbndReq(SzUiSztUbndReq, pst, mBuf);
               break;
            case EVTSZTCONREQ:
               cmUnpkSztConReq(SzUiSztConReq, pst, mBuf, &sMem);
               break;
            case EVTSZTCONRSP:
               cmUnpkSztConRsp(SzUiSztConRsp, pst, mBuf, &sMem);
               break;
            case EVTSZTRELREQ:
               cmUnpkSztRelReq(SzUiSztRelReq, pst, mBuf, &sMem);
               break;
            case EVTSZTRELRSP:
               cmUnpkSztRelRsp(SzUiSztRelRsp, pst, mBuf, &sMem);
               break;
            case EVTSZTDATREQ:
               cmUnpkSztDatReq(SzUiSztDatReq, pst, mBuf, &sMem);
               break;
            case EVTSZTUDATREQ:
               cmUnpkSztUDatReq(SzUiSztUDatReq, pst, mBuf, &sMem);
               break;
            case EVTSZTENCDECREQ:
               cmUnpkSztEncDecReq(SzUiSztEncDecReq, pst, mBuf, &sMem);
               break;
            case EVTSZTAUDREQ:
               cmUnpkSztAudReq(SzUiSztAudReq,  pst, mBuf, &sMem);
               break;
/* sz005.301 Added for S1 Abort request support by UI */
#ifdef SZTV2
            case EVTSZTABORTS1REQ:
               cmUnpkSztAbortS1Req(SzUiSztAbortS1Req, pst, mBuf);
               break;
#endif /* SZTV2 */               
            default:
#if (ERRCLASS & ERRCLS_DEBUG)
               SZLOGERROR(ERRCLS_DEBUG, ESZ005, (ErrVal) 0,
              "Invalid event from Upper Interface: szActvTsk Failed");
#endif /* ERRCLASS & ERRCLS_DEBUG */
               SPutMsg(mBuf);
               break;
         }
         break;
      }
#endif 
      /* sz003.301: Updted for PSF-S1AP 3.1 release. Added the PSF
       * actv task function for incoming event  */
#ifdef SZ_FTHA
      case ENTSH:   /* events from system agent */
         switch (pst->event)
         {
            case EVTSHTCNTRLREQ:  /* system agent control request */
               /* call unpacking function */
               cmUnpkMiShtCntrlReq(SzMiShtCntrlReq, pst, mBuf);
               break;
            default:
               /* If the event is not for the layer then it will fwd to PSF*/
               ytActvTsk(pst, mBuf);
               break;
         }
      break;

      case ENTSZ:
         /* If the event is not for the layer then it will fwd to PSF*/
         ytActvTsk(pst, mBuf);
         break;
#endif /* SZ_FTHA */

      default:
#if (ERRCLASS & ERRCLS_DEBUG)
        SZLOGERROR(ERRCLS_DEBUG, ESZ006, (ErrVal) 0, 
              "Event Received from Invalid Entity : szActvTsk Failed");
#endif /* ERRCLASS & ERRCLS_DEBUG */
        SPutMsg(mBuf);
        break;

   } /* end switch */

   SExitTsk();
   RETVALUE(ROK);

} /* end of szActvTsk */

/********************************************************************30**
 
         End of file:     sq_ex_ms.c@@/main/4 - Mon Jan 10 22:16:57 2011
 
*********************************************************************31*/
 
/********************************************************************40**
 
        Notes:
 
*********************************************************************41*/
 
/********************************************************************50**
 
*********************************************************************51*/
 
/********************************************************************60**
 
        Revision history:
 
*********************************************************************61*/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/4      ---      pkaX   1. Updated for S1AP release 3.1
/main/4   sz003.301   pka    1. Updated for PSF-S1AP 1.1 release
/main/4   sz005.301   va     1. Updated for S1 Abort request support by UI
/main/4   sz006.301   ve    1. Removed un-necessary include files
/main/4   sz008.301  akaranth 1.Support for source RNC to target RNC.
*********************************************************************91*/
