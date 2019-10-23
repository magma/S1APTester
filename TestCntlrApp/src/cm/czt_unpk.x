/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_smm_init.c

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/
#ifndef __CZTUNPKX__
#define __CZTUNPKX__ 


#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

EXTERN S16 cmUnpkCztPrivIE_ID ARGS ((CztPrivIE_ID *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnABSInformFDD_ExtIEsCls ARGS ((Czt_ExtnABSInformFDD_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_ABSInformFDD_ExtIEs ARGS ((CztProtExtnField_ABSInformFDD_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_ABSInformFDD_ExtIEs ARGS ((CztProtExtnCont_ABSInformFDD_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztABSInformFDD ARGS ((CztABSInformFDD *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnABSInformTDD_ExtIEsCls ARGS ((Czt_ExtnABSInformTDD_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_ABSInformTDD_ExtIEs ARGS ((CztProtExtnField_ABSInformTDD_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_ABSInformTDD_ExtIEs ARGS ((CztProtExtnCont_ABSInformTDD_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztABSInformTDD ARGS ((CztABSInformTDD *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztABSInform ARGS ((CztABSInform *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnUsableABSInformFDD_ExtIEsCls ARGS ((Czt_ExtnUsableABSInformFDD_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_UsableABSInformFDD_ExtIEs ARGS ((CztProtExtnField_UsableABSInformFDD_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_UsableABSInformFDD_ExtIEs ARGS ((CztProtExtnCont_UsableABSInformFDD_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztUsableABSInformFDD ARGS ((CztUsableABSInformFDD *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnUsableABSInformTDD_ExtIEsCls ARGS ((Czt_ExtnUsableABSInformTDD_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_UsableABSInformTDD_ExtIEs ARGS ((CztProtExtnField_UsableABSInformTDD_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_UsableABSInformTDD_ExtIEs ARGS ((CztProtExtnCont_UsableABSInformTDD_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztUsableABSInformTDD ARGS ((CztUsableABSInformTDD *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztUsableABSInform ARGS ((CztUsableABSInform *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnABS_Status_ExtIEsCls ARGS ((Czt_ExtnABS_Status_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_ABS_Status_ExtIEs ARGS ((CztProtExtnField_ABS_Status_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_ABS_Status_ExtIEs ARGS ((CztProtExtnCont_ABS_Status_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztABS_Status ARGS ((CztABS_Status *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnAdditionalSpecialSubframe_Info_ExtIEsCls ARGS ((Czt_ExtnAdditionalSpecialSubframe_Info_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_AdditionalSpecialSubframe_Info_ExtIEs ARGS ((CztProtExtnField_AdditionalSpecialSubframe_Info_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEs ARGS ((CztProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztAdditionalSpecialSubframe_Info ARGS ((CztAdditionalSpecialSubframe_Info *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnAS_SecurInform_ExtIEsCls ARGS ((Czt_ExtnAS_SecurInform_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_AS_SecurInform_ExtIEs ARGS ((CztProtExtnField_AS_SecurInform_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_AS_SecurInform_ExtIEs ARGS ((CztProtExtnCont_AS_SecurInform_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztAS_SecurInform ARGS ((CztAS_SecurInform *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnAllocnAndRetentionPriority_ExtIEsCls ARGS ((Czt_ExtnAllocnAndRetentionPriority_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_AllocnAndRetentionPriority_ExtIEs ARGS ((CztProtExtnField_AllocnAndRetentionPriority_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_AllocnAndRetentionPriority_ExtIEs ARGS ((CztProtExtnCont_AllocnAndRetentionPriority_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztAllocnAndRetentionPriority ARGS ((CztAllocnAndRetentionPriority *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnECGI_ExtIEsCls ARGS ((Czt_ExtnECGI_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_ECGI_ExtIEs ARGS ((CztProtExtnField_ECGI_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_ECGI_ExtIEs ARGS ((CztProtExtnCont_ECGI_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztECGI ARGS ((CztECGI *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztCellIdLstforMDT ARGS ((CztCellIdLstforMDT *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnCellBasedMDT_ExtIEsCls ARGS ((Czt_ExtnCellBasedMDT_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_CellBasedMDT_ExtIEs ARGS ((CztProtExtnField_CellBasedMDT_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_CellBasedMDT_ExtIEs ARGS ((CztProtExtnCont_CellBasedMDT_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztCellBasedMDT ARGS ((CztCellBasedMDT *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztTALstforMDT ARGS ((CztTALstforMDT *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnTABasedMDT_ExtIEsCls ARGS ((Czt_ExtnTABasedMDT_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_TABasedMDT_ExtIEs ARGS ((CztProtExtnField_TABasedMDT_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_TABasedMDT_ExtIEs ARGS ((CztProtExtnCont_TABasedMDT_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztTABasedMDT ARGS ((CztTABasedMDT *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnTAI_Item_ExtIEsCls ARGS ((Czt_ExtnTAI_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_TAI_Item_ExtIEs ARGS ((CztProtExtnField_TAI_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_TAI_Item_ExtIEs ARGS ((CztProtExtnCont_TAI_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztTAI_Item ARGS ((CztTAI_Item *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztTAILstforMDT ARGS ((CztTAILstforMDT *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnTAIBasedMDT_ExtIEsCls ARGS ((Czt_ExtnTAIBasedMDT_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_TAIBasedMDT_ExtIEs ARGS ((CztProtExtnField_TAIBasedMDT_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_TAIBasedMDT_ExtIEs ARGS ((CztProtExtnCont_TAIBasedMDT_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztTAIBasedMDT ARGS ((CztTAIBasedMDT *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztAreaScopeOfMDT ARGS ((CztAreaScopeOfMDT *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztBroadcastPLMNs_Item ARGS ((CztBroadcastPLMNs_Item *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztCause ARGS ((CztCause *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnCellTyp_ExtIEsCls ARGS ((Czt_ExtnCellTyp_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_CellTyp_ExtIEs ARGS ((CztProtExtnField_CellTyp_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_CellTyp_ExtIEs ARGS ((CztProtExtnCont_CellTyp_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztCellTyp ARGS ((CztCellTyp *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnCompositeAvailableCapacity_ExtIEsCls ARGS ((Czt_ExtnCompositeAvailableCapacity_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_CompositeAvailableCapacity_ExtIEs ARGS ((CztProtExtnField_CompositeAvailableCapacity_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_CompositeAvailableCapacity_ExtIEs ARGS ((CztProtExtnCont_CompositeAvailableCapacity_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztCompositeAvailableCapacity ARGS ((CztCompositeAvailableCapacity *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnCompositeAvailableCapacityGroup_ExtIEsCls ARGS ((Czt_ExtnCompositeAvailableCapacityGroup_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_CompositeAvailableCapacityGroup_ExtIEs ARGS ((CztProtExtnField_CompositeAvailableCapacityGroup_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_CompositeAvailableCapacityGroup_ExtIEs ARGS ((CztProtExtnCont_CompositeAvailableCapacityGroup_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztCompositeAvailableCapacityGroup ARGS ((CztCompositeAvailableCapacityGroup *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnCOUNTvalue_ExtIEsCls ARGS ((Czt_ExtnCOUNTvalue_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_COUNTvalue_ExtIEs ARGS ((CztProtExtnField_COUNTvalue_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_COUNTvalue_ExtIEs ARGS ((CztProtExtnCont_COUNTvalue_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztCOUNTvalue ARGS ((CztCOUNTvalue *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnCOUNTValueExtended_ExtIEsCls ARGS ((Czt_ExtnCOUNTValueExtended_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_COUNTValueExtended_ExtIEs ARGS ((CztProtExtnField_COUNTValueExtended_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_COUNTValueExtended_ExtIEs ARGS ((CztProtExtnCont_COUNTValueExtended_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztCOUNTValueExtended ARGS ((CztCOUNTValueExtended *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnCriticalityDiag_IE_Lst_ExtIEsCls ARGS ((Czt_ExtnCriticalityDiag_IE_Lst_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_CriticalityDiag_IE_Lst_ExtIEs ARGS ((CztProtExtnField_CriticalityDiag_IE_Lst_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_CriticalityDiag_IE_Lst_ExtIEs ARGS ((CztProtExtnCont_CriticalityDiag_IE_Lst_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztCriticalityDiag_IE_LstMember ARGS ((CztCriticalityDiag_IE_LstMember *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztCriticalityDiag_IE_Lst ARGS ((CztCriticalityDiag_IE_Lst *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnCriticalityDiag_ExtIEsCls ARGS ((Czt_ExtnCriticalityDiag_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_CriticalityDiag_ExtIEs ARGS ((CztProtExtnField_CriticalityDiag_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_CriticalityDiag_ExtIEs ARGS ((CztProtExtnCont_CriticalityDiag_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztCriticalityDiag ARGS ((CztCriticalityDiag *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnFDD_Info_ExtIEsCls ARGS ((Czt_ExtnFDD_Info_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_FDD_Info_ExtIEs ARGS ((CztProtExtnField_FDD_Info_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_FDD_Info_ExtIEs ARGS ((CztProtExtnCont_FDD_Info_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztFDD_Info ARGS ((CztFDD_Info *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnSpecialSubframe_Info_ExtIEsCls ARGS ((Czt_ExtnSpecialSubframe_Info_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_SpecialSubframe_Info_ExtIEs ARGS ((CztProtExtnField_SpecialSubframe_Info_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_SpecialSubframe_Info_ExtIEs ARGS ((CztProtExtnCont_SpecialSubframe_Info_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztSpecialSubframe_Info ARGS ((CztSpecialSubframe_Info *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnTDD_Info_ExtIEsCls ARGS ((Czt_ExtnTDD_Info_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_TDD_Info_ExtIEs ARGS ((CztProtExtnField_TDD_Info_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_TDD_Info_ExtIEs ARGS ((CztProtExtnCont_TDD_Info_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztTDD_Info ARGS ((CztTDD_Info *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztEUTRA_Mode_Info ARGS ((CztEUTRA_Mode_Info *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztENB_ID ARGS ((CztENB_ID *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztEPLMNs ARGS ((CztEPLMNs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnGBR_QosInform_ExtIEsCls ARGS ((Czt_ExtnGBR_QosInform_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_GBR_QosInform_ExtIEs ARGS ((CztProtExtnField_GBR_QosInform_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_GBR_QosInform_ExtIEs ARGS ((CztProtExtnCont_GBR_QosInform_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztGBR_QosInform ARGS ((CztGBR_QosInform *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnE_RAB_Lvl_QoS_Params_ExtIEsCls ARGS ((Czt_ExtnE_RAB_Lvl_QoS_Params_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEs ARGS ((CztProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEs ARGS ((CztProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztE_RAB_Lvl_QoS_Params ARGS ((CztE_RAB_Lvl_QoS_Params *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnE_RAB_Item_ExtIEsCls ARGS ((Czt_ExtnE_RAB_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_E_RAB_Item_ExtIEs ARGS ((CztProtExtnField_E_RAB_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_E_RAB_Item_ExtIEs ARGS ((CztProtExtnCont_E_RAB_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztE_RAB_Item ARGS ((CztE_RAB_Item *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueE_RAB_ItemIEsCls ARGS ((Czt_ValueE_RAB_ItemIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_E_RAB_ItemIEs ARGS ((CztProtIE_Field_E_RAB_ItemIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztE_RAB_Lst ARGS ((CztE_RAB_Lst *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztForbiddenTACs ARGS ((CztForbiddenTACs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnForbiddenTAs_Item_ExtIEsCls ARGS ((Czt_ExtnForbiddenTAs_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_ForbiddenTAs_Item_ExtIEs ARGS ((CztProtExtnField_ForbiddenTAs_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_ForbiddenTAs_Item_ExtIEs ARGS ((CztProtExtnCont_ForbiddenTAs_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztForbiddenTAs_Item ARGS ((CztForbiddenTAs_Item *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztForbiddenTAs ARGS ((CztForbiddenTAs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztForbiddenLACs ARGS ((CztForbiddenLACs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnForbiddenLAs_Item_ExtIEsCls ARGS ((Czt_ExtnForbiddenLAs_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_ForbiddenLAs_Item_ExtIEs ARGS ((CztProtExtnField_ForbiddenLAs_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_ForbiddenLAs_Item_ExtIEs ARGS ((CztProtExtnCont_ForbiddenLAs_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztForbiddenLAs_Item ARGS ((CztForbiddenLAs_Item *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztForbiddenLAs ARGS ((CztForbiddenLAs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnGlobalENB_ID_ExtIEsCls ARGS ((Czt_ExtnGlobalENB_ID_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_GlobalENB_ID_ExtIEs ARGS ((CztProtExtnField_GlobalENB_ID_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_GlobalENB_ID_ExtIEs ARGS ((CztProtExtnCont_GlobalENB_ID_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztGlobalENB_ID ARGS ((CztGlobalENB_ID *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnGTPtunnelEndpoint_ExtIEsCls ARGS ((Czt_ExtnGTPtunnelEndpoint_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_GTPtunnelEndpoint_ExtIEs ARGS ((CztProtExtnField_GTPtunnelEndpoint_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_GTPtunnelEndpoint_ExtIEs ARGS ((CztProtExtnCont_GTPtunnelEndpoint_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztGTPtunnelEndpoint ARGS ((CztGTPtunnelEndpoint *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnGU_Group_ID_ExtIEsCls ARGS ((Czt_ExtnGU_Group_ID_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_GU_Group_ID_ExtIEs ARGS ((CztProtExtnField_GU_Group_ID_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_GU_Group_ID_ExtIEs ARGS ((CztProtExtnCont_GU_Group_ID_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztGU_Group_ID ARGS ((CztGU_Group_ID *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztGUGroupIDLst ARGS ((CztGUGroupIDLst *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnGUMMEI_ExtIEsCls ARGS ((Czt_ExtnGUMMEI_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_GUMMEI_ExtIEs ARGS ((CztProtExtnField_GUMMEI_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_GUMMEI_ExtIEs ARGS ((CztProtExtnCont_GUMMEI_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztGUMMEI ARGS ((CztGUMMEI *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnHovrRestrnLst_ExtIEsCls ARGS ((Czt_ExtnHovrRestrnLst_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_HovrRestrnLst_ExtIEs ARGS ((CztProtExtnField_HovrRestrnLst_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_HovrRestrnLst_ExtIEs ARGS ((CztProtExtnCont_HovrRestrnLst_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztHovrRestrnLst ARGS ((CztHovrRestrnLst *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnHWLoadIndicator_ExtIEsCls ARGS ((Czt_ExtnHWLoadIndicator_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_HWLoadIndicator_ExtIEs ARGS ((CztProtExtnField_HWLoadIndicator_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_HWLoadIndicator_ExtIEs ARGS ((CztProtExtnCont_HWLoadIndicator_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztHWLoadIndicator ARGS ((CztHWLoadIndicator *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls ARGS ((Czt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs ARGS ((CztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs ARGS ((CztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztLastVisitedEUTRANCellInform ARGS ((CztLastVisitedEUTRANCellInform *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztLastVisitedGERANCellInform ARGS ((CztLastVisitedGERANCellInform *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztLastVisitedCell_Item ARGS ((CztLastVisitedCell_Item *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnLocRprtngInform_ExtIEsCls ARGS ((Czt_ExtnLocRprtngInform_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_LocRprtngInform_ExtIEs ARGS ((CztProtExtnField_LocRprtngInform_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_LocRprtngInform_ExtIEs ARGS ((CztProtExtnCont_LocRprtngInform_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztLocRprtngInform ARGS ((CztLocRprtngInform *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnM3Config_ExtIEsCls ARGS ((Czt_ExtnM3Config_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_M3Config_ExtIEs ARGS ((CztProtExtnField_M3Config_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_M3Config_ExtIEs ARGS ((CztProtExtnCont_M3Config_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztM3Config ARGS ((CztM3Config *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnM4Config_ExtIEsCls ARGS ((Czt_ExtnM4Config_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_M4Config_ExtIEs ARGS ((CztProtExtnField_M4Config_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_M4Config_ExtIEs ARGS ((CztProtExtnCont_M4Config_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztM4Config ARGS ((CztM4Config *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnM5Config_ExtIEsCls ARGS ((Czt_ExtnM5Config_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_M5Config_ExtIEs ARGS ((CztProtExtnField_M5Config_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_M5Config_ExtIEs ARGS ((CztProtExtnCont_M5Config_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztM5Config ARGS ((CztM5Config *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztMeasurementThresholdA2 ARGS ((CztMeasurementThresholdA2 *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnM1ThresholdEventA2_ExtIEsCls ARGS ((Czt_ExtnM1ThresholdEventA2_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_M1ThresholdEventA2_ExtIEs ARGS ((CztProtExtnField_M1ThresholdEventA2_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_M1ThresholdEventA2_ExtIEs ARGS ((CztProtExtnCont_M1ThresholdEventA2_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztM1ThresholdEventA2 ARGS ((CztM1ThresholdEventA2 *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnM1PeriodicRprtng_ExtIEsCls ARGS ((Czt_ExtnM1PeriodicRprtng_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_M1PeriodicRprtng_ExtIEs ARGS ((CztProtExtnField_M1PeriodicRprtng_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_M1PeriodicRprtng_ExtIEs ARGS ((CztProtExtnCont_M1PeriodicRprtng_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztM1PeriodicRprtng ARGS ((CztM1PeriodicRprtng *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztMDTPLMNLst ARGS ((CztMDTPLMNLst *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnMDT_Config_ExtIEsCls ARGS ((Czt_ExtnMDT_Config_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_MDT_Config_ExtIEs ARGS ((CztProtExtnField_MDT_Config_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_MDT_Config_ExtIEs ARGS ((CztProtExtnCont_MDT_Config_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztMDT_Config ARGS ((CztMDT_Config *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztMBMS_Service_Area_Identity_Lst ARGS ((CztMBMS_Service_Area_Identity_Lst *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztSubframeAllocn ARGS ((CztSubframeAllocn *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnMBSFN_Subframe_Info_ExtIEsCls ARGS ((Czt_ExtnMBSFN_Subframe_Info_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_MBSFN_Subframe_Info_ExtIEs ARGS ((CztProtExtnField_MBSFN_Subframe_Info_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_MBSFN_Subframe_Info_ExtIEs ARGS ((CztProtExtnCont_MBSFN_Subframe_Info_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztMBSFN_Subframe_Info ARGS ((CztMBSFN_Subframe_Info *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztMBSFN_Subframe_Infolist ARGS ((CztMBSFN_Subframe_Infolist *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztMobilityParamsModificationRange ARGS ((CztMobilityParamsModificationRange *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztMobilityParamsInform ARGS ((CztMobilityParamsInform *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnBandInfo_ExtIEsCls ARGS ((Czt_ExtnBandInfo_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_BandInfo_ExtIEs ARGS ((CztProtExtnField_BandInfo_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_BandInfo_ExtIEs ARGS ((CztProtExtnCont_BandInfo_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztBandInfo ARGS ((CztBandInfo *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztMultibandInfoLst ARGS ((CztMultibandInfoLst *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnNeighbour_Inform_ExtIEsCls ARGS ((Czt_ExtnNeighbour_Inform_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_Neighbour_Inform_ExtIEs ARGS ((CztProtExtnField_Neighbour_Inform_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_Neighbour_Inform_ExtIEs ARGS ((CztProtExtnCont_Neighbour_Inform_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztNeighbour_InformMember ARGS ((CztNeighbour_InformMember *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztNeighbour_Inform ARGS ((CztNeighbour_Inform *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnPRACH_Config_ExtIEsCls ARGS ((Czt_ExtnPRACH_Config_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_PRACH_Config_ExtIEs ARGS ((CztProtExtnField_PRACH_Config_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_PRACH_Config_ExtIEs ARGS ((CztProtExtnCont_PRACH_Config_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztPRACH_Config ARGS ((CztPRACH_Config *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnRadioResStatus_ExtIEsCls ARGS ((Czt_ExtnRadioResStatus_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_RadioResStatus_ExtIEs ARGS ((CztProtExtnField_RadioResStatus_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_RadioResStatus_ExtIEs ARGS ((CztProtExtnCont_RadioResStatus_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztRadioResStatus ARGS ((CztRadioResStatus *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnRelativeNarrowbandTxPower_ExtIEsCls ARGS ((Czt_ExtnRelativeNarrowbandTxPower_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_RelativeNarrowbandTxPower_ExtIEs ARGS ((CztProtExtnField_RelativeNarrowbandTxPower_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_RelativeNarrowbandTxPower_ExtIEs ARGS ((CztProtExtnCont_RelativeNarrowbandTxPower_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztRelativeNarrowbandTxPower ARGS ((CztRelativeNarrowbandTxPower *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnS1TNLLoadIndicator_ExtIEsCls ARGS ((Czt_ExtnS1TNLLoadIndicator_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_S1TNLLoadIndicator_ExtIEs ARGS ((CztProtExtnField_S1TNLLoadIndicator_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_S1TNLLoadIndicator_ExtIEs ARGS ((CztProtExtnCont_S1TNLLoadIndicator_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztS1TNLLoadIndicator ARGS ((CztS1TNLLoadIndicator *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnSrvdCell_Inform_ExtIEsCls ARGS ((Czt_ExtnSrvdCell_Inform_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_SrvdCell_Inform_ExtIEs ARGS ((CztProtExtnField_SrvdCell_Inform_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_SrvdCell_Inform_ExtIEs ARGS ((CztProtExtnCont_SrvdCell_Inform_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztSrvdCell_Inform ARGS ((CztSrvdCell_Inform *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnSrvdCell_ExtIEsCls ARGS ((Czt_ExtnSrvdCell_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_SrvdCell_ExtIEs ARGS ((CztProtExtnField_SrvdCell_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_SrvdCell_ExtIEs ARGS ((CztProtExtnCont_SrvdCell_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztSrvdCellsMember ARGS ((CztSrvdCellsMember *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztSrvdCells ARGS ((CztSrvdCells *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnTraceActvn_ExtIEsCls ARGS ((Czt_ExtnTraceActvn_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_TraceActvn_ExtIEs ARGS ((CztProtExtnField_TraceActvn_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_TraceActvn_ExtIEs ARGS ((CztProtExtnCont_TraceActvn_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztTraceActvn ARGS ((CztTraceActvn *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztUE_HistoryInform ARGS ((CztUE_HistoryInform *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnUEAgg_MaxBitrate_ExtIEsCls ARGS ((Czt_ExtnUEAgg_MaxBitrate_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_UEAgg_MaxBitrate_ExtIEs ARGS ((CztProtExtnField_UEAgg_MaxBitrate_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_UEAgg_MaxBitrate_ExtIEs ARGS ((CztProtExtnCont_UEAgg_MaxBitrate_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztUEAggMaxBitRate ARGS ((CztUEAggMaxBitRate *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnUESecurCapabilities_ExtIEsCls ARGS ((Czt_ExtnUESecurCapabilities_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_UESecurCapabilities_ExtIEs ARGS ((CztProtExtnField_UESecurCapabilities_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_UESecurCapabilities_ExtIEs ARGS ((CztProtExtnCont_UESecurCapabilities_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztUESecurCapabilities ARGS ((CztUESecurCapabilities *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztUL_InterferenceOverloadInd ARGS ((CztUL_InterferenceOverloadInd *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsCls ARGS ((Czt_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEs ARGS ((CztProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEs ARGS ((CztProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztUL_HighInterferenceIndInfo_Item ARGS ((CztUL_HighInterferenceIndInfo_Item *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztUL_HighInterferenceIndInfo ARGS ((CztUL_HighInterferenceIndInfo *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnE_RABs_ToBeSetup_ItemExtIEsCls ARGS ((Czt_ExtnE_RABs_ToBeSetup_ItemExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_E_RABs_ToBeSetup_ItemExtIEs ARGS ((CztProtExtnField_E_RABs_ToBeSetup_ItemExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_E_RABs_ToBeSetup_ItemExtIEs ARGS ((CztProtExtnCont_E_RABs_ToBeSetup_ItemExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztE_RABs_ToBeSetup_Item ARGS ((CztE_RABs_ToBeSetup_Item *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueE_RABs_ToBeSetup_ItemIEsCls ARGS ((Czt_ValueE_RABs_ToBeSetup_ItemIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_E_RABs_ToBeSetup_ItemIEs ARGS ((CztProtIE_Field_E_RABs_ToBeSetup_ItemIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztE_RABs_ToBeSetup_Lst ARGS ((CztE_RABs_ToBeSetup_Lst *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnUE_CntxtInform_ExtIEsCls ARGS ((Czt_ExtnUE_CntxtInform_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_UE_CntxtInform_ExtIEs ARGS ((CztProtExtnField_UE_CntxtInform_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_UE_CntxtInform_ExtIEs ARGS ((CztProtExtnCont_UE_CntxtInform_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztUE_CntxtInform ARGS ((CztUE_CntxtInform *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueHovrRqst_IEsCls ARGS ((Czt_ValueHovrRqst_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_HovrRqst_IEs ARGS ((CztProtIE_Field_HovrRqst_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Cont_HovrRqst_IEs ARGS ((CztProtIE_Cont_HovrRqst_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztHovrRqst ARGS ((CztHovrRqst *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnE_RABs_Admtd_Item_ExtIEsCls ARGS ((Czt_ExtnE_RABs_Admtd_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_E_RABs_Admtd_Item_ExtIEs ARGS ((CztProtExtnField_E_RABs_Admtd_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_E_RABs_Admtd_Item_ExtIEs ARGS ((CztProtExtnCont_E_RABs_Admtd_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztE_RABs_Admtd_Item ARGS ((CztE_RABs_Admtd_Item *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueE_RABs_Admtd_ItemIEsCls ARGS ((Czt_ValueE_RABs_Admtd_ItemIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_E_RABs_Admtd_ItemIEs ARGS ((CztProtIE_Field_E_RABs_Admtd_ItemIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztE_RABs_Admtd_Lst ARGS ((CztE_RABs_Admtd_Lst *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueHovrRqstAckg_IEsCls ARGS ((Czt_ValueHovrRqstAckg_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_HovrRqstAckg_IEs ARGS ((CztProtIE_Field_HovrRqstAckg_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Cont_HovrRqstAckg_IEs ARGS ((CztProtIE_Cont_HovrRqstAckg_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztHovrRqstAckg ARGS ((CztHovrRqstAckg *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueHovrPrepFail_IEsCls ARGS ((Czt_ValueHovrPrepFail_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_HovrPrepFail_IEs ARGS ((CztProtIE_Field_HovrPrepFail_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Cont_HovrPrepFail_IEs ARGS ((CztProtIE_Cont_HovrPrepFail_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztHovrPrepFail ARGS ((CztHovrPrepFail *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueHovrReport_IEsCls ARGS ((Czt_ValueHovrReport_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_HovrReport_IEs ARGS ((CztProtIE_Field_HovrReport_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Cont_HovrReport_IEs ARGS ((CztProtIE_Cont_HovrReport_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztHovrReport ARGS ((CztHovrReport *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsCls ARGS ((Czt_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEs ARGS ((CztProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEs ARGS ((CztProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztE_RABs_SubjToStatusTfr_Item ARGS ((CztE_RABs_SubjToStatusTfr_Item *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueE_RABs_SubjToStatusTfr_ItemIEsCls ARGS ((Czt_ValueE_RABs_SubjToStatusTfr_ItemIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEs ARGS ((CztProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztE_RABs_SubjToStatusTfr_Lst ARGS ((CztE_RABs_SubjToStatusTfr_Lst *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueSNStatusTfr_IEsCls ARGS ((Czt_ValueSNStatusTfr_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_SNStatusTfr_IEs ARGS ((CztProtIE_Field_SNStatusTfr_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Cont_SNStatusTfr_IEs ARGS ((CztProtIE_Cont_SNStatusTfr_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztSNStatusTfr ARGS ((CztSNStatusTfr *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueUECntxtRls_IEsCls ARGS ((Czt_ValueUECntxtRls_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_UECntxtRls_IEs ARGS ((CztProtIE_Field_UECntxtRls_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Cont_UECntxtRls_IEs ARGS ((CztProtIE_Cont_UECntxtRls_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztUECntxtRls ARGS ((CztUECntxtRls *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueHovrCancel_IEsCls ARGS ((Czt_ValueHovrCancel_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_HovrCancel_IEs ARGS ((CztProtIE_Field_HovrCancel_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Cont_HovrCancel_IEs ARGS ((CztProtIE_Cont_HovrCancel_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztHovrCancel ARGS ((CztHovrCancel *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueErrInd_IEsCls ARGS ((Czt_ValueErrInd_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_ErrInd_IEs ARGS ((CztProtIE_Field_ErrInd_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Cont_ErrInd_IEs ARGS ((CztProtIE_Cont_ErrInd_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztErrInd ARGS ((CztErrInd *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueResetRqst_IEsCls ARGS ((Czt_ValueResetRqst_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_ResetRqst_IEs ARGS ((CztProtIE_Field_ResetRqst_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Cont_ResetRqst_IEs ARGS ((CztProtIE_Cont_ResetRqst_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztResetRqst ARGS ((CztResetRqst *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueResetResp_IEsCls ARGS ((Czt_ValueResetResp_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_ResetResp_IEs ARGS ((CztProtIE_Field_ResetResp_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Cont_ResetResp_IEs ARGS ((CztProtIE_Cont_ResetResp_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztResetResp ARGS ((CztResetResp *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueX2SetupRqst_IEsCls ARGS ((Czt_ValueX2SetupRqst_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_X2SetupRqst_IEs ARGS ((CztProtIE_Field_X2SetupRqst_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Cont_X2SetupRqst_IEs ARGS ((CztProtIE_Cont_X2SetupRqst_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztX2SetupRqst ARGS ((CztX2SetupRqst *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueX2SetupResp_IEsCls ARGS ((Czt_ValueX2SetupResp_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_X2SetupResp_IEs ARGS ((CztProtIE_Field_X2SetupResp_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Cont_X2SetupResp_IEs ARGS ((CztProtIE_Cont_X2SetupResp_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztX2SetupResp ARGS ((CztX2SetupResp *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueX2SetupFail_IEsCls ARGS ((Czt_ValueX2SetupFail_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_X2SetupFail_IEs ARGS ((CztProtIE_Field_X2SetupFail_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Cont_X2SetupFail_IEs ARGS ((CztProtIE_Cont_X2SetupFail_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztX2SetupFail ARGS ((CztX2SetupFail *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnCellInform_Item_ExtIEsCls ARGS ((Czt_ExtnCellInform_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_CellInform_Item_ExtIEs ARGS ((CztProtExtnField_CellInform_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_CellInform_Item_ExtIEs ARGS ((CztProtExtnCont_CellInform_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztCellInform_Item ARGS ((CztCellInform_Item *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueCellInform_ItemIEsCls ARGS ((Czt_ValueCellInform_ItemIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_CellInform_ItemIEs ARGS ((CztProtIE_Field_CellInform_ItemIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztCellInform_Lst ARGS ((CztCellInform_Lst *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueLoadInform_IEsCls ARGS ((Czt_ValueLoadInform_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_LoadInform_IEs ARGS ((CztProtIE_Field_LoadInform_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Cont_LoadInform_IEs ARGS ((CztProtIE_Cont_LoadInform_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztLoadInform ARGS ((CztLoadInform *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnSrvdCellsToMdfy_Item_ExtIEsCls ARGS ((Czt_ExtnSrvdCellsToMdfy_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_SrvdCellsToMdfy_Item_ExtIEs ARGS ((CztProtExtnField_SrvdCellsToMdfy_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_SrvdCellsToMdfy_Item_ExtIEs ARGS ((CztProtExtnCont_SrvdCellsToMdfy_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztSrvdCellsToMdfy_Item ARGS ((CztSrvdCellsToMdfy_Item *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztSrvdCellsToMdfy ARGS ((CztSrvdCellsToMdfy *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztOld_ECGIs ARGS ((CztOld_ECGIs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueENBConfigUpd_IEsCls ARGS ((Czt_ValueENBConfigUpd_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_ENBConfigUpd_IEs ARGS ((CztProtIE_Field_ENBConfigUpd_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Cont_ENBConfigUpd_IEs ARGS ((CztProtIE_Cont_ENBConfigUpd_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztENBConfigUpd ARGS ((CztENBConfigUpd *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueENBConfigUpdAckg_IEsCls ARGS ((Czt_ValueENBConfigUpdAckg_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_ENBConfigUpdAckg_IEs ARGS ((CztProtIE_Field_ENBConfigUpdAckg_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Cont_ENBConfigUpdAckg_IEs ARGS ((CztProtIE_Cont_ENBConfigUpdAckg_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztENBConfigUpdAckg ARGS ((CztENBConfigUpdAckg *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueENBConfigUpdFail_IEsCls ARGS ((Czt_ValueENBConfigUpdFail_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_ENBConfigUpdFail_IEs ARGS ((CztProtIE_Field_ENBConfigUpdFail_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Cont_ENBConfigUpdFail_IEs ARGS ((CztProtIE_Cont_ENBConfigUpdFail_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztENBConfigUpdFail ARGS ((CztENBConfigUpdFail *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnCellToReport_Item_ExtIEsCls ARGS ((Czt_ExtnCellToReport_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_CellToReport_Item_ExtIEs ARGS ((CztProtExtnField_CellToReport_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_CellToReport_Item_ExtIEs ARGS ((CztProtExtnCont_CellToReport_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztCellToReport_Item ARGS ((CztCellToReport_Item *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueCellToReport_ItemIEsCls ARGS ((Czt_ValueCellToReport_ItemIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_CellToReport_ItemIEs ARGS ((CztProtIE_Field_CellToReport_ItemIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztCellToReport_Lst ARGS ((CztCellToReport_Lst *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueResStatusRqst_IEsCls ARGS ((Czt_ValueResStatusRqst_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_ResStatusRqst_IEs ARGS ((CztProtIE_Field_ResStatusRqst_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Cont_ResStatusRqst_IEs ARGS ((CztProtIE_Cont_ResStatusRqst_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztResStatusRqst ARGS ((CztResStatusRqst *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnMeasurementFailCause_Item_ExtIEsCls ARGS ((Czt_ExtnMeasurementFailCause_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_MeasurementFailCause_Item_ExtIEs ARGS ((CztProtExtnField_MeasurementFailCause_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_MeasurementFailCause_Item_ExtIEs ARGS ((CztProtExtnCont_MeasurementFailCause_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztMeasurementFailCause_Item ARGS ((CztMeasurementFailCause_Item *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueMeasurementFailCause_ItemIEsCls ARGS ((Czt_ValueMeasurementFailCause_ItemIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_MeasurementFailCause_ItemIEs ARGS ((CztProtIE_Field_MeasurementFailCause_ItemIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztMeasurementFailCause_Lst ARGS ((CztMeasurementFailCause_Lst *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnMeasurementInitiationResult_Item_ExtIEsCls ARGS ((Czt_ExtnMeasurementInitiationResult_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_MeasurementInitiationResult_Item_ExtIEs ARGS ((CztProtExtnField_MeasurementInitiationResult_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_MeasurementInitiationResult_Item_ExtIEs ARGS ((CztProtExtnCont_MeasurementInitiationResult_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztMeasurementInitiationResult_Item ARGS ((CztMeasurementInitiationResult_Item *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueMeasurementInitiationResult_ItemIEsCls ARGS ((Czt_ValueMeasurementInitiationResult_ItemIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_MeasurementInitiationResult_ItemIEs ARGS ((CztProtIE_Field_MeasurementInitiationResult_ItemIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztMeasurementInitiationResult_Lst ARGS ((CztMeasurementInitiationResult_Lst *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueResStatusResp_IEsCls ARGS ((Czt_ValueResStatusResp_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_ResStatusResp_IEs ARGS ((CztProtIE_Field_ResStatusResp_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Cont_ResStatusResp_IEs ARGS ((CztProtIE_Cont_ResStatusResp_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztResStatusResp ARGS ((CztResStatusResp *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnCompleteFailCauseInform_Item_ExtIEsCls ARGS ((Czt_ExtnCompleteFailCauseInform_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_CompleteFailCauseInform_Item_ExtIEs ARGS ((CztProtExtnField_CompleteFailCauseInform_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_CompleteFailCauseInform_Item_ExtIEs ARGS ((CztProtExtnCont_CompleteFailCauseInform_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztCompleteFailCauseInform_Item ARGS ((CztCompleteFailCauseInform_Item *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueCompleteFailCauseInform_ItemIEsCls ARGS ((Czt_ValueCompleteFailCauseInform_ItemIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_CompleteFailCauseInform_ItemIEs ARGS ((CztProtIE_Field_CompleteFailCauseInform_ItemIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztCompleteFailCauseInform_Lst ARGS ((CztCompleteFailCauseInform_Lst *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueResStatusFail_IEsCls ARGS ((Czt_ValueResStatusFail_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_ResStatusFail_IEs ARGS ((CztProtIE_Field_ResStatusFail_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Cont_ResStatusFail_IEs ARGS ((CztProtIE_Cont_ResStatusFail_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztResStatusFail ARGS ((CztResStatusFail *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnCellMeasurementResult_Item_ExtIEsCls ARGS ((Czt_ExtnCellMeasurementResult_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_CellMeasurementResult_Item_ExtIEs ARGS ((CztProtExtnField_CellMeasurementResult_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_CellMeasurementResult_Item_ExtIEs ARGS ((CztProtExtnCont_CellMeasurementResult_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztCellMeasurementResult_Item ARGS ((CztCellMeasurementResult_Item *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueCellMeasurementResult_ItemIEsCls ARGS ((Czt_ValueCellMeasurementResult_ItemIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_CellMeasurementResult_ItemIEs ARGS ((CztProtIE_Field_CellMeasurementResult_ItemIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztCellMeasurementResult_Lst ARGS ((CztCellMeasurementResult_Lst *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueResStatusUpd_IEsCls ARGS ((Czt_ValueResStatusUpd_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_ResStatusUpd_IEs ARGS ((CztProtIE_Field_ResStatusUpd_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Cont_ResStatusUpd_IEs ARGS ((CztProtIE_Cont_ResStatusUpd_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztResStatusUpd ARGS ((CztResStatusUpd *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValuePrivMsg_IEsCls ARGS ((Czt_ValuePrivMsg_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztPrivIE_Field_PrivMsg_IEs ARGS ((CztPrivIE_Field_PrivMsg_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztPrivIE_Cont_PrivMsg_IEs ARGS ((CztPrivIE_Cont_PrivMsg_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztPrivMsg ARGS ((CztPrivMsg *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueMobilityChangeRqst_IEsCls ARGS ((Czt_ValueMobilityChangeRqst_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_MobilityChangeRqst_IEs ARGS ((CztProtIE_Field_MobilityChangeRqst_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Cont_MobilityChangeRqst_IEs ARGS ((CztProtIE_Cont_MobilityChangeRqst_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztMobilityChangeRqst ARGS ((CztMobilityChangeRqst *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueMobilityChangeAckg_IEsCls ARGS ((Czt_ValueMobilityChangeAckg_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_MobilityChangeAckg_IEs ARGS ((CztProtIE_Field_MobilityChangeAckg_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Cont_MobilityChangeAckg_IEs ARGS ((CztProtIE_Cont_MobilityChangeAckg_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztMobilityChangeAckg ARGS ((CztMobilityChangeAckg *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueMobilityChangeFail_IEsCls ARGS ((Czt_ValueMobilityChangeFail_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_MobilityChangeFail_IEs ARGS ((CztProtIE_Field_MobilityChangeFail_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Cont_MobilityChangeFail_IEs ARGS ((CztProtIE_Cont_MobilityChangeFail_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztMobilityChangeFail ARGS ((CztMobilityChangeFail *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueRLFInd_IEsCls ARGS ((Czt_ValueRLFInd_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_RLFInd_IEs ARGS ((CztProtIE_Field_RLFInd_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Cont_RLFInd_IEs ARGS ((CztProtIE_Cont_RLFInd_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztRLFInd ARGS ((CztRLFInd *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnSrvdCellsToActivate_Item_ExtIEsCls ARGS ((Czt_ExtnSrvdCellsToActivate_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_SrvdCellsToActivate_Item_ExtIEs ARGS ((CztProtExtnField_SrvdCellsToActivate_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_SrvdCellsToActivate_Item_ExtIEs ARGS ((CztProtExtnCont_SrvdCellsToActivate_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztSrvdCellsToActivate_Item ARGS ((CztSrvdCellsToActivate_Item *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztSrvdCellsToActivate ARGS ((CztSrvdCellsToActivate *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueCellActvnRqst_IEsCls ARGS ((Czt_ValueCellActvnRqst_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_CellActvnRqst_IEs ARGS ((CztProtIE_Field_CellActvnRqst_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Cont_CellActvnRqst_IEs ARGS ((CztProtIE_Cont_CellActvnRqst_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztCellActvnRqst ARGS ((CztCellActvnRqst *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ExtnActivatedCellLst_Item_ExtIEsCls ARGS ((Czt_ExtnActivatedCellLst_Item_ExtIEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnField_ActivatedCellLst_Item_ExtIEs ARGS ((CztProtExtnField_ActivatedCellLst_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtExtnCont_ActivatedCellLst_Item_ExtIEs ARGS ((CztProtExtnCont_ActivatedCellLst_Item_ExtIEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztActivatedCellLst_Item ARGS ((CztActivatedCellLst_Item *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztActivatedCellLst ARGS ((CztActivatedCellLst *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueCellActvnResp_IEsCls ARGS ((Czt_ValueCellActvnResp_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_CellActvnResp_IEs ARGS ((CztProtIE_Field_CellActvnResp_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Cont_CellActvnResp_IEs ARGS ((CztProtIE_Cont_CellActvnResp_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztCellActvnResp ARGS ((CztCellActvnResp *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_ValueCellActvnFail_IEsCls ARGS ((Czt_ValueCellActvnFail_IEsCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Field_CellActvnFail_IEs ARGS ((CztProtIE_Field_CellActvnFail_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztProtIE_Cont_CellActvnFail_IEs ARGS ((CztProtIE_Cont_CellActvnFail_IEs *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztCellActvnFail ARGS ((CztCellActvnFail *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_InitiatingMsgCls ARGS ((Czt_InitiatingMsgCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztInitiatingMsg ARGS ((CztInitiatingMsg *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_SuccessfulOutcomeCls ARGS ((Czt_SuccessfulOutcomeCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztSuccessfulOutcome ARGS ((CztSuccessfulOutcome *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCzt_UnsuccessfulOutcomeCls ARGS ((Czt_UnsuccessfulOutcomeCls *param, U32 val, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztUnsuccessfulOutcome ARGS ((CztUnsuccessfulOutcome *param, Ptr ptr, Buffer *mBuf));
EXTERN S16 cmUnpkCztX2AP_PDU ARGS ((CztX2AP_PDU *param, Ptr ptr, Buffer *mBuf));
#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif

/********************************************************************30**

           End of file:    $SID$

*********************************************************************31*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
$SID$        ---      chebli         1. Updated DB for X2AP R11 for TotaleNodeB GA3.0
$SID$        ---      chebli         1. Updated DB for X2AP R11.8.0 for TotaleNodeB GA5.0
*********************************************************************91*/

