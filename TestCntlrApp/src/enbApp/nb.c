/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

/**********************************************************************

    Name:  LTE S1SIM - ENODEB Application Module

    Type:  C include file

    Desc:  C source code for ENODEB Application

     File:     nb.c

    Sid:

     Prg:

**********************************************************************/

#include "nb.h"
#include "rl_interface.h"
#include "rl_common.h"
#include "nb_smm_init.h"
#include "nbt.h"
#include "nb_dam.h"
#include "nb_ifm_dam.h"
#include "nb_utils.h"
#include "nb_log.h"
#include "nbt.x"

int atoi(const char *nptr);
PUBLIC NbCb nbCb;
EXTERN U8 uesLocalRel;

PUBLIC S16 NbEnbUeCtxtRelForInitCtxtSetup(NbSendUeCtxtRelForICSRsp *sendUeCtxtRelReq);
PUBLIC S16 NbEnbDelayInitCtxtSetupRsp(NbDelayICSRsp *delayICSRsp);
PUBLIC S16 NbEnbDropInitCtxtSetup(NbDropInitCtxtSetup *dropInitCtxtSetup);
PUBLIC S16 nbDelUeCb(U32 ueId);
PUBLIC S16 nbUeTnlCreatCfm(U8, U32);
PUBLIC S16 nbPrcDamUeDelCfm(U32);
PUBLIC S16 nbCreateUeTunnReq(U32 ueId, U8 bearerId, U32 ueIp4Addr, U8 *ipv6_addr,
                             NbuUeIpInfoRsp *rsp);
PUBLIC S16 NbEnbUeRelReqHdl(NbUeCntxtRelReq*);
PUBLIC S16 NbEnbResetReqHdl(NbResetRequest *resetReq);
/*PUBLIC S16 NbEnbErabRelIndHdl(NbErabRelInd *erabRelInd);*/
PUBLIC S16 NbEnbErabRelIndHdl(NbuErabRelIndList *erabRelInd);
PUBLIC S16 NbEnbErabRelRspHdl(NbErabRelRsp *erabRelInd);
PUBLIC S16 NbEnbNasNonDel(NbNasNonDel *nasNonDel);
PUBLIC S16 NbEnbInitCtxtSetupFail(NbInitCtxtSetupFail *initCtxtSetupFail);

EXTERN S16 nbIfmDamTnlCreatReq(NbDamTnlInfo*);
EXTERN S16 nbIfmDamUeRelReq(U32, U8);
EXTERN S16 nbAppRouteInit(U32 selfIp, S8*);

EXTERN NbDamCb nbDamCb;

/* @brief This function updates the MME control Block with
 *       GUMMEIs received in S1 Setup response message.
 *
 * @details This function updates the MME control Block with
 *    GUMMEIs received in S1 Setup response message.
 *
 * Function: nbEmmMmePrcGummeis
 *
 *       Processing steps:
 *        -
 *
 *       - Notes: We support only LTE PLMN IDs and hence we process
 *           only one IE in this function.
 *
 *@param[in, out] mmeCb: MME control block.
 * @param[in]         ie: served GUMME IDs IE receved in
 *                      S1-Setup Response msg.
 *@return  S16
 *          -# Success : ROK
 */
PRIVATE S16 nbMmePrcGummeis
(
 NbMmeCb   *mmeCb,
 SztProtIE_Field_S1SetupRespIEs *ie
)
{
   U32                         idx;
   SztSrvdGUMMEIs              *gummeis = &ie->value.u.sztSrvdGUMMEIs;
   SztSrvdGUMMEIsItem          *gummei  = gummeis->member;
   SztSrvdPLMNs                *plmns   = &gummei->servedPLMNs;
   NbPlmnId                    plmnId;
   U32                         noPlmns = plmns->noComp.val;
   SztSrvdGroupIDs             *grpIds = &gummei->servedGroupIDs;
   SztSrvdMMECs                *mmeCs = &gummei->servedMMECs;
   U32                         noGrpIds;
   U32                         noMmeCs;

   NB_LOG_ENTERFN(&nbCb);

   if (noPlmns > NB_MAX_PLMNS_PER_MME)
   {
      noPlmns = NB_MAX_PLMNS_PER_MME;
   }

   for (idx = 0; idx < noPlmns; idx++)
   {
      nbParsePlmnIe(plmns->member + idx, &plmnId);
      nbAddPlmnId(mmeCb, &plmnId);
   }

   noGrpIds = grpIds->noComp.val;
   if(noGrpIds > NB_MAX_GRPS_PER_MME)
   {
      noGrpIds = NB_MAX_GRPS_PER_MME;
   }

   for(idx = 0; idx < noGrpIds; idx++)
   {
      mmeCb->groupIds[idx] = (((grpIds->member + idx)->val[1]) |
            ((grpIds->member + idx)->val[0] << 8));
   }

   mmeCb->numGrpIds = noGrpIds;
   noMmeCs = mmeCs->noComp.val;
   if(noMmeCs > NB_MAX_CODES_PER_MME)
   {
      noMmeCs = NB_MAX_CODES_PER_MME;
   }

   for(idx = 0; idx < noMmeCs; idx++)
   {
      mmeCb->codes[idx] = (mmeCs->member + idx)->val[0];
   }

   mmeCb->numCodes = noMmeCs;


   RETVALUE(ROK);

}

/*
 *         Fun:     nbHandleS1SetupReq
 *
 *  Desc:    This primitive is called by SM to request
 *            EMM to invoke S1 Setup with the configured
 *             MMEs.
 *
 *  Ret:     ROK   - OK / RFAILED - Failure
 *
 *  Notes :  None.
 **/

PUBLIC S16 nbHandleS1SetupReq
(
   NbMmeId   mmeId
)
{
   NB_LOG_ENTERFN(&nbCb);

      nbBuildAndSendS1SetupReq (mmeId);
      RETVALUE(ROK);
}

/* @brief This function process the S1AP:S1 Setup Response mesage.
 *
 * @details This function process the S1AP:S1 Setup Response mesage.
 *
 *Function: wrEmmMmePrcSetupRsp
 *
 * Processing steps:
 *  - Stop the S1 Setup Response timer.
 *   - parse and Update the MME control block with the received
 *      information in S1 Setup Response.
 *     - Finally move the MME control block state is WR_MME_UP.
 *      - Send MME add request to RRM
 *       - Send an Alram to SM to indicate the S1 Setup procedure is completed
 *          successfully.
 *
 *@param[in]     peerId: Peer Id from which S1 setup resp recvd
 *@param[in]        pdu: S1-AP:setup response PDU
 *@return  S16
 *          -# Success : ROK
 *         -# Failure : RFAILED
 */
PUBLIC S16 nbPrcS1SetupRsp
(
 U32 peerId,
 S1apPdu *pdu
)
{
   U32 idx;
   NbMmeCb *mmeCb;
   SztSuccessfulOutcome *succMsg  = &pdu->pdu.val.successfulOutcome;
   SztS1SetupResp *setupRsp = &succMsg->value.u.sztS1SetupResp;
   SztProtIE_Field_S1SetupRespIEs *IEs = setupRsp->protocolIEs.member;
   /* Multi eNB support */
#ifdef MULTI_ENB_SUPPORT
   PRIVATE U32 inst = 0;
#endif

   NB_LOG_ENTERFN(&nbCb);

   mmeCb = &nbCb.mmeInfo;
   if (mmeCb == NULLP)
   {
      RETVALUE(RFAILED);
   }

   /* Stop the S1-Setup Timer started for this peer */
   /* Multi enb support */
#ifndef MULTI_ENB_SUPPORT
   nbStopTmr((PTR)mmeCb, NB_TMR_MME_SETUP_RSP);
#endif

   for (idx = 0; idx < setupRsp->protocolIEs.noComp.val; idx++)
   {
      SztProtIE_Field_S1SetupRespIEs* ie = IEs + idx;

      switch(ie->id.val)
      {
         case Sztid_RelativeMMECapacity:
            mmeCb->relCapacity = ie->value.u.sztRelativeMMECapacity.val;
            break;
         case Sztid_SrvdGUMMEIs:
            if (nbMmePrcGummeis(mmeCb, ie) != ROK)
            {
               RETVALUE(RFAILED);
            }
            break;
         case Sztid_MMEname:
            mmeCb->mmeName.len = ie->value.u.sztMMEname.len;
            cmMemcpy(mmeCb->mmeName.val, ie->value.u.sztMMEname.val,
                     mmeCb->mmeName.len);
            break;
         case Sztid_MMERelaySupportIndicator:
            mmeCb->mmeRelaySuppInd =
                                   ie->value.u.sztMMERelaySupportIndicator.val;
            break;
         default:
            NB_LOG_ERROR(&nbCb, "Wrong IE(%d) in S1 SETUP RESP", ie->id.val);
            break;
      }
   }

   mmeCb->state = NB_MME_UP;
   smCfgCb.smState = NB_SM_STATE_CELL_UP;
   UNUSED(peerId);

   /*send the mme up indication */
   /* Multi eNB support */
#ifdef MULTI_ENB_SUPPORT
   inst++;
   if(inst >= smCfgCb.numOfEnbs)
   {
      smNbProcSm(EVTNBCELLCFG);
      inst = 0;
   }
#else
   smNbProcSm(EVTNBCELLCFG);
#endif

   RETVALUE(ROK);
} /* nbPrcS1SetupRsp */

PUBLIC S16 nbPrcResetAck
(
 U32 peerId,
 S1apPdu *pdu
)
{
   S16 ret = RFAILED;
   U16 numComp = 0;
   U32 idx = 0;
   U32 mmeUeS1apId = 0;
   U32 enbUeS1apId = 0;
   U16 cnt = 0;
   U32 ueId = 0;
   NbResetAckldg nbResetAck = {0};
   SztSuccessfulOutcome *succMsg  = &pdu->pdu.val.successfulOutcome;
   SztResetAckg *resetAck = &succMsg->value.u.sztResetAckg;
   SztProtIE_Field_ResetAckgIEs *IEs = resetAck->protocolIEs.member;

   NB_LOG_ENTERFN(&nbCb);

   for (idx = 0; idx < resetAck->protocolIEs.noComp.val; idx++)
   {
      SztProtIE_Field_ResetAckgIEs *ie = IEs + idx;

      switch(ie->id.val)
      {
         case Sztid_UE_assocLogS1_ConLstResAck:
            numComp = ie->value.u.sztUE_assocLogS1_ConLstResAck.noComp.val;
            if(numComp)
            {
               nbResetAck.numOfUes = numComp;
               NB_ALLOC(&nbResetAck.ueIdLst, numComp * sizeof(U32));
            }
            for(cnt = 0; cnt < numComp; cnt++)
            {
               SztProtIE_SingleCont_UE_assocLogS1_ConItemResAck \
                  *resIe = &(ie->value.u.sztUE_assocLogS1_ConLstResAck.\
                  member[cnt]);
               enbUeS1apId = resIe->value.u.sztUE_assocLogS1_ConItem.\
                             eNB_UE_S1AP_ID.val;
               mmeUeS1apId = resIe->value.u.sztUE_assocLogS1_ConItem.\
                             mME_UE_S1AP_ID.val;
               NB_LOG_DEBUG(&nbCb,"MME_UE_S1AP_ID(%d) ENB_UE_S1AP_ID(%d)",
                     mmeUeS1apId, enbUeS1apId);
            }
            break;
         case Sztid_CriticalityDiag:
            NB_LOG_ERROR(&nbCb, "Criticality Diag Info not handled");
            break;
         default:
            NB_LOG_ERROR(&nbCb, "Invalid Id recieved");
            NB_LOG_EXITFN(&nbCb, RFAILED);
      }
   }

   if(nbUiSendResetAckToUser(&nbResetAck) != ROK)
   {
      NB_FREE(nbResetAck.ueIdLst, nbResetAck.numOfUes * sizeof(U32));
      NB_LOG_EXITFN(&nbCb, RFAILED);
   }

   NB_FREE(nbResetAck.ueIdLst, nbResetAck.numOfUes * sizeof(U32));
   uesLocalRel = FALSE;
   UNUSED(peerId);

   RETVALUE(ROK);
} /* nbPrcResetAck */

/*
 * @brief This function constructs the PLMN ID from the received S1AP PLMN IE.
 *
 * @details This function constructs the PLMN ID from the received S1AP PLMN IE.
 *
 * Function: nbParsePlmnIe
 *
 * Processing steps:
 *        -
 *
 *
 * @param[in]   plmnIe: S1-AP PLMN IE
 * @param[out]  plmnId: PLMN ID
 * @return  S16
 *          -# Success : ROK
 */
PUBLIC Void  nbParsePlmnIe
(
 SztPLMNidentity              *plmnIe,
 NbPlmnId                     *plmnId
 )
{
   NB_LOG_ENTERFN(&nbCb);

   plmnId->mcc[0]          = plmnIe->val[0] &0x0f;
   plmnId->mcc[1]          = (plmnIe->val[0] & 0xf0) >> 4;
   plmnId->mcc[2]          = plmnIe->val[1] &0x0f;
   if ((plmnIe->val[1] & 0xf0) == 0xf0)
   {
      plmnId->numMncDigits = 2;
      plmnId->mnc[1]       = (plmnIe->val[2] & 0xf0) >> 4;
      plmnId->mnc[0]       = plmnIe->val[2] & 0x0f;
   }
   else
   {
      plmnId->numMncDigits = 3;
      plmnId->mnc[0]       = (plmnIe->val[1] & 0xf0) >> 4;
      plmnId->mnc[1]       = plmnIe->val[2] & 0x0f;
      plmnId->mnc[2]       = (plmnIe->val[2] & 0xf0) >> 4;
   }
  /* RETVALUE(ROK);*/
}

PUBLIC Void nbAddPlmnId
(
NbMmeCb                      *mmeCb,
NbPlmnId                     *plmnId
)
{
   NB_LOG_ENTERFN(&nbCb);
   /* Multi eNB supoprt */
#ifndef MULTI_ENB_SUPPORT
   mmeCb->plmnIds[mmeCb->numPlmnIds] = *plmnId;
   mmeCb->numPlmnIds++;
#else
   mmeCb->plmnIds[0] = *plmnId;
   mmeCb->numPlmnIds=1;
#endif
   /*RETVALUE(ROK);*/
} /* end of  nbAddPlmnId */

PUBLIC S16 nbUeTnlCreatCfm(U8 status, U32 lclTeid)
{
   S16 ret = ROK;
   NB_LOG_ENTERFN(&nbCb);

   if(status == LCM_PRIM_OK)
   {
      NB_LOG_DEBUG(&nbCb,"Tunnel created successfully with LclTeid[%d]",lclTeid);

   }
   else
   {
      NB_LOG_ERROR(&nbCb,"Tunnel created Failed with LclTeid[%d]",lclTeid);
      ret = RFAILED;
   }
   RETVALUE(ret);
}

PUBLIC S16 nbPrcDamUeDelCfm(U32 ueId)
{
   S16 ret = ROK;

   NB_LOG_ENTERFN(&nbCb);

   NB_LOG_DEBUG(&nbCb,"all the bearer deleted related to ueId:[%d], deleting the uecb...\n",ueId);
   ret = nbDelUeCb(ueId);
   RETVALUE(ret);
}

PUBLIC S16 nbCreateUeTunnReq(U32 ueId, U8 bearerId, U32 ueIp4Addr, U8 *ipv6_addr,
                             NbuUeIpInfoRsp *rsp) {
  U8 idx = 0;
  U8 num_tft = 0;
  NbUeCb *ueCb = NULLP;
  U32 berId = bearerId;

  NbDamTnlInfo *tnlInfo = NULLP;
  NbUeTunInfo *tunInfo = NULLP;

  NB_LOG_ENTERFN(&nbCb);
  if (ROK != (cmHashListFind(&(nbCb.ueCbLst), (U8 *)&(ueId), sizeof(U32), 0,
                             (PTR *)&ueCb))) {
    RETVALUE(RFAILED);
  }

  NB_ALLOC_SHAREBLE_BUF(&tnlInfo, sizeof(NbDamTnlInfo));
  if (tnlInfo != NULLP) {
    for (idx = 0; idx < ueCb->tunnIdx; idx++) {
      if (ROK != (cmHashListFind(&(ueCb->tunnInfo), (U8 *)&(berId), sizeof(U32),
                                 0, (PTR *)&tunInfo))) {
        if (ipv6_addr) {
          NB_FREE(ipv6_addr, sizeof(ipv6_addr));
        }
        RETVALUE(RFAILED);
      } else {
        tnlInfo->tnlId.drbId = tunInfo->bearerId;
        tnlInfo->tnlType = NB_TNL_NORMAL;
        tnlInfo->remTeid = tunInfo->remTeId;
        tnlInfo->lclTeid = tunInfo->lclTeId;
        tnlInfo->pdnType = rsp->pdnType;

        if ((rsp->pdnType == NB_PDN_IPV4) || (rsp->pdnType == NB_PDN_IPV4V6)) {
          tnlInfo->pdnIp4Addr = ueIp4Addr;
        }
        if ((ipv6_addr) && ((rsp->pdnType == NB_PDN_IPV6) ||
                            (rsp->pdnType == NB_PDN_IPV4V6))) {
          cmMemcpy(tnlInfo->pdnIp6Addr, ipv6_addr, NB_IPV6_ADDRESS_LEN);
          NB_FREE(ipv6_addr, sizeof(ipv6_addr));
        }

        nbCpyCmTptAddr(&tnlInfo->dstAddr, &(tunInfo->sgwAddr));
        nbCpyCmTptAddr(&tnlInfo->srcAddr, &(nbCb.datAppAddr));
        tnlInfo->tft.lnkEpsBearId = rsp->lnkEpsBearId;
        // Fill TFT info
        if (rsp->noOfPfs) {
          tnlInfo->tft.num_pf = rsp->noOfPfs;
          cmMemcpy(tnlInfo->tft.pfList, rsp->pfList, sizeof(rsp->pfList));
        }
        RETVALUE(nbIfmDamTnlCreatReq(tnlInfo));
      }
    }
  }
  RETVALUE(RFAILED);
}

PUBLIC S16 nbDelUeCb(U32 ueId)
{

   S16 ret = RFAILED;
   NbUeCb                 *ueCb   = NULLP;  /* enbApp uecb */
   NbUeTunInfo  *prevTunnCb = NULLP;
   NbUeTunInfo  *tunnCb = NULLP;

   NB_LOG_ENTERFN(&nbCb);
#if 0
   U8 idx = 0;
   for(idx = 0; idx < nbCb.crntUeIdx; idx++)
   {
      if((nbCb.ueCbLst[idx] != NULLP) && (nbCb.ueCbLst[idx]->ueId == ueId))
      {
         ueCb = nbCb.ueCbLst[idx];
         /* delete the tunninfo cb */
#if 0
         NB_FREE(ueCb->tunnInfo,sizeof(NbUeTunInfo));
#endif
         /* delete the s1apcb */
         NB_FREE(ueCb->s1ConCb,sizeof(NbS1ConCb));
         /* delete the ueCb */
         NB_FREE(ueCb,sizeof(NbUeCb));
         nbCb.ueCbLst[idx] = NULLP;
         ret = ROK;
         /*nbCb.crntUeIdx--;*/
         NB_LOG_DEBUG(&nbCb,"UE context successfully deleted with ueId:[%d]",
               ueId);
         break;
      }
   }
#endif
   if ( ROK != (cmHashListFind(&(nbCb.ueCbLst), (U8 *)&(ueId),
      sizeof(U32),0,(PTR *)&ueCb)))
   {
      ret = RFAILED;
   }
   else
   {
#if 0
      NB_FREE(ueCb->tunnInfo,sizeof(NbUeTunInfo));
#endif
      /* delete the s1apcb */
      NB_FREE(ueCb->s1ConCb,sizeof(NbS1ConCb));
      /* delete the ueCb */
      for(;((cmHashListGetNext(&(ueCb->tunnInfo),(PTR)prevTunnCb,(PTR*)&tunnCb)) == ROK);)
      {
         if(ueCb->tunnIdx == 0)
            break;
         ret  = cmHashListDelete(&(ueCb->tunnInfo), (PTR)tunnCb);
         if (ret == RFAILED)
         {
            NB_LOG_ERROR(&nbCb,"Failed to delete TunnelCb");

         }
         NB_FREE(tunnCb, sizeof(NbUeTunInfo))
         tunnCb = NULLP;
         ueCb->tunnIdx--;
      }
      cmHashListDeinit(&(ueCb->tunnInfo));
      cmHashListDelete(&(nbCb.ueCbLst), (PTR)ueCb);
      NB_FREE(ueCb,sizeof(NbUeCb));
      ret = ROK;
      NB_LOG_DEBUG(&nbCb,"UE context successfully deleted with ueId:[%d]",
               ueId);
   }
   nbRelCntxtInTrafficHandler(ueId);
   /* - Inform the Tfw about UE context release
      - When the ue release is local release i.e
         occurred due to sctp shutdown/abort, need not to inform Stub
      - Release indication will be sent to Stub in only in case of
         when MME is Sending UE_CNTXT Release Command
   */
   if(uesLocalRel == FALSE)
   {
      ret = nbUiSendUeCtxRelIndToUser(ueId);
   }
   RETVALUE(ret);
}

PUBLIC Void nbHandleUeDelReq(NbUeCb *ueCb)
{
   SztRelReq                 s1RelReq={0};

   NB_LOG_ENTERFN(&nbCb);

   if(ROK !=nbIfmDamUeDelReq(ueCb->ueId))
   {
      NB_LOG_ERROR(&nbCb,"Failure in Lcl ue delete");
   }
   if((ueCb->s1ConCb != NULLP) &&
         (ueCb->s1ConCb->s1apConnState != NB_S1AP_NOT_CONNECTED))
   {
      s1RelReq.connId = ueCb->s1ConCb->suConnId;
      s1RelReq.connIdType = SZT_CONN_TYPE_SU;
      s1RelReq.relType = SZT_LOCAL_REL;
      if(NbIfmS1apRelReq(&s1RelReq) != ROK)
      {
         NB_LOG_ERROR(&nbCb,"Failure in S1AP Local Release");
      }

   }   /* trigger req to delete the s1ap connection cb */
   RETVOID;
}

/** @brief This function is responsible for sending context release request
 *
 * @details
 *
 *     Function: nbSndCtxtRelReq
 *
 *         Processing steps:
 *         - Process message
 *
 * @param [in] crnti : CRNTI for the UE
 * @param [in] cellId: Cell Identity
 * @param [in] event : Event values could be due to Inactivity
 * @return S16
 *       -# ROK
 *       -# RFAILED
 */
PUBLIC S16 nbSndCtxtRelReq
(
 U32                           ueId,
 NbUeMsgCause                 *relCause
)
{
   NbUeCb                    *ueCb = NULLP;
   S1apPdu                   *ctxtRelReqPdu = NULLP;

   NB_LOG_ENTERFN(&nbCb);

#if 0
   U8 idx = 0;
   for(idx = 0; idx < nbCb.crntUeIdx; idx++)
   {
      if(nbCb.ueCbLst[idx] == NULLP)
         continue;
      if(nbCb.ueCbLst[idx]->ueId == ueId)
      {
         ueCb = nbCb.ueCbLst[idx];
         break;
      }
   }
   if( ueCb == NULLP)
   {
      NB_LOG_ERROR(&nbCb,"ueCb not found");
      RETVALUE(RFAILED);
   }
#endif
   if ( ROK != (cmHashListFind(&(nbCb.ueCbLst), (U8 *)&(ueId),
      sizeof(U32),0,(PTR *)&ueCb)))
   {
      NB_LOG_ERROR(&nbCb,"ueCb not found");
      RETVALUE(RFAILED);
   }
   /* Check for s1ConCb before sending Connection release to MME */
   if(NULLP != ueCb->s1ConCb)
   {
            NB_LOG_DEBUG(&nbCb,"Sending UE CONTEXT RELEASE REQUEST" \
            ",MME-UE-S1AP-ID[%d], eNB-UE-S1AP-ID[%d]",\
            ueCb->s1ConCb->mme_ue_s1ap_id, ueCb->s1ConCb->enb_ue_s1ap_id);

      if(nbS1apFillCtxtRelReq(ueCb,&ctxtRelReqPdu, relCause) != ROK)
      {
         NB_LOG_ERROR(&nbCb, "Failed to build s1ap Context Rel Request");
         RETVALUE(RFAILED);
      }
#ifdef MULTI_ENB_SUPPORT
      nbIfmS1apSndUeMsg(ueCb->s1ConCb->spConnId, ctxtRelReqPdu, ueCb->enbId);
#else

      nbIfmS1apSndUeMsg(ueCb->s1ConCb->spConnId, ctxtRelReqPdu);
#endif
   }
   else
   {
      NB_LOG_ERROR(&nbCb, "Error in getting S1ConCb for ueId:[%d]",ueCb->ueId);
   }
   RETVALUE(ROK);
}

/*
 *@details This function is used Porocess the Received enbApp config req
 *
 *Function:NbUiNbtEnbCfgReq
 *
 * @param[in] NbConfigReq *cfg
 * @return  S16
 *  -# Success : ROK
 *   -# Failure : RFAILED
 */
PUBLIC S16 NbEnbCfgReqHdl
(
NbConfigReq   *cfg
)
{
   U16 i = 0, j = 0;
   U16 smEvent;
   U32 plmnVal;
   U8  plmnLen;
   U8  tmpPlmn[NB_THREE] = {0};
   SztPLMNidentity pLMNidentity;

   NB_LOG_ENTERFN(&nbCb);

   if (NULLP == cfg)
   {
      NB_LOG_ERROR(&nbCb,"NULL Management structure");
      RETVALUE(RFAILED);
   }

   /* If only reconfiguration of Inactivity timer is required */
   if(smCfgCb.smState == NB_SM_STATE_CELL_UP)
   {
      nbDamCb.inactvTmrVal = cfg->inactvTmrVal;
      nbDamCb.expiryCnt = cfg->maxExpires;
      RETVALUE(ROK);
   }

   /* populate the stack manager structure and trigger the stack
    * initialization */
   smCfgCb.cellId              = cfg->cellId;
   smCfgCb.trackAreaCode       = cfg->tac;
   smCfgCb.enbIpAddr           = cfg->enbIpAddr;
   cmMemset(smCfgCb.enbName,0,NB_ENB_NAME);
   if(strlen((S8*)cfg->enbName) < NB_ENB_NAME)
   {
      cmMemcpy(smCfgCb.enbName,cfg->enbName,strlen((S8*)cfg->enbName));
      smCfgCb.enbNameLen            = strlen((S8*)cfg->enbName);
   }
   smCfgCb.sctpIpAddr          = cfg->sctpIpAddr;
   smCfgCb.inactvTmrVal        = cfg->inactvTmrVal;
   smCfgCb.maxExpires          = cfg->maxExpires;
   smCfgCb.s1SetupTmrVal       = cfg->s1SetupTmr;
   /* get the plmn-id */
   plmnLen = strlen((S8*)cfg->plmnId);
   plmnVal = atoi((S8*)cfg->plmnId);

   NB_GET_PLMN(tmpPlmn,plmnLen,plmnVal)

   pLMNidentity.val = (U8*)&tmpPlmn;
   nbUtlGetPlmnId(&smCfgCb.plmnId, &pLMNidentity);

   /* Copy info from cfg to smCfgCb */
#if 0
   /* Copy Home PLMN */
   /* TODO : to be converted from encoded format to size, mcc, mnc format */
   memcpy(smCfgCb.plmnId, cfg->plmnId, NBT_MAX_PLMN_ID);
#endif

   /* Copy Supported TAs */
   if (cfg->suppTAs.pres)
   {
      smCfgCb.suppTAs.pres = cfg->suppTAs.pres;
      smCfgCb.suppTAs.numTAs = cfg->suppTAs.numTAs;
      for (i = 0; i < smCfgCb.suppTAs.numTAs; i++)
      {
         smCfgCb.suppTAs.suppTA[i].tac = cfg->suppTAs.suppTA[i].tac;
         smCfgCb.suppTAs.suppTA[i].bPlmnList.numBPlmns =
                                       cfg->suppTAs.suppTA[i].bPlmnList.numBPlmns;
         for (j = 0; j < smCfgCb.suppTAs.suppTA[i].bPlmnList.numBPlmns; j++)
         {
            memcpy(&(smCfgCb.suppTAs.suppTA[i].bPlmnList.plmnIds[j]),
                   &(cfg->suppTAs.suppTA[i].bPlmnList.plmnIds[j]),
                   sizeof(NbtPlmnId));
         }
      }
   }

   /* eNodeB type: Macro eNodeB or Home eNodeB */
   if (cfg->eNodeBType.pres)
   {
      smCfgCb.eNodeBType.pres = cfg->eNodeBType.pres;
      smCfgCb.eNodeBType.val = cfg->eNodeBType.val;
   }

   /* Copy number of CSG IDs */
   if (cfg->csgIdList.pres)
   {
      smCfgCb.csgIdList.pres = cfg->csgIdList.pres;
      smCfgCb.csgIdList.numCsgIds = cfg->csgIdList.numCsgIds;
      for (i = 0; i < smCfgCb.csgIdList.numCsgIds; i++)
      {
         /* Copy CSG IDs (only lower 27 bits valid) */
         smCfgCb.csgIdList.csgId[i] = cfg->csgIdList.csgId[i];
      }
   }

   smCfgCb.lnbSctpParamCfg.heartBeatInterval   = cfg->heartBeatInterval;
   smCfgCb.lnbSctpParamCfg.rtoInitial          = cfg->rtoInitial/NB_100;
   smCfgCb.lnbSctpParamCfg.rtoMin              = cfg->rtoMin/NB_100;
   smCfgCb.lnbSctpParamCfg.rtoMax              = cfg->rtoMax/NB_100;
   smCfgCb.s1PrepTimerVal                      = cfg->s1PrepTimerVal;
   smCfgCb.s1OvrAllTimerVal                    = cfg->s1OvrAllTimerVal;
   smCfgCb.sctpUdpServiceType  = cfg->sctpUdpServiceType;
   /* initialize the default parameters and polulate the strcture,
    * nbcb, nbcfgcb */
   smEvent                       = EVNTNBINITCFG;
   smCfgCb.smState               = NB_SM_STATE_INIT;
   smCfgCb.noOfCfg               = NB_ONE; /* no of mme */
   NB_ALLOC(&smCfgCb.mmeCfg[0], sizeof(LnbSmMmeCfg));
   smCfgCb.mmeCfg[0]->mmeId      = cfg->mmeId;
   smCfgCb.mmeCfg[0]->noOfIps    = NB_ONE; /* no. of ip per mme */
   smCfgCb.mmeCfg[0]->mmeAddr[0] = cfg->mmeAddr;
   smCfgCb.noOfSctpInStreams     = cfg->noOfSctpInStreams;
   smCfgCb.noOfSctpOutStreams    = cfg->noOfSctpOutStreams;
#ifdef MULTI_ENB_SUPPORT
   smCfgCb.numOfEnbs             = cfg->numOfEnbs;
#endif


   if(nbAppRouteInit(smCfgCb.enbIpAddr, cfg->ueEthIntf) != ROK)
   {
      NB_LOG_ERROR(&nbCb,"Failed to initialize Pcap");
      nbUiSendConfigFailIndToUser(NB_PCAP_CFG_FAILED);
      smCfgCb.smState   = NB_SM_STATE_INIT;
      RETVALUE(RFAILED);
   }

   /* trigger the state machine for configuration */
   smNbProcSm(smEvent);
   RETVALUE(ROK);
}

/*
 * @details This function is used Process the Received UE context
 *          Release Request from TFW.
 *
 * Function: NbEnbUeRelReqHdl
 *
 * @param[in] NbUeCntxtRelReq *relReq
 * @return  S16
 *  -# Success : ROK
 *  -# Failure : RFAILED
 */
PUBLIC S16 NbEnbUeRelReqHdl
(
 NbUeCntxtRelReq *relReq
)
{
   NbUeMsgCause cause;
   NB_LOG_ENTERFN(&nbCb);

   if(NULLP == relReq)
   {
      NB_LOG_ERROR(&nbCb,"Recieved empty(NULL) request");
      RETVALUE(RFAILED);
   }
   cause.causeTyp = relReq->cause.causeType;
   cause.causeVal = relReq->cause.causeVal;

   RETVALUE(nbSndCtxtRelReq(relReq->ueId,&cause));
} /* NbEnbUeRelReqHdl */

PRIVATE S16 getS1apInfoFrmUeId(NbUeS1apIdPair *ueS1apIdPairList, U32 numOfUes,
                               NbResetMsgInfo *resetMsg) {
  U32 cnt = 0;
  U32 ueId = 0;
  NbUeCb *ueCb = NULLP;

  NB_LOG_ENTERFN(&nbCb);

  if (ueS1apIdPairList == NULLP) {
    NB_LOG_ERROR(&nbCb, "UE Id List is empty");
    NB_LOG_EXITFN(&nbCb, RFAILED);
  }

  resetMsg->s1apIdCnt = numOfUes;
  NB_ALLOC(&resetMsg->enbUeS1apIdLst, sizeof(U32) * numOfUes);
  NB_ALLOC(&resetMsg->mmeUeS1apIdLst, sizeof(U32) * numOfUes);

  for (cnt = 0; cnt < numOfUes; cnt++) {
    ueId = ueS1apIdPairList[cnt].ueId;
    if (ROK != (cmHashListFind(&(nbCb.ueCbLst), (U8 *)&(ueId), sizeof(U32), 0,
                               (PTR *)&ueCb))) {
      NB_LOG_ERROR(&nbCb, "UeCb not found for UeId %u",
                   ueS1apIdPairList[cnt].ueId);
    } else {
      if (ueS1apIdPairList[cnt].enbUeS1apId) {
        resetMsg->enbUeS1apIdLst[cnt] = ueS1apIdPairList[cnt].enbUeS1apId;
      } else {
        resetMsg->enbUeS1apIdLst[cnt] = ueCb->s1ConCb->enb_ue_s1ap_id;
      }
      if (ueS1apIdPairList[cnt].mmeUeS1apId) {
        resetMsg->mmeUeS1apIdLst[cnt] = ueS1apIdPairList[cnt].mmeUeS1apId;
      } else {
        resetMsg->mmeUeS1apIdLst[cnt] = ueCb->s1ConCb->mme_ue_s1ap_id;
      }
    }
  }

  RETVALUE(ROK);
} /* getS1apInfoFrmUeId */

PUBLIC S16 NbEnbResetReqHdl
(
 NbResetRequest *resetReq
)
{
   U32 idx = 0;
   S16 ret = ROK;
   NbUeCb *ueCb = NULLP, *prev = NULLP;
   NbResetMsgInfo resetMsgInfo = {0};
   NB_LOG_ENTERFN(&nbCb);

   if(NULLP == resetReq)
   {
      NB_LOG_ERROR(&nbCb, "Recieved empty(NULL) request");
      RETVALUE(RFAILED);
   }

   resetMsgInfo.type = resetReq->rstType;
   resetMsgInfo.cause.causeTyp = resetReq->cause.causeType;
   resetMsgInfo.cause.causeVal = resetReq->cause.causeVal;
   uesLocalRel = TRUE;
   if(resetMsgInfo.type == NB_PARTIAL_RESET)
   {
     if (getS1apInfoFrmUeId(resetReq->u.partialRst.ueS1apIdPairList,
                            resetReq->u.partialRst.numOfConn,
                            &resetMsgInfo) != ROK) {
       NB_LOG_ERROR(&nbCb, "Failed to fetch UE Info using UeId");
       NB_FREE(resetReq->u.partialRst.ueS1apIdPairList,
               resetReq->u.partialRst.numOfConn);
       RETVALUE(RFAILED);
     }
      for(idx = 0 ; idx < resetReq->u.partialRst.numOfConn ; idx ++)
      {
        if (ret != nbSendS1RelIndToUeApp(
                       resetReq->u.partialRst.ueS1apIdPairList[idx].ueId)) {
          NB_LOG_ERROR(&nbCb, "Failed to send Release Indication to UeApp");
          RETVALUE(RFAILED);
        }
        if (ret != nbIfmDamUeDelReq(
                       resetReq->u.partialRst.ueS1apIdPairList[idx].ueId)) {
          NB_LOG_ERROR(&nbCb, "Failed to send UE Delete Indication to DAM");
          RETVALUE(RFAILED);
        }
      }
      NB_FREE(resetReq->u.partialRst.ueS1apIdPairList,
              resetReq->u.partialRst.numOfConn);
   }
   else
   {
      while (cmHashListGetNext(&(nbCb.ueCbLst), (PTR)prev, (PTR *)&ueCb) == ROK)
      {
         NB_LOG_DEBUG(&nbCb, "Found ueCb->ueId=%d in HashList", ueCb->ueId);
         /* Inform the UeApp about UE context release */
         NB_LOG_DEBUG(&nbCb, "Inform UE to release context");
         ret = nbSendS1RelIndToUeApp(ueCb->ueId);
         if (ret != ROK)
         {
            NB_LOG_ERROR(&nbCb, "Failed to send Release Indication to UeApp");
         }

         /* Trigger ueCb deletion in DAM */
         NB_LOG_DEBUG(&nbCb, "Passing UE Delete Indication to DAM");
         ret = nbIfmDamUeDelReq(ueCb->ueId);
         if (ret != ROK)
         {
            NB_LOG_ERROR(&nbCb, "Failed to send UE Delete Indication to DAM");
         }

         prev = NULLP;
         /* Delete hash list entry for ueCb */
         cmHashListDelete(&(nbCb.ueCbLst), (PTR)ueCb);
      }
#ifdef MULTI_ENB_SUPPORT
   resetMsgInfo.enbId = resetReq->u.completeRst.enbId;
#endif
   }
   if(nbBuildAndSendResetRequest(&resetMsgInfo) != ROK)
   {
      NB_LOG_ERROR(&nbCb,"Failed to send Reset request");
      NB_FREE(resetMsgInfo.enbUeS1apIdLst, sizeof(U32) * resetMsgInfo.s1apIdCnt);
      NB_FREE(resetMsgInfo.mmeUeS1apIdLst, sizeof(U32) * resetMsgInfo.s1apIdCnt);
      RETVALUE(RFAILED);
   }
   NB_FREE(resetMsgInfo.enbUeS1apIdLst, sizeof(U32) * resetMsgInfo.s1apIdCnt);
   NB_FREE(resetMsgInfo.mmeUeS1apIdLst, sizeof(U32) * resetMsgInfo.s1apIdCnt);
   RETVALUE(ROK);
} /* NbEnbResetReqHdl */

PUBLIC S16 NbEnbErabRelIndHdl
(
 NbuErabRelIndList *erabRelInd
)
{
   U32 enbUeS1apId = 0;
   U32 mmeUeS1apId = 0;
   NbUeCb *ueCb = NULLP;

   NB_LOG_ENTERFN(&nbCb);

   if(NULLP == erabRelInd)
   {
      NB_LOG_ERROR(&nbCb, "Recieved empty(NULL) request");
      RETVALUE(RFAILED);
   }

   /* Find the ENB and MME UE-S1AP Ids using UeId */
   if ( ROK != (cmHashListFind(&(nbCb.ueCbLst), (U8 *)&(erabRelInd->ueId),
      sizeof(U32),0,(PTR *)&ueCb)))
   {
      RETVALUE(RFAILED);
   }

   /* Release all bearers which are their in the erabIdLst */
   nbIfmDamErabDelReq((Void *)erabRelInd);

   enbUeS1apId = ueCb->s1ConCb->enb_ue_s1ap_id;
   mmeUeS1apId = ueCb->s1ConCb->mme_ue_s1ap_id;

   if(nbBuildAndSendErabRelInd(enbUeS1apId, mmeUeS1apId,
            erabRelInd->numOfErabIds, erabRelInd->erabIdLst) != ROK)
   {
      NB_LOG_ERROR(&nbCb,"Failed to send E-RAB Release Indication");
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* NbEnbErabRelIndHdl */

PUBLIC S16 NbEnbErabRelRspHdl
(
 NbErabRelRsp *erabRelRsp
)
{
   U32 enbUeS1apId = 0;
   U32 mmeUeS1apId = 0;
   NbUeCb *ueCb = NULLP;
   NbErabRelReq *erabRelReq = NULLP;

   NB_LOG_ENTERFN(&nbCb);

   if(NULLP == erabRelRsp)
   {
      NB_LOG_ERROR(&nbCb, "Recieved empty(NULL) request");
      RETVALUE(RFAILED);
   }

   /* Find the ENB and MME UE-S1AP Ids using UeId */
   if ( ROK != (cmHashListFind(&(nbCb.ueCbLst), (U8 *)&(erabRelRsp->ueId),
      sizeof(U32),0,(PTR *)&ueCb)))
   {
      NB_LOG_ERROR(&nbCb, "UeCb not found for UeId %d", erabRelRsp->ueId);
      NB_LOG_EXITFN(&nbCb, RFAILED);
   }

   if((erabRelRsp->enbUeS1apId != ueCb->s1ConCb->enb_ue_s1ap_id) ||
   (erabRelRsp->mmeUeS1apId != ueCb->s1ConCb->mme_ue_s1ap_id))
   {
      NB_LOG_ERROR(&nbCb, "MME(%d)/ENB(%d) S1AP IDs are not associated with "\
            "ueId %d", erabRelRsp->mmeUeS1apId, erabRelRsp->enbUeS1apId,
            erabRelRsp->ueId);
   }

   /* Release all bearers which are their in the erabIdLst */
   NB_ALLOC(&erabRelReq, sizeof(NbErabRelReq));
   erabRelReq->ueId = ueCb->ueId;
   erabRelReq->numOfErabIds = erabRelRsp->numOfErabIds;

   NB_ALLOC(&erabRelReq->erabIdLst, erabRelReq->numOfErabIds * sizeof(U8));
   cmMemcpy(erabRelReq->erabIdLst, erabRelRsp->erabIdLst,
         erabRelReq->numOfErabIds * sizeof(U8));
   nbIfmDamErabDelReq((Void *)erabRelReq);

   if(nbBuildAndSendErabRelInd(enbUeS1apId, mmeUeS1apId,
            erabRelRsp->numOfErabIds, erabRelRsp->erabIdLst) != ROK)
   {
      NB_LOG_ERROR(&nbCb,"Failed to send E-RAB Release Response");
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* NbEnbErabRelRspHdl */

PUBLIC S16 NbEnbNasNonDel
(
 NbNasNonDel *nasNonDel
)
{
   NB_LOG_ENTERFN(&nbCb);

   if(NULLP == nasNonDel)
   {
      NB_LOG_ERROR(&nbCb, "Recieved empty(NULL) request");
      RETVALUE(RFAILED);
   }

   nbCb.nasNonDel[(nasNonDel->ueId) - 1].flag = nasNonDel->flag;
   nbCb.nasNonDel[(nasNonDel->ueId) - 1].causeType = nasNonDel->causeType;
   nbCb.nasNonDel[(nasNonDel->ueId) - 1].causeVal = nasNonDel->causeVal;

   RETVALUE(ROK);
}
PUBLIC S16 NbEnbInitCtxtSetupFail(NbInitCtxtSetupFail *initCtxtSetupFail)
{
   NB_LOG_ENTERFN(&nbCb);

   if(NULLP == initCtxtSetupFail)
   {
      NB_LOG_ERROR(&nbCb, "Recieved empty(NULL) request");
      RETVALUE(RFAILED);
   }

   nbCb.initCtxtSetupFail[(initCtxtSetupFail->ueId) - 1].initCtxtSetupFailInd = initCtxtSetupFail->initCtxtSetupFailInd;
   nbCb.initCtxtSetupFail[(initCtxtSetupFail->ueId) - 1].causeType = initCtxtSetupFail->causeType;
   nbCb.initCtxtSetupFail[(initCtxtSetupFail->ueId) - 1].causeVal = initCtxtSetupFail->causeVal;

   RETVALUE(ROK);
}

/*
 * @details This function marked a ue for dropping intial context setup
 *
 * Function: NbEnbDropInitCtxtSetup
 *
 *
 * @param[in]  NbDropInitCtxtSetup
 * @return  S16
 *          -# Success : ROK
 */
PUBLIC S16 NbEnbDropInitCtxtSetup(NbDropInitCtxtSetup *dropInitCtxtSetup)
{
   NB_LOG_ENTERFN(&nbCb);

   if(NULLP == dropInitCtxtSetup)
   {
      NB_LOG_ERROR(&nbCb, "Recieved empty(NULL) request");
      RETVALUE(RFAILED);
   }

   nbCb.dropInitCtxtSetup[(dropInitCtxtSetup->ueId) - 1].isDropICSEnable = dropInitCtxtSetup->isDropICSEnable;
   nbCb.dropInitCtxtSetup[(dropInitCtxtSetup->ueId) - 1].tmrVal = dropInitCtxtSetup->tmrVal;

   RETVALUE(ROK);
}

/*
 * @details This function marked a ue for delay intial context setup
 *
 * Function: NbEnbDelayInitCtxtSetup
 *
 *
 * @param[in]  NbDelayInitCtxtSetup
 * @return  S16
 *          -# Success : ROK
 */
PUBLIC S16 NbEnbDelayInitCtxtSetupRsp(NbDelayICSRsp *delayICSRsp)
{
   NB_LOG_ENTERFN(&nbCb);

   if(NULLP == delayICSRsp)
   {
      NB_LOG_ERROR(&nbCb, "Recieved empty(NULL) request");
      RETVALUE(RFAILED);
   }

   nbCb.delayInitCtxtSetupRsp[(delayICSRsp->ueId) - 1].delayICSRsp  = delayICSRsp->isDelayICSRsp;
   nbCb.delayInitCtxtSetupRsp[(delayICSRsp->ueId) - 1].tmrVal  = delayICSRsp->tmrVal;

   RETVALUE(ROK);
}

/*
 * @details This function marks failed erabs to be sent in ICS Rsp
 *
 * Function: NbEnbHandleInitCtxtSetupRspFailedErabs
 *
 * @param[in]  pointer to NbInitCtxtSetupFailedErabs
 * @return  S16
 *          -# Success : ROK
 */
PUBLIC S16 NbEnbHandleInitCtxtSetupRspFailedErabs(
    NbInitCtxtSetupFailedErabs *icsRspFailedErabs) {
  NB_LOG_ENTERFN(&nbCb);
  U8 idx;
  if (NULLP == icsRspFailedErabs) {
    NB_LOG_ERROR(&nbCb, "Recieved empty(NULL) request");
    RETVALUE(RFAILED);
  }

  nbCb.initCtxtSetupFailedErabs[(icsRspFailedErabs->ueId) - 1].numFailedErabs =
      icsRspFailedErabs->numFailedErabs;
  for (idx = 0; idx < icsRspFailedErabs->numFailedErabs; idx++) {
    nbCb.initCtxtSetupFailedErabs[(icsRspFailedErabs->ueId) - 1]
        .failedErabs[idx] = icsRspFailedErabs->failedErabs[idx];
  }
  nbCb.initCtxtSetupFailedErabs[(icsRspFailedErabs->ueId) - 1].cause.causeTyp =
      NB_CAUSE_TRANSPORT;
  nbCb.initCtxtSetupFailedErabs[(icsRspFailedErabs->ueId) - 1].cause.causeVal =
      CAUSE_TRANSPORT_RESOURCE_UNAVAILABLE;
  RETVALUE(ROK);
}


/*
 * @details This function marked a ue for delay ue context release complete
 *
 * Function: NbEnbDelayUeCtxtRelCmp
 *
 *
 * @param[in]  NbDelayUeCtxtRelCmp
 * @return  S16
 *          -# Success : ROK
 */
PUBLIC S16 NbEnbDelayUeCtxtRelCmp(NbDelayUeCtxtRelCmp *delayUeCRC)
{
   NB_LOG_ENTERFN(&nbCb);
   if(NULLP == delayUeCRC)
   {
      NB_LOG_ERROR(&nbCb, "Recieved empty(NULL) request");
      RETVALUE(RFAILED);
   }

   nbCb.delayUeCtxtRelCmp[(delayUeCRC->ueId) - 1].delayUeCtxRelComp  = delayUeCRC->isDelayUeCtxtRelCmp;
   nbCb.delayUeCtxtRelCmp[(delayUeCRC->ueId) - 1].tmrVal  = delayUeCRC->tmrVal;

   RETVALUE(ROK);
}
/*
 * @details This function marked a ue for dropping intial context setup and
 * sending ue context release message
 *
 * Function: NbEnbUeCtxtRelForInitCtxtSetup
 *
 *
 * @param[in]  NbDropInitCtxtSetup
 * @return  S16
 *          -# Success : ROK
 */
PUBLIC S16 NbEnbUeCtxtRelForInitCtxtSetup(NbSendUeCtxtRelForICSRsp *sendUeCtxtRelReq)
{
   NB_LOG_ENTERFN(&nbCb);

   if(NULLP == sendUeCtxtRelReq)
   {
      NB_LOG_ERROR(&nbCb, "Recieved empty(NULL) request");
      RETVALUE(RFAILED);
   }

   nbCb.dropICSSndCtxtRel[(sendUeCtxtRelReq->ueId) - 1].sndICSRspUeCtxtRel = sendUeCtxtRelReq->sndICSRspUeCtxtRel;
   nbCb.dropICSSndCtxtRel[(sendUeCtxtRelReq->ueId) - 1].causeType = sendUeCtxtRelReq->causeType;
   nbCb.dropICSSndCtxtRel[(sendUeCtxtRelReq->ueId) - 1].causeVal = sendUeCtxtRelReq->causeVal;

   RETVALUE(ROK);
}

PUBLIC S16 NbMultiEnbCfgReq(NbMultiEnbConfigReq *multiEnbCfgReq)
{
   EnbCb tmpEnbCb;
   EnbCb *eNbCb = NULLP;
   U8 nbOffset = 0;

   NB_LOG_ENTERFN(&nbCb);

   NB_LOG_DEBUG(&nbCb, "Handling Multi Enb Config Req in NBApp");
   if(NULLP == multiEnbCfgReq)
   {
      NB_LOG_ERROR(&nbCb, "Recieved empty(NULL) request");
      RETVALUE(RFAILED);
   }
   nbCb.multiEnbCfgInfo.pres  = TRUE;
   nbCb.multiEnbCfgInfo.numOfEnbs = multiEnbCfgReq->numOfEnbs;
   for (int index = 0; index < multiEnbCfgReq->numOfEnbs; index++) {
     /* Allocate memory */
     NB_ALLOC(&eNbCb, sizeof(EnbCb));
     eNbCb->enbId = index;
     eNbCb->cell_id = multiEnbCfgReq->nbMultiEnbCfgParam[index].cell_id;
     eNbCb->tac = multiEnbCfgReq->nbMultiEnbCfgParam[index].tac;
     eNbCb->enbType = multiEnbCfgReq->nbMultiEnbCfgParam[index].enbType;
     eNbCb->plmn_length = multiEnbCfgReq->nbMultiEnbCfgParam[index].plmn_length;

     if (eNbCb->plmn_length == 5) {
       eNbCb->plmnId.numMncDigits = 2;
     } else {
       eNbCb->plmnId.numMncDigits = 3;
     }
     eNbCb->plmnId.mcc[0] =
       multiEnbCfgReq->nbMultiEnbCfgParam[index].plmn_id[0];
     eNbCb->plmnId.mcc[1] =
       multiEnbCfgReq->nbMultiEnbCfgParam[index].plmn_id[1];
     eNbCb->plmnId.mcc[2] =
       multiEnbCfgReq->nbMultiEnbCfgParam[index].plmn_id[2];
     eNbCb->plmnId.mnc[0] =
       multiEnbCfgReq->nbMultiEnbCfgParam[index].plmn_id[3];
     eNbCb->plmnId.mnc[1] =
       multiEnbCfgReq->nbMultiEnbCfgParam[index].plmn_id[4];
     eNbCb->plmnId.mnc[2] =
       multiEnbCfgReq->nbMultiEnbCfgParam[index].plmn_id[5];
     NB_LOG_DEBUG(
       &nbCb, "Inserting EnbCb into the ENB list for enbId = %d", eNbCb->enbId);
     if (
       ROK !=
       cmHashListInsert(
         &(nbCb.eNBCbLst), (PTR) eNbCb, (U32*) &eNbCb->enbId, sizeof(U32))) {
       NB_FREE(eNbCb, sizeof(EnbCb))
       NB_LOG_ERROR(
         &nbCb, "Failed to Insert ENB into eNBCbLst[%d]", eNbCb->enbId);
       RETVALUE(RFAILED);
     }
   }
   RETVALUE(ROK);
}
#ifdef MULTI_ENB_SUPPORT
/*
 * @details This function is used Process the Received X2 HO
 *          Trigger Request from TFW.
 *
 * Function: NbEnbX2HOTriggerReqHdl
 *
 * @param[in] NbUeCntxtRelReq *relReq
 * @return  S16
 *  -# Success : ROK
 *  -# Failure : RFAILED
 */
PUBLIC S16 NbEnbX2HOTriggerReqHdl
(
 NbX2HOTriggerReq *x2HOTriggerReq
)
{
   NbUeCb       *ueCb   = NULLP;  /* enbApp uecb */
   EnbCb        *nbCbNew   = NULLP;  /* enbApp uecb */
   NbUeCb       *prevnbCb   = NULLP;  /* enbApp uecb */
   NbUeTunInfo  *prevTunnCb = NULLP;
   NbUeTunInfo  *tunnCb = NULLP;
   NbUeTunInfo  *tunInfo = NULLP;
   U32 erabId = 0;
   U32 remTeId = 0;
   U32 numOfErabIds = 1;
   CmTptAddr    sgwAddr;
   NB_LOG_ENTERFN(&nbCb);
   NbTunDelReq *tunDelReq = NULLP;
   S16 ret = RFAILED;
   U32 suConId;
   NbS1ConCb *s1apConCb = NULLP;
   SztConReq datEvt;
   U32 mme_ue_s1ap_id = 0;

   NB_LOG_DEBUG(&nbCb,"Received X2 HO Trigger request at NB App for UE %d",x2HOTriggerReq->ueId);
   if(NULLP == x2HOTriggerReq)
   {
      NB_LOG_ERROR(&nbCb,"Recieved empty(NULL) request");
      RETVALUE(RFAILED);
   }
   if ( ROK != (cmHashListFind(&(nbCb.ueCbLst), (U8 *)&(x2HOTriggerReq->ueId),
      sizeof(U32),0,(PTR *)&ueCb)))
   {
      NB_LOG_ERROR(&nbCb, "UeCb not found for UeId %d", x2HOTriggerReq->ueId);
      NB_LOG_EXITFN(&nbCb, RFAILED);
   }

   // Store Target eNB ID in ueCb
   while(cmHashListGetNext(&(nbCb.eNBCbLst),(PTR)nbCbNew,(PTR*)&nbCbNew) == ROK)
   {
     if (!nbCbNew)
     {
       NB_LOG_ERROR(&nbCb,"eNBCbLst is NULL\n");
       RETVALUE(RFAILED);
     }
     if (nbCbNew->enbId != ueCb->enbId)
     {
       //Store the Target eNB in UeCb and set the flag
       ueCb->enbId = nbCbNew->enbId;
       nbCb.x2HoDone = TRUE;
       NB_LOG_DEBUG(&nbCb,"Updated Target enbId into UeCB %d ",ueCb->enbId);
       break;
     }
   }

   /*Find and Delete the old Tunnel.Create a new lclteId and GTP Tunnel*/

   NB_ALLOC(&(tunInfo),(sizeof(NbUeTunInfo)));
   for(;((cmHashListGetNext(&(ueCb->tunnInfo),(PTR)prevTunnCb,(PTR*)&tunnCb)) == ROK);)
   {
     erabId = tunnCb->bearerId;
     cmMemcpy(tunInfo,tunnCb,sizeof(NbUeTunInfo));
     ret  = cmHashListDelete(&(ueCb->tunnInfo), (PTR)tunnCb);
     if (ret == RFAILED)
     {
       NB_LOG_ERROR(&nbCb,"Failed to delete TunnelCb");

     }
     NB_FREE(tunnCb, sizeof(NbUeTunInfo))
     tunnCb = NULLP;
     ueCb->tunnIdx--;
   }
   NB_LOG_DEBUG(&nbCb,"Deleted tun info for bearer %d\n",erabId);
   //Delete the existing tunnel
   NB_ALLOC(&tunDelReq, sizeof(NbTunDelReq));
   tunDelReq->bearerId = erabId;
   tunDelReq->ueId = x2HOTriggerReq->ueId;
   nbIfmDamTunDelReq(tunDelReq);
   NB_LOG_DEBUG(&nbCb,"Sent Tunnel Req to DAM\n");
   // Create a new Tunnel entry
   tunInfo->lclTeId = nbGetUeLclTeid(ueCb->ueId,
     erabId,ueCb->enbId);

   if (ROK != cmHashListInsert(&(ueCb->tunnInfo),(PTR)tunInfo,
     (U8 *) &tunInfo->bearerId,sizeof(U32)))
   {
     NB_FREE(tunInfo, sizeof(NbUeTunInfo))
     NB_LOG_ERROR(&nbCb, "Failed to Insert tunnel info ");
     RETVALUE(RFAILED);
   }
   NB_LOG_DEBUG(&nbCb,"Inserted new tun info\n");

   mme_ue_s1ap_id = ueCb->s1ConCb->mme_ue_s1ap_id;
   suConId = (((nbCbNew->cell_id & 0xFFFF) << 16) |
	     (ueCb->ueId & 0xFFFF));
   NB_FREE(ueCb->s1ConCb, sizeof(NbS1ConCb))
   NB_ALLOC(&s1apConCb, sizeof(NbS1ConCb));
   if(s1apConCb == NULLP)
   {
      NB_FREE(ueCb, sizeof(NbUeCb))
      NB_LOG_ERROR(&nbCb, "Failed to allocate memory for S1ap Control block");
      RETVALUE(RFAILED);
   }
   s1apConCb->suConnId       = suConId;
   s1apConCb->s1apConnState  = NB_S1AP_CONNECTED;
   s1apConCb->enb_ue_s1ap_id = suConId;
   s1apConCb->mme_ue_s1ap_id = mme_ue_s1ap_id;
   ueCb->s1ConCb             = s1apConCb;

   nbHandleUeIpInfoReq(ueCb->ueId,erabId);
   if(nbS1apFillPathSwReq(ueCb,&datEvt.pdu,erabId,tunInfo->lclTeId,numOfErabIds,mme_ue_s1ap_id) != ROK)
   {
     NB_LOG_ERROR(&nbCb, "Failed to build s1ap Context Rel Request");
     RETVALUE(RFAILED);
   }
   NB_LOG_DEBUG(&nbCb,"Built PATH SW REQUEST\n");
   datEvt.peerId.pres = PRSNT_NODEF;
   datEvt.peerId.val  = nbCb.mmeInfo.mmeId;
   datEvt.u.suConnId  = suConId;
   datEvt.enbId = ueCb->enbId;

   /*Send S1AP Path Switch Request to MME*/
   if (NbIfmS1apConReq(&datEvt) != ROK)
   {
      cmHashListDeinit(&(ueCb->tunnInfo));
      cmHashListDelete(&(nbCb.ueCbLst), (PTR)ueCb);
      NB_FREE(ueCb, sizeof(NbUeCb))
      NB_FREE(s1apConCb, sizeof(NbS1ConCb));
      NB_LOG_ERROR(&nbCb, "Failure in sending the SZT CON REQ");
      RETVALUE(RFAILED);
   }
   NB_LOG_DEBUG(&nbCb,"Sent PATH SW REQUEST\n");
   RETVALUE(ROK);
} /* NbEnbX2HOTriggerReqHdl */
#endif

#ifdef MULTI_ENB_SUPPORT
/*
 * @details This function is used Process the Received
 *          enb COnfig Transfer from TFW.
 *
 * Function: NbEnbConfigTransferHdl
 *
 * @param[in] NbEnbConfigTrnsf *enbConfigTrnsf
 * @return  S16
 *  -# Success : ROK
 *  -# Failure : RFAILED
 */
PUBLIC S16 NbEnbConfigTransferHdl
(
 NbEnbConfigTrnsf *enbConfigTrnsf
)
{
   SztUDatEvnt  uDatEvnt;
   NbMmeCb      *mmeCb = NULLP;
   mmeCb =      &nbCb.mmeInfo;
   NbUeCb       *ueCb   = NULLP;

   if ( ROK != (cmHashListFind(&(nbCb.ueCbLst), (U8 *)&(enbConfigTrnsf->ueId),
      sizeof(U32),0,(PTR *)&ueCb)))
   {
      NB_LOG_ERROR(&nbCb, "UeCb not found for UeId %d", enbConfigTrnsf->ueId);
      NB_LOG_EXITFN(&nbCb, RFAILED);
   }

   uDatEvnt.enbId = ueCb->enbId;
   EnbCb *enbCb = NULLP;
   if ( ROK != (cmHashListFind(&(nbCb.eNBCbLst), (U32 *)&(ueCb->enbId),
      sizeof(U32),0,(PTR *)&enbCb)))
   {
      NB_LOG_ERROR(&nbCb, "enbCb not found for enbId %d", uDatEvnt.enbId);
      RETVALUE(RFAILED);
   }
   if (enbCb == NULLP){
      NB_LOG_ERROR(&nbCb, "enbCb is NULL!!");
   }
   if (nbBldENbConfigTransfer(&(uDatEvnt.pdu), enbCb, ueCb) != ROK)
   {
      RETVALUE(RFAILED);
   }

   uDatEvnt.transId.pres = PRSNT_NODEF;
   uDatEvnt.transId.val = 1;
   uDatEvnt.peerId.pres = PRSNT_NODEF;
   uDatEvnt.peerId.val = mmeCb->mmeId;

   /* Send the pdu to the MME */
   if((NbIfmS1apSndMgmtMsg(&uDatEvnt)) != ROK)
   {
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);

} /* NbEnbConfigTransferHdl */
#endif


#ifdef MULTI_ENB_SUPPORT
/*
 * @details This function is used send the
 *         enb Config Transfer in response to
 *         MME Config Transfer.
 *
 * Function: sendEnbCfgTransferRsp
 *
 * @param[in] NbEnbConfigTrnsf *enbConfigTrnsf
 * @return  S16
 *  -# Success : ROK
 *  -# Failure : RFAILED
 */
PUBLIC S16 sendEnbCfgTransferRsp()
{
   SztUDatEvnt  uDatEvnt;
   NbMmeCb      *mmeCb = NULLP;
   mmeCb =      &nbCb.mmeInfo;
   EnbCb *srcenbCb = NULLP;
   EnbCb *tgtenbCb = NULLP;
   U32 enbId = 0;
   U32 inst = 0;

   if(mmeCb == NULLP)
   {
      RETVALUE(RFAILED);
   }

   enbId = (nbCb.enbId + inst);

   if ( ROK != (cmHashListFind(&(nbCb.eNBCbLst), (U32 *)&(enbId),
               sizeof(U32),0,(PTR *)&srcenbCb)))
   {
      NB_LOG_ERROR(&nbCb, "enbCb not found for enbId %d", uDatEvnt.enbId);
      RETVALUE(RFAILED);
   }
   if (srcenbCb == NULLP){
      NB_LOG_ERROR(&nbCb, "enbCb is NULL!!");
   }
   inst++;
   enbId = (nbCb.enbId + inst);
   uDatEvnt.enbId = (nbCb.enbId + inst);

   if ( ROK != (cmHashListFind(&(nbCb.eNBCbLst), (U32 *)&(enbId),
               sizeof(U32),0,(PTR *)&tgtenbCb)))
   {
      NB_LOG_ERROR(&nbCb, "enbCb not found for enbId %d", uDatEvnt.enbId);
      RETVALUE(RFAILED);
   }
   if (tgtenbCb == NULLP){
      NB_LOG_ERROR(&nbCb, "enbCb is NULL!!");
   }
   if (nbBldENbConfigTransferRsp(&(uDatEvnt.pdu), tgtenbCb, srcenbCb) != ROK)
   {
      RETVALUE(RFAILED);
   }

   uDatEvnt.transId.pres = PRSNT_NODEF;
   uDatEvnt.transId.val = 1;
   uDatEvnt.peerId.pres = PRSNT_NODEF;
   uDatEvnt.peerId.val = mmeCb->mmeId;

   /* Send the pdu to the MME */
   if((NbIfmS1apSndMgmtMsg(&uDatEvnt)) != ROK)
   {
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);

} /* sendEnbCfgTransferRsp */
#endif

#ifdef MULTI_ENB_SUPPORT
PUBLIC S16 nbPrcMMEConfigTrf
(
 U32 peerId,
 S1apPdu *pdu
)
{
   U32 idx;
   NbMmeCb *mmeCb;
   SztInitiatingMsg  *initMsg    = &pdu->pdu.val.initiatingMsg;
   SztMMEConfigTfr *mmeConfigTrf = &initMsg->value.u.sztMMEConfigTfr;
   SztSONConfigTfr *sonCfgTfr    = NULLP;
   SztSrceNB_ID    *srcEnbId     = NULLP;
   SztTgeteNB_ID   *tgetEnbId    = NULLP;
   SztProtIE_Field_MMEConfigTfrIEs *ie = NULLP;
   U32  sonInfoType;
   NbMmeConfigTrnsf mmeConfigTrnsf = {0};

   NB_LOG_ENTERFN(&nbCb);

   mmeCb = &nbCb.mmeInfo;
   if (mmeCb == NULLP)
   {
      RETVALUE(RFAILED);
   }

   sonCfgTfr = &mmeConfigTrf->protocolIEs.member[0].value.u.sztSONConfigTfr;
   srcEnbId = &sonCfgTfr->sourceeNB_ID;
   tgetEnbId = &sonCfgTfr->targeteNB_ID;

   for (idx = 0; idx < mmeConfigTrf->protocolIEs.noComp.val; idx++)
   {
      ie = mmeConfigTrf->protocolIEs.member + idx;
      switch(ie->id.val)
      {
         case Sztid_SONConfigTfrMCT:
         {
            if(TRUE != sonCfgTfr->sONInform.choice.pres)
            {
               break;
            }
            sonInfoType = sonCfgTfr->sONInform.choice.val;
            switch(sonInfoType)
            {
               case SONINFORM_SONINFORMRQST:
               {
                 NB_LOG_DEBUG(&nbCb,"Send eNodeB config transfer with reply");
                 sendEnbCfgTransferRsp();
                 mmeConfigTrnsf.u.req = 1;
                 break;
               }
               case SONINFORM_SONINFORMREPLY:
               {
                 NB_LOG_DEBUG(&nbCb,"Received SONINFORM_SONINFORMREPLY\n");
                 mmeConfigTrnsf.u.reply = 1;
                 break;
               }
            }
          }
          break;

          default:
            NB_LOG_ERROR(&nbCb, "Wrong IE(%d) in MME CONFIG TRANSFER", ie->id.val);
            break;
      }
    }
   nbUiSendMmeConfigTrfToUser(&mmeConfigTrnsf);
   RETVALUE(ROK);
} /* nbPrcS1SetupRsp */
#endif

/*
 * @details This function sets a flag in nbCb to delay erab setup rsp
 *
 * Function: NbEnbDelayErabSetupRsp
 *
 * @param[in]  NbDelayErabSetupRsp
 * @return  S16
 *          -# Success : ROK
 *          -# Failure : RFAILED
 */
PUBLIC S16 NbEnbDelayErabSetupRsp(NbDelayErabSetupRsp *delayErabRsp) {
  NB_LOG_ENTERFN(&nbCb);

  if (NULLP == delayErabRsp) {
    NB_LOG_ERROR(&nbCb, "Received empty(NULL) NbDelayErabSetupRsp request");
    RETVALUE(RFAILED);
  }

  nbCb.delayErabSetupRsp[(delayErabRsp->ueId) - 1].isDelayErabSetupRsp =
      delayErabRsp->isDelayErabSetupRsp;
  nbCb.delayErabSetupRsp[(delayErabRsp->ueId) - 1].tmrVal =
      delayErabRsp->tmrVal;

  RETVALUE(ROK);
}

