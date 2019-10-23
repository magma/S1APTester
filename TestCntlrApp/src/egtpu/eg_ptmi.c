


/********************************************************************20**

     Name:     eGTP   Protocol - management interface

     Type:     C source file

     Desc:     C Source code for the eGTP   Protocol upper management primitives.

     File:     eg_ptmi.c

     Sid:      eg_ptmi.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:47 2015

     Prg:      an

*********************************************************************21*/


/* header include files (.h) */

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* General */
#include "ssi.h"           /* System Services */
#include "cm_tkns.h"       /* common tokens */
#include "cm_hash.h"       /* common structs 1 */
#include "cm_mblk.h"       /* common memory */
#include "cm_llist.h"      /* cm link list */
#include "cm5.h"           /* common structs 3 */
#include "cm_inet.h"       /* common tokens  */
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport */
#include "cm_dns.h"        /* common transport */
#include "hit.h"           /* TUCL Layer */
#include "egt.h"           /* eGTP Upper Interface */
#include "leg.h"           /* eGTP LM Interface */
/*eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_psf.h"
#include "sht.h"           /* SHT include file                */
#endif
#include "eg.h"            /* eGTP Layer */
#include "eg_err.h"        /* Error codes */
#include "eg_edm.h"        /* EDM Module structures            */

/* Header Include Files (.x) */

#include "gen.x"           /* General */
#include "ssi.x"           /* System Services */
#include "cm_tkns.x"       /* common tokens */
#include "cm_hash.x"       /* common structs 1 */
#include "cm_lib.x"        /* common library */
#include "cm_mblk.x"       /* common memory */
#include "cm_llist.x"      /* cm link list */
#include "cm5.x"           /* common structs 3 */
#include "cm_inet.x"       /* common transport */
#include "cm_tpt.x"        /* common transport */
#include "cm_dns.x"        /* common transport */
#include "hit.x"           /* TUCL Layer */
#include "egt.x"           /* eGTP Upper Interface */
#include "leg.x"           /* eGTP LM Interface */
#include "eg_edm.x"        /* EDM Module structures            */
/*eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#include "sht.x"           /* SHT include file                */

#endif
#include "eg.x"            /* eGTP Layer */
#include "eg_tpt.x"            /* EGTP TPT module defines */
#ifdef HW
#include "lhw.x"
#include "hw.x"          /* EGTPC UA                       */
#endif

/* local function definition */

/* local defines */
#define EG_MAX_MILEG_SEL   3  /* maximum no. of selectors */

#ifndef LCEGMILEG
#define PTEGMILEG
#else
#ifndef SM
#define PTEGMILEG
#else
#endif /* end of LCEGMILEG */
#endif /* end of LCEGMILEG */

#ifdef __cplusplus
EXTERN "C" {
#endif /* end of __cplusplus */

/* functions in other modules */

/* public variable declarations */

/* control variables for testing */

/* private variable declarations */

#ifdef PTEGMILEG
/* portable functions */
/* forward references */
PRIVATE S16 PtMiLegCfgCfm ARGS((Pst *pst, EgMngmt *cfm));
PRIVATE S16 PtMiLegStsCfm ARGS((Pst *pst, EgMngmt *cfm));
PRIVATE S16 PtMiLegStaCfm ARGS((Pst *pst, EgMngmt *cfm));
PRIVATE S16 PtMiLegStaInd ARGS((Pst *pst, EgMngmt *ind));
PRIVATE S16 PtMiLegCntrlCfm ARGS((Pst *pst, EgMngmt *cfm));
PRIVATE S16 PtMiLegTrcInd ARGS((Pst *pst, EgMngmt *ind, Buffer *mBuf));
#endif
/*eg004.201 eGTPC PSF specific primitive to handle SH request*/
#ifdef HW
PRIVATE S16 PtMiShtCntrlCfm  ARGS((Pst             *pst,
                                   ShtCntrlCfmEvnt *cfmInfo));
#endif

/*
   The following matrices define the mapping between the primitives
   called by the management interface of eGTP   Protocol layer and
   the corresponding primitives of the eGTP   Protocol layer
   service user(s).

   The parameter EG_MAX_MILEG_SEL defines the maximum number of service users on
   top of eGTP   Protocol. There is an array of functions per
   primitive invoked by eGTP   Protocol. Every array is EG_MAX_MILEG_SEL
   long (i.e. there are as many functions as the number of service users).

   The dispatching is performed by the configurable variable: selector.
   The selector is configured on a per SAP basis. The selectors are:

   EG_SEL_LC - loosely coupled
   EG_SEL_TC - tightly coupled

*/

/* Config Confirm primitive */
PRIVATE CONSTANT LegCfgCfm EgMiLegCfgCfmMt [EG_MAX_MILEG_SEL] =
{
#ifdef LCEGMILEG
   cmPkLegCfgCfm,          /* 0 - loosely coupled */
#else
   PtMiLegCfgCfm,          /* 0 - loosely coupled, portable */
#endif
#ifdef SM
   SmMiLegCfgCfm,          /* 1 - tightly coupled, service user SM */
#else
   PtMiLegCfgCfm,          /* 1 - tightly coupled, portable */
#endif
};

/* Statistics Confirm primitive */
PRIVATE CONSTANT LegStsCfm EgMiLegStsCfmMt [EG_MAX_MILEG_SEL] =
{
#ifdef LCEGMILEG
   cmPkLegStsCfm,          /* 0 - loosely coupled */
#else
   PtMiLegStsCfm,          /* 0 - loosely coupled, portable */
#endif
#ifdef SM
   SmMiLegStsCfm,          /* 1 - tightly coupled, service user SM */
#else
   PtMiLegStsCfm,          /* 1 - tightly coupled, portable */
#endif
};

/* Status Confirm primitive */
PRIVATE CONSTANT LegStaCfm EgMiLegStaCfmMt [EG_MAX_MILEG_SEL] =
{
#ifdef LCEGMILEG
   cmPkLegStaCfm,          /* 0 - loosely coupled */
#else
   PtMiLegStaCfm,          /* 0 - loosely coupled, portable */
#endif
#ifdef SM
   SmMiLegStaCfm,          /* 1 - tightly coupled, service user SM */
#else
   PtMiLegStaCfm,          /* 1 - tightly coupled, portable */
#endif
};

/* Status Indication primitive */
PRIVATE CONSTANT LegStaInd EgMiLegStaIndMt [EG_MAX_MILEG_SEL] =
{
#ifdef LCEGMILEG
   cmPkLegStaInd,          /* 0 - loosely coupled */
#else
   PtMiLegStaInd,          /* 0 - loosely coupled, portable */
#endif
#ifdef SM
   SmMiLegStaInd,          /* 1 - tightly coupled, service user SM */
#else
   PtMiLegStaInd,          /* 1 - tightly coupled, portable */
#endif
};

/* Control Confirm primitive */
PRIVATE CONSTANT LegCntrlCfm EgMiLegCntrlCfmMt [EG_MAX_MILEG_SEL] =
{
#ifdef LCEGMILEG
   cmPkLegCntrlCfm,          /* 0 - loosely coupled */
#else
   PtMiLegCntrlCfm,          /* 0 - loosely coupled, portable */
#endif
#ifdef SM
   SmMiLegCntrlCfm,          /* 1 - tightly coupled, service user SM */
#else
   PtMiLegCntrlCfm,          /* 1 - tightly coupled, portable */
#endif
};

/* Trace Indication primitive */
PRIVATE CONSTANT LegTrcInd EgMiLegTrcIndMt [EG_MAX_MILEG_SEL] =
{
#ifdef LCEGMILEG
   cmPkLegTrcInd,          /* 0 - loosely coupled */
#else
   PtMiLegTrcInd,          /* 0 - loosely coupled, portable */
#endif
#ifdef SM
   SmMiLegTrcInd,          /* 1 - tightly coupled, service user SM */
#else
   PtMiLegTrcInd,          /* 1 - tightly coupled, portable */
#endif
};
/* eg004.201 Selector table for Packing of SH control request based on selector*/
#ifdef EG_FTHA
PUBLIC ShtCntrlCfm EgMiShtCntrlCfmMt[EG_MAX_MILEG_SEL] =
{
#ifdef LCSHMILEG
   cmPkMiShtCntrlCfm,     /* 0 - loosely coupled (default mechanism) */
#else
   PtMiShtCntrlCfm,       /* 1 - tightly coupled, portable */
#endif
#ifdef SH
   ShMiShtCntrlCfm,       /* 1 - tightly coupled, stack manager */
#else
   PtMiShtCntrlCfm,       /* 1 - tightly coupled, portable */
#endif
};
#endif




/*
*
*       Fun:   EgMiLegCfgCfm
*
*       Desc:  This function resolves the LegCfgCfm primitive
*
*       Ret:  ROK -      ok
*
*       Notes: none
*
*       File:  eg_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 EgMiLegCfgCfm
(
Pst      *pst,
EgMngmt  *cfm
)
#else
PUBLIC S16 EgMiLegCfgCfm (pst, cfm)
Pst      *pst;
EgMngmt  *cfm;
#endif
{
   TRC3(EgMiLegCfgCfm);

   (*EgMiLegCfgCfmMt[pst->selector])(pst, cfm);

   RETVALUE(ROK);
} /* end of EgMiLegCfgCfm */


/*
*
*       Fun:   EgMiLegStsCfm
*
*       Desc:  This function resolves the LegStsCfm primitive
*
*       Ret:  ROK -      ok
*
*       Notes: none
*
*       File:  eg_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 EgMiLegStsCfm
(
Pst      *pst,
EgMngmt  *cfm
)
#else
PUBLIC S16 EgMiLegStsCfm (pst, cfm)
Pst      *pst;
EgMngmt  *cfm;
#endif
{
   TRC3(EgMiLegStsCfm);

   (*EgMiLegStsCfmMt[pst->selector])(pst, cfm);

   RETVALUE(ROK);
} /* end of EgMiLegStsCfm */


/*
*
*       Fun:   EgMiLegStaCfm
*
*       Desc:  This function resolves the LegStaCfm primitive
*
*       Ret:  ROK -      ok
*
*       Notes: none
*
*       File:  eg_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 EgMiLegStaCfm
(
Pst      *pst,
EgMngmt  *cfm
)
#else
PUBLIC S16 EgMiLegStaCfm (pst, cfm)
Pst      *pst;
EgMngmt  *cfm;
#endif
{
   TRC3(EgMiLegStaCfm);

   (*EgMiLegStaCfmMt[pst->selector])(pst, cfm);

   RETVALUE(ROK);
} /* end of EgMiLegStaCfm */


/*
*
*       Fun:   EgMiLegStaInd
*
*       Desc:  This function resolves the LegStaInd primitive
*
*       Ret:  ROK -      ok
*
*       Notes: none
*
*       File:  eg_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 EgMiLegStaInd
(
Pst      *pst,
EgMngmt  *cfm
)
#else
PUBLIC S16 EgMiLegStaInd (pst, cfm)
Pst      *pst;
EgMngmt  *cfm;
#endif
{
   TRC3(EgMiLegStaInd);

   (*EgMiLegStaIndMt[pst->selector])(pst, cfm);

   RETVALUE(ROK);
} /* end of EgMiLegStaInd */


/*
*
*       Fun:   EgMiLegCntrlCfm
*
*       Desc:  This function resolves the LegCntrlCfm primitive
*
*       Ret:  ROK -      ok
*
*       Notes: none
*
*       File:  eg_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 EgMiLegCntrlCfm
(
Pst      *pst,
EgMngmt  *cfm
)
#else
PUBLIC S16 EgMiLegCntrlCfm (pst, cfm)
Pst      *pst;
EgMngmt  *cfm;
#endif
{
   TRC3(EgMiLegCntrlCfm);

   (*EgMiLegCntrlCfmMt[pst->selector])(pst, cfm);

   RETVALUE(ROK);
} /* end of EgMiLegCntrlCfm */


/*
*
*       Fun:   EgMiLegTrcInd
*
*       Desc:  This function resolves the LegTrcInd primitive
*
*       Ret:  ROK -      ok
*
*       Notes: none
*
*       File:  eg_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 EgMiLegTrcInd
(
Pst      *pst,
EgMngmt  *cfm,
Buffer   *mBuf
)
#else
PUBLIC S16 EgMiLegTrcInd (pst, cfm, mBuf)
Pst      *pst;
EgMngmt  *cfm;
Buffer   *mBuf;
#endif
{
   TRC3(EgMiLegTrcInd);

   (*EgMiLegTrcIndMt[pst->selector])(pst, cfm, mBuf);

   RETVALUE(ROK);
} /* end of EgMiLegTrcInd */

#ifdef PTEGMILEG


/*
*
*       Fun:   PtMiLegCfgCfm
*
*       Desc:  This function resolves the LegCfgCfm primitive
*
*       Ret:  ROK -      ok
*
*       Notes: none
*
*       File:  eg_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 PtMiLegCfgCfm
(
Pst      *pst,
EgMngmt  *cfm
)
#else
PUBLIC S16 PtMiLegCfgCfm (pst, cfm)
Pst      *pst;
EgMngmt  *cfm;
#endif
{
   TRC3(PtMiLegCfgCfm);

   EGLOGERROR(ERRCLS_DEBUG, EEG009, ERRZERO, "PtMiLegCfgCfm: Invalid selector");

   UNUSED(pst);
   UNUSED(cfm);

   RETVALUE(ROK);
} /* end of PtMiLegCfgCfm */


/*
*
*       Fun:   PtMiLegStsCfm
*
*       Desc:  This function resolves the LegStsCfm primitive
*
*       Ret:  ROK -      ok
*
*       Notes: none
*
*       File:  eg_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 PtMiLegStsCfm
(
Pst      *pst,
EgMngmt  *cfm
)
#else
PUBLIC S16 PtMiLegStsCfm (pst, cfm)
Pst      *pst;
EgMngmt  *cfm;
#endif
{
   TRC3(PtMiLegStsCfm);

   EGLOGERROR(ERRCLS_DEBUG, EEG010, ERRZERO, "PtMiLegStsCfm: Invalid selector");

   UNUSED(pst);
   UNUSED(cfm);

   RETVALUE(ROK);
} /* end of PtMiLegStsCfm */


/*
*
*       Fun:   PtMiLegStaCfm
*
*       Desc:  This function resolves the LegStaCfm primitive
*
*       Ret:  ROK -      ok
*
*       Notes: none
*
*       File:  eg_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 PtMiLegStaCfm
(
Pst      *pst,
EgMngmt  *cfm
)
#else
PUBLIC S16 PtMiLegStaCfm (pst, cfm)
Pst      *pst;
EgMngmt  *cfm;
#endif
{
   TRC3(PtMiLegStaCfm);

   EGLOGERROR(ERRCLS_DEBUG, EEG011, ERRZERO, "PtMiLegStaCfm: Invalid selector");

   UNUSED(pst);
   UNUSED(cfm);

   RETVALUE(ROK);
} /* end of PtMiLegStaCfm */


/*
*
*       Fun:   PtMiLegStaInd
*
*       Desc:  This function resolves the LegStaInd primitive
*
*       Ret:  ROK -      ok
*
*       Notes: none
*
*       File:  eg_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 PtMiLegStaInd
(
Pst      *pst,
EgMngmt  *ind
)
#else
PUBLIC S16 PtMiLegStaInd (pst, ind)
Pst      *pst;
EgMngmt  *ind;
#endif
{
   TRC3(PtMiLegStaInd);

   EGLOGERROR(ERRCLS_DEBUG, EEG012, ERRZERO, "PtMiLegStaInd: Invalid selector");

   UNUSED(pst);
   UNUSED(ind);

   RETVALUE(ROK);
} /* end of PtMiLegStaInd */


/*
*
*       Fun:   PtMiLegCntrlCfm
*
*       Desc:  This function resolves the LegCntrlCfm primitive
*
*       Ret:  ROK -      ok
*
*       Notes: none
*
*       File:  eg_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 PtMiLegCntrlCfm
(
Pst      *pst,
EgMngmt  *cfm
)
#else
PUBLIC S16 PtMiLegCntrlCfm (pst, cfm)
Pst      *pst;
EgMngmt  *cfm;
#endif
{
   TRC3(PtMiLegCntrlCfm);

   EGLOGERROR(ERRCLS_DEBUG, EEG013, ERRZERO, "PtMiLegCntrlCfm: Invalid selector");

   UNUSED(pst);
   UNUSED(cfm);

   RETVALUE(ROK);
} /* end of PtMiLegCntrlCfm */


/*
*
*       Fun:   PtMiLegTrcInd
*
*       Desc:  This function resolves the LegTrcInd primitive
*
*       Ret:  ROK -      ok
*
*       Notes: none
*
*       File:  eg_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 PtMiLegTrcInd
(
Pst      *pst,
EgMngmt  *ind,
Buffer   *mBuf
)
#else
PUBLIC S16 PtMiLegTrcInd (pst, ind, mBuf)
Pst      *pst;
EgMngmt  *ind;
Buffer   *mBuf;
#endif
{
   TRC3(PtMiLegTrcInd);

   EGLOGERROR(ERRCLS_DEBUG, EEG014, ERRZERO, "PtMiLegTrcInd: Invalid selector");

   UNUSED(pst);
   UNUSED(ind);
   UNUSED(mBuf);

   RETVALUE(ROK);
} /* end of PtMiLegTrcInd */

#endif

/*eg004.201 SH cotrol conform definition for eGTPC PSF*/
#ifdef EG_FTHA
/**********************************************************
*
*       Fun:   System Agent Control Confirm
*
*       Desc:  This function sends System Agent Control Confirm
*
*       Ret:   ROK - ok
*
*       Notes: none
*
*       File:  eg_ptmi.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 EgMiShtCntrlCfm
(
Pst             *pst,            /* post structure */
ShtCntrlCfmEvnt *cfmInfo         /* system agent control confirm event */
)
#else
PUBLIC S16 EgMiShtCntrlCfm (pst, cfmInfo)
Pst             *pst;            /* post structure */
ShtCntrlCfmEvnt *cfmInfo;        /* system agent control confirm event */
#endif
{
   EG_TRC3(EgMiShtCntrlCfm);

   (*EgMiShtCntrlCfmMt[pst->selector])(pst, cfmInfo);

   RETVALUE(ROK);
}/* EgMiShtCntrlCfm */
#endif /* HW */


#ifdef HW

/**********************************************************
*
*       Fun:   PtMiShtCntrlCfm
*
*       Desc:  Portable version of ShtCntrlCfm primitive
*
*       Ret:   RFAILED
*
*       Notes: none
*
*       File:  eg_ptmi.c
*
**********************************************************/
#ifdef ANSI
PRIVATE S16 PtMiShtCntrlCfm
(
Pst             *pst,            /* post structure */
ShtCntrlCfmEvnt *cfmInfo         /* system agent control confirm event */
)
#else
PRIVATE S16 PtMiShtCntrlCfm (pst, cfmInfo)
Pst             *pst;            /* post structure */
ShtCntrlCfmEvnt *cfmInfo;        /* system agent control confirm event */
#endif
{
   EG_TRC3(PtMiShtCntrlCfm);

   EGLOGDBGERR(EEGXXX, (ErrVal)ERRZERO, "PtMiShtCntrlCfm(): Invalid Selector");

   UNUSED(pst);
   UNUSED(cfmInfo);

   RETVALUE(RFAILED);
} /* PtMiShtCntrlCfm */
#endif




#ifdef __cplusplus
} /* end of EXTERN "C" */
#endif /* end of __cplusplus */

/********************************************************************30**
 
         End of file:     eg_ptmi.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:47 2015
 
*********************************************************************31*/
 
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
/main/1      ---      ad                1. Created for Initial Release 1.1
/main/2      ---      rss               1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla       Initial Release of eGTP 2.1 release
/main/3      eg004.201 magnihotri      1. Header files added for eGTP-C PSF
                                       2. eGTPC PSF specific primitive to handle SH request
                                       3. table for Packing of SH control request based on selector
                                       4. SH cotrol conform definition for eGTPC PSF
*********************************************************************91*/
