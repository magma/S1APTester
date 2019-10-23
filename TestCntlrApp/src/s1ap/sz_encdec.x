

/**********************************************************************

     Name:     S1AP Layer

     Type:     C source file

     Desc:     C source code for encoder/decoder library

     File:     sz_encdec.x

     Sid:      sz_encdec.x@@/main/1 - Mon Jan 10 22:17:13 2011

     Prg:      pkaX

**********************************************************************/

#ifndef __SZ_ENCDECX__
#define __SZ_ENCDECX__

#ifdef __cplusplus
{
#endif 

typedef struct _szIeErrInfo
{
   U8        errType;      /* Error type */
   U16       criticality;  /* Criticality of IE */
   U32       ieId;         /* IE Id */
}SzIeErrInfo;

typedef struct _szAsnErr
{
   S16       errCode;  /* Error code */
}SzAsnErr;

typedef struct _szEncDecErr
{
   U16         ieCount;                /* No of erroneous IEs */
   SzIeErrInfo ieInfo[SZT_MAX_ERR_IE]; /* Erroneous IE Information */
   SzAsnErr    asnErr;                 /* Error Code */
}SzEncDecErr;

typedef struct _szMsgSts
{
   SztEncDecMsgSts   encSts;        /* Encoding statistics */
   SztEncDecMsgSts   decSts;        /* Decoding statistics */
}SzMsgSts;

typedef struct _szMsgParams
{
   S1apPdu  *sdu;            /* S1AP Message Parameters */
}SzMsgParams;

/* sz004.301: Added for TC Dec/Enc */
typedef struct _szMsgParamsIe
{
   U8       type;          /* Type of Ie */
   SzIePdu  *ieSdu;          /* S1AP Message Parameters for IE's*/
}SzMsgParamsIe;

typedef struct _szDecEncInfo
{
   Bool  debug;              /* Run-time Debug Information */
}SzDecEncInfo;

typedef struct _szCauseDgn
{
   U32           numDecOct;  /* Number of octets decoded */
   S16           errCode;    /* Error Code */
} SzCauseDgn;

typedef struct _sztEncDecIe
{
   CmMemListCp  memCp;
   Void         *iePtr;
}SztEncDecIE;

typedef struct _szCbEncDec
{
#ifdef DEBUGP
   TskInit         init;        /* Init structure */
#endif
   SzEncDecErr    encDecErr;   /* Encode/decode error */
   SzMsgSts        sts;         /* Encode/decode statistics */
}SzCb;

EXTERN S16 SzDecodeMsgReq  ARGS((Buffer *mBuf, SzMsgParams *msgParams, 
                                 SzDecEncInfo *decInfo, SzCauseDgn *causeDgn));
EXTERN S16 SzEncodeMsgReq ARGS((Buffer *mBuf, SzMsgParams *msgParam,
                                SzDecEncInfo *encInfo, SzCauseDgn *causeDgn));
EXTERN S16 SzStatisticsReq ARGS((SzMsgSts *msgSts, U8 action, U8  *errNo));
EXTERN S16 SzInitReq ARGS((Void *init, U8  *err));

EXTERN S16 szPrntTknStrBSXL ARGS((TknStrBSXL *tknStr));
EXTERN S16 szPrntTknBStr32 ARGS((TknBStr32 *tknStr));
EXTERN S16 szPrntTknPres ARGS((TknPres  *param));
EXTERN S16 szPrntTknU8 ARGS((TknU8 *param));
EXTERN S16 szPrntTknU16 ARGS((TknU16 *param));
EXTERN S16 szPrntTknU32 ARGS((TknU32 *param));
EXTERN S16 szPrntTknStrOSXL ARGS((TknStrOSXL  *param));
EXTERN S16 szPrntTknStr4 ARGS((TknStr4  *param));
EXTERN S16 szPrntPrivIE_ID ARGS ((SztPrivIE_ID *param));
EXTERN S16 szPrnt_ExtnAllocnAndRetentionPriority_ExtIEsCls ARGS ((Szt_ExtnAllocnAndRetentionPriority_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_AllocnAndRetentionPriority_ExtIEs ARGS ((SztProtExtnField_AllocnAndRetentionPriority_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_AllocnAndRetentionPriority_ExtIEs ARGS ((SztProtExtnCont_AllocnAndRetentionPriority_ExtIEs *param));
EXTERN S16 szPrntAllocnAndRetentionPriority ARGS ((SztAllocnAndRetentionPriority *param));
EXTERN S16 szPrnt_ExtnCOUNTvalue_ExtIEsCls ARGS ((Szt_ExtnCOUNTvalue_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_COUNTvalue_ExtIEs ARGS ((SztProtExtnField_COUNTvalue_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_COUNTvalue_ExtIEs ARGS ((SztProtExtnCont_COUNTvalue_ExtIEs *param));
EXTERN S16 szPrntCOUNTvalue ARGS ((SztCOUNTvalue *param));
EXTERN S16 szPrnt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls ARGS ((Szt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs ARGS ((SztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs *param));
EXTERN S16 szPrntProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs ARGS ((SztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs *param));
EXTERN S16 szPrntBrs_SubjToStatusTfr_Item ARGS ((SztBrs_SubjToStatusTfr_Item *param));
EXTERN S16 szPrnt_ValueBrs_SubjToStatusTfr_ItemIEsCls ARGS ((Szt_ValueBrs_SubjToStatusTfr_ItemIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_Brs_SubjToStatusTfr_ItemIEs ARGS ((SztProtIE_Field_Brs_SubjToStatusTfr_ItemIEs *param));
EXTERN S16 szPrntBrs_SubjToStatusTfrLst ARGS ((SztBrs_SubjToStatusTfrLst *param));
EXTERN S16 szPrntBPLMNs ARGS ((SztBPLMNs *param));
EXTERN S16 szPrnt_ExtnEUTRAN_CGI_ExtIEsCls ARGS ((Szt_ExtnEUTRAN_CGI_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_EUTRAN_CGI_ExtIEs ARGS ((SztProtExtnField_EUTRAN_CGI_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_EUTRAN_CGI_ExtIEs ARGS ((SztProtExtnCont_EUTRAN_CGI_ExtIEs *param));
EXTERN S16 szPrntEUTRAN_CGI ARGS ((SztEUTRAN_CGI *param));
EXTERN S16 szPrnt_ExtnCellID_Broadcast_Item_ExtIEsCls ARGS ((Szt_ExtnCellID_Broadcast_Item_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_CellID_Broadcast_Item_ExtIEs ARGS ((SztProtExtnField_CellID_Broadcast_Item_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_CellID_Broadcast_Item_ExtIEs ARGS ((SztProtExtnCont_CellID_Broadcast_Item_ExtIEs *param));
EXTERN S16 szPrntCellID_Broadcast_Item ARGS ((SztCellID_Broadcast_Item *param));
EXTERN S16 szPrntCellID_Broadcast ARGS ((SztCellID_Broadcast *param));
EXTERN S16 szPrnt_ExtnTAI_ExtIEsCls ARGS ((Szt_ExtnTAI_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_TAI_ExtIEs ARGS ((SztProtExtnField_TAI_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_TAI_ExtIEs ARGS ((SztProtExtnCont_TAI_ExtIEs *param));
EXTERN S16 szPrntTAI ARGS ((SztTAI *param));
EXTERN S16 szPrnt_ExtnCompletedCellinTAI_Item_ExtIEsCls ARGS ((Szt_ExtnCompletedCellinTAI_Item_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_CompletedCellinTAI_Item_ExtIEs ARGS ((SztProtExtnField_CompletedCellinTAI_Item_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_CompletedCellinTAI_Item_ExtIEs ARGS ((SztProtExtnCont_CompletedCellinTAI_Item_ExtIEs *param));
EXTERN S16 szPrntCompletedCellinTAI_Item ARGS ((SztCompletedCellinTAI_Item *param));
EXTERN S16 szPrntCompletedCellinTAI ARGS ((SztCompletedCellinTAI *param));
EXTERN S16 szPrnt_ExtnTAI_Broadcast_Item_ExtIEsCls ARGS ((Szt_ExtnTAI_Broadcast_Item_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_TAI_Broadcast_Item_ExtIEs ARGS ((SztProtExtnField_TAI_Broadcast_Item_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_TAI_Broadcast_Item_ExtIEs ARGS ((SztProtExtnCont_TAI_Broadcast_Item_ExtIEs *param));
EXTERN S16 szPrntTAI_Broadcast_Item ARGS ((SztTAI_Broadcast_Item *param));
EXTERN S16 szPrntTAI_Broadcast ARGS ((SztTAI_Broadcast *param));
EXTERN S16 szPrnt_ExtnCompletedCellinEAI_Item_ExtIEsCls ARGS ((Szt_ExtnCompletedCellinEAI_Item_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_CompletedCellinEAI_Item_ExtIEs ARGS ((SztProtExtnField_CompletedCellinEAI_Item_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_CompletedCellinEAI_Item_ExtIEs ARGS ((SztProtExtnCont_CompletedCellinEAI_Item_ExtIEs *param));
EXTERN S16 szPrntCompletedCellinEAI_Item ARGS ((SztCompletedCellinEAI_Item *param));
EXTERN S16 szPrntCompletedCellinEAI ARGS ((SztCompletedCellinEAI *param));
EXTERN S16 szPrnt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls ARGS ((Szt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs ARGS ((SztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs ARGS ((SztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs *param));
EXTERN S16 szPrntEmergencyAreaID_Broadcast_Item ARGS ((SztEmergencyAreaID_Broadcast_Item *param));
EXTERN S16 szPrntEmergencyAreaID_Broadcast ARGS ((SztEmergencyAreaID_Broadcast *param));
EXTERN S16 szPrntBroadcastCompletedAreaLst ARGS ((SztBroadcastCompletedAreaLst *param));
EXTERN S16 szPrntCause ARGS ((SztCause *param));
EXTERN S16 szPrnt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls ARGS ((Szt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs ARGS ((SztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs ARGS ((SztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs *param));
EXTERN S16 szPrntCdma2000OneXSRVCCInfo ARGS ((SztCdma2000OneXSRVCCInfo *param));
EXTERN S16 szPrnt_ExtnCellTyp_ExtIEsCls ARGS ((Szt_ExtnCellTyp_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_CellTyp_ExtIEs ARGS ((SztProtExtnField_CellTyp_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_CellTyp_ExtIEs ARGS ((SztProtExtnCont_CellTyp_ExtIEs *param));
EXTERN S16 szPrntCellTyp ARGS ((SztCellTyp *param));
EXTERN S16 szPrnt_ExtnCGI_ExtIEsCls ARGS ((Szt_ExtnCGI_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_CGI_ExtIEs ARGS ((SztProtExtnField_CGI_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_CGI_ExtIEs ARGS ((SztProtExtnCont_CGI_ExtIEs *param));
EXTERN S16 szPrntCGI ARGS ((SztCGI *param));
EXTERN S16 szPrnt_ExtnCSG_IdLst_Item_ExtIEsCls ARGS ((Szt_ExtnCSG_IdLst_Item_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_CSG_IdLst_Item_ExtIEs ARGS ((SztProtExtnField_CSG_IdLst_Item_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_CSG_IdLst_Item_ExtIEs ARGS ((SztProtExtnCont_CSG_IdLst_Item_ExtIEs *param));
EXTERN S16 szPrntCSG_IdLst_Item ARGS ((SztCSG_IdLst_Item *param));
EXTERN S16 szPrntCSG_IdLst ARGS ((SztCSG_IdLst *param));
EXTERN S16 szPrnt_ExtnCriticalityDiag_IE_Item_ExtIEsCls ARGS ((Szt_ExtnCriticalityDiag_IE_Item_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_CriticalityDiag_IE_Item_ExtIEs ARGS ((SztProtExtnField_CriticalityDiag_IE_Item_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_CriticalityDiag_IE_Item_ExtIEs ARGS ((SztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs *param));
EXTERN S16 szPrntCriticalityDiag_IE_Item ARGS ((SztCriticalityDiag_IE_Item *param));
EXTERN S16 szPrntCriticalityDiag_IE_Lst ARGS ((SztCriticalityDiag_IE_Lst *param));
EXTERN S16 szPrnt_ExtnCriticalityDiag_ExtIEsCls ARGS ((Szt_ExtnCriticalityDiag_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_CriticalityDiag_ExtIEs ARGS ((SztProtExtnField_CriticalityDiag_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_CriticalityDiag_ExtIEs ARGS ((SztProtExtnCont_CriticalityDiag_ExtIEs *param));
EXTERN S16 szPrntCriticalityDiag ARGS ((SztCriticalityDiag *param));
EXTERN S16 szPrntECGILst ARGS ((SztECGILst *param));
EXTERN S16 szPrntEmergencyAreaIDLst ARGS ((SztEmergencyAreaIDLst *param));
EXTERN S16 szPrntENB_ID ARGS ((SztENB_ID *param));
EXTERN S16 szPrnt_ExtnLAI_ExtIEsCls ARGS ((Szt_ExtnLAI_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_LAI_ExtIEs ARGS ((SztProtExtnField_LAI_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_LAI_ExtIEs ARGS ((SztProtExtnCont_LAI_ExtIEs *param));
EXTERN S16 szPrntLAI ARGS ((SztLAI *param));
EXTERN S16 szPrnt_ExtnGERAN_Cell_ID_ExtIEsCls ARGS ((Szt_ExtnGERAN_Cell_ID_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_GERAN_Cell_ID_ExtIEs ARGS ((SztProtExtnField_GERAN_Cell_ID_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_GERAN_Cell_ID_ExtIEs ARGS ((SztProtExtnCont_GERAN_Cell_ID_ExtIEs *param));
EXTERN S16 szPrntGERAN_Cell_ID ARGS ((SztGERAN_Cell_ID *param));
EXTERN S16 szPrnt_ExtnGlobalENB_ID_ExtIEsCls ARGS ((Szt_ExtnGlobalENB_ID_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_GlobalENB_ID_ExtIEs ARGS ((SztProtExtnField_GlobalENB_ID_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_GlobalENB_ID_ExtIEs ARGS ((SztProtExtnCont_GlobalENB_ID_ExtIEs *param));
EXTERN S16 szPrntGlobal_ENB_ID ARGS ((SztGlobal_ENB_ID *param));
EXTERN S16 szPrnt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls ARGS ((Szt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs ARGS ((SztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs ARGS ((SztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs *param));
EXTERN S16 szPrntENB_StatusTfr_TprntCont ARGS ((SztENB_StatusTfr_TprntCont *param));
EXTERN S16 szPrntENBX2TLAs ARGS ((SztENBX2TLAs *param));
EXTERN S16 szPrntEPLMNs ARGS ((SztEPLMNs *param));
EXTERN S16 szPrnt_ExtnE_RABInformLstItem_ExtIEsCls ARGS ((Szt_ExtnE_RABInformLstItem_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_E_RABInformLstItem_ExtIEs ARGS ((SztProtExtnField_E_RABInformLstItem_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_E_RABInformLstItem_ExtIEs ARGS ((SztProtExtnCont_E_RABInformLstItem_ExtIEs *param));
EXTERN S16 szPrntE_RABInformLstItem ARGS ((SztE_RABInformLstItem *param));
EXTERN S16 szPrnt_ValueE_RABInformLstIEsCls ARGS ((Szt_ValueE_RABInformLstIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_E_RABInformLstIEs ARGS ((SztProtIE_Field_E_RABInformLstIEs *param));
EXTERN S16 szPrntE_RABInformLst ARGS ((SztE_RABInformLst *param));
EXTERN S16 szPrnt_ExtnE_RABItem_ExtIEsCls ARGS ((Szt_ExtnE_RABItem_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_E_RABItem_ExtIEs ARGS ((SztProtExtnField_E_RABItem_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_E_RABItem_ExtIEs ARGS ((SztProtExtnCont_E_RABItem_ExtIEs *param));
EXTERN S16 szPrntE_RABItem ARGS ((SztE_RABItem *param));
EXTERN S16 szPrnt_ValueE_RABItemIEsCls ARGS ((Szt_ValueE_RABItemIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_E_RABItemIEs ARGS ((SztProtIE_Field_E_RABItemIEs *param));
EXTERN S16 szPrntE_RABLst ARGS ((SztE_RABLst *param));
EXTERN S16 szPrnt_ExtnGBR_QosInform_ExtIEsCls ARGS ((Szt_ExtnGBR_QosInform_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_GBR_QosInform_ExtIEs ARGS ((SztProtExtnField_GBR_QosInform_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_GBR_QosInform_ExtIEs ARGS ((SztProtExtnCont_GBR_QosInform_ExtIEs *param));
EXTERN S16 szPrntGBR_QosInform ARGS ((SztGBR_QosInform *param));
EXTERN S16 szPrnt_ExtnE_RABQoSParams_ExtIEsCls ARGS ((Szt_ExtnE_RABQoSParams_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_E_RABQoSParams_ExtIEs ARGS ((SztProtExtnField_E_RABQoSParams_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_E_RABQoSParams_ExtIEs ARGS ((SztProtExtnCont_E_RABQoSParams_ExtIEs *param));
EXTERN S16 szPrntE_RABLvlQoSParams ARGS ((SztE_RABLvlQoSParams *param));
EXTERN S16 szPrntForbiddenTACs ARGS ((SztForbiddenTACs *param));
EXTERN S16 szPrnt_ExtnForbiddenTAs_Item_ExtIEsCls ARGS ((Szt_ExtnForbiddenTAs_Item_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_ForbiddenTAs_Item_ExtIEs ARGS ((SztProtExtnField_ForbiddenTAs_Item_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_ForbiddenTAs_Item_ExtIEs ARGS ((SztProtExtnCont_ForbiddenTAs_Item_ExtIEs *param));
EXTERN S16 szPrntForbiddenTAs_Item ARGS ((SztForbiddenTAs_Item *param));
EXTERN S16 szPrntForbiddenTAs ARGS ((SztForbiddenTAs *param));
EXTERN S16 szPrntForbiddenLACs ARGS ((SztForbiddenLACs *param));
EXTERN S16 szPrnt_ExtnForbiddenLAs_Item_ExtIEsCls ARGS ((Szt_ExtnForbiddenLAs_Item_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_ForbiddenLAs_Item_ExtIEs ARGS ((SztProtExtnField_ForbiddenLAs_Item_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_ForbiddenLAs_Item_ExtIEs ARGS ((SztProtExtnCont_ForbiddenLAs_Item_ExtIEs *param));
EXTERN S16 szPrntForbiddenLAs_Item ARGS ((SztForbiddenLAs_Item *param));
EXTERN S16 szPrntForbiddenLAs ARGS ((SztForbiddenLAs *param));
EXTERN S16 szPrnt_ExtnGUMMEI_ExtIEsCls ARGS ((Szt_ExtnGUMMEI_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_GUMMEI_ExtIEs ARGS ((SztProtExtnField_GUMMEI_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_GUMMEI_ExtIEs ARGS ((SztProtExtnCont_GUMMEI_ExtIEs *param));
EXTERN S16 szPrntGUMMEI ARGS ((SztGUMMEI *param));
EXTERN S16 szPrnt_ExtnHovrRestrnLst_ExtIEsCls ARGS ((Szt_ExtnHovrRestrnLst_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_HovrRestrnLst_ExtIEs ARGS ((SztProtExtnField_HovrRestrnLst_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_HovrRestrnLst_ExtIEs ARGS ((SztProtExtnCont_HovrRestrnLst_ExtIEs *param));
EXTERN S16 szPrntHovrRestrnLst ARGS ((SztHovrRestrnLst *param));
EXTERN S16 szPrnt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls ARGS ((Szt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_LastVisitedEUTRANCellInform_ExtIEs ARGS ((SztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs ARGS ((SztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs *param));
EXTERN S16 szPrntLastVisitedEUTRANCellInform ARGS ((SztLastVisitedEUTRANCellInform *param));
EXTERN S16 szPrntLastVisitedGERANCellInform ARGS ((SztLastVisitedGERANCellInform *param));
EXTERN S16 szPrntLastVisitedCell_Item ARGS ((SztLastVisitedCell_Item *param));
EXTERN S16 szPrntOverloadResp ARGS ((SztOverloadResp *param));
EXTERN S16 szPrnt_ExtnRqstTyp_ExtIEsCls ARGS ((Szt_ExtnRqstTyp_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_RqstTyp_ExtIEs ARGS ((SztProtExtnField_RqstTyp_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_RqstTyp_ExtIEs ARGS ((SztProtExtnCont_RqstTyp_ExtIEs *param));
EXTERN S16 szPrntRqstTyp ARGS ((SztRqstTyp *param));
EXTERN S16 szPrntRIMRoutingAddr ARGS ((SztRIMRoutingAddr *param));
EXTERN S16 szPrnt_ExtnRIMTfr_ExtIEsCls ARGS ((Szt_ExtnRIMTfr_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_RIMTfr_ExtIEs ARGS ((SztProtExtnField_RIMTfr_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_RIMTfr_ExtIEs ARGS ((SztProtExtnCont_RIMTfr_ExtIEs *param));
EXTERN S16 szPrntRIMTfr ARGS ((SztRIMTfr *param));
EXTERN S16 szPrnt_ExtnSecurCntxt_ExtIEsCls ARGS ((Szt_ExtnSecurCntxt_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_SecurCntxt_ExtIEs ARGS ((SztProtExtnField_SecurCntxt_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_SecurCntxt_ExtIEs ARGS ((SztProtExtnCont_SecurCntxt_ExtIEs *param));
EXTERN S16 szPrntSecurCntxt ARGS ((SztSecurCntxt *param));
EXTERN S16 szPrnt_ExtnX2TNLConfigInfo_ExtIEsCls ARGS ((Szt_ExtnX2TNLConfigInfo_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_X2TNLConfigInfo_ExtIEs ARGS ((SztProtExtnField_X2TNLConfigInfo_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_X2TNLConfigInfo_ExtIEs ARGS ((SztProtExtnCont_X2TNLConfigInfo_ExtIEs *param));
EXTERN S16 szPrntX2TNLConfigInfo ARGS ((SztX2TNLConfigInfo *param));
EXTERN S16 szPrnt_ExtnSONInformReply_ExtIEsCls ARGS ((Szt_ExtnSONInformReply_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_SONInformReply_ExtIEs ARGS ((SztProtExtnField_SONInformReply_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_SONInformReply_ExtIEs ARGS ((SztProtExtnCont_SONInformReply_ExtIEs *param));
EXTERN S16 szPrntSONInformReply ARGS ((SztSONInformReply *param));
EXTERN S16 szPrntSONInform ARGS ((SztSONInform *param));
EXTERN S16 szPrnt_ExtnTgeteNB_ID_ExtIEsCls ARGS ((Szt_ExtnTgeteNB_ID_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_TgeteNB_ID_ExtIEs ARGS ((SztProtExtnField_TgeteNB_ID_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_TgeteNB_ID_ExtIEs ARGS ((SztProtExtnCont_TgeteNB_ID_ExtIEs *param));
EXTERN S16 szPrntTgeteNB_ID ARGS ((SztTgeteNB_ID *param));
EXTERN S16 szPrnt_ExtnSrceNB_ID_ExtIEsCls ARGS ((Szt_ExtnSrceNB_ID_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_SrceNB_ID_ExtIEs ARGS ((SztProtExtnField_SrceNB_ID_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_SrceNB_ID_ExtIEs ARGS ((SztProtExtnCont_SrceNB_ID_ExtIEs *param));
EXTERN S16 szPrntSrceNB_ID ARGS ((SztSrceNB_ID *param));
EXTERN S16 szPrnt_ExtnSONConfigTfr_ExtIEsCls ARGS ((Szt_ExtnSONConfigTfr_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_SONConfigTfr_ExtIEs ARGS ((SztProtExtnField_SONConfigTfr_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_SONConfigTfr_ExtIEs ARGS ((SztProtExtnCont_SONConfigTfr_ExtIEs *param));
EXTERN S16 szPrntSONConfigTfr ARGS ((SztSONConfigTfr *param));
EXTERN S16 szPrntUE_HistoryInform ARGS ((SztUE_HistoryInform *param));
EXTERN S16 szPrnt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls ARGS ((Szt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs ARGS ((SztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs ARGS ((SztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs *param));
EXTERN S16 szPrntSrceNB_ToTgeteNB_TprntCont ARGS ((SztSrceNB_ToTgeteNB_TprntCont *param));
EXTERN S16 szPrntSrvdPLMNs ARGS ((SztSrvdPLMNs *param));
EXTERN S16 szPrntSrvdGroupIDs ARGS ((SztSrvdGroupIDs *param));
EXTERN S16 szPrntSrvdMMECs ARGS ((SztSrvdMMECs *param));
EXTERN S16 szPrnt_ExtnSrvdGUMMEIsItem_ExtIEsCls ARGS ((Szt_ExtnSrvdGUMMEIsItem_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_SrvdGUMMEIsItem_ExtIEs ARGS ((SztProtExtnField_SrvdGUMMEIsItem_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_SrvdGUMMEIsItem_ExtIEs ARGS ((SztProtExtnCont_SrvdGUMMEIsItem_ExtIEs *param));
EXTERN S16 szPrntSrvdGUMMEIsItem ARGS ((SztSrvdGUMMEIsItem *param));
EXTERN S16 szPrntSrvdGUMMEIs ARGS ((SztSrvdGUMMEIs *param));
EXTERN S16 szPrnt_ExtnSuppTAs_Item_ExtIEsCls ARGS ((Szt_ExtnSuppTAs_Item_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_SuppTAs_Item_ExtIEs ARGS ((SztProtExtnField_SuppTAs_Item_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_SuppTAs_Item_ExtIEs ARGS ((SztProtExtnCont_SuppTAs_Item_ExtIEs *param));
EXTERN S16 szPrntSuppTAs_Item ARGS ((SztSuppTAs_Item *param));
EXTERN S16 szPrntSuppTAs ARGS ((SztSuppTAs *param));
EXTERN S16 szPrnt_ExtnS_TMSI_ExtIEsCls ARGS ((Szt_ExtnS_TMSI_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_S_TMSI_ExtIEs ARGS ((SztProtExtnField_S_TMSI_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_S_TMSI_ExtIEs ARGS ((SztProtExtnCont_S_TMSI_ExtIEs *param));
EXTERN S16 szPrntS_TMSI ARGS ((SztS_TMSI *param));
EXTERN S16 szPrntTAILstforWarning ARGS ((SztTAILstforWarning *param));
EXTERN S16 szPrnt_ExtnTgetRNC_ID_ExtIEsCls ARGS ((Szt_ExtnTgetRNC_ID_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_TgetRNC_ID_ExtIEs ARGS ((SztProtExtnField_TgetRNC_ID_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_TgetRNC_ID_ExtIEs ARGS ((SztProtExtnCont_TgetRNC_ID_ExtIEs *param));
EXTERN S16 szPrntTgetRNC_ID ARGS ((SztTgetRNC_ID *param));
EXTERN S16 szPrntTgetID ARGS ((SztTgetID *param));
EXTERN S16 szPrnt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls ARGS ((Szt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs ARGS ((SztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs ARGS ((SztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs *param));
EXTERN S16 szPrntTgeteNB_ToSrceNB_TprntCont ARGS ((SztTgeteNB_ToSrceNB_TprntCont *param));
EXTERN S16 szPrnt_ExtnTraceActvn_ExtIEsCls ARGS ((Szt_ExtnTraceActvn_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_TraceActvn_ExtIEs ARGS ((SztProtExtnField_TraceActvn_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_TraceActvn_ExtIEs ARGS ((SztProtExtnCont_TraceActvn_ExtIEs *param));
EXTERN S16 szPrntTraceActvn ARGS ((SztTraceActvn *param));
EXTERN S16 szPrnt_ExtnUEAgg_MaxBitrates_ExtIEsCls ARGS ((Szt_ExtnUEAgg_MaxBitrates_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_UEAgg_MaxBitrates_ExtIEs ARGS ((SztProtExtnField_UEAgg_MaxBitrates_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_UEAgg_MaxBitrates_ExtIEs ARGS ((SztProtExtnCont_UEAgg_MaxBitrates_ExtIEs *param));
EXTERN S16 szPrntUEAggMaxBitrate ARGS ((SztUEAggMaxBitrate *param));
EXTERN S16 szPrnt_ExtnUE_S1AP_ID_pair_ExtIEsCls ARGS ((Szt_ExtnUE_S1AP_ID_pair_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_UE_S1AP_ID_pair_ExtIEs ARGS ((SztProtExtnField_UE_S1AP_ID_pair_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_UE_S1AP_ID_pair_ExtIEs ARGS ((SztProtExtnCont_UE_S1AP_ID_pair_ExtIEs *param));
EXTERN S16 szPrntUE_S1AP_ID_pair ARGS ((SztUE_S1AP_ID_pair *param));
EXTERN S16 szPrntUE_S1AP_IDs ARGS ((SztUE_S1AP_IDs *param));
EXTERN S16 szPrnt_ExtnUE_assocLogS1_ConItemExtIEsCls ARGS ((Szt_ExtnUE_assocLogS1_ConItemExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_UE_assocLogS1_ConItemExtIEs ARGS ((SztProtExtnField_UE_assocLogS1_ConItemExtIEs *param));
EXTERN S16 szPrntProtExtnCont_UE_assocLogS1_ConItemExtIEs ARGS ((SztProtExtnCont_UE_assocLogS1_ConItemExtIEs *param));
EXTERN S16 szPrntUE_assocLogS1_ConItem ARGS ((SztUE_assocLogS1_ConItem *param));
EXTERN S16 szPrntUEPagID ARGS ((SztUEPagID *param));
EXTERN S16 szPrnt_ExtnUESecurCapabilities_ExtIEsCls ARGS ((Szt_ExtnUESecurCapabilities_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_UESecurCapabilities_ExtIEs ARGS ((SztProtExtnField_UESecurCapabilities_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_UESecurCapabilities_ExtIEs ARGS ((SztProtExtnCont_UESecurCapabilities_ExtIEs *param));
EXTERN S16 szPrntUESecurCapabilities ARGS ((SztUESecurCapabilities *param));
EXTERN S16 szPrntWarningAreaLst ARGS ((SztWarningAreaLst *param));
EXTERN S16 szPrnt_ValueHovrReqdIEsCls ARGS ((Szt_ValueHovrReqdIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_HovrReqdIEs ARGS ((SztProtIE_Field_HovrReqdIEs *param));
EXTERN S16 szPrntProtIE_Cont_HovrReqdIEs ARGS ((SztProtIE_Cont_HovrReqdIEs *param));
EXTERN S16 szPrntHovrReqd ARGS ((SztHovrReqd *param));
EXTERN S16 szPrnt_ExtnE_RABDataFwdingItem_ExtIEsCls ARGS ((Szt_ExtnE_RABDataFwdingItem_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_E_RABDataFwdingItem_ExtIEs ARGS ((SztProtExtnField_E_RABDataFwdingItem_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_E_RABDataFwdingItem_ExtIEs ARGS ((SztProtExtnCont_E_RABDataFwdingItem_ExtIEs *param));
EXTERN S16 szPrntE_RABDataFwdingItem ARGS ((SztE_RABDataFwdingItem *param));
EXTERN S16 szPrnt_ValueE_RABDataFwdingItemIEsCls ARGS ((Szt_ValueE_RABDataFwdingItemIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_E_RABDataFwdingItemIEs ARGS ((SztProtIE_Field_E_RABDataFwdingItemIEs *param));
EXTERN S16 szPrntProtIE_ContLst_E_RABDataFwdingItemIEs ARGS ((SztProtIE_ContLst_E_RABDataFwdingItemIEs *param));
EXTERN S16 szPrnt_ValueHovrCmmdIEsCls ARGS ((Szt_ValueHovrCmmdIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_HovrCmmdIEs ARGS ((SztProtIE_Field_HovrCmmdIEs *param));
EXTERN S16 szPrntProtIE_Cont_HovrCmmdIEs ARGS ((SztProtIE_Cont_HovrCmmdIEs *param));
EXTERN S16 szPrntHovrCmmd ARGS ((SztHovrCmmd *param));
EXTERN S16 szPrnt_ValueHovrPrepFailIEsCls ARGS ((Szt_ValueHovrPrepFailIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_HovrPrepFailIEs ARGS ((SztProtIE_Field_HovrPrepFailIEs *param));
EXTERN S16 szPrntProtIE_Cont_HovrPrepFailIEs ARGS ((SztProtIE_Cont_HovrPrepFailIEs *param));
EXTERN S16 szPrntHovrPrepFail ARGS ((SztHovrPrepFail *param));
EXTERN S16 szPrnt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls ARGS ((Szt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs ARGS ((SztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs ARGS ((SztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs *param));
EXTERN S16 szPrntE_RABToBeSetupItemHOReq ARGS ((SztE_RABToBeSetupItemHOReq *param));
EXTERN S16 szPrnt_ValueE_RABToBeSetupItemHOReqIEsCls ARGS ((Szt_ValueE_RABToBeSetupItemHOReqIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_E_RABToBeSetupItemHOReqIEs ARGS ((SztProtIE_Field_E_RABToBeSetupItemHOReqIEs *param));
EXTERN S16 szPrntProtIE_ContLst_E_RABToBeSetupItemHOReqIEs ARGS ((SztProtIE_ContLst_E_RABToBeSetupItemHOReqIEs *param));
EXTERN S16 szPrnt_ValueHovrRqstIEsCls ARGS ((Szt_ValueHovrRqstIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_HovrRqstIEs ARGS ((SztProtIE_Field_HovrRqstIEs *param));
EXTERN S16 szPrntProtIE_Cont_HovrRqstIEs ARGS ((SztProtIE_Cont_HovrRqstIEs *param));
EXTERN S16 szPrntHovrRqst ARGS ((SztHovrRqst *param));
EXTERN S16 szPrnt_ExtnE_RABAdmtdItem_ExtIEsCls ARGS ((Szt_ExtnE_RABAdmtdItem_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_E_RABAdmtdItem_ExtIEs ARGS ((SztProtExtnField_E_RABAdmtdItem_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_E_RABAdmtdItem_ExtIEs ARGS ((SztProtExtnCont_E_RABAdmtdItem_ExtIEs *param));
EXTERN S16 szPrntE_RABAdmtdItem ARGS ((SztE_RABAdmtdItem *param));
EXTERN S16 szPrnt_ValueE_RABAdmtdItemIEsCls ARGS ((Szt_ValueE_RABAdmtdItemIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_E_RABAdmtdItemIEs ARGS ((SztProtIE_Field_E_RABAdmtdItemIEs *param));
EXTERN S16 szPrntProtIE_ContLst_E_RABAdmtdItemIEs ARGS ((SztProtIE_ContLst_E_RABAdmtdItemIEs *param));
EXTERN S16 szPrnt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls ARGS ((Szt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs ARGS ((SztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs *param));
EXTERN S16 szPrntProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs ARGS ((SztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs *param));
EXTERN S16 szPrntE_RABFailedToSetupItemHOReqAck ARGS ((SztE_RABFailedToSetupItemHOReqAck *param));
EXTERN S16 szPrnt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls ARGS ((Szt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs ARGS ((SztProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs *param));
EXTERN S16 szPrntProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs ARGS ((SztProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs *param));
EXTERN S16 szPrnt_ValueHovrRqstAckgIEsCls ARGS ((Szt_ValueHovrRqstAckgIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_HovrRqstAckgIEs ARGS ((SztProtIE_Field_HovrRqstAckgIEs *param));
EXTERN S16 szPrntProtIE_Cont_HovrRqstAckgIEs ARGS ((SztProtIE_Cont_HovrRqstAckgIEs *param));
EXTERN S16 szPrntHovrRqstAckg ARGS ((SztHovrRqstAckg *param));
EXTERN S16 szPrnt_ValueHovrFailIEsCls ARGS ((Szt_ValueHovrFailIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_HovrFailIEs ARGS ((SztProtIE_Field_HovrFailIEs *param));
EXTERN S16 szPrntProtIE_Cont_HovrFailIEs ARGS ((SztProtIE_Cont_HovrFailIEs *param));
EXTERN S16 szPrntHovrFail ARGS ((SztHovrFail *param));
EXTERN S16 szPrnt_ValueHovrNtfyIEsCls ARGS ((Szt_ValueHovrNtfyIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_HovrNtfyIEs ARGS ((SztProtIE_Field_HovrNtfyIEs *param));
EXTERN S16 szPrntProtIE_Cont_HovrNtfyIEs ARGS ((SztProtIE_Cont_HovrNtfyIEs *param));
EXTERN S16 szPrntHovrNtfy ARGS ((SztHovrNtfy *param));
EXTERN S16 szPrnt_ExtnE_RABToBeSwedDLItem_ExtIEsCls ARGS ((Szt_ExtnE_RABToBeSwedDLItem_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_E_RABToBeSwedDLItem_ExtIEs ARGS ((SztProtExtnField_E_RABToBeSwedDLItem_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_E_RABToBeSwedDLItem_ExtIEs ARGS ((SztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs *param));
EXTERN S16 szPrntE_RABToBeSwedDLItem ARGS ((SztE_RABToBeSwedDLItem *param));
EXTERN S16 szPrnt_ValueE_RABToBeSwedDLItemIEsCls ARGS ((Szt_ValueE_RABToBeSwedDLItemIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_E_RABToBeSwedDLItemIEs ARGS ((SztProtIE_Field_E_RABToBeSwedDLItemIEs *param));
EXTERN S16 szPrntProtIE_ContLst_E_RABToBeSwedDLItemIEs ARGS ((SztProtIE_ContLst_E_RABToBeSwedDLItemIEs *param));
EXTERN S16 szPrnt_ValuePathSwRqstIEsCls ARGS ((Szt_ValuePathSwRqstIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_PathSwRqstIEs ARGS ((SztProtIE_Field_PathSwRqstIEs *param));
EXTERN S16 szPrntProtIE_Cont_PathSwRqstIEs ARGS ((SztProtIE_Cont_PathSwRqstIEs *param));
EXTERN S16 szPrntPathSwRqst ARGS ((SztPathSwRqst *param));
EXTERN S16 szPrnt_ExtnE_RABToBeSwedULItem_ExtIEsCls ARGS ((Szt_ExtnE_RABToBeSwedULItem_ExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_E_RABToBeSwedULItem_ExtIEs ARGS ((SztProtExtnField_E_RABToBeSwedULItem_ExtIEs *param));
EXTERN S16 szPrntProtExtnCont_E_RABToBeSwedULItem_ExtIEs ARGS ((SztProtExtnCont_E_RABToBeSwedULItem_ExtIEs *param));
EXTERN S16 szPrntE_RABToBeSwedULItem ARGS ((SztE_RABToBeSwedULItem *param));
EXTERN S16 szPrnt_ValueE_RABToBeSwedULItemIEsCls ARGS ((Szt_ValueE_RABToBeSwedULItemIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_E_RABToBeSwedULItemIEs ARGS ((SztProtIE_Field_E_RABToBeSwedULItemIEs *param));
EXTERN S16 szPrntProtIE_ContLst_E_RABToBeSwedULItemIEs ARGS ((SztProtIE_ContLst_E_RABToBeSwedULItemIEs *param));
EXTERN S16 szPrnt_ValuePathSwRqstAckgIEsCls ARGS ((Szt_ValuePathSwRqstAckgIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_PathSwRqstAckgIEs ARGS ((SztProtIE_Field_PathSwRqstAckgIEs *param));
EXTERN S16 szPrntProtIE_Cont_PathSwRqstAckgIEs ARGS ((SztProtIE_Cont_PathSwRqstAckgIEs *param));
EXTERN S16 szPrntPathSwRqstAckg ARGS ((SztPathSwRqstAckg *param));
EXTERN S16 szPrnt_ValuePathSwRqstFailIEsCls ARGS ((Szt_ValuePathSwRqstFailIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_PathSwRqstFailIEs ARGS ((SztProtIE_Field_PathSwRqstFailIEs *param));
EXTERN S16 szPrntProtIE_Cont_PathSwRqstFailIEs ARGS ((SztProtIE_Cont_PathSwRqstFailIEs *param));
EXTERN S16 szPrntPathSwRqstFail ARGS ((SztPathSwRqstFail *param));
EXTERN S16 szPrnt_ValueHovrCancelIEsCls ARGS ((Szt_ValueHovrCancelIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_HovrCancelIEs ARGS ((SztProtIE_Field_HovrCancelIEs *param));
EXTERN S16 szPrntProtIE_Cont_HovrCancelIEs ARGS ((SztProtIE_Cont_HovrCancelIEs *param));
EXTERN S16 szPrntHovrCancel ARGS ((SztHovrCancel *param));
EXTERN S16 szPrnt_ValueHovrCancelAckgIEsCls ARGS ((Szt_ValueHovrCancelAckgIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_HovrCancelAckgIEs ARGS ((SztProtIE_Field_HovrCancelAckgIEs *param));
EXTERN S16 szPrntProtIE_Cont_HovrCancelAckgIEs ARGS ((SztProtIE_Cont_HovrCancelAckgIEs *param));
EXTERN S16 szPrntHovrCancelAckg ARGS ((SztHovrCancelAckg *param));
EXTERN S16 szPrnt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls ARGS ((Szt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs ARGS ((SztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs *param));
EXTERN S16 szPrntProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs ARGS ((SztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs *param));
EXTERN S16 szPrntE_RABToBeSetupItemBrSUReq ARGS ((SztE_RABToBeSetupItemBrSUReq *param));
EXTERN S16 szPrnt_ValueE_RABToBeSetupItemBrSUReqIEsCls ARGS ((Szt_ValueE_RABToBeSetupItemBrSUReqIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_E_RABToBeSetupItemBrSUReqIEs ARGS ((SztProtIE_Field_E_RABToBeSetupItemBrSUReqIEs *param));
EXTERN S16 szPrntE_RABToBeSetupLstBrSUReq ARGS ((SztE_RABToBeSetupLstBrSUReq *param));
EXTERN S16 szPrnt_ValueE_RABSetupRqstIEsCls ARGS ((Szt_ValueE_RABSetupRqstIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_E_RABSetupRqstIEs ARGS ((SztProtIE_Field_E_RABSetupRqstIEs *param));
EXTERN S16 szPrntProtIE_Cont_E_RABSetupRqstIEs ARGS ((SztProtIE_Cont_E_RABSetupRqstIEs *param));
EXTERN S16 szPrntE_RABSetupRqst ARGS ((SztE_RABSetupRqst *param));
EXTERN S16 szPrnt_ExtnE_RABSetupItemBrSUResExtIEsCls ARGS ((Szt_ExtnE_RABSetupItemBrSUResExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_E_RABSetupItemBrSUResExtIEs ARGS ((SztProtExtnField_E_RABSetupItemBrSUResExtIEs *param));
EXTERN S16 szPrntProtExtnCont_E_RABSetupItemBrSUResExtIEs ARGS ((SztProtExtnCont_E_RABSetupItemBrSUResExtIEs *param));
EXTERN S16 szPrntE_RABSetupItemBrSURes ARGS ((SztE_RABSetupItemBrSURes *param));
EXTERN S16 szPrnt_ValueE_RABSetupItemBrSUResIEsCls ARGS ((Szt_ValueE_RABSetupItemBrSUResIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_E_RABSetupItemBrSUResIEs ARGS ((SztProtIE_Field_E_RABSetupItemBrSUResIEs *param));
EXTERN S16 szPrntE_RABSetupLstBrSURes ARGS ((SztE_RABSetupLstBrSURes *param));
EXTERN S16 szPrnt_ValueE_RABSetupRespIEsCls ARGS ((Szt_ValueE_RABSetupRespIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_E_RABSetupRespIEs ARGS ((SztProtIE_Field_E_RABSetupRespIEs *param));
EXTERN S16 szPrntProtIE_Cont_E_RABSetupRespIEs ARGS ((SztProtIE_Cont_E_RABSetupRespIEs *param));
EXTERN S16 szPrntE_RABSetupResp ARGS ((SztE_RABSetupResp *param));
EXTERN S16 szPrnt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls ARGS ((Szt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs ARGS ((SztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs *param));
EXTERN S16 szPrntProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs ARGS ((SztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs *param));
EXTERN S16 szPrntE_RABToBeMdfdItemBrModReq ARGS ((SztE_RABToBeMdfdItemBrModReq *param));
EXTERN S16 szPrnt_ValueE_RABToBeMdfdItemBrModReqIEsCls ARGS ((Szt_ValueE_RABToBeMdfdItemBrModReqIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_E_RABToBeMdfdItemBrModReqIEs ARGS ((SztProtIE_Field_E_RABToBeMdfdItemBrModReqIEs *param));
EXTERN S16 szPrntE_RABToBeMdfdLstBrModReq ARGS ((SztE_RABToBeMdfdLstBrModReq *param));
EXTERN S16 szPrnt_ValueE_RABMdfyRqstIEsCls ARGS ((Szt_ValueE_RABMdfyRqstIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_E_RABMdfyRqstIEs ARGS ((SztProtIE_Field_E_RABMdfyRqstIEs *param));
EXTERN S16 szPrntProtIE_Cont_E_RABMdfyRqstIEs ARGS ((SztProtIE_Cont_E_RABMdfyRqstIEs *param));
EXTERN S16 szPrntE_RABMdfyRqst ARGS ((SztE_RABMdfyRqst *param));
EXTERN S16 szPrnt_ExtnE_RABMdfyItemBrModResExtIEsCls ARGS ((Szt_ExtnE_RABMdfyItemBrModResExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_E_RABMdfyItemBrModResExtIEs ARGS ((SztProtExtnField_E_RABMdfyItemBrModResExtIEs *param));
EXTERN S16 szPrntProtExtnCont_E_RABMdfyItemBrModResExtIEs ARGS ((SztProtExtnCont_E_RABMdfyItemBrModResExtIEs *param));
EXTERN S16 szPrntE_RABMdfyItemBrModRes ARGS ((SztE_RABMdfyItemBrModRes *param));
EXTERN S16 szPrnt_ValueE_RABMdfyItemBrModResIEsCls ARGS ((Szt_ValueE_RABMdfyItemBrModResIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_E_RABMdfyItemBrModResIEs ARGS ((SztProtIE_Field_E_RABMdfyItemBrModResIEs *param));
EXTERN S16 szPrntE_RABMdfyLstBrModRes ARGS ((SztE_RABMdfyLstBrModRes *param));
EXTERN S16 szPrnt_ValueE_RABMdfyRespIEsCls ARGS ((Szt_ValueE_RABMdfyRespIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_E_RABMdfyRespIEs ARGS ((SztProtIE_Field_E_RABMdfyRespIEs *param));
EXTERN S16 szPrntProtIE_Cont_E_RABMdfyRespIEs ARGS ((SztProtIE_Cont_E_RABMdfyRespIEs *param));
EXTERN S16 szPrntE_RABMdfyResp ARGS ((SztE_RABMdfyResp *param));
EXTERN S16 szPrnt_ValueE_RABRlsCmmdIEsCls ARGS ((Szt_ValueE_RABRlsCmmdIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_E_RABRlsCmmdIEs ARGS ((SztProtIE_Field_E_RABRlsCmmdIEs *param));
EXTERN S16 szPrntProtIE_Cont_E_RABRlsCmmdIEs ARGS ((SztProtIE_Cont_E_RABRlsCmmdIEs *param));
EXTERN S16 szPrnt_ExtnE_RABRlsItemBrRelCompExtIEsCls ARGS ((Szt_ExtnE_RABRlsItemBrRelCompExtIEsCls *param, U32 val));
EXTERN S16 szPrntE_RABRlsCmmd ARGS ((SztE_RABRlsCmmd *param));
EXTERN S16 szPrntProtExtnField_E_RABRlsItemBrRelCompExtIEs ARGS ((SztProtExtnField_E_RABRlsItemBrRelCompExtIEs *param));
EXTERN S16 szPrntProtExtnCont_E_RABRlsItemBrRelCompExtIEs ARGS ((SztProtExtnCont_E_RABRlsItemBrRelCompExtIEs *param));
EXTERN S16 szPrntE_RABRlsItemBrRelComp ARGS ((SztE_RABRlsItemBrRelComp *param));
EXTERN S16 szPrnt_ValueE_RABRlsItemBrRelCompIEsCls ARGS ((Szt_ValueE_RABRlsItemBrRelCompIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_E_RABRlsItemBrRelCompIEs ARGS ((SztProtIE_Field_E_RABRlsItemBrRelCompIEs *param));
EXTERN S16 szPrntE_RABRlsLstBrRelComp ARGS ((SztE_RABRlsLstBrRelComp *param));
EXTERN S16 szPrnt_ValueE_RABRlsRespIEsCls ARGS ((Szt_ValueE_RABRlsRespIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_E_RABRlsRespIEs ARGS ((SztProtIE_Field_E_RABRlsRespIEs *param));
EXTERN S16 szPrntProtIE_Cont_E_RABRlsRespIEs ARGS ((SztProtIE_Cont_E_RABRlsRespIEs *param));
EXTERN S16 szPrntE_RABRlsResp ARGS ((SztE_RABRlsResp *param));
EXTERN S16 szPrnt_ValueE_RABRlsIndIEsCls ARGS ((Szt_ValueE_RABRlsIndIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_E_RABRlsIndIEs ARGS ((SztProtIE_Field_E_RABRlsIndIEs *param));
EXTERN S16 szPrntProtIE_Cont_E_RABRlsIndIEs ARGS ((SztProtIE_Cont_E_RABRlsIndIEs *param));
EXTERN S16 szPrntE_RABRlsInd ARGS ((SztE_RABRlsInd *param));
EXTERN S16 szPrnt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls ARGS ((Szt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs ARGS ((SztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs *param));
EXTERN S16 szPrntProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs ARGS ((SztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs *param));
EXTERN S16 szPrntE_RABToBeSetupItemCtxtSUReq ARGS ((SztE_RABToBeSetupItemCtxtSUReq *param));
EXTERN S16 szPrnt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls ARGS ((Szt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs ARGS ((SztProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs *param));
EXTERN S16 szPrntE_RABToBeSetupLstCtxtSUReq ARGS ((SztE_RABToBeSetupLstCtxtSUReq *param));
EXTERN S16 szPrnt_ValueInitCntxtSetupRqstIEsCls ARGS ((Szt_ValueInitCntxtSetupRqstIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_InitCntxtSetupRqstIEs ARGS ((SztProtIE_Field_InitCntxtSetupRqstIEs *param));
EXTERN S16 szPrntProtIE_Cont_InitCntxtSetupRqstIEs ARGS ((SztProtIE_Cont_InitCntxtSetupRqstIEs *param));
EXTERN S16 szPrntInitCntxtSetupRqst ARGS ((SztInitCntxtSetupRqst *param));
EXTERN S16 szPrnt_ExtnE_RABSetupItemCtxtSUResExtIEsCls ARGS ((Szt_ExtnE_RABSetupItemCtxtSUResExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_E_RABSetupItemCtxtSUResExtIEs ARGS ((SztProtExtnField_E_RABSetupItemCtxtSUResExtIEs *param));
EXTERN S16 szPrntProtExtnCont_E_RABSetupItemCtxtSUResExtIEs ARGS ((SztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs *param));
EXTERN S16 szPrntE_RABSetupItemCtxtSURes ARGS ((SztE_RABSetupItemCtxtSURes *param));
EXTERN S16 szPrnt_ValueE_RABSetupItemCtxtSUResIEsCls ARGS ((Szt_ValueE_RABSetupItemCtxtSUResIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_E_RABSetupItemCtxtSUResIEs ARGS ((SztProtIE_Field_E_RABSetupItemCtxtSUResIEs *param));
EXTERN S16 szPrntE_RABSetupLstCtxtSURes ARGS ((SztE_RABSetupLstCtxtSURes *param));
EXTERN S16 szPrnt_ValueInitCntxtSetupRespIEsCls ARGS ((Szt_ValueInitCntxtSetupRespIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_InitCntxtSetupRespIEs ARGS ((SztProtIE_Field_InitCntxtSetupRespIEs *param));
EXTERN S16 szPrntProtIE_Cont_InitCntxtSetupRespIEs ARGS ((SztProtIE_Cont_InitCntxtSetupRespIEs *param));
EXTERN S16 szPrntInitCntxtSetupResp ARGS ((SztInitCntxtSetupResp *param));
EXTERN S16 szPrnt_ValueInitCntxtSetupFailIEsCls ARGS ((Szt_ValueInitCntxtSetupFailIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_InitCntxtSetupFailIEs ARGS ((SztProtIE_Field_InitCntxtSetupFailIEs *param));
EXTERN S16 szPrntProtIE_Cont_InitCntxtSetupFailIEs ARGS ((SztProtIE_Cont_InitCntxtSetupFailIEs *param));
EXTERN S16 szPrntInitCntxtSetupFail ARGS ((SztInitCntxtSetupFail *param));
EXTERN S16 szPrnt_ExtnTAIItemExtIEsCls ARGS ((Szt_ExtnTAIItemExtIEsCls *param, U32 val));
EXTERN S16 szPrntProtExtnField_TAIItemExtIEs ARGS ((SztProtExtnField_TAIItemExtIEs *param));
EXTERN S16 szPrntProtExtnCont_TAIItemExtIEs ARGS ((SztProtExtnCont_TAIItemExtIEs *param));
EXTERN S16 szPrntTAIItem ARGS ((SztTAIItem *param));
EXTERN S16 szPrnt_ValueTAIItemIEsCls ARGS ((Szt_ValueTAIItemIEsCls *param, U32 val));
EXTERN S16 szPrntTAILst ARGS ((SztTAILst *param));
EXTERN S16 szPrnt_ValuePagIEsCls ARGS ((Szt_ValuePagIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_PagIEs ARGS ((SztProtIE_Field_PagIEs *param));
EXTERN S16 szPrntProtIE_Cont_PagIEs ARGS ((SztProtIE_Cont_PagIEs *param));
EXTERN S16 szPrntPag ARGS ((SztPag *param));
EXTERN S16 szPrnt_ValueUECntxtRlsRqst_IEsCls ARGS ((Szt_ValueUECntxtRlsRqst_IEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_UECntxtRlsRqst_IEs ARGS ((SztProtIE_Field_UECntxtRlsRqst_IEs *param));
EXTERN S16 szPrntProtIE_Cont_UECntxtRlsRqst_IEs ARGS ((SztProtIE_Cont_UECntxtRlsRqst_IEs *param));
EXTERN S16 szPrntUECntxtRlsRqst ARGS ((SztUECntxtRlsRqst *param));
EXTERN S16 szPrnt_ValueUECntxtRlsCmmd_IEsCls ARGS ((Szt_ValueUECntxtRlsCmmd_IEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_UECntxtRlsCmmd_IEs ARGS ((SztProtIE_Field_UECntxtRlsCmmd_IEs *param));
EXTERN S16 szPrntProtIE_Cont_UECntxtRlsCmmd_IEs ARGS ((SztProtIE_Cont_UECntxtRlsCmmd_IEs *param));
EXTERN S16 szPrntUECntxtRlsCmmd ARGS ((SztUECntxtRlsCmmd *param));
EXTERN S16 szPrnt_ValueUECntxtRlsComplete_IEsCls ARGS ((Szt_ValueUECntxtRlsComplete_IEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_UECntxtRlsComplete_IEs ARGS ((SztProtIE_Field_UECntxtRlsComplete_IEs *param));
EXTERN S16 szPrntProtIE_Cont_UECntxtRlsComplete_IEs ARGS ((SztProtIE_Cont_UECntxtRlsComplete_IEs *param));
EXTERN S16 szPrntUECntxtRlsComplete ARGS ((SztUECntxtRlsComplete *param));
EXTERN S16 szPrnt_ValueUECntxtModificationRqstIEsCls ARGS ((Szt_ValueUECntxtModificationRqstIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_UECntxtModificationRqstIEs ARGS ((SztProtIE_Field_UECntxtModificationRqstIEs *param));
EXTERN S16 szPrntProtIE_Cont_UECntxtModificationRqstIEs ARGS ((SztProtIE_Cont_UECntxtModificationRqstIEs *param));
EXTERN S16 szPrntUECntxtModificationRqst ARGS ((SztUECntxtModificationRqst *param));
EXTERN S16 szPrnt_ValueUECntxtModificationRespIEsCls ARGS ((Szt_ValueUECntxtModificationRespIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_UECntxtModificationRespIEs ARGS ((SztProtIE_Field_UECntxtModificationRespIEs *param));
EXTERN S16 szPrntProtIE_Cont_UECntxtModificationRespIEs ARGS ((SztProtIE_Cont_UECntxtModificationRespIEs *param));
EXTERN S16 szPrntUECntxtModificationResp ARGS ((SztUECntxtModificationResp *param));
EXTERN S16 szPrnt_ValueUECntxtModificationFailIEsCls ARGS ((Szt_ValueUECntxtModificationFailIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_UECntxtModificationFailIEs ARGS ((SztProtIE_Field_UECntxtModificationFailIEs *param));
EXTERN S16 szPrntProtIE_Cont_UECntxtModificationFailIEs ARGS ((SztProtIE_Cont_UECntxtModificationFailIEs *param));
EXTERN S16 szPrntUECntxtModificationFail ARGS ((SztUECntxtModificationFail *param));
EXTERN S16 szPrnt_ValueDlnkNASTport_IEsCls ARGS ((Szt_ValueDlnkNASTport_IEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_DlnkNASTport_IEs ARGS ((SztProtIE_Field_DlnkNASTport_IEs *param));
EXTERN S16 szPrntProtIE_Cont_DlnkNASTport_IEs ARGS ((SztProtIE_Cont_DlnkNASTport_IEs *param));
EXTERN S16 szPrntDlnkNASTport ARGS ((SztDlnkNASTport *param));
EXTERN S16 szPrnt_ValueInitUEMsg_IEsCls ARGS ((Szt_ValueInitUEMsg_IEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_InitUEMsg_IEs ARGS ((SztProtIE_Field_InitUEMsg_IEs *param));
EXTERN S16 szPrntProtIE_Cont_InitUEMsg_IEs ARGS ((SztProtIE_Cont_InitUEMsg_IEs *param));
EXTERN S16 szPrntInitUEMsg ARGS ((SztInitUEMsg *param));
EXTERN S16 szPrnt_ValueUlnkNASTport_IEsCls ARGS ((Szt_ValueUlnkNASTport_IEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_UlnkNASTport_IEs ARGS ((SztProtIE_Field_UlnkNASTport_IEs *param));
EXTERN S16 szPrntProtIE_Cont_UlnkNASTport_IEs ARGS ((SztProtIE_Cont_UlnkNASTport_IEs *param));
EXTERN S16 szPrntUlnkNASTport ARGS ((SztUlnkNASTport *param));
EXTERN S16 szPrnt_ValueNASNonDlvryInd_IEsCls ARGS ((Szt_ValueNASNonDlvryInd_IEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_NASNonDlvryInd_IEs ARGS ((SztProtIE_Field_NASNonDlvryInd_IEs *param));
EXTERN S16 szPrntProtIE_Cont_NASNonDlvryInd_IEs ARGS ((SztProtIE_Cont_NASNonDlvryInd_IEs *param));
EXTERN S16 szPrntNASNonDlvryInd ARGS ((SztNASNonDlvryInd *param));
EXTERN S16 szPrnt_ValueUE_assocLogS1_ConItemResCls ARGS ((Szt_ValueUE_assocLogS1_ConItemResCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_UE_assocLogS1_ConItemRes ARGS ((SztProtIE_Field_UE_assocLogS1_ConItemRes *param));
EXTERN S16 szPrntUE_assocLogS1_ConLstRes ARGS ((SztUE_assocLogS1_ConLstRes *param));
EXTERN S16 szPrntResetTyp ARGS ((SztResetTyp *param));
EXTERN S16 szPrnt_ValueResetIEsCls ARGS ((Szt_ValueResetIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_ResetIEs ARGS ((SztProtIE_Field_ResetIEs *param));
EXTERN S16 szPrntProtIE_Cont_ResetIEs ARGS ((SztProtIE_Cont_ResetIEs *param));
EXTERN S16 szPrntReset ARGS ((SztReset *param));
EXTERN S16 szPrnt_ValueUE_assocLogS1_ConItemResAckCls ARGS ((Szt_ValueUE_assocLogS1_ConItemResAckCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_UE_assocLogS1_ConItemResAck ARGS ((SztProtIE_Field_UE_assocLogS1_ConItemResAck *param));
EXTERN S16 szPrntUE_assocLogS1_ConLstResAck ARGS ((SztUE_assocLogS1_ConLstResAck *param));
EXTERN S16 szPrnt_ValueResetAckgIEsCls ARGS ((Szt_ValueResetAckgIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_ResetAckgIEs ARGS ((SztProtIE_Field_ResetAckgIEs *param));
EXTERN S16 szPrntProtIE_Cont_ResetAckgIEs ARGS ((SztProtIE_Cont_ResetAckgIEs *param));
EXTERN S16 szPrntResetAckg ARGS ((SztResetAckg *param));
EXTERN S16 szPrnt_ValueErrIndIEsCls ARGS ((Szt_ValueErrIndIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_ErrIndIEs ARGS ((SztProtIE_Field_ErrIndIEs *param));
EXTERN S16 szPrntProtIE_Cont_ErrIndIEs ARGS ((SztProtIE_Cont_ErrIndIEs *param));
EXTERN S16 szPrntErrInd ARGS ((SztErrInd *param));
EXTERN S16 szPrnt_ValueS1SetupRqstIEsCls ARGS ((Szt_ValueS1SetupRqstIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_S1SetupRqstIEs ARGS ((SztProtIE_Field_S1SetupRqstIEs *param));
EXTERN S16 szPrntProtIE_Cont_S1SetupRqstIEs ARGS ((SztProtIE_Cont_S1SetupRqstIEs *param));
EXTERN S16 szPrntS1SetupRqst ARGS ((SztS1SetupRqst *param));
EXTERN S16 szPrnt_ValueS1SetupRespIEsCls ARGS ((Szt_ValueS1SetupRespIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_S1SetupRespIEs ARGS ((SztProtIE_Field_S1SetupRespIEs *param));
EXTERN S16 szPrntProtIE_Cont_S1SetupRespIEs ARGS ((SztProtIE_Cont_S1SetupRespIEs *param));
EXTERN S16 szPrntS1SetupResp ARGS ((SztS1SetupResp *param));
EXTERN S16 szPrnt_ValueS1SetupFailIEsCls ARGS ((Szt_ValueS1SetupFailIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_S1SetupFailIEs ARGS ((SztProtIE_Field_S1SetupFailIEs *param));
EXTERN S16 szPrntProtIE_Cont_S1SetupFailIEs ARGS ((SztProtIE_Cont_S1SetupFailIEs *param));
EXTERN S16 szPrntS1SetupFail ARGS ((SztS1SetupFail *param));
EXTERN S16 szPrnt_ValueENBConfigUpdIEsCls ARGS ((Szt_ValueENBConfigUpdIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_ENBConfigUpdIEs ARGS ((SztProtIE_Field_ENBConfigUpdIEs *param));
EXTERN S16 szPrntProtIE_Cont_ENBConfigUpdIEs ARGS ((SztProtIE_Cont_ENBConfigUpdIEs *param));
EXTERN S16 szPrntENBConfigUpd ARGS ((SztENBConfigUpd *param));
EXTERN S16 szPrnt_ValueENBConfigUpdAckgIEsCls ARGS ((Szt_ValueENBConfigUpdAckgIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_ENBConfigUpdAckgIEs ARGS ((SztProtIE_Field_ENBConfigUpdAckgIEs *param));
EXTERN S16 szPrntProtIE_Cont_ENBConfigUpdAckgIEs ARGS ((SztProtIE_Cont_ENBConfigUpdAckgIEs *param));
EXTERN S16 szPrntENBConfigUpdAckg ARGS ((SztENBConfigUpdAckg *param));
EXTERN S16 szPrnt_ValueENBConfigUpdFailIEsCls ARGS ((Szt_ValueENBConfigUpdFailIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_ENBConfigUpdFailIEs ARGS ((SztProtIE_Field_ENBConfigUpdFailIEs *param));
EXTERN S16 szPrntProtIE_Cont_ENBConfigUpdFailIEs ARGS ((SztProtIE_Cont_ENBConfigUpdFailIEs *param));
EXTERN S16 szPrntENBConfigUpdFail ARGS ((SztENBConfigUpdFail *param));
EXTERN S16 szPrnt_ValueMMEConfigUpdIEsCls ARGS ((Szt_ValueMMEConfigUpdIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_MMEConfigUpdIEs ARGS ((SztProtIE_Field_MMEConfigUpdIEs *param));
EXTERN S16 szPrntProtIE_Cont_MMEConfigUpdIEs ARGS ((SztProtIE_Cont_MMEConfigUpdIEs *param));
EXTERN S16 szPrntMMEConfigUpd ARGS ((SztMMEConfigUpd *param));
EXTERN S16 szPrnt_ValueMMEConfigUpdAckgIEsCls ARGS ((Szt_ValueMMEConfigUpdAckgIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_MMEConfigUpdAckgIEs ARGS ((SztProtIE_Field_MMEConfigUpdAckgIEs *param));
EXTERN S16 szPrntProtIE_Cont_MMEConfigUpdAckgIEs ARGS ((SztProtIE_Cont_MMEConfigUpdAckgIEs *param));
EXTERN S16 szPrntMMEConfigUpdAckg ARGS ((SztMMEConfigUpdAckg *param));
EXTERN S16 szPrnt_ValueMMEConfigUpdFailIEsCls ARGS ((Szt_ValueMMEConfigUpdFailIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_MMEConfigUpdFailIEs ARGS ((SztProtIE_Field_MMEConfigUpdFailIEs *param));
EXTERN S16 szPrntProtIE_Cont_MMEConfigUpdFailIEs ARGS ((SztProtIE_Cont_MMEConfigUpdFailIEs *param));
EXTERN S16 szPrntMMEConfigUpdFail ARGS ((SztMMEConfigUpdFail *param));
EXTERN S16 szPrnt_ValueDlnkS1cdma2000tunnelingIEsCls ARGS ((Szt_ValueDlnkS1cdma2000tunnelingIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_DlnkS1cdma2000tunnelingIEs ARGS ((SztProtIE_Field_DlnkS1cdma2000tunnelingIEs *param));
EXTERN S16 szPrntProtIE_Cont_DlnkS1cdma2000tunnelingIEs ARGS ((SztProtIE_Cont_DlnkS1cdma2000tunnelingIEs *param));
EXTERN S16 szPrntDlnkS1cdma2000tunneling ARGS ((SztDlnkS1cdma2000tunneling *param));
EXTERN S16 szPrnt_ValueUlnkS1cdma2000tunnelingIEsCls ARGS ((Szt_ValueUlnkS1cdma2000tunnelingIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_UlnkS1cdma2000tunnelingIEs ARGS ((SztProtIE_Field_UlnkS1cdma2000tunnelingIEs *param));
EXTERN S16 szPrntProtIE_Cont_UlnkS1cdma2000tunnelingIEs ARGS ((SztProtIE_Cont_UlnkS1cdma2000tunnelingIEs *param));
EXTERN S16 szPrntUlnkS1cdma2000tunneling ARGS ((SztUlnkS1cdma2000tunneling *param));
EXTERN S16 szPrnt_ValueUECapbltyInfoIndIEsCls ARGS ((Szt_ValueUECapbltyInfoIndIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_UECapbltyInfoIndIEs ARGS ((SztProtIE_Field_UECapbltyInfoIndIEs *param));
EXTERN S16 szPrntProtIE_Cont_UECapbltyInfoIndIEs ARGS ((SztProtIE_Cont_UECapbltyInfoIndIEs *param));
EXTERN S16 szPrntUECapbltyInfoInd ARGS ((SztUECapbltyInfoInd *param));
EXTERN S16 szPrnt_ValueENBStatusTfrIEsCls ARGS ((Szt_ValueENBStatusTfrIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_ENBStatusTfrIEs ARGS ((SztProtIE_Field_ENBStatusTfrIEs *param));
EXTERN S16 szPrntProtIE_Cont_ENBStatusTfrIEs ARGS ((SztProtIE_Cont_ENBStatusTfrIEs *param));
EXTERN S16 szPrntENBStatusTfr ARGS ((SztENBStatusTfr *param));
EXTERN S16 szPrnt_ValueMMEStatusTfrIEsCls ARGS ((Szt_ValueMMEStatusTfrIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_MMEStatusTfrIEs ARGS ((SztProtIE_Field_MMEStatusTfrIEs *param));
EXTERN S16 szPrntProtIE_Cont_MMEStatusTfrIEs ARGS ((SztProtIE_Cont_MMEStatusTfrIEs *param));
EXTERN S16 szPrntMMEStatusTfr ARGS ((SztMMEStatusTfr *param));
EXTERN S16 szPrnt_ValueTraceStartIEsCls ARGS ((Szt_ValueTraceStartIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_TraceStartIEs ARGS ((SztProtIE_Field_TraceStartIEs *param));
EXTERN S16 szPrntProtIE_Cont_TraceStartIEs ARGS ((SztProtIE_Cont_TraceStartIEs *param));
EXTERN S16 szPrntTraceStart ARGS ((SztTraceStart *param));
EXTERN S16 szPrnt_ValueTraceFailIndIEsCls ARGS ((Szt_ValueTraceFailIndIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_TraceFailIndIEs ARGS ((SztProtIE_Field_TraceFailIndIEs *param));
EXTERN S16 szPrntProtIE_Cont_TraceFailIndIEs ARGS ((SztProtIE_Cont_TraceFailIndIEs *param));
EXTERN S16 szPrntTraceFailInd ARGS ((SztTraceFailInd *param));
EXTERN S16 szPrnt_ValueDeactvTraceIEsCls ARGS ((Szt_ValueDeactvTraceIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_DeactvTraceIEs ARGS ((SztProtIE_Field_DeactvTraceIEs *param));
EXTERN S16 szPrntProtIE_Cont_DeactvTraceIEs ARGS ((SztProtIE_Cont_DeactvTraceIEs *param));
EXTERN S16 szPrntDeactvTrace ARGS ((SztDeactvTrace *param));
EXTERN S16 szPrnt_ValueCellTrafficTraceIEsCls ARGS ((Szt_ValueCellTrafficTraceIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_CellTrafficTraceIEs ARGS ((SztProtIE_Field_CellTrafficTraceIEs *param));
EXTERN S16 szPrntProtIE_Cont_CellTrafficTraceIEs ARGS ((SztProtIE_Cont_CellTrafficTraceIEs *param));
EXTERN S16 szPrntCellTrafficTrace ARGS ((SztCellTrafficTrace *param));
EXTERN S16 szPrnt_ValueLocRprtngCntrlIEsCls ARGS ((Szt_ValueLocRprtngCntrlIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_LocRprtngCntrlIEs ARGS ((SztProtIE_Field_LocRprtngCntrlIEs *param));
EXTERN S16 szPrntProtIE_Cont_LocRprtngCntrlIEs ARGS ((SztProtIE_Cont_LocRprtngCntrlIEs *param));
EXTERN S16 szPrntLocRprtngCntrl ARGS ((SztLocRprtngCntrl *param));
EXTERN S16 szPrnt_ValueLocRprtngFailIndIEsCls ARGS ((Szt_ValueLocRprtngFailIndIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_LocRprtngFailIndIEs ARGS ((SztProtIE_Field_LocRprtngFailIndIEs *param));
EXTERN S16 szPrntProtIE_Cont_LocRprtngFailIndIEs ARGS ((SztProtIE_Cont_LocRprtngFailIndIEs *param));
EXTERN S16 szPrntLocRprtngFailInd ARGS ((SztLocRprtngFailInd *param));
EXTERN S16 szPrnt_ValueLocReportIEsCls ARGS ((Szt_ValueLocReportIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_LocReportIEs ARGS ((SztProtIE_Field_LocReportIEs *param));
EXTERN S16 szPrntProtIE_Cont_LocReportIEs ARGS ((SztProtIE_Cont_LocReportIEs *param));
EXTERN S16 szPrntLocReport ARGS ((SztLocReport *param));
EXTERN S16 szPrnt_ValueOverloadStartIEsCls ARGS ((Szt_ValueOverloadStartIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_OverloadStartIEs ARGS ((SztProtIE_Field_OverloadStartIEs *param));
EXTERN S16 szPrntProtIE_Cont_OverloadStartIEs ARGS ((SztProtIE_Cont_OverloadStartIEs *param));
EXTERN S16 szPrntOverloadStart ARGS ((SztOverloadStart *param));
EXTERN S16 szPrnt_ValueOverloadStopIEsCls ARGS ((Szt_ValueOverloadStopIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_OverloadStopIEs ARGS ((SztProtIE_Field_OverloadStopIEs *param));
EXTERN S16 szPrntProtIE_Cont_OverloadStopIEs ARGS ((SztProtIE_Cont_OverloadStopIEs *param));
EXTERN S16 szPrntOverloadStop ARGS ((SztOverloadStop *param));
EXTERN S16 szPrnt_ValueWriteReplaceWarningRqstIEsCls ARGS ((Szt_ValueWriteReplaceWarningRqstIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_WriteReplaceWarningRqstIEs ARGS ((SztProtIE_Field_WriteReplaceWarningRqstIEs *param));
EXTERN S16 szPrntProtIE_Cont_WriteReplaceWarningRqstIEs ARGS ((SztProtIE_Cont_WriteReplaceWarningRqstIEs *param));
EXTERN S16 szPrntWriteReplaceWarningRqst ARGS ((SztWriteReplaceWarningRqst *param));
EXTERN S16 szPrnt_ValueWriteReplaceWarningRespIEsCls ARGS ((Szt_ValueWriteReplaceWarningRespIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_WriteReplaceWarningRespIEs ARGS ((SztProtIE_Field_WriteReplaceWarningRespIEs *param));
EXTERN S16 szPrntProtIE_Cont_WriteReplaceWarningRespIEs ARGS ((SztProtIE_Cont_WriteReplaceWarningRespIEs *param));
EXTERN S16 szPrntWriteReplaceWarningResp ARGS ((SztWriteReplaceWarningResp *param));
EXTERN S16 szPrntInter_SystemInformTfrTyp ARGS ((SztInter_SystemInformTfrTyp *param));
EXTERN S16 szPrnt_ValueENBDirectInformTfrIEsCls ARGS ((Szt_ValueENBDirectInformTfrIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_ENBDirectInformTfrIEs ARGS ((SztProtIE_Field_ENBDirectInformTfrIEs *param));
EXTERN S16 szPrntProtIE_Cont_ENBDirectInformTfrIEs ARGS ((SztProtIE_Cont_ENBDirectInformTfrIEs *param));
EXTERN S16 szPrntENBDirectInformTfr ARGS ((SztENBDirectInformTfr *param));
EXTERN S16 szPrnt_ValueMMEDirectInformTfrIEsCls ARGS ((Szt_ValueMMEDirectInformTfrIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_MMEDirectInformTfrIEs ARGS ((SztProtIE_Field_MMEDirectInformTfrIEs *param));
EXTERN S16 szPrntProtIE_Cont_MMEDirectInformTfrIEs ARGS ((SztProtIE_Cont_MMEDirectInformTfrIEs *param));
EXTERN S16 szPrntMMEDirectInformTfr ARGS ((SztMMEDirectInformTfr *param));
EXTERN S16 szPrnt_ValueENBConfigTfrIEsCls ARGS ((Szt_ValueENBConfigTfrIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_ENBConfigTfrIEs ARGS ((SztProtIE_Field_ENBConfigTfrIEs *param));
EXTERN S16 szPrntProtIE_Cont_ENBConfigTfrIEs ARGS ((SztProtIE_Cont_ENBConfigTfrIEs *param));
EXTERN S16 szPrntENBConfigTfr ARGS ((SztENBConfigTfr *param));
EXTERN S16 szPrnt_ValueMMEConfigTfrIEsCls ARGS ((Szt_ValueMMEConfigTfrIEsCls *param, U32 val));
EXTERN S16 szPrntProtIE_Field_MMEConfigTfrIEs ARGS ((SztProtIE_Field_MMEConfigTfrIEs *param));
EXTERN S16 szPrntProtIE_Cont_MMEConfigTfrIEs ARGS ((SztProtIE_Cont_MMEConfigTfrIEs *param));
EXTERN S16 szPrntMMEConfigTfr ARGS ((SztMMEConfigTfr *param));
EXTERN S16 szPrnt_ValuePrivMsgIEsCls ARGS ((Szt_ValuePrivMsgIEsCls *param, U32 val));
EXTERN S16 szPrntPrivIE_Field_PrivMsgIEs ARGS ((SztPrivIE_Field_PrivMsgIEs *param));
EXTERN S16 szPrntPrivIE_Cont_PrivMsgIEs ARGS ((SztPrivIE_Cont_PrivMsgIEs *param));
EXTERN S16 szPrntProtIE_Field_TAIItemIEs ARGS((SztProtIE_Field_TAIItemIEs *param));
EXTERN S16 szPrntPrivMsg ARGS ((SztPrivMsg *param));
EXTERN S16 szPrnt_InitiatingMsgCls ARGS ((Szt_InitiatingMsgCls *param, U32 val));
EXTERN S16 szPrntInitiatingMsg ARGS ((SztInitiatingMsg *param));
EXTERN S16 szPrnt_SuccessfulOutcomeCls ARGS ((Szt_SuccessfulOutcomeCls *param, U32 val));
EXTERN S16 szPrntSuccessfulOutcome ARGS ((SztSuccessfulOutcome *param));
EXTERN S16 szPrnt_UnsuccessfulOutcomeCls ARGS ((Szt_UnsuccessfulOutcomeCls *param, U32 val));
EXTERN S16 szPrntUnsuccessfulOutcome ARGS((SztUnsuccessfulOutcome *param));
EXTERN S16 szPrntS1AP_PDU ARGS((SztS1AP_PDU *param));


#ifdef __cplusplus
}
#endif /* __cplusplus */ 

#endif /* __SZ_ENCDECX__ */

/**********************************************************************

         End of file:     sz_encdec.x@@/main/1 - Mon Jan 10 22:17:13 2011

**********************************************************************/

/**********************************************************************
        Revision History:

**********************************************************************/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     pkaX   1. S1AP encode/decode library Initial Release.
/main/4   sz004.301   va    1. Updated for Transparent Container Enc/Dec
*********************************************************************91*/

