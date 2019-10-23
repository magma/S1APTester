
/**********************************************************************

     Name:     S1AP Layer

     Type:     C source file

     Desc:     C source code for DB

     File:     sq_3gdb.c

     Sid:

     Prg:      akaranth 

**********************************************************************/

/* sz008.301: Support for Source RNC to Target RNC TC Enc/Dec. */

#include "envopt.h"           /* environment options */
#ifdef SZTV3
#include "envdep.h"           /* environment dependent */
#include "envind.h"           /* environment independent */
#include "gen.h"              /* general layer */
#include "ssi.h"              /* system services */
#include "cm_mblk.h"
#include "cm_tkns.h"
#include "cm_hash.h"
#include "cm_pasn.h"          /* common defines for ASN */
#include "cm5.h"

#include "cm_tpt.h"
#include "sct.h"
#include "cm_inet.h"
#include "szt.h"
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_pftha.h"
#include "cm_psf.h"
#include "sht.h"           /* System Agent */
#endif /* SZ_FTHA */
#ifndef SZ_ENC_DEC
#include "lsz.h"
#endif
#include "sz.h"

/* header/extern include files (.x) */
#include "cm_llist.h"         /* */
#include "cm_hash.h"
#include "cm_umts.h"
#include "gen.x"              /* general layer */
#include "ssi.x"              /* system services */
#include "cm5.x"              /* */
#include "cm_tkns.x"          /* */
#include "cm_mblk.x"
#include "cm_llist.x"
#include "cm_hash.x"
#include "cm_umts.x"
#include "cm_pasn.x"          /* PASN */
#include "szt_asn.x"
#include "szt_asn.h"
#include "szt_3gasn.h"
#include "szt_3gasn.x"
#include "cm_inet.x"
#include "cm_tpt.x"
#include "sct.x"
#include "szt.x"
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_pftha.x"
#include "cm_psf.x"
#include "sht.x"           /* System Agent */
#endif /* SZ_FTHA */
#ifndef SZ_ENC_DEC
#include "lsz.x"
#include "sz.x"
#else
#include "sz_encdec.x"
#endif /* SZ_ENC_DEC */


#ifdef SZ_ACC_TST_ESC_FUNC
PRIVATE  U32 flagSz3O = CM_PASN_ELM_OPT | CM_PASN_POST_DECODE_ESC_CALL;
PRIVATE  U32 flagSz3M = CM_PASN_ELM_MAND | CM_PASN_POST_DECODE_ESC_CALL;
#else
PRIVATE  U32 flagSz3O = CM_PASN_ELM_OPT | CM_PASN_PRE_ENCODE_ESC_CALL |CM_PASN_POST_DECODE_ESC_CALL;
PRIVATE  U32 flagSz3M = CM_PASN_ELM_MAND | CM_PASN_PRE_ENCODE_ESC_CALL | CM_PASN_POST_DECODE_ESC_CALL;
#endif



CmPAsnElmDef sz3gConstTerm =
{
#ifdef CM_PASN_DBG
   " sz3gConstTerm (Set-Sequence Terminator) ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SETSEQ_TERM,
   CM_PASN_EXT_MKR_ABS,
   0,
   &flagSz3M,    
   CM_PASN_ESC_FUNC_NULLP,
   NULLP 
};

CmPAsnOctStrDef sz3gRRC_Contspec =
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
	0,
	CM_PASN_PLUS_INF
};
CmPAsnElmDef sz3gRRC_Cont =
{
#ifdef CM_PASN_DBG
	" sz3gRRC_Cont " ,
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_OCTSTRXL,
	CM_PASN_EXT_MKR_ABS,
	sizeof(SztRRC_Cont),
	&flagSz3M,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *) (&sz3gRRC_Contspec),
	NULLP
};

/* Element ----- NumberOfIuInstances ------- */
CmPAsnUIntDef sz3gNumberOfIuInstancesspec =
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
	1,
	2UL
};
CmPAsnElmDef sz3gNumberOfIuInstances =
{
#ifdef CM_PASN_DBG
	" sz3gNumberOfIuInstances ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_UINT32,
	CM_PASN_EXT_MKR_ABS,
	sizeof(SztNumberOfIuInstances),
	&flagSz3M,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *)(&sz3gNumberOfIuInstancesspec),
	NULLP
};

/* Element ----- RelocationType ------- */
CmPAsnTknEnum sz3gRelocationTypLst[3] =
{
   2,
   SztRelocationTypue_not_involvedEnum,
   SztRelocationTypue_involvedEnum
};
CmPAsnEnumDef sz3gRelocationTypspec =
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
	sz3gRelocationTypLst,
	NULLP
};
CmPAsnElmDef sz3gRelocationTyp =
{
#ifdef CM_PASN_DBG
	" sz3gRelocationTyp ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_ENUM,
	CM_PASN_EXT_MKR_PRES,
	sizeof(SztRelocationTyp),
	&flagSz3M,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *)(&sz3gRelocationTypspec),
	NULLP
};

CmPAsnBitStrDef sz3gIntegrityProtectionKeyspec =
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_BITSTRXL,
#endif /* CM_PASN_DEBUG */
	128,
	128
};
CmPAsnElmDef sz3gOptIntegrityProtectionKey =
{
#ifdef CM_PASN_DBG
	" sz3gIntegrityProtectionKey ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_BITSTRXL,
	CM_PASN_EXT_MKR_ABS,
	sizeof(SztIntegrityProtectionKey),
	&flagSz3O,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *) (&sz3gIntegrityProtectionKeyspec),
	NULLP
};

CmPAsnBitStrDef sz3gEncryptionKeyspec =
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_BITSTRXL,
#endif /* CM_PASN_DEBUG */
	128,
	128
};
CmPAsnElmDef sz3gOptEncryptionKey =
{
#ifdef CM_PASN_DBG
	" sz3gEncryptionKey ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_BITSTRXL,
	CM_PASN_EXT_MKR_ABS,
	sizeof(SztEncryptionKey),
	&flagSz3O,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *) (&sz3gEncryptionKeyspec),
	NULLP
};


/* Element ----- D-RNTI ------- */
CmPAsnUIntDef sz3gD_RNTIspec =
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
	0,
	1048575UL
};
CmPAsnElmDef sz3gOptD_RNTI =
{
#ifdef CM_PASN_DBG
	" sz3gD_RNTI ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_UINT32,
	CM_PASN_EXT_MKR_ABS,
	sizeof(SztD_RNTI),
	&flagSz3O,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *)(&sz3gD_RNTIspec),
	NULLP
};

/* Element ----- TargetCellId ------- */
CmPAsnUIntDef sz3gTgetCellIdspec =
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
	0,
	268435455UL
};

CmPAsnElmDef sz3gOptTgetCellId =
{
#ifdef CM_PASN_DBG
	" sz3gTgetCellId ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_UINT32,
	CM_PASN_EXT_MKR_ABS,
	sizeof(SztTgetCellId),
	&flagSz3O,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *)(&sz3gTgetCellIdspec),
	NULLP
};
CmPAsnSetSeqOfDef sz3gRAB_TrCH_Mappingspec =
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
	1,        /* start of the size */
	SztmaxNrOfRABs,        /* start of the size */
	3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef sz3gOptRAB_TrCH_Mapping =
{
#ifdef CM_PASN_DBG
	" sz3gRAB_TrCH_Mapping ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_SEQOF,
	CM_PASN_EXT_MKR_ABS,
	sizeof(SztRAB_TrCH_Mapping),
	&flagSz3O,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *) (&sz3gRAB_TrCH_Mappingspec),
	NULLP
};
CmPAsnBitStrDef sz3gRAB_IDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_BITSTR,
#endif /* CM_PASN_DEBUG */
   8,
   8
};
CmPAsnElmDef sz3gRAB_ID =
{
#ifdef CM_PASN_DBG
   " sz3gRAB_ID ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_BITSTR,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztRAB_ID),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&sz3gRAB_IDspec),
   NULLP
};
/* Element ----- DCH-ID ------- */
CmPAsnUIntDef sz3gDCH_IDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
   0,
   255UL
};
CmPAsnElmDef sz3gOptDCH_ID =
{
#ifdef CM_PASN_DBG
   " sz3gDCH_ID ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztDCH_ID),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3gDCH_IDspec),
   NULLP
};
/* Element ----- DSCH-ID ------- */
CmPAsnUIntDef sz3gDSCH_IDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
   0,
   255UL
};

CmPAsnElmDef sz3gOptDSCH_ID =
{
#ifdef CM_PASN_DBG
   " sz3gDSCH_ID ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztDSCH_ID),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3gDSCH_IDspec),
   NULLP
};

/* Element ----- USCH-ID ------- */
CmPAsnUIntDef sz3gUSCH_IDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
   0,
   255UL
};
CmPAsnElmDef sz3gOptUSCH_ID =
{
#ifdef CM_PASN_DBG
   " sz3gUSCH_ID ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztUSCH_ID),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3gUSCH_IDspec),
   NULLP
};
CmPAsnSetSeqOfDef sz3gProtExtnCont_TrCH_ID_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef sz3gOptProtExtnCont_TrCH_ID_ExtIEs =
{
#ifdef CM_PASN_DBG
   " sz3gProtExtnCont_TrCH_ID_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_TrCH_ID_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&sz3gProtExtnCont_TrCH_ID_ExtIEsspec),
   NULLP
};



/* --------- */

/* Element ----- ProtocolExtensionID ------- */
CmPAsnUIntDef sz3gProtExtnIDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
   0,
   65535UL
};
CmPAsnElmDef sz3gProtExtnID =
{
#ifdef CM_PASN_DBG
   " sz3gProtExtnID ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnID),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3gProtExtnIDspec),
   NULLP
};
/* Element ----- Criticality ------- */
CmPAsnTknEnum sz3gCriticalityLst[4] =
{
   3,
   SztCriticalityrejectEnum,
   SztCriticalityignoreEnum,
   SztCriticalitynotifyEnum
};
CmPAsnEnumDef sz3gCriticalityspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   sz3gCriticalityLst,
   NULLP
};
CmPAsnElmDef sz3gCriticality =
{
#ifdef CM_PASN_DBG
   " sz3gCriticality ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztCriticality),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3gCriticalityspec),
   NULLP
};
/* Element ----- HS-DSCH-MAC-d-Flow-ID ------- */
CmPAsnUIntDef sz3gHS_DSCH_MAC_d_Flow_IDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
   0,
   149245488UL
};
CmPAsnElmDef sz3gHS_DSCH_MAC_d_Flow_ID =
{
#ifdef CM_PASN_DBG
   " sz3gHS_DSCH_MAC_d_Flow_ID ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztHS_DSCH_MAC_d_Flow_ID),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3gHS_DSCH_MAC_d_Flow_IDspec),
   NULLP
};
/* Element ----- E-DCH-MAC-d-Flow-ID ------- */
CmPAsnUIntDef sz3gE_DCH_MAC_d_Flow_IDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
   0,
   149198968UL
};
CmPAsnElmDef sz3gE_DCH_MAC_d_Flow_ID =
{
#ifdef CM_PASN_DBG
   " sz3gE_DCH_MAC_d_Flow_ID ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztE_DCH_MAC_d_Flow_ID),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3gE_DCH_MAC_d_Flow_IDspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz3g_ExtnTrCH_ID_ExtIEsClsInst[] =
{
   &sz3gHS_DSCH_MAC_d_Flow_ID,
   &sz3gE_DCH_MAC_d_Flow_ID
};
PUBLIC U32 sz3g_ExtnTrCH_ID_ExtIEsClsInstId[] =
{
   Sztid_hS_DSCH_MAC_d_Flow_ID,
   Sztid_E_DCH_MAC_d_Flow_ID
};
PUBLIC CmPAsnClassInfo sz3g_ExtnTrCH_ID_ExtIEsClsInfo =
{
   2,
   &sz3g_ExtnTrCH_ID_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz3g_ExtnTrCH_ID_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz3g_ExtnTrCH_ID_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz3g_ExtnTrCH_ID_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};

PUBLIC CmPAsnElmDef sz3g_ExtnTrCH_ID_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz3g_ExtnTrCH_ID_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnTrCH_ID_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3g_ExtnTrCH_ID_ExtIEsClsSpec)
};
PUBLIC CmPAsnElmDef *sz3gProtExtnField_TrCH_ID_ExtIEsTkn[] =
{
   &sz3gProtExtnID,
   &sz3gCriticality,
   &sz3g_ExtnTrCH_ID_ExtIEsCls,
   &sz3gConstTerm
};
CmPAsnSetSeqDef sz3gProtExtnField_TrCH_ID_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &sz3gProtExtnField_TrCH_ID_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef sz3gProtExtnField_TrCH_ID_ExtIEs =
{
#ifdef CM_PASN_DBG
   " sz3gProtExtnField_TrCH_ID_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_TrCH_ID_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3gProtExtnField_TrCH_ID_ExtIEsspec),
   NULLP
};
CmPAsnElmDef sz3gExtMkr =
{
#ifdef CM_PASN_DBG
   " sz3gExtMkr(Extension Marker) ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_EXT_MKR,
   CM_PASN_EXT_MKR_ABS,
   0,
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   NULLP
};
PUBLIC CmPAsnElmDef *sz3gTrCH_IDTkn[] =
{
   &sz3gOptDCH_ID,
   &sz3gOptDSCH_ID,
   &sz3gOptUSCH_ID,
   &sz3gOptProtExtnCont_TrCH_ID_ExtIEs,
   &sz3gProtExtnField_TrCH_ID_ExtIEs,
   &sz3gConstTerm,
   &sz3gExtMkr,
   &sz3gConstTerm
};
CmPAsnSetSeqDef sz3gTrCH_IDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   4,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &sz3gTrCH_IDTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef sz3gTrCH_ID =
{
#ifdef CM_PASN_DBG
   " sz3gTrCH_ID ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztTrCH_ID),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3gTrCH_IDspec),
   NULLP
};
CmPAsnSetSeqOfDef sz3gTrCH_ID_Lstspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxRAB_Subflows,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef sz3gTrCH_ID_Lst =
{
#ifdef CM_PASN_DBG
   " sz3gTrCH_ID_Lst ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztTrCH_ID_Lst),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&sz3gTrCH_ID_Lstspec),
   NULLP
};
CmPAsnSetSeqOfDef sz3gProtExtnCont_RAB_TrCH_MappingItem_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef sz3gOptProtExtnCont_RAB_TrCH_MappingItem_ExtIEs =
{
#ifdef CM_PASN_DBG
   " sz3gProtExtnCont_RAB_TrCH_MappingItem_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_RAB_TrCH_MappingItem_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&sz3gProtExtnCont_RAB_TrCH_MappingItem_ExtIEsspec),
   NULLP
};
CmPAsnTknEnum sz3gCN_DomainIndicatorLst[3] =
{
   2,
   SztCN_DomainIndicatorcs_domainEnum,
   SztCN_DomainIndicatorps_domainEnum
};
CmPAsnEnumDef sz3gCN_DomainIndicatorspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   sz3gCN_DomainIndicatorLst,
   NULLP
};
CmPAsnElmDef sz3gCN_DomainIndicator =
{
#ifdef CM_PASN_DBG
   " sz3gCN_DomainIndicator ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztCN_DomainIndicator),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3gCN_DomainIndicatorspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz3g_ExtnRAB_TrCH_MappingItem_ExtIEsClsInst[] =
{
      &sz3gCN_DomainIndicator
};
PUBLIC U32 sz3g_ExtnRAB_TrCH_MappingItem_ExtIEsClsInstId[] =
{
   Sztid_CN_DomainIndicator
};
PUBLIC CmPAsnClassInfo sz3g_ExtnRAB_TrCH_MappingItem_ExtIEsClsInfo =
{
   1,
   &sz3g_ExtnRAB_TrCH_MappingItem_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz3g_ExtnRAB_TrCH_MappingItem_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz3g_ExtnRAB_TrCH_MappingItem_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz3g_ExtnRAB_TrCH_MappingItem_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz3g_ExtnRAB_TrCH_MappingItem_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz3g_ExtnRAB_TrCH_MappingItem_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnRAB_TrCH_MappingItem_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3g_ExtnRAB_TrCH_MappingItem_ExtIEsClsSpec)
};
PUBLIC CmPAsnElmDef *sz3gProtExtnField_RAB_TrCH_MappingItem_ExtIEsTkn[] =
{
   &sz3gProtExtnID,
   &sz3gCriticality,
   &sz3g_ExtnRAB_TrCH_MappingItem_ExtIEsCls,
   &sz3gConstTerm
};
CmPAsnSetSeqDef sz3gProtExtnField_RAB_TrCH_MappingItem_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &sz3gProtExtnField_RAB_TrCH_MappingItem_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef sz3gProtExtnField_RAB_TrCH_MappingItem_ExtIEs =
{
#ifdef CM_PASN_DBG
   " sz3gProtExtnField_RAB_TrCH_MappingItem_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_RAB_TrCH_MappingItem_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3gProtExtnField_RAB_TrCH_MappingItem_ExtIEsspec),
   NULLP
};

PUBLIC CmPAsnElmDef *sz3gRAB_TrCH_MappingItemTkn[] =
{
   &sz3gRAB_ID,
   &sz3gTrCH_ID_Lst,
   &sz3gTrCH_ID,
   &sz3gConstTerm,
   &sz3gOptProtExtnCont_RAB_TrCH_MappingItem_ExtIEs,
   &sz3gProtExtnField_RAB_TrCH_MappingItem_ExtIEs,
   &sz3gConstTerm,
   &sz3gExtMkr,
   &sz3gConstTerm
};

CmPAsnSetSeqDef sz3gRAB_TrCH_MappingItemspec =
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
	1,      /* number of optional elements */
	0,      /* number of extension elements */
	NULLP, /* not supported yet */
	NULLP, /* not supported yet */
	&sz3gRAB_TrCH_MappingItemTkn[0], /* ptr to first token*/
	FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef sz3gRAB_TrCH_MappingItem =
{
#ifdef CM_PASN_DBG
	" sz3gRAB_TrCH_MappingItem ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_SEQ,
	CM_PASN_EXT_MKR_PRES,
	sizeof(SztRAB_TrCH_MappingItem),
	&flagSz3M,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *)(&sz3gRAB_TrCH_MappingItemspec),
	NULLP
};
CmPAsnSetSeqOfDef sz3gProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef sz3gOptProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEs =
{
#ifdef CM_PASN_DBG
	" sz3gProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEs ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_SEQOF,
	CM_PASN_EXT_MKR_ABS,
	sizeof(SztProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEs),
	&flagSz3O,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *) (&sz3gProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEsspec),
	NULLP
};
CmPAsnSetSeqOfDef sz3gSRB_TrCH_Mappingspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxNrOfSRBs,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef sz3gSRB_TrCH_Mapping =
{
#ifdef CM_PASN_DBG
   " sz3gSRB_TrCH_Mapping ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztSRB_TrCH_Mapping),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&sz3gSRB_TrCH_Mappingspec),
   NULLP
};
/* Element ----- SRB-ID ------- */
CmPAsnUIntDef sz3gSRB_IDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
   1,
   32UL
};
CmPAsnElmDef sz3gSRB_ID =
{
#ifdef CM_PASN_DBG
   " sz3gSRB_ID ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztSRB_ID),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3gSRB_IDspec),
   NULLP
};
CmPAsnSetSeqOfDef sz3gProtExtnCont_SRB_TrCH_MappingItem_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef sz3gOptProtExtnCont_SRB_TrCH_MappingItem_ExtIEs =
{
#ifdef CM_PASN_DBG
   " sz3gProtExtnCont_SRB_TrCH_MappingItem_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_SRB_TrCH_MappingItem_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&sz3gProtExtnCont_SRB_TrCH_MappingItem_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz3g_ExtnSRB_TrCH_MappingItem_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz3g_ExtnSRB_TrCH_MappingItem_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz3g_ExtnSRB_TrCH_MappingItem_ExtIEsClsInfo =
{
   0,
   &sz3g_ExtnSRB_TrCH_MappingItem_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz3g_ExtnSRB_TrCH_MappingItem_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz3g_ExtnSRB_TrCH_MappingItem_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz3g_ExtnSRB_TrCH_MappingItem_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz3g_ExtnSRB_TrCH_MappingItem_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz3g_ExtnSRB_TrCH_MappingItem_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnSRB_TrCH_MappingItem_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3g_ExtnSRB_TrCH_MappingItem_ExtIEsClsSpec)
};
PUBLIC CmPAsnElmDef *sz3gProtExtnField_SRB_TrCH_MappingItem_ExtIEsTkn[] =
{
   &sz3gProtExtnID,
   &sz3gCriticality,
   &sz3g_ExtnSRB_TrCH_MappingItem_ExtIEsCls,
   &sz3gConstTerm
};
CmPAsnSetSeqDef sz3gProtExtnField_SRB_TrCH_MappingItem_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &sz3gProtExtnField_SRB_TrCH_MappingItem_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef sz3gProtExtnField_SRB_TrCH_MappingItem_ExtIEs =
{
#ifdef CM_PASN_DBG
   " sz3gProtExtnField_SRB_TrCH_MappingItem_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_SRB_TrCH_MappingItem_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3gProtExtnField_SRB_TrCH_MappingItem_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz3gSRB_TrCH_MappingItemTkn[] =
{
   &sz3gSRB_ID,
   &sz3gTrCH_ID,
   &sz3gOptProtExtnCont_SRB_TrCH_MappingItem_ExtIEs,
   &sz3gProtExtnField_SRB_TrCH_MappingItem_ExtIEs,
   &sz3gConstTerm,
   &sz3gExtMkr,
   &sz3gConstTerm
};
CmPAsnSetSeqDef sz3gSRB_TrCH_MappingItemspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &sz3gSRB_TrCH_MappingItemTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef sz3gSRB_TrCH_MappingItem =
{
#ifdef CM_PASN_DBG
   " sz3gSRB_TrCH_MappingItem ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztSRB_TrCH_MappingItem),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3gSRB_TrCH_MappingItemspec),
   NULLP
};
CmPAsnElmDef sz3gTgetCellId =
{
#ifdef CM_PASN_DBG
   " sz3gTgetCellId ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztTgetCellId),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3gTgetCellIdspec),
   NULLP
};
CmPAsnSetSeqOfDef sz3gProtExtnCont_SrcUTRANCellID_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef sz3gOptProtExtnCont_SrcUTRANCellID_ExtIEs =
{
#ifdef CM_PASN_DBG
   " sz3gProtExtnCont_SrcUTRANCellID_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_SrcUTRANCellID_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&sz3gProtExtnCont_SrcUTRANCellID_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz3g_ExtnSrcUTRANCellID_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz3g_ExtnSrcUTRANCellID_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz3g_ExtnSrcUTRANCellID_ExtIEsClsInfo =
{
   0,
   &sz3g_ExtnSrcUTRANCellID_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz3g_ExtnSrcUTRANCellID_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz3g_ExtnSrcUTRANCellID_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz3g_ExtnSrcUTRANCellID_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz3g_ExtnSrcUTRANCellID_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz3g_ExtnSrcUTRANCellID_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnSrcUTRANCellID_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3g_ExtnSrcUTRANCellID_ExtIEsClsSpec)
};
PUBLIC CmPAsnElmDef *sz3gProtExtnField_SrcUTRANCellID_ExtIEsTkn[] =
{
   &sz3gProtExtnID,
   &sz3gCriticality,
   &sz3g_ExtnSrcUTRANCellID_ExtIEsCls,
   &sz3gConstTerm
};
CmPAsnSetSeqDef sz3gProtExtnField_SrcUTRANCellID_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &sz3gProtExtnField_SrcUTRANCellID_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef sz3gProtExtnField_SrcUTRANCellID_ExtIEs =
{
#ifdef CM_PASN_DBG
   " sz3gProtExtnField_SrcUTRANCellID_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_SrcUTRANCellID_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3gProtExtnField_SrcUTRANCellID_ExtIEsspec),
   NULLP
};
CmPAsnOctStrDef sz3gTBCD_STRINGspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
    3,
    3
};
CmPAsnElmDef sz3gTBCD_STRING =
{
#ifdef CM_PASN_DBG
   " sz3gTBCD_STRING " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztTBCD_STRING),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&sz3gTBCD_STRINGspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz3gSrcUTRANCellIDTkn[] =
{
   &sz3gTBCD_STRING,
   &sz3gTgetCellId,
   &sz3gOptProtExtnCont_SrcUTRANCellID_ExtIEs,
   &sz3gProtExtnField_SrcUTRANCellID_ExtIEs,
   &sz3gConstTerm,
   &sz3gConstTerm
};
CmPAsnSetSeqDef sz3gSrcUTRANCellIDspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &sz3gSrcUTRANCellIDTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef sz3gSrcUTRANCellID =
{
#ifdef CM_PASN_DBG
	" sz3gSrcUTRANCellID ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_SEQ,
	CM_PASN_EXT_MKR_ABS,
	sizeof(SztSrcUTRANCellID),
	&flagSz3M,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *)(&sz3gSrcUTRANCellIDspec),
	NULLP
};
CmPAsnOctStrDef sz3gCIspec =
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_OCTSTR,
#endif /* CM_PASN_DEBUG */
	2,
	2
};
CmPAsnElmDef sz3gCI =
{
#ifdef CM_PASN_DBG
	" sz3gCI " ,
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_OCTSTR,
	CM_PASN_EXT_MKR_ABS,
	sizeof(SztCI),
	&flagSz3M,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *) (&sz3gCIspec),
	NULLP
};
CmPAsnOctStrDef sz3gRACspec =
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_OCTSTR,
#endif /* CM_PASN_DEBUG */
	1,
	1
};
CmPAsnElmDef sz3gOptRAC =
{
#ifdef CM_PASN_DBG
	" sz3gRAC " ,
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_OCTSTR,
	CM_PASN_EXT_MKR_ABS,
	sizeof(SztRAC),
	&flagSz3O,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *) (&sz3gRACspec),
	NULLP
};
CmPAsnElmDef sz3gRAC =
{
#ifdef CM_PASN_DBG
	" sz3gRAC " ,
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_OCTSTR,
	CM_PASN_EXT_MKR_ABS,
	sizeof(SztRAC),
	&flagSz3M,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *) (&sz3gRACspec),
	NULLP
};
PUBLIC CmPAsnElmDef *sz3g_ExtnCGI_ExtIEsClsInst[] =
{
	&sz3gRAC
};
PUBLIC U32 sz3g_ExtnCGI_ExtIEsClsInstId[] =
{
	Sztid_RAC
};
PUBLIC CmPAsnClassInfo sz3g_ExtnCGI_ExtIEsClsInfo =
{
	1,
	&sz3g_ExtnCGI_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz3g_ExtnCGI_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
	&sz3g_ExtnCGI_ExtIEsClsInfo,
	(sizeof(SztProtExtnID) + sizeof(SztCriticality)),
	&sz3g_ExtnCGI_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
	CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz3g_ExtnCGI_ExtIEsCls =
{
#ifdef CM_PASN_DBG
	" sz3g_ExtnCGI_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_CLASSIE,
	CM_PASN_EXT_MKR_ABS,
	sizeof(Szt_ExtnCGI_ExtIEsCls),
	&flagSz3M,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *)(&sz3g_ExtnCGI_ExtIEsClsSpec)
};
PUBLIC CmPAsnElmDef *sz3gProtExtnField_CGI_ExtIEsTkn[] =
{
	&sz3gProtExtnID,
	&sz3gCriticality,
	&sz3g_ExtnCGI_ExtIEsCls,
	&sz3gConstTerm
};
CmPAsnSetSeqDef sz3gProtExtnField_CGI_ExtIEsspec =
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
	0,      /* number of optional elements */
	0,      /* number of extension elements */
	NULLP, /* not supported yet */
	NULLP, /* not supported yet */
	&sz3gProtExtnField_CGI_ExtIEsTkn[0], /* ptr to first token*/
	FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef sz3gProtExtnField_CGI_ExtIEs =
{
#ifdef CM_PASN_DBG
	" sz3gProtExtnField_CGI_ExtIEs ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_SEQ,
	CM_PASN_EXT_MKR_ABS,
	sizeof(SztProtExtnField_CGI_ExtIEs),
	&flagSz3M,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *)(&sz3gProtExtnField_CGI_ExtIEsspec),
	NULLP
};
CmPAsnSetSeqOfDef sz3gProtExtnCont_CGI_ExtIEsspec =
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
	1,        /* start of the size */
	SztmaxProtExtns,        /* start of the size */
	3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef sz3gOptProtExtnCont_CGI_ExtIEs =
{
#ifdef CM_PASN_DBG
	" sz3gProtExtnCont_CGI_ExtIEs ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_SEQOF,
	CM_PASN_EXT_MKR_ABS,
	sizeof(SztProtExtnCont_CGI_ExtIEs),
	&flagSz3O,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *) (&sz3gProtExtnCont_CGI_ExtIEsspec),
	NULLP
};
PUBLIC CmPAsnElmDef sz3gProtExtnCont_CGI_ExtIEs =
{
#ifdef CM_PASN_DBG
	" sz3gProtExtnCont_CGI_ExtIEs ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_SEQOF,
	CM_PASN_EXT_MKR_ABS,
	sizeof(SztProtExtnCont_CGI_ExtIEs),
	&flagSz3M,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *) (&sz3gProtExtnCont_CGI_ExtIEsspec),
	NULLP
};
CmPAsnOctStrDef sz3gLACspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTR,
#endif /* CM_PASN_DEBUG */
   2,
   2
};
CmPAsnElmDef sz3gLAC =
{
#ifdef CM_PASN_DBG
   " sz3gLAC " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTR,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztLAC),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&sz3gLACspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz3gCGITkn[] =
{
	&sz3gTBCD_STRING,
	&sz3gLAC,
	&sz3gCI,
	&sz3gOptProtExtnCont_CGI_ExtIEs,
		&sz3gProtExtnField_CGI_ExtIEs,
		&sz3gConstTerm,
	&sz3gConstTerm
};
CmPAsnSetSeqDef sz3gCGIspec =
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
	1,      /* number of optional elements */
	0,      /* number of extension elements */
	NULLP, /* not supported yet */
	NULLP, /* not supported yet */
	&sz3gCGITkn[0], /* ptr to first token*/
	FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef sz3gCGI =
{
#ifdef CM_PASN_DBG
	" sz3gCGI ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_SEQ,
	CM_PASN_EXT_MKR_ABS,
	sizeof(SztCGI),
	&flagSz3M,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *)(&sz3gCGIspec),
	NULLP
};
PUBLIC CmPAsnElmDef *sz3gSrcCellIDTkn[] =
{
	&sz3gSrcUTRANCellID,
	&sz3gCGI,
	&sz3gExtMkr,
	&sz3gConstTerm
};
CmPAsnChoiceDef sz3gSrcCellIDspec = 
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_CHOICE,
#endif
	2,
	0,
	&sz3gSrcCellIDTkn[0]  /* Token List */
};
CmPAsnElmDef sz3gSrcCellID =
{
#ifdef CM_PASN_DBG
	" sz3gSrcCellID ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_CHOICE,
	CM_PASN_EXT_MKR_PRES,
	sizeof(SztSrcCellID),
	&flagSz3M,
	NULLP,
	(U8 *)(&sz3gSrcCellIDspec),
	NULLP
};

/* Element ----- Cell-Capacity-Class-Value ------- */
CmPAsnUIntDef sz3gCell_Capacity_Class_Valuespec =
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
	1,
	100UL
};
CmPAsnElmDef sz3gCell_Capacity_Class_Value =
{
#ifdef CM_PASN_DBG
	" sz3gCell_Capacity_Class_Value ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_UINT32,
	CM_PASN_EXT_MKR_PRES,
	sizeof(SztCell_Capacity_Class_Value),
	&flagSz3M,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *)(&sz3gCell_Capacity_Class_Valuespec),
	NULLP
};

/* Element ----- LoadValue ------- */
CmPAsnUIntDef sz3gLoadValuespec =
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
	0,
	100UL
};
CmPAsnElmDef sz3gLoadValue =
{
#ifdef CM_PASN_DBG
	" sz3gLoadValue ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_UINT32,
	CM_PASN_EXT_MKR_ABS,
	sizeof(SztLoadValue),
	&flagSz3M,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *)(&sz3gLoadValuespec),
	NULLP
};

/* Element ----- RTLoadValue ------- */
CmPAsnUIntDef sz3gRTLoadValuespec =
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
	0,
	100UL
};
CmPAsnElmDef sz3gOptRTLoadValue =
{
#ifdef CM_PASN_DBG
	" sz3gRTLoadValue ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_UINT32,
	CM_PASN_EXT_MKR_ABS,
	sizeof(SztRTLoadValue),
	&flagSz3O,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *)(&sz3gRTLoadValuespec),
	NULLP
};

/* Element ----- NRTLoadInformationValue ------- */
CmPAsnUIntDef sz3gNRTLoadInformValuespec =
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
	0,
	3UL
};
CmPAsnElmDef sz3gOptNRTLoadInformValue =
{
#ifdef CM_PASN_DBG
	" sz3gNRTLoadInformValue ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_UINT32,
	CM_PASN_EXT_MKR_ABS,
	sizeof(SztNRTLoadInformValue),
	&flagSz3O,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *)(&sz3gNRTLoadInformValuespec),
	NULLP
};
CmPAsnSetSeqOfDef sz3gProtExtnCont_CellLoadInform_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef sz3gOptProtExtnCont_CellLoadInform_ExtIEs =
{
#ifdef CM_PASN_DBG
   " sz3gProtExtnCont_CellLoadInform_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_CellLoadInform_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&sz3gProtExtnCont_CellLoadInform_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef sz3gProtExtnCont_CellLoadInform_ExtIEs =
{
#ifdef CM_PASN_DBG
   " sz3gProtExtnCont_CellLoadInform_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_CellLoadInform_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&sz3gProtExtnCont_CellLoadInform_ExtIEsspec),
   NULLP
};

PUBLIC CmPAsnElmDef *sz3g_ExtnCellLoadInform_ExtIEsClsInst[] =
{
   NULLP
};
PUBLIC U32 sz3g_ExtnCellLoadInform_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz3g_ExtnCellLoadInform_ExtIEsClsInfo =
{
   0,
   &sz3g_ExtnCellLoadInform_ExtIEsClsInstId[0]
};

CmPAsnClassIEDef sz3g_ExtnCellLoadInform_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz3g_ExtnCellLoadInform_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz3g_ExtnCellLoadInform_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz3g_ExtnCellLoadInform_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz3g_ExtnCellLoadInform_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnCellLoadInform_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3g_ExtnCellLoadInform_ExtIEsClsSpec)
};
PUBLIC CmPAsnElmDef *sz3gProtExtnField_CellLoadInform_ExtIEsTkn[] =
{
   &sz3gProtExtnID,
   &sz3gCriticality,
   &sz3g_ExtnCellLoadInform_ExtIEsCls,
   &sz3gConstTerm
};
CmPAsnSetSeqDef sz3gProtExtnField_CellLoadInform_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &sz3gProtExtnField_CellLoadInform_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef sz3gProtExtnField_CellLoadInform_ExtIEs =
{
#ifdef CM_PASN_DBG
   " sz3gProtExtnField_CellLoadInform_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_CellLoadInform_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3gProtExtnField_CellLoadInform_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz3gCellLoadInformTkn[] =
{
   &sz3gCell_Capacity_Class_Value,
   &sz3gLoadValue,
   &sz3gOptRTLoadValue,
   &sz3gOptNRTLoadInformValue,
   &sz3gOptProtExtnCont_CellLoadInform_ExtIEs,
   &sz3gProtExtnField_CellLoadInform_ExtIEs,
   &sz3gConstTerm,
   &sz3gExtMkr,
   &sz3gConstTerm
};
CmPAsnSetSeqDef sz3gCellLoadInformspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   3,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &sz3gCellLoadInformTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef sz3gOptCellLoadInform =
{
#ifdef CM_PASN_DBG
   " sz3gCellLoadInform ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztCellLoadInform),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3gCellLoadInformspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz3g_ExtnCellLoadInformGroup_ExtIEsClsInst[] =
{
	NULLP
};
PUBLIC U32 sz3g_ExtnCellLoadInformGroup_ExtIEsClsInstId[] =
{
	Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz3g_ExtnCellLoadInformGroup_ExtIEsClsInfo =
{
	0,
	&sz3g_ExtnCellLoadInformGroup_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz3g_ExtnCellLoadInformGroup_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
	&sz3g_ExtnCellLoadInformGroup_ExtIEsClsInfo,
	(sizeof(SztProtExtnID) + sizeof(SztCriticality)),
	&sz3g_ExtnCellLoadInformGroup_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
	CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz3g_ExtnCellLoadInformGroup_ExtIEsCls =
{
#ifdef CM_PASN_DBG
	" sz3g_ExtnCellLoadInformGroup_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_CLASSIE,
	CM_PASN_EXT_MKR_ABS,
	sizeof(Szt_ExtnCellLoadInformGroup_ExtIEsCls),
	&flagSz3M,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *)(&sz3g_ExtnCellLoadInformGroup_ExtIEsClsSpec)
};
PUBLIC CmPAsnElmDef *sz3gProtExtnField_CellLoadInformGroup_ExtIEsTkn[] =
{
	&sz3gProtExtnID,
	&sz3gCriticality,
	&sz3g_ExtnCellLoadInformGroup_ExtIEsCls,
	&sz3gConstTerm
};
CmPAsnSetSeqDef sz3gProtExtnField_CellLoadInformGroup_ExtIEsspec =
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
	0,      /* number of optional elements */
	0,      /* number of extension elements */
	NULLP, /* not supported yet */
	NULLP, /* not supported yet */
	&sz3gProtExtnField_CellLoadInformGroup_ExtIEsTkn[0], /* ptr to first token*/
	FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef sz3gProtExtnField_CellLoadInformGroup_ExtIEs =
{
#ifdef CM_PASN_DBG
	" sz3gProtExtnField_CellLoadInformGroup_ExtIEs ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_SEQ,
	CM_PASN_EXT_MKR_ABS,
	sizeof(SztProtExtnField_CellLoadInformGroup_ExtIEs),
	&flagSz3M,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *)(&sz3gProtExtnField_CellLoadInformGroup_ExtIEsspec),
	NULLP
};
CmPAsnSetSeqOfDef sz3gProtExtnCont_CellLoadInformGroup_ExtIEsspec =
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
	1,        /* start of the size */
	SztmaxProtExtns,        /* start of the size */
	3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef sz3gOptProtExtnCont_CellLoadInformGroup_ExtIEs =
{
#ifdef CM_PASN_DBG
	" sz3gProtExtnCont_CellLoadInformGroup_ExtIEs ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_SEQOF,
	CM_PASN_EXT_MKR_ABS,
	sizeof(SztProtExtnCont_CellLoadInformGroup_ExtIEs),
	&flagSz3O,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *) (&sz3gProtExtnCont_CellLoadInformGroup_ExtIEsspec),
	NULLP
};

PUBLIC CmPAsnElmDef *sz3gCellLoadInformGroupTkn[] =
{
   &sz3gSrcCellID,
   &sz3gOptCellLoadInform,
   &sz3gOptCellLoadInform,
   &sz3gOptProtExtnCont_CellLoadInformGroup_ExtIEs,
   &sz3gProtExtnField_CellLoadInformGroup_ExtIEs,
   &sz3gConstTerm,
   &sz3gExtMkr,
   &sz3gConstTerm
};
CmPAsnSetSeqDef sz3gCellLoadInformGroupspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   3,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &sz3gCellLoadInformGroupTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef sz3gCellLoadInformGroup =
{
#ifdef CM_PASN_DBG
   " sz3gCellLoadInformGroup ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztCellLoadInformGroup),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3gCellLoadInformGroupspec),
   NULLP
};
CmPAsnOctStrDef sz3gTraceReferencespec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   2,
   3
};

CmPAsnElmDef sz3gTraceReference =
{
#ifdef CM_PASN_DBG
   " sz3gTraceReference " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztTraceReference),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&sz3gTraceReferencespec),
   NULLP
};
/* Element ----- TraceRecordingSessionReference ------- */
CmPAsnUIntDef sz3gTraceRecordingSessionReferencespec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
   0,
   65535UL
};
CmPAsnElmDef sz3gTraceRecordingSessionReference =
{
#ifdef CM_PASN_DBG
   " sz3gTraceRecordingSessionReference ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztTraceRecordingSessionReference),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3gTraceRecordingSessionReferencespec),
   NULLP
};
CmPAsnSetSeqOfDef sz3gProtExtnCont_TraceRecordingSessionInform_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef sz3gOptProtExtnCont_TraceRecordingSessionInform_ExtIEs =
{
#ifdef CM_PASN_DBG
   " sz3gProtExtnCont_TraceRecordingSessionInform_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_TraceRecordingSessionInform_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&sz3gProtExtnCont_TraceRecordingSessionInform_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz3g_ExtnTraceRecordingSessionInform_ExtIEsClsInst[] =
{
      NULLP
};
PUBLIC U32 sz3g_ExtnTraceRecordingSessionInform_ExtIEsClsInstId[] =
{
   Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz3g_ExtnTraceRecordingSessionInform_ExtIEsClsInfo =
{
   0,
   &sz3g_ExtnTraceRecordingSessionInform_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz3g_ExtnTraceRecordingSessionInform_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz3g_ExtnTraceRecordingSessionInform_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz3g_ExtnTraceRecordingSessionInform_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz3g_ExtnTraceRecordingSessionInform_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz3g_ExtnTraceRecordingSessionInform_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnTraceRecordingSessionInform_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3g_ExtnTraceRecordingSessionInform_ExtIEsClsSpec)
};
PUBLIC CmPAsnElmDef *sz3gProtExtnField_TraceRecordingSessionInform_ExtIEsTkn[] =
{
   &sz3gProtExtnID,
   &sz3gCriticality,
   &sz3g_ExtnTraceRecordingSessionInform_ExtIEsCls,
   &sz3gConstTerm
};
CmPAsnSetSeqDef sz3gProtExtnField_TraceRecordingSessionInform_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &sz3gProtExtnField_TraceRecordingSessionInform_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef sz3gProtExtnField_TraceRecordingSessionInform_ExtIEs =
{
#ifdef CM_PASN_DBG
   " sz3gProtExtnField_TraceRecordingSessionInform_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_TraceRecordingSessionInform_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3gProtExtnField_TraceRecordingSessionInform_ExtIEsspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz3gTraceRecordingSessionInformTkn[] =
{
   &sz3gTraceReference,
   &sz3gTraceRecordingSessionReference,
   &sz3gOptProtExtnCont_TraceRecordingSessionInform_ExtIEs,
   &sz3gProtExtnField_TraceRecordingSessionInform_ExtIEs,
   &sz3gConstTerm,
   &sz3gExtMkr,
   &sz3gConstTerm
};
CmPAsnSetSeqDef sz3gTraceRecordingSessionInformspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &sz3gTraceRecordingSessionInformTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef sz3gTraceRecordingSessionInform =
{
#ifdef CM_PASN_DBG
   " sz3gTraceRecordingSessionInform ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztTraceRecordingSessionInform),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3gTraceRecordingSessionInformspec),
   NULLP
};
/* Element ----- MBMSLinkingInformation ------- */
CmPAsnTknEnum sz3gMBMSLinkingInformLst[2] =
{
   1,
   SztMBMSLinkingInformuE_has_joined_multicast_servicesEnum
};
CmPAsnEnumDef sz3gMBMSLinkingInformspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   sz3gMBMSLinkingInformLst,
   NULLP
};
CmPAsnElmDef sz3gMBMSLinkingInform =
{
#ifdef CM_PASN_DBG
   " sz3gMBMSLinkingInform ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztMBMSLinkingInform),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3gMBMSLinkingInformspec),
   NULLP
};
CmPAsnElmDef sz3gD_RNTI =
{
#ifdef CM_PASN_DBG
   " sz3gD_RNTI ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztD_RNTI),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3gD_RNTIspec),
   NULLP
};
CmPAsnOctStrDef sz3gUE_History_Informspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_OCTSTRXL,
#endif /* CM_PASN_DEBUG */
   0,
   CM_PASN_PLUS_INF
};
CmPAsnElmDef sz3gUE_History_Inform =
{
#ifdef CM_PASN_DBG
   " sz3gUE_History_Inform " ,
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_OCTSTRXL,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztUE_History_Inform),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&sz3gUE_History_Informspec),
   NULLP
};
/* Element ----- SubscriberProfileIDforRFP ------- */
CmPAsnUIntDef sz3gSubscriberProfileIDforRFPspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT32,
#endif /* CM_PASN_DEBUG */
   1,
   256UL
};
CmPAsnElmDef sz3gSubscriberProfileIDforRFP =
{
#ifdef CM_PASN_DBG
   " sz3gSubscriberProfileIDforRFP ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_UINT32,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztSubscriberProfileIDforRFP),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3gSubscriberProfileIDforRFPspec),
   NULLP
};
CmPAsnBitStrDef sz3gSRVCC_Informnoncespec =
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_BITSTRXL,
#endif /* CM_PASN_DEBUG */
	128,
	128
};
CmPAsnElmDef sz3gSRVCC_Informnonce =
{
#ifdef CM_PASN_DBG
	" sz3gSRVCC_Informnonce ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_BITSTRXL,
	CM_PASN_EXT_MKR_ABS,
	sizeof(SztSRVCC_Informnonce),
	&flagSz3M,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *) (&sz3gSRVCC_Informnoncespec),
	NULLP
};
PUBLIC CmPAsnElmDef *sz3g_ExtnSRVCC_Inform_ExtIEsClsInst[] =
{
	NULLP
};
PUBLIC U32 sz3g_ExtnSRVCC_Inform_ExtIEsClsInstId[] =
{
	Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz3g_ExtnSRVCC_Inform_ExtIEsClsInfo =
{
	0,
	&sz3g_ExtnSRVCC_Inform_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz3g_ExtnSRVCC_Inform_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
	&sz3g_ExtnSRVCC_Inform_ExtIEsClsInfo,
	(sizeof(SztProtExtnID) + sizeof(SztCriticality)),
	&sz3g_ExtnSRVCC_Inform_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
	CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz3g_ExtnSRVCC_Inform_ExtIEsCls =
{
#ifdef CM_PASN_DBG
	" sz3g_ExtnSRVCC_Inform_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_CLASSIE,
	CM_PASN_EXT_MKR_ABS,
	sizeof(Szt_ExtnSRVCC_Inform_ExtIEsCls),
	&flagSz3M,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *)(&sz3g_ExtnSRVCC_Inform_ExtIEsClsSpec)
};
PUBLIC CmPAsnElmDef *sz3gProtExtnField_SRVCC_Inform_ExtIEsTkn[] =
{
	&sz3gProtExtnID,
	&sz3gCriticality,
	&sz3g_ExtnSRVCC_Inform_ExtIEsCls,
	&sz3gConstTerm
};
CmPAsnSetSeqDef sz3gProtExtnField_SRVCC_Inform_ExtIEsspec =
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
	0,      /* number of optional elements */
	0,      /* number of extension elements */
	NULLP, /* not supported yet */
	NULLP, /* not supported yet */
	&sz3gProtExtnField_SRVCC_Inform_ExtIEsTkn[0], /* ptr to first token*/
	FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef sz3gProtExtnField_SRVCC_Inform_ExtIEs =
{
#ifdef CM_PASN_DBG
	" sz3gProtExtnField_SRVCC_Inform_ExtIEs ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_SEQ,
	CM_PASN_EXT_MKR_ABS,
	sizeof(SztProtExtnField_SRVCC_Inform_ExtIEs),
	&flagSz3M,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *)(&sz3gProtExtnField_SRVCC_Inform_ExtIEsspec),
	NULLP
};
CmPAsnSetSeqOfDef sz3gProtExtnCont_SRVCC_Inform_ExtIEsspec =
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
	1,        /* start of the size */
	SztmaxProtExtns,        /* start of the size */
	3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef sz3gOptProtExtnCont_SRVCC_Inform_ExtIEs =
{
#ifdef CM_PASN_DBG
	" sz3gProtExtnCont_SRVCC_Inform_ExtIEs ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_SEQOF,
	CM_PASN_EXT_MKR_ABS,
	sizeof(SztProtExtnCont_SRVCC_Inform_ExtIEs),
	&flagSz3O,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *) (&sz3gProtExtnCont_SRVCC_Inform_ExtIEsspec),
	NULLP
};
PUBLIC CmPAsnElmDef sz3gProtExtnCont_SRVCC_Inform_ExtIEs =
{
#ifdef CM_PASN_DBG
	" sz3gProtExtnCont_SRVCC_Inform_ExtIEs ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_SEQOF,
	CM_PASN_EXT_MKR_ABS,
	sizeof(SztProtExtnCont_SRVCC_Inform_ExtIEs),
	&flagSz3M,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *) (&sz3gProtExtnCont_SRVCC_Inform_ExtIEsspec),
	NULLP
};

PUBLIC CmPAsnElmDef *sz3gSRVCC_InformTkn[] =
{
   &sz3gSRVCC_Informnonce,
   &sz3gOptProtExtnCont_SRVCC_Inform_ExtIEs,
   &sz3gProtExtnField_SRVCC_Inform_ExtIEs,
   &sz3gConstTerm,
   &sz3gExtMkr,
   &sz3gConstTerm
};
CmPAsnSetSeqDef sz3gSRVCC_Informspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   1,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &sz3gSRVCC_InformTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef sz3gSRVCC_Inform =
{
#ifdef CM_PASN_DBG
   " sz3gSRVCC_Inform ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztSRVCC_Inform),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3gSRVCC_Informspec),
   NULLP
};
/* Element ----- CSFB-Information ------- */
CmPAsnTknEnum sz3gCSFB_InformLst[3] =
{
   2,
   SztCSFB_InformcsfbEnum,
   SztCSFB_Informcsfb_high_priorityEnum
};
CmPAsnEnumDef sz3gCSFB_Informspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_ENUM,
#endif /* CM_PASN_DEBUG */
   sz3gCSFB_InformLst,
   NULLP
};
CmPAsnElmDef sz3gCSFB_Inform =
{
#ifdef CM_PASN_DBG
   " sz3gCSFB_Inform ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_ENUM,
   CM_PASN_EXT_MKR_PRES,
   sizeof(SztCSFB_Inform),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3gCSFB_Informspec),
   NULLP
};
PUBLIC CmPAsnElmDef *sz3g_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsClsInst[] =
{
   &sz3gSRB_TrCH_Mapping,
   &sz3gSRB_TrCH_MappingItem,
   &sz3gConstTerm,
   &sz3gCellLoadInformGroup,
   &sz3gTraceRecordingSessionInform,
   &sz3gMBMSLinkingInform,
   &sz3gD_RNTI,
   &sz3gUE_History_Inform,
   &sz3gSubscriberProfileIDforRFP,
   &sz3gSRVCC_Inform,
   &sz3gRAB_ID,
   &sz3gCSFB_Inform
};
PUBLIC U32 sz3g_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsClsInstId[] =
{
   Sztid_SRB_TrCH_Mapping,
   Sztid_Invalid,
   Sztid_Invalid,
   Sztid_CellLoadInformGroup,
   Sztid_TraceRecordingSessionInform,
   Sztid_MBMSLinkingInform,
   Sztid_d_RNTI_for_NoIuCSUP,
   Sztid_UE_History_Inform,
   Sztid_SubscriberProfileIDforRFP,
   Sztid_SRVCC_Inform,
   Sztid_PSRABtobeReplaced,
   Sztid_CSFB_Inform
};
PUBLIC CmPAsnClassInfo sz3g_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsClsInfo =
{
   12,
   &sz3g_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsClsInstId[0]
};
CmPAsnClassIEDef sz3g_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz3g_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz3g_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};
PUBLIC CmPAsnElmDef sz3g_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz3g_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3g_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsClsSpec)
};
PUBLIC CmPAsnElmDef *sz3gProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEsTkn[] =
{
	&sz3gProtExtnID,
	&sz3gCriticality,
	&sz3g_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsCls,
	&sz3gConstTerm
};

CmPAsnSetSeqDef sz3gProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEsspec =
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
	0,      /* number of optional elements */
	0,      /* number of extension elements */
	NULLP, /* not supported yet */
	NULLP, /* not supported yet */
	&sz3gProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEsTkn[0], /* ptr to first token*/
	FALSE      /* Event Memory Allocated */
};

PUBLIC CmPAsnElmDef sz3gProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEs =
{
#ifdef CM_PASN_DBG
	" sz3gProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEs ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_SEQ,
	CM_PASN_EXT_MKR_ABS,
	sizeof(SztProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEs),
	&flagSz3M,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *)(&sz3gProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEsspec),
	NULLP
};

CmPAsnUIntDef sz3gIntegrityProtectionAlgorithmspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT8,
#endif
   0,   /* minimum */
   15   /* maximum */
};

CmPAsnElmDef sz3gOptIntegrityProtectionAlgorithm =
{
#ifdef CM_PASN_DBG
   "sz3gIntegrityProtectionAlgorithm",
#endif
   CM_PASN_TET_UINT8,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztChosenIntegrityProtectionAlgorithm),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 * ) (&sz3gIntegrityProtectionAlgorithmspec)
};

/* Message definition for sz3gOptEncryptionAlgorithm, sz3gEncryptionAlgorithmspec */
CmPAsnUIntDef sz3gEncryptionAlgorithmspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_UINT8,
#endif
   0,   /* minimum */
   15   /* maximum */
};
CmPAsnElmDef sz3gOptEncryptionAlgorithm=
{
#ifdef CM_PASN_DBG
   "sz3gEncryptionAlgorithm",
#endif
   CM_PASN_TET_UINT8,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztChosenIntegrityProtectionAlgorithm),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 * ) (&sz3gEncryptionAlgorithmspec)
};

/* START Source RNC to target RNC container */
PUBLIC CmPAsnElmDef *sz3gSrcRNC_ToTgetRNC_TprntContTkn[] =
{
	&sz3gRRC_Cont,
	&sz3gNumberOfIuInstances,
	&sz3gRelocationTyp,
	&sz3gOptIntegrityProtectionAlgorithm,
	&sz3gOptIntegrityProtectionKey,
	&sz3gOptEncryptionAlgorithm,
	&sz3gOptEncryptionKey,
	&sz3gOptEncryptionAlgorithm,
	&sz3gOptEncryptionAlgorithm,
	&sz3gOptD_RNTI,
	&sz3gOptTgetCellId,
	&sz3gOptRAB_TrCH_Mapping,
		&sz3gRAB_TrCH_MappingItem,
		&sz3gConstTerm,
	&sz3gOptProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEs, 
		&sz3gProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEs, 
      &sz3gConstTerm,
	&sz3gExtMkr,
	&sz3gConstTerm
};
CmPAsnSetSeqDef sz3gSrcRNC_ToTgetRNC_TprntContspec =
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
	10,      /* number of optional elements */
	0,      /* number of extension elements */
	NULLP, /* not supported yet */
	NULLP, /* not supported yet */
	&sz3gSrcRNC_ToTgetRNC_TprntContTkn[0], /* ptr to first token*/
	FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef sz3gSrcRNC_ToTgetRNC_TprntCont =
{
#ifdef CM_PASN_DBG
	" sz3gSrcRNC_ToTgetRNC_TprntCont ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_SEQ,
	CM_PASN_EXT_MKR_PRES,
	sizeof(SztSrcRNC_ToTgetRNC_TprntCont),
	&flagSz3M,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *)(&sz3gSrcRNC_ToTgetRNC_TprntContspec),
	NULLP
};
/* END source RNC to target RNC container */

/* START target RNC to source RNC container */

CmPAsnSetSeqOfDef sz3gProtExtnCont_TgetRNC_ToSrcRNC_TprntCont_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQOF,
#endif /* CM_PASN_DEBUG */
   1,        /* start of the size */
   SztmaxProtExtns,        /* start of the size */
   3*sizeof(PTR)
};
PUBLIC CmPAsnElmDef sz3gOptProtExtnCont_TgetRNC_ToSrcRNC_TprntCont_ExtIEs =
{
#ifdef CM_PASN_DBG
   " sz3gProtExtnCont_TgetRNC_ToSrcRNC_TprntCont_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQOF,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnCont_TgetRNC_ToSrcRNC_TprntCont_ExtIEs),
   &flagSz3O,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *) (&sz3gProtExtnCont_TgetRNC_ToSrcRNC_TprntCont_ExtIEsspec),
   NULLP
};

PUBLIC CmPAsnElmDef *sz3g_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsClsInst[] =
{
      NULLP
};
PUBLIC U32 sz3g_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsClsInstId[] =
{
      Sztid_Invalid
};
PUBLIC CmPAsnClassInfo sz3g_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsClsInfo =
{
   0,
   &sz3g_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsClsInstId[0]
};

CmPAsnClassIEDef sz3g_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsClsSpec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_CLASSIE,
#endif /* CM_PASN_DEBUG */
   &sz3g_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsClsInfo,
   (sizeof(SztProtExtnID) + sizeof(SztCriticality)),
   &sz3g_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsClsInst[0],
#ifdef CM_PASN_CLASS_IDTYPE
   CM_PASN_TET_UINT32
#endif
};

PUBLIC CmPAsnElmDef sz3g_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsCls =
{
#ifdef CM_PASN_DBG
   " sz3g_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsCls ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_CLASSIE,
   CM_PASN_EXT_MKR_ABS,
   sizeof(Szt_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsCls),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3g_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsClsSpec)
};

PUBLIC CmPAsnElmDef *sz3gProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEsTkn[] =
{
   &sz3gProtExtnID,
   &sz3gCriticality,
   &sz3g_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsCls,
   &sz3gConstTerm
};

CmPAsnSetSeqDef sz3gProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEsspec =
{
#ifdef CM_PASN_DBG
   CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
   0,      /* number of optional elements */
   0,      /* number of extension elements */
   NULLP, /* not supported yet */
   NULLP, /* not supported yet */
   &sz3gProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEsTkn[0], /* ptr to first token*/
   FALSE      /* Event Memory Allocated */
};

PUBLIC CmPAsnElmDef sz3gProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEs =
{
#ifdef CM_PASN_DBG
   " sz3gProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEs ",
#endif /* CM_PASN_DEBUG */
   CM_PASN_TET_SEQ,
   CM_PASN_EXT_MKR_ABS,
   sizeof(SztProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEs),
   &flagSz3M,
   CM_PASN_ESC_FUNC_NULLP,
   (U8 *)(&sz3gProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEsspec),
   NULLP
};

PUBLIC CmPAsnElmDef *sz3gTgetRNC_ToSrcRNC_TprntContTkn[] =
{
	&sz3gRRC_Cont,
	&sz3gOptD_RNTI,
	&sz3gOptProtExtnCont_TgetRNC_ToSrcRNC_TprntCont_ExtIEs,
		&sz3gProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEs,
		&sz3gConstTerm,
	&sz3gExtMkr,
	&sz3gConstTerm
};
CmPAsnSetSeqDef sz3gTgetRNC_ToSrcRNC_TprntContspec =
{
#ifdef CM_PASN_DBG
	CM_PASN_TET_SEQ,
#endif /* CM_PASN_DEBUG */
	2,      /* number of optional elements */
	0,      /* number of extension elements */
	NULLP, /* not supported yet */
	NULLP, /* not supported yet */
	&sz3gTgetRNC_ToSrcRNC_TprntContTkn[0], /* ptr to first token*/
	FALSE      /* Event Memory Allocated */
};
PUBLIC CmPAsnElmDef sz3gTgetRNC_ToSrcRNC_TprntCont =
{
#ifdef CM_PASN_DBG
	" sz3gTgetRNC_ToSrcRNC_TprntCont ",
#endif /* CM_PASN_DEBUG */
	CM_PASN_TET_SEQ,
	CM_PASN_EXT_MKR_PRES,
	sizeof(SztTgetRNC_ToSrcRNC_TprntCont),
	&flagSz3M,
	CM_PASN_ESC_FUNC_NULLP,
	(U8 *)(&sz3gTgetRNC_ToSrcRNC_TprntContspec),
	NULLP
};

PUBLIC CmPAsnElmDef *szMsg3gDbIe[][2] =
{
   {
      NULLP
   },
   {
      NULLP
   },
   {
      NULLP
   },
   {
      &sz3gSrcRNC_ToTgetRNC_TprntCont,
      NULLP
   },
   {
      &sz3gTgetRNC_ToSrcRNC_TprntCont,
      NULLP
   },
   {
      &sz3gSrcCellID,
      NULLP
   }
};
#endif

/**********************************************************************
 
         End of file:     sq_3gdb.c

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
/main/1    sz008.301   akaranth 1. Support for Source RNC to Target RNC TC Enc/Dec.

*********************************************************************91*/
