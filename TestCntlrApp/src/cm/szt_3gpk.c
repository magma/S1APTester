
/***********************************************************************

     Name: S1AP Layer
           
     Type: C Soruce code File
                          
     Desc: Primitives for pack of szt interface
                  
     File: szt_3gpk.c
         
     Sid:  

     Prg: akaranth 
                                                                        
***********************************************************************/

#include "envopt.h"           /* environment options */
#include "envdep.h"           /* environment dependent */
#include "envind.h"           /* environment independent */
#include "gen.h"              /* general layer */
#include "ssi.h"              /* system services */
#include "cm_mblk.h"
#include "cm_tkns.h"
#include "cm_pasn.h"          /* common defines for ASN */
#include "cm_umts.h"
#include "szt_asn.h"
#include "szt_3gasn.h"

#include "gen.x"              /* general layer */
#include "ssi.x"              /* system services */
#include "cm_tkns.x"          /* */
#include "cm_mblk.x"
#include "cm_pasn.x"          /* PASN */
#include "szt_asn.x"
#include "szt_3gasn.x"
#include "szt_3gpk.x"


/* szt_3gpk_c_001.main_1: Support for Source RNC to Target RNC TC Enc/Dec. */

#define cmPkSztCriticality cmPkTknU32
#define cmPkSztProtExtnID cmPkTknU32 
#define cmPkSztHS_DSCH_MAC_d_Flow_ID cmPkTknU32 
#define cmPkSztE_DCH_MAC_d_Flow_ID cmPkTknU32 
#define cmPkSztUSCH_ID cmPkTknU32 
#define cmPkSztDSCH_ID cmPkTknU32 
#define cmPkSztDCH_ID cmPkTknU32 
#define cmPkSztRAB_ID cmPkTknBStr32 
#define cmPkSztTgetCellId cmPkTknU32 
#define cmPkSztD_RNTI cmPkTknU32 
#define cmPkSztEncryptionAlgorithm cmPkTknU32 
/* Element ------------- ChosenEncryptionAlgorithm ------------ */
#define cmPkSztChosenEncryptionAlgorithm cmPkTknU8
#define cmPkSztIntegrityProtectionAlgorithm cmPkTknU32 
/* Element ------------- ChosenIntegrityProtectionAlgorithm ------------ */
#define cmPkSztChosenIntegrityProtectionAlgorithm cmPkTknU8
#define cmPkSztEncryptionKey cmPkTknStrBSXL 
#define cmPkSztIntegrityProtectionKey cmPkTknStrBSXL 
#define cmPkSztRelocationTyp cmPkTknU32
#define cmPkSztNumberOfIuInstances cmPkTknU32 
#define cmPkSztRRC_Cont cmPkTknStrOSXL 
#define cmPkSztNRTLoadInformValue cmPkTknU32 
#define cmPkSztRTLoadValue cmPkTknU32 
#define cmPkSztLoadValue cmPkTknU32 
#define cmPkSztCell_Capacity_Class_Value cmPkTknU32 
#define cmPkSztRAC cmPkTknStr4 
#define cmPkSztCI cmPkTknStr4 
#define cmPkSztLAC cmPkTknStr4 
#define cmPkSztTBCD_STRING cmPkTknStrOSXL 
/* Element ------------- PLMNidentity ------------ */
#define cmPkSztPLMNidentity cmPkSztTBCD_STRING
#define cmPkSztTraceRecordingSessionReference cmPkTknU32 
#define cmPkSztTraceReference cmPkTknStrOSXL 
#define cmPkSztMBMSLinkingInform cmPkTknU32
#define cmPkSztUE_History_Inform cmPkTknStrOSXL 
#define cmPkSztSubscriberProfileIDforRFP cmPkTknU32 
#define cmPkSztSRVCC_Informnonce cmPkTknStrBSXL 
#define cmPkSztCSFB_Inform cmPkTknU32
#define cmPkSztSRB_ID cmPkTknU32 
#define cmPkSztCN_DomainIndicator cmPkTknU32

/***************/

/* 
* FUN : cmPkSzt_ExtnSRB_TrCH_MappingItem_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnSRB_TrCH_MappingItem_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnSRB_TrCH_MappingItem_ExtIEsCls
(
Szt_ExtnSRB_TrCH_MappingItem_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnSRB_TrCH_MappingItem_ExtIEsCls(param, val, mBuf)
Szt_ExtnSRB_TrCH_MappingItem_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnSRB_TrCH_MappingItem_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnSRB_TrCH_MappingItem_ExtIEsCls */


/* 
* FUN : cmPkSztProtExtnField_SRB_TrCH_MappingItem_ExtIEs
*  DESC: Function to Pack SztProtExtnField_SRB_TrCH_MappingItem_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_SRB_TrCH_MappingItem_ExtIEs
(
SztProtExtnField_SRB_TrCH_MappingItem_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_SRB_TrCH_MappingItem_ExtIEs(param, mBuf)
SztProtExtnField_SRB_TrCH_MappingItem_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_SRB_TrCH_MappingItem_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnSRB_TrCH_MappingItem_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_SRB_TrCH_MappingItem_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_SRB_TrCH_MappingItem_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_SRB_TrCH_MappingItem_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_SRB_TrCH_MappingItem_ExtIEs
(
SztProtExtnCont_SRB_TrCH_MappingItem_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_SRB_TrCH_MappingItem_ExtIEs(param, mBuf)
SztProtExtnCont_SRB_TrCH_MappingItem_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_SRB_TrCH_MappingItem_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_SRB_TrCH_MappingItem_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_SRB_TrCH_MappingItem_ExtIEs */

/* 
* FUN : cmPkSztTrCH_ID
*  DESC: Function to Pack SztTrCH_ID structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztTrCH_ID
(
SztTrCH_ID *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztTrCH_ID(param, mBuf)
SztTrCH_ID *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztTrCH_ID) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_TrCH_ID_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztUSCH_ID, &param->uSCH_ID, mBuf); 
		CMCHKPK(cmPkSztDSCH_ID, &param->dSCH_ID, mBuf); 
		CMCHKPK(cmPkSztDCH_ID, &param->dCH_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztTrCH_ID */



/* 
* FUN : cmPkSztSRB_TrCH_MappingItem
*  DESC: Function to Pack SztSRB_TrCH_MappingItem structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztSRB_TrCH_MappingItem
(
SztSRB_TrCH_MappingItem *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztSRB_TrCH_MappingItem(param, mBuf)
SztSRB_TrCH_MappingItem *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztSRB_TrCH_MappingItem) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_SRB_TrCH_MappingItem_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztTrCH_ID, &param->trCH_ID, mBuf); 
		CMCHKPK(cmPkSztSRB_ID, &param->sRB_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztSRB_TrCH_MappingItem */



/* 
* FUN : cmPkSztSRB_TrCH_Mapping
*  DESC: Function to Pack SztSRB_TrCH_Mapping structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztSRB_TrCH_Mapping
(
SztSRB_TrCH_Mapping *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztSRB_TrCH_Mapping(param, mBuf)
SztSRB_TrCH_Mapping *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztSRB_TrCH_Mapping) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztSRB_TrCH_MappingItem, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztSRB_TrCH_Mapping */

/* 
* FUN : cmPkSzt_ExtnCellLoadInformGroup_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnCellLoadInformGroup_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnCellLoadInformGroup_ExtIEsCls
(
Szt_ExtnCellLoadInformGroup_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnCellLoadInformGroup_ExtIEsCls(param, val, mBuf)
Szt_ExtnCellLoadInformGroup_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnCellLoadInformGroup_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnCellLoadInformGroup_ExtIEsCls */

/* 
* FUN : cmPkSztProtExtnField_CellLoadInformGroup_ExtIEs
*  DESC: Function to Pack SztProtExtnField_CellLoadInformGroup_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_CellLoadInformGroup_ExtIEs
(
SztProtExtnField_CellLoadInformGroup_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_CellLoadInformGroup_ExtIEs(param, mBuf)
SztProtExtnField_CellLoadInformGroup_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_CellLoadInformGroup_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnCellLoadInformGroup_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_CellLoadInformGroup_ExtIEs */





/* 
* FUN : cmPkSztProtExtnCont_CellLoadInformGroup_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_CellLoadInformGroup_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_CellLoadInformGroup_ExtIEs
(
SztProtExtnCont_CellLoadInformGroup_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_CellLoadInformGroup_ExtIEs(param, mBuf)
SztProtExtnCont_CellLoadInformGroup_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_CellLoadInformGroup_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_CellLoadInformGroup_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_CellLoadInformGroup_ExtIEs */

/* 
* FUN : cmPkSzt_ExtnCellLoadInform_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnCellLoadInform_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnCellLoadInform_ExtIEsCls
(
Szt_ExtnCellLoadInform_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnCellLoadInform_ExtIEsCls(param, val, mBuf)
Szt_ExtnCellLoadInform_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnCellLoadInform_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnCellLoadInform_ExtIEsCls */




/* 
* FUN : cmPkSztProtExtnField_CellLoadInform_ExtIEs
*  DESC: Function to Pack SztProtExtnField_CellLoadInform_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_CellLoadInform_ExtIEs
(
SztProtExtnField_CellLoadInform_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_CellLoadInform_ExtIEs(param, mBuf)
SztProtExtnField_CellLoadInform_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_CellLoadInform_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnCellLoadInform_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_CellLoadInform_ExtIEs */




/* 
* FUN : cmPkSztProtExtnCont_CellLoadInform_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_CellLoadInform_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_CellLoadInform_ExtIEs
(
SztProtExtnCont_CellLoadInform_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_CellLoadInform_ExtIEs(param, mBuf)
SztProtExtnCont_CellLoadInform_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_CellLoadInform_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_CellLoadInform_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_CellLoadInform_ExtIEs */




/* 
* FUN : cmPkSztCellLoadInform
*  DESC: Function to Pack SztCellLoadInform structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztCellLoadInform
(
SztCellLoadInform *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztCellLoadInform(param, mBuf)
SztCellLoadInform *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztCellLoadInform) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_CellLoadInform_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztNRTLoadInformValue, &param->nRTLoadInformValue, mBuf); 
		CMCHKPK(cmPkSztRTLoadValue, &param->rTLoadValue, mBuf); 
		CMCHKPK(cmPkSztLoadValue, &param->loadValue, mBuf); 
		CMCHKPK(cmPkSztCell_Capacity_Class_Value, &param->cell_Capacity_Class_Value, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztCellLoadInform */

/* 
* FUN : cmPkSzt3g_ExtnCGI_ExtIEsCls
*  DESC: Function to Pack Szt3g_ExtnCGI_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt3g_ExtnCGI_ExtIEsCls
(
Szt3g_ExtnCGI_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt3g_ExtnCGI_ExtIEsCls(param, val, mBuf)
Szt3g_ExtnCGI_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt3g_ExtnCGI_ExtIEsCls) 
	
	switch (val)
	{
		case Sztid_RAC:
			CMCHKPK(cmPkSztRAC, &param->u.sztRAC, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt3g_ExtnCGI_ExtIEsCls */




/* 
* FUN : cmPkSzt3gProtExtnField_CGI_ExtIEs
*  DESC: Function to Pack SztProtExtnField_CGI_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt3gProtExtnField_CGI_ExtIEs
(
Szt3gProtExtnField_CGI_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt3gProtExtnField_CGI_ExtIEs(param, mBuf)
Szt3gProtExtnField_CGI_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt3gProtExtnField_CGI_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt3g_ExtnCGI_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSzt3gProtExtnField_CGI_ExtIEs */




/* 
* FUN : cmPkSzt3gProtExtnCont_CGI_ExtIEs
*  DESC: Function to Pack Szt3gProtExtnCont_CGI_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt3gProtExtnCont_CGI_ExtIEs
(
Szt3gProtExtnCont_CGI_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt3gProtExtnCont_CGI_ExtIEs(param, mBuf)
Szt3gProtExtnCont_CGI_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSzt3gProtExtnCont_CGI_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSzt3gProtExtnField_CGI_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSzt3gProtExtnCont_CGI_ExtIEs */




/* 
* FUN : cmPkSzt3gCGI
*  DESC: Function to Pack Szt3gCGI structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt3gCGI
(
Szt3gCGI *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt3gCGI(param, mBuf)
Szt3gCGI *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt3gCGI) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSzt3gProtExtnCont_CGI_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztCI, &param->cI, mBuf); 
		CMCHKPK(cmPkSztLAC, &param->lAC, mBuf); 
		CMCHKPK(cmPkSztPLMNidentity, &param->pLMNidentity, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSzt3gCGI */

/* 
* FUN : cmPkSzt_ExtnSrcUTRANCellID_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnSrcUTRANCellID_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnSrcUTRANCellID_ExtIEsCls
(
Szt_ExtnSrcUTRANCellID_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnSrcUTRANCellID_ExtIEsCls(param, val, mBuf)
Szt_ExtnSrcUTRANCellID_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnSrcUTRANCellID_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnSrcUTRANCellID_ExtIEsCls */

/* 
* FUN : cmPkSztProtExtnField_SrcUTRANCellID_ExtIEs
*  DESC: Function to Pack SztProtExtnField_SrcUTRANCellID_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_SrcUTRANCellID_ExtIEs
(
SztProtExtnField_SrcUTRANCellID_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_SrcUTRANCellID_ExtIEs(param, mBuf)
SztProtExtnField_SrcUTRANCellID_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_SrcUTRANCellID_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnSrcUTRANCellID_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_SrcUTRANCellID_ExtIEs */




/* 
* FUN : cmPkSztProtExtnCont_SrcUTRANCellID_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_SrcUTRANCellID_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_SrcUTRANCellID_ExtIEs
(
SztProtExtnCont_SrcUTRANCellID_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_SrcUTRANCellID_ExtIEs(param, mBuf)
SztProtExtnCont_SrcUTRANCellID_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_SrcUTRANCellID_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_SrcUTRANCellID_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_SrcUTRANCellID_ExtIEs */

/* 
* FUN : cmPkSztSrcUTRANCellID
*  DESC: Function to Pack SztSrcUTRANCellID structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztSrcUTRANCellID
(
SztSrcUTRANCellID *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztSrcUTRANCellID(param, mBuf)
SztSrcUTRANCellID *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztSrcUTRANCellID) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_SrcUTRANCellID_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztTgetCellId, &param->uTRANcellID, mBuf); 
		CMCHKPK(cmPkSztPLMNidentity, &param->pLMNidentity, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztSrcUTRANCellID */




/* 
* FUN : cmPkSztSrcCellID
*  DESC: Function to Pack SztSrcCellID structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztSrcCellID
(
SztSrcCellID *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztSrcCellID(param, mBuf)
SztSrcCellID *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztSrcCellID) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case SRCCELLID_SOURCEGERANCELLID :
				CMCHKPK(cmPkSzt3gCGI, &param->val.sourceGERANCellID, mBuf); 
				break;
			case SRCCELLID_SOURCEUTRANCELLID :
				CMCHKPK(cmPkSztSrcUTRANCellID, &param->val.sourceUTRANCellID, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztSrcCellID */



/* 
* FUN : cmPkSztCellLoadInformGroup
*  DESC: Function to Pack SztCellLoadInformGroup structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztCellLoadInformGroup
(
SztCellLoadInformGroup *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztCellLoadInformGroup(param, mBuf)
SztCellLoadInformGroup *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztCellLoadInformGroup) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_CellLoadInformGroup_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztCellLoadInform, &param->downlinkCellLoadInform, mBuf); 
		CMCHKPK(cmPkSztCellLoadInform, &param->uplinkCellLoadInform, mBuf); 
		CMCHKPK(cmPkSztSrcCellID, &param->sourceCellID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztCellLoadInformGroup */

/* 
* FUN : cmPkSzt_ExtnTraceRecordingSessionInform_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnTraceRecordingSessionInform_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnTraceRecordingSessionInform_ExtIEsCls
(
Szt_ExtnTraceRecordingSessionInform_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnTraceRecordingSessionInform_ExtIEsCls(param, val, mBuf)
Szt_ExtnTraceRecordingSessionInform_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnTraceRecordingSessionInform_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnTraceRecordingSessionInform_ExtIEsCls */

/* 
* FUN : cmPkSztProtExtnField_TraceRecordingSessionInform_ExtIEs
*  DESC: Function to Pack SztProtExtnField_TraceRecordingSessionInform_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_TraceRecordingSessionInform_ExtIEs
(
SztProtExtnField_TraceRecordingSessionInform_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_TraceRecordingSessionInform_ExtIEs(param, mBuf)
SztProtExtnField_TraceRecordingSessionInform_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_TraceRecordingSessionInform_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnTraceRecordingSessionInform_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_TraceRecordingSessionInform_ExtIEs */





/* 
* FUN : cmPkSztProtExtnCont_TraceRecordingSessionInform_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_TraceRecordingSessionInform_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_TraceRecordingSessionInform_ExtIEs
(
SztProtExtnCont_TraceRecordingSessionInform_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_TraceRecordingSessionInform_ExtIEs(param, mBuf)
SztProtExtnCont_TraceRecordingSessionInform_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_TraceRecordingSessionInform_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_TraceRecordingSessionInform_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_TraceRecordingSessionInform_ExtIEs */



/* 
* FUN : cmPkSztTraceRecordingSessionInform
*  DESC: Function to Pack SztTraceRecordingSessionInform structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztTraceRecordingSessionInform
(
SztTraceRecordingSessionInform *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztTraceRecordingSessionInform(param, mBuf)
SztTraceRecordingSessionInform *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztTraceRecordingSessionInform) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_TraceRecordingSessionInform_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztTraceRecordingSessionReference, &param->traceRecordingSessionReference, mBuf); 
		CMCHKPK(cmPkSztTraceReference, &param->traceReference, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztTraceRecordingSessionInform */

/* 
* FUN : cmPkSzt_ExtnSRVCC_Inform_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnSRVCC_Inform_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnSRVCC_Inform_ExtIEsCls
(
Szt_ExtnSRVCC_Inform_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnSRVCC_Inform_ExtIEsCls(param, val, mBuf)
Szt_ExtnSRVCC_Inform_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnSRVCC_Inform_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnSRVCC_Inform_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_SRVCC_Inform_ExtIEs
*  DESC: Function to Pack SztProtExtnField_SRVCC_Inform_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_SRVCC_Inform_ExtIEs
(
SztProtExtnField_SRVCC_Inform_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_SRVCC_Inform_ExtIEs(param, mBuf)
SztProtExtnField_SRVCC_Inform_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_SRVCC_Inform_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnSRVCC_Inform_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_SRVCC_Inform_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_SRVCC_Inform_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_SRVCC_Inform_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_SRVCC_Inform_ExtIEs
(
SztProtExtnCont_SRVCC_Inform_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_SRVCC_Inform_ExtIEs(param, mBuf)
SztProtExtnCont_SRVCC_Inform_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_SRVCC_Inform_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_SRVCC_Inform_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_SRVCC_Inform_ExtIEs */




/* 
* FUN : cmPkSztSRVCC_Inform
*  DESC: Function to Pack SztSRVCC_Inform structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztSRVCC_Inform
(
SztSRVCC_Inform *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztSRVCC_Inform(param, mBuf)
SztSRVCC_Inform *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztSRVCC_Inform) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_SRVCC_Inform_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztSRVCC_Informnonce, &param->nonce, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztSRVCC_Inform */




/* 
* FUN : cmPkSzt_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsCls
(
Szt_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsCls(param, val, mBuf)
Szt_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsCls) 
	
	switch (val)
	{
		case Sztid_SRB_TrCH_Mapping:
			CMCHKPK(cmPkSztSRB_TrCH_Mapping, &param->u.sztSRB_TrCH_Mapping, mBuf);
			break;
		case Sztid_CellLoadInformGroup:
			CMCHKPK(cmPkSztCellLoadInformGroup, &param->u.sztCellLoadInformGroup, mBuf);
			break;
		case Sztid_TraceRecordingSessionInform:
			CMCHKPK(cmPkSztTraceRecordingSessionInform, &param->u.sztTraceRecordingSessionInform, mBuf);
			break;
		case Sztid_MBMSLinkingInform:
			CMCHKPK(cmPkSztMBMSLinkingInform, &param->u.sztMBMSLinkingInform, mBuf);
			break;
		case Sztid_d_RNTI_for_NoIuCSUP:
			CMCHKPK(cmPkSztD_RNTI, &param->u.sztD_RNTI, mBuf);
			break;
		case Sztid_UE_History_Inform:
			CMCHKPK(cmPkSztUE_History_Inform, &param->u.sztUE_History_Inform, mBuf);
			break;
		case Sztid_SubscriberProfileIDforRFP:
			CMCHKPK(cmPkSztSubscriberProfileIDforRFP, &param->u.sztSubscriberProfileIDforRFP, mBuf);
			break;
		case Sztid_SRVCC_Inform:
			CMCHKPK(cmPkSztSRVCC_Inform, &param->u.sztSRVCC_Inform, mBuf);
			break;
		case Sztid_PSRABtobeReplaced:
			CMCHKPK(cmPkSztRAB_ID, &param->u.sztRAB_ID, mBuf);
			break;
		case Sztid_CSFB_Inform:
			CMCHKPK(cmPkSztCSFB_Inform, &param->u.sztCSFB_Inform, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsCls */







/**************/

/*
 * * FUN : cmPkSztProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEs
 * *  DESC: Function to Pack SztProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEs structure
 * * RETURN: ROK - OK
 * */
#ifdef ANSI
PUBLIC S16 cmPkSztProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEs
(
 SztProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEs *param,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmPkSztProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEs(param, mBuf)
   SztProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEs *param;
   Buffer *mBuf;
#endif
{

   TRC3(cmPkSztProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEs)

      if( param->pres.pres != NOTPRSNT )
      {
         {
            S16 ret;
            ret = cmPkSzt_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
            if (ret != ROK)
               RETVALUE(RFAILED);
         }
         CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf);
         CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf);
      }
   CMCHKPK(cmPkTknPres, &param->pres, mBuf);
   RETVALUE(ROK);
}   /* End of function cmPkSztProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEs */

/*
 * * FUN : cmPkSztProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEs
 * *  DESC: Function to Pack SztProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEs structure
 * * RETURN: ROK - OK
 * */
#ifdef ANSI
PUBLIC S16 cmPkSztProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEs
(
 SztProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEs *param,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmPkSztProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEs(param, mBuf)
   SztProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEs *param;
   Buffer *mBuf;
#endif
{
   Cntr i;
   TRC3(cmPkSztProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEs)

      if( param->noComp.pres != NOTPRSNT )
      {
         for(i = param->noComp.val-1; i >= 0; i--)
         {
            CMCHKPK(cmPkSztProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEs, (&param->member[i]), mBuf);
         }
      }
   CMCHKPK(cmPkTknU16, &param->noComp, mBuf);
   RETVALUE(ROK);
}   /* End of function cmPkSztProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEs */

/* 
* FUN : cmPkSzt_ExtnTrCH_ID_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnTrCH_ID_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnTrCH_ID_ExtIEsCls
(
Szt_ExtnTrCH_ID_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnTrCH_ID_ExtIEsCls(param, val, mBuf)
Szt_ExtnTrCH_ID_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnTrCH_ID_ExtIEsCls) 
	
	switch (val)
	{
		case Sztid_hS_DSCH_MAC_d_Flow_ID:
			CMCHKPK(cmPkSztHS_DSCH_MAC_d_Flow_ID, &param->u.sztHS_DSCH_MAC_d_Flow_ID, mBuf);
			break;
		case Sztid_E_DCH_MAC_d_Flow_ID:
			CMCHKPK(cmPkSztE_DCH_MAC_d_Flow_ID, &param->u.sztE_DCH_MAC_d_Flow_ID, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ExtnTrCH_ID_ExtIEsCls */

/* 
* FUN : cmPkSztProtExtnField_TrCH_ID_ExtIEs
*  DESC: Function to Pack SztProtExtnField_TrCH_ID_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_TrCH_ID_ExtIEs
(
SztProtExtnField_TrCH_ID_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_TrCH_ID_ExtIEs(param, mBuf)
SztProtExtnField_TrCH_ID_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_TrCH_ID_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnTrCH_ID_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_TrCH_ID_ExtIEs */

/* 
* FUN : cmPkSztProtExtnCont_TrCH_ID_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_TrCH_ID_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_TrCH_ID_ExtIEs
(
SztProtExtnCont_TrCH_ID_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_TrCH_ID_ExtIEs(param, mBuf)
SztProtExtnCont_TrCH_ID_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_TrCH_ID_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_TrCH_ID_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_TrCH_ID_ExtIEs */


/* 
* FUN : cmPkSztTrCH_ID_Lst
*  DESC: Function to Pack SztTrCH_ID_Lst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztTrCH_ID_Lst
(
SztTrCH_ID_Lst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztTrCH_ID_Lst(param, mBuf)
SztTrCH_ID_Lst *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztTrCH_ID_Lst) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztTrCH_ID, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztTrCH_ID_Lst */

/* 
* FUN : cmPkSzt_ExtnRAB_TrCH_MappingItem_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnRAB_TrCH_MappingItem_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnRAB_TrCH_MappingItem_ExtIEsCls
(
Szt_ExtnRAB_TrCH_MappingItem_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnRAB_TrCH_MappingItem_ExtIEsCls(param, val, mBuf)
Szt_ExtnRAB_TrCH_MappingItem_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnRAB_TrCH_MappingItem_ExtIEsCls) 
	
	switch (val)
	{
		case Sztid_CN_DomainIndicator:
			CMCHKPK(cmPkSztCN_DomainIndicator, &param->u.sztCN_DomainIndicator, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ExtnRAB_TrCH_MappingItem_ExtIEsCls */




/* 
* FUN : cmPkSztProtExtnField_RAB_TrCH_MappingItem_ExtIEs
*  DESC: Function to Pack SztProtExtnField_RAB_TrCH_MappingItem_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_RAB_TrCH_MappingItem_ExtIEs
(
SztProtExtnField_RAB_TrCH_MappingItem_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_RAB_TrCH_MappingItem_ExtIEs(param, mBuf)
SztProtExtnField_RAB_TrCH_MappingItem_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_RAB_TrCH_MappingItem_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnRAB_TrCH_MappingItem_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_RAB_TrCH_MappingItem_ExtIEs */




/* 
* FUN : cmPkSztProtExtnCont_RAB_TrCH_MappingItem_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_RAB_TrCH_MappingItem_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_RAB_TrCH_MappingItem_ExtIEs
(
SztProtExtnCont_RAB_TrCH_MappingItem_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_RAB_TrCH_MappingItem_ExtIEs(param, mBuf)
SztProtExtnCont_RAB_TrCH_MappingItem_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_RAB_TrCH_MappingItem_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_RAB_TrCH_MappingItem_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_RAB_TrCH_MappingItem_ExtIEs */

/* 
* FUN : cmPkSztRAB_TrCH_MappingItem
*  DESC: Function to Pack SztRAB_TrCH_MappingItem structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztRAB_TrCH_MappingItem
(
SztRAB_TrCH_MappingItem *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztRAB_TrCH_MappingItem(param, mBuf)
SztRAB_TrCH_MappingItem *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztRAB_TrCH_MappingItem) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_RAB_TrCH_MappingItem_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztTrCH_ID_Lst, &param->trCH_ID_Lst, mBuf); 
		CMCHKPK(cmPkSztRAB_ID, &param->rAB_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztRAB_TrCH_MappingItem */

/* 
* FUN : cmPkSztRAB_TrCH_Mapping
*  DESC: Function to Pack SztRAB_TrCH_Mapping structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztRAB_TrCH_Mapping
(
SztRAB_TrCH_Mapping *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztRAB_TrCH_Mapping(param, mBuf)
SztRAB_TrCH_Mapping *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztRAB_TrCH_Mapping) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztRAB_TrCH_MappingItem, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztRAB_TrCH_Mapping */

/*
 * * FUN : cmPkSztSrcRNC_ToTgetRNC_TprntCont
 * *  DESC: Function to Pack SztSrcRNC_ToTgetRNC_TprntCont structure
 * * RETURN: ROK - OK
 * */
#ifdef ANSI
PUBLIC S16 cmPkSztSrcRNC_ToTgetRNC_TprntCont
(
 SztSrcRNC_ToTgetRNC_TprntCont_3gasn *param,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmPkSztSrcRNC_ToTgetRNC_TprntCont(param, mBuf)
   SztSrcRNC_ToTgetRNC_TprntCont_3gasn *param;
   Buffer *mBuf;
#endif
{

   TRC3(cmPkSztSrcRNC_ToTgetRNC_TprntCont)

      if( param->pres.pres != NOTPRSNT )
      {
         CMCHKPK(cmPkSztProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEs, &param->iE_Extns, mBuf);
         CMCHKPK(cmPkSztRAB_TrCH_Mapping, &param->rAB_TrCH_Mapping, mBuf);
         CMCHKPK(cmPkSztTgetCellId, &param->targetCellId, mBuf);
         CMCHKPK(cmPkSztD_RNTI, &param->d_RNTI, mBuf);
         CMCHKPK(cmPkSztChosenEncryptionAlgorithm, &param->chosenEncryptionAlgorithForPS, mBuf);
         CMCHKPK(cmPkSztChosenEncryptionAlgorithm, &param->chosenEncryptionAlgorithForCS, mBuf);
         CMCHKPK(cmPkSztEncryptionKey, &param->cipheringKey, mBuf);
         CMCHKPK(cmPkSztChosenEncryptionAlgorithm, &param->chosenEncryptionAlgorithForSignalling, mBuf);
         CMCHKPK(cmPkSztIntegrityProtectionKey, &param->integrityProtectionKey, mBuf);
         CMCHKPK(cmPkSztChosenIntegrityProtectionAlgorithm, &param->chosenIntegrityProtectionAlgorithm, mBuf);
         CMCHKPK(cmPkSztRelocationTyp, &param->relocationTyp, mBuf);
         CMCHKPK(cmPkSztNumberOfIuInstances, &param->numberOfIuInstances, mBuf);
         CMCHKPK(cmPkSztRRC_Cont, &param->rRC_Cont, mBuf);
      }
   CMCHKPK(cmPkTknPres, &param->pres, mBuf);
   RETVALUE(ROK);
}	 /* End of function cmPkSztSrcRNC_ToTgetRNC_TprntCont */

/* 
* FUN : cmPkSzt_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsCls
(
Szt_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsCls(param, val, mBuf)
Szt_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsCls */

/* 
* FUN : cmPkSztProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEs
*  DESC: Function to Pack SztProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEs
(
SztProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEs(param, mBuf)
SztProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEs */

/* 
* FUN : cmPkSztProtExtnCont_TgetRNC_ToSrcRNC_TprntCont_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_TgetRNC_ToSrcRNC_TprntCont_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_TgetRNC_ToSrcRNC_TprntCont_ExtIEs
(
SztProtExtnCont_TgetRNC_ToSrcRNC_TprntCont_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_TgetRNC_ToSrcRNC_TprntCont_ExtIEs(param, mBuf)
SztProtExtnCont_TgetRNC_ToSrcRNC_TprntCont_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_TgetRNC_ToSrcRNC_TprntCont_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_TgetRNC_ToSrcRNC_TprntCont_ExtIEs */

/* 
* FUN : cmPkSztTgetRNC_ToSrcRNC_TprntCont
*  DESC: Function to Pack SztTgetRNC_ToSrcRNC_TprntCont structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztTgetRNC_ToSrcRNC_TprntCont
(
SztTgetRNC_ToSrcRNC_TprntCont_3gasn *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztTgetRNC_ToSrcRNC_TprntCont(param, mBuf)
SztTgetRNC_ToSrcRNC_TprntCont_3gasn *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztTgetRNC_ToSrcRNC_TprntCont) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_TgetRNC_ToSrcRNC_TprntCont_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztD_RNTI, &param->d_RNTI, mBuf); 
		CMCHKPK(cmPkSztRRC_Cont, &param->rRC_Cont, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztTgetRNC_ToSrcRNC_TprntCont */

/**********************************************************************
 
         End of file:     szt_3gpk.c

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
   $SID$    szt_3gpk_c_001.main_1   akaranth 1. Support for Source RNC to Target RNC TC Enc/Dec.

*********************************************************************91*/
