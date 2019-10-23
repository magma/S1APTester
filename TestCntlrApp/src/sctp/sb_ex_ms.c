

/********************************************************************20**

     Name:    SCTP - external - mos

     Type:    C source file

     Desc:    Functions required for scheduling and initialization.


     File:    sb_ex_ms.c

     Sid:      sb_ex_ms.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:15 2015

     Prg:     bk, wvdl

*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm_hash.h"       /* common hashing */
#include "cm_llist.h"      /* common linked list */
#include "cm5.h"           /* common timer */
#include "lsb.h"           /* layer management SB */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"        /* common DNS */
#ifdef SB_FTHA
#include "sht.h"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "sct.h"           /* sct interface */
#include "hit.h"           /* hit interface */
#include "sb_mtu.h"
#include "sb.h"            /* SCTP defines */
#include "sb_err.h"        /* SB error */

/* header/extern include files (.x) */
#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */
#include "cm_hash.x"       /* common hashing */
#include "cm_llist.x"      /* common linked list */
#include "cm5.x"           /* common timer */
#include "cm_tpt.x"        /* common transport address */
#include "cm_dns.x"        /* common DNS */
#ifdef SB_FTHA
#include "sht.x"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "hit.x"           /* hit interface */
#include "sct.x"           /* sct interface */
#include "lsb.x"           /* layer management SCTP */
#include "sb_mtu.x"
#include "sb.x"            /* SCTP typedefs */


/* local defines */

/* local typedefs */

/* local externs */

/* functions in other modules */

/* public variable declarations */

/* private variable declarations */


/*
*     support functions
*/

/* ------------------------------------------------------------ */


/*
*
*       Fun:    initialize external
*
*       Desc:   Initializes variables used to interface with Upper/Lower
*               Layer
*
*       Ret:    ROK  - ok
*
*       Notes:  None
*
*       File:   sb_ex_ms.c
*
*/

#ifdef ANSI
PUBLIC S16 sbInitExt
(
void
)
#else
PUBLIC S16 sbInitExt()
#endif
{
   TRC2(sbInitExt)

   RETVALUE(ROK);

} /* end of sbInitExt */



/*
*
*       Fun:    activation task
*
*       Desc:   Processes received event from Upper/Lower Layer
*
*       Ret:    ROK  - ok
*
*       Notes:  This function notifies the SB layer of a posted message
*
*       File:   sb_ex_ms.c
*
*/

#ifdef ANSI
PUBLIC S16 sbActvTsk
(
Pst    *pst,                /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 sbActvTsk(pst, mBuf)
Pst    *pst;                /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   S16 ret;
   /* Patch sb031.102 IPV6 Support Added */
#ifdef IPV6_OPTS_SUPPORTED
   Mem memInfo;             /* meminfo for cmUnpkCmIphdrParm() */

#ifdef SS_MULTIPLE_PROCS

   if(SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                          (void **)&sbGlobalCbPtr) != ROK)
   {
     SBLOGERROR(ERRCLS_DEBUG, ESB313, 0,
               "sbActvTsk () failed, cannot derive sbGlobalCbPtr");
     RETVALUE(FALSE);
   }

   SBDBGP(DBGMASK_SI, (sbGlobalCb.sbInit.prntBuf,
         "-------SCTP------(proc(%d), ent(%d), inst(%d))--------\n",
         pst->dstProcId, pst->dstEnt, pst->dstInst));

#endif /* SS_MULTIPLE_PROCS */
#endif /* IPV6_OPTS_SUPPORTED */

   TRC3(sbActvTsk)

   ret = ROK;

   /* call the unpacking function, depending on source entity and event type */

   switch(pst->srcEnt)
   {
     /* sb001.12 : addition - Case for ENDID - IUA added */
     /* sb016.102 : addition - Case for ENTSU & ENTMW */
     /* sb048.102 : addition - GCP & Dummy are added as new SCTP user */
     /* sb052.102 : NBAP (ENTIB) and M1UA (ENTMZ) added as new SCTP user */
     /* sb079.102 : SIP (ENTSO) added as new SCTP user */
     /* sb016.103 : S1AP (ENTSZ) added as new SCTP user */
     /* sb025.103 : X2AP (ENTCZ) added as new SCTP user */
     /* sb027.103 : Iuh (ENTHM) added as new SCTP user */
      case ENTMG:
      case ENTDM:
      case ENTMW:
      case ENTSU:
      case ENTID:
      case ENTIT:
      case ENTIB:
      case ENTMZ:
      case ENTSO:
      /* sb001.103 :  case for ENTAQ - Diameter added */
      case ENTAQ:
     /* sb003.103: Case for ENTMX - M2PA added */
      case ENTMX:
      case ENTSZ:
      case ENTCZ:
      case ENTHM:
      {

#ifdef LCSBUISCT          /* loosely coupled SCT interface */
         switch(pst->event)
         {
            case  SCT_EVTBNDREQ:                 /* bind request */
               ret = cmUnpkSctBndReq(SbUiSctBndReq, pst, mBuf);
               break;

            case  SCT_EVTASSOCREQ:               /* association request */
               ret = cmUnpkSctAssocReq(SbUiSctAssocReq, pst, mBuf);
               break;

            case  SCT_EVTASSOCRSP:               /* association responce */
               ret = cmUnpkSctAssocRsp(SbUiSctAssocRsp, pst, mBuf);
               break;

            case  SCT_EVTTERMREQ:                /* termination request */
               ret = cmUnpkSctTermReq(SbUiSctTermReq, pst, mBuf);
               break;

            case  SCT_EVTSETPRIREQ:              /* set primary DTA request */
               ret = cmUnpkSctSetPriReq(SbUiSctSetPriReq, pst, mBuf);
               break;

            case  SCT_EVTHBEATREQ:               /* heartbeat request */
               ret = cmUnpkSctHBeatReq(SbUiSctHBeatReq, pst, mBuf);
               break;

            case  SCT_EVTDATREQ:                 /* data request */
               ret = cmUnpkSctDatReq(SbUiSctDatReq, pst, mBuf);
               break;

            case  SCT_EVTSTAREQ:                 /* status request */
               ret = cmUnpkSctStaReq(SbUiSctStaReq, pst, mBuf);
               break;

            case  SCT_EVTENDPOPENREQ:            /* endpoint open request */
               ret = cmUnpkSctEndpOpenReq(SbUiSctEndpOpenReq, pst, mBuf);
               break;

            case  SCT_EVTENDPCLOSEREQ:           /* endpoint close request */
               ret = cmUnpkSctEndpCloseReq(SbUiSctEndpCloseReq, pst, mBuf);
               break;

            default:
/*sb005.103: Replaced SB_PUTMSG with SB_CHK_PUTMSG */
               SB_CHK_PUTMSG(mBuf);

#if (ERRCLASS & ERRCLS_DEBUG)
               SBLOGERROR(ERRCLS_DEBUG, ESB314, (ErrVal)pst->event,
                          "[SCT] sbActvTsk: Invalid Event from service user" );
#endif

               ret = RFAILED;
               break;

         }/* end switch */
         break;

#endif /* LCSBUISCT */
      }
      break;

      case ENTHI:
      {
#ifdef LCSBLIHIT          /* loosely coupled HIT interface */

         switch(pst->event)
         {
            case  EVTHITBNDCFM:             /* bind confirm */
               ret = cmUnpkHitBndCfm(SbLiHitBndCfm, pst, mBuf);
               break;

            case  EVTHITCONCFM:             /* connection confirm */
               ret = cmUnpkHitConCfm(SbLiHitConCfm, pst, mBuf);
               break;

            case  EVTHITUDATIND:            /* unit data indication */
              /* Patch sb031.102 IPV6 Support Added */
#ifdef IPV6_OPTS_SUPPORTED
              memInfo.region = sbGlobalCb.sbInit.region;
              memInfo.pool = sbGlobalCb.sbInit.pool;
              ret = cmUnpkHitUDatInd(SbLiHitUDatInd, pst, mBuf, &memInfo);
#else
               ret = cmUnpkHitUDatInd(SbLiHitUDatInd, pst, mBuf);
#endif
               break;

            case  EVTHITDISCIND:            /* disconnect indication */
               ret = cmUnpkHitDiscInd(SbLiHitDiscInd, pst, mBuf);
               break;

            case EVTHITDISCCFM:             /* disconnection confirm */
               ret = cmUnpkHitDiscCfm(SbLiHitDiscCfm, pst,mBuf);
               break;

            default:
               SB_CHK_PUTMSG(mBuf);

#if (ERRCLASS & ERRCLS_DEBUG)
               SBLOGERROR(ERRCLS_DEBUG, ESB315, (ErrVal)pst->event,
                       "[HIT] sbActvTsk: Invalid Event from service provider" );
#endif

               ret = RFAILED;
               break;

         }/* end switch */
         break;
#endif /* LCSBLIHIT */
      }
      break;

      /* layer management primitives */
      case ENTSM:
      {
#ifdef LCSBMILSB     /* loosely coupled layer manager */

         switch(pst->event)
         {
            case LSB_EVTCFGREQ:       /* Configuration Request */
               ret = cmUnpkLsbCfgReq(SbMiLsbCfgReq, pst, mBuf);
               break;

            case LSB_EVTSTSREQ:       /* Statistics Request */
               ret = cmUnpkLsbStsReq(SbMiLsbStsReq, pst, mBuf);
               break;

            case LSB_EVTCNTRLREQ:     /* Control Request */
               ret = cmUnpkLsbCntrlReq(SbMiLsbCntrlReq, pst, mBuf);
               break;

            case LSB_EVTSTAREQ:       /* Status Request */
               ret = cmUnpkLsbStaReq(SbMiLsbStaReq, pst, mBuf);
               break;

            default:
               SB_CHK_PUTMSG(mBuf);

#if (ERRCLASS & ERRCLS_DEBUG)
               SBLOGERROR(ERRCLS_DEBUG, ESB316, (ErrVal)pst->event,
                          "[LSB] sbActvTsk: Invalid Event from layer manager");
#endif

               ret = RFAILED;

         }/* end of switch */
         break;
#endif /* LCSBMILSB */
      }
      break;
      /* sb042.102 - Added change for SHT interface */
#ifdef SB_FTHA
      case ENTSH:
         switch (pst->event)
         {
            case EVTSHTCNTRLREQ:     /* system agent control request */
               ret = cmUnpkMiShtCntrlReq(SbMiShtCntrlReq, pst, mBuf);
               break;
            default:
               SB_CHK_PUTMSG(mBuf);

#if (ERRCLASS & ERRCLS_DEBUG)
               SBLOGERROR(ERRCLS_DEBUG, ESB317, (ErrVal) pst->event,
               "[LSB] sbActvTsk: Invalid event for ENTSH");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
               ret = RFAILED;
               break;
         }
         break;
#endif /* SB_FTHA */

      default:
         SB_CHK_PUTMSG(mBuf);

#if (ERRCLASS & ERRCLS_DEBUG)
         SBLOGERROR(ERRCLS_DEBUG, ESB318, (ErrVal)pst->srcEnt,
                    "[LSB] sbActvTsk: Invalid source entity" );
#endif

         ret = RFAILED;
         break;

   }/* end of switch */

   /* sb042.102 - Added change for rolling upgrade */
#ifdef SB_RUG
   if ((ret == RINVIFVER) && (sbGlobalCb.sbInit.cfgDone == TRUE))
   {
      /* sb046.102 - modify the event type */
      /* sb076.102:changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm */
      SB_LM_GEN_ALARM((U16)LCM_CATEGORY_INTERFACE, \
                   (U16)LCM_EVENT_INV_EVT, \
                   (U16)LCM_CAUSE_DECODE_ERR, \
                   0, LSB_SW_RFC_REL0 );

   }
#endif /* SB_RUG */

   SExitTsk();
   RETVALUE(ret);
}/* end of sbActvTsk */


/********************************************************************30**

         End of file:     sb_ex_ms.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:15 2015

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
 /main/2     ---     bk     1. initial release.
 /main/2     ---     sb     1. Modified for SCTP release based on 
                               RFC-2960 'Oct 2000.
           sb001.12  sb     1. Entity-Id for IUA added.
           sb016.102 rs     1. Entity-Id for M2UA and SUA added.
           sb031.102 hm    1. IPV6 Support Added
           sb042.102 hl    1. Added change for SHT interface and Rolling
                              Up Grade
           sb046.102 hl    1. Modify the alarm event type
           sb048.102 rs    1. GCP & Dummy are added as new SCTP user.
           sb052.102 ag    1. ENTIB, ENTMZ added as new SCTP user.
           sb057.102 pr    1. Multiple proc ids support added.
           sb076.102 kp    1. changed sbLmGenAlarm to macro due to the
                              addition of new feild info for path alarm.
           sb079.102 kp    1. SIP (ENTSO) added as new SCTP user.
/main/3      ---   rsr/ag  1. Updated for Release of 1.3
           sb001.103 ag    1. Entity-Id ENTAQ for Diameter added.
           sb003.103 ag    1. Entity-Id ENTMX for M2PA added.
           sb005.103 ag    1. Replaced macro SB_PUTMSG with SB_CHK_PUTMSG.
           sb016.103 hsingh   1. S1AP (ENTSZ) added as new SCTP user.
           sb025.103 mm     1. X2AP (ENTCZ) added as new SCTP user.
           sb027.103 ajainx 1. Iuh (ENTHM) added as new SCTP user.
*********************************************************************91*/
