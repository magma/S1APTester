/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_smm_init.c

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/

#ifndef __SZTASNX__
#define __SZTASNX__ 

/* Element ----- Criticality ------- */
typedef enum enumSztCriticality
{
	SztCriticalityrejectEnum,
	SztCriticalityignoreEnum,
	SztCriticalitynotifyEnum
} EnumSztCriticality;
typedef TknU32 SztCriticality;

/* Element ----- Presence ------- */
typedef enum enumSztPresence
{
	SztPresenceoptionalEnum,
	SztPresenceconditionalEnum,
	SztPresencemandatoryEnum
} EnumSztPresence;
typedef TknU32 SztPresence;

/* Element ----- local ------- */
typedef TknU32 SztPrivIE_IDlocal;

typedef struct s1apPrivIE_ID
{
	TknU8 choice;
	union {
		SztPrivIE_IDlocal local;
	} val;
} SztPrivIE_ID;

/* Element ----- ProcedureCode ------- */
typedef TknU32 SztProcedureCode;

/* Element ----- ProtocolExtensionID ------- */
typedef TknU32 SztProtExtnID;

/* Element ----- ProtocolIE-ID ------- */
typedef TknU32 SztProtIE_ID;

/* Element ----- TriggeringMessage ------- */
typedef enum enumSztTrgMsg
{
	SztTrgMsginitiating_messageEnum,
	SztTrgMsgsuccessful_outcomeEnum,
	SztTrgMsgunsuccessfull_outcomeEnum
} EnumSztTrgMsg;
typedef TknU32 SztTrgMsg;

/* Element ---------- TBCD-STRING ----------- */
typedef TknStrOSXL SztTBCD_STRING;
/* Element ------------- PLMNidentity ------------ */
typedef SztTBCD_STRING  SztPLMNidentity;
/* Element ---------- CellIdentity ----------- */
typedef TknBStr32 SztCellIdentity;
typedef struct s1ap_ExtnEUTRAN_CGI_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnEUTRAN_CGI_ExtIEsCls;
typedef struct s1apProtExtnField_EUTRAN_CGI_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnEUTRAN_CGI_ExtIEsCls extensionValue;
} SztProtExtnField_EUTRAN_CGI_ExtIEs;

typedef struct s1apProtExtnCont_EUTRAN_CGI_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_EUTRAN_CGI_ExtIEs *member;
}SztProtExtnCont_EUTRAN_CGI_ExtIEs;

typedef struct s1apEUTRAN_CGI
{
	TknPres pres;
	SztPLMNidentity pLMNidentity;
	SztCellIdentity cell_ID;
	SztProtExtnCont_EUTRAN_CGI_ExtIEs iE_Extns;
} SztEUTRAN_CGI;

typedef struct s1apCellIdLstforMDT
{
	TknU16 noComp;
	SztEUTRAN_CGI *member;
}SztCellIdLstforMDT;

typedef struct s1ap_ExtnCellBasedMDT_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnCellBasedMDT_ExtIEsCls;
typedef struct s1apProtExtnField_CellBasedMDT_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnCellBasedMDT_ExtIEsCls extensionValue;
} SztProtExtnField_CellBasedMDT_ExtIEs;

typedef struct s1apProtExtnCont_CellBasedMDT_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_CellBasedMDT_ExtIEs *member;
}SztProtExtnCont_CellBasedMDT_ExtIEs;

typedef struct s1apCellBasedMDT
{
	TknPres pres;
	SztCellIdLstforMDT cellIdLstforMDT;
	SztProtExtnCont_CellBasedMDT_ExtIEs iE_Extns;
} SztCellBasedMDT;

/* Element ---------- TAC ----------- */
typedef TknStr4 SztTAC;
typedef struct s1apTALstforMDT
{
	TknU16 noComp;
	SztTAC *member;
}SztTALstforMDT;

typedef struct s1ap_ExtnTABasedMDT_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnTABasedMDT_ExtIEsCls;
typedef struct s1apProtExtnField_TABasedMDT_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnTABasedMDT_ExtIEsCls extensionValue;
} SztProtExtnField_TABasedMDT_ExtIEs;

typedef struct s1apProtExtnCont_TABasedMDT_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_TABasedMDT_ExtIEs *member;
}SztProtExtnCont_TABasedMDT_ExtIEs;

typedef struct s1apTABasedMDT
{
	TknPres pres;
	SztTALstforMDT tALstforMDT;
	SztProtExtnCont_TABasedMDT_ExtIEs iE_Extns;
} SztTABasedMDT;

typedef struct s1ap_ExtnTAI_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnTAI_ExtIEsCls;
typedef struct s1apProtExtnField_TAI_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnTAI_ExtIEsCls extensionValue;
} SztProtExtnField_TAI_ExtIEs;

typedef struct s1apProtExtnCont_TAI_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_TAI_ExtIEs *member;
}SztProtExtnCont_TAI_ExtIEs;

typedef struct s1apTAI
{
	TknPres pres;
	SztPLMNidentity pLMNidentity;
	SztTAC tAC;
	SztProtExtnCont_TAI_ExtIEs iE_Extns;
} SztTAI;

typedef struct s1apTAILstforMDT
{
	TknU16 noComp;
	SztTAI *member;
}SztTAILstforMDT;

typedef struct s1ap_ExtnTAIBasedMDT_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnTAIBasedMDT_ExtIEsCls;
typedef struct s1apProtExtnField_TAIBasedMDT_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnTAIBasedMDT_ExtIEsCls extensionValue;
} SztProtExtnField_TAIBasedMDT_ExtIEs;

typedef struct s1apProtExtnCont_TAIBasedMDT_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_TAIBasedMDT_ExtIEs *member;
}SztProtExtnCont_TAIBasedMDT_ExtIEs;

typedef struct s1apTAIBasedMDT
{
	TknPres pres;
	SztTAILstforMDT tAILstforMDT;
	SztProtExtnCont_TAIBasedMDT_ExtIEs iE_Extns;
} SztTAIBasedMDT;

typedef struct s1apAreaScopeOfMDT
{
	TknU8 choice;
	union {
		SztCellBasedMDT cellBased;
		SztTABasedMDT tABased;
		SztTAIBasedMDT tAIBased;
	} val;
} SztAreaScopeOfMDT;

/* Element ----- PriorityLevel ------- */
typedef TknU32 SztPriorityLvl;

/* Element ----- Pre-emptionCapability ------- */
typedef enum enumSztPre_emptionCapblty
{
	SztPre_emptionCapbltyshall_not_trigger_pre_emptionEnum,
	SztPre_emptionCapbltymay_trigger_pre_emptionEnum
} EnumSztPre_emptionCapblty;
typedef TknU32 SztPre_emptionCapblty;

/* Element ----- Pre-emptionVulnerability ------- */
typedef enum enumSztPre_emptionVulnerability
{
	SztPre_emptionVulnerabilitynot_pre_emptableEnum,
	SztPre_emptionVulnerabilitypre_emptableEnum
} EnumSztPre_emptionVulnerability;
typedef TknU32 SztPre_emptionVulnerability;

typedef struct s1ap_ExtnAllocnAndRetentionPriority_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnAllocnAndRetentionPriority_ExtIEsCls;
typedef struct s1apProtExtnField_AllocnAndRetentionPriority_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnAllocnAndRetentionPriority_ExtIEsCls extensionValue;
} SztProtExtnField_AllocnAndRetentionPriority_ExtIEs;

typedef struct s1apProtExtnCont_AllocnAndRetentionPriority_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_AllocnAndRetentionPriority_ExtIEs *member;
}SztProtExtnCont_AllocnAndRetentionPriority_ExtIEs;

typedef struct s1apAllocnAndRetentionPriority
{
	TknPres pres;
	SztPriorityLvl priorityLvl;
	SztPre_emptionCapblty pre_emptionCapblty;
	SztPre_emptionVulnerability pre_emptionVulnerability;
	SztProtExtnCont_AllocnAndRetentionPriority_ExtIEs iE_Extns;
} SztAllocnAndRetentionPriority;

/* Element ----- E-RAB-ID ------- */
typedef TknU32 SztE_RAB_ID;

/* Element ----- PDCP-SN ------- */
typedef TknU32 SztPDCP_SN;

/* Element ----- HFN ------- */
typedef TknU32 SztHFN;

typedef struct s1ap_ExtnCOUNTvalue_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnCOUNTvalue_ExtIEsCls;
typedef struct s1apProtExtnField_COUNTvalue_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnCOUNTvalue_ExtIEsCls extensionValue;
} SztProtExtnField_COUNTvalue_ExtIEs;

typedef struct s1apProtExtnCont_COUNTvalue_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_COUNTvalue_ExtIEs *member;
}SztProtExtnCont_COUNTvalue_ExtIEs;

typedef struct s1apCOUNTvalue
{
	TknPres pres;
	SztPDCP_SN pDCP_SN;
	SztHFN hFN;
	SztProtExtnCont_COUNTvalue_ExtIEs iE_Extns;
} SztCOUNTvalue;

/* Element ---------- ReceiveStatusofULPDCPSDUs ----------- */
typedef TknStrBSXL SztReceiveStatusofULPDCPSDUs;
/* Element ----- PDCP-SNExtended ------- */
typedef TknU32 SztPDCP_SNExtended;

/* Element ----- HFNModified ------- */
typedef TknU32 SztHFNMdfd;

typedef struct s1ap_ExtnCOUNTValueExtended_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnCOUNTValueExtended_ExtIEsCls;
typedef struct s1apProtExtnField_COUNTValueExtended_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnCOUNTValueExtended_ExtIEsCls extensionValue;
} SztProtExtnField_COUNTValueExtended_ExtIEs;

typedef struct s1apProtExtnCont_COUNTValueExtended_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_COUNTValueExtended_ExtIEs *member;
}SztProtExtnCont_COUNTValueExtended_ExtIEs;

typedef struct s1apCOUNTValueExtended
{
	TknPres pres;
	SztPDCP_SNExtended pDCP_SNExtended;
	SztHFNMdfd hFNMdfd;
	SztProtExtnCont_COUNTValueExtended_ExtIEs iE_Extns;
} SztCOUNTValueExtended;

/* Element ---------- ReceiveStatusOfULPDCPSDUsExtended ----------- */
typedef TknStrBSXL SztReceiveStatusOfULPDCPSDUsExtended;
typedef struct s1ap_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls{
	union {
		SztCOUNTValueExtended sztid_ULCOUNTValueExtended;
		SztCOUNTValueExtended sztid_DLCOUNTValueExtended;
		SztReceiveStatusOfULPDCPSDUsExtended sztReceiveStatusOfULPDCPSDUsExtended;
	} u;
} Szt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls;
typedef struct s1apProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls extensionValue;
} SztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs;

typedef struct s1apProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs
{
	TknU16 noComp;
	SztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs *member;
}SztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs;

typedef struct s1apBrs_SubjToStatusTfr_Item
{
	TknPres pres;
	SztE_RAB_ID e_RAB_ID;
	SztCOUNTvalue uL_COUNTvalue;
	SztCOUNTvalue dL_COUNTvalue;
	SztReceiveStatusofULPDCPSDUs receiveStatusofULPDCPSDUs;
	SztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs iE_Extns;
} SztBrs_SubjToStatusTfr_Item;

typedef struct s1ap_ValueBrs_SubjToStatusTfr_ItemIEsCls{
	union {
		SztBrs_SubjToStatusTfr_Item sztBrs_SubjToStatusTfr_Item;
	} u;
} Szt_ValueBrs_SubjToStatusTfr_ItemIEsCls;
typedef struct s1apProtIE_Field_Brs_SubjToStatusTfr_ItemIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueBrs_SubjToStatusTfr_ItemIEsCls value;
} SztProtIE_Field_Brs_SubjToStatusTfr_ItemIEs;

/* Element ------------- ProtocolIE-SingleContainer ------------ */
typedef SztProtIE_Field_Brs_SubjToStatusTfr_ItemIEs SztProtIE_SingleCont_Brs_SubjToStatusTfr_ItemIEs;
typedef struct s1apBrs_SubjToStatusTfrLst
{
	TknU16 noComp;
	SztProtIE_SingleCont_Brs_SubjToStatusTfr_ItemIEs *member;
}SztBrs_SubjToStatusTfrLst;

/* Element ----- BitRate ------- */
typedef TknStrOSXL SztBitRate;

typedef struct s1apBPLMNs
{
	TknU16 noComp;
	SztPLMNidentity *member;
}SztBPLMNs;

/* Element ----- NumberOfBroadcasts ------- */
typedef TknU32 SztNumberOfBroadcasts;

typedef struct s1ap_ExtnCellID_Cancelled_Item_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnCellID_Cancelled_Item_ExtIEsCls;
typedef struct s1apProtExtnField_CellID_Cancelled_Item_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnCellID_Cancelled_Item_ExtIEsCls extensionValue;
} SztProtExtnField_CellID_Cancelled_Item_ExtIEs;

typedef struct s1apProtExtnCont_CellID_Cancelled_Item_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_CellID_Cancelled_Item_ExtIEs *member;
}SztProtExtnCont_CellID_Cancelled_Item_ExtIEs;

typedef struct s1apCellID_Cancelled_Item
{
	TknPres pres;
	SztEUTRAN_CGI eCGI;
	SztNumberOfBroadcasts numberOfBroadcasts;
	SztProtExtnCont_CellID_Cancelled_Item_ExtIEs iE_Extns;
} SztCellID_Cancelled_Item;

typedef struct s1apCellID_Cancelled
{
	TknU16 noComp;
	SztCellID_Cancelled_Item *member;
}SztCellID_Cancelled;

typedef struct s1ap_ExtnCancelledCellinTAI_Item_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnCancelledCellinTAI_Item_ExtIEsCls;
typedef struct s1apProtExtnField_CancelledCellinTAI_Item_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnCancelledCellinTAI_Item_ExtIEsCls extensionValue;
} SztProtExtnField_CancelledCellinTAI_Item_ExtIEs;

typedef struct s1apProtExtnCont_CancelledCellinTAI_Item_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_CancelledCellinTAI_Item_ExtIEs *member;
}SztProtExtnCont_CancelledCellinTAI_Item_ExtIEs;

typedef struct s1apCancelledCellinTAI_Item
{
	TknPres pres;
	SztEUTRAN_CGI eCGI;
	SztNumberOfBroadcasts numberOfBroadcasts;
	SztProtExtnCont_CancelledCellinTAI_Item_ExtIEs iE_Extns;
} SztCancelledCellinTAI_Item;

typedef struct s1apCancelledCellinTAI
{
	TknU16 noComp;
	SztCancelledCellinTAI_Item *member;
}SztCancelledCellinTAI;

typedef struct s1ap_ExtnTAI_Cancelled_Item_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnTAI_Cancelled_Item_ExtIEsCls;
typedef struct s1apProtExtnField_TAI_Cancelled_Item_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnTAI_Cancelled_Item_ExtIEsCls extensionValue;
} SztProtExtnField_TAI_Cancelled_Item_ExtIEs;

typedef struct s1apProtExtnCont_TAI_Cancelled_Item_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_TAI_Cancelled_Item_ExtIEs *member;
}SztProtExtnCont_TAI_Cancelled_Item_ExtIEs;

typedef struct s1apTAI_Cancelled_Item
{
	TknPres pres;
	SztTAI tAI;
	SztCancelledCellinTAI cancelledCellinTAI;
	SztProtExtnCont_TAI_Cancelled_Item_ExtIEs iE_Extns;
} SztTAI_Cancelled_Item;

typedef struct s1apTAI_Cancelled
{
	TknU16 noComp;
	SztTAI_Cancelled_Item *member;
}SztTAI_Cancelled;

/* Element ---------- EmergencyAreaID ----------- */
typedef TknStrOSXL SztEmergencyAreaID;
typedef struct s1ap_ExtnCancelledCellinEAI_Item_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnCancelledCellinEAI_Item_ExtIEsCls;
typedef struct s1apProtExtnField_CancelledCellinEAI_Item_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnCancelledCellinEAI_Item_ExtIEsCls extensionValue;
} SztProtExtnField_CancelledCellinEAI_Item_ExtIEs;

typedef struct s1apProtExtnCont_CancelledCellinEAI_Item_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_CancelledCellinEAI_Item_ExtIEs *member;
}SztProtExtnCont_CancelledCellinEAI_Item_ExtIEs;

typedef struct s1apCancelledCellinEAI_Item
{
	TknPres pres;
	SztEUTRAN_CGI eCGI;
	SztNumberOfBroadcasts numberOfBroadcasts;
	SztProtExtnCont_CancelledCellinEAI_Item_ExtIEs iE_Extns;
} SztCancelledCellinEAI_Item;

typedef struct s1apCancelledCellinEAI
{
	TknU16 noComp;
	SztCancelledCellinEAI_Item *member;
}SztCancelledCellinEAI;

typedef struct s1ap_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls;
typedef struct s1apProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls extensionValue;
} SztProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs;

typedef struct s1apProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs *member;
}SztProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs;

typedef struct s1apEmergencyAreaID_Cancelled_Item
{
	TknPres pres;
	SztEmergencyAreaID emergencyAreaID;
	SztCancelledCellinEAI cancelledCellinEAI;
	SztProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs iE_Extns;
} SztEmergencyAreaID_Cancelled_Item;

typedef struct s1apEmergencyAreaID_Cancelled
{
	TknU16 noComp;
	SztEmergencyAreaID_Cancelled_Item *member;
}SztEmergencyAreaID_Cancelled;

typedef struct s1apBroadcastCancelledAreaLst
{
	TknU8 choice;
	union {
		SztCellID_Cancelled cellID_Cancelled;
		SztTAI_Cancelled tAI_Cancelled;
		SztEmergencyAreaID_Cancelled emergencyAreaID_Cancelled;
	} val;
} SztBroadcastCancelledAreaLst;

typedef struct s1ap_ExtnCellID_Broadcast_Item_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnCellID_Broadcast_Item_ExtIEsCls;
typedef struct s1apProtExtnField_CellID_Broadcast_Item_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnCellID_Broadcast_Item_ExtIEsCls extensionValue;
} SztProtExtnField_CellID_Broadcast_Item_ExtIEs;

typedef struct s1apProtExtnCont_CellID_Broadcast_Item_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_CellID_Broadcast_Item_ExtIEs *member;
}SztProtExtnCont_CellID_Broadcast_Item_ExtIEs;

typedef struct s1apCellID_Broadcast_Item
{
	TknPres pres;
	SztEUTRAN_CGI eCGI;
	SztProtExtnCont_CellID_Broadcast_Item_ExtIEs iE_Extns;
} SztCellID_Broadcast_Item;

typedef struct s1apCellID_Broadcast
{
	TknU16 noComp;
	SztCellID_Broadcast_Item *member;
}SztCellID_Broadcast;

typedef struct s1ap_ExtnCompletedCellinTAI_Item_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnCompletedCellinTAI_Item_ExtIEsCls;
typedef struct s1apProtExtnField_CompletedCellinTAI_Item_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnCompletedCellinTAI_Item_ExtIEsCls extensionValue;
} SztProtExtnField_CompletedCellinTAI_Item_ExtIEs;

typedef struct s1apProtExtnCont_CompletedCellinTAI_Item_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_CompletedCellinTAI_Item_ExtIEs *member;
}SztProtExtnCont_CompletedCellinTAI_Item_ExtIEs;

typedef struct s1apCompletedCellinTAI_Item
{
	TknPres pres;
	SztEUTRAN_CGI eCGI;
	SztProtExtnCont_CompletedCellinTAI_Item_ExtIEs iE_Extns;
} SztCompletedCellinTAI_Item;

typedef struct s1apCompletedCellinTAI
{
	TknU16 noComp;
	SztCompletedCellinTAI_Item *member;
}SztCompletedCellinTAI;

typedef struct s1ap_ExtnTAI_Broadcast_Item_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnTAI_Broadcast_Item_ExtIEsCls;
typedef struct s1apProtExtnField_TAI_Broadcast_Item_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnTAI_Broadcast_Item_ExtIEsCls extensionValue;
} SztProtExtnField_TAI_Broadcast_Item_ExtIEs;

typedef struct s1apProtExtnCont_TAI_Broadcast_Item_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_TAI_Broadcast_Item_ExtIEs *member;
}SztProtExtnCont_TAI_Broadcast_Item_ExtIEs;

typedef struct s1apTAI_Broadcast_Item
{
	TknPres pres;
	SztTAI tAI;
	SztCompletedCellinTAI completedCellinTAI;
	SztProtExtnCont_TAI_Broadcast_Item_ExtIEs iE_Extns;
} SztTAI_Broadcast_Item;

typedef struct s1apTAI_Broadcast
{
	TknU16 noComp;
	SztTAI_Broadcast_Item *member;
}SztTAI_Broadcast;

typedef struct s1ap_ExtnCompletedCellinEAI_Item_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnCompletedCellinEAI_Item_ExtIEsCls;
typedef struct s1apProtExtnField_CompletedCellinEAI_Item_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnCompletedCellinEAI_Item_ExtIEsCls extensionValue;
} SztProtExtnField_CompletedCellinEAI_Item_ExtIEs;

typedef struct s1apProtExtnCont_CompletedCellinEAI_Item_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_CompletedCellinEAI_Item_ExtIEs *member;
}SztProtExtnCont_CompletedCellinEAI_Item_ExtIEs;

typedef struct s1apCompletedCellinEAI_Item
{
	TknPres pres;
	SztEUTRAN_CGI eCGI;
	SztProtExtnCont_CompletedCellinEAI_Item_ExtIEs iE_Extns;
} SztCompletedCellinEAI_Item;

typedef struct s1apCompletedCellinEAI
{
	TknU16 noComp;
	SztCompletedCellinEAI_Item *member;
}SztCompletedCellinEAI;

typedef struct s1ap_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls;
typedef struct s1apProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls extensionValue;
} SztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs;

typedef struct s1apProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs *member;
}SztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs;

typedef struct s1apEmergencyAreaID_Broadcast_Item
{
	TknPres pres;
	SztEmergencyAreaID emergencyAreaID;
	SztCompletedCellinEAI completedCellinEAI;
	SztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs iE_Extns;
} SztEmergencyAreaID_Broadcast_Item;

typedef struct s1apEmergencyAreaID_Broadcast
{
	TknU16 noComp;
	SztEmergencyAreaID_Broadcast_Item *member;
}SztEmergencyAreaID_Broadcast;

typedef struct s1apBroadcastCompletedAreaLst
{
	TknU8 choice;
	union {
		SztCellID_Broadcast cellID_Broadcast;
		SztTAI_Broadcast tAI_Broadcast;
		SztEmergencyAreaID_Broadcast emergencyAreaID_Broadcast;
	} val;
} SztBroadcastCompletedAreaLst;

/* Element ----- CauseRadioNetwork ------- */
typedef enum enumSztCauseRadioNw
{
	SztCauseRadioNwunspecifiedEnum,
	SztCauseRadioNwtx2relocoverall_expiryEnum,
	SztCauseRadioNwsuccessful_handoverEnum,
	SztCauseRadioNwrelease_due_to_eutran_generated_reasonEnum,
	SztCauseRadioNwhandover_cancelledEnum,
	SztCauseRadioNwpartial_handoverEnum,
	SztCauseRadioNwho_failure_in_target_EPC_eNB_or_target_systemEnum,
	SztCauseRadioNwho_target_not_allowedEnum,
	SztCauseRadioNwtS1relocoverall_expiryEnum,
	SztCauseRadioNwtS1relocprep_expiryEnum,
	SztCauseRadioNwcell_not_availableEnum,
	SztCauseRadioNwunknown_targetIDEnum,
	SztCauseRadioNwno_radio_resources_available_in_target_cellEnum,
	SztCauseRadioNwunknown_mme_ue_s1ap_idEnum,
	SztCauseRadioNwunknown_enb_ue_s1ap_idEnum,
	SztCauseRadioNwunknown_pair_ue_s1ap_idEnum,
	SztCauseRadioNwhandover_desirable_for_radio_reasonEnum,
	SztCauseRadioNwtime_critical_handoverEnum,
	SztCauseRadioNwresource_optimisation_handoverEnum,
	SztCauseRadioNwreduce_load_in_serving_cellEnum,
	SztCauseRadioNwuser_inactivityEnum,
	SztCauseRadioNwradio_connection_with_ue_lostEnum,
	SztCauseRadioNwload_balancing_tau_requiredEnum,
	SztCauseRadioNwcs_fallback_triggeredEnum,
	SztCauseRadioNwue_not_available_for_ps_serviceEnum,
	SztCauseRadioNwradio_resources_not_availableEnum,
	SztCauseRadioNwfailure_in_radio_interface_procedureEnum,
	SztCauseRadioNwinvalid_qos_combinationEnum,
	SztCauseRadioNwinterrat_redirectionEnum,
	SztCauseRadioNwinteraction_with_other_procedureEnum,
	SztCauseRadioNwunknown_E_RAB_IDEnum,
	SztCauseRadioNwmultiple_E_RAB_ID_instancesEnum,
	SztCauseRadioNwencryption_and_or_integrity_protection_algorithms_not_supportedEnum,
	SztCauseRadioNws1_intra_system_handover_triggeredEnum,
	SztCauseRadioNws1_inter_system_handover_triggeredEnum,
	SztCauseRadioNwx2_handover_triggeredEnum,
	SztCauseRadioNwredirection_towards_1xRTTEnum,
	SztCauseRadioNwnot_supported_QCI_valueEnum,
	SztCauseRadioNwinvalid_CSG_IdEnum
} EnumSztCauseRadioNw;
typedef TknU32 SztCauseRadioNw;

/* Element ----- CauseTransport ------- */
typedef enum enumSztCauseTport
{
	SztCauseTporttransport_resource_unavailableEnum,
	SztCauseTportunspecifiedEnum
} EnumSztCauseTport;
typedef TknU32 SztCauseTport;

/* Element ----- CauseNas ------- */
typedef enum enumSztCauseNas
{
	SztCauseNasnormal_releaseEnum,
	SztCauseNasauthentication_failureEnum,
	SztCauseNasdetachEnum,
	SztCauseNasunspecifiedEnum,
	SztCauseNascsg_subscription_expiryEnum
} EnumSztCauseNas;
typedef TknU32 SztCauseNas;

/* Element ----- CauseProtocol ------- */
typedef enum enumSztCauseProt
{
	SztCauseProttransfer_syntax_errorEnum,
	SztCauseProtabstract_syntax_error_rejectEnum,
	SztCauseProtabstract_syntax_error_ignore_and_notifyEnum,
	SztCauseProtmessage_not_compatible_with_receiver_stateEnum,
	SztCauseProtsemantic_errorEnum,
	SztCauseProtabstract_syntax_error_falsely_constructed_messageEnum,
	SztCauseProtunspecifiedEnum
} EnumSztCauseProt;
typedef TknU32 SztCauseProt;

/* Element ----- CauseMisc ------- */
typedef enum enumSztCauseMisc
{
	SztCauseMisccontrol_processing_overloadEnum,
	SztCauseMiscnot_enough_user_plane_processing_resourcesEnum,
	SztCauseMischardware_failureEnum,
	SztCauseMiscom_interventionEnum,
	SztCauseMiscunspecifiedEnum,
	SztCauseMiscunknown_PLMNEnum
} EnumSztCauseMisc;
typedef TknU32 SztCauseMisc;

typedef struct s1apCause
{
	TknU8 choice;
	union {
		SztCauseRadioNw radioNw;
		SztCauseTport transport;
		SztCauseNas nas;
		SztCauseProt protocol;
		SztCauseMisc misc;
	} val;
} SztCause;

/* Element ----- CellAccessMode ------- */
typedef enum enumSztCellAccessMode
{
	SztCellAccessModehybridEnum
} EnumSztCellAccessMode;
typedef TknU32 SztCellAccessMode;

/* Element ---------- Cdma2000PDU ----------- */
typedef TknStrOSXL SztCdma2000PDU;
/* Element ----- Cdma2000RATType ------- */
typedef enum enumSztCdma2000RATTyp
{
	SztCdma2000RATTyphRPDEnum,
	SztCdma2000RATTyponexRTTEnum
} EnumSztCdma2000RATTyp;
typedef TknU32 SztCdma2000RATTyp;

/* Element ---------- Cdma2000SectorID ----------- */
typedef TknStrOSXL SztCdma2000SectorID;
/* Element ----- Cdma2000HOStatus ------- */
typedef enum enumSztCdma2000HOStatus
{
	SztCdma2000HOStatushOSuccessEnum,
	SztCdma2000HOStatushOFailEnum
} EnumSztCdma2000HOStatus;
typedef TknU32 SztCdma2000HOStatus;

/* Element ----- Cdma2000HORequiredIndication ------- */
typedef enum enumSztCdma2000HOReqdInd
{
	SztCdma2000HOReqdIndtrueEnum
} EnumSztCdma2000HOReqdInd;
typedef TknU32 SztCdma2000HOReqdInd;

/* Element ---------- Cdma2000OneXMEID ----------- */
typedef TknStrOSXL SztCdma2000OneXMEID;
/* Element ---------- Cdma2000OneXMSI ----------- */
typedef TknStrOSXL SztCdma2000OneXMSI;
/* Element ---------- Cdma2000OneXPilot ----------- */
typedef TknStrOSXL SztCdma2000OneXPilot;
typedef struct s1ap_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls;
typedef struct s1apProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls extensionValue;
} SztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs;

typedef struct s1apProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs *member;
}SztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs;

typedef struct s1apCdma2000OneXSRVCCInfo
{
	TknPres pres;
	SztCdma2000OneXMEID cdma2000OneXMEID;
	SztCdma2000OneXMSI cdma2000OneXMSI;
	SztCdma2000OneXPilot cdma2000OneXPilot;
	SztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs iE_Extns;
} SztCdma2000OneXSRVCCInfo;

/* Element ---------- Cdma2000OneXRAND ----------- */
typedef TknStrOSXL SztCdma2000OneXRAND;
/* Element ----- Cell-Size ------- */
typedef enum enumSztCell_Size
{
	SztCell_SizeverysmallEnum,
	SztCell_SizesmallEnum,
	SztCell_SizemediumEnum,
	SztCell_SizelargeEnum
} EnumSztCell_Size;
typedef TknU32 SztCell_Size;

typedef struct s1ap_ExtnCellTyp_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnCellTyp_ExtIEsCls;
typedef struct s1apProtExtnField_CellTyp_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnCellTyp_ExtIEsCls extensionValue;
} SztProtExtnField_CellTyp_ExtIEs;

typedef struct s1apProtExtnCont_CellTyp_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_CellTyp_ExtIEs *member;
}SztProtExtnCont_CellTyp_ExtIEs;

typedef struct s1apCellTyp
{
	TknPres pres;
	SztCell_Size cell_Size;
	SztProtExtnCont_CellTyp_ExtIEs iE_Extns;
} SztCellTyp;

/* Element ---------- LAC ----------- */
typedef TknStr4 SztLAC;
/* Element ---------- CI ----------- */
typedef TknStr4 SztCI;
/* Element ---------- RAC ----------- */
typedef TknStr4 SztRAC;
typedef struct s1ap_ExtnCGI_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnCGI_ExtIEsCls;
typedef struct s1apProtExtnField_CGI_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnCGI_ExtIEsCls extensionValue;
} SztProtExtnField_CGI_ExtIEs;

typedef struct s1apProtExtnCont_CGI_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_CGI_ExtIEs *member;
}SztProtExtnCont_CGI_ExtIEs;

typedef struct s1apCGI
{
	TknPres pres;
	SztPLMNidentity pLMNidentity;
	SztLAC lAC;
	SztCI cI;
	SztRAC rAC;
	SztProtExtnCont_CGI_ExtIEs iE_Extns;
} SztCGI;

/* Element ----- CNDomain ------- */
typedef enum enumSztCNDomain
{
	SztCNDomainpsEnum,
	SztCNDomaincsEnum
} EnumSztCNDomain;
typedef TknU32 SztCNDomain;

/* Element ----- ConcurrentWarningMessageIndicator ------- */
typedef enum enumSztConcurrentWarningMsgIndicator
{
	SztConcurrentWarningMsgIndicatortrueEnum
} EnumSztConcurrentWarningMsgIndicator;
typedef TknU32 SztConcurrentWarningMsgIndicator;

/* Element ---------- Correlation-ID ----------- */
typedef TknStrOSXL SztCorrelation_ID;
/* Element ----- CSFallbackIndicator ------- */
typedef enum enumSztCSFallbackIndicator
{
	SztCSFallbackIndicatorcs_fallback_requiredEnum,
	SztCSFallbackIndicatorcs_fallback_high_priorityEnum
} EnumSztCSFallbackIndicator;
typedef TknU32 SztCSFallbackIndicator;

/* Element ---------- CSG-Id ----------- */
typedef TknBStr32 SztCSG_Id;
typedef struct s1ap_ExtnCSG_IdLst_Item_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnCSG_IdLst_Item_ExtIEsCls;
typedef struct s1apProtExtnField_CSG_IdLst_Item_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnCSG_IdLst_Item_ExtIEsCls extensionValue;
} SztProtExtnField_CSG_IdLst_Item_ExtIEs;

typedef struct s1apProtExtnCont_CSG_IdLst_Item_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_CSG_IdLst_Item_ExtIEs *member;
}SztProtExtnCont_CSG_IdLst_Item_ExtIEs;

typedef struct s1apCSG_IdLst_Item
{
	TknPres pres;
	SztCSG_Id cSG_Id;
	SztProtExtnCont_CSG_IdLst_Item_ExtIEs iE_Extns;
} SztCSG_IdLst_Item;

typedef struct s1apCSG_IdLst
{
	TknU16 noComp;
	SztCSG_IdLst_Item *member;
}SztCSG_IdLst;

/* Element ----- CSGMembershipStatus ------- */
typedef enum enumSztCSGMembershipStatus
{
	SztCSGMembershipStatusmemberEnum,
	SztCSGMembershipStatusnot_memberEnum
} EnumSztCSGMembershipStatus;
typedef TknU32 SztCSGMembershipStatus;

/* Element ----- TypeOfError ------- */
typedef enum enumSztTypOfErr
{
	SztTypOfErrnot_understoodEnum,
	SztTypOfErrmissingEnum
} EnumSztTypOfErr;
typedef TknU32 SztTypOfErr;

typedef struct s1ap_ExtnCriticalityDiag_IE_Item_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnCriticalityDiag_IE_Item_ExtIEsCls;
typedef struct s1apProtExtnField_CriticalityDiag_IE_Item_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnCriticalityDiag_IE_Item_ExtIEsCls extensionValue;
} SztProtExtnField_CriticalityDiag_IE_Item_ExtIEs;

typedef struct s1apProtExtnCont_CriticalityDiag_IE_Item_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_CriticalityDiag_IE_Item_ExtIEs *member;
}SztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs;

typedef struct s1apCriticalityDiag_IE_Item
{
	TknPres pres;
	SztCriticality iECriticality;
	SztProtIE_ID iE_ID;
	SztTypOfErr typeOfErr;
	SztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs iE_Extns;
} SztCriticalityDiag_IE_Item;

typedef struct s1apCriticalityDiag_IE_Lst
{
	TknU16 noComp;
	SztCriticalityDiag_IE_Item *member;
}SztCriticalityDiag_IE_Lst;

typedef struct s1ap_ExtnCriticalityDiag_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnCriticalityDiag_ExtIEsCls;
typedef struct s1apProtExtnField_CriticalityDiag_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnCriticalityDiag_ExtIEsCls extensionValue;
} SztProtExtnField_CriticalityDiag_ExtIEs;

typedef struct s1apProtExtnCont_CriticalityDiag_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_CriticalityDiag_ExtIEs *member;
}SztProtExtnCont_CriticalityDiag_ExtIEs;

typedef struct s1apCriticalityDiag
{
	TknPres pres;
	SztProcedureCode procedureCode;
	SztTrgMsg triggeringMsg;
	SztCriticality procedureCriticality;
	SztCriticalityDiag_IE_Lst iEsCriticalityDiag;
	SztProtExtnCont_CriticalityDiag_ExtIEs iE_Extns;
} SztCriticalityDiag;

/* Element ---------- DataCodingScheme ----------- */
typedef TknBStr32 SztDataCodingScheme;
/* Element ----- DL-Forwarding ------- */
typedef enum enumSztDL_Fwding
{
	SztDL_FwdingdL_Fwding_proposedEnum
} EnumSztDL_Fwding;
typedef TknU32 SztDL_Fwding;

/* Element ----- Direct-Forwarding-Path-Availability ------- */
typedef enum enumSztDirect_Fwding_Path_Avlblty
{
	SztDirect_Fwding_Path_AvlbltydirectPathAvailableEnum
} EnumSztDirect_Fwding_Path_Avlblty;
typedef TknU32 SztDirect_Fwding_Path_Avlblty;

/* Element ----- Data-Forwarding-Not-Possible ------- */
typedef enum enumSztData_Fwding_Not_Possible
{
	SztData_Fwding_Not_Possibledata_Fwding_not_PossibleEnum
} EnumSztData_Fwding_Not_Possible;
typedef TknU32 SztData_Fwding_Not_Possible;

typedef struct s1apECGILst
{
	TknU16 noComp;
	SztEUTRAN_CGI *member;
}SztECGILst;

typedef struct s1apEmergencyAreaIDLst
{
	TknU16 noComp;
	SztEmergencyAreaID *member;
}SztEmergencyAreaIDLst;

/* Element ---------- macroENB-ID ----------- */
typedef TknBStr32 SztENB_IDmacroENB_ID;
/* Element ---------- homeENB-ID ----------- */
typedef TknBStr32 SztENB_IDhomeENB_ID;
typedef struct s1apENB_ID
{
	TknU8 choice;
	union {
		SztENB_IDmacroENB_ID macroENB_ID;
		SztENB_IDhomeENB_ID homeENB_ID;
	} val;
} SztENB_ID;

typedef struct s1ap_ExtnLAI_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnLAI_ExtIEsCls;
typedef struct s1apProtExtnField_LAI_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnLAI_ExtIEsCls extensionValue;
} SztProtExtnField_LAI_ExtIEs;

typedef struct s1apProtExtnCont_LAI_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_LAI_ExtIEs *member;
}SztProtExtnCont_LAI_ExtIEs;

typedef struct s1apLAI
{
	TknPres pres;
	SztPLMNidentity pLMNidentity;
	SztLAC lAC;
	SztProtExtnCont_LAI_ExtIEs iE_Extns;
} SztLAI;

typedef struct s1ap_ExtnGERAN_Cell_ID_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnGERAN_Cell_ID_ExtIEsCls;
typedef struct s1apProtExtnField_GERAN_Cell_ID_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnGERAN_Cell_ID_ExtIEsCls extensionValue;
} SztProtExtnField_GERAN_Cell_ID_ExtIEs;

typedef struct s1apProtExtnCont_GERAN_Cell_ID_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_GERAN_Cell_ID_ExtIEs *member;
}SztProtExtnCont_GERAN_Cell_ID_ExtIEs;

typedef struct s1apGERAN_Cell_ID
{
	TknPres pres;
	SztLAI lAI;
	SztRAC rAC;
	SztCI cI;
	SztProtExtnCont_GERAN_Cell_ID_ExtIEs iE_Extns;
} SztGERAN_Cell_ID;

typedef struct s1ap_ExtnGlobalENB_ID_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnGlobalENB_ID_ExtIEsCls;
typedef struct s1apProtExtnField_GlobalENB_ID_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnGlobalENB_ID_ExtIEsCls extensionValue;
} SztProtExtnField_GlobalENB_ID_ExtIEs;

typedef struct s1apProtExtnCont_GlobalENB_ID_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_GlobalENB_ID_ExtIEs *member;
}SztProtExtnCont_GlobalENB_ID_ExtIEs;

typedef struct s1apGlobal_ENB_ID
{
	TknPres pres;
	SztPLMNidentity pLMNidentity;
	SztENB_ID eNB_ID;
	SztProtExtnCont_GlobalENB_ID_ExtIEs iE_Extns;
} SztGlobal_ENB_ID;

/* Element ---------- MME-Group-ID ----------- */
typedef TknStr4 SztMME_Group_ID;
/* Element ---------- MME-Code ----------- */
typedef TknStr4 SztMME_Code;
typedef struct s1ap_ExtnGUMMEI_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnGUMMEI_ExtIEsCls;
typedef struct s1apProtExtnField_GUMMEI_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnGUMMEI_ExtIEsCls extensionValue;
} SztProtExtnField_GUMMEI_ExtIEs;

typedef struct s1apProtExtnCont_GUMMEI_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_GUMMEI_ExtIEs *member;
}SztProtExtnCont_GUMMEI_ExtIEs;

typedef struct s1apGUMMEI
{
	TknPres pres;
	SztPLMNidentity pLMN_Identity;
	SztMME_Group_ID mME_Group_ID;
	SztMME_Code mME_Code;
	SztProtExtnCont_GUMMEI_ExtIEs iE_Extns;
} SztGUMMEI;

typedef struct s1apGUMMEILst
{
	TknU16 noComp;
	SztGUMMEI *member;
}SztGUMMEILst;

typedef struct s1ap_ExtnENB_StatusTfr_TprntCont_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls;
typedef struct s1apProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls extensionValue;
} SztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs;

typedef struct s1apProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs *member;
}SztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs;

typedef struct s1apENB_StatusTfr_TprntCont
{
	TknPres pres;
	SztBrs_SubjToStatusTfrLst bearers_SubjToStatusTfrLst;
	SztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs iE_Extns;
} SztENB_StatusTfr_TprntCont;

/* Element ----- ENB-UE-S1AP-ID ------- */
typedef TknU32 SztENB_UE_S1AP_ID;

/* Element ---------- ENBname ----------- */
typedef TknStrOSXL SztENBname;
/* Element ---------- TransportLayerAddress ----------- */
typedef TknStrBSXL SztTportLyrAddr;
typedef struct s1apENBX2TLAs
{
	TknU16 noComp;
	SztTportLyrAddr *member;
}SztENBX2TLAs;

/* Element ---------- EncryptionAlgorithms ----------- */
typedef TknBStr32 SztEncryptionAlgorithms;
typedef struct s1apEPLMNs
{
	TknU16 noComp;
	SztPLMNidentity *member;
}SztEPLMNs;

/* Element ----- EventType ------- */
typedef enum enumSztEventTyp
{
	SztEventTypdirectEnum,
	SztEventTypchange_of_serve_cellEnum,
	SztEventTypstop_change_of_serve_cellEnum
} EnumSztEventTyp;
typedef TknU32 SztEventTyp;

typedef struct s1ap_ExtnE_RABInformLstItem_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnE_RABInformLstItem_ExtIEsCls;
typedef struct s1apProtExtnField_E_RABInformLstItem_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnE_RABInformLstItem_ExtIEsCls extensionValue;
} SztProtExtnField_E_RABInformLstItem_ExtIEs;

typedef struct s1apProtExtnCont_E_RABInformLstItem_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_E_RABInformLstItem_ExtIEs *member;
}SztProtExtnCont_E_RABInformLstItem_ExtIEs;

typedef struct s1apE_RABInformLstItem
{
	TknPres pres;
	SztE_RAB_ID e_RAB_ID;
	SztDL_Fwding dL_Fwding;
	SztProtExtnCont_E_RABInformLstItem_ExtIEs iE_Extns;
} SztE_RABInformLstItem;

typedef struct s1ap_ValueE_RABInformLstIEsCls{
	union {
		SztE_RABInformLstItem sztE_RABInformLstItem;
	} u;
} Szt_ValueE_RABInformLstIEsCls;
typedef struct s1apProtIE_Field_E_RABInformLstIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueE_RABInformLstIEsCls value;
} SztProtIE_Field_E_RABInformLstIEs;

/* Element ------------- ProtocolIE-SingleContainer ------------ */
typedef SztProtIE_Field_E_RABInformLstIEs SztProtIE_SingleCont_E_RABInformLstIEs;
typedef struct s1apE_RABInformLst
{
	TknU16 noComp;
	SztProtIE_SingleCont_E_RABInformLstIEs *member;
}SztE_RABInformLst;

typedef struct s1ap_ExtnE_RABItem_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnE_RABItem_ExtIEsCls;
typedef struct s1apProtExtnField_E_RABItem_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnE_RABItem_ExtIEsCls extensionValue;
} SztProtExtnField_E_RABItem_ExtIEs;

typedef struct s1apProtExtnCont_E_RABItem_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_E_RABItem_ExtIEs *member;
}SztProtExtnCont_E_RABItem_ExtIEs;

typedef struct s1apE_RABItem
{
	TknPres pres;
	SztE_RAB_ID e_RAB_ID;
	SztCause cause;
	SztProtExtnCont_E_RABItem_ExtIEs iE_Extns;
} SztE_RABItem;

typedef struct s1ap_ValueE_RABItemIEsCls{
	union {
		SztE_RABItem sztE_RABItem;
	} u;
} Szt_ValueE_RABItemIEsCls;
typedef struct s1apProtIE_Field_E_RABItemIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueE_RABItemIEsCls value;
} SztProtIE_Field_E_RABItemIEs;

/* Element ------------- ProtocolIE-SingleContainer ------------ */
typedef SztProtIE_Field_E_RABItemIEs SztProtIE_SingleCont_E_RABItemIEs;
typedef struct s1apE_RABLst
{
	TknU16 noComp;
	SztProtIE_SingleCont_E_RABItemIEs *member;
}SztE_RABLst;

/* Element ----- QCI ------- */
typedef TknU32 SztQCI;

typedef struct s1ap_ExtnGBR_QosInform_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnGBR_QosInform_ExtIEsCls;
typedef struct s1apProtExtnField_GBR_QosInform_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnGBR_QosInform_ExtIEsCls extensionValue;
} SztProtExtnField_GBR_QosInform_ExtIEs;

typedef struct s1apProtExtnCont_GBR_QosInform_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_GBR_QosInform_ExtIEs *member;
}SztProtExtnCont_GBR_QosInform_ExtIEs;

typedef struct s1apGBR_QosInform
{
	TknPres pres;
	SztBitRate e_RAB_MaxBitrateDL;
	SztBitRate e_RAB_MaxBitrateUL;
	SztBitRate e_RAB_GuaranteedBitrateDL;
	SztBitRate e_RAB_GuaranteedBitrateUL;
	SztProtExtnCont_GBR_QosInform_ExtIEs iE_Extns;
} SztGBR_QosInform;

typedef struct s1ap_ExtnE_RABQoSParams_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnE_RABQoSParams_ExtIEsCls;
typedef struct s1apProtExtnField_E_RABQoSParams_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnE_RABQoSParams_ExtIEsCls extensionValue;
} SztProtExtnField_E_RABQoSParams_ExtIEs;

typedef struct s1apProtExtnCont_E_RABQoSParams_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_E_RABQoSParams_ExtIEs *member;
}SztProtExtnCont_E_RABQoSParams_ExtIEs;

typedef struct s1apE_RABLvlQoSParams
{
	TknPres pres;
	SztQCI qCI;
	SztAllocnAndRetentionPriority allocationRetentionPriority;
	SztGBR_QosInform gbrQosInform;
	SztProtExtnCont_E_RABQoSParams_ExtIEs iE_Extns;
} SztE_RABLvlQoSParams;

/* Element ----- EUTRANRoundTripDelayEstimationInfo ------- */
typedef TknU32 SztEUTRANRoundTripDelayEstimationInfo;

/* Element ----- ExtendedRNC-ID ------- */
typedef TknU32 SztExtendedRNC_ID;

/* Element ----- ExtendedRepetitionPeriod ------- */
typedef TknU32 SztExtendedRepetitionPeriod;

/* Element ----- ForbiddenInterRATs ------- */
typedef enum enumSztForbiddenInterRATs
{
	SztForbiddenInterRATsallEnum,
	SztForbiddenInterRATsgeranEnum,
	SztForbiddenInterRATsutranEnum,
	SztForbiddenInterRATscdma2000Enum,
	SztForbiddenInterRATsgeranandutranEnum,
	SztForbiddenInterRATscdma2000andutranEnum
} EnumSztForbiddenInterRATs;
typedef TknU32 SztForbiddenInterRATs;

typedef struct s1apForbiddenTACs
{
	TknU16 noComp;
	SztTAC *member;
}SztForbiddenTACs;

typedef struct s1ap_ExtnForbiddenTAs_Item_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnForbiddenTAs_Item_ExtIEsCls;
typedef struct s1apProtExtnField_ForbiddenTAs_Item_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnForbiddenTAs_Item_ExtIEsCls extensionValue;
} SztProtExtnField_ForbiddenTAs_Item_ExtIEs;

typedef struct s1apProtExtnCont_ForbiddenTAs_Item_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_ForbiddenTAs_Item_ExtIEs *member;
}SztProtExtnCont_ForbiddenTAs_Item_ExtIEs;

typedef struct s1apForbiddenTAs_Item
{
	TknPres pres;
	SztPLMNidentity pLMN_Identity;
	SztForbiddenTACs forbiddenTACs;
	SztProtExtnCont_ForbiddenTAs_Item_ExtIEs iE_Extns;
} SztForbiddenTAs_Item;

typedef struct s1apForbiddenTAs
{
	TknU16 noComp;
	SztForbiddenTAs_Item *member;
}SztForbiddenTAs;

typedef struct s1apForbiddenLACs
{
	TknU16 noComp;
	SztLAC *member;
}SztForbiddenLACs;

typedef struct s1ap_ExtnForbiddenLAs_Item_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnForbiddenLAs_Item_ExtIEsCls;
typedef struct s1apProtExtnField_ForbiddenLAs_Item_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnForbiddenLAs_Item_ExtIEsCls extensionValue;
} SztProtExtnField_ForbiddenLAs_Item_ExtIEs;

typedef struct s1apProtExtnCont_ForbiddenLAs_Item_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_ForbiddenLAs_Item_ExtIEs *member;
}SztProtExtnCont_ForbiddenLAs_Item_ExtIEs;

typedef struct s1apForbiddenLAs_Item
{
	TknPres pres;
	SztPLMNidentity pLMN_Identity;
	SztForbiddenLACs forbiddenLACs;
	SztProtExtnCont_ForbiddenLAs_Item_ExtIEs iE_Extns;
} SztForbiddenLAs_Item;

typedef struct s1apForbiddenLAs
{
	TknU16 noComp;
	SztForbiddenLAs_Item *member;
}SztForbiddenLAs;

/* Element ---------- GTP-TEID ----------- */
typedef TknStrOSXL SztGTP_TEID;
/* Element ----- GUMMEIType ------- */
typedef enum enumSztGUMMEITyp
{
	SztGUMMEITypnativeEnum,
	SztGUMMEITypmappedEnum
} EnumSztGUMMEITyp;
typedef TknU32 SztGUMMEITyp;

/* Element ----- GWContextReleaseIndication ------- */
typedef enum enumSztGWCntxtRlsInd
{
	SztGWCntxtRlsIndtrueEnum
} EnumSztGWCntxtRlsInd;
typedef TknU32 SztGWCntxtRlsInd;

typedef struct s1ap_ExtnHovrRestrnLst_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnHovrRestrnLst_ExtIEsCls;
typedef struct s1apProtExtnField_HovrRestrnLst_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnHovrRestrnLst_ExtIEsCls extensionValue;
} SztProtExtnField_HovrRestrnLst_ExtIEs;

typedef struct s1apProtExtnCont_HovrRestrnLst_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_HovrRestrnLst_ExtIEs *member;
}SztProtExtnCont_HovrRestrnLst_ExtIEs;

typedef struct s1apHovrRestrnLst
{
	TknPres pres;
	SztPLMNidentity servingPLMN;
	SztEPLMNs equivalentPLMNs;
	SztForbiddenTAs forbiddenTAs;
	SztForbiddenLAs forbiddenLAs;
	SztForbiddenInterRATs forbiddenInterRATs;
	SztProtExtnCont_HovrRestrnLst_ExtIEs iE_Extns;
} SztHovrRestrnLst;

/* Element ----- HandoverType ------- */
typedef enum enumSztHovrTyp
{
	SztHovrTypintralteEnum,
	SztHovrTypltetoutranEnum,
	SztHovrTypltetogeranEnum,
	SztHovrTyputrantolteEnum,
	SztHovrTypgerantolteEnum
} EnumSztHovrTyp;
typedef TknU32 SztHovrTyp;

/* Element ---------- MeasurementsToActivate ----------- */
typedef TknBStr32 SztMeasurementsToActivate;
/* Element ----- M1ReportingTrigger ------- */
typedef enum enumSztM1RprtngTrigger
{
	SztM1RprtngTriggerperiodicEnum,
	SztM1RprtngTriggera2eventtriggeredEnum,
	SztM1RprtngTriggera2eventtriggered_periodicEnum
} EnumSztM1RprtngTrigger;
typedef TknU32 SztM1RprtngTrigger;

/* Element ----- Threshold-RSRP ------- */
typedef TknU32 SztThreshold_RSRP;

/* Element ----- Threshold-RSRQ ------- */
typedef TknU32 SztThreshold_RSRQ;

typedef struct s1apMeasurementThresholdA2
{
	TknU8 choice;
	union {
		SztThreshold_RSRP threshold_RSRP;
		SztThreshold_RSRQ threshold_RSRQ;
	} val;
} SztMeasurementThresholdA2;

typedef struct s1ap_ExtnM1ThresholdEventA2_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnM1ThresholdEventA2_ExtIEsCls;
typedef struct s1apProtExtnField_M1ThresholdEventA2_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnM1ThresholdEventA2_ExtIEsCls extensionValue;
} SztProtExtnField_M1ThresholdEventA2_ExtIEs;

typedef struct s1apProtExtnCont_M1ThresholdEventA2_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_M1ThresholdEventA2_ExtIEs *member;
}SztProtExtnCont_M1ThresholdEventA2_ExtIEs;

typedef struct s1apM1ThresholdEventA2
{
	TknPres pres;
	SztMeasurementThresholdA2 measurementThreshold;
	SztProtExtnCont_M1ThresholdEventA2_ExtIEs iE_Extns;
} SztM1ThresholdEventA2;

/* Element ----- ReportIntervalMDT ------- */
typedef enum enumSztReportIntervalMDT
{
	SztReportIntervalMDTms120Enum,
	SztReportIntervalMDTms240Enum,
	SztReportIntervalMDTms480Enum,
	SztReportIntervalMDTms640Enum,
	SztReportIntervalMDTms1024Enum,
	SztReportIntervalMDTms2048Enum,
	SztReportIntervalMDTms5120Enum,
	SztReportIntervalMDTms10240Enum,
	SztReportIntervalMDTmin1Enum,
	SztReportIntervalMDTmin6Enum,
	SztReportIntervalMDTmin12Enum,
	SztReportIntervalMDTmin30Enum,
	SztReportIntervalMDTmin60Enum
} EnumSztReportIntervalMDT;
typedef TknU32 SztReportIntervalMDT;

/* Element ----- ReportAmountMDT ------- */
typedef enum enumSztReportAmountMDT
{
	SztReportAmountMDTr1Enum,
	SztReportAmountMDTr2Enum,
	SztReportAmountMDTr4Enum,
	SztReportAmountMDTr8Enum,
	SztReportAmountMDTr16Enum,
	SztReportAmountMDTr32Enum,
	SztReportAmountMDTr64Enum,
	SztReportAmountMDTrinfinityEnum
} EnumSztReportAmountMDT;
typedef TknU32 SztReportAmountMDT;

typedef struct s1ap_ExtnM1PeriodicRprtng_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnM1PeriodicRprtng_ExtIEsCls;
typedef struct s1apProtExtnField_M1PeriodicRprtng_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnM1PeriodicRprtng_ExtIEsCls extensionValue;
} SztProtExtnField_M1PeriodicRprtng_ExtIEs;

typedef struct s1apProtExtnCont_M1PeriodicRprtng_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_M1PeriodicRprtng_ExtIEs *member;
}SztProtExtnCont_M1PeriodicRprtng_ExtIEs;

typedef struct s1apM1PeriodicRprtng
{
	TknPres pres;
	SztReportIntervalMDT reportInterval;
	SztReportAmountMDT reportAmount;
	SztProtExtnCont_M1PeriodicRprtng_ExtIEs iE_Extns;
} SztM1PeriodicRprtng;

/* Element ----- M3period ------- */
typedef enum enumSztM3period
{
	SztM3periodms100Enum,
	SztM3periodms1000Enum,
	SztM3periodms10000Enum
} EnumSztM3period;
typedef TknU32 SztM3period;

typedef struct s1ap_ExtnM3Config_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnM3Config_ExtIEsCls;
typedef struct s1apProtExtnField_M3Config_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnM3Config_ExtIEsCls extensionValue;
} SztProtExtnField_M3Config_ExtIEs;

typedef struct s1apProtExtnCont_M3Config_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_M3Config_ExtIEs *member;
}SztProtExtnCont_M3Config_ExtIEs;

typedef struct s1apM3Config
{
	TknPres pres;
	SztM3period m3period;
	SztProtExtnCont_M3Config_ExtIEs iE_Extns;
} SztM3Config;

/* Element ----- M4period ------- */
typedef enum enumSztM4period
{
	SztM4periodms1024Enum,
	SztM4periodms2048Enum,
	SztM4periodms5120Enum,
	SztM4periodms10240Enum,
	SztM4periodmin1Enum
} EnumSztM4period;
typedef TknU32 SztM4period;

/* Element ----- Links-to-log ------- */
typedef enum enumSztLinks_to_log
{
	SztLinks_to_loguplinkEnum,
	SztLinks_to_logdownlinkEnum,
	SztLinks_to_logboth_uplink_and_downlinkEnum
} EnumSztLinks_to_log;
typedef TknU32 SztLinks_to_log;

typedef struct s1ap_ExtnM4Config_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnM4Config_ExtIEsCls;
typedef struct s1apProtExtnField_M4Config_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnM4Config_ExtIEsCls extensionValue;
} SztProtExtnField_M4Config_ExtIEs;

typedef struct s1apProtExtnCont_M4Config_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_M4Config_ExtIEs *member;
}SztProtExtnCont_M4Config_ExtIEs;

typedef struct s1apM4Config
{
	TknPres pres;
	SztM4period m4period;
	SztLinks_to_log m4_links_to_log;
	SztProtExtnCont_M4Config_ExtIEs iE_Extns;
} SztM4Config;

/* Element ----- M5period ------- */
typedef enum enumSztM5period
{
	SztM5periodms1024Enum,
	SztM5periodms2048Enum,
	SztM5periodms5120Enum,
	SztM5periodms10240Enum,
	SztM5periodmin1Enum
} EnumSztM5period;
typedef TknU32 SztM5period;

typedef struct s1ap_ExtnM5Config_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnM5Config_ExtIEsCls;
typedef struct s1apProtExtnField_M5Config_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnM5Config_ExtIEsCls extensionValue;
} SztProtExtnField_M5Config_ExtIEs;

typedef struct s1apProtExtnCont_M5Config_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_M5Config_ExtIEs *member;
}SztProtExtnCont_M5Config_ExtIEs;

typedef struct s1apM5Config
{
	TknPres pres;
	SztM5period m5period;
	SztLinks_to_log m5_links_to_log;
	SztProtExtnCont_M5Config_ExtIEs iE_Extns;
} SztM5Config;

/* Element ---------- MDT-Location-Info ----------- */
typedef TknBStr32 SztMDT_Loc_Info;
typedef struct s1ap_ExtnImmediateMDT_ExtIEsCls{
	union {
		SztM3Config sztM3Config;
		SztM4Config sztM4Config;
		SztM5Config sztM5Config;
		SztMDT_Loc_Info sztMDT_Loc_Info;
	} u;
} Szt_ExtnImmediateMDT_ExtIEsCls;
typedef struct s1apProtExtnField_ImmediateMDT_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnImmediateMDT_ExtIEsCls extensionValue;
} SztProtExtnField_ImmediateMDT_ExtIEs;

typedef struct s1apProtExtnCont_ImmediateMDT_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_ImmediateMDT_ExtIEs *member;
}SztProtExtnCont_ImmediateMDT_ExtIEs;

typedef struct s1apImmediateMDT
{
	TknPres pres;
	SztMeasurementsToActivate measurementsToActivate;
	SztM1RprtngTrigger m1reportingTrigger;
	SztM1ThresholdEventA2 m1thresholdeventA2;
	SztM1PeriodicRprtng m1periodicRprtng;
	SztProtExtnCont_ImmediateMDT_ExtIEs iE_Extns;
} SztImmediateMDT;

/* Element ---------- IMSI ----------- */
typedef TknStrOSXL SztIMSI;
/* Element ---------- IntegrityProtectionAlgorithms ----------- */
typedef TknBStr32 SztIntegrityProtectionAlgorithms;
/* Element ---------- InterfacesToTrace ----------- */
typedef TknBStr32 SztIntfsToTrace;
/* Element ----- Time-UE-StayedInCell ------- */
typedef TknU32 SztTime_UE_StayedInCell;

/* Element ----- Time-UE-StayedInCell-EnhancedGranularity ------- */
typedef TknU32 SztTime_UE_StayedInCell_EnhancedGranularity;

typedef struct s1ap_ExtnLastVisitedEUTRANCellInform_ExtIEsCls{
	union {
		SztTime_UE_StayedInCell_EnhancedGranularity sztTime_UE_StayedInCell_EnhancedGranularity;
		SztCause sztCause;
	} u;
} Szt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls;
typedef struct s1apProtExtnField_LastVisitedEUTRANCellInform_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls extensionValue;
} SztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs;

typedef struct s1apProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs *member;
}SztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs;

typedef struct s1apLastVisitedEUTRANCellInform
{
	TknPres pres;
	SztEUTRAN_CGI global_Cell_ID;
	SztCellTyp cellTyp;
	SztTime_UE_StayedInCell time_UE_StayedInCell;
	SztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs iE_Extns;
} SztLastVisitedEUTRANCellInform;

/* Element ---------- LastVisitedUTRANCellInformation ----------- */
typedef TknStrOSXL SztLastVisitedUTRANCellInform;
typedef struct s1apLastVisitedGERANCellInform
{
	TknU8 choice;
	union {
		TknU8 unused;
	} val;
} SztLastVisitedGERANCellInform;

typedef struct s1apLastVisitedCell_Item
{
	TknU8 choice;
	union {
		SztLastVisitedEUTRANCellInform e_UTRAN_Cell;
		SztLastVisitedUTRANCellInform uTRAN_Cell;
		SztLastVisitedGERANCellInform gERAN_Cell;
	} val;
} SztLastVisitedCell_Item;

/* Element ---------- L3-Information ----------- */
typedef TknStrOSXL SztL3_Inform;
/* Element ---------- LPPa-PDU ----------- */
typedef TknStrOSXL SztLPPa_PDU;
/* Element ----- LoggingInterval ------- */
typedef enum enumSztLoggingInterval
{
	SztLoggingIntervalms128Enum,
	SztLoggingIntervalms256Enum,
	SztLoggingIntervalms512Enum,
	SztLoggingIntervalms1024Enum,
	SztLoggingIntervalms2048Enum,
	SztLoggingIntervalms3072Enum,
	SztLoggingIntervalms4096Enum,
	SztLoggingIntervalms6144Enum
} EnumSztLoggingInterval;
typedef TknU32 SztLoggingInterval;

/* Element ----- LoggingDuration ------- */
typedef enum enumSztLoggingDuration
{
	SztLoggingDurationm10Enum,
	SztLoggingDurationm20Enum,
	SztLoggingDurationm40Enum,
	SztLoggingDurationm60Enum,
	SztLoggingDurationm90Enum,
	SztLoggingDurationm120Enum
} EnumSztLoggingDuration;
typedef TknU32 SztLoggingDuration;

typedef struct s1ap_ExtnLoggedMDT_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnLoggedMDT_ExtIEsCls;
typedef struct s1apProtExtnField_LoggedMDT_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnLoggedMDT_ExtIEsCls extensionValue;
} SztProtExtnField_LoggedMDT_ExtIEs;

typedef struct s1apProtExtnCont_LoggedMDT_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_LoggedMDT_ExtIEs *member;
}SztProtExtnCont_LoggedMDT_ExtIEs;

typedef struct s1apLoggedMDT
{
	TknPres pres;
	SztLoggingInterval loggingInterval;
	SztLoggingDuration loggingDuration;
	SztProtExtnCont_LoggedMDT_ExtIEs iE_Extns;
} SztLoggedMDT;

/* Element ----- MDT-Activation ------- */
typedef enum enumSztMDT_Actvn
{
	SztMDT_Actvnimmediate_MDT_onlyEnum,
	SztMDT_Actvnimmediate_MDT_and_TraceEnum,
	SztMDT_Actvnlogged_MDT_onlyEnum
} EnumSztMDT_Actvn;
typedef TknU32 SztMDT_Actvn;

typedef struct s1apMDTMode
{
	TknU8 choice;
	union {
		SztImmediateMDT immediateMDT;
		SztLoggedMDT loggedMDT;
	} val;
} SztMDTMode;

typedef struct s1apMDTPLMNLst
{
	TknU16 noComp;
	SztPLMNidentity *member;
}SztMDTPLMNLst;

typedef struct s1ap_ExtnMDT_Config_ExtIEsCls{
	union {
		SztMDTPLMNLst sztMDTPLMNLst;
	} u;
} Szt_ExtnMDT_Config_ExtIEsCls;
typedef struct s1apProtExtnField_MDT_Config_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnMDT_Config_ExtIEsCls extensionValue;
} SztProtExtnField_MDT_Config_ExtIEs;

typedef struct s1apProtExtnCont_MDT_Config_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_MDT_Config_ExtIEs *member;
}SztProtExtnCont_MDT_Config_ExtIEs;

typedef struct s1apMDT_Config
{
	TknPres pres;
	SztMDT_Actvn mdt_Actvn;
	SztAreaScopeOfMDT areaScopeOfMDT;
	SztMDTMode mDTMode;
	SztProtExtnCont_MDT_Config_ExtIEs iE_Extns;
} SztMDT_Config;

/* Element ----- ManagementBasedMDTAllowed ------- */
typedef enum enumSztManagementBasedMDTAllowed
{
	SztManagementBasedMDTAllowedallowedEnum
} EnumSztManagementBasedMDTAllowed;
typedef TknU32 SztManagementBasedMDTAllowed;

/* Element ----- PrivacyIndicator ------- */
typedef enum enumSztPrivacyIndicator
{
	SztPrivacyIndicatorimmediate_MDTEnum,
	SztPrivacyIndicatorlogged_MDTEnum
} EnumSztPrivacyIndicator;
typedef TknU32 SztPrivacyIndicator;

/* Element ---------- MessageIdentifier ----------- */
typedef TknBStr32 SztMsgIdentifier;
/* Element ---------- MobilityInformation ----------- */
typedef TknBStr32 SztMobilityInform;
/* Element ---------- MMEname ----------- */
typedef TknStrOSXL SztMMEname;
/* Element ----- MMERelaySupportIndicator ------- */
typedef enum enumSztMMERelaySupportIndicator
{
	SztMMERelaySupportIndicatortrueEnum
} EnumSztMMERelaySupportIndicator;
typedef TknU32 SztMMERelaySupportIndicator;

/* Element ----- MME-UE-S1AP-ID ------- */
typedef TknU32 SztMME_UE_S1AP_ID;

/* Element ---------- M-TMSI ----------- */
typedef TknStrOSXL SztM_TMSI;
/* Element ---------- MSClassmark2 ----------- */
typedef TknStrOSXL SztMSClassmark2;
/* Element ---------- MSClassmark3 ----------- */
typedef TknStrOSXL SztMSClassmark3;
/* Element ---------- NAS-PDU ----------- */
typedef TknStrOSXL SztNAS_PDU;
/* Element ---------- NASSecurityParametersfromE-UTRAN ----------- */
typedef TknStrOSXL SztNASSecurParamsfromE_UTRAN;
/* Element ---------- NASSecurityParameterstoE-UTRAN ----------- */
typedef TknStrOSXL SztNASSecurParamstoE_UTRAN;
/* Element ----- NumberofBroadcastRequest ------- */
typedef TknU32 SztNumberofBroadcastRqst;

/* Element ---------- OldBSS-ToNewBSS-Information ----------- */
typedef TknStrOSXL SztOldBSS_ToNewBSS_Inform;
/* Element ----- OverloadAction ------- */
typedef enum enumSztOverloadAction
{
	SztOverloadActionreject_non_emergency_mo_dtEnum,
	SztOverloadActionreject_rrc_cr_signallingEnum,
	SztOverloadActionpermit_emergency_sessions_and_mobile_terminated_services_onlyEnum,
	SztOverloadActionpermit_high_priority_sessions_and_mobile_terminated_services_onlyEnum,
	SztOverloadActionreject_delay_tolerant_accessEnum
} EnumSztOverloadAction;
typedef TknU32 SztOverloadAction;

typedef struct s1apOverloadResp
{
	TknU8 choice;
	union {
		SztOverloadAction overloadAction;
	} val;
} SztOverloadResp;

/* Element ----- PagingDRX ------- */
typedef enum enumSztPagDRX
{
	SztPagDRXv32Enum,
	SztPagDRXv64Enum,
	SztPagDRXv128Enum,
	SztPagDRXv256Enum
} EnumSztPagDRX;
typedef TknU32 SztPagDRX;

/* Element ----- PagingPriority ------- */
typedef enum enumSztPagPriority
{
	SztPagPrioritypriolevel1Enum,
	SztPagPrioritypriolevel2Enum,
	SztPagPrioritypriolevel3Enum,
	SztPagPrioritypriolevel4Enum,
	SztPagPrioritypriolevel5Enum,
	SztPagPrioritypriolevel6Enum,
	SztPagPrioritypriolevel7Enum,
	SztPagPrioritypriolevel8Enum
} EnumSztPagPriority;
typedef TknU32 SztPagPriority;

/* Element ---------- Port-Number ----------- */
typedef TknStr4 SztPort_Number;
/* Element ----- PS-ServiceNotAvailable ------- */
typedef enum enumSztPS_ServiceNotAvailable
{
	SztPS_ServiceNotAvailableps_service_not_availableEnum
} EnumSztPS_ServiceNotAvailable;
typedef TknU32 SztPS_ServiceNotAvailable;

/* Element ----- RelativeMMECapacity ------- */
typedef TknU32 SztRelativeMMECapacity;

/* Element ----- RelayNode-Indicator ------- */
typedef enum enumSztRelayNode_Indicator
{
	SztRelayNode_IndicatortrueEnum
} EnumSztRelayNode_Indicator;
typedef TknU32 SztRelayNode_Indicator;

/* Element ----- ReportArea ------- */
typedef enum enumSztReportArea
{
	SztReportAreaecgiEnum
} EnumSztReportArea;
typedef TknU32 SztReportArea;

typedef struct s1ap_ExtnRqstTyp_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnRqstTyp_ExtIEsCls;
typedef struct s1apProtExtnField_RqstTyp_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnRqstTyp_ExtIEsCls extensionValue;
} SztProtExtnField_RqstTyp_ExtIEs;

typedef struct s1apProtExtnCont_RqstTyp_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_RqstTyp_ExtIEs *member;
}SztProtExtnCont_RqstTyp_ExtIEs;

typedef struct s1apRqstTyp
{
	TknPres pres;
	SztEventTyp eventTyp;
	SztReportArea reportArea;
	SztProtExtnCont_RqstTyp_ExtIEs iE_Extns;
} SztRqstTyp;

/* Element ---------- RIMInformation ----------- */
typedef TknStrOSXL SztRIMInform;
/* Element ----- RNC-ID ------- */
typedef TknU32 SztRNC_ID;

typedef struct s1ap_ExtnTgetRNC_ID_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnTgetRNC_ID_ExtIEsCls;
typedef struct s1apProtExtnField_TgetRNC_ID_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnTgetRNC_ID_ExtIEsCls extensionValue;
} SztProtExtnField_TgetRNC_ID_ExtIEs;

typedef struct s1apProtExtnCont_TgetRNC_ID_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_TgetRNC_ID_ExtIEs *member;
}SztProtExtnCont_TgetRNC_ID_ExtIEs;

typedef struct s1apTgetRNC_ID
{
	TknPres pres;
	SztLAI lAI;
	SztRAC rAC;
	SztRNC_ID rNC_ID;
	SztExtendedRNC_ID extendedRNC_ID;
	SztProtExtnCont_TgetRNC_ID_ExtIEs iE_Extns;
} SztTgetRNC_ID;

typedef struct s1apRIMRoutingAddr
{
	TknU8 choice;
	union {
		SztGERAN_Cell_ID gERAN_Cell_ID;
		SztTgetRNC_ID targetRNC_ID;
	} val;
} SztRIMRoutingAddr;

typedef struct s1ap_ExtnRIMTfr_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnRIMTfr_ExtIEsCls;
typedef struct s1apProtExtnField_RIMTfr_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnRIMTfr_ExtIEsCls extensionValue;
} SztProtExtnField_RIMTfr_ExtIEs;

typedef struct s1apProtExtnCont_RIMTfr_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_RIMTfr_ExtIEs *member;
}SztProtExtnCont_RIMTfr_ExtIEs;

typedef struct s1apRIMTfr
{
	TknPres pres;
	SztRIMInform rIMInform;
	SztRIMRoutingAddr rIMRoutingAddr;
	SztProtExtnCont_RIMTfr_ExtIEs iE_Extns;
} SztRIMTfr;

/* Element ----- RepetitionPeriod ------- */
typedef TknU32 SztRepetitionPeriod;

/* Element ---------- RRC-Container ----------- */
typedef TknStrOSXL SztRRC_Cont;
/* Element ----- RRC-Establishment-Cause ------- */
typedef enum enumSztRRC_Establishment_Cause
{
	SztRRC_Establishment_CauseemergencyEnum,
	SztRRC_Establishment_CausehighPriorityAccessEnum,
	SztRRC_Establishment_Causemt_AccessEnum,
	SztRRC_Establishment_Causemo_SignallingEnum,
	SztRRC_Establishment_Causemo_DataEnum,
	SztRRC_Establishment_Causedelay_TolerantAccessEnum
} EnumSztRRC_Establishment_Cause;
typedef TknU32 SztRRC_Establishment_Cause;

/* Element ----- Routing-ID ------- */
typedef TknU32 SztRouting_ID;

/* Element ---------- SecurityKey ----------- */
typedef TknStrBSXL SztSecurKey;
/* Element ----- nextHopChainingCount ------- */
typedef TknU32 SztSecurCntxtnextHopChainingCount;

typedef struct s1ap_ExtnSecurCntxt_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnSecurCntxt_ExtIEsCls;
typedef struct s1apProtExtnField_SecurCntxt_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnSecurCntxt_ExtIEsCls extensionValue;
} SztProtExtnField_SecurCntxt_ExtIEs;

typedef struct s1apProtExtnCont_SecurCntxt_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_SecurCntxt_ExtIEs *member;
}SztProtExtnCont_SecurCntxt_ExtIEs;

typedef struct s1apSecurCntxt
{
	TknPres pres;
	SztSecurCntxtnextHopChainingCount nextHopChainingCount;
	SztSecurKey nextHopParameter;
	SztProtExtnCont_SecurCntxt_ExtIEs iE_Extns;
} SztSecurCntxt;

/* Element ---------- SerialNumber ----------- */
typedef TknBStr32 SztSerialNumber;
/* Element ----- SONInformationRequest ------- */
typedef enum enumSztSONInformRqst
{
	SztSONInformRqstx2TNL_Config_InfoEnum,
	SztSONInformRqsttime_Synchronization_InfoEnum
} EnumSztSONInformRqst;
typedef TknU32 SztSONInformRqst;

typedef struct s1apENBX2GTPTLAs
{
	TknU16 noComp;
	SztTportLyrAddr *member;
}SztENBX2GTPTLAs;

typedef struct s1ap_ExtnENBX2ExtTLA_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnENBX2ExtTLA_ExtIEsCls;
typedef struct s1apProtExtnField_ENBX2ExtTLA_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnENBX2ExtTLA_ExtIEsCls extensionValue;
} SztProtExtnField_ENBX2ExtTLA_ExtIEs;

typedef struct s1apProtExtnCont_ENBX2ExtTLA_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_ENBX2ExtTLA_ExtIEs *member;
}SztProtExtnCont_ENBX2ExtTLA_ExtIEs;

typedef struct s1apENBX2ExtTLA
{
	TknPres pres;
	SztTportLyrAddr iPsecTLA;
	SztENBX2GTPTLAs gTPTLAa;
	SztProtExtnCont_ENBX2ExtTLA_ExtIEs iE_Extns;
} SztENBX2ExtTLA;

typedef struct s1apENBX2ExtTLAs
{
	TknU16 noComp;
	SztENBX2ExtTLA *member;
}SztENBX2ExtTLAs;

typedef struct s1ap_ExtnX2TNLConfigInfo_ExtIEsCls{
	union {
		SztENBX2ExtTLAs sztENBX2ExtTLAs;
	} u;
} Szt_ExtnX2TNLConfigInfo_ExtIEsCls;
typedef struct s1apProtExtnField_X2TNLConfigInfo_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnX2TNLConfigInfo_ExtIEsCls extensionValue;
} SztProtExtnField_X2TNLConfigInfo_ExtIEs;

typedef struct s1apProtExtnCont_X2TNLConfigInfo_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_X2TNLConfigInfo_ExtIEs *member;
}SztProtExtnCont_X2TNLConfigInfo_ExtIEs;

typedef struct s1apX2TNLConfigInfo
{
	TknPres pres;
	SztENBX2TLAs eNBX2TportLyrAddres;
	SztProtExtnCont_X2TNLConfigInfo_ExtIEs iE_Extns;
} SztX2TNLConfigInfo;

/* Element ----- StratumLevel ------- */
typedef TknU32 SztStratumLvl;

/* Element ----- SynchronizationStatus ------- */
typedef enum enumSztSynchronizationStatus
{
	SztSynchronizationStatussynchronousEnum,
	SztSynchronizationStatusasynchronousEnum
} EnumSztSynchronizationStatus;
typedef TknU32 SztSynchronizationStatus;

typedef struct s1ap_ExtnTimeSynchronizationInfo_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnTimeSynchronizationInfo_ExtIEsCls;
typedef struct s1apProtExtnField_TimeSynchronizationInfo_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnTimeSynchronizationInfo_ExtIEsCls extensionValue;
} SztProtExtnField_TimeSynchronizationInfo_ExtIEs;

typedef struct s1apProtExtnCont_TimeSynchronizationInfo_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_TimeSynchronizationInfo_ExtIEs *member;
}SztProtExtnCont_TimeSynchronizationInfo_ExtIEs;

typedef struct s1apTimeSynchronizationInfo
{
	TknPres pres;
	SztStratumLvl stratumLvl;
	SztSynchronizationStatus synchronizationStatus;
	SztProtExtnCont_TimeSynchronizationInfo_ExtIEs iE_Extns;
} SztTimeSynchronizationInfo;

typedef struct s1ap_ExtnSONInformReply_ExtIEsCls{
	union {
		SztTimeSynchronizationInfo sztTimeSynchronizationInfo;
	} u;
} Szt_ExtnSONInformReply_ExtIEsCls;
typedef struct s1apProtExtnField_SONInformReply_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnSONInformReply_ExtIEsCls extensionValue;
} SztProtExtnField_SONInformReply_ExtIEs;

typedef struct s1apProtExtnCont_SONInformReply_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_SONInformReply_ExtIEs *member;
}SztProtExtnCont_SONInformReply_ExtIEs;

typedef struct s1apSONInformReply
{
	TknPres pres;
	SztX2TNLConfigInfo x2TNLConfigInfo;
	SztProtExtnCont_SONInformReply_ExtIEs iE_Extns;
} SztSONInformReply;

typedef struct s1apSONInform
{
	TknU8 choice;
	union {
		SztSONInformRqst sONInformRqst;
		SztSONInformReply sONInformReply;
	} val;
} SztSONInform;

typedef struct s1ap_ExtnTgeteNB_ID_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnTgeteNB_ID_ExtIEsCls;
typedef struct s1apProtExtnField_TgeteNB_ID_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnTgeteNB_ID_ExtIEsCls extensionValue;
} SztProtExtnField_TgeteNB_ID_ExtIEs;

typedef struct s1apProtExtnCont_TgeteNB_ID_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_TgeteNB_ID_ExtIEs *member;
}SztProtExtnCont_TgeteNB_ID_ExtIEs;

typedef struct s1apTgeteNB_ID
{
	TknPres pres;
	SztGlobal_ENB_ID global_ENB_ID;
	SztTAI selected_TAI;
	SztProtExtnCont_TgeteNB_ID_ExtIEs iE_Extns;
} SztTgeteNB_ID;

typedef struct s1ap_ExtnSrceNB_ID_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnSrceNB_ID_ExtIEsCls;
typedef struct s1apProtExtnField_SrceNB_ID_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnSrceNB_ID_ExtIEsCls extensionValue;
} SztProtExtnField_SrceNB_ID_ExtIEs;

typedef struct s1apProtExtnCont_SrceNB_ID_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_SrceNB_ID_ExtIEs *member;
}SztProtExtnCont_SrceNB_ID_ExtIEs;

typedef struct s1apSrceNB_ID
{
	TknPres pres;
	SztGlobal_ENB_ID global_ENB_ID;
	SztTAI selected_TAI;
	SztProtExtnCont_SrceNB_ID_ExtIEs iE_Extns;
} SztSrceNB_ID;

typedef struct s1ap_ExtnSONConfigTfr_ExtIEsCls{
	union {
		SztX2TNLConfigInfo sztX2TNLConfigInfo;
	} u;
} Szt_ExtnSONConfigTfr_ExtIEsCls;
typedef struct s1apProtExtnField_SONConfigTfr_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnSONConfigTfr_ExtIEsCls extensionValue;
} SztProtExtnField_SONConfigTfr_ExtIEs;

typedef struct s1apProtExtnCont_SONConfigTfr_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_SONConfigTfr_ExtIEs *member;
}SztProtExtnCont_SONConfigTfr_ExtIEs;

typedef struct s1apSONConfigTfr
{
	TknPres pres;
	SztTgeteNB_ID targeteNB_ID;
	SztSrceNB_ID sourceeNB_ID;
	SztSONInform sONInform;
	SztProtExtnCont_SONConfigTfr_ExtIEs iE_Extns;
} SztSONConfigTfr;

/* Element ---------- Source-ToTarget-TransparentContainer ----------- */
typedef TknStrOSXL SztSrc_ToTget_TprntCont;
/* Element ---------- SourceBSS-ToTargetBSS-TransparentContainer ----------- */
typedef TknStrOSXL SztSrcBSS_ToTgetBSS_TprntCont;
/* Element ----- SRVCCOperationPossible ------- */
typedef enum enumSztSRVCCOperationPossible
{
	SztSRVCCOperationPossiblepossibleEnum
} EnumSztSRVCCOperationPossible;
typedef TknU32 SztSRVCCOperationPossible;

/* Element ----- SRVCCHOIndication ------- */
typedef enum enumSztSRVCCHOInd
{
	SztSRVCCHOIndpSandCSEnum,
	SztSRVCCHOIndcSonlyEnum
} EnumSztSRVCCHOInd;
typedef TknU32 SztSRVCCHOInd;

/* Element ----- SubscriberProfileIDforRFP ------- */
typedef TknU32 SztSubscriberProfileIDforRFP;

typedef struct s1apUE_HistoryInform
{
	TknU16 noComp;
	SztLastVisitedCell_Item *member;
}SztUE_HistoryInform;

typedef struct s1ap_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls{
	union {
		SztMobilityInform sztMobilityInform;
	} u;
} Szt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls;
typedef struct s1apProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls extensionValue;
} SztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs;

typedef struct s1apProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs *member;
}SztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs;

typedef struct s1apSrceNB_ToTgeteNB_TprntCont
{
	TknPres pres;
	SztRRC_Cont rRC_Cont;
	SztE_RABInformLst e_RABInformLst;
	SztEUTRAN_CGI targetCell_ID;
	SztSubscriberProfileIDforRFP subscriberProfileIDforRFP;
	SztUE_HistoryInform uE_HistoryInform;
	SztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs iE_Extns;
} SztSrceNB_ToTgeteNB_TprntCont;

/* Element ---------- SourceRNC-ToTargetRNC-TransparentContainer ----------- */
typedef TknStrOSXL SztSrcRNC_ToTgetRNC_TprntCont;
typedef struct s1apSrvdPLMNs
{
	TknU16 noComp;
	SztPLMNidentity *member;
}SztSrvdPLMNs;

typedef struct s1apSrvdGroupIDs
{
	TknU16 noComp;
	SztMME_Group_ID *member;
}SztSrvdGroupIDs;

typedef struct s1apSrvdMMECs
{
	TknU16 noComp;
	SztMME_Code *member;
}SztSrvdMMECs;

typedef struct s1ap_ExtnSrvdGUMMEIsItem_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnSrvdGUMMEIsItem_ExtIEsCls;
typedef struct s1apProtExtnField_SrvdGUMMEIsItem_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnSrvdGUMMEIsItem_ExtIEsCls extensionValue;
} SztProtExtnField_SrvdGUMMEIsItem_ExtIEs;

typedef struct s1apProtExtnCont_SrvdGUMMEIsItem_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_SrvdGUMMEIsItem_ExtIEs *member;
}SztProtExtnCont_SrvdGUMMEIsItem_ExtIEs;

typedef struct s1apSrvdGUMMEIsItem
{
	TknPres pres;
	SztSrvdPLMNs servedPLMNs;
	SztSrvdGroupIDs servedGroupIDs;
	SztSrvdMMECs servedMMECs;
	SztProtExtnCont_SrvdGUMMEIsItem_ExtIEs iE_Extns;
} SztSrvdGUMMEIsItem;

typedef struct s1apSrvdGUMMEIs
{
	TknU16 noComp;
	SztSrvdGUMMEIsItem *member;
}SztSrvdGUMMEIs;

typedef struct s1ap_ExtnSuppTAs_Item_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnSuppTAs_Item_ExtIEsCls;
typedef struct s1apProtExtnField_SuppTAs_Item_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnSuppTAs_Item_ExtIEsCls extensionValue;
} SztProtExtnField_SuppTAs_Item_ExtIEs;

typedef struct s1apProtExtnCont_SuppTAs_Item_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_SuppTAs_Item_ExtIEs *member;
}SztProtExtnCont_SuppTAs_Item_ExtIEs;

typedef struct s1apSuppTAs_Item
{
	TknPres pres;
	SztTAC tAC;
	SztBPLMNs broadcastPLMNs;
	SztProtExtnCont_SuppTAs_Item_ExtIEs iE_Extns;
} SztSuppTAs_Item;

typedef struct s1apSuppTAs
{
	TknU16 noComp;
	SztSuppTAs_Item *member;
}SztSuppTAs;

typedef struct s1ap_ExtnS_TMSI_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnS_TMSI_ExtIEsCls;
typedef struct s1apProtExtnField_S_TMSI_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnS_TMSI_ExtIEsCls extensionValue;
} SztProtExtnField_S_TMSI_ExtIEs;

typedef struct s1apProtExtnCont_S_TMSI_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_S_TMSI_ExtIEs *member;
}SztProtExtnCont_S_TMSI_ExtIEs;

typedef struct s1apS_TMSI
{
	TknPres pres;
	SztMME_Code mMEC;
	SztM_TMSI m_TMSI;
	SztProtExtnCont_S_TMSI_ExtIEs iE_Extns;
} SztS_TMSI;

typedef struct s1apTAILstforWarning
{
	TknU16 noComp;
	SztTAI *member;
}SztTAILstforWarning;

typedef struct s1apTgetID
{
	TknU8 choice;
	union {
		SztTgeteNB_ID targeteNB_ID;
		SztTgetRNC_ID targetRNC_ID;
		SztCGI cGI;
	} val;
} SztTgetID;

typedef struct s1ap_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls;
typedef struct s1apProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls extensionValue;
} SztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs;

typedef struct s1apProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs *member;
}SztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs;

typedef struct s1apTgeteNB_ToSrceNB_TprntCont
{
	TknPres pres;
	SztRRC_Cont rRC_Cont;
	SztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs iE_Extns;
} SztTgeteNB_ToSrceNB_TprntCont;

/* Element ---------- Target-ToSource-TransparentContainer ----------- */
typedef TknStrOSXL SztTget_ToSrc_TprntCont;
/* Element ---------- TargetRNC-ToSourceRNC-TransparentContainer ----------- */
typedef TknStrOSXL SztTgetRNC_ToSrcRNC_TprntCont;
/* Element ---------- TargetBSS-ToSourceBSS-TransparentContainer ----------- */
typedef TknStrOSXL SztTgetBSS_ToSrcBSS_TprntCont;
/* Element ----- TimeToWait ------- */
typedef enum enumSztTimeToWait
{
	SztTimeToWaitv1sEnum,
	SztTimeToWaitv2sEnum,
	SztTimeToWaitv5sEnum,
	SztTimeToWaitv10sEnum,
	SztTimeToWaitv20sEnum,
	SztTimeToWaitv60sEnum
} EnumSztTimeToWait;
typedef TknU32 SztTimeToWait;

/* Element ---------- E-UTRAN-Trace-ID ----------- */
typedef TknStrOSXL SztE_UTRAN_Trace_ID;
/* Element ----- TraceDepth ------- */
typedef enum enumSztTraceDepth
{
	SztTraceDepthminimumEnum,
	SztTraceDepthmediumEnum,
	SztTraceDepthmaximumEnum,
	SztTraceDepthminimumWithoutVendorSpecificExtnEnum,
	SztTraceDepthmediumWithoutVendorSpecificExtnEnum,
	SztTraceDepthmaximumWithoutVendorSpecificExtnEnum
} EnumSztTraceDepth;
typedef TknU32 SztTraceDepth;

typedef struct s1ap_ExtnTraceActvn_ExtIEsCls{
	union {
		SztMDT_Config sztMDT_Config;
	} u;
} Szt_ExtnTraceActvn_ExtIEsCls;
typedef struct s1apProtExtnField_TraceActvn_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnTraceActvn_ExtIEsCls extensionValue;
} SztProtExtnField_TraceActvn_ExtIEs;

typedef struct s1apProtExtnCont_TraceActvn_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_TraceActvn_ExtIEs *member;
}SztProtExtnCont_TraceActvn_ExtIEs;

typedef struct s1apTraceActvn
{
	TknPres pres;
	SztE_UTRAN_Trace_ID e_UTRAN_Trace_ID;
	SztIntfsToTrace interfacesToTrace;
	SztTraceDepth traceDepth;
	SztTportLyrAddr traceCollectionEntityIPAddr;
	SztProtExtnCont_TraceActvn_ExtIEs iE_Extns;
} SztTraceActvn;

/* Element ----- TrafficLoadReductionIndication ------- */
typedef TknU32 SztTrafficLoadReductionInd;

typedef struct s1ap_ExtnTunnel_Inform_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnTunnel_Inform_ExtIEsCls;
typedef struct s1apProtExtnField_Tunnel_Inform_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnTunnel_Inform_ExtIEsCls extensionValue;
} SztProtExtnField_Tunnel_Inform_ExtIEs;

typedef struct s1apProtExtnCont_Tunnel_Inform_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_Tunnel_Inform_ExtIEs *member;
}SztProtExtnCont_Tunnel_Inform_ExtIEs;

typedef struct s1apTunnelInform
{
	TknPres pres;
	SztTportLyrAddr transportLyrAddr;
	SztPort_Number uDP_Port_Number;
	SztProtExtnCont_Tunnel_Inform_ExtIEs iE_Extns;
} SztTunnelInform;

typedef struct s1ap_ExtnUEAgg_MaxBitrates_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnUEAgg_MaxBitrates_ExtIEsCls;
typedef struct s1apProtExtnField_UEAgg_MaxBitrates_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnUEAgg_MaxBitrates_ExtIEsCls extensionValue;
} SztProtExtnField_UEAgg_MaxBitrates_ExtIEs;

typedef struct s1apProtExtnCont_UEAgg_MaxBitrates_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_UEAgg_MaxBitrates_ExtIEs *member;
}SztProtExtnCont_UEAgg_MaxBitrates_ExtIEs;

typedef struct s1apUEAggMaxBitrate
{
	TknPres pres;
	SztBitRate uEaggregateMaxBitRateDL;
	SztBitRate uEaggregateMaxBitRateUL;
	SztProtExtnCont_UEAgg_MaxBitrates_ExtIEs iE_Extns;
} SztUEAggMaxBitrate;

typedef struct s1ap_ExtnUE_S1AP_ID_pair_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnUE_S1AP_ID_pair_ExtIEsCls;
typedef struct s1apProtExtnField_UE_S1AP_ID_pair_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnUE_S1AP_ID_pair_ExtIEsCls extensionValue;
} SztProtExtnField_UE_S1AP_ID_pair_ExtIEs;

typedef struct s1apProtExtnCont_UE_S1AP_ID_pair_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_UE_S1AP_ID_pair_ExtIEs *member;
}SztProtExtnCont_UE_S1AP_ID_pair_ExtIEs;

typedef struct s1apUE_S1AP_ID_pair
{
	TknPres pres;
	SztMME_UE_S1AP_ID mME_UE_S1AP_ID;
	SztENB_UE_S1AP_ID eNB_UE_S1AP_ID;
	SztProtExtnCont_UE_S1AP_ID_pair_ExtIEs iE_Extns;
} SztUE_S1AP_ID_pair;

typedef struct s1apUE_S1AP_IDs
{
	TknU8 choice;
	union {
		SztUE_S1AP_ID_pair uE_S1AP_ID_pair;
		SztMME_UE_S1AP_ID mME_UE_S1AP_ID;
	} val;
} SztUE_S1AP_IDs;

typedef struct s1ap_ExtnUE_assocLogS1_ConItemExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnUE_assocLogS1_ConItemExtIEsCls;
typedef struct s1apProtExtnField_UE_assocLogS1_ConItemExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnUE_assocLogS1_ConItemExtIEsCls extensionValue;
} SztProtExtnField_UE_assocLogS1_ConItemExtIEs;

typedef struct s1apProtExtnCont_UE_assocLogS1_ConItemExtIEs
{
	TknU16 noComp;
	SztProtExtnField_UE_assocLogS1_ConItemExtIEs *member;
}SztProtExtnCont_UE_assocLogS1_ConItemExtIEs;

typedef struct s1apUE_assocLogS1_ConItem
{
	TknPres pres;
	SztMME_UE_S1AP_ID mME_UE_S1AP_ID;
	SztENB_UE_S1AP_ID eNB_UE_S1AP_ID;
	SztProtExtnCont_UE_assocLogS1_ConItemExtIEs iE_Extns;
} SztUE_assocLogS1_ConItem;

/* Element ---------- UEIdentityIndexValue ----------- */
typedef TknBStr32 SztUEIdentityIdxValue;
typedef struct s1apUEPagID
{
	TknU8 choice;
	union {
		SztS_TMSI s_TMSI;
		SztIMSI iMSI;
	} val;
} SztUEPagID;

/* Element ---------- UERadioCapability ----------- */
typedef TknStrOSXL SztUERadioCapblty;
typedef struct s1ap_ExtnUESecurCapabilities_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnUESecurCapabilities_ExtIEsCls;
typedef struct s1apProtExtnField_UESecurCapabilities_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnUESecurCapabilities_ExtIEsCls extensionValue;
} SztProtExtnField_UESecurCapabilities_ExtIEs;

typedef struct s1apProtExtnCont_UESecurCapabilities_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_UESecurCapabilities_ExtIEs *member;
}SztProtExtnCont_UESecurCapabilities_ExtIEs;

typedef struct s1apUESecurCapabilities
{
	TknPres pres;
	SztEncryptionAlgorithms encryptionAlgorithms;
	SztIntegrityProtectionAlgorithms integrityProtectionAlgorithms;
	SztProtExtnCont_UESecurCapabilities_ExtIEs iE_Extns;
} SztUESecurCapabilities;

/* Element ----- VoiceSupportMatchIndicator ------- */
typedef enum enumSztVoiceSupportMatchIndicator
{
	SztVoiceSupportMatchIndicatorsupportedEnum,
	SztVoiceSupportMatchIndicatornot_supportedEnum
} EnumSztVoiceSupportMatchIndicator;
typedef TknU32 SztVoiceSupportMatchIndicator;

typedef struct s1apWarningAreaLst
{
	TknU8 choice;
	union {
		SztECGILst cellIDLst;
		SztTAILstforWarning trackingAreaLstforWarning;
		SztEmergencyAreaIDLst emergencyAreaIDLst;
	} val;
} SztWarningAreaLst;

/* Element ---------- WarningType ----------- */
typedef TknStr4 SztWarningTyp;
/* Element ---------- WarningSecurityInfo ----------- */
typedef TknStrOSXL SztWarningSecurInfo;
/* Element ---------- WarningMessageContents ----------- */
typedef TknStrOSXL SztWarningMsgContents;
typedef struct s1ap_ValueHovrReqdIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztHovrTyp sztHovrTyp;
		SztCause sztCause;
		SztTgetID sztTgetID;
		SztDirect_Fwding_Path_Avlblty sztDirect_Fwding_Path_Avlblty;
		SztSRVCCHOInd sztSRVCCHOInd;
		SztSrc_ToTget_TprntCont sztid_Src_ToTget_TprntCont;
		SztSrc_ToTget_TprntCont sztid_Src_ToTget_TprntCont_Secondary;
		SztMSClassmark2 sztMSClassmark2;
		SztMSClassmark3 sztMSClassmark3;
		SztCSG_Id sztCSG_Id;
		SztCellAccessMode sztCellAccessMode;
		SztPS_ServiceNotAvailable sztPS_ServiceNotAvailable;
	} u;
} Szt_ValueHovrReqdIEsCls;
typedef struct s1apProtIE_Field_HovrReqdIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueHovrReqdIEsCls value;
} SztProtIE_Field_HovrReqdIEs;

typedef struct s1apProtIE_Cont_HovrReqdIEs
{
	TknU16 noComp;
	SztProtIE_Field_HovrReqdIEs *member;
}SztProtIE_Cont_HovrReqdIEs;

typedef struct s1apHovrReqd
{
	TknPres pres;
	SztProtIE_Cont_HovrReqdIEs protocolIEs;
} SztHovrReqd;

typedef struct s1ap_ExtnE_RABDataFwdingItem_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnE_RABDataFwdingItem_ExtIEsCls;
typedef struct s1apProtExtnField_E_RABDataFwdingItem_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnE_RABDataFwdingItem_ExtIEsCls extensionValue;
} SztProtExtnField_E_RABDataFwdingItem_ExtIEs;

typedef struct s1apProtExtnCont_E_RABDataFwdingItem_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_E_RABDataFwdingItem_ExtIEs *member;
}SztProtExtnCont_E_RABDataFwdingItem_ExtIEs;

typedef struct s1apE_RABDataFwdingItem
{
	TknPres pres;
	SztE_RAB_ID e_RAB_ID;
	SztTportLyrAddr dL_transportLyrAddr;
	SztGTP_TEID dL_gTP_TEID;
	SztTportLyrAddr uL_TportLyrAddr;
	SztGTP_TEID uL_GTP_TEID;
	SztProtExtnCont_E_RABDataFwdingItem_ExtIEs iE_Extns;
} SztE_RABDataFwdingItem;

typedef struct s1ap_ValueE_RABDataFwdingItemIEsCls{
	union {
		SztE_RABDataFwdingItem sztE_RABDataFwdingItem;
	} u;
} Szt_ValueE_RABDataFwdingItemIEsCls;
typedef struct s1apProtIE_Field_E_RABDataFwdingItemIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueE_RABDataFwdingItemIEsCls value;
} SztProtIE_Field_E_RABDataFwdingItemIEs;

/* Element ------------- ProtocolIE-SingleContainer ------------ */
typedef SztProtIE_Field_E_RABDataFwdingItemIEs SztProtIE_SingleCont_E_RABDataFwdingItemIEs;
typedef struct s1apProtIE_ContLst_E_RABDataFwdingItemIEs
{
	TknU16 noComp;
	SztProtIE_SingleCont_E_RABDataFwdingItemIEs *member;
}SztProtIE_ContLst_E_RABDataFwdingItemIEs;

/* Element ------------- E-RAB-IE-ContainerList ------------ */
typedef SztProtIE_ContLst_E_RABDataFwdingItemIEs SztE_RAB_IE_ContLst_E_RABDataFwdingItemIEs;
/* Element ------------- E-RABSubjecttoDataForwardingList ------------ */
typedef SztE_RAB_IE_ContLst_E_RABDataFwdingItemIEs  SztE_RABSubjtoDataFwdingLst;
typedef struct s1ap_ValueHovrCmmdIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztHovrTyp sztHovrTyp;
		SztNASSecurParamsfromE_UTRAN sztNASSecurParamsfromE_UTRAN;
		SztE_RABSubjtoDataFwdingLst sztE_RABSubjtoDataFwdingLst;
		SztE_RABLst sztE_RABLst;
		SztTget_ToSrc_TprntCont sztid_Tget_ToSrc_TprntCont;
		SztTget_ToSrc_TprntCont sztid_Tget_ToSrc_TprntCont_Secondary;
		SztCriticalityDiag sztCriticalityDiag;
	} u;
} Szt_ValueHovrCmmdIEsCls;
typedef struct s1apProtIE_Field_HovrCmmdIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueHovrCmmdIEsCls value;
} SztProtIE_Field_HovrCmmdIEs;

typedef struct s1apProtIE_Cont_HovrCmmdIEs
{
	TknU16 noComp;
	SztProtIE_Field_HovrCmmdIEs *member;
}SztProtIE_Cont_HovrCmmdIEs;

typedef struct s1apHovrCmmd
{
	TknPres pres;
	SztProtIE_Cont_HovrCmmdIEs protocolIEs;
} SztHovrCmmd;

typedef struct s1ap_ValueHovrPrepFailIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztCause sztCause;
		SztCriticalityDiag sztCriticalityDiag;
	} u;
} Szt_ValueHovrPrepFailIEsCls;
typedef struct s1apProtIE_Field_HovrPrepFailIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueHovrPrepFailIEsCls value;
} SztProtIE_Field_HovrPrepFailIEs;

typedef struct s1apProtIE_Cont_HovrPrepFailIEs
{
	TknU16 noComp;
	SztProtIE_Field_HovrPrepFailIEs *member;
}SztProtIE_Cont_HovrPrepFailIEs;

typedef struct s1apHovrPrepFail
{
	TknPres pres;
	SztProtIE_Cont_HovrPrepFailIEs protocolIEs;
} SztHovrPrepFail;

typedef struct s1ap_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls{
	union {
		SztData_Fwding_Not_Possible sztData_Fwding_Not_Possible;
	} u;
} Szt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls;
typedef struct s1apProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls extensionValue;
} SztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs;

typedef struct s1apProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs *member;
}SztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs;

typedef struct s1apE_RABToBeSetupItemHOReq
{
	TknPres pres;
	SztE_RAB_ID e_RAB_ID;
	SztTportLyrAddr transportLyrAddr;
	SztGTP_TEID gTP_TEID;
	SztE_RABLvlQoSParams e_RABlevelQosParams;
	SztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs iE_Extns;
} SztE_RABToBeSetupItemHOReq;

typedef struct s1ap_ValueE_RABToBeSetupItemHOReqIEsCls{
	union {
		SztE_RABToBeSetupItemHOReq sztE_RABToBeSetupItemHOReq;
	} u;
} Szt_ValueE_RABToBeSetupItemHOReqIEsCls;
typedef struct s1apProtIE_Field_E_RABToBeSetupItemHOReqIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueE_RABToBeSetupItemHOReqIEsCls value;
} SztProtIE_Field_E_RABToBeSetupItemHOReqIEs;

/* Element ------------- ProtocolIE-SingleContainer ------------ */
typedef SztProtIE_Field_E_RABToBeSetupItemHOReqIEs SztProtIE_SingleCont_E_RABToBeSetupItemHOReqIEs;
typedef struct s1apProtIE_ContLst_E_RABToBeSetupItemHOReqIEs
{
	TknU16 noComp;
	SztProtIE_SingleCont_E_RABToBeSetupItemHOReqIEs *member;
}SztProtIE_ContLst_E_RABToBeSetupItemHOReqIEs;

/* Element ------------- E-RAB-IE-ContainerList ------------ */
typedef SztProtIE_ContLst_E_RABToBeSetupItemHOReqIEs SztE_RAB_IE_ContLst_E_RABToBeSetupItemHOReqIEs;
/* Element ------------- E-RABToBeSetupListHOReq ------------ */
typedef SztE_RAB_IE_ContLst_E_RABToBeSetupItemHOReqIEs  SztE_RABToBeSetupLstHOReq;
typedef struct s1ap_ValueHovrRqstIEsCls{
	union {
		SztMME_UE_S1AP_ID sztid_MME_UE_S1AP_ID;
		SztHovrTyp sztHovrTyp;
		SztCause sztCause;
		SztUEAggMaxBitrate sztUEAggMaxBitrate;
		SztE_RABToBeSetupLstHOReq sztE_RABToBeSetupLstHOReq;
		SztSrc_ToTget_TprntCont sztSrc_ToTget_TprntCont;
		SztUESecurCapabilities sztUESecurCapabilities;
		SztHovrRestrnLst sztHovrRestrnLst;
		SztTraceActvn sztTraceActvn;
		SztRqstTyp sztRqstTyp;
		SztSRVCCOperationPossible sztSRVCCOperationPossible;
		SztSecurCntxt sztSecurCntxt;
		SztNASSecurParamstoE_UTRAN sztNASSecurParamstoE_UTRAN;
		SztCSG_Id sztCSG_Id;
		SztCSGMembershipStatus sztCSGMembershipStatus;
		SztGUMMEI sztGUMMEI;
		SztMME_UE_S1AP_ID sztid_MME_UE_S1AP_ID_2;
		SztManagementBasedMDTAllowed sztManagementBasedMDTAllowed;
		SztMDTPLMNLst sztMDTPLMNLst;
	} u;
} Szt_ValueHovrRqstIEsCls;
typedef struct s1apProtIE_Field_HovrRqstIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueHovrRqstIEsCls value;
} SztProtIE_Field_HovrRqstIEs;

typedef struct s1apProtIE_Cont_HovrRqstIEs
{
	TknU16 noComp;
	SztProtIE_Field_HovrRqstIEs *member;
}SztProtIE_Cont_HovrRqstIEs;

typedef struct s1apHovrRqst
{
	TknPres pres;
	SztProtIE_Cont_HovrRqstIEs protocolIEs;
} SztHovrRqst;

typedef struct s1ap_ExtnE_RABAdmtdItem_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnE_RABAdmtdItem_ExtIEsCls;
typedef struct s1apProtExtnField_E_RABAdmtdItem_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnE_RABAdmtdItem_ExtIEsCls extensionValue;
} SztProtExtnField_E_RABAdmtdItem_ExtIEs;

typedef struct s1apProtExtnCont_E_RABAdmtdItem_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_E_RABAdmtdItem_ExtIEs *member;
}SztProtExtnCont_E_RABAdmtdItem_ExtIEs;

typedef struct s1apE_RABAdmtdItem
{
	TknPres pres;
	SztE_RAB_ID e_RAB_ID;
	SztTportLyrAddr transportLyrAddr;
	SztGTP_TEID gTP_TEID;
	SztTportLyrAddr dL_transportLyrAddr;
	SztGTP_TEID dL_gTP_TEID;
	SztTportLyrAddr uL_TportLyrAddr;
	SztGTP_TEID uL_GTP_TEID;
	SztProtExtnCont_E_RABAdmtdItem_ExtIEs iE_Extns;
} SztE_RABAdmtdItem;

typedef struct s1ap_ValueE_RABAdmtdItemIEsCls{
	union {
		SztE_RABAdmtdItem sztE_RABAdmtdItem;
	} u;
} Szt_ValueE_RABAdmtdItemIEsCls;
typedef struct s1apProtIE_Field_E_RABAdmtdItemIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueE_RABAdmtdItemIEsCls value;
} SztProtIE_Field_E_RABAdmtdItemIEs;

/* Element ------------- ProtocolIE-SingleContainer ------------ */
typedef SztProtIE_Field_E_RABAdmtdItemIEs SztProtIE_SingleCont_E_RABAdmtdItemIEs;
typedef struct s1apProtIE_ContLst_E_RABAdmtdItemIEs
{
	TknU16 noComp;
	SztProtIE_SingleCont_E_RABAdmtdItemIEs *member;
}SztProtIE_ContLst_E_RABAdmtdItemIEs;

/* Element ------------- E-RAB-IE-ContainerList ------------ */
typedef SztProtIE_ContLst_E_RABAdmtdItemIEs SztE_RAB_IE_ContLst_E_RABAdmtdItemIEs;
/* Element ------------- E-RABAdmittedList ------------ */
typedef SztE_RAB_IE_ContLst_E_RABAdmtdItemIEs  SztE_RABAdmtdLst;
typedef struct s1ap_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls;
typedef struct s1apProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls extensionValue;
} SztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs;

typedef struct s1apProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs
{
	TknU16 noComp;
	SztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs *member;
}SztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs;

typedef struct s1apE_RABFailedToSetupItemHOReqAck
{
	TknPres pres;
	SztE_RAB_ID e_RAB_ID;
	SztCause cause;
	SztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs iE_Extns;
} SztE_RABFailedToSetupItemHOReqAck;

typedef struct s1ap_ValueE_RABFailedtoSetupItemHOReqAckIEsCls{
	union {
		SztE_RABFailedToSetupItemHOReqAck sztE_RABFailedToSetupItemHOReqAck;
	} u;
} Szt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls;
typedef struct s1apProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls value;
} SztProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs;

/* Element ------------- ProtocolIE-SingleContainer ------------ */
typedef SztProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs SztProtIE_SingleCont_E_RABFailedtoSetupItemHOReqAckIEs;
typedef struct s1apProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs
{
	TknU16 noComp;
	SztProtIE_SingleCont_E_RABFailedtoSetupItemHOReqAckIEs *member;
}SztProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs;

/* Element ------------- E-RAB-IE-ContainerList ------------ */
typedef SztProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs SztE_RAB_IE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs;
/* Element ------------- E-RABFailedtoSetupListHOReqAck ------------ */
typedef SztE_RAB_IE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs  SztE_RABFailedtoSetupLstHOReqAck;
typedef struct s1ap_ValueHovrRqstAckgIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztE_RABAdmtdLst sztE_RABAdmtdLst;
		SztE_RABFailedtoSetupLstHOReqAck sztE_RABFailedtoSetupLstHOReqAck;
		SztTget_ToSrc_TprntCont sztTget_ToSrc_TprntCont;
		SztCSG_Id sztCSG_Id;
		SztCriticalityDiag sztCriticalityDiag;
		SztCellAccessMode sztCellAccessMode;
	} u;
} Szt_ValueHovrRqstAckgIEsCls;
typedef struct s1apProtIE_Field_HovrRqstAckgIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueHovrRqstAckgIEsCls value;
} SztProtIE_Field_HovrRqstAckgIEs;

typedef struct s1apProtIE_Cont_HovrRqstAckgIEs
{
	TknU16 noComp;
	SztProtIE_Field_HovrRqstAckgIEs *member;
}SztProtIE_Cont_HovrRqstAckgIEs;

typedef struct s1apHovrRqstAckg
{
	TknPres pres;
	SztProtIE_Cont_HovrRqstAckgIEs protocolIEs;
} SztHovrRqstAckg;

typedef struct s1ap_ValueHovrFailIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztCause sztCause;
		SztCriticalityDiag sztCriticalityDiag;
	} u;
} Szt_ValueHovrFailIEsCls;
typedef struct s1apProtIE_Field_HovrFailIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueHovrFailIEsCls value;
} SztProtIE_Field_HovrFailIEs;

typedef struct s1apProtIE_Cont_HovrFailIEs
{
	TknU16 noComp;
	SztProtIE_Field_HovrFailIEs *member;
}SztProtIE_Cont_HovrFailIEs;

typedef struct s1apHovrFail
{
	TknPres pres;
	SztProtIE_Cont_HovrFailIEs protocolIEs;
} SztHovrFail;

typedef struct s1ap_ValueHovrNtfyIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztEUTRAN_CGI sztEUTRAN_CGI;
		SztTAI sztTAI;
		SztTunnelInform sztTunnelInform;
	} u;
} Szt_ValueHovrNtfyIEsCls;
typedef struct s1apProtIE_Field_HovrNtfyIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueHovrNtfyIEsCls value;
} SztProtIE_Field_HovrNtfyIEs;

typedef struct s1apProtIE_Cont_HovrNtfyIEs
{
	TknU16 noComp;
	SztProtIE_Field_HovrNtfyIEs *member;
}SztProtIE_Cont_HovrNtfyIEs;

typedef struct s1apHovrNtfy
{
	TknPres pres;
	SztProtIE_Cont_HovrNtfyIEs protocolIEs;
} SztHovrNtfy;

typedef struct s1ap_ExtnE_RABToBeSwedDLItem_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnE_RABToBeSwedDLItem_ExtIEsCls;
typedef struct s1apProtExtnField_E_RABToBeSwedDLItem_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnE_RABToBeSwedDLItem_ExtIEsCls extensionValue;
} SztProtExtnField_E_RABToBeSwedDLItem_ExtIEs;

typedef struct s1apProtExtnCont_E_RABToBeSwedDLItem_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_E_RABToBeSwedDLItem_ExtIEs *member;
}SztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs;

typedef struct s1apE_RABToBeSwedDLItem
{
	TknPres pres;
	SztE_RAB_ID e_RAB_ID;
	SztTportLyrAddr transportLyrAddr;
	SztGTP_TEID gTP_TEID;
	SztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs iE_Extns;
} SztE_RABToBeSwedDLItem;

typedef struct s1ap_ValueE_RABToBeSwedDLItemIEsCls{
	union {
		SztE_RABToBeSwedDLItem sztE_RABToBeSwedDLItem;
	} u;
} Szt_ValueE_RABToBeSwedDLItemIEsCls;
typedef struct s1apProtIE_Field_E_RABToBeSwedDLItemIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueE_RABToBeSwedDLItemIEsCls value;
} SztProtIE_Field_E_RABToBeSwedDLItemIEs;

/* Element ------------- ProtocolIE-SingleContainer ------------ */
typedef SztProtIE_Field_E_RABToBeSwedDLItemIEs SztProtIE_SingleCont_E_RABToBeSwedDLItemIEs;
typedef struct s1apProtIE_ContLst_E_RABToBeSwedDLItemIEs
{
	TknU16 noComp;
	SztProtIE_SingleCont_E_RABToBeSwedDLItemIEs *member;
}SztProtIE_ContLst_E_RABToBeSwedDLItemIEs;

/* Element ------------- E-RAB-IE-ContainerList ------------ */
typedef SztProtIE_ContLst_E_RABToBeSwedDLItemIEs SztE_RAB_IE_ContLst_E_RABToBeSwedDLItemIEs;
/* Element ------------- E-RABToBeSwitchedDLList ------------ */
typedef SztE_RAB_IE_ContLst_E_RABToBeSwedDLItemIEs  SztE_RABToBeSwedDLLst;
typedef struct s1ap_ValuePathSwRqstIEsCls{
	union {
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztE_RABToBeSwedDLLst sztE_RABToBeSwedDLLst;
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztEUTRAN_CGI sztEUTRAN_CGI;
		SztTAI sztTAI;
		SztUESecurCapabilities sztUESecurCapabilities;
		SztCSG_Id sztCSG_Id;
		SztCellAccessMode sztCellAccessMode;
		SztGUMMEI sztGUMMEI;
		SztCSGMembershipStatus sztCSGMembershipStatus;
		SztTunnelInform sztTunnelInform;
	} u;
} Szt_ValuePathSwRqstIEsCls;
typedef struct s1apProtIE_Field_PathSwRqstIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValuePathSwRqstIEsCls value;
} SztProtIE_Field_PathSwRqstIEs;

typedef struct s1apProtIE_Cont_PathSwRqstIEs
{
	TknU16 noComp;
	SztProtIE_Field_PathSwRqstIEs *member;
}SztProtIE_Cont_PathSwRqstIEs;

typedef struct s1apPathSwRqst
{
	TknPres pres;
	SztProtIE_Cont_PathSwRqstIEs protocolIEs;
} SztPathSwRqst;

typedef struct s1ap_ExtnE_RABToBeSwedULItem_ExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnE_RABToBeSwedULItem_ExtIEsCls;
typedef struct s1apProtExtnField_E_RABToBeSwedULItem_ExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnE_RABToBeSwedULItem_ExtIEsCls extensionValue;
} SztProtExtnField_E_RABToBeSwedULItem_ExtIEs;

typedef struct s1apProtExtnCont_E_RABToBeSwedULItem_ExtIEs
{
	TknU16 noComp;
	SztProtExtnField_E_RABToBeSwedULItem_ExtIEs *member;
}SztProtExtnCont_E_RABToBeSwedULItem_ExtIEs;

typedef struct s1apE_RABToBeSwedULItem
{
	TknPres pres;
	SztE_RAB_ID e_RAB_ID;
	SztTportLyrAddr transportLyrAddr;
	SztGTP_TEID gTP_TEID;
	SztProtExtnCont_E_RABToBeSwedULItem_ExtIEs iE_Extns;
} SztE_RABToBeSwedULItem;

typedef struct s1ap_ValueE_RABToBeSwedULItemIEsCls{
	union {
		SztE_RABToBeSwedULItem sztE_RABToBeSwedULItem;
	} u;
} Szt_ValueE_RABToBeSwedULItemIEsCls;
typedef struct s1apProtIE_Field_E_RABToBeSwedULItemIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueE_RABToBeSwedULItemIEsCls value;
} SztProtIE_Field_E_RABToBeSwedULItemIEs;

/* Element ------------- ProtocolIE-SingleContainer ------------ */
typedef SztProtIE_Field_E_RABToBeSwedULItemIEs SztProtIE_SingleCont_E_RABToBeSwedULItemIEs;
typedef struct s1apProtIE_ContLst_E_RABToBeSwedULItemIEs
{
	TknU16 noComp;
	SztProtIE_SingleCont_E_RABToBeSwedULItemIEs *member;
}SztProtIE_ContLst_E_RABToBeSwedULItemIEs;

/* Element ------------- E-RAB-IE-ContainerList ------------ */
typedef SztProtIE_ContLst_E_RABToBeSwedULItemIEs SztE_RAB_IE_ContLst_E_RABToBeSwedULItemIEs;
/* Element ------------- E-RABToBeSwitchedULList ------------ */
typedef SztE_RAB_IE_ContLst_E_RABToBeSwedULItemIEs  SztE_RABToBeSwedULLst;
typedef struct s1ap_ValuePathSwRqstAckgIEsCls{
	union {
		SztMME_UE_S1AP_ID sztid_MME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztUEAggMaxBitrate sztUEAggMaxBitrate;
		SztE_RABToBeSwedULLst sztE_RABToBeSwedULLst;
		SztE_RABLst sztE_RABLst;
		SztSecurCntxt sztSecurCntxt;
		SztCriticalityDiag sztCriticalityDiag;
		SztMME_UE_S1AP_ID sztid_MME_UE_S1AP_ID_2;
		SztCSGMembershipStatus sztCSGMembershipStatus;
	} u;
} Szt_ValuePathSwRqstAckgIEsCls;
typedef struct s1apProtIE_Field_PathSwRqstAckgIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValuePathSwRqstAckgIEsCls value;
} SztProtIE_Field_PathSwRqstAckgIEs;

typedef struct s1apProtIE_Cont_PathSwRqstAckgIEs
{
	TknU16 noComp;
	SztProtIE_Field_PathSwRqstAckgIEs *member;
}SztProtIE_Cont_PathSwRqstAckgIEs;

typedef struct s1apPathSwRqstAckg
{
	TknPres pres;
	SztProtIE_Cont_PathSwRqstAckgIEs protocolIEs;
} SztPathSwRqstAckg;

typedef struct s1ap_ValuePathSwRqstFailIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztCause sztCause;
		SztCriticalityDiag sztCriticalityDiag;
	} u;
} Szt_ValuePathSwRqstFailIEsCls;
typedef struct s1apProtIE_Field_PathSwRqstFailIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValuePathSwRqstFailIEsCls value;
} SztProtIE_Field_PathSwRqstFailIEs;

typedef struct s1apProtIE_Cont_PathSwRqstFailIEs
{
	TknU16 noComp;
	SztProtIE_Field_PathSwRqstFailIEs *member;
}SztProtIE_Cont_PathSwRqstFailIEs;

typedef struct s1apPathSwRqstFail
{
	TknPres pres;
	SztProtIE_Cont_PathSwRqstFailIEs protocolIEs;
} SztPathSwRqstFail;

typedef struct s1ap_ValueHovrCancelIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztCause sztCause;
	} u;
} Szt_ValueHovrCancelIEsCls;
typedef struct s1apProtIE_Field_HovrCancelIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueHovrCancelIEsCls value;
} SztProtIE_Field_HovrCancelIEs;

typedef struct s1apProtIE_Cont_HovrCancelIEs
{
	TknU16 noComp;
	SztProtIE_Field_HovrCancelIEs *member;
}SztProtIE_Cont_HovrCancelIEs;

typedef struct s1apHovrCancel
{
	TknPres pres;
	SztProtIE_Cont_HovrCancelIEs protocolIEs;
} SztHovrCancel;

typedef struct s1ap_ValueHovrCancelAckgIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztCriticalityDiag sztCriticalityDiag;
	} u;
} Szt_ValueHovrCancelAckgIEsCls;
typedef struct s1apProtIE_Field_HovrCancelAckgIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueHovrCancelAckgIEsCls value;
} SztProtIE_Field_HovrCancelAckgIEs;

typedef struct s1apProtIE_Cont_HovrCancelAckgIEs
{
	TknU16 noComp;
	SztProtIE_Field_HovrCancelAckgIEs *member;
}SztProtIE_Cont_HovrCancelAckgIEs;

typedef struct s1apHovrCancelAckg
{
	TknPres pres;
	SztProtIE_Cont_HovrCancelAckgIEs protocolIEs;
} SztHovrCancelAckg;

typedef struct s1ap_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls{
	union {
		SztCorrelation_ID sztCorrelation_ID;
	} u;
} Szt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls;
typedef struct s1apProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls extensionValue;
} SztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs;

typedef struct s1apProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs
{
	TknU16 noComp;
	SztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs *member;
}SztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs;

typedef struct s1apE_RABToBeSetupItemBrSUReq
{
	TknPres pres;
	SztE_RAB_ID e_RAB_ID;
	SztE_RABLvlQoSParams e_RABlevelQoSParams;
	SztTportLyrAddr transportLyrAddr;
	SztGTP_TEID gTP_TEID;
	SztNAS_PDU nAS_PDU;
	SztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs iE_Extns;
} SztE_RABToBeSetupItemBrSUReq;

typedef struct s1ap_ValueE_RABToBeSetupItemBrSUReqIEsCls{
	union {
		SztE_RABToBeSetupItemBrSUReq sztE_RABToBeSetupItemBrSUReq;
	} u;
} Szt_ValueE_RABToBeSetupItemBrSUReqIEsCls;
typedef struct s1apProtIE_Field_E_RABToBeSetupItemBrSUReqIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueE_RABToBeSetupItemBrSUReqIEsCls value;
} SztProtIE_Field_E_RABToBeSetupItemBrSUReqIEs;

/* Element ------------- ProtocolIE-SingleContainer ------------ */
typedef SztProtIE_Field_E_RABToBeSetupItemBrSUReqIEs SztProtIE_SingleCont_E_RABToBeSetupItemBrSUReqIEs;
typedef struct s1apE_RABToBeSetupLstBrSUReq
{
	TknU16 noComp;
	SztProtIE_SingleCont_E_RABToBeSetupItemBrSUReqIEs *member;
}SztE_RABToBeSetupLstBrSUReq;

typedef struct s1ap_ValueE_RABSetupRqstIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztUEAggMaxBitrate sztUEAggMaxBitrate;
		SztE_RABToBeSetupLstBrSUReq sztE_RABToBeSetupLstBrSUReq;
	} u;
} Szt_ValueE_RABSetupRqstIEsCls;
typedef struct s1apProtIE_Field_E_RABSetupRqstIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueE_RABSetupRqstIEsCls value;
} SztProtIE_Field_E_RABSetupRqstIEs;

typedef struct s1apProtIE_Cont_E_RABSetupRqstIEs
{
	TknU16 noComp;
	SztProtIE_Field_E_RABSetupRqstIEs *member;
}SztProtIE_Cont_E_RABSetupRqstIEs;

typedef struct s1apE_RABSetupRqst
{
	TknPres pres;
	SztProtIE_Cont_E_RABSetupRqstIEs protocolIEs;
} SztE_RABSetupRqst;

typedef struct s1ap_ExtnE_RABSetupItemBrSUResExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnE_RABSetupItemBrSUResExtIEsCls;
typedef struct s1apProtExtnField_E_RABSetupItemBrSUResExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnE_RABSetupItemBrSUResExtIEsCls extensionValue;
} SztProtExtnField_E_RABSetupItemBrSUResExtIEs;

typedef struct s1apProtExtnCont_E_RABSetupItemBrSUResExtIEs
{
	TknU16 noComp;
	SztProtExtnField_E_RABSetupItemBrSUResExtIEs *member;
}SztProtExtnCont_E_RABSetupItemBrSUResExtIEs;

typedef struct s1apE_RABSetupItemBrSURes
{
	TknPres pres;
	SztE_RAB_ID e_RAB_ID;
	SztTportLyrAddr transportLyrAddr;
	SztGTP_TEID gTP_TEID;
	SztProtExtnCont_E_RABSetupItemBrSUResExtIEs iE_Extns;
} SztE_RABSetupItemBrSURes;

typedef struct s1ap_ValueE_RABSetupItemBrSUResIEsCls{
	union {
		SztE_RABSetupItemBrSURes sztE_RABSetupItemBrSURes;
	} u;
} Szt_ValueE_RABSetupItemBrSUResIEsCls;
typedef struct s1apProtIE_Field_E_RABSetupItemBrSUResIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueE_RABSetupItemBrSUResIEsCls value;
} SztProtIE_Field_E_RABSetupItemBrSUResIEs;

/* Element ------------- ProtocolIE-SingleContainer ------------ */
typedef SztProtIE_Field_E_RABSetupItemBrSUResIEs SztProtIE_SingleCont_E_RABSetupItemBrSUResIEs;
typedef struct s1apE_RABSetupLstBrSURes
{
	TknU16 noComp;
	SztProtIE_SingleCont_E_RABSetupItemBrSUResIEs *member;
}SztE_RABSetupLstBrSURes;

typedef struct s1ap_ValueE_RABSetupRespIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztE_RABSetupLstBrSURes sztE_RABSetupLstBrSURes;
		SztE_RABLst sztE_RABLst;
		SztCriticalityDiag sztCriticalityDiag;
	} u;
} Szt_ValueE_RABSetupRespIEsCls;
typedef struct s1apProtIE_Field_E_RABSetupRespIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueE_RABSetupRespIEsCls value;
} SztProtIE_Field_E_RABSetupRespIEs;

typedef struct s1apProtIE_Cont_E_RABSetupRespIEs
{
	TknU16 noComp;
	SztProtIE_Field_E_RABSetupRespIEs *member;
}SztProtIE_Cont_E_RABSetupRespIEs;

typedef struct s1apE_RABSetupResp
{
	TknPres pres;
	SztProtIE_Cont_E_RABSetupRespIEs protocolIEs;
} SztE_RABSetupResp;

typedef struct s1ap_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls;
typedef struct s1apProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls extensionValue;
} SztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs;

typedef struct s1apProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs
{
	TknU16 noComp;
	SztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs *member;
}SztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs;

typedef struct s1apE_RABToBeMdfdItemBrModReq
{
	TknPres pres;
	SztE_RAB_ID e_RAB_ID;
	SztE_RABLvlQoSParams e_RABLvlQoSParams;
	SztNAS_PDU nAS_PDU;
	SztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs iE_Extns;
} SztE_RABToBeMdfdItemBrModReq;

typedef struct s1ap_ValueE_RABToBeMdfdItemBrModReqIEsCls{
	union {
		SztE_RABToBeMdfdItemBrModReq sztE_RABToBeMdfdItemBrModReq;
	} u;
} Szt_ValueE_RABToBeMdfdItemBrModReqIEsCls;
typedef struct s1apProtIE_Field_E_RABToBeMdfdItemBrModReqIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueE_RABToBeMdfdItemBrModReqIEsCls value;
} SztProtIE_Field_E_RABToBeMdfdItemBrModReqIEs;

/* Element ------------- ProtocolIE-SingleContainer ------------ */
typedef SztProtIE_Field_E_RABToBeMdfdItemBrModReqIEs SztProtIE_SingleCont_E_RABToBeMdfdItemBrModReqIEs;
typedef struct s1apE_RABToBeMdfdLstBrModReq
{
	TknU16 noComp;
	SztProtIE_SingleCont_E_RABToBeMdfdItemBrModReqIEs *member;
}SztE_RABToBeMdfdLstBrModReq;

typedef struct s1ap_ValueE_RABMdfyRqstIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztUEAggMaxBitrate sztUEAggMaxBitrate;
		SztE_RABToBeMdfdLstBrModReq sztE_RABToBeMdfdLstBrModReq;
	} u;
} Szt_ValueE_RABMdfyRqstIEsCls;
typedef struct s1apProtIE_Field_E_RABMdfyRqstIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueE_RABMdfyRqstIEsCls value;
} SztProtIE_Field_E_RABMdfyRqstIEs;

typedef struct s1apProtIE_Cont_E_RABMdfyRqstIEs
{
	TknU16 noComp;
	SztProtIE_Field_E_RABMdfyRqstIEs *member;
}SztProtIE_Cont_E_RABMdfyRqstIEs;

typedef struct s1apE_RABMdfyRqst
{
	TknPres pres;
	SztProtIE_Cont_E_RABMdfyRqstIEs protocolIEs;
} SztE_RABMdfyRqst;

typedef struct s1ap_ExtnE_RABMdfyItemBrModResExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnE_RABMdfyItemBrModResExtIEsCls;
typedef struct s1apProtExtnField_E_RABMdfyItemBrModResExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnE_RABMdfyItemBrModResExtIEsCls extensionValue;
} SztProtExtnField_E_RABMdfyItemBrModResExtIEs;

typedef struct s1apProtExtnCont_E_RABMdfyItemBrModResExtIEs
{
	TknU16 noComp;
	SztProtExtnField_E_RABMdfyItemBrModResExtIEs *member;
}SztProtExtnCont_E_RABMdfyItemBrModResExtIEs;

typedef struct s1apE_RABMdfyItemBrModRes
{
	TknPres pres;
	SztE_RAB_ID e_RAB_ID;
	SztProtExtnCont_E_RABMdfyItemBrModResExtIEs iE_Extns;
} SztE_RABMdfyItemBrModRes;

typedef struct s1ap_ValueE_RABMdfyItemBrModResIEsCls{
	union {
		SztE_RABMdfyItemBrModRes sztE_RABMdfyItemBrModRes;
	} u;
} Szt_ValueE_RABMdfyItemBrModResIEsCls;
typedef struct s1apProtIE_Field_E_RABMdfyItemBrModResIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueE_RABMdfyItemBrModResIEsCls value;
} SztProtIE_Field_E_RABMdfyItemBrModResIEs;

/* Element ------------- ProtocolIE-SingleContainer ------------ */
typedef SztProtIE_Field_E_RABMdfyItemBrModResIEs SztProtIE_SingleCont_E_RABMdfyItemBrModResIEs;
typedef struct s1apE_RABMdfyLstBrModRes
{
	TknU16 noComp;
	SztProtIE_SingleCont_E_RABMdfyItemBrModResIEs *member;
}SztE_RABMdfyLstBrModRes;

typedef struct s1ap_ValueE_RABMdfyRespIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztE_RABMdfyLstBrModRes sztE_RABMdfyLstBrModRes;
		SztE_RABLst sztE_RABLst;
		SztCriticalityDiag sztCriticalityDiag;
	} u;
} Szt_ValueE_RABMdfyRespIEsCls;
typedef struct s1apProtIE_Field_E_RABMdfyRespIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueE_RABMdfyRespIEsCls value;
} SztProtIE_Field_E_RABMdfyRespIEs;

typedef struct s1apProtIE_Cont_E_RABMdfyRespIEs
{
	TknU16 noComp;
	SztProtIE_Field_E_RABMdfyRespIEs *member;
}SztProtIE_Cont_E_RABMdfyRespIEs;

typedef struct s1apE_RABMdfyResp
{
	TknPres pres;
	SztProtIE_Cont_E_RABMdfyRespIEs protocolIEs;
} SztE_RABMdfyResp;

typedef struct s1ap_ValueE_RABRlsCmmdIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztUEAggMaxBitrate sztUEAggMaxBitrate;
		SztE_RABLst sztE_RABLst;
		SztNAS_PDU sztNAS_PDU;
	} u;
} Szt_ValueE_RABRlsCmmdIEsCls;
typedef struct s1apProtIE_Field_E_RABRlsCmmdIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueE_RABRlsCmmdIEsCls value;
} SztProtIE_Field_E_RABRlsCmmdIEs;

typedef struct s1apProtIE_Cont_E_RABRlsCmmdIEs
{
	TknU16 noComp;
	SztProtIE_Field_E_RABRlsCmmdIEs *member;
}SztProtIE_Cont_E_RABRlsCmmdIEs;

typedef struct s1apE_RABRlsCmmd
{
	TknPres pres;
	SztProtIE_Cont_E_RABRlsCmmdIEs protocolIEs;
} SztE_RABRlsCmmd;

typedef struct s1ap_ExtnE_RABRlsItemBrRelCompExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnE_RABRlsItemBrRelCompExtIEsCls;
typedef struct s1apProtExtnField_E_RABRlsItemBrRelCompExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnE_RABRlsItemBrRelCompExtIEsCls extensionValue;
} SztProtExtnField_E_RABRlsItemBrRelCompExtIEs;

typedef struct s1apProtExtnCont_E_RABRlsItemBrRelCompExtIEs
{
	TknU16 noComp;
	SztProtExtnField_E_RABRlsItemBrRelCompExtIEs *member;
}SztProtExtnCont_E_RABRlsItemBrRelCompExtIEs;

typedef struct s1apE_RABRlsItemBrRelComp
{
	TknPres pres;
	SztE_RAB_ID e_RAB_ID;
	SztProtExtnCont_E_RABRlsItemBrRelCompExtIEs iE_Extns;
} SztE_RABRlsItemBrRelComp;

typedef struct s1ap_ValueE_RABRlsItemBrRelCompIEsCls{
	union {
		SztE_RABRlsItemBrRelComp sztE_RABRlsItemBrRelComp;
	} u;
} Szt_ValueE_RABRlsItemBrRelCompIEsCls;
typedef struct s1apProtIE_Field_E_RABRlsItemBrRelCompIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueE_RABRlsItemBrRelCompIEsCls value;
} SztProtIE_Field_E_RABRlsItemBrRelCompIEs;

/* Element ------------- ProtocolIE-SingleContainer ------------ */
typedef SztProtIE_Field_E_RABRlsItemBrRelCompIEs SztProtIE_SingleCont_E_RABRlsItemBrRelCompIEs;
typedef struct s1apE_RABRlsLstBrRelComp
{
	TknU16 noComp;
	SztProtIE_SingleCont_E_RABRlsItemBrRelCompIEs *member;
}SztE_RABRlsLstBrRelComp;

typedef struct s1ap_ValueE_RABRlsRespIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztE_RABRlsLstBrRelComp sztE_RABRlsLstBrRelComp;
		SztE_RABLst sztE_RABLst;
		SztCriticalityDiag sztCriticalityDiag;
	} u;
} Szt_ValueE_RABRlsRespIEsCls;
typedef struct s1apProtIE_Field_E_RABRlsRespIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueE_RABRlsRespIEsCls value;
} SztProtIE_Field_E_RABRlsRespIEs;

typedef struct s1apProtIE_Cont_E_RABRlsRespIEs
{
	TknU16 noComp;
	SztProtIE_Field_E_RABRlsRespIEs *member;
}SztProtIE_Cont_E_RABRlsRespIEs;

typedef struct s1apE_RABRlsResp
{
	TknPres pres;
	SztProtIE_Cont_E_RABRlsRespIEs protocolIEs;
} SztE_RABRlsResp;

typedef struct s1ap_ValueE_RABRlsIndIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztE_RABLst sztE_RABLst;
	} u;
} Szt_ValueE_RABRlsIndIEsCls;
typedef struct s1apProtIE_Field_E_RABRlsIndIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueE_RABRlsIndIEsCls value;
} SztProtIE_Field_E_RABRlsIndIEs;

typedef struct s1apProtIE_Cont_E_RABRlsIndIEs
{
	TknU16 noComp;
	SztProtIE_Field_E_RABRlsIndIEs *member;
}SztProtIE_Cont_E_RABRlsIndIEs;

typedef struct s1apE_RABRlsInd
{
	TknPres pres;
	SztProtIE_Cont_E_RABRlsIndIEs protocolIEs;
} SztE_RABRlsInd;

typedef struct s1ap_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls{
	union {
		SztCorrelation_ID sztCorrelation_ID;
	} u;
} Szt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls;
typedef struct s1apProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls extensionValue;
} SztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs;

typedef struct s1apProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs
{
	TknU16 noComp;
	SztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs *member;
}SztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs;

typedef struct s1apE_RABToBeSetupItemCtxtSUReq
{
	TknPres pres;
	SztE_RAB_ID e_RAB_ID;
	SztE_RABLvlQoSParams e_RABlevelQoSParams;
	SztTportLyrAddr transportLyrAddr;
	SztGTP_TEID gTP_TEID;
	SztNAS_PDU nAS_PDU;
	SztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs iE_Extns;
} SztE_RABToBeSetupItemCtxtSUReq;

typedef struct s1ap_ValueE_RABToBeSetupItemCtxtSUReqIEsCls{
	union {
		SztE_RABToBeSetupItemCtxtSUReq sztE_RABToBeSetupItemCtxtSUReq;
	} u;
} Szt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls;
typedef struct s1apProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls value;
} SztProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs;

/* Element ------------- ProtocolIE-SingleContainer ------------ */
typedef SztProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs SztProtIE_SingleCont_E_RABToBeSetupItemCtxtSUReqIEs;
typedef struct s1apE_RABToBeSetupLstCtxtSUReq
{
	TknU16 noComp;
	SztProtIE_SingleCont_E_RABToBeSetupItemCtxtSUReqIEs *member;
}SztE_RABToBeSetupLstCtxtSUReq;

typedef struct s1ap_ValueInitCntxtSetupRqstIEsCls{
	union {
		SztMME_UE_S1AP_ID sztid_MME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztUEAggMaxBitrate sztUEAggMaxBitrate;
		SztE_RABToBeSetupLstCtxtSUReq sztE_RABToBeSetupLstCtxtSUReq;
		SztUESecurCapabilities sztUESecurCapabilities;
		SztSecurKey sztSecurKey;
		SztTraceActvn sztTraceActvn;
		SztHovrRestrnLst sztHovrRestrnLst;
		SztUERadioCapblty sztUERadioCapblty;
		SztSubscriberProfileIDforRFP sztSubscriberProfileIDforRFP;
		SztCSFallbackIndicator sztCSFallbackIndicator;
		SztSRVCCOperationPossible sztSRVCCOperationPossible;
		SztCSGMembershipStatus sztCSGMembershipStatus;
		SztLAI sztLAI;
		SztGUMMEI sztGUMMEI;
		SztMME_UE_S1AP_ID sztid_MME_UE_S1AP_ID_2;
		SztManagementBasedMDTAllowed sztManagementBasedMDTAllowed;
		SztMDTPLMNLst sztMDTPLMNLst;
	} u;
} Szt_ValueInitCntxtSetupRqstIEsCls;
typedef struct s1apProtIE_Field_InitCntxtSetupRqstIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueInitCntxtSetupRqstIEsCls value;
} SztProtIE_Field_InitCntxtSetupRqstIEs;

typedef struct s1apProtIE_Cont_InitCntxtSetupRqstIEs
{
	TknU16 noComp;
	SztProtIE_Field_InitCntxtSetupRqstIEs *member;
}SztProtIE_Cont_InitCntxtSetupRqstIEs;

typedef struct s1apInitCntxtSetupRqst
{
	TknPres pres;
	SztProtIE_Cont_InitCntxtSetupRqstIEs protocolIEs;
} SztInitCntxtSetupRqst;

typedef struct s1ap_ExtnE_RABSetupItemCtxtSUResExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnE_RABSetupItemCtxtSUResExtIEsCls;
typedef struct s1apProtExtnField_E_RABSetupItemCtxtSUResExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnE_RABSetupItemCtxtSUResExtIEsCls extensionValue;
} SztProtExtnField_E_RABSetupItemCtxtSUResExtIEs;

typedef struct s1apProtExtnCont_E_RABSetupItemCtxtSUResExtIEs
{
	TknU16 noComp;
	SztProtExtnField_E_RABSetupItemCtxtSUResExtIEs *member;
}SztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs;

typedef struct s1apE_RABSetupItemCtxtSURes
{
	TknPres pres;
	SztE_RAB_ID e_RAB_ID;
	SztTportLyrAddr transportLyrAddr;
	SztGTP_TEID gTP_TEID;
	SztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs iE_Extns;
} SztE_RABSetupItemCtxtSURes;

typedef struct s1ap_ValueE_RABSetupItemCtxtSUResIEsCls{
	union {
		SztE_RABSetupItemCtxtSURes sztE_RABSetupItemCtxtSURes;
	} u;
} Szt_ValueE_RABSetupItemCtxtSUResIEsCls;
typedef struct s1apProtIE_Field_E_RABSetupItemCtxtSUResIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueE_RABSetupItemCtxtSUResIEsCls value;
} SztProtIE_Field_E_RABSetupItemCtxtSUResIEs;

/* Element ------------- ProtocolIE-SingleContainer ------------ */
typedef SztProtIE_Field_E_RABSetupItemCtxtSUResIEs SztProtIE_SingleCont_E_RABSetupItemCtxtSUResIEs;
typedef struct s1apE_RABSetupLstCtxtSURes
{
	TknU16 noComp;
	SztProtIE_SingleCont_E_RABSetupItemCtxtSUResIEs *member;
}SztE_RABSetupLstCtxtSURes;

typedef struct s1ap_ValueInitCntxtSetupRespIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztE_RABSetupLstCtxtSURes sztE_RABSetupLstCtxtSURes;
		SztE_RABLst sztE_RABLst;
		SztCriticalityDiag sztCriticalityDiag;
	} u;
} Szt_ValueInitCntxtSetupRespIEsCls;
typedef struct s1apProtIE_Field_InitCntxtSetupRespIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueInitCntxtSetupRespIEsCls value;
} SztProtIE_Field_InitCntxtSetupRespIEs;

typedef struct s1apProtIE_Cont_InitCntxtSetupRespIEs
{
	TknU16 noComp;
	SztProtIE_Field_InitCntxtSetupRespIEs *member;
}SztProtIE_Cont_InitCntxtSetupRespIEs;

typedef struct s1apInitCntxtSetupResp
{
	TknPres pres;
	SztProtIE_Cont_InitCntxtSetupRespIEs protocolIEs;
} SztInitCntxtSetupResp;

typedef struct s1ap_ValueInitCntxtSetupFailIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztCause sztCause;
		SztCriticalityDiag sztCriticalityDiag;
	} u;
} Szt_ValueInitCntxtSetupFailIEsCls;
typedef struct s1apProtIE_Field_InitCntxtSetupFailIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueInitCntxtSetupFailIEsCls value;
} SztProtIE_Field_InitCntxtSetupFailIEs;

typedef struct s1apProtIE_Cont_InitCntxtSetupFailIEs
{
	TknU16 noComp;
	SztProtIE_Field_InitCntxtSetupFailIEs *member;
}SztProtIE_Cont_InitCntxtSetupFailIEs;

typedef struct s1apInitCntxtSetupFail
{
	TknPres pres;
	SztProtIE_Cont_InitCntxtSetupFailIEs protocolIEs;
} SztInitCntxtSetupFail;

typedef struct s1ap_ExtnTAIItemExtIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ExtnTAIItemExtIEsCls;
typedef struct s1apProtExtnField_TAIItemExtIEs
{
	TknPres pres;
	SztProtExtnID id;
	SztCriticality criticality;
	Szt_ExtnTAIItemExtIEsCls extensionValue;
} SztProtExtnField_TAIItemExtIEs;

typedef struct s1apProtExtnCont_TAIItemExtIEs
{
	TknU16 noComp;
	SztProtExtnField_TAIItemExtIEs *member;
}SztProtExtnCont_TAIItemExtIEs;

typedef struct s1apTAIItem
{
	TknPres pres;
	SztTAI tAI;
	SztProtExtnCont_TAIItemExtIEs iE_Extns;
} SztTAIItem;

typedef struct s1ap_ValueTAIItemIEsCls{
	union {
		SztTAIItem sztTAIItem;
	} u;
} Szt_ValueTAIItemIEsCls;
typedef struct s1apProtIE_Field_TAIItemIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueTAIItemIEsCls value;
} SztProtIE_Field_TAIItemIEs;

/* Element ------------- ProtocolIE-SingleContainer ------------ */
typedef SztProtIE_Field_TAIItemIEs SztProtIE_SingleCont_TAIItemIEs;
typedef struct s1apTAILst
{
	TknU16 noComp;
	SztProtIE_SingleCont_TAIItemIEs *member;
}SztTAILst;

typedef struct s1ap_ValuePagIEsCls{
	union {
		SztUEIdentityIdxValue sztUEIdentityIdxValue;
		SztUEPagID sztUEPagID;
		SztPagDRX sztPagDRX;
		SztCNDomain sztCNDomain;
		SztTAILst sztTAILst;
		SztCSG_IdLst sztCSG_IdLst;
		SztPagPriority sztPagPriority;
	} u;
} Szt_ValuePagIEsCls;
typedef struct s1apProtIE_Field_PagIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValuePagIEsCls value;
} SztProtIE_Field_PagIEs;

typedef struct s1apProtIE_Cont_PagIEs
{
	TknU16 noComp;
	SztProtIE_Field_PagIEs *member;
}SztProtIE_Cont_PagIEs;

typedef struct s1apPag
{
	TknPres pres;
	SztProtIE_Cont_PagIEs protocolIEs;
} SztPag;

typedef struct s1ap_ValueUECntxtRlsRqst_IEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztCause sztCause;
		SztGWCntxtRlsInd sztGWCntxtRlsInd;
	} u;
} Szt_ValueUECntxtRlsRqst_IEsCls;
typedef struct s1apProtIE_Field_UECntxtRlsRqst_IEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueUECntxtRlsRqst_IEsCls value;
} SztProtIE_Field_UECntxtRlsRqst_IEs;

typedef struct s1apProtIE_Cont_UECntxtRlsRqst_IEs
{
	TknU16 noComp;
	SztProtIE_Field_UECntxtRlsRqst_IEs *member;
}SztProtIE_Cont_UECntxtRlsRqst_IEs;

typedef struct s1apUECntxtRlsRqst
{
	TknPres pres;
	SztProtIE_Cont_UECntxtRlsRqst_IEs protocolIEs;
} SztUECntxtRlsRqst;

typedef struct s1ap_ValueUECntxtRlsCmmd_IEsCls{
	union {
		SztUE_S1AP_IDs sztUE_S1AP_IDs;
		SztCause sztCause;
	} u;
} Szt_ValueUECntxtRlsCmmd_IEsCls;
typedef struct s1apProtIE_Field_UECntxtRlsCmmd_IEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueUECntxtRlsCmmd_IEsCls value;
} SztProtIE_Field_UECntxtRlsCmmd_IEs;

typedef struct s1apProtIE_Cont_UECntxtRlsCmmd_IEs
{
	TknU16 noComp;
	SztProtIE_Field_UECntxtRlsCmmd_IEs *member;
}SztProtIE_Cont_UECntxtRlsCmmd_IEs;

typedef struct s1apUECntxtRlsCmmd
{
	TknPres pres;
	SztProtIE_Cont_UECntxtRlsCmmd_IEs protocolIEs;
} SztUECntxtRlsCmmd;

typedef struct s1ap_ValueUECntxtRlsComplete_IEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztCriticalityDiag sztCriticalityDiag;
	} u;
} Szt_ValueUECntxtRlsComplete_IEsCls;
typedef struct s1apProtIE_Field_UECntxtRlsComplete_IEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueUECntxtRlsComplete_IEsCls value;
} SztProtIE_Field_UECntxtRlsComplete_IEs;

typedef struct s1apProtIE_Cont_UECntxtRlsComplete_IEs
{
	TknU16 noComp;
	SztProtIE_Field_UECntxtRlsComplete_IEs *member;
}SztProtIE_Cont_UECntxtRlsComplete_IEs;

typedef struct s1apUECntxtRlsComplete
{
	TknPres pres;
	SztProtIE_Cont_UECntxtRlsComplete_IEs protocolIEs;
} SztUECntxtRlsComplete;

typedef struct s1ap_ValueUECntxtModificationRqstIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztSecurKey sztSecurKey;
		SztSubscriberProfileIDforRFP sztSubscriberProfileIDforRFP;
		SztUEAggMaxBitrate sztUEAggMaxBitrate;
		SztCSFallbackIndicator sztCSFallbackIndicator;
		SztUESecurCapabilities sztUESecurCapabilities;
		SztCSGMembershipStatus sztCSGMembershipStatus;
		SztLAI sztLAI;
	} u;
} Szt_ValueUECntxtModificationRqstIEsCls;
typedef struct s1apProtIE_Field_UECntxtModificationRqstIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueUECntxtModificationRqstIEsCls value;
} SztProtIE_Field_UECntxtModificationRqstIEs;

typedef struct s1apProtIE_Cont_UECntxtModificationRqstIEs
{
	TknU16 noComp;
	SztProtIE_Field_UECntxtModificationRqstIEs *member;
}SztProtIE_Cont_UECntxtModificationRqstIEs;

typedef struct s1apUECntxtModificationRqst
{
	TknPres pres;
	SztProtIE_Cont_UECntxtModificationRqstIEs protocolIEs;
} SztUECntxtModificationRqst;

typedef struct s1ap_ValueUECntxtModificationRespIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztCriticalityDiag sztCriticalityDiag;
	} u;
} Szt_ValueUECntxtModificationRespIEsCls;
typedef struct s1apProtIE_Field_UECntxtModificationRespIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueUECntxtModificationRespIEsCls value;
} SztProtIE_Field_UECntxtModificationRespIEs;

typedef struct s1apProtIE_Cont_UECntxtModificationRespIEs
{
	TknU16 noComp;
	SztProtIE_Field_UECntxtModificationRespIEs *member;
}SztProtIE_Cont_UECntxtModificationRespIEs;

typedef struct s1apUECntxtModificationResp
{
	TknPres pres;
	SztProtIE_Cont_UECntxtModificationRespIEs protocolIEs;
} SztUECntxtModificationResp;

typedef struct s1ap_ValueUECntxtModificationFailIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztCause sztCause;
		SztCriticalityDiag sztCriticalityDiag;
	} u;
} Szt_ValueUECntxtModificationFailIEsCls;
typedef struct s1apProtIE_Field_UECntxtModificationFailIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueUECntxtModificationFailIEsCls value;
} SztProtIE_Field_UECntxtModificationFailIEs;

typedef struct s1apProtIE_Cont_UECntxtModificationFailIEs
{
	TknU16 noComp;
	SztProtIE_Field_UECntxtModificationFailIEs *member;
}SztProtIE_Cont_UECntxtModificationFailIEs;

typedef struct s1apUECntxtModificationFail
{
	TknPres pres;
	SztProtIE_Cont_UECntxtModificationFailIEs protocolIEs;
} SztUECntxtModificationFail;

typedef struct s1ap_ValueUERadioCapbltyMatchRqstIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztUERadioCapblty sztUERadioCapblty;
	} u;
} Szt_ValueUERadioCapbltyMatchRqstIEsCls;
typedef struct s1apProtIE_Field_UERadioCapbltyMatchRqstIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueUERadioCapbltyMatchRqstIEsCls value;
} SztProtIE_Field_UERadioCapbltyMatchRqstIEs;

typedef struct s1apProtIE_Cont_UERadioCapbltyMatchRqstIEs
{
	TknU16 noComp;
	SztProtIE_Field_UERadioCapbltyMatchRqstIEs *member;
}SztProtIE_Cont_UERadioCapbltyMatchRqstIEs;

typedef struct s1apUERadioCapbltyMatchRqst
{
	TknPres pres;
	SztProtIE_Cont_UERadioCapbltyMatchRqstIEs protocolIEs;
} SztUERadioCapbltyMatchRqst;

typedef struct s1ap_ValueUERadioCapbltyMatchRespIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztVoiceSupportMatchIndicator sztVoiceSupportMatchIndicator;
		SztCriticalityDiag sztCriticalityDiag;
	} u;
} Szt_ValueUERadioCapbltyMatchRespIEsCls;
typedef struct s1apProtIE_Field_UERadioCapbltyMatchRespIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueUERadioCapbltyMatchRespIEsCls value;
} SztProtIE_Field_UERadioCapbltyMatchRespIEs;

typedef struct s1apProtIE_Cont_UERadioCapbltyMatchRespIEs
{
	TknU16 noComp;
	SztProtIE_Field_UERadioCapbltyMatchRespIEs *member;
}SztProtIE_Cont_UERadioCapbltyMatchRespIEs;

typedef struct s1apUERadioCapbltyMatchResp
{
	TknPres pres;
	SztProtIE_Cont_UERadioCapbltyMatchRespIEs protocolIEs;
} SztUERadioCapbltyMatchResp;

typedef struct s1ap_ValueDlnkNASTport_IEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztNAS_PDU sztNAS_PDU;
		SztHovrRestrnLst sztHovrRestrnLst;
		SztSubscriberProfileIDforRFP sztSubscriberProfileIDforRFP;
	} u;
} Szt_ValueDlnkNASTport_IEsCls;
typedef struct s1apProtIE_Field_DlnkNASTport_IEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueDlnkNASTport_IEsCls value;
} SztProtIE_Field_DlnkNASTport_IEs;

typedef struct s1apProtIE_Cont_DlnkNASTport_IEs
{
	TknU16 noComp;
	SztProtIE_Field_DlnkNASTport_IEs *member;
}SztProtIE_Cont_DlnkNASTport_IEs;

typedef struct s1apDlnkNASTport
{
	TknPres pres;
	SztProtIE_Cont_DlnkNASTport_IEs protocolIEs;
} SztDlnkNASTport;

typedef struct s1ap_ValueInitUEMsg_IEsCls{
	union {
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztNAS_PDU sztNAS_PDU;
		SztTAI sztTAI;
		SztEUTRAN_CGI sztEUTRAN_CGI;
		SztRRC_Establishment_Cause sztRRC_Establishment_Cause;
		SztS_TMSI sztS_TMSI;
		SztCSG_Id sztCSG_Id;
		SztGUMMEI sztGUMMEI;
		SztCellAccessMode sztCellAccessMode;
		SztTportLyrAddr sztTportLyrAddr;
		SztRelayNode_Indicator sztRelayNode_Indicator;
		SztGUMMEITyp sztGUMMEITyp;
		SztTunnelInform sztTunnelInform;
	} u;
} Szt_ValueInitUEMsg_IEsCls;
typedef struct s1apProtIE_Field_InitUEMsg_IEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueInitUEMsg_IEsCls value;
} SztProtIE_Field_InitUEMsg_IEs;

typedef struct s1apProtIE_Cont_InitUEMsg_IEs
{
	TknU16 noComp;
	SztProtIE_Field_InitUEMsg_IEs *member;
}SztProtIE_Cont_InitUEMsg_IEs;

typedef struct s1apInitUEMsg
{
	TknPres pres;
	SztProtIE_Cont_InitUEMsg_IEs protocolIEs;
} SztInitUEMsg;

typedef struct s1ap_ValueUlnkNASTport_IEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztNAS_PDU sztNAS_PDU;
		SztEUTRAN_CGI sztEUTRAN_CGI;
		SztTAI sztTAI;
		SztTportLyrAddr sztTportLyrAddr;
	} u;
} Szt_ValueUlnkNASTport_IEsCls;
typedef struct s1apProtIE_Field_UlnkNASTport_IEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueUlnkNASTport_IEsCls value;
} SztProtIE_Field_UlnkNASTport_IEs;

typedef struct s1apProtIE_Cont_UlnkNASTport_IEs
{
	TknU16 noComp;
	SztProtIE_Field_UlnkNASTport_IEs *member;
}SztProtIE_Cont_UlnkNASTport_IEs;

typedef struct s1apUlnkNASTport
{
	TknPres pres;
	SztProtIE_Cont_UlnkNASTport_IEs protocolIEs;
} SztUlnkNASTport;

typedef struct s1ap_ValueNASNonDlvryInd_IEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztNAS_PDU sztNAS_PDU;
		SztCause sztCause;
	} u;
} Szt_ValueNASNonDlvryInd_IEsCls;
typedef struct s1apProtIE_Field_NASNonDlvryInd_IEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueNASNonDlvryInd_IEsCls value;
} SztProtIE_Field_NASNonDlvryInd_IEs;

typedef struct s1apProtIE_Cont_NASNonDlvryInd_IEs
{
	TknU16 noComp;
	SztProtIE_Field_NASNonDlvryInd_IEs *member;
}SztProtIE_Cont_NASNonDlvryInd_IEs;

typedef struct s1apNASNonDlvryInd
{
	TknPres pres;
	SztProtIE_Cont_NASNonDlvryInd_IEs protocolIEs;
} SztNASNonDlvryInd;

/* Element ----- ResetAll ------- */
typedef enum enumSztResetAll
{
	SztResetAllreset_allEnum
} EnumSztResetAll;
typedef TknU32 SztResetAll;

typedef struct s1ap_ValueUE_assocLogS1_ConItemResCls{
	union {
		SztUE_assocLogS1_ConItem sztUE_assocLogS1_ConItem;
	} u;
} Szt_ValueUE_assocLogS1_ConItemResCls;
typedef struct s1apProtIE_Field_UE_assocLogS1_ConItemRes
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueUE_assocLogS1_ConItemResCls value;
} SztProtIE_Field_UE_assocLogS1_ConItemRes;

/* Element ------------- ProtocolIE-SingleContainer ------------ */
typedef SztProtIE_Field_UE_assocLogS1_ConItemRes SztProtIE_SingleCont_UE_assocLogS1_ConItemRes;
typedef struct s1apUE_assocLogS1_ConLstRes
{
	TknU16 noComp;
	SztProtIE_SingleCont_UE_assocLogS1_ConItemRes *member;
}SztUE_assocLogS1_ConLstRes;

typedef struct s1apResetTyp
{
	TknU8 choice;
	union {
		SztResetAll s1_Intf;
		SztUE_assocLogS1_ConLstRes partOfS1_Intf;
	} val;
} SztResetTyp;

typedef struct s1ap_ValueResetIEsCls{
	union {
		SztCause sztCause;
		SztResetTyp sztResetTyp;
	} u;
} Szt_ValueResetIEsCls;
typedef struct s1apProtIE_Field_ResetIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueResetIEsCls value;
} SztProtIE_Field_ResetIEs;

typedef struct s1apProtIE_Cont_ResetIEs
{
	TknU16 noComp;
	SztProtIE_Field_ResetIEs *member;
}SztProtIE_Cont_ResetIEs;

typedef struct s1apReset
{
	TknPres pres;
	SztProtIE_Cont_ResetIEs protocolIEs;
} SztReset;

typedef struct s1ap_ValueUE_assocLogS1_ConItemResAckCls{
	union {
		SztUE_assocLogS1_ConItem sztUE_assocLogS1_ConItem;
	} u;
} Szt_ValueUE_assocLogS1_ConItemResAckCls;
typedef struct s1apProtIE_Field_UE_assocLogS1_ConItemResAck
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueUE_assocLogS1_ConItemResAckCls value;
} SztProtIE_Field_UE_assocLogS1_ConItemResAck;

/* Element ------------- ProtocolIE-SingleContainer ------------ */
typedef SztProtIE_Field_UE_assocLogS1_ConItemResAck SztProtIE_SingleCont_UE_assocLogS1_ConItemResAck;
typedef struct s1apUE_assocLogS1_ConLstResAck
{
	TknU16 noComp;
	SztProtIE_SingleCont_UE_assocLogS1_ConItemResAck *member;
}SztUE_assocLogS1_ConLstResAck;

typedef struct s1ap_ValueResetAckgIEsCls{
	union {
		SztUE_assocLogS1_ConLstResAck sztUE_assocLogS1_ConLstResAck;
		SztCriticalityDiag sztCriticalityDiag;
	} u;
} Szt_ValueResetAckgIEsCls;
typedef struct s1apProtIE_Field_ResetAckgIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueResetAckgIEsCls value;
} SztProtIE_Field_ResetAckgIEs;

typedef struct s1apProtIE_Cont_ResetAckgIEs
{
	TknU16 noComp;
	SztProtIE_Field_ResetAckgIEs *member;
}SztProtIE_Cont_ResetAckgIEs;

typedef struct s1apResetAckg
{
	TknPres pres;
	SztProtIE_Cont_ResetAckgIEs protocolIEs;
} SztResetAckg;

typedef struct s1ap_ValueErrIndIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztCause sztCause;
		SztCriticalityDiag sztCriticalityDiag;
	} u;
} Szt_ValueErrIndIEsCls;
typedef struct s1apProtIE_Field_ErrIndIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueErrIndIEsCls value;
} SztProtIE_Field_ErrIndIEs;

typedef struct s1apProtIE_Cont_ErrIndIEs
{
	TknU16 noComp;
	SztProtIE_Field_ErrIndIEs *member;
}SztProtIE_Cont_ErrIndIEs;

typedef struct s1apErrInd
{
	TknPres pres;
	SztProtIE_Cont_ErrIndIEs protocolIEs;
} SztErrInd;

typedef struct s1ap_ValueS1SetupRqstIEsCls{
	union {
		SztGlobal_ENB_ID sztGlobal_ENB_ID;
		SztENBname sztENBname;
		SztSuppTAs sztSuppTAs;
		SztPagDRX sztPagDRX;
		SztCSG_IdLst sztCSG_IdLst;
	} u;
} Szt_ValueS1SetupRqstIEsCls;
typedef struct s1apProtIE_Field_S1SetupRqstIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueS1SetupRqstIEsCls value;
} SztProtIE_Field_S1SetupRqstIEs;

typedef struct s1apProtIE_Cont_S1SetupRqstIEs
{
	TknU16 noComp;
	SztProtIE_Field_S1SetupRqstIEs *member;
}SztProtIE_Cont_S1SetupRqstIEs;

typedef struct s1apS1SetupRqst
{
	TknPres pres;
	SztProtIE_Cont_S1SetupRqstIEs protocolIEs;
} SztS1SetupRqst;

typedef struct s1ap_ValueS1SetupRespIEsCls{
	union {
		SztMMEname sztMMEname;
		SztSrvdGUMMEIs sztSrvdGUMMEIs;
		SztRelativeMMECapacity sztRelativeMMECapacity;
		SztMMERelaySupportIndicator sztMMERelaySupportIndicator;
		SztCriticalityDiag sztCriticalityDiag;
	} u;
} Szt_ValueS1SetupRespIEsCls;
typedef struct s1apProtIE_Field_S1SetupRespIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueS1SetupRespIEsCls value;
} SztProtIE_Field_S1SetupRespIEs;

typedef struct s1apProtIE_Cont_S1SetupRespIEs
{
	TknU16 noComp;
	SztProtIE_Field_S1SetupRespIEs *member;
}SztProtIE_Cont_S1SetupRespIEs;

typedef struct s1apS1SetupResp
{
	TknPres pres;
	SztProtIE_Cont_S1SetupRespIEs protocolIEs;
} SztS1SetupResp;

typedef struct s1ap_ValueS1SetupFailIEsCls{
	union {
		SztCause sztCause;
		SztTimeToWait sztTimeToWait;
		SztCriticalityDiag sztCriticalityDiag;
	} u;
} Szt_ValueS1SetupFailIEsCls;
typedef struct s1apProtIE_Field_S1SetupFailIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueS1SetupFailIEsCls value;
} SztProtIE_Field_S1SetupFailIEs;

typedef struct s1apProtIE_Cont_S1SetupFailIEs
{
	TknU16 noComp;
	SztProtIE_Field_S1SetupFailIEs *member;
}SztProtIE_Cont_S1SetupFailIEs;

typedef struct s1apS1SetupFail
{
	TknPres pres;
	SztProtIE_Cont_S1SetupFailIEs protocolIEs;
} SztS1SetupFail;

typedef struct s1ap_ValueENBConfigUpdIEsCls{
	union {
		SztENBname sztENBname;
		SztSuppTAs sztSuppTAs;
		SztCSG_IdLst sztCSG_IdLst;
		SztPagDRX sztPagDRX;
	} u;
} Szt_ValueENBConfigUpdIEsCls;
typedef struct s1apProtIE_Field_ENBConfigUpdIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueENBConfigUpdIEsCls value;
} SztProtIE_Field_ENBConfigUpdIEs;

typedef struct s1apProtIE_Cont_ENBConfigUpdIEs
{
	TknU16 noComp;
	SztProtIE_Field_ENBConfigUpdIEs *member;
}SztProtIE_Cont_ENBConfigUpdIEs;

typedef struct s1apENBConfigUpd
{
	TknPres pres;
	SztProtIE_Cont_ENBConfigUpdIEs protocolIEs;
} SztENBConfigUpd;

typedef struct s1ap_ValueENBConfigUpdAckgIEsCls{
	union {
		SztCriticalityDiag sztCriticalityDiag;
	} u;
} Szt_ValueENBConfigUpdAckgIEsCls;
typedef struct s1apProtIE_Field_ENBConfigUpdAckgIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueENBConfigUpdAckgIEsCls value;
} SztProtIE_Field_ENBConfigUpdAckgIEs;

typedef struct s1apProtIE_Cont_ENBConfigUpdAckgIEs
{
	TknU16 noComp;
	SztProtIE_Field_ENBConfigUpdAckgIEs *member;
}SztProtIE_Cont_ENBConfigUpdAckgIEs;

typedef struct s1apENBConfigUpdAckg
{
	TknPres pres;
	SztProtIE_Cont_ENBConfigUpdAckgIEs protocolIEs;
} SztENBConfigUpdAckg;

typedef struct s1ap_ValueENBConfigUpdFailIEsCls{
	union {
		SztCause sztCause;
		SztTimeToWait sztTimeToWait;
		SztCriticalityDiag sztCriticalityDiag;
	} u;
} Szt_ValueENBConfigUpdFailIEsCls;
typedef struct s1apProtIE_Field_ENBConfigUpdFailIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueENBConfigUpdFailIEsCls value;
} SztProtIE_Field_ENBConfigUpdFailIEs;

typedef struct s1apProtIE_Cont_ENBConfigUpdFailIEs
{
	TknU16 noComp;
	SztProtIE_Field_ENBConfigUpdFailIEs *member;
}SztProtIE_Cont_ENBConfigUpdFailIEs;

typedef struct s1apENBConfigUpdFail
{
	TknPres pres;
	SztProtIE_Cont_ENBConfigUpdFailIEs protocolIEs;
} SztENBConfigUpdFail;

typedef struct s1ap_ValueMMEConfigUpdIEsCls{
	union {
		SztMMEname sztMMEname;
		SztSrvdGUMMEIs sztSrvdGUMMEIs;
		SztRelativeMMECapacity sztRelativeMMECapacity;
	} u;
} Szt_ValueMMEConfigUpdIEsCls;
typedef struct s1apProtIE_Field_MMEConfigUpdIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueMMEConfigUpdIEsCls value;
} SztProtIE_Field_MMEConfigUpdIEs;

typedef struct s1apProtIE_Cont_MMEConfigUpdIEs
{
	TknU16 noComp;
	SztProtIE_Field_MMEConfigUpdIEs *member;
}SztProtIE_Cont_MMEConfigUpdIEs;

typedef struct s1apMMEConfigUpd
{
	TknPres pres;
	SztProtIE_Cont_MMEConfigUpdIEs protocolIEs;
} SztMMEConfigUpd;

typedef struct s1ap_ValueMMEConfigUpdAckgIEsCls{
	union {
		SztCriticalityDiag sztCriticalityDiag;
	} u;
} Szt_ValueMMEConfigUpdAckgIEsCls;
typedef struct s1apProtIE_Field_MMEConfigUpdAckgIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueMMEConfigUpdAckgIEsCls value;
} SztProtIE_Field_MMEConfigUpdAckgIEs;

typedef struct s1apProtIE_Cont_MMEConfigUpdAckgIEs
{
	TknU16 noComp;
	SztProtIE_Field_MMEConfigUpdAckgIEs *member;
}SztProtIE_Cont_MMEConfigUpdAckgIEs;

typedef struct s1apMMEConfigUpdAckg
{
	TknPres pres;
	SztProtIE_Cont_MMEConfigUpdAckgIEs protocolIEs;
} SztMMEConfigUpdAckg;

typedef struct s1ap_ValueMMEConfigUpdFailIEsCls{
	union {
		SztCause sztCause;
		SztTimeToWait sztTimeToWait;
		SztCriticalityDiag sztCriticalityDiag;
	} u;
} Szt_ValueMMEConfigUpdFailIEsCls;
typedef struct s1apProtIE_Field_MMEConfigUpdFailIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueMMEConfigUpdFailIEsCls value;
} SztProtIE_Field_MMEConfigUpdFailIEs;

typedef struct s1apProtIE_Cont_MMEConfigUpdFailIEs
{
	TknU16 noComp;
	SztProtIE_Field_MMEConfigUpdFailIEs *member;
}SztProtIE_Cont_MMEConfigUpdFailIEs;

typedef struct s1apMMEConfigUpdFail
{
	TknPres pres;
	SztProtIE_Cont_MMEConfigUpdFailIEs protocolIEs;
} SztMMEConfigUpdFail;

typedef struct s1ap_ValueDlnkS1cdma2000tunnelingIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztE_RABSubjtoDataFwdingLst sztE_RABSubjtoDataFwdingLst;
		SztCdma2000HOStatus sztCdma2000HOStatus;
		SztCdma2000RATTyp sztCdma2000RATTyp;
		SztCdma2000PDU sztCdma2000PDU;
	} u;
} Szt_ValueDlnkS1cdma2000tunnelingIEsCls;
typedef struct s1apProtIE_Field_DlnkS1cdma2000tunnelingIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueDlnkS1cdma2000tunnelingIEsCls value;
} SztProtIE_Field_DlnkS1cdma2000tunnelingIEs;

typedef struct s1apProtIE_Cont_DlnkS1cdma2000tunnelingIEs
{
	TknU16 noComp;
	SztProtIE_Field_DlnkS1cdma2000tunnelingIEs *member;
}SztProtIE_Cont_DlnkS1cdma2000tunnelingIEs;

typedef struct s1apDlnkS1cdma2000tunneling
{
	TknPres pres;
	SztProtIE_Cont_DlnkS1cdma2000tunnelingIEs protocolIEs;
} SztDlnkS1cdma2000tunneling;

typedef struct s1ap_ValueUlnkS1cdma2000tunnelingIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztCdma2000RATTyp sztCdma2000RATTyp;
		SztCdma2000SectorID sztCdma2000SectorID;
		SztCdma2000HOReqdInd sztCdma2000HOReqdInd;
		SztCdma2000OneXSRVCCInfo sztCdma2000OneXSRVCCInfo;
		SztCdma2000OneXRAND sztCdma2000OneXRAND;
		SztCdma2000PDU sztCdma2000PDU;
		SztEUTRANRoundTripDelayEstimationInfo sztEUTRANRoundTripDelayEstimationInfo;
	} u;
} Szt_ValueUlnkS1cdma2000tunnelingIEsCls;
typedef struct s1apProtIE_Field_UlnkS1cdma2000tunnelingIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueUlnkS1cdma2000tunnelingIEsCls value;
} SztProtIE_Field_UlnkS1cdma2000tunnelingIEs;

typedef struct s1apProtIE_Cont_UlnkS1cdma2000tunnelingIEs
{
	TknU16 noComp;
	SztProtIE_Field_UlnkS1cdma2000tunnelingIEs *member;
}SztProtIE_Cont_UlnkS1cdma2000tunnelingIEs;

typedef struct s1apUlnkS1cdma2000tunneling
{
	TknPres pres;
	SztProtIE_Cont_UlnkS1cdma2000tunnelingIEs protocolIEs;
} SztUlnkS1cdma2000tunneling;

typedef struct s1ap_ValueUECapbltyInfoIndIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztUERadioCapblty sztUERadioCapblty;
	} u;
} Szt_ValueUECapbltyInfoIndIEsCls;
typedef struct s1apProtIE_Field_UECapbltyInfoIndIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueUECapbltyInfoIndIEsCls value;
} SztProtIE_Field_UECapbltyInfoIndIEs;

typedef struct s1apProtIE_Cont_UECapbltyInfoIndIEs
{
	TknU16 noComp;
	SztProtIE_Field_UECapbltyInfoIndIEs *member;
}SztProtIE_Cont_UECapbltyInfoIndIEs;

typedef struct s1apUECapbltyInfoInd
{
	TknPres pres;
	SztProtIE_Cont_UECapbltyInfoIndIEs protocolIEs;
} SztUECapbltyInfoInd;

typedef struct s1ap_ValueENBStatusTfrIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztENB_StatusTfr_TprntCont sztENB_StatusTfr_TprntCont;
	} u;
} Szt_ValueENBStatusTfrIEsCls;
typedef struct s1apProtIE_Field_ENBStatusTfrIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueENBStatusTfrIEsCls value;
} SztProtIE_Field_ENBStatusTfrIEs;

typedef struct s1apProtIE_Cont_ENBStatusTfrIEs
{
	TknU16 noComp;
	SztProtIE_Field_ENBStatusTfrIEs *member;
}SztProtIE_Cont_ENBStatusTfrIEs;

typedef struct s1apENBStatusTfr
{
	TknPres pres;
	SztProtIE_Cont_ENBStatusTfrIEs protocolIEs;
} SztENBStatusTfr;

typedef struct s1ap_ValueMMEStatusTfrIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztENB_StatusTfr_TprntCont sztENB_StatusTfr_TprntCont;
	} u;
} Szt_ValueMMEStatusTfrIEsCls;
typedef struct s1apProtIE_Field_MMEStatusTfrIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueMMEStatusTfrIEsCls value;
} SztProtIE_Field_MMEStatusTfrIEs;

typedef struct s1apProtIE_Cont_MMEStatusTfrIEs
{
	TknU16 noComp;
	SztProtIE_Field_MMEStatusTfrIEs *member;
}SztProtIE_Cont_MMEStatusTfrIEs;

typedef struct s1apMMEStatusTfr
{
	TknPres pres;
	SztProtIE_Cont_MMEStatusTfrIEs protocolIEs;
} SztMMEStatusTfr;

typedef struct s1ap_ValueTraceStartIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztTraceActvn sztTraceActvn;
	} u;
} Szt_ValueTraceStartIEsCls;
typedef struct s1apProtIE_Field_TraceStartIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueTraceStartIEsCls value;
} SztProtIE_Field_TraceStartIEs;

typedef struct s1apProtIE_Cont_TraceStartIEs
{
	TknU16 noComp;
	SztProtIE_Field_TraceStartIEs *member;
}SztProtIE_Cont_TraceStartIEs;

typedef struct s1apTraceStart
{
	TknPres pres;
	SztProtIE_Cont_TraceStartIEs protocolIEs;
} SztTraceStart;

typedef struct s1ap_ValueTraceFailIndIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztE_UTRAN_Trace_ID sztE_UTRAN_Trace_ID;
		SztCause sztCause;
	} u;
} Szt_ValueTraceFailIndIEsCls;
typedef struct s1apProtIE_Field_TraceFailIndIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueTraceFailIndIEsCls value;
} SztProtIE_Field_TraceFailIndIEs;

typedef struct s1apProtIE_Cont_TraceFailIndIEs
{
	TknU16 noComp;
	SztProtIE_Field_TraceFailIndIEs *member;
}SztProtIE_Cont_TraceFailIndIEs;

typedef struct s1apTraceFailInd
{
	TknPres pres;
	SztProtIE_Cont_TraceFailIndIEs protocolIEs;
} SztTraceFailInd;

typedef struct s1ap_ValueDeactvTraceIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztE_UTRAN_Trace_ID sztE_UTRAN_Trace_ID;
	} u;
} Szt_ValueDeactvTraceIEsCls;
typedef struct s1apProtIE_Field_DeactvTraceIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueDeactvTraceIEsCls value;
} SztProtIE_Field_DeactvTraceIEs;

typedef struct s1apProtIE_Cont_DeactvTraceIEs
{
	TknU16 noComp;
	SztProtIE_Field_DeactvTraceIEs *member;
}SztProtIE_Cont_DeactvTraceIEs;

typedef struct s1apDeactvTrace
{
	TknPres pres;
	SztProtIE_Cont_DeactvTraceIEs protocolIEs;
} SztDeactvTrace;

typedef struct s1ap_ValueCellTrafficTraceIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztE_UTRAN_Trace_ID sztE_UTRAN_Trace_ID;
		SztEUTRAN_CGI sztEUTRAN_CGI;
		SztTportLyrAddr sztTportLyrAddr;
		SztPrivacyIndicator sztPrivacyIndicator;
	} u;
} Szt_ValueCellTrafficTraceIEsCls;
typedef struct s1apProtIE_Field_CellTrafficTraceIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueCellTrafficTraceIEsCls value;
} SztProtIE_Field_CellTrafficTraceIEs;

typedef struct s1apProtIE_Cont_CellTrafficTraceIEs
{
	TknU16 noComp;
	SztProtIE_Field_CellTrafficTraceIEs *member;
}SztProtIE_Cont_CellTrafficTraceIEs;

typedef struct s1apCellTrafficTrace
{
	TknPres pres;
	SztProtIE_Cont_CellTrafficTraceIEs protocolIEs;
} SztCellTrafficTrace;

typedef struct s1ap_ValueLocRprtngCntrlIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztRqstTyp sztRqstTyp;
	} u;
} Szt_ValueLocRprtngCntrlIEsCls;
typedef struct s1apProtIE_Field_LocRprtngCntrlIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueLocRprtngCntrlIEsCls value;
} SztProtIE_Field_LocRprtngCntrlIEs;

typedef struct s1apProtIE_Cont_LocRprtngCntrlIEs
{
	TknU16 noComp;
	SztProtIE_Field_LocRprtngCntrlIEs *member;
}SztProtIE_Cont_LocRprtngCntrlIEs;

typedef struct s1apLocRprtngCntrl
{
	TknPres pres;
	SztProtIE_Cont_LocRprtngCntrlIEs protocolIEs;
} SztLocRprtngCntrl;

typedef struct s1ap_ValueLocRprtngFailIndIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztCause sztCause;
	} u;
} Szt_ValueLocRprtngFailIndIEsCls;
typedef struct s1apProtIE_Field_LocRprtngFailIndIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueLocRprtngFailIndIEsCls value;
} SztProtIE_Field_LocRprtngFailIndIEs;

typedef struct s1apProtIE_Cont_LocRprtngFailIndIEs
{
	TknU16 noComp;
	SztProtIE_Field_LocRprtngFailIndIEs *member;
}SztProtIE_Cont_LocRprtngFailIndIEs;

typedef struct s1apLocRprtngFailInd
{
	TknPres pres;
	SztProtIE_Cont_LocRprtngFailIndIEs protocolIEs;
} SztLocRprtngFailInd;

typedef struct s1ap_ValueLocReportIEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztEUTRAN_CGI sztEUTRAN_CGI;
		SztTAI sztTAI;
		SztRqstTyp sztRqstTyp;
	} u;
} Szt_ValueLocReportIEsCls;
typedef struct s1apProtIE_Field_LocReportIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueLocReportIEsCls value;
} SztProtIE_Field_LocReportIEs;

typedef struct s1apProtIE_Cont_LocReportIEs
{
	TknU16 noComp;
	SztProtIE_Field_LocReportIEs *member;
}SztProtIE_Cont_LocReportIEs;

typedef struct s1apLocReport
{
	TknPres pres;
	SztProtIE_Cont_LocReportIEs protocolIEs;
} SztLocReport;

typedef struct s1ap_ValueOverloadStartIEsCls{
	union {
		SztOverloadResp sztOverloadResp;
		SztGUMMEILst sztGUMMEILst;
		SztTrafficLoadReductionInd sztTrafficLoadReductionInd;
	} u;
} Szt_ValueOverloadStartIEsCls;
typedef struct s1apProtIE_Field_OverloadStartIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueOverloadStartIEsCls value;
} SztProtIE_Field_OverloadStartIEs;

typedef struct s1apProtIE_Cont_OverloadStartIEs
{
	TknU16 noComp;
	SztProtIE_Field_OverloadStartIEs *member;
}SztProtIE_Cont_OverloadStartIEs;

typedef struct s1apOverloadStart
{
	TknPres pres;
	SztProtIE_Cont_OverloadStartIEs protocolIEs;
} SztOverloadStart;

typedef struct s1ap_ValueOverloadStopIEsCls{
	union {
		SztGUMMEILst sztGUMMEILst;
	} u;
} Szt_ValueOverloadStopIEsCls;
typedef struct s1apProtIE_Field_OverloadStopIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueOverloadStopIEsCls value;
} SztProtIE_Field_OverloadStopIEs;

typedef struct s1apProtIE_Cont_OverloadStopIEs
{
	TknU16 noComp;
	SztProtIE_Field_OverloadStopIEs *member;
}SztProtIE_Cont_OverloadStopIEs;

typedef struct s1apOverloadStop
{
	TknPres pres;
	SztProtIE_Cont_OverloadStopIEs protocolIEs;
} SztOverloadStop;

typedef struct s1ap_ValueWriteReplaceWarningRqstIEsCls{
	union {
		SztMsgIdentifier sztMsgIdentifier;
		SztSerialNumber sztSerialNumber;
		SztWarningAreaLst sztWarningAreaLst;
		SztRepetitionPeriod sztRepetitionPeriod;
		SztExtendedRepetitionPeriod sztExtendedRepetitionPeriod;
		SztNumberofBroadcastRqst sztNumberofBroadcastRqst;
		SztWarningTyp sztWarningTyp;
		SztWarningSecurInfo sztWarningSecurInfo;
		SztDataCodingScheme sztDataCodingScheme;
		SztWarningMsgContents sztWarningMsgContents;
		SztConcurrentWarningMsgIndicator sztConcurrentWarningMsgIndicator;
	} u;
} Szt_ValueWriteReplaceWarningRqstIEsCls;
typedef struct s1apProtIE_Field_WriteReplaceWarningRqstIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueWriteReplaceWarningRqstIEsCls value;
} SztProtIE_Field_WriteReplaceWarningRqstIEs;

typedef struct s1apProtIE_Cont_WriteReplaceWarningRqstIEs
{
	TknU16 noComp;
	SztProtIE_Field_WriteReplaceWarningRqstIEs *member;
}SztProtIE_Cont_WriteReplaceWarningRqstIEs;

typedef struct s1apWriteReplaceWarningRqst
{
	TknPres pres;
	SztProtIE_Cont_WriteReplaceWarningRqstIEs protocolIEs;
} SztWriteReplaceWarningRqst;

typedef struct s1ap_ValueWriteReplaceWarningRespIEsCls{
	union {
		SztMsgIdentifier sztMsgIdentifier;
		SztSerialNumber sztSerialNumber;
		SztBroadcastCompletedAreaLst sztBroadcastCompletedAreaLst;
		SztCriticalityDiag sztCriticalityDiag;
	} u;
} Szt_ValueWriteReplaceWarningRespIEsCls;
typedef struct s1apProtIE_Field_WriteReplaceWarningRespIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueWriteReplaceWarningRespIEsCls value;
} SztProtIE_Field_WriteReplaceWarningRespIEs;

typedef struct s1apProtIE_Cont_WriteReplaceWarningRespIEs
{
	TknU16 noComp;
	SztProtIE_Field_WriteReplaceWarningRespIEs *member;
}SztProtIE_Cont_WriteReplaceWarningRespIEs;

typedef struct s1apWriteReplaceWarningResp
{
	TknPres pres;
	SztProtIE_Cont_WriteReplaceWarningRespIEs protocolIEs;
} SztWriteReplaceWarningResp;

typedef struct s1apInter_SystemInformTfrTyp
{
	TknU8 choice;
	union {
		SztRIMTfr rIMTfr;
	} val;
} SztInter_SystemInformTfrTyp;

typedef struct s1ap_ValueENBDirectInformTfrIEsCls{
	union {
		SztInter_SystemInformTfrTyp sztInter_SystemInformTfrTyp;
	} u;
} Szt_ValueENBDirectInformTfrIEsCls;
typedef struct s1apProtIE_Field_ENBDirectInformTfrIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueENBDirectInformTfrIEsCls value;
} SztProtIE_Field_ENBDirectInformTfrIEs;

typedef struct s1apProtIE_Cont_ENBDirectInformTfrIEs
{
	TknU16 noComp;
	SztProtIE_Field_ENBDirectInformTfrIEs *member;
}SztProtIE_Cont_ENBDirectInformTfrIEs;

typedef struct s1apENBDirectInformTfr
{
	TknPres pres;
	SztProtIE_Cont_ENBDirectInformTfrIEs protocolIEs;
} SztENBDirectInformTfr;

typedef struct s1ap_ValueMMEDirectInformTfrIEsCls{
	union {
		SztInter_SystemInformTfrTyp sztInter_SystemInformTfrTyp;
	} u;
} Szt_ValueMMEDirectInformTfrIEsCls;
typedef struct s1apProtIE_Field_MMEDirectInformTfrIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueMMEDirectInformTfrIEsCls value;
} SztProtIE_Field_MMEDirectInformTfrIEs;

typedef struct s1apProtIE_Cont_MMEDirectInformTfrIEs
{
	TknU16 noComp;
	SztProtIE_Field_MMEDirectInformTfrIEs *member;
}SztProtIE_Cont_MMEDirectInformTfrIEs;

typedef struct s1apMMEDirectInformTfr
{
	TknPres pres;
	SztProtIE_Cont_MMEDirectInformTfrIEs protocolIEs;
} SztMMEDirectInformTfr;

typedef struct s1ap_ValueENBConfigTfrIEsCls{
	union {
		SztSONConfigTfr sztSONConfigTfr;
	} u;
} Szt_ValueENBConfigTfrIEsCls;
typedef struct s1apProtIE_Field_ENBConfigTfrIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueENBConfigTfrIEsCls value;
} SztProtIE_Field_ENBConfigTfrIEs;

typedef struct s1apProtIE_Cont_ENBConfigTfrIEs
{
	TknU16 noComp;
	SztProtIE_Field_ENBConfigTfrIEs *member;
}SztProtIE_Cont_ENBConfigTfrIEs;

typedef struct s1apENBConfigTfr
{
	TknPres pres;
	SztProtIE_Cont_ENBConfigTfrIEs protocolIEs;
} SztENBConfigTfr;

typedef struct s1ap_ValueMMEConfigTfrIEsCls{
	union {
		SztSONConfigTfr sztSONConfigTfr;
	} u;
} Szt_ValueMMEConfigTfrIEsCls;
typedef struct s1apProtIE_Field_MMEConfigTfrIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueMMEConfigTfrIEsCls value;
} SztProtIE_Field_MMEConfigTfrIEs;

typedef struct s1apProtIE_Cont_MMEConfigTfrIEs
{
	TknU16 noComp;
	SztProtIE_Field_MMEConfigTfrIEs *member;
}SztProtIE_Cont_MMEConfigTfrIEs;

typedef struct s1apMMEConfigTfr
{
	TknPres pres;
	SztProtIE_Cont_MMEConfigTfrIEs protocolIEs;
} SztMMEConfigTfr;

typedef struct s1ap_ValuePrivMsgIEsCls{
	union {
		TknU8 unused;
	} u;
} Szt_ValuePrivMsgIEsCls;
typedef struct s1apPrivIE_Field_PrivMsgIEs
{
	TknPres pres;
	SztPrivIE_ID id;
	SztCriticality criticality;
	Szt_ValuePrivMsgIEsCls value;
} SztPrivIE_Field_PrivMsgIEs;

typedef struct s1apPrivIE_Cont_PrivMsgIEs
{
	TknU16 noComp;
	SztPrivIE_Field_PrivMsgIEs *member;
}SztPrivIE_Cont_PrivMsgIEs;

typedef struct s1apPrivMsg
{
	TknPres pres;
	SztPrivIE_Cont_PrivMsgIEs privateIEs;
} SztPrivMsg;

typedef struct s1ap_ValueKillRqstIEsCls{
	union {
		SztMsgIdentifier sztMsgIdentifier;
		SztSerialNumber sztSerialNumber;
		SztWarningAreaLst sztWarningAreaLst;
	} u;
} Szt_ValueKillRqstIEsCls;
typedef struct s1apProtIE_Field_KillRqstIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueKillRqstIEsCls value;
} SztProtIE_Field_KillRqstIEs;

typedef struct s1apProtIE_Cont_KillRqstIEs
{
	TknU16 noComp;
	SztProtIE_Field_KillRqstIEs *member;
}SztProtIE_Cont_KillRqstIEs;

typedef struct s1apKillRqst
{
	TknPres pres;
	SztProtIE_Cont_KillRqstIEs protocolIEs;
} SztKillRqst;

typedef struct s1ap_ValueKillRespIEsCls{
	union {
		SztMsgIdentifier sztMsgIdentifier;
		SztSerialNumber sztSerialNumber;
		SztBroadcastCancelledAreaLst sztBroadcastCancelledAreaLst;
		SztCriticalityDiag sztCriticalityDiag;
	} u;
} Szt_ValueKillRespIEsCls;
typedef struct s1apProtIE_Field_KillRespIEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueKillRespIEsCls value;
} SztProtIE_Field_KillRespIEs;

typedef struct s1apProtIE_Cont_KillRespIEs
{
	TknU16 noComp;
	SztProtIE_Field_KillRespIEs *member;
}SztProtIE_Cont_KillRespIEs;

typedef struct s1apKillResp
{
	TknPres pres;
	SztProtIE_Cont_KillRespIEs protocolIEs;
} SztKillResp;

typedef struct s1ap_ValueDlnkUEAssociatedLPPaTport_IEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztRouting_ID sztRouting_ID;
		SztLPPa_PDU sztLPPa_PDU;
	} u;
} Szt_ValueDlnkUEAssociatedLPPaTport_IEsCls;
typedef struct s1apProtIE_Field_DlnkUEAssociatedLPPaTport_IEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueDlnkUEAssociatedLPPaTport_IEsCls value;
} SztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs;

typedef struct s1apProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs
{
	TknU16 noComp;
	SztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs *member;
}SztProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs;

typedef struct s1apDlnkUEAssociatedLPPaTport
{
	TknPres pres;
	SztProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs protocolIEs;
} SztDlnkUEAssociatedLPPaTport;

typedef struct s1ap_ValueUlnkUEAssociatedLPPaTport_IEsCls{
	union {
		SztMME_UE_S1AP_ID sztMME_UE_S1AP_ID;
		SztENB_UE_S1AP_ID sztENB_UE_S1AP_ID;
		SztRouting_ID sztRouting_ID;
		SztLPPa_PDU sztLPPa_PDU;
	} u;
} Szt_ValueUlnkUEAssociatedLPPaTport_IEsCls;
typedef struct s1apProtIE_Field_UlnkUEAssociatedLPPaTport_IEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueUlnkUEAssociatedLPPaTport_IEsCls value;
} SztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs;

typedef struct s1apProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs
{
	TknU16 noComp;
	SztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs *member;
}SztProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs;

typedef struct s1apUlnkUEAssociatedLPPaTport
{
	TknPres pres;
	SztProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs protocolIEs;
} SztUlnkUEAssociatedLPPaTport;

typedef struct s1ap_ValueDlnkNonUEAssociatedLPPaTport_IEsCls{
	union {
		SztRouting_ID sztRouting_ID;
		SztLPPa_PDU sztLPPa_PDU;
	} u;
} Szt_ValueDlnkNonUEAssociatedLPPaTport_IEsCls;
typedef struct s1apProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueDlnkNonUEAssociatedLPPaTport_IEsCls value;
} SztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs;

typedef struct s1apProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs
{
	TknU16 noComp;
	SztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs *member;
}SztProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs;

typedef struct s1apDlnkNonUEAssociatedLPPaTport
{
	TknPres pres;
	SztProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs protocolIEs;
} SztDlnkNonUEAssociatedLPPaTport;

typedef struct s1ap_ValueUlnkNonUEAssociatedLPPaTport_IEsCls{
	union {
		SztRouting_ID sztRouting_ID;
		SztLPPa_PDU sztLPPa_PDU;
	} u;
} Szt_ValueUlnkNonUEAssociatedLPPaTport_IEsCls;
typedef struct s1apProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs
{
	TknPres pres;
	SztProtIE_ID id;
	SztCriticality criticality;
	Szt_ValueUlnkNonUEAssociatedLPPaTport_IEsCls value;
} SztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs;

typedef struct s1apProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs
{
	TknU16 noComp;
	SztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs *member;
}SztProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs;

typedef struct s1apUlnkNonUEAssociatedLPPaTport
{
	TknPres pres;
	SztProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs protocolIEs;
} SztUlnkNonUEAssociatedLPPaTport;

typedef struct s1ap_InitiatingMsgCls{
	union {
		SztHovrReqd sztHovrReqd;
		SztHovrRqst sztHovrRqst;
		SztPathSwRqst sztPathSwRqst;
		SztE_RABSetupRqst sztE_RABSetupRqst;
		SztE_RABMdfyRqst sztE_RABMdfyRqst;
		SztE_RABRlsCmmd sztE_RABRlsCmmd;
		SztInitCntxtSetupRqst sztInitCntxtSetupRqst;
		SztHovrCancel sztHovrCancel;
		SztKillRqst sztKillRqst;
		SztReset sztReset;
		SztS1SetupRqst sztS1SetupRqst;
		SztUECntxtModificationRqst sztUECntxtModificationRqst;
		SztUECntxtRlsCmmd sztUECntxtRlsCmmd;
		SztENBConfigUpd sztENBConfigUpd;
		SztMMEConfigUpd sztMMEConfigUpd;
		SztWriteReplaceWarningRqst sztWriteReplaceWarningRqst;
		SztUERadioCapbltyMatchRqst sztUERadioCapbltyMatchRqst;
		SztHovrNtfy sztHovrNtfy;
		SztE_RABRlsInd sztE_RABRlsInd;
		SztPag sztPag;
		SztDlnkNASTport sztDlnkNASTport;
		SztInitUEMsg sztInitUEMsg;
		SztUlnkNASTport sztUlnkNASTport;
		SztErrInd sztErrInd;
		SztNASNonDlvryInd sztNASNonDlvryInd;
		SztUECntxtRlsRqst sztUECntxtRlsRqst;
		SztDlnkS1cdma2000tunneling sztDlnkS1cdma2000tunneling;
		SztUlnkS1cdma2000tunneling sztUlnkS1cdma2000tunneling;
		SztUECapbltyInfoInd sztUECapbltyInfoInd;
		SztENBStatusTfr sztENBStatusTfr;
		SztMMEStatusTfr sztMMEStatusTfr;
		SztDeactvTrace sztDeactvTrace;
		SztTraceStart sztTraceStart;
		SztTraceFailInd sztTraceFailInd;
		SztCellTrafficTrace sztCellTrafficTrace;
		SztLocRprtngCntrl sztLocRprtngCntrl;
		SztLocRprtngFailInd sztLocRprtngFailInd;
		SztLocReport sztLocReport;
		SztOverloadStart sztOverloadStart;
		SztOverloadStop sztOverloadStop;
		SztENBDirectInformTfr sztENBDirectInformTfr;
		SztMMEDirectInformTfr sztMMEDirectInformTfr;
		SztENBConfigTfr sztENBConfigTfr;
		SztMMEConfigTfr sztMMEConfigTfr;
		SztPrivMsg sztPrivMsg;
		SztDlnkUEAssociatedLPPaTport sztDlnkUEAssociatedLPPaTport;
		SztUlnkUEAssociatedLPPaTport sztUlnkUEAssociatedLPPaTport;
		SztDlnkNonUEAssociatedLPPaTport sztDlnkNonUEAssociatedLPPaTport;
		SztUlnkNonUEAssociatedLPPaTport sztUlnkNonUEAssociatedLPPaTport;
	} u;
} Szt_InitiatingMsgCls;
typedef struct s1apInitiatingMsg
{
	TknPres pres;
	SztProcedureCode procedureCode;
	SztCriticality criticality;
	Szt_InitiatingMsgCls value;
} SztInitiatingMsg;

typedef struct s1ap_SuccessfulOutcomeCls{
	union {
		SztHovrCmmd sztHovrCmmd;
		SztHovrRqstAckg sztHovrRqstAckg;
		SztPathSwRqstAckg sztPathSwRqstAckg;
		SztE_RABSetupResp sztE_RABSetupResp;
		SztE_RABMdfyResp sztE_RABMdfyResp;
		SztE_RABRlsResp sztE_RABRlsResp;
		SztInitCntxtSetupResp sztInitCntxtSetupResp;
		SztHovrCancelAckg sztHovrCancelAckg;
		SztKillResp sztKillResp;
		SztResetAckg sztResetAckg;
		SztS1SetupResp sztS1SetupResp;
		SztUECntxtModificationResp sztUECntxtModificationResp;
		SztUECntxtRlsComplete sztUECntxtRlsComplete;
		SztENBConfigUpdAckg sztENBConfigUpdAckg;
		SztMMEConfigUpdAckg sztMMEConfigUpdAckg;
		SztWriteReplaceWarningResp sztWriteReplaceWarningResp;
		SztUERadioCapbltyMatchResp sztUERadioCapbltyMatchResp;
	} u;
} Szt_SuccessfulOutcomeCls;
typedef struct s1apSuccessfulOutcome
{
	TknPres pres;
	SztProcedureCode procedureCode;
	SztCriticality criticality;
	Szt_SuccessfulOutcomeCls value;
} SztSuccessfulOutcome;

typedef struct s1ap_UnsuccessfulOutcomeCls{
	union {
		SztHovrPrepFail sztHovrPrepFail;
		SztHovrFail sztHovrFail;
		SztPathSwRqstFail sztPathSwRqstFail;
		SztInitCntxtSetupFail sztInitCntxtSetupFail;
		SztS1SetupFail sztS1SetupFail;
		SztUECntxtModificationFail sztUECntxtModificationFail;
		SztENBConfigUpdFail sztENBConfigUpdFail;
		SztMMEConfigUpdFail sztMMEConfigUpdFail;
	} u;
} Szt_UnsuccessfulOutcomeCls;
typedef struct s1apUnsuccessfulOutcome
{
	TknPres pres;
	SztProcedureCode procedureCode;
	SztCriticality criticality;
	Szt_UnsuccessfulOutcomeCls value;
} SztUnsuccessfulOutcome;

typedef struct s1apS1AP_PDU
{
	TknU8 choice;
	union {
		SztInitiatingMsg initiatingMsg;
		SztSuccessfulOutcome successfulOutcome;
		SztUnsuccessfulOutcome unsuccessfulOutcome;
	} val;
} SztS1AP_PDU;


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
