

/********************************************************************20**

     Name:     S1AP Layer

     Type:     C source file

     Desc:     C Source code for SM

     File:     sz_sm.c

     Sid:      sq_sm.c@@/main/4 - Mon Jan 10 22:17:05 2011

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
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#include "cm_pasn.h"
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
#endif /* SZ_FTHA */
#include "lsz.h"           /* S1AP LM Interface */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#include "szt_asn.h"
#ifdef YT
#include "lyt.h"           /* S1AP-PSF LM Interface */
#include "yt.h"            /* S1AP-PSF Layer */
#endif /* YT */
#include "sz.h"            /* S1AP Layer */
#include "sz_err.h"
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
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#include "cm_pasn.x"
#ifdef SZ_FTHA
#include "cm_ftha.x"
#include "cm_pftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#endif /* SZ_FTHA */

#include "szt_asn.x"
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.x"
#endif
#include "sct.x"           /* SCTP Layer */
#include "szt.x"           /* S1AP Upper Interface */
#ifdef SZ_FTHA
#include "sht.x"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.x"           /* S1AP LM Interface */
#ifdef YT
#include "lyt.x"           /* S1AP-PSF LM Interface */
#include "yt.x"
#endif /* YT */
#include "sz.x"            /* S1AP Layer */

/*
*
*       Fun:  szSmSndConnStMsg
*
*       Desc:  Called to send messages in connecting state
*
*       Ret:   ok:     ROK
*              failed: RFAILED
*
*       Notes: None
*
*       File:  sz_smuimme.c
*
*/

#ifdef ANSI
PUBLIC S16 szSmSndConnStMsg
(
SzConCb  *conCb,
SzPeerCb *peerCb,
S1apPdu  *pdu
)
#else
PUBLIC S16 szSmSndConnStMsg(conCb, peerCb, pdu)
SzConCb  *conCb;
SzPeerCb *peerCb;
S1apPdu  *pdu;
#endif
{
   S16 ret = ROK;

#ifdef SZ_ENB
   TknU8 *eNbId = NULLP;
#endif /* SZ_ENB */
   U8    evnt;

   TRC2(szSmSndConnStMsg)

   szUtilsGetMsgIdx(&evnt,pdu);

#ifdef SZ_ENB
   if(peerCb->nodeType == LSZ_NODE_MME)
   {
      switch(evnt)
      {
         case SZT_MSG_ID_UL_NAS_TPT:
         case SZT_MSG_ID_HO_REQ_ACK:
              szGetIE(&pdu->pdu, Sztid_eNB_UE_S1AP_ID, &eNbId);
              if (NULLP != eNbId)
              {
              ((SztENB_UE_S1AP_ID *)eNbId)->val = conCb->lclConRefNo; 
              }
              else
              {
                 /*Sending local error indication and releasing the pdu*/
                 SZ_SEND_LCL_ERR_IND(PRSNT_NODEF, conCb->cd.suConnId,
                       peerCb->sztSapCb, SZT_CAUSE_PC_TX_SYNTAX_ERR, 0);
                 SZ_FREE_SDU(pdu);
                 RETVALUE(RFAILED);
              }
         break;
      }
   }
#endif


   /* Send this message send/receive interface */
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

#if (ERRCLASS & ERRCLS_INT_PAR)
      SZLOGERROR(ERRCLS_INT_PAR, ESZ139, (ErrVal) conCb->lclConRefNo,
            "szSmSndConnStMsg: Lower Interface send failed");
#endif
      RETVALUE(ret);
   }

   /* Change the state to Connected */
   conCb->state = SZ_SMSZ_ESTABLISHED;

   /* sz003.301: Added hooks for PSF-S1AP */
   /* Send the runtime update message to peer for state updation */
#ifdef YT
   YT_RTUPD_MOD(YT_UPD_CONN_CB, conCb);
#endif /* YT */

   RETVALUE(ROK);
} /* end of szSmSndConnStMsg */

/*
*
*       Fun:  szSmSndEstStMsg
*
*       Desc:  Called to send messages in established state
*
*       Ret:   ok:     ROK
*              failed: RFAILED
*
*       Notes: None
*
*       File:  sz_smuimme.c
*
*/

#ifdef ANSI
PUBLIC S16 szSmSndEstStMsg
(
SzConCb  *conCb,
SzPeerCb *peerCb,
S1apPdu  *pdu
)
#else
PUBLIC S16 szSmSndEstStMsg(conCb, peerCb, pdu)
SzConCb  *conCb;
SzPeerCb *peerCb;
S1apPdu  *pdu;
#endif
{
#ifdef SZ_ENB
   TknU8  *mmeS1apId = NULLP;
#endif
   S16    ret = RFAILED;

   TRC2(szSmSndEstStMsg)

#ifdef SZ_ENB
   if(peerCb->nodeType == LSZ_NODE_MME)
   {
      szGetIE(&(pdu->pdu), Sztid_MME_UE_S1AP_ID, &mmeS1apId);
      if(NULLP != mmeS1apId)
      {
      /* sz008.301: Removed rechecking of mmes1apID */
      if(((SztMME_UE_S1AP_ID *)mmeS1apId)->val != conCb->rmtConRefNo)
      {
         /* Error Indication to the user */
         SZ_SEND_LCL_ERR_IND(PRSNT_NODEF, conCb->cd.spConnId, 
               peerCb->sztSapCb, SZT_CAUSE_INV_CONID, ((SztMME_UE_S1AP_ID *)mmeS1apId)->val);
         SZ_FREE_SDU(pdu);
         RETVALUE(ret);
      }
   }
      else
      {
         /*Sending local error indication and releasing the pdu*/
         SZ_SEND_LCL_ERR_IND(PRSNT_NODEF, conCb->cd.suConnId,
               peerCb->sztSapCb, SZT_CAUSE_PC_TX_SYNTAX_ERR, 0);
         SZ_FREE_SDU(pdu);
         RETVALUE(RFAILED);
      }
   }
#endif


   /* Send this message send/receive interface */
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

#if (ERRCLASS & ERRCLS_INT_PAR)
      SZLOGERROR(ERRCLS_INT_PAR, ESZ140, (ErrVal) conCb->lclConRefNo,
            "szSmSndEstStMsg: Lower Interface send failed");
#endif
   }

   RETVALUE(ret);
} /* end of szSmSndEstStMsg */

/*
*
*       Fun:  szSmLclRlsReq
*
*       Desc:  Called to release logical S1 connection
*
*       Ret:   ok:     ROK
*              failed: RFAILED
*
*       Notes: None
*
*       File:  sz_smuimme.c
*
*/

#ifdef ANSI
PUBLIC S16 szSmLclRlsReq
(
SzConCb  *conCb,
SzPeerCb *peerCb,
S1apPdu  *pdu
)
#else
PUBLIC S16 szSmLclRlsReq(conCb, peerCb, pdu)
SzConCb  *conCb;
SzPeerCb *peerCb;
S1apPdu  *pdu;
#endif
{  
   S16 ret = RFAILED;

   TRC2(szSmLclRlsReq)

   /* Deallocate connection control block */
   ret = szNdbDeallocConCb(conCb->lclConRefNo, peerCb, SZ_CONN_REF_LCL);

   if(ret == RFAILED)
   {
      SZ_SEND_LCL_ERR_IND(PRSNT_NODEF, conCb->cd.suConnId,
                          peerCb->sztSapCb, SZT_CAUSE_INV_CONID, conCb->lclConRefNo);
   
      SZ_FREE_SDU(pdu);

#if (ERRCLASS & ERRCLS_INT_PAR)
      SZLOGERROR(ERRCLS_INT_PAR, ESZ141, (ErrVal) conCb->lclConRefNo,
           "szSmLclRlsReq: Couldn't find the connection CB");
#endif
   }

   SZ_FREE_SDU(pdu);

   RETVALUE(ret);
} /* end of szSmLclRlsReq */

/*
*
*       Fun:   szSmLclErrHdlr
*
*       Desc:  Called to send error indication to peer node
*
*       Ret:   ok:     ROK
*              failed: RFAILED
*
*       Notes: None
*
*       File:  sz_smuimme.c
*
*/

#ifdef ANSI
PUBLIC S16 szSmLclErrMsg
(
SzConCb  *conCb,
SzPeerCb *peerCb,
S1apPdu  *pdu
)
#else
PUBLIC S16 szSmLclErrMsg(conCb, peerCb, pdu)
SzConCb  *conCb;
SzPeerCb *peerCb;
S1apPdu  *pdu;
#endif
{
   U8       evnt;

   TRC2(szSmLclErrMsg)

   /* sz002.301: Increment the invalid un-expected event counter */
   peerCb->peerSts.cfm.nmbUnexpEvt++;

   szUtilsGetMsgIdx(&evnt,pdu);

   SZ_SEND_LCL_ERR_IND(PRSNT_NODEF, conCb->cd.suConnId,
                       peerCb->sztSapCb, SZT_CAUSE_UNEXP_MSG, evnt);

   SZ_FREE_SDU(pdu);

   RETVALUE(ROK);
} /* end of szSmLclErrMsg */

/*
*
*       Fun:   szSmLclErrState
*
*       Desc:  Called to send error indication to peer node
*
*       Ret:   ok:     ROK
*              failed: RFAILED
*
*       Notes: None
*
*       File:  sz_smuimme.c
*
*/

#ifdef ANSI
PUBLIC S16 szSmLclErrState
(
SzConCb  *conCb,
SzPeerCb *peerCb,
S1apPdu  *pdu
)
#else
PUBLIC S16 szSmLclErrState(conCb, peerCb, pdu)
SzConCb  *conCb;
SzPeerCb *peerCb;
S1apPdu  *pdu;
#endif
{

   TRC2(szSmLclErrState)

   /* sz002.301: Increment the invalid un-expected event counter */
   peerCb->peerSts.cfm.nmbUnexpEvt++;

   SZ_SEND_LCL_ERR_IND(PRSNT_NODEF, conCb->cd.suConnId,
                       peerCb->sztSapCb, SZT_CAUSE_INV_STATE, conCb->state);
   SZ_FREE_SDU(pdu);

   RETVALUE(ROK);
} /* end of szSmLclErrState */

/*
*
*       Fun:   szSmSndIdleStMsg
*
*       Desc:  Called to send Idle state message
*
*       Ret:   ok:     ROK
*              failed: RFAILED
*
*       Notes: None
*
*       File:  sz_sm.c
*
*/
#ifdef ANSI
PUBLIC S16 szSmSndIdleStMsg
(
SzConCb  *conCb,
SzPeerCb *peerCb,
S1apPdu  *pdu
)
#else
PUBLIC S16 szSmSndIdleStMsg(conCb, peerCb, pdu)
SzConCb  *conCb;
SzPeerCb *peerCb;
S1apPdu  *pdu;
#endif
{ 
   S16 ret = RFAILED;

#ifdef SZ_ENB
   TknU8 *eNbId = NULLP;
#endif /* SZ_ENB */
   U8    evnt;

   TRC2(szSmSndIdleStMsg)


      conCb->cd.spConnId = conCb->lclConRefNo;

   szUtilsGetMsgIdx(&evnt,pdu);

#ifdef SZ_ENB
   if(peerCb->nodeType == LSZ_NODE_MME)
   {
      switch(evnt)
      {
         case SZT_MSG_ID_INIT_UE_MSG:
         case SZT_MSG_ID_PATH_SWTCH_REQ:
            szGetIE(&pdu->pdu, Sztid_eNB_UE_S1AP_ID, &eNbId);
            if(NULLP != eNbId)
            {
               ((SztENB_UE_S1AP_ID *)eNbId)->val = conCb->lclConRefNo;
            }
            else
            {
               /*Sending local error indication and releasing the pdu*/
               SZ_SEND_LCL_ERR_IND(PRSNT_NODEF, conCb->cd.suConnId,
                     peerCb->sztSapCb, SZT_CAUSE_PC_TX_SYNTAX_ERR, 0);
               SZ_FREE_SDU(pdu);
               RETVALUE(RFAILED);
            }
            break;
      }
   }
#endif


   /* Change the state to Connection in progress */
   conCb->state = SZ_SMSZ_CONNECTING;

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

      /* Deleate the connection control block */
      szNdbDeallocConCb(conCb->lclConRefNo,peerCb, SZ_CONN_REF_LCL);

#if (ERRCLASS & ERRCLS_INT_PAR)
      SZLOGERROR(ERRCLS_INT_PAR, ESZ142, (ErrVal) conCb->lclConRefNo,
            "szSmSndDlNasTpt: Lower Interface send failed");
#endif
   }

   RETVALUE(ret);
} /* end of szSmSndIdleStMsg */


#ifdef SZ_ENB
/*
*
*       Fun:   szSmSndConnStHoFail
*
*       Desc:  Called to send Handover Failure in connecting state
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
PUBLIC S16 szSmSndConnStHoFail
(
SzConCb  *conCb,
SzPeerCb *peerCb,
S1apPdu  *pdu
)
#else
PUBLIC S16 szSmSndConnStHoFail(conCb, peerCb, pdu)
SzConCb  *conCb;
SzPeerCb *peerCb;
S1apPdu  *pdu;
#endif
{
   S16 ret = RFAILED;

   TRC2(szSmSndConnStHoFail)

   /* Send decoded data to peer */
   ret = szLiSndToLower(peerCb, conCb, pdu);
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
#if (ERRCLASS & ERRCLS_INT_PAR)
      SZLOGERROR(ERRCLS_INT_PAR, ESZ143, (ErrVal) conCb->lclConRefNo,
            "szSmSndConnStHoFail: Lower Interface send failed");
#endif
   }

   /* Change the state to idle */
   conCb->state = SZ_SMSZ_IDLE;

   /* Deallocate connection control block */
   ret = szNdbDeallocConCb(conCb->lclConRefNo, peerCb, SZ_CONN_REF_LCL);
#if (ERRCLASS & ERRCLS_DEBUG)
   if(ret == RFAILED)
   {
      SZLOGERROR(ERRCLS_DEBUG, ESZ144, (ErrVal) conCb->lclConRefNo,
            "szSmSndConnStHoFail: Couldn't retreive connection CB");
   }
#endif
   RETVALUE(ret);
} /* end of szSmSndConnStHoFail */
#endif
/*
*
*       Fun:   szSendPeerErrInd
*
*       Desc:  This function is used to fill and send peer error indication 
*              
*
*       Ret:   ROK     - ok
*              RFAILED - failure
*
*       Notes: N/A
*
*       File:  sz_sm.c
*
*/
#ifdef ANSI
PRIVATE S16 szSendPeerErrInd
(
S1apPdu   *pdu,
SzPeerCb  *peerCb      /* Peer control block */
)
#else
PRIVATE S16 szSendPeerErrInd(pdu, peerCb)
S1apPdu   *pdu;
SzPeerCb  *peerCb;      /* Peer control block */
#endif
{
   Mem mem;
   S16 retVal = ROK; /* Return value */
   S1apPdu  *errPdu = NULLP;  /* Error Indication PDU */
   U32 cause = SztCauseProttransfer_syntax_errorEnum;
   CmPAsnErr asnErr;

   mem.region = peerCb->sctSapCb->pst.region;
   mem.pool   = peerCb->sctSapCb->pst.pool;

#ifdef CM_PASN_CRIT_HANDL
   asnErr.ieCount = 0;
#endif /* CM_PASN_CRIT_HANDL */

   retVal =  szDbFillErrInd(pdu, CAUSE_PROTOCOL, cause, &errPdu, mem, &asnErr);
   if(ROK != retVal)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SZLOGERROR(ERRCLS_INT_PAR, ESZ063, (ErrVal) peerCb->peerId,
            "szSendPeerErrInd: Error Indication send failed");
#endif
      RETVALUE(retVal);
   }
#ifdef LSZV1
   /* Increment the error statistics */
   szIncErrSts(peerCb, CAUSE_PROTOCOL, cause);
#endif

   /* Send decoded data to its User */
   retVal = szLiSndToLower(peerCb, NULLP, errPdu);
   if (ROK != retVal)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SZLOGERROR(ERRCLS_INT_PAR, ESZ063, (ErrVal) peerCb->peerId,
            "szSendPeerErrInd: Lower Interface send failed");
#endif
      RETVALUE(retVal);
   }
   RETVALUE(retVal);
}/*end of szSendPeerErrInd*/




/*
*
*       Fun:  szSmRcvIdleStMsg
*
*       Desc:  Called to receive Idle state message
*
*       Ret:   ok:     ROK
*              failed: RFAILED
*
*       Notes: None
*
*       File:  sz_sm.c
*
*/

#ifdef ANSI
PUBLIC S16 szSmRcvIdleStMsg
(
SzConCb  *conCb,
SzPeerCb *peerCb,
S1apPdu  *pdu
)
#else
PUBLIC S16 szSmRcvIdleStMsg(conCb, peerCb, pdu)
SzConCb  *conCb;
SzPeerCb *peerCb;
S1apPdu  *pdu;
#endif
{
   SztConInd conInd;
   S16 ret = RFAILED;

#ifdef SZ_ENB
   TknU8 *mmeS1apId = NULLP;
#endif /* SZ_ENB */
   U8    evnt;

   TRC2(szSmRcvIdleStMsg)

   ret = szNdbAllocConCb(&conCb, peerCb);

   if(ret != ROK)
   {
      RETVALUE(RFAILED);
   }

   SZ_ZERO(&conInd, sizeof(SztConInd));

   /* This function will always return ROK */
   szNdbGetStream(conCb->cd.peerCb, &conCb->cd.streamNo);

   szUtilsGetMsgIdx(&evnt,pdu);
   /* sz003.301: Added hooks for PSF-S1AP */
   conCb->conType   = SZ_INCMG_CONN;

#ifdef SZ_ENB
   if(peerCb->nodeType == LSZ_NODE_MME)
   {
      switch(evnt)
      {
         case SZT_MSG_ID_DL_NAS_TPT:
         case SZT_MSG_ID_HO_REQ:
              szGetIE(&pdu->pdu, Sztid_MME_UE_S1AP_ID, &mmeS1apId);
            if(NULLP != mmeS1apId)
            {
              conCb->rmtConRefNo = (((SztMME_UE_S1AP_ID *)mmeS1apId)->val); 
            }
            else
            {
               ret = szSendPeerErrInd(pdu,peerCb);
               SZ_FREE_SDU(pdu);
               RETVALUE(ret);
            }
         break;
      }
   }
#endif


   conCb->cd.spConnId = conCb->lclConRefNo;

   /* Change the state to Connection in progress */
   conCb->state = SZ_SMSZ_CONNECTING;

   conInd.peerId.pres = TRUE;
   conInd.peerId.val = conCb->cd.peerCb->peerId;
   conInd.u.spConnId = conCb->cd.spConnId;
   conInd.pdu = pdu;

   /* Add connection CB into peerCb remote connection hash list */
   ret = cmHashListInsert (&peerCb->conRefLstRem, (PTR)conCb,
         (U8 *)&conCb->rmtConRefNo, sizeof (SzConRefNo));

   /* Handle the failure procedure in case not able to insert into
    * hash list */
   /* sz008.301 : added the Generic check */
   if(ret != ROK  ||(ROKDUP == ret))
   {
      /* Deallocate the connection control block */
      szNdbDeallocConCb(conCb->lclConRefNo,conCb->cd.peerCb, SZ_CONN_REF_LCL);
      SZ_FREE_SDU(pdu);
#if (ERRCLASS & ERRCLS_INT_PAR)
      SZLOGERROR(ERRCLS_INT_PAR, ESZ147, (ErrVal) conCb->lclConRefNo,
                 "szSmRcvInitUeMsg: Hashlist insertion failed");
#endif
      RETVALUE(ret);
   }

   /* Send decoded data to its User */
   ret = szUiSndConInd(conCb, &conInd);

   if(ret == RFAILED)
   {
      /* Deallocate the connection control block */
      szNdbDeallocConCb(conCb->lclConRefNo,conCb->cd.peerCb, SZ_CONN_REF_LCL);
      SZ_FREE_SDU(pdu);
#if (ERRCLASS & ERRCLS_INT_PAR)
      SZLOGERROR(ERRCLS_INT_PAR, ESZ148, (ErrVal) conCb->lclConRefNo,
                 "szSmRcvInitUeMsg: Upper Interface send failed");
#endif
   }

   RETVALUE(ret);
} /* end of szSmRcvIdleStMsg */

/*
*
*       Fun:  szSmRcvConnStMsg
*
*       Desc:  Called to handle receive of connecting state messages
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
PUBLIC S16 szSmRcvConnStMsg
(
SzConCb  *conCb,
SzPeerCb *peerCb,
S1apPdu  *pdu
)
#else  
PUBLIC S16 szSmRcvConnStMsg(conCb, peerCb, pdu)
SzConCb  *conCb;
SzPeerCb *peerCb;
S1apPdu  *pdu;
#endif
{  
   S16 ret = RFAILED;

   SztConCfm conCfm;
   SzConCb  *dupConCb = NULLP;

#ifdef SZ_ENB
   TknU8 *mmeS1apId = NULLP;
#endif /* SZ_ENB */
   U8    evnt;

   TRC2(szSmRcvConnStMsg)

   SZ_ZERO(&conCfm, sizeof(SztConCfm));

   szUtilsGetMsgIdx(&evnt,pdu);

#ifdef SZ_ENB
   if(peerCb->nodeType == LSZ_NODE_MME)
   {
      switch(evnt)
      {
         case SZT_MSG_ID_CXT_SETUP_REQ:
         case SZT_MSG_ID_PATH_SWTCH_REQ_ACK:
         case SZT_MSG_ID_DL_NAS_TPT:
              szGetIE(&pdu->pdu, Sztid_MME_UE_S1AP_ID, &mmeS1apId);
              if(NULLP != mmeS1apId)
              {
                 conCb->rmtConRefNo = (((SztMME_UE_S1AP_ID *)mmeS1apId)->val); 
              }
              else
              {
                 ret = szSendPeerErrInd(pdu,peerCb);
                 SZ_FREE_SDU(pdu);
                 RETVALUE(ret);
              }
         break;
      }
   }
#endif


   conCb->cd.spConnId = conCb->lclConRefNo;

   conCfm.suConnId = conCb->cd.suConnId;
   conCfm.spConnId = conCb->cd.spConnId;
   conCfm.pdu = pdu;
/* Multi eNB support */
#ifdef MULTI_ENB_SUPPORT
   conCfm.enbId = currEnbId;
#endif

   /* Change the state to connected */
   conCb->state = SZ_SMSZ_ESTABLISHED;

   /* sz003.301: Added hooks for PSF-S1AP */
   /* Send the runtime update message to peer for state updation */
#ifdef YT
   YT_RTUPD_MOD(YT_UPD_CONN_CB, conCb);
#endif /* YT */

   /* Add connection CB in peerCb remote connection hash list */
   ret = cmHashListInsert (&peerCb->conRefLstRem, (PTR)conCb,
         (U8 *)&conCb->rmtConRefNo, sizeof (SzConRefNo));

   /* Handle the failure procedure in case not able to insert into
    * hash list */
	
   if((ret == RFAILED)) 
   {
      /* Deallocate the connection control block */
      szNdbDeallocConCb(conCb->lclConRefNo, conCb->cd.peerCb, SZ_CONN_REF_LCL);
      SZ_FREE_SDU(pdu);
      /* send error indication for the old enb ue s1ap entry */
      SZ_SEND_LCL_ERR_IND(PRSNT_NODEF, conCb->cd.suConnId,
            peerCb->sztSapCb, SZT_CAUSE_HASH_INS_FAIL, conCb->cd.suConnId);
#if (ERRCLASS & ERRCLS_INT_PAR)
      SZLOGERROR(ERRCLS_INT_PAR, ESZ149, (ErrVal) conCb->lclConRefNo,
                 "szSmRcvConnStMsg: Hashlist insertion failed");
#endif
      RETVALUE(ret);
   }

   if(ROKDUP == ret)
   {

      ret = cmHashListFind (&peerCb->conRefLstRem, 
            (U8 *)&conCb->rmtConRefNo,sizeof(U32),0,(PTR*)&dupConCb);

      cmHashListDelete (&peerCb->conRefLstRem, (PTR)dupConCb);
      ret = cmHashListInsert (&peerCb->conRefLstRem, (PTR)conCb,
            (U8 *)&conCb->rmtConRefNo, sizeof (SzConRefNo));
      
      /* Send decoded data to its User */
      ret = szUiSndConCfm(conCb, &conCfm);
      /* send error indication for the old enb ue s1ap entry */
      SZ_SEND_LCL_ERR_IND(PRSNT_NODEF, dupConCb->cd.suConnId,
            peerCb->sztSapCb, SZT_CAUSE_DUP_CONID, dupConCb->cd.suConnId);

      RETVALUE(ret);
   }

   /* Send decoded data to its User */
   ret = szUiSndConCfm(conCb, &conCfm);

   RETVALUE(ret);
} /* end of szSmRcvConnStMsg */

/*
*
*       Fun:  szSmRcvEstStMsg
*
*       Desc:  Called to receive messages in established state
*
*       Ret:   ok:     ROK
*              failed: RFAILED
*
*       Notes: None
*
*       File:  sz_smlimme.c
*
*/

#ifdef ANSI
PUBLIC S16 szSmRcvEstStMsg
(
SzConCb  *conCb,
SzPeerCb *peerCb,
S1apPdu  *pdu
)
#else
PUBLIC S16 szSmRcvEstStMsg(conCb, peerCb, pdu)
SzConCb  *conCb;
SzPeerCb *peerCb;
S1apPdu  *pdu;
#endif
{
   S16            ret = RFAILED;
   SztDatEvntInd  datEvnt;
   S1apPdu        *errPdu = NULLP;     /* Response Error S1AP PDU */
   Mem            mem;                 /* Memory block */
   SztUE_S1AP_IDs *ueS1apId = NULLP;
   U16            szErrCause = 0;
#ifdef SZ_ENB
   TknU8          *mmeS1apId = NULLP;
#endif
   U8             evnt;

   TRC2(szSmRcvEstStMsg)

   mem.region = peerCb->sctSapCb->pst.region;
   mem.pool   = peerCb->sctSapCb->pst.pool;

#ifdef SZ_ENB
   if(peerCb->nodeType == LSZ_NODE_MME)
   {
      szErrCause = SztCauseRadioNwunknown_mme_ue_s1ap_idEnum;

      /* Get mmeId from S1AP Msg, if it exsits */
      szGetIE(&(pdu->pdu), Sztid_MME_UE_S1AP_ID, &mmeS1apId);

      if (mmeS1apId == NULLP)
      {
         szGetIE(&(pdu->pdu), Sztid_UE_S1AP_IDs, (TknU8 **)&ueS1apId);
          
         if (ueS1apId != NULLP)
         {
            switch (ueS1apId->choice.val)
            {
               case UE_S1AP_IDS_UE_S1AP_ID_PAIR:
                  mmeS1apId = (TknU8*)&ueS1apId->val.uE_S1AP_ID_pair.mME_UE_S1AP_ID;
                  szErrCause = SztCauseRadioNwunknown_pair_ue_s1ap_idEnum;
                  break;
            }
         }
      }
      if ((mmeS1apId == NULLP) || (((SztMME_UE_S1AP_ID *)mmeS1apId)->val != conCb->rmtConRefNo))
      {
         szUtilsGetMsgIdx(&evnt, pdu);

         /* Donot trigger the error indication to peer if the message is
          * error indication */
         if(evnt != SZT_MSG_ID_ERR_IND)
         {
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
         /* Trigger local error indication */
         else
         {
            SZ_SEND_LCL_ERR_IND(PRSNT_NODEF, conCb->cd.suConnId,
                  peerCb->sztSapCb, SZT_CAUSE_INV_CONID, 0);
         }
      }
   }
#endif

   SZ_ZERO(&datEvnt, sizeof(SztDatEvntInd));

   datEvnt.suConnId = conCb->cd.suConnId;
   datEvnt.pdu = pdu;

   /* Send decoded data to its User */
   ret = szUiSndDatInd(conCb, &datEvnt);

   if(ret == RFAILED)
   {
      SZ_FREE_SDU(pdu);
#if (ERRCLASS & ERRCLS_INT_PAR)
      SZLOGERROR(ERRCLS_INT_PAR, ESZ150, (ErrVal) conCb->lclConRefNo,
            "szSmRcvEstStMsg: Upper Interface send failed");
#endif
   }

   RETVALUE(ret);
} /* end of szSmRcvEstStMsg */

/*
*
*       Fun:   szSmIdleStPeerErr 
*
*       Desc:  Called to send error indication to peer node
*
*       Ret:   ok:     ROK
*              failed: RFAILED
*
*       Notes: None
*
*       File:  sz_smlimme.c
*
*/

#ifdef ANSI
PUBLIC S16 szSmIdleStPeerErr
(
SzConCb  *conCb,                      /* Connection control block */
SzPeerCb *peerCb,
S1apPdu  *pdu                         /* S1AP PDU */
)
#else
PUBLIC S16 szSmIdleStPeerErr(conCb, peerCb, pdu)
SzConCb  *conCb;                      /* Connection control block */
SzPeerCb *peerCb;
S1apPdu  *pdu;                        /* S1AP PDU */
#endif
{
   SztUE_S1AP_IDs  *ueS1apId = NULLP;
#ifdef SZ_ENB
   TknU8           *eNbS1apId = NULLP;
#endif
   S16             ret = RFAILED;
   S1apPdu         *errPdu = NULLP;     /* Response Error S1AP PDU */
   Mem             mem;                 /* Memory block */
   U16             szErrCause = 0;        /* Error cause */

   TRC2(szSmIdleStPeerErr)

   mem.region = peerCb->sctSapCb->pst.region;
   mem.pool   = peerCb->sctSapCb->pst.pool;

#ifdef SZ_ENB
   if(peerCb->nodeType == LSZ_NODE_MME)
   {
      szErrCause = SztCauseRadioNwunknown_enb_ue_s1ap_idEnum;

      /* Get eNBId from S1AP Msg, if it exsits */
      szGetIE(&(pdu->pdu), Sztid_eNB_UE_S1AP_ID, &eNbS1apId);

      if (eNbS1apId == NULLP)
      {
         szGetIE(&(pdu->pdu), Sztid_UE_S1AP_IDs, (TknU8 **)&ueS1apId);

         if (ueS1apId != NULLP)
         {
            switch (ueS1apId->choice.val)
            {
               case UE_S1AP_IDS_UE_S1AP_ID_PAIR:
                  {
                     /* If s1ap id was extracted from pair then fill
                        invalid pair id error in errPdu */
                     szErrCause = SztCauseRadioNwunknown_pair_ue_s1ap_idEnum;
                  }
                  break;
               case UE_S1AP_IDS_MME_UE_S1AP_ID:
                  {
                     /* If MME Ue s1ap ID is wrong */
                     szErrCause = SztCauseRadioNwunknown_mme_ue_s1ap_idEnum;
                  }
                  break;
               default:
                  break;
            }
         }
      }
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
#if (ERRCLASS & ERRCLS_INT_PAR)
            SZLOGERROR(ERRCLS_INT_PAR, ESZ151, (ErrVal)ret,
                  "szSmIdleStPeerErr: Lower Interface send failed");
#endif
      }
   }
#endif


   SZ_FREE_SDU(pdu);

   RETVALUE(ret);
} /* end of szSmIdleStPeerErr */

/*
*
*       Fun:   szSmPeerErrHdlr
*
*       Desc:  Called to send error indication to peer node
*
*       Ret:   ok:     ROK
*              failed: RFAILED
*
*       Notes: None
*
*       File:  sz_smlimme.c
*
*/

#ifdef ANSI
PUBLIC S16 szSmPeerErrHdlr
(
SzConCb  *conCb,                      /* Connection control block */
SzPeerCb *peerCb,
S1apPdu  *pdu                         /* S1AP PDU */
)
#else
PUBLIC S16 szSmPeerErrHdlr(conCb, peerCb, pdu)
SzConCb  *conCb;                      /* Connection control block */
SzPeerCb *peerCb;
S1apPdu  *pdu;                        /* S1AP PDU */
#endif
{
   S16      ret = RFAILED;           /* return value */
   S1apPdu  *errPdu;                 /* Response PDU */
   Mem      mem;                     /* Memory block */

   TRC2(szSmPeerErrHdlr)

   errPdu = NULLP;

   mem.region = peerCb->sctSapCb->pst.region;
   mem.pool   = peerCb->sctSapCb->pst.pool;

   /* sz002.301: Increment the invalid un-expected event counter */
   peerCb->peerSts.cfm.nmbUnexpEvt++;

   /* Call function to generate errPdu */
   ret = szLiErrHndlr(pdu, CAUSE_PROTOCOL,
                      SztCauseProtmessage_not_compatible_with_receiver_stateEnum,
                                                                     &errPdu, mem);
   
#ifdef LSZV1
            /* Increment the error statistics */
            szIncErrSts(peerCb, CAUSE_PROTOCOL,
                   SztCauseProtmessage_not_compatible_with_receiver_stateEnum);
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

#if (ERRCLASS & ERRCLS_INT_PAR)
      SZLOGERROR(ERRCLS_INT_PAR, ESZ153, (ErrVal) conCb->lclConRefNo,
            "szSmPeerErrHdlr: Lower Interface send failed");
#endif
   }

   SZ_FREE_SDU(pdu);

   RETVALUE(ret);
} /* end of szSmPeerErrHdlr */

/*
*
*       Fun:   szSmSemPeerErr
*
*       Desc:  Called to send semantic error indication to peer node
*
*       Ret:   ok:     ROK
*              failed: RFAILED
*
*       Notes: None
*
*       File:  sz_smlimme.c
*
*/

#ifdef ANSI
PUBLIC S16 szSmSemPeerErr
(
SzConCb  *conCb,                      /* Connection control block */
SzPeerCb *peerCb,
S1apPdu  *pdu                         /* S1AP PDU */
)
#else
PUBLIC S16 szSmSemPeerErr(conCb, peerCb, pdu)
SzConCb  *conCb;                      /* Connection control block */
SzPeerCb *peerCb;
S1apPdu  *pdu;                        /* S1AP PDU */
#endif
{
   S16      ret = RFAILED;           /* return value */
   S1apPdu  *errPdu;                 /* Response PDU */
   Mem      mem;                     /* Memory block */

   TRC2(szSmSemPeerErr)

   errPdu = NULLP;

   mem.region = peerCb->sctSapCb->pst.region;
   mem.pool   = peerCb->sctSapCb->pst.pool;

   /* sz002.301: Increment the invalid un-expected event counter */
   peerCb->peerSts.cfm.nmbUnexpEvt++;

   /* Call function to generate errPdu */
   ret = szLiErrHndlr(pdu, CAUSE_PROTOCOL,
                      SztCauseProtsemantic_errorEnum, &errPdu, mem);
   
#ifdef LSZV1
   /* Increment the error statistics */
   szIncErrSts(peerCb, CAUSE_PROTOCOL,
                           SztCauseProtsemantic_errorEnum);
#endif

   /* Send decoded data to its User */
   ret = szLiSndToLower(peerCb,conCb, errPdu);
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

#if (ERRCLASS & ERRCLS_INT_PAR)
      SZLOGERROR(ERRCLS_INT_PAR, ESZ154, (ErrVal) conCb->lclConRefNo,
            "szSmPeerErrHdlr: Lower Interface send failed");
#endif
   }

   SZ_FREE_SDU(pdu);

   RETVALUE(ret);
} /* end of szSmSemPeerErr */

/*
*
*       Fun:  szSmRcvIdleStErrInd
*
*       Desc:  Called to handle receive of idle state error indication
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
PUBLIC S16 szSmRcvIdleStErrInd 
(
SzConCb  *conCb,
SzPeerCb *peerCb,
S1apPdu  *pdu
)
#else
PUBLIC S16 szSmRcvIdleStErrInd(conCb, peerCb, pdu)
SzConCb  *conCb;
SzPeerCb *peerCb;
S1apPdu  *pdu;
#endif
{
   S16         ret = ROK;            /* Return value */
   SztUDatEvnt uDatEvnt;             /* Connectionless data */

   TRC2(szSmRcvIdleStErrInd);

   SZ_ZERO(&uDatEvnt, sizeof(SztUDatEvnt));
 
   uDatEvnt.transId.pres = NOTPRSNT;
   uDatEvnt.peerId.val = peerCb->peerId;
   uDatEvnt.pdu = pdu;

   /* Send data to the user */
   ret = szUiSndUDatInd(peerCb, &uDatEvnt);
#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
      SZLOGERROR(ERRCLS_DEBUG, ESZ155, (ErrVal)peerCb->peerId,
                 "szSmRcvIdleStErrInd: Failed to send error indication the user");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

   RETVALUE(ret);

} /* szSmRcvIdleStErrInd */

/*
*
*       Fun:  szSmRcvConnStErrInd
*
*       Desc:  Called to handle receive of connecting state error indication
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
PUBLIC S16 szSmRcvConnStErrInd
(
SzConCb  *conCb,
SzPeerCb *peerCb,
S1apPdu  *pdu
)
#else
PUBLIC S16 szSmRcvConnStErrInd(conCb, peerCb, pdu)
SzConCb  *conCb;
SzPeerCb *peerCb;
S1apPdu  *pdu;
#endif
{  
   S16 ret = RFAILED;
#ifdef SZ_ENB
   TknU8 *mmeS1apId = NULLP;
#endif
   SztRelInd relInd;

   TRC2(szSmRcvConnStErrInd)

#ifdef SZ_ENB
   if(peerCb->nodeType == LSZ_NODE_MME)
   {
      szGetIE(&pdu->pdu, Sztid_MME_UE_S1AP_ID, &mmeS1apId);
      if(mmeS1apId != NULLP)
      {
         conCb->rmtConRefNo = (((SztMME_UE_S1AP_ID *)mmeS1apId)->val); 
      }
   }
#endif


   conCb->cd.spConnId = conCb->lclConRefNo;

   SZ_ZERO(&relInd, sizeof(SztRelInd));

   relInd.suConnId.pres = PRSNT_NODEF;
   relInd.suConnId.val  = conCb->cd.suConnId;
   relInd.spConnId = conCb->cd.spConnId;
   relInd.pdu = pdu;

   /* Change the state to connected */
   conCb->state = SZ_SMSZ_RELEASING;

   /* Send decoded data to its User */
   ret = szUiSndRelInd(conCb, &relInd);

   RETVALUE(ret);
} /* end of szSmRcvConnStErrInd */




#ifdef SZ_ENB    
/*
*
*       Fun:  szSmRcvConnStPathSwReqFail
*
*       Desc:  Called to handle Path Switch Request Failure in connecting state
*
*       Ret:   ok:     ROK
*              failed: RFAILED
*
*       Notes: None
*
*       File:  sq_sm.c
*
*/
#ifdef ANSI
PUBLIC S16 szSmRcvConnStPathSwReqFail
(
SzConCb  *conCb,
SzPeerCb *peerCb,
S1apPdu  *pdu
)
#else
PUBLIC S16 szSmRcvConnStPathSwReqFail(conCb, peerCb, pdu)
SzConCb  *conCb;
SzPeerCb *peerCb;
S1apPdu  *pdu;
#endif
{
   S16        ret = RFAILED;
   SztRelInd  relInd;

   TRC2(szSmRcvConnStPathSwReqFail)

   conCb->cd.spConnId = conCb->lclConRefNo;

   SZ_ZERO(&relInd, sizeof(SztRelInd));

   relInd.suConnId.pres = PRSNT_NODEF;
   relInd.suConnId.val  = conCb->cd.suConnId;
   relInd.spConnId      = conCb->cd.spConnId;
   relInd.pdu           = pdu;

   /* Change the state to idle */
   conCb->state = SZ_SMSZ_IDLE;

   /* Send decoded data to its User */
   ret = szUiSndRelInd(conCb, &relInd);

   /* Deallocate connection control block */
   ret = szNdbDeallocConCb(conCb->lclConRefNo, peerCb, SZ_CONN_REF_LCL);
#if (ERRCLASS & ERRCLS_DEBUG)
   if(ret == RFAILED)
   {
      SZLOGERROR(ERRCLS_INT_PAR, ESZ157, (ErrVal) conCb->lclConRefNo,
           "szSmRcvConnStPathSwReqFail: Couldn't dealloc Connection CB");
   }
#endif 
   RETVALUE(ret);
} /* end of szSmRcvConnStPathSwReqFail */
#endif


/*
 *
 *       Fun:   szSmExecMt
 *
 *       Desc:  This function invokes state based event handler
 *
 *       Ret:   ROK     - success
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  sz_ui.c
 *
 */
 
#ifdef ANSI
PUBLIC S16 szSmExcMt
(
SzConCb  *conCb,
SzPeerCb *peerCb,
S1apPdu  *pdu,
U8       evnt,
U8       dir
)
#else
PUBLIC S16 szSmExcMt(conCb, peerCb, pdu, evnt, dir)
SzConCb  *conCb;
SzPeerCb *peerCb;
S1apPdu  *pdu;
U8       evnt;
U8       dir;
#endif
{
   U8 state;
   S16 ret = RFAILED;

   TRC2(szSmExecMt)

   state = SZ_SMSZ_IDLE;
   
   if (conCb != NULLP) 
   {
      state = conCb->state;
   }

#ifdef SZ_ENB
   if(peerCb->nodeType == LSZ_NODE_MME)
   {
      if(dir == SZ_UI)
      {
         ret = szSmUiEnb[evnt][state](conCb, peerCb, pdu);
      }
      else if(dir == SZ_LI)
      {
         ret = szSmLiEnb[evnt][state](conCb, peerCb, pdu);
      }
   }
#endif
   return(ret);
}

/**********************************************************************

         End of file:     sq_sm.c@@/main/4 - Mon Jan 10 22:17:05 2011

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
/main/4     sz002.301   pkaX      1. Handled the un-expected event statistics
                                     correctly.
/main/4   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
/main/4   sz008.301 akaranth1. Support for source RNC to target RNC.
                            2. Fix for Kwork. 
                            3. Added the generic check in the function szSmRcvIdleStMsg.
                               After returning from the cmHashListInsert.
                            4. Added support to check the MME_UE_S1AP_ID in the ue context
                               release command message.
*********************************************************************91*/
