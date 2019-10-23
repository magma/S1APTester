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
#include "gen.x"              /* general layer */
#include "ssi.x"              /* system services */
#include "cm_tkns.x"          /* */
#include "cm_mblk.x"
#include "cm_pasn.x"          /* PASN */
#include <czt_asn.h>
#include <czt_asn.x>
#include <czt_pk.x>

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/
#define cmPkCztCriticality cmPkTknU32
#define cmPkCztPresence cmPkTknU32
#define cmPkCztPrivIE_IDlocal cmPkTknU32 


/* 
* FUN : cmPkCztPrivIE_ID
*  DESC: Function to Pack CztPrivIE_ID structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztPrivIE_ID
(
CztPrivIE_ID *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztPrivIE_ID(param, mBuf)
CztPrivIE_ID *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztPrivIE_ID) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case PRIVIE_ID_GLOBAL :
				break;
			case PRIVIE_ID_LOCAL :
				CMCHKPK(cmPkCztPrivIE_IDlocal, &param->val.local, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztPrivIE_ID */

#define cmPkCztProcedureCode cmPkTknU32 
#define cmPkCztProtIE_ID cmPkTknU32 
#define cmPkCztTrgMsg cmPkTknU32
#define cmPkCztABSInformFDDabs_pattern_info cmPkTknStrBSXL 
#define cmPkCztABSInformFDDnumberOfCellSpecificAntennaPorts cmPkTknU32
#define cmPkCztABSInformFDDmeasurement_subset cmPkTknStrBSXL 


/* 
* FUN : cmPkCzt_ExtnABSInformFDD_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnABSInformFDD_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnABSInformFDD_ExtIEsCls
(
Czt_ExtnABSInformFDD_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnABSInformFDD_ExtIEsCls(param, val, mBuf)
Czt_ExtnABSInformFDD_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnABSInformFDD_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnABSInformFDD_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_ABSInformFDD_ExtIEs
*  DESC: Function to Pack CztProtExtnField_ABSInformFDD_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_ABSInformFDD_ExtIEs
(
CztProtExtnField_ABSInformFDD_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_ABSInformFDD_ExtIEs(param, mBuf)
CztProtExtnField_ABSInformFDD_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_ABSInformFDD_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnABSInformFDD_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_ABSInformFDD_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_ABSInformFDD_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_ABSInformFDD_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_ABSInformFDD_ExtIEs
(
CztProtExtnCont_ABSInformFDD_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_ABSInformFDD_ExtIEs(param, mBuf)
CztProtExtnCont_ABSInformFDD_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_ABSInformFDD_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_ABSInformFDD_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_ABSInformFDD_ExtIEs */



/* 
* FUN : cmPkCztABSInformFDD
*  DESC: Function to Pack CztABSInformFDD structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztABSInformFDD
(
CztABSInformFDD *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztABSInformFDD(param, mBuf)
CztABSInformFDD *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztABSInformFDD) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_ABSInformFDD_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztABSInformFDDmeasurement_subset, &param->measurement_subset, mBuf); 
		CMCHKPK(cmPkCztABSInformFDDnumberOfCellSpecificAntennaPorts, &param->numberOfCellSpecificAntennaPorts, mBuf); 
		CMCHKPK(cmPkCztABSInformFDDabs_pattern_info, &param->abs_pattern_info, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztABSInformFDD */

#define cmPkCztABSInformTDDabs_pattern_info cmPkTknStrBSXL 
#define cmPkCztABSInformTDDnumberOfCellSpecificAntennaPorts cmPkTknU32
#define cmPkCztABSInformTDDmeasurement_subset cmPkTknStrBSXL 


/* 
* FUN : cmPkCzt_ExtnABSInformTDD_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnABSInformTDD_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnABSInformTDD_ExtIEsCls
(
Czt_ExtnABSInformTDD_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnABSInformTDD_ExtIEsCls(param, val, mBuf)
Czt_ExtnABSInformTDD_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnABSInformTDD_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnABSInformTDD_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_ABSInformTDD_ExtIEs
*  DESC: Function to Pack CztProtExtnField_ABSInformTDD_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_ABSInformTDD_ExtIEs
(
CztProtExtnField_ABSInformTDD_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_ABSInformTDD_ExtIEs(param, mBuf)
CztProtExtnField_ABSInformTDD_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_ABSInformTDD_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnABSInformTDD_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_ABSInformTDD_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_ABSInformTDD_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_ABSInformTDD_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_ABSInformTDD_ExtIEs
(
CztProtExtnCont_ABSInformTDD_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_ABSInformTDD_ExtIEs(param, mBuf)
CztProtExtnCont_ABSInformTDD_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_ABSInformTDD_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_ABSInformTDD_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_ABSInformTDD_ExtIEs */



/* 
* FUN : cmPkCztABSInformTDD
*  DESC: Function to Pack CztABSInformTDD structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztABSInformTDD
(
CztABSInformTDD *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztABSInformTDD(param, mBuf)
CztABSInformTDD *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztABSInformTDD) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_ABSInformTDD_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztABSInformTDDmeasurement_subset, &param->measurement_subset, mBuf); 
		CMCHKPK(cmPkCztABSInformTDDnumberOfCellSpecificAntennaPorts, &param->numberOfCellSpecificAntennaPorts, mBuf); 
		CMCHKPK(cmPkCztABSInformTDDabs_pattern_info, &param->abs_pattern_info, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztABSInformTDD */



/* 
* FUN : cmPkCztABSInform
*  DESC: Function to Pack CztABSInform structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztABSInform
(
CztABSInform *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztABSInform(param, mBuf)
CztABSInform *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztABSInform) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case ABSINFORM_ABS_INACTIVE :
				break;
			case ABSINFORM_TDD :
				CMCHKPK(cmPkCztABSInformTDD, &param->val.tdd, mBuf); 
				break;
			case ABSINFORM_FDD :
				CMCHKPK(cmPkCztABSInformFDD, &param->val.fdd, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztABSInform */

#define cmPkCztDL_ABS_status cmPkTknU32 
#define cmPkCztUsableABSInformFDDusable_abs_pattern_info cmPkTknStrBSXL 


/* 
* FUN : cmPkCzt_ExtnUsableABSInformFDD_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnUsableABSInformFDD_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnUsableABSInformFDD_ExtIEsCls
(
Czt_ExtnUsableABSInformFDD_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnUsableABSInformFDD_ExtIEsCls(param, val, mBuf)
Czt_ExtnUsableABSInformFDD_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnUsableABSInformFDD_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnUsableABSInformFDD_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_UsableABSInformFDD_ExtIEs
*  DESC: Function to Pack CztProtExtnField_UsableABSInformFDD_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_UsableABSInformFDD_ExtIEs
(
CztProtExtnField_UsableABSInformFDD_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_UsableABSInformFDD_ExtIEs(param, mBuf)
CztProtExtnField_UsableABSInformFDD_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_UsableABSInformFDD_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnUsableABSInformFDD_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_UsableABSInformFDD_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_UsableABSInformFDD_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_UsableABSInformFDD_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_UsableABSInformFDD_ExtIEs
(
CztProtExtnCont_UsableABSInformFDD_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_UsableABSInformFDD_ExtIEs(param, mBuf)
CztProtExtnCont_UsableABSInformFDD_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_UsableABSInformFDD_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_UsableABSInformFDD_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_UsableABSInformFDD_ExtIEs */



/* 
* FUN : cmPkCztUsableABSInformFDD
*  DESC: Function to Pack CztUsableABSInformFDD structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztUsableABSInformFDD
(
CztUsableABSInformFDD *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztUsableABSInformFDD(param, mBuf)
CztUsableABSInformFDD *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztUsableABSInformFDD) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_UsableABSInformFDD_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztUsableABSInformFDDusable_abs_pattern_info, &param->usable_abs_pattern_info, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztUsableABSInformFDD */

#define cmPkCztUsableABSInformTDDusaable_abs_pattern_info cmPkTknStrBSXL 


/* 
* FUN : cmPkCzt_ExtnUsableABSInformTDD_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnUsableABSInformTDD_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnUsableABSInformTDD_ExtIEsCls
(
Czt_ExtnUsableABSInformTDD_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnUsableABSInformTDD_ExtIEsCls(param, val, mBuf)
Czt_ExtnUsableABSInformTDD_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnUsableABSInformTDD_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnUsableABSInformTDD_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_UsableABSInformTDD_ExtIEs
*  DESC: Function to Pack CztProtExtnField_UsableABSInformTDD_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_UsableABSInformTDD_ExtIEs
(
CztProtExtnField_UsableABSInformTDD_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_UsableABSInformTDD_ExtIEs(param, mBuf)
CztProtExtnField_UsableABSInformTDD_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_UsableABSInformTDD_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnUsableABSInformTDD_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_UsableABSInformTDD_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_UsableABSInformTDD_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_UsableABSInformTDD_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_UsableABSInformTDD_ExtIEs
(
CztProtExtnCont_UsableABSInformTDD_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_UsableABSInformTDD_ExtIEs(param, mBuf)
CztProtExtnCont_UsableABSInformTDD_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_UsableABSInformTDD_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_UsableABSInformTDD_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_UsableABSInformTDD_ExtIEs */



/* 
* FUN : cmPkCztUsableABSInformTDD
*  DESC: Function to Pack CztUsableABSInformTDD structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztUsableABSInformTDD
(
CztUsableABSInformTDD *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztUsableABSInformTDD(param, mBuf)
CztUsableABSInformTDD *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztUsableABSInformTDD) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_UsableABSInformTDD_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztUsableABSInformTDDusaable_abs_pattern_info, &param->usaable_abs_pattern_info, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztUsableABSInformTDD */



/* 
* FUN : cmPkCztUsableABSInform
*  DESC: Function to Pack CztUsableABSInform structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztUsableABSInform
(
CztUsableABSInform *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztUsableABSInform(param, mBuf)
CztUsableABSInform *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztUsableABSInform) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case USABLEABSINFORM_TDD :
				CMCHKPK(cmPkCztUsableABSInformTDD, &param->val.tdd, mBuf); 
				break;
			case USABLEABSINFORM_FDD :
				CMCHKPK(cmPkCztUsableABSInformFDD, &param->val.fdd, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztUsableABSInform */



/* 
* FUN : cmPkCzt_ExtnABS_Status_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnABS_Status_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnABS_Status_ExtIEsCls
(
Czt_ExtnABS_Status_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnABS_Status_ExtIEsCls(param, val, mBuf)
Czt_ExtnABS_Status_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnABS_Status_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnABS_Status_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_ABS_Status_ExtIEs
*  DESC: Function to Pack CztProtExtnField_ABS_Status_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_ABS_Status_ExtIEs
(
CztProtExtnField_ABS_Status_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_ABS_Status_ExtIEs(param, mBuf)
CztProtExtnField_ABS_Status_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_ABS_Status_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnABS_Status_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_ABS_Status_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_ABS_Status_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_ABS_Status_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_ABS_Status_ExtIEs
(
CztProtExtnCont_ABS_Status_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_ABS_Status_ExtIEs(param, mBuf)
CztProtExtnCont_ABS_Status_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_ABS_Status_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_ABS_Status_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_ABS_Status_ExtIEs */



/* 
* FUN : cmPkCztABS_Status
*  DESC: Function to Pack CztABS_Status structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztABS_Status
(
CztABS_Status *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztABS_Status(param, mBuf)
CztABS_Status *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztABS_Status) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_ABS_Status_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztUsableABSInform, &param->usableABSInform, mBuf); 
		CMCHKPK(cmPkCztDL_ABS_status, &param->dL_ABS_status, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztABS_Status */

#define cmPkCztAdditionalSpecialSubframePatterns cmPkTknU32
#define cmPkCztCyclicPrefixDL cmPkTknU32
#define cmPkCztCyclicPrefixUL cmPkTknU32


/* 
* FUN : cmPkCzt_ExtnAdditionalSpecialSubframe_Info_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnAdditionalSpecialSubframe_Info_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnAdditionalSpecialSubframe_Info_ExtIEsCls
(
Czt_ExtnAdditionalSpecialSubframe_Info_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnAdditionalSpecialSubframe_Info_ExtIEsCls(param, val, mBuf)
Czt_ExtnAdditionalSpecialSubframe_Info_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnAdditionalSpecialSubframe_Info_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnAdditionalSpecialSubframe_Info_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_AdditionalSpecialSubframe_Info_ExtIEs
*  DESC: Function to Pack CztProtExtnField_AdditionalSpecialSubframe_Info_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_AdditionalSpecialSubframe_Info_ExtIEs
(
CztProtExtnField_AdditionalSpecialSubframe_Info_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_AdditionalSpecialSubframe_Info_ExtIEs(param, mBuf)
CztProtExtnField_AdditionalSpecialSubframe_Info_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_AdditionalSpecialSubframe_Info_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnAdditionalSpecialSubframe_Info_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_AdditionalSpecialSubframe_Info_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEs
(
CztProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEs(param, mBuf)
CztProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_AdditionalSpecialSubframe_Info_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEs */



/* 
* FUN : cmPkCztAdditionalSpecialSubframe_Info
*  DESC: Function to Pack CztAdditionalSpecialSubframe_Info structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztAdditionalSpecialSubframe_Info
(
CztAdditionalSpecialSubframe_Info *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztAdditionalSpecialSubframe_Info(param, mBuf)
CztAdditionalSpecialSubframe_Info *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztAdditionalSpecialSubframe_Info) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztCyclicPrefixUL, &param->cyclicPrefixUL, mBuf); 
		CMCHKPK(cmPkCztCyclicPrefixDL, &param->cyclicPrefixDL, mBuf); 
		CMCHKPK(cmPkCztAdditionalSpecialSubframePatterns, &param->additionalspecialSubframePatterns, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztAdditionalSpecialSubframe_Info */

#define cmPkCztKey_eNodeB_Star cmPkTknStrBSXL 
#define cmPkCztNextHopChainingCount cmPkTknU32 


/* 
* FUN : cmPkCzt_ExtnAS_SecurInform_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnAS_SecurInform_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnAS_SecurInform_ExtIEsCls
(
Czt_ExtnAS_SecurInform_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnAS_SecurInform_ExtIEsCls(param, val, mBuf)
Czt_ExtnAS_SecurInform_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnAS_SecurInform_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnAS_SecurInform_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_AS_SecurInform_ExtIEs
*  DESC: Function to Pack CztProtExtnField_AS_SecurInform_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_AS_SecurInform_ExtIEs
(
CztProtExtnField_AS_SecurInform_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_AS_SecurInform_ExtIEs(param, mBuf)
CztProtExtnField_AS_SecurInform_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_AS_SecurInform_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnAS_SecurInform_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_AS_SecurInform_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_AS_SecurInform_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_AS_SecurInform_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_AS_SecurInform_ExtIEs
(
CztProtExtnCont_AS_SecurInform_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_AS_SecurInform_ExtIEs(param, mBuf)
CztProtExtnCont_AS_SecurInform_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_AS_SecurInform_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_AS_SecurInform_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_AS_SecurInform_ExtIEs */



/* 
* FUN : cmPkCztAS_SecurInform
*  DESC: Function to Pack CztAS_SecurInform structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztAS_SecurInform
(
CztAS_SecurInform *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztAS_SecurInform(param, mBuf)
CztAS_SecurInform *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztAS_SecurInform) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_AS_SecurInform_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztNextHopChainingCount, &param->nextHopChainingCount, mBuf); 
		CMCHKPK(cmPkCztKey_eNodeB_Star, &param->key_eNodeB_star, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztAS_SecurInform */

#define cmPkCztPriorityLvl cmPkTknU32 
#define cmPkCztPre_emptionCapblty cmPkTknU32
#define cmPkCztPre_emptionVulnerability cmPkTknU32


/* 
* FUN : cmPkCzt_ExtnAllocnAndRetentionPriority_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnAllocnAndRetentionPriority_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnAllocnAndRetentionPriority_ExtIEsCls
(
Czt_ExtnAllocnAndRetentionPriority_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnAllocnAndRetentionPriority_ExtIEsCls(param, val, mBuf)
Czt_ExtnAllocnAndRetentionPriority_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnAllocnAndRetentionPriority_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnAllocnAndRetentionPriority_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_AllocnAndRetentionPriority_ExtIEs
*  DESC: Function to Pack CztProtExtnField_AllocnAndRetentionPriority_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_AllocnAndRetentionPriority_ExtIEs
(
CztProtExtnField_AllocnAndRetentionPriority_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_AllocnAndRetentionPriority_ExtIEs(param, mBuf)
CztProtExtnField_AllocnAndRetentionPriority_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_AllocnAndRetentionPriority_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnAllocnAndRetentionPriority_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_AllocnAndRetentionPriority_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_AllocnAndRetentionPriority_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_AllocnAndRetentionPriority_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_AllocnAndRetentionPriority_ExtIEs
(
CztProtExtnCont_AllocnAndRetentionPriority_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_AllocnAndRetentionPriority_ExtIEs(param, mBuf)
CztProtExtnCont_AllocnAndRetentionPriority_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_AllocnAndRetentionPriority_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_AllocnAndRetentionPriority_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_AllocnAndRetentionPriority_ExtIEs */



/* 
* FUN : cmPkCztAllocnAndRetentionPriority
*  DESC: Function to Pack CztAllocnAndRetentionPriority structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztAllocnAndRetentionPriority
(
CztAllocnAndRetentionPriority *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztAllocnAndRetentionPriority(param, mBuf)
CztAllocnAndRetentionPriority *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztAllocnAndRetentionPriority) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_AllocnAndRetentionPriority_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztPre_emptionVulnerability, &param->pre_emptionVulnerability, mBuf); 
		CMCHKPK(cmPkCztPre_emptionCapblty, &param->pre_emptionCapblty, mBuf); 
		CMCHKPK(cmPkCztPriorityLvl, &param->priorityLvl, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztAllocnAndRetentionPriority */

#define cmPkCztPLMN_Identity cmPkTknStrOSXL 
#define cmPkCztEUTRANCellIdentifier cmPkTknBStr32 


/* 
* FUN : cmPkCzt_ExtnECGI_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnECGI_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnECGI_ExtIEsCls
(
Czt_ExtnECGI_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnECGI_ExtIEsCls(param, val, mBuf)
Czt_ExtnECGI_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnECGI_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnECGI_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_ECGI_ExtIEs
*  DESC: Function to Pack CztProtExtnField_ECGI_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_ECGI_ExtIEs
(
CztProtExtnField_ECGI_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_ECGI_ExtIEs(param, mBuf)
CztProtExtnField_ECGI_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_ECGI_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnECGI_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_ECGI_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_ECGI_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_ECGI_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_ECGI_ExtIEs
(
CztProtExtnCont_ECGI_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_ECGI_ExtIEs(param, mBuf)
CztProtExtnCont_ECGI_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_ECGI_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_ECGI_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_ECGI_ExtIEs */



/* 
* FUN : cmPkCztECGI
*  DESC: Function to Pack CztECGI structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztECGI
(
CztECGI *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztECGI(param, mBuf)
CztECGI *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztECGI) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_ECGI_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztEUTRANCellIdentifier, &param->eUTRANcellIdentifier, mBuf); 
		CMCHKPK(cmPkCztPLMN_Identity, &param->pLMN_Identity, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztECGI */



/* 
* FUN : cmPkCztCellIdLstforMDT
*  DESC: Function to Pack CztCellIdLstforMDT structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztCellIdLstforMDT
(
CztCellIdLstforMDT *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztCellIdLstforMDT(param, mBuf)
CztCellIdLstforMDT *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztCellIdLstforMDT) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztECGI, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztCellIdLstforMDT */



/* 
* FUN : cmPkCzt_ExtnCellBasedMDT_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnCellBasedMDT_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnCellBasedMDT_ExtIEsCls
(
Czt_ExtnCellBasedMDT_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnCellBasedMDT_ExtIEsCls(param, val, mBuf)
Czt_ExtnCellBasedMDT_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnCellBasedMDT_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnCellBasedMDT_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_CellBasedMDT_ExtIEs
*  DESC: Function to Pack CztProtExtnField_CellBasedMDT_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_CellBasedMDT_ExtIEs
(
CztProtExtnField_CellBasedMDT_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_CellBasedMDT_ExtIEs(param, mBuf)
CztProtExtnField_CellBasedMDT_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_CellBasedMDT_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnCellBasedMDT_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_CellBasedMDT_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_CellBasedMDT_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_CellBasedMDT_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_CellBasedMDT_ExtIEs
(
CztProtExtnCont_CellBasedMDT_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_CellBasedMDT_ExtIEs(param, mBuf)
CztProtExtnCont_CellBasedMDT_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_CellBasedMDT_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_CellBasedMDT_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_CellBasedMDT_ExtIEs */



/* 
* FUN : cmPkCztCellBasedMDT
*  DESC: Function to Pack CztCellBasedMDT structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztCellBasedMDT
(
CztCellBasedMDT *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztCellBasedMDT(param, mBuf)
CztCellBasedMDT *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztCellBasedMDT) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_CellBasedMDT_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztCellIdLstforMDT, &param->cellIdLstforMDT, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztCellBasedMDT */

#define cmPkCztTAC cmPkTknStr4 


/* 
* FUN : cmPkCztTALstforMDT
*  DESC: Function to Pack CztTALstforMDT structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztTALstforMDT
(
CztTALstforMDT *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztTALstforMDT(param, mBuf)
CztTALstforMDT *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztTALstforMDT) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztTAC, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztTALstforMDT */



/* 
* FUN : cmPkCzt_ExtnTABasedMDT_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnTABasedMDT_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnTABasedMDT_ExtIEsCls
(
Czt_ExtnTABasedMDT_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnTABasedMDT_ExtIEsCls(param, val, mBuf)
Czt_ExtnTABasedMDT_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnTABasedMDT_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnTABasedMDT_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_TABasedMDT_ExtIEs
*  DESC: Function to Pack CztProtExtnField_TABasedMDT_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_TABasedMDT_ExtIEs
(
CztProtExtnField_TABasedMDT_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_TABasedMDT_ExtIEs(param, mBuf)
CztProtExtnField_TABasedMDT_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_TABasedMDT_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnTABasedMDT_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_TABasedMDT_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_TABasedMDT_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_TABasedMDT_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_TABasedMDT_ExtIEs
(
CztProtExtnCont_TABasedMDT_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_TABasedMDT_ExtIEs(param, mBuf)
CztProtExtnCont_TABasedMDT_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_TABasedMDT_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_TABasedMDT_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_TABasedMDT_ExtIEs */



/* 
* FUN : cmPkCztTABasedMDT
*  DESC: Function to Pack CztTABasedMDT structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztTABasedMDT
(
CztTABasedMDT *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztTABasedMDT(param, mBuf)
CztTABasedMDT *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztTABasedMDT) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_TABasedMDT_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztTALstforMDT, &param->tALstforMDT, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztTABasedMDT */



/* 
* FUN : cmPkCzt_ExtnTAI_Item_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnTAI_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnTAI_Item_ExtIEsCls
(
Czt_ExtnTAI_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnTAI_Item_ExtIEsCls(param, val, mBuf)
Czt_ExtnTAI_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnTAI_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnTAI_Item_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_TAI_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnField_TAI_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_TAI_Item_ExtIEs
(
CztProtExtnField_TAI_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_TAI_Item_ExtIEs(param, mBuf)
CztProtExtnField_TAI_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_TAI_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnTAI_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_TAI_Item_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_TAI_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_TAI_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_TAI_Item_ExtIEs
(
CztProtExtnCont_TAI_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_TAI_Item_ExtIEs(param, mBuf)
CztProtExtnCont_TAI_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_TAI_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_TAI_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_TAI_Item_ExtIEs */



/* 
* FUN : cmPkCztTAI_Item
*  DESC: Function to Pack CztTAI_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztTAI_Item
(
CztTAI_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztTAI_Item(param, mBuf)
CztTAI_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztTAI_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_TAI_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztPLMN_Identity, &param->pLMN_Identity, mBuf); 
		CMCHKPK(cmPkCztTAC, &param->tAC, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztTAI_Item */



/* 
* FUN : cmPkCztTAILstforMDT
*  DESC: Function to Pack CztTAILstforMDT structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztTAILstforMDT
(
CztTAILstforMDT *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztTAILstforMDT(param, mBuf)
CztTAILstforMDT *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztTAILstforMDT) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztTAI_Item, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztTAILstforMDT */



/* 
* FUN : cmPkCzt_ExtnTAIBasedMDT_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnTAIBasedMDT_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnTAIBasedMDT_ExtIEsCls
(
Czt_ExtnTAIBasedMDT_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnTAIBasedMDT_ExtIEsCls(param, val, mBuf)
Czt_ExtnTAIBasedMDT_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnTAIBasedMDT_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnTAIBasedMDT_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_TAIBasedMDT_ExtIEs
*  DESC: Function to Pack CztProtExtnField_TAIBasedMDT_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_TAIBasedMDT_ExtIEs
(
CztProtExtnField_TAIBasedMDT_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_TAIBasedMDT_ExtIEs(param, mBuf)
CztProtExtnField_TAIBasedMDT_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_TAIBasedMDT_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnTAIBasedMDT_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_TAIBasedMDT_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_TAIBasedMDT_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_TAIBasedMDT_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_TAIBasedMDT_ExtIEs
(
CztProtExtnCont_TAIBasedMDT_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_TAIBasedMDT_ExtIEs(param, mBuf)
CztProtExtnCont_TAIBasedMDT_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_TAIBasedMDT_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_TAIBasedMDT_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_TAIBasedMDT_ExtIEs */



/* 
* FUN : cmPkCztTAIBasedMDT
*  DESC: Function to Pack CztTAIBasedMDT structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztTAIBasedMDT
(
CztTAIBasedMDT *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztTAIBasedMDT(param, mBuf)
CztTAIBasedMDT *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztTAIBasedMDT) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_TAIBasedMDT_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztTAILstforMDT, &param->tAILstforMDT, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztTAIBasedMDT */



/* 
* FUN : cmPkCztAreaScopeOfMDT
*  DESC: Function to Pack CztAreaScopeOfMDT structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztAreaScopeOfMDT
(
CztAreaScopeOfMDT *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztAreaScopeOfMDT(param, mBuf)
CztAreaScopeOfMDT *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztAreaScopeOfMDT) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case AREASCOPEOFMDT_TAIBASED :
				CMCHKPK(cmPkCztTAIBasedMDT, &param->val.tAIBased, mBuf); 
				break;
			case AREASCOPEOFMDT_PLMNWIDE :
				break;
			case AREASCOPEOFMDT_TABASED :
				CMCHKPK(cmPkCztTABasedMDT, &param->val.tABased, mBuf); 
				break;
			case AREASCOPEOFMDT_CELLBASED :
				CMCHKPK(cmPkCztCellBasedMDT, &param->val.cellBased, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztAreaScopeOfMDT */

#define cmPkCztBitRate cmPkTknStrOSXL 


/* 
* FUN : cmPkCztBroadcastPLMNs_Item
*  DESC: Function to Pack CztBroadcastPLMNs_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztBroadcastPLMNs_Item
(
CztBroadcastPLMNs_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztBroadcastPLMNs_Item(param, mBuf)
CztBroadcastPLMNs_Item *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztBroadcastPLMNs_Item) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztPLMN_Identity, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztBroadcastPLMNs_Item */

#define cmPkCztCapacityValue cmPkTknU32 
#define cmPkCztCellCapacityClassValue cmPkTknU32 
#define cmPkCztCauseRadioNw cmPkTknU32
#define cmPkCztCauseTport cmPkTknU32
#define cmPkCztCauseProt cmPkTknU32
#define cmPkCztCauseMisc cmPkTknU32


/* 
* FUN : cmPkCztCause
*  DESC: Function to Pack CztCause structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztCause
(
CztCause *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztCause(param, mBuf)
CztCause *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztCause) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case CZT_CAUSE_MISC :
				CMCHKPK(cmPkCztCauseMisc, &param->val.misc, mBuf); 
				break;
			case CZT_CAUSE_PROTOCOL :
				CMCHKPK(cmPkCztCauseProt, &param->val.protocol, mBuf); 
				break;
			case CAUSE_TRANSPORT :
				CMCHKPK(cmPkCztCauseTport, &param->val.transport, mBuf); 
				break;
			case CAUSE_RADIONW :
				CMCHKPK(cmPkCztCauseRadioNw, &param->val.radioNw, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztCause */

#define cmPkCztCell_Size cmPkTknU32


/* 
* FUN : cmPkCzt_ExtnCellTyp_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnCellTyp_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnCellTyp_ExtIEsCls
(
Czt_ExtnCellTyp_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnCellTyp_ExtIEsCls(param, val, mBuf)
Czt_ExtnCellTyp_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnCellTyp_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnCellTyp_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_CellTyp_ExtIEs
*  DESC: Function to Pack CztProtExtnField_CellTyp_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_CellTyp_ExtIEs
(
CztProtExtnField_CellTyp_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_CellTyp_ExtIEs(param, mBuf)
CztProtExtnField_CellTyp_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_CellTyp_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnCellTyp_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_CellTyp_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_CellTyp_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_CellTyp_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_CellTyp_ExtIEs
(
CztProtExtnCont_CellTyp_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_CellTyp_ExtIEs(param, mBuf)
CztProtExtnCont_CellTyp_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_CellTyp_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_CellTyp_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_CellTyp_ExtIEs */



/* 
* FUN : cmPkCztCellTyp
*  DESC: Function to Pack CztCellTyp structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztCellTyp
(
CztCellTyp *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztCellTyp(param, mBuf)
CztCellTyp *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztCellTyp) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_CellTyp_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztCell_Size, &param->cell_Size, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztCellTyp */



/* 
* FUN : cmPkCzt_ExtnCompositeAvailableCapacity_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnCompositeAvailableCapacity_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnCompositeAvailableCapacity_ExtIEsCls
(
Czt_ExtnCompositeAvailableCapacity_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnCompositeAvailableCapacity_ExtIEsCls(param, val, mBuf)
Czt_ExtnCompositeAvailableCapacity_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnCompositeAvailableCapacity_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnCompositeAvailableCapacity_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_CompositeAvailableCapacity_ExtIEs
*  DESC: Function to Pack CztProtExtnField_CompositeAvailableCapacity_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_CompositeAvailableCapacity_ExtIEs
(
CztProtExtnField_CompositeAvailableCapacity_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_CompositeAvailableCapacity_ExtIEs(param, mBuf)
CztProtExtnField_CompositeAvailableCapacity_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_CompositeAvailableCapacity_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnCompositeAvailableCapacity_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_CompositeAvailableCapacity_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_CompositeAvailableCapacity_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_CompositeAvailableCapacity_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_CompositeAvailableCapacity_ExtIEs
(
CztProtExtnCont_CompositeAvailableCapacity_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_CompositeAvailableCapacity_ExtIEs(param, mBuf)
CztProtExtnCont_CompositeAvailableCapacity_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_CompositeAvailableCapacity_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_CompositeAvailableCapacity_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_CompositeAvailableCapacity_ExtIEs */



/* 
* FUN : cmPkCztCompositeAvailableCapacity
*  DESC: Function to Pack CztCompositeAvailableCapacity structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztCompositeAvailableCapacity
(
CztCompositeAvailableCapacity *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztCompositeAvailableCapacity(param, mBuf)
CztCompositeAvailableCapacity *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztCompositeAvailableCapacity) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_CompositeAvailableCapacity_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztCapacityValue, &param->capacityValue, mBuf); 
		CMCHKPK(cmPkCztCellCapacityClassValue, &param->cellCapacityClassValue, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztCompositeAvailableCapacity */



/* 
* FUN : cmPkCzt_ExtnCompositeAvailableCapacityGroup_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnCompositeAvailableCapacityGroup_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnCompositeAvailableCapacityGroup_ExtIEsCls
(
Czt_ExtnCompositeAvailableCapacityGroup_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnCompositeAvailableCapacityGroup_ExtIEsCls(param, val, mBuf)
Czt_ExtnCompositeAvailableCapacityGroup_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnCompositeAvailableCapacityGroup_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnCompositeAvailableCapacityGroup_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_CompositeAvailableCapacityGroup_ExtIEs
*  DESC: Function to Pack CztProtExtnField_CompositeAvailableCapacityGroup_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_CompositeAvailableCapacityGroup_ExtIEs
(
CztProtExtnField_CompositeAvailableCapacityGroup_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_CompositeAvailableCapacityGroup_ExtIEs(param, mBuf)
CztProtExtnField_CompositeAvailableCapacityGroup_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_CompositeAvailableCapacityGroup_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnCompositeAvailableCapacityGroup_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_CompositeAvailableCapacityGroup_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_CompositeAvailableCapacityGroup_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_CompositeAvailableCapacityGroup_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_CompositeAvailableCapacityGroup_ExtIEs
(
CztProtExtnCont_CompositeAvailableCapacityGroup_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_CompositeAvailableCapacityGroup_ExtIEs(param, mBuf)
CztProtExtnCont_CompositeAvailableCapacityGroup_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_CompositeAvailableCapacityGroup_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_CompositeAvailableCapacityGroup_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_CompositeAvailableCapacityGroup_ExtIEs */



/* 
* FUN : cmPkCztCompositeAvailableCapacityGroup
*  DESC: Function to Pack CztCompositeAvailableCapacityGroup structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztCompositeAvailableCapacityGroup
(
CztCompositeAvailableCapacityGroup *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztCompositeAvailableCapacityGroup(param, mBuf)
CztCompositeAvailableCapacityGroup *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztCompositeAvailableCapacityGroup) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_CompositeAvailableCapacityGroup_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztCompositeAvailableCapacity, &param->uL_CompositeAvailableCapacity, mBuf); 
		CMCHKPK(cmPkCztCompositeAvailableCapacity, &param->dL_CompositeAvailableCapacity, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztCompositeAvailableCapacityGroup */

#define cmPkCztPDCP_SN cmPkTknU32 
#define cmPkCztHFN cmPkTknU32 


/* 
* FUN : cmPkCzt_ExtnCOUNTvalue_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnCOUNTvalue_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnCOUNTvalue_ExtIEsCls
(
Czt_ExtnCOUNTvalue_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnCOUNTvalue_ExtIEsCls(param, val, mBuf)
Czt_ExtnCOUNTvalue_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnCOUNTvalue_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnCOUNTvalue_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_COUNTvalue_ExtIEs
*  DESC: Function to Pack CztProtExtnField_COUNTvalue_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_COUNTvalue_ExtIEs
(
CztProtExtnField_COUNTvalue_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_COUNTvalue_ExtIEs(param, mBuf)
CztProtExtnField_COUNTvalue_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_COUNTvalue_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnCOUNTvalue_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_COUNTvalue_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_COUNTvalue_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_COUNTvalue_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_COUNTvalue_ExtIEs
(
CztProtExtnCont_COUNTvalue_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_COUNTvalue_ExtIEs(param, mBuf)
CztProtExtnCont_COUNTvalue_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_COUNTvalue_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_COUNTvalue_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_COUNTvalue_ExtIEs */



/* 
* FUN : cmPkCztCOUNTvalue
*  DESC: Function to Pack CztCOUNTvalue structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztCOUNTvalue
(
CztCOUNTvalue *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztCOUNTvalue(param, mBuf)
CztCOUNTvalue *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztCOUNTvalue) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_COUNTvalue_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztHFN, &param->hFN, mBuf); 
		CMCHKPK(cmPkCztPDCP_SN, &param->pDCP_SN, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztCOUNTvalue */

#define cmPkCztPDCP_SNExtended cmPkTknU32 
#define cmPkCztHFNMdfd cmPkTknU32 


/* 
* FUN : cmPkCzt_ExtnCOUNTValueExtended_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnCOUNTValueExtended_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnCOUNTValueExtended_ExtIEsCls
(
Czt_ExtnCOUNTValueExtended_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnCOUNTValueExtended_ExtIEsCls(param, val, mBuf)
Czt_ExtnCOUNTValueExtended_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnCOUNTValueExtended_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnCOUNTValueExtended_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_COUNTValueExtended_ExtIEs
*  DESC: Function to Pack CztProtExtnField_COUNTValueExtended_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_COUNTValueExtended_ExtIEs
(
CztProtExtnField_COUNTValueExtended_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_COUNTValueExtended_ExtIEs(param, mBuf)
CztProtExtnField_COUNTValueExtended_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_COUNTValueExtended_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnCOUNTValueExtended_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_COUNTValueExtended_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_COUNTValueExtended_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_COUNTValueExtended_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_COUNTValueExtended_ExtIEs
(
CztProtExtnCont_COUNTValueExtended_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_COUNTValueExtended_ExtIEs(param, mBuf)
CztProtExtnCont_COUNTValueExtended_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_COUNTValueExtended_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_COUNTValueExtended_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_COUNTValueExtended_ExtIEs */



/* 
* FUN : cmPkCztCOUNTValueExtended
*  DESC: Function to Pack CztCOUNTValueExtended structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztCOUNTValueExtended
(
CztCOUNTValueExtended *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztCOUNTValueExtended(param, mBuf)
CztCOUNTValueExtended *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztCOUNTValueExtended) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_COUNTValueExtended_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztHFNMdfd, &param->hFNMdfd, mBuf); 
		CMCHKPK(cmPkCztPDCP_SNExtended, &param->pDCP_SNExtended, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztCOUNTValueExtended */

#define cmPkCztTypOfErr cmPkTknU32


/* 
* FUN : cmPkCzt_ExtnCriticalityDiag_IE_Lst_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnCriticalityDiag_IE_Lst_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnCriticalityDiag_IE_Lst_ExtIEsCls
(
Czt_ExtnCriticalityDiag_IE_Lst_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnCriticalityDiag_IE_Lst_ExtIEsCls(param, val, mBuf)
Czt_ExtnCriticalityDiag_IE_Lst_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnCriticalityDiag_IE_Lst_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnCriticalityDiag_IE_Lst_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_CriticalityDiag_IE_Lst_ExtIEs
*  DESC: Function to Pack CztProtExtnField_CriticalityDiag_IE_Lst_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_CriticalityDiag_IE_Lst_ExtIEs
(
CztProtExtnField_CriticalityDiag_IE_Lst_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_CriticalityDiag_IE_Lst_ExtIEs(param, mBuf)
CztProtExtnField_CriticalityDiag_IE_Lst_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_CriticalityDiag_IE_Lst_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnCriticalityDiag_IE_Lst_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_CriticalityDiag_IE_Lst_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_CriticalityDiag_IE_Lst_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_CriticalityDiag_IE_Lst_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_CriticalityDiag_IE_Lst_ExtIEs
(
CztProtExtnCont_CriticalityDiag_IE_Lst_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_CriticalityDiag_IE_Lst_ExtIEs(param, mBuf)
CztProtExtnCont_CriticalityDiag_IE_Lst_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_CriticalityDiag_IE_Lst_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_CriticalityDiag_IE_Lst_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_CriticalityDiag_IE_Lst_ExtIEs */



/* 
* FUN : cmPkCztCriticalityDiag_IE_LstMember
*  DESC: Function to Pack CztCriticalityDiag_IE_LstMember structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztCriticalityDiag_IE_LstMember
(
CztCriticalityDiag_IE_LstMember *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztCriticalityDiag_IE_LstMember(param, mBuf)
CztCriticalityDiag_IE_LstMember *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztCriticalityDiag_IE_LstMember) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_CriticalityDiag_IE_Lst_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztTypOfErr, &param->typeOfErr, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->iE_ID, mBuf); 
		CMCHKPK(cmPkCztCriticality, &param->iECriticality, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztCriticalityDiag_IE_LstMember */



/* 
* FUN : cmPkCztCriticalityDiag_IE_Lst
*  DESC: Function to Pack CztCriticalityDiag_IE_Lst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztCriticalityDiag_IE_Lst
(
CztCriticalityDiag_IE_Lst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztCriticalityDiag_IE_Lst(param, mBuf)
CztCriticalityDiag_IE_Lst *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztCriticalityDiag_IE_Lst) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztCriticalityDiag_IE_LstMember, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztCriticalityDiag_IE_Lst */



/* 
* FUN : cmPkCzt_ExtnCriticalityDiag_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnCriticalityDiag_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnCriticalityDiag_ExtIEsCls
(
Czt_ExtnCriticalityDiag_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnCriticalityDiag_ExtIEsCls(param, val, mBuf)
Czt_ExtnCriticalityDiag_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnCriticalityDiag_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnCriticalityDiag_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_CriticalityDiag_ExtIEs
*  DESC: Function to Pack CztProtExtnField_CriticalityDiag_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_CriticalityDiag_ExtIEs
(
CztProtExtnField_CriticalityDiag_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_CriticalityDiag_ExtIEs(param, mBuf)
CztProtExtnField_CriticalityDiag_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_CriticalityDiag_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnCriticalityDiag_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_CriticalityDiag_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_CriticalityDiag_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_CriticalityDiag_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_CriticalityDiag_ExtIEs
(
CztProtExtnCont_CriticalityDiag_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_CriticalityDiag_ExtIEs(param, mBuf)
CztProtExtnCont_CriticalityDiag_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_CriticalityDiag_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_CriticalityDiag_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_CriticalityDiag_ExtIEs */



/* 
* FUN : cmPkCztCriticalityDiag
*  DESC: Function to Pack CztCriticalityDiag structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztCriticalityDiag
(
CztCriticalityDiag *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztCriticalityDiag(param, mBuf)
CztCriticalityDiag *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztCriticalityDiag) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_CriticalityDiag_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztCriticalityDiag_IE_Lst, &param->iEsCriticalityDiag, mBuf); 
		CMCHKPK(cmPkCztCriticality, &param->procedureCriticality, mBuf); 
		CMCHKPK(cmPkCztTrgMsg, &param->triggeringMsg, mBuf); 
		CMCHKPK(cmPkCztProcedureCode, &param->procedureCode, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztCriticalityDiag */

#define cmPkCztCRNTI cmPkTknBStr32 
#define cmPkCztCSGMembershipStatus cmPkTknU32
#define cmPkCztCSG_Id cmPkTknBStr32 
#define cmPkCztDeactivationInd cmPkTknU32
#define cmPkCztDL_Fwding cmPkTknU32
#define cmPkCztDL_GBR_PRB_usage cmPkTknU32 
#define cmPkCztDL_non_GBR_PRB_usage cmPkTknU32 
#define cmPkCztDL_Total_PRB_usage cmPkTknU32 
#define cmPkCztEARFCN cmPkTknU32 
#define cmPkCztEARFCNExtn cmPkTknU32 
#define cmPkCztTransmission_Bandwidth cmPkTknU32


/* 
* FUN : cmPkCzt_ExtnFDD_Info_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnFDD_Info_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnFDD_Info_ExtIEsCls
(
Czt_ExtnFDD_Info_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnFDD_Info_ExtIEsCls(param, val, mBuf)
Czt_ExtnFDD_Info_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnFDD_Info_ExtIEsCls) 
	
	switch (val)
	{
		case Cztid_UL_EARFCNExtn:
			CMCHKPK(cmPkCztEARFCNExtn, &param->u.cztid_UL_EARFCNExtn, mBuf);
			break;
		case Cztid_DL_EARFCNExtn:
			CMCHKPK(cmPkCztEARFCNExtn, &param->u.cztid_DL_EARFCNExtn, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ExtnFDD_Info_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_FDD_Info_ExtIEs
*  DESC: Function to Pack CztProtExtnField_FDD_Info_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_FDD_Info_ExtIEs
(
CztProtExtnField_FDD_Info_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_FDD_Info_ExtIEs(param, mBuf)
CztProtExtnField_FDD_Info_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_FDD_Info_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnFDD_Info_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_FDD_Info_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_FDD_Info_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_FDD_Info_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_FDD_Info_ExtIEs
(
CztProtExtnCont_FDD_Info_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_FDD_Info_ExtIEs(param, mBuf)
CztProtExtnCont_FDD_Info_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_FDD_Info_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_FDD_Info_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_FDD_Info_ExtIEs */



/* 
* FUN : cmPkCztFDD_Info
*  DESC: Function to Pack CztFDD_Info structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztFDD_Info
(
CztFDD_Info *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztFDD_Info(param, mBuf)
CztFDD_Info *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztFDD_Info) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_FDD_Info_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztTransmission_Bandwidth, &param->dL_Transmission_Bandwidth, mBuf); 
		CMCHKPK(cmPkCztTransmission_Bandwidth, &param->uL_Transmission_Bandwidth, mBuf); 
		CMCHKPK(cmPkCztEARFCN, &param->dL_EARFCN, mBuf); 
		CMCHKPK(cmPkCztEARFCN, &param->uL_EARFCN, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztFDD_Info */

#define cmPkCztSubframeAssignment cmPkTknU32
#define cmPkCztSpecialSubframePatterns cmPkTknU32


/* 
* FUN : cmPkCzt_ExtnSpecialSubframe_Info_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnSpecialSubframe_Info_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnSpecialSubframe_Info_ExtIEsCls
(
Czt_ExtnSpecialSubframe_Info_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnSpecialSubframe_Info_ExtIEsCls(param, val, mBuf)
Czt_ExtnSpecialSubframe_Info_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnSpecialSubframe_Info_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnSpecialSubframe_Info_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_SpecialSubframe_Info_ExtIEs
*  DESC: Function to Pack CztProtExtnField_SpecialSubframe_Info_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_SpecialSubframe_Info_ExtIEs
(
CztProtExtnField_SpecialSubframe_Info_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_SpecialSubframe_Info_ExtIEs(param, mBuf)
CztProtExtnField_SpecialSubframe_Info_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_SpecialSubframe_Info_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnSpecialSubframe_Info_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_SpecialSubframe_Info_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_SpecialSubframe_Info_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_SpecialSubframe_Info_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_SpecialSubframe_Info_ExtIEs
(
CztProtExtnCont_SpecialSubframe_Info_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_SpecialSubframe_Info_ExtIEs(param, mBuf)
CztProtExtnCont_SpecialSubframe_Info_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_SpecialSubframe_Info_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_SpecialSubframe_Info_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_SpecialSubframe_Info_ExtIEs */



/* 
* FUN : cmPkCztSpecialSubframe_Info
*  DESC: Function to Pack CztSpecialSubframe_Info structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztSpecialSubframe_Info
(
CztSpecialSubframe_Info *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztSpecialSubframe_Info(param, mBuf)
CztSpecialSubframe_Info *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztSpecialSubframe_Info) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_SpecialSubframe_Info_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztCyclicPrefixUL, &param->cyclicPrefixUL, mBuf); 
		CMCHKPK(cmPkCztCyclicPrefixDL, &param->cyclicPrefixDL, mBuf); 
		CMCHKPK(cmPkCztSpecialSubframePatterns, &param->specialSubframePatterns, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztSpecialSubframe_Info */



/* 
* FUN : cmPkCzt_ExtnTDD_Info_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnTDD_Info_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnTDD_Info_ExtIEsCls
(
Czt_ExtnTDD_Info_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnTDD_Info_ExtIEsCls(param, val, mBuf)
Czt_ExtnTDD_Info_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnTDD_Info_ExtIEsCls) 
	
	switch (val)
	{
		case Cztid_AdditionalSpecialSubframe_Info:
			CMCHKPK(cmPkCztAdditionalSpecialSubframe_Info, &param->u.cztAdditionalSpecialSubframe_Info, mBuf);
			break;
		case Cztid_eARFCNExtn:
			CMCHKPK(cmPkCztEARFCNExtn, &param->u.cztEARFCNExtn, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ExtnTDD_Info_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_TDD_Info_ExtIEs
*  DESC: Function to Pack CztProtExtnField_TDD_Info_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_TDD_Info_ExtIEs
(
CztProtExtnField_TDD_Info_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_TDD_Info_ExtIEs(param, mBuf)
CztProtExtnField_TDD_Info_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_TDD_Info_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnTDD_Info_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_TDD_Info_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_TDD_Info_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_TDD_Info_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_TDD_Info_ExtIEs
(
CztProtExtnCont_TDD_Info_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_TDD_Info_ExtIEs(param, mBuf)
CztProtExtnCont_TDD_Info_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_TDD_Info_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_TDD_Info_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_TDD_Info_ExtIEs */



/* 
* FUN : cmPkCztTDD_Info
*  DESC: Function to Pack CztTDD_Info structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztTDD_Info
(
CztTDD_Info *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztTDD_Info(param, mBuf)
CztTDD_Info *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztTDD_Info) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_TDD_Info_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztSpecialSubframe_Info, &param->specialSubframe_Info, mBuf); 
		CMCHKPK(cmPkCztSubframeAssignment, &param->subframeAssignment, mBuf); 
		CMCHKPK(cmPkCztTransmission_Bandwidth, &param->transmission_Bandwidth, mBuf); 
		CMCHKPK(cmPkCztEARFCN, &param->eARFCN, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztTDD_Info */



/* 
* FUN : cmPkCztEUTRA_Mode_Info
*  DESC: Function to Pack CztEUTRA_Mode_Info structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztEUTRA_Mode_Info
(
CztEUTRA_Mode_Info *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztEUTRA_Mode_Info(param, mBuf)
CztEUTRA_Mode_Info *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztEUTRA_Mode_Info) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case EUTRA_MODE_INFO_TDD :
				CMCHKPK(cmPkCztTDD_Info, &param->val.tDD, mBuf); 
				break;
			case EUTRA_MODE_INFO_FDD :
				CMCHKPK(cmPkCztFDD_Info, &param->val.fDD, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztEUTRA_Mode_Info */

#define cmPkCztENB_IDmacro_eNB_ID cmPkTknBStr32 
#define cmPkCztENB_IDhome_eNB_ID cmPkTknBStr32 


/* 
* FUN : cmPkCztENB_ID
*  DESC: Function to Pack CztENB_ID structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztENB_ID
(
CztENB_ID *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztENB_ID(param, mBuf)
CztENB_ID *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztENB_ID) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case ENB_ID_HOME_ENB_ID :
				CMCHKPK(cmPkCztENB_IDhome_eNB_ID, &param->val.home_eNB_ID, mBuf); 
				break;
			case ENB_ID_MACRO_ENB_ID :
				CMCHKPK(cmPkCztENB_IDmacro_eNB_ID, &param->val.macro_eNB_ID, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztENB_ID */

#define cmPkCztEncryptionAlgorithms cmPkTknBStr32 


/* 
* FUN : cmPkCztEPLMNs
*  DESC: Function to Pack CztEPLMNs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztEPLMNs
(
CztEPLMNs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztEPLMNs(param, mBuf)
CztEPLMNs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztEPLMNs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztPLMN_Identity, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztEPLMNs */

#define cmPkCztE_RAB_ID cmPkTknU32 
#define cmPkCztQCI cmPkTknU32 


/* 
* FUN : cmPkCzt_ExtnGBR_QosInform_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnGBR_QosInform_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnGBR_QosInform_ExtIEsCls
(
Czt_ExtnGBR_QosInform_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnGBR_QosInform_ExtIEsCls(param, val, mBuf)
Czt_ExtnGBR_QosInform_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnGBR_QosInform_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnGBR_QosInform_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_GBR_QosInform_ExtIEs
*  DESC: Function to Pack CztProtExtnField_GBR_QosInform_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_GBR_QosInform_ExtIEs
(
CztProtExtnField_GBR_QosInform_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_GBR_QosInform_ExtIEs(param, mBuf)
CztProtExtnField_GBR_QosInform_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_GBR_QosInform_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnGBR_QosInform_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_GBR_QosInform_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_GBR_QosInform_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_GBR_QosInform_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_GBR_QosInform_ExtIEs
(
CztProtExtnCont_GBR_QosInform_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_GBR_QosInform_ExtIEs(param, mBuf)
CztProtExtnCont_GBR_QosInform_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_GBR_QosInform_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_GBR_QosInform_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_GBR_QosInform_ExtIEs */



/* 
* FUN : cmPkCztGBR_QosInform
*  DESC: Function to Pack CztGBR_QosInform structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztGBR_QosInform
(
CztGBR_QosInform *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztGBR_QosInform(param, mBuf)
CztGBR_QosInform *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztGBR_QosInform) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_GBR_QosInform_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztBitRate, &param->e_RAB_GuaranteedBitrateUL, mBuf); 
		CMCHKPK(cmPkCztBitRate, &param->e_RAB_GuaranteedBitrateDL, mBuf); 
		CMCHKPK(cmPkCztBitRate, &param->e_RAB_MaxBitrateUL, mBuf); 
		CMCHKPK(cmPkCztBitRate, &param->e_RAB_MaxBitrateDL, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztGBR_QosInform */



/* 
* FUN : cmPkCzt_ExtnE_RAB_Lvl_QoS_Params_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnE_RAB_Lvl_QoS_Params_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnE_RAB_Lvl_QoS_Params_ExtIEsCls
(
Czt_ExtnE_RAB_Lvl_QoS_Params_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnE_RAB_Lvl_QoS_Params_ExtIEsCls(param, val, mBuf)
Czt_ExtnE_RAB_Lvl_QoS_Params_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnE_RAB_Lvl_QoS_Params_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnE_RAB_Lvl_QoS_Params_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEs
*  DESC: Function to Pack CztProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEs
(
CztProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEs(param, mBuf)
CztProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnE_RAB_Lvl_QoS_Params_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEs
(
CztProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEs(param, mBuf)
CztProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEs */



/* 
* FUN : cmPkCztE_RAB_Lvl_QoS_Params
*  DESC: Function to Pack CztE_RAB_Lvl_QoS_Params structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztE_RAB_Lvl_QoS_Params
(
CztE_RAB_Lvl_QoS_Params *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztE_RAB_Lvl_QoS_Params(param, mBuf)
CztE_RAB_Lvl_QoS_Params *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztE_RAB_Lvl_QoS_Params) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztGBR_QosInform, &param->gbrQosInform, mBuf); 
		CMCHKPK(cmPkCztAllocnAndRetentionPriority, &param->allocationAndRetentionPriority, mBuf); 
		CMCHKPK(cmPkCztQCI, &param->qCI, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztE_RAB_Lvl_QoS_Params */



/* 
* FUN : cmPkCzt_ExtnE_RAB_Item_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnE_RAB_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnE_RAB_Item_ExtIEsCls
(
Czt_ExtnE_RAB_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnE_RAB_Item_ExtIEsCls(param, val, mBuf)
Czt_ExtnE_RAB_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnE_RAB_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnE_RAB_Item_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_E_RAB_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnField_E_RAB_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_E_RAB_Item_ExtIEs
(
CztProtExtnField_E_RAB_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_E_RAB_Item_ExtIEs(param, mBuf)
CztProtExtnField_E_RAB_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_E_RAB_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnE_RAB_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_E_RAB_Item_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_E_RAB_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_E_RAB_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_E_RAB_Item_ExtIEs
(
CztProtExtnCont_E_RAB_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_E_RAB_Item_ExtIEs(param, mBuf)
CztProtExtnCont_E_RAB_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_E_RAB_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_E_RAB_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_E_RAB_Item_ExtIEs */



/* 
* FUN : cmPkCztE_RAB_Item
*  DESC: Function to Pack CztE_RAB_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztE_RAB_Item
(
CztE_RAB_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztE_RAB_Item(param, mBuf)
CztE_RAB_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztE_RAB_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_E_RAB_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztCause, &param->cause, mBuf); 
		CMCHKPK(cmPkCztE_RAB_ID, &param->e_RAB_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztE_RAB_Item */



/* 
* FUN : cmPkCzt_ValueE_RAB_ItemIEsCls
*  DESC: Function to Pack Czt_ValueE_RAB_ItemIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueE_RAB_ItemIEsCls
(
Czt_ValueE_RAB_ItemIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueE_RAB_ItemIEsCls(param, val, mBuf)
Czt_ValueE_RAB_ItemIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueE_RAB_ItemIEsCls) 
	
	switch (val)
	{
		case Cztid_E_RAB_Item:
			CMCHKPK(cmPkCztE_RAB_Item, &param->u.cztE_RAB_Item, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueE_RAB_ItemIEsCls */



/* 
* FUN : cmPkCztProtIE_Field_E_RAB_ItemIEs
*  DESC: Function to Pack CztProtIE_Field_E_RAB_ItemIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_E_RAB_ItemIEs
(
CztProtIE_Field_E_RAB_ItemIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_E_RAB_ItemIEs(param, mBuf)
CztProtIE_Field_E_RAB_ItemIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_E_RAB_ItemIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueE_RAB_ItemIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_E_RAB_ItemIEs */

/* Element ------------- ProtocolIE-Single-Container ------------ */
#define cmPkCztProtIE_Single_Cont_E_RAB_ItemIEs cmPkCztProtIE_Field_E_RAB_ItemIEs


/* 
* FUN : cmPkCztE_RAB_Lst
*  DESC: Function to Pack CztE_RAB_Lst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztE_RAB_Lst
(
CztE_RAB_Lst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztE_RAB_Lst(param, mBuf)
CztE_RAB_Lst *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztE_RAB_Lst) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Single_Cont_E_RAB_ItemIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztE_RAB_Lst */

#define cmPkCztEUTRANTraceID cmPkTknStrOSXL 
#define cmPkCztEventTyp cmPkTknU32
#define cmPkCztForbiddenInterRATs cmPkTknU32


/* 
* FUN : cmPkCztForbiddenTACs
*  DESC: Function to Pack CztForbiddenTACs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztForbiddenTACs
(
CztForbiddenTACs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztForbiddenTACs(param, mBuf)
CztForbiddenTACs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztForbiddenTACs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztTAC, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztForbiddenTACs */



/* 
* FUN : cmPkCzt_ExtnForbiddenTAs_Item_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnForbiddenTAs_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnForbiddenTAs_Item_ExtIEsCls
(
Czt_ExtnForbiddenTAs_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnForbiddenTAs_Item_ExtIEsCls(param, val, mBuf)
Czt_ExtnForbiddenTAs_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnForbiddenTAs_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnForbiddenTAs_Item_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_ForbiddenTAs_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnField_ForbiddenTAs_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_ForbiddenTAs_Item_ExtIEs
(
CztProtExtnField_ForbiddenTAs_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_ForbiddenTAs_Item_ExtIEs(param, mBuf)
CztProtExtnField_ForbiddenTAs_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_ForbiddenTAs_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnForbiddenTAs_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_ForbiddenTAs_Item_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_ForbiddenTAs_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_ForbiddenTAs_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_ForbiddenTAs_Item_ExtIEs
(
CztProtExtnCont_ForbiddenTAs_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_ForbiddenTAs_Item_ExtIEs(param, mBuf)
CztProtExtnCont_ForbiddenTAs_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_ForbiddenTAs_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_ForbiddenTAs_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_ForbiddenTAs_Item_ExtIEs */



/* 
* FUN : cmPkCztForbiddenTAs_Item
*  DESC: Function to Pack CztForbiddenTAs_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztForbiddenTAs_Item
(
CztForbiddenTAs_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztForbiddenTAs_Item(param, mBuf)
CztForbiddenTAs_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztForbiddenTAs_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_ForbiddenTAs_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztForbiddenTACs, &param->forbiddenTACs, mBuf); 
		CMCHKPK(cmPkCztPLMN_Identity, &param->pLMN_Identity, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztForbiddenTAs_Item */



/* 
* FUN : cmPkCztForbiddenTAs
*  DESC: Function to Pack CztForbiddenTAs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztForbiddenTAs
(
CztForbiddenTAs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztForbiddenTAs(param, mBuf)
CztForbiddenTAs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztForbiddenTAs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztForbiddenTAs_Item, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztForbiddenTAs */

#define cmPkCztLAC cmPkTknStr4 


/* 
* FUN : cmPkCztForbiddenLACs
*  DESC: Function to Pack CztForbiddenLACs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztForbiddenLACs
(
CztForbiddenLACs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztForbiddenLACs(param, mBuf)
CztForbiddenLACs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztForbiddenLACs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztLAC, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztForbiddenLACs */



/* 
* FUN : cmPkCzt_ExtnForbiddenLAs_Item_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnForbiddenLAs_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnForbiddenLAs_Item_ExtIEsCls
(
Czt_ExtnForbiddenLAs_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnForbiddenLAs_Item_ExtIEsCls(param, val, mBuf)
Czt_ExtnForbiddenLAs_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnForbiddenLAs_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnForbiddenLAs_Item_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_ForbiddenLAs_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnField_ForbiddenLAs_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_ForbiddenLAs_Item_ExtIEs
(
CztProtExtnField_ForbiddenLAs_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_ForbiddenLAs_Item_ExtIEs(param, mBuf)
CztProtExtnField_ForbiddenLAs_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_ForbiddenLAs_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnForbiddenLAs_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_ForbiddenLAs_Item_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_ForbiddenLAs_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_ForbiddenLAs_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_ForbiddenLAs_Item_ExtIEs
(
CztProtExtnCont_ForbiddenLAs_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_ForbiddenLAs_Item_ExtIEs(param, mBuf)
CztProtExtnCont_ForbiddenLAs_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_ForbiddenLAs_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_ForbiddenLAs_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_ForbiddenLAs_Item_ExtIEs */



/* 
* FUN : cmPkCztForbiddenLAs_Item
*  DESC: Function to Pack CztForbiddenLAs_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztForbiddenLAs_Item
(
CztForbiddenLAs_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztForbiddenLAs_Item(param, mBuf)
CztForbiddenLAs_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztForbiddenLAs_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_ForbiddenLAs_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztForbiddenLACs, &param->forbiddenLACs, mBuf); 
		CMCHKPK(cmPkCztPLMN_Identity, &param->pLMN_Identity, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztForbiddenLAs_Item */



/* 
* FUN : cmPkCztForbiddenLAs
*  DESC: Function to Pack CztForbiddenLAs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztForbiddenLAs
(
CztForbiddenLAs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztForbiddenLAs(param, mBuf)
CztForbiddenLAs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztForbiddenLAs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztForbiddenLAs_Item, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztForbiddenLAs */

#define cmPkCztFourframes cmPkTknBStr32 
#define cmPkCztFreqBandIndicator cmPkTknU32 


/* 
* FUN : cmPkCzt_ExtnGlobalENB_ID_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnGlobalENB_ID_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnGlobalENB_ID_ExtIEsCls
(
Czt_ExtnGlobalENB_ID_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnGlobalENB_ID_ExtIEsCls(param, val, mBuf)
Czt_ExtnGlobalENB_ID_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnGlobalENB_ID_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnGlobalENB_ID_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_GlobalENB_ID_ExtIEs
*  DESC: Function to Pack CztProtExtnField_GlobalENB_ID_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_GlobalENB_ID_ExtIEs
(
CztProtExtnField_GlobalENB_ID_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_GlobalENB_ID_ExtIEs(param, mBuf)
CztProtExtnField_GlobalENB_ID_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_GlobalENB_ID_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnGlobalENB_ID_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_GlobalENB_ID_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_GlobalENB_ID_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_GlobalENB_ID_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_GlobalENB_ID_ExtIEs
(
CztProtExtnCont_GlobalENB_ID_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_GlobalENB_ID_ExtIEs(param, mBuf)
CztProtExtnCont_GlobalENB_ID_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_GlobalENB_ID_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_GlobalENB_ID_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_GlobalENB_ID_ExtIEs */



/* 
* FUN : cmPkCztGlobalENB_ID
*  DESC: Function to Pack CztGlobalENB_ID structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztGlobalENB_ID
(
CztGlobalENB_ID *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztGlobalENB_ID(param, mBuf)
CztGlobalENB_ID *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztGlobalENB_ID) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_GlobalENB_ID_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztENB_ID, &param->eNB_ID, mBuf); 
		CMCHKPK(cmPkCztPLMN_Identity, &param->pLMN_Identity, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztGlobalENB_ID */

#define cmPkCztTportLyrAddr cmPkTknStrBSXL 
#define cmPkCztGTP_TEI cmPkTknStrOSXL 


/* 
* FUN : cmPkCzt_ExtnGTPtunnelEndpoint_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnGTPtunnelEndpoint_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnGTPtunnelEndpoint_ExtIEsCls
(
Czt_ExtnGTPtunnelEndpoint_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnGTPtunnelEndpoint_ExtIEsCls(param, val, mBuf)
Czt_ExtnGTPtunnelEndpoint_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnGTPtunnelEndpoint_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnGTPtunnelEndpoint_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_GTPtunnelEndpoint_ExtIEs
*  DESC: Function to Pack CztProtExtnField_GTPtunnelEndpoint_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_GTPtunnelEndpoint_ExtIEs
(
CztProtExtnField_GTPtunnelEndpoint_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_GTPtunnelEndpoint_ExtIEs(param, mBuf)
CztProtExtnField_GTPtunnelEndpoint_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_GTPtunnelEndpoint_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnGTPtunnelEndpoint_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_GTPtunnelEndpoint_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_GTPtunnelEndpoint_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_GTPtunnelEndpoint_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_GTPtunnelEndpoint_ExtIEs
(
CztProtExtnCont_GTPtunnelEndpoint_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_GTPtunnelEndpoint_ExtIEs(param, mBuf)
CztProtExtnCont_GTPtunnelEndpoint_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_GTPtunnelEndpoint_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_GTPtunnelEndpoint_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_GTPtunnelEndpoint_ExtIEs */



/* 
* FUN : cmPkCztGTPtunnelEndpoint
*  DESC: Function to Pack CztGTPtunnelEndpoint structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztGTPtunnelEndpoint
(
CztGTPtunnelEndpoint *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztGTPtunnelEndpoint(param, mBuf)
CztGTPtunnelEndpoint *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztGTPtunnelEndpoint) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_GTPtunnelEndpoint_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztGTP_TEI, &param->gTP_TEID, mBuf); 
		CMCHKPK(cmPkCztTportLyrAddr, &param->transportLyrAddr, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztGTPtunnelEndpoint */

#define cmPkCztMME_Group_ID cmPkTknStr4 


/* 
* FUN : cmPkCzt_ExtnGU_Group_ID_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnGU_Group_ID_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnGU_Group_ID_ExtIEsCls
(
Czt_ExtnGU_Group_ID_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnGU_Group_ID_ExtIEsCls(param, val, mBuf)
Czt_ExtnGU_Group_ID_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnGU_Group_ID_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnGU_Group_ID_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_GU_Group_ID_ExtIEs
*  DESC: Function to Pack CztProtExtnField_GU_Group_ID_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_GU_Group_ID_ExtIEs
(
CztProtExtnField_GU_Group_ID_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_GU_Group_ID_ExtIEs(param, mBuf)
CztProtExtnField_GU_Group_ID_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_GU_Group_ID_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnGU_Group_ID_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_GU_Group_ID_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_GU_Group_ID_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_GU_Group_ID_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_GU_Group_ID_ExtIEs
(
CztProtExtnCont_GU_Group_ID_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_GU_Group_ID_ExtIEs(param, mBuf)
CztProtExtnCont_GU_Group_ID_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_GU_Group_ID_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_GU_Group_ID_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_GU_Group_ID_ExtIEs */



/* 
* FUN : cmPkCztGU_Group_ID
*  DESC: Function to Pack CztGU_Group_ID structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztGU_Group_ID
(
CztGU_Group_ID *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztGU_Group_ID(param, mBuf)
CztGU_Group_ID *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztGU_Group_ID) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_GU_Group_ID_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztMME_Group_ID, &param->mME_Group_ID, mBuf); 
		CMCHKPK(cmPkCztPLMN_Identity, &param->pLMN_Identity, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztGU_Group_ID */



/* 
* FUN : cmPkCztGUGroupIDLst
*  DESC: Function to Pack CztGUGroupIDLst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztGUGroupIDLst
(
CztGUGroupIDLst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztGUGroupIDLst(param, mBuf)
CztGUGroupIDLst *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztGUGroupIDLst) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztGU_Group_ID, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztGUGroupIDLst */

#define cmPkCztMME_Code cmPkTknStr4 


/* 
* FUN : cmPkCzt_ExtnGUMMEI_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnGUMMEI_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnGUMMEI_ExtIEsCls
(
Czt_ExtnGUMMEI_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnGUMMEI_ExtIEsCls(param, val, mBuf)
Czt_ExtnGUMMEI_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnGUMMEI_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnGUMMEI_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_GUMMEI_ExtIEs
*  DESC: Function to Pack CztProtExtnField_GUMMEI_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_GUMMEI_ExtIEs
(
CztProtExtnField_GUMMEI_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_GUMMEI_ExtIEs(param, mBuf)
CztProtExtnField_GUMMEI_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_GUMMEI_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnGUMMEI_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_GUMMEI_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_GUMMEI_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_GUMMEI_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_GUMMEI_ExtIEs
(
CztProtExtnCont_GUMMEI_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_GUMMEI_ExtIEs(param, mBuf)
CztProtExtnCont_GUMMEI_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_GUMMEI_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_GUMMEI_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_GUMMEI_ExtIEs */



/* 
* FUN : cmPkCztGUMMEI
*  DESC: Function to Pack CztGUMMEI structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztGUMMEI
(
CztGUMMEI *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztGUMMEI(param, mBuf)
CztGUMMEI *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztGUMMEI) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_GUMMEI_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztMME_Code, &param->mME_Code, mBuf); 
		CMCHKPK(cmPkCztGU_Group_ID, &param->gU_Group_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztGUMMEI */

#define cmPkCztHovrReportTyp cmPkTknU32


/* 
* FUN : cmPkCzt_ExtnHovrRestrnLst_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnHovrRestrnLst_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnHovrRestrnLst_ExtIEsCls
(
Czt_ExtnHovrRestrnLst_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnHovrRestrnLst_ExtIEsCls(param, val, mBuf)
Czt_ExtnHovrRestrnLst_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnHovrRestrnLst_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnHovrRestrnLst_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_HovrRestrnLst_ExtIEs
*  DESC: Function to Pack CztProtExtnField_HovrRestrnLst_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_HovrRestrnLst_ExtIEs
(
CztProtExtnField_HovrRestrnLst_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_HovrRestrnLst_ExtIEs(param, mBuf)
CztProtExtnField_HovrRestrnLst_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_HovrRestrnLst_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnHovrRestrnLst_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_HovrRestrnLst_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_HovrRestrnLst_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_HovrRestrnLst_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_HovrRestrnLst_ExtIEs
(
CztProtExtnCont_HovrRestrnLst_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_HovrRestrnLst_ExtIEs(param, mBuf)
CztProtExtnCont_HovrRestrnLst_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_HovrRestrnLst_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_HovrRestrnLst_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_HovrRestrnLst_ExtIEs */



/* 
* FUN : cmPkCztHovrRestrnLst
*  DESC: Function to Pack CztHovrRestrnLst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztHovrRestrnLst
(
CztHovrRestrnLst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztHovrRestrnLst(param, mBuf)
CztHovrRestrnLst *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztHovrRestrnLst) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_HovrRestrnLst_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztForbiddenInterRATs, &param->forbiddenInterRATs, mBuf); 
		CMCHKPK(cmPkCztForbiddenLAs, &param->forbiddenLAs, mBuf); 
		CMCHKPK(cmPkCztForbiddenTAs, &param->forbiddenTAs, mBuf); 
		CMCHKPK(cmPkCztEPLMNs, &param->equivalentPLMNs, mBuf); 
		CMCHKPK(cmPkCztPLMN_Identity, &param->servingPLMN, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztHovrRestrnLst */

#define cmPkCztLoadIndicator cmPkTknU32


/* 
* FUN : cmPkCzt_ExtnHWLoadIndicator_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnHWLoadIndicator_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnHWLoadIndicator_ExtIEsCls
(
Czt_ExtnHWLoadIndicator_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnHWLoadIndicator_ExtIEsCls(param, val, mBuf)
Czt_ExtnHWLoadIndicator_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnHWLoadIndicator_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnHWLoadIndicator_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_HWLoadIndicator_ExtIEs
*  DESC: Function to Pack CztProtExtnField_HWLoadIndicator_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_HWLoadIndicator_ExtIEs
(
CztProtExtnField_HWLoadIndicator_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_HWLoadIndicator_ExtIEs(param, mBuf)
CztProtExtnField_HWLoadIndicator_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_HWLoadIndicator_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnHWLoadIndicator_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_HWLoadIndicator_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_HWLoadIndicator_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_HWLoadIndicator_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_HWLoadIndicator_ExtIEs
(
CztProtExtnCont_HWLoadIndicator_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_HWLoadIndicator_ExtIEs(param, mBuf)
CztProtExtnCont_HWLoadIndicator_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_HWLoadIndicator_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_HWLoadIndicator_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_HWLoadIndicator_ExtIEs */



/* 
* FUN : cmPkCztHWLoadIndicator
*  DESC: Function to Pack CztHWLoadIndicator structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztHWLoadIndicator
(
CztHWLoadIndicator *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztHWLoadIndicator(param, mBuf)
CztHWLoadIndicator *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztHWLoadIndicator) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_HWLoadIndicator_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztLoadIndicator, &param->uLHWLoadIndicator, mBuf); 
		CMCHKPK(cmPkCztLoadIndicator, &param->dLHWLoadIndicator, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztHWLoadIndicator */

#define cmPkCztInvokeInd cmPkTknU32
#define cmPkCztIntegrityProtectionAlgorithms cmPkTknBStr32 
#define cmPkCztIntfsToTrace cmPkTknBStr32 
#define cmPkCztTime_UE_StayedInCell cmPkTknU32 
#define cmPkCztTime_UE_StayedInCell_EnhancedGranularity cmPkTknU32 


/* 
* FUN : cmPkCzt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls
(
Czt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls(param, val, mBuf)
Czt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls) 
	
	switch (val)
	{
		case Cztid_Time_UE_StayedInCell_EnhancedGranularity:
			CMCHKPK(cmPkCztTime_UE_StayedInCell_EnhancedGranularity, &param->u.cztTime_UE_StayedInCell_EnhancedGranularity, mBuf);
			break;
		case Cztid_HO_cause:
			CMCHKPK(cmPkCztCause, &param->u.cztCause, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs
*  DESC: Function to Pack CztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs
(
CztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs(param, mBuf)
CztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs
(
CztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs(param, mBuf)
CztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs */



/* 
* FUN : cmPkCztLastVisitedEUTRANCellInform
*  DESC: Function to Pack CztLastVisitedEUTRANCellInform structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztLastVisitedEUTRANCellInform
(
CztLastVisitedEUTRANCellInform *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztLastVisitedEUTRANCellInform(param, mBuf)
CztLastVisitedEUTRANCellInform *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztLastVisitedEUTRANCellInform) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztTime_UE_StayedInCell, &param->time_UE_StayedInCell, mBuf); 
		CMCHKPK(cmPkCztCellTyp, &param->cellTyp, mBuf); 
		CMCHKPK(cmPkCztECGI, &param->global_Cell_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztLastVisitedEUTRANCellInform */

#define cmPkCztLastVisitedUTRANCellInform cmPkTknStrOSXL 


/* 
* FUN : cmPkCztLastVisitedGERANCellInform
*  DESC: Function to Pack CztLastVisitedGERANCellInform structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztLastVisitedGERANCellInform
(
CztLastVisitedGERANCellInform *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztLastVisitedGERANCellInform(param, mBuf)
CztLastVisitedGERANCellInform *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztLastVisitedGERANCellInform) 
	
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
}	 /* End of function cmPkCztLastVisitedGERANCellInform */



/* 
* FUN : cmPkCztLastVisitedCell_Item
*  DESC: Function to Pack CztLastVisitedCell_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztLastVisitedCell_Item
(
CztLastVisitedCell_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztLastVisitedCell_Item(param, mBuf)
CztLastVisitedCell_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztLastVisitedCell_Item) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case LASTVISITEDCELL_ITEM_GERAN_CELL :
				CMCHKPK(cmPkCztLastVisitedGERANCellInform, &param->val.gERAN_Cell, mBuf); 
				break;
			case LASTVISITEDCELL_ITEM_UTRAN_CELL :
				CMCHKPK(cmPkCztLastVisitedUTRANCellInform, &param->val.uTRAN_Cell, mBuf); 
				break;
			case LASTVISITEDCELL_ITEM_E_UTRAN_CELL :
				CMCHKPK(cmPkCztLastVisitedEUTRANCellInform, &param->val.e_UTRAN_Cell, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztLastVisitedCell_Item */

#define cmPkCztLinks_to_log cmPkTknU32
#define cmPkCztReportArea cmPkTknU32


/* 
* FUN : cmPkCzt_ExtnLocRprtngInform_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnLocRprtngInform_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnLocRprtngInform_ExtIEsCls
(
Czt_ExtnLocRprtngInform_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnLocRprtngInform_ExtIEsCls(param, val, mBuf)
Czt_ExtnLocRprtngInform_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnLocRprtngInform_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnLocRprtngInform_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_LocRprtngInform_ExtIEs
*  DESC: Function to Pack CztProtExtnField_LocRprtngInform_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_LocRprtngInform_ExtIEs
(
CztProtExtnField_LocRprtngInform_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_LocRprtngInform_ExtIEs(param, mBuf)
CztProtExtnField_LocRprtngInform_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_LocRprtngInform_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnLocRprtngInform_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_LocRprtngInform_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_LocRprtngInform_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_LocRprtngInform_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_LocRprtngInform_ExtIEs
(
CztProtExtnCont_LocRprtngInform_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_LocRprtngInform_ExtIEs(param, mBuf)
CztProtExtnCont_LocRprtngInform_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_LocRprtngInform_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_LocRprtngInform_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_LocRprtngInform_ExtIEs */



/* 
* FUN : cmPkCztLocRprtngInform
*  DESC: Function to Pack CztLocRprtngInform structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztLocRprtngInform
(
CztLocRprtngInform *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztLocRprtngInform(param, mBuf)
CztLocRprtngInform *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztLocRprtngInform) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_LocRprtngInform_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztReportArea, &param->reportArea, mBuf); 
		CMCHKPK(cmPkCztEventTyp, &param->eventTyp, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztLocRprtngInform */

#define cmPkCztM3period cmPkTknU32


/* 
* FUN : cmPkCzt_ExtnM3Config_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnM3Config_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnM3Config_ExtIEsCls
(
Czt_ExtnM3Config_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnM3Config_ExtIEsCls(param, val, mBuf)
Czt_ExtnM3Config_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnM3Config_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnM3Config_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_M3Config_ExtIEs
*  DESC: Function to Pack CztProtExtnField_M3Config_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_M3Config_ExtIEs
(
CztProtExtnField_M3Config_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_M3Config_ExtIEs(param, mBuf)
CztProtExtnField_M3Config_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_M3Config_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnM3Config_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_M3Config_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_M3Config_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_M3Config_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_M3Config_ExtIEs
(
CztProtExtnCont_M3Config_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_M3Config_ExtIEs(param, mBuf)
CztProtExtnCont_M3Config_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_M3Config_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_M3Config_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_M3Config_ExtIEs */



/* 
* FUN : cmPkCztM3Config
*  DESC: Function to Pack CztM3Config structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztM3Config
(
CztM3Config *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztM3Config(param, mBuf)
CztM3Config *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztM3Config) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_M3Config_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztM3period, &param->m3period, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztM3Config */

#define cmPkCztM4period cmPkTknU32


/* 
* FUN : cmPkCzt_ExtnM4Config_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnM4Config_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnM4Config_ExtIEsCls
(
Czt_ExtnM4Config_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnM4Config_ExtIEsCls(param, val, mBuf)
Czt_ExtnM4Config_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnM4Config_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnM4Config_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_M4Config_ExtIEs
*  DESC: Function to Pack CztProtExtnField_M4Config_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_M4Config_ExtIEs
(
CztProtExtnField_M4Config_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_M4Config_ExtIEs(param, mBuf)
CztProtExtnField_M4Config_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_M4Config_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnM4Config_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_M4Config_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_M4Config_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_M4Config_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_M4Config_ExtIEs
(
CztProtExtnCont_M4Config_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_M4Config_ExtIEs(param, mBuf)
CztProtExtnCont_M4Config_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_M4Config_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_M4Config_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_M4Config_ExtIEs */



/* 
* FUN : cmPkCztM4Config
*  DESC: Function to Pack CztM4Config structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztM4Config
(
CztM4Config *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztM4Config(param, mBuf)
CztM4Config *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztM4Config) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_M4Config_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztLinks_to_log, &param->m4_links_to_log, mBuf); 
		CMCHKPK(cmPkCztM4period, &param->m4period, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztM4Config */

#define cmPkCztM5period cmPkTknU32


/* 
* FUN : cmPkCzt_ExtnM5Config_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnM5Config_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnM5Config_ExtIEsCls
(
Czt_ExtnM5Config_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnM5Config_ExtIEsCls(param, val, mBuf)
Czt_ExtnM5Config_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnM5Config_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnM5Config_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_M5Config_ExtIEs
*  DESC: Function to Pack CztProtExtnField_M5Config_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_M5Config_ExtIEs
(
CztProtExtnField_M5Config_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_M5Config_ExtIEs(param, mBuf)
CztProtExtnField_M5Config_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_M5Config_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnM5Config_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_M5Config_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_M5Config_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_M5Config_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_M5Config_ExtIEs
(
CztProtExtnCont_M5Config_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_M5Config_ExtIEs(param, mBuf)
CztProtExtnCont_M5Config_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_M5Config_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_M5Config_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_M5Config_ExtIEs */



/* 
* FUN : cmPkCztM5Config
*  DESC: Function to Pack CztM5Config structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztM5Config
(
CztM5Config *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztM5Config(param, mBuf)
CztM5Config *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztM5Config) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_M5Config_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztLinks_to_log, &param->m5_links_to_log, mBuf); 
		CMCHKPK(cmPkCztM5period, &param->m5period, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztM5Config */

#define cmPkCztMDT_Actvn cmPkTknU32
#define cmPkCztMeasurementsToActivate cmPkTknBStr32 
#define cmPkCztM1RprtngTrigger cmPkTknU32
#define cmPkCztThreshold_RSRP cmPkTknU32 
#define cmPkCztThreshold_RSRQ cmPkTknU32 


/* 
* FUN : cmPkCztMeasurementThresholdA2
*  DESC: Function to Pack CztMeasurementThresholdA2 structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztMeasurementThresholdA2
(
CztMeasurementThresholdA2 *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztMeasurementThresholdA2(param, mBuf)
CztMeasurementThresholdA2 *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztMeasurementThresholdA2) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case MEASUREMENTTHRESHOLDA2_THRESHOLD_RSRQ :
				CMCHKPK(cmPkCztThreshold_RSRQ, &param->val.threshold_RSRQ, mBuf); 
				break;
			case MEASUREMENTTHRESHOLDA2_THRESHOLD_RSRP :
				CMCHKPK(cmPkCztThreshold_RSRP, &param->val.threshold_RSRP, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztMeasurementThresholdA2 */



/* 
* FUN : cmPkCzt_ExtnM1ThresholdEventA2_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnM1ThresholdEventA2_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnM1ThresholdEventA2_ExtIEsCls
(
Czt_ExtnM1ThresholdEventA2_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnM1ThresholdEventA2_ExtIEsCls(param, val, mBuf)
Czt_ExtnM1ThresholdEventA2_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnM1ThresholdEventA2_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnM1ThresholdEventA2_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_M1ThresholdEventA2_ExtIEs
*  DESC: Function to Pack CztProtExtnField_M1ThresholdEventA2_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_M1ThresholdEventA2_ExtIEs
(
CztProtExtnField_M1ThresholdEventA2_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_M1ThresholdEventA2_ExtIEs(param, mBuf)
CztProtExtnField_M1ThresholdEventA2_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_M1ThresholdEventA2_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnM1ThresholdEventA2_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_M1ThresholdEventA2_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_M1ThresholdEventA2_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_M1ThresholdEventA2_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_M1ThresholdEventA2_ExtIEs
(
CztProtExtnCont_M1ThresholdEventA2_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_M1ThresholdEventA2_ExtIEs(param, mBuf)
CztProtExtnCont_M1ThresholdEventA2_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_M1ThresholdEventA2_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_M1ThresholdEventA2_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_M1ThresholdEventA2_ExtIEs */



/* 
* FUN : cmPkCztM1ThresholdEventA2
*  DESC: Function to Pack CztM1ThresholdEventA2 structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztM1ThresholdEventA2
(
CztM1ThresholdEventA2 *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztM1ThresholdEventA2(param, mBuf)
CztM1ThresholdEventA2 *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztM1ThresholdEventA2) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_M1ThresholdEventA2_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztMeasurementThresholdA2, &param->measurementThreshold, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztM1ThresholdEventA2 */

#define cmPkCztReportIntervalMDT cmPkTknU32
#define cmPkCztReportAmountMDT cmPkTknU32


/* 
* FUN : cmPkCzt_ExtnM1PeriodicRprtng_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnM1PeriodicRprtng_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnM1PeriodicRprtng_ExtIEsCls
(
Czt_ExtnM1PeriodicRprtng_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnM1PeriodicRprtng_ExtIEsCls(param, val, mBuf)
Czt_ExtnM1PeriodicRprtng_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnM1PeriodicRprtng_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnM1PeriodicRprtng_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_M1PeriodicRprtng_ExtIEs
*  DESC: Function to Pack CztProtExtnField_M1PeriodicRprtng_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_M1PeriodicRprtng_ExtIEs
(
CztProtExtnField_M1PeriodicRprtng_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_M1PeriodicRprtng_ExtIEs(param, mBuf)
CztProtExtnField_M1PeriodicRprtng_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_M1PeriodicRprtng_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnM1PeriodicRprtng_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_M1PeriodicRprtng_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_M1PeriodicRprtng_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_M1PeriodicRprtng_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_M1PeriodicRprtng_ExtIEs
(
CztProtExtnCont_M1PeriodicRprtng_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_M1PeriodicRprtng_ExtIEs(param, mBuf)
CztProtExtnCont_M1PeriodicRprtng_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_M1PeriodicRprtng_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_M1PeriodicRprtng_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_M1PeriodicRprtng_ExtIEs */



/* 
* FUN : cmPkCztM1PeriodicRprtng
*  DESC: Function to Pack CztM1PeriodicRprtng structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztM1PeriodicRprtng
(
CztM1PeriodicRprtng *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztM1PeriodicRprtng(param, mBuf)
CztM1PeriodicRprtng *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztM1PeriodicRprtng) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_M1PeriodicRprtng_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztReportAmountMDT, &param->reportAmount, mBuf); 
		CMCHKPK(cmPkCztReportIntervalMDT, &param->reportInterval, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztM1PeriodicRprtng */

#define cmPkCztMDT_Loc_Info cmPkTknBStr32 


/* 
* FUN : cmPkCztMDTPLMNLst
*  DESC: Function to Pack CztMDTPLMNLst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztMDTPLMNLst
(
CztMDTPLMNLst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztMDTPLMNLst(param, mBuf)
CztMDTPLMNLst *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztMDTPLMNLst) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztPLMN_Identity, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztMDTPLMNLst */



/* 
* FUN : cmPkCzt_ExtnMDT_Config_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnMDT_Config_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnMDT_Config_ExtIEsCls
(
Czt_ExtnMDT_Config_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnMDT_Config_ExtIEsCls(param, val, mBuf)
Czt_ExtnMDT_Config_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnMDT_Config_ExtIEsCls) 
	
	switch (val)
	{
		case Cztid_M3Config:
			CMCHKPK(cmPkCztM3Config, &param->u.cztM3Config, mBuf);
			break;
		case Cztid_M4Config:
			CMCHKPK(cmPkCztM4Config, &param->u.cztM4Config, mBuf);
			break;
		case Cztid_M5Config:
			CMCHKPK(cmPkCztM5Config, &param->u.cztM5Config, mBuf);
			break;
		case Cztid_MDT_Loc_Info:
			CMCHKPK(cmPkCztMDT_Loc_Info, &param->u.cztMDT_Loc_Info, mBuf);
			break;
		case Cztid_SignallingBasedMDTPLMNLst:
			CMCHKPK(cmPkCztMDTPLMNLst, &param->u.cztMDTPLMNLst, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ExtnMDT_Config_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_MDT_Config_ExtIEs
*  DESC: Function to Pack CztProtExtnField_MDT_Config_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_MDT_Config_ExtIEs
(
CztProtExtnField_MDT_Config_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_MDT_Config_ExtIEs(param, mBuf)
CztProtExtnField_MDT_Config_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_MDT_Config_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnMDT_Config_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_MDT_Config_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_MDT_Config_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_MDT_Config_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_MDT_Config_ExtIEs
(
CztProtExtnCont_MDT_Config_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_MDT_Config_ExtIEs(param, mBuf)
CztProtExtnCont_MDT_Config_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_MDT_Config_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_MDT_Config_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_MDT_Config_ExtIEs */



/* 
* FUN : cmPkCztMDT_Config
*  DESC: Function to Pack CztMDT_Config structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztMDT_Config
(
CztMDT_Config *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztMDT_Config(param, mBuf)
CztMDT_Config *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztMDT_Config) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_MDT_Config_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztM1PeriodicRprtng, &param->m1periodicRprtng, mBuf); 
		CMCHKPK(cmPkCztM1ThresholdEventA2, &param->m1thresholdeventA2, mBuf); 
		CMCHKPK(cmPkCztM1RprtngTrigger, &param->m1reportingTrigger, mBuf); 
		CMCHKPK(cmPkCztMeasurementsToActivate, &param->measurementsToActivate, mBuf); 
		CMCHKPK(cmPkCztAreaScopeOfMDT, &param->areaScopeOfMDT, mBuf); 
		CMCHKPK(cmPkCztMDT_Actvn, &param->mdt_Actvn, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztMDT_Config */

#define cmPkCztMeasurement_ID cmPkTknU32 
#define cmPkCztMBMS_Service_Area_Identity cmPkTknStr4 


/* 
* FUN : cmPkCztMBMS_Service_Area_Identity_Lst
*  DESC: Function to Pack CztMBMS_Service_Area_Identity_Lst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztMBMS_Service_Area_Identity_Lst
(
CztMBMS_Service_Area_Identity_Lst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztMBMS_Service_Area_Identity_Lst(param, mBuf)
CztMBMS_Service_Area_Identity_Lst *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztMBMS_Service_Area_Identity_Lst) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztMBMS_Service_Area_Identity, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztMBMS_Service_Area_Identity_Lst */

#define cmPkCztRadioframeAllocnPeriod cmPkTknU32
#define cmPkCztRadioframeAllocnOffset cmPkTknU32 
#define cmPkCztOneframe cmPkTknBStr32 


/* 
* FUN : cmPkCztSubframeAllocn
*  DESC: Function to Pack CztSubframeAllocn structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztSubframeAllocn
(
CztSubframeAllocn *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztSubframeAllocn(param, mBuf)
CztSubframeAllocn *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztSubframeAllocn) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case SUBFRAMEALLOCN_FOURFRAMES :
				CMCHKPK(cmPkCztFourframes, &param->val.fourframes, mBuf); 
				break;
			case SUBFRAMEALLOCN_ONEFRAME :
				CMCHKPK(cmPkCztOneframe, &param->val.oneframe, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztSubframeAllocn */



/* 
* FUN : cmPkCzt_ExtnMBSFN_Subframe_Info_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnMBSFN_Subframe_Info_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnMBSFN_Subframe_Info_ExtIEsCls
(
Czt_ExtnMBSFN_Subframe_Info_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnMBSFN_Subframe_Info_ExtIEsCls(param, val, mBuf)
Czt_ExtnMBSFN_Subframe_Info_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnMBSFN_Subframe_Info_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnMBSFN_Subframe_Info_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_MBSFN_Subframe_Info_ExtIEs
*  DESC: Function to Pack CztProtExtnField_MBSFN_Subframe_Info_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_MBSFN_Subframe_Info_ExtIEs
(
CztProtExtnField_MBSFN_Subframe_Info_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_MBSFN_Subframe_Info_ExtIEs(param, mBuf)
CztProtExtnField_MBSFN_Subframe_Info_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_MBSFN_Subframe_Info_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnMBSFN_Subframe_Info_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_MBSFN_Subframe_Info_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_MBSFN_Subframe_Info_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_MBSFN_Subframe_Info_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_MBSFN_Subframe_Info_ExtIEs
(
CztProtExtnCont_MBSFN_Subframe_Info_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_MBSFN_Subframe_Info_ExtIEs(param, mBuf)
CztProtExtnCont_MBSFN_Subframe_Info_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_MBSFN_Subframe_Info_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_MBSFN_Subframe_Info_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_MBSFN_Subframe_Info_ExtIEs */



/* 
* FUN : cmPkCztMBSFN_Subframe_Info
*  DESC: Function to Pack CztMBSFN_Subframe_Info structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztMBSFN_Subframe_Info
(
CztMBSFN_Subframe_Info *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztMBSFN_Subframe_Info(param, mBuf)
CztMBSFN_Subframe_Info *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztMBSFN_Subframe_Info) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_MBSFN_Subframe_Info_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztSubframeAllocn, &param->subframeAllocn, mBuf); 
		CMCHKPK(cmPkCztRadioframeAllocnOffset, &param->radioframeAllocnOffset, mBuf); 
		CMCHKPK(cmPkCztRadioframeAllocnPeriod, &param->radioframeAllocnPeriod, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztMBSFN_Subframe_Info */



/* 
* FUN : cmPkCztMBSFN_Subframe_Infolist
*  DESC: Function to Pack CztMBSFN_Subframe_Infolist structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztMBSFN_Subframe_Infolist
(
CztMBSFN_Subframe_Infolist *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztMBSFN_Subframe_Infolist(param, mBuf)
CztMBSFN_Subframe_Infolist *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztMBSFN_Subframe_Infolist) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztMBSFN_Subframe_Info, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztMBSFN_Subframe_Infolist */

#define cmPkCztManagementBasedMDTallowed cmPkTknU32
#define cmPkCztMobilityParamsModificationRangehandoverTriggerChangeLowerLimit cmPkTknS32 
#define cmPkCztMobilityParamsModificationRangehandoverTriggerChangeUpperLimit cmPkTknS32 


/* 
* FUN : cmPkCztMobilityParamsModificationRange
*  DESC: Function to Pack CztMobilityParamsModificationRange structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztMobilityParamsModificationRange
(
CztMobilityParamsModificationRange *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztMobilityParamsModificationRange(param, mBuf)
CztMobilityParamsModificationRange *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztMobilityParamsModificationRange) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztMobilityParamsModificationRangehandoverTriggerChangeUpperLimit, &param->handoverTriggerChangeUpperLimit, mBuf); 
		CMCHKPK(cmPkCztMobilityParamsModificationRangehandoverTriggerChangeLowerLimit, &param->handoverTriggerChangeLowerLimit, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztMobilityParamsModificationRange */

#define cmPkCztMobilityParamsInformhandoverTriggerChange cmPkTknS32 


/* 
* FUN : cmPkCztMobilityParamsInform
*  DESC: Function to Pack CztMobilityParamsInform structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztMobilityParamsInform
(
CztMobilityParamsInform *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztMobilityParamsInform(param, mBuf)
CztMobilityParamsInform *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztMobilityParamsInform) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztMobilityParamsInformhandoverTriggerChange, &param->handoverTriggerChange, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztMobilityParamsInform */



/* 
* FUN : cmPkCzt_ExtnBandInfo_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnBandInfo_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnBandInfo_ExtIEsCls
(
Czt_ExtnBandInfo_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnBandInfo_ExtIEsCls(param, val, mBuf)
Czt_ExtnBandInfo_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnBandInfo_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnBandInfo_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_BandInfo_ExtIEs
*  DESC: Function to Pack CztProtExtnField_BandInfo_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_BandInfo_ExtIEs
(
CztProtExtnField_BandInfo_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_BandInfo_ExtIEs(param, mBuf)
CztProtExtnField_BandInfo_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_BandInfo_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnBandInfo_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_BandInfo_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_BandInfo_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_BandInfo_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_BandInfo_ExtIEs
(
CztProtExtnCont_BandInfo_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_BandInfo_ExtIEs(param, mBuf)
CztProtExtnCont_BandInfo_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_BandInfo_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_BandInfo_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_BandInfo_ExtIEs */



/* 
* FUN : cmPkCztBandInfo
*  DESC: Function to Pack CztBandInfo structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztBandInfo
(
CztBandInfo *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztBandInfo(param, mBuf)
CztBandInfo *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztBandInfo) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_BandInfo_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztFreqBandIndicator, &param->freqBandIndicator, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztBandInfo */



/* 
* FUN : cmPkCztMultibandInfoLst
*  DESC: Function to Pack CztMultibandInfoLst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztMultibandInfoLst
(
CztMultibandInfoLst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztMultibandInfoLst(param, mBuf)
CztMultibandInfoLst *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztMultibandInfoLst) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztBandInfo, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztMultibandInfoLst */

#define cmPkCztPCI cmPkTknU32 


/* 
* FUN : cmPkCzt_ExtnNeighbour_Inform_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnNeighbour_Inform_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnNeighbour_Inform_ExtIEsCls
(
Czt_ExtnNeighbour_Inform_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnNeighbour_Inform_ExtIEsCls(param, val, mBuf)
Czt_ExtnNeighbour_Inform_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnNeighbour_Inform_ExtIEsCls) 
	
	switch (val)
	{
		case Cztid_NeighbourTAC:
			CMCHKPK(cmPkCztTAC, &param->u.cztTAC, mBuf);
			break;
		case Cztid_eARFCNExtn:
			CMCHKPK(cmPkCztEARFCNExtn, &param->u.cztEARFCNExtn, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ExtnNeighbour_Inform_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_Neighbour_Inform_ExtIEs
*  DESC: Function to Pack CztProtExtnField_Neighbour_Inform_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_Neighbour_Inform_ExtIEs
(
CztProtExtnField_Neighbour_Inform_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_Neighbour_Inform_ExtIEs(param, mBuf)
CztProtExtnField_Neighbour_Inform_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_Neighbour_Inform_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnNeighbour_Inform_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_Neighbour_Inform_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_Neighbour_Inform_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_Neighbour_Inform_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_Neighbour_Inform_ExtIEs
(
CztProtExtnCont_Neighbour_Inform_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_Neighbour_Inform_ExtIEs(param, mBuf)
CztProtExtnCont_Neighbour_Inform_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_Neighbour_Inform_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_Neighbour_Inform_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_Neighbour_Inform_ExtIEs */



/* 
* FUN : cmPkCztNeighbour_InformMember
*  DESC: Function to Pack CztNeighbour_InformMember structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztNeighbour_InformMember
(
CztNeighbour_InformMember *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztNeighbour_InformMember(param, mBuf)
CztNeighbour_InformMember *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztNeighbour_InformMember) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_Neighbour_Inform_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztEARFCN, &param->eARFCN, mBuf); 
		CMCHKPK(cmPkCztPCI, &param->pCI, mBuf); 
		CMCHKPK(cmPkCztECGI, &param->eCGI, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztNeighbour_InformMember */



/* 
* FUN : cmPkCztNeighbour_Inform
*  DESC: Function to Pack CztNeighbour_Inform structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztNeighbour_Inform
(
CztNeighbour_Inform *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztNeighbour_Inform(param, mBuf)
CztNeighbour_Inform *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztNeighbour_Inform) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztNeighbour_InformMember, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztNeighbour_Inform */

#define cmPkCztNumber_of_Antennaports cmPkTknU32
#define cmPkCztPRACH_ConfigrootSequenceIdx cmPkTknU32 
#define cmPkCztPRACH_ConfigzeroCorrelationIdx cmPkTknU32 
#define cmPkCztPRACH_ConfighighSpeedFlag cmPkTknU8
#define cmPkCztPRACH_Configprach_FreqOffset cmPkTknU32 
#define cmPkCztPRACH_Configprach_ConfigIdx cmPkTknU32 


/* 
* FUN : cmPkCzt_ExtnPRACH_Config_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnPRACH_Config_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnPRACH_Config_ExtIEsCls
(
Czt_ExtnPRACH_Config_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnPRACH_Config_ExtIEsCls(param, val, mBuf)
Czt_ExtnPRACH_Config_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnPRACH_Config_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnPRACH_Config_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_PRACH_Config_ExtIEs
*  DESC: Function to Pack CztProtExtnField_PRACH_Config_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_PRACH_Config_ExtIEs
(
CztProtExtnField_PRACH_Config_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_PRACH_Config_ExtIEs(param, mBuf)
CztProtExtnField_PRACH_Config_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_PRACH_Config_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnPRACH_Config_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_PRACH_Config_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_PRACH_Config_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_PRACH_Config_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_PRACH_Config_ExtIEs
(
CztProtExtnCont_PRACH_Config_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_PRACH_Config_ExtIEs(param, mBuf)
CztProtExtnCont_PRACH_Config_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_PRACH_Config_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_PRACH_Config_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_PRACH_Config_ExtIEs */



/* 
* FUN : cmPkCztPRACH_Config
*  DESC: Function to Pack CztPRACH_Config structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztPRACH_Config
(
CztPRACH_Config *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztPRACH_Config(param, mBuf)
CztPRACH_Config *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztPRACH_Config) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_PRACH_Config_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztPRACH_Configprach_ConfigIdx, &param->prach_ConfigIdx, mBuf); 
		CMCHKPK(cmPkCztPRACH_Configprach_FreqOffset, &param->prach_FreqOffset, mBuf); 
		CMCHKPK(cmPkCztPRACH_ConfighighSpeedFlag, &param->highSpeedFlag, mBuf); 
		CMCHKPK(cmPkCztPRACH_ConfigzeroCorrelationIdx, &param->zeroCorrelationIdx, mBuf); 
		CMCHKPK(cmPkCztPRACH_ConfigrootSequenceIdx, &param->rootSequenceIdx, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztPRACH_Config */

#define cmPkCztUL_GBR_PRB_usage cmPkTknU32 
#define cmPkCztUL_non_GBR_PRB_usage cmPkTknU32 
#define cmPkCztUL_Total_PRB_usage cmPkTknU32 


/* 
* FUN : cmPkCzt_ExtnRadioResStatus_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnRadioResStatus_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnRadioResStatus_ExtIEsCls
(
Czt_ExtnRadioResStatus_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnRadioResStatus_ExtIEsCls(param, val, mBuf)
Czt_ExtnRadioResStatus_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnRadioResStatus_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnRadioResStatus_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_RadioResStatus_ExtIEs
*  DESC: Function to Pack CztProtExtnField_RadioResStatus_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_RadioResStatus_ExtIEs
(
CztProtExtnField_RadioResStatus_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_RadioResStatus_ExtIEs(param, mBuf)
CztProtExtnField_RadioResStatus_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_RadioResStatus_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnRadioResStatus_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_RadioResStatus_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_RadioResStatus_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_RadioResStatus_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_RadioResStatus_ExtIEs
(
CztProtExtnCont_RadioResStatus_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_RadioResStatus_ExtIEs(param, mBuf)
CztProtExtnCont_RadioResStatus_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_RadioResStatus_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_RadioResStatus_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_RadioResStatus_ExtIEs */



/* 
* FUN : cmPkCztRadioResStatus
*  DESC: Function to Pack CztRadioResStatus structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztRadioResStatus
(
CztRadioResStatus *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztRadioResStatus(param, mBuf)
CztRadioResStatus *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztRadioResStatus) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_RadioResStatus_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztUL_Total_PRB_usage, &param->uL_Total_PRB_usage, mBuf); 
		CMCHKPK(cmPkCztDL_Total_PRB_usage, &param->dL_Total_PRB_usage, mBuf); 
		CMCHKPK(cmPkCztUL_non_GBR_PRB_usage, &param->uL_non_GBR_PRB_usage, mBuf); 
		CMCHKPK(cmPkCztDL_non_GBR_PRB_usage, &param->dL_non_GBR_PRB_usage, mBuf); 
		CMCHKPK(cmPkCztUL_GBR_PRB_usage, &param->uL_GBR_PRB_usage, mBuf); 
		CMCHKPK(cmPkCztDL_GBR_PRB_usage, &param->dL_GBR_PRB_usage, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztRadioResStatus */

#define cmPkCztReceiveStatusofULPDCPSDUs cmPkTknStrBSXL 
#define cmPkCztReceiveStatusOfULPDCPSDUsExtended cmPkTknStrBSXL 
#define cmPkCztRegistration_Rqst cmPkTknU32
#define cmPkCztRNTP_Threshold cmPkTknU32
#define cmPkCztRelativeNarrowbandTxPowerrNTP_PerPRB cmPkTknStrBSXL 
#define cmPkCztRelativeNarrowbandTxPowernumberOfCellSpecificAntennaPorts cmPkTknU32
#define cmPkCztRelativeNarrowbandTxPowerp_B cmPkTknU32 
#define cmPkCztRelativeNarrowbandTxPowerpDCCH_InterferenceImpact cmPkTknU32 


/* 
* FUN : cmPkCzt_ExtnRelativeNarrowbandTxPower_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnRelativeNarrowbandTxPower_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnRelativeNarrowbandTxPower_ExtIEsCls
(
Czt_ExtnRelativeNarrowbandTxPower_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnRelativeNarrowbandTxPower_ExtIEsCls(param, val, mBuf)
Czt_ExtnRelativeNarrowbandTxPower_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnRelativeNarrowbandTxPower_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnRelativeNarrowbandTxPower_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_RelativeNarrowbandTxPower_ExtIEs
*  DESC: Function to Pack CztProtExtnField_RelativeNarrowbandTxPower_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_RelativeNarrowbandTxPower_ExtIEs
(
CztProtExtnField_RelativeNarrowbandTxPower_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_RelativeNarrowbandTxPower_ExtIEs(param, mBuf)
CztProtExtnField_RelativeNarrowbandTxPower_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_RelativeNarrowbandTxPower_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnRelativeNarrowbandTxPower_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_RelativeNarrowbandTxPower_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_RelativeNarrowbandTxPower_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_RelativeNarrowbandTxPower_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_RelativeNarrowbandTxPower_ExtIEs
(
CztProtExtnCont_RelativeNarrowbandTxPower_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_RelativeNarrowbandTxPower_ExtIEs(param, mBuf)
CztProtExtnCont_RelativeNarrowbandTxPower_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_RelativeNarrowbandTxPower_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_RelativeNarrowbandTxPower_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_RelativeNarrowbandTxPower_ExtIEs */



/* 
* FUN : cmPkCztRelativeNarrowbandTxPower
*  DESC: Function to Pack CztRelativeNarrowbandTxPower structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztRelativeNarrowbandTxPower
(
CztRelativeNarrowbandTxPower *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztRelativeNarrowbandTxPower(param, mBuf)
CztRelativeNarrowbandTxPower *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztRelativeNarrowbandTxPower) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_RelativeNarrowbandTxPower_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztRelativeNarrowbandTxPowerpDCCH_InterferenceImpact, &param->pDCCH_InterferenceImpact, mBuf); 
		CMCHKPK(cmPkCztRelativeNarrowbandTxPowerp_B, &param->p_B, mBuf); 
		CMCHKPK(cmPkCztRelativeNarrowbandTxPowernumberOfCellSpecificAntennaPorts, &param->numberOfCellSpecificAntennaPorts, mBuf); 
		CMCHKPK(cmPkCztRNTP_Threshold, &param->rNTP_Threshold, mBuf); 
		CMCHKPK(cmPkCztRelativeNarrowbandTxPowerrNTP_PerPRB, &param->rNTP_PerPRB, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztRelativeNarrowbandTxPower */

#define cmPkCztReportCharacteristics cmPkTknBStr32 
#define cmPkCztRRC_Cntxt cmPkTknStrOSXL 
#define cmPkCztRRCConnReestabIndicator cmPkTknU32
#define cmPkCztRRCConnSetupIndicator cmPkTknU32


/* 
* FUN : cmPkCzt_ExtnS1TNLLoadIndicator_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnS1TNLLoadIndicator_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnS1TNLLoadIndicator_ExtIEsCls
(
Czt_ExtnS1TNLLoadIndicator_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnS1TNLLoadIndicator_ExtIEsCls(param, val, mBuf)
Czt_ExtnS1TNLLoadIndicator_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnS1TNLLoadIndicator_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnS1TNLLoadIndicator_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_S1TNLLoadIndicator_ExtIEs
*  DESC: Function to Pack CztProtExtnField_S1TNLLoadIndicator_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_S1TNLLoadIndicator_ExtIEs
(
CztProtExtnField_S1TNLLoadIndicator_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_S1TNLLoadIndicator_ExtIEs(param, mBuf)
CztProtExtnField_S1TNLLoadIndicator_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_S1TNLLoadIndicator_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnS1TNLLoadIndicator_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_S1TNLLoadIndicator_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_S1TNLLoadIndicator_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_S1TNLLoadIndicator_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_S1TNLLoadIndicator_ExtIEs
(
CztProtExtnCont_S1TNLLoadIndicator_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_S1TNLLoadIndicator_ExtIEs(param, mBuf)
CztProtExtnCont_S1TNLLoadIndicator_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_S1TNLLoadIndicator_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_S1TNLLoadIndicator_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_S1TNLLoadIndicator_ExtIEs */



/* 
* FUN : cmPkCztS1TNLLoadIndicator
*  DESC: Function to Pack CztS1TNLLoadIndicator structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztS1TNLLoadIndicator
(
CztS1TNLLoadIndicator *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztS1TNLLoadIndicator(param, mBuf)
CztS1TNLLoadIndicator *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztS1TNLLoadIndicator) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_S1TNLLoadIndicator_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztLoadIndicator, &param->uLS1TNLLoadIndicator, mBuf); 
		CMCHKPK(cmPkCztLoadIndicator, &param->dLS1TNLLoadIndicator, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztS1TNLLoadIndicator */



/* 
* FUN : cmPkCzt_ExtnSrvdCell_Inform_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnSrvdCell_Inform_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnSrvdCell_Inform_ExtIEsCls
(
Czt_ExtnSrvdCell_Inform_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnSrvdCell_Inform_ExtIEsCls(param, val, mBuf)
Czt_ExtnSrvdCell_Inform_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnSrvdCell_Inform_ExtIEsCls) 
	
	switch (val)
	{
		case Cztid_Number_of_Antennaports:
			CMCHKPK(cmPkCztNumber_of_Antennaports, &param->u.cztNumber_of_Antennaports, mBuf);
			break;
		case Cztid_PRACH_Config:
			CMCHKPK(cmPkCztPRACH_Config, &param->u.cztPRACH_Config, mBuf);
			break;
		case Cztid_MBSFN_Subframe_Info:
			CMCHKPK(cmPkCztMBSFN_Subframe_Infolist, &param->u.cztMBSFN_Subframe_Infolist, mBuf);
			break;
		case Cztid_CSG_Id:
			CMCHKPK(cmPkCztCSG_Id, &param->u.cztCSG_Id, mBuf);
			break;
		case Cztid_MBMS_Service_Area_Lst:
			CMCHKPK(cmPkCztMBMS_Service_Area_Identity_Lst, &param->u.cztMBMS_Service_Area_Identity_Lst, mBuf);
			break;
		case Cztid_MultibandInfoLst:
			CMCHKPK(cmPkCztMultibandInfoLst, &param->u.cztMultibandInfoLst, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ExtnSrvdCell_Inform_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_SrvdCell_Inform_ExtIEs
*  DESC: Function to Pack CztProtExtnField_SrvdCell_Inform_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_SrvdCell_Inform_ExtIEs
(
CztProtExtnField_SrvdCell_Inform_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_SrvdCell_Inform_ExtIEs(param, mBuf)
CztProtExtnField_SrvdCell_Inform_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_SrvdCell_Inform_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnSrvdCell_Inform_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_SrvdCell_Inform_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_SrvdCell_Inform_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_SrvdCell_Inform_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_SrvdCell_Inform_ExtIEs
(
CztProtExtnCont_SrvdCell_Inform_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_SrvdCell_Inform_ExtIEs(param, mBuf)
CztProtExtnCont_SrvdCell_Inform_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_SrvdCell_Inform_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_SrvdCell_Inform_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_SrvdCell_Inform_ExtIEs */



/* 
* FUN : cmPkCztSrvdCell_Inform
*  DESC: Function to Pack CztSrvdCell_Inform structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztSrvdCell_Inform
(
CztSrvdCell_Inform *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztSrvdCell_Inform(param, mBuf)
CztSrvdCell_Inform *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztSrvdCell_Inform) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_SrvdCell_Inform_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztEUTRA_Mode_Info, &param->eUTRA_Mode_Info, mBuf); 
		CMCHKPK(cmPkCztBroadcastPLMNs_Item, &param->broadcastPLMNs, mBuf); 
		CMCHKPK(cmPkCztTAC, &param->tAC, mBuf); 
		CMCHKPK(cmPkCztECGI, &param->cellId, mBuf); 
		CMCHKPK(cmPkCztPCI, &param->pCI, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztSrvdCell_Inform */



/* 
* FUN : cmPkCzt_ExtnSrvdCell_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnSrvdCell_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnSrvdCell_ExtIEsCls
(
Czt_ExtnSrvdCell_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnSrvdCell_ExtIEsCls(param, val, mBuf)
Czt_ExtnSrvdCell_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnSrvdCell_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnSrvdCell_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_SrvdCell_ExtIEs
*  DESC: Function to Pack CztProtExtnField_SrvdCell_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_SrvdCell_ExtIEs
(
CztProtExtnField_SrvdCell_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_SrvdCell_ExtIEs(param, mBuf)
CztProtExtnField_SrvdCell_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_SrvdCell_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnSrvdCell_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_SrvdCell_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_SrvdCell_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_SrvdCell_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_SrvdCell_ExtIEs
(
CztProtExtnCont_SrvdCell_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_SrvdCell_ExtIEs(param, mBuf)
CztProtExtnCont_SrvdCell_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_SrvdCell_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_SrvdCell_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_SrvdCell_ExtIEs */



/* 
* FUN : cmPkCztSrvdCellsMember
*  DESC: Function to Pack CztSrvdCellsMember structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztSrvdCellsMember
(
CztSrvdCellsMember *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztSrvdCellsMember(param, mBuf)
CztSrvdCellsMember *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztSrvdCellsMember) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_SrvdCell_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztNeighbour_Inform, &param->neighbour_Info, mBuf); 
		CMCHKPK(cmPkCztSrvdCell_Inform, &param->servedCellInfo, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztSrvdCellsMember */



/* 
* FUN : cmPkCztSrvdCells
*  DESC: Function to Pack CztSrvdCells structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztSrvdCells
(
CztSrvdCells *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztSrvdCells(param, mBuf)
CztSrvdCells *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztSrvdCells) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztSrvdCellsMember, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztSrvdCells */

#define cmPkCztShortMAC_I cmPkTknBStr32 
#define cmPkCztSRVCCOperationPossible cmPkTknU32
#define cmPkCztSubscriberProfileIDforRFP cmPkTknU32 
#define cmPkCztTgetCellInUTRAN cmPkTknStrOSXL 
#define cmPkCztTgeteNBtoSrc_eNBTprntCont cmPkTknStrOSXL 
#define cmPkCztTimeToWait cmPkTknU32
#define cmPkCztTraceDepth cmPkTknU32
#define cmPkCztTraceCollectionEntityIPAddr cmPkTknStrBSXL 


/* 
* FUN : cmPkCzt_ExtnTraceActvn_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnTraceActvn_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnTraceActvn_ExtIEsCls
(
Czt_ExtnTraceActvn_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnTraceActvn_ExtIEsCls(param, val, mBuf)
Czt_ExtnTraceActvn_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnTraceActvn_ExtIEsCls) 
	
	switch (val)
	{
		case Cztid_MDTConfig:
			CMCHKPK(cmPkCztMDT_Config, &param->u.cztMDT_Config, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ExtnTraceActvn_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_TraceActvn_ExtIEs
*  DESC: Function to Pack CztProtExtnField_TraceActvn_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_TraceActvn_ExtIEs
(
CztProtExtnField_TraceActvn_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_TraceActvn_ExtIEs(param, mBuf)
CztProtExtnField_TraceActvn_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_TraceActvn_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnTraceActvn_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_TraceActvn_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_TraceActvn_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_TraceActvn_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_TraceActvn_ExtIEs
(
CztProtExtnCont_TraceActvn_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_TraceActvn_ExtIEs(param, mBuf)
CztProtExtnCont_TraceActvn_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_TraceActvn_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_TraceActvn_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_TraceActvn_ExtIEs */



/* 
* FUN : cmPkCztTraceActvn
*  DESC: Function to Pack CztTraceActvn structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztTraceActvn
(
CztTraceActvn *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztTraceActvn(param, mBuf)
CztTraceActvn *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztTraceActvn) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_TraceActvn_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztTraceCollectionEntityIPAddr, &param->traceCollectionEntityIPAddr, mBuf); 
		CMCHKPK(cmPkCztTraceDepth, &param->traceDepth, mBuf); 
		CMCHKPK(cmPkCztIntfsToTrace, &param->interfacesToTrace, mBuf); 
		CMCHKPK(cmPkCztEUTRANTraceID, &param->eUTRANTraceID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztTraceActvn */



/* 
* FUN : cmPkCztUE_HistoryInform
*  DESC: Function to Pack CztUE_HistoryInform structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztUE_HistoryInform
(
CztUE_HistoryInform *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztUE_HistoryInform(param, mBuf)
CztUE_HistoryInform *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztUE_HistoryInform) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztLastVisitedCell_Item, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztUE_HistoryInform */

#define cmPkCztUE_S1AP_ID cmPkTknU32 
#define cmPkCztUE_X2AP_ID cmPkTknU32 


/* 
* FUN : cmPkCzt_ExtnUEAgg_MaxBitrate_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnUEAgg_MaxBitrate_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnUEAgg_MaxBitrate_ExtIEsCls
(
Czt_ExtnUEAgg_MaxBitrate_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnUEAgg_MaxBitrate_ExtIEsCls(param, val, mBuf)
Czt_ExtnUEAgg_MaxBitrate_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnUEAgg_MaxBitrate_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnUEAgg_MaxBitrate_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_UEAgg_MaxBitrate_ExtIEs
*  DESC: Function to Pack CztProtExtnField_UEAgg_MaxBitrate_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_UEAgg_MaxBitrate_ExtIEs
(
CztProtExtnField_UEAgg_MaxBitrate_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_UEAgg_MaxBitrate_ExtIEs(param, mBuf)
CztProtExtnField_UEAgg_MaxBitrate_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_UEAgg_MaxBitrate_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnUEAgg_MaxBitrate_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_UEAgg_MaxBitrate_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_UEAgg_MaxBitrate_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_UEAgg_MaxBitrate_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_UEAgg_MaxBitrate_ExtIEs
(
CztProtExtnCont_UEAgg_MaxBitrate_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_UEAgg_MaxBitrate_ExtIEs(param, mBuf)
CztProtExtnCont_UEAgg_MaxBitrate_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_UEAgg_MaxBitrate_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_UEAgg_MaxBitrate_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_UEAgg_MaxBitrate_ExtIEs */



/* 
* FUN : cmPkCztUEAggMaxBitRate
*  DESC: Function to Pack CztUEAggMaxBitRate structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztUEAggMaxBitRate
(
CztUEAggMaxBitRate *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztUEAggMaxBitRate(param, mBuf)
CztUEAggMaxBitRate *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztUEAggMaxBitRate) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_UEAgg_MaxBitrate_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztBitRate, &param->uEaggregateMaxBitRateUlnk, mBuf); 
		CMCHKPK(cmPkCztBitRate, &param->uEaggregateMaxBitRateDlnk, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztUEAggMaxBitRate */



/* 
* FUN : cmPkCzt_ExtnUESecurCapabilities_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnUESecurCapabilities_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnUESecurCapabilities_ExtIEsCls
(
Czt_ExtnUESecurCapabilities_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnUESecurCapabilities_ExtIEsCls(param, val, mBuf)
Czt_ExtnUESecurCapabilities_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnUESecurCapabilities_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnUESecurCapabilities_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_UESecurCapabilities_ExtIEs
*  DESC: Function to Pack CztProtExtnField_UESecurCapabilities_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_UESecurCapabilities_ExtIEs
(
CztProtExtnField_UESecurCapabilities_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_UESecurCapabilities_ExtIEs(param, mBuf)
CztProtExtnField_UESecurCapabilities_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_UESecurCapabilities_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnUESecurCapabilities_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_UESecurCapabilities_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_UESecurCapabilities_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_UESecurCapabilities_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_UESecurCapabilities_ExtIEs
(
CztProtExtnCont_UESecurCapabilities_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_UESecurCapabilities_ExtIEs(param, mBuf)
CztProtExtnCont_UESecurCapabilities_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_UESecurCapabilities_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_UESecurCapabilities_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_UESecurCapabilities_ExtIEs */



/* 
* FUN : cmPkCztUESecurCapabilities
*  DESC: Function to Pack CztUESecurCapabilities structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztUESecurCapabilities
(
CztUESecurCapabilities *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztUESecurCapabilities(param, mBuf)
CztUESecurCapabilities *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztUESecurCapabilities) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_UESecurCapabilities_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztIntegrityProtectionAlgorithms, &param->integrityProtectionAlgorithms, mBuf); 
		CMCHKPK(cmPkCztEncryptionAlgorithms, &param->encryptionAlgorithms, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztUESecurCapabilities */

#define cmPkCztUL_InterferenceOverloadInd_Item cmPkTknU32


/* 
* FUN : cmPkCztUL_InterferenceOverloadInd
*  DESC: Function to Pack CztUL_InterferenceOverloadInd structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztUL_InterferenceOverloadInd
(
CztUL_InterferenceOverloadInd *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztUL_InterferenceOverloadInd(param, mBuf)
CztUL_InterferenceOverloadInd *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztUL_InterferenceOverloadInd) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztUL_InterferenceOverloadInd_Item, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztUL_InterferenceOverloadInd */

#define cmPkCztUL_HighInterferenceInd cmPkTknStrBSXL 


/* 
* FUN : cmPkCzt_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsCls
(
Czt_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsCls(param, val, mBuf)
Czt_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEs
(
CztProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEs(param, mBuf)
CztProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEs
(
CztProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEs(param, mBuf)
CztProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEs */



/* 
* FUN : cmPkCztUL_HighInterferenceIndInfo_Item
*  DESC: Function to Pack CztUL_HighInterferenceIndInfo_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztUL_HighInterferenceIndInfo_Item
(
CztUL_HighInterferenceIndInfo_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztUL_HighInterferenceIndInfo_Item(param, mBuf)
CztUL_HighInterferenceIndInfo_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztUL_HighInterferenceIndInfo_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztUL_HighInterferenceInd, &param->ul_interferenceindication, mBuf); 
		CMCHKPK(cmPkCztECGI, &param->target_Cell_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztUL_HighInterferenceIndInfo_Item */



/* 
* FUN : cmPkCztUL_HighInterferenceIndInfo
*  DESC: Function to Pack CztUL_HighInterferenceIndInfo structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztUL_HighInterferenceIndInfo
(
CztUL_HighInterferenceIndInfo *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztUL_HighInterferenceIndInfo(param, mBuf)
CztUL_HighInterferenceIndInfo *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztUL_HighInterferenceIndInfo) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztUL_HighInterferenceIndInfo_Item, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztUL_HighInterferenceIndInfo */

#define cmPkCztUE_RLF_Report_Cont cmPkTknStrOSXL 


/* 
* FUN : cmPkCzt_ExtnE_RABs_ToBeSetup_ItemExtIEsCls
*  DESC: Function to Pack Czt_ExtnE_RABs_ToBeSetup_ItemExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnE_RABs_ToBeSetup_ItemExtIEsCls
(
Czt_ExtnE_RABs_ToBeSetup_ItemExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnE_RABs_ToBeSetup_ItemExtIEsCls(param, val, mBuf)
Czt_ExtnE_RABs_ToBeSetup_ItemExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnE_RABs_ToBeSetup_ItemExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnE_RABs_ToBeSetup_ItemExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_E_RABs_ToBeSetup_ItemExtIEs
*  DESC: Function to Pack CztProtExtnField_E_RABs_ToBeSetup_ItemExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_E_RABs_ToBeSetup_ItemExtIEs
(
CztProtExtnField_E_RABs_ToBeSetup_ItemExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_E_RABs_ToBeSetup_ItemExtIEs(param, mBuf)
CztProtExtnField_E_RABs_ToBeSetup_ItemExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_E_RABs_ToBeSetup_ItemExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnE_RABs_ToBeSetup_ItemExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_E_RABs_ToBeSetup_ItemExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_E_RABs_ToBeSetup_ItemExtIEs
*  DESC: Function to Pack CztProtExtnCont_E_RABs_ToBeSetup_ItemExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_E_RABs_ToBeSetup_ItemExtIEs
(
CztProtExtnCont_E_RABs_ToBeSetup_ItemExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_E_RABs_ToBeSetup_ItemExtIEs(param, mBuf)
CztProtExtnCont_E_RABs_ToBeSetup_ItemExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_E_RABs_ToBeSetup_ItemExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_E_RABs_ToBeSetup_ItemExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_E_RABs_ToBeSetup_ItemExtIEs */



/* 
* FUN : cmPkCztE_RABs_ToBeSetup_Item
*  DESC: Function to Pack CztE_RABs_ToBeSetup_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztE_RABs_ToBeSetup_Item
(
CztE_RABs_ToBeSetup_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztE_RABs_ToBeSetup_Item(param, mBuf)
CztE_RABs_ToBeSetup_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztE_RABs_ToBeSetup_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_E_RABs_ToBeSetup_ItemExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztGTPtunnelEndpoint, &param->uL_GTPtunnelEndpoint, mBuf); 
		CMCHKPK(cmPkCztDL_Fwding, &param->dL_Fwding, mBuf); 
		CMCHKPK(cmPkCztE_RAB_Lvl_QoS_Params, &param->e_RAB_Lvl_QoS_Params, mBuf); 
		CMCHKPK(cmPkCztE_RAB_ID, &param->e_RAB_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztE_RABs_ToBeSetup_Item */



/* 
* FUN : cmPkCzt_ValueE_RABs_ToBeSetup_ItemIEsCls
*  DESC: Function to Pack Czt_ValueE_RABs_ToBeSetup_ItemIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueE_RABs_ToBeSetup_ItemIEsCls
(
Czt_ValueE_RABs_ToBeSetup_ItemIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueE_RABs_ToBeSetup_ItemIEsCls(param, val, mBuf)
Czt_ValueE_RABs_ToBeSetup_ItemIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueE_RABs_ToBeSetup_ItemIEsCls) 
	
	switch (val)
	{
		case Cztid_E_RABs_ToBeSetup_Item:
			CMCHKPK(cmPkCztE_RABs_ToBeSetup_Item, &param->u.cztE_RABs_ToBeSetup_Item, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueE_RABs_ToBeSetup_ItemIEsCls */



/* 
* FUN : cmPkCztProtIE_Field_E_RABs_ToBeSetup_ItemIEs
*  DESC: Function to Pack CztProtIE_Field_E_RABs_ToBeSetup_ItemIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_E_RABs_ToBeSetup_ItemIEs
(
CztProtIE_Field_E_RABs_ToBeSetup_ItemIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_E_RABs_ToBeSetup_ItemIEs(param, mBuf)
CztProtIE_Field_E_RABs_ToBeSetup_ItemIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_E_RABs_ToBeSetup_ItemIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueE_RABs_ToBeSetup_ItemIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_E_RABs_ToBeSetup_ItemIEs */

/* Element ------------- ProtocolIE-Single-Container ------------ */
#define cmPkCztProtIE_Single_Cont_E_RABs_ToBeSetup_ItemIEs cmPkCztProtIE_Field_E_RABs_ToBeSetup_ItemIEs


/* 
* FUN : cmPkCztE_RABs_ToBeSetup_Lst
*  DESC: Function to Pack CztE_RABs_ToBeSetup_Lst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztE_RABs_ToBeSetup_Lst
(
CztE_RABs_ToBeSetup_Lst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztE_RABs_ToBeSetup_Lst(param, mBuf)
CztE_RABs_ToBeSetup_Lst *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztE_RABs_ToBeSetup_Lst) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Single_Cont_E_RABs_ToBeSetup_ItemIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztE_RABs_ToBeSetup_Lst */



/* 
* FUN : cmPkCzt_ExtnUE_CntxtInform_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnUE_CntxtInform_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnUE_CntxtInform_ExtIEsCls
(
Czt_ExtnUE_CntxtInform_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnUE_CntxtInform_ExtIEsCls(param, val, mBuf)
Czt_ExtnUE_CntxtInform_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnUE_CntxtInform_ExtIEsCls) 
	
	switch (val)
	{
		case Cztid_ManagementBasedMDTallowed:
			CMCHKPK(cmPkCztManagementBasedMDTallowed, &param->u.cztManagementBasedMDTallowed, mBuf);
			break;
		case Cztid_ManagementBasedMDTPLMNLst:
			CMCHKPK(cmPkCztMDTPLMNLst, &param->u.cztMDTPLMNLst, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ExtnUE_CntxtInform_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_UE_CntxtInform_ExtIEs
*  DESC: Function to Pack CztProtExtnField_UE_CntxtInform_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_UE_CntxtInform_ExtIEs
(
CztProtExtnField_UE_CntxtInform_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_UE_CntxtInform_ExtIEs(param, mBuf)
CztProtExtnField_UE_CntxtInform_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_UE_CntxtInform_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnUE_CntxtInform_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_UE_CntxtInform_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_UE_CntxtInform_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_UE_CntxtInform_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_UE_CntxtInform_ExtIEs
(
CztProtExtnCont_UE_CntxtInform_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_UE_CntxtInform_ExtIEs(param, mBuf)
CztProtExtnCont_UE_CntxtInform_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_UE_CntxtInform_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_UE_CntxtInform_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_UE_CntxtInform_ExtIEs */



/* 
* FUN : cmPkCztUE_CntxtInform
*  DESC: Function to Pack CztUE_CntxtInform structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztUE_CntxtInform
(
CztUE_CntxtInform *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztUE_CntxtInform(param, mBuf)
CztUE_CntxtInform *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztUE_CntxtInform) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_UE_CntxtInform_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztLocRprtngInform, &param->locationRprtngInform, mBuf); 
		CMCHKPK(cmPkCztHovrRestrnLst, &param->handoverRestrnLst, mBuf); 
		CMCHKPK(cmPkCztRRC_Cntxt, &param->rRC_Cntxt, mBuf); 
		CMCHKPK(cmPkCztE_RABs_ToBeSetup_Lst, &param->e_RABs_ToBeSetup_Lst, mBuf); 
		CMCHKPK(cmPkCztSubscriberProfileIDforRFP, &param->subscriberProfileIDforRFP, mBuf); 
		CMCHKPK(cmPkCztUEAggMaxBitRate, &param->uEaggregateMaxBitRate, mBuf); 
		CMCHKPK(cmPkCztAS_SecurInform, &param->aS_SecurInform, mBuf); 
		CMCHKPK(cmPkCztUESecurCapabilities, &param->uESecurCapabilities, mBuf); 
		CMCHKPK(cmPkCztUE_S1AP_ID, &param->mME_UE_S1AP_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztUE_CntxtInform */

#define cmPkCztMobilityInform cmPkTknBStr32 


/* 
* FUN : cmPkCzt_ValueHovrRqst_IEsCls
*  DESC: Function to Pack Czt_ValueHovrRqst_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueHovrRqst_IEsCls
(
Czt_ValueHovrRqst_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueHovrRqst_IEsCls(param, val, mBuf)
Czt_ValueHovrRqst_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueHovrRqst_IEsCls) 
	
	switch (val)
	{
		case Cztid_Old_eNB_UE_X2AP_ID:
			CMCHKPK(cmPkCztUE_X2AP_ID, &param->u.cztUE_X2AP_ID, mBuf);
			break;
		case Cztid_Cause:
			CMCHKPK(cmPkCztCause, &param->u.cztCause, mBuf);
			break;
		case Cztid_TgetCell_ID:
			CMCHKPK(cmPkCztECGI, &param->u.cztECGI, mBuf);
			break;
		case Cztid_GUMMEI_ID:
			CMCHKPK(cmPkCztGUMMEI, &param->u.cztGUMMEI, mBuf);
			break;
		case Cztid_UE_CntxtInform:
			CMCHKPK(cmPkCztUE_CntxtInform, &param->u.cztUE_CntxtInform, mBuf);
			break;
		case Cztid_UE_HistoryInform:
			CMCHKPK(cmPkCztUE_HistoryInform, &param->u.cztUE_HistoryInform, mBuf);
			break;
		case Cztid_TraceActvn:
			CMCHKPK(cmPkCztTraceActvn, &param->u.cztTraceActvn, mBuf);
			break;
		case Cztid_SRVCCOperationPossible:
			CMCHKPK(cmPkCztSRVCCOperationPossible, &param->u.cztSRVCCOperationPossible, mBuf);
			break;
		case Cztid_CSGMembershipStatus:
			CMCHKPK(cmPkCztCSGMembershipStatus, &param->u.cztCSGMembershipStatus, mBuf);
			break;
		case Cztid_MobilityInform:
			CMCHKPK(cmPkCztMobilityInform, &param->u.cztMobilityInform, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueHovrRqst_IEsCls */



/* 
* FUN : cmPkCztProtIE_Field_HovrRqst_IEs
*  DESC: Function to Pack CztProtIE_Field_HovrRqst_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_HovrRqst_IEs
(
CztProtIE_Field_HovrRqst_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_HovrRqst_IEs(param, mBuf)
CztProtIE_Field_HovrRqst_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_HovrRqst_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueHovrRqst_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_HovrRqst_IEs */



/* 
* FUN : cmPkCztProtIE_Cont_HovrRqst_IEs
*  DESC: Function to Pack CztProtIE_Cont_HovrRqst_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Cont_HovrRqst_IEs
(
CztProtIE_Cont_HovrRqst_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Cont_HovrRqst_IEs(param, mBuf)
CztProtIE_Cont_HovrRqst_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtIE_Cont_HovrRqst_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Field_HovrRqst_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Cont_HovrRqst_IEs */



/* 
* FUN : cmPkCztHovrRqst
*  DESC: Function to Pack CztHovrRqst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztHovrRqst
(
CztHovrRqst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztHovrRqst(param, mBuf)
CztHovrRqst *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztHovrRqst) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtIE_Cont_HovrRqst_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztHovrRqst */



/* 
* FUN : cmPkCzt_ExtnE_RABs_Admtd_Item_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnE_RABs_Admtd_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnE_RABs_Admtd_Item_ExtIEsCls
(
Czt_ExtnE_RABs_Admtd_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnE_RABs_Admtd_Item_ExtIEsCls(param, val, mBuf)
Czt_ExtnE_RABs_Admtd_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnE_RABs_Admtd_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnE_RABs_Admtd_Item_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_E_RABs_Admtd_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnField_E_RABs_Admtd_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_E_RABs_Admtd_Item_ExtIEs
(
CztProtExtnField_E_RABs_Admtd_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_E_RABs_Admtd_Item_ExtIEs(param, mBuf)
CztProtExtnField_E_RABs_Admtd_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_E_RABs_Admtd_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnE_RABs_Admtd_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_E_RABs_Admtd_Item_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_E_RABs_Admtd_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_E_RABs_Admtd_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_E_RABs_Admtd_Item_ExtIEs
(
CztProtExtnCont_E_RABs_Admtd_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_E_RABs_Admtd_Item_ExtIEs(param, mBuf)
CztProtExtnCont_E_RABs_Admtd_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_E_RABs_Admtd_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_E_RABs_Admtd_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_E_RABs_Admtd_Item_ExtIEs */



/* 
* FUN : cmPkCztE_RABs_Admtd_Item
*  DESC: Function to Pack CztE_RABs_Admtd_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztE_RABs_Admtd_Item
(
CztE_RABs_Admtd_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztE_RABs_Admtd_Item(param, mBuf)
CztE_RABs_Admtd_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztE_RABs_Admtd_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_E_RABs_Admtd_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztGTPtunnelEndpoint, &param->dL_GTP_TunnelEndpoint, mBuf); 
		CMCHKPK(cmPkCztGTPtunnelEndpoint, &param->uL_GTP_TunnelEndpoint, mBuf); 
		CMCHKPK(cmPkCztE_RAB_ID, &param->e_RAB_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztE_RABs_Admtd_Item */



/* 
* FUN : cmPkCzt_ValueE_RABs_Admtd_ItemIEsCls
*  DESC: Function to Pack Czt_ValueE_RABs_Admtd_ItemIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueE_RABs_Admtd_ItemIEsCls
(
Czt_ValueE_RABs_Admtd_ItemIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueE_RABs_Admtd_ItemIEsCls(param, val, mBuf)
Czt_ValueE_RABs_Admtd_ItemIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueE_RABs_Admtd_ItemIEsCls) 
	
	switch (val)
	{
		case Cztid_E_RABs_Admtd_Item:
			CMCHKPK(cmPkCztE_RABs_Admtd_Item, &param->u.cztE_RABs_Admtd_Item, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueE_RABs_Admtd_ItemIEsCls */



/* 
* FUN : cmPkCztProtIE_Field_E_RABs_Admtd_ItemIEs
*  DESC: Function to Pack CztProtIE_Field_E_RABs_Admtd_ItemIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_E_RABs_Admtd_ItemIEs
(
CztProtIE_Field_E_RABs_Admtd_ItemIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_E_RABs_Admtd_ItemIEs(param, mBuf)
CztProtIE_Field_E_RABs_Admtd_ItemIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_E_RABs_Admtd_ItemIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueE_RABs_Admtd_ItemIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_E_RABs_Admtd_ItemIEs */

/* Element ------------- ProtocolIE-Single-Container ------------ */
#define cmPkCztProtIE_Single_Cont_E_RABs_Admtd_ItemIEs cmPkCztProtIE_Field_E_RABs_Admtd_ItemIEs


/* 
* FUN : cmPkCztE_RABs_Admtd_Lst
*  DESC: Function to Pack CztE_RABs_Admtd_Lst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztE_RABs_Admtd_Lst
(
CztE_RABs_Admtd_Lst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztE_RABs_Admtd_Lst(param, mBuf)
CztE_RABs_Admtd_Lst *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztE_RABs_Admtd_Lst) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Single_Cont_E_RABs_Admtd_ItemIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztE_RABs_Admtd_Lst */



/* 
* FUN : cmPkCzt_ValueHovrRqstAckg_IEsCls
*  DESC: Function to Pack Czt_ValueHovrRqstAckg_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueHovrRqstAckg_IEsCls
(
Czt_ValueHovrRqstAckg_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueHovrRqstAckg_IEsCls(param, val, mBuf)
Czt_ValueHovrRqstAckg_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueHovrRqstAckg_IEsCls) 
	
	switch (val)
	{
		case Cztid_Old_eNB_UE_X2AP_ID:
			CMCHKPK(cmPkCztUE_X2AP_ID, &param->u.cztid_Old_eNB_UE_X2AP_ID, mBuf);
			break;
		case Cztid_New_eNB_UE_X2AP_ID:
			CMCHKPK(cmPkCztUE_X2AP_ID, &param->u.cztid_New_eNB_UE_X2AP_ID, mBuf);
			break;
		case Cztid_E_RABs_Admtd_Lst:
			CMCHKPK(cmPkCztE_RABs_Admtd_Lst, &param->u.cztE_RABs_Admtd_Lst, mBuf);
			break;
		case Cztid_E_RABs_NotAdmtd_Lst:
			CMCHKPK(cmPkCztE_RAB_Lst, &param->u.cztE_RAB_Lst, mBuf);
			break;
		case Cztid_TgeteNBtoSrc_eNBTprntCont:
			CMCHKPK(cmPkCztTgeteNBtoSrc_eNBTprntCont, &param->u.cztTgeteNBtoSrc_eNBTprntCont, mBuf);
			break;
		case Cztid_CriticalityDiag:
			CMCHKPK(cmPkCztCriticalityDiag, &param->u.cztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueHovrRqstAckg_IEsCls */



/* 
* FUN : cmPkCztProtIE_Field_HovrRqstAckg_IEs
*  DESC: Function to Pack CztProtIE_Field_HovrRqstAckg_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_HovrRqstAckg_IEs
(
CztProtIE_Field_HovrRqstAckg_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_HovrRqstAckg_IEs(param, mBuf)
CztProtIE_Field_HovrRqstAckg_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_HovrRqstAckg_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueHovrRqstAckg_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_HovrRqstAckg_IEs */



/* 
* FUN : cmPkCztProtIE_Cont_HovrRqstAckg_IEs
*  DESC: Function to Pack CztProtIE_Cont_HovrRqstAckg_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Cont_HovrRqstAckg_IEs
(
CztProtIE_Cont_HovrRqstAckg_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Cont_HovrRqstAckg_IEs(param, mBuf)
CztProtIE_Cont_HovrRqstAckg_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtIE_Cont_HovrRqstAckg_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Field_HovrRqstAckg_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Cont_HovrRqstAckg_IEs */



/* 
* FUN : cmPkCztHovrRqstAckg
*  DESC: Function to Pack CztHovrRqstAckg structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztHovrRqstAckg
(
CztHovrRqstAckg *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztHovrRqstAckg(param, mBuf)
CztHovrRqstAckg *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztHovrRqstAckg) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtIE_Cont_HovrRqstAckg_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztHovrRqstAckg */



/* 
* FUN : cmPkCzt_ValueHovrPrepFail_IEsCls
*  DESC: Function to Pack Czt_ValueHovrPrepFail_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueHovrPrepFail_IEsCls
(
Czt_ValueHovrPrepFail_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueHovrPrepFail_IEsCls(param, val, mBuf)
Czt_ValueHovrPrepFail_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueHovrPrepFail_IEsCls) 
	
	switch (val)
	{
		case Cztid_Old_eNB_UE_X2AP_ID:
			CMCHKPK(cmPkCztUE_X2AP_ID, &param->u.cztUE_X2AP_ID, mBuf);
			break;
		case Cztid_Cause:
			CMCHKPK(cmPkCztCause, &param->u.cztCause, mBuf);
			break;
		case Cztid_CriticalityDiag:
			CMCHKPK(cmPkCztCriticalityDiag, &param->u.cztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueHovrPrepFail_IEsCls */



/* 
* FUN : cmPkCztProtIE_Field_HovrPrepFail_IEs
*  DESC: Function to Pack CztProtIE_Field_HovrPrepFail_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_HovrPrepFail_IEs
(
CztProtIE_Field_HovrPrepFail_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_HovrPrepFail_IEs(param, mBuf)
CztProtIE_Field_HovrPrepFail_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_HovrPrepFail_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueHovrPrepFail_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_HovrPrepFail_IEs */



/* 
* FUN : cmPkCztProtIE_Cont_HovrPrepFail_IEs
*  DESC: Function to Pack CztProtIE_Cont_HovrPrepFail_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Cont_HovrPrepFail_IEs
(
CztProtIE_Cont_HovrPrepFail_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Cont_HovrPrepFail_IEs(param, mBuf)
CztProtIE_Cont_HovrPrepFail_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtIE_Cont_HovrPrepFail_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Field_HovrPrepFail_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Cont_HovrPrepFail_IEs */



/* 
* FUN : cmPkCztHovrPrepFail
*  DESC: Function to Pack CztHovrPrepFail structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztHovrPrepFail
(
CztHovrPrepFail *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztHovrPrepFail(param, mBuf)
CztHovrPrepFail *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztHovrPrepFail) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtIE_Cont_HovrPrepFail_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztHovrPrepFail */



/* 
* FUN : cmPkCzt_ValueHovrReport_IEsCls
*  DESC: Function to Pack Czt_ValueHovrReport_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueHovrReport_IEsCls
(
Czt_ValueHovrReport_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueHovrReport_IEsCls(param, val, mBuf)
Czt_ValueHovrReport_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueHovrReport_IEsCls) 
	
	switch (val)
	{
		case Cztid_HovrReportTyp:
			CMCHKPK(cmPkCztHovrReportTyp, &param->u.cztHovrReportTyp, mBuf);
			break;
		case Cztid_Cause:
			CMCHKPK(cmPkCztCause, &param->u.cztCause, mBuf);
			break;
		case Cztid_SrcCellECGI:
			CMCHKPK(cmPkCztECGI, &param->u.cztid_SrcCellECGI, mBuf);
			break;
		case Cztid_FailCellECGI:
			CMCHKPK(cmPkCztECGI, &param->u.cztid_FailCellECGI, mBuf);
			break;
		case Cztid_Re_establishmentCellECGI:
			CMCHKPK(cmPkCztECGI, &param->u.cztid_Re_establishmentCellECGI, mBuf);
			break;
		case Cztid_TgetCellInUTRAN:
			CMCHKPK(cmPkCztTgetCellInUTRAN, &param->u.cztTgetCellInUTRAN, mBuf);
			break;
		case Cztid_SrcCellCRNTI:
			CMCHKPK(cmPkCztCRNTI, &param->u.cztCRNTI, mBuf);
			break;
		case Cztid_MobilityInform:
			CMCHKPK(cmPkCztMobilityInform, &param->u.cztMobilityInform, mBuf);
			break;
		case Cztid_UE_RLF_Report_Cont:
			CMCHKPK(cmPkCztUE_RLF_Report_Cont, &param->u.cztUE_RLF_Report_Cont, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueHovrReport_IEsCls */



/* 
* FUN : cmPkCztProtIE_Field_HovrReport_IEs
*  DESC: Function to Pack CztProtIE_Field_HovrReport_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_HovrReport_IEs
(
CztProtIE_Field_HovrReport_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_HovrReport_IEs(param, mBuf)
CztProtIE_Field_HovrReport_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_HovrReport_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueHovrReport_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_HovrReport_IEs */



/* 
* FUN : cmPkCztProtIE_Cont_HovrReport_IEs
*  DESC: Function to Pack CztProtIE_Cont_HovrReport_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Cont_HovrReport_IEs
(
CztProtIE_Cont_HovrReport_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Cont_HovrReport_IEs(param, mBuf)
CztProtIE_Cont_HovrReport_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtIE_Cont_HovrReport_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Field_HovrReport_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Cont_HovrReport_IEs */



/* 
* FUN : cmPkCztHovrReport
*  DESC: Function to Pack CztHovrReport structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztHovrReport
(
CztHovrReport *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztHovrReport(param, mBuf)
CztHovrReport *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztHovrReport) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtIE_Cont_HovrReport_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztHovrReport */



/* 
* FUN : cmPkCzt_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsCls
*  DESC: Function to Pack Czt_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsCls
(
Czt_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsCls(param, val, mBuf)
Czt_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsCls) 
	
	switch (val)
	{
		case Cztid_ReceiveStatusOfULPDCPSDUsExtended:
			CMCHKPK(cmPkCztReceiveStatusOfULPDCPSDUsExtended, &param->u.cztReceiveStatusOfULPDCPSDUsExtended, mBuf);
			break;
		case Cztid_ULCOUNTValueExtended:
			CMCHKPK(cmPkCztCOUNTValueExtended, &param->u.cztid_ULCOUNTValueExtended, mBuf);
			break;
		case Cztid_DLCOUNTValueExtended:
			CMCHKPK(cmPkCztCOUNTValueExtended, &param->u.cztid_DLCOUNTValueExtended, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEs
*  DESC: Function to Pack CztProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEs
(
CztProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEs(param, mBuf)
CztProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEs
*  DESC: Function to Pack CztProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEs
(
CztProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEs(param, mBuf)
CztProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEs */



/* 
* FUN : cmPkCztE_RABs_SubjToStatusTfr_Item
*  DESC: Function to Pack CztE_RABs_SubjToStatusTfr_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztE_RABs_SubjToStatusTfr_Item
(
CztE_RABs_SubjToStatusTfr_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztE_RABs_SubjToStatusTfr_Item(param, mBuf)
CztE_RABs_SubjToStatusTfr_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztE_RABs_SubjToStatusTfr_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztCOUNTvalue, &param->dL_COUNTvalue, mBuf); 
		CMCHKPK(cmPkCztCOUNTvalue, &param->uL_COUNTvalue, mBuf); 
		CMCHKPK(cmPkCztReceiveStatusofULPDCPSDUs, &param->receiveStatusofULPDCPSDUs, mBuf); 
		CMCHKPK(cmPkCztE_RAB_ID, &param->e_RAB_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztE_RABs_SubjToStatusTfr_Item */



/* 
* FUN : cmPkCzt_ValueE_RABs_SubjToStatusTfr_ItemIEsCls
*  DESC: Function to Pack Czt_ValueE_RABs_SubjToStatusTfr_ItemIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueE_RABs_SubjToStatusTfr_ItemIEsCls
(
Czt_ValueE_RABs_SubjToStatusTfr_ItemIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueE_RABs_SubjToStatusTfr_ItemIEsCls(param, val, mBuf)
Czt_ValueE_RABs_SubjToStatusTfr_ItemIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueE_RABs_SubjToStatusTfr_ItemIEsCls) 
	
	switch (val)
	{
		case Cztid_E_RABs_SubjToStatusTfr_Item:
			CMCHKPK(cmPkCztE_RABs_SubjToStatusTfr_Item, &param->u.cztE_RABs_SubjToStatusTfr_Item, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueE_RABs_SubjToStatusTfr_ItemIEsCls */



/* 
* FUN : cmPkCztProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEs
*  DESC: Function to Pack CztProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEs
(
CztProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEs(param, mBuf)
CztProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueE_RABs_SubjToStatusTfr_ItemIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEs */

/* Element ------------- ProtocolIE-Single-Container ------------ */
#define cmPkCztProtIE_Single_Cont_E_RABs_SubjToStatusTfr_ItemIEs cmPkCztProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEs


/* 
* FUN : cmPkCztE_RABs_SubjToStatusTfr_Lst
*  DESC: Function to Pack CztE_RABs_SubjToStatusTfr_Lst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztE_RABs_SubjToStatusTfr_Lst
(
CztE_RABs_SubjToStatusTfr_Lst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztE_RABs_SubjToStatusTfr_Lst(param, mBuf)
CztE_RABs_SubjToStatusTfr_Lst *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztE_RABs_SubjToStatusTfr_Lst) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Single_Cont_E_RABs_SubjToStatusTfr_ItemIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztE_RABs_SubjToStatusTfr_Lst */



/* 
* FUN : cmPkCzt_ValueSNStatusTfr_IEsCls
*  DESC: Function to Pack Czt_ValueSNStatusTfr_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueSNStatusTfr_IEsCls
(
Czt_ValueSNStatusTfr_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueSNStatusTfr_IEsCls(param, val, mBuf)
Czt_ValueSNStatusTfr_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueSNStatusTfr_IEsCls) 
	
	switch (val)
	{
		case Cztid_Old_eNB_UE_X2AP_ID:
			CMCHKPK(cmPkCztUE_X2AP_ID, &param->u.cztid_Old_eNB_UE_X2AP_ID, mBuf);
			break;
		case Cztid_New_eNB_UE_X2AP_ID:
			CMCHKPK(cmPkCztUE_X2AP_ID, &param->u.cztid_New_eNB_UE_X2AP_ID, mBuf);
			break;
		case Cztid_E_RABs_SubjToStatusTfr_Lst:
			CMCHKPK(cmPkCztE_RABs_SubjToStatusTfr_Lst, &param->u.cztE_RABs_SubjToStatusTfr_Lst, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueSNStatusTfr_IEsCls */



/* 
* FUN : cmPkCztProtIE_Field_SNStatusTfr_IEs
*  DESC: Function to Pack CztProtIE_Field_SNStatusTfr_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_SNStatusTfr_IEs
(
CztProtIE_Field_SNStatusTfr_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_SNStatusTfr_IEs(param, mBuf)
CztProtIE_Field_SNStatusTfr_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_SNStatusTfr_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueSNStatusTfr_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_SNStatusTfr_IEs */



/* 
* FUN : cmPkCztProtIE_Cont_SNStatusTfr_IEs
*  DESC: Function to Pack CztProtIE_Cont_SNStatusTfr_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Cont_SNStatusTfr_IEs
(
CztProtIE_Cont_SNStatusTfr_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Cont_SNStatusTfr_IEs(param, mBuf)
CztProtIE_Cont_SNStatusTfr_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtIE_Cont_SNStatusTfr_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Field_SNStatusTfr_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Cont_SNStatusTfr_IEs */



/* 
* FUN : cmPkCztSNStatusTfr
*  DESC: Function to Pack CztSNStatusTfr structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztSNStatusTfr
(
CztSNStatusTfr *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztSNStatusTfr(param, mBuf)
CztSNStatusTfr *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztSNStatusTfr) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtIE_Cont_SNStatusTfr_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztSNStatusTfr */



/* 
* FUN : cmPkCzt_ValueUECntxtRls_IEsCls
*  DESC: Function to Pack Czt_ValueUECntxtRls_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueUECntxtRls_IEsCls
(
Czt_ValueUECntxtRls_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueUECntxtRls_IEsCls(param, val, mBuf)
Czt_ValueUECntxtRls_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueUECntxtRls_IEsCls) 
	
	switch (val)
	{
		case Cztid_Old_eNB_UE_X2AP_ID:
			CMCHKPK(cmPkCztUE_X2AP_ID, &param->u.cztid_Old_eNB_UE_X2AP_ID, mBuf);
			break;
		case Cztid_New_eNB_UE_X2AP_ID:
			CMCHKPK(cmPkCztUE_X2AP_ID, &param->u.cztid_New_eNB_UE_X2AP_ID, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueUECntxtRls_IEsCls */



/* 
* FUN : cmPkCztProtIE_Field_UECntxtRls_IEs
*  DESC: Function to Pack CztProtIE_Field_UECntxtRls_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_UECntxtRls_IEs
(
CztProtIE_Field_UECntxtRls_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_UECntxtRls_IEs(param, mBuf)
CztProtIE_Field_UECntxtRls_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_UECntxtRls_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueUECntxtRls_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_UECntxtRls_IEs */



/* 
* FUN : cmPkCztProtIE_Cont_UECntxtRls_IEs
*  DESC: Function to Pack CztProtIE_Cont_UECntxtRls_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Cont_UECntxtRls_IEs
(
CztProtIE_Cont_UECntxtRls_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Cont_UECntxtRls_IEs(param, mBuf)
CztProtIE_Cont_UECntxtRls_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtIE_Cont_UECntxtRls_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Field_UECntxtRls_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Cont_UECntxtRls_IEs */



/* 
* FUN : cmPkCztUECntxtRls
*  DESC: Function to Pack CztUECntxtRls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztUECntxtRls
(
CztUECntxtRls *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztUECntxtRls(param, mBuf)
CztUECntxtRls *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztUECntxtRls) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtIE_Cont_UECntxtRls_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztUECntxtRls */



/* 
* FUN : cmPkCzt_ValueHovrCancel_IEsCls
*  DESC: Function to Pack Czt_ValueHovrCancel_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueHovrCancel_IEsCls
(
Czt_ValueHovrCancel_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueHovrCancel_IEsCls(param, val, mBuf)
Czt_ValueHovrCancel_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueHovrCancel_IEsCls) 
	
	switch (val)
	{
		case Cztid_Old_eNB_UE_X2AP_ID:
			CMCHKPK(cmPkCztUE_X2AP_ID, &param->u.cztid_Old_eNB_UE_X2AP_ID, mBuf);
			break;
		case Cztid_New_eNB_UE_X2AP_ID:
			CMCHKPK(cmPkCztUE_X2AP_ID, &param->u.cztid_New_eNB_UE_X2AP_ID, mBuf);
			break;
		case Cztid_Cause:
			CMCHKPK(cmPkCztCause, &param->u.cztCause, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueHovrCancel_IEsCls */



/* 
* FUN : cmPkCztProtIE_Field_HovrCancel_IEs
*  DESC: Function to Pack CztProtIE_Field_HovrCancel_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_HovrCancel_IEs
(
CztProtIE_Field_HovrCancel_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_HovrCancel_IEs(param, mBuf)
CztProtIE_Field_HovrCancel_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_HovrCancel_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueHovrCancel_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_HovrCancel_IEs */



/* 
* FUN : cmPkCztProtIE_Cont_HovrCancel_IEs
*  DESC: Function to Pack CztProtIE_Cont_HovrCancel_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Cont_HovrCancel_IEs
(
CztProtIE_Cont_HovrCancel_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Cont_HovrCancel_IEs(param, mBuf)
CztProtIE_Cont_HovrCancel_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtIE_Cont_HovrCancel_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Field_HovrCancel_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Cont_HovrCancel_IEs */



/* 
* FUN : cmPkCztHovrCancel
*  DESC: Function to Pack CztHovrCancel structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztHovrCancel
(
CztHovrCancel *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztHovrCancel(param, mBuf)
CztHovrCancel *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztHovrCancel) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtIE_Cont_HovrCancel_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztHovrCancel */



/* 
* FUN : cmPkCzt_ValueErrInd_IEsCls
*  DESC: Function to Pack Czt_ValueErrInd_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueErrInd_IEsCls
(
Czt_ValueErrInd_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueErrInd_IEsCls(param, val, mBuf)
Czt_ValueErrInd_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueErrInd_IEsCls) 
	
	switch (val)
	{
		case Cztid_Old_eNB_UE_X2AP_ID:
			CMCHKPK(cmPkCztUE_X2AP_ID, &param->u.cztid_Old_eNB_UE_X2AP_ID, mBuf);
			break;
		case Cztid_New_eNB_UE_X2AP_ID:
			CMCHKPK(cmPkCztUE_X2AP_ID, &param->u.cztid_New_eNB_UE_X2AP_ID, mBuf);
			break;
		case Cztid_Cause:
			CMCHKPK(cmPkCztCause, &param->u.cztCause, mBuf);
			break;
		case Cztid_CriticalityDiag:
			CMCHKPK(cmPkCztCriticalityDiag, &param->u.cztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueErrInd_IEsCls */



/* 
* FUN : cmPkCztProtIE_Field_ErrInd_IEs
*  DESC: Function to Pack CztProtIE_Field_ErrInd_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_ErrInd_IEs
(
CztProtIE_Field_ErrInd_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_ErrInd_IEs(param, mBuf)
CztProtIE_Field_ErrInd_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_ErrInd_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueErrInd_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_ErrInd_IEs */



/* 
* FUN : cmPkCztProtIE_Cont_ErrInd_IEs
*  DESC: Function to Pack CztProtIE_Cont_ErrInd_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Cont_ErrInd_IEs
(
CztProtIE_Cont_ErrInd_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Cont_ErrInd_IEs(param, mBuf)
CztProtIE_Cont_ErrInd_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtIE_Cont_ErrInd_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Field_ErrInd_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Cont_ErrInd_IEs */



/* 
* FUN : cmPkCztErrInd
*  DESC: Function to Pack CztErrInd structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztErrInd
(
CztErrInd *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztErrInd(param, mBuf)
CztErrInd *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztErrInd) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtIE_Cont_ErrInd_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztErrInd */



/* 
* FUN : cmPkCzt_ValueResetRqst_IEsCls
*  DESC: Function to Pack Czt_ValueResetRqst_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueResetRqst_IEsCls
(
Czt_ValueResetRqst_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueResetRqst_IEsCls(param, val, mBuf)
Czt_ValueResetRqst_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueResetRqst_IEsCls) 
	
	switch (val)
	{
		case Cztid_Cause:
			CMCHKPK(cmPkCztCause, &param->u.cztCause, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueResetRqst_IEsCls */



/* 
* FUN : cmPkCztProtIE_Field_ResetRqst_IEs
*  DESC: Function to Pack CztProtIE_Field_ResetRqst_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_ResetRqst_IEs
(
CztProtIE_Field_ResetRqst_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_ResetRqst_IEs(param, mBuf)
CztProtIE_Field_ResetRqst_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_ResetRqst_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueResetRqst_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_ResetRqst_IEs */



/* 
* FUN : cmPkCztProtIE_Cont_ResetRqst_IEs
*  DESC: Function to Pack CztProtIE_Cont_ResetRqst_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Cont_ResetRqst_IEs
(
CztProtIE_Cont_ResetRqst_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Cont_ResetRqst_IEs(param, mBuf)
CztProtIE_Cont_ResetRqst_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtIE_Cont_ResetRqst_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Field_ResetRqst_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Cont_ResetRqst_IEs */



/* 
* FUN : cmPkCztResetRqst
*  DESC: Function to Pack CztResetRqst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztResetRqst
(
CztResetRqst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztResetRqst(param, mBuf)
CztResetRqst *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztResetRqst) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtIE_Cont_ResetRqst_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztResetRqst */



/* 
* FUN : cmPkCzt_ValueResetResp_IEsCls
*  DESC: Function to Pack Czt_ValueResetResp_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueResetResp_IEsCls
(
Czt_ValueResetResp_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueResetResp_IEsCls(param, val, mBuf)
Czt_ValueResetResp_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueResetResp_IEsCls) 
	
	switch (val)
	{
		case Cztid_CriticalityDiag:
			CMCHKPK(cmPkCztCriticalityDiag, &param->u.cztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueResetResp_IEsCls */



/* 
* FUN : cmPkCztProtIE_Field_ResetResp_IEs
*  DESC: Function to Pack CztProtIE_Field_ResetResp_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_ResetResp_IEs
(
CztProtIE_Field_ResetResp_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_ResetResp_IEs(param, mBuf)
CztProtIE_Field_ResetResp_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_ResetResp_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueResetResp_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_ResetResp_IEs */



/* 
* FUN : cmPkCztProtIE_Cont_ResetResp_IEs
*  DESC: Function to Pack CztProtIE_Cont_ResetResp_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Cont_ResetResp_IEs
(
CztProtIE_Cont_ResetResp_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Cont_ResetResp_IEs(param, mBuf)
CztProtIE_Cont_ResetResp_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtIE_Cont_ResetResp_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Field_ResetResp_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Cont_ResetResp_IEs */



/* 
* FUN : cmPkCztResetResp
*  DESC: Function to Pack CztResetResp structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztResetResp
(
CztResetResp *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztResetResp(param, mBuf)
CztResetResp *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztResetResp) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtIE_Cont_ResetResp_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztResetResp */



/* 
* FUN : cmPkCzt_ValueX2SetupRqst_IEsCls
*  DESC: Function to Pack Czt_ValueX2SetupRqst_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueX2SetupRqst_IEsCls
(
Czt_ValueX2SetupRqst_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueX2SetupRqst_IEsCls(param, val, mBuf)
Czt_ValueX2SetupRqst_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueX2SetupRqst_IEsCls) 
	
	switch (val)
	{
		case Cztid_GlobalENB_ID:
			CMCHKPK(cmPkCztGlobalENB_ID, &param->u.cztGlobalENB_ID, mBuf);
			break;
		case Cztid_SrvdCells:
			CMCHKPK(cmPkCztSrvdCells, &param->u.cztSrvdCells, mBuf);
			break;
		case Cztid_GUGroupIDLst:
			CMCHKPK(cmPkCztGUGroupIDLst, &param->u.cztGUGroupIDLst, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueX2SetupRqst_IEsCls */



/* 
* FUN : cmPkCztProtIE_Field_X2SetupRqst_IEs
*  DESC: Function to Pack CztProtIE_Field_X2SetupRqst_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_X2SetupRqst_IEs
(
CztProtIE_Field_X2SetupRqst_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_X2SetupRqst_IEs(param, mBuf)
CztProtIE_Field_X2SetupRqst_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_X2SetupRqst_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueX2SetupRqst_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_X2SetupRqst_IEs */



/* 
* FUN : cmPkCztProtIE_Cont_X2SetupRqst_IEs
*  DESC: Function to Pack CztProtIE_Cont_X2SetupRqst_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Cont_X2SetupRqst_IEs
(
CztProtIE_Cont_X2SetupRqst_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Cont_X2SetupRqst_IEs(param, mBuf)
CztProtIE_Cont_X2SetupRqst_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtIE_Cont_X2SetupRqst_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Field_X2SetupRqst_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Cont_X2SetupRqst_IEs */



/* 
* FUN : cmPkCztX2SetupRqst
*  DESC: Function to Pack CztX2SetupRqst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztX2SetupRqst
(
CztX2SetupRqst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztX2SetupRqst(param, mBuf)
CztX2SetupRqst *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztX2SetupRqst) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtIE_Cont_X2SetupRqst_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztX2SetupRqst */



/* 
* FUN : cmPkCzt_ValueX2SetupResp_IEsCls
*  DESC: Function to Pack Czt_ValueX2SetupResp_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueX2SetupResp_IEsCls
(
Czt_ValueX2SetupResp_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueX2SetupResp_IEsCls(param, val, mBuf)
Czt_ValueX2SetupResp_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueX2SetupResp_IEsCls) 
	
	switch (val)
	{
		case Cztid_GlobalENB_ID:
			CMCHKPK(cmPkCztGlobalENB_ID, &param->u.cztGlobalENB_ID, mBuf);
			break;
		case Cztid_SrvdCells:
			CMCHKPK(cmPkCztSrvdCells, &param->u.cztSrvdCells, mBuf);
			break;
		case Cztid_GUGroupIDLst:
			CMCHKPK(cmPkCztGUGroupIDLst, &param->u.cztGUGroupIDLst, mBuf);
			break;
		case Cztid_CriticalityDiag:
			CMCHKPK(cmPkCztCriticalityDiag, &param->u.cztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueX2SetupResp_IEsCls */



/* 
* FUN : cmPkCztProtIE_Field_X2SetupResp_IEs
*  DESC: Function to Pack CztProtIE_Field_X2SetupResp_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_X2SetupResp_IEs
(
CztProtIE_Field_X2SetupResp_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_X2SetupResp_IEs(param, mBuf)
CztProtIE_Field_X2SetupResp_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_X2SetupResp_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueX2SetupResp_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_X2SetupResp_IEs */



/* 
* FUN : cmPkCztProtIE_Cont_X2SetupResp_IEs
*  DESC: Function to Pack CztProtIE_Cont_X2SetupResp_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Cont_X2SetupResp_IEs
(
CztProtIE_Cont_X2SetupResp_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Cont_X2SetupResp_IEs(param, mBuf)
CztProtIE_Cont_X2SetupResp_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtIE_Cont_X2SetupResp_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Field_X2SetupResp_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Cont_X2SetupResp_IEs */



/* 
* FUN : cmPkCztX2SetupResp
*  DESC: Function to Pack CztX2SetupResp structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztX2SetupResp
(
CztX2SetupResp *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztX2SetupResp(param, mBuf)
CztX2SetupResp *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztX2SetupResp) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtIE_Cont_X2SetupResp_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztX2SetupResp */



/* 
* FUN : cmPkCzt_ValueX2SetupFail_IEsCls
*  DESC: Function to Pack Czt_ValueX2SetupFail_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueX2SetupFail_IEsCls
(
Czt_ValueX2SetupFail_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueX2SetupFail_IEsCls(param, val, mBuf)
Czt_ValueX2SetupFail_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueX2SetupFail_IEsCls) 
	
	switch (val)
	{
		case Cztid_Cause:
			CMCHKPK(cmPkCztCause, &param->u.cztCause, mBuf);
			break;
		case Cztid_TimeToWait:
			CMCHKPK(cmPkCztTimeToWait, &param->u.cztTimeToWait, mBuf);
			break;
		case Cztid_CriticalityDiag:
			CMCHKPK(cmPkCztCriticalityDiag, &param->u.cztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueX2SetupFail_IEsCls */



/* 
* FUN : cmPkCztProtIE_Field_X2SetupFail_IEs
*  DESC: Function to Pack CztProtIE_Field_X2SetupFail_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_X2SetupFail_IEs
(
CztProtIE_Field_X2SetupFail_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_X2SetupFail_IEs(param, mBuf)
CztProtIE_Field_X2SetupFail_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_X2SetupFail_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueX2SetupFail_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_X2SetupFail_IEs */



/* 
* FUN : cmPkCztProtIE_Cont_X2SetupFail_IEs
*  DESC: Function to Pack CztProtIE_Cont_X2SetupFail_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Cont_X2SetupFail_IEs
(
CztProtIE_Cont_X2SetupFail_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Cont_X2SetupFail_IEs(param, mBuf)
CztProtIE_Cont_X2SetupFail_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtIE_Cont_X2SetupFail_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Field_X2SetupFail_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Cont_X2SetupFail_IEs */



/* 
* FUN : cmPkCztX2SetupFail
*  DESC: Function to Pack CztX2SetupFail structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztX2SetupFail
(
CztX2SetupFail *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztX2SetupFail(param, mBuf)
CztX2SetupFail *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztX2SetupFail) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtIE_Cont_X2SetupFail_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztX2SetupFail */



/* 
* FUN : cmPkCzt_ExtnCellInform_Item_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnCellInform_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnCellInform_Item_ExtIEsCls
(
Czt_ExtnCellInform_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnCellInform_Item_ExtIEsCls(param, val, mBuf)
Czt_ExtnCellInform_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnCellInform_Item_ExtIEsCls) 
	
	switch (val)
	{
		case Cztid_ABSInform:
			CMCHKPK(cmPkCztABSInform, &param->u.cztABSInform, mBuf);
			break;
		case Cztid_InvokeInd:
			CMCHKPK(cmPkCztInvokeInd, &param->u.cztInvokeInd, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ExtnCellInform_Item_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_CellInform_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnField_CellInform_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_CellInform_Item_ExtIEs
(
CztProtExtnField_CellInform_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_CellInform_Item_ExtIEs(param, mBuf)
CztProtExtnField_CellInform_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_CellInform_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnCellInform_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_CellInform_Item_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_CellInform_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_CellInform_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_CellInform_Item_ExtIEs
(
CztProtExtnCont_CellInform_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_CellInform_Item_ExtIEs(param, mBuf)
CztProtExtnCont_CellInform_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_CellInform_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_CellInform_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_CellInform_Item_ExtIEs */



/* 
* FUN : cmPkCztCellInform_Item
*  DESC: Function to Pack CztCellInform_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztCellInform_Item
(
CztCellInform_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztCellInform_Item(param, mBuf)
CztCellInform_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztCellInform_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_CellInform_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztRelativeNarrowbandTxPower, &param->relativeNarrowbandTxPower, mBuf); 
		CMCHKPK(cmPkCztUL_HighInterferenceIndInfo, &param->ul_HighInterferenceIndInfo, mBuf); 
		CMCHKPK(cmPkCztUL_InterferenceOverloadInd, &param->ul_InterferenceOverloadInd, mBuf); 
		CMCHKPK(cmPkCztECGI, &param->cell_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztCellInform_Item */



/* 
* FUN : cmPkCzt_ValueCellInform_ItemIEsCls
*  DESC: Function to Pack Czt_ValueCellInform_ItemIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueCellInform_ItemIEsCls
(
Czt_ValueCellInform_ItemIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueCellInform_ItemIEsCls(param, val, mBuf)
Czt_ValueCellInform_ItemIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueCellInform_ItemIEsCls) 
	
	switch (val)
	{
		case Cztid_CellInform_Item:
			CMCHKPK(cmPkCztCellInform_Item, &param->u.cztCellInform_Item, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueCellInform_ItemIEsCls */



/* 
* FUN : cmPkCztProtIE_Field_CellInform_ItemIEs
*  DESC: Function to Pack CztProtIE_Field_CellInform_ItemIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_CellInform_ItemIEs
(
CztProtIE_Field_CellInform_ItemIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_CellInform_ItemIEs(param, mBuf)
CztProtIE_Field_CellInform_ItemIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_CellInform_ItemIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueCellInform_ItemIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_CellInform_ItemIEs */

/* Element ------------- ProtocolIE-Single-Container ------------ */
#define cmPkCztProtIE_Single_Cont_CellInform_ItemIEs cmPkCztProtIE_Field_CellInform_ItemIEs


/* 
* FUN : cmPkCztCellInform_Lst
*  DESC: Function to Pack CztCellInform_Lst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztCellInform_Lst
(
CztCellInform_Lst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztCellInform_Lst(param, mBuf)
CztCellInform_Lst *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztCellInform_Lst) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Single_Cont_CellInform_ItemIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztCellInform_Lst */



/* 
* FUN : cmPkCzt_ValueLoadInform_IEsCls
*  DESC: Function to Pack Czt_ValueLoadInform_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueLoadInform_IEsCls
(
Czt_ValueLoadInform_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueLoadInform_IEsCls(param, val, mBuf)
Czt_ValueLoadInform_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueLoadInform_IEsCls) 
	
	switch (val)
	{
		case Cztid_CellInform:
			CMCHKPK(cmPkCztCellInform_Lst, &param->u.cztCellInform_Lst, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueLoadInform_IEsCls */



/* 
* FUN : cmPkCztProtIE_Field_LoadInform_IEs
*  DESC: Function to Pack CztProtIE_Field_LoadInform_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_LoadInform_IEs
(
CztProtIE_Field_LoadInform_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_LoadInform_IEs(param, mBuf)
CztProtIE_Field_LoadInform_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_LoadInform_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueLoadInform_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_LoadInform_IEs */



/* 
* FUN : cmPkCztProtIE_Cont_LoadInform_IEs
*  DESC: Function to Pack CztProtIE_Cont_LoadInform_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Cont_LoadInform_IEs
(
CztProtIE_Cont_LoadInform_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Cont_LoadInform_IEs(param, mBuf)
CztProtIE_Cont_LoadInform_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtIE_Cont_LoadInform_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Field_LoadInform_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Cont_LoadInform_IEs */



/* 
* FUN : cmPkCztLoadInform
*  DESC: Function to Pack CztLoadInform structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztLoadInform
(
CztLoadInform *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztLoadInform(param, mBuf)
CztLoadInform *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztLoadInform) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtIE_Cont_LoadInform_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztLoadInform */



/* 
* FUN : cmPkCzt_ExtnSrvdCellsToMdfy_Item_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnSrvdCellsToMdfy_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnSrvdCellsToMdfy_Item_ExtIEsCls
(
Czt_ExtnSrvdCellsToMdfy_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnSrvdCellsToMdfy_Item_ExtIEsCls(param, val, mBuf)
Czt_ExtnSrvdCellsToMdfy_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnSrvdCellsToMdfy_Item_ExtIEsCls) 
	
	switch (val)
	{
		case Cztid_DeactivationInd:
			CMCHKPK(cmPkCztDeactivationInd, &param->u.cztDeactivationInd, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ExtnSrvdCellsToMdfy_Item_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_SrvdCellsToMdfy_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnField_SrvdCellsToMdfy_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_SrvdCellsToMdfy_Item_ExtIEs
(
CztProtExtnField_SrvdCellsToMdfy_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_SrvdCellsToMdfy_Item_ExtIEs(param, mBuf)
CztProtExtnField_SrvdCellsToMdfy_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_SrvdCellsToMdfy_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnSrvdCellsToMdfy_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_SrvdCellsToMdfy_Item_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_SrvdCellsToMdfy_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_SrvdCellsToMdfy_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_SrvdCellsToMdfy_Item_ExtIEs
(
CztProtExtnCont_SrvdCellsToMdfy_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_SrvdCellsToMdfy_Item_ExtIEs(param, mBuf)
CztProtExtnCont_SrvdCellsToMdfy_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_SrvdCellsToMdfy_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_SrvdCellsToMdfy_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_SrvdCellsToMdfy_Item_ExtIEs */



/* 
* FUN : cmPkCztSrvdCellsToMdfy_Item
*  DESC: Function to Pack CztSrvdCellsToMdfy_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztSrvdCellsToMdfy_Item
(
CztSrvdCellsToMdfy_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztSrvdCellsToMdfy_Item(param, mBuf)
CztSrvdCellsToMdfy_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztSrvdCellsToMdfy_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_SrvdCellsToMdfy_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztNeighbour_Inform, &param->neighbour_Info, mBuf); 
		CMCHKPK(cmPkCztSrvdCell_Inform, &param->servedCellInfo, mBuf); 
		CMCHKPK(cmPkCztECGI, &param->old_ecgi, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztSrvdCellsToMdfy_Item */



/* 
* FUN : cmPkCztSrvdCellsToMdfy
*  DESC: Function to Pack CztSrvdCellsToMdfy structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztSrvdCellsToMdfy
(
CztSrvdCellsToMdfy *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztSrvdCellsToMdfy(param, mBuf)
CztSrvdCellsToMdfy *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztSrvdCellsToMdfy) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztSrvdCellsToMdfy_Item, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztSrvdCellsToMdfy */



/* 
* FUN : cmPkCztOld_ECGIs
*  DESC: Function to Pack CztOld_ECGIs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztOld_ECGIs
(
CztOld_ECGIs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztOld_ECGIs(param, mBuf)
CztOld_ECGIs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztOld_ECGIs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztECGI, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztOld_ECGIs */



/* 
* FUN : cmPkCzt_ValueENBConfigUpd_IEsCls
*  DESC: Function to Pack Czt_ValueENBConfigUpd_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueENBConfigUpd_IEsCls
(
Czt_ValueENBConfigUpd_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueENBConfigUpd_IEsCls(param, val, mBuf)
Czt_ValueENBConfigUpd_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueENBConfigUpd_IEsCls) 
	
	switch (val)
	{
		case Cztid_SrvdCellsToAdd:
			CMCHKPK(cmPkCztSrvdCells, &param->u.cztSrvdCells, mBuf);
			break;
		case Cztid_SrvdCellsToMdfy:
			CMCHKPK(cmPkCztSrvdCellsToMdfy, &param->u.cztSrvdCellsToMdfy, mBuf);
			break;
		case Cztid_SrvdCellsToDelete:
			CMCHKPK(cmPkCztOld_ECGIs, &param->u.cztOld_ECGIs, mBuf);
			break;
		case Cztid_GUGroupIDToAddLst:
			CMCHKPK(cmPkCztGUGroupIDLst, &param->u.cztid_GUGroupIDToAddLst, mBuf);
			break;
		case Cztid_GUGroupIDToDeleteLst:
			CMCHKPK(cmPkCztGUGroupIDLst, &param->u.cztid_GUGroupIDToDeleteLst, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueENBConfigUpd_IEsCls */



/* 
* FUN : cmPkCztProtIE_Field_ENBConfigUpd_IEs
*  DESC: Function to Pack CztProtIE_Field_ENBConfigUpd_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_ENBConfigUpd_IEs
(
CztProtIE_Field_ENBConfigUpd_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_ENBConfigUpd_IEs(param, mBuf)
CztProtIE_Field_ENBConfigUpd_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_ENBConfigUpd_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueENBConfigUpd_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_ENBConfigUpd_IEs */



/* 
* FUN : cmPkCztProtIE_Cont_ENBConfigUpd_IEs
*  DESC: Function to Pack CztProtIE_Cont_ENBConfigUpd_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Cont_ENBConfigUpd_IEs
(
CztProtIE_Cont_ENBConfigUpd_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Cont_ENBConfigUpd_IEs(param, mBuf)
CztProtIE_Cont_ENBConfigUpd_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtIE_Cont_ENBConfigUpd_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Field_ENBConfigUpd_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Cont_ENBConfigUpd_IEs */



/* 
* FUN : cmPkCztENBConfigUpd
*  DESC: Function to Pack CztENBConfigUpd structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztENBConfigUpd
(
CztENBConfigUpd *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztENBConfigUpd(param, mBuf)
CztENBConfigUpd *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztENBConfigUpd) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtIE_Cont_ENBConfigUpd_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztENBConfigUpd */



/* 
* FUN : cmPkCzt_ValueENBConfigUpdAckg_IEsCls
*  DESC: Function to Pack Czt_ValueENBConfigUpdAckg_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueENBConfigUpdAckg_IEsCls
(
Czt_ValueENBConfigUpdAckg_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueENBConfigUpdAckg_IEsCls(param, val, mBuf)
Czt_ValueENBConfigUpdAckg_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueENBConfigUpdAckg_IEsCls) 
	
	switch (val)
	{
		case Cztid_CriticalityDiag:
			CMCHKPK(cmPkCztCriticalityDiag, &param->u.cztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueENBConfigUpdAckg_IEsCls */



/* 
* FUN : cmPkCztProtIE_Field_ENBConfigUpdAckg_IEs
*  DESC: Function to Pack CztProtIE_Field_ENBConfigUpdAckg_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_ENBConfigUpdAckg_IEs
(
CztProtIE_Field_ENBConfigUpdAckg_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_ENBConfigUpdAckg_IEs(param, mBuf)
CztProtIE_Field_ENBConfigUpdAckg_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_ENBConfigUpdAckg_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueENBConfigUpdAckg_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_ENBConfigUpdAckg_IEs */



/* 
* FUN : cmPkCztProtIE_Cont_ENBConfigUpdAckg_IEs
*  DESC: Function to Pack CztProtIE_Cont_ENBConfigUpdAckg_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Cont_ENBConfigUpdAckg_IEs
(
CztProtIE_Cont_ENBConfigUpdAckg_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Cont_ENBConfigUpdAckg_IEs(param, mBuf)
CztProtIE_Cont_ENBConfigUpdAckg_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtIE_Cont_ENBConfigUpdAckg_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Field_ENBConfigUpdAckg_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Cont_ENBConfigUpdAckg_IEs */



/* 
* FUN : cmPkCztENBConfigUpdAckg
*  DESC: Function to Pack CztENBConfigUpdAckg structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztENBConfigUpdAckg
(
CztENBConfigUpdAckg *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztENBConfigUpdAckg(param, mBuf)
CztENBConfigUpdAckg *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztENBConfigUpdAckg) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtIE_Cont_ENBConfigUpdAckg_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztENBConfigUpdAckg */



/* 
* FUN : cmPkCzt_ValueENBConfigUpdFail_IEsCls
*  DESC: Function to Pack Czt_ValueENBConfigUpdFail_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueENBConfigUpdFail_IEsCls
(
Czt_ValueENBConfigUpdFail_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueENBConfigUpdFail_IEsCls(param, val, mBuf)
Czt_ValueENBConfigUpdFail_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueENBConfigUpdFail_IEsCls) 
	
	switch (val)
	{
		case Cztid_Cause:
			CMCHKPK(cmPkCztCause, &param->u.cztCause, mBuf);
			break;
		case Cztid_TimeToWait:
			CMCHKPK(cmPkCztTimeToWait, &param->u.cztTimeToWait, mBuf);
			break;
		case Cztid_CriticalityDiag:
			CMCHKPK(cmPkCztCriticalityDiag, &param->u.cztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueENBConfigUpdFail_IEsCls */



/* 
* FUN : cmPkCztProtIE_Field_ENBConfigUpdFail_IEs
*  DESC: Function to Pack CztProtIE_Field_ENBConfigUpdFail_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_ENBConfigUpdFail_IEs
(
CztProtIE_Field_ENBConfigUpdFail_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_ENBConfigUpdFail_IEs(param, mBuf)
CztProtIE_Field_ENBConfigUpdFail_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_ENBConfigUpdFail_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueENBConfigUpdFail_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_ENBConfigUpdFail_IEs */



/* 
* FUN : cmPkCztProtIE_Cont_ENBConfigUpdFail_IEs
*  DESC: Function to Pack CztProtIE_Cont_ENBConfigUpdFail_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Cont_ENBConfigUpdFail_IEs
(
CztProtIE_Cont_ENBConfigUpdFail_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Cont_ENBConfigUpdFail_IEs(param, mBuf)
CztProtIE_Cont_ENBConfigUpdFail_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtIE_Cont_ENBConfigUpdFail_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Field_ENBConfigUpdFail_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Cont_ENBConfigUpdFail_IEs */



/* 
* FUN : cmPkCztENBConfigUpdFail
*  DESC: Function to Pack CztENBConfigUpdFail structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztENBConfigUpdFail
(
CztENBConfigUpdFail *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztENBConfigUpdFail(param, mBuf)
CztENBConfigUpdFail *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztENBConfigUpdFail) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtIE_Cont_ENBConfigUpdFail_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztENBConfigUpdFail */



/* 
* FUN : cmPkCzt_ExtnCellToReport_Item_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnCellToReport_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnCellToReport_Item_ExtIEsCls
(
Czt_ExtnCellToReport_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnCellToReport_Item_ExtIEsCls(param, val, mBuf)
Czt_ExtnCellToReport_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnCellToReport_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnCellToReport_Item_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_CellToReport_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnField_CellToReport_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_CellToReport_Item_ExtIEs
(
CztProtExtnField_CellToReport_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_CellToReport_Item_ExtIEs(param, mBuf)
CztProtExtnField_CellToReport_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_CellToReport_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnCellToReport_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_CellToReport_Item_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_CellToReport_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_CellToReport_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_CellToReport_Item_ExtIEs
(
CztProtExtnCont_CellToReport_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_CellToReport_Item_ExtIEs(param, mBuf)
CztProtExtnCont_CellToReport_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_CellToReport_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_CellToReport_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_CellToReport_Item_ExtIEs */



/* 
* FUN : cmPkCztCellToReport_Item
*  DESC: Function to Pack CztCellToReport_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztCellToReport_Item
(
CztCellToReport_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztCellToReport_Item(param, mBuf)
CztCellToReport_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztCellToReport_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_CellToReport_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztECGI, &param->cell_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztCellToReport_Item */



/* 
* FUN : cmPkCzt_ValueCellToReport_ItemIEsCls
*  DESC: Function to Pack Czt_ValueCellToReport_ItemIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueCellToReport_ItemIEsCls
(
Czt_ValueCellToReport_ItemIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueCellToReport_ItemIEsCls(param, val, mBuf)
Czt_ValueCellToReport_ItemIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueCellToReport_ItemIEsCls) 
	
	switch (val)
	{
		case Cztid_CellToReport_Item:
			CMCHKPK(cmPkCztCellToReport_Item, &param->u.cztCellToReport_Item, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueCellToReport_ItemIEsCls */



/* 
* FUN : cmPkCztProtIE_Field_CellToReport_ItemIEs
*  DESC: Function to Pack CztProtIE_Field_CellToReport_ItemIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_CellToReport_ItemIEs
(
CztProtIE_Field_CellToReport_ItemIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_CellToReport_ItemIEs(param, mBuf)
CztProtIE_Field_CellToReport_ItemIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_CellToReport_ItemIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueCellToReport_ItemIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_CellToReport_ItemIEs */

/* Element ------------- ProtocolIE-Single-Container ------------ */
#define cmPkCztProtIE_Single_Cont_CellToReport_ItemIEs cmPkCztProtIE_Field_CellToReport_ItemIEs


/* 
* FUN : cmPkCztCellToReport_Lst
*  DESC: Function to Pack CztCellToReport_Lst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztCellToReport_Lst
(
CztCellToReport_Lst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztCellToReport_Lst(param, mBuf)
CztCellToReport_Lst *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztCellToReport_Lst) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Single_Cont_CellToReport_ItemIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztCellToReport_Lst */

#define cmPkCztRprtngPeriodicity cmPkTknU32
#define cmPkCztPartialSuccessIndicator cmPkTknU32


/* 
* FUN : cmPkCzt_ValueResStatusRqst_IEsCls
*  DESC: Function to Pack Czt_ValueResStatusRqst_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueResStatusRqst_IEsCls
(
Czt_ValueResStatusRqst_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueResStatusRqst_IEsCls(param, val, mBuf)
Czt_ValueResStatusRqst_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueResStatusRqst_IEsCls) 
	
	switch (val)
	{
		case Cztid_ENB1_Measurement_ID:
			CMCHKPK(cmPkCztMeasurement_ID, &param->u.cztid_ENB1_Measurement_ID, mBuf);
			break;
		case Cztid_ENB2_Measurement_ID:
			CMCHKPK(cmPkCztMeasurement_ID, &param->u.cztid_ENB2_Measurement_ID, mBuf);
			break;
		case Cztid_Registration_Rqst:
			CMCHKPK(cmPkCztRegistration_Rqst, &param->u.cztRegistration_Rqst, mBuf);
			break;
		case Cztid_ReportCharacteristics:
			CMCHKPK(cmPkCztReportCharacteristics, &param->u.cztReportCharacteristics, mBuf);
			break;
		case Cztid_CellToReport:
			CMCHKPK(cmPkCztCellToReport_Lst, &param->u.cztCellToReport_Lst, mBuf);
			break;
		case Cztid_RprtngPeriodicity:
			CMCHKPK(cmPkCztRprtngPeriodicity, &param->u.cztRprtngPeriodicity, mBuf);
			break;
		case Cztid_PartialSuccessIndicator:
			CMCHKPK(cmPkCztPartialSuccessIndicator, &param->u.cztPartialSuccessIndicator, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueResStatusRqst_IEsCls */



/* 
* FUN : cmPkCztProtIE_Field_ResStatusRqst_IEs
*  DESC: Function to Pack CztProtIE_Field_ResStatusRqst_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_ResStatusRqst_IEs
(
CztProtIE_Field_ResStatusRqst_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_ResStatusRqst_IEs(param, mBuf)
CztProtIE_Field_ResStatusRqst_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_ResStatusRqst_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueResStatusRqst_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_ResStatusRqst_IEs */



/* 
* FUN : cmPkCztProtIE_Cont_ResStatusRqst_IEs
*  DESC: Function to Pack CztProtIE_Cont_ResStatusRqst_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Cont_ResStatusRqst_IEs
(
CztProtIE_Cont_ResStatusRqst_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Cont_ResStatusRqst_IEs(param, mBuf)
CztProtIE_Cont_ResStatusRqst_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtIE_Cont_ResStatusRqst_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Field_ResStatusRqst_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Cont_ResStatusRqst_IEs */



/* 
* FUN : cmPkCztResStatusRqst
*  DESC: Function to Pack CztResStatusRqst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztResStatusRqst
(
CztResStatusRqst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztResStatusRqst(param, mBuf)
CztResStatusRqst *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztResStatusRqst) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtIE_Cont_ResStatusRqst_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztResStatusRqst */



/* 
* FUN : cmPkCzt_ExtnMeasurementFailCause_Item_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnMeasurementFailCause_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnMeasurementFailCause_Item_ExtIEsCls
(
Czt_ExtnMeasurementFailCause_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnMeasurementFailCause_Item_ExtIEsCls(param, val, mBuf)
Czt_ExtnMeasurementFailCause_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnMeasurementFailCause_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnMeasurementFailCause_Item_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_MeasurementFailCause_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnField_MeasurementFailCause_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_MeasurementFailCause_Item_ExtIEs
(
CztProtExtnField_MeasurementFailCause_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_MeasurementFailCause_Item_ExtIEs(param, mBuf)
CztProtExtnField_MeasurementFailCause_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_MeasurementFailCause_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnMeasurementFailCause_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_MeasurementFailCause_Item_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_MeasurementFailCause_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_MeasurementFailCause_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_MeasurementFailCause_Item_ExtIEs
(
CztProtExtnCont_MeasurementFailCause_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_MeasurementFailCause_Item_ExtIEs(param, mBuf)
CztProtExtnCont_MeasurementFailCause_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_MeasurementFailCause_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_MeasurementFailCause_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_MeasurementFailCause_Item_ExtIEs */



/* 
* FUN : cmPkCztMeasurementFailCause_Item
*  DESC: Function to Pack CztMeasurementFailCause_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztMeasurementFailCause_Item
(
CztMeasurementFailCause_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztMeasurementFailCause_Item(param, mBuf)
CztMeasurementFailCause_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztMeasurementFailCause_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_MeasurementFailCause_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztCause, &param->cause, mBuf); 
		CMCHKPK(cmPkCztReportCharacteristics, &param->measurementFailedReportCharacteristics, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztMeasurementFailCause_Item */



/* 
* FUN : cmPkCzt_ValueMeasurementFailCause_ItemIEsCls
*  DESC: Function to Pack Czt_ValueMeasurementFailCause_ItemIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueMeasurementFailCause_ItemIEsCls
(
Czt_ValueMeasurementFailCause_ItemIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueMeasurementFailCause_ItemIEsCls(param, val, mBuf)
Czt_ValueMeasurementFailCause_ItemIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueMeasurementFailCause_ItemIEsCls) 
	
	switch (val)
	{
		case Cztid_MeasurementFailCause_Item:
			CMCHKPK(cmPkCztMeasurementFailCause_Item, &param->u.cztMeasurementFailCause_Item, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueMeasurementFailCause_ItemIEsCls */



/* 
* FUN : cmPkCztProtIE_Field_MeasurementFailCause_ItemIEs
*  DESC: Function to Pack CztProtIE_Field_MeasurementFailCause_ItemIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_MeasurementFailCause_ItemIEs
(
CztProtIE_Field_MeasurementFailCause_ItemIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_MeasurementFailCause_ItemIEs(param, mBuf)
CztProtIE_Field_MeasurementFailCause_ItemIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_MeasurementFailCause_ItemIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueMeasurementFailCause_ItemIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_MeasurementFailCause_ItemIEs */

/* Element ------------- ProtocolIE-Single-Container ------------ */
#define cmPkCztProtIE_Single_Cont_MeasurementFailCause_ItemIEs cmPkCztProtIE_Field_MeasurementFailCause_ItemIEs


/* 
* FUN : cmPkCztMeasurementFailCause_Lst
*  DESC: Function to Pack CztMeasurementFailCause_Lst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztMeasurementFailCause_Lst
(
CztMeasurementFailCause_Lst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztMeasurementFailCause_Lst(param, mBuf)
CztMeasurementFailCause_Lst *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztMeasurementFailCause_Lst) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Single_Cont_MeasurementFailCause_ItemIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztMeasurementFailCause_Lst */



/* 
* FUN : cmPkCzt_ExtnMeasurementInitiationResult_Item_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnMeasurementInitiationResult_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnMeasurementInitiationResult_Item_ExtIEsCls
(
Czt_ExtnMeasurementInitiationResult_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnMeasurementInitiationResult_Item_ExtIEsCls(param, val, mBuf)
Czt_ExtnMeasurementInitiationResult_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnMeasurementInitiationResult_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnMeasurementInitiationResult_Item_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_MeasurementInitiationResult_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnField_MeasurementInitiationResult_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_MeasurementInitiationResult_Item_ExtIEs
(
CztProtExtnField_MeasurementInitiationResult_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_MeasurementInitiationResult_Item_ExtIEs(param, mBuf)
CztProtExtnField_MeasurementInitiationResult_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_MeasurementInitiationResult_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnMeasurementInitiationResult_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_MeasurementInitiationResult_Item_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_MeasurementInitiationResult_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_MeasurementInitiationResult_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_MeasurementInitiationResult_Item_ExtIEs
(
CztProtExtnCont_MeasurementInitiationResult_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_MeasurementInitiationResult_Item_ExtIEs(param, mBuf)
CztProtExtnCont_MeasurementInitiationResult_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_MeasurementInitiationResult_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_MeasurementInitiationResult_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_MeasurementInitiationResult_Item_ExtIEs */



/* 
* FUN : cmPkCztMeasurementInitiationResult_Item
*  DESC: Function to Pack CztMeasurementInitiationResult_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztMeasurementInitiationResult_Item
(
CztMeasurementInitiationResult_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztMeasurementInitiationResult_Item(param, mBuf)
CztMeasurementInitiationResult_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztMeasurementInitiationResult_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_MeasurementInitiationResult_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztMeasurementFailCause_Lst, &param->measurementFailCause_Lst, mBuf); 
		CMCHKPK(cmPkCztECGI, &param->cell_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztMeasurementInitiationResult_Item */



/* 
* FUN : cmPkCzt_ValueMeasurementInitiationResult_ItemIEsCls
*  DESC: Function to Pack Czt_ValueMeasurementInitiationResult_ItemIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueMeasurementInitiationResult_ItemIEsCls
(
Czt_ValueMeasurementInitiationResult_ItemIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueMeasurementInitiationResult_ItemIEsCls(param, val, mBuf)
Czt_ValueMeasurementInitiationResult_ItemIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueMeasurementInitiationResult_ItemIEsCls) 
	
	switch (val)
	{
		case Cztid_MeasurementInitiationResult_Item:
			CMCHKPK(cmPkCztMeasurementInitiationResult_Item, &param->u.cztMeasurementInitiationResult_Item, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueMeasurementInitiationResult_ItemIEsCls */



/* 
* FUN : cmPkCztProtIE_Field_MeasurementInitiationResult_ItemIEs
*  DESC: Function to Pack CztProtIE_Field_MeasurementInitiationResult_ItemIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_MeasurementInitiationResult_ItemIEs
(
CztProtIE_Field_MeasurementInitiationResult_ItemIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_MeasurementInitiationResult_ItemIEs(param, mBuf)
CztProtIE_Field_MeasurementInitiationResult_ItemIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_MeasurementInitiationResult_ItemIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueMeasurementInitiationResult_ItemIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_MeasurementInitiationResult_ItemIEs */

/* Element ------------- ProtocolIE-Single-Container ------------ */
#define cmPkCztProtIE_Single_Cont_MeasurementInitiationResult_ItemIEs cmPkCztProtIE_Field_MeasurementInitiationResult_ItemIEs


/* 
* FUN : cmPkCztMeasurementInitiationResult_Lst
*  DESC: Function to Pack CztMeasurementInitiationResult_Lst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztMeasurementInitiationResult_Lst
(
CztMeasurementInitiationResult_Lst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztMeasurementInitiationResult_Lst(param, mBuf)
CztMeasurementInitiationResult_Lst *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztMeasurementInitiationResult_Lst) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Single_Cont_MeasurementInitiationResult_ItemIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztMeasurementInitiationResult_Lst */



/* 
* FUN : cmPkCzt_ValueResStatusResp_IEsCls
*  DESC: Function to Pack Czt_ValueResStatusResp_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueResStatusResp_IEsCls
(
Czt_ValueResStatusResp_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueResStatusResp_IEsCls(param, val, mBuf)
Czt_ValueResStatusResp_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueResStatusResp_IEsCls) 
	
	switch (val)
	{
		case Cztid_ENB1_Measurement_ID:
			CMCHKPK(cmPkCztMeasurement_ID, &param->u.cztid_ENB1_Measurement_ID, mBuf);
			break;
		case Cztid_ENB2_Measurement_ID:
			CMCHKPK(cmPkCztMeasurement_ID, &param->u.cztid_ENB2_Measurement_ID, mBuf);
			break;
		case Cztid_CriticalityDiag:
			CMCHKPK(cmPkCztCriticalityDiag, &param->u.cztCriticalityDiag, mBuf);
			break;
		case Cztid_MeasurementInitiationResult_Lst:
			CMCHKPK(cmPkCztMeasurementInitiationResult_Lst, &param->u.cztMeasurementInitiationResult_Lst, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueResStatusResp_IEsCls */



/* 
* FUN : cmPkCztProtIE_Field_ResStatusResp_IEs
*  DESC: Function to Pack CztProtIE_Field_ResStatusResp_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_ResStatusResp_IEs
(
CztProtIE_Field_ResStatusResp_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_ResStatusResp_IEs(param, mBuf)
CztProtIE_Field_ResStatusResp_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_ResStatusResp_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueResStatusResp_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_ResStatusResp_IEs */



/* 
* FUN : cmPkCztProtIE_Cont_ResStatusResp_IEs
*  DESC: Function to Pack CztProtIE_Cont_ResStatusResp_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Cont_ResStatusResp_IEs
(
CztProtIE_Cont_ResStatusResp_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Cont_ResStatusResp_IEs(param, mBuf)
CztProtIE_Cont_ResStatusResp_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtIE_Cont_ResStatusResp_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Field_ResStatusResp_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Cont_ResStatusResp_IEs */



/* 
* FUN : cmPkCztResStatusResp
*  DESC: Function to Pack CztResStatusResp structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztResStatusResp
(
CztResStatusResp *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztResStatusResp(param, mBuf)
CztResStatusResp *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztResStatusResp) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtIE_Cont_ResStatusResp_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztResStatusResp */



/* 
* FUN : cmPkCzt_ExtnCompleteFailCauseInform_Item_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnCompleteFailCauseInform_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnCompleteFailCauseInform_Item_ExtIEsCls
(
Czt_ExtnCompleteFailCauseInform_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnCompleteFailCauseInform_Item_ExtIEsCls(param, val, mBuf)
Czt_ExtnCompleteFailCauseInform_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnCompleteFailCauseInform_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnCompleteFailCauseInform_Item_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_CompleteFailCauseInform_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnField_CompleteFailCauseInform_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_CompleteFailCauseInform_Item_ExtIEs
(
CztProtExtnField_CompleteFailCauseInform_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_CompleteFailCauseInform_Item_ExtIEs(param, mBuf)
CztProtExtnField_CompleteFailCauseInform_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_CompleteFailCauseInform_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnCompleteFailCauseInform_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_CompleteFailCauseInform_Item_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_CompleteFailCauseInform_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_CompleteFailCauseInform_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_CompleteFailCauseInform_Item_ExtIEs
(
CztProtExtnCont_CompleteFailCauseInform_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_CompleteFailCauseInform_Item_ExtIEs(param, mBuf)
CztProtExtnCont_CompleteFailCauseInform_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_CompleteFailCauseInform_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_CompleteFailCauseInform_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_CompleteFailCauseInform_Item_ExtIEs */



/* 
* FUN : cmPkCztCompleteFailCauseInform_Item
*  DESC: Function to Pack CztCompleteFailCauseInform_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztCompleteFailCauseInform_Item
(
CztCompleteFailCauseInform_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztCompleteFailCauseInform_Item(param, mBuf)
CztCompleteFailCauseInform_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztCompleteFailCauseInform_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_CompleteFailCauseInform_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztMeasurementFailCause_Lst, &param->measurementFailCause_Lst, mBuf); 
		CMCHKPK(cmPkCztECGI, &param->cell_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztCompleteFailCauseInform_Item */



/* 
* FUN : cmPkCzt_ValueCompleteFailCauseInform_ItemIEsCls
*  DESC: Function to Pack Czt_ValueCompleteFailCauseInform_ItemIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueCompleteFailCauseInform_ItemIEsCls
(
Czt_ValueCompleteFailCauseInform_ItemIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueCompleteFailCauseInform_ItemIEsCls(param, val, mBuf)
Czt_ValueCompleteFailCauseInform_ItemIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueCompleteFailCauseInform_ItemIEsCls) 
	
	switch (val)
	{
		case Cztid_CompleteFailCauseInform_Item:
			CMCHKPK(cmPkCztCompleteFailCauseInform_Item, &param->u.cztCompleteFailCauseInform_Item, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueCompleteFailCauseInform_ItemIEsCls */



/* 
* FUN : cmPkCztProtIE_Field_CompleteFailCauseInform_ItemIEs
*  DESC: Function to Pack CztProtIE_Field_CompleteFailCauseInform_ItemIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_CompleteFailCauseInform_ItemIEs
(
CztProtIE_Field_CompleteFailCauseInform_ItemIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_CompleteFailCauseInform_ItemIEs(param, mBuf)
CztProtIE_Field_CompleteFailCauseInform_ItemIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_CompleteFailCauseInform_ItemIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueCompleteFailCauseInform_ItemIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_CompleteFailCauseInform_ItemIEs */

/* Element ------------- ProtocolIE-Single-Container ------------ */
#define cmPkCztProtIE_Single_Cont_CompleteFailCauseInform_ItemIEs cmPkCztProtIE_Field_CompleteFailCauseInform_ItemIEs


/* 
* FUN : cmPkCztCompleteFailCauseInform_Lst
*  DESC: Function to Pack CztCompleteFailCauseInform_Lst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztCompleteFailCauseInform_Lst
(
CztCompleteFailCauseInform_Lst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztCompleteFailCauseInform_Lst(param, mBuf)
CztCompleteFailCauseInform_Lst *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztCompleteFailCauseInform_Lst) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Single_Cont_CompleteFailCauseInform_ItemIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztCompleteFailCauseInform_Lst */



/* 
* FUN : cmPkCzt_ValueResStatusFail_IEsCls
*  DESC: Function to Pack Czt_ValueResStatusFail_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueResStatusFail_IEsCls
(
Czt_ValueResStatusFail_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueResStatusFail_IEsCls(param, val, mBuf)
Czt_ValueResStatusFail_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueResStatusFail_IEsCls) 
	
	switch (val)
	{
		case Cztid_ENB1_Measurement_ID:
			CMCHKPK(cmPkCztMeasurement_ID, &param->u.cztid_ENB1_Measurement_ID, mBuf);
			break;
		case Cztid_ENB2_Measurement_ID:
			CMCHKPK(cmPkCztMeasurement_ID, &param->u.cztid_ENB2_Measurement_ID, mBuf);
			break;
		case Cztid_Cause:
			CMCHKPK(cmPkCztCause, &param->u.cztCause, mBuf);
			break;
		case Cztid_CriticalityDiag:
			CMCHKPK(cmPkCztCriticalityDiag, &param->u.cztCriticalityDiag, mBuf);
			break;
		case Cztid_CompleteFailCauseInform_Lst:
			CMCHKPK(cmPkCztCompleteFailCauseInform_Lst, &param->u.cztCompleteFailCauseInform_Lst, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueResStatusFail_IEsCls */



/* 
* FUN : cmPkCztProtIE_Field_ResStatusFail_IEs
*  DESC: Function to Pack CztProtIE_Field_ResStatusFail_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_ResStatusFail_IEs
(
CztProtIE_Field_ResStatusFail_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_ResStatusFail_IEs(param, mBuf)
CztProtIE_Field_ResStatusFail_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_ResStatusFail_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueResStatusFail_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_ResStatusFail_IEs */



/* 
* FUN : cmPkCztProtIE_Cont_ResStatusFail_IEs
*  DESC: Function to Pack CztProtIE_Cont_ResStatusFail_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Cont_ResStatusFail_IEs
(
CztProtIE_Cont_ResStatusFail_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Cont_ResStatusFail_IEs(param, mBuf)
CztProtIE_Cont_ResStatusFail_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtIE_Cont_ResStatusFail_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Field_ResStatusFail_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Cont_ResStatusFail_IEs */



/* 
* FUN : cmPkCztResStatusFail
*  DESC: Function to Pack CztResStatusFail structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztResStatusFail
(
CztResStatusFail *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztResStatusFail(param, mBuf)
CztResStatusFail *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztResStatusFail) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtIE_Cont_ResStatusFail_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztResStatusFail */



/* 
* FUN : cmPkCzt_ExtnCellMeasurementResult_Item_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnCellMeasurementResult_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnCellMeasurementResult_Item_ExtIEsCls
(
Czt_ExtnCellMeasurementResult_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnCellMeasurementResult_Item_ExtIEsCls(param, val, mBuf)
Czt_ExtnCellMeasurementResult_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnCellMeasurementResult_Item_ExtIEsCls) 
	
	switch (val)
	{
		case Cztid_CompositeAvailableCapacityGroup:
			CMCHKPK(cmPkCztCompositeAvailableCapacityGroup, &param->u.cztCompositeAvailableCapacityGroup, mBuf);
			break;
		case Cztid_ABS_Status:
			CMCHKPK(cmPkCztABS_Status, &param->u.cztABS_Status, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ExtnCellMeasurementResult_Item_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_CellMeasurementResult_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnField_CellMeasurementResult_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_CellMeasurementResult_Item_ExtIEs
(
CztProtExtnField_CellMeasurementResult_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_CellMeasurementResult_Item_ExtIEs(param, mBuf)
CztProtExtnField_CellMeasurementResult_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_CellMeasurementResult_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnCellMeasurementResult_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_CellMeasurementResult_Item_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_CellMeasurementResult_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_CellMeasurementResult_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_CellMeasurementResult_Item_ExtIEs
(
CztProtExtnCont_CellMeasurementResult_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_CellMeasurementResult_Item_ExtIEs(param, mBuf)
CztProtExtnCont_CellMeasurementResult_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_CellMeasurementResult_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_CellMeasurementResult_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_CellMeasurementResult_Item_ExtIEs */



/* 
* FUN : cmPkCztCellMeasurementResult_Item
*  DESC: Function to Pack CztCellMeasurementResult_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztCellMeasurementResult_Item
(
CztCellMeasurementResult_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztCellMeasurementResult_Item(param, mBuf)
CztCellMeasurementResult_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztCellMeasurementResult_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_CellMeasurementResult_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztRadioResStatus, &param->radioResStatus, mBuf); 
		CMCHKPK(cmPkCztS1TNLLoadIndicator, &param->s1TNLLoadIndicator, mBuf); 
		CMCHKPK(cmPkCztHWLoadIndicator, &param->hWLoadIndicator, mBuf); 
		CMCHKPK(cmPkCztECGI, &param->cell_ID, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztCellMeasurementResult_Item */



/* 
* FUN : cmPkCzt_ValueCellMeasurementResult_ItemIEsCls
*  DESC: Function to Pack Czt_ValueCellMeasurementResult_ItemIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueCellMeasurementResult_ItemIEsCls
(
Czt_ValueCellMeasurementResult_ItemIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueCellMeasurementResult_ItemIEsCls(param, val, mBuf)
Czt_ValueCellMeasurementResult_ItemIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueCellMeasurementResult_ItemIEsCls) 
	
	switch (val)
	{
		case Cztid_CellMeasurementResult_Item:
			CMCHKPK(cmPkCztCellMeasurementResult_Item, &param->u.cztCellMeasurementResult_Item, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueCellMeasurementResult_ItemIEsCls */



/* 
* FUN : cmPkCztProtIE_Field_CellMeasurementResult_ItemIEs
*  DESC: Function to Pack CztProtIE_Field_CellMeasurementResult_ItemIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_CellMeasurementResult_ItemIEs
(
CztProtIE_Field_CellMeasurementResult_ItemIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_CellMeasurementResult_ItemIEs(param, mBuf)
CztProtIE_Field_CellMeasurementResult_ItemIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_CellMeasurementResult_ItemIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueCellMeasurementResult_ItemIEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_CellMeasurementResult_ItemIEs */

/* Element ------------- ProtocolIE-Single-Container ------------ */
#define cmPkCztProtIE_Single_Cont_CellMeasurementResult_ItemIEs cmPkCztProtIE_Field_CellMeasurementResult_ItemIEs


/* 
* FUN : cmPkCztCellMeasurementResult_Lst
*  DESC: Function to Pack CztCellMeasurementResult_Lst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztCellMeasurementResult_Lst
(
CztCellMeasurementResult_Lst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztCellMeasurementResult_Lst(param, mBuf)
CztCellMeasurementResult_Lst *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztCellMeasurementResult_Lst) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Single_Cont_CellMeasurementResult_ItemIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztCellMeasurementResult_Lst */



/* 
* FUN : cmPkCzt_ValueResStatusUpd_IEsCls
*  DESC: Function to Pack Czt_ValueResStatusUpd_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueResStatusUpd_IEsCls
(
Czt_ValueResStatusUpd_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueResStatusUpd_IEsCls(param, val, mBuf)
Czt_ValueResStatusUpd_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueResStatusUpd_IEsCls) 
	
	switch (val)
	{
		case Cztid_ENB1_Measurement_ID:
			CMCHKPK(cmPkCztMeasurement_ID, &param->u.cztid_ENB1_Measurement_ID, mBuf);
			break;
		case Cztid_ENB2_Measurement_ID:
			CMCHKPK(cmPkCztMeasurement_ID, &param->u.cztid_ENB2_Measurement_ID, mBuf);
			break;
		case Cztid_CellMeasurementResult:
			CMCHKPK(cmPkCztCellMeasurementResult_Lst, &param->u.cztCellMeasurementResult_Lst, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueResStatusUpd_IEsCls */



/* 
* FUN : cmPkCztProtIE_Field_ResStatusUpd_IEs
*  DESC: Function to Pack CztProtIE_Field_ResStatusUpd_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_ResStatusUpd_IEs
(
CztProtIE_Field_ResStatusUpd_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_ResStatusUpd_IEs(param, mBuf)
CztProtIE_Field_ResStatusUpd_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_ResStatusUpd_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueResStatusUpd_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_ResStatusUpd_IEs */



/* 
* FUN : cmPkCztProtIE_Cont_ResStatusUpd_IEs
*  DESC: Function to Pack CztProtIE_Cont_ResStatusUpd_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Cont_ResStatusUpd_IEs
(
CztProtIE_Cont_ResStatusUpd_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Cont_ResStatusUpd_IEs(param, mBuf)
CztProtIE_Cont_ResStatusUpd_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtIE_Cont_ResStatusUpd_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Field_ResStatusUpd_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Cont_ResStatusUpd_IEs */



/* 
* FUN : cmPkCztResStatusUpd
*  DESC: Function to Pack CztResStatusUpd structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztResStatusUpd
(
CztResStatusUpd *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztResStatusUpd(param, mBuf)
CztResStatusUpd *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztResStatusUpd) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtIE_Cont_ResStatusUpd_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztResStatusUpd */



/* 
* FUN : cmPkCzt_ValuePrivMsg_IEsCls
*  DESC: Function to Pack Czt_ValuePrivMsg_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValuePrivMsg_IEsCls
(
Czt_ValuePrivMsg_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValuePrivMsg_IEsCls(param, val, mBuf)
Czt_ValuePrivMsg_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValuePrivMsg_IEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ValuePrivMsg_IEsCls */



/* 
* FUN : cmPkCztPrivIE_Field_PrivMsg_IEs
*  DESC: Function to Pack CztPrivIE_Field_PrivMsg_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztPrivIE_Field_PrivMsg_IEs
(
CztPrivIE_Field_PrivMsg_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztPrivIE_Field_PrivMsg_IEs(param, mBuf)
CztPrivIE_Field_PrivMsg_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztPrivIE_Field_PrivMsg_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztPrivIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztPrivIE_Field_PrivMsg_IEs */



/* 
* FUN : cmPkCztPrivIE_Cont_PrivMsg_IEs
*  DESC: Function to Pack CztPrivIE_Cont_PrivMsg_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztPrivIE_Cont_PrivMsg_IEs
(
CztPrivIE_Cont_PrivMsg_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztPrivIE_Cont_PrivMsg_IEs(param, mBuf)
CztPrivIE_Cont_PrivMsg_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztPrivIE_Cont_PrivMsg_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztPrivIE_Field_PrivMsg_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztPrivIE_Cont_PrivMsg_IEs */



/* 
* FUN : cmPkCztPrivMsg
*  DESC: Function to Pack CztPrivMsg structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztPrivMsg
(
CztPrivMsg *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztPrivMsg(param, mBuf)
CztPrivMsg *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztPrivMsg) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztPrivIE_Cont_PrivMsg_IEs, &param->privateIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztPrivMsg */



/* 
* FUN : cmPkCzt_ValueMobilityChangeRqst_IEsCls
*  DESC: Function to Pack Czt_ValueMobilityChangeRqst_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueMobilityChangeRqst_IEsCls
(
Czt_ValueMobilityChangeRqst_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueMobilityChangeRqst_IEsCls(param, val, mBuf)
Czt_ValueMobilityChangeRqst_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueMobilityChangeRqst_IEsCls) 
	
	switch (val)
	{
		case Cztid_ENB1_Cell_ID:
			CMCHKPK(cmPkCztECGI, &param->u.cztid_ENB1_Cell_ID, mBuf);
			break;
		case Cztid_ENB2_Cell_ID:
			CMCHKPK(cmPkCztECGI, &param->u.cztid_ENB2_Cell_ID, mBuf);
			break;
		case Cztid_ENB1_Mobility_Params:
			CMCHKPK(cmPkCztMobilityParamsInform, &param->u.cztid_ENB1_Mobility_Params, mBuf);
			break;
		case Cztid_ENB2_Proposed_Mobility_Params:
			CMCHKPK(cmPkCztMobilityParamsInform, &param->u.cztid_ENB2_Proposed_Mobility_Params, mBuf);
			break;
		case Cztid_Cause:
			CMCHKPK(cmPkCztCause, &param->u.cztCause, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueMobilityChangeRqst_IEsCls */



/* 
* FUN : cmPkCztProtIE_Field_MobilityChangeRqst_IEs
*  DESC: Function to Pack CztProtIE_Field_MobilityChangeRqst_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_MobilityChangeRqst_IEs
(
CztProtIE_Field_MobilityChangeRqst_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_MobilityChangeRqst_IEs(param, mBuf)
CztProtIE_Field_MobilityChangeRqst_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_MobilityChangeRqst_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueMobilityChangeRqst_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_MobilityChangeRqst_IEs */



/* 
* FUN : cmPkCztProtIE_Cont_MobilityChangeRqst_IEs
*  DESC: Function to Pack CztProtIE_Cont_MobilityChangeRqst_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Cont_MobilityChangeRqst_IEs
(
CztProtIE_Cont_MobilityChangeRqst_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Cont_MobilityChangeRqst_IEs(param, mBuf)
CztProtIE_Cont_MobilityChangeRqst_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtIE_Cont_MobilityChangeRqst_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Field_MobilityChangeRqst_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Cont_MobilityChangeRqst_IEs */



/* 
* FUN : cmPkCztMobilityChangeRqst
*  DESC: Function to Pack CztMobilityChangeRqst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztMobilityChangeRqst
(
CztMobilityChangeRqst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztMobilityChangeRqst(param, mBuf)
CztMobilityChangeRqst *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztMobilityChangeRqst) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtIE_Cont_MobilityChangeRqst_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztMobilityChangeRqst */



/* 
* FUN : cmPkCzt_ValueMobilityChangeAckg_IEsCls
*  DESC: Function to Pack Czt_ValueMobilityChangeAckg_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueMobilityChangeAckg_IEsCls
(
Czt_ValueMobilityChangeAckg_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueMobilityChangeAckg_IEsCls(param, val, mBuf)
Czt_ValueMobilityChangeAckg_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueMobilityChangeAckg_IEsCls) 
	
	switch (val)
	{
		case Cztid_ENB1_Cell_ID:
			CMCHKPK(cmPkCztECGI, &param->u.cztid_ENB1_Cell_ID, mBuf);
			break;
		case Cztid_ENB2_Cell_ID:
			CMCHKPK(cmPkCztECGI, &param->u.cztid_ENB2_Cell_ID, mBuf);
			break;
		case Cztid_CriticalityDiag:
			CMCHKPK(cmPkCztCriticalityDiag, &param->u.cztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueMobilityChangeAckg_IEsCls */



/* 
* FUN : cmPkCztProtIE_Field_MobilityChangeAckg_IEs
*  DESC: Function to Pack CztProtIE_Field_MobilityChangeAckg_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_MobilityChangeAckg_IEs
(
CztProtIE_Field_MobilityChangeAckg_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_MobilityChangeAckg_IEs(param, mBuf)
CztProtIE_Field_MobilityChangeAckg_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_MobilityChangeAckg_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueMobilityChangeAckg_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_MobilityChangeAckg_IEs */



/* 
* FUN : cmPkCztProtIE_Cont_MobilityChangeAckg_IEs
*  DESC: Function to Pack CztProtIE_Cont_MobilityChangeAckg_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Cont_MobilityChangeAckg_IEs
(
CztProtIE_Cont_MobilityChangeAckg_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Cont_MobilityChangeAckg_IEs(param, mBuf)
CztProtIE_Cont_MobilityChangeAckg_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtIE_Cont_MobilityChangeAckg_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Field_MobilityChangeAckg_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Cont_MobilityChangeAckg_IEs */



/* 
* FUN : cmPkCztMobilityChangeAckg
*  DESC: Function to Pack CztMobilityChangeAckg structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztMobilityChangeAckg
(
CztMobilityChangeAckg *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztMobilityChangeAckg(param, mBuf)
CztMobilityChangeAckg *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztMobilityChangeAckg) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtIE_Cont_MobilityChangeAckg_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztMobilityChangeAckg */



/* 
* FUN : cmPkCzt_ValueMobilityChangeFail_IEsCls
*  DESC: Function to Pack Czt_ValueMobilityChangeFail_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueMobilityChangeFail_IEsCls
(
Czt_ValueMobilityChangeFail_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueMobilityChangeFail_IEsCls(param, val, mBuf)
Czt_ValueMobilityChangeFail_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueMobilityChangeFail_IEsCls) 
	
	switch (val)
	{
		case Cztid_ENB1_Cell_ID:
			CMCHKPK(cmPkCztECGI, &param->u.cztid_ENB1_Cell_ID, mBuf);
			break;
		case Cztid_ENB2_Cell_ID:
			CMCHKPK(cmPkCztECGI, &param->u.cztid_ENB2_Cell_ID, mBuf);
			break;
		case Cztid_Cause:
			CMCHKPK(cmPkCztCause, &param->u.cztCause, mBuf);
			break;
		case Cztid_ENB2_Mobility_Params_Modification_Range:
			CMCHKPK(cmPkCztMobilityParamsModificationRange, &param->u.cztMobilityParamsModificationRange, mBuf);
			break;
		case Cztid_CriticalityDiag:
			CMCHKPK(cmPkCztCriticalityDiag, &param->u.cztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueMobilityChangeFail_IEsCls */



/* 
* FUN : cmPkCztProtIE_Field_MobilityChangeFail_IEs
*  DESC: Function to Pack CztProtIE_Field_MobilityChangeFail_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_MobilityChangeFail_IEs
(
CztProtIE_Field_MobilityChangeFail_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_MobilityChangeFail_IEs(param, mBuf)
CztProtIE_Field_MobilityChangeFail_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_MobilityChangeFail_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueMobilityChangeFail_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_MobilityChangeFail_IEs */



/* 
* FUN : cmPkCztProtIE_Cont_MobilityChangeFail_IEs
*  DESC: Function to Pack CztProtIE_Cont_MobilityChangeFail_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Cont_MobilityChangeFail_IEs
(
CztProtIE_Cont_MobilityChangeFail_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Cont_MobilityChangeFail_IEs(param, mBuf)
CztProtIE_Cont_MobilityChangeFail_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtIE_Cont_MobilityChangeFail_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Field_MobilityChangeFail_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Cont_MobilityChangeFail_IEs */



/* 
* FUN : cmPkCztMobilityChangeFail
*  DESC: Function to Pack CztMobilityChangeFail structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztMobilityChangeFail
(
CztMobilityChangeFail *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztMobilityChangeFail(param, mBuf)
CztMobilityChangeFail *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztMobilityChangeFail) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtIE_Cont_MobilityChangeFail_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztMobilityChangeFail */



/* 
* FUN : cmPkCzt_ValueRLFInd_IEsCls
*  DESC: Function to Pack Czt_ValueRLFInd_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueRLFInd_IEsCls
(
Czt_ValueRLFInd_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueRLFInd_IEsCls(param, val, mBuf)
Czt_ValueRLFInd_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueRLFInd_IEsCls) 
	
	switch (val)
	{
		case Cztid_FailCellPCI:
			CMCHKPK(cmPkCztPCI, &param->u.cztPCI, mBuf);
			break;
		case Cztid_Re_establishmentCellECGI:
			CMCHKPK(cmPkCztECGI, &param->u.cztECGI, mBuf);
			break;
		case Cztid_FailCellCRNTI:
			CMCHKPK(cmPkCztCRNTI, &param->u.cztCRNTI, mBuf);
			break;
		case Cztid_ShortMAC_I:
			CMCHKPK(cmPkCztShortMAC_I, &param->u.cztShortMAC_I, mBuf);
			break;
		case Cztid_UE_RLF_Report_Cont:
			CMCHKPK(cmPkCztUE_RLF_Report_Cont, &param->u.cztUE_RLF_Report_Cont, mBuf);
			break;
		case Cztid_RRCConnSetupIndicator:
			CMCHKPK(cmPkCztRRCConnSetupIndicator, &param->u.cztRRCConnSetupIndicator, mBuf);
			break;
		case Cztid_RRCConnReestabIndicator:
			CMCHKPK(cmPkCztRRCConnReestabIndicator, &param->u.cztRRCConnReestabIndicator, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueRLFInd_IEsCls */



/* 
* FUN : cmPkCztProtIE_Field_RLFInd_IEs
*  DESC: Function to Pack CztProtIE_Field_RLFInd_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_RLFInd_IEs
(
CztProtIE_Field_RLFInd_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_RLFInd_IEs(param, mBuf)
CztProtIE_Field_RLFInd_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_RLFInd_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueRLFInd_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_RLFInd_IEs */



/* 
* FUN : cmPkCztProtIE_Cont_RLFInd_IEs
*  DESC: Function to Pack CztProtIE_Cont_RLFInd_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Cont_RLFInd_IEs
(
CztProtIE_Cont_RLFInd_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Cont_RLFInd_IEs(param, mBuf)
CztProtIE_Cont_RLFInd_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtIE_Cont_RLFInd_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Field_RLFInd_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Cont_RLFInd_IEs */



/* 
* FUN : cmPkCztRLFInd
*  DESC: Function to Pack CztRLFInd structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztRLFInd
(
CztRLFInd *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztRLFInd(param, mBuf)
CztRLFInd *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztRLFInd) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtIE_Cont_RLFInd_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztRLFInd */



/* 
* FUN : cmPkCzt_ExtnSrvdCellsToActivate_Item_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnSrvdCellsToActivate_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnSrvdCellsToActivate_Item_ExtIEsCls
(
Czt_ExtnSrvdCellsToActivate_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnSrvdCellsToActivate_Item_ExtIEsCls(param, val, mBuf)
Czt_ExtnSrvdCellsToActivate_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnSrvdCellsToActivate_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnSrvdCellsToActivate_Item_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_SrvdCellsToActivate_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnField_SrvdCellsToActivate_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_SrvdCellsToActivate_Item_ExtIEs
(
CztProtExtnField_SrvdCellsToActivate_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_SrvdCellsToActivate_Item_ExtIEs(param, mBuf)
CztProtExtnField_SrvdCellsToActivate_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_SrvdCellsToActivate_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnSrvdCellsToActivate_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_SrvdCellsToActivate_Item_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_SrvdCellsToActivate_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_SrvdCellsToActivate_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_SrvdCellsToActivate_Item_ExtIEs
(
CztProtExtnCont_SrvdCellsToActivate_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_SrvdCellsToActivate_Item_ExtIEs(param, mBuf)
CztProtExtnCont_SrvdCellsToActivate_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_SrvdCellsToActivate_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_SrvdCellsToActivate_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_SrvdCellsToActivate_Item_ExtIEs */



/* 
* FUN : cmPkCztSrvdCellsToActivate_Item
*  DESC: Function to Pack CztSrvdCellsToActivate_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztSrvdCellsToActivate_Item
(
CztSrvdCellsToActivate_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztSrvdCellsToActivate_Item(param, mBuf)
CztSrvdCellsToActivate_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztSrvdCellsToActivate_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_SrvdCellsToActivate_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztECGI, &param->ecgi, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztSrvdCellsToActivate_Item */



/* 
* FUN : cmPkCztSrvdCellsToActivate
*  DESC: Function to Pack CztSrvdCellsToActivate structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztSrvdCellsToActivate
(
CztSrvdCellsToActivate *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztSrvdCellsToActivate(param, mBuf)
CztSrvdCellsToActivate *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztSrvdCellsToActivate) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztSrvdCellsToActivate_Item, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztSrvdCellsToActivate */



/* 
* FUN : cmPkCzt_ValueCellActvnRqst_IEsCls
*  DESC: Function to Pack Czt_ValueCellActvnRqst_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueCellActvnRqst_IEsCls
(
Czt_ValueCellActvnRqst_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueCellActvnRqst_IEsCls(param, val, mBuf)
Czt_ValueCellActvnRqst_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueCellActvnRqst_IEsCls) 
	
	switch (val)
	{
		case Cztid_SrvdCellsToActivate:
			CMCHKPK(cmPkCztSrvdCellsToActivate, &param->u.cztSrvdCellsToActivate, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueCellActvnRqst_IEsCls */



/* 
* FUN : cmPkCztProtIE_Field_CellActvnRqst_IEs
*  DESC: Function to Pack CztProtIE_Field_CellActvnRqst_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_CellActvnRqst_IEs
(
CztProtIE_Field_CellActvnRqst_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_CellActvnRqst_IEs(param, mBuf)
CztProtIE_Field_CellActvnRqst_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_CellActvnRqst_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueCellActvnRqst_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_CellActvnRqst_IEs */



/* 
* FUN : cmPkCztProtIE_Cont_CellActvnRqst_IEs
*  DESC: Function to Pack CztProtIE_Cont_CellActvnRqst_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Cont_CellActvnRqst_IEs
(
CztProtIE_Cont_CellActvnRqst_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Cont_CellActvnRqst_IEs(param, mBuf)
CztProtIE_Cont_CellActvnRqst_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtIE_Cont_CellActvnRqst_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Field_CellActvnRqst_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Cont_CellActvnRqst_IEs */



/* 
* FUN : cmPkCztCellActvnRqst
*  DESC: Function to Pack CztCellActvnRqst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztCellActvnRqst
(
CztCellActvnRqst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztCellActvnRqst(param, mBuf)
CztCellActvnRqst *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztCellActvnRqst) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtIE_Cont_CellActvnRqst_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztCellActvnRqst */



/* 
* FUN : cmPkCzt_ExtnActivatedCellLst_Item_ExtIEsCls
*  DESC: Function to Pack Czt_ExtnActivatedCellLst_Item_ExtIEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ExtnActivatedCellLst_Item_ExtIEsCls
(
Czt_ExtnActivatedCellLst_Item_ExtIEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ExtnActivatedCellLst_Item_ExtIEsCls(param, val, mBuf)
Czt_ExtnActivatedCellLst_Item_ExtIEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ExtnActivatedCellLst_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmPkCzt_ExtnActivatedCellLst_Item_ExtIEsCls */



/* 
* FUN : cmPkCztProtExtnField_ActivatedCellLst_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnField_ActivatedCellLst_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnField_ActivatedCellLst_Item_ExtIEs
(
CztProtExtnField_ActivatedCellLst_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnField_ActivatedCellLst_Item_ExtIEs(param, mBuf)
CztProtExtnField_ActivatedCellLst_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtExtnField_ActivatedCellLst_Item_ExtIEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ExtnActivatedCellLst_Item_ExtIEsCls(&param->extensionValue, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnField_ActivatedCellLst_Item_ExtIEs */



/* 
* FUN : cmPkCztProtExtnCont_ActivatedCellLst_Item_ExtIEs
*  DESC: Function to Pack CztProtExtnCont_ActivatedCellLst_Item_ExtIEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtExtnCont_ActivatedCellLst_Item_ExtIEs
(
CztProtExtnCont_ActivatedCellLst_Item_ExtIEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtExtnCont_ActivatedCellLst_Item_ExtIEs(param, mBuf)
CztProtExtnCont_ActivatedCellLst_Item_ExtIEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtExtnCont_ActivatedCellLst_Item_ExtIEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtExtnField_ActivatedCellLst_Item_ExtIEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtExtnCont_ActivatedCellLst_Item_ExtIEs */



/* 
* FUN : cmPkCztActivatedCellLst_Item
*  DESC: Function to Pack CztActivatedCellLst_Item structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztActivatedCellLst_Item
(
CztActivatedCellLst_Item *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztActivatedCellLst_Item(param, mBuf)
CztActivatedCellLst_Item *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztActivatedCellLst_Item) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtExtnCont_ActivatedCellLst_Item_ExtIEs, &param->iE_Extns, mBuf); 
		CMCHKPK(cmPkCztECGI, &param->ecgi, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztActivatedCellLst_Item */



/* 
* FUN : cmPkCztActivatedCellLst
*  DESC: Function to Pack CztActivatedCellLst structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztActivatedCellLst
(
CztActivatedCellLst *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztActivatedCellLst(param, mBuf)
CztActivatedCellLst *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztActivatedCellLst) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztActivatedCellLst_Item, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztActivatedCellLst */



/* 
* FUN : cmPkCzt_ValueCellActvnResp_IEsCls
*  DESC: Function to Pack Czt_ValueCellActvnResp_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueCellActvnResp_IEsCls
(
Czt_ValueCellActvnResp_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueCellActvnResp_IEsCls(param, val, mBuf)
Czt_ValueCellActvnResp_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueCellActvnResp_IEsCls) 
	
	switch (val)
	{
		case Cztid_ActivatedCellLst:
			CMCHKPK(cmPkCztActivatedCellLst, &param->u.cztActivatedCellLst, mBuf);
			break;
		case Cztid_CriticalityDiag:
			CMCHKPK(cmPkCztCriticalityDiag, &param->u.cztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueCellActvnResp_IEsCls */



/* 
* FUN : cmPkCztProtIE_Field_CellActvnResp_IEs
*  DESC: Function to Pack CztProtIE_Field_CellActvnResp_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_CellActvnResp_IEs
(
CztProtIE_Field_CellActvnResp_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_CellActvnResp_IEs(param, mBuf)
CztProtIE_Field_CellActvnResp_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_CellActvnResp_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueCellActvnResp_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_CellActvnResp_IEs */



/* 
* FUN : cmPkCztProtIE_Cont_CellActvnResp_IEs
*  DESC: Function to Pack CztProtIE_Cont_CellActvnResp_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Cont_CellActvnResp_IEs
(
CztProtIE_Cont_CellActvnResp_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Cont_CellActvnResp_IEs(param, mBuf)
CztProtIE_Cont_CellActvnResp_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtIE_Cont_CellActvnResp_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Field_CellActvnResp_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Cont_CellActvnResp_IEs */



/* 
* FUN : cmPkCztCellActvnResp
*  DESC: Function to Pack CztCellActvnResp structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztCellActvnResp
(
CztCellActvnResp *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztCellActvnResp(param, mBuf)
CztCellActvnResp *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztCellActvnResp) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtIE_Cont_CellActvnResp_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztCellActvnResp */



/* 
* FUN : cmPkCzt_ValueCellActvnFail_IEsCls
*  DESC: Function to Pack Czt_ValueCellActvnFail_IEsCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_ValueCellActvnFail_IEsCls
(
Czt_ValueCellActvnFail_IEsCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_ValueCellActvnFail_IEsCls(param, val, mBuf)
Czt_ValueCellActvnFail_IEsCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_ValueCellActvnFail_IEsCls) 
	
	switch (val)
	{
		case Cztid_Cause:
			CMCHKPK(cmPkCztCause, &param->u.cztCause, mBuf);
			break;
		case Cztid_CriticalityDiag:
			CMCHKPK(cmPkCztCriticalityDiag, &param->u.cztCriticalityDiag, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_ValueCellActvnFail_IEsCls */



/* 
* FUN : cmPkCztProtIE_Field_CellActvnFail_IEs
*  DESC: Function to Pack CztProtIE_Field_CellActvnFail_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Field_CellActvnFail_IEs
(
CztProtIE_Field_CellActvnFail_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Field_CellActvnFail_IEs(param, mBuf)
CztProtIE_Field_CellActvnFail_IEs *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztProtIE_Field_CellActvnFail_IEs) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_ValueCellActvnFail_IEsCls(&param->value, param->id.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProtIE_ID, &param->id, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Field_CellActvnFail_IEs */



/* 
* FUN : cmPkCztProtIE_Cont_CellActvnFail_IEs
*  DESC: Function to Pack CztProtIE_Cont_CellActvnFail_IEs structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztProtIE_Cont_CellActvnFail_IEs
(
CztProtIE_Cont_CellActvnFail_IEs *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztProtIE_Cont_CellActvnFail_IEs(param, mBuf)
CztProtIE_Cont_CellActvnFail_IEs *param;
Buffer *mBuf;
#endif
{ 
	Cntr i;
	TRC3(cmPkCztProtIE_Cont_CellActvnFail_IEs) 
	
	if( param->noComp.pres != NOTPRSNT ) 
	{ 
		for(i = param->noComp.val-1; i >= 0; i--) 
		{ 
			CMCHKPK(cmPkCztProtIE_Field_CellActvnFail_IEs, (&param->member[i]), mBuf);
		} 
	} 
	CMCHKPK(cmPkTknU16, &param->noComp, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztProtIE_Cont_CellActvnFail_IEs */



/* 
* FUN : cmPkCztCellActvnFail
*  DESC: Function to Pack CztCellActvnFail structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztCellActvnFail
(
CztCellActvnFail *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztCellActvnFail(param, mBuf)
CztCellActvnFail *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztCellActvnFail) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKPK(cmPkCztProtIE_Cont_CellActvnFail_IEs, &param->protocolIEs, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztCellActvnFail */



/* 
* FUN : cmPkCzt_InitiatingMsgCls
*  DESC: Function to Pack Czt_InitiatingMsgCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_InitiatingMsgCls
(
Czt_InitiatingMsgCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_InitiatingMsgCls(param, val, mBuf)
Czt_InitiatingMsgCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_InitiatingMsgCls) 
	
	switch (val)
	{
		case Cztid_handoverPrep:
			CMCHKPK(cmPkCztHovrRqst, &param->u.cztHovrRqst, mBuf);
			break;
		case Cztid_reset:
			CMCHKPK(cmPkCztResetRqst, &param->u.cztResetRqst, mBuf);
			break;
		case Cztid_x2Setup:
			CMCHKPK(cmPkCztX2SetupRqst, &param->u.cztX2SetupRqst, mBuf);
			break;
		case Cztid_resourceStatusRprtngInitiation:
			CMCHKPK(cmPkCztResStatusRqst, &param->u.cztResStatusRqst, mBuf);
			break;
		case Cztid_eNBConfigUpd:
			CMCHKPK(cmPkCztENBConfigUpd, &param->u.cztENBConfigUpd, mBuf);
			break;
		case Cztid_mobilitySettingsChange:
			CMCHKPK(cmPkCztMobilityChangeRqst, &param->u.cztMobilityChangeRqst, mBuf);
			break;
		case Cztid_cellActvn:
			CMCHKPK(cmPkCztCellActvnRqst, &param->u.cztCellActvnRqst, mBuf);
			break;
		case Cztid_snStatusTfr:
			CMCHKPK(cmPkCztSNStatusTfr, &param->u.cztSNStatusTfr, mBuf);
			break;
		case Cztid_uECntxtRls:
			CMCHKPK(cmPkCztUECntxtRls, &param->u.cztUECntxtRls, mBuf);
			break;
		case Cztid_handoverCancel:
			CMCHKPK(cmPkCztHovrCancel, &param->u.cztHovrCancel, mBuf);
			break;
		case Cztid_errorInd:
			CMCHKPK(cmPkCztErrInd, &param->u.cztErrInd, mBuf);
			break;
		case Cztid_resourceStatusRprtng:
			CMCHKPK(cmPkCztResStatusUpd, &param->u.cztResStatusUpd, mBuf);
			break;
		case Cztid_loadInd:
			CMCHKPK(cmPkCztLoadInform, &param->u.cztLoadInform, mBuf);
			break;
		case Cztid_privateMsg:
			CMCHKPK(cmPkCztPrivMsg, &param->u.cztPrivMsg, mBuf);
			break;
		case Cztid_rLFInd:
			CMCHKPK(cmPkCztRLFInd, &param->u.cztRLFInd, mBuf);
			break;
		case Cztid_handoverReport:
			CMCHKPK(cmPkCztHovrReport, &param->u.cztHovrReport, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_InitiatingMsgCls */



/* 
* FUN : cmPkCztInitiatingMsg
*  DESC: Function to Pack CztInitiatingMsg structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztInitiatingMsg
(
CztInitiatingMsg *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztInitiatingMsg(param, mBuf)
CztInitiatingMsg *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztInitiatingMsg) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_InitiatingMsgCls(&param->value, param->procedureCode.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProcedureCode, &param->procedureCode, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztInitiatingMsg */



/* 
* FUN : cmPkCzt_SuccessfulOutcomeCls
*  DESC: Function to Pack Czt_SuccessfulOutcomeCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_SuccessfulOutcomeCls
(
Czt_SuccessfulOutcomeCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_SuccessfulOutcomeCls(param, val, mBuf)
Czt_SuccessfulOutcomeCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_SuccessfulOutcomeCls) 
	
	switch (val)
	{
		case Cztid_handoverPrep:
			CMCHKPK(cmPkCztHovrRqstAckg, &param->u.cztHovrRqstAckg, mBuf);
			break;
		case Cztid_reset:
			CMCHKPK(cmPkCztResetResp, &param->u.cztResetResp, mBuf);
			break;
		case Cztid_x2Setup:
			CMCHKPK(cmPkCztX2SetupResp, &param->u.cztX2SetupResp, mBuf);
			break;
		case Cztid_resourceStatusRprtngInitiation:
			CMCHKPK(cmPkCztResStatusResp, &param->u.cztResStatusResp, mBuf);
			break;
		case Cztid_eNBConfigUpd:
			CMCHKPK(cmPkCztENBConfigUpdAckg, &param->u.cztENBConfigUpdAckg, mBuf);
			break;
		case Cztid_mobilitySettingsChange:
			CMCHKPK(cmPkCztMobilityChangeAckg, &param->u.cztMobilityChangeAckg, mBuf);
			break;
		case Cztid_cellActvn:
			CMCHKPK(cmPkCztCellActvnResp, &param->u.cztCellActvnResp, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_SuccessfulOutcomeCls */



/* 
* FUN : cmPkCztSuccessfulOutcome
*  DESC: Function to Pack CztSuccessfulOutcome structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztSuccessfulOutcome
(
CztSuccessfulOutcome *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztSuccessfulOutcome(param, mBuf)
CztSuccessfulOutcome *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztSuccessfulOutcome) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_SuccessfulOutcomeCls(&param->value, param->procedureCode.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProcedureCode, &param->procedureCode, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztSuccessfulOutcome */



/* 
* FUN : cmPkCzt_UnsuccessfulOutcomeCls
*  DESC: Function to Pack Czt_UnsuccessfulOutcomeCls structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCzt_UnsuccessfulOutcomeCls
(
Czt_UnsuccessfulOutcomeCls *param,
U32 val,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCzt_UnsuccessfulOutcomeCls(param, val, mBuf)
Czt_UnsuccessfulOutcomeCls *param;
U32 val;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCzt_UnsuccessfulOutcomeCls) 
	
	switch (val)
	{
		case Cztid_handoverPrep:
			CMCHKPK(cmPkCztHovrPrepFail, &param->u.cztHovrPrepFail, mBuf);
			break;
		case Cztid_x2Setup:
			CMCHKPK(cmPkCztX2SetupFail, &param->u.cztX2SetupFail, mBuf);
			break;
		case Cztid_resourceStatusRprtngInitiation:
			CMCHKPK(cmPkCztResStatusFail, &param->u.cztResStatusFail, mBuf);
			break;
		case Cztid_eNBConfigUpd:
			CMCHKPK(cmPkCztENBConfigUpdFail, &param->u.cztENBConfigUpdFail, mBuf);
			break;
		case Cztid_mobilitySettingsChange:
			CMCHKPK(cmPkCztMobilityChangeFail, &param->u.cztMobilityChangeFail, mBuf);
			break;
		case Cztid_cellActvn:
			CMCHKPK(cmPkCztCellActvnFail, &param->u.cztCellActvnFail, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmPkCzt_UnsuccessfulOutcomeCls */



/* 
* FUN : cmPkCztUnsuccessfulOutcome
*  DESC: Function to Pack CztUnsuccessfulOutcome structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztUnsuccessfulOutcome
(
CztUnsuccessfulOutcome *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztUnsuccessfulOutcome(param, mBuf)
CztUnsuccessfulOutcome *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztUnsuccessfulOutcome) 
	
	if( param->pres.pres != NOTPRSNT ) 
	{
		{
			S16 ret;
			ret = cmPkCzt_UnsuccessfulOutcomeCls(&param->value, param->procedureCode.val, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
		CMCHKPK(cmPkCztCriticality, &param->criticality, mBuf); 
		CMCHKPK(cmPkCztProcedureCode, &param->procedureCode, mBuf); 
	}
	CMCHKPK(cmPkTknPres, &param->pres, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztUnsuccessfulOutcome */



/* 
* FUN : cmPkCztX2AP_PDU
*  DESC: Function to Pack CztX2AP_PDU structure
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmPkCztX2AP_PDU
(
CztX2AP_PDU *param,
Buffer *mBuf
)
#else 
PUBLIC S16 cmPkCztX2AP_PDU(param, mBuf)
CztX2AP_PDU *param;
Buffer *mBuf;
#endif
{
	
	TRC3(cmPkCztX2AP_PDU) 
	
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case X2AP_PDU_UNSUCCESSFULOUTCOME :
				CMCHKPK(cmPkCztUnsuccessfulOutcome, &param->val.unsuccessfulOutcome, mBuf); 
				break;
			case X2AP_PDU_SUCCESSFULOUTCOME :
				CMCHKPK(cmPkCztSuccessfulOutcome, &param->val.successfulOutcome, mBuf); 
				break;
			case X2AP_PDU_INITIATINGMSG :
				CMCHKPK(cmPkCztInitiatingMsg, &param->val.initiatingMsg, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	CMCHKPK(cmPkTknU8, &param->choice, mBuf); 
	RETVALUE(ROK);
}	 /* End of function cmPkCztX2AP_PDU */


#ifdef __cplusplus
}
#endif /*__cplusplus*/
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
$SID$        ---      chebli         1. Updated DB for X2AP R11 for TotaleNodeB GA3.0
$SID$        ---      chebli         1. Updated DB for X2AP R11.8.0 for TotaleNodeB GA5.0
*********************************************************************91*/

