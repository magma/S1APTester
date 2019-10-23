
/********************************************************************20**

     Name:     eGTP Protocol - upper interface

     Type:     C source file

     Desc:     C Source code for the eGTP Protocol upper interface primitives.

     File:     eg_ptui.c

     Sid:      eg_ptui.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:48 2015

     Prg:      kc

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
/* eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_psf.h"
#include "sht.h"
#endif
#include "egt.h"           /* eGTP Upper Interface */
#include "leg.h"           /* eGTP LM Interface */
#include "eg.h"            /* eGTP Layer */
#include "eg_err.h"        /* Error codes */
#include "eg_util.h"       /* eGTP Utility library */
#include "eg_edm.h"        /* EDM Module structures            */
#ifdef TIME_MES
#include <time.h>
#endif

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
/* eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#include "sht.x"
#endif
#include "egt.x"           /* eGTP Upper Interface */
#include "leg.x"           /* eGTP LM Interface */
#include "eg_edm.x"        /* EDM Module structures            */
#include "eg.x"            /* eGTP Layer */
#include "eg_util.x"       /* eGTP Utility library */
/* eg004.201 Header files added for eGTP-C PSF*/
#include "eg_tpt.x"            /* EGTP TPT module defines */
#ifdef HW
#include "lhw.x"
#include "hw.x"          /* EGTPC UA                       */
#endif

/* local function definition */

/* local defines */
#define EG_MAX_UIEGT_SEL      3

#if (!defined(LWLCEGUIEGT) || !defined(LCEGUIEGT))
#define PTEGUIEGT
#else
#ifndef EU
#define PTEGUIEGT
#else
#endif
#endif

#ifdef __cplusplus
EXTERN "C" {
#endif /* end of __cplusplus */

#ifdef PTEGUIEGT

/* portable functions */
PRIVATE S16 PtUiEgtBndCfm ARGS (( Pst *pst, SuId suId, U8 status));

#ifdef EGTP_U
PUBLIC S16 PtUiEgtEguLclTnlMgmtCfm ARGS((Pst *pst, SuId suId, EgtUEvnt *egtUEvnt));
PUBLIC S16 PtUiEgtEguStaCfm ARGS((Pst *pst, SuId suId, EgtUEvnt *egtUEvnt));
PUBLIC S16 PtUiEgtEguUStaInd ARGS((Pst *pst, SuId suId, EgtUEvnt *egtUEvnt));
PUBLIC S16 PtUiEgtEguErrInd ARGS((Pst *pst, SuId suId, EgtUEvnt *egtUEvnt));
PUBLIC S16 PtUiEgtEguDatInd ARGS((Pst *pst, SuId suId, EgtUEvnt *egtUEvnt));
#endif
#endif /*PTEGUIEGT */

#ifdef __cplusplus
} /* end of EXTERN "C" */
#endif /* end of __cplusplus */

/*
   The following matrices define the mapping between the primitives
   called by the upper interface of eGTP Base Protocol layer and
   the corresponding primitives of the eGTP Base Protocol layer
   service user(s).

   The parameter EG_MAX_UIEGT_SEL defines the maximum number of service users on
   top of eGTP Base Protocol. There is an array of functions per
   primitive invoked by eGTP Base Protocol. Every array is EG_MAX_UIEGT_SEL
   long (i.e. there are as many functions as the number of service users).

   The dispatching is performed by the configurable variable: selector.
   The selector is configured on a per SAP basis. The selectors are:

   EGT_SEL_LC - loosely coupled
   EGT_SEL_TC - tightly coupled

*/

/* Bind Confirm primitive */
PRIVATE CONSTANT EgtBndCfm EgUiEgtBndCfmMt [EG_MAX_UIEGT_SEL] =
{
#ifdef LCEGUIEGT
   cmPkEgtBndCfm,          /* 0 - loosely coupled */
#else
   PtUiEgtBndCfm,          /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCEGUIEGT
   cmPkEgtBndCfm,          /* 1 - loosely coupled */
#else
   PtUiEgtBndCfm,          /* 0 - loosely coupled, portable */
#endif
#ifdef EU
   EuLiEgtBndCfm,          /* 1 - tightly coupled, service user EU */
#else
   PtUiEgtBndCfm,          /* 1 - tightly coupled, portable */
#endif
};

#ifdef EGTP_U

/* Delete Local Tunnel primitive */
PRIVATE CONSTANT EgtEguLclTnlMgmtCfm EgUiEgtEguLclTnlMgmtCfmMt[EG_MAX_UIEGT_SEL] =
{
#ifdef LCEGUIEGT
   cmPkEgtEguLclTnlMgmtCfm,          /* 0 - loosely coupled */
#else
   PtUiEgtEguLclTnlMgmtCfm,          /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCEGUIEGT
   cmPkEgtEguLclTnlMgmtCfm,          /* 1 - loosely coupled */
#else
   PtUiEgtEguLclTnlMgmtCfm,          /* 1 - loosely coupled, portable */
#endif
#ifdef EU
   EuLiEgtEguLclTnlMgmtCfm,          /* 1 - tightly coupled, service user EU */
#else
   PtUiEgtEguLclTnlMgmtCfm,          /* 1 - tightly coupled, portable */
#endif
};


/* Delete Local Tunnel primitive */
PRIVATE CONSTANT EgtEguStaCfm EgUiEgtEguStaCfmMt[EG_MAX_UIEGT_SEL] =
{
#ifdef LCEGUIEGT
   cmPkEgtEguStaCfm,          /* 0 - loosely coupled */
#else
   PtUiEgtEguStaCfm,          /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCEGUIEGT
   cmPkEgtEguStaCfm,          /* 1 - loosely coupled */
#else
   PtUiEgtEguStaCfm,          /* 1 - loosely coupled, portable */
#endif
#ifdef EU
   EuLiEgtEguStaCfm,          /* 1 - tightly coupled, service user EU */
#else
   PtUiEgtEguStaCfm,          /* 1 - tightly coupled, portable */
#endif
};

/* Delete Local Tunnel primitive */
PRIVATE CONSTANT EgtEguUStaInd EgUiEgtEguUStaIndMt[EG_MAX_UIEGT_SEL] =
{
#ifdef LCEGUIEGT
   cmPkEgtEguUStaInd,          /* 0 - loosely coupled */
#else
   PtUiEgtEguUStaInd,          /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCEGUIEGT
   cmPkEgtEguUStaInd,          /* 1 - loosely coupled */
#else
   PtUiEgtEguUStaInd,          /* 1 - loosely coupled, portable */
#endif
#ifdef EU
   EuLiEgtEguUStaInd,          /* 1 - tightly coupled, service user EU */
#else
   PtUiEgtEguUStaInd,          /* 1 - tightly coupled, portable */
#endif
};



PRIVATE CONSTANT EgtEguErrInd EgUiEgtEguErrIndMt[EG_MAX_UIEGT_SEL] =
{
#ifdef LCEGUIEGT
   cmPkEgtEguErrInd,          /* 0 - loosely coupled */
#else
   PtUiEgtEguErrInd,          /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCEGUIEGT
   cmPkEgtEguErrInd,          /* 1 - loosely coupled */
#else
   PtUiEgtEguErrInd,          /* 1 - loosely coupled, portable */
#endif
#ifdef EU
   EuLiEgtEguErrInd,          /* 1 - tightly coupled, service user EU */
#else
   PtUiEgtEguErrInd,          /* 1 - tightly coupled, portable */
#endif
};

PRIVATE CONSTANT EgtEguDatInd EgUiEgtEguDatIndMt[EG_MAX_UIEGT_SEL] =
{
#ifdef LCEGUIEGT
   cmPkEgtEguDatInd,          /* 0 - loosely coupled */
#else
   PtUiEgtEguDatInd,          /* 0 - loosely coupled, portable */
#endif
#ifdef LWLCEGUIEGT
   cmPkEgtEguDatInd,          /* 1 - loosely coupled */
#else
   PtUiEgtEguDatInd,          /* 1 - loosely coupled, portable */
#endif
#ifdef EU
   EuLiEgtEguDatInd,          /* 1 - tightly coupled, service user EU */
#else
   PtUiEgtEguDatInd,          /* 1 - tightly coupled, portable */
#endif
};

#endif /* EGTP_U */















/* Primitive Mapping Dispatching Functions */


/*
*
*       Fun:   EgUiEgtBndCfm
*
*       Desc:  This function resolves the EgtBndCfm primitive
*
*       Ret:  ROK -      ok
*
*       Notes: none
*
*       File:  eg_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 EgUiEgtBndCfm
(
Pst  *pst,              /* post structure */
SuId suId,              /* service user id */
U8   status             /* status of bind request */
)
#else
PUBLIC S16 EgUiEgtBndCfm (pst, suId, status)
Pst   *pst;              /* post structure */
SuId  suId;              /* service user id */
U8    status;            /* status of bind request */
#endif
{
   TRC3(EgUiEgtBndCfm);

   EGDBGP(DBGMASK_UI, (egCb.init.prntBuf,
          "EgUiEgtBndCfm(pst, suId(%d), status(%d))\n", suId, status)); 

   (*EgUiEgtBndCfmMt[pst->selector])(pst, suId, status);

   RETVALUE(ROK);
} /* end of EgUiEgtBndCfm */


#ifdef EGTP_U

/*
*
*       Fun: EgUiEgtEguLclTnlMgmtCfm 
*
*       Desc:  This function resolves the EgtStaCfm primitive
*
*       Ret:  ROK -      ok
*
*       Notes: none
*
*       File:  eg_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 EgUiEgtEguLclTnlMgmtCfm 
(
Pst          *pst,              /* post structure */
SuId         suId,              /* service user id */
EgtUEvnt     *egtUEvnt
)
#else
PUBLIC S16 EgUiEgtEguLclTnlMgmtCfm(pst, suId, egtUEvnt)
Pst          *pst;              /* post structure */
SuId         suId;              /* service user id */
EgtUEvnt     *egtUEvnt;
#endif
{
   TRC3(EgUiEgtEguLclTnlMgmtCfm);

   EGDBGP(DBGMASK_UI, (egCb.init.prntBuf,
          "EgUiEgtStaCfm(pst, suId(%d) ...)\n", suId));

   (*EgUiEgtEguLclTnlMgmtCfmMt[pst->selector])(pst, suId, egtUEvnt);

   RETVALUE(ROK);
} /* end of EgUiEgtEguLclTnlMgmtCfm() */

/*
*
*       Fun: EgUiEgtEguStaCfm 
*
*       Desc:  
*
*       Ret:  ROK -      ok
*
*       Notes: none
*
*       File:  eg_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 EgUiEgtEguStaCfm 
(
Pst          *pst,              /* post structure */
SuId         suId,              /* service user id */
EgtUEvnt     *egtUEvnt
)
#else
PUBLIC S16 EgUiEgtEguStaCfm(pst, suId, egtUEvnt)
Pst          *pst;              /* post structure */
SuId         suId;              /* service user id */
EgtUEvnt     *egtUEvnt;
#endif
{
   TRC3(EgUiEgtStaCfm);

   EGDBGP(DBGMASK_UI, (egCb.init.prntBuf,
          "EgUiEgtStaCfm(pst, suId(%d) ...)\n", suId));

   (*EgUiEgtEguStaCfmMt[pst->selector])(pst, suId, egtUEvnt);

   RETVALUE(ROK);
} /* end of EgUiEgtEguTnlMgmtCfm() */

/*
*
*       Fun:  EgUiEgtEguUStaInd
*
*       Desc:  
*
*       Ret:  ROK -      ok
*
*       Notes: none
*
*       File:  eg_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 EgUiEgtEguUStaInd 
(
Pst          *pst,              /* post structure */
SuId         suId,              /* service user id */
EgtUEvnt     *egtUEvnt
)
#else
PUBLIC S16 EgUiEgtEguUStaInd(pst, suId, egtUEvnt)
Pst          *pst;              /* post structure */
SuId         suId;              /* service user id */
EgtUEvnt     *egtUEvnt;
#endif
{
   TRC3(EgUiEgtEguUStaInd);

   EGDBGP(DBGMASK_UI, (egCb.init.prntBuf,
          "EgUiEgtEguUStaInd(pst, suId(%d) ...)\n", suId));

   (*EgUiEgtEguUStaIndMt[pst->selector])(pst, suId, egtUEvnt);

   RETVALUE(ROK);
} /* end of EgUiEgtEguTnlMgmtCfm() */

/*
*
*       Fun:  EgUiEgtEguErrInd
*
*       Desc:  
*
*       Ret:  ROK -      ok
*
*       Notes: none
*
*       File:  eg_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 EgUiEgtEguErrInd
(
Pst          *pst,              /* post structure */
SuId         suId,              /* service user id */
EgtUEvnt     *egtUEvnt
)
#else
PUBLIC S16 EgUiEgtEguErrInd(pst, suId, egtUEvnt)
Pst          *pst;              /* post structure */
SuId         suId;              /* service user id */
EgtUEvnt     *egtUEvnt;
#endif
{
   TRC3(EgUiEgtEguErrInd);

   EGDBGP(DBGMASK_UI, (egCb.init.prntBuf,
          "EgUiEgtEguErrInd(pst, suId(%d) ...)\n", suId));

   (*EgUiEgtEguErrIndMt[pst->selector])(pst, suId, egtUEvnt);

   RETVALUE(ROK);
} /* end of EgUiEgtEguErrInd() */

/*
*
*       Fun:  EgUiEgtEguDatInd
*
*       Desc:  
*
*       Ret:  ROK -      ok
*
*       Notes: none
*
*       File:  eg_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 EgUiEgtEguDatInd 
(
Pst          *pst,              /* post structure */
SuId         suId,              /* service user id */
EgtUEvnt     *egtUEvnt
)
#else
PUBLIC S16 EgUiEgtEguDatInd(pst, suId, egtUEvnt)
Pst          *pst;              /* post structure */
SuId         suId;              /* service user id */
EgtUEvnt     *egtUEvnt;
#endif
{
#ifdef TIME_MES
#ifdef SS_MT_CB
   if(exitRx[pst->srcInst-1].call < MAX_MSG)
   {
      clock_gettime(0, &exitRx[pst->srcInst-1].time[exitRx[pst->srcInst-1].call++]);
   }
#else
   PRIVATE U32 call;
   if(call < MAX_MSG)
   {
      clock_gettime(0, &exitRx2[call]);
      call ++;
   }
#endif
#endif
   TRC3(EgUiEgtEguDatInd);

   EGDBGP(DBGMASK_UI, (egCb.init.prntBuf,
          "EgUiEgtEguDatInd(pst, suId(%d) ...)\n", suId));

   (*EgUiEgtEguDatIndMt[pst->selector])(pst, suId, egtUEvnt);

   RETVALUE(ROK);
} /* end of EgUiEgtEguDatInd() */

#endif /* EGTP_U */

#ifdef PTEGUIEGT


/*
*
*       Fun:   PtUiEgtBndCfm
*
*       Desc:  portable version of EgtBndCfm primitive
*
*       Ret:  ROK -      ok
*
*       Notes: none
*
*       File:  eg_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 PtUiEgtBndCfm
(
Pst  *pst,              /* post structure */
SuId suId,              /* service user id */
U8   status             /* status of bind request */
)
#else
PUBLIC S16 PtUiEgtBndCfm (pst, suId, status)
Pst   *pst;              /* post structure */
SuId  suId;              /* service user id */
U8    status;            /* status of bind request */
#endif
{
   TRC3(PtUiEgtBndCfm);

   EGLOGERROR(ERRCLS_DEBUG, EEG015, ERRZERO, "PtUiEgtBndCfm: Invalid selector");

   UNUSED(suId);
   UNUSED(status);

   RETVALUE(ROK);
} /* end of PtUiEgtBndCfm */

#ifdef EGTP_U

/*
*
*       Fun:  PtUiEgtEguTnlMgmtCfm 
*
*       Desc:  This function resolves the EgtStaCfm primitive
*
*       Ret:  ROK -      ok
*
*       Notes: none
*
*       File:  eg_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 PtUiEgtEguLclTnlMgmtCfm 
(
Pst          *pst,              /* post structure */
SuId         suId,              /* service user id */
EgtUEvnt     *egtUEvnt
)
#else
PUBLIC S16 PtUiEgtEguLclTnlMgmtCfm(pst, suId, egtUEvnt)
Pst          *pst;              /* post structure */
SuId         suId;              /* service user id */
EgtUEvnt     *egtUEvnt;
#endif
{
   TRC3(PtUiEgtEguLclTnlMgmtCfm);

   EGDBGP(DBGMASK_UI, (egCb.init.prntBuf,
          "EgUiEgtStaCfm(pst, suId(%d) ...)\n", suId));

   RETVALUE(ROK);
} /* end of PtUiEgtEguLclTnlMgmtCfm() */

/*
*
*       Fun: PtUiEgtEguStaCfm 
*
*       Desc:  
*
*       Ret:  ROK -      ok
*
*       Notes: none
*
*       File:  eg_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 PtUiEgtEguStaCfm 
(
Pst          *pst,              /* post structure */
SuId         suId,              /* service user id */
EgtUEvnt     *egtUEvnt
)
#else
PUBLIC S16 PtUiEgtEguStaCfm(pst, suId, egtUEvnt)
Pst          *pst;              /* post structure */
SuId         suId;              /* service user id */
EgtUEvnt     *egtUEvnt;
#endif
{
   TRC3(EgUiEgtStaCfm);

   EGDBGP(DBGMASK_UI, (egCb.init.prntBuf,
          "EgUiEgtStaCfm(pst, suId(%d) ...)\n", suId));

   RETVALUE(ROK);
} /* end of EgUiEgtEguTnlMgmtCfm() */

/*
*
*       Fun:  PtUiEgtEguUStaInd
*
*       Desc:  
*
*       Ret:  ROK -      ok
*
*       Notes: none
*
*       File:  eg_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 PtUiEgtEguUStaInd 
(
Pst          *pst,              /* post structure */
SuId         suId,              /* service user id */
EgtUEvnt     *egtUEvnt
)
#else
PUBLIC S16 PtUiEgtEguUStaInd(pst, suId, egtUEvnt)
Pst          *pst;              /* post structure */
SuId         suId;              /* service user id */
EgtUEvnt     *egtUEvnt;
#endif
{
   TRC3(PtUiEgtEguUStaInd);

   EGDBGP(DBGMASK_UI, (egCb.init.prntBuf,
          "PtUiEgtEguUStaInd(pst, suId(%d) ...)\n", suId));


   RETVALUE(ROK);
} /* end of EgUiEgtEguTnlMgmtCfm() */

/*
*
*       Fun:  PtUiEgtEguErrInd
*
*       Desc:  
*
*       Ret:  ROK -      ok
*
*       Notes: none
*
*       File:  eg_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 PtUiEgtEguErrInd
(
Pst          *pst,              /* post structure */
SuId         suId,              /* service user id */
EgtUEvnt     *egtUEvnt
)
#else
PUBLIC S16 PtUiEgtEguErrInd(pst, suId, egtUEvnt)
Pst          *pst;              /* post structure */
SuId         suId;              /* service user id */
EgtUEvnt     *egtUEvnt;
#endif
{
   TRC3(PtUiEgtEguErrInd);

   EGDBGP(DBGMASK_UI, (egCb.init.prntBuf,
          "PtUiEgtEguErrInd(pst, suId(%d) ...)\n", suId));

   RETVALUE(ROK);
} /* end of EgUiEgtEguErrInd() */


/*
*
*       Fun:  PtUiEgtEguDatInd 
*
*       Desc:  
*
*       Ret:  ROK -      ok
*
*       Notes: none
*
*       File:  eg_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 PtUiEgtEguDatInd 
(
Pst          *pst,              /* post structure */
SuId         suId,              /* service user id */
EgtUEvnt     *egtUEvnt
)
#else
PUBLIC S16 PtUiEgtEguDatInd(pst, suId, egtUEvnt)
Pst          *pst;              /* post structure */
SuId         suId;              /* service user id */
EgtUEvnt     *egtUEvnt;
#endif
{
   TRC3(PtUiEgtEguDatInd);

   EGDBGP(DBGMASK_UI, (egCb.init.prntBuf,
          "PtUiEgtEguDatInd(pst, suId(%d) ...)\n", suId));

   RETVALUE(ROK);
} /* end of PtUiEgtEguDatInd() */

#endif /* EGTP_U */
#endif /* PTEGUIEGT */

/********************************************************************30**

         End of file:     eg_ptui.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:48 2015

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
----------- -------- ---- -----------------------------------------------
/main/1      ---      ad                1. Created for Initial Release 1.1
/main/2      ---      nkottapalli       1. Initial for eGTP 1.2 Release
/main/2      eg001.102    snatarajan        1. EGTP_C Path management functionality is introduced. 
                          rss                 2. Multithreaded performance changes gaurded under SS_MT_CB flag.
/main/3      ---      pmacharla       Initial Release of eGTP 2.1 release
/main/3     eg004.201 magnihotri        1. Header files added for eGTP-C PSF
*********************************************************************91*/
