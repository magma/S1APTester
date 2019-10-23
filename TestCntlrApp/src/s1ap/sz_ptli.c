

/***********************************************************************

************************************************************************

   Name: S1AP Layer

   Type: C Source File
   
   Desc: C Source code for the protable functions of S1AP lower
            interface layer

   File: sz_ptli.c

   Sid:      sq_ptli.c@@/main/4 - Mon Jan 10 22:17:03 2011

   Prg : ms

************************************************************************/



/*
The following functions are provided in this file:
   SctBndReq             - Bind Request
      SctEndpOpenReq        - End point open request
      SctEndpCloseReq       - End point close request
      SctSetPriReq          - Set primary address request
      SctStaReq             - Status request
      SctTermReq            - Termination request
      SctAssocReq           - Association request
      SctDatReq             - Data request
      SctAssocRsp           - Association response
      SctHBeatReq           - Heart beat request

It should be noted that not all of these functions may be required
by a particular network layer service provider.

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
#include "cm_dns.h"       /* Common hash library             */
#include "cm_tpt.h"        /* Common transport library        */
#include "cm_tkns.h"       /* Common tokens                   */
#include "cm_mblk.h"       /* Common memory allocation        */
#include "cm_inet.h"       /* Common socket library           */
#include "sct.h"           /* SCT interface defines           */
#include "szt.h"           /* SZT interface defines           */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_pftha.h"
#include "cm_psf.h"
#include "sht.h"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.h"           /* S1AP Layer management           */
#include "sz.h"            /* S1AP layer defines              */
#include "sz_err.h"            /* S1AP layer defines              */
#ifdef SB
#include "lsb.h"            /* SCTP layer managment defines */
#endif /*SB*/
#ifdef HI
#include "lhi.h"            /* TUCL layer managment defines */
#endif /*hi*/
#include "cm_pasn.h"
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.h"
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
#include "cm_inet.x"       /* Common socket library           */
/* sz006.301: Removed un-necessary include files  */
#include"szt_asn.x"        /* common ss7 */
#ifndef SZ_ENC_DEC
#include "szt_pk.x"
#include "szt_unpk.x"
#endif /* SZ_ENC_DEC */
#include "sct.x"           /* SCT interface defines           */
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.x"
#endif
#include "szt.x"           /* SZT interface structures        */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_pftha.x"
#include "cm_psf.x"
#include "sht.x"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.x"           /* S1AP Layer management           */
#include "cm_pasn.x"
#include "sz.x"            /* S1AP layer structures           */
#ifdef SB
#include "lsb.x"           /* SCTP layer managment structures */
#endif /*SB*/
#ifdef HI
#include "lhi.x"           /* TUCL layer managment structures */
#endif /*hi*/


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if (!defined SB || !defined LCSZLISCT || !defined HI_LKSCTP || !defined HI || !defined DM)
/* portable functions */


PRIVATE S16 PtLiSctBndReq            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SpId           spId));


#ifdef SCT_ENDP_MULTI_IPADDR
PRIVATE S16 PtLiSctEndpOpenReq ARGS (( Pst *pst,
                                    SpId spId,
                                    UConnId suEndpId,
                                    U16 port,
                                    SctNetAddrLst  *srcAddrLst));
#else                                    
PRIVATE S16 PtLiSctEndpOpenReq ARGS((Pst            *pst,
                                    SpId            spId,
                                    UConnId         suEndpId,
                                    SctPort         port,
                                    CmNetAddr      *intfNAddr));
#endif /* SCT_ENDP_MULTI_IPADDR */


PRIVATE S16 PtLiSctEndpCloseReq      ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        endpId,
                                          U8             endpIdType));



#ifdef SCT3
PRIVATE S16 PtLiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          SctTos        tos,
                                          Buffer        *vsInfo));
#else
PRIVATE S16 PtLiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          Buffer        *vsInfo));
#endif /* end of SCT3 */


#ifdef SCT3
PRIVATE S16 PtLiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctTos             tos,
                                          SctResult          result,
                                          Buffer            *vsInfo));
#else
PRIVATE S16 PtLiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctResult          result,
                                          Buffer            *vsInfo));
#endif /* end of SCT3 */

#ifdef SZ_PHASE2
PRIVATE S16 PtLiSctHBeatReq   ARGS((Pst            *pst,
                                   SpId            spId,
                                   UConnId         spAssocId,
                                   CmNetAddr      *dstNAddr,
                                   U16             intervalTime,
                                   SctStatus       status));
#endif

PRIVATE S16 PtLiSctTermReq           ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          Bool           abrtFlg));


#ifdef SZ_PHASE2
PRIVATE S16 PtLiSctSetPriReq         ARGS((Pst           *pst,
                                           SpId          spId,
                                           UConnId       spAssocId,
                                           CmNetAddr     *dstNAddr));
#endif

PRIVATE S16 PtLiSctDatReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStrmId      strmId,
                                          Bool           unorderFlg,
                                          Bool           nobundleFlg,
                                          U16            lifeTime,
                                          U32            protId,
                                          Buffer        *mBuf));


PRIVATE S16 PtLiSctStaReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U8             staType));
#endif /* end of (!defined SB || !defined LCSZLISCT || !defined HI_LKSCTP || !defined HI || !defined DM) */
#ifdef __cplusplus
}
#endif /* __cplusplus */



/***********************************************************************
The following matrices define the mapping between the primitives called 
by the UI of SCTP layer and the corresponding primitives in SCTP

SZ_SCT_MAX_SEL defines the maximum number of valid selector values.
The selectors are
0 - Loosely coupled with SCTP (#define LCSZLISCT)
1 - Tightly coupled with SCTP (#define SB)
2 - Tightly coupled with KSCTP (#define HI)
**********************************************************************/


/* Bind request primitive */
PRIVATE SctBndReq SzLiSctBndReqMt[SZ_SCT_MAX_SEL] =
{
#ifdef LCSZLISCT
   cmPkSctBndReq,          /* 0 - loosely coupled (default mechanism) */
#else
   PtLiSctBndReq,          /* 0 - tightly coupled, portable */
#endif
#ifdef SB
   SbUiSctBndReq,          /* 1 - tightly coupled, Service Provider SB */
#else
   PtLiSctBndReq,          /* 1 - tightly coupled, portable */
#endif
#if (defined(HI) && defined(HI_LKSCTP))
   HiUiSctBndReq,          /* 2 - tightly coupled, Service Provider HI */
#else
   PtLiSctBndReq,          /* 2 - tightly coupled, portable */
#endif
#ifdef DM
   DmUiSctBndReq,          /* 3 - tightly coupled, Service Provider HI */
#else
   PtLiSctBndReq,          /* 3 - tightly coupled, portable */
#endif
}; /* SzLiSctBndReqMt */


/* End point open request primitive */
PRIVATE  SctEndpOpenReq SzLiSctEndpOpenReqMt[SZ_SCT_MAX_SEL] =
{
#ifdef LCSZLISCT
   cmPkSctEndpOpenReq,     /* 0 - loosely coupled */
#else
   PtLiSctEndpOpenReq,     /* 0 - tightly coupled, portable */
#endif
#ifdef SB
   SbUiSctEndpOpenReq,     /* 1 - tightly coupled, stub layer */
#else
   PtLiSctEndpOpenReq,     /* 1 - tightly coupled, portable */
#endif
#if (defined(HI) && defined(HI_LKSCTP))
   HiUiSctEndpOpenReq,     /* 2 - tightly coupled, stub layer */
#else
   PtLiSctEndpOpenReq,     /* 2 - tightly coupled, portable */
#endif
#ifdef DM
   DmUiSctEndpOpenReq,     /* 3 - tightly coupled, stub layer */
#else
   PtLiSctEndpOpenReq,     /* 3 - tightly coupled, portable */
#endif
}; /* SzLiSctEndpOpenReqMt */


/* End point close request primitive */
PRIVATE  SctEndpCloseReq SzLiSctEndpCloseReqMt[SZ_SCT_MAX_SEL] =
{
#ifdef LCSZLISCT
   cmPkSctEndpCloseReq,     /* 0 - loosely coupled */
#else
   PtLiSctEndpCloseReq,     /* 0 - tightly coupled, portable */
#endif
#ifdef SB
   SbUiSctEndpCloseReq,     /* 1 - tightly coupled, stub layer */
#else
   PtLiSctEndpCloseReq,     /* 1 - tightly coupled, portable */
#endif
#if (defined(HI) && defined(HI_LKSCTP))
   HiUiSctEndpCloseReq,     /* 2 - tightly coupled, stub layer */
#else
   PtLiSctEndpCloseReq,     /* 2 - tightly coupled, portable */
#endif
#ifdef DM
   DmUiSctEndpCloseReq,     /* 3 - tightly coupled, stub layer */
#else
   PtLiSctEndpCloseReq,     /* 3 - tightly coupled, portable */
#endif
}; /* SzLiSctEndpCloseReqMt */

#ifdef SZ_PHASE2
/* Set primary address request primitive */
PRIVATE  SctSetPriReq SzLiSctSetPriReqMt[SZ_SCT_MAX_SEL] =
{
#ifdef LCSZLISCT
   cmPkSctSetPriReq,      /* 0 - loosely coupled */
#else
   PtLiSctSetPriReq,      /* 0 - tightly coupled, portable */
#endif
#ifdef SB
   SbUiSctSetPriReq,      /* 1 - tightly coupled, stub layer */
#else
   PtLiSctSetPriReq,      /* 1 - tightly coupled, portable */
#endif
#if (defined(HI) && defined(HI_LKSCTP))
   HiUiSctSetPriReq,      /* 2 - tightly coupled, stub layer */
#else
   PtLiSctSetPriReq,      /* 2 - tightly coupled, portable */
#endif
#ifdef DM
   DmUiSctSetPriReq,      /* 3 - tightly coupled, stub layer */
#else
   PtLiSctSetPriReq,      /* 3 - tightly coupled, portable */
#endif
}; /* SzLiSctSetPriReqMt */
#endif /* SZ_PHASE2 */

/* Status request primitive */
PRIVATE  SctStaReq SzLiSctStaReqMt[SZ_SCT_MAX_SEL] =
{
#ifdef LCSZLISCT
   cmPkSctStaReq,         /* 0 - loosely coupled */
#else
   PtLiSctStaReq,         /* 0 - tightly coupled, portable */
#endif
#ifdef SB
   SbUiSctStaReq,        /* 1 - tightly coupled, stub layer */
#else
   PtLiSctStaReq,        /* 1 - tightly coupled, portable */
#endif
#if (defined(HI) && defined(HI_LKSCTP))
   HiUiSctStaReq,        /* 2 - tightly coupled, stub layer */
#else
   PtLiSctStaReq,        /* 2 - tightly coupled, portable */
#endif
#ifdef DM
   DmUiSctStaReq,        /* 3 - tightly coupled, stub layer */
#else
   PtLiSctStaReq,        /* 3 - tightly coupled, portable */
#endif
}; /* SzLiSctStaReqMt */


/* Termination request primitive */
PRIVATE SctTermReq SzLiSctTermReqMt[SZ_SCT_MAX_SEL] =
{
#ifdef LCSZLISCT
   cmPkSctTermReq,          /* 0 - loosely coupled (default mechanism) */
#else
   PtLiSctTermReq,          /* 0 - tightly coupled, portable */
#endif
#ifdef SB
   SbUiSctTermReq,          /* 1 - tightly coupled, Service Provider SB */
#else
   PtLiSctTermReq,          /* 1 - tightly coupled, portable */
#endif
#if (defined(HI) && defined(HI_LKSCTP))
   HiUiSctTermReq,          /* 2 - tightly coupled, Service Provider HI */
#else
   PtLiSctTermReq,          /* 2 - tightly coupled, portable */
#endif
#ifdef DM
   DmUiSctTermReq,          /* 3 - tightly coupled, Service Provider HI */
#else
   PtLiSctTermReq,          /* 3 - tightly coupled, portable */
#endif
}; /*SzLiSctTermReqMt */


/* Association request primitive */
PRIVATE SctAssocReq SzLiSctAssocReqMt[SZ_SCT_MAX_SEL] =
{
#ifdef LCSZLISCT
   cmPkSctAssocReq,          /* 0 - loosely coupled (default mechanism) */
#else
   PtLiSctAssocReq,          /* 0 - tightly coupled, portable */
#endif
#ifdef SB
   SbUiSctAssocReq,          /* 1 - tightly coupled, Service Provider SB */
#else
   PtLiSctAssocReq,          /* 1 - tightly coupled, portable */
#endif
#if (defined(HI) && defined(HI_LKSCTP))
   HiUiSctAssocReq,          /* 2 - tightly coupled, Service Provider HI */
#else
   PtLiSctAssocReq,          /* 2 - tightly coupled, portable */
#endif
#ifdef DM
   DmUiSctAssocReq,          /* 3 - tightly coupled, Service Provider HI */
#else
   PtLiSctAssocReq,          /* 3 - tightly coupled, portable */
#endif
}; /* SzLiSctAssocReqMt */


/* Data request primitive */
PRIVATE SctDatReq SzLiSctDatReqMt[SZ_SCT_MAX_SEL] =
{
#ifdef LCSZLISCT
   cmPkSctDatReq,          /* 0 - loosely coupled (default mechanism) */
#else
   PtLiSctDatReq,          /* 0 - tightly coupled, portable */
#endif
#ifdef SB
   SbUiSctDatReq,          /* 1 - tightly coupled, Service Provider SB */
#else
   PtLiSctDatReq,          /* 1 - tightly coupled, portable */
#endif
#if (defined(HI) && defined(HI_LKSCTP))
   HiUiSctDatReq,          /* 2 - tightly coupled, Service Provider HI */
#else
   PtLiSctDatReq,          /* 2 - tightly coupled, portable */
#endif
#ifdef DM
   DmUiSctDatReq,          /* 3 - tightly coupled, Service Provider HI */
#else
   PtLiSctDatReq,          /* 3 - tightly coupled, portable */
#endif
}; /* SzLiSctDatReqMt */


/* Association response primitive */
PRIVATE SctAssocRsp SzLiSctAssocRspMt[SZ_SCT_MAX_SEL] =
{
#ifdef LCSZLISCT
   cmPkSctAssocRsp,          /* 0 - loosely coupled (default mechanism) */
#else
   PtLiSctAssocRsp,          /* 0 - tightly coupled, portable */
#endif
#ifdef SB
   SbUiSctAssocRsp,          /* 1 - tightly coupled, Service Provider SB */
#else
   PtLiSctAssocRsp,          /* 1 - tightly coupled, portable */
#endif
#if (defined(HI) && defined(HI_LKSCTP))
   HiUiSctAssocRsp,          /* 2 - tightly coupled, Service Provider HI */
#else
   PtLiSctAssocRsp,          /* 2 - tightly coupled, portable */
#endif
#ifdef DM
   DmUiSctAssocRsp,          /* 3 - tightly coupled, Service Provider HI */
#else
   PtLiSctAssocRsp,          /* 3 - tightly coupled, portable */
#endif
}; /* SzLiSctAssocRspMt */


#ifdef SZ_PHASE2 
/* Heartbeat request primitive */
PRIVATE SctHBeatReq SzLiSctHBeatReqMt[SZ_SCT_MAX_SEL] =
{
#ifdef LCSULISCT
    cmPkSctHBeatReq,        /* 0 - loosely coupled */
#else
    PtLiSctHBeatReq,        /* 0 - tightly coupled, portable */
#endif
#ifdef SB
    SbUiSctHBeatReq,        /* 1 - tightly coupled, layer management */
#else
    PtLiSctHBeatReq,        /* 1 - tightly coupled, portable */
#endif
#if (defined(HI) && defined(HI_LKSCTP))
    HiUiSctHBeatReq,        /* 2 - tightly coupled, layer management */
#else
    PtLiSctHBeatReq,        /* 2 - tightly coupled, portable */
#endif
#ifdef DM
    DmUiSctHBeatReq,        /* 3 - tightly coupled, layer management */
#else
    PtLiSctHBeatReq,        /* 3 - tightly coupled, portable */
#endif
}; /* SzLiSctHBeatReqMt */
#endif /* SZ_PHASE2 */


/************************************************************************
                   Function Definitions
************************************************************************/


/*
*
*       Fun:   Bind request
*
*       Desc:  This function is used to bind two upper SAPs.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sz_ptli.c
*
*/

#ifdef ANSI
PUBLIC S16 SzLiSctBndReq
(
Pst *pst,                 /* post structure */
SuId suId,                /* Su SAP Id */
SpId spId                 /* Sp SAP Id */
)
#else
PUBLIC S16 SzLiSctBndReq(pst, suId, spId)
Pst *pst;                 /* post structure */
SuId suId;                /* Su SAP Id */
SpId spId;                /* Sp SAP Id */
#endif
{
   TRC3(SzLiSctBndReq);

#ifdef DEBUGP
   SZDBGP (DBGMASK_LI, (szCb.init.prntBuf, 
           "SzLiSctBndReq(pst, suId: %d, spId: %d)\n", suId, spId));
#endif /* DEBUGP */

   /* jump to specific primitive depending on configured selector */
   RETVALUE((*SzLiSctBndReqMt[pst->selector])(pst, suId, spId));
} /* end of SzLiSctBndReq */




/*
*
*       Fun:   Opening of endpoint request
*
*       Desc:  This function is used to request the opening of
*              an endpoint at the SCTP layer.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sz_ptli.c
*
*/

#ifdef SCT_ENDP_MULTI_IPADDR
#ifdef ANSI
PUBLIC S16 SzLiSctEndpOpenReq      
( 
Pst            *pst,
SpId           spId,
UConnId        suEndpId,
SctPort        port,
SctNetAddrLst  *srcAddrLst         /* Interface IP address List  */
)
#else
PUBLIC S16 SzLiSctEndpOpenReq (pst, spId, suEndpId, port, srcAddrLst)
Pst            *pst;
SpId           spId;
UConnId        suEndpId;
SctPort        port;
SctNetAddrLst  *srcAddrLst;       /* Interface IP address List  */
#endif
#else /* SCT_ENDP_MULTI_IPADDR */
#ifdef ANSI
PUBLIC S16 SzLiSctEndpOpenReq
(
Pst            *pst,
SpId           spId,
UConnId        suEndpId,
SctPort        port,
CmNetAddr      *intfNAddr
)
#else
PUBLIC S16 SzLiSctEndpOpenReq (pst, spId, suEndpId, port, intfNAddr )
Pst            *pst;
SpId           spId;
UConnId        suEndpId;
SctPort        port;
CmNetAddr      *intfNAddr;
#endif
#endif /* SCT_ENDP_MULTI_IPADDR */

{
   TRC3(SzLiSctEndpOpenReq);
   
#ifdef DEBUGP
   {
#ifndef ALIGN_64BIT
      SZDBGP (DBGMASK_LI, (szCb.init.prntBuf, 
              "SzLiSctEndpOpenReq(pst, spId: %d, suEndpId: %ld, port: %d )\n",
              spId, suEndpId, port));
#else
      SZDBGP (DBGMASK_LI, (szCb.init.prntBuf, 
              "SzLiSctEndpOpenReq(pst, spId: %d, suEndpId: %d, port: %d )\n",
              spId, suEndpId, port));
#endif
   }
#endif /* DEBUGP */

   /* jump to specific primitive depending on configured selector */
#ifdef SCT_ENDP_MULTI_IPADDR
   RETVALUE((*SzLiSctEndpOpenReqMt[pst->selector])(pst, spId, suEndpId, port, 
                                                   srcAddrLst));
#else
   RETVALUE((*SzLiSctEndpOpenReqMt[pst->selector])(pst, spId, suEndpId, port, 
                                                   intfNAddr));
#endif
} /* end of SzLiSctEndpOpenReq */




/*
*
*       Fun:   Endpoint closing request
*
*       Desc:  This function is used to send a request for the closing of 
*              the SCTP endpoint
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sz_ptli.c
*
*/

#ifdef ANSI
PUBLIC S16 SzLiSctEndpCloseReq
(
Pst *pst,                 /* post structure */
SpId spId,                /* service provider SAPID */
UConnId endpId,           /* endpoint ID */
U8 endpIdType             /* endpoint ID type */
)
#else
PUBLIC S16 SzLiSctEndpCloseReq(pst, spId, endpId, endpIdType)
Pst *pst;                 /* post structure */
SpId spId;                /* service provider SAPID */
UConnId endpId;           /* endpoint ID */
U8 endpIdType;            /* endpoint ID type */
#endif
{
   TRC3(SzLiSctEndpCloseReq);
   
#ifdef DEBUGP
   {
#ifndef ALIGN_64BIT
      SZDBGP (DBGMASK_LI, (szCb.init.prntBuf, 
              "SzLiSctEndpCloseReq(pst, spId: %d, endpId: %ld, "
              "endpIdType: %d)\n",
              spId, endpId, endpIdType));
#else
      SZDBGP (DBGMASK_LI, (szCb.init.prntBuf, 
              "SzLiSctEndpCloseReq(pst, spId: %d, endpId: %d, "
              "endpIdType: %d)\n",
              spId, endpId, endpIdType));
#endif
   }
#endif /* DEBUGP */

   /* jump to specific primitive depending on configured selector */
   RETVALUE((*SzLiSctEndpCloseReqMt[pst->selector])(pst, spId, endpId, 
                                                    endpIdType));
} /* end of SzLiSctEndpCloseReq */



#ifdef SCT3

/*
*
*       Fun:   Association establishment request
*
*       Desc:  This function is used to send a request for the closing of 
*              the SCTP endpoint
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sz_ptli.c
*
*/

#ifdef ANSI
PUBLIC S16 SzLiSctAssocReq
(
Pst *pst,                  /* post structure */
SpId spId,                 /* service provider SAP ID */
UConnId spEndpId,          /* service provider endpoint ID */
UConnId suAssocId,         /* service userassociation ID */
CmNetAddr *priDstNAddr,    /* primary destination network address */
SctPort dstPort,           /* destination port number */
SctStrmId outStrms,        /* no. of outgoing streams */
SctNetAddrLst *dstNAddrLst, /* dest. network address list */
SctNetAddrLst *srcNAddrLst, /* src. network address list */
SctTos        tos,
Buffer *vsInfo              /* vendor specific info */
)
#else
PUBLIC S16 SzLiSctAssocReq(pst, spId, spEndpId, suAssocId, priDstNAddr, dstPort,
outStrms, dstNAddrLst, srcNAddrLst, tos, vsInfo)
Pst *pst;                  /* post structure */
SpId spId;                 /* service provider SAP ID */
UConnId spEndpId;          /* service provider endpoint ID */
UConnId suAssocId;         /* service userassociation ID */
CmNetAddr *priDstNAddr;    /* primary destination network address */
SctPort dstPort;           /* destination port number */
SctStrmId outStrms;        /* no. of outgoing streams */
SctNetAddrLst *dstNAddrLst; /* dest. network address list */
SctNetAddrLst *srcNAddrLst; /* src. network address list */
SctTos        tos;
Buffer *vsInfo;             /* vendor specific info */
#endif
#else
#ifdef ANSI
PUBLIC S16 SzLiSctAssocReq
(
Pst *pst,                  /* post structure */
SpId spId,                 /* service provider SAP ID */
UConnId spEndpId,          /* service provider endpoint ID */
UConnId suAssocId,         /* service userassociation ID */
CmNetAddr *priDstNAddr,    /* primary destination network address */
SctPort dstPort,           /* destination port number */
SctStrmId outStrms,        /* no. of outgoing streams */
SctNetAddrLst *dstNAddrLst, /* dest. network address list */
SctNetAddrLst *srcNAddrLst, /* src. network address list */
Buffer *vsInfo              /* vendor specific info */
)
#else
PUBLIC S16 SzLiSctAssocReq(pst, spId, spEndpId, suAssocId, priDstNAddr, dstPort,
outStrms, dstNAddrLst, srcNAddrLst, vsInfo)
Pst *pst;                  /* post structure */
SpId spId;                 /* service provider SAP ID */
UConnId spEndpId;          /* service provider endpoint ID */
UConnId suAssocId;         /* service userassociation ID */
CmNetAddr *priDstNAddr;    /* primary destination network address */
SctPort dstPort;           /* destination port number */
SctStrmId outStrms;        /* no. of outgoing streams */
SctNetAddrLst *dstNAddrLst; /* dest. network address list */
SctNetAddrLst *srcNAddrLst; /* src. network address list */
Buffer *vsInfo;             /* vendor specific info */
#endif
#endif /* SCT3 */
{
   TRC3(SzLiSctAssocReq);
   
#ifdef DEBUGP
   {
      /* ICNC : print priDstNAddr, dst(src)NAddrLst contents */

#ifndef ALIGN_64BIT
      SZDBGP (DBGMASK_LI, (szCb.init.prntBuf, 
              "SzLiSctAssocReq(pst, spId: %d, spEndpId: %ld, "
              "suAssocId: %ld, dstPort: %d, outStrms: %d)\n",
              spId, spEndpId, suAssocId, dstPort, outStrms));
#else
      SZDBGP (DBGMASK_LI, (szCb.init.prntBuf, 
              "SzLiSctAssocReq(pst, spId: %d, spEndpId: %d, "
              "suAssocId: %d, dstPort: %d, outStrms: %d)\n",
              spId, spEndpId, suAssocId, dstPort, outStrms));
#endif
   }
#endif /* DEBUGP */

#ifdef SCT3
   /* jump to specific primitive depending on configured selector */
   RETVALUE((*SzLiSctAssocReqMt[pst->selector])(pst, spId, spEndpId, suAssocId,
                                                priDstNAddr, dstPort, outStrms, 
                                                dstNAddrLst, srcNAddrLst, tos,
                                                vsInfo));
#else
   /* jump to specific primitive depending on configured selector */
   RETVALUE((*SzLiSctAssocReqMt[pst->selector])(pst, spId, spEndpId, suAssocId,
                                                priDstNAddr, dstPort, outStrms, 
                                                dstNAddrLst, srcNAddrLst, 
                                                vsInfo));
#endif
} /* end of SzLiSctAssocReq */



/*
*
*       Fun:   Association Establishment response
*
*       Desc:  This function is used by the service user to respond to an 
*              association iniitialization indication by accepting the 
*              association.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sz_ptli.c
*
*/

#ifdef SCT3
#ifdef ANSI
PUBLIC S16 SzLiSctAssocRsp
(
Pst *pst,                  /* post structure */
SpId spId,                 /* service provider SAP ID */
UConnId spAssocId,         /* service provider association ID */
SctAssocIndParams *assocIndParams, /* association parameters */
SctTos             tos,
SctResult result,          /* result */
Buffer *vsInfo             /* vendor specific info */
)
#else
PUBLIC S16 SzLiSctAssocRsp(pst, spId, spAssocId, assocIndParams, tos, result, vsInfo)
Pst *pst;                  /* post structure */
SpId spId;                 /* service provider SAP ID */
UConnId spAssocId;         /* service provider association ID */
SctAssocIndParams *assocIndParams; /* association parameters */
SctTos             tos;
SctResult result;          /* result */
Buffer *vsInfo;            /* vendor specific info */
#endif
#else
#ifdef ANSI
PUBLIC S16 SzLiSctAssocRsp
(
Pst *pst,                  /* post structure */
SpId spId,                 /* service provider SAP ID */
UConnId spAssocId,         /* service provider association ID */
SctAssocIndParams *assocIndParams, /* association parameters */
SctResult result,          /* result */
Buffer *vsInfo             /* vendor specific info */
)
#else
PUBLIC S16 SzLiSctAssocRsp(pst, spId, spAssocId, assocIndParams, result, vsInfo)
Pst *pst;                  /* post structure */
SpId spId;                 /* service provider SAP ID */
UConnId spAssocId;         /* service provider association ID */
SctAssocIndParams *assocIndParams; /* association parameters */
SctResult result;          /* result */
Buffer *vsInfo;            /* vendor specific info */
#endif
#endif /* SCT3 */
{
   TRC3(SzLiSctAssocRsp);
   
#ifdef DEBUGP
   if (assocIndParams->type == SCT_ASSOC_IND_INIT)
   {
       /* ICNC : print peerAddrLst, localAddrLst & hstName contents */

       SctInitParams *ip;

       ip = &(assocIndParams->t.initParams);

#ifndef ALIGN_64BIT
       SZDBGP (DBGMASK_LI, (szCb.init.prntBuf, 
               "\nSzLiSctAssocRsp(pst, spId: %d, spAssocId: %ld, "
               "result: %d, assocIndParams->type: %d, "
               "initParams: iTag: %ld, a_rwnd: %ld, "
               "outStrms: %d, inStrms: %d)\n",
               spId, spAssocId, result, assocIndParams->type,
               ip->iTag, ip->a_rwnd, ip->outStrms, ip->inStrms));
#else
      SZDBGP (DBGMASK_LI, (szCb.init.prntBuf, 
              "\nSzLiSctAssocRsp(pst, spId: %d, spAssocId: %d, "
              "result: %d, assocIndParams->type: %d, "
              "initParams: iTag: %d, a_rwnd: %d, "
              "outStrms: %d, inStrms: %d)\n",
              spId, spAssocId, result, assocIndParams->type,
              ip->iTag, ip->a_rwnd, ip->outStrms, ip->inStrms));
#endif

      }
      else if (assocIndParams->type == SCT_ASSOC_IND_COOKIE)
      {
         /* ICNC : print peerAddrLst contents */

         SctCookieParams *cp;

         cp = &(assocIndParams->t.cookieParams);

#ifndef ALIGN_64BIT
         SZDBGP (DBGMASK_LI, (szCb.init.prntBuf, 
                 "\nSzLiSctAssocRsp(pst, spId: %d, spAssocId: %ld, "
                 "result: %d, assocIndParams->type: %d, "
                 "cookieParams: spAssocId: %ld, suAssocId: %ld, "
                 "peerPort: %d)\n",
                 spId, spAssocId, result, assocIndParams->type,
                 cp->spAssocId, cp->suAssocId, cp->peerPort));
#else
         SZDBGP (DBGMASK_LI, (szCb.init.prntBuf, 
                 "\nSzLiSctAssocRsp(pst, spId: %d, spAssocId: %d, "
                 "result: %d, assocIndParams->type: %d, "
                 "cookieParams: spAssocId: %d, suAssocId: %d, "
                 "peerPort: %d)\n",
                 spId, spAssocId, result, assocIndParams->type,
                 cp->spAssocId, cp->suAssocId, cp->peerPort));
#endif
   }
#endif /* DEBUGP */

#ifdef SCT3
   /* jump to specific primitive depending on configured selector */
   RETVALUE((*SzLiSctAssocRspMt[pst->selector])(pst, spId, spAssocId, 
                                                assocIndParams, tos, result, 
                                                vsInfo));
#else
   /* jump to specific primitive depending on configured selector */
   RETVALUE((*SzLiSctAssocRspMt[pst->selector])(pst, spId, spAssocId, 
                                                assocIndParams, result, 
                                                vsInfo));
#endif
} /* end of SzLiSctAssocRsp */

#ifdef SZ_PHASE2
/*
*
*       Fun:   Enable/Disable Heartbeat request
*
*       Desc:  This function is used by the service user to enable/disable
*              heartbeat either on an association or on a destination transport
*              address in an association.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  su_ptli.c
*
*/
#ifdef ANSI
PUBLIC S16 SzLiSctHBeatReq
(
Pst                *pst,                /* Post Structure */
SpId                spId,               /* Service Provider Identifier */
UConnId             spAssocId,          /* Service provider Association ID */
CmNetAddr          *dstNAddr,           /* IP Network Address pointer */
U16                 intervalTime,       /* Heart-Beat Periodicity Timeout */
SctStatus           status              /* Status */
)
#else
PUBLIC S16 SzLiSctHBeatReq(pst, spId, spAssocId, dstNAddr, intervalTime,
   status)
Pst                *pst;                /* Post Structure */
SpId                spId;               /* Service Provider Identifier */
UConnId             spAssocId;          /* Service provider Association ID */
CmNetAddr          *dstNAddr;           /* IP Network Address pointer */
U16                 intervalTime;       /* Heart-Beat Periodicity Timeout */
SctStatus           status;             /* Status */
#endif
{
   TRC3(SzLiSctHBeatReq)
   /* jump to specific primitive depending on configured selector */
   (*SzLiSctHBeatReqMt[pst->selector])(pst, spId, spAssocId, dstNAddr,
                                       intervalTime, status);
   RETVALUE(ROK);
} /* end of SzLiSctHBeatReq */
#endif /* SZ_PHASE2 */



/*
*
*       Fun:   Association Termination Request
*
*       Desc:  This function is used to request the termination of an 
*              association which is either established or being established.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sz_ptli.c
*
*/

#ifdef ANSI
#ifdef S1SIMAPP
PUBLIC S16 SzLiSctTermReq
(
Pst *pst,                 /* post structure */
SpId spId,                /* service provider SAP ID */
UConnId assocId,          /* association ID */
U8 assocIdType,           /* association ID type */
Bool abrtFlg,              /* abort flag */
U8   cause
)
#else
PUBLIC S16 SzLiSctTermReq
(
Pst *pst,                 /* post structure */
SpId spId,                /* service provider SAP ID */
UConnId assocId,          /* association ID */
U8 assocIdType,           /* association ID type */
Bool abrtFlg              /* abort flag */
)
#endif
#else
#ifdef S1SIMAPP
PUBLIC S16 SzLiSctTermReq(pst, spId, assocId, assocIdType, abrtFlg,cause)
Pst *pst;                 /* post structure */
SpId spId;                /* service provider SAP ID */
UConnId assocId;          /* association ID */
U8 assocIdType;           /* association ID type */
Bool abrtFlg;             /* abort flag */
U8   cause;
#else
PUBLIC S16 SzLiSctTermReq(pst, spId, assocId, assocIdType, abrtFlg)
Pst *pst;                 /* post structure */
SpId spId;                /* service provider SAP ID */
UConnId assocId;          /* association ID */
U8 assocIdType;           /* association ID type */
Bool abrtFlg;             /* abort flag */
#endif
#endif
{
   TRC3(SzLiSctTermReq);
   
#ifdef DEBUGP
   {
#ifndef ALIGN_64BIT
      SZDBGP (DBGMASK_LI, (szCb.init.prntBuf, 
              "SzLiSctTermReq(pst, spId: %d, assocId: %ld, "
              "assocIdType: %d, abrtFlg: %d)\n",
              spId, assocId, assocIdType, abrtFlg));
#else
      SZDBGP (DBGMASK_LI, (szCb.init.prntBuf, 
              "SzLiSctTermReq(pst, spId: %d, assocId: %d, "
              "assocIdType: %d, abrtFlg: %d)\n",
              spId, assocId, assocIdType, abrtFlg));
#endif
   }
#endif /* DEBUGP */

#ifdef S1SIMAPP
   /* jump to specific primitive depending on configured selector */
   RETVALUE((*SzLiSctTermReqMt[pst->selector])(pst, spId, assocId, assocIdType, 
                                               abrtFlg,cause));
#else
   /* jump to specific primitive depending on configured selector */
   RETVALUE((*SzLiSctTermReqMt[pst->selector])(pst, spId, assocId, assocIdType, 
                                               abrtFlg));
#endif
} /* end of SzLiSctTermReq */


#ifdef SZ_PHASE2

/*
*
*       Fun:   Set Primary Destination Address request
*
*       Desc:  This function is used to set a particular
*              primary destination address.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sz_ptli.c
*
*/

#ifdef ANSI
PUBLIC S16 SzLiSctSetPriReq
(
Pst *pst,                 /* post structure */
SpId spId,                /* service provider SAP ID */
UConnId spAssocId,        /* service provider association ID */
CmNetAddr *dstNAddr       /* dest. network address */
)
#else
PUBLIC S16 SzLiSctSetPriReq(pst, spId, spAssocId, dstNAddr)
Pst *pst;                 /* post structure */
SpId spId;                /* service provider SAP ID */
UConnId spAssocId;        /* service provider association ID */
CmNetAddr *dstNAddr;      /* dest. network address */
#endif
{
   TRC3(SzLiSctSetPriReq);
   
#ifdef DEBUGP
   {
      /* ICNC : print dstNAddr contents */

#ifndef ALIGN_64BIT
      SZDBGP (DBGMASK_LI, (szCb.init.prntBuf, 
              "SzLiSctSetPriReq(pst, spId: %d, spAssocId: %ld)\n",
              spId, spAssocId));
#else
      SZDBGP (DBGMASK_LI, (szCb.init.prntBuf, 
              "SzLiSctSetPriReq(pst, spId: %d, spAssocId: %d)\n",
              spId, spAssocId));
#endif
   }
#endif /* DEBUGP */

   /* jump to specific primitive depending on configured selector */
   RETVALUE((*SzLiSctSetPriReqMt[pst->selector])(pst, spId, spAssocId,
                                                 dstNAddr));
} /* end of SzLiSctSetPriReq */

#endif /* SZ_PHASE2 */



/*
*
*       Fun:   Data request
*
*       Desc:  This function is used to request the service provider to send a
*              user datagram to the destination.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sz_ptli.c
*
*/

#ifdef ANSI
PUBLIC S16 SzLiSctDatReq
(
Pst *pst,                 /* post structure */
SpId spId,                /* service provider SAP ID */
UConnId spAssocId,        /* service provider association ID */
CmNetAddr *dstNAddr,      /* dest. network address */
SctStrmId strmId,         /* stream ID */
Bool unorderFlg,          /* unordered delivery flag */
Bool nobundleFlg,         /* nobundleFlg */
U16 lifetime,             /* datagram lifetime */
U32 protId,               /* protocol ID */
Buffer *mBuf              /* message buffer */
)
#else
PUBLIC S16 SzLiSctDatReq(pst, spId, spAssocId, dstNAddr, strmId, unorderFlg, 
                         nobundleFlg, lifetime, protId, mBuf)
Pst *pst;                 /* post structure */
SpId spId;                /* service provider SAP ID */
UConnId spAssocId;        /* service provider association ID */
CmNetAddr *dstNAddr;      /* dest. network address */
SctStrmId strmId;         /* stream ID */
Bool unorderFlg;          /* unordered delivery flag */
Bool nobundleFlg;         /* nobundleFlg */
U16 lifetime;             /* datagram lifetime */
U32 protId;               /* protocol ID */
Buffer *mBuf;             /* message buffer */
#endif
{
   TRC3(SzLiSctDatReq);
   
#ifdef DEBUGP
   {
      /* ICNC : print dstNAddr contents */

#ifndef ALIGN_64BIT
      SZDBGP (DBGMASK_LI, (szCb.init.prntBuf, 
              "SzLiSctDatReq(pst, spId: %d, spAssocId: %ld, "
              "strmId: %d, unorderFlg: %d, nobundleFlg: %d, "
              "lifetime: %d, protId: %ld)\n",
              spId, spAssocId, strmId, unorderFlg, nobundleFlg,
              lifetime, protId));
#else
      SZDBGP (DBGMASK_LI, (szCb.init.prntBuf, 
              "SzLiSctDatReq(pst, spId: %d, spAssocId: %d, "
              "strmId: %d, unorderFlg: %d, nobundleFlg: %d, "
              "lifetime: %d, protId: %d)\n",
              spId, spAssocId, strmId, unorderFlg, nobundleFlg,
              lifetime, protId));
#endif
   }
#endif /* DEBUGP */


   /* jump to specific primitive depending on configured selector */
   RETVALUE((*SzLiSctDatReqMt[pst->selector])(pst, spId, spAssocId, dstNAddr, 
                                              strmId, unorderFlg, nobundleFlg, 
                                              lifetime, protId, mBuf));
} /* end of SzLiSctDatReq */



/*
*
*       Fun:   Status request
*
*       Desc:  This function is used to retrieve 
*              unsent/unacknowledged/undelivered datagrams from the service 
*              provider and to get statistical information from the service 
*              provider.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sz_ptli.c
*
*/

#ifdef ANSI
PUBLIC S16 SzLiSctStaReq
(
Pst *pst,                 /* post structure */
SpId spId,                /* service provider SAP ID */
UConnId spAssocId,        /* service provider association ID */
CmNetAddr *dstNAddr,      /* dest. network address */
U8 staType                /* status type */
)
#else
PUBLIC S16 SzLiSctStaReq(pst, spId, spAssocId, dstNAddr, staType)
Pst *pst;                 /* post structure */
SpId spId;                /* service provider SAP ID */
UConnId spAssocId;        /* service provider association ID */
CmNetAddr *dstNAddr;      /* dest. network address */
U8 staType;               /* status type */
#endif
{
   TRC3(SzLiSctStaReq);

#ifdef DEBUGP
   {
      /* ICNC : print dstNAddr contents */

#ifndef ALIGN_64BIT
      SZDBGP (DBGMASK_LI, (szCb.init.prntBuf, 
              "SzLiSctStaReq(pst, spId: %d, spAssocId: %ld, "
              "staType: %d)\n",
              spId, spAssocId, staType));
#else
      SZDBGP (DBGMASK_LI, (szCb.init.prntBuf, 
              "SzLiSctStaReq(pst, spId: %d, spAssocId: %d, "
              "staType: %d)\n",
              spId, spAssocId, staType));
#endif
   }
#endif /* DEBUGP */

   /* jump to specific primitive depending on configured selector */
   RETVALUE((*SzLiSctStaReqMt[pst->selector])(pst, spId, spAssocId, dstNAddr, 
                                              staType));
} /* end of SzLiSctStaReq */


#if (!defined SB || !defined LCSZLISCT || !defined HI_LKSCTP || !defined HI || !defined DM)


/*
*
*       Fun:   Portable bind Request
*
*       Desc:  This function is used to request a bind
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sz_ptli.c
*
*/

#ifdef ANSI
PRIVATE S16 PtLiSctBndReq
(
Pst *pst,                 /* post structure */
SuId suId,                /* Service user SAP Id */
SpId spId                /* Service provider SAP Id */
)
#else
PRIVATE S16 PtLiSctBndReq(pst, suId, spId)
Pst *pst;                 /* post structure */
SuId suId;                /* Service user SAP Id */
SpId spId;                /* Service provider SAP Id */
#endif
{
   TRC3(PtLiSctBndReq);

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(spId);
   RETVALUE(ROK);
} /* end of PtLiSctBndReq */




/*
*
*       Fun:   Portable open endpoint request
*
*       Desc:  This function is used to request a new endpoint
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sz_ptli.c
*
*/

#ifdef SCT_ENDP_MULTI_IPADDR
#ifdef ANSI
PRIVATE S16 PtLiSctEndpOpenReq
(
Pst *pst,                    /* post structure */
SpId spId,                   /* Service provider SAP Id */
UConnId suEndpId,            /* Service user Endpoint Id */
U16 port,                    /* SCTP Port number */
SctNetAddrLst  *srcAddrLst   /* Interface IP address List  */
)
#else
PRIVATE S16 PtLiSctEndpOpenReq(pst, spId, suEndpId, port,srcAddrLst)
Pst *pst;                    /* post structure */
SpId spId;                   /* Service provider SAP Id */
UConnId suEndpId;            /* Service user Endpoint Id */
U16 port;                    /* SCTP Port number */
SctNetAddrLst  *srcAddrLst;  /* Interface IP address List  */
#endif
#else /* SCT_ENDP_MULTI_IPADDR */
#ifdef ANSI
PRIVATE S16 PtLiSctEndpOpenReq
(
Pst *pst,                    /* post structure */
SpId spId,                   /* Service provider SAP Id */
UConnId suEndpId,            /* Service user Endpoint Id */
U16 port,                    /* SCTP Port number */
CmNetAddr   *intfNAddr       /* Interface IP address*/
)
#else
PRIVATE S16 PtLiSctEndpOpenReq(pst, spId, suEndpId, port,intfNAddr)
Pst *pst;                    /* post structure */
SpId spId;                   /* Service provider SAP Id */
UConnId suEndpId;            /* Service user Endpoint Id */
U16 port;                    /* SCTP Port number */
CmNetAddr    *intfNAddr;     /* Interface IP address*/
#endif
#endif /* SCT_ENDP_MULTI_IPADDR */

{
   TRC3(PtLiSctEndpOpenReq);


   UNUSED(pst);
   UNUSED(spId);
   UNUSED(suEndpId);
   UNUSED(port);
#ifdef SCT_ENDP_MULTI_IPADDR   
   UNUSED(srcAddrLst);
#else
   UNUSED(intfNAddr);
#endif
   RETVALUE(ROK);
} /* end of PtLiSctEndpOpenReq */




/*
*
*       Fun:   Portable close endpoint request
*  
*       Desc:  This function is used to close an endpoint
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sz_ptli.c
*
*/

#ifdef ANSI
PRIVATE S16 PtLiSctEndpCloseReq
(
Pst *pst,                 /* post structure */
SpId spId,                /* service provider SAPID */
UConnId endpId,           /* endpoint ID */
U8 endpIdType             /* endpoint ID type */
)
#else
PRIVATE S16 PtLiSctEndpCloseReq(pst, spId, endpId, endpIdType)
Pst *pst;                 /* post structure */
SpId spId;                /* service provider SAPID */
UConnId endpId;           /* endpoint ID */
U8 endpIdType;            /* endpoint ID type */
#endif
{
   TRC3(PtLiSctEndpCloseReq);


   UNUSED(pst);
   UNUSED(spId);
   UNUSED(endpId);
   UNUSED(endpIdType);
   RETVALUE(ROK);
} /* end of PtLiSctEndpCloseReq */




/*
*
*       Fun:   Portable Association request
*
*       Desc:  This function is used to request a new association
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sz_ptli.c
*
*/
#ifdef SCT3
#ifdef ANSI
PRIVATE S16 PtLiSctAssocReq
(
Pst *pst,                  /* post structure */
SpId spId,                 /* service provider SAP ID */
UConnId spEndpId,        /* service provider endpoint ID */
UConnId suAssocId,      /* service userassociation ID */
CmNetAddr *priDstNAddr,    /* primary destination network address */
U16 dstPort,               /* destination port number */
SctStrmId outStrms,        /* no. of outgoing streams */
SctNetAddrLst *dstNAddrLst, /* dest. network address list */
SctNetAddrLst *srcNAddrLst, /* src. network address list */
SctTos          tos,
Buffer *vsInfo          /* vendor specific info */
)
#else
PRIVATE S16 PtLiSctAssocReq(pst, spId, spEndpId, suAssocId, priDstNAddr, 
                            dstPort, outStrms, dstNAddrLst, srcNAddrLst, tos,vsInfo)
Pst *pst;                  /* post structure */
SpId spId;                 /* service provider SAP ID */
UConnId spEndpId;        /* service provider endpoint ID */
UConnId suAssocId;      /* service userassociation ID */
CmNetAddr *priDstNAddr;    /* primary destination network address */
U16 dstPort;               /* destination port number */
SctStrmId outStrms;        /* no. of outgoing streams */
SctNetAddrLst *dstNAddrLst; /* dest. network address list */
SctNetAddrLst *srcNAddrLst; /* src. network address list */
SctTos          tos;
Buffer *vsInfo;          /* vendor specific info */
#endif
#else /*-- SCT3 --*/
#ifdef ANSI
PRIVATE S16 PtLiSctAssocReq
(
Pst *pst,                  /* post structure */
SpId spId,                 /* service provider SAP ID */
UConnId spEndpId,        /* service provider endpoint ID */
UConnId suAssocId,      /* service userassociation ID */
CmNetAddr *priDstNAddr,    /* primary destination network address */
U16 dstPort,               /* destination port number */
SctStrmId outStrms,        /* no. of outgoing streams */
SctNetAddrLst *dstNAddrLst, /* dest. network address list */
SctNetAddrLst *srcNAddrLst, /* src. network address list */
Buffer *vsInfo          /* vendor specific info */
)
#else
PRIVATE S16 PtLiSctAssocReq(pst, spId, spEndpId, suAssocId, priDstNAddr, 
                            dstPort, outStrms, dstNAddrLst, srcNAddrLst, vsInfo)
Pst *pst;                  /* post structure */
SpId spId;                 /* service provider SAP ID */
UConnId spEndpId;        /* service provider endpoint ID */
UConnId suAssocId;      /* service userassociation ID */
CmNetAddr *priDstNAddr;    /* primary destination network address */
U16 dstPort;               /* destination port number */
SctStrmId outStrms;        /* no. of outgoing streams */
SctNetAddrLst *dstNAddrLst; /* dest. network address list */
SctNetAddrLst *srcNAddrLst; /* src. network address list */
Buffer *vsInfo;          /* vendor specific info */
#endif
#endif /*-- SCT3 --*/
{
   TRC3(PtLiSctAssocReq);


   UNUSED(pst);
   UNUSED(spId);
   UNUSED(spEndpId);
   UNUSED(suAssocId);
   UNUSED(priDstNAddr);
   UNUSED(dstPort);
   UNUSED(outStrms);
   UNUSED(dstNAddrLst);
   UNUSED(srcNAddrLst);
   if (vsInfo != (Buffer *)NULLP)
   {
      SPutMsg(vsInfo);
   }

   RETVALUE(ROK);
} /* end of PtLiSctAssocReq */




/*
*
*       Fun:   Portable association response
*
*       Desc:  This function is used to respond to an association indication
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sz_ptli.c
*
*/
#ifdef SCT3
#ifdef ANSI
PRIVATE S16 PtLiSctAssocRsp
(
Pst *pst,                  /* post structure */
SpId spId,                 /* service provider SAP ID */
UConnId spAssocId,         /* service provider association ID */
SctAssocIndParams *assocIndParams, /* association parameters */
SctTos          tos,
SctResult result,          /* result */
Buffer *vsInfo             /* vendor specific info */
)
#else
PRIVATE S16 PtLiSctAssocRsp(pst, spId, spAssocId, assocIndParams, tos, result, 
                            vsInfo)
Pst *pst;                  /* post structure */
SpId spId;                 /* service provider SAP ID */
UConnId spAssocId;         /* service provider association ID */
SctAssocIndParams *assocIndParams; /* association parameters */
SctTos          tos;
SctResult result;          /* result */
Buffer *vsInfo;            /* vendor specific info */
#endif
#else /*-- SCT3 --*/
#ifdef ANSI
PRIVATE S16 PtLiSctAssocRsp
(
Pst *pst,                  /* post structure */
SpId spId,                 /* service provider SAP ID */
UConnId spAssocId,         /* service provider association ID */
SctAssocIndParams *assocIndParams, /* association parameters */
SctResult result,          /* result */
Buffer *vsInfo             /* vendor specific info */
)
#else
PRIVATE S16 PtLiSctAssocRsp(pst, spId, spAssocId, assocIndParams, result, 
                            vsInfo)
Pst *pst;                  /* post structure */
SpId spId;                 /* service provider SAP ID */
UConnId spAssocId;         /* service provider association ID */
SctAssocIndParams *assocIndParams; /* association parameters */
SctResult result;          /* result */
Buffer *vsInfo;            /* vendor specific info */
#endif
#endif /*-- SCT3 --*/
{
   TRC3(PtLiSctAssocRsp);


   UNUSED(pst);
   UNUSED(spId);
   UNUSED(spAssocId);
   UNUSED(assocIndParams);
   UNUSED(result);
   if (vsInfo != (Buffer *)NULLP)
   {
      SPutMsg(vsInfo);
   }

   RETVALUE(ROK);
} /* end of PtLiSctAssocRsp */




/*
*
*       Fun:   Portable termination request
*
*       Desc:  This function is used to terminate an association
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sz_ptli.c
*
*/

#ifdef ANSI
PRIVATE S16 PtLiSctTermReq
(
Pst *pst,                 /* post structure */
SpId spId,                /* service provider SAP ID */
UConnId assocId,          /* association ID */
U8 assocIdType,           /* association ID type */
Bool abrtFlg              /* abort flag */
)
#else
PRIVATE S16 PtLiSctTermReq(pst, spId, assocId, assocIdType, abrtFlg)
Pst *pst;                 /* post structure */
SpId spId;                /* service provider SAP ID */
UConnId assocId;          /* association ID */
U8 assocIdType;           /* association ID type */
Bool abrtFlg;             /* abort flag */
#endif
{
   TRC3(PtLiSctTermReq);


   UNUSED(pst);
   UNUSED(spId);
   UNUSED(assocId);
   UNUSED(assocIdType);
   UNUSED(abrtFlg);
   RETVALUE(ROK);
} /* end of PtLiSctTermReq */




#ifdef SZ_PHASE2
/*
*
*       Fun:   Portable set Primary destination address request
*
*       Desc:  This function is used to set a particular
*              primary destination address
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sz_ptli.c
*
*/

#ifdef ANSI
PRIVATE S16 PtLiSctSetPriReq
(
Pst *pst,                 /* post structure */
SpId spId,                /* service provider SAP ID */
UConnId spAssocId,        /* service provider association ID */
CmNetAddr *dstNAddr       /* dest. network address */
)
#else
PRIVATE S16 PtLiSctSetPriReq(pst, spId, spAssocId, dstNAddr)
Pst *pst;                 /* post structure */
SpId spId;                /* service provider SAP ID */
UConnId spAssocId;        /* service provider association ID */
CmNetAddr *dstNAddr;      /* dest. network address */
#endif
{
   TRC3(PtLiSctSetPriReq);


   UNUSED(pst);
   UNUSED(spId);
   UNUSED(spAssocId);
   UNUSED(dstNAddr);
   RETVALUE(ROK);
} /* end of PtLiSctSetPriReq */
#endif /* SZ_PHASE2 */



/*
*
*       Fun:   Portable data Request
*
*       Desc:  This function is used to send data to a peer
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sz_ptli.c
*
*/

#ifdef ANSI
PRIVATE S16 PtLiSctDatReq
(
Pst *pst,                 /* post structure */
SpId spId,                /* service provider SAP ID */
UConnId spAssocId,        /* service provider association ID */
CmNetAddr *dstNAddr,      /* dest. network address */
SctStrmId strmId,         /* stream ID */
Bool unorderFlg,          /* unordered delivery flag */
Bool nobundleFlg,         /* nobundleFlg */
U16 lifetime,             /* datagram lifetime */
U32 protId,               /* protocol ID */
Buffer *mBuf              /* message buffer */
)
#else
PRIVATE S16 PtLiSctDatReq(pst, spId, spAssocId, dstNAddr, strmId, unorderFlg,
   nobundleFlg, lifetime, protId, mBuf)
Pst *pst;                 /* post structure */
SpId spId;                /* service provider SAP ID */
UConnId spAssocId;        /* service provider association ID */
CmNetAddr *dstNAddr;      /* dest. network address */
SctStrmId strmId;         /* stream ID */
Bool unorderFlg;          /* unordered delivery flag */
Bool nobundleFlg;         /* nobundleFlg */
U16 lifetime;             /* datagram lifetime */
U32 protId;               /* protocol ID */
Buffer *mBuf;             /* message buffer */
#endif
{
   TRC3(PtLiSctDatReq);


   UNUSED(pst);
   UNUSED(spId);
   UNUSED(spAssocId);
   UNUSED(dstNAddr);
   UNUSED(strmId);
   UNUSED(unorderFlg);
   UNUSED(nobundleFlg);
   UNUSED(lifetime);
   UNUSED(protId);
   if (mBuf != (Buffer *)NULLP)
   {
      SPutMsg(mBuf);
   }

   RETVALUE(ROK);
} /* end of PtLiSctDatReq */



/*
*
*       Fun:   Portable status request
*
*       Desc:  This function is used to request status
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sz_ptli.c
*
*/

#ifdef ANSI
PRIVATE S16 PtLiSctStaReq
(
Pst *pst,                 /* post structure */
SpId spId,                /* service provider SAP ID */
UConnId spAssocId,        /* service provider association ID */
CmNetAddr *dstNAddr,      /* dest. network address */
U8 staType                /* status type */
)
#else
PRIVATE S16 PtLiSctStaReq(pst, spId, spAssocId, dstNAddr, staType)
Pst *pst;                 /* post structure */
SpId spId;                /* service provider SAP ID */
UConnId spAssocId;        /* service provider association ID */
CmNetAddr *dstNAddr;      /* dest. network address */
U8 staType;               /* status type */
#endif
{
   TRC3(PtLiSctStaReq);


   UNUSED(pst);
   UNUSED(spId);
   UNUSED(spAssocId);
   UNUSED(dstNAddr);
   UNUSED(staType);
   RETVALUE(ROK);
} /* end of PtLiSctStaReq */


#ifdef SZ_PHASE2
/*
*
*       Fun:   Portable heart beat request
*
*       Desc:  Dummy heart beat request, customize if necessary
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  su_ptli.c
*
*/
#ifdef ANSI
PRIVATE S16 PtLiSctHBeatReq
(
Pst                *pst,                /* Post Structure */
SpId                spId,               /* Service Provider Identifier */
UConnId             spAssocId,          /* Service provider Association ID */
CmNetAddr          *dstNAddr,           /* IP Network Address pointer */
U16                 intervalTime,       /* Heart-Beat Periodicity Timeout */
SctStatus           status              /* Status */
)
#else
PRIVATE S16 PtLiSctHBeatReq(pst, spId, spAssocId, dstNAddr, intervalTime,
   status)
Pst                *pst;                /* Post Structure */
SpId                spId;               /* Service Provider Identifier */
UConnId             spAssocId;          /* Service provider Association ID */
CmNetAddr          *dstNAddr;           /* IP Network Address pointer */
U16                 intervalTime;       /* Heart-Beat Periodicity Timeout */
SctStatus           status;             /* Status */
#endif
{
   TRC3(PtLiSctHBeatReq);
#if (ERRCLASS & ERRCLS_DEBUG)
   SZLOGERROR(ERRCLS_DEBUG, ESZ119, (ErrVal) 0, "PtLiSctHBeatReq");
#endif
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(spAssocId);
   UNUSED(dstNAddr);
   UNUSED(intervalTime);
   UNUSED(status);

   RETVALUE(ROK);
} /* end of PtLiSctHBeatReq */
#endif

#endif /* end of (!defined SB || !defined LCSZLISCT || !defined HI_LKSCTP || !defined HI !defined DM) */





/********************************************************************30**

         End of file:     sq_ptli.c@@/main/4 - Mon Jan 10 22:17:03 2011

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
/main/4      ---      pkaX  1. Updated for S1AP release 3.1
/main/4   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
/main/4   sz006.301   ve    1. Removed un-necessary include files
/main/4   sz008.301  akaranth 1. Support for source RNC to target RNC 
*********************************************************************91*/
