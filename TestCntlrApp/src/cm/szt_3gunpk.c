
/***********************************************************************

************************************************************************

     Name: S1AP Layer

     Type: C Soruce code File

     Desc: Primitives for pack of szt interface

     File: szt_3gunpk.c

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
#include "szt_3gunpk.x"

/* szt_3gunpk_c_001.main_1: Support for Source RNC to Target RNC TC Enc/Dec. */

#define cmUnpkSztRRC_Cont cmUnpkTknStrOSXL 
#define cmUnpkSztD_RNTI cmUnpkTknU32 
#define cmUnpkSztProtExtnID cmUnpkTknU32 
#define cmUnpkSztCriticality cmUnpkTknU32
#define cmUnpkSztRRC_Cont cmUnpkTknStrOSXL 
#define cmUnpkSztNumberOfIuInstances cmUnpkTknU32 
#define cmUnpkSztRelocationTyp cmUnpkTknU32
#define cmUnpkSztIntegrityProtectionAlgorithm cmUnpkTknU32 
/* Element ------------- ChosenIntegrityProtectionAlgorithm ------------ */
#define cmUnpkSztChosenIntegrityProtectionAlgorithm cmUnpkTknU8 
#define cmUnpkSztIntegrityProtectionKey cmUnpkTknStrBSXL 
#define cmUnpkSztEncryptionAlgorithm cmUnpkTknU32 
/* Element ------------- ChosenEncryptionAlgorithm ------------ */
#define cmUnpkSztChosenEncryptionAlgorithm cmUnpkTknU8
#define cmUnpkSztEncryptionKey cmUnpkTknStrBSXL 
#define cmUnpkSztD_RNTI cmUnpkTknU32 
#define cmUnpkSztTgetCellId cmUnpkTknU32 
#define cmUnpkSztRAB_ID cmUnpkTknBStr32 
#define cmUnpkSztDCH_ID cmUnpkTknU32 
#define cmUnpkSztDSCH_ID cmUnpkTknU32 
#define cmUnpkSztUSCH_ID cmUnpkTknU32 
#define cmUnpkSztHS_DSCH_MAC_d_Flow_ID cmUnpkTknU32 
#define cmUnpkSztE_DCH_MAC_d_Flow_ID cmUnpkTknU32 
#define cmUnpkSztCN_DomainIndicator cmUnpkTknU32
#define cmUnpkSztSRB_ID cmUnpkTknU32 
#define cmUnpkSztDCH_ID cmUnpkTknU32 
#define cmUnpkSztDSCH_ID cmUnpkTknU32 
#define cmUnpkSztUSCH_ID cmUnpkTknU32 
#define cmUnpkSztHS_DSCH_MAC_d_Flow_ID cmUnpkTknU32 
#define cmUnpkSztE_DCH_MAC_d_Flow_ID cmUnpkTknU32 
#define cmUnpkSztTBCD_STRING cmUnpkTknStrOSXL 
/* Element ------------- PLMNidentity ------------ */
#define cmUnpkSztPLMNidentity cmUnpkSztTBCD_STRING
#define cmUnpkSztTgetCellId cmUnpkTknU32 
#define cmUnpkSztTBCD_STRING cmUnpkTknStrOSXL 
/* Element ------------- PLMNidentity ------------ */
#define cmUnpkSztPLMNidentity cmUnpkSztTBCD_STRING
#define cmUnpkSztLAC cmUnpkTknStr4 
#define cmUnpkSztCI cmUnpkTknStr4 
#define cmUnpkSzt3gRAC cmUnpkTknStr4 
#define cmUnpkSztCell_Capacity_Class_Value cmUnpkTknU32 
#define cmUnpkSztLoadValue cmUnpkTknU32 
#define cmUnpkSztRTLoadValue cmUnpkTknU32 
#define cmUnpkSztNRTLoadInformValue cmUnpkTknU32 
#define cmUnpkSztTraceReference cmUnpkTknStrOSXL 
#define cmUnpkSztTraceRecordingSessionReference cmUnpkTknU32 
#define cmUnpkSztMBMSLinkingInform cmUnpkTknU32
#define cmUnpkSztD_RNTI cmUnpkTknU32 
#define cmUnpkSztUE_History_Inform cmUnpkTknStrOSXL 
#define cmUnpkSztSubscriberProfileIDforRFP cmUnpkTknU32 
#define cmUnpkSztSRVCC_Informnonce cmUnpkTknStrBSXL 
#define cmUnpkSztCSFB_Inform cmUnpkTknU32


/*
* FUN : cmUnpkSzt_ExtnTrCH_ID_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnTrCH_ID_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnTrCH_ID_ExtIEsCls
(
Szt_ExtnTrCH_ID_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnTrCH_ID_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnTrCH_ID_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnTrCH_ID_ExtIEsCls) 
	
	switch (val)
	{
		case Sztid_hS_DSCH_MAC_d_Flow_ID:
			CMCHKUNPK(cmUnpkSztHS_DSCH_MAC_d_Flow_ID, &param->u.sztHS_DSCH_MAC_d_Flow_ID, mBuf); 
			break;
		case Sztid_E_DCH_MAC_d_Flow_ID:
			CMCHKUNPK(cmUnpkSztE_DCH_MAC_d_Flow_ID, &param->u.sztE_DCH_MAC_d_Flow_ID, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ExtnTrCH_ID_ExtIEsCls */

/*
* FUN : cmUnpkSztProtExtnField_TrCH_ID_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_TrCH_ID_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_TrCH_ID_ExtIEs
(
SztProtExtnField_TrCH_ID_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_TrCH_ID_ExtIEs(param, ptr, mBuf)
SztProtExtnField_TrCH_ID_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_TrCH_ID_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnTrCH_ID_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_TrCH_ID_ExtIEs */

/*
* FUN : cmUnpkSztProtExtnCont_TrCH_ID_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_TrCH_ID_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_TrCH_ID_ExtIEs
(
SztProtExtnCont_TrCH_ID_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_TrCH_ID_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_TrCH_ID_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_TrCH_ID_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_TrCH_ID_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_TrCH_ID_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_TrCH_ID_ExtIEs */

/*
* FUN : cmUnpkSzt_ExtnRAB_TrCH_MappingItem_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnRAB_TrCH_MappingItem_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnRAB_TrCH_MappingItem_ExtIEsCls
(
Szt_ExtnRAB_TrCH_MappingItem_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnRAB_TrCH_MappingItem_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnRAB_TrCH_MappingItem_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnRAB_TrCH_MappingItem_ExtIEsCls) 
	
	switch (val)
	{
		case Sztid_CN_DomainIndicator:
			CMCHKUNPK(cmUnpkSztCN_DomainIndicator, &param->u.sztCN_DomainIndicator, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ExtnRAB_TrCH_MappingItem_ExtIEsCls */

/*
* FUN : cmUnpkSztProtExtnField_RAB_TrCH_MappingItem_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_RAB_TrCH_MappingItem_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_RAB_TrCH_MappingItem_ExtIEs
(
SztProtExtnField_RAB_TrCH_MappingItem_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_RAB_TrCH_MappingItem_ExtIEs(param, ptr, mBuf)
SztProtExtnField_RAB_TrCH_MappingItem_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_RAB_TrCH_MappingItem_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnRAB_TrCH_MappingItem_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_RAB_TrCH_MappingItem_ExtIEs */

/*
* FUN : cmUnpkSztProtExtnCont_RAB_TrCH_MappingItem_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_RAB_TrCH_MappingItem_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_RAB_TrCH_MappingItem_ExtIEs
(
SztProtExtnCont_RAB_TrCH_MappingItem_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_RAB_TrCH_MappingItem_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_RAB_TrCH_MappingItem_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_RAB_TrCH_MappingItem_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_RAB_TrCH_MappingItem_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_RAB_TrCH_MappingItem_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_RAB_TrCH_MappingItem_ExtIEs */

/*
* FUN : cmUnpkSztTrCH_ID
*  DESC: Function to Unpack SztTrCH_ID structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztTrCH_ID
(
SztTrCH_ID *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztTrCH_ID(param, ptr, mBuf)
SztTrCH_ID *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztTrCH_ID) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztDCH_ID, &param->dCH_ID, mBuf); 
		CMCHKUNPK(cmUnpkSztDSCH_ID, &param->dSCH_ID, mBuf); 
		CMCHKUNPK(cmUnpkSztUSCH_ID, &param->uSCH_ID, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_TrCH_ID_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztTrCH_ID */

/*
* FUN : cmUnpkSztTrCH_ID_Lst
*  DESC: Function to Unpack SztTrCH_ID_Lst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztTrCH_ID_Lst
(
SztTrCH_ID_Lst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztTrCH_ID_Lst(param, ptr, mBuf)
SztTrCH_ID_Lst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztTrCH_ID_Lst) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztTrCH_ID)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztTrCH_ID, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztTrCH_ID_Lst */

/*
* FUN : cmUnpkSztRAB_TrCH_MappingItem
*  DESC: Function to Unpack SztRAB_TrCH_MappingItem structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztRAB_TrCH_MappingItem
(
SztRAB_TrCH_MappingItem *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztRAB_TrCH_MappingItem(param, ptr, mBuf)
SztRAB_TrCH_MappingItem *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztRAB_TrCH_MappingItem) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztRAB_ID, &param->rAB_ID, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztTrCH_ID_Lst, &param->trCH_ID_Lst, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_RAB_TrCH_MappingItem_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztRAB_TrCH_MappingItem */

/*
* FUN : cmUnpkSztRAB_TrCH_Mapping
*  DESC: Function to Unpack SztRAB_TrCH_Mapping structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztRAB_TrCH_Mapping
(
SztRAB_TrCH_Mapping *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztRAB_TrCH_Mapping(param, ptr, mBuf)
SztRAB_TrCH_Mapping *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztRAB_TrCH_Mapping) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztRAB_TrCH_MappingItem)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztRAB_TrCH_MappingItem, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztRAB_TrCH_Mapping */

/*
* FUN : cmUnpkSzt_ExtnSRB_TrCH_MappingItem_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnSRB_TrCH_MappingItem_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnSRB_TrCH_MappingItem_ExtIEsCls
(
Szt_ExtnSRB_TrCH_MappingItem_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnSRB_TrCH_MappingItem_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnSRB_TrCH_MappingItem_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnSRB_TrCH_MappingItem_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnSRB_TrCH_MappingItem_ExtIEsCls */

/*
* FUN : cmUnpkSztProtExtnField_SRB_TrCH_MappingItem_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_SRB_TrCH_MappingItem_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_SRB_TrCH_MappingItem_ExtIEs
(
SztProtExtnField_SRB_TrCH_MappingItem_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_SRB_TrCH_MappingItem_ExtIEs(param, ptr, mBuf)
SztProtExtnField_SRB_TrCH_MappingItem_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_SRB_TrCH_MappingItem_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnSRB_TrCH_MappingItem_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_SRB_TrCH_MappingItem_ExtIEs */

/*
* FUN : cmUnpkSztProtExtnCont_SRB_TrCH_MappingItem_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_SRB_TrCH_MappingItem_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_SRB_TrCH_MappingItem_ExtIEs
(
SztProtExtnCont_SRB_TrCH_MappingItem_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_SRB_TrCH_MappingItem_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_SRB_TrCH_MappingItem_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_SRB_TrCH_MappingItem_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_SRB_TrCH_MappingItem_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_SRB_TrCH_MappingItem_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_SRB_TrCH_MappingItem_ExtIEs */

/*
* FUN : cmUnpkSztSRB_TrCH_MappingItem
*  DESC: Function to Unpack SztSRB_TrCH_MappingItem structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztSRB_TrCH_MappingItem
(
SztSRB_TrCH_MappingItem *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztSRB_TrCH_MappingItem(param, ptr, mBuf)
SztSRB_TrCH_MappingItem *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztSRB_TrCH_MappingItem) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztSRB_ID, &param->sRB_ID, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztTrCH_ID, &param->trCH_ID, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_SRB_TrCH_MappingItem_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztSRB_TrCH_MappingItem */

/*
* FUN : cmUnpkSztSRB_TrCH_Mapping
*  DESC: Function to Unpack SztSRB_TrCH_Mapping structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztSRB_TrCH_Mapping
(
SztSRB_TrCH_Mapping *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztSRB_TrCH_Mapping(param, ptr, mBuf)
SztSRB_TrCH_Mapping *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztSRB_TrCH_Mapping) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztSRB_TrCH_MappingItem)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztSRB_TrCH_MappingItem, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztSRB_TrCH_Mapping */

/*
* FUN : cmUnpkSzt_ExtnSrcUTRANCellID_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnSrcUTRANCellID_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnSrcUTRANCellID_ExtIEsCls
(
Szt_ExtnSrcUTRANCellID_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnSrcUTRANCellID_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnSrcUTRANCellID_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnSrcUTRANCellID_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnSrcUTRANCellID_ExtIEsCls */

/*
* FUN : cmUnpkSztProtExtnField_SrcUTRANCellID_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_SrcUTRANCellID_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_SrcUTRANCellID_ExtIEs
(
SztProtExtnField_SrcUTRANCellID_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_SrcUTRANCellID_ExtIEs(param, ptr, mBuf)
SztProtExtnField_SrcUTRANCellID_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_SrcUTRANCellID_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnSrcUTRANCellID_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_SrcUTRANCellID_ExtIEs */

/*
* FUN : cmUnpkSztProtExtnCont_SrcUTRANCellID_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_SrcUTRANCellID_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_SrcUTRANCellID_ExtIEs
(
SztProtExtnCont_SrcUTRANCellID_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_SrcUTRANCellID_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_SrcUTRANCellID_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_SrcUTRANCellID_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_SrcUTRANCellID_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_SrcUTRANCellID_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_SrcUTRANCellID_ExtIEs */

/*
* FUN : cmUnpkSztSrcUTRANCellID
*  DESC: Function to Unpack SztSrcUTRANCellID structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztSrcUTRANCellID
(
SztSrcUTRANCellID *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztSrcUTRANCellID(param, ptr, mBuf)
SztSrcUTRANCellID *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztSrcUTRANCellID) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		SZUCHKUNPKPTR(cmUnpkSztPLMNidentity, &param->pLMNidentity, ptr, mBuf); 
		CMCHKUNPK(cmUnpkSztTgetCellId, &param->uTRANcellID, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_SrcUTRANCellID_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztSrcUTRANCellID */

/*
* FUN : cmUnpkSzt3g_ExtnCGI_ExtIEsCls
*  DESC: Function to Unpack Szt3g_ExtnCGI_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt3g_ExtnCGI_ExtIEsCls
(
Szt3g_ExtnCGI_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt3g_ExtnCGI_ExtIEsCls(param, val, ptr, mBuf)
Szt3g_ExtnCGI_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt3g_ExtnCGI_ExtIEsCls) 
	
	switch (val)
	{
		case Sztid_RAC:
			CMCHKUNPK(cmUnpkSzt3gRAC, &param->u.sztRAC, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt3g_ExtnCGI_ExtIEsCls */

/*
* FUN : cmUnpkSzt3gProtExtnField_CGI_ExtIEs
*  DESC: Function to Unpack Szt3gProtExtnField_CGI_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt3gProtExtnField_CGI_ExtIEs
(
Szt3gProtExtnField_CGI_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt3gProtExtnField_CGI_ExtIEs(param, ptr, mBuf)
Szt3gProtExtnField_CGI_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt3gProtExtnField_CGI_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt3g_ExtnCGI_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt3gProtExtnField_CGI_ExtIEs */

/*
* FUN : cmUnpkSzt3gProtExtnCont_CGI_ExtIEs
*  DESC: Function to Unpack Szt3gProtExtnCont_CGI_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt3gProtExtnCont_CGI_ExtIEs
(
Szt3gProtExtnCont_CGI_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt3gProtExtnCont_CGI_ExtIEs(param, ptr, mBuf)
Szt3gProtExtnCont_CGI_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSzt3gProtExtnCont_CGI_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_CGI_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSzt3gProtExtnField_CGI_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSzt3gProtExtnCont_CGI_ExtIEs */

/*
* FUN : cmUnpkSzt3gCGI
*  DESC: Function to Unpack Szt3gCGI structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt3gCGI
(
Szt3gCGI *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt3gCGI(param, ptr, mBuf)
Szt3gCGI *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt3gCGI) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		SZUCHKUNPKPTR(cmUnpkSztPLMNidentity, &param->pLMNidentity, ptr, mBuf); 
		CMCHKUNPK(cmUnpkSztLAC, &param->lAC, mBuf); 
		CMCHKUNPK(cmUnpkSztCI, &param->cI, mBuf); 
		CMCHKUNPKPTR(cmUnpkSzt3gProtExtnCont_CGI_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt3gCGI */

/*
* FUN : cmUnpkSztSrcCellID
*  DESC: Function to Unpack SztSrcCellID structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztSrcCellID
(
SztSrcCellID *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztSrcCellID(param, ptr, mBuf)
SztSrcCellID *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztSrcCellID) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case SRCCELLID_SOURCEUTRANCELLID :
				CMCHKUNPKPTR(cmUnpkSztSrcUTRANCellID, &param->val.sourceUTRANCellID, ptr, mBuf); 
				break;
			case SRCCELLID_SOURCEGERANCELLID :
				CMCHKUNPKPTR(cmUnpkSzt3gCGI, &param->val.sourceGERANCellID, ptr, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztSrcCellID */


/*
* FUN : cmUnpkSzt_ExtnCellLoadInform_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnCellLoadInform_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnCellLoadInform_ExtIEsCls
(
Szt_ExtnCellLoadInform_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnCellLoadInform_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnCellLoadInform_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnCellLoadInform_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnCellLoadInform_ExtIEsCls */

/*
* FUN : cmUnpkSztProtExtnField_CellLoadInform_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_CellLoadInform_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_CellLoadInform_ExtIEs
(
SztProtExtnField_CellLoadInform_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_CellLoadInform_ExtIEs(param, ptr, mBuf)
SztProtExtnField_CellLoadInform_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_CellLoadInform_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnCellLoadInform_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_CellLoadInform_ExtIEs */

/*
* FUN : cmUnpkSztProtExtnCont_CellLoadInform_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_CellLoadInform_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_CellLoadInform_ExtIEs
(
SztProtExtnCont_CellLoadInform_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_CellLoadInform_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_CellLoadInform_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_CellLoadInform_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_CellLoadInform_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_CellLoadInform_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_CellLoadInform_ExtIEs */

/*
* FUN : cmUnpkSztCellLoadInform
*  DESC: Function to Unpack SztCellLoadInform structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztCellLoadInform
(
SztCellLoadInform *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztCellLoadInform(param, ptr, mBuf)
SztCellLoadInform *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztCellLoadInform) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztCell_Capacity_Class_Value, &param->cell_Capacity_Class_Value, mBuf); 
		CMCHKUNPK(cmUnpkSztLoadValue, &param->loadValue, mBuf); 
		CMCHKUNPK(cmUnpkSztRTLoadValue, &param->rTLoadValue, mBuf); 
		CMCHKUNPK(cmUnpkSztNRTLoadInformValue, &param->nRTLoadInformValue, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_CellLoadInform_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztCellLoadInform */

/*
* FUN : cmUnpkSzt_ExtnCellLoadInformGroup_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnCellLoadInformGroup_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnCellLoadInformGroup_ExtIEsCls
(
Szt_ExtnCellLoadInformGroup_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnCellLoadInformGroup_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnCellLoadInformGroup_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnCellLoadInformGroup_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnCellLoadInformGroup_ExtIEsCls */

/*
* FUN : cmUnpkSztProtExtnField_CellLoadInformGroup_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_CellLoadInformGroup_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_CellLoadInformGroup_ExtIEs
(
SztProtExtnField_CellLoadInformGroup_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_CellLoadInformGroup_ExtIEs(param, ptr, mBuf)
SztProtExtnField_CellLoadInformGroup_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_CellLoadInformGroup_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnCellLoadInformGroup_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_CellLoadInformGroup_ExtIEs */

/*
* FUN : cmUnpkSztProtExtnCont_CellLoadInformGroup_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_CellLoadInformGroup_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_CellLoadInformGroup_ExtIEs
(
SztProtExtnCont_CellLoadInformGroup_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_CellLoadInformGroup_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_CellLoadInformGroup_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_CellLoadInformGroup_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_CellLoadInformGroup_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_CellLoadInformGroup_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_CellLoadInformGroup_ExtIEs */

/*
* FUN : cmUnpkSztCellLoadInformGroup
*  DESC: Function to Unpack SztCellLoadInformGroup structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztCellLoadInformGroup
(
SztCellLoadInformGroup *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztCellLoadInformGroup(param, ptr, mBuf)
SztCellLoadInformGroup *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztCellLoadInformGroup) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztSrcCellID, &param->sourceCellID, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztCellLoadInform, &param->uplinkCellLoadInform, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztCellLoadInform, &param->downlinkCellLoadInform, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_CellLoadInformGroup_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztCellLoadInformGroup */

/*
* FUN : cmUnpkSzt_ExtnTraceRecordingSessionInform_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnTraceRecordingSessionInform_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnTraceRecordingSessionInform_ExtIEsCls
(
Szt_ExtnTraceRecordingSessionInform_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnTraceRecordingSessionInform_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnTraceRecordingSessionInform_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnTraceRecordingSessionInform_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnTraceRecordingSessionInform_ExtIEsCls */


/*
* FUN : cmUnpkSztProtExtnField_TraceRecordingSessionInform_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_TraceRecordingSessionInform_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_TraceRecordingSessionInform_ExtIEs
(
SztProtExtnField_TraceRecordingSessionInform_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_TraceRecordingSessionInform_ExtIEs(param, ptr, mBuf)
SztProtExtnField_TraceRecordingSessionInform_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_TraceRecordingSessionInform_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnTraceRecordingSessionInform_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_TraceRecordingSessionInform_ExtIEs */

/*
* FUN : cmUnpkSztProtExtnCont_TraceRecordingSessionInform_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_TraceRecordingSessionInform_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_TraceRecordingSessionInform_ExtIEs
(
SztProtExtnCont_TraceRecordingSessionInform_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_TraceRecordingSessionInform_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_TraceRecordingSessionInform_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_TraceRecordingSessionInform_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_TraceRecordingSessionInform_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_TraceRecordingSessionInform_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_TraceRecordingSessionInform_ExtIEs */

/*
* FUN : cmUnpkSztTraceRecordingSessionInform
*  DESC: Function to Unpack SztTraceRecordingSessionInform structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztTraceRecordingSessionInform
(
SztTraceRecordingSessionInform *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztTraceRecordingSessionInform(param, ptr, mBuf)
SztTraceRecordingSessionInform *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztTraceRecordingSessionInform) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		SZUCHKUNPKPTR(cmUnpkSztTraceReference, &param->traceReference, ptr, mBuf); 
		CMCHKUNPK(cmUnpkSztTraceRecordingSessionReference, &param->traceRecordingSessionReference, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_TraceRecordingSessionInform_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztTraceRecordingSessionInform */

/*
* FUN : cmUnpkSzt_ExtnSRVCC_Inform_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnSRVCC_Inform_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnSRVCC_Inform_ExtIEsCls
(
Szt_ExtnSRVCC_Inform_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnSRVCC_Inform_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnSRVCC_Inform_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnSRVCC_Inform_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnSRVCC_Inform_ExtIEsCls */

/*
* FUN : cmUnpkSztProtExtnField_SRVCC_Inform_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_SRVCC_Inform_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_SRVCC_Inform_ExtIEs
(
SztProtExtnField_SRVCC_Inform_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_SRVCC_Inform_ExtIEs(param, ptr, mBuf)
SztProtExtnField_SRVCC_Inform_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_SRVCC_Inform_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnSRVCC_Inform_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_SRVCC_Inform_ExtIEs */

/*
* FUN : cmUnpkSztProtExtnCont_SRVCC_Inform_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_SRVCC_Inform_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_SRVCC_Inform_ExtIEs
(
SztProtExtnCont_SRVCC_Inform_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_SRVCC_Inform_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_SRVCC_Inform_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_SRVCC_Inform_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_SRVCC_Inform_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_SRVCC_Inform_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_SRVCC_Inform_ExtIEs */

/*
* FUN : cmUnpkSztSRVCC_Inform
*  DESC: Function to Unpack SztSRVCC_Inform structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztSRVCC_Inform
(
SztSRVCC_Inform *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztSRVCC_Inform(param, ptr, mBuf)
SztSRVCC_Inform *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztSRVCC_Inform) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztSRVCC_Informnonce, &param->nonce, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_SRVCC_Inform_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztSRVCC_Inform */


/*
* FUN : cmUnpkSzt_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsCls
(
Szt_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsCls) 
	
	switch (val)
	{
		case Sztid_SRB_TrCH_Mapping:
			CMCHKUNPKPTR(cmUnpkSztSRB_TrCH_Mapping, &param->u.sztSRB_TrCH_Mapping, ptr, mBuf);
			break;
		case Sztid_CellLoadInformGroup:
			CMCHKUNPKPTR(cmUnpkSztCellLoadInformGroup, &param->u.sztCellLoadInformGroup, ptr, mBuf);
			break;
		case Sztid_TraceRecordingSessionInform:
			CMCHKUNPKPTR(cmUnpkSztTraceRecordingSessionInform, &param->u.sztTraceRecordingSessionInform, ptr, mBuf);
			break;
		case Sztid_MBMSLinkingInform:
			CMCHKUNPK(cmUnpkSztMBMSLinkingInform, &param->u.sztMBMSLinkingInform, mBuf); 
			break;
		case Sztid_d_RNTI_for_NoIuCSUP:
			CMCHKUNPK(cmUnpkSztD_RNTI, &param->u.sztD_RNTI, mBuf); 
			break;
		case Sztid_UE_History_Inform:
			SZUCHKUNPKPTR(cmUnpkSztUE_History_Inform, &param->u.sztUE_History_Inform, ptr, mBuf); 
			break;
		case Sztid_SubscriberProfileIDforRFP:
			CMCHKUNPK(cmUnpkSztSubscriberProfileIDforRFP, &param->u.sztSubscriberProfileIDforRFP, mBuf); 
			break;
		case Sztid_SRVCC_Inform:
			CMCHKUNPKPTR(cmUnpkSztSRVCC_Inform, &param->u.sztSRVCC_Inform, ptr, mBuf);
			break;
		case Sztid_PSRABtobeReplaced:
			CMCHKUNPK(cmUnpkSztRAB_ID, &param->u.sztRAB_ID, mBuf); 
			break;
		case Sztid_CSFB_Inform:
			CMCHKUNPK(cmUnpkSztCSFB_Inform, &param->u.sztCSFB_Inform, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsCls */

/*
* FUN : cmUnpkSztProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEs
(
SztProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEs(param, ptr, mBuf)
SztProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEs */

/*
* FUN : cmUnpkSztProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEs
(
SztProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEs */

/*
* FUN : cmUnpkSztSrcRNC_ToTgetRNC_TprntCont
*  DESC: Function to Unpack SztSrcRNC_ToTgetRNC_TprntCont_3gasn structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztSrcRNC_ToTgetRNC_TprntCont
(
SztSrcRNC_ToTgetRNC_TprntCont_3gasn *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztSrcRNC_ToTgetRNC_TprntCont(param, ptr, mBuf)
SztSrcRNC_ToTgetRNC_TprntCont_3gasn *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztSrcRNC_ToTgetRNC_TprntCont) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		SZUCHKUNPKPTR(cmUnpkSztRRC_Cont, &param->rRC_Cont, ptr, mBuf); 
		CMCHKUNPK(cmUnpkSztNumberOfIuInstances, &param->numberOfIuInstances, mBuf); 
		CMCHKUNPK(cmUnpkSztRelocationTyp, &param->relocationTyp, mBuf); 
		CMCHKUNPK(cmUnpkSztChosenIntegrityProtectionAlgorithm, &param->chosenIntegrityProtectionAlgorithm, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztIntegrityProtectionKey, &param->integrityProtectionKey, ptr, mBuf); 
		CMCHKUNPK(cmUnpkSztChosenEncryptionAlgorithm, &param->chosenEncryptionAlgorithForSignalling, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztEncryptionKey, &param->cipheringKey, ptr, mBuf); 
		CMCHKUNPK(cmUnpkSztChosenEncryptionAlgorithm, &param->chosenEncryptionAlgorithForCS, mBuf); 
		CMCHKUNPK(cmUnpkSztChosenEncryptionAlgorithm, &param->chosenEncryptionAlgorithForPS, mBuf); 
		CMCHKUNPK(cmUnpkSztD_RNTI, &param->d_RNTI, mBuf); 
		CMCHKUNPK(cmUnpkSztTgetCellId, &param->targetCellId, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztRAB_TrCH_Mapping, &param->rAB_TrCH_Mapping, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztSrcRNC_ToTgetRNC_TprntCont */

/*
* FUN : cmUnpkSzt_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsCls
(
Szt_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsCls */

/*
* FUN : cmUnpkSztProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEs
(
SztProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEs(param, ptr, mBuf)
SztProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEs */

/*
* FUN : cmUnpkSztProtExtnCont_TgetRNC_ToSrcRNC_TprntCont_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_TgetRNC_ToSrcRNC_TprntCont_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_TgetRNC_ToSrcRNC_TprntCont_ExtIEs
(
SztProtExtnCont_TgetRNC_ToSrcRNC_TprntCont_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_TgetRNC_ToSrcRNC_TprntCont_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_TgetRNC_ToSrcRNC_TprntCont_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_TgetRNC_ToSrcRNC_TprntCont_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_TgetRNC_ToSrcRNC_TprntCont_ExtIEs */

/*
* FUN : cmUnpkSztTgetRNC_ToSrcRNC_TprntCont
*  DESC: Function to Unpack SztTgetRNC_ToSrcRNC_TprntCont_3gasn structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztTgetRNC_ToSrcRNC_TprntCont
(
SztTgetRNC_ToSrcRNC_TprntCont_3gasn *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztTgetRNC_ToSrcRNC_TprntCont(param, ptr, mBuf)
SztTgetRNC_ToSrcRNC_TprntCont_3gasn *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztTgetRNC_ToSrcRNC_TprntCont) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		SZUCHKUNPKPTR(cmUnpkSztRRC_Cont, &param->rRC_Cont, ptr, mBuf); 
		CMCHKUNPK(cmUnpkSztD_RNTI, &param->d_RNTI, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_TgetRNC_ToSrcRNC_TprntCont_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztTgetRNC_ToSrcRNC_TprntCont */


/**********************************************************************
 
         End of file:     szt_3gunpk.c

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
$SID$  szt_3gunpk_c_001.main_1 akaranth 1. Support for Source RNC to Target RNC TC Enc/Dec.

*********************************************************************91*/
