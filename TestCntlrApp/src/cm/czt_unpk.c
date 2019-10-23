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
#include <czt_unpk.x>

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
#include <czt_unpk.x>

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/
#define cmUnpkCztCriticality cmUnpkTknU32

#define cmUnpkCztPresence cmUnpkTknU32

#define cmUnpkCztPrivIE_IDlocal cmUnpkTknU32 


/*
* FUN : cmUnpkCztPrivIE_ID
*  DESC: Function to Unpack CztPrivIE_ID structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztPrivIE_ID
(
CztPrivIE_ID *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztPrivIE_ID(param, ptr, mBuf)
CztPrivIE_ID *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztPrivIE_ID) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case PRIVIE_ID_LOCAL :
				CMCHKUNPK(cmUnpkCztPrivIE_IDlocal, &param->val.local, mBuf); 
				break;
			case PRIVIE_ID_GLOBAL :
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztPrivIE_ID */

#define cmUnpkCztProcedureCode cmUnpkTknU32 
#define cmUnpkCztProtIE_ID cmUnpkTknU32 
#define cmUnpkCztTrgMsg cmUnpkTknU32

#define cmUnpkCztABSInformFDDabs_pattern_info cmUnpkTknStrBSXL 
#define cmUnpkCztABSInformFDDnumberOfCellSpecificAntennaPorts cmUnpkTknU32

#define cmUnpkCztABSInformFDDmeasurement_subset cmUnpkTknStrBSXL 


/*
* FUN : cmUnpkCzt_ExtnABSInformFDD_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnABSInformFDD_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnABSInformFDD_ExtIEsCls
(
Czt_ExtnABSInformFDD_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnABSInformFDD_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnABSInformFDD_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnABSInformFDD_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnABSInformFDD_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_ABSInformFDD_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_ABSInformFDD_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_ABSInformFDD_ExtIEs
(
CztProtExtnField_ABSInformFDD_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_ABSInformFDD_ExtIEs(param, ptr, mBuf)
CztProtExtnField_ABSInformFDD_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_ABSInformFDD_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnABSInformFDD_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_ABSInformFDD_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_ABSInformFDD_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_ABSInformFDD_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_ABSInformFDD_ExtIEs
(
CztProtExtnCont_ABSInformFDD_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_ABSInformFDD_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_ABSInformFDD_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_ABSInformFDD_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_ABSInformFDD_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_ABSInformFDD_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_ABSInformFDD_ExtIEs */



/*
* FUN : cmUnpkCztABSInformFDD
*  DESC: Function to Unpack CztABSInformFDD structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztABSInformFDD
(
CztABSInformFDD *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztABSInformFDD(param, ptr, mBuf)
CztABSInformFDD *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztABSInformFDD) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztABSInformFDDabs_pattern_info, &param->abs_pattern_info, ptr, mBuf); 
		CMCHKUNPK(cmUnpkCztABSInformFDDnumberOfCellSpecificAntennaPorts, &param->numberOfCellSpecificAntennaPorts, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztABSInformFDDmeasurement_subset, &param->measurement_subset, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_ABSInformFDD_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztABSInformFDD */

#define cmUnpkCztABSInformTDDabs_pattern_info cmUnpkTknStrBSXL 
#define cmUnpkCztABSInformTDDnumberOfCellSpecificAntennaPorts cmUnpkTknU32

#define cmUnpkCztABSInformTDDmeasurement_subset cmUnpkTknStrBSXL 


/*
* FUN : cmUnpkCzt_ExtnABSInformTDD_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnABSInformTDD_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnABSInformTDD_ExtIEsCls
(
Czt_ExtnABSInformTDD_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnABSInformTDD_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnABSInformTDD_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnABSInformTDD_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnABSInformTDD_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_ABSInformTDD_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_ABSInformTDD_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_ABSInformTDD_ExtIEs
(
CztProtExtnField_ABSInformTDD_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_ABSInformTDD_ExtIEs(param, ptr, mBuf)
CztProtExtnField_ABSInformTDD_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_ABSInformTDD_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnABSInformTDD_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_ABSInformTDD_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_ABSInformTDD_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_ABSInformTDD_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_ABSInformTDD_ExtIEs
(
CztProtExtnCont_ABSInformTDD_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_ABSInformTDD_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_ABSInformTDD_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_ABSInformTDD_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_ABSInformTDD_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_ABSInformTDD_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_ABSInformTDD_ExtIEs */



/*
* FUN : cmUnpkCztABSInformTDD
*  DESC: Function to Unpack CztABSInformTDD structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztABSInformTDD
(
CztABSInformTDD *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztABSInformTDD(param, ptr, mBuf)
CztABSInformTDD *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztABSInformTDD) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztABSInformTDDabs_pattern_info, &param->abs_pattern_info, ptr, mBuf); 
		CMCHKUNPK(cmUnpkCztABSInformTDDnumberOfCellSpecificAntennaPorts, &param->numberOfCellSpecificAntennaPorts, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztABSInformTDDmeasurement_subset, &param->measurement_subset, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_ABSInformTDD_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztABSInformTDD */



/*
* FUN : cmUnpkCztABSInform
*  DESC: Function to Unpack CztABSInform structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztABSInform
(
CztABSInform *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztABSInform(param, ptr, mBuf)
CztABSInform *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztABSInform) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case ABSINFORM_FDD :
				CMCHKUNPKPTR(cmUnpkCztABSInformFDD, &param->val.fdd, ptr, mBuf); 
				break;
			case ABSINFORM_TDD :
				CMCHKUNPKPTR(cmUnpkCztABSInformTDD, &param->val.tdd, ptr, mBuf); 
				break;
			case ABSINFORM_ABS_INACTIVE :
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztABSInform */

#define cmUnpkCztDL_ABS_status cmUnpkTknU32 
#define cmUnpkCztUsableABSInformFDDusable_abs_pattern_info cmUnpkTknStrBSXL 


/*
* FUN : cmUnpkCzt_ExtnUsableABSInformFDD_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnUsableABSInformFDD_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnUsableABSInformFDD_ExtIEsCls
(
Czt_ExtnUsableABSInformFDD_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnUsableABSInformFDD_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnUsableABSInformFDD_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnUsableABSInformFDD_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnUsableABSInformFDD_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_UsableABSInformFDD_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_UsableABSInformFDD_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_UsableABSInformFDD_ExtIEs
(
CztProtExtnField_UsableABSInformFDD_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_UsableABSInformFDD_ExtIEs(param, ptr, mBuf)
CztProtExtnField_UsableABSInformFDD_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_UsableABSInformFDD_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnUsableABSInformFDD_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_UsableABSInformFDD_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_UsableABSInformFDD_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_UsableABSInformFDD_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_UsableABSInformFDD_ExtIEs
(
CztProtExtnCont_UsableABSInformFDD_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_UsableABSInformFDD_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_UsableABSInformFDD_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_UsableABSInformFDD_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_UsableABSInformFDD_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_UsableABSInformFDD_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_UsableABSInformFDD_ExtIEs */



/*
* FUN : cmUnpkCztUsableABSInformFDD
*  DESC: Function to Unpack CztUsableABSInformFDD structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztUsableABSInformFDD
(
CztUsableABSInformFDD *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztUsableABSInformFDD(param, ptr, mBuf)
CztUsableABSInformFDD *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztUsableABSInformFDD) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztUsableABSInformFDDusable_abs_pattern_info, &param->usable_abs_pattern_info, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_UsableABSInformFDD_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztUsableABSInformFDD */

#define cmUnpkCztUsableABSInformTDDusaable_abs_pattern_info cmUnpkTknStrBSXL 


/*
* FUN : cmUnpkCzt_ExtnUsableABSInformTDD_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnUsableABSInformTDD_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnUsableABSInformTDD_ExtIEsCls
(
Czt_ExtnUsableABSInformTDD_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnUsableABSInformTDD_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnUsableABSInformTDD_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnUsableABSInformTDD_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnUsableABSInformTDD_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_UsableABSInformTDD_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_UsableABSInformTDD_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_UsableABSInformTDD_ExtIEs
(
CztProtExtnField_UsableABSInformTDD_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_UsableABSInformTDD_ExtIEs(param, ptr, mBuf)
CztProtExtnField_UsableABSInformTDD_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_UsableABSInformTDD_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnUsableABSInformTDD_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_UsableABSInformTDD_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_UsableABSInformTDD_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_UsableABSInformTDD_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_UsableABSInformTDD_ExtIEs
(
CztProtExtnCont_UsableABSInformTDD_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_UsableABSInformTDD_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_UsableABSInformTDD_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_UsableABSInformTDD_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_UsableABSInformTDD_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_UsableABSInformTDD_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_UsableABSInformTDD_ExtIEs */



/*
* FUN : cmUnpkCztUsableABSInformTDD
*  DESC: Function to Unpack CztUsableABSInformTDD structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztUsableABSInformTDD
(
CztUsableABSInformTDD *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztUsableABSInformTDD(param, ptr, mBuf)
CztUsableABSInformTDD *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztUsableABSInformTDD) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztUsableABSInformTDDusaable_abs_pattern_info, &param->usaable_abs_pattern_info, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_UsableABSInformTDD_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztUsableABSInformTDD */



/*
* FUN : cmUnpkCztUsableABSInform
*  DESC: Function to Unpack CztUsableABSInform structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztUsableABSInform
(
CztUsableABSInform *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztUsableABSInform(param, ptr, mBuf)
CztUsableABSInform *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztUsableABSInform) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case USABLEABSINFORM_FDD :
				CMCHKUNPKPTR(cmUnpkCztUsableABSInformFDD, &param->val.fdd, ptr, mBuf); 
				break;
			case USABLEABSINFORM_TDD :
				CMCHKUNPKPTR(cmUnpkCztUsableABSInformTDD, &param->val.tdd, ptr, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztUsableABSInform */



/*
* FUN : cmUnpkCzt_ExtnABS_Status_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnABS_Status_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnABS_Status_ExtIEsCls
(
Czt_ExtnABS_Status_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnABS_Status_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnABS_Status_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnABS_Status_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnABS_Status_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_ABS_Status_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_ABS_Status_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_ABS_Status_ExtIEs
(
CztProtExtnField_ABS_Status_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_ABS_Status_ExtIEs(param, ptr, mBuf)
CztProtExtnField_ABS_Status_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_ABS_Status_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnABS_Status_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_ABS_Status_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_ABS_Status_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_ABS_Status_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_ABS_Status_ExtIEs
(
CztProtExtnCont_ABS_Status_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_ABS_Status_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_ABS_Status_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_ABS_Status_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_ABS_Status_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_ABS_Status_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_ABS_Status_ExtIEs */



/*
* FUN : cmUnpkCztABS_Status
*  DESC: Function to Unpack CztABS_Status structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztABS_Status
(
CztABS_Status *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztABS_Status(param, ptr, mBuf)
CztABS_Status *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztABS_Status) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztDL_ABS_status, &param->dL_ABS_status, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztUsableABSInform, &param->usableABSInform, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_ABS_Status_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztABS_Status */

#define cmUnpkCztAdditionalSpecialSubframePatterns cmUnpkTknU32

#define cmUnpkCztCyclicPrefixDL cmUnpkTknU32

#define cmUnpkCztCyclicPrefixUL cmUnpkTknU32



/*
* FUN : cmUnpkCzt_ExtnAdditionalSpecialSubframe_Info_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnAdditionalSpecialSubframe_Info_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnAdditionalSpecialSubframe_Info_ExtIEsCls
(
Czt_ExtnAdditionalSpecialSubframe_Info_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnAdditionalSpecialSubframe_Info_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnAdditionalSpecialSubframe_Info_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnAdditionalSpecialSubframe_Info_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnAdditionalSpecialSubframe_Info_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_AdditionalSpecialSubframe_Info_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_AdditionalSpecialSubframe_Info_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_AdditionalSpecialSubframe_Info_ExtIEs
(
CztProtExtnField_AdditionalSpecialSubframe_Info_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_AdditionalSpecialSubframe_Info_ExtIEs(param, ptr, mBuf)
CztProtExtnField_AdditionalSpecialSubframe_Info_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_AdditionalSpecialSubframe_Info_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnAdditionalSpecialSubframe_Info_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_AdditionalSpecialSubframe_Info_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEs
(
CztProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_AdditionalSpecialSubframe_Info_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_AdditionalSpecialSubframe_Info_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEs */



/*
* FUN : cmUnpkCztAdditionalSpecialSubframe_Info
*  DESC: Function to Unpack CztAdditionalSpecialSubframe_Info structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztAdditionalSpecialSubframe_Info
(
CztAdditionalSpecialSubframe_Info *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztAdditionalSpecialSubframe_Info(param, ptr, mBuf)
CztAdditionalSpecialSubframe_Info *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztAdditionalSpecialSubframe_Info) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztAdditionalSpecialSubframePatterns, &param->additionalspecialSubframePatterns, mBuf); 
		CMCHKUNPK(cmUnpkCztCyclicPrefixDL, &param->cyclicPrefixDL, mBuf); 
		CMCHKUNPK(cmUnpkCztCyclicPrefixUL, &param->cyclicPrefixUL, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_AdditionalSpecialSubframe_Info_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztAdditionalSpecialSubframe_Info */

#define cmUnpkCztKey_eNodeB_Star cmUnpkTknStrBSXL 
#define cmUnpkCztNextHopChainingCount cmUnpkTknU32 


/*
* FUN : cmUnpkCzt_ExtnAS_SecurInform_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnAS_SecurInform_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnAS_SecurInform_ExtIEsCls
(
Czt_ExtnAS_SecurInform_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnAS_SecurInform_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnAS_SecurInform_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnAS_SecurInform_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnAS_SecurInform_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_AS_SecurInform_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_AS_SecurInform_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_AS_SecurInform_ExtIEs
(
CztProtExtnField_AS_SecurInform_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_AS_SecurInform_ExtIEs(param, ptr, mBuf)
CztProtExtnField_AS_SecurInform_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_AS_SecurInform_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnAS_SecurInform_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_AS_SecurInform_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_AS_SecurInform_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_AS_SecurInform_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_AS_SecurInform_ExtIEs
(
CztProtExtnCont_AS_SecurInform_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_AS_SecurInform_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_AS_SecurInform_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_AS_SecurInform_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_AS_SecurInform_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_AS_SecurInform_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_AS_SecurInform_ExtIEs */



/*
* FUN : cmUnpkCztAS_SecurInform
*  DESC: Function to Unpack CztAS_SecurInform structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztAS_SecurInform
(
CztAS_SecurInform *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztAS_SecurInform(param, ptr, mBuf)
CztAS_SecurInform *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztAS_SecurInform) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztKey_eNodeB_Star, &param->key_eNodeB_star, ptr, mBuf); 
		CMCHKUNPK(cmUnpkCztNextHopChainingCount, &param->nextHopChainingCount, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_AS_SecurInform_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztAS_SecurInform */

#define cmUnpkCztPriorityLvl cmUnpkTknU32 
#define cmUnpkCztPre_emptionCapblty cmUnpkTknU32

#define cmUnpkCztPre_emptionVulnerability cmUnpkTknU32



/*
* FUN : cmUnpkCzt_ExtnAllocnAndRetentionPriority_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnAllocnAndRetentionPriority_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnAllocnAndRetentionPriority_ExtIEsCls
(
Czt_ExtnAllocnAndRetentionPriority_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnAllocnAndRetentionPriority_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnAllocnAndRetentionPriority_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnAllocnAndRetentionPriority_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnAllocnAndRetentionPriority_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_AllocnAndRetentionPriority_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_AllocnAndRetentionPriority_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_AllocnAndRetentionPriority_ExtIEs
(
CztProtExtnField_AllocnAndRetentionPriority_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_AllocnAndRetentionPriority_ExtIEs(param, ptr, mBuf)
CztProtExtnField_AllocnAndRetentionPriority_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_AllocnAndRetentionPriority_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnAllocnAndRetentionPriority_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_AllocnAndRetentionPriority_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_AllocnAndRetentionPriority_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_AllocnAndRetentionPriority_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_AllocnAndRetentionPriority_ExtIEs
(
CztProtExtnCont_AllocnAndRetentionPriority_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_AllocnAndRetentionPriority_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_AllocnAndRetentionPriority_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_AllocnAndRetentionPriority_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_AllocnAndRetentionPriority_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_AllocnAndRetentionPriority_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_AllocnAndRetentionPriority_ExtIEs */



/*
* FUN : cmUnpkCztAllocnAndRetentionPriority
*  DESC: Function to Unpack CztAllocnAndRetentionPriority structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztAllocnAndRetentionPriority
(
CztAllocnAndRetentionPriority *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztAllocnAndRetentionPriority(param, ptr, mBuf)
CztAllocnAndRetentionPriority *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztAllocnAndRetentionPriority) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztPriorityLvl, &param->priorityLvl, mBuf); 
		CMCHKUNPK(cmUnpkCztPre_emptionCapblty, &param->pre_emptionCapblty, mBuf); 
		CMCHKUNPK(cmUnpkCztPre_emptionVulnerability, &param->pre_emptionVulnerability, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_AllocnAndRetentionPriority_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztAllocnAndRetentionPriority */

#define cmUnpkCztPLMN_Identity cmUnpkTknStrOSXL 
#define cmUnpkCztEUTRANCellIdentifier cmUnpkTknBStr32 


/*
* FUN : cmUnpkCzt_ExtnECGI_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnECGI_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnECGI_ExtIEsCls
(
Czt_ExtnECGI_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnECGI_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnECGI_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnECGI_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnECGI_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_ECGI_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_ECGI_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_ECGI_ExtIEs
(
CztProtExtnField_ECGI_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_ECGI_ExtIEs(param, ptr, mBuf)
CztProtExtnField_ECGI_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_ECGI_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnECGI_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_ECGI_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_ECGI_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_ECGI_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_ECGI_ExtIEs
(
CztProtExtnCont_ECGI_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_ECGI_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_ECGI_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_ECGI_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_ECGI_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_ECGI_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_ECGI_ExtIEs */



/*
* FUN : cmUnpkCztECGI
*  DESC: Function to Unpack CztECGI structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztECGI
(
CztECGI *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztECGI(param, ptr, mBuf)
CztECGI *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztECGI) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CZUCHKUNPKPTR(cmUnpkCztPLMN_Identity, &param->pLMN_Identity, ptr, mBuf); 
		CMCHKUNPK(cmUnpkCztEUTRANCellIdentifier, &param->eUTRANcellIdentifier, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_ECGI_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztECGI */



/*
* FUN : cmUnpkCztCellIdLstforMDT
*  DESC: Function to Unpack CztCellIdLstforMDT structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztCellIdLstforMDT
(
CztCellIdLstforMDT *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztCellIdLstforMDT(param, ptr, mBuf)
CztCellIdLstforMDT *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztCellIdLstforMDT) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztECGI)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztECGI, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztCellIdLstforMDT */



/*
* FUN : cmUnpkCzt_ExtnCellBasedMDT_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnCellBasedMDT_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnCellBasedMDT_ExtIEsCls
(
Czt_ExtnCellBasedMDT_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnCellBasedMDT_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnCellBasedMDT_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnCellBasedMDT_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnCellBasedMDT_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_CellBasedMDT_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_CellBasedMDT_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_CellBasedMDT_ExtIEs
(
CztProtExtnField_CellBasedMDT_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_CellBasedMDT_ExtIEs(param, ptr, mBuf)
CztProtExtnField_CellBasedMDT_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_CellBasedMDT_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnCellBasedMDT_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_CellBasedMDT_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_CellBasedMDT_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_CellBasedMDT_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_CellBasedMDT_ExtIEs
(
CztProtExtnCont_CellBasedMDT_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_CellBasedMDT_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_CellBasedMDT_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_CellBasedMDT_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_CellBasedMDT_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_CellBasedMDT_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_CellBasedMDT_ExtIEs */



/*
* FUN : cmUnpkCztCellBasedMDT
*  DESC: Function to Unpack CztCellBasedMDT structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztCellBasedMDT
(
CztCellBasedMDT *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztCellBasedMDT(param, ptr, mBuf)
CztCellBasedMDT *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztCellBasedMDT) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztCellIdLstforMDT, &param->cellIdLstforMDT, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_CellBasedMDT_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztCellBasedMDT */

#define cmUnpkCztTAC cmUnpkTknStr4 


/*
* FUN : cmUnpkCztTALstforMDT
*  DESC: Function to Unpack CztTALstforMDT structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztTALstforMDT
(
CztTALstforMDT *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztTALstforMDT(param, ptr, mBuf)
CztTALstforMDT *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztTALstforMDT) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztTAC)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPK(cmUnpkCztTAC, &(param->member[i]), mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztTALstforMDT */



/*
* FUN : cmUnpkCzt_ExtnTABasedMDT_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnTABasedMDT_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnTABasedMDT_ExtIEsCls
(
Czt_ExtnTABasedMDT_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnTABasedMDT_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnTABasedMDT_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnTABasedMDT_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnTABasedMDT_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_TABasedMDT_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_TABasedMDT_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_TABasedMDT_ExtIEs
(
CztProtExtnField_TABasedMDT_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_TABasedMDT_ExtIEs(param, ptr, mBuf)
CztProtExtnField_TABasedMDT_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_TABasedMDT_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnTABasedMDT_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_TABasedMDT_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_TABasedMDT_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_TABasedMDT_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_TABasedMDT_ExtIEs
(
CztProtExtnCont_TABasedMDT_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_TABasedMDT_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_TABasedMDT_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_TABasedMDT_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_TABasedMDT_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_TABasedMDT_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_TABasedMDT_ExtIEs */



/*
* FUN : cmUnpkCztTABasedMDT
*  DESC: Function to Unpack CztTABasedMDT structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztTABasedMDT
(
CztTABasedMDT *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztTABasedMDT(param, ptr, mBuf)
CztTABasedMDT *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztTABasedMDT) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztTALstforMDT, &param->tALstforMDT, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_TABasedMDT_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztTABasedMDT */



/*
* FUN : cmUnpkCzt_ExtnTAI_Item_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnTAI_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnTAI_Item_ExtIEsCls
(
Czt_ExtnTAI_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnTAI_Item_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnTAI_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnTAI_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnTAI_Item_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_TAI_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_TAI_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_TAI_Item_ExtIEs
(
CztProtExtnField_TAI_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_TAI_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnField_TAI_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_TAI_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnTAI_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_TAI_Item_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_TAI_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_TAI_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_TAI_Item_ExtIEs
(
CztProtExtnCont_TAI_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_TAI_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_TAI_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_TAI_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_TAI_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_TAI_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_TAI_Item_ExtIEs */



/*
* FUN : cmUnpkCztTAI_Item
*  DESC: Function to Unpack CztTAI_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztTAI_Item
(
CztTAI_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztTAI_Item(param, ptr, mBuf)
CztTAI_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztTAI_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztTAC, &param->tAC, mBuf); 
		CZUCHKUNPKPTR(cmUnpkCztPLMN_Identity, &param->pLMN_Identity, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_TAI_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztTAI_Item */



/*
* FUN : cmUnpkCztTAILstforMDT
*  DESC: Function to Unpack CztTAILstforMDT structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztTAILstforMDT
(
CztTAILstforMDT *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztTAILstforMDT(param, ptr, mBuf)
CztTAILstforMDT *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztTAILstforMDT) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztTAI_Item)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztTAI_Item, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztTAILstforMDT */



/*
* FUN : cmUnpkCzt_ExtnTAIBasedMDT_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnTAIBasedMDT_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnTAIBasedMDT_ExtIEsCls
(
Czt_ExtnTAIBasedMDT_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnTAIBasedMDT_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnTAIBasedMDT_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnTAIBasedMDT_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnTAIBasedMDT_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_TAIBasedMDT_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_TAIBasedMDT_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_TAIBasedMDT_ExtIEs
(
CztProtExtnField_TAIBasedMDT_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_TAIBasedMDT_ExtIEs(param, ptr, mBuf)
CztProtExtnField_TAIBasedMDT_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_TAIBasedMDT_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnTAIBasedMDT_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_TAIBasedMDT_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_TAIBasedMDT_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_TAIBasedMDT_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_TAIBasedMDT_ExtIEs
(
CztProtExtnCont_TAIBasedMDT_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_TAIBasedMDT_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_TAIBasedMDT_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_TAIBasedMDT_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_TAIBasedMDT_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_TAIBasedMDT_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_TAIBasedMDT_ExtIEs */



/*
* FUN : cmUnpkCztTAIBasedMDT
*  DESC: Function to Unpack CztTAIBasedMDT structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztTAIBasedMDT
(
CztTAIBasedMDT *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztTAIBasedMDT(param, ptr, mBuf)
CztTAIBasedMDT *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztTAIBasedMDT) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztTAILstforMDT, &param->tAILstforMDT, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_TAIBasedMDT_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztTAIBasedMDT */



/*
* FUN : cmUnpkCztAreaScopeOfMDT
*  DESC: Function to Unpack CztAreaScopeOfMDT structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztAreaScopeOfMDT
(
CztAreaScopeOfMDT *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztAreaScopeOfMDT(param, ptr, mBuf)
CztAreaScopeOfMDT *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztAreaScopeOfMDT) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case AREASCOPEOFMDT_CELLBASED :
				CMCHKUNPKPTR(cmUnpkCztCellBasedMDT, &param->val.cellBased, ptr, mBuf); 
				break;
			case AREASCOPEOFMDT_TABASED :
				CMCHKUNPKPTR(cmUnpkCztTABasedMDT, &param->val.tABased, ptr, mBuf); 
				break;
			case AREASCOPEOFMDT_PLMNWIDE :
				break;
			case AREASCOPEOFMDT_TAIBASED :
				CMCHKUNPKPTR(cmUnpkCztTAIBasedMDT, &param->val.tAIBased, ptr, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztAreaScopeOfMDT */

#define cmUnpkCztBitRate cmUnpkTknStrOSXL 


/*
* FUN : cmUnpkCztBroadcastPLMNs_Item
*  DESC: Function to Unpack CztBroadcastPLMNs_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztBroadcastPLMNs_Item
(
CztBroadcastPLMNs_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztBroadcastPLMNs_Item(param, ptr, mBuf)
CztBroadcastPLMNs_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztBroadcastPLMNs_Item) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztPLMN_Identity)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CZUCHKUNPKPTR(cmUnpkCztPLMN_Identity, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztBroadcastPLMNs_Item */

#define cmUnpkCztCapacityValue cmUnpkTknU32 
#define cmUnpkCztCellCapacityClassValue cmUnpkTknU32 
#define cmUnpkCztCauseRadioNw cmUnpkTknU32

#define cmUnpkCztCauseTport cmUnpkTknU32

#define cmUnpkCztCauseProt cmUnpkTknU32

#define cmUnpkCztCauseMisc cmUnpkTknU32



/*
* FUN : cmUnpkCztCause
*  DESC: Function to Unpack CztCause structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztCause
(
CztCause *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztCause(param, ptr, mBuf)
CztCause *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztCause) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case CAUSE_RADIONW :
				CMCHKUNPK(cmUnpkCztCauseRadioNw, &param->val.radioNw, mBuf); 
				break;
			case CAUSE_TRANSPORT :
				CMCHKUNPK(cmUnpkCztCauseTport, &param->val.transport, mBuf); 
				break;
			case CZT_CAUSE_PROTOCOL :
				CMCHKUNPK(cmUnpkCztCauseProt, &param->val.protocol, mBuf); 
				break;
			case CZT_CAUSE_MISC :
				CMCHKUNPK(cmUnpkCztCauseMisc, &param->val.misc, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztCause */

#define cmUnpkCztCell_Size cmUnpkTknU32



/*
* FUN : cmUnpkCzt_ExtnCellTyp_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnCellTyp_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnCellTyp_ExtIEsCls
(
Czt_ExtnCellTyp_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnCellTyp_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnCellTyp_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnCellTyp_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnCellTyp_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_CellTyp_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_CellTyp_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_CellTyp_ExtIEs
(
CztProtExtnField_CellTyp_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_CellTyp_ExtIEs(param, ptr, mBuf)
CztProtExtnField_CellTyp_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_CellTyp_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnCellTyp_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_CellTyp_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_CellTyp_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_CellTyp_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_CellTyp_ExtIEs
(
CztProtExtnCont_CellTyp_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_CellTyp_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_CellTyp_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_CellTyp_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_CellTyp_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_CellTyp_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_CellTyp_ExtIEs */



/*
* FUN : cmUnpkCztCellTyp
*  DESC: Function to Unpack CztCellTyp structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztCellTyp
(
CztCellTyp *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztCellTyp(param, ptr, mBuf)
CztCellTyp *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztCellTyp) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztCell_Size, &param->cell_Size, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_CellTyp_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztCellTyp */



/*
* FUN : cmUnpkCzt_ExtnCompositeAvailableCapacity_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnCompositeAvailableCapacity_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnCompositeAvailableCapacity_ExtIEsCls
(
Czt_ExtnCompositeAvailableCapacity_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnCompositeAvailableCapacity_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnCompositeAvailableCapacity_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnCompositeAvailableCapacity_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnCompositeAvailableCapacity_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_CompositeAvailableCapacity_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_CompositeAvailableCapacity_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_CompositeAvailableCapacity_ExtIEs
(
CztProtExtnField_CompositeAvailableCapacity_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_CompositeAvailableCapacity_ExtIEs(param, ptr, mBuf)
CztProtExtnField_CompositeAvailableCapacity_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_CompositeAvailableCapacity_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnCompositeAvailableCapacity_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_CompositeAvailableCapacity_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_CompositeAvailableCapacity_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_CompositeAvailableCapacity_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_CompositeAvailableCapacity_ExtIEs
(
CztProtExtnCont_CompositeAvailableCapacity_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_CompositeAvailableCapacity_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_CompositeAvailableCapacity_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_CompositeAvailableCapacity_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_CompositeAvailableCapacity_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_CompositeAvailableCapacity_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_CompositeAvailableCapacity_ExtIEs */



/*
* FUN : cmUnpkCztCompositeAvailableCapacity
*  DESC: Function to Unpack CztCompositeAvailableCapacity structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztCompositeAvailableCapacity
(
CztCompositeAvailableCapacity *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztCompositeAvailableCapacity(param, ptr, mBuf)
CztCompositeAvailableCapacity *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztCompositeAvailableCapacity) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztCellCapacityClassValue, &param->cellCapacityClassValue, mBuf); 
		CMCHKUNPK(cmUnpkCztCapacityValue, &param->capacityValue, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_CompositeAvailableCapacity_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztCompositeAvailableCapacity */



/*
* FUN : cmUnpkCzt_ExtnCompositeAvailableCapacityGroup_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnCompositeAvailableCapacityGroup_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnCompositeAvailableCapacityGroup_ExtIEsCls
(
Czt_ExtnCompositeAvailableCapacityGroup_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnCompositeAvailableCapacityGroup_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnCompositeAvailableCapacityGroup_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnCompositeAvailableCapacityGroup_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnCompositeAvailableCapacityGroup_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_CompositeAvailableCapacityGroup_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_CompositeAvailableCapacityGroup_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_CompositeAvailableCapacityGroup_ExtIEs
(
CztProtExtnField_CompositeAvailableCapacityGroup_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_CompositeAvailableCapacityGroup_ExtIEs(param, ptr, mBuf)
CztProtExtnField_CompositeAvailableCapacityGroup_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_CompositeAvailableCapacityGroup_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnCompositeAvailableCapacityGroup_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_CompositeAvailableCapacityGroup_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_CompositeAvailableCapacityGroup_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_CompositeAvailableCapacityGroup_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_CompositeAvailableCapacityGroup_ExtIEs
(
CztProtExtnCont_CompositeAvailableCapacityGroup_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_CompositeAvailableCapacityGroup_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_CompositeAvailableCapacityGroup_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_CompositeAvailableCapacityGroup_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_CompositeAvailableCapacityGroup_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_CompositeAvailableCapacityGroup_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_CompositeAvailableCapacityGroup_ExtIEs */



/*
* FUN : cmUnpkCztCompositeAvailableCapacityGroup
*  DESC: Function to Unpack CztCompositeAvailableCapacityGroup structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztCompositeAvailableCapacityGroup
(
CztCompositeAvailableCapacityGroup *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztCompositeAvailableCapacityGroup(param, ptr, mBuf)
CztCompositeAvailableCapacityGroup *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztCompositeAvailableCapacityGroup) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztCompositeAvailableCapacity, &param->dL_CompositeAvailableCapacity, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztCompositeAvailableCapacity, &param->uL_CompositeAvailableCapacity, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_CompositeAvailableCapacityGroup_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztCompositeAvailableCapacityGroup */

#define cmUnpkCztPDCP_SN cmUnpkTknU32 
#define cmUnpkCztHFN cmUnpkTknU32 


/*
* FUN : cmUnpkCzt_ExtnCOUNTvalue_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnCOUNTvalue_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnCOUNTvalue_ExtIEsCls
(
Czt_ExtnCOUNTvalue_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnCOUNTvalue_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnCOUNTvalue_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnCOUNTvalue_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnCOUNTvalue_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_COUNTvalue_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_COUNTvalue_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_COUNTvalue_ExtIEs
(
CztProtExtnField_COUNTvalue_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_COUNTvalue_ExtIEs(param, ptr, mBuf)
CztProtExtnField_COUNTvalue_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_COUNTvalue_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnCOUNTvalue_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_COUNTvalue_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_COUNTvalue_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_COUNTvalue_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_COUNTvalue_ExtIEs
(
CztProtExtnCont_COUNTvalue_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_COUNTvalue_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_COUNTvalue_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_COUNTvalue_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_COUNTvalue_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_COUNTvalue_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_COUNTvalue_ExtIEs */



/*
* FUN : cmUnpkCztCOUNTvalue
*  DESC: Function to Unpack CztCOUNTvalue structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztCOUNTvalue
(
CztCOUNTvalue *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztCOUNTvalue(param, ptr, mBuf)
CztCOUNTvalue *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztCOUNTvalue) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztPDCP_SN, &param->pDCP_SN, mBuf); 
		CMCHKUNPK(cmUnpkCztHFN, &param->hFN, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_COUNTvalue_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztCOUNTvalue */

#define cmUnpkCztPDCP_SNExtended cmUnpkTknU32 
#define cmUnpkCztHFNMdfd cmUnpkTknU32 


/*
* FUN : cmUnpkCzt_ExtnCOUNTValueExtended_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnCOUNTValueExtended_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnCOUNTValueExtended_ExtIEsCls
(
Czt_ExtnCOUNTValueExtended_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnCOUNTValueExtended_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnCOUNTValueExtended_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnCOUNTValueExtended_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnCOUNTValueExtended_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_COUNTValueExtended_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_COUNTValueExtended_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_COUNTValueExtended_ExtIEs
(
CztProtExtnField_COUNTValueExtended_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_COUNTValueExtended_ExtIEs(param, ptr, mBuf)
CztProtExtnField_COUNTValueExtended_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_COUNTValueExtended_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnCOUNTValueExtended_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_COUNTValueExtended_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_COUNTValueExtended_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_COUNTValueExtended_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_COUNTValueExtended_ExtIEs
(
CztProtExtnCont_COUNTValueExtended_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_COUNTValueExtended_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_COUNTValueExtended_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_COUNTValueExtended_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_COUNTValueExtended_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_COUNTValueExtended_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_COUNTValueExtended_ExtIEs */



/*
* FUN : cmUnpkCztCOUNTValueExtended
*  DESC: Function to Unpack CztCOUNTValueExtended structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztCOUNTValueExtended
(
CztCOUNTValueExtended *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztCOUNTValueExtended(param, ptr, mBuf)
CztCOUNTValueExtended *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztCOUNTValueExtended) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztPDCP_SNExtended, &param->pDCP_SNExtended, mBuf); 
		CMCHKUNPK(cmUnpkCztHFNMdfd, &param->hFNMdfd, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_COUNTValueExtended_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztCOUNTValueExtended */

#define cmUnpkCztTypOfErr cmUnpkTknU32



/*
* FUN : cmUnpkCzt_ExtnCriticalityDiag_IE_Lst_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnCriticalityDiag_IE_Lst_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnCriticalityDiag_IE_Lst_ExtIEsCls
(
Czt_ExtnCriticalityDiag_IE_Lst_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnCriticalityDiag_IE_Lst_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnCriticalityDiag_IE_Lst_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnCriticalityDiag_IE_Lst_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnCriticalityDiag_IE_Lst_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_CriticalityDiag_IE_Lst_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_CriticalityDiag_IE_Lst_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_CriticalityDiag_IE_Lst_ExtIEs
(
CztProtExtnField_CriticalityDiag_IE_Lst_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_CriticalityDiag_IE_Lst_ExtIEs(param, ptr, mBuf)
CztProtExtnField_CriticalityDiag_IE_Lst_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_CriticalityDiag_IE_Lst_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnCriticalityDiag_IE_Lst_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_CriticalityDiag_IE_Lst_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_CriticalityDiag_IE_Lst_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_CriticalityDiag_IE_Lst_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_CriticalityDiag_IE_Lst_ExtIEs
(
CztProtExtnCont_CriticalityDiag_IE_Lst_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_CriticalityDiag_IE_Lst_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_CriticalityDiag_IE_Lst_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_CriticalityDiag_IE_Lst_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_CriticalityDiag_IE_Lst_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_CriticalityDiag_IE_Lst_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_CriticalityDiag_IE_Lst_ExtIEs */



/*
* FUN : cmUnpkCztCriticalityDiag_IE_LstMember
*  DESC: Function to Unpack CztCriticalityDiag_IE_LstMember structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztCriticalityDiag_IE_LstMember
(
CztCriticalityDiag_IE_LstMember *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztCriticalityDiag_IE_LstMember(param, ptr, mBuf)
CztCriticalityDiag_IE_LstMember *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztCriticalityDiag_IE_LstMember) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztCriticality, &param->iECriticality, mBuf); 
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->iE_ID, mBuf); 
		CMCHKUNPK(cmUnpkCztTypOfErr, &param->typeOfErr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_CriticalityDiag_IE_Lst_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztCriticalityDiag_IE_LstMember */



/*
* FUN : cmUnpkCztCriticalityDiag_IE_Lst
*  DESC: Function to Unpack CztCriticalityDiag_IE_Lst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztCriticalityDiag_IE_Lst
(
CztCriticalityDiag_IE_Lst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztCriticalityDiag_IE_Lst(param, ptr, mBuf)
CztCriticalityDiag_IE_Lst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztCriticalityDiag_IE_Lst) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztCriticalityDiag_IE_LstMember)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztCriticalityDiag_IE_LstMember, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztCriticalityDiag_IE_Lst */



/*
* FUN : cmUnpkCzt_ExtnCriticalityDiag_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnCriticalityDiag_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnCriticalityDiag_ExtIEsCls
(
Czt_ExtnCriticalityDiag_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnCriticalityDiag_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnCriticalityDiag_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnCriticalityDiag_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnCriticalityDiag_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_CriticalityDiag_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_CriticalityDiag_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_CriticalityDiag_ExtIEs
(
CztProtExtnField_CriticalityDiag_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_CriticalityDiag_ExtIEs(param, ptr, mBuf)
CztProtExtnField_CriticalityDiag_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_CriticalityDiag_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnCriticalityDiag_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_CriticalityDiag_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_CriticalityDiag_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_CriticalityDiag_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_CriticalityDiag_ExtIEs
(
CztProtExtnCont_CriticalityDiag_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_CriticalityDiag_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_CriticalityDiag_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_CriticalityDiag_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_CriticalityDiag_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_CriticalityDiag_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_CriticalityDiag_ExtIEs */



/*
* FUN : cmUnpkCztCriticalityDiag
*  DESC: Function to Unpack CztCriticalityDiag structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztCriticalityDiag
(
CztCriticalityDiag *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztCriticalityDiag(param, ptr, mBuf)
CztCriticalityDiag *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztCriticalityDiag) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProcedureCode, &param->procedureCode, mBuf); 
		CMCHKUNPK(cmUnpkCztTrgMsg, &param->triggeringMsg, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->procedureCriticality, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztCriticalityDiag_IE_Lst, &param->iEsCriticalityDiag, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_CriticalityDiag_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztCriticalityDiag */

#define cmUnpkCztCRNTI cmUnpkTknBStr32 
#define cmUnpkCztCSGMembershipStatus cmUnpkTknU32

#define cmUnpkCztCSG_Id cmUnpkTknBStr32 
#define cmUnpkCztDeactivationInd cmUnpkTknU32

#define cmUnpkCztDL_Fwding cmUnpkTknU32

#define cmUnpkCztDL_GBR_PRB_usage cmUnpkTknU32 
#define cmUnpkCztDL_non_GBR_PRB_usage cmUnpkTknU32 
#define cmUnpkCztDL_Total_PRB_usage cmUnpkTknU32 
#define cmUnpkCztEARFCN cmUnpkTknU32 
#define cmUnpkCztEARFCNExtn cmUnpkTknU32 
#define cmUnpkCztTransmission_Bandwidth cmUnpkTknU32



/*
* FUN : cmUnpkCzt_ExtnFDD_Info_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnFDD_Info_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnFDD_Info_ExtIEsCls
(
Czt_ExtnFDD_Info_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnFDD_Info_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnFDD_Info_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnFDD_Info_ExtIEsCls) 
	
	switch (val)
	{
		case Cztid_UL_EARFCNExtn:
			CMCHKUNPK(cmUnpkCztEARFCNExtn, &param->u.cztid_UL_EARFCNExtn, mBuf); 
			break;
		case Cztid_DL_EARFCNExtn:
			CMCHKUNPK(cmUnpkCztEARFCNExtn, &param->u.cztid_DL_EARFCNExtn, mBuf); 
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ExtnFDD_Info_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_FDD_Info_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_FDD_Info_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_FDD_Info_ExtIEs
(
CztProtExtnField_FDD_Info_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_FDD_Info_ExtIEs(param, ptr, mBuf)
CztProtExtnField_FDD_Info_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_FDD_Info_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnFDD_Info_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_FDD_Info_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_FDD_Info_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_FDD_Info_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_FDD_Info_ExtIEs
(
CztProtExtnCont_FDD_Info_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_FDD_Info_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_FDD_Info_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_FDD_Info_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_FDD_Info_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_FDD_Info_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_FDD_Info_ExtIEs */



/*
* FUN : cmUnpkCztFDD_Info
*  DESC: Function to Unpack CztFDD_Info structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztFDD_Info
(
CztFDD_Info *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztFDD_Info(param, ptr, mBuf)
CztFDD_Info *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztFDD_Info) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztEARFCN, &param->uL_EARFCN, mBuf); 
		CMCHKUNPK(cmUnpkCztEARFCN, &param->dL_EARFCN, mBuf); 
		CMCHKUNPK(cmUnpkCztTransmission_Bandwidth, &param->uL_Transmission_Bandwidth, mBuf); 
		CMCHKUNPK(cmUnpkCztTransmission_Bandwidth, &param->dL_Transmission_Bandwidth, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_FDD_Info_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztFDD_Info */

#define cmUnpkCztSubframeAssignment cmUnpkTknU32

#define cmUnpkCztSpecialSubframePatterns cmUnpkTknU32



/*
* FUN : cmUnpkCzt_ExtnSpecialSubframe_Info_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnSpecialSubframe_Info_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnSpecialSubframe_Info_ExtIEsCls
(
Czt_ExtnSpecialSubframe_Info_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnSpecialSubframe_Info_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnSpecialSubframe_Info_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnSpecialSubframe_Info_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnSpecialSubframe_Info_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_SpecialSubframe_Info_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_SpecialSubframe_Info_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_SpecialSubframe_Info_ExtIEs
(
CztProtExtnField_SpecialSubframe_Info_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_SpecialSubframe_Info_ExtIEs(param, ptr, mBuf)
CztProtExtnField_SpecialSubframe_Info_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_SpecialSubframe_Info_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnSpecialSubframe_Info_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_SpecialSubframe_Info_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_SpecialSubframe_Info_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_SpecialSubframe_Info_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_SpecialSubframe_Info_ExtIEs
(
CztProtExtnCont_SpecialSubframe_Info_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_SpecialSubframe_Info_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_SpecialSubframe_Info_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_SpecialSubframe_Info_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_SpecialSubframe_Info_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_SpecialSubframe_Info_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_SpecialSubframe_Info_ExtIEs */



/*
* FUN : cmUnpkCztSpecialSubframe_Info
*  DESC: Function to Unpack CztSpecialSubframe_Info structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztSpecialSubframe_Info
(
CztSpecialSubframe_Info *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztSpecialSubframe_Info(param, ptr, mBuf)
CztSpecialSubframe_Info *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztSpecialSubframe_Info) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztSpecialSubframePatterns, &param->specialSubframePatterns, mBuf); 
		CMCHKUNPK(cmUnpkCztCyclicPrefixDL, &param->cyclicPrefixDL, mBuf); 
		CMCHKUNPK(cmUnpkCztCyclicPrefixUL, &param->cyclicPrefixUL, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_SpecialSubframe_Info_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztSpecialSubframe_Info */



/*
* FUN : cmUnpkCzt_ExtnTDD_Info_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnTDD_Info_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnTDD_Info_ExtIEsCls
(
Czt_ExtnTDD_Info_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnTDD_Info_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnTDD_Info_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnTDD_Info_ExtIEsCls) 
	
	switch (val)
	{
		case Cztid_AdditionalSpecialSubframe_Info:
			CMCHKUNPKPTR(cmUnpkCztAdditionalSpecialSubframe_Info, &param->u.cztAdditionalSpecialSubframe_Info, ptr, mBuf);
			break;
		case Cztid_eARFCNExtn:
			CMCHKUNPK(cmUnpkCztEARFCNExtn, &param->u.cztEARFCNExtn, mBuf); 
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ExtnTDD_Info_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_TDD_Info_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_TDD_Info_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_TDD_Info_ExtIEs
(
CztProtExtnField_TDD_Info_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_TDD_Info_ExtIEs(param, ptr, mBuf)
CztProtExtnField_TDD_Info_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_TDD_Info_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnTDD_Info_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_TDD_Info_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_TDD_Info_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_TDD_Info_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_TDD_Info_ExtIEs
(
CztProtExtnCont_TDD_Info_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_TDD_Info_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_TDD_Info_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_TDD_Info_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_TDD_Info_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_TDD_Info_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_TDD_Info_ExtIEs */



/*
* FUN : cmUnpkCztTDD_Info
*  DESC: Function to Unpack CztTDD_Info structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztTDD_Info
(
CztTDD_Info *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztTDD_Info(param, ptr, mBuf)
CztTDD_Info *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztTDD_Info) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztEARFCN, &param->eARFCN, mBuf); 
		CMCHKUNPK(cmUnpkCztTransmission_Bandwidth, &param->transmission_Bandwidth, mBuf); 
		CMCHKUNPK(cmUnpkCztSubframeAssignment, &param->subframeAssignment, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztSpecialSubframe_Info, &param->specialSubframe_Info, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_TDD_Info_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztTDD_Info */



/*
* FUN : cmUnpkCztEUTRA_Mode_Info
*  DESC: Function to Unpack CztEUTRA_Mode_Info structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztEUTRA_Mode_Info
(
CztEUTRA_Mode_Info *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztEUTRA_Mode_Info(param, ptr, mBuf)
CztEUTRA_Mode_Info *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztEUTRA_Mode_Info) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case EUTRA_MODE_INFO_FDD :
				CMCHKUNPKPTR(cmUnpkCztFDD_Info, &param->val.fDD, ptr, mBuf); 
				break;
			case EUTRA_MODE_INFO_TDD :
				CMCHKUNPKPTR(cmUnpkCztTDD_Info, &param->val.tDD, ptr, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztEUTRA_Mode_Info */

#define cmUnpkCztENB_IDmacro_eNB_ID cmUnpkTknBStr32 
#define cmUnpkCztENB_IDhome_eNB_ID cmUnpkTknBStr32 


/*
* FUN : cmUnpkCztENB_ID
*  DESC: Function to Unpack CztENB_ID structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztENB_ID
(
CztENB_ID *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztENB_ID(param, ptr, mBuf)
CztENB_ID *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztENB_ID) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case ENB_ID_MACRO_ENB_ID :
				CMCHKUNPK(cmUnpkCztENB_IDmacro_eNB_ID, &param->val.macro_eNB_ID, mBuf); 
				break;
			case ENB_ID_HOME_ENB_ID :
				CMCHKUNPK(cmUnpkCztENB_IDhome_eNB_ID, &param->val.home_eNB_ID, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztENB_ID */

#define cmUnpkCztEncryptionAlgorithms cmUnpkTknBStr32 


/*
* FUN : cmUnpkCztEPLMNs
*  DESC: Function to Unpack CztEPLMNs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztEPLMNs
(
CztEPLMNs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztEPLMNs(param, ptr, mBuf)
CztEPLMNs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztEPLMNs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztPLMN_Identity)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CZUCHKUNPKPTR(cmUnpkCztPLMN_Identity, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztEPLMNs */

#define cmUnpkCztE_RAB_ID cmUnpkTknU32 
#define cmUnpkCztQCI cmUnpkTknU32 


/*
* FUN : cmUnpkCzt_ExtnGBR_QosInform_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnGBR_QosInform_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnGBR_QosInform_ExtIEsCls
(
Czt_ExtnGBR_QosInform_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnGBR_QosInform_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnGBR_QosInform_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnGBR_QosInform_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnGBR_QosInform_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_GBR_QosInform_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_GBR_QosInform_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_GBR_QosInform_ExtIEs
(
CztProtExtnField_GBR_QosInform_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_GBR_QosInform_ExtIEs(param, ptr, mBuf)
CztProtExtnField_GBR_QosInform_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_GBR_QosInform_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnGBR_QosInform_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_GBR_QosInform_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_GBR_QosInform_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_GBR_QosInform_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_GBR_QosInform_ExtIEs
(
CztProtExtnCont_GBR_QosInform_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_GBR_QosInform_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_GBR_QosInform_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_GBR_QosInform_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_GBR_QosInform_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_GBR_QosInform_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_GBR_QosInform_ExtIEs */



/*
* FUN : cmUnpkCztGBR_QosInform
*  DESC: Function to Unpack CztGBR_QosInform structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztGBR_QosInform
(
CztGBR_QosInform *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztGBR_QosInform(param, ptr, mBuf)
CztGBR_QosInform *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztGBR_QosInform) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CZUCHKUNPKPTR(cmUnpkCztBitRate, &param->e_RAB_MaxBitrateDL, ptr, mBuf); 
		CZUCHKUNPKPTR(cmUnpkCztBitRate, &param->e_RAB_MaxBitrateUL, ptr, mBuf); 
		CZUCHKUNPKPTR(cmUnpkCztBitRate, &param->e_RAB_GuaranteedBitrateDL, ptr, mBuf); 
		CZUCHKUNPKPTR(cmUnpkCztBitRate, &param->e_RAB_GuaranteedBitrateUL, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_GBR_QosInform_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztGBR_QosInform */



/*
* FUN : cmUnpkCzt_ExtnE_RAB_Lvl_QoS_Params_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnE_RAB_Lvl_QoS_Params_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnE_RAB_Lvl_QoS_Params_ExtIEsCls
(
Czt_ExtnE_RAB_Lvl_QoS_Params_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnE_RAB_Lvl_QoS_Params_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnE_RAB_Lvl_QoS_Params_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnE_RAB_Lvl_QoS_Params_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnE_RAB_Lvl_QoS_Params_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEs
(
CztProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEs(param, ptr, mBuf)
CztProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnE_RAB_Lvl_QoS_Params_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEs
(
CztProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_E_RAB_Lvl_QoS_Params_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEs */



/*
* FUN : cmUnpkCztE_RAB_Lvl_QoS_Params
*  DESC: Function to Unpack CztE_RAB_Lvl_QoS_Params structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztE_RAB_Lvl_QoS_Params
(
CztE_RAB_Lvl_QoS_Params *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztE_RAB_Lvl_QoS_Params(param, ptr, mBuf)
CztE_RAB_Lvl_QoS_Params *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztE_RAB_Lvl_QoS_Params) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztQCI, &param->qCI, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztAllocnAndRetentionPriority, &param->allocationAndRetentionPriority, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztGBR_QosInform, &param->gbrQosInform, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_E_RAB_Lvl_QoS_Params_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztE_RAB_Lvl_QoS_Params */



/*
* FUN : cmUnpkCzt_ExtnE_RAB_Item_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnE_RAB_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnE_RAB_Item_ExtIEsCls
(
Czt_ExtnE_RAB_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnE_RAB_Item_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnE_RAB_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnE_RAB_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnE_RAB_Item_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_E_RAB_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_E_RAB_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_E_RAB_Item_ExtIEs
(
CztProtExtnField_E_RAB_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_E_RAB_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnField_E_RAB_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_E_RAB_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnE_RAB_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_E_RAB_Item_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_E_RAB_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_E_RAB_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_E_RAB_Item_ExtIEs
(
CztProtExtnCont_E_RAB_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_E_RAB_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_E_RAB_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_E_RAB_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_E_RAB_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_E_RAB_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_E_RAB_Item_ExtIEs */



/*
* FUN : cmUnpkCztE_RAB_Item
*  DESC: Function to Unpack CztE_RAB_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztE_RAB_Item
(
CztE_RAB_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztE_RAB_Item(param, ptr, mBuf)
CztE_RAB_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztE_RAB_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztE_RAB_ID, &param->e_RAB_ID, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztCause, &param->cause, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_E_RAB_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztE_RAB_Item */



/*
* FUN : cmUnpkCzt_ValueE_RAB_ItemIEsCls
*  DESC: Function to Unpack Czt_ValueE_RAB_ItemIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueE_RAB_ItemIEsCls
(
Czt_ValueE_RAB_ItemIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueE_RAB_ItemIEsCls(param, val, ptr, mBuf)
Czt_ValueE_RAB_ItemIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueE_RAB_ItemIEsCls) 
	
	switch (val)
	{
		case Cztid_E_RAB_Item:
			CMCHKUNPKPTR(cmUnpkCztE_RAB_Item, &param->u.cztE_RAB_Item, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueE_RAB_ItemIEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_E_RAB_ItemIEs
*  DESC: Function to Unpack CztProtIE_Field_E_RAB_ItemIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_E_RAB_ItemIEs
(
CztProtIE_Field_E_RAB_ItemIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_E_RAB_ItemIEs(param, ptr, mBuf)
CztProtIE_Field_E_RAB_ItemIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_E_RAB_ItemIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueE_RAB_ItemIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_E_RAB_ItemIEs */

/* Element ------------- ProtocolIE-Single-Container ------------ */
#define cmUnpkCztProtIE_Single_Cont_E_RAB_ItemIEs cmUnpkCztProtIE_Field_E_RAB_ItemIEs


/*
* FUN : cmUnpkCztE_RAB_Lst
*  DESC: Function to Unpack CztE_RAB_Lst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztE_RAB_Lst
(
CztE_RAB_Lst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztE_RAB_Lst(param, ptr, mBuf)
CztE_RAB_Lst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztE_RAB_Lst) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Single_Cont_E_RAB_ItemIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Single_Cont_E_RAB_ItemIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztE_RAB_Lst */

#define cmUnpkCztEUTRANTraceID cmUnpkTknStrOSXL 
#define cmUnpkCztEventTyp cmUnpkTknU32

#define cmUnpkCztForbiddenInterRATs cmUnpkTknU32



/*
* FUN : cmUnpkCztForbiddenTACs
*  DESC: Function to Unpack CztForbiddenTACs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztForbiddenTACs
(
CztForbiddenTACs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztForbiddenTACs(param, ptr, mBuf)
CztForbiddenTACs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztForbiddenTACs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztTAC)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPK(cmUnpkCztTAC, &(param->member[i]), mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztForbiddenTACs */



/*
* FUN : cmUnpkCzt_ExtnForbiddenTAs_Item_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnForbiddenTAs_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnForbiddenTAs_Item_ExtIEsCls
(
Czt_ExtnForbiddenTAs_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnForbiddenTAs_Item_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnForbiddenTAs_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnForbiddenTAs_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnForbiddenTAs_Item_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_ForbiddenTAs_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_ForbiddenTAs_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_ForbiddenTAs_Item_ExtIEs
(
CztProtExtnField_ForbiddenTAs_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_ForbiddenTAs_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnField_ForbiddenTAs_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_ForbiddenTAs_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnForbiddenTAs_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_ForbiddenTAs_Item_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_ForbiddenTAs_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_ForbiddenTAs_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_ForbiddenTAs_Item_ExtIEs
(
CztProtExtnCont_ForbiddenTAs_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_ForbiddenTAs_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_ForbiddenTAs_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_ForbiddenTAs_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_ForbiddenTAs_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_ForbiddenTAs_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_ForbiddenTAs_Item_ExtIEs */



/*
* FUN : cmUnpkCztForbiddenTAs_Item
*  DESC: Function to Unpack CztForbiddenTAs_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztForbiddenTAs_Item
(
CztForbiddenTAs_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztForbiddenTAs_Item(param, ptr, mBuf)
CztForbiddenTAs_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztForbiddenTAs_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CZUCHKUNPKPTR(cmUnpkCztPLMN_Identity, &param->pLMN_Identity, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztForbiddenTACs, &param->forbiddenTACs, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_ForbiddenTAs_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztForbiddenTAs_Item */



/*
* FUN : cmUnpkCztForbiddenTAs
*  DESC: Function to Unpack CztForbiddenTAs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztForbiddenTAs
(
CztForbiddenTAs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztForbiddenTAs(param, ptr, mBuf)
CztForbiddenTAs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztForbiddenTAs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztForbiddenTAs_Item)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztForbiddenTAs_Item, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztForbiddenTAs */

#define cmUnpkCztLAC cmUnpkTknStr4 


/*
* FUN : cmUnpkCztForbiddenLACs
*  DESC: Function to Unpack CztForbiddenLACs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztForbiddenLACs
(
CztForbiddenLACs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztForbiddenLACs(param, ptr, mBuf)
CztForbiddenLACs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztForbiddenLACs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztLAC)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPK(cmUnpkCztLAC, &(param->member[i]), mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztForbiddenLACs */



/*
* FUN : cmUnpkCzt_ExtnForbiddenLAs_Item_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnForbiddenLAs_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnForbiddenLAs_Item_ExtIEsCls
(
Czt_ExtnForbiddenLAs_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnForbiddenLAs_Item_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnForbiddenLAs_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnForbiddenLAs_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnForbiddenLAs_Item_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_ForbiddenLAs_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_ForbiddenLAs_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_ForbiddenLAs_Item_ExtIEs
(
CztProtExtnField_ForbiddenLAs_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_ForbiddenLAs_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnField_ForbiddenLAs_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_ForbiddenLAs_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnForbiddenLAs_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_ForbiddenLAs_Item_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_ForbiddenLAs_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_ForbiddenLAs_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_ForbiddenLAs_Item_ExtIEs
(
CztProtExtnCont_ForbiddenLAs_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_ForbiddenLAs_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_ForbiddenLAs_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_ForbiddenLAs_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_ForbiddenLAs_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_ForbiddenLAs_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_ForbiddenLAs_Item_ExtIEs */



/*
* FUN : cmUnpkCztForbiddenLAs_Item
*  DESC: Function to Unpack CztForbiddenLAs_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztForbiddenLAs_Item
(
CztForbiddenLAs_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztForbiddenLAs_Item(param, ptr, mBuf)
CztForbiddenLAs_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztForbiddenLAs_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CZUCHKUNPKPTR(cmUnpkCztPLMN_Identity, &param->pLMN_Identity, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztForbiddenLACs, &param->forbiddenLACs, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_ForbiddenLAs_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztForbiddenLAs_Item */



/*
* FUN : cmUnpkCztForbiddenLAs
*  DESC: Function to Unpack CztForbiddenLAs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztForbiddenLAs
(
CztForbiddenLAs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztForbiddenLAs(param, ptr, mBuf)
CztForbiddenLAs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztForbiddenLAs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztForbiddenLAs_Item)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztForbiddenLAs_Item, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztForbiddenLAs */

#define cmUnpkCztFourframes cmUnpkTknBStr32 
#define cmUnpkCztFreqBandIndicator cmUnpkTknU32 


/*
* FUN : cmUnpkCzt_ExtnGlobalENB_ID_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnGlobalENB_ID_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnGlobalENB_ID_ExtIEsCls
(
Czt_ExtnGlobalENB_ID_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnGlobalENB_ID_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnGlobalENB_ID_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnGlobalENB_ID_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnGlobalENB_ID_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_GlobalENB_ID_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_GlobalENB_ID_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_GlobalENB_ID_ExtIEs
(
CztProtExtnField_GlobalENB_ID_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_GlobalENB_ID_ExtIEs(param, ptr, mBuf)
CztProtExtnField_GlobalENB_ID_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_GlobalENB_ID_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnGlobalENB_ID_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_GlobalENB_ID_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_GlobalENB_ID_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_GlobalENB_ID_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_GlobalENB_ID_ExtIEs
(
CztProtExtnCont_GlobalENB_ID_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_GlobalENB_ID_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_GlobalENB_ID_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_GlobalENB_ID_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_GlobalENB_ID_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_GlobalENB_ID_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_GlobalENB_ID_ExtIEs */



/*
* FUN : cmUnpkCztGlobalENB_ID
*  DESC: Function to Unpack CztGlobalENB_ID structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztGlobalENB_ID
(
CztGlobalENB_ID *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztGlobalENB_ID(param, ptr, mBuf)
CztGlobalENB_ID *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztGlobalENB_ID) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CZUCHKUNPKPTR(cmUnpkCztPLMN_Identity, &param->pLMN_Identity, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztENB_ID, &param->eNB_ID, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_GlobalENB_ID_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztGlobalENB_ID */

#define cmUnpkCztTportLyrAddr cmUnpkTknStrBSXL 
#define cmUnpkCztGTP_TEI cmUnpkTknStrOSXL 


/*
* FUN : cmUnpkCzt_ExtnGTPtunnelEndpoint_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnGTPtunnelEndpoint_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnGTPtunnelEndpoint_ExtIEsCls
(
Czt_ExtnGTPtunnelEndpoint_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnGTPtunnelEndpoint_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnGTPtunnelEndpoint_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnGTPtunnelEndpoint_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnGTPtunnelEndpoint_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_GTPtunnelEndpoint_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_GTPtunnelEndpoint_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_GTPtunnelEndpoint_ExtIEs
(
CztProtExtnField_GTPtunnelEndpoint_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_GTPtunnelEndpoint_ExtIEs(param, ptr, mBuf)
CztProtExtnField_GTPtunnelEndpoint_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_GTPtunnelEndpoint_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnGTPtunnelEndpoint_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_GTPtunnelEndpoint_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_GTPtunnelEndpoint_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_GTPtunnelEndpoint_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_GTPtunnelEndpoint_ExtIEs
(
CztProtExtnCont_GTPtunnelEndpoint_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_GTPtunnelEndpoint_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_GTPtunnelEndpoint_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_GTPtunnelEndpoint_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_GTPtunnelEndpoint_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_GTPtunnelEndpoint_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_GTPtunnelEndpoint_ExtIEs */



/*
* FUN : cmUnpkCztGTPtunnelEndpoint
*  DESC: Function to Unpack CztGTPtunnelEndpoint structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztGTPtunnelEndpoint
(
CztGTPtunnelEndpoint *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztGTPtunnelEndpoint(param, ptr, mBuf)
CztGTPtunnelEndpoint *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztGTPtunnelEndpoint) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztTportLyrAddr, &param->transportLyrAddr, ptr, mBuf); 
		CZUCHKUNPKPTR(cmUnpkCztGTP_TEI, &param->gTP_TEID, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_GTPtunnelEndpoint_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztGTPtunnelEndpoint */

#define cmUnpkCztMME_Group_ID cmUnpkTknStr4 


/*
* FUN : cmUnpkCzt_ExtnGU_Group_ID_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnGU_Group_ID_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnGU_Group_ID_ExtIEsCls
(
Czt_ExtnGU_Group_ID_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnGU_Group_ID_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnGU_Group_ID_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnGU_Group_ID_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnGU_Group_ID_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_GU_Group_ID_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_GU_Group_ID_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_GU_Group_ID_ExtIEs
(
CztProtExtnField_GU_Group_ID_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_GU_Group_ID_ExtIEs(param, ptr, mBuf)
CztProtExtnField_GU_Group_ID_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_GU_Group_ID_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnGU_Group_ID_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_GU_Group_ID_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_GU_Group_ID_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_GU_Group_ID_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_GU_Group_ID_ExtIEs
(
CztProtExtnCont_GU_Group_ID_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_GU_Group_ID_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_GU_Group_ID_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_GU_Group_ID_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_GU_Group_ID_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_GU_Group_ID_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_GU_Group_ID_ExtIEs */



/*
* FUN : cmUnpkCztGU_Group_ID
*  DESC: Function to Unpack CztGU_Group_ID structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztGU_Group_ID
(
CztGU_Group_ID *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztGU_Group_ID(param, ptr, mBuf)
CztGU_Group_ID *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztGU_Group_ID) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CZUCHKUNPKPTR(cmUnpkCztPLMN_Identity, &param->pLMN_Identity, ptr, mBuf); 
		CMCHKUNPK(cmUnpkCztMME_Group_ID, &param->mME_Group_ID, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_GU_Group_ID_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztGU_Group_ID */



/*
* FUN : cmUnpkCztGUGroupIDLst
*  DESC: Function to Unpack CztGUGroupIDLst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztGUGroupIDLst
(
CztGUGroupIDLst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztGUGroupIDLst(param, ptr, mBuf)
CztGUGroupIDLst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztGUGroupIDLst) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztGU_Group_ID)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztGU_Group_ID, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztGUGroupIDLst */

#define cmUnpkCztMME_Code cmUnpkTknStr4 


/*
* FUN : cmUnpkCzt_ExtnGUMMEI_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnGUMMEI_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnGUMMEI_ExtIEsCls
(
Czt_ExtnGUMMEI_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnGUMMEI_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnGUMMEI_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnGUMMEI_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnGUMMEI_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_GUMMEI_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_GUMMEI_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_GUMMEI_ExtIEs
(
CztProtExtnField_GUMMEI_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_GUMMEI_ExtIEs(param, ptr, mBuf)
CztProtExtnField_GUMMEI_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_GUMMEI_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnGUMMEI_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_GUMMEI_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_GUMMEI_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_GUMMEI_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_GUMMEI_ExtIEs
(
CztProtExtnCont_GUMMEI_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_GUMMEI_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_GUMMEI_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_GUMMEI_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_GUMMEI_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_GUMMEI_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_GUMMEI_ExtIEs */



/*
* FUN : cmUnpkCztGUMMEI
*  DESC: Function to Unpack CztGUMMEI structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztGUMMEI
(
CztGUMMEI *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztGUMMEI(param, ptr, mBuf)
CztGUMMEI *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztGUMMEI) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztGU_Group_ID, &param->gU_Group_ID, ptr, mBuf); 
		CMCHKUNPK(cmUnpkCztMME_Code, &param->mME_Code, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_GUMMEI_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztGUMMEI */

#define cmUnpkCztHovrReportTyp cmUnpkTknU32



/*
* FUN : cmUnpkCzt_ExtnHovrRestrnLst_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnHovrRestrnLst_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnHovrRestrnLst_ExtIEsCls
(
Czt_ExtnHovrRestrnLst_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnHovrRestrnLst_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnHovrRestrnLst_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnHovrRestrnLst_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnHovrRestrnLst_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_HovrRestrnLst_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_HovrRestrnLst_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_HovrRestrnLst_ExtIEs
(
CztProtExtnField_HovrRestrnLst_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_HovrRestrnLst_ExtIEs(param, ptr, mBuf)
CztProtExtnField_HovrRestrnLst_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_HovrRestrnLst_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnHovrRestrnLst_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_HovrRestrnLst_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_HovrRestrnLst_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_HovrRestrnLst_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_HovrRestrnLst_ExtIEs
(
CztProtExtnCont_HovrRestrnLst_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_HovrRestrnLst_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_HovrRestrnLst_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_HovrRestrnLst_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_HovrRestrnLst_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_HovrRestrnLst_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_HovrRestrnLst_ExtIEs */



/*
* FUN : cmUnpkCztHovrRestrnLst
*  DESC: Function to Unpack CztHovrRestrnLst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztHovrRestrnLst
(
CztHovrRestrnLst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztHovrRestrnLst(param, ptr, mBuf)
CztHovrRestrnLst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztHovrRestrnLst) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CZUCHKUNPKPTR(cmUnpkCztPLMN_Identity, &param->servingPLMN, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztEPLMNs, &param->equivalentPLMNs, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztForbiddenTAs, &param->forbiddenTAs, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztForbiddenLAs, &param->forbiddenLAs, ptr, mBuf); 
		CMCHKUNPK(cmUnpkCztForbiddenInterRATs, &param->forbiddenInterRATs, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_HovrRestrnLst_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztHovrRestrnLst */

#define cmUnpkCztLoadIndicator cmUnpkTknU32



/*
* FUN : cmUnpkCzt_ExtnHWLoadIndicator_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnHWLoadIndicator_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnHWLoadIndicator_ExtIEsCls
(
Czt_ExtnHWLoadIndicator_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnHWLoadIndicator_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnHWLoadIndicator_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnHWLoadIndicator_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnHWLoadIndicator_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_HWLoadIndicator_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_HWLoadIndicator_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_HWLoadIndicator_ExtIEs
(
CztProtExtnField_HWLoadIndicator_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_HWLoadIndicator_ExtIEs(param, ptr, mBuf)
CztProtExtnField_HWLoadIndicator_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_HWLoadIndicator_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnHWLoadIndicator_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_HWLoadIndicator_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_HWLoadIndicator_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_HWLoadIndicator_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_HWLoadIndicator_ExtIEs
(
CztProtExtnCont_HWLoadIndicator_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_HWLoadIndicator_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_HWLoadIndicator_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_HWLoadIndicator_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_HWLoadIndicator_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_HWLoadIndicator_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_HWLoadIndicator_ExtIEs */



/*
* FUN : cmUnpkCztHWLoadIndicator
*  DESC: Function to Unpack CztHWLoadIndicator structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztHWLoadIndicator
(
CztHWLoadIndicator *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztHWLoadIndicator(param, ptr, mBuf)
CztHWLoadIndicator *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztHWLoadIndicator) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztLoadIndicator, &param->dLHWLoadIndicator, mBuf); 
		CMCHKUNPK(cmUnpkCztLoadIndicator, &param->uLHWLoadIndicator, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_HWLoadIndicator_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztHWLoadIndicator */

#define cmUnpkCztInvokeInd cmUnpkTknU32

#define cmUnpkCztIntegrityProtectionAlgorithms cmUnpkTknBStr32 
#define cmUnpkCztIntfsToTrace cmUnpkTknBStr32 
#define cmUnpkCztTime_UE_StayedInCell cmUnpkTknU32 
#define cmUnpkCztTime_UE_StayedInCell_EnhancedGranularity cmUnpkTknU32 


/*
* FUN : cmUnpkCzt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls
(
Czt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls) 
	
	switch (val)
	{
		case Cztid_Time_UE_StayedInCell_EnhancedGranularity:
			CMCHKUNPK(cmUnpkCztTime_UE_StayedInCell_EnhancedGranularity, &param->u.cztTime_UE_StayedInCell_EnhancedGranularity, mBuf); 
			break;
		case Cztid_HO_cause:
			CMCHKUNPKPTR(cmUnpkCztCause, &param->u.cztCause, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs
(
CztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs(param, ptr, mBuf)
CztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs
(
CztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs */



/*
* FUN : cmUnpkCztLastVisitedEUTRANCellInform
*  DESC: Function to Unpack CztLastVisitedEUTRANCellInform structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztLastVisitedEUTRANCellInform
(
CztLastVisitedEUTRANCellInform *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztLastVisitedEUTRANCellInform(param, ptr, mBuf)
CztLastVisitedEUTRANCellInform *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztLastVisitedEUTRANCellInform) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztECGI, &param->global_Cell_ID, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztCellTyp, &param->cellTyp, ptr, mBuf); 
		CMCHKUNPK(cmUnpkCztTime_UE_StayedInCell, &param->time_UE_StayedInCell, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztLastVisitedEUTRANCellInform */

#define cmUnpkCztLastVisitedUTRANCellInform cmUnpkTknStrOSXL 


/*
* FUN : cmUnpkCztLastVisitedGERANCellInform
*  DESC: Function to Unpack CztLastVisitedGERANCellInform structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztLastVisitedGERANCellInform
(
CztLastVisitedGERANCellInform *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztLastVisitedGERANCellInform(param, ptr, mBuf)
CztLastVisitedGERANCellInform *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztLastVisitedGERANCellInform) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
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
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztLastVisitedGERANCellInform */



/*
* FUN : cmUnpkCztLastVisitedCell_Item
*  DESC: Function to Unpack CztLastVisitedCell_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztLastVisitedCell_Item
(
CztLastVisitedCell_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztLastVisitedCell_Item(param, ptr, mBuf)
CztLastVisitedCell_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztLastVisitedCell_Item) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case LASTVISITEDCELL_ITEM_E_UTRAN_CELL :
				CMCHKUNPKPTR(cmUnpkCztLastVisitedEUTRANCellInform, &param->val.e_UTRAN_Cell, ptr, mBuf); 
				break;
			case LASTVISITEDCELL_ITEM_UTRAN_CELL :
				CZUCHKUNPKPTR(cmUnpkCztLastVisitedUTRANCellInform, &param->val.uTRAN_Cell, ptr, mBuf); 
				break;
			case LASTVISITEDCELL_ITEM_GERAN_CELL :
				CMCHKUNPKPTR(cmUnpkCztLastVisitedGERANCellInform, &param->val.gERAN_Cell, ptr, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztLastVisitedCell_Item */

#define cmUnpkCztLinks_to_log cmUnpkTknU32

#define cmUnpkCztReportArea cmUnpkTknU32



/*
* FUN : cmUnpkCzt_ExtnLocRprtngInform_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnLocRprtngInform_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnLocRprtngInform_ExtIEsCls
(
Czt_ExtnLocRprtngInform_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnLocRprtngInform_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnLocRprtngInform_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnLocRprtngInform_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnLocRprtngInform_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_LocRprtngInform_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_LocRprtngInform_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_LocRprtngInform_ExtIEs
(
CztProtExtnField_LocRprtngInform_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_LocRprtngInform_ExtIEs(param, ptr, mBuf)
CztProtExtnField_LocRprtngInform_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_LocRprtngInform_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnLocRprtngInform_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_LocRprtngInform_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_LocRprtngInform_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_LocRprtngInform_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_LocRprtngInform_ExtIEs
(
CztProtExtnCont_LocRprtngInform_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_LocRprtngInform_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_LocRprtngInform_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_LocRprtngInform_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_LocRprtngInform_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_LocRprtngInform_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_LocRprtngInform_ExtIEs */



/*
* FUN : cmUnpkCztLocRprtngInform
*  DESC: Function to Unpack CztLocRprtngInform structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztLocRprtngInform
(
CztLocRprtngInform *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztLocRprtngInform(param, ptr, mBuf)
CztLocRprtngInform *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztLocRprtngInform) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztEventTyp, &param->eventTyp, mBuf); 
		CMCHKUNPK(cmUnpkCztReportArea, &param->reportArea, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_LocRprtngInform_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztLocRprtngInform */

#define cmUnpkCztM3period cmUnpkTknU32



/*
* FUN : cmUnpkCzt_ExtnM3Config_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnM3Config_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnM3Config_ExtIEsCls
(
Czt_ExtnM3Config_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnM3Config_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnM3Config_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnM3Config_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnM3Config_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_M3Config_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_M3Config_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_M3Config_ExtIEs
(
CztProtExtnField_M3Config_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_M3Config_ExtIEs(param, ptr, mBuf)
CztProtExtnField_M3Config_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_M3Config_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnM3Config_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_M3Config_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_M3Config_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_M3Config_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_M3Config_ExtIEs
(
CztProtExtnCont_M3Config_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_M3Config_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_M3Config_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_M3Config_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_M3Config_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_M3Config_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_M3Config_ExtIEs */



/*
* FUN : cmUnpkCztM3Config
*  DESC: Function to Unpack CztM3Config structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztM3Config
(
CztM3Config *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztM3Config(param, ptr, mBuf)
CztM3Config *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztM3Config) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztM3period, &param->m3period, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_M3Config_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztM3Config */

#define cmUnpkCztM4period cmUnpkTknU32



/*
* FUN : cmUnpkCzt_ExtnM4Config_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnM4Config_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnM4Config_ExtIEsCls
(
Czt_ExtnM4Config_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnM4Config_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnM4Config_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnM4Config_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnM4Config_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_M4Config_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_M4Config_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_M4Config_ExtIEs
(
CztProtExtnField_M4Config_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_M4Config_ExtIEs(param, ptr, mBuf)
CztProtExtnField_M4Config_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_M4Config_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnM4Config_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_M4Config_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_M4Config_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_M4Config_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_M4Config_ExtIEs
(
CztProtExtnCont_M4Config_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_M4Config_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_M4Config_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_M4Config_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_M4Config_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_M4Config_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_M4Config_ExtIEs */



/*
* FUN : cmUnpkCztM4Config
*  DESC: Function to Unpack CztM4Config structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztM4Config
(
CztM4Config *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztM4Config(param, ptr, mBuf)
CztM4Config *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztM4Config) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztM4period, &param->m4period, mBuf); 
		CMCHKUNPK(cmUnpkCztLinks_to_log, &param->m4_links_to_log, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_M4Config_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztM4Config */

#define cmUnpkCztM5period cmUnpkTknU32



/*
* FUN : cmUnpkCzt_ExtnM5Config_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnM5Config_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnM5Config_ExtIEsCls
(
Czt_ExtnM5Config_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnM5Config_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnM5Config_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnM5Config_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnM5Config_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_M5Config_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_M5Config_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_M5Config_ExtIEs
(
CztProtExtnField_M5Config_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_M5Config_ExtIEs(param, ptr, mBuf)
CztProtExtnField_M5Config_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_M5Config_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnM5Config_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_M5Config_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_M5Config_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_M5Config_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_M5Config_ExtIEs
(
CztProtExtnCont_M5Config_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_M5Config_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_M5Config_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_M5Config_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_M5Config_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_M5Config_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_M5Config_ExtIEs */



/*
* FUN : cmUnpkCztM5Config
*  DESC: Function to Unpack CztM5Config structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztM5Config
(
CztM5Config *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztM5Config(param, ptr, mBuf)
CztM5Config *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztM5Config) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztM5period, &param->m5period, mBuf); 
		CMCHKUNPK(cmUnpkCztLinks_to_log, &param->m5_links_to_log, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_M5Config_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztM5Config */

#define cmUnpkCztMDT_Actvn cmUnpkTknU32

#define cmUnpkCztMeasurementsToActivate cmUnpkTknBStr32 
#define cmUnpkCztM1RprtngTrigger cmUnpkTknU32

#define cmUnpkCztThreshold_RSRP cmUnpkTknU32 
#define cmUnpkCztThreshold_RSRQ cmUnpkTknU32 


/*
* FUN : cmUnpkCztMeasurementThresholdA2
*  DESC: Function to Unpack CztMeasurementThresholdA2 structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztMeasurementThresholdA2
(
CztMeasurementThresholdA2 *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztMeasurementThresholdA2(param, ptr, mBuf)
CztMeasurementThresholdA2 *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztMeasurementThresholdA2) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case MEASUREMENTTHRESHOLDA2_THRESHOLD_RSRP :
				CMCHKUNPK(cmUnpkCztThreshold_RSRP, &param->val.threshold_RSRP, mBuf); 
				break;
			case MEASUREMENTTHRESHOLDA2_THRESHOLD_RSRQ :
				CMCHKUNPK(cmUnpkCztThreshold_RSRQ, &param->val.threshold_RSRQ, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztMeasurementThresholdA2 */



/*
* FUN : cmUnpkCzt_ExtnM1ThresholdEventA2_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnM1ThresholdEventA2_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnM1ThresholdEventA2_ExtIEsCls
(
Czt_ExtnM1ThresholdEventA2_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnM1ThresholdEventA2_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnM1ThresholdEventA2_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnM1ThresholdEventA2_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnM1ThresholdEventA2_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_M1ThresholdEventA2_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_M1ThresholdEventA2_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_M1ThresholdEventA2_ExtIEs
(
CztProtExtnField_M1ThresholdEventA2_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_M1ThresholdEventA2_ExtIEs(param, ptr, mBuf)
CztProtExtnField_M1ThresholdEventA2_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_M1ThresholdEventA2_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnM1ThresholdEventA2_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_M1ThresholdEventA2_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_M1ThresholdEventA2_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_M1ThresholdEventA2_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_M1ThresholdEventA2_ExtIEs
(
CztProtExtnCont_M1ThresholdEventA2_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_M1ThresholdEventA2_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_M1ThresholdEventA2_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_M1ThresholdEventA2_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_M1ThresholdEventA2_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_M1ThresholdEventA2_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_M1ThresholdEventA2_ExtIEs */



/*
* FUN : cmUnpkCztM1ThresholdEventA2
*  DESC: Function to Unpack CztM1ThresholdEventA2 structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztM1ThresholdEventA2
(
CztM1ThresholdEventA2 *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztM1ThresholdEventA2(param, ptr, mBuf)
CztM1ThresholdEventA2 *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztM1ThresholdEventA2) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztMeasurementThresholdA2, &param->measurementThreshold, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_M1ThresholdEventA2_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztM1ThresholdEventA2 */

#define cmUnpkCztReportIntervalMDT cmUnpkTknU32

#define cmUnpkCztReportAmountMDT cmUnpkTknU32



/*
* FUN : cmUnpkCzt_ExtnM1PeriodicRprtng_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnM1PeriodicRprtng_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnM1PeriodicRprtng_ExtIEsCls
(
Czt_ExtnM1PeriodicRprtng_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnM1PeriodicRprtng_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnM1PeriodicRprtng_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnM1PeriodicRprtng_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnM1PeriodicRprtng_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_M1PeriodicRprtng_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_M1PeriodicRprtng_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_M1PeriodicRprtng_ExtIEs
(
CztProtExtnField_M1PeriodicRprtng_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_M1PeriodicRprtng_ExtIEs(param, ptr, mBuf)
CztProtExtnField_M1PeriodicRprtng_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_M1PeriodicRprtng_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnM1PeriodicRprtng_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_M1PeriodicRprtng_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_M1PeriodicRprtng_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_M1PeriodicRprtng_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_M1PeriodicRprtng_ExtIEs
(
CztProtExtnCont_M1PeriodicRprtng_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_M1PeriodicRprtng_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_M1PeriodicRprtng_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_M1PeriodicRprtng_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_M1PeriodicRprtng_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_M1PeriodicRprtng_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_M1PeriodicRprtng_ExtIEs */



/*
* FUN : cmUnpkCztM1PeriodicRprtng
*  DESC: Function to Unpack CztM1PeriodicRprtng structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztM1PeriodicRprtng
(
CztM1PeriodicRprtng *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztM1PeriodicRprtng(param, ptr, mBuf)
CztM1PeriodicRprtng *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztM1PeriodicRprtng) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztReportIntervalMDT, &param->reportInterval, mBuf); 
		CMCHKUNPK(cmUnpkCztReportAmountMDT, &param->reportAmount, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_M1PeriodicRprtng_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztM1PeriodicRprtng */

#define cmUnpkCztMDT_Loc_Info cmUnpkTknBStr32 


/*
* FUN : cmUnpkCztMDTPLMNLst
*  DESC: Function to Unpack CztMDTPLMNLst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztMDTPLMNLst
(
CztMDTPLMNLst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztMDTPLMNLst(param, ptr, mBuf)
CztMDTPLMNLst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztMDTPLMNLst) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztPLMN_Identity)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CZUCHKUNPKPTR(cmUnpkCztPLMN_Identity, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztMDTPLMNLst */



/*
* FUN : cmUnpkCzt_ExtnMDT_Config_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnMDT_Config_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnMDT_Config_ExtIEsCls
(
Czt_ExtnMDT_Config_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnMDT_Config_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnMDT_Config_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnMDT_Config_ExtIEsCls) 
	
	switch (val)
	{
		case Cztid_M3Config:
			CMCHKUNPKPTR(cmUnpkCztM3Config, &param->u.cztM3Config, ptr, mBuf);
			break;
		case Cztid_M4Config:
			CMCHKUNPKPTR(cmUnpkCztM4Config, &param->u.cztM4Config, ptr, mBuf);
			break;
		case Cztid_M5Config:
			CMCHKUNPKPTR(cmUnpkCztM5Config, &param->u.cztM5Config, ptr, mBuf);
			break;
		case Cztid_MDT_Loc_Info:
			CMCHKUNPK(cmUnpkCztMDT_Loc_Info, &param->u.cztMDT_Loc_Info, mBuf); 
			break;
		case Cztid_SignallingBasedMDTPLMNLst:
			CMCHKUNPKPTR(cmUnpkCztMDTPLMNLst, &param->u.cztMDTPLMNLst, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ExtnMDT_Config_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_MDT_Config_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_MDT_Config_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_MDT_Config_ExtIEs
(
CztProtExtnField_MDT_Config_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_MDT_Config_ExtIEs(param, ptr, mBuf)
CztProtExtnField_MDT_Config_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_MDT_Config_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnMDT_Config_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_MDT_Config_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_MDT_Config_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_MDT_Config_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_MDT_Config_ExtIEs
(
CztProtExtnCont_MDT_Config_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_MDT_Config_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_MDT_Config_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_MDT_Config_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_MDT_Config_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_MDT_Config_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_MDT_Config_ExtIEs */



/*
* FUN : cmUnpkCztMDT_Config
*  DESC: Function to Unpack CztMDT_Config structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztMDT_Config
(
CztMDT_Config *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztMDT_Config(param, ptr, mBuf)
CztMDT_Config *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztMDT_Config) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztMDT_Actvn, &param->mdt_Actvn, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztAreaScopeOfMDT, &param->areaScopeOfMDT, ptr, mBuf); 
		CMCHKUNPK(cmUnpkCztMeasurementsToActivate, &param->measurementsToActivate, mBuf); 
		CMCHKUNPK(cmUnpkCztM1RprtngTrigger, &param->m1reportingTrigger, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztM1ThresholdEventA2, &param->m1thresholdeventA2, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztM1PeriodicRprtng, &param->m1periodicRprtng, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_MDT_Config_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztMDT_Config */

#define cmUnpkCztMeasurement_ID cmUnpkTknU32 
#define cmUnpkCztMBMS_Service_Area_Identity cmUnpkTknStr4 


/*
* FUN : cmUnpkCztMBMS_Service_Area_Identity_Lst
*  DESC: Function to Unpack CztMBMS_Service_Area_Identity_Lst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztMBMS_Service_Area_Identity_Lst
(
CztMBMS_Service_Area_Identity_Lst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztMBMS_Service_Area_Identity_Lst(param, ptr, mBuf)
CztMBMS_Service_Area_Identity_Lst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztMBMS_Service_Area_Identity_Lst) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztMBMS_Service_Area_Identity)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPK(cmUnpkCztMBMS_Service_Area_Identity, &(param->member[i]), mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztMBMS_Service_Area_Identity_Lst */

#define cmUnpkCztRadioframeAllocnPeriod cmUnpkTknU32

#define cmUnpkCztRadioframeAllocnOffset cmUnpkTknU32 
#define cmUnpkCztOneframe cmUnpkTknBStr32 


/*
* FUN : cmUnpkCztSubframeAllocn
*  DESC: Function to Unpack CztSubframeAllocn structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztSubframeAllocn
(
CztSubframeAllocn *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztSubframeAllocn(param, ptr, mBuf)
CztSubframeAllocn *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztSubframeAllocn) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case SUBFRAMEALLOCN_ONEFRAME :
				CMCHKUNPK(cmUnpkCztOneframe, &param->val.oneframe, mBuf); 
				break;
			case SUBFRAMEALLOCN_FOURFRAMES :
				CMCHKUNPK(cmUnpkCztFourframes, &param->val.fourframes, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztSubframeAllocn */



/*
* FUN : cmUnpkCzt_ExtnMBSFN_Subframe_Info_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnMBSFN_Subframe_Info_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnMBSFN_Subframe_Info_ExtIEsCls
(
Czt_ExtnMBSFN_Subframe_Info_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnMBSFN_Subframe_Info_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnMBSFN_Subframe_Info_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnMBSFN_Subframe_Info_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnMBSFN_Subframe_Info_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_MBSFN_Subframe_Info_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_MBSFN_Subframe_Info_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_MBSFN_Subframe_Info_ExtIEs
(
CztProtExtnField_MBSFN_Subframe_Info_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_MBSFN_Subframe_Info_ExtIEs(param, ptr, mBuf)
CztProtExtnField_MBSFN_Subframe_Info_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_MBSFN_Subframe_Info_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnMBSFN_Subframe_Info_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_MBSFN_Subframe_Info_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_MBSFN_Subframe_Info_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_MBSFN_Subframe_Info_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_MBSFN_Subframe_Info_ExtIEs
(
CztProtExtnCont_MBSFN_Subframe_Info_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_MBSFN_Subframe_Info_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_MBSFN_Subframe_Info_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_MBSFN_Subframe_Info_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_MBSFN_Subframe_Info_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_MBSFN_Subframe_Info_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_MBSFN_Subframe_Info_ExtIEs */



/*
* FUN : cmUnpkCztMBSFN_Subframe_Info
*  DESC: Function to Unpack CztMBSFN_Subframe_Info structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztMBSFN_Subframe_Info
(
CztMBSFN_Subframe_Info *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztMBSFN_Subframe_Info(param, ptr, mBuf)
CztMBSFN_Subframe_Info *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztMBSFN_Subframe_Info) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztRadioframeAllocnPeriod, &param->radioframeAllocnPeriod, mBuf); 
		CMCHKUNPK(cmUnpkCztRadioframeAllocnOffset, &param->radioframeAllocnOffset, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztSubframeAllocn, &param->subframeAllocn, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_MBSFN_Subframe_Info_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztMBSFN_Subframe_Info */



/*
* FUN : cmUnpkCztMBSFN_Subframe_Infolist
*  DESC: Function to Unpack CztMBSFN_Subframe_Infolist structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztMBSFN_Subframe_Infolist
(
CztMBSFN_Subframe_Infolist *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztMBSFN_Subframe_Infolist(param, ptr, mBuf)
CztMBSFN_Subframe_Infolist *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztMBSFN_Subframe_Infolist) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztMBSFN_Subframe_Info)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztMBSFN_Subframe_Info, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztMBSFN_Subframe_Infolist */

#define cmUnpkCztManagementBasedMDTallowed cmUnpkTknU32

#define cmUnpkCztMobilityParamsModificationRangehandoverTriggerChangeLowerLimit cmUnpkTknS32 
#define cmUnpkCztMobilityParamsModificationRangehandoverTriggerChangeUpperLimit cmUnpkTknS32 


/*
* FUN : cmUnpkCztMobilityParamsModificationRange
*  DESC: Function to Unpack CztMobilityParamsModificationRange structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztMobilityParamsModificationRange
(
CztMobilityParamsModificationRange *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztMobilityParamsModificationRange(param, ptr, mBuf)
CztMobilityParamsModificationRange *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztMobilityParamsModificationRange) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztMobilityParamsModificationRangehandoverTriggerChangeLowerLimit, &param->handoverTriggerChangeLowerLimit, mBuf); 
		CMCHKUNPK(cmUnpkCztMobilityParamsModificationRangehandoverTriggerChangeUpperLimit, &param->handoverTriggerChangeUpperLimit, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztMobilityParamsModificationRange */

#define cmUnpkCztMobilityParamsInformhandoverTriggerChange cmUnpkTknS32 


/*
* FUN : cmUnpkCztMobilityParamsInform
*  DESC: Function to Unpack CztMobilityParamsInform structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztMobilityParamsInform
(
CztMobilityParamsInform *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztMobilityParamsInform(param, ptr, mBuf)
CztMobilityParamsInform *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztMobilityParamsInform) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztMobilityParamsInformhandoverTriggerChange, &param->handoverTriggerChange, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztMobilityParamsInform */



/*
* FUN : cmUnpkCzt_ExtnBandInfo_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnBandInfo_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnBandInfo_ExtIEsCls
(
Czt_ExtnBandInfo_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnBandInfo_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnBandInfo_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnBandInfo_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnBandInfo_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_BandInfo_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_BandInfo_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_BandInfo_ExtIEs
(
CztProtExtnField_BandInfo_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_BandInfo_ExtIEs(param, ptr, mBuf)
CztProtExtnField_BandInfo_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_BandInfo_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnBandInfo_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_BandInfo_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_BandInfo_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_BandInfo_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_BandInfo_ExtIEs
(
CztProtExtnCont_BandInfo_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_BandInfo_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_BandInfo_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_BandInfo_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_BandInfo_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_BandInfo_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_BandInfo_ExtIEs */



/*
* FUN : cmUnpkCztBandInfo
*  DESC: Function to Unpack CztBandInfo structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztBandInfo
(
CztBandInfo *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztBandInfo(param, ptr, mBuf)
CztBandInfo *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztBandInfo) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztFreqBandIndicator, &param->freqBandIndicator, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_BandInfo_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztBandInfo */



/*
* FUN : cmUnpkCztMultibandInfoLst
*  DESC: Function to Unpack CztMultibandInfoLst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztMultibandInfoLst
(
CztMultibandInfoLst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztMultibandInfoLst(param, ptr, mBuf)
CztMultibandInfoLst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztMultibandInfoLst) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztBandInfo)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztBandInfo, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztMultibandInfoLst */

#define cmUnpkCztPCI cmUnpkTknU32 


/*
* FUN : cmUnpkCzt_ExtnNeighbour_Inform_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnNeighbour_Inform_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnNeighbour_Inform_ExtIEsCls
(
Czt_ExtnNeighbour_Inform_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnNeighbour_Inform_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnNeighbour_Inform_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnNeighbour_Inform_ExtIEsCls) 
	
	switch (val)
	{
		case Cztid_NeighbourTAC:
			CMCHKUNPK(cmUnpkCztTAC, &param->u.cztTAC, mBuf); 
			break;
		case Cztid_eARFCNExtn:
			CMCHKUNPK(cmUnpkCztEARFCNExtn, &param->u.cztEARFCNExtn, mBuf); 
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ExtnNeighbour_Inform_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_Neighbour_Inform_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_Neighbour_Inform_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_Neighbour_Inform_ExtIEs
(
CztProtExtnField_Neighbour_Inform_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_Neighbour_Inform_ExtIEs(param, ptr, mBuf)
CztProtExtnField_Neighbour_Inform_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_Neighbour_Inform_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnNeighbour_Inform_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_Neighbour_Inform_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_Neighbour_Inform_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_Neighbour_Inform_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_Neighbour_Inform_ExtIEs
(
CztProtExtnCont_Neighbour_Inform_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_Neighbour_Inform_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_Neighbour_Inform_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_Neighbour_Inform_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_Neighbour_Inform_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_Neighbour_Inform_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_Neighbour_Inform_ExtIEs */



/*
* FUN : cmUnpkCztNeighbour_InformMember
*  DESC: Function to Unpack CztNeighbour_InformMember structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztNeighbour_InformMember
(
CztNeighbour_InformMember *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztNeighbour_InformMember(param, ptr, mBuf)
CztNeighbour_InformMember *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztNeighbour_InformMember) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztECGI, &param->eCGI, ptr, mBuf); 
		CMCHKUNPK(cmUnpkCztPCI, &param->pCI, mBuf); 
		CMCHKUNPK(cmUnpkCztEARFCN, &param->eARFCN, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_Neighbour_Inform_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztNeighbour_InformMember */



/*
* FUN : cmUnpkCztNeighbour_Inform
*  DESC: Function to Unpack CztNeighbour_Inform structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztNeighbour_Inform
(
CztNeighbour_Inform *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztNeighbour_Inform(param, ptr, mBuf)
CztNeighbour_Inform *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztNeighbour_Inform) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztNeighbour_InformMember)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztNeighbour_InformMember, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztNeighbour_Inform */

#define cmUnpkCztNumber_of_Antennaports cmUnpkTknU32

#define cmUnpkCztPRACH_ConfigrootSequenceIdx cmUnpkTknU32 
#define cmUnpkCztPRACH_ConfigzeroCorrelationIdx cmUnpkTknU32 
#define cmUnpkCztPRACH_ConfighighSpeedFlag cmUnpkTknU8

#define cmUnpkCztPRACH_Configprach_FreqOffset cmUnpkTknU32 
#define cmUnpkCztPRACH_Configprach_ConfigIdx cmUnpkTknU32 


/*
* FUN : cmUnpkCzt_ExtnPRACH_Config_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnPRACH_Config_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnPRACH_Config_ExtIEsCls
(
Czt_ExtnPRACH_Config_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnPRACH_Config_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnPRACH_Config_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnPRACH_Config_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnPRACH_Config_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_PRACH_Config_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_PRACH_Config_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_PRACH_Config_ExtIEs
(
CztProtExtnField_PRACH_Config_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_PRACH_Config_ExtIEs(param, ptr, mBuf)
CztProtExtnField_PRACH_Config_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_PRACH_Config_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnPRACH_Config_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_PRACH_Config_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_PRACH_Config_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_PRACH_Config_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_PRACH_Config_ExtIEs
(
CztProtExtnCont_PRACH_Config_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_PRACH_Config_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_PRACH_Config_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_PRACH_Config_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_PRACH_Config_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_PRACH_Config_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_PRACH_Config_ExtIEs */



/*
* FUN : cmUnpkCztPRACH_Config
*  DESC: Function to Unpack CztPRACH_Config structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztPRACH_Config
(
CztPRACH_Config *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztPRACH_Config(param, ptr, mBuf)
CztPRACH_Config *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztPRACH_Config) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztPRACH_ConfigrootSequenceIdx, &param->rootSequenceIdx, mBuf); 
		CMCHKUNPK(cmUnpkCztPRACH_ConfigzeroCorrelationIdx, &param->zeroCorrelationIdx, mBuf); 
		CMCHKUNPK(cmUnpkCztPRACH_ConfighighSpeedFlag, &param->highSpeedFlag, mBuf); 
		CMCHKUNPK(cmUnpkCztPRACH_Configprach_FreqOffset, &param->prach_FreqOffset, mBuf); 
		CMCHKUNPK(cmUnpkCztPRACH_Configprach_ConfigIdx, &param->prach_ConfigIdx, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_PRACH_Config_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztPRACH_Config */

#define cmUnpkCztUL_GBR_PRB_usage cmUnpkTknU32 
#define cmUnpkCztUL_non_GBR_PRB_usage cmUnpkTknU32 
#define cmUnpkCztUL_Total_PRB_usage cmUnpkTknU32 


/*
* FUN : cmUnpkCzt_ExtnRadioResStatus_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnRadioResStatus_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnRadioResStatus_ExtIEsCls
(
Czt_ExtnRadioResStatus_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnRadioResStatus_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnRadioResStatus_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnRadioResStatus_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnRadioResStatus_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_RadioResStatus_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_RadioResStatus_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_RadioResStatus_ExtIEs
(
CztProtExtnField_RadioResStatus_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_RadioResStatus_ExtIEs(param, ptr, mBuf)
CztProtExtnField_RadioResStatus_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_RadioResStatus_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnRadioResStatus_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_RadioResStatus_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_RadioResStatus_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_RadioResStatus_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_RadioResStatus_ExtIEs
(
CztProtExtnCont_RadioResStatus_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_RadioResStatus_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_RadioResStatus_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_RadioResStatus_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_RadioResStatus_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_RadioResStatus_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_RadioResStatus_ExtIEs */



/*
* FUN : cmUnpkCztRadioResStatus
*  DESC: Function to Unpack CztRadioResStatus structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztRadioResStatus
(
CztRadioResStatus *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztRadioResStatus(param, ptr, mBuf)
CztRadioResStatus *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztRadioResStatus) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztDL_GBR_PRB_usage, &param->dL_GBR_PRB_usage, mBuf); 
		CMCHKUNPK(cmUnpkCztUL_GBR_PRB_usage, &param->uL_GBR_PRB_usage, mBuf); 
		CMCHKUNPK(cmUnpkCztDL_non_GBR_PRB_usage, &param->dL_non_GBR_PRB_usage, mBuf); 
		CMCHKUNPK(cmUnpkCztUL_non_GBR_PRB_usage, &param->uL_non_GBR_PRB_usage, mBuf); 
		CMCHKUNPK(cmUnpkCztDL_Total_PRB_usage, &param->dL_Total_PRB_usage, mBuf); 
		CMCHKUNPK(cmUnpkCztUL_Total_PRB_usage, &param->uL_Total_PRB_usage, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_RadioResStatus_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztRadioResStatus */

#define cmUnpkCztReceiveStatusofULPDCPSDUs cmUnpkTknStrBSXL 
#define cmUnpkCztReceiveStatusOfULPDCPSDUsExtended cmUnpkTknStrBSXL 
#define cmUnpkCztRegistration_Rqst cmUnpkTknU32

#define cmUnpkCztRNTP_Threshold cmUnpkTknU32

#define cmUnpkCztRelativeNarrowbandTxPowerrNTP_PerPRB cmUnpkTknStrBSXL 
#define cmUnpkCztRelativeNarrowbandTxPowernumberOfCellSpecificAntennaPorts cmUnpkTknU32

#define cmUnpkCztRelativeNarrowbandTxPowerp_B cmUnpkTknU32 
#define cmUnpkCztRelativeNarrowbandTxPowerpDCCH_InterferenceImpact cmUnpkTknU32 


/*
* FUN : cmUnpkCzt_ExtnRelativeNarrowbandTxPower_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnRelativeNarrowbandTxPower_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnRelativeNarrowbandTxPower_ExtIEsCls
(
Czt_ExtnRelativeNarrowbandTxPower_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnRelativeNarrowbandTxPower_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnRelativeNarrowbandTxPower_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnRelativeNarrowbandTxPower_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnRelativeNarrowbandTxPower_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_RelativeNarrowbandTxPower_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_RelativeNarrowbandTxPower_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_RelativeNarrowbandTxPower_ExtIEs
(
CztProtExtnField_RelativeNarrowbandTxPower_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_RelativeNarrowbandTxPower_ExtIEs(param, ptr, mBuf)
CztProtExtnField_RelativeNarrowbandTxPower_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_RelativeNarrowbandTxPower_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnRelativeNarrowbandTxPower_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_RelativeNarrowbandTxPower_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_RelativeNarrowbandTxPower_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_RelativeNarrowbandTxPower_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_RelativeNarrowbandTxPower_ExtIEs
(
CztProtExtnCont_RelativeNarrowbandTxPower_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_RelativeNarrowbandTxPower_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_RelativeNarrowbandTxPower_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_RelativeNarrowbandTxPower_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_RelativeNarrowbandTxPower_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_RelativeNarrowbandTxPower_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_RelativeNarrowbandTxPower_ExtIEs */



/*
* FUN : cmUnpkCztRelativeNarrowbandTxPower
*  DESC: Function to Unpack CztRelativeNarrowbandTxPower structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztRelativeNarrowbandTxPower
(
CztRelativeNarrowbandTxPower *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztRelativeNarrowbandTxPower(param, ptr, mBuf)
CztRelativeNarrowbandTxPower *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztRelativeNarrowbandTxPower) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztRelativeNarrowbandTxPowerrNTP_PerPRB, &param->rNTP_PerPRB, ptr, mBuf); 
		CMCHKUNPK(cmUnpkCztRNTP_Threshold, &param->rNTP_Threshold, mBuf); 
		CMCHKUNPK(cmUnpkCztRelativeNarrowbandTxPowernumberOfCellSpecificAntennaPorts, &param->numberOfCellSpecificAntennaPorts, mBuf); 
		CMCHKUNPK(cmUnpkCztRelativeNarrowbandTxPowerp_B, &param->p_B, mBuf); 
		CMCHKUNPK(cmUnpkCztRelativeNarrowbandTxPowerpDCCH_InterferenceImpact, &param->pDCCH_InterferenceImpact, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_RelativeNarrowbandTxPower_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztRelativeNarrowbandTxPower */

#define cmUnpkCztReportCharacteristics cmUnpkTknBStr32 
#define cmUnpkCztRRC_Cntxt cmUnpkTknStrOSXL 
#define cmUnpkCztRRCConnReestabIndicator cmUnpkTknU32

#define cmUnpkCztRRCConnSetupIndicator cmUnpkTknU32



/*
* FUN : cmUnpkCzt_ExtnS1TNLLoadIndicator_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnS1TNLLoadIndicator_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnS1TNLLoadIndicator_ExtIEsCls
(
Czt_ExtnS1TNLLoadIndicator_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnS1TNLLoadIndicator_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnS1TNLLoadIndicator_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnS1TNLLoadIndicator_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnS1TNLLoadIndicator_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_S1TNLLoadIndicator_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_S1TNLLoadIndicator_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_S1TNLLoadIndicator_ExtIEs
(
CztProtExtnField_S1TNLLoadIndicator_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_S1TNLLoadIndicator_ExtIEs(param, ptr, mBuf)
CztProtExtnField_S1TNLLoadIndicator_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_S1TNLLoadIndicator_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnS1TNLLoadIndicator_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_S1TNLLoadIndicator_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_S1TNLLoadIndicator_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_S1TNLLoadIndicator_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_S1TNLLoadIndicator_ExtIEs
(
CztProtExtnCont_S1TNLLoadIndicator_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_S1TNLLoadIndicator_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_S1TNLLoadIndicator_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_S1TNLLoadIndicator_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_S1TNLLoadIndicator_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_S1TNLLoadIndicator_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_S1TNLLoadIndicator_ExtIEs */



/*
* FUN : cmUnpkCztS1TNLLoadIndicator
*  DESC: Function to Unpack CztS1TNLLoadIndicator structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztS1TNLLoadIndicator
(
CztS1TNLLoadIndicator *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztS1TNLLoadIndicator(param, ptr, mBuf)
CztS1TNLLoadIndicator *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztS1TNLLoadIndicator) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztLoadIndicator, &param->dLS1TNLLoadIndicator, mBuf); 
		CMCHKUNPK(cmUnpkCztLoadIndicator, &param->uLS1TNLLoadIndicator, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_S1TNLLoadIndicator_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztS1TNLLoadIndicator */



/*
* FUN : cmUnpkCzt_ExtnSrvdCell_Inform_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnSrvdCell_Inform_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnSrvdCell_Inform_ExtIEsCls
(
Czt_ExtnSrvdCell_Inform_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnSrvdCell_Inform_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnSrvdCell_Inform_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnSrvdCell_Inform_ExtIEsCls) 
	
	switch (val)
	{
		case Cztid_Number_of_Antennaports:
			CMCHKUNPK(cmUnpkCztNumber_of_Antennaports, &param->u.cztNumber_of_Antennaports, mBuf); 
			break;
		case Cztid_PRACH_Config:
			CMCHKUNPKPTR(cmUnpkCztPRACH_Config, &param->u.cztPRACH_Config, ptr, mBuf);
			break;
		case Cztid_MBSFN_Subframe_Info:
			CMCHKUNPKPTR(cmUnpkCztMBSFN_Subframe_Infolist, &param->u.cztMBSFN_Subframe_Infolist, ptr, mBuf);
			break;
		case Cztid_CSG_Id:
			CMCHKUNPK(cmUnpkCztCSG_Id, &param->u.cztCSG_Id, mBuf); 
			break;
		case Cztid_MBMS_Service_Area_Lst:
			CMCHKUNPKPTR(cmUnpkCztMBMS_Service_Area_Identity_Lst, &param->u.cztMBMS_Service_Area_Identity_Lst, ptr, mBuf);
			break;
		case Cztid_MultibandInfoLst:
			CMCHKUNPKPTR(cmUnpkCztMultibandInfoLst, &param->u.cztMultibandInfoLst, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ExtnSrvdCell_Inform_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_SrvdCell_Inform_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_SrvdCell_Inform_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_SrvdCell_Inform_ExtIEs
(
CztProtExtnField_SrvdCell_Inform_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_SrvdCell_Inform_ExtIEs(param, ptr, mBuf)
CztProtExtnField_SrvdCell_Inform_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_SrvdCell_Inform_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnSrvdCell_Inform_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_SrvdCell_Inform_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_SrvdCell_Inform_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_SrvdCell_Inform_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_SrvdCell_Inform_ExtIEs
(
CztProtExtnCont_SrvdCell_Inform_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_SrvdCell_Inform_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_SrvdCell_Inform_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_SrvdCell_Inform_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_SrvdCell_Inform_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_SrvdCell_Inform_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_SrvdCell_Inform_ExtIEs */



/*
* FUN : cmUnpkCztSrvdCell_Inform
*  DESC: Function to Unpack CztSrvdCell_Inform structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztSrvdCell_Inform
(
CztSrvdCell_Inform *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztSrvdCell_Inform(param, ptr, mBuf)
CztSrvdCell_Inform *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztSrvdCell_Inform) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztPCI, &param->pCI, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztECGI, &param->cellId, ptr, mBuf); 
		CMCHKUNPK(cmUnpkCztTAC, &param->tAC, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztBroadcastPLMNs_Item, &param->broadcastPLMNs, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztEUTRA_Mode_Info, &param->eUTRA_Mode_Info, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_SrvdCell_Inform_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztSrvdCell_Inform */



/*
* FUN : cmUnpkCzt_ExtnSrvdCell_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnSrvdCell_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnSrvdCell_ExtIEsCls
(
Czt_ExtnSrvdCell_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnSrvdCell_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnSrvdCell_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnSrvdCell_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnSrvdCell_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_SrvdCell_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_SrvdCell_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_SrvdCell_ExtIEs
(
CztProtExtnField_SrvdCell_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_SrvdCell_ExtIEs(param, ptr, mBuf)
CztProtExtnField_SrvdCell_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_SrvdCell_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnSrvdCell_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_SrvdCell_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_SrvdCell_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_SrvdCell_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_SrvdCell_ExtIEs
(
CztProtExtnCont_SrvdCell_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_SrvdCell_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_SrvdCell_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_SrvdCell_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_SrvdCell_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_SrvdCell_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_SrvdCell_ExtIEs */



/*
* FUN : cmUnpkCztSrvdCellsMember
*  DESC: Function to Unpack CztSrvdCellsMember structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztSrvdCellsMember
(
CztSrvdCellsMember *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztSrvdCellsMember(param, ptr, mBuf)
CztSrvdCellsMember *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztSrvdCellsMember) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztSrvdCell_Inform, &param->servedCellInfo, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztNeighbour_Inform, &param->neighbour_Info, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_SrvdCell_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztSrvdCellsMember */



/*
* FUN : cmUnpkCztSrvdCells
*  DESC: Function to Unpack CztSrvdCells structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztSrvdCells
(
CztSrvdCells *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztSrvdCells(param, ptr, mBuf)
CztSrvdCells *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztSrvdCells) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztSrvdCellsMember)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztSrvdCellsMember, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztSrvdCells */

#define cmUnpkCztShortMAC_I cmUnpkTknBStr32 
#define cmUnpkCztSRVCCOperationPossible cmUnpkTknU32

#define cmUnpkCztSubscriberProfileIDforRFP cmUnpkTknU32 
#define cmUnpkCztTgetCellInUTRAN cmUnpkTknStrOSXL 
#define cmUnpkCztTgeteNBtoSrc_eNBTprntCont cmUnpkTknStrOSXL 
#define cmUnpkCztTimeToWait cmUnpkTknU32

#define cmUnpkCztTraceDepth cmUnpkTknU32

#define cmUnpkCztTraceCollectionEntityIPAddr cmUnpkTknStrBSXL 


/*
* FUN : cmUnpkCzt_ExtnTraceActvn_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnTraceActvn_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnTraceActvn_ExtIEsCls
(
Czt_ExtnTraceActvn_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnTraceActvn_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnTraceActvn_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnTraceActvn_ExtIEsCls) 
	
	switch (val)
	{
		case Cztid_MDTConfig:
			CMCHKUNPKPTR(cmUnpkCztMDT_Config, &param->u.cztMDT_Config, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ExtnTraceActvn_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_TraceActvn_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_TraceActvn_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_TraceActvn_ExtIEs
(
CztProtExtnField_TraceActvn_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_TraceActvn_ExtIEs(param, ptr, mBuf)
CztProtExtnField_TraceActvn_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_TraceActvn_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnTraceActvn_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_TraceActvn_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_TraceActvn_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_TraceActvn_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_TraceActvn_ExtIEs
(
CztProtExtnCont_TraceActvn_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_TraceActvn_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_TraceActvn_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_TraceActvn_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_TraceActvn_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_TraceActvn_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_TraceActvn_ExtIEs */



/*
* FUN : cmUnpkCztTraceActvn
*  DESC: Function to Unpack CztTraceActvn structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztTraceActvn
(
CztTraceActvn *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztTraceActvn(param, ptr, mBuf)
CztTraceActvn *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztTraceActvn) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CZUCHKUNPKPTR(cmUnpkCztEUTRANTraceID, &param->eUTRANTraceID, ptr, mBuf); 
		CMCHKUNPK(cmUnpkCztIntfsToTrace, &param->interfacesToTrace, mBuf); 
		CMCHKUNPK(cmUnpkCztTraceDepth, &param->traceDepth, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztTraceCollectionEntityIPAddr, &param->traceCollectionEntityIPAddr, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_TraceActvn_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztTraceActvn */



/*
* FUN : cmUnpkCztUE_HistoryInform
*  DESC: Function to Unpack CztUE_HistoryInform structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztUE_HistoryInform
(
CztUE_HistoryInform *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztUE_HistoryInform(param, ptr, mBuf)
CztUE_HistoryInform *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztUE_HistoryInform) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztLastVisitedCell_Item)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztLastVisitedCell_Item, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztUE_HistoryInform */

#define cmUnpkCztUE_S1AP_ID cmUnpkTknU32 
#define cmUnpkCztUE_X2AP_ID cmUnpkTknU32 


/*
* FUN : cmUnpkCzt_ExtnUEAgg_MaxBitrate_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnUEAgg_MaxBitrate_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnUEAgg_MaxBitrate_ExtIEsCls
(
Czt_ExtnUEAgg_MaxBitrate_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnUEAgg_MaxBitrate_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnUEAgg_MaxBitrate_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnUEAgg_MaxBitrate_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnUEAgg_MaxBitrate_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_UEAgg_MaxBitrate_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_UEAgg_MaxBitrate_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_UEAgg_MaxBitrate_ExtIEs
(
CztProtExtnField_UEAgg_MaxBitrate_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_UEAgg_MaxBitrate_ExtIEs(param, ptr, mBuf)
CztProtExtnField_UEAgg_MaxBitrate_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_UEAgg_MaxBitrate_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnUEAgg_MaxBitrate_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_UEAgg_MaxBitrate_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_UEAgg_MaxBitrate_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_UEAgg_MaxBitrate_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_UEAgg_MaxBitrate_ExtIEs
(
CztProtExtnCont_UEAgg_MaxBitrate_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_UEAgg_MaxBitrate_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_UEAgg_MaxBitrate_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_UEAgg_MaxBitrate_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_UEAgg_MaxBitrate_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_UEAgg_MaxBitrate_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_UEAgg_MaxBitrate_ExtIEs */



/*
* FUN : cmUnpkCztUEAggMaxBitRate
*  DESC: Function to Unpack CztUEAggMaxBitRate structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztUEAggMaxBitRate
(
CztUEAggMaxBitRate *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztUEAggMaxBitRate(param, ptr, mBuf)
CztUEAggMaxBitRate *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztUEAggMaxBitRate) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CZUCHKUNPKPTR(cmUnpkCztBitRate, &param->uEaggregateMaxBitRateDlnk, ptr, mBuf); 
		CZUCHKUNPKPTR(cmUnpkCztBitRate, &param->uEaggregateMaxBitRateUlnk, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_UEAgg_MaxBitrate_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztUEAggMaxBitRate */



/*
* FUN : cmUnpkCzt_ExtnUESecurCapabilities_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnUESecurCapabilities_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnUESecurCapabilities_ExtIEsCls
(
Czt_ExtnUESecurCapabilities_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnUESecurCapabilities_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnUESecurCapabilities_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnUESecurCapabilities_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnUESecurCapabilities_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_UESecurCapabilities_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_UESecurCapabilities_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_UESecurCapabilities_ExtIEs
(
CztProtExtnField_UESecurCapabilities_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_UESecurCapabilities_ExtIEs(param, ptr, mBuf)
CztProtExtnField_UESecurCapabilities_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_UESecurCapabilities_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnUESecurCapabilities_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_UESecurCapabilities_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_UESecurCapabilities_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_UESecurCapabilities_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_UESecurCapabilities_ExtIEs
(
CztProtExtnCont_UESecurCapabilities_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_UESecurCapabilities_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_UESecurCapabilities_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_UESecurCapabilities_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_UESecurCapabilities_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_UESecurCapabilities_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_UESecurCapabilities_ExtIEs */



/*
* FUN : cmUnpkCztUESecurCapabilities
*  DESC: Function to Unpack CztUESecurCapabilities structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztUESecurCapabilities
(
CztUESecurCapabilities *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztUESecurCapabilities(param, ptr, mBuf)
CztUESecurCapabilities *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztUESecurCapabilities) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztEncryptionAlgorithms, &param->encryptionAlgorithms, mBuf); 
		CMCHKUNPK(cmUnpkCztIntegrityProtectionAlgorithms, &param->integrityProtectionAlgorithms, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_UESecurCapabilities_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztUESecurCapabilities */

#define cmUnpkCztUL_InterferenceOverloadInd_Item cmUnpkTknU32



/*
* FUN : cmUnpkCztUL_InterferenceOverloadInd
*  DESC: Function to Unpack CztUL_InterferenceOverloadInd structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztUL_InterferenceOverloadInd
(
CztUL_InterferenceOverloadInd *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztUL_InterferenceOverloadInd(param, ptr, mBuf)
CztUL_InterferenceOverloadInd *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztUL_InterferenceOverloadInd) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztUL_InterferenceOverloadInd_Item)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPK(cmUnpkCztUL_InterferenceOverloadInd_Item, &(param->member[i]), mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztUL_InterferenceOverloadInd */

#define cmUnpkCztUL_HighInterferenceInd cmUnpkTknStrBSXL 


/*
* FUN : cmUnpkCzt_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsCls
(
Czt_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEs
(
CztProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnUL_HighInterferenceIndInfo_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEs
(
CztProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_UL_HighInterferenceIndInfo_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEs */



/*
* FUN : cmUnpkCztUL_HighInterferenceIndInfo_Item
*  DESC: Function to Unpack CztUL_HighInterferenceIndInfo_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztUL_HighInterferenceIndInfo_Item
(
CztUL_HighInterferenceIndInfo_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztUL_HighInterferenceIndInfo_Item(param, ptr, mBuf)
CztUL_HighInterferenceIndInfo_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztUL_HighInterferenceIndInfo_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztECGI, &param->target_Cell_ID, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztUL_HighInterferenceInd, &param->ul_interferenceindication, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_UL_HighInterferenceIndInfo_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztUL_HighInterferenceIndInfo_Item */



/*
* FUN : cmUnpkCztUL_HighInterferenceIndInfo
*  DESC: Function to Unpack CztUL_HighInterferenceIndInfo structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztUL_HighInterferenceIndInfo
(
CztUL_HighInterferenceIndInfo *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztUL_HighInterferenceIndInfo(param, ptr, mBuf)
CztUL_HighInterferenceIndInfo *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztUL_HighInterferenceIndInfo) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztUL_HighInterferenceIndInfo_Item)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztUL_HighInterferenceIndInfo_Item, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztUL_HighInterferenceIndInfo */

#define cmUnpkCztUE_RLF_Report_Cont cmUnpkTknStrOSXL 


/*
* FUN : cmUnpkCzt_ExtnE_RABs_ToBeSetup_ItemExtIEsCls
*  DESC: Function to Unpack Czt_ExtnE_RABs_ToBeSetup_ItemExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnE_RABs_ToBeSetup_ItemExtIEsCls
(
Czt_ExtnE_RABs_ToBeSetup_ItemExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnE_RABs_ToBeSetup_ItemExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnE_RABs_ToBeSetup_ItemExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnE_RABs_ToBeSetup_ItemExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnE_RABs_ToBeSetup_ItemExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_E_RABs_ToBeSetup_ItemExtIEs
*  DESC: Function to Unpack CztProtExtnField_E_RABs_ToBeSetup_ItemExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_E_RABs_ToBeSetup_ItemExtIEs
(
CztProtExtnField_E_RABs_ToBeSetup_ItemExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_E_RABs_ToBeSetup_ItemExtIEs(param, ptr, mBuf)
CztProtExtnField_E_RABs_ToBeSetup_ItemExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_E_RABs_ToBeSetup_ItemExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnE_RABs_ToBeSetup_ItemExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_E_RABs_ToBeSetup_ItemExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_E_RABs_ToBeSetup_ItemExtIEs
*  DESC: Function to Unpack CztProtExtnCont_E_RABs_ToBeSetup_ItemExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_E_RABs_ToBeSetup_ItemExtIEs
(
CztProtExtnCont_E_RABs_ToBeSetup_ItemExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_E_RABs_ToBeSetup_ItemExtIEs(param, ptr, mBuf)
CztProtExtnCont_E_RABs_ToBeSetup_ItemExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_E_RABs_ToBeSetup_ItemExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_E_RABs_ToBeSetup_ItemExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_E_RABs_ToBeSetup_ItemExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_E_RABs_ToBeSetup_ItemExtIEs */



/*
* FUN : cmUnpkCztE_RABs_ToBeSetup_Item
*  DESC: Function to Unpack CztE_RABs_ToBeSetup_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztE_RABs_ToBeSetup_Item
(
CztE_RABs_ToBeSetup_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztE_RABs_ToBeSetup_Item(param, ptr, mBuf)
CztE_RABs_ToBeSetup_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztE_RABs_ToBeSetup_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztE_RAB_ID, &param->e_RAB_ID, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztE_RAB_Lvl_QoS_Params, &param->e_RAB_Lvl_QoS_Params, ptr, mBuf); 
		CMCHKUNPK(cmUnpkCztDL_Fwding, &param->dL_Fwding, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztGTPtunnelEndpoint, &param->uL_GTPtunnelEndpoint, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_E_RABs_ToBeSetup_ItemExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztE_RABs_ToBeSetup_Item */



/*
* FUN : cmUnpkCzt_ValueE_RABs_ToBeSetup_ItemIEsCls
*  DESC: Function to Unpack Czt_ValueE_RABs_ToBeSetup_ItemIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueE_RABs_ToBeSetup_ItemIEsCls
(
Czt_ValueE_RABs_ToBeSetup_ItemIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueE_RABs_ToBeSetup_ItemIEsCls(param, val, ptr, mBuf)
Czt_ValueE_RABs_ToBeSetup_ItemIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueE_RABs_ToBeSetup_ItemIEsCls) 
	
	switch (val)
	{
		case Cztid_E_RABs_ToBeSetup_Item:
			CMCHKUNPKPTR(cmUnpkCztE_RABs_ToBeSetup_Item, &param->u.cztE_RABs_ToBeSetup_Item, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueE_RABs_ToBeSetup_ItemIEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_E_RABs_ToBeSetup_ItemIEs
*  DESC: Function to Unpack CztProtIE_Field_E_RABs_ToBeSetup_ItemIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_E_RABs_ToBeSetup_ItemIEs
(
CztProtIE_Field_E_RABs_ToBeSetup_ItemIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_E_RABs_ToBeSetup_ItemIEs(param, ptr, mBuf)
CztProtIE_Field_E_RABs_ToBeSetup_ItemIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_E_RABs_ToBeSetup_ItemIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueE_RABs_ToBeSetup_ItemIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_E_RABs_ToBeSetup_ItemIEs */

/* Element ------------- ProtocolIE-Single-Container ------------ */
#define cmUnpkCztProtIE_Single_Cont_E_RABs_ToBeSetup_ItemIEs cmUnpkCztProtIE_Field_E_RABs_ToBeSetup_ItemIEs


/*
* FUN : cmUnpkCztE_RABs_ToBeSetup_Lst
*  DESC: Function to Unpack CztE_RABs_ToBeSetup_Lst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztE_RABs_ToBeSetup_Lst
(
CztE_RABs_ToBeSetup_Lst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztE_RABs_ToBeSetup_Lst(param, ptr, mBuf)
CztE_RABs_ToBeSetup_Lst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztE_RABs_ToBeSetup_Lst) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Single_Cont_E_RABs_ToBeSetup_ItemIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Single_Cont_E_RABs_ToBeSetup_ItemIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztE_RABs_ToBeSetup_Lst */



/*
* FUN : cmUnpkCzt_ExtnUE_CntxtInform_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnUE_CntxtInform_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnUE_CntxtInform_ExtIEsCls
(
Czt_ExtnUE_CntxtInform_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnUE_CntxtInform_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnUE_CntxtInform_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnUE_CntxtInform_ExtIEsCls) 
	
	switch (val)
	{
		case Cztid_ManagementBasedMDTallowed:
			CMCHKUNPK(cmUnpkCztManagementBasedMDTallowed, &param->u.cztManagementBasedMDTallowed, mBuf); 
			break;
		case Cztid_ManagementBasedMDTPLMNLst:
			CMCHKUNPKPTR(cmUnpkCztMDTPLMNLst, &param->u.cztMDTPLMNLst, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ExtnUE_CntxtInform_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_UE_CntxtInform_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_UE_CntxtInform_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_UE_CntxtInform_ExtIEs
(
CztProtExtnField_UE_CntxtInform_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_UE_CntxtInform_ExtIEs(param, ptr, mBuf)
CztProtExtnField_UE_CntxtInform_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_UE_CntxtInform_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnUE_CntxtInform_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_UE_CntxtInform_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_UE_CntxtInform_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_UE_CntxtInform_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_UE_CntxtInform_ExtIEs
(
CztProtExtnCont_UE_CntxtInform_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_UE_CntxtInform_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_UE_CntxtInform_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_UE_CntxtInform_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_UE_CntxtInform_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_UE_CntxtInform_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_UE_CntxtInform_ExtIEs */



/*
* FUN : cmUnpkCztUE_CntxtInform
*  DESC: Function to Unpack CztUE_CntxtInform structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztUE_CntxtInform
(
CztUE_CntxtInform *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztUE_CntxtInform(param, ptr, mBuf)
CztUE_CntxtInform *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztUE_CntxtInform) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztUE_S1AP_ID, &param->mME_UE_S1AP_ID, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztUESecurCapabilities, &param->uESecurCapabilities, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztAS_SecurInform, &param->aS_SecurInform, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztUEAggMaxBitRate, &param->uEaggregateMaxBitRate, ptr, mBuf); 
		CMCHKUNPK(cmUnpkCztSubscriberProfileIDforRFP, &param->subscriberProfileIDforRFP, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztE_RABs_ToBeSetup_Lst, &param->e_RABs_ToBeSetup_Lst, ptr, mBuf); 
		CZUCHKUNPKPTR(cmUnpkCztRRC_Cntxt, &param->rRC_Cntxt, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztHovrRestrnLst, &param->handoverRestrnLst, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztLocRprtngInform, &param->locationRprtngInform, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_UE_CntxtInform_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztUE_CntxtInform */

#define cmUnpkCztMobilityInform cmUnpkTknBStr32 


/*
* FUN : cmUnpkCzt_ValueHovrRqst_IEsCls
*  DESC: Function to Unpack Czt_ValueHovrRqst_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueHovrRqst_IEsCls
(
Czt_ValueHovrRqst_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueHovrRqst_IEsCls(param, val, ptr, mBuf)
Czt_ValueHovrRqst_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueHovrRqst_IEsCls) 
	
	switch (val)
	{
		case Cztid_Old_eNB_UE_X2AP_ID:
			CMCHKUNPK(cmUnpkCztUE_X2AP_ID, &param->u.cztUE_X2AP_ID, mBuf); 
			break;
		case Cztid_Cause:
			CMCHKUNPKPTR(cmUnpkCztCause, &param->u.cztCause, ptr, mBuf);
			break;
		case Cztid_TgetCell_ID:
			CMCHKUNPKPTR(cmUnpkCztECGI, &param->u.cztECGI, ptr, mBuf);
			break;
		case Cztid_GUMMEI_ID:
			CMCHKUNPKPTR(cmUnpkCztGUMMEI, &param->u.cztGUMMEI, ptr, mBuf);
			break;
		case Cztid_UE_CntxtInform:
			CMCHKUNPKPTR(cmUnpkCztUE_CntxtInform, &param->u.cztUE_CntxtInform, ptr, mBuf);
			break;
		case Cztid_UE_HistoryInform:
			CMCHKUNPKPTR(cmUnpkCztUE_HistoryInform, &param->u.cztUE_HistoryInform, ptr, mBuf);
			break;
		case Cztid_TraceActvn:
			CMCHKUNPKPTR(cmUnpkCztTraceActvn, &param->u.cztTraceActvn, ptr, mBuf);
			break;
		case Cztid_SRVCCOperationPossible:
			CMCHKUNPK(cmUnpkCztSRVCCOperationPossible, &param->u.cztSRVCCOperationPossible, mBuf); 
			break;
		case Cztid_CSGMembershipStatus:
			CMCHKUNPK(cmUnpkCztCSGMembershipStatus, &param->u.cztCSGMembershipStatus, mBuf); 
			break;
		case Cztid_MobilityInform:
			CMCHKUNPK(cmUnpkCztMobilityInform, &param->u.cztMobilityInform, mBuf); 
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueHovrRqst_IEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_HovrRqst_IEs
*  DESC: Function to Unpack CztProtIE_Field_HovrRqst_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_HovrRqst_IEs
(
CztProtIE_Field_HovrRqst_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_HovrRqst_IEs(param, ptr, mBuf)
CztProtIE_Field_HovrRqst_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_HovrRqst_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueHovrRqst_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_HovrRqst_IEs */



/*
* FUN : cmUnpkCztProtIE_Cont_HovrRqst_IEs
*  DESC: Function to Unpack CztProtIE_Cont_HovrRqst_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Cont_HovrRqst_IEs
(
CztProtIE_Cont_HovrRqst_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Cont_HovrRqst_IEs(param, ptr, mBuf)
CztProtIE_Cont_HovrRqst_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtIE_Cont_HovrRqst_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Field_HovrRqst_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Field_HovrRqst_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtIE_Cont_HovrRqst_IEs */



/*
* FUN : cmUnpkCztHovrRqst
*  DESC: Function to Unpack CztHovrRqst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztHovrRqst
(
CztHovrRqst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztHovrRqst(param, ptr, mBuf)
CztHovrRqst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztHovrRqst) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztProtIE_Cont_HovrRqst_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztHovrRqst */



/*
* FUN : cmUnpkCzt_ExtnE_RABs_Admtd_Item_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnE_RABs_Admtd_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnE_RABs_Admtd_Item_ExtIEsCls
(
Czt_ExtnE_RABs_Admtd_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnE_RABs_Admtd_Item_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnE_RABs_Admtd_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnE_RABs_Admtd_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnE_RABs_Admtd_Item_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_E_RABs_Admtd_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_E_RABs_Admtd_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_E_RABs_Admtd_Item_ExtIEs
(
CztProtExtnField_E_RABs_Admtd_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_E_RABs_Admtd_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnField_E_RABs_Admtd_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_E_RABs_Admtd_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnE_RABs_Admtd_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_E_RABs_Admtd_Item_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_E_RABs_Admtd_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_E_RABs_Admtd_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_E_RABs_Admtd_Item_ExtIEs
(
CztProtExtnCont_E_RABs_Admtd_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_E_RABs_Admtd_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_E_RABs_Admtd_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_E_RABs_Admtd_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_E_RABs_Admtd_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_E_RABs_Admtd_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_E_RABs_Admtd_Item_ExtIEs */



/*
* FUN : cmUnpkCztE_RABs_Admtd_Item
*  DESC: Function to Unpack CztE_RABs_Admtd_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztE_RABs_Admtd_Item
(
CztE_RABs_Admtd_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztE_RABs_Admtd_Item(param, ptr, mBuf)
CztE_RABs_Admtd_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztE_RABs_Admtd_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztE_RAB_ID, &param->e_RAB_ID, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztGTPtunnelEndpoint, &param->uL_GTP_TunnelEndpoint, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztGTPtunnelEndpoint, &param->dL_GTP_TunnelEndpoint, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_E_RABs_Admtd_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztE_RABs_Admtd_Item */



/*
* FUN : cmUnpkCzt_ValueE_RABs_Admtd_ItemIEsCls
*  DESC: Function to Unpack Czt_ValueE_RABs_Admtd_ItemIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueE_RABs_Admtd_ItemIEsCls
(
Czt_ValueE_RABs_Admtd_ItemIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueE_RABs_Admtd_ItemIEsCls(param, val, ptr, mBuf)
Czt_ValueE_RABs_Admtd_ItemIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueE_RABs_Admtd_ItemIEsCls) 
	
	switch (val)
	{
		case Cztid_E_RABs_Admtd_Item:
			CMCHKUNPKPTR(cmUnpkCztE_RABs_Admtd_Item, &param->u.cztE_RABs_Admtd_Item, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueE_RABs_Admtd_ItemIEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_E_RABs_Admtd_ItemIEs
*  DESC: Function to Unpack CztProtIE_Field_E_RABs_Admtd_ItemIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_E_RABs_Admtd_ItemIEs
(
CztProtIE_Field_E_RABs_Admtd_ItemIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_E_RABs_Admtd_ItemIEs(param, ptr, mBuf)
CztProtIE_Field_E_RABs_Admtd_ItemIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_E_RABs_Admtd_ItemIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueE_RABs_Admtd_ItemIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_E_RABs_Admtd_ItemIEs */

/* Element ------------- ProtocolIE-Single-Container ------------ */
#define cmUnpkCztProtIE_Single_Cont_E_RABs_Admtd_ItemIEs cmUnpkCztProtIE_Field_E_RABs_Admtd_ItemIEs


/*
* FUN : cmUnpkCztE_RABs_Admtd_Lst
*  DESC: Function to Unpack CztE_RABs_Admtd_Lst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztE_RABs_Admtd_Lst
(
CztE_RABs_Admtd_Lst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztE_RABs_Admtd_Lst(param, ptr, mBuf)
CztE_RABs_Admtd_Lst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztE_RABs_Admtd_Lst) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Single_Cont_E_RABs_Admtd_ItemIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Single_Cont_E_RABs_Admtd_ItemIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztE_RABs_Admtd_Lst */



/*
* FUN : cmUnpkCzt_ValueHovrRqstAckg_IEsCls
*  DESC: Function to Unpack Czt_ValueHovrRqstAckg_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueHovrRqstAckg_IEsCls
(
Czt_ValueHovrRqstAckg_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueHovrRqstAckg_IEsCls(param, val, ptr, mBuf)
Czt_ValueHovrRqstAckg_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueHovrRqstAckg_IEsCls) 
	
	switch (val)
	{
		case Cztid_Old_eNB_UE_X2AP_ID:
			CMCHKUNPK(cmUnpkCztUE_X2AP_ID, &param->u.cztid_Old_eNB_UE_X2AP_ID, mBuf); 
			break;
		case Cztid_New_eNB_UE_X2AP_ID:
			CMCHKUNPK(cmUnpkCztUE_X2AP_ID, &param->u.cztid_New_eNB_UE_X2AP_ID, mBuf); 
			break;
		case Cztid_E_RABs_Admtd_Lst:
			CMCHKUNPKPTR(cmUnpkCztE_RABs_Admtd_Lst, &param->u.cztE_RABs_Admtd_Lst, ptr, mBuf);
			break;
		case Cztid_E_RABs_NotAdmtd_Lst:
			CMCHKUNPKPTR(cmUnpkCztE_RAB_Lst, &param->u.cztE_RAB_Lst, ptr, mBuf);
			break;
		case Cztid_TgeteNBtoSrc_eNBTprntCont:
			CZUCHKUNPKPTR(cmUnpkCztTgeteNBtoSrc_eNBTprntCont, &param->u.cztTgeteNBtoSrc_eNBTprntCont, ptr, mBuf); 
			break;
		case Cztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkCztCriticalityDiag, &param->u.cztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueHovrRqstAckg_IEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_HovrRqstAckg_IEs
*  DESC: Function to Unpack CztProtIE_Field_HovrRqstAckg_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_HovrRqstAckg_IEs
(
CztProtIE_Field_HovrRqstAckg_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_HovrRqstAckg_IEs(param, ptr, mBuf)
CztProtIE_Field_HovrRqstAckg_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_HovrRqstAckg_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueHovrRqstAckg_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_HovrRqstAckg_IEs */



/*
* FUN : cmUnpkCztProtIE_Cont_HovrRqstAckg_IEs
*  DESC: Function to Unpack CztProtIE_Cont_HovrRqstAckg_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Cont_HovrRqstAckg_IEs
(
CztProtIE_Cont_HovrRqstAckg_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Cont_HovrRqstAckg_IEs(param, ptr, mBuf)
CztProtIE_Cont_HovrRqstAckg_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtIE_Cont_HovrRqstAckg_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Field_HovrRqstAckg_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Field_HovrRqstAckg_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtIE_Cont_HovrRqstAckg_IEs */



/*
* FUN : cmUnpkCztHovrRqstAckg
*  DESC: Function to Unpack CztHovrRqstAckg structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztHovrRqstAckg
(
CztHovrRqstAckg *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztHovrRqstAckg(param, ptr, mBuf)
CztHovrRqstAckg *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztHovrRqstAckg) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztProtIE_Cont_HovrRqstAckg_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztHovrRqstAckg */



/*
* FUN : cmUnpkCzt_ValueHovrPrepFail_IEsCls
*  DESC: Function to Unpack Czt_ValueHovrPrepFail_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueHovrPrepFail_IEsCls
(
Czt_ValueHovrPrepFail_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueHovrPrepFail_IEsCls(param, val, ptr, mBuf)
Czt_ValueHovrPrepFail_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueHovrPrepFail_IEsCls) 
	
	switch (val)
	{
		case Cztid_Old_eNB_UE_X2AP_ID:
			CMCHKUNPK(cmUnpkCztUE_X2AP_ID, &param->u.cztUE_X2AP_ID, mBuf); 
			break;
		case Cztid_Cause:
			CMCHKUNPKPTR(cmUnpkCztCause, &param->u.cztCause, ptr, mBuf);
			break;
		case Cztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkCztCriticalityDiag, &param->u.cztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueHovrPrepFail_IEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_HovrPrepFail_IEs
*  DESC: Function to Unpack CztProtIE_Field_HovrPrepFail_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_HovrPrepFail_IEs
(
CztProtIE_Field_HovrPrepFail_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_HovrPrepFail_IEs(param, ptr, mBuf)
CztProtIE_Field_HovrPrepFail_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_HovrPrepFail_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueHovrPrepFail_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_HovrPrepFail_IEs */



/*
* FUN : cmUnpkCztProtIE_Cont_HovrPrepFail_IEs
*  DESC: Function to Unpack CztProtIE_Cont_HovrPrepFail_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Cont_HovrPrepFail_IEs
(
CztProtIE_Cont_HovrPrepFail_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Cont_HovrPrepFail_IEs(param, ptr, mBuf)
CztProtIE_Cont_HovrPrepFail_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtIE_Cont_HovrPrepFail_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Field_HovrPrepFail_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Field_HovrPrepFail_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtIE_Cont_HovrPrepFail_IEs */



/*
* FUN : cmUnpkCztHovrPrepFail
*  DESC: Function to Unpack CztHovrPrepFail structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztHovrPrepFail
(
CztHovrPrepFail *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztHovrPrepFail(param, ptr, mBuf)
CztHovrPrepFail *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztHovrPrepFail) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztProtIE_Cont_HovrPrepFail_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztHovrPrepFail */



/*
* FUN : cmUnpkCzt_ValueHovrReport_IEsCls
*  DESC: Function to Unpack Czt_ValueHovrReport_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueHovrReport_IEsCls
(
Czt_ValueHovrReport_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueHovrReport_IEsCls(param, val, ptr, mBuf)
Czt_ValueHovrReport_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueHovrReport_IEsCls) 
	
	switch (val)
	{
		case Cztid_HovrReportTyp:
			CMCHKUNPK(cmUnpkCztHovrReportTyp, &param->u.cztHovrReportTyp, mBuf); 
			break;
		case Cztid_Cause:
			CMCHKUNPKPTR(cmUnpkCztCause, &param->u.cztCause, ptr, mBuf);
			break;
		case Cztid_SrcCellECGI:
			CMCHKUNPKPTR(cmUnpkCztECGI, &param->u.cztid_SrcCellECGI, ptr, mBuf);
			break;
		case Cztid_FailCellECGI:
			CMCHKUNPKPTR(cmUnpkCztECGI, &param->u.cztid_FailCellECGI, ptr, mBuf);
			break;
		case Cztid_Re_establishmentCellECGI:
			CMCHKUNPKPTR(cmUnpkCztECGI, &param->u.cztid_Re_establishmentCellECGI, ptr, mBuf);
			break;
		case Cztid_TgetCellInUTRAN:
			CZUCHKUNPKPTR(cmUnpkCztTgetCellInUTRAN, &param->u.cztTgetCellInUTRAN, ptr, mBuf); 
			break;
		case Cztid_SrcCellCRNTI:
			CMCHKUNPK(cmUnpkCztCRNTI, &param->u.cztCRNTI, mBuf); 
			break;
		case Cztid_MobilityInform:
			CMCHKUNPK(cmUnpkCztMobilityInform, &param->u.cztMobilityInform, mBuf); 
			break;
		case Cztid_UE_RLF_Report_Cont:
			CZUCHKUNPKPTR(cmUnpkCztUE_RLF_Report_Cont, &param->u.cztUE_RLF_Report_Cont, ptr, mBuf); 
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueHovrReport_IEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_HovrReport_IEs
*  DESC: Function to Unpack CztProtIE_Field_HovrReport_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_HovrReport_IEs
(
CztProtIE_Field_HovrReport_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_HovrReport_IEs(param, ptr, mBuf)
CztProtIE_Field_HovrReport_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_HovrReport_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueHovrReport_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_HovrReport_IEs */



/*
* FUN : cmUnpkCztProtIE_Cont_HovrReport_IEs
*  DESC: Function to Unpack CztProtIE_Cont_HovrReport_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Cont_HovrReport_IEs
(
CztProtIE_Cont_HovrReport_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Cont_HovrReport_IEs(param, ptr, mBuf)
CztProtIE_Cont_HovrReport_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtIE_Cont_HovrReport_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Field_HovrReport_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Field_HovrReport_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtIE_Cont_HovrReport_IEs */



/*
* FUN : cmUnpkCztHovrReport
*  DESC: Function to Unpack CztHovrReport structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztHovrReport
(
CztHovrReport *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztHovrReport(param, ptr, mBuf)
CztHovrReport *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztHovrReport) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztProtIE_Cont_HovrReport_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztHovrReport */



/*
* FUN : cmUnpkCzt_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsCls
*  DESC: Function to Unpack Czt_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsCls
(
Czt_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsCls) 
	
	switch (val)
	{
		case Cztid_ReceiveStatusOfULPDCPSDUsExtended:
			CMCHKUNPKPTR(cmUnpkCztReceiveStatusOfULPDCPSDUsExtended, &param->u.cztReceiveStatusOfULPDCPSDUsExtended, ptr, mBuf); 
			break;
		case Cztid_ULCOUNTValueExtended:
			CMCHKUNPKPTR(cmUnpkCztCOUNTValueExtended, &param->u.cztid_ULCOUNTValueExtended, ptr, mBuf);
			break;
		case Cztid_DLCOUNTValueExtended:
			CMCHKUNPKPTR(cmUnpkCztCOUNTValueExtended, &param->u.cztid_DLCOUNTValueExtended, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEs
*  DESC: Function to Unpack CztProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEs
(
CztProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEs(param, ptr, mBuf)
CztProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnE_RABs_SubjToStatusTfr_ItemExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEs
*  DESC: Function to Unpack CztProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEs
(
CztProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEs(param, ptr, mBuf)
CztProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_E_RABs_SubjToStatusTfr_ItemExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEs */



/*
* FUN : cmUnpkCztE_RABs_SubjToStatusTfr_Item
*  DESC: Function to Unpack CztE_RABs_SubjToStatusTfr_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztE_RABs_SubjToStatusTfr_Item
(
CztE_RABs_SubjToStatusTfr_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztE_RABs_SubjToStatusTfr_Item(param, ptr, mBuf)
CztE_RABs_SubjToStatusTfr_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztE_RABs_SubjToStatusTfr_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztE_RAB_ID, &param->e_RAB_ID, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztReceiveStatusofULPDCPSDUs, &param->receiveStatusofULPDCPSDUs, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztCOUNTvalue, &param->uL_COUNTvalue, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztCOUNTvalue, &param->dL_COUNTvalue, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_E_RABs_SubjToStatusTfr_ItemExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztE_RABs_SubjToStatusTfr_Item */



/*
* FUN : cmUnpkCzt_ValueE_RABs_SubjToStatusTfr_ItemIEsCls
*  DESC: Function to Unpack Czt_ValueE_RABs_SubjToStatusTfr_ItemIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueE_RABs_SubjToStatusTfr_ItemIEsCls
(
Czt_ValueE_RABs_SubjToStatusTfr_ItemIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueE_RABs_SubjToStatusTfr_ItemIEsCls(param, val, ptr, mBuf)
Czt_ValueE_RABs_SubjToStatusTfr_ItemIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueE_RABs_SubjToStatusTfr_ItemIEsCls) 
	
	switch (val)
	{
		case Cztid_E_RABs_SubjToStatusTfr_Item:
			CMCHKUNPKPTR(cmUnpkCztE_RABs_SubjToStatusTfr_Item, &param->u.cztE_RABs_SubjToStatusTfr_Item, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueE_RABs_SubjToStatusTfr_ItemIEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEs
*  DESC: Function to Unpack CztProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEs
(
CztProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEs(param, ptr, mBuf)
CztProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueE_RABs_SubjToStatusTfr_ItemIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEs */

/* Element ------------- ProtocolIE-Single-Container ------------ */
#define cmUnpkCztProtIE_Single_Cont_E_RABs_SubjToStatusTfr_ItemIEs cmUnpkCztProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEs


/*
* FUN : cmUnpkCztE_RABs_SubjToStatusTfr_Lst
*  DESC: Function to Unpack CztE_RABs_SubjToStatusTfr_Lst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztE_RABs_SubjToStatusTfr_Lst
(
CztE_RABs_SubjToStatusTfr_Lst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztE_RABs_SubjToStatusTfr_Lst(param, ptr, mBuf)
CztE_RABs_SubjToStatusTfr_Lst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztE_RABs_SubjToStatusTfr_Lst) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Single_Cont_E_RABs_SubjToStatusTfr_ItemIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Single_Cont_E_RABs_SubjToStatusTfr_ItemIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztE_RABs_SubjToStatusTfr_Lst */



/*
* FUN : cmUnpkCzt_ValueSNStatusTfr_IEsCls
*  DESC: Function to Unpack Czt_ValueSNStatusTfr_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueSNStatusTfr_IEsCls
(
Czt_ValueSNStatusTfr_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueSNStatusTfr_IEsCls(param, val, ptr, mBuf)
Czt_ValueSNStatusTfr_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueSNStatusTfr_IEsCls) 
	
	switch (val)
	{
		case Cztid_Old_eNB_UE_X2AP_ID:
			CMCHKUNPK(cmUnpkCztUE_X2AP_ID, &param->u.cztid_Old_eNB_UE_X2AP_ID, mBuf); 
			break;
		case Cztid_New_eNB_UE_X2AP_ID:
			CMCHKUNPK(cmUnpkCztUE_X2AP_ID, &param->u.cztid_New_eNB_UE_X2AP_ID, mBuf); 
			break;
		case Cztid_E_RABs_SubjToStatusTfr_Lst:
			CMCHKUNPKPTR(cmUnpkCztE_RABs_SubjToStatusTfr_Lst, &param->u.cztE_RABs_SubjToStatusTfr_Lst, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueSNStatusTfr_IEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_SNStatusTfr_IEs
*  DESC: Function to Unpack CztProtIE_Field_SNStatusTfr_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_SNStatusTfr_IEs
(
CztProtIE_Field_SNStatusTfr_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_SNStatusTfr_IEs(param, ptr, mBuf)
CztProtIE_Field_SNStatusTfr_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_SNStatusTfr_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueSNStatusTfr_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_SNStatusTfr_IEs */



/*
* FUN : cmUnpkCztProtIE_Cont_SNStatusTfr_IEs
*  DESC: Function to Unpack CztProtIE_Cont_SNStatusTfr_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Cont_SNStatusTfr_IEs
(
CztProtIE_Cont_SNStatusTfr_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Cont_SNStatusTfr_IEs(param, ptr, mBuf)
CztProtIE_Cont_SNStatusTfr_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtIE_Cont_SNStatusTfr_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Field_SNStatusTfr_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Field_SNStatusTfr_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtIE_Cont_SNStatusTfr_IEs */



/*
* FUN : cmUnpkCztSNStatusTfr
*  DESC: Function to Unpack CztSNStatusTfr structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztSNStatusTfr
(
CztSNStatusTfr *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztSNStatusTfr(param, ptr, mBuf)
CztSNStatusTfr *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztSNStatusTfr) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztProtIE_Cont_SNStatusTfr_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztSNStatusTfr */



/*
* FUN : cmUnpkCzt_ValueUECntxtRls_IEsCls
*  DESC: Function to Unpack Czt_ValueUECntxtRls_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueUECntxtRls_IEsCls
(
Czt_ValueUECntxtRls_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueUECntxtRls_IEsCls(param, val, ptr, mBuf)
Czt_ValueUECntxtRls_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueUECntxtRls_IEsCls) 
	
	switch (val)
	{
		case Cztid_Old_eNB_UE_X2AP_ID:
			CMCHKUNPK(cmUnpkCztUE_X2AP_ID, &param->u.cztid_Old_eNB_UE_X2AP_ID, mBuf); 
			break;
		case Cztid_New_eNB_UE_X2AP_ID:
			CMCHKUNPK(cmUnpkCztUE_X2AP_ID, &param->u.cztid_New_eNB_UE_X2AP_ID, mBuf); 
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueUECntxtRls_IEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_UECntxtRls_IEs
*  DESC: Function to Unpack CztProtIE_Field_UECntxtRls_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_UECntxtRls_IEs
(
CztProtIE_Field_UECntxtRls_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_UECntxtRls_IEs(param, ptr, mBuf)
CztProtIE_Field_UECntxtRls_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_UECntxtRls_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueUECntxtRls_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_UECntxtRls_IEs */



/*
* FUN : cmUnpkCztProtIE_Cont_UECntxtRls_IEs
*  DESC: Function to Unpack CztProtIE_Cont_UECntxtRls_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Cont_UECntxtRls_IEs
(
CztProtIE_Cont_UECntxtRls_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Cont_UECntxtRls_IEs(param, ptr, mBuf)
CztProtIE_Cont_UECntxtRls_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtIE_Cont_UECntxtRls_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Field_UECntxtRls_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Field_UECntxtRls_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtIE_Cont_UECntxtRls_IEs */



/*
* FUN : cmUnpkCztUECntxtRls
*  DESC: Function to Unpack CztUECntxtRls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztUECntxtRls
(
CztUECntxtRls *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztUECntxtRls(param, ptr, mBuf)
CztUECntxtRls *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztUECntxtRls) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztProtIE_Cont_UECntxtRls_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztUECntxtRls */



/*
* FUN : cmUnpkCzt_ValueHovrCancel_IEsCls
*  DESC: Function to Unpack Czt_ValueHovrCancel_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueHovrCancel_IEsCls
(
Czt_ValueHovrCancel_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueHovrCancel_IEsCls(param, val, ptr, mBuf)
Czt_ValueHovrCancel_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueHovrCancel_IEsCls) 
	
	switch (val)
	{
		case Cztid_Old_eNB_UE_X2AP_ID:
			CMCHKUNPK(cmUnpkCztUE_X2AP_ID, &param->u.cztid_Old_eNB_UE_X2AP_ID, mBuf); 
			break;
		case Cztid_New_eNB_UE_X2AP_ID:
			CMCHKUNPK(cmUnpkCztUE_X2AP_ID, &param->u.cztid_New_eNB_UE_X2AP_ID, mBuf); 
			break;
		case Cztid_Cause:
			CMCHKUNPKPTR(cmUnpkCztCause, &param->u.cztCause, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueHovrCancel_IEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_HovrCancel_IEs
*  DESC: Function to Unpack CztProtIE_Field_HovrCancel_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_HovrCancel_IEs
(
CztProtIE_Field_HovrCancel_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_HovrCancel_IEs(param, ptr, mBuf)
CztProtIE_Field_HovrCancel_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_HovrCancel_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueHovrCancel_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_HovrCancel_IEs */



/*
* FUN : cmUnpkCztProtIE_Cont_HovrCancel_IEs
*  DESC: Function to Unpack CztProtIE_Cont_HovrCancel_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Cont_HovrCancel_IEs
(
CztProtIE_Cont_HovrCancel_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Cont_HovrCancel_IEs(param, ptr, mBuf)
CztProtIE_Cont_HovrCancel_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtIE_Cont_HovrCancel_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Field_HovrCancel_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Field_HovrCancel_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtIE_Cont_HovrCancel_IEs */



/*
* FUN : cmUnpkCztHovrCancel
*  DESC: Function to Unpack CztHovrCancel structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztHovrCancel
(
CztHovrCancel *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztHovrCancel(param, ptr, mBuf)
CztHovrCancel *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztHovrCancel) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztProtIE_Cont_HovrCancel_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztHovrCancel */



/*
* FUN : cmUnpkCzt_ValueErrInd_IEsCls
*  DESC: Function to Unpack Czt_ValueErrInd_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueErrInd_IEsCls
(
Czt_ValueErrInd_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueErrInd_IEsCls(param, val, ptr, mBuf)
Czt_ValueErrInd_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueErrInd_IEsCls) 
	
	switch (val)
	{
		case Cztid_Old_eNB_UE_X2AP_ID:
			CMCHKUNPK(cmUnpkCztUE_X2AP_ID, &param->u.cztid_Old_eNB_UE_X2AP_ID, mBuf); 
			break;
		case Cztid_New_eNB_UE_X2AP_ID:
			CMCHKUNPK(cmUnpkCztUE_X2AP_ID, &param->u.cztid_New_eNB_UE_X2AP_ID, mBuf); 
			break;
		case Cztid_Cause:
			CMCHKUNPKPTR(cmUnpkCztCause, &param->u.cztCause, ptr, mBuf);
			break;
		case Cztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkCztCriticalityDiag, &param->u.cztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueErrInd_IEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_ErrInd_IEs
*  DESC: Function to Unpack CztProtIE_Field_ErrInd_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_ErrInd_IEs
(
CztProtIE_Field_ErrInd_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_ErrInd_IEs(param, ptr, mBuf)
CztProtIE_Field_ErrInd_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_ErrInd_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueErrInd_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_ErrInd_IEs */



/*
* FUN : cmUnpkCztProtIE_Cont_ErrInd_IEs
*  DESC: Function to Unpack CztProtIE_Cont_ErrInd_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Cont_ErrInd_IEs
(
CztProtIE_Cont_ErrInd_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Cont_ErrInd_IEs(param, ptr, mBuf)
CztProtIE_Cont_ErrInd_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtIE_Cont_ErrInd_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Field_ErrInd_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Field_ErrInd_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtIE_Cont_ErrInd_IEs */



/*
* FUN : cmUnpkCztErrInd
*  DESC: Function to Unpack CztErrInd structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztErrInd
(
CztErrInd *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztErrInd(param, ptr, mBuf)
CztErrInd *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztErrInd) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztProtIE_Cont_ErrInd_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztErrInd */



/*
* FUN : cmUnpkCzt_ValueResetRqst_IEsCls
*  DESC: Function to Unpack Czt_ValueResetRqst_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueResetRqst_IEsCls
(
Czt_ValueResetRqst_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueResetRqst_IEsCls(param, val, ptr, mBuf)
Czt_ValueResetRqst_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueResetRqst_IEsCls) 
	
	switch (val)
	{
		case Cztid_Cause:
			CMCHKUNPKPTR(cmUnpkCztCause, &param->u.cztCause, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueResetRqst_IEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_ResetRqst_IEs
*  DESC: Function to Unpack CztProtIE_Field_ResetRqst_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_ResetRqst_IEs
(
CztProtIE_Field_ResetRqst_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_ResetRqst_IEs(param, ptr, mBuf)
CztProtIE_Field_ResetRqst_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_ResetRqst_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueResetRqst_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_ResetRqst_IEs */



/*
* FUN : cmUnpkCztProtIE_Cont_ResetRqst_IEs
*  DESC: Function to Unpack CztProtIE_Cont_ResetRqst_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Cont_ResetRqst_IEs
(
CztProtIE_Cont_ResetRqst_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Cont_ResetRqst_IEs(param, ptr, mBuf)
CztProtIE_Cont_ResetRqst_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtIE_Cont_ResetRqst_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Field_ResetRqst_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Field_ResetRqst_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtIE_Cont_ResetRqst_IEs */



/*
* FUN : cmUnpkCztResetRqst
*  DESC: Function to Unpack CztResetRqst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztResetRqst
(
CztResetRqst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztResetRqst(param, ptr, mBuf)
CztResetRqst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztResetRqst) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztProtIE_Cont_ResetRqst_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztResetRqst */



/*
* FUN : cmUnpkCzt_ValueResetResp_IEsCls
*  DESC: Function to Unpack Czt_ValueResetResp_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueResetResp_IEsCls
(
Czt_ValueResetResp_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueResetResp_IEsCls(param, val, ptr, mBuf)
Czt_ValueResetResp_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueResetResp_IEsCls) 
	
	switch (val)
	{
		case Cztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkCztCriticalityDiag, &param->u.cztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueResetResp_IEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_ResetResp_IEs
*  DESC: Function to Unpack CztProtIE_Field_ResetResp_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_ResetResp_IEs
(
CztProtIE_Field_ResetResp_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_ResetResp_IEs(param, ptr, mBuf)
CztProtIE_Field_ResetResp_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_ResetResp_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueResetResp_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_ResetResp_IEs */



/*
* FUN : cmUnpkCztProtIE_Cont_ResetResp_IEs
*  DESC: Function to Unpack CztProtIE_Cont_ResetResp_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Cont_ResetResp_IEs
(
CztProtIE_Cont_ResetResp_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Cont_ResetResp_IEs(param, ptr, mBuf)
CztProtIE_Cont_ResetResp_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtIE_Cont_ResetResp_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Field_ResetResp_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Field_ResetResp_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtIE_Cont_ResetResp_IEs */



/*
* FUN : cmUnpkCztResetResp
*  DESC: Function to Unpack CztResetResp structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztResetResp
(
CztResetResp *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztResetResp(param, ptr, mBuf)
CztResetResp *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztResetResp) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztProtIE_Cont_ResetResp_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztResetResp */



/*
* FUN : cmUnpkCzt_ValueX2SetupRqst_IEsCls
*  DESC: Function to Unpack Czt_ValueX2SetupRqst_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueX2SetupRqst_IEsCls
(
Czt_ValueX2SetupRqst_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueX2SetupRqst_IEsCls(param, val, ptr, mBuf)
Czt_ValueX2SetupRqst_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueX2SetupRqst_IEsCls) 
	
	switch (val)
	{
		case Cztid_GlobalENB_ID:
			CMCHKUNPKPTR(cmUnpkCztGlobalENB_ID, &param->u.cztGlobalENB_ID, ptr, mBuf);
			break;
		case Cztid_SrvdCells:
			CMCHKUNPKPTR(cmUnpkCztSrvdCells, &param->u.cztSrvdCells, ptr, mBuf);
			break;
		case Cztid_GUGroupIDLst:
			CMCHKUNPKPTR(cmUnpkCztGUGroupIDLst, &param->u.cztGUGroupIDLst, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueX2SetupRqst_IEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_X2SetupRqst_IEs
*  DESC: Function to Unpack CztProtIE_Field_X2SetupRqst_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_X2SetupRqst_IEs
(
CztProtIE_Field_X2SetupRqst_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_X2SetupRqst_IEs(param, ptr, mBuf)
CztProtIE_Field_X2SetupRqst_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_X2SetupRqst_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueX2SetupRqst_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_X2SetupRqst_IEs */



/*
* FUN : cmUnpkCztProtIE_Cont_X2SetupRqst_IEs
*  DESC: Function to Unpack CztProtIE_Cont_X2SetupRqst_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Cont_X2SetupRqst_IEs
(
CztProtIE_Cont_X2SetupRqst_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Cont_X2SetupRqst_IEs(param, ptr, mBuf)
CztProtIE_Cont_X2SetupRqst_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtIE_Cont_X2SetupRqst_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Field_X2SetupRqst_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Field_X2SetupRqst_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtIE_Cont_X2SetupRqst_IEs */



/*
* FUN : cmUnpkCztX2SetupRqst
*  DESC: Function to Unpack CztX2SetupRqst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztX2SetupRqst
(
CztX2SetupRqst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztX2SetupRqst(param, ptr, mBuf)
CztX2SetupRqst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztX2SetupRqst) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztProtIE_Cont_X2SetupRqst_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztX2SetupRqst */



/*
* FUN : cmUnpkCzt_ValueX2SetupResp_IEsCls
*  DESC: Function to Unpack Czt_ValueX2SetupResp_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueX2SetupResp_IEsCls
(
Czt_ValueX2SetupResp_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueX2SetupResp_IEsCls(param, val, ptr, mBuf)
Czt_ValueX2SetupResp_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueX2SetupResp_IEsCls) 
	
	switch (val)
	{
		case Cztid_GlobalENB_ID:
			CMCHKUNPKPTR(cmUnpkCztGlobalENB_ID, &param->u.cztGlobalENB_ID, ptr, mBuf);
			break;
		case Cztid_SrvdCells:
			CMCHKUNPKPTR(cmUnpkCztSrvdCells, &param->u.cztSrvdCells, ptr, mBuf);
			break;
		case Cztid_GUGroupIDLst:
			CMCHKUNPKPTR(cmUnpkCztGUGroupIDLst, &param->u.cztGUGroupIDLst, ptr, mBuf);
			break;
		case Cztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkCztCriticalityDiag, &param->u.cztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueX2SetupResp_IEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_X2SetupResp_IEs
*  DESC: Function to Unpack CztProtIE_Field_X2SetupResp_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_X2SetupResp_IEs
(
CztProtIE_Field_X2SetupResp_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_X2SetupResp_IEs(param, ptr, mBuf)
CztProtIE_Field_X2SetupResp_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_X2SetupResp_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueX2SetupResp_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_X2SetupResp_IEs */



/*
* FUN : cmUnpkCztProtIE_Cont_X2SetupResp_IEs
*  DESC: Function to Unpack CztProtIE_Cont_X2SetupResp_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Cont_X2SetupResp_IEs
(
CztProtIE_Cont_X2SetupResp_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Cont_X2SetupResp_IEs(param, ptr, mBuf)
CztProtIE_Cont_X2SetupResp_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtIE_Cont_X2SetupResp_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Field_X2SetupResp_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Field_X2SetupResp_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtIE_Cont_X2SetupResp_IEs */



/*
* FUN : cmUnpkCztX2SetupResp
*  DESC: Function to Unpack CztX2SetupResp structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztX2SetupResp
(
CztX2SetupResp *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztX2SetupResp(param, ptr, mBuf)
CztX2SetupResp *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztX2SetupResp) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztProtIE_Cont_X2SetupResp_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztX2SetupResp */



/*
* FUN : cmUnpkCzt_ValueX2SetupFail_IEsCls
*  DESC: Function to Unpack Czt_ValueX2SetupFail_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueX2SetupFail_IEsCls
(
Czt_ValueX2SetupFail_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueX2SetupFail_IEsCls(param, val, ptr, mBuf)
Czt_ValueX2SetupFail_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueX2SetupFail_IEsCls) 
	
	switch (val)
	{
		case Cztid_Cause:
			CMCHKUNPKPTR(cmUnpkCztCause, &param->u.cztCause, ptr, mBuf);
			break;
		case Cztid_TimeToWait:
			CMCHKUNPK(cmUnpkCztTimeToWait, &param->u.cztTimeToWait, mBuf); 
			break;
		case Cztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkCztCriticalityDiag, &param->u.cztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueX2SetupFail_IEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_X2SetupFail_IEs
*  DESC: Function to Unpack CztProtIE_Field_X2SetupFail_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_X2SetupFail_IEs
(
CztProtIE_Field_X2SetupFail_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_X2SetupFail_IEs(param, ptr, mBuf)
CztProtIE_Field_X2SetupFail_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_X2SetupFail_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueX2SetupFail_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_X2SetupFail_IEs */



/*
* FUN : cmUnpkCztProtIE_Cont_X2SetupFail_IEs
*  DESC: Function to Unpack CztProtIE_Cont_X2SetupFail_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Cont_X2SetupFail_IEs
(
CztProtIE_Cont_X2SetupFail_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Cont_X2SetupFail_IEs(param, ptr, mBuf)
CztProtIE_Cont_X2SetupFail_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtIE_Cont_X2SetupFail_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Field_X2SetupFail_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Field_X2SetupFail_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtIE_Cont_X2SetupFail_IEs */



/*
* FUN : cmUnpkCztX2SetupFail
*  DESC: Function to Unpack CztX2SetupFail structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztX2SetupFail
(
CztX2SetupFail *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztX2SetupFail(param, ptr, mBuf)
CztX2SetupFail *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztX2SetupFail) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztProtIE_Cont_X2SetupFail_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztX2SetupFail */



/*
* FUN : cmUnpkCzt_ExtnCellInform_Item_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnCellInform_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnCellInform_Item_ExtIEsCls
(
Czt_ExtnCellInform_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnCellInform_Item_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnCellInform_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnCellInform_Item_ExtIEsCls) 
	
	switch (val)
	{
		case Cztid_ABSInform:
			CMCHKUNPKPTR(cmUnpkCztABSInform, &param->u.cztABSInform, ptr, mBuf);
			break;
		case Cztid_InvokeInd:
			CMCHKUNPK(cmUnpkCztInvokeInd, &param->u.cztInvokeInd, mBuf); 
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ExtnCellInform_Item_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_CellInform_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_CellInform_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_CellInform_Item_ExtIEs
(
CztProtExtnField_CellInform_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_CellInform_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnField_CellInform_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_CellInform_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnCellInform_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_CellInform_Item_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_CellInform_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_CellInform_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_CellInform_Item_ExtIEs
(
CztProtExtnCont_CellInform_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_CellInform_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_CellInform_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_CellInform_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_CellInform_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_CellInform_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_CellInform_Item_ExtIEs */



/*
* FUN : cmUnpkCztCellInform_Item
*  DESC: Function to Unpack CztCellInform_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztCellInform_Item
(
CztCellInform_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztCellInform_Item(param, ptr, mBuf)
CztCellInform_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztCellInform_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztECGI, &param->cell_ID, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztUL_InterferenceOverloadInd, &param->ul_InterferenceOverloadInd, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztUL_HighInterferenceIndInfo, &param->ul_HighInterferenceIndInfo, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztRelativeNarrowbandTxPower, &param->relativeNarrowbandTxPower, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_CellInform_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztCellInform_Item */



/*
* FUN : cmUnpkCzt_ValueCellInform_ItemIEsCls
*  DESC: Function to Unpack Czt_ValueCellInform_ItemIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueCellInform_ItemIEsCls
(
Czt_ValueCellInform_ItemIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueCellInform_ItemIEsCls(param, val, ptr, mBuf)
Czt_ValueCellInform_ItemIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueCellInform_ItemIEsCls) 
	
	switch (val)
	{
		case Cztid_CellInform_Item:
			CMCHKUNPKPTR(cmUnpkCztCellInform_Item, &param->u.cztCellInform_Item, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueCellInform_ItemIEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_CellInform_ItemIEs
*  DESC: Function to Unpack CztProtIE_Field_CellInform_ItemIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_CellInform_ItemIEs
(
CztProtIE_Field_CellInform_ItemIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_CellInform_ItemIEs(param, ptr, mBuf)
CztProtIE_Field_CellInform_ItemIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_CellInform_ItemIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueCellInform_ItemIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_CellInform_ItemIEs */

/* Element ------------- ProtocolIE-Single-Container ------------ */
#define cmUnpkCztProtIE_Single_Cont_CellInform_ItemIEs cmUnpkCztProtIE_Field_CellInform_ItemIEs


/*
* FUN : cmUnpkCztCellInform_Lst
*  DESC: Function to Unpack CztCellInform_Lst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztCellInform_Lst
(
CztCellInform_Lst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztCellInform_Lst(param, ptr, mBuf)
CztCellInform_Lst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztCellInform_Lst) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Single_Cont_CellInform_ItemIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Single_Cont_CellInform_ItemIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztCellInform_Lst */



/*
* FUN : cmUnpkCzt_ValueLoadInform_IEsCls
*  DESC: Function to Unpack Czt_ValueLoadInform_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueLoadInform_IEsCls
(
Czt_ValueLoadInform_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueLoadInform_IEsCls(param, val, ptr, mBuf)
Czt_ValueLoadInform_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueLoadInform_IEsCls) 
	
	switch (val)
	{
		case Cztid_CellInform:
			CMCHKUNPKPTR(cmUnpkCztCellInform_Lst, &param->u.cztCellInform_Lst, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueLoadInform_IEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_LoadInform_IEs
*  DESC: Function to Unpack CztProtIE_Field_LoadInform_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_LoadInform_IEs
(
CztProtIE_Field_LoadInform_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_LoadInform_IEs(param, ptr, mBuf)
CztProtIE_Field_LoadInform_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_LoadInform_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueLoadInform_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_LoadInform_IEs */



/*
* FUN : cmUnpkCztProtIE_Cont_LoadInform_IEs
*  DESC: Function to Unpack CztProtIE_Cont_LoadInform_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Cont_LoadInform_IEs
(
CztProtIE_Cont_LoadInform_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Cont_LoadInform_IEs(param, ptr, mBuf)
CztProtIE_Cont_LoadInform_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtIE_Cont_LoadInform_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Field_LoadInform_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Field_LoadInform_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtIE_Cont_LoadInform_IEs */



/*
* FUN : cmUnpkCztLoadInform
*  DESC: Function to Unpack CztLoadInform structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztLoadInform
(
CztLoadInform *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztLoadInform(param, ptr, mBuf)
CztLoadInform *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztLoadInform) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztProtIE_Cont_LoadInform_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztLoadInform */



/*
* FUN : cmUnpkCzt_ExtnSrvdCellsToMdfy_Item_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnSrvdCellsToMdfy_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnSrvdCellsToMdfy_Item_ExtIEsCls
(
Czt_ExtnSrvdCellsToMdfy_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnSrvdCellsToMdfy_Item_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnSrvdCellsToMdfy_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnSrvdCellsToMdfy_Item_ExtIEsCls) 
	
	switch (val)
	{
		case Cztid_DeactivationInd:
			CMCHKUNPK(cmUnpkCztDeactivationInd, &param->u.cztDeactivationInd, mBuf); 
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ExtnSrvdCellsToMdfy_Item_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_SrvdCellsToMdfy_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_SrvdCellsToMdfy_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_SrvdCellsToMdfy_Item_ExtIEs
(
CztProtExtnField_SrvdCellsToMdfy_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_SrvdCellsToMdfy_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnField_SrvdCellsToMdfy_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_SrvdCellsToMdfy_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnSrvdCellsToMdfy_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_SrvdCellsToMdfy_Item_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_SrvdCellsToMdfy_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_SrvdCellsToMdfy_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_SrvdCellsToMdfy_Item_ExtIEs
(
CztProtExtnCont_SrvdCellsToMdfy_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_SrvdCellsToMdfy_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_SrvdCellsToMdfy_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_SrvdCellsToMdfy_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_SrvdCellsToMdfy_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_SrvdCellsToMdfy_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_SrvdCellsToMdfy_Item_ExtIEs */



/*
* FUN : cmUnpkCztSrvdCellsToMdfy_Item
*  DESC: Function to Unpack CztSrvdCellsToMdfy_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztSrvdCellsToMdfy_Item
(
CztSrvdCellsToMdfy_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztSrvdCellsToMdfy_Item(param, ptr, mBuf)
CztSrvdCellsToMdfy_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztSrvdCellsToMdfy_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztECGI, &param->old_ecgi, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztSrvdCell_Inform, &param->servedCellInfo, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztNeighbour_Inform, &param->neighbour_Info, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_SrvdCellsToMdfy_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztSrvdCellsToMdfy_Item */



/*
* FUN : cmUnpkCztSrvdCellsToMdfy
*  DESC: Function to Unpack CztSrvdCellsToMdfy structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztSrvdCellsToMdfy
(
CztSrvdCellsToMdfy *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztSrvdCellsToMdfy(param, ptr, mBuf)
CztSrvdCellsToMdfy *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztSrvdCellsToMdfy) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztSrvdCellsToMdfy_Item)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztSrvdCellsToMdfy_Item, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztSrvdCellsToMdfy */



/*
* FUN : cmUnpkCztOld_ECGIs
*  DESC: Function to Unpack CztOld_ECGIs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztOld_ECGIs
(
CztOld_ECGIs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztOld_ECGIs(param, ptr, mBuf)
CztOld_ECGIs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztOld_ECGIs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztECGI)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztECGI, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztOld_ECGIs */



/*
* FUN : cmUnpkCzt_ValueENBConfigUpd_IEsCls
*  DESC: Function to Unpack Czt_ValueENBConfigUpd_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueENBConfigUpd_IEsCls
(
Czt_ValueENBConfigUpd_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueENBConfigUpd_IEsCls(param, val, ptr, mBuf)
Czt_ValueENBConfigUpd_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueENBConfigUpd_IEsCls) 
	
	switch (val)
	{
		case Cztid_SrvdCellsToAdd:
			CMCHKUNPKPTR(cmUnpkCztSrvdCells, &param->u.cztSrvdCells, ptr, mBuf);
			break;
		case Cztid_SrvdCellsToMdfy:
			CMCHKUNPKPTR(cmUnpkCztSrvdCellsToMdfy, &param->u.cztSrvdCellsToMdfy, ptr, mBuf);
			break;
		case Cztid_SrvdCellsToDelete:
			CMCHKUNPKPTR(cmUnpkCztOld_ECGIs, &param->u.cztOld_ECGIs, ptr, mBuf);
			break;
		case Cztid_GUGroupIDToAddLst:
			CMCHKUNPKPTR(cmUnpkCztGUGroupIDLst, &param->u.cztid_GUGroupIDToAddLst, ptr, mBuf);
			break;
		case Cztid_GUGroupIDToDeleteLst:
			CMCHKUNPKPTR(cmUnpkCztGUGroupIDLst, &param->u.cztid_GUGroupIDToDeleteLst, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueENBConfigUpd_IEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_ENBConfigUpd_IEs
*  DESC: Function to Unpack CztProtIE_Field_ENBConfigUpd_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_ENBConfigUpd_IEs
(
CztProtIE_Field_ENBConfigUpd_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_ENBConfigUpd_IEs(param, ptr, mBuf)
CztProtIE_Field_ENBConfigUpd_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_ENBConfigUpd_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueENBConfigUpd_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_ENBConfigUpd_IEs */



/*
* FUN : cmUnpkCztProtIE_Cont_ENBConfigUpd_IEs
*  DESC: Function to Unpack CztProtIE_Cont_ENBConfigUpd_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Cont_ENBConfigUpd_IEs
(
CztProtIE_Cont_ENBConfigUpd_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Cont_ENBConfigUpd_IEs(param, ptr, mBuf)
CztProtIE_Cont_ENBConfigUpd_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtIE_Cont_ENBConfigUpd_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Field_ENBConfigUpd_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Field_ENBConfigUpd_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtIE_Cont_ENBConfigUpd_IEs */



/*
* FUN : cmUnpkCztENBConfigUpd
*  DESC: Function to Unpack CztENBConfigUpd structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztENBConfigUpd
(
CztENBConfigUpd *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztENBConfigUpd(param, ptr, mBuf)
CztENBConfigUpd *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztENBConfigUpd) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztProtIE_Cont_ENBConfigUpd_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztENBConfigUpd */



/*
* FUN : cmUnpkCzt_ValueENBConfigUpdAckg_IEsCls
*  DESC: Function to Unpack Czt_ValueENBConfigUpdAckg_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueENBConfigUpdAckg_IEsCls
(
Czt_ValueENBConfigUpdAckg_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueENBConfigUpdAckg_IEsCls(param, val, ptr, mBuf)
Czt_ValueENBConfigUpdAckg_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueENBConfigUpdAckg_IEsCls) 
	
	switch (val)
	{
		case Cztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkCztCriticalityDiag, &param->u.cztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueENBConfigUpdAckg_IEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_ENBConfigUpdAckg_IEs
*  DESC: Function to Unpack CztProtIE_Field_ENBConfigUpdAckg_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_ENBConfigUpdAckg_IEs
(
CztProtIE_Field_ENBConfigUpdAckg_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_ENBConfigUpdAckg_IEs(param, ptr, mBuf)
CztProtIE_Field_ENBConfigUpdAckg_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_ENBConfigUpdAckg_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueENBConfigUpdAckg_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_ENBConfigUpdAckg_IEs */



/*
* FUN : cmUnpkCztProtIE_Cont_ENBConfigUpdAckg_IEs
*  DESC: Function to Unpack CztProtIE_Cont_ENBConfigUpdAckg_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Cont_ENBConfigUpdAckg_IEs
(
CztProtIE_Cont_ENBConfigUpdAckg_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Cont_ENBConfigUpdAckg_IEs(param, ptr, mBuf)
CztProtIE_Cont_ENBConfigUpdAckg_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtIE_Cont_ENBConfigUpdAckg_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Field_ENBConfigUpdAckg_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Field_ENBConfigUpdAckg_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtIE_Cont_ENBConfigUpdAckg_IEs */



/*
* FUN : cmUnpkCztENBConfigUpdAckg
*  DESC: Function to Unpack CztENBConfigUpdAckg structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztENBConfigUpdAckg
(
CztENBConfigUpdAckg *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztENBConfigUpdAckg(param, ptr, mBuf)
CztENBConfigUpdAckg *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztENBConfigUpdAckg) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztProtIE_Cont_ENBConfigUpdAckg_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztENBConfigUpdAckg */



/*
* FUN : cmUnpkCzt_ValueENBConfigUpdFail_IEsCls
*  DESC: Function to Unpack Czt_ValueENBConfigUpdFail_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueENBConfigUpdFail_IEsCls
(
Czt_ValueENBConfigUpdFail_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueENBConfigUpdFail_IEsCls(param, val, ptr, mBuf)
Czt_ValueENBConfigUpdFail_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueENBConfigUpdFail_IEsCls) 
	
	switch (val)
	{
		case Cztid_Cause:
			CMCHKUNPKPTR(cmUnpkCztCause, &param->u.cztCause, ptr, mBuf);
			break;
		case Cztid_TimeToWait:
			CMCHKUNPK(cmUnpkCztTimeToWait, &param->u.cztTimeToWait, mBuf); 
			break;
		case Cztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkCztCriticalityDiag, &param->u.cztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueENBConfigUpdFail_IEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_ENBConfigUpdFail_IEs
*  DESC: Function to Unpack CztProtIE_Field_ENBConfigUpdFail_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_ENBConfigUpdFail_IEs
(
CztProtIE_Field_ENBConfigUpdFail_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_ENBConfigUpdFail_IEs(param, ptr, mBuf)
CztProtIE_Field_ENBConfigUpdFail_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_ENBConfigUpdFail_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueENBConfigUpdFail_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_ENBConfigUpdFail_IEs */



/*
* FUN : cmUnpkCztProtIE_Cont_ENBConfigUpdFail_IEs
*  DESC: Function to Unpack CztProtIE_Cont_ENBConfigUpdFail_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Cont_ENBConfigUpdFail_IEs
(
CztProtIE_Cont_ENBConfigUpdFail_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Cont_ENBConfigUpdFail_IEs(param, ptr, mBuf)
CztProtIE_Cont_ENBConfigUpdFail_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtIE_Cont_ENBConfigUpdFail_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Field_ENBConfigUpdFail_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Field_ENBConfigUpdFail_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtIE_Cont_ENBConfigUpdFail_IEs */



/*
* FUN : cmUnpkCztENBConfigUpdFail
*  DESC: Function to Unpack CztENBConfigUpdFail structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztENBConfigUpdFail
(
CztENBConfigUpdFail *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztENBConfigUpdFail(param, ptr, mBuf)
CztENBConfigUpdFail *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztENBConfigUpdFail) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztProtIE_Cont_ENBConfigUpdFail_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztENBConfigUpdFail */



/*
* FUN : cmUnpkCzt_ExtnCellToReport_Item_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnCellToReport_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnCellToReport_Item_ExtIEsCls
(
Czt_ExtnCellToReport_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnCellToReport_Item_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnCellToReport_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnCellToReport_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnCellToReport_Item_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_CellToReport_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_CellToReport_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_CellToReport_Item_ExtIEs
(
CztProtExtnField_CellToReport_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_CellToReport_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnField_CellToReport_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_CellToReport_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnCellToReport_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_CellToReport_Item_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_CellToReport_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_CellToReport_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_CellToReport_Item_ExtIEs
(
CztProtExtnCont_CellToReport_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_CellToReport_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_CellToReport_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_CellToReport_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_CellToReport_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_CellToReport_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_CellToReport_Item_ExtIEs */



/*
* FUN : cmUnpkCztCellToReport_Item
*  DESC: Function to Unpack CztCellToReport_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztCellToReport_Item
(
CztCellToReport_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztCellToReport_Item(param, ptr, mBuf)
CztCellToReport_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztCellToReport_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztECGI, &param->cell_ID, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_CellToReport_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztCellToReport_Item */



/*
* FUN : cmUnpkCzt_ValueCellToReport_ItemIEsCls
*  DESC: Function to Unpack Czt_ValueCellToReport_ItemIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueCellToReport_ItemIEsCls
(
Czt_ValueCellToReport_ItemIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueCellToReport_ItemIEsCls(param, val, ptr, mBuf)
Czt_ValueCellToReport_ItemIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueCellToReport_ItemIEsCls) 
	
	switch (val)
	{
		case Cztid_CellToReport_Item:
			CMCHKUNPKPTR(cmUnpkCztCellToReport_Item, &param->u.cztCellToReport_Item, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueCellToReport_ItemIEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_CellToReport_ItemIEs
*  DESC: Function to Unpack CztProtIE_Field_CellToReport_ItemIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_CellToReport_ItemIEs
(
CztProtIE_Field_CellToReport_ItemIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_CellToReport_ItemIEs(param, ptr, mBuf)
CztProtIE_Field_CellToReport_ItemIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_CellToReport_ItemIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueCellToReport_ItemIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_CellToReport_ItemIEs */

/* Element ------------- ProtocolIE-Single-Container ------------ */
#define cmUnpkCztProtIE_Single_Cont_CellToReport_ItemIEs cmUnpkCztProtIE_Field_CellToReport_ItemIEs


/*
* FUN : cmUnpkCztCellToReport_Lst
*  DESC: Function to Unpack CztCellToReport_Lst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztCellToReport_Lst
(
CztCellToReport_Lst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztCellToReport_Lst(param, ptr, mBuf)
CztCellToReport_Lst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztCellToReport_Lst) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Single_Cont_CellToReport_ItemIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Single_Cont_CellToReport_ItemIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztCellToReport_Lst */

#define cmUnpkCztRprtngPeriodicity cmUnpkTknU32

#define cmUnpkCztPartialSuccessIndicator cmUnpkTknU32



/*
* FUN : cmUnpkCzt_ValueResStatusRqst_IEsCls
*  DESC: Function to Unpack Czt_ValueResStatusRqst_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueResStatusRqst_IEsCls
(
Czt_ValueResStatusRqst_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueResStatusRqst_IEsCls(param, val, ptr, mBuf)
Czt_ValueResStatusRqst_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueResStatusRqst_IEsCls) 
	
	switch (val)
	{
		case Cztid_ENB1_Measurement_ID:
			CMCHKUNPK(cmUnpkCztMeasurement_ID, &param->u.cztid_ENB1_Measurement_ID, mBuf); 
			break;
		case Cztid_ENB2_Measurement_ID:
			CMCHKUNPK(cmUnpkCztMeasurement_ID, &param->u.cztid_ENB2_Measurement_ID, mBuf); 
			break;
		case Cztid_Registration_Rqst:
			CMCHKUNPK(cmUnpkCztRegistration_Rqst, &param->u.cztRegistration_Rqst, mBuf); 
			break;
		case Cztid_ReportCharacteristics:
			CMCHKUNPK(cmUnpkCztReportCharacteristics, &param->u.cztReportCharacteristics, mBuf); 
			break;
		case Cztid_CellToReport:
			CMCHKUNPKPTR(cmUnpkCztCellToReport_Lst, &param->u.cztCellToReport_Lst, ptr, mBuf);
			break;
		case Cztid_RprtngPeriodicity:
			CMCHKUNPK(cmUnpkCztRprtngPeriodicity, &param->u.cztRprtngPeriodicity, mBuf); 
			break;
		case Cztid_PartialSuccessIndicator:
			CMCHKUNPK(cmUnpkCztPartialSuccessIndicator, &param->u.cztPartialSuccessIndicator, mBuf); 
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueResStatusRqst_IEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_ResStatusRqst_IEs
*  DESC: Function to Unpack CztProtIE_Field_ResStatusRqst_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_ResStatusRqst_IEs
(
CztProtIE_Field_ResStatusRqst_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_ResStatusRqst_IEs(param, ptr, mBuf)
CztProtIE_Field_ResStatusRqst_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_ResStatusRqst_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueResStatusRqst_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_ResStatusRqst_IEs */



/*
* FUN : cmUnpkCztProtIE_Cont_ResStatusRqst_IEs
*  DESC: Function to Unpack CztProtIE_Cont_ResStatusRqst_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Cont_ResStatusRqst_IEs
(
CztProtIE_Cont_ResStatusRqst_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Cont_ResStatusRqst_IEs(param, ptr, mBuf)
CztProtIE_Cont_ResStatusRqst_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtIE_Cont_ResStatusRqst_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Field_ResStatusRqst_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Field_ResStatusRqst_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtIE_Cont_ResStatusRqst_IEs */



/*
* FUN : cmUnpkCztResStatusRqst
*  DESC: Function to Unpack CztResStatusRqst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztResStatusRqst
(
CztResStatusRqst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztResStatusRqst(param, ptr, mBuf)
CztResStatusRqst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztResStatusRqst) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztProtIE_Cont_ResStatusRqst_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztResStatusRqst */



/*
* FUN : cmUnpkCzt_ExtnMeasurementFailCause_Item_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnMeasurementFailCause_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnMeasurementFailCause_Item_ExtIEsCls
(
Czt_ExtnMeasurementFailCause_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnMeasurementFailCause_Item_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnMeasurementFailCause_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnMeasurementFailCause_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnMeasurementFailCause_Item_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_MeasurementFailCause_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_MeasurementFailCause_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_MeasurementFailCause_Item_ExtIEs
(
CztProtExtnField_MeasurementFailCause_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_MeasurementFailCause_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnField_MeasurementFailCause_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_MeasurementFailCause_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnMeasurementFailCause_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_MeasurementFailCause_Item_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_MeasurementFailCause_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_MeasurementFailCause_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_MeasurementFailCause_Item_ExtIEs
(
CztProtExtnCont_MeasurementFailCause_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_MeasurementFailCause_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_MeasurementFailCause_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_MeasurementFailCause_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_MeasurementFailCause_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_MeasurementFailCause_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_MeasurementFailCause_Item_ExtIEs */



/*
* FUN : cmUnpkCztMeasurementFailCause_Item
*  DESC: Function to Unpack CztMeasurementFailCause_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztMeasurementFailCause_Item
(
CztMeasurementFailCause_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztMeasurementFailCause_Item(param, ptr, mBuf)
CztMeasurementFailCause_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztMeasurementFailCause_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztReportCharacteristics, &param->measurementFailedReportCharacteristics, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztCause, &param->cause, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_MeasurementFailCause_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztMeasurementFailCause_Item */



/*
* FUN : cmUnpkCzt_ValueMeasurementFailCause_ItemIEsCls
*  DESC: Function to Unpack Czt_ValueMeasurementFailCause_ItemIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueMeasurementFailCause_ItemIEsCls
(
Czt_ValueMeasurementFailCause_ItemIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueMeasurementFailCause_ItemIEsCls(param, val, ptr, mBuf)
Czt_ValueMeasurementFailCause_ItemIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueMeasurementFailCause_ItemIEsCls) 
	
	switch (val)
	{
		case Cztid_MeasurementFailCause_Item:
			CMCHKUNPKPTR(cmUnpkCztMeasurementFailCause_Item, &param->u.cztMeasurementFailCause_Item, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueMeasurementFailCause_ItemIEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_MeasurementFailCause_ItemIEs
*  DESC: Function to Unpack CztProtIE_Field_MeasurementFailCause_ItemIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_MeasurementFailCause_ItemIEs
(
CztProtIE_Field_MeasurementFailCause_ItemIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_MeasurementFailCause_ItemIEs(param, ptr, mBuf)
CztProtIE_Field_MeasurementFailCause_ItemIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_MeasurementFailCause_ItemIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueMeasurementFailCause_ItemIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_MeasurementFailCause_ItemIEs */

/* Element ------------- ProtocolIE-Single-Container ------------ */
#define cmUnpkCztProtIE_Single_Cont_MeasurementFailCause_ItemIEs cmUnpkCztProtIE_Field_MeasurementFailCause_ItemIEs


/*
* FUN : cmUnpkCztMeasurementFailCause_Lst
*  DESC: Function to Unpack CztMeasurementFailCause_Lst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztMeasurementFailCause_Lst
(
CztMeasurementFailCause_Lst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztMeasurementFailCause_Lst(param, ptr, mBuf)
CztMeasurementFailCause_Lst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztMeasurementFailCause_Lst) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Single_Cont_MeasurementFailCause_ItemIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Single_Cont_MeasurementFailCause_ItemIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztMeasurementFailCause_Lst */



/*
* FUN : cmUnpkCzt_ExtnMeasurementInitiationResult_Item_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnMeasurementInitiationResult_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnMeasurementInitiationResult_Item_ExtIEsCls
(
Czt_ExtnMeasurementInitiationResult_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnMeasurementInitiationResult_Item_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnMeasurementInitiationResult_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnMeasurementInitiationResult_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnMeasurementInitiationResult_Item_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_MeasurementInitiationResult_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_MeasurementInitiationResult_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_MeasurementInitiationResult_Item_ExtIEs
(
CztProtExtnField_MeasurementInitiationResult_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_MeasurementInitiationResult_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnField_MeasurementInitiationResult_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_MeasurementInitiationResult_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnMeasurementInitiationResult_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_MeasurementInitiationResult_Item_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_MeasurementInitiationResult_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_MeasurementInitiationResult_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_MeasurementInitiationResult_Item_ExtIEs
(
CztProtExtnCont_MeasurementInitiationResult_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_MeasurementInitiationResult_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_MeasurementInitiationResult_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_MeasurementInitiationResult_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_MeasurementInitiationResult_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_MeasurementInitiationResult_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_MeasurementInitiationResult_Item_ExtIEs */



/*
* FUN : cmUnpkCztMeasurementInitiationResult_Item
*  DESC: Function to Unpack CztMeasurementInitiationResult_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztMeasurementInitiationResult_Item
(
CztMeasurementInitiationResult_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztMeasurementInitiationResult_Item(param, ptr, mBuf)
CztMeasurementInitiationResult_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztMeasurementInitiationResult_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztECGI, &param->cell_ID, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztMeasurementFailCause_Lst, &param->measurementFailCause_Lst, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_MeasurementInitiationResult_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztMeasurementInitiationResult_Item */



/*
* FUN : cmUnpkCzt_ValueMeasurementInitiationResult_ItemIEsCls
*  DESC: Function to Unpack Czt_ValueMeasurementInitiationResult_ItemIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueMeasurementInitiationResult_ItemIEsCls
(
Czt_ValueMeasurementInitiationResult_ItemIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueMeasurementInitiationResult_ItemIEsCls(param, val, ptr, mBuf)
Czt_ValueMeasurementInitiationResult_ItemIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueMeasurementInitiationResult_ItemIEsCls) 
	
	switch (val)
	{
		case Cztid_MeasurementInitiationResult_Item:
			CMCHKUNPKPTR(cmUnpkCztMeasurementInitiationResult_Item, &param->u.cztMeasurementInitiationResult_Item, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueMeasurementInitiationResult_ItemIEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_MeasurementInitiationResult_ItemIEs
*  DESC: Function to Unpack CztProtIE_Field_MeasurementInitiationResult_ItemIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_MeasurementInitiationResult_ItemIEs
(
CztProtIE_Field_MeasurementInitiationResult_ItemIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_MeasurementInitiationResult_ItemIEs(param, ptr, mBuf)
CztProtIE_Field_MeasurementInitiationResult_ItemIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_MeasurementInitiationResult_ItemIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueMeasurementInitiationResult_ItemIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_MeasurementInitiationResult_ItemIEs */

/* Element ------------- ProtocolIE-Single-Container ------------ */
#define cmUnpkCztProtIE_Single_Cont_MeasurementInitiationResult_ItemIEs cmUnpkCztProtIE_Field_MeasurementInitiationResult_ItemIEs


/*
* FUN : cmUnpkCztMeasurementInitiationResult_Lst
*  DESC: Function to Unpack CztMeasurementInitiationResult_Lst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztMeasurementInitiationResult_Lst
(
CztMeasurementInitiationResult_Lst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztMeasurementInitiationResult_Lst(param, ptr, mBuf)
CztMeasurementInitiationResult_Lst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztMeasurementInitiationResult_Lst) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Single_Cont_MeasurementInitiationResult_ItemIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Single_Cont_MeasurementInitiationResult_ItemIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztMeasurementInitiationResult_Lst */



/*
* FUN : cmUnpkCzt_ValueResStatusResp_IEsCls
*  DESC: Function to Unpack Czt_ValueResStatusResp_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueResStatusResp_IEsCls
(
Czt_ValueResStatusResp_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueResStatusResp_IEsCls(param, val, ptr, mBuf)
Czt_ValueResStatusResp_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueResStatusResp_IEsCls) 
	
	switch (val)
	{
		case Cztid_ENB1_Measurement_ID:
			CMCHKUNPK(cmUnpkCztMeasurement_ID, &param->u.cztid_ENB1_Measurement_ID, mBuf); 
			break;
		case Cztid_ENB2_Measurement_ID:
			CMCHKUNPK(cmUnpkCztMeasurement_ID, &param->u.cztid_ENB2_Measurement_ID, mBuf); 
			break;
		case Cztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkCztCriticalityDiag, &param->u.cztCriticalityDiag, ptr, mBuf);
			break;
		case Cztid_MeasurementInitiationResult_Lst:
			CMCHKUNPKPTR(cmUnpkCztMeasurementInitiationResult_Lst, &param->u.cztMeasurementInitiationResult_Lst, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueResStatusResp_IEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_ResStatusResp_IEs
*  DESC: Function to Unpack CztProtIE_Field_ResStatusResp_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_ResStatusResp_IEs
(
CztProtIE_Field_ResStatusResp_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_ResStatusResp_IEs(param, ptr, mBuf)
CztProtIE_Field_ResStatusResp_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_ResStatusResp_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueResStatusResp_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_ResStatusResp_IEs */



/*
* FUN : cmUnpkCztProtIE_Cont_ResStatusResp_IEs
*  DESC: Function to Unpack CztProtIE_Cont_ResStatusResp_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Cont_ResStatusResp_IEs
(
CztProtIE_Cont_ResStatusResp_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Cont_ResStatusResp_IEs(param, ptr, mBuf)
CztProtIE_Cont_ResStatusResp_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtIE_Cont_ResStatusResp_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Field_ResStatusResp_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Field_ResStatusResp_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtIE_Cont_ResStatusResp_IEs */



/*
* FUN : cmUnpkCztResStatusResp
*  DESC: Function to Unpack CztResStatusResp structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztResStatusResp
(
CztResStatusResp *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztResStatusResp(param, ptr, mBuf)
CztResStatusResp *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztResStatusResp) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztProtIE_Cont_ResStatusResp_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztResStatusResp */



/*
* FUN : cmUnpkCzt_ExtnCompleteFailCauseInform_Item_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnCompleteFailCauseInform_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnCompleteFailCauseInform_Item_ExtIEsCls
(
Czt_ExtnCompleteFailCauseInform_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnCompleteFailCauseInform_Item_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnCompleteFailCauseInform_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnCompleteFailCauseInform_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnCompleteFailCauseInform_Item_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_CompleteFailCauseInform_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_CompleteFailCauseInform_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_CompleteFailCauseInform_Item_ExtIEs
(
CztProtExtnField_CompleteFailCauseInform_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_CompleteFailCauseInform_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnField_CompleteFailCauseInform_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_CompleteFailCauseInform_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnCompleteFailCauseInform_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_CompleteFailCauseInform_Item_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_CompleteFailCauseInform_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_CompleteFailCauseInform_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_CompleteFailCauseInform_Item_ExtIEs
(
CztProtExtnCont_CompleteFailCauseInform_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_CompleteFailCauseInform_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_CompleteFailCauseInform_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_CompleteFailCauseInform_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_CompleteFailCauseInform_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_CompleteFailCauseInform_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_CompleteFailCauseInform_Item_ExtIEs */



/*
* FUN : cmUnpkCztCompleteFailCauseInform_Item
*  DESC: Function to Unpack CztCompleteFailCauseInform_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztCompleteFailCauseInform_Item
(
CztCompleteFailCauseInform_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztCompleteFailCauseInform_Item(param, ptr, mBuf)
CztCompleteFailCauseInform_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztCompleteFailCauseInform_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztECGI, &param->cell_ID, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztMeasurementFailCause_Lst, &param->measurementFailCause_Lst, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_CompleteFailCauseInform_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztCompleteFailCauseInform_Item */



/*
* FUN : cmUnpkCzt_ValueCompleteFailCauseInform_ItemIEsCls
*  DESC: Function to Unpack Czt_ValueCompleteFailCauseInform_ItemIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueCompleteFailCauseInform_ItemIEsCls
(
Czt_ValueCompleteFailCauseInform_ItemIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueCompleteFailCauseInform_ItemIEsCls(param, val, ptr, mBuf)
Czt_ValueCompleteFailCauseInform_ItemIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueCompleteFailCauseInform_ItemIEsCls) 
	
	switch (val)
	{
		case Cztid_CompleteFailCauseInform_Item:
			CMCHKUNPKPTR(cmUnpkCztCompleteFailCauseInform_Item, &param->u.cztCompleteFailCauseInform_Item, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueCompleteFailCauseInform_ItemIEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_CompleteFailCauseInform_ItemIEs
*  DESC: Function to Unpack CztProtIE_Field_CompleteFailCauseInform_ItemIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_CompleteFailCauseInform_ItemIEs
(
CztProtIE_Field_CompleteFailCauseInform_ItemIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_CompleteFailCauseInform_ItemIEs(param, ptr, mBuf)
CztProtIE_Field_CompleteFailCauseInform_ItemIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_CompleteFailCauseInform_ItemIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueCompleteFailCauseInform_ItemIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_CompleteFailCauseInform_ItemIEs */

/* Element ------------- ProtocolIE-Single-Container ------------ */
#define cmUnpkCztProtIE_Single_Cont_CompleteFailCauseInform_ItemIEs cmUnpkCztProtIE_Field_CompleteFailCauseInform_ItemIEs


/*
* FUN : cmUnpkCztCompleteFailCauseInform_Lst
*  DESC: Function to Unpack CztCompleteFailCauseInform_Lst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztCompleteFailCauseInform_Lst
(
CztCompleteFailCauseInform_Lst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztCompleteFailCauseInform_Lst(param, ptr, mBuf)
CztCompleteFailCauseInform_Lst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztCompleteFailCauseInform_Lst) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Single_Cont_CompleteFailCauseInform_ItemIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Single_Cont_CompleteFailCauseInform_ItemIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztCompleteFailCauseInform_Lst */



/*
* FUN : cmUnpkCzt_ValueResStatusFail_IEsCls
*  DESC: Function to Unpack Czt_ValueResStatusFail_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueResStatusFail_IEsCls
(
Czt_ValueResStatusFail_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueResStatusFail_IEsCls(param, val, ptr, mBuf)
Czt_ValueResStatusFail_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueResStatusFail_IEsCls) 
	
	switch (val)
	{
		case Cztid_ENB1_Measurement_ID:
			CMCHKUNPK(cmUnpkCztMeasurement_ID, &param->u.cztid_ENB1_Measurement_ID, mBuf); 
			break;
		case Cztid_ENB2_Measurement_ID:
			CMCHKUNPK(cmUnpkCztMeasurement_ID, &param->u.cztid_ENB2_Measurement_ID, mBuf); 
			break;
		case Cztid_Cause:
			CMCHKUNPKPTR(cmUnpkCztCause, &param->u.cztCause, ptr, mBuf);
			break;
		case Cztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkCztCriticalityDiag, &param->u.cztCriticalityDiag, ptr, mBuf);
			break;
		case Cztid_CompleteFailCauseInform_Lst:
			CMCHKUNPKPTR(cmUnpkCztCompleteFailCauseInform_Lst, &param->u.cztCompleteFailCauseInform_Lst, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueResStatusFail_IEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_ResStatusFail_IEs
*  DESC: Function to Unpack CztProtIE_Field_ResStatusFail_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_ResStatusFail_IEs
(
CztProtIE_Field_ResStatusFail_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_ResStatusFail_IEs(param, ptr, mBuf)
CztProtIE_Field_ResStatusFail_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_ResStatusFail_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueResStatusFail_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_ResStatusFail_IEs */



/*
* FUN : cmUnpkCztProtIE_Cont_ResStatusFail_IEs
*  DESC: Function to Unpack CztProtIE_Cont_ResStatusFail_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Cont_ResStatusFail_IEs
(
CztProtIE_Cont_ResStatusFail_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Cont_ResStatusFail_IEs(param, ptr, mBuf)
CztProtIE_Cont_ResStatusFail_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtIE_Cont_ResStatusFail_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Field_ResStatusFail_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Field_ResStatusFail_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtIE_Cont_ResStatusFail_IEs */



/*
* FUN : cmUnpkCztResStatusFail
*  DESC: Function to Unpack CztResStatusFail structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztResStatusFail
(
CztResStatusFail *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztResStatusFail(param, ptr, mBuf)
CztResStatusFail *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztResStatusFail) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztProtIE_Cont_ResStatusFail_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztResStatusFail */



/*
* FUN : cmUnpkCzt_ExtnCellMeasurementResult_Item_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnCellMeasurementResult_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnCellMeasurementResult_Item_ExtIEsCls
(
Czt_ExtnCellMeasurementResult_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnCellMeasurementResult_Item_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnCellMeasurementResult_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnCellMeasurementResult_Item_ExtIEsCls) 
	
	switch (val)
	{
		case Cztid_CompositeAvailableCapacityGroup:
			CMCHKUNPKPTR(cmUnpkCztCompositeAvailableCapacityGroup, &param->u.cztCompositeAvailableCapacityGroup, ptr, mBuf);
			break;
		case Cztid_ABS_Status:
			CMCHKUNPKPTR(cmUnpkCztABS_Status, &param->u.cztABS_Status, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ExtnCellMeasurementResult_Item_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_CellMeasurementResult_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_CellMeasurementResult_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_CellMeasurementResult_Item_ExtIEs
(
CztProtExtnField_CellMeasurementResult_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_CellMeasurementResult_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnField_CellMeasurementResult_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_CellMeasurementResult_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnCellMeasurementResult_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_CellMeasurementResult_Item_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_CellMeasurementResult_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_CellMeasurementResult_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_CellMeasurementResult_Item_ExtIEs
(
CztProtExtnCont_CellMeasurementResult_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_CellMeasurementResult_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_CellMeasurementResult_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_CellMeasurementResult_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_CellMeasurementResult_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_CellMeasurementResult_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_CellMeasurementResult_Item_ExtIEs */



/*
* FUN : cmUnpkCztCellMeasurementResult_Item
*  DESC: Function to Unpack CztCellMeasurementResult_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztCellMeasurementResult_Item
(
CztCellMeasurementResult_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztCellMeasurementResult_Item(param, ptr, mBuf)
CztCellMeasurementResult_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztCellMeasurementResult_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztECGI, &param->cell_ID, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztHWLoadIndicator, &param->hWLoadIndicator, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztS1TNLLoadIndicator, &param->s1TNLLoadIndicator, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztRadioResStatus, &param->radioResStatus, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_CellMeasurementResult_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztCellMeasurementResult_Item */



/*
* FUN : cmUnpkCzt_ValueCellMeasurementResult_ItemIEsCls
*  DESC: Function to Unpack Czt_ValueCellMeasurementResult_ItemIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueCellMeasurementResult_ItemIEsCls
(
Czt_ValueCellMeasurementResult_ItemIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueCellMeasurementResult_ItemIEsCls(param, val, ptr, mBuf)
Czt_ValueCellMeasurementResult_ItemIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueCellMeasurementResult_ItemIEsCls) 
	
	switch (val)
	{
		case Cztid_CellMeasurementResult_Item:
			CMCHKUNPKPTR(cmUnpkCztCellMeasurementResult_Item, &param->u.cztCellMeasurementResult_Item, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueCellMeasurementResult_ItemIEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_CellMeasurementResult_ItemIEs
*  DESC: Function to Unpack CztProtIE_Field_CellMeasurementResult_ItemIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_CellMeasurementResult_ItemIEs
(
CztProtIE_Field_CellMeasurementResult_ItemIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_CellMeasurementResult_ItemIEs(param, ptr, mBuf)
CztProtIE_Field_CellMeasurementResult_ItemIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_CellMeasurementResult_ItemIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueCellMeasurementResult_ItemIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_CellMeasurementResult_ItemIEs */

/* Element ------------- ProtocolIE-Single-Container ------------ */
#define cmUnpkCztProtIE_Single_Cont_CellMeasurementResult_ItemIEs cmUnpkCztProtIE_Field_CellMeasurementResult_ItemIEs


/*
* FUN : cmUnpkCztCellMeasurementResult_Lst
*  DESC: Function to Unpack CztCellMeasurementResult_Lst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztCellMeasurementResult_Lst
(
CztCellMeasurementResult_Lst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztCellMeasurementResult_Lst(param, ptr, mBuf)
CztCellMeasurementResult_Lst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztCellMeasurementResult_Lst) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Single_Cont_CellMeasurementResult_ItemIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Single_Cont_CellMeasurementResult_ItemIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztCellMeasurementResult_Lst */



/*
* FUN : cmUnpkCzt_ValueResStatusUpd_IEsCls
*  DESC: Function to Unpack Czt_ValueResStatusUpd_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueResStatusUpd_IEsCls
(
Czt_ValueResStatusUpd_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueResStatusUpd_IEsCls(param, val, ptr, mBuf)
Czt_ValueResStatusUpd_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueResStatusUpd_IEsCls) 
	
	switch (val)
	{
		case Cztid_ENB1_Measurement_ID:
			CMCHKUNPK(cmUnpkCztMeasurement_ID, &param->u.cztid_ENB1_Measurement_ID, mBuf); 
			break;
		case Cztid_ENB2_Measurement_ID:
			CMCHKUNPK(cmUnpkCztMeasurement_ID, &param->u.cztid_ENB2_Measurement_ID, mBuf); 
			break;
		case Cztid_CellMeasurementResult:
			CMCHKUNPKPTR(cmUnpkCztCellMeasurementResult_Lst, &param->u.cztCellMeasurementResult_Lst, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueResStatusUpd_IEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_ResStatusUpd_IEs
*  DESC: Function to Unpack CztProtIE_Field_ResStatusUpd_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_ResStatusUpd_IEs
(
CztProtIE_Field_ResStatusUpd_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_ResStatusUpd_IEs(param, ptr, mBuf)
CztProtIE_Field_ResStatusUpd_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_ResStatusUpd_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueResStatusUpd_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_ResStatusUpd_IEs */



/*
* FUN : cmUnpkCztProtIE_Cont_ResStatusUpd_IEs
*  DESC: Function to Unpack CztProtIE_Cont_ResStatusUpd_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Cont_ResStatusUpd_IEs
(
CztProtIE_Cont_ResStatusUpd_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Cont_ResStatusUpd_IEs(param, ptr, mBuf)
CztProtIE_Cont_ResStatusUpd_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtIE_Cont_ResStatusUpd_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Field_ResStatusUpd_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Field_ResStatusUpd_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtIE_Cont_ResStatusUpd_IEs */



/*
* FUN : cmUnpkCztResStatusUpd
*  DESC: Function to Unpack CztResStatusUpd structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztResStatusUpd
(
CztResStatusUpd *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztResStatusUpd(param, ptr, mBuf)
CztResStatusUpd *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztResStatusUpd) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztProtIE_Cont_ResStatusUpd_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztResStatusUpd */



/*
* FUN : cmUnpkCzt_ValuePrivMsg_IEsCls
*  DESC: Function to Unpack Czt_ValuePrivMsg_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValuePrivMsg_IEsCls
(
Czt_ValuePrivMsg_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValuePrivMsg_IEsCls(param, val, ptr, mBuf)
Czt_ValuePrivMsg_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValuePrivMsg_IEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ValuePrivMsg_IEsCls */



/*
* FUN : cmUnpkCztPrivIE_Field_PrivMsg_IEs
*  DESC: Function to Unpack CztPrivIE_Field_PrivMsg_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztPrivIE_Field_PrivMsg_IEs
(
CztPrivIE_Field_PrivMsg_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztPrivIE_Field_PrivMsg_IEs(param, ptr, mBuf)
CztPrivIE_Field_PrivMsg_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztPrivIE_Field_PrivMsg_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztPrivIE_ID, &param->id, ptr, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztPrivIE_Field_PrivMsg_IEs */



/*
* FUN : cmUnpkCztPrivIE_Cont_PrivMsg_IEs
*  DESC: Function to Unpack CztPrivIE_Cont_PrivMsg_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztPrivIE_Cont_PrivMsg_IEs
(
CztPrivIE_Cont_PrivMsg_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztPrivIE_Cont_PrivMsg_IEs(param, ptr, mBuf)
CztPrivIE_Cont_PrivMsg_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztPrivIE_Cont_PrivMsg_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztPrivIE_Field_PrivMsg_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztPrivIE_Field_PrivMsg_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztPrivIE_Cont_PrivMsg_IEs */



/*
* FUN : cmUnpkCztPrivMsg
*  DESC: Function to Unpack CztPrivMsg structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztPrivMsg
(
CztPrivMsg *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztPrivMsg(param, ptr, mBuf)
CztPrivMsg *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztPrivMsg) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztPrivIE_Cont_PrivMsg_IEs, &param->privateIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztPrivMsg */



/*
* FUN : cmUnpkCzt_ValueMobilityChangeRqst_IEsCls
*  DESC: Function to Unpack Czt_ValueMobilityChangeRqst_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueMobilityChangeRqst_IEsCls
(
Czt_ValueMobilityChangeRqst_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueMobilityChangeRqst_IEsCls(param, val, ptr, mBuf)
Czt_ValueMobilityChangeRqst_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueMobilityChangeRqst_IEsCls) 
	
	switch (val)
	{
		case Cztid_ENB1_Cell_ID:
			CMCHKUNPKPTR(cmUnpkCztECGI, &param->u.cztid_ENB1_Cell_ID, ptr, mBuf);
			break;
		case Cztid_ENB2_Cell_ID:
			CMCHKUNPKPTR(cmUnpkCztECGI, &param->u.cztid_ENB2_Cell_ID, ptr, mBuf);
			break;
		case Cztid_ENB1_Mobility_Params:
			CMCHKUNPKPTR(cmUnpkCztMobilityParamsInform, &param->u.cztid_ENB1_Mobility_Params, ptr, mBuf);
			break;
		case Cztid_ENB2_Proposed_Mobility_Params:
			CMCHKUNPKPTR(cmUnpkCztMobilityParamsInform, &param->u.cztid_ENB2_Proposed_Mobility_Params, ptr, mBuf);
			break;
		case Cztid_Cause:
			CMCHKUNPKPTR(cmUnpkCztCause, &param->u.cztCause, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueMobilityChangeRqst_IEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_MobilityChangeRqst_IEs
*  DESC: Function to Unpack CztProtIE_Field_MobilityChangeRqst_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_MobilityChangeRqst_IEs
(
CztProtIE_Field_MobilityChangeRqst_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_MobilityChangeRqst_IEs(param, ptr, mBuf)
CztProtIE_Field_MobilityChangeRqst_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_MobilityChangeRqst_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueMobilityChangeRqst_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_MobilityChangeRqst_IEs */



/*
* FUN : cmUnpkCztProtIE_Cont_MobilityChangeRqst_IEs
*  DESC: Function to Unpack CztProtIE_Cont_MobilityChangeRqst_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Cont_MobilityChangeRqst_IEs
(
CztProtIE_Cont_MobilityChangeRqst_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Cont_MobilityChangeRqst_IEs(param, ptr, mBuf)
CztProtIE_Cont_MobilityChangeRqst_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtIE_Cont_MobilityChangeRqst_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Field_MobilityChangeRqst_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Field_MobilityChangeRqst_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtIE_Cont_MobilityChangeRqst_IEs */



/*
* FUN : cmUnpkCztMobilityChangeRqst
*  DESC: Function to Unpack CztMobilityChangeRqst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztMobilityChangeRqst
(
CztMobilityChangeRqst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztMobilityChangeRqst(param, ptr, mBuf)
CztMobilityChangeRqst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztMobilityChangeRqst) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztProtIE_Cont_MobilityChangeRqst_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztMobilityChangeRqst */



/*
* FUN : cmUnpkCzt_ValueMobilityChangeAckg_IEsCls
*  DESC: Function to Unpack Czt_ValueMobilityChangeAckg_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueMobilityChangeAckg_IEsCls
(
Czt_ValueMobilityChangeAckg_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueMobilityChangeAckg_IEsCls(param, val, ptr, mBuf)
Czt_ValueMobilityChangeAckg_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueMobilityChangeAckg_IEsCls) 
	
	switch (val)
	{
		case Cztid_ENB1_Cell_ID:
			CMCHKUNPKPTR(cmUnpkCztECGI, &param->u.cztid_ENB1_Cell_ID, ptr, mBuf);
			break;
		case Cztid_ENB2_Cell_ID:
			CMCHKUNPKPTR(cmUnpkCztECGI, &param->u.cztid_ENB2_Cell_ID, ptr, mBuf);
			break;
		case Cztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkCztCriticalityDiag, &param->u.cztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueMobilityChangeAckg_IEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_MobilityChangeAckg_IEs
*  DESC: Function to Unpack CztProtIE_Field_MobilityChangeAckg_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_MobilityChangeAckg_IEs
(
CztProtIE_Field_MobilityChangeAckg_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_MobilityChangeAckg_IEs(param, ptr, mBuf)
CztProtIE_Field_MobilityChangeAckg_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_MobilityChangeAckg_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueMobilityChangeAckg_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_MobilityChangeAckg_IEs */



/*
* FUN : cmUnpkCztProtIE_Cont_MobilityChangeAckg_IEs
*  DESC: Function to Unpack CztProtIE_Cont_MobilityChangeAckg_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Cont_MobilityChangeAckg_IEs
(
CztProtIE_Cont_MobilityChangeAckg_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Cont_MobilityChangeAckg_IEs(param, ptr, mBuf)
CztProtIE_Cont_MobilityChangeAckg_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtIE_Cont_MobilityChangeAckg_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Field_MobilityChangeAckg_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Field_MobilityChangeAckg_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtIE_Cont_MobilityChangeAckg_IEs */



/*
* FUN : cmUnpkCztMobilityChangeAckg
*  DESC: Function to Unpack CztMobilityChangeAckg structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztMobilityChangeAckg
(
CztMobilityChangeAckg *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztMobilityChangeAckg(param, ptr, mBuf)
CztMobilityChangeAckg *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztMobilityChangeAckg) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztProtIE_Cont_MobilityChangeAckg_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztMobilityChangeAckg */



/*
* FUN : cmUnpkCzt_ValueMobilityChangeFail_IEsCls
*  DESC: Function to Unpack Czt_ValueMobilityChangeFail_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueMobilityChangeFail_IEsCls
(
Czt_ValueMobilityChangeFail_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueMobilityChangeFail_IEsCls(param, val, ptr, mBuf)
Czt_ValueMobilityChangeFail_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueMobilityChangeFail_IEsCls) 
	
	switch (val)
	{
		case Cztid_ENB1_Cell_ID:
			CMCHKUNPKPTR(cmUnpkCztECGI, &param->u.cztid_ENB1_Cell_ID, ptr, mBuf);
			break;
		case Cztid_ENB2_Cell_ID:
			CMCHKUNPKPTR(cmUnpkCztECGI, &param->u.cztid_ENB2_Cell_ID, ptr, mBuf);
			break;
		case Cztid_Cause:
			CMCHKUNPKPTR(cmUnpkCztCause, &param->u.cztCause, ptr, mBuf);
			break;
		case Cztid_ENB2_Mobility_Params_Modification_Range:
			CMCHKUNPKPTR(cmUnpkCztMobilityParamsModificationRange, &param->u.cztMobilityParamsModificationRange, ptr, mBuf);
			break;
		case Cztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkCztCriticalityDiag, &param->u.cztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueMobilityChangeFail_IEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_MobilityChangeFail_IEs
*  DESC: Function to Unpack CztProtIE_Field_MobilityChangeFail_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_MobilityChangeFail_IEs
(
CztProtIE_Field_MobilityChangeFail_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_MobilityChangeFail_IEs(param, ptr, mBuf)
CztProtIE_Field_MobilityChangeFail_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_MobilityChangeFail_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueMobilityChangeFail_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_MobilityChangeFail_IEs */



/*
* FUN : cmUnpkCztProtIE_Cont_MobilityChangeFail_IEs
*  DESC: Function to Unpack CztProtIE_Cont_MobilityChangeFail_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Cont_MobilityChangeFail_IEs
(
CztProtIE_Cont_MobilityChangeFail_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Cont_MobilityChangeFail_IEs(param, ptr, mBuf)
CztProtIE_Cont_MobilityChangeFail_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtIE_Cont_MobilityChangeFail_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Field_MobilityChangeFail_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Field_MobilityChangeFail_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtIE_Cont_MobilityChangeFail_IEs */



/*
* FUN : cmUnpkCztMobilityChangeFail
*  DESC: Function to Unpack CztMobilityChangeFail structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztMobilityChangeFail
(
CztMobilityChangeFail *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztMobilityChangeFail(param, ptr, mBuf)
CztMobilityChangeFail *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztMobilityChangeFail) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztProtIE_Cont_MobilityChangeFail_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztMobilityChangeFail */



/*
* FUN : cmUnpkCzt_ValueRLFInd_IEsCls
*  DESC: Function to Unpack Czt_ValueRLFInd_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueRLFInd_IEsCls
(
Czt_ValueRLFInd_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueRLFInd_IEsCls(param, val, ptr, mBuf)
Czt_ValueRLFInd_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueRLFInd_IEsCls) 
	
	switch (val)
	{
		case Cztid_FailCellPCI:
			CMCHKUNPK(cmUnpkCztPCI, &param->u.cztPCI, mBuf); 
			break;
		case Cztid_Re_establishmentCellECGI:
			CMCHKUNPKPTR(cmUnpkCztECGI, &param->u.cztECGI, ptr, mBuf);
			break;
		case Cztid_FailCellCRNTI:
			CMCHKUNPK(cmUnpkCztCRNTI, &param->u.cztCRNTI, mBuf); 
			break;
		case Cztid_ShortMAC_I:
			CMCHKUNPK(cmUnpkCztShortMAC_I, &param->u.cztShortMAC_I, mBuf); 
			break;
		case Cztid_UE_RLF_Report_Cont:
			CZUCHKUNPKPTR(cmUnpkCztUE_RLF_Report_Cont, &param->u.cztUE_RLF_Report_Cont, ptr, mBuf); 
			break;
		case Cztid_RRCConnSetupIndicator:
			CMCHKUNPK(cmUnpkCztRRCConnSetupIndicator, &param->u.cztRRCConnSetupIndicator, mBuf); 
			break;
		case Cztid_RRCConnReestabIndicator:
			CMCHKUNPK(cmUnpkCztRRCConnReestabIndicator, &param->u.cztRRCConnReestabIndicator, mBuf); 
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueRLFInd_IEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_RLFInd_IEs
*  DESC: Function to Unpack CztProtIE_Field_RLFInd_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_RLFInd_IEs
(
CztProtIE_Field_RLFInd_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_RLFInd_IEs(param, ptr, mBuf)
CztProtIE_Field_RLFInd_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_RLFInd_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueRLFInd_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_RLFInd_IEs */



/*
* FUN : cmUnpkCztProtIE_Cont_RLFInd_IEs
*  DESC: Function to Unpack CztProtIE_Cont_RLFInd_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Cont_RLFInd_IEs
(
CztProtIE_Cont_RLFInd_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Cont_RLFInd_IEs(param, ptr, mBuf)
CztProtIE_Cont_RLFInd_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtIE_Cont_RLFInd_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Field_RLFInd_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Field_RLFInd_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtIE_Cont_RLFInd_IEs */



/*
* FUN : cmUnpkCztRLFInd
*  DESC: Function to Unpack CztRLFInd structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztRLFInd
(
CztRLFInd *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztRLFInd(param, ptr, mBuf)
CztRLFInd *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztRLFInd) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztProtIE_Cont_RLFInd_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztRLFInd */



/*
* FUN : cmUnpkCzt_ExtnSrvdCellsToActivate_Item_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnSrvdCellsToActivate_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnSrvdCellsToActivate_Item_ExtIEsCls
(
Czt_ExtnSrvdCellsToActivate_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnSrvdCellsToActivate_Item_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnSrvdCellsToActivate_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnSrvdCellsToActivate_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnSrvdCellsToActivate_Item_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_SrvdCellsToActivate_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_SrvdCellsToActivate_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_SrvdCellsToActivate_Item_ExtIEs
(
CztProtExtnField_SrvdCellsToActivate_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_SrvdCellsToActivate_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnField_SrvdCellsToActivate_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_SrvdCellsToActivate_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnSrvdCellsToActivate_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_SrvdCellsToActivate_Item_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_SrvdCellsToActivate_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_SrvdCellsToActivate_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_SrvdCellsToActivate_Item_ExtIEs
(
CztProtExtnCont_SrvdCellsToActivate_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_SrvdCellsToActivate_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_SrvdCellsToActivate_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_SrvdCellsToActivate_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_SrvdCellsToActivate_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_SrvdCellsToActivate_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_SrvdCellsToActivate_Item_ExtIEs */



/*
* FUN : cmUnpkCztSrvdCellsToActivate_Item
*  DESC: Function to Unpack CztSrvdCellsToActivate_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztSrvdCellsToActivate_Item
(
CztSrvdCellsToActivate_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztSrvdCellsToActivate_Item(param, ptr, mBuf)
CztSrvdCellsToActivate_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztSrvdCellsToActivate_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztECGI, &param->ecgi, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_SrvdCellsToActivate_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztSrvdCellsToActivate_Item */



/*
* FUN : cmUnpkCztSrvdCellsToActivate
*  DESC: Function to Unpack CztSrvdCellsToActivate structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztSrvdCellsToActivate
(
CztSrvdCellsToActivate *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztSrvdCellsToActivate(param, ptr, mBuf)
CztSrvdCellsToActivate *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztSrvdCellsToActivate) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztSrvdCellsToActivate_Item)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztSrvdCellsToActivate_Item, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztSrvdCellsToActivate */



/*
* FUN : cmUnpkCzt_ValueCellActvnRqst_IEsCls
*  DESC: Function to Unpack Czt_ValueCellActvnRqst_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueCellActvnRqst_IEsCls
(
Czt_ValueCellActvnRqst_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueCellActvnRqst_IEsCls(param, val, ptr, mBuf)
Czt_ValueCellActvnRqst_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueCellActvnRqst_IEsCls) 
	
	switch (val)
	{
		case Cztid_SrvdCellsToActivate:
			CMCHKUNPKPTR(cmUnpkCztSrvdCellsToActivate, &param->u.cztSrvdCellsToActivate, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueCellActvnRqst_IEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_CellActvnRqst_IEs
*  DESC: Function to Unpack CztProtIE_Field_CellActvnRqst_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_CellActvnRqst_IEs
(
CztProtIE_Field_CellActvnRqst_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_CellActvnRqst_IEs(param, ptr, mBuf)
CztProtIE_Field_CellActvnRqst_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_CellActvnRqst_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueCellActvnRqst_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_CellActvnRqst_IEs */



/*
* FUN : cmUnpkCztProtIE_Cont_CellActvnRqst_IEs
*  DESC: Function to Unpack CztProtIE_Cont_CellActvnRqst_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Cont_CellActvnRqst_IEs
(
CztProtIE_Cont_CellActvnRqst_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Cont_CellActvnRqst_IEs(param, ptr, mBuf)
CztProtIE_Cont_CellActvnRqst_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtIE_Cont_CellActvnRqst_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Field_CellActvnRqst_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Field_CellActvnRqst_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtIE_Cont_CellActvnRqst_IEs */



/*
* FUN : cmUnpkCztCellActvnRqst
*  DESC: Function to Unpack CztCellActvnRqst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztCellActvnRqst
(
CztCellActvnRqst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztCellActvnRqst(param, ptr, mBuf)
CztCellActvnRqst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztCellActvnRqst) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztProtIE_Cont_CellActvnRqst_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztCellActvnRqst */



/*
* FUN : cmUnpkCzt_ExtnActivatedCellLst_Item_ExtIEsCls
*  DESC: Function to Unpack Czt_ExtnActivatedCellLst_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ExtnActivatedCellLst_Item_ExtIEsCls
(
Czt_ExtnActivatedCellLst_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ExtnActivatedCellLst_Item_ExtIEsCls(param, val, ptr, mBuf)
Czt_ExtnActivatedCellLst_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ExtnActivatedCellLst_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkCzt_ExtnActivatedCellLst_Item_ExtIEsCls */



/*
* FUN : cmUnpkCztProtExtnField_ActivatedCellLst_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnField_ActivatedCellLst_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnField_ActivatedCellLst_Item_ExtIEs
(
CztProtExtnField_ActivatedCellLst_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnField_ActivatedCellLst_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnField_ActivatedCellLst_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtExtnField_ActivatedCellLst_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ExtnActivatedCellLst_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtExtnField_ActivatedCellLst_Item_ExtIEs */



/*
* FUN : cmUnpkCztProtExtnCont_ActivatedCellLst_Item_ExtIEs
*  DESC: Function to Unpack CztProtExtnCont_ActivatedCellLst_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtExtnCont_ActivatedCellLst_Item_ExtIEs
(
CztProtExtnCont_ActivatedCellLst_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtExtnCont_ActivatedCellLst_Item_ExtIEs(param, ptr, mBuf)
CztProtExtnCont_ActivatedCellLst_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtExtnCont_ActivatedCellLst_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtExtnField_ActivatedCellLst_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtExtnField_ActivatedCellLst_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtExtnCont_ActivatedCellLst_Item_ExtIEs */



/*
* FUN : cmUnpkCztActivatedCellLst_Item
*  DESC: Function to Unpack CztActivatedCellLst_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztActivatedCellLst_Item
(
CztActivatedCellLst_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztActivatedCellLst_Item(param, ptr, mBuf)
CztActivatedCellLst_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztActivatedCellLst_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztECGI, &param->ecgi, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkCztProtExtnCont_ActivatedCellLst_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztActivatedCellLst_Item */



/*
* FUN : cmUnpkCztActivatedCellLst
*  DESC: Function to Unpack CztActivatedCellLst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztActivatedCellLst
(
CztActivatedCellLst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztActivatedCellLst(param, ptr, mBuf)
CztActivatedCellLst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztActivatedCellLst) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztActivatedCellLst_Item)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztActivatedCellLst_Item, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztActivatedCellLst */



/*
* FUN : cmUnpkCzt_ValueCellActvnResp_IEsCls
*  DESC: Function to Unpack Czt_ValueCellActvnResp_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueCellActvnResp_IEsCls
(
Czt_ValueCellActvnResp_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueCellActvnResp_IEsCls(param, val, ptr, mBuf)
Czt_ValueCellActvnResp_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueCellActvnResp_IEsCls) 
	
	switch (val)
	{
		case Cztid_ActivatedCellLst:
			CMCHKUNPKPTR(cmUnpkCztActivatedCellLst, &param->u.cztActivatedCellLst, ptr, mBuf);
			break;
		case Cztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkCztCriticalityDiag, &param->u.cztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueCellActvnResp_IEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_CellActvnResp_IEs
*  DESC: Function to Unpack CztProtIE_Field_CellActvnResp_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_CellActvnResp_IEs
(
CztProtIE_Field_CellActvnResp_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_CellActvnResp_IEs(param, ptr, mBuf)
CztProtIE_Field_CellActvnResp_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_CellActvnResp_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueCellActvnResp_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_CellActvnResp_IEs */



/*
* FUN : cmUnpkCztProtIE_Cont_CellActvnResp_IEs
*  DESC: Function to Unpack CztProtIE_Cont_CellActvnResp_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Cont_CellActvnResp_IEs
(
CztProtIE_Cont_CellActvnResp_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Cont_CellActvnResp_IEs(param, ptr, mBuf)
CztProtIE_Cont_CellActvnResp_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtIE_Cont_CellActvnResp_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Field_CellActvnResp_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Field_CellActvnResp_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtIE_Cont_CellActvnResp_IEs */



/*
* FUN : cmUnpkCztCellActvnResp
*  DESC: Function to Unpack CztCellActvnResp structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztCellActvnResp
(
CztCellActvnResp *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztCellActvnResp(param, ptr, mBuf)
CztCellActvnResp *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztCellActvnResp) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztProtIE_Cont_CellActvnResp_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztCellActvnResp */



/*
* FUN : cmUnpkCzt_ValueCellActvnFail_IEsCls
*  DESC: Function to Unpack Czt_ValueCellActvnFail_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_ValueCellActvnFail_IEsCls
(
Czt_ValueCellActvnFail_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_ValueCellActvnFail_IEsCls(param, val, ptr, mBuf)
Czt_ValueCellActvnFail_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_ValueCellActvnFail_IEsCls) 
	
	switch (val)
	{
		case Cztid_Cause:
			CMCHKUNPKPTR(cmUnpkCztCause, &param->u.cztCause, ptr, mBuf);
			break;
		case Cztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkCztCriticalityDiag, &param->u.cztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_ValueCellActvnFail_IEsCls */



/*
* FUN : cmUnpkCztProtIE_Field_CellActvnFail_IEs
*  DESC: Function to Unpack CztProtIE_Field_CellActvnFail_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Field_CellActvnFail_IEs
(
CztProtIE_Field_CellActvnFail_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Field_CellActvnFail_IEs(param, ptr, mBuf)
CztProtIE_Field_CellActvnFail_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztProtIE_Field_CellActvnFail_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_ValueCellActvnFail_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztProtIE_Field_CellActvnFail_IEs */



/*
* FUN : cmUnpkCztProtIE_Cont_CellActvnFail_IEs
*  DESC: Function to Unpack CztProtIE_Cont_CellActvnFail_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztProtIE_Cont_CellActvnFail_IEs
(
CztProtIE_Cont_CellActvnFail_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztProtIE_Cont_CellActvnFail_IEs(param, ptr, mBuf)
CztProtIE_Cont_CellActvnFail_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkCztProtIE_Cont_CellActvnFail_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(CztProtIE_Field_CellActvnFail_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkCztProtIE_Field_CellActvnFail_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkCztProtIE_Cont_CellActvnFail_IEs */



/*
* FUN : cmUnpkCztCellActvnFail
*  DESC: Function to Unpack CztCellActvnFail structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztCellActvnFail
(
CztCellActvnFail *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztCellActvnFail(param, ptr, mBuf)
CztCellActvnFail *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztCellActvnFail) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkCztProtIE_Cont_CellActvnFail_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztCellActvnFail */



/*
* FUN : cmUnpkCzt_InitiatingMsgCls
*  DESC: Function to Unpack Czt_InitiatingMsgCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_InitiatingMsgCls
(
Czt_InitiatingMsgCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_InitiatingMsgCls(param, val, ptr, mBuf)
Czt_InitiatingMsgCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_InitiatingMsgCls) 
	
	switch (val)
	{
		case Cztid_handoverPrep:
			CMCHKUNPKPTR(cmUnpkCztHovrRqst, &param->u.cztHovrRqst, ptr, mBuf);
			break;
		case Cztid_reset:
			CMCHKUNPKPTR(cmUnpkCztResetRqst, &param->u.cztResetRqst, ptr, mBuf);
			break;
		case Cztid_x2Setup:
			CMCHKUNPKPTR(cmUnpkCztX2SetupRqst, &param->u.cztX2SetupRqst, ptr, mBuf);
			break;
		case Cztid_resourceStatusRprtngInitiation:
			CMCHKUNPKPTR(cmUnpkCztResStatusRqst, &param->u.cztResStatusRqst, ptr, mBuf);
			break;
		case Cztid_eNBConfigUpd:
			CMCHKUNPKPTR(cmUnpkCztENBConfigUpd, &param->u.cztENBConfigUpd, ptr, mBuf);
			break;
		case Cztid_mobilitySettingsChange:
			CMCHKUNPKPTR(cmUnpkCztMobilityChangeRqst, &param->u.cztMobilityChangeRqst, ptr, mBuf);
			break;
		case Cztid_cellActvn:
			CMCHKUNPKPTR(cmUnpkCztCellActvnRqst, &param->u.cztCellActvnRqst, ptr, mBuf);
			break;
		case Cztid_snStatusTfr:
			CMCHKUNPKPTR(cmUnpkCztSNStatusTfr, &param->u.cztSNStatusTfr, ptr, mBuf);
			break;
		case Cztid_uECntxtRls:
			CMCHKUNPKPTR(cmUnpkCztUECntxtRls, &param->u.cztUECntxtRls, ptr, mBuf);
			break;
		case Cztid_handoverCancel:
			CMCHKUNPKPTR(cmUnpkCztHovrCancel, &param->u.cztHovrCancel, ptr, mBuf);
			break;
		case Cztid_errorInd:
			CMCHKUNPKPTR(cmUnpkCztErrInd, &param->u.cztErrInd, ptr, mBuf);
			break;
		case Cztid_resourceStatusRprtng:
			CMCHKUNPKPTR(cmUnpkCztResStatusUpd, &param->u.cztResStatusUpd, ptr, mBuf);
			break;
		case Cztid_loadInd:
			CMCHKUNPKPTR(cmUnpkCztLoadInform, &param->u.cztLoadInform, ptr, mBuf);
			break;
		case Cztid_privateMsg:
			CMCHKUNPKPTR(cmUnpkCztPrivMsg, &param->u.cztPrivMsg, ptr, mBuf);
			break;
		case Cztid_rLFInd:
			CMCHKUNPKPTR(cmUnpkCztRLFInd, &param->u.cztRLFInd, ptr, mBuf);
			break;
		case Cztid_handoverReport:
			CMCHKUNPKPTR(cmUnpkCztHovrReport, &param->u.cztHovrReport, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_InitiatingMsgCls */



/*
* FUN : cmUnpkCztInitiatingMsg
*  DESC: Function to Unpack CztInitiatingMsg structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztInitiatingMsg
(
CztInitiatingMsg *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztInitiatingMsg(param, ptr, mBuf)
CztInitiatingMsg *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztInitiatingMsg) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProcedureCode, &param->procedureCode, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_InitiatingMsgCls(&param->value, param->procedureCode.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztInitiatingMsg */



/*
* FUN : cmUnpkCzt_SuccessfulOutcomeCls
*  DESC: Function to Unpack Czt_SuccessfulOutcomeCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_SuccessfulOutcomeCls
(
Czt_SuccessfulOutcomeCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_SuccessfulOutcomeCls(param, val, ptr, mBuf)
Czt_SuccessfulOutcomeCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_SuccessfulOutcomeCls) 
	
	switch (val)
	{
		case Cztid_handoverPrep:
			CMCHKUNPKPTR(cmUnpkCztHovrRqstAckg, &param->u.cztHovrRqstAckg, ptr, mBuf);
			break;
		case Cztid_reset:
			CMCHKUNPKPTR(cmUnpkCztResetResp, &param->u.cztResetResp, ptr, mBuf);
			break;
		case Cztid_x2Setup:
			CMCHKUNPKPTR(cmUnpkCztX2SetupResp, &param->u.cztX2SetupResp, ptr, mBuf);
			break;
		case Cztid_resourceStatusRprtngInitiation:
			CMCHKUNPKPTR(cmUnpkCztResStatusResp, &param->u.cztResStatusResp, ptr, mBuf);
			break;
		case Cztid_eNBConfigUpd:
			CMCHKUNPKPTR(cmUnpkCztENBConfigUpdAckg, &param->u.cztENBConfigUpdAckg, ptr, mBuf);
			break;
		case Cztid_mobilitySettingsChange:
			CMCHKUNPKPTR(cmUnpkCztMobilityChangeAckg, &param->u.cztMobilityChangeAckg, ptr, mBuf);
			break;
		case Cztid_cellActvn:
			CMCHKUNPKPTR(cmUnpkCztCellActvnResp, &param->u.cztCellActvnResp, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_SuccessfulOutcomeCls */



/*
* FUN : cmUnpkCztSuccessfulOutcome
*  DESC: Function to Unpack CztSuccessfulOutcome structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztSuccessfulOutcome
(
CztSuccessfulOutcome *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztSuccessfulOutcome(param, ptr, mBuf)
CztSuccessfulOutcome *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztSuccessfulOutcome) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProcedureCode, &param->procedureCode, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_SuccessfulOutcomeCls(&param->value, param->procedureCode.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztSuccessfulOutcome */



/*
* FUN : cmUnpkCzt_UnsuccessfulOutcomeCls
*  DESC: Function to Unpack Czt_UnsuccessfulOutcomeCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCzt_UnsuccessfulOutcomeCls
(
Czt_UnsuccessfulOutcomeCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCzt_UnsuccessfulOutcomeCls(param, val, ptr, mBuf)
Czt_UnsuccessfulOutcomeCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCzt_UnsuccessfulOutcomeCls) 
	
	switch (val)
	{
		case Cztid_handoverPrep:
			CMCHKUNPKPTR(cmUnpkCztHovrPrepFail, &param->u.cztHovrPrepFail, ptr, mBuf);
			break;
		case Cztid_x2Setup:
			CMCHKUNPKPTR(cmUnpkCztX2SetupFail, &param->u.cztX2SetupFail, ptr, mBuf);
			break;
		case Cztid_resourceStatusRprtngInitiation:
			CMCHKUNPKPTR(cmUnpkCztResStatusFail, &param->u.cztResStatusFail, ptr, mBuf);
			break;
		case Cztid_eNBConfigUpd:
			CMCHKUNPKPTR(cmUnpkCztENBConfigUpdFail, &param->u.cztENBConfigUpdFail, ptr, mBuf);
			break;
		case Cztid_mobilitySettingsChange:
			CMCHKUNPKPTR(cmUnpkCztMobilityChangeFail, &param->u.cztMobilityChangeFail, ptr, mBuf);
			break;
		case Cztid_cellActvn:
			CMCHKUNPKPTR(cmUnpkCztCellActvnFail, &param->u.cztCellActvnFail, ptr, mBuf);
			break;
		default:
		RETVALUE(RFAILED);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCzt_UnsuccessfulOutcomeCls */



/*
* FUN : cmUnpkCztUnsuccessfulOutcome
*  DESC: Function to Unpack CztUnsuccessfulOutcome structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztUnsuccessfulOutcome
(
CztUnsuccessfulOutcome *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztUnsuccessfulOutcome(param, ptr, mBuf)
CztUnsuccessfulOutcome *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztUnsuccessfulOutcome) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkCztProcedureCode, &param->procedureCode, mBuf); 
		CMCHKUNPK(cmUnpkCztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkCzt_UnsuccessfulOutcomeCls(&param->value, param->procedureCode.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztUnsuccessfulOutcome */



/*
* FUN : cmUnpkCztX2AP_PDU
*  DESC: Function to Unpack CztX2AP_PDU structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkCztX2AP_PDU
(
CztX2AP_PDU *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkCztX2AP_PDU(param, ptr, mBuf)
CztX2AP_PDU *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkCztX2AP_PDU) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case X2AP_PDU_INITIATINGMSG :
				CMCHKUNPKPTR(cmUnpkCztInitiatingMsg, &param->val.initiatingMsg, ptr, mBuf); 
				break;
			case X2AP_PDU_SUCCESSFULOUTCOME :
				CMCHKUNPKPTR(cmUnpkCztSuccessfulOutcome, &param->val.successfulOutcome, ptr, mBuf); 
				break;
			case X2AP_PDU_UNSUCCESSFULOUTCOME :
				CMCHKUNPKPTR(cmUnpkCztUnsuccessfulOutcome, &param->val.unsuccessfulOutcome, ptr, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkCztX2AP_PDU */


#ifdef __cplusplus
}
#endif /*__cplusplus*/

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

