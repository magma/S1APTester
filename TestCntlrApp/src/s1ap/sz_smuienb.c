

/********************************************************************20**

     Name:     S1AP Layer

     Type:     C source file

     Desc:     C Source code for upper interface state machine on EnodeB

     File:     sq_smuienb.c

     Sid:      sq_smuienb.c@@/main/4 - Mon Jan 10 22:17:07 2011

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
#include "sct.h"           /* SCTP Layer */
#include "szt.h"           /* S1AP Upper Interface */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_pftha.h"
#include "cm_psf.h"
#include "sht.h"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.h"           /* S1AP LM Interface */
#include "sz.h"            /* S1AP Layer */
#include "sz_err.h"
#include "cm_pasn.h"
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
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_pftha.x"
#include "cm_psf.x"
#include "sht.x"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.x"           /* S1AP LM Interface */
#include "cm_pasn.x"
#include "sz.x"            /* S1AP Layer */

#ifdef SZ_ENB
#ifdef __cplusplus
EXTERN "C" {
#endif
PUBLIC S16 szSmSndUeCtxRlsCmp ARGS((SzConCb *conCb,SzPeerCb *peerCb,S1apPdu *pdu));
#ifdef __cplusplus
}
#endif

PFRAM szSmUiEnb[SZ_MAX_MSG_ID][SZ_MAX_ST] = 
{
   /* E-RAB setup request */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* E-RAB setup response */
   {
      szSmLclErrState,        /* Idle        */
      szSmLclErrState,        /* Connecting  */
      szSmSndEstStMsg,       /* Estbalished */
      szSmLclErrState         /* Releasing   */
   },
   /* E-RAB modify request */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* E-RAB modify response */
   {
      szSmLclErrState,        /* Idle        */
      szSmLclErrState,        /* Connecting  */
      szSmSndEstStMsg,       /* Estbalished */
      szSmLclErrState         /* Releasing   */
   },
   /* E-RAB release command */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* E-RAB release complete */
   {
      szSmLclErrState,        /* Idle        */
      szSmLclErrState,        /* Connecting  */
      szSmSndEstStMsg,       /* Estbalished */
      szSmLclErrState         /* Releasing   */
   },
   /* E-RAB release request */
   {
      szSmLclErrState,        /* Idle        */
      szSmLclErrState,        /* Connecting  */
      szSmSndEstStMsg,       /* Estbalished */
      szSmLclErrState         /* Releasing   */
   },
   /* Initial Context setup request */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Initial context setup response */
   {
      szSmLclErrState,        /* Idle        */
      szSmLclErrState,        /* Connecting  */
      szSmSndEstStMsg,       /* Estbalished */
      szSmLclErrState         /* Releasing   */
   },
   /* Initial context setup failure */
   {
      szSmLclErrState,        /* Idle        */
      szSmLclErrState,        /* Connecting  */
      szSmSndEstStMsg,       /* Estbalished */
      szSmLclErrState         /* Releasing   */
   },
   /* UE Context release request */
   {
      szSmLclErrState,        /* Idle        */
      szSmLclErrState,        /* Connecting  */
      szSmSndEstStMsg,       /* Estbalished */
      szSmLclErrState         /* Releasing   */
   },
   /* UE Context release command */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* UE Context release complete */
   {
      szSmLclErrState,        /* Idle        */
      szSmLclErrState,        /* Connecting  */
      szSmLclErrState,        /* Estbalished */
      szSmSndUeCtxRlsCmp     /* Releasing   */
   },
   /* UE Context Modification request */
    {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* UE Context Modification response */
   {
      szSmLclErrState,        /* Idle        */
      szSmLclErrState,        /* Connecting  */
      szSmSndEstStMsg,       /* Estbalished */
      szSmLclErrState         /* Releasing   */
   },
   /* UE Context Modification failure */
   {
      szSmLclErrState,        /* Idle        */
      szSmLclErrState,        /* Connecting  */
      szSmSndEstStMsg,       /* Estbalished */
      szSmLclErrState         /* Releasing   */
   },
   /* Initial UE message */
   {
      szSmSndIdleStMsg,     /* Idle        */
      szSmLclErrState,      /* Connecting  */
      szSmLclErrState,      /* Estbalished */
      szSmLclErrState       /* Releasing   */
   },
   /* Downlink NAS transport */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Uplink NAS transport */
   {
      szSmLclErrState,      /* Idle        */
      szSmSndConnStMsg,     /* Connecting  */
      szSmSndEstStMsg,      /* Estbalished */
      szSmLclErrState       /* Releasing   */
   },
   /* NAS non delivery indication */
   {
      szSmLclErrState,        /* Idle        */
      szSmLclErrState,        /* Connecting  */
      szSmSndEstStMsg,       /* Estbalished */
      szSmLclErrState         /* Releasing   */
   },
   /* Error Indication */
   {
      szSmLclErrState,        /* Idle        */
      szSmLclErrState,        /* Connecting  */
      szSmSndEstStMsg,       /* Estbalished */
      szSmLclErrState         /* Releasing   */
   },
   /* No Data */
   {
      szSmLclErrState,        /* Idle        */
      szSmLclErrState,        /* Connecting  */
      szSmLclRlsReq,         /* Estbalished */
      szSmLclRlsReq          /* Releasing   */
   },
   /* Reset */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Reset Acknowledge */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Setup Request */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Setup Response */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Setup Fail */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Paging */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Handover Required */
   {
      szSmLclErrState,        /* Idle        */
      szSmLclErrState,        /* Connecting  */
      szSmSndEstStMsg,        /* Estbalished */
      szSmLclErrState         /* Releasing   */
   },
   /* Handover Command */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Handover Preperation Failure */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Handover Request */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Handover Request Acknowledge */
   {
      szSmLclErrState,      /* Idle        */
      szSmSndConnStMsg,     /* Connecting  */
      szSmLclErrState,      /* Estbalished */
      szSmLclErrState       /* Releasing   */
   },
   /* Handover Request Failure */
   {
      szSmLclErrState,      /* Idle        */
      szSmSndConnStHoFail,  /* Connecting  */
      szSmLclErrState,      /* Estbalished */
      szSmLclErrState       /* Releasing   */
   },
   /* Handover Notify */
   {
      szSmLclErrState,        /* Idle        */
      szSmLclErrState,        /* Connecting  */
      szSmSndEstStMsg,        /* Estbalished */
      szSmLclErrState         /* Releasing   */
   },
   /* Path Switch Request */
   {
      szSmSndIdleStMsg,     /* Idle        */
      szSmLclErrState,      /* Connecting  */
      szSmLclErrState,      /* Estbalished */
      szSmLclErrState       /* Releasing   */
   },
   /* Path Switch Request Acknowledge */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Path Switch Request Failure */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Handover Cancel */
   {
      szSmLclErrState,        /* Idle        */
      szSmLclErrState,        /* Connecting  */
      szSmSndEstStMsg,        /* Estbalished */
      szSmLclErrState         /* Releasing   */
   },
   /* Handover Cancel Acknowledge */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* ENB Status Transfer */
   {
      szSmLclErrState,        /* Idle        */
      szSmLclErrState,        /* Connecting  */
      szSmSndEstStMsg,        /* Estbalished */
      szSmLclErrState         /* Releasing   */
   },
   /* MME Status Transfer */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Deactivate Trace */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Trace Start */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Trace Failure Indication */
   {
      szSmLclErrState,        /* Idle        */
      szSmLclErrState,        /* Connecting  */
      szSmSndEstStMsg,        /* Estbalished */
      szSmLclErrState         /* Releasing   */
   },
   /* Location Reporting Control */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Location Report Failure Indication */
   {
      szSmLclErrState,        /* Idle        */
      szSmLclErrState,        /* Connecting  */
      szSmSndEstStMsg,        /* Estbalished */
      szSmLclErrState         /* Releasing   */
   },
   /* Location Report */
   {
      szSmLclErrState,        /* Idle        */
      szSmLclErrState,        /* Connecting  */
      szSmSndEstStMsg,        /* Estbalished */
      szSmLclErrState         /* Releasing   */
   },
   /* ENB Configuration Update */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* ENB Configuration Update Acknowledge */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* ENB Configuration Update Failure */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* MME Configuration Update */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* MME Configuration Update Acknowledge */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* MME Configuration Update Failure */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Uplink Cdma 2000 Tunneling */
   {
      szSmLclErrState,        /* Idle        */
      szSmLclErrState,        /* Connecting  */
      szSmSndEstStMsg,        /* Estbalished */
      szSmLclErrState         /* Releasing   */
   },
   /* Downlink Cdma 2000 Tunneling */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* UE Capability Info  */
   {
      szSmLclErrState,        /* Idle        */
      szSmLclErrState,        /* Connecting  */
      szSmSndEstStMsg,        /* Estbalished */
      szSmLclErrState         /* Releasing   */
   },
   /* Overload Start */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Overload Stop */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Write Replace Warning Request */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Write Replace Warning Response */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* ENB Information Direct Transfer */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* MME Information Direct Transfer */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /*  Private Message */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* ENB Configuration Transfer */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* MME Configuration Transfer */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Cell Traffic Trace */
   {
      szSmLclErrState,      /* Idle        */
      szSmLclErrState,      /* Connecting  */
      szSmSndEstStMsg,      /* Estbalished */
      szSmLclErrState       /* Releasing   */
   }
#ifndef S1AP_REL8A0
   ,
   /* Kill Request */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Established */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Kill Response */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Established */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Downlink UE Associated LPPa Transport */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Established */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Uplink UE Associated LPPa Transport */
   {
      szSmLclErrState,      /* Idle        */
      szSmLclErrState,      /* Connecting  */
      szSmSndEstStMsg,      /* Established */
      szSmLclErrState       /* Releasing   */
   },
   /* Downlink non-UE Associated LPPa Transport */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Established */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Uplink non-UE Associated LPPa Transport */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Established */
      szSmLclErrMsg         /* Releasing   */
   }
#endif /* S1AP_REL8A0 */
};

/*
*
*       Fun:   szSmSndUeCtxRlsCmp
*
*       Desc:  Called to send UE Context release complete
*
*       Ret:   ok:     ROK
*              failed: RFAILED
*
*       Notes: None
*
*       File:  sz_smuienb.c
*
*/

#ifdef ANSI
PUBLIC S16 szSmSndUeCtxRlsCmp
(
SzConCb  *conCb,
SzPeerCb *peerCb,
S1apPdu  *pdu
)
#else
PUBLIC S16 szSmSndUeCtxRlsCmp(conCb, peerCb, pdu)
SzConCb  *conCb;
SzPeerCb *peerCb;
S1apPdu  *pdu;
#endif
{
   S16 ret = RFAILED;

   TRC2(szSmSndUeCtxRlsCmp)

   /* Send decoded data to its User */
   ret = szLiSndToLower(peerCb,conCb, pdu);
   if(ret != ROK)
   {
      if((ret == SZT_CAUSE_PC_TX_SYNTAX_ERR) || 
            (ret == SZT_CAUSE_PC_ABS_SYNTAX_ERR))
      {
         SZ_SEND_LCL_ERR_IND(PRSNT_NODEF, conCb->cd.suConnId,
               peerCb->sztSapCb, ret, 0);
      }
      else
      {
         SZ_SEND_LCL_ERR_IND(PRSNT_NODEF, conCb->cd.suConnId, 
               peerCb->sztSapCb, SZT_CAUSE_LOWER_LAYER_SND_FAILED, 0);
      }

      SZ_FREE_SDU(pdu);
#if (ERRCLASS & ERRCLS_DEBUG)
      SZLOGERROR(ERRCLS_DEBUG, ESZ160, (ErrVal) conCb->lclConRefNo,
            "szSmSndUeCtxRlsCmp: Lower Interface send failed");
#endif
   }
   /* Deallocate connection control block */
   ret = szNdbDeallocConCb(conCb->lclConRefNo,peerCb, SZ_CONN_REF_LCL);
#if (ERRCLASS & ERRCLS_DEBUG)
   if(ret == RFAILED)
   {
      SZLOGERROR(ERRCLS_DEBUG, ESZ161, (ErrVal) conCb->lclConRefNo,
           "szSmSndUeCtxRlsCmp: Couldn't retreive connection CB");
   }
#endif
   RETVALUE(ret);
} /* end of szSmSndUeCtxRlsCmp */

#endif

/**********************************************************************
 
         End of file:     sq_smuienb.c@@/main/4 - Mon Jan 10 22:17:07 2011
 
**********************************************************************/

/********************************************************************40**
 
        Notes:
 
*********************************************************************41*/

/********************************************************************50**
 
*********************************************************************51*/

/********************************************************************60**
 
        Revision history:
 
*********************************************************************61*/

/********************************************************************80**
 
*********************************************************************81*/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/4      ---      vvashishth  1. Updated for S1AP release 3.1
/main/4   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
/main/4   sz006.301   ve    1. Removed un-necessary include files
/main/4   sz008.301 akaranth 1. Support for source RNC to target RNC.
*********************************************************************91*/
