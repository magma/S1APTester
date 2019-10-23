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
#include <szt_unpk.x>

#define cmUnpkSztCriticality cmUnpkTknU32

#define cmUnpkSztPresence cmUnpkTknU32

#define cmUnpkSztPrivIE_IDlocal cmUnpkTknU32 


/*
* FUN : cmUnpkSztPrivIE_ID
*  DESC: Function to Unpack SztPrivIE_ID structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztPrivIE_ID
(
SztPrivIE_ID *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztPrivIE_ID(param, ptr, mBuf)
SztPrivIE_ID *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztPrivIE_ID) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case PRIVIE_ID_LOCAL :
				CMCHKUNPK(cmUnpkSztPrivIE_IDlocal, &param->val.local, mBuf); 
				break;
			case PRIVIE_ID_GLOBAL :
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztPrivIE_ID */

#define cmUnpkSztProcedureCode cmUnpkTknU32 
#define cmUnpkSztProtExtnID cmUnpkTknU32 
#define cmUnpkSztProtIE_ID cmUnpkTknU32 
#define cmUnpkSztTrgMsg cmUnpkTknU32

#define cmUnpkSztTBCD_STRING cmUnpkTknStrOSXL 
/* Element ------------- PLMNidentity ------------ */
#define cmUnpkSztPLMNidentity cmUnpkSztTBCD_STRING
#define cmUnpkSztCellIdentity cmUnpkTknBStr32 


/*
* FUN : cmUnpkSzt_ExtnEUTRAN_CGI_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnEUTRAN_CGI_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnEUTRAN_CGI_ExtIEsCls
(
Szt_ExtnEUTRAN_CGI_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnEUTRAN_CGI_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnEUTRAN_CGI_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnEUTRAN_CGI_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnEUTRAN_CGI_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_EUTRAN_CGI_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_EUTRAN_CGI_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_EUTRAN_CGI_ExtIEs
(
SztProtExtnField_EUTRAN_CGI_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_EUTRAN_CGI_ExtIEs(param, ptr, mBuf)
SztProtExtnField_EUTRAN_CGI_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_EUTRAN_CGI_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnEUTRAN_CGI_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_EUTRAN_CGI_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_EUTRAN_CGI_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_EUTRAN_CGI_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_EUTRAN_CGI_ExtIEs
(
SztProtExtnCont_EUTRAN_CGI_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_EUTRAN_CGI_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_EUTRAN_CGI_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_EUTRAN_CGI_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_EUTRAN_CGI_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_EUTRAN_CGI_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_EUTRAN_CGI_ExtIEs */



/*
* FUN : cmUnpkSztEUTRAN_CGI
*  DESC: Function to Unpack SztEUTRAN_CGI structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztEUTRAN_CGI
(
SztEUTRAN_CGI *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztEUTRAN_CGI(param, ptr, mBuf)
SztEUTRAN_CGI *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztEUTRAN_CGI) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		SZUCHKUNPKPTR(cmUnpkSztPLMNidentity, &param->pLMNidentity, ptr, mBuf); 
		CMCHKUNPK(cmUnpkSztCellIdentity, &param->cell_ID, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_EUTRAN_CGI_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztEUTRAN_CGI */



/*
* FUN : cmUnpkSztCellIdLstforMDT
*  DESC: Function to Unpack SztCellIdLstforMDT structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztCellIdLstforMDT
(
SztCellIdLstforMDT *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztCellIdLstforMDT(param, ptr, mBuf)
SztCellIdLstforMDT *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztCellIdLstforMDT) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztEUTRAN_CGI)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztEUTRAN_CGI, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztCellIdLstforMDT */



/*
* FUN : cmUnpkSzt_ExtnCellBasedMDT_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnCellBasedMDT_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnCellBasedMDT_ExtIEsCls
(
Szt_ExtnCellBasedMDT_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnCellBasedMDT_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnCellBasedMDT_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnCellBasedMDT_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnCellBasedMDT_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_CellBasedMDT_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_CellBasedMDT_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_CellBasedMDT_ExtIEs
(
SztProtExtnField_CellBasedMDT_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_CellBasedMDT_ExtIEs(param, ptr, mBuf)
SztProtExtnField_CellBasedMDT_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_CellBasedMDT_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnCellBasedMDT_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_CellBasedMDT_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_CellBasedMDT_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_CellBasedMDT_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_CellBasedMDT_ExtIEs
(
SztProtExtnCont_CellBasedMDT_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_CellBasedMDT_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_CellBasedMDT_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_CellBasedMDT_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_CellBasedMDT_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_CellBasedMDT_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_CellBasedMDT_ExtIEs */



/*
* FUN : cmUnpkSztCellBasedMDT
*  DESC: Function to Unpack SztCellBasedMDT structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztCellBasedMDT
(
SztCellBasedMDT *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztCellBasedMDT(param, ptr, mBuf)
SztCellBasedMDT *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztCellBasedMDT) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztCellIdLstforMDT, &param->cellIdLstforMDT, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_CellBasedMDT_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztCellBasedMDT */

#define cmUnpkSztTAC cmUnpkTknStr4 


/*
* FUN : cmUnpkSztTALstforMDT
*  DESC: Function to Unpack SztTALstforMDT structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztTALstforMDT
(
SztTALstforMDT *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztTALstforMDT(param, ptr, mBuf)
SztTALstforMDT *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztTALstforMDT) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztTAC)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPK(cmUnpkSztTAC, &(param->member[i]), mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztTALstforMDT */



/*
* FUN : cmUnpkSzt_ExtnTABasedMDT_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnTABasedMDT_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnTABasedMDT_ExtIEsCls
(
Szt_ExtnTABasedMDT_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnTABasedMDT_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnTABasedMDT_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnTABasedMDT_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnTABasedMDT_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_TABasedMDT_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_TABasedMDT_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_TABasedMDT_ExtIEs
(
SztProtExtnField_TABasedMDT_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_TABasedMDT_ExtIEs(param, ptr, mBuf)
SztProtExtnField_TABasedMDT_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_TABasedMDT_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnTABasedMDT_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_TABasedMDT_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_TABasedMDT_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_TABasedMDT_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_TABasedMDT_ExtIEs
(
SztProtExtnCont_TABasedMDT_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_TABasedMDT_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_TABasedMDT_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_TABasedMDT_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_TABasedMDT_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_TABasedMDT_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_TABasedMDT_ExtIEs */



/*
* FUN : cmUnpkSztTABasedMDT
*  DESC: Function to Unpack SztTABasedMDT structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztTABasedMDT
(
SztTABasedMDT *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztTABasedMDT(param, ptr, mBuf)
SztTABasedMDT *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztTABasedMDT) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztTALstforMDT, &param->tALstforMDT, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_TABasedMDT_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztTABasedMDT */



/*
* FUN : cmUnpkSzt_ExtnTAI_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnTAI_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnTAI_ExtIEsCls
(
Szt_ExtnTAI_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnTAI_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnTAI_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnTAI_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnTAI_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_TAI_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_TAI_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_TAI_ExtIEs
(
SztProtExtnField_TAI_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_TAI_ExtIEs(param, ptr, mBuf)
SztProtExtnField_TAI_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_TAI_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnTAI_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_TAI_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_TAI_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_TAI_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_TAI_ExtIEs
(
SztProtExtnCont_TAI_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_TAI_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_TAI_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_TAI_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_TAI_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_TAI_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_TAI_ExtIEs */



/*
* FUN : cmUnpkSztTAI
*  DESC: Function to Unpack SztTAI structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztTAI
(
SztTAI *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztTAI(param, ptr, mBuf)
SztTAI *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztTAI) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		SZUCHKUNPKPTR(cmUnpkSztPLMNidentity, &param->pLMNidentity, ptr, mBuf); 
		CMCHKUNPK(cmUnpkSztTAC, &param->tAC, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_TAI_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztTAI */



/*
* FUN : cmUnpkSztTAILstforMDT
*  DESC: Function to Unpack SztTAILstforMDT structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztTAILstforMDT
(
SztTAILstforMDT *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztTAILstforMDT(param, ptr, mBuf)
SztTAILstforMDT *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztTAILstforMDT) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztTAI)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztTAI, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztTAILstforMDT */



/*
* FUN : cmUnpkSzt_ExtnTAIBasedMDT_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnTAIBasedMDT_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnTAIBasedMDT_ExtIEsCls
(
Szt_ExtnTAIBasedMDT_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnTAIBasedMDT_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnTAIBasedMDT_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnTAIBasedMDT_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnTAIBasedMDT_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_TAIBasedMDT_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_TAIBasedMDT_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_TAIBasedMDT_ExtIEs
(
SztProtExtnField_TAIBasedMDT_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_TAIBasedMDT_ExtIEs(param, ptr, mBuf)
SztProtExtnField_TAIBasedMDT_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_TAIBasedMDT_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnTAIBasedMDT_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_TAIBasedMDT_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_TAIBasedMDT_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_TAIBasedMDT_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_TAIBasedMDT_ExtIEs
(
SztProtExtnCont_TAIBasedMDT_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_TAIBasedMDT_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_TAIBasedMDT_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_TAIBasedMDT_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_TAIBasedMDT_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_TAIBasedMDT_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_TAIBasedMDT_ExtIEs */



/*
* FUN : cmUnpkSztTAIBasedMDT
*  DESC: Function to Unpack SztTAIBasedMDT structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztTAIBasedMDT
(
SztTAIBasedMDT *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztTAIBasedMDT(param, ptr, mBuf)
SztTAIBasedMDT *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztTAIBasedMDT) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztTAILstforMDT, &param->tAILstforMDT, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_TAIBasedMDT_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztTAIBasedMDT */



/*
* FUN : cmUnpkSztAreaScopeOfMDT
*  DESC: Function to Unpack SztAreaScopeOfMDT structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztAreaScopeOfMDT
(
SztAreaScopeOfMDT *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztAreaScopeOfMDT(param, ptr, mBuf)
SztAreaScopeOfMDT *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztAreaScopeOfMDT) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case AREASCOPEOFMDT_CELLBASED :
				CMCHKUNPKPTR(cmUnpkSztCellBasedMDT, &param->val.cellBased, ptr, mBuf); 
				break;
			case AREASCOPEOFMDT_TABASED :
				CMCHKUNPKPTR(cmUnpkSztTABasedMDT, &param->val.tABased, ptr, mBuf); 
				break;
			case AREASCOPEOFMDT_PLMNWIDE :
				break;
			case AREASCOPEOFMDT_TAIBASED :
				CMCHKUNPKPTR(cmUnpkSztTAIBasedMDT, &param->val.tAIBased, ptr, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztAreaScopeOfMDT */

#define cmUnpkSztPriorityLvl cmUnpkTknU32 
#define cmUnpkSztPre_emptionCapblty cmUnpkTknU32

#define cmUnpkSztPre_emptionVulnerability cmUnpkTknU32



/*
* FUN : cmUnpkSzt_ExtnAllocnAndRetentionPriority_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnAllocnAndRetentionPriority_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnAllocnAndRetentionPriority_ExtIEsCls
(
Szt_ExtnAllocnAndRetentionPriority_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnAllocnAndRetentionPriority_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnAllocnAndRetentionPriority_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnAllocnAndRetentionPriority_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnAllocnAndRetentionPriority_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_AllocnAndRetentionPriority_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_AllocnAndRetentionPriority_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_AllocnAndRetentionPriority_ExtIEs
(
SztProtExtnField_AllocnAndRetentionPriority_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_AllocnAndRetentionPriority_ExtIEs(param, ptr, mBuf)
SztProtExtnField_AllocnAndRetentionPriority_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_AllocnAndRetentionPriority_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnAllocnAndRetentionPriority_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_AllocnAndRetentionPriority_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_AllocnAndRetentionPriority_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_AllocnAndRetentionPriority_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_AllocnAndRetentionPriority_ExtIEs
(
SztProtExtnCont_AllocnAndRetentionPriority_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_AllocnAndRetentionPriority_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_AllocnAndRetentionPriority_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_AllocnAndRetentionPriority_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_AllocnAndRetentionPriority_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_AllocnAndRetentionPriority_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_AllocnAndRetentionPriority_ExtIEs */



/*
* FUN : cmUnpkSztAllocnAndRetentionPriority
*  DESC: Function to Unpack SztAllocnAndRetentionPriority structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztAllocnAndRetentionPriority
(
SztAllocnAndRetentionPriority *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztAllocnAndRetentionPriority(param, ptr, mBuf)
SztAllocnAndRetentionPriority *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztAllocnAndRetentionPriority) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztPriorityLvl, &param->priorityLvl, mBuf); 
		CMCHKUNPK(cmUnpkSztPre_emptionCapblty, &param->pre_emptionCapblty, mBuf); 
		CMCHKUNPK(cmUnpkSztPre_emptionVulnerability, &param->pre_emptionVulnerability, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_AllocnAndRetentionPriority_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztAllocnAndRetentionPriority */

#define cmUnpkSztE_RAB_ID cmUnpkTknU32 
#define cmUnpkSztPDCP_SN cmUnpkTknU32 
#define cmUnpkSztHFN cmUnpkTknU32 


/*
* FUN : cmUnpkSzt_ExtnCOUNTvalue_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnCOUNTvalue_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnCOUNTvalue_ExtIEsCls
(
Szt_ExtnCOUNTvalue_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnCOUNTvalue_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnCOUNTvalue_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnCOUNTvalue_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnCOUNTvalue_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_COUNTvalue_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_COUNTvalue_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_COUNTvalue_ExtIEs
(
SztProtExtnField_COUNTvalue_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_COUNTvalue_ExtIEs(param, ptr, mBuf)
SztProtExtnField_COUNTvalue_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_COUNTvalue_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnCOUNTvalue_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_COUNTvalue_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_COUNTvalue_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_COUNTvalue_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_COUNTvalue_ExtIEs
(
SztProtExtnCont_COUNTvalue_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_COUNTvalue_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_COUNTvalue_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_COUNTvalue_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_COUNTvalue_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_COUNTvalue_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_COUNTvalue_ExtIEs */



/*
* FUN : cmUnpkSztCOUNTvalue
*  DESC: Function to Unpack SztCOUNTvalue structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztCOUNTvalue
(
SztCOUNTvalue *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztCOUNTvalue(param, ptr, mBuf)
SztCOUNTvalue *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztCOUNTvalue) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztPDCP_SN, &param->pDCP_SN, mBuf); 
		CMCHKUNPK(cmUnpkSztHFN, &param->hFN, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_COUNTvalue_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztCOUNTvalue */

#define cmUnpkSztReceiveStatusofULPDCPSDUs cmUnpkTknStrBSXL 
#define cmUnpkSztPDCP_SNExtended cmUnpkTknU32 
#define cmUnpkSztHFNMdfd cmUnpkTknU32 


/*
* FUN : cmUnpkSzt_ExtnCOUNTValueExtended_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnCOUNTValueExtended_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnCOUNTValueExtended_ExtIEsCls
(
Szt_ExtnCOUNTValueExtended_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnCOUNTValueExtended_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnCOUNTValueExtended_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnCOUNTValueExtended_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnCOUNTValueExtended_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_COUNTValueExtended_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_COUNTValueExtended_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_COUNTValueExtended_ExtIEs
(
SztProtExtnField_COUNTValueExtended_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_COUNTValueExtended_ExtIEs(param, ptr, mBuf)
SztProtExtnField_COUNTValueExtended_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_COUNTValueExtended_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnCOUNTValueExtended_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_COUNTValueExtended_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_COUNTValueExtended_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_COUNTValueExtended_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_COUNTValueExtended_ExtIEs
(
SztProtExtnCont_COUNTValueExtended_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_COUNTValueExtended_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_COUNTValueExtended_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_COUNTValueExtended_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_COUNTValueExtended_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_COUNTValueExtended_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_COUNTValueExtended_ExtIEs */



/*
* FUN : cmUnpkSztCOUNTValueExtended
*  DESC: Function to Unpack SztCOUNTValueExtended structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztCOUNTValueExtended
(
SztCOUNTValueExtended *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztCOUNTValueExtended(param, ptr, mBuf)
SztCOUNTValueExtended *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztCOUNTValueExtended) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztPDCP_SNExtended, &param->pDCP_SNExtended, mBuf); 
		CMCHKUNPK(cmUnpkSztHFNMdfd, &param->hFNMdfd, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_COUNTValueExtended_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztCOUNTValueExtended */

#define cmUnpkSztReceiveStatusOfULPDCPSDUsExtended cmUnpkTknStrBSXL 


/*
* FUN : cmUnpkSzt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls
*  DESC: Function to Unpack Szt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls
(
Szt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls) 
	
	switch (val)
	{
		case Sztid_ULCOUNTValueExtended:
			CMCHKUNPKPTR(cmUnpkSztCOUNTValueExtended, &param->u.sztid_ULCOUNTValueExtended, ptr, mBuf);
			break;
		case Sztid_DLCOUNTValueExtended:
			CMCHKUNPKPTR(cmUnpkSztCOUNTValueExtended, &param->u.sztid_DLCOUNTValueExtended, ptr, mBuf);
			break;
		case Sztid_ReceiveStatusOfULPDCPSDUsExtended:
			CMCHKUNPKPTR(cmUnpkSztReceiveStatusOfULPDCPSDUsExtended, &param->u.sztReceiveStatusOfULPDCPSDUsExtended, ptr, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs
*  DESC: Function to Unpack SztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs
(
SztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs(param, ptr, mBuf)
SztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnBrs_SubjToStatusTfr_ItemExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs
*  DESC: Function to Unpack SztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs
(
SztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs(param, ptr, mBuf)
SztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_Brs_SubjToStatusTfr_ItemExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs */



/*
* FUN : cmUnpkSztBrs_SubjToStatusTfr_Item
*  DESC: Function to Unpack SztBrs_SubjToStatusTfr_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztBrs_SubjToStatusTfr_Item
(
SztBrs_SubjToStatusTfr_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztBrs_SubjToStatusTfr_Item(param, ptr, mBuf)
SztBrs_SubjToStatusTfr_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztBrs_SubjToStatusTfr_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztCOUNTvalue, &param->uL_COUNTvalue, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztCOUNTvalue, &param->dL_COUNTvalue, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztReceiveStatusofULPDCPSDUs, &param->receiveStatusofULPDCPSDUs, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_Brs_SubjToStatusTfr_ItemExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztBrs_SubjToStatusTfr_Item */



/*
* FUN : cmUnpkSzt_ValueBrs_SubjToStatusTfr_ItemIEsCls
*  DESC: Function to Unpack Szt_ValueBrs_SubjToStatusTfr_ItemIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueBrs_SubjToStatusTfr_ItemIEsCls
(
Szt_ValueBrs_SubjToStatusTfr_ItemIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueBrs_SubjToStatusTfr_ItemIEsCls(param, val, ptr, mBuf)
Szt_ValueBrs_SubjToStatusTfr_ItemIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueBrs_SubjToStatusTfr_ItemIEsCls) 
	
	switch (val)
	{
		case Sztid_Brs_SubjToStatusTfr_Item:
			CMCHKUNPKPTR(cmUnpkSztBrs_SubjToStatusTfr_Item, &param->u.sztBrs_SubjToStatusTfr_Item, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueBrs_SubjToStatusTfr_ItemIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_Brs_SubjToStatusTfr_ItemIEs
*  DESC: Function to Unpack SztProtIE_Field_Brs_SubjToStatusTfr_ItemIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_Brs_SubjToStatusTfr_ItemIEs
(
SztProtIE_Field_Brs_SubjToStatusTfr_ItemIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_Brs_SubjToStatusTfr_ItemIEs(param, ptr, mBuf)
SztProtIE_Field_Brs_SubjToStatusTfr_ItemIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_Brs_SubjToStatusTfr_ItemIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueBrs_SubjToStatusTfr_ItemIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_Brs_SubjToStatusTfr_ItemIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmUnpkSztProtIE_SingleCont_Brs_SubjToStatusTfr_ItemIEs cmUnpkSztProtIE_Field_Brs_SubjToStatusTfr_ItemIEs


/*
* FUN : cmUnpkSztBrs_SubjToStatusTfrLst
*  DESC: Function to Unpack SztBrs_SubjToStatusTfrLst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztBrs_SubjToStatusTfrLst
(
SztBrs_SubjToStatusTfrLst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztBrs_SubjToStatusTfrLst(param, ptr, mBuf)
SztBrs_SubjToStatusTfrLst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztBrs_SubjToStatusTfrLst) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_SingleCont_Brs_SubjToStatusTfr_ItemIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_SingleCont_Brs_SubjToStatusTfr_ItemIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztBrs_SubjToStatusTfrLst */

#define cmUnpkSztBitRate cmUnpkTknStrOSXL 


/*
* FUN : cmUnpkSztBPLMNs
*  DESC: Function to Unpack SztBPLMNs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztBPLMNs
(
SztBPLMNs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztBPLMNs(param, ptr, mBuf)
SztBPLMNs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztBPLMNs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztPLMNidentity)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			SZUCHKUNPKPTR(cmUnpkSztTBCD_STRING, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztBPLMNs */

#define cmUnpkSztNumberOfBroadcasts cmUnpkTknU32 


/*
* FUN : cmUnpkSzt_ExtnCellID_Cancelled_Item_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnCellID_Cancelled_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnCellID_Cancelled_Item_ExtIEsCls
(
Szt_ExtnCellID_Cancelled_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnCellID_Cancelled_Item_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnCellID_Cancelled_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnCellID_Cancelled_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnCellID_Cancelled_Item_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_CellID_Cancelled_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_CellID_Cancelled_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_CellID_Cancelled_Item_ExtIEs
(
SztProtExtnField_CellID_Cancelled_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_CellID_Cancelled_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnField_CellID_Cancelled_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_CellID_Cancelled_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnCellID_Cancelled_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_CellID_Cancelled_Item_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_CellID_Cancelled_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_CellID_Cancelled_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_CellID_Cancelled_Item_ExtIEs
(
SztProtExtnCont_CellID_Cancelled_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_CellID_Cancelled_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_CellID_Cancelled_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_CellID_Cancelled_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_CellID_Cancelled_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_CellID_Cancelled_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_CellID_Cancelled_Item_ExtIEs */



/*
* FUN : cmUnpkSztCellID_Cancelled_Item
*  DESC: Function to Unpack SztCellID_Cancelled_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztCellID_Cancelled_Item
(
SztCellID_Cancelled_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztCellID_Cancelled_Item(param, ptr, mBuf)
SztCellID_Cancelled_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztCellID_Cancelled_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztEUTRAN_CGI, &param->eCGI, ptr, mBuf); 
		CMCHKUNPK(cmUnpkSztNumberOfBroadcasts, &param->numberOfBroadcasts, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_CellID_Cancelled_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztCellID_Cancelled_Item */



/*
* FUN : cmUnpkSztCellID_Cancelled
*  DESC: Function to Unpack SztCellID_Cancelled structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztCellID_Cancelled
(
SztCellID_Cancelled *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztCellID_Cancelled(param, ptr, mBuf)
SztCellID_Cancelled *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztCellID_Cancelled) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztCellID_Cancelled_Item)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztCellID_Cancelled_Item, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztCellID_Cancelled */



/*
* FUN : cmUnpkSzt_ExtnCancelledCellinTAI_Item_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnCancelledCellinTAI_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnCancelledCellinTAI_Item_ExtIEsCls
(
Szt_ExtnCancelledCellinTAI_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnCancelledCellinTAI_Item_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnCancelledCellinTAI_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnCancelledCellinTAI_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnCancelledCellinTAI_Item_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_CancelledCellinTAI_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_CancelledCellinTAI_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_CancelledCellinTAI_Item_ExtIEs
(
SztProtExtnField_CancelledCellinTAI_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_CancelledCellinTAI_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnField_CancelledCellinTAI_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_CancelledCellinTAI_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnCancelledCellinTAI_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_CancelledCellinTAI_Item_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_CancelledCellinTAI_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_CancelledCellinTAI_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_CancelledCellinTAI_Item_ExtIEs
(
SztProtExtnCont_CancelledCellinTAI_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_CancelledCellinTAI_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_CancelledCellinTAI_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_CancelledCellinTAI_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_CancelledCellinTAI_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_CancelledCellinTAI_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_CancelledCellinTAI_Item_ExtIEs */



/*
* FUN : cmUnpkSztCancelledCellinTAI_Item
*  DESC: Function to Unpack SztCancelledCellinTAI_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztCancelledCellinTAI_Item
(
SztCancelledCellinTAI_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztCancelledCellinTAI_Item(param, ptr, mBuf)
SztCancelledCellinTAI_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztCancelledCellinTAI_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztEUTRAN_CGI, &param->eCGI, ptr, mBuf); 
		CMCHKUNPK(cmUnpkSztNumberOfBroadcasts, &param->numberOfBroadcasts, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_CancelledCellinTAI_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztCancelledCellinTAI_Item */



/*
* FUN : cmUnpkSztCancelledCellinTAI
*  DESC: Function to Unpack SztCancelledCellinTAI structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztCancelledCellinTAI
(
SztCancelledCellinTAI *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztCancelledCellinTAI(param, ptr, mBuf)
SztCancelledCellinTAI *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztCancelledCellinTAI) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztCancelledCellinTAI_Item)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztCancelledCellinTAI_Item, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztCancelledCellinTAI */



/*
* FUN : cmUnpkSzt_ExtnTAI_Cancelled_Item_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnTAI_Cancelled_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnTAI_Cancelled_Item_ExtIEsCls
(
Szt_ExtnTAI_Cancelled_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnTAI_Cancelled_Item_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnTAI_Cancelled_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnTAI_Cancelled_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnTAI_Cancelled_Item_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_TAI_Cancelled_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_TAI_Cancelled_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_TAI_Cancelled_Item_ExtIEs
(
SztProtExtnField_TAI_Cancelled_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_TAI_Cancelled_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnField_TAI_Cancelled_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_TAI_Cancelled_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnTAI_Cancelled_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_TAI_Cancelled_Item_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_TAI_Cancelled_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_TAI_Cancelled_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_TAI_Cancelled_Item_ExtIEs
(
SztProtExtnCont_TAI_Cancelled_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_TAI_Cancelled_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_TAI_Cancelled_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_TAI_Cancelled_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_TAI_Cancelled_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_TAI_Cancelled_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_TAI_Cancelled_Item_ExtIEs */



/*
* FUN : cmUnpkSztTAI_Cancelled_Item
*  DESC: Function to Unpack SztTAI_Cancelled_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztTAI_Cancelled_Item
(
SztTAI_Cancelled_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztTAI_Cancelled_Item(param, ptr, mBuf)
SztTAI_Cancelled_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztTAI_Cancelled_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztTAI, &param->tAI, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztCancelledCellinTAI, &param->cancelledCellinTAI, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_TAI_Cancelled_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztTAI_Cancelled_Item */



/*
* FUN : cmUnpkSztTAI_Cancelled
*  DESC: Function to Unpack SztTAI_Cancelled structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztTAI_Cancelled
(
SztTAI_Cancelled *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztTAI_Cancelled(param, ptr, mBuf)
SztTAI_Cancelled *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztTAI_Cancelled) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztTAI_Cancelled_Item)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztTAI_Cancelled_Item, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztTAI_Cancelled */

#define cmUnpkSztEmergencyAreaID cmUnpkTknStrOSXL 


/*
* FUN : cmUnpkSzt_ExtnCancelledCellinEAI_Item_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnCancelledCellinEAI_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnCancelledCellinEAI_Item_ExtIEsCls
(
Szt_ExtnCancelledCellinEAI_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnCancelledCellinEAI_Item_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnCancelledCellinEAI_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnCancelledCellinEAI_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnCancelledCellinEAI_Item_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_CancelledCellinEAI_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_CancelledCellinEAI_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_CancelledCellinEAI_Item_ExtIEs
(
SztProtExtnField_CancelledCellinEAI_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_CancelledCellinEAI_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnField_CancelledCellinEAI_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_CancelledCellinEAI_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnCancelledCellinEAI_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_CancelledCellinEAI_Item_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_CancelledCellinEAI_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_CancelledCellinEAI_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_CancelledCellinEAI_Item_ExtIEs
(
SztProtExtnCont_CancelledCellinEAI_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_CancelledCellinEAI_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_CancelledCellinEAI_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_CancelledCellinEAI_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_CancelledCellinEAI_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_CancelledCellinEAI_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_CancelledCellinEAI_Item_ExtIEs */



/*
* FUN : cmUnpkSztCancelledCellinEAI_Item
*  DESC: Function to Unpack SztCancelledCellinEAI_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztCancelledCellinEAI_Item
(
SztCancelledCellinEAI_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztCancelledCellinEAI_Item(param, ptr, mBuf)
SztCancelledCellinEAI_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztCancelledCellinEAI_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztEUTRAN_CGI, &param->eCGI, ptr, mBuf); 
		CMCHKUNPK(cmUnpkSztNumberOfBroadcasts, &param->numberOfBroadcasts, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_CancelledCellinEAI_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztCancelledCellinEAI_Item */



/*
* FUN : cmUnpkSztCancelledCellinEAI
*  DESC: Function to Unpack SztCancelledCellinEAI structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztCancelledCellinEAI
(
SztCancelledCellinEAI *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztCancelledCellinEAI(param, ptr, mBuf)
SztCancelledCellinEAI *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztCancelledCellinEAI) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztCancelledCellinEAI_Item)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztCancelledCellinEAI_Item, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztCancelledCellinEAI */



/*
* FUN : cmUnpkSzt_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls
(
Szt_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs
(
SztProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnEmergencyAreaID_Cancelled_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs
(
SztProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_EmergencyAreaID_Cancelled_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs */



/*
* FUN : cmUnpkSztEmergencyAreaID_Cancelled_Item
*  DESC: Function to Unpack SztEmergencyAreaID_Cancelled_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztEmergencyAreaID_Cancelled_Item
(
SztEmergencyAreaID_Cancelled_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztEmergencyAreaID_Cancelled_Item(param, ptr, mBuf)
SztEmergencyAreaID_Cancelled_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztEmergencyAreaID_Cancelled_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		SZUCHKUNPKPTR(cmUnpkSztEmergencyAreaID, &param->emergencyAreaID, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztCancelledCellinEAI, &param->cancelledCellinEAI, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_EmergencyAreaID_Cancelled_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztEmergencyAreaID_Cancelled_Item */



/*
* FUN : cmUnpkSztEmergencyAreaID_Cancelled
*  DESC: Function to Unpack SztEmergencyAreaID_Cancelled structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztEmergencyAreaID_Cancelled
(
SztEmergencyAreaID_Cancelled *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztEmergencyAreaID_Cancelled(param, ptr, mBuf)
SztEmergencyAreaID_Cancelled *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztEmergencyAreaID_Cancelled) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztEmergencyAreaID_Cancelled_Item)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztEmergencyAreaID_Cancelled_Item, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztEmergencyAreaID_Cancelled */



/*
* FUN : cmUnpkSztBroadcastCancelledAreaLst
*  DESC: Function to Unpack SztBroadcastCancelledAreaLst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztBroadcastCancelledAreaLst
(
SztBroadcastCancelledAreaLst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztBroadcastCancelledAreaLst(param, ptr, mBuf)
SztBroadcastCancelledAreaLst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztBroadcastCancelledAreaLst) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case BROADCASTCANCELLEDAREALST_CELLID_CANCELLED :
				CMCHKUNPKPTR(cmUnpkSztCellID_Cancelled, &param->val.cellID_Cancelled, ptr, mBuf); 
				break;
			case BROADCASTCANCELLEDAREALST_TAI_CANCELLED :
				CMCHKUNPKPTR(cmUnpkSztTAI_Cancelled, &param->val.tAI_Cancelled, ptr, mBuf); 
				break;
			case BROADCASTCANCELLEDAREALST_EMERGENCYAREAID_CANCELLED :
				CMCHKUNPKPTR(cmUnpkSztEmergencyAreaID_Cancelled, &param->val.emergencyAreaID_Cancelled, ptr, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztBroadcastCancelledAreaLst */



/*
* FUN : cmUnpkSzt_ExtnCellID_Broadcast_Item_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnCellID_Broadcast_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnCellID_Broadcast_Item_ExtIEsCls
(
Szt_ExtnCellID_Broadcast_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnCellID_Broadcast_Item_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnCellID_Broadcast_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnCellID_Broadcast_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnCellID_Broadcast_Item_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_CellID_Broadcast_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_CellID_Broadcast_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_CellID_Broadcast_Item_ExtIEs
(
SztProtExtnField_CellID_Broadcast_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_CellID_Broadcast_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnField_CellID_Broadcast_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_CellID_Broadcast_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnCellID_Broadcast_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_CellID_Broadcast_Item_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_CellID_Broadcast_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_CellID_Broadcast_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_CellID_Broadcast_Item_ExtIEs
(
SztProtExtnCont_CellID_Broadcast_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_CellID_Broadcast_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_CellID_Broadcast_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_CellID_Broadcast_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_CellID_Broadcast_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_CellID_Broadcast_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_CellID_Broadcast_Item_ExtIEs */



/*
* FUN : cmUnpkSztCellID_Broadcast_Item
*  DESC: Function to Unpack SztCellID_Broadcast_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztCellID_Broadcast_Item
(
SztCellID_Broadcast_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztCellID_Broadcast_Item(param, ptr, mBuf)
SztCellID_Broadcast_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztCellID_Broadcast_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztEUTRAN_CGI, &param->eCGI, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_CellID_Broadcast_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztCellID_Broadcast_Item */



/*
* FUN : cmUnpkSztCellID_Broadcast
*  DESC: Function to Unpack SztCellID_Broadcast structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztCellID_Broadcast
(
SztCellID_Broadcast *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztCellID_Broadcast(param, ptr, mBuf)
SztCellID_Broadcast *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztCellID_Broadcast) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztCellID_Broadcast_Item)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztCellID_Broadcast_Item, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztCellID_Broadcast */



/*
* FUN : cmUnpkSzt_ExtnCompletedCellinTAI_Item_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnCompletedCellinTAI_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnCompletedCellinTAI_Item_ExtIEsCls
(
Szt_ExtnCompletedCellinTAI_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnCompletedCellinTAI_Item_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnCompletedCellinTAI_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnCompletedCellinTAI_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnCompletedCellinTAI_Item_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_CompletedCellinTAI_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_CompletedCellinTAI_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_CompletedCellinTAI_Item_ExtIEs
(
SztProtExtnField_CompletedCellinTAI_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_CompletedCellinTAI_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnField_CompletedCellinTAI_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_CompletedCellinTAI_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnCompletedCellinTAI_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_CompletedCellinTAI_Item_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_CompletedCellinTAI_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_CompletedCellinTAI_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_CompletedCellinTAI_Item_ExtIEs
(
SztProtExtnCont_CompletedCellinTAI_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_CompletedCellinTAI_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_CompletedCellinTAI_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_CompletedCellinTAI_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_CompletedCellinTAI_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_CompletedCellinTAI_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_CompletedCellinTAI_Item_ExtIEs */



/*
* FUN : cmUnpkSztCompletedCellinTAI_Item
*  DESC: Function to Unpack SztCompletedCellinTAI_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztCompletedCellinTAI_Item
(
SztCompletedCellinTAI_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztCompletedCellinTAI_Item(param, ptr, mBuf)
SztCompletedCellinTAI_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztCompletedCellinTAI_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztEUTRAN_CGI, &param->eCGI, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_CompletedCellinTAI_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztCompletedCellinTAI_Item */



/*
* FUN : cmUnpkSztCompletedCellinTAI
*  DESC: Function to Unpack SztCompletedCellinTAI structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztCompletedCellinTAI
(
SztCompletedCellinTAI *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztCompletedCellinTAI(param, ptr, mBuf)
SztCompletedCellinTAI *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztCompletedCellinTAI) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztCompletedCellinTAI_Item)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztCompletedCellinTAI_Item, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztCompletedCellinTAI */



/*
* FUN : cmUnpkSzt_ExtnTAI_Broadcast_Item_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnTAI_Broadcast_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnTAI_Broadcast_Item_ExtIEsCls
(
Szt_ExtnTAI_Broadcast_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnTAI_Broadcast_Item_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnTAI_Broadcast_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnTAI_Broadcast_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnTAI_Broadcast_Item_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_TAI_Broadcast_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_TAI_Broadcast_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_TAI_Broadcast_Item_ExtIEs
(
SztProtExtnField_TAI_Broadcast_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_TAI_Broadcast_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnField_TAI_Broadcast_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_TAI_Broadcast_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnTAI_Broadcast_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_TAI_Broadcast_Item_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_TAI_Broadcast_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_TAI_Broadcast_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_TAI_Broadcast_Item_ExtIEs
(
SztProtExtnCont_TAI_Broadcast_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_TAI_Broadcast_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_TAI_Broadcast_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_TAI_Broadcast_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_TAI_Broadcast_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_TAI_Broadcast_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_TAI_Broadcast_Item_ExtIEs */



/*
* FUN : cmUnpkSztTAI_Broadcast_Item
*  DESC: Function to Unpack SztTAI_Broadcast_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztTAI_Broadcast_Item
(
SztTAI_Broadcast_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztTAI_Broadcast_Item(param, ptr, mBuf)
SztTAI_Broadcast_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztTAI_Broadcast_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztTAI, &param->tAI, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztCompletedCellinTAI, &param->completedCellinTAI, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_TAI_Broadcast_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztTAI_Broadcast_Item */



/*
* FUN : cmUnpkSztTAI_Broadcast
*  DESC: Function to Unpack SztTAI_Broadcast structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztTAI_Broadcast
(
SztTAI_Broadcast *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztTAI_Broadcast(param, ptr, mBuf)
SztTAI_Broadcast *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztTAI_Broadcast) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztTAI_Broadcast_Item)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztTAI_Broadcast_Item, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztTAI_Broadcast */



/*
* FUN : cmUnpkSzt_ExtnCompletedCellinEAI_Item_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnCompletedCellinEAI_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnCompletedCellinEAI_Item_ExtIEsCls
(
Szt_ExtnCompletedCellinEAI_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnCompletedCellinEAI_Item_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnCompletedCellinEAI_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnCompletedCellinEAI_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnCompletedCellinEAI_Item_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_CompletedCellinEAI_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_CompletedCellinEAI_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_CompletedCellinEAI_Item_ExtIEs
(
SztProtExtnField_CompletedCellinEAI_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_CompletedCellinEAI_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnField_CompletedCellinEAI_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_CompletedCellinEAI_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnCompletedCellinEAI_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_CompletedCellinEAI_Item_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_CompletedCellinEAI_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_CompletedCellinEAI_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_CompletedCellinEAI_Item_ExtIEs
(
SztProtExtnCont_CompletedCellinEAI_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_CompletedCellinEAI_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_CompletedCellinEAI_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_CompletedCellinEAI_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_CompletedCellinEAI_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_CompletedCellinEAI_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_CompletedCellinEAI_Item_ExtIEs */



/*
* FUN : cmUnpkSztCompletedCellinEAI_Item
*  DESC: Function to Unpack SztCompletedCellinEAI_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztCompletedCellinEAI_Item
(
SztCompletedCellinEAI_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztCompletedCellinEAI_Item(param, ptr, mBuf)
SztCompletedCellinEAI_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztCompletedCellinEAI_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztEUTRAN_CGI, &param->eCGI, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_CompletedCellinEAI_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztCompletedCellinEAI_Item */



/*
* FUN : cmUnpkSztCompletedCellinEAI
*  DESC: Function to Unpack SztCompletedCellinEAI structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztCompletedCellinEAI
(
SztCompletedCellinEAI *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztCompletedCellinEAI(param, ptr, mBuf)
SztCompletedCellinEAI *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztCompletedCellinEAI) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztCompletedCellinEAI_Item)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztCompletedCellinEAI_Item, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztCompletedCellinEAI */



/*
* FUN : cmUnpkSzt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls
(
Szt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs
(
SztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnEmergencyAreaID_Broadcast_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs
(
SztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_EmergencyAreaID_Broadcast_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs */



/*
* FUN : cmUnpkSztEmergencyAreaID_Broadcast_Item
*  DESC: Function to Unpack SztEmergencyAreaID_Broadcast_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztEmergencyAreaID_Broadcast_Item
(
SztEmergencyAreaID_Broadcast_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztEmergencyAreaID_Broadcast_Item(param, ptr, mBuf)
SztEmergencyAreaID_Broadcast_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztEmergencyAreaID_Broadcast_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		SZUCHKUNPKPTR(cmUnpkSztEmergencyAreaID, &param->emergencyAreaID, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztCompletedCellinEAI, &param->completedCellinEAI, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_EmergencyAreaID_Broadcast_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztEmergencyAreaID_Broadcast_Item */



/*
* FUN : cmUnpkSztEmergencyAreaID_Broadcast
*  DESC: Function to Unpack SztEmergencyAreaID_Broadcast structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztEmergencyAreaID_Broadcast
(
SztEmergencyAreaID_Broadcast *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztEmergencyAreaID_Broadcast(param, ptr, mBuf)
SztEmergencyAreaID_Broadcast *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztEmergencyAreaID_Broadcast) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztEmergencyAreaID_Broadcast_Item)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztEmergencyAreaID_Broadcast_Item, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztEmergencyAreaID_Broadcast */



/*
* FUN : cmUnpkSztBroadcastCompletedAreaLst
*  DESC: Function to Unpack SztBroadcastCompletedAreaLst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztBroadcastCompletedAreaLst
(
SztBroadcastCompletedAreaLst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztBroadcastCompletedAreaLst(param, ptr, mBuf)
SztBroadcastCompletedAreaLst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztBroadcastCompletedAreaLst) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case BROADCASTCOMPLETEDAREALST_CELLID_BROADCAST :
				CMCHKUNPKPTR(cmUnpkSztCellID_Broadcast, &param->val.cellID_Broadcast, ptr, mBuf); 
				break;
			case BROADCASTCOMPLETEDAREALST_TAI_BROADCAST :
				CMCHKUNPKPTR(cmUnpkSztTAI_Broadcast, &param->val.tAI_Broadcast, ptr, mBuf); 
				break;
			case BROADCASTCOMPLETEDAREALST_EMERGENCYAREAID_BROADCAST :
				CMCHKUNPKPTR(cmUnpkSztEmergencyAreaID_Broadcast, &param->val.emergencyAreaID_Broadcast, ptr, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztBroadcastCompletedAreaLst */

#define cmUnpkSztCauseRadioNw cmUnpkTknU32

#define cmUnpkSztCauseTport cmUnpkTknU32

#define cmUnpkSztCauseNas cmUnpkTknU32

#define cmUnpkSztCauseProt cmUnpkTknU32

#define cmUnpkSztCauseMisc cmUnpkTknU32



/*
* FUN : cmUnpkSztCause
*  DESC: Function to Unpack SztCause structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztCause
(
SztCause *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztCause(param, ptr, mBuf)
SztCause *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztCause) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case CAUSE_RADIONW :
				CMCHKUNPK(cmUnpkSztCauseRadioNw, &param->val.radioNw, mBuf); 
				break;
			case CAUSE_TRANSPORT :
				CMCHKUNPK(cmUnpkSztCauseTport, &param->val.transport, mBuf); 
				break;
			case CAUSE_NAS :
				CMCHKUNPK(cmUnpkSztCauseNas, &param->val.nas, mBuf); 
				break;
			case CAUSE_PROTOCOL :
				CMCHKUNPK(cmUnpkSztCauseProt, &param->val.protocol, mBuf); 
				break;
			case CAUSE_MISC :
				CMCHKUNPK(cmUnpkSztCauseMisc, &param->val.misc, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztCause */

#define cmUnpkSztCellAccessMode cmUnpkTknU32

#define cmUnpkSztCdma2000PDU cmUnpkTknStrOSXL 
#define cmUnpkSztCdma2000RATTyp cmUnpkTknU32

#define cmUnpkSztCdma2000SectorID cmUnpkTknStrOSXL 
#define cmUnpkSztCdma2000HOStatus cmUnpkTknU32

#define cmUnpkSztCdma2000HOReqdInd cmUnpkTknU32

#define cmUnpkSztCdma2000OneXMEID cmUnpkTknStrOSXL 
#define cmUnpkSztCdma2000OneXMSI cmUnpkTknStrOSXL 
#define cmUnpkSztCdma2000OneXPilot cmUnpkTknStrOSXL 


/*
* FUN : cmUnpkSzt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls
(
Szt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs
(
SztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs(param, ptr, mBuf)
SztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnCdma2000OneXSRVCCInfo_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs
(
SztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_Cdma2000OneXSRVCCInfo_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs */



/*
* FUN : cmUnpkSztCdma2000OneXSRVCCInfo
*  DESC: Function to Unpack SztCdma2000OneXSRVCCInfo structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztCdma2000OneXSRVCCInfo
(
SztCdma2000OneXSRVCCInfo *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztCdma2000OneXSRVCCInfo(param, ptr, mBuf)
SztCdma2000OneXSRVCCInfo *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztCdma2000OneXSRVCCInfo) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		SZUCHKUNPKPTR(cmUnpkSztCdma2000OneXMEID, &param->cdma2000OneXMEID, ptr, mBuf); 
		SZUCHKUNPKPTR(cmUnpkSztCdma2000OneXMSI, &param->cdma2000OneXMSI, ptr, mBuf); 
		SZUCHKUNPKPTR(cmUnpkSztCdma2000OneXPilot, &param->cdma2000OneXPilot, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_Cdma2000OneXSRVCCInfo_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztCdma2000OneXSRVCCInfo */

#define cmUnpkSztCdma2000OneXRAND cmUnpkTknStrOSXL 
#define cmUnpkSztCell_Size cmUnpkTknU32



/*
* FUN : cmUnpkSzt_ExtnCellTyp_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnCellTyp_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnCellTyp_ExtIEsCls
(
Szt_ExtnCellTyp_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnCellTyp_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnCellTyp_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnCellTyp_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnCellTyp_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_CellTyp_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_CellTyp_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_CellTyp_ExtIEs
(
SztProtExtnField_CellTyp_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_CellTyp_ExtIEs(param, ptr, mBuf)
SztProtExtnField_CellTyp_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_CellTyp_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnCellTyp_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_CellTyp_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_CellTyp_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_CellTyp_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_CellTyp_ExtIEs
(
SztProtExtnCont_CellTyp_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_CellTyp_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_CellTyp_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_CellTyp_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_CellTyp_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_CellTyp_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_CellTyp_ExtIEs */



/*
* FUN : cmUnpkSztCellTyp
*  DESC: Function to Unpack SztCellTyp structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztCellTyp
(
SztCellTyp *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztCellTyp(param, ptr, mBuf)
SztCellTyp *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztCellTyp) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztCell_Size, &param->cell_Size, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_CellTyp_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztCellTyp */

#define cmUnpkSztLAC cmUnpkTknStr4 
#define cmUnpkSztCI cmUnpkTknStr4 
#define cmUnpkSztRAC cmUnpkTknStr4 


/*
* FUN : cmUnpkSzt_ExtnCGI_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnCGI_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnCGI_ExtIEsCls
(
Szt_ExtnCGI_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnCGI_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnCGI_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnCGI_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnCGI_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_CGI_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_CGI_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_CGI_ExtIEs
(
SztProtExtnField_CGI_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_CGI_ExtIEs(param, ptr, mBuf)
SztProtExtnField_CGI_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_CGI_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnCGI_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_CGI_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_CGI_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_CGI_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_CGI_ExtIEs
(
SztProtExtnCont_CGI_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_CGI_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_CGI_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_CGI_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_CGI_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_CGI_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_CGI_ExtIEs */



/*
* FUN : cmUnpkSztCGI
*  DESC: Function to Unpack SztCGI structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztCGI
(
SztCGI *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztCGI(param, ptr, mBuf)
SztCGI *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztCGI) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		SZUCHKUNPKPTR(cmUnpkSztPLMNidentity, &param->pLMNidentity, ptr, mBuf); 
		CMCHKUNPK(cmUnpkSztLAC, &param->lAC, mBuf); 
		CMCHKUNPK(cmUnpkSztCI, &param->cI, mBuf); 
		CMCHKUNPK(cmUnpkSztRAC, &param->rAC, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_CGI_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztCGI */

#define cmUnpkSztCNDomain cmUnpkTknU32

#define cmUnpkSztConcurrentWarningMsgIndicator cmUnpkTknU32

#define cmUnpkSztCorrelation_ID cmUnpkTknStrOSXL 
#define cmUnpkSztCSFallbackIndicator cmUnpkTknU32

#define cmUnpkSztCSG_Id cmUnpkTknBStr32 


/*
* FUN : cmUnpkSzt_ExtnCSG_IdLst_Item_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnCSG_IdLst_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnCSG_IdLst_Item_ExtIEsCls
(
Szt_ExtnCSG_IdLst_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnCSG_IdLst_Item_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnCSG_IdLst_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnCSG_IdLst_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnCSG_IdLst_Item_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_CSG_IdLst_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_CSG_IdLst_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_CSG_IdLst_Item_ExtIEs
(
SztProtExtnField_CSG_IdLst_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_CSG_IdLst_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnField_CSG_IdLst_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_CSG_IdLst_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnCSG_IdLst_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_CSG_IdLst_Item_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_CSG_IdLst_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_CSG_IdLst_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_CSG_IdLst_Item_ExtIEs
(
SztProtExtnCont_CSG_IdLst_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_CSG_IdLst_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_CSG_IdLst_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_CSG_IdLst_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_CSG_IdLst_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_CSG_IdLst_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_CSG_IdLst_Item_ExtIEs */



/*
* FUN : cmUnpkSztCSG_IdLst_Item
*  DESC: Function to Unpack SztCSG_IdLst_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztCSG_IdLst_Item
(
SztCSG_IdLst_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztCSG_IdLst_Item(param, ptr, mBuf)
SztCSG_IdLst_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztCSG_IdLst_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztCSG_Id, &param->cSG_Id, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_CSG_IdLst_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztCSG_IdLst_Item */



/*
* FUN : cmUnpkSztCSG_IdLst
*  DESC: Function to Unpack SztCSG_IdLst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztCSG_IdLst
(
SztCSG_IdLst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztCSG_IdLst(param, ptr, mBuf)
SztCSG_IdLst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztCSG_IdLst) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztCSG_IdLst_Item)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztCSG_IdLst_Item, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztCSG_IdLst */

#define cmUnpkSztCSGMembershipStatus cmUnpkTknU32

#define cmUnpkSztTypOfErr cmUnpkTknU32



/*
* FUN : cmUnpkSzt_ExtnCriticalityDiag_IE_Item_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnCriticalityDiag_IE_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnCriticalityDiag_IE_Item_ExtIEsCls
(
Szt_ExtnCriticalityDiag_IE_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnCriticalityDiag_IE_Item_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnCriticalityDiag_IE_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnCriticalityDiag_IE_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnCriticalityDiag_IE_Item_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_CriticalityDiag_IE_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_CriticalityDiag_IE_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_CriticalityDiag_IE_Item_ExtIEs
(
SztProtExtnField_CriticalityDiag_IE_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_CriticalityDiag_IE_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnField_CriticalityDiag_IE_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_CriticalityDiag_IE_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnCriticalityDiag_IE_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_CriticalityDiag_IE_Item_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs
(
SztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_CriticalityDiag_IE_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_CriticalityDiag_IE_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs */



/*
* FUN : cmUnpkSztCriticalityDiag_IE_Item
*  DESC: Function to Unpack SztCriticalityDiag_IE_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztCriticalityDiag_IE_Item
(
SztCriticalityDiag_IE_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztCriticalityDiag_IE_Item(param, ptr, mBuf)
SztCriticalityDiag_IE_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztCriticalityDiag_IE_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztCriticality, &param->iECriticality, mBuf); 
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->iE_ID, mBuf); 
		CMCHKUNPK(cmUnpkSztTypOfErr, &param->typeOfErr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_CriticalityDiag_IE_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztCriticalityDiag_IE_Item */



/*
* FUN : cmUnpkSztCriticalityDiag_IE_Lst
*  DESC: Function to Unpack SztCriticalityDiag_IE_Lst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztCriticalityDiag_IE_Lst
(
SztCriticalityDiag_IE_Lst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztCriticalityDiag_IE_Lst(param, ptr, mBuf)
SztCriticalityDiag_IE_Lst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztCriticalityDiag_IE_Lst) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztCriticalityDiag_IE_Item)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztCriticalityDiag_IE_Item, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztCriticalityDiag_IE_Lst */



/*
* FUN : cmUnpkSzt_ExtnCriticalityDiag_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnCriticalityDiag_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnCriticalityDiag_ExtIEsCls
(
Szt_ExtnCriticalityDiag_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnCriticalityDiag_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnCriticalityDiag_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnCriticalityDiag_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnCriticalityDiag_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_CriticalityDiag_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_CriticalityDiag_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_CriticalityDiag_ExtIEs
(
SztProtExtnField_CriticalityDiag_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_CriticalityDiag_ExtIEs(param, ptr, mBuf)
SztProtExtnField_CriticalityDiag_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_CriticalityDiag_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnCriticalityDiag_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_CriticalityDiag_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_CriticalityDiag_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_CriticalityDiag_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_CriticalityDiag_ExtIEs
(
SztProtExtnCont_CriticalityDiag_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_CriticalityDiag_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_CriticalityDiag_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_CriticalityDiag_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_CriticalityDiag_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_CriticalityDiag_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_CriticalityDiag_ExtIEs */



/*
* FUN : cmUnpkSztCriticalityDiag
*  DESC: Function to Unpack SztCriticalityDiag structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztCriticalityDiag
(
SztCriticalityDiag *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztCriticalityDiag(param, ptr, mBuf)
SztCriticalityDiag *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztCriticalityDiag) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProcedureCode, &param->procedureCode, mBuf); 
		CMCHKUNPK(cmUnpkSztTrgMsg, &param->triggeringMsg, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->procedureCriticality, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztCriticalityDiag_IE_Lst, &param->iEsCriticalityDiag, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_CriticalityDiag_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztCriticalityDiag */

#define cmUnpkSztDataCodingScheme cmUnpkTknBStr32 
#define cmUnpkSztDL_Fwding cmUnpkTknU32

#define cmUnpkSztDirect_Fwding_Path_Avlblty cmUnpkTknU32

#define cmUnpkSztData_Fwding_Not_Possible cmUnpkTknU32



/*
* FUN : cmUnpkSztECGILst
*  DESC: Function to Unpack SztECGILst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztECGILst
(
SztECGILst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztECGILst(param, ptr, mBuf)
SztECGILst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztECGILst) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztEUTRAN_CGI)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztEUTRAN_CGI, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztECGILst */



/*
* FUN : cmUnpkSztEmergencyAreaIDLst
*  DESC: Function to Unpack SztEmergencyAreaIDLst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztEmergencyAreaIDLst
(
SztEmergencyAreaIDLst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztEmergencyAreaIDLst(param, ptr, mBuf)
SztEmergencyAreaIDLst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztEmergencyAreaIDLst) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztEmergencyAreaID)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			SZUCHKUNPKPTR(cmUnpkSztEmergencyAreaID, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztEmergencyAreaIDLst */

#define cmUnpkSztENB_IDmacroENB_ID cmUnpkTknBStr32 
#define cmUnpkSztENB_IDhomeENB_ID cmUnpkTknBStr32 


/*
* FUN : cmUnpkSztENB_ID
*  DESC: Function to Unpack SztENB_ID structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztENB_ID
(
SztENB_ID *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztENB_ID(param, ptr, mBuf)
SztENB_ID *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztENB_ID) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case ENB_ID_MACROENB_ID :
				CMCHKUNPK(cmUnpkSztENB_IDmacroENB_ID, &param->val.macroENB_ID, mBuf); 
				break;
			case ENB_ID_HOMEENB_ID :
				CMCHKUNPK(cmUnpkSztENB_IDhomeENB_ID, &param->val.homeENB_ID, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztENB_ID */



/*
* FUN : cmUnpkSzt_ExtnLAI_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnLAI_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnLAI_ExtIEsCls
(
Szt_ExtnLAI_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnLAI_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnLAI_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnLAI_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnLAI_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_LAI_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_LAI_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_LAI_ExtIEs
(
SztProtExtnField_LAI_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_LAI_ExtIEs(param, ptr, mBuf)
SztProtExtnField_LAI_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_LAI_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnLAI_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_LAI_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_LAI_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_LAI_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_LAI_ExtIEs
(
SztProtExtnCont_LAI_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_LAI_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_LAI_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_LAI_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_LAI_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_LAI_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_LAI_ExtIEs */



/*
* FUN : cmUnpkSztLAI
*  DESC: Function to Unpack SztLAI structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztLAI
(
SztLAI *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztLAI(param, ptr, mBuf)
SztLAI *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztLAI) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		SZUCHKUNPKPTR(cmUnpkSztPLMNidentity, &param->pLMNidentity, ptr, mBuf); 
		CMCHKUNPK(cmUnpkSztLAC, &param->lAC, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_LAI_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztLAI */



/*
* FUN : cmUnpkSzt_ExtnGERAN_Cell_ID_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnGERAN_Cell_ID_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnGERAN_Cell_ID_ExtIEsCls
(
Szt_ExtnGERAN_Cell_ID_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnGERAN_Cell_ID_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnGERAN_Cell_ID_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnGERAN_Cell_ID_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnGERAN_Cell_ID_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_GERAN_Cell_ID_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_GERAN_Cell_ID_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_GERAN_Cell_ID_ExtIEs
(
SztProtExtnField_GERAN_Cell_ID_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_GERAN_Cell_ID_ExtIEs(param, ptr, mBuf)
SztProtExtnField_GERAN_Cell_ID_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_GERAN_Cell_ID_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnGERAN_Cell_ID_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_GERAN_Cell_ID_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_GERAN_Cell_ID_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_GERAN_Cell_ID_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_GERAN_Cell_ID_ExtIEs
(
SztProtExtnCont_GERAN_Cell_ID_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_GERAN_Cell_ID_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_GERAN_Cell_ID_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_GERAN_Cell_ID_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_GERAN_Cell_ID_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_GERAN_Cell_ID_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_GERAN_Cell_ID_ExtIEs */



/*
* FUN : cmUnpkSztGERAN_Cell_ID
*  DESC: Function to Unpack SztGERAN_Cell_ID structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztGERAN_Cell_ID
(
SztGERAN_Cell_ID *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztGERAN_Cell_ID(param, ptr, mBuf)
SztGERAN_Cell_ID *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztGERAN_Cell_ID) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztLAI, &param->lAI, ptr, mBuf); 
		CMCHKUNPK(cmUnpkSztRAC, &param->rAC, mBuf); 
		CMCHKUNPK(cmUnpkSztCI, &param->cI, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_GERAN_Cell_ID_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztGERAN_Cell_ID */



/*
* FUN : cmUnpkSzt_ExtnGlobalENB_ID_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnGlobalENB_ID_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnGlobalENB_ID_ExtIEsCls
(
Szt_ExtnGlobalENB_ID_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnGlobalENB_ID_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnGlobalENB_ID_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnGlobalENB_ID_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnGlobalENB_ID_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_GlobalENB_ID_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_GlobalENB_ID_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_GlobalENB_ID_ExtIEs
(
SztProtExtnField_GlobalENB_ID_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_GlobalENB_ID_ExtIEs(param, ptr, mBuf)
SztProtExtnField_GlobalENB_ID_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_GlobalENB_ID_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnGlobalENB_ID_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_GlobalENB_ID_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_GlobalENB_ID_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_GlobalENB_ID_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_GlobalENB_ID_ExtIEs
(
SztProtExtnCont_GlobalENB_ID_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_GlobalENB_ID_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_GlobalENB_ID_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_GlobalENB_ID_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_GlobalENB_ID_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_GlobalENB_ID_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_GlobalENB_ID_ExtIEs */



/*
* FUN : cmUnpkSztGlobal_ENB_ID
*  DESC: Function to Unpack SztGlobal_ENB_ID structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztGlobal_ENB_ID
(
SztGlobal_ENB_ID *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztGlobal_ENB_ID(param, ptr, mBuf)
SztGlobal_ENB_ID *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztGlobal_ENB_ID) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		SZUCHKUNPKPTR(cmUnpkSztPLMNidentity, &param->pLMNidentity, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztENB_ID, &param->eNB_ID, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_GlobalENB_ID_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztGlobal_ENB_ID */

#define cmUnpkSztMME_Group_ID cmUnpkTknStr4 
#define cmUnpkSztMME_Code cmUnpkTknStr4 


/*
* FUN : cmUnpkSzt_ExtnGUMMEI_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnGUMMEI_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnGUMMEI_ExtIEsCls
(
Szt_ExtnGUMMEI_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnGUMMEI_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnGUMMEI_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnGUMMEI_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnGUMMEI_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_GUMMEI_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_GUMMEI_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_GUMMEI_ExtIEs
(
SztProtExtnField_GUMMEI_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_GUMMEI_ExtIEs(param, ptr, mBuf)
SztProtExtnField_GUMMEI_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_GUMMEI_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnGUMMEI_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_GUMMEI_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_GUMMEI_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_GUMMEI_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_GUMMEI_ExtIEs
(
SztProtExtnCont_GUMMEI_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_GUMMEI_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_GUMMEI_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_GUMMEI_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_GUMMEI_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_GUMMEI_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_GUMMEI_ExtIEs */



/*
* FUN : cmUnpkSztGUMMEI
*  DESC: Function to Unpack SztGUMMEI structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztGUMMEI
(
SztGUMMEI *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztGUMMEI(param, ptr, mBuf)
SztGUMMEI *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztGUMMEI) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		SZUCHKUNPKPTR(cmUnpkSztPLMNidentity, &param->pLMN_Identity, ptr, mBuf); 
		CMCHKUNPK(cmUnpkSztMME_Group_ID, &param->mME_Group_ID, mBuf); 
		CMCHKUNPK(cmUnpkSztMME_Code, &param->mME_Code, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_GUMMEI_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztGUMMEI */



/*
* FUN : cmUnpkSztGUMMEILst
*  DESC: Function to Unpack SztGUMMEILst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztGUMMEILst
(
SztGUMMEILst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztGUMMEILst(param, ptr, mBuf)
SztGUMMEILst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztGUMMEILst) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztGUMMEI)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztGUMMEI, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztGUMMEILst */



/*
* FUN : cmUnpkSzt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls
(
Szt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs
(
SztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs(param, ptr, mBuf)
SztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnENB_StatusTfr_TprntCont_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs
(
SztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_ENB_StatusTfr_TprntCont_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs */



/*
* FUN : cmUnpkSztENB_StatusTfr_TprntCont
*  DESC: Function to Unpack SztENB_StatusTfr_TprntCont structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztENB_StatusTfr_TprntCont
(
SztENB_StatusTfr_TprntCont *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztENB_StatusTfr_TprntCont(param, ptr, mBuf)
SztENB_StatusTfr_TprntCont *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztENB_StatusTfr_TprntCont) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztBrs_SubjToStatusTfrLst, &param->bearers_SubjToStatusTfrLst, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_ENB_StatusTfr_TprntCont_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztENB_StatusTfr_TprntCont */

#define cmUnpkSztENB_UE_S1AP_ID cmUnpkTknU32 
#define cmUnpkSztENBname cmUnpkTknStrOSXL 
#define cmUnpkSztTportLyrAddr cmUnpkTknStrBSXL 


/*
* FUN : cmUnpkSztENBX2TLAs
*  DESC: Function to Unpack SztENBX2TLAs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztENBX2TLAs
(
SztENBX2TLAs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztENBX2TLAs(param, ptr, mBuf)
SztENBX2TLAs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztENBX2TLAs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztTportLyrAddr)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztTportLyrAddr, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztENBX2TLAs */

#define cmUnpkSztEncryptionAlgorithms cmUnpkTknBStr32 


/*
* FUN : cmUnpkSztEPLMNs
*  DESC: Function to Unpack SztEPLMNs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztEPLMNs
(
SztEPLMNs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztEPLMNs(param, ptr, mBuf)
SztEPLMNs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztEPLMNs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztPLMNidentity)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			SZUCHKUNPKPTR(cmUnpkSztTBCD_STRING, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztEPLMNs */

#define cmUnpkSztEventTyp cmUnpkTknU32



/*
* FUN : cmUnpkSzt_ExtnE_RABInformLstItem_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnE_RABInformLstItem_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnE_RABInformLstItem_ExtIEsCls
(
Szt_ExtnE_RABInformLstItem_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnE_RABInformLstItem_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnE_RABInformLstItem_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnE_RABInformLstItem_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnE_RABInformLstItem_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_E_RABInformLstItem_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_E_RABInformLstItem_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABInformLstItem_ExtIEs
(
SztProtExtnField_E_RABInformLstItem_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABInformLstItem_ExtIEs(param, ptr, mBuf)
SztProtExtnField_E_RABInformLstItem_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_E_RABInformLstItem_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnE_RABInformLstItem_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_E_RABInformLstItem_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_E_RABInformLstItem_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_E_RABInformLstItem_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABInformLstItem_ExtIEs
(
SztProtExtnCont_E_RABInformLstItem_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABInformLstItem_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_E_RABInformLstItem_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_E_RABInformLstItem_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_E_RABInformLstItem_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_E_RABInformLstItem_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_E_RABInformLstItem_ExtIEs */



/*
* FUN : cmUnpkSztE_RABInformLstItem
*  DESC: Function to Unpack SztE_RABInformLstItem structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABInformLstItem
(
SztE_RABInformLstItem *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABInformLstItem(param, ptr, mBuf)
SztE_RABInformLstItem *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztE_RABInformLstItem) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
		CMCHKUNPK(cmUnpkSztDL_Fwding, &param->dL_Fwding, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_E_RABInformLstItem_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztE_RABInformLstItem */



/*
* FUN : cmUnpkSzt_ValueE_RABInformLstIEsCls
*  DESC: Function to Unpack Szt_ValueE_RABInformLstIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueE_RABInformLstIEsCls
(
Szt_ValueE_RABInformLstIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueE_RABInformLstIEsCls(param, val, ptr, mBuf)
Szt_ValueE_RABInformLstIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueE_RABInformLstIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABInformLstItem:
			CMCHKUNPKPTR(cmUnpkSztE_RABInformLstItem, &param->u.sztE_RABInformLstItem, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueE_RABInformLstIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_E_RABInformLstIEs
*  DESC: Function to Unpack SztProtIE_Field_E_RABInformLstIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABInformLstIEs
(
SztProtIE_Field_E_RABInformLstIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABInformLstIEs(param, ptr, mBuf)
SztProtIE_Field_E_RABInformLstIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_E_RABInformLstIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueE_RABInformLstIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_E_RABInformLstIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmUnpkSztProtIE_SingleCont_E_RABInformLstIEs cmUnpkSztProtIE_Field_E_RABInformLstIEs


/*
* FUN : cmUnpkSztE_RABInformLst
*  DESC: Function to Unpack SztE_RABInformLst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABInformLst
(
SztE_RABInformLst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABInformLst(param, ptr, mBuf)
SztE_RABInformLst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztE_RABInformLst) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_SingleCont_E_RABInformLstIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_SingleCont_E_RABInformLstIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztE_RABInformLst */



/*
* FUN : cmUnpkSzt_ExtnE_RABItem_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnE_RABItem_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnE_RABItem_ExtIEsCls
(
Szt_ExtnE_RABItem_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnE_RABItem_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnE_RABItem_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnE_RABItem_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnE_RABItem_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_E_RABItem_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_E_RABItem_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABItem_ExtIEs
(
SztProtExtnField_E_RABItem_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABItem_ExtIEs(param, ptr, mBuf)
SztProtExtnField_E_RABItem_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_E_RABItem_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnE_RABItem_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_E_RABItem_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_E_RABItem_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_E_RABItem_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABItem_ExtIEs
(
SztProtExtnCont_E_RABItem_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABItem_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_E_RABItem_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_E_RABItem_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_E_RABItem_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_E_RABItem_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_E_RABItem_ExtIEs */



/*
* FUN : cmUnpkSztE_RABItem
*  DESC: Function to Unpack SztE_RABItem structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABItem
(
SztE_RABItem *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABItem(param, ptr, mBuf)
SztE_RABItem *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztE_RABItem) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztCause, &param->cause, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_E_RABItem_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztE_RABItem */



/*
* FUN : cmUnpkSzt_ValueE_RABItemIEsCls
*  DESC: Function to Unpack Szt_ValueE_RABItemIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueE_RABItemIEsCls
(
Szt_ValueE_RABItemIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueE_RABItemIEsCls(param, val, ptr, mBuf)
Szt_ValueE_RABItemIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueE_RABItemIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABItem:
			CMCHKUNPKPTR(cmUnpkSztE_RABItem, &param->u.sztE_RABItem, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueE_RABItemIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_E_RABItemIEs
*  DESC: Function to Unpack SztProtIE_Field_E_RABItemIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABItemIEs
(
SztProtIE_Field_E_RABItemIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABItemIEs(param, ptr, mBuf)
SztProtIE_Field_E_RABItemIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_E_RABItemIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueE_RABItemIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_E_RABItemIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmUnpkSztProtIE_SingleCont_E_RABItemIEs cmUnpkSztProtIE_Field_E_RABItemIEs


/*
* FUN : cmUnpkSztE_RABLst
*  DESC: Function to Unpack SztE_RABLst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABLst
(
SztE_RABLst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABLst(param, ptr, mBuf)
SztE_RABLst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztE_RABLst) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_SingleCont_E_RABItemIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_SingleCont_E_RABItemIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztE_RABLst */

#define cmUnpkSztQCI cmUnpkTknU32 


/*
* FUN : cmUnpkSzt_ExtnGBR_QosInform_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnGBR_QosInform_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnGBR_QosInform_ExtIEsCls
(
Szt_ExtnGBR_QosInform_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnGBR_QosInform_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnGBR_QosInform_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnGBR_QosInform_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnGBR_QosInform_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_GBR_QosInform_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_GBR_QosInform_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_GBR_QosInform_ExtIEs
(
SztProtExtnField_GBR_QosInform_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_GBR_QosInform_ExtIEs(param, ptr, mBuf)
SztProtExtnField_GBR_QosInform_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_GBR_QosInform_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnGBR_QosInform_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_GBR_QosInform_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_GBR_QosInform_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_GBR_QosInform_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_GBR_QosInform_ExtIEs
(
SztProtExtnCont_GBR_QosInform_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_GBR_QosInform_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_GBR_QosInform_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_GBR_QosInform_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_GBR_QosInform_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_GBR_QosInform_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_GBR_QosInform_ExtIEs */



/*
* FUN : cmUnpkSztGBR_QosInform
*  DESC: Function to Unpack SztGBR_QosInform structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztGBR_QosInform
(
SztGBR_QosInform *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztGBR_QosInform(param, ptr, mBuf)
SztGBR_QosInform *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztGBR_QosInform) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		SZUCHKUNPKPTR(cmUnpkSztBitRate, &param->e_RAB_MaxBitrateDL, ptr, mBuf); 
		SZUCHKUNPKPTR(cmUnpkSztBitRate, &param->e_RAB_MaxBitrateUL, ptr, mBuf); 
		SZUCHKUNPKPTR(cmUnpkSztBitRate, &param->e_RAB_GuaranteedBitrateDL, ptr, mBuf); 
		SZUCHKUNPKPTR(cmUnpkSztBitRate, &param->e_RAB_GuaranteedBitrateUL, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_GBR_QosInform_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztGBR_QosInform */



/*
* FUN : cmUnpkSzt_ExtnE_RABQoSParams_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnE_RABQoSParams_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnE_RABQoSParams_ExtIEsCls
(
Szt_ExtnE_RABQoSParams_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnE_RABQoSParams_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnE_RABQoSParams_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnE_RABQoSParams_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnE_RABQoSParams_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_E_RABQoSParams_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_E_RABQoSParams_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABQoSParams_ExtIEs
(
SztProtExtnField_E_RABQoSParams_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABQoSParams_ExtIEs(param, ptr, mBuf)
SztProtExtnField_E_RABQoSParams_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_E_RABQoSParams_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnE_RABQoSParams_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_E_RABQoSParams_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_E_RABQoSParams_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_E_RABQoSParams_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABQoSParams_ExtIEs
(
SztProtExtnCont_E_RABQoSParams_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABQoSParams_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_E_RABQoSParams_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_E_RABQoSParams_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_E_RABQoSParams_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_E_RABQoSParams_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_E_RABQoSParams_ExtIEs */



/*
* FUN : cmUnpkSztE_RABLvlQoSParams
*  DESC: Function to Unpack SztE_RABLvlQoSParams structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABLvlQoSParams
(
SztE_RABLvlQoSParams *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABLvlQoSParams(param, ptr, mBuf)
SztE_RABLvlQoSParams *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztE_RABLvlQoSParams) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztQCI, &param->qCI, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztAllocnAndRetentionPriority, &param->allocationRetentionPriority, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztGBR_QosInform, &param->gbrQosInform, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_E_RABQoSParams_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztE_RABLvlQoSParams */

#define cmUnpkSztEUTRANRoundTripDelayEstimationInfo cmUnpkTknU32 
#define cmUnpkSztExtendedRNC_ID cmUnpkTknU32 
#define cmUnpkSztExtendedRepetitionPeriod cmUnpkTknU32 
#define cmUnpkSztForbiddenInterRATs cmUnpkTknU32



/*
* FUN : cmUnpkSztForbiddenTACs
*  DESC: Function to Unpack SztForbiddenTACs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztForbiddenTACs
(
SztForbiddenTACs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztForbiddenTACs(param, ptr, mBuf)
SztForbiddenTACs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztForbiddenTACs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztTAC)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPK(cmUnpkSztTAC, &(param->member[i]), mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztForbiddenTACs */



/*
* FUN : cmUnpkSzt_ExtnForbiddenTAs_Item_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnForbiddenTAs_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnForbiddenTAs_Item_ExtIEsCls
(
Szt_ExtnForbiddenTAs_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnForbiddenTAs_Item_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnForbiddenTAs_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnForbiddenTAs_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnForbiddenTAs_Item_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_ForbiddenTAs_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_ForbiddenTAs_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_ForbiddenTAs_Item_ExtIEs
(
SztProtExtnField_ForbiddenTAs_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_ForbiddenTAs_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnField_ForbiddenTAs_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_ForbiddenTAs_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnForbiddenTAs_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_ForbiddenTAs_Item_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_ForbiddenTAs_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_ForbiddenTAs_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_ForbiddenTAs_Item_ExtIEs
(
SztProtExtnCont_ForbiddenTAs_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_ForbiddenTAs_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_ForbiddenTAs_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_ForbiddenTAs_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_ForbiddenTAs_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_ForbiddenTAs_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_ForbiddenTAs_Item_ExtIEs */



/*
* FUN : cmUnpkSztForbiddenTAs_Item
*  DESC: Function to Unpack SztForbiddenTAs_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztForbiddenTAs_Item
(
SztForbiddenTAs_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztForbiddenTAs_Item(param, ptr, mBuf)
SztForbiddenTAs_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztForbiddenTAs_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		SZUCHKUNPKPTR(cmUnpkSztPLMNidentity, &param->pLMN_Identity, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztForbiddenTACs, &param->forbiddenTACs, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_ForbiddenTAs_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztForbiddenTAs_Item */



/*
* FUN : cmUnpkSztForbiddenTAs
*  DESC: Function to Unpack SztForbiddenTAs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztForbiddenTAs
(
SztForbiddenTAs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztForbiddenTAs(param, ptr, mBuf)
SztForbiddenTAs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztForbiddenTAs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztForbiddenTAs_Item)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztForbiddenTAs_Item, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztForbiddenTAs */



/*
* FUN : cmUnpkSztForbiddenLACs
*  DESC: Function to Unpack SztForbiddenLACs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztForbiddenLACs
(
SztForbiddenLACs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztForbiddenLACs(param, ptr, mBuf)
SztForbiddenLACs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztForbiddenLACs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztLAC)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPK(cmUnpkSztLAC, &(param->member[i]), mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztForbiddenLACs */



/*
* FUN : cmUnpkSzt_ExtnForbiddenLAs_Item_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnForbiddenLAs_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnForbiddenLAs_Item_ExtIEsCls
(
Szt_ExtnForbiddenLAs_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnForbiddenLAs_Item_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnForbiddenLAs_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnForbiddenLAs_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnForbiddenLAs_Item_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_ForbiddenLAs_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_ForbiddenLAs_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_ForbiddenLAs_Item_ExtIEs
(
SztProtExtnField_ForbiddenLAs_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_ForbiddenLAs_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnField_ForbiddenLAs_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_ForbiddenLAs_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnForbiddenLAs_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_ForbiddenLAs_Item_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_ForbiddenLAs_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_ForbiddenLAs_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_ForbiddenLAs_Item_ExtIEs
(
SztProtExtnCont_ForbiddenLAs_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_ForbiddenLAs_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_ForbiddenLAs_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_ForbiddenLAs_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_ForbiddenLAs_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_ForbiddenLAs_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_ForbiddenLAs_Item_ExtIEs */



/*
* FUN : cmUnpkSztForbiddenLAs_Item
*  DESC: Function to Unpack SztForbiddenLAs_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztForbiddenLAs_Item
(
SztForbiddenLAs_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztForbiddenLAs_Item(param, ptr, mBuf)
SztForbiddenLAs_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztForbiddenLAs_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		SZUCHKUNPKPTR(cmUnpkSztPLMNidentity, &param->pLMN_Identity, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztForbiddenLACs, &param->forbiddenLACs, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_ForbiddenLAs_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztForbiddenLAs_Item */



/*
* FUN : cmUnpkSztForbiddenLAs
*  DESC: Function to Unpack SztForbiddenLAs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztForbiddenLAs
(
SztForbiddenLAs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztForbiddenLAs(param, ptr, mBuf)
SztForbiddenLAs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztForbiddenLAs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztForbiddenLAs_Item)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztForbiddenLAs_Item, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztForbiddenLAs */

#define cmUnpkSztGTP_TEID cmUnpkTknStrOSXL 
#define cmUnpkSztGUMMEITyp cmUnpkTknU32

#define cmUnpkSztGWCntxtRlsInd cmUnpkTknU32



/*
* FUN : cmUnpkSzt_ExtnHovrRestrnLst_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnHovrRestrnLst_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnHovrRestrnLst_ExtIEsCls
(
Szt_ExtnHovrRestrnLst_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnHovrRestrnLst_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnHovrRestrnLst_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnHovrRestrnLst_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnHovrRestrnLst_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_HovrRestrnLst_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_HovrRestrnLst_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_HovrRestrnLst_ExtIEs
(
SztProtExtnField_HovrRestrnLst_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_HovrRestrnLst_ExtIEs(param, ptr, mBuf)
SztProtExtnField_HovrRestrnLst_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_HovrRestrnLst_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnHovrRestrnLst_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_HovrRestrnLst_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_HovrRestrnLst_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_HovrRestrnLst_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_HovrRestrnLst_ExtIEs
(
SztProtExtnCont_HovrRestrnLst_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_HovrRestrnLst_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_HovrRestrnLst_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_HovrRestrnLst_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_HovrRestrnLst_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_HovrRestrnLst_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_HovrRestrnLst_ExtIEs */



/*
* FUN : cmUnpkSztHovrRestrnLst
*  DESC: Function to Unpack SztHovrRestrnLst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztHovrRestrnLst
(
SztHovrRestrnLst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztHovrRestrnLst(param, ptr, mBuf)
SztHovrRestrnLst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztHovrRestrnLst) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		SZUCHKUNPKPTR(cmUnpkSztPLMNidentity, &param->servingPLMN, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztEPLMNs, &param->equivalentPLMNs, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztForbiddenTAs, &param->forbiddenTAs, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztForbiddenLAs, &param->forbiddenLAs, ptr, mBuf); 
		CMCHKUNPK(cmUnpkSztForbiddenInterRATs, &param->forbiddenInterRATs, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_HovrRestrnLst_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztHovrRestrnLst */

#define cmUnpkSztHovrTyp cmUnpkTknU32

#define cmUnpkSztMeasurementsToActivate cmUnpkTknBStr32 
#define cmUnpkSztM1RprtngTrigger cmUnpkTknU32

#define cmUnpkSztThreshold_RSRP cmUnpkTknU32 
#define cmUnpkSztThreshold_RSRQ cmUnpkTknU32 


/*
* FUN : cmUnpkSztMeasurementThresholdA2
*  DESC: Function to Unpack SztMeasurementThresholdA2 structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztMeasurementThresholdA2
(
SztMeasurementThresholdA2 *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztMeasurementThresholdA2(param, ptr, mBuf)
SztMeasurementThresholdA2 *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztMeasurementThresholdA2) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case MEASUREMENTTHRESHOLDA2_THRESHOLD_RSRP :
				CMCHKUNPK(cmUnpkSztThreshold_RSRP, &param->val.threshold_RSRP, mBuf); 
				break;
			case MEASUREMENTTHRESHOLDA2_THRESHOLD_RSRQ :
				CMCHKUNPK(cmUnpkSztThreshold_RSRQ, &param->val.threshold_RSRQ, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztMeasurementThresholdA2 */



/*
* FUN : cmUnpkSzt_ExtnM1ThresholdEventA2_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnM1ThresholdEventA2_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnM1ThresholdEventA2_ExtIEsCls
(
Szt_ExtnM1ThresholdEventA2_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnM1ThresholdEventA2_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnM1ThresholdEventA2_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnM1ThresholdEventA2_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnM1ThresholdEventA2_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_M1ThresholdEventA2_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_M1ThresholdEventA2_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_M1ThresholdEventA2_ExtIEs
(
SztProtExtnField_M1ThresholdEventA2_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_M1ThresholdEventA2_ExtIEs(param, ptr, mBuf)
SztProtExtnField_M1ThresholdEventA2_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_M1ThresholdEventA2_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnM1ThresholdEventA2_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_M1ThresholdEventA2_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_M1ThresholdEventA2_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_M1ThresholdEventA2_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_M1ThresholdEventA2_ExtIEs
(
SztProtExtnCont_M1ThresholdEventA2_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_M1ThresholdEventA2_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_M1ThresholdEventA2_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_M1ThresholdEventA2_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_M1ThresholdEventA2_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_M1ThresholdEventA2_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_M1ThresholdEventA2_ExtIEs */



/*
* FUN : cmUnpkSztM1ThresholdEventA2
*  DESC: Function to Unpack SztM1ThresholdEventA2 structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztM1ThresholdEventA2
(
SztM1ThresholdEventA2 *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztM1ThresholdEventA2(param, ptr, mBuf)
SztM1ThresholdEventA2 *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztM1ThresholdEventA2) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztMeasurementThresholdA2, &param->measurementThreshold, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_M1ThresholdEventA2_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztM1ThresholdEventA2 */

#define cmUnpkSztReportIntervalMDT cmUnpkTknU32

#define cmUnpkSztReportAmountMDT cmUnpkTknU32



/*
* FUN : cmUnpkSzt_ExtnM1PeriodicRprtng_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnM1PeriodicRprtng_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnM1PeriodicRprtng_ExtIEsCls
(
Szt_ExtnM1PeriodicRprtng_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnM1PeriodicRprtng_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnM1PeriodicRprtng_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnM1PeriodicRprtng_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnM1PeriodicRprtng_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_M1PeriodicRprtng_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_M1PeriodicRprtng_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_M1PeriodicRprtng_ExtIEs
(
SztProtExtnField_M1PeriodicRprtng_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_M1PeriodicRprtng_ExtIEs(param, ptr, mBuf)
SztProtExtnField_M1PeriodicRprtng_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_M1PeriodicRprtng_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnM1PeriodicRprtng_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_M1PeriodicRprtng_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_M1PeriodicRprtng_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_M1PeriodicRprtng_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_M1PeriodicRprtng_ExtIEs
(
SztProtExtnCont_M1PeriodicRprtng_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_M1PeriodicRprtng_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_M1PeriodicRprtng_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_M1PeriodicRprtng_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_M1PeriodicRprtng_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_M1PeriodicRprtng_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_M1PeriodicRprtng_ExtIEs */



/*
* FUN : cmUnpkSztM1PeriodicRprtng
*  DESC: Function to Unpack SztM1PeriodicRprtng structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztM1PeriodicRprtng
(
SztM1PeriodicRprtng *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztM1PeriodicRprtng(param, ptr, mBuf)
SztM1PeriodicRprtng *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztM1PeriodicRprtng) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztReportIntervalMDT, &param->reportInterval, mBuf); 
		CMCHKUNPK(cmUnpkSztReportAmountMDT, &param->reportAmount, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_M1PeriodicRprtng_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztM1PeriodicRprtng */

#define cmUnpkSztM3period cmUnpkTknU32



/*
* FUN : cmUnpkSzt_ExtnM3Config_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnM3Config_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnM3Config_ExtIEsCls
(
Szt_ExtnM3Config_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnM3Config_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnM3Config_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnM3Config_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnM3Config_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_M3Config_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_M3Config_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_M3Config_ExtIEs
(
SztProtExtnField_M3Config_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_M3Config_ExtIEs(param, ptr, mBuf)
SztProtExtnField_M3Config_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_M3Config_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnM3Config_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_M3Config_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_M3Config_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_M3Config_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_M3Config_ExtIEs
(
SztProtExtnCont_M3Config_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_M3Config_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_M3Config_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_M3Config_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_M3Config_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_M3Config_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_M3Config_ExtIEs */



/*
* FUN : cmUnpkSztM3Config
*  DESC: Function to Unpack SztM3Config structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztM3Config
(
SztM3Config *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztM3Config(param, ptr, mBuf)
SztM3Config *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztM3Config) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztM3period, &param->m3period, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_M3Config_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztM3Config */

#define cmUnpkSztM4period cmUnpkTknU32

#define cmUnpkSztLinks_to_log cmUnpkTknU32



/*
* FUN : cmUnpkSzt_ExtnM4Config_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnM4Config_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnM4Config_ExtIEsCls
(
Szt_ExtnM4Config_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnM4Config_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnM4Config_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnM4Config_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnM4Config_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_M4Config_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_M4Config_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_M4Config_ExtIEs
(
SztProtExtnField_M4Config_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_M4Config_ExtIEs(param, ptr, mBuf)
SztProtExtnField_M4Config_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_M4Config_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnM4Config_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_M4Config_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_M4Config_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_M4Config_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_M4Config_ExtIEs
(
SztProtExtnCont_M4Config_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_M4Config_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_M4Config_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_M4Config_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_M4Config_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_M4Config_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_M4Config_ExtIEs */



/*
* FUN : cmUnpkSztM4Config
*  DESC: Function to Unpack SztM4Config structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztM4Config
(
SztM4Config *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztM4Config(param, ptr, mBuf)
SztM4Config *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztM4Config) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztM4period, &param->m4period, mBuf); 
		CMCHKUNPK(cmUnpkSztLinks_to_log, &param->m4_links_to_log, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_M4Config_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztM4Config */

#define cmUnpkSztM5period cmUnpkTknU32



/*
* FUN : cmUnpkSzt_ExtnM5Config_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnM5Config_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnM5Config_ExtIEsCls
(
Szt_ExtnM5Config_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnM5Config_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnM5Config_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnM5Config_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnM5Config_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_M5Config_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_M5Config_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_M5Config_ExtIEs
(
SztProtExtnField_M5Config_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_M5Config_ExtIEs(param, ptr, mBuf)
SztProtExtnField_M5Config_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_M5Config_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnM5Config_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_M5Config_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_M5Config_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_M5Config_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_M5Config_ExtIEs
(
SztProtExtnCont_M5Config_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_M5Config_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_M5Config_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_M5Config_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_M5Config_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_M5Config_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_M5Config_ExtIEs */



/*
* FUN : cmUnpkSztM5Config
*  DESC: Function to Unpack SztM5Config structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztM5Config
(
SztM5Config *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztM5Config(param, ptr, mBuf)
SztM5Config *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztM5Config) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztM5period, &param->m5period, mBuf); 
		CMCHKUNPK(cmUnpkSztLinks_to_log, &param->m5_links_to_log, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_M5Config_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztM5Config */

#define cmUnpkSztMDT_Loc_Info cmUnpkTknBStr32 


/*
* FUN : cmUnpkSzt_ExtnImmediateMDT_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnImmediateMDT_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnImmediateMDT_ExtIEsCls
(
Szt_ExtnImmediateMDT_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnImmediateMDT_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnImmediateMDT_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnImmediateMDT_ExtIEsCls) 
	
	switch (val)
	{
		case Sztid_M3Config:
			CMCHKUNPKPTR(cmUnpkSztM3Config, &param->u.sztM3Config, ptr, mBuf);
			break;
		case Sztid_M4Config:
			CMCHKUNPKPTR(cmUnpkSztM4Config, &param->u.sztM4Config, ptr, mBuf);
			break;
		case Sztid_M5Config:
			CMCHKUNPKPTR(cmUnpkSztM5Config, &param->u.sztM5Config, ptr, mBuf);
			break;
		case Sztid_MDT_Loc_Info:
			CMCHKUNPK(cmUnpkSztMDT_Loc_Info, &param->u.sztMDT_Loc_Info, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ExtnImmediateMDT_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_ImmediateMDT_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_ImmediateMDT_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_ImmediateMDT_ExtIEs
(
SztProtExtnField_ImmediateMDT_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_ImmediateMDT_ExtIEs(param, ptr, mBuf)
SztProtExtnField_ImmediateMDT_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_ImmediateMDT_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnImmediateMDT_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_ImmediateMDT_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_ImmediateMDT_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_ImmediateMDT_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_ImmediateMDT_ExtIEs
(
SztProtExtnCont_ImmediateMDT_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_ImmediateMDT_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_ImmediateMDT_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_ImmediateMDT_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_ImmediateMDT_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_ImmediateMDT_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_ImmediateMDT_ExtIEs */



/*
* FUN : cmUnpkSztImmediateMDT
*  DESC: Function to Unpack SztImmediateMDT structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztImmediateMDT
(
SztImmediateMDT *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztImmediateMDT(param, ptr, mBuf)
SztImmediateMDT *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztImmediateMDT) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztMeasurementsToActivate, &param->measurementsToActivate, mBuf); 
		CMCHKUNPK(cmUnpkSztM1RprtngTrigger, &param->m1reportingTrigger, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztM1ThresholdEventA2, &param->m1thresholdeventA2, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztM1PeriodicRprtng, &param->m1periodicRprtng, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_ImmediateMDT_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztImmediateMDT */

#define cmUnpkSztIMSI cmUnpkTknStrOSXL 
#define cmUnpkSztIntegrityProtectionAlgorithms cmUnpkTknBStr32 
#define cmUnpkSztIntfsToTrace cmUnpkTknBStr32 
#define cmUnpkSztTime_UE_StayedInCell cmUnpkTknU32 
#define cmUnpkSztTime_UE_StayedInCell_EnhancedGranularity cmUnpkTknU32 


/*
* FUN : cmUnpkSzt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls
(
Szt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls) 
	
	switch (val)
	{
		case Sztid_Time_UE_StayedInCell_EnhancedGranularity:
			CMCHKUNPK(cmUnpkSztTime_UE_StayedInCell_EnhancedGranularity, &param->u.sztTime_UE_StayedInCell_EnhancedGranularity, mBuf); 
			break;
		case Sztid_HO_Cause:
			CMCHKUNPKPTR(cmUnpkSztCause, &param->u.sztCause, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs
(
SztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs(param, ptr, mBuf)
SztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnLastVisitedEUTRANCellInform_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs
(
SztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_LastVisitedEUTRANCellInform_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs */



/*
* FUN : cmUnpkSztLastVisitedEUTRANCellInform
*  DESC: Function to Unpack SztLastVisitedEUTRANCellInform structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztLastVisitedEUTRANCellInform
(
SztLastVisitedEUTRANCellInform *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztLastVisitedEUTRANCellInform(param, ptr, mBuf)
SztLastVisitedEUTRANCellInform *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztLastVisitedEUTRANCellInform) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztEUTRAN_CGI, &param->global_Cell_ID, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztCellTyp, &param->cellTyp, ptr, mBuf); 
		CMCHKUNPK(cmUnpkSztTime_UE_StayedInCell, &param->time_UE_StayedInCell, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_LastVisitedEUTRANCellInform_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztLastVisitedEUTRANCellInform */

#define cmUnpkSztLastVisitedUTRANCellInform cmUnpkTknStrOSXL 


/*
* FUN : cmUnpkSztLastVisitedGERANCellInform
*  DESC: Function to Unpack SztLastVisitedGERANCellInform structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztLastVisitedGERANCellInform
(
SztLastVisitedGERANCellInform *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztLastVisitedGERANCellInform(param, ptr, mBuf)
SztLastVisitedGERANCellInform *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztLastVisitedGERANCellInform) 
	
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
}	 /* End of function cmUnpkSztLastVisitedGERANCellInform */



/*
* FUN : cmUnpkSztLastVisitedCell_Item
*  DESC: Function to Unpack SztLastVisitedCell_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztLastVisitedCell_Item
(
SztLastVisitedCell_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztLastVisitedCell_Item(param, ptr, mBuf)
SztLastVisitedCell_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztLastVisitedCell_Item) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case LASTVISITEDCELL_ITEM_E_UTRAN_CELL :
				CMCHKUNPKPTR(cmUnpkSztLastVisitedEUTRANCellInform, &param->val.e_UTRAN_Cell, ptr, mBuf); 
				break;
			case LASTVISITEDCELL_ITEM_UTRAN_CELL :
				SZUCHKUNPKPTR(cmUnpkSztLastVisitedUTRANCellInform, &param->val.uTRAN_Cell, ptr, mBuf); 
				break;
			case LASTVISITEDCELL_ITEM_GERAN_CELL :
				CMCHKUNPKPTR(cmUnpkSztLastVisitedGERANCellInform, &param->val.gERAN_Cell, ptr, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztLastVisitedCell_Item */

#define cmUnpkSztL3_Inform cmUnpkTknStrOSXL 
#define cmUnpkSztLPPa_PDU cmUnpkTknStrOSXL 
#define cmUnpkSztLoggingInterval cmUnpkTknU32

#define cmUnpkSztLoggingDuration cmUnpkTknU32



/*
* FUN : cmUnpkSzt_ExtnLoggedMDT_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnLoggedMDT_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnLoggedMDT_ExtIEsCls
(
Szt_ExtnLoggedMDT_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnLoggedMDT_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnLoggedMDT_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnLoggedMDT_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnLoggedMDT_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_LoggedMDT_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_LoggedMDT_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_LoggedMDT_ExtIEs
(
SztProtExtnField_LoggedMDT_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_LoggedMDT_ExtIEs(param, ptr, mBuf)
SztProtExtnField_LoggedMDT_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_LoggedMDT_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnLoggedMDT_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_LoggedMDT_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_LoggedMDT_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_LoggedMDT_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_LoggedMDT_ExtIEs
(
SztProtExtnCont_LoggedMDT_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_LoggedMDT_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_LoggedMDT_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_LoggedMDT_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_LoggedMDT_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_LoggedMDT_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_LoggedMDT_ExtIEs */



/*
* FUN : cmUnpkSztLoggedMDT
*  DESC: Function to Unpack SztLoggedMDT structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztLoggedMDT
(
SztLoggedMDT *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztLoggedMDT(param, ptr, mBuf)
SztLoggedMDT *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztLoggedMDT) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztLoggingInterval, &param->loggingInterval, mBuf); 
		CMCHKUNPK(cmUnpkSztLoggingDuration, &param->loggingDuration, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_LoggedMDT_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztLoggedMDT */

#define cmUnpkSztMDT_Actvn cmUnpkTknU32



/*
* FUN : cmUnpkSztMDTMode
*  DESC: Function to Unpack SztMDTMode structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztMDTMode
(
SztMDTMode *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztMDTMode(param, ptr, mBuf)
SztMDTMode *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztMDTMode) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case MDTMODE_IMMEDIATEMDT :
				CMCHKUNPKPTR(cmUnpkSztImmediateMDT, &param->val.immediateMDT, ptr, mBuf); 
				break;
			case MDTMODE_LOGGEDMDT :
				CMCHKUNPKPTR(cmUnpkSztLoggedMDT, &param->val.loggedMDT, ptr, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztMDTMode */



/*
* FUN : cmUnpkSztMDTPLMNLst
*  DESC: Function to Unpack SztMDTPLMNLst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztMDTPLMNLst
(
SztMDTPLMNLst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztMDTPLMNLst(param, ptr, mBuf)
SztMDTPLMNLst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztMDTPLMNLst) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztPLMNidentity)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			SZUCHKUNPKPTR(cmUnpkSztTBCD_STRING, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztMDTPLMNLst */



/*
* FUN : cmUnpkSzt_ExtnMDT_Config_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnMDT_Config_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnMDT_Config_ExtIEsCls
(
Szt_ExtnMDT_Config_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnMDT_Config_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnMDT_Config_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnMDT_Config_ExtIEsCls) 
	
	switch (val)
	{
		case Sztid_SignallingBasedMDTPLMNLst:
			CMCHKUNPKPTR(cmUnpkSztMDTPLMNLst, &param->u.sztMDTPLMNLst, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ExtnMDT_Config_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_MDT_Config_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_MDT_Config_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_MDT_Config_ExtIEs
(
SztProtExtnField_MDT_Config_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_MDT_Config_ExtIEs(param, ptr, mBuf)
SztProtExtnField_MDT_Config_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_MDT_Config_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnMDT_Config_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_MDT_Config_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_MDT_Config_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_MDT_Config_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_MDT_Config_ExtIEs
(
SztProtExtnCont_MDT_Config_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_MDT_Config_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_MDT_Config_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_MDT_Config_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_MDT_Config_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_MDT_Config_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_MDT_Config_ExtIEs */



/*
* FUN : cmUnpkSztMDT_Config
*  DESC: Function to Unpack SztMDT_Config structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztMDT_Config
(
SztMDT_Config *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztMDT_Config(param, ptr, mBuf)
SztMDT_Config *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztMDT_Config) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztMDT_Actvn, &param->mdt_Actvn, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztAreaScopeOfMDT, &param->areaScopeOfMDT, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztMDTMode, &param->mDTMode, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_MDT_Config_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztMDT_Config */

#define cmUnpkSztManagementBasedMDTAllowed cmUnpkTknU32

#define cmUnpkSztPrivacyIndicator cmUnpkTknU32

#define cmUnpkSztMsgIdentifier cmUnpkTknBStr32 
#define cmUnpkSztMobilityInform cmUnpkTknBStr32 
#define cmUnpkSztMMEname cmUnpkTknStrOSXL 
#define cmUnpkSztMMERelaySupportIndicator cmUnpkTknU32

#define cmUnpkSztMME_UE_S1AP_ID cmUnpkTknU32 
#define cmUnpkSztM_TMSI cmUnpkTknStrOSXL 
#define cmUnpkSztMSClassmark2 cmUnpkTknStrOSXL 
#define cmUnpkSztMSClassmark3 cmUnpkTknStrOSXL 
#define cmUnpkSztNAS_PDU cmUnpkTknStrOSXL 
#define cmUnpkSztNASSecurParamsfromE_UTRAN cmUnpkTknStrOSXL 
#define cmUnpkSztNASSecurParamstoE_UTRAN cmUnpkTknStrOSXL 
#define cmUnpkSztNumberofBroadcastRqst cmUnpkTknU32 
#define cmUnpkSztOldBSS_ToNewBSS_Inform cmUnpkTknStrOSXL 
#define cmUnpkSztOverloadAction cmUnpkTknU32



/*
* FUN : cmUnpkSztOverloadResp
*  DESC: Function to Unpack SztOverloadResp structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztOverloadResp
(
SztOverloadResp *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztOverloadResp(param, ptr, mBuf)
SztOverloadResp *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztOverloadResp) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case OVERLOADRESP_OVERLOADACTION :
				CMCHKUNPK(cmUnpkSztOverloadAction, &param->val.overloadAction, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztOverloadResp */

#define cmUnpkSztPagDRX cmUnpkTknU32

#define cmUnpkSztPagPriority cmUnpkTknU32

#define cmUnpkSztPort_Number cmUnpkTknStr4 
#define cmUnpkSztPS_ServiceNotAvailable cmUnpkTknU32

#define cmUnpkSztRelativeMMECapacity cmUnpkTknU32 
#define cmUnpkSztRelayNode_Indicator cmUnpkTknU32

#define cmUnpkSztReportArea cmUnpkTknU32



/*
* FUN : cmUnpkSzt_ExtnRqstTyp_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnRqstTyp_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnRqstTyp_ExtIEsCls
(
Szt_ExtnRqstTyp_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnRqstTyp_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnRqstTyp_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnRqstTyp_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnRqstTyp_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_RqstTyp_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_RqstTyp_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_RqstTyp_ExtIEs
(
SztProtExtnField_RqstTyp_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_RqstTyp_ExtIEs(param, ptr, mBuf)
SztProtExtnField_RqstTyp_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_RqstTyp_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnRqstTyp_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_RqstTyp_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_RqstTyp_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_RqstTyp_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_RqstTyp_ExtIEs
(
SztProtExtnCont_RqstTyp_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_RqstTyp_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_RqstTyp_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_RqstTyp_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_RqstTyp_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_RqstTyp_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_RqstTyp_ExtIEs */



/*
* FUN : cmUnpkSztRqstTyp
*  DESC: Function to Unpack SztRqstTyp structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztRqstTyp
(
SztRqstTyp *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztRqstTyp(param, ptr, mBuf)
SztRqstTyp *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztRqstTyp) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztEventTyp, &param->eventTyp, mBuf); 
		CMCHKUNPK(cmUnpkSztReportArea, &param->reportArea, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_RqstTyp_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztRqstTyp */

#define cmUnpkSztRIMInform cmUnpkTknStrOSXL 
#define cmUnpkSztRNC_ID cmUnpkTknU32 


/*
* FUN : cmUnpkSzt_ExtnTgetRNC_ID_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnTgetRNC_ID_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnTgetRNC_ID_ExtIEsCls
(
Szt_ExtnTgetRNC_ID_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnTgetRNC_ID_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnTgetRNC_ID_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnTgetRNC_ID_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnTgetRNC_ID_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_TgetRNC_ID_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_TgetRNC_ID_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_TgetRNC_ID_ExtIEs
(
SztProtExtnField_TgetRNC_ID_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_TgetRNC_ID_ExtIEs(param, ptr, mBuf)
SztProtExtnField_TgetRNC_ID_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_TgetRNC_ID_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnTgetRNC_ID_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_TgetRNC_ID_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_TgetRNC_ID_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_TgetRNC_ID_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_TgetRNC_ID_ExtIEs
(
SztProtExtnCont_TgetRNC_ID_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_TgetRNC_ID_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_TgetRNC_ID_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_TgetRNC_ID_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_TgetRNC_ID_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_TgetRNC_ID_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_TgetRNC_ID_ExtIEs */



/*
* FUN : cmUnpkSztTgetRNC_ID
*  DESC: Function to Unpack SztTgetRNC_ID structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztTgetRNC_ID
(
SztTgetRNC_ID *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztTgetRNC_ID(param, ptr, mBuf)
SztTgetRNC_ID *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztTgetRNC_ID) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztLAI, &param->lAI, ptr, mBuf); 
		CMCHKUNPK(cmUnpkSztRAC, &param->rAC, mBuf); 
		CMCHKUNPK(cmUnpkSztRNC_ID, &param->rNC_ID, mBuf); 
		CMCHKUNPK(cmUnpkSztExtendedRNC_ID, &param->extendedRNC_ID, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_TgetRNC_ID_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztTgetRNC_ID */



/*
* FUN : cmUnpkSztRIMRoutingAddr
*  DESC: Function to Unpack SztRIMRoutingAddr structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztRIMRoutingAddr
(
SztRIMRoutingAddr *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztRIMRoutingAddr(param, ptr, mBuf)
SztRIMRoutingAddr *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztRIMRoutingAddr) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case RIMROUTINGADDR_GERAN_CELL_ID :
				CMCHKUNPKPTR(cmUnpkSztGERAN_Cell_ID, &param->val.gERAN_Cell_ID, ptr, mBuf); 
				break;
			case RIMROUTINGADDR_TARGETRNC_ID :
				CMCHKUNPKPTR(cmUnpkSztTgetRNC_ID, &param->val.targetRNC_ID, ptr, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztRIMRoutingAddr */



/*
* FUN : cmUnpkSzt_ExtnRIMTfr_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnRIMTfr_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnRIMTfr_ExtIEsCls
(
Szt_ExtnRIMTfr_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnRIMTfr_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnRIMTfr_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnRIMTfr_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnRIMTfr_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_RIMTfr_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_RIMTfr_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_RIMTfr_ExtIEs
(
SztProtExtnField_RIMTfr_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_RIMTfr_ExtIEs(param, ptr, mBuf)
SztProtExtnField_RIMTfr_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_RIMTfr_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnRIMTfr_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_RIMTfr_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_RIMTfr_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_RIMTfr_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_RIMTfr_ExtIEs
(
SztProtExtnCont_RIMTfr_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_RIMTfr_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_RIMTfr_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_RIMTfr_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_RIMTfr_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_RIMTfr_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_RIMTfr_ExtIEs */



/*
* FUN : cmUnpkSztRIMTfr
*  DESC: Function to Unpack SztRIMTfr structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztRIMTfr
(
SztRIMTfr *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztRIMTfr(param, ptr, mBuf)
SztRIMTfr *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztRIMTfr) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		SZUCHKUNPKPTR(cmUnpkSztRIMInform, &param->rIMInform, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztRIMRoutingAddr, &param->rIMRoutingAddr, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_RIMTfr_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztRIMTfr */

#define cmUnpkSztRepetitionPeriod cmUnpkTknU32 
#define cmUnpkSztRRC_Cont cmUnpkTknStrOSXL 
#define cmUnpkSztRRC_Establishment_Cause cmUnpkTknU32

#define cmUnpkSztRouting_ID cmUnpkTknU32 
#define cmUnpkSztSecurKey cmUnpkTknStrBSXL 
#define cmUnpkSztSecurCntxtnextHopChainingCount cmUnpkTknU32 


/*
* FUN : cmUnpkSzt_ExtnSecurCntxt_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnSecurCntxt_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnSecurCntxt_ExtIEsCls
(
Szt_ExtnSecurCntxt_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnSecurCntxt_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnSecurCntxt_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnSecurCntxt_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnSecurCntxt_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_SecurCntxt_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_SecurCntxt_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_SecurCntxt_ExtIEs
(
SztProtExtnField_SecurCntxt_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_SecurCntxt_ExtIEs(param, ptr, mBuf)
SztProtExtnField_SecurCntxt_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_SecurCntxt_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnSecurCntxt_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_SecurCntxt_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_SecurCntxt_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_SecurCntxt_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_SecurCntxt_ExtIEs
(
SztProtExtnCont_SecurCntxt_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_SecurCntxt_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_SecurCntxt_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_SecurCntxt_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_SecurCntxt_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_SecurCntxt_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_SecurCntxt_ExtIEs */



/*
* FUN : cmUnpkSztSecurCntxt
*  DESC: Function to Unpack SztSecurCntxt structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztSecurCntxt
(
SztSecurCntxt *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztSecurCntxt(param, ptr, mBuf)
SztSecurCntxt *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztSecurCntxt) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztSecurCntxtnextHopChainingCount, &param->nextHopChainingCount, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztSecurKey, &param->nextHopParameter, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_SecurCntxt_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztSecurCntxt */

#define cmUnpkSztSerialNumber cmUnpkTknBStr32 
#define cmUnpkSztSONInformRqst cmUnpkTknU32



/*
* FUN : cmUnpkSztENBX2GTPTLAs
*  DESC: Function to Unpack SztENBX2GTPTLAs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztENBX2GTPTLAs
(
SztENBX2GTPTLAs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztENBX2GTPTLAs(param, ptr, mBuf)
SztENBX2GTPTLAs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztENBX2GTPTLAs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztTportLyrAddr)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztTportLyrAddr, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztENBX2GTPTLAs */



/*
* FUN : cmUnpkSzt_ExtnENBX2ExtTLA_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnENBX2ExtTLA_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnENBX2ExtTLA_ExtIEsCls
(
Szt_ExtnENBX2ExtTLA_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnENBX2ExtTLA_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnENBX2ExtTLA_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnENBX2ExtTLA_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnENBX2ExtTLA_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_ENBX2ExtTLA_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_ENBX2ExtTLA_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_ENBX2ExtTLA_ExtIEs
(
SztProtExtnField_ENBX2ExtTLA_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_ENBX2ExtTLA_ExtIEs(param, ptr, mBuf)
SztProtExtnField_ENBX2ExtTLA_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_ENBX2ExtTLA_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnENBX2ExtTLA_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_ENBX2ExtTLA_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_ENBX2ExtTLA_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_ENBX2ExtTLA_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_ENBX2ExtTLA_ExtIEs
(
SztProtExtnCont_ENBX2ExtTLA_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_ENBX2ExtTLA_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_ENBX2ExtTLA_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_ENBX2ExtTLA_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_ENBX2ExtTLA_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_ENBX2ExtTLA_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_ENBX2ExtTLA_ExtIEs */



/*
* FUN : cmUnpkSztENBX2ExtTLA
*  DESC: Function to Unpack SztENBX2ExtTLA structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztENBX2ExtTLA
(
SztENBX2ExtTLA *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztENBX2ExtTLA(param, ptr, mBuf)
SztENBX2ExtTLA *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztENBX2ExtTLA) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztTportLyrAddr, &param->iPsecTLA, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztENBX2GTPTLAs, &param->gTPTLAa, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_ENBX2ExtTLA_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztENBX2ExtTLA */



/*
* FUN : cmUnpkSztENBX2ExtTLAs
*  DESC: Function to Unpack SztENBX2ExtTLAs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztENBX2ExtTLAs
(
SztENBX2ExtTLAs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztENBX2ExtTLAs(param, ptr, mBuf)
SztENBX2ExtTLAs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztENBX2ExtTLAs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztENBX2ExtTLA)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztENBX2ExtTLA, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztENBX2ExtTLAs */



/*
* FUN : cmUnpkSzt_ExtnX2TNLConfigInfo_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnX2TNLConfigInfo_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnX2TNLConfigInfo_ExtIEsCls
(
Szt_ExtnX2TNLConfigInfo_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnX2TNLConfigInfo_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnX2TNLConfigInfo_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnX2TNLConfigInfo_ExtIEsCls) 
	
	switch (val)
	{
		case Sztid_eNBX2ExtendedTportLyrAddres:
			CMCHKUNPKPTR(cmUnpkSztENBX2ExtTLAs, &param->u.sztENBX2ExtTLAs, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ExtnX2TNLConfigInfo_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_X2TNLConfigInfo_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_X2TNLConfigInfo_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_X2TNLConfigInfo_ExtIEs
(
SztProtExtnField_X2TNLConfigInfo_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_X2TNLConfigInfo_ExtIEs(param, ptr, mBuf)
SztProtExtnField_X2TNLConfigInfo_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_X2TNLConfigInfo_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnX2TNLConfigInfo_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_X2TNLConfigInfo_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_X2TNLConfigInfo_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_X2TNLConfigInfo_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_X2TNLConfigInfo_ExtIEs
(
SztProtExtnCont_X2TNLConfigInfo_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_X2TNLConfigInfo_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_X2TNLConfigInfo_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_X2TNLConfigInfo_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_X2TNLConfigInfo_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_X2TNLConfigInfo_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_X2TNLConfigInfo_ExtIEs */



/*
* FUN : cmUnpkSztX2TNLConfigInfo
*  DESC: Function to Unpack SztX2TNLConfigInfo structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztX2TNLConfigInfo
(
SztX2TNLConfigInfo *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztX2TNLConfigInfo(param, ptr, mBuf)
SztX2TNLConfigInfo *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztX2TNLConfigInfo) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztENBX2TLAs, &param->eNBX2TportLyrAddres, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_X2TNLConfigInfo_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztX2TNLConfigInfo */

#define cmUnpkSztStratumLvl cmUnpkTknU32 
#define cmUnpkSztSynchronizationStatus cmUnpkTknU32



/*
* FUN : cmUnpkSzt_ExtnTimeSynchronizationInfo_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnTimeSynchronizationInfo_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnTimeSynchronizationInfo_ExtIEsCls
(
Szt_ExtnTimeSynchronizationInfo_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnTimeSynchronizationInfo_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnTimeSynchronizationInfo_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnTimeSynchronizationInfo_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnTimeSynchronizationInfo_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_TimeSynchronizationInfo_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_TimeSynchronizationInfo_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_TimeSynchronizationInfo_ExtIEs
(
SztProtExtnField_TimeSynchronizationInfo_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_TimeSynchronizationInfo_ExtIEs(param, ptr, mBuf)
SztProtExtnField_TimeSynchronizationInfo_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_TimeSynchronizationInfo_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnTimeSynchronizationInfo_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_TimeSynchronizationInfo_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_TimeSynchronizationInfo_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_TimeSynchronizationInfo_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_TimeSynchronizationInfo_ExtIEs
(
SztProtExtnCont_TimeSynchronizationInfo_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_TimeSynchronizationInfo_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_TimeSynchronizationInfo_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_TimeSynchronizationInfo_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_TimeSynchronizationInfo_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_TimeSynchronizationInfo_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_TimeSynchronizationInfo_ExtIEs */



/*
* FUN : cmUnpkSztTimeSynchronizationInfo
*  DESC: Function to Unpack SztTimeSynchronizationInfo structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztTimeSynchronizationInfo
(
SztTimeSynchronizationInfo *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztTimeSynchronizationInfo(param, ptr, mBuf)
SztTimeSynchronizationInfo *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztTimeSynchronizationInfo) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztStratumLvl, &param->stratumLvl, mBuf); 
		CMCHKUNPK(cmUnpkSztSynchronizationStatus, &param->synchronizationStatus, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_TimeSynchronizationInfo_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztTimeSynchronizationInfo */



/*
* FUN : cmUnpkSzt_ExtnSONInformReply_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnSONInformReply_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnSONInformReply_ExtIEsCls
(
Szt_ExtnSONInformReply_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnSONInformReply_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnSONInformReply_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnSONInformReply_ExtIEsCls) 
	
	switch (val)
	{
		case Sztid_Time_Synchronization_Info:
			CMCHKUNPKPTR(cmUnpkSztTimeSynchronizationInfo, &param->u.sztTimeSynchronizationInfo, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ExtnSONInformReply_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_SONInformReply_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_SONInformReply_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_SONInformReply_ExtIEs
(
SztProtExtnField_SONInformReply_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_SONInformReply_ExtIEs(param, ptr, mBuf)
SztProtExtnField_SONInformReply_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_SONInformReply_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnSONInformReply_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_SONInformReply_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_SONInformReply_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_SONInformReply_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_SONInformReply_ExtIEs
(
SztProtExtnCont_SONInformReply_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_SONInformReply_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_SONInformReply_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_SONInformReply_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_SONInformReply_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_SONInformReply_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_SONInformReply_ExtIEs */



/*
* FUN : cmUnpkSztSONInformReply
*  DESC: Function to Unpack SztSONInformReply structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztSONInformReply
(
SztSONInformReply *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztSONInformReply(param, ptr, mBuf)
SztSONInformReply *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztSONInformReply) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztX2TNLConfigInfo, &param->x2TNLConfigInfo, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_SONInformReply_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztSONInformReply */



/*
* FUN : cmUnpkSztSONInform
*  DESC: Function to Unpack SztSONInform structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztSONInform
(
SztSONInform *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztSONInform(param, ptr, mBuf)
SztSONInform *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztSONInform) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case SONINFORM_SONINFORMRQST :
				CMCHKUNPK(cmUnpkSztSONInformRqst, &param->val.sONInformRqst, mBuf); 
				break;
			case SONINFORM_SONINFORMREPLY :
				CMCHKUNPKPTR(cmUnpkSztSONInformReply, &param->val.sONInformReply, ptr, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztSONInform */



/*
* FUN : cmUnpkSzt_ExtnTgeteNB_ID_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnTgeteNB_ID_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnTgeteNB_ID_ExtIEsCls
(
Szt_ExtnTgeteNB_ID_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnTgeteNB_ID_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnTgeteNB_ID_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnTgeteNB_ID_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnTgeteNB_ID_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_TgeteNB_ID_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_TgeteNB_ID_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_TgeteNB_ID_ExtIEs
(
SztProtExtnField_TgeteNB_ID_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_TgeteNB_ID_ExtIEs(param, ptr, mBuf)
SztProtExtnField_TgeteNB_ID_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_TgeteNB_ID_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnTgeteNB_ID_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_TgeteNB_ID_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_TgeteNB_ID_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_TgeteNB_ID_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_TgeteNB_ID_ExtIEs
(
SztProtExtnCont_TgeteNB_ID_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_TgeteNB_ID_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_TgeteNB_ID_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_TgeteNB_ID_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_TgeteNB_ID_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_TgeteNB_ID_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_TgeteNB_ID_ExtIEs */



/*
* FUN : cmUnpkSztTgeteNB_ID
*  DESC: Function to Unpack SztTgeteNB_ID structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztTgeteNB_ID
(
SztTgeteNB_ID *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztTgeteNB_ID(param, ptr, mBuf)
SztTgeteNB_ID *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztTgeteNB_ID) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztGlobal_ENB_ID, &param->global_ENB_ID, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztTAI, &param->selected_TAI, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_TgeteNB_ID_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztTgeteNB_ID */



/*
* FUN : cmUnpkSzt_ExtnSrceNB_ID_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnSrceNB_ID_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnSrceNB_ID_ExtIEsCls
(
Szt_ExtnSrceNB_ID_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnSrceNB_ID_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnSrceNB_ID_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnSrceNB_ID_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnSrceNB_ID_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_SrceNB_ID_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_SrceNB_ID_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_SrceNB_ID_ExtIEs
(
SztProtExtnField_SrceNB_ID_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_SrceNB_ID_ExtIEs(param, ptr, mBuf)
SztProtExtnField_SrceNB_ID_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_SrceNB_ID_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnSrceNB_ID_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_SrceNB_ID_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_SrceNB_ID_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_SrceNB_ID_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_SrceNB_ID_ExtIEs
(
SztProtExtnCont_SrceNB_ID_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_SrceNB_ID_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_SrceNB_ID_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_SrceNB_ID_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_SrceNB_ID_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_SrceNB_ID_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_SrceNB_ID_ExtIEs */



/*
* FUN : cmUnpkSztSrceNB_ID
*  DESC: Function to Unpack SztSrceNB_ID structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztSrceNB_ID
(
SztSrceNB_ID *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztSrceNB_ID(param, ptr, mBuf)
SztSrceNB_ID *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztSrceNB_ID) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztGlobal_ENB_ID, &param->global_ENB_ID, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztTAI, &param->selected_TAI, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_SrceNB_ID_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztSrceNB_ID */



/*
* FUN : cmUnpkSzt_ExtnSONConfigTfr_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnSONConfigTfr_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnSONConfigTfr_ExtIEsCls
(
Szt_ExtnSONConfigTfr_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnSONConfigTfr_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnSONConfigTfr_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnSONConfigTfr_ExtIEsCls) 
	
	switch (val)
	{
		case Sztid_x2TNLConfigInfo:
			CMCHKUNPKPTR(cmUnpkSztX2TNLConfigInfo, &param->u.sztX2TNLConfigInfo, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ExtnSONConfigTfr_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_SONConfigTfr_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_SONConfigTfr_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_SONConfigTfr_ExtIEs
(
SztProtExtnField_SONConfigTfr_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_SONConfigTfr_ExtIEs(param, ptr, mBuf)
SztProtExtnField_SONConfigTfr_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_SONConfigTfr_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnSONConfigTfr_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_SONConfigTfr_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_SONConfigTfr_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_SONConfigTfr_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_SONConfigTfr_ExtIEs
(
SztProtExtnCont_SONConfigTfr_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_SONConfigTfr_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_SONConfigTfr_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_SONConfigTfr_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_SONConfigTfr_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_SONConfigTfr_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_SONConfigTfr_ExtIEs */



/*
* FUN : cmUnpkSztSONConfigTfr
*  DESC: Function to Unpack SztSONConfigTfr structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztSONConfigTfr
(
SztSONConfigTfr *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztSONConfigTfr(param, ptr, mBuf)
SztSONConfigTfr *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztSONConfigTfr) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztTgeteNB_ID, &param->targeteNB_ID, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztSrceNB_ID, &param->sourceeNB_ID, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztSONInform, &param->sONInform, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_SONConfigTfr_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztSONConfigTfr */

#define cmUnpkSztSrc_ToTget_TprntCont cmUnpkTknStrOSXL 
#define cmUnpkSztSrcBSS_ToTgetBSS_TprntCont cmUnpkTknStrOSXL 
#define cmUnpkSztSRVCCOperationPossible cmUnpkTknU32

#define cmUnpkSztSRVCCHOInd cmUnpkTknU32

#define cmUnpkSztSubscriberProfileIDforRFP cmUnpkTknU32 


/*
* FUN : cmUnpkSztUE_HistoryInform
*  DESC: Function to Unpack SztUE_HistoryInform structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztUE_HistoryInform
(
SztUE_HistoryInform *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztUE_HistoryInform(param, ptr, mBuf)
SztUE_HistoryInform *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztUE_HistoryInform) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztLastVisitedCell_Item)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztLastVisitedCell_Item, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztUE_HistoryInform */



/*
* FUN : cmUnpkSzt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls
(
Szt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls) 
	
	switch (val)
	{
		case Sztid_MobilityInform:
			CMCHKUNPK(cmUnpkSztMobilityInform, &param->u.sztMobilityInform, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs
(
SztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs(param, ptr, mBuf)
SztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnSrceNB_ToTgeteNB_TprntCont_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs
(
SztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_SrceNB_ToTgeteNB_TprntCont_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs */



/*
* FUN : cmUnpkSztSrceNB_ToTgeteNB_TprntCont
*  DESC: Function to Unpack SztSrceNB_ToTgeteNB_TprntCont structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztSrceNB_ToTgeteNB_TprntCont
(
SztSrceNB_ToTgeteNB_TprntCont *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztSrceNB_ToTgeteNB_TprntCont(param, ptr, mBuf)
SztSrceNB_ToTgeteNB_TprntCont *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztSrceNB_ToTgeteNB_TprntCont) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		SZUCHKUNPKPTR(cmUnpkSztRRC_Cont, &param->rRC_Cont, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztE_RABInformLst, &param->e_RABInformLst, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztEUTRAN_CGI, &param->targetCell_ID, ptr, mBuf); 
		CMCHKUNPK(cmUnpkSztSubscriberProfileIDforRFP, &param->subscriberProfileIDforRFP, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztUE_HistoryInform, &param->uE_HistoryInform, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_SrceNB_ToTgeteNB_TprntCont_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztSrceNB_ToTgeteNB_TprntCont */

#define cmUnpkSztSrcRNC_ToTgetRNC_TprntCont cmUnpkTknStrOSXL 


/*
* FUN : cmUnpkSztSrvdPLMNs
*  DESC: Function to Unpack SztSrvdPLMNs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztSrvdPLMNs
(
SztSrvdPLMNs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztSrvdPLMNs(param, ptr, mBuf)
SztSrvdPLMNs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztSrvdPLMNs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztPLMNidentity)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			SZUCHKUNPKPTR(cmUnpkSztTBCD_STRING, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztSrvdPLMNs */



/*
* FUN : cmUnpkSztSrvdGroupIDs
*  DESC: Function to Unpack SztSrvdGroupIDs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztSrvdGroupIDs
(
SztSrvdGroupIDs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztSrvdGroupIDs(param, ptr, mBuf)
SztSrvdGroupIDs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztSrvdGroupIDs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztMME_Group_ID)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPK(cmUnpkSztMME_Group_ID, &(param->member[i]), mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztSrvdGroupIDs */



/*
* FUN : cmUnpkSztSrvdMMECs
*  DESC: Function to Unpack SztSrvdMMECs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztSrvdMMECs
(
SztSrvdMMECs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztSrvdMMECs(param, ptr, mBuf)
SztSrvdMMECs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztSrvdMMECs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztMME_Code)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPK(cmUnpkSztMME_Code, &(param->member[i]), mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztSrvdMMECs */



/*
* FUN : cmUnpkSzt_ExtnSrvdGUMMEIsItem_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnSrvdGUMMEIsItem_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnSrvdGUMMEIsItem_ExtIEsCls
(
Szt_ExtnSrvdGUMMEIsItem_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnSrvdGUMMEIsItem_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnSrvdGUMMEIsItem_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnSrvdGUMMEIsItem_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnSrvdGUMMEIsItem_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_SrvdGUMMEIsItem_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_SrvdGUMMEIsItem_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_SrvdGUMMEIsItem_ExtIEs
(
SztProtExtnField_SrvdGUMMEIsItem_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_SrvdGUMMEIsItem_ExtIEs(param, ptr, mBuf)
SztProtExtnField_SrvdGUMMEIsItem_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_SrvdGUMMEIsItem_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnSrvdGUMMEIsItem_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_SrvdGUMMEIsItem_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_SrvdGUMMEIsItem_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_SrvdGUMMEIsItem_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_SrvdGUMMEIsItem_ExtIEs
(
SztProtExtnCont_SrvdGUMMEIsItem_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_SrvdGUMMEIsItem_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_SrvdGUMMEIsItem_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_SrvdGUMMEIsItem_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_SrvdGUMMEIsItem_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_SrvdGUMMEIsItem_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_SrvdGUMMEIsItem_ExtIEs */



/*
* FUN : cmUnpkSztSrvdGUMMEIsItem
*  DESC: Function to Unpack SztSrvdGUMMEIsItem structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztSrvdGUMMEIsItem
(
SztSrvdGUMMEIsItem *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztSrvdGUMMEIsItem(param, ptr, mBuf)
SztSrvdGUMMEIsItem *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztSrvdGUMMEIsItem) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztSrvdPLMNs, &param->servedPLMNs, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztSrvdGroupIDs, &param->servedGroupIDs, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztSrvdMMECs, &param->servedMMECs, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_SrvdGUMMEIsItem_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztSrvdGUMMEIsItem */



/*
* FUN : cmUnpkSztSrvdGUMMEIs
*  DESC: Function to Unpack SztSrvdGUMMEIs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztSrvdGUMMEIs
(
SztSrvdGUMMEIs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztSrvdGUMMEIs(param, ptr, mBuf)
SztSrvdGUMMEIs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztSrvdGUMMEIs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztSrvdGUMMEIsItem)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztSrvdGUMMEIsItem, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztSrvdGUMMEIs */



/*
* FUN : cmUnpkSzt_ExtnSuppTAs_Item_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnSuppTAs_Item_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnSuppTAs_Item_ExtIEsCls
(
Szt_ExtnSuppTAs_Item_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnSuppTAs_Item_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnSuppTAs_Item_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnSuppTAs_Item_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnSuppTAs_Item_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_SuppTAs_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_SuppTAs_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_SuppTAs_Item_ExtIEs
(
SztProtExtnField_SuppTAs_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_SuppTAs_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnField_SuppTAs_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_SuppTAs_Item_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnSuppTAs_Item_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_SuppTAs_Item_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_SuppTAs_Item_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_SuppTAs_Item_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_SuppTAs_Item_ExtIEs
(
SztProtExtnCont_SuppTAs_Item_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_SuppTAs_Item_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_SuppTAs_Item_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_SuppTAs_Item_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_SuppTAs_Item_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_SuppTAs_Item_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_SuppTAs_Item_ExtIEs */



/*
* FUN : cmUnpkSztSuppTAs_Item
*  DESC: Function to Unpack SztSuppTAs_Item structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztSuppTAs_Item
(
SztSuppTAs_Item *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztSuppTAs_Item(param, ptr, mBuf)
SztSuppTAs_Item *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztSuppTAs_Item) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztTAC, &param->tAC, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztBPLMNs, &param->broadcastPLMNs, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_SuppTAs_Item_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztSuppTAs_Item */



/*
* FUN : cmUnpkSztSuppTAs
*  DESC: Function to Unpack SztSuppTAs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztSuppTAs
(
SztSuppTAs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztSuppTAs(param, ptr, mBuf)
SztSuppTAs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztSuppTAs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztSuppTAs_Item)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztSuppTAs_Item, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztSuppTAs */



/*
* FUN : cmUnpkSzt_ExtnS_TMSI_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnS_TMSI_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnS_TMSI_ExtIEsCls
(
Szt_ExtnS_TMSI_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnS_TMSI_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnS_TMSI_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnS_TMSI_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnS_TMSI_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_S_TMSI_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_S_TMSI_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_S_TMSI_ExtIEs
(
SztProtExtnField_S_TMSI_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_S_TMSI_ExtIEs(param, ptr, mBuf)
SztProtExtnField_S_TMSI_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_S_TMSI_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnS_TMSI_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_S_TMSI_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_S_TMSI_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_S_TMSI_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_S_TMSI_ExtIEs
(
SztProtExtnCont_S_TMSI_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_S_TMSI_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_S_TMSI_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_S_TMSI_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_S_TMSI_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_S_TMSI_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_S_TMSI_ExtIEs */



/*
* FUN : cmUnpkSztS_TMSI
*  DESC: Function to Unpack SztS_TMSI structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztS_TMSI
(
SztS_TMSI *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztS_TMSI(param, ptr, mBuf)
SztS_TMSI *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztS_TMSI) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztMME_Code, &param->mMEC, mBuf); 
		SZUCHKUNPKPTR(cmUnpkSztM_TMSI, &param->m_TMSI, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_S_TMSI_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztS_TMSI */



/*
* FUN : cmUnpkSztTAILstforWarning
*  DESC: Function to Unpack SztTAILstforWarning structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztTAILstforWarning
(
SztTAILstforWarning *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztTAILstforWarning(param, ptr, mBuf)
SztTAILstforWarning *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztTAILstforWarning) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztTAI)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztTAI, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztTAILstforWarning */



/*
* FUN : cmUnpkSztTgetID
*  DESC: Function to Unpack SztTgetID structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztTgetID
(
SztTgetID *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztTgetID(param, ptr, mBuf)
SztTgetID *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztTgetID) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case TGETID_TARGETENB_ID :
				CMCHKUNPKPTR(cmUnpkSztTgeteNB_ID, &param->val.targeteNB_ID, ptr, mBuf); 
				break;
			case TGETID_TARGETRNC_ID :
				CMCHKUNPKPTR(cmUnpkSztTgetRNC_ID, &param->val.targetRNC_ID, ptr, mBuf); 
				break;
			case TGETID_CGI :
				CMCHKUNPKPTR(cmUnpkSztCGI, &param->val.cGI, ptr, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztTgetID */



/*
* FUN : cmUnpkSzt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls
(
Szt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs
(
SztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs(param, ptr, mBuf)
SztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnTgeteNB_ToSrceNB_TprntCont_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs
(
SztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_TgeteNB_ToSrceNB_TprntCont_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs */



/*
* FUN : cmUnpkSztTgeteNB_ToSrceNB_TprntCont
*  DESC: Function to Unpack SztTgeteNB_ToSrceNB_TprntCont structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztTgeteNB_ToSrceNB_TprntCont
(
SztTgeteNB_ToSrceNB_TprntCont *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztTgeteNB_ToSrceNB_TprntCont(param, ptr, mBuf)
SztTgeteNB_ToSrceNB_TprntCont *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztTgeteNB_ToSrceNB_TprntCont) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		SZUCHKUNPKPTR(cmUnpkSztRRC_Cont, &param->rRC_Cont, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_TgeteNB_ToSrceNB_TprntCont_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztTgeteNB_ToSrceNB_TprntCont */

#define cmUnpkSztTget_ToSrc_TprntCont cmUnpkTknStrOSXL 
#define cmUnpkSztTgetRNC_ToSrcRNC_TprntCont cmUnpkTknStrOSXL 
#define cmUnpkSztTgetBSS_ToSrcBSS_TprntCont cmUnpkTknStrOSXL 
#define cmUnpkSztTimeToWait cmUnpkTknU32

#define cmUnpkSztE_UTRAN_Trace_ID cmUnpkTknStrOSXL 
#define cmUnpkSztTraceDepth cmUnpkTknU32



/*
* FUN : cmUnpkSzt_ExtnTraceActvn_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnTraceActvn_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnTraceActvn_ExtIEsCls
(
Szt_ExtnTraceActvn_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnTraceActvn_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnTraceActvn_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnTraceActvn_ExtIEsCls) 
	
	switch (val)
	{
		case Sztid_MDTConfig:
			CMCHKUNPKPTR(cmUnpkSztMDT_Config, &param->u.sztMDT_Config, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ExtnTraceActvn_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_TraceActvn_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_TraceActvn_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_TraceActvn_ExtIEs
(
SztProtExtnField_TraceActvn_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_TraceActvn_ExtIEs(param, ptr, mBuf)
SztProtExtnField_TraceActvn_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_TraceActvn_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnTraceActvn_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_TraceActvn_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_TraceActvn_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_TraceActvn_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_TraceActvn_ExtIEs
(
SztProtExtnCont_TraceActvn_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_TraceActvn_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_TraceActvn_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_TraceActvn_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_TraceActvn_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_TraceActvn_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_TraceActvn_ExtIEs */



/*
* FUN : cmUnpkSztTraceActvn
*  DESC: Function to Unpack SztTraceActvn structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztTraceActvn
(
SztTraceActvn *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztTraceActvn(param, ptr, mBuf)
SztTraceActvn *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztTraceActvn) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		SZUCHKUNPKPTR(cmUnpkSztE_UTRAN_Trace_ID, &param->e_UTRAN_Trace_ID, ptr, mBuf); 
		CMCHKUNPK(cmUnpkSztIntfsToTrace, &param->interfacesToTrace, mBuf); 
		CMCHKUNPK(cmUnpkSztTraceDepth, &param->traceDepth, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztTportLyrAddr, &param->traceCollectionEntityIPAddr, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_TraceActvn_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztTraceActvn */

#define cmUnpkSztTrafficLoadReductionInd cmUnpkTknU32 


/*
* FUN : cmUnpkSzt_ExtnTunnel_Inform_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnTunnel_Inform_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnTunnel_Inform_ExtIEsCls
(
Szt_ExtnTunnel_Inform_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnTunnel_Inform_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnTunnel_Inform_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnTunnel_Inform_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnTunnel_Inform_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_Tunnel_Inform_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_Tunnel_Inform_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_Tunnel_Inform_ExtIEs
(
SztProtExtnField_Tunnel_Inform_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_Tunnel_Inform_ExtIEs(param, ptr, mBuf)
SztProtExtnField_Tunnel_Inform_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_Tunnel_Inform_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnTunnel_Inform_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_Tunnel_Inform_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_Tunnel_Inform_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_Tunnel_Inform_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_Tunnel_Inform_ExtIEs
(
SztProtExtnCont_Tunnel_Inform_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_Tunnel_Inform_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_Tunnel_Inform_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_Tunnel_Inform_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_Tunnel_Inform_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_Tunnel_Inform_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_Tunnel_Inform_ExtIEs */



/*
* FUN : cmUnpkSztTunnelInform
*  DESC: Function to Unpack SztTunnelInform structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztTunnelInform
(
SztTunnelInform *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztTunnelInform(param, ptr, mBuf)
SztTunnelInform *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztTunnelInform) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztTportLyrAddr, &param->transportLyrAddr, ptr, mBuf); 
		CMCHKUNPK(cmUnpkSztPort_Number, &param->uDP_Port_Number, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_Tunnel_Inform_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztTunnelInform */



/*
* FUN : cmUnpkSzt_ExtnUEAgg_MaxBitrates_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnUEAgg_MaxBitrates_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnUEAgg_MaxBitrates_ExtIEsCls
(
Szt_ExtnUEAgg_MaxBitrates_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnUEAgg_MaxBitrates_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnUEAgg_MaxBitrates_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnUEAgg_MaxBitrates_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnUEAgg_MaxBitrates_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_UEAgg_MaxBitrates_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_UEAgg_MaxBitrates_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_UEAgg_MaxBitrates_ExtIEs
(
SztProtExtnField_UEAgg_MaxBitrates_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_UEAgg_MaxBitrates_ExtIEs(param, ptr, mBuf)
SztProtExtnField_UEAgg_MaxBitrates_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_UEAgg_MaxBitrates_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnUEAgg_MaxBitrates_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_UEAgg_MaxBitrates_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_UEAgg_MaxBitrates_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_UEAgg_MaxBitrates_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_UEAgg_MaxBitrates_ExtIEs
(
SztProtExtnCont_UEAgg_MaxBitrates_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_UEAgg_MaxBitrates_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_UEAgg_MaxBitrates_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_UEAgg_MaxBitrates_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_UEAgg_MaxBitrates_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_UEAgg_MaxBitrates_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_UEAgg_MaxBitrates_ExtIEs */



/*
* FUN : cmUnpkSztUEAggMaxBitrate
*  DESC: Function to Unpack SztUEAggMaxBitrate structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztUEAggMaxBitrate
(
SztUEAggMaxBitrate *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztUEAggMaxBitrate(param, ptr, mBuf)
SztUEAggMaxBitrate *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztUEAggMaxBitrate) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		SZUCHKUNPKPTR(cmUnpkSztBitRate, &param->uEaggregateMaxBitRateDL, ptr, mBuf); 
		SZUCHKUNPKPTR(cmUnpkSztBitRate, &param->uEaggregateMaxBitRateUL, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_UEAgg_MaxBitrates_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztUEAggMaxBitrate */



/*
* FUN : cmUnpkSzt_ExtnUE_S1AP_ID_pair_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnUE_S1AP_ID_pair_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnUE_S1AP_ID_pair_ExtIEsCls
(
Szt_ExtnUE_S1AP_ID_pair_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnUE_S1AP_ID_pair_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnUE_S1AP_ID_pair_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnUE_S1AP_ID_pair_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnUE_S1AP_ID_pair_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_UE_S1AP_ID_pair_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_UE_S1AP_ID_pair_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_UE_S1AP_ID_pair_ExtIEs
(
SztProtExtnField_UE_S1AP_ID_pair_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_UE_S1AP_ID_pair_ExtIEs(param, ptr, mBuf)
SztProtExtnField_UE_S1AP_ID_pair_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_UE_S1AP_ID_pair_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnUE_S1AP_ID_pair_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_UE_S1AP_ID_pair_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_UE_S1AP_ID_pair_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_UE_S1AP_ID_pair_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_UE_S1AP_ID_pair_ExtIEs
(
SztProtExtnCont_UE_S1AP_ID_pair_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_UE_S1AP_ID_pair_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_UE_S1AP_ID_pair_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_UE_S1AP_ID_pair_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_UE_S1AP_ID_pair_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_UE_S1AP_ID_pair_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_UE_S1AP_ID_pair_ExtIEs */



/*
* FUN : cmUnpkSztUE_S1AP_ID_pair
*  DESC: Function to Unpack SztUE_S1AP_ID_pair structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztUE_S1AP_ID_pair
(
SztUE_S1AP_ID_pair *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztUE_S1AP_ID_pair(param, ptr, mBuf)
SztUE_S1AP_ID_pair *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztUE_S1AP_ID_pair) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->mME_UE_S1AP_ID, mBuf); 
		CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->eNB_UE_S1AP_ID, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_UE_S1AP_ID_pair_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztUE_S1AP_ID_pair */



/*
* FUN : cmUnpkSztUE_S1AP_IDs
*  DESC: Function to Unpack SztUE_S1AP_IDs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztUE_S1AP_IDs
(
SztUE_S1AP_IDs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztUE_S1AP_IDs(param, ptr, mBuf)
SztUE_S1AP_IDs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztUE_S1AP_IDs) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case UE_S1AP_IDS_UE_S1AP_ID_PAIR :
				CMCHKUNPKPTR(cmUnpkSztUE_S1AP_ID_pair, &param->val.uE_S1AP_ID_pair, ptr, mBuf); 
				break;
			case UE_S1AP_IDS_MME_UE_S1AP_ID :
				CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->val.mME_UE_S1AP_ID, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztUE_S1AP_IDs */



/*
* FUN : cmUnpkSzt_ExtnUE_assocLogS1_ConItemExtIEsCls
*  DESC: Function to Unpack Szt_ExtnUE_assocLogS1_ConItemExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnUE_assocLogS1_ConItemExtIEsCls
(
Szt_ExtnUE_assocLogS1_ConItemExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnUE_assocLogS1_ConItemExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnUE_assocLogS1_ConItemExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnUE_assocLogS1_ConItemExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnUE_assocLogS1_ConItemExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_UE_assocLogS1_ConItemExtIEs
*  DESC: Function to Unpack SztProtExtnField_UE_assocLogS1_ConItemExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_UE_assocLogS1_ConItemExtIEs
(
SztProtExtnField_UE_assocLogS1_ConItemExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_UE_assocLogS1_ConItemExtIEs(param, ptr, mBuf)
SztProtExtnField_UE_assocLogS1_ConItemExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_UE_assocLogS1_ConItemExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnUE_assocLogS1_ConItemExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_UE_assocLogS1_ConItemExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_UE_assocLogS1_ConItemExtIEs
*  DESC: Function to Unpack SztProtExtnCont_UE_assocLogS1_ConItemExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_UE_assocLogS1_ConItemExtIEs
(
SztProtExtnCont_UE_assocLogS1_ConItemExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_UE_assocLogS1_ConItemExtIEs(param, ptr, mBuf)
SztProtExtnCont_UE_assocLogS1_ConItemExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_UE_assocLogS1_ConItemExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_UE_assocLogS1_ConItemExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_UE_assocLogS1_ConItemExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_UE_assocLogS1_ConItemExtIEs */



/*
* FUN : cmUnpkSztUE_assocLogS1_ConItem
*  DESC: Function to Unpack SztUE_assocLogS1_ConItem structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztUE_assocLogS1_ConItem
(
SztUE_assocLogS1_ConItem *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztUE_assocLogS1_ConItem(param, ptr, mBuf)
SztUE_assocLogS1_ConItem *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztUE_assocLogS1_ConItem) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->mME_UE_S1AP_ID, mBuf); 
		CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->eNB_UE_S1AP_ID, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_UE_assocLogS1_ConItemExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztUE_assocLogS1_ConItem */

#define cmUnpkSztUEIdentityIdxValue cmUnpkTknBStr32 


/*
* FUN : cmUnpkSztUEPagID
*  DESC: Function to Unpack SztUEPagID structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztUEPagID
(
SztUEPagID *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztUEPagID(param, ptr, mBuf)
SztUEPagID *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztUEPagID) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case UEPAGID_S_TMSI :
				CMCHKUNPKPTR(cmUnpkSztS_TMSI, &param->val.s_TMSI, ptr, mBuf); 
				break;
			case UEPAGID_IMSI :
				SZUCHKUNPKPTR(cmUnpkSztIMSI, &param->val.iMSI, ptr, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztUEPagID */

#define cmUnpkSztUERadioCapblty cmUnpkTknStrOSXL 


/*
* FUN : cmUnpkSzt_ExtnUESecurCapabilities_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnUESecurCapabilities_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnUESecurCapabilities_ExtIEsCls
(
Szt_ExtnUESecurCapabilities_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnUESecurCapabilities_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnUESecurCapabilities_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnUESecurCapabilities_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnUESecurCapabilities_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_UESecurCapabilities_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_UESecurCapabilities_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_UESecurCapabilities_ExtIEs
(
SztProtExtnField_UESecurCapabilities_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_UESecurCapabilities_ExtIEs(param, ptr, mBuf)
SztProtExtnField_UESecurCapabilities_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_UESecurCapabilities_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnUESecurCapabilities_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_UESecurCapabilities_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_UESecurCapabilities_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_UESecurCapabilities_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_UESecurCapabilities_ExtIEs
(
SztProtExtnCont_UESecurCapabilities_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_UESecurCapabilities_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_UESecurCapabilities_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_UESecurCapabilities_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_UESecurCapabilities_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_UESecurCapabilities_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_UESecurCapabilities_ExtIEs */



/*
* FUN : cmUnpkSztUESecurCapabilities
*  DESC: Function to Unpack SztUESecurCapabilities structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztUESecurCapabilities
(
SztUESecurCapabilities *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztUESecurCapabilities(param, ptr, mBuf)
SztUESecurCapabilities *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztUESecurCapabilities) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztEncryptionAlgorithms, &param->encryptionAlgorithms, mBuf); 
		CMCHKUNPK(cmUnpkSztIntegrityProtectionAlgorithms, &param->integrityProtectionAlgorithms, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_UESecurCapabilities_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztUESecurCapabilities */

#define cmUnpkSztVoiceSupportMatchIndicator cmUnpkTknU32



/*
* FUN : cmUnpkSztWarningAreaLst
*  DESC: Function to Unpack SztWarningAreaLst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztWarningAreaLst
(
SztWarningAreaLst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztWarningAreaLst(param, ptr, mBuf)
SztWarningAreaLst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztWarningAreaLst) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case WARNINGAREALST_CELLIDLST :
				CMCHKUNPKPTR(cmUnpkSztECGILst, &param->val.cellIDLst, ptr, mBuf); 
				break;
			case WARNINGAREALST_TRACKINGAREALSTFORWARNING :
				CMCHKUNPKPTR(cmUnpkSztTAILstforWarning, &param->val.trackingAreaLstforWarning, ptr, mBuf); 
				break;
			case WARNINGAREALST_EMERGENCYAREAIDLST :
				CMCHKUNPKPTR(cmUnpkSztEmergencyAreaIDLst, &param->val.emergencyAreaIDLst, ptr, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztWarningAreaLst */

#define cmUnpkSztWarningTyp cmUnpkTknStr4 
#define cmUnpkSztWarningSecurInfo cmUnpkTknStrOSXL 
#define cmUnpkSztWarningMsgContents cmUnpkTknStrOSXL 


/*
* FUN : cmUnpkSzt_ValueHovrReqdIEsCls
*  DESC: Function to Unpack Szt_ValueHovrReqdIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueHovrReqdIEsCls
(
Szt_ValueHovrReqdIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueHovrReqdIEsCls(param, val, ptr, mBuf)
Szt_ValueHovrReqdIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueHovrReqdIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_HovrTyp:
			CMCHKUNPK(cmUnpkSztHovrTyp, &param->u.sztHovrTyp, mBuf); 
			break;
		case Sztid_Cause:
			CMCHKUNPKPTR(cmUnpkSztCause, &param->u.sztCause, ptr, mBuf);
			break;
		case Sztid_TgetID:
			CMCHKUNPKPTR(cmUnpkSztTgetID, &param->u.sztTgetID, ptr, mBuf);
			break;
		case Sztid_Direct_Fwding_Path_Avlblty:
			CMCHKUNPK(cmUnpkSztDirect_Fwding_Path_Avlblty, &param->u.sztDirect_Fwding_Path_Avlblty, mBuf); 
			break;
		case Sztid_SRVCCHOInd:
			CMCHKUNPK(cmUnpkSztSRVCCHOInd, &param->u.sztSRVCCHOInd, mBuf); 
			break;
		case Sztid_Src_ToTget_TprntCont:
			SZUCHKUNPKPTR(cmUnpkSztSrc_ToTget_TprntCont, &param->u.sztid_Src_ToTget_TprntCont, ptr, mBuf); 
			break;
		case Sztid_Src_ToTget_TprntCont_Secondary:
			SZUCHKUNPKPTR(cmUnpkSztSrc_ToTget_TprntCont, &param->u.sztid_Src_ToTget_TprntCont_Secondary, ptr, mBuf); 
			break;
		case Sztid_MSClassmark2:
			SZUCHKUNPKPTR(cmUnpkSztMSClassmark2, &param->u.sztMSClassmark2, ptr, mBuf); 
			break;
		case Sztid_MSClassmark3:
			SZUCHKUNPKPTR(cmUnpkSztMSClassmark3, &param->u.sztMSClassmark3, ptr, mBuf); 
			break;
		case Sztid_CSG_Id:
			CMCHKUNPK(cmUnpkSztCSG_Id, &param->u.sztCSG_Id, mBuf); 
			break;
		case Sztid_CellAccessMode:
			CMCHKUNPK(cmUnpkSztCellAccessMode, &param->u.sztCellAccessMode, mBuf); 
			break;
		case Sztid_PS_ServiceNotAvailable:
			CMCHKUNPK(cmUnpkSztPS_ServiceNotAvailable, &param->u.sztPS_ServiceNotAvailable, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueHovrReqdIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_HovrReqdIEs
*  DESC: Function to Unpack SztProtIE_Field_HovrReqdIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_HovrReqdIEs
(
SztProtIE_Field_HovrReqdIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_HovrReqdIEs(param, ptr, mBuf)
SztProtIE_Field_HovrReqdIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_HovrReqdIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueHovrReqdIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_HovrReqdIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_HovrReqdIEs
*  DESC: Function to Unpack SztProtIE_Cont_HovrReqdIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_HovrReqdIEs
(
SztProtIE_Cont_HovrReqdIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_HovrReqdIEs(param, ptr, mBuf)
SztProtIE_Cont_HovrReqdIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_HovrReqdIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_HovrReqdIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_HovrReqdIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_HovrReqdIEs */



/*
* FUN : cmUnpkSztHovrReqd
*  DESC: Function to Unpack SztHovrReqd structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztHovrReqd
(
SztHovrReqd *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztHovrReqd(param, ptr, mBuf)
SztHovrReqd *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztHovrReqd) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_HovrReqdIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztHovrReqd */



/*
* FUN : cmUnpkSzt_ExtnE_RABDataFwdingItem_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnE_RABDataFwdingItem_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnE_RABDataFwdingItem_ExtIEsCls
(
Szt_ExtnE_RABDataFwdingItem_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnE_RABDataFwdingItem_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnE_RABDataFwdingItem_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnE_RABDataFwdingItem_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnE_RABDataFwdingItem_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_E_RABDataFwdingItem_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_E_RABDataFwdingItem_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABDataFwdingItem_ExtIEs
(
SztProtExtnField_E_RABDataFwdingItem_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABDataFwdingItem_ExtIEs(param, ptr, mBuf)
SztProtExtnField_E_RABDataFwdingItem_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_E_RABDataFwdingItem_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnE_RABDataFwdingItem_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_E_RABDataFwdingItem_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_E_RABDataFwdingItem_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_E_RABDataFwdingItem_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABDataFwdingItem_ExtIEs
(
SztProtExtnCont_E_RABDataFwdingItem_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABDataFwdingItem_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_E_RABDataFwdingItem_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_E_RABDataFwdingItem_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_E_RABDataFwdingItem_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_E_RABDataFwdingItem_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_E_RABDataFwdingItem_ExtIEs */



/*
* FUN : cmUnpkSztE_RABDataFwdingItem
*  DESC: Function to Unpack SztE_RABDataFwdingItem structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABDataFwdingItem
(
SztE_RABDataFwdingItem *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABDataFwdingItem(param, ptr, mBuf)
SztE_RABDataFwdingItem *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztE_RABDataFwdingItem) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztTportLyrAddr, &param->dL_transportLyrAddr, ptr, mBuf); 
		SZUCHKUNPKPTR(cmUnpkSztGTP_TEID, &param->dL_gTP_TEID, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztTportLyrAddr, &param->uL_TportLyrAddr, ptr, mBuf); 
		SZUCHKUNPKPTR(cmUnpkSztGTP_TEID, &param->uL_GTP_TEID, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_E_RABDataFwdingItem_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztE_RABDataFwdingItem */



/*
* FUN : cmUnpkSzt_ValueE_RABDataFwdingItemIEsCls
*  DESC: Function to Unpack Szt_ValueE_RABDataFwdingItemIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueE_RABDataFwdingItemIEsCls
(
Szt_ValueE_RABDataFwdingItemIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueE_RABDataFwdingItemIEsCls(param, val, ptr, mBuf)
Szt_ValueE_RABDataFwdingItemIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueE_RABDataFwdingItemIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABDataFwdingItem:
			CMCHKUNPKPTR(cmUnpkSztE_RABDataFwdingItem, &param->u.sztE_RABDataFwdingItem, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueE_RABDataFwdingItemIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_E_RABDataFwdingItemIEs
*  DESC: Function to Unpack SztProtIE_Field_E_RABDataFwdingItemIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABDataFwdingItemIEs
(
SztProtIE_Field_E_RABDataFwdingItemIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABDataFwdingItemIEs(param, ptr, mBuf)
SztProtIE_Field_E_RABDataFwdingItemIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_E_RABDataFwdingItemIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueE_RABDataFwdingItemIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_E_RABDataFwdingItemIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmUnpkSztProtIE_SingleCont_E_RABDataFwdingItemIEs cmUnpkSztProtIE_Field_E_RABDataFwdingItemIEs


/*
* FUN : cmUnpkSztProtIE_ContLst_E_RABDataFwdingItemIEs
*  DESC: Function to Unpack SztProtIE_ContLst_E_RABDataFwdingItemIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_ContLst_E_RABDataFwdingItemIEs
(
SztProtIE_ContLst_E_RABDataFwdingItemIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_ContLst_E_RABDataFwdingItemIEs(param, ptr, mBuf)
SztProtIE_ContLst_E_RABDataFwdingItemIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_ContLst_E_RABDataFwdingItemIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_SingleCont_E_RABDataFwdingItemIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_SingleCont_E_RABDataFwdingItemIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_ContLst_E_RABDataFwdingItemIEs */

/* Element ------------- E-RAB-IE-ContainerList ------------ */
#define cmUnpkSztE_RAB_IE_ContLst_E_RABDataFwdingItemIEs cmUnpkSztProtIE_ContLst_E_RABDataFwdingItemIEs
/* Element ------------- E-RABSubjecttoDataForwardingList ------------ */
#define cmUnpkSztE_RABSubjtoDataFwdingLst cmUnpkSztE_RAB_IE_ContLst_E_RABDataFwdingItemIEs


/*
* FUN : cmUnpkSzt_ValueHovrCmmdIEsCls
*  DESC: Function to Unpack Szt_ValueHovrCmmdIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueHovrCmmdIEsCls
(
Szt_ValueHovrCmmdIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueHovrCmmdIEsCls(param, val, ptr, mBuf)
Szt_ValueHovrCmmdIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueHovrCmmdIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_HovrTyp:
			CMCHKUNPK(cmUnpkSztHovrTyp, &param->u.sztHovrTyp, mBuf); 
			break;
		case Sztid_NASSecurParamsfromE_UTRAN:
			SZUCHKUNPKPTR(cmUnpkSztNASSecurParamsfromE_UTRAN, &param->u.sztNASSecurParamsfromE_UTRAN, ptr, mBuf); 
			break;
		case Sztid_E_RABSubjtoDataFwdingLst:
			CMCHKUNPKPTR(cmUnpkSztE_RABSubjtoDataFwdingLst, &param->u.sztE_RABSubjtoDataFwdingLst, ptr, mBuf);
			break;
		case Sztid_E_RABtoRlsLstHOCmd:
			CMCHKUNPKPTR(cmUnpkSztE_RABLst, &param->u.sztE_RABLst, ptr, mBuf);
			break;
		case Sztid_Tget_ToSrc_TprntCont:
			SZUCHKUNPKPTR(cmUnpkSztTget_ToSrc_TprntCont, &param->u.sztid_Tget_ToSrc_TprntCont, ptr, mBuf); 
			break;
		case Sztid_Tget_ToSrc_TprntCont_Secondary:
			SZUCHKUNPKPTR(cmUnpkSztTget_ToSrc_TprntCont, &param->u.sztid_Tget_ToSrc_TprntCont_Secondary, ptr, mBuf); 
			break;
		case Sztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkSztCriticalityDiag, &param->u.sztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueHovrCmmdIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_HovrCmmdIEs
*  DESC: Function to Unpack SztProtIE_Field_HovrCmmdIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_HovrCmmdIEs
(
SztProtIE_Field_HovrCmmdIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_HovrCmmdIEs(param, ptr, mBuf)
SztProtIE_Field_HovrCmmdIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_HovrCmmdIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueHovrCmmdIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_HovrCmmdIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_HovrCmmdIEs
*  DESC: Function to Unpack SztProtIE_Cont_HovrCmmdIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_HovrCmmdIEs
(
SztProtIE_Cont_HovrCmmdIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_HovrCmmdIEs(param, ptr, mBuf)
SztProtIE_Cont_HovrCmmdIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_HovrCmmdIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_HovrCmmdIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_HovrCmmdIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_HovrCmmdIEs */



/*
* FUN : cmUnpkSztHovrCmmd
*  DESC: Function to Unpack SztHovrCmmd structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztHovrCmmd
(
SztHovrCmmd *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztHovrCmmd(param, ptr, mBuf)
SztHovrCmmd *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztHovrCmmd) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_HovrCmmdIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztHovrCmmd */



/*
* FUN : cmUnpkSzt_ValueHovrPrepFailIEsCls
*  DESC: Function to Unpack Szt_ValueHovrPrepFailIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueHovrPrepFailIEsCls
(
Szt_ValueHovrPrepFailIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueHovrPrepFailIEsCls(param, val, ptr, mBuf)
Szt_ValueHovrPrepFailIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueHovrPrepFailIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_Cause:
			CMCHKUNPKPTR(cmUnpkSztCause, &param->u.sztCause, ptr, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkSztCriticalityDiag, &param->u.sztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueHovrPrepFailIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_HovrPrepFailIEs
*  DESC: Function to Unpack SztProtIE_Field_HovrPrepFailIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_HovrPrepFailIEs
(
SztProtIE_Field_HovrPrepFailIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_HovrPrepFailIEs(param, ptr, mBuf)
SztProtIE_Field_HovrPrepFailIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_HovrPrepFailIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueHovrPrepFailIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_HovrPrepFailIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_HovrPrepFailIEs
*  DESC: Function to Unpack SztProtIE_Cont_HovrPrepFailIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_HovrPrepFailIEs
(
SztProtIE_Cont_HovrPrepFailIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_HovrPrepFailIEs(param, ptr, mBuf)
SztProtIE_Cont_HovrPrepFailIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_HovrPrepFailIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_HovrPrepFailIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_HovrPrepFailIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_HovrPrepFailIEs */



/*
* FUN : cmUnpkSztHovrPrepFail
*  DESC: Function to Unpack SztHovrPrepFail structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztHovrPrepFail
(
SztHovrPrepFail *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztHovrPrepFail(param, ptr, mBuf)
SztHovrPrepFail *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztHovrPrepFail) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_HovrPrepFailIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztHovrPrepFail */



/*
* FUN : cmUnpkSzt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls
(
Szt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls) 
	
	switch (val)
	{
		case Sztid_Data_Fwding_Not_Possible:
			CMCHKUNPK(cmUnpkSztData_Fwding_Not_Possible, &param->u.sztData_Fwding_Not_Possible, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs
(
SztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs(param, ptr, mBuf)
SztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnE_RABToBeSetupItemHOReq_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs
(
SztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_E_RABToBeSetupItemHOReq_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs */



/*
* FUN : cmUnpkSztE_RABToBeSetupItemHOReq
*  DESC: Function to Unpack SztE_RABToBeSetupItemHOReq structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABToBeSetupItemHOReq
(
SztE_RABToBeSetupItemHOReq *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABToBeSetupItemHOReq(param, ptr, mBuf)
SztE_RABToBeSetupItemHOReq *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztE_RABToBeSetupItemHOReq) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztTportLyrAddr, &param->transportLyrAddr, ptr, mBuf); 
		SZUCHKUNPKPTR(cmUnpkSztGTP_TEID, &param->gTP_TEID, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztE_RABLvlQoSParams, &param->e_RABlevelQosParams, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_E_RABToBeSetupItemHOReq_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztE_RABToBeSetupItemHOReq */



/*
* FUN : cmUnpkSzt_ValueE_RABToBeSetupItemHOReqIEsCls
*  DESC: Function to Unpack Szt_ValueE_RABToBeSetupItemHOReqIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueE_RABToBeSetupItemHOReqIEsCls
(
Szt_ValueE_RABToBeSetupItemHOReqIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueE_RABToBeSetupItemHOReqIEsCls(param, val, ptr, mBuf)
Szt_ValueE_RABToBeSetupItemHOReqIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueE_RABToBeSetupItemHOReqIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABToBeSetupItemHOReq:
			CMCHKUNPKPTR(cmUnpkSztE_RABToBeSetupItemHOReq, &param->u.sztE_RABToBeSetupItemHOReq, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueE_RABToBeSetupItemHOReqIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_E_RABToBeSetupItemHOReqIEs
*  DESC: Function to Unpack SztProtIE_Field_E_RABToBeSetupItemHOReqIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABToBeSetupItemHOReqIEs
(
SztProtIE_Field_E_RABToBeSetupItemHOReqIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABToBeSetupItemHOReqIEs(param, ptr, mBuf)
SztProtIE_Field_E_RABToBeSetupItemHOReqIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_E_RABToBeSetupItemHOReqIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueE_RABToBeSetupItemHOReqIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_E_RABToBeSetupItemHOReqIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmUnpkSztProtIE_SingleCont_E_RABToBeSetupItemHOReqIEs cmUnpkSztProtIE_Field_E_RABToBeSetupItemHOReqIEs


/*
* FUN : cmUnpkSztProtIE_ContLst_E_RABToBeSetupItemHOReqIEs
*  DESC: Function to Unpack SztProtIE_ContLst_E_RABToBeSetupItemHOReqIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_ContLst_E_RABToBeSetupItemHOReqIEs
(
SztProtIE_ContLst_E_RABToBeSetupItemHOReqIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_ContLst_E_RABToBeSetupItemHOReqIEs(param, ptr, mBuf)
SztProtIE_ContLst_E_RABToBeSetupItemHOReqIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_ContLst_E_RABToBeSetupItemHOReqIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_SingleCont_E_RABToBeSetupItemHOReqIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_SingleCont_E_RABToBeSetupItemHOReqIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_ContLst_E_RABToBeSetupItemHOReqIEs */

/* Element ------------- E-RAB-IE-ContainerList ------------ */
#define cmUnpkSztE_RAB_IE_ContLst_E_RABToBeSetupItemHOReqIEs cmUnpkSztProtIE_ContLst_E_RABToBeSetupItemHOReqIEs
/* Element ------------- E-RABToBeSetupListHOReq ------------ */
#define cmUnpkSztE_RABToBeSetupLstHOReq cmUnpkSztE_RAB_IE_ContLst_E_RABToBeSetupItemHOReqIEs


/*
* FUN : cmUnpkSzt_ValueHovrRqstIEsCls
*  DESC: Function to Unpack Szt_ValueHovrRqstIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueHovrRqstIEsCls
(
Szt_ValueHovrRqstIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueHovrRqstIEsCls(param, val, ptr, mBuf)
Szt_ValueHovrRqstIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueHovrRqstIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztid_MME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_HovrTyp:
			CMCHKUNPK(cmUnpkSztHovrTyp, &param->u.sztHovrTyp, mBuf); 
			break;
		case Sztid_Cause:
			CMCHKUNPKPTR(cmUnpkSztCause, &param->u.sztCause, ptr, mBuf);
			break;
		case Sztid_uEaggregateMaxBitrate:
			CMCHKUNPKPTR(cmUnpkSztUEAggMaxBitrate, &param->u.sztUEAggMaxBitrate, ptr, mBuf);
			break;
		case Sztid_E_RABToBeSetupLstHOReq:
			CMCHKUNPKPTR(cmUnpkSztE_RABToBeSetupLstHOReq, &param->u.sztE_RABToBeSetupLstHOReq, ptr, mBuf);
			break;
		case Sztid_Src_ToTget_TprntCont:
			SZUCHKUNPKPTR(cmUnpkSztSrc_ToTget_TprntCont, &param->u.sztSrc_ToTget_TprntCont, ptr, mBuf); 
			break;
		case Sztid_UESecurCapabilities:
			CMCHKUNPKPTR(cmUnpkSztUESecurCapabilities, &param->u.sztUESecurCapabilities, ptr, mBuf);
			break;
		case Sztid_HovrRestrnLst:
			CMCHKUNPKPTR(cmUnpkSztHovrRestrnLst, &param->u.sztHovrRestrnLst, ptr, mBuf);
			break;
		case Sztid_TraceActvn:
			CMCHKUNPKPTR(cmUnpkSztTraceActvn, &param->u.sztTraceActvn, ptr, mBuf);
			break;
		case Sztid_RqstTyp:
			CMCHKUNPKPTR(cmUnpkSztRqstTyp, &param->u.sztRqstTyp, ptr, mBuf);
			break;
		case Sztid_SRVCCOperationPossible:
			CMCHKUNPK(cmUnpkSztSRVCCOperationPossible, &param->u.sztSRVCCOperationPossible, mBuf); 
			break;
		case Sztid_SecurCntxt:
			CMCHKUNPKPTR(cmUnpkSztSecurCntxt, &param->u.sztSecurCntxt, ptr, mBuf);
			break;
		case Sztid_NASSecurParamstoE_UTRAN:
			SZUCHKUNPKPTR(cmUnpkSztNASSecurParamstoE_UTRAN, &param->u.sztNASSecurParamstoE_UTRAN, ptr, mBuf); 
			break;
		case Sztid_CSG_Id:
			CMCHKUNPK(cmUnpkSztCSG_Id, &param->u.sztCSG_Id, mBuf); 
			break;
		case Sztid_CSGMembershipStatus:
			CMCHKUNPK(cmUnpkSztCSGMembershipStatus, &param->u.sztCSGMembershipStatus, mBuf); 
			break;
		case Sztid_GUMMEI_ID:
			CMCHKUNPKPTR(cmUnpkSztGUMMEI, &param->u.sztGUMMEI, ptr, mBuf);
			break;
		case Sztid_MME_UE_S1AP_ID_2:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztid_MME_UE_S1AP_ID_2, mBuf); 
			break;
		case Sztid_ManagementBasedMDTAllowed:
			CMCHKUNPK(cmUnpkSztManagementBasedMDTAllowed, &param->u.sztManagementBasedMDTAllowed, mBuf); 
			break;
		case Sztid_ManagementBasedMDTPLMNLst:
			CMCHKUNPKPTR(cmUnpkSztMDTPLMNLst, &param->u.sztMDTPLMNLst, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueHovrRqstIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_HovrRqstIEs
*  DESC: Function to Unpack SztProtIE_Field_HovrRqstIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_HovrRqstIEs
(
SztProtIE_Field_HovrRqstIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_HovrRqstIEs(param, ptr, mBuf)
SztProtIE_Field_HovrRqstIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_HovrRqstIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueHovrRqstIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_HovrRqstIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_HovrRqstIEs
*  DESC: Function to Unpack SztProtIE_Cont_HovrRqstIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_HovrRqstIEs
(
SztProtIE_Cont_HovrRqstIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_HovrRqstIEs(param, ptr, mBuf)
SztProtIE_Cont_HovrRqstIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_HovrRqstIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_HovrRqstIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_HovrRqstIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_HovrRqstIEs */



/*
* FUN : cmUnpkSztHovrRqst
*  DESC: Function to Unpack SztHovrRqst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztHovrRqst
(
SztHovrRqst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztHovrRqst(param, ptr, mBuf)
SztHovrRqst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztHovrRqst) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_HovrRqstIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztHovrRqst */



/*
* FUN : cmUnpkSzt_ExtnE_RABAdmtdItem_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnE_RABAdmtdItem_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnE_RABAdmtdItem_ExtIEsCls
(
Szt_ExtnE_RABAdmtdItem_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnE_RABAdmtdItem_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnE_RABAdmtdItem_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnE_RABAdmtdItem_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnE_RABAdmtdItem_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_E_RABAdmtdItem_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_E_RABAdmtdItem_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABAdmtdItem_ExtIEs
(
SztProtExtnField_E_RABAdmtdItem_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABAdmtdItem_ExtIEs(param, ptr, mBuf)
SztProtExtnField_E_RABAdmtdItem_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_E_RABAdmtdItem_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnE_RABAdmtdItem_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_E_RABAdmtdItem_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_E_RABAdmtdItem_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_E_RABAdmtdItem_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABAdmtdItem_ExtIEs
(
SztProtExtnCont_E_RABAdmtdItem_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABAdmtdItem_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_E_RABAdmtdItem_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_E_RABAdmtdItem_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_E_RABAdmtdItem_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_E_RABAdmtdItem_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_E_RABAdmtdItem_ExtIEs */



/*
* FUN : cmUnpkSztE_RABAdmtdItem
*  DESC: Function to Unpack SztE_RABAdmtdItem structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABAdmtdItem
(
SztE_RABAdmtdItem *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABAdmtdItem(param, ptr, mBuf)
SztE_RABAdmtdItem *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztE_RABAdmtdItem) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztTportLyrAddr, &param->transportLyrAddr, ptr, mBuf); 
		SZUCHKUNPKPTR(cmUnpkSztGTP_TEID, &param->gTP_TEID, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztTportLyrAddr, &param->dL_transportLyrAddr, ptr, mBuf); 
		SZUCHKUNPKPTR(cmUnpkSztGTP_TEID, &param->dL_gTP_TEID, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztTportLyrAddr, &param->uL_TportLyrAddr, ptr, mBuf); 
		SZUCHKUNPKPTR(cmUnpkSztGTP_TEID, &param->uL_GTP_TEID, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_E_RABAdmtdItem_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztE_RABAdmtdItem */



/*
* FUN : cmUnpkSzt_ValueE_RABAdmtdItemIEsCls
*  DESC: Function to Unpack Szt_ValueE_RABAdmtdItemIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueE_RABAdmtdItemIEsCls
(
Szt_ValueE_RABAdmtdItemIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueE_RABAdmtdItemIEsCls(param, val, ptr, mBuf)
Szt_ValueE_RABAdmtdItemIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueE_RABAdmtdItemIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABAdmtdItem:
			CMCHKUNPKPTR(cmUnpkSztE_RABAdmtdItem, &param->u.sztE_RABAdmtdItem, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueE_RABAdmtdItemIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_E_RABAdmtdItemIEs
*  DESC: Function to Unpack SztProtIE_Field_E_RABAdmtdItemIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABAdmtdItemIEs
(
SztProtIE_Field_E_RABAdmtdItemIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABAdmtdItemIEs(param, ptr, mBuf)
SztProtIE_Field_E_RABAdmtdItemIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_E_RABAdmtdItemIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueE_RABAdmtdItemIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_E_RABAdmtdItemIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmUnpkSztProtIE_SingleCont_E_RABAdmtdItemIEs cmUnpkSztProtIE_Field_E_RABAdmtdItemIEs


/*
* FUN : cmUnpkSztProtIE_ContLst_E_RABAdmtdItemIEs
*  DESC: Function to Unpack SztProtIE_ContLst_E_RABAdmtdItemIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_ContLst_E_RABAdmtdItemIEs
(
SztProtIE_ContLst_E_RABAdmtdItemIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_ContLst_E_RABAdmtdItemIEs(param, ptr, mBuf)
SztProtIE_ContLst_E_RABAdmtdItemIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_ContLst_E_RABAdmtdItemIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_SingleCont_E_RABAdmtdItemIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_SingleCont_E_RABAdmtdItemIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_ContLst_E_RABAdmtdItemIEs */

/* Element ------------- E-RAB-IE-ContainerList ------------ */
#define cmUnpkSztE_RAB_IE_ContLst_E_RABAdmtdItemIEs cmUnpkSztProtIE_ContLst_E_RABAdmtdItemIEs
/* Element ------------- E-RABAdmittedList ------------ */
#define cmUnpkSztE_RABAdmtdLst cmUnpkSztE_RAB_IE_ContLst_E_RABAdmtdItemIEs


/*
* FUN : cmUnpkSzt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls
*  DESC: Function to Unpack Szt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls
(
Szt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs
*  DESC: Function to Unpack SztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs
(
SztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs(param, ptr, mBuf)
SztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnE_RABFailedToSetupItemHOReqAckExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs
*  DESC: Function to Unpack SztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs
(
SztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs(param, ptr, mBuf)
SztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_E_RABFailedToSetupItemHOReqAckExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs */



/*
* FUN : cmUnpkSztE_RABFailedToSetupItemHOReqAck
*  DESC: Function to Unpack SztE_RABFailedToSetupItemHOReqAck structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABFailedToSetupItemHOReqAck
(
SztE_RABFailedToSetupItemHOReqAck *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABFailedToSetupItemHOReqAck(param, ptr, mBuf)
SztE_RABFailedToSetupItemHOReqAck *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztE_RABFailedToSetupItemHOReqAck) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztCause, &param->cause, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_E_RABFailedToSetupItemHOReqAckExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztE_RABFailedToSetupItemHOReqAck */



/*
* FUN : cmUnpkSzt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls
*  DESC: Function to Unpack Szt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls
(
Szt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls(param, val, ptr, mBuf)
Szt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABFailedtoSetupItemHOReqAck:
			CMCHKUNPKPTR(cmUnpkSztE_RABFailedToSetupItemHOReqAck, &param->u.sztE_RABFailedToSetupItemHOReqAck, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs
*  DESC: Function to Unpack SztProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs
(
SztProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs(param, ptr, mBuf)
SztProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueE_RABFailedtoSetupItemHOReqAckIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmUnpkSztProtIE_SingleCont_E_RABFailedtoSetupItemHOReqAckIEs cmUnpkSztProtIE_Field_E_RABFailedtoSetupItemHOReqAckIEs


/*
* FUN : cmUnpkSztProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs
*  DESC: Function to Unpack SztProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs
(
SztProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs(param, ptr, mBuf)
SztProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_SingleCont_E_RABFailedtoSetupItemHOReqAckIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_SingleCont_E_RABFailedtoSetupItemHOReqAckIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs */

/* Element ------------- E-RAB-IE-ContainerList ------------ */
#define cmUnpkSztE_RAB_IE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs cmUnpkSztProtIE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs
/* Element ------------- E-RABFailedtoSetupListHOReqAck ------------ */
#define cmUnpkSztE_RABFailedtoSetupLstHOReqAck cmUnpkSztE_RAB_IE_ContLst_E_RABFailedtoSetupItemHOReqAckIEs


/*
* FUN : cmUnpkSzt_ValueHovrRqstAckgIEsCls
*  DESC: Function to Unpack Szt_ValueHovrRqstAckgIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueHovrRqstAckgIEsCls
(
Szt_ValueHovrRqstAckgIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueHovrRqstAckgIEsCls(param, val, ptr, mBuf)
Szt_ValueHovrRqstAckgIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueHovrRqstAckgIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_E_RABAdmtdLst:
			CMCHKUNPKPTR(cmUnpkSztE_RABAdmtdLst, &param->u.sztE_RABAdmtdLst, ptr, mBuf);
			break;
		case Sztid_E_RABFailedToSetupLstHOReqAck:
			CMCHKUNPKPTR(cmUnpkSztE_RABFailedtoSetupLstHOReqAck, &param->u.sztE_RABFailedtoSetupLstHOReqAck, ptr, mBuf);
			break;
		case Sztid_Tget_ToSrc_TprntCont:
			SZUCHKUNPKPTR(cmUnpkSztTget_ToSrc_TprntCont, &param->u.sztTget_ToSrc_TprntCont, ptr, mBuf); 
			break;
		case Sztid_CSG_Id:
			CMCHKUNPK(cmUnpkSztCSG_Id, &param->u.sztCSG_Id, mBuf); 
			break;
		case Sztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkSztCriticalityDiag, &param->u.sztCriticalityDiag, ptr, mBuf);
			break;
		case Sztid_CellAccessMode:
			CMCHKUNPK(cmUnpkSztCellAccessMode, &param->u.sztCellAccessMode, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueHovrRqstAckgIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_HovrRqstAckgIEs
*  DESC: Function to Unpack SztProtIE_Field_HovrRqstAckgIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_HovrRqstAckgIEs
(
SztProtIE_Field_HovrRqstAckgIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_HovrRqstAckgIEs(param, ptr, mBuf)
SztProtIE_Field_HovrRqstAckgIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_HovrRqstAckgIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueHovrRqstAckgIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_HovrRqstAckgIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_HovrRqstAckgIEs
*  DESC: Function to Unpack SztProtIE_Cont_HovrRqstAckgIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_HovrRqstAckgIEs
(
SztProtIE_Cont_HovrRqstAckgIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_HovrRqstAckgIEs(param, ptr, mBuf)
SztProtIE_Cont_HovrRqstAckgIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_HovrRqstAckgIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_HovrRqstAckgIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_HovrRqstAckgIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_HovrRqstAckgIEs */



/*
* FUN : cmUnpkSztHovrRqstAckg
*  DESC: Function to Unpack SztHovrRqstAckg structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztHovrRqstAckg
(
SztHovrRqstAckg *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztHovrRqstAckg(param, ptr, mBuf)
SztHovrRqstAckg *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztHovrRqstAckg) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_HovrRqstAckgIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztHovrRqstAckg */



/*
* FUN : cmUnpkSzt_ValueHovrFailIEsCls
*  DESC: Function to Unpack Szt_ValueHovrFailIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueHovrFailIEsCls
(
Szt_ValueHovrFailIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueHovrFailIEsCls(param, val, ptr, mBuf)
Szt_ValueHovrFailIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueHovrFailIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_Cause:
			CMCHKUNPKPTR(cmUnpkSztCause, &param->u.sztCause, ptr, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkSztCriticalityDiag, &param->u.sztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueHovrFailIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_HovrFailIEs
*  DESC: Function to Unpack SztProtIE_Field_HovrFailIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_HovrFailIEs
(
SztProtIE_Field_HovrFailIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_HovrFailIEs(param, ptr, mBuf)
SztProtIE_Field_HovrFailIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_HovrFailIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueHovrFailIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_HovrFailIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_HovrFailIEs
*  DESC: Function to Unpack SztProtIE_Cont_HovrFailIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_HovrFailIEs
(
SztProtIE_Cont_HovrFailIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_HovrFailIEs(param, ptr, mBuf)
SztProtIE_Cont_HovrFailIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_HovrFailIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_HovrFailIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_HovrFailIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_HovrFailIEs */



/*
* FUN : cmUnpkSztHovrFail
*  DESC: Function to Unpack SztHovrFail structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztHovrFail
(
SztHovrFail *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztHovrFail(param, ptr, mBuf)
SztHovrFail *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztHovrFail) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_HovrFailIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztHovrFail */



/*
* FUN : cmUnpkSzt_ValueHovrNtfyIEsCls
*  DESC: Function to Unpack Szt_ValueHovrNtfyIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueHovrNtfyIEsCls
(
Szt_ValueHovrNtfyIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueHovrNtfyIEsCls(param, val, ptr, mBuf)
Szt_ValueHovrNtfyIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueHovrNtfyIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_EUTRAN_CGI:
			CMCHKUNPKPTR(cmUnpkSztEUTRAN_CGI, &param->u.sztEUTRAN_CGI, ptr, mBuf);
			break;
		case Sztid_TAI:
			CMCHKUNPKPTR(cmUnpkSztTAI, &param->u.sztTAI, ptr, mBuf);
			break;
		case Sztid_Tunnel_Inform_for_BBF:
			CMCHKUNPKPTR(cmUnpkSztTunnelInform, &param->u.sztTunnelInform, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueHovrNtfyIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_HovrNtfyIEs
*  DESC: Function to Unpack SztProtIE_Field_HovrNtfyIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_HovrNtfyIEs
(
SztProtIE_Field_HovrNtfyIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_HovrNtfyIEs(param, ptr, mBuf)
SztProtIE_Field_HovrNtfyIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_HovrNtfyIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueHovrNtfyIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_HovrNtfyIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_HovrNtfyIEs
*  DESC: Function to Unpack SztProtIE_Cont_HovrNtfyIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_HovrNtfyIEs
(
SztProtIE_Cont_HovrNtfyIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_HovrNtfyIEs(param, ptr, mBuf)
SztProtIE_Cont_HovrNtfyIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_HovrNtfyIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_HovrNtfyIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_HovrNtfyIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_HovrNtfyIEs */



/*
* FUN : cmUnpkSztHovrNtfy
*  DESC: Function to Unpack SztHovrNtfy structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztHovrNtfy
(
SztHovrNtfy *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztHovrNtfy(param, ptr, mBuf)
SztHovrNtfy *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztHovrNtfy) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_HovrNtfyIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztHovrNtfy */



/*
* FUN : cmUnpkSzt_ExtnE_RABToBeSwedDLItem_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnE_RABToBeSwedDLItem_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnE_RABToBeSwedDLItem_ExtIEsCls
(
Szt_ExtnE_RABToBeSwedDLItem_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnE_RABToBeSwedDLItem_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnE_RABToBeSwedDLItem_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnE_RABToBeSwedDLItem_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnE_RABToBeSwedDLItem_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_E_RABToBeSwedDLItem_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_E_RABToBeSwedDLItem_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABToBeSwedDLItem_ExtIEs
(
SztProtExtnField_E_RABToBeSwedDLItem_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABToBeSwedDLItem_ExtIEs(param, ptr, mBuf)
SztProtExtnField_E_RABToBeSwedDLItem_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_E_RABToBeSwedDLItem_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnE_RABToBeSwedDLItem_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_E_RABToBeSwedDLItem_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs
(
SztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_E_RABToBeSwedDLItem_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_E_RABToBeSwedDLItem_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs */



/*
* FUN : cmUnpkSztE_RABToBeSwedDLItem
*  DESC: Function to Unpack SztE_RABToBeSwedDLItem structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABToBeSwedDLItem
(
SztE_RABToBeSwedDLItem *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABToBeSwedDLItem(param, ptr, mBuf)
SztE_RABToBeSwedDLItem *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztE_RABToBeSwedDLItem) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztTportLyrAddr, &param->transportLyrAddr, ptr, mBuf); 
		SZUCHKUNPKPTR(cmUnpkSztGTP_TEID, &param->gTP_TEID, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_E_RABToBeSwedDLItem_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztE_RABToBeSwedDLItem */



/*
* FUN : cmUnpkSzt_ValueE_RABToBeSwedDLItemIEsCls
*  DESC: Function to Unpack Szt_ValueE_RABToBeSwedDLItemIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueE_RABToBeSwedDLItemIEsCls
(
Szt_ValueE_RABToBeSwedDLItemIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueE_RABToBeSwedDLItemIEsCls(param, val, ptr, mBuf)
Szt_ValueE_RABToBeSwedDLItemIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueE_RABToBeSwedDLItemIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABToBeSwedDLItem:
			CMCHKUNPKPTR(cmUnpkSztE_RABToBeSwedDLItem, &param->u.sztE_RABToBeSwedDLItem, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueE_RABToBeSwedDLItemIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_E_RABToBeSwedDLItemIEs
*  DESC: Function to Unpack SztProtIE_Field_E_RABToBeSwedDLItemIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABToBeSwedDLItemIEs
(
SztProtIE_Field_E_RABToBeSwedDLItemIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABToBeSwedDLItemIEs(param, ptr, mBuf)
SztProtIE_Field_E_RABToBeSwedDLItemIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_E_RABToBeSwedDLItemIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueE_RABToBeSwedDLItemIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_E_RABToBeSwedDLItemIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmUnpkSztProtIE_SingleCont_E_RABToBeSwedDLItemIEs cmUnpkSztProtIE_Field_E_RABToBeSwedDLItemIEs


/*
* FUN : cmUnpkSztProtIE_ContLst_E_RABToBeSwedDLItemIEs
*  DESC: Function to Unpack SztProtIE_ContLst_E_RABToBeSwedDLItemIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_ContLst_E_RABToBeSwedDLItemIEs
(
SztProtIE_ContLst_E_RABToBeSwedDLItemIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_ContLst_E_RABToBeSwedDLItemIEs(param, ptr, mBuf)
SztProtIE_ContLst_E_RABToBeSwedDLItemIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_ContLst_E_RABToBeSwedDLItemIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_SingleCont_E_RABToBeSwedDLItemIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_SingleCont_E_RABToBeSwedDLItemIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_ContLst_E_RABToBeSwedDLItemIEs */

/* Element ------------- E-RAB-IE-ContainerList ------------ */
#define cmUnpkSztE_RAB_IE_ContLst_E_RABToBeSwedDLItemIEs cmUnpkSztProtIE_ContLst_E_RABToBeSwedDLItemIEs
/* Element ------------- E-RABToBeSwitchedDLList ------------ */
#define cmUnpkSztE_RABToBeSwedDLLst cmUnpkSztE_RAB_IE_ContLst_E_RABToBeSwedDLItemIEs


/*
* FUN : cmUnpkSzt_ValuePathSwRqstIEsCls
*  DESC: Function to Unpack Szt_ValuePathSwRqstIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValuePathSwRqstIEsCls
(
Szt_ValuePathSwRqstIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValuePathSwRqstIEsCls(param, val, ptr, mBuf)
Szt_ValuePathSwRqstIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValuePathSwRqstIEsCls) 
	
	switch (val)
	{
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_E_RABToBeSwedDLLst:
			CMCHKUNPKPTR(cmUnpkSztE_RABToBeSwedDLLst, &param->u.sztE_RABToBeSwedDLLst, ptr, mBuf);
			break;
		case Sztid_SrcMME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_EUTRAN_CGI:
			CMCHKUNPKPTR(cmUnpkSztEUTRAN_CGI, &param->u.sztEUTRAN_CGI, ptr, mBuf);
			break;
		case Sztid_TAI:
			CMCHKUNPKPTR(cmUnpkSztTAI, &param->u.sztTAI, ptr, mBuf);
			break;
		case Sztid_UESecurCapabilities:
			CMCHKUNPKPTR(cmUnpkSztUESecurCapabilities, &param->u.sztUESecurCapabilities, ptr, mBuf);
			break;
		case Sztid_CSG_Id:
			CMCHKUNPK(cmUnpkSztCSG_Id, &param->u.sztCSG_Id, mBuf); 
			break;
		case Sztid_CellAccessMode:
			CMCHKUNPK(cmUnpkSztCellAccessMode, &param->u.sztCellAccessMode, mBuf); 
			break;
		case Sztid_SrcMME_GUMMEI:
			CMCHKUNPKPTR(cmUnpkSztGUMMEI, &param->u.sztGUMMEI, ptr, mBuf);
			break;
		case Sztid_CSGMembershipStatus:
			CMCHKUNPK(cmUnpkSztCSGMembershipStatus, &param->u.sztCSGMembershipStatus, mBuf); 
			break;
		case Sztid_Tunnel_Inform_for_BBF:
			CMCHKUNPKPTR(cmUnpkSztTunnelInform, &param->u.sztTunnelInform, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValuePathSwRqstIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_PathSwRqstIEs
*  DESC: Function to Unpack SztProtIE_Field_PathSwRqstIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_PathSwRqstIEs
(
SztProtIE_Field_PathSwRqstIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_PathSwRqstIEs(param, ptr, mBuf)
SztProtIE_Field_PathSwRqstIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_PathSwRqstIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValuePathSwRqstIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_PathSwRqstIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_PathSwRqstIEs
*  DESC: Function to Unpack SztProtIE_Cont_PathSwRqstIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_PathSwRqstIEs
(
SztProtIE_Cont_PathSwRqstIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_PathSwRqstIEs(param, ptr, mBuf)
SztProtIE_Cont_PathSwRqstIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_PathSwRqstIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_PathSwRqstIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_PathSwRqstIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_PathSwRqstIEs */



/*
* FUN : cmUnpkSztPathSwRqst
*  DESC: Function to Unpack SztPathSwRqst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztPathSwRqst
(
SztPathSwRqst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztPathSwRqst(param, ptr, mBuf)
SztPathSwRqst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztPathSwRqst) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_PathSwRqstIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztPathSwRqst */



/*
* FUN : cmUnpkSzt_ExtnE_RABToBeSwedULItem_ExtIEsCls
*  DESC: Function to Unpack Szt_ExtnE_RABToBeSwedULItem_ExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnE_RABToBeSwedULItem_ExtIEsCls
(
Szt_ExtnE_RABToBeSwedULItem_ExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnE_RABToBeSwedULItem_ExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnE_RABToBeSwedULItem_ExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnE_RABToBeSwedULItem_ExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnE_RABToBeSwedULItem_ExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_E_RABToBeSwedULItem_ExtIEs
*  DESC: Function to Unpack SztProtExtnField_E_RABToBeSwedULItem_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABToBeSwedULItem_ExtIEs
(
SztProtExtnField_E_RABToBeSwedULItem_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABToBeSwedULItem_ExtIEs(param, ptr, mBuf)
SztProtExtnField_E_RABToBeSwedULItem_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_E_RABToBeSwedULItem_ExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnE_RABToBeSwedULItem_ExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_E_RABToBeSwedULItem_ExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_E_RABToBeSwedULItem_ExtIEs
*  DESC: Function to Unpack SztProtExtnCont_E_RABToBeSwedULItem_ExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABToBeSwedULItem_ExtIEs
(
SztProtExtnCont_E_RABToBeSwedULItem_ExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABToBeSwedULItem_ExtIEs(param, ptr, mBuf)
SztProtExtnCont_E_RABToBeSwedULItem_ExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_E_RABToBeSwedULItem_ExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_E_RABToBeSwedULItem_ExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_E_RABToBeSwedULItem_ExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_E_RABToBeSwedULItem_ExtIEs */



/*
* FUN : cmUnpkSztE_RABToBeSwedULItem
*  DESC: Function to Unpack SztE_RABToBeSwedULItem structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABToBeSwedULItem
(
SztE_RABToBeSwedULItem *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABToBeSwedULItem(param, ptr, mBuf)
SztE_RABToBeSwedULItem *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztE_RABToBeSwedULItem) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztTportLyrAddr, &param->transportLyrAddr, ptr, mBuf); 
		SZUCHKUNPKPTR(cmUnpkSztGTP_TEID, &param->gTP_TEID, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_E_RABToBeSwedULItem_ExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztE_RABToBeSwedULItem */



/*
* FUN : cmUnpkSzt_ValueE_RABToBeSwedULItemIEsCls
*  DESC: Function to Unpack Szt_ValueE_RABToBeSwedULItemIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueE_RABToBeSwedULItemIEsCls
(
Szt_ValueE_RABToBeSwedULItemIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueE_RABToBeSwedULItemIEsCls(param, val, ptr, mBuf)
Szt_ValueE_RABToBeSwedULItemIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueE_RABToBeSwedULItemIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABToBeSwedULItem:
			CMCHKUNPKPTR(cmUnpkSztE_RABToBeSwedULItem, &param->u.sztE_RABToBeSwedULItem, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueE_RABToBeSwedULItemIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_E_RABToBeSwedULItemIEs
*  DESC: Function to Unpack SztProtIE_Field_E_RABToBeSwedULItemIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABToBeSwedULItemIEs
(
SztProtIE_Field_E_RABToBeSwedULItemIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABToBeSwedULItemIEs(param, ptr, mBuf)
SztProtIE_Field_E_RABToBeSwedULItemIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_E_RABToBeSwedULItemIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueE_RABToBeSwedULItemIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_E_RABToBeSwedULItemIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmUnpkSztProtIE_SingleCont_E_RABToBeSwedULItemIEs cmUnpkSztProtIE_Field_E_RABToBeSwedULItemIEs


/*
* FUN : cmUnpkSztProtIE_ContLst_E_RABToBeSwedULItemIEs
*  DESC: Function to Unpack SztProtIE_ContLst_E_RABToBeSwedULItemIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_ContLst_E_RABToBeSwedULItemIEs
(
SztProtIE_ContLst_E_RABToBeSwedULItemIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_ContLst_E_RABToBeSwedULItemIEs(param, ptr, mBuf)
SztProtIE_ContLst_E_RABToBeSwedULItemIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_ContLst_E_RABToBeSwedULItemIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_SingleCont_E_RABToBeSwedULItemIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_SingleCont_E_RABToBeSwedULItemIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_ContLst_E_RABToBeSwedULItemIEs */

/* Element ------------- E-RAB-IE-ContainerList ------------ */
#define cmUnpkSztE_RAB_IE_ContLst_E_RABToBeSwedULItemIEs cmUnpkSztProtIE_ContLst_E_RABToBeSwedULItemIEs
/* Element ------------- E-RABToBeSwitchedULList ------------ */
#define cmUnpkSztE_RABToBeSwedULLst cmUnpkSztE_RAB_IE_ContLst_E_RABToBeSwedULItemIEs


/*
* FUN : cmUnpkSzt_ValuePathSwRqstAckgIEsCls
*  DESC: Function to Unpack Szt_ValuePathSwRqstAckgIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValuePathSwRqstAckgIEsCls
(
Szt_ValuePathSwRqstAckgIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValuePathSwRqstAckgIEsCls(param, val, ptr, mBuf)
Szt_ValuePathSwRqstAckgIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValuePathSwRqstAckgIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztid_MME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_uEaggregateMaxBitrate:
			CMCHKUNPKPTR(cmUnpkSztUEAggMaxBitrate, &param->u.sztUEAggMaxBitrate, ptr, mBuf);
			break;
		case Sztid_E_RABToBeSwedULLst:
			CMCHKUNPKPTR(cmUnpkSztE_RABToBeSwedULLst, &param->u.sztE_RABToBeSwedULLst, ptr, mBuf);
			break;
		case Sztid_E_RABToBeRlsdLst:
			CMCHKUNPKPTR(cmUnpkSztE_RABLst, &param->u.sztE_RABLst, ptr, mBuf);
			break;
		case Sztid_SecurCntxt:
			CMCHKUNPKPTR(cmUnpkSztSecurCntxt, &param->u.sztSecurCntxt, ptr, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkSztCriticalityDiag, &param->u.sztCriticalityDiag, ptr, mBuf);
			break;
		case Sztid_MME_UE_S1AP_ID_2:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztid_MME_UE_S1AP_ID_2, mBuf); 
			break;
		case Sztid_CSGMembershipStatus:
			CMCHKUNPK(cmUnpkSztCSGMembershipStatus, &param->u.sztCSGMembershipStatus, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValuePathSwRqstAckgIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_PathSwRqstAckgIEs
*  DESC: Function to Unpack SztProtIE_Field_PathSwRqstAckgIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_PathSwRqstAckgIEs
(
SztProtIE_Field_PathSwRqstAckgIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_PathSwRqstAckgIEs(param, ptr, mBuf)
SztProtIE_Field_PathSwRqstAckgIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_PathSwRqstAckgIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValuePathSwRqstAckgIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_PathSwRqstAckgIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_PathSwRqstAckgIEs
*  DESC: Function to Unpack SztProtIE_Cont_PathSwRqstAckgIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_PathSwRqstAckgIEs
(
SztProtIE_Cont_PathSwRqstAckgIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_PathSwRqstAckgIEs(param, ptr, mBuf)
SztProtIE_Cont_PathSwRqstAckgIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_PathSwRqstAckgIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_PathSwRqstAckgIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_PathSwRqstAckgIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_PathSwRqstAckgIEs */



/*
* FUN : cmUnpkSztPathSwRqstAckg
*  DESC: Function to Unpack SztPathSwRqstAckg structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztPathSwRqstAckg
(
SztPathSwRqstAckg *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztPathSwRqstAckg(param, ptr, mBuf)
SztPathSwRqstAckg *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztPathSwRqstAckg) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_PathSwRqstAckgIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztPathSwRqstAckg */



/*
* FUN : cmUnpkSzt_ValuePathSwRqstFailIEsCls
*  DESC: Function to Unpack Szt_ValuePathSwRqstFailIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValuePathSwRqstFailIEsCls
(
Szt_ValuePathSwRqstFailIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValuePathSwRqstFailIEsCls(param, val, ptr, mBuf)
Szt_ValuePathSwRqstFailIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValuePathSwRqstFailIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_Cause:
			CMCHKUNPKPTR(cmUnpkSztCause, &param->u.sztCause, ptr, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkSztCriticalityDiag, &param->u.sztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValuePathSwRqstFailIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_PathSwRqstFailIEs
*  DESC: Function to Unpack SztProtIE_Field_PathSwRqstFailIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_PathSwRqstFailIEs
(
SztProtIE_Field_PathSwRqstFailIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_PathSwRqstFailIEs(param, ptr, mBuf)
SztProtIE_Field_PathSwRqstFailIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_PathSwRqstFailIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValuePathSwRqstFailIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_PathSwRqstFailIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_PathSwRqstFailIEs
*  DESC: Function to Unpack SztProtIE_Cont_PathSwRqstFailIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_PathSwRqstFailIEs
(
SztProtIE_Cont_PathSwRqstFailIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_PathSwRqstFailIEs(param, ptr, mBuf)
SztProtIE_Cont_PathSwRqstFailIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_PathSwRqstFailIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_PathSwRqstFailIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_PathSwRqstFailIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_PathSwRqstFailIEs */



/*
* FUN : cmUnpkSztPathSwRqstFail
*  DESC: Function to Unpack SztPathSwRqstFail structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztPathSwRqstFail
(
SztPathSwRqstFail *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztPathSwRqstFail(param, ptr, mBuf)
SztPathSwRqstFail *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztPathSwRqstFail) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_PathSwRqstFailIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztPathSwRqstFail */



/*
* FUN : cmUnpkSzt_ValueHovrCancelIEsCls
*  DESC: Function to Unpack Szt_ValueHovrCancelIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueHovrCancelIEsCls
(
Szt_ValueHovrCancelIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueHovrCancelIEsCls(param, val, ptr, mBuf)
Szt_ValueHovrCancelIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueHovrCancelIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_Cause:
			CMCHKUNPKPTR(cmUnpkSztCause, &param->u.sztCause, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueHovrCancelIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_HovrCancelIEs
*  DESC: Function to Unpack SztProtIE_Field_HovrCancelIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_HovrCancelIEs
(
SztProtIE_Field_HovrCancelIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_HovrCancelIEs(param, ptr, mBuf)
SztProtIE_Field_HovrCancelIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_HovrCancelIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueHovrCancelIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_HovrCancelIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_HovrCancelIEs
*  DESC: Function to Unpack SztProtIE_Cont_HovrCancelIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_HovrCancelIEs
(
SztProtIE_Cont_HovrCancelIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_HovrCancelIEs(param, ptr, mBuf)
SztProtIE_Cont_HovrCancelIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_HovrCancelIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_HovrCancelIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_HovrCancelIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_HovrCancelIEs */



/*
* FUN : cmUnpkSztHovrCancel
*  DESC: Function to Unpack SztHovrCancel structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztHovrCancel
(
SztHovrCancel *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztHovrCancel(param, ptr, mBuf)
SztHovrCancel *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztHovrCancel) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_HovrCancelIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztHovrCancel */



/*
* FUN : cmUnpkSzt_ValueHovrCancelAckgIEsCls
*  DESC: Function to Unpack Szt_ValueHovrCancelAckgIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueHovrCancelAckgIEsCls
(
Szt_ValueHovrCancelAckgIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueHovrCancelAckgIEsCls(param, val, ptr, mBuf)
Szt_ValueHovrCancelAckgIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueHovrCancelAckgIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkSztCriticalityDiag, &param->u.sztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueHovrCancelAckgIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_HovrCancelAckgIEs
*  DESC: Function to Unpack SztProtIE_Field_HovrCancelAckgIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_HovrCancelAckgIEs
(
SztProtIE_Field_HovrCancelAckgIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_HovrCancelAckgIEs(param, ptr, mBuf)
SztProtIE_Field_HovrCancelAckgIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_HovrCancelAckgIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueHovrCancelAckgIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_HovrCancelAckgIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_HovrCancelAckgIEs
*  DESC: Function to Unpack SztProtIE_Cont_HovrCancelAckgIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_HovrCancelAckgIEs
(
SztProtIE_Cont_HovrCancelAckgIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_HovrCancelAckgIEs(param, ptr, mBuf)
SztProtIE_Cont_HovrCancelAckgIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_HovrCancelAckgIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_HovrCancelAckgIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_HovrCancelAckgIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_HovrCancelAckgIEs */



/*
* FUN : cmUnpkSztHovrCancelAckg
*  DESC: Function to Unpack SztHovrCancelAckg structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztHovrCancelAckg
(
SztHovrCancelAckg *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztHovrCancelAckg(param, ptr, mBuf)
SztHovrCancelAckg *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztHovrCancelAckg) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_HovrCancelAckgIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztHovrCancelAckg */



/*
* FUN : cmUnpkSzt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls
*  DESC: Function to Unpack Szt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls
(
Szt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls) 
	
	switch (val)
	{
		case Sztid_Correlation_ID:
			SZUCHKUNPKPTR(cmUnpkSztCorrelation_ID, &param->u.sztCorrelation_ID, ptr, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs
*  DESC: Function to Unpack SztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs
(
SztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs(param, ptr, mBuf)
SztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnE_RABToBeSetupItemBrSUReqExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs
*  DESC: Function to Unpack SztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs
(
SztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs(param, ptr, mBuf)
SztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs */



/*
* FUN : cmUnpkSztE_RABToBeSetupItemBrSUReq
*  DESC: Function to Unpack SztE_RABToBeSetupItemBrSUReq structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABToBeSetupItemBrSUReq
(
SztE_RABToBeSetupItemBrSUReq *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABToBeSetupItemBrSUReq(param, ptr, mBuf)
SztE_RABToBeSetupItemBrSUReq *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztE_RABToBeSetupItemBrSUReq) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztE_RABLvlQoSParams, &param->e_RABlevelQoSParams, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztTportLyrAddr, &param->transportLyrAddr, ptr, mBuf); 
		SZUCHKUNPKPTR(cmUnpkSztGTP_TEID, &param->gTP_TEID, ptr, mBuf); 
		SZUCHKUNPKPTR(cmUnpkSztNAS_PDU, &param->nAS_PDU, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_E_RABToBeSetupItemBrSUReqExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztE_RABToBeSetupItemBrSUReq */



/*
* FUN : cmUnpkSzt_ValueE_RABToBeSetupItemBrSUReqIEsCls
*  DESC: Function to Unpack Szt_ValueE_RABToBeSetupItemBrSUReqIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueE_RABToBeSetupItemBrSUReqIEsCls
(
Szt_ValueE_RABToBeSetupItemBrSUReqIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueE_RABToBeSetupItemBrSUReqIEsCls(param, val, ptr, mBuf)
Szt_ValueE_RABToBeSetupItemBrSUReqIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueE_RABToBeSetupItemBrSUReqIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABToBeSetupItemBrSUReq:
			CMCHKUNPKPTR(cmUnpkSztE_RABToBeSetupItemBrSUReq, &param->u.sztE_RABToBeSetupItemBrSUReq, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueE_RABToBeSetupItemBrSUReqIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_E_RABToBeSetupItemBrSUReqIEs
*  DESC: Function to Unpack SztProtIE_Field_E_RABToBeSetupItemBrSUReqIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABToBeSetupItemBrSUReqIEs
(
SztProtIE_Field_E_RABToBeSetupItemBrSUReqIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABToBeSetupItemBrSUReqIEs(param, ptr, mBuf)
SztProtIE_Field_E_RABToBeSetupItemBrSUReqIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_E_RABToBeSetupItemBrSUReqIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueE_RABToBeSetupItemBrSUReqIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_E_RABToBeSetupItemBrSUReqIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmUnpkSztProtIE_SingleCont_E_RABToBeSetupItemBrSUReqIEs cmUnpkSztProtIE_Field_E_RABToBeSetupItemBrSUReqIEs


/*
* FUN : cmUnpkSztE_RABToBeSetupLstBrSUReq
*  DESC: Function to Unpack SztE_RABToBeSetupLstBrSUReq structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABToBeSetupLstBrSUReq
(
SztE_RABToBeSetupLstBrSUReq *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABToBeSetupLstBrSUReq(param, ptr, mBuf)
SztE_RABToBeSetupLstBrSUReq *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztE_RABToBeSetupLstBrSUReq) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_SingleCont_E_RABToBeSetupItemBrSUReqIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_SingleCont_E_RABToBeSetupItemBrSUReqIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztE_RABToBeSetupLstBrSUReq */



/*
* FUN : cmUnpkSzt_ValueE_RABSetupRqstIEsCls
*  DESC: Function to Unpack Szt_ValueE_RABSetupRqstIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueE_RABSetupRqstIEsCls
(
Szt_ValueE_RABSetupRqstIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueE_RABSetupRqstIEsCls(param, val, ptr, mBuf)
Szt_ValueE_RABSetupRqstIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueE_RABSetupRqstIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_uEaggregateMaxBitrate:
			CMCHKUNPKPTR(cmUnpkSztUEAggMaxBitrate, &param->u.sztUEAggMaxBitrate, ptr, mBuf);
			break;
		case Sztid_E_RABToBeSetupLstBrSUReq:
			CMCHKUNPKPTR(cmUnpkSztE_RABToBeSetupLstBrSUReq, &param->u.sztE_RABToBeSetupLstBrSUReq, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueE_RABSetupRqstIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_E_RABSetupRqstIEs
*  DESC: Function to Unpack SztProtIE_Field_E_RABSetupRqstIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABSetupRqstIEs
(
SztProtIE_Field_E_RABSetupRqstIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABSetupRqstIEs(param, ptr, mBuf)
SztProtIE_Field_E_RABSetupRqstIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_E_RABSetupRqstIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueE_RABSetupRqstIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_E_RABSetupRqstIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_E_RABSetupRqstIEs
*  DESC: Function to Unpack SztProtIE_Cont_E_RABSetupRqstIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_E_RABSetupRqstIEs
(
SztProtIE_Cont_E_RABSetupRqstIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_E_RABSetupRqstIEs(param, ptr, mBuf)
SztProtIE_Cont_E_RABSetupRqstIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_E_RABSetupRqstIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_E_RABSetupRqstIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_E_RABSetupRqstIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_E_RABSetupRqstIEs */



/*
* FUN : cmUnpkSztE_RABSetupRqst
*  DESC: Function to Unpack SztE_RABSetupRqst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABSetupRqst
(
SztE_RABSetupRqst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABSetupRqst(param, ptr, mBuf)
SztE_RABSetupRqst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztE_RABSetupRqst) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_E_RABSetupRqstIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztE_RABSetupRqst */



/*
* FUN : cmUnpkSzt_ExtnE_RABSetupItemBrSUResExtIEsCls
*  DESC: Function to Unpack Szt_ExtnE_RABSetupItemBrSUResExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnE_RABSetupItemBrSUResExtIEsCls
(
Szt_ExtnE_RABSetupItemBrSUResExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnE_RABSetupItemBrSUResExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnE_RABSetupItemBrSUResExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnE_RABSetupItemBrSUResExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnE_RABSetupItemBrSUResExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_E_RABSetupItemBrSUResExtIEs
*  DESC: Function to Unpack SztProtExtnField_E_RABSetupItemBrSUResExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABSetupItemBrSUResExtIEs
(
SztProtExtnField_E_RABSetupItemBrSUResExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABSetupItemBrSUResExtIEs(param, ptr, mBuf)
SztProtExtnField_E_RABSetupItemBrSUResExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_E_RABSetupItemBrSUResExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnE_RABSetupItemBrSUResExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_E_RABSetupItemBrSUResExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_E_RABSetupItemBrSUResExtIEs
*  DESC: Function to Unpack SztProtExtnCont_E_RABSetupItemBrSUResExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABSetupItemBrSUResExtIEs
(
SztProtExtnCont_E_RABSetupItemBrSUResExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABSetupItemBrSUResExtIEs(param, ptr, mBuf)
SztProtExtnCont_E_RABSetupItemBrSUResExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_E_RABSetupItemBrSUResExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_E_RABSetupItemBrSUResExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_E_RABSetupItemBrSUResExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_E_RABSetupItemBrSUResExtIEs */



/*
* FUN : cmUnpkSztE_RABSetupItemBrSURes
*  DESC: Function to Unpack SztE_RABSetupItemBrSURes structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABSetupItemBrSURes
(
SztE_RABSetupItemBrSURes *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABSetupItemBrSURes(param, ptr, mBuf)
SztE_RABSetupItemBrSURes *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztE_RABSetupItemBrSURes) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztTportLyrAddr, &param->transportLyrAddr, ptr, mBuf); 
		SZUCHKUNPKPTR(cmUnpkSztGTP_TEID, &param->gTP_TEID, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_E_RABSetupItemBrSUResExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztE_RABSetupItemBrSURes */



/*
* FUN : cmUnpkSzt_ValueE_RABSetupItemBrSUResIEsCls
*  DESC: Function to Unpack Szt_ValueE_RABSetupItemBrSUResIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueE_RABSetupItemBrSUResIEsCls
(
Szt_ValueE_RABSetupItemBrSUResIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueE_RABSetupItemBrSUResIEsCls(param, val, ptr, mBuf)
Szt_ValueE_RABSetupItemBrSUResIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueE_RABSetupItemBrSUResIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABSetupItemBrSURes:
			CMCHKUNPKPTR(cmUnpkSztE_RABSetupItemBrSURes, &param->u.sztE_RABSetupItemBrSURes, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueE_RABSetupItemBrSUResIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_E_RABSetupItemBrSUResIEs
*  DESC: Function to Unpack SztProtIE_Field_E_RABSetupItemBrSUResIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABSetupItemBrSUResIEs
(
SztProtIE_Field_E_RABSetupItemBrSUResIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABSetupItemBrSUResIEs(param, ptr, mBuf)
SztProtIE_Field_E_RABSetupItemBrSUResIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_E_RABSetupItemBrSUResIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueE_RABSetupItemBrSUResIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_E_RABSetupItemBrSUResIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmUnpkSztProtIE_SingleCont_E_RABSetupItemBrSUResIEs cmUnpkSztProtIE_Field_E_RABSetupItemBrSUResIEs


/*
* FUN : cmUnpkSztE_RABSetupLstBrSURes
*  DESC: Function to Unpack SztE_RABSetupLstBrSURes structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABSetupLstBrSURes
(
SztE_RABSetupLstBrSURes *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABSetupLstBrSURes(param, ptr, mBuf)
SztE_RABSetupLstBrSURes *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztE_RABSetupLstBrSURes) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_SingleCont_E_RABSetupItemBrSUResIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_SingleCont_E_RABSetupItemBrSUResIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztE_RABSetupLstBrSURes */



/*
* FUN : cmUnpkSzt_ValueE_RABSetupRespIEsCls
*  DESC: Function to Unpack Szt_ValueE_RABSetupRespIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueE_RABSetupRespIEsCls
(
Szt_ValueE_RABSetupRespIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueE_RABSetupRespIEsCls(param, val, ptr, mBuf)
Szt_ValueE_RABSetupRespIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueE_RABSetupRespIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_E_RABSetupLstBrSURes:
			CMCHKUNPKPTR(cmUnpkSztE_RABSetupLstBrSURes, &param->u.sztE_RABSetupLstBrSURes, ptr, mBuf);
			break;
		case Sztid_E_RABFailedToSetupLstBrSURes:
			CMCHKUNPKPTR(cmUnpkSztE_RABLst, &param->u.sztE_RABLst, ptr, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkSztCriticalityDiag, &param->u.sztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueE_RABSetupRespIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_E_RABSetupRespIEs
*  DESC: Function to Unpack SztProtIE_Field_E_RABSetupRespIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABSetupRespIEs
(
SztProtIE_Field_E_RABSetupRespIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABSetupRespIEs(param, ptr, mBuf)
SztProtIE_Field_E_RABSetupRespIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_E_RABSetupRespIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueE_RABSetupRespIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_E_RABSetupRespIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_E_RABSetupRespIEs
*  DESC: Function to Unpack SztProtIE_Cont_E_RABSetupRespIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_E_RABSetupRespIEs
(
SztProtIE_Cont_E_RABSetupRespIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_E_RABSetupRespIEs(param, ptr, mBuf)
SztProtIE_Cont_E_RABSetupRespIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_E_RABSetupRespIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_E_RABSetupRespIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_E_RABSetupRespIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_E_RABSetupRespIEs */



/*
* FUN : cmUnpkSztE_RABSetupResp
*  DESC: Function to Unpack SztE_RABSetupResp structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABSetupResp
(
SztE_RABSetupResp *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABSetupResp(param, ptr, mBuf)
SztE_RABSetupResp *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztE_RABSetupResp) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_E_RABSetupRespIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztE_RABSetupResp */



/*
* FUN : cmUnpkSzt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls
*  DESC: Function to Unpack Szt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls
(
Szt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs
*  DESC: Function to Unpack SztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs
(
SztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs(param, ptr, mBuf)
SztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnE_RABToBeMdfyItemBrModReqExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs
*  DESC: Function to Unpack SztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs
(
SztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs(param, ptr, mBuf)
SztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_E_RABToBeMdfyItemBrModReqExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs */



/*
* FUN : cmUnpkSztE_RABToBeMdfdItemBrModReq
*  DESC: Function to Unpack SztE_RABToBeMdfdItemBrModReq structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABToBeMdfdItemBrModReq
(
SztE_RABToBeMdfdItemBrModReq *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABToBeMdfdItemBrModReq(param, ptr, mBuf)
SztE_RABToBeMdfdItemBrModReq *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztE_RABToBeMdfdItemBrModReq) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztE_RABLvlQoSParams, &param->e_RABLvlQoSParams, ptr, mBuf); 
		SZUCHKUNPKPTR(cmUnpkSztNAS_PDU, &param->nAS_PDU, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_E_RABToBeMdfyItemBrModReqExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztE_RABToBeMdfdItemBrModReq */



/*
* FUN : cmUnpkSzt_ValueE_RABToBeMdfdItemBrModReqIEsCls
*  DESC: Function to Unpack Szt_ValueE_RABToBeMdfdItemBrModReqIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueE_RABToBeMdfdItemBrModReqIEsCls
(
Szt_ValueE_RABToBeMdfdItemBrModReqIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueE_RABToBeMdfdItemBrModReqIEsCls(param, val, ptr, mBuf)
Szt_ValueE_RABToBeMdfdItemBrModReqIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueE_RABToBeMdfdItemBrModReqIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABToBeMdfdItemBrModReq:
			CMCHKUNPKPTR(cmUnpkSztE_RABToBeMdfdItemBrModReq, &param->u.sztE_RABToBeMdfdItemBrModReq, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueE_RABToBeMdfdItemBrModReqIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_E_RABToBeMdfdItemBrModReqIEs
*  DESC: Function to Unpack SztProtIE_Field_E_RABToBeMdfdItemBrModReqIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABToBeMdfdItemBrModReqIEs
(
SztProtIE_Field_E_RABToBeMdfdItemBrModReqIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABToBeMdfdItemBrModReqIEs(param, ptr, mBuf)
SztProtIE_Field_E_RABToBeMdfdItemBrModReqIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_E_RABToBeMdfdItemBrModReqIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueE_RABToBeMdfdItemBrModReqIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_E_RABToBeMdfdItemBrModReqIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmUnpkSztProtIE_SingleCont_E_RABToBeMdfdItemBrModReqIEs cmUnpkSztProtIE_Field_E_RABToBeMdfdItemBrModReqIEs


/*
* FUN : cmUnpkSztE_RABToBeMdfdLstBrModReq
*  DESC: Function to Unpack SztE_RABToBeMdfdLstBrModReq structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABToBeMdfdLstBrModReq
(
SztE_RABToBeMdfdLstBrModReq *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABToBeMdfdLstBrModReq(param, ptr, mBuf)
SztE_RABToBeMdfdLstBrModReq *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztE_RABToBeMdfdLstBrModReq) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_SingleCont_E_RABToBeMdfdItemBrModReqIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_SingleCont_E_RABToBeMdfdItemBrModReqIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztE_RABToBeMdfdLstBrModReq */



/*
* FUN : cmUnpkSzt_ValueE_RABMdfyRqstIEsCls
*  DESC: Function to Unpack Szt_ValueE_RABMdfyRqstIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueE_RABMdfyRqstIEsCls
(
Szt_ValueE_RABMdfyRqstIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueE_RABMdfyRqstIEsCls(param, val, ptr, mBuf)
Szt_ValueE_RABMdfyRqstIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueE_RABMdfyRqstIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_uEaggregateMaxBitrate:
			CMCHKUNPKPTR(cmUnpkSztUEAggMaxBitrate, &param->u.sztUEAggMaxBitrate, ptr, mBuf);
			break;
		case Sztid_E_RABToBeMdfdLstBrModReq:
			CMCHKUNPKPTR(cmUnpkSztE_RABToBeMdfdLstBrModReq, &param->u.sztE_RABToBeMdfdLstBrModReq, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueE_RABMdfyRqstIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_E_RABMdfyRqstIEs
*  DESC: Function to Unpack SztProtIE_Field_E_RABMdfyRqstIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABMdfyRqstIEs
(
SztProtIE_Field_E_RABMdfyRqstIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABMdfyRqstIEs(param, ptr, mBuf)
SztProtIE_Field_E_RABMdfyRqstIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_E_RABMdfyRqstIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueE_RABMdfyRqstIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_E_RABMdfyRqstIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_E_RABMdfyRqstIEs
*  DESC: Function to Unpack SztProtIE_Cont_E_RABMdfyRqstIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_E_RABMdfyRqstIEs
(
SztProtIE_Cont_E_RABMdfyRqstIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_E_RABMdfyRqstIEs(param, ptr, mBuf)
SztProtIE_Cont_E_RABMdfyRqstIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_E_RABMdfyRqstIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_E_RABMdfyRqstIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_E_RABMdfyRqstIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_E_RABMdfyRqstIEs */



/*
* FUN : cmUnpkSztE_RABMdfyRqst
*  DESC: Function to Unpack SztE_RABMdfyRqst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABMdfyRqst
(
SztE_RABMdfyRqst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABMdfyRqst(param, ptr, mBuf)
SztE_RABMdfyRqst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztE_RABMdfyRqst) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_E_RABMdfyRqstIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztE_RABMdfyRqst */



/*
* FUN : cmUnpkSzt_ExtnE_RABMdfyItemBrModResExtIEsCls
*  DESC: Function to Unpack Szt_ExtnE_RABMdfyItemBrModResExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnE_RABMdfyItemBrModResExtIEsCls
(
Szt_ExtnE_RABMdfyItemBrModResExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnE_RABMdfyItemBrModResExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnE_RABMdfyItemBrModResExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnE_RABMdfyItemBrModResExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnE_RABMdfyItemBrModResExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_E_RABMdfyItemBrModResExtIEs
*  DESC: Function to Unpack SztProtExtnField_E_RABMdfyItemBrModResExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABMdfyItemBrModResExtIEs
(
SztProtExtnField_E_RABMdfyItemBrModResExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABMdfyItemBrModResExtIEs(param, ptr, mBuf)
SztProtExtnField_E_RABMdfyItemBrModResExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_E_RABMdfyItemBrModResExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnE_RABMdfyItemBrModResExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_E_RABMdfyItemBrModResExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_E_RABMdfyItemBrModResExtIEs
*  DESC: Function to Unpack SztProtExtnCont_E_RABMdfyItemBrModResExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABMdfyItemBrModResExtIEs
(
SztProtExtnCont_E_RABMdfyItemBrModResExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABMdfyItemBrModResExtIEs(param, ptr, mBuf)
SztProtExtnCont_E_RABMdfyItemBrModResExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_E_RABMdfyItemBrModResExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_E_RABMdfyItemBrModResExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_E_RABMdfyItemBrModResExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_E_RABMdfyItemBrModResExtIEs */



/*
* FUN : cmUnpkSztE_RABMdfyItemBrModRes
*  DESC: Function to Unpack SztE_RABMdfyItemBrModRes structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABMdfyItemBrModRes
(
SztE_RABMdfyItemBrModRes *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABMdfyItemBrModRes(param, ptr, mBuf)
SztE_RABMdfyItemBrModRes *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztE_RABMdfyItemBrModRes) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_E_RABMdfyItemBrModResExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztE_RABMdfyItemBrModRes */



/*
* FUN : cmUnpkSzt_ValueE_RABMdfyItemBrModResIEsCls
*  DESC: Function to Unpack Szt_ValueE_RABMdfyItemBrModResIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueE_RABMdfyItemBrModResIEsCls
(
Szt_ValueE_RABMdfyItemBrModResIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueE_RABMdfyItemBrModResIEsCls(param, val, ptr, mBuf)
Szt_ValueE_RABMdfyItemBrModResIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueE_RABMdfyItemBrModResIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABMdfyItemBrModRes:
			CMCHKUNPKPTR(cmUnpkSztE_RABMdfyItemBrModRes, &param->u.sztE_RABMdfyItemBrModRes, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueE_RABMdfyItemBrModResIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_E_RABMdfyItemBrModResIEs
*  DESC: Function to Unpack SztProtIE_Field_E_RABMdfyItemBrModResIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABMdfyItemBrModResIEs
(
SztProtIE_Field_E_RABMdfyItemBrModResIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABMdfyItemBrModResIEs(param, ptr, mBuf)
SztProtIE_Field_E_RABMdfyItemBrModResIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_E_RABMdfyItemBrModResIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueE_RABMdfyItemBrModResIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_E_RABMdfyItemBrModResIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmUnpkSztProtIE_SingleCont_E_RABMdfyItemBrModResIEs cmUnpkSztProtIE_Field_E_RABMdfyItemBrModResIEs


/*
* FUN : cmUnpkSztE_RABMdfyLstBrModRes
*  DESC: Function to Unpack SztE_RABMdfyLstBrModRes structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABMdfyLstBrModRes
(
SztE_RABMdfyLstBrModRes *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABMdfyLstBrModRes(param, ptr, mBuf)
SztE_RABMdfyLstBrModRes *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztE_RABMdfyLstBrModRes) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_SingleCont_E_RABMdfyItemBrModResIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_SingleCont_E_RABMdfyItemBrModResIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztE_RABMdfyLstBrModRes */



/*
* FUN : cmUnpkSzt_ValueE_RABMdfyRespIEsCls
*  DESC: Function to Unpack Szt_ValueE_RABMdfyRespIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueE_RABMdfyRespIEsCls
(
Szt_ValueE_RABMdfyRespIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueE_RABMdfyRespIEsCls(param, val, ptr, mBuf)
Szt_ValueE_RABMdfyRespIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueE_RABMdfyRespIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_E_RABMdfyLstBrModRes:
			CMCHKUNPKPTR(cmUnpkSztE_RABMdfyLstBrModRes, &param->u.sztE_RABMdfyLstBrModRes, ptr, mBuf);
			break;
		case Sztid_E_RABFailedToMdfyLst:
			CMCHKUNPKPTR(cmUnpkSztE_RABLst, &param->u.sztE_RABLst, ptr, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkSztCriticalityDiag, &param->u.sztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueE_RABMdfyRespIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_E_RABMdfyRespIEs
*  DESC: Function to Unpack SztProtIE_Field_E_RABMdfyRespIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABMdfyRespIEs
(
SztProtIE_Field_E_RABMdfyRespIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABMdfyRespIEs(param, ptr, mBuf)
SztProtIE_Field_E_RABMdfyRespIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_E_RABMdfyRespIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueE_RABMdfyRespIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_E_RABMdfyRespIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_E_RABMdfyRespIEs
*  DESC: Function to Unpack SztProtIE_Cont_E_RABMdfyRespIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_E_RABMdfyRespIEs
(
SztProtIE_Cont_E_RABMdfyRespIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_E_RABMdfyRespIEs(param, ptr, mBuf)
SztProtIE_Cont_E_RABMdfyRespIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_E_RABMdfyRespIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_E_RABMdfyRespIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_E_RABMdfyRespIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_E_RABMdfyRespIEs */



/*
* FUN : cmUnpkSztE_RABMdfyResp
*  DESC: Function to Unpack SztE_RABMdfyResp structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABMdfyResp
(
SztE_RABMdfyResp *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABMdfyResp(param, ptr, mBuf)
SztE_RABMdfyResp *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztE_RABMdfyResp) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_E_RABMdfyRespIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztE_RABMdfyResp */



/*
* FUN : cmUnpkSzt_ValueE_RABRlsCmmdIEsCls
*  DESC: Function to Unpack Szt_ValueE_RABRlsCmmdIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueE_RABRlsCmmdIEsCls
(
Szt_ValueE_RABRlsCmmdIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueE_RABRlsCmmdIEsCls(param, val, ptr, mBuf)
Szt_ValueE_RABRlsCmmdIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueE_RABRlsCmmdIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_uEaggregateMaxBitrate:
			CMCHKUNPKPTR(cmUnpkSztUEAggMaxBitrate, &param->u.sztUEAggMaxBitrate, ptr, mBuf);
			break;
		case Sztid_E_RABToBeRlsdLst:
			CMCHKUNPKPTR(cmUnpkSztE_RABLst, &param->u.sztE_RABLst, ptr, mBuf);
			break;
		case Sztid_NAS_PDU:
			SZUCHKUNPKPTR(cmUnpkSztNAS_PDU, &param->u.sztNAS_PDU, ptr, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueE_RABRlsCmmdIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_E_RABRlsCmmdIEs
*  DESC: Function to Unpack SztProtIE_Field_E_RABRlsCmmdIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABRlsCmmdIEs
(
SztProtIE_Field_E_RABRlsCmmdIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABRlsCmmdIEs(param, ptr, mBuf)
SztProtIE_Field_E_RABRlsCmmdIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_E_RABRlsCmmdIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueE_RABRlsCmmdIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_E_RABRlsCmmdIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_E_RABRlsCmmdIEs
*  DESC: Function to Unpack SztProtIE_Cont_E_RABRlsCmmdIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_E_RABRlsCmmdIEs
(
SztProtIE_Cont_E_RABRlsCmmdIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_E_RABRlsCmmdIEs(param, ptr, mBuf)
SztProtIE_Cont_E_RABRlsCmmdIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_E_RABRlsCmmdIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_E_RABRlsCmmdIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_E_RABRlsCmmdIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_E_RABRlsCmmdIEs */



/*
* FUN : cmUnpkSztE_RABRlsCmmd
*  DESC: Function to Unpack SztE_RABRlsCmmd structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABRlsCmmd
(
SztE_RABRlsCmmd *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABRlsCmmd(param, ptr, mBuf)
SztE_RABRlsCmmd *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztE_RABRlsCmmd) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_E_RABRlsCmmdIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztE_RABRlsCmmd */



/*
* FUN : cmUnpkSzt_ExtnE_RABRlsItemBrRelCompExtIEsCls
*  DESC: Function to Unpack Szt_ExtnE_RABRlsItemBrRelCompExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnE_RABRlsItemBrRelCompExtIEsCls
(
Szt_ExtnE_RABRlsItemBrRelCompExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnE_RABRlsItemBrRelCompExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnE_RABRlsItemBrRelCompExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnE_RABRlsItemBrRelCompExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnE_RABRlsItemBrRelCompExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_E_RABRlsItemBrRelCompExtIEs
*  DESC: Function to Unpack SztProtExtnField_E_RABRlsItemBrRelCompExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABRlsItemBrRelCompExtIEs
(
SztProtExtnField_E_RABRlsItemBrRelCompExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABRlsItemBrRelCompExtIEs(param, ptr, mBuf)
SztProtExtnField_E_RABRlsItemBrRelCompExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_E_RABRlsItemBrRelCompExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnE_RABRlsItemBrRelCompExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_E_RABRlsItemBrRelCompExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_E_RABRlsItemBrRelCompExtIEs
*  DESC: Function to Unpack SztProtExtnCont_E_RABRlsItemBrRelCompExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABRlsItemBrRelCompExtIEs
(
SztProtExtnCont_E_RABRlsItemBrRelCompExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABRlsItemBrRelCompExtIEs(param, ptr, mBuf)
SztProtExtnCont_E_RABRlsItemBrRelCompExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_E_RABRlsItemBrRelCompExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_E_RABRlsItemBrRelCompExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_E_RABRlsItemBrRelCompExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_E_RABRlsItemBrRelCompExtIEs */



/*
* FUN : cmUnpkSztE_RABRlsItemBrRelComp
*  DESC: Function to Unpack SztE_RABRlsItemBrRelComp structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABRlsItemBrRelComp
(
SztE_RABRlsItemBrRelComp *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABRlsItemBrRelComp(param, ptr, mBuf)
SztE_RABRlsItemBrRelComp *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztE_RABRlsItemBrRelComp) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_E_RABRlsItemBrRelCompExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztE_RABRlsItemBrRelComp */



/*
* FUN : cmUnpkSzt_ValueE_RABRlsItemBrRelCompIEsCls
*  DESC: Function to Unpack Szt_ValueE_RABRlsItemBrRelCompIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueE_RABRlsItemBrRelCompIEsCls
(
Szt_ValueE_RABRlsItemBrRelCompIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueE_RABRlsItemBrRelCompIEsCls(param, val, ptr, mBuf)
Szt_ValueE_RABRlsItemBrRelCompIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueE_RABRlsItemBrRelCompIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABRlsItemBrRelComp:
			CMCHKUNPKPTR(cmUnpkSztE_RABRlsItemBrRelComp, &param->u.sztE_RABRlsItemBrRelComp, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueE_RABRlsItemBrRelCompIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_E_RABRlsItemBrRelCompIEs
*  DESC: Function to Unpack SztProtIE_Field_E_RABRlsItemBrRelCompIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABRlsItemBrRelCompIEs
(
SztProtIE_Field_E_RABRlsItemBrRelCompIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABRlsItemBrRelCompIEs(param, ptr, mBuf)
SztProtIE_Field_E_RABRlsItemBrRelCompIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_E_RABRlsItemBrRelCompIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueE_RABRlsItemBrRelCompIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_E_RABRlsItemBrRelCompIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmUnpkSztProtIE_SingleCont_E_RABRlsItemBrRelCompIEs cmUnpkSztProtIE_Field_E_RABRlsItemBrRelCompIEs


/*
* FUN : cmUnpkSztE_RABRlsLstBrRelComp
*  DESC: Function to Unpack SztE_RABRlsLstBrRelComp structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABRlsLstBrRelComp
(
SztE_RABRlsLstBrRelComp *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABRlsLstBrRelComp(param, ptr, mBuf)
SztE_RABRlsLstBrRelComp *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztE_RABRlsLstBrRelComp) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_SingleCont_E_RABRlsItemBrRelCompIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_SingleCont_E_RABRlsItemBrRelCompIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztE_RABRlsLstBrRelComp */



/*
* FUN : cmUnpkSzt_ValueE_RABRlsRespIEsCls
*  DESC: Function to Unpack Szt_ValueE_RABRlsRespIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueE_RABRlsRespIEsCls
(
Szt_ValueE_RABRlsRespIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueE_RABRlsRespIEsCls(param, val, ptr, mBuf)
Szt_ValueE_RABRlsRespIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueE_RABRlsRespIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_E_RABRlsLstBrRelComp:
			CMCHKUNPKPTR(cmUnpkSztE_RABRlsLstBrRelComp, &param->u.sztE_RABRlsLstBrRelComp, ptr, mBuf);
			break;
		case Sztid_E_RABFailedToRlsLst:
			CMCHKUNPKPTR(cmUnpkSztE_RABLst, &param->u.sztE_RABLst, ptr, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkSztCriticalityDiag, &param->u.sztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueE_RABRlsRespIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_E_RABRlsRespIEs
*  DESC: Function to Unpack SztProtIE_Field_E_RABRlsRespIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABRlsRespIEs
(
SztProtIE_Field_E_RABRlsRespIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABRlsRespIEs(param, ptr, mBuf)
SztProtIE_Field_E_RABRlsRespIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_E_RABRlsRespIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueE_RABRlsRespIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_E_RABRlsRespIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_E_RABRlsRespIEs
*  DESC: Function to Unpack SztProtIE_Cont_E_RABRlsRespIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_E_RABRlsRespIEs
(
SztProtIE_Cont_E_RABRlsRespIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_E_RABRlsRespIEs(param, ptr, mBuf)
SztProtIE_Cont_E_RABRlsRespIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_E_RABRlsRespIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_E_RABRlsRespIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_E_RABRlsRespIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_E_RABRlsRespIEs */



/*
* FUN : cmUnpkSztE_RABRlsResp
*  DESC: Function to Unpack SztE_RABRlsResp structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABRlsResp
(
SztE_RABRlsResp *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABRlsResp(param, ptr, mBuf)
SztE_RABRlsResp *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztE_RABRlsResp) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_E_RABRlsRespIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztE_RABRlsResp */



/*
* FUN : cmUnpkSzt_ValueE_RABRlsIndIEsCls
*  DESC: Function to Unpack Szt_ValueE_RABRlsIndIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueE_RABRlsIndIEsCls
(
Szt_ValueE_RABRlsIndIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueE_RABRlsIndIEsCls(param, val, ptr, mBuf)
Szt_ValueE_RABRlsIndIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueE_RABRlsIndIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_E_RABRlsdLst:
			CMCHKUNPKPTR(cmUnpkSztE_RABLst, &param->u.sztE_RABLst, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueE_RABRlsIndIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_E_RABRlsIndIEs
*  DESC: Function to Unpack SztProtIE_Field_E_RABRlsIndIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABRlsIndIEs
(
SztProtIE_Field_E_RABRlsIndIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABRlsIndIEs(param, ptr, mBuf)
SztProtIE_Field_E_RABRlsIndIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_E_RABRlsIndIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueE_RABRlsIndIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_E_RABRlsIndIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_E_RABRlsIndIEs
*  DESC: Function to Unpack SztProtIE_Cont_E_RABRlsIndIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_E_RABRlsIndIEs
(
SztProtIE_Cont_E_RABRlsIndIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_E_RABRlsIndIEs(param, ptr, mBuf)
SztProtIE_Cont_E_RABRlsIndIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_E_RABRlsIndIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_E_RABRlsIndIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_E_RABRlsIndIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_E_RABRlsIndIEs */



/*
* FUN : cmUnpkSztE_RABRlsInd
*  DESC: Function to Unpack SztE_RABRlsInd structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABRlsInd
(
SztE_RABRlsInd *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABRlsInd(param, ptr, mBuf)
SztE_RABRlsInd *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztE_RABRlsInd) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_E_RABRlsIndIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztE_RABRlsInd */



/*
* FUN : cmUnpkSzt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls
*  DESC: Function to Unpack Szt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls
(
Szt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls) 
	
	switch (val)
	{
		case Sztid_Correlation_ID:
			SZUCHKUNPKPTR(cmUnpkSztCorrelation_ID, &param->u.sztCorrelation_ID, ptr, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs
*  DESC: Function to Unpack SztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs
(
SztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs(param, ptr, mBuf)
SztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnE_RABToBeSetupItemCtxtSUReqExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs
*  DESC: Function to Unpack SztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs
(
SztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs(param, ptr, mBuf)
SztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs */



/*
* FUN : cmUnpkSztE_RABToBeSetupItemCtxtSUReq
*  DESC: Function to Unpack SztE_RABToBeSetupItemCtxtSUReq structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABToBeSetupItemCtxtSUReq
(
SztE_RABToBeSetupItemCtxtSUReq *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABToBeSetupItemCtxtSUReq(param, ptr, mBuf)
SztE_RABToBeSetupItemCtxtSUReq *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztE_RABToBeSetupItemCtxtSUReq) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztE_RABLvlQoSParams, &param->e_RABlevelQoSParams, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztTportLyrAddr, &param->transportLyrAddr, ptr, mBuf); 
		SZUCHKUNPKPTR(cmUnpkSztGTP_TEID, &param->gTP_TEID, ptr, mBuf); 
		SZUCHKUNPKPTR(cmUnpkSztNAS_PDU, &param->nAS_PDU, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_E_RABToBeSetupItemCtxtSUReqExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztE_RABToBeSetupItemCtxtSUReq */



/*
* FUN : cmUnpkSzt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls
*  DESC: Function to Unpack Szt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls
(
Szt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls(param, val, ptr, mBuf)
Szt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABToBeSetupItemCtxtSUReq:
			CMCHKUNPKPTR(cmUnpkSztE_RABToBeSetupItemCtxtSUReq, &param->u.sztE_RABToBeSetupItemCtxtSUReq, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs
*  DESC: Function to Unpack SztProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs
(
SztProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs(param, ptr, mBuf)
SztProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueE_RABToBeSetupItemCtxtSUReqIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmUnpkSztProtIE_SingleCont_E_RABToBeSetupItemCtxtSUReqIEs cmUnpkSztProtIE_Field_E_RABToBeSetupItemCtxtSUReqIEs


/*
* FUN : cmUnpkSztE_RABToBeSetupLstCtxtSUReq
*  DESC: Function to Unpack SztE_RABToBeSetupLstCtxtSUReq structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABToBeSetupLstCtxtSUReq
(
SztE_RABToBeSetupLstCtxtSUReq *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABToBeSetupLstCtxtSUReq(param, ptr, mBuf)
SztE_RABToBeSetupLstCtxtSUReq *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztE_RABToBeSetupLstCtxtSUReq) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_SingleCont_E_RABToBeSetupItemCtxtSUReqIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_SingleCont_E_RABToBeSetupItemCtxtSUReqIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztE_RABToBeSetupLstCtxtSUReq */



/*
* FUN : cmUnpkSzt_ValueInitCntxtSetupRqstIEsCls
*  DESC: Function to Unpack Szt_ValueInitCntxtSetupRqstIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueInitCntxtSetupRqstIEsCls
(
Szt_ValueInitCntxtSetupRqstIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueInitCntxtSetupRqstIEsCls(param, val, ptr, mBuf)
Szt_ValueInitCntxtSetupRqstIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueInitCntxtSetupRqstIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztid_MME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_uEaggregateMaxBitrate:
			CMCHKUNPKPTR(cmUnpkSztUEAggMaxBitrate, &param->u.sztUEAggMaxBitrate, ptr, mBuf);
			break;
		case Sztid_E_RABToBeSetupLstCtxtSUReq:
			CMCHKUNPKPTR(cmUnpkSztE_RABToBeSetupLstCtxtSUReq, &param->u.sztE_RABToBeSetupLstCtxtSUReq, ptr, mBuf);
			break;
		case Sztid_UESecurCapabilities:
			CMCHKUNPKPTR(cmUnpkSztUESecurCapabilities, &param->u.sztUESecurCapabilities, ptr, mBuf);
			break;
		case Sztid_SecurKey:
			CMCHKUNPKPTR(cmUnpkSztSecurKey, &param->u.sztSecurKey, ptr, mBuf); 
			break;
		case Sztid_TraceActvn:
			CMCHKUNPKPTR(cmUnpkSztTraceActvn, &param->u.sztTraceActvn, ptr, mBuf);
			break;
		case Sztid_HovrRestrnLst:
			CMCHKUNPKPTR(cmUnpkSztHovrRestrnLst, &param->u.sztHovrRestrnLst, ptr, mBuf);
			break;
		case Sztid_UERadioCapblty:
			SZUCHKUNPKPTR(cmUnpkSztUERadioCapblty, &param->u.sztUERadioCapblty, ptr, mBuf); 
			break;
		case Sztid_SubscriberProfileIDforRFP:
			CMCHKUNPK(cmUnpkSztSubscriberProfileIDforRFP, &param->u.sztSubscriberProfileIDforRFP, mBuf); 
			break;
		case Sztid_CSFallbackIndicator:
			CMCHKUNPK(cmUnpkSztCSFallbackIndicator, &param->u.sztCSFallbackIndicator, mBuf); 
			break;
		case Sztid_SRVCCOperationPossible:
			CMCHKUNPK(cmUnpkSztSRVCCOperationPossible, &param->u.sztSRVCCOperationPossible, mBuf); 
			break;
		case Sztid_CSGMembershipStatus:
			CMCHKUNPK(cmUnpkSztCSGMembershipStatus, &param->u.sztCSGMembershipStatus, mBuf); 
			break;
		case Sztid_RegisteredLAI:
			CMCHKUNPKPTR(cmUnpkSztLAI, &param->u.sztLAI, ptr, mBuf);
			break;
		case Sztid_GUMMEI_ID:
			CMCHKUNPKPTR(cmUnpkSztGUMMEI, &param->u.sztGUMMEI, ptr, mBuf);
			break;
		case Sztid_MME_UE_S1AP_ID_2:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztid_MME_UE_S1AP_ID_2, mBuf); 
			break;
		case Sztid_ManagementBasedMDTAllowed:
			CMCHKUNPK(cmUnpkSztManagementBasedMDTAllowed, &param->u.sztManagementBasedMDTAllowed, mBuf); 
			break;
		case Sztid_ManagementBasedMDTPLMNLst:
			CMCHKUNPKPTR(cmUnpkSztMDTPLMNLst, &param->u.sztMDTPLMNLst, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueInitCntxtSetupRqstIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_InitCntxtSetupRqstIEs
*  DESC: Function to Unpack SztProtIE_Field_InitCntxtSetupRqstIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_InitCntxtSetupRqstIEs
(
SztProtIE_Field_InitCntxtSetupRqstIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_InitCntxtSetupRqstIEs(param, ptr, mBuf)
SztProtIE_Field_InitCntxtSetupRqstIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_InitCntxtSetupRqstIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueInitCntxtSetupRqstIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_InitCntxtSetupRqstIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_InitCntxtSetupRqstIEs
*  DESC: Function to Unpack SztProtIE_Cont_InitCntxtSetupRqstIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_InitCntxtSetupRqstIEs
(
SztProtIE_Cont_InitCntxtSetupRqstIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_InitCntxtSetupRqstIEs(param, ptr, mBuf)
SztProtIE_Cont_InitCntxtSetupRqstIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_InitCntxtSetupRqstIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_InitCntxtSetupRqstIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_InitCntxtSetupRqstIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_InitCntxtSetupRqstIEs */



/*
* FUN : cmUnpkSztInitCntxtSetupRqst
*  DESC: Function to Unpack SztInitCntxtSetupRqst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztInitCntxtSetupRqst
(
SztInitCntxtSetupRqst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztInitCntxtSetupRqst(param, ptr, mBuf)
SztInitCntxtSetupRqst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztInitCntxtSetupRqst) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_InitCntxtSetupRqstIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztInitCntxtSetupRqst */



/*
* FUN : cmUnpkSzt_ExtnE_RABSetupItemCtxtSUResExtIEsCls
*  DESC: Function to Unpack Szt_ExtnE_RABSetupItemCtxtSUResExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnE_RABSetupItemCtxtSUResExtIEsCls
(
Szt_ExtnE_RABSetupItemCtxtSUResExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnE_RABSetupItemCtxtSUResExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnE_RABSetupItemCtxtSUResExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnE_RABSetupItemCtxtSUResExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnE_RABSetupItemCtxtSUResExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_E_RABSetupItemCtxtSUResExtIEs
*  DESC: Function to Unpack SztProtExtnField_E_RABSetupItemCtxtSUResExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABSetupItemCtxtSUResExtIEs
(
SztProtExtnField_E_RABSetupItemCtxtSUResExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_E_RABSetupItemCtxtSUResExtIEs(param, ptr, mBuf)
SztProtExtnField_E_RABSetupItemCtxtSUResExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_E_RABSetupItemCtxtSUResExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnE_RABSetupItemCtxtSUResExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_E_RABSetupItemCtxtSUResExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs
*  DESC: Function to Unpack SztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs
(
SztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs(param, ptr, mBuf)
SztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_E_RABSetupItemCtxtSUResExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_E_RABSetupItemCtxtSUResExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs */



/*
* FUN : cmUnpkSztE_RABSetupItemCtxtSURes
*  DESC: Function to Unpack SztE_RABSetupItemCtxtSURes structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABSetupItemCtxtSURes
(
SztE_RABSetupItemCtxtSURes *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABSetupItemCtxtSURes(param, ptr, mBuf)
SztE_RABSetupItemCtxtSURes *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztE_RABSetupItemCtxtSURes) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztE_RAB_ID, &param->e_RAB_ID, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztTportLyrAddr, &param->transportLyrAddr, ptr, mBuf); 
		SZUCHKUNPKPTR(cmUnpkSztGTP_TEID, &param->gTP_TEID, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_E_RABSetupItemCtxtSUResExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztE_RABSetupItemCtxtSURes */



/*
* FUN : cmUnpkSzt_ValueE_RABSetupItemCtxtSUResIEsCls
*  DESC: Function to Unpack Szt_ValueE_RABSetupItemCtxtSUResIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueE_RABSetupItemCtxtSUResIEsCls
(
Szt_ValueE_RABSetupItemCtxtSUResIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueE_RABSetupItemCtxtSUResIEsCls(param, val, ptr, mBuf)
Szt_ValueE_RABSetupItemCtxtSUResIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueE_RABSetupItemCtxtSUResIEsCls) 
	
	switch (val)
	{
		case Sztid_E_RABSetupItemCtxtSURes:
			CMCHKUNPKPTR(cmUnpkSztE_RABSetupItemCtxtSURes, &param->u.sztE_RABSetupItemCtxtSURes, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueE_RABSetupItemCtxtSUResIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_E_RABSetupItemCtxtSUResIEs
*  DESC: Function to Unpack SztProtIE_Field_E_RABSetupItemCtxtSUResIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABSetupItemCtxtSUResIEs
(
SztProtIE_Field_E_RABSetupItemCtxtSUResIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_E_RABSetupItemCtxtSUResIEs(param, ptr, mBuf)
SztProtIE_Field_E_RABSetupItemCtxtSUResIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_E_RABSetupItemCtxtSUResIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueE_RABSetupItemCtxtSUResIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_E_RABSetupItemCtxtSUResIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmUnpkSztProtIE_SingleCont_E_RABSetupItemCtxtSUResIEs cmUnpkSztProtIE_Field_E_RABSetupItemCtxtSUResIEs


/*
* FUN : cmUnpkSztE_RABSetupLstCtxtSURes
*  DESC: Function to Unpack SztE_RABSetupLstCtxtSURes structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztE_RABSetupLstCtxtSURes
(
SztE_RABSetupLstCtxtSURes *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztE_RABSetupLstCtxtSURes(param, ptr, mBuf)
SztE_RABSetupLstCtxtSURes *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztE_RABSetupLstCtxtSURes) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_SingleCont_E_RABSetupItemCtxtSUResIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_SingleCont_E_RABSetupItemCtxtSUResIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztE_RABSetupLstCtxtSURes */



/*
* FUN : cmUnpkSzt_ValueInitCntxtSetupRespIEsCls
*  DESC: Function to Unpack Szt_ValueInitCntxtSetupRespIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueInitCntxtSetupRespIEsCls
(
Szt_ValueInitCntxtSetupRespIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueInitCntxtSetupRespIEsCls(param, val, ptr, mBuf)
Szt_ValueInitCntxtSetupRespIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueInitCntxtSetupRespIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_E_RABSetupLstCtxtSURes:
			CMCHKUNPKPTR(cmUnpkSztE_RABSetupLstCtxtSURes, &param->u.sztE_RABSetupLstCtxtSURes, ptr, mBuf);
			break;
		case Sztid_E_RABFailedToSetupLstCtxtSURes:
			CMCHKUNPKPTR(cmUnpkSztE_RABLst, &param->u.sztE_RABLst, ptr, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkSztCriticalityDiag, &param->u.sztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueInitCntxtSetupRespIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_InitCntxtSetupRespIEs
*  DESC: Function to Unpack SztProtIE_Field_InitCntxtSetupRespIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_InitCntxtSetupRespIEs
(
SztProtIE_Field_InitCntxtSetupRespIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_InitCntxtSetupRespIEs(param, ptr, mBuf)
SztProtIE_Field_InitCntxtSetupRespIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_InitCntxtSetupRespIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueInitCntxtSetupRespIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_InitCntxtSetupRespIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_InitCntxtSetupRespIEs
*  DESC: Function to Unpack SztProtIE_Cont_InitCntxtSetupRespIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_InitCntxtSetupRespIEs
(
SztProtIE_Cont_InitCntxtSetupRespIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_InitCntxtSetupRespIEs(param, ptr, mBuf)
SztProtIE_Cont_InitCntxtSetupRespIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_InitCntxtSetupRespIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_InitCntxtSetupRespIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_InitCntxtSetupRespIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_InitCntxtSetupRespIEs */



/*
* FUN : cmUnpkSztInitCntxtSetupResp
*  DESC: Function to Unpack SztInitCntxtSetupResp structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztInitCntxtSetupResp
(
SztInitCntxtSetupResp *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztInitCntxtSetupResp(param, ptr, mBuf)
SztInitCntxtSetupResp *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztInitCntxtSetupResp) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_InitCntxtSetupRespIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztInitCntxtSetupResp */



/*
* FUN : cmUnpkSzt_ValueInitCntxtSetupFailIEsCls
*  DESC: Function to Unpack Szt_ValueInitCntxtSetupFailIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueInitCntxtSetupFailIEsCls
(
Szt_ValueInitCntxtSetupFailIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueInitCntxtSetupFailIEsCls(param, val, ptr, mBuf)
Szt_ValueInitCntxtSetupFailIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueInitCntxtSetupFailIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_Cause:
			CMCHKUNPKPTR(cmUnpkSztCause, &param->u.sztCause, ptr, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkSztCriticalityDiag, &param->u.sztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueInitCntxtSetupFailIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_InitCntxtSetupFailIEs
*  DESC: Function to Unpack SztProtIE_Field_InitCntxtSetupFailIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_InitCntxtSetupFailIEs
(
SztProtIE_Field_InitCntxtSetupFailIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_InitCntxtSetupFailIEs(param, ptr, mBuf)
SztProtIE_Field_InitCntxtSetupFailIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_InitCntxtSetupFailIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueInitCntxtSetupFailIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_InitCntxtSetupFailIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_InitCntxtSetupFailIEs
*  DESC: Function to Unpack SztProtIE_Cont_InitCntxtSetupFailIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_InitCntxtSetupFailIEs
(
SztProtIE_Cont_InitCntxtSetupFailIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_InitCntxtSetupFailIEs(param, ptr, mBuf)
SztProtIE_Cont_InitCntxtSetupFailIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_InitCntxtSetupFailIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_InitCntxtSetupFailIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_InitCntxtSetupFailIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_InitCntxtSetupFailIEs */



/*
* FUN : cmUnpkSztInitCntxtSetupFail
*  DESC: Function to Unpack SztInitCntxtSetupFail structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztInitCntxtSetupFail
(
SztInitCntxtSetupFail *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztInitCntxtSetupFail(param, ptr, mBuf)
SztInitCntxtSetupFail *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztInitCntxtSetupFail) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_InitCntxtSetupFailIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztInitCntxtSetupFail */



/*
* FUN : cmUnpkSzt_ExtnTAIItemExtIEsCls
*  DESC: Function to Unpack Szt_ExtnTAIItemExtIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ExtnTAIItemExtIEsCls
(
Szt_ExtnTAIItemExtIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ExtnTAIItemExtIEsCls(param, val, ptr, mBuf)
Szt_ExtnTAIItemExtIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ExtnTAIItemExtIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ExtnTAIItemExtIEsCls */



/*
* FUN : cmUnpkSztProtExtnField_TAIItemExtIEs
*  DESC: Function to Unpack SztProtExtnField_TAIItemExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnField_TAIItemExtIEs
(
SztProtExtnField_TAIItemExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnField_TAIItemExtIEs(param, ptr, mBuf)
SztProtExtnField_TAIItemExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtExtnField_TAIItemExtIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtExtnID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ExtnTAIItemExtIEsCls(&param->extensionValue, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtExtnField_TAIItemExtIEs */



/*
* FUN : cmUnpkSztProtExtnCont_TAIItemExtIEs
*  DESC: Function to Unpack SztProtExtnCont_TAIItemExtIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtExtnCont_TAIItemExtIEs
(
SztProtExtnCont_TAIItemExtIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtExtnCont_TAIItemExtIEs(param, ptr, mBuf)
SztProtExtnCont_TAIItemExtIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtExtnCont_TAIItemExtIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtExtnField_TAIItemExtIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtExtnField_TAIItemExtIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtExtnCont_TAIItemExtIEs */



/*
* FUN : cmUnpkSztTAIItem
*  DESC: Function to Unpack SztTAIItem structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztTAIItem
(
SztTAIItem *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztTAIItem(param, ptr, mBuf)
SztTAIItem *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztTAIItem) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztTAI, &param->tAI, ptr, mBuf); 
		CMCHKUNPKPTR(cmUnpkSztProtExtnCont_TAIItemExtIEs, &param->iE_Extns, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztTAIItem */



/*
* FUN : cmUnpkSzt_ValueTAIItemIEsCls
*  DESC: Function to Unpack Szt_ValueTAIItemIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueTAIItemIEsCls
(
Szt_ValueTAIItemIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueTAIItemIEsCls(param, val, ptr, mBuf)
Szt_ValueTAIItemIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueTAIItemIEsCls) 
	
	switch (val)
	{
		case Sztid_TAIItem:
			CMCHKUNPKPTR(cmUnpkSztTAIItem, &param->u.sztTAIItem, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueTAIItemIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_TAIItemIEs
*  DESC: Function to Unpack SztProtIE_Field_TAIItemIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_TAIItemIEs
(
SztProtIE_Field_TAIItemIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_TAIItemIEs(param, ptr, mBuf)
SztProtIE_Field_TAIItemIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_TAIItemIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueTAIItemIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_TAIItemIEs */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmUnpkSztProtIE_SingleCont_TAIItemIEs cmUnpkSztProtIE_Field_TAIItemIEs


/*
* FUN : cmUnpkSztTAILst
*  DESC: Function to Unpack SztTAILst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztTAILst
(
SztTAILst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztTAILst(param, ptr, mBuf)
SztTAILst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztTAILst) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_SingleCont_TAIItemIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_SingleCont_TAIItemIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztTAILst */



/*
* FUN : cmUnpkSzt_ValuePagIEsCls
*  DESC: Function to Unpack Szt_ValuePagIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValuePagIEsCls
(
Szt_ValuePagIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValuePagIEsCls(param, val, ptr, mBuf)
Szt_ValuePagIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValuePagIEsCls) 
	
	switch (val)
	{
		case Sztid_UEIdentityIdxValue:
			CMCHKUNPK(cmUnpkSztUEIdentityIdxValue, &param->u.sztUEIdentityIdxValue, mBuf); 
			break;
		case Sztid_UEPagID:
			CMCHKUNPKPTR(cmUnpkSztUEPagID, &param->u.sztUEPagID, ptr, mBuf);
			break;
		case Sztid_pagingDRX:
			CMCHKUNPK(cmUnpkSztPagDRX, &param->u.sztPagDRX, mBuf); 
			break;
		case Sztid_CNDomain:
			CMCHKUNPK(cmUnpkSztCNDomain, &param->u.sztCNDomain, mBuf); 
			break;
		case Sztid_TAILst:
			CMCHKUNPKPTR(cmUnpkSztTAILst, &param->u.sztTAILst, ptr, mBuf);
			break;
		case Sztid_CSG_IdLst:
			CMCHKUNPKPTR(cmUnpkSztCSG_IdLst, &param->u.sztCSG_IdLst, ptr, mBuf);
			break;
		case Sztid_PagPriority:
			CMCHKUNPK(cmUnpkSztPagPriority, &param->u.sztPagPriority, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValuePagIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_PagIEs
*  DESC: Function to Unpack SztProtIE_Field_PagIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_PagIEs
(
SztProtIE_Field_PagIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_PagIEs(param, ptr, mBuf)
SztProtIE_Field_PagIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_PagIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValuePagIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_PagIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_PagIEs
*  DESC: Function to Unpack SztProtIE_Cont_PagIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_PagIEs
(
SztProtIE_Cont_PagIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_PagIEs(param, ptr, mBuf)
SztProtIE_Cont_PagIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_PagIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_PagIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_PagIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_PagIEs */



/*
* FUN : cmUnpkSztPag
*  DESC: Function to Unpack SztPag structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztPag
(
SztPag *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztPag(param, ptr, mBuf)
SztPag *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztPag) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_PagIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztPag */



/*
* FUN : cmUnpkSzt_ValueUECntxtRlsRqst_IEsCls
*  DESC: Function to Unpack Szt_ValueUECntxtRlsRqst_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueUECntxtRlsRqst_IEsCls
(
Szt_ValueUECntxtRlsRqst_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueUECntxtRlsRqst_IEsCls(param, val, ptr, mBuf)
Szt_ValueUECntxtRlsRqst_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueUECntxtRlsRqst_IEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_Cause:
			CMCHKUNPKPTR(cmUnpkSztCause, &param->u.sztCause, ptr, mBuf);
			break;
		case Sztid_GWCntxtRlsInd:
			CMCHKUNPK(cmUnpkSztGWCntxtRlsInd, &param->u.sztGWCntxtRlsInd, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueUECntxtRlsRqst_IEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_UECntxtRlsRqst_IEs
*  DESC: Function to Unpack SztProtIE_Field_UECntxtRlsRqst_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_UECntxtRlsRqst_IEs
(
SztProtIE_Field_UECntxtRlsRqst_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_UECntxtRlsRqst_IEs(param, ptr, mBuf)
SztProtIE_Field_UECntxtRlsRqst_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_UECntxtRlsRqst_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueUECntxtRlsRqst_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_UECntxtRlsRqst_IEs */



/*
* FUN : cmUnpkSztProtIE_Cont_UECntxtRlsRqst_IEs
*  DESC: Function to Unpack SztProtIE_Cont_UECntxtRlsRqst_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_UECntxtRlsRqst_IEs
(
SztProtIE_Cont_UECntxtRlsRqst_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_UECntxtRlsRqst_IEs(param, ptr, mBuf)
SztProtIE_Cont_UECntxtRlsRqst_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_UECntxtRlsRqst_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_UECntxtRlsRqst_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_UECntxtRlsRqst_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_UECntxtRlsRqst_IEs */



/*
* FUN : cmUnpkSztUECntxtRlsRqst
*  DESC: Function to Unpack SztUECntxtRlsRqst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztUECntxtRlsRqst
(
SztUECntxtRlsRqst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztUECntxtRlsRqst(param, ptr, mBuf)
SztUECntxtRlsRqst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztUECntxtRlsRqst) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_UECntxtRlsRqst_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztUECntxtRlsRqst */



/*
* FUN : cmUnpkSzt_ValueUECntxtRlsCmmd_IEsCls
*  DESC: Function to Unpack Szt_ValueUECntxtRlsCmmd_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueUECntxtRlsCmmd_IEsCls
(
Szt_ValueUECntxtRlsCmmd_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueUECntxtRlsCmmd_IEsCls(param, val, ptr, mBuf)
Szt_ValueUECntxtRlsCmmd_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueUECntxtRlsCmmd_IEsCls) 
	
	switch (val)
	{
		case Sztid_UE_S1AP_IDs:
			CMCHKUNPKPTR(cmUnpkSztUE_S1AP_IDs, &param->u.sztUE_S1AP_IDs, ptr, mBuf);
			break;
		case Sztid_Cause:
			CMCHKUNPKPTR(cmUnpkSztCause, &param->u.sztCause, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueUECntxtRlsCmmd_IEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_UECntxtRlsCmmd_IEs
*  DESC: Function to Unpack SztProtIE_Field_UECntxtRlsCmmd_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_UECntxtRlsCmmd_IEs
(
SztProtIE_Field_UECntxtRlsCmmd_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_UECntxtRlsCmmd_IEs(param, ptr, mBuf)
SztProtIE_Field_UECntxtRlsCmmd_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_UECntxtRlsCmmd_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueUECntxtRlsCmmd_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_UECntxtRlsCmmd_IEs */



/*
* FUN : cmUnpkSztProtIE_Cont_UECntxtRlsCmmd_IEs
*  DESC: Function to Unpack SztProtIE_Cont_UECntxtRlsCmmd_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_UECntxtRlsCmmd_IEs
(
SztProtIE_Cont_UECntxtRlsCmmd_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_UECntxtRlsCmmd_IEs(param, ptr, mBuf)
SztProtIE_Cont_UECntxtRlsCmmd_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_UECntxtRlsCmmd_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_UECntxtRlsCmmd_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_UECntxtRlsCmmd_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_UECntxtRlsCmmd_IEs */



/*
* FUN : cmUnpkSztUECntxtRlsCmmd
*  DESC: Function to Unpack SztUECntxtRlsCmmd structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztUECntxtRlsCmmd
(
SztUECntxtRlsCmmd *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztUECntxtRlsCmmd(param, ptr, mBuf)
SztUECntxtRlsCmmd *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztUECntxtRlsCmmd) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_UECntxtRlsCmmd_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztUECntxtRlsCmmd */



/*
* FUN : cmUnpkSzt_ValueUECntxtRlsComplete_IEsCls
*  DESC: Function to Unpack Szt_ValueUECntxtRlsComplete_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueUECntxtRlsComplete_IEsCls
(
Szt_ValueUECntxtRlsComplete_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueUECntxtRlsComplete_IEsCls(param, val, ptr, mBuf)
Szt_ValueUECntxtRlsComplete_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueUECntxtRlsComplete_IEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkSztCriticalityDiag, &param->u.sztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueUECntxtRlsComplete_IEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_UECntxtRlsComplete_IEs
*  DESC: Function to Unpack SztProtIE_Field_UECntxtRlsComplete_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_UECntxtRlsComplete_IEs
(
SztProtIE_Field_UECntxtRlsComplete_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_UECntxtRlsComplete_IEs(param, ptr, mBuf)
SztProtIE_Field_UECntxtRlsComplete_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_UECntxtRlsComplete_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueUECntxtRlsComplete_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_UECntxtRlsComplete_IEs */



/*
* FUN : cmUnpkSztProtIE_Cont_UECntxtRlsComplete_IEs
*  DESC: Function to Unpack SztProtIE_Cont_UECntxtRlsComplete_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_UECntxtRlsComplete_IEs
(
SztProtIE_Cont_UECntxtRlsComplete_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_UECntxtRlsComplete_IEs(param, ptr, mBuf)
SztProtIE_Cont_UECntxtRlsComplete_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_UECntxtRlsComplete_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_UECntxtRlsComplete_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_UECntxtRlsComplete_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_UECntxtRlsComplete_IEs */



/*
* FUN : cmUnpkSztUECntxtRlsComplete
*  DESC: Function to Unpack SztUECntxtRlsComplete structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztUECntxtRlsComplete
(
SztUECntxtRlsComplete *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztUECntxtRlsComplete(param, ptr, mBuf)
SztUECntxtRlsComplete *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztUECntxtRlsComplete) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_UECntxtRlsComplete_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztUECntxtRlsComplete */



/*
* FUN : cmUnpkSzt_ValueUECntxtModificationRqstIEsCls
*  DESC: Function to Unpack Szt_ValueUECntxtModificationRqstIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueUECntxtModificationRqstIEsCls
(
Szt_ValueUECntxtModificationRqstIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueUECntxtModificationRqstIEsCls(param, val, ptr, mBuf)
Szt_ValueUECntxtModificationRqstIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueUECntxtModificationRqstIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_SecurKey:
			CMCHKUNPKPTR(cmUnpkSztSecurKey, &param->u.sztSecurKey, ptr, mBuf); 
			break;
		case Sztid_SubscriberProfileIDforRFP:
			CMCHKUNPK(cmUnpkSztSubscriberProfileIDforRFP, &param->u.sztSubscriberProfileIDforRFP, mBuf); 
			break;
		case Sztid_uEaggregateMaxBitrate:
			CMCHKUNPKPTR(cmUnpkSztUEAggMaxBitrate, &param->u.sztUEAggMaxBitrate, ptr, mBuf);
			break;
		case Sztid_CSFallbackIndicator:
			CMCHKUNPK(cmUnpkSztCSFallbackIndicator, &param->u.sztCSFallbackIndicator, mBuf); 
			break;
		case Sztid_UESecurCapabilities:
			CMCHKUNPKPTR(cmUnpkSztUESecurCapabilities, &param->u.sztUESecurCapabilities, ptr, mBuf);
			break;
		case Sztid_CSGMembershipStatus:
			CMCHKUNPK(cmUnpkSztCSGMembershipStatus, &param->u.sztCSGMembershipStatus, mBuf); 
			break;
		case Sztid_RegisteredLAI:
			CMCHKUNPKPTR(cmUnpkSztLAI, &param->u.sztLAI, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueUECntxtModificationRqstIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_UECntxtModificationRqstIEs
*  DESC: Function to Unpack SztProtIE_Field_UECntxtModificationRqstIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_UECntxtModificationRqstIEs
(
SztProtIE_Field_UECntxtModificationRqstIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_UECntxtModificationRqstIEs(param, ptr, mBuf)
SztProtIE_Field_UECntxtModificationRqstIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_UECntxtModificationRqstIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueUECntxtModificationRqstIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_UECntxtModificationRqstIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_UECntxtModificationRqstIEs
*  DESC: Function to Unpack SztProtIE_Cont_UECntxtModificationRqstIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_UECntxtModificationRqstIEs
(
SztProtIE_Cont_UECntxtModificationRqstIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_UECntxtModificationRqstIEs(param, ptr, mBuf)
SztProtIE_Cont_UECntxtModificationRqstIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_UECntxtModificationRqstIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_UECntxtModificationRqstIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_UECntxtModificationRqstIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_UECntxtModificationRqstIEs */



/*
* FUN : cmUnpkSztUECntxtModificationRqst
*  DESC: Function to Unpack SztUECntxtModificationRqst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztUECntxtModificationRqst
(
SztUECntxtModificationRqst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztUECntxtModificationRqst(param, ptr, mBuf)
SztUECntxtModificationRqst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztUECntxtModificationRqst) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_UECntxtModificationRqstIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztUECntxtModificationRqst */



/*
* FUN : cmUnpkSzt_ValueUECntxtModificationRespIEsCls
*  DESC: Function to Unpack Szt_ValueUECntxtModificationRespIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueUECntxtModificationRespIEsCls
(
Szt_ValueUECntxtModificationRespIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueUECntxtModificationRespIEsCls(param, val, ptr, mBuf)
Szt_ValueUECntxtModificationRespIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueUECntxtModificationRespIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkSztCriticalityDiag, &param->u.sztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueUECntxtModificationRespIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_UECntxtModificationRespIEs
*  DESC: Function to Unpack SztProtIE_Field_UECntxtModificationRespIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_UECntxtModificationRespIEs
(
SztProtIE_Field_UECntxtModificationRespIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_UECntxtModificationRespIEs(param, ptr, mBuf)
SztProtIE_Field_UECntxtModificationRespIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_UECntxtModificationRespIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueUECntxtModificationRespIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_UECntxtModificationRespIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_UECntxtModificationRespIEs
*  DESC: Function to Unpack SztProtIE_Cont_UECntxtModificationRespIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_UECntxtModificationRespIEs
(
SztProtIE_Cont_UECntxtModificationRespIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_UECntxtModificationRespIEs(param, ptr, mBuf)
SztProtIE_Cont_UECntxtModificationRespIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_UECntxtModificationRespIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_UECntxtModificationRespIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_UECntxtModificationRespIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_UECntxtModificationRespIEs */



/*
* FUN : cmUnpkSztUECntxtModificationResp
*  DESC: Function to Unpack SztUECntxtModificationResp structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztUECntxtModificationResp
(
SztUECntxtModificationResp *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztUECntxtModificationResp(param, ptr, mBuf)
SztUECntxtModificationResp *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztUECntxtModificationResp) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_UECntxtModificationRespIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztUECntxtModificationResp */



/*
* FUN : cmUnpkSzt_ValueUECntxtModificationFailIEsCls
*  DESC: Function to Unpack Szt_ValueUECntxtModificationFailIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueUECntxtModificationFailIEsCls
(
Szt_ValueUECntxtModificationFailIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueUECntxtModificationFailIEsCls(param, val, ptr, mBuf)
Szt_ValueUECntxtModificationFailIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueUECntxtModificationFailIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_Cause:
			CMCHKUNPKPTR(cmUnpkSztCause, &param->u.sztCause, ptr, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkSztCriticalityDiag, &param->u.sztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueUECntxtModificationFailIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_UECntxtModificationFailIEs
*  DESC: Function to Unpack SztProtIE_Field_UECntxtModificationFailIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_UECntxtModificationFailIEs
(
SztProtIE_Field_UECntxtModificationFailIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_UECntxtModificationFailIEs(param, ptr, mBuf)
SztProtIE_Field_UECntxtModificationFailIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_UECntxtModificationFailIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueUECntxtModificationFailIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_UECntxtModificationFailIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_UECntxtModificationFailIEs
*  DESC: Function to Unpack SztProtIE_Cont_UECntxtModificationFailIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_UECntxtModificationFailIEs
(
SztProtIE_Cont_UECntxtModificationFailIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_UECntxtModificationFailIEs(param, ptr, mBuf)
SztProtIE_Cont_UECntxtModificationFailIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_UECntxtModificationFailIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_UECntxtModificationFailIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_UECntxtModificationFailIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_UECntxtModificationFailIEs */



/*
* FUN : cmUnpkSztUECntxtModificationFail
*  DESC: Function to Unpack SztUECntxtModificationFail structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztUECntxtModificationFail
(
SztUECntxtModificationFail *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztUECntxtModificationFail(param, ptr, mBuf)
SztUECntxtModificationFail *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztUECntxtModificationFail) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_UECntxtModificationFailIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztUECntxtModificationFail */



/*
* FUN : cmUnpkSzt_ValueUERadioCapbltyMatchRqstIEsCls
*  DESC: Function to Unpack Szt_ValueUERadioCapbltyMatchRqstIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueUERadioCapbltyMatchRqstIEsCls
(
Szt_ValueUERadioCapbltyMatchRqstIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueUERadioCapbltyMatchRqstIEsCls(param, val, ptr, mBuf)
Szt_ValueUERadioCapbltyMatchRqstIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueUERadioCapbltyMatchRqstIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_UERadioCapblty:
			SZUCHKUNPKPTR(cmUnpkSztUERadioCapblty, &param->u.sztUERadioCapblty, ptr, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueUERadioCapbltyMatchRqstIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_UERadioCapbltyMatchRqstIEs
*  DESC: Function to Unpack SztProtIE_Field_UERadioCapbltyMatchRqstIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_UERadioCapbltyMatchRqstIEs
(
SztProtIE_Field_UERadioCapbltyMatchRqstIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_UERadioCapbltyMatchRqstIEs(param, ptr, mBuf)
SztProtIE_Field_UERadioCapbltyMatchRqstIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_UERadioCapbltyMatchRqstIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueUERadioCapbltyMatchRqstIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_UERadioCapbltyMatchRqstIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_UERadioCapbltyMatchRqstIEs
*  DESC: Function to Unpack SztProtIE_Cont_UERadioCapbltyMatchRqstIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_UERadioCapbltyMatchRqstIEs
(
SztProtIE_Cont_UERadioCapbltyMatchRqstIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_UERadioCapbltyMatchRqstIEs(param, ptr, mBuf)
SztProtIE_Cont_UERadioCapbltyMatchRqstIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_UERadioCapbltyMatchRqstIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_UERadioCapbltyMatchRqstIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_UERadioCapbltyMatchRqstIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_UERadioCapbltyMatchRqstIEs */



/*
* FUN : cmUnpkSztUERadioCapbltyMatchRqst
*  DESC: Function to Unpack SztUERadioCapbltyMatchRqst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztUERadioCapbltyMatchRqst
(
SztUERadioCapbltyMatchRqst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztUERadioCapbltyMatchRqst(param, ptr, mBuf)
SztUERadioCapbltyMatchRqst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztUERadioCapbltyMatchRqst) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_UERadioCapbltyMatchRqstIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztUERadioCapbltyMatchRqst */



/*
* FUN : cmUnpkSzt_ValueUERadioCapbltyMatchRespIEsCls
*  DESC: Function to Unpack Szt_ValueUERadioCapbltyMatchRespIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueUERadioCapbltyMatchRespIEsCls
(
Szt_ValueUERadioCapbltyMatchRespIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueUERadioCapbltyMatchRespIEsCls(param, val, ptr, mBuf)
Szt_ValueUERadioCapbltyMatchRespIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueUERadioCapbltyMatchRespIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_VoiceSupportMatchIndicator:
			CMCHKUNPK(cmUnpkSztVoiceSupportMatchIndicator, &param->u.sztVoiceSupportMatchIndicator, mBuf); 
			break;
		case Sztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkSztCriticalityDiag, &param->u.sztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueUERadioCapbltyMatchRespIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_UERadioCapbltyMatchRespIEs
*  DESC: Function to Unpack SztProtIE_Field_UERadioCapbltyMatchRespIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_UERadioCapbltyMatchRespIEs
(
SztProtIE_Field_UERadioCapbltyMatchRespIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_UERadioCapbltyMatchRespIEs(param, ptr, mBuf)
SztProtIE_Field_UERadioCapbltyMatchRespIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_UERadioCapbltyMatchRespIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueUERadioCapbltyMatchRespIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_UERadioCapbltyMatchRespIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_UERadioCapbltyMatchRespIEs
*  DESC: Function to Unpack SztProtIE_Cont_UERadioCapbltyMatchRespIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_UERadioCapbltyMatchRespIEs
(
SztProtIE_Cont_UERadioCapbltyMatchRespIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_UERadioCapbltyMatchRespIEs(param, ptr, mBuf)
SztProtIE_Cont_UERadioCapbltyMatchRespIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_UERadioCapbltyMatchRespIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_UERadioCapbltyMatchRespIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_UERadioCapbltyMatchRespIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_UERadioCapbltyMatchRespIEs */



/*
* FUN : cmUnpkSztUERadioCapbltyMatchResp
*  DESC: Function to Unpack SztUERadioCapbltyMatchResp structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztUERadioCapbltyMatchResp
(
SztUERadioCapbltyMatchResp *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztUERadioCapbltyMatchResp(param, ptr, mBuf)
SztUERadioCapbltyMatchResp *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztUERadioCapbltyMatchResp) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_UERadioCapbltyMatchRespIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztUERadioCapbltyMatchResp */



/*
* FUN : cmUnpkSzt_ValueDlnkNASTport_IEsCls
*  DESC: Function to Unpack Szt_ValueDlnkNASTport_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueDlnkNASTport_IEsCls
(
Szt_ValueDlnkNASTport_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueDlnkNASTport_IEsCls(param, val, ptr, mBuf)
Szt_ValueDlnkNASTport_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueDlnkNASTport_IEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_NAS_PDU:
			SZUCHKUNPKPTR(cmUnpkSztNAS_PDU, &param->u.sztNAS_PDU, ptr, mBuf); 
			break;
		case Sztid_HovrRestrnLst:
			CMCHKUNPKPTR(cmUnpkSztHovrRestrnLst, &param->u.sztHovrRestrnLst, ptr, mBuf);
			break;
		case Sztid_SubscriberProfileIDforRFP:
			CMCHKUNPK(cmUnpkSztSubscriberProfileIDforRFP, &param->u.sztSubscriberProfileIDforRFP, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueDlnkNASTport_IEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_DlnkNASTport_IEs
*  DESC: Function to Unpack SztProtIE_Field_DlnkNASTport_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_DlnkNASTport_IEs
(
SztProtIE_Field_DlnkNASTport_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_DlnkNASTport_IEs(param, ptr, mBuf)
SztProtIE_Field_DlnkNASTport_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_DlnkNASTport_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueDlnkNASTport_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_DlnkNASTport_IEs */



/*
* FUN : cmUnpkSztProtIE_Cont_DlnkNASTport_IEs
*  DESC: Function to Unpack SztProtIE_Cont_DlnkNASTport_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_DlnkNASTport_IEs
(
SztProtIE_Cont_DlnkNASTport_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_DlnkNASTport_IEs(param, ptr, mBuf)
SztProtIE_Cont_DlnkNASTport_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_DlnkNASTport_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_DlnkNASTport_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_DlnkNASTport_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_DlnkNASTport_IEs */



/*
* FUN : cmUnpkSztDlnkNASTport
*  DESC: Function to Unpack SztDlnkNASTport structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztDlnkNASTport
(
SztDlnkNASTport *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztDlnkNASTport(param, ptr, mBuf)
SztDlnkNASTport *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztDlnkNASTport) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_DlnkNASTport_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztDlnkNASTport */



/*
* FUN : cmUnpkSzt_ValueInitUEMsg_IEsCls
*  DESC: Function to Unpack Szt_ValueInitUEMsg_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueInitUEMsg_IEsCls
(
Szt_ValueInitUEMsg_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueInitUEMsg_IEsCls(param, val, ptr, mBuf)
Szt_ValueInitUEMsg_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueInitUEMsg_IEsCls) 
	
	switch (val)
	{
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_NAS_PDU:
			SZUCHKUNPKPTR(cmUnpkSztNAS_PDU, &param->u.sztNAS_PDU, ptr, mBuf); 
			break;
		case Sztid_TAI:
			CMCHKUNPKPTR(cmUnpkSztTAI, &param->u.sztTAI, ptr, mBuf);
			break;
		case Sztid_EUTRAN_CGI:
			CMCHKUNPKPTR(cmUnpkSztEUTRAN_CGI, &param->u.sztEUTRAN_CGI, ptr, mBuf);
			break;
		case Sztid_RRC_Establishment_Cause:
			CMCHKUNPK(cmUnpkSztRRC_Establishment_Cause, &param->u.sztRRC_Establishment_Cause, mBuf); 
			break;
		case Sztid_S_TMSI:
			CMCHKUNPKPTR(cmUnpkSztS_TMSI, &param->u.sztS_TMSI, ptr, mBuf);
			break;
		case Sztid_CSG_Id:
			CMCHKUNPK(cmUnpkSztCSG_Id, &param->u.sztCSG_Id, mBuf); 
			break;
		case Sztid_GUMMEI_ID:
			CMCHKUNPKPTR(cmUnpkSztGUMMEI, &param->u.sztGUMMEI, ptr, mBuf);
			break;
		case Sztid_CellAccessMode:
			CMCHKUNPK(cmUnpkSztCellAccessMode, &param->u.sztCellAccessMode, mBuf); 
			break;
		case Sztid_GW_TportLyrAddr:
			CMCHKUNPKPTR(cmUnpkSztTportLyrAddr, &param->u.sztTportLyrAddr, ptr, mBuf); 
			break;
		case Sztid_RelayNode_Indicator:
			CMCHKUNPK(cmUnpkSztRelayNode_Indicator, &param->u.sztRelayNode_Indicator, mBuf); 
			break;
		case Sztid_GUMMEITyp:
			CMCHKUNPK(cmUnpkSztGUMMEITyp, &param->u.sztGUMMEITyp, mBuf); 
			break;
		case Sztid_Tunnel_Inform_for_BBF:
			CMCHKUNPKPTR(cmUnpkSztTunnelInform, &param->u.sztTunnelInform, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueInitUEMsg_IEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_InitUEMsg_IEs
*  DESC: Function to Unpack SztProtIE_Field_InitUEMsg_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_InitUEMsg_IEs
(
SztProtIE_Field_InitUEMsg_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_InitUEMsg_IEs(param, ptr, mBuf)
SztProtIE_Field_InitUEMsg_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_InitUEMsg_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueInitUEMsg_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_InitUEMsg_IEs */



/*
* FUN : cmUnpkSztProtIE_Cont_InitUEMsg_IEs
*  DESC: Function to Unpack SztProtIE_Cont_InitUEMsg_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_InitUEMsg_IEs
(
SztProtIE_Cont_InitUEMsg_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_InitUEMsg_IEs(param, ptr, mBuf)
SztProtIE_Cont_InitUEMsg_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_InitUEMsg_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_InitUEMsg_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_InitUEMsg_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_InitUEMsg_IEs */



/*
* FUN : cmUnpkSztInitUEMsg
*  DESC: Function to Unpack SztInitUEMsg structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztInitUEMsg
(
SztInitUEMsg *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztInitUEMsg(param, ptr, mBuf)
SztInitUEMsg *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztInitUEMsg) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_InitUEMsg_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztInitUEMsg */



/*
* FUN : cmUnpkSzt_ValueUlnkNASTport_IEsCls
*  DESC: Function to Unpack Szt_ValueUlnkNASTport_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueUlnkNASTport_IEsCls
(
Szt_ValueUlnkNASTport_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueUlnkNASTport_IEsCls(param, val, ptr, mBuf)
Szt_ValueUlnkNASTport_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueUlnkNASTport_IEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_NAS_PDU:
			SZUCHKUNPKPTR(cmUnpkSztNAS_PDU, &param->u.sztNAS_PDU, ptr, mBuf); 
			break;
		case Sztid_EUTRAN_CGI:
			CMCHKUNPKPTR(cmUnpkSztEUTRAN_CGI, &param->u.sztEUTRAN_CGI, ptr, mBuf);
			break;
		case Sztid_TAI:
			CMCHKUNPKPTR(cmUnpkSztTAI, &param->u.sztTAI, ptr, mBuf);
			break;
		case Sztid_GW_TportLyrAddr:
			CMCHKUNPKPTR(cmUnpkSztTportLyrAddr, &param->u.sztTportLyrAddr, ptr, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueUlnkNASTport_IEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_UlnkNASTport_IEs
*  DESC: Function to Unpack SztProtIE_Field_UlnkNASTport_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_UlnkNASTport_IEs
(
SztProtIE_Field_UlnkNASTport_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_UlnkNASTport_IEs(param, ptr, mBuf)
SztProtIE_Field_UlnkNASTport_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_UlnkNASTport_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueUlnkNASTport_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_UlnkNASTport_IEs */



/*
* FUN : cmUnpkSztProtIE_Cont_UlnkNASTport_IEs
*  DESC: Function to Unpack SztProtIE_Cont_UlnkNASTport_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_UlnkNASTport_IEs
(
SztProtIE_Cont_UlnkNASTport_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_UlnkNASTport_IEs(param, ptr, mBuf)
SztProtIE_Cont_UlnkNASTport_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_UlnkNASTport_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_UlnkNASTport_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_UlnkNASTport_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_UlnkNASTport_IEs */



/*
* FUN : cmUnpkSztUlnkNASTport
*  DESC: Function to Unpack SztUlnkNASTport structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztUlnkNASTport
(
SztUlnkNASTport *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztUlnkNASTport(param, ptr, mBuf)
SztUlnkNASTport *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztUlnkNASTport) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_UlnkNASTport_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztUlnkNASTport */



/*
* FUN : cmUnpkSzt_ValueNASNonDlvryInd_IEsCls
*  DESC: Function to Unpack Szt_ValueNASNonDlvryInd_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueNASNonDlvryInd_IEsCls
(
Szt_ValueNASNonDlvryInd_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueNASNonDlvryInd_IEsCls(param, val, ptr, mBuf)
Szt_ValueNASNonDlvryInd_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueNASNonDlvryInd_IEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_NAS_PDU:
			SZUCHKUNPKPTR(cmUnpkSztNAS_PDU, &param->u.sztNAS_PDU, ptr, mBuf); 
			break;
		case Sztid_Cause:
			CMCHKUNPKPTR(cmUnpkSztCause, &param->u.sztCause, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueNASNonDlvryInd_IEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_NASNonDlvryInd_IEs
*  DESC: Function to Unpack SztProtIE_Field_NASNonDlvryInd_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_NASNonDlvryInd_IEs
(
SztProtIE_Field_NASNonDlvryInd_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_NASNonDlvryInd_IEs(param, ptr, mBuf)
SztProtIE_Field_NASNonDlvryInd_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_NASNonDlvryInd_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueNASNonDlvryInd_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_NASNonDlvryInd_IEs */



/*
* FUN : cmUnpkSztProtIE_Cont_NASNonDlvryInd_IEs
*  DESC: Function to Unpack SztProtIE_Cont_NASNonDlvryInd_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_NASNonDlvryInd_IEs
(
SztProtIE_Cont_NASNonDlvryInd_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_NASNonDlvryInd_IEs(param, ptr, mBuf)
SztProtIE_Cont_NASNonDlvryInd_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_NASNonDlvryInd_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_NASNonDlvryInd_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_NASNonDlvryInd_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_NASNonDlvryInd_IEs */



/*
* FUN : cmUnpkSztNASNonDlvryInd
*  DESC: Function to Unpack SztNASNonDlvryInd structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztNASNonDlvryInd
(
SztNASNonDlvryInd *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztNASNonDlvryInd(param, ptr, mBuf)
SztNASNonDlvryInd *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztNASNonDlvryInd) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_NASNonDlvryInd_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztNASNonDlvryInd */

#define cmUnpkSztResetAll cmUnpkTknU32



/*
* FUN : cmUnpkSzt_ValueUE_assocLogS1_ConItemResCls
*  DESC: Function to Unpack Szt_ValueUE_assocLogS1_ConItemResCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueUE_assocLogS1_ConItemResCls
(
Szt_ValueUE_assocLogS1_ConItemResCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueUE_assocLogS1_ConItemResCls(param, val, ptr, mBuf)
Szt_ValueUE_assocLogS1_ConItemResCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueUE_assocLogS1_ConItemResCls) 
	
	switch (val)
	{
		case Sztid_UE_assocLogS1_ConItem:
			CMCHKUNPKPTR(cmUnpkSztUE_assocLogS1_ConItem, &param->u.sztUE_assocLogS1_ConItem, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueUE_assocLogS1_ConItemResCls */



/*
* FUN : cmUnpkSztProtIE_Field_UE_assocLogS1_ConItemRes
*  DESC: Function to Unpack SztProtIE_Field_UE_assocLogS1_ConItemRes structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_UE_assocLogS1_ConItemRes
(
SztProtIE_Field_UE_assocLogS1_ConItemRes *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_UE_assocLogS1_ConItemRes(param, ptr, mBuf)
SztProtIE_Field_UE_assocLogS1_ConItemRes *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_UE_assocLogS1_ConItemRes) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueUE_assocLogS1_ConItemResCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_UE_assocLogS1_ConItemRes */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmUnpkSztProtIE_SingleCont_UE_assocLogS1_ConItemRes cmUnpkSztProtIE_Field_UE_assocLogS1_ConItemRes


/*
* FUN : cmUnpkSztUE_assocLogS1_ConLstRes
*  DESC: Function to Unpack SztUE_assocLogS1_ConLstRes structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztUE_assocLogS1_ConLstRes
(
SztUE_assocLogS1_ConLstRes *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztUE_assocLogS1_ConLstRes(param, ptr, mBuf)
SztUE_assocLogS1_ConLstRes *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztUE_assocLogS1_ConLstRes) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_SingleCont_UE_assocLogS1_ConItemRes)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_SingleCont_UE_assocLogS1_ConItemRes, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztUE_assocLogS1_ConLstRes */



/*
* FUN : cmUnpkSztResetTyp
*  DESC: Function to Unpack SztResetTyp structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztResetTyp
(
SztResetTyp *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztResetTyp(param, ptr, mBuf)
SztResetTyp *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztResetTyp) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case RESETTYP_S1_INTF :
				CMCHKUNPK(cmUnpkSztResetAll, &param->val.s1_Intf, mBuf); 
				break;
			case RESETTYP_PARTOFS1_INTF :
				CMCHKUNPKPTR(cmUnpkSztUE_assocLogS1_ConLstRes, &param->val.partOfS1_Intf, ptr, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztResetTyp */



/*
* FUN : cmUnpkSzt_ValueResetIEsCls
*  DESC: Function to Unpack Szt_ValueResetIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueResetIEsCls
(
Szt_ValueResetIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueResetIEsCls(param, val, ptr, mBuf)
Szt_ValueResetIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueResetIEsCls) 
	
	switch (val)
	{
		case Sztid_Cause:
			CMCHKUNPKPTR(cmUnpkSztCause, &param->u.sztCause, ptr, mBuf);
			break;
		case Sztid_ResetTyp:
			CMCHKUNPKPTR(cmUnpkSztResetTyp, &param->u.sztResetTyp, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueResetIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_ResetIEs
*  DESC: Function to Unpack SztProtIE_Field_ResetIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_ResetIEs
(
SztProtIE_Field_ResetIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_ResetIEs(param, ptr, mBuf)
SztProtIE_Field_ResetIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_ResetIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueResetIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_ResetIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_ResetIEs
*  DESC: Function to Unpack SztProtIE_Cont_ResetIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_ResetIEs
(
SztProtIE_Cont_ResetIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_ResetIEs(param, ptr, mBuf)
SztProtIE_Cont_ResetIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_ResetIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_ResetIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_ResetIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_ResetIEs */



/*
* FUN : cmUnpkSztReset
*  DESC: Function to Unpack SztReset structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztReset
(
SztReset *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztReset(param, ptr, mBuf)
SztReset *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztReset) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_ResetIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztReset */



/*
* FUN : cmUnpkSzt_ValueUE_assocLogS1_ConItemResAckCls
*  DESC: Function to Unpack Szt_ValueUE_assocLogS1_ConItemResAckCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueUE_assocLogS1_ConItemResAckCls
(
Szt_ValueUE_assocLogS1_ConItemResAckCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueUE_assocLogS1_ConItemResAckCls(param, val, ptr, mBuf)
Szt_ValueUE_assocLogS1_ConItemResAckCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueUE_assocLogS1_ConItemResAckCls) 
	
	switch (val)
	{
		case Sztid_UE_assocLogS1_ConItem:
			CMCHKUNPKPTR(cmUnpkSztUE_assocLogS1_ConItem, &param->u.sztUE_assocLogS1_ConItem, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueUE_assocLogS1_ConItemResAckCls */



/*
* FUN : cmUnpkSztProtIE_Field_UE_assocLogS1_ConItemResAck
*  DESC: Function to Unpack SztProtIE_Field_UE_assocLogS1_ConItemResAck structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_UE_assocLogS1_ConItemResAck
(
SztProtIE_Field_UE_assocLogS1_ConItemResAck *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_UE_assocLogS1_ConItemResAck(param, ptr, mBuf)
SztProtIE_Field_UE_assocLogS1_ConItemResAck *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_UE_assocLogS1_ConItemResAck) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueUE_assocLogS1_ConItemResAckCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_UE_assocLogS1_ConItemResAck */

/* Element ------------- ProtocolIE-SingleContainer ------------ */
#define cmUnpkSztProtIE_SingleCont_UE_assocLogS1_ConItemResAck cmUnpkSztProtIE_Field_UE_assocLogS1_ConItemResAck


/*
* FUN : cmUnpkSztUE_assocLogS1_ConLstResAck
*  DESC: Function to Unpack SztUE_assocLogS1_ConLstResAck structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztUE_assocLogS1_ConLstResAck
(
SztUE_assocLogS1_ConLstResAck *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztUE_assocLogS1_ConLstResAck(param, ptr, mBuf)
SztUE_assocLogS1_ConLstResAck *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztUE_assocLogS1_ConLstResAck) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_SingleCont_UE_assocLogS1_ConItemResAck)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_SingleCont_UE_assocLogS1_ConItemResAck, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztUE_assocLogS1_ConLstResAck */



/*
* FUN : cmUnpkSzt_ValueResetAckgIEsCls
*  DESC: Function to Unpack Szt_ValueResetAckgIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueResetAckgIEsCls
(
Szt_ValueResetAckgIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueResetAckgIEsCls(param, val, ptr, mBuf)
Szt_ValueResetAckgIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueResetAckgIEsCls) 
	
	switch (val)
	{
		case Sztid_UE_assocLogS1_ConLstResAck:
			CMCHKUNPKPTR(cmUnpkSztUE_assocLogS1_ConLstResAck, &param->u.sztUE_assocLogS1_ConLstResAck, ptr, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkSztCriticalityDiag, &param->u.sztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueResetAckgIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_ResetAckgIEs
*  DESC: Function to Unpack SztProtIE_Field_ResetAckgIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_ResetAckgIEs
(
SztProtIE_Field_ResetAckgIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_ResetAckgIEs(param, ptr, mBuf)
SztProtIE_Field_ResetAckgIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_ResetAckgIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueResetAckgIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_ResetAckgIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_ResetAckgIEs
*  DESC: Function to Unpack SztProtIE_Cont_ResetAckgIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_ResetAckgIEs
(
SztProtIE_Cont_ResetAckgIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_ResetAckgIEs(param, ptr, mBuf)
SztProtIE_Cont_ResetAckgIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_ResetAckgIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_ResetAckgIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_ResetAckgIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_ResetAckgIEs */



/*
* FUN : cmUnpkSztResetAckg
*  DESC: Function to Unpack SztResetAckg structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztResetAckg
(
SztResetAckg *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztResetAckg(param, ptr, mBuf)
SztResetAckg *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztResetAckg) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_ResetAckgIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztResetAckg */



/*
* FUN : cmUnpkSzt_ValueErrIndIEsCls
*  DESC: Function to Unpack Szt_ValueErrIndIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueErrIndIEsCls
(
Szt_ValueErrIndIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueErrIndIEsCls(param, val, ptr, mBuf)
Szt_ValueErrIndIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueErrIndIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_Cause:
			CMCHKUNPKPTR(cmUnpkSztCause, &param->u.sztCause, ptr, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkSztCriticalityDiag, &param->u.sztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueErrIndIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_ErrIndIEs
*  DESC: Function to Unpack SztProtIE_Field_ErrIndIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_ErrIndIEs
(
SztProtIE_Field_ErrIndIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_ErrIndIEs(param, ptr, mBuf)
SztProtIE_Field_ErrIndIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_ErrIndIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueErrIndIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_ErrIndIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_ErrIndIEs
*  DESC: Function to Unpack SztProtIE_Cont_ErrIndIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_ErrIndIEs
(
SztProtIE_Cont_ErrIndIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_ErrIndIEs(param, ptr, mBuf)
SztProtIE_Cont_ErrIndIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_ErrIndIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_ErrIndIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_ErrIndIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_ErrIndIEs */



/*
* FUN : cmUnpkSztErrInd
*  DESC: Function to Unpack SztErrInd structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztErrInd
(
SztErrInd *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztErrInd(param, ptr, mBuf)
SztErrInd *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztErrInd) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_ErrIndIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztErrInd */



/*
* FUN : cmUnpkSzt_ValueS1SetupRqstIEsCls
*  DESC: Function to Unpack Szt_ValueS1SetupRqstIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueS1SetupRqstIEsCls
(
Szt_ValueS1SetupRqstIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueS1SetupRqstIEsCls(param, val, ptr, mBuf)
Szt_ValueS1SetupRqstIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueS1SetupRqstIEsCls) 
	
	switch (val)
	{
		case Sztid_Global_ENB_ID:
			CMCHKUNPKPTR(cmUnpkSztGlobal_ENB_ID, &param->u.sztGlobal_ENB_ID, ptr, mBuf);
			break;
		case Sztid_eNBname:
			SZUCHKUNPKPTR(cmUnpkSztENBname, &param->u.sztENBname, ptr, mBuf); 
			break;
		case Sztid_SuppTAs:
			CMCHKUNPKPTR(cmUnpkSztSuppTAs, &param->u.sztSuppTAs, ptr, mBuf);
			break;
		case Sztid_DefaultPagDRX:
			CMCHKUNPK(cmUnpkSztPagDRX, &param->u.sztPagDRX, mBuf); 
			break;
		case Sztid_CSG_IdLst:
			CMCHKUNPKPTR(cmUnpkSztCSG_IdLst, &param->u.sztCSG_IdLst, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueS1SetupRqstIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_S1SetupRqstIEs
*  DESC: Function to Unpack SztProtIE_Field_S1SetupRqstIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_S1SetupRqstIEs
(
SztProtIE_Field_S1SetupRqstIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_S1SetupRqstIEs(param, ptr, mBuf)
SztProtIE_Field_S1SetupRqstIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_S1SetupRqstIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueS1SetupRqstIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_S1SetupRqstIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_S1SetupRqstIEs
*  DESC: Function to Unpack SztProtIE_Cont_S1SetupRqstIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_S1SetupRqstIEs
(
SztProtIE_Cont_S1SetupRqstIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_S1SetupRqstIEs(param, ptr, mBuf)
SztProtIE_Cont_S1SetupRqstIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_S1SetupRqstIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_S1SetupRqstIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_S1SetupRqstIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_S1SetupRqstIEs */



/*
* FUN : cmUnpkSztS1SetupRqst
*  DESC: Function to Unpack SztS1SetupRqst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztS1SetupRqst
(
SztS1SetupRqst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztS1SetupRqst(param, ptr, mBuf)
SztS1SetupRqst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztS1SetupRqst) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_S1SetupRqstIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztS1SetupRqst */



/*
* FUN : cmUnpkSzt_ValueS1SetupRespIEsCls
*  DESC: Function to Unpack Szt_ValueS1SetupRespIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueS1SetupRespIEsCls
(
Szt_ValueS1SetupRespIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueS1SetupRespIEsCls(param, val, ptr, mBuf)
Szt_ValueS1SetupRespIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueS1SetupRespIEsCls) 
	
	switch (val)
	{
		case Sztid_MMEname:
			SZUCHKUNPKPTR(cmUnpkSztMMEname, &param->u.sztMMEname, ptr, mBuf); 
			break;
		case Sztid_SrvdGUMMEIs:
			CMCHKUNPKPTR(cmUnpkSztSrvdGUMMEIs, &param->u.sztSrvdGUMMEIs, ptr, mBuf);
			break;
		case Sztid_RelativeMMECapacity:
			CMCHKUNPK(cmUnpkSztRelativeMMECapacity, &param->u.sztRelativeMMECapacity, mBuf); 
			break;
		case Sztid_MMERelaySupportIndicator:
			CMCHKUNPK(cmUnpkSztMMERelaySupportIndicator, &param->u.sztMMERelaySupportIndicator, mBuf); 
			break;
		case Sztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkSztCriticalityDiag, &param->u.sztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueS1SetupRespIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_S1SetupRespIEs
*  DESC: Function to Unpack SztProtIE_Field_S1SetupRespIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_S1SetupRespIEs
(
SztProtIE_Field_S1SetupRespIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_S1SetupRespIEs(param, ptr, mBuf)
SztProtIE_Field_S1SetupRespIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_S1SetupRespIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueS1SetupRespIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_S1SetupRespIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_S1SetupRespIEs
*  DESC: Function to Unpack SztProtIE_Cont_S1SetupRespIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_S1SetupRespIEs
(
SztProtIE_Cont_S1SetupRespIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_S1SetupRespIEs(param, ptr, mBuf)
SztProtIE_Cont_S1SetupRespIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_S1SetupRespIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_S1SetupRespIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_S1SetupRespIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_S1SetupRespIEs */



/*
* FUN : cmUnpkSztS1SetupResp
*  DESC: Function to Unpack SztS1SetupResp structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztS1SetupResp
(
SztS1SetupResp *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztS1SetupResp(param, ptr, mBuf)
SztS1SetupResp *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztS1SetupResp) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_S1SetupRespIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztS1SetupResp */



/*
* FUN : cmUnpkSzt_ValueS1SetupFailIEsCls
*  DESC: Function to Unpack Szt_ValueS1SetupFailIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueS1SetupFailIEsCls
(
Szt_ValueS1SetupFailIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueS1SetupFailIEsCls(param, val, ptr, mBuf)
Szt_ValueS1SetupFailIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueS1SetupFailIEsCls) 
	
	switch (val)
	{
		case Sztid_Cause:
			CMCHKUNPKPTR(cmUnpkSztCause, &param->u.sztCause, ptr, mBuf);
			break;
		case Sztid_TimeToWait:
			CMCHKUNPK(cmUnpkSztTimeToWait, &param->u.sztTimeToWait, mBuf); 
			break;
		case Sztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkSztCriticalityDiag, &param->u.sztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueS1SetupFailIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_S1SetupFailIEs
*  DESC: Function to Unpack SztProtIE_Field_S1SetupFailIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_S1SetupFailIEs
(
SztProtIE_Field_S1SetupFailIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_S1SetupFailIEs(param, ptr, mBuf)
SztProtIE_Field_S1SetupFailIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_S1SetupFailIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueS1SetupFailIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_S1SetupFailIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_S1SetupFailIEs
*  DESC: Function to Unpack SztProtIE_Cont_S1SetupFailIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_S1SetupFailIEs
(
SztProtIE_Cont_S1SetupFailIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_S1SetupFailIEs(param, ptr, mBuf)
SztProtIE_Cont_S1SetupFailIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_S1SetupFailIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_S1SetupFailIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_S1SetupFailIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_S1SetupFailIEs */



/*
* FUN : cmUnpkSztS1SetupFail
*  DESC: Function to Unpack SztS1SetupFail structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztS1SetupFail
(
SztS1SetupFail *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztS1SetupFail(param, ptr, mBuf)
SztS1SetupFail *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztS1SetupFail) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_S1SetupFailIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztS1SetupFail */



/*
* FUN : cmUnpkSzt_ValueENBConfigUpdIEsCls
*  DESC: Function to Unpack Szt_ValueENBConfigUpdIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueENBConfigUpdIEsCls
(
Szt_ValueENBConfigUpdIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueENBConfigUpdIEsCls(param, val, ptr, mBuf)
Szt_ValueENBConfigUpdIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueENBConfigUpdIEsCls) 
	
	switch (val)
	{
		case Sztid_eNBname:
			SZUCHKUNPKPTR(cmUnpkSztENBname, &param->u.sztENBname, ptr, mBuf); 
			break;
		case Sztid_SuppTAs:
			CMCHKUNPKPTR(cmUnpkSztSuppTAs, &param->u.sztSuppTAs, ptr, mBuf);
			break;
		case Sztid_CSG_IdLst:
			CMCHKUNPKPTR(cmUnpkSztCSG_IdLst, &param->u.sztCSG_IdLst, ptr, mBuf);
			break;
		case Sztid_DefaultPagDRX:
			CMCHKUNPK(cmUnpkSztPagDRX, &param->u.sztPagDRX, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueENBConfigUpdIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_ENBConfigUpdIEs
*  DESC: Function to Unpack SztProtIE_Field_ENBConfigUpdIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_ENBConfigUpdIEs
(
SztProtIE_Field_ENBConfigUpdIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_ENBConfigUpdIEs(param, ptr, mBuf)
SztProtIE_Field_ENBConfigUpdIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_ENBConfigUpdIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueENBConfigUpdIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_ENBConfigUpdIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_ENBConfigUpdIEs
*  DESC: Function to Unpack SztProtIE_Cont_ENBConfigUpdIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_ENBConfigUpdIEs
(
SztProtIE_Cont_ENBConfigUpdIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_ENBConfigUpdIEs(param, ptr, mBuf)
SztProtIE_Cont_ENBConfigUpdIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_ENBConfigUpdIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_ENBConfigUpdIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_ENBConfigUpdIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_ENBConfigUpdIEs */



/*
* FUN : cmUnpkSztENBConfigUpd
*  DESC: Function to Unpack SztENBConfigUpd structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztENBConfigUpd
(
SztENBConfigUpd *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztENBConfigUpd(param, ptr, mBuf)
SztENBConfigUpd *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztENBConfigUpd) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_ENBConfigUpdIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztENBConfigUpd */



/*
* FUN : cmUnpkSzt_ValueENBConfigUpdAckgIEsCls
*  DESC: Function to Unpack Szt_ValueENBConfigUpdAckgIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueENBConfigUpdAckgIEsCls
(
Szt_ValueENBConfigUpdAckgIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueENBConfigUpdAckgIEsCls(param, val, ptr, mBuf)
Szt_ValueENBConfigUpdAckgIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueENBConfigUpdAckgIEsCls) 
	
	switch (val)
	{
		case Sztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkSztCriticalityDiag, &param->u.sztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueENBConfigUpdAckgIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_ENBConfigUpdAckgIEs
*  DESC: Function to Unpack SztProtIE_Field_ENBConfigUpdAckgIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_ENBConfigUpdAckgIEs
(
SztProtIE_Field_ENBConfigUpdAckgIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_ENBConfigUpdAckgIEs(param, ptr, mBuf)
SztProtIE_Field_ENBConfigUpdAckgIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_ENBConfigUpdAckgIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueENBConfigUpdAckgIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_ENBConfigUpdAckgIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_ENBConfigUpdAckgIEs
*  DESC: Function to Unpack SztProtIE_Cont_ENBConfigUpdAckgIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_ENBConfigUpdAckgIEs
(
SztProtIE_Cont_ENBConfigUpdAckgIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_ENBConfigUpdAckgIEs(param, ptr, mBuf)
SztProtIE_Cont_ENBConfigUpdAckgIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_ENBConfigUpdAckgIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_ENBConfigUpdAckgIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_ENBConfigUpdAckgIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_ENBConfigUpdAckgIEs */



/*
* FUN : cmUnpkSztENBConfigUpdAckg
*  DESC: Function to Unpack SztENBConfigUpdAckg structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztENBConfigUpdAckg
(
SztENBConfigUpdAckg *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztENBConfigUpdAckg(param, ptr, mBuf)
SztENBConfigUpdAckg *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztENBConfigUpdAckg) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_ENBConfigUpdAckgIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztENBConfigUpdAckg */



/*
* FUN : cmUnpkSzt_ValueENBConfigUpdFailIEsCls
*  DESC: Function to Unpack Szt_ValueENBConfigUpdFailIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueENBConfigUpdFailIEsCls
(
Szt_ValueENBConfigUpdFailIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueENBConfigUpdFailIEsCls(param, val, ptr, mBuf)
Szt_ValueENBConfigUpdFailIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueENBConfigUpdFailIEsCls) 
	
	switch (val)
	{
		case Sztid_Cause:
			CMCHKUNPKPTR(cmUnpkSztCause, &param->u.sztCause, ptr, mBuf);
			break;
		case Sztid_TimeToWait:
			CMCHKUNPK(cmUnpkSztTimeToWait, &param->u.sztTimeToWait, mBuf); 
			break;
		case Sztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkSztCriticalityDiag, &param->u.sztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueENBConfigUpdFailIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_ENBConfigUpdFailIEs
*  DESC: Function to Unpack SztProtIE_Field_ENBConfigUpdFailIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_ENBConfigUpdFailIEs
(
SztProtIE_Field_ENBConfigUpdFailIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_ENBConfigUpdFailIEs(param, ptr, mBuf)
SztProtIE_Field_ENBConfigUpdFailIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_ENBConfigUpdFailIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueENBConfigUpdFailIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_ENBConfigUpdFailIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_ENBConfigUpdFailIEs
*  DESC: Function to Unpack SztProtIE_Cont_ENBConfigUpdFailIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_ENBConfigUpdFailIEs
(
SztProtIE_Cont_ENBConfigUpdFailIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_ENBConfigUpdFailIEs(param, ptr, mBuf)
SztProtIE_Cont_ENBConfigUpdFailIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_ENBConfigUpdFailIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_ENBConfigUpdFailIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_ENBConfigUpdFailIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_ENBConfigUpdFailIEs */



/*
* FUN : cmUnpkSztENBConfigUpdFail
*  DESC: Function to Unpack SztENBConfigUpdFail structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztENBConfigUpdFail
(
SztENBConfigUpdFail *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztENBConfigUpdFail(param, ptr, mBuf)
SztENBConfigUpdFail *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztENBConfigUpdFail) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_ENBConfigUpdFailIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztENBConfigUpdFail */



/*
* FUN : cmUnpkSzt_ValueMMEConfigUpdIEsCls
*  DESC: Function to Unpack Szt_ValueMMEConfigUpdIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueMMEConfigUpdIEsCls
(
Szt_ValueMMEConfigUpdIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueMMEConfigUpdIEsCls(param, val, ptr, mBuf)
Szt_ValueMMEConfigUpdIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueMMEConfigUpdIEsCls) 
	
	switch (val)
	{
		case Sztid_MMEname:
			SZUCHKUNPKPTR(cmUnpkSztMMEname, &param->u.sztMMEname, ptr, mBuf); 
			break;
		case Sztid_SrvdGUMMEIs:
			CMCHKUNPKPTR(cmUnpkSztSrvdGUMMEIs, &param->u.sztSrvdGUMMEIs, ptr, mBuf);
			break;
		case Sztid_RelativeMMECapacity:
			CMCHKUNPK(cmUnpkSztRelativeMMECapacity, &param->u.sztRelativeMMECapacity, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueMMEConfigUpdIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_MMEConfigUpdIEs
*  DESC: Function to Unpack SztProtIE_Field_MMEConfigUpdIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_MMEConfigUpdIEs
(
SztProtIE_Field_MMEConfigUpdIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_MMEConfigUpdIEs(param, ptr, mBuf)
SztProtIE_Field_MMEConfigUpdIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_MMEConfigUpdIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueMMEConfigUpdIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_MMEConfigUpdIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_MMEConfigUpdIEs
*  DESC: Function to Unpack SztProtIE_Cont_MMEConfigUpdIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_MMEConfigUpdIEs
(
SztProtIE_Cont_MMEConfigUpdIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_MMEConfigUpdIEs(param, ptr, mBuf)
SztProtIE_Cont_MMEConfigUpdIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_MMEConfigUpdIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_MMEConfigUpdIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_MMEConfigUpdIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_MMEConfigUpdIEs */



/*
* FUN : cmUnpkSztMMEConfigUpd
*  DESC: Function to Unpack SztMMEConfigUpd structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztMMEConfigUpd
(
SztMMEConfigUpd *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztMMEConfigUpd(param, ptr, mBuf)
SztMMEConfigUpd *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztMMEConfigUpd) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_MMEConfigUpdIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztMMEConfigUpd */



/*
* FUN : cmUnpkSzt_ValueMMEConfigUpdAckgIEsCls
*  DESC: Function to Unpack Szt_ValueMMEConfigUpdAckgIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueMMEConfigUpdAckgIEsCls
(
Szt_ValueMMEConfigUpdAckgIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueMMEConfigUpdAckgIEsCls(param, val, ptr, mBuf)
Szt_ValueMMEConfigUpdAckgIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueMMEConfigUpdAckgIEsCls) 
	
	switch (val)
	{
		case Sztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkSztCriticalityDiag, &param->u.sztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueMMEConfigUpdAckgIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_MMEConfigUpdAckgIEs
*  DESC: Function to Unpack SztProtIE_Field_MMEConfigUpdAckgIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_MMEConfigUpdAckgIEs
(
SztProtIE_Field_MMEConfigUpdAckgIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_MMEConfigUpdAckgIEs(param, ptr, mBuf)
SztProtIE_Field_MMEConfigUpdAckgIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_MMEConfigUpdAckgIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueMMEConfigUpdAckgIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_MMEConfigUpdAckgIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_MMEConfigUpdAckgIEs
*  DESC: Function to Unpack SztProtIE_Cont_MMEConfigUpdAckgIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_MMEConfigUpdAckgIEs
(
SztProtIE_Cont_MMEConfigUpdAckgIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_MMEConfigUpdAckgIEs(param, ptr, mBuf)
SztProtIE_Cont_MMEConfigUpdAckgIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_MMEConfigUpdAckgIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_MMEConfigUpdAckgIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_MMEConfigUpdAckgIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_MMEConfigUpdAckgIEs */



/*
* FUN : cmUnpkSztMMEConfigUpdAckg
*  DESC: Function to Unpack SztMMEConfigUpdAckg structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztMMEConfigUpdAckg
(
SztMMEConfigUpdAckg *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztMMEConfigUpdAckg(param, ptr, mBuf)
SztMMEConfigUpdAckg *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztMMEConfigUpdAckg) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_MMEConfigUpdAckgIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztMMEConfigUpdAckg */



/*
* FUN : cmUnpkSzt_ValueMMEConfigUpdFailIEsCls
*  DESC: Function to Unpack Szt_ValueMMEConfigUpdFailIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueMMEConfigUpdFailIEsCls
(
Szt_ValueMMEConfigUpdFailIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueMMEConfigUpdFailIEsCls(param, val, ptr, mBuf)
Szt_ValueMMEConfigUpdFailIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueMMEConfigUpdFailIEsCls) 
	
	switch (val)
	{
		case Sztid_Cause:
			CMCHKUNPKPTR(cmUnpkSztCause, &param->u.sztCause, ptr, mBuf);
			break;
		case Sztid_TimeToWait:
			CMCHKUNPK(cmUnpkSztTimeToWait, &param->u.sztTimeToWait, mBuf); 
			break;
		case Sztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkSztCriticalityDiag, &param->u.sztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueMMEConfigUpdFailIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_MMEConfigUpdFailIEs
*  DESC: Function to Unpack SztProtIE_Field_MMEConfigUpdFailIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_MMEConfigUpdFailIEs
(
SztProtIE_Field_MMEConfigUpdFailIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_MMEConfigUpdFailIEs(param, ptr, mBuf)
SztProtIE_Field_MMEConfigUpdFailIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_MMEConfigUpdFailIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueMMEConfigUpdFailIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_MMEConfigUpdFailIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_MMEConfigUpdFailIEs
*  DESC: Function to Unpack SztProtIE_Cont_MMEConfigUpdFailIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_MMEConfigUpdFailIEs
(
SztProtIE_Cont_MMEConfigUpdFailIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_MMEConfigUpdFailIEs(param, ptr, mBuf)
SztProtIE_Cont_MMEConfigUpdFailIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_MMEConfigUpdFailIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_MMEConfigUpdFailIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_MMEConfigUpdFailIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_MMEConfigUpdFailIEs */



/*
* FUN : cmUnpkSztMMEConfigUpdFail
*  DESC: Function to Unpack SztMMEConfigUpdFail structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztMMEConfigUpdFail
(
SztMMEConfigUpdFail *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztMMEConfigUpdFail(param, ptr, mBuf)
SztMMEConfigUpdFail *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztMMEConfigUpdFail) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_MMEConfigUpdFailIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztMMEConfigUpdFail */



/*
* FUN : cmUnpkSzt_ValueDlnkS1cdma2000tunnelingIEsCls
*  DESC: Function to Unpack Szt_ValueDlnkS1cdma2000tunnelingIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueDlnkS1cdma2000tunnelingIEsCls
(
Szt_ValueDlnkS1cdma2000tunnelingIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueDlnkS1cdma2000tunnelingIEsCls(param, val, ptr, mBuf)
Szt_ValueDlnkS1cdma2000tunnelingIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueDlnkS1cdma2000tunnelingIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_E_RABSubjtoDataFwdingLst:
			CMCHKUNPKPTR(cmUnpkSztE_RABSubjtoDataFwdingLst, &param->u.sztE_RABSubjtoDataFwdingLst, ptr, mBuf);
			break;
		case Sztid_cdma2000HOStatus:
			CMCHKUNPK(cmUnpkSztCdma2000HOStatus, &param->u.sztCdma2000HOStatus, mBuf); 
			break;
		case Sztid_cdma2000RATTyp:
			CMCHKUNPK(cmUnpkSztCdma2000RATTyp, &param->u.sztCdma2000RATTyp, mBuf); 
			break;
		case Sztid_cdma2000PDU:
			SZUCHKUNPKPTR(cmUnpkSztCdma2000PDU, &param->u.sztCdma2000PDU, ptr, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueDlnkS1cdma2000tunnelingIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_DlnkS1cdma2000tunnelingIEs
*  DESC: Function to Unpack SztProtIE_Field_DlnkS1cdma2000tunnelingIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_DlnkS1cdma2000tunnelingIEs
(
SztProtIE_Field_DlnkS1cdma2000tunnelingIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_DlnkS1cdma2000tunnelingIEs(param, ptr, mBuf)
SztProtIE_Field_DlnkS1cdma2000tunnelingIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_DlnkS1cdma2000tunnelingIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueDlnkS1cdma2000tunnelingIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_DlnkS1cdma2000tunnelingIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_DlnkS1cdma2000tunnelingIEs
*  DESC: Function to Unpack SztProtIE_Cont_DlnkS1cdma2000tunnelingIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_DlnkS1cdma2000tunnelingIEs
(
SztProtIE_Cont_DlnkS1cdma2000tunnelingIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_DlnkS1cdma2000tunnelingIEs(param, ptr, mBuf)
SztProtIE_Cont_DlnkS1cdma2000tunnelingIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_DlnkS1cdma2000tunnelingIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_DlnkS1cdma2000tunnelingIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_DlnkS1cdma2000tunnelingIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_DlnkS1cdma2000tunnelingIEs */



/*
* FUN : cmUnpkSztDlnkS1cdma2000tunneling
*  DESC: Function to Unpack SztDlnkS1cdma2000tunneling structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztDlnkS1cdma2000tunneling
(
SztDlnkS1cdma2000tunneling *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztDlnkS1cdma2000tunneling(param, ptr, mBuf)
SztDlnkS1cdma2000tunneling *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztDlnkS1cdma2000tunneling) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_DlnkS1cdma2000tunnelingIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztDlnkS1cdma2000tunneling */



/*
* FUN : cmUnpkSzt_ValueUlnkS1cdma2000tunnelingIEsCls
*  DESC: Function to Unpack Szt_ValueUlnkS1cdma2000tunnelingIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueUlnkS1cdma2000tunnelingIEsCls
(
Szt_ValueUlnkS1cdma2000tunnelingIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueUlnkS1cdma2000tunnelingIEsCls(param, val, ptr, mBuf)
Szt_ValueUlnkS1cdma2000tunnelingIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueUlnkS1cdma2000tunnelingIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_cdma2000RATTyp:
			CMCHKUNPK(cmUnpkSztCdma2000RATTyp, &param->u.sztCdma2000RATTyp, mBuf); 
			break;
		case Sztid_cdma2000SectorID:
			SZUCHKUNPKPTR(cmUnpkSztCdma2000SectorID, &param->u.sztCdma2000SectorID, ptr, mBuf); 
			break;
		case Sztid_cdma2000HOReqdInd:
			CMCHKUNPK(cmUnpkSztCdma2000HOReqdInd, &param->u.sztCdma2000HOReqdInd, mBuf); 
			break;
		case Sztid_cdma2000OneXSRVCCInfo:
			CMCHKUNPKPTR(cmUnpkSztCdma2000OneXSRVCCInfo, &param->u.sztCdma2000OneXSRVCCInfo, ptr, mBuf);
			break;
		case Sztid_cdma2000OneXRAND:
			SZUCHKUNPKPTR(cmUnpkSztCdma2000OneXRAND, &param->u.sztCdma2000OneXRAND, ptr, mBuf); 
			break;
		case Sztid_cdma2000PDU:
			SZUCHKUNPKPTR(cmUnpkSztCdma2000PDU, &param->u.sztCdma2000PDU, ptr, mBuf); 
			break;
		case Sztid_EUTRANRoundTripDelayEstimationInfo:
			CMCHKUNPK(cmUnpkSztEUTRANRoundTripDelayEstimationInfo, &param->u.sztEUTRANRoundTripDelayEstimationInfo, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueUlnkS1cdma2000tunnelingIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_UlnkS1cdma2000tunnelingIEs
*  DESC: Function to Unpack SztProtIE_Field_UlnkS1cdma2000tunnelingIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_UlnkS1cdma2000tunnelingIEs
(
SztProtIE_Field_UlnkS1cdma2000tunnelingIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_UlnkS1cdma2000tunnelingIEs(param, ptr, mBuf)
SztProtIE_Field_UlnkS1cdma2000tunnelingIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_UlnkS1cdma2000tunnelingIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueUlnkS1cdma2000tunnelingIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_UlnkS1cdma2000tunnelingIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_UlnkS1cdma2000tunnelingIEs
*  DESC: Function to Unpack SztProtIE_Cont_UlnkS1cdma2000tunnelingIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_UlnkS1cdma2000tunnelingIEs
(
SztProtIE_Cont_UlnkS1cdma2000tunnelingIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_UlnkS1cdma2000tunnelingIEs(param, ptr, mBuf)
SztProtIE_Cont_UlnkS1cdma2000tunnelingIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_UlnkS1cdma2000tunnelingIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_UlnkS1cdma2000tunnelingIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_UlnkS1cdma2000tunnelingIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_UlnkS1cdma2000tunnelingIEs */



/*
* FUN : cmUnpkSztUlnkS1cdma2000tunneling
*  DESC: Function to Unpack SztUlnkS1cdma2000tunneling structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztUlnkS1cdma2000tunneling
(
SztUlnkS1cdma2000tunneling *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztUlnkS1cdma2000tunneling(param, ptr, mBuf)
SztUlnkS1cdma2000tunneling *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztUlnkS1cdma2000tunneling) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_UlnkS1cdma2000tunnelingIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztUlnkS1cdma2000tunneling */



/*
* FUN : cmUnpkSzt_ValueUECapbltyInfoIndIEsCls
*  DESC: Function to Unpack Szt_ValueUECapbltyInfoIndIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueUECapbltyInfoIndIEsCls
(
Szt_ValueUECapbltyInfoIndIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueUECapbltyInfoIndIEsCls(param, val, ptr, mBuf)
Szt_ValueUECapbltyInfoIndIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueUECapbltyInfoIndIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_UERadioCapblty:
			SZUCHKUNPKPTR(cmUnpkSztUERadioCapblty, &param->u.sztUERadioCapblty, ptr, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueUECapbltyInfoIndIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_UECapbltyInfoIndIEs
*  DESC: Function to Unpack SztProtIE_Field_UECapbltyInfoIndIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_UECapbltyInfoIndIEs
(
SztProtIE_Field_UECapbltyInfoIndIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_UECapbltyInfoIndIEs(param, ptr, mBuf)
SztProtIE_Field_UECapbltyInfoIndIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_UECapbltyInfoIndIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueUECapbltyInfoIndIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_UECapbltyInfoIndIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_UECapbltyInfoIndIEs
*  DESC: Function to Unpack SztProtIE_Cont_UECapbltyInfoIndIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_UECapbltyInfoIndIEs
(
SztProtIE_Cont_UECapbltyInfoIndIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_UECapbltyInfoIndIEs(param, ptr, mBuf)
SztProtIE_Cont_UECapbltyInfoIndIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_UECapbltyInfoIndIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_UECapbltyInfoIndIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_UECapbltyInfoIndIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_UECapbltyInfoIndIEs */



/*
* FUN : cmUnpkSztUECapbltyInfoInd
*  DESC: Function to Unpack SztUECapbltyInfoInd structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztUECapbltyInfoInd
(
SztUECapbltyInfoInd *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztUECapbltyInfoInd(param, ptr, mBuf)
SztUECapbltyInfoInd *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztUECapbltyInfoInd) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_UECapbltyInfoIndIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztUECapbltyInfoInd */



/*
* FUN : cmUnpkSzt_ValueENBStatusTfrIEsCls
*  DESC: Function to Unpack Szt_ValueENBStatusTfrIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueENBStatusTfrIEsCls
(
Szt_ValueENBStatusTfrIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueENBStatusTfrIEsCls(param, val, ptr, mBuf)
Szt_ValueENBStatusTfrIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueENBStatusTfrIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_StatusTfr_TprntCont:
			CMCHKUNPKPTR(cmUnpkSztENB_StatusTfr_TprntCont, &param->u.sztENB_StatusTfr_TprntCont, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueENBStatusTfrIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_ENBStatusTfrIEs
*  DESC: Function to Unpack SztProtIE_Field_ENBStatusTfrIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_ENBStatusTfrIEs
(
SztProtIE_Field_ENBStatusTfrIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_ENBStatusTfrIEs(param, ptr, mBuf)
SztProtIE_Field_ENBStatusTfrIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_ENBStatusTfrIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueENBStatusTfrIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_ENBStatusTfrIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_ENBStatusTfrIEs
*  DESC: Function to Unpack SztProtIE_Cont_ENBStatusTfrIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_ENBStatusTfrIEs
(
SztProtIE_Cont_ENBStatusTfrIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_ENBStatusTfrIEs(param, ptr, mBuf)
SztProtIE_Cont_ENBStatusTfrIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_ENBStatusTfrIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_ENBStatusTfrIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_ENBStatusTfrIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_ENBStatusTfrIEs */



/*
* FUN : cmUnpkSztENBStatusTfr
*  DESC: Function to Unpack SztENBStatusTfr structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztENBStatusTfr
(
SztENBStatusTfr *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztENBStatusTfr(param, ptr, mBuf)
SztENBStatusTfr *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztENBStatusTfr) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_ENBStatusTfrIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztENBStatusTfr */



/*
* FUN : cmUnpkSzt_ValueMMEStatusTfrIEsCls
*  DESC: Function to Unpack Szt_ValueMMEStatusTfrIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueMMEStatusTfrIEsCls
(
Szt_ValueMMEStatusTfrIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueMMEStatusTfrIEsCls(param, val, ptr, mBuf)
Szt_ValueMMEStatusTfrIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueMMEStatusTfrIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_StatusTfr_TprntCont:
			CMCHKUNPKPTR(cmUnpkSztENB_StatusTfr_TprntCont, &param->u.sztENB_StatusTfr_TprntCont, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueMMEStatusTfrIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_MMEStatusTfrIEs
*  DESC: Function to Unpack SztProtIE_Field_MMEStatusTfrIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_MMEStatusTfrIEs
(
SztProtIE_Field_MMEStatusTfrIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_MMEStatusTfrIEs(param, ptr, mBuf)
SztProtIE_Field_MMEStatusTfrIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_MMEStatusTfrIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueMMEStatusTfrIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_MMEStatusTfrIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_MMEStatusTfrIEs
*  DESC: Function to Unpack SztProtIE_Cont_MMEStatusTfrIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_MMEStatusTfrIEs
(
SztProtIE_Cont_MMEStatusTfrIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_MMEStatusTfrIEs(param, ptr, mBuf)
SztProtIE_Cont_MMEStatusTfrIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_MMEStatusTfrIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_MMEStatusTfrIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_MMEStatusTfrIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_MMEStatusTfrIEs */



/*
* FUN : cmUnpkSztMMEStatusTfr
*  DESC: Function to Unpack SztMMEStatusTfr structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztMMEStatusTfr
(
SztMMEStatusTfr *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztMMEStatusTfr(param, ptr, mBuf)
SztMMEStatusTfr *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztMMEStatusTfr) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_MMEStatusTfrIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztMMEStatusTfr */



/*
* FUN : cmUnpkSzt_ValueTraceStartIEsCls
*  DESC: Function to Unpack Szt_ValueTraceStartIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueTraceStartIEsCls
(
Szt_ValueTraceStartIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueTraceStartIEsCls(param, val, ptr, mBuf)
Szt_ValueTraceStartIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueTraceStartIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_TraceActvn:
			CMCHKUNPKPTR(cmUnpkSztTraceActvn, &param->u.sztTraceActvn, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueTraceStartIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_TraceStartIEs
*  DESC: Function to Unpack SztProtIE_Field_TraceStartIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_TraceStartIEs
(
SztProtIE_Field_TraceStartIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_TraceStartIEs(param, ptr, mBuf)
SztProtIE_Field_TraceStartIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_TraceStartIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueTraceStartIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_TraceStartIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_TraceStartIEs
*  DESC: Function to Unpack SztProtIE_Cont_TraceStartIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_TraceStartIEs
(
SztProtIE_Cont_TraceStartIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_TraceStartIEs(param, ptr, mBuf)
SztProtIE_Cont_TraceStartIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_TraceStartIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_TraceStartIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_TraceStartIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_TraceStartIEs */



/*
* FUN : cmUnpkSztTraceStart
*  DESC: Function to Unpack SztTraceStart structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztTraceStart
(
SztTraceStart *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztTraceStart(param, ptr, mBuf)
SztTraceStart *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztTraceStart) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_TraceStartIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztTraceStart */



/*
* FUN : cmUnpkSzt_ValueTraceFailIndIEsCls
*  DESC: Function to Unpack Szt_ValueTraceFailIndIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueTraceFailIndIEsCls
(
Szt_ValueTraceFailIndIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueTraceFailIndIEsCls(param, val, ptr, mBuf)
Szt_ValueTraceFailIndIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueTraceFailIndIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_E_UTRAN_Trace_ID:
			SZUCHKUNPKPTR(cmUnpkSztE_UTRAN_Trace_ID, &param->u.sztE_UTRAN_Trace_ID, ptr, mBuf); 
			break;
		case Sztid_Cause:
			CMCHKUNPKPTR(cmUnpkSztCause, &param->u.sztCause, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueTraceFailIndIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_TraceFailIndIEs
*  DESC: Function to Unpack SztProtIE_Field_TraceFailIndIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_TraceFailIndIEs
(
SztProtIE_Field_TraceFailIndIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_TraceFailIndIEs(param, ptr, mBuf)
SztProtIE_Field_TraceFailIndIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_TraceFailIndIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueTraceFailIndIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_TraceFailIndIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_TraceFailIndIEs
*  DESC: Function to Unpack SztProtIE_Cont_TraceFailIndIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_TraceFailIndIEs
(
SztProtIE_Cont_TraceFailIndIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_TraceFailIndIEs(param, ptr, mBuf)
SztProtIE_Cont_TraceFailIndIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_TraceFailIndIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_TraceFailIndIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_TraceFailIndIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_TraceFailIndIEs */



/*
* FUN : cmUnpkSztTraceFailInd
*  DESC: Function to Unpack SztTraceFailInd structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztTraceFailInd
(
SztTraceFailInd *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztTraceFailInd(param, ptr, mBuf)
SztTraceFailInd *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztTraceFailInd) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_TraceFailIndIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztTraceFailInd */



/*
* FUN : cmUnpkSzt_ValueDeactvTraceIEsCls
*  DESC: Function to Unpack Szt_ValueDeactvTraceIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueDeactvTraceIEsCls
(
Szt_ValueDeactvTraceIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueDeactvTraceIEsCls(param, val, ptr, mBuf)
Szt_ValueDeactvTraceIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueDeactvTraceIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_E_UTRAN_Trace_ID:
			SZUCHKUNPKPTR(cmUnpkSztE_UTRAN_Trace_ID, &param->u.sztE_UTRAN_Trace_ID, ptr, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueDeactvTraceIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_DeactvTraceIEs
*  DESC: Function to Unpack SztProtIE_Field_DeactvTraceIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_DeactvTraceIEs
(
SztProtIE_Field_DeactvTraceIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_DeactvTraceIEs(param, ptr, mBuf)
SztProtIE_Field_DeactvTraceIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_DeactvTraceIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueDeactvTraceIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_DeactvTraceIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_DeactvTraceIEs
*  DESC: Function to Unpack SztProtIE_Cont_DeactvTraceIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_DeactvTraceIEs
(
SztProtIE_Cont_DeactvTraceIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_DeactvTraceIEs(param, ptr, mBuf)
SztProtIE_Cont_DeactvTraceIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_DeactvTraceIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_DeactvTraceIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_DeactvTraceIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_DeactvTraceIEs */



/*
* FUN : cmUnpkSztDeactvTrace
*  DESC: Function to Unpack SztDeactvTrace structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztDeactvTrace
(
SztDeactvTrace *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztDeactvTrace(param, ptr, mBuf)
SztDeactvTrace *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztDeactvTrace) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_DeactvTraceIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztDeactvTrace */



/*
* FUN : cmUnpkSzt_ValueCellTrafficTraceIEsCls
*  DESC: Function to Unpack Szt_ValueCellTrafficTraceIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueCellTrafficTraceIEsCls
(
Szt_ValueCellTrafficTraceIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueCellTrafficTraceIEsCls(param, val, ptr, mBuf)
Szt_ValueCellTrafficTraceIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueCellTrafficTraceIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_E_UTRAN_Trace_ID:
			SZUCHKUNPKPTR(cmUnpkSztE_UTRAN_Trace_ID, &param->u.sztE_UTRAN_Trace_ID, ptr, mBuf); 
			break;
		case Sztid_EUTRAN_CGI:
			CMCHKUNPKPTR(cmUnpkSztEUTRAN_CGI, &param->u.sztEUTRAN_CGI, ptr, mBuf);
			break;
		case Sztid_TraceCollectionEntityIPAddr:
			CMCHKUNPKPTR(cmUnpkSztTportLyrAddr, &param->u.sztTportLyrAddr, ptr, mBuf); 
			break;
		case Sztid_PrivacyIndicator:
			CMCHKUNPK(cmUnpkSztPrivacyIndicator, &param->u.sztPrivacyIndicator, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueCellTrafficTraceIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_CellTrafficTraceIEs
*  DESC: Function to Unpack SztProtIE_Field_CellTrafficTraceIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_CellTrafficTraceIEs
(
SztProtIE_Field_CellTrafficTraceIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_CellTrafficTraceIEs(param, ptr, mBuf)
SztProtIE_Field_CellTrafficTraceIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_CellTrafficTraceIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueCellTrafficTraceIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_CellTrafficTraceIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_CellTrafficTraceIEs
*  DESC: Function to Unpack SztProtIE_Cont_CellTrafficTraceIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_CellTrafficTraceIEs
(
SztProtIE_Cont_CellTrafficTraceIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_CellTrafficTraceIEs(param, ptr, mBuf)
SztProtIE_Cont_CellTrafficTraceIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_CellTrafficTraceIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_CellTrafficTraceIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_CellTrafficTraceIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_CellTrafficTraceIEs */



/*
* FUN : cmUnpkSztCellTrafficTrace
*  DESC: Function to Unpack SztCellTrafficTrace structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztCellTrafficTrace
(
SztCellTrafficTrace *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztCellTrafficTrace(param, ptr, mBuf)
SztCellTrafficTrace *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztCellTrafficTrace) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_CellTrafficTraceIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztCellTrafficTrace */



/*
* FUN : cmUnpkSzt_ValueLocRprtngCntrlIEsCls
*  DESC: Function to Unpack Szt_ValueLocRprtngCntrlIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueLocRprtngCntrlIEsCls
(
Szt_ValueLocRprtngCntrlIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueLocRprtngCntrlIEsCls(param, val, ptr, mBuf)
Szt_ValueLocRprtngCntrlIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueLocRprtngCntrlIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_RqstTyp:
			CMCHKUNPKPTR(cmUnpkSztRqstTyp, &param->u.sztRqstTyp, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueLocRprtngCntrlIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_LocRprtngCntrlIEs
*  DESC: Function to Unpack SztProtIE_Field_LocRprtngCntrlIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_LocRprtngCntrlIEs
(
SztProtIE_Field_LocRprtngCntrlIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_LocRprtngCntrlIEs(param, ptr, mBuf)
SztProtIE_Field_LocRprtngCntrlIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_LocRprtngCntrlIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueLocRprtngCntrlIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_LocRprtngCntrlIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_LocRprtngCntrlIEs
*  DESC: Function to Unpack SztProtIE_Cont_LocRprtngCntrlIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_LocRprtngCntrlIEs
(
SztProtIE_Cont_LocRprtngCntrlIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_LocRprtngCntrlIEs(param, ptr, mBuf)
SztProtIE_Cont_LocRprtngCntrlIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_LocRprtngCntrlIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_LocRprtngCntrlIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_LocRprtngCntrlIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_LocRprtngCntrlIEs */



/*
* FUN : cmUnpkSztLocRprtngCntrl
*  DESC: Function to Unpack SztLocRprtngCntrl structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztLocRprtngCntrl
(
SztLocRprtngCntrl *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztLocRprtngCntrl(param, ptr, mBuf)
SztLocRprtngCntrl *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztLocRprtngCntrl) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_LocRprtngCntrlIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztLocRprtngCntrl */



/*
* FUN : cmUnpkSzt_ValueLocRprtngFailIndIEsCls
*  DESC: Function to Unpack Szt_ValueLocRprtngFailIndIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueLocRprtngFailIndIEsCls
(
Szt_ValueLocRprtngFailIndIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueLocRprtngFailIndIEsCls(param, val, ptr, mBuf)
Szt_ValueLocRprtngFailIndIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueLocRprtngFailIndIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_Cause:
			CMCHKUNPKPTR(cmUnpkSztCause, &param->u.sztCause, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueLocRprtngFailIndIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_LocRprtngFailIndIEs
*  DESC: Function to Unpack SztProtIE_Field_LocRprtngFailIndIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_LocRprtngFailIndIEs
(
SztProtIE_Field_LocRprtngFailIndIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_LocRprtngFailIndIEs(param, ptr, mBuf)
SztProtIE_Field_LocRprtngFailIndIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_LocRprtngFailIndIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueLocRprtngFailIndIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_LocRprtngFailIndIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_LocRprtngFailIndIEs
*  DESC: Function to Unpack SztProtIE_Cont_LocRprtngFailIndIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_LocRprtngFailIndIEs
(
SztProtIE_Cont_LocRprtngFailIndIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_LocRprtngFailIndIEs(param, ptr, mBuf)
SztProtIE_Cont_LocRprtngFailIndIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_LocRprtngFailIndIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_LocRprtngFailIndIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_LocRprtngFailIndIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_LocRprtngFailIndIEs */



/*
* FUN : cmUnpkSztLocRprtngFailInd
*  DESC: Function to Unpack SztLocRprtngFailInd structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztLocRprtngFailInd
(
SztLocRprtngFailInd *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztLocRprtngFailInd(param, ptr, mBuf)
SztLocRprtngFailInd *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztLocRprtngFailInd) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_LocRprtngFailIndIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztLocRprtngFailInd */



/*
* FUN : cmUnpkSzt_ValueLocReportIEsCls
*  DESC: Function to Unpack Szt_ValueLocReportIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueLocReportIEsCls
(
Szt_ValueLocReportIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueLocReportIEsCls(param, val, ptr, mBuf)
Szt_ValueLocReportIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueLocReportIEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_EUTRAN_CGI:
			CMCHKUNPKPTR(cmUnpkSztEUTRAN_CGI, &param->u.sztEUTRAN_CGI, ptr, mBuf);
			break;
		case Sztid_TAI:
			CMCHKUNPKPTR(cmUnpkSztTAI, &param->u.sztTAI, ptr, mBuf);
			break;
		case Sztid_RqstTyp:
			CMCHKUNPKPTR(cmUnpkSztRqstTyp, &param->u.sztRqstTyp, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueLocReportIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_LocReportIEs
*  DESC: Function to Unpack SztProtIE_Field_LocReportIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_LocReportIEs
(
SztProtIE_Field_LocReportIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_LocReportIEs(param, ptr, mBuf)
SztProtIE_Field_LocReportIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_LocReportIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueLocReportIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_LocReportIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_LocReportIEs
*  DESC: Function to Unpack SztProtIE_Cont_LocReportIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_LocReportIEs
(
SztProtIE_Cont_LocReportIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_LocReportIEs(param, ptr, mBuf)
SztProtIE_Cont_LocReportIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_LocReportIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_LocReportIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_LocReportIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_LocReportIEs */



/*
* FUN : cmUnpkSztLocReport
*  DESC: Function to Unpack SztLocReport structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztLocReport
(
SztLocReport *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztLocReport(param, ptr, mBuf)
SztLocReport *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztLocReport) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_LocReportIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztLocReport */



/*
* FUN : cmUnpkSzt_ValueOverloadStartIEsCls
*  DESC: Function to Unpack Szt_ValueOverloadStartIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueOverloadStartIEsCls
(
Szt_ValueOverloadStartIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueOverloadStartIEsCls(param, val, ptr, mBuf)
Szt_ValueOverloadStartIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueOverloadStartIEsCls) 
	
	switch (val)
	{
		case Sztid_OverloadResp:
			CMCHKUNPKPTR(cmUnpkSztOverloadResp, &param->u.sztOverloadResp, ptr, mBuf);
			break;
		case Sztid_GUMMEILst:
			CMCHKUNPKPTR(cmUnpkSztGUMMEILst, &param->u.sztGUMMEILst, ptr, mBuf);
			break;
		case Sztid_TrafficLoadReductionInd:
			CMCHKUNPK(cmUnpkSztTrafficLoadReductionInd, &param->u.sztTrafficLoadReductionInd, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueOverloadStartIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_OverloadStartIEs
*  DESC: Function to Unpack SztProtIE_Field_OverloadStartIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_OverloadStartIEs
(
SztProtIE_Field_OverloadStartIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_OverloadStartIEs(param, ptr, mBuf)
SztProtIE_Field_OverloadStartIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_OverloadStartIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueOverloadStartIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_OverloadStartIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_OverloadStartIEs
*  DESC: Function to Unpack SztProtIE_Cont_OverloadStartIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_OverloadStartIEs
(
SztProtIE_Cont_OverloadStartIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_OverloadStartIEs(param, ptr, mBuf)
SztProtIE_Cont_OverloadStartIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_OverloadStartIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_OverloadStartIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_OverloadStartIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_OverloadStartIEs */



/*
* FUN : cmUnpkSztOverloadStart
*  DESC: Function to Unpack SztOverloadStart structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztOverloadStart
(
SztOverloadStart *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztOverloadStart(param, ptr, mBuf)
SztOverloadStart *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztOverloadStart) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_OverloadStartIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztOverloadStart */



/*
* FUN : cmUnpkSzt_ValueOverloadStopIEsCls
*  DESC: Function to Unpack Szt_ValueOverloadStopIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueOverloadStopIEsCls
(
Szt_ValueOverloadStopIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueOverloadStopIEsCls(param, val, ptr, mBuf)
Szt_ValueOverloadStopIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueOverloadStopIEsCls) 
	
	switch (val)
	{
		case Sztid_GUMMEILst:
			CMCHKUNPKPTR(cmUnpkSztGUMMEILst, &param->u.sztGUMMEILst, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueOverloadStopIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_OverloadStopIEs
*  DESC: Function to Unpack SztProtIE_Field_OverloadStopIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_OverloadStopIEs
(
SztProtIE_Field_OverloadStopIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_OverloadStopIEs(param, ptr, mBuf)
SztProtIE_Field_OverloadStopIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_OverloadStopIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueOverloadStopIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_OverloadStopIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_OverloadStopIEs
*  DESC: Function to Unpack SztProtIE_Cont_OverloadStopIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_OverloadStopIEs
(
SztProtIE_Cont_OverloadStopIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_OverloadStopIEs(param, ptr, mBuf)
SztProtIE_Cont_OverloadStopIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_OverloadStopIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_OverloadStopIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_OverloadStopIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_OverloadStopIEs */



/*
* FUN : cmUnpkSztOverloadStop
*  DESC: Function to Unpack SztOverloadStop structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztOverloadStop
(
SztOverloadStop *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztOverloadStop(param, ptr, mBuf)
SztOverloadStop *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztOverloadStop) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_OverloadStopIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztOverloadStop */



/*
* FUN : cmUnpkSzt_ValueWriteReplaceWarningRqstIEsCls
*  DESC: Function to Unpack Szt_ValueWriteReplaceWarningRqstIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueWriteReplaceWarningRqstIEsCls
(
Szt_ValueWriteReplaceWarningRqstIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueWriteReplaceWarningRqstIEsCls(param, val, ptr, mBuf)
Szt_ValueWriteReplaceWarningRqstIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueWriteReplaceWarningRqstIEsCls) 
	
	switch (val)
	{
		case Sztid_MsgIdentifier:
			CMCHKUNPK(cmUnpkSztMsgIdentifier, &param->u.sztMsgIdentifier, mBuf); 
			break;
		case Sztid_SerialNumber:
			CMCHKUNPK(cmUnpkSztSerialNumber, &param->u.sztSerialNumber, mBuf); 
			break;
		case Sztid_WarningAreaLst:
			CMCHKUNPKPTR(cmUnpkSztWarningAreaLst, &param->u.sztWarningAreaLst, ptr, mBuf);
			break;
		case Sztid_RepetitionPeriod:
			CMCHKUNPK(cmUnpkSztRepetitionPeriod, &param->u.sztRepetitionPeriod, mBuf); 
			break;
		case Sztid_ExtendedRepetitionPeriod:
			CMCHKUNPK(cmUnpkSztExtendedRepetitionPeriod, &param->u.sztExtendedRepetitionPeriod, mBuf); 
			break;
		case Sztid_NumberofBroadcastRqst:
			CMCHKUNPK(cmUnpkSztNumberofBroadcastRqst, &param->u.sztNumberofBroadcastRqst, mBuf); 
			break;
		case Sztid_WarningTyp:
			CMCHKUNPK(cmUnpkSztWarningTyp, &param->u.sztWarningTyp, mBuf); 
			break;
		case Sztid_WarningSecurInfo:
			SZUCHKUNPKPTR(cmUnpkSztWarningSecurInfo, &param->u.sztWarningSecurInfo, ptr, mBuf); 
			break;
		case Sztid_DataCodingScheme:
			CMCHKUNPK(cmUnpkSztDataCodingScheme, &param->u.sztDataCodingScheme, mBuf); 
			break;
		case Sztid_WarningMsgContents:
			SZUCHKUNPKPTR(cmUnpkSztWarningMsgContents, &param->u.sztWarningMsgContents, ptr, mBuf); 
			break;
		case Sztid_ConcurrentWarningMsgIndicator:
			CMCHKUNPK(cmUnpkSztConcurrentWarningMsgIndicator, &param->u.sztConcurrentWarningMsgIndicator, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueWriteReplaceWarningRqstIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_WriteReplaceWarningRqstIEs
*  DESC: Function to Unpack SztProtIE_Field_WriteReplaceWarningRqstIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_WriteReplaceWarningRqstIEs
(
SztProtIE_Field_WriteReplaceWarningRqstIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_WriteReplaceWarningRqstIEs(param, ptr, mBuf)
SztProtIE_Field_WriteReplaceWarningRqstIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_WriteReplaceWarningRqstIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueWriteReplaceWarningRqstIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_WriteReplaceWarningRqstIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_WriteReplaceWarningRqstIEs
*  DESC: Function to Unpack SztProtIE_Cont_WriteReplaceWarningRqstIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_WriteReplaceWarningRqstIEs
(
SztProtIE_Cont_WriteReplaceWarningRqstIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_WriteReplaceWarningRqstIEs(param, ptr, mBuf)
SztProtIE_Cont_WriteReplaceWarningRqstIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_WriteReplaceWarningRqstIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_WriteReplaceWarningRqstIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_WriteReplaceWarningRqstIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_WriteReplaceWarningRqstIEs */



/*
* FUN : cmUnpkSztWriteReplaceWarningRqst
*  DESC: Function to Unpack SztWriteReplaceWarningRqst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztWriteReplaceWarningRqst
(
SztWriteReplaceWarningRqst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztWriteReplaceWarningRqst(param, ptr, mBuf)
SztWriteReplaceWarningRqst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztWriteReplaceWarningRqst) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_WriteReplaceWarningRqstIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztWriteReplaceWarningRqst */



/*
* FUN : cmUnpkSzt_ValueWriteReplaceWarningRespIEsCls
*  DESC: Function to Unpack Szt_ValueWriteReplaceWarningRespIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueWriteReplaceWarningRespIEsCls
(
Szt_ValueWriteReplaceWarningRespIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueWriteReplaceWarningRespIEsCls(param, val, ptr, mBuf)
Szt_ValueWriteReplaceWarningRespIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueWriteReplaceWarningRespIEsCls) 
	
	switch (val)
	{
		case Sztid_MsgIdentifier:
			CMCHKUNPK(cmUnpkSztMsgIdentifier, &param->u.sztMsgIdentifier, mBuf); 
			break;
		case Sztid_SerialNumber:
			CMCHKUNPK(cmUnpkSztSerialNumber, &param->u.sztSerialNumber, mBuf); 
			break;
		case Sztid_BroadcastCompletedAreaLst:
			CMCHKUNPKPTR(cmUnpkSztBroadcastCompletedAreaLst, &param->u.sztBroadcastCompletedAreaLst, ptr, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkSztCriticalityDiag, &param->u.sztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueWriteReplaceWarningRespIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_WriteReplaceWarningRespIEs
*  DESC: Function to Unpack SztProtIE_Field_WriteReplaceWarningRespIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_WriteReplaceWarningRespIEs
(
SztProtIE_Field_WriteReplaceWarningRespIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_WriteReplaceWarningRespIEs(param, ptr, mBuf)
SztProtIE_Field_WriteReplaceWarningRespIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_WriteReplaceWarningRespIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueWriteReplaceWarningRespIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_WriteReplaceWarningRespIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_WriteReplaceWarningRespIEs
*  DESC: Function to Unpack SztProtIE_Cont_WriteReplaceWarningRespIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_WriteReplaceWarningRespIEs
(
SztProtIE_Cont_WriteReplaceWarningRespIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_WriteReplaceWarningRespIEs(param, ptr, mBuf)
SztProtIE_Cont_WriteReplaceWarningRespIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_WriteReplaceWarningRespIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_WriteReplaceWarningRespIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_WriteReplaceWarningRespIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_WriteReplaceWarningRespIEs */



/*
* FUN : cmUnpkSztWriteReplaceWarningResp
*  DESC: Function to Unpack SztWriteReplaceWarningResp structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztWriteReplaceWarningResp
(
SztWriteReplaceWarningResp *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztWriteReplaceWarningResp(param, ptr, mBuf)
SztWriteReplaceWarningResp *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztWriteReplaceWarningResp) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_WriteReplaceWarningRespIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztWriteReplaceWarningResp */



/*
* FUN : cmUnpkSztInter_SystemInformTfrTyp
*  DESC: Function to Unpack SztInter_SystemInformTfrTyp structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztInter_SystemInformTfrTyp
(
SztInter_SystemInformTfrTyp *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztInter_SystemInformTfrTyp(param, ptr, mBuf)
SztInter_SystemInformTfrTyp *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztInter_SystemInformTfrTyp) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case INTER_SYSTEMINFORMTFRTYP_RIMTFR :
				CMCHKUNPKPTR(cmUnpkSztRIMTfr, &param->val.rIMTfr, ptr, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztInter_SystemInformTfrTyp */



/*
* FUN : cmUnpkSzt_ValueENBDirectInformTfrIEsCls
*  DESC: Function to Unpack Szt_ValueENBDirectInformTfrIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueENBDirectInformTfrIEsCls
(
Szt_ValueENBDirectInformTfrIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueENBDirectInformTfrIEsCls(param, val, ptr, mBuf)
Szt_ValueENBDirectInformTfrIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueENBDirectInformTfrIEsCls) 
	
	switch (val)
	{
		case Sztid_Inter_SystemInformTfrTypEDT:
			CMCHKUNPKPTR(cmUnpkSztInter_SystemInformTfrTyp, &param->u.sztInter_SystemInformTfrTyp, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueENBDirectInformTfrIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_ENBDirectInformTfrIEs
*  DESC: Function to Unpack SztProtIE_Field_ENBDirectInformTfrIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_ENBDirectInformTfrIEs
(
SztProtIE_Field_ENBDirectInformTfrIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_ENBDirectInformTfrIEs(param, ptr, mBuf)
SztProtIE_Field_ENBDirectInformTfrIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_ENBDirectInformTfrIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueENBDirectInformTfrIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_ENBDirectInformTfrIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_ENBDirectInformTfrIEs
*  DESC: Function to Unpack SztProtIE_Cont_ENBDirectInformTfrIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_ENBDirectInformTfrIEs
(
SztProtIE_Cont_ENBDirectInformTfrIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_ENBDirectInformTfrIEs(param, ptr, mBuf)
SztProtIE_Cont_ENBDirectInformTfrIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_ENBDirectInformTfrIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_ENBDirectInformTfrIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_ENBDirectInformTfrIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_ENBDirectInformTfrIEs */



/*
* FUN : cmUnpkSztENBDirectInformTfr
*  DESC: Function to Unpack SztENBDirectInformTfr structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztENBDirectInformTfr
(
SztENBDirectInformTfr *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztENBDirectInformTfr(param, ptr, mBuf)
SztENBDirectInformTfr *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztENBDirectInformTfr) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_ENBDirectInformTfrIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztENBDirectInformTfr */



/*
* FUN : cmUnpkSzt_ValueMMEDirectInformTfrIEsCls
*  DESC: Function to Unpack Szt_ValueMMEDirectInformTfrIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueMMEDirectInformTfrIEsCls
(
Szt_ValueMMEDirectInformTfrIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueMMEDirectInformTfrIEsCls(param, val, ptr, mBuf)
Szt_ValueMMEDirectInformTfrIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueMMEDirectInformTfrIEsCls) 
	
	switch (val)
	{
		case Sztid_Inter_SystemInformTfrTypMDT:
			CMCHKUNPKPTR(cmUnpkSztInter_SystemInformTfrTyp, &param->u.sztInter_SystemInformTfrTyp, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueMMEDirectInformTfrIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_MMEDirectInformTfrIEs
*  DESC: Function to Unpack SztProtIE_Field_MMEDirectInformTfrIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_MMEDirectInformTfrIEs
(
SztProtIE_Field_MMEDirectInformTfrIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_MMEDirectInformTfrIEs(param, ptr, mBuf)
SztProtIE_Field_MMEDirectInformTfrIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_MMEDirectInformTfrIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueMMEDirectInformTfrIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_MMEDirectInformTfrIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_MMEDirectInformTfrIEs
*  DESC: Function to Unpack SztProtIE_Cont_MMEDirectInformTfrIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_MMEDirectInformTfrIEs
(
SztProtIE_Cont_MMEDirectInformTfrIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_MMEDirectInformTfrIEs(param, ptr, mBuf)
SztProtIE_Cont_MMEDirectInformTfrIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_MMEDirectInformTfrIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_MMEDirectInformTfrIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_MMEDirectInformTfrIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_MMEDirectInformTfrIEs */



/*
* FUN : cmUnpkSztMMEDirectInformTfr
*  DESC: Function to Unpack SztMMEDirectInformTfr structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztMMEDirectInformTfr
(
SztMMEDirectInformTfr *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztMMEDirectInformTfr(param, ptr, mBuf)
SztMMEDirectInformTfr *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztMMEDirectInformTfr) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_MMEDirectInformTfrIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztMMEDirectInformTfr */



/*
* FUN : cmUnpkSzt_ValueENBConfigTfrIEsCls
*  DESC: Function to Unpack Szt_ValueENBConfigTfrIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueENBConfigTfrIEsCls
(
Szt_ValueENBConfigTfrIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueENBConfigTfrIEsCls(param, val, ptr, mBuf)
Szt_ValueENBConfigTfrIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueENBConfigTfrIEsCls) 
	
	switch (val)
	{
		case Sztid_SONConfigTfrECT:
			CMCHKUNPKPTR(cmUnpkSztSONConfigTfr, &param->u.sztSONConfigTfr, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueENBConfigTfrIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_ENBConfigTfrIEs
*  DESC: Function to Unpack SztProtIE_Field_ENBConfigTfrIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_ENBConfigTfrIEs
(
SztProtIE_Field_ENBConfigTfrIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_ENBConfigTfrIEs(param, ptr, mBuf)
SztProtIE_Field_ENBConfigTfrIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_ENBConfigTfrIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueENBConfigTfrIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_ENBConfigTfrIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_ENBConfigTfrIEs
*  DESC: Function to Unpack SztProtIE_Cont_ENBConfigTfrIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_ENBConfigTfrIEs
(
SztProtIE_Cont_ENBConfigTfrIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_ENBConfigTfrIEs(param, ptr, mBuf)
SztProtIE_Cont_ENBConfigTfrIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_ENBConfigTfrIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_ENBConfigTfrIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_ENBConfigTfrIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_ENBConfigTfrIEs */



/*
* FUN : cmUnpkSztENBConfigTfr
*  DESC: Function to Unpack SztENBConfigTfr structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztENBConfigTfr
(
SztENBConfigTfr *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztENBConfigTfr(param, ptr, mBuf)
SztENBConfigTfr *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztENBConfigTfr) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_ENBConfigTfrIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztENBConfigTfr */



/*
* FUN : cmUnpkSzt_ValueMMEConfigTfrIEsCls
*  DESC: Function to Unpack Szt_ValueMMEConfigTfrIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueMMEConfigTfrIEsCls
(
Szt_ValueMMEConfigTfrIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueMMEConfigTfrIEsCls(param, val, ptr, mBuf)
Szt_ValueMMEConfigTfrIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueMMEConfigTfrIEsCls) 
	
	switch (val)
	{
		case Sztid_SONConfigTfrMCT:
			CMCHKUNPKPTR(cmUnpkSztSONConfigTfr, &param->u.sztSONConfigTfr, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueMMEConfigTfrIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_MMEConfigTfrIEs
*  DESC: Function to Unpack SztProtIE_Field_MMEConfigTfrIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_MMEConfigTfrIEs
(
SztProtIE_Field_MMEConfigTfrIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_MMEConfigTfrIEs(param, ptr, mBuf)
SztProtIE_Field_MMEConfigTfrIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_MMEConfigTfrIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueMMEConfigTfrIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_MMEConfigTfrIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_MMEConfigTfrIEs
*  DESC: Function to Unpack SztProtIE_Cont_MMEConfigTfrIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_MMEConfigTfrIEs
(
SztProtIE_Cont_MMEConfigTfrIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_MMEConfigTfrIEs(param, ptr, mBuf)
SztProtIE_Cont_MMEConfigTfrIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_MMEConfigTfrIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_MMEConfigTfrIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_MMEConfigTfrIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_MMEConfigTfrIEs */



/*
* FUN : cmUnpkSztMMEConfigTfr
*  DESC: Function to Unpack SztMMEConfigTfr structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztMMEConfigTfr
(
SztMMEConfigTfr *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztMMEConfigTfr(param, ptr, mBuf)
SztMMEConfigTfr *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztMMEConfigTfr) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_MMEConfigTfrIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztMMEConfigTfr */



/*
* FUN : cmUnpkSzt_ValuePrivMsgIEsCls
*  DESC: Function to Unpack Szt_ValuePrivMsgIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValuePrivMsgIEsCls
(
Szt_ValuePrivMsgIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValuePrivMsgIEsCls(param, val, ptr, mBuf)
Szt_ValuePrivMsgIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValuePrivMsgIEsCls) 
	
	RETVALUE(RFAILED);
}	 /* End of function cmUnpkSzt_ValuePrivMsgIEsCls */



/*
* FUN : cmUnpkSztPrivIE_Field_PrivMsgIEs
*  DESC: Function to Unpack SztPrivIE_Field_PrivMsgIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztPrivIE_Field_PrivMsgIEs
(
SztPrivIE_Field_PrivMsgIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztPrivIE_Field_PrivMsgIEs(param, ptr, mBuf)
SztPrivIE_Field_PrivMsgIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztPrivIE_Field_PrivMsgIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztPrivIE_ID, &param->id, ptr, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztPrivIE_Field_PrivMsgIEs */



/*
* FUN : cmUnpkSztPrivIE_Cont_PrivMsgIEs
*  DESC: Function to Unpack SztPrivIE_Cont_PrivMsgIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztPrivIE_Cont_PrivMsgIEs
(
SztPrivIE_Cont_PrivMsgIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztPrivIE_Cont_PrivMsgIEs(param, ptr, mBuf)
SztPrivIE_Cont_PrivMsgIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztPrivIE_Cont_PrivMsgIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztPrivIE_Field_PrivMsgIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztPrivIE_Field_PrivMsgIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztPrivIE_Cont_PrivMsgIEs */



/*
* FUN : cmUnpkSztPrivMsg
*  DESC: Function to Unpack SztPrivMsg structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztPrivMsg
(
SztPrivMsg *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztPrivMsg(param, ptr, mBuf)
SztPrivMsg *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztPrivMsg) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztPrivIE_Cont_PrivMsgIEs, &param->privateIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztPrivMsg */



/*
* FUN : cmUnpkSzt_ValueKillRqstIEsCls
*  DESC: Function to Unpack Szt_ValueKillRqstIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueKillRqstIEsCls
(
Szt_ValueKillRqstIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueKillRqstIEsCls(param, val, ptr, mBuf)
Szt_ValueKillRqstIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueKillRqstIEsCls) 
	
	switch (val)
	{
		case Sztid_MsgIdentifier:
			CMCHKUNPK(cmUnpkSztMsgIdentifier, &param->u.sztMsgIdentifier, mBuf); 
			break;
		case Sztid_SerialNumber:
			CMCHKUNPK(cmUnpkSztSerialNumber, &param->u.sztSerialNumber, mBuf); 
			break;
		case Sztid_WarningAreaLst:
			CMCHKUNPKPTR(cmUnpkSztWarningAreaLst, &param->u.sztWarningAreaLst, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueKillRqstIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_KillRqstIEs
*  DESC: Function to Unpack SztProtIE_Field_KillRqstIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_KillRqstIEs
(
SztProtIE_Field_KillRqstIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_KillRqstIEs(param, ptr, mBuf)
SztProtIE_Field_KillRqstIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_KillRqstIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueKillRqstIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_KillRqstIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_KillRqstIEs
*  DESC: Function to Unpack SztProtIE_Cont_KillRqstIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_KillRqstIEs
(
SztProtIE_Cont_KillRqstIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_KillRqstIEs(param, ptr, mBuf)
SztProtIE_Cont_KillRqstIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_KillRqstIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_KillRqstIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_KillRqstIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_KillRqstIEs */



/*
* FUN : cmUnpkSztKillRqst
*  DESC: Function to Unpack SztKillRqst structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztKillRqst
(
SztKillRqst *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztKillRqst(param, ptr, mBuf)
SztKillRqst *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztKillRqst) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_KillRqstIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztKillRqst */



/*
* FUN : cmUnpkSzt_ValueKillRespIEsCls
*  DESC: Function to Unpack Szt_ValueKillRespIEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueKillRespIEsCls
(
Szt_ValueKillRespIEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueKillRespIEsCls(param, val, ptr, mBuf)
Szt_ValueKillRespIEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueKillRespIEsCls) 
	
	switch (val)
	{
		case Sztid_MsgIdentifier:
			CMCHKUNPK(cmUnpkSztMsgIdentifier, &param->u.sztMsgIdentifier, mBuf); 
			break;
		case Sztid_SerialNumber:
			CMCHKUNPK(cmUnpkSztSerialNumber, &param->u.sztSerialNumber, mBuf); 
			break;
		case Sztid_BroadcastCancelledAreaLst:
			CMCHKUNPKPTR(cmUnpkSztBroadcastCancelledAreaLst, &param->u.sztBroadcastCancelledAreaLst, ptr, mBuf);
			break;
		case Sztid_CriticalityDiag:
			CMCHKUNPKPTR(cmUnpkSztCriticalityDiag, &param->u.sztCriticalityDiag, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueKillRespIEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_KillRespIEs
*  DESC: Function to Unpack SztProtIE_Field_KillRespIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_KillRespIEs
(
SztProtIE_Field_KillRespIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_KillRespIEs(param, ptr, mBuf)
SztProtIE_Field_KillRespIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_KillRespIEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueKillRespIEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_KillRespIEs */



/*
* FUN : cmUnpkSztProtIE_Cont_KillRespIEs
*  DESC: Function to Unpack SztProtIE_Cont_KillRespIEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_KillRespIEs
(
SztProtIE_Cont_KillRespIEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_KillRespIEs(param, ptr, mBuf)
SztProtIE_Cont_KillRespIEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_KillRespIEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_KillRespIEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_KillRespIEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_KillRespIEs */



/*
* FUN : cmUnpkSztKillResp
*  DESC: Function to Unpack SztKillResp structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztKillResp
(
SztKillResp *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztKillResp(param, ptr, mBuf)
SztKillResp *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztKillResp) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_KillRespIEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztKillResp */



/*
* FUN : cmUnpkSzt_ValueDlnkUEAssociatedLPPaTport_IEsCls
*  DESC: Function to Unpack Szt_ValueDlnkUEAssociatedLPPaTport_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueDlnkUEAssociatedLPPaTport_IEsCls
(
Szt_ValueDlnkUEAssociatedLPPaTport_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueDlnkUEAssociatedLPPaTport_IEsCls(param, val, ptr, mBuf)
Szt_ValueDlnkUEAssociatedLPPaTport_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueDlnkUEAssociatedLPPaTport_IEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_Routing_ID:
			CMCHKUNPK(cmUnpkSztRouting_ID, &param->u.sztRouting_ID, mBuf); 
			break;
		case Sztid_LPPa_PDU:
			SZUCHKUNPKPTR(cmUnpkSztLPPa_PDU, &param->u.sztLPPa_PDU, ptr, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueDlnkUEAssociatedLPPaTport_IEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs
*  DESC: Function to Unpack SztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs
(
SztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs(param, ptr, mBuf)
SztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueDlnkUEAssociatedLPPaTport_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs */



/*
* FUN : cmUnpkSztProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs
*  DESC: Function to Unpack SztProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs
(
SztProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs(param, ptr, mBuf)
SztProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs */



/*
* FUN : cmUnpkSztDlnkUEAssociatedLPPaTport
*  DESC: Function to Unpack SztDlnkUEAssociatedLPPaTport structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztDlnkUEAssociatedLPPaTport
(
SztDlnkUEAssociatedLPPaTport *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztDlnkUEAssociatedLPPaTport(param, ptr, mBuf)
SztDlnkUEAssociatedLPPaTport *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztDlnkUEAssociatedLPPaTport) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_DlnkUEAssociatedLPPaTport_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztDlnkUEAssociatedLPPaTport */



/*
* FUN : cmUnpkSzt_ValueUlnkUEAssociatedLPPaTport_IEsCls
*  DESC: Function to Unpack Szt_ValueUlnkUEAssociatedLPPaTport_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueUlnkUEAssociatedLPPaTport_IEsCls
(
Szt_ValueUlnkUEAssociatedLPPaTport_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueUlnkUEAssociatedLPPaTport_IEsCls(param, val, ptr, mBuf)
Szt_ValueUlnkUEAssociatedLPPaTport_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueUlnkUEAssociatedLPPaTport_IEsCls) 
	
	switch (val)
	{
		case Sztid_MME_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztMME_UE_S1AP_ID, &param->u.sztMME_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_eNB_UE_S1AP_ID:
			CMCHKUNPK(cmUnpkSztENB_UE_S1AP_ID, &param->u.sztENB_UE_S1AP_ID, mBuf); 
			break;
		case Sztid_Routing_ID:
			CMCHKUNPK(cmUnpkSztRouting_ID, &param->u.sztRouting_ID, mBuf); 
			break;
		case Sztid_LPPa_PDU:
			SZUCHKUNPKPTR(cmUnpkSztLPPa_PDU, &param->u.sztLPPa_PDU, ptr, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueUlnkUEAssociatedLPPaTport_IEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs
*  DESC: Function to Unpack SztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs
(
SztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs(param, ptr, mBuf)
SztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueUlnkUEAssociatedLPPaTport_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs */



/*
* FUN : cmUnpkSztProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs
*  DESC: Function to Unpack SztProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs
(
SztProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs(param, ptr, mBuf)
SztProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs */



/*
* FUN : cmUnpkSztUlnkUEAssociatedLPPaTport
*  DESC: Function to Unpack SztUlnkUEAssociatedLPPaTport structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztUlnkUEAssociatedLPPaTport
(
SztUlnkUEAssociatedLPPaTport *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztUlnkUEAssociatedLPPaTport(param, ptr, mBuf)
SztUlnkUEAssociatedLPPaTport *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztUlnkUEAssociatedLPPaTport) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_UlnkUEAssociatedLPPaTport_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztUlnkUEAssociatedLPPaTport */



/*
* FUN : cmUnpkSzt_ValueDlnkNonUEAssociatedLPPaTport_IEsCls
*  DESC: Function to Unpack Szt_ValueDlnkNonUEAssociatedLPPaTport_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueDlnkNonUEAssociatedLPPaTport_IEsCls
(
Szt_ValueDlnkNonUEAssociatedLPPaTport_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueDlnkNonUEAssociatedLPPaTport_IEsCls(param, val, ptr, mBuf)
Szt_ValueDlnkNonUEAssociatedLPPaTport_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueDlnkNonUEAssociatedLPPaTport_IEsCls) 
	
	switch (val)
	{
		case Sztid_Routing_ID:
			CMCHKUNPK(cmUnpkSztRouting_ID, &param->u.sztRouting_ID, mBuf); 
			break;
		case Sztid_LPPa_PDU:
			SZUCHKUNPKPTR(cmUnpkSztLPPa_PDU, &param->u.sztLPPa_PDU, ptr, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueDlnkNonUEAssociatedLPPaTport_IEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs
*  DESC: Function to Unpack SztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs
(
SztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs(param, ptr, mBuf)
SztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueDlnkNonUEAssociatedLPPaTport_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs */



/*
* FUN : cmUnpkSztProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs
*  DESC: Function to Unpack SztProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs
(
SztProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs(param, ptr, mBuf)
SztProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs */



/*
* FUN : cmUnpkSztDlnkNonUEAssociatedLPPaTport
*  DESC: Function to Unpack SztDlnkNonUEAssociatedLPPaTport structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztDlnkNonUEAssociatedLPPaTport
(
SztDlnkNonUEAssociatedLPPaTport *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztDlnkNonUEAssociatedLPPaTport(param, ptr, mBuf)
SztDlnkNonUEAssociatedLPPaTport *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztDlnkNonUEAssociatedLPPaTport) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_DlnkNonUEAssociatedLPPaTport_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztDlnkNonUEAssociatedLPPaTport */



/*
* FUN : cmUnpkSzt_ValueUlnkNonUEAssociatedLPPaTport_IEsCls
*  DESC: Function to Unpack Szt_ValueUlnkNonUEAssociatedLPPaTport_IEsCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_ValueUlnkNonUEAssociatedLPPaTport_IEsCls
(
Szt_ValueUlnkNonUEAssociatedLPPaTport_IEsCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_ValueUlnkNonUEAssociatedLPPaTport_IEsCls(param, val, ptr, mBuf)
Szt_ValueUlnkNonUEAssociatedLPPaTport_IEsCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_ValueUlnkNonUEAssociatedLPPaTport_IEsCls) 
	
	switch (val)
	{
		case Sztid_Routing_ID:
			CMCHKUNPK(cmUnpkSztRouting_ID, &param->u.sztRouting_ID, mBuf); 
			break;
		case Sztid_LPPa_PDU:
			SZUCHKUNPKPTR(cmUnpkSztLPPa_PDU, &param->u.sztLPPa_PDU, ptr, mBuf); 
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_ValueUlnkNonUEAssociatedLPPaTport_IEsCls */



/*
* FUN : cmUnpkSztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs
*  DESC: Function to Unpack SztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs
(
SztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs(param, ptr, mBuf)
SztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProtIE_ID, &param->id, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_ValueUlnkNonUEAssociatedLPPaTport_IEsCls(&param->value, param->id.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs */



/*
* FUN : cmUnpkSztProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs
*  DESC: Function to Unpack SztProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs
(
SztProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs(param, ptr, mBuf)
SztProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	Cntr i;
	TRC3(cmUnpkSztProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs) 
	
	CMCHKUNPK(cmUnpkTknU16, &param->noComp, mBuf); 
	if( param->noComp.pres != NOTPRSNT ) 
	{
		CMGETMBLK(ptr, sizeof(SztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs)*(param->noComp.val), (Ptr*)&(param->member) );
		for(i = 0; i < param->noComp.val; i++)
		{
			CMCHKUNPKPTR(cmUnpkSztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs, &(param->member[i]), ptr, mBuf); 
		}
	}
	return(ROK);
}	 /* End of function cmUnpkSztProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs */



/*
* FUN : cmUnpkSztUlnkNonUEAssociatedLPPaTport
*  DESC: Function to Unpack SztUlnkNonUEAssociatedLPPaTport structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztUlnkNonUEAssociatedLPPaTport
(
SztUlnkNonUEAssociatedLPPaTport *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztUlnkNonUEAssociatedLPPaTport(param, ptr, mBuf)
SztUlnkNonUEAssociatedLPPaTport *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztUlnkNonUEAssociatedLPPaTport) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPKPTR(cmUnpkSztProtIE_Cont_UlnkNonUEAssociatedLPPaTport_IEs, &param->protocolIEs, ptr, mBuf); 
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztUlnkNonUEAssociatedLPPaTport */



/*
* FUN : cmUnpkSzt_InitiatingMsgCls
*  DESC: Function to Unpack Szt_InitiatingMsgCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_InitiatingMsgCls
(
Szt_InitiatingMsgCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_InitiatingMsgCls(param, val, ptr, mBuf)
Szt_InitiatingMsgCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_InitiatingMsgCls) 
	
	switch (val)
	{
		case Sztid_HovrPrep:
			CMCHKUNPKPTR(cmUnpkSztHovrReqd, &param->u.sztHovrReqd, ptr, mBuf);
			break;
		case Sztid_HovrResourceAllocn:
			CMCHKUNPKPTR(cmUnpkSztHovrRqst, &param->u.sztHovrRqst, ptr, mBuf);
			break;
		case Sztid_PathSwRqst:
			CMCHKUNPKPTR(cmUnpkSztPathSwRqst, &param->u.sztPathSwRqst, ptr, mBuf);
			break;
		case Sztid_E_RABSetup:
			CMCHKUNPKPTR(cmUnpkSztE_RABSetupRqst, &param->u.sztE_RABSetupRqst, ptr, mBuf);
			break;
		case Sztid_E_RABMdfy:
			CMCHKUNPKPTR(cmUnpkSztE_RABMdfyRqst, &param->u.sztE_RABMdfyRqst, ptr, mBuf);
			break;
		case Sztid_E_RABRls:
			CMCHKUNPKPTR(cmUnpkSztE_RABRlsCmmd, &param->u.sztE_RABRlsCmmd, ptr, mBuf);
			break;
		case Sztid_InitCntxtSetup:
			CMCHKUNPKPTR(cmUnpkSztInitCntxtSetupRqst, &param->u.sztInitCntxtSetupRqst, ptr, mBuf);
			break;
		case Sztid_HovrCancel:
			CMCHKUNPKPTR(cmUnpkSztHovrCancel, &param->u.sztHovrCancel, ptr, mBuf);
			break;
		case Sztid_Kill:
			CMCHKUNPKPTR(cmUnpkSztKillRqst, &param->u.sztKillRqst, ptr, mBuf);
			break;
		case Sztid_Reset:
			CMCHKUNPKPTR(cmUnpkSztReset, &param->u.sztReset, ptr, mBuf);
			break;
		case Sztid_S1Setup:
			CMCHKUNPKPTR(cmUnpkSztS1SetupRqst, &param->u.sztS1SetupRqst, ptr, mBuf);
			break;
		case Sztid_UECntxtModification:
			CMCHKUNPKPTR(cmUnpkSztUECntxtModificationRqst, &param->u.sztUECntxtModificationRqst, ptr, mBuf);
			break;
		case Sztid_UECntxtRls:
			CMCHKUNPKPTR(cmUnpkSztUECntxtRlsCmmd, &param->u.sztUECntxtRlsCmmd, ptr, mBuf);
			break;
		case Sztid_ENBConfigUpd:
			CMCHKUNPKPTR(cmUnpkSztENBConfigUpd, &param->u.sztENBConfigUpd, ptr, mBuf);
			break;
		case Sztid_MMEConfigUpd:
			CMCHKUNPKPTR(cmUnpkSztMMEConfigUpd, &param->u.sztMMEConfigUpd, ptr, mBuf);
			break;
		case Sztid_WriteReplaceWarning:
			CMCHKUNPKPTR(cmUnpkSztWriteReplaceWarningRqst, &param->u.sztWriteReplaceWarningRqst, ptr, mBuf);
			break;
		case Sztid_UERadioCapbltyMatch:
			CMCHKUNPKPTR(cmUnpkSztUERadioCapbltyMatchRqst, &param->u.sztUERadioCapbltyMatchRqst, ptr, mBuf);
			break;
		case Sztid_HovrNotification:
			CMCHKUNPKPTR(cmUnpkSztHovrNtfy, &param->u.sztHovrNtfy, ptr, mBuf);
			break;
		case Sztid_E_RABRlsInd:
			CMCHKUNPKPTR(cmUnpkSztE_RABRlsInd, &param->u.sztE_RABRlsInd, ptr, mBuf);
			break;
		case Sztid_Pag:
			CMCHKUNPKPTR(cmUnpkSztPag, &param->u.sztPag, ptr, mBuf);
			break;
		case Sztid_downlinkNASTport:
			CMCHKUNPKPTR(cmUnpkSztDlnkNASTport, &param->u.sztDlnkNASTport, ptr, mBuf);
			break;
		case Sztid_initialUEMsg:
			CMCHKUNPKPTR(cmUnpkSztInitUEMsg, &param->u.sztInitUEMsg, ptr, mBuf);
			break;
		case Sztid_uplinkNASTport:
			CMCHKUNPKPTR(cmUnpkSztUlnkNASTport, &param->u.sztUlnkNASTport, ptr, mBuf);
			break;
		case Sztid_ErrInd:
			CMCHKUNPKPTR(cmUnpkSztErrInd, &param->u.sztErrInd, ptr, mBuf);
			break;
		case Sztid_NASNonDlvryInd:
			CMCHKUNPKPTR(cmUnpkSztNASNonDlvryInd, &param->u.sztNASNonDlvryInd, ptr, mBuf);
			break;
		case Sztid_UECntxtRlsRqst:
			CMCHKUNPKPTR(cmUnpkSztUECntxtRlsRqst, &param->u.sztUECntxtRlsRqst, ptr, mBuf);
			break;
		case Sztid_DlnkS1cdma2000tunneling:
			CMCHKUNPKPTR(cmUnpkSztDlnkS1cdma2000tunneling, &param->u.sztDlnkS1cdma2000tunneling, ptr, mBuf);
			break;
		case Sztid_UlnkS1cdma2000tunneling:
			CMCHKUNPKPTR(cmUnpkSztUlnkS1cdma2000tunneling, &param->u.sztUlnkS1cdma2000tunneling, ptr, mBuf);
			break;
		case Sztid_UECapbltyInfoInd:
			CMCHKUNPKPTR(cmUnpkSztUECapbltyInfoInd, &param->u.sztUECapbltyInfoInd, ptr, mBuf);
			break;
		case Sztid_eNBStatusTfr:
			CMCHKUNPKPTR(cmUnpkSztENBStatusTfr, &param->u.sztENBStatusTfr, ptr, mBuf);
			break;
		case Sztid_MMEStatusTfr:
			CMCHKUNPKPTR(cmUnpkSztMMEStatusTfr, &param->u.sztMMEStatusTfr, ptr, mBuf);
			break;
		case Sztid_DeactvTrace:
			CMCHKUNPKPTR(cmUnpkSztDeactvTrace, &param->u.sztDeactvTrace, ptr, mBuf);
			break;
		case Sztid_TraceStart:
			CMCHKUNPKPTR(cmUnpkSztTraceStart, &param->u.sztTraceStart, ptr, mBuf);
			break;
		case Sztid_TraceFailInd:
			CMCHKUNPKPTR(cmUnpkSztTraceFailInd, &param->u.sztTraceFailInd, ptr, mBuf);
			break;
		case Sztid_CellTrafficTrace:
			CMCHKUNPKPTR(cmUnpkSztCellTrafficTrace, &param->u.sztCellTrafficTrace, ptr, mBuf);
			break;
		case Sztid_LocRprtngCntrl:
			CMCHKUNPKPTR(cmUnpkSztLocRprtngCntrl, &param->u.sztLocRprtngCntrl, ptr, mBuf);
			break;
		case Sztid_LocRprtngFailInd:
			CMCHKUNPKPTR(cmUnpkSztLocRprtngFailInd, &param->u.sztLocRprtngFailInd, ptr, mBuf);
			break;
		case Sztid_LocReport:
			CMCHKUNPKPTR(cmUnpkSztLocReport, &param->u.sztLocReport, ptr, mBuf);
			break;
		case Sztid_OverloadStart:
			CMCHKUNPKPTR(cmUnpkSztOverloadStart, &param->u.sztOverloadStart, ptr, mBuf);
			break;
		case Sztid_OverloadStop:
			CMCHKUNPKPTR(cmUnpkSztOverloadStop, &param->u.sztOverloadStop, ptr, mBuf);
			break;
		case Sztid_eNBDirectInformTfr:
			CMCHKUNPKPTR(cmUnpkSztENBDirectInformTfr, &param->u.sztENBDirectInformTfr, ptr, mBuf);
			break;
		case Sztid_MMEDirectInformTfr:
			CMCHKUNPKPTR(cmUnpkSztMMEDirectInformTfr, &param->u.sztMMEDirectInformTfr, ptr, mBuf);
			break;
		case Sztid_eNBConfigTfr:
			CMCHKUNPKPTR(cmUnpkSztENBConfigTfr, &param->u.sztENBConfigTfr, ptr, mBuf);
			break;
		case Sztid_MMEConfigTfr:
			CMCHKUNPKPTR(cmUnpkSztMMEConfigTfr, &param->u.sztMMEConfigTfr, ptr, mBuf);
			break;
		case Sztid_PrivMsg:
			CMCHKUNPKPTR(cmUnpkSztPrivMsg, &param->u.sztPrivMsg, ptr, mBuf);
			break;
		case Sztid_downlinkUEAssociatedLPPaTport:
			CMCHKUNPKPTR(cmUnpkSztDlnkUEAssociatedLPPaTport, &param->u.sztDlnkUEAssociatedLPPaTport, ptr, mBuf);
			break;
		case Sztid_uplinkUEAssociatedLPPaTport:
			CMCHKUNPKPTR(cmUnpkSztUlnkUEAssociatedLPPaTport, &param->u.sztUlnkUEAssociatedLPPaTport, ptr, mBuf);
			break;
		case Sztid_downlinkNonUEAssociatedLPPaTport:
			CMCHKUNPKPTR(cmUnpkSztDlnkNonUEAssociatedLPPaTport, &param->u.sztDlnkNonUEAssociatedLPPaTport, ptr, mBuf);
			break;
		case Sztid_uplinkNonUEAssociatedLPPaTport:
			CMCHKUNPKPTR(cmUnpkSztUlnkNonUEAssociatedLPPaTport, &param->u.sztUlnkNonUEAssociatedLPPaTport, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_InitiatingMsgCls */



/*
* FUN : cmUnpkSztInitiatingMsg
*  DESC: Function to Unpack SztInitiatingMsg structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztInitiatingMsg
(
SztInitiatingMsg *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztInitiatingMsg(param, ptr, mBuf)
SztInitiatingMsg *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztInitiatingMsg) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProcedureCode, &param->procedureCode, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_InitiatingMsgCls(&param->value, param->procedureCode.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztInitiatingMsg */



/*
* FUN : cmUnpkSzt_SuccessfulOutcomeCls
*  DESC: Function to Unpack Szt_SuccessfulOutcomeCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_SuccessfulOutcomeCls
(
Szt_SuccessfulOutcomeCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_SuccessfulOutcomeCls(param, val, ptr, mBuf)
Szt_SuccessfulOutcomeCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_SuccessfulOutcomeCls) 
	
	switch (val)
	{
		case Sztid_HovrPrep:
			CMCHKUNPKPTR(cmUnpkSztHovrCmmd, &param->u.sztHovrCmmd, ptr, mBuf);
			break;
		case Sztid_HovrResourceAllocn:
			CMCHKUNPKPTR(cmUnpkSztHovrRqstAckg, &param->u.sztHovrRqstAckg, ptr, mBuf);
			break;
		case Sztid_PathSwRqst:
			CMCHKUNPKPTR(cmUnpkSztPathSwRqstAckg, &param->u.sztPathSwRqstAckg, ptr, mBuf);
			break;
		case Sztid_E_RABSetup:
			CMCHKUNPKPTR(cmUnpkSztE_RABSetupResp, &param->u.sztE_RABSetupResp, ptr, mBuf);
			break;
		case Sztid_E_RABMdfy:
			CMCHKUNPKPTR(cmUnpkSztE_RABMdfyResp, &param->u.sztE_RABMdfyResp, ptr, mBuf);
			break;
		case Sztid_E_RABRls:
			CMCHKUNPKPTR(cmUnpkSztE_RABRlsResp, &param->u.sztE_RABRlsResp, ptr, mBuf);
			break;
		case Sztid_InitCntxtSetup:
			CMCHKUNPKPTR(cmUnpkSztInitCntxtSetupResp, &param->u.sztInitCntxtSetupResp, ptr, mBuf);
			break;
		case Sztid_HovrCancel:
			CMCHKUNPKPTR(cmUnpkSztHovrCancelAckg, &param->u.sztHovrCancelAckg, ptr, mBuf);
			break;
		case Sztid_Kill:
			CMCHKUNPKPTR(cmUnpkSztKillResp, &param->u.sztKillResp, ptr, mBuf);
			break;
		case Sztid_Reset:
			CMCHKUNPKPTR(cmUnpkSztResetAckg, &param->u.sztResetAckg, ptr, mBuf);
			break;
		case Sztid_S1Setup:
			CMCHKUNPKPTR(cmUnpkSztS1SetupResp, &param->u.sztS1SetupResp, ptr, mBuf);
			break;
		case Sztid_UECntxtModification:
			CMCHKUNPKPTR(cmUnpkSztUECntxtModificationResp, &param->u.sztUECntxtModificationResp, ptr, mBuf);
			break;
		case Sztid_UECntxtRls:
			CMCHKUNPKPTR(cmUnpkSztUECntxtRlsComplete, &param->u.sztUECntxtRlsComplete, ptr, mBuf);
			break;
		case Sztid_ENBConfigUpd:
			CMCHKUNPKPTR(cmUnpkSztENBConfigUpdAckg, &param->u.sztENBConfigUpdAckg, ptr, mBuf);
			break;
		case Sztid_MMEConfigUpd:
			CMCHKUNPKPTR(cmUnpkSztMMEConfigUpdAckg, &param->u.sztMMEConfigUpdAckg, ptr, mBuf);
			break;
		case Sztid_WriteReplaceWarning:
			CMCHKUNPKPTR(cmUnpkSztWriteReplaceWarningResp, &param->u.sztWriteReplaceWarningResp, ptr, mBuf);
			break;
		case Sztid_UERadioCapbltyMatch:
			CMCHKUNPKPTR(cmUnpkSztUERadioCapbltyMatchResp, &param->u.sztUERadioCapbltyMatchResp, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_SuccessfulOutcomeCls */



/*
* FUN : cmUnpkSztSuccessfulOutcome
*  DESC: Function to Unpack SztSuccessfulOutcome structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztSuccessfulOutcome
(
SztSuccessfulOutcome *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztSuccessfulOutcome(param, ptr, mBuf)
SztSuccessfulOutcome *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztSuccessfulOutcome) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProcedureCode, &param->procedureCode, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_SuccessfulOutcomeCls(&param->value, param->procedureCode.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztSuccessfulOutcome */



/*
* FUN : cmUnpkSzt_UnsuccessfulOutcomeCls
*  DESC: Function to Unpack Szt_UnsuccessfulOutcomeCls structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSzt_UnsuccessfulOutcomeCls
(
Szt_UnsuccessfulOutcomeCls *param,
U32 val,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSzt_UnsuccessfulOutcomeCls(param, val, ptr, mBuf)
Szt_UnsuccessfulOutcomeCls *param;
U32 val;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSzt_UnsuccessfulOutcomeCls) 
	
	switch (val)
	{
		case Sztid_HovrPrep:
			CMCHKUNPKPTR(cmUnpkSztHovrPrepFail, &param->u.sztHovrPrepFail, ptr, mBuf);
			break;
		case Sztid_HovrResourceAllocn:
			CMCHKUNPKPTR(cmUnpkSztHovrFail, &param->u.sztHovrFail, ptr, mBuf);
			break;
		case Sztid_PathSwRqst:
			CMCHKUNPKPTR(cmUnpkSztPathSwRqstFail, &param->u.sztPathSwRqstFail, ptr, mBuf);
			break;
		case Sztid_InitCntxtSetup:
			CMCHKUNPKPTR(cmUnpkSztInitCntxtSetupFail, &param->u.sztInitCntxtSetupFail, ptr, mBuf);
			break;
		case Sztid_S1Setup:
			CMCHKUNPKPTR(cmUnpkSztS1SetupFail, &param->u.sztS1SetupFail, ptr, mBuf);
			break;
		case Sztid_UECntxtModification:
			CMCHKUNPKPTR(cmUnpkSztUECntxtModificationFail, &param->u.sztUECntxtModificationFail, ptr, mBuf);
			break;
		case Sztid_ENBConfigUpd:
			CMCHKUNPKPTR(cmUnpkSztENBConfigUpdFail, &param->u.sztENBConfigUpdFail, ptr, mBuf);
			break;
		case Sztid_MMEConfigUpd:
			CMCHKUNPKPTR(cmUnpkSztMMEConfigUpdFail, &param->u.sztMMEConfigUpdFail, ptr, mBuf);
			break;
		default:
		RETVALUE(ROK);
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSzt_UnsuccessfulOutcomeCls */



/*
* FUN : cmUnpkSztUnsuccessfulOutcome
*  DESC: Function to Unpack SztUnsuccessfulOutcome structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztUnsuccessfulOutcome
(
SztUnsuccessfulOutcome *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztUnsuccessfulOutcome(param, ptr, mBuf)
SztUnsuccessfulOutcome *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztUnsuccessfulOutcome) 
	
	CMCHKUNPK( cmUnpkTknPres, &param->pres, mBuf); 
	if( param->pres.pres != NOTPRSNT ) 
	{
		CMCHKUNPK(cmUnpkSztProcedureCode, &param->procedureCode, mBuf); 
		CMCHKUNPK(cmUnpkSztCriticality, &param->criticality, mBuf); 
		{
			S16 ret;
			ret = cmUnpkSzt_UnsuccessfulOutcomeCls(&param->value, param->procedureCode.val, ptr, mBuf);
			if (ret != ROK)
				RETVALUE(RFAILED);
		}
	}
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztUnsuccessfulOutcome */



/*
* FUN : cmUnpkSztS1AP_PDU
*  DESC: Function to Unpack SztS1AP_PDU structure 
* RETURN: ROK - OK
*/ 
#ifdef ANSI 
PUBLIC S16 cmUnpkSztS1AP_PDU
(
SztS1AP_PDU *param,
Ptr ptr,
Buffer *mBuf
)
#else 
PUBLIC S16 cmUnpkSztS1AP_PDU(param, ptr, mBuf)
SztS1AP_PDU *param;
Ptr ptr; 
Buffer *mBuf;
#endif
{
	
	TRC3(cmUnpkSztS1AP_PDU) 
	
	CMCHKUNPK(cmUnpkTknU8, &param->choice, mBuf); 
	if(param->choice.pres) 
	{
		switch( param->choice.val ) 
		{
			case S1AP_PDU_INITIATINGMSG :
				CMCHKUNPKPTR(cmUnpkSztInitiatingMsg, &param->val.initiatingMsg, ptr, mBuf); 
				break;
			case S1AP_PDU_SUCCESSFULOUTCOME :
				CMCHKUNPKPTR(cmUnpkSztSuccessfulOutcome, &param->val.successfulOutcome, ptr, mBuf); 
				break;
			case S1AP_PDU_UNSUCCESSFULOUTCOME :
				CMCHKUNPKPTR(cmUnpkSztUnsuccessfulOutcome, &param->val.unsuccessfulOutcome, ptr, mBuf); 
				break;
			default:
				RETVALUE(RFAILED); 
		} 
	} 
	RETVALUE(ROK);
}	 /* End of function cmUnpkSztS1AP_PDU */
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
