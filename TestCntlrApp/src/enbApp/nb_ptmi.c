/**********************************************************************

    Name:  LTE S1SIM - ENODEB Application Module 

    Type:  C include file

    Desc:  C source code for ENODEB Application

    File:  nb_ptmi.c

    Sid:   

    Prg:   

**********************************************************************/

#include "nb.h" 
#include "rl_interface.h"
#include "rl_common.h"
#include "nb_lnb.h"
#include "nb_log.h"

#if (!defined(LCNBMILNB) || !defined(SM) || !defined(LWLCNBMILNB))
#define PTNBMILNB
#endif

#define NB_LNB_MAX_SEL       3      /* maximum number of selectors */

/* forward references */
#ifdef PTNBMILNB
PRIVATE S16 PtMiLnbCfgCfm    (Pst *pst, LnbMngmt *cfg);
PRIVATE S16 PtMiLnbCntrlCfm  (Pst *pst, LnbMngmt *cntrl);
PRIVATE S16 PtMiLnbStaInd  (Pst *pst, LnbMngmt *usta);
#endif
/* Status Indication primitive */
PRIVATE LnbStaInd NbMiLnbStaIndMt[NB_LNB_MAX_SEL] =
{
#ifdef LCNBMILNB
   cmPkLnbStaInd,          /* 0 - loosely coupled  */
#else
   PtMiLnbStaInd,          /* 0 - loosely coupled, portable */
#endif /* LCNBMILNB */
#ifdef SM
   SmMiLnbStaInd,          /* 1 - tightly coupled, layer management */
#else
   PtMiLnbStaInd,          /* 1 - tightly coupled, portable */
#endif /* SM */
#ifdef LWLCNBMILNB
   cmPkLnbStaInd,          /* 2 - Light weight loosely coupled  */
#else
   PtMiLnbStaInd,          /* 2 - Light weight loosely, portable */
#endif /* LCNBMILNB */
};

/* private variable definitions */
PRIVATE LnbCfgCfm nbMiLnbCfgCfmMt[NB_LNB_MAX_SEL] =
{
#ifdef LCNBMILNB
   cmPkLnbCfgCfm,            /* 0 - loosely coupled  */
#else
   PtMiLnbCfgCfm,            /* 0 - loosely coupled, portable */
#endif 
#ifdef SM                                                                
   SmMiLnbCfgCfm,            /* 1 - tightly coupled, layer management */
#else                                                                    
   PtMiLnbCfgCfm,            /* 1 - tightly coupled, portable */
#endif /* SM */                                                          
#ifdef LWLCNBMILNB
   cmPkLnbCfgCfm,            /* 2 - Light weight loosely coupled  */
#else
   PtMiLnbCfgCfm,            /* 2 - Light weight loosely, portable */
#endif  
};

PRIVATE LnbCntrlCfm nbMiLnbCntrlCfmMt[NB_LNB_MAX_SEL] =
{
#ifdef LCNBMILNB
   cmPkLnbCntrlCfm,       /* 0 - loosely coupled  */
#else
   PtMiLnbCntrlCfm,       /* 0 - loosely coupled, portable */
#endif
#ifdef SM                                                             
   SmMiLnbCntrlCfm,       /* 1 - tightly coupled, layer management */
#else
   PtMiLnbCntrlCfm,       /* 1 - tightly coupled, portable */
#endif 
#ifdef LWLCNBMILNB                                                    
   cmPkLnbCntrlCfm,       /* 2 - Light weight loosely coupled  */
#else
   PtMiLnbCntrlCfm,       /* 2 - Light weight loosely, portable */
#endif
};
/*
*     layer management interface functions
*/
/*
*
*       Fun:    NbMiLnbCfgCfm
*
*       Desc:   configuration confirm
*
*       Ret:    ROK     - succeeded
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   nb_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 NbMiLnbCfgCfm
(
Pst         *pst,
LnbMngmt    *cfg
)
#else
PUBLIC S16 NbMiLnbCfgCfm(pst, cfg)
Pst         *pst;
LnbMngmt    *cfg;
#endif /* ANSI */
{
   NB_LOG_ENTERFN(&nbCb);
#if (ERRCLASS & ERRCLS_INT_PAR)
   if (pst == (Pst *)NULLP || pst->selector >= NB_LNB_MAX_SEL)
   {
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */
   RETVALUE((*nbMiLnbCfgCfmMt[pst->selector])(pst, cfg));
}

/*
*
*       Fun:    NbMiLnbCntrlCfm
*
*       Desc:   control confirm
*
*       Ret:    ROK     - succeeded
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   nb_ptmi.c
*
*/
#ifdef ANSI
PUBLIC S16 NbMiLnbCntrlCfm
(
Pst         *pst,             /* post structure */         
LnbMngmt      *cntrl            /* management structure */   
)
#else
PUBLIC S16 NbMiLnbCntrlCfm(pst, cntrl)
Pst         *pst;             /* post structure */         
LnbMngmt     *cntrl;           /* management structure */   
#endif
{
   TRC3(NbMiLnbCntrlCfm)
#if (ERRCLASS & ERRCLS_INT_PAR)
   if (pst == (Pst *)NULLP || pst->selector >= WR_LWR_MAX_SEL)
   {
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */
   RETVALUE((*nbMiLnbCntrlCfmMt[pst->selector])(pst, cntrl));
}
/**************************************************************************
 *
 *      Fun:  NbMiLwrStaInd  
 *
 *      Desc: Used to indicate the status of the RRC layer to the layer manager. 
 *
 *      Ret:  ROK - OK 
 *
 *      Notes:None 
 *
 *      File:  nb_ptmi.c
 *
 *************************************************************************/

#ifdef ANSI
PUBLIC S16 NbMiLnbStaInd
(
Pst *pst,                 /* Post structure */
LnbMngmt *usta             /* Unsolicited status */
)
#else
PUBLIC S16 NbMiLnbStaInd(pst, usta)
Pst *pst;                 /* Post structure */   
LnbMngmt *usta;            /* Unsolicited status */
#endif
{
   TRC3(NbMiLnbStaInd);

   /* jump to specific primitive depending on configured selector */
   (*NbMiLnbStaIndMt[pst->selector])(pst, usta); 

   RETVALUE(ROK);
} /* end of function WrMiLwrStaInd */


/* Portable functions */
#ifdef PTNBMILNB
/*
*
*       Fun:    PtMiLnbCfgCfm
*
*       Desc:   Dummy configuration confirm, customize if necessary
*
*       Ret:    ROK     - succeeded
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   nb_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 PtMiLnbCfgCfm
(
Pst                     *pst,
LnbMngmt                *cfg
)
#else
PUBLIC S16 PtMiLnbCfgCfm(pst, cfg)
Pst                     *pst;
LnbMngmt                *cfg;
#endif
{
   TRC3(PtMiLnbCfgCfm)
   UNUSED(pst);
   UNUSED(cfg);
   RETVALUE(RFAILED);
}

/*
*
*       Fun:    PtMiLnbCntrlCfm
*
*       Desc:   Dummy control confirm, customize if necessary
*
*       Ret:    ROK     - succeeded
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   nb_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 PtMiLnbCntrlCfm
(
Pst                     *pst,
LnbMngmt                *cntrl
)
#else
PUBLIC S16 PtMiLnbCntrlCfm(pst, cntrl)
Pst                     *pst;
LnbMngmt                *cntrl;
#endif
{
   TRC3(PtMiLnbCntrlCfm)
   UNUSED(pst);
   UNUSED(cntrl);
   RETVALUE(RFAILED);
}

/**************************************************************************
 *
 *      Fun:  PtMiLnbStaInd (Portable) 
 *
 *      Desc: Used to indicate the status of the RRC layer to the layer manager. 
 *
 *      Ret:  ROK - OK 
 *
 *      Notes:None 
 *
 *      File:  nb_ptmi.c
 *
 *************************************************************************/

#ifdef ANSI
PUBLIC S16 PtMiLnbStaInd
(
Pst *pst,                 /* Post structure */
LnbMngmt *usta             /* Unsolicited status */
)
#else
PUBLIC S16 PtMiLnbStaInd(pst, usta)
Pst *pst;                 /* Post structure */   
LnbMngmt *usta;            /* Unsolicited status */
#endif
{
   TRC3(PtMiLnbStaInd);

   UNUSED(pst);
   UNUSED(usta);


   RETVALUE(ROK);
} /* end of PtMiLnbStaInd */
#endif
