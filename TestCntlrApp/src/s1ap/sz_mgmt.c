/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */



/********************************************************************20**
 
     Name:     S1AP - Common Procedures Module
  
     Type:     C source file
  
     Desc:     C source code for Common / Management procedures Module
  
     File:     sz_mgmt.c
  
     Sid:      sq_mgmt.c@@/main/4 - Mon Jan 10 22:17:00 2011
  
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
#include "sht.h"           /* System Agent */
#endif /* SZ_FTHA */

#include "sct.h"           /* SCT interface defines           */
#include "szt.h"           /* SZT interface defines           */
/* sz006.301: Removed un-necessary include files  */
#include "szt_asn.h"
#include "lsz.h"           /* S1AP Layer management           */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef YT
#include "lyt.h"            /* S1AP-PSF                        */
#include "yt.h"            /* S1AP-PSF                        */
#endif /* YT */
#include "sz.h"            /* S1AP layer defines              */
#include "sz_err.h"        /* S1AP - error */
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
  
/* local defines */
  
/* local externs */
  
/* forward references */

/* public variable declarations */
  
/* This structure holds all the global structs we need. */

/* private variable declarations */

/* Private function declarations */
/* sz008.301: fix for kwork fix */
PRIVATE Bool szMgmtChkConnLst ARGS((
        SztResetTyp *tknIE,
        S1apPdu     *pdu,
        U8          *cause
        ));

/*******************************************************************************

  Management module handles the following Common Procedures :

  *   Paging and
  *   S1 Interface Management Procedures :
         *  S1 Setup
         *  Reset and
         *  Error Indication.  
  
*******************************************************************************/

#ifdef SZ_ENB
PFSZMGMTUIMSGHANDLER szMgmtUiEnb[SZ_MAX_MSG_ID] =
{
   szMgmtUiInvldMsgHandler,     /* E-RAB setup request */
   szMgmtUiInvldMsgHandler,     /* E-RAB setup response */
   szMgmtUiInvldMsgHandler,     /* E-RAB modify request */
   szMgmtUiInvldMsgHandler,     /* E-RAB modify response */
   szMgmtUiInvldMsgHandler,     /* E-RAB release command */
   szMgmtUiInvldMsgHandler,     /* E-RAB release complete */
   szMgmtUiInvldMsgHandler,     /* E-RAB release request */
   szMgmtUiInvldMsgHandler,     /* Initial Context setup request */
   szMgmtUiInvldMsgHandler,     /* Initial Context setup response */
   szMgmtUiInvldMsgHandler,     /* Initial Context setup failure */
   szMgmtUiInvldMsgHandler,     /* UE Context release request */
   szMgmtUiInvldMsgHandler,     /* UE Context release command */
   szMgmtUiInvldMsgHandler,     /* UE Context release complete */
   szMgmtUiInvldMsgHandler,     /* UE Context modification request */
   szMgmtUiInvldMsgHandler,     /* UE Context modification response */
   szMgmtUiInvldMsgHandler,     /* UE Context modification failure */
   szMgmtUiInvldMsgHandler,     /* Initial UE message */
   szMgmtUiInvldMsgHandler,     /* Downlink NAS transport */
   szMgmtUiInvldMsgHandler,     /* Uplink NAS transport */
   szMgmtUiInvldMsgHandler,     /* NAS non delivery indication */
   szMgmtUiErrInd,              /* Error indication */
   szMgmtUiInvldMsgHandler,     /* No Data */
   szMgmtUiRst,                 /* Reset */
   szMgmtUiRstAck,              /* Reset Acknowledge */
   szMgmtUiSetupReq,            /* Setup Request */
   szMgmtUiInvldMsgHandler,     /* Setup Response */
   szMgmtUiInvldMsgHandler,     /* Setup Fail */
   szMgmtUiInvldMsgHandler,     /* Paging */
   szMgmtUiMsgHandler,          /* Handover Required */
   szMgmtUiInvldMsgHandler,     /* Handover Command */
   szMgmtUiInvldMsgHandler,     /* Handover Preperation Failure */
   szMgmtUiInvldMsgHandler,     /* Handover Request */
   szMgmtUiMsgHandler,          /* Handover Request Acknowledge */
   szMgmtUiMsgHandler,          /* Handover Request Failure */
   szMgmtUiMsgHandler,          /* Handover Notify */
   szMgmtUiInvldMsgHandler,     /* Path Switch Request */
   szMgmtUiInvldMsgHandler,     /* Path Switch Request Acknowledge */
   szMgmtUiInvldMsgHandler,     /* Path Switch Request Failure */
   szMgmtUiMsgHandler,          /* Handover Cancel */
   szMgmtUiInvldMsgHandler,     /* Handover Cancel Acknowledge */
   szMgmtUiMsgHandler,          /* ENB Status Transfer */
   szMgmtUiInvldMsgHandler,     /* MME Status Transfer */
   szMgmtUiInvldMsgHandler,     /* Deactivate Trace */
   szMgmtUiInvldMsgHandler,     /* Trace Start */
   szMgmtUiInvldMsgHandler,     /* Trace Failure Indication */
   szMgmtUiInvldMsgHandler,     /* Location Reporting Control */
   szMgmtUiInvldMsgHandler,     /* Location Report Failure Indication */
   szMgmtUiInvldMsgHandler,     /* Location Report */
   szMgmtUiMsgHandler,          /* ENB Configuration Update */
   szMgmtUiInvldMsgHandler,     /* ENB Configuration Update Acknowledge */
   szMgmtUiInvldMsgHandler,     /* ENB Configuration Update Failure */
   szMgmtUiInvldMsgHandler,     /* MME Configuration Update */
   szMgmtUiMsgHandler,          /* MME Configuration Update Acknowledge */
   szMgmtUiMsgHandler,          /* MME Configuration Update Failure */
   szMgmtUiInvldMsgHandler,     /* Uplink CDMA 2000 Tunneling */
   szMgmtUiInvldMsgHandler,     /* Downlink CDMA 2000 Tunneling */
   szMgmtUiInvldMsgHandler,     /* UE Capability Info Indication */
   szMgmtUiInvldMsgHandler,     /* Overload Start */
   szMgmtUiInvldMsgHandler,     /* Overload Stop */
   szMgmtUiInvldMsgHandler,     /* Write Replace Warning Request */
   szMgmtUiMsgHandler,          /* Write Replace Warning Response */
   szMgmtUiMsgHandler,          /* ENB Information Direct Transfer */
   szMgmtUiInvldMsgHandler,     /* MME Information Direct Transfer */
   szMgmtUiInvldMsgHandler,     /* Private message */
   szMgmtUiMsgHandler,          /* ENB Configuration Transfer */
   szMgmtUiInvldMsgHandler,     /* MME Configuration Transfer */
   szMgmtUiInvldMsgHandler     /* Cell Traffic Trace */
#ifndef S1AP_REL8A0
   ,
   szMgmtUiInvldMsgHandler,     /* Kill Request */
   szMgmtUiMsgHandler,          /* Kill Response */
   szMgmtUiInvldMsgHandler,     /* Downlink UE Associated LPPa Transport */
   szMgmtUiInvldMsgHandler,     /* Uplink UE Associated LPPa Transport */
   szMgmtUiInvldMsgHandler,     /* Downlink non-UE Associated LPPa Transport */
   szMgmtUiMsgHandler           /* Uplink non-UE Associated LPPa Transport */
#endif /* S1AP_REL8A0 */
};
#endif


/*
 *
 *       Fun:   szMgmtUiInvldMsgHandler - Handler for Setup Response.
 *
 *       Desc:  This function handles the Invalid management message
 *              received from the User
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: Incase if the bypassing of UE state machine is enabled,
 *              This function will encode and send the message to peer
 *              Node.
 *              
 *       File:  sz_mgmt.c
 *
 */
#ifdef ANSI
PUBLIC S16 szMgmtUiInvldMsgHandler
(
SzPeerCb    *peerCb,                  /* Peer control block */
S1apPdu     *pdu,                     /* S1AP PDU */
SzSztSapCb  *uSapCb,                  /* SZT Sap control block */
U8          *cause,                    /* Error cause */
UConnId suConnId
)
#else
PUBLIC S16 szMgmtUiInvldMsgHandler(peerCb, pdu, uSapCb, cause, suConnId)
SzPeerCb    *peerCb;                 /* Peer control block */
S1apPdu     *pdu;                    /* S1AP PDU */
SzSztSapCb  *uSapCb;                  /* SZT Sap control block */
U8          *cause;                  /* Error cause */
UConnId     suConnId;
#endif
{
   S16        ret = RFAILED;
   
   TRC2(szMgmtUiInvldMsgHandler);

   /* Validate if the bypassing of UE state machine is enabled, if it is
    * enabled will ignore the UE state machine */
#ifdef LSZV1
   if(peerCb->skipUeSm)
   {
      /* Check state of the node */
      if (peerCb->state != SZT_ND_ST_NORMAL)
      {
         *cause = SZT_CAUSE_INV_STATE;
         RETVALUE(ret);
      } 

      /* Send encoded data to the peer */
      if ((ret = szLiSndToLower(peerCb, NULLP, pdu)) != ROK)
      {
         if((ret == SZT_CAUSE_PC_TX_SYNTAX_ERR) || 
               (ret == SZT_CAUSE_PC_ABS_SYNTAX_ERR))
         {
            *cause = (U8) ret; 
         }
         else
         {
            *cause = SZT_CAUSE_MSG_NOT_DELIVERED;
         }
         RETVALUE(ret);
      } 
      ret = ROK;
   }
   else
   {
#endif /* LSZV1 */

   /* Report error incase if the skip UE state machine is not enabled */

   *cause = SZT_CAUSE_UNEXP_MSG;
#ifdef LSZV1
   }
#endif /* LSZV1 */

   RETVALUE(ret);
} /* szMgmtUiInvldMsgHandler */


#ifdef SZ_ENB
/*
 *
 *       Fun:   szMgmtUiSetupReq - Handler for Setup Request
 *
 *       Desc:  This function handles Setup Request received from the User.
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *              
 *       File:  sz_mgmt.c
 *
 */
#ifdef ANSI
PUBLIC S16 szMgmtUiSetupReq 
(
SzPeerCb    *peerCb,                  /* Peer control block */
S1apPdu     *pdu,                     /* S1AP PDU */
SzSztSapCb  *uSapCb,                  /* SZT Sap control block */
U8          *cause,                    /* Error cause */
UConnId suConnId
)
#else
PUBLIC S16 szMgmtUiSetupReq(peerCb, pdu, uSapCb, cause, suConnId)
SzPeerCb    *peerCb;                 /* Peer control block */
S1apPdu     *pdu;                    /* S1AP PDU */
SzSztSapCb  *uSapCb;                 /* SZT Sap control block */
U8          *cause;                  /* Error cause */
UConnId     suConnId;
#endif
{
   S16        ret = ROK;             /* return value */
#ifdef MULTI_ENB_SUPPORT
   SzSctSapCb *sctSapCb = NULLP;
#endif
   TRC2(szMgmtUiSetupReq);
   /* Check the state of the node */
#ifndef MULTI_ENB_SUPPORT
   if (peerCb->state == SZT_ND_ST_NORMAL)
   {
      *cause = SZT_CAUSE_INV_STATE;
      RETVALUE(RFAILED);
   }
#else
   /* If Sap is not bound then return invalid sap */
   /* TODO: consider the start enbId below */
   if (!szCb.sctSapLst || ( (sctSapCb = szCb.sctSapLst[currEnbId]) == NULLP)
       || sctSapCb->state != LSZ_SAP_ISBOUND)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SZLOGERROR(ERRCLS_INT_PAR, ESZ039, (ErrVal) 0,
                 "SzLiSctTermInd: Invalid sap \n");
#endif /* ERRCLS */
      SZ_SEND_SAPID_ALARM(currEnbId, LSZ_EVENT_LI_TERM_IND, LCM_CAUSE_INV_SAP);
      RETVALUE(RFAILED);
   }
   sctSapCb->setupReq = pdu;
#endif

     /* Change the state to Setup in progress */
   peerCb->state = SZT_ND_ST_SETUP_IN_PRG;
   /* sz001.301: Fix for compilation warning */
#ifdef LSZV1
   if(peerCb->skipUeSm == FALSE)
   {
#endif /* LSZV1 */
      /* Release all the connections if it exist before with peerCb */
      (Void) szNdbRelConns(peerCb);
#ifdef LSZV1
   }
#endif /* LSZV1 */
   /* Store this setup request in peerCb */
   peerCb->setupReq = pdu; 

   /* Send AssocReq */
   if ((ret = szLiSndAssocReq(peerCb->assocCb)) != ROK)
   {
      /* Association is already up and running, send setup request to the peer */
/* Multi eNB support */
#ifdef MULTI_ENB_SUPPORT
      if ((ret = szLiSndToLower(peerCb, NULLP, sctSapCb->setupReq)) != ROK)
#else
      if ((ret = szLiSndToLower(peerCb, NULLP, peerCb->setupReq)) != ROK)
#endif
      {
         if((ret == SZT_CAUSE_PC_TX_SYNTAX_ERR) || 
               (ret == SZT_CAUSE_PC_ABS_SYNTAX_ERR))
         {
            *cause = (U8) ret; 
         }
         else
         {
            *cause = SZT_CAUSE_MSG_NOT_DELIVERED;
         }
      }
      peerCb->setupReq = NULLP;
#ifdef MULTI_ENB_SUPPORT
      sctSapCb->setupReq = NULLP;
#endif
   }
   /* Else, Setup request will be sent after receiving AssocCfm */

   RETVALUE(ret);

} /* szMgmtUiSetupReq */

/*
 *
 *       Fun:   szMgmtLiSetupRsp - Handler for Setup Response
 *
 *       Desc:  This function handles Setup Response received from the Peer.
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *              
 *       File:  sz_mgmt.c
 *
 */
#ifdef ANSI
PUBLIC S16 szMgmtLiSetupRsp 
(
SzPeerCb   *peerCb,                  /* Peer control block */
S1apPdu    *pdu                      /* S1AP PDU */
)
#else
PUBLIC S16 szMgmtLiSetupRsp(peerCb, pdu)
SzPeerCb   *peerCb;                  /* Peer control block */
S1apPdu    *pdu;                     /* S1AP PDU */
#endif
{
   S16         ret = ROK;            /* Return value */
   SztUDatEvnt uDatEvnt;             /* Connectionless data */

   TRC2(szMgmtLiSetupRsp);

/* Multi eNB support */
#ifndef MULTI_ENB_SUPPORT
   /* Check the state of the node */
   if (peerCb->state != SZT_ND_ST_SETUP_IN_PRG)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SZLOGERROR(ERRCLS_INT_PAR, ESZ066, (ErrVal)peerCb->peerId,
                 "szMgmtLiSetupRsp: Node is not in valid state \
                  to receive SetupRsp");
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */
      RETVALUE(RFAILED);
   }
#endif

   /* Change the state to Normal */ 
   peerCb->state = SZT_ND_ST_NORMAL;

   SZ_ZERO(&uDatEvnt, sizeof(SztUDatEvnt));

   uDatEvnt.transId.pres = NOTPRSNT;
   /* sz002.201 pres field of peerId is set in SetupResponse */
   uDatEvnt.peerId.pres = PRSNT_NODEF;
   uDatEvnt.peerId.val  = peerCb->peerId;
   uDatEvnt.pdu = pdu;

/* Multi eNB support */
#ifdef MULTI_ENB_SUPPORT
   uDatEvnt.enbId = currEnbId;
#endif

   /* Send the setup response pdu to the user */
   ret = szUiSndUDatInd(peerCb, &uDatEvnt);
#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
      SZLOGERROR(ERRCLS_DEBUG, ESZ067, (ErrVal)peerCb->peerId,
                 "szMgmtLiSetupRsp: Failed to send setup response to the user");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

   /* sz003.301: Added hooks for PSF-S1AP */
   /* Send the runtime update message for PeerCb */
#ifdef YT
   YT_RTUPD_MOD(YT_UPD_PEER_CB, peerCb);
#endif /* YT */

   RETVALUE(ret);

} /* szMgmtLiSetupRsp */

/*
 *
 *       Fun:   szMgmtLiSetupFailure - Handler for Setup Failure
 *
 *       Desc:  This function handles Setup Failure received from the Peer.
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *              
 *       File:  sz_mgmt.c
 *
 */
#ifdef ANSI
PUBLIC S16 szMgmtLiSetupFailure 
(
SzPeerCb   *peerCb,                  /* Peer control block */
S1apPdu    *pdu                      /* S1AP PDU */
)
#else
PUBLIC S16 szMgmtLiSetupFailure(peerCb, pdu)
SzPeerCb   *peerCb;                  /* Peer control block */
S1apPdu    *pdu;                     /* S1AP PDU */
#endif
{
   S16         ret = ROK;            /* Return value */
   SztUDatEvnt uDatEvnt;             /* Connectionless data */

   TRC2(szMgmtLiSetupFailure);

   /* Check the state of the node */
   if (peerCb->state != SZT_ND_ST_SETUP_IN_PRG)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SZLOGERROR(ERRCLS_INT_PAR, ESZ068, (ErrVal)peerCb->peerId,
                 "szMgmtLiSetupFailure: Node is not in valid state \
                  to receive SetupFailure");
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */
      RETVALUE(RFAILED);
   }

   /* Change the state to Idle; setup failed,  
      So the state can not be moved to normal */
   peerCb->state = SZT_ND_ST_IDLE;

   SZ_ZERO(&uDatEvnt, sizeof(SztUDatEvnt));

   uDatEvnt.transId.pres = NOTPRSNT;
   uDatEvnt.peerId.pres = PRSNT_NODEF;
   uDatEvnt.peerId.val = peerCb->peerId;
   uDatEvnt.pdu = pdu;

   /* Send the setup failure pdu to its user */
   ret = szUiSndUDatInd(peerCb, &uDatEvnt);
#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
      SZLOGERROR(ERRCLS_DEBUG, ESZ069, (ErrVal)peerCb->peerId,
                 "szMgmtLiSetupFailure: Failed to send setup failure \
                  to its user");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
  

   RETVALUE(ret);

} /* szMgmtLiSetupFailure */

#endif /* SZ_ENB */

/*
 *
 *       Fun:   szMgmtUiMsgHandler - Common handler for connection-less message 
 *
 *       Desc:  This function does common handling of the connection-less
 *              message received from the User
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *              
 *       File:  sz_mgmt.c
 *
 */
#ifdef ANSI
PUBLIC S16 szMgmtUiMsgHandler
(
SzPeerCb    *peerCb,                  /* Peer control block */
S1apPdu     *pdu,                     /* S1AP PDU */
SzSztSapCb  *uSapCb,                  /* SZT Sap control block */
U8          *cause,                    /* Error cause */
UConnId suConnId
)
#else
PUBLIC S16 szMgmtUiMsgHandler(peerCb, pdu, uSapCb, cause, suConnId)
SzPeerCb    *peerCb;                 /* Peer control block */
S1apPdu     *pdu;                    /* S1AP PDU */
SzSztSapCb  *uSapCb;                 /* SZT Sap control block */
U8          *cause;                  /* Error cause */
UConnId     suConnId;
#endif
{
   S16        ret = ROK;             /* return value */ 

   TRC2(szMgmtUiMsgHandler);

   /* Check state of the node */
   if (peerCb->state != SZT_ND_ST_NORMAL)
   {
      *cause = SZT_CAUSE_INV_STATE;
      RETVALUE(RFAILED);
   } 

   /* Send encoded data to the peer */
   if ((ret = szLiSndToLower(peerCb, NULLP, pdu)) != ROK)
   {
      if((ret == SZT_CAUSE_PC_TX_SYNTAX_ERR) || 
            (ret == SZT_CAUSE_PC_ABS_SYNTAX_ERR))
      {
         *cause = (U8) ret; 
      }
      else
      {
         *cause = SZT_CAUSE_MSG_NOT_DELIVERED;
      }
   }    

   RETVALUE(ret);

} /* szMgmtUiMsgHandler */

/*
 *
 *       Fun:   szMgmtUiRst - Handler for Reset 
 *
 *       Desc:  This function handles the Reset message received from the User.
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *              
 *       File:  sz_mgmt.c
 *
 */
#ifdef ANSI
PUBLIC S16 szMgmtUiRst
(
SzPeerCb    *peerCb,                  /* Peer control block */
S1apPdu     *pdu,                     /* S1AP PDU */
SzSztSapCb  *uSapCb,                  /* SZT Sap control block */
U8          *cause,                    /* Error cause */
UConnId lclRefNum
)
#else
PUBLIC S16 szMgmtUiRst(peerCb, pdu, uSapCb, cause, lclRefNum)
SzPeerCb    *peerCb;                 /* Peer control block */
S1apPdu     *pdu;                    /* S1AP PDU */
SzSztSapCb  *uSapCb;                 /* SZT Sap control block */
U8          *cause;                    /* Error cause */
UConnId lclRefNum;
#endif
{
   S16         ret = ROK;             /* return value */
   S1apPdu     *rstAckPdu = NULLP;    /* PDU for Reset Ack */
   TknU8       *tknIE = NULLP;        /* Reset type IE */
   Mem         mem;                   /* Memory block */
   U8          idx;                   /* Index */
   U16         nmbConns;              /* Number of connections in Reset */
   SzConRefNo  conRefNo;             /* Connection Id received in the Reset */
   SztUDatEvnt uDatEvnt;             /* Connectionless data */
   U8          conRefType;           /* Connection reference type */

   TRC2(szMgmtUiRst);

   SZ_ZERO(&uDatEvnt, sizeof(SztUDatEvnt));

   /* sz001.301: Fix for compilation warning */
#ifdef LSZV1
   if(peerCb->skipUeSm == FALSE)
   {
#endif /* LSZV1 */
      /* Get S1 connection list from DB */
      szGetIE(&pdu->pdu, Sztid_ResetTyp, &tknIE);

      if(tknIE == NULLP)
      {
         SZ_FREE_SDU(pdu);
         RETVALUE(RFAILED);
      }

      mem.region = uSapCb->pst.region; 
      mem.pool   = uSapCb->pst.pool;

      /* Check if the node is in RESET state already */
      if (peerCb->state == SZT_ND_ST_RESET)
      {
         /* If connections are similar, send reset ack to the user */
         /* sz008.301:  Fix for kwork */
         if ((ret = szMgmtChkConnLst(((SztResetTyp *)tknIE), peerCb->resetPdu, cause)) == TRUE)
         {
            uDatEvnt.transId.pres = NOTPRSNT;
            uDatEvnt.peerId.pres = PRSNT_NODEF;
            uDatEvnt.peerId.val = peerCb->peerId;

            /* Fill Reset Ack to the user */
            /* sz008.301: fix for Kwork */
            ret = szDbFillResetAck(pdu, &rstAckPdu, mem, cause);
            if(ret != ROK)
            {
               RETVALUE(RFAILED);
            }
            uDatEvnt.pdu = rstAckPdu;
            SZ_FREE_SDU(pdu);
            ret = szUiSndUDatInd(peerCb, &uDatEvnt);
            RETVALUE(ret);
         }
         /* sz008.301: fix for Kwork */
         else if(*cause == SZT_CAUSE_MSING_MNDTRY_PARM)
         {
            RETVALUE(RFAILED);
         }
      }
      /* sz001.301: Fix for compilation warning */
#ifdef LSZV1
   }
#endif /* LSZV1 */

   /* Change the state of the node to Reset */
   peerCb->state = SZT_ND_ST_RESET;  

   /* sz001.301: Fix for compilation warning */
#ifdef LSZV1
   if(peerCb->skipUeSm == FALSE)
   {
#endif /* LSZV1 */
      /* Release all the connections or part of the connections 
         as per the choice in the reset */
      if (((SztResetTyp *)tknIE)->choice.val == SZ_FULL_RESET)
      {
         ret = szNdbDeallocConCb(lclRefNum, peerCb, SZ_CONN_REF_LCL);
      }
      else
      {
         /* Partial reset */
         nmbConns = ((SztResetTyp *)tknIE)->val.partOfS1_Intf.noComp.val;
         for (idx = 0; idx < nmbConns; idx++)
         {
            /* Deallocate ConCb */
            if (((SztResetTyp *)tknIE)->val.partOfS1_Intf.member[idx].value.u.\
                  sztUE_assocLogS1_ConItem.pres.pres != NOTPRSNT)
            {
               /* Assigne the connection reference type */
               {
#ifdef SZ_ENB
                  if (((SztResetTyp *)tknIE)->val.partOfS1_Intf.member[idx].\
                        value.u.sztUE_assocLogS1_ConItem.eNB_UE_S1AP_ID.pres != NOTPRSNT)
                  {
                     conRefNo = ((SztResetTyp *)tknIE)->val.partOfS1_Intf.member[idx].\
                                value.u.sztUE_assocLogS1_ConItem.eNB_UE_S1AP_ID.val;

                     conRefType = SZ_CONN_REF_LCL;
                  }
                  else if (((SztResetTyp *)tknIE)->val.partOfS1_Intf.member[idx].\
                        value.u.sztUE_assocLogS1_ConItem.mME_UE_S1AP_ID.pres != NOTPRSNT)
                  {
                     conRefNo = ((SztResetTyp *)tknIE)->val.partOfS1_Intf.member[idx].\
                                value.u.sztUE_assocLogS1_ConItem.mME_UE_S1AP_ID.val;

                     conRefType = SZ_CONN_REF_RMT;
                  }
                  else
#endif
                  {
                     uDatEvnt.transId.pres = NOTPRSNT;
                     uDatEvnt.peerId.pres = PRSNT_NODEF;
                     uDatEvnt.peerId.val = peerCb->peerId;

                     /* Fill & Keep Reset Ack to the user */
                     /* sz008.301: fix for Kwork. */
                     ret = szDbFillResetAck(pdu, &rstAckPdu, mem, cause);
                     if(ret != ROK)
                     {
                        RETVALUE(RFAILED);
                     }
                     uDatEvnt.pdu = rstAckPdu;
                     SZ_FREE_SDU(pdu);
                     ret = szUiSndUDatInd(peerCb, &uDatEvnt);
                     RETVALUE(ret);
                  }
               }

               /* Mention the connection reference type */
               ret = szNdbDeallocConCb(conRefNo, peerCb, conRefType);
            }
         }
      }

      /* Store this connection list in peerCb, temporarily */
      if ((ret = szDbFillResetFrmPdu(pdu, &peerCb->resetPdu, mem)) != ROK)
      {
         *cause = SZT_CAUSE_MSG_NOT_DELIVERED;
         SZ_FREE_SDU(pdu);
         RETVALUE(ret);
      }
      /* sz001.301: Fix for compilation warning */
#ifdef LSZV1
   }
#endif /* LSZV1 */

   /* Send encoded data to the peer */
   if ((ret = szLiSndToLower(peerCb, NULLP, pdu)) != ROK)
   { 
      if((ret == SZT_CAUSE_PC_TX_SYNTAX_ERR) || 
            (ret == SZT_CAUSE_PC_ABS_SYNTAX_ERR))
      {
         *cause = (U8) ret; 
      }
      else
      {
         *cause = SZT_CAUSE_MSG_NOT_DELIVERED;
      }
      
      SZ_FREE_SDU(peerCb->resetPdu);
      RETVALUE(ret);
   }


   RETVALUE(ret);

} /* szMgmtUiRst */

/*
 *
 *       Fun:   szMgmtUiRstAck - Handler for Reset Ack
 *
 *       Desc:  This function handles the Reset Ack received from the User.
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *              
 *       File:  sz_mgmt.c
 *
 */
#ifdef ANSI
PUBLIC S16 szMgmtUiRstAck 
(
SzPeerCb    *peerCb,                  /* Peer control block */
S1apPdu     *pdu,                     /* S1AP PDU */
SzSztSapCb  *uSapCb,                  /* SZT Sap control block */
U8          *cause,                    /* Error cause */
UConnId suConnId
)
#else
PUBLIC S16 szMgmtUiRstAck(peerCb, pdu, uSapCb, cause, suConnId)
SzPeerCb    *peerCb;                 /* Peer control block */
S1apPdu     *pdu;                    /* S1AP PDU */
SzSztSapCb *uSapCb;                  /* SZT Sap control block */
U8          *cause;                    /* Error cause */
UConnId suConnId;
#endif
{
   S16         ret = ROK;             /* return value */

   TRC2(szMgmtUiRstAck);

   /* Send encoded data to the peer */
   if ((ret = szLiSndToLower(peerCb, NULLP, pdu)) != ROK)
   {
      if((ret == SZT_CAUSE_PC_TX_SYNTAX_ERR) || 
            (ret == SZT_CAUSE_PC_ABS_SYNTAX_ERR))
      {
         *cause = (U8) ret; 
      }
      else
      {
         *cause = SZT_CAUSE_MSG_NOT_DELIVERED;
      }
      RETVALUE(ret);
   }

   /* Change the state of the node to normal */
   peerCb->state = SZT_ND_ST_NORMAL;

   /* Remove the temporarily stored reset info from peerCb */
    SZ_FREE_SDU(peerCb->resetPdu); 

   RETVALUE(ret);

} /* szMgmtUiRstAck */

/*
 *
 *       Fun:   szMgmtLiRst - Handler for Reset 
 *
 *       Desc:  This function handles the Reset message received from the Peer.
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *              
 *       File:  sz_mgmt.c
 *
 */
#ifdef ANSI
PUBLIC S16 szMgmtLiRst 
(
SzPeerCb   *peerCb,                  /* Peer control block */
S1apPdu    *pdu                      /* S1AP PDU */
)
#else
PUBLIC S16 szMgmtLiRst(peerCb, pdu)
SzPeerCb    *peerCb;                 /* Peer control block */
S1apPdu     *pdu;                    /* S1AP PDU */
#endif
{
   S16         ret = ROK;            /* Return value */
   SztUDatEvnt uDatEvnt;             /* Connectionless data */
   TknU8       *tknIE = NULLP;       /* Reset Type IE */
   S1apPdu     *rstAckPdu = NULLP;   /* Reset Ack PDU */
   Mem         mem;                  /* Memory block */
   U8          idx;                  /* Index */
   U16         nmbConns = 0;         /* Number of connections in Reset */
   SzConRefNo  conRefNo;             /* Connection Id received in the Reset */
   U8          conRefType;           /* Connection reference type */
   /* sz008.301: fix for kwork */
   U8          cause;

   TRC2(szMgmtLiRst);

   SZ_ZERO(&uDatEvnt, sizeof(SztUDatEvnt));

   /* sz001.301: Fix for compilation warning */
#ifdef LSZV1
   if(peerCb->skipUeSm == FALSE)
   {
#endif /* LSZV1 */
      /* Get S1 connection list from DB */
      szGetIE(&pdu->pdu, Sztid_ResetTyp, &tknIE); 

      if(tknIE == NULLP)
      {
         SZ_FREE_SDU(pdu);
         RETVALUE(RFAILED);
      }

      mem.region = peerCb->sctSapCb->pst.region;
      mem.pool   = peerCb->sctSapCb->pst.pool;

      /* Check if the node is in RESET state already */
      if (peerCb->state == SZT_ND_ST_RESET)
      {
         /* If connections are similar, send reset ack to the peer */ 
         /* sz008.301: Fix for kwork */
         if ((ret = szMgmtChkConnLst(((SztResetTyp *)tknIE), peerCb->resetPdu, &cause)) == TRUE)
         {
            /* Fill & Keep Reset Ack to the peer */
            /* sz008.301: fix for kwork,
             * added check for return value, as we are returning other than ROK 
             * from szDbFillResetAck in error scenario */

            ret = szDbFillResetAck(pdu, &rstAckPdu, mem, &cause);
            if (ret != ROK)
            {
               SZ_FREE_SDU(pdu);
               RETVALUE(RFAILED);
            }
            szLiSndToLower(peerCb, NULLP, rstAckPdu);

            SZ_FREE_SDU(pdu);
            RETVALUE(ROK); 
         }
          /* sz008.301: fix for Kwork */
         else if(cause  == SZT_CAUSE_MSING_MNDTRY_PARM)
         {
            RETVALUE(RFAILED);
         }

      }
      /* sz001.301: Fix for compilation warning */
#ifdef LSZV1
   }
#endif /* LSZV1 */

   /* Proceed with the reset if the connections are not similar to the previous
      Reset received from user */

   /* Change the state of the node to reset */
   peerCb->state = SZT_ND_ST_RESET;

   /* sz001.301: Fix for compilation warning */
#ifdef LSZV1
   if(peerCb->skipUeSm == FALSE)
   {
#endif /* LSZV1 */

      /* Release all the connections or part of the connections 
         as per the choice in the reset */
      if (((SztResetTyp *)tknIE)->choice.val == SZ_FULL_RESET)   
      {
         (Void) szNdbRelConns(peerCb);
      }
      else
      {
         /* Partial reset */  
         nmbConns = ((SztResetTyp *)tknIE)->val.partOfS1_Intf.noComp.val;
         for (idx = 0; idx < nmbConns; idx++)
         {
            /* Deallocate ConCb */
            if (((SztResetTyp *)tknIE)->val.partOfS1_Intf.member[idx].value.u.\
                  sztUE_assocLogS1_ConItem.pres.pres != NOTPRSNT)
            {
               /* Assigne the connection refence type */
               {
#ifdef SZ_ENB
                  if (((SztResetTyp *)tknIE)->val.partOfS1_Intf.member[idx].\
                        value.u.sztUE_assocLogS1_ConItem.eNB_UE_S1AP_ID.pres != NOTPRSNT)
                  {
                     conRefNo = ((SztResetTyp *)tknIE)->val.partOfS1_Intf.member[idx].\
                                value.u.sztUE_assocLogS1_ConItem.eNB_UE_S1AP_ID.val;

                     conRefType = SZ_CONN_REF_LCL;
                  }
                  else if(((SztResetTyp *)tknIE)->val.partOfS1_Intf.member[idx].value.\
                        u.sztUE_assocLogS1_ConItem.mME_UE_S1AP_ID.pres != NOTPRSNT)
                  {
                     conRefNo = ((SztResetTyp *)tknIE)->val.partOfS1_Intf.member[idx].\
                                value.u.sztUE_assocLogS1_ConItem.mME_UE_S1AP_ID.val;

                     conRefType = SZ_CONN_REF_RMT;
                  }
                  else
#endif
                  {
                     /* Fill & Keep Reset Ack to the peer */
                     /* sz008.301: fix for kwork,
                      * added check for return value, as we are returning other than ROK 
                      * from szDbFillResetAck in error scenario */

                     ret = szDbFillResetAck(pdu, &rstAckPdu, mem, &cause);
                     if (ret != ROK)
                     {
                        SZ_FREE_SDU(pdu);
                        RETVALUE(RFAILED);
                     }
                     szLiSndToLower(peerCb, NULLP, rstAckPdu);

                     SZ_FREE_SDU(pdu);
                     RETVALUE(ROK);
                  }
               }
               /* Mention the connection reference type */
               ret = szNdbDeallocConCb(conRefNo, peerCb, conRefType);
            }
         }
      }
      /* sz001.301: Fix for compilation warning */
#ifdef LSZV1
   }
#endif /* LSZV1 */

   uDatEvnt.transId.pres = NOTPRSNT;
   uDatEvnt.peerId.pres = PRSNT_NODEF;
   uDatEvnt.peerId.val = peerCb->peerId;
   uDatEvnt.pdu = pdu;

   /* sz001.301: Fix for compilation warning */
#ifdef LSZV1
   if(peerCb->skipUeSm == FALSE)
   {
#endif /* LSZV1 */

      /* Store this connection list in peerCb, temporarily */
      if ((ret = szDbFillResetFrmPdu(pdu, &peerCb->resetPdu, mem)) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SZLOGERROR(ERRCLS_DEBUG, ESZ070, (ErrVal)peerCb->peerId,
               "szMgmtLiRst: Failed to make a copy Reset pdu");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
      }
   /* sz001.301: Fix for compilation warning */
#ifdef LSZV1
   }
#endif /* LSZV1 */

   /* Send Reset to the user */
   if ((ret = szUiSndUDatInd(peerCb, &uDatEvnt)) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SZLOGERROR(ERRCLS_DEBUG, ESZ071, (ErrVal)peerCb->peerId,
                 "szMgmtLiRst: Failed to send Reset to the user");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

      SZ_FREE_SDU(peerCb->resetPdu);
   }

   RETVALUE(ret);

} /* szMgmtLiRst */

/*
 *
 *       Fun:   szMgmtLiRstAck - Handler for Reset Ack
 *
 *       Desc:  This function handles the Reset Ack received from the Peer.
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *              
 *       File:  sz_mgmt.c
 *
 */
#ifdef ANSI
PUBLIC S16 szMgmtLiRstAck 
(
SzPeerCb   *peerCb,                  /* Peer control block */
S1apPdu    *pdu                      /* S1AP PDU */
)
#else
PUBLIC S16 szMgmtLiRstAck(peerCb, pdu)
SzPeerCb   *peerCb;                  /* Peer control block */
S1apPdu    *pdu;                     /* S1AP PDU */
#endif
{
   S16         ret = ROK;            /* Return value */
   SztUDatEvnt uDatEvnt;             /* Connectionless data */

   TRC2(szMgmtLiRstAck);

   SZ_ZERO(&uDatEvnt, sizeof(SztUDatEvnt));

   uDatEvnt.transId.pres = NOTPRSNT;
   uDatEvnt.peerId.pres = PRSNT_NODEF;
   uDatEvnt.peerId.val = peerCb->peerId;
   uDatEvnt.pdu = pdu;

   /* Change the state of the node to normal */
   peerCb->state     = SZT_ND_ST_NORMAL;

   /* Send the Reset Ack to the user */
   ret = szUiSndUDatInd(peerCb, &uDatEvnt);
#if (ERRCLASS & ERRCLS_INT_PAR)
   if (ret != ROK)
      SZLOGERROR(ERRCLS_INT_PAR, ESZ072, (ErrVal)peerCb->peerId,
                 "szMgmtLiRstAck: Failed to send Reset Ack to the user");
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */

   /* Remove the temporarily stored reset info from peerCb */
   SZ_FREE_SDU(peerCb->resetPdu); 

   RETVALUE(ret);

} /* szMgmtLiRstAck */

/*
 *
 *       Fun:   szMgmtUiErrInd - Handler for Error Indication
 *
 *       Desc:  This function handles Error Indication received from the user.
 *       Desc:  This function handles Error scenarios upon receiving the 
 *              message from the User.
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *              
 *       File:  sz_mgmt.c
 *
 */
#ifdef ANSI
PUBLIC S16 szMgmtUiErrInd
(
SzPeerCb    *peerCb,                  /* Peer control block */
S1apPdu     *pdu,                     /* S1AP PDU */
SzSztSapCb  *uSapCb,                  /* SZT Sap control block */
U8          *cause,                    /* Error cause */
UConnId     suConnId
)
#else
PUBLIC S16 szMgmtUiErrInd(peerCb, pdu, uSapCb, cause, suConnId)
SzPeerCb    *peerCb;                 /* Peer control block */
S1apPdu     *pdu;                    /* S1AP PDU */
SzSztSapCb  *uSapCb;                  /* SZT Sap control block */
U8          *cause;                  /* Error cause */
UConnId      suConnId;

#endif
{
   S16        ret = ROK;             /* return value */

   TRC2(szMgmtUiErrInd);

   /* Send encoded data to the peer */
   if ((ret = szLiSndToLower(peerCb, NULLP, pdu)) != ROK)
   {
      if((ret == SZT_CAUSE_PC_TX_SYNTAX_ERR) || 
            (ret == SZT_CAUSE_PC_ABS_SYNTAX_ERR))
      {
         *cause = (U8) ret; 
      }
      else
      {
         *cause = SZT_CAUSE_MSG_NOT_DELIVERED;
      }
   }

   RETVALUE(ret);

} /* szMgmtUiErrInd */

/*
 *
 *       Fun:   szMgmtLiMsgHandler - Common handler for connection-less message 
 *
 *       Desc:  This function does common handling of the connection-less
 *              message received from the peer 
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *              
 *       File:  sz_mgmt.c
 *
 */
#ifdef ANSI
PUBLIC S16 szMgmtLiMsgHandler
(
SzPeerCb   *peerCb,                  /* Peer control block */
S1apPdu    *pdu                      /* S1AP PDU */
)
#else
PUBLIC S16 szMgmtLiMsgHandler(peerCb, pdu)
SzPeerCb   *peerCb;                  /* Peer control block */
S1apPdu    *pdu;                     /* S1AP PDU */
#endif
{
   S16         ret = ROK;            /* Return value */ 
   SztUDatEvnt uDatEvnt;             /* Connectionless data */

   TRC2(szMgmtLiMsgHandler);

   /* Check the state of the node */
   if (peerCb->state != SZT_ND_ST_NORMAL)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SZLOGERROR(ERRCLS_INT_PAR, ESZ073, (ErrVal)peerCb->peerId,
                 "szMgmtLiMsgHandler : Node is not in valid state \
                  to receive message");
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */
      RETVALUE(RFAILED);
   }

   /* State will remain same - NORMAL */

   SZ_ZERO(&uDatEvnt, sizeof(SztUDatEvnt));

   uDatEvnt.transId.pres = NOTPRSNT; 
   uDatEvnt.peerId.pres = PRSNT_NODEF;
   uDatEvnt.peerId.val   = peerCb->peerId;
   uDatEvnt.pdu          = pdu;

   /* Send data to the user */
   ret = szUiSndUDatInd(peerCb, &uDatEvnt);
#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
      SZLOGERROR(ERRCLS_DEBUG, ESZ074, (ErrVal)peerCb->peerId,
                 "szMgmtLiMsgHandler : Failed to send data to the user");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
  

   RETVALUE(ret);

} /* szMgmtLiMsgHandler */

/*
 *
 *       Fun:   szMgmtChkConnLst - Compare S1 connection list
 *
 *       Desc:  This function compares S1 connection list with the temporarily 
 *              stored connection list in peerCb.
 *
 *       Ret:   ROK     - TRUE 
 *              RFAILED - FALSE 
 *
 *       Notes: None
 *              
 *       File:  sz_mgmt.c
 *
 */
#ifdef ANSI
PRIVATE Bool szMgmtChkConnLst 
(
SztResetTyp *tknIE,                  /* Connection list IE */
S1apPdu     *pdu,                    /* Reset Pdu */
U8          *cause
)
#else
PRIVATE Bool szMgmtChkConnLst(tknIE, pdu, cause)
SztResetTyp *tknIE;                  /* Connection list IE */
S1apPdu     *pdu;                    /* Reset Pdu */
U8          *cause;
#endif
{
   U8          i;                     /* Index variable for the outer loop */
   U8          j;                     /* Index variable for the inner loop */
   U16         nmbConns = 0;          /* Number of connections in Reset */
   SzConRefNo  conRefNo = 0;          /* Connection Id received in the Reset */ 
   TknU8       *tmpReset = NULLP;     /* Reset type IE stored in Peer */
   U16         tmpConns = 0;          /* Number of connections in Reset stored in Peer */
   SzConRefNo  tmpCon;                /* Connection Id stored in Peer */
   Bool        isEqual = FALSE;       /* isEqual flag */
   SztUE_assocLogS1_ConItem *conItem, *tmpConItem; /* conItem pointers */

   TRC2(szMgmtChkConnLst);

   /* sz008.301: fix for kwork */
   *cause = LCM_CAUSE_UNKNOWN;
   /* Get S1 connection list from DB for the reset pdu stored in peerCb */
   szGetIE(&pdu->pdu, Sztid_ResetTyp, &tmpReset);
   /* sz008.301: fix for Kwork */
   if((tknIE == NULLP) || (tmpReset == NULLP))
   {
      *cause = SZT_CAUSE_MSING_MNDTRY_PARM;
      RETVALUE(FALSE);
   }

   /* Check if we received full reset before and the current one is 
      partial/full reset */
   if (((SztResetTyp *)tmpReset)->choice.val == SZ_FULL_RESET) 
   {
      if ((tknIE->choice.val == SZ_PARTIAL_RESET) ||
          (tknIE->choice.val == SZ_FULL_RESET))
         RETVALUE(TRUE); 
   }

   /* Number of connections */
   tmpConns = ((SztResetTyp *)tmpReset)->val.partOfS1_Intf.noComp.val; 
   nmbConns = tknIE->val.partOfS1_Intf.noComp.val;

   /* Compare the connections received in Reset 
      with the connections stored in Peer */
   for (i = 0; i < nmbConns; i++)
   {
      conItem = &(tknIE->val.partOfS1_Intf.member[i].value.u.sztUE_assocLogS1_ConItem);

      if (conItem->pres.pres != NOTPRSNT)
      {
         if (conItem->mME_UE_S1AP_ID.pres != NOTPRSNT)
         {
            conRefNo = conItem->mME_UE_S1AP_ID.val;
         }
         else if (conItem->eNB_UE_S1AP_ID.pres != NOTPRSNT)
         {
            conRefNo = conItem->eNB_UE_S1AP_ID.val;
         }
         else
         {
            RETVALUE(TRUE); /* Empty list */
         }
      }
      else
      {
         /* Connection block is empty */
         SZDBGP(DBGMASK_LYR, (szCb.init.prntBuf,
                "szMgmtChkConnLst: S1 Connection is empty \n"));
      }

      isEqual = FALSE;
      for (j = 0; j < tmpConns; j++)
      {
        tmpConItem = &(((SztResetTyp *)tmpReset)->val.partOfS1_Intf.member[j].value.u.sztUE_assocLogS1_ConItem);

        if (tmpConItem->pres.pres != NOTPRSNT) 
        {
            if (tmpConItem->mME_UE_S1AP_ID.pres != NOTPRSNT)
            {
               tmpCon = tmpConItem->mME_UE_S1AP_ID.val;
            }
            else
            {
               tmpCon = tmpConItem->eNB_UE_S1AP_ID.val;
            }

            if (conRefNo == tmpCon) 
            {
               isEqual = TRUE;
               break;
            }
        }
      }
      if (!isEqual)
      {
         RETVALUE(isEqual);
      }
   }

   RETVALUE(isEqual);

} /* szMgmtChkConnLst */

/**********************************************************************

         End of file:     sq_mgmt.c@@/main/4 - Mon Jan 10 22:17:00 2011

**********************************************************************/

/**********************************************************************
        Revision History:

**********************************************************************/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/4      ---        pkaX   1. Updated for S1AP release 3.1
/main/4     sz001.301   pkaX   1. Fix for compilation warnings when LSZV1
                                  is disabled.
/main/4   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
/main/4   sz006.301   ve    1. Removed un-necessary include files
/main/4   sz008.301  akaranth 1.Support for source RNC to target RNC.
                              2.kwork fixes.
*********************************************************************91*/
