


/********************************************************************20**

     Name:     SCTP Layer

     Type:     C source file

     Desc:     C source code for SB layer portable Lower Interface

     File:     sb_ptli.c

     Sid:      sb_ptli.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:17 2015

     Prg:      bk, wvdl

*********************************************************************21*/


/* header include files (.h) */

/* header/extern include files (.x) */



/*

The following functions are provided in this file:

     SbLiHitBndReq         upper interface - Bind Request
     SbLiHitServOpenReq    upper interface - Server Open Request
     SbLiHitConReq         upper interface - Connection Request
     SbLiHitConRsp         upper interface - Connection Responce
     SbLiHitDatReq         upper interface - Data Request
     SbLiHitUDatReq        upper interface - Unreliable Data Request
     SbLiHitDiscReq        upper interface - Disconnect Request

It should be noted that not all of these functions may be required
by a particular network layer service provider.


*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm_hash.h"       /* common hashing */
#include "cm_llist.h"      /* common linked list */
#include "cm_err.h"        /* common error */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"        /* common transport defines */
#ifdef SB_FTHA
#include "sht.h"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "sct.h"           /* sct interface */
#include "hit.h"           /* HIT interface */
#include "sb_mtu.h"
#include "lsb.h"           /* layer management SB */
#include "sb.h"            /* SB layer */
#include "sb_err.h"        /* SB error */

/* header/extern include files (.x) */

#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */
#include "cm_hash.x"       /* common hashing */
#include "cm_llist.x"      /* common linked list */
#include "cm_tpt.x"        /* common transport */
#include "cm_dns.x"        /* common transport defines */
#include "cm5.x"           /* common timer */
#ifdef SB_FTHA
#include "sht.x"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "sct.x"           /* sct interface */
#include "hit.x"           /* HIT interface */
#include "sb_mtu.x"
#include "lsb.x"           /* layer management SB */
#include "sb.x"            /* SB layer */



/* local defines */
#define MAXSBUI 2          /* max SB Layer upper users */

#ifndef LCSBLIHIT
#define PTSBLIHIT
#else
#ifndef HI
#define PTSBLIHIT
#else
#endif
#endif

/* local typedefs */

/* local externs */
/* sb028.103: Fix for compiler warnings. */
#ifdef __cplusplus
extern "C" {
#endif
#ifdef PTSBLIHIT

/* declaration of portable functions */
PRIVATE S16 PtLiHitBndReq  ARGS((Pst *pst, SuId suId, SpId spId));
PRIVATE S16 PtLiHitServOpenReq  ARGS((Pst *pst, SpId spId, UConnId servConId,
                                     CmTptAddr *servTAddr, CmTptParam *tPar,
                                     CmIcmpFilter *icmpFilter, U8 srvcType));
/* sb050.102 - Add tPar for HI_REL_1_4 */
#ifdef HI_REL_1_4
PRIVATE S16 PtLiHitUDatReq ARGS((Pst *pst, SpId spId, UConnId spConId,
                                 CmTptAddr *remAddr, CmTptAddr *srcAddr,
                                 CmIpHdrParm *hdrParm, CmTptParam *tPar,
                                 Buffer *mBuf));
#else
PRIVATE S16 PtLiHitUDatReq ARGS((Pst *pst, SpId spId, UConnId spConId,
                                 CmTptAddr *remAddr, CmTptAddr *srcAddr,
                                 CmIpHdrParm *hdrParm, Buffer *mBuf));
#endif /* HI_REL_1_4 */
PRIVATE S16 PtLiHitDiscReq ARGS((Pst *pst, SpId spId, U8 choice, UConnId conId,
                                Action action, CmTptParam *tPar));



#endif /* PTSBLIHIT */
/* sb028.103: Fix for the compiler warnings. */
#ifdef __cplusplus
}
#endif


/*
  The following matrices define the mapping between the primitives
  called by the upper interface of SCTP Layer
  and the corresponding primitives of the SCTP Layer
  service user(s).

  The parameter MAXSBUI defines the maximum number of service users on
  top of SCTP Layer. There is an array of functions
  per primitive invoked by SCTP Layer. Every array is
  MAXSBUI long(i.e.there are as many functions as the number of service
  users).

  The dispatcsbng is performed by the configurable variable: selector.
  The selector is configured on a per SAP basis.

  The selectors are:

  0 - loosely coupled (#define LCSBUISBT)
  1 - TUCL            (#define HI)
*/


PRIVATE HitBndReq SbLiHitBndReqMt[MAXSBUI] =
{
#ifdef LCSBLIHIT
   cmPkHitBndReq,         /* 0 - loosely coupled */
#else
   PtLiHitBndReq,         /* 0 - tightly coupled, portable */
#endif
#ifdef HI
   HiUiHitBndReq,         /* 1 - tightly coupled, TUCL */
#else
   PtLiHitBndReq,         /* 1 - tightly coupled, portable */
#endif
};

PRIVATE HitServOpenReq SbLiHitServOpenReqMt[MAXSBUI] =
{
#ifdef LCSBLIHIT
   cmPkHitServOpenReq,         /* 0 - loosely coupled */
#else
   PtLiHitServOpenReq,         /* 0 - loosely coupled, portable */
#endif
#ifdef HI
   HiUiHitServOpenReq,         /* 1 - tightly coupled, TUCL */
#else
   PtLiHitServOpenReq,         /* 1 - tightly coupled, portable */
#endif
};

PRIVATE HitUDatReq SbLiHitUDatReqMt[MAXSBUI] =
{
#ifdef LCSBLIHIT
   cmPkHitUDatReq,         /* 0 - loosely coupled */
#else
   PtLiHitUDatReq,         /* 0 - loosely coupled, portable */
#endif
#ifdef HI
   HiUiHitUDatReq,         /* 1 - tightly coupled, TUCL */
#else
   PtLiHitUDatReq,         /* 1 - tightly coupled, portable */
#endif
};

PRIVATE HitDiscReq SbLiHitDiscReqMt[MAXSBUI] =
{
#ifdef LCSBLIHIT
   cmPkHitDiscReq,         /* 0 - loosely coupled */
#else
   PtLiHitDiscReq,         /* 0 - loosely coupled, portable */
#endif
#ifdef HI
   HiUiHitDiscReq,         /* 1 - tightly coupled, TUCL */
#else
   PtLiHitDiscReq,         /* 1 - tightly coupled, portable */
#endif
};


/*
 *  lower interface functions
 */


/*
*
*       Fun:
*
*       Desc:
*
*       Ret:   ROK     - ok
*              RFAILED - not ok
*
*       Notes: None
*
*       File:  sb_ptli.c
*
*/
#ifdef ANSI
PUBLIC S16 SbLiHitBndReq
(
Pst *pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 SbLiHitBndReq(pst, suId, spId)
Pst *pst;
SuId suId;
SpId spId;
#endif
{
   TRC3(SbLiHitBndReq);
   /* sb043.102: the debug mask is for lower interface */
   SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
          "SbLiHitBndReq(pst, suId(%d), spId(%d))\n", suId, spId));

   /* jump to specific primitive depending on configured selector */
   (*SbLiHitBndReqMt[pst->selector])(pst, suId, spId);

   RETVALUE(ROK);
}



/*
*
*       Fun:
*
*       Desc:
*
*       Ret:   ROK     - ok
*              RFAILED - not ok
*
*       Notes: None
*
*       File:  sb_ptli.c
*
*/
#ifdef ANSI
PUBLIC S16 SbLiHitServOpenReq
(
Pst *pst,
SpId spId,
UConnId servConId,
CmTptAddr *servTAddr,
CmTptParam *tPar,
CmIcmpFilter *icmpFilter,
U8 srvcType
)
#else
PUBLIC S16 SbLiHitServOpenReq(pst, spId, servConId, servTAddr, tPar,
                              icmpFilter, srvcType)
Pst *pst;
SpId spId;
UConnId servConId;
CmTptAddr *servTAddr;
CmTptParam *tPar;
CmIcmpFilter *icmpFilter;
U8 srvcType;
#endif
{
   TRC3(SbLiHitServOpenReq);
   /* sb043.102: the debug mask is for lower interface */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
          "SbLiHitServOpenReq(pst, spId(%d), servConId(%d), servTAddr, tPar, icmpFilter, srvcType(%d))\n",
          spId, servConId, srvcType));
#else
   SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
          "SbLiHitServOpenReq(pst, spId(%d), servConId(%ld), servTAddr, tPar, icmpFilter, srvcType(%d))\n",
          spId, servConId, srvcType));
#endif /* BIT_64 */

   /* jump to specific primitive depending on configured selector */
   (*SbLiHitServOpenReqMt[pst->selector])(pst, spId, servConId, servTAddr,
                                          tPar, icmpFilter, srvcType);

   RETVALUE(ROK);
}



/*
*
*       Fun:
*
*       Desc:
*
*       Ret:   ROK     - ok
*              RFAILED - not ok
*
*       Notes: None
*
*       File:  sb_ptli.c
*
*/
/* sb012.102 additional parameter for TUCL1.4 */
#ifdef HI_REL_1_4
#ifdef ANSI
PUBLIC S16 SbLiHitUDatReq
(
Pst                 *pst,
SpId                 spId,
UConnId              spConId,
CmTptAddr           *remAddr,
CmTptAddr           *srcAddr,
CmIpHdrParm         *hdrParm,
CmTptParam          *tPar,
Buffer              *mBuf
)
#else
PUBLIC S16 SbLiHitUDatReq(pst, spId, spConId, remAddr, srcAddr, hdrParm, tPar, mBuf)
Pst                 *pst;
SpId                 spId;
UConnId              spConId;
CmTptAddr           *remAddr;
CmTptAddr           *srcAddr;
CmIpHdrParm         *hdrParm;
CmTptParam          *tPar;
Buffer              *mBuf;
#endif /* ANSI */
#else
#ifdef ANSI
PUBLIC S16 SbLiHitUDatReq
(
Pst                 *pst,
SpId                 spId,
UConnId              spConId,
CmTptAddr           *remAddr,
CmTptAddr           *srcAddr,
CmIpHdrParm         *hdrParm,
Buffer              *mBuf
)
#else
PUBLIC S16 SbLiHitUDatReq(pst, spId, spConId, remAddr, srcAddr, hdrParm, mBuf)
Pst                 *pst;
SpId                 spId;
UConnId              spConId;
CmTptAddr           *remAddr;
CmTptAddr           *srcAddr;
CmIpHdrParm         *hdrParm;
Buffer              *mBuf;
#endif /* ANSI */
#endif /* HI_REL_1_4 */
{
   TRC3(SbLiHitUDatReq)
   /* sb043.102: the debug mask is for lower interface */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
          "SbLiHitUDatReq(pst, spId(%d), spConId(%d), remAddr, mBuf)\n",
          spId, spConId));
#else
   SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
          "SbLiHitUDatReq(pst, spId(%d), spConId(%ld), remAddr, mBuf)\n",
          spId, spConId));
#endif /* BIT_64 */

   SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
          "pst(dstEnt(%d), dstInst(%d), srcEnt(%d), srcInst(%d), selector(%d)\n",
          pst->dstEnt, pst->dstInst, pst->srcEnt, pst->srcInst, pst->selector));

   /* jump to specific primitive depending on configured selector */
   (*SbLiHitUDatReqMt[pst->selector])(pst, spId, spConId, remAddr, srcAddr,
                                      hdrParm, 
  /* sb012.102 additional parameter for TUCL1.4 */
#ifdef HI_REL_1_4
                                      tPar,
#endif /* HI_REL_1_4 */
                                      mBuf);

   RETVALUE(ROK);
}



/*
*
*       Fun:
*
*       Desc:
*
*       Ret:   ROK     - ok
*              RFAILED - not ok
*
*       Notes: None
*
*       File:  sb_ptli.c
*
*/
#ifdef ANSI
PUBLIC S16 SbLiHitDiscReq
(
Pst *pst,
SpId spId,
U8 choice,
UConnId conId,
Action action,
CmTptParam *tPar
)
#else
PUBLIC S16 SbLiHitDiscReq(pst, spId, choice, conId, action, tPar)
Pst *pst;
SpId spId;
U8 choice;
UConnId conId;
Action action;
CmTptParam *tPar;
#endif
{
   TRC3(SbLiHitDiscReq)
   /* sb043.102: the debug mask is for lower interface */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
     "SbLiHitDiscReq(pst, spId(%d), choice(%d), conId(%d), action(%d), tPar)\n",
      spId, choice, conId, action));
#else
   SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
     "SbLiHitDiscReq(pst, spId(%d), choice(%d), conId(%ld), action(%d), tPar)\n",
      spId, choice, conId, action));
#endif /* BIT_64 */

   /* jump to specific primitive depending on configured selector */
   (*SbLiHitDiscReqMt[pst->selector])(pst, spId, choice, conId, action, tPar);

   RETVALUE(ROK);
}


/*
*     lower interface portable functions
*/

#ifdef PTSBLIHIT


/*
*
*       Fun:   Portable
*
*       Desc:
*
*       Ret:   ROK     - ok
*              RFAILED - not ok
*
*       Notes: None
*
*       File:  sb_ptli.c
*
*/
#ifdef ANSI
PUBLIC S16 PtLiHitBndReq
(
Pst *pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 PtLiHitBndReq(pst, suId, spId)
Pst *pst;
SuId suId;
SpId spId;
#endif
{
   TRC3(PtLiHitBndReq);
#if (ERRCLASS & ERRCLS_DEBUG)
   SBLOGERROR(ERRCLS_DEBUG, ESB362, (ErrVal)ERRZERO, "PtLiHitBndReq");
#endif /* ERRCLASS */

   UNUSED( pst );
   UNUSED( suId );
   UNUSED( spId );

   RETVALUE(ROK);
}



/*
*
*       Fun:   Portable
*
*       Desc:
*
*       Ret:   ROK     - ok
*              RFAILED - not ok
*
*       Notes: None
*
*       File:  sb_ptli.c
*
*/
#ifdef ANSI
PUBLIC S16 PtLiHitServOpenReq
(
Pst *pst,
SpId spId,
UConnId servConId,
CmTptAddr *servTAddr,
CmTptParam *tPar,
CmIcmpFilter *icmpFilter,
U8 srvcType
)
#else
PUBLIC S16 PtLiHitServOpenReq(pst, spId, servConId, servTAddr, tPar,
                              icmpFilter, srvcType)
Pst *pst;
SpId spId;
UConnId servConId;
CmTptAddr *servTAddr;
CmTptParam *tPar;
CmIcmpFilter *icmpFilter;
U8 srvcType;
#endif
{
   TRC3(PtLiHitServOpenReq);
#if (ERRCLASS & ERRCLS_DEBUG)
   SBLOGERROR(ERRCLS_DEBUG, ESB363, (ErrVal)ERRZERO, "PtLiHitServOpenReq");
#endif /* ERRCLASS */

   UNUSED( pst );
   UNUSED( spId );
   UNUSED( servConId );
   UNUSED( servTAddr );
   UNUSED( tPar );
   UNUSED( icmpFilter );
   UNUSED( srvcType );

   RETVALUE(ROK);
}



/*
*
*       Fun:   Portable
*
*       Desc:
*
*       Ret:   ROK     - ok
*              RFAILED - not ok
*
*       Notes: None
*
*       File:  sb_ptli.c
*
*/
/* sb050.102 - Add tPar for HI_REL_1_4 */
#ifdef HI_REL_1_4
#ifdef ANSI
PUBLIC S16 PtLiHitUDatReq
(
Pst                 *pst,
SpId                 spId,
UConnId              spConId,
CmTptAddr           *remAddr,
CmTptAddr           *srcAddr,
CmIpHdrParm         *hdrParm,
CmTptParam          *tPar,
Buffer              *mBuf
)
#else
PUBLIC S16 PtLiHitUDatReq(pst, spId, spConId, remAddr, srcAddr, hdrParm, tPar, mBuf)
Pst                 *pst;
SpId                 spId;
UConnId              spConId;
CmTptAddr           *remAddr;
CmTptAddr           *srcAddr;
CmIpHdrParm         *hdrParm;
CmTptParam          *tPar;
Buffer              *mBuf;
#endif /* ANSI */
#else
#ifdef ANSI
PUBLIC S16 PtLiHitUDatReq
(
Pst                 *pst,
SpId                 spId,
UConnId              spConId,
CmTptAddr           *remAddr,
CmTptAddr           *srcAddr,
CmIpHdrParm         *hdrParm,
Buffer              *mBuf
)
#else
PUBLIC S16 PtLiHitUDatReq(pst, spId, spConId, remAddr, srcAddr, hdrParm, mBuf)
Pst                 *pst;
SpId                 spId;
UConnId              spConId;
CmTptAddr           *remAddr;
CmTptAddr           *srcAddr;
CmIpHdrParm         *hdrParm;
Buffer              *mBuf;
#endif /* ANSI */
#endif /* HI_REL_1_4 */
{
   TRC3(PtLiHitUDatReq)
#if (ERRCLASS & ERRCLS_DEBUG)
   SBLOGERROR(ERRCLS_DEBUG, ESB364, (ErrVal)ERRZERO, "PtLiHitUDatReq");
#endif /* ERRCLASS */

   UNUSED( pst );
   UNUSED( remAddr );
   UNUSED( spId );
   UNUSED( spConId );
   UNUSED( srcAddr );
   UNUSED( hdrParm );
/* sb050.102 - Add tPar for HI_REL_1_4 */
#ifdef HI_REL_1_4
   UNUSED( tPar );
#endif /* HI_REL_1_4 */
   UNUSED( mBuf );

   RETVALUE(ROK);
}



/*
*
*       Fun:   Portable
*
*       Desc:
*
*       Ret:   ROK     - ok
*              RFAILED - not ok
*
*       Notes: None
*
*       File:  sb_ptli.c
*
*/
#ifdef ANSI
PUBLIC S16 PtLiHitDiscReq
(
Pst *pst,
SpId spId,
U8 choice,
UConnId conId,
Action action,
CmTptParam *tPar
)
#else
PUBLIC S16 PtLiHitDiscReq(pst, spId, choice, conId, action, tPar)
Pst *pst;
SpId spId;
U8 choice;
UConnId conId;
Action action;
CmTptParam *tPar;
#endif
{
   TRC3(PtLiHitDiscReq)
#if (ERRCLASS & ERRCLS_DEBUG)
   SBLOGERROR(ERRCLS_DEBUG, ESB365, (ErrVal)ERRZERO, "PtLiHitDiscReq");
#endif /* ERRCLASS */

   UNUSED( pst );
   UNUSED( choice );
   UNUSED( spId );
   UNUSED( conId );
   UNUSED( action );
   UNUSED( tPar );

   RETVALUE(ROK);
}

#endif /* PTSBLIHIT */




/********************************************************************30**

         End of file:     sb_ptli.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:17 2015

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

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
 /main/2     ---   wvdl   1. initial release.
 /main/2     ---   sb     1. Modified for SCTP release based on 
                                RFC-2960 'Oct 2000.
        sb012.102  rs     1. Backward compatible for TUCL1.4.  
        sb042.102  hl     1. Added change for SHT interface and Rolling
                             UpGrade
        sb043.102  hl     1. the debug mask is for lower interface
        sb050.102  sg     1. Added tPar for HI_REL_1_4 in PtLiHitUDatReq()
/main/3      ---  rsr/ag  1. Updated for Release of 1.3
/main/3 sb028.103 ajainx  1. Fix for compilation warnings.
/main/3 sb030.103 krkx    1. Fixed the warnings during 64-BIT compilation.
*********************************************************************91*/

