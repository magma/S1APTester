

/********************************************************************20**

     Name:     SCTP Layer

     Type:     C source file

     Desc:     C source code for SCTP Layer
               portable Management Interface

     File:     sb_ptmi.c

     Sid:      sb_ptmi.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:18 2015

     Prg:      bk, wvdl

*********************************************************************21*/


/* header include files (.h) */

/* header/extern include files (.x) */



/*

The following functions are provided in this file:
     SbMiLsbCfgCfm      Configuration Confirm
     SbMiLsbCntrlCfm    Control Confirm
     SbMiLsbStsCfm      Statistics Confirm
     SbMiLsbStaInd      Status Indication
     SbMiLsbStaCfm      Status Confirm
     SbMiLsbTrcInd      Trace Indication

It should be noted that not all of these functions may be required
by a particular layer management service user.

It is assumed that the following functions are provided in TUCL

     SbMiLsbCfgReq      Configure Request
     SbMiLsbCntrlReq    Control Request
     SbMiLsbStsReq      Statistics Request
     SbMiLsbStaReq      Status Request

*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm_hash.h"       /* common hashing */
#include "cm_llist.h"      /* common linked list */
#include "lsb.h"           /* layer management SCTP */
#include "cm_err.h"        /* common error */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"        /* common DNS defines */
#ifdef SB_FTHA
#include "sht.h"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "sct.h"           /* sct interface */
#include "hit.h"           /* hit interface */
#include "sb_mtu.h"
#include "sb.h"            /* SCTP defines */
#include "sb_err.h"        /* SB error */

/* header/extern include files (.x) */

#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */
#include "cm_hash.x"       /* common hashing */
#include "cm_llist.x"      /* common linked list */
#include "cm_tpt.x"        /* common transport address */
#include "cm_dns.x"        /* common DNS */
#include "cm5.x"           /* common timer  */
#ifdef SB_FTHA
#include "sht.x"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "hit.x"           /* hit interface */
#include "sct.x"           /* sct interface */
#include "lsb.x"           /* layer management SCTP */
#include "sb_mtu.x"
#include "sb.x"            /* SCTP typedefs */

/* local externs */


#define MAXSBMI  2

#ifndef LCSBMILSB
#define PTSBMILSB
#else
#ifndef SM
#define PTSBMILSB
#endif
#endif

/* sb022.103: c++ compilation error fix */
#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus */

#ifdef PTSBMILSB

/* declaration of portable functions */
PRIVATE S16 PtMiLsbCfgCfm     ARGS((Pst *pst, SbMgmt  *cfg));
PRIVATE S16 PtMiLsbCntrlCfm   ARGS((Pst *pst, SbMgmt *cntrl));
PRIVATE S16 PtMiLsbStaCfm     ARGS((Pst *pst, SbMgmt *sta));
PRIVATE S16 PtMiLsbStaInd     ARGS((Pst *pst, SbMgmt *usta));
PRIVATE S16 PtMiLsbStsCfm     ARGS((Pst *pst, SbMgmt *sts));
PRIVATE S16 PtMiLsbTrcInd     ARGS((Pst *pst, SbMgmt *trc));

#endif /* PTSBMILSB */
#ifdef SB_FTHA   
#ifndef SH
PRIVATE S16 PtSbMiShtCntrlCfm    ARGS((Pst *pst, ShtCntrlCfmEvnt *cfmInfo));
#endif
#endif /* SB_FTHA */

/* sb022.103: c++ compilation error fix */
#ifdef __cplusplus
}
#endif /*__cplusplus */


/*
  The following matrices define the mapping between the primitives
  called by the layer Manager interface of SCTP Layer
  and the corresponding primitives of the SCTP Layer

  The parameter MAXSBMI defines the maximum number of service users on
  top of SCTP Layer. There is an array of functions
  per primitive invoked by SCTP Layer. Every array is
  MAXSBMI long(i.e.there are as many functions as the number of service
  users).

  The dispatching is performed by the configurable variable: selector.
  The selector is configured on a per SAP basis.

  The selectors are:

   0 - loosely coupled (#define LCSBMILSB)
   1 - Lsb (#define SM)

*/



/* Configuration Confirm primitive */

PRIVATE LsbCfgCfm SbMiLsbCfgCfmMt[MAXSBMI] =
{
#ifdef LCSBMILSB
   cmPkLsbCfgCfm,          /* 0 - loosely coupled  */
#else
   PtMiLsbCfgCfm,          /* 0 - tightly coupled, portable */
#endif
#ifdef SM
   SmMiLsbCfgCfm,          /* 1 - tightly coupled, layer management */
#else
   PtMiLsbCfgCfm,          /* 1 - tightly coupled, portable */
#endif
};

/* Control Confirm primitive */

PRIVATE LsbCntrlCfm SbMiLsbCntrlCfmMt[MAXSBMI] =
{
#ifdef LCSBMILSB
   cmPkLsbCntrlCfm,          /* 0 - loosely coupled  */
#else
   PtMiLsbCntrlCfm,          /* 0 - tightly coupled, portable */
#endif
#ifdef SM
   SmMiLsbCntrlCfm,          /* 1 - tightly coupled, layer management */
#else
   PtMiLsbCntrlCfm,          /* 1 - tightly coupled, portable */
#endif
};

/* Statistics Confirm primitive */

PRIVATE LsbStsCfm SbMiLsbStsCfmMt[MAXSBMI] =
{
#ifdef LCSBMILSB
   cmPkLsbStsCfm,          /* 0 - loosely coupled  */
#else
   PtMiLsbStsCfm,          /* 0 - tightly coupled, portable */
#endif
#ifdef SM
   SmMiLsbStsCfm,          /* 1 - tightly coupled, layer management */
#else
   PtMiLsbStsCfm,          /* 1 - tightly coupled, portable */
#endif
};

/* Status Indication primitive */

PRIVATE LsbStaInd SbMiLsbStaIndMt[MAXSBMI] =
{
#ifdef LCSBMILSB
   cmPkLsbStaInd,          /* 0 - loosely coupled  */
#else
   PtMiLsbStaInd,          /* 0 - tightly coupled, portable */
#endif
#ifdef SM
   SmMiLsbStaInd,          /* 1 - tightly coupled, layer management */
#else
   PtMiLsbStaInd,          /* 1 - tightly coupled, portable */
#endif
};

/* Status Confirm primitive */

PRIVATE LsbStaCfm SbMiLsbStaCfmMt[MAXSBMI] =
{
#ifdef LCSBMILSB
   cmPkLsbStaCfm,          /* 0 - loosely coupled  */
#else
   PtMiLsbStaCfm,          /* 0 - tightly coupled, portable */
#endif
#ifdef SM
   SmMiLsbStaCfm,          /* 1 - tightly coupled, layer management */
#else
   PtMiLsbStaCfm,          /* 1 - tightly coupled, portable */
#endif
};

/* Trace Indication primitive */

PRIVATE LsbTrcInd SbMiLsbTrcIndMt[MAXSBMI] =
{
#ifdef LCSBMILSB
   cmPkLsbTrcInd,          /* 0 - loosely coupled  */
#else
   PtMiLsbTrcInd,          /* 0 - tightly coupled, portable */
#endif
#ifdef SM
   SmMiLsbTrcInd,          /* 1 - tightly coupled, layer management */
#else
   PtMiLsbTrcInd,          /* 1 - tightly coupled, portable */
#endif
};

#ifdef SB_FTHA             
/* System agent control Confirm primitive */
PRIVATE ShtCntrlCfm SbMiShtCntrlCfmMt[MAXSBMI] =
{
   cmPkMiShtCntrlCfm,               /* 0 - loosely coupled          */

#ifdef SH
   ShMiShtCntrlCfm,                 /* 1 - tightly coupled system agent */
#else
   PtSbMiShtCntrlCfm,               /* 1 - tightly coupled, portable*/
#endif
};
#endif /* SB_FTHA */




/*
*     Layer Management Interface Functions
*/


/*
*
*       Fun:   Configuration confirm
*
*       Desc:  Tsbs function is used to send a configuration confirm
*              to the layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sb_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 SbMiLsbCfgCfm
(
Pst     *pst,            /* post structure */
SbMgmt  *cfg             /* configuration */
)
#else
PUBLIC S16 SbMiLsbCfgCfm(pst, cfg)
Pst     *pst;            /* post structure */
SbMgmt  *cfg;            /* configuration */
#endif
{
   TRC3(SbMiLsbCfgCfm)
   /* sb061.102 - remove compiler warnings */
   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
         "SbMiLsbCfgCfm(pst, cfg(%p))\n", (Void *)cfg));

   /* jump to specific primitive depending on configured selector */
   RETVALUE( (*SbMiLsbCfgCfmMt[pst->selector]) (pst, cfg) );
} /* end of SbMiLsbCfgCfm */


/*
*
*       Fun:   Control confirm
*
*       Desc:  Tsbs function is used to send a control confirm
*              to the layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sb_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 SbMiLsbCntrlCfm
(
Pst     *pst,            /* post structure */
SbMgmt  *cntrl           /* control */
)
#else
PUBLIC S16 SbMiLsbCntrlCfm(pst, cntrl)
Pst     *pst;            /* post structure */
SbMgmt  *cntrl;          /* control */
#endif
{
   TRC3(SbMiLsbCntrlCfm)

   /* sb061.102 - remove compiler warnings */
   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
         "SbMiLsbCntrlCfm(pst, cntrl(%p))\n", (Void *)cntrl));

   /* jump to specific primitive depending on configured selector */
   RETVALUE( (*SbMiLsbCntrlCfmMt[pst->selector]) (pst, cntrl) );
} /* end of SbMiLsbCntrlCfm */


/*
*
*       Fun:   Status Indication
*
*       Desc:  Tsbs function is used to indicate the status
*              to the layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sb_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 SbMiLsbStaInd
(
Pst     *pst,            /* post structure */
SbMgmt  *usta             /* unsolicited status */
)
#else
PUBLIC S16 SbMiLsbStaInd(pst, usta)
Pst     *pst;            /* post structure */
SbMgmt  *usta;            /* unsolicited status */
#endif
{
   TRC3(SbMiLsbStaInd)

   /* sb061.102 - remove compiler warnings */
   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
          "SbMiLsbStaInd(pst, usta(%p))\n", (Void *)usta));

   /* jump to specific primitive depending on configured selector */
   RETVALUE( (*SbMiLsbStaIndMt[pst->selector]) (pst, usta) );
} /* end of SbMiLsbStaInd */


/*
*
*       Fun:   Status Confirm
*
*       Desc:  Tsbs function is used to return the status
*              to layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sb_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 SbMiLsbStaCfm
(
Pst     *pst,            /* post structure */
SbMgmt  *sta              /* solicited status */
)
#else
PUBLIC S16 SbMiLsbStaCfm(pst, sta)
Pst     *pst;            /* post structure */
SbMgmt  *sta;             /* solicited status */
#endif
{
   TRC3(SbMiLsbStaCfm)

   /* sb061.102 - remove compiler warnings */
   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
          "SbMiLsbStaCfm(pst, sta (0x%p))\n",  (Void *)sta));

   /* jump to specific primitive depending on configured selector */
   RETVALUE( (*SbMiLsbStaCfmMt[pst->selector]) (pst, sta) );
} /* end of SbMiLsbStaCfm */

/*
*
*       Fun:   Statistics Confirm
*
*       Desc:  Tsbs function is used to return the statistics
*              to layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sb_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 SbMiLsbStsCfm
(
Pst     *pst,                /* post structure */
SbMgmt  *sts                 /* statistics */
)
#else
PUBLIC S16 SbMiLsbStsCfm(pst, sts)
Pst     *pst;                /* post structure */
SbMgmt  *sts;                /* statistics */
#endif
{
   TRC3(SbMiLsbStsCfm)

   /* sb061.102 - remove compiler warnings */
   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
         "SbMiLsbStsCfm(pst, sts (0x%p))\n", (Void *)sts));

   /* jump to specific primitive depending on configured selector */
   RETVALUE( (*SbMiLsbStsCfmMt[pst->selector]) (pst, sts) );
} /* end of SbMiLsbStsCfm */


/*
*
*       Fun:   Trace Indication
*
*       Desc:  Tsbs function is used to indicate the trace
*              to the layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sb_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 SbMiLsbTrcInd
(
Pst     *pst,            /* post structure */
SbMgmt  *trc              /* unsolicited status */
)
#else
PUBLIC S16 SbMiLsbTrcInd(pst, trc)
Pst     *pst;            /* post structure */
SbMgmt  *trc;             /* unsolicited status */
#endif
{
   TRC3(SbMiLsbTrcInd)

   /* sb061.102 - remove compiler warnings */
   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
         "SbMiLsbTrcInd(pst, trc (0x%p))\n", (Void *)trc));

   /* jump to specific primitive depending on configured selector */
   RETVALUE( (*SbMiLsbTrcIndMt[pst->selector]) (pst, trc) );
} /* end of SbMiLsbTrcInd */

#ifdef SB_FTHA
/*
*
*       Fun:   System agent control Confirm
*
*       Desc:  This function is used to send the system agent control confirm 
*              primitive
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  it_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 SbMiShtCntrlCfm
(
Pst             *pst,        /* post structure */
ShtCntrlCfmEvnt *cfmInfo     /* system agent control confirm event */
)
#else
PUBLIC S16 SbMiShtCntrlCfm(pst, cfmInfo)
Pst             *pst;        /* post structure */
ShtCntrlCfmEvnt *cfmInfo;    /* system agent control confirm event */
#endif
{
   TRC3(SbMiShtCntrlCfm)

   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,\
          "SbMiShtCntrlCfm(pst, cfmInfo)\n"));

   /* jump to specific primitive depending on configured selector */
   (*SbMiShtCntrlCfmMt[pst->selector])(pst, cfmInfo); 

   RETVALUE(ROK);
} /* end of SbMiShtCntrlCfm */ 
#endif /* SB_FTHA */

#ifdef PTSBMILSB

/*
*
*       Fun:   Portable Configuration confirm
*
*       Desc:
*
*       Ret:   None
*
*       Notes: None
*
*       File:  sb_ptmi.c
*
*/

#ifdef ANSI
PRIVATE S16 PtMiLsbCfgCfm
(
Pst     *pst,              /* post structure */
SbMgmt  *cfg               /* configuration */
)
#else
PRIVATE S16 PtMiLsbCfgCfm(pst, cfg)
Pst     *pst;              /* post structure */
SbMgmt  *cfg;              /* configuration */
#endif
{
   TRC3(PtMiLsbCfgCfm)

   UNUSED(pst);
   UNUSED(cfg);

#if (ERRCLASS & ERRCLS_DEBUG)
   SBLOGERROR(ERRCLS_DEBUG, ESB366, (ErrVal)0,
              "PtMiLsbCfgCfm: Failed");
#endif
   RETVALUE(ROK);
} /* end of PtMiLsbCfgCfm */


/*
*
*       Fun:   Portable Control confirm
*
*       Desc:
*
*       Ret:   None
*
*       Notes: None
*
*       File:  sb_ptmi.c
*
*/

#ifdef ANSI
PRIVATE S16 PtMiLsbCntrlCfm
(
Pst     *pst,              /* post structure */
SbMgmt  *cntrl             /* control */
)
#else
PRIVATE S16 PtMiLsbCntrlCfm(pst, cntrl)
Pst     *pst;              /* post structure */
SbMgmt  *cntrl;            /* control */
#endif
{
  TRC3(PtMiLsbCntrlCfm)

  UNUSED(pst);
  UNUSED(cntrl);

#if (ERRCLASS & ERRCLS_DEBUG)
  SBLOGERROR(ERRCLS_DEBUG, ESB367, (ErrVal)0,
             "PtMiLsbCntrlCfm: Failed");
#endif
  RETVALUE(ROK);
} /* end of PtMiLsbCntrlCfm */

/*
*
*       Fun:   Portable Status Confirm
*
*       Desc:
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sb_ptmi.c
*
*/

#ifdef ANSI
PRIVATE S16 PtMiLsbStaCfm
(
Pst     *pst,              /* post structure */
SbMgmt  *sta                /* solicited status */
)
#else
PRIVATE S16 PtMiLsbStaCfm(pst, sta)
Pst     *pst;              /* post structure */
SbMgmt  *sta;               /* solicited status */
#endif
{
   TRC3(PtMiLsbStaCfm);

   UNUSED(pst);
   UNUSED(sta);


#if (ERRCLASS & ERRCLS_DEBUG)
  SBLOGERROR(ERRCLS_DEBUG, ESB368, (ErrVal)0,
             "PtMiLsbStaCfm: Failed");
#endif

   RETVALUE(ROK);
} /* end of PtMiLsbStaCfm */


/*
*
*       Fun:   Portable Status Indication
*
*       Desc:
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sb_ptmi.c
*
*/

#ifdef ANSI
PRIVATE S16 PtMiLsbStaInd
(
Pst     *pst,                /* post structure */
SbMgmt  *usta                /* unsolicited status */
)
#else
PRIVATE S16 PtMiLsbStaInd(pst, usta)
Pst     *pst;                /* post structure */
SbMgmt  *usta;               /* unsolicited status */
#endif
{
  TRC3(PtMiLsbStaInd);

  UNUSED(pst);
  UNUSED(usta);

#if (ERRCLASS & ERRCLS_DEBUG)
  SBLOGERROR(ERRCLS_DEBUG, ESB369, (ErrVal)0,
             "PtMiLsbStaInd: Failed");
#endif

  RETVALUE(ROK);
} /* end of PtMiLsbStaInd */


/*
*
*       Fun:   Portable Statistics Confirm
*
*       Desc:
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sb_ptmi.c
*
*/

#ifdef ANSI
PRIVATE S16 PtMiLsbStsCfm
(
Pst     *pst,              /* post structure */
SbMgmt  *sts               /* statistics */
)
#else
PRIVATE S16 PtMiLsbStsCfm(pst, sts)
Pst     *pst;              /* post structure */
SbMgmt  *sts;              /* statistics */
#endif
{
  TRC3(PtMiLsbStsCfm);

  UNUSED(pst);
  UNUSED(sts);

#if (ERRCLASS & ERRCLS_DEBUG)
  SBLOGERROR(ERRCLS_DEBUG, ESB370, (ErrVal)0,
             "PtMiLsbStsCfm: Failed");
#endif
  RETVALUE(ROK);
} /* end of PtMiLsbStsCfm */


/*
*
*       Fun:   Portable Trace Indication
*
*       Desc:
*
*       Ret:   None
*
*       Notes: None
*
*       File:  sb_ptmi.c
*
*/

#ifdef ANSI
PRIVATE S16 PtMiLsbTrcInd
(
Pst     *pst,              /* post structure */
SbMgmt  *trc              /* trace */
)
#else
PRIVATE S16 PtMiLsbTrcInd(pst, trc)
Pst     *pst;              /* post structure */
SbMgmt  *trc;               /* trace */
#endif
{
  TRC3(PtMiLsbTrcInd);

  UNUSED(pst);
  UNUSED(trc);

#if (ERRCLASS & ERRCLS_DEBUG)
  SBLOGERROR(ERRCLS_DEBUG, ESB371, (ErrVal)0,
             "PtMiLsbTrcInd: Failed");
#endif
  RETVALUE(ROK);
} /* end of PtMiLsbTrcInd */

#endif /* PTSBMILSB */


#ifdef SB_FTHA
#ifndef SH
/*
*
*       Fun:    PtSbMiShtCntrlCfm
*
*       Desc:   Dummy SHT Contrl Confirm, customize if neccessary.
*
*       Ret:    ROK     - succeeded
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   it_ptmi.c
*
*/

#ifdef ANSI
PRIVATE S16 PtSbMiShtCntrlCfm
(
Pst             *pst,         /* post structure */                      
ShtCntrlCfmEvnt *cfmInfo      /* system agent control confirm event */  
)
#else
PRIVATE S16 PtSbMiShtCntrlCfm(pst, cfmInfo)
Pst             *pst;         /* post structure */                      
ShtCntrlCfmEvnt *cfmInfo;     /* system agent control confirm event */  
#endif /* ANSI */
{
   TRC3(PtSbMiShtCntrlCfm)

#if (ERRCLASS & ERRCLS_DEBUG)
   SBLOGERROR(ERRCLS_DEBUG, ESB372, (ErrVal)0,
             "PtSbMiShtCntrlCfm: Failed");
#endif

   RETVALUE(ROK);
} /* end of PtSbMiShtCntrlCfm() */
#endif
#endif /* SB_FTHA */



/********************************************************************30**

         End of file:     sb_ptmi.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:18 2015

*********************************************************************31*/

/********************************************************************40**

        notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/

/********************************************************************60**

        revision history:

*********************************************************************61*/
/********************************************************************70**

  version    initials                   description
-----------  ---------  ------------------------------------------------

*********************************************************************71*/

/********************************************************************80**

*********************************************************************81*/
/********************************************************************90**

    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
 /main/2     ---    bk     1. initial release.
 /main/2     ---    sb     1. Modified for SCTP release based on 
                                RFC-2960 'Oct 2000.
          sb042.102 hl     1. Added change for SHT interface and Rolling
                              UpGrade
          sb061.102 pr     1. Remove compiler warnings. 
/main/3      ---   rsr/ag  1. Updated for Release of 1.3
/main/3   sb022.103 pkaX   1. C++ compilation error fix.
*********************************************************************91*/
