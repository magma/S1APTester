/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_smm_init.c

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/

#include "envopt.h"           /* environment options */
#include "envdep.h"           /* environment dependent */
#include "envind.h"           /* environment independent */
#include "gen.h"              /* general layer */
#include "ssi.h"              /* system services */
#include "cm_mblk.h"
#include "cm_tkns.h"
#include "cm_pasn.h"          /* common defines for ASN */
#include "cm_umts.h"
#include "gen.x"              /* general layer */
#include "ssi.x"              /* system services */
#include "cm_tkns.x"          /* */
#include "cm_mblk.x"
#include "cm_pasn.x"          /* PASN */
#include <szt_asn.h>
#include <szt_asn.x>
#include <szt_pk.x>

#define cmPkSztCriticality cmPkTknU32
#define cmPkSztPresence cmPkTknU32
#define cmPkSztPrivIE_IDlocal cmPkTknU32 


/* 
* FUN : cmPkSztPrivIE_ID
*  DESC: Function to Pack SztPrivIE_ID structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztPrivIE_ID
(
SztPrivIE_ID *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztPrivIE_ID(param, mBuf)
SztPrivIE_ID *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztPrivIE_ID) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case PRIVIE_ID_GLOBAL :
				break;
			case PRIVIE_ID_LOCAL :
				CMCHKPK(cmPkSztPrivIE_IDlocal, &param->val.local, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztPrivIE_ID */

#define cmPkSztProcedureCode cmPkTknU32 
#define cmPkSztProtExtnID cmPkTknU32 
#define cmPkSztProtIE_ID cmPkTknU32 
#define cmPkSztTrgMsg cmPkTknU32
#define cmPkSztTBCD_STRING cmPkTknStrOSXL 
/* Element ------------- PLMNidentity ------------ */
#define cmPkSztPLMNidentity cmPkSztTBCD_STRING
#define cmPkSztCellIdentity cmPkTknBStr32 


/* 
* FUN : cmPkSzt_ExtnEUTRAN_CGI_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnEUTRAN_CGI_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnEUTRAN_CGI_ExtIEsCls
(
Szt_ExtnEUTRAN_CGI_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnEUTRAN_CGI_ExtIEsCls(param, val, mBuf)
Szt_ExtnEUTRAN_CGI_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnEUTRAN_CGI_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnEUTRAN_CGI_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_EUTRAN_CGI_ExtIEs
*  DESC: Function to Pack SztProtExtnField_EUTRAN_CGI_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_EUTRAN_CGI_ExtIEs
(
SztProtExtnField_EUTRAN_CGI_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_EUTRAN_CGI_ExtIEs(param, mBuf)
SztProtExtnField_EUTRAN_CGI_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_EUTRAN_CGI_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnEUTRAN_CGI_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_EUTRAN_CGI_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_EUTRAN_CGI_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_EUTRAN_CGI_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_EUTRAN_CGI_ExtIEs
(
SztProtExtnCont_EUTRAN_CGI_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_EUTRAN_CGI_ExtIEs(param, mBuf)
SztProtExtnCont_EUTRAN_CGI_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_EUTRAN_CGI_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_EUTRAN_CGI_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_EUTRAN_CGI_ExtIEs */



/* 
* FUN : cmPkSztEUTRAN_CGI
*  DESC: Function to Pack SztEUTRAN_CGI structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztEUTRAN_CGI
(
SztEUTRAN_CGI *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztEUTRAN_CGI(param, mBuf)
SztEUTRAN_CGI *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztEUTRAN_CGI) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_EUTRAN_CGI_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztCellIdentity, &param->cell_ID, mBuf); 
		CMCHKPK(cmPkSztPLMNidentity, &param->pLMNidentity, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztEUTRAN_CGI */



/* 
* FUN : cmPkSztCellIdLstforMDT
*  DESC: Function to Pack SztCellIdLstforMDT structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztCellIdLstforMDT
(
SztCellIdLstforMDT *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztCellIdLstforMDT(param, mBuf)
SztCellIdLstforMDT *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztCellIdLstforMDT) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztEUTRAN_CGI, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztCellIdLstforMDT */



/* 
* FUN : cmPkSzt_ExtnCellBasedMDT_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnCellBasedMDT_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnCellBasedMDT_ExtIEsCls
(
Szt_ExtnCellBasedMDT_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnCellBasedMDT_ExtIEsCls(param, val, mBuf)
Szt_ExtnCellBasedMDT_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnCellBasedMDT_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnCellBasedMDT_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_CellBasedMDT_ExtIEs
*  DESC: Function to Pack SztProtExtnField_CellBasedMDT_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_CellBasedMDT_ExtIEs
(
SztProtExtnField_CellBasedMDT_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_CellBasedMDT_ExtIEs(param, mBuf)
SztProtExtnField_CellBasedMDT_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_CellBasedMDT_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnCellBasedMDT_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_CellBasedMDT_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_CellBasedMDT_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_CellBasedMDT_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_CellBasedMDT_ExtIEs
(
SztProtExtnCont_CellBasedMDT_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_CellBasedMDT_ExtIEs(param, mBuf)
SztProtExtnCont_CellBasedMDT_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_CellBasedMDT_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_CellBasedMDT_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_CellBasedMDT_ExtIEs */



/* 
* FUN : cmPkSztCellBasedMDT
*  DESC: Function to Pack SztCellBasedMDT structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztCellBasedMDT
(
SztCellBasedMDT *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztCellBasedMDT(param, mBuf)
SztCellBasedMDT *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztCellBasedMDT) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_CellBasedMDT_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztCellIdLstforMDT, &param->cellIdLstforMDT, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztCellBasedMDT */

#define cmPkSztTAC cmPkTknStr4 


/* 
* FUN : cmPkSztTALstforMDT
*  DESC: Function to Pack SztTALstforMDT structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztTALstforMDT
(
SztTALstforMDT *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztTALstforMDT(param, mBuf)
SztTALstforMDT *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztTALstforMDT) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztTAC, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztTALstforMDT */



/* 
* FUN : cmPkSzt_ExtnTABasedMDT_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnTABasedMDT_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnTABasedMDT_ExtIEsCls
(
Szt_ExtnTABasedMDT_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnTABasedMDT_ExtIEsCls(param, val, mBuf)
Szt_ExtnTABasedMDT_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnTABasedMDT_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnTABasedMDT_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_TABasedMDT_ExtIEs
*  DESC: Function to Pack SztProtExtnField_TABasedMDT_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_TABasedMDT_ExtIEs
(
SztProtExtnField_TABasedMDT_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_TABasedMDT_ExtIEs(param, mBuf)
SztProtExtnField_TABasedMDT_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_TABasedMDT_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnTABasedMDT_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_TABasedMDT_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_TABasedMDT_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_TABasedMDT_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_TABasedMDT_ExtIEs
(
SztProtExtnCont_TABasedMDT_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_TABasedMDT_ExtIEs(param, mBuf)
SztProtExtnCont_TABasedMDT_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_TABasedMDT_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_TABasedMDT_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_TABasedMDT_ExtIEs */



/* 
* FUN : cmPkSztTABasedMDT
*  DESC: Function to Pack SztTABasedMDT structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztTABasedMDT
(
SztTABasedMDT *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztTABasedMDT(param, mBuf)
SztTABasedMDT *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztTABasedMDT) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_TABasedMDT_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztTALstforMDT, &param->tALstforMDT, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztTABasedMDT */



/* 
* FUN : cmPkSzt_ExtnTAI_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnTAI_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnTAI_ExtIEsCls
(
Szt_ExtnTAI_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnTAI_ExtIEsCls(param, val, mBuf)
Szt_ExtnTAI_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnTAI_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnTAI_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_TAI_ExtIEs
*  DESC: Function to Pack SztProtExtnField_TAI_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_TAI_ExtIEs
(
SztProtExtnField_TAI_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_TAI_ExtIEs(param, mBuf)
SztProtExtnField_TAI_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_TAI_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnTAI_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_TAI_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_TAI_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_TAI_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_TAI_ExtIEs
(
SztProtExtnCont_TAI_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_TAI_ExtIEs(param, mBuf)
SztProtExtnCont_TAI_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_TAI_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_TAI_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_TAI_ExtIEs */



/* 
* FUN : cmPkSztTAI
*  DESC: Function to Pack SztTAI structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztTAI
(
SztTAI *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztTAI(param, mBuf)
SztTAI *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztTAI) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_TAI_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztTAC, &param->tAC, mBuf); 
		CMCHKPK(cmPkSztPLMNidentity, &param->pLMNidentity, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztTAI */



/* 
* FUN : cmPkSztTAILstforMDT
*  DESC: Function to Pack SztTAILstforMDT structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztTAILstforMDT
(
SztTAILstforMDT *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztTAILstforMDT(param, mBuf)
SztTAILstforMDT *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztTAILstforMDT) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztTAI, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztTAILstforMDT */



/* 
* FUN : cmPkSzt_ExtnTAIBasedMDT_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnTAIBasedMDT_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnTAIBasedMDT_ExtIEsCls
(
Szt_ExtnTAIBasedMDT_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnTAIBasedMDT_ExtIEsCls(param, val, mBuf)
Szt_ExtnTAIBasedMDT_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnTAIBasedMDT_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnTAIBasedMDT_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_TAIBasedMDT_ExtIEs
*  DESC: Function to Pack SztProtExtnField_TAIBasedMDT_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_TAIBasedMDT_ExtIEs
(
SztProtExtnField_TAIBasedMDT_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_TAIBasedMDT_ExtIEs(param, mBuf)
SztProtExtnField_TAIBasedMDT_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_TAIBasedMDT_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnTAIBasedMDT_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_TAIBasedMDT_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_TAIBasedMDT_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_TAIBasedMDT_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_TAIBasedMDT_ExtIEs
(
SztProtExtnCont_TAIBasedMDT_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_TAIBasedMDT_ExtIEs(param, mBuf)
SztProtExtnCont_TAIBasedMDT_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_TAIBasedMDT_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_TAIBasedMDT_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_TAIBasedMDT_ExtIEs */



/* 
* FUN : cmPkSztTAIBasedMDT
*  DESC: Function to Pack SztTAIBasedMDT structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztTAIBasedMDT
(
SztTAIBasedMDT *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztTAIBasedMDT(param, mBuf)
SztTAIBasedMDT *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztTAIBasedMDT) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_TAIBasedMDT_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztTAILstforMDT, &param->tAILstforMDT, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztTAIBasedMDT */



/* 
* FUN : cmPkSztAreaScopeOfMDT
*  DESC: Function to Pack SztAreaScopeOfMDT structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztAreaScopeOfMDT
(
SztAreaScopeOfMDT *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztAreaScopeOfMDT(param, mBuf)
SztAreaScopeOfMDT *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztAreaScopeOfMDT) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case AREASCOPEOFMDT_TAIBASED :
				CMCHKPK(cmPkSztTAIBasedMDT, &param->val.tAIBased, mBuf); 
				break;
			case AREASCOPEOFMDT_PLMNWIDE :
				break;
			case AREASCOPEOFMDT_TABASED :
				CMCHKPK(cmPkSztTABasedMDT, &param->val.tABased, mBuf); 
				break;
			case AREASCOPEOFMDT_CELLBASED :
				CMCHKPK(cmPkSztCellBasedMDT, &param->val.cellBased, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztAreaScopeOfMDT */

#define cmPkSztPriorityLvl cmPkTknU32 
#define cmPkSztPre_emptionCapblty cmPkTknU32
#define cmPkSztPre_emptionVulnerability cmPkTknU32


/* 
* FUN : cmPkSzt_ExtnAllocnAndRetentionPriority_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnAllocnAndRetentionPriority_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnAllocnAndRetentionPriority_ExtIEsCls
(
Szt_ExtnAllocnAndRetentionPriority_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnAllocnAndRetentionPriority_ExtIEsCls(param, val, mBuf)
Szt_ExtnAllocnAndRetentionPriority_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnAllocnAndRetentionPriority_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnAllocnAndRetentionPriority_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_AllocnAndRetentionPriority_ExtIEs
*  DESC: Function to Pack SztProtExtnField_AllocnAndRetentionPriority_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_AllocnAndRetentionPriority_ExtIEs
(
SztProtExtnField_AllocnAndRetentionPriority_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_AllocnAndRetentionPriority_ExtIEs(param, mBuf)
SztProtExtnField_AllocnAndRetentionPriority_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_AllocnAndRetentionPriority_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnAllocnAndRetentionPriority_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_AllocnAndRetentionPriority_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_AllocnAndRetentionPriority_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_AllocnAndRetentionPriority_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_AllocnAndRetentionPriority_ExtIEs
(
SztProtExtnCont_AllocnAndRetentionPriority_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_AllocnAndRetentionPriority_ExtIEs(param, mBuf)
SztProtExtnCont_AllocnAndRetentionPriority_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_AllocnAndRetentionPriority_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_AllocnAndRetentionPriority_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_AllocnAndRetentionPriority_ExtIEs */



/* 
* FUN : cmPkSztAllocnAndRetentionPriority
*  DESC: Function to Pack SztAllocnAndRetentionPriority structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztAllocnAndRetentionPriority
(
SztAllocnAndRetentionPriority *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztAllocnAndRetentionPriority(param, mBuf)
SztAllocnAndRetentionPriority *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztAllocnAndRetentionPriority) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_AllocnAndRetentionPriority_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztPre_emptionVulnerability, &param->pre_emptionVulnerability, mBuf); 
		CMCHKPK(cmPkSztPre_emptionCapblty, &param->pre_emptionCapblty, mBuf); 
		CMCHKPK(cmPkSztPriorityLvl, &param->priorityLvl, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztAllocnAndRetentionPriority */

#define cmPkSztE_RAB_ID cmPkTknU32 
#define cmPkSztPDCP_SN cmPkTknU32 
#define cmPkSztHFN cmPkTknU32 


/* 
* FUN : cmPkSzt_ExtnCOUNTvalue_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnCOUNTvalue_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnCOUNTvalue_ExtIEsCls
(
Szt_ExtnCOUNTvalue_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnCOUNTvalue_ExtIEsCls(param, val, mBuf)
Szt_ExtnCOUNTvalue_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnCOUNTvalue_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnCOUNTvalue_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_COUNTvalue_ExtIEs
*  DESC: Function to Pack SztProtExtnField_COUNTvalue_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_COUNTvalue_ExtIEs
(
SztProtExtnField_COUNTvalue_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_COUNTvalue_ExtIEs(param, mBuf)
SztProtExtnField_COUNTvalue_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_COUNTvalue_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnCOUNTvalue_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_COUNTvalue_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_COUNTvalue_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_COUNTvalue_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_COUNTvalue_ExtIEs
(
SztProtExtnCont_COUNTvalue_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_COUNTvalue_ExtIEs(param, mBuf)
SztProtExtnCont_COUNTvalue_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_COUNTvalue_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_COUNTvalue_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_COUNTvalue_ExtIEs */



/* 
* FUN : cmPkSztCOUNTvalue
*  DESC: Function to Pack SztCOUNTvalue structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztCOUNTvalue
(
SztCOUNTvalue *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztCOUNTvalue(param, mBuf)
SztCOUNTvalue *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztCOUNTvalue) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_COUNTvalue_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztHFN, &param->hFN, mBuf); 
		CMCHKPK(cmPkSztPDCP_SN, &param->pDCP_SN, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztCOUNTvalue */

#define cmPkSztReceiveStatusofULPDCPSDUs cmPkTknStrBSXL 
#define cmPkSztPDCP_SNExtended cmPkTknU32 
#define cmPkSztHFNMdfd cmPkTknU32 


/* 
* FUN : cmPkSzt_ExtnCOUNTValueExtended_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnCOUNTValueExtended_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnCOUNTValueExtended_ExtIEsCls
(
Szt_ExtnCOUNTValueExtended_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnCOUNTValueExtended_ExtIEsCls(param, val, mBuf)
Szt_ExtnCOUNTValueExtended_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnCOUNTValueExtended_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnCOUNTValueExtended_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_COUNTValueExtended_ExtIEs
*  DESC: Function to Pack SztProtExtnField_COUNTValueExtended_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_COUNTValueExtended_ExtIEs
(
SztProtExtnField_COUNTValueExtended_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_COUNTValueExtended_ExtIEs(param, mBuf)
SztProtExtnField_COUNTValueExtended_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_COUNTValueExtended_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnCOUNTValueExtended_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_COUNTValueExtended_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_COUNTValueExtended_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_COUNTValueExtended_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_COUNTValueExtended_ExtIEs
(
SztProtExtnCont_COUNTValueExtended_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_COUNTValueExtended_ExtIEs(param, mBuf)
SztProtExtnCont_COUNTValueExtended_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_COUNTValueExtended_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_COUNTValueExtended_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_COUNTValueExtended_ExtIEs */



/* 
* FUN : cmPkSztCOUNTValueExtended
*  DESC: Function to Pack SztCOUNTValueExtended structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztCOUNTValueExtended
(
SztCOUNTValueExtended *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztCOUNTValueExtended(param, mBuf)
SztCOUNTValueExtended *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztCOUNTValueExtended) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_COUNTValueExtended_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztHFNMdfd, &param->hFNMdfd, mBuf); 
		CMCHKPK(cmPkSztPDCP_SNExtended, &param->pDCP_SNExtended, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztCOUNTValueExtended */

#define cmPkSztReceiveStatusOfULPDCPSDUsExtended cmPkTknStrBSXL 


/* 
* FUN : cmPkSzt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls
*  DESC: Function to Pack Szt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls
(
Szt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls(param, val, mBuf)
Szt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls) 
	
	switch (val)
	{
		case Sztid_ULCOUNTValueExtended:
			CMCHKPK(cmPkSztCOUNTValueExtended, &param->u.sztid_ULCOUNTValueExtended, mBuf);
			break;
		case Sztid_DLCOUNTValueExtended:
			CMCHKPK(cmPkSztCOUNTValueExtended, &param->u.sztid_DLCOUNTValueExtended, mBuf);
			break;
		case Sztid_ReceiveStatusOfULPDCPSDUsExtended:
			CMCHKPK(cmPkSztReceiveStatusOfULPDCPSDUsExtended, &param->u.sztReceiveStatusOfULPDCPSDUsExtended, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs
*  DESC: Function to Pack SztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs
(
SztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs(param, mBuf)
SztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs
*  DESC: Function to Pack SztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs
(
SztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs(param, mBuf)
SztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs */



/* 
* FUN : cmPkSztBrs_SubjToStatusTfr_Item
*  DESC: Function to Pack SztBrs_SubjToStatusTfr_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztBrs_SubjToStatusTfr_Item
(
SztBrs_SubjToStatusTfr_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztBrs_SubjToStatusTfr_Item(param, mBuf)
SztBrs_SubjToStatusTfr_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztBrs_SubjToStatusTfr_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztReceiveStatusofULPDCPSDUs, &param->receiveStatusofULPDCPSDUs, mBuf); 
		CMCHKPK(cmPkSztCOUNTvalue, &param->dL_COUNTvalue, mBuf); 
		CMCHKPK(cmPkSztCOUNTvalue, &param->uL_COUNTvalue, mBuf); 
		CMCHKPK(cmPkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztBrs_SubjToStatusTfr_Item */



/* 
* FUN : cmPkSzt_ValueBrs_SubjToStatusTfr_ItemIEsCls
*  DESC: Function to Pack Szt_ValueBrs_SubjToStatusTfr_ItemIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueBrs_SubjToStatusTfr_ItemIEsCls
(
Szt_ValueBrs_SubjToStatusTfr_ItemIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueBrs_SubjToStatusTfr_ItemIEsCls(param, val, mBuf)
Szt_ValueBrs_SubjToStatusTfr_ItemIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueBrs_SubjToStatusTfr_ItemIEsCls) 
	
	switch (val)
	{
		case Sztid_Brs_SubjToStatusTfr_Item:
			CMCHKPK(cmPkSztBrs_SubjToStatusTfr_Item, &param->u.sztBrs_SubjToStatusTfr_Item, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueBrs_SubjToStatusTfr_ItemIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_Brs_SubjToStatusTfr_ItemIEs
*  DESC: Function to Pack SztProtIE_Field_Brs_SubjToStatusTfr_ItemIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_Brs_SubjToStatusTfr_ItemIEs
(
SztProtIE_Field_Brs_SubjToStatusTfr_ItemIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_Brs_SubjToStatusTfr_ItemIEs(param, mBuf)
SztProtIE_Field_Brs_SubjToStatusTfr_ItemIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_Brs_SubjToStatusTfr_ItemIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueBrs_SubjToStatusTfr_ItemIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_Brs_SubjToStatusTfr_ItemIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmPkSztProtIE_SingleCont_Brs_SubjToStatusTfr_ItemIEs cmPkSztProtIE_Field_Brs_SubjToStatusTfr_ItemIEs


/* 
* FUN : cmPkSztBrs_SubjToStatusTfrLst
*  DESC: Function to Pack SztBrs_SubjToStatusTfrLst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztBrs_SubjToStatusTfrLst
(
SztBrs_SubjToStatusTfrLst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztBrs_SubjToStatusTfrLst(param, mBuf)
SztBrs_SubjToStatusTfrLst *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztBrs_SubjToStatusTfrLst) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_SingleCont_Brs_SubjToStatusTfr_ItemIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztBrs_SubjToStatusTfrLst */

#define cmPkSztBitRate cmPkTknStrOSXL 


/* 
* FUN : cmPkSztBPLMNs
*  DESC: Function to Pack SztBPLMNs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztBPLMNs
(
SztBPLMNs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztBPLMNs(param, mBuf)
SztBPLMNs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztBPLMNs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztPLMNidentity, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztBPLMNs */

#define cmPkSztNumberOfBroadcasts cmPkTknU32 


/* 
* FUN : cmPkSzt_ExtnCellID_Cancelled_Item_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnCellID_Cancelled_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnCellID_Cancelled_Item_ExtIEsCls
(
Szt_ExtnCellID_Cancelled_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnCellID_Cancelled_Item_ExtIEsCls(param, val, mBuf)
Szt_ExtnCellID_Cancelled_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnCellID_Cancelled_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnCellID_Cancelled_Item_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_CellID_Cancelled_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnField_CellID_Cancelled_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_CellID_Cancelled_Item_ExtIEs
(
SztProtExtnField_CellID_Cancelled_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_CellID_Cancelled_Item_ExtIEs(param, mBuf)
SztProtExtnField_CellID_Cancelled_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_CellID_Cancelled_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnCellID_Cancelled_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_CellID_Cancelled_Item_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_CellID_Cancelled_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_CellID_Cancelled_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_CellID_Cancelled_Item_ExtIEs
(
SztProtExtnCont_CellID_Cancelled_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_CellID_Cancelled_Item_ExtIEs(param, mBuf)
SztProtExtnCont_CellID_Cancelled_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_CellID_Cancelled_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_CellID_Cancelled_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_CellID_Cancelled_Item_ExtIEs */



/* 
* FUN : cmPkSztCellID_Cancelled_Item
*  DESC: Function to Pack SztCellID_Cancelled_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztCellID_Cancelled_Item
(
SztCellID_Cancelled_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztCellID_Cancelled_Item(param, mBuf)
SztCellID_Cancelled_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztCellID_Cancelled_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_CellID_Cancelled_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztNumberOfBroadcasts, &param->numberOfBroadcasts, mBuf); 
		CMCHKPK(cmPkSztEUTRAN_CGI, &param->eCGI, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztCellID_Cancelled_Item */



/* 
* FUN : cmPkSztCellID_Cancelled
*  DESC: Function to Pack SztCellID_Cancelled structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztCellID_Cancelled
(
SztCellID_Cancelled *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztCellID_Cancelled(param, mBuf)
SztCellID_Cancelled *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztCellID_Cancelled) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztCellID_Cancelled_Item, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztCellID_Cancelled */



/* 
* FUN : cmPkSzt_ExtnCancelledCellinTAI_Item_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnCancelledCellinTAI_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnCancelledCellinTAI_Item_ExtIEsCls
(
Szt_ExtnCancelledCellinTAI_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnCancelledCellinTAI_Item_ExtIEsCls(param, val, mBuf)
Szt_ExtnCancelledCellinTAI_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnCancelledCellinTAI_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnCancelledCellinTAI_Item_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_CancelledCellinTAI_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnField_CancelledCellinTAI_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_CancelledCellinTAI_Item_ExtIEs
(
SztProtExtnField_CancelledCellinTAI_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_CancelledCellinTAI_Item_ExtIEs(param, mBuf)
SztProtExtnField_CancelledCellinTAI_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_CancelledCellinTAI_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnCancelledCellinTAI_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_CancelledCellinTAI_Item_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_CancelledCellinTAI_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_CancelledCellinTAI_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_CancelledCellinTAI_Item_ExtIEs
(
SztProtExtnCont_CancelledCellinTAI_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_CancelledCellinTAI_Item_ExtIEs(param, mBuf)
SztProtExtnCont_CancelledCellinTAI_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_CancelledCellinTAI_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_CancelledCellinTAI_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_CancelledCellinTAI_Item_ExtIEs */



/* 
* FUN : cmPkSztCancelledCellinTAI_Item
*  DESC: Function to Pack SztCancelledCellinTAI_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztCancelledCellinTAI_Item
(
SztCancelledCellinTAI_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztCancelledCellinTAI_Item(param, mBuf)
SztCancelledCellinTAI_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztCancelledCellinTAI_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_CancelledCellinTAI_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztNumberOfBroadcasts, &param->numberOfBroadcasts, mBuf); 
		CMCHKPK(cmPkSztEUTRAN_CGI, &param->eCGI, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztCancelledCellinTAI_Item */



/* 
* FUN : cmPkSztCancelledCellinTAI
*  DESC: Function to Pack SztCancelledCellinTAI structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztCancelledCellinTAI
(
SztCancelledCellinTAI *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztCancelledCellinTAI(param, mBuf)
SztCancelledCellinTAI *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztCancelledCellinTAI) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztCancelledCellinTAI_Item, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztCancelledCellinTAI */



/* 
* FUN : cmPkSzt_ExtnTAI_Cancelled_Item_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnTAI_Cancelled_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnTAI_Cancelled_Item_ExtIEsCls
(
Szt_ExtnTAI_Cancelled_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnTAI_Cancelled_Item_ExtIEsCls(param, val, mBuf)
Szt_ExtnTAI_Cancelled_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnTAI_Cancelled_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnTAI_Cancelled_Item_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_TAI_Cancelled_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnField_TAI_Cancelled_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_TAI_Cancelled_Item_ExtIEs
(
SztProtExtnField_TAI_Cancelled_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_TAI_Cancelled_Item_ExtIEs(param, mBuf)
SztProtExtnField_TAI_Cancelled_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_TAI_Cancelled_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnTAI_Cancelled_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_TAI_Cancelled_Item_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_TAI_Cancelled_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_TAI_Cancelled_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_TAI_Cancelled_Item_ExtIEs
(
SztProtExtnCont_TAI_Cancelled_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_TAI_Cancelled_Item_ExtIEs(param, mBuf)
SztProtExtnCont_TAI_Cancelled_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_TAI_Cancelled_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_TAI_Cancelled_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_TAI_Cancelled_Item_ExtIEs */



/* 
* FUN : cmPkSztTAI_Cancelled_Item
*  DESC: Function to Pack SztTAI_Cancelled_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztTAI_Cancelled_Item
(
SztTAI_Cancelled_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztTAI_Cancelled_Item(param, mBuf)
SztTAI_Cancelled_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztTAI_Cancelled_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_TAI_Cancelled_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztCancelledCellinTAI, &param->cancelledCellinTAI, mBuf); 
		CMCHKPK(cmPkSztTAI, &param->tAI, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztTAI_Cancelled_Item */



/* 
* FUN : cmPkSztTAI_Cancelled
*  DESC: Function to Pack SztTAI_Cancelled structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztTAI_Cancelled
(
SztTAI_Cancelled *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztTAI_Cancelled(param, mBuf)
SztTAI_Cancelled *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztTAI_Cancelled) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztTAI_Cancelled_Item, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztTAI_Cancelled */

#define cmPkSztEmergencyAreaID cmPkTknStrOSXL 


/* 
* FUN : cmPkSzt_ExtnCancelledCellinEAI_Item_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnCancelledCellinEAI_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnCancelledCellinEAI_Item_ExtIEsCls
(
Szt_ExtnCancelledCellinEAI_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnCancelledCellinEAI_Item_ExtIEsCls(param, val, mBuf)
Szt_ExtnCancelledCellinEAI_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnCancelledCellinEAI_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnCancelledCellinEAI_Item_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_CancelledCellinEAI_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnField_CancelledCellinEAI_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_CancelledCellinEAI_Item_ExtIEs
(
SztProtExtnField_CancelledCellinEAI_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_CancelledCellinEAI_Item_ExtIEs(param, mBuf)
SztProtExtnField_CancelledCellinEAI_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_CancelledCellinEAI_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnCancelledCellinEAI_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_CancelledCellinEAI_Item_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_CancelledCellinEAI_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_CancelledCellinEAI_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_CancelledCellinEAI_Item_ExtIEs
(
SztProtExtnCont_CancelledCellinEAI_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_CancelledCellinEAI_Item_ExtIEs(param, mBuf)
SztProtExtnCont_CancelledCellinEAI_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_CancelledCellinEAI_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_CancelledCellinEAI_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_CancelledCellinEAI_Item_ExtIEs */



/* 
* FUN : cmPkSztCancelledCellinEAI_Item
*  DESC: Function to Pack SztCancelledCellinEAI_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztCancelledCellinEAI_Item
(
SztCancelledCellinEAI_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztCancelledCellinEAI_Item(param, mBuf)
SztCancelledCellinEAI_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztCancelledCellinEAI_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_CancelledCellinEAI_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztNumberOfBroadcasts, &param->numberOfBroadcasts, mBuf); 
		CMCHKPK(cmPkSztEUTRAN_CGI, &param->eCGI, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztCancelledCellinEAI_Item */



/* 
* FUN : cmPkSztCancelledCellinEAI
*  DESC: Function to Pack SztCancelledCellinEAI structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztCancelledCellinEAI
(
SztCancelledCellinEAI *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztCancelledCellinEAI(param, mBuf)
SztCancelledCellinEAI *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztCancelledCellinEAI) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztCancelledCellinEAI_Item, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztCancelledCellinEAI */



/* 
* FUN : cmPkSzt_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls
(
Szt_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls(param, val, mBuf)
Szt_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs
(
SztProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs(param, mBuf)
SztProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs
(
SztProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs(param, mBuf)
SztProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs */



/* 
* FUN : cmPkSztEmergencyAreaID_Cancelled_Item
*  DESC: Function to Pack SztEmergencyAreaID_Cancelled_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztEmergencyAreaID_Cancelled_Item
(
SztEmergencyAreaID_Cancelled_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztEmergencyAreaID_Cancelled_Item(param, mBuf)
SztEmergencyAreaID_Cancelled_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztEmergencyAreaID_Cancelled_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztCancelledCellinEAI, &param->cancelledCellinEAI, mBuf); 
		CMCHKPK(cmPkSztEmergencyAreaID, &param->emergencyAreaID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztEmergencyAreaID_Cancelled_Item */



/* 
* FUN : cmPkSztEmergencyAreaID_Cancelled
*  DESC: Function to Pack SztEmergencyAreaID_Cancelled structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztEmergencyAreaID_Cancelled
(
SztEmergencyAreaID_Cancelled *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztEmergencyAreaID_Cancelled(param, mBuf)
SztEmergencyAreaID_Cancelled *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztEmergencyAreaID_Cancelled) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztEmergencyAreaID_Cancelled_Item, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztEmergencyAreaID_Cancelled */



/* 
* FUN : cmPkSztBroadcastCancelledAreaLst
*  DESC: Function to Pack SztBroadcastCancelledAreaLst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztBroadcastCancelledAreaLst
(
SztBroadcastCancelledAreaLst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztBroadcastCancelledAreaLst(param, mBuf)
SztBroadcastCancelledAreaLst *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztBroadcastCancelledAreaLst) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case BROADCASTCANCELLEDAREALST_EMERGENCYAREAID_CANCELLED :
				CMCHKPK(cmPkSztEmergencyAreaID_Cancelled, &param->val.emergencyAreaID_Cancelled, mBuf); 
				break;
			case BROADCASTCANCELLEDAREALST_TAI_CANCELLED :
				CMCHKPK(cmPkSztTAI_Cancelled, &param->val.tAI_Cancelled, mBuf); 
				break;
			case BROADCASTCANCELLEDAREALST_CELLID_CANCELLED :
				CMCHKPK(cmPkSztCellID_Cancelled, &param->val.cellID_Cancelled, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztBroadcastCancelledAreaLst */



/* 
* FUN : cmPkSzt_ExtnCellID_Broadcast_Item_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnCellID_Broadcast_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnCellID_Broadcast_Item_ExtIEsCls
(
Szt_ExtnCellID_Broadcast_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnCellID_Broadcast_Item_ExtIEsCls(param, val, mBuf)
Szt_ExtnCellID_Broadcast_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnCellID_Broadcast_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnCellID_Broadcast_Item_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_CellID_Broadcast_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnField_CellID_Broadcast_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_CellID_Broadcast_Item_ExtIEs
(
SztProtExtnField_CellID_Broadcast_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_CellID_Broadcast_Item_ExtIEs(param, mBuf)
SztProtExtnField_CellID_Broadcast_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_CellID_Broadcast_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnCellID_Broadcast_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_CellID_Broadcast_Item_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_CellID_Broadcast_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_CellID_Broadcast_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_CellID_Broadcast_Item_ExtIEs
(
SztProtExtnCont_CellID_Broadcast_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_CellID_Broadcast_Item_ExtIEs(param, mBuf)
SztProtExtnCont_CellID_Broadcast_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_CellID_Broadcast_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_CellID_Broadcast_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_CellID_Broadcast_Item_ExtIEs */



/* 
* FUN : cmPkSztCellID_Broadcast_Item
*  DESC: Function to Pack SztCellID_Broadcast_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztCellID_Broadcast_Item
(
SztCellID_Broadcast_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztCellID_Broadcast_Item(param, mBuf)
SztCellID_Broadcast_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztCellID_Broadcast_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_CellID_Broadcast_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztEUTRAN_CGI, &param->eCGI, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztCellID_Broadcast_Item */



/* 
* FUN : cmPkSztCellID_Broadcast
*  DESC: Function to Pack SztCellID_Broadcast structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztCellID_Broadcast
(
SztCellID_Broadcast *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztCellID_Broadcast(param, mBuf)
SztCellID_Broadcast *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztCellID_Broadcast) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztCellID_Broadcast_Item, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztCellID_Broadcast */



/* 
* FUN : cmPkSzt_ExtnCompletedCellinTAI_Item_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnCompletedCellinTAI_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnCompletedCellinTAI_Item_ExtIEsCls
(
Szt_ExtnCompletedCellinTAI_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnCompletedCellinTAI_Item_ExtIEsCls(param, val, mBuf)
Szt_ExtnCompletedCellinTAI_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnCompletedCellinTAI_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnCompletedCellinTAI_Item_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_CompletedCellinTAI_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnField_CompletedCellinTAI_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_CompletedCellinTAI_Item_ExtIEs
(
SztProtExtnField_CompletedCellinTAI_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_CompletedCellinTAI_Item_ExtIEs(param, mBuf)
SztProtExtnField_CompletedCellinTAI_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_CompletedCellinTAI_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnCompletedCellinTAI_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_CompletedCellinTAI_Item_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_CompletedCellinTAI_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_CompletedCellinTAI_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_CompletedCellinTAI_Item_ExtIEs
(
SztProtExtnCont_CompletedCellinTAI_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_CompletedCellinTAI_Item_ExtIEs(param, mBuf)
SztProtExtnCont_CompletedCellinTAI_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_CompletedCellinTAI_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_CompletedCellinTAI_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_CompletedCellinTAI_Item_ExtIEs */



/* 
* FUN : cmPkSztCompletedCellinTAI_Item
*  DESC: Function to Pack SztCompletedCellinTAI_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztCompletedCellinTAI_Item
(
SztCompletedCellinTAI_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztCompletedCellinTAI_Item(param, mBuf)
SztCompletedCellinTAI_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztCompletedCellinTAI_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_CompletedCellinTAI_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztEUTRAN_CGI, &param->eCGI, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztCompletedCellinTAI_Item */



/* 
* FUN : cmPkSztCompletedCellinTAI
*  DESC: Function to Pack SztCompletedCellinTAI structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztCompletedCellinTAI
(
SztCompletedCellinTAI *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztCompletedCellinTAI(param, mBuf)
SztCompletedCellinTAI *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztCompletedCellinTAI) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztCompletedCellinTAI_Item, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztCompletedCellinTAI */



/* 
* FUN : cmPkSzt_ExtnTAI_Broadcast_Item_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnTAI_Broadcast_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnTAI_Broadcast_Item_ExtIEsCls
(
Szt_ExtnTAI_Broadcast_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnTAI_Broadcast_Item_ExtIEsCls(param, val, mBuf)
Szt_ExtnTAI_Broadcast_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnTAI_Broadcast_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnTAI_Broadcast_Item_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_TAI_Broadcast_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnField_TAI_Broadcast_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_TAI_Broadcast_Item_ExtIEs
(
SztProtExtnField_TAI_Broadcast_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_TAI_Broadcast_Item_ExtIEs(param, mBuf)
SztProtExtnField_TAI_Broadcast_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_TAI_Broadcast_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnTAI_Broadcast_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_TAI_Broadcast_Item_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_TAI_Broadcast_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_TAI_Broadcast_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_TAI_Broadcast_Item_ExtIEs
(
SztProtExtnCont_TAI_Broadcast_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_TAI_Broadcast_Item_ExtIEs(param, mBuf)
SztProtExtnCont_TAI_Broadcast_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_TAI_Broadcast_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_TAI_Broadcast_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_TAI_Broadcast_Item_ExtIEs */



/* 
* FUN : cmPkSztTAI_Broadcast_Item
*  DESC: Function to Pack SztTAI_Broadcast_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztTAI_Broadcast_Item
(
SztTAI_Broadcast_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztTAI_Broadcast_Item(param, mBuf)
SztTAI_Broadcast_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztTAI_Broadcast_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_TAI_Broadcast_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztCompletedCellinTAI, &param->completedCellinTAI, mBuf); 
		CMCHKPK(cmPkSztTAI, &param->tAI, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztTAI_Broadcast_Item */



/* 
* FUN : cmPkSztTAI_Broadcast
*  DESC: Function to Pack SztTAI_Broadcast structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztTAI_Broadcast
(
SztTAI_Broadcast *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztTAI_Broadcast(param, mBuf)
SztTAI_Broadcast *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztTAI_Broadcast) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztTAI_Broadcast_Item, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztTAI_Broadcast */



/* 
* FUN : cmPkSzt_ExtnCompletedCellinEAI_Item_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnCompletedCellinEAI_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnCompletedCellinEAI_Item_ExtIEsCls
(
Szt_ExtnCompletedCellinEAI_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnCompletedCellinEAI_Item_ExtIEsCls(param, val, mBuf)
Szt_ExtnCompletedCellinEAI_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnCompletedCellinEAI_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnCompletedCellinEAI_Item_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_CompletedCellinEAI_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnField_CompletedCellinEAI_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_CompletedCellinEAI_Item_ExtIEs
(
SztProtExtnField_CompletedCellinEAI_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_CompletedCellinEAI_Item_ExtIEs(param, mBuf)
SztProtExtnField_CompletedCellinEAI_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_CompletedCellinEAI_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnCompletedCellinEAI_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_CompletedCellinEAI_Item_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_CompletedCellinEAI_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_CompletedCellinEAI_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_CompletedCellinEAI_Item_ExtIEs
(
SztProtExtnCont_CompletedCellinEAI_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_CompletedCellinEAI_Item_ExtIEs(param, mBuf)
SztProtExtnCont_CompletedCellinEAI_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_CompletedCellinEAI_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_CompletedCellinEAI_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_CompletedCellinEAI_Item_ExtIEs */



/* 
* FUN : cmPkSztCompletedCellinEAI_Item
*  DESC: Function to Pack SztCompletedCellinEAI_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztCompletedCellinEAI_Item
(
SztCompletedCellinEAI_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztCompletedCellinEAI_Item(param, mBuf)
SztCompletedCellinEAI_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztCompletedCellinEAI_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_CompletedCellinEAI_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztEUTRAN_CGI, &param->eCGI, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztCompletedCellinEAI_Item */



/* 
* FUN : cmPkSztCompletedCellinEAI
*  DESC: Function to Pack SztCompletedCellinEAI structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztCompletedCellinEAI
(
SztCompletedCellinEAI *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztCompletedCellinEAI(param, mBuf)
SztCompletedCellinEAI *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztCompletedCellinEAI) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztCompletedCellinEAI_Item, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztCompletedCellinEAI */



/* 
* FUN : cmPkSzt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls
(
Szt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls(param, val, mBuf)
Szt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs
(
SztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs(param, mBuf)
SztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs
(
SztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs(param, mBuf)
SztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs */



/* 
* FUN : cmPkSztEmergencyAreaID_Broadcast_Item
*  DESC: Function to Pack SztEmergencyAreaID_Broadcast_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztEmergencyAreaID_Broadcast_Item
(
SztEmergencyAreaID_Broadcast_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztEmergencyAreaID_Broadcast_Item(param, mBuf)
SztEmergencyAreaID_Broadcast_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztEmergencyAreaID_Broadcast_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztCompletedCellinEAI, &param->completedCellinEAI, mBuf); 
		CMCHKPK(cmPkSztEmergencyAreaID, &param->emergencyAreaID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztEmergencyAreaID_Broadcast_Item */



/* 
* FUN : cmPkSztEmergencyAreaID_Broadcast
*  DESC: Function to Pack SztEmergencyAreaID_Broadcast structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztEmergencyAreaID_Broadcast
(
SztEmergencyAreaID_Broadcast *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztEmergencyAreaID_Broadcast(param, mBuf)
SztEmergencyAreaID_Broadcast *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztEmergencyAreaID_Broadcast) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztEmergencyAreaID_Broadcast_Item, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztEmergencyAreaID_Broadcast */



/* 
* FUN : cmPkSztBroadcastCompletedAreaLst
*  DESC: Function to Pack SztBroadcastCompletedAreaLst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztBroadcastCompletedAreaLst
(
SztBroadcastCompletedAreaLst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztBroadcastCompletedAreaLst(param, mBuf)
SztBroadcastCompletedAreaLst *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztBroadcastCompletedAreaLst) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case BROADCASTCOMPLETEDAREALST_EMERGENCYAREAID_BROADCAST :
				CMCHKPK(cmPkSztEmergencyAreaID_Broadcast, &param->val.emergencyAreaID_Broadcast, mBuf); 
				break;
			case BROADCASTCOMPLETEDAREALST_TAI_BROADCAST :
				CMCHKPK(cmPkSztTAI_Broadcast, &param->val.tAI_Broadcast, mBuf); 
				break;
			case BROADCASTCOMPLETEDAREALST_CELLID_BROADCAST :
				CMCHKPK(cmPkSztCellID_Broadcast, &param->val.cellID_Broadcast, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztBroadcastCompletedAreaLst */

#define cmPkSztCauseRadioNw cmPkTknU32
#define cmPkSztCauseTport cmPkTknU32
#define cmPkSztCauseNas cmPkTknU32
#define cmPkSztCauseProt cmPkTknU32
#define cmPkSztCauseMisc cmPkTknU32


/* 
* FUN : cmPkSztCause
*  DESC: Function to Pack SztCause structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztCause
(
SztCause *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztCause(param, mBuf)
SztCause *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztCause) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case CAUSE_MISC :
				CMCHKPK(cmPkSztCauseMisc, &param->val.misc, mBuf); 
				break;
			case CAUSE_PROTOCOL :
				CMCHKPK(cmPkSztCauseProt, &param->val.protocol, mBuf); 
				break;
			case CAUSE_NAS :
				CMCHKPK(cmPkSztCauseNas, &param->val.nas, mBuf); 
				break;
			case CAUSE_TRANSPORT :
				CMCHKPK(cmPkSztCauseTport, &param->val.transport, mBuf); 
				break;
			case CAUSE_RADIONW :
				CMCHKPK(cmPkSztCauseRadioNw, &param->val.radioNw, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztCause */

#define cmPkSztCellAccessMode cmPkTknU32
#define cmPkSztCdma2000PDU cmPkTknStrOSXL 
#define cmPkSztCdma2000RATTyp cmPkTknU32
#define cmPkSztCdma2000SectorID cmPkTknStrOSXL 
#define cmPkSztCdma2000HOStatus cmPkTknU32
#define cmPkSztCdma2000HOReqdInd cmPkTknU32
#define cmPkSztCdma2000OneXMEID cmPkTknStrOSXL 
#define cmPkSztCdma2000OneXMSI cmPkTknStrOSXL 
#define cmPkSztCdma2000OneXPilot cmPkTknStrOSXL 


/* 
* FUN : cmPkSzt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls
(
Szt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls(param, val, mBuf)
Szt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs
*  DESC: Function to Pack SztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs
(
SztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs(param, mBuf)
SztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs
(
SztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs(param, mBuf)
SztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs */



/* 
* FUN : cmPkSztCdma2000OneXSRVCCInfo
*  DESC: Function to Pack SztCdma2000OneXSRVCCInfo structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztCdma2000OneXSRVCCInfo
(
SztCdma2000OneXSRVCCInfo *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztCdma2000OneXSRVCCInfo(param, mBuf)
SztCdma2000OneXSRVCCInfo *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztCdma2000OneXSRVCCInfo) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztCdma2000OneXPilot, &param->cdma2000OneXPilot, mBuf); 
		CMCHKPK(cmPkSztCdma2000OneXMSI, &param->cdma2000OneXMSI, mBuf); 
		CMCHKPK(cmPkSztCdma2000OneXMEID, &param->cdma2000OneXMEID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztCdma2000OneXSRVCCInfo */

#define cmPkSztCdma2000OneXRAND cmPkTknStrOSXL 
#define cmPkSztCell_Size cmPkTknU32


/* 
* FUN : cmPkSzt_ExtnCellTyp_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnCellTyp_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnCellTyp_ExtIEsCls
(
Szt_ExtnCellTyp_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnCellTyp_ExtIEsCls(param, val, mBuf)
Szt_ExtnCellTyp_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnCellTyp_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnCellTyp_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_CellTyp_ExtIEs
*  DESC: Function to Pack SztProtExtnField_CellTyp_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_CellTyp_ExtIEs
(
SztProtExtnField_CellTyp_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_CellTyp_ExtIEs(param, mBuf)
SztProtExtnField_CellTyp_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_CellTyp_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnCellTyp_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_CellTyp_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_CellTyp_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_CellTyp_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_CellTyp_ExtIEs
(
SztProtExtnCont_CellTyp_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_CellTyp_ExtIEs(param, mBuf)
SztProtExtnCont_CellTyp_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_CellTyp_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_CellTyp_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_CellTyp_ExtIEs */



/* 
* FUN : cmPkSztCellTyp
*  DESC: Function to Pack SztCellTyp structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztCellTyp
(
SztCellTyp *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztCellTyp(param, mBuf)
SztCellTyp *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztCellTyp) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_CellTyp_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztCell_Size, &param->cell_Size, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztCellTyp */

#define cmPkSztLAC cmPkTknStr4 
#define cmPkSztCI cmPkTknStr4 
#define cmPkSztRAC cmPkTknStr4 


/* 
* FUN : cmPkSzt_ExtnCGI_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnCGI_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnCGI_ExtIEsCls
(
Szt_ExtnCGI_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnCGI_ExtIEsCls(param, val, mBuf)
Szt_ExtnCGI_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnCGI_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnCGI_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_CGI_ExtIEs
*  DESC: Function to Pack SztProtExtnField_CGI_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_CGI_ExtIEs
(
SztProtExtnField_CGI_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_CGI_ExtIEs(param, mBuf)
SztProtExtnField_CGI_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_CGI_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnCGI_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_CGI_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_CGI_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_CGI_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_CGI_ExtIEs
(
SztProtExtnCont_CGI_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_CGI_ExtIEs(param, mBuf)
SztProtExtnCont_CGI_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_CGI_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_CGI_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_CGI_ExtIEs */



/* 
* FUN : cmPkSztCGI
*  DESC: Function to Pack SztCGI structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztCGI
(
SztCGI *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztCGI(param, mBuf)
SztCGI *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztCGI) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_CGI_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztRAC, &param->rAC, mBuf); 
		CMCHKPK(cmPkSztCI, &param->cI, mBuf); 
		CMCHKPK(cmPkSztLAC, &param->lAC, mBuf); 
		CMCHKPK(cmPkSztPLMNidentity, &param->pLMNidentity, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztCGI */

#define cmPkSztCNDomain cmPkTknU32
#define cmPkSztConcurrentWarningMsgIndicator cmPkTknU32
#define cmPkSztCorrelation_ID cmPkTknStrOSXL 
#define cmPkSztCSFallbackIndicator cmPkTknU32
#define cmPkSztCSG_Id cmPkTknBStr32 


/* 
* FUN : cmPkSzt_ExtnCSG_IdLst_Item_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnCSG_IdLst_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnCSG_IdLst_Item_ExtIEsCls
(
Szt_ExtnCSG_IdLst_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnCSG_IdLst_Item_ExtIEsCls(param, val, mBuf)
Szt_ExtnCSG_IdLst_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnCSG_IdLst_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnCSG_IdLst_Item_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_CSG_IdLst_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnField_CSG_IdLst_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_CSG_IdLst_Item_ExtIEs
(
SztProtExtnField_CSG_IdLst_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_CSG_IdLst_Item_ExtIEs(param, mBuf)
SztProtExtnField_CSG_IdLst_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_CSG_IdLst_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnCSG_IdLst_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_CSG_IdLst_Item_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_CSG_IdLst_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_CSG_IdLst_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_CSG_IdLst_Item_ExtIEs
(
SztProtExtnCont_CSG_IdLst_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_CSG_IdLst_Item_ExtIEs(param, mBuf)
SztProtExtnCont_CSG_IdLst_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_CSG_IdLst_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_CSG_IdLst_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_CSG_IdLst_Item_ExtIEs */



/* 
* FUN : cmPkSztCSG_IdLst_Item
*  DESC: Function to Pack SztCSG_IdLst_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztCSG_IdLst_Item
(
SztCSG_IdLst_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztCSG_IdLst_Item(param, mBuf)
SztCSG_IdLst_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztCSG_IdLst_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_CSG_IdLst_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztCSG_Id, &param->cSG_Id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztCSG_IdLst_Item */



/* 
* FUN : cmPkSztCSG_IdLst
*  DESC: Function to Pack SztCSG_IdLst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztCSG_IdLst
(
SztCSG_IdLst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztCSG_IdLst(param, mBuf)
SztCSG_IdLst *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztCSG_IdLst) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztCSG_IdLst_Item, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztCSG_IdLst */

#define cmPkSztCSGMembershipStatus cmPkTknU32
#define cmPkSztTypOfErr cmPkTknU32


/* 
* FUN : cmPkSzt_ExtnCriticalityDiag_IE_Item_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnCriticalityDiag_IE_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnCriticalityDiag_IE_Item_ExtIEsCls
(
Szt_ExtnCriticalityDiag_IE_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnCriticalityDiag_IE_Item_ExtIEsCls(param, val, mBuf)
Szt_ExtnCriticalityDiag_IE_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnCriticalityDiag_IE_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnCriticalityDiag_IE_Item_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_CriticalityDiag_IE_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnField_CriticalityDiag_IE_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_CriticalityDiag_IE_Item_ExtIEs
(
SztProtExtnField_CriticalityDiag_IE_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_CriticalityDiag_IE_Item_ExtIEs(param, mBuf)
SztProtExtnField_CriticalityDiag_IE_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_CriticalityDiag_IE_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnCriticalityDiag_IE_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_CriticalityDiag_IE_Item_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs
(
SztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs(param, mBuf)
SztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_CriticalityDiag_IE_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs */



/* 
* FUN : cmPkSztCriticalityDiag_IE_Item
*  DESC: Function to Pack SztCriticalityDiag_IE_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztCriticalityDiag_IE_Item
(
SztCriticalityDiag_IE_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztCriticalityDiag_IE_Item(param, mBuf)
SztCriticalityDiag_IE_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztCriticalityDiag_IE_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztTypOfErr, &param->typeOfErr, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->iE_ID, mBuf); 
		CMCHKPK(cmPkSztCriticality, &param->iECriticality, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztCriticalityDiag_IE_Item */



/* 
* FUN : cmPkSztCriticalityDiag_IE_Lst
*  DESC: Function to Pack SztCriticalityDiag_IE_Lst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztCriticalityDiag_IE_Lst
(
SztCriticalityDiag_IE_Lst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztCriticalityDiag_IE_Lst(param, mBuf)
SztCriticalityDiag_IE_Lst *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztCriticalityDiag_IE_Lst) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztCriticalityDiag_IE_Item, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztCriticalityDiag_IE_Lst */



/* 
* FUN : cmPkSzt_ExtnCriticalityDiag_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnCriticalityDiag_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnCriticalityDiag_ExtIEsCls
(
Szt_ExtnCriticalityDiag_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnCriticalityDiag_ExtIEsCls(param, val, mBuf)
Szt_ExtnCriticalityDiag_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnCriticalityDiag_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnCriticalityDiag_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_CriticalityDiag_ExtIEs
*  DESC: Function to Pack SztProtExtnField_CriticalityDiag_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_CriticalityDiag_ExtIEs
(
SztProtExtnField_CriticalityDiag_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_CriticalityDiag_ExtIEs(param, mBuf)
SztProtExtnField_CriticalityDiag_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_CriticalityDiag_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnCriticalityDiag_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_CriticalityDiag_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_CriticalityDiag_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_CriticalityDiag_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_CriticalityDiag_ExtIEs
(
SztProtExtnCont_CriticalityDiag_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_CriticalityDiag_ExtIEs(param, mBuf)
SztProtExtnCont_CriticalityDiag_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_CriticalityDiag_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_CriticalityDiag_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_CriticalityDiag_ExtIEs */



/* 
* FUN : cmPkSztCriticalityDiag
*  DESC: Function to Pack SztCriticalityDiag structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztCriticalityDiag
(
SztCriticalityDiag *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztCriticalityDiag(param, mBuf)
SztCriticalityDiag *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztCriticalityDiag) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_CriticalityDiag_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztCriticalityDiag_IE_Lst, &param->iEsCriticalityDiag, mBuf); 
		CMCHKPK(cmPkSztCriticality, &param->procedureCriticality, mBuf); 
		CMCHKPK(cmPkSztTrgMsg, &param->triggeringMsg, mBuf); 
		CMCHKPK(cmPkSztProcedureCode, &param->procedureCode, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztCriticalityDiag */

#define cmPkSztDataCodingScheme cmPkTknBStr32 
#define cmPkSztDL_Fwding cmPkTknU32
#define cmPkSztDirect_Fwding_Path_Avlblty cmPkTknU32
#define cmPkSztData_Fwding_Not_Possible cmPkTknU32


/* 
* FUN : cmPkSztECGILst
*  DESC: Function to Pack SztECGILst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztECGILst
(
SztECGILst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztECGILst(param, mBuf)
SztECGILst *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztECGILst) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztEUTRAN_CGI, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztECGILst */



/* 
* FUN : cmPkSztEmergencyAreaIDLst
*  DESC: Function to Pack SztEmergencyAreaIDLst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztEmergencyAreaIDLst
(
SztEmergencyAreaIDLst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztEmergencyAreaIDLst(param, mBuf)
SztEmergencyAreaIDLst *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztEmergencyAreaIDLst) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztEmergencyAreaID, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztEmergencyAreaIDLst */

#define cmPkSztENB_IDmacroENB_ID cmPkTknBStr32 
#define cmPkSztENB_IDhomeENB_ID cmPkTknBStr32 


/* 
* FUN : cmPkSztENB_ID
*  DESC: Function to Pack SztENB_ID structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztENB_ID
(
SztENB_ID *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztENB_ID(param, mBuf)
SztENB_ID *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztENB_ID) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case ENB_ID_HOMEENB_ID :
				CMCHKPK(cmPkSztENB_IDhomeENB_ID, &param->val.homeENB_ID, mBuf); 
				break;
			case ENB_ID_MACROENB_ID :
				CMCHKPK(cmPkSztENB_IDmacroENB_ID, &param->val.macroENB_ID, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztENB_ID */



/* 
* FUN : cmPkSzt_ExtnLAI_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnLAI_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnLAI_ExtIEsCls
(
Szt_ExtnLAI_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnLAI_ExtIEsCls(param, val, mBuf)
Szt_ExtnLAI_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnLAI_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnLAI_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_LAI_ExtIEs
*  DESC: Function to Pack SztProtExtnField_LAI_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_LAI_ExtIEs
(
SztProtExtnField_LAI_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_LAI_ExtIEs(param, mBuf)
SztProtExtnField_LAI_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_LAI_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnLAI_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_LAI_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_LAI_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_LAI_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_LAI_ExtIEs
(
SztProtExtnCont_LAI_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_LAI_ExtIEs(param, mBuf)
SztProtExtnCont_LAI_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_LAI_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_LAI_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_LAI_ExtIEs */



/* 
* FUN : cmPkSztLAI
*  DESC: Function to Pack SztLAI structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztLAI
(
SztLAI *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztLAI(param, mBuf)
SztLAI *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztLAI) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_LAI_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztLAC, &param->lAC, mBuf); 
		CMCHKPK(cmPkSztPLMNidentity, &param->pLMNidentity, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztLAI */



/* 
* FUN : cmPkSzt_ExtnGERAN_Cell_ID_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnGERAN_Cell_ID_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnGERAN_Cell_ID_ExtIEsCls
(
Szt_ExtnGERAN_Cell_ID_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnGERAN_Cell_ID_ExtIEsCls(param, val, mBuf)
Szt_ExtnGERAN_Cell_ID_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnGERAN_Cell_ID_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnGERAN_Cell_ID_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_GERAN_Cell_ID_ExtIEs
*  DESC: Function to Pack SztProtExtnField_GERAN_Cell_ID_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_GERAN_Cell_ID_ExtIEs
(
SztProtExtnField_GERAN_Cell_ID_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_GERAN_Cell_ID_ExtIEs(param, mBuf)
SztProtExtnField_GERAN_Cell_ID_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_GERAN_Cell_ID_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnGERAN_Cell_ID_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_GERAN_Cell_ID_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_GERAN_Cell_ID_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_GERAN_Cell_ID_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_GERAN_Cell_ID_ExtIEs
(
SztProtExtnCont_GERAN_Cell_ID_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_GERAN_Cell_ID_ExtIEs(param, mBuf)
SztProtExtnCont_GERAN_Cell_ID_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_GERAN_Cell_ID_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_GERAN_Cell_ID_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_GERAN_Cell_ID_ExtIEs */



/* 
* FUN : cmPkSztGERAN_Cell_ID
*  DESC: Function to Pack SztGERAN_Cell_ID structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztGERAN_Cell_ID
(
SztGERAN_Cell_ID *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztGERAN_Cell_ID(param, mBuf)
SztGERAN_Cell_ID *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztGERAN_Cell_ID) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_GERAN_Cell_ID_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztCI, &param->cI, mBuf); 
		CMCHKPK(cmPkSztRAC, &param->rAC, mBuf); 
		CMCHKPK(cmPkSztLAI, &param->lAI, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztGERAN_Cell_ID */



/* 
* FUN : cmPkSzt_ExtnGlobalENB_ID_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnGlobalENB_ID_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnGlobalENB_ID_ExtIEsCls
(
Szt_ExtnGlobalENB_ID_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnGlobalENB_ID_ExtIEsCls(param, val, mBuf)
Szt_ExtnGlobalENB_ID_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnGlobalENB_ID_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnGlobalENB_ID_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_GlobalENB_ID_ExtIEs
*  DESC: Function to Pack SztProtExtnField_GlobalENB_ID_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_GlobalENB_ID_ExtIEs
(
SztProtExtnField_GlobalENB_ID_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_GlobalENB_ID_ExtIEs(param, mBuf)
SztProtExtnField_GlobalENB_ID_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_GlobalENB_ID_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnGlobalENB_ID_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_GlobalENB_ID_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_GlobalENB_ID_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_GlobalENB_ID_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_GlobalENB_ID_ExtIEs
(
SztProtExtnCont_GlobalENB_ID_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_GlobalENB_ID_ExtIEs(param, mBuf)
SztProtExtnCont_GlobalENB_ID_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_GlobalENB_ID_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_GlobalENB_ID_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_GlobalENB_ID_ExtIEs */



/* 
* FUN : cmPkSztGlobal_ENB_ID
*  DESC: Function to Pack SztGlobal_ENB_ID structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztGlobal_ENB_ID
(
SztGlobal_ENB_ID *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztGlobal_ENB_ID(param, mBuf)
SztGlobal_ENB_ID *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztGlobal_ENB_ID) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_GlobalENB_ID_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztENB_ID, &param->eNB_ID, mBuf); 
		CMCHKPK(cmPkSztPLMNidentity, &param->pLMNidentity, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztGlobal_ENB_ID */

#define cmPkSztMME_Group_ID cmPkTknStr4 
#define cmPkSztMME_Code cmPkTknStr4 


/* 
* FUN : cmPkSzt_ExtnGUMMEI_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnGUMMEI_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnGUMMEI_ExtIEsCls
(
Szt_ExtnGUMMEI_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnGUMMEI_ExtIEsCls(param, val, mBuf)
Szt_ExtnGUMMEI_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnGUMMEI_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnGUMMEI_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_GUMMEI_ExtIEs
*  DESC: Function to Pack SztProtExtnField_GUMMEI_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_GUMMEI_ExtIEs
(
SztProtExtnField_GUMMEI_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_GUMMEI_ExtIEs(param, mBuf)
SztProtExtnField_GUMMEI_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_GUMMEI_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnGUMMEI_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_GUMMEI_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_GUMMEI_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_GUMMEI_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_GUMMEI_ExtIEs
(
SztProtExtnCont_GUMMEI_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_GUMMEI_ExtIEs(param, mBuf)
SztProtExtnCont_GUMMEI_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_GUMMEI_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_GUMMEI_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_GUMMEI_ExtIEs */



/* 
* FUN : cmPkSztGUMMEI
*  DESC: Function to Pack SztGUMMEI structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztGUMMEI
(
SztGUMMEI *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztGUMMEI(param, mBuf)
SztGUMMEI *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztGUMMEI) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_GUMMEI_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztMME_Code, &param->mME_Code, mBuf); 
		CMCHKPK(cmPkSztMME_Group_ID, &param->mME_Group_ID, mBuf); 
		CMCHKPK(cmPkSztPLMNidentity, &param->pLMN_Identity, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztGUMMEI */



/* 
* FUN : cmPkSztGUMMEILst
*  DESC: Function to Pack SztGUMMEILst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztGUMMEILst
(
SztGUMMEILst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztGUMMEILst(param, mBuf)
SztGUMMEILst *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztGUMMEILst) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztGUMMEI, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztGUMMEILst */



/* 
* FUN : cmPkSzt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls
(
Szt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls(param, val, mBuf)
Szt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs
*  DESC: Function to Pack SztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs
(
SztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs(param, mBuf)
SztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs
(
SztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs(param, mBuf)
SztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs */



/* 
* FUN : cmPkSztENB_StatusTfr_TprntCont
*  DESC: Function to Pack SztENB_StatusTfr_TprntCont structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztENB_StatusTfr_TprntCont
(
SztENB_StatusTfr_TprntCont *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztENB_StatusTfr_TprntCont(param, mBuf)
SztENB_StatusTfr_TprntCont *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztENB_StatusTfr_TprntCont) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztBrs_SubjToStatusTfrLst, &param->bearers_SubjToStatusTfrLst, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztENB_StatusTfr_TprntCont */

#define cmPkSztENB_UE_S1AP_ID cmPkTknU32 
#define cmPkSztENBname cmPkTknStrOSXL 
#define cmPkSztTportLyrAddr cmPkTknStrBSXL 


/* 
* FUN : cmPkSztENBX2TLAs
*  DESC: Function to Pack SztENBX2TLAs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztENBX2TLAs
(
SztENBX2TLAs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztENBX2TLAs(param, mBuf)
SztENBX2TLAs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztENBX2TLAs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztTportLyrAddr, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztENBX2TLAs */

#define cmPkSztEncryptionAlgorithms cmPkTknBStr32 


/* 
* FUN : cmPkSztEPLMNs
*  DESC: Function to Pack SztEPLMNs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztEPLMNs
(
SztEPLMNs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztEPLMNs(param, mBuf)
SztEPLMNs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztEPLMNs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztPLMNidentity, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztEPLMNs */

#define cmPkSztEventTyp cmPkTknU32


/* 
* FUN : cmPkSzt_ExtnE_RABInformLstItem_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnE_RABInformLstItem_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnE_RABInformLstItem_ExtIEsCls
(
Szt_ExtnE_RABInformLstItem_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnE_RABInformLstItem_ExtIEsCls(param, val, mBuf)
Szt_ExtnE_RABInformLstItem_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnE_RABInformLstItem_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnE_RABInformLstItem_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_E_RABInformLstItem_ExtIEs
*  DESC: Function to Pack SztProtExtnField_E_RABInformLstItem_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_E_RABInformLstItem_ExtIEs
(
SztProtExtnField_E_RABInformLstItem_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_E_RABInformLstItem_ExtIEs(param, mBuf)
SztProtExtnField_E_RABInformLstItem_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_E_RABInformLstItem_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnE_RABInformLstItem_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_E_RABInformLstItem_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_E_RABInformLstItem_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_E_RABInformLstItem_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_E_RABInformLstItem_ExtIEs
(
SztProtExtnCont_E_RABInformLstItem_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_E_RABInformLstItem_ExtIEs(param, mBuf)
SztProtExtnCont_E_RABInformLstItem_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_E_RABInformLstItem_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_E_RABInformLstItem_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_E_RABInformLstItem_ExtIEs */



/* 
* FUN : cmPkSztE_RABInformLstItem
*  DESC: Function to Pack SztE_RABInformLstItem structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABInformLstItem
(
SztE_RABInformLstItem *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABInformLstItem(param, mBuf)
SztE_RABInformLstItem *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztE_RABInformLstItem) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_E_RABInformLstItem_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztDL_Fwding, &param->dL_Fwding, mBuf); 
		CMCHKPK(cmPkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABInformLstItem */



/* 
* FUN : cmPkSzt_ValueE_RABInformLstIEsCls
*  DESC: Function to Pack Szt_ValueE_RABInformLstIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueE_RABInformLstIEsCls
(
Szt_ValueE_RABInformLstIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueE_RABInformLstIEsCls(param, val, mBuf)
Szt_ValueE_RABInformLstIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueE_RABInformLstIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABInformLstItem:
			CMCHKPK(cmPkSztE_RABInformLstItem, &param->u.sztE_RABInformLstItem, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueE_RABInformLstIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_E_RABInformLstIEs
*  DESC: Function to Pack SztProtIE_Field_E_RABInformLstIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_E_RABInformLstIEs
(
SztProtIE_Field_E_RABInformLstIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_E_RABInformLstIEs(param, mBuf)
SztProtIE_Field_E_RABInformLstIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_E_RABInformLstIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueE_RABInformLstIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_E_RABInformLstIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmPkSztProtIE_SingleCont_E_RABInformLstIEs cmPkSztProtIE_Field_E_RABInformLstIEs


/* 
* FUN : cmPkSztE_RABInformLst
*  DESC: Function to Pack SztE_RABInformLst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABInformLst
(
SztE_RABInformLst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABInformLst(param, mBuf)
SztE_RABInformLst *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztE_RABInformLst) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_SingleCont_E_RABInformLstIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABInformLst */



/* 
* FUN : cmPkSzt_ExtnE_RABItem_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnE_RABItem_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnE_RABItem_ExtIEsCls
(
Szt_ExtnE_RABItem_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnE_RABItem_ExtIEsCls(param, val, mBuf)
Szt_ExtnE_RABItem_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnE_RABItem_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnE_RABItem_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_E_RABItem_ExtIEs
*  DESC: Function to Pack SztProtExtnField_E_RABItem_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_E_RABItem_ExtIEs
(
SztProtExtnField_E_RABItem_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_E_RABItem_ExtIEs(param, mBuf)
SztProtExtnField_E_RABItem_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_E_RABItem_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnE_RABItem_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_E_RABItem_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_E_RABItem_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_E_RABItem_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_E_RABItem_ExtIEs
(
SztProtExtnCont_E_RABItem_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_E_RABItem_ExtIEs(param, mBuf)
SztProtExtnCont_E_RABItem_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_E_RABItem_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_E_RABItem_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_E_RABItem_ExtIEs */



/* 
* FUN : cmPkSztE_RABItem
*  DESC: Function to Pack SztE_RABItem structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABItem
(
SztE_RABItem *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABItem(param, mBuf)
SztE_RABItem *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztE_RABItem) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_E_RABItem_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztCause, &param->cause, mBuf); 
		CMCHKPK(cmPkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABItem */



/* 
* FUN : cmPkSzt_ValueE_RABItemIEsCls
*  DESC: Function to Pack Szt_ValueE_RABItemIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueE_RABItemIEsCls
(
Szt_ValueE_RABItemIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueE_RABItemIEsCls(param, val, mBuf)
Szt_ValueE_RABItemIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueE_RABItemIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABItem:
			CMCHKPK(cmPkSztE_RABItem, &param->u.sztE_RABItem, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueE_RABItemIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_E_RABItemIEs
*  DESC: Function to Pack SztProtIE_Field_E_RABItemIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_E_RABItemIEs
(
SztProtIE_Field_E_RABItemIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_E_RABItemIEs(param, mBuf)
SztProtIE_Field_E_RABItemIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_E_RABItemIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueE_RABItemIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_E_RABItemIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmPkSztProtIE_SingleCont_E_RABItemIEs cmPkSztProtIE_Field_E_RABItemIEs


/* 
* FUN : cmPkSztE_RABLst
*  DESC: Function to Pack SztE_RABLst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABLst
(
SztE_RABLst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABLst(param, mBuf)
SztE_RABLst *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztE_RABLst) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_SingleCont_E_RABItemIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABLst */

#define cmPkSztQCI cmPkTknU32 


/* 
* FUN : cmPkSzt_ExtnGBR_QosInform_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnGBR_QosInform_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnGBR_QosInform_ExtIEsCls
(
Szt_ExtnGBR_QosInform_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnGBR_QosInform_ExtIEsCls(param, val, mBuf)
Szt_ExtnGBR_QosInform_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnGBR_QosInform_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnGBR_QosInform_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_GBR_QosInform_ExtIEs
*  DESC: Function to Pack SztProtExtnField_GBR_QosInform_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_GBR_QosInform_ExtIEs
(
SztProtExtnField_GBR_QosInform_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_GBR_QosInform_ExtIEs(param, mBuf)
SztProtExtnField_GBR_QosInform_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_GBR_QosInform_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnGBR_QosInform_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_GBR_QosInform_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_GBR_QosInform_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_GBR_QosInform_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_GBR_QosInform_ExtIEs
(
SztProtExtnCont_GBR_QosInform_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_GBR_QosInform_ExtIEs(param, mBuf)
SztProtExtnCont_GBR_QosInform_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_GBR_QosInform_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_GBR_QosInform_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_GBR_QosInform_ExtIEs */



/* 
* FUN : cmPkSztGBR_QosInform
*  DESC: Function to Pack SztGBR_QosInform structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztGBR_QosInform
(
SztGBR_QosInform *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztGBR_QosInform(param, mBuf)
SztGBR_QosInform *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztGBR_QosInform) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_GBR_QosInform_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztBitRate, &param->e_RAB_GuaranteedBitrateUL, mBuf); 
		CMCHKPK(cmPkSztBitRate, &param->e_RAB_GuaranteedBitrateDL, mBuf); 
		CMCHKPK(cmPkSztBitRate, &param->e_RAB_MaxBitrateUL, mBuf); 
		CMCHKPK(cmPkSztBitRate, &param->e_RAB_MaxBitrateDL, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztGBR_QosInform */



/* 
* FUN : cmPkSzt_ExtnE_RABQoSParams_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnE_RABQoSParams_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnE_RABQoSParams_ExtIEsCls
(
Szt_ExtnE_RABQoSParams_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnE_RABQoSParams_ExtIEsCls(param, val, mBuf)
Szt_ExtnE_RABQoSParams_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnE_RABQoSParams_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnE_RABQoSParams_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_E_RABQoSParams_ExtIEs
*  DESC: Function to Pack SztProtExtnField_E_RABQoSParams_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_E_RABQoSParams_ExtIEs
(
SztProtExtnField_E_RABQoSParams_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_E_RABQoSParams_ExtIEs(param, mBuf)
SztProtExtnField_E_RABQoSParams_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_E_RABQoSParams_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnE_RABQoSParams_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_E_RABQoSParams_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_E_RABQoSParams_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_E_RABQoSParams_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_E_RABQoSParams_ExtIEs
(
SztProtExtnCont_E_RABQoSParams_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_E_RABQoSParams_ExtIEs(param, mBuf)
SztProtExtnCont_E_RABQoSParams_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_E_RABQoSParams_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_E_RABQoSParams_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_E_RABQoSParams_ExtIEs */



/* 
* FUN : cmPkSztE_RABLvlQoSParams
*  DESC: Function to Pack SztE_RABLvlQoSParams structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABLvlQoSParams
(
SztE_RABLvlQoSParams *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABLvlQoSParams(param, mBuf)
SztE_RABLvlQoSParams *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztE_RABLvlQoSParams) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_E_RABQoSParams_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztGBR_QosInform, &param->gbrQosInform, mBuf); 
		CMCHKPK(cmPkSztAllocnAndRetentionPriority, &param->allocationRetentionPriority, mBuf); 
		CMCHKPK(cmPkSztQCI, &param->qCI, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABLvlQoSParams */

#define cmPkSztEUTRANRoundTripDelayEstimationInfo cmPkTknU32 
#define cmPkSztExtendedRNC_ID cmPkTknU32 
#define cmPkSztExtendedRepetitionPeriod cmPkTknU32 
#define cmPkSztForbiddenInterRATs cmPkTknU32


/* 
* FUN : cmPkSztForbiddenTACs
*  DESC: Function to Pack SztForbiddenTACs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztForbiddenTACs
(
SztForbiddenTACs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztForbiddenTACs(param, mBuf)
SztForbiddenTACs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztForbiddenTACs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztTAC, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztForbiddenTACs */



/* 
* FUN : cmPkSzt_ExtnForbiddenTAs_Item_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnForbiddenTAs_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnForbiddenTAs_Item_ExtIEsCls
(
Szt_ExtnForbiddenTAs_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnForbiddenTAs_Item_ExtIEsCls(param, val, mBuf)
Szt_ExtnForbiddenTAs_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnForbiddenTAs_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnForbiddenTAs_Item_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_ForbiddenTAs_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnField_ForbiddenTAs_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_ForbiddenTAs_Item_ExtIEs
(
SztProtExtnField_ForbiddenTAs_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_ForbiddenTAs_Item_ExtIEs(param, mBuf)
SztProtExtnField_ForbiddenTAs_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_ForbiddenTAs_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnForbiddenTAs_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_ForbiddenTAs_Item_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_ForbiddenTAs_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_ForbiddenTAs_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_ForbiddenTAs_Item_ExtIEs
(
SztProtExtnCont_ForbiddenTAs_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_ForbiddenTAs_Item_ExtIEs(param, mBuf)
SztProtExtnCont_ForbiddenTAs_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_ForbiddenTAs_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_ForbiddenTAs_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_ForbiddenTAs_Item_ExtIEs */



/* 
* FUN : cmPkSztForbiddenTAs_Item
*  DESC: Function to Pack SztForbiddenTAs_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztForbiddenTAs_Item
(
SztForbiddenTAs_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztForbiddenTAs_Item(param, mBuf)
SztForbiddenTAs_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztForbiddenTAs_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_ForbiddenTAs_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztForbiddenTACs, &param->forbiddenTACs, mBuf); 
		CMCHKPK(cmPkSztPLMNidentity, &param->pLMN_Identity, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztForbiddenTAs_Item */



/* 
* FUN : cmPkSztForbiddenTAs
*  DESC: Function to Pack SztForbiddenTAs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztForbiddenTAs
(
SztForbiddenTAs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztForbiddenTAs(param, mBuf)
SztForbiddenTAs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztForbiddenTAs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztForbiddenTAs_Item, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztForbiddenTAs */



/* 
* FUN : cmPkSztForbiddenLACs
*  DESC: Function to Pack SztForbiddenLACs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztForbiddenLACs
(
SztForbiddenLACs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztForbiddenLACs(param, mBuf)
SztForbiddenLACs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztForbiddenLACs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztLAC, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztForbiddenLACs */



/* 
* FUN : cmPkSzt_ExtnForbiddenLAs_Item_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnForbiddenLAs_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnForbiddenLAs_Item_ExtIEsCls
(
Szt_ExtnForbiddenLAs_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnForbiddenLAs_Item_ExtIEsCls(param, val, mBuf)
Szt_ExtnForbiddenLAs_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnForbiddenLAs_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnForbiddenLAs_Item_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_ForbiddenLAs_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnField_ForbiddenLAs_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_ForbiddenLAs_Item_ExtIEs
(
SztProtExtnField_ForbiddenLAs_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_ForbiddenLAs_Item_ExtIEs(param, mBuf)
SztProtExtnField_ForbiddenLAs_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_ForbiddenLAs_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnForbiddenLAs_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_ForbiddenLAs_Item_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_ForbiddenLAs_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_ForbiddenLAs_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_ForbiddenLAs_Item_ExtIEs
(
SztProtExtnCont_ForbiddenLAs_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_ForbiddenLAs_Item_ExtIEs(param, mBuf)
SztProtExtnCont_ForbiddenLAs_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_ForbiddenLAs_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_ForbiddenLAs_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_ForbiddenLAs_Item_ExtIEs */



/* 
* FUN : cmPkSztForbiddenLAs_Item
*  DESC: Function to Pack SztForbiddenLAs_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztForbiddenLAs_Item
(
SztForbiddenLAs_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztForbiddenLAs_Item(param, mBuf)
SztForbiddenLAs_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztForbiddenLAs_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_ForbiddenLAs_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztForbiddenLACs, &param->forbiddenLACs, mBuf); 
		CMCHKPK(cmPkSztPLMNidentity, &param->pLMN_Identity, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztForbiddenLAs_Item */



/* 
* FUN : cmPkSztForbiddenLAs
*  DESC: Function to Pack SztForbiddenLAs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztForbiddenLAs
(
SztForbiddenLAs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztForbiddenLAs(param, mBuf)
SztForbiddenLAs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztForbiddenLAs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztForbiddenLAs_Item, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztForbiddenLAs */

#define cmPkSztGTP_TEID cmPkTknStrOSXL 
#define cmPkSztGUMMEITyp cmPkTknU32
#define cmPkSztGWCntxtRlsInd cmPkTknU32


/* 
* FUN : cmPkSzt_ExtnHovrRestrnLst_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnHovrRestrnLst_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnHovrRestrnLst_ExtIEsCls
(
Szt_ExtnHovrRestrnLst_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnHovrRestrnLst_ExtIEsCls(param, val, mBuf)
Szt_ExtnHovrRestrnLst_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnHovrRestrnLst_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnHovrRestrnLst_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_HovrRestrnLst_ExtIEs
*  DESC: Function to Pack SztProtExtnField_HovrRestrnLst_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_HovrRestrnLst_ExtIEs
(
SztProtExtnField_HovrRestrnLst_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_HovrRestrnLst_ExtIEs(param, mBuf)
SztProtExtnField_HovrRestrnLst_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_HovrRestrnLst_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnHovrRestrnLst_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_HovrRestrnLst_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_HovrRestrnLst_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_HovrRestrnLst_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_HovrRestrnLst_ExtIEs
(
SztProtExtnCont_HovrRestrnLst_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_HovrRestrnLst_ExtIEs(param, mBuf)
SztProtExtnCont_HovrRestrnLst_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_HovrRestrnLst_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_HovrRestrnLst_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_HovrRestrnLst_ExtIEs */



/* 
* FUN : cmPkSztHovrRestrnLst
*  DESC: Function to Pack SztHovrRestrnLst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztHovrRestrnLst
(
SztHovrRestrnLst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztHovrRestrnLst(param, mBuf)
SztHovrRestrnLst *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztHovrRestrnLst) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_HovrRestrnLst_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztForbiddenInterRATs, &param->forbiddenInterRATs, mBuf); 
		CMCHKPK(cmPkSztForbiddenLAs, &param->forbiddenLAs, mBuf); 
		CMCHKPK(cmPkSztForbiddenTAs, &param->forbiddenTAs, mBuf); 
		CMCHKPK(cmPkSztEPLMNs, &param->equivalentPLMNs, mBuf); 
		CMCHKPK(cmPkSztPLMNidentity, &param->servingPLMN, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztHovrRestrnLst */

#define cmPkSztHovrTyp cmPkTknU32
#define cmPkSztMeasurementsToActivate cmPkTknBStr32 
#define cmPkSztM1RprtngTrigger cmPkTknU32
#define cmPkSztThreshold_RSRP cmPkTknU32 
#define cmPkSztThreshold_RSRQ cmPkTknU32 


/* 
* FUN : cmPkSztMeasurementThresholdA2
*  DESC: Function to Pack SztMeasurementThresholdA2 structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztMeasurementThresholdA2
(
SztMeasurementThresholdA2 *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztMeasurementThresholdA2(param, mBuf)
SztMeasurementThresholdA2 *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztMeasurementThresholdA2) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case MEASUREMENTTHRESHOLDA2_THRESHOLD_RSRQ :
				CMCHKPK(cmPkSztThreshold_RSRQ, &param->val.threshold_RSRQ, mBuf); 
				break;
			case MEASUREMENTTHRESHOLDA2_THRESHOLD_RSRP :
				CMCHKPK(cmPkSztThreshold_RSRP, &param->val.threshold_RSRP, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztMeasurementThresholdA2 */



/* 
* FUN : cmPkSzt_ExtnM1ThresholdEventA2_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnM1ThresholdEventA2_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnM1ThresholdEventA2_ExtIEsCls
(
Szt_ExtnM1ThresholdEventA2_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnM1ThresholdEventA2_ExtIEsCls(param, val, mBuf)
Szt_ExtnM1ThresholdEventA2_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnM1ThresholdEventA2_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnM1ThresholdEventA2_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_M1ThresholdEventA2_ExtIEs
*  DESC: Function to Pack SztProtExtnField_M1ThresholdEventA2_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_M1ThresholdEventA2_ExtIEs
(
SztProtExtnField_M1ThresholdEventA2_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_M1ThresholdEventA2_ExtIEs(param, mBuf)
SztProtExtnField_M1ThresholdEventA2_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_M1ThresholdEventA2_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnM1ThresholdEventA2_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_M1ThresholdEventA2_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_M1ThresholdEventA2_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_M1ThresholdEventA2_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_M1ThresholdEventA2_ExtIEs
(
SztProtExtnCont_M1ThresholdEventA2_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_M1ThresholdEventA2_ExtIEs(param, mBuf)
SztProtExtnCont_M1ThresholdEventA2_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_M1ThresholdEventA2_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_M1ThresholdEventA2_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_M1ThresholdEventA2_ExtIEs */



/* 
* FUN : cmPkSztM1ThresholdEventA2
*  DESC: Function to Pack SztM1ThresholdEventA2 structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztM1ThresholdEventA2
(
SztM1ThresholdEventA2 *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztM1ThresholdEventA2(param, mBuf)
SztM1ThresholdEventA2 *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztM1ThresholdEventA2) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_M1ThresholdEventA2_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztMeasurementThresholdA2, &param->measurementThreshold, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztM1ThresholdEventA2 */

#define cmPkSztReportIntervalMDT cmPkTknU32
#define cmPkSztReportAmountMDT cmPkTknU32


/* 
* FUN : cmPkSzt_ExtnM1PeriodicRprtng_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnM1PeriodicRprtng_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnM1PeriodicRprtng_ExtIEsCls
(
Szt_ExtnM1PeriodicRprtng_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnM1PeriodicRprtng_ExtIEsCls(param, val, mBuf)
Szt_ExtnM1PeriodicRprtng_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnM1PeriodicRprtng_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnM1PeriodicRprtng_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_M1PeriodicRprtng_ExtIEs
*  DESC: Function to Pack SztProtExtnField_M1PeriodicRprtng_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_M1PeriodicRprtng_ExtIEs
(
SztProtExtnField_M1PeriodicRprtng_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_M1PeriodicRprtng_ExtIEs(param, mBuf)
SztProtExtnField_M1PeriodicRprtng_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_M1PeriodicRprtng_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnM1PeriodicRprtng_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_M1PeriodicRprtng_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_M1PeriodicRprtng_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_M1PeriodicRprtng_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_M1PeriodicRprtng_ExtIEs
(
SztProtExtnCont_M1PeriodicRprtng_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_M1PeriodicRprtng_ExtIEs(param, mBuf)
SztProtExtnCont_M1PeriodicRprtng_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_M1PeriodicRprtng_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_M1PeriodicRprtng_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_M1PeriodicRprtng_ExtIEs */



/* 
* FUN : cmPkSztM1PeriodicRprtng
*  DESC: Function to Pack SztM1PeriodicRprtng structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztM1PeriodicRprtng
(
SztM1PeriodicRprtng *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztM1PeriodicRprtng(param, mBuf)
SztM1PeriodicRprtng *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztM1PeriodicRprtng) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_M1PeriodicRprtng_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztReportAmountMDT, &param->reportAmount, mBuf); 
		CMCHKPK(cmPkSztReportIntervalMDT, &param->reportInterval, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztM1PeriodicRprtng */

#define cmPkSztM3period cmPkTknU32


/* 
* FUN : cmPkSzt_ExtnM3Config_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnM3Config_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnM3Config_ExtIEsCls
(
Szt_ExtnM3Config_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnM3Config_ExtIEsCls(param, val, mBuf)
Szt_ExtnM3Config_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnM3Config_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnM3Config_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_M3Config_ExtIEs
*  DESC: Function to Pack SztProtExtnField_M3Config_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_M3Config_ExtIEs
(
SztProtExtnField_M3Config_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_M3Config_ExtIEs(param, mBuf)
SztProtExtnField_M3Config_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_M3Config_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnM3Config_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_M3Config_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_M3Config_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_M3Config_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_M3Config_ExtIEs
(
SztProtExtnCont_M3Config_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_M3Config_ExtIEs(param, mBuf)
SztProtExtnCont_M3Config_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_M3Config_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_M3Config_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_M3Config_ExtIEs */



/* 
* FUN : cmPkSztM3Config
*  DESC: Function to Pack SztM3Config structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztM3Config
(
SztM3Config *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztM3Config(param, mBuf)
SztM3Config *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztM3Config) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_M3Config_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztM3period, &param->m3period, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztM3Config */

#define cmPkSztM4period cmPkTknU32
#define cmPkSztLinks_to_log cmPkTknU32


/* 
* FUN : cmPkSzt_ExtnM4Config_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnM4Config_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnM4Config_ExtIEsCls
(
Szt_ExtnM4Config_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnM4Config_ExtIEsCls(param, val, mBuf)
Szt_ExtnM4Config_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnM4Config_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnM4Config_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_M4Config_ExtIEs
*  DESC: Function to Pack SztProtExtnField_M4Config_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_M4Config_ExtIEs
(
SztProtExtnField_M4Config_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_M4Config_ExtIEs(param, mBuf)
SztProtExtnField_M4Config_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_M4Config_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnM4Config_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_M4Config_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_M4Config_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_M4Config_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_M4Config_ExtIEs
(
SztProtExtnCont_M4Config_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_M4Config_ExtIEs(param, mBuf)
SztProtExtnCont_M4Config_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_M4Config_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_M4Config_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_M4Config_ExtIEs */



/* 
* FUN : cmPkSztM4Config
*  DESC: Function to Pack SztM4Config structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztM4Config
(
SztM4Config *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztM4Config(param, mBuf)
SztM4Config *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztM4Config) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_M4Config_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztLinks_to_log, &param->m4_links_to_log, mBuf); 
		CMCHKPK(cmPkSztM4period, &param->m4period, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztM4Config */

#define cmPkSztM5period cmPkTknU32


/* 
* FUN : cmPkSzt_ExtnM5Config_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnM5Config_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnM5Config_ExtIEsCls
(
Szt_ExtnM5Config_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnM5Config_ExtIEsCls(param, val, mBuf)
Szt_ExtnM5Config_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnM5Config_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnM5Config_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_M5Config_ExtIEs
*  DESC: Function to Pack SztProtExtnField_M5Config_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_M5Config_ExtIEs
(
SztProtExtnField_M5Config_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_M5Config_ExtIEs(param, mBuf)
SztProtExtnField_M5Config_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_M5Config_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnM5Config_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_M5Config_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_M5Config_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_M5Config_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_M5Config_ExtIEs
(
SztProtExtnCont_M5Config_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_M5Config_ExtIEs(param, mBuf)
SztProtExtnCont_M5Config_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_M5Config_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_M5Config_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_M5Config_ExtIEs */



/* 
* FUN : cmPkSztM5Config
*  DESC: Function to Pack SztM5Config structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztM5Config
(
SztM5Config *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztM5Config(param, mBuf)
SztM5Config *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztM5Config) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_M5Config_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztLinks_to_log, &param->m5_links_to_log, mBuf); 
		CMCHKPK(cmPkSztM5period, &param->m5period, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztM5Config */

#define cmPkSztMDT_Loc_Info cmPkTknBStr32 


/* 
* FUN : cmPkSzt_ExtnImmediateMDT_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnImmediateMDT_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnImmediateMDT_ExtIEsCls
(
Szt_ExtnImmediateMDT_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnImmediateMDT_ExtIEsCls(param, val, mBuf)
Szt_ExtnImmediateMDT_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnImmediateMDT_ExtIEsCls) 
	
	switch (val)
	{
		case Sztid_M3Config:
			CMCHKPK(cmPkSztM3Config, &param->u.sztM3Config, mBuf);
			break;
		case Sztid_M4Config:
			CMCHKPK(cmPkSztM4Config, &param->u.sztM4Config, mBuf);
			break;
		case Sztid_M5Config:
			CMCHKPK(cmPkSztM5Config, &param->u.sztM5Config, mBuf);
			break;
		case Sztid_MDT_Loc_Info:
			CMCHKPK(cmPkSztMDT_Loc_Info, &param->u.sztMDT_Loc_Info, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ExtnImmediateMDT_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_ImmediateMDT_ExtIEs
*  DESC: Function to Pack SztProtExtnField_ImmediateMDT_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_ImmediateMDT_ExtIEs
(
SztProtExtnField_ImmediateMDT_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_ImmediateMDT_ExtIEs(param, mBuf)
SztProtExtnField_ImmediateMDT_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_ImmediateMDT_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnImmediateMDT_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_ImmediateMDT_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_ImmediateMDT_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_ImmediateMDT_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_ImmediateMDT_ExtIEs
(
SztProtExtnCont_ImmediateMDT_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_ImmediateMDT_ExtIEs(param, mBuf)
SztProtExtnCont_ImmediateMDT_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_ImmediateMDT_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_ImmediateMDT_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_ImmediateMDT_ExtIEs */



/* 
* FUN : cmPkSztImmediateMDT
*  DESC: Function to Pack SztImmediateMDT structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztImmediateMDT
(
SztImmediateMDT *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztImmediateMDT(param, mBuf)
SztImmediateMDT *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztImmediateMDT) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_ImmediateMDT_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztM1PeriodicRprtng, &param->m1periodicRprtng, mBuf); 
		CMCHKPK(cmPkSztM1ThresholdEventA2, &param->m1thresholdeventA2, mBuf); 
		CMCHKPK(cmPkSztM1RprtngTrigger, &param->m1reportingTrigger, mBuf); 
		CMCHKPK(cmPkSztMeasurementsToActivate, &param->measurementsToActivate, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztImmediateMDT */

#define cmPkSztIMSI cmPkTknStrOSXL 
#define cmPkSztIntegrityProtectionAlgorithms cmPkTknBStr32 
#define cmPkSztIntfsToTrace cmPkTknBStr32 
#define cmPkSztTime_UE_StayedInCell cmPkTknU32 
#define cmPkSztTime_UE_StayedInCell_EnhancedGranularity cmPkTknU32 


/* 
* FUN : cmPkSzt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls
(
Szt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls(param, val, mBuf)
Szt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls) 
	
	switch (val)
	{
		case Sztid_Time_UE_StayedInCell_EnhancedGranularity:
			CMCHKPK(cmPkSztTime_UE_StayedInCell_EnhancedGranularity, &param->u.sztTime_UE_StayedInCell_EnhancedGranularity, mBuf);
			break;
		case Sztid_HO_Cause:
			CMCHKPK(cmPkSztCause, &param->u.sztCause, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs
*  DESC: Function to Pack SztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs
(
SztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs(param, mBuf)
SztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs
(
SztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs(param, mBuf)
SztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs */



/* 
* FUN : cmPkSztLastVisitedEUTRANCellInform
*  DESC: Function to Pack SztLastVisitedEUTRANCellInform structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztLastVisitedEUTRANCellInform
(
SztLastVisitedEUTRANCellInform *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztLastVisitedEUTRANCellInform(param, mBuf)
SztLastVisitedEUTRANCellInform *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztLastVisitedEUTRANCellInform) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztTime_UE_StayedInCell, &param->time_UE_StayedInCell, mBuf); 
		CMCHKPK(cmPkSztCellTyp, &param->cellTyp, mBuf); 
		CMCHKPK(cmPkSztEUTRAN_CGI, &param->global_Cell_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztLastVisitedEUTRANCellInform */

#define cmPkSztLastVisitedUTRANCellInform cmPkTknStrOSXL 


/* 
* FUN : cmPkSztLastVisitedGERANCellInform
*  DESC: Function to Pack SztLastVisitedGERANCellInform structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztLastVisitedGERANCellInform
(
SztLastVisitedGERANCellInform *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztLastVisitedGERANCellInform(param, mBuf)
SztLastVisitedGERANCellInform *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztLastVisitedGERANCellInform) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case LASTVISITEDGERANCELLINFORM_UNDEFINED :
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztLastVisitedGERANCellInform */



/* 
* FUN : cmPkSztLastVisitedCell_Item
*  DESC: Function to Pack SztLastVisitedCell_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztLastVisitedCell_Item
(
SztLastVisitedCell_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztLastVisitedCell_Item(param, mBuf)
SztLastVisitedCell_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztLastVisitedCell_Item) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case LASTVISITEDCELL_ITEM_GERAN_CELL :
				CMCHKPK(cmPkSztLastVisitedGERANCellInform, &param->val.gERAN_Cell, mBuf); 
				break;
			case LASTVISITEDCELL_ITEM_UTRAN_CELL :
				CMCHKPK(cmPkSztLastVisitedUTRANCellInform, &param->val.uTRAN_Cell, mBuf); 
				break;
			case LASTVISITEDCELL_ITEM_E_UTRAN_CELL :
				CMCHKPK(cmPkSztLastVisitedEUTRANCellInform, &param->val.e_UTRAN_Cell, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztLastVisitedCell_Item */

#define cmPkSztL3_Inform cmPkTknStrOSXL 
#define cmPkSztLPPa_PDU cmPkTknStrOSXL 
#define cmPkSztLoggingInterval cmPkTknU32
#define cmPkSztLoggingDuration cmPkTknU32


/* 
* FUN : cmPkSzt_ExtnLoggedMDT_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnLoggedMDT_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnLoggedMDT_ExtIEsCls
(
Szt_ExtnLoggedMDT_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnLoggedMDT_ExtIEsCls(param, val, mBuf)
Szt_ExtnLoggedMDT_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnLoggedMDT_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnLoggedMDT_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_LoggedMDT_ExtIEs
*  DESC: Function to Pack SztProtExtnField_LoggedMDT_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_LoggedMDT_ExtIEs
(
SztProtExtnField_LoggedMDT_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_LoggedMDT_ExtIEs(param, mBuf)
SztProtExtnField_LoggedMDT_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_LoggedMDT_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnLoggedMDT_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_LoggedMDT_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_LoggedMDT_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_LoggedMDT_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_LoggedMDT_ExtIEs
(
SztProtExtnCont_LoggedMDT_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_LoggedMDT_ExtIEs(param, mBuf)
SztProtExtnCont_LoggedMDT_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_LoggedMDT_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_LoggedMDT_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_LoggedMDT_ExtIEs */



/* 
* FUN : cmPkSztLoggedMDT
*  DESC: Function to Pack SztLoggedMDT structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztLoggedMDT
(
SztLoggedMDT *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztLoggedMDT(param, mBuf)
SztLoggedMDT *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztLoggedMDT) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_LoggedMDT_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztLoggingDuration, &param->loggingDuration, mBuf); 
		CMCHKPK(cmPkSztLoggingInterval, &param->loggingInterval, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztLoggedMDT */

#define cmPkSztMDT_Actvn cmPkTknU32


/* 
* FUN : cmPkSztMDTMode
*  DESC: Function to Pack SztMDTMode structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztMDTMode
(
SztMDTMode *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztMDTMode(param, mBuf)
SztMDTMode *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztMDTMode) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case MDTMODE_LOGGEDMDT :
				CMCHKPK(cmPkSztLoggedMDT, &param->val.loggedMDT, mBuf); 
				break;
			case MDTMODE_IMMEDIATEMDT :
				CMCHKPK(cmPkSztImmediateMDT, &param->val.immediateMDT, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztMDTMode */



/* 
* FUN : cmPkSztMDTPLMNLst
*  DESC: Function to Pack SztMDTPLMNLst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztMDTPLMNLst
(
SztMDTPLMNLst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztMDTPLMNLst(param, mBuf)
SztMDTPLMNLst *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztMDTPLMNLst) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztPLMNidentity, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztMDTPLMNLst */



/* 
* FUN : cmPkSzt_ExtnMDT_Config_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnMDT_Config_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnMDT_Config_ExtIEsCls
(
Szt_ExtnMDT_Config_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnMDT_Config_ExtIEsCls(param, val, mBuf)
Szt_ExtnMDT_Config_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnMDT_Config_ExtIEsCls) 
	
	switch (val)
	{
		case Sztid_SignallingBasedMDTPLMNLst:
			CMCHKPK(cmPkSztMDTPLMNLst, &param->u.sztMDTPLMNLst, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ExtnMDT_Config_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_MDT_Config_ExtIEs
*  DESC: Function to Pack SztProtExtnField_MDT_Config_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_MDT_Config_ExtIEs
(
SztProtExtnField_MDT_Config_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_MDT_Config_ExtIEs(param, mBuf)
SztProtExtnField_MDT_Config_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_MDT_Config_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnMDT_Config_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_MDT_Config_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_MDT_Config_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_MDT_Config_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_MDT_Config_ExtIEs
(
SztProtExtnCont_MDT_Config_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_MDT_Config_ExtIEs(param, mBuf)
SztProtExtnCont_MDT_Config_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_MDT_Config_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_MDT_Config_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_MDT_Config_ExtIEs */



/* 
* FUN : cmPkSztMDT_Config
*  DESC: Function to Pack SztMDT_Config structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztMDT_Config
(
SztMDT_Config *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztMDT_Config(param, mBuf)
SztMDT_Config *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztMDT_Config) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_MDT_Config_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztMDTMode, &param->mDTMode, mBuf); 
		CMCHKPK(cmPkSztAreaScopeOfMDT, &param->areaScopeOfMDT, mBuf); 
		CMCHKPK(cmPkSztMDT_Actvn, &param->mdt_Actvn, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztMDT_Config */

#define cmPkSztManagementBasedMDTAllowed cmPkTknU32
#define cmPkSztPrivacyIndicator cmPkTknU32
#define cmPkSztMsgIdentifier cmPkTknBStr32 
#define cmPkSztMobilityInform cmPkTknBStr32 
#define cmPkSztMMEname cmPkTknStrOSXL 
#define cmPkSztMMERelaySupportIndicator cmPkTknU32
#define cmPkSztMME_UE_S1AP_ID cmPkTknU32 
#define cmPkSztM_TMSI cmPkTknStrOSXL 
#define cmPkSztMSClassmark2 cmPkTknStrOSXL 
#define cmPkSztMSClassmark3 cmPkTknStrOSXL 
#define cmPkSztNAS_PDU cmPkTknStrOSXL 
#define cmPkSztNASSecurParamsfromE_UTRAN cmPkTknStrOSXL 
#define cmPkSztNASSecurParamstoE_UTRAN cmPkTknStrOSXL 
#define cmPkSztNumberofBroadcastRqst cmPkTknU32 
#define cmPkSztOldBSS_ToNewBSS_Inform cmPkTknStrOSXL 
#define cmPkSztOverloadAction cmPkTknU32


/* 
* FUN : cmPkSztOverloadResp
*  DESC: Function to Pack SztOverloadResp structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztOverloadResp
(
SztOverloadResp *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztOverloadResp(param, mBuf)
SztOverloadResp *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztOverloadResp) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case OVERLOADRESP_OVERLOADACTION :
				CMCHKPK(cmPkSztOverloadAction, &param->val.overloadAction, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztOverloadResp */

#define cmPkSztPagDRX cmPkTknU32
#define cmPkSztPagPriority cmPkTknU32
#define cmPkSztPort_Number cmPkTknStr4 
#define cmPkSztPS_ServiceNotAvailable cmPkTknU32
#define cmPkSztRelativeMMECapacity cmPkTknU32 
#define cmPkSztRelayNode_Indicator cmPkTknU32
#define cmPkSztReportArea cmPkTknU32


/* 
* FUN : cmPkSzt_ExtnRqstTyp_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnRqstTyp_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnRqstTyp_ExtIEsCls
(
Szt_ExtnRqstTyp_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnRqstTyp_ExtIEsCls(param, val, mBuf)
Szt_ExtnRqstTyp_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnRqstTyp_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnRqstTyp_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_RqstTyp_ExtIEs
*  DESC: Function to Pack SztProtExtnField_RqstTyp_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_RqstTyp_ExtIEs
(
SztProtExtnField_RqstTyp_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_RqstTyp_ExtIEs(param, mBuf)
SztProtExtnField_RqstTyp_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_RqstTyp_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnRqstTyp_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_RqstTyp_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_RqstTyp_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_RqstTyp_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_RqstTyp_ExtIEs
(
SztProtExtnCont_RqstTyp_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_RqstTyp_ExtIEs(param, mBuf)
SztProtExtnCont_RqstTyp_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_RqstTyp_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_RqstTyp_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_RqstTyp_ExtIEs */



/* 
* FUN : cmPkSztRqstTyp
*  DESC: Function to Pack SztRqstTyp structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztRqstTyp
(
SztRqstTyp *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztRqstTyp(param, mBuf)
SztRqstTyp *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztRqstTyp) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_RqstTyp_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztReportArea, &param->reportArea, mBuf); 
		CMCHKPK(cmPkSztEventTyp, &param->eventTyp, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztRqstTyp */

#define cmPkSztRIMInform cmPkTknStrOSXL 
#define cmPkSztRNC_ID cmPkTknU32 


/* 
* FUN : cmPkSzt_ExtnTgetRNC_ID_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnTgetRNC_ID_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnTgetRNC_ID_ExtIEsCls
(
Szt_ExtnTgetRNC_ID_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnTgetRNC_ID_ExtIEsCls(param, val, mBuf)
Szt_ExtnTgetRNC_ID_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnTgetRNC_ID_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnTgetRNC_ID_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_TgetRNC_ID_ExtIEs
*  DESC: Function to Pack SztProtExtnField_TgetRNC_ID_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_TgetRNC_ID_ExtIEs
(
SztProtExtnField_TgetRNC_ID_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_TgetRNC_ID_ExtIEs(param, mBuf)
SztProtExtnField_TgetRNC_ID_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_TgetRNC_ID_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnTgetRNC_ID_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_TgetRNC_ID_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_TgetRNC_ID_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_TgetRNC_ID_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_TgetRNC_ID_ExtIEs
(
SztProtExtnCont_TgetRNC_ID_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_TgetRNC_ID_ExtIEs(param, mBuf)
SztProtExtnCont_TgetRNC_ID_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_TgetRNC_ID_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_TgetRNC_ID_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_TgetRNC_ID_ExtIEs */



/* 
* FUN : cmPkSztTgetRNC_ID
*  DESC: Function to Pack SztTgetRNC_ID structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztTgetRNC_ID
(
SztTgetRNC_ID *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztTgetRNC_ID(param, mBuf)
SztTgetRNC_ID *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztTgetRNC_ID) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_TgetRNC_ID_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztExtendedRNC_ID, &param->extendedRNC_ID, mBuf); 
		CMCHKPK(cmPkSztRNC_ID, &param->rNC_ID, mBuf); 
		CMCHKPK(cmPkSztRAC, &param->rAC, mBuf); 
		CMCHKPK(cmPkSztLAI, &param->lAI, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztTgetRNC_ID */



/* 
* FUN : cmPkSztRIMRoutingAddr
*  DESC: Function to Pack SztRIMRoutingAddr structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztRIMRoutingAddr
(
SztRIMRoutingAddr *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztRIMRoutingAddr(param, mBuf)
SztRIMRoutingAddr *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztRIMRoutingAddr) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case RIMROUTINGADDR_TARGETRNC_ID :
				CMCHKPK(cmPkSztTgetRNC_ID, &param->val.targetRNC_ID, mBuf); 
				break;
			case RIMROUTINGADDR_GERAN_CELL_ID :
				CMCHKPK(cmPkSztGERAN_Cell_ID, &param->val.gERAN_Cell_ID, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztRIMRoutingAddr */



/* 
* FUN : cmPkSzt_ExtnRIMTfr_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnRIMTfr_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnRIMTfr_ExtIEsCls
(
Szt_ExtnRIMTfr_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnRIMTfr_ExtIEsCls(param, val, mBuf)
Szt_ExtnRIMTfr_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnRIMTfr_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnRIMTfr_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_RIMTfr_ExtIEs
*  DESC: Function to Pack SztProtExtnField_RIMTfr_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_RIMTfr_ExtIEs
(
SztProtExtnField_RIMTfr_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_RIMTfr_ExtIEs(param, mBuf)
SztProtExtnField_RIMTfr_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_RIMTfr_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnRIMTfr_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_RIMTfr_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_RIMTfr_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_RIMTfr_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_RIMTfr_ExtIEs
(
SztProtExtnCont_RIMTfr_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_RIMTfr_ExtIEs(param, mBuf)
SztProtExtnCont_RIMTfr_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_RIMTfr_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_RIMTfr_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_RIMTfr_ExtIEs */



/* 
* FUN : cmPkSztRIMTfr
*  DESC: Function to Pack SztRIMTfr structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztRIMTfr
(
SztRIMTfr *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztRIMTfr(param, mBuf)
SztRIMTfr *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztRIMTfr) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_RIMTfr_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztRIMRoutingAddr, &param->rIMRoutingAddr, mBuf); 
		CMCHKPK(cmPkSztRIMInform, &param->rIMInform, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztRIMTfr */

#define cmPkSztRepetitionPeriod cmPkTknU32 
#define cmPkSztRRC_Cont cmPkTknStrOSXL 
#define cmPkSztRRC_Establishment_Cause cmPkTknU32
#define cmPkSztRouting_ID cmPkTknU32 
#define cmPkSztSecurKey cmPkTknStrBSXL 
#define cmPkSztSecurCntxtnextHopChainingCount cmPkTknU32 


/* 
* FUN : cmPkSzt_ExtnSecurCntxt_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnSecurCntxt_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnSecurCntxt_ExtIEsCls
(
Szt_ExtnSecurCntxt_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnSecurCntxt_ExtIEsCls(param, val, mBuf)
Szt_ExtnSecurCntxt_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnSecurCntxt_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnSecurCntxt_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_SecurCntxt_ExtIEs
*  DESC: Function to Pack SztProtExtnField_SecurCntxt_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_SecurCntxt_ExtIEs
(
SztProtExtnField_SecurCntxt_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_SecurCntxt_ExtIEs(param, mBuf)
SztProtExtnField_SecurCntxt_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_SecurCntxt_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnSecurCntxt_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_SecurCntxt_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_SecurCntxt_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_SecurCntxt_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_SecurCntxt_ExtIEs
(
SztProtExtnCont_SecurCntxt_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_SecurCntxt_ExtIEs(param, mBuf)
SztProtExtnCont_SecurCntxt_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_SecurCntxt_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_SecurCntxt_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_SecurCntxt_ExtIEs */



/* 
* FUN : cmPkSztSecurCntxt
*  DESC: Function to Pack SztSecurCntxt structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztSecurCntxt
(
SztSecurCntxt *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztSecurCntxt(param, mBuf)
SztSecurCntxt *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztSecurCntxt) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_SecurCntxt_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztSecurKey, &param->nextHopParameter, mBuf); 
		CMCHKPK(cmPkSztSecurCntxtnextHopChainingCount, &param->nextHopChainingCount, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztSecurCntxt */

#define cmPkSztSerialNumber cmPkTknBStr32 
#define cmPkSztSONInformRqst cmPkTknU32


/* 
* FUN : cmPkSztENBX2GTPTLAs
*  DESC: Function to Pack SztENBX2GTPTLAs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztENBX2GTPTLAs
(
SztENBX2GTPTLAs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztENBX2GTPTLAs(param, mBuf)
SztENBX2GTPTLAs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztENBX2GTPTLAs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztTportLyrAddr, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztENBX2GTPTLAs */



/* 
* FUN : cmPkSzt_ExtnENBX2ExtTLA_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnENBX2ExtTLA_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnENBX2ExtTLA_ExtIEsCls
(
Szt_ExtnENBX2ExtTLA_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnENBX2ExtTLA_ExtIEsCls(param, val, mBuf)
Szt_ExtnENBX2ExtTLA_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnENBX2ExtTLA_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnENBX2ExtTLA_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_ENBX2ExtTLA_ExtIEs
*  DESC: Function to Pack SztProtExtnField_ENBX2ExtTLA_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_ENBX2ExtTLA_ExtIEs
(
SztProtExtnField_ENBX2ExtTLA_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_ENBX2ExtTLA_ExtIEs(param, mBuf)
SztProtExtnField_ENBX2ExtTLA_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_ENBX2ExtTLA_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnENBX2ExtTLA_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_ENBX2ExtTLA_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_ENBX2ExtTLA_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_ENBX2ExtTLA_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_ENBX2ExtTLA_ExtIEs
(
SztProtExtnCont_ENBX2ExtTLA_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_ENBX2ExtTLA_ExtIEs(param, mBuf)
SztProtExtnCont_ENBX2ExtTLA_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_ENBX2ExtTLA_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_ENBX2ExtTLA_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_ENBX2ExtTLA_ExtIEs */



/* 
* FUN : cmPkSztENBX2ExtTLA
*  DESC: Function to Pack SztENBX2ExtTLA structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztENBX2ExtTLA
(
SztENBX2ExtTLA *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztENBX2ExtTLA(param, mBuf)
SztENBX2ExtTLA *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztENBX2ExtTLA) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_ENBX2ExtTLA_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztENBX2GTPTLAs, &param->gTPTLAa, mBuf); 
		CMCHKPK(cmPkSztTportLyrAddr, &param->iPsecTLA, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztENBX2ExtTLA */



/* 
* FUN : cmPkSztENBX2ExtTLAs
*  DESC: Function to Pack SztENBX2ExtTLAs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztENBX2ExtTLAs
(
SztENBX2ExtTLAs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztENBX2ExtTLAs(param, mBuf)
SztENBX2ExtTLAs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztENBX2ExtTLAs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztENBX2ExtTLA, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztENBX2ExtTLAs */



/* 
* FUN : cmPkSzt_ExtnX2TNLConfigInfo_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnX2TNLConfigInfo_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnX2TNLConfigInfo_ExtIEsCls
(
Szt_ExtnX2TNLConfigInfo_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnX2TNLConfigInfo_ExtIEsCls(param, val, mBuf)
Szt_ExtnX2TNLConfigInfo_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnX2TNLConfigInfo_ExtIEsCls) 
	
	switch (val)
	{
		case Sztid_eNBX2ExtendedTportLyrAddres:
			CMCHKPK(cmPkSztENBX2ExtTLAs, &param->u.sztENBX2ExtTLAs, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ExtnX2TNLConfigInfo_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_X2TNLConfigInfo_ExtIEs
*  DESC: Function to Pack SztProtExtnField_X2TNLConfigInfo_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_X2TNLConfigInfo_ExtIEs
(
SztProtExtnField_X2TNLConfigInfo_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_X2TNLConfigInfo_ExtIEs(param, mBuf)
SztProtExtnField_X2TNLConfigInfo_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_X2TNLConfigInfo_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnX2TNLConfigInfo_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_X2TNLConfigInfo_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_X2TNLConfigInfo_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_X2TNLConfigInfo_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_X2TNLConfigInfo_ExtIEs
(
SztProtExtnCont_X2TNLConfigInfo_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_X2TNLConfigInfo_ExtIEs(param, mBuf)
SztProtExtnCont_X2TNLConfigInfo_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_X2TNLConfigInfo_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_X2TNLConfigInfo_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_X2TNLConfigInfo_ExtIEs */



/* 
* FUN : cmPkSztX2TNLConfigInfo
*  DESC: Function to Pack SztX2TNLConfigInfo structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztX2TNLConfigInfo
(
SztX2TNLConfigInfo *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztX2TNLConfigInfo(param, mBuf)
SztX2TNLConfigInfo *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztX2TNLConfigInfo) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_X2TNLConfigInfo_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztENBX2TLAs, &param->eNBX2TportLyrAddres, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztX2TNLConfigInfo */

#define cmPkSztStratumLvl cmPkTknU32 
#define cmPkSztSynchronizationStatus cmPkTknU32


/* 
* FUN : cmPkSzt_ExtnTimeSynchronizationInfo_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnTimeSynchronizationInfo_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnTimeSynchronizationInfo_ExtIEsCls
(
Szt_ExtnTimeSynchronizationInfo_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnTimeSynchronizationInfo_ExtIEsCls(param, val, mBuf)
Szt_ExtnTimeSynchronizationInfo_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnTimeSynchronizationInfo_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnTimeSynchronizationInfo_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_TimeSynchronizationInfo_ExtIEs
*  DESC: Function to Pack SztProtExtnField_TimeSynchronizationInfo_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_TimeSynchronizationInfo_ExtIEs
(
SztProtExtnField_TimeSynchronizationInfo_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_TimeSynchronizationInfo_ExtIEs(param, mBuf)
SztProtExtnField_TimeSynchronizationInfo_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_TimeSynchronizationInfo_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnTimeSynchronizationInfo_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_TimeSynchronizationInfo_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_TimeSynchronizationInfo_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_TimeSynchronizationInfo_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_TimeSynchronizationInfo_ExtIEs
(
SztProtExtnCont_TimeSynchronizationInfo_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_TimeSynchronizationInfo_ExtIEs(param, mBuf)
SztProtExtnCont_TimeSynchronizationInfo_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_TimeSynchronizationInfo_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_TimeSynchronizationInfo_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_TimeSynchronizationInfo_ExtIEs */



/* 
* FUN : cmPkSztTimeSynchronizationInfo
*  DESC: Function to Pack SztTimeSynchronizationInfo structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztTimeSynchronizationInfo
(
SztTimeSynchronizationInfo *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztTimeSynchronizationInfo(param, mBuf)
SztTimeSynchronizationInfo *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztTimeSynchronizationInfo) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_TimeSynchronizationInfo_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztSynchronizationStatus, &param->synchronizationStatus, mBuf); 
		CMCHKPK(cmPkSztStratumLvl, &param->stratumLvl, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztTimeSynchronizationInfo */



/* 
* FUN : cmPkSzt_ExtnSONInformReply_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnSONInformReply_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnSONInformReply_ExtIEsCls
(
Szt_ExtnSONInformReply_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnSONInformReply_ExtIEsCls(param, val, mBuf)
Szt_ExtnSONInformReply_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnSONInformReply_ExtIEsCls) 
	
	switch (val)
	{
		case Sztid_Time_Synchronization_Info:
			CMCHKPK(cmPkSztTimeSynchronizationInfo, &param->u.sztTimeSynchronizationInfo, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ExtnSONInformReply_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_SONInformReply_ExtIEs
*  DESC: Function to Pack SztProtExtnField_SONInformReply_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_SONInformReply_ExtIEs
(
SztProtExtnField_SONInformReply_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_SONInformReply_ExtIEs(param, mBuf)
SztProtExtnField_SONInformReply_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_SONInformReply_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnSONInformReply_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_SONInformReply_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_SONInformReply_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_SONInformReply_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_SONInformReply_ExtIEs
(
SztProtExtnCont_SONInformReply_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_SONInformReply_ExtIEs(param, mBuf)
SztProtExtnCont_SONInformReply_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_SONInformReply_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_SONInformReply_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_SONInformReply_ExtIEs */



/* 
* FUN : cmPkSztSONInformReply
*  DESC: Function to Pack SztSONInformReply structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztSONInformReply
(
SztSONInformReply *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztSONInformReply(param, mBuf)
SztSONInformReply *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztSONInformReply) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_SONInformReply_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztX2TNLConfigInfo, &param->x2TNLConfigInfo, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztSONInformReply */



/* 
* FUN : cmPkSztSONInform
*  DESC: Function to Pack SztSONInform structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztSONInform
(
SztSONInform *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztSONInform(param, mBuf)
SztSONInform *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztSONInform) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case SONINFORM_SONINFORMREPLY :
				CMCHKPK(cmPkSztSONInformReply, &param->val.sONInformReply, mBuf); 
				break;
			case SONINFORM_SONINFORMRQST :
				CMCHKPK(cmPkSztSONInformRqst, &param->val.sONInformRqst, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztSONInform */



/* 
* FUN : cmPkSzt_ExtnTgeteNB_ID_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnTgeteNB_ID_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnTgeteNB_ID_ExtIEsCls
(
Szt_ExtnTgeteNB_ID_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnTgeteNB_ID_ExtIEsCls(param, val, mBuf)
Szt_ExtnTgeteNB_ID_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnTgeteNB_ID_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnTgeteNB_ID_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_TgeteNB_ID_ExtIEs
*  DESC: Function to Pack SztProtExtnField_TgeteNB_ID_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_TgeteNB_ID_ExtIEs
(
SztProtExtnField_TgeteNB_ID_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_TgeteNB_ID_ExtIEs(param, mBuf)
SztProtExtnField_TgeteNB_ID_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_TgeteNB_ID_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnTgeteNB_ID_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_TgeteNB_ID_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_TgeteNB_ID_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_TgeteNB_ID_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_TgeteNB_ID_ExtIEs
(
SztProtExtnCont_TgeteNB_ID_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_TgeteNB_ID_ExtIEs(param, mBuf)
SztProtExtnCont_TgeteNB_ID_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_TgeteNB_ID_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_TgeteNB_ID_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_TgeteNB_ID_ExtIEs */



/* 
* FUN : cmPkSztTgeteNB_ID
*  DESC: Function to Pack SztTgeteNB_ID structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztTgeteNB_ID
(
SztTgeteNB_ID *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztTgeteNB_ID(param, mBuf)
SztTgeteNB_ID *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztTgeteNB_ID) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_TgeteNB_ID_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztTAI, &param->selected_TAI, mBuf); 
		CMCHKPK(cmPkSztGlobal_ENB_ID, &param->global_ENB_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztTgeteNB_ID */



/* 
* FUN : cmPkSzt_ExtnSrceNB_ID_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnSrceNB_ID_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnSrceNB_ID_ExtIEsCls
(
Szt_ExtnSrceNB_ID_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnSrceNB_ID_ExtIEsCls(param, val, mBuf)
Szt_ExtnSrceNB_ID_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnSrceNB_ID_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnSrceNB_ID_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_SrceNB_ID_ExtIEs
*  DESC: Function to Pack SztProtExtnField_SrceNB_ID_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_SrceNB_ID_ExtIEs
(
SztProtExtnField_SrceNB_ID_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_SrceNB_ID_ExtIEs(param, mBuf)
SztProtExtnField_SrceNB_ID_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_SrceNB_ID_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnSrceNB_ID_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_SrceNB_ID_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_SrceNB_ID_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_SrceNB_ID_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_SrceNB_ID_ExtIEs
(
SztProtExtnCont_SrceNB_ID_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_SrceNB_ID_ExtIEs(param, mBuf)
SztProtExtnCont_SrceNB_ID_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_SrceNB_ID_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_SrceNB_ID_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_SrceNB_ID_ExtIEs */



/* 
* FUN : cmPkSztSrceNB_ID
*  DESC: Function to Pack SztSrceNB_ID structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztSrceNB_ID
(
SztSrceNB_ID *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztSrceNB_ID(param, mBuf)
SztSrceNB_ID *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztSrceNB_ID) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_SrceNB_ID_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztTAI, &param->selected_TAI, mBuf); 
		CMCHKPK(cmPkSztGlobal_ENB_ID, &param->global_ENB_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztSrceNB_ID */



/* 
* FUN : cmPkSzt_ExtnSONConfigTfr_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnSONConfigTfr_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnSONConfigTfr_ExtIEsCls
(
Szt_ExtnSONConfigTfr_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnSONConfigTfr_ExtIEsCls(param, val, mBuf)
Szt_ExtnSONConfigTfr_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnSONConfigTfr_ExtIEsCls) 
	
	switch (val)
	{
		case Sztid_x2TNLConfigInfo:
			CMCHKPK(cmPkSztX2TNLConfigInfo, &param->u.sztX2TNLConfigInfo, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ExtnSONConfigTfr_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_SONConfigTfr_ExtIEs
*  DESC: Function to Pack SztProtExtnField_SONConfigTfr_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_SONConfigTfr_ExtIEs
(
SztProtExtnField_SONConfigTfr_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_SONConfigTfr_ExtIEs(param, mBuf)
SztProtExtnField_SONConfigTfr_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_SONConfigTfr_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnSONConfigTfr_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_SONConfigTfr_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_SONConfigTfr_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_SONConfigTfr_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_SONConfigTfr_ExtIEs
(
SztProtExtnCont_SONConfigTfr_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_SONConfigTfr_ExtIEs(param, mBuf)
SztProtExtnCont_SONConfigTfr_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_SONConfigTfr_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_SONConfigTfr_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_SONConfigTfr_ExtIEs */



/* 
* FUN : cmPkSztSONConfigTfr
*  DESC: Function to Pack SztSONConfigTfr structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztSONConfigTfr
(
SztSONConfigTfr *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztSONConfigTfr(param, mBuf)
SztSONConfigTfr *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztSONConfigTfr) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_SONConfigTfr_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztSONInform, &param->sONInform, mBuf); 
		CMCHKPK(cmPkSztSrceNB_ID, &param->sourceeNB_ID, mBuf); 
		CMCHKPK(cmPkSztTgeteNB_ID, &param->targeteNB_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztSONConfigTfr */

#define cmPkSztSrc_ToTget_TprntCont cmPkTknStrOSXL 
#define cmPkSztSrcBSS_ToTgetBSS_TprntCont cmPkTknStrOSXL 
#define cmPkSztSRVCCOperationPossible cmPkTknU32
#define cmPkSztSRVCCHOInd cmPkTknU32
#define cmPkSztSubscriberProfileIDforRFP cmPkTknU32 


/* 
* FUN : cmPkSztUE_HistoryInform
*  DESC: Function to Pack SztUE_HistoryInform structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztUE_HistoryInform
(
SztUE_HistoryInform *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztUE_HistoryInform(param, mBuf)
SztUE_HistoryInform *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztUE_HistoryInform) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztLastVisitedCell_Item, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztUE_HistoryInform */



/* 
* FUN : cmPkSzt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls
(
Szt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls(param, val, mBuf)
Szt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls) 
	
	switch (val)
	{
		case Sztid_MobilityInform:
			CMCHKPK(cmPkSztMobilityInform, &param->u.sztMobilityInform, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs
*  DESC: Function to Pack SztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs
(
SztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs(param, mBuf)
SztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs
(
SztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs(param, mBuf)
SztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs */



/* 
* FUN : cmPkSztSrceNB_ToTgeteNB_TprntCont
*  DESC: Function to Pack SztSrceNB_ToTgeteNB_TprntCont structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztSrceNB_ToTgeteNB_TprntCont
(
SztSrceNB_ToTgeteNB_TprntCont *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztSrceNB_ToTgeteNB_TprntCont(param, mBuf)
SztSrceNB_ToTgeteNB_TprntCont *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztSrceNB_ToTgeteNB_TprntCont) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztUE_HistoryInform, &param->uE_HistoryInform, mBuf); 
		CMCHKPK(cmPkSztSubscriberProfileIDforRFP, &param->subscriberProfileIDforRFP, mBuf); 
		CMCHKPK(cmPkSztEUTRAN_CGI, &param->targetCell_ID, mBuf); 
		CMCHKPK(cmPkSztE_RABInformLst, &param->e_RABInformLst, mBuf); 
		CMCHKPK(cmPkSztRRC_Cont, &param->rRC_Cont, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztSrceNB_ToTgeteNB_TprntCont */

#define cmPkSztSrcRNC_ToTgetRNC_TprntCont cmPkTknStrOSXL 


/* 
* FUN : cmPkSztSrvdPLMNs
*  DESC: Function to Pack SztSrvdPLMNs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztSrvdPLMNs
(
SztSrvdPLMNs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztSrvdPLMNs(param, mBuf)
SztSrvdPLMNs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztSrvdPLMNs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztPLMNidentity, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztSrvdPLMNs */



/* 
* FUN : cmPkSztSrvdGroupIDs
*  DESC: Function to Pack SztSrvdGroupIDs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztSrvdGroupIDs
(
SztSrvdGroupIDs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztSrvdGroupIDs(param, mBuf)
SztSrvdGroupIDs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztSrvdGroupIDs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztMME_Group_ID, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztSrvdGroupIDs */



/* 
* FUN : cmPkSztSrvdMMECs
*  DESC: Function to Pack SztSrvdMMECs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztSrvdMMECs
(
SztSrvdMMECs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztSrvdMMECs(param, mBuf)
SztSrvdMMECs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztSrvdMMECs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztMME_Code, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztSrvdMMECs */



/* 
* FUN : cmPkSzt_ExtnSrvdGUMMEIsItem_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnSrvdGUMMEIsItem_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnSrvdGUMMEIsItem_ExtIEsCls
(
Szt_ExtnSrvdGUMMEIsItem_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnSrvdGUMMEIsItem_ExtIEsCls(param, val, mBuf)
Szt_ExtnSrvdGUMMEIsItem_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnSrvdGUMMEIsItem_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnSrvdGUMMEIsItem_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_SrvdGUMMEIsItem_ExtIEs
*  DESC: Function to Pack SztProtExtnField_SrvdGUMMEIsItem_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_SrvdGUMMEIsItem_ExtIEs
(
SztProtExtnField_SrvdGUMMEIsItem_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_SrvdGUMMEIsItem_ExtIEs(param, mBuf)
SztProtExtnField_SrvdGUMMEIsItem_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_SrvdGUMMEIsItem_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnSrvdGUMMEIsItem_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_SrvdGUMMEIsItem_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_SrvdGUMMEIsItem_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_SrvdGUMMEIsItem_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_SrvdGUMMEIsItem_ExtIEs
(
SztProtExtnCont_SrvdGUMMEIsItem_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_SrvdGUMMEIsItem_ExtIEs(param, mBuf)
SztProtExtnCont_SrvdGUMMEIsItem_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_SrvdGUMMEIsItem_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_SrvdGUMMEIsItem_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_SrvdGUMMEIsItem_ExtIEs */



/* 
* FUN : cmPkSztSrvdGUMMEIsItem
*  DESC: Function to Pack SztSrvdGUMMEIsItem structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztSrvdGUMMEIsItem
(
SztSrvdGUMMEIsItem *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztSrvdGUMMEIsItem(param, mBuf)
SztSrvdGUMMEIsItem *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztSrvdGUMMEIsItem) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_SrvdGUMMEIsItem_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztSrvdMMECs, &param->servedMMECs, mBuf); 
		CMCHKPK(cmPkSztSrvdGroupIDs, &param->servedGroupIDs, mBuf); 
		CMCHKPK(cmPkSztSrvdPLMNs, &param->servedPLMNs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztSrvdGUMMEIsItem */



/* 
* FUN : cmPkSztSrvdGUMMEIs
*  DESC: Function to Pack SztSrvdGUMMEIs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztSrvdGUMMEIs
(
SztSrvdGUMMEIs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztSrvdGUMMEIs(param, mBuf)
SztSrvdGUMMEIs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztSrvdGUMMEIs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztSrvdGUMMEIsItem, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztSrvdGUMMEIs */



/* 
* FUN : cmPkSzt_ExtnSuppTAs_Item_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnSuppTAs_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnSuppTAs_Item_ExtIEsCls
(
Szt_ExtnSuppTAs_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnSuppTAs_Item_ExtIEsCls(param, val, mBuf)
Szt_ExtnSuppTAs_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnSuppTAs_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnSuppTAs_Item_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_SuppTAs_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnField_SuppTAs_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_SuppTAs_Item_ExtIEs
(
SztProtExtnField_SuppTAs_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_SuppTAs_Item_ExtIEs(param, mBuf)
SztProtExtnField_SuppTAs_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_SuppTAs_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnSuppTAs_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_SuppTAs_Item_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_SuppTAs_Item_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_SuppTAs_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_SuppTAs_Item_ExtIEs
(
SztProtExtnCont_SuppTAs_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_SuppTAs_Item_ExtIEs(param, mBuf)
SztProtExtnCont_SuppTAs_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_SuppTAs_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_SuppTAs_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_SuppTAs_Item_ExtIEs */



/* 
* FUN : cmPkSztSuppTAs_Item
*  DESC: Function to Pack SztSuppTAs_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztSuppTAs_Item
(
SztSuppTAs_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztSuppTAs_Item(param, mBuf)
SztSuppTAs_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztSuppTAs_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_SuppTAs_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztBPLMNs, &param->broadcastPLMNs, mBuf); 
		CMCHKPK(cmPkSztTAC, &param->tAC, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztSuppTAs_Item */



/* 
* FUN : cmPkSztSuppTAs
*  DESC: Function to Pack SztSuppTAs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztSuppTAs
(
SztSuppTAs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztSuppTAs(param, mBuf)
SztSuppTAs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztSuppTAs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztSuppTAs_Item, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztSuppTAs */



/* 
* FUN : cmPkSzt_ExtnS_TMSI_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnS_TMSI_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnS_TMSI_ExtIEsCls
(
Szt_ExtnS_TMSI_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnS_TMSI_ExtIEsCls(param, val, mBuf)
Szt_ExtnS_TMSI_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnS_TMSI_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnS_TMSI_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_S_TMSI_ExtIEs
*  DESC: Function to Pack SztProtExtnField_S_TMSI_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_S_TMSI_ExtIEs
(
SztProtExtnField_S_TMSI_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_S_TMSI_ExtIEs(param, mBuf)
SztProtExtnField_S_TMSI_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_S_TMSI_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnS_TMSI_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_S_TMSI_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_S_TMSI_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_S_TMSI_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_S_TMSI_ExtIEs
(
SztProtExtnCont_S_TMSI_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_S_TMSI_ExtIEs(param, mBuf)
SztProtExtnCont_S_TMSI_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_S_TMSI_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_S_TMSI_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_S_TMSI_ExtIEs */



/* 
* FUN : cmPkSztS_TMSI
*  DESC: Function to Pack SztS_TMSI structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztS_TMSI
(
SztS_TMSI *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztS_TMSI(param, mBuf)
SztS_TMSI *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztS_TMSI) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_S_TMSI_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztM_TMSI, &param->m_TMSI, mBuf); 
		CMCHKPK(cmPkSztMME_Code, &param->mMEC, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztS_TMSI */



/* 
* FUN : cmPkSztTAILstforWarning
*  DESC: Function to Pack SztTAILstforWarning structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztTAILstforWarning
(
SztTAILstforWarning *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztTAILstforWarning(param, mBuf)
SztTAILstforWarning *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztTAILstforWarning) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztTAI, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztTAILstforWarning */



/* 
* FUN : cmPkSztTgetID
*  DESC: Function to Pack SztTgetID structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztTgetID
(
SztTgetID *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztTgetID(param, mBuf)
SztTgetID *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztTgetID) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case TGETID_CGI :
				CMCHKPK(cmPkSztCGI, &param->val.cGI, mBuf); 
				break;
			case TGETID_TARGETRNC_ID :
				CMCHKPK(cmPkSztTgetRNC_ID, &param->val.targetRNC_ID, mBuf); 
				break;
			case TGETID_TARGETENB_ID :
				CMCHKPK(cmPkSztTgeteNB_ID, &param->val.targeteNB_ID, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztTgetID */



/* 
* FUN : cmPkSzt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls
(
Szt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls(param, val, mBuf)
Szt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs
*  DESC: Function to Pack SztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs
(
SztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs(param, mBuf)
SztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs
(
SztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs(param, mBuf)
SztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs */



/* 
* FUN : cmPkSztTgeteNB_ToSrceNB_TprntCont
*  DESC: Function to Pack SztTgeteNB_ToSrceNB_TprntCont structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztTgeteNB_ToSrceNB_TprntCont
(
SztTgeteNB_ToSrceNB_TprntCont *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztTgeteNB_ToSrceNB_TprntCont(param, mBuf)
SztTgeteNB_ToSrceNB_TprntCont *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztTgeteNB_ToSrceNB_TprntCont) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztRRC_Cont, &param->rRC_Cont, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztTgeteNB_ToSrceNB_TprntCont */

#define cmPkSztTget_ToSrc_TprntCont cmPkTknStrOSXL 
#define cmPkSztTgetRNC_ToSrcRNC_TprntCont cmPkTknStrOSXL 
#define cmPkSztTgetBSS_ToSrcBSS_TprntCont cmPkTknStrOSXL 
#define cmPkSztTimeToWait cmPkTknU32
#define cmPkSztE_UTRAN_Trace_ID cmPkTknStrOSXL 
#define cmPkSztTraceDepth cmPkTknU32


/* 
* FUN : cmPkSzt_ExtnTraceActvn_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnTraceActvn_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnTraceActvn_ExtIEsCls
(
Szt_ExtnTraceActvn_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnTraceActvn_ExtIEsCls(param, val, mBuf)
Szt_ExtnTraceActvn_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnTraceActvn_ExtIEsCls) 
	
	switch (val)
	{
		case Sztid_MDTConfig:
			CMCHKPK(cmPkSztMDT_Config, &param->u.sztMDT_Config, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ExtnTraceActvn_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_TraceActvn_ExtIEs
*  DESC: Function to Pack SztProtExtnField_TraceActvn_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_TraceActvn_ExtIEs
(
SztProtExtnField_TraceActvn_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_TraceActvn_ExtIEs(param, mBuf)
SztProtExtnField_TraceActvn_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_TraceActvn_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnTraceActvn_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_TraceActvn_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_TraceActvn_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_TraceActvn_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_TraceActvn_ExtIEs
(
SztProtExtnCont_TraceActvn_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_TraceActvn_ExtIEs(param, mBuf)
SztProtExtnCont_TraceActvn_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_TraceActvn_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_TraceActvn_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_TraceActvn_ExtIEs */



/* 
* FUN : cmPkSztTraceActvn
*  DESC: Function to Pack SztTraceActvn structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztTraceActvn
(
SztTraceActvn *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztTraceActvn(param, mBuf)
SztTraceActvn *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztTraceActvn) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_TraceActvn_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztTportLyrAddr, &param->traceCollectionEntityIPAddr, mBuf); 
		CMCHKPK(cmPkSztTraceDepth, &param->traceDepth, mBuf); 
		CMCHKPK(cmPkSztIntfsToTrace, &param->interfacesToTrace, mBuf); 
		CMCHKPK(cmPkSztE_UTRAN_Trace_ID, &param->e_UTRAN_Trace_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztTraceActvn */

#define cmPkSztTrafficLoadReductionInd cmPkTknU32 


/* 
* FUN : cmPkSzt_ExtnTunnel_Inform_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnTunnel_Inform_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnTunnel_Inform_ExtIEsCls
(
Szt_ExtnTunnel_Inform_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnTunnel_Inform_ExtIEsCls(param, val, mBuf)
Szt_ExtnTunnel_Inform_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnTunnel_Inform_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnTunnel_Inform_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_Tunnel_Inform_ExtIEs
*  DESC: Function to Pack SztProtExtnField_Tunnel_Inform_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_Tunnel_Inform_ExtIEs
(
SztProtExtnField_Tunnel_Inform_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_Tunnel_Inform_ExtIEs(param, mBuf)
SztProtExtnField_Tunnel_Inform_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_Tunnel_Inform_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnTunnel_Inform_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_Tunnel_Inform_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_Tunnel_Inform_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_Tunnel_Inform_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_Tunnel_Inform_ExtIEs
(
SztProtExtnCont_Tunnel_Inform_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_Tunnel_Inform_ExtIEs(param, mBuf)
SztProtExtnCont_Tunnel_Inform_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_Tunnel_Inform_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_Tunnel_Inform_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_Tunnel_Inform_ExtIEs */



/* 
* FUN : cmPkSztTunnelInform
*  DESC: Function to Pack SztTunnelInform structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztTunnelInform
(
SztTunnelInform *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztTunnelInform(param, mBuf)
SztTunnelInform *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztTunnelInform) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_Tunnel_Inform_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztPort_Number, &param->uDP_Port_Number, mBuf); 
		CMCHKPK(cmPkSztTportLyrAddr, &param->transportLyrAddr, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztTunnelInform */



/* 
* FUN : cmPkSzt_ExtnUEAgg_MaxBitrates_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnUEAgg_MaxBitrates_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnUEAgg_MaxBitrates_ExtIEsCls
(
Szt_ExtnUEAgg_MaxBitrates_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnUEAgg_MaxBitrates_ExtIEsCls(param, val, mBuf)
Szt_ExtnUEAgg_MaxBitrates_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnUEAgg_MaxBitrates_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnUEAgg_MaxBitrates_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_UEAgg_MaxBitrates_ExtIEs
*  DESC: Function to Pack SztProtExtnField_UEAgg_MaxBitrates_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_UEAgg_MaxBitrates_ExtIEs
(
SztProtExtnField_UEAgg_MaxBitrates_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_UEAgg_MaxBitrates_ExtIEs(param, mBuf)
SztProtExtnField_UEAgg_MaxBitrates_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_UEAgg_MaxBitrates_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnUEAgg_MaxBitrates_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_UEAgg_MaxBitrates_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_UEAgg_MaxBitrates_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_UEAgg_MaxBitrates_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_UEAgg_MaxBitrates_ExtIEs
(
SztProtExtnCont_UEAgg_MaxBitrates_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_UEAgg_MaxBitrates_ExtIEs(param, mBuf)
SztProtExtnCont_UEAgg_MaxBitrates_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_UEAgg_MaxBitrates_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_UEAgg_MaxBitrates_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_UEAgg_MaxBitrates_ExtIEs */



/* 
* FUN : cmPkSztUEAggMaxBitrate
*  DESC: Function to Pack SztUEAggMaxBitrate structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztUEAggMaxBitrate
(
SztUEAggMaxBitrate *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztUEAggMaxBitrate(param, mBuf)
SztUEAggMaxBitrate *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztUEAggMaxBitrate) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_UEAgg_MaxBitrates_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztBitRate, &param->uEaggregateMaxBitRateUL, mBuf); 
		CMCHKPK(cmPkSztBitRate, &param->uEaggregateMaxBitRateDL, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztUEAggMaxBitrate */



/* 
* FUN : cmPkSzt_ExtnUE_S1AP_ID_pair_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnUE_S1AP_ID_pair_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnUE_S1AP_ID_pair_ExtIEsCls
(
Szt_ExtnUE_S1AP_ID_pair_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnUE_S1AP_ID_pair_ExtIEsCls(param, val, mBuf)
Szt_ExtnUE_S1AP_ID_pair_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnUE_S1AP_ID_pair_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnUE_S1AP_ID_pair_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_UE_S1AP_ID_pair_ExtIEs
*  DESC: Function to Pack SztProtExtnField_UE_S1AP_ID_pair_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_UE_S1AP_ID_pair_ExtIEs
(
SztProtExtnField_UE_S1AP_ID_pair_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_UE_S1AP_ID_pair_ExtIEs(param, mBuf)
SztProtExtnField_UE_S1AP_ID_pair_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_UE_S1AP_ID_pair_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnUE_S1AP_ID_pair_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_UE_S1AP_ID_pair_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_UE_S1AP_ID_pair_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_UE_S1AP_ID_pair_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_UE_S1AP_ID_pair_ExtIEs
(
SztProtExtnCont_UE_S1AP_ID_pair_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_UE_S1AP_ID_pair_ExtIEs(param, mBuf)
SztProtExtnCont_UE_S1AP_ID_pair_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_UE_S1AP_ID_pair_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_UE_S1AP_ID_pair_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_UE_S1AP_ID_pair_ExtIEs */



/* 
* FUN : cmPkSztUE_S1AP_ID_pair
*  DESC: Function to Pack SztUE_S1AP_ID_pair structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztUE_S1AP_ID_pair
(
SztUE_S1AP_ID_pair *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztUE_S1AP_ID_pair(param, mBuf)
SztUE_S1AP_ID_pair *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztUE_S1AP_ID_pair) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_UE_S1AP_ID_pair_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->eNB_UE_S1AP_ID, mBuf); 
		CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->mME_UE_S1AP_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztUE_S1AP_ID_pair */



/* 
* FUN : cmPkSztUE_S1AP_IDs
*  DESC: Function to Pack SztUE_S1AP_IDs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztUE_S1AP_IDs
(
SztUE_S1AP_IDs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztUE_S1AP_IDs(param, mBuf)
SztUE_S1AP_IDs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztUE_S1AP_IDs) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case UE_S1AP_IDS_MME_UE_S1AP_ID :
				CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->val.mME_UE_S1AP_ID, mBuf); 
				break;
			case UE_S1AP_IDS_UE_S1AP_ID_PAIR :
				CMCHKPK(cmPkSztUE_S1AP_ID_pair, &param->val.uE_S1AP_ID_pair, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztUE_S1AP_IDs */



/* 
* FUN : cmPkSzt_ExtnUE_assocLogS1_ConItemExtIEsCls
*  DESC: Function to Pack Szt_ExtnUE_assocLogS1_ConItemExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnUE_assocLogS1_ConItemExtIEsCls
(
Szt_ExtnUE_assocLogS1_ConItemExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnUE_assocLogS1_ConItemExtIEsCls(param, val, mBuf)
Szt_ExtnUE_assocLogS1_ConItemExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnUE_assocLogS1_ConItemExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnUE_assocLogS1_ConItemExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_UE_assocLogS1_ConItemExtIEs
*  DESC: Function to Pack SztProtExtnField_UE_assocLogS1_ConItemExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_UE_assocLogS1_ConItemExtIEs
(
SztProtExtnField_UE_assocLogS1_ConItemExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_UE_assocLogS1_ConItemExtIEs(param, mBuf)
SztProtExtnField_UE_assocLogS1_ConItemExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_UE_assocLogS1_ConItemExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnUE_assocLogS1_ConItemExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_UE_assocLogS1_ConItemExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_UE_assocLogS1_ConItemExtIEs
*  DESC: Function to Pack SztProtExtnCont_UE_assocLogS1_ConItemExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_UE_assocLogS1_ConItemExtIEs
(
SztProtExtnCont_UE_assocLogS1_ConItemExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_UE_assocLogS1_ConItemExtIEs(param, mBuf)
SztProtExtnCont_UE_assocLogS1_ConItemExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_UE_assocLogS1_ConItemExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_UE_assocLogS1_ConItemExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_UE_assocLogS1_ConItemExtIEs */



/* 
* FUN : cmPkSztUE_assocLogS1_ConItem
*  DESC: Function to Pack SztUE_assocLogS1_ConItem structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztUE_assocLogS1_ConItem
(
SztUE_assocLogS1_ConItem *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztUE_assocLogS1_ConItem(param, mBuf)
SztUE_assocLogS1_ConItem *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztUE_assocLogS1_ConItem) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_UE_assocLogS1_ConItemExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->eNB_UE_S1AP_ID, mBuf); 
		CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->mME_UE_S1AP_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztUE_assocLogS1_ConItem */

#define cmPkSztUEIdentityIdxValue cmPkTknBStr32 


/* 
* FUN : cmPkSztUEPagID
*  DESC: Function to Pack SztUEPagID structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztUEPagID
(
SztUEPagID *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztUEPagID(param, mBuf)
SztUEPagID *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztUEPagID) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case UEPAGID_IMSI :
				CMCHKPK(cmPkSztIMSI, &param->val.iMSI, mBuf); 
				break;
			case UEPAGID_S_TMSI :
				CMCHKPK(cmPkSztS_TMSI, &param->val.s_TMSI, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztUEPagID */

#define cmPkSztUERadioCapblty cmPkTknStrOSXL 


/* 
* FUN : cmPkSzt_ExtnUESecurCapabilities_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnUESecurCapabilities_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnUESecurCapabilities_ExtIEsCls
(
Szt_ExtnUESecurCapabilities_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnUESecurCapabilities_ExtIEsCls(param, val, mBuf)
Szt_ExtnUESecurCapabilities_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnUESecurCapabilities_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnUESecurCapabilities_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_UESecurCapabilities_ExtIEs
*  DESC: Function to Pack SztProtExtnField_UESecurCapabilities_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_UESecurCapabilities_ExtIEs
(
SztProtExtnField_UESecurCapabilities_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_UESecurCapabilities_ExtIEs(param, mBuf)
SztProtExtnField_UESecurCapabilities_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_UESecurCapabilities_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnUESecurCapabilities_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_UESecurCapabilities_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_UESecurCapabilities_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_UESecurCapabilities_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_UESecurCapabilities_ExtIEs
(
SztProtExtnCont_UESecurCapabilities_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_UESecurCapabilities_ExtIEs(param, mBuf)
SztProtExtnCont_UESecurCapabilities_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_UESecurCapabilities_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_UESecurCapabilities_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_UESecurCapabilities_ExtIEs */



/* 
* FUN : cmPkSztUESecurCapabilities
*  DESC: Function to Pack SztUESecurCapabilities structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztUESecurCapabilities
(
SztUESecurCapabilities *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztUESecurCapabilities(param, mBuf)
SztUESecurCapabilities *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztUESecurCapabilities) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_UESecurCapabilities_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztIntegrityProtectionAlgorithms, &param->integrityProtectionAlgorithms, mBuf); 
		CMCHKPK(cmPkSztEncryptionAlgorithms, &param->encryptionAlgorithms, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztUESecurCapabilities */

#define cmPkSztVoiceSupportMatchIndicator cmPkTknU32


/* 
* FUN : cmPkSztWarningAreaLst
*  DESC: Function to Pack SztWarningAreaLst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztWarningAreaLst
(
SztWarningAreaLst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztWarningAreaLst(param, mBuf)
SztWarningAreaLst *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztWarningAreaLst) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case WARNINGAREALST_EMERGENCYAREAIDLST :
				CMCHKPK(cmPkSztEmergencyAreaIDLst, &param->val.emergencyAreaIDLst, mBuf); 
				break;
			case WARNINGAREALST_TRACKINGAREALSTFORWARNING :
				CMCHKPK(cmPkSztTAILstforWarning, &param->val.trackingAreaLstforWarning, mBuf); 
				break;
			case WARNINGAREALST_CELLIDLST :
				CMCHKPK(cmPkSztECGILst, &param->val.cellIDLst, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztWarningAreaLst */

#define cmPkSztWarningTyp cmPkTknStr4 
#define cmPkSztWarningSecurInfo cmPkTknStrOSXL 
#define cmPkSztWarningMsgContents cmPkTknStrOSXL 


/* 
* FUN : cmPkSzt_ValueHovrReqdIEsCls
*  DESC: Function to Pack Szt_ValueHovrReqdIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueHovrReqdIEsCls
(
Szt_ValueHovrReqdIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueHovrReqdIEsCls(param, val, mBuf)
Szt_ValueHovrReqdIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueHovrReqdIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_HovrTyp:
			CMCHKPK(cmPkSztHovrTyp, &param->u.sztHovrTyp, mBuf);
			break;
		case Sztid_Cause:
			CMCHKPK(cmPkSztCause, &param->u.sztCause, mBuf);
			break;
		case Sztid_TgetID:
			CMCHKPK(cmPkSztTgetID, &param->u.sztTgetID, mBuf);
			break;
		case Sztid_Direct_Fwding_Path_Avlblty:
			CMCHKPK(cmPkSztDirect_Fwding_Path_Avlblty, &param->u.sztDirect_Fwding_Path_Avlblty, mBuf);
			break;
		case Sztid_SRVCCHOInd:
			CMCHKPK(cmPkSztSRVCCHOInd, &param->u.sztSRVCCHOInd, mBuf);
			break;
		case Sztid_Src_ToTget_TprntCont:
			CMCHKPK(cmPkSztSrc_ToTget_TprntCont, &param->u.sztid_Src_ToTget_TprntCont, mBuf);
			break;
		case Sztid_Src_ToTget_TprntCont_Secondary:
			CMCHKPK(cmPkSztSrc_ToTget_TprntCont, &param->u.sztid_Src_ToTget_TprntCont_Secondary, mBuf);
			break;
		case Sztid_MSClassmark2:
			CMCHKPK(cmPkSztMSClassmark2, &param->u.sztMSClassmark2, mBuf);
			break;
		case Sztid_MSClassmark3:
			CMCHKPK(cmPkSztMSClassmark3, &param->u.sztMSClassmark3, mBuf);
			break;
		case Sztid_CSG_Id:
			CMCHKPK(cmPkSztCSG_Id, &param->u.sztCSG_Id, mBuf);
			break;
		case Sztid_CellAccessMode:
			CMCHKPK(cmPkSztCellAccessMode, &param->u.sztCellAccessMode, mBuf);
			break;
		case Sztid_PS_ServiceNotAvailable:
			CMCHKPK(cmPkSztPS_ServiceNotAvailable, &param->u.sztPS_ServiceNotAvailable, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueHovrReqdIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_HovrReqdIEs
*  DESC: Function to Pack SztProtIE_Field_HovrReqdIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_HovrReqdIEs
(
SztProtIE_Field_HovrReqdIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_HovrReqdIEs(param, mBuf)
SztProtIE_Field_HovrReqdIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_HovrReqdIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueHovrReqdIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_HovrReqdIEs */



/* 
* FUN : cmPkSztProtIE_Cont_HovrReqdIEs
*  DESC: Function to Pack SztProtIE_Cont_HovrReqdIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_HovrReqdIEs
(
SztProtIE_Cont_HovrReqdIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_HovrReqdIEs(param, mBuf)
SztProtIE_Cont_HovrReqdIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_HovrReqdIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_HovrReqdIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_HovrReqdIEs */



/* 
* FUN : cmPkSztHovrReqd
*  DESC: Function to Pack SztHovrReqd structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztHovrReqd
(
SztHovrReqd *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztHovrReqd(param, mBuf)
SztHovrReqd *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztHovrReqd) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_HovrReqdIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztHovrReqd */



/* 
* FUN : cmPkSzt_ExtnE_RABDataFwdingItem_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnE_RABDataFwdingItem_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnE_RABDataFwdingItem_ExtIEsCls
(
Szt_ExtnE_RABDataFwdingItem_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnE_RABDataFwdingItem_ExtIEsCls(param, val, mBuf)
Szt_ExtnE_RABDataFwdingItem_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnE_RABDataFwdingItem_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnE_RABDataFwdingItem_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_E_RABDataFwdingItem_ExtIEs
*  DESC: Function to Pack SztProtExtnField_E_RABDataFwdingItem_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_E_RABDataFwdingItem_ExtIEs
(
SztProtExtnField_E_RABDataFwdingItem_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_E_RABDataFwdingItem_ExtIEs(param, mBuf)
SztProtExtnField_E_RABDataFwdingItem_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_E_RABDataFwdingItem_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnE_RABDataFwdingItem_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_E_RABDataFwdingItem_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_E_RABDataFwdingItem_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_E_RABDataFwdingItem_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_E_RABDataFwdingItem_ExtIEs
(
SztProtExtnCont_E_RABDataFwdingItem_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_E_RABDataFwdingItem_ExtIEs(param, mBuf)
SztProtExtnCont_E_RABDataFwdingItem_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_E_RABDataFwdingItem_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_E_RABDataFwdingItem_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_E_RABDataFwdingItem_ExtIEs */



/* 
* FUN : cmPkSztE_RABDataFwdingItem
*  DESC: Function to Pack SztE_RABDataFwdingItem structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABDataFwdingItem
(
SztE_RABDataFwdingItem *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABDataFwdingItem(param, mBuf)
SztE_RABDataFwdingItem *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztE_RABDataFwdingItem) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_E_RABDataFwdingItem_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztGTP_TEID, &param->uL_GTP_TEID, mBuf); 
		CMCHKPK(cmPkSztTportLyrAddr, &param->uL_TportLyrAddr, mBuf); 
		CMCHKPK(cmPkSztGTP_TEID, &param->dL_gTP_TEID, mBuf); 
		CMCHKPK(cmPkSztTportLyrAddr, &param->dL_transportLyrAddr, mBuf); 
		CMCHKPK(cmPkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABDataFwdingItem */



/* 
* FUN : cmPkSzt_ValueE_RABDataFwdingItemIEsCls
*  DESC: Function to Pack Szt_ValueE_RABDataFwdingItemIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueE_RABDataFwdingItemIEsCls
(
Szt_ValueE_RABDataFwdingItemIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueE_RABDataFwdingItemIEsCls(param, val, mBuf)
Szt_ValueE_RABDataFwdingItemIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueE_RABDataFwdingItemIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABDataFwdingItem:
			CMCHKPK(cmPkSztE_RABDataFwdingItem, &param->u.sztE_RABDataFwdingItem, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueE_RABDataFwdingItemIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_E_RABDataFwdingItemIEs
*  DESC: Function to Pack SztProtIE_Field_E_RABDataFwdingItemIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_E_RABDataFwdingItemIEs
(
SztProtIE_Field_E_RABDataFwdingItemIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_E_RABDataFwdingItemIEs(param, mBuf)
SztProtIE_Field_E_RABDataFwdingItemIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_E_RABDataFwdingItemIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueE_RABDataFwdingItemIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_E_RABDataFwdingItemIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmPkSztProtIE_SingleCont_E_RABDataFwdingItemIEs cmPkSztProtIE_Field_E_RABDataFwdingItemIEs


/* 
* FUN : cmPkSztProtIE_ContLst_E_RABDataFwdingItemIEs
*  DESC: Function to Pack SztProtIE_ContLst_E_RABDataFwdingItemIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_ContLst_E_RABDataFwdingItemIEs
(
SztProtIE_ContLst_E_RABDataFwdingItemIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_ContLst_E_RABDataFwdingItemIEs(param, mBuf)
SztProtIE_ContLst_E_RABDataFwdingItemIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_ContLst_E_RABDataFwdingItemIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_SingleCont_E_RABDataFwdingItemIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_ContLst_E_RABDataFwdingItemIEs */

/* Element ------------- E-RAB-IE-ContainerList ------------ */
#define cmPkSztE_RAB_IE_ContLst_E_RABDataFwdingItemIEs cmPkSztProtIE_ContLst_E_RABDataFwdingItemIEs
/* Element ------------- E-RABSubjecttoDataForwardingList ------------ */
#define cmPkSztE_RABSubjtoDataFwdingLst cmPkSztE_RAB_IE_ContLst_E_RABDataFwdingItemIEs


/* 
* FUN : cmPkSzt_ValueHovrCmmdIEsCls
*  DESC: Function to Pack Szt_ValueHovrCmmdIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueHovrCmmdIEsCls
(
Szt_ValueHovrCmmdIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueHovrCmmdIEsCls(param, val, mBuf)
Szt_ValueHovrCmmdIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueHovrCmmdIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_HovrTyp:
			CMCHKPK(cmPkSztHovrTyp, &param->u.sztHovrTyp, mBuf);
			break;
		case Sztid_NASSecurParamsfromE_UTRAN:
			CMCHKPK(cmPkSztNASSecurParamsfromE_UTRAN, &param->u.sztNASSecurParamsfromE_UTRAN, mBuf);
			break;
		case Sztid_E_RABSubjtoDataFwdingLst:
			CMCHKPK(cmPkSztE_RABSubjtoDataFwdingLst, &param->u.sztE_RABSubjtoDataFwdingLst, mBuf);
			break;
		case Sztid_E_RABtoRlsLstHOCmd:
			CMCHKPK(cmPkSztE_RABLst, &param->u.sztE_RABLst, mBuf);
			break;
		case Sztid_Tget_ToSrc_TprntCont:
			CMCHKPK(cmPkSztTget_ToSrc_TprntCont, &param->u.sztid_Tget_ToSrc_TprntCont, mBuf);
			break;
		case Sztid_Tget_ToSrc_TprntCont_Secondary:
			CMCHKPK(cmPkSztTget_ToSrc_TprntCont, &param->u.sztid_Tget_ToSrc_TprntCont_Secondary, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKPK(cmPkSztCriticalityDiag, &param->u.sztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueHovrCmmdIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_HovrCmmdIEs
*  DESC: Function to Pack SztProtIE_Field_HovrCmmdIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_HovrCmmdIEs
(
SztProtIE_Field_HovrCmmdIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_HovrCmmdIEs(param, mBuf)
SztProtIE_Field_HovrCmmdIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_HovrCmmdIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueHovrCmmdIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_HovrCmmdIEs */



/* 
* FUN : cmPkSztProtIE_Cont_HovrCmmdIEs
*  DESC: Function to Pack SztProtIE_Cont_HovrCmmdIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_HovrCmmdIEs
(
SztProtIE_Cont_HovrCmmdIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_HovrCmmdIEs(param, mBuf)
SztProtIE_Cont_HovrCmmdIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_HovrCmmdIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_HovrCmmdIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_HovrCmmdIEs */



/* 
* FUN : cmPkSztHovrCmmd
*  DESC: Function to Pack SztHovrCmmd structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztHovrCmmd
(
SztHovrCmmd *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztHovrCmmd(param, mBuf)
SztHovrCmmd *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztHovrCmmd) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_HovrCmmdIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztHovrCmmd */



/* 
* FUN : cmPkSzt_ValueHovrPrepFailIEsCls
*  DESC: Function to Pack Szt_ValueHovrPrepFailIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueHovrPrepFailIEsCls
(
Szt_ValueHovrPrepFailIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueHovrPrepFailIEsCls(param, val, mBuf)
Szt_ValueHovrPrepFailIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueHovrPrepFailIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_Cause:
			CMCHKPK(cmPkSztCause, &param->u.sztCause, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKPK(cmPkSztCriticalityDiag, &param->u.sztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueHovrPrepFailIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_HovrPrepFailIEs
*  DESC: Function to Pack SztProtIE_Field_HovrPrepFailIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_HovrPrepFailIEs
(
SztProtIE_Field_HovrPrepFailIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_HovrPrepFailIEs(param, mBuf)
SztProtIE_Field_HovrPrepFailIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_HovrPrepFailIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueHovrPrepFailIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_HovrPrepFailIEs */



/* 
* FUN : cmPkSztProtIE_Cont_HovrPrepFailIEs
*  DESC: Function to Pack SztProtIE_Cont_HovrPrepFailIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_HovrPrepFailIEs
(
SztProtIE_Cont_HovrPrepFailIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_HovrPrepFailIEs(param, mBuf)
SztProtIE_Cont_HovrPrepFailIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_HovrPrepFailIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_HovrPrepFailIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_HovrPrepFailIEs */



/* 
* FUN : cmPkSztHovrPrepFail
*  DESC: Function to Pack SztHovrPrepFail structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztHovrPrepFail
(
SztHovrPrepFail *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztHovrPrepFail(param, mBuf)
SztHovrPrepFail *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztHovrPrepFail) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_HovrPrepFailIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztHovrPrepFail */



/* 
* FUN : cmPkSzt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls
(
Szt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls(param, val, mBuf)
Szt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls) 
	
	switch (val)
	{
		case Sztid_Data_Fwding_Not_Possible:
			CMCHKPK(cmPkSztData_Fwding_Not_Possible, &param->u.sztData_Fwding_Not_Possible, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs
*  DESC: Function to Pack SztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs
(
SztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs(param, mBuf)
SztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs
(
SztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs(param, mBuf)
SztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs */



/* 
* FUN : cmPkSztE_RABToBeSetupItemHOReq
*  DESC: Function to Pack SztE_RABToBeSetupItemHOReq structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABToBeSetupItemHOReq
(
SztE_RABToBeSetupItemHOReq *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABToBeSetupItemHOReq(param, mBuf)
SztE_RABToBeSetupItemHOReq *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztE_RABToBeSetupItemHOReq) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztE_RABLvlQoSParams, &param->e_RABlevelQosParams, mBuf); 
		CMCHKPK(cmPkSztGTP_TEID, &param->gTP_TEID, mBuf); 
		CMCHKPK(cmPkSztTportLyrAddr, &param->transportLyrAddr, mBuf); 
		CMCHKPK(cmPkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABToBeSetupItemHOReq */



/* 
* FUN : cmPkSzt_ValueE_RABToBeSetupItemHOReqIEsCls
*  DESC: Function to Pack Szt_ValueE_RABToBeSetupItemHOReqIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueE_RABToBeSetupItemHOReqIEsCls
(
Szt_ValueE_RABToBeSetupItemHOReqIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueE_RABToBeSetupItemHOReqIEsCls(param, val, mBuf)
Szt_ValueE_RABToBeSetupItemHOReqIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueE_RABToBeSetupItemHOReqIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABToBeSetupItemHOReq:
			CMCHKPK(cmPkSztE_RABToBeSetupItemHOReq, &param->u.sztE_RABToBeSetupItemHOReq, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueE_RABToBeSetupItemHOReqIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_E_RABToBeSetupItemHOReqIEs
*  DESC: Function to Pack SztProtIE_Field_E_RABToBeSetupItemHOReqIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_E_RABToBeSetupItemHOReqIEs
(
SztProtIE_Field_E_RABToBeSetupItemHOReqIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_E_RABToBeSetupItemHOReqIEs(param, mBuf)
SztProtIE_Field_E_RABToBeSetupItemHOReqIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_E_RABToBeSetupItemHOReqIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueE_RABToBeSetupItemHOReqIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_E_RABToBeSetupItemHOReqIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmPkSztProtIE_SingleCont_E_RABToBeSetupItemHOReqIEs cmPkSztProtIE_Field_E_RABToBeSetupItemHOReqIEs


/* 
* FUN : cmPkSztProtIE_ContLst_E_RABToBeSetupItemHOReqIEs
*  DESC: Function to Pack SztProtIE_ContLst_E_RABToBeSetupItemHOReqIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_ContLst_E_RABToBeSetupItemHOReqIEs
(
SztProtIE_ContLst_E_RABToBeSetupItemHOReqIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_ContLst_E_RABToBeSetupItemHOReqIEs(param, mBuf)
SztProtIE_ContLst_E_RABToBeSetupItemHOReqIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_ContLst_E_RABToBeSetupItemHOReqIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_SingleCont_E_RABToBeSetupItemHOReqIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_ContLst_E_RABToBeSetupItemHOReqIEs */

/* Element ------------- E-RAB-IE-ContainerList ------------ */
#define cmPkSztE_RAB_IE_ContLst_E_RABToBeSetupItemHOReqIEs cmPkSztProtIE_ContLst_E_RABToBeSetupItemHOReqIEs
/* Element ------------- E-RABToBeSetupListHOReq ------------ */
#define cmPkSztE_RABToBeSetupLstHOReq cmPkSztE_RAB_IE_ContLst_E_RABToBeSetupItemHOReqIEs


/* 
* FUN : cmPkSzt_ValueHovrRqstIEsCls
*  DESC: Function to Pack Szt_ValueHovrRqstIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueHovrRqstIEsCls
(
Szt_ValueHovrRqstIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueHovrRqstIEsCls(param, val, mBuf)
Szt_ValueHovrRqstIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueHovrRqstIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztid_MME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_HovrTyp:
			CMCHKPK(cmPkSztHovrTyp, &param->u.sztHovrTyp, mBuf);
			break;
		case Sztid_Cause:
			CMCHKPK(cmPkSztCause, &param->u.sztCause, mBuf);
			break;
		case Sztid_uEaggregateMaxBitrate:
			CMCHKPK(cmPkSztUEAggMaxBitrate, &param->u.sztUEAggMaxBitrate, mBuf);
			break;
		case Sztid_E_RABToBeSetupLstHOReq:
			CMCHKPK(cmPkSztE_RABToBeSetupLstHOReq, &param->u.sztE_RABToBeSetupLstHOReq, mBuf);
			break;
		case Sztid_Src_ToTget_TprntCont:
			CMCHKPK(cmPkSztSrc_ToTget_TprntCont, &param->u.sztSrc_ToTget_TprntCont, mBuf);
			break;
		case Sztid_UESecurCapabilities:
			CMCHKPK(cmPkSztUESecurCapabilities, &param->u.sztUESecurCapabilities, mBuf);
			break;
		case Sztid_HovrRestrnLst:
			CMCHKPK(cmPkSztHovrRestrnLst, &param->u.sztHovrRestrnLst, mBuf);
			break;
		case Sztid_TraceActvn:
			CMCHKPK(cmPkSztTraceActvn, &param->u.sztTraceActvn, mBuf);
			break;
		case Sztid_RqstTyp:
			CMCHKPK(cmPkSztRqstTyp, &param->u.sztRqstTyp, mBuf);
			break;
		case Sztid_SRVCCOperationPossible:
			CMCHKPK(cmPkSztSRVCCOperationPossible, &param->u.sztSRVCCOperationPossible, mBuf);
			break;
		case Sztid_SecurCntxt:
			CMCHKPK(cmPkSztSecurCntxt, &param->u.sztSecurCntxt, mBuf);
			break;
		case Sztid_NASSecurParamstoE_UTRAN:
			CMCHKPK(cmPkSztNASSecurParamstoE_UTRAN, &param->u.sztNASSecurParamstoE_UTRAN, mBuf);
			break;
		case Sztid_CSG_Id:
			CMCHKPK(cmPkSztCSG_Id, &param->u.sztCSG_Id, mBuf);
			break;
		case Sztid_CSGMembershipStatus:
			CMCHKPK(cmPkSztCSGMembershipStatus, &param->u.sztCSGMembershipStatus, mBuf);
			break;
		case Sztid_GUMMEI_ID:
			CMCHKPK(cmPkSztGUMMEI, &param->u.sztGUMMEI, mBuf);
			break;
		case Sztid_MME_UE_S1AP_ID_2:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztid_MME_UE_S1AP_ID_2, mBuf);
			break;
		case Sztid_ManagementBasedMDTAllowed:
			CMCHKPK(cmPkSztManagementBasedMDTAllowed, &param->u.sztManagementBasedMDTAllowed, mBuf);
			break;
		case Sztid_ManagementBasedMDTPLMNLst:
			CMCHKPK(cmPkSztMDTPLMNLst, &param->u.sztMDTPLMNLst, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueHovrRqstIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_HovrRqstIEs
*  DESC: Function to Pack SztProtIE_Field_HovrRqstIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_HovrRqstIEs
(
SztProtIE_Field_HovrRqstIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_HovrRqstIEs(param, mBuf)
SztProtIE_Field_HovrRqstIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_HovrRqstIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueHovrRqstIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_HovrRqstIEs */



/* 
* FUN : cmPkSztProtIE_Cont_HovrRqstIEs
*  DESC: Function to Pack SztProtIE_Cont_HovrRqstIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_HovrRqstIEs
(
SztProtIE_Cont_HovrRqstIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_HovrRqstIEs(param, mBuf)
SztProtIE_Cont_HovrRqstIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_HovrRqstIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_HovrRqstIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_HovrRqstIEs */



/* 
* FUN : cmPkSztHovrRqst
*  DESC: Function to Pack SztHovrRqst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztHovrRqst
(
SztHovrRqst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztHovrRqst(param, mBuf)
SztHovrRqst *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztHovrRqst) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_HovrRqstIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztHovrRqst */



/* 
* FUN : cmPkSzt_ExtnE_RABAdmtdItem_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnE_RABAdmtdItem_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnE_RABAdmtdItem_ExtIEsCls
(
Szt_ExtnE_RABAdmtdItem_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnE_RABAdmtdItem_ExtIEsCls(param, val, mBuf)
Szt_ExtnE_RABAdmtdItem_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnE_RABAdmtdItem_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnE_RABAdmtdItem_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_E_RABAdmtdItem_ExtIEs
*  DESC: Function to Pack SztProtExtnField_E_RABAdmtdItem_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_E_RABAdmtdItem_ExtIEs
(
SztProtExtnField_E_RABAdmtdItem_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_E_RABAdmtdItem_ExtIEs(param, mBuf)
SztProtExtnField_E_RABAdmtdItem_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_E_RABAdmtdItem_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnE_RABAdmtdItem_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_E_RABAdmtdItem_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_E_RABAdmtdItem_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_E_RABAdmtdItem_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_E_RABAdmtdItem_ExtIEs
(
SztProtExtnCont_E_RABAdmtdItem_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_E_RABAdmtdItem_ExtIEs(param, mBuf)
SztProtExtnCont_E_RABAdmtdItem_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_E_RABAdmtdItem_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_E_RABAdmtdItem_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_E_RABAdmtdItem_ExtIEs */



/* 
* FUN : cmPkSztE_RABAdmtdItem
*  DESC: Function to Pack SztE_RABAdmtdItem structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABAdmtdItem
(
SztE_RABAdmtdItem *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABAdmtdItem(param, mBuf)
SztE_RABAdmtdItem *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztE_RABAdmtdItem) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_E_RABAdmtdItem_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztGTP_TEID, &param->uL_GTP_TEID, mBuf); 
		CMCHKPK(cmPkSztTportLyrAddr, &param->uL_TportLyrAddr, mBuf); 
		CMCHKPK(cmPkSztGTP_TEID, &param->dL_gTP_TEID, mBuf); 
		CMCHKPK(cmPkSztTportLyrAddr, &param->dL_transportLyrAddr, mBuf); 
		CMCHKPK(cmPkSztGTP_TEID, &param->gTP_TEID, mBuf); 
		CMCHKPK(cmPkSztTportLyrAddr, &param->transportLyrAddr, mBuf); 
		CMCHKPK(cmPkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABAdmtdItem */



/* 
* FUN : cmPkSzt_ValueE_RABAdmtdItemIEsCls
*  DESC: Function to Pack Szt_ValueE_RABAdmtdItemIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueE_RABAdmtdItemIEsCls
(
Szt_ValueE_RABAdmtdItemIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueE_RABAdmtdItemIEsCls(param, val, mBuf)
Szt_ValueE_RABAdmtdItemIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueE_RABAdmtdItemIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABAdmtdItem:
			CMCHKPK(cmPkSztE_RABAdmtdItem, &param->u.sztE_RABAdmtdItem, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueE_RABAdmtdItemIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_E_RABAdmtdItemIEs
*  DESC: Function to Pack SztProtIE_Field_E_RABAdmtdItemIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_E_RABAdmtdItemIEs
(
SztProtIE_Field_E_RABAdmtdItemIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_E_RABAdmtdItemIEs(param, mBuf)
SztProtIE_Field_E_RABAdmtdItemIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_E_RABAdmtdItemIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueE_RABAdmtdItemIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_E_RABAdmtdItemIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmPkSztProtIE_SingleCont_E_RABAdmtdItemIEs cmPkSztProtIE_Field_E_RABAdmtdItemIEs


/* 
* FUN : cmPkSztProtIE_ContLst_E_RABAdmtdItemIEs
*  DESC: Function to Pack SztProtIE_ContLst_E_RABAdmtdItemIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_ContLst_E_RABAdmtdItemIEs
(
SztProtIE_ContLst_E_RABAdmtdItemIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_ContLst_E_RABAdmtdItemIEs(param, mBuf)
SztProtIE_ContLst_E_RABAdmtdItemIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_ContLst_E_RABAdmtdItemIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_SingleCont_E_RABAdmtdItemIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_ContLst_E_RABAdmtdItemIEs */

/* Element ------------- E-RAB-IE-ContainerList ------------ */
#define cmPkSztE_RAB_IE_ContLst_E_RABAdmtdItemIEs cmPkSztProtIE_ContLst_E_RABAdmtdItemIEs
/* Element ------------- E-RABAdmittedList ------------ */
#define cmPkSztE_RABAdmtdLst cmPkSztE_RAB_IE_ContLst_E_RABAdmtdItemIEs


/* 
* FUN : cmPkSzt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls
*  DESC: Function to Pack Szt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls
(
Szt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls(param, val, mBuf)
Szt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs
*  DESC: Function to Pack SztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs
(
SztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs(param, mBuf)
SztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs
*  DESC: Function to Pack SztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs
(
SztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs(param, mBuf)
SztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs */



/* 
* FUN : cmPkSztE_RABFailedToSetupItemHOReqAck
*  DESC: Function to Pack SztE_RABFailedToSetupItemHOReqAck structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABFailedToSetupItemHOReqAck
(
SztE_RABFailedToSetupItemHOReqAck *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABFailedToSetupItemHOReqAck(param, mBuf)
SztE_RABFailedToSetupItemHOReqAck *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztE_RABFailedToSetupItemHOReqAck) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztCause, &param->cause, mBuf); 
		CMCHKPK(cmPkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABFailedToSetupItemHOReqAck */



/* 
* FUN : cmPkSzt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls
*  DESC: Function to Pack Szt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls
(
Szt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls(param, val, mBuf)
Szt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABFailedtoSetupItemHOReqAck:
			CMCHKPK(cmPkSztE_RABFailedToSetupItemHOReqAck, &param->u.sztE_RABFailedToSetupItemHOReqAck, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs
*  DESC: Function to Pack SztProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs
(
SztProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs(param, mBuf)
SztProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmPkSztProtIE_SingleCont_E_RABFailedtoSetupItemHOReqAckIEs cmPkSztProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs


/* 
* FUN : cmPkSztProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs
*  DESC: Function to Pack SztProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs
(
SztProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs(param, mBuf)
SztProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_SingleCont_E_RABFailedtoSetupItemHOReqAckIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs */

/* Element ------------- E-RAB-IE-ContainerList ------------ */
#define cmPkSztE_RAB_IE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs cmPkSztProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs
/* Element ------------- E-RABFailedtoSetupListHOReqAck ------------ */
#define cmPkSztE_RABFailedtoSetupLstHOReqAck cmPkSztE_RAB_IE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs


/* 
* FUN : cmPkSzt_ValueHovrRqstAckgIEsCls
*  DESC: Function to Pack Szt_ValueHovrRqstAckgIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueHovrRqstAckgIEsCls
(
Szt_ValueHovrRqstAckgIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueHovrRqstAckgIEsCls(param, val, mBuf)
Szt_ValueHovrRqstAckgIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueHovrRqstAckgIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_E_RABAdmtdLst:
			CMCHKPK(cmPkSztE_RABAdmtdLst, &param->u.sztE_RABAdmtdLst, mBuf);
			break;
		case Sztid_E_RABFailedToSetupLstHOReqAck:
			CMCHKPK(cmPkSztE_RABFailedtoSetupLstHOReqAck, &param->u.sztE_RABFailedtoSetupLstHOReqAck, mBuf);
			break;
		case Sztid_Tget_ToSrc_TprntCont:
			CMCHKPK(cmPkSztTget_ToSrc_TprntCont, &param->u.sztTget_ToSrc_TprntCont, mBuf);
			break;
		case Sztid_CSG_Id:
			CMCHKPK(cmPkSztCSG_Id, &param->u.sztCSG_Id, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKPK(cmPkSztCriticalityDiag, &param->u.sztCriticalityDiag, mBuf);
			break;
		case Sztid_CellAccessMode:
			CMCHKPK(cmPkSztCellAccessMode, &param->u.sztCellAccessMode, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueHovrRqstAckgIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_HovrRqstAckgIEs
*  DESC: Function to Pack SztProtIE_Field_HovrRqstAckgIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_HovrRqstAckgIEs
(
SztProtIE_Field_HovrRqstAckgIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_HovrRqstAckgIEs(param, mBuf)
SztProtIE_Field_HovrRqstAckgIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_HovrRqstAckgIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueHovrRqstAckgIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_HovrRqstAckgIEs */



/* 
* FUN : cmPkSztProtIE_Cont_HovrRqstAckgIEs
*  DESC: Function to Pack SztProtIE_Cont_HovrRqstAckgIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_HovrRqstAckgIEs
(
SztProtIE_Cont_HovrRqstAckgIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_HovrRqstAckgIEs(param, mBuf)
SztProtIE_Cont_HovrRqstAckgIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_HovrRqstAckgIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_HovrRqstAckgIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_HovrRqstAckgIEs */



/* 
* FUN : cmPkSztHovrRqstAckg
*  DESC: Function to Pack SztHovrRqstAckg structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztHovrRqstAckg
(
SztHovrRqstAckg *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztHovrRqstAckg(param, mBuf)
SztHovrRqstAckg *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztHovrRqstAckg) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_HovrRqstAckgIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztHovrRqstAckg */



/* 
* FUN : cmPkSzt_ValueHovrFailIEsCls
*  DESC: Function to Pack Szt_ValueHovrFailIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueHovrFailIEsCls
(
Szt_ValueHovrFailIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueHovrFailIEsCls(param, val, mBuf)
Szt_ValueHovrFailIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueHovrFailIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_Cause:
			CMCHKPK(cmPkSztCause, &param->u.sztCause, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKPK(cmPkSztCriticalityDiag, &param->u.sztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueHovrFailIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_HovrFailIEs
*  DESC: Function to Pack SztProtIE_Field_HovrFailIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_HovrFailIEs
(
SztProtIE_Field_HovrFailIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_HovrFailIEs(param, mBuf)
SztProtIE_Field_HovrFailIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_HovrFailIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueHovrFailIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_HovrFailIEs */



/* 
* FUN : cmPkSztProtIE_Cont_HovrFailIEs
*  DESC: Function to Pack SztProtIE_Cont_HovrFailIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_HovrFailIEs
(
SztProtIE_Cont_HovrFailIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_HovrFailIEs(param, mBuf)
SztProtIE_Cont_HovrFailIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_HovrFailIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_HovrFailIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_HovrFailIEs */



/* 
* FUN : cmPkSztHovrFail
*  DESC: Function to Pack SztHovrFail structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztHovrFail
(
SztHovrFail *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztHovrFail(param, mBuf)
SztHovrFail *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztHovrFail) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_HovrFailIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztHovrFail */



/* 
* FUN : cmPkSzt_ValueHovrNtfyIEsCls
*  DESC: Function to Pack Szt_ValueHovrNtfyIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueHovrNtfyIEsCls
(
Szt_ValueHovrNtfyIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueHovrNtfyIEsCls(param, val, mBuf)
Szt_ValueHovrNtfyIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueHovrNtfyIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_EUTRAN_CGI:
			CMCHKPK(cmPkSztEUTRAN_CGI, &param->u.sztEUTRAN_CGI, mBuf);
			break;
		case Sztid_TAI:
			CMCHKPK(cmPkSztTAI, &param->u.sztTAI, mBuf);
			break;
		case Sztid_Tunnel_Inform_for_BBF:
			CMCHKPK(cmPkSztTunnelInform, &param->u.sztTunnelInform, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueHovrNtfyIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_HovrNtfyIEs
*  DESC: Function to Pack SztProtIE_Field_HovrNtfyIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_HovrNtfyIEs
(
SztProtIE_Field_HovrNtfyIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_HovrNtfyIEs(param, mBuf)
SztProtIE_Field_HovrNtfyIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_HovrNtfyIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueHovrNtfyIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_HovrNtfyIEs */



/* 
* FUN : cmPkSztProtIE_Cont_HovrNtfyIEs
*  DESC: Function to Pack SztProtIE_Cont_HovrNtfyIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_HovrNtfyIEs
(
SztProtIE_Cont_HovrNtfyIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_HovrNtfyIEs(param, mBuf)
SztProtIE_Cont_HovrNtfyIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_HovrNtfyIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_HovrNtfyIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_HovrNtfyIEs */



/* 
* FUN : cmPkSztHovrNtfy
*  DESC: Function to Pack SztHovrNtfy structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztHovrNtfy
(
SztHovrNtfy *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztHovrNtfy(param, mBuf)
SztHovrNtfy *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztHovrNtfy) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_HovrNtfyIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztHovrNtfy */



/* 
* FUN : cmPkSzt_ExtnE_RABToBeSwedDLItem_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnE_RABToBeSwedDLItem_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnE_RABToBeSwedDLItem_ExtIEsCls
(
Szt_ExtnE_RABToBeSwedDLItem_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnE_RABToBeSwedDLItem_ExtIEsCls(param, val, mBuf)
Szt_ExtnE_RABToBeSwedDLItem_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnE_RABToBeSwedDLItem_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnE_RABToBeSwedDLItem_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_E_RABToBeSwedDLItem_ExtIEs
*  DESC: Function to Pack SztProtExtnField_E_RABToBeSwedDLItem_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_E_RABToBeSwedDLItem_ExtIEs
(
SztProtExtnField_E_RABToBeSwedDLItem_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_E_RABToBeSwedDLItem_ExtIEs(param, mBuf)
SztProtExtnField_E_RABToBeSwedDLItem_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_E_RABToBeSwedDLItem_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnE_RABToBeSwedDLItem_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_E_RABToBeSwedDLItem_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs
(
SztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs(param, mBuf)
SztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_E_RABToBeSwedDLItem_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs */



/* 
* FUN : cmPkSztE_RABToBeSwedDLItem
*  DESC: Function to Pack SztE_RABToBeSwedDLItem structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABToBeSwedDLItem
(
SztE_RABToBeSwedDLItem *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABToBeSwedDLItem(param, mBuf)
SztE_RABToBeSwedDLItem *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztE_RABToBeSwedDLItem) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztGTP_TEID, &param->gTP_TEID, mBuf); 
		CMCHKPK(cmPkSztTportLyrAddr, &param->transportLyrAddr, mBuf); 
		CMCHKPK(cmPkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABToBeSwedDLItem */



/* 
* FUN : cmPkSzt_ValueE_RABToBeSwedDLItemIEsCls
*  DESC: Function to Pack Szt_ValueE_RABToBeSwedDLItemIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueE_RABToBeSwedDLItemIEsCls
(
Szt_ValueE_RABToBeSwedDLItemIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueE_RABToBeSwedDLItemIEsCls(param, val, mBuf)
Szt_ValueE_RABToBeSwedDLItemIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueE_RABToBeSwedDLItemIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABToBeSwedDLItem:
			CMCHKPK(cmPkSztE_RABToBeSwedDLItem, &param->u.sztE_RABToBeSwedDLItem, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueE_RABToBeSwedDLItemIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_E_RABToBeSwedDLItemIEs
*  DESC: Function to Pack SztProtIE_Field_E_RABToBeSwedDLItemIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_E_RABToBeSwedDLItemIEs
(
SztProtIE_Field_E_RABToBeSwedDLItemIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_E_RABToBeSwedDLItemIEs(param, mBuf)
SztProtIE_Field_E_RABToBeSwedDLItemIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_E_RABToBeSwedDLItemIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueE_RABToBeSwedDLItemIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_E_RABToBeSwedDLItemIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmPkSztProtIE_SingleCont_E_RABToBeSwedDLItemIEs cmPkSztProtIE_Field_E_RABToBeSwedDLItemIEs


/* 
* FUN : cmPkSztProtIE_ContLst_E_RABToBeSwedDLItemIEs
*  DESC: Function to Pack SztProtIE_ContLst_E_RABToBeSwedDLItemIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_ContLst_E_RABToBeSwedDLItemIEs
(
SztProtIE_ContLst_E_RABToBeSwedDLItemIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_ContLst_E_RABToBeSwedDLItemIEs(param, mBuf)
SztProtIE_ContLst_E_RABToBeSwedDLItemIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_ContLst_E_RABToBeSwedDLItemIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_SingleCont_E_RABToBeSwedDLItemIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_ContLst_E_RABToBeSwedDLItemIEs */

/* Element ------------- E-RAB-IE-ContainerList ------------ */
#define cmPkSztE_RAB_IE_ContLst_E_RABToBeSwedDLItemIEs cmPkSztProtIE_ContLst_E_RABToBeSwedDLItemIEs
/* Element ------------- E-RABToBeSwitchedDLList ------------ */
#define cmPkSztE_RABToBeSwedDLLst cmPkSztE_RAB_IE_ContLst_E_RABToBeSwedDLItemIEs


/* 
* FUN : cmPkSzt_ValuePathSwRqstIEsCls
*  DESC: Function to Pack Szt_ValuePathSwRqstIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValuePathSwRqstIEsCls
(
Szt_ValuePathSwRqstIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValuePathSwRqstIEsCls(param, val, mBuf)
Szt_ValuePathSwRqstIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValuePathSwRqstIEsCls) 
	
	switch (val)
	{
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_E_RABToBeSwedDLLst:
			CMCHKPK(cmPkSztE_RABToBeSwedDLLst, &param->u.sztE_RABToBeSwedDLLst, mBuf);
			break;
		case Sztid_SrcMME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_EUTRAN_CGI:
			CMCHKPK(cmPkSztEUTRAN_CGI, &param->u.sztEUTRAN_CGI, mBuf);
			break;
		case Sztid_TAI:
			CMCHKPK(cmPkSztTAI, &param->u.sztTAI, mBuf);
			break;
		case Sztid_UESecurCapabilities:
			CMCHKPK(cmPkSztUESecurCapabilities, &param->u.sztUESecurCapabilities, mBuf);
			break;
		case Sztid_CSG_Id:
			CMCHKPK(cmPkSztCSG_Id, &param->u.sztCSG_Id, mBuf);
			break;
		case Sztid_CellAccessMode:
			CMCHKPK(cmPkSztCellAccessMode, &param->u.sztCellAccessMode, mBuf);
			break;
		case Sztid_SrcMME_GUMMEI:
			CMCHKPK(cmPkSztGUMMEI, &param->u.sztGUMMEI, mBuf);
			break;
		case Sztid_CSGMembershipStatus:
			CMCHKPK(cmPkSztCSGMembershipStatus, &param->u.sztCSGMembershipStatus, mBuf);
			break;
		case Sztid_Tunnel_Inform_for_BBF:
			CMCHKPK(cmPkSztTunnelInform, &param->u.sztTunnelInform, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValuePathSwRqstIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_PathSwRqstIEs
*  DESC: Function to Pack SztProtIE_Field_PathSwRqstIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_PathSwRqstIEs
(
SztProtIE_Field_PathSwRqstIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_PathSwRqstIEs(param, mBuf)
SztProtIE_Field_PathSwRqstIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_PathSwRqstIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValuePathSwRqstIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_PathSwRqstIEs */



/* 
* FUN : cmPkSztProtIE_Cont_PathSwRqstIEs
*  DESC: Function to Pack SztProtIE_Cont_PathSwRqstIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_PathSwRqstIEs
(
SztProtIE_Cont_PathSwRqstIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_PathSwRqstIEs(param, mBuf)
SztProtIE_Cont_PathSwRqstIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_PathSwRqstIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_PathSwRqstIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_PathSwRqstIEs */



/* 
* FUN : cmPkSztPathSwRqst
*  DESC: Function to Pack SztPathSwRqst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztPathSwRqst
(
SztPathSwRqst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztPathSwRqst(param, mBuf)
SztPathSwRqst *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztPathSwRqst) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_PathSwRqstIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztPathSwRqst */



/* 
* FUN : cmPkSzt_ExtnE_RABToBeSwedULItem_ExtIEsCls
*  DESC: Function to Pack Szt_ExtnE_RABToBeSwedULItem_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnE_RABToBeSwedULItem_ExtIEsCls
(
Szt_ExtnE_RABToBeSwedULItem_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnE_RABToBeSwedULItem_ExtIEsCls(param, val, mBuf)
Szt_ExtnE_RABToBeSwedULItem_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnE_RABToBeSwedULItem_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnE_RABToBeSwedULItem_ExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_E_RABToBeSwedULItem_ExtIEs
*  DESC: Function to Pack SztProtExtnField_E_RABToBeSwedULItem_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_E_RABToBeSwedULItem_ExtIEs
(
SztProtExtnField_E_RABToBeSwedULItem_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_E_RABToBeSwedULItem_ExtIEs(param, mBuf)
SztProtExtnField_E_RABToBeSwedULItem_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_E_RABToBeSwedULItem_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnE_RABToBeSwedULItem_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_E_RABToBeSwedULItem_ExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_E_RABToBeSwedULItem_ExtIEs
*  DESC: Function to Pack SztProtExtnCont_E_RABToBeSwedULItem_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_E_RABToBeSwedULItem_ExtIEs
(
SztProtExtnCont_E_RABToBeSwedULItem_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_E_RABToBeSwedULItem_ExtIEs(param, mBuf)
SztProtExtnCont_E_RABToBeSwedULItem_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_E_RABToBeSwedULItem_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_E_RABToBeSwedULItem_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_E_RABToBeSwedULItem_ExtIEs */



/* 
* FUN : cmPkSztE_RABToBeSwedULItem
*  DESC: Function to Pack SztE_RABToBeSwedULItem structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABToBeSwedULItem
(
SztE_RABToBeSwedULItem *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABToBeSwedULItem(param, mBuf)
SztE_RABToBeSwedULItem *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztE_RABToBeSwedULItem) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_E_RABToBeSwedULItem_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztGTP_TEID, &param->gTP_TEID, mBuf); 
		CMCHKPK(cmPkSztTportLyrAddr, &param->transportLyrAddr, mBuf); 
		CMCHKPK(cmPkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABToBeSwedULItem */



/* 
* FUN : cmPkSzt_ValueE_RABToBeSwedULItemIEsCls
*  DESC: Function to Pack Szt_ValueE_RABToBeSwedULItemIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueE_RABToBeSwedULItemIEsCls
(
Szt_ValueE_RABToBeSwedULItemIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueE_RABToBeSwedULItemIEsCls(param, val, mBuf)
Szt_ValueE_RABToBeSwedULItemIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueE_RABToBeSwedULItemIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABToBeSwedULItem:
			CMCHKPK(cmPkSztE_RABToBeSwedULItem, &param->u.sztE_RABToBeSwedULItem, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueE_RABToBeSwedULItemIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_E_RABToBeSwedULItemIEs
*  DESC: Function to Pack SztProtIE_Field_E_RABToBeSwedULItemIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_E_RABToBeSwedULItemIEs
(
SztProtIE_Field_E_RABToBeSwedULItemIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_E_RABToBeSwedULItemIEs(param, mBuf)
SztProtIE_Field_E_RABToBeSwedULItemIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_E_RABToBeSwedULItemIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueE_RABToBeSwedULItemIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_E_RABToBeSwedULItemIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmPkSztProtIE_SingleCont_E_RABToBeSwedULItemIEs cmPkSztProtIE_Field_E_RABToBeSwedULItemIEs


/* 
* FUN : cmPkSztProtIE_ContLst_E_RABToBeSwedULItemIEs
*  DESC: Function to Pack SztProtIE_ContLst_E_RABToBeSwedULItemIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_ContLst_E_RABToBeSwedULItemIEs
(
SztProtIE_ContLst_E_RABToBeSwedULItemIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_ContLst_E_RABToBeSwedULItemIEs(param, mBuf)
SztProtIE_ContLst_E_RABToBeSwedULItemIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_ContLst_E_RABToBeSwedULItemIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_SingleCont_E_RABToBeSwedULItemIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_ContLst_E_RABToBeSwedULItemIEs */

/* Element ------------- E-RAB-IE-ContainerList ------------ */
#define cmPkSztE_RAB_IE_ContLst_E_RABToBeSwedULItemIEs cmPkSztProtIE_ContLst_E_RABToBeSwedULItemIEs
/* Element ------------- E-RABToBeSwitchedULList ------------ */
#define cmPkSztE_RABToBeSwedULLst cmPkSztE_RAB_IE_ContLst_E_RABToBeSwedULItemIEs


/* 
* FUN : cmPkSzt_ValuePathSwRqstAckgIEsCls
*  DESC: Function to Pack Szt_ValuePathSwRqstAckgIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValuePathSwRqstAckgIEsCls
(
Szt_ValuePathSwRqstAckgIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValuePathSwRqstAckgIEsCls(param, val, mBuf)
Szt_ValuePathSwRqstAckgIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValuePathSwRqstAckgIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztid_MME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_uEaggregateMaxBitrate:
			CMCHKPK(cmPkSztUEAggMaxBitrate, &param->u.sztUEAggMaxBitrate, mBuf);
			break;
		case Sztid_E_RABToBeSwedULLst:
			CMCHKPK(cmPkSztE_RABToBeSwedULLst, &param->u.sztE_RABToBeSwedULLst, mBuf);
			break;
		case Sztid_E_RABToBeRlsdLst:
			CMCHKPK(cmPkSztE_RABLst, &param->u.sztE_RABLst, mBuf);
			break;
		case Sztid_SecurCntxt:
			CMCHKPK(cmPkSztSecurCntxt, &param->u.sztSecurCntxt, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKPK(cmPkSztCriticalityDiag, &param->u.sztCriticalityDiag, mBuf);
			break;
		case Sztid_MME_UE_S1AP_ID_2:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztid_MME_UE_S1AP_ID_2, mBuf);
			break;
		case Sztid_CSGMembershipStatus:
			CMCHKPK(cmPkSztCSGMembershipStatus, &param->u.sztCSGMembershipStatus, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValuePathSwRqstAckgIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_PathSwRqstAckgIEs
*  DESC: Function to Pack SztProtIE_Field_PathSwRqstAckgIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_PathSwRqstAckgIEs
(
SztProtIE_Field_PathSwRqstAckgIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_PathSwRqstAckgIEs(param, mBuf)
SztProtIE_Field_PathSwRqstAckgIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_PathSwRqstAckgIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValuePathSwRqstAckgIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_PathSwRqstAckgIEs */



/* 
* FUN : cmPkSztProtIE_Cont_PathSwRqstAckgIEs
*  DESC: Function to Pack SztProtIE_Cont_PathSwRqstAckgIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_PathSwRqstAckgIEs
(
SztProtIE_Cont_PathSwRqstAckgIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_PathSwRqstAckgIEs(param, mBuf)
SztProtIE_Cont_PathSwRqstAckgIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_PathSwRqstAckgIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_PathSwRqstAckgIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_PathSwRqstAckgIEs */



/* 
* FUN : cmPkSztPathSwRqstAckg
*  DESC: Function to Pack SztPathSwRqstAckg structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztPathSwRqstAckg
(
SztPathSwRqstAckg *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztPathSwRqstAckg(param, mBuf)
SztPathSwRqstAckg *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztPathSwRqstAckg) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_PathSwRqstAckgIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztPathSwRqstAckg */



/* 
* FUN : cmPkSzt_ValuePathSwRqstFailIEsCls
*  DESC: Function to Pack Szt_ValuePathSwRqstFailIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValuePathSwRqstFailIEsCls
(
Szt_ValuePathSwRqstFailIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValuePathSwRqstFailIEsCls(param, val, mBuf)
Szt_ValuePathSwRqstFailIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValuePathSwRqstFailIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_Cause:
			CMCHKPK(cmPkSztCause, &param->u.sztCause, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKPK(cmPkSztCriticalityDiag, &param->u.sztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValuePathSwRqstFailIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_PathSwRqstFailIEs
*  DESC: Function to Pack SztProtIE_Field_PathSwRqstFailIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_PathSwRqstFailIEs
(
SztProtIE_Field_PathSwRqstFailIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_PathSwRqstFailIEs(param, mBuf)
SztProtIE_Field_PathSwRqstFailIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_PathSwRqstFailIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValuePathSwRqstFailIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_PathSwRqstFailIEs */



/* 
* FUN : cmPkSztProtIE_Cont_PathSwRqstFailIEs
*  DESC: Function to Pack SztProtIE_Cont_PathSwRqstFailIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_PathSwRqstFailIEs
(
SztProtIE_Cont_PathSwRqstFailIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_PathSwRqstFailIEs(param, mBuf)
SztProtIE_Cont_PathSwRqstFailIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_PathSwRqstFailIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_PathSwRqstFailIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_PathSwRqstFailIEs */



/* 
* FUN : cmPkSztPathSwRqstFail
*  DESC: Function to Pack SztPathSwRqstFail structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztPathSwRqstFail
(
SztPathSwRqstFail *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztPathSwRqstFail(param, mBuf)
SztPathSwRqstFail *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztPathSwRqstFail) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_PathSwRqstFailIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztPathSwRqstFail */



/* 
* FUN : cmPkSzt_ValueHovrCancelIEsCls
*  DESC: Function to Pack Szt_ValueHovrCancelIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueHovrCancelIEsCls
(
Szt_ValueHovrCancelIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueHovrCancelIEsCls(param, val, mBuf)
Szt_ValueHovrCancelIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueHovrCancelIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_Cause:
			CMCHKPK(cmPkSztCause, &param->u.sztCause, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueHovrCancelIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_HovrCancelIEs
*  DESC: Function to Pack SztProtIE_Field_HovrCancelIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_HovrCancelIEs
(
SztProtIE_Field_HovrCancelIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_HovrCancelIEs(param, mBuf)
SztProtIE_Field_HovrCancelIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_HovrCancelIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueHovrCancelIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_HovrCancelIEs */



/* 
* FUN : cmPkSztProtIE_Cont_HovrCancelIEs
*  DESC: Function to Pack SztProtIE_Cont_HovrCancelIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_HovrCancelIEs
(
SztProtIE_Cont_HovrCancelIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_HovrCancelIEs(param, mBuf)
SztProtIE_Cont_HovrCancelIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_HovrCancelIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_HovrCancelIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_HovrCancelIEs */



/* 
* FUN : cmPkSztHovrCancel
*  DESC: Function to Pack SztHovrCancel structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztHovrCancel
(
SztHovrCancel *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztHovrCancel(param, mBuf)
SztHovrCancel *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztHovrCancel) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_HovrCancelIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztHovrCancel */



/* 
* FUN : cmPkSzt_ValueHovrCancelAckgIEsCls
*  DESC: Function to Pack Szt_ValueHovrCancelAckgIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueHovrCancelAckgIEsCls
(
Szt_ValueHovrCancelAckgIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueHovrCancelAckgIEsCls(param, val, mBuf)
Szt_ValueHovrCancelAckgIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueHovrCancelAckgIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKPK(cmPkSztCriticalityDiag, &param->u.sztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueHovrCancelAckgIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_HovrCancelAckgIEs
*  DESC: Function to Pack SztProtIE_Field_HovrCancelAckgIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_HovrCancelAckgIEs
(
SztProtIE_Field_HovrCancelAckgIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_HovrCancelAckgIEs(param, mBuf)
SztProtIE_Field_HovrCancelAckgIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_HovrCancelAckgIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueHovrCancelAckgIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_HovrCancelAckgIEs */



/* 
* FUN : cmPkSztProtIE_Cont_HovrCancelAckgIEs
*  DESC: Function to Pack SztProtIE_Cont_HovrCancelAckgIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_HovrCancelAckgIEs
(
SztProtIE_Cont_HovrCancelAckgIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_HovrCancelAckgIEs(param, mBuf)
SztProtIE_Cont_HovrCancelAckgIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_HovrCancelAckgIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_HovrCancelAckgIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_HovrCancelAckgIEs */



/* 
* FUN : cmPkSztHovrCancelAckg
*  DESC: Function to Pack SztHovrCancelAckg structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztHovrCancelAckg
(
SztHovrCancelAckg *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztHovrCancelAckg(param, mBuf)
SztHovrCancelAckg *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztHovrCancelAckg) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_HovrCancelAckgIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztHovrCancelAckg */



/* 
* FUN : cmPkSzt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls
*  DESC: Function to Pack Szt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls
(
Szt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls(param, val, mBuf)
Szt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls) 
	
	switch (val)
	{
		case Sztid_Correlation_ID:
			CMCHKPK(cmPkSztCorrelation_ID, &param->u.sztCorrelation_ID, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs
*  DESC: Function to Pack SztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs
(
SztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs(param, mBuf)
SztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs
*  DESC: Function to Pack SztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs
(
SztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs(param, mBuf)
SztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs */



/* 
* FUN : cmPkSztE_RABToBeSetupItemBrSUReq
*  DESC: Function to Pack SztE_RABToBeSetupItemBrSUReq structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABToBeSetupItemBrSUReq
(
SztE_RABToBeSetupItemBrSUReq *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABToBeSetupItemBrSUReq(param, mBuf)
SztE_RABToBeSetupItemBrSUReq *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztE_RABToBeSetupItemBrSUReq) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztNAS_PDU, &param->nAS_PDU, mBuf); 
		CMCHKPK(cmPkSztGTP_TEID, &param->gTP_TEID, mBuf); 
		CMCHKPK(cmPkSztTportLyrAddr, &param->transportLyrAddr, mBuf); 
		CMCHKPK(cmPkSztE_RABLvlQoSParams, &param->e_RABlevelQoSParams, mBuf); 
		CMCHKPK(cmPkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABToBeSetupItemBrSUReq */



/* 
* FUN : cmPkSzt_ValueE_RABToBeSetupItemBrSUReqIEsCls
*  DESC: Function to Pack Szt_ValueE_RABToBeSetupItemBrSUReqIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueE_RABToBeSetupItemBrSUReqIEsCls
(
Szt_ValueE_RABToBeSetupItemBrSUReqIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueE_RABToBeSetupItemBrSUReqIEsCls(param, val, mBuf)
Szt_ValueE_RABToBeSetupItemBrSUReqIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueE_RABToBeSetupItemBrSUReqIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABToBeSetupItemBrSUReq:
			CMCHKPK(cmPkSztE_RABToBeSetupItemBrSUReq, &param->u.sztE_RABToBeSetupItemBrSUReq, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueE_RABToBeSetupItemBrSUReqIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_E_RABToBeSetupItemBrSUReqIEs
*  DESC: Function to Pack SztProtIE_Field_E_RABToBeSetupItemBrSUReqIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_E_RABToBeSetupItemBrSUReqIEs
(
SztProtIE_Field_E_RABToBeSetupItemBrSUReqIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_E_RABToBeSetupItemBrSUReqIEs(param, mBuf)
SztProtIE_Field_E_RABToBeSetupItemBrSUReqIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_E_RABToBeSetupItemBrSUReqIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueE_RABToBeSetupItemBrSUReqIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_E_RABToBeSetupItemBrSUReqIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmPkSztProtIE_SingleCont_E_RABToBeSetupItemBrSUReqIEs cmPkSztProtIE_Field_E_RABToBeSetupItemBrSUReqIEs


/* 
* FUN : cmPkSztE_RABToBeSetupLstBrSUReq
*  DESC: Function to Pack SztE_RABToBeSetupLstBrSUReq structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABToBeSetupLstBrSUReq
(
SztE_RABToBeSetupLstBrSUReq *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABToBeSetupLstBrSUReq(param, mBuf)
SztE_RABToBeSetupLstBrSUReq *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztE_RABToBeSetupLstBrSUReq) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_SingleCont_E_RABToBeSetupItemBrSUReqIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABToBeSetupLstBrSUReq */



/* 
* FUN : cmPkSzt_ValueE_RABSetupRqstIEsCls
*  DESC: Function to Pack Szt_ValueE_RABSetupRqstIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueE_RABSetupRqstIEsCls
(
Szt_ValueE_RABSetupRqstIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueE_RABSetupRqstIEsCls(param, val, mBuf)
Szt_ValueE_RABSetupRqstIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueE_RABSetupRqstIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_uEaggregateMaxBitrate:
			CMCHKPK(cmPkSztUEAggMaxBitrate, &param->u.sztUEAggMaxBitrate, mBuf);
			break;
		case Sztid_E_RABToBeSetupLstBrSUReq:
			CMCHKPK(cmPkSztE_RABToBeSetupLstBrSUReq, &param->u.sztE_RABToBeSetupLstBrSUReq, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueE_RABSetupRqstIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_E_RABSetupRqstIEs
*  DESC: Function to Pack SztProtIE_Field_E_RABSetupRqstIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_E_RABSetupRqstIEs
(
SztProtIE_Field_E_RABSetupRqstIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_E_RABSetupRqstIEs(param, mBuf)
SztProtIE_Field_E_RABSetupRqstIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_E_RABSetupRqstIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueE_RABSetupRqstIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_E_RABSetupRqstIEs */



/* 
* FUN : cmPkSztProtIE_Cont_E_RABSetupRqstIEs
*  DESC: Function to Pack SztProtIE_Cont_E_RABSetupRqstIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_E_RABSetupRqstIEs
(
SztProtIE_Cont_E_RABSetupRqstIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_E_RABSetupRqstIEs(param, mBuf)
SztProtIE_Cont_E_RABSetupRqstIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_E_RABSetupRqstIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_E_RABSetupRqstIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_E_RABSetupRqstIEs */



/* 
* FUN : cmPkSztE_RABSetupRqst
*  DESC: Function to Pack SztE_RABSetupRqst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABSetupRqst
(
SztE_RABSetupRqst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABSetupRqst(param, mBuf)
SztE_RABSetupRqst *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztE_RABSetupRqst) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_E_RABSetupRqstIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABSetupRqst */



/* 
* FUN : cmPkSzt_ExtnE_RABSetupItemBrSUResExtIEsCls
*  DESC: Function to Pack Szt_ExtnE_RABSetupItemBrSUResExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnE_RABSetupItemBrSUResExtIEsCls
(
Szt_ExtnE_RABSetupItemBrSUResExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnE_RABSetupItemBrSUResExtIEsCls(param, val, mBuf)
Szt_ExtnE_RABSetupItemBrSUResExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnE_RABSetupItemBrSUResExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnE_RABSetupItemBrSUResExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_E_RABSetupItemBrSUResExtIEs
*  DESC: Function to Pack SztProtExtnField_E_RABSetupItemBrSUResExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_E_RABSetupItemBrSUResExtIEs
(
SztProtExtnField_E_RABSetupItemBrSUResExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_E_RABSetupItemBrSUResExtIEs(param, mBuf)
SztProtExtnField_E_RABSetupItemBrSUResExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_E_RABSetupItemBrSUResExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnE_RABSetupItemBrSUResExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_E_RABSetupItemBrSUResExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_E_RABSetupItemBrSUResExtIEs
*  DESC: Function to Pack SztProtExtnCont_E_RABSetupItemBrSUResExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_E_RABSetupItemBrSUResExtIEs
(
SztProtExtnCont_E_RABSetupItemBrSUResExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_E_RABSetupItemBrSUResExtIEs(param, mBuf)
SztProtExtnCont_E_RABSetupItemBrSUResExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_E_RABSetupItemBrSUResExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_E_RABSetupItemBrSUResExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_E_RABSetupItemBrSUResExtIEs */



/* 
* FUN : cmPkSztE_RABSetupItemBrSURes
*  DESC: Function to Pack SztE_RABSetupItemBrSURes structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABSetupItemBrSURes
(
SztE_RABSetupItemBrSURes *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABSetupItemBrSURes(param, mBuf)
SztE_RABSetupItemBrSURes *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztE_RABSetupItemBrSURes) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_E_RABSetupItemBrSUResExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztGTP_TEID, &param->gTP_TEID, mBuf); 
		CMCHKPK(cmPkSztTportLyrAddr, &param->transportLyrAddr, mBuf); 
		CMCHKPK(cmPkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABSetupItemBrSURes */



/* 
* FUN : cmPkSzt_ValueE_RABSetupItemBrSUResIEsCls
*  DESC: Function to Pack Szt_ValueE_RABSetupItemBrSUResIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueE_RABSetupItemBrSUResIEsCls
(
Szt_ValueE_RABSetupItemBrSUResIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueE_RABSetupItemBrSUResIEsCls(param, val, mBuf)
Szt_ValueE_RABSetupItemBrSUResIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueE_RABSetupItemBrSUResIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABSetupItemBrSURes:
			CMCHKPK(cmPkSztE_RABSetupItemBrSURes, &param->u.sztE_RABSetupItemBrSURes, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueE_RABSetupItemBrSUResIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_E_RABSetupItemBrSUResIEs
*  DESC: Function to Pack SztProtIE_Field_E_RABSetupItemBrSUResIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_E_RABSetupItemBrSUResIEs
(
SztProtIE_Field_E_RABSetupItemBrSUResIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_E_RABSetupItemBrSUResIEs(param, mBuf)
SztProtIE_Field_E_RABSetupItemBrSUResIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_E_RABSetupItemBrSUResIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueE_RABSetupItemBrSUResIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_E_RABSetupItemBrSUResIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmPkSztProtIE_SingleCont_E_RABSetupItemBrSUResIEs cmPkSztProtIE_Field_E_RABSetupItemBrSUResIEs


/* 
* FUN : cmPkSztE_RABSetupLstBrSURes
*  DESC: Function to Pack SztE_RABSetupLstBrSURes structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABSetupLstBrSURes
(
SztE_RABSetupLstBrSURes *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABSetupLstBrSURes(param, mBuf)
SztE_RABSetupLstBrSURes *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztE_RABSetupLstBrSURes) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_SingleCont_E_RABSetupItemBrSUResIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABSetupLstBrSURes */



/* 
* FUN : cmPkSzt_ValueE_RABSetupRespIEsCls
*  DESC: Function to Pack Szt_ValueE_RABSetupRespIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueE_RABSetupRespIEsCls
(
Szt_ValueE_RABSetupRespIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueE_RABSetupRespIEsCls(param, val, mBuf)
Szt_ValueE_RABSetupRespIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueE_RABSetupRespIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_E_RABSetupLstBrSURes:
			CMCHKPK(cmPkSztE_RABSetupLstBrSURes, &param->u.sztE_RABSetupLstBrSURes, mBuf);
			break;
		case Sztid_E_RABFailedToSetupLstBrSURes:
			CMCHKPK(cmPkSztE_RABLst, &param->u.sztE_RABLst, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKPK(cmPkSztCriticalityDiag, &param->u.sztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueE_RABSetupRespIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_E_RABSetupRespIEs
*  DESC: Function to Pack SztProtIE_Field_E_RABSetupRespIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_E_RABSetupRespIEs
(
SztProtIE_Field_E_RABSetupRespIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_E_RABSetupRespIEs(param, mBuf)
SztProtIE_Field_E_RABSetupRespIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_E_RABSetupRespIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueE_RABSetupRespIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_E_RABSetupRespIEs */



/* 
* FUN : cmPkSztProtIE_Cont_E_RABSetupRespIEs
*  DESC: Function to Pack SztProtIE_Cont_E_RABSetupRespIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_E_RABSetupRespIEs
(
SztProtIE_Cont_E_RABSetupRespIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_E_RABSetupRespIEs(param, mBuf)
SztProtIE_Cont_E_RABSetupRespIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_E_RABSetupRespIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_E_RABSetupRespIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_E_RABSetupRespIEs */



/* 
* FUN : cmPkSztE_RABSetupResp
*  DESC: Function to Pack SztE_RABSetupResp structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABSetupResp
(
SztE_RABSetupResp *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABSetupResp(param, mBuf)
SztE_RABSetupResp *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztE_RABSetupResp) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_E_RABSetupRespIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABSetupResp */



/* 
* FUN : cmPkSzt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls
*  DESC: Function to Pack Szt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls
(
Szt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls(param, val, mBuf)
Szt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs
*  DESC: Function to Pack SztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs
(
SztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs(param, mBuf)
SztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs
*  DESC: Function to Pack SztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs
(
SztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs(param, mBuf)
SztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs */



/* 
* FUN : cmPkSztE_RABToBeMdfdItemBrModReq
*  DESC: Function to Pack SztE_RABToBeMdfdItemBrModReq structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABToBeMdfdItemBrModReq
(
SztE_RABToBeMdfdItemBrModReq *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABToBeMdfdItemBrModReq(param, mBuf)
SztE_RABToBeMdfdItemBrModReq *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztE_RABToBeMdfdItemBrModReq) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztNAS_PDU, &param->nAS_PDU, mBuf); 
		CMCHKPK(cmPkSztE_RABLvlQoSParams, &param->e_RABLvlQoSParams, mBuf); 
		CMCHKPK(cmPkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABToBeMdfdItemBrModReq */



/* 
* FUN : cmPkSzt_ValueE_RABToBeMdfdItemBrModReqIEsCls
*  DESC: Function to Pack Szt_ValueE_RABToBeMdfdItemBrModReqIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueE_RABToBeMdfdItemBrModReqIEsCls
(
Szt_ValueE_RABToBeMdfdItemBrModReqIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueE_RABToBeMdfdItemBrModReqIEsCls(param, val, mBuf)
Szt_ValueE_RABToBeMdfdItemBrModReqIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueE_RABToBeMdfdItemBrModReqIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABToBeMdfdItemBrModReq:
			CMCHKPK(cmPkSztE_RABToBeMdfdItemBrModReq, &param->u.sztE_RABToBeMdfdItemBrModReq, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueE_RABToBeMdfdItemBrModReqIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_E_RABToBeMdfdItemBrModReqIEs
*  DESC: Function to Pack SztProtIE_Field_E_RABToBeMdfdItemBrModReqIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_E_RABToBeMdfdItemBrModReqIEs
(
SztProtIE_Field_E_RABToBeMdfdItemBrModReqIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_E_RABToBeMdfdItemBrModReqIEs(param, mBuf)
SztProtIE_Field_E_RABToBeMdfdItemBrModReqIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_E_RABToBeMdfdItemBrModReqIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueE_RABToBeMdfdItemBrModReqIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_E_RABToBeMdfdItemBrModReqIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmPkSztProtIE_SingleCont_E_RABToBeMdfdItemBrModReqIEs cmPkSztProtIE_Field_E_RABToBeMdfdItemBrModReqIEs


/* 
* FUN : cmPkSztE_RABToBeMdfdLstBrModReq
*  DESC: Function to Pack SztE_RABToBeMdfdLstBrModReq structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABToBeMdfdLstBrModReq
(
SztE_RABToBeMdfdLstBrModReq *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABToBeMdfdLstBrModReq(param, mBuf)
SztE_RABToBeMdfdLstBrModReq *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztE_RABToBeMdfdLstBrModReq) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_SingleCont_E_RABToBeMdfdItemBrModReqIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABToBeMdfdLstBrModReq */



/* 
* FUN : cmPkSzt_ValueE_RABMdfyRqstIEsCls
*  DESC: Function to Pack Szt_ValueE_RABMdfyRqstIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueE_RABMdfyRqstIEsCls
(
Szt_ValueE_RABMdfyRqstIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueE_RABMdfyRqstIEsCls(param, val, mBuf)
Szt_ValueE_RABMdfyRqstIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueE_RABMdfyRqstIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_uEaggregateMaxBitrate:
			CMCHKPK(cmPkSztUEAggMaxBitrate, &param->u.sztUEAggMaxBitrate, mBuf);
			break;
		case Sztid_E_RABToBeMdfdLstBrModReq:
			CMCHKPK(cmPkSztE_RABToBeMdfdLstBrModReq, &param->u.sztE_RABToBeMdfdLstBrModReq, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueE_RABMdfyRqstIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_E_RABMdfyRqstIEs
*  DESC: Function to Pack SztProtIE_Field_E_RABMdfyRqstIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_E_RABMdfyRqstIEs
(
SztProtIE_Field_E_RABMdfyRqstIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_E_RABMdfyRqstIEs(param, mBuf)
SztProtIE_Field_E_RABMdfyRqstIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_E_RABMdfyRqstIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueE_RABMdfyRqstIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_E_RABMdfyRqstIEs */



/* 
* FUN : cmPkSztProtIE_Cont_E_RABMdfyRqstIEs
*  DESC: Function to Pack SztProtIE_Cont_E_RABMdfyRqstIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_E_RABMdfyRqstIEs
(
SztProtIE_Cont_E_RABMdfyRqstIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_E_RABMdfyRqstIEs(param, mBuf)
SztProtIE_Cont_E_RABMdfyRqstIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_E_RABMdfyRqstIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_E_RABMdfyRqstIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_E_RABMdfyRqstIEs */



/* 
* FUN : cmPkSztE_RABMdfyRqst
*  DESC: Function to Pack SztE_RABMdfyRqst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABMdfyRqst
(
SztE_RABMdfyRqst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABMdfyRqst(param, mBuf)
SztE_RABMdfyRqst *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztE_RABMdfyRqst) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_E_RABMdfyRqstIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABMdfyRqst */



/* 
* FUN : cmPkSzt_ExtnE_RABMdfyItemBrModResExtIEsCls
*  DESC: Function to Pack Szt_ExtnE_RABMdfyItemBrModResExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnE_RABMdfyItemBrModResExtIEsCls
(
Szt_ExtnE_RABMdfyItemBrModResExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnE_RABMdfyItemBrModResExtIEsCls(param, val, mBuf)
Szt_ExtnE_RABMdfyItemBrModResExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnE_RABMdfyItemBrModResExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnE_RABMdfyItemBrModResExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_E_RABMdfyItemBrModResExtIEs
*  DESC: Function to Pack SztProtExtnField_E_RABMdfyItemBrModResExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_E_RABMdfyItemBrModResExtIEs
(
SztProtExtnField_E_RABMdfyItemBrModResExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_E_RABMdfyItemBrModResExtIEs(param, mBuf)
SztProtExtnField_E_RABMdfyItemBrModResExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_E_RABMdfyItemBrModResExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnE_RABMdfyItemBrModResExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_E_RABMdfyItemBrModResExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_E_RABMdfyItemBrModResExtIEs
*  DESC: Function to Pack SztProtExtnCont_E_RABMdfyItemBrModResExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_E_RABMdfyItemBrModResExtIEs
(
SztProtExtnCont_E_RABMdfyItemBrModResExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_E_RABMdfyItemBrModResExtIEs(param, mBuf)
SztProtExtnCont_E_RABMdfyItemBrModResExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_E_RABMdfyItemBrModResExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_E_RABMdfyItemBrModResExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_E_RABMdfyItemBrModResExtIEs */



/* 
* FUN : cmPkSztE_RABMdfyItemBrModRes
*  DESC: Function to Pack SztE_RABMdfyItemBrModRes structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABMdfyItemBrModRes
(
SztE_RABMdfyItemBrModRes *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABMdfyItemBrModRes(param, mBuf)
SztE_RABMdfyItemBrModRes *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztE_RABMdfyItemBrModRes) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_E_RABMdfyItemBrModResExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABMdfyItemBrModRes */



/* 
* FUN : cmPkSzt_ValueE_RABMdfyItemBrModResIEsCls
*  DESC: Function to Pack Szt_ValueE_RABMdfyItemBrModResIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueE_RABMdfyItemBrModResIEsCls
(
Szt_ValueE_RABMdfyItemBrModResIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueE_RABMdfyItemBrModResIEsCls(param, val, mBuf)
Szt_ValueE_RABMdfyItemBrModResIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueE_RABMdfyItemBrModResIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABMdfyItemBrModRes:
			CMCHKPK(cmPkSztE_RABMdfyItemBrModRes, &param->u.sztE_RABMdfyItemBrModRes, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueE_RABMdfyItemBrModResIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_E_RABMdfyItemBrModResIEs
*  DESC: Function to Pack SztProtIE_Field_E_RABMdfyItemBrModResIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_E_RABMdfyItemBrModResIEs
(
SztProtIE_Field_E_RABMdfyItemBrModResIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_E_RABMdfyItemBrModResIEs(param, mBuf)
SztProtIE_Field_E_RABMdfyItemBrModResIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_E_RABMdfyItemBrModResIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueE_RABMdfyItemBrModResIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_E_RABMdfyItemBrModResIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmPkSztProtIE_SingleCont_E_RABMdfyItemBrModResIEs cmPkSztProtIE_Field_E_RABMdfyItemBrModResIEs


/* 
* FUN : cmPkSztE_RABMdfyLstBrModRes
*  DESC: Function to Pack SztE_RABMdfyLstBrModRes structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABMdfyLstBrModRes
(
SztE_RABMdfyLstBrModRes *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABMdfyLstBrModRes(param, mBuf)
SztE_RABMdfyLstBrModRes *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztE_RABMdfyLstBrModRes) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_SingleCont_E_RABMdfyItemBrModResIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABMdfyLstBrModRes */



/* 
* FUN : cmPkSzt_ValueE_RABMdfyRespIEsCls
*  DESC: Function to Pack Szt_ValueE_RABMdfyRespIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueE_RABMdfyRespIEsCls
(
Szt_ValueE_RABMdfyRespIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueE_RABMdfyRespIEsCls(param, val, mBuf)
Szt_ValueE_RABMdfyRespIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueE_RABMdfyRespIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_E_RABMdfyLstBrModRes:
			CMCHKPK(cmPkSztE_RABMdfyLstBrModRes, &param->u.sztE_RABMdfyLstBrModRes, mBuf);
			break;
		case Sztid_E_RABFailedToMdfyLst:
			CMCHKPK(cmPkSztE_RABLst, &param->u.sztE_RABLst, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKPK(cmPkSztCriticalityDiag, &param->u.sztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueE_RABMdfyRespIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_E_RABMdfyRespIEs
*  DESC: Function to Pack SztProtIE_Field_E_RABMdfyRespIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_E_RABMdfyRespIEs
(
SztProtIE_Field_E_RABMdfyRespIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_E_RABMdfyRespIEs(param, mBuf)
SztProtIE_Field_E_RABMdfyRespIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_E_RABMdfyRespIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueE_RABMdfyRespIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_E_RABMdfyRespIEs */



/* 
* FUN : cmPkSztProtIE_Cont_E_RABMdfyRespIEs
*  DESC: Function to Pack SztProtIE_Cont_E_RABMdfyRespIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_E_RABMdfyRespIEs
(
SztProtIE_Cont_E_RABMdfyRespIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_E_RABMdfyRespIEs(param, mBuf)
SztProtIE_Cont_E_RABMdfyRespIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_E_RABMdfyRespIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_E_RABMdfyRespIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_E_RABMdfyRespIEs */



/* 
* FUN : cmPkSztE_RABMdfyResp
*  DESC: Function to Pack SztE_RABMdfyResp structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABMdfyResp
(
SztE_RABMdfyResp *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABMdfyResp(param, mBuf)
SztE_RABMdfyResp *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztE_RABMdfyResp) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_E_RABMdfyRespIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABMdfyResp */



/* 
* FUN : cmPkSzt_ValueE_RABRlsCmmdIEsCls
*  DESC: Function to Pack Szt_ValueE_RABRlsCmmdIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueE_RABRlsCmmdIEsCls
(
Szt_ValueE_RABRlsCmmdIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueE_RABRlsCmmdIEsCls(param, val, mBuf)
Szt_ValueE_RABRlsCmmdIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueE_RABRlsCmmdIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_uEaggregateMaxBitrate:
			CMCHKPK(cmPkSztUEAggMaxBitrate, &param->u.sztUEAggMaxBitrate, mBuf);
			break;
		case Sztid_E_RABToBeRlsdLst:
			CMCHKPK(cmPkSztE_RABLst, &param->u.sztE_RABLst, mBuf);
			break;
		case Sztid_NAS_PDU:
			CMCHKPK(cmPkSztNAS_PDU, &param->u.sztNAS_PDU, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueE_RABRlsCmmdIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_E_RABRlsCmmdIEs
*  DESC: Function to Pack SztProtIE_Field_E_RABRlsCmmdIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_E_RABRlsCmmdIEs
(
SztProtIE_Field_E_RABRlsCmmdIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_E_RABRlsCmmdIEs(param, mBuf)
SztProtIE_Field_E_RABRlsCmmdIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_E_RABRlsCmmdIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueE_RABRlsCmmdIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_E_RABRlsCmmdIEs */



/* 
* FUN : cmPkSztProtIE_Cont_E_RABRlsCmmdIEs
*  DESC: Function to Pack SztProtIE_Cont_E_RABRlsCmmdIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_E_RABRlsCmmdIEs
(
SztProtIE_Cont_E_RABRlsCmmdIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_E_RABRlsCmmdIEs(param, mBuf)
SztProtIE_Cont_E_RABRlsCmmdIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_E_RABRlsCmmdIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_E_RABRlsCmmdIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_E_RABRlsCmmdIEs */



/* 
* FUN : cmPkSztE_RABRlsCmmd
*  DESC: Function to Pack SztE_RABRlsCmmd structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABRlsCmmd
(
SztE_RABRlsCmmd *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABRlsCmmd(param, mBuf)
SztE_RABRlsCmmd *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztE_RABRlsCmmd) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_E_RABRlsCmmdIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABRlsCmmd */



/* 
* FUN : cmPkSzt_ExtnE_RABRlsItemBrRelCompExtIEsCls
*  DESC: Function to Pack Szt_ExtnE_RABRlsItemBrRelCompExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnE_RABRlsItemBrRelCompExtIEsCls
(
Szt_ExtnE_RABRlsItemBrRelCompExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnE_RABRlsItemBrRelCompExtIEsCls(param, val, mBuf)
Szt_ExtnE_RABRlsItemBrRelCompExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnE_RABRlsItemBrRelCompExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnE_RABRlsItemBrRelCompExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_E_RABRlsItemBrRelCompExtIEs
*  DESC: Function to Pack SztProtExtnField_E_RABRlsItemBrRelCompExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_E_RABRlsItemBrRelCompExtIEs
(
SztProtExtnField_E_RABRlsItemBrRelCompExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_E_RABRlsItemBrRelCompExtIEs(param, mBuf)
SztProtExtnField_E_RABRlsItemBrRelCompExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_E_RABRlsItemBrRelCompExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnE_RABRlsItemBrRelCompExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_E_RABRlsItemBrRelCompExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_E_RABRlsItemBrRelCompExtIEs
*  DESC: Function to Pack SztProtExtnCont_E_RABRlsItemBrRelCompExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_E_RABRlsItemBrRelCompExtIEs
(
SztProtExtnCont_E_RABRlsItemBrRelCompExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_E_RABRlsItemBrRelCompExtIEs(param, mBuf)
SztProtExtnCont_E_RABRlsItemBrRelCompExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_E_RABRlsItemBrRelCompExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_E_RABRlsItemBrRelCompExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_E_RABRlsItemBrRelCompExtIEs */



/* 
* FUN : cmPkSztE_RABRlsItemBrRelComp
*  DESC: Function to Pack SztE_RABRlsItemBrRelComp structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABRlsItemBrRelComp
(
SztE_RABRlsItemBrRelComp *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABRlsItemBrRelComp(param, mBuf)
SztE_RABRlsItemBrRelComp *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztE_RABRlsItemBrRelComp) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_E_RABRlsItemBrRelCompExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABRlsItemBrRelComp */



/* 
* FUN : cmPkSzt_ValueE_RABRlsItemBrRelCompIEsCls
*  DESC: Function to Pack Szt_ValueE_RABRlsItemBrRelCompIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueE_RABRlsItemBrRelCompIEsCls
(
Szt_ValueE_RABRlsItemBrRelCompIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueE_RABRlsItemBrRelCompIEsCls(param, val, mBuf)
Szt_ValueE_RABRlsItemBrRelCompIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueE_RABRlsItemBrRelCompIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABRlsItemBrRelComp:
			CMCHKPK(cmPkSztE_RABRlsItemBrRelComp, &param->u.sztE_RABRlsItemBrRelComp, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueE_RABRlsItemBrRelCompIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_E_RABRlsItemBrRelCompIEs
*  DESC: Function to Pack SztProtIE_Field_E_RABRlsItemBrRelCompIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_E_RABRlsItemBrRelCompIEs
(
SztProtIE_Field_E_RABRlsItemBrRelCompIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_E_RABRlsItemBrRelCompIEs(param, mBuf)
SztProtIE_Field_E_RABRlsItemBrRelCompIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_E_RABRlsItemBrRelCompIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueE_RABRlsItemBrRelCompIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_E_RABRlsItemBrRelCompIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmPkSztProtIE_SingleCont_E_RABRlsItemBrRelCompIEs cmPkSztProtIE_Field_E_RABRlsItemBrRelCompIEs


/* 
* FUN : cmPkSztE_RABRlsLstBrRelComp
*  DESC: Function to Pack SztE_RABRlsLstBrRelComp structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABRlsLstBrRelComp
(
SztE_RABRlsLstBrRelComp *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABRlsLstBrRelComp(param, mBuf)
SztE_RABRlsLstBrRelComp *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztE_RABRlsLstBrRelComp) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_SingleCont_E_RABRlsItemBrRelCompIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABRlsLstBrRelComp */



/* 
* FUN : cmPkSzt_ValueE_RABRlsRespIEsCls
*  DESC: Function to Pack Szt_ValueE_RABRlsRespIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueE_RABRlsRespIEsCls
(
Szt_ValueE_RABRlsRespIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueE_RABRlsRespIEsCls(param, val, mBuf)
Szt_ValueE_RABRlsRespIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueE_RABRlsRespIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_E_RABRlsLstBrRelComp:
			CMCHKPK(cmPkSztE_RABRlsLstBrRelComp, &param->u.sztE_RABRlsLstBrRelComp, mBuf);
			break;
		case Sztid_E_RABFailedToRlsLst:
			CMCHKPK(cmPkSztE_RABLst, &param->u.sztE_RABLst, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKPK(cmPkSztCriticalityDiag, &param->u.sztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueE_RABRlsRespIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_E_RABRlsRespIEs
*  DESC: Function to Pack SztProtIE_Field_E_RABRlsRespIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_E_RABRlsRespIEs
(
SztProtIE_Field_E_RABRlsRespIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_E_RABRlsRespIEs(param, mBuf)
SztProtIE_Field_E_RABRlsRespIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_E_RABRlsRespIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueE_RABRlsRespIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_E_RABRlsRespIEs */



/* 
* FUN : cmPkSztProtIE_Cont_E_RABRlsRespIEs
*  DESC: Function to Pack SztProtIE_Cont_E_RABRlsRespIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_E_RABRlsRespIEs
(
SztProtIE_Cont_E_RABRlsRespIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_E_RABRlsRespIEs(param, mBuf)
SztProtIE_Cont_E_RABRlsRespIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_E_RABRlsRespIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_E_RABRlsRespIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_E_RABRlsRespIEs */



/* 
* FUN : cmPkSztE_RABRlsResp
*  DESC: Function to Pack SztE_RABRlsResp structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABRlsResp
(
SztE_RABRlsResp *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABRlsResp(param, mBuf)
SztE_RABRlsResp *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztE_RABRlsResp) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_E_RABRlsRespIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABRlsResp */



/* 
* FUN : cmPkSzt_ValueE_RABRlsIndIEsCls
*  DESC: Function to Pack Szt_ValueE_RABRlsIndIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueE_RABRlsIndIEsCls
(
Szt_ValueE_RABRlsIndIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueE_RABRlsIndIEsCls(param, val, mBuf)
Szt_ValueE_RABRlsIndIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueE_RABRlsIndIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_E_RABRlsdLst:
			CMCHKPK(cmPkSztE_RABLst, &param->u.sztE_RABLst, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueE_RABRlsIndIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_E_RABRlsIndIEs
*  DESC: Function to Pack SztProtIE_Field_E_RABRlsIndIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_E_RABRlsIndIEs
(
SztProtIE_Field_E_RABRlsIndIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_E_RABRlsIndIEs(param, mBuf)
SztProtIE_Field_E_RABRlsIndIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_E_RABRlsIndIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueE_RABRlsIndIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_E_RABRlsIndIEs */



/* 
* FUN : cmPkSztProtIE_Cont_E_RABRlsIndIEs
*  DESC: Function to Pack SztProtIE_Cont_E_RABRlsIndIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_E_RABRlsIndIEs
(
SztProtIE_Cont_E_RABRlsIndIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_E_RABRlsIndIEs(param, mBuf)
SztProtIE_Cont_E_RABRlsIndIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_E_RABRlsIndIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_E_RABRlsIndIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_E_RABRlsIndIEs */



/* 
* FUN : cmPkSztE_RABRlsInd
*  DESC: Function to Pack SztE_RABRlsInd structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABRlsInd
(
SztE_RABRlsInd *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABRlsInd(param, mBuf)
SztE_RABRlsInd *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztE_RABRlsInd) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_E_RABRlsIndIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABRlsInd */



/* 
* FUN : cmPkSzt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls
*  DESC: Function to Pack Szt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls
(
Szt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls(param, val, mBuf)
Szt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls) 
	
	switch (val)
	{
		case Sztid_Correlation_ID:
			CMCHKPK(cmPkSztCorrelation_ID, &param->u.sztCorrelation_ID, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs
*  DESC: Function to Pack SztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs
(
SztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs(param, mBuf)
SztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs
*  DESC: Function to Pack SztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs
(
SztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs(param, mBuf)
SztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs */



/* 
* FUN : cmPkSztE_RABToBeSetupItemCtxtSUReq
*  DESC: Function to Pack SztE_RABToBeSetupItemCtxtSUReq structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABToBeSetupItemCtxtSUReq
(
SztE_RABToBeSetupItemCtxtSUReq *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABToBeSetupItemCtxtSUReq(param, mBuf)
SztE_RABToBeSetupItemCtxtSUReq *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztE_RABToBeSetupItemCtxtSUReq) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztNAS_PDU, &param->nAS_PDU, mBuf); 
		CMCHKPK(cmPkSztGTP_TEID, &param->gTP_TEID, mBuf); 
		CMCHKPK(cmPkSztTportLyrAddr, &param->transportLyrAddr, mBuf); 
		CMCHKPK(cmPkSztE_RABLvlQoSParams, &param->e_RABlevelQoSParams, mBuf); 
		CMCHKPK(cmPkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABToBeSetupItemCtxtSUReq */



/* 
* FUN : cmPkSzt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls
*  DESC: Function to Pack Szt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls
(
Szt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls(param, val, mBuf)
Szt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABToBeSetupItemCtxtSUReq:
			CMCHKPK(cmPkSztE_RABToBeSetupItemCtxtSUReq, &param->u.sztE_RABToBeSetupItemCtxtSUReq, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs
*  DESC: Function to Pack SztProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs
(
SztProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs(param, mBuf)
SztProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmPkSztProtIE_SingleCont_E_RABToBeSetupItemCtxtSUReqIEs cmPkSztProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs


/* 
* FUN : cmPkSztE_RABToBeSetupLstCtxtSUReq
*  DESC: Function to Pack SztE_RABToBeSetupLstCtxtSUReq structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABToBeSetupLstCtxtSUReq
(
SztE_RABToBeSetupLstCtxtSUReq *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABToBeSetupLstCtxtSUReq(param, mBuf)
SztE_RABToBeSetupLstCtxtSUReq *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztE_RABToBeSetupLstCtxtSUReq) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_SingleCont_E_RABToBeSetupItemCtxtSUReqIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABToBeSetupLstCtxtSUReq */



/* 
* FUN : cmPkSzt_ValueInitCntxtSetupRqstIEsCls
*  DESC: Function to Pack Szt_ValueInitCntxtSetupRqstIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueInitCntxtSetupRqstIEsCls
(
Szt_ValueInitCntxtSetupRqstIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueInitCntxtSetupRqstIEsCls(param, val, mBuf)
Szt_ValueInitCntxtSetupRqstIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueInitCntxtSetupRqstIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztid_MME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_uEaggregateMaxBitrate:
			CMCHKPK(cmPkSztUEAggMaxBitrate, &param->u.sztUEAggMaxBitrate, mBuf);
			break;
		case Sztid_E_RABToBeSetupLstCtxtSUReq:
			CMCHKPK(cmPkSztE_RABToBeSetupLstCtxtSUReq, &param->u.sztE_RABToBeSetupLstCtxtSUReq, mBuf);
			break;
		case Sztid_UESecurCapabilities:
			CMCHKPK(cmPkSztUESecurCapabilities, &param->u.sztUESecurCapabilities, mBuf);
			break;
		case Sztid_SecurKey:
			CMCHKPK(cmPkSztSecurKey, &param->u.sztSecurKey, mBuf);
			break;
		case Sztid_TraceActvn:
			CMCHKPK(cmPkSztTraceActvn, &param->u.sztTraceActvn, mBuf);
			break;
		case Sztid_HovrRestrnLst:
			CMCHKPK(cmPkSztHovrRestrnLst, &param->u.sztHovrRestrnLst, mBuf);
			break;
		case Sztid_UERadioCapblty:
			CMCHKPK(cmPkSztUERadioCapblty, &param->u.sztUERadioCapblty, mBuf);
			break;
		case Sztid_SubscriberProfileIDforRFP:
			CMCHKPK(cmPkSztSubscriberProfileIDforRFP, &param->u.sztSubscriberProfileIDforRFP, mBuf);
			break;
		case Sztid_CSFallbackIndicator:
			CMCHKPK(cmPkSztCSFallbackIndicator, &param->u.sztCSFallbackIndicator, mBuf);
			break;
		case Sztid_SRVCCOperationPossible:
			CMCHKPK(cmPkSztSRVCCOperationPossible, &param->u.sztSRVCCOperationPossible, mBuf);
			break;
		case Sztid_CSGMembershipStatus:
			CMCHKPK(cmPkSztCSGMembershipStatus, &param->u.sztCSGMembershipStatus, mBuf);
			break;
		case Sztid_RegisteredLAI:
			CMCHKPK(cmPkSztLAI, &param->u.sztLAI, mBuf);
			break;
		case Sztid_GUMMEI_ID:
			CMCHKPK(cmPkSztGUMMEI, &param->u.sztGUMMEI, mBuf);
			break;
		case Sztid_MME_UE_S1AP_ID_2:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztid_MME_UE_S1AP_ID_2, mBuf);
			break;
		case Sztid_ManagementBasedMDTAllowed:
			CMCHKPK(cmPkSztManagementBasedMDTAllowed, &param->u.sztManagementBasedMDTAllowed, mBuf);
			break;
		case Sztid_ManagementBasedMDTPLMNLst:
			CMCHKPK(cmPkSztMDTPLMNLst, &param->u.sztMDTPLMNLst, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueInitCntxtSetupRqstIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_InitCntxtSetupRqstIEs
*  DESC: Function to Pack SztProtIE_Field_InitCntxtSetupRqstIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_InitCntxtSetupRqstIEs
(
SztProtIE_Field_InitCntxtSetupRqstIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_InitCntxtSetupRqstIEs(param, mBuf)
SztProtIE_Field_InitCntxtSetupRqstIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_InitCntxtSetupRqstIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueInitCntxtSetupRqstIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_InitCntxtSetupRqstIEs */



/* 
* FUN : cmPkSztProtIE_Cont_InitCntxtSetupRqstIEs
*  DESC: Function to Pack SztProtIE_Cont_InitCntxtSetupRqstIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_InitCntxtSetupRqstIEs
(
SztProtIE_Cont_InitCntxtSetupRqstIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_InitCntxtSetupRqstIEs(param, mBuf)
SztProtIE_Cont_InitCntxtSetupRqstIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_InitCntxtSetupRqstIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_InitCntxtSetupRqstIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_InitCntxtSetupRqstIEs */



/* 
* FUN : cmPkSztInitCntxtSetupRqst
*  DESC: Function to Pack SztInitCntxtSetupRqst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztInitCntxtSetupRqst
(
SztInitCntxtSetupRqst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztInitCntxtSetupRqst(param, mBuf)
SztInitCntxtSetupRqst *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztInitCntxtSetupRqst) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_InitCntxtSetupRqstIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztInitCntxtSetupRqst */



/* 
* FUN : cmPkSzt_ExtnE_RABSetupItemCtxtSUResExtIEsCls
*  DESC: Function to Pack Szt_ExtnE_RABSetupItemCtxtSUResExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnE_RABSetupItemCtxtSUResExtIEsCls
(
Szt_ExtnE_RABSetupItemCtxtSUResExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnE_RABSetupItemCtxtSUResExtIEsCls(param, val, mBuf)
Szt_ExtnE_RABSetupItemCtxtSUResExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnE_RABSetupItemCtxtSUResExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnE_RABSetupItemCtxtSUResExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_E_RABSetupItemCtxtSUResExtIEs
*  DESC: Function to Pack SztProtExtnField_E_RABSetupItemCtxtSUResExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_E_RABSetupItemCtxtSUResExtIEs
(
SztProtExtnField_E_RABSetupItemCtxtSUResExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_E_RABSetupItemCtxtSUResExtIEs(param, mBuf)
SztProtExtnField_E_RABSetupItemCtxtSUResExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_E_RABSetupItemCtxtSUResExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnE_RABSetupItemCtxtSUResExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_E_RABSetupItemCtxtSUResExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs
*  DESC: Function to Pack SztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs
(
SztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs(param, mBuf)
SztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_E_RABSetupItemCtxtSUResExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs */



/* 
* FUN : cmPkSztE_RABSetupItemCtxtSURes
*  DESC: Function to Pack SztE_RABSetupItemCtxtSURes structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABSetupItemCtxtSURes
(
SztE_RABSetupItemCtxtSURes *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABSetupItemCtxtSURes(param, mBuf)
SztE_RABSetupItemCtxtSURes *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztE_RABSetupItemCtxtSURes) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztGTP_TEID, &param->gTP_TEID, mBuf); 
		CMCHKPK(cmPkSztTportLyrAddr, &param->transportLyrAddr, mBuf); 
		CMCHKPK(cmPkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABSetupItemCtxtSURes */



/* 
* FUN : cmPkSzt_ValueE_RABSetupItemCtxtSUResIEsCls
*  DESC: Function to Pack Szt_ValueE_RABSetupItemCtxtSUResIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueE_RABSetupItemCtxtSUResIEsCls
(
Szt_ValueE_RABSetupItemCtxtSUResIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueE_RABSetupItemCtxtSUResIEsCls(param, val, mBuf)
Szt_ValueE_RABSetupItemCtxtSUResIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueE_RABSetupItemCtxtSUResIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABSetupItemCtxtSURes:
			CMCHKPK(cmPkSztE_RABSetupItemCtxtSURes, &param->u.sztE_RABSetupItemCtxtSURes, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueE_RABSetupItemCtxtSUResIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_E_RABSetupItemCtxtSUResIEs
*  DESC: Function to Pack SztProtIE_Field_E_RABSetupItemCtxtSUResIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_E_RABSetupItemCtxtSUResIEs
(
SztProtIE_Field_E_RABSetupItemCtxtSUResIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_E_RABSetupItemCtxtSUResIEs(param, mBuf)
SztProtIE_Field_E_RABSetupItemCtxtSUResIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_E_RABSetupItemCtxtSUResIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueE_RABSetupItemCtxtSUResIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_E_RABSetupItemCtxtSUResIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmPkSztProtIE_SingleCont_E_RABSetupItemCtxtSUResIEs cmPkSztProtIE_Field_E_RABSetupItemCtxtSUResIEs


/* 
* FUN : cmPkSztE_RABSetupLstCtxtSURes
*  DESC: Function to Pack SztE_RABSetupLstCtxtSURes structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztE_RABSetupLstCtxtSURes
(
SztE_RABSetupLstCtxtSURes *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztE_RABSetupLstCtxtSURes(param, mBuf)
SztE_RABSetupLstCtxtSURes *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztE_RABSetupLstCtxtSURes) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_SingleCont_E_RABSetupItemCtxtSUResIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztE_RABSetupLstCtxtSURes */



/* 
* FUN : cmPkSzt_ValueInitCntxtSetupRespIEsCls
*  DESC: Function to Pack Szt_ValueInitCntxtSetupRespIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueInitCntxtSetupRespIEsCls
(
Szt_ValueInitCntxtSetupRespIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueInitCntxtSetupRespIEsCls(param, val, mBuf)
Szt_ValueInitCntxtSetupRespIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueInitCntxtSetupRespIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_E_RABSetupLstCtxtSURes:
			CMCHKPK(cmPkSztE_RABSetupLstCtxtSURes, &param->u.sztE_RABSetupLstCtxtSURes, mBuf);
			break;
		case Sztid_E_RABFailedToSetupLstCtxtSURes:
			CMCHKPK(cmPkSztE_RABLst, &param->u.sztE_RABLst, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKPK(cmPkSztCriticalityDiag, &param->u.sztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueInitCntxtSetupRespIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_InitCntxtSetupRespIEs
*  DESC: Function to Pack SztProtIE_Field_InitCntxtSetupRespIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_InitCntxtSetupRespIEs
(
SztProtIE_Field_InitCntxtSetupRespIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_InitCntxtSetupRespIEs(param, mBuf)
SztProtIE_Field_InitCntxtSetupRespIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_InitCntxtSetupRespIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueInitCntxtSetupRespIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_InitCntxtSetupRespIEs */



/* 
* FUN : cmPkSztProtIE_Cont_InitCntxtSetupRespIEs
*  DESC: Function to Pack SztProtIE_Cont_InitCntxtSetupRespIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_InitCntxtSetupRespIEs
(
SztProtIE_Cont_InitCntxtSetupRespIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_InitCntxtSetupRespIEs(param, mBuf)
SztProtIE_Cont_InitCntxtSetupRespIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_InitCntxtSetupRespIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_InitCntxtSetupRespIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_InitCntxtSetupRespIEs */



/* 
* FUN : cmPkSztInitCntxtSetupResp
*  DESC: Function to Pack SztInitCntxtSetupResp structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztInitCntxtSetupResp
(
SztInitCntxtSetupResp *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztInitCntxtSetupResp(param, mBuf)
SztInitCntxtSetupResp *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztInitCntxtSetupResp) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_InitCntxtSetupRespIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztInitCntxtSetupResp */



/* 
* FUN : cmPkSzt_ValueInitCntxtSetupFailIEsCls
*  DESC: Function to Pack Szt_ValueInitCntxtSetupFailIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueInitCntxtSetupFailIEsCls
(
Szt_ValueInitCntxtSetupFailIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueInitCntxtSetupFailIEsCls(param, val, mBuf)
Szt_ValueInitCntxtSetupFailIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueInitCntxtSetupFailIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_Cause:
			CMCHKPK(cmPkSztCause, &param->u.sztCause, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKPK(cmPkSztCriticalityDiag, &param->u.sztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueInitCntxtSetupFailIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_InitCntxtSetupFailIEs
*  DESC: Function to Pack SztProtIE_Field_InitCntxtSetupFailIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_InitCntxtSetupFailIEs
(
SztProtIE_Field_InitCntxtSetupFailIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_InitCntxtSetupFailIEs(param, mBuf)
SztProtIE_Field_InitCntxtSetupFailIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_InitCntxtSetupFailIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueInitCntxtSetupFailIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_InitCntxtSetupFailIEs */



/* 
* FUN : cmPkSztProtIE_Cont_InitCntxtSetupFailIEs
*  DESC: Function to Pack SztProtIE_Cont_InitCntxtSetupFailIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_InitCntxtSetupFailIEs
(
SztProtIE_Cont_InitCntxtSetupFailIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_InitCntxtSetupFailIEs(param, mBuf)
SztProtIE_Cont_InitCntxtSetupFailIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_InitCntxtSetupFailIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_InitCntxtSetupFailIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_InitCntxtSetupFailIEs */



/* 
* FUN : cmPkSztInitCntxtSetupFail
*  DESC: Function to Pack SztInitCntxtSetupFail structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztInitCntxtSetupFail
(
SztInitCntxtSetupFail *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztInitCntxtSetupFail(param, mBuf)
SztInitCntxtSetupFail *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztInitCntxtSetupFail) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_InitCntxtSetupFailIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztInitCntxtSetupFail */



/* 
* FUN : cmPkSzt_ExtnTAIItemExtIEsCls
*  DESC: Function to Pack Szt_ExtnTAIItemExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ExtnTAIItemExtIEsCls
(
Szt_ExtnTAIItemExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ExtnTAIItemExtIEsCls(param, val, mBuf)
Szt_ExtnTAIItemExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ExtnTAIItemExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ExtnTAIItemExtIEsCls */



/* 
* FUN : cmPkSztProtExtnField_TAIItemExtIEs
*  DESC: Function to Pack SztProtExtnField_TAIItemExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnField_TAIItemExtIEs
(
SztProtExtnField_TAIItemExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnField_TAIItemExtIEs(param, mBuf)
SztProtExtnField_TAIItemExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtExtnField_TAIItemExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ExtnTAIItemExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtExtnID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnField_TAIItemExtIEs */



/* 
* FUN : cmPkSztProtExtnCont_TAIItemExtIEs
*  DESC: Function to Pack SztProtExtnCont_TAIItemExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtExtnCont_TAIItemExtIEs
(
SztProtExtnCont_TAIItemExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtExtnCont_TAIItemExtIEs(param, mBuf)
SztProtExtnCont_TAIItemExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtExtnCont_TAIItemExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtExtnField_TAIItemExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtExtnCont_TAIItemExtIEs */



/* 
* FUN : cmPkSztTAIItem
*  DESC: Function to Pack SztTAIItem structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztTAIItem
(
SztTAIItem *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztTAIItem(param, mBuf)
SztTAIItem *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztTAIItem) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtExtnCont_TAIItemExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkSztTAI, &param->tAI, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztTAIItem */



/* 
* FUN : cmPkSzt_ValueTAIItemIEsCls
*  DESC: Function to Pack Szt_ValueTAIItemIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueTAIItemIEsCls
(
Szt_ValueTAIItemIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueTAIItemIEsCls(param, val, mBuf)
Szt_ValueTAIItemIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueTAIItemIEsCls) 
	
	switch (val)
	{
		case Sztid_TAIItem:
			CMCHKPK(cmPkSztTAIItem, &param->u.sztTAIItem, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueTAIItemIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_TAIItemIEs
*  DESC: Function to Pack SztProtIE_Field_TAIItemIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_TAIItemIEs
(
SztProtIE_Field_TAIItemIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_TAIItemIEs(param, mBuf)
SztProtIE_Field_TAIItemIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_TAIItemIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueTAIItemIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_TAIItemIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmPkSztProtIE_SingleCont_TAIItemIEs cmPkSztProtIE_Field_TAIItemIEs


/* 
* FUN : cmPkSztTAILst
*  DESC: Function to Pack SztTAILst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztTAILst
(
SztTAILst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztTAILst(param, mBuf)
SztTAILst *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztTAILst) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_SingleCont_TAIItemIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztTAILst */



/* 
* FUN : cmPkSzt_ValuePagIEsCls
*  DESC: Function to Pack Szt_ValuePagIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValuePagIEsCls
(
Szt_ValuePagIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValuePagIEsCls(param, val, mBuf)
Szt_ValuePagIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValuePagIEsCls) 
	
	switch (val)
	{
		case Sztid_UEIdentityIdxValue:
			CMCHKPK(cmPkSztUEIdentityIdxValue, &param->u.sztUEIdentityIdxValue, mBuf);
			break;
		case Sztid_UEPagID:
			CMCHKPK(cmPkSztUEPagID, &param->u.sztUEPagID, mBuf);
			break;
		case Sztid_pagingDRX:
			CMCHKPK(cmPkSztPagDRX, &param->u.sztPagDRX, mBuf);
			break;
		case Sztid_CNDomain:
			CMCHKPK(cmPkSztCNDomain, &param->u.sztCNDomain, mBuf);
			break;
		case Sztid_TAILst:
			CMCHKPK(cmPkSztTAILst, &param->u.sztTAILst, mBuf);
			break;
		case Sztid_CSG_IdLst:
			CMCHKPK(cmPkSztCSG_IdLst, &param->u.sztCSG_IdLst, mBuf);
			break;
		case Sztid_PagPriority:
			CMCHKPK(cmPkSztPagPriority, &param->u.sztPagPriority, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValuePagIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_PagIEs
*  DESC: Function to Pack SztProtIE_Field_PagIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_PagIEs
(
SztProtIE_Field_PagIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_PagIEs(param, mBuf)
SztProtIE_Field_PagIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_PagIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValuePagIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_PagIEs */



/* 
* FUN : cmPkSztProtIE_Cont_PagIEs
*  DESC: Function to Pack SztProtIE_Cont_PagIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_PagIEs
(
SztProtIE_Cont_PagIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_PagIEs(param, mBuf)
SztProtIE_Cont_PagIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_PagIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_PagIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_PagIEs */



/* 
* FUN : cmPkSztPag
*  DESC: Function to Pack SztPag structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztPag
(
SztPag *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztPag(param, mBuf)
SztPag *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztPag) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_PagIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztPag */



/* 
* FUN : cmPkSzt_ValueUECntxtRlsRqst_IEsCls
*  DESC: Function to Pack Szt_ValueUECntxtRlsRqst_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueUECntxtRlsRqst_IEsCls
(
Szt_ValueUECntxtRlsRqst_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueUECntxtRlsRqst_IEsCls(param, val, mBuf)
Szt_ValueUECntxtRlsRqst_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueUECntxtRlsRqst_IEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_Cause:
			CMCHKPK(cmPkSztCause, &param->u.sztCause, mBuf);
			break;
		case Sztid_GWCntxtRlsInd:
			CMCHKPK(cmPkSztGWCntxtRlsInd, &param->u.sztGWCntxtRlsInd, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueUECntxtRlsRqst_IEsCls */



/* 
* FUN : cmPkSztProtIE_Field_UECntxtRlsRqst_IEs
*  DESC: Function to Pack SztProtIE_Field_UECntxtRlsRqst_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_UECntxtRlsRqst_IEs
(
SztProtIE_Field_UECntxtRlsRqst_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_UECntxtRlsRqst_IEs(param, mBuf)
SztProtIE_Field_UECntxtRlsRqst_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_UECntxtRlsRqst_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueUECntxtRlsRqst_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_UECntxtRlsRqst_IEs */



/* 
* FUN : cmPkSztProtIE_Cont_UECntxtRlsRqst_IEs
*  DESC: Function to Pack SztProtIE_Cont_UECntxtRlsRqst_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_UECntxtRlsRqst_IEs
(
SztProtIE_Cont_UECntxtRlsRqst_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_UECntxtRlsRqst_IEs(param, mBuf)
SztProtIE_Cont_UECntxtRlsRqst_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_UECntxtRlsRqst_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_UECntxtRlsRqst_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_UECntxtRlsRqst_IEs */



/* 
* FUN : cmPkSztUECntxtRlsRqst
*  DESC: Function to Pack SztUECntxtRlsRqst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztUECntxtRlsRqst
(
SztUECntxtRlsRqst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztUECntxtRlsRqst(param, mBuf)
SztUECntxtRlsRqst *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztUECntxtRlsRqst) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_UECntxtRlsRqst_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztUECntxtRlsRqst */



/* 
* FUN : cmPkSzt_ValueUECntxtRlsCmmd_IEsCls
*  DESC: Function to Pack Szt_ValueUECntxtRlsCmmd_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueUECntxtRlsCmmd_IEsCls
(
Szt_ValueUECntxtRlsCmmd_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueUECntxtRlsCmmd_IEsCls(param, val, mBuf)
Szt_ValueUECntxtRlsCmmd_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueUECntxtRlsCmmd_IEsCls) 
	
	switch (val)
	{
		case Sztid_UE_S1AP_IDs:
			CMCHKPK(cmPkSztUE_S1AP_IDs, &param->u.sztUE_S1AP_IDs, mBuf);
			break;
		case Sztid_Cause:
			CMCHKPK(cmPkSztCause, &param->u.sztCause, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueUECntxtRlsCmmd_IEsCls */



/* 
* FUN : cmPkSztProtIE_Field_UECntxtRlsCmmd_IEs
*  DESC: Function to Pack SztProtIE_Field_UECntxtRlsCmmd_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_UECntxtRlsCmmd_IEs
(
SztProtIE_Field_UECntxtRlsCmmd_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_UECntxtRlsCmmd_IEs(param, mBuf)
SztProtIE_Field_UECntxtRlsCmmd_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_UECntxtRlsCmmd_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueUECntxtRlsCmmd_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_UECntxtRlsCmmd_IEs */



/* 
* FUN : cmPkSztProtIE_Cont_UECntxtRlsCmmd_IEs
*  DESC: Function to Pack SztProtIE_Cont_UECntxtRlsCmmd_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_UECntxtRlsCmmd_IEs
(
SztProtIE_Cont_UECntxtRlsCmmd_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_UECntxtRlsCmmd_IEs(param, mBuf)
SztProtIE_Cont_UECntxtRlsCmmd_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_UECntxtRlsCmmd_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_UECntxtRlsCmmd_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_UECntxtRlsCmmd_IEs */



/* 
* FUN : cmPkSztUECntxtRlsCmmd
*  DESC: Function to Pack SztUECntxtRlsCmmd structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztUECntxtRlsCmmd
(
SztUECntxtRlsCmmd *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztUECntxtRlsCmmd(param, mBuf)
SztUECntxtRlsCmmd *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztUECntxtRlsCmmd) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_UECntxtRlsCmmd_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztUECntxtRlsCmmd */



/* 
* FUN : cmPkSzt_ValueUECntxtRlsComplete_IEsCls
*  DESC: Function to Pack Szt_ValueUECntxtRlsComplete_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueUECntxtRlsComplete_IEsCls
(
Szt_ValueUECntxtRlsComplete_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueUECntxtRlsComplete_IEsCls(param, val, mBuf)
Szt_ValueUECntxtRlsComplete_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueUECntxtRlsComplete_IEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKPK(cmPkSztCriticalityDiag, &param->u.sztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueUECntxtRlsComplete_IEsCls */



/* 
* FUN : cmPkSztProtIE_Field_UECntxtRlsComplete_IEs
*  DESC: Function to Pack SztProtIE_Field_UECntxtRlsComplete_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_UECntxtRlsComplete_IEs
(
SztProtIE_Field_UECntxtRlsComplete_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_UECntxtRlsComplete_IEs(param, mBuf)
SztProtIE_Field_UECntxtRlsComplete_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_UECntxtRlsComplete_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueUECntxtRlsComplete_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_UECntxtRlsComplete_IEs */



/* 
* FUN : cmPkSztProtIE_Cont_UECntxtRlsComplete_IEs
*  DESC: Function to Pack SztProtIE_Cont_UECntxtRlsComplete_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_UECntxtRlsComplete_IEs
(
SztProtIE_Cont_UECntxtRlsComplete_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_UECntxtRlsComplete_IEs(param, mBuf)
SztProtIE_Cont_UECntxtRlsComplete_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_UECntxtRlsComplete_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_UECntxtRlsComplete_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_UECntxtRlsComplete_IEs */



/* 
* FUN : cmPkSztUECntxtRlsComplete
*  DESC: Function to Pack SztUECntxtRlsComplete structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztUECntxtRlsComplete
(
SztUECntxtRlsComplete *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztUECntxtRlsComplete(param, mBuf)
SztUECntxtRlsComplete *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztUECntxtRlsComplete) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_UECntxtRlsComplete_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztUECntxtRlsComplete */



/* 
* FUN : cmPkSzt_ValueUECntxtModificationRqstIEsCls
*  DESC: Function to Pack Szt_ValueUECntxtModificationRqstIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueUECntxtModificationRqstIEsCls
(
Szt_ValueUECntxtModificationRqstIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueUECntxtModificationRqstIEsCls(param, val, mBuf)
Szt_ValueUECntxtModificationRqstIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueUECntxtModificationRqstIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_SecurKey:
			CMCHKPK(cmPkSztSecurKey, &param->u.sztSecurKey, mBuf);
			break;
		case Sztid_SubscriberProfileIDforRFP:
			CMCHKPK(cmPkSztSubscriberProfileIDforRFP, &param->u.sztSubscriberProfileIDforRFP, mBuf);
			break;
		case Sztid_uEaggregateMaxBitrate:
			CMCHKPK(cmPkSztUEAggMaxBitrate, &param->u.sztUEAggMaxBitrate, mBuf);
			break;
		case Sztid_CSFallbackIndicator:
			CMCHKPK(cmPkSztCSFallbackIndicator, &param->u.sztCSFallbackIndicator, mBuf);
			break;
		case Sztid_UESecurCapabilities:
			CMCHKPK(cmPkSztUESecurCapabilities, &param->u.sztUESecurCapabilities, mBuf);
			break;
		case Sztid_CSGMembershipStatus:
			CMCHKPK(cmPkSztCSGMembershipStatus, &param->u.sztCSGMembershipStatus, mBuf);
			break;
		case Sztid_RegisteredLAI:
			CMCHKPK(cmPkSztLAI, &param->u.sztLAI, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueUECntxtModificationRqstIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_UECntxtModificationRqstIEs
*  DESC: Function to Pack SztProtIE_Field_UECntxtModificationRqstIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_UECntxtModificationRqstIEs
(
SztProtIE_Field_UECntxtModificationRqstIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_UECntxtModificationRqstIEs(param, mBuf)
SztProtIE_Field_UECntxtModificationRqstIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_UECntxtModificationRqstIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueUECntxtModificationRqstIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_UECntxtModificationRqstIEs */



/* 
* FUN : cmPkSztProtIE_Cont_UECntxtModificationRqstIEs
*  DESC: Function to Pack SztProtIE_Cont_UECntxtModificationRqstIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_UECntxtModificationRqstIEs
(
SztProtIE_Cont_UECntxtModificationRqstIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_UECntxtModificationRqstIEs(param, mBuf)
SztProtIE_Cont_UECntxtModificationRqstIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_UECntxtModificationRqstIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_UECntxtModificationRqstIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_UECntxtModificationRqstIEs */



/* 
* FUN : cmPkSztUECntxtModificationRqst
*  DESC: Function to Pack SztUECntxtModificationRqst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztUECntxtModificationRqst
(
SztUECntxtModificationRqst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztUECntxtModificationRqst(param, mBuf)
SztUECntxtModificationRqst *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztUECntxtModificationRqst) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_UECntxtModificationRqstIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztUECntxtModificationRqst */



/* 
* FUN : cmPkSzt_ValueUECntxtModificationRespIEsCls
*  DESC: Function to Pack Szt_ValueUECntxtModificationRespIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueUECntxtModificationRespIEsCls
(
Szt_ValueUECntxtModificationRespIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueUECntxtModificationRespIEsCls(param, val, mBuf)
Szt_ValueUECntxtModificationRespIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueUECntxtModificationRespIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKPK(cmPkSztCriticalityDiag, &param->u.sztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueUECntxtModificationRespIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_UECntxtModificationRespIEs
*  DESC: Function to Pack SztProtIE_Field_UECntxtModificationRespIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_UECntxtModificationRespIEs
(
SztProtIE_Field_UECntxtModificationRespIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_UECntxtModificationRespIEs(param, mBuf)
SztProtIE_Field_UECntxtModificationRespIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_UECntxtModificationRespIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueUECntxtModificationRespIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_UECntxtModificationRespIEs */



/* 
* FUN : cmPkSztProtIE_Cont_UECntxtModificationRespIEs
*  DESC: Function to Pack SztProtIE_Cont_UECntxtModificationRespIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_UECntxtModificationRespIEs
(
SztProtIE_Cont_UECntxtModificationRespIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_UECntxtModificationRespIEs(param, mBuf)
SztProtIE_Cont_UECntxtModificationRespIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_UECntxtModificationRespIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_UECntxtModificationRespIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_UECntxtModificationRespIEs */



/* 
* FUN : cmPkSztUECntxtModificationResp
*  DESC: Function to Pack SztUECntxtModificationResp structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztUECntxtModificationResp
(
SztUECntxtModificationResp *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztUECntxtModificationResp(param, mBuf)
SztUECntxtModificationResp *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztUECntxtModificationResp) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_UECntxtModificationRespIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztUECntxtModificationResp */



/* 
* FUN : cmPkSzt_ValueUECntxtModificationFailIEsCls
*  DESC: Function to Pack Szt_ValueUECntxtModificationFailIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueUECntxtModificationFailIEsCls
(
Szt_ValueUECntxtModificationFailIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueUECntxtModificationFailIEsCls(param, val, mBuf)
Szt_ValueUECntxtModificationFailIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueUECntxtModificationFailIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_Cause:
			CMCHKPK(cmPkSztCause, &param->u.sztCause, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKPK(cmPkSztCriticalityDiag, &param->u.sztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueUECntxtModificationFailIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_UECntxtModificationFailIEs
*  DESC: Function to Pack SztProtIE_Field_UECntxtModificationFailIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_UECntxtModificationFailIEs
(
SztProtIE_Field_UECntxtModificationFailIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_UECntxtModificationFailIEs(param, mBuf)
SztProtIE_Field_UECntxtModificationFailIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_UECntxtModificationFailIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueUECntxtModificationFailIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_UECntxtModificationFailIEs */



/* 
* FUN : cmPkSztProtIE_Cont_UECntxtModificationFailIEs
*  DESC: Function to Pack SztProtIE_Cont_UECntxtModificationFailIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_UECntxtModificationFailIEs
(
SztProtIE_Cont_UECntxtModificationFailIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_UECntxtModificationFailIEs(param, mBuf)
SztProtIE_Cont_UECntxtModificationFailIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_UECntxtModificationFailIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_UECntxtModificationFailIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_UECntxtModificationFailIEs */



/* 
* FUN : cmPkSztUECntxtModificationFail
*  DESC: Function to Pack SztUECntxtModificationFail structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztUECntxtModificationFail
(
SztUECntxtModificationFail *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztUECntxtModificationFail(param, mBuf)
SztUECntxtModificationFail *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztUECntxtModificationFail) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_UECntxtModificationFailIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztUECntxtModificationFail */



/* 
* FUN : cmPkSzt_ValueUERadioCapbltyMatchRqstIEsCls
*  DESC: Function to Pack Szt_ValueUERadioCapbltyMatchRqstIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueUERadioCapbltyMatchRqstIEsCls
(
Szt_ValueUERadioCapbltyMatchRqstIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueUERadioCapbltyMatchRqstIEsCls(param, val, mBuf)
Szt_ValueUERadioCapbltyMatchRqstIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueUERadioCapbltyMatchRqstIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_UERadioCapblty:
			CMCHKPK(cmPkSztUERadioCapblty, &param->u.sztUERadioCapblty, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueUERadioCapbltyMatchRqstIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_UERadioCapbltyMatchRqstIEs
*  DESC: Function to Pack SztProtIE_Field_UERadioCapbltyMatchRqstIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_UERadioCapbltyMatchRqstIEs
(
SztProtIE_Field_UERadioCapbltyMatchRqstIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_UERadioCapbltyMatchRqstIEs(param, mBuf)
SztProtIE_Field_UERadioCapbltyMatchRqstIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_UERadioCapbltyMatchRqstIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueUERadioCapbltyMatchRqstIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_UERadioCapbltyMatchRqstIEs */



/* 
* FUN : cmPkSztProtIE_Cont_UERadioCapbltyMatchRqstIEs
*  DESC: Function to Pack SztProtIE_Cont_UERadioCapbltyMatchRqstIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_UERadioCapbltyMatchRqstIEs
(
SztProtIE_Cont_UERadioCapbltyMatchRqstIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_UERadioCapbltyMatchRqstIEs(param, mBuf)
SztProtIE_Cont_UERadioCapbltyMatchRqstIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_UERadioCapbltyMatchRqstIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_UERadioCapbltyMatchRqstIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_UERadioCapbltyMatchRqstIEs */



/* 
* FUN : cmPkSztUERadioCapbltyMatchRqst
*  DESC: Function to Pack SztUERadioCapbltyMatchRqst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztUERadioCapbltyMatchRqst
(
SztUERadioCapbltyMatchRqst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztUERadioCapbltyMatchRqst(param, mBuf)
SztUERadioCapbltyMatchRqst *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztUERadioCapbltyMatchRqst) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_UERadioCapbltyMatchRqstIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztUERadioCapbltyMatchRqst */



/* 
* FUN : cmPkSzt_ValueUERadioCapbltyMatchRespIEsCls
*  DESC: Function to Pack Szt_ValueUERadioCapbltyMatchRespIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueUERadioCapbltyMatchRespIEsCls
(
Szt_ValueUERadioCapbltyMatchRespIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueUERadioCapbltyMatchRespIEsCls(param, val, mBuf)
Szt_ValueUERadioCapbltyMatchRespIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueUERadioCapbltyMatchRespIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_VoiceSupportMatchIndicator:
			CMCHKPK(cmPkSztVoiceSupportMatchIndicator, &param->u.sztVoiceSupportMatchIndicator, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKPK(cmPkSztCriticalityDiag, &param->u.sztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueUERadioCapbltyMatchRespIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_UERadioCapbltyMatchRespIEs
*  DESC: Function to Pack SztProtIE_Field_UERadioCapbltyMatchRespIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_UERadioCapbltyMatchRespIEs
(
SztProtIE_Field_UERadioCapbltyMatchRespIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_UERadioCapbltyMatchRespIEs(param, mBuf)
SztProtIE_Field_UERadioCapbltyMatchRespIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_UERadioCapbltyMatchRespIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueUERadioCapbltyMatchRespIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_UERadioCapbltyMatchRespIEs */



/* 
* FUN : cmPkSztProtIE_Cont_UERadioCapbltyMatchRespIEs
*  DESC: Function to Pack SztProtIE_Cont_UERadioCapbltyMatchRespIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_UERadioCapbltyMatchRespIEs
(
SztProtIE_Cont_UERadioCapbltyMatchRespIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_UERadioCapbltyMatchRespIEs(param, mBuf)
SztProtIE_Cont_UERadioCapbltyMatchRespIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_UERadioCapbltyMatchRespIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_UERadioCapbltyMatchRespIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_UERadioCapbltyMatchRespIEs */



/* 
* FUN : cmPkSztUERadioCapbltyMatchResp
*  DESC: Function to Pack SztUERadioCapbltyMatchResp structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztUERadioCapbltyMatchResp
(
SztUERadioCapbltyMatchResp *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztUERadioCapbltyMatchResp(param, mBuf)
SztUERadioCapbltyMatchResp *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztUERadioCapbltyMatchResp) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_UERadioCapbltyMatchRespIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztUERadioCapbltyMatchResp */



/* 
* FUN : cmPkSzt_ValueDlnkNASTport_IEsCls
*  DESC: Function to Pack Szt_ValueDlnkNASTport_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueDlnkNASTport_IEsCls
(
Szt_ValueDlnkNASTport_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueDlnkNASTport_IEsCls(param, val, mBuf)
Szt_ValueDlnkNASTport_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueDlnkNASTport_IEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_NAS_PDU:
			CMCHKPK(cmPkSztNAS_PDU, &param->u.sztNAS_PDU, mBuf);
			break;
		case Sztid_HovrRestrnLst:
			CMCHKPK(cmPkSztHovrRestrnLst, &param->u.sztHovrRestrnLst, mBuf);
			break;
		case Sztid_SubscriberProfileIDforRFP:
			CMCHKPK(cmPkSztSubscriberProfileIDforRFP, &param->u.sztSubscriberProfileIDforRFP, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueDlnkNASTport_IEsCls */



/* 
* FUN : cmPkSztProtIE_Field_DlnkNASTport_IEs
*  DESC: Function to Pack SztProtIE_Field_DlnkNASTport_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_DlnkNASTport_IEs
(
SztProtIE_Field_DlnkNASTport_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_DlnkNASTport_IEs(param, mBuf)
SztProtIE_Field_DlnkNASTport_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_DlnkNASTport_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueDlnkNASTport_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_DlnkNASTport_IEs */



/* 
* FUN : cmPkSztProtIE_Cont_DlnkNASTport_IEs
*  DESC: Function to Pack SztProtIE_Cont_DlnkNASTport_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_DlnkNASTport_IEs
(
SztProtIE_Cont_DlnkNASTport_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_DlnkNASTport_IEs(param, mBuf)
SztProtIE_Cont_DlnkNASTport_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_DlnkNASTport_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_DlnkNASTport_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_DlnkNASTport_IEs */



/* 
* FUN : cmPkSztDlnkNASTport
*  DESC: Function to Pack SztDlnkNASTport structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztDlnkNASTport
(
SztDlnkNASTport *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztDlnkNASTport(param, mBuf)
SztDlnkNASTport *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztDlnkNASTport) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_DlnkNASTport_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztDlnkNASTport */



/* 
* FUN : cmPkSzt_ValueInitUEMsg_IEsCls
*  DESC: Function to Pack Szt_ValueInitUEMsg_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueInitUEMsg_IEsCls
(
Szt_ValueInitUEMsg_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueInitUEMsg_IEsCls(param, val, mBuf)
Szt_ValueInitUEMsg_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueInitUEMsg_IEsCls) 
	
	switch (val)
	{
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_NAS_PDU:
			CMCHKPK(cmPkSztNAS_PDU, &param->u.sztNAS_PDU, mBuf);
			break;
		case Sztid_TAI:
			CMCHKPK(cmPkSztTAI, &param->u.sztTAI, mBuf);
			break;
		case Sztid_EUTRAN_CGI:
			CMCHKPK(cmPkSztEUTRAN_CGI, &param->u.sztEUTRAN_CGI, mBuf);
			break;
		case Sztid_RRC_Establishment_Cause:
			CMCHKPK(cmPkSztRRC_Establishment_Cause, &param->u.sztRRC_Establishment_Cause, mBuf);
			break;
		case Sztid_S_TMSI:
			CMCHKPK(cmPkSztS_TMSI, &param->u.sztS_TMSI, mBuf);
			break;
		case Sztid_CSG_Id:
			CMCHKPK(cmPkSztCSG_Id, &param->u.sztCSG_Id, mBuf);
			break;
		case Sztid_GUMMEI_ID:
			CMCHKPK(cmPkSztGUMMEI, &param->u.sztGUMMEI, mBuf);
			break;
		case Sztid_CellAccessMode:
			CMCHKPK(cmPkSztCellAccessMode, &param->u.sztCellAccessMode, mBuf);
			break;
		case Sztid_GW_TportLyrAddr:
			CMCHKPK(cmPkSztTportLyrAddr, &param->u.sztTportLyrAddr, mBuf);
			break;
		case Sztid_RelayNode_Indicator:
			CMCHKPK(cmPkSztRelayNode_Indicator, &param->u.sztRelayNode_Indicator, mBuf);
			break;
		case Sztid_GUMMEITyp:
			CMCHKPK(cmPkSztGUMMEITyp, &param->u.sztGUMMEITyp, mBuf);
			break;
		case Sztid_Tunnel_Inform_for_BBF:
			CMCHKPK(cmPkSztTunnelInform, &param->u.sztTunnelInform, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueInitUEMsg_IEsCls */



/* 
* FUN : cmPkSztProtIE_Field_InitUEMsg_IEs
*  DESC: Function to Pack SztProtIE_Field_InitUEMsg_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_InitUEMsg_IEs
(
SztProtIE_Field_InitUEMsg_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_InitUEMsg_IEs(param, mBuf)
SztProtIE_Field_InitUEMsg_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_InitUEMsg_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueInitUEMsg_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_InitUEMsg_IEs */



/* 
* FUN : cmPkSztProtIE_Cont_InitUEMsg_IEs
*  DESC: Function to Pack SztProtIE_Cont_InitUEMsg_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_InitUEMsg_IEs
(
SztProtIE_Cont_InitUEMsg_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_InitUEMsg_IEs(param, mBuf)
SztProtIE_Cont_InitUEMsg_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_InitUEMsg_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_InitUEMsg_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_InitUEMsg_IEs */



/* 
* FUN : cmPkSztInitUEMsg
*  DESC: Function to Pack SztInitUEMsg structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztInitUEMsg
(
SztInitUEMsg *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztInitUEMsg(param, mBuf)
SztInitUEMsg *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztInitUEMsg) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_InitUEMsg_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztInitUEMsg */



/* 
* FUN : cmPkSzt_ValueUlnkNASTport_IEsCls
*  DESC: Function to Pack Szt_ValueUlnkNASTport_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueUlnkNASTport_IEsCls
(
Szt_ValueUlnkNASTport_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueUlnkNASTport_IEsCls(param, val, mBuf)
Szt_ValueUlnkNASTport_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueUlnkNASTport_IEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_NAS_PDU:
			CMCHKPK(cmPkSztNAS_PDU, &param->u.sztNAS_PDU, mBuf);
			break;
		case Sztid_EUTRAN_CGI:
			CMCHKPK(cmPkSztEUTRAN_CGI, &param->u.sztEUTRAN_CGI, mBuf);
			break;
		case Sztid_TAI:
			CMCHKPK(cmPkSztTAI, &param->u.sztTAI, mBuf);
			break;
		case Sztid_GW_TportLyrAddr:
			CMCHKPK(cmPkSztTportLyrAddr, &param->u.sztTportLyrAddr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueUlnkNASTport_IEsCls */



/* 
* FUN : cmPkSztProtIE_Field_UlnkNASTport_IEs
*  DESC: Function to Pack SztProtIE_Field_UlnkNASTport_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_UlnkNASTport_IEs
(
SztProtIE_Field_UlnkNASTport_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_UlnkNASTport_IEs(param, mBuf)
SztProtIE_Field_UlnkNASTport_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_UlnkNASTport_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueUlnkNASTport_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_UlnkNASTport_IEs */



/* 
* FUN : cmPkSztProtIE_Cont_UlnkNASTport_IEs
*  DESC: Function to Pack SztProtIE_Cont_UlnkNASTport_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_UlnkNASTport_IEs
(
SztProtIE_Cont_UlnkNASTport_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_UlnkNASTport_IEs(param, mBuf)
SztProtIE_Cont_UlnkNASTport_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_UlnkNASTport_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_UlnkNASTport_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_UlnkNASTport_IEs */



/* 
* FUN : cmPkSztUlnkNASTport
*  DESC: Function to Pack SztUlnkNASTport structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztUlnkNASTport
(
SztUlnkNASTport *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztUlnkNASTport(param, mBuf)
SztUlnkNASTport *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztUlnkNASTport) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_UlnkNASTport_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztUlnkNASTport */



/* 
* FUN : cmPkSzt_ValueNASNonDlvryInd_IEsCls
*  DESC: Function to Pack Szt_ValueNASNonDlvryInd_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueNASNonDlvryInd_IEsCls
(
Szt_ValueNASNonDlvryInd_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueNASNonDlvryInd_IEsCls(param, val, mBuf)
Szt_ValueNASNonDlvryInd_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueNASNonDlvryInd_IEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_NAS_PDU:
			CMCHKPK(cmPkSztNAS_PDU, &param->u.sztNAS_PDU, mBuf);
			break;
		case Sztid_Cause:
			CMCHKPK(cmPkSztCause, &param->u.sztCause, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueNASNonDlvryInd_IEsCls */



/* 
* FUN : cmPkSztProtIE_Field_NASNonDlvryInd_IEs
*  DESC: Function to Pack SztProtIE_Field_NASNonDlvryInd_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_NASNonDlvryInd_IEs
(
SztProtIE_Field_NASNonDlvryInd_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_NASNonDlvryInd_IEs(param, mBuf)
SztProtIE_Field_NASNonDlvryInd_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_NASNonDlvryInd_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueNASNonDlvryInd_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_NASNonDlvryInd_IEs */



/* 
* FUN : cmPkSztProtIE_Cont_NASNonDlvryInd_IEs
*  DESC: Function to Pack SztProtIE_Cont_NASNonDlvryInd_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_NASNonDlvryInd_IEs
(
SztProtIE_Cont_NASNonDlvryInd_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_NASNonDlvryInd_IEs(param, mBuf)
SztProtIE_Cont_NASNonDlvryInd_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_NASNonDlvryInd_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_NASNonDlvryInd_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_NASNonDlvryInd_IEs */



/* 
* FUN : cmPkSztNASNonDlvryInd
*  DESC: Function to Pack SztNASNonDlvryInd structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztNASNonDlvryInd
(
SztNASNonDlvryInd *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztNASNonDlvryInd(param, mBuf)
SztNASNonDlvryInd *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztNASNonDlvryInd) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_NASNonDlvryInd_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztNASNonDlvryInd */

#define cmPkSztResetAll cmPkTknU32


/* 
* FUN : cmPkSzt_ValueUE_assocLogS1_ConItemResCls
*  DESC: Function to Pack Szt_ValueUE_assocLogS1_ConItemResCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueUE_assocLogS1_ConItemResCls
(
Szt_ValueUE_assocLogS1_ConItemResCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueUE_assocLogS1_ConItemResCls(param, val, mBuf)
Szt_ValueUE_assocLogS1_ConItemResCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueUE_assocLogS1_ConItemResCls) 
	
	switch (val)
	{
		case Sztid_UE_assocLogS1_ConItem:
			CMCHKPK(cmPkSztUE_assocLogS1_ConItem, &param->u.sztUE_assocLogS1_ConItem, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueUE_assocLogS1_ConItemResCls */



/* 
* FUN : cmPkSztProtIE_Field_UE_assocLogS1_ConItemRes
*  DESC: Function to Pack SztProtIE_Field_UE_assocLogS1_ConItemRes structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_UE_assocLogS1_ConItemRes
(
SztProtIE_Field_UE_assocLogS1_ConItemRes *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_UE_assocLogS1_ConItemRes(param, mBuf)
SztProtIE_Field_UE_assocLogS1_ConItemRes *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_UE_assocLogS1_ConItemRes) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueUE_assocLogS1_ConItemResCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_UE_assocLogS1_ConItemRes */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmPkSztProtIE_SingleCont_UE_assocLogS1_ConItemRes cmPkSztProtIE_Field_UE_assocLogS1_ConItemRes


/* 
* FUN : cmPkSztUE_assocLogS1_ConLstRes
*  DESC: Function to Pack SztUE_assocLogS1_ConLstRes structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztUE_assocLogS1_ConLstRes
(
SztUE_assocLogS1_ConLstRes *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztUE_assocLogS1_ConLstRes(param, mBuf)
SztUE_assocLogS1_ConLstRes *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztUE_assocLogS1_ConLstRes) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_SingleCont_UE_assocLogS1_ConItemRes, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztUE_assocLogS1_ConLstRes */



/* 
* FUN : cmPkSztResetTyp
*  DESC: Function to Pack SztResetTyp structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztResetTyp
(
SztResetTyp *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztResetTyp(param, mBuf)
SztResetTyp *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztResetTyp) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case RESETTYP_PARTOFS1_INTF :
				CMCHKPK(cmPkSztUE_assocLogS1_ConLstRes, &param->val.partOfS1_Intf, mBuf); 
				break;
			case RESETTYP_S1_INTF :
				CMCHKPK(cmPkSztResetAll, &param->val.s1_Intf, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztResetTyp */



/* 
* FUN : cmPkSzt_ValueResetIEsCls
*  DESC: Function to Pack Szt_ValueResetIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueResetIEsCls
(
Szt_ValueResetIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueResetIEsCls(param, val, mBuf)
Szt_ValueResetIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueResetIEsCls) 
	
	switch (val)
	{
		case Sztid_Cause:
			CMCHKPK(cmPkSztCause, &param->u.sztCause, mBuf);
			break;
		case Sztid_ResetTyp:
			CMCHKPK(cmPkSztResetTyp, &param->u.sztResetTyp, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueResetIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_ResetIEs
*  DESC: Function to Pack SztProtIE_Field_ResetIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_ResetIEs
(
SztProtIE_Field_ResetIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_ResetIEs(param, mBuf)
SztProtIE_Field_ResetIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_ResetIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueResetIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_ResetIEs */



/* 
* FUN : cmPkSztProtIE_Cont_ResetIEs
*  DESC: Function to Pack SztProtIE_Cont_ResetIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_ResetIEs
(
SztProtIE_Cont_ResetIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_ResetIEs(param, mBuf)
SztProtIE_Cont_ResetIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_ResetIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_ResetIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_ResetIEs */



/* 
* FUN : cmPkSztReset
*  DESC: Function to Pack SztReset structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztReset
(
SztReset *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztReset(param, mBuf)
SztReset *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztReset) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_ResetIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztReset */



/* 
* FUN : cmPkSzt_ValueUE_assocLogS1_ConItemResAckCls
*  DESC: Function to Pack Szt_ValueUE_assocLogS1_ConItemResAckCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueUE_assocLogS1_ConItemResAckCls
(
Szt_ValueUE_assocLogS1_ConItemResAckCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueUE_assocLogS1_ConItemResAckCls(param, val, mBuf)
Szt_ValueUE_assocLogS1_ConItemResAckCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueUE_assocLogS1_ConItemResAckCls) 
	
	switch (val)
	{
		case Sztid_UE_assocLogS1_ConItem:
			CMCHKPK(cmPkSztUE_assocLogS1_ConItem, &param->u.sztUE_assocLogS1_ConItem, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueUE_assocLogS1_ConItemResAckCls */



/* 
* FUN : cmPkSztProtIE_Field_UE_assocLogS1_ConItemResAck
*  DESC: Function to Pack SztProtIE_Field_UE_assocLogS1_ConItemResAck structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_UE_assocLogS1_ConItemResAck
(
SztProtIE_Field_UE_assocLogS1_ConItemResAck *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_UE_assocLogS1_ConItemResAck(param, mBuf)
SztProtIE_Field_UE_assocLogS1_ConItemResAck *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_UE_assocLogS1_ConItemResAck) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueUE_assocLogS1_ConItemResAckCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_UE_assocLogS1_ConItemResAck */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmPkSztProtIE_SingleCont_UE_assocLogS1_ConItemResAck cmPkSztProtIE_Field_UE_assocLogS1_ConItemResAck


/* 
* FUN : cmPkSztUE_assocLogS1_ConLstResAck
*  DESC: Function to Pack SztUE_assocLogS1_ConLstResAck structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztUE_assocLogS1_ConLstResAck
(
SztUE_assocLogS1_ConLstResAck *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztUE_assocLogS1_ConLstResAck(param, mBuf)
SztUE_assocLogS1_ConLstResAck *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztUE_assocLogS1_ConLstResAck) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_SingleCont_UE_assocLogS1_ConItemResAck, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztUE_assocLogS1_ConLstResAck */



/* 
* FUN : cmPkSzt_ValueResetAckgIEsCls
*  DESC: Function to Pack Szt_ValueResetAckgIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueResetAckgIEsCls
(
Szt_ValueResetAckgIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueResetAckgIEsCls(param, val, mBuf)
Szt_ValueResetAckgIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueResetAckgIEsCls) 
	
	switch (val)
	{
		case Sztid_UE_assocLogS1_ConLstResAck:
			CMCHKPK(cmPkSztUE_assocLogS1_ConLstResAck, &param->u.sztUE_assocLogS1_ConLstResAck, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKPK(cmPkSztCriticalityDiag, &param->u.sztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueResetAckgIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_ResetAckgIEs
*  DESC: Function to Pack SztProtIE_Field_ResetAckgIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_ResetAckgIEs
(
SztProtIE_Field_ResetAckgIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_ResetAckgIEs(param, mBuf)
SztProtIE_Field_ResetAckgIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_ResetAckgIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueResetAckgIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_ResetAckgIEs */



/* 
* FUN : cmPkSztProtIE_Cont_ResetAckgIEs
*  DESC: Function to Pack SztProtIE_Cont_ResetAckgIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_ResetAckgIEs
(
SztProtIE_Cont_ResetAckgIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_ResetAckgIEs(param, mBuf)
SztProtIE_Cont_ResetAckgIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_ResetAckgIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_ResetAckgIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_ResetAckgIEs */



/* 
* FUN : cmPkSztResetAckg
*  DESC: Function to Pack SztResetAckg structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztResetAckg
(
SztResetAckg *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztResetAckg(param, mBuf)
SztResetAckg *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztResetAckg) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_ResetAckgIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztResetAckg */



/* 
* FUN : cmPkSzt_ValueErrIndIEsCls
*  DESC: Function to Pack Szt_ValueErrIndIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueErrIndIEsCls
(
Szt_ValueErrIndIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueErrIndIEsCls(param, val, mBuf)
Szt_ValueErrIndIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueErrIndIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_Cause:
			CMCHKPK(cmPkSztCause, &param->u.sztCause, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKPK(cmPkSztCriticalityDiag, &param->u.sztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueErrIndIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_ErrIndIEs
*  DESC: Function to Pack SztProtIE_Field_ErrIndIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_ErrIndIEs
(
SztProtIE_Field_ErrIndIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_ErrIndIEs(param, mBuf)
SztProtIE_Field_ErrIndIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_ErrIndIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueErrIndIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_ErrIndIEs */



/* 
* FUN : cmPkSztProtIE_Cont_ErrIndIEs
*  DESC: Function to Pack SztProtIE_Cont_ErrIndIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_ErrIndIEs
(
SztProtIE_Cont_ErrIndIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_ErrIndIEs(param, mBuf)
SztProtIE_Cont_ErrIndIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_ErrIndIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_ErrIndIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_ErrIndIEs */



/* 
* FUN : cmPkSztErrInd
*  DESC: Function to Pack SztErrInd structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztErrInd
(
SztErrInd *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztErrInd(param, mBuf)
SztErrInd *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztErrInd) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_ErrIndIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztErrInd */



/* 
* FUN : cmPkSzt_ValueS1SetupRqstIEsCls
*  DESC: Function to Pack Szt_ValueS1SetupRqstIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueS1SetupRqstIEsCls
(
Szt_ValueS1SetupRqstIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueS1SetupRqstIEsCls(param, val, mBuf)
Szt_ValueS1SetupRqstIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueS1SetupRqstIEsCls) 
	
	switch (val)
	{
		case Sztid_Global_ENB_ID:
			CMCHKPK(cmPkSztGlobal_ENB_ID, &param->u.sztGlobal_ENB_ID, mBuf);
			break;
		case Sztid_eNBname:
			CMCHKPK(cmPkSztENBname, &param->u.sztENBname, mBuf);
			break;
		case Sztid_SuppTAs:
			CMCHKPK(cmPkSztSuppTAs, &param->u.sztSuppTAs, mBuf);
			break;
		case Sztid_DefaultPagDRX:
			CMCHKPK(cmPkSztPagDRX, &param->u.sztPagDRX, mBuf);
			break;
		case Sztid_CSG_IdLst:
			CMCHKPK(cmPkSztCSG_IdLst, &param->u.sztCSG_IdLst, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueS1SetupRqstIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_S1SetupRqstIEs
*  DESC: Function to Pack SztProtIE_Field_S1SetupRqstIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_S1SetupRqstIEs
(
SztProtIE_Field_S1SetupRqstIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_S1SetupRqstIEs(param, mBuf)
SztProtIE_Field_S1SetupRqstIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_S1SetupRqstIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueS1SetupRqstIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_S1SetupRqstIEs */



/* 
* FUN : cmPkSztProtIE_Cont_S1SetupRqstIEs
*  DESC: Function to Pack SztProtIE_Cont_S1SetupRqstIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_S1SetupRqstIEs
(
SztProtIE_Cont_S1SetupRqstIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_S1SetupRqstIEs(param, mBuf)
SztProtIE_Cont_S1SetupRqstIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_S1SetupRqstIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_S1SetupRqstIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_S1SetupRqstIEs */



/* 
* FUN : cmPkSztS1SetupRqst
*  DESC: Function to Pack SztS1SetupRqst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztS1SetupRqst
(
SztS1SetupRqst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztS1SetupRqst(param, mBuf)
SztS1SetupRqst *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztS1SetupRqst) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_S1SetupRqstIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztS1SetupRqst */



/* 
* FUN : cmPkSzt_ValueS1SetupRespIEsCls
*  DESC: Function to Pack Szt_ValueS1SetupRespIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueS1SetupRespIEsCls
(
Szt_ValueS1SetupRespIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueS1SetupRespIEsCls(param, val, mBuf)
Szt_ValueS1SetupRespIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueS1SetupRespIEsCls) 
	
	switch (val)
	{
		case Sztid_MMEname:
			CMCHKPK(cmPkSztMMEname, &param->u.sztMMEname, mBuf);
			break;
		case Sztid_SrvdGUMMEIs:
			CMCHKPK(cmPkSztSrvdGUMMEIs, &param->u.sztSrvdGUMMEIs, mBuf);
			break;
		case Sztid_RelativeMMECapacity:
			CMCHKPK(cmPkSztRelativeMMECapacity, &param->u.sztRelativeMMECapacity, mBuf);
			break;
		case Sztid_MMERelaySupportIndicator:
			CMCHKPK(cmPkSztMMERelaySupportIndicator, &param->u.sztMMERelaySupportIndicator, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKPK(cmPkSztCriticalityDiag, &param->u.sztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueS1SetupRespIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_S1SetupRespIEs
*  DESC: Function to Pack SztProtIE_Field_S1SetupRespIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_S1SetupRespIEs
(
SztProtIE_Field_S1SetupRespIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_S1SetupRespIEs(param, mBuf)
SztProtIE_Field_S1SetupRespIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_S1SetupRespIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueS1SetupRespIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_S1SetupRespIEs */



/* 
* FUN : cmPkSztProtIE_Cont_S1SetupRespIEs
*  DESC: Function to Pack SztProtIE_Cont_S1SetupRespIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_S1SetupRespIEs
(
SztProtIE_Cont_S1SetupRespIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_S1SetupRespIEs(param, mBuf)
SztProtIE_Cont_S1SetupRespIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_S1SetupRespIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_S1SetupRespIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_S1SetupRespIEs */



/* 
* FUN : cmPkSztS1SetupResp
*  DESC: Function to Pack SztS1SetupResp structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztS1SetupResp
(
SztS1SetupResp *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztS1SetupResp(param, mBuf)
SztS1SetupResp *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztS1SetupResp) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_S1SetupRespIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztS1SetupResp */



/* 
* FUN : cmPkSzt_ValueS1SetupFailIEsCls
*  DESC: Function to Pack Szt_ValueS1SetupFailIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueS1SetupFailIEsCls
(
Szt_ValueS1SetupFailIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueS1SetupFailIEsCls(param, val, mBuf)
Szt_ValueS1SetupFailIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueS1SetupFailIEsCls) 
	
	switch (val)
	{
		case Sztid_Cause:
			CMCHKPK(cmPkSztCause, &param->u.sztCause, mBuf);
			break;
		case Sztid_TimeToWait:
			CMCHKPK(cmPkSztTimeToWait, &param->u.sztTimeToWait, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKPK(cmPkSztCriticalityDiag, &param->u.sztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueS1SetupFailIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_S1SetupFailIEs
*  DESC: Function to Pack SztProtIE_Field_S1SetupFailIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_S1SetupFailIEs
(
SztProtIE_Field_S1SetupFailIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_S1SetupFailIEs(param, mBuf)
SztProtIE_Field_S1SetupFailIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_S1SetupFailIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueS1SetupFailIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_S1SetupFailIEs */



/* 
* FUN : cmPkSztProtIE_Cont_S1SetupFailIEs
*  DESC: Function to Pack SztProtIE_Cont_S1SetupFailIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_S1SetupFailIEs
(
SztProtIE_Cont_S1SetupFailIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_S1SetupFailIEs(param, mBuf)
SztProtIE_Cont_S1SetupFailIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_S1SetupFailIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_S1SetupFailIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_S1SetupFailIEs */



/* 
* FUN : cmPkSztS1SetupFail
*  DESC: Function to Pack SztS1SetupFail structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztS1SetupFail
(
SztS1SetupFail *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztS1SetupFail(param, mBuf)
SztS1SetupFail *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztS1SetupFail) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_S1SetupFailIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztS1SetupFail */



/* 
* FUN : cmPkSzt_ValueENBConfigUpdIEsCls
*  DESC: Function to Pack Szt_ValueENBConfigUpdIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueENBConfigUpdIEsCls
(
Szt_ValueENBConfigUpdIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueENBConfigUpdIEsCls(param, val, mBuf)
Szt_ValueENBConfigUpdIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueENBConfigUpdIEsCls) 
	
	switch (val)
	{
		case Sztid_eNBname:
			CMCHKPK(cmPkSztENBname, &param->u.sztENBname, mBuf);
			break;
		case Sztid_SuppTAs:
			CMCHKPK(cmPkSztSuppTAs, &param->u.sztSuppTAs, mBuf);
			break;
		case Sztid_CSG_IdLst:
			CMCHKPK(cmPkSztCSG_IdLst, &param->u.sztCSG_IdLst, mBuf);
			break;
		case Sztid_DefaultPagDRX:
			CMCHKPK(cmPkSztPagDRX, &param->u.sztPagDRX, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueENBConfigUpdIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_ENBConfigUpdIEs
*  DESC: Function to Pack SztProtIE_Field_ENBConfigUpdIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_ENBConfigUpdIEs
(
SztProtIE_Field_ENBConfigUpdIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_ENBConfigUpdIEs(param, mBuf)
SztProtIE_Field_ENBConfigUpdIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_ENBConfigUpdIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueENBConfigUpdIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_ENBConfigUpdIEs */



/* 
* FUN : cmPkSztProtIE_Cont_ENBConfigUpdIEs
*  DESC: Function to Pack SztProtIE_Cont_ENBConfigUpdIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_ENBConfigUpdIEs
(
SztProtIE_Cont_ENBConfigUpdIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_ENBConfigUpdIEs(param, mBuf)
SztProtIE_Cont_ENBConfigUpdIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_ENBConfigUpdIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_ENBConfigUpdIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_ENBConfigUpdIEs */



/* 
* FUN : cmPkSztENBConfigUpd
*  DESC: Function to Pack SztENBConfigUpd structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztENBConfigUpd
(
SztENBConfigUpd *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztENBConfigUpd(param, mBuf)
SztENBConfigUpd *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztENBConfigUpd) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_ENBConfigUpdIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztENBConfigUpd */



/* 
* FUN : cmPkSzt_ValueENBConfigUpdAckgIEsCls
*  DESC: Function to Pack Szt_ValueENBConfigUpdAckgIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueENBConfigUpdAckgIEsCls
(
Szt_ValueENBConfigUpdAckgIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueENBConfigUpdAckgIEsCls(param, val, mBuf)
Szt_ValueENBConfigUpdAckgIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueENBConfigUpdAckgIEsCls) 
	
	switch (val)
	{
		case Sztid_CriticalityDiag:
			CMCHKPK(cmPkSztCriticalityDiag, &param->u.sztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueENBConfigUpdAckgIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_ENBConfigUpdAckgIEs
*  DESC: Function to Pack SztProtIE_Field_ENBConfigUpdAckgIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_ENBConfigUpdAckgIEs
(
SztProtIE_Field_ENBConfigUpdAckgIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_ENBConfigUpdAckgIEs(param, mBuf)
SztProtIE_Field_ENBConfigUpdAckgIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_ENBConfigUpdAckgIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueENBConfigUpdAckgIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_ENBConfigUpdAckgIEs */



/* 
* FUN : cmPkSztProtIE_Cont_ENBConfigUpdAckgIEs
*  DESC: Function to Pack SztProtIE_Cont_ENBConfigUpdAckgIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_ENBConfigUpdAckgIEs
(
SztProtIE_Cont_ENBConfigUpdAckgIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_ENBConfigUpdAckgIEs(param, mBuf)
SztProtIE_Cont_ENBConfigUpdAckgIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_ENBConfigUpdAckgIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_ENBConfigUpdAckgIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_ENBConfigUpdAckgIEs */



/* 
* FUN : cmPkSztENBConfigUpdAckg
*  DESC: Function to Pack SztENBConfigUpdAckg structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztENBConfigUpdAckg
(
SztENBConfigUpdAckg *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztENBConfigUpdAckg(param, mBuf)
SztENBConfigUpdAckg *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztENBConfigUpdAckg) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_ENBConfigUpdAckgIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztENBConfigUpdAckg */



/* 
* FUN : cmPkSzt_ValueENBConfigUpdFailIEsCls
*  DESC: Function to Pack Szt_ValueENBConfigUpdFailIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueENBConfigUpdFailIEsCls
(
Szt_ValueENBConfigUpdFailIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueENBConfigUpdFailIEsCls(param, val, mBuf)
Szt_ValueENBConfigUpdFailIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueENBConfigUpdFailIEsCls) 
	
	switch (val)
	{
		case Sztid_Cause:
			CMCHKPK(cmPkSztCause, &param->u.sztCause, mBuf);
			break;
		case Sztid_TimeToWait:
			CMCHKPK(cmPkSztTimeToWait, &param->u.sztTimeToWait, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKPK(cmPkSztCriticalityDiag, &param->u.sztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueENBConfigUpdFailIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_ENBConfigUpdFailIEs
*  DESC: Function to Pack SztProtIE_Field_ENBConfigUpdFailIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_ENBConfigUpdFailIEs
(
SztProtIE_Field_ENBConfigUpdFailIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_ENBConfigUpdFailIEs(param, mBuf)
SztProtIE_Field_ENBConfigUpdFailIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_ENBConfigUpdFailIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueENBConfigUpdFailIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_ENBConfigUpdFailIEs */



/* 
* FUN : cmPkSztProtIE_Cont_ENBConfigUpdFailIEs
*  DESC: Function to Pack SztProtIE_Cont_ENBConfigUpdFailIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_ENBConfigUpdFailIEs
(
SztProtIE_Cont_ENBConfigUpdFailIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_ENBConfigUpdFailIEs(param, mBuf)
SztProtIE_Cont_ENBConfigUpdFailIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_ENBConfigUpdFailIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_ENBConfigUpdFailIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_ENBConfigUpdFailIEs */



/* 
* FUN : cmPkSztENBConfigUpdFail
*  DESC: Function to Pack SztENBConfigUpdFail structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztENBConfigUpdFail
(
SztENBConfigUpdFail *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztENBConfigUpdFail(param, mBuf)
SztENBConfigUpdFail *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztENBConfigUpdFail) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_ENBConfigUpdFailIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztENBConfigUpdFail */



/* 
* FUN : cmPkSzt_ValueMMEConfigUpdIEsCls
*  DESC: Function to Pack Szt_ValueMMEConfigUpdIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueMMEConfigUpdIEsCls
(
Szt_ValueMMEConfigUpdIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueMMEConfigUpdIEsCls(param, val, mBuf)
Szt_ValueMMEConfigUpdIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueMMEConfigUpdIEsCls) 
	
	switch (val)
	{
		case Sztid_MMEname:
			CMCHKPK(cmPkSztMMEname, &param->u.sztMMEname, mBuf);
			break;
		case Sztid_SrvdGUMMEIs:
			CMCHKPK(cmPkSztSrvdGUMMEIs, &param->u.sztSrvdGUMMEIs, mBuf);
			break;
		case Sztid_RelativeMMECapacity:
			CMCHKPK(cmPkSztRelativeMMECapacity, &param->u.sztRelativeMMECapacity, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueMMEConfigUpdIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_MMEConfigUpdIEs
*  DESC: Function to Pack SztProtIE_Field_MMEConfigUpdIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_MMEConfigUpdIEs
(
SztProtIE_Field_MMEConfigUpdIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_MMEConfigUpdIEs(param, mBuf)
SztProtIE_Field_MMEConfigUpdIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_MMEConfigUpdIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueMMEConfigUpdIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_MMEConfigUpdIEs */



/* 
* FUN : cmPkSztProtIE_Cont_MMEConfigUpdIEs
*  DESC: Function to Pack SztProtIE_Cont_MMEConfigUpdIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_MMEConfigUpdIEs
(
SztProtIE_Cont_MMEConfigUpdIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_MMEConfigUpdIEs(param, mBuf)
SztProtIE_Cont_MMEConfigUpdIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_MMEConfigUpdIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_MMEConfigUpdIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_MMEConfigUpdIEs */



/* 
* FUN : cmPkSztMMEConfigUpd
*  DESC: Function to Pack SztMMEConfigUpd structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztMMEConfigUpd
(
SztMMEConfigUpd *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztMMEConfigUpd(param, mBuf)
SztMMEConfigUpd *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztMMEConfigUpd) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_MMEConfigUpdIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztMMEConfigUpd */



/* 
* FUN : cmPkSzt_ValueMMEConfigUpdAckgIEsCls
*  DESC: Function to Pack Szt_ValueMMEConfigUpdAckgIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueMMEConfigUpdAckgIEsCls
(
Szt_ValueMMEConfigUpdAckgIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueMMEConfigUpdAckgIEsCls(param, val, mBuf)
Szt_ValueMMEConfigUpdAckgIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueMMEConfigUpdAckgIEsCls) 
	
	switch (val)
	{
		case Sztid_CriticalityDiag:
			CMCHKPK(cmPkSztCriticalityDiag, &param->u.sztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueMMEConfigUpdAckgIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_MMEConfigUpdAckgIEs
*  DESC: Function to Pack SztProtIE_Field_MMEConfigUpdAckgIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_MMEConfigUpdAckgIEs
(
SztProtIE_Field_MMEConfigUpdAckgIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_MMEConfigUpdAckgIEs(param, mBuf)
SztProtIE_Field_MMEConfigUpdAckgIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_MMEConfigUpdAckgIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueMMEConfigUpdAckgIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_MMEConfigUpdAckgIEs */



/* 
* FUN : cmPkSztProtIE_Cont_MMEConfigUpdAckgIEs
*  DESC: Function to Pack SztProtIE_Cont_MMEConfigUpdAckgIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_MMEConfigUpdAckgIEs
(
SztProtIE_Cont_MMEConfigUpdAckgIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_MMEConfigUpdAckgIEs(param, mBuf)
SztProtIE_Cont_MMEConfigUpdAckgIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_MMEConfigUpdAckgIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_MMEConfigUpdAckgIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_MMEConfigUpdAckgIEs */



/* 
* FUN : cmPkSztMMEConfigUpdAckg
*  DESC: Function to Pack SztMMEConfigUpdAckg structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztMMEConfigUpdAckg
(
SztMMEConfigUpdAckg *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztMMEConfigUpdAckg(param, mBuf)
SztMMEConfigUpdAckg *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztMMEConfigUpdAckg) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_MMEConfigUpdAckgIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztMMEConfigUpdAckg */



/* 
* FUN : cmPkSzt_ValueMMEConfigUpdFailIEsCls
*  DESC: Function to Pack Szt_ValueMMEConfigUpdFailIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueMMEConfigUpdFailIEsCls
(
Szt_ValueMMEConfigUpdFailIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueMMEConfigUpdFailIEsCls(param, val, mBuf)
Szt_ValueMMEConfigUpdFailIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueMMEConfigUpdFailIEsCls) 
	
	switch (val)
	{
		case Sztid_Cause:
			CMCHKPK(cmPkSztCause, &param->u.sztCause, mBuf);
			break;
		case Sztid_TimeToWait:
			CMCHKPK(cmPkSztTimeToWait, &param->u.sztTimeToWait, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKPK(cmPkSztCriticalityDiag, &param->u.sztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueMMEConfigUpdFailIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_MMEConfigUpdFailIEs
*  DESC: Function to Pack SztProtIE_Field_MMEConfigUpdFailIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_MMEConfigUpdFailIEs
(
SztProtIE_Field_MMEConfigUpdFailIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_MMEConfigUpdFailIEs(param, mBuf)
SztProtIE_Field_MMEConfigUpdFailIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_MMEConfigUpdFailIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueMMEConfigUpdFailIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_MMEConfigUpdFailIEs */



/* 
* FUN : cmPkSztProtIE_Cont_MMEConfigUpdFailIEs
*  DESC: Function to Pack SztProtIE_Cont_MMEConfigUpdFailIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_MMEConfigUpdFailIEs
(
SztProtIE_Cont_MMEConfigUpdFailIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_MMEConfigUpdFailIEs(param, mBuf)
SztProtIE_Cont_MMEConfigUpdFailIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_MMEConfigUpdFailIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_MMEConfigUpdFailIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_MMEConfigUpdFailIEs */



/* 
* FUN : cmPkSztMMEConfigUpdFail
*  DESC: Function to Pack SztMMEConfigUpdFail structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztMMEConfigUpdFail
(
SztMMEConfigUpdFail *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztMMEConfigUpdFail(param, mBuf)
SztMMEConfigUpdFail *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztMMEConfigUpdFail) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_MMEConfigUpdFailIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztMMEConfigUpdFail */



/* 
* FUN : cmPkSzt_ValueDlnkS1cdma2000tunnelingIEsCls
*  DESC: Function to Pack Szt_ValueDlnkS1cdma2000tunnelingIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueDlnkS1cdma2000tunnelingIEsCls
(
Szt_ValueDlnkS1cdma2000tunnelingIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueDlnkS1cdma2000tunnelingIEsCls(param, val, mBuf)
Szt_ValueDlnkS1cdma2000tunnelingIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueDlnkS1cdma2000tunnelingIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_E_RABSubjtoDataFwdingLst:
			CMCHKPK(cmPkSztE_RABSubjtoDataFwdingLst, &param->u.sztE_RABSubjtoDataFwdingLst, mBuf);
			break;
		case Sztid_cdma2000HOStatus:
			CMCHKPK(cmPkSztCdma2000HOStatus, &param->u.sztCdma2000HOStatus, mBuf);
			break;
		case Sztid_cdma2000RATTyp:
			CMCHKPK(cmPkSztCdma2000RATTyp, &param->u.sztCdma2000RATTyp, mBuf);
			break;
		case Sztid_cdma2000PDU:
			CMCHKPK(cmPkSztCdma2000PDU, &param->u.sztCdma2000PDU, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueDlnkS1cdma2000tunnelingIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_DlnkS1cdma2000tunnelingIEs
*  DESC: Function to Pack SztProtIE_Field_DlnkS1cdma2000tunnelingIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_DlnkS1cdma2000tunnelingIEs
(
SztProtIE_Field_DlnkS1cdma2000tunnelingIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_DlnkS1cdma2000tunnelingIEs(param, mBuf)
SztProtIE_Field_DlnkS1cdma2000tunnelingIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_DlnkS1cdma2000tunnelingIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueDlnkS1cdma2000tunnelingIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_DlnkS1cdma2000tunnelingIEs */



/* 
* FUN : cmPkSztProtIE_Cont_DlnkS1cdma2000tunnelingIEs
*  DESC: Function to Pack SztProtIE_Cont_DlnkS1cdma2000tunnelingIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_DlnkS1cdma2000tunnelingIEs
(
SztProtIE_Cont_DlnkS1cdma2000tunnelingIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_DlnkS1cdma2000tunnelingIEs(param, mBuf)
SztProtIE_Cont_DlnkS1cdma2000tunnelingIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_DlnkS1cdma2000tunnelingIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_DlnkS1cdma2000tunnelingIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_DlnkS1cdma2000tunnelingIEs */



/* 
* FUN : cmPkSztDlnkS1cdma2000tunneling
*  DESC: Function to Pack SztDlnkS1cdma2000tunneling structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztDlnkS1cdma2000tunneling
(
SztDlnkS1cdma2000tunneling *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztDlnkS1cdma2000tunneling(param, mBuf)
SztDlnkS1cdma2000tunneling *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztDlnkS1cdma2000tunneling) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_DlnkS1cdma2000tunnelingIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztDlnkS1cdma2000tunneling */



/* 
* FUN : cmPkSzt_ValueUlnkS1cdma2000tunnelingIEsCls
*  DESC: Function to Pack Szt_ValueUlnkS1cdma2000tunnelingIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueUlnkS1cdma2000tunnelingIEsCls
(
Szt_ValueUlnkS1cdma2000tunnelingIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueUlnkS1cdma2000tunnelingIEsCls(param, val, mBuf)
Szt_ValueUlnkS1cdma2000tunnelingIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueUlnkS1cdma2000tunnelingIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_cdma2000RATTyp:
			CMCHKPK(cmPkSztCdma2000RATTyp, &param->u.sztCdma2000RATTyp, mBuf);
			break;
		case Sztid_cdma2000SectorID:
			CMCHKPK(cmPkSztCdma2000SectorID, &param->u.sztCdma2000SectorID, mBuf);
			break;
		case Sztid_cdma2000HOReqdInd:
			CMCHKPK(cmPkSztCdma2000HOReqdInd, &param->u.sztCdma2000HOReqdInd, mBuf);
			break;
		case Sztid_cdma2000OneXSRVCCInfo:
			CMCHKPK(cmPkSztCdma2000OneXSRVCCInfo, &param->u.sztCdma2000OneXSRVCCInfo, mBuf);
			break;
		case Sztid_cdma2000OneXRAND:
			CMCHKPK(cmPkSztCdma2000OneXRAND, &param->u.sztCdma2000OneXRAND, mBuf);
			break;
		case Sztid_cdma2000PDU:
			CMCHKPK(cmPkSztCdma2000PDU, &param->u.sztCdma2000PDU, mBuf);
			break;
		case Sztid_EUTRANRoundTripDelayEstimationInfo:
			CMCHKPK(cmPkSztEUTRANRoundTripDelayEstimationInfo, &param->u.sztEUTRANRoundTripDelayEstimationInfo, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueUlnkS1cdma2000tunnelingIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_UlnkS1cdma2000tunnelingIEs
*  DESC: Function to Pack SztProtIE_Field_UlnkS1cdma2000tunnelingIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_UlnkS1cdma2000tunnelingIEs
(
SztProtIE_Field_UlnkS1cdma2000tunnelingIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_UlnkS1cdma2000tunnelingIEs(param, mBuf)
SztProtIE_Field_UlnkS1cdma2000tunnelingIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_UlnkS1cdma2000tunnelingIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueUlnkS1cdma2000tunnelingIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_UlnkS1cdma2000tunnelingIEs */



/* 
* FUN : cmPkSztProtIE_Cont_UlnkS1cdma2000tunnelingIEs
*  DESC: Function to Pack SztProtIE_Cont_UlnkS1cdma2000tunnelingIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_UlnkS1cdma2000tunnelingIEs
(
SztProtIE_Cont_UlnkS1cdma2000tunnelingIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_UlnkS1cdma2000tunnelingIEs(param, mBuf)
SztProtIE_Cont_UlnkS1cdma2000tunnelingIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_UlnkS1cdma2000tunnelingIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_UlnkS1cdma2000tunnelingIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_UlnkS1cdma2000tunnelingIEs */



/* 
* FUN : cmPkSztUlnkS1cdma2000tunneling
*  DESC: Function to Pack SztUlnkS1cdma2000tunneling structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztUlnkS1cdma2000tunneling
(
SztUlnkS1cdma2000tunneling *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztUlnkS1cdma2000tunneling(param, mBuf)
SztUlnkS1cdma2000tunneling *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztUlnkS1cdma2000tunneling) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_UlnkS1cdma2000tunnelingIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztUlnkS1cdma2000tunneling */



/* 
* FUN : cmPkSzt_ValueUECapbltyInfoIndIEsCls
*  DESC: Function to Pack Szt_ValueUECapbltyInfoIndIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueUECapbltyInfoIndIEsCls
(
Szt_ValueUECapbltyInfoIndIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueUECapbltyInfoIndIEsCls(param, val, mBuf)
Szt_ValueUECapbltyInfoIndIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueUECapbltyInfoIndIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_UERadioCapblty:
			CMCHKPK(cmPkSztUERadioCapblty, &param->u.sztUERadioCapblty, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueUECapbltyInfoIndIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_UECapbltyInfoIndIEs
*  DESC: Function to Pack SztProtIE_Field_UECapbltyInfoIndIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_UECapbltyInfoIndIEs
(
SztProtIE_Field_UECapbltyInfoIndIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_UECapbltyInfoIndIEs(param, mBuf)
SztProtIE_Field_UECapbltyInfoIndIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_UECapbltyInfoIndIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueUECapbltyInfoIndIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_UECapbltyInfoIndIEs */



/* 
* FUN : cmPkSztProtIE_Cont_UECapbltyInfoIndIEs
*  DESC: Function to Pack SztProtIE_Cont_UECapbltyInfoIndIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_UECapbltyInfoIndIEs
(
SztProtIE_Cont_UECapbltyInfoIndIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_UECapbltyInfoIndIEs(param, mBuf)
SztProtIE_Cont_UECapbltyInfoIndIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_UECapbltyInfoIndIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_UECapbltyInfoIndIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_UECapbltyInfoIndIEs */



/* 
* FUN : cmPkSztUECapbltyInfoInd
*  DESC: Function to Pack SztUECapbltyInfoInd structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztUECapbltyInfoInd
(
SztUECapbltyInfoInd *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztUECapbltyInfoInd(param, mBuf)
SztUECapbltyInfoInd *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztUECapbltyInfoInd) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_UECapbltyInfoIndIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztUECapbltyInfoInd */



/* 
* FUN : cmPkSzt_ValueENBStatusTfrIEsCls
*  DESC: Function to Pack Szt_ValueENBStatusTfrIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueENBStatusTfrIEsCls
(
Szt_ValueENBStatusTfrIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueENBStatusTfrIEsCls(param, val, mBuf)
Szt_ValueENBStatusTfrIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueENBStatusTfrIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_StatusTfr_TprntCont:
			CMCHKPK(cmPkSztENB_StatusTfr_TprntCont, &param->u.sztENB_StatusTfr_TprntCont, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueENBStatusTfrIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_ENBStatusTfrIEs
*  DESC: Function to Pack SztProtIE_Field_ENBStatusTfrIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_ENBStatusTfrIEs
(
SztProtIE_Field_ENBStatusTfrIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_ENBStatusTfrIEs(param, mBuf)
SztProtIE_Field_ENBStatusTfrIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_ENBStatusTfrIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueENBStatusTfrIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_ENBStatusTfrIEs */



/* 
* FUN : cmPkSztProtIE_Cont_ENBStatusTfrIEs
*  DESC: Function to Pack SztProtIE_Cont_ENBStatusTfrIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_ENBStatusTfrIEs
(
SztProtIE_Cont_ENBStatusTfrIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_ENBStatusTfrIEs(param, mBuf)
SztProtIE_Cont_ENBStatusTfrIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_ENBStatusTfrIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_ENBStatusTfrIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_ENBStatusTfrIEs */



/* 
* FUN : cmPkSztENBStatusTfr
*  DESC: Function to Pack SztENBStatusTfr structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztENBStatusTfr
(
SztENBStatusTfr *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztENBStatusTfr(param, mBuf)
SztENBStatusTfr *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztENBStatusTfr) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_ENBStatusTfrIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztENBStatusTfr */



/* 
* FUN : cmPkSzt_ValueMMEStatusTfrIEsCls
*  DESC: Function to Pack Szt_ValueMMEStatusTfrIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueMMEStatusTfrIEsCls
(
Szt_ValueMMEStatusTfrIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueMMEStatusTfrIEsCls(param, val, mBuf)
Szt_ValueMMEStatusTfrIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueMMEStatusTfrIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_StatusTfr_TprntCont:
			CMCHKPK(cmPkSztENB_StatusTfr_TprntCont, &param->u.sztENB_StatusTfr_TprntCont, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueMMEStatusTfrIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_MMEStatusTfrIEs
*  DESC: Function to Pack SztProtIE_Field_MMEStatusTfrIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_MMEStatusTfrIEs
(
SztProtIE_Field_MMEStatusTfrIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_MMEStatusTfrIEs(param, mBuf)
SztProtIE_Field_MMEStatusTfrIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_MMEStatusTfrIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueMMEStatusTfrIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_MMEStatusTfrIEs */



/* 
* FUN : cmPkSztProtIE_Cont_MMEStatusTfrIEs
*  DESC: Function to Pack SztProtIE_Cont_MMEStatusTfrIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_MMEStatusTfrIEs
(
SztProtIE_Cont_MMEStatusTfrIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_MMEStatusTfrIEs(param, mBuf)
SztProtIE_Cont_MMEStatusTfrIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_MMEStatusTfrIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_MMEStatusTfrIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_MMEStatusTfrIEs */



/* 
* FUN : cmPkSztMMEStatusTfr
*  DESC: Function to Pack SztMMEStatusTfr structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztMMEStatusTfr
(
SztMMEStatusTfr *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztMMEStatusTfr(param, mBuf)
SztMMEStatusTfr *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztMMEStatusTfr) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_MMEStatusTfrIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztMMEStatusTfr */



/* 
* FUN : cmPkSzt_ValueTraceStartIEsCls
*  DESC: Function to Pack Szt_ValueTraceStartIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueTraceStartIEsCls
(
Szt_ValueTraceStartIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueTraceStartIEsCls(param, val, mBuf)
Szt_ValueTraceStartIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueTraceStartIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_TraceActvn:
			CMCHKPK(cmPkSztTraceActvn, &param->u.sztTraceActvn, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueTraceStartIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_TraceStartIEs
*  DESC: Function to Pack SztProtIE_Field_TraceStartIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_TraceStartIEs
(
SztProtIE_Field_TraceStartIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_TraceStartIEs(param, mBuf)
SztProtIE_Field_TraceStartIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_TraceStartIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueTraceStartIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_TraceStartIEs */



/* 
* FUN : cmPkSztProtIE_Cont_TraceStartIEs
*  DESC: Function to Pack SztProtIE_Cont_TraceStartIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_TraceStartIEs
(
SztProtIE_Cont_TraceStartIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_TraceStartIEs(param, mBuf)
SztProtIE_Cont_TraceStartIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_TraceStartIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_TraceStartIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_TraceStartIEs */



/* 
* FUN : cmPkSztTraceStart
*  DESC: Function to Pack SztTraceStart structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztTraceStart
(
SztTraceStart *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztTraceStart(param, mBuf)
SztTraceStart *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztTraceStart) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_TraceStartIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztTraceStart */



/* 
* FUN : cmPkSzt_ValueTraceFailIndIEsCls
*  DESC: Function to Pack Szt_ValueTraceFailIndIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueTraceFailIndIEsCls
(
Szt_ValueTraceFailIndIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueTraceFailIndIEsCls(param, val, mBuf)
Szt_ValueTraceFailIndIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueTraceFailIndIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_E_UTRAN_Trace_ID:
			CMCHKPK(cmPkSztE_UTRAN_Trace_ID, &param->u.sztE_UTRAN_Trace_ID, mBuf);
			break;
		case Sztid_Cause:
			CMCHKPK(cmPkSztCause, &param->u.sztCause, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueTraceFailIndIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_TraceFailIndIEs
*  DESC: Function to Pack SztProtIE_Field_TraceFailIndIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_TraceFailIndIEs
(
SztProtIE_Field_TraceFailIndIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_TraceFailIndIEs(param, mBuf)
SztProtIE_Field_TraceFailIndIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_TraceFailIndIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueTraceFailIndIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_TraceFailIndIEs */



/* 
* FUN : cmPkSztProtIE_Cont_TraceFailIndIEs
*  DESC: Function to Pack SztProtIE_Cont_TraceFailIndIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_TraceFailIndIEs
(
SztProtIE_Cont_TraceFailIndIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_TraceFailIndIEs(param, mBuf)
SztProtIE_Cont_TraceFailIndIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_TraceFailIndIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_TraceFailIndIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_TraceFailIndIEs */



/* 
* FUN : cmPkSztTraceFailInd
*  DESC: Function to Pack SztTraceFailInd structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztTraceFailInd
(
SztTraceFailInd *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztTraceFailInd(param, mBuf)
SztTraceFailInd *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztTraceFailInd) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_TraceFailIndIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztTraceFailInd */



/* 
* FUN : cmPkSzt_ValueDeactvTraceIEsCls
*  DESC: Function to Pack Szt_ValueDeactvTraceIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueDeactvTraceIEsCls
(
Szt_ValueDeactvTraceIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueDeactvTraceIEsCls(param, val, mBuf)
Szt_ValueDeactvTraceIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueDeactvTraceIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_E_UTRAN_Trace_ID:
			CMCHKPK(cmPkSztE_UTRAN_Trace_ID, &param->u.sztE_UTRAN_Trace_ID, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueDeactvTraceIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_DeactvTraceIEs
*  DESC: Function to Pack SztProtIE_Field_DeactvTraceIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_DeactvTraceIEs
(
SztProtIE_Field_DeactvTraceIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_DeactvTraceIEs(param, mBuf)
SztProtIE_Field_DeactvTraceIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_DeactvTraceIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueDeactvTraceIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_DeactvTraceIEs */



/* 
* FUN : cmPkSztProtIE_Cont_DeactvTraceIEs
*  DESC: Function to Pack SztProtIE_Cont_DeactvTraceIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_DeactvTraceIEs
(
SztProtIE_Cont_DeactvTraceIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_DeactvTraceIEs(param, mBuf)
SztProtIE_Cont_DeactvTraceIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_DeactvTraceIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_DeactvTraceIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_DeactvTraceIEs */



/* 
* FUN : cmPkSztDeactvTrace
*  DESC: Function to Pack SztDeactvTrace structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztDeactvTrace
(
SztDeactvTrace *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztDeactvTrace(param, mBuf)
SztDeactvTrace *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztDeactvTrace) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_DeactvTraceIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztDeactvTrace */



/* 
* FUN : cmPkSzt_ValueCellTrafficTraceIEsCls
*  DESC: Function to Pack Szt_ValueCellTrafficTraceIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueCellTrafficTraceIEsCls
(
Szt_ValueCellTrafficTraceIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueCellTrafficTraceIEsCls(param, val, mBuf)
Szt_ValueCellTrafficTraceIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueCellTrafficTraceIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_E_UTRAN_Trace_ID:
			CMCHKPK(cmPkSztE_UTRAN_Trace_ID, &param->u.sztE_UTRAN_Trace_ID, mBuf);
			break;
		case Sztid_EUTRAN_CGI:
			CMCHKPK(cmPkSztEUTRAN_CGI, &param->u.sztEUTRAN_CGI, mBuf);
			break;
		case Sztid_TraceCollectionEntityIPAddr:
			CMCHKPK(cmPkSztTportLyrAddr, &param->u.sztTportLyrAddr, mBuf);
			break;
		case Sztid_PrivacyIndicator:
			CMCHKPK(cmPkSztPrivacyIndicator, &param->u.sztPrivacyIndicator, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueCellTrafficTraceIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_CellTrafficTraceIEs
*  DESC: Function to Pack SztProtIE_Field_CellTrafficTraceIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_CellTrafficTraceIEs
(
SztProtIE_Field_CellTrafficTraceIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_CellTrafficTraceIEs(param, mBuf)
SztProtIE_Field_CellTrafficTraceIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_CellTrafficTraceIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueCellTrafficTraceIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_CellTrafficTraceIEs */



/* 
* FUN : cmPkSztProtIE_Cont_CellTrafficTraceIEs
*  DESC: Function to Pack SztProtIE_Cont_CellTrafficTraceIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_CellTrafficTraceIEs
(
SztProtIE_Cont_CellTrafficTraceIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_CellTrafficTraceIEs(param, mBuf)
SztProtIE_Cont_CellTrafficTraceIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_CellTrafficTraceIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_CellTrafficTraceIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_CellTrafficTraceIEs */



/* 
* FUN : cmPkSztCellTrafficTrace
*  DESC: Function to Pack SztCellTrafficTrace structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztCellTrafficTrace
(
SztCellTrafficTrace *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztCellTrafficTrace(param, mBuf)
SztCellTrafficTrace *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztCellTrafficTrace) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_CellTrafficTraceIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztCellTrafficTrace */



/* 
* FUN : cmPkSzt_ValueLocRprtngCntrlIEsCls
*  DESC: Function to Pack Szt_ValueLocRprtngCntrlIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueLocRprtngCntrlIEsCls
(
Szt_ValueLocRprtngCntrlIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueLocRprtngCntrlIEsCls(param, val, mBuf)
Szt_ValueLocRprtngCntrlIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueLocRprtngCntrlIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_RqstTyp:
			CMCHKPK(cmPkSztRqstTyp, &param->u.sztRqstTyp, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueLocRprtngCntrlIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_LocRprtngCntrlIEs
*  DESC: Function to Pack SztProtIE_Field_LocRprtngCntrlIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_LocRprtngCntrlIEs
(
SztProtIE_Field_LocRprtngCntrlIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_LocRprtngCntrlIEs(param, mBuf)
SztProtIE_Field_LocRprtngCntrlIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_LocRprtngCntrlIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueLocRprtngCntrlIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_LocRprtngCntrlIEs */



/* 
* FUN : cmPkSztProtIE_Cont_LocRprtngCntrlIEs
*  DESC: Function to Pack SztProtIE_Cont_LocRprtngCntrlIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_LocRprtngCntrlIEs
(
SztProtIE_Cont_LocRprtngCntrlIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_LocRprtngCntrlIEs(param, mBuf)
SztProtIE_Cont_LocRprtngCntrlIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_LocRprtngCntrlIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_LocRprtngCntrlIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_LocRprtngCntrlIEs */



/* 
* FUN : cmPkSztLocRprtngCntrl
*  DESC: Function to Pack SztLocRprtngCntrl structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztLocRprtngCntrl
(
SztLocRprtngCntrl *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztLocRprtngCntrl(param, mBuf)
SztLocRprtngCntrl *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztLocRprtngCntrl) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_LocRprtngCntrlIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztLocRprtngCntrl */



/* 
* FUN : cmPkSzt_ValueLocRprtngFailIndIEsCls
*  DESC: Function to Pack Szt_ValueLocRprtngFailIndIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueLocRprtngFailIndIEsCls
(
Szt_ValueLocRprtngFailIndIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueLocRprtngFailIndIEsCls(param, val, mBuf)
Szt_ValueLocRprtngFailIndIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueLocRprtngFailIndIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_Cause:
			CMCHKPK(cmPkSztCause, &param->u.sztCause, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueLocRprtngFailIndIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_LocRprtngFailIndIEs
*  DESC: Function to Pack SztProtIE_Field_LocRprtngFailIndIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_LocRprtngFailIndIEs
(
SztProtIE_Field_LocRprtngFailIndIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_LocRprtngFailIndIEs(param, mBuf)
SztProtIE_Field_LocRprtngFailIndIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_LocRprtngFailIndIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueLocRprtngFailIndIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_LocRprtngFailIndIEs */



/* 
* FUN : cmPkSztProtIE_Cont_LocRprtngFailIndIEs
*  DESC: Function to Pack SztProtIE_Cont_LocRprtngFailIndIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_LocRprtngFailIndIEs
(
SztProtIE_Cont_LocRprtngFailIndIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_LocRprtngFailIndIEs(param, mBuf)
SztProtIE_Cont_LocRprtngFailIndIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_LocRprtngFailIndIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_LocRprtngFailIndIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_LocRprtngFailIndIEs */



/* 
* FUN : cmPkSztLocRprtngFailInd
*  DESC: Function to Pack SztLocRprtngFailInd structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztLocRprtngFailInd
(
SztLocRprtngFailInd *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztLocRprtngFailInd(param, mBuf)
SztLocRprtngFailInd *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztLocRprtngFailInd) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_LocRprtngFailIndIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztLocRprtngFailInd */



/* 
* FUN : cmPkSzt_ValueLocReportIEsCls
*  DESC: Function to Pack Szt_ValueLocReportIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueLocReportIEsCls
(
Szt_ValueLocReportIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueLocReportIEsCls(param, val, mBuf)
Szt_ValueLocReportIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueLocReportIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_EUTRAN_CGI:
			CMCHKPK(cmPkSztEUTRAN_CGI, &param->u.sztEUTRAN_CGI, mBuf);
			break;
		case Sztid_TAI:
			CMCHKPK(cmPkSztTAI, &param->u.sztTAI, mBuf);
			break;
		case Sztid_RqstTyp:
			CMCHKPK(cmPkSztRqstTyp, &param->u.sztRqstTyp, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueLocReportIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_LocReportIEs
*  DESC: Function to Pack SztProtIE_Field_LocReportIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_LocReportIEs
(
SztProtIE_Field_LocReportIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_LocReportIEs(param, mBuf)
SztProtIE_Field_LocReportIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_LocReportIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueLocReportIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_LocReportIEs */



/* 
* FUN : cmPkSztProtIE_Cont_LocReportIEs
*  DESC: Function to Pack SztProtIE_Cont_LocReportIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_LocReportIEs
(
SztProtIE_Cont_LocReportIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_LocReportIEs(param, mBuf)
SztProtIE_Cont_LocReportIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_LocReportIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_LocReportIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_LocReportIEs */



/* 
* FUN : cmPkSztLocReport
*  DESC: Function to Pack SztLocReport structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztLocReport
(
SztLocReport *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztLocReport(param, mBuf)
SztLocReport *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztLocReport) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_LocReportIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztLocReport */



/* 
* FUN : cmPkSzt_ValueOverloadStartIEsCls
*  DESC: Function to Pack Szt_ValueOverloadStartIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueOverloadStartIEsCls
(
Szt_ValueOverloadStartIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueOverloadStartIEsCls(param, val, mBuf)
Szt_ValueOverloadStartIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueOverloadStartIEsCls) 
	
	switch (val)
	{
		case Sztid_OverloadResp:
			CMCHKPK(cmPkSztOverloadResp, &param->u.sztOverloadResp, mBuf);
			break;
		case Sztid_GUMMEILst:
			CMCHKPK(cmPkSztGUMMEILst, &param->u.sztGUMMEILst, mBuf);
			break;
		case Sztid_TrafficLoadReductionInd:
			CMCHKPK(cmPkSztTrafficLoadReductionInd, &param->u.sztTrafficLoadReductionInd, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueOverloadStartIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_OverloadStartIEs
*  DESC: Function to Pack SztProtIE_Field_OverloadStartIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_OverloadStartIEs
(
SztProtIE_Field_OverloadStartIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_OverloadStartIEs(param, mBuf)
SztProtIE_Field_OverloadStartIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_OverloadStartIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueOverloadStartIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_OverloadStartIEs */



/* 
* FUN : cmPkSztProtIE_Cont_OverloadStartIEs
*  DESC: Function to Pack SztProtIE_Cont_OverloadStartIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_OverloadStartIEs
(
SztProtIE_Cont_OverloadStartIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_OverloadStartIEs(param, mBuf)
SztProtIE_Cont_OverloadStartIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_OverloadStartIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_OverloadStartIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_OverloadStartIEs */



/* 
* FUN : cmPkSztOverloadStart
*  DESC: Function to Pack SztOverloadStart structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztOverloadStart
(
SztOverloadStart *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztOverloadStart(param, mBuf)
SztOverloadStart *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztOverloadStart) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_OverloadStartIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztOverloadStart */



/* 
* FUN : cmPkSzt_ValueOverloadStopIEsCls
*  DESC: Function to Pack Szt_ValueOverloadStopIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueOverloadStopIEsCls
(
Szt_ValueOverloadStopIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueOverloadStopIEsCls(param, val, mBuf)
Szt_ValueOverloadStopIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueOverloadStopIEsCls) 
	
	switch (val)
	{
		case Sztid_GUMMEILst:
			CMCHKPK(cmPkSztGUMMEILst, &param->u.sztGUMMEILst, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueOverloadStopIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_OverloadStopIEs
*  DESC: Function to Pack SztProtIE_Field_OverloadStopIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_OverloadStopIEs
(
SztProtIE_Field_OverloadStopIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_OverloadStopIEs(param, mBuf)
SztProtIE_Field_OverloadStopIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_OverloadStopIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueOverloadStopIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_OverloadStopIEs */



/* 
* FUN : cmPkSztProtIE_Cont_OverloadStopIEs
*  DESC: Function to Pack SztProtIE_Cont_OverloadStopIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_OverloadStopIEs
(
SztProtIE_Cont_OverloadStopIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_OverloadStopIEs(param, mBuf)
SztProtIE_Cont_OverloadStopIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_OverloadStopIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_OverloadStopIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_OverloadStopIEs */



/* 
* FUN : cmPkSztOverloadStop
*  DESC: Function to Pack SztOverloadStop structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztOverloadStop
(
SztOverloadStop *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztOverloadStop(param, mBuf)
SztOverloadStop *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztOverloadStop) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_OverloadStopIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztOverloadStop */



/* 
* FUN : cmPkSzt_ValueWriteReplaceWarningRqstIEsCls
*  DESC: Function to Pack Szt_ValueWriteReplaceWarningRqstIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueWriteReplaceWarningRqstIEsCls
(
Szt_ValueWriteReplaceWarningRqstIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueWriteReplaceWarningRqstIEsCls(param, val, mBuf)
Szt_ValueWriteReplaceWarningRqstIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueWriteReplaceWarningRqstIEsCls) 
	
	switch (val)
	{
		case Sztid_MsgIdentifier:
			CMCHKPK(cmPkSztMsgIdentifier, &param->u.sztMsgIdentifier, mBuf);
			break;
		case Sztid_SerialNumber:
			CMCHKPK(cmPkSztSerialNumber, &param->u.sztSerialNumber, mBuf);
			break;
		case Sztid_WarningAreaLst:
			CMCHKPK(cmPkSztWarningAreaLst, &param->u.sztWarningAreaLst, mBuf);
			break;
		case Sztid_RepetitionPeriod:
			CMCHKPK(cmPkSztRepetitionPeriod, &param->u.sztRepetitionPeriod, mBuf);
			break;
		case Sztid_ExtendedRepetitionPeriod:
			CMCHKPK(cmPkSztExtendedRepetitionPeriod, &param->u.sztExtendedRepetitionPeriod, mBuf);
			break;
		case Sztid_NumberofBroadcastRqst:
			CMCHKPK(cmPkSztNumberofBroadcastRqst, &param->u.sztNumberofBroadcastRqst, mBuf);
			break;
		case Sztid_WarningTyp:
			CMCHKPK(cmPkSztWarningTyp, &param->u.sztWarningTyp, mBuf);
			break;
		case Sztid_WarningSecurInfo:
			CMCHKPK(cmPkSztWarningSecurInfo, &param->u.sztWarningSecurInfo, mBuf);
			break;
		case Sztid_DataCodingScheme:
			CMCHKPK(cmPkSztDataCodingScheme, &param->u.sztDataCodingScheme, mBuf);
			break;
		case Sztid_WarningMsgContents:
			CMCHKPK(cmPkSztWarningMsgContents, &param->u.sztWarningMsgContents, mBuf);
			break;
		case Sztid_ConcurrentWarningMsgIndicator:
			CMCHKPK(cmPkSztConcurrentWarningMsgIndicator, &param->u.sztConcurrentWarningMsgIndicator, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueWriteReplaceWarningRqstIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_WriteReplaceWarningRqstIEs
*  DESC: Function to Pack SztProtIE_Field_WriteReplaceWarningRqstIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_WriteReplaceWarningRqstIEs
(
SztProtIE_Field_WriteReplaceWarningRqstIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_WriteReplaceWarningRqstIEs(param, mBuf)
SztProtIE_Field_WriteReplaceWarningRqstIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_WriteReplaceWarningRqstIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueWriteReplaceWarningRqstIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_WriteReplaceWarningRqstIEs */



/* 
* FUN : cmPkSztProtIE_Cont_WriteReplaceWarningRqstIEs
*  DESC: Function to Pack SztProtIE_Cont_WriteReplaceWarningRqstIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_WriteReplaceWarningRqstIEs
(
SztProtIE_Cont_WriteReplaceWarningRqstIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_WriteReplaceWarningRqstIEs(param, mBuf)
SztProtIE_Cont_WriteReplaceWarningRqstIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_WriteReplaceWarningRqstIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_WriteReplaceWarningRqstIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_WriteReplaceWarningRqstIEs */



/* 
* FUN : cmPkSztWriteReplaceWarningRqst
*  DESC: Function to Pack SztWriteReplaceWarningRqst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztWriteReplaceWarningRqst
(
SztWriteReplaceWarningRqst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztWriteReplaceWarningRqst(param, mBuf)
SztWriteReplaceWarningRqst *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztWriteReplaceWarningRqst) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_WriteReplaceWarningRqstIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztWriteReplaceWarningRqst */



/* 
* FUN : cmPkSzt_ValueWriteReplaceWarningRespIEsCls
*  DESC: Function to Pack Szt_ValueWriteReplaceWarningRespIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueWriteReplaceWarningRespIEsCls
(
Szt_ValueWriteReplaceWarningRespIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueWriteReplaceWarningRespIEsCls(param, val, mBuf)
Szt_ValueWriteReplaceWarningRespIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueWriteReplaceWarningRespIEsCls) 
	
	switch (val)
	{
		case Sztid_MsgIdentifier:
			CMCHKPK(cmPkSztMsgIdentifier, &param->u.sztMsgIdentifier, mBuf);
			break;
		case Sztid_SerialNumber:
			CMCHKPK(cmPkSztSerialNumber, &param->u.sztSerialNumber, mBuf);
			break;
		case Sztid_BroadcastCompletedAreaLst:
			CMCHKPK(cmPkSztBroadcastCompletedAreaLst, &param->u.sztBroadcastCompletedAreaLst, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKPK(cmPkSztCriticalityDiag, &param->u.sztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueWriteReplaceWarningRespIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_WriteReplaceWarningRespIEs
*  DESC: Function to Pack SztProtIE_Field_WriteReplaceWarningRespIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_WriteReplaceWarningRespIEs
(
SztProtIE_Field_WriteReplaceWarningRespIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_WriteReplaceWarningRespIEs(param, mBuf)
SztProtIE_Field_WriteReplaceWarningRespIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_WriteReplaceWarningRespIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueWriteReplaceWarningRespIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_WriteReplaceWarningRespIEs */



/* 
* FUN : cmPkSztProtIE_Cont_WriteReplaceWarningRespIEs
*  DESC: Function to Pack SztProtIE_Cont_WriteReplaceWarningRespIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_WriteReplaceWarningRespIEs
(
SztProtIE_Cont_WriteReplaceWarningRespIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_WriteReplaceWarningRespIEs(param, mBuf)
SztProtIE_Cont_WriteReplaceWarningRespIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_WriteReplaceWarningRespIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_WriteReplaceWarningRespIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_WriteReplaceWarningRespIEs */



/* 
* FUN : cmPkSztWriteReplaceWarningResp
*  DESC: Function to Pack SztWriteReplaceWarningResp structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztWriteReplaceWarningResp
(
SztWriteReplaceWarningResp *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztWriteReplaceWarningResp(param, mBuf)
SztWriteReplaceWarningResp *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztWriteReplaceWarningResp) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_WriteReplaceWarningRespIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztWriteReplaceWarningResp */



/* 
* FUN : cmPkSztInter_SystemInformTfrTyp
*  DESC: Function to Pack SztInter_SystemInformTfrTyp structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztInter_SystemInformTfrTyp
(
SztInter_SystemInformTfrTyp *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztInter_SystemInformTfrTyp(param, mBuf)
SztInter_SystemInformTfrTyp *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztInter_SystemInformTfrTyp) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case INTER_SYSTEMINFORMTFRTYP_RIMTFR :
				CMCHKPK(cmPkSztRIMTfr, &param->val.rIMTfr, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztInter_SystemInformTfrTyp */



/* 
* FUN : cmPkSzt_ValueENBDirectInformTfrIEsCls
*  DESC: Function to Pack Szt_ValueENBDirectInformTfrIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueENBDirectInformTfrIEsCls
(
Szt_ValueENBDirectInformTfrIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueENBDirectInformTfrIEsCls(param, val, mBuf)
Szt_ValueENBDirectInformTfrIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueENBDirectInformTfrIEsCls) 
	
	switch (val)
	{
		case Sztid_Inter_SystemInformTfrTypEDT:
			CMCHKPK(cmPkSztInter_SystemInformTfrTyp, &param->u.sztInter_SystemInformTfrTyp, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueENBDirectInformTfrIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_ENBDirectInformTfrIEs
*  DESC: Function to Pack SztProtIE_Field_ENBDirectInformTfrIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_ENBDirectInformTfrIEs
(
SztProtIE_Field_ENBDirectInformTfrIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_ENBDirectInformTfrIEs(param, mBuf)
SztProtIE_Field_ENBDirectInformTfrIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_ENBDirectInformTfrIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueENBDirectInformTfrIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_ENBDirectInformTfrIEs */



/* 
* FUN : cmPkSztProtIE_Cont_ENBDirectInformTfrIEs
*  DESC: Function to Pack SztProtIE_Cont_ENBDirectInformTfrIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_ENBDirectInformTfrIEs
(
SztProtIE_Cont_ENBDirectInformTfrIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_ENBDirectInformTfrIEs(param, mBuf)
SztProtIE_Cont_ENBDirectInformTfrIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_ENBDirectInformTfrIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_ENBDirectInformTfrIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_ENBDirectInformTfrIEs */



/* 
* FUN : cmPkSztENBDirectInformTfr
*  DESC: Function to Pack SztENBDirectInformTfr structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztENBDirectInformTfr
(
SztENBDirectInformTfr *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztENBDirectInformTfr(param, mBuf)
SztENBDirectInformTfr *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztENBDirectInformTfr) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_ENBDirectInformTfrIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztENBDirectInformTfr */



/* 
* FUN : cmPkSzt_ValueMMEDirectInformTfrIEsCls
*  DESC: Function to Pack Szt_ValueMMEDirectInformTfrIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueMMEDirectInformTfrIEsCls
(
Szt_ValueMMEDirectInformTfrIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueMMEDirectInformTfrIEsCls(param, val, mBuf)
Szt_ValueMMEDirectInformTfrIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueMMEDirectInformTfrIEsCls) 
	
	switch (val)
	{
		case Sztid_Inter_SystemInformTfrTypMDT:
			CMCHKPK(cmPkSztInter_SystemInformTfrTyp, &param->u.sztInter_SystemInformTfrTyp, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueMMEDirectInformTfrIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_MMEDirectInformTfrIEs
*  DESC: Function to Pack SztProtIE_Field_MMEDirectInformTfrIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_MMEDirectInformTfrIEs
(
SztProtIE_Field_MMEDirectInformTfrIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_MMEDirectInformTfrIEs(param, mBuf)
SztProtIE_Field_MMEDirectInformTfrIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_MMEDirectInformTfrIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueMMEDirectInformTfrIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_MMEDirectInformTfrIEs */



/* 
* FUN : cmPkSztProtIE_Cont_MMEDirectInformTfrIEs
*  DESC: Function to Pack SztProtIE_Cont_MMEDirectInformTfrIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_MMEDirectInformTfrIEs
(
SztProtIE_Cont_MMEDirectInformTfrIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_MMEDirectInformTfrIEs(param, mBuf)
SztProtIE_Cont_MMEDirectInformTfrIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_MMEDirectInformTfrIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_MMEDirectInformTfrIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_MMEDirectInformTfrIEs */



/* 
* FUN : cmPkSztMMEDirectInformTfr
*  DESC: Function to Pack SztMMEDirectInformTfr structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztMMEDirectInformTfr
(
SztMMEDirectInformTfr *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztMMEDirectInformTfr(param, mBuf)
SztMMEDirectInformTfr *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztMMEDirectInformTfr) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_MMEDirectInformTfrIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztMMEDirectInformTfr */



/* 
* FUN : cmPkSzt_ValueENBConfigTfrIEsCls
*  DESC: Function to Pack Szt_ValueENBConfigTfrIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueENBConfigTfrIEsCls
(
Szt_ValueENBConfigTfrIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueENBConfigTfrIEsCls(param, val, mBuf)
Szt_ValueENBConfigTfrIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueENBConfigTfrIEsCls) 
	
	switch (val)
	{
		case Sztid_SONConfigTfrECT:
			CMCHKPK(cmPkSztSONConfigTfr, &param->u.sztSONConfigTfr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueENBConfigTfrIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_ENBConfigTfrIEs
*  DESC: Function to Pack SztProtIE_Field_ENBConfigTfrIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_ENBConfigTfrIEs
(
SztProtIE_Field_ENBConfigTfrIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_ENBConfigTfrIEs(param, mBuf)
SztProtIE_Field_ENBConfigTfrIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_ENBConfigTfrIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueENBConfigTfrIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_ENBConfigTfrIEs */



/* 
* FUN : cmPkSztProtIE_Cont_ENBConfigTfrIEs
*  DESC: Function to Pack SztProtIE_Cont_ENBConfigTfrIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_ENBConfigTfrIEs
(
SztProtIE_Cont_ENBConfigTfrIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_ENBConfigTfrIEs(param, mBuf)
SztProtIE_Cont_ENBConfigTfrIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_ENBConfigTfrIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_ENBConfigTfrIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_ENBConfigTfrIEs */



/* 
* FUN : cmPkSztENBConfigTfr
*  DESC: Function to Pack SztENBConfigTfr structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztENBConfigTfr
(
SztENBConfigTfr *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztENBConfigTfr(param, mBuf)
SztENBConfigTfr *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztENBConfigTfr) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_ENBConfigTfrIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztENBConfigTfr */



/* 
* FUN : cmPkSzt_ValueMMEConfigTfrIEsCls
*  DESC: Function to Pack Szt_ValueMMEConfigTfrIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueMMEConfigTfrIEsCls
(
Szt_ValueMMEConfigTfrIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueMMEConfigTfrIEsCls(param, val, mBuf)
Szt_ValueMMEConfigTfrIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueMMEConfigTfrIEsCls) 
	
	switch (val)
	{
		case Sztid_SONConfigTfrMCT:
			CMCHKPK(cmPkSztSONConfigTfr, &param->u.sztSONConfigTfr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueMMEConfigTfrIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_MMEConfigTfrIEs
*  DESC: Function to Pack SztProtIE_Field_MMEConfigTfrIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_MMEConfigTfrIEs
(
SztProtIE_Field_MMEConfigTfrIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_MMEConfigTfrIEs(param, mBuf)
SztProtIE_Field_MMEConfigTfrIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_MMEConfigTfrIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueMMEConfigTfrIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_MMEConfigTfrIEs */



/* 
* FUN : cmPkSztProtIE_Cont_MMEConfigTfrIEs
*  DESC: Function to Pack SztProtIE_Cont_MMEConfigTfrIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_MMEConfigTfrIEs
(
SztProtIE_Cont_MMEConfigTfrIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_MMEConfigTfrIEs(param, mBuf)
SztProtIE_Cont_MMEConfigTfrIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_MMEConfigTfrIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_MMEConfigTfrIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_MMEConfigTfrIEs */



/* 
* FUN : cmPkSztMMEConfigTfr
*  DESC: Function to Pack SztMMEConfigTfr structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztMMEConfigTfr
(
SztMMEConfigTfr *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztMMEConfigTfr(param, mBuf)
SztMMEConfigTfr *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztMMEConfigTfr) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_MMEConfigTfrIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztMMEConfigTfr */



/* 
* FUN : cmPkSzt_ValuePrivMsgIEsCls
*  DESC: Function to Pack Szt_ValuePrivMsgIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValuePrivMsgIEsCls
(
Szt_ValuePrivMsgIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValuePrivMsgIEsCls(param, val, mBuf)
Szt_ValuePrivMsgIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValuePrivMsgIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkSzt_ValuePrivMsgIEsCls */



/* 
* FUN : cmPkSztPrivIE_Field_PrivMsgIEs
*  DESC: Function to Pack SztPrivIE_Field_PrivMsgIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztPrivIE_Field_PrivMsgIEs
(
SztPrivIE_Field_PrivMsgIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztPrivIE_Field_PrivMsgIEs(param, mBuf)
SztPrivIE_Field_PrivMsgIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztPrivIE_Field_PrivMsgIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztPrivIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztPrivIE_Field_PrivMsgIEs */



/* 
* FUN : cmPkSztPrivIE_Cont_PrivMsgIEs
*  DESC: Function to Pack SztPrivIE_Cont_PrivMsgIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztPrivIE_Cont_PrivMsgIEs
(
SztPrivIE_Cont_PrivMsgIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztPrivIE_Cont_PrivMsgIEs(param, mBuf)
SztPrivIE_Cont_PrivMsgIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztPrivIE_Cont_PrivMsgIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztPrivIE_Field_PrivMsgIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztPrivIE_Cont_PrivMsgIEs */



/* 
* FUN : cmPkSztPrivMsg
*  DESC: Function to Pack SztPrivMsg structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztPrivMsg
(
SztPrivMsg *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztPrivMsg(param, mBuf)
SztPrivMsg *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztPrivMsg) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztPrivIE_Cont_PrivMsgIEs, &param->privateIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztPrivMsg */



/* 
* FUN : cmPkSzt_ValueKillRqstIEsCls
*  DESC: Function to Pack Szt_ValueKillRqstIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueKillRqstIEsCls
(
Szt_ValueKillRqstIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueKillRqstIEsCls(param, val, mBuf)
Szt_ValueKillRqstIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueKillRqstIEsCls) 
	
	switch (val)
	{
		case Sztid_MsgIdentifier:
			CMCHKPK(cmPkSztMsgIdentifier, &param->u.sztMsgIdentifier, mBuf);
			break;
		case Sztid_SerialNumber:
			CMCHKPK(cmPkSztSerialNumber, &param->u.sztSerialNumber, mBuf);
			break;
		case Sztid_WarningAreaLst:
			CMCHKPK(cmPkSztWarningAreaLst, &param->u.sztWarningAreaLst, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueKillRqstIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_KillRqstIEs
*  DESC: Function to Pack SztProtIE_Field_KillRqstIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_KillRqstIEs
(
SztProtIE_Field_KillRqstIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_KillRqstIEs(param, mBuf)
SztProtIE_Field_KillRqstIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_KillRqstIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueKillRqstIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_KillRqstIEs */



/* 
* FUN : cmPkSztProtIE_Cont_KillRqstIEs
*  DESC: Function to Pack SztProtIE_Cont_KillRqstIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_KillRqstIEs
(
SztProtIE_Cont_KillRqstIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_KillRqstIEs(param, mBuf)
SztProtIE_Cont_KillRqstIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_KillRqstIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_KillRqstIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_KillRqstIEs */



/* 
* FUN : cmPkSztKillRqst
*  DESC: Function to Pack SztKillRqst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztKillRqst
(
SztKillRqst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztKillRqst(param, mBuf)
SztKillRqst *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztKillRqst) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_KillRqstIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztKillRqst */



/* 
* FUN : cmPkSzt_ValueKillRespIEsCls
*  DESC: Function to Pack Szt_ValueKillRespIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueKillRespIEsCls
(
Szt_ValueKillRespIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueKillRespIEsCls(param, val, mBuf)
Szt_ValueKillRespIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueKillRespIEsCls) 
	
	switch (val)
	{
		case Sztid_MsgIdentifier:
			CMCHKPK(cmPkSztMsgIdentifier, &param->u.sztMsgIdentifier, mBuf);
			break;
		case Sztid_SerialNumber:
			CMCHKPK(cmPkSztSerialNumber, &param->u.sztSerialNumber, mBuf);
			break;
		case Sztid_BroadcastCancelledAreaLst:
			CMCHKPK(cmPkSztBroadcastCancelledAreaLst, &param->u.sztBroadcastCancelledAreaLst, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKPK(cmPkSztCriticalityDiag, &param->u.sztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueKillRespIEsCls */



/* 
* FUN : cmPkSztProtIE_Field_KillRespIEs
*  DESC: Function to Pack SztProtIE_Field_KillRespIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_KillRespIEs
(
SztProtIE_Field_KillRespIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_KillRespIEs(param, mBuf)
SztProtIE_Field_KillRespIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_KillRespIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueKillRespIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_KillRespIEs */



/* 
* FUN : cmPkSztProtIE_Cont_KillRespIEs
*  DESC: Function to Pack SztProtIE_Cont_KillRespIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_KillRespIEs
(
SztProtIE_Cont_KillRespIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_KillRespIEs(param, mBuf)
SztProtIE_Cont_KillRespIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_KillRespIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_KillRespIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_KillRespIEs */



/* 
* FUN : cmPkSztKillResp
*  DESC: Function to Pack SztKillResp structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztKillResp
(
SztKillResp *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztKillResp(param, mBuf)
SztKillResp *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztKillResp) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_KillRespIEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztKillResp */



/* 
* FUN : cmPkSzt_ValueDlnkUEAssociatedLPPaTport_IEsCls
*  DESC: Function to Pack Szt_ValueDlnkUEAssociatedLPPaTport_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueDlnkUEAssociatedLPPaTport_IEsCls
(
Szt_ValueDlnkUEAssociatedLPPaTport_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueDlnkUEAssociatedLPPaTport_IEsCls(param, val, mBuf)
Szt_ValueDlnkUEAssociatedLPPaTport_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueDlnkUEAssociatedLPPaTport_IEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_Routing_ID:
			CMCHKPK(cmPkSztRouting_ID, &param->u.sztRouting_ID, mBuf);
			break;
		case Sztid_LPPa_PDU:
			CMCHKPK(cmPkSztLPPa_PDU, &param->u.sztLPPa_PDU, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueDlnkUEAssociatedLPPaTport_IEsCls */



/* 
* FUN : cmPkSztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs
*  DESC: Function to Pack SztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs
(
SztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs(param, mBuf)
SztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueDlnkUEAssociatedLPPaTport_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs */



/* 
* FUN : cmPkSztProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs
*  DESC: Function to Pack SztProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs
(
SztProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs(param, mBuf)
SztProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs */



/* 
* FUN : cmPkSztDlnkUEAssociatedLPPaTport
*  DESC: Function to Pack SztDlnkUEAssociatedLPPaTport structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztDlnkUEAssociatedLPPaTport
(
SztDlnkUEAssociatedLPPaTport *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztDlnkUEAssociatedLPPaTport(param, mBuf)
SztDlnkUEAssociatedLPPaTport *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztDlnkUEAssociatedLPPaTport) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztDlnkUEAssociatedLPPaTport */



/* 
* FUN : cmPkSzt_ValueUlnkUEAssociatedLPPaTport_IEsCls
*  DESC: Function to Pack Szt_ValueUlnkUEAssociatedLPPaTport_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueUlnkUEAssociatedLPPaTport_IEsCls
(
Szt_ValueUlnkUEAssociatedLPPaTport_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueUlnkUEAssociatedLPPaTport_IEsCls(param, val, mBuf)
Szt_ValueUlnkUEAssociatedLPPaTport_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueUlnkUEAssociatedLPPaTport_IEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKPK(cmPkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf);
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKPK(cmPkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf);
			break;
		case Sztid_Routing_ID:
			CMCHKPK(cmPkSztRouting_ID, &param->u.sztRouting_ID, mBuf);
			break;
		case Sztid_LPPa_PDU:
			CMCHKPK(cmPkSztLPPa_PDU, &param->u.sztLPPa_PDU, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueUlnkUEAssociatedLPPaTport_IEsCls */



/* 
* FUN : cmPkSztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs
*  DESC: Function to Pack SztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs
(
SztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs(param, mBuf)
SztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueUlnkUEAssociatedLPPaTport_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs */



/* 
* FUN : cmPkSztProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs
*  DESC: Function to Pack SztProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs
(
SztProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs(param, mBuf)
SztProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs */



/* 
* FUN : cmPkSztUlnkUEAssociatedLPPaTport
*  DESC: Function to Pack SztUlnkUEAssociatedLPPaTport structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztUlnkUEAssociatedLPPaTport
(
SztUlnkUEAssociatedLPPaTport *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztUlnkUEAssociatedLPPaTport(param, mBuf)
SztUlnkUEAssociatedLPPaTport *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztUlnkUEAssociatedLPPaTport) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztUlnkUEAssociatedLPPaTport */



/* 
* FUN : cmPkSzt_ValueDlnkNonUEAssociatedLPPaTport_IEsCls
*  DESC: Function to Pack Szt_ValueDlnkNonUEAssociatedLPPaTport_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueDlnkNonUEAssociatedLPPaTport_IEsCls
(
Szt_ValueDlnkNonUEAssociatedLPPaTport_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueDlnkNonUEAssociatedLPPaTport_IEsCls(param, val, mBuf)
Szt_ValueDlnkNonUEAssociatedLPPaTport_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueDlnkNonUEAssociatedLPPaTport_IEsCls) 
	
	switch (val)
	{
		case Sztid_Routing_ID:
			CMCHKPK(cmPkSztRouting_ID, &param->u.sztRouting_ID, mBuf);
			break;
		case Sztid_LPPa_PDU:
			CMCHKPK(cmPkSztLPPa_PDU, &param->u.sztLPPa_PDU, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueDlnkNonUEAssociatedLPPaTport_IEsCls */



/* 
* FUN : cmPkSztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs
*  DESC: Function to Pack SztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs
(
SztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs(param, mBuf)
SztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueDlnkNonUEAssociatedLPPaTport_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs */



/* 
* FUN : cmPkSztProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs
*  DESC: Function to Pack SztProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs
(
SztProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs(param, mBuf)
SztProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs */



/* 
* FUN : cmPkSztDlnkNonUEAssociatedLPPaTport
*  DESC: Function to Pack SztDlnkNonUEAssociatedLPPaTport structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztDlnkNonUEAssociatedLPPaTport
(
SztDlnkNonUEAssociatedLPPaTport *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztDlnkNonUEAssociatedLPPaTport(param, mBuf)
SztDlnkNonUEAssociatedLPPaTport *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztDlnkNonUEAssociatedLPPaTport) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztDlnkNonUEAssociatedLPPaTport */



/* 
* FUN : cmPkSzt_ValueUlnkNonUEAssociatedLPPaTport_IEsCls
*  DESC: Function to Pack Szt_ValueUlnkNonUEAssociatedLPPaTport_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_ValueUlnkNonUEAssociatedLPPaTport_IEsCls
(
Szt_ValueUlnkNonUEAssociatedLPPaTport_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_ValueUlnkNonUEAssociatedLPPaTport_IEsCls(param, val, mBuf)
Szt_ValueUlnkNonUEAssociatedLPPaTport_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_ValueUlnkNonUEAssociatedLPPaTport_IEsCls) 
	
	switch (val)
	{
		case Sztid_Routing_ID:
			CMCHKPK(cmPkSztRouting_ID, &param->u.sztRouting_ID, mBuf);
			break;
		case Sztid_LPPa_PDU:
			CMCHKPK(cmPkSztLPPa_PDU, &param->u.sztLPPa_PDU, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_ValueUlnkNonUEAssociatedLPPaTport_IEsCls */



/* 
* FUN : cmPkSztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs
*  DESC: Function to Pack SztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs
(
SztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs(param, mBuf)
SztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_ValueUlnkNonUEAssociatedLPPaTport_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs */



/* 
* FUN : cmPkSztProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs
*  DESC: Function to Pack SztProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs
(
SztProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs(param, mBuf)
SztProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkSztProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkSztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs */



/* 
* FUN : cmPkSztUlnkNonUEAssociatedLPPaTport
*  DESC: Function to Pack SztUlnkNonUEAssociatedLPPaTport structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztUlnkNonUEAssociatedLPPaTport
(
SztUlnkNonUEAssociatedLPPaTport *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztUlnkNonUEAssociatedLPPaTport(param, mBuf)
SztUlnkNonUEAssociatedLPPaTport *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztUlnkNonUEAssociatedLPPaTport) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkSztProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztUlnkNonUEAssociatedLPPaTport */



/* 
* FUN : cmPkSzt_InitiatingMsgCls
*  DESC: Function to Pack Szt_InitiatingMsgCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_InitiatingMsgCls
(
Szt_InitiatingMsgCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_InitiatingMsgCls(param, val, mBuf)
Szt_InitiatingMsgCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_InitiatingMsgCls) 
	
	switch (val)
	{
		case Sztid_HovrPrep:
			CMCHKPK(cmPkSztHovrReqd, &param->u.sztHovrReqd, mBuf);
			break;
		case Sztid_HovrResourceAllocn:
			CMCHKPK(cmPkSztHovrRqst, &param->u.sztHovrRqst, mBuf);
			break;
		case Sztid_PathSwRqst:
			CMCHKPK(cmPkSztPathSwRqst, &param->u.sztPathSwRqst, mBuf);
			break;
		case Sztid_E_RABSetup:
			CMCHKPK(cmPkSztE_RABSetupRqst, &param->u.sztE_RABSetupRqst, mBuf);
			break;
		case Sztid_E_RABMdfy:
			CMCHKPK(cmPkSztE_RABMdfyRqst, &param->u.sztE_RABMdfyRqst, mBuf);
			break;
		case Sztid_E_RABRls:
			CMCHKPK(cmPkSztE_RABRlsCmmd, &param->u.sztE_RABRlsCmmd, mBuf);
			break;
		case Sztid_InitCntxtSetup:
			CMCHKPK(cmPkSztInitCntxtSetupRqst, &param->u.sztInitCntxtSetupRqst, mBuf);
			break;
		case Sztid_HovrCancel:
			CMCHKPK(cmPkSztHovrCancel, &param->u.sztHovrCancel, mBuf);
			break;
		case Sztid_Kill:
			CMCHKPK(cmPkSztKillRqst, &param->u.sztKillRqst, mBuf);
			break;
		case Sztid_Reset:
			CMCHKPK(cmPkSztReset, &param->u.sztReset, mBuf);
			break;
		case Sztid_S1Setup:
			CMCHKPK(cmPkSztS1SetupRqst, &param->u.sztS1SetupRqst, mBuf);
			break;
		case Sztid_UECntxtModification:
			CMCHKPK(cmPkSztUECntxtModificationRqst, &param->u.sztUECntxtModificationRqst, mBuf);
			break;
		case Sztid_UECntxtRls:
			CMCHKPK(cmPkSztUECntxtRlsCmmd, &param->u.sztUECntxtRlsCmmd, mBuf);
			break;
		case Sztid_ENBConfigUpd:
			CMCHKPK(cmPkSztENBConfigUpd, &param->u.sztENBConfigUpd, mBuf);
			break;
		case Sztid_MMEConfigUpd:
			CMCHKPK(cmPkSztMMEConfigUpd, &param->u.sztMMEConfigUpd, mBuf);
			break;
		case Sztid_WriteReplaceWarning:
			CMCHKPK(cmPkSztWriteReplaceWarningRqst, &param->u.sztWriteReplaceWarningRqst, mBuf);
			break;
		case Sztid_UERadioCapbltyMatch:
			CMCHKPK(cmPkSztUERadioCapbltyMatchRqst, &param->u.sztUERadioCapbltyMatchRqst, mBuf);
			break;
		case Sztid_HovrNotification:
			CMCHKPK(cmPkSztHovrNtfy, &param->u.sztHovrNtfy, mBuf);
			break;
		case Sztid_E_RABRlsInd:
			CMCHKPK(cmPkSztE_RABRlsInd, &param->u.sztE_RABRlsInd, mBuf);
			break;
		case Sztid_Pag:
			CMCHKPK(cmPkSztPag, &param->u.sztPag, mBuf);
			break;
		case Sztid_downlinkNASTport:
			CMCHKPK(cmPkSztDlnkNASTport, &param->u.sztDlnkNASTport, mBuf);
			break;
		case Sztid_initialUEMsg:
			CMCHKPK(cmPkSztInitUEMsg, &param->u.sztInitUEMsg, mBuf);
			break;
		case Sztid_uplinkNASTport:
			CMCHKPK(cmPkSztUlnkNASTport, &param->u.sztUlnkNASTport, mBuf);
			break;
		case Sztid_ErrInd:
			CMCHKPK(cmPkSztErrInd, &param->u.sztErrInd, mBuf);
			break;
		case Sztid_NASNonDlvryInd:
			CMCHKPK(cmPkSztNASNonDlvryInd, &param->u.sztNASNonDlvryInd, mBuf);
			break;
		case Sztid_UECntxtRlsRqst:
			CMCHKPK(cmPkSztUECntxtRlsRqst, &param->u.sztUECntxtRlsRqst, mBuf);
			break;
		case Sztid_DlnkS1cdma2000tunneling:
			CMCHKPK(cmPkSztDlnkS1cdma2000tunneling, &param->u.sztDlnkS1cdma2000tunneling, mBuf);
			break;
		case Sztid_UlnkS1cdma2000tunneling:
			CMCHKPK(cmPkSztUlnkS1cdma2000tunneling, &param->u.sztUlnkS1cdma2000tunneling, mBuf);
			break;
		case Sztid_UECapbltyInfoInd:
			CMCHKPK(cmPkSztUECapbltyInfoInd, &param->u.sztUECapbltyInfoInd, mBuf);
			break;
		case Sztid_eNBStatusTfr:
			CMCHKPK(cmPkSztENBStatusTfr, &param->u.sztENBStatusTfr, mBuf);
			break;
		case Sztid_MMEStatusTfr:
			CMCHKPK(cmPkSztMMEStatusTfr, &param->u.sztMMEStatusTfr, mBuf);
			break;
		case Sztid_DeactvTrace:
			CMCHKPK(cmPkSztDeactvTrace, &param->u.sztDeactvTrace, mBuf);
			break;
		case Sztid_TraceStart:
			CMCHKPK(cmPkSztTraceStart, &param->u.sztTraceStart, mBuf);
			break;
		case Sztid_TraceFailInd:
			CMCHKPK(cmPkSztTraceFailInd, &param->u.sztTraceFailInd, mBuf);
			break;
		case Sztid_CellTrafficTrace:
			CMCHKPK(cmPkSztCellTrafficTrace, &param->u.sztCellTrafficTrace, mBuf);
			break;
		case Sztid_LocRprtngCntrl:
			CMCHKPK(cmPkSztLocRprtngCntrl, &param->u.sztLocRprtngCntrl, mBuf);
			break;
		case Sztid_LocRprtngFailInd:
			CMCHKPK(cmPkSztLocRprtngFailInd, &param->u.sztLocRprtngFailInd, mBuf);
			break;
		case Sztid_LocReport:
			CMCHKPK(cmPkSztLocReport, &param->u.sztLocReport, mBuf);
			break;
		case Sztid_OverloadStart:
			CMCHKPK(cmPkSztOverloadStart, &param->u.sztOverloadStart, mBuf);
			break;
		case Sztid_OverloadStop:
			CMCHKPK(cmPkSztOverloadStop, &param->u.sztOverloadStop, mBuf);
			break;
		case Sztid_eNBDirectInformTfr:
			CMCHKPK(cmPkSztENBDirectInformTfr, &param->u.sztENBDirectInformTfr, mBuf);
			break;
		case Sztid_MMEDirectInformTfr:
			CMCHKPK(cmPkSztMMEDirectInformTfr, &param->u.sztMMEDirectInformTfr, mBuf);
			break;
		case Sztid_eNBConfigTfr:
			CMCHKPK(cmPkSztENBConfigTfr, &param->u.sztENBConfigTfr, mBuf);
			break;
		case Sztid_MMEConfigTfr:
			CMCHKPK(cmPkSztMMEConfigTfr, &param->u.sztMMEConfigTfr, mBuf);
			break;
		case Sztid_PrivMsg:
			CMCHKPK(cmPkSztPrivMsg, &param->u.sztPrivMsg, mBuf);
			break;
		case Sztid_downlinkUEAssociatedLPPaTport:
			CMCHKPK(cmPkSztDlnkUEAssociatedLPPaTport, &param->u.sztDlnkUEAssociatedLPPaTport, mBuf);
			break;
		case Sztid_uplinkUEAssociatedLPPaTport:
			CMCHKPK(cmPkSztUlnkUEAssociatedLPPaTport, &param->u.sztUlnkUEAssociatedLPPaTport, mBuf);
			break;
		case Sztid_downlinkNonUEAssociatedLPPaTport:
			CMCHKPK(cmPkSztDlnkNonUEAssociatedLPPaTport, &param->u.sztDlnkNonUEAssociatedLPPaTport, mBuf);
			break;
		case Sztid_uplinkNonUEAssociatedLPPaTport:
			CMCHKPK(cmPkSztUlnkNonUEAssociatedLPPaTport, &param->u.sztUlnkNonUEAssociatedLPPaTport, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_InitiatingMsgCls */



/* 
* FUN : cmPkSztInitiatingMsg
*  DESC: Function to Pack SztInitiatingMsg structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztInitiatingMsg
(
SztInitiatingMsg *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztInitiatingMsg(param, mBuf)
SztInitiatingMsg *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztInitiatingMsg) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_InitiatingMsgCls(&param->value, param->procedureCode.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProcedureCode, &param->procedureCode, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztInitiatingMsg */



/* 
* FUN : cmPkSzt_SuccessfulOutcomeCls
*  DESC: Function to Pack Szt_SuccessfulOutcomeCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_SuccessfulOutcomeCls
(
Szt_SuccessfulOutcomeCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_SuccessfulOutcomeCls(param, val, mBuf)
Szt_SuccessfulOutcomeCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_SuccessfulOutcomeCls) 
	
	switch (val)
	{
		case Sztid_HovrPrep:
			CMCHKPK(cmPkSztHovrCmmd, &param->u.sztHovrCmmd, mBuf);
			break;
		case Sztid_HovrResourceAllocn:
			CMCHKPK(cmPkSztHovrRqstAckg, &param->u.sztHovrRqstAckg, mBuf);
			break;
		case Sztid_PathSwRqst:
			CMCHKPK(cmPkSztPathSwRqstAckg, &param->u.sztPathSwRqstAckg, mBuf);
			break;
		case Sztid_E_RABSetup:
			CMCHKPK(cmPkSztE_RABSetupResp, &param->u.sztE_RABSetupResp, mBuf);
			break;
		case Sztid_E_RABMdfy:
			CMCHKPK(cmPkSztE_RABMdfyResp, &param->u.sztE_RABMdfyResp, mBuf);
			break;
		case Sztid_E_RABRls:
			CMCHKPK(cmPkSztE_RABRlsResp, &param->u.sztE_RABRlsResp, mBuf);
			break;
		case Sztid_InitCntxtSetup:
			CMCHKPK(cmPkSztInitCntxtSetupResp, &param->u.sztInitCntxtSetupResp, mBuf);
			break;
		case Sztid_HovrCancel:
			CMCHKPK(cmPkSztHovrCancelAckg, &param->u.sztHovrCancelAckg, mBuf);
			break;
		case Sztid_Kill:
			CMCHKPK(cmPkSztKillResp, &param->u.sztKillResp, mBuf);
			break;
		case Sztid_Reset:
			CMCHKPK(cmPkSztResetAckg, &param->u.sztResetAckg, mBuf);
			break;
		case Sztid_S1Setup:
			CMCHKPK(cmPkSztS1SetupResp, &param->u.sztS1SetupResp, mBuf);
			break;
		case Sztid_UECntxtModification:
			CMCHKPK(cmPkSztUECntxtModificationResp, &param->u.sztUECntxtModificationResp, mBuf);
			break;
		case Sztid_UECntxtRls:
			CMCHKPK(cmPkSztUECntxtRlsComplete, &param->u.sztUECntxtRlsComplete, mBuf);
			break;
		case Sztid_ENBConfigUpd:
			CMCHKPK(cmPkSztENBConfigUpdAckg, &param->u.sztENBConfigUpdAckg, mBuf);
			break;
		case Sztid_MMEConfigUpd:
			CMCHKPK(cmPkSztMMEConfigUpdAckg, &param->u.sztMMEConfigUpdAckg, mBuf);
			break;
		case Sztid_WriteReplaceWarning:
			CMCHKPK(cmPkSztWriteReplaceWarningResp, &param->u.sztWriteReplaceWarningResp, mBuf);
			break;
		case Sztid_UERadioCapbltyMatch:
			CMCHKPK(cmPkSztUERadioCapbltyMatchResp, &param->u.sztUERadioCapbltyMatchResp, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_SuccessfulOutcomeCls */



/* 
* FUN : cmPkSztSuccessfulOutcome
*  DESC: Function to Pack SztSuccessfulOutcome structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztSuccessfulOutcome
(
SztSuccessfulOutcome *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztSuccessfulOutcome(param, mBuf)
SztSuccessfulOutcome *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztSuccessfulOutcome) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_SuccessfulOutcomeCls(&param->value, param->procedureCode.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProcedureCode, &param->procedureCode, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztSuccessfulOutcome */



/* 
* FUN : cmPkSzt_UnsuccessfulOutcomeCls
*  DESC: Function to Pack Szt_UnsuccessfulOutcomeCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSzt_UnsuccessfulOutcomeCls
(
Szt_UnsuccessfulOutcomeCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSzt_UnsuccessfulOutcomeCls(param, val, mBuf)
Szt_UnsuccessfulOutcomeCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSzt_UnsuccessfulOutcomeCls) 
	
	switch (val)
	{
		case Sztid_HovrPrep:
			CMCHKPK(cmPkSztHovrPrepFail, &param->u.sztHovrPrepFail, mBuf);
			break;
		case Sztid_HovrResourceAllocn:
			CMCHKPK(cmPkSztHovrFail, &param->u.sztHovrFail, mBuf);
			break;
		case Sztid_PathSwRqst:
			CMCHKPK(cmPkSztPathSwRqstFail, &param->u.sztPathSwRqstFail, mBuf);
			break;
		case Sztid_InitCntxtSetup:
			CMCHKPK(cmPkSztInitCntxtSetupFail, &param->u.sztInitCntxtSetupFail, mBuf);
			break;
		case Sztid_S1Setup:
			CMCHKPK(cmPkSztS1SetupFail, &param->u.sztS1SetupFail, mBuf);
			break;
		case Sztid_UECntxtModification:
			CMCHKPK(cmPkSztUECntxtModificationFail, &param->u.sztUECntxtModificationFail, mBuf);
			break;
		case Sztid_ENBConfigUpd:
			CMCHKPK(cmPkSztENBConfigUpdFail, &param->u.sztENBConfigUpdFail, mBuf);
			break;
		case Sztid_MMEConfigUpd:
			CMCHKPK(cmPkSztMMEConfigUpdFail, &param->u.sztMMEConfigUpdFail, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkSzt_UnsuccessfulOutcomeCls */



/* 
* FUN : cmPkSztUnsuccessfulOutcome
*  DESC: Function to Pack SztUnsuccessfulOutcome structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztUnsuccessfulOutcome
(
SztUnsuccessfulOutcome *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztUnsuccessfulOutcome(param, mBuf)
SztUnsuccessfulOutcome *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztUnsuccessfulOutcome) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkSzt_UnsuccessfulOutcomeCls(&param->value, param->procedureCode.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkSztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkSztProcedureCode, &param->procedureCode, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztUnsuccessfulOutcome */



/* 
* FUN : cmPkSztS1AP_PDU
*  DESC: Function to Pack SztS1AP_PDU structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkSztS1AP_PDU
(
SztS1AP_PDU *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkSztS1AP_PDU(param, mBuf)
SztS1AP_PDU *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkSztS1AP_PDU) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case S1AP_PDU_UNSUCCESSFULOUTCOME :
				CMCHKPK(cmPkSztUnsuccessfulOutcome, &param->val.unsuccessfulOutcome, mBuf); 
				break;
			case S1AP_PDU_SUCCESSFULOUTCOME :
				CMCHKPK(cmPkSztSuccessfulOutcome, &param->val.successfulOutcome, mBuf); 
				break;
			case S1AP_PDU_INITIATINGMSG :
				CMCHKPK(cmPkSztInitiatingMsg, &param->val.initiatingMsg, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkSztS1AP_PDU */
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
