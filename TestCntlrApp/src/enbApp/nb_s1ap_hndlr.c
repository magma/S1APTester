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

    Desc:  C source code for UE Application

    File:  nb_ifm_egtp.c

    Sid:

    Prg:

**********************************************************************/
#include "nb.h"
#include "rl_interface.h"
#include "rl_common.h"
#include "nb_smm_init.h"
#include "nb_utils.h"
#include "nb_log.h"
#include "nbt.h"
#include "nbt.x"

EXTERN U8 uesLocalRel;
EXTERN S16 nbUiSendIntCtxtSetupDrpdIndToUser(U32 ueId);
PUBLIC S16 nbCtxtRelSndRlsCmpl(NbUeCb*);
PUBLIC S16 nbProcessDlNasMsg(NbUeCb*, S1apPdu*, U8);
PUBLIC S16 nbGetTai(NbTai*);
#ifdef MULTI_ENB_SUPPORT
PUBLIC U32  nbGetUeLclTeid(U32, U32, U32);
#else
PUBLIC U32  nbGetUeLclTeid(U32, U32);
#endif
PUBLIC S16 nbGetErabInfoFrmIntCnxt(NbUeCb*, SztE_RABToBeSetupLstCtxtSUReq*,
      NbErabLst**);
#ifdef MULTI_ENB_SUPPORT
PRIVATE S16 nbBldS1SetupReq(S1apPdu**,EnbCb *);
#else
PRIVATE S16 nbBldS1SetupReq(S1apPdu**);
#endif
PRIVATE S16 nbBldResetReq(S1apPdu**, NbResetMsgInfo*);
PRIVATE S16 nbBldErabRelInd(S1apPdu**, U32, U32, U8, U8*);
PRIVATE S16 nbBldErabRelRsp(S1apPdu**, U32, U32, U8, U8*, U8, U8*);
#ifdef MULTI_ENB_SUPPORT
PRIVATE S16 nbS1apFillTAI(NbUeCb*, S1apPdu*, SztTAI*, EnbCb *);
#else
PRIVATE S16 nbS1apFillTAI(NbUeCb*, S1apPdu*, SztTAI*);
#endif
PUBLIC S16 nbBuildAndSendIntCtxtSetupRsp(NbUeCb*, NbErabLst*);
PRIVATE S16 nbBuildIntCtxtSetupRsp(NbUeCb*, NbErabLst*, S1apPdu**);
PUBLIC S16 nbHandleS1UeReleaseCmd(NbUeCb *ueCb, NbRelCause relCause);
PRIVATE S16 nbPrcSuccPdu(U32, S1apPdu*);
PRIVATE S16 nbPrcUnsuccPdu(U32, S1apPdu*);
PRIVATE S16 nbRabSetupSndS1apRsp(NbUeCb *ueCb, NbErabLst *erabInfo,
                                 NbFailedErabLst *failedErabInfo);
PUBLIC S16 nbS1apFillCtxtRelCmpl(NbS1ConCb *, S1apPdu **);
S16 nbIfmDamUeDelReq(U8);
PUBLIC S16 nbS1apFillCause(SztCause *ie, NbUeMsgCause *cause);
PUBLIC S16 nbGetErabInfoFrmErabSetup(NbUeCb *, SztE_RABToBeSetupLstBrSUReq *,
                                     NbErabLst **, NbFailedErabLst **);
PRIVATE S16 nbFillErrIndMsg(NbErrIndMsg *s1ErrInd, S1apPdu **errIndPdu);
PUBLIC S16  NbBuildAndSndErrIndMsg(NbErrIndMsg *s1ErrInd);
PUBLIC S16 sendNonDelFlag(NbUeCb *ueCb, SztNAS_PDU *pdu, NbUeMsgCause *cause);
PUBLIC S16 sendInitCtxtSetupFailRsp(NbUeCb *ueCb, NbUeMsgCause *cause);
PRIVATE S16 nbSendUeCtxtRelReqAsICSRsp(NbUeCb *ueCb);
PRIVATE S16 nbStartDelayTimerForICSRsp(U32 ueId,NbErabLst *erabInfo);
PRIVATE S16 nbStartDelayTimerForErabRsp(U32 ueId, NbErabLst *erabInfo,
                                        NbFailedErabLst *failedErabInfo,
                                        U32 tmrVal);
PRIVATE S16 nbStartDelayTimerForUeCtxRel(U32 ueId);
PUBLIC S16 nbHandleDelayTimerForUeCtxRelComplExpiry(NbDelayUeCtxtRelCmpCb *ueCtxtRelCmpCb);
PUBLIC S16 nbPrcPathSwReqAck(NbUeCb *ueCb,S1apPdu *pdu);
EXTERN S16 nbUiSendPathSwReqAckToUser(NbPathSwReqAck *nbpathSwReqAck);

/*
 *    @brief This function is used to build and send the S1 Setup Request
 *    to the MME.
 *
 *    @details This function is used to build and send the S1 Setup Request
 *    to the MME.
 *
 * Function:nbBuildAndSendS1SetupReq
 *
 *       Processing steps:
 *        - Build and send S1 Setup Request to the MME.
 *        - Move the MME control block state to WR_MME_IN_PROG.
 *        - Start the Setup response timer to retransmit the setup request
 *          incase of reponse is not received with in the time.
 *        - This function is invoked EMM module when EMM Module ges trigger
 *          from Management intrerface ie., during cell config/setup.
 *
 * @param[in] mmeId: MME Id.
 *
 *  @return  S16
 * -# Success : ROKi
 * -# Failure : RFAILED
 */
PUBLIC S16 nbBuildAndSendS1SetupReq
(
 NbMmeId mmeId
)
{
   SztUDatEvnt               uDatEvnt;
   NbMmeCb                   *mmeCb = NULLP;
   mmeCb = &nbCb.mmeInfo;
#ifdef MULTI_ENB_SUPPORT
   PRIVATE U32 inst = 0;
#endif
   if(mmeCb == NULLP)
   {
      RETVALUE(RFAILED);
   }
#ifdef MULTI_ENB_SUPPORT
   uDatEvnt.enbId = (nbCb.enbId + inst);  /* TODO: Update required */
   U32 enbId = (nbCb.enbId + inst);
   inst++;
   if(inst >= smCfgCb.numOfEnbs)
       inst = 0;
   EnbCb *enbCb = NULLP;
   if ( ROK != (cmHashListFind(&(nbCb.eNBCbLst), (U32 *)&(enbId),
      sizeof(U32),0,(PTR *)&enbCb)))
   {
      if (nbCb.multiEnbCfgInfo.pres == FALSE)
      {
        /* Allocate memory */
        NB_ALLOC(&enbCb, sizeof(EnbCb));
        enbCb->enbId = 0;
        enbCb->cell_id = nbCb.cellId;
        enbCb->tac = nbCb.tac;
        enbCb->enbType = nbCb.enbType;
        enbCb->plmnId.numMncDigits = nbCb.plmnId.numMncDigits;
        enbCb->plmnId.mcc[0] = nbCb.plmnId.mcc[0];
        enbCb->plmnId.mcc[1] = nbCb.plmnId.mcc[1];
        enbCb->plmnId.mcc[2] = nbCb.plmnId.mcc[2];
        enbCb->plmnId.mnc[0] = nbCb.plmnId.mnc[0];
        enbCb->plmnId.mnc[1] = nbCb.plmnId.mnc[1];
        enbCb->plmnId.mnc[2] = nbCb.plmnId.mnc[2];
        NB_LOG_DEBUG(&nbCb, "Inserting EnbCb into the ENB list for enbId = %d", enbCb->enbId);
        if (ROK != cmHashListInsert(&(nbCb.eNBCbLst),(PTR)enbCb,
             		   (U32 *) &enbCb->enbId,sizeof(U32)))
        {
           NB_FREE(enbCb, sizeof(EnbCb))
           NB_LOG_ERROR(&nbCb, "Failed to Insert ENB into eNBCbLst[%d]",enbCb->enbId);
           RETVALUE(RFAILED);
        }
      }
      else
      {
        NB_LOG_ERROR(&nbCb, "enbCb not found for enbId %d", uDatEvnt.enbId);
        RETVALUE(RFAILED);
      }
   }
   if (enbCb == NULLP){
      NB_LOG_ERROR(&nbCb, "enbCb is NULL!!");
   }
#endif
#ifdef MULTI_ENB_SUPPORT
   if (nbBldS1SetupReq(&(uDatEvnt.pdu), enbCb) != ROK)
#else
   if (nbBldS1SetupReq(&(uDatEvnt.pdu)) != ROK)
#endif
   {
      RETVALUE(RFAILED);
   }

   uDatEvnt.transId.pres = PRSNT_NODEF;
   uDatEvnt.transId.val = 1;
   uDatEvnt.peerId.pres = PRSNT_NODEF;
   uDatEvnt.peerId.val = mmeId;

   /* Send the pdu to the MME */
   if((NbIfmS1apSndMgmtMsg(&uDatEvnt)) != ROK)
   {
      RETVALUE(RFAILED);
   }
   /* update state of the s1 connection */
   mmeCb->state = NB_MME_IN_PROG;
#ifndef MULTI_ENB_SUPPORT
   nbStartTmr((PTR)mmeCb, NB_TMR_MME_SETUP_RSP, nbCb.tmrCfg.s1SetupTmr);
#endif
   RETVALUE(ROK);
}

PUBLIC S16 nbBuildAndSendResetRequest
(
 NbResetMsgInfo *resetMsgInfo, UConnId spConnId
)
{
   SztUDatEvnt uDatEvnt;
   NbMmeCb *mmeCb = NULLP;

   mmeCb = &nbCb.mmeInfo;
   if(mmeCb == NULLP)
   {
      RETVALUE(RFAILED);
   }

   if(nbBldResetReq(&(uDatEvnt.pdu), resetMsgInfo) != ROK)
   {
      RETVALUE(RFAILED);
   }

   uDatEvnt.transId.pres = PRSNT_NODEF;
   uDatEvnt.transId.val = 1;
   uDatEvnt.peerId.pres = PRSNT_NODEF;
   uDatEvnt.peerId.val = nbCb.mmeInfo.mmeId;
   uDatEvnt.spConnId = spConnId;
#ifdef MULTI_ENB_SUPPORT
   uDatEvnt.enbId = resetMsgInfo->enbId;
#endif

   /* Send the pdu to the MME */
   if((NbIfmS1apSndMgmtMsg(&uDatEvnt)) != ROK)
   {
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* nbBuildAndSendResetRequest */

PUBLIC S16 nbBuildAndSendErabRelInd
(
 U32 enbUeS1apId,
 U32 mmeUeS1apId,
 U8 numOfErabIds,
 U8 *erabIdLst
)
{
   SztUDatEvnt uDatEvnt;
   NbMmeCb *mmeCb = NULLP;

   mmeCb = &nbCb.mmeInfo;
   if(mmeCb == NULLP)
   {
      RETVALUE(RFAILED);
   }

   if(nbBldErabRelInd(&(uDatEvnt.pdu), enbUeS1apId, mmeUeS1apId,
            numOfErabIds, erabIdLst) != ROK)
   {
      RETVALUE(RFAILED);
   }

   uDatEvnt.transId.pres = PRSNT_NODEF;
   uDatEvnt.transId.val = 1;
   uDatEvnt.peerId.pres = PRSNT_NODEF;
   uDatEvnt.peerId.val = nbCb.mmeInfo.mmeId;

   /* Send the pdu to the MME */
   if((NbIfmS1apSndMgmtMsg(&uDatEvnt)) != ROK)
   {
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* nbBuildAndSendErabRelInd */

PUBLIC S16 nbBuildAndSendErabRelRsp(NbUeCb *ueCb, U32 enbUeS1apId,
                                    U32 mmeUeS1apId, U8 numOfErabIdsRlsd,
                                    U8 *rlsdErabIdLst, U8 numOfErabIdsRlsFld,
                                    U8 *rlsFldErabLst) {
  // SztUDatEvnt uDatEvnt;
  SztDatEvntReq erabRelRsp = {0};
  NbMmeCb *mmeCb = NULLP;
  S1apPdu *erabRelPdu = NULLP;

  NB_SET_ZERO(&erabRelRsp, sizeof(SztDatEvntReq));

  mmeCb = &nbCb.mmeInfo;
  if (mmeCb == NULLP) {
    RETVALUE(RFAILED);
  }

  if (!ueCb) {
    NB_LOG_ERROR(&nbCb, "UeCb is NULL ");
    RETVALUE(RFAILED);
  }

  if (nbBldErabRelRsp(&(erabRelPdu), enbUeS1apId, mmeUeS1apId, numOfErabIdsRlsd,
                      rlsdErabIdLst, numOfErabIdsRlsFld,
                      rlsFldErabLst) != ROK) {
    RETVALUE(RFAILED);
  }

  NbS1ConCb *s1apCon = ueCb->s1ConCb;
  erabRelRsp.spConnId = s1apCon->spConnId;
  erabRelRsp.pdu = erabRelPdu;

  if ((NbIfmS1apDatReq(&erabRelRsp)) != ROK) {
    NB_LOG_ERROR(&nbCb, "Failed to send Erab Release Response ");
    RETVALUE(RFAILED);
  }

  RETVALUE(ROK);
} /* nbBuildAndSendErabRelRsp */

/*
 *    @brief Build and send the S1 Abort Request.
 *
 *    @details This function is used to build and send the S1 Abort Request
 *
 *    Function: nbBuildAndSendS1AbortReq
 *
 *       Processing steps:
 *        - Build and send S1 Abort Request to S1AP.
 *
 *    @param[in] cause: cause/reason for abort
 *
 *    @return  S16
 *       -# Success : ROK
 *       -# Failure : RFAILED
 */
PUBLIC S16 nbBuildAndSendS1AbortReq
(
 NbMmeId mmeId,
 U8 cause
)
{
   S16 ret = 0;
   SztAbortS1  abortS1;
   NbMmeCb *mmeCb = NULLP;
   NbUeCb *ueCb = NULLP, *prev = NULLP;

#ifdef MULTI_ENB_SUPPORT
   U32 enbIdx = 0;
#endif
   mmeCb = &nbCb.mmeInfo;
   if (mmeCb == NULLP)
   {
      RETVALUE(RFAILED);
   }

   abortS1.peerId.pres = PRSNT_NODEF;
   abortS1.peerId.val = mmeId;
   abortS1.sndAbortFlag = TRUE;
   abortS1.cause = cause;

   /* Send the pdu to the MME */
   NB_LOG_DEBUG(&nbCb, "Passing SCTP ABORT REQUEST to S1AP");
#ifdef MULTI_ENB_SUPPORT
   for(enbIdx = 0; enbIdx < smCfgCb.numOfEnbs; enbIdx++)
   {
      abortS1.enbId = enbIdx;
      if ((NbIfmS1apSndAbortMsg(&abortS1)) != ROK)
      {
         RETVALUE(RFAILED);
      }
   }
#else
   if ((NbIfmS1apSndAbortMsg(&abortS1)) != ROK)
   {
      RETVALUE(RFAILED);
   }
#endif
   /* update state of the s1 connection */
   smCfgCb.smState = NB_SM_STATE_AWAIT_S1_CON;
   mmeCb->state = NB_MME_INITED;
   /* flag to inform enbApp that it is local release */
   uesLocalRel = TRUE;
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

   RETVALUE(ROK);
}

/*
 *    @brief Build and send the S1 Shutdown Request.
 *
 *    @details This function is used to build and send the S1 Shutdown Request
 *
 *    Function: nbBuildAndSendS1AbortReq
 *
 *       Processing steps:
 *        - Build and send S1 Shutdown Request to S1AP.
 *
 *    @param[in] : none
 *
 *    @return  S16
 *       -# Success : ROK
 *       -# Failure : RFAILED
 */

PUBLIC S16 nbBuildAndSendS1ShutdownReq
(
 NbMmeId mmeId
)
{
   S16 ret = 0;
   SztAbortS1  abortS1;
   NbMmeCb *mmeCb = NULLP;
   NbUeCb *ueCb = NULLP, *prev = NULLP;
   /* Multi eNB support */
#ifdef MULTI_ENB_SUPPORT
   PRIVATE U32 enbIdx = 0;
#endif

   mmeCb = &nbCb.mmeInfo;
   if (mmeCb == NULLP)
   {
      RETVALUE(RFAILED);
   }

   abortS1.peerId.pres = PRSNT_NODEF;
   abortS1.peerId.val = mmeId;
   abortS1.sndAbortFlag = FALSE;

   /* Send the pdu to the MME */
   NB_LOG_DEBUG(&nbCb, "Passing SCTP SHUTDOWN REQUEST to S1AP");
   /* Multi eNB support */
#ifdef MULTI_ENB_SUPPORT
   for(enbIdx = 0; enbIdx < smCfgCb.numOfEnbs; enbIdx++)
   {
      abortS1.enbId = enbIdx;
      if ((NbIfmS1apSndAbortMsg(&abortS1)) != ROK)
      {
         RETVALUE(RFAILED);
      }
   }
#else
   if ((NbIfmS1apSndAbortMsg(&abortS1)) != ROK)
   {
      RETVALUE(RFAILED);
   }
#endif

   /* update state of the s1 connection */
   smCfgCb.smState = NB_SM_STATE_AWAIT_S1_CON;
   mmeCb->state = NB_MME_INITED;
   /* flag to inform enbApp that it is local release */
   uesLocalRel = TRUE;
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

   RETVALUE(ROK);
}


/* All initiating messages follow                                         */
/* ======================================= */
/* S1AP S1 SETUP REQUEST MESSAGE BUILDING  */
/* ======================================= */
/** @brief This function will allocate memory and build the
 *       S1AP:S1 Setup Request Message.
 *
 * @details This function allocates the memory for S1AP: S1 Setup Request
 *    Message PDU and fills the PDU with proper values.
 *
 * Function: nbBldSetupReq
 *
 *       Processing steps:
 *        - Allocate Memory for S1-AP: EnodeB S1 Setup Request Message PDU.
 *         - Fill the PDU with proper values.
 *
 *@param[out] pdu: S1-AP: S1 Setup Request PDU.
 * @return  S16
 *      -# Success : ROK
 *       -# Failure : RFAILED
 */
#ifdef MULTI_ENB_SUPPORT
PRIVATE S16 nbBldS1SetupReq
(
 S1apPdu                           **pdu,
 EnbCb                             *enbCb
)
#else
PRIVATE S16 nbBldS1SetupReq
(
 S1apPdu                           **pdu
)
#endif
{
   S1apPdu                        *setupReqPdu = NULLP;
   U16                            numComp;
   S16                            ret;
   SztProtIE_Field_S1SetupRqstIEs *ie;
   SztSuppTAs_Item                *tACItem;
   SztInitiatingMsg               *initMsg;
   U32                            numTAs, numCsgIds;
   U32                            taIdx;
   U32                            idx;
   U32                            ieIdx = 0;

   TRC2(nbtBldS1etupReq);
   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), NB_SZ_MEM_SDU_SIZE, &nbCb.mem,
         (Ptr *)&setupReqPdu);
   if(ret != ROK)
   {
      NB_LOG_ERROR(&nbCb, "cmAllocEvnt failed");
      RETVALUE(RFAILED);
   }
#ifdef MULTI_ENB_SUPPORT
   if (enbCb == NULLP)
   {
      NB_LOG_ERROR(&nbCb, "enbCb is NULL!!\n");
      RETVALUE(RFAILED);
   }
#endif
   nbFillTknU8(&(setupReqPdu->pdu.choice), SZT_TRGR_INTI_MSG);

   initMsg = &(setupReqPdu->pdu.val.initiatingMsg);
   nbFillTknU8(&(initMsg->pres), PRSNT_NODEF);
   nbFillTknU32(&(initMsg->procedureCode), Sztid_S1Setup);
   nbFillTknU32(&(initMsg->criticality), SztCriticalityrejectEnum);
   nbFillTknU8(&(initMsg->value.u.sztS1SetupRqst.pres), PRSNT_NODEF);

   numComp = 5;

   if ((cmGetMem(setupReqPdu,
                 numComp * sizeof(SztProtIE_Field_S1SetupRqstIEs),
                 (Ptr*)&initMsg->value.u.sztS1SetupRqst.protocolIEs.\
                 member)) !=ROK)
   {
      NB_LOG_ERROR(&nbCb, "BldS1SetupReq: cmGetMem failed");
      NB_FREE_EVNT(setupReqPdu);
      RETVALUE(RFAILED);
   }

   /* IE1 - Filling ENB Global Id */
   ie = &initMsg->value.u.sztS1SetupRqst.protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_Global_ENB_ID);
   nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   nbFillTknU8(&(ie->value.u.sztGlobal_ENB_ID.pres), PRSNT_NODEF);
   /* ENodeBType : Macro NB or Home NB */
   if (smCfgCb.eNodeBType.pres)
   {
#ifdef MULTI_ENB_SUPPORT
      /* Value coming from Test Stub */
      nbSztFillS1eNBId(setupReqPdu, smCfgCb.eNodeBType.val, enbCb->cell_id,
         &(enbCb->plmnId),
         &(ie->value.u.sztGlobal_ENB_ID));
#else
      /* Value coming from Test Stub */
      nbSztFillS1eNBId(setupReqPdu, smCfgCb.eNodeBType.val, nbCb.enbId,
         &smCfgCb.plmnId,
         &(ie->value.u.sztGlobal_ENB_ID));
#endif
   }
   else
   {
#ifdef MULTI_ENB_SUPPORT
      nbSztFillS1eNBId(setupReqPdu, enbCb->enbType, enbCb->cell_id,
         &(enbCb->plmnId),
         &(ie->value.u.sztGlobal_ENB_ID));
#else
      nbSztFillS1eNBId(setupReqPdu, nbCb.enbType, nbCb.enbId,
         &smCfgCb.plmnId,
         &(ie->value.u.sztGlobal_ENB_ID));
#endif
   }
   ieIdx++;

   /* IE2 - Filling ENB Name */
   ie = &initMsg->value.u.sztS1SetupRqst.protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_eNBname);
   nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   NB_GET_MEM(setupReqPdu, smCfgCb.enbNameLen, &(ie->value.u.sztENBname.val));
   ie->value.u.sztENBname.len  = smCfgCb.enbNameLen;
   if(smCfgCb.enbNameLen <= NB_ENB_NAME) /*KW Fix */
   {
      nbFillTknStrOSXL(&(ie->value.u.sztENBname), smCfgCb.enbNameLen,
            smCfgCb.enbName, &(setupReqPdu->memCp));
   }
   else
   {
      nbFillTknStrOSXL(&(ie->value.u.sztENBname), NB_ENB_NAME,
            smCfgCb.enbName, &(setupReqPdu->memCp));
   }

   ieIdx++;

   /* IE3 - Filling Supported TAs                                         */
   if (smCfgCb.suppTAs.pres)
   {
      ie = &initMsg->value.u.sztS1SetupRqst.protocolIEs.member[ieIdx];
      nbFillTknU8(&(ie->pres), PRSNT_NODEF);
      nbFillTknU32(&(ie->id), Sztid_SuppTAs);
      nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
      /* Handle the case of multiple TAs/cells                        */
      numTAs = smCfgCb.suppTAs.numTAs;
      nbFillTknU16(&(ie->value.u.sztSuppTAs.noComp), numTAs);
      if ((cmGetMem(setupReqPdu, numTAs * sizeof(SztSuppTAs_Item),
           (Ptr*)&(ie->value.u.sztSuppTAs.member))) != ROK)
      {
         NB_LOG_ERROR(&nbCb, "SztBldSetupReq: cmGetMem failed");
         NB_FREE_EVNT(setupReqPdu);
         RETVALUE(RFAILED);
      }
      for (taIdx = 0; taIdx < numTAs; taIdx++)
      {
         tACItem = &ie->value.u.sztSuppTAs.member[taIdx];
         nbFillTknU8(&(tACItem->pres), PRSNT_NODEF);
         nbSztFillTAC(smCfgCb.suppTAs.suppTA[taIdx].tac, setupReqPdu,
                      &tACItem->tAC);
         numComp = smCfgCb.suppTAs.suppTA[taIdx].bPlmnList.numBPlmns;
         /* Allocate memory for broadcast PLMNs */
         if ((cmGetMem(setupReqPdu, numComp * sizeof(SztBPLMNs),
              (Ptr*)&(tACItem->broadcastPLMNs.member))) != ROK)
         {
            NB_LOG_ERROR(&nbCb, "BldSetupReq:cmGetMem failed");
            NB_FREE_EVNT(setupReqPdu);
            RETVALUE(RFAILED);
         }
         nbFillTknU16(&(tACItem->broadcastPLMNs.noComp), numComp);
         for (idx = 0; idx < numComp; idx++)
         {
            nbSztFillPLMNId(setupReqPdu,
                           &(smCfgCb.suppTAs.suppTA[taIdx].bPlmnList.plmnIds[idx]),
                           &(tACItem->broadcastPLMNs.member[idx]));
         }
      }
      ieIdx++;
   }
   else
   {
      ie = &initMsg->value.u.sztS1SetupRqst.protocolIEs.member[ieIdx];
      nbFillTknU8(&(ie->pres), PRSNT_NODEF);
      nbFillTknU32(&(ie->id), Sztid_SuppTAs);
      nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
      numTAs = 1;
      nbFillTknU16(&(ie->value.u.sztSuppTAs.noComp), numTAs);
      if ((cmGetMem(setupReqPdu, numTAs * sizeof(SztSuppTAs_Item),
                  (Ptr*)&(ie->value.u.sztSuppTAs.member))) !=ROK)
      {
         NB_LOG_ERROR(&nbCb, "SztBldSetupReq: cmGetMem failed");
         NB_FREE_EVNT(setupReqPdu);
         RETVALUE(RFAILED);
      }
      for( taIdx = 0; taIdx < numTAs; taIdx++)
      {
         tACItem = &ie->value.u.sztSuppTAs.member[taIdx];
         nbFillTknU8(&(tACItem->pres), PRSNT_NODEF);
         #ifdef MULTI_ENB_SUPPORT
         nbSztFillTAC(enbCb->tac, setupReqPdu, &tACItem->tAC);
         #else
         nbSztFillTAC(smCfgCb.trackAreaCode, setupReqPdu, &tACItem->tAC);
         #endif
         numComp = 1;
         /* Allocate memory for broadcast PLMNs */
         if((cmGetMem(setupReqPdu, numComp * sizeof(SztPLMNidentity),
                     (Ptr*)&(tACItem->broadcastPLMNs.member))) !=ROK)
         {
            NB_LOG_ERROR(&nbCb, "BldSetupReq:cmGetMem failed");
            NB_FREE_EVNT(setupReqPdu);
            RETVALUE(RFAILED);
         }
         nbFillTknU16(&(tACItem->broadcastPLMNs.noComp), numComp);
         for(idx = 0; idx < numComp; idx++)
         {
            #ifdef MULTI_ENB_SUPPORT
            nbSztFillPLMNId(setupReqPdu, &(enbCb->plmnId),
                  &(tACItem->broadcastPLMNs.member[idx]));
            #else
            nbSztFillPLMNId(setupReqPdu, &(smCfgCb.plmnId),
                  &(tACItem->broadcastPLMNs.member[idx]));
            #endif
         }
      }
      ieIdx++;
   }

   /* IE4 - Filling the PagDRX */
   ie = &initMsg->value.u.sztS1SetupRqst.protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_DefaultPagDRX);
   nbFillTknU32(&(ie->value.u.sztPagDRX), 0);
   nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   ieIdx++;

   /* IE5 - Filling CSG ID List */
   if (smCfgCb.csgIdList.pres)
   {
      ie = &initMsg->value.u.sztS1SetupRqst.protocolIEs.member[ieIdx];
      nbFillTknU8(&(ie->pres), PRSNT_NODEF);
      nbFillTknU32(&(ie->id), Sztid_CSG_IdLst);
      /* Allocate memory for CSG ID List */
      numCsgIds = smCfgCb.csgIdList.pres;
      numCsgIds = smCfgCb.csgIdList.numCsgIds;
      nbFillTknU16(&(ie->value.u.sztCSG_IdLst.noComp), numCsgIds);
      if ((cmGetMem(setupReqPdu, numCsgIds * sizeof(SztCSG_IdLst_Item),
           (Ptr*)&(ie->value.u.sztCSG_IdLst.member))) != ROK)
      {
         NB_LOG_ERROR(&nbCb, "SztBldSetupReq: cmGetMem failed");
         NB_FREE_EVNT(setupReqPdu);
         RETVALUE(RFAILED);
      }
      for (idx = 0; idx < numCsgIds; idx++)
      {
         nbFillTknU8(&(ie->value.u.sztCSG_IdLst.member[idx].pres), PRSNT_NODEF);
         nbFillTknBStr32(&(ie->value.u.sztCSG_IdLst.member[idx].cSG_Id), 27,
                         smCfgCb.csgIdList.csgId[idx]);
      }

      nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
      ieIdx++;
   }

   /* Fill in the number of IEs included in the message */
   nbFillTknU16(&(initMsg->value.u.sztS1SetupRqst.protocolIEs.noComp), ieIdx);

   /* Pass the constructed PDU back to the caller */
   *pdu = setupReqPdu;

   RETVALUE(ROK);
} /* nbBldS1SetupReq */

PRIVATE S16 nbBldResetReq(S1apPdu **pdu, NbResetMsgInfo *resetMsgInfo) {
   S1apPdu                        *resetReqPdu = NULLP;
   S1apPdu                        *resetReqPdu1 = NULLP;
   U16                            numComp;
   U16                            cnt = 0;
   S16                            ret;
   SztProtIE_Field_ResetIEs       *ie;
   SztProtIE_SingleCont_UE_assocLogS1_ConItemRes *resetIe;
   SztInitiatingMsg               *initMsg;
   U32                            ieIdx = 0;
   U32                            ieIdx1 = 0;
   NbUeMsgCause                   cause = {0};

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), NB_SZ_MEM_SDU_SIZE, &nbCb.mem,
         (Ptr *)&resetReqPdu);
   if(ret != ROK)
   {
      NB_LOG_ERROR(&nbCb, "cmAllocEvnt failed");
      RETVALUE(RFAILED);
   }
   /* assin the cause values */
   cause.causeTyp = resetMsgInfo->cause.causeTyp;
   cause.causeVal = resetMsgInfo->cause.causeVal;

   nbFillTknU8(&(resetReqPdu->pdu.choice), SZT_TRGR_INTI_MSG);

   initMsg = &(resetReqPdu->pdu.val.initiatingMsg);
   nbFillTknU8(&(initMsg->pres), PRSNT_NODEF);
   nbFillTknU32(&(initMsg->procedureCode), Sztid_Reset);
   nbFillTknU32(&(initMsg->criticality), SztCriticalityrejectEnum);
   nbFillTknU8(&(initMsg->value.u.sztReset.pres), PRSNT_NODEF);

   numComp = 2;

   if ((cmGetMem(resetReqPdu, numComp * sizeof(SztProtIE_Cont_ResetIEs),
               (Ptr*)&initMsg->value.u.sztReset.protocolIEs.member)) != ROK)
   {
      NB_LOG_ERROR(&nbCb, "cmGetMem failed");
      NB_FREE_EVNT(resetReqPdu);
      RETVALUE(RFAILED);
   }

   /* IE1 - Filling Reset Cause */
   ie = &initMsg->value.u.sztReset.protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_Cause);
   nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   nbS1apFillCause(&ie->value.u.sztCause, &cause);
   ieIdx++;

   /* IE2 - Filling Reset Type */
   ie = &initMsg->value.u.sztReset.protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_ResetTyp);
   nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

   if(resetMsgInfo->type != NB_COMPLETE_RESET && resetMsgInfo->type != NB_PARTIAL_RESET)
   {
      NB_LOG_ERROR(&nbCb, "Invalid Reset Type");
      NB_FREE_EVNT(resetReqPdu);
      RETVALUE(RFAILED);
   }

   // Allocate memory for storing UE Id pair to be reset
   if(cmAllocEvnt(sizeof(S1apPdu), NB_SZ_MEM_SDU_SIZE, &nbCb.mem,
         (Ptr *)&resetReqPdu1) != ROK)
   {
      NB_LOG_ERROR(&nbCb, "cmAllocEvnt failed");
      RETVALUE(RFAILED);
   }
   if((cmGetMem(resetReqPdu1, resetMsgInfo->s1apIdCnt * \
               sizeof(SztProtIE_SingleCont_UE_assocLogS1_ConItemRes),
               (Ptr*)&ie->value.u.sztResetTyp.val.partOfS1_Intf.\
               member)) != ROK)
   {
      NB_LOG_ERROR(&nbCb, "cmGetMem failed");
      NB_FREE_EVNT(resetReqPdu);
      NB_FREE_EVNT(resetReqPdu1);
      RETVALUE(RFAILED);
   }

   /* TODO: Conditional assignments requirements */
   if(resetMsgInfo->type == NB_COMPLETE_RESET)
   {
      nbFillTknU8(&(ie->value.u.sztResetTyp.choice), RESETTYP_S1_INTF);
      nbFillTknU32(&(ie->value.u.sztResetTyp.val.s1_Intf),
            SztResetAllreset_allEnum);
   }
   else if(resetMsgInfo->type == NB_PARTIAL_RESET)
   {
      nbFillTknU8(&(ie->value.u.sztResetTyp.choice), RESETTYP_PARTOFS1_INTF);
   }

   /* This UE Id pair will be sent as it is to the MME in the reset message for
    * ENB Partial Reset message. However, it will be dropped in the S1AP layer
    * after extracting the connection details for ENB Complete Reset message
    */
   for(cnt = 0; cnt < resetMsgInfo->s1apIdCnt; cnt++)
   {
      resetIe = &ie->value.u.sztResetTyp.val.partOfS1_Intf.member[ieIdx1];
      nbFillTknU8(&(resetIe->pres), PRSNT_NODEF);
      nbFillTknU32(&(resetIe->id), Sztid_UE_assocLogS1_ConItem);
      nbFillTknU32(&(resetIe->criticality), SztCriticalityrejectEnum);
      nbFillTknU8(&(resetIe->value.u.sztUE_assocLogS1_ConItem.pres),
            PRSNT_NODEF);
      // Send mme ue s1ap id, if received from MME
      if(resetMsgInfo->mmeUeS1apIdLst[cnt])
      {
         nbFillTknU32(&(resetIe->value.u.sztUE_assocLogS1_ConItem.\
               mME_UE_S1AP_ID), resetMsgInfo->mmeUeS1apIdLst[cnt]);
      }
      else
      {
         resetIe->value.u.sztUE_assocLogS1_ConItem.mME_UE_S1AP_ID.pres =
                NOTPRSNT;
      }
      nbFillTknU32(
          &(resetIe->value.u.sztUE_assocLogS1_ConItem.eNB_UE_S1AP_ID),
          resetMsgInfo->enbUeS1apIdLst[cnt] & 0xFF);

      resetIe->value.u.sztUE_assocLogS1_ConItem.iE_Extns.\
         noComp.pres = NOTPRSNT;
      ieIdx1++;
   }
   nbFillTknU16(&(ie->value.u.sztResetTyp.val.partOfS1_Intf.noComp),
         resetMsgInfo->s1apIdCnt);
   ieIdx++;

   nbFillTknU16(&(initMsg->value.u.sztReset.protocolIEs.noComp), ieIdx);

   /* Pass the constructed PDU back to the caller */
   *pdu = resetReqPdu;

   RETVALUE(ROK);
} /* nbBldResetReq */

PRIVATE S16 nbBldErabRelInd
(
 S1apPdu **pdu,
 U32 enbUeS1apId,
 U32 mmeUeS1apId,
 U8 numOfErabIds,
 U8 *erabIdLst
)
{
   S1apPdu                        *erabRelIndPdu = NULLP;
   S1apPdu                        *erabRelIndPdu1 = NULLP;
   U16                            numComp;
   U16                            cnt = 0;
   S16                            ret;
   U32                            ieIdx = 0;
   SztProtIE_Field_E_RABRlsIndIEs *ie;
   SztProtIE_SingleCont_E_RABItemIEs *erabRelLstIe;
   SztInitiatingMsg               *initMsg;
   NbUeMsgCause                   cause = {0};

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), NB_SZ_MEM_SDU_SIZE, &nbCb.mem,
         (Ptr *)&erabRelIndPdu);
   if(ret != ROK)
   {
      NB_LOG_ERROR(&nbCb, "cmAllocEvnt failed");
      RETVALUE(RFAILED);
   }

   nbFillTknU8(&(erabRelIndPdu->pdu.choice), SZT_TRGR_INTI_MSG);

   initMsg = &(erabRelIndPdu->pdu.val.initiatingMsg);
   nbFillTknU8(&(initMsg->pres), PRSNT_NODEF);
   nbFillTknU32(&(initMsg->procedureCode), Sztid_E_RABRlsInd);
   nbFillTknU32(&(initMsg->criticality), SztCriticalityignoreEnum);
   nbFillTknU8(&(initMsg->value.u.sztE_RABRlsInd.pres), PRSNT_NODEF);

   numComp = 3;

   if ((cmGetMem(erabRelIndPdu,
               numComp * sizeof(SztProtIE_Field_E_RABRlsIndIEs),
               (Ptr*)&initMsg->value.u.sztE_RABRlsInd.protocolIEs.\
               member)) != ROK)
   {
      NB_LOG_ERROR(&nbCb, "cmGetMem failed");
      NB_FREE_EVNT(erabRelIndPdu);
      RETVALUE(RFAILED);
   }

   /* IE1 - Filling MME UE S1AP ID */
   ie = &initMsg->value.u.sztE_RABRlsInd.protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
   nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   nbFillTknU32(&ie->value.u.sztMME_UE_S1AP_ID, mmeUeS1apId);
   ieIdx++;

   /* IE2 - Filling ENB UE S1AP ID */
   ie = &initMsg->value.u.sztE_RABRlsInd.protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
   nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   nbFillTknU32(&ie->value.u.sztENB_UE_S1AP_ID, enbUeS1apId);
   ieIdx++;

   /* IE3 - Filling E-RAB ID Lst */
   ie = &initMsg->value.u.sztE_RABRlsInd.protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_E_RABRlsdLst);
   nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   ieIdx++;

   ret = cmAllocEvnt(sizeof(S1apPdu), NB_SZ_MEM_SDU_SIZE, &nbCb.mem,
         (Ptr *)&erabRelIndPdu1);

   if((cmGetMem(erabRelIndPdu1, numOfErabIds * \
               sizeof(SztProtIE_SingleCont_E_RABItemIEs),
               (Ptr*)&ie->value.u.sztE_RABLst.member)) != ROK)
   {
      NB_LOG_ERROR(&nbCb, "cmGetMem failed");
      NB_FREE_EVNT(erabRelIndPdu1);
      RETVALUE(RFAILED);
   }

   for(cnt = 0; cnt < numOfErabIds; cnt++)
   {
      erabRelLstIe = &ie->value.u.sztE_RABLst.member[cnt];

      nbFillTknU8(&(erabRelLstIe->pres), PRSNT_NODEF);
      nbFillTknU32(&(erabRelLstIe->id), Sztid_E_RABItem);
      nbFillTknU32(&(erabRelLstIe->criticality), SztCriticalityignoreEnum);

      nbFillTknU8(&(erabRelLstIe->value.u.sztE_RABItem.pres), PRSNT_NODEF);
      nbFillTknU32(&(erabRelLstIe->value.u.sztE_RABItem.e_RAB_ID),
            erabIdLst[cnt]);
      nbS1apFillCause(&(erabRelLstIe->value.u.sztE_RABItem.cause), &cause);
      erabRelLstIe->value.u.sztE_RABItem.iE_Extns.noComp.pres = NOTPRSNT;
   }

   nbFillTknU16(&(ie->value.u.sztE_RABLst.noComp), numOfErabIds);
   nbFillTknU16(&(initMsg->value.u.sztE_RABRlsInd.protocolIEs.noComp), ieIdx);

   /* Pass the constructed PDU back to the caller */
   *pdu = erabRelIndPdu;

   RETVALUE(ROK);
} /* nbBldErabRelInd */

PRIVATE S16 nbBldErabRelRsp
(
 S1apPdu **pdu,
 U32 enbUeS1apId,
 U32 mmeUeS1apId,
 U8 numOfErabIdsRlsd,
 U8 *rlsdErabIdLst,
 U8 numOfErabIdsRlsFld,
 U8 *rlsFldErabIdLst
)
{
   S1apPdu                        *erabRelRspPdu = NULLP;
   S1apPdu                        *erabRelRspPdu1 = NULLP;
   U16                            numComp;
   U16                            cnt = 0;
   S16                            ret;
   U32                            ieIdx = 0;
   SztProtIE_Field_E_RABRlsRespIEs *ie;
   SztProtIE_SingleCont_E_RABRlsItemBrRelCompIEs *erabRelLstIe;
   SztSuccessfulOutcome           *succOut;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), NB_SZ_MEM_SDU_SIZE, &nbCb.mem,
         (Ptr *)&erabRelRspPdu);
   if(ret != ROK)
   {
      NB_LOG_ERROR(&nbCb, "cmAllocEvnt failed");
      RETVALUE(RFAILED);
   }

   nbFillTknU8(&(erabRelRspPdu->pdu.choice), SZT_TRGR_SUCCESS_OUTCOME);

   succOut = &(erabRelRspPdu->pdu.val.successfulOutcome);
   nbFillTknU8(&(succOut->pres), PRSNT_NODEF);
   nbFillTknU32(&(succOut->procedureCode), Sztid_E_RABRls);
   nbFillTknU32(&(succOut->criticality), SztCriticalityrejectEnum);
   nbFillTknU8(&(succOut->value.u.sztE_RABRlsResp.pres), PRSNT_NODEF);

   numComp = 3;

   if ((cmGetMem(erabRelRspPdu,
               numComp * sizeof(SztProtIE_Field_E_RABRlsRespIEs),
               (Ptr*)&succOut->value.u.sztE_RABRlsResp.protocolIEs.\
               member)) != ROK)
   {
      NB_LOG_ERROR(&nbCb, "cmGetMem failed");
      NB_FREE_EVNT(erabRelRspPdu);
      RETVALUE(RFAILED);
   }

   /* IE1 - Filling MME UE S1AP ID */
   ie = &succOut->value.u.sztE_RABRlsResp.protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
   nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   nbFillTknU32(&ie->value.u.sztMME_UE_S1AP_ID, mmeUeS1apId);
   ieIdx++;

   /* IE2 - Filling ENB UE S1AP ID */
   ie = &succOut->value.u.sztE_RABRlsResp.protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
   nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   nbFillTknU32(&ie->value.u.sztENB_UE_S1AP_ID, enbUeS1apId);
   ieIdx++;

   /* IE3 - Filling ERAB Released Lst */
   ie = &succOut->value.u.sztE_RABRlsResp.protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_E_RABRlsLstBrRelComp);
   nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   ieIdx++;

   ret = cmAllocEvnt(sizeof(S1apPdu), NB_SZ_MEM_SDU_SIZE, &nbCb.mem,
         (Ptr *)&erabRelRspPdu1);

   if((cmGetMem(erabRelRspPdu1, numOfErabIdsRlsd * \
               sizeof(SztProtIE_SingleCont_E_RABItemIEs),
               (Ptr*)&ie->value.u.sztE_RABLst.member)) != ROK)
   {
      NB_LOG_ERROR(&nbCb, "cmGetMem failed");
      NB_FREE_EVNT(erabRelRspPdu1);
      RETVALUE(RFAILED);
   }

   for(cnt = 0; cnt < numOfErabIdsRlsd; cnt++)
   {
      erabRelLstIe = &ie->value.u.sztE_RABRlsLstBrRelComp.member[cnt];

      nbFillTknU8(&(erabRelLstIe->pres), PRSNT_NODEF);
      nbFillTknU32(&(erabRelLstIe->id), Sztid_E_RABRlsItemBrRelComp);
      nbFillTknU32(&(erabRelLstIe->criticality), SztCriticalityignoreEnum);

      nbFillTknU8(&(erabRelLstIe->value.u.sztE_RABRlsItemBrRelComp.pres), PRSNT_NODEF);
      nbFillTknU32(&(erabRelLstIe->value.u.sztE_RABRlsItemBrRelComp.e_RAB_ID),
            rlsdErabIdLst[cnt]);
      erabRelLstIe->value.u.sztE_RABRlsItemBrRelComp.iE_Extns.noComp.pres = NOTPRSNT;
   }

   nbFillTknU16(&(ie->value.u.sztE_RABLst.noComp), numOfErabIdsRlsd);
   nbFillTknU16(&(succOut->value.u.sztE_RABRlsResp.protocolIEs.noComp), ieIdx);

   /* Pass the constructed PDU back to the caller */
   *pdu = erabRelRspPdu;

   RETVALUE(ROK);
} /* nbBldErabRelRsp */

/** @brief This function process incoming the recieved S1AP PDU.
 *
 *@details
 *
 *Function: nbMmePrcRcvdPdu
 *
 *   Processing steps:
 *    - Based on the choice of the message PDU, It will procss the Initing
 *       PDU, Successful outcome and Unsuccessful outcome messages.
 *
 *
 * @param[in] peerId: Peer ID.
 * @param[in]    pdu: S1AP PDU
 *  @return  S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 nbPrcRcvdPdu
(
   U32      peerId,
   S1apPdu  *pdu
)
{
   S16 ret = RFAILED;

   switch (pdu->pdu.choice.val)
   {
      case S1AP_PDU_INITIATINGMSG:
         ret = nbPrcInitPdu(peerId, pdu);
         break;
      case S1AP_PDU_SUCCESSFULOUTCOME:
         ret = nbPrcSuccPdu(peerId, pdu);
         break;
      case S1AP_PDU_UNSUCCESSFULOUTCOME:
         ret = nbPrcUnsuccPdu(peerId, pdu);
         break;
      default :
           break;
   }

   RETVALUE(ret);
} /* end of nbPrcRcvdPdu */

/** @brief This function process the MME initiated messages which are belongs to
 *         EMM specific module.
 *
 * @details This function process the MME initiated messags like S1AP: MME
 *          Configuration Update Messages, MME initiated RESET message,
 *          PAging message, Overload Start message, Write Replacement warning
 *          message etc.,
 *
 *     Function: nbPrcInitPdu
 *
 *         Processing steps:
 *         - Based on the S1AP Initing PDU's procedure code,
 *           call the respective function to process the received PDU.
 *
 * @param[in] peerId: Peer ID from which S1AP PDU received.
 * @param[in]    pdu: S1-AP MME initiated PDU.
 * @return  S16
 *       -# Success : ROK
 */
PUBLIC S16 nbPrcInitPdu
(
U32                          peerId,
S1apPdu                      *pdu
)
{
   S16                       ret = ROK;
   SztInitiatingMsg          *initMsg = &pdu->pdu.val.initiatingMsg;

   switch(initMsg->procedureCode.val)
   {
      case Sztid_Pag:
         nbProcPagingMsg(pdu);
         break;
      case Sztid_E_RABRls:
         nbProcErabRelCmd(pdu, NULL);
         break;
#ifdef MULTI_ENB_SUPPORT
      case Sztid_MMEConfigTfr:
         NB_LOG_DEBUG(&nbCb, "RECEIVED MME CONFIG TRANSFER");
         ret = nbPrcMMEConfigTrf(peerId, pdu);
         break;
      case Sztid_HovrResourceAllocn:
         // S1 HO Request is the Initiating msg for HO Resource Allocation
         NB_LOG_DEBUG(&nbCb, "Received S1 Handover Request Message");
         ret = nbPrcS1HoReq(peerId, pdu);
         break;
#endif
      default:
         NB_LOG_ERROR(&nbCb,"Err: Msg not handled");
         break;
   }
   UNUSED(peerId);
   RETVALUE(ret);
} /* end of nbPrcInitPdu */

/*
 * @brief This function is used to process the S1-AP Paging message.
 *
 * @details
 *
 *     Function:nbProcPagingMsg
 *
 *         Processing steps:
 *         - This function is called EMM module on reception trigger from the
 *           S1-AP IM module upon receiving S1-AP:Paging Message from MME.
 *         - Identify in which Cells the RRC:Paging message needs to triger
 *           based on TAI and or CSGID for each cell and received List in
 *           S1-AP Pagigng Message.
 *         - Update the UePagingInfo(which includes all information to
 *           calculate PF and PO and paging record) from S1-AP:Paging Message.
 *         - Traverse all Cells supported by ENB to validate paging msg
 *           trigger is required or not.
 *         - If the cell's TAI is present in the received S1-AP Paging
 *           Request TAI list.Then trigger the RRC:Paging message in this
 *           Cell.
 *         - Otherwise Validate the CSG id of the cell is present or not
 *           in the received S1-AP paging Req csg id list.If CSG ID is
 *           present then trgger the RRC:paging message in the current cell.
 *           Otherwise skip cell to process the paging request.
 *
 * @param [in] s1apPagMsg : S1-AP paging message PDU.
 * @return S16
 *       ROK     : succefully processed the S1-AP paging message.
 *       RFAILED : not able to process the paging message due to memory lack.
 */
PUBLIC S16 nbProcPagingMsg
(
 S1apPdu *s1apPagMsg
)
{
   SztTAILst *taiLst = NULLP;
   SztCSG_IdLst *csgIdLst = NULLP;
   NbPagingMsgInfo uePagingInfo;
   U16 cellIdx = 0;
   S16 retVal = ROK;

   TRC2(nbProcPagingMsg);

   /* Initialize the default paging priority to 255 and the same will be
    * updated if it is received from MME.
    */
   uePagingInfo.pagPriority = NB_DEFAULT_PAGING_PRI;

   /* Update the UePagingInfo from S1-AP:Paging Message */
   nbUpdateUePagInfo(s1apPagMsg, &uePagingInfo, &taiLst, &csgIdLst);

   NB_LOG_DEBUG(&nbCb, "Received PAGING, UE Index = [%d], CN Domain = [%d]",
         uePagingInfo.ue_Id, uePagingInfo.domIndType);

   /* traverse all Cells supported by ENB to validate paging msg trigger is
    * required or not */
   for (cellIdx = 0; cellIdx < 1; cellIdx++)
   {
      /* cell's TAI is present in the received S1-AP paging Req TAI list */
     /* if ((NULLP != taiLst) &&
            (TRUE == nbIsTaiPresent(taiLst)))*/
      {
         retVal = nbUiBuildAndSendPagingMsg(&uePagingInfo);
      }

   } /* end of for to traverse all the cells in ENB */
   RETVALUE(retVal);
} /* end of nbProcPagingMsg */

/*
 * @brief This function is used to process the S1-AP Paging message.
 *
 * @param [in] s1apPagMsg : S1-AP paging message PDU.
 * @return S16
 *       ROK     : succefully processed the S1-AP ERAB Release Cmd message.
 *       RFAILED : not able to process the ERAB Release Cmd message due to
 *       memory lack.
 */
PUBLIC S16 nbProcErabRelCmd(S1apPdu *s1apErabRlsCmd, NbUeCb *ueCb) {
  S16 retVal = ROK;
  U16 numComp = 0;
  U16 cnt = 0;
  U16 erabCnt = 0;
  NbErabRelCmd erabRelCmd = {0};
  SztE_RABRlsCmmd *erabRlsCmd = NULLP;
  SztProtIE_Field_E_RABRlsCmmdIEs *ie = NULLP;
  U32 enbUeS1apId = 0;
  U32 mmeUeS1apId = 0;
  U8 numOfErabIdsRlsd = 0;
  SztNAS_PDU *nasPdu = NULLP;
  NbUeTunInfo *tunInfo = NULLP;
  NbErabRelReq *erabRelReq = NULLP;

  TRC2(nbProcErabRelCmd);
  erabRlsCmd = &s1apErabRlsCmd->pdu.val.initiatingMsg.value.u.sztE_RABRlsCmmd;
  numComp = erabRlsCmd->protocolIEs.noComp.val;

  for (cnt = 0; cnt < numComp; cnt++) {
    ie = &erabRlsCmd->protocolIEs.member[cnt];
    switch (ie->id.val) {
    case Sztid_eNB_UE_S1AP_ID:
      erabRelCmd.enbUeS1apId = ie->value.u.sztENB_UE_S1AP_ID.val;
      break;
    case Sztid_MME_UE_S1AP_ID:
      erabRelCmd.mmeUeS1apId = ie->value.u.sztMME_UE_S1AP_ID.val;
      break;
    case Sztid_E_RABToBeRlsdLst:
      erabRelCmd.numOfErabIds = ie->value.u.sztE_RABLst.noComp.val;
      NB_ALLOC(&erabRelCmd.erabIdLst, erabRelCmd.numOfErabIds);
      for (erabCnt = 0; erabCnt < erabRelCmd.numOfErabIds; erabCnt++) {
        erabRelCmd.erabIdLst[erabCnt] = ie->value.u.sztE_RABLst.member[erabCnt]
                                            .value.u.sztE_RABItem.e_RAB_ID.val;
      }
      break;
    case Sztid_uEaggregateMaxBitrate:
      break;
    case Sztid_downlinkNASTport:
      break;
    case Sztid_NAS_PDU:
      if (ie->value.u.sztNAS_PDU.pres == PRSNT_NODEF) {

        erabRelCmd.nasPdu.pres = TRUE;
        NB_ALLOC(&erabRelCmd.nasPdu.val,
                 ((ie->value.u.sztNAS_PDU.len + 1) * sizeof(U8)));
        erabRelCmd.nasPdu.pres = TRUE;
        erabRelCmd.nasPdu.len = ie->value.u.sztNAS_PDU.len;
        cmMemcpy((U8 *)erabRelCmd.nasPdu.val, (U8 *)ie->value.u.sztNAS_PDU.val,
                 erabRelCmd.nasPdu.len);
      }
      break;
    default:
      NB_LOG_ERROR(&nbCb, "Invalid IE.");
      retVal = RFAILED;
      break;
    }
  }
  enbUeS1apId = erabRelCmd.enbUeS1apId;
  mmeUeS1apId = erabRelCmd.mmeUeS1apId;
  numOfErabIdsRlsd = erabRelCmd.numOfErabIds;

  /* Get UeCb using enb/mme ue s1ap Ids */
  /*for(cnt = 0; cnt < nbCb.crntUeIdx; cnt++)
  {
  }*/
  if (!ueCb) {
    cmHashListFind(&(nbCb.ueCbLst), (U8 *)&(enbUeS1apId), sizeof(U8), 0,
                 (PTR *)(&ueCb));
  }
  for (cnt = 0; cnt < numOfErabIdsRlsd; cnt++) {
    U32 bearerId = erabRelCmd.erabIdLst[cnt];
    retVal = cmHashListFind(&(ueCb->tunnInfo), (U8 *)&(bearerId), sizeof(U32),
                            0, (PTR *)(&tunInfo));
    if (tunInfo == NULL) {
      NB_LOG_ERROR(&nbCb, "Could not find tuninfo \n");
    }
    if (tunInfo) {
      cmHashListDelete(&(ueCb->tunnInfo), (PTR)(tunInfo));
      NB_LOG_DEBUG(&nbCb, "Deleted tun info for bearer %d\n",
                   erabRelCmd.erabIdLst[cnt]);
    }
  }

  /* Send message to nb dam to delete the packet filters */
  NB_ALLOC(&erabRelReq, sizeof(NbErabRelReq));
  erabRelReq->ueId = ueCb->ueId;
  erabRelReq->numOfErabIds = numOfErabIdsRlsd;

  NB_ALLOC(&erabRelReq->erabIdLst, erabRelReq->numOfErabIds * sizeof(U8));
  cmMemcpy(erabRelReq->erabIdLst, erabRelCmd.erabIdLst,
           erabRelReq->numOfErabIds * sizeof(U8));
  nbIfmDamErabDelReq((Void *)erabRelReq);

  if (erabRelCmd.nasPdu.pres == TRUE) {
    /* Need to send to UeApp */
    retVal = nbSendErabsRelInfo(&erabRelCmd, ueCb->ueId);

    /* Send Erab Rel Rsp message */
    retVal =
        nbBuildAndSendErabRelRsp(ueCb, enbUeS1apId, mmeUeS1apId, numOfErabIdsRlsd,
                                 erabRelCmd.erabIdLst, 0, NULL);
  } else {
    /* Indicate the TFW about the recieved E-RAB Release command. */
    nbUiSendErabRelCmdInfoToUser(&erabRelCmd);
  }

  RETVALUE(retVal);
} /* end of nbProcErabRelCmd */

/*
 * @brief This function is used to validate the cell TAI is present in the TAI
 *         list received in the S1AP: Paging message.
 *
 * @details
 *
 *     Function: nbIsTaiPresent
 *
 *     Processing steps:
 *     - Get the Tracking Area Code, num of PLMNs and PLMN IDs from NbCb.
 *     - Traverse all TAIs in S1-AP paging msg and compare with cell TAI.
 *     - First compare the TAC in TAI of the cell is matched with the
 *       received TAC in TAI.Then compare the received PLMN with the
 *       cell PLMN list.If there is any match found then returns TRUE.
 *       Otherwise returns FALSE.
 *
 * @param [in] cellCb : cell control block
 * @param [in] taiLst : TAI list
 * @return Bool
 *         TRUE  : If cell TAI is matched with at least one TAI in the received
 *                 TAI list.
 *         FALSE : cell TAI is not present in the received TAI list.
 */
PUBLIC Bool nbIsTaiPresent
(
 SztTAILst   *taiLst
)
{
   NbPlmnId                          *cellPlmnId   = NULLP;
   NbPlmnId                          plmnId;
   SztProtIE_SingleCont_TAIItemIEs   *taiMbr       = NULLP;
   SztPLMNidentity                   *plmnIe       = NULLP;
   U8                                cellTac[2]    = {0};
   U8                                numPlmnIds    = 0;
   U8                                plmnIndex, taiIndex;

   /* Get the Tracking Area Code,num of PLMNs and PLMN IDs from SIB1 */
   cellTac[1] = (U8)(nbCb.tac & 0xff);
   cellTac[0] = (U8)((nbCb.tac & 0xff00)>>8);

   numPlmnIds = 1; /*cellCb->sib1.numPlmnIds;*/

   /* traverse all TAIs in S1-AP paging msg and compare with cell TAI */
   for (taiIndex = 0; (taiIndex < taiLst->noComp.val); taiIndex++)
   {
      taiMbr = &taiLst->member[taiIndex];

      if ((cellTac[0] == taiMbr->value.u.sztTAIItem.tAI.tAC.val[0]) &&
            (cellTac[1] == taiMbr->value.u.sztTAIItem.tAI.tAC.val[1]))
      {
         /* Parse S1AP PLMN ID IE */
         plmnIe = &taiMbr->value.u.sztTAIItem.tAI.pLMNidentity;
         nbParsePlmnIe(plmnIe, &plmnId);

         /* compare the received PLMNID with the cell PLMNIDs */
         for (plmnIndex = 0 ; plmnIndex < numPlmnIds; plmnIndex++)
         {
            cellPlmnId = &nbCb.plmnId;
            if(nbPlmnPlmnsEqual(&plmnId, cellPlmnId))
            {
               RETVALUE(TRUE);
            }
         } /* end of for loop for PLMN Ids comparison */
      }  /* end of if for TAC comparison */
   } /* end of TAI list for loop */

   RETVALUE(FALSE);
} /* end of wrPbmIsTaiPresent */

/** @brief This function validates the requested PLMNs are equal or not.
 *
 * @details This function validates the requested source and destination PLMNs
 *          are equal or not.
 *
 *     Function: nbPlmnPlmnsEqual
 *
 *         Processing steps:
 *         - If the both requested PLMN ID's number of MNC digitts  not equal
 *           then return both the PLMNs are not equal.
 *         - Otherwise compare both the requested PLMN IDs are having the same
 *           MCC and MNC digit values.If bothe are matches then return TRUE.
 *           otherwise FALSE.
 *
 * @param[in] plmnId1: source PLMN ID
 * @param[in] plmnId2: destination PLMN ID
 * @return Bool
 *        -# Success : TRUE
 *        -# Failure : FALSE
 */
PUBLIC Bool nbPlmnPlmnsEqual
(
 NbPlmnId                     *plmnId1,
 NbPlmnId                     *plmnId2
)
{
   if ((plmnId1->mcc[0] != plmnId2->mcc[0]) ||
       (plmnId1->mcc[1] != plmnId2->mcc[1]) ||
       (plmnId1->mcc[2] != plmnId2->mcc[2]))
   {
      RETVALUE(FALSE);
   }
   if (plmnId1->numMncDigits != plmnId2->numMncDigits)
   {
      RETVALUE(FALSE);
   }
   if ((plmnId1->mnc[0] != plmnId2->mnc[0]) ||
       (plmnId1->mnc[1] != plmnId2->mnc[1]))
   {
      RETVALUE(FALSE);
   }
   if (plmnId1->numMncDigits == 3)
   {
      if (plmnId1->mnc[2] != plmnId2->mnc[2])
      {
         RETVALUE(FALSE);
      }
   }
   RETVALUE(TRUE);
} /* end of nbPlmnPlmnsEqual */

/*This This function process the Successful Outcome S1AP PDUs like
 *S1 Setup Response, EnodeB Configration Update ack or Reset
 *   Acknowledge messages.
 *
 *Function: wrEmmMmePrcSuccPdu
 *
 *      Processing steps:
 *       - Based on the Succesful Outcome S1AP PDU's procedure code call the
 *          corresponding response processing function.
 *
 * @param[in] peerId: Peer ID.
 * @param[in]    pdu: S1-AP PDU
 * @return  S16
 *       -# Success : ROK
 *       -# Failure : RFAILED
 */
/** @brief This function parse the S1-AP Paging msg and update the uePagingInfo.
 *
 * @details
 *
 *     Function: wrPbmUpdateUePagInfo
 *
 *         Processing steps:
 *         - Update all the parameters of UePagingInfo which we received from
 *           S1-AP:Paging message.
 *         - Update the output parameters pagMsgTAILst, pagMsgCSG_IdLst if the
 *           TAI and CSG IDs are present in the received S1-AP paging message.
 *           If any list is not present set the oupur parameter to NULLP.
 *
 * @param [in]       s1apPagMsg : S1-AP paging message PDU
 * @param [out]    uePagingInfo : UE specific paging info updated based on S1-AP PDU.
 * @param [out]    pagMsgTAILst : TAI list if TAI Lst present in Paging Msg or NULLP.
 * @param [out] pagMsgCSG_IdLst : CSG ID List if CSG Lst present in paging msg or NULLP
 * @return S16
 *    -# Success : ROK
 *    -# Failure : RFAILED
 */
PUBLIC S16 nbUpdateUePagInfo
(
 S1apPdu             *s1apPagMsg,
 NbPagingMsgInfo   *uePagingInfo,
 SztTAILst           **pagMsgTAILst,
 SztCSG_IdLst        **pagMsgCSG_IdLst
)
{
   SztProtIE_Field_PagIEs *pagMember = NULLP;
   SztPag                 *sztPag     = NULLP;
   U16                    memberIdx = 0;
   TknBStr32              *ueIdxBitStr = NULLP;
   U16                    numCompPagMsg = 0;
   U32                    ueId = 0;
   U8                     idx1, idx2;
   U16                    memberId;

   TRC2(nbPbmUpdateUePagInfo);

   /* Get the reference of the Paging Message */
   sztPag = &(s1apPagMsg->pdu.val.initiatingMsg.value.u.sztPag);
   numCompPagMsg = sztPag->protocolIEs.noComp.val;

   /* Accessing the IEs within the S1AP pdu */
   for(memberIdx = 0; memberIdx < numCompPagMsg; memberIdx++)
   {
      pagMember = &(sztPag->protocolIEs.member[memberIdx]);
      memberId = pagMember->id.val;

      switch(memberId)
      {
         case Sztid_TAILst:
            {
               *pagMsgTAILst = &(pagMember->value.u.sztTAILst);
               break;
            }
         case Sztid_CSG_IdLst:
            {
               *pagMsgCSG_IdLst = &(pagMember->value.u.sztCSG_IdLst);
               break;
            }
         case Sztid_UEIdentityIdxValue:
            {
               ueIdxBitStr = &(pagMember->value.u.sztUEIdentityIdxValue);
               /* UEID is only 10 bits so it has been shifted for 6 bits */
               ueId = 0;
               ueId =((ueIdxBitStr->val[0] << 2) |
                     ((ueIdxBitStr->val[1] & 0xC0) >> 6));
               uePagingInfo->ue_Id = ueId;
               break;
            }
         case Sztid_UEPagID:
            {
               if(pagMember->value.u.sztUEPagID.choice.val == UEPAGID_IMSI)
               {
                  uePagingInfo->ueIdenType = UEPAGID_IMSI;
                  /* Number of IMSI Digits(0-9 digits are
                     only valid) = 2 * IMSI legth in bytes                   */
                  uePagingInfo->ueIden.imsi[0] =
                     2*(pagMember->value.u.sztUEPagID.val.iMSI.len);

                  /* Converting IMSI in byte format to IMSI in digit format    */
                  for(idx1 = 0, idx2 = 1;
                        idx1 < pagMember->value.u.sztUEPagID.val.iMSI.len;
                        idx1++, idx2++)
                  {
                     uePagingInfo->ueIden.imsi[idx2]  =
                        pagMember->value.u.sztUEPagID.val.iMSI.val[idx1] & 0x0f;
                     uePagingInfo->ueIden.imsi[++idx2]  =
                        ((pagMember->value.u.sztUEPagID.val.iMSI.val[idx1] & 0xf0) >> 4);
                  } /* end of for loop */

                  /*   When IMSI has odd number of digits,the filler
                   *   digit will  be added at the end to make an even number
                   *   of digits of length 2N. The filler digit must be ignorded
                   *   while sending to RRC and the length should be decremented
                   * */
                  if((uePagingInfo->ueIden.imsi[idx2-1] == 0xf))
                  {
                     uePagingInfo->ueIden.imsi[0] =
                        uePagingInfo->ueIden.imsi[0] - 1 ;
                  }
               }
               else if (pagMember->value.u.sztUEPagID.choice.val == UEPAGID_S_TMSI)
               {
                  uePagingInfo->ueIdenType = UEPAGID_S_TMSI;
                  uePagingInfo->ueIden.sTMSI.pres = TRUE;
                  uePagingInfo->ueIden.sTMSI.mmec = pagMember->value.u.
                     sztUEPagID.val.s_TMSI.mMEC.val[0];

                  for(idx1 = 0; idx1 < 4; idx1++)
                  {
                     uePagingInfo->ueIden.sTMSI.mTMSI <<= 8;
                     uePagingInfo->ueIden.sTMSI.mTMSI |=
                        (U32)(pagMember->value.u.sztUEPagID.
                              val.s_TMSI.m_TMSI.val[idx1]);
                  } /* end of for loop */
               }
               else
               {
                  NB_LOG_ERROR(&nbCb, "Valid UE Identity should be provided");
                  RETVALUE(RFAILED);
               } /* end of else statement */
               break;
            } /* end of Sztid_UEPagID */
         case Sztid_pagingDRX:
            {
               uePagingInfo->pagingDrxPres = TRUE;
               uePagingInfo->ueSpcPagDrx = pagMember->value.u.sztPagDRX.val;
               break;
            } /* end of Sztid_pagingDRX */
         case Sztid_CNDomain:
            {
               uePagingInfo->domIndType = pagMember->value.u.sztCNDomain.val;
               break;
            }
         case Sztid_PagPriority:
            {
               uePagingInfo->pagPriority = pagMember->value.u.sztPagPriority.val;
            }
            break;
         default:
            {
               NB_LOG_ERROR(&nbCb, "Unknown IE or Option received:[%d]",
                     memberId);
               break;
            }
      } /* end of switch statement */
   } /* end of for loop */

   RETVALUE(ROK);
} /* end of wrPbmUpdateUePagInfo */

PRIVATE S16 nbPrcSuccPdu
(
 U32      peerId,
 S1apPdu  *pdu
)
{
   SztSuccessfulOutcome  *succMsg = &pdu->pdu.val.successfulOutcome;
   S16  ret = ROK;

   switch (succMsg->procedureCode.val)
   {
      case Sztid_S1Setup:
         NB_LOG_DEBUG(&nbCb, "RECEIVED SUCCESSFUL S1 SETUP RESPONSE");
         ret = nbPrcS1SetupRsp(peerId, pdu);
         break;
      case Sztid_Reset:
         NB_LOG_DEBUG(&nbCb, "RECEIVED RESET ACK");
         ret = nbPrcResetAck(peerId, pdu);
         break;

      default:
         NB_LOG_ERROR(&nbCb, "Invalid IE.");
         ret = RFAILED;
         break;
   }

   RETVALUE(ret);
} /* end of nbPrcSuccPdu */

PUBLIC S16 nbPrcS1SetupFail(U16 peerId, S1apPdu *pdu)
{
   NbMmeCb      *mmeCb = NULLP;
   TknU32       *s1TimeToWait = NULLP;
   TknU8        *ie = NULLP;
   U32          wait = 0;
   S16          ret = ROK;
   SztCause     *cause = NULLP;
   U8           causeType = 0;
   U32          causeVal = 0;
   mmeCb = &nbCb.mmeInfo;

   NB_LOG_ERROR(&nbCb, "S1 setup failure received");
   /* Multi eNB support */
#ifndef MULTI_ENB_SUPPORT
   nbStopTmr((PTR)mmeCb, NB_TMR_MME_SETUP_RSP);
#endif

   nbSzGetIE(&(pdu->pdu), Sztid_Cause, &ie);

   if(ie == NULLP)
   {
      NB_LOG_ERROR(&nbCb, "Failed to retrive cause");
      RETVALUE(RFAILED);
   }

   cause = (SztCause *)ie;
   causeType = cause->choice.val;
   switch(cause->choice.val)
   {
      case CAUSE_RADIONW:
         causeVal = cause->val.radioNw.val;
         break;
      case CAUSE_TRANSPORT:
         causeVal = cause->val.transport.val;
         break;
      case CAUSE_NAS:
         causeVal = cause->val.nas.val;
         break;
      case CAUSE_PROTOCOL:
         causeVal = cause->val.protocol.val;
         break;
      case CAUSE_MISC:
         causeVal = cause->val.misc.val;
         switch(causeVal)
         {
            case SztCauseMisccontrol_processing_overloadEnum:
               NB_LOG_ERROR(&nbCb, "Control processing overload");
               break;
            case SztCauseMiscnot_enough_user_plane_processing_resourcesEnum:
               NB_LOG_ERROR(&nbCb, "Not enough user plane processing resources");
               break;
            case SztCauseMischardware_failureEnum:
               NB_LOG_ERROR(&nbCb, "Hardware failure");
               break;
            case SztCauseMiscom_interventionEnum:
               NB_LOG_ERROR(&nbCb, "Communication intervention");
               break;
            case SztCauseMiscunspecifiedEnum:
               NB_LOG_ERROR(&nbCb, "Unspecified");
               break;
            case SztCauseMiscunknown_PLMNEnum:
               NB_LOG_ERROR(&nbCb, "Unkown-PLMN");
               break;
            default :
               NB_LOG_ERROR(&nbCb, "invalid case");
               break;
         }
         break;
      default:
         NB_LOG_ERROR(&nbCb, "invalid case");
         break;
   }
   nbSzGetIE(&(pdu->pdu), Sztid_TimeToWait, &ie);
   s1TimeToWait = (TknU32 *)ie;
   if(s1TimeToWait != NULLP)
   {
      wait = s1TimeToWait->val;
   }
   /* send s1-setup response to user */

   nbUiSendS1SetupFailInd(causeType, causeVal, wait);
   UNUSED(peerId);
   RETVALUE(ret);
}

/* @brief This function process the S1AP Unsuccessful Outcome messages.
 *
 * @details This function process the S1AP Unsuccessful Outcome messages like
 *          S1-Setup Response Fail, EnodeB Configuration Update failure meesages.
 *
 * Function: nbPrcUnsuccPdu
 *
 * Processing steps:
 *- Based on the Unsuccessful S1AP PDU's procedure code, this funcation
 * calls the respective functions to process the failure messages.
 *
 * @param[in] peerId: Peer ID.
 * @param[in]    pdu: S1-AP PDU
 *@return    -# Success: ROK
 *-# Failure: RFAILED
 */
PRIVATE S16 nbPrcUnsuccPdu
(
 U32                          peerId,
 S1apPdu                      *pdu
)
{
   TRC2(nbPrcUnsuccPdu);
   SztUnsuccessfulOutcome    *unsuccMsg = &pdu->pdu.val.unsuccessfulOutcome;
   S16                       ret        = ROK;

   switch(unsuccMsg->procedureCode.val)
   {
      case Sztid_S1Setup:
         NB_LOG_ERROR(&nbCb, "RECEIVED UNSECCESSFUL SETUP RESPONSE");
         ret = nbPrcS1SetupFail(peerId, pdu);
         break;
     default:
         NB_LOG_ERROR(&nbCb, "Unknown procedure code received");
         break;
   }
   RETVALUE(ret);
} /* end of uccPdubPrcUnsuccPdu */

PUBLIC Void  nbSztFillTAC
(
 U16                          tac,
 S1apPdu                      *pdu,
 SztTAC                       *tAC
)
{
   tAC->pres   = PRSNT_NODEF;
   tAC->len    = NB_LAC_IE_LEN;
   tAC->val[1] = (U8)(tac & 0xff);
   tAC->val[0] = (U8)((tac & 0xff00)>>8);
   /*RETVALUE(ROK);*/
}

/*  @brief This function builds the UL NAS pdu
*
*      Function: nbS1apBldUlNasPdu
*
*          Processing steps:
*          - Alloc memory to S1AP UL NAS pdu message
*          - fill the mandatory IE's
*          - update the pointer to S1AP UL NAS pdu message
*            into out pointer
*
*  @param [in]  ueCb     : pointer to UE CB
*  @param [in]  nasPdu   : encoded nas pdu
*  @param [out] pdu      : double pointer to return the UL NAS PDU
*  @return S16
  -# Success : ROK
  -# Failure : RFAILED
*/
#ifdef MULTI_ENB_SUPPORT
PUBLIC S16 nbS1apBldUlNasPdu
(
 NbUeCb *ueCb,
 TknStrOSXL *nasPdu,
 S1apPdu **pdu,
 EnbCb   *enbCb
)
#else
PUBLIC S16 nbS1apBldUlNasPdu
(
 NbUeCb *ueCb,
 TknStrOSXL *nasPdu,
 S1apPdu **pdu
)
#endif
{
   NbS1ConCb                 *s1apCon = ueCb->s1ConCb;
   S1apPdu                   *ulNasPdu = NULLP;
   SztInitiatingMsg          *initMsg;
   U32                       ieIdx = 0;
   SztUlnkNASTport           *ulNas;
   SztProtIE_Field_UlnkNASTport_IEs *ie = NULLP;

   /* Initialize memory control point */
   if (cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &nbCb.mem,
            (Ptr *)&ulNasPdu) != ROK)
   {
      NB_LOG_ERROR(&nbCb, "Failed to allocate memory. cmAllocEvnt failed");
      RETVALUE(RFAILED);
   }

   nbFillTknU8(&(ulNasPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   initMsg = &ulNasPdu->pdu.val.initiatingMsg;
   nbFillTknU8(&(initMsg->pres), PRSNT_NODEF);
   nbFillTknU32(&(initMsg->criticality), SztCriticalityignoreEnum);
   nbFillTknU32(&(initMsg->procedureCode), Sztid_uplinkNASTport);
   ulNas = &(initMsg->value.u.sztUlnkNASTport);
   nbFillTknU8(&(ulNas->pres), PRSNT_NODEF);

   /* Allocate memory for 5 IEs */
   if ((cmGetMem(ulNasPdu, 5 * sizeof(SztProtIE_Field_UlnkNASTport_IEs),
               (Ptr*)&ulNas->protocolIEs.member)) !=ROK)
   {
      NB_LOG_ERROR(&nbCb, "Failed to allocate memory. cmGetMem failed");
      RETVALUE(RFAILED);
   }

   /* IE1 - Filling MME ID */
   ie = &ulNas->protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
   nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   nbFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), s1apCon->mme_ue_s1ap_id);
   ieIdx++;

   /* IE2 - Filling enb s1ap id */
   ie = &ulNas->protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
   nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   nbFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), s1apCon->enb_ue_s1ap_id);
   ieIdx++;

   /* IE3 - Filling nas pdu */
   ie = &ulNas->protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_NAS_PDU);
   nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   nbFillTknStrOSXL(&(ie->value.u.sztNAS_PDU), nasPdu->len, nasPdu->val,
         &(ulNasPdu->memCp));
   ieIdx++;

   /* IE4 - Filling  EUTRAN CGI */
   ie = &ulNas->protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_EUTRAN_CGI);
   nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
#ifdef MULTI_ENB_SUPPORT
   nbS1apFillEutranCgi(ulNasPdu, &(ie->value.u.sztEUTRAN_CGI), enbCb);
#else
   nbS1apFillEutranCgi(ulNasPdu, &(ie->value.u.sztEUTRAN_CGI));
#endif
   ieIdx++;

   /* IE5 - Filling  TAI*/
   ie = &ulNas->protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_TAI);
   nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   nbFillTknU8(&(ie->value.u.sztTAI.pres), PRSNT_NODEF);
#ifdef MULTI_ENB_SUPPORT
   nbS1apFillTAI(ueCb, ulNasPdu, &(ie->value.u.sztTAI), enbCb);
#else
   nbS1apFillTAI(ueCb, ulNasPdu, &(ie->value.u.sztTAI));
#endif
   ieIdx++;

   /* Fill the number of IEs in the UL NAS message                        */
   nbFillTknU16(&(ulNas->protocolIEs.noComp), ieIdx);

   *pdu = ulNasPdu;

   RETVALUE(ROK);
}

/*  @brief This function builds the UE RADIO CAPABILITY IND
*
*      Function: nbS1apBldUeCapIndPdu
*
*          Processing steps:
*          - Alloc memory to S1AP UE RADIO CAPABILITY IND message
*          - fill the mandatory IE's
*          - update the pointer to RRC ASN.1 encoded Capability IE
*            into out pointer
*
*  @param [in]  ueCb     : pointer to UE CB
*  @param [in]  nasPdu   : encoded nas pdu
*  @param [out] pdu      : double pointer to return the UE RADIO CAPABILITY IND PDU
*  @return S16
  -# Success : ROK
  -# Failure : RFAILED
*/

PUBLIC S16 nbS1apBldUeCapIndPdu
(
 NbUeCb         *ueCb,
 TknStrOSXL     *capInfo,
 S1apPdu        **pdu
)
{
   NbS1ConCb                 *s1apCon = ueCb->s1ConCb;
   S1apPdu                   *ulCapIndPdu = NULLP;
   SztInitiatingMsg          *initMsg;
   U32                       ieIdx = 0;
   SztUECapbltyInfoInd           *ueCapInfo;
   SztProtIE_Field_UECapbltyInfoIndIEs *ie = NULLP;

   /* Initialize memory control point */
   if (cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &nbCb.mem,
            (Ptr *)&ulCapIndPdu) != ROK)
   {
      NB_LOG_ERROR(&nbCb,"Failed to allocate memory. cmAllocEvnt failed");
      RETVALUE(RFAILED);
   }

   nbFillTknU8(&(ulCapIndPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   initMsg = &ulCapIndPdu->pdu.val.initiatingMsg;
   nbFillTknU8(&(initMsg->pres), PRSNT_NODEF);
   nbFillTknU32(&(initMsg->criticality), SztCriticalityignoreEnum);
   nbFillTknU32(&(initMsg->procedureCode), Sztid_UECapbltyInfoInd);
   ueCapInfo = &(initMsg->value.u.sztUECapbltyInfoInd);
   nbFillTknU8(&(ueCapInfo->pres), PRSNT_NODEF);

   /* Allocate memory for 3 IEs */
   if ((cmGetMem(ulCapIndPdu, 3 * sizeof(SztProtIE_Field_UECapbltyInfoIndIEs),
               (Ptr*)&ueCapInfo->protocolIEs.member)) !=ROK)
   {
      NB_LOG_ERROR(&nbCb,"Failed to allocate memory. cmGetMem failed");
      RETVALUE(RFAILED);
   }

   /* IE1 - Filling MME ID */
   ie = &ueCapInfo->protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
   nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   nbFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), s1apCon->mme_ue_s1ap_id);
   ieIdx++;

   /* IE2 - Filling enb s1ap id */
   ie = &ueCapInfo->protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres),PRSNT_NODEF);
   nbFillTknU32(&(ie->id),Sztid_eNB_UE_S1AP_ID);
   nbFillTknU32(&(ie->criticality),SztCriticalityrejectEnum);
   nbFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), s1apCon->enb_ue_s1ap_id);
   ieIdx++;

   /* IE3 - Filling UE Radio Capability */
   ie = &ueCapInfo->protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres),PRSNT_NODEF);
   nbFillTknU32(&(ie->id),Sztid_UERadioCapblty);
   nbFillTknU32(&(ie->criticality),SztCriticalityignoreEnum);
   nbFillTknStrOSXL(&(ie->value.u.sztUERadioCapblty), capInfo->len, capInfo->val,
         &(ulCapIndPdu->memCp));
   ieIdx++;

   /* Fill the number of IEs in the UL NAS message                        */
   nbFillTknU16(&(ueCapInfo->protocolIEs.noComp), ieIdx);

   *pdu = ulCapIndPdu;

   RETVALUE(ROK);
}

/** @brief This function is responsible for parsing the Initial Context Setup
 *         Request message and store the information into the internal data
 *         structure.
 *
 * @details
 *
 *     Function: nbInitCtxtPrcSetup
 *
 *         Processing steps:
 *         - for the number of IEs present in the message
 *         - parse the IE and store the information into the internal data
 *           structure
 *
 * @param[in]  transCb : transaction information
 * @return S16
 *    -#Success : ROK
 *    -#Failure : RFAILED
 */
PRIVATE S16 nbHandleInitCtxtPrcSetup(NbUeCb *ueCb, S1apPdu *pdu) {
  NbErabLst *erabInfo = NULLP;
  U16 cnt = 0;
  S16 retVal = RFAILED;
  NbUeMsgCause cause;
  U8 idx;
  SztInitiatingMsg *initMsg = NULLP;
  SztProtIE_Field_InitCntxtSetupRqstIEs *ie = NULLP;
  SztProtIE_Cont_InitCntxtSetupRqstIEs *protIes = NULLP;
  SztE_RABToBeSetupLstCtxtSUReq *s1ErabLst = NULLP;
  Bool ueRadCapRcvd = FALSE;

  // Parse and process the received IEs
  initMsg = &(pdu->pdu.val.initiatingMsg);
  protIes = &initMsg->value.u.sztInitCntxtSetupRqst.protocolIEs;

  for (cnt = 0; cnt < protIes->noComp.val; cnt++) {
    ie = &(protIes->member[cnt]);
    switch (ie->id.val) {
    case Sztid_MME_UE_S1AP_ID: {
      ueCb->s1ConCb->mme_ue_s1ap_id = ie->value.u.sztid_MME_UE_S1AP_ID.val;
      break;
    }
    case Sztid_eNB_UE_S1AP_ID: {
      ueCb->s1ConCb->enb_ue_s1ap_id = ie->value.u.sztENB_UE_S1AP_ID.val;
      break;
    }
    case Sztid_uEaggregateMaxBitrate: {
      break;
    }
    case Sztid_E_RABToBeSetupLstCtxtSUReq: {
      s1ErabLst = &ie->value.u.sztE_RABToBeSetupLstCtxtSUReq;
      if ((retVal = nbGetErabInfoFrmIntCnxt(ueCb, s1ErabLst, &erabInfo)) !=
          ROK) {
        NB_LOG_ERROR(&nbCb, "processing ERABs failed");
        RETVALUE(RFAILED);
      }
      break;
    }
    case Sztid_UESecurCapabilities: {
#ifdef MULTI_ENB_SUPPORT
      U32 idx = 0;
      U16 temp =
          ie->value.u.sztUESecurCapabilities.encryptionAlgorithms.val[idx++];
      ueCb->encryptionAlgo |= temp << 8;
      temp = ie->value.u.sztUESecurCapabilities.encryptionAlgorithms.val[idx];
      ueCb->encryptionAlgo |= temp;

      idx = 0;
      temp = 0;
      temp = ie->value.u.sztUESecurCapabilities.integrityProtectionAlgorithms
                 .val[idx++];
      ueCb->integrityAlgo |= temp << 8;
      temp = ie->value.u.sztUESecurCapabilities.integrityProtectionAlgorithms
                 .val[idx];
      ueCb->integrityAlgo |= temp;
#endif
      break;
    }
    case Sztid_SecurKey: {
      break;
    }
    case Sztid_UERadioCapblty: {
      ueRadCapRcvd = TRUE;
      break;
    }
    case Sztid_CSFallbackIndicator: {
      break;
    }
    case Sztid_CSGMembershipStatus: {
      break;
    }
    case Sztid_RegisteredLAI: {
      break;
    }
    case Sztid_GUMMEI_ID: {
      break;
    }
    case Sztid_MME_UE_S1AP_ID_2: {
      break;
    }
    case Sztid_HovrRestrnLst: {
      break;
    }
    case Sztid_ManagementBasedMDTAllowed: {
      break;
    }
    case Sztid_SubscriberProfileIDforRFP: {
    } break;
    default:
      break;
    }
  }

  ueCb->s1ConCb->s1apConnState = NB_S1AP_CONNECTED;
  if (erabInfo != NULLP) {
    if (nbCb.initCtxtSetupFail[(ueCb->ueId) - 1].initCtxtSetupFailInd == TRUE) {
      cause.causeTyp = nbCb.initCtxtSetupFail[(ueCb->ueId) - 1].causeType;
      cause.causeVal = nbCb.initCtxtSetupFail[(ueCb->ueId) - 1].causeVal;
      if (ROK != sendInitCtxtSetupFailRsp(ueCb, &cause)) {
        NB_LOG_DEBUG(
            &nbCb,
            "Failed to send Initial Context Setup Failure message to MME");
      }
      NB_FREE(erabInfo->erabs, (erabInfo->noOfComp * sizeof(NbErabCb)));
      NB_FREE(erabInfo, sizeof(NbErabLst));
    } else if (nbCb.dropInitCtxtSetup[(ueCb->ueId) - 1].isDropICSEnable ==
               TRUE) {
      if (!nbIsTmrRunning(&nbCb.dropInitCtxtSetup[(ueCb->ueId) - 1].timer,
                          NB_TMR_LCL_UE_CTXT_REL_REQ)) {
        // Start timer to release the UE context locally
        cmInitTimers(&nbCb.dropInitCtxtSetup[(ueCb->ueId) - 1].timer, 1);
        if (retVal !=
            nbStartTmr((PTR)ueCb, NB_TMR_LCL_UE_CTXT_REL_REQ,
                       nbCb.dropInitCtxtSetup[(ueCb->ueId) - 1].tmrVal)) {
          RETVALUE(retVal);
        }
      }

      // Send indication to tfwApp for dropping the Initial Context Setup Req
      retVal = nbUiSendIntCtxtSetupDrpdIndToUser(ueCb->ueId);
      if (retVal != ROK) {
        NB_LOG_ERROR(&nbCb, "Failed to send Initial Context Setup Dropped "
                            "Indiaction to User");
      }
      NB_FREE(erabInfo->erabs, (erabInfo->noOfComp * sizeof(NbErabCb)));
      NB_FREE(erabInfo, sizeof(NbErabLst));
    } else if (nbCb.dropICSSndCtxtRel[(ueCb->ueId) - 1].sndICSRspUeCtxtRel ==
               TRUE) {
      retVal = nbSendUeCtxtRelReqAsICSRsp(ueCb);
      NB_FREE(erabInfo->erabs, (erabInfo->noOfComp * sizeof(NbErabCb)));
      NB_FREE(erabInfo, sizeof(NbErabLst));
    } else {
      if (nbCb.delayInitCtxtSetupRsp[(ueCb->ueId) - 1].delayICSRsp != TRUE) {
        // Send the s1-context resp to mme and nas pdu to UE
        retVal = nbBuildAndSendIntCtxtSetupRsp(ueCb, erabInfo);
        if (retVal != ROK) {
          NB_FREE(erabInfo->erabs, (erabInfo->noOfComp * sizeof(NbErabCb)));
          NB_FREE(erabInfo, sizeof(NbErabLst));
          RETVALUE(RFAILED);
        }
        retVal = nbSendErabsInfo(ueCb, erabInfo, NULL, ueRadCapRcvd);
        // Send UeIpInfoReq message to ueApp only for successful bearers
        if (nbCb.initCtxtSetupFailedErabs[ueCb->ueId - 1].numFailedErabs > 0) {
          Bool found = FALSE;
          for (idx = 0; idx < erabInfo->noOfComp; idx++) {
            for (U8 failed_idx = 0;
                 failed_idx <
                 nbCb.initCtxtSetupFailedErabs[ueCb->ueId - 1].numFailedErabs;
                 failed_idx++) {
              if (erabInfo->erabs[idx].erabId ==
                  nbCb.initCtxtSetupFailedErabs[ueCb->ueId - 1]
                      .failedErabs[failed_idx]) {
                found = TRUE;
                break;
              }
            }
            if (found) {
              found = FALSE;
              continue;
            }
            nbHandleUeIpInfoReq(ueCb->ueId, erabInfo->erabs[idx].erabId, TRUE);
          }
          nbCb.initCtxtSetupFailedErabs[ueCb->ueId - 1].numFailedErabs = 0;
        } else {
          for (idx = 0; idx < erabInfo->noOfComp; idx++) {
            nbHandleUeIpInfoReq(ueCb->ueId, erabInfo->erabs[idx].erabId, TRUE);
          }
        }
        NB_FREE(erabInfo->erabs, (erabInfo->noOfComp * sizeof(NbErabCb)));
        NB_FREE(erabInfo, sizeof(NbErabLst));
      } else {
        retVal = nbSendErabsInfo(ueCb, erabInfo, NULL, ueRadCapRcvd);
        // Do the IP-query to ueapp for received bearers
        for (idx = 0; idx < erabInfo->noOfComp; idx++) {
          nbHandleUeIpInfoReq(ueCb->ueId, erabInfo->erabs[idx].erabId, TRUE);
        }
        nbStartDelayTimerForICSRsp(ueCb->ueId, erabInfo);
      }
    }
  }
  RETVALUE(retVal);
}

PRIVATE S16 nbHandleRabSetupMsg(NbUeCb *ueCb, S1apPdu *pdu) {
  U8 idx;
  SztInitiatingMsg *initMsg = &pdu->pdu.val.initiatingMsg;
  SztE_RABSetupRqst *rabSetupIE = &initMsg->value.u.sztE_RABSetupRqst;
  SztProtIE_Field_E_RABSetupRqstIEs *ie;
  NbErabLst *erabInfo = NULLP;
  NbFailedErabLst *failedErabInfo = NULLP;
  S16 retVal = RFAILED;
  SztE_RABToBeSetupLstBrSUReq *s1ErabLst;
  for (idx = 0; idx < rabSetupIE->protocolIEs.noComp.val; idx++) {
    ie = &rabSetupIE->protocolIEs.member[idx];
    switch (ie->id.val) {
      case Sztid_E_RABToBeSetupLstBrSUReq: {
        s1ErabLst = &ie->value.u.sztE_RABToBeSetupLstBrSUReq;
        if ((retVal = nbGetErabInfoFrmErabSetup(ueCb, s1ErabLst, &erabInfo,
                                                &failedErabInfo)) != ROK) {
          NB_LOG_ERROR(&nbCb, "processing ERABs failed");
          RETVALUE(RFAILED);
        }
        break;
      }
    }
  }
  if (erabInfo != NULLP || failedErabInfo != NULLP) {

    retVal = nbSendErabsInfo(ueCb, erabInfo, failedErabInfo, TRUE);
    /* query the ip address from ueapp for the received bearers */
    if (erabInfo->noOfComp > 0) {
      for (idx = 0; idx < erabInfo->noOfComp; idx++) {
        nbHandleUeIpInfoReq(ueCb->ueId, erabInfo->erabs[idx].erabId, FALSE);
      }
    }
    // Check if erab setup req needs to be dropped
    if (nbCb.dropErabSetupReq[(ueCb->ueId) - 1].isDropErabSetupReq) {
      // Reset isDropErabSetupReq flag
      nbCb.dropErabSetupReq[(ueCb->ueId) - 1].isDropErabSetupReq = FALSE;
      NB_LOG_DEBUG(&nbCb,
                 "Dropping E-RAB Setup Request message\n");
      RETVALUE(retVal);
    }
    // Start a timer to delay sending of erab setup rsp
    if (nbCb.delayErabSetupRsp[(ueCb->ueId) - 1].isDelayErabSetupRsp) {
      retVal = nbStartDelayTimerForErabRsp(
          ueCb->ueId, erabInfo, failedErabInfo,
          nbCb.delayErabSetupRsp[(ueCb->ueId) - 1].tmrVal);
      nbCb.delayErabSetupRsp[(ueCb->ueId) - 1].isDelayErabSetupRsp = FALSE;
      RETVALUE(retVal);
    }
    retVal = nbRabSetupSndS1apRsp(ueCb, erabInfo, failedErabInfo);
    NB_FREE(erabInfo->erabs, (erabInfo->noOfComp * sizeof(NbErabCb)));
    NB_FREE(erabInfo, sizeof(NbErabLst));
    if (failedErabInfo) {
      NB_FREE(failedErabInfo->failedErabs,
              (failedErabInfo->noOfComp * sizeof(NbFailedErab)));
      NB_FREE(failedErabInfo, sizeof(NbFailedErabLst));
    }
  }
  RETVALUE(retVal);
}

PUBLIC S16 nbGetS1UeRelCause(S1apPdu *pdu, NbRelCause *relCause) {
  U8 idx = 0;
  SztInitiatingMsg *initMsg = &pdu->pdu.val.initiatingMsg;
  SztUECntxtRlsCmmd *s1UeCtxtRelCmd = &initMsg->value.u.sztUECntxtRlsCmmd;
  SztProtIE_Field_UECntxtRlsCmmd_IEs *ie = NULLP;

  for (idx = 0; idx < s1UeCtxtRelCmd->protocolIEs.noComp.val; idx++) {
    ie = s1UeCtxtRelCmd->protocolIEs.member + idx;
    if (ie->id.val == Sztid_Cause) {
      relCause->causeType = ie->value.u.sztCause.choice.val;
      switch (relCause->causeType) {
      case NB_CAUSE_RADIONW:
        relCause->causeVal = ie->value.u.sztCause.val.radioNw.val;
        break;
      case NB_CAUSE_TRANSPORT:
        relCause->causeVal = ie->value.u.sztCause.val.transport.val;
        break;
      case NB_CAUSE_NAS:
        relCause->causeVal = ie->value.u.sztCause.val.nas.val;
        break;
      case NB_CAUSE_PROTOCOL:
        relCause->causeVal = ie->value.u.sztCause.val.protocol.val;
        break;
      case NB_CAUSE_MISC:
        relCause->causeVal = ie->value.u.sztCause.val.misc.val;
        break;
      default:
        NB_LOG_ERROR(&nbCb, "Unknown cause received");
        break;
      }
      break;
    }
  }
} // nbGetS1UeRelCause

/** @brief  This function is called by IFM module to pass the received S1AP
*          PDU
*
* @details
*
*     Function:
*
*         Processing steps:
*           This function is receives procedure initiaing messages from UE. It
*           creates an incoming message that is common for all the different
*           interfaces and invokes wrUmmPrcIncMsg() for further processing.
*
*
* @param  SztConCfm        *conCfm
*
* @return S16
  -# Success : ROK
  -# Failure : RFAILED
*/

PUBLIC S16 nbPrcIncS1apMsg(NbUeCb *ueCb, S1apPdu *pdu, U8 msgType) {
  U32 procedureCodeVal;
  U8 ret = RFAILED;
  NbRelCause relCause = {0};
  // Get the procedure code
  procedureCodeVal = pdu->pdu.val.initiatingMsg.procedureCode.val;
  if (procedureCodeVal == 11) // downlink NAS Transport MSG
  {
    ret = nbProcessDlNasMsg(ueCb, pdu, msgType);
  } else if (procedureCodeVal == 9) // initial context setup request
  {
    ret = nbHandleInitCtxtPrcSetup(ueCb, pdu);
    // Inform the Tfw about Initial Context Setup
    if ((nbCb.dropInitCtxtSetup[(ueCb->ueId) - 1].isDropICSEnable != TRUE) &&
        (nbCb.dropICSSndCtxtRel[(ueCb->ueId) - 1].sndICSRspUeCtxtRel != TRUE)) {
      ret = nbUiSendIntCtxtSetupIndToUser(
          ueCb->ueId,
          nbCb.initCtxtSetupFail[(ueCb->ueId) - 1].initCtxtSetupFailInd);
      if (ret != ROK) {
        NB_LOG_ERROR(&nbCb, "Failed to Send Initial Context Setup"
                            "Indiaction to ueApp");
      }
    }
  } else if (procedureCodeVal == 5) // rab setup request
  {
    NB_LOG_DEBUG(&nbCb,
                 "nbPrcIncS1apMsg(): Handling RAB Setup Request message\n");
    ret = nbHandleRabSetupMsg(ueCb, pdu);
  } else if (procedureCodeVal == 23) // context release command message
  {
    nbGetS1UeRelCause(pdu, &relCause);
    ret = nbHandleS1UeReleaseCmd(ueCb, relCause);
    if (ret == ROK) {
#ifdef MULTI_ENB_SUPPORT
      if (ueCb->s1HoInfo != NULLP) {
        if (!(ueCb->s1HoInfo->s1HoEvent == S1_HO_OVRALL_TMR_EXPIRY &&
              relCause.causeType == NB_CAUSE_RADIONW &&
              relCause.causeVal == SztCauseRadioNwsuccessful_handoverEnum)) {

          NB_LOG_DEBUG(&nbCb,
                       "Released UE context from source ENB. "
                       "Deleting the S1 handover context for UE Id: %u",
                       ueCb->ueId);
          nbCb.s1HoDone = FALSE;
          NB_FREE(ueCb->s1HoInfo, sizeof(NbS1HoInfo));
        }
      } else {
#endif
        // Inform the ueApp about UE context release
        ret = nbSendS1RelIndToUeApp(ueCb->ueId);
        if (ret != ROK) {
          NB_LOG_ERROR(&nbCb, "Failed to Send S1 Release Indiaction "
                              "to ueApp");
        }
#ifdef MULTI_ENB_SUPPORT
      }
#endif

      if (nbIsTmrRunning(&nbCb.dropInitCtxtSetup[(ueCb->ueId) - 1].timer,
                         NB_TMR_LCL_UE_CTXT_REL_REQ)) {
        nbCb.dropInitCtxtSetup[(ueCb->ueId) - 1].isDropICSEnable = FALSE;

        if (ROK != (cmHashListFind(&(nbCb.ueCbLst), (U8 *)&(ueCb->ueId),
                                   sizeof(U32), 0, (PTR *)&ueCb))) {
          NB_LOG_ERROR(&nbCb,
                       "Failed to stop the local UE context release timer, "
                       "could not find ueCb");
          RETVALUE(RFAILED);
        } else {
          nbStopTmr((PTR)ueCb, NB_TMR_LCL_UE_CTXT_REL_REQ);
        }
      }
#if 0

         /* Inform the Tfw about UE context release */
         ret = nbUiSendUeCtxRelIndToUser(ueCb->ueId);
         /* trigger ueCb deletion in enbApp */
         ret = nbIfmDamUeDelReq(ueCb->ueId);
#endif
    }
  } else if (procedureCodeVal == 7) {
    NB_LOG_DEBUG(&nbCb,
                 "nbPrcIncS1apMsg(): Handling RAB Release Command message\n");
    ret = nbProcErabRelCmd(pdu, ueCb);
    if (ret != ROK) {
      NB_LOG_ERROR(&nbCb, "Failed to send Erab Release Command Indication "
                          "to ueApp");
    }

  }
#ifdef MULTI_ENB_SUPPORT
  else if (procedureCodeVal == 3) // Path SW Req Ack
  {
    NB_LOG_DEBUG(&nbCb, "RECEIVED PATH SW REQ ACK");
    ret = nbPrcPathSwReqAck(ueCb, pdu);
  } else if (procedureCodeVal == 0) // Handover Preparation
  {
    if (pdu->pdu.choice.val == 1) {
      // Choice: 1 (SuccessfulOutcome) -Handover Command
      ret = nbPrcS1HoCommand(ueCb, pdu);
    } else if (pdu->pdu.choice.val == 2) {
      // Choice: 2 (UnsuccessfulOutcome) -Handover Preparation Failure
      ret = nbPrcS1HoPrepFailure(ueCb, pdu);
    }

    if (ret != ROK) {
      NB_LOG_ERROR(&nbCb, "Failed to handle S1 handover preparation");
    }
  } else if (procedureCodeVal == 4) // S1 Handover Cancel Ack
  {
    ret = nbPrcS1HoCancelAck(ueCb, pdu);
    if (ret != ROK) {
      NB_LOG_ERROR(&nbCb, "Failed to handle S1 handover Cancel Ack");
    }
  } else if (procedureCodeVal == 25) // MME Status Transfer
  {
    ret = nbPrcMmeStatusTrnsfr(ueCb, pdu);
    if (ret != ROK) {
      NB_LOG_ERROR(&nbCb, "Failed to handle MME Status Transfer");
    }
  }
#endif
  else {
    NB_LOG_ERROR(&nbCb, "Procedure not handled: %u", procedureCodeVal);
    ret = RFAILED;
  }

  cmFreeMem((Ptr *)(pdu));

  RETVALUE(ret);
}

PUBLIC S16 nbPrcS1apRelInd
(
 SztRelInd   *relInd
)
{
   U32 ueIdx = 0;
   S16 retVal = ROK;
   U8 msgType = NB_S1_REL_IND;
   NbUeCb *ueCb = NULLP;

   ueIdx  = relInd->suConnId.val & 0xffff;
#if 0
   ueCb  = nbCb.ueCbLst[ueIdx];
#endif
   if ( ROK != (cmHashListFind(&(nbCb.ueCbLst), (U8 *)&(ueIdx),
      sizeof(U32),0,(PTR *)&ueCb)))
   {
      RETVALUE(RFAILED);
   }
   ueCb->s1ConCb->spConnId = relInd->spConnId;
   retVal = nbPrcIncS1apMsg(ueCb, relInd->pdu, msgType);

   RETVALUE(retVal);
}

PUBLIC S16 nbPrcS1apConCfm
(
 SztConCfm   *conCfm
)
{
   U32 ueIdx = 0;
   S16 retVal = ROK;
   U8 msgType = NB_S1_CON_CFM;
   NbUeCb *ueCb = NULLP;

   ueIdx  = conCfm->suConnId & 0xffff;
#if 0
   ueCb  = nbCb.ueCbLst[ueIdx];
#endif
   if ( ROK != (cmHashListFind(&(nbCb.ueCbLst), (U8 *)&(ueIdx),
      sizeof(U32),0,(PTR *)&ueCb)))
   {
      RETVALUE(RFAILED);
   }
   ueCb->s1ConCb->spConnId = conCfm->spConnId;
   retVal = nbPrcIncS1apMsg(ueCb, conCfm->pdu, msgType);

   RETVALUE(retVal);
}

PUBLIC S16 nbPrcS1DatInd
(
 SztDatEvntInd   *s1DatInd
)
{
   U32 ueIdx = 0;
   S16 retVal = ROK;
   U8 msgType = NB_S1_DAT_IND;
   NbUeCb *ueCb = NULLP;

   ueIdx = s1DatInd->suConnId & 0xffff;
#if 0
   ueCb =  nbCb.ueCbLst[ueIdx];
#endif
   if ( ROK != (cmHashListFind(&(nbCb.ueCbLst), (U8 *)&(ueIdx),
      sizeof(U32),0,(PTR *)&ueCb)))
   {
      RETVALUE(RFAILED);
   }
   retVal = nbPrcIncS1apMsg(ueCb, s1DatInd->pdu, msgType);

   RETVALUE(retVal);
}

PUBLIC S16 sendNonDelFlag(NbUeCb *ueCb, SztNAS_PDU *pdu, NbUeMsgCause *cause)
{
   NbS1ConCb                 *s1apCon = ueCb->s1ConCb;
   S1apPdu                   *nasNonDel = NULLP;
   SztInitiatingMsg          *initMsg;
   SztNASNonDlvryInd          *nasNonDlvryInd;
   U32                       ieIdx = 0;
   SztProtIE_Field_NASNonDlvryInd_IEs *ie = NULLP;
   SztDatEvntReq s1NasNonDel = {0}; /*S1apPdu *pdu = NULLP;*/

   NB_SET_ZERO(&s1NasNonDel, sizeof(SztDatEvntReq));
   s1NasNonDel.spConnId = s1apCon->spConnId;
      /* Initialize memory control point */
   if (cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &nbCb.mem,
            (Ptr *)&nasNonDel) != ROK)
   {
      NB_LOG_ERROR(&nbCb, "Failed to allocate memory. cmAllocEvnt failed");
      RETVALUE(RFAILED);
   }

   nbFillTknU8(&(nasNonDel->pdu.choice), S1AP_PDU_INITIATINGMSG);
   initMsg = &nasNonDel->pdu.val.initiatingMsg;
   nbFillTknU8(&(initMsg->pres), PRSNT_NODEF);
   nbFillTknU32(&(initMsg->criticality), SztCriticalityignoreEnum);
   nbFillTknU32(&(initMsg->procedureCode), Sztid_NASNonDlvryInd);
   nasNonDlvryInd = &(initMsg->value.u.sztNASNonDlvryInd);
   nbFillTknU8(&(nasNonDlvryInd->pres), PRSNT_NODEF);

   /* Allocate memory for 4 IEs */
   if ((cmGetMem(nasNonDel, 4 * sizeof(SztProtIE_Field_NASNonDlvryInd_IEs),
               (Ptr*)&nasNonDlvryInd->protocolIEs.member)) !=ROK)
   {
      NB_LOG_ERROR(&nbCb, "Failed to allocate memory. cmGetMem failed");
      RETVALUE(RFAILED);
   }

   /* IE1 - Filling MME ID */
   ie = &nasNonDlvryInd->protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
   nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   nbFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), s1apCon->mme_ue_s1ap_id);
   ieIdx++;

   /* IE2 - Filling enb s1ap id */
   ie = &nasNonDlvryInd->protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
   nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   nbFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), s1apCon->enb_ue_s1ap_id);
   ieIdx++;

   /* IE3 - Filling nas pdu */
   ie = &nasNonDlvryInd->protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_NAS_PDU);
   nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   nbFillTknStrOSXL(&(ie->value.u.sztNAS_PDU), pdu->len, pdu->val,
         &(nasNonDel->memCp));
   ieIdx++;

   /* IE4 - Filling  Cause */
   ie = &nasNonDlvryInd->protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_Cause);
   nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   nbS1apFillCause(&ie->value.u.sztCause, cause);
   ieIdx++;

   nbFillTknU16(&(nasNonDlvryInd->protocolIEs.noComp), ieIdx);
   s1NasNonDel.pdu = nasNonDel;
   /* Dispatch the message using S1 interface to the selected MME         */
   if (ROK != NbIfmS1apDatReq(&s1NasNonDel))
   {
      NB_LOG_ERROR(&nbCb,"NbIfmS1apDatReq failed");
      NB_FREE(pdu->val, pdu->len);
      NB_FREE(pdu, sizeof(SztNAS_PDU));
      RETVALUE(RFAILED);
   }
#if 0
   NB_FREE(pdu->val, pdu->len);
   NB_FREE(pdu, sizeof(SztNAS_PDU));
#endif
   RETVALUE(ROK);


}
PUBLIC S16 sendInitCtxtSetupFailRsp(NbUeCb *ueCb, NbUeMsgCause *cause)
{
   SztProtIE_Field_InitCntxtSetupFailIEs            *ie;
   SztInitCntxtSetupFail                            *initCtxtSetupFail;
   S1apPdu                                          *initCtxtSetupFailPdu = NULLP;
   SztDatEvntReq                                    datEvt;

   U16                                              numComp;
   U16                                              crntIe = 0;
   NbS1ConCb                                        *s1ConCb = ueCb->s1ConCb;
   SztUnsuccessfulOutcome                           *unsuccOut;

   NB_ALLOCEVNT(&initCtxtSetupFailPdu, sizeof(S1apPdu));
   if (initCtxtSetupFailPdu == NULLP)
   {
      NB_LOG_ERROR(&nbCb, "Failed to allocate memory for s1apPdu ");
      RETVALUE(RFAILED);
   }
   nbFillTknU8(&(initCtxtSetupFailPdu->pdu.choice), SZT_TRGR_UNSUCCESS_OUTCOME);
   unsuccOut = &(initCtxtSetupFailPdu->pdu.val.unsuccessfulOutcome);
   nbFillTknU8(&(unsuccOut->pres), PRSNT_NODEF);
   nbFillTknU32(&(unsuccOut->procedureCode), Sztid_InitCntxtSetup);
   nbFillTknU32(&(unsuccOut->criticality), SztCriticalityrejectEnum);

   numComp = 4;
   initCtxtSetupFail = &unsuccOut->value.u.sztInitCntxtSetupFail;
   nbFillTknU8(&(initCtxtSetupFail->pres), PRSNT_NODEF);

   if ((cmGetMem(initCtxtSetupFailPdu,
               (numComp * sizeof(SztProtIE_Field_InitCntxtSetupFailIEs)),
               (Ptr *)&initCtxtSetupFail->protocolIEs.member)) != ROK)
   {
      NB_LOG_ERROR(&nbCb, "Failed to allocate memory for components.");
      cmFreeMem(initCtxtSetupFailPdu);
      RETVALUE(RFAILED);
   }

   /* Filling MME UE ID */
   ie = &initCtxtSetupFail->protocolIEs.member[crntIe++];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
   nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   nbFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), s1ConCb->mme_ue_s1ap_id);


   /* Filling ENB UE ID */
   ie = &initCtxtSetupFail->protocolIEs.member[crntIe++];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
   nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   nbFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), s1ConCb->enb_ue_s1ap_id);

   /* IE4 - Filling  Cause */
   ie = &initCtxtSetupFail->protocolIEs.member[crntIe++];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_Cause);
   nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   nbS1apFillCause(&ie->value.u.sztCause, cause);

   nbFillTknU16(&(initCtxtSetupFail->protocolIEs.noComp), crntIe);

   /* populate the event structure */
   datEvt.spConnId = s1ConCb->spConnId;
   datEvt.pdu      = initCtxtSetupFailPdu;
   /* Multi eNB support */
#ifdef MULTI_ENB_SUPPORT
   datEvt.enbId    = ueCb->enbId;
#endif

   if (ROK != NbIfmS1apDatReq(&datEvt))
   {
      NB_LOG_ERROR(&nbCb,"NbIfmS1apDatReq failed");
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}
PUBLIC S16 nbProcessDlNasMsg(NbUeCb *ueCb, S1apPdu *pdu, U8 msgType)
{
   SztDlnkNASTport      *dlNas = NULLP;
   SztInitiatingMsg     *initMsg = NULLP;
   SztNAS_PDU           *nasPdu = NULLP;
   U32                  idx = 0;
   TknU8                *mmeIdTkn = NULLP;
   TknU8                *enbIdTkn = NULLP;
   SztProtIE_Field_DlnkNASTport_IEs *ie = NULLP;
   NbUeMsgCause         cause;

   /* Update S1AP Con Cb */
   if(msgType == NB_S1_CON_CFM)
   {
      nbSzGetIE(&pdu->pdu, Sztid_MME_UE_S1AP_ID, &mmeIdTkn);
      nbSzGetIE(&pdu->pdu, Sztid_eNB_UE_S1AP_ID, &enbIdTkn);

      if (enbIdTkn == NULLP || mmeIdTkn == NULLP)
      {
         NB_LOG_ERROR(&nbCb, "nbSzGetIE failed");
         RETVALUE(RFAILED);
      }

      ueCb->s1ConCb->mme_ue_s1ap_id = ((TknU32 *)mmeIdTkn)->val;
      ueCb->s1ConCb->enb_ue_s1ap_id = ((TknU32 *)enbIdTkn)->val;
      ueCb->s1ConCb->s1apConnState = NB_S1AP_CONNECTED;

   }
   initMsg = &pdu->pdu.val.initiatingMsg;
   dlNas   = &initMsg->value.u.sztDlnkNASTport;
   ie      = dlNas->protocolIEs.member;

   ie = dlNas->protocolIEs.member;
   for(idx = 0; idx < dlNas->protocolIEs.noComp.val; idx++)
   {
      if (ie->id.val == Sztid_NAS_PDU)
      {
         nasPdu = &ie->value.u.sztNAS_PDU;
         break;
      }
      ie = ie + 1;
   }

   if (nasPdu == NULLP)
   {
      NB_LOG_ERROR(&nbCb, "Missing NAS PDU in DL NAS TRANSFER");
      RETVALUE(ROK);
   }
   if(nbCb.nasNonDel[(ueCb->ueId) - 1].flag == 1)
   {
      cause.causeTyp = nbCb.nasNonDel[(ueCb->ueId) - 1].causeType;
      cause.causeVal = nbCb.nasNonDel[(ueCb->ueId) - 1].causeVal;
      if(ROK == sendNonDelFlag(ueCb, nasPdu, &cause))
      {
         /*not sending NAS_NON_DEL_IND to Tfw as per Anoop comment */
         /*nbUiBuildAndSendNasNonDlvryIndToTfw(ueCb->ueId);*/
         NB_LOG_DEBUG(&nbCb,"Sending NAS Non Delivery to MME Successful");
      }
      else
      {
         NB_LOG_DEBUG(&nbCb,"Sending NAS Non Delivery to MME FAILED");
      }
   }
   else
   {
      nbUiBuildAndSendDlNasMsg(ueCb, nasPdu);
   }

   RETVALUE(ROK);
}

PUBLIC S16 nbGetErabInfoFrmErabSetup(NbUeCb *ueCb,
                                     SztE_RABToBeSetupLstBrSUReq *s1ErabLst,
                                     NbErabLst **erabInfo,
                                     NbFailedErabLst **failedErabInfo) {
  U32 addrMask = 0;
  U8 rbIdx = 0;
  U8 failedRbIdx = 0;
  U8 shiftBits = 0;
  U8 indx = 0;
  U8 idx = 0;
  SztGTP_TEID *remTeIdStr = NULLP;
  SztE_RABToBeSetupItemBrSUReq *erabItem = NULLP;
  NbUeTunInfo *tunInfo;
#define MAX_QCI_VAL 9
#define MIN_QCI_VAL 1

  U8 numErabs = 0;
  numErabs = s1ErabLst->noComp.val;

  NB_ALLOC(erabInfo, sizeof(NbErabLst));
  if (erabInfo == NULLP) {
    NB_LOG_ERROR(&nbCb, "MEMORY ALLOCATION FAILED");
    RETVALUE(RFAILED);
  }
  NB_ALLOC(&(*erabInfo)->erabs, (numErabs * sizeof(NbErabCb)));
  if ((*erabInfo)->erabs == NULLP) {
    NB_LOG_ERROR(&nbCb, "MEMORY ALLOCATION FAILED");
    NB_FREE(*erabInfo, sizeof(NbErabLst));
    RETVALUE(RFAILED);
  }

  NB_ALLOC(failedErabInfo, sizeof(NbFailedErabLst));
  if (failedErabInfo == NULLP) {
    NB_LOG_ERROR(&nbCb, "MEMORY ALLOCATION FAILED");
    RETVALUE(RFAILED);
  }
  NB_ALLOC(&(*failedErabInfo)->failedErabs, (numErabs * sizeof(NbFailedErab)));
  if ((*failedErabInfo)->failedErabs == NULLP) {
    NB_LOG_ERROR(&nbCb, "MEMORY ALLOCATION FAILED");
    NB_FREE(*failedErabInfo, sizeof(NbFailedErabLst));
    RETVALUE(RFAILED);
  }
  for (idx = 0; idx < numErabs; idx++) {
    erabItem = &s1ErabLst->member[idx].value.u.sztE_RABToBeSetupItemBrSUReq;
    /* Store the remote tunnel information */
    /* Retrieve the remote S-GW's EGTP-U tunnel Id */

    if (erabItem->e_RABlevelQoSParams.qCI.pres &&
        (erabItem->e_RABlevelQoSParams.qCI.val < MIN_QCI_VAL ||
         erabItem->e_RABlevelQoSParams.qCI.val > MAX_QCI_VAL)) {
      NB_LOG_ERROR(&nbCb, "Received invalid qci:%d for bearer_id:%u \n",
                   erabItem->e_RABlevelQoSParams.qCI.val,
                   erabItem->e_RAB_ID.val);
      (*failedErabInfo)->noOfComp += 1;
      (*failedErabInfo)->failedErabs[failedRbIdx].qci =
          erabItem->e_RABlevelQoSParams.qCI.val;
      (*failedErabInfo)->failedErabs[failedRbIdx].erabId =
          erabItem->e_RAB_ID.val;
      (*failedErabInfo)->failedErabs[failedRbIdx].cause.causeTyp =
          NB_CAUSE_RADIONW;
      (*failedErabInfo)->failedErabs[failedRbIdx].cause.causeVal =
          CAUSE_RADIONW_QCI_UNSUPPORTED;
      failedRbIdx += 1;
      continue;
    }
    remTeIdStr = &(erabItem->gTP_TEID);
    shiftBits = (remTeIdStr->len);
    addrMask = 0xFF000000;
    NB_ALLOC(&(tunInfo), (sizeof(NbUeTunInfo)));

    for (indx = 0; indx < remTeIdStr->len; indx++) {
      shiftBits--;
      tunInfo->remTeId |=
          ((U32)(remTeIdStr->val[indx] << (8 * shiftBits)) & addrMask);
      addrMask = addrMask >> 8;
    }
    tunInfo->bearerId = erabItem->e_RAB_ID.val;
    /* assinging received ueid as lclTeid */
#ifdef MULTI_ENB_SUPPORT
      tunInfo->lclTeId = nbGetUeLclTeid(ueCb->ueId,
            erabItem->e_RAB_ID.val,ueCb->enbId);
#else
      tunInfo->lclTeId = nbGetUeLclTeid(ueCb->ueId,
            erabItem->e_RAB_ID.val);
#endif
      /* store the SGW IP Address */
      switch(erabItem->transportLyrAddr.len)
      {
         case 32:
            {
               tunInfo->sgwAddr.type = CM_TPTADDR_IPV4;
               tunInfo->sgwAddr.u.ipv4TptAddr.port = NB_DFLT_EGTP_PORT;

               /* copy 4bytes into the U32 */
               shiftBits = erabItem->transportLyrAddr.len / 8;
               addrMask = 0xFF000000;
               for(indx = 0; indx < 4; indx++)
               {
                  shiftBits--;
                  tunInfo->sgwAddr.u.ipv4TptAddr.address |=
                     ((U32)(erabItem->transportLyrAddr.val[indx]
                        << (8 * shiftBits)) & addrMask);
                  addrMask = addrMask >> 8;
               }
               break;
            }
         case 128:
            {
               tunInfo->sgwAddr.type = CM_TPTADDR_IPV6;
               tunInfo->sgwAddr.u.ipv6TptAddr.\
                  port = NB_DFLT_EGTP_PORT;
               for (indx = 0; indx < 16; indx++)
               {
                  tunInfo->sgwAddr.u.ipv6TptAddr.\
                     ipv6NetAddr[indx] = erabItem->transportLyrAddr.val[indx];
               }
               break;
            }
         default:
            {
               /* This means both IPv4 and IPv6 addresses are present. We are */
               /* yet to support this option                                  */
               // TODO: Add ipv4v6 support. For now, copy ipv4 addr only
               tunInfo->sgwAddr.type = CM_TPTADDR_IPV4;
               tunInfo->sgwAddr.u.ipv4TptAddr.port = NB_DFLT_EGTP_PORT;

               // copy 4bytes into the U32
               shiftBits = erabItem->transportLyrAddr.len / 8;
               addrMask = 0xFF000000;
               for(indx = 0; indx < 4; indx++)
               {
                  shiftBits--;
                  tunInfo->sgwAddr.u.ipv4TptAddr.address |=
                     ((U32)(erabItem->transportLyrAddr.val[indx]
                        << (8 * shiftBits)) & addrMask);
                  addrMask = addrMask >> 8;
               }

               break;
            }
      }
      if (ROK != cmHashListInsert(&(ueCb->tunnInfo), (PTR)tunInfo,
                                  (U8 *)&tunInfo->bearerId, sizeof(U32))) {
        NB_FREE(tunInfo, sizeof(NbUeTunInfo))
        NB_LOG_ERROR(&nbCb, "Failed to Insert tunnel info ");
        RETVALUE(RFAILED);
      }
      /* store the NAS PDU */
      if(erabItem->nAS_PDU.pres == PRSNT_NODEF)
      {
         (*erabInfo)->erabs[rbIdx].nasPdu = &(erabItem->nAS_PDU);
      }
      else
      {
         (*erabInfo)->erabs[rbIdx].nasPdu = NULLP;
      }
      (*erabInfo)->erabs[rbIdx].erabId = tunInfo->bearerId;
      (*erabInfo)->erabs[rbIdx].remTeid =tunInfo->remTeId;
      (*erabInfo)->erabs[rbIdx].lclTeid =tunInfo->lclTeId;
      rbIdx++;
      tunInfo = NULLP;
  }
   (*erabInfo)->noOfComp = rbIdx;

   RETVALUE(ROK);
}

PUBLIC S16 nbGetErabInfoFrmIntCnxt
(
 NbUeCb                            *ueCb,
 SztE_RABToBeSetupLstCtxtSUReq     *s1ErabLst,
 NbErabLst                         **erabInfo
)
{
   U32                            addrMask = 0;
   U8                             rbIdx = 0;
   U8                             shiftBits = 0;
   U8                             indx = 0;
   U8                             idx = 0;
   SztGTP_TEID                    *remTeIdStr = NULLP;
   SztE_RABToBeSetupItemCtxtSUReq *erabItem = NULLP;
   NbUeTunInfo                    *tunInfo = NULLP;

   U8   numErabs = 0;
   numErabs      = s1ErabLst->noComp.val;

   NB_ALLOC(erabInfo, sizeof(NbErabLst));
   if(erabInfo == NULLP)
   {
      NB_LOG_ERROR(&nbCb, "MEMORY ALLOCATION FAILED");
      RETVALUE(RFAILED);
   }

   NB_ALLOC(&(*erabInfo)->erabs, (numErabs * sizeof(NbErabCb)));
   if((*erabInfo)->erabs == NULLP)
   {
      NB_LOG_ERROR(&nbCb, "MEMORY ALLOCATION FAILED");
      NB_FREE(*erabInfo, sizeof(NbErabLst));
      RETVALUE(RFAILED);
   }

   ueCb->tunnIdx = 0;
   for(idx = 0; idx < numErabs; idx++)
   {
      erabItem = &s1ErabLst->member[idx].value.u.sztE_RABToBeSetupItemCtxtSUReq;

      /* Store the remote tunnel information */
      /* Retrieve the remote S-GW's EGTP-U tunnel Id */
      remTeIdStr = &(erabItem->gTP_TEID);
      shiftBits = (remTeIdStr->len);
      addrMask = 0xFF000000;
      NB_ALLOC(&(tunInfo),(sizeof(NbUeTunInfo)));
      for(indx = 0;indx < remTeIdStr->len; indx++)
      {
         shiftBits--;
         tunInfo->remTeId |=
            ((U32)(remTeIdStr->val[indx] << (8*shiftBits)) & addrMask);
         addrMask = addrMask >> 8;
      }
      tunInfo->bearerId = erabItem->e_RAB_ID.val;
      /* assinging received ueid as lclTeid */
#ifdef MULTI_ENB_SUPPORT
      tunInfo->lclTeId = nbGetUeLclTeid(ueCb->ueId,
            erabItem->e_RAB_ID.val,ueCb->enbId);
#else
      tunInfo->lclTeId = nbGetUeLclTeid(ueCb->ueId,
            erabItem->e_RAB_ID.val);
#endif
      /* store the SGW IP Address */
      switch(erabItem->transportLyrAddr.len)
      {
         case 32:
            {
               tunInfo->sgwAddr.type = CM_TPTADDR_IPV4;
               tunInfo->sgwAddr.u.ipv4TptAddr.\
                  port = NB_DFLT_EGTP_PORT;

               /* copy 4bytes into the U32 */
               shiftBits = erabItem->transportLyrAddr.len / 8;
               addrMask = 0xFF000000;
               for(indx = 0; indx < 4; indx++)
               {
                  shiftBits--;
                  tunInfo->sgwAddr.u.ipv4TptAddr.address |=
                     ((U32)(erabItem->transportLyrAddr.val[indx]
                        << (8 * shiftBits)) & addrMask);
                  addrMask = addrMask >> 8;
               }
               break;
            }
         case 128:
            {
               tunInfo->sgwAddr.type = CM_TPTADDR_IPV6;
               tunInfo->sgwAddr.u.ipv6TptAddr.\
                  port = NB_DFLT_EGTP_PORT;
               for (indx = 0; indx < 16; indx++)
               {
                  tunInfo->sgwAddr.u.ipv6TptAddr.\
                     ipv6NetAddr[indx] = erabItem->transportLyrAddr.val[indx];
               }
               break;
            }
         default: {
               /* This means both IPv4 and IPv6 addresses are present. We are */
               /* yet to support this option                                  */
              // TODO: Add ipv4v6 support. For now, copy ipv4 addr only
              tunInfo->sgwAddr.type = CM_TPTADDR_IPV4;
              tunInfo->sgwAddr.u.ipv4TptAddr.\
                 port = NB_DFLT_EGTP_PORT;

              // copy 4bytes into the U32
              shiftBits = erabItem->transportLyrAddr.len / 8;
              addrMask = 0xFF000000;
              for(indx = 0; indx < 4; indx++) {
                shiftBits--;
                tunInfo->sgwAddr.u.ipv4TptAddr.address |=
                   ((U32)(erabItem->transportLyrAddr.val[indx]
                      << (8 * shiftBits)) & addrMask);
                addrMask = addrMask >> 8;
              }
             break;
           }
      }
      if (ROK != cmHashListInsert(&(ueCb->tunnInfo),(PTR)tunInfo,
               (U8 *) &tunInfo->bearerId,sizeof(U32)))
      {
         NB_LOG_ERROR(&nbCb, "Failed to Insert tunnel info");
         /*NB_FREE(tunInfo, sizeof(NbUeTunInfo))
         RETVALUE(RFAILED);*/
      }
      /* store the NAS PDU */
      if(erabItem->nAS_PDU.pres == PRSNT_NODEF)
      {
         (*erabInfo)->erabs[rbIdx].nasPdu = &(erabItem->nAS_PDU);
      }
      else
      {
         (*erabInfo)->erabs[rbIdx].nasPdu = NULLP;
      }
      (*erabInfo)->erabs[rbIdx].erabId =  tunInfo->bearerId;
      (*erabInfo)->erabs[rbIdx].remTeid = tunInfo->remTeId;
      (*erabInfo)->erabs[rbIdx].lclTeid = tunInfo->lclTeId;
      ueCb->tunnIdx++;
      rbIdx++;
   }
   (*erabInfo)->noOfComp = numErabs;
   RETVALUE(ROK);
}

PRIVATE S16 nbFillS1apRabSetupRsp(NbUeCb *ueCb, NbErabLst *erabInfo,
                                  S1apPdu **s1apPdu,
                                  NbFailedErabLst *failedErabInfo) {
  NbErabCb *rab;
  S1apPdu *szERABRspPdu = NULLP;
  SztSuccessfulOutcome *succOut;
  SztE_RABSetupResp *rabSetupRsp;
  S16 ret = ROK;
  NbS1ConCb *s1apCon;
  U16 idx;
  U16 crntIe = 0;
  U8 numRabsAllowed = 0;
  SztProtIE_Field_E_RABSetupRespIEs *ie = NULLP;
  SztProtIE_SingleCont_E_RABSetupItemBrSUResIEs *rspMember = NULLP;
  U8 cnt = 0;
  U8 len = 0;
  U8 noComp = 0;
  U8 ieIdx;
  U8 offSet;

  NB_LOG_DEBUG(&nbCb, "Filling E-RAB Setup Response");
  numRabsAllowed = erabInfo->noOfComp;

  noComp = 2;
  if (erabInfo->noOfComp > 0) {
    ++noComp;
  }
  if ((failedErabInfo) && (failedErabInfo->noOfComp > 0)) {
    ++noComp;
  }
  s1apCon = ueCb->s1ConCb;
  if (cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &nbCb.mem,
                  (Ptr *)&szERABRspPdu) != ROK) {
    NB_LOG_ERROR(&nbCb, "Failed to allocate memory for s1apPdu.");
    RETVALUE(RFAILED);
  }

  nbFillTknU8(&(szERABRspPdu->pdu.choice), SZT_TRGR_SUCCESS_OUTCOME);
  succOut = &(szERABRspPdu->pdu.val.successfulOutcome);
  nbFillTknU8(&(succOut->pres), PRSNT_NODEF);
  nbFillTknU32(&(succOut->procedureCode), Sztid_E_RABSetup);
  nbFillTknU32(&(succOut->criticality), SztCriticalityrejectEnum);
  rabSetupRsp = &(succOut->value.u.sztE_RABSetupResp);
  nbFillTknU8(&(rabSetupRsp->pres), PRSNT_NODEF);

  /*List of IEs Filled
   * 1. UE ENB S1AP Id
   * 2. UE MME S1AP Id
   * 3. E-RAB Setup List
   * 4. E-RAB failed to Setup List
   * */
  if (cmGetMem(szERABRspPdu,
               (noComp * sizeof(SztProtIE_Field_E_RABSetupRespIEs)),
               (Ptr *)&rabSetupRsp->protocolIEs.member) != ROK) {
    NB_LOG_ERROR(&nbCb, "Failed to allocate memory. cmGetMem failed.");
    RETVALUE(RFAILED);
  }

  /* Filling MME ID */
  ie = &rabSetupRsp->protocolIEs.member[crntIe++];
  nbFillTknU8(&(ie->pres), PRSNT_NODEF);
  nbFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
  nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
  nbFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), s1apCon->mme_ue_s1ap_id);

  /* Filling ENB ID */
  ie = &rabSetupRsp->protocolIEs.member[crntIe++];
  nbFillTknU8(&(ie->pres), PRSNT_NODEF);
  nbFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
  nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
  nbFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), s1apCon->enb_ue_s1ap_id);

  if (numRabsAllowed > 0) {
    /* ERAB Setup List  */
    ie = &rabSetupRsp->protocolIEs.member[crntIe++];
    nbFillTknU8(&(ie->pres), PRSNT_NODEF);
    nbFillTknU32(&(ie->id), Sztid_E_RABSetupLstBrSURes);
    nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
    if ((cmGetMem(szERABRspPdu,
                  (numRabsAllowed *
                   sizeof(SztProtIE_SingleCont_E_RABSetupItemBrSUResIEs)),
                  (Ptr *)&ie->value.u.sztE_RABSetupLstBrSURes.member)) != ROK) {
      NB_LOG_ERROR(&nbCb, "Failed to allocate memory. cmGetMem failed");
      RETVALUE(RFAILED);
    }

    /* Locate ERAB to be setup List IE  */
    ieIdx = 0;
    for (idx = 0; idx < erabInfo->noOfComp; idx++) {
      SztE_RABSetupItemBrSURes *rabIE;

      rspMember = &(ie->value.u.sztE_RABSetupLstBrSURes.member[ieIdx++]);
      nbFillTknU8(&(rspMember->pres), PRSNT_NODEF);
      nbFillTknU32(&(rspMember->id), Sztid_E_RABSetupItemBrSURes);
      nbFillTknU32(&(rspMember->criticality), SztCriticalityignoreEnum);
      rab = &(erabInfo->erabs[idx]);
      rabIE = &(rspMember->value.u.sztE_RABSetupItemBrSURes);
      nbFillTknU8(&(rabIE->pres), PRSNT_NODEF);
      nbFillTknU32(&rabIE->e_RAB_ID, rab->erabId);
#if 1
         if (nbCb.datAppAddr.type == CM_TPTADDR_IPV4)
#endif
         {
            len = 4;
            rabIE->transportLyrAddr.pres = PRSNT_NODEF;
            rabIE->transportLyrAddr.len = (U16)(len * 8);
            NB_GET_MEM(szERABRspPdu, len, &rabIE->transportLyrAddr.val);
            for (cnt = 0; cnt < len; cnt++)
            {
#if 1
               offSet =(U8)((len - (cnt + 1)) * 8);
               rabIE->transportLyrAddr.val[cnt] =
                  (U8)(nbCb.datAppAddr.u.ipv4TptAddr.address >> offSet);
#endif
            }
         }

         nbFillTknStrOSXL1(&rabIE->gTP_TEID, 4, rab->lclTeid, &(szERABRspPdu->memCp));
         rabIE->iE_Extns.noComp.pres = NOTPRSNT;
         if (ieIdx >= numRabsAllowed)
         {
            break;
         }
      }
      nbFillTknU16(&(ie->value.u.sztE_RABSetupLstBrSURes.noComp), ieIdx);
   }
   if (failedErabInfo) {
     NB_LOG_ERROR(&nbCb, "failedErabInfo->noOfComp :%d \n",
                failedErabInfo->noOfComp);
     if (failedErabInfo->noOfComp > 0) {
       SztProtIE_SingleCont_E_RABItemIEs *failedErabItem;
       NbFailedErab failedRab = {0};
       // E-RAB failed to Setup List
       ie = &rabSetupRsp->protocolIEs.member[crntIe++];
       nbFillTknU8(&(ie->pres), PRSNT_NODEF);
       nbFillTknU32(&(ie->id), Sztid_E_RABFailedToSetupLstBrSURes);
       nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
       if ((cmGetMem(szERABRspPdu,
                   ((failedErabInfo->noOfComp) *
                    sizeof(SztProtIE_SingleCont_E_RABItemIEs)),
                   (Ptr *)&ie->value.u.sztE_RABLst.member)) != ROK) {
         NB_LOG_ERROR(&nbCb, "Failed to allocate memory. cmGetMem failed");
         RETVALUE(RFAILED);
       }

       ieIdx = 0;
       for (idx = 0; idx < failedErabInfo->noOfComp; idx++) {
         SztE_RABItem *rabIE;
         failedErabItem = &(ie->value.u.sztE_RABLst.member[ieIdx++]);
         nbFillTknU8(&(failedErabItem->pres), PRSNT_NODEF);
         nbFillTknU32(&(failedErabItem->id), Sztid_E_RABItem);
         nbFillTknU32(&(failedErabItem->criticality), SztCriticalityignoreEnum);
         failedRab = failedErabInfo->failedErabs[idx];
         rabIE = &(failedErabItem->value.u.sztE_RABItem);
         nbFillTknU8(&(rabIE->pres), PRSNT_NODEF);
         nbFillTknU32(&(rabIE->e_RAB_ID), failedRab.erabId);
         nbS1apFillCause(&(rabIE->cause), &failedRab.cause);
       }
       nbFillTknU16(&(ie->value.u.sztE_RABLst.noComp), failedErabInfo->noOfComp);
     }
   }
   nbFillTknU16(&(rabSetupRsp->protocolIEs.noComp), crntIe);

   *s1apPdu = szERABRspPdu;
   RETVALUE(ret);
}

PRIVATE S16 nbRabSetupSndS1apRsp(NbUeCb *ueCb, NbErabLst *erabInfo,
                                 NbFailedErabLst *failedErabInfo) {
  S1apPdu *s1apPdu = NULLP;
  S16 ret = ROK;

  ret = nbFillS1apRabSetupRsp(ueCb, erabInfo, &s1apPdu, failedErabInfo);
  if (ret != ROK) {
    RETVALUE(RFAILED);
  }
#ifdef MULTI_ENB_SUPPORT
   if (nbIfmS1apSndUeMsg(ueCb->s1ConCb->spConnId, s1apPdu, ueCb->enbId) != ROK)
#else
   if (nbIfmS1apSndUeMsg(ueCb->s1ConCb->spConnId, s1apPdu) != ROK)
#endif
   {
      RETVALUE(RFAILED);
   }
   RETVALUE(ret);
}

PUBLIC S16 nbBuildAndSendIntCtxtSetupRsp
(
 NbUeCb *ueCb,
 NbErabLst *erabInfo
)
{
   S1apPdu   *s1apPdu = NULLP;
   S16 ret = ROK;
   ret = nbBuildIntCtxtSetupRsp(ueCb, erabInfo, &s1apPdu);
   if(ret != ROK)
   {
      RETVALUE(RFAILED);
   }
#ifdef MULTI_ENB_SUPPORT
   if (nbIfmS1apSndUeMsg(ueCb->s1ConCb->spConnId, s1apPdu, ueCb->enbId) != ROK)
#else
   if (nbIfmS1apSndUeMsg(ueCb->s1ConCb->spConnId, s1apPdu) != ROK)
#endif
   {
      RETVALUE(RFAILED);
   }
   RETVALUE(ret);
}

PRIVATE S16 nbBuildIntCtxtSetupRsp(NbUeCb *ueCb, NbErabLst *erabInfo,
                                   S1apPdu **s1apPdu) {
  SztProtIE_SingleCont_E_RABSetupItemCtxtSUResIEs *ie1;
  SztProtIE_SingleCont_E_RABItemIEs *ie2;
  SztProtIE_Field_InitCntxtSetupRespIEs *ie;
  SztInitCntxtSetupResp *initCtxtRsp;
  S1apPdu *initCtxtRspPdu = NULLP;

  U16 idx;
  U16 idx1;
  U16 cnt;
  U8 offSet;
  U16 numComp;
  U32 len;
  U16 crntIe = 0;
  NbS1ConCb *s1ConCb = ueCb->s1ConCb;
  SztSuccessfulOutcome *succOut;
  U8 succIdx = 0;
  U8 failIdx = 0;
  U8 numSuccErabs = 0;

  NB_ALLOCEVNT(&initCtxtRspPdu, sizeof(S1apPdu));
  if (initCtxtRspPdu == NULLP) {
    NB_LOG_ERROR(&nbCb, "Failed to allocate memory for s1apPdu ");
    RETVALUE(RFAILED);
  }
  nbFillTknU8(&(initCtxtRspPdu->pdu.choice), SZT_TRGR_SUCCESS_OUTCOME);
  succOut = &(initCtxtRspPdu->pdu.val.successfulOutcome);
  nbFillTknU8(&(succOut->pres), PRSNT_NODEF);
  nbFillTknU32(&(succOut->procedureCode), Sztid_InitCntxtSetup);
  nbFillTknU32(&(succOut->criticality), SztCriticalityrejectEnum);

  numComp = 5;
  initCtxtRsp = &succOut->value.u.sztInitCntxtSetupResp;
  nbFillTknU8(&(initCtxtRsp->pres), PRSNT_NODEF);

  if ((cmGetMem(initCtxtRspPdu,
                (numComp * sizeof(SztProtIE_Field_InitCntxtSetupRespIEs)),
                (Ptr *)&initCtxtRsp->protocolIEs.member)) != ROK) {
    NB_LOG_ERROR(&nbCb, "Failed to allocate memory for components.");
    cmFreeMem(initCtxtRspPdu);
    RETVALUE(RFAILED);
  }

  /* Filling MME UE ID */
  ie = &initCtxtRsp->protocolIEs.member[crntIe++];
  nbFillTknU8(&(ie->pres), PRSNT_NODEF);
  nbFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
  nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
  nbFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), s1ConCb->mme_ue_s1ap_id);

  /* Filling ENB UE ID */
  ie = &initCtxtRsp->protocolIEs.member[crntIe++];
  nbFillTknU8(&(ie->pres), PRSNT_NODEF);
  nbFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
  nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
  nbFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), s1ConCb->enb_ue_s1ap_id);

  /* Filling ERAB Setup List */
  ie = &initCtxtRsp->protocolIEs.member[crntIe++];
  nbFillTknU8(&(ie->pres), PRSNT_NODEF);
  nbFillTknU32(&(ie->id), Sztid_E_RABSetupLstCtxtSURes);
  nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);

  numComp = erabInfo->noOfComp;

  U8 numFailedErabs =
      nbCb.initCtxtSetupFailedErabs[ueCb->ueId - 1].numFailedErabs;
  numSuccErabs = numComp - numFailedErabs;
  NB_LOG_DEBUG(&nbCb, "numSuccErabs %d\n", numSuccErabs);
  NB_LOG_DEBUG(&nbCb, "numFailedErabs %d\n", numFailedErabs);

  if (cmGetMem(initCtxtRspPdu,
               (numSuccErabs *
                sizeof(SztProtIE_SingleCont_E_RABSetupItemCtxtSUResIEs)),
               (Ptr *)&(ie->value.u.sztE_RABSetupLstCtxtSURes.member)) != ROK) {
    NB_LOG_ERROR(&nbCb, "Failed to allocate memory for RAB SETUP list.");
    cmFreeMem(initCtxtRspPdu);
    RETVALUE(RFAILED);
  }
  nbFillTknU16(&(ie->value.u.sztE_RABSetupLstCtxtSURes.noComp), numSuccErabs);
  /* fill the bearer details */
  U8 itr = 0;
  Bool found = FALSE;
  for (idx = 0; idx < numComp; idx++) {
    if (numFailedErabs > 0) {
      for (itr = 0; itr < numFailedErabs; itr++) {
        if (erabInfo->erabs[idx].erabId ==
            nbCb.initCtxtSetupFailedErabs[ueCb->ueId - 1].failedErabs[itr]) {
          found = TRUE;
          break;
        }
      }
      if (found) {
        found = FALSE;
        continue;
      }
    }
    SztE_RABSetupItemCtxtSURes *erabIe;
    NB_LOG_DEBUG(&nbCb, "Adding ebi %u to successfully setup list in ICS Rsp\n",
                 erabInfo->erabs[idx].erabId);
    ie1 = &(ie->value.u.sztE_RABSetupLstCtxtSURes.member[succIdx++]);
    erabIe = &(ie1->value.u.sztE_RABSetupItemCtxtSURes);
    nbFillTknU8(&(ie1->pres), PRSNT_NODEF);
    nbFillTknU32(&(ie1->id), Sztid_E_RABSetupItemCtxtSURes);
    nbFillTknU32(&(ie1->criticality), SztCriticalityignoreEnum);
    nbFillTknU8(&(erabIe->pres), PRSNT_NODEF);
    nbFillTknU32(&(erabIe->e_RAB_ID), erabInfo->erabs[idx].erabId);
    if (nbCb.datAppAddr.type == CM_TPTADDR_IPV4) {
      len = 4;
      erabIe->transportLyrAddr.pres = PRSNT_NODEF;
      erabIe->transportLyrAddr.len = (U16)(len * 8);
      NB_GET_MEM(initCtxtRspPdu, len, &erabIe->transportLyrAddr.val);
      for (cnt = 0; cnt < len; cnt++) {
        offSet = (U8)((len - (cnt + 1)) * 8);
        erabIe->transportLyrAddr.val[cnt] =
            (U8)(nbCb.datAppAddr.u.ipv4TptAddr.address >> offSet);
      }
    }
    len = 4;
    erabIe->gTP_TEID.len = (U16)len;
    erabIe->gTP_TEID.pres = PRSNT_NODEF;
    NB_GET_MEM(initCtxtRspPdu, len, &erabIe->gTP_TEID.val);
    for (cnt = 0; cnt < len; cnt++) {
      offSet = (U8)(len - (cnt + 1)) * 8;
      erabIe->gTP_TEID.val[cnt] = (U8)(erabInfo->erabs[idx].lclTeid >> offSet);
    }
    erabIe->iE_Extns.noComp.pres = NOTPRSNT;
  }
  if (numFailedErabs > 0) {
    /* Filling ERAB Failed List */
    ie = &initCtxtRsp->protocolIEs.member[crntIe++];
    nbFillTknU8(&(ie->pres), PRSNT_NODEF);
    nbFillTknU32(&(ie->id), Sztid_E_RABFailedToSetupLstCtxtSURes);
    nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
    if ((cmGetMem(
            initCtxtRspPdu,
            ((numFailedErabs) * sizeof(SztProtIE_SingleCont_E_RABItemIEs)),
            (Ptr *)&ie->value.u.sztE_RABLst.member)) != ROK) {
      NB_LOG_ERROR(&nbCb, "Failed to allocate memory. cmGetMem failed");
      RETVALUE(RFAILED);
    }

    nbFillTknU16(&(ie->value.u.sztE_RABLst.noComp), numFailedErabs);
    for (idx1 = 0; idx1 < numFailedErabs; idx1++) {
      NB_LOG_DEBUG(
          &nbCb, "Adding ebi %u to failed to setup list in ICS Rsp\n",
          nbCb.initCtxtSetupFailedErabs[ueCb->ueId - 1].failedErabs[idx1]);
      SztE_RABItem *failedErabItem;
      // E-RAB failed to Setup List
      ie2 = &(ie->value.u.sztE_RABLst.member[failIdx++]);
      nbFillTknU8(&(ie2->pres), PRSNT_NODEF);
      nbFillTknU32(&(ie2->id), Sztid_E_RABItem);
      nbFillTknU32(&(ie2->criticality), SztCriticalityignoreEnum);
      failedErabItem = &(ie2->value.u.sztE_RABItem);
      nbFillTknU8(&(failedErabItem->pres), PRSNT_NODEF);
      nbFillTknU32(
          &(failedErabItem->e_RAB_ID),
          nbCb.initCtxtSetupFailedErabs[ueCb->ueId - 1].failedErabs[idx1]);
      nbS1apFillCause(&(failedErabItem->cause),
                      &nbCb.initCtxtSetupFailedErabs[ueCb->ueId - 1].cause);
    }
  }

  nbFillTknU16(&(initCtxtRsp->protocolIEs.noComp), crntIe);
  *s1apPdu = initCtxtRspPdu;
  RETVALUE(ROK);
}

PUBLIC S16 nbHandleS1UeReleaseCmd(NbUeCb *ueCb, NbRelCause relCause) {
  S16 ret;

  if (nbCb.delayUeCtxtRelCmp[(ueCb->ueId) - 1].delayUeCtxRelComp != TRUE) {
    if (ueCb->s1HoInfo != NULLP &&
        ueCb->s1HoInfo->s1HoEvent == S1_HO_OVRALL_TMR_EXPIRY) {
      if (relCause.causeType == NB_CAUSE_RADIONW &&
          relCause.causeVal == SztCauseRadioNwsuccessful_handoverEnum) {
        NB_LOG_DEBUG(
            &nbCb, "UE context release cmd received after successful handover. "
                   "Sending UE context release indication to TFW");
        ret = nbUiSendUeCtxRelIndToUser(ueCb->ueId, relCause);
        RETVALUE(ret);
      }
    }

    /* send the release complete to mme */
    ret = nbCtxtRelSndRlsCmpl(ueCb);
#ifdef MULTI_ENB_SUPPORT
    if (ueCb->s1HoInfo != NULLP) {
      if (relCause.causeType == NB_CAUSE_RADIONW &&
          relCause.causeVal == SztCauseRadioNwsuccessful_handoverEnum) {
        // Stopping the S1 Reloc Overall Timer
        NB_LOG_DEBUG(&nbCb, "Stopping timer NB_TMR_S1_OVRL_TMR for UE Id: %u",
                     ueCb->ueId);
        nbStopTmr((PTR)ueCb, NB_TMR_S1_OVRL_TMR);

        NB_LOG_DEBUG(
            &nbCb, "UE context release cmd received after successful "
                   "S1 handover. Sending UE context release indication to TFW");
      } else {
        NB_LOG_DEBUG(
            &nbCb,
            "UE context release cmd received due to S1 overall reloc timer"
            " expiry. Sending UE context release indication to TFW");
      }
      ret = nbUiSendUeCtxRelIndToUser(ueCb->ueId, relCause);
    } else {
#endif
      ret = nbIfmDamUeDelReq(ueCb->ueId);
#ifdef MULTI_ENB_SUPPORT
    }
#endif
  } else {
    nbStartDelayTimerForUeCtxRel(ueCb->ueId);
  }
  RETVALUE(ret);
}

PUBLIC S16 nbCtxtRelSndRlsCmpl(NbUeCb *ueCb)
{
   S1apPdu                 *ctxtRelPdu;
   SztRelRsp               relRsp;
   nbS1apFillCtxtRelCmpl(ueCb->s1ConCb, &ctxtRelPdu);
   if(ctxtRelPdu == NULLP)
   {
      NB_LOG_ERROR(&nbCb, "Failed to build UE Context Release Message");
      RETVALUE(RFAILED);
   }
   relRsp.suConnId = ueCb->s1ConCb->suConnId;
   relRsp.spConnId = ueCb->s1ConCb->spConnId;
   relRsp.pdu      = ctxtRelPdu;
#ifdef MULTI_ENB_SUPPORT
   if (ueCb->s1HoInfo != NULLP) {
     relRsp.cntxtRelForS1Ho = TRUE;
     relRsp.enbId = ueCb->s1HoInfo->srcEnbId;
   } else {
     relRsp.cntxtRelForS1Ho = FALSE;
     relRsp.enbId = ueCb->enbId;
   }
#endif
   NbIfmS1apRelRsp(&relRsp);
   RETVALUE(ROK);
}

PUBLIC S16 nbS1apFillCtxtRelCmpl
(
 NbS1ConCb                    *s1Con,
 S1apPdu                      **pdu
)
{
   S1apPdu                   *szUeCxtRlsCmplPdu = NULLP;
   U16                       numComp;
   SztProtIE_Field_UECntxtRlsComplete_IEs *ie = NULLP;
   U16                       ieIdx = 0;
   SztSuccessfulOutcome      *succMsg;
   SztUECntxtRlsComplete     *ctxtRelComp;

   NB_LOG_DEBUG(&nbCb, "Constructing UE Context Release");

   if (cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &nbCb.mem,
            (Ptr *)&szUeCxtRlsCmplPdu) != ROK)
   {
      NB_LOG_ERROR(&nbCb, "Failed to allocate memory. cmAllocEvnt failed");
      RETVALUE(RFAILED);
   }

   nbFillTknU8(&(szUeCxtRlsCmplPdu->pdu.choice), SZT_TRGR_SUCCESS_OUTCOME);
   succMsg = &szUeCxtRlsCmplPdu->pdu.val.successfulOutcome;
   nbFillTknU8(&(succMsg->pres), PRSNT_NODEF);
   nbFillTknU32(&(succMsg->procedureCode), Sztid_UECntxtRls);
   nbFillTknU32(&(succMsg->criticality), SztCriticalityrejectEnum);

   /* Filling 2 mandatory headers */
   /*List of IEs Filled
    * 1. UE MME S1AP ID
    * 2. UE ENB S1AP ID*/
   numComp     = 2;
   ctxtRelComp = &succMsg->value.u.sztUECntxtRlsComplete;
   nbFillTknU8(&(ctxtRelComp->pres), PRSNT_NODEF);
   if ((cmGetMem(szUeCxtRlsCmplPdu,
               (numComp * sizeof(SztProtIE_Field_UECntxtRlsComplete_IEs)),
               (Ptr *)&ctxtRelComp->protocolIEs.member)) != ROK)
   {
      NB_LOG_ERROR(&nbCb, "Failed to allocate memory. cmGetMem failed");
      RETVALUE(RFAILED);
   }

   /* IE1 - Filling MME ID */
   ie = &ctxtRelComp->protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
   nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   nbFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), s1Con->mme_ue_s1ap_id);
   ieIdx++;

   /* IE2 - Filling ENB ID */
   ie = &ctxtRelComp->protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
   nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   nbFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), s1Con->enb_ue_s1ap_id);
   ieIdx++;

   nbFillTknU16(&(ctxtRelComp->protocolIEs.noComp), numComp);

   *pdu = szUeCxtRlsCmplPdu;

   RETVALUE(ROK);
} /* nbS1apFillCtxtRelCmpl */

#ifdef MULTI_ENB_SUPPORT
PRIVATE S16 nbS1apFillTAI
(
 NbUeCb      *ueCb,
 S1apPdu     *pdu,
 SztTAI      *taiIe,
 EnbCb       *enbCb
)
#else
PRIVATE S16 nbS1apFillTAI
(
 NbUeCb                     *ueCb,
 S1apPdu                      *pdu,
 SztTAI                       *taiIe
)
#endif
{
#ifndef MULTI_ENB_SUPPORT
   NbTai                     tai;

   if(nbGetTai(&tai) != ROK)
   {
      RETVALUE(RFAILED);
   }
#endif
   nbFillTknU8(&(taiIe->pres), PRSNT_NODEF);
#ifdef MULTI_ENB_SUPPORT
   if (nbSztFillPLMNId(pdu, &enbCb->plmnId, &(taiIe->pLMNidentity)) != ROK)
#else
   if (nbSztFillPLMNId(pdu, &tai.plmnId, &(taiIe->pLMNidentity)) != ROK)
#endif
   {
      RETVALUE(RFAILED);
   }
#ifdef MULTI_ENB_SUPPORT
   nbSztFillTAC(enbCb->tac, pdu, &(taiIe->tAC));
#else
   nbSztFillTAC(tai.tac, pdu, &(taiIe->tAC));
#endif
   RETVALUE(ROK);
} /* end of nbS1apFillTAI */

PUBLIC S16 nbGetTai
(
 NbTai *tai
)
{
   tai->plmnId = nbCb.plmnId;
   tai->tac    = nbCb.tac;
   RETVALUE(ROK);
}


#ifdef MULTI_ENB_SUPPORT
PUBLIC U32  nbGetUeLclTeid(U32 ueId, U32 rabId, U32 enbId)
#else
PUBLIC U32  nbGetUeLclTeid(U32 ueId, U32 rabId)
#endif
{
   U32 lclTeId = 0;
   lclTeId  = (nbCb.cellId & 0xff) << 24;
   lclTeId |= (ueId & 0xffff) << 8;
   lclTeId |= (rabId & 0xff) << 3;
#ifdef MULTI_ENB_SUPPORT
   lclTeId |= enbId;
#endif
   return lclTeId;
}

/* ================================================ */
/* S1AP UE CONTEXT RELEASE MESSAGE BUILDING         */
/* ================================================ */

/**
 *  @brief This function builds the S1AP Ue Context Release Request
 *
 *      Function: nbS1apFillCtxtRelReq
 *
 *          Processing steps:
 *          - Alloc memory to S1AP Ue Context Release Request message
 *          - fill the mandatory IE's
 *          - update the pointer to Release Request message into out pointer
 *
 *  @param [in]  s1Con : pointer to S1Ap connection CB
 *  @param [out] pdu   : double pointer to reurn the release request message
 *  @param [in]  cause : cause for the release
 *  @return S16
    -# Success : ROK
    -# Failure : RFAILED
 */

PUBLIC S16 nbS1apFillCtxtRelReq
(
 NbUeCb                       *ueCb,
 S1apPdu                      **pdu,
 NbUeMsgCause                *cause
)
{
   S1apPdu                   *szUeCxtRlsPdu = NULLP;
   U16                       numComp;
   SztProtIE_Field_UECntxtRlsRqst_IEs *ie = NULLP;
   U32                       ieIdx = 0;
   SztInitiatingMsg          *initMsg;
   SztUECntxtRlsRqst         *ctxtRel;
   NbS1ConCb                 *s1Con = ueCb->s1ConCb;

   NB_LOG_DEBUG(&nbCb, "Constructing UE Context Release Request");

   if (cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &nbCb.mem,
            (Ptr *)&szUeCxtRlsPdu) != ROK)
   {
      NB_LOG_ERROR(&nbCb, "Failed to allocate memory. cmAllocEvnt failed");
      RETVALUE(RFAILED);
   }

   nbFillTknU8(&(szUeCxtRlsPdu->pdu.choice), SZT_TRGR_INTI_MSG);
   initMsg = &(szUeCxtRlsPdu->pdu.val.initiatingMsg);
   nbFillTknU8(&(initMsg->pres), PRSNT_NODEF);
   nbFillTknU32(&(initMsg->procedureCode), Sztid_UECntxtRlsRqst);
   nbFillTknU32(&(initMsg->criticality), SztCriticalityignoreEnum);

   /* Filling 3 mandatory headers */
   /*List of IEs Filled
    * 1.UE MME S1AP ID
    * 2.UE ENB S1AP ID
    * 3.CAUSE */
   ctxtRel = &initMsg->value.u.sztUECntxtRlsRqst;
   nbFillTknU8(&(ctxtRel->pres), PRSNT_NODEF);
   numComp = 3;

   if ((cmGetMem(szUeCxtRlsPdu,
               (numComp * sizeof(SztProtIE_Field_UECntxtRlsRqst_IEs)),
               (Ptr *)&ctxtRel->protocolIEs.member)) != ROK)
   {
      NB_LOG_ERROR(&nbCb, "Failed to allocate memory. cmGetMem failed");
      RETVALUE(RFAILED);
   }

   /* IE1 - Filling MME ID */
   ie = &ctxtRel->protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
   nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   nbFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), s1Con->mme_ue_s1ap_id);
   ieIdx++;

   /* IE2 - Filling ENB ID */
   ie = &ctxtRel->protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
   nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   nbFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), s1Con->enb_ue_s1ap_id);
   ieIdx++;

   /* IE3 - Filling Cause */
   ie = &ctxtRel->protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_Cause);
   nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   nbS1apFillCause(&ie->value.u.sztCause, cause);
   ieIdx++;

   nbFillTknU16(&(ctxtRel->protocolIEs.noComp), ieIdx);

   *pdu = szUeCxtRlsPdu;
   RETVALUE(ROK);
}

/** @brief This function fills the S1-AP Cause IE.
 *
 * @details This function fills the S1AP: Cause IE with the
 *          cause type and cause value.
 *
 *     Function: nbS1apFillCause
 *
 * @param[out]            ie: S1AP Cause IE.
 * @param[in]          cause: cause type and cause value.
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 nbS1apFillCause
(
SztCause                     *ie,
NbUeMsgCause                 *cause
)
{
   ie->choice.pres    = PRSNT_NODEF;
   ie->choice.val     = cause->causeTyp;
   switch(cause->causeTyp)
   {
      case NB_CAUSE_RADIONW:
         nbFillTknU32(&(ie->val.radioNw), cause->causeVal);
         break;
      case NB_CAUSE_TRANSPORT:
         nbFillTknU32(&(ie->val.transport), cause->causeVal);
         break;
      case NB_CAUSE_NAS:
         nbFillTknU32(&(ie->val.nas), cause->causeVal);
         break;
      case NB_CAUSE_PROTOCOL:
         nbFillTknU32(&(ie->val.protocol), cause->causeVal);
         break;
      case NB_CAUSE_MISC:
         nbFillTknU32(&(ie->val.misc), cause->causeVal);
         break;
      default:
         NB_LOG_ERROR(&nbCb, "Unknown cause received");
         break;
   }
   RETVALUE(ROK);
}

PUBLIC S16  NbBuildAndSndErrIndMsg(NbErrIndMsg *s1ErrInd)
{
   NbMmeCb     *mmeCb  = NULLP;
   SztUDatEvnt uDatEvnt;
   mmeCb = &nbCb.mmeInfo;
   if(mmeCb == NULLP)
   {
      RETVALUE(RFAILED);
   }

   if (nbFillErrIndMsg(s1ErrInd,&(uDatEvnt.pdu)) != ROK)
   {
      RETVALUE(RFAILED);
   }

   uDatEvnt.transId.pres = PRSNT_NODEF;
   uDatEvnt.transId.val = 1;
   uDatEvnt.peerId.pres = PRSNT_NODEF;
   uDatEvnt.peerId.val = mmeCb->mmeId;
   #ifdef MULTI_ENB_SUPPORT
   uDatEvnt.enbId = s1ErrInd->enbId;
   #endif
   /* Send the pdu to the MME */
   if((NbIfmS1apSndMgmtMsg(&uDatEvnt)) != ROK)
   {
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}

PRIVATE S16 nbFillErrIndMsg(NbErrIndMsg *s1ErrInd,S1apPdu **errIndPdu)
{

   SztProtIE_Field_ErrIndIEs *ie = NULLP;
   SztCriticalityDiag_IE_Item *ie1 = NULLP;

   U16 numComp = 0;
   S16 ret = 0;
   U32 ueId = 0;
   U32 idx = 0;
   NbUeCb *ueCb = NULLP;
   NbS1ConCb *s1apConCb = NULLP;

   if((s1ErrInd->causePres != TRUE) &&(s1ErrInd->criticalityDiag.pres != TRUE))
   {
      NB_LOG_ERROR(&nbCb, "Neither CauseIe Nor CriticalDiagnosis Ie Present");
      RETVALUE(RFAILED);
   }
   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &nbCb.mem, (Ptr *)errIndPdu);
   if (ret != ROK)
   {
      RETVALUE(RFAILED);
   }
   nbFillTknU8(&((*errIndPdu)->pdu.choice), SZT_TRGR_INTI_MSG);
   nbFillTknU8(&((*errIndPdu)->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   nbFillTknU32(&((*errIndPdu)->pdu.val.initiatingMsg.procedureCode), Sztid_ErrInd);
   nbFillTknU32(&((*errIndPdu)->pdu.val.initiatingMsg.criticality), SztCriticalityignoreEnum);

   /* Filling of ErrInd structure */
   if(s1ErrInd->causePres == TRUE)
   {
      numComp++;
   }
   nbFillTknU8(&((*errIndPdu)->pdu.val.initiatingMsg.value.u.sztErrInd.pres), PRSNT_NODEF);
   if(s1ErrInd->isUeAssoc == TRUE)
   {
      ueId = s1ErrInd->ue_Id;
      if(ROK != (cmHashListFind(&(nbCb.ueCbLst), (U8 *)&(ueId),
              sizeof(U32), 0, (PTR *)&ueCb)))
      {
         NB_LOG_ERROR(&nbCb, "ueCb not found for UeId %d", ueId);
         RETVALUE(RFAILED);
      }
      s1apConCb = ueCb->s1ConCb;
      if(s1apConCb == NULLP || ((s1apConCb != NULLP) &&
            (s1apConCb->s1apConnState != NB_S1AP_CONNECTED)))
      {
         RETVALUE(RFAILED);
      }
      /*get the mmeS1ap and enbS1ap Ids */
         numComp = numComp + 2;
   }
   if(s1ErrInd->criticalityDiag.pres == TRUE)
   {
      numComp++;
   }
   nbFillTknU16(&((*errIndPdu)->pdu.val.initiatingMsg.value.u.sztErrInd.protocolIEs.noComp), numComp);
   /* check if critically diagnosys is present: increment number of components */
    if ((cmGetMem((*errIndPdu), (numComp * sizeof(SztProtIE_Field_ErrIndIEs)),
               (Ptr *)&((*errIndPdu)->pdu.val.initiatingMsg.value.u.sztErrInd.protocolIEs.member))) !=ROK)
      {
         NB_FREE((*errIndPdu),sizeof(S1apPdu));
         RETVALUE(RFAILED);
      }
   /* Reset the numComp parameter */
   numComp = 0;
   if(s1ErrInd->isUeAssoc == TRUE)
   {
       ie = &((*errIndPdu)->pdu.val.initiatingMsg.value.u.sztErrInd.protocolIEs.member[numComp++]);
       nbFillTknU8(&(ie->pres),PRSNT_NODEF);
       nbFillTknU32(&(ie->id),Sztid_MME_UE_S1AP_ID);
       nbFillTknU32(&(ie->criticality),SztCriticalityignoreEnum);
       nbFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID),s1apConCb->mme_ue_s1ap_id);

      ie = &((*errIndPdu)->pdu.val.initiatingMsg.value.u.sztErrInd.protocolIEs.member[numComp++]);
      nbFillTknU8(&(ie->pres),PRSNT_NODEF);
      nbFillTknU32(&(ie->id),Sztid_eNB_UE_S1AP_ID);
      nbFillTknU32(&(ie->criticality),SztCriticalityignoreEnum);
      nbFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID),s1apConCb->enb_ue_s1ap_id);
   }
   if(s1ErrInd->causePres == TRUE)
   {
      /* Fill cause */
      ie = &((*errIndPdu)->pdu.val.initiatingMsg.value.u.sztErrInd.protocolIEs.member[numComp++]);
      /* Fill cause IE container */
      nbFillTknU8(&(ie->pres), PRSNT_NODEF);
      nbFillTknU32(&(ie->id), Sztid_Cause);
      nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
      nbFillTknU8(&(ie->value.u.sztCause.choice), s1ErrInd->cause.causeType);
      switch(s1ErrInd->cause.causeType)
      {
         case CAUSE_RADIONW:
            nbFillTknU32(&(ie->value.u.sztCause.val.radioNw), s1ErrInd->cause.causeVal);
            break;

         case CAUSE_TRANSPORT:
            nbFillTknU32(&(ie->value.u.sztCause.val.transport), s1ErrInd->cause.causeVal);
            break;

         case CAUSE_NAS:
            nbFillTknU32(&(ie->value.u.sztCause.val.nas), s1ErrInd->cause.causeVal);
            break;

         case CAUSE_PROTOCOL:
            nbFillTknU32(&(ie->value.u.sztCause.val.protocol), s1ErrInd->cause.causeVal);
            break;

         case CAUSE_MISC:
            nbFillTknU32(&(ie->value.u.sztCause.val.misc), s1ErrInd->cause.causeVal);
            break;

         default:
            break;
      }
   }
   if(s1ErrInd->criticalityDiag.pres == TRUE)
   {
      ie = &((*errIndPdu)->pdu.val.initiatingMsg.value.u.sztErrInd.protocolIEs.member[numComp++]);

      nbFillTknU8(&(ie->pres), PRSNT_NODEF);
      nbFillTknU32(&(ie->id), Sztid_CriticalityDiag);
      nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
      nbFillTknU8(&(ie->value.u.sztCriticalityDiag.pres), PRSNT_NODEF);

      /* Get the procedure code and criticality from PDU */
      if(s1ErrInd->criticalityDiag.procCodePres == TRUE)
      {
         nbFillTknU32(&(ie->value.u.sztCriticalityDiag.procedureCode),\
           s1ErrInd->criticalityDiag.procedureCode);
      }
      if(s1ErrInd->criticalityDiag.trigMsgPres == TRUE)
      {
         nbFillTknU32(&(ie->value.u.sztCriticalityDiag.triggeringMsg),\
           s1ErrInd->criticalityDiag.triggeringMsg);
      }
      if(s1ErrInd->criticalityDiag.proCriticalityPres == TRUE)
      {
         nbFillTknU32(&(ie->value.u.sztCriticalityDiag.procedureCriticality),\
           s1ErrInd->criticalityDiag.procedureCriticality );
      }

      /* Get the no of components, the no of components is equal to error Ies */
      numComp = s1ErrInd->criticalityDiag.ieLst.noComp;
      nbFillTknU16(&(ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.noComp), numComp);

      /* Allocate memory for the members */
      if ((cmGetMem((*errIndPdu), (numComp * sizeof(SztCriticalityDiag_IE_Item)),
                  (Ptr *)&(ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.member))) != ROK)
      {
         NB_FREE((*errIndPdu),sizeof(S1apPdu));
         RETVALUE(RFAILED);
      }

      /* Fill the each reported error Ies with its criticality and ID */
      for(idx = 0; idx < numComp; idx++)
      {
         ie1 = &ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.member[idx];
         nbFillTknU8(&(ie1->pres), PRSNT_NODEF);
         nbFillTknU32(&(ie1->iECriticality), s1ErrInd->criticalityDiag.ieLst.member[idx].iECriticality);
         nbFillTknU32(&(ie1->iE_ID), s1ErrInd->criticalityDiag.ieLst.member[idx].iE_ID);
         nbFillTknU32(&(ie1->typeOfErr), s1ErrInd->criticalityDiag.ieLst.member[idx].TypOfErr);
         ie1->iE_Extns.noComp.pres = NOTPRSNT;
      }
   }
   RETVALUE(ROK);
}
PRIVATE S16 nbStartDelayTimerForUeCtxRel(U32 ueId)
{
   S16 retVal = RFAILED;
   NbDelayUeCtxtRelCmpCb *ueCtxtRelCmp = NULLP;
   NB_ALLOC(&ueCtxtRelCmp,sizeof(NbDelayUeCtxtRelCmpCb));
   ueCtxtRelCmp->ueId = ueId;
   cmInitTimers(&ueCtxtRelCmp->timer, 1);
   retVal = nbStartTmr((PTR)ueCtxtRelCmp, NB_TMR_DELAY_UE_CTX_REL_COMP, nbCb.delayUeCtxtRelCmp[ueId - 1].tmrVal);
   RETVALUE(retVal);
}
PRIVATE S16 nbStartDelayTimerForICSRsp(U32 ueId,NbErabLst *erabInfo)
{
  S16 retVal = RFAILED;
  NbDelayICSRspCb *icsRspCb = NULLP;

  NB_ALLOC(&icsRspCb,sizeof(NbDelayICSRspCb));
  icsRspCb->ueId = ueId;
  icsRspCb->erabInfo = erabInfo;
  cmInitTimers(&icsRspCb->timer, 1);
  retVal = nbStartTmr((PTR)icsRspCb,NB_TMR_DELAY_ICS_RSP,nbCb.delayInitCtxtSetupRsp[ueId - 1].tmrVal);
  RETVALUE(retVal);
}

PUBLIC S16 nbHandleDelayTimerForICSExpiry(NbDelayICSRspCb *icsRspCb)
{

   S16 retVal = RFAILED;
   NbUeCb *ueCb = NULLP;
   NbErabLst *erabInfo = NULLP;

   if ( ROK != (cmHashListFind(&(nbCb.ueCbLst), (U8 *)&(icsRspCb->ueId),
      sizeof(U32),0,(PTR *)&ueCb)))
   {
      NB_LOG_ERROR(&nbCb, "Failed to Find UeCb");
      RETVALUE(RFAILED);
   }
   erabInfo = icsRspCb->erabInfo;
   icsRspCb->erabInfo = NULLP;
   retVal = nbBuildAndSendIntCtxtSetupRsp(ueCb, erabInfo);

   NB_FREE(erabInfo->erabs,(erabInfo->noOfComp * sizeof(NbErabCb)));
   NB_FREE(erabInfo,sizeof(NbErabLst));
   NB_FREE(icsRspCb, sizeof(NbErabLst));

   RETVALUE(retVal);
}

PRIVATE S16 nbStartDelayTimerForErabRsp(U32 ueId, NbErabLst *erabInfo,
                                        NbFailedErabLst *failedErabInfo,
                                        U32 tmrVal) {
  S16 retVal = RFAILED;
  NbErabSetupRspCb *erabSetupRspCb = NULLP;
  NB_ALLOC(&erabSetupRspCb, sizeof(NbErabSetupRspCb));
  erabSetupRspCb->ueId = ueId;
  erabSetupRspCb->erabInfo = erabInfo;
  erabSetupRspCb->failedErabInfo = failedErabInfo;
  cmInitTimers(&erabSetupRspCb->timer, 1);
  if (nbStartTmr((PTR)erabSetupRspCb, NB_TMR_DELAY_ERAB_SETUP_RSP, tmrVal) !=
      ROK) {
    NB_LOG_ERROR(&nbCb,
                 "Failed to start timer for delaying erab setup rsp for ue %u",
                 ueId);
    RETVALUE(RFAILED);
  }
  NB_LOG_DEBUG(&nbCb, "Started timer of (%u) secs for ERAB_SETUP_RSP\n",
               tmrVal);
  RETVALUE(ROK);
}

PUBLIC S16
nbHandleDelayTimerForErabSetupRspExpiry(NbErabSetupRspCb *erabSetupRspCb) {

  S16 retVal = RFAILED;
  NbUeCb *ueCb = NULLP;
  NbErabLst *erabInfo = NULLP;
  NbFailedErabLst *failedErabInfo = NULLP;

  NB_LOG_DEBUG(&nbCb, "Timer expired for ERAB_SETUP_RSP\n");
  if (ROK != (cmHashListFind(&(nbCb.ueCbLst), (U8 *)&(erabSetupRspCb->ueId),
                             sizeof(U32), 0, (PTR *)&ueCb))) {
    NB_LOG_ERROR(&nbCb, "Failed to Find UeCb");
    RETVALUE(RFAILED);
  }
  if (erabSetupRspCb == NULLP) {
    NB_LOG_ERROR(&nbCb, "erabSetupRspCb is NULL for ue %u ",
                 erabSetupRspCb->ueId);
    RETVALUE(RFAILED);
  }
  erabInfo = erabSetupRspCb->erabInfo;
  failedErabInfo = erabSetupRspCb->failedErabInfo;
  NB_LOG_DEBUG(&nbCb, "Sending out-of-order ERAB_SETUP_RSP for ue %u\n",
               erabSetupRspCb->ueId);
  retVal = nbRabSetupSndS1apRsp(ueCb, erabInfo, failedErabInfo);

  if (erabInfo) {
    NB_FREE(erabInfo->erabs, (erabInfo->noOfComp * sizeof(NbErabCb)));
    NB_FREE(erabInfo, sizeof(NbErabLst));
  }
  if (failedErabInfo) {
    NB_FREE(failedErabInfo->failedErabs,
            (failedErabInfo->noOfComp * sizeof(NbFailedErab)));
    NB_FREE(failedErabInfo, sizeof(NbFailedErabLst));
  }
  NB_FREE(erabSetupRspCb, sizeof(NbErabSetupRspCb));

  RETVALUE(retVal);
}

PRIVATE S16 nbSendUeCtxtRelReqAsICSRsp(NbUeCb *ueCb) {
  S16 retVal = ROK;
  S1apPdu *ctxtRelReqPdu = NULLP;
  NbUeMsgCause cause;

   cause.causeTyp = \
         nbCb.dropICSSndCtxtRel[(ueCb->ueId) - 1].causeType;
   cause.causeVal = \
        nbCb.dropICSSndCtxtRel[(ueCb->ueId) - 1].causeVal;


   /* Check for s1ConCb before sending Connection release to MME */
   if(NULLP != ueCb->s1ConCb)
   {
            NB_LOG_DEBUG(&nbCb,"Sending UE CONTEXT RELEASE REQUEST" \
            ",MME-UE-S1AP-ID[%d], eNB-UE-S1AP-ID[%d]",\
            ueCb->s1ConCb->mme_ue_s1ap_id, ueCb->s1ConCb->enb_ue_s1ap_id);

      if(nbS1apFillCtxtRelReq(ueCb, &ctxtRelReqPdu, &cause) != ROK)
      {
         NB_LOG_ERROR(&nbCb, "Failed to build s1ap Context Rel Request");
         retVal = RFAILED;
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
   RETVALUE(retVal);
}

PUBLIC S16 nbHandleDelayTimerForUeCtxRelComplExpiry(NbDelayUeCtxtRelCmpCb *ueCtxtRelCmp)
{
   S16 retVal = RFAILED;
   NbUeCb *ueCb = NULLP;
   if ( ROK != (cmHashListFind(&(nbCb.ueCbLst), (U8 *)&(ueCtxtRelCmp->ueId),
				   sizeof(U32),0,(PTR *)&ueCb)))
   {
	   NB_LOG_ERROR(&nbCb, "Failed to Find UeCb");
	   RETVALUE(RFAILED);
   }
   retVal = nbCtxtRelSndRlsCmpl(ueCb);

   retVal = nbIfmDamUeDelReq(ueCb->ueId);
   RETVALUE(retVal);
}

#ifdef MULTI_ENB_SUPPORT
/* ================================================ */
/* S1AP PATH SWITCH REQUEST MESSAGE BUILDING         */
/* ================================================ */

/**
 *  @brief This function builds the Path Switch Request
 *
 *      Function: nbS1apFillPathSwitchReq
 *
 *          Processing steps:
 *          - Alloc memory to S1AP Path Switch Request message
 *          - fill the mandatory IE's
 *          - update the pointer to Path Switch Request message into out pointer
 *
 *  @param [in]  s1Con : pointer to S1Ap connection CB
 *  @param [out] pdu   : double pointer to reurn the Path Switch request message
 *  @param [in]  erabId : ERAB ID
 *  @param [in]  gtpTeId : eNB GTP TEID
 *  @return S16
    -# Success : ROK
    -# Failure : RFAILED
 */

PUBLIC S16 nbS1apFillPathSwReq
(
 NbUeCb                       *ueCb,
 S1apPdu                      **pdu,
 U32                          erabId,
 U32                          teId,
 U32                          numOfErabIds,
 U32                          mme_ue_s1ap_id
)
{
   S1apPdu                   *szPathSwReqPdu = NULLP;
   U16                       numComp;
   SztProtIE_Field_PathSwRqstIEs *ie = NULLP;
   SztProtIE_SingleCont_E_RABToBeSwedDLItemIEs *pathSwReqIeLst = NULLP;
   U32                       ieIdx = 0;
   SztInitiatingMsg          *initMsg  = NULLP;
   SztPathSwRqst             *pathSwReq = NULLP;
   NbS1ConCb                 *s1Con = ueCb->s1ConCb;
   U32                       len = 0;
   U32                       idx = 0;
   U32                       cnt = 0;
   U32                       cntr = 0;
   U8                        offSet;
   EnbCb                     *enbCb = NULLP;

   NB_LOG_DEBUG(&nbCb, "Constructing Path Switch Request");

   NB_ALLOCEVNT(&szPathSwReqPdu, sizeof(S1apPdu));
   if (szPathSwReqPdu == NULLP)
   {
      NB_LOG_ERROR(&nbCb, "Failed to allocate memory. cmAllocEvnt failed");
      RETVALUE(RFAILED);
   }

   nbFillTknU8(&(szPathSwReqPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   initMsg = &(szPathSwReqPdu->pdu.val.initiatingMsg);
   nbFillTknU8(&(initMsg->pres), PRSNT_NODEF);
   nbFillTknU32(&(initMsg->procedureCode),Sztid_PathSwRqst);
   nbFillTknU32(&(initMsg->criticality), SztCriticalityrejectEnum);
   /* Filling mandatory IEs */
   /*List of IEs Filled
    * 1.UE MME S1AP ID
    * 2.UE ENB S1AP ID
    * 3.E-RAB To be switched in DL
    *   1.Transport Layer Address
    *   2.GTP TEID
    * 4.ECGI
    * 5.TAI
    * 6.UE Security Capabilities */
   numComp = 6;
   pathSwReq = &initMsg->value.u.sztPathSwRqst;
   nbFillTknU8(&(pathSwReq->pres), PRSNT_NODEF);
   nbFillTknU16(&(initMsg->value.u.sztPathSwRqst.protocolIEs.noComp), numComp);

   if ((cmGetMem(szPathSwReqPdu,
               (numComp * sizeof(SztProtIE_Field_PathSwRqstIEs )),
               (Ptr *)&pathSwReq->protocolIEs.member)) != ROK)
   {
      NB_LOG_ERROR(&nbCb, "Failed to allocate memory. cmGetMem failed");
      RETVALUE(RFAILED);
   }
   /* IE1 - Filling ENB ID */
   ie = &pathSwReq->protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
   nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   nbFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), s1Con->enb_ue_s1ap_id);
   ieIdx++;

   /* IE2 - Filling ERAB to be switched in DL List */
   ie = &pathSwReq->protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_E_RABToBeSwedDLLst);
   nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   ieIdx++;

   nbFillTknU16(&(ie->value.u.sztE_RABToBeSwedDLLst.noComp), numOfErabIds);
   if (cmGetMem(szPathSwReqPdu,
            (numOfErabIds * sizeof(SztProtIE_SingleCont_E_RABToBeSwedDLItemIEs)),
            (Ptr *)&(ie->value.u.sztE_RABToBeSwedDLLst.member)) !=ROK)
   {
      NB_LOG_ERROR(&nbCb, "Failed to allocate memory for RAB SETUP list.");
      cmFreeMem(szPathSwReqPdu);
      RETVALUE(RFAILED);
   }
   for(cnt = 0; cnt < numOfErabIds; cnt++)
   {
      pathSwReqIeLst  = &ie->value.u.sztE_RABToBeSwedDLLst.member[cnt];

      nbFillTknU8(&(pathSwReqIeLst->pres), PRSNT_NODEF);
      nbFillTknU32(&(pathSwReqIeLst->id), Sztid_E_RABToBeSwedDLItem);
      nbFillTknU32(&(pathSwReqIeLst->criticality), SztCriticalityrejectEnum);

      nbFillTknU8(&(pathSwReqIeLst->value.u.sztE_RABToBeSwedDLItem.pres), PRSNT_NODEF);
      nbFillTknU32(&(pathSwReqIeLst->value.u.sztE_RABToBeSwedDLItem.e_RAB_ID),erabId);

      len = 4;
      pathSwReqIeLst->value.u.sztE_RABToBeSwedDLItem.gTP_TEID.len = (U16)len;
      pathSwReqIeLst->value.u.sztE_RABToBeSwedDLItem.gTP_TEID.pres = PRSNT_NODEF;
      NB_GET_MEM(szPathSwReqPdu, len, &pathSwReqIeLst->value.u.sztE_RABToBeSwedDLItem.gTP_TEID.val);
      for(cntr = 0; cntr < len; cntr++)
      {
         offSet = (U8)(len - (cntr + 1)) * 8;
         pathSwReqIeLst->value.u.sztE_RABToBeSwedDLItem.gTP_TEID.val[cntr] =
		 (U8)(teId >> offSet);
      }

      len = 4;
      pathSwReqIeLst->value.u.sztE_RABToBeSwedDLItem.transportLyrAddr.pres = PRSNT_NODEF;
      pathSwReqIeLst->value.u.sztE_RABToBeSwedDLItem.transportLyrAddr.len = (U16)(len * 8);
      NB_GET_MEM(szPathSwReqPdu, len,
		      &pathSwReqIeLst->value.u.sztE_RABToBeSwedDLItem.transportLyrAddr.val);
      for (idx = 0; idx < len; idx++)
      {
        offSet =(U8)((len - (idx + 1)) * 8);
        pathSwReqIeLst->value.u.sztE_RABToBeSwedDLItem.transportLyrAddr.val[idx] =
        (U8)(nbCb.datAppAddr.u.ipv4TptAddr.address >> offSet);
      }

      pathSwReqIeLst->value.u.sztE_RABToBeSwedDLItem.iE_Extns.noComp.pres = NOTPRSNT;
   }

   /* IE3 - Filling MME ID */
   ie = &pathSwReq->protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_SrcMME_UE_S1AP_ID);
   nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   nbFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mme_ue_s1ap_id);
   ieIdx++;

   /* IE4 - Filling  EUTRAN CGI */
   ie = &pathSwReq->protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_EUTRAN_CGI);
   nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);

   if ( ROK != (cmHashListFind(&(nbCb.eNBCbLst), (U32 *)&(ueCb->enbId),
               sizeof(U32),0,(PTR *)&enbCb)))
   {
      NB_LOG_ERROR(&nbCb, "enbCb not found for enbId %d", ueCb->enbId);
      RETVALUE(RFAILED);
   }
   if (enbCb == NULLP){
      NB_LOG_ERROR(&nbCb, "enbCb is NULL!!");
   }

   nbFillTknU8(&(ie->value.u.sztEUTRAN_CGI.pres), PRSNT_NODEF);
   nbSztFillPLMNId(szPathSwReqPdu, &enbCb->plmnId, &ie->value.u.sztEUTRAN_CGI.pLMNidentity);
   nbFillTknBStr32(&(ie->value.u.sztEUTRAN_CGI.cell_ID), 28, enbCb->cell_id);
   ie->value.u.sztEUTRAN_CGI.iE_Extns.noComp.pres = NOTPRSNT;
   ieIdx++;

   /* IE5 - Filling  TAI*/
   ie = &pathSwReq->protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_TAI);
   nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   nbFillTknU8(&(ie->value.u.sztTAI.pres), PRSNT_NODEF);

   NbTai  tai;
   tai.plmnId = enbCb->plmnId;
   tai.tac    = enbCb->tac;

   nbFillTknU8(&(ie->value.u.sztTAI.pres), PRSNT_NODEF);
   if (nbSztFillPLMNId(szPathSwReqPdu, &tai.plmnId, &(ie->value.u.sztTAI.pLMNidentity)) != ROK)
   {
      RETVALUE(RFAILED);
   }
   nbSztFillTAC(tai.tac, szPathSwReqPdu, &(ie->value.u.sztTAI.tAC));
   ieIdx++;

   /* IE6 - Filling  UE Security Capability*/
   ie = &pathSwReq->protocolIEs.member[ieIdx];
   nbFillTknU8(&(ie->pres), PRSNT_NODEF);
   nbFillTknU32(&(ie->id), Sztid_UESecurCapabilities);
   nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   nbFillTknU8(&(ie->value.u.sztUESecurCapabilities.pres), PRSNT_NODEF);
   nbFillTknBStr32(&(ie->value.u.sztUESecurCapabilities.encryptionAlgorithms),
     16, ueCb->encryptionAlgo);
   nbFillTknBStr32(&(ie->value.u.sztUESecurCapabilities.integrityProtectionAlgorithms),
     16, ueCb->integrityAlgo);
   ieIdx++;

   *pdu = szPathSwReqPdu;

   RETVALUE(ROK);
}

/* ================================================= */
/* S1AP ENB CONFIGURATION TRANSFER MESSAGE BUILDING  */
/* ================================================= */
/** @brief This function will allocate memory and build the
 *       S1AP:ENB Configuration Transfer message .
 *
 * @details This function allocates the memory for S1AP:
 *    ENB CONFIGURATION TRANSFER
 *    Message PDU and fills the PDU with proper values.
 *
 * Function: nbBldEnbConfigTransfer
 *
 *       Processing steps:
 *        - Allocate Memory for S1-AP: EnodeB Config Transfer Message PDU.
 *         - Fill the PDU with proper values.
 *
 *@param[out] pdu: S1-AP: ENB Config Transfer PDU.
 * @return  S16
 *      -# Success : ROK
 *       -# Failure : RFAILED
 */
#ifdef MULTI_ENB_SUPPORT
PUBLIC S16 nbBldENbConfigTransfer
(
 S1apPdu      **pdu,
 EnbCb        *srcenbCb,
 NbUeCb       *ueCb
)
{
   S1apPdu                              *eNBConfigTfrPdu = NULLP;
   U16                                  numComp;
   S16                                  ret;
   SztProtIE_Field_ENBConfigTfrIEs      *ie;
   SztTgeteNB_ID                        *ie1;
   SztSrceNB_ID                         *ie2;
   SztSONInform                         *ie3;
   SztProtExtnField_SONConfigTfr_ExtIEs *ie4;
   SztInitiatingMsg                     *initMsg;
   EnbCb                                *tgtEnbCb   = NULLP;  /* enbApp uecb */
   EnbCb                                *prevnbCb   = NULLP;  /* enbApp uecb */
   U32                                  len = 0;
   U8                                   offSet = 0;
   U32                                  idx = 0;
   U8                                   tptAddr[10];
   TRC2(nbtBldS1etupReq);
   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), NB_SZ_MEM_SDU_SIZE, &nbCb.mem,
         (Ptr *)&eNBConfigTfrPdu);
   if(ret != ROK)
   {
      NB_LOG_ERROR(&nbCb, "cmAllocEvnt failed");
      RETVALUE(RFAILED);
   }
   if (srcenbCb == NULLP)
   {
      NB_LOG_ERROR(&nbCb, "srcenbCb is NULL!!\n");
      RETVALUE(RFAILED);
   }
   nbFillTknU8(&(eNBConfigTfrPdu->pdu.choice), SZT_TRGR_INTI_MSG);

   initMsg = &(eNBConfigTfrPdu->pdu.val.initiatingMsg);
   nbFillTknU8(&(initMsg->pres), PRSNT_NODEF);
   nbFillTknU32(&(initMsg->procedureCode), Sztid_eNBConfigTfr);
   nbFillTknU32(&(initMsg->criticality), SztCriticalityignoreEnum);
   nbFillTknU8(&(initMsg->value.u.sztENBConfigTfr.pres), PRSNT_NODEF);

   numComp = 1;
   szFillTknU8(&(eNBConfigTfrPdu->pdu.val.initiatingMsg.value.u.sztENBConfigTfr.pres), PRSNT_NODEF);
   szFillTknU16(&(eNBConfigTfrPdu->pdu.val.initiatingMsg.value.u.sztENBConfigTfr.protocolIEs.noComp), numComp);

   if ((cmGetMem(eNBConfigTfrPdu, (numComp * sizeof( SztProtIE_Field_ENBConfigTfrIEs )),
		(Ptr *)&eNBConfigTfrPdu->pdu.val.initiatingMsg.value.u.sztENBConfigTfr.protocolIEs.member)) !=ROK)
   {
      NB_LOG_ERROR(&nbCb, " nbBldEnbConfigTransfer: cmGetMem failed");
      RETVALUE(RFAILED);
   }

   ie = &initMsg->value.u.sztENBConfigTfr.protocolIEs.member[0];

   // SON COnfiguration Transfer
   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_SONConfigTfrECT);
   szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   szFillTknU8(&(ie->value.u.sztSONConfigTfr.pres), PRSNT_NODEF);

   // Target enbID
   for(;((cmHashListGetNext(&(nbCb.eNBCbLst),(PTR)prevnbCb,(PTR*)&tgtEnbCb)) == ROK);)
   {
     if (!tgtEnbCb)
     {
       NB_LOG_ERROR(&nbCb,"eNBCbLst is NULL\n");
       RETVALUE(RFAILED);
     }
     if (tgtEnbCb->enbId == ueCb->enbId)
     {
       continue;
     }
     break;
   }
   ie1 = &(ie->value.u.sztSONConfigTfr.targeteNB_ID);

   szFillTknU8(&(ie1->pres), PRSNT_NODEF);
   szFillTknU8(&(ie1->global_ENB_ID.pres), PRSNT_NODEF);
   /* ENodeBType : Macro NB or Home NB */
   if (smCfgCb.eNodeBType.pres)
   {
      /* Value coming from Test Stub */
      nbSztFillS1eNBId(eNBConfigTfrPdu, smCfgCb.eNodeBType.val, tgtEnbCb->cell_id,
         &(tgtEnbCb->plmnId),
         &(ie1->global_ENB_ID));
   }
   else
   {
      nbSztFillS1eNBId(eNBConfigTfrPdu, nbCb.enbType, tgtEnbCb->cell_id,
         &(tgtEnbCb->plmnId),
         &(ie1->global_ENB_ID));
   }

   ie1->global_ENB_ID.iE_Extns.noComp.pres = NOTPRSNT;
   //TAI
   szFillTknU8(&(ie1->selected_TAI.pres), PRSNT_NODEF);
   nbSztFillPLMNId(eNBConfigTfrPdu,&tgtEnbCb->plmnId,&ie1->selected_TAI.pLMNidentity);
   nbSztFillTAC(tgtEnbCb->tac, eNBConfigTfrPdu,&ie1->selected_TAI.tAC);
   ie1->selected_TAI.iE_Extns.noComp.pres = NOTPRSNT;

   // Source eNBID
   ie2 = &(ie->value.u.sztSONConfigTfr.sourceeNB_ID);

   szFillTknU8(&(ie2->pres), PRSNT_NODEF);
   szFillTknU8(&(ie2->global_ENB_ID.pres), PRSNT_NODEF);
   /* ENodeBType : Macro NB or Home NB */
   if (smCfgCb.eNodeBType.pres)
   {
      /* Value coming from Test Stub */
      nbSztFillS1eNBId(eNBConfigTfrPdu, smCfgCb.eNodeBType.val, srcenbCb->cell_id,
         &(srcenbCb->plmnId),
         &(ie2->global_ENB_ID));
   }
   else
   {
      nbSztFillS1eNBId(eNBConfigTfrPdu, nbCb.enbType, srcenbCb->cell_id,
         &(srcenbCb->plmnId),
         &(ie2->global_ENB_ID));
   }

   ie2->global_ENB_ID.iE_Extns.noComp.pres = NOTPRSNT;
   //TAI
   szFillTknU8(&(ie2->selected_TAI.pres), PRSNT_NODEF);
   nbSztFillPLMNId(eNBConfigTfrPdu,&srcenbCb->plmnId,&ie2->selected_TAI.pLMNidentity);
   nbSztFillTAC(srcenbCb->tac, eNBConfigTfrPdu,&ie2->selected_TAI.tAC);
   ie2->selected_TAI.iE_Extns.noComp.pres = NOTPRSNT;

   // SON Information
   ie3 = &(ie->value.u.sztSONConfigTfr.sONInform);
   szFillTknU8(&(ie3->choice), SONINFORM_SONINFORMRQST);
   szFillTknU32(&(ie3->val.sONInformRqst), SztSONInformRqstx2TNL_Config_InfoEnum);

   //Transport Layer Address
   szFillTknU16(&(ie->value.u.sztSONConfigTfr.iE_Extns.noComp),1);
   if (cmGetMem(eNBConfigTfrPdu, (1 * sizeof(SztProtExtnField_SONConfigTfr_ExtIEs)),
            (Ptr *)&(ie->value.u.sztSONConfigTfr.iE_Extns.member)) !=ROK)
   {
      RETVALUE(RFAILED);
   }

   ie4 = &(ie->value.u.sztSONConfigTfr.iE_Extns.member[0]);

   szFillTknU8(&(ie4->pres), PRSNT_NODEF);
   szFillTknU32(&(ie4->id), Sztid_x2TNLConfigInfo);
   szFillTknU32(&(ie4->criticality), SztCriticalityignoreEnum);

   szFillTknU8(&(ie4->extensionValue.u.sztX2TNLConfigInfo.pres), PRSNT_NODEF);

   szFillTknU16(&(ie4->extensionValue.u.sztX2TNLConfigInfo.eNBX2TportLyrAddres.noComp), 1);


   if (cmGetMem(eNBConfigTfrPdu, (1 * sizeof(SztTportLyrAddr)),
            (Ptr *)&(ie4->extensionValue.u.sztX2TNLConfigInfo.eNBX2TportLyrAddres.member)) !=ROK)
   {
      RETVALUE(RFAILED);
   }
   U8 addrOctets[4];
   addrOctets[0] = (nbCb.datAppAddr.u.ipv4TptAddr.address & 0xff000000) >> 24;
   addrOctets[1] = (nbCb.datAppAddr.u.ipv4TptAddr.address & 0x00ff0000) >> 16;
   addrOctets[2] = (nbCb.datAppAddr.u.ipv4TptAddr.address & 0x0000ff00) >> 8;
   addrOctets[3] = (nbCb.datAppAddr.u.ipv4TptAddr.address & 0x000000ff);

   if (nbFillTknStrBSXL(
            &ie4->extensionValue.u.sztX2TNLConfigInfo.eNBX2TportLyrAddres.member[0],
            32, addrOctets,
            (CmMemListCp*)eNBConfigTfrPdu) != ROK)
   {
      NB_LOG_ERROR(&nbCb, "Failed to fill IPV4 adress");
      RETVALUE(RFAILED);
   }

   /* Fill in the number of IEs included in the message */
   nbFillTknU16(&(initMsg->value.u.sztENBConfigTfr.protocolIEs.noComp), 1);

   /* Pass the constructed PDU back to the caller */
   *pdu = eNBConfigTfrPdu;

   RETVALUE(ROK);
} /* nbBldS1SetupReq */

/* ====================================== */
/* S1 HANDOVER REQUIRED MESSAGE BUILDING  */
/* ====================================== */
/* @brief This function will allocate memory and build the
 *    S1AP: S1 Handover Required message
 *
 * @details This function allocates the memory for S1AP:
 *    S1 HANDOVER REQUIRED
 *    Message PDU and fills the PDU with proper values
 *
 * Function: nbBldS1HandoverRequired
 *
 *    Processing steps:
 *     -Allocate Memory for S1AP: S1 Handover Required Message PDU
 *     -Fill the PDU with proper values
 *
 * @param[out] pdu: S1AP: S1 Handover Required PDU
 *
 * @return  S16
 *    -# Success : ROK
 *    -# Failure : RFAILED
 */
PUBLIC S16 nbBldS1HandoverRequired(S1apPdu **pdu, NbUeCb *ueCb, EnbCb *tgtEnbCb,
                                   NbUeMsgCause *cause) {
  S1apPdu *s1HoRequiredPdu = NULLP;
  NbS1ConCb *s1apCon = ueCb->s1ConCb;
  SztInitiatingMsg *initMsg;
  SztHovrReqd *s1HoReqd = NULLP;
  SztProtIE_Field_HovrReqdIEs *ie;
  SztTgeteNB_ID *ie1;
  U16 numComp;
  S16 ret;
  U32 ieIdx = 0;
  TRC2(nbBldS1HandoverRequired);

  NB_LOG_DEBUG(&nbCb, "Building S1 Handover Required Message for UE Id: %u",
               ueCb->ueId);

  // Initialize memory control point
  ret = cmAllocEvnt(sizeof(S1apPdu), NB_SZ_MEM_SDU_SIZE, &nbCb.mem,
                    (Ptr *)&s1HoRequiredPdu);
  if (ret != ROK) {
    NB_LOG_ERROR(&nbCb, "cmAllocEvnt failed for s1HoRequiredPdu");
    RETVALUE(RFAILED);
  }
  nbFillTknU8(&(s1HoRequiredPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);

  initMsg = &(s1HoRequiredPdu->pdu.val.initiatingMsg);
  nbFillTknU8(&(initMsg->pres), PRSNT_NODEF);
  nbFillTknU32(&(initMsg->procedureCode), Sztid_HovrPrep);
  nbFillTknU32(&(initMsg->criticality), SztCriticalityrejectEnum);

  /* IEs to be filled in PDU:
   * 1. MME UE S1AP Id
   * 2. ENB UE S1AP Id
   * 3. Handover Type
   * 4. Cause
   * 5. Target Id
   * 6. Source to Target Transparent Container
   */
  numComp = 6;
  s1HoReqd = &initMsg->value.u.sztHovrReqd;
  nbFillTknU8(&(s1HoReqd->pres), PRSNT_NODEF);
  nbFillTknU16(&(initMsg->value.u.sztHovrReqd.protocolIEs.noComp), numComp);

  if ((cmGetMem(s1HoRequiredPdu,
                (numComp * sizeof(SztProtIE_Field_HovrReqdIEs)),
                (Ptr *)&s1HoReqd->protocolIEs.member)) != ROK) {
    NB_LOG_ERROR(&nbCb, "Failed to allocate memory for S1HovrReqdIEs");
    RETVALUE(RFAILED);
  }

  // IE1 - Filling MME UE S1AP Id
  ie = &s1HoReqd->protocolIEs.member[ieIdx];
  nbFillTknU8(&(ie->pres), PRSNT_NODEF);
  nbFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
  nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
  nbFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), s1apCon->mme_ue_s1ap_id);
  ieIdx++;

  // IE2 - Filling ENB UE S1AP Id
  ie = &s1HoReqd->protocolIEs.member[ieIdx];
  nbFillTknU8(&(ie->pres), PRSNT_NODEF);
  nbFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
  nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
  nbFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), s1apCon->enb_ue_s1ap_id);
  ieIdx++;

  // IE3 - Filling S1AP Handover Type
  ie = &s1HoReqd->protocolIEs.member[ieIdx];
  nbFillTknU8(&(ie->pres), PRSNT_NODEF);
  nbFillTknU32(&(ie->id), Sztid_HovrTyp);
  nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
  nbFillTknU32(&(ie->value.u.sztHovrTyp), SztHovrTypintralteEnum);
  ieIdx++;

  // IE4 - Filling Handover Cause
  ie = &s1HoReqd->protocolIEs.member[ieIdx];
  nbFillTknU8(&(ie->pres), PRSNT_NODEF);
  nbFillTknU32(&(ie->id), Sztid_Cause);
  nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
  nbS1apFillCause(&(ie->value.u.sztCause), cause);
  ieIdx++;

  // IE5 - Filling Target Id
  ie = &s1HoReqd->protocolIEs.member[ieIdx];
  nbFillTknU8(&(ie->pres), PRSNT_NODEF);
  nbFillTknU32(&(ie->id), Sztid_TgetID);
  nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
  szFillTknU8(&(ie->value.u.sztTgetID.choice), TGETID_TARGETENB_ID);

  // targeteNB_ID
  ie1 = &(ie->value.u.sztTgetID.val.targeteNB_ID);
  szFillTknU8(&(ie1->pres), PRSNT_NODEF);

  // targeteNB_ID -> global_ENB_ID
  szFillTknU8(&(ie1->global_ENB_ID.pres), PRSNT_NODEF);
  // ENodeBType : Macro NB or Home NB
  if (smCfgCb.eNodeBType.pres) {
    // Value coming from Test Stub
    nbSztFillS1eNBId(s1HoRequiredPdu, smCfgCb.eNodeBType.val, tgtEnbCb->cell_id,
                     &(tgtEnbCb->plmnId), &(ie1->global_ENB_ID));
  } else {
    nbSztFillS1eNBId(s1HoRequiredPdu, nbCb.enbType, tgtEnbCb->cell_id,
                     &(tgtEnbCb->plmnId), &(ie1->global_ENB_ID));
  }
  ie1->global_ENB_ID.iE_Extns.noComp.pres = NOTPRSNT;

  // targeteNB_ID -> selected_TAI
  szFillTknU8(&(ie1->selected_TAI.pres), PRSNT_NODEF);
  nbSztFillPLMNId(s1HoRequiredPdu, &tgtEnbCb->plmnId,
                  &ie1->selected_TAI.pLMNidentity);
  nbSztFillTAC(tgtEnbCb->tac, s1HoRequiredPdu, &ie1->selected_TAI.tAC);
  ie1->selected_TAI.iE_Extns.noComp.pres = NOTPRSNT;
  ieIdx++;

  // IE6 - Filling Source to Target Transparent Container
  U16 lenData = 40;
  U8 *tempData;
  tempData = (U8 *)malloc(sizeof(U8) * lenData);
  memcpy(tempData,
         "\x60\x04\x00\x03\x90\x00\x00\x40\x00\x00\x00\x00\x00\x00\x00\x00\x00"
         "\xf8\xfd\x00\x00\x00\x58\x30\x31\x32\x33\x34\x30\x36\x0a\x38\x39\x61"
         "\x62\x63\x64\x65\x66\x00",
         lenData);

  ie = &s1HoReqd->protocolIEs.member[ieIdx];
  nbFillTknU8(&(ie->pres), PRSNT_NODEF);
  nbFillTknU32(&(ie->id), Sztid_Src_ToTget_TprntCont);
  nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
  nbFillTknStrOSXL(&(ie->value.u.sztid_Src_ToTget_TprntCont), lenData, tempData,
                   &(s1HoRequiredPdu->memCp));

  // Pass the constructed PDU back to the caller
  *pdu = s1HoRequiredPdu;

  RETVALUE(ROK);
} // nbBldS1HandoverRequired

/* ================================================= */
/* S1 HANDOVER REQUEST ACKNOWLEDGE MESSAGE BUILDING  */
/* ================================================= */
/* @brief This function will allocate memory and build the
 *    S1AP: S1 Handover Request Acknowledge message
 *
 * @details This function allocates the memory for S1AP:
 *    S1 HANDOVER REQUEST ACKNOWLEDGE
 *    Message PDU and fills the PDU with proper values
 *
 * Function: nbBldS1HandoverReqAck
 *
 *    Processing steps:
 *     -Allocate Memory for S1AP: S1 Handover Request Acknowledge Message PDU
 *     -Fill the PDU with proper values
 *
 * @param[out] pdu: S1AP: S1 Handover Request Acknowledge PDU
 *
 * @return  S16
 *    -# Success : ROK
 *    -# Failure : RFAILED
 */
PUBLIC S16 nbBldS1HandoverReqAck(S1apPdu **pdu, NbUeCb *ueCb) {
  S1apPdu *s1HoReqAckPdu = NULLP;
  NbS1ConCb *s1apCon = ueCb->s1ConCb;
  SztSuccessfulOutcome *succMsg;
  SztHovrRqstAckg *s1HoReqAckg = NULLP;
  SztProtIE_Field_HovrRqstAckgIEs *ie;
  SztProtIE_SingleCont_E_RABAdmtdItemIEs *rspMember;
  U16 numComp;
  S16 ret;
  U32 ieIdx = 0;
  U32 len = 0;
  U8 offSet = 0;
  U32 idx = 0;
  U32 ieIdx2 = 0;

  TRC2(nbBldS1HandoverReqAck);

  NB_LOG_DEBUG(
      &nbCb,
      "Building S1 Handover Request Acknowledgement Message for UE Id: %u",
      ueCb->ueId);

  // Initialize memory control point
  ret = cmAllocEvnt(sizeof(S1apPdu), NB_SZ_MEM_SDU_SIZE, &nbCb.mem,
                    (Ptr *)&s1HoReqAckPdu);
  if (ret != ROK) {
    NB_LOG_ERROR(&nbCb, "cmAllocEvnt failed for s1HoReqAckPdu");
    RETVALUE(RFAILED);
  }
  nbFillTknU8(&(s1HoReqAckPdu->pdu.choice), S1AP_PDU_SUCCESSFULOUTCOME);

  succMsg = &(s1HoReqAckPdu->pdu.val.successfulOutcome);
  nbFillTknU8(&(succMsg->pres), PRSNT_NODEF);
  nbFillTknU32(&(succMsg->procedureCode), Sztid_HovrResourceAllocn);
  nbFillTknU32(&(succMsg->criticality), SztCriticalityrejectEnum);

  /* IEs to be filled in PDU:
   * 1. MME UE S1AP Id
   * 2. ENB UE S1AP Id
   * 3. E-RAB Admitted List
   * 4. Target to Source Transparent Container
   */
  numComp = 4;
  s1HoReqAckg = &succMsg->value.u.sztHovrRqstAckg;
  nbFillTknU8(&(s1HoReqAckg->pres), PRSNT_NODEF);
  nbFillTknU16(&(succMsg->value.u.sztHovrRqstAckg.protocolIEs.noComp), numComp);

  if ((cmGetMem(s1HoReqAckPdu,
                (numComp * sizeof(SztProtIE_Field_HovrRqstAckgIEs)),
                (Ptr *)&s1HoReqAckg->protocolIEs.member)) != ROK) {
    NB_LOG_ERROR(&nbCb, "Failed to allocate memory for S1HovrRqstAckgIEs");
    RETVALUE(RFAILED);
  }

  // IE1 - Filling MME UE S1AP Id
  ie = &s1HoReqAckg->protocolIEs.member[ieIdx];
  nbFillTknU8(&(ie->pres), PRSNT_NODEF);
  nbFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
  nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
  nbFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), s1apCon->mme_ue_s1ap_id);
  ieIdx++;

  // IE2 - Filling ENB UE S1AP Id
  ie = &s1HoReqAckg->protocolIEs.member[ieIdx];
  nbFillTknU8(&(ie->pres), PRSNT_NODEF);
  nbFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
  nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
  nbFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), s1apCon->enb_ue_s1ap_id);
  ieIdx++;

  // IE3 - Filling E-RAB Admitted List
  U16 numRabsAllowed = 1;
  ie = &s1HoReqAckg->protocolIEs.member[ieIdx];
  nbFillTknU8(&(ie->pres), PRSNT_NODEF);
  nbFillTknU32(&(ie->id), Sztid_E_RABAdmtdLst);
  nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
  nbFillTknU16(&(ie->value.u.sztE_RABAdmtdLst.noComp), numRabsAllowed);
  ieIdx++;

  if (numRabsAllowed > 0) {
    // ERAB Admitted List
    if ((cmGetMem(
            s1HoReqAckPdu,
            (numRabsAllowed * sizeof(SztProtIE_SingleCont_E_RABAdmtdItemIEs)),
            (Ptr *)&ie->value.u.sztE_RABAdmtdLst.member)) != ROK) {
      NB_LOG_ERROR(&nbCb, "Failed to allocate memory for E_RABAdmtdItemIEs");
      RETVALUE(RFAILED);
    }

    // Locate ERAB to be setup List IE
    for (idx = 0; idx < numRabsAllowed; idx++) {
      SztE_RABAdmtdItem *rabIE;

      rspMember = &(ie->value.u.sztE_RABAdmtdLst.member[ieIdx2++]);
      nbFillTknU8(&(rspMember->pres), PRSNT_NODEF);
      nbFillTknU32(&(rspMember->id), Sztid_E_RABAdmtdItem);
      nbFillTknU32(&(rspMember->criticality), SztCriticalityignoreEnum);

      rabIE = &(rspMember->value.u.sztE_RABAdmtdItem);
      nbFillTknU8(&(rabIE->pres), PRSNT_NODEF);
      nbFillTknU32(&rabIE->e_RAB_ID, ueCb->s1HoInfo->tunInfo->bearerId);

      if (nbCb.datAppAddr.type == CM_TPTADDR_IPV4) {
        len = 4;
        rabIE->transportLyrAddr.pres = PRSNT_NODEF;
        rabIE->transportLyrAddr.len = (U16)(len * 8);
        NB_GET_MEM(s1HoReqAckPdu, len, &rabIE->transportLyrAddr.val);

        U16 cnt = 0;
        for (cnt = 0; cnt < len; cnt++) {
          offSet = (U8)((len - (cnt + 1)) * 8);
          rabIE->transportLyrAddr.val[cnt] =
              (U8)(nbCb.datAppAddr.u.ipv4TptAddr.address >> offSet);
        }
      }

      nbFillTknStrOSXL1(&rabIE->gTP_TEID, 4, ueCb->s1HoInfo->tunInfo->lclTeId,
                        &(s1HoReqAckPdu->memCp));
      rabIE->iE_Extns.noComp.pres = NOTPRSNT;
      if (ieIdx2 >= numRabsAllowed) {
        break;
      }
    }
  }

  // IE4 - Filling Target to Source Transparent Container
  U16 lenData = 53;
  U8 *temp;
  temp = (U8 *)malloc(sizeof(U8) * lenData);
  memcpy(temp,
         "\x00\x20\x20\x20\x20\x20\x74\x61\x72\x67\x65\x74\x20\x74\x6f\x20\x73"
         "\x6f\x75\x72\x63\x65\x20\x74\x72\x61\x6e\x73\x70\x61\x72\x65\x6e\x74"
         "\x20\x20\x20\x63\x6f\x6e\x74\x20\x00\x31\x32\x33\x34\x35\x36\x00\x01"
         "\x02\x03\x00",
         lenData);

  ie = &s1HoReqAckg->protocolIEs.member[ieIdx];
  nbFillTknU8(&(ie->pres), PRSNT_NODEF);
  nbFillTknU32(&(ie->id), Sztid_Tget_ToSrc_TprntCont);
  nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
  nbFillTknStrOSXL(&(ie->value.u.sztTget_ToSrc_TprntCont), lenData, temp,
                   &(s1HoReqAckPdu->memCp));

  // Pass the constructed PDU back to the caller
  *pdu = s1HoReqAckPdu;

  RETVALUE(ROK);
} // nbBldS1HandoverReqAck

/* ====================================== */
/* ENB STATUS TRANSFER MESSAGE BUILDING   */
/* ====================================== */
/* @brief This function will allocate memory and build the
 *    S1AP: ENB Status Transfer message
 *
 * @details This function allocates the memory for S1AP:
 *    ENB STATUS TRANSFER
 *    Message PDU and fills the PDU with proper values
 *
 * Function: nbBldS1HoEnbStatusTransfer
 *
 *    Processing steps:
 *     -Allocate Memory for S1AP: ENB Status Transfer Message PDU
 *     -Fill the PDU with proper values
 *
 * @param[out] pdu: S1AP: ENB Status Transfer PDU
 *
 * @return  S16
 *    -# Success : ROK
 *    -# Failure : RFAILED
 */
PUBLIC S16 nbBldS1HoEnbStatusTransfer(S1apPdu **pdu, NbUeCb *ueCb) {
  S1apPdu *enbStatusTransferPdu = NULLP;
  NbS1ConCb *s1apCon = ueCb->s1ConCb;
  SztInitiatingMsg *initMsg;
  SztENBStatusTfr *s1ENBStatusTfr = NULLP;
  SztProtIE_Field_ENBStatusTfrIEs *ie;
  SztENB_StatusTfr_TprntCont *ie1;
  SztProtIE_SingleCont_Brs_SubjToStatusTfr_ItemIEs *ie2;
  U16 numComp;
  S16 ret;
  U32 ieIdx = 0;

  TRC2(nbBldS1HoEnbStatusTransfer);

  NB_LOG_DEBUG(&nbCb, "Building ENB Status Transfer Message for UE Id: %u",
               ueCb->ueId);

  // Initialize memory control point
  ret = cmAllocEvnt(sizeof(S1apPdu), NB_SZ_MEM_SDU_SIZE, &nbCb.mem,
                    (Ptr *)&enbStatusTransferPdu);
  if (ret != ROK) {
    NB_LOG_ERROR(&nbCb, "cmAllocEvnt failed for enbStatusTransferPdu");
    RETVALUE(RFAILED);
  }
  nbFillTknU8(&(enbStatusTransferPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);

  initMsg = &(enbStatusTransferPdu->pdu.val.initiatingMsg);
  nbFillTknU8(&(initMsg->pres), PRSNT_NODEF);
  nbFillTknU32(&(initMsg->procedureCode), Sztid_eNBStatusTfr);
  nbFillTknU32(&(initMsg->criticality), SztCriticalityignoreEnum);

  /* IEs to be filled in PDU:
   * 1. MME UE S1AP Id
   * 2. ENB UE S1AP Id
   * 3. ENB Status Transfer Transparent Container
   */
  numComp = 3;
  s1ENBStatusTfr = &initMsg->value.u.sztENBStatusTfr;
  nbFillTknU8(&(s1ENBStatusTfr->pres), PRSNT_NODEF);
  nbFillTknU16(&(initMsg->value.u.sztENBStatusTfr.protocolIEs.noComp), numComp);

  if ((cmGetMem(enbStatusTransferPdu,
                (numComp * sizeof(SztProtIE_Field_ENBStatusTfrIEs)),
                (Ptr *)&s1ENBStatusTfr->protocolIEs.member)) != ROK) {
    NB_LOG_ERROR(&nbCb, "Failed to allocate memory for ENBStatusTfrIEs");
    RETVALUE(RFAILED);
  }

  // IE1 - Filling MME UE S1AP Id
  ie = &s1ENBStatusTfr->protocolIEs.member[ieIdx];
  nbFillTknU8(&(ie->pres), PRSNT_NODEF);
  nbFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
  nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
  nbFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), s1apCon->mme_ue_s1ap_id);
  ieIdx++;

  // IE2 - Filling ENB UE S1AP Id
  ie = &s1ENBStatusTfr->protocolIEs.member[ieIdx];
  nbFillTknU8(&(ie->pres), PRSNT_NODEF);
  nbFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
  nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
  nbFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), s1apCon->enb_ue_s1ap_id);
  ieIdx++;

  // IE3 - Filling ENB Status Transfer Transparent Container
  ie = &s1ENBStatusTfr->protocolIEs.member[ieIdx];
  nbFillTknU8(&(ie->pres), PRSNT_NODEF);
  nbFillTknU32(&(ie->id), Sztid_eNB_StatusTfr_TprntCont);
  nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

  ie1 = &ie->value.u.sztENB_StatusTfr_TprntCont;
  nbFillTknU8(&(ie1->pres), PRSNT_NODEF);
  ie1->iE_Extns.noComp.pres = NOTPRSNT;

  numComp = 1;
  nbFillTknU16(&(ie1->bearers_SubjToStatusTfrLst.noComp), numComp);

  if ((cmGetMem(
          enbStatusTransferPdu,
          (numComp * sizeof(SztProtIE_SingleCont_Brs_SubjToStatusTfr_ItemIEs)),
          (Ptr *)&ie1->bearers_SubjToStatusTfrLst.member)) != ROK) {
    NB_LOG_ERROR(&nbCb,
                 "Failed to allocate memory for Brs_SubjToStatusTfr_ItemIEs");
    RETVALUE(RFAILED);
  }

  ie2 = &ie1->bearers_SubjToStatusTfrLst.member[0];
  nbFillTknU8(&(ie2->pres), PRSNT_NODEF);
  nbFillTknU32(&(ie2->id), Sztid_Brs_SubjToStatusTfr_Item);
  nbFillTknU32(&(ie2->criticality), SztCriticalityignoreEnum);

  nbFillTknU8(&(ie2->value.u.sztBrs_SubjToStatusTfr_Item.pres), PRSNT_NODEF);
  nbFillTknU32(&(ie2->value.u.sztBrs_SubjToStatusTfr_Item.e_RAB_ID), 5);
  nbFillTknU8(&(ie2->value.u.sztBrs_SubjToStatusTfr_Item.uL_COUNTvalue.pres),
              PRSNT_NODEF);
  nbFillTknU32(
      &(ie2->value.u.sztBrs_SubjToStatusTfr_Item.uL_COUNTvalue.pDCP_SN), 0);
  nbFillTknU32(&(ie2->value.u.sztBrs_SubjToStatusTfr_Item.uL_COUNTvalue.hFN),
               0);
  ie2->value.u.sztBrs_SubjToStatusTfr_Item.uL_COUNTvalue.iE_Extns.noComp.pres =
      NOTPRSNT;
  nbFillTknU8(&(ie2->value.u.sztBrs_SubjToStatusTfr_Item.dL_COUNTvalue.pres),
              PRSNT_NODEF);
  nbFillTknU32(
      &(ie2->value.u.sztBrs_SubjToStatusTfr_Item.dL_COUNTvalue.pDCP_SN), 0);
  nbFillTknU32(&(ie2->value.u.sztBrs_SubjToStatusTfr_Item.dL_COUNTvalue.hFN),
               0);
  ie2->value.u.sztBrs_SubjToStatusTfr_Item.dL_COUNTvalue.iE_Extns.noComp.pres =
      NOTPRSNT;
  ie2->value.u.sztBrs_SubjToStatusTfr_Item.receiveStatusofULPDCPSDUs.pres =
      NOTPRSNT;
  ie2->value.u.sztBrs_SubjToStatusTfr_Item.iE_Extns.noComp.pres = NOTPRSNT;

  // Pass the constructed PDU back to the caller
  *pdu = enbStatusTransferPdu;

  RETVALUE(ROK);
} // nbBldS1HoEnbStatusTransfer

/* ==================================== */
/* S1 HANDOVER NOTIFY MESSAGE BUILDING  */
/* ==================================== */
/* @brief This function will allocate memory and build the
 *    S1AP: S1 Handover Notify message
 *
 * @details This function allocates the memory for S1AP:
 *    S1 HANDOVER NOTIFY
 *    Message PDU and fills the PDU with proper values
 *
 * Function: nbBldS1HandoverNotify
 *
 *    Processing steps:
 *     -Allocate Memory for S1AP: S1 Handover Notify Message PDU
 *     -Fill the PDU with proper values
 *
 * @param[out] pdu: S1AP: S1 Handover Notify PDU
 *
 * @return  S16
 *    -# Success : ROK
 *    -# Failure : RFAILED
 */
PUBLIC S16 nbBldS1HandoverNotify(S1apPdu **pdu, EnbCb *tgtEnbCb, NbUeCb *ueCb) {
  S1apPdu *s1HoNotifyPdu = NULLP;
  NbS1ConCb *s1apCon = ueCb->s1ConCb;
  SztInitiatingMsg *initMsg;
  SztHovrNtfy *s1HoNotify = NULLP;
  SztProtIE_Field_HovrNtfyIEs *ie;
  U16 numComp;
  S16 ret;
  U32 ieIdx = 0;
  NbTai tai;

  TRC2(nbBldS1HandoverNotify);

  NB_LOG_DEBUG(&nbCb, "Building S1 Handover Notify Message for UE Id: %u",
               ueCb->ueId);

  // Initialize memory control point
  ret = cmAllocEvnt(sizeof(S1apPdu), NB_SZ_MEM_SDU_SIZE, &nbCb.mem,
                    (Ptr *)&s1HoNotifyPdu);
  if (ret != ROK) {
    NB_LOG_ERROR(&nbCb, "cmAllocEvnt failed for s1HoNotifyPdu");
    RETVALUE(RFAILED);
  }
  nbFillTknU8(&(s1HoNotifyPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);

  initMsg = &(s1HoNotifyPdu->pdu.val.initiatingMsg);
  nbFillTknU8(&(initMsg->pres), PRSNT_NODEF);
  nbFillTknU32(&(initMsg->procedureCode), Sztid_HovrNotification);
  nbFillTknU32(&(initMsg->criticality), SztCriticalityignoreEnum);

  /* IEs to be filled in PDU:
   * 1. MME UE S1AP Id
   * 2. ENB UE S1AP Id
   * 3. EUTRAN CGI
   * 4. TAI
   */
  numComp = 4;
  s1HoNotify = &initMsg->value.u.sztHovrNtfy;
  nbFillTknU8(&(s1HoNotify->pres), PRSNT_NODEF);
  nbFillTknU16(&(initMsg->value.u.sztHovrNtfy.protocolIEs.noComp), numComp);

  if ((cmGetMem(s1HoNotifyPdu, (numComp * sizeof(SztProtIE_Field_HovrNtfyIEs)),
                (Ptr *)&s1HoNotify->protocolIEs.member)) != ROK) {
    NB_LOG_ERROR(&nbCb, "Failed to allocate memory for S1HovrNtfyIEs");
    RETVALUE(RFAILED);
  }

  // IE1 - Filling MME UE S1AP Id
  ie = &s1HoNotify->protocolIEs.member[ieIdx];
  nbFillTknU8(&(ie->pres), PRSNT_NODEF);
  nbFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
  nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
  nbFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), s1apCon->mme_ue_s1ap_id);
  ieIdx++;

  // IE2 - Filling ENB UE S1AP Id
  ie = &s1HoNotify->protocolIEs.member[ieIdx];
  nbFillTknU8(&(ie->pres), PRSNT_NODEF);
  nbFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
  nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
  nbFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), s1apCon->enb_ue_s1ap_id);
  ieIdx++;

  // IE3 - Filling  EUTRAN CGI
  ie = &s1HoNotify->protocolIEs.member[ieIdx];
  nbFillTknU8(&(ie->pres), PRSNT_NODEF);
  nbFillTknU32(&(ie->id), Sztid_EUTRAN_CGI);
  nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);

  nbFillTknU8(&(ie->value.u.sztEUTRAN_CGI.pres), PRSNT_NODEF);
  nbSztFillPLMNId(s1HoNotifyPdu, &tgtEnbCb->plmnId,
                  &ie->value.u.sztEUTRAN_CGI.pLMNidentity);
  nbFillTknBStr32(&(ie->value.u.sztEUTRAN_CGI.cell_ID), 28, tgtEnbCb->cell_id);
  ie->value.u.sztEUTRAN_CGI.iE_Extns.noComp.pres = NOTPRSNT;
  ieIdx++;

  // IE4 - Filling  TAI
  ie = &s1HoNotify->protocolIEs.member[ieIdx];
  nbFillTknU8(&(ie->pres), PRSNT_NODEF);
  nbFillTknU32(&(ie->id), Sztid_TAI);
  nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
  nbFillTknU8(&(ie->value.u.sztTAI.pres), PRSNT_NODEF);

  tai.plmnId = tgtEnbCb->plmnId;
  tai.tac = tgtEnbCb->tac;
  nbFillTknU8(&(ie->value.u.sztTAI.pres), PRSNT_NODEF);
  if (nbSztFillPLMNId(s1HoNotifyPdu, &tai.plmnId,
                      &(ie->value.u.sztTAI.pLMNidentity)) != ROK) {
    RETVALUE(RFAILED);
  }
  nbSztFillTAC(tai.tac, s1HoNotifyPdu, &(ie->value.u.sztTAI.tAC));

  // Pass the constructed PDU back to the caller
  *pdu = s1HoNotifyPdu;

  RETVALUE(ROK);
} // nbBldS1HandoverNotify

/* ====================================== */
/* S1 HANDOVER CANCEL MESSAGE BUILDING    */
/* ====================================== */
/* @brief This function will allocate memory and build the
 *    S1AP: S1 Handover Cancel message
 *
 * @details This function allocates the memory for S1AP:
 *    S1 HANDOVER CANCEL
 *    Message PDU and fills the PDU with proper values
 *
 * Function: nbBldS1HandoverCancel
 *
 *    Processing steps:
 *     -Allocate Memory for S1AP: S1 Handover Cancel Message PDU
 *     -Fill the PDU with proper values
 *
 * @param[out] pdu: S1AP: S1 Handover Cancel PDU
 *
 * @return  S16
 *     -# Success : ROK
 *     -# Failure : RFAILED
 */
PUBLIC S16 nbBldS1HandoverCancel(S1apPdu **pdu, NbUeCb *ueCb,
                                 NbUeMsgCause *cause) {
  S1apPdu *s1HoCancelPdu = NULLP;
  NbS1ConCb *s1apCon = ueCb->s1ConCb;
  SztInitiatingMsg *initMsg;
  SztHovrCancel *s1HoCancel = NULLP;
  U16 numComp;
  S16 ret;
  SztProtIE_Field_HovrCancelIEs *ie;
  U32 ieIdx = 0;

  TRC2(nbBldS1HandoverCancel);

  NB_LOG_DEBUG(&nbCb, "Building S1 Handover Cancel Message for UE Id: %u",
               ueCb->ueId);

  // Initialize memory control point
  ret = cmAllocEvnt(sizeof(S1apPdu), NB_SZ_MEM_SDU_SIZE, &nbCb.mem,
                    (Ptr *)&s1HoCancelPdu);
  if (ret != ROK) {
    NB_LOG_ERROR(&nbCb, "cmAllocEvnt failed for s1HoCancelPdu");
    RETVALUE(RFAILED);
  }
  nbFillTknU8(&(s1HoCancelPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);

  initMsg = &(s1HoCancelPdu->pdu.val.initiatingMsg);
  nbFillTknU8(&(initMsg->pres), PRSNT_NODEF);
  nbFillTknU32(&(initMsg->procedureCode), Sztid_HovrCancel);
  nbFillTknU32(&(initMsg->criticality), SztCriticalityrejectEnum);

  /* IEs to be filled in PDU:
   * 1. MME UE S1AP Id
   * 2. ENB UE S1AP Id
   * 3. Cause
   */
  numComp = 3;
  s1HoCancel = &initMsg->value.u.sztHovrCancel;
  nbFillTknU8(&(s1HoCancel->pres), PRSNT_NODEF);
  nbFillTknU16(&(initMsg->value.u.sztHovrCancel.protocolIEs.noComp), numComp);

  if ((cmGetMem(s1HoCancelPdu,
                (numComp * sizeof(SztProtIE_Field_HovrCancelIEs)),
                (Ptr *)&s1HoCancel->protocolIEs.member)) != ROK) {
    NB_LOG_ERROR(&nbCb, "Failed to allocate memory for S1HovrCancelIEs");
    RETVALUE(RFAILED);
  }

  // IE1 - Filling MME UE S1AP Id
  ie = &s1HoCancel->protocolIEs.member[ieIdx];
  nbFillTknU8(&(ie->pres), PRSNT_NODEF);
  nbFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
  nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
  nbFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), s1apCon->mme_ue_s1ap_id);
  ieIdx++;

  // IE2 - Filling ENB UE S1AP Id
  ie = &s1HoCancel->protocolIEs.member[ieIdx];
  nbFillTknU8(&(ie->pres), PRSNT_NODEF);
  nbFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
  nbFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
  nbFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), s1apCon->enb_ue_s1ap_id);
  ieIdx++;

  // IE3 - Filling S1ap Handover Cancel Cause
  ie = &s1HoCancel->protocolIEs.member[ieIdx];
  nbFillTknU8(&(ie->pres), PRSNT_NODEF);
  nbFillTknU32(&(ie->id), Sztid_Cause);
  nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
  nbS1apFillCause(&(ie->value.u.sztCause), cause);

  // Pass the constructed PDU back to the caller
  *pdu = s1HoCancelPdu;

  RETVALUE(ROK);
} // nbBldS1HandoverCancel

/* ====================================== */
/* S1 HANDOVER FAILURE MESSAGE BUILDING   */
/* ====================================== */
/* @brief This function will allocate memory and build the
 *    S1AP: S1 Handover Failure message
 *
 * @details This function allocates the memory for S1AP:
 *    S1 HANDOVER FAILURE
 *    Message PDU and fills the PDU with proper values
 *
 * Function: nbBldS1HandoverFailure
 *
 *    Processing steps:
 *     -Allocate Memory for S1AP: S1 Handover Failure Message PDU
 *     -Fill the PDU with proper values
 *
 * @param[out] pdu: S1AP: S1 Handover Failure PDU
 *
 * @return  S16
 *    -# Success : ROK
 *    -# Failure : RFAILED
 */
PUBLIC S16 nbBldS1HandoverFailure(S1apPdu **pdu, NbUeCb *ueCb,
                                  NbUeMsgCause *cause) {
  S1apPdu *s1HoFailurePdu = NULLP;
  NbS1ConCb *s1apCon = ueCb->s1ConCb;
  SztUnsuccessfulOutcome *unsuccOut;
  SztHovrFail *s1HoFailure = NULLP;
  SztProtIE_Field_HovrFailIEs *ie;
  U16 numComp;
  S16 ret;
  U32 ieIdx = 0;

  TRC2(nbBldS1HandoverFailure);

  NB_LOG_DEBUG(&nbCb,
               "Building S1 Handover Request Failure Message for UE Id: %u",
               ueCb->ueId);

  // Initialize memory control point
  ret = cmAllocEvnt(sizeof(S1apPdu), NB_SZ_MEM_SDU_SIZE, &nbCb.mem,
                    (Ptr *)&s1HoFailurePdu);
  if (ret != ROK) {
    NB_LOG_ERROR(&nbCb, "cmAllocEvnt failed for s1HoFailurePdu");
    RETVALUE(RFAILED);
  }
  nbFillTknU8(&(s1HoFailurePdu->pdu.choice), S1AP_PDU_UNSUCCESSFULOUTCOME);

  unsuccOut = &(s1HoFailurePdu->pdu.val.unsuccessfulOutcome);
  nbFillTknU8(&(unsuccOut->pres), PRSNT_NODEF);
  nbFillTknU32(&(unsuccOut->procedureCode), Sztid_HovrResourceAllocn);
  nbFillTknU32(&(unsuccOut->criticality), SztCriticalityrejectEnum);

  /* IEs to be filled in PDU:
   * 1. MME UE S1AP Id
   * 2. Cause
   */
  numComp = 2;
  s1HoFailure = &unsuccOut->value.u.sztHovrFail;
  nbFillTknU8(&(s1HoFailure->pres), PRSNT_NODEF);
  nbFillTknU16(&(unsuccOut->value.u.sztHovrFail.protocolIEs.noComp), numComp);

  if ((cmGetMem(s1HoFailurePdu, (numComp * sizeof(SztProtIE_Field_HovrFailIEs)),
                (Ptr *)&s1HoFailure->protocolIEs.member)) != ROK) {
    NB_LOG_ERROR(&nbCb, "Failed to allocate memory for S1HovrFailIEs");
    RETVALUE(RFAILED);
  }

  // IE1 - Filling MME UE S1AP Id
  ie = &s1HoFailure->protocolIEs.member[ieIdx];
  nbFillTknU8(&(ie->pres), PRSNT_NODEF);
  nbFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
  nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
  nbFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), s1apCon->mme_ue_s1ap_id);
  ieIdx++;

  // IE2 - Filling S1ap Handover Failure Cause
  ie = &s1HoFailure->protocolIEs.member[ieIdx];
  nbFillTknU8(&(ie->pres), PRSNT_NODEF);
  nbFillTknU32(&(ie->id), Sztid_Cause);
  nbFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
  nbS1apFillCause(&(ie->value.u.sztCause), cause);

  // Pass the constructed PDU back to the caller
  *pdu = s1HoFailurePdu;

  RETVALUE(ROK);
} // nbBldS1HandoverFailure
#endif

/* ================================================= */
/* S1AP ENB CONFIGURATION TRANSFER RSP MESSAGE BUILDING  */
/* ================================================= */
/** @brief This function will allocate memory and build the
 *       S1AP:ENB Configuration Transfer message in response
 *       to MME COnfiguration Transfer .
 *
 * @details This function allocates the memory for S1AP:ENB CONFIGURATION TRANSFER
 *    Message PDU and fills the PDU with proper values.
 *
 * Function: nbBldEnbConfigTransfer
 *
 *       Processing steps:
 *        - Allocate Memory for S1-AP: EnodeB Config Transfer RSP Message PDU.
 *         - Fill the PDU with proper values.
 *
 *@param[out] pdu: S1-AP: ENB Config Transfer PDU.
 * @return  S16
 *      -# Success : ROK
 *       -# Failure : RFAILED
 */
#ifdef MULTI_ENB_SUPPORT
PUBLIC S16 nbBldENbConfigTransferRsp
(
 S1apPdu      **pdu,
 EnbCb        *tgtenbCb,
 EnbCb        *srcenbCb
)
{
   S1apPdu                              *eNBConfigTfrPdu = NULLP;
   U16                                  numComp;
   S16                                  ret;
   SztProtIE_Field_ENBConfigTfrIEs      *ie;
   SztSONConfigTfr                      *sonCont;
   SztTgeteNB_ID                        *ie1;
   SztSrceNB_ID                         *ie2;
   SztSONInform                         *ie3;
   SztProtExtnField_SONConfigTfr_ExtIEs *ie4;
   SztInitiatingMsg                     *initMsg;
   EnbCb                                *tgtEnbCb   = NULLP;  /* enbApp uecb */
   EnbCb                                *prevnbCb   = NULLP;  /* enbApp uecb */
   U32                                  len = 0;
   U8                                   offSet = 0;
   U32                                  idx = 0;
   U8                                   tptAddr[10];
   TRC2(nbtBldS1etupReq);
   /* Initialize memory control point */

   ret = cmAllocEvnt(sizeof(S1apPdu), NB_SZ_MEM_SDU_SIZE, &nbCb.mem,
         (Ptr *)&eNBConfigTfrPdu);
   if(ret != ROK)
   {
      NB_LOG_ERROR(&nbCb, "cmAllocEvnt failed");
      RETVALUE(RFAILED);
   }
   if (srcenbCb == NULLP)
   {
      NB_LOG_ERROR(&nbCb, "srcenbCb is NULL!!\n");
      RETVALUE(RFAILED);
   }
   nbFillTknU8(&(eNBConfigTfrPdu->pdu.choice), SZT_TRGR_INTI_MSG);

   initMsg = &(eNBConfigTfrPdu->pdu.val.initiatingMsg);
   nbFillTknU8(&(initMsg->pres), PRSNT_NODEF);
   nbFillTknU32(&(initMsg->procedureCode), Sztid_eNBConfigTfr);
   nbFillTknU32(&(initMsg->criticality), SztCriticalityignoreEnum);
   nbFillTknU8(&(initMsg->value.u.sztENBConfigTfr.pres), PRSNT_NODEF);

   numComp = 1;
   szFillTknU8(&(eNBConfigTfrPdu->pdu.val.initiatingMsg.value.u.sztENBConfigTfr.pres), PRSNT_NODEF);
   szFillTknU16(&(eNBConfigTfrPdu->pdu.val.initiatingMsg.value.u.sztENBConfigTfr.protocolIEs.noComp), numComp);

   if ((cmGetMem(eNBConfigTfrPdu, (numComp * sizeof( SztProtIE_Field_ENBConfigTfrIEs )),
		(Ptr *)&eNBConfigTfrPdu->pdu.val.initiatingMsg.value.u.sztENBConfigTfr.protocolIEs.member)) !=ROK)
   {
      NB_LOG_ERROR(&nbCb, " nbBldEnbConfigTransfer: cmGetMem failed");
      RETVALUE(RFAILED);
   }

   ie = &initMsg->value.u.sztENBConfigTfr.protocolIEs.member[0];

   // SON COnfiguration Transfer
   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_SONConfigTfrECT);
   szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   szFillTknU8(&(ie->value.u.sztSONConfigTfr.pres), PRSNT_NODEF);
   sonCont = &ie->value.u.sztSONConfigTfr;
   // Target enbID
   ie1 = &(ie->value.u.sztSONConfigTfr.targeteNB_ID);

   szFillTknU8(&(ie1->pres), PRSNT_NODEF);
   szFillTknU8(&(ie1->global_ENB_ID.pres), PRSNT_NODEF);
   /* ENodeBType : Macro NB or Home NB */
   if (smCfgCb.eNodeBType.pres)
   {
      /* Value coming from Test Stub */
      nbSztFillS1eNBId(eNBConfigTfrPdu, nbCb.enbType, srcenbCb->cell_id,
         &(srcenbCb->plmnId),
         &(ie1->global_ENB_ID));
   }
   else
   {
      nbSztFillS1eNBId(eNBConfigTfrPdu, nbCb.enbType, srcenbCb->cell_id,
         &(srcenbCb->plmnId),
         &(ie1->global_ENB_ID));
   }

   ie1->global_ENB_ID.iE_Extns.noComp.pres = NOTPRSNT;
   //TAI
   szFillTknU8(&(ie1->selected_TAI.pres), PRSNT_NODEF);
   nbSztFillPLMNId(eNBConfigTfrPdu,&srcenbCb->plmnId,&ie1->selected_TAI.pLMNidentity);
   nbSztFillTAC(srcenbCb->tac, eNBConfigTfrPdu,&ie1->selected_TAI.tAC);
   ie1->selected_TAI.iE_Extns.noComp.pres = NOTPRSNT;

   // Source eNBID
   ie2 = &(ie->value.u.sztSONConfigTfr.sourceeNB_ID);

   szFillTknU8(&(ie2->pres), PRSNT_NODEF);
   szFillTknU8(&(ie2->global_ENB_ID.pres), PRSNT_NODEF);
   /* ENodeBType : Macro NB or Home NB */
   if (smCfgCb.eNodeBType.pres)
   {
      /* Value coming from Test Stub */
      nbSztFillS1eNBId(eNBConfigTfrPdu, smCfgCb.eNodeBType.val, tgtenbCb->cell_id,
         &(tgtenbCb->plmnId),
         &(ie2->global_ENB_ID));
   }
   else
   {
      nbSztFillS1eNBId(eNBConfigTfrPdu, nbCb.enbType, tgtenbCb->cell_id,
         &(tgtenbCb->plmnId),
         &(ie2->global_ENB_ID));
   }

   ie2->global_ENB_ID.iE_Extns.noComp.pres = NOTPRSNT;
   //TAI
   szFillTknU8(&(ie2->selected_TAI.pres), PRSNT_NODEF);
   nbSztFillPLMNId(eNBConfigTfrPdu,&tgtenbCb->plmnId,&ie2->selected_TAI.pLMNidentity);
   nbSztFillTAC(tgtenbCb->tac, eNBConfigTfrPdu,&ie2->selected_TAI.tAC);
   ie2->selected_TAI.iE_Extns.noComp.pres = NOTPRSNT;

   // SON Information
   SztSONInformReply      *reply = &sonCont->sONInform.val.sONInformReply;
   SztENBX2TLAs           *TLAs;
   szFillTknU8(&sonCont->sONInform.choice, SONINFORM_SONINFORMREPLY);
   reply->pres.pres = PRSNT_NODEF;
   reply->x2TNLConfigInfo.pres.pres = PRSNT_NODEF;
   TLAs = & reply->x2TNLConfigInfo.eNBX2TportLyrAddres;
   szFillTknU16(&TLAs->noComp, 1);
   if ((cmGetMem(eNBConfigTfrPdu, sizeof(SztTportLyrAddr),
               (Ptr*)&TLAs->member)) != ROK)
   {
      cmFreeMem(eNBConfigTfrPdu);
      NB_LOG_ERROR(&nbCb, "Memory allocation failed for Transport Lyr Addr");
      RETVALUE(RFAILED);
   }
   U8 addrOctets[4];
   addrOctets[0] = (nbCb.datAppAddr.u.ipv4TptAddr.address & 0xff000000) >> 24;
   addrOctets[1] = (nbCb.datAppAddr.u.ipv4TptAddr.address & 0x00ff0000) >> 16;
   addrOctets[2] = (nbCb.datAppAddr.u.ipv4TptAddr.address & 0x0000ff00) >> 8;
   addrOctets[3] = (nbCb.datAppAddr.u.ipv4TptAddr.address & 0x000000ff);

   if (nbFillTknStrBSXL(&TLAs->member[0], 32, addrOctets,
                       (CmMemListCp*)eNBConfigTfrPdu) != ROK)
   {
      NB_LOG_ERROR(&nbCb, "Failed to fill IPV4 adress");
      RETVALUE(RFAILED);
   }

   reply->x2TNLConfigInfo.iE_Extns.noComp.pres = NOTPRSNT;
   reply->iE_Extns.noComp.pres = NOTPRSNT;

   /* Fill in the number of IEs included in the message */
   nbFillTknU16(&(initMsg->value.u.sztENBConfigTfr.protocolIEs.noComp), 1);

   /* Pass the constructed PDU back to the caller */
   *pdu = eNBConfigTfrPdu;

   RETVALUE(ROK);
} /* nbBldENbConfigTransferRsp */
#endif


PUBLIC S16 nbPrcPathSwReqAck
(
 NbUeCb *ueCb,
 S1apPdu *pdu
)
{
   S16 ret = RFAILED;
   U32 idx = 0;
   U32 remTeId = 0;
   U32 bearerId = 0;
   SztGTP_TEID    *remTeIdStr = NULLP;
   NbPathSwReqAck *nbpathSwReqAck = NULLP;
   SztSuccessfulOutcome *succMsg  = &pdu->pdu.val.successfulOutcome;
   SztPathSwRqstAckg *pathSwReqAck = &succMsg->value.u.sztPathSwRqstAckg;
   SztProtIE_Field_PathSwRqstAckgIEs *IEs = pathSwReqAck->protocolIEs.member;
   U32  addrMask = 0;
   U8   shiftBits = 0;
   U8   indx = 0;
   U32 numOfErabIds = 0;
   NbUeTunInfo *tunCb = NULLP;
   NbTunDelReq *tunDelReq = NULLP;

   NB_LOG_ENTERFN(&nbCb);

   NB_ALLOC(&nbpathSwReqAck, sizeof(NbPathSwReqAck));
   if (nbpathSwReqAck == NULLP)
   {
      NB_LOG_ERROR(&nbCb, "Failed to allocate memory. cmAllocEvnt failed");
      RETVALUE(RFAILED);
   }
   nbpathSwReqAck->ueId = ueCb->ueId;
   for (idx = 0; idx < pathSwReqAck->protocolIEs.noComp.val; idx++)
   {
      SztProtIE_Field_PathSwRqstAckgIEs *ie = IEs + idx;

      switch(ie->id.val)
      {
         case Sztid_MME_UE_S1AP_ID:
            nbpathSwReqAck->mmeUeS1apId = ie->value.u.sztid_MME_UE_S1AP_ID.val;
            ueCb->s1ConCb->mme_ue_s1ap_id = nbpathSwReqAck->mmeUeS1apId;
            break;
         case Sztid_eNB_UE_S1AP_ID:
            nbpathSwReqAck->enbUeS1apId = ie->value.u.sztENB_UE_S1AP_ID.val;
            ueCb->s1ConCb->enb_ue_s1ap_id = nbpathSwReqAck->enbUeS1apId;
            break;
         case Sztid_E_RABToBeSwedULLst:
	        numOfErabIds = ie->value.u.sztE_RABLst.noComp.val;
            for(indx = 0; indx < numOfErabIds; indx++)
            {
               bearerId = ie->value.u.sztE_RABToBeSwedULLst.\
                                                member[indx].value.u.\
                                                sztE_RABToBeSwedULItem.e_RAB_ID.val;


               remTeIdStr = &(ie->value.u.sztE_RABToBeSwedULLst.\
                                                member[indx].value.u.\
                                                sztE_RABToBeSwedULItem.gTP_TEID);

               shiftBits = (remTeIdStr->len);
               addrMask = 0xFF000000;
               for(indx = 0;indx < remTeIdStr->len; indx++)
               {
                 shiftBits--;
                 remTeId |=
                   ((U32)(remTeIdStr->val[indx] << (8*shiftBits)) & addrMask);
                 addrMask = addrMask >> 8;
               }
            }
            if ( ROK != (cmHashListFind(&(ueCb->tunnInfo), (U32 *)&(bearerId),
              sizeof(U32),0,(PTR *)&tunCb)))
            {
              NB_LOG_ERROR(&nbCb, "tunCb not found for bearerID %d", bearerId);
              RETVALUE(RFAILED);
            }
	        else
	        { /*Update Remote TEID*/
              NB_ALLOC(&tunDelReq, sizeof(NbTunDelReq));
                tunDelReq->bearerId = bearerId;
                tunDelReq->ueId = ueCb->ueId;
                nbIfmDamTunDelReq(tunDelReq);

              tunCb->remTeId = remTeId;
              NB_LOG_DEBUG(&nbCb, "tunCb updated with remTeID%d", remTeId);
              // Create new tunnel
              nbHandleUeIpInfoReq(ueCb->ueId,bearerId, FALSE);
	        }

            break;
         case Sztid_SecurCntxt:
            nbpathSwReqAck->ncc = ie->value.u.sztSecurCntxt.nextHopChainingCount.val;
            cmMemcpy(nbpathSwReqAck->nh, ie->value.u.sztSecurCntxt.nextHopParameter.val,
                    sizeof(nbpathSwReqAck->nh));
            NB_LOG_DEBUG(&nbCb, "Received NCC %d", nbpathSwReqAck->ncc);
            NB_LOG_DEBUG(&nbCb, "Received NH %x", nbpathSwReqAck->nh);
            break;
         default:
            NB_LOG_ERROR(&nbCb, "Invalid Id recieved");
            NB_LOG_EXITFN(&nbCb, RFAILED);
      }
   }

   nbCb.x2HoDone = FALSE;
   nbUiSendPathSwReqAckToUser(nbpathSwReqAck);
   RETVALUE(ROK);
} /* nbPrcResetAck */
#endif
