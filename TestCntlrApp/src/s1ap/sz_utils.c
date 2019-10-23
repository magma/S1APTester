
/**********************************************************************

     Name:     S1AP Layer

     Type:     C source file

     Desc:     C Source code for Utility functions 

     File:     sq_utils.c

     Sid:      sq_utils.c@@/main/4 - Mon Jan 10 22:17:11 2011

     Prg:      sn

**********************************************************************/
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
#endif  /* SZ_FTHA */
#if ((defined SZ_MME) || (defined SZ_ENB))
#include "lsz.h"           /* S1AP LM Interface */
#endif
#include "sz.h"            /* S1AP Layer */
#include "szt_asn.h"
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
#include "szt_asn.x"        /* common ss7 */
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
#include "cm_pasn.x"
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_pftha.x"
#include "cm_psf.x"
#include "sht.x"           /* System Agent */
#endif  /* SZ_FTHA */
#if ((defined SZ_MME) || (defined SZ_ENB))
#include "lsz.x"           /* S1AP LM Interface */
#include "sz.x"            /* S1AP Layer */
#endif
#include "szt_asn.x"

#ifdef __cplusplus
EXTERN "C" {
#endif
PUBLIC S16 szFillTknU32 ARGS((TknU32 *encParam,U32 val));
PUBLIC S16 szFillTknU8 ARGS((TknU8 *encParam,U8 val));
PUBLIC S16 szFillTknU16 ARGS((TknU16 *encParam,U16 val));
#ifdef SZ_ENC_DEC
EXTERN S16 szUtilsGetMsgIdx ARGS((U8 *evnt,S1apPdu *pdu));
EXTERN S16 szGetIE  ARGS((SztS1AP_PDU *pdu, U32 id, TknU8 **ie));
#endif
#ifdef __cplusplus
}
#endif


U16 szElmSize[][SZT_MAX_PROC_ID] = 
{
   {
      /* Msg Id 0 - Sztid_HovrPrep */
      sizeof(SztProtIE_Field_HovrReqdIEs),
      /* Msg Id 1 - Sztid_HovrResourceAllocn */
      sizeof(SztProtIE_Field_HovrRqstIEs),
      /* Msg Id 2 - Sztid_HovrNotification */
      sizeof(SztProtIE_Field_HovrNtfyIEs),
      /* Msg Id 3 - Sztid_PathSwRqst */
      sizeof(SztProtIE_Field_PathSwRqstIEs),
      /* Msg Id 4 - Sztid_HovrCancel */
      sizeof(SztProtIE_Field_HovrCancelIEs),
      /* Msg Id 5 - Sztid_E_RABSetup */
      sizeof(SztProtIE_Field_E_RABSetupRqstIEs),
      /* Msg Id 6 - Sztid_E_RABMdfy */
      sizeof(SztProtIE_Field_E_RABMdfyRqstIEs),
      /* Msg Id 7 - Sztid_E_RABRls cmd */
      sizeof(SztProtIE_Field_E_RABRlsCmmdIEs),
      /* Msg Id 8 - Sztid_E_RABRlsInd */
      sizeof(SztProtIE_Field_E_RABRlsIndIEs),
      /* Msg Id 9 - Sztid_InitCntxtSetup */
      sizeof(SztProtIE_Field_InitCntxtSetupRqstIEs),
      /* Msg Id 10 - Sztid_Pag */
      sizeof(SztProtIE_Field_PagIEs),
      /* Msg Id 11 - Sztid_downlinkNASTport */
      sizeof(SztProtIE_Field_DlnkNASTport_IEs),
      /* Msg Id 12 - Sztid_initialUEMsg */
      sizeof(SztProtIE_Field_InitUEMsg_IEs),
      /* Msg Id 13 - Sztid_uplinkNASTport */
      sizeof(SztProtIE_Field_UlnkNASTport_IEs),
      /* Msg Id 14 - Sztid_Reset */
      sizeof(SztProtIE_Field_ResetIEs),
      /* Msg Id 15 - Sztid_ErrInd */
      sizeof(SztProtIE_Field_ErrIndIEs),
      /* Msg Id 16 - Sztid_NASNonDlvryInd */
      sizeof(SztProtIE_Field_NASNonDlvryInd_IEs),
      /* Msg Id 17 - Sztid_S1Setup */
      sizeof(SztProtIE_Field_S1SetupRqstIEs),
      /* Msg Id 18 - Sztid_UECntxtRlsRqst */
      sizeof(SztProtIE_Field_UECntxtRlsRqst_IEs),
      /* Msg Id 19 - Sztid_DlnkS1cdma2000tunneling */
      sizeof(SztProtIE_Field_DlnkS1cdma2000tunnelingIEs),
      /* Msg Id 20 - Sztid_UlnkS1cdma2000tunneling */
      sizeof(SztProtIE_Field_UlnkS1cdma2000tunnelingIEs),
      /* Msg Id 21 - Sztid_UECntxtModification */
      sizeof(SztProtIE_Field_UECntxtModificationRqstIEs),
      /* Msg Id 22 - Sztid_UECapbltyInfoInd */
      sizeof(SztProtIE_Field_UECapbltyInfoIndIEs),
      /* Msg Id 23 - Sztid_UECntxtRls */
      sizeof(SztProtIE_Field_UECntxtRlsCmmd_IEs),
      /* Msg Id 24 - Sztid_eNBStatusTfr */
      sizeof(SztProtIE_Field_ENBStatusTfrIEs),
      /* Msg Id 25 - Sztid_MMEStatusTfr */
      sizeof(SztProtIE_Field_MMEStatusTfrIEs),
      /* Msg Id 26 - Sztid_DeactvTrace */
      sizeof(SztProtIE_Field_DeactvTraceIEs),
      /* Msg Id 27 - Sztid_TraceStart */
      sizeof(SztProtIE_Field_TraceStartIEs),
      /* Msg Id 28 - Sztid_TraceFailInd */
      sizeof(SztProtIE_Field_TraceFailIndIEs),
      /* Msg Id 29 - Sztid_ENBConfigUpd */
      sizeof(SztProtIE_Field_ENBConfigUpdIEs),
      /* Msg Id 30 - Sztid_MMEConfigUpd */
      sizeof(SztProtIE_Field_MMEConfigUpdIEs),
      /* Msg Id 31 - Sztid_LocRprtngCntrl */
      sizeof(SztProtIE_Field_LocRprtngCntrlIEs),
      /* Msg Id 32 - Sztid_LocRprtngFailInd */
      sizeof(SztProtIE_Field_LocRprtngFailIndIEs),
      /* Msg Id 33 - Sztid_LocReport */
      sizeof(SztProtIE_Field_LocReportIEs),
      /* Msg Id 34 - Sztid_OverloadStart */
      sizeof(SztProtIE_Field_OverloadStartIEs),
      /* Msg Id 35 - Sztid_OverloadStop */
      sizeof(SztProtIE_Field_OverloadStopIEs),
      /* Msg Id 36 - Sztid_WriteReplaceWarning */
      sizeof(SztProtIE_Field_WriteReplaceWarningRqstIEs),
      /* Msg Id 37 - Sztid_eNBDirectInformTfr */
      sizeof(SztProtIE_Field_ENBDirectInformTfrIEs),
      /* Msg Id 38 - Sztid_MMEDirectInformTfr */
      sizeof(SztProtIE_Field_MMEDirectInformTfrIEs),
      /* Msg Id 39 -Sztid_PrivMsg */ 
      sizeof(SztPrivIE_Field_PrivMsgIEs),
      /* Msg Id 40 -Sztid_eNBConfigTfr */
      sizeof(SztProtIE_Field_ENBConfigTfrIEs),
      /* Msg Id 41- Sztid_MMEConfigTfr */
      sizeof(SztProtIE_Field_MMEConfigTfrIEs),
      /* Msg Id 42-Sztid_CellTrafficTrace */
      sizeof(SztProtIE_Field_CellTrafficTraceIEs)
#ifndef S1AP_REL8A0
      ,
      /* Msg Id 43-Sztid_Kill */
      sizeof(SztProtIE_Field_KillRqstIEs),
      /* Msg Id 44-Sztid_DownlinkUeAssociatedLPPaTprt */
      sizeof(SztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs),
      /* Msg Id 45-Sztid_UplinkUeAssociatedLPPaTprt */
      sizeof(SztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs),
      /* Msg Id 46-Sztid_DownlinkNonUeAssociatedLPPaTprt */
      sizeof(SztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs),
      /* Msg Id 47-Sztid_UplinkNonUeAssociatedLPPaTprt */
      sizeof(SztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs)
#endif

   },

   {
      /* Msg Id 0 - Sztid_HovrPrep */
      sizeof(SztProtIE_Field_HovrCmmdIEs),
      /* Msg Id 1 - Sztid_HovrResourceAllocn */
      sizeof(SztProtIE_Field_HovrRqstAckgIEs),
      /* Msg Id 2 - Sztid_HovrNotification */
      0,
      /* Msg Id 3 - Sztid_PathSwRqst */
      sizeof(SztProtIE_Field_PathSwRqstAckgIEs),
      /* Msg Id 4 - Sztid_HovrCancel */
      sizeof(SztProtIE_Field_HovrCancelAckgIEs),
      /* Msg Id 5 - Sztid_E_RABSetup */
      sizeof(SztProtIE_Field_E_RABSetupRespIEs),
      /* Msg Id 6 - Sztid_E_RABMdfy */
      sizeof(SztProtIE_Field_E_RABMdfyRespIEs),
      /* Msg Id 7 - Sztid_E_RABRls cmd */
      sizeof(SztProtIE_Field_E_RABRlsRespIEs),
      /* Msg Id 8 - Sztid_E_RABRlsInd */
      0,
      /* Msg Id 9 - Sztid_InitCntxtSetup */
      sizeof(SztProtIE_Field_InitCntxtSetupRespIEs),
      /* Msg Id 10 - Sztid_Pag */
      0,
      /* Msg Id 11 - Sztid_downlinkNASTport */
      0,
      /* Msg Id 12 - Sztid_initialUEMsg */
      0,
      /* Msg Id 13 - Sztid_uplinkNASTport */
      0,
      /* Msg Id 14 - Sztid_Reset */
      sizeof(SztProtIE_Field_ResetAckgIEs),
      /* Msg Id 15 - Sztid_ErrInd */
      0,
      /* Msg Id 16 - Sztid_NASNonDlvryInd */
      0,
      /* Msg Id 17 - Sztid_S1Setup */
      sizeof(SztProtIE_Field_S1SetupRespIEs),
      /* Msg Id 18 - Sztid_UECntxtRlsRqst */
      0,
      /* Msg Id 19 - Sztid_DlnkS1cdma2000tunneling */
      0,
      /* Msg Id 20 - Sztid_UlnkS1cdma2000tunneling */
      0,
      /* Msg Id 21 - Sztid_UECntxtModification */
      sizeof(SztProtIE_Field_UECntxtModificationRespIEs),
      /* Msg Id 22 - Sztid_UECapbltyInfoInd */
      0,
      /* Msg Id 23 - Sztid_UECntxtRls */
      sizeof(SztProtIE_Field_UECntxtRlsComplete_IEs),
      /* Msg Id 24 - Sztid_eNBStatusTfr */
      0,
      /* Msg Id 25 - Sztid_MMEStatusTfr */
      0,
      /* Msg Id 26 - Sztid_DeactvTrace */
      0,
      /* Msg Id 27 - Sztid_TraceStart */
      0,
      /* Msg Id 28 - Sztid_TraceFailInd */
      0,
      /* Msg Id 29 - Sztid_ENBConfigUpd */
      sizeof(SztProtIE_Field_ENBConfigUpdAckgIEs),
      /* Msg Id 30 - Sztid_MMEConfigUpd */
      sizeof(SztProtIE_Field_MMEConfigUpdFailIEs),
      /* Msg Id 31 - Sztid_LocRprtngCntrl */
      0,
      /* Msg Id 32 - Sztid_LocRprtngFailInd */
      0,
      /* Msg Id 33 - Sztid_LocReport */
      0,
      /* Msg Id 34 - Sztid_OverloadStart */
      0,
      /* Msg Id 35 - Sztid_OverloadStop */
      0,
      /* Msg Id 36 - Sztid_WriteReplaceWarning */
      sizeof(SztProtIE_Field_WriteReplaceWarningRespIEs),
      /* Msg Id 37 - Sztid_eNBDirectInformTfr */
      0,
      /* Msg Id 38 - Sztid_MMEDirectInformTfr */
      0,
      /* Msg Id 39 -Sztid_PrivMsg */
      0,
      /* Msg Id 40 - Sztid_eNBConfigTfr */
      0,
      /* Msg Id 41 - Sztid_MMEConfigTfr*/
      0,
      /* Msg Id 42 - Sztid_CellTrafficTrace  */
      0
#ifndef S1AP_REL8A0
      ,
      /* Msg Id 43-Sztid_Kill */
      sizeof(SztProtIE_Field_KillRespIEs),
      /* Msg Id 44-Sztid_DownlinkUeAssociatedLPPaTprt */
      0,
      /* Msg Id 45-Sztid_UplinkUeAssociatedLPPaTprt */
      0,
      /* Msg Id 46-Sztid_DownlinkNonUeAssociatedLPPaTprt */
      0,
      /* Msg Id 47-Sztid_UplinkNonUeAssociatedLPPaTprt */
      0
#endif
   },

   {
      /* Msg Id 0 - Sztid_HovrPrep */
      sizeof(SztProtIE_Field_HovrPrepFailIEs),
      /* Msg Id 1 - Sztid_HovrResourceAllocn */
      sizeof(SztProtIE_Field_HovrFailIEs),
      /* Msg Id 2 - Sztid_HovrNotification */
      0,
      /* Msg Id 3 - Sztid_PathSwRqst */
      sizeof(SztProtIE_Field_PathSwRqstFailIEs),
      /* Msg Id 4 - Sztid_HovrCancel */
      0,
      /* Msg Id 5 - Sztid_E_RABSetup */
      0,
      /* Msg Id 6 - Sztid_E_RABMdfy */
      0,
      /* Msg Id 7 - Sztid_E_RABRls cmd */
      0,
      /* Msg Id 8 - Sztid_E_RABRlsInd */
      0,
      /* Msg Id 9 - Sztid_InitCntxtSetup */
      sizeof(SztProtIE_Field_InitCntxtSetupFailIEs),
      /* Msg Id 10 - Sztid_Pag */
      0,
      /* Msg Id 11 - Sztid_downlinkNASTport */
      0,
      /* Msg Id 12 - Sztid_initialUEMsg */
      0,
      /* Msg Id 13 - Sztid_uplinkNASTport */
      0,
      /* Msg Id 14 - Sztid_Reset */
      0,
      /* Msg Id 15 - Sztid_ErrInd */
      0,
      /* Msg Id 16 - Sztid_NASNonDlvryInd */
      0,
      /* Msg Id 17 - Sztid_S1Setup */
      sizeof(SztProtIE_Field_S1SetupFailIEs),
      /* Msg Id 18 - Sztid_UECntxtRlsRqst */
      0,
      /* Msg Id 19 - Sztid_DlnkS1cdma2000tunneling */
      0,
      /* Msg Id 20 - Sztid_UlnkS1cdma2000tunneling */
      0,
      /* Msg Id 21 - Sztid_UECntxtModification */
      sizeof(SztProtIE_Field_UECntxtModificationFailIEs),
      /* Msg Id 22 - Sztid_UECapbltyInfoInd */
      0,
      /* Msg Id 23 - Sztid_UECntxtRls */
      0,
      /* Msg Id 24 - Sztid_eNBStatusTfr */
      0,
      /* Msg Id 25 - Sztid_MMEStatusTfr */
      0,
      /* Msg Id 26 - Sztid_DeactvTrace */
      0,
      /* Msg Id 27 - Sztid_TraceStart */
      0,
      /* Msg Id 28 - Sztid_TraceFailInd */
      0,
      /* Msg Id 29 - Sztid_ENBConfigUpd */
      sizeof(SztProtIE_Field_ENBConfigUpdFailIEs),
      /* Msg Id 30 - Sztid_MMEConfigUpd */
      sizeof(SztProtIE_Field_MMEConfigUpdFailIEs),
      /* Msg Id 31 - Sztid_LocRprtngCntrl */
      0,
      /* Msg Id 32 - Sztid_LocRprtngFailInd */
      0,
      /* Msg Id 33 - Sztid_LocReport */
      0,
      /* Msg Id 34 - Sztid_OverloadStart */
      0,
      /* Msg Id 35 - Sztid_OverloadStop */
      0,
      /* Msg Id 36 - Sztid_WriteReplaceWarning */
      0,
      /* Msg Id 37 - Sztid_eNBDirectInformTfr */
      0,
      /* Msg Id 38 - Sztid_MMEDirectInformTfr */
      0,
       /* Msg Id 39 -Sztid_PrivMsg */
      0,
      /* Msg Id 40 - Sztid_eNBConfigTfr */
      0,
      /* Msg Id 41 - Sztid_MMEConfigTfr*/
      0,
      /* Msg Id 42 - Sztid_CellTrafficTrace  */
      0
#ifndef S1AP_REL8A0
      ,
      /* Msg Id 43-Sztid_Kill */
      0,
      /* Msg Id 44-Sztid_DownlinkUeAssociatedLPPaTprt */
      0,
      /* Msg Id 45-Sztid_UplinkUeAssociatedLPPaTprt */
      0,
      /* Msg Id 46-Sztid_DownlinkNonUeAssociatedLPPaTprt */
      0,
      /* Msg Id 47-Sztid_UplinkNonUeAssociatedLPPaTprt */
      0
#endif

   }
};

/*
 *
 *      Fun:   szUtilsGetMsgIdx
 *
 *      Desc:  Retrieve message index
 *
 *      Ret:   ROK   - ok
 *
 *      Notes: None.
 *
 *      File:  sq_utils.c
 *
 */
#ifdef ANSI
PUBLIC S16 szUtilsGetMsgIdx
(
U8 *msgIdx,
S1apPdu *pdu
)
#else
PUBLIC S16 szUtilsGetMsgIdx(msgIdx,pdu)
U8 *msgIdx;
S1apPdu *pdu;
#endif
{
   U8 msgType;
   U32 procCode;

   TRC2(szUtilsGetMsgIdx)

   if(pdu->pdu.choice.pres == TRUE)
   {
      msgType  = pdu->pdu.choice.val;
   }
   else
   {
      *msgIdx = SZT_MSG_ID_NO_DATA;
      RETVALUE(ROK);
   }
   switch(msgType)
   {
      case S1AP_PDU_INITIATINGMSG:
         if(pdu->pdu.val.initiatingMsg.pres.pres == TRUE)
         {
            procCode = pdu->pdu.val.initiatingMsg.procedureCode.val;
            *msgIdx = SzMsgId[procCode][msgType];
         }
         else 
         { 
            *msgIdx = SZT_MSG_ID_NO_MSG;
         }
         break;
      case S1AP_PDU_SUCCESSFULOUTCOME:
         if(pdu->pdu.val.successfulOutcome.pres.pres == TRUE)
         {
            procCode = pdu->pdu.val.successfulOutcome.procedureCode.val;
            *msgIdx = SzMsgId[procCode][msgType];
         }
         else
         {
            *msgIdx = SZT_MSG_ID_NO_MSG;
         }
         break;
      case S1AP_PDU_UNSUCCESSFULOUTCOME:
        if(pdu->pdu.val.unsuccessfulOutcome.pres.pres == TRUE)
        {
           procCode = pdu->pdu.val.unsuccessfulOutcome.procedureCode.val;
           *msgIdx = SzMsgId[procCode][msgType];
        }
         else
         {
            *msgIdx = SZT_MSG_ID_NO_MSG;
         }
         break;
   }
   RETVALUE(ROK);
}

/*
 *
 *      Fun:   szGetIE
 *
 *      Desc:  Retrieve message index
 *
 *      Ret:   ROK   - ok
 *
 *      Notes: None.
 *
 *      File:  sq_utils.c
 *
 */
#ifdef ANSI
PUBLIC S16 szGetIE
(
 SztS1AP_PDU *pdu,
 U32     id,
 TknU8   **ie
)
#else
PUBLIC S16 szGetIE (pdu, id, ie)
 SztS1AP_PDU *pdu;
 U32     id;
 TknU8   **ie;
#endif
{
   TknU8   *currStr;    /* Start definition */
   TknU8   *startStr;   /* Start event structure */
   U8      choiceType;
   U16     numComp;
   U16     recIdx;
   U32     recId;
   U32     procCode;
   U16     size;

   TRC2(szGetIE)
         
   /* Initialize the return pointer Tkn to NOTPRSNT */
   *ie = NULLP;
   
   numComp = 0;
   recIdx = 0; 

   if(pdu->choice.pres != PRSNT_NODEF)
   {
      RETVALUE(ROK);
   }
 
   choiceType = pdu->choice.val;

   /* Make start string point to the message in the PDU   */
   switch(choiceType)
   {
      case S1AP_PDU_INITIATINGMSG:
            if (pdu->val.initiatingMsg.pres.pres != PRSNT_NODEF)
               RETVALUE(ROK);

            startStr  = (TknU8 *)(&(pdu->val.initiatingMsg.value.u));
            procCode  = pdu->val.initiatingMsg.procedureCode.val;
            break;

      case S1AP_PDU_SUCCESSFULOUTCOME:
            if (pdu->val.successfulOutcome.pres.pres != PRSNT_NODEF)
               RETVALUE(ROK);

            startStr  = (TknU8 *)(&(pdu->val.successfulOutcome.value.u));
            procCode  = pdu->val.successfulOutcome.procedureCode.val;
            break;
         
      default: 
            if ((pdu->val.unsuccessfulOutcome.pres.pres != PRSNT_NODEF) ||
               (choiceType != S1AP_PDU_UNSUCCESSFULOUTCOME))
               RETVALUE(ROK);

            startStr  = (TknU8 *)(&(pdu->val.unsuccessfulOutcome.value.u));
            procCode  = pdu->val.unsuccessfulOutcome.procedureCode.val;
            break;
   }

   if (((TknU8 *)startStr)->pres == PRSNT_NODEF)
   {
      /* Increment it by TknU8 for TknPres */
      currStr  = (TknU8 *) ((PTR)startStr + sizeof(TknU8));
   }
   else
      RETVALUE(ROK);
    
   if (((TknU16 *)(currStr))->pres == PRSNT_NODEF)
   {
      /* get the Number of IEs received : noComp */
      numComp = ((TknU16 *)(currStr))->val;
   }
        
   /*  Increment currStr by TknU16 for skipping noComp */
   currStr = (TknU8 *)((PTR)currStr + sizeof(TknU16));

   currStr = *(TknU8**)currStr;

   while (recIdx < numComp) 
   {
      startStr = currStr;

      if (((TknPres *)currStr)->pres == PRSNT_NODEF)
      {   
         /* Increment it by TknU8 for TknPres */
         currStr  = (TknU8 *) ((PTR)currStr + sizeof(TknPres));

         /* Get the received Id  */
         recId  = ((SztProtIE_ID *)currStr)->val; 

         /* Compare the two Ids */
         if (recId == id)
         {
            startStr = (TknU8 *) ((PTR)currStr + sizeof(SztProtIE_ID) + sizeof(SztCriticality));

            *ie = startStr;
            break;
         }
      }

      size = szElmSize[choiceType][procCode];
      currStr  = (TknU8 *) ((PTR)startStr + size);
      recIdx++;
   }

   RETVALUE(ROK);
} /* end of szGetIE */

#if ((defined SZ_MME) || (defined SZ_ENB))  /*   ndef SZ_ENC_DEC */
/* 
 * 
 *      Fun:   szDbFillResetAck
 *
 *      Desc:  Fill Reset Acknowledge
 *
 *      Ret:   ROK   - ok
 *
 *      Notes: None.
 *
 *      File:  sq_utils.c
 *
 */
#ifdef ANSI
PUBLIC S16 szDbFillResetAck
(
S1apPdu *pdu,
S1apPdu **rstAckPdu,
Mem mem,
U8 *cause
)
#else
PUBLIC S16 szDbFillResetAck(pdu,rstAckPdu,mem, cause)
S1apPdu *pdu;
S1apPdu **rstAckPdu;
Mem mem;
U8 *cause;
#endif
{
   S16 ret = RFAILED;
   SztProtIE_Field_ResetAckgIEs *ie;
   SztProtIE_SingleCont_UE_assocLogS1_ConItemResAck *ie1;
   TknU8 *rstIe;
   S16 numCon;
   S16 idx;

   TRC2(szDbFillResetAck)

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)rstAckPdu);
   if (ret != ROK)
   {
      /*sz008.301: Kwork fix, Returning the specific cause */
      *cause = SZT_CAUSE_MEM_ALLOC_FAIL;
      RETVALUE(RFAILED);
   }

   szFillTknU8(&((*rstAckPdu)->pdu.choice), SZT_TRGR_SUCCESS_OUTCOME);
   szFillTknU8(&((*rstAckPdu)->pdu.val.successfulOutcome.pres),PRSNT_NODEF);
   szFillTknU32(&((*rstAckPdu)->pdu.val.successfulOutcome.procedureCode),Sztid_Reset);
   szFillTknU32(&((*rstAckPdu)->pdu.val.successfulOutcome.criticality),SztCriticalityrejectEnum);
   szFillTknU8(&((*rstAckPdu)->pdu.val.successfulOutcome.value.u.sztResetAckg.pres),PRSNT_NODEF);

   szGetIE(&(pdu->pdu),SZT_ELM_ID_RESET_TYPE,&rstIe);
   /* sz008.301: fix for Kwork */
   if(rstIe == NULLP)
   {
      *cause = SZT_CAUSE_MSING_MNDTRY_PARM;
      SZ_FREE_SDU(*rstAckPdu);
      RETVALUE(RFAILED);
   }

   /* Partial reset */
   if(((SztResetTyp *)rstIe)->choice.val == SZT_PARTIAL_RESET)
   {
      szFillTknU16(&((*rstAckPdu)->pdu.val.successfulOutcome.value.u.sztResetAckg.protocolIEs.noComp),1);

      if ((cmGetMem(&((*rstAckPdu)->memCp), sizeof(SztProtIE_Field_ResetAckgIEs),
          (Ptr *)&((*rstAckPdu)->pdu.val.successfulOutcome.value.\
                       u.sztResetAckg.protocolIEs.member))) !=ROK)
      {
         /*sz008.301: Returning the specific cause */
         *cause = SZT_CAUSE_MEM_ALLOC_FAIL;
         SZ_FREE_SDU(*rstAckPdu);
         RETVALUE(RFAILED);
      }

      ie = (*rstAckPdu)->pdu.val.successfulOutcome.value.u.sztResetAckg.protocolIEs.member;
   
      /* Fill IE container */
      szFillTknU8(&(ie->pres),PRSNT_NODEF);
      szFillTknU32(&(ie->id),SZT_ELM_ID_UE_ASSOC_LOG_S1_CON_LST_RES_ACK);
      szFillTknU32(&(ie->criticality),SztCriticalityignoreEnum);
      szFillTknU16(&(ie->value.u.sztUE_assocLogS1_ConLstResAck.noComp),1);

      numCon = ((SztResetTyp *)rstIe)->val.partOfS1_Intf.noComp.val;

      if ((cmGetMem(&((*rstAckPdu)->memCp), numCon * sizeof(SztProtIE_SingleCont_UE_assocLogS1_ConItemResAck), 
          (Ptr *)&ie->value.u.sztUE_assocLogS1_ConLstResAck.member)) !=ROK)
      { 
         /*sz008.301: Returning the specific cause */
         *cause = SZT_CAUSE_MEM_ALLOC_FAIL;
         SZ_FREE_SDU(*rstAckPdu);
         RETVALUE(RFAILED);
      }

      for(idx = 0; idx < numCon; idx++)
      {
         ie1 = &ie->value.u.sztUE_assocLogS1_ConLstResAck.member[idx];

         szFillTknU8(&(ie1->pres),PRSNT_NODEF);
         szFillTknU32(&(ie1->id),SZT_ELM_ID_UE_ASSOC_LOG_S1_CON_ITM);
         szFillTknU32(&(ie1->criticality),SztCriticalityignoreEnum);
         szFillTknU8(&(ie1->value.u.sztUE_assocLogS1_ConItem.pres),PRSNT_NODEF);
         szFillTknU32(&(ie1->value.u.sztUE_assocLogS1_ConItem.mME_UE_S1AP_ID),\
                       ((SztResetTyp *)rstIe)->val.partOfS1_Intf.member[idx].value.u.sztUE_assocLogS1_ConItem.mME_UE_S1AP_ID.val);
         szFillTknU32(&(ie1->value.u.sztUE_assocLogS1_ConItem.eNB_UE_S1AP_ID),\
                       ((SztResetTyp *)rstIe)->val.partOfS1_Intf.member[idx].value.u.sztUE_assocLogS1_ConItem.eNB_UE_S1AP_ID.val);
         ie1->value.u.sztUE_assocLogS1_ConItem.iE_Extns.noComp.pres = FALSE;
      }
   }
   else 
   {
      szFillTknU16(&((*rstAckPdu)->pdu.val.successfulOutcome.value.u.sztResetAckg.protocolIEs.noComp),0);
   }

   RETVALUE(ROK);
}

/* 
 * 
 *      Fun:   szDbFillErrInd
 *
 *      Desc:  Fill Error Indication
 *
 *      Ret:   ROK   - ok
 *
 *      Notes: None.
 *
 *      File:  sq_utils.c
 *
 */
#ifdef ANSI
PUBLIC S16 szDbFillErrInd
(
S1apPdu *pdu,
U8  causeChoice,
U32 causeVal,
S1apPdu **errIndPdu,
Mem mem,
CmPAsnErr *asnErr
)
#else
PUBLIC S16 szDbFillErrInd(pdu, causeChoice, causeVal, errIndPdu, mem, asnErr)
S1apPdu *pdu;
U8  causeChoice;
U32 causeVal;
S1apPdu **errIndPdu;
Mem mem;
CmPAsnErr *asnErr;
#endif
{
   SztProtIE_Field_ErrIndIEs *ie = NULLP;
   TknU8 *mmeS1apId = NULLP;
   TknU8 *enbS1apId = NULLP;

   U16 numComp = 0;
   S16 ret = 0;
#ifdef CM_PASN_CRIT_HANDL
   SztCriticalityDiag_IE_Item *ie1 = NULLP;
   U8   idx;
   U32  procCode;
   U32  criticality;
#endif /* CM_PASN_CRIT_HANDL */

   TRC2(szDbFillErrInd);

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)errIndPdu);
   if (ret != ROK)
   {
      RETVALUE(RFAILED);
   }

   szFillTknU8(&((*errIndPdu)->pdu.choice), SZT_TRGR_INTI_MSG);
   szFillTknU8(&((*errIndPdu)->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&((*errIndPdu)->pdu.val.initiatingMsg.procedureCode), Sztid_ErrInd);
   szFillTknU32(&((*errIndPdu)->pdu.val.initiatingMsg.criticality), SztCriticalityignoreEnum);

   /* Filling of ErrInd structure */
   szFillTknU8(&((*errIndPdu)->pdu.val.initiatingMsg.value.u.sztErrInd.pres), PRSNT_NODEF);

   numComp = 1;

   if(pdu != NULLP)
   {
      szGetIE(&pdu->pdu,Sztid_MME_UE_S1AP_ID, &mmeS1apId);
      szGetIE(&pdu->pdu,Sztid_eNB_UE_S1AP_ID, &enbS1apId);
   }

   if (mmeS1apId != NULLP)
   {
      numComp++;
   }
   if (enbS1apId != NULLP)
   {
      numComp++;
   }

#ifdef CM_PASN_CRIT_HANDL
   if(asnErr->ieCount)
   {
      numComp++;
   }
#endif /* CM_PASN_CRIT_HANDL */

   szFillTknU16(&((*errIndPdu)->pdu.val.initiatingMsg.value.u.sztErrInd.protocolIEs.noComp), numComp);

   if ((cmGetMem((*errIndPdu), (numComp * sizeof(SztProtIE_Field_ErrIndIEs)),
               (Ptr *)&((*errIndPdu)->pdu.val.initiatingMsg.value.u.sztErrInd.protocolIEs.member))) !=ROK)
   {
      SZ_FREE_SDU(*errIndPdu);
      RETVALUE(RFAILED);
   }
   
   /* Reset the numComp parameter */
   numComp = 0;

   /* sz001.201 Correction in ordering of Error Indication PDU IEs */
   /* Fill MME IE if present */ 
   if (mmeS1apId != NULLP)
   {
      ie = &((*errIndPdu)->pdu.val.initiatingMsg.value.u.sztErrInd.protocolIEs.member[numComp++]);

      szFillTknU8(&(ie->pres),PRSNT_NODEF);
      szFillTknU32(&(ie->id),Sztid_MME_UE_S1AP_ID);
      szFillTknU32(&(ie->criticality),SztCriticalityignoreEnum);
      szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID),((TknU32 *)mmeS1apId)->val);
   }

   /* Fill eNB IE if present */ 
   if (enbS1apId != NULLP)
   {
      ie = &((*errIndPdu)->pdu.val.initiatingMsg.value.u.sztErrInd.protocolIEs.member[numComp++]);

      szFillTknU8(&(ie->pres),PRSNT_NODEF);
      szFillTknU32(&(ie->id),Sztid_eNB_UE_S1AP_ID);
      szFillTknU32(&(ie->criticality),SztCriticalityignoreEnum);
      szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID),((TknU32 *)enbS1apId)->val);
   }

   /* Fill cause */
   ie = &((*errIndPdu)->pdu.val.initiatingMsg.value.u.sztErrInd.protocolIEs.member[numComp++]);

   /* Fill cause IE container */
   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_Cause);
   szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   szFillTknU8(&(ie->value.u.sztCause.choice), causeChoice);

   switch(causeChoice)
   {
      case CAUSE_RADIONW:
         szFillTknU32(&(ie->value.u.sztCause.val.radioNw), causeVal);
         break;

      case CAUSE_TRANSPORT:
         szFillTknU32(&(ie->value.u.sztCause.val.transport), causeVal);
         break;

      case CAUSE_NAS:
         szFillTknU32(&(ie->value.u.sztCause.val.nas), causeVal);
         break;

      case CAUSE_PROTOCOL:
         szFillTknU32(&(ie->value.u.sztCause.val.protocol), causeVal);
         break;

      case CAUSE_MISC:
         szFillTknU32(&(ie->value.u.sztCause.val.misc), causeVal);
         break;

      default:
         break;
   }

   /* Fill the criticality diagnostics depnding on the no of error Ies */
#ifdef CM_PASN_CRIT_HANDL
   /* Check the ieCount and restrict it to the MAX value if it is more than
    * MAX value to avoid array out of bound
    */
   if(asnErr->ieCount > CM_PASN_MAX_ERR_IE)
   {
      asnErr->ieCount = CM_PASN_MAX_ERR_IE;
   }

   if(asnErr->ieCount && (NULLP != pdu))
   {
      /* Get the procedure code and criticality from PDU */
      procCode    = pdu->pdu.val.initiatingMsg.procedureCode.val;
      criticality = pdu->pdu.val.initiatingMsg.criticality.val;

      ie = &((*errIndPdu)->pdu.val.initiatingMsg.value.u.sztErrInd.protocolIEs.member[numComp++]);

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_CriticalityDiag);
      szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
      szFillTknU8(&(ie->value.u.sztCriticalityDiag.pres), PRSNT_NODEF);

      szFillTknU32(&(ie->value.u.sztCriticalityDiag.procedureCode), procCode);
      szFillTknU32(&(ie->value.u.sztCriticalityDiag.triggeringMsg), SztTrgMsginitiating_messageEnum);
      szFillTknU32(&(ie->value.u.sztCriticalityDiag.procedureCriticality), criticality);

      /* Get the no of components, the no of components is equal to error Ies */
      numComp = asnErr->ieCount;
      szFillTknU16(&(ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.noComp), numComp);

      /* Allocate memory for the members */
      if ((cmGetMem((*errIndPdu), (numComp * sizeof(SztCriticalityDiag_IE_Item)),
                  (Ptr *)&(ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.member))) != ROK)
      {
         SZ_FREE_SDU(*errIndPdu);
         RETVALUE(RFAILED);
      }

      /* Fill the each reported error Ies with its criticality and ID */
      for(idx = 0; idx < numComp; idx++)
      {
         ie1 = &ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.member[idx];
         szFillTknU8(&(ie1->pres), PRSNT_NODEF);
         szFillTknU32(&(ie1->iECriticality), asnErr->ieInfo[idx].criticality);
         szFillTknU32(&(ie1->iE_ID), asnErr->ieInfo[idx].ieId);
         szFillTknU32(&(ie1->typeOfErr), asnErr->ieInfo[idx].errType);
         ie1->iE_Extns.noComp.pres = NOTPRSNT;
      }
   }
#endif /* CM_PASN_CRIT_HANDL */

   RETVALUE(ROK);
} /* End of szDbFillErrInd */


/* 
 * 
 *      Fun:   szDbFillInitCxtSetupFail
 *
 *      Desc:  Fill Error Indication
 *
 *      Ret:   ROK   - ok
 *
 *      Notes: None.
 *
 *      File:  sq_utils.c
 *
 */
#ifdef ANSI
PUBLIC S16 szDbFillInitCxtSetupFail
(
S1apPdu *pdu,
U8  causeChoice,
U32 causeVal,
S1apPdu **initCxtSetupFail,
Mem mem,
CmPAsnErr *asnErr
)
#else
PUBLIC S16 szDbFillInitCxtSetupFail(pdu,causeChoice,causeVal,initCxtSetupFail,mem,asnErr)
S1apPdu *pdu;
U8  causeChoice;
U32 causeVal;
S1apPdu **initCxtSetupFail;
Mem mem;
CmPAsnErr *asnErr;
#endif
{
   SztProtIE_Field_InitCntxtSetupFailIEs *ie;
   S16 numComp = 0;
   TknU8 *mmeS1apId = NULLP;
   TknU8 *enbS1apId = NULLP;
   S16 ret = 0;
#ifdef CM_PASN_CRIT_HANDL
   SztCriticalityDiag_IE_Item *ie1 = NULLP;
   U8    idx;
#endif /* CM_PASN_CRIT_HANDL */

   TRC2(szDbFillInitCxtSetupFail)

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)initCxtSetupFail);
   if (ret != ROK)
   {
      RETVALUE(RFAILED);
   }

   szFillTknU8(&((*initCxtSetupFail)->pdu.choice), S1AP_PDU_UNSUCCESSFULOUTCOME);
   szFillTknU8(&((*initCxtSetupFail)->pdu.val.unsuccessfulOutcome.pres),PRSNT_NODEF);
   szFillTknU32(&((*initCxtSetupFail)->pdu.val.unsuccessfulOutcome.procedureCode),Sztid_InitCntxtSetup);
   szFillTknU32(&((*initCxtSetupFail)->pdu.val.unsuccessfulOutcome.criticality),SztCriticalityrejectEnum);

   /* Filling of UE cntxt mod fail structure */
   szFillTknU8(&((*initCxtSetupFail)->pdu.val.unsuccessfulOutcome.value.u.sztInitCntxtSetupFail.pres),PRSNT_NODEF);

   numComp = 3;

   /* Increment the no of components incase of error Ie */
#ifdef CM_PASN_CRIT_HANDL
   if(asnErr->ieCount)
   {
      numComp++;
   }
#endif /* CM_PASN_CRIT_HANDL */

   szGetIE(&pdu->pdu,Sztid_MME_UE_S1AP_ID,&mmeS1apId);
   szGetIE(&pdu->pdu,Sztid_eNB_UE_S1AP_ID,&enbS1apId);

   szFillTknU16(&((*initCxtSetupFail)->pdu.val.unsuccessfulOutcome.value.u.sztInitCntxtSetupFail.protocolIEs.noComp),numComp);
   /* sz002.301: Corrected the structure given for sizeof while allocating 
    * the memory*/

   if ((cmGetMem((*initCxtSetupFail), numComp*sizeof(SztProtIE_Field_InitCntxtSetupFailIEs),
       (Ptr *)&((*initCxtSetupFail)->pdu.val.unsuccessfulOutcome.value.u.sztInitCntxtSetupFail.protocolIEs.member))) !=ROK)
   {  
      SZ_FREE_SDU(*initCxtSetupFail);
      RETVALUE(RFAILED);
   }

   /* Reset the numComp parameter */
   numComp = 0;

   /* Fill MME IE */ 
   if(NULLP != mmeS1apId)
   {
      ie = &((*initCxtSetupFail)->pdu.val.unsuccessfulOutcome.value.u.sztInitCntxtSetupFail.protocolIEs.member[numComp++]);

      szFillTknU8(&(ie->pres),PRSNT_NODEF);
      szFillTknU32(&(ie->id),Sztid_MME_UE_S1AP_ID);
      szFillTknU32(&(ie->criticality),SztCriticalityignoreEnum);
      szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID),((TknU32 *)mmeS1apId)->val);
   }

   /* Fill eNB IE */ 
   if(NULLP != enbS1apId)
   {
      ie = &((*initCxtSetupFail)->pdu.val.unsuccessfulOutcome.value.u.sztInitCntxtSetupFail.protocolIEs.member[numComp++]);

      szFillTknU8(&(ie->pres),PRSNT_NODEF);
      szFillTknU32(&(ie->id),Sztid_eNB_UE_S1AP_ID);
      szFillTknU32(&(ie->criticality),SztCriticalityignoreEnum);
      szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID),((TknU32 *)enbS1apId)->val);
   }

   /* Fill cause IE container */

   ie = &((*initCxtSetupFail)->pdu.val.unsuccessfulOutcome.value.u.sztInitCntxtSetupFail.protocolIEs.member[numComp++]);
   
   szFillTknU8(&(ie->pres),PRSNT_NODEF);
   szFillTknU32(&(ie->id),Sztid_Cause);
   szFillTknU32(&(ie->criticality),SztCriticalityignoreEnum);
   szFillTknU8(&(ie->value.u.sztCause.choice),causeChoice);
   szFillTknU32(&(ie->value.u.sztCause.val.radioNw),causeVal);

   /* Fill the criticality diagnostics depending on the no of error Ies */
#ifdef CM_PASN_CRIT_HANDL
   if(asnErr->ieCount)
   {
      ie = &((*initCxtSetupFail)->pdu.val.unsuccessfulOutcome.value.u.sztInitCntxtSetupFail.protocolIEs.member[numComp++]);

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_CriticalityDiag);
      szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
      szFillTknU8(&(ie->value.u.sztCriticalityDiag.pres), PRSNT_NODEF);

      /* Get the no of components, the no of components is equal to error Ies */
      numComp = asnErr->ieCount;
      szFillTknU16(&(ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.noComp), numComp);

      /* Allocate memory for the members */
      if ((cmGetMem((*initCxtSetupFail), (numComp * sizeof(SztCriticalityDiag_IE_Item)),
                  (Ptr *)&(ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.member))) != ROK)
      {
         SZ_FREE_SDU(*initCxtSetupFail);
         RETVALUE(RFAILED);
      }

      /* Fill the each reported error Ies with its criticality and ID */
      for(idx = 0; idx < numComp; idx++)
      {
         ie1 = &ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.member[idx];
         szFillTknU8(&(ie1->pres), PRSNT_NODEF);
         szFillTknU32(&(ie1->iECriticality), asnErr->ieInfo[idx].criticality);
         szFillTknU32(&(ie1->iE_ID), asnErr->ieInfo[idx].ieId);
         szFillTknU32(&(ie1->typeOfErr), asnErr->ieInfo[idx].errType);
         ie1->iE_Extns.noComp.pres = NOTPRSNT;
      }
   }
#endif /* CM_PASN_CRIT_HANDL */

   RETVALUE(ROK);
} /* End of szDbFillInitCxtSetupFail */

/* 
 * 
 *      Fun:   szDbFillUeCxtModFail
 *
 *      Desc:  Fill Error Indication
 *
 *      Ret:   ROK   - ok
 *
 *      Notes: None.
 *
 *      File:  sq_utils.c
 *
 */
#ifdef ANSI
PUBLIC S16 szDbFillUeCxtModFail
(
S1apPdu *pdu,
U8  causeChoice,
U32 causeVal,
S1apPdu **ueCxtModFailPdu,
Mem mem,
CmPAsnErr *asnErr
)
#else
PUBLIC S16 szDbFillUeCxtModFail(pdu,causeChoice,causeVal,ueCxtModFailPdu,mem,asnErr)
S1apPdu *pdu;
U8  causeChoice;
U32 causeVal;
S1apPdu **ueCxtModFailPdu;
Mem mem;
CmPAsnErr *asnErr;
#endif
{
   SztProtIE_Field_UECntxtModificationFailIEs *ie;
   U16 numComp = 0;
   TknU8 *mmeS1apId = NULLP;
   TknU8 *enbS1apId = NULLP;
   S16 ret = 0;
#ifdef CM_PASN_CRIT_HANDL
   SztCriticalityDiag_IE_Item *ie1 = NULLP;
   U8   idx;
#endif /* CM_PASN_CRIT_HANDL */

   TRC2(szDbFillUeCxtModFail)

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)ueCxtModFailPdu);
   if (ret != ROK)
   {
      RETVALUE(RFAILED);
   }

   szFillTknU8(&((*ueCxtModFailPdu)->pdu.choice), S1AP_PDU_UNSUCCESSFULOUTCOME);
   szFillTknU8(&((*ueCxtModFailPdu)->pdu.val.unsuccessfulOutcome.pres),PRSNT_NODEF);
   szFillTknU32(&((*ueCxtModFailPdu)->pdu.val.unsuccessfulOutcome.procedureCode),Sztid_UECntxtModification);
   szFillTknU32(&((*ueCxtModFailPdu)->pdu.val.unsuccessfulOutcome.criticality),SztCriticalityrejectEnum);

   /* Filling of UE cntxt mod fail structure */
   szFillTknU8(&((*ueCxtModFailPdu)->pdu.val.unsuccessfulOutcome.value.u.sztUECntxtModificationFail.pres),PRSNT_NODEF);

   numComp = 3;

#ifdef CM_PASN_CRIT_HANDL
   if(asnErr->ieCount)
   {
      numComp++;
   }
#endif /* CM_PASN_CRIT_HANDL */

   szGetIE(&pdu->pdu,Sztid_MME_UE_S1AP_ID,&mmeS1apId);
   szGetIE(&pdu->pdu,Sztid_eNB_UE_S1AP_ID,&enbS1apId);

   szFillTknU16(&((*ueCxtModFailPdu)->pdu.val.unsuccessfulOutcome.value.u.sztUECntxtModificationFail.protocolIEs.noComp),numComp);

   if ((cmGetMem((*ueCxtModFailPdu), numComp*sizeof(SztProtIE_Field_UECntxtModificationFailIEs), 
       (Ptr *)&((*ueCxtModFailPdu)->pdu.val.unsuccessfulOutcome.value.u.sztUECntxtModificationFail.protocolIEs.member))) !=ROK)
   {
      SZ_FREE_SDU(*ueCxtModFailPdu);
      RETVALUE(RFAILED);
   }
   
   /* Reset the numComp parameter */
   numComp = 0;

   /* Fill MME IE if present */ 
   if(NULLP != mmeS1apId)
   {
      ie = &((*ueCxtModFailPdu)->pdu.val.unsuccessfulOutcome.value.u.sztUECntxtModificationFail.protocolIEs.member[numComp++]);

      szFillTknU8(&(ie->pres),PRSNT_NODEF);
      szFillTknU32(&(ie->id),Sztid_MME_UE_S1AP_ID);
      szFillTknU32(&(ie->criticality),SztCriticalityignoreEnum);
      szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID),((TknU32 *)mmeS1apId)->val);
   }

   /* Fill eNB IE if present */ 
   if(NULLP != enbS1apId)
   {
      ie = &((*ueCxtModFailPdu)->pdu.val.unsuccessfulOutcome.value.u.sztUECntxtModificationFail.protocolIEs.member[numComp++]); 
      szFillTknU8(&(ie->pres),PRSNT_NODEF);
      szFillTknU32(&(ie->id),Sztid_eNB_UE_S1AP_ID);
      szFillTknU32(&(ie->criticality),SztCriticalityignoreEnum);
      szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID),((TknU32 *)enbS1apId)->val);
   }

   /* Fill cause IE container */

   ie = &((*ueCxtModFailPdu)->pdu.val.unsuccessfulOutcome.value.u.sztUECntxtModificationFail.protocolIEs.member[numComp++]);
   
   szFillTknU8(&(ie->pres),PRSNT_NODEF);
   szFillTknU32(&(ie->id),Sztid_Cause);
   szFillTknU32(&(ie->criticality),SztCriticalityignoreEnum);
   szFillTknU8(&(ie->value.u.sztCause.choice),causeChoice);
   szFillTknU32(&(ie->value.u.sztCause.val.radioNw),causeVal);

   /* Fill the criticality diagnostics depnding on the no of error Ies */
#ifdef CM_PASN_CRIT_HANDL
   if(asnErr->ieCount)
   {
      ie = &((*ueCxtModFailPdu)->pdu.val.unsuccessfulOutcome.value.u.sztUECntxtModificationFail.protocolIEs.member[numComp++]);

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_CriticalityDiag);
      szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
      szFillTknU8(&(ie->value.u.sztCriticalityDiag.pres), PRSNT_NODEF);

      /* Get the no of components, the no of components is equal to error Ies */
      numComp = asnErr->ieCount;
      szFillTknU16(&(ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.noComp), numComp);

      /* Allocate memory for the members */
      if ((cmGetMem((*ueCxtModFailPdu), (numComp * sizeof(SztCriticalityDiag_IE_Item)),
                  (Ptr *)&(ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.member))) != ROK)
      {
         SZ_FREE_SDU(*ueCxtModFailPdu);
         RETVALUE(RFAILED);
      }

      /* Fill the each reported error Ies with its criticality and ID */
      for(idx = 0; idx < numComp; idx++)
      {
         ie1 = &ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.member[idx];
         szFillTknU8(&(ie1->pres), PRSNT_NODEF);
         szFillTknU32(&(ie1->iECriticality), asnErr->ieInfo[idx].criticality);
         szFillTknU32(&(ie1->iE_ID), asnErr->ieInfo[idx].ieId);
         szFillTknU32(&(ie1->typeOfErr), asnErr->ieInfo[idx].errType);
         ie1->iE_Extns.noComp.pres = NOTPRSNT;
      }
   }
#endif /* CM_PASN_CRIT_HANDL */

   RETVALUE(ROK);
} /* End of szDbFillUeCxtModFail */

/*
 *
 *      Fun:   szValidateSdus
 *
 *      Desc:  Validate the Sdus
 *
 *      Ret:   ROK   - ok
 *
 *      Notes: None.
 *
 *      File:  sq_utils.c
 *
 */
#ifdef ANSI
PUBLIC S16 szValidateSdus
(
S1apPdu     *pdu,          /* Connection sdus */
U8          primType,      /* Primitive type */
U8          *evnt          /* Event type */
)
#else
PUBLIC S16 szValidateSdus (pdu, primType,evnt)
S1apPdu     *pdu;          /* Connection sdus */
U8          primType;      /* Primitive type */
U8          *evnt;         /* Event type */
#endif
{

   TRC2(szValidateSdus);

   if(!pdu)
      RETVALUE(RFAILED);

   szUtilsGetMsgIdx(evnt, pdu);

   switch(primType)
   {
      case SZ_UI_CON_REQ:
      {
         switch (*evnt)
         {
            case SZT_MSG_ID_INIT_UE_MSG:
            case SZT_MSG_ID_DL_NAS_TPT:
            case SZT_MSG_ID_HO_REQ:
            case SZT_MSG_ID_PATH_SWTCH_REQ:
               break;
            default:
               RETVALUE(RFAILED);
         }
         break;
      }
      
      case SZ_UI_CON_RSP:
      {
         switch (*evnt)
         {
            case SZT_MSG_ID_CXT_SETUP_REQ:
            case SZT_MSG_ID_DL_NAS_TPT:
            case SZT_MSG_ID_UL_NAS_TPT:
            case SZT_MSG_ID_HO_REQ_ACK:
            case SZT_MSG_ID_PATH_SWTCH_REQ_ACK:
               break;
            default:
               RETVALUE(RFAILED);
         }
         break;
      }

      case SZ_UI_REL_REQ:
      {
         switch (*evnt)
         {
            case SZT_MSG_ID_UE_CXT_REL_CMD:
            case SZT_MSG_ID_INIT_CXT_SETUP_FAIL:
            case SZT_MSG_ID_NO_DATA:
            case SZT_MSG_ID_HO_FAIL:
            case SZT_MSG_ID_PATH_SWTCH_REQ_FAIL:
               break;
            default:
               RETVALUE(RFAILED);
         }
         break;
      }

      case SZ_UI_REL_RSP:
      {
         switch (*evnt)
         {
            case SZT_MSG_ID_UE_CXT_REL_CMPL:
               break;
            default:
               RETVALUE(RFAILED);
         }
         break;
      }

      case SZ_UI_DAT_REQ:
      {
         switch (*evnt)
         {
            case SZT_MSG_ID_CXT_SETUP_REQ:
            case SZT_MSG_ID_CXT_SETUP_RSP:
            case SZT_MSG_ID_E_RAB_BRR_SETUP_REQ:
            case SZT_MSG_ID_E_RAB_BRR_SETUP_RSP:
            case SZT_MSG_ID_E_RAB_BRR_MOD_REQ:
            case SZT_MSG_ID_E_RAB_BRR_MOD_RSP:
            case SZT_MSG_ID_E_RAB_BRR_REL_REQ:
            case SZT_MSG_ID_E_RAB_BRR_REL_CMD:
            case SZT_MSG_ID_E_RAB_BRR_REL_CMPLT:
            case SZT_MSG_ID_UE_CXT_MOD_REQ:
            case SZT_MSG_ID_UE_CXT_MOD_RSP:
            case SZT_MSG_ID_UE_CXT_MOD_FAIL:
            case SZT_MSG_ID_ERR_IND:
            case SZT_MSG_ID_UE_CXT_REL_REQ:
            case SZT_MSG_ID_DL_NAS_TPT:
            case SZT_MSG_ID_UL_NAS_TPT:
            case SZT_MSG_ID_NAS_NON_DEL_IND:
            case SZT_MSG_ID_HO_REQD:
            case SZT_MSG_ID_HO_CMD:
            case SZT_MSG_ID_HO_PREP_FAIL:
            case SZT_MSG_ID_HO_NTFY:
            case SZT_MSG_ID_HO_CANCEL:
            case SZT_MSG_ID_HO_CANCEL_ACK:
            case SZT_MSG_ID_ENB_STA_TRFR:
            case SZT_MSG_ID_MME_STA_TRFR:
            case SZT_MSG_ID_DEACTV_TRACE:
            case SZT_MSG_ID_TRACE_START:
            case SZT_MSG_ID_TRACE_FAIL_IND:
            case SZT_MSG_ID_LOC_REPORT_CNTRL:
            case SZT_MSG_ID_LOC_REPORT_FAIL_IND:
            case SZT_MSG_ID_LOC_REPORT:
            case SZT_MSG_ID_UPLNK_CDMA_TUNNL:
            case SZT_MSG_ID_DNLNK_CDMA_TUNNL:
            case SZT_MSG_ID_UE_CAP_INFO:
            case SZT_MSG_ID_CELL_TRAFFIC_TRACE:
            case SZT_MSG_ID_DNLNK_UE_ASSOC_LPPA_TPRT:
            case SZT_MSG_ID_UPLNK_UE_ASSOC_LPPA_TPRT:
            /* sz005.301: Added the Initial context setup fail */
            case SZT_MSG_ID_INIT_CXT_SETUP_FAIL:
               break;
            default:
               RETVALUE(RFAILED);
         }
         break;
      }

   }
   RETVALUE(ROK);
} /* end of szValidateSdus */


/*
*
*       Fun:   szUtilsAllocConId
*
*       Desc:  Called to allocate connection identifier
*
*       Ret:   ok:     ROK
*              failed: RFAILED
*
*       Notes: None
*
*       File:  sq_utils.c
*
*/
#ifdef ANSI
PUBLIC S16 szUtilsAllocConId
(
U32 *connId
)
#else
PUBLIC S16 szUtilsAllocConId(connId)
U32 *connId;
#endif
{
   UConnId    prevId;
   UConnId    id;
   S16        found;
   SzPeerCb  *conCb = NULLP;

   TRC2(szUtilsAllocConId);

   prevId = szCb.lclConCntr;
   id = 0;

#ifdef SZ_ENB
   if (szCb.nodeCb.nodeType == LSZ_NODE_ENB)
   {
      id = ((++szCb.lclConCntr) % SZ_MAX_ENBID);
   }
#endif

#ifdef LSZV1
   if(szCb.nodeCb.nodeType == LSZ_NODE_GW)
   {
      id = ((++szCb.lclConCntr) % SZ_MAX_GWID);
   }
#endif

   if (id == 0)
   {
      id = ++szCb.lclConCntr;
   }

   while (id != prevId)
   {
      found = cmHashListFind(&szCb.lclConCp, (U8 *)&id, sizeof (UConnId),
                  0, (PTR *)&conCb);

      if (found == RFAILED)
      {
         szCb.lclConCntr = id;
         break;
      }

#ifdef SZ_ENB
      if (szCb.nodeCb.nodeType == LSZ_NODE_ENB)
      {
         id = ((id + 1) % SZ_MAX_ENBID);
      }
#endif

#ifdef LSZV1
      if (szCb.nodeCb.nodeType == LSZ_NODE_GW)
      {
         id = ((id + 1) % SZ_MAX_GWID);
      }
#endif

      if (id == 0)
      {
         id++;
      }
   }

   *connId = id;

   RETVALUE(ROK);
}
#endif

/*                                     
*
*       Fun:   szFillTknU8
*
*       Desc:  Fills  the TknU8 structure with the specified value
*
*       Ret:   ROK       - ok
*
*       Notes: None
*
*       File:  sq_utils.c
*
*/
#ifdef ANSI
PUBLIC S16  szFillTknU8
(
TknU8  *encParam,
U8     val
)
#else
PUBLIC S16 szFillTknU8(encParam, val)
TknU8  *encParam;
U8     val;
#endif
{
  TRC2(szFillTknU8)
  encParam->pres = PRSNT_NODEF;
  encParam->val  = val;
  RETVALUE(ROK);
} /* end of szFillTknU8 */

/*                                     
*
*       Fun:   szFillTknU16
*
*       Desc:  Fill a TknU16 structure
*
*       Ret:   ROK       - ok
*
*       Notes: None
*
*       File:  sz_msgfn.c
*
*/

#ifdef ANSI
PUBLIC S16  szFillTknU16
(
TknU16  *encParam,
U16     val
)
#else
PUBLIC S16 szFillTknU16(encParam, val)
TknU16  *encParam;
U16     val;
#endif
{
  TRC2(szFillTknU16)
  encParam->pres = PRSNT_NODEF;
  encParam->val  = val;
  RETVALUE(ROK);
} /* end of szFillTknU16 */

/*                                     
*
*       Fun:   szFillTknU32
*
*       Desc:  Fills the TknU32 structure
*
*       Ret:   RA_ROK       - ok
*
*       Notes: None
*
*       File:  sq_utils.c
*
*/

#ifdef ANSI
PUBLIC S16  szFillTknU32
(
TknU32  *encParam,
U32     val
)
#else
PUBLIC S16 szFillTknU32(encParam, val)
TknU32  *encParam;
U32     val;
#endif
{
   TRC2(szFillTknU32)
   encParam->pres = PRSNT_NODEF;
   encParam->val  = val;
   RETVALUE(ROK);
} /* end of szFillTknU32 */

#if ((defined SZ_MME) || (defined SZ_ENB))  /*   ndef SZ_ENC_DEC */
/*
*
*       Fun:   szDbFillResetFrmPdu
*
*       Desc:  Call handler to fill reset message
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_sztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 szDbFillResetFrmPdu
(
S1apPdu *pdu,
S1apPdu **rstPdu,
Mem mem
)
#else
PUBLIC S16 szDbFillResetFrmPdu(pdu, rstPdu, mem)
S1apPdu *pdu;
S1apPdu **rstPdu;
Mem mem;
#endif
{
   S1apPdu *szRstPdu = NULLP;
   TknU8   *rstIe;
   S16  ret;
   U16  numComp;
   U16  i;

   SztProtIE_Field_ResetIEs *ie;
   SztProtIE_SingleCont_UE_assocLogS1_ConItemRes *ie1;

   TRC2(szDbFillResetFrmPdu);

   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&szRstPdu);
   if (ret != ROK)
   {
      SZ_FREE_SDU(szRstPdu);
      RETVALUE(RFAILED);
   }

   szFillTknU8(&(szRstPdu->pdu.choice), SZT_TRGR_INTI_MSG);
   szFillTknU8(&(szRstPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(szRstPdu->pdu.val.initiatingMsg.procedureCode),
         Sztid_Reset);
   szFillTknU32(&(szRstPdu->pdu.val.initiatingMsg.criticality),
         SztCriticalityrejectEnum);
   szFillTknU8(&(szRstPdu->pdu.val.initiatingMsg.value.u.sztReset.pres),
         PRSNT_NODEF);

   /* Filling 2 mandatory headers */

   numComp = pdu->pdu.val.initiatingMsg.value.u.sztReset.protocolIEs.noComp.val;
   szFillTknU16(&(szRstPdu->pdu.val.initiatingMsg.value.u.sztReset.protocolIEs.noComp), numComp);

   if ((cmGetMem(szRstPdu, (numComp * sizeof(SztProtIE_Field_ResetIEs)),
               (Ptr *)&szRstPdu->pdu.val.initiatingMsg.value.u.sztReset.protocolIEs.member)) !=ROK)
   {
      SZ_FREE_SDU(szRstPdu);
      RETVALUE(RFAILED);
   }

   /* IE1 - Filling cause */
   szGetIE(&(pdu->pdu),Sztid_Cause,&rstIe);

   if(rstIe == NULLP)
   {
      SZ_FREE_SDU(szRstPdu);
      RETVALUE(RFAILED);
   }

   ie = &szRstPdu->pdu.val.initiatingMsg.value.u.sztReset.protocolIEs.member[0];

   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_Cause);
   szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   szFillTknU8(&(ie->value.u.sztCause.choice),((SztCause *)rstIe)->choice.val);
   szFillTknU32(&(ie->value.u.sztCause.val.radioNw),((SztCause *)rstIe)->val.radioNw.val);

   /* IE2 - Filling reset type */
   szGetIE(&(pdu->pdu),Sztid_ResetTyp,&rstIe);
   if(rstIe == NULLP)
   {
      SZ_FREE_SDU(szRstPdu);
      RETVALUE(RFAILED);
   }
   ie = &szRstPdu->pdu.val.initiatingMsg.value.u.sztReset.protocolIEs.member[1];

   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_ResetTyp);
   szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);


   szFillTknU8(&(ie->value.u.sztResetTyp.choice),((SztResetTyp *)rstIe)->choice.val);
   numComp = ((SztResetTyp *)rstIe)->val.partOfS1_Intf.noComp.val;
   szFillTknU16(&(ie->value.u.sztResetTyp.val.partOfS1_Intf.noComp), numComp);

   if(ie->value.u.sztResetTyp.choice.val == SZT_FULL_RESET)
   {
      szFillTknU32(&(ie->value.u.sztResetTyp.val.s1_Intf),SztResetAllreset_allEnum);
   }
   else
   {
      /* Allocate memory */
      if (cmGetMem(szRstPdu, (numComp * sizeof(SztProtIE_SingleCont_UE_assocLogS1_ConItemRes)),
               (Ptr *)&(ie->value.u.sztResetTyp.val.partOfS1_Intf.member)) != ROK)
      {
         SZ_FREE_SDU(szRstPdu);
         RETVALUE(RFAILED);
      }  

      for(i = 0; i< numComp; i++)
      {
         ie1 = &(ie->value.u.sztResetTyp.val.partOfS1_Intf.member[i]);

         szFillTknU8(&(ie1->pres), PRSNT_NODEF);
         szFillTknU32(&(ie1->id),SZT_ELM_ID_UE_ASSOC_LOG_S1_CON_ITM);
         szFillTknU32(&(ie1->criticality),SztCriticalityignoreEnum);
         szFillTknU8(&(ie1->value.u.sztUE_assocLogS1_ConItem.pres),
               ((SztResetTyp *)rstIe)->val.partOfS1_Intf.member[i].value.u.sztUE_assocLogS1_ConItem.pres.pres);
         if(((SztResetTyp *)rstIe)->val.partOfS1_Intf.member[i].value.u.sztUE_assocLogS1_ConItem.mME_UE_S1AP_ID.pres)
            szFillTknU32(&(ie1->value.u.sztUE_assocLogS1_ConItem.mME_UE_S1AP_ID),
                  ((SztResetTyp *)rstIe)->val.partOfS1_Intf.member[i].value.u.sztUE_assocLogS1_ConItem.mME_UE_S1AP_ID.val);
         if(((SztResetTyp *)rstIe)->val.partOfS1_Intf.member[i].value.u.sztUE_assocLogS1_ConItem.eNB_UE_S1AP_ID.pres)
            szFillTknU32(&(ie1->value.u.sztUE_assocLogS1_ConItem.eNB_UE_S1AP_ID),
                  ((SztResetTyp *)rstIe)->val.partOfS1_Intf.member[i].value.u.sztUE_assocLogS1_ConItem.eNB_UE_S1AP_ID.val);
         ie1->value.u.sztUE_assocLogS1_ConItem.iE_Extns.noComp.pres = FALSE;
      }
   }

   *rstPdu = szRstPdu; 

   RETVALUE(ROK);

} /* End of szDbFillResetFrmPdu */

/*
*
*       Fun:   szUtilsGetConCb  
*
*       Desc:  Called to locate respective conCb
*
*       Ret:   ok:     ROK
*              failed: RFAILED
*
*       Notes: None
*
*       File:  sz_li.c
*
*/

#ifdef ANSI
PUBLIC S16 szUtilsGetConCb 
(
SzPeerCb *peerCb,
S1apPdu  *pdu,
SzConCb  **conCb
)
#else
PUBLIC S16 szUtilsGetConCb(peerCb, pdu, conCb)
SzPeerCb *peerCb;
S1apPdu  *pdu;
SzConCb  **conCb;
#endif
{
#if ((defined SZ_MME) || (defined SZ_ENB))
   SztUE_S1AP_IDs  *ueS1apId = NULLP;
#endif

#ifdef SZ_ENB
   TknU8           *eNbIdTkn = NULLP;
#endif
   U8    evnt = 0;

   TRC2(szUtilsGetConCb)

   SZDBGP(DBGMASK_LI, (szCb.init.prntBuf, 
     "szUtilsGetConCb : Received dedicated procedure\n"));

   szUtilsGetMsgIdx(&evnt, pdu);

#ifdef SZ_ENB
   if(peerCb->nodeType == LSZ_NODE_MME)
   /* if (szCb.nodeCb.nodeType == LSZ_NODE_ENB) */
   {
      /* Get eNBId from S1AP Msg, if it exsits */
      szGetIE(&(pdu->pdu), Sztid_eNB_UE_S1AP_ID, &eNbIdTkn);

      if (eNbIdTkn == NULLP)
      {
         szGetIE(&(pdu->pdu), Sztid_UE_S1AP_IDs, (TknU8 **)&ueS1apId);

         if (ueS1apId != NULLP)
         {
            switch (ueS1apId->choice.val)
            {
               case UE_S1AP_IDS_UE_S1AP_ID_PAIR:
                  eNbIdTkn = (TknU8*)&ueS1apId->val.uE_S1AP_ID_pair.eNB_UE_S1AP_ID;
                  break;

               default:
                  break;
            }
         }          
      }

      if (eNbIdTkn != NULLP)
      {
         cmHashListFind(&peerCb->conRefLst, 
                       (U8*) &(((SztENB_UE_S1AP_ID *)eNbIdTkn)->val),
                       sizeof(U32), 0, (PTR*)conCb);
      }                 
   }
#endif
 

    RETVALUE(ROK);
} /* end of szUtilsGetConCb */


/* 
 * 
 *      Fun:   szDbFillHovrPrepFail
 *
 *      Desc:  Fill Error Indication
 *
 *      Ret:   ROK   - ok
 *
 *      Notes: None.
 *
 *      File:  sq_utils.c
 *
 */
#ifdef ANSI
PUBLIC S16 szDbFillHovrPrepFail
(
S1apPdu *pdu,
U8  causeChoice,
U32 causeVal,
S1apPdu **errIndPdu,
Mem mem,
CmPAsnErr *asnErr
)
#else
PUBLIC S16 szDbFillHovrPrepFail(pdu, causeChoice, causeVal, errIndPdu, mem, asnErr)
S1apPdu *pdu;
U8  causeChoice;
U32 causeVal;
S1apPdu **errIndPdu;
Mem mem;
CmPAsnErr *asnErr;
#endif
{
   TknU8 *mmeS1apId = NULLP;
   TknU8 *enbS1apId = NULLP;

   U16 numComp = 0;
   S16 ret = 0;

   SztHovrPrepFail *failMsg = NULLP;
   SztProtIE_Field_HovrPrepFailIEs *ie = NULLP;
#ifdef CM_PASN_CRIT_HANDL
   SztCriticalityDiag_IE_Item *ie1 = NULLP;
   U8    idx;
#endif /* CM_PASN_CRIT_HANDL */

   TRC2(szDbFillHovrPrepFail);


   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)errIndPdu);
   if (ret != ROK)
   {
      RETVALUE(RFAILED);
   }

   /* Building respective message */
   szFillTknU8(&((*errIndPdu)->pdu.choice), S1AP_PDU_UNSUCCESSFULOUTCOME);
   szFillTknU8(&((*errIndPdu)->pdu.val.unsuccessfulOutcome.pres), PRSNT_NODEF);
   szFillTknU32(&((*errIndPdu)->pdu.val.unsuccessfulOutcome.procedureCode),
         Sztid_HovrPrep);
   szFillTknU32(&((*errIndPdu)->pdu.val.unsuccessfulOutcome.criticality),
         SztCriticalityignoreEnum);

   /* Filling of failure message */
   failMsg = &((*errIndPdu)->pdu.val.unsuccessfulOutcome.value.u.sztHovrPrepFail);
   szFillTknU8(&(failMsg->pres), PRSNT_NODEF);

   if(pdu != NULLP)
   {
      szGetIE(&pdu->pdu,Sztid_MME_UE_S1AP_ID, &mmeS1apId);
      szGetIE(&pdu->pdu,Sztid_eNB_UE_S1AP_ID, &enbS1apId);
   }

   if (mmeS1apId != NULLP)
   {
      numComp++;
   }
   if (enbS1apId != NULLP)
   {
      numComp++;
   }

#ifdef CM_PASN_CRIT_HANDL
   if(asnErr->ieCount)
   {
      numComp++;
   }
#endif /* CM_PASN_CRIT_HANDL */

   szFillTknU16(&(failMsg->protocolIEs.noComp), numComp);

   if ((cmGetMem((*errIndPdu), (numComp * sizeof(SztProtIE_Field_HovrPrepFailIEs)),
               (Ptr *)&(failMsg->protocolIEs.member))) != ROK)
   {
      SZ_FREE_SDU(*errIndPdu);
      RETVALUE(RFAILED);
   }

   /* make the number of comp as zero */
   numComp = 0;

   /* Fill MME IE if present */ 
   if (mmeS1apId != NULLP)
   {
      ie = &(failMsg->protocolIEs.member[numComp++]);

      szFillTknU8(&(ie->pres),PRSNT_NODEF);
      szFillTknU32(&(ie->id),Sztid_MME_UE_S1AP_ID);
      szFillTknU32(&(ie->criticality),SztCriticalityignoreEnum);
      szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID),((TknU32 *)mmeS1apId)->val);
   }

   /* Fill eNB IE if present */ 
   if (enbS1apId != NULLP)
   {
      ie = &(failMsg->protocolIEs.member[numComp++]);

      szFillTknU8(&(ie->pres),PRSNT_NODEF);
      szFillTknU32(&(ie->id),Sztid_eNB_UE_S1AP_ID);
      szFillTknU32(&(ie->criticality),SztCriticalityignoreEnum);
      szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID),((TknU32 *)enbS1apId)->val);
   }

   /* Fill cause */
   ie = &(failMsg->protocolIEs.member[numComp++]);

   /* Fill cause IE container */
   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_Cause);
   szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   szFillTknU8(&(ie->value.u.sztCause.choice), causeChoice);

   switch(causeChoice)
   {
      case CAUSE_RADIONW:
         szFillTknU32(&(ie->value.u.sztCause.val.radioNw), causeVal);
         break;

      case CAUSE_TRANSPORT:
         szFillTknU32(&(ie->value.u.sztCause.val.transport), causeVal);
         break;

      case CAUSE_NAS:
         szFillTknU32(&(ie->value.u.sztCause.val.nas), causeVal);
         break;

      case CAUSE_PROTOCOL:
         szFillTknU32(&(ie->value.u.sztCause.val.protocol), causeVal);
         break;

      case CAUSE_MISC:
         szFillTknU32(&(ie->value.u.sztCause.val.misc), causeVal);
         break;

      default:
         break;
   }

   /* Fill the criticality diagnostics depnding on the no of error Ies */
#ifdef CM_PASN_CRIT_HANDL
   if(asnErr->ieCount)
   {
      ie = &(failMsg->protocolIEs.member[numComp++]);

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_CriticalityDiag);
      szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
      szFillTknU8(&(ie->value.u.sztCriticalityDiag.pres), PRSNT_NODEF);

      /* Get the no of components, the no of components is equal to error Ies */
      numComp = asnErr->ieCount;
      szFillTknU16(&(ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.noComp), numComp);

      /* Allocate memory for the members */
      if ((cmGetMem((*errIndPdu), (numComp * sizeof(SztCriticalityDiag_IE_Item)),
                  (Ptr *)&(ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.member))) != ROK)
      {
         SZ_FREE_SDU(*errIndPdu);
         RETVALUE(RFAILED);
      }

      /* Fill the each reported error Ies with its criticality and ID */
      for(idx = 0; idx < numComp; idx++)
      {
         ie1 = &ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.member[idx];
         szFillTknU8(&(ie1->pres), PRSNT_NODEF);
         szFillTknU32(&(ie1->iECriticality), asnErr->ieInfo[idx].criticality);
         szFillTknU32(&(ie1->iE_ID), asnErr->ieInfo[idx].ieId);
         szFillTknU32(&(ie1->typeOfErr), asnErr->ieInfo[idx].errType);
         ie1->iE_Extns.noComp.pres = NOTPRSNT;
      }
   }
#endif /* CM_PASN_CRIT_HANDL */

   RETVALUE(ROK);
} /* End of szDbFillHovrPrepFail */

/* 
 * 
 *      Fun:   szDbFillHovrFail
 *
 *      Desc:  Fill Error Indication
 *
 *      Ret:   ROK   - ok
 *
 *      Notes: None.
 *
 *      File:  sq_utils.c
 *
 */
#ifdef ANSI
PUBLIC S16 szDbFillHovrFail
(
S1apPdu *pdu,
U8  causeChoice,
U32 causeVal,
S1apPdu **errIndPdu,
Mem mem,
CmPAsnErr *asnErr
)
#else
PUBLIC S16 szDbFillHovrFail(pdu, causeChoice, causeVal, errIndPdu, mem, asnErr)
S1apPdu *pdu;
U8  causeChoice;
U32 causeVal;
S1apPdu **errIndPdu;
Mem mem;
CmPAsnErr *asnErr;
#endif
{
   TknU8 *mmeS1apId = NULLP;

   U16 numComp = 0;
   S16 ret = 0;

   SztHovrFail *failMsg = NULLP;
   SztProtIE_Field_HovrFailIEs *ie = NULLP;
#ifdef CM_PASN_CRIT_HANDL
   SztCriticalityDiag_IE_Item *ie1 = NULLP;
   U8     idx;
#endif /* CM_PASN_CRIT_HANDL */

   TRC2(szDbFillHovrFail);


   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)errIndPdu);
   if (ret != ROK)
   {
      RETVALUE(RFAILED);
   }

   /* Building respective message */
   szFillTknU8(&((*errIndPdu)->pdu.choice), S1AP_PDU_UNSUCCESSFULOUTCOME);
   szFillTknU8(&((*errIndPdu)->pdu.val.unsuccessfulOutcome.pres), PRSNT_NODEF);
   szFillTknU32(&((*errIndPdu)->pdu.val.unsuccessfulOutcome.procedureCode),
         Sztid_HovrResourceAllocn);
   szFillTknU32(&((*errIndPdu)->pdu.val.unsuccessfulOutcome.criticality),
         SztCriticalityignoreEnum);

   /* Filling of failure message */
   failMsg = &((*errIndPdu)->pdu.val.unsuccessfulOutcome.value.u.sztHovrFail);
   szFillTknU8(&(failMsg->pres), PRSNT_NODEF);

   numComp = 1;

   if(pdu != NULLP)
   {
      szGetIE(&pdu->pdu,Sztid_MME_UE_S1AP_ID, &mmeS1apId);
   }

   if (mmeS1apId != NULLP)
   {
      numComp++;
   }

  /* Changed the no of comps */
#ifdef CM_PASN_CRIT_HANDL
   if(asnErr->ieCount)
   {
      numComp++;
   }
#endif /* CM_PASN_CRIT_HANDL */

   szFillTknU16(&(failMsg->protocolIEs.noComp), numComp);

   if ((cmGetMem((*errIndPdu), (numComp * sizeof(SztProtIE_Field_HovrFailIEs)),
               (Ptr *)&(failMsg->protocolIEs.member))) != ROK)
   {
      SZ_FREE_SDU(*errIndPdu);
      RETVALUE(RFAILED);
   }

   /* Reset the numComp parameter */
   numComp = 0;
   
   /* Fill MME IE if present */ 
   if (mmeS1apId != NULLP)
   {
      ie = &(failMsg->protocolIEs.member[numComp++]);

      szFillTknU8(&(ie->pres),PRSNT_NODEF);
      szFillTknU32(&(ie->id),Sztid_MME_UE_S1AP_ID);
      szFillTknU32(&(ie->criticality),SztCriticalityignoreEnum);
      szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID),((TknU32 *)mmeS1apId)->val);
   }

   /* Fill cause */
   ie = &(failMsg->protocolIEs.member[numComp++]);

   /* Fill cause IE container */
   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_Cause);
   szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   szFillTknU8(&(ie->value.u.sztCause.choice), causeChoice);

   switch(causeChoice)
   {
      case CAUSE_RADIONW:
         szFillTknU32(&(ie->value.u.sztCause.val.radioNw), causeVal);
         break;

      case CAUSE_TRANSPORT:
         szFillTknU32(&(ie->value.u.sztCause.val.transport), causeVal);
         break;

      case CAUSE_NAS:
         szFillTknU32(&(ie->value.u.sztCause.val.nas), causeVal);
         break;

      case CAUSE_PROTOCOL:
         szFillTknU32(&(ie->value.u.sztCause.val.protocol), causeVal);
         break;

      case CAUSE_MISC:
         szFillTknU32(&(ie->value.u.sztCause.val.misc), causeVal);
         break;

      default:
         break;
   }

   /* Fill the criticality diagnostics depnding on the no of error Ies */
#ifdef CM_PASN_CRIT_HANDL
   if(asnErr->ieCount)
   {
      ie = &(failMsg->protocolIEs.member[numComp++]);

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_CriticalityDiag);
      szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
      szFillTknU8(&(ie->value.u.sztCriticalityDiag.pres), PRSNT_NODEF);

      /* Get the no of components, the no of components is equal to error Ies */
      numComp = asnErr->ieCount;
      szFillTknU16(&(ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.noComp), numComp);

      /* Allocate memory for the members */
      if ((cmGetMem((*errIndPdu), (numComp * sizeof(SztCriticalityDiag_IE_Item)),
                  (Ptr *)&(ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.member))) != ROK)
      {
         SZ_FREE_SDU(*errIndPdu);
         RETVALUE(RFAILED);
      }

      /* Fill the each reported error Ies with its criticality and ID */
      for(idx = 0; idx < numComp; idx++)
      {
         ie1 = &ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.member[idx];
         szFillTknU8(&(ie1->pres), PRSNT_NODEF);
         szFillTknU32(&(ie1->iECriticality), asnErr->ieInfo[idx].criticality);
         szFillTknU32(&(ie1->iE_ID), asnErr->ieInfo[idx].ieId);
         szFillTknU32(&(ie1->typeOfErr), asnErr->ieInfo[idx].errType);
         ie1->iE_Extns.noComp.pres = NOTPRSNT;
      }
   }
#endif /* CM_PASN_CRIT_HANDL */

   RETVALUE(ROK);
} /* End of szDbFillHovrFail */


/* 
 * 
 *      Fun:   szDbFillPathSwRqstFail
 *
 *      Desc:  Fill Error Indication
 *
 *      Ret:   ROK   - ok
 *
 *      Notes: None.
 *
 *      File:  sq_utils.c
 *
 */
#ifdef ANSI
PUBLIC S16 szDbFillPathSwRqstFail
(
S1apPdu *pdu,
U8  causeChoice,
U32 causeVal,
S1apPdu **errIndPdu,
Mem mem,
CmPAsnErr *asnErr
)
#else
PUBLIC S16 szDbFillPathSwRqstFail(pdu, causeChoice, causeVal, errIndPdu, mem, asnErr)
S1apPdu *pdu;
U8  causeChoice;
U32 causeVal;
S1apPdu **errIndPdu;
Mem mem;
CmPAsnErr *asnErr;
#endif
{
   TknU8 *mmeS1apId = NULLP;
   TknU8 *enbS1apId = NULLP;

   U16 numComp = 0;
   S16 ret = 0;

   SztPathSwRqstFail *failMsg = NULLP;
   SztProtIE_Field_PathSwRqstFailIEs *ie = NULLP;
#ifdef CM_PASN_CRIT_HANDL
   SztCriticalityDiag_IE_Item *ie1 = NULLP;
   U8    idx;
#endif /* CM_PASN_CRIT_HANDL */

   TRC2(szDbFillPathSwRqstFail);


   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)errIndPdu);
   if (ret != ROK)
   {
      RETVALUE(RFAILED);
   }

   /* Building respective message */
   szFillTknU8(&((*errIndPdu)->pdu.choice), S1AP_PDU_UNSUCCESSFULOUTCOME);
   szFillTknU8(&((*errIndPdu)->pdu.val.unsuccessfulOutcome.pres), PRSNT_NODEF);
   szFillTknU32(&((*errIndPdu)->pdu.val.unsuccessfulOutcome.procedureCode),
         Sztid_PathSwRqst);
   szFillTknU32(&((*errIndPdu)->pdu.val.unsuccessfulOutcome.criticality),
         SztCriticalityignoreEnum);

   /* Filling of failure message */
   failMsg = &((*errIndPdu)->pdu.val.unsuccessfulOutcome.value.u.sztPathSwRqstFail);
   szFillTknU8(&(failMsg->pres), PRSNT_NODEF);

   numComp = 1;

   if(pdu != NULLP)
   {
      szGetIE(&pdu->pdu, Sztid_SrcMME_UE_S1AP_ID, &mmeS1apId);
      szGetIE(&pdu->pdu, Sztid_eNB_UE_S1AP_ID, &enbS1apId);
   }

   if (mmeS1apId != NULLP)
   {
      numComp++;
   }
   if (enbS1apId != NULLP)
   {
      numComp++;
   }

   /* Increment the no of components incase of error Ie */
#ifdef CM_PASN_CRIT_HANDL
   if(asnErr->ieCount)
   {
      numComp++;
   }
#endif /* CM_PASN_CRIT_HANDL */
   szFillTknU16(&(failMsg->protocolIEs.noComp), numComp);

   if ((cmGetMem((*errIndPdu), (numComp * sizeof(SztProtIE_Field_PathSwRqstFailIEs)),
               (Ptr *)&(failMsg->protocolIEs.member))) != ROK)
   {
      SZ_FREE_SDU(*errIndPdu);
      RETVALUE(RFAILED);
   }

   /* Reset the numComp parameter */
   numComp = 0;

   /* Fill MME IE if present */ 
   if (mmeS1apId != NULLP)
   {
      ie = &(failMsg->protocolIEs.member[numComp++]);

      szFillTknU8(&(ie->pres),PRSNT_NODEF);
      szFillTknU32(&(ie->id),Sztid_MME_UE_S1AP_ID);
      szFillTknU32(&(ie->criticality),SztCriticalityignoreEnum);
      szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID),((TknU32 *)mmeS1apId)->val);
   }

   /* Fill eNB IE if present */ 
   if (enbS1apId != NULLP)
   {
      ie = &(failMsg->protocolIEs.member[numComp++]);

      szFillTknU8(&(ie->pres),PRSNT_NODEF);
      szFillTknU32(&(ie->id),Sztid_eNB_UE_S1AP_ID);
      szFillTknU32(&(ie->criticality),SztCriticalityignoreEnum);
      szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID),((TknU32 *)enbS1apId)->val);
   }

   /* Fill cause */
   ie = &(failMsg->protocolIEs.member[numComp++]);

   /* Fill cause IE container */
   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_Cause);
   szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   szFillTknU8(&(ie->value.u.sztCause.choice), causeChoice);

   switch(causeChoice)
   {
      case CAUSE_RADIONW:
         szFillTknU32(&(ie->value.u.sztCause.val.radioNw), causeVal);
         break;

      case CAUSE_TRANSPORT:
         szFillTknU32(&(ie->value.u.sztCause.val.transport), causeVal);
         break;

      case CAUSE_NAS:
         szFillTknU32(&(ie->value.u.sztCause.val.nas), causeVal);
         break;

      case CAUSE_PROTOCOL:
         szFillTknU32(&(ie->value.u.sztCause.val.protocol), causeVal);
         break;

      case CAUSE_MISC:
         szFillTknU32(&(ie->value.u.sztCause.val.misc), causeVal);
         break;

      default:
         break;
   }

   /* Fill the criticality diagnostics depnding on the no of error Ies */
#ifdef CM_PASN_CRIT_HANDL
   if(asnErr->ieCount)
   {
      ie = &(failMsg->protocolIEs.member[numComp++]);

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_CriticalityDiag);
      szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
      szFillTknU8(&(ie->value.u.sztCriticalityDiag.pres), PRSNT_NODEF);

      /* Get the no of components, the no of components is equal to error Ies */
      numComp = asnErr->ieCount;
      szFillTknU16(&(ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.noComp), numComp);

      /* Allocate memory for the members */
      if ((cmGetMem((*errIndPdu), (numComp * sizeof(SztCriticalityDiag_IE_Item)),
                  (Ptr *)&(ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.member))) != ROK)
      {
         SZ_FREE_SDU(*errIndPdu);
         RETVALUE(RFAILED);
      }

      /* Fill the each reported error Ies with its criticality and ID */
      for(idx = 0; idx < numComp; idx++)
      {
         ie1 = &ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.member[idx];
         szFillTknU8(&(ie1->pres), PRSNT_NODEF);
         szFillTknU32(&(ie1->iECriticality), asnErr->ieInfo[idx].criticality);
         szFillTknU32(&(ie1->iE_ID), asnErr->ieInfo[idx].ieId);
         szFillTknU32(&(ie1->typeOfErr), asnErr->ieInfo[idx].errType);
         ie1->iE_Extns.noComp.pres = NOTPRSNT;
      }
   }
#endif /* CM_PASN_CRIT_HANDL */

   RETVALUE(ROK);
} /* End of szDbFillPathSwRqstFail */

/* 
 * 
 *      Fun:   szDbFillS1SetupFail
 *
 *      Desc:  Fill Error Indication
 *
 *      Ret:   ROK   - ok
 *
 *      Notes: None.
 *
 *      File:  sq_utils.c
 *
 */
#ifdef ANSI
PUBLIC S16 szDbFillS1SetupFail
(
S1apPdu *pdu,
U8  causeChoice,
U32 causeVal,
S1apPdu **errIndPdu,
Mem mem,
CmPAsnErr *asnErr
)
#else
PUBLIC S16 szDbFillS1SetupFail(pdu, causeChoice, causeVal, errIndPdu, mem, asnErr)
S1apPdu *pdu;
U8  causeChoice;
U32 causeVal;
S1apPdu **errIndPdu;
Mem mem;
CmPAsnErr *asnErr;
#endif
{

   U16 numComp = 0;
   S16 ret = 0;

   SztS1SetupFail *failMsg = NULLP;
   SztProtIE_Field_S1SetupFailIEs *ie = NULLP;
#ifdef CM_PASN_CRIT_HANDL
   SztCriticalityDiag_IE_Item *ie1 = NULLP;
   U8   idx;
#endif /* CM_PASN_CRIT_HANDL */

   TRC2(szDbFillS1SetupFail);


   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)errIndPdu);
   if (ret != ROK)
   {
      RETVALUE(RFAILED);
   }

   /* Building respective message */
   szFillTknU8(&((*errIndPdu)->pdu.choice), S1AP_PDU_UNSUCCESSFULOUTCOME);
   szFillTknU8(&((*errIndPdu)->pdu.val.unsuccessfulOutcome.pres), PRSNT_NODEF);
   szFillTknU32(&((*errIndPdu)->pdu.val.unsuccessfulOutcome.procedureCode),
         Sztid_S1Setup);
   szFillTknU32(&((*errIndPdu)->pdu.val.unsuccessfulOutcome.criticality),
         SztCriticalityignoreEnum);

   /* Filling of failure message */
   failMsg = &((*errIndPdu)->pdu.val.unsuccessfulOutcome.value.u.sztS1SetupFail);
   szFillTknU8(&(failMsg->pres), PRSNT_NODEF);

   numComp = 1;

#ifdef CM_PASN_CRIT_HANDL
   if(asnErr->ieCount)
   {
      numComp++;
   }
#endif /* CM_PASN_CRIT_HANDL */

   szFillTknU16(&(failMsg->protocolIEs.noComp), numComp);

   if ((cmGetMem((*errIndPdu), (numComp * sizeof(SztProtIE_Field_S1SetupFailIEs)),
               (Ptr *)&(failMsg->protocolIEs.member))) != ROK)
   {
      SZ_FREE_SDU(*errIndPdu);
      RETVALUE(RFAILED);
   }

   /* Reset the numComp parameter */
   numComp = 0;

   /* Fill cause */
   ie = &(failMsg->protocolIEs.member[numComp++]);

   /* Fill cause IE container */
   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_Cause);
   szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   szFillTknU8(&(ie->value.u.sztCause.choice), causeChoice);

   switch(causeChoice)
   {
      case CAUSE_RADIONW:
         szFillTknU32(&(ie->value.u.sztCause.val.radioNw), causeVal);
         break;

      case CAUSE_TRANSPORT:
         szFillTknU32(&(ie->value.u.sztCause.val.transport), causeVal);
         break;

      case CAUSE_NAS:
         szFillTknU32(&(ie->value.u.sztCause.val.nas), causeVal);
         break;

      case CAUSE_PROTOCOL:
         szFillTknU32(&(ie->value.u.sztCause.val.protocol), causeVal);
         break;

      case CAUSE_MISC:
         szFillTknU32(&(ie->value.u.sztCause.val.misc), causeVal);
         break;

      default:
         break;
   }

   /* Fill the criticality diagnostics depnding on the no of error Ies */
#ifdef CM_PASN_CRIT_HANDL
   if(asnErr->ieCount)
   {
      ie = &(failMsg->protocolIEs.member[numComp++]);

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_CriticalityDiag);
      szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
      szFillTknU8(&(ie->value.u.sztCriticalityDiag.pres), PRSNT_NODEF);

      /* Get the no of components, the no of components is equal to error Ies */
      numComp = asnErr->ieCount;
      szFillTknU16(&(ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.noComp), numComp);

      /* Allocate memory for the members */
      if ((cmGetMem((*errIndPdu), (numComp * sizeof(SztCriticalityDiag_IE_Item)),
                  (Ptr *)&(ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.member))) != ROK)
      {
         SZ_FREE_SDU(*errIndPdu);
         RETVALUE(RFAILED);
      }

      /* Fill the each reported error Ies with its criticality and ID */
      for(idx = 0; idx < numComp; idx++)
      {
         ie1 = &ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.member[idx];
         szFillTknU8(&(ie1->pres), PRSNT_NODEF);
         szFillTknU32(&(ie1->iECriticality), asnErr->ieInfo[idx].criticality);
         szFillTknU32(&(ie1->iE_ID), asnErr->ieInfo[idx].ieId);
         szFillTknU32(&(ie1->typeOfErr), asnErr->ieInfo[idx].errType);
         ie1->iE_Extns.noComp.pres = NOTPRSNT;
      }
   }
#endif /* CM_PASN_CRIT_HANDL */

   RETVALUE(ROK);
} /* End of szDbFillS1SetupFail */

/* 
 * 
 *      Fun:   szDbFillENBConfigUpdFail
 *
 *      Desc:  Fill Error Indication
 *
 *      Ret:   ROK   - ok
 *
 *      Notes: None.
 *
 *      File:  sq_utils.c
 *
 */
#ifdef ANSI
PUBLIC S16 szDbFillENBConfigUpdFail
(
S1apPdu *pdu,
U8  causeChoice,
U32 causeVal,
S1apPdu **errIndPdu,
Mem mem,
CmPAsnErr *asnErr
)
#else
PUBLIC S16 szDbFillENBConfigUpdFail(pdu, causeChoice, causeVal, errIndPdu, mem, asnErr)
S1apPdu *pdu;
U8  causeChoice;
U32 causeVal;
S1apPdu **errIndPdu;
Mem mem;
CmPAsnErr *asnErr;
#endif
{

   U16 numComp = 0;
   S16 ret = 0;

   SztENBConfigUpdFail *failMsg = NULLP;
   SztProtIE_Field_ENBConfigUpdFailIEs *ie = NULLP;
#ifdef CM_PASN_CRIT_HANDL
   SztCriticalityDiag_IE_Item *ie1 = NULLP;
   U8   idx;
#endif /* CM_PASN_CRIT_HANDL */

   TRC2(szDbFillENBConfigUpdFail);


   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)errIndPdu);
   if (ret != ROK)
   {
      RETVALUE(RFAILED);
   }

   /* Building respective message */
   szFillTknU8(&((*errIndPdu)->pdu.choice), S1AP_PDU_UNSUCCESSFULOUTCOME);
   szFillTknU8(&((*errIndPdu)->pdu.val.unsuccessfulOutcome.pres), PRSNT_NODEF);
   szFillTknU32(&((*errIndPdu)->pdu.val.unsuccessfulOutcome.procedureCode),
         Sztid_ENBConfigUpd);
   szFillTknU32(&((*errIndPdu)->pdu.val.unsuccessfulOutcome.criticality),
         SztCriticalityignoreEnum);

   /* Filling of failure message */
   failMsg = &((*errIndPdu)->pdu.val.unsuccessfulOutcome.value.u.sztENBConfigUpdFail);
   szFillTknU8(&(failMsg->pres), PRSNT_NODEF);

   numComp = 1;

#ifdef CM_PASN_CRIT_HANDL
   if(asnErr->ieCount)
   {
      numComp++;
   }
#endif /* CM_PASN_CRIT_HANDL */

   szFillTknU16(&(failMsg->protocolIEs.noComp), numComp);

   if ((cmGetMem((*errIndPdu), (numComp * sizeof(SztProtIE_Field_ENBConfigUpdFailIEs)),
               (Ptr *)&(failMsg->protocolIEs.member))) != ROK)
   {
      SZ_FREE_SDU(*errIndPdu);
      RETVALUE(RFAILED);
   }

   /* Reset the numComp parameter */
   numComp = 0;

   /* Fill cause */
   ie = &(failMsg->protocolIEs.member[numComp++]);

   /* Fill cause IE container */
   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_Cause);
   szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   szFillTknU8(&(ie->value.u.sztCause.choice), causeChoice);

   switch(causeChoice)
   {
      case CAUSE_RADIONW:
         szFillTknU32(&(ie->value.u.sztCause.val.radioNw), causeVal);
         break;

      case CAUSE_TRANSPORT:
         szFillTknU32(&(ie->value.u.sztCause.val.transport), causeVal);
         break;

      case CAUSE_NAS:
         szFillTknU32(&(ie->value.u.sztCause.val.nas), causeVal);
         break;

      case CAUSE_PROTOCOL:
         szFillTknU32(&(ie->value.u.sztCause.val.protocol), causeVal);
         break;

      case CAUSE_MISC:
         szFillTknU32(&(ie->value.u.sztCause.val.misc), causeVal);
         break;

      default:
         break;
   }

   /* Fill the criticality diagnostics depnding on the no of error Ies */
#ifdef CM_PASN_CRIT_HANDL
   if(asnErr->ieCount)
   {
      ie = &(failMsg->protocolIEs.member[numComp++]);

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_CriticalityDiag);
      szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
      szFillTknU8(&(ie->value.u.sztCriticalityDiag.pres), PRSNT_NODEF);

      /* Get the no of components, the no of components is equal to error Ies */
      numComp = asnErr->ieCount;
      szFillTknU16(&(ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.noComp), numComp);

      /* Allocate memory for the members */
      if ((cmGetMem((*errIndPdu), (numComp * sizeof(SztCriticalityDiag_IE_Item)),
                  (Ptr *)&(ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.member))) != ROK)
      {
         SZ_FREE_SDU(*errIndPdu);
         RETVALUE(RFAILED);
      }

      /* Fill the each reported error Ies with its criticality and ID */
      for(idx = 0; idx < numComp; idx++)
      {
         ie1 = &ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.member[idx];
         szFillTknU8(&(ie1->pres), PRSNT_NODEF);
         szFillTknU32(&(ie1->iECriticality), asnErr->ieInfo[idx].criticality);
         szFillTknU32(&(ie1->iE_ID), asnErr->ieInfo[idx].ieId);
         szFillTknU32(&(ie1->typeOfErr), asnErr->ieInfo[idx].errType);
         ie1->iE_Extns.noComp.pres = NOTPRSNT;
      }
   }
#endif /* CM_PASN_CRIT_HANDL */

   RETVALUE(ROK);
} /* End of szDbFillENBConfigUpdFail */


/* 
 * 
 *      Fun:   szDbFillMMEConfigUpdFail
 *
 *      Desc:  Fill Error Indication
 *
 *      Ret:   ROK   - ok
 *
 *      Notes: None.
 *
 *      File:  sq_utils.c
 *
 */
#ifdef ANSI
PUBLIC S16 szDbFillMMEConfigUpdFail
(
S1apPdu *pdu,
U8  causeChoice,
U32 causeVal,
S1apPdu **errIndPdu,
Mem mem,
CmPAsnErr *asnErr
)
#else
PUBLIC S16 szDbFillMMEConfigUpdFail(pdu, causeChoice, causeVal, errIndPdu, mem, asnErr)
S1apPdu *pdu;
U8  causeChoice;
U32 causeVal;
S1apPdu **errIndPdu;
Mem mem;
CmPAsnErr *asnErr;
#endif
{
   U16 numComp = 0;
   S16 ret = 0;

   SztMMEConfigUpdFail *failMsg = NULLP;
   SztProtIE_Field_MMEConfigUpdFailIEs *ie = NULLP;
#ifdef CM_PASN_CRIT_HANDL
   SztCriticalityDiag_IE_Item *ie1 = NULLP;
   U8   idx;
#endif /* CM_PASN_CRIT_HANDL */

   TRC2(szDbFillMMEConfigUpdFail);


   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)errIndPdu);
   if (ret != ROK)
   {
      RETVALUE(RFAILED);
   }

   /* Building respective message */
   szFillTknU8(&((*errIndPdu)->pdu.choice), S1AP_PDU_UNSUCCESSFULOUTCOME);
   szFillTknU8(&((*errIndPdu)->pdu.val.unsuccessfulOutcome.pres), PRSNT_NODEF);
   szFillTknU32(&((*errIndPdu)->pdu.val.unsuccessfulOutcome.procedureCode),
         Sztid_MMEConfigUpd);
   szFillTknU32(&((*errIndPdu)->pdu.val.unsuccessfulOutcome.criticality),
         SztCriticalityignoreEnum);

   /* Filling of failure message */
   failMsg = &((*errIndPdu)->pdu.val.unsuccessfulOutcome.value.u.sztMMEConfigUpdFail);
   szFillTknU8(&(failMsg->pres), PRSNT_NODEF);

   numComp = 1;

#ifdef CM_PASN_CRIT_HANDL
   if(asnErr->ieCount)
   {
      numComp++;
   }
#endif /* CM_PASN_CRIT_HANDL */

   szFillTknU16(&(failMsg->protocolIEs.noComp), numComp);

   if ((cmGetMem((*errIndPdu), (numComp * sizeof(SztProtIE_Field_MMEConfigUpdFailIEs)),
               (Ptr *)&(failMsg->protocolIEs.member))) != ROK)
   {
      SZ_FREE_SDU(*errIndPdu);
      RETVALUE(RFAILED);
   }

   /* Reset the numComp parameter */
   numComp = 0;
   
   /* Fill cause */
   ie = &(failMsg->protocolIEs.member[numComp++]);

   /* Fill cause IE container */
   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_Cause);
   szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   szFillTknU8(&(ie->value.u.sztCause.choice), causeChoice);

   switch(causeChoice)
   {
      case CAUSE_RADIONW:
         szFillTknU32(&(ie->value.u.sztCause.val.radioNw), causeVal);
         break;

      case CAUSE_TRANSPORT:
         szFillTknU32(&(ie->value.u.sztCause.val.transport), causeVal);
         break;

      case CAUSE_NAS:
         szFillTknU32(&(ie->value.u.sztCause.val.nas), causeVal);
         break;

      case CAUSE_PROTOCOL:
         szFillTknU32(&(ie->value.u.sztCause.val.protocol), causeVal);
         break;

      case CAUSE_MISC:
         szFillTknU32(&(ie->value.u.sztCause.val.misc), causeVal);
         break;

      default:
         break;
   }

   /* Fill the criticality diagnostics depnding on the no of error Ies */
#ifdef CM_PASN_CRIT_HANDL
   if(asnErr->ieCount)
   {
      ie = &(failMsg->protocolIEs.member[numComp++]);

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_CriticalityDiag);
      szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
      szFillTknU8(&(ie->value.u.sztCriticalityDiag.pres), PRSNT_NODEF);

      /* Get the no of components, the no of components is equal to error Ies */
      numComp = asnErr->ieCount;
      szFillTknU16(&(ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.noComp), numComp);

      /* Allocate memory for the members */
      if ((cmGetMem((*errIndPdu), (numComp * sizeof(SztCriticalityDiag_IE_Item)),
                  (Ptr *)&(ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.member))) != ROK)
      {
         SZ_FREE_SDU(*errIndPdu);
         RETVALUE(RFAILED);
      }

      /* Fill the each reported error Ies with its criticality and ID */
      for(idx = 0; idx < numComp; idx++)
      {
         ie1 = &ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.member[idx];
         szFillTknU8(&(ie1->pres), PRSNT_NODEF);
         szFillTknU32(&(ie1->iECriticality), asnErr->ieInfo[idx].criticality);
         szFillTknU32(&(ie1->iE_ID), asnErr->ieInfo[idx].ieId);
         szFillTknU32(&(ie1->typeOfErr), asnErr->ieInfo[idx].errType);
         ie1->iE_Extns.noComp.pres = NOTPRSNT;
      }
   }
#endif /* CM_PASN_CRIT_HANDL */

   RETVALUE(ROK);
} /* End of szDbFillMMEConfigUpdFail */


/*
*
*       Fun:   szUtilsBldUnsucOutComeMsg  
*
*       Desc:  Called to build an Unsuccessful outcome;
*       if message doesnot exist then builds an error indication.
*
*       Ret:   ok:     ROK
*              failed: RFAILED
*
*       Notes: None
*
*       File:  sz_li.c
*
*/

#ifdef ANSI
PUBLIC S16 szUtilsBldUnsucOutComeMsg 
(
S1apPdu  *pdu,
U8  causeChoice,
U32 causeVal,
S1apPdu **errPdu,
Mem mem,
CmPAsnErr *asnErr
)
#else
PUBLIC S16 szUtilsBldUnsucOutComeMsg(pdu, causeChoice, causeVal, errPdu, mem, asnErr)
S1apPdu  *pdu;
U8  causeChoice;
U32 causeVal;
S1apPdu **errPdu;
Mem mem;
CmPAsnErr *asnErr;
#endif
{
   S16   ret = ROK;
   U32    evnt = 0;

   TRC2(szUtilsBldUnsucOutComeMsg);

   SZDBGP(DBGMASK_LI, (szCb.init.prntBuf, 
     "szUtilsBldUnsucOutComeMsg : Received dedicated procedure\n"));

   /* get evnt type */
   evnt = pdu->pdu.val.initiatingMsg.procedureCode.val;

   switch(evnt)
   {
      case Sztid_HovrPrep:
         /* Build Handover Prep. Failure */
         ret = szDbFillHovrPrepFail(pdu, causeChoice, causeVal, errPdu, mem, asnErr);
         break;
      case Sztid_HovrResourceAllocn:
         /* Build Handover Failure */
         ret = szDbFillHovrFail(pdu, causeChoice, causeVal, errPdu, mem, asnErr);
         break;
      case Sztid_PathSwRqst:
         /* Build Path Switch Request Failure */
         ret = szDbFillPathSwRqstFail(pdu, causeChoice, causeVal, errPdu, mem, asnErr);
         break;
      case Sztid_InitCntxtSetup:
         /* Build Initial Context Setup Failure */
         ret = szDbFillInitCxtSetupFail(pdu, causeChoice, causeVal, errPdu, mem, asnErr);
         break;
      case Sztid_S1Setup:
         /* Build S1 Setup Failure */
         ret = szDbFillS1SetupFail(pdu, causeChoice, causeVal, errPdu, mem, asnErr);
         break;
      case Sztid_UECntxtModification:
         /* Build UE Context Modification Failure */
         ret = szDbFillUeCxtModFail(pdu, causeChoice, causeVal, errPdu, mem, asnErr);
         break;
      case Sztid_ENBConfigUpd:
         /* Build ENB Configuration Update Failure */
         ret = szDbFillENBConfigUpdFail(pdu, causeChoice, causeVal, errPdu, mem, asnErr);
         break;
      case Sztid_MMEConfigUpd:
         /* Build MME Configuration Update Failure */
         ret = szDbFillMMEConfigUpdFail(pdu, causeChoice, causeVal, errPdu, mem, asnErr);
         break;
      default:
         /* send an error Indication */
         ret = szDbFillErrInd(pdu, causeChoice, causeVal, errPdu, mem, asnErr);
         break;
   }

    RETVALUE(ret);
} /* end of szUtilsBldUnsucOutComeMsg */
#endif

#ifdef LSZV1
/*
*
*       Fun:   szIncErrSts
*
*       Desc:  Increment the error statistics
*
*       Ret:   ROK     - ok
*              RFAILED - failure
*
*       Notes: N/A
*
*       File:  sz_utils.c
*
*/

#ifdef ANSI
PUBLIC S16 szIncErrSts
(
SzPeerCb    *peer,
U16         causeType,
U16         cause
)
#else
PUBLIC S16 szIncErrSts (peer, causeType, cause)
SzPeerCb    *peer;
U16         causeType;
U16         cause;
#endif
{
   StsCntr  *ptr;                                                
                                                                  
   switch(causeType)                                             
   {                                                              
      case CAUSE_RADIONW:                                         
      {                                                           
         SzRadioNwErrSts *p1;                                    
         p1 = &peer->peerSts.cfm.errSts.radioNwErrSts;          
         switch(cause)                                           
         {                                                        
            case SZ_UNKNOWN_MME_UE_S1AP_ID:                          
            {                                                     
               ptr = (StsCntr *)(&p1->unknownMmeUeS1apId);      
               *ptr = (*ptr) + 1;                               
               break;                                             
            }                                                     
                                                                  
            case SZ_UNKNOWN_ENB_UE_S1AP_ID:                          
            {                                                     
               ptr = (StsCntr *)(&p1->unknownEnbUeS1apId);      
               *ptr = (*ptr) + 1;                               
               break;                                             
            }                                                     
                                                                  
            case SZ_UNKNOWN_PAIR_UE_S1AP_ID:                         
            {                                                     
               ptr = (StsCntr *)(&p1->unknownPairUeS1apId);     
               *ptr = (*ptr) + 1;                               
               break;                                             
            }                                                     
                                                                  
            default:                                              
               break;                                             
         }                                                        
                                                                  
         break;                                                   
      }                                                           
                                                                  
      case CAUSE_NAS:                                             
        break;                                                    
                                                                  
      case CAUSE_TRANSPORT:                                       
        break;                                                    
                                                                  
      case CAUSE_PROTOCOL:                                        
      {                                                           
         SzProtErrSts *p2;                                       
         if(cause < SZ_MAX_PROTOCOL_ERRS_HANDLD)                    
         {                                                        
            p2 = &peer->peerSts.cfm.errSts.protErrSts;          
            ptr = ((StsCntr *)(((StsCntr *)p2) + (U32)cause)); 
            *ptr = (*ptr) + 1;                                  
         }                                                        
         break;                                                   
      }                                                           
                                                                  
      case CAUSE_MISC:                                            
        break;                                                    
                                                                  
      default:                                                    
        break;                                                    
   }                                                              

   RETVALUE(ROK);
}
#endif


/**********************************************************************
 
         End of file:     sq_utils.c@@/main/4 - Mon Jan 10 22:17:11 2011
 
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
/main/4      ---      pkaX  1. Updated for S1AP release 3.1
/main/4    sz002.301  pkaX  1. Fix for the memory allocation issue.
/main/4   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
/main/4   sz005.301   va   1. Added the Initial context setup fail
/main/4   sz006.301   ve    1. Removed un-necessary include files
/main/4   sz008.301 akaranth 1. Support for source RNC to target RNC.
                             2. Fix for kwork.
*********************************************************************91*/
