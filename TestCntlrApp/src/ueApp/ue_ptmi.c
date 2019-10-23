/**********************************************************************

     Name:     Ue Application - management interface

     Type:     C source file

     Desc:     C Source code for the Ue Application upper management primitives.

     File:     ab_ptmi.c

     Sid:      

     Prg:      snatra

**********************************************************************/

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
#include "cm_inet.h"
#include "cm_tpt.h"
#include "ue.h"            /* Ue Layer */
#include "ue_log.h"
#include "lue.h"
#include "lfw.h"

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
#include "cm_tkns.x"
#include "cm_tpt.x"
#include "uet.x"
#include "ue.x"            /* Ue Layer */
#include "lue.x"
#include "ueAppdbm.x"


/* local defines */
#define UE_MAX_MILUE_SEL   4  /* maximum no. of selectors */

#ifdef __cplusplus
EXTERN "C" {
#endif /* end of __cplusplus */
EXTERN UeAppCb gueAppCb;
#if (defined(PTABMILAB) || !defined(LWLCABMILAB))
PRIVATE S16 PtMiLueCfgCfm ARGS((Pst *pst, UeMngmt *cfm));
PRIVATE S16 PtMiLueCntrlCfm ARGS((Pst *pst, UeMngmt *cfm));
#endif /* PTSMAQMILAQ */
/*
   The following matrices define the mapping between the primitives
   called by the management interface of Ue Application layer and
   the corresponding primitives of the Ue Application layer
   service user(s).

   The parameter UE_MAX_MILUE_SEL defines the maximum number of service users on
   top of Ue Application. There is an array of functions per
   primitive invoked by Ue Application. Every array is UE_MAX_MILUE_SEL
   long (i.e. there are as many functions as the number of service users).

   The dispatching is performed by the configurable variable: selector.
   The selector is configured on a per SAP basis. The selectors are:

   UE_SEL_LC - loosely coupled
   UE_SEL_TC - tightly coupled

*/

/* Config Confirm primitive */
PRIVATE CONSTANT LueCfgCfm UeMiLueCfgCfmMt [UE_MAX_MILUE_SEL] =
{
#ifdef LCABMILAB
   cmPkLueCfgCfm,          /* 0 - loosely coupled */
#else
   PtMiLueCfgCfm,          /* 0 - loosely coupled, portable */
#endif
   PtMiLueCfgCfm,          /* 1 - tightly coupled, portable */
#ifdef LWLCABMILAB
   cmPkLueCfgCfm           /* 2 - light weight loosely coupled */
#else
      PtMiLueCfgCfm           /* 2 - light weight loosely coupled, portable */
#endif
};

/* Control Confirm primitive */
PRIVATE CONSTANT LueCntrlCfm UeMiLueCntrlCfmMt [UE_MAX_MILUE_SEL] =
{
#ifdef LCABMILAB
   cmPkLueCntrlCfm,          /* 0 - loosely coupled */
#else
   PtMiLueCntrlCfm,          /* 0 - loosely coupled, portable */
#endif
   PtMiLueCntrlCfm,          /* 1 - tightly coupled, portable */
#ifdef LWLCABMILAB
   cmPkLueCntrlCfm           /* 2 - light weight loosely coupled */
#else
      PtMiLueCntrlCfm           /* 2 - light weight loosely coupled, portable */
#endif
};



/*
*
*       Fun:   UeMiLueCfgCfm
*
*       Desc:  This function resolves the LueCfgCfm primitive
*
*       Ret:  ROK -      ok
*
*       Notes: none
*
*       File:  ab_ptui.c
*
*/
PUBLIC S16 UeMiLueCfgCfm
(
Pst      *pst,
UeMngmt  *cfm
)
{

   (*UeMiLueCfgCfmMt[pst->selector])(pst, cfm);
   RETVALUE(ROK);
} /* end of UeMiLueCfgCfm */

/*
*
*       Fun:   UeMiLueCntrlCfm
*
*       Desc:  This function resolves the LueCntrlCfm primitive
*
*       Ret:  ROK -      ok
*
*       Notes: none
*
*       File:  ab_ptui.c
*
*/
PUBLIC S16 UeMiLueCntrlCfm
(
Pst      *pst,
UeMngmt  *cfm
)
{

   (*UeMiLueCntrlCfmMt[pst->selector])(pst, cfm);
   RETVALUE(ROK);

} /* end of UeMiLueCntrlCfm */
/*
*
*       Fun:   PtMiLueCfgCfm
*
*       Desc:  This function resolves the LueCfgCfm primitive
*
*       Ret:  ROK -      ok
*
*       Notes: none
*
*       File:  ab_ptui.c
*
*/
PUBLIC S16 PtMiLueCfgCfm
(
Pst      *pst,
UeMngmt  *cfm
)
{


   UNUSED(pst);
   UNUSED(cfm);
   RETVALUE(ROK);
} /* end of PtMiLueCfgCfm */

/*
*
*       Fun:   PtMiLueCntrlCfm
*
*       Desc:  This function resolves the LueCntrlCfm primitive
*
*       Ret:  ROK -      ok
*
*       Notes: none
*
*       File:  ab_ptui.c
*
*/
PUBLIC S16 PtMiLueCntrlCfm
(
Pst      *pst,
UeMngmt  *cfm
)
{

   UNUSED(pst);
   UNUSED(cfm);
   RETVALUE(ROK);

} /* end of PtMiLueCntrlCfm */
#ifdef __cplusplus
} /* end of EXTERN "C" */
#endif /* end of __cplusplus */

/********************************************************************30**

           End of file:    

*********************************************************************31*/
