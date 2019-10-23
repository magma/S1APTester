

/********************************************************************20**

     Name:     S1AP Layer

     Type:     C source file

     Desc:     C Source code for Lower interface state machine on EnodeB

     File:     sq_smlienb.c

     Sid:      sq_smlienb.c@@/main/4 - Mon Jan 10 22:17:06 2011

     Prg:      sn

*********************************************************************21*/
/* Header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"
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
/* sz009.301 */
#include "szt_asn.h"       /* S1AP ASN */
#include "cm_pasn.h"
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.h"
#endif
#include "szt_asn.h"

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
PUBLIC S16 szSmRcvUeCtxRlsCmd ARGS((SzConCb *conCb,SzPeerCb *peerCb,S1apPdu *pdu));
#ifdef __cplusplus
}
#endif

PFRAM szSmLiEnb[SZ_MAX_MSG_ID][SZ_MAX_ST] =
{
   /* E-RAB setup request */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmRcvEstStMsg,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* E-RAB setup response */
   {
      szSmSemPeerErr,       /* Idle        */
      szSmSemPeerErr,       /* Connecting  */
      szSmSemPeerErr,       /* Estbalished */
      szSmSemPeerErr        /* Releasing   */
   },
   /* E-RAB modify request */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmRcvEstStMsg,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* E-RAB modify response */
   {
      szSmSemPeerErr,       /* Idle        */
      szSmSemPeerErr,       /* Connecting  */
      szSmSemPeerErr,       /* Estbalished */
      szSmSemPeerErr        /* Releasing   */
   },
   /* E-RAB release command */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmRcvEstStMsg,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* E-RAB release complete */
   {
      szSmSemPeerErr,       /* Idle        */
      szSmSemPeerErr,       /* Connecting  */
      szSmSemPeerErr,       /* Estbalished */
      szSmSemPeerErr        /* Releasing   */
   },
   /* E-RAB release request */
   {
      szSmSemPeerErr,       /* Idle        */
      szSmSemPeerErr,       /* Connecting  */
      szSmSemPeerErr,       /* Estbalished */
      szSmSemPeerErr        /* Releasing   */
   },
   /* Initial Context setup request */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmRcvConnStMsg,      /* Connecting  */
      szSmRcvEstStMsg,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* Initial Context setup response */
   {
      szSmSemPeerErr,       /* Idle        */
      szSmSemPeerErr,       /* Connecting  */
      szSmSemPeerErr,       /* Estbalished */
      szSmSemPeerErr        /* Releasing   */
   },
   /* Initial Context setup failure */
   {
      szSmSemPeerErr,       /* Idle        */
      szSmSemPeerErr,       /* Connecting  */
      szSmSemPeerErr,       /* Estbalished */
      szSmSemPeerErr        /* Releasing   */
   },
   /* UE Context release request */
   {
      szSmSemPeerErr,       /* Idle        */
      szSmSemPeerErr,       /* Connecting  */
      szSmSemPeerErr,       /* Estbalished */
      szSmSemPeerErr        /* Releasing   */
   },
   /* UE Context release command */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmRcvUeCtxRlsCmd,    /* Connecting  */
      szSmRcvUeCtxRlsCmd,    /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /*  UE Context release complete */
   {
      szSmSemPeerErr,       /* Idle        */
      szSmSemPeerErr,       /* Connecting  */
      szSmSemPeerErr,       /* Estbalished */
      szSmSemPeerErr        /* Releasing   */
   },
   /* UE Context modification request */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmRcvEstStMsg,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* UE Context modification response */
   {
      szSmSemPeerErr,       /* Idle        */
      szSmSemPeerErr,       /* Connecting  */
      szSmSemPeerErr,       /* Estbalished */
      szSmSemPeerErr        /* Releasing   */
   },
   /* UE Context modification failure */
   {
      szSmSemPeerErr,       /* Idle        */
      szSmSemPeerErr,       /* Connecting  */
      szSmSemPeerErr,       /* Estbalished */
      szSmSemPeerErr        /* Releasing   */
   },
   /* Initial UE message */
   {
      szSmSemPeerErr,       /* Idle        */
      szSmSemPeerErr,       /* Connecting  */
      szSmSemPeerErr,       /* Estbalished */
      szSmSemPeerErr        /* Releasing   */
   },
   /* Downlink NAS transport */
   {
      /* sz008.301: In idle case,szSmPeerErrHdlr changed with 
       * szSmIdleStPeerErr function. */
      szSmIdleStPeerErr,      /* Idle        */
      szSmRcvConnStMsg,      /* Connecting  */
      szSmRcvEstStMsg,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* Uplink NAS transport */
   {
      szSmSemPeerErr,       /* Idle        */
      szSmSemPeerErr,       /* Connecting  */
      szSmSemPeerErr,       /* Estbalished */
      szSmSemPeerErr        /* Releasing   */
   },
   /* NAS non delivery indication */
   {
      szSmSemPeerErr,       /* Idle        */
      szSmSemPeerErr,       /* Connecting  */
      szSmSemPeerErr,       /* Estbalished */
      szSmSemPeerErr        /* Releasing   */
   },
   /* Error indication */
   {
      szSmRcvIdleStErrInd,   /* Idle        */
      szSmRcvConnStErrInd,   /* Connecting  */
      szSmRcvEstStMsg,       /* Estbalished */
      szSmLclErrState        /* Releasing   */
   },
   /* No Data */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmPeerErrHdlr,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* Reset */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmPeerErrHdlr,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* Reset Acknowledge */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmPeerErrHdlr,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* Setup Request */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmPeerErrHdlr,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* Setup Response */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmPeerErrHdlr,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* Setup Fail */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmPeerErrHdlr,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* Paging */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmPeerErrHdlr,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* Handover Required */
   {
      szSmSemPeerErr,       /* Idle        */
      szSmSemPeerErr,       /* Connecting  */
      szSmSemPeerErr,       /* Estbalished */
      szSmSemPeerErr        /* Releasing   */
   },
   /* Handover Command */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmRcvEstStMsg,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* Handover Preperation Failure */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmRcvEstStMsg,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* Handover Request */
   {
      szSmRcvIdleStMsg,      /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmPeerErrHdlr,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* Handover Request Acknowledge */
   {
      szSmSemPeerErr,       /* Idle        */
      szSmSemPeerErr,       /* Connecting  */
      szSmSemPeerErr,       /* Estbalished */
      szSmSemPeerErr        /* Releasing   */
   },
   /* Handover Request Failure */
   {
      szSmSemPeerErr,       /* Idle        */
      szSmSemPeerErr,       /* Connecting  */
      szSmSemPeerErr,       /* Estbalished */
      szSmSemPeerErr        /* Releasing   */
   },
   /* Handover Notify */
   {
      szSmSemPeerErr,       /* Idle        */
      szSmSemPeerErr,       /* Connecting  */
      szSmSemPeerErr,       /* Estbalished */
      szSmSemPeerErr        /* Releasing   */
   },
   /* Path Switch Request */
   {
      szSmSemPeerErr,       /* Idle        */
      szSmSemPeerErr,       /* Connecting  */
      szSmSemPeerErr,       /* Estbalished */
      szSmSemPeerErr        /* Releasing   */
   },
   /* Path Switch Request Acknowledge */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmRcvConnStMsg,      /* Connecting  */
      szSmPeerErrHdlr,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* Path Switch Request Failure */
   {
      szSmIdleStPeerErr,          /* Idle        */
      szSmRcvConnStPathSwReqFail, /* Connecting  */
      szSmPeerErrHdlr,            /* Estbalished */
      szSmPeerErrHdlr             /* Releasing   */
   },
   /* Handover Cancel */
   {
      szSmSemPeerErr,       /* Idle        */
      szSmSemPeerErr,       /* Connecting  */
      szSmSemPeerErr,       /* Estbalished */
      szSmSemPeerErr        /* Releasing   */
   },
   /* Handover Cancel Acknowledge */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmRcvEstStMsg,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* ENB Status Transfer */
   {
      szSmSemPeerErr,       /* Idle        */
      szSmSemPeerErr,       /* Connecting  */
      szSmSemPeerErr,       /* Estbalished */
      szSmSemPeerErr        /* Releasing   */
   },
   /* MME Status Transfer */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmRcvEstStMsg,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* Deactivate Trace */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmRcvEstStMsg,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* Trace Start */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmRcvEstStMsg,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* Trace Failure Indication */
   {
      szSmSemPeerErr,       /* Idle        */
      szSmSemPeerErr,       /* Connecting  */
      szSmSemPeerErr,       /* Estbalished */
      szSmSemPeerErr        /* Releasing   */
   },
   /* Location Reporting Control */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmRcvEstStMsg,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* Location Report Failure Indication */
   {
      szSmSemPeerErr,       /* Idle        */
      szSmSemPeerErr,       /* Connecting  */
      szSmSemPeerErr,       /* Estbalished */
      szSmSemPeerErr        /* Releasing   */
   },
   /* Location Report */
   {
      szSmSemPeerErr,       /* Idle        */
      szSmSemPeerErr,       /* Connecting  */
      szSmSemPeerErr,       /* Estbalished */
      szSmSemPeerErr        /* Releasing   */
   },
   /* ENB Configuration Update */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmPeerErrHdlr,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* ENB Configuration Update Acknowledge */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmPeerErrHdlr,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* ENB Configuration Update Failure */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmPeerErrHdlr,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* MME Configuration Update */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmPeerErrHdlr,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* MME Configuration Update Acknowledge */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmPeerErrHdlr,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* MME Configuration Update Failure */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmPeerErrHdlr,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* Uplink CDMA 2000 Tunneling */
   {
      szSmSemPeerErr,       /* Idle        */
      szSmSemPeerErr,       /* Connecting  */
      szSmSemPeerErr,       /* Estbalished */
      szSmSemPeerErr        /* Releasing   */
   },
   /* Downlink CDMA 2000 Tunneling */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmRcvEstStMsg,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* UE Capability Info Indication */
   {
      szSmSemPeerErr,       /* Idle        */
      szSmSemPeerErr,       /* Connecting  */
      szSmSemPeerErr,       /* Estbalished */
      szSmSemPeerErr        /* Releasing   */
   },
   /* Overload Start */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmPeerErrHdlr,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* Overload Stop */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmPeerErrHdlr,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* Write Replace Warning Request */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmPeerErrHdlr,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* Write Replace Warning Response */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmPeerErrHdlr,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* ENB Information Direct Transfer */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmPeerErrHdlr,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* MME Information Direct Transfer */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmPeerErrHdlr,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* Private Message */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmPeerErrHdlr,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* ENB Configuration Transfer */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmPeerErrHdlr,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* MME Configuration Transfer */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmPeerErrHdlr,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* Cell Traffic Trace */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmPeerErrHdlr,       /* Estbalished */
      szSmPeerErrHdlr        /* Releasing   */
   }
#ifndef S1AP_REL8A0
   ,
   /* Kill Request */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmPeerErrHdlr,       /* Established */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* Kill Response */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmPeerErrHdlr,       /* Established */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* Downlink UE Associated LPPa Transport  */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmRcvEstStMsg,       /* Established */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* Uplink UE Associated LPPa Transport  */
   {
      szSmSemPeerErr,        /* Idle        */
      szSmSemPeerErr,        /* Connecting  */
      szSmSemPeerErr,        /* Established */
      szSmSemPeerErr         /* Releasing   */
   },
   /* Downlink non-UE Associated LPPa Transport  */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmPeerErrHdlr,       /* Established */
      szSmPeerErrHdlr        /* Releasing   */
   },
   /* Uplink non-UE Associated LPPa Transport  */
   {
      szSmIdleStPeerErr,     /* Idle        */
      szSmPeerErrHdlr,       /* Connecting  */
      szSmPeerErrHdlr,       /* Established */
      szSmPeerErrHdlr        /* Releasing   */
   }
#endif /* S1AP_REL8A0 */
};

/*
*
*       Fun:  szSmRcvUeCtxRlsCmd 
*
*       Desc:  Called to handle UE release command
*
*       Ret:   ok:     ROK
*              failed: RFAILED
*
*       Notes: None
*
*       File:  sz_smlienb.c
*
*/

#ifdef ANSI
PUBLIC S16 szSmRcvUeCtxRlsCmd 
(
SzConCb  *conCb,
SzPeerCb *peerCb,
S1apPdu  *pdu
)
#else
PUBLIC S16 szSmRcvUeCtxRlsCmd(conCb, peerCb, pdu)
SzConCb  *conCb;
SzPeerCb *peerCb;
S1apPdu  *pdu;
#endif
{
   S16 ret = RFAILED;
   SztRelInd relInd;
#ifdef SZ_ENB
   /* sz008.301 : Added supported to check MmeId in the uE_S1AP_ID_pair */
   S1apPdu        *errPdu = NULLP;     /* Response Error S1AP PDU */
   Mem            mem;                 /* Memory block */
   SztUE_S1AP_IDs *ueS1apId = NULLP;
   U16            szErrCause = 0;
   TknU32         *mmeIdTkn = NULLP; 
   mem.region = peerCb->sctSapCb->pst.region;
   mem.pool   = peerCb->sctSapCb->pst.pool;
#endif


   TRC2(szSmRcvUeCtxRlsCmd)

#ifdef SZ_ENB
      /* sz008.301: In Ue context release command message, if Sztid_UE_S1AP_IDs
       * pair is present, then eNbIdTkn and mmeIdTkn should be correct
       * if any one is wrong s1ap should send error indication message.
       * With proper cause i.e unknwon mme_ue_s1ap_id or enb_ue_s1ap_id. */
      if (peerCb->nodeType == LSZ_NODE_MME)
      {
         szGetIE(&(pdu->pdu), Sztid_UE_S1AP_IDs, (TknU8 **)&ueS1apId); 
         if (ueS1apId != NULLP)
         {
            if(ueS1apId->choice.val == UE_S1AP_IDS_UE_S1AP_ID_PAIR)
            {
               mmeIdTkn = &ueS1apId->val.uE_S1AP_ID_pair.mME_UE_S1AP_ID;

                  /* conCb is populated using a enbIdTkn. conCb->rmtConRefNo contains
                   * the mmeId. According to spec, The mmeIdTkn which is present in the 
                   * uE_S1AP_ID_pair should match with the conCb->rmtConRefNo
                   * else send the error message as invalid pair */
                  if(conCb->rmtConRefNo != mmeIdTkn->val && 
                        (conCb->state == SZ_SMSZ_ESTABLISHED) )
                  {
                     szErrCause = SztCauseRadioNwunknown_pair_ue_s1ap_idEnum; 
                     /* Call function to generate errPdu */
                     szLiErrHndlr(pdu, CAUSE_RADIONW, szErrCause, &errPdu, mem);
#ifdef LSZV1
                     /* Increment the error statistics */
                     szIncErrSts(peerCb, CAUSE_RADIONW, szErrCause);
#endif
                     /* Send decoded data to its User */
                     ret = szLiSndToLower(peerCb, conCb, errPdu);

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
                     }

                     SZ_FREE_SDU(pdu);
                     RETVALUE(RFAILED);
                  }
            }
         }
      }
#endif

   SZ_ZERO(&relInd, sizeof(SztRelInd));

   relInd.spConnId = conCb->cd.spConnId;
   /* sz008.301: Fix to handle UE context release command 
    * message in the connecting state. */
   if((conCb->state == SZ_SMSZ_ESTABLISHED) ||
      (conCb->conType == SZ_OUTGNG_CONN))
   {
      relInd.suConnId.pres = PRSNT_NODEF;
      relInd.suConnId.val = conCb->cd.suConnId;
   }
   else
   {
      relInd.suConnId.pres = NOTPRSNT;
   }
   relInd.pdu = pdu;

   /* Change the state to Releasing */
   conCb->state = SZ_SMSZ_RELEASING;

   /* Send decoded data to its User */
   ret = szUiSndRelInd(conCb, &relInd);

   RETVALUE(ret);
} /* end of szSmRcvUeCtxRlsCmd */
#endif

/**********************************************************************
 
         End of file:     sq_smlienb.c@@/main/4 - Mon Jan 10 22:17:06 2011
 
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
/main/4   sz008.301 akaranth1. Support for source RNC to target RNC.
                            2. Removed redundant code.
                            3. Added supported to check MmeId in the uE_S1AP_ID_pair.
                            4. Fix to handle the UE context release command in the connecting state.
*********************************************************************91*/
