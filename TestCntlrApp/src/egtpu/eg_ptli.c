
/********************************************************************20**

     Name:    EGTP - Portable File for Lower Layer Interface

     Type:    C source file

     Desc:    This file contains all functions called twoards Lower Interface.


     File:    eg_ptli.c

     Sid:      eg_ptli.c@@/main/TeNB_Main_BR/5 - Mon Aug 11 16:42:26 2014

     Prg:     ad

*********************************************************************21*/

/*
The following functions are provided in this file:
   HitBndReq                - Bind Request
   HitUbndReq               - Unbind Request
   HitServOpenReq           - Server Open Request
   HitUDatReq               - Unit Data Request
   HitDiscReq               - Disconnect Request

*/

/* header include files (.h) */
#include "envopt.h"        /* Environment options             */
#include "envdep.h"        /* Environment dependent options   */
#include "envind.h"        /* Environment independent options */
#include "gen.h"           /* General layer                   */
#include "ssi.h"           /* System service interface        */
#include "cm5.h"           /* Common timer library            */
#include "cm_llist.h"      /* Common linked list library      */
#include "cm_hash.h"       /* Common hash library             */
#include "cm_tpt.h"        /* Common transport library        */
#include "cm_tkns.h"       /* Common tokens                   */
#include "cm_mblk.h"       /* Common memory allocation        */
#include "cm_dns.h"        /* Common DNS library              */
#include "cm_inet.h"       /* Common socket library           */
#include "hit.h"           /* HIT interface defines           */
/*eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_psf.h"
#include "sht.h"
#endif
#include "egt.h"           /* EGTP Upper Interface Defines  */
#include "leg.h"           /* EGTP MI Interface Defines  */
#include "eg.h"            /* EGTP Defines  */
#include "eg_err.h"        /* EGTP Errors */
#include "eg_edm.h"        /* EDM Module structures            */
#ifdef TIME_MES
#include <time.h>
#endif


/* header/extern include files (.x) */
#include "gen.x"           /* General layer                   */
#include "ssi.x"           /* System services interface       */
#include "cm5.x"           /* Common timer module             */
#include "cm_lib.x"        /* Common linrary function         */
#include "cm_llist.x"      /* Common link list library        */
#include "cm_hash.x"       /* Common hash list library        */
#include "cm_tkns.x"       /* Common tokens                   */
#include "cm_tpt.x"        /* Common transport library        */
#include "cm_mblk.x"       /* Common memory allocation        */
#include "cm_dns.x"        /* Common DNS library              */
#include "cm_inet.x"       /* Common socket library           */
#include "hit.x"           /* HIT interface defines           */
/*eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#include "sht.x"
#endif

#include "egt.x"           /* EGTP Upper Interface Defines  */
#include "leg.x"           /* EGTP MI Interface Defines  */
#include "eg_edm.x"        /* EDM Module structures            */
#include "eg.x"           /* EGTP Defines  */
#include "eg_tpt.x"       /* EGTP TPT Module */

#ifdef EG_ACC
#include "egac_acc.x"
#include "egac_hit.x"
#endif
/*eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "lhw.x"
#include "hw.x"          /* EGTPC UA                       */
#endif
#ifdef REVIEW
#include "eg_socklayer.h"
#include "eg_socklayer.x"
#endif

#if !(defined (DHI))
#define PTEGLIHIT
#endif

/* local defines */
#if  (!(defined(LCEGLIHIT) && defined(HI) ))
#ifndef PTEGLIHIT
#define PTEGLIHIT
#endif
#endif

#ifdef __cplusplus
EXTERN "C" {
#endif

#ifdef PTEGLIHIT
#ifndef REVIEW
PRIVATE S16 PtLiHitBndReq      ARGS((Pst          *pst,
                                     SuId         suId,
                                     SpId         spId));

PRIVATE S16 PtLiHitServOpenReq ARGS((Pst          *pst,
                                     SpId         spId,
                                     UConnId      servConId,
                                     CmTptAddr    *servTAddr,
                                     CmTptParam   *tPar,
                                     CmIcmpFilter *icmpFilter,
                                     U8           srvcType));
PRIVATE S16 PtLiHitUbndReq      ARGS((Pst          *pst,
                                     SpId         spId,
                                     Reason       reason));

PRIVATE S16 PtLiHitUDatReq      ARGS((Pst          *pst,
                                     SpId         spId,
                                     UConnId      spConId,
                                     CmTptAddr    *remAddr,
                                     CmTptAddr    *srcAddr,
                                     CmIpHdrParm  *hdrParm,
                                     CmTptParam   *tPar,
                                     Buffer       *mBuf));

PRIVATE S16 PtLiHitDiscReq      ARGS((Pst          *pst,
                                     SpId         spId,
                                     U8           choice,
                                     UConnId      conId,
                                     Action       action,
                                     CmTptParam   *tPar));


#ifdef __cplusplus
}
#endif

/* Primitive Mapping Tables */
PRIVATE HitBndReq EgLiHitBndReqMt[EG_MAX_LIHIT_SEL] =
{
#ifdef LCEGLIHIT
   cmPkHitBndReq,          /* 0 - loosely coupled (default mechanism) */
#else
   PtLiHitBndReq,          /* 0 - tightly coupled, portable */
#endif
#ifdef HI
   HiUiHitBndReq,          /* 1 - tightly coupled, Service Provider HI */
#else
   PtLiHitBndReq,          /* 1 - tightly coupled, portable */
#endif
#ifdef DHI
   DHiLiHitBndReq,         /* 2 - tightly coupled, dummy Service Provider HI */
#else
   PtLiHitBndReq           /* 2 - tightly coupled, portable */
#endif
};

PRIVATE HitUbndReq EgLiHitUbndReqMt[EG_MAX_LIHIT_SEL] =
{
#ifdef LCEGLIHIT
   cmPkHitUbndReq,         /* 0 - loosely coupled (default mechanism) */
#else
   PtLiHitUbndReq,         /* 0 - tightly coupled, portable */
#endif
#ifdef HI
   HiUiHitUbndReq,         /* 1 - tightly coupled, Service Provider HI */
#else
   PtLiHitUbndReq,         /* 1 - tightly coupled, portable */
#endif
#ifdef DHI
   DHiLiHitUbndReq,        /* 2 - tightly coupled, dummy Service Provider HI */
#else
   PtLiHitUbndReq          /* 2 - tightly coupled, portable */
#endif
};

PRIVATE HitServOpenReq EgLiHitServOpenReqMt[EG_MAX_LIHIT_SEL] =
{
#ifdef LCEGLIHIT
   cmPkHitServOpenReq,     /* 0 - loosely coupled (default mechanism) */
#else
   PtLiHitServOpenReq,     /* 0 - tightly coupled, portable */
#endif
#ifdef HI
   HiUiHitServOpenReq,     /* 1 - tightly coupled, Service Provider HI */
#else
   PtLiHitServOpenReq,     /* 1 - tightly coupled, portable */
#endif
#ifdef DHI
   DHiLiHitServOpenReq,    /* 2 - tightly coupled, dummy Service Provider HI */
#else
   PtLiHitServOpenReq      /* 2 - tightly coupled, portable */
#endif
};


PRIVATE HitUDatReq EgLiHitUDatReqMt[EG_MAX_LIHIT_SEL] =
{
#ifdef LCEGLIHIT
   cmPkHitUDatReq,         /* 0 - loosely coupled (default mechanism) */
#else
   PtLiHitUDatReq,         /* 0 - tightly coupled, portable */
#endif
#ifdef HI
   HiUiHitUDatReq,         /* 1 - tightly coupled, Service Provider HI */
#else
   PtLiHitUDatReq,         /* 1 - tightly coupled, portable */
#endif
#ifdef DHI
   DHiLiHitUDatReq,        /* 2 - tightly coupled, dummy Service Provider HI */
#else
   PtLiHitUDatReq          /* 2 - tightly coupled, portable */
#endif
};

PRIVATE HitDiscReq EgLiHitDiscReqMt[EG_MAX_LIHIT_SEL] =
{
#ifdef LCEGLIHIT
   cmPkHitDiscReq,         /* 0 - loosely coupled (default mechanism) */
#else
   PtLiHitDiscReq,         /* 0 - tightly coupled, portable */
#endif
#ifdef HI
   HiUiHitDiscReq,         /* 1 - tightly coupled, Service Provider HI */
#else
   PtLiHitDiscReq,         /* 1 - tightly coupled, portable */
#endif
#ifdef DHI
   DHiLiHitDiscReq,        /* 2 - tightly coupled, dummy Service Provider HI */
#else
   PtLiHitDiscReq          /* 2 - tightly coupled, portable */
#endif
};
#endif
#endif /* PTEGLIHIT */
/* Primitive Mapping Dispatching Functions */

/****************************************************************
*
*       Fun:   EgLiHitBndReq
*
*       Desc:  This function is used to bind a transport SAP
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  eg_ptli.c
*
*******************************************************************/
/* REVIEW-ID:56220:purecov fix */
#ifndef REVIEW
#ifdef ANSI
PUBLIC S16 EgLiHitBndReq
(
Pst  *pst,                /* post structure */
SuId suId,                /* service user SAP ID */
SpId spId                 /* service provider SAP ID */
)
#else
PUBLIC S16 EgLiHitBndReq(pst, suId, spId)
Pst  *pst;                /* post structure */
SuId suId;                /* service user SAP ID */
SpId spId;                /* service provider SAP ID */
#endif
{
   EG_TRC3(EgLiHitBndReq);

   EG_DBG_FLOW(pst, EVTHITBNDREQ);

   EG_DBG_PARAM(0,0,(egp,"suId(%d) spId(%d)", suId, spId));

#ifndef REVIEW
   (*EgLiHitBndReqMt[pst->selector])(pst, suId, spId);
#else
   EgTLBndReq(pst, suId, spId);
#endif /* REVIEW */

   RETVALUE(ROK);
} /* EgLiHitBndReq */
#endif /* REVIEW */ 
/*******************************************************************
*
*       Fun:   EgLiHitUbndReq
*
*       Desc:  This function is used to unbind a transport SAP
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  eg_ptli.c
*
*******************************************************************/
/* REVIEW-ID:56220:purecov fix */
#ifndef REVIEW
#ifdef ANSI
PUBLIC S16 EgLiHitUbndReq
(
Pst    *pst,              /* post structure */
SpId   spId,              /* service provider SAP ID */
Reason reason             /* reason */
)
#else
PUBLIC S16 EgLiHitUbndReq(pst, spId, reason)
Pst    *pst;              /* post structure */
SpId   spId;              /* service provider SAP ID */
Reason reason;            /* reason */
#endif
{
   EG_TRC3(EgLiHitUbndReq);

   EG_DBG_FLOW(pst, EVTHITUBNDREQ);
   EG_DBG_PARAM(0,0,(egp,"spId(%d) reason(%d)", spId, reason));

#ifndef REVIEW
   (*EgLiHitUbndReqMt[pst->selector])(pst, spId, reason);
#else
   EgTLUbndReq(pst, spId, reason);
#endif /* REVIEW */

   RETVALUE(ROK);
} /* EgLiHitUbndReq */
#endif /* REVIEW */
/*******************************************************************
*
*       Fun:   EgLiHitServOpenReq
*
*       Desc:  This function is used to open a TCP or UDP server
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  eg_ptli.c
*
*******************************************************************/
#ifdef ANSI
PUBLIC S16 EgLiHitServOpenReq
(
Pst          *pst,          /* post stucture */
SpId         spId,          /* service provider Id */
UConnId      servConId,     /* service user’s connection Id */
CmTptAddr    *servTAddr,    /* transport address of the server */
CmTptParam   *tPar,         /* transport parameters */
CmIcmpFilter *icmpFilter,   /* Filter parameters */
U8           srvcType       /* service type */
)
#else
PUBLIC S16 EgLiHitServOpenReq(pst, spId, servConId, servTAddr, tPar,
                              icmpFilter, srvcType)
Pst          *pst;          /* post stucture */
SpId         spId;          /* service provider Id */
UConnId      servConId;     /* service user’s connection Id */
CmTptAddr    *servTAddr;    /* transport address of the server */
CmTptParam   *tPar;         /* transport parameters */
CmIcmpFilter *icmpFilter;   /* Filter parameters */
U8           srvcType;      /* service type */
#endif
{
   EG_TRC3(EgLiHitServOpenReq);

   EG_DBG_FLOW(pst, EVTHITSRVOPENREQ);

#ifdef ALIGN_64BIT
   EG_DBG_PARAM(0,0,(egp,"spId(%d) servConId(%d)", spId, servConId));
#else
   EG_DBG_PARAM(0,0,(egp,"spId(%d) servConId(%ld)", spId, servConId));

#endif

   EG_DBG_PARAM(0,0,(egp,"srvcType(%d)", srvcType));
   EG_DBG_PARAM(EG_DBG_CMTPTADDR, servTAddr,(egp," "));

#ifndef REVIEW
   (*EgLiHitServOpenReqMt[pst->selector])(pst, spId, servConId, servTAddr,
                                          tPar, icmpFilter, srvcType);
#else
   EgTLOpenServerReq(pst, spId, servConId, servTAddr);
#endif

   RETVALUE(ROK);
} /* EgLiHitServOpenReq */





/*******************************************************************
*
*       Fun:   EgLiHitUDatReq
*
*       Desc:  This function is used to send data to an UDP client
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  eg_ptli.c
*
*******************************************************************/
#ifdef ANSI
PUBLIC S16 EgLiHitUDatReq
(
Pst         *pst,          /* post stucture */
SpId        spId,          /* service provider Id */
UConnId     spConId,       /* service provider’s connection Id */
CmTptAddr   *remAddr,      /* remote address */
CmTptAddr   *srcAddr,      /* egurce address */
CmIpHdrParm *hdrParm,      /* header parameters */
CmTptParam  *tPar,
Buffer      *mBuf          /* message buffer */
)
#else /* ANSI */
PUBLIC S16 EgLiHitUDatReq(pst, spId, spConId, remAddr, srcAddr, hdrParm, tPar,
                          mBuf)
Pst         *pst;          /* post stucture */
SpId        spId;          /* service provider Id */
UConnId     spConId;       /* service provider’s connection Id */
CmTptAddr   *remAddr;      /* remote address */
CmTptAddr   *srcAddr;      /* egurce address */
CmIpHdrParm *hdrParm;      /* header parameters */
CmTptParam  *tPar;
Buffer      *mBuf;         /* message buffer */
#endif /* ANSI */

{
#ifdef TIME_MES
#ifdef SS_MT_CB
  PRIVATE U32 call;
  FILE *fp;
  U32   i;
  U32   j;
  unsigned long long av_time  = 0;
  if(exitTx[pst->srcInst-1].call < MAX_MSG)
  {
     clock_gettime(0, &exitTx[pst->srcInst-1].time[exitTx[pst->srcInst-1].call++]);
  }
#else
  PRIVATE U32 call;
  FILE *fp;
  U32   i;
  unsigned long long av_time  = 0;
  if(call < MAX_MSG)
  {
     clock_gettime(0, &exitTx2[call]);
     call ++;
  }
#endif
#endif
   EG_TRC3(EgLiHitUDatReq);

   EG_DBG_FLOW(pst, EVTHITUDATREQ);

#ifdef ALIGN_64BIT
   EG_DBG_PARAM(0,0,(egp,"spId(%d) spConId(%d)",spId, spConId));
#else
   EG_DBG_PARAM(0,0,(egp,"spId(%d) spConId(%ld)",spId, spConId));

#endif

   EG_DBG_PARAM(EG_DBG_CMTPTADDR, remAddr,(egp," "));
   EG_DBG_PARAM(EG_DBG_CMTPTADDR, srcAddr,(egp," "));


#ifdef TIME_MES
#ifdef SS_MT_CB
  if (exitTx[pst->srcInst-1].call == MAX_MSG)
  {
     fp = fopen("/home/rss/perf_log_1","w");
     for (i = 0; i < MAX_MSG; i++)
     {
        for(j = 0; j< MAX_THREAD; j++)
        {
           if (exitTx[j].time[i].tv_sec - entryTx[j].time[i].tv_sec == 0)
           {
              av_time += exitTx[j].time[i].tv_nsec - entryTx[j].time[i].tv_nsec;
           }
           else if (exitTx[j].time[i].tv_sec - entryTx[j].time[i].tv_sec == 1)
           {
              av_time += (exitTx[j].time[i].tv_nsec) + (1000000000 - entryTx[j].time[i].tv_nsec);
           }
        }
     }
     av_time /= (MAX_MSG * MAX_THREAD);
     fprintf(fp, "Average message processing time (sender) %llu \n", av_time);
     fclose(fp);
  }
#else
  if (call == MAX_MSG)
  {
     fp = fopen("/home/rss/perf_log_1","w");
     for (i = 0; i < MAX_MSG; i++)
     {
        if (exitTx1[i].tv_sec - entryTx1[i].tv_sec == 0)
        {
           av_time += exitTx1[i].tv_nsec - entryTx1[i].tv_nsec;
        }
        else if (exitTx1[i].tv_sec - entryTx1[i].tv_sec == 1)
        {
           av_time += (exitTx1[i].tv_nsec) + (1000000000 - entryTx1[i].tv_nsec);
        }

        if(exitTx2[i].tv_sec - entryTx2[i].tv_sec == 0)
        {
           av_time += exitTx2[i].tv_nsec - entryTx2[i].tv_nsec;
        }
        else if (exitTx2[i].tv_sec - entryTx2[i].tv_sec == 1)
        {
           av_time += (exitTx2[i].tv_nsec) + (1000000000 - entryTx2[i].tv_nsec);
        }
        fprintf(fp, "Average Time %llu \n", av_time);
     }
     av_time /= MAX_MSG;
     fprintf(fp, "Average message processing time (Sender) %lu \n", av_time);
     fclose(fp);
     call ++;
  }
#endif
#endif

#ifndef REVIEW
   (*EgLiHitUDatReqMt[pst->selector])(pst, spId, spConId, remAddr, srcAddr,
                                      hdrParm, tPar, mBuf);
#else
   EgTLDatReq(spConId, remAddr, srcAddr, hdrParm, mBuf);
#endif /* REVIEW */

   RETVALUE(ROK);
} /* EgLiHitUDatReq */

/*******************************************************************
*
*       Fun:   EgLiHitDiscReq
*
*       Desc:  This function is used to disconnect a server
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  eg_ptli.c
*
*******************************************************************/
#ifdef ANSI
PUBLIC S16 EgLiHitDiscReq
(
Pst         *pst,          /* post stucture */
SpId        spId,          /* service provider Id */
U8          choice,        /* choice parameter */
UConnId     conId,         /* connection Id */
Action      action,        /* action type */
CmTptParam  *tPar          /* transport parameter */
)
#else
PUBLIC S16 EgLiHitDiscReq(pst, spId, choice, conId, action, tPar)
Pst         *pst;          /* post stucture */
SpId        spId;          /* service provider Id */
U8          choice;        /* choice parameter */
UConnId     conId;         /* connection Id */
Action      action;        /* action type */
CmTptParam  *tPar;         /* transport parameter */
#endif
{
   EG_TRC3(EgLiHitDiscReq);

   EG_DBG_FLOW(pst, EVTHITDISCREQ);

#ifdef ALIGN_64BIT
   EG_DBG_PARAM(0,0,(egp,"spId(%d) choice(%d) conId(%d)",spId, choice, conId));
#else
   EG_DBG_PARAM(0,0,(egp,"spId(%d) choice(%d) conId(%ld)",spId, choice, conId));

#endif

   EG_DBG_PARAM(0,0,(egp,"action(%d)",action));



   EG_DBG_MEM((Ptr)tPar, EG_MEMTYPE_EVNT, EG_MEMMODE_SEND, 0);

#ifndef REVIEW
   (*EgLiHitDiscReqMt[pst->selector])(pst, spId, choice, conId, action, tPar);
#else
   EgTLDiscServerReq(conId);
#endif /* REVIEW */

   RETVALUE(ROK);
} /* EgLiHitDiscReq */


#ifdef PTEGLIHIT
/* Portable Stub Functions */
#ifndef REVIEW
/*******************************************************************
*
*       Fun:   PtLiHitBndReq
*
*       Desc:  Portable version of HitBndReq primitive
*
*       Ret:   RFAILED
*
*       Notes: None
*
*       File:  eg_ptli.c
*
*******************************************************************/
#ifdef ANSI
PRIVATE S16 PtLiHitBndReq
(
Pst  *pst,                /* post structure */
SuId suId,                /* service user SAP ID */
SpId spId                 /* service provider SAP ID */
)
#else
PRIVATE S16 PtLiHitBndReq(pst, suId, spId)
Pst  *pst;                /* post structure */
SuId suId;                /* service user SAP ID */
SpId spId;                /* service provider SAP ID */
#endif
{
   EG_TRC3(PtLiHitBndReq);

   EGLOGDBGERR(EEG004,(ErrVal)ERRZERO, "PtLiHitBndReq(): Invalid Selector");

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(spId);

   RETVALUE(RFAILED);
} /* PtLiHitBndReq*/

/*******************************************************************
*
*       Fun:   PtLiHitUbndReq
*
*       Desc:  Portable version of HitUbndReq primitive
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  eg_ptli.c
*
*******************************************************************/
#ifdef ANSI
PRIVATE S16 PtLiHitUbndReq
(
Pst    *pst,              /* post structure */
SpId   spId,              /* service provider SAP ID */
Reason reason             /* reason */
)
#else
PRIVATE S16 PtLiHitUbndReq(pst, spId, reason)
Pst    *pst;              /* post structure */
SpId   spId;              /* service provider SAP ID */
Reason reason;            /* reason */
#endif
{
   EG_TRC3(PtLiHitUbndReq);

   EGLOGDBGERR(EEG005, (ErrVal)ERRZERO, "PtLiHitUBndReq(): Invalid Selector");

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(reason);

   RETVALUE(RFAILED);
} /* PtLiHitUbndReq */

/*******************************************************************
*
*       Fun:   PtLiHitServOpenReq
*
*       Desc:  Portable version of HitServOpenReq primitive
*
*       Ret:   RFAILED
*
*       Notes: None
*
*       File:  eg_ptli.c
*
*******************************************************************/
#ifdef ANSI
PRIVATE S16 PtLiHitServOpenReq
(
Pst          *pst,          /* post stucture */
SpId         spId,          /* service provider Id */
UConnId      servConId,     /* service user’s connection Id */
CmTptAddr    *servTAddr,    /* transport address of the server */
CmTptParam   *tPar,         /* transport parameters */
CmIcmpFilter *icmpFilter,   /* Filter parameters */
U8           srvcType       /* service type */
)
#else
PRIVATE S16 PtLiHitServOpenReq(pst, spId, servConId, servTAddr, tPar,
                              icmpFilter, srvcType)
Pst          *pst;          /* post stucture */
SpId         spId;          /* service provider Id */
UConnId      servConId;     /* service user’s connection Id */
CmTptAddr    *servTAddr;    /* transport address of the server */
CmTptParam   *tPar;         /* transport parameters */
CmIcmpFilter *icmpFilter;   /* Filter parameters */
U8           srvcType;      /* service type */
#endif
{
   EG_TRC3(PtLiHitServOpenReq);

   EGLOGDBGERR(EEG006, (ErrVal)ERRZERO, "PtLiHitServOpenReq(): Invalid Selector");

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(servConId);
   UNUSED(servTAddr);
   UNUSED(tPar);
   UNUSED(icmpFilter);
   UNUSED(srvcType);

   RETVALUE(RFAILED);
} /* PtLiHitServOpenReq */

/*******************************************************************
*
*       Fun:   PtLiHitUDatReq
*
*       Desc:  Portable version of HitUDatReq primitive
*
*       Ret:   RFAILED
*
*       Notes: None
*
*       File:  eg_ptli.c
*
*******************************************************************/
#ifdef ANSI
PRIVATE S16 PtLiHitUDatReq
(
Pst         *pst,          /* post stucture */
SpId        spId,          /* service provider Id */
UConnId     spConId,       /* service provider’s connection Id */
CmTptAddr   *remAddr,      /* remote address */
CmTptAddr   *srcAddr,      /* source address */
CmIpHdrParm *hdrParm,      /* header parameters */
CmTptParam  *tPar,         /* Transport Parameters */
Buffer      *mBuf          /* message buffer */
)
#else
PRIVATE S16 PtLiHitUDatReq(pst, spId, spConId, remAddr, srcAddr, hdrParm,
                          tPar, mBuf)
Pst         *pst;          /* post stucture */
SpId        spId;          /* service provider Id */
UConnId     spConId;       /* service provider’s connection Id */
CmTptAddr   *remAddr;      /* remote address */
CmTptAddr   *srcAddr;      /* source address */
CmIpHdrParm *hdrParm;      /* header parameters */
CmTptParam  *tPar;         /* Transport Parameters */
Buffer      *mBuf;         /* message buffer */
#endif
{
   EG_TRC3(PtLiHitUDatReq);

   EGLOGDBGERR(EEG007, (ErrVal)ERRZERO, "PtLiHitUDatReq(): Invalid Selector");

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(spConId);
   UNUSED(remAddr);
   UNUSED(srcAddr);
   UNUSED(hdrParm);
   UNUSED(mBuf);

   RETVALUE(RFAILED);
} /* PtLiHitUDatReq */

/*******************************************************************
*
*       Fun:   PtLiHitDiscReq
*
*       Desc:  Portable version of Hit primitive
*
*       Ret:   RFAILED
*
*       Notes: None
*
*       File:  eg_ptli.c
*
*******************************************************************/
#ifdef ANSI
PRIVATE S16 PtLiHitDiscReq
(
Pst         *pst,          /* post stucture */
SpId        spId,          /* service provider Id */
U8          choice,        /* choice parameter */
UConnId     conId,         /* connection Id */
Action      action,        /* action type */
CmTptParam  *tPar          /* transport parameter */
)
#else
PRIVATE S16 PtLiHitDiscReq(pst, spId, choice, conId, action, tPar)
Pst         *pst;          /* post stucture */
SpId        spId;          /* service provider Id */
U8          choice;        /* choice parameter */
UConnId     conId;         /* connection Id */
Action      action;        /* action type */
CmTptParam  *tPar;         /* transport parameter */
#endif
{
   EG_TRC3(PtLiHitDiscReq);

   EGLOGDBGERR(EEG008, (ErrVal)ERRZERO, "PtLiHitDiscReq(): Invalid Selector");

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(choice);
   UNUSED(conId);
   UNUSED(action);
   UNUSED(tPar);

   RETVALUE(RFAILED);
} /* PtLiHitDiscReq */
#endif
#endif

/********************************************************************30**

         End of file:     eg_ptli.c@@/main/TeNB_Main_BR/5 - Mon Aug 11 16:42:26 2014

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
/main/2      ---      rsharon           1. Initial for eGTP 1.2 Release
/main/2      eg001.102   rss               2. Multithreaded performance changes .
/main/2      eg003.102   rss               1.  Removed cm_xtree from the include list.
/main/3      ---      pmacharla       Initial Release of eGTP 2.1 release
/main/3      eg004.201  magnihotri      1.Header files added for eGTP-C PSF
*********************************************************************91*/
