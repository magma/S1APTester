

/********************************************************************20**

     Name:    TCP/UDP Convergence Layer

     Type:    C source file

     Desc:    External interface to SSI.

     File:    hi_ex_ms.c

     Sid:      hi_ex_ms.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Tue Aug 11 10:25:30 2015

     Prg:     asa

*********************************************************************21*/


/* header include files (.h) */

#include "envopt.h"             /* environment options */  
#include "envdep.h"             /* environment dependent */
#include "envind.h"             /* environment independent */

#include "gen.h"                /* general layer */
#include "ssi.h"                /* system services interface */

/* external headers */
#ifdef HI_TLS
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/x509v3.h>
#endif

#include "cm_hash.h"            /* common hash list */
#include "cm_llist.h"           /* common linked list */
#include "cm5.h"                /* common timer */
#include "cm_inet.h"            /* common sockets */
#include "cm_tpt.h"             /* common transport defines */

#ifdef FTHA
#include "sht.h"                /* SHT interface */
#endif

#include "lhi.h"                /* layer management, TUCL  */
#include "hit.h"                /* HIT interface */
#ifdef HI_LKSCTP
#include "sct.h"                /* SCT interface */
#endif
#include "hi.h"                 /* TUCL internal defines */
#include "hi_err.h"             /* TUCL errors */

#ifdef H323_PERF
#include "hc_prf.h"             /* performance measurement */
#endif


/* header/extern include files (.x) */

#include "gen.x"                /* general layer */
#include "ssi.x"                /* system services interface */

#include "cm_hash.x"            /* common hashing */
#include "cm_llist.x"           /* common linked list */
#include "cm_lib.x"             /* common library */
#include "cm5.x"                /* common timer */
#include "cm_inet.x"            /* common sockets */
#include "cm_tpt.x"             /* common transport typedefs */

#ifdef FTHA
#include "sht.x"                /* SHT interface */
#endif

#include "lhi.x"                /* layer management, TUCL */
#include "hit.x"                /* HIT interface */
#ifdef HI_LKSCTP
#include "sct.x"                /* SCT interface */
#endif
#include "hi.x"                 /* TUCL internal typedefs */

#ifdef H323_PERF
#include "hc_prf.x"             /* performance measurement */
#endif

PUBLIC U8 stopSchdTmr;

/*  hi004.105 Moved hiActvInit function to hi_bdy1.c for code 
*             reorganization. 
*/


/*
*
*       Fun:    hiActvTsk
*
*       Desc:   Process received events.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_ex_ms.c
*
*/
#ifdef ANSI
PUBLIC S16 hiActvTsk
(
Pst             *pst,           /* post */
Buffer          *mBuf           /* message buffer */
)
#else
PUBLIC S16 hiActvTsk(pst, mBuf)
Pst             *pst;           /* post */
Buffer          *mBuf;          /* message buffer */
#endif
{
   S16          ret = ROK;
#ifdef IPV6_OPTS_SUPPORTED    
   Mem          memInfo;
#endif
#ifdef HI_RUG
   HiAlarmInfo  info;
#endif


   TRC3(hiActvTsk);

#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId, pst->dstEnt, pst->dstInst,
                          (Void **)&hiCbPtr)) != ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId, pst->dstEnt, EHI004, 
            (ErrVal)0, pst->dstInst,
            "hiActvTsk() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }
   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt,pst->dstInst));
#endif  /* SS_MULTIPLE_PROCS */

#ifdef HI_RUG
   info.spId = -1; /* set to this value to indiacte error */
   info.type = LHI_ALARMINFO_TYPE_INFVER;
#endif


   /* check the message source */
   switch (pst->srcEnt)
   {
#ifdef LCHIMILHI
      /* stack manager primitive */
      case ENTSM:
      {
         switch (pst->event)
         {
            case EVTLHICFGREQ:
               ret = cmUnpkLhiCfgReq(HiMiLhiCfgReq, pst, mBuf);
               break;
            case EVTLHISTSREQ:
               ret = cmUnpkLhiStsReq(HiMiLhiStsReq, pst, mBuf);
               break;
            case EVTLHICNTRLREQ:
               ret = cmUnpkLhiCntrlReq(HiMiLhiCntrlReq, pst, mBuf);
               break;
            case EVTLHISTAREQ:
               ret = cmUnpkLhiStaReq(HiMiLhiStaReq, pst, mBuf);
               break;
            default:
               HILOGERROR_INT_PAR(EHI005, pst->event, pst->dstInst,
                  "hiActvTsk(): Invalid event from layer manager");
               SPutMsg(mBuf);
               ret = RFAILED;
               break;
         }
         break;
      }
#endif /* LCHIMILHI */

#if (defined(LCHIUIHIT) || (defined(HI_LKSCTP) && defined(LCHIUISCT)))

#ifdef LCHIUIHIT
      case ENTHC:
      case ENTHR:
      case ENTGT:
      case ENTMG:
      case ENTHG:
      case ENTSB:
      case ENTLN:
#ifdef DM
      case ENTDM:
#endif
#ifdef SV
      case ENTSV:
#endif
/* hi009.105 : Added FP as upper user for TUCL */
#ifdef FP
      case ENTFP:
#endif
/* hi012.105 : Added AQ as upper user for TUCL */
#ifdef AQ 
      case ENTAQ:
#endif
/* hi007.201 : Added SZ as upper user for TUCL */
#ifdef SZ 
      case ENTSZ:
#endif
#endif

#if (defined(HI_LKSCTP) && defined(LCHIUISCT))
      case ENTIT:
#endif

#if (defined(LCHIUIHIT) || (defined(HI_LKSCTP) && defined(LCHIUISCT)))
#ifdef SO
      case ENTSO:
#endif
/* hi013.201 : Addtions for eGTP protocol */
#ifdef EG
      case ENTEG:
#endif
      /* hi020.201 Added the CZ Entity for Loose Couple Mode(KSCTP)*/
#ifdef CZ
    case ENTCZ:
#endif /* CZ */
      /* hi021.201 Added the HM Entity(IUH) for Loose Couple Mode(KSCTP)*/
#ifdef HM
    case ENTHM:
#endif /* HM */
#endif
      /* hi028.201: Added support for sua DFTHA */
#ifdef SU
    case ENTSU:
#endif /* SU */

         switch (pst->event)
         {
#if (defined(HI_LKSCTP) && defined(LCHIUISCT))
             case  SCT_EVTBNDREQ:                 /* bind request */
               ret = cmUnpkSctBndReq(HiUiSctBndReq, pst, mBuf);
               break;

            case  SCT_EVTASSOCREQ:               /* association request */
               ret = cmUnpkSctAssocReq(HiUiSctAssocReq, pst, mBuf);
               break;

            case  SCT_EVTASSOCRSP:               /* association response */
               ret = cmUnpkSctAssocRsp(HiUiSctAssocRsp, pst, mBuf);
               break;

            case  SCT_EVTTERMREQ:                /* termination request */
               ret = cmUnpkSctTermReq(HiUiSctTermReq, pst, mBuf);
               break;

            case  SCT_EVTSETPRIREQ:              /* set primary DTA request */
               ret = cmUnpkSctSetPriReq(HiUiSctSetPriReq, pst, mBuf);
               break;

            case  SCT_EVTHBEATREQ:               /* heartbeat request */
               ret = cmUnpkSctHBeatReq(HiUiSctHBeatReq, pst, mBuf);
               break;

            case  SCT_EVTDATREQ:                 /* data request */
               ret = cmUnpkSctDatReq(HiUiSctDatReq, pst, mBuf);
               break;

            case  SCT_EVTSTAREQ:                 /* status request */
               ret = cmUnpkSctStaReq(HiUiSctStaReq, pst, mBuf);
               break;

            case  SCT_EVTENDPOPENREQ:            /* endpoint open request */
               ret = cmUnpkSctEndpOpenReq(HiUiSctEndpOpenReq, pst, mBuf);
               break;

            case  SCT_EVTENDPCLOSEREQ:           /* endpoint close request */
               ret = cmUnpkSctEndpCloseReq(HiUiSctEndpCloseReq, pst, mBuf);
               break;

#endif

#ifdef LCHIUIHIT
            case EVTHITBNDREQ:
               ret = cmUnpkHitBndReq(HiUiHitBndReq, pst, mBuf);
               break;

            case EVTHITUBNDREQ:
               ret = cmUnpkHitUbndReq(HiUiHitUbndReq, pst, mBuf);
               break;

            case EVTHITSRVOPENREQ:
               ret = cmUnpkHitServOpenReq(HiUiHitServOpenReq, pst, mBuf);
               break;

            case EVTHITCONREQ:
#ifdef H323_PERF
               TAKE_TIMESTAMP("L ConReq HC->HI, in HI");
#endif
               ret = cmUnpkHitConReq(HiUiHitConReq, pst, mBuf);
               break;

            case EVTHITCONRSP:
               ret = cmUnpkHitConRsp(HiUiHitConRsp, pst, mBuf);
               break;

            case EVTHITDATREQ:
#ifdef H323_PERF
               TAKE_TIMESTAMP("L DatReq HC->HI, in HI");
#endif
               ret = cmUnpkHitDatReq(HiUiHitDatReq, pst, mBuf);
               break;

            case EVTHITUDATREQ:
#ifdef H323_PERF
               TAKE_TIMESTAMP("L UDatReq HC->HI, in HI");
#endif
#ifdef IPV6_OPTS_SUPPORTED
               memInfo.region = hiCb.init.region;
               memInfo.pool = hiCb.init.pool;
               ret = cmUnpkHitUDatReq(HiUiHitUDatReq, pst, mBuf, &memInfo);
#else
               ret = cmUnpkHitUDatReq(HiUiHitUDatReq, pst, mBuf);
#endif
               break;

            case EVTHITDISCREQ:
               ret = cmUnpkHitDiscReq(HiUiHitDiscReq, pst, mBuf);
               break;

/* hi013.105 :  Added two new HIT primitives. HiUiHitTlsEstReq(), HiUiHitTlsEstCfm().*/
#ifdef HITV2
#ifdef HI_TLS
#ifdef HI_TCP_TLS
            case EVTHITTLSESTREQ:
               ret = cmUnpkHitTlsEstReq(HiUiHitTlsEstReq, pst, mBuf);
               break;
#endif /*HI_TCP_TLS */
#endif /*HI_TLS */
#endif /*HITV2 */

#endif
            default:
               HILOGERROR_INT_PAR(EHI006, pst->event, pst->dstInst,
                  "hiActvTsk(): Invalid event from service user");
               SPutMsg(mBuf);
               ret = RFAILED;
               break;
         }
         break;
#endif

      /* system agent is always loosely coupled */
      case ENTSH:
         switch (pst->event)
         {
#ifdef FTHA
            case EVTSHTCNTRLREQ:
               ret = cmUnpkMiShtCntrlReq(HiMiShtCntrlReq, pst, mBuf);
               break;
#endif

            default:
               HILOGERROR_INT_PAR(EHI007, pst->event, pst->dstInst,
                  "hiActvTsk(): Invalid event from system agent" );
               SPutMsg(mBuf);
               break;
         }
         break;

      case ENTYS:
      {
         stopSchdTmr = TRUE;
         /* KW fixes for acc compilation  */
         hiRecvTsk(pst, NULLP);
         SPutMsg(mBuf);
         break;
      }

      default:
         HILOGERROR_INT_PAR(EHI008, pst->event, pst->dstInst,
            "hiActvTsk(): Invalid source entity");
         SPutMsg(mBuf);
         ret = RFAILED;
         break;
   }


#ifdef HI_RUG
   /* primitive has invalid interface version num? */
   if (ret == RINVIFVER  &&  hiCb.init.cfgDone == TRUE)
   {
      info.spId = -1;
      info.type = LHI_ALARMINFO_TYPE_INFVER;
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_INV_EVT,
                  LCM_CAUSE_DECODE_ERR, &info);
   }
#endif


   SExitTsk();


   RETVALUE(ret);
} /* end of hiActvTsk */


/********************************************************************30**

         End of file:     hi_ex_ms.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Tue Aug 11 10:25:30 2015

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

    ver       pat     init                  description
----------- --------- ---- -----------------------------------------------
1.1         ---       asa  1. initial release.
1.1+        hi002.11  asa  1. changes for GTP.
1.1+        hi004.11  cvp  1. changes for MGCP.
1.1+        hi005.11  cvp  1. included MGCP loose coupling flag.
/main/2     ---       cvp  1. changes for Annex G.
                           2. changed the copyright header.
            /main/4   sb   1. changes for SCTP.
                      cvp  2. changes for MPLS.
/main/4+    hi003.13  cvp  1. changes for dummy layer.
/main/4+    hi006.13  bsr  1. changes for SIP layer.
/main/4     ---       cvp  1. changes for multi-threaded TUCL.
                           2. changed the copyright header.
/main/4+    hi009.104 mmh  1. passing memInfo needed to allocate memory
                              for ip hdr parameters in cmUnpkHitUDatReq. 
                           2. Rolling upgrade changes, under compile flag
                              HI_RUG as per tcr0020.txt:
                           -  Added new variable for alarm info
                           -  Fill up the alarm info structure properly
                           -  Check on return value of unpacking primitive is
                              added for alarm indication to LM in case primitive
                              is received with invalid interface version number.
                           -  added missing break in case ENTSH
/main/4+    hi020.104 rs   1. Added ENTSV as one of the users.
/main/4+    hi021.104 rs   1. Warning Removed.
/main/5      ---       kp   1. Updated for release 1.5.
/main/5+    hi002.105 ss   1. SS_MULTIPLE_PROC flags added.
/main/5+    hi004.105 ss   1. Moved hiActvInit function to hi_bdy1.c for 
                              code reorganization. 
/main/5+    hi009.105 ss   1. Added FP as upper user.
/main/5+    hi012.105 svp   1. Added AQ as upper user.
/main/5+    hi013.105 svp  1. Added two new HIT primitives.
                              HiUiHitTlsEstReq(), HiUiHitTlsEstCfm().
/main/6      ---       hs   1. Updated for release of 2.1
/main/6    hi007.201  hsingh   1. Added SZ as upper user for TUCL
                                   function hiActvTsk().
*********************************************************************91*/

