

/********************************************************************20**

     Name:     TCP/UDP Convergence Layer

     Type:     C source file

     Desc:     Management interface.

     File:     hi_ptmi.c

     Sid:      hi_ptmi.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:39:00 2015

     Prg:      asa

*********************************************************************21*/


/*
  
The following functions are provided in this file:
     HiMiLhiCfgCfm      Configuration Confirm
     HiMiLhiCntrlCfm    Control Confirm
     HiMiLhiStsCfm      Statistics Confirm
     HiMiLhiStaInd      Status Indication
     HiMiLhiStaCfm      Status Confirm
     HiMiLhiTrcInd      Trace Indication
   
It should be noted that not all of these functions may be required
by a particular layer management service user.

It is assumed that the following functions are provided in TUCL:
     HiMiLhiCfgReq      Configuration Request
     HiMiLhiCntrlReq    Control Request
     HiMiLhiStsReq      Statistics Request
     HiMiLhiStaReq      Status Request

*/


/* header include files (.h) */

#include "envopt.h"             /* environment options */  
#include "envdep.h"             /* environment dependent */
#include "envind.h"             /* environment independent */

#include "gen.h"                /* general layer */
#include "ssi.h"                /* system services interface */

/* external headers */
#ifdef HI_TLS
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/x509v3.h>
#endif

#include "cm_hash.h"            /* common hash list */
#include "cm_llist.h"           /* common linked list */
#include "cm5.h"                /* common timer */
#include "cm_inet.h"            /* common sockets */
#include "cm_tpt.h"             /* common transport defines */

#ifdef FTHA
#include "sht.h"                /* SHT interface */
#endif

#include "lhi.h"                /* layer management, TUCL  */
#include "hit.h"                /* HIT interface */
#ifdef HI_LKSCTP
#include "sct.h"                /* SCT interface */
#endif
#include "hi.h"                 /* TUCL internal defines */
#include "hi_err.h"             /* TUCL errors */


/* header/extern include files (.x) */

#include "gen.x"                /* general layer */
#include "ssi.x"                /* system services interface */

#include "cm_hash.x"            /* common hashing */
#include "cm_llist.x"           /* common linked list */
#include "cm_lib.x"             /* common library */
#include "cm5.x"                /* common timer */
#include "cm_inet.x"            /* common sockets */
#include "cm_tpt.x"             /* common transport typedefs */

#ifdef FTHA
#include "sht.x"                /* SHT interface */
#endif

#ifdef HI_LKSCTP
#include "sct.x"                /* SCT interface */
#endif
#include "lhi.x"                /* layer management, TUCL */
#include "hit.x"                /* HIT interface */
#include "hi.x"                 /* TUCL internal typedefs */



/* local defines */

#define MAXHIMI 2

#ifndef LCHIMILHI
#define PTHIMILHI
#else
#ifndef SM
#define PTHIMILHI
#endif
#endif



#ifdef PTHIMILHI
/* declaration of portable functions */

#ifdef __cplusplus
extern "C" {
#endif

PRIVATE S16 PtMiLhiCfgCfm     ARGS((Pst *pst, HiMngmt  *cfg));
PRIVATE S16 PtMiLhiCntrlCfm   ARGS((Pst *pst, HiMngmt *cntrl));
PRIVATE S16 PtMiLhiStaCfm     ARGS((Pst *pst, HiMngmt *sta));
PRIVATE S16 PtMiLhiStaInd     ARGS((Pst *pst, HiMngmt *usta));
PRIVATE S16 PtMiLhiStsCfm     ARGS((Pst *pst, HiMngmt *sts));
PRIVATE S16 PtMiLhiTrcInd     ARGS((Pst *pst, HiMngmt *trc, Buffer *mBuf));

#ifdef __cplusplus
}
#endif

#endif /* PTHIMILHI */

#ifdef FTHA
#ifndef SH
EXTERN S16 PtHiMiShtCntrlCfm ARGS((Pst *pst, ShtCntrlCfmEvnt *cfmInfo));
#endif
#endif


/*
  The following matrices define the mapping between the primitives
  called by the upper interface of TUCL and the corresponding
  primitives of the TCP UDP Convergence Layer service user(s).

  The parameter MAXHIMI defines the maximum number of service
  users on top of TUCL. There is an array of functions per
  primitive invoked by TUCL. Every array is MAXHIMI long (i.e.
  there are as many functions as the number of service users).

  The dispatching is performed by the configurable variable:
  selector. The selector is configured on a per SAP basis.

  The selectors are:

   0 - loosely coupled (#define LCHIMILHI) 1 - LHI (#define SM)

*/



/* Configuration Confirm */
 
PRIVATE LhiCfgCfm HiMiLhiCfgCfmMt[MAXHIMI] =
{
#ifdef LCHIMILHI
   cmPkLhiCfgCfm,          /* 0 - loosely coupled  */
#else
   PtMiLhiCfgCfm,          /* 0 - tightly coupled, portable */
#endif
#ifdef SM
   SmMiLhiCfgCfm,          /* 1 - tightly coupled, layer management */
#else
   PtMiLhiCfgCfm,          /* 1 - tightly coupled, portable */
#endif
};

/* Control Confirm */
 
PRIVATE LhiCntrlCfm HiMiLhiCntrlCfmMt[MAXHIMI] =
{
#ifdef LCHIMILHI
   cmPkLhiCntrlCfm,          /* 0 - loosely coupled  */
#else
   PtMiLhiCntrlCfm,          /* 0 - tightly coupled, portable */
#endif
#ifdef SM
   SmMiLhiCntrlCfm,          /* 1 - tightly coupled, layer management */
#else
   PtMiLhiCntrlCfm,          /* 1 - tightly coupled, portable */
#endif
};

/* Statistics Confirm */
 
PRIVATE LhiStsCfm HiMiLhiStsCfmMt[MAXHIMI] =
{
#ifdef LCHIMILHI
   cmPkLhiStsCfm,          /* 0 - loosely coupled  */
#else
   PtMiLhiStsCfm,          /* 0 - tightly coupled, portable */
#endif
#ifdef SM
   SmMiLhiStsCfm,          /* 1 - tightly coupled, layer management */
#else
   PtMiLhiStsCfm,          /* 1 - tightly coupled, portable */
#endif
};

/* Status Indication */
 
PRIVATE LhiStaInd HiMiLhiStaIndMt[MAXHIMI] =
{
#ifdef LCHIMILHI
   cmPkLhiStaInd,          /* 0 - loosely coupled  */
#else
   PtMiLhiStaInd,          /* 0 - tightly coupled, portable */
#endif
#ifdef SM
   SmMiLhiStaInd,          /* 1 - tightly coupled, layer management */
#else
   PtMiLhiStaInd,          /* 1 - tightly coupled, portable */
#endif
};

/* Status Confirm */
 
PRIVATE LhiStaCfm HiMiLhiStaCfmMt[MAXHIMI] =
{
#ifdef LCHIMILHI
   cmPkLhiStaCfm,          /* 0 - loosely coupled  */
#else
   PtMiLhiStaCfm,          /* 0 - tightly coupled, portable */
#endif
#ifdef SM
   SmMiLhiStaCfm,          /* 1 - tightly coupled, layer management */
#else
   PtMiLhiStaCfm,          /* 1 - tightly coupled, portable */
#endif
};

/* Trace Indication */
 
PRIVATE LhiTrcInd HiMiLhiTrcIndMt[MAXHIMI] =
{
#ifdef LCHIMILHI
   cmPkLhiTrcInd,          /* 0 - loosely coupled  */
#else
   PtMiLhiTrcInd,          /* 0 - tightly coupled, portable */
#endif
#ifdef SM
   SmMiLhiTrcInd,          /* 1 - tightly coupled, layer management */
#else
   PtMiLhiTrcInd,          /* 1 - tightly coupled, portable */
#endif
};

#ifdef FTHA
/* System Agent Control Confirm */
PRIVATE ShtCntrlCfm HiMiShtCntrlCfmMt[MAXHIMI] =
{
   cmPkMiShtCntrlCfm,      /* 0 - loosely coupled */
#ifdef SH
   ShMiShtCntrlCfm,        /* 1 - tightly coupled system agent */
#else
   PtHiMiShtCntrlCfm,      /* 1 - tightly coupled, portable */
#endif
};


/*
*
*       Fun:   System Agent Control Confirm
*
*       Desc:  This function is used to send the system agent control confirm 
*              primitive
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  hi_ptmi.c
*
*/
#ifdef ANSI
PUBLIC S16 HiMiShtCntrlCfm
(
Pst *pst,                /* post structure */
ShtCntrlCfmEvnt *cfmInfo     /* system agent control confirm event */
)
#else
PUBLIC S16 HiMiShtCntrlCfm(pst, cfmInfo)
Pst *pst;                /* post structure */
ShtCntrlCfmEvnt *cfmInfo;    /* system agent control confirm event */
#endif
{
   TRC3(HiMiShtCntrlCfm)

   /* jump to specific primitive depending on configured selector */
   RETVALUE((*HiMiShtCntrlCfmMt[pst->selector])(pst, cfmInfo));
} /* end of HiMiShtCntrlCfm */

#ifndef SH

/*
*
*       Fun:   Portable system agent control Confirm
*
*       Desc:  This function is used to send the system agent control confirm 
*              primitive
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  hi_ptmi.c
*
*/
#ifdef ANSI
PUBLIC S16 PtHiMiShtCntrlCfm
(
Pst *pst,                /* post structure */
ShtCntrlCfmEvnt *cfmInfo     /* system agent control confirm event */
)
#else
PUBLIC S16 PtHiMiShtCntrlCfm(pst, cfmInfo)
Pst *pst;                /* post structure */
ShtCntrlCfmEvnt *cfmInfo;    /* system agent control confirm event */
#endif
{
   TRC3(PtHiMiShtCntrlCfm)

   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
         "HiMiLhiCfgCfm(pst, cfg))\n"));

   RETVALUE(ROK);
} /* end of PtHiMiShtCntrlCfm */
#endif /* SH */
#endif /* FTHA */


/*
*     Layer Management Interface Functions 
*/


/*
*
*       Fun:   Configuration confirm
*
*       Desc:  This function is used to send a configuration confirm
*              to the layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  hi_ptmi.c
*
*/
#ifdef ANSI
PUBLIC S16 HiMiLhiCfgCfm
(
Pst     *pst,            /* post structure */
HiMngmt *cfg             /* configuration */
)
#else
PUBLIC S16 HiMiLhiCfgCfm(pst, cfg)
Pst     *pst;            /* post structure */   
HiMngmt *cfg;            /* configuration */
#endif
{
   TRC3(HiMiLhiCfgCfm)

   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
         "HiMiLhiCfgCfm(pst, cfg (0x%p))\n", (Ptr)cfg));

   /* jump to specific primitive depending on configured selector */
   RETVALUE((*HiMiLhiCfgCfmMt[pst->selector])(pst, cfg)); 
} /* end of HiMiLhiCfgCfm */


/*
*
*       Fun:   Control confirm
*
*       Desc:  This function is used to send a control confirm
*              to the layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  hi_ptmi.c
*
*/
#ifdef ANSI
PUBLIC S16 HiMiLhiCntrlCfm
(
Pst     *pst,            /* post structure */
HiMngmt *cntrl           /* control */
)
#else
PUBLIC S16 HiMiLhiCntrlCfm(pst, cntrl)
Pst     *pst;            /* post structure */   
HiMngmt *cntrl;          /* control */
#endif
{
   TRC3(HiMiLhiCntrlCfm)

   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
         "HiMiLhiCntrlCfm(pst, cntrl (0x%p))\n", (Ptr)cntrl));

   /* jump to specific primitive depending on configured selector */
   RETVALUE((*HiMiLhiCntrlCfmMt[pst->selector])(pst, cntrl)); 
} /* end of HiMiLhiCntrlCfm */


/*
*
*       Fun:   Status Indication
*
*       Desc:  This function is used to indicate the status
*              to the layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  hi_ptmi.c
*
*/
#ifdef ANSI
PUBLIC S16 HiMiLhiStaInd
(
Pst     *pst,            /* post structure */
HiMngmt *usta             /* unsolicited status */
)
#else
PUBLIC S16 HiMiLhiStaInd(pst, usta)
Pst     *pst;            /* post structure */   
HiMngmt *usta;            /* unsolicited status */
#endif
{
   TRC3(HiMiLhiStaInd)

   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
          "HiMiLhiStaInd(pst, usta (0x%p))\n", (Ptr)usta));

   /* jump to specific primitive depending on configured selector */
   RETVALUE((*HiMiLhiStaIndMt[pst->selector])(pst, usta)); 
} /* end of HiMiLhiStaInd */


/*
*
*       Fun:   Status Confirm
*
*       Desc:  This function is used to return the status 
*              to layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  hi_ptmi.c
*
*/
#ifdef ANSI
PUBLIC S16 HiMiLhiStaCfm
(
Pst     *pst,            /* post structure */     
HiMngmt *sta              /* solicited status */
)
#else
PUBLIC S16 HiMiLhiStaCfm(pst, sta)
Pst     *pst;            /* post structure */     
HiMngmt *sta;             /* solicited status */
#endif
{
   TRC3(HiMiLhiStaCfm)

   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
          "HiMiLhiStaCfm(pst, sta (0x%p))\n", (Ptr)sta));

   /* jump to specific primitive depending on configured selector */
   RETVALUE((*HiMiLhiStaCfmMt[pst->selector])(pst, sta)); 
} /* end of HiMiLhiStaCfm */


/*
*
*       Fun:   Statistics Confirm
*
*       Desc:  This function is used to return the statistics 
*              to layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  hi_ptmi.c
*
*/
#ifdef ANSI
PUBLIC S16 HiMiLhiStsCfm
(
Pst     *pst,                /* post structure */    
HiMngmt *sts                 /* statistics */
)
#else
PUBLIC S16 HiMiLhiStsCfm(pst, sts)
Pst     *pst;                /* post structure */    
HiMngmt *sts;                /* statistics */
#endif
{
   TRC3(HiMiLhiStsCfm)

   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
         "HiMiLhiStsCfm(pst, sts (0x%p))\n", (Ptr)sts));

   /* jump to specific primitive depending on configured selector */
   RETVALUE((*HiMiLhiStsCfmMt[pst->selector])(pst, sts)); 
} /* end of HiMiLhiStsCfm */


/*
*
*       Fun:   Trace Indication
*
*       Desc:  This function is used to indicate the trace 
*              to the layer management.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  hi_ptmi.c
*
*/
#ifdef ANSI
PUBLIC S16 HiMiLhiTrcInd
(
Pst     *pst,            /* post structure */
HiMngmt *trc,             /* unsolicited status */
Buffer  *mBuf              /* message buffer */ 
)
#else
PUBLIC S16 HiMiLhiTrcInd(pst, trc, mBuf)
Pst     *pst;            /* post structure */   
HiMngmt *trc;             /* unsolicited status */
Buffer  *mBuf;             /* message buffer */ 
#endif
{
   TRC3(HiMiLhiTrcInd)

   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
         "HiMiLhiTrcInd(pst, trc (0x%p))\n", (Ptr)trc));

   /* jump to specific primitive depending on configured selector */
   RETVALUE((*HiMiLhiTrcIndMt[pst->selector])(pst, trc, mBuf)); 
} /* end of HiMiLhiTrcInd */ 

#ifdef PTHIMILHI

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
*       File:  hi_ptmi.c
*
*/
#ifdef ANSI
PRIVATE S16 PtMiLhiCfgCfm
(
Pst     *pst,              /* post structure */
HiMngmt *cfg               /* configuration */
)
#else
PRIVATE S16 PtMiLhiCfgCfm(pst, cfg)
Pst     *pst;              /* post structure */
HiMngmt *cfg;              /* configuration */
#endif
{
   TRC3(PtMiLhiCfgCfm)

   UNUSED(pst);
   UNUSED(cfg);

#if (ERRCLASS & ERRCLS_DEBUG)
   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
         "PtMiLhiCfgCfm () Failed\n"));
#endif

   RETVALUE(ROK);
} /* end of PtMiLhiCfgCfm */


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
*       File:  hi_ptmi.c
*
*/
#ifdef ANSI
PRIVATE S16 PtMiLhiCntrlCfm
(
Pst     *pst,              /* post structure */
HiMngmt *cntrl             /* control */
)
#else
PRIVATE S16 PtMiLhiCntrlCfm(pst, cntrl)
Pst     *pst;              /* post structure */
HiMngmt *cntrl;            /* control */
#endif
{
   TRC3(PtMiLhiCntrlCfm)

   UNUSED(pst);
   UNUSED(cntrl);

#if (ERRCLASS & ERRCLS_DEBUG)
   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
         "PtMiLhiCntrlCfm () Failed\n"));
#endif

   RETVALUE(ROK);
} /* end of PtMiLhiCntrlCfm */

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
*       File:  hi_ptmi.c
*
*/
#ifdef ANSI
PRIVATE S16 PtMiLhiStaCfm
(
Pst     *pst,              /* post structure */
HiMngmt *sta                /* solicited status */
)
#else
PRIVATE S16 PtMiLhiStaCfm(pst, sta)
Pst     *pst;              /* post structure */
HiMngmt *sta;               /* solicited status */
#endif
{
   TRC3(PtMiLhiStaCfm)

   UNUSED(pst);
   UNUSED(sta);

#if (ERRCLASS & ERRCLS_DEBUG)
   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
         "PtMiLhiStaCfm () Failed\n"));
#endif

   RETVALUE(ROK);
} /* end of PtMiLhiStaCfm */


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
*       File:  hi_ptmi.c
*
*/
#ifdef ANSI
PRIVATE S16 PtMiLhiStaInd
(
Pst     *pst,               /* post structure */
HiMngmt *usta                /* unsolicited status */
)
#else
PRIVATE S16 PtMiLhiStaInd(pst, usta)
Pst     *pst;               /* post structure */
HiMngmt *usta;               /* unsolicited status */
#endif
{
   TRC3(PtMiLhiStaInd)

   UNUSED(pst);
   UNUSED(usta);

#if (ERRCLASS & ERRCLS_DEBUG)
   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
         "PtMiLhiStaInd () Failed\n"));
#endif

   RETVALUE(ROK);
} /* end of PtMiLhiStaInd */


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
*       File:  hi_ptmi.c
*
*/
#ifdef ANSI
PRIVATE S16 PtMiLhiStsCfm
(
Pst     *pst,              /* post structure */
HiMngmt *sts               /* statistics */
)
#else
PRIVATE S16 PtMiLhiStsCfm(pst, sts)
Pst     *pst;              /* post structure */
HiMngmt *sts;              /* statistics */
#endif
{
   TRC3(PtMiLhiStsCfm)

   UNUSED(pst);
   UNUSED(sts);

#if (ERRCLASS & ERRCLS_DEBUG)
   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
        "PtMiLhiStsCfm () Failed\n"));
#endif

  RETVALUE(ROK);
} /* end of PtMiLhiStsCfm */


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
*       File:  hi_ptmi.c
*
*/
#ifdef ANSI
PRIVATE S16 PtMiLhiTrcInd
(
Pst     *pst,              /* post structure */
HiMngmt *trc,              /* trace */
Buffer  *mBuf              /* message buffer */ 
)
#else
PRIVATE S16 PtMiLhiTrcInd(pst, trc, mBuf)
Pst     *pst;              /* post structure */
HiMngmt *trc;               /* trace */
Buffer  *mBuf;             /* message buffer */ 
#endif
{
   TRC3(PtMiLhiTrcInd)

   UNUSED(pst);
   UNUSED(trc);

#if (ERRCLASS & ERRCLS_DEBUG)
   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
         "PtMiLhiTrcInd () Failed\n"));
#endif

   RETVALUE(ROK);
} /* end of PtMiLhiTrcInd */

#endif /* PTHIMILHI */


/********************************************************************30**

         End of file:     hi_ptmi.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:39:00 2015

*********************************************************************31*/

/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/

/********************************************************************60**

        Revision History:

*********************************************************************61*/
/********************************************************************90**

    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
1.1         ---      asa  1. initial release.
/main/2     ---      cvp  1. changed the copyright header.
            /main/4  cvp  1. changes for sht interface. 
/main/4     ---      cvp  1. changed the copyright header.
/main/5      ---      kp   1. Updated for release 1.5.
/main/6      ---       hs   1. Updated for release of 2.1
*********************************************************************91*/

