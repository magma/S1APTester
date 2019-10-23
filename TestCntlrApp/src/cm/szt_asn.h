/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_smm_init.c

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/

#ifndef __SZTASNH__
#define __SZTASNH__ 

#define SZUCHKUNPKPTR(func, val, ptr, mBuf) {\
   S16 ret;\
   if ((ret = func(val, mBuf, ptr)) != ROK)\
      RETVALUE(ret);\
}
#define Sztid_Invalid 0xffffffff

#define PRIVIE_ID_LOCAL 0
#define PRIVIE_ID_GLOBAL 1
#define Sztid_HovrPrep 0
#define Sztid_HovrResourceAllocn 1
#define Sztid_HovrNotification 2
#define Sztid_PathSwRqst 3
#define Sztid_HovrCancel 4
#define Sztid_E_RABSetup 5
#define Sztid_E_RABMdfy 6
#define Sztid_E_RABRls 7
#define Sztid_E_RABRlsInd 8
#define Sztid_InitCntxtSetup 9
#define Sztid_Pag 10
#define Sztid_downlinkNASTport 11
#define Sztid_initialUEMsg 12
#define Sztid_uplinkNASTport 13
#define Sztid_Reset 14
#define Sztid_ErrInd 15
#define Sztid_NASNonDlvryInd 16
#define Sztid_S1Setup 17
#define Sztid_UECntxtRlsRqst 18
#define Sztid_DlnkS1cdma2000tunneling 19
#define Sztid_UlnkS1cdma2000tunneling 20
#define Sztid_UECntxtModification 21
#define Sztid_UECapbltyInfoInd 22
#define Sztid_UECntxtRls 23
#define Sztid_eNBStatusTfr 24
#define Sztid_MMEStatusTfr 25
#define Sztid_DeactvTrace 26
#define Sztid_TraceStart 27
#define Sztid_TraceFailInd 28
#define Sztid_ENBConfigUpd 29
#define Sztid_MMEConfigUpd 30
#define Sztid_LocRprtngCntrl 31
#define Sztid_LocRprtngFailInd 32
#define Sztid_LocReport 33
#define Sztid_OverloadStart 34
#define Sztid_OverloadStop 35
#define Sztid_WriteReplaceWarning 36
#define Sztid_eNBDirectInformTfr 37
#define Sztid_MMEDirectInformTfr 38
#define Sztid_PrivMsg 39
#define Sztid_eNBConfigTfr 40
#define Sztid_MMEConfigTfr 41
#define Sztid_CellTrafficTrace 42
#define Sztid_Kill 43
#define Sztid_downlinkUEAssociatedLPPaTport 44
#define Sztid_uplinkUEAssociatedLPPaTport 45
#define Sztid_downlinkNonUEAssociatedLPPaTport 46
#define Sztid_uplinkNonUEAssociatedLPPaTport 47
#define Sztid_UERadioCapbltyMatch 48
#define SztmaxPrivIEs 65535
#define SztmaxProtExtns 65535
#define SztmaxProtIEs 65535
#define SztmaxnoofCSGs 256
#define SztmaxnoofE_RABs 256
#define SztmaxnoofTAIs 256
#define SztmaxnoofTACs 256
#define SztmaxnoofErrs 256
#define SztmaxnoofBPLMNs 6
#define SztmaxnoofPLMNsPerMME 32
#define SztmaxnoofEPLMNs 15
#define SztmaxnoofEPLMNsPlusOne 16
#define SztmaxnoofForbLACs 4096
#define SztmaxnoofForbTACs 4096
#define SztmaxnoofIvdualS1ConsToReset 256
#define SztmaxnoofCells 16
#define SztmaxnoofTAIforWarning 65535
#define SztmaxnoofCellID 65535
#define SztmaxnoofEmergencyAreaID 65535
#define SztmaxnoofCellinTAI 65535
#define SztmaxnoofCellinEAI 65535
#define SztmaxnoofeNBX2TLAs 2
#define SztmaxnoofeNBX2ExtTLAs 16
#define SztmaxnoofeNBX2GTPTLAs 16
#define SztmaxnoofRATs 8
#define SztmaxnoofGroupIDs 65535
#define SztmaxnoofMMECs 256
#define SztmaxnoofCellIDforMDT 32
#define SztmaxnoofTAforMDT 8
#define SztmaxnoofMDTPLMNs 16
#define Sztid_MME_UE_S1AP_ID 0
#define Sztid_HovrTyp 1
#define Sztid_Cause 2
#define Sztid_SrcID 3
#define Sztid_TgetID 4
#define Sztid_eNB_UE_S1AP_ID 8
#define Sztid_E_RABSubjtoDataFwdingLst 12
#define Sztid_E_RABtoRlsLstHOCmd 13
#define Sztid_E_RABDataFwdingItem 14
#define Sztid_E_RABRlsItemBrRelComp 15
#define Sztid_E_RABToBeSetupLstBrSUReq 16
#define Sztid_E_RABToBeSetupItemBrSUReq 17
#define Sztid_E_RABAdmtdLst 18
#define Sztid_E_RABFailedToSetupLstHOReqAck 19
#define Sztid_E_RABAdmtdItem 20
#define Sztid_E_RABFailedtoSetupItemHOReqAck 21
#define Sztid_E_RABToBeSwedDLLst 22
#define Sztid_E_RABToBeSwedDLItem 23
#define Sztid_E_RABToBeSetupLstCtxtSUReq 24
#define Sztid_TraceActvn 25
#define Sztid_NAS_PDU 26
#define Sztid_E_RABToBeSetupItemHOReq 27
#define Sztid_E_RABSetupLstBrSURes 28
#define Sztid_E_RABFailedToSetupLstBrSURes 29
#define Sztid_E_RABToBeMdfdLstBrModReq 30
#define Sztid_E_RABMdfyLstBrModRes 31
#define Sztid_E_RABFailedToMdfyLst 32
#define Sztid_E_RABToBeRlsdLst 33
#define Sztid_E_RABFailedToRlsLst 34
#define Sztid_E_RABItem 35
#define Sztid_E_RABToBeMdfdItemBrModReq 36
#define Sztid_E_RABMdfyItemBrModRes 37
#define Sztid_E_RABRlsItem 38
#define Sztid_E_RABSetupItemBrSURes 39
#define Sztid_SecurCntxt 40
#define Sztid_HovrRestrnLst 41
#define Sztid_UEPagID 43
#define Sztid_pagingDRX 44
#define Sztid_TAILst 46
#define Sztid_TAIItem 47
#define Sztid_E_RABFailedToSetupLstCtxtSURes 48
#define Sztid_E_RABRlsItemHOCmd 49
#define Sztid_E_RABSetupItemCtxtSURes 50
#define Sztid_E_RABSetupLstCtxtSURes 51
#define Sztid_E_RABToBeSetupItemCtxtSUReq 52
#define Sztid_E_RABToBeSetupLstHOReq 53
#define Sztid_GERANtoLTEHOInformRes 55
#define Sztid_UTRANtoLTEHOInformRes 57
#define Sztid_CriticalityDiag 58
#define Sztid_Global_ENB_ID 59
#define Sztid_eNBname 60
#define Sztid_MMEname 61
#define Sztid_SrvdPLMNs 63
#define Sztid_SuppTAs 64
#define Sztid_TimeToWait 65
#define Sztid_uEaggregateMaxBitrate 66
#define Sztid_TAI 67
#define Sztid_E_RABRlsLstBrRelComp 69
#define Sztid_cdma2000PDU 70
#define Sztid_cdma2000RATTyp 71
#define Sztid_cdma2000SectorID 72
#define Sztid_SecurKey 73
#define Sztid_UERadioCapblty 74
#define Sztid_GUMMEI_ID 75
#define Sztid_E_RABInformLstItem 78
#define Sztid_Direct_Fwding_Path_Avlblty 79
#define Sztid_UEIdentityIdxValue 80
#define Sztid_cdma2000HOStatus 83
#define Sztid_cdma2000HOReqdInd 84
#define Sztid_E_UTRAN_Trace_ID 86
#define Sztid_RelativeMMECapacity 87
#define Sztid_SrcMME_UE_S1AP_ID 88
#define Sztid_Brs_SubjToStatusTfr_Item 89
#define Sztid_eNB_StatusTfr_TprntCont 90
#define Sztid_UE_assocLogS1_ConItem 91
#define Sztid_ResetTyp 92
#define Sztid_UE_assocLogS1_ConLstResAck 93
#define Sztid_E_RABToBeSwedULItem 94
#define Sztid_E_RABToBeSwedULLst 95
#define Sztid_S_TMSI 96
#define Sztid_cdma2000OneXRAND 97
#define Sztid_RqstTyp 98
#define Sztid_UE_S1AP_IDs 99
#define Sztid_EUTRAN_CGI 100
#define Sztid_OverloadResp 101
#define Sztid_cdma2000OneXSRVCCInfo 102
#define Sztid_E_RABFailedToBeRlsdLst 103
#define Sztid_Src_ToTget_TprntCont 104
#define Sztid_SrvdGUMMEIs 105
#define Sztid_SubscriberProfileIDforRFP 106
#define Sztid_UESecurCapabilities 107
#define Sztid_CSFallbackIndicator 108
#define Sztid_CNDomain 109
#define Sztid_E_RABRlsdLst 110
#define Sztid_MsgIdentifier 111
#define Sztid_SerialNumber 112
#define Sztid_WarningAreaLst 113
#define Sztid_RepetitionPeriod 114
#define Sztid_NumberofBroadcastRqst 115
#define Sztid_WarningTyp 116
#define Sztid_WarningSecurInfo 117
#define Sztid_DataCodingScheme 118
#define Sztid_WarningMsgContents 119
#define Sztid_BroadcastCompletedAreaLst 120
#define Sztid_Inter_SystemInformTfrTypEDT 121
#define Sztid_Inter_SystemInformTfrTypMDT 122
#define Sztid_Tget_ToSrc_TprntCont 123
#define Sztid_SRVCCOperationPossible 124
#define Sztid_SRVCCHOInd 125
#define Sztid_NAS_DlnkCount 126
#define Sztid_CSG_Id 127
#define Sztid_CSG_IdLst 128
#define Sztid_SONConfigTfrECT 129
#define Sztid_SONConfigTfrMCT 130
#define Sztid_TraceCollectionEntityIPAddr 131
#define Sztid_MSClassmark2 132
#define Sztid_MSClassmark3 133
#define Sztid_RRC_Establishment_Cause 134
#define Sztid_NASSecurParamsfromE_UTRAN 135
#define Sztid_NASSecurParamstoE_UTRAN 136
#define Sztid_DefaultPagDRX 137
#define Sztid_Src_ToTget_TprntCont_Secondary 138
#define Sztid_Tget_ToSrc_TprntCont_Secondary 139
#define Sztid_EUTRANRoundTripDelayEstimationInfo 140
#define Sztid_BroadcastCancelledAreaLst 141
#define Sztid_ConcurrentWarningMsgIndicator 142
#define Sztid_Data_Fwding_Not_Possible 143
#define Sztid_ExtendedRepetitionPeriod 144
#define Sztid_CellAccessMode 145
#define Sztid_CSGMembershipStatus 146
#define Sztid_LPPa_PDU 147
#define Sztid_Routing_ID 148
#define Sztid_Time_Synchronization_Info 149
#define Sztid_PS_ServiceNotAvailable 150
#define Sztid_PagPriority 151
#define Sztid_x2TNLConfigInfo 152
#define Sztid_eNBX2ExtendedTportLyrAddres 153
#define Sztid_GUMMEILst 154
#define Sztid_GW_TportLyrAddr 155
#define Sztid_Correlation_ID 156
#define Sztid_SrcMME_GUMMEI 157
#define Sztid_MME_UE_S1AP_ID_2 158
#define Sztid_RegisteredLAI 159
#define Sztid_RelayNode_Indicator 160
#define Sztid_TrafficLoadReductionInd 161
#define Sztid_MDTConfig 162
#define Sztid_MMERelaySupportIndicator 163
#define Sztid_GWCntxtRlsInd 164
#define Sztid_ManagementBasedMDTAllowed 165
#define Sztid_PrivacyIndicator 166
#define Sztid_Time_UE_StayedInCell_EnhancedGranularity 167
#define Sztid_HO_Cause 168
#define Sztid_VoiceSupportMatchIndicator 169
#define Sztid_GUMMEITyp 170
#define Sztid_M3Config 171
#define Sztid_M4Config 172
#define Sztid_M5Config 173
#define Sztid_MDT_Loc_Info 174
#define Sztid_MobilityInform 175
#define Sztid_Tunnel_Inform_for_BBF 176
#define Sztid_ManagementBasedMDTPLMNLst 177
#define Sztid_SignallingBasedMDTPLMNLst 178
#define Sztid_ULCOUNTValueExtended 179
#define Sztid_DLCOUNTValueExtended 180
#define Sztid_ReceiveStatusOfULPDCPSDUsExtended 181

#define AREASCOPEOFMDT_CELLBASED 0
#define AREASCOPEOFMDT_TABASED 1
#define AREASCOPEOFMDT_PLMNWIDE 2
#define AREASCOPEOFMDT_TAIBASED 3

#define BROADCASTCANCELLEDAREALST_CELLID_CANCELLED 0
#define BROADCASTCANCELLEDAREALST_TAI_CANCELLED 1
#define BROADCASTCANCELLEDAREALST_EMERGENCYAREAID_CANCELLED 2

#define BROADCASTCOMPLETEDAREALST_CELLID_BROADCAST 0
#define BROADCASTCOMPLETEDAREALST_TAI_BROADCAST 1
#define BROADCASTCOMPLETEDAREALST_EMERGENCYAREAID_BROADCAST 2

#define CAUSE_RADIONW 0
#define CAUSE_TRANSPORT 1
#define CAUSE_NAS 2
#define CAUSE_PROTOCOL 3
#define CAUSE_MISC 4

#define ENB_ID_MACROENB_ID 0
#define ENB_ID_HOMEENB_ID 1

#define MEASUREMENTTHRESHOLDA2_THRESHOLD_RSRP 0
#define MEASUREMENTTHRESHOLDA2_THRESHOLD_RSRQ 1

#define LASTVISITEDGERANCELLINFORM_UNDEFINED 0

#define LASTVISITEDCELL_ITEM_E_UTRAN_CELL 0
#define LASTVISITEDCELL_ITEM_UTRAN_CELL 1
#define LASTVISITEDCELL_ITEM_GERAN_CELL 2

#define MDTMODE_IMMEDIATEMDT 0
#define MDTMODE_LOGGEDMDT 1

#define OVERLOADRESP_OVERLOADACTION 0

#define RIMROUTINGADDR_GERAN_CELL_ID 0
#define RIMROUTINGADDR_TARGETRNC_ID 1

#define SONINFORM_SONINFORMRQST 0
#define SONINFORM_SONINFORMREPLY 1

#define TGETID_TARGETENB_ID 0
#define TGETID_TARGETRNC_ID 1
#define TGETID_CGI 2

#define UE_S1AP_IDS_UE_S1AP_ID_PAIR 0
#define UE_S1AP_IDS_MME_UE_S1AP_ID 1

#define UEPAGID_S_TMSI 0
#define UEPAGID_IMSI 1

#define WARNINGAREALST_CELLIDLST 0
#define WARNINGAREALST_TRACKINGAREALSTFORWARNING 1
#define WARNINGAREALST_EMERGENCYAREAIDLST 2

#define RESETTYP_S1_INTF 0
#define RESETTYP_PARTOFS1_INTF 1

#define INTER_SYSTEMINFORMTFRTYP_RIMTFR 0

#define S1AP_PDU_INITIATINGMSG 0
#define S1AP_PDU_SUCCESSFULOUTCOME 1
#define S1AP_PDU_UNSUCCESSFULOUTCOME 2

#endif
/********************************************************************30**

           End of file:    $SID$

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
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
$SID$        ---      chebli         1. Updated DB for S1AP R11 for TotaleNodeB GA3.0
*********************************************************************91*/
