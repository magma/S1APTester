

/********************************************************************20**

     Name:     TCP/UDP Convergence Layer

     Type:     C source file

     Desc:     Upper interface.

     File:     hi_ptui.c

     Sid:      hi_ptui.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Tue Aug 11 10:26:30 2015

     Prg:      asa

*********************************************************************21*/


/*

The following functions are provided in this file:

     HiUiHitConInd      Connect Indication
     HiUiHitConCfm      Connect Confirm
     HiUiHitBndCfm      Bind Confirm
     HiUiHitDatInd      Data Indication
     HiUiHitUDatInd     Unit Data Indication
     HiUiHitDiscInd     Disconnect Indication
     HiUiHitDiscCfm     Disconnect Confirm
     HiUiHitFlcInd      Flow Control Indication
     HiUiHitTlsEstCfm   Tls Establishment Indication

It should be noted that not all of these functions may be required
by a particular network layer service user.

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

#ifdef H323_PERF
#include "hc_prf.h"             /* performance measurement */
#endif


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

#ifdef H323_PERF
#include "hc_prf.x"             /* performance measurement */
#endif



/* local defines */
/* hi009.105 : Added FP as another user */
/* hi012.105 : Added AQ as another user */
/* hi007.201 : Added SZ as another user */
/* hi020.201 : Added CZ as another user(KSCTP) */
/* hi021.201 : Added HM as another user(KSCTP) */
#define MAXHIUI 16

/* Always define PTHIUIHIT because HR and SB dont have the
*  corresponding ConInd, DatInd and FlcInd primitives at their
*  lower interface. Hence PTHIUIHIT is needed if they are
*  defined and if they are not defined, i.e., always.
*/
#define PTHIUIHIT
/* hi025.201 define the macro PTHIUISCT */
#ifdef HI_LKSCTP
#define PTHIUISCT
#endif /* HI_LKSCTP */



/* hi019.201: Added this to remove C++ warnings */
#ifdef __cplusplus
extern "C" {
#endif


#ifdef PTHIUIHIT


/* declaration of portable functions */

PRIVATE S16 PtUiHitConInd  ARGS((Pst *pst, SuId suId, UConnId servconId,
                                 UConnId spConId, CmTptAddr *peerAddr));
PRIVATE S16 PtUiHitConCfm  ARGS((Pst *pst, SuId suId, UConnId suConId,
                                 UConnId spConId, CmTptAddr *localAddr));
PRIVATE S16 PtUiHitBndCfm  ARGS((Pst *pst, SuId suId, U8 status));

#ifdef LOCAL_INTF
PRIVATE S16 PtUiHitUDatInd ARGS((Pst *pst, SuId suId, UConnId suConId,
                                 CmTptAddr *srcAddr, CmTptAddr *remAddr,
                                 CmIpHdrParm *ipHdrParm,
                                 CmTptLocalInf *localIf, Buffer *mBuf));
#else
PRIVATE S16 PtUiHitUDatInd ARGS((Pst *pst, SuId suId, UConnId suConId,
                                 CmTptAddr *srcAddr, CmTptAddr *remAddr,
                                 CmIpHdrParm *ipHdrParm,
                                 Buffer *mBuf));
#endif /* LOCAL_INTF */

PRIVATE S16 PtUiHitDatInd  ARGS((Pst *pst, SuId suId, UConnId suConId,
                                 Buffer *mBuf));
PRIVATE S16 PtUiHitDiscInd ARGS((Pst *pst, SuId suId, U8 choice,
                                 UConnId conId, Reason reason));
PRIVATE S16 PtUiHitDiscCfm ARGS((Pst *pst, SuId suId, U8 choice,
                                 UConnId conId, Action action));
PRIVATE S16 PtUiHitFlcInd  ARGS((Pst *pst, SuId suId,
                                 UConnId suConId, Reason reason));

/* hi013.105 :  Added two new HIT primitives. HiUiHitTlsEstReq(), HiUiHitTlsEstCfm().*/
#ifdef HITV2
#ifdef HI_TLS
#ifdef HI_TCP_TLS
PRIVATE S16 PtUiHitTlsEstCfm ARGS((Pst *pst, SuId suId, UConnId suConId,
                                 U8 status, Reason reason));
#endif /* HI_TCP_TLS */
#endif /* HI_TLS */
#endif /* HITV2 */

#endif /* PTHIUIHIT */

#ifdef HI_LKSCTP

#ifdef PTHIUISCT

/* declaration of portable functions */
PRIVATE S16 PtUiSctBndCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SctResult      result));

PRIVATE S16 PtUiSctEndpOpenCfm       ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          UConnId        spEndpId,
                                          SctResult      result,
                                          SctCause       cause));

PRIVATE S16 PtUiSctEndpCloseCfm      ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          SctResult      result,
                                          SctCause       cause));


PRIVATE S16 PtUiSctAssocInd          ARGS((Pst               *pst,
                                           SuId               suId,
                                           UConnId            suEndpId,
                                           SctAssocIndParams *assocParams,
                                           Buffer            *vsInfo));

/* sb016.102 - Include in-stream parameter here */
#ifdef SCT2
PRIVATE S16 PtUiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      inStrms,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo ));
#else /* SCT2 */
PRIVATE S16 PtUiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo ));
#endif /* SCT2 */

PRIVATE S16 PtUiSctTermInd           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          SctStatus      status,
                                          SctCause       cause,
                                          SctRtrvInfo   *rtrvInfo));

PRIVATE S16 PtUiSctTermCfm           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

PRIVATE S16 PtUiSctSetPriCfm         ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

PRIVATE S16 PtUiSctHBeatCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctResult      result,
                                          SctCause       cause));

PRIVATE S16 PtUiSctDatInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctStrmId      strmId,
                                          SctDatIndType *indType,
                                          U32            protId,
                                          Buffer        *mBuf));

PRIVATE S16 PtUiSctStaCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctResult      result,
                                          SctCause       cause,
                                          SctStaInfo    *staInfo));

/* hi019.201: Included protId parameter in status indication */
#ifdef SCT7
PRIVATE S16 PtUiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          U32            protId,
                                          Buffer        *mBuf));
#else
PRIVATE S16 PtUiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          Buffer        *mBuf));
#endif

PRIVATE S16 PtUiSctFlcInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          Reason         reason));

#endif /* PTHIUISCT */


/*
  The following matrices define the mapping between the primitives
  called by the upper interface of SCTP Layer
  and the corresponding primitives of the SCTP Layer
  service user(s).

  The parameter MAXHIUI defines the maximum number of service users on
  top of SCTP Layer. There is an array of functions
  per primitive invoked by SCTP Layer. Every array is
  MAXHIUI long(i.e.there are as many functions as the number of service
  users).

  The dispatching is performed by the configurable variable: selector.
  The selector is configured on a per SAP basis.

  The selectors are:

  0 - loosely coupled (#define LCHIUISCT)
  1 - M3UA            (#define IT)
  2 - IUA             (#define ID)
  3 - SUA             (#define SU)
  4 - M2UA            (#define MW)
  sb048.102: Changes to incorporate GCP
  5 - GCP             (#define MG)
  6 - Dummy Layer     (#define DM)
  sb052.102: NBAP (ENTIB) added as new SCTP user. 
  7 - NBAP            (#define IB)
  8 - M1UA            (#define MZ)
  9 - SIP             (#define SO)

*/



PRIVATE SctBndCfm HiUiSctBndCfmMt[MAXHIUI] =
{
#ifdef LCHIUISCT
   cmPkSctBndCfm,         /* 0 - loosely coupled */
#else
   PtUiSctBndCfm,         /* 0 - tightly coupled, portable */
#endif
#ifdef IT
   ItLiSctBndCfm,         /* 1 - tightly coupled, M3UA */
#else
   PtUiSctBndCfm,         /* 1 - tightly coupled, portable */
#endif
#ifdef ID
   IdLiSctBndCfm,         /* 2 - tightly coupled, IUA */
#else
   PtUiSctBndCfm,         /* 2 - tightly coupled, portable */
#endif
#ifdef SU
   SuLiSctBndCfm,         /* 3 - tightly coupled, SUA */
#else
   PtUiSctBndCfm,         /* 3 - tightly coupled, portable */
#endif
#ifdef MW
   MwLiSctBndCfm,         /* 4 - tightly coupled, M2UA */
#else
   PtUiSctBndCfm,         /* 4 - tightly coupled, portable */
#endif
/* sb048.102: Changes to incorporate GCP */
#ifdef MG
   MgLiSctBndCfm,         /* 5 - tightly coupled, GCP */
#else
   PtUiSctBndCfm,         /* 5 - tightly coupled, portable */
#endif
#ifdef DM
   DmLiSctBndCfm,         /* 6 - tightly coupled, DM */
#else
   PtUiSctBndCfm,         /* 6 - tightly coupled, portable */
#endif
/* sb052.102: NBAP (ENTIB), M1UA (ENTMZ) added as new SCTP user. */
#ifdef IB
   IbLiSctBndCfm,         /* 7 - tightly coupled, GCP */
#else
   PtUiSctBndCfm,         /* 7 - tightly coupled, portable */
#endif
#ifdef MZ
   MzLiSctBndCfm,         /* 8 - tightly coupled, GCP */
#else
   PtUiSctBndCfm,         /* 8 - tightly coupled, portable */
#endif
/* sb065.102: SIP added as new SCTP user */
#ifdef SO
   SoLiSctBndCfm,         /* 8 - tightly coupled, SIP */
#else
   PtUiSctBndCfm,         /* 8 - tightly coupled, portable */
#endif

/*sb079.102 : Diameter added as new SCTP user*/
#ifdef AQ
   AqLiSctBndCfm,         /* 10 - tightly coupled, Diameter */
#else
   PtUiSctBndCfm,         /* 10 - tightly coupled, portable */
#endif

/*hi007.201 : S1AP added as new SCTP user*/
#ifdef SZ
   SzLiSctBndCfm,         /* 11 - tightly coupled, S1AP */
#else
   PtUiSctBndCfm,         /* 11 - tightly coupled, portable */
#endif
/* hi020.201 : Added CZ as another user(KSCTP) */
#ifdef CZ
   CzLiSctBndCfm,         /* 12 - tightly coupled, X2AP */
#else
   PtUiSctBndCfm,         /* 12 - tightly coupled, portable */
#endif
/* hi021.201 : Added HM as another user(KSCTP) */
#ifdef HM
   HmLiSctBndCfm,         /* 13 - tightly coupled, Iuh */
#else
   PtUiSctBndCfm,         /* 13 - tightly coupled, portable */
#endif /* HM */

};


PRIVATE SctEndpOpenCfm HiUiSctEndpOpenCfmMt[MAXHIUI] =
{
#ifdef LCHIUISCT
   cmPkSctEndpOpenCfm,         /* 0 - loosely coupled */
#else
   PtUiSctEndpOpenCfm,         /* 0 - tightly coupled, portable */
#endif
#ifdef IT
   ItLiSctEndpOpenCfm,         /* 1 - tightly coupled, M3UA */
#else
   PtUiSctEndpOpenCfm,         /* 1 - tightly coupled, portable */
#endif
#ifdef ID
   IdLiSctEndpOpenCfm,         /* 2 - tightly coupled, IUA */
#else
   PtUiSctEndpOpenCfm,         /* 2 - tightly coupled, portable */
#endif
#ifdef SU
   SuLiSctEndpOpenCfm,         /* 3 - tightly coupled, SUA */
#else
   PtUiSctEndpOpenCfm,         /* 3 - tightly coupled, portable */
#endif
#ifdef MW
   MwLiSctEndpOpenCfm,         /* 4 - tightly coupled, M2UA */
#else
   PtUiSctEndpOpenCfm,         /* 4 - tightly coupled, portable */
#endif
/* sb048.102: Changes to incorporate GCP */
#ifdef MG
   MgLiSctEndpOpenCfm,         /* 5 - tightly coupled, GCP */
#else
   PtUiSctEndpOpenCfm,         /* 5 - tightly coupled, portable */
#endif
#ifdef DM
   DmLiSctEndpOpenCfm,         /* 6 - tightly coupled, DM */
#else
   PtUiSctEndpOpenCfm,         /* 6 - tightly coupled, portable */
#endif
/* sb052.102: NBAP (ENTIB), M1UA (ENTMZ) added as new SCTP user. */
#ifdef IB 
   IbLiSctEndpOpenCfm,         /* 7 - tightly coupled, GCP */
#else
   PtUiSctEndpOpenCfm,         /* 7 - tightly coupled, portable */
#endif
#ifdef MZ 
   MzLiSctEndpOpenCfm,         /* 8 - tightly coupled, GCP */
#else
   PtUiSctEndpOpenCfm,         /* 8 - tightly coupled, portable */
#endif
/* sb065.102: SIP added as new SCTP user */
#ifdef SO 
   SoLiSctEndpOpenCfm,         /* 8 - tightly coupled, SIP */
#else
   PtUiSctEndpOpenCfm,         /* 8 - tightly coupled, portable */
#endif
/*sb079.102: Diameter added as new SCTP user*/
#ifdef AQ
   AqLiSctEndpOpenCfm,         /* 10 - tightly coupled, Diameter */
#else
   PtUiSctEndpOpenCfm,         /* 10 - tightly coupled, portable */
#endif

/*hi007.201: S1AP added as new SCTP user*/
#ifdef SZ
   SzLiSctEndpOpenCfm,         /* 11 - tightly coupled, S1AP */
#else
   PtUiSctEndpOpenCfm,         /* 11 - tightly coupled, portable */
#endif
/* hi020.201 : Added CZ as another user(KSCTP) */
#ifdef CZ
   CzLiSctEndpOpenCfm,         /* 12 - tightly coupled, X2AP */
#else
   PtUiSctEndpOpenCfm,         /* 12 - tightly coupled, portable */
#endif
/* hi021.201 : Added HM as another user(KSCTP) */
#ifdef HM
   HmLiSctEndpOpenCfm,         /* 13 - tightly coupled, Iuh */
#else
   PtUiSctEndpOpenCfm,         /* 13 - tightly coupled, portable */
#endif /* HM */
};

PRIVATE SctEndpCloseCfm HiUiSctEndpCloseCfmMt[MAXHIUI] =
{
#ifdef LCHIUISCT
   cmPkSctEndpCloseCfm,         /* 0 - loosely coupled */
#else
   PtUiSctEndpCloseCfm,         /* 0 - tightly coupled, portable */
#endif
#ifdef IT
   ItLiSctEndpCloseCfm,         /* 1 - tightly coupled, M3UA */
#else
   PtUiSctEndpCloseCfm,         /* 1 - tightly coupled, portable */
#endif
#ifdef ID
   IdLiSctEndpCloseCfm,         /* 2 - tightly coupled, IUA */
#else
   PtUiSctEndpCloseCfm,         /* 2 - tightly coupled, portable */
#endif
#ifdef SU
   SuLiSctEndpCloseCfm,         /* 3 - tightly coupled, SUA */
#else
   PtUiSctEndpCloseCfm,         /* 3 - tightly coupled, portable */
#endif
#ifdef MW
   MwLiSctEndpCloseCfm,         /* 4 - tightly coupled, M2UA */
#else
   PtUiSctEndpCloseCfm,         /* 4 - tightly coupled, portable */
#endif
/* sb048.102: Changes to incorporate GCP */
#ifdef MG
   MgLiSctEndpCloseCfm,         /* 5 - tightly coupled, GCP */
#else
   PtUiSctEndpCloseCfm,         /* 5 - tightly coupled, portable */
#endif
#ifdef DM
   DmLiSctEndpCloseCfm,         /* 6 - tightly coupled, DM */
#else
   PtUiSctEndpCloseCfm,         /* 6 - tightly coupled, portable */
#endif
/* sb052.102: NBAP (ENTIB), M1UA (ENTMZ) added as new SCTP user. */
#ifdef IB 
   IbLiSctEndpCloseCfm,         /* 7 - tightly coupled, GCP */
#else
   PtUiSctEndpCloseCfm,         /* 7 - tightly coupled, portable */
#endif
#ifdef MZ 
   MzLiSctEndpCloseCfm,         /* 8 - tightly coupled, GCP */
#else
   PtUiSctEndpCloseCfm,         /* 8 - tightly coupled, portable */
#endif
/* sb065.102: SIP added as new SCTP user */
#ifdef SO 
   SoLiSctEndpCloseCfm,         /* 8 - tightly coupled, SIP */
#else
   PtUiSctEndpCloseCfm,         /* 8 - tightly coupled, portable */
#endif
/*sb079.102: Diameter added as new SCTP  user*/
#ifdef AQ
   AqLiSctEndpCloseCfm,         /* 10 - tightly coupled, Diameter */
#else
   PtUiSctEndpCloseCfm,         /* 10 - tightly coupled, portable */
#endif

/*hi007.201: S1AP added as new SCTP  user*/
#ifdef SZ
   SzLiSctEndpCloseCfm,         /* 11 - tightly coupled, S1AP */
#else
   PtUiSctEndpCloseCfm,         /* 11 - tightly coupled, portable */
#endif
/* hi020.201 : Added CZ as another user(KSCTP) */
#ifdef CZ
   CzLiSctEndpCloseCfm,         /* 12 - tightly coupled, X2AP */
#else
   PtUiSctEndpCloseCfm,         /* 12 - tightly coupled, portable */
#endif
/* hi021.201 : Added HM as another user(KSCTP) */
#ifdef HM
   HmLiSctEndpCloseCfm,         /* 13 - tightly coupled, Iuh */
#else
   PtUiSctEndpCloseCfm,         /* 13 - tightly coupled, portable */
#endif /* HM */
};

PRIVATE SctAssocInd HiUiSctAssocIndMt[MAXHIUI] =
{
#ifdef LCHIUISCT
   cmPkSctAssocInd,         /* 0 - loosely coupled */
#else
   PtUiSctAssocInd,         /* 0 - tightly coupled, portable */
#endif
#ifdef IT
   ItLiSctAssocInd,         /* 1 - tightly coupled, M3UA */
#else
   PtUiSctAssocInd,         /* 1 - tightly coupled, portable */
#endif
#ifdef ID
   IdLiSctAssocInd,         /* 2 - tightly coupled, IUA */
#else
   PtUiSctAssocInd,         /* 2 - tightly coupled, portable */
#endif
#ifdef SU
   SuLiSctAssocInd,         /* 3 - tightly coupled, SUA */
#else
   PtUiSctAssocInd,         /* 3 - tightly coupled, portable */
#endif
#ifdef MW
   MwLiSctAssocInd,         /* 4 - tightly coupled, M2UA */
#else
   PtUiSctAssocInd,         /* 4 - tightly coupled, portable */
#endif
/* sb048.102: Changes to incorporate GCP */
#ifdef MG
   MgLiSctAssocInd,         /* 5 - tightly coupled, GCP */
#else
   PtUiSctAssocInd,         /* 5 - tightly coupled, portable */
#endif
#ifdef DM
   DmLiSctAssocInd,         /* 6 - tightly coupled, DM */
#else
   PtUiSctAssocInd,         /* 6 - tightly coupled, portable */
#endif
/* sb052.102: NBAP (ENTIB), M1UA (ENTMZ) added as new SCTP user. */
#ifdef IB
   IbLiSctAssocInd,         /* 7 - tightly coupled, GCP */
#else
   PtUiSctAssocInd,         /* 7 - tightly coupled, portable */
#endif
#ifdef MZ
   MzLiSctAssocInd,         /* 8 - tightly coupled, GCP */
#else
   PtUiSctAssocInd,         /* 8 - tightly coupled, portable */
#endif
/* sb065.102: SIP added as new SCTP user */
#ifdef SO
   SoLiSctAssocInd,         /* 8 - tightly coupled, SIP */
#else
   PtUiSctAssocInd,         /* 8 - tightly coupled, portable */
#endif
/*sb079.102: Diameter as new SCTP user*/
#ifdef AQ
   AqLiSctAssocInd,         /* 10 - tightly coupled, Diameter */
#else
   PtUiSctAssocInd,         /* 10 - tightly coupled, portable */
#endif

/*hi007.201: S1AP as new SCTP user*/
#ifdef SZ
   SzLiSctAssocInd,         /* 11 - tightly coupled, S1AP */
#else
   PtUiSctAssocInd,         /* 11 - tightly coupled, portable */
#endif
/* hi020.201 : Added CZ as another user(KSCTP) */
#ifdef CZ
   CzLiSctAssocInd,         /* 12 - tightly coupled, X2AP */
#else
   PtUiSctAssocInd,         /* 12 - tightly coupled, portable */
#endif
/* hi021.201 : Added HM as another user(KSCTP) */
#ifdef HM
   HmLiSctAssocInd,         /* 13 - tightly coupled, Iuh */
#else
   PtUiSctAssocInd,         /* 13 - tightly coupled, portable */
#endif /* HM */
};

PRIVATE SctAssocCfm HiUiSctAssocCfmMt[MAXHIUI] =
{
#ifdef LCHIUISCT
   cmPkSctAssocCfm,         /* 0 - loosely coupled */
#else
   PtUiSctAssocCfm,         /* 0 - tightly coupled, portable */
#endif
#ifdef IT
   ItLiSctAssocCfm,         /* 1 - tightly coupled, M3UA */
#else
   PtUiSctAssocCfm,         /* 1 - tightly coupled, portable */
#endif
#ifdef ID
   IdLiSctAssocCfm,         /* 2 - tightly coupled, IUA */
#else
   PtUiSctAssocCfm,         /* 2 - tightly coupled, portable */
#endif
#ifdef SU
   SuLiSctAssocCfm,         /* 3 - tightly coupled, SUA */
#else
   PtUiSctAssocCfm,         /* 3 - tightly coupled, portable */
#endif
#ifdef MW
   MwLiSctAssocCfm,         /* 4 - tightly coupled, M2UA */
#else
   PtUiSctAssocCfm,         /* 4 - tightly coupled, portable */
#endif
/* sb048.102: Changes to incorporate GCP */
#ifdef MG
   MgLiSctAssocCfm,         /* 5 - tightly coupled, GCP */
#else
   PtUiSctAssocCfm,         /* 5 - tightly coupled, portable */
#endif
#ifdef DM
   DmLiSctAssocCfm,         /* 6 - tightly coupled, DM */
#else
   PtUiSctAssocCfm,         /* 6 - tightly coupled, portable */
#endif
/* sb052.102: NBAP (ENTIB), M1UA (ENTMZ) added as new SCTP user. */
#ifdef IB
   IbLiSctAssocCfm,         /* 7 - tightly coupled, GCP */
#else
   PtUiSctAssocCfm,         /* 7 - tightly coupled, portable */
#endif
#ifdef MZ
   MzLiSctAssocCfm,         /* 8 - tightly coupled, GCP */
#else
   PtUiSctAssocCfm,         /* 8 - tightly coupled, portable */
#endif
/* sb065.102: SIP added as new SCTP user */
#ifdef SO
   SoLiSctAssocCfm,         /* 8 - tightly coupled, SIP */
#else
   PtUiSctAssocCfm,         /* 8 - tightly coupled, portable */
#endif
/*sb079.102: Diameter as new SCTP user*/
#ifdef AQ
   AqLiSctAssocCfm,         /* 10 - tightly coupled, Diameter */
#else
   PtUiSctAssocCfm,         /* 10 - tightly coupled, portable */
#endif

/*hi007.201: S1AP as new SCTP user*/
#ifdef SZ
   SzLiSctAssocCfm,         /* 11 - tightly coupled, S1AP */
#else
   PtUiSctAssocCfm,         /* 11 - tightly coupled, portable */
#endif
/* hi020.201 : Added CZ as another user(KSCTP) */
#ifdef CZ
   CzLiSctAssocCfm,         /* 12 - tightly coupled, X2AP */
#else
   PtUiSctAssocCfm,         /* 12 - tightly coupled, portable */
#endif
/* hi021.201 : Added HM as another user(KSCTP) */
#ifdef HM
   HmLiSctAssocCfm,         /* 13 - tightly coupled, Iuh */
#else
   PtUiSctAssocCfm,         /* 13 - tightly coupled, portable */
#endif /* HM */
};

PRIVATE SctTermInd HiUiSctTermIndMt[MAXHIUI] =
{
#ifdef LCHIUISCT
   cmPkSctTermInd,         /* 0 - loosely coupled */
#else
   PtUiSctTermInd,         /* 0 - tightly coupled, portable */
#endif
#ifdef IT
   ItLiSctTermInd,         /* 1 - tightly coupled, M3UA */
#else
   PtUiSctTermInd,         /* 1 - tightly coupled, portable */
#endif
#ifdef ID
   IdLiSctTermInd,         /* 2 - tightly coupled, IUA */
#else
   PtUiSctTermInd,         /* 2 - tightly coupled, portable */
#endif
#ifdef SU
   SuLiSctTermInd,         /* 3 - tightly coupled, SUA */
#else
   PtUiSctTermInd,         /* 3 - tightly coupled, portable */
#endif
#ifdef MW
   MwLiSctTermInd,         /* 4 - tightly coupled, M2UA */
#else
   PtUiSctTermInd,         /* 4 - tightly coupled, portable */
#endif
/* sb048.102: Changes to incorporate GCP */
#ifdef MG
   MgLiSctTermInd,         /* 5 - tightly coupled, GCP */
#else
   PtUiSctTermInd,         /* 5 - tightly coupled, portable */
#endif
#ifdef DM
   DmLiSctTermInd,         /* 6 - tightly coupled, DM */
#else
   PtUiSctTermInd,         /* 6 - tightly coupled, portable */
#endif
/* sb052.102: NBAP (ENTIB), M1UA (ENTMZ) added as new SCTP user. */
#ifdef IB
   IbLiSctTermInd,         /* 7 - tightly coupled, GCP */
#else
   PtUiSctTermInd,         /* 7 - tightly coupled, portable */
#endif
#ifdef MZ
   MzLiSctTermInd,         /* 8 - tightly coupled, GCP */
#else
   PtUiSctTermInd,         /* 8 - tightly coupled, portable */
#endif
/* sb065.102: SIP added as new SCTP user */
#ifdef SO
   SoLiSctTermInd,         /* 8 - tightly coupled, SIP */
#else
   PtUiSctTermInd,         /* 8 - tightly coupled, portable */
#endif
/*sb079.102: Diameter added as new SCTP user*/
#ifdef AQ
   AqLiSctTermInd,         /* 10 - tightly coupled, Diameter */
#else
   PtUiSctTermInd,         /* 10 - tightly coupled, portable */
#endif

/*hi007.201: S1AP added as new SCTP user*/
#ifdef SZ
   SzLiSctTermInd,         /* 11 - tightly coupled, S1AP */
#else
   PtUiSctTermInd,         /* 11 - tightly coupled, portable */
#endif
/* hi020.201 : Added CZ as another user(KSCTP) */
#ifdef CZ
   CzLiSctTermInd,         /* 12 - tightly coupled, X2AP */
#else
   PtUiSctTermInd,         /* 12 - tightly coupled, portable */
#endif
/* hi021.201 : Added HM as another user(KSCTP) */
#ifdef HM
   HmLiSctTermInd,         /* 13 - tightly coupled, Iuh */
#else
   PtUiSctTermInd,         /* 13 - tightly coupled, portable */
#endif /* HM */
};

PRIVATE SctTermCfm HiUiSctTermCfmMt[MAXHIUI] =
{
#ifdef LCHIUISCT
   cmPkSctTermCfm,         /* 0 - loosely coupled */
#else
   PtUiSctTermCfm,         /* 0 - tightly coupled, portable */
#endif
#ifdef IT
   ItLiSctTermCfm,         /* 1 - tightly coupled, M3UA */
#else
   PtUiSctTermCfm,         /* 1 - tightly coupled, portable */
#endif
#ifdef ID
   IdLiSctTermCfm,         /* 2 - tightly coupled, IUA */
#else
   PtUiSctTermCfm,         /* 2 - tightly coupled, portable */
#endif
#ifdef SU
   SuLiSctTermCfm,         /* 3 - tightly coupled, SUA */
#else
   PtUiSctTermCfm,         /* 3 - tightly coupled, portable */
#endif
#ifdef MW
   MwLiSctTermCfm,         /* 4 - tightly coupled, M2UA */
#else
   PtUiSctTermCfm,         /* 4 - tightly coupled, portable */
#endif
/* sb048.102: Changes to incorporate GCP */
#ifdef MG
   MgLiSctTermCfm,         /* 5 - tightly coupled, GCP */
#else
   PtUiSctTermCfm,         /* 5 - tightly coupled, portable */
#endif
#ifdef DM
   DmLiSctTermCfm,         /* 6 - tightly coupled, DM */
#else
   PtUiSctTermCfm,         /* 6 - tightly coupled, portable */
#endif
/* sb052.102: NBAP (ENTIB), M1UA (ENTMZ) added as new SCTP user. */
#ifdef IB
   IbLiSctTermCfm,         /* 7 - tightly coupled, GCP */
#else
   PtUiSctTermCfm,         /* 7 - tightly coupled, portable */
#endif
#ifdef MZ
   MzLiSctTermCfm,         /* 8 - tightly coupled, GCP */
#else
   PtUiSctTermCfm,         /* 8 - tightly coupled, portable */
#endif
/* sb065.102: SIP added as new SCTP user */
#ifdef SO
   SoLiSctTermCfm,         /* 8 - tightly coupled, SIP */
#else
   PtUiSctTermCfm,         /* 8 - tightly coupled, portable */
#endif
/*sb079.102: Diameter as new SCTP user*/
#ifdef AQ
   AqLiSctTermCfm,         /* 10 - tightly coupled, Diameter */
#else
   PtUiSctTermCfm,         /* 10 - tightly coupled, portable */
#endif

/*hi007.201: S1AP as new SCTP user*/
#ifdef SZ
   SzLiSctTermCfm,         /* 11 - tightly coupled, S1AP */
#else
   PtUiSctTermCfm,         /* 11 - tightly coupled, portable */
#endif
/* hi020.201 : Added CZ as another user(KSCTP) */
#ifdef CZ
   CzLiSctTermCfm,         /* 12 - tightly coupled, X2AP */
#else
   PtUiSctTermCfm,         /* 12 - tightly coupled, portable */
#endif
/* hi021.201 : Added HM as another user(KSCTP) */
#ifdef HM
   HmLiSctTermCfm,         /* 13 - tightly coupled, Iuh */
#else
   PtUiSctTermCfm,         /* 13 - tightly coupled, portable */
#endif /* HM */
};

PRIVATE SctSetPriCfm HiUiSctSetPriCfmMt[MAXHIUI] =
{
#ifdef LCHIUISCT
   cmPkSctSetPriCfm,         /* 0 - loosely coupled */
#else
   PtUiSctSetPriCfm,         /* 0 - tightly coupled, portable */
#endif
#ifdef IT
   ItLiSctSetPriCfm,         /* 1 - tightly coupled, M3UA */
#else
   PtUiSctSetPriCfm,         /* 1 - tightly coupled, portable */
#endif
#ifdef ID
   IdLiSctSetPriCfm,         /* 2 - tightly coupled, IUA */
#else
   PtUiSctSetPriCfm,         /* 2 - tightly coupled, portable */
#endif
#ifdef SU
   SuLiSctSetPriCfm,         /* 3 - tightly coupled, SUA */
#else
   PtUiSctSetPriCfm,         /* 3 - tightly coupled, portable */
#endif
#ifdef MW
   MwLiSctSetPriCfm,         /* 4 - tightly coupled, M2UA */
#else
   PtUiSctSetPriCfm,         /* 4 - tightly coupled, portable */
#endif
/* sb048.102: Changes to incorporate GCP */
#ifdef MG
   MgLiSctSetPriCfm,         /* 5 - tightly coupled, M2UA */
#else
   PtUiSctSetPriCfm,         /* 5 - tightly coupled, portable */
#endif
#ifdef DM
   DmLiSctSetPriCfm,         /* 6 - tightly coupled, DM */
#else
   PtUiSctSetPriCfm,         /* 6 - tightly coupled, portable */
#endif
/* sb052.102: NBAP (ENTIB), M1UA (ENTMZ) added as new SCTP user. */
#ifdef IB
   IbLiSctSetPriCfm,         /* 7 - tightly coupled, M2UA */
#else
   PtUiSctSetPriCfm,         /* 7 - tightly coupled, portable */
#endif
#ifdef MZ
   MzLiSctSetPriCfm,         /* 8 - tightly coupled, M2UA */
#else
   PtUiSctSetPriCfm,         /* 8 - tightly coupled, portable */
#endif
/* sb065.102: SIP added as new SCTP user */
#ifdef SO
   SoLiSctSetPriCfm,         /* 8 - tightly coupled, SIP */
#else
   PtUiSctSetPriCfm,         /* 8 - tightly coupled, portable */
#endif
/*sb079.102: Diameter added as new */
#ifdef AQ
   AqLiSctSetPriCfm,         /* 10 - tightly coupled, Diameter */
#else
   PtUiSctSetPriCfm,         /* 10 - tightly coupled, portable */
#endif

/*hi007.201: S1AP added as new */
#ifdef SZ_PHASE2
#ifdef SZ
   SzLiSctSetPriCfm,         /* 11 - tightly coupled, S1AP */
#else
   PtUiSctSetPriCfm,         /* 11 - tightly coupled, portable */
#endif /* SZ */
#endif /* SZ_PHASE2 */
/* hi020.201 : Added CZ as another user(KSCTP) */
#ifdef CZ
   CzLiSctSetPriCfm,         /* 12 - tightly coupled, X2AP */
#else
   PtUiSctSetPriCfm,         /* 12 - tightly coupled, portable */
#endif /* CZ */
/* hi021.201 : Added HM as another user(KSCTP) */
#ifdef HM
   HmLiSctSetPriCfm,         /* 13 - tightly coupled, Iuh */
#else
   PtUiSctSetPriCfm,         /* 13 - tightly coupled, portable */
#endif /* HM */
};

PRIVATE SctHBeatCfm HiUiSctHBeatCfmMt[MAXHIUI] =
{
#ifdef LCHIUISCT
   cmPkSctHBeatCfm,         /* 0 - loosely coupled */
#else
   PtUiSctHBeatCfm,         /* 0 - tightly coupled, portable */
#endif
#ifdef IT
   ItLiSctHBeatCfm,         /* 1 - tightly coupled, M3UA */
#else
   PtUiSctHBeatCfm,         /* 1 - tightly coupled, portable */
#endif
#ifdef ID
   IdLiSctHBeatCfm,         /* 2 - tightly coupled, IUA */
#else
   PtUiSctHBeatCfm,         /* 2 - tightly coupled, portable */
#endif
#ifdef SU
   SuLiSctHBeatCfm,         /* 3 - tightly coupled, SUA */
#else
   PtUiSctHBeatCfm,         /* 3 - tightly coupled, portable */
#endif
#ifdef MW
   MwLiSctHBeatCfm,         /* 4 - tightly coupled, M2UA */
#else
   PtUiSctHBeatCfm,         /* 4 - tightly coupled, portable */
#endif
/* sb048.102: Changes to incorporate GCP */
#ifdef MG
   MgLiSctHBeatCfm,         /* 5 - tightly coupled, GCP */
#else
   PtUiSctHBeatCfm,         /* 5 - tightly coupled, portable */
#endif
#ifdef DM
   DmLiSctHBeatCfm,         /* 6 - tightly coupled, DM */
#else
   PtUiSctHBeatCfm,         /* 6 - tightly coupled, portable */
#endif
/* sb052.102: NBAP (ENTIB), M1UA (ENTMZ) added as new SCTP user. */
#ifdef IB
   IbLiSctHBeatCfm,         /* 7 - tightly coupled, GCP */
#else
   PtUiSctHBeatCfm,         /* 7 - tightly coupled, portable */
#endif
#ifdef MZ
   MzLiSctHBeatCfm,         /* 8 - tightly coupled, GCP */
#else
   PtUiSctHBeatCfm,         /* 8 - tightly coupled, portable */
#endif
/* sb065.102: SIP added as new SCTP user */
#ifdef SO
   SoLiSctHBeatCfm,         /* 8 - tightly coupled, SIP */
#else
   PtUiSctHBeatCfm,         /* 8 - tightly coupled, portable */
#endif
/*sb079.102: Diameter as new SCTP user*/
#ifdef AQ
   AqLiSctHBeatCfm,         /* 10 - tightly coupled, Diameter */
#else
   PtUiSctHBeatCfm,         /* 10 - tightly coupled, portable */
#endif

/*hi007.201: S1AP as new SCTP user*/
#ifdef SZ_PHASE2
#ifdef SZ
   SzLiSctHBeatCfm,         /* 11 - tightly coupled, S1AP */
#else
   PtUiSctHBeatCfm,         /* 11 - tightly coupled, portable */
#endif /* SZ */
#endif /* SZ_PHASE2 */

/* hi020.201 : Added CZ as another user(KSCTP) */
#ifdef CZ
   CzLiSctHBeatCfm,         /* 12 - tightly coupled, X2AP */
#else
   PtUiSctHBeatCfm,         /* 12 - tightly coupled, portable */
#endif /* CZ */
};

PRIVATE SctDatInd HiUiSctDatIndMt[MAXHIUI] =
{
#ifdef LCHIUISCT
   cmPkSctDatInd,         /* 0 - loosely coupled */
#else
   PtUiSctDatInd,         /* 0 - tightly coupled, portable */
#endif
#ifdef IT
   ItLiSctDatInd,         /* 1 - tightly coupled, M3UA */
#else
   PtUiSctDatInd,         /* 1 - tightly coupled, portable */
#endif
#ifdef ID 
   IdLiSctDatInd,         /* 2 - tightly coupled, IUA */
#else
   PtUiSctDatInd,         /* 2 - tightly coupled, portable */
#endif
#ifdef SU
   SuLiSctDatInd,         /* 3 - tightly coupled, SUA */
#else
   PtUiSctDatInd,         /* 3 - tightly coupled, portable */
#endif
#ifdef MW
   MwLiSctDatInd,         /* 4 - tightly coupled, M2UA */
#else
   PtUiSctDatInd,         /* 4 - tightly coupled, portable */
#endif
/* sb048.102: Changes to incorporate GCP */
#ifdef MG
   MgLiSctDatInd,         /* 5 - tightly coupled, GCP */
#else
   PtUiSctDatInd,         /* 5 - tightly coupled, portable */
#endif
#ifdef DM
   DmLiSctDatInd,         /* 6 - tightly coupled, DM */
#else
   PtUiSctDatInd,         /* 6 - tightly coupled, portable */
#endif
/* sb052.102: NBAP (ENTIB), M1UA (ENTMZ) added as new SCTP user. */
#ifdef IB
   IbLiSctDatInd,         /* 7 - tightly coupled, GCP */
#else
   PtUiSctDatInd,         /* 7 - tightly coupled, portable */
#endif
#ifdef MZ
   MzLiSctDatInd,         /* 8 - tightly coupled, GCP */
#else
   PtUiSctDatInd,         /* 8 - tightly coupled, portable */
#endif
/* sb065.102: SIP added as new SCTP user */
#ifdef SO
   SoLiSctDatInd,         /* 8 - tightly coupled, SIP */
#else
   PtUiSctDatInd,         /* 8 - tightly coupled, portable */
#endif
/*sb079.102: Diameter as new SCTP user*/
#ifdef AQ
   AqLiSctDatInd,         /* 10 - tightly coupled, Diameter */
#else
   PtUiSctDatInd,         /* 10 - tightly coupled, portable */
#endif

/*hi007.201: S1AP as new SCTP user*/
#ifdef SZ
   SzLiSctDatInd,         /* 11 - tightly coupled, S1AP */
#else
   PtUiSctDatInd,         /* 11 - tightly coupled, portable */
#endif
/* hi020.201 : Added CZ as another user(KSCTP) */
#ifdef CZ
   CzLiSctDatInd,         /* 12 - tightly coupled, X2AP */
#else
   PtUiSctDatInd,         /* 12 - tightly coupled, portable */
#endif
/* hi021.201 : Added HM as another user(KSCTP) */
#ifdef HM
   HmLiSctDatInd,         /* 13 - tightly coupled, Iuh */
#else
   PtUiSctDatInd,         /* 13 - tightly coupled, portable */
#endif /* HM */
};

PRIVATE SctStaCfm HiUiSctStaCfmMt[MAXHIUI] =
{
#ifdef LCHIUISCT
   cmPkSctStaCfm,         /* 0 - loosely coupled */
#else
   PtUiSctStaCfm,         /* 0 - tightly coupled, portable */
#endif
#ifdef IT
   ItLiSctStaCfm,         /* 1 - tightly coupled, M3UA */
#else
   PtUiSctStaCfm,         /* 1 - tightly coupled, portable */
#endif
#ifdef ID
   IdLiSctStaCfm,         /* 2 - tightly coupled, IUA */
#else
   PtUiSctStaCfm,         /* 2 - tightly coupled, portable */
#endif
#ifdef SU
   SuLiSctStaCfm,         /* 3 - tightly coupled, SUA */
#else
   PtUiSctStaCfm,         /* 3 - tightly coupled, portable */
#endif
#ifdef MW
   MwLiSctStaCfm,         /* 4 - tightly coupled, M2UA */
#else
   PtUiSctStaCfm,         /* 4 - tightly coupled, portable */
#endif
/* sb048.102: Changes to incorporate GCP */
#ifdef MG
   MgLiSctStaCfm,         /* 5 - tightly coupled, GCP  */
#else
   PtUiSctStaCfm,         /* 5 - tightly coupled, portable */
#endif
#ifdef DM
   DmLiSctStaCfm,         /* 6 - tightly coupled, DM */
#else
   PtUiSctStaCfm,         /* 6 - tightly coupled, portable */
#endif
/* sb052.102: NBAP (ENTIB), M1UA (ENTMZ) added as new SCTP user. */
#ifdef IB
   IbLiSctStaCfm,         /* 7 - tightly coupled, GCP  */
#else
   PtUiSctStaCfm,         /* 7 - tightly coupled, portable */
#endif
#ifdef MZ
   MzLiSctStaCfm,         /* 8 - tightly coupled, GCP  */
#else
   PtUiSctStaCfm,         /* 8 - tightly coupled, portable */
#endif
/* sb065.102: SIP added as new SCTP user */
#ifdef SO
   SoLiSctStaCfm,         /* 8 - tightly coupled, SIP  */
#else
   PtUiSctStaCfm,         /* 8 - tightly coupled, portable */
#endif
/*sb079.102: Diameter as new SCTP user*/
#ifdef AQ
   AqLiSctStaCfm,         /* 10 - tightly coupled, Diameter */
#else
   PtUiSctStaCfm,         /* 10 - tightly coupled, portable */
#endif

/*hi007.201: S1AP as new SCTP user*/
#ifdef SZ
#ifdef SZ_PHASE2
   SzLiSctStaCfm,         /* 11 - tightly coupled, S1AP */
#else
   PtUiSctStaCfm,         /* 11 - tightly coupled, portable */
#endif
#endif
/* hi020.201 : Added CZ as another user(KSCTP) */
#ifdef CZ
   CzLiSctStaCfm,         /* 12 - tightly coupled, X2AP */
#else
   PtUiSctStaCfm,         /* 12 - tightly coupled, portable */
#endif
/* hi021.201 : Added HM as another user(KSCTP) */
#ifdef HM
   HmLiSctStaCfm,         /* 13 - tightly coupled, Iuh */
#else
   PtUiSctStaCfm,         /* 13 - tightly coupled, portable */
#endif /* HM */
};

PRIVATE SctStaInd HiUiSctStaIndMt[MAXHIUI] =
{
#ifdef LCHIUISCT
   cmPkSctStaInd,         /* 0 - loosely coupled */
#else
   PtUiSctStaInd,         /* 0 - tightly coupled, portable */
#endif
#ifdef IT
   ItLiSctStaInd,         /* 1 - tightly coupled, M3UA */
#else
   PtUiSctStaInd,         /* 1 - tightly coupled, portable */
#endif
#ifdef ID
   IdLiSctStaInd,         /* 2 - tightly coupled, IUA */
#else
   PtUiSctStaInd,         /* 2 - tightly coupled, portable */
#endif
#ifdef SU
   SuLiSctStaInd,         /* 3 - tightly coupled, SUA */
#else
   PtUiSctStaInd,         /* 3 - tightly coupled, portable */
#endif
#ifdef MW
   MwLiSctStaInd,         /* 4 - tightly coupled, M2UA */
#else
   PtUiSctStaInd,         /* 4 - tightly coupled, portable */
#endif
/* sb048.102: Changes to incorporate GCP */
#ifdef MG
   MgLiSctStaInd,         /* 5 - tightly coupled, GCP */
#else
   PtUiSctStaInd,         /* 5 - tightly coupled, portable */
#endif
#ifdef DM
   DmLiSctStaInd,         /* 6 - tightly coupled, DM */
#else
   PtUiSctStaInd,         /* 6 - tightly coupled, portable */
#endif
/* sb052.102: NBAP (ENTIB), M1UA (ENTMZ) added as new SCTP user. */
#ifdef IB
   IbLiSctStaInd,         /* 7 - tightly coupled, GCP */
#else
   PtUiSctStaInd,         /* 7 - tightly coupled, portable */
#endif
#ifdef MZ
   MzLiSctStaInd,         /* 8 - tightly coupled, GCP */
#else
   PtUiSctStaInd,         /* 8 - tightly coupled, portable */
#endif
/* sb065.102: SIP added as new SCTP user */
#ifdef SO
   SoLiSctStaInd,         /* 8 - tightly coupled, SIP */
#else
   PtUiSctStaInd,         /* 8 - tightly coupled, portable */
#endif
/*sb079.102: Diameter as new SCTP user*/
#ifdef AQ
   AqLiSctStaInd,         /* 10 - tightly coupled, Diameter */
#else
   PtUiSctStaInd,         /* 10 - tightly coupled, portable */
#endif

/*hi007.201: S1AP as new SCTP user*/
#ifdef SZ
   SzLiSctStaInd,         /* 11 - tightly coupled, S1AP */
#else
   PtUiSctStaInd,         /* 11 - tightly coupled, portable */
#endif
/* hi020.201 : Added CZ as another user(KSCTP) */
#ifdef CZ
   CzLiSctStaInd,         /* 12 - tightly coupled, X2AP */
#else
   PtUiSctStaInd,         /* 12 - tightly coupled, portable */
#endif
/* hi021.201 : Added HM as another user(KSCTP) */
#ifdef HM
   HmLiSctStaInd,         /* 13 - tightly coupled, Iuh */
#else
   PtUiSctStaInd,         /* 13 - tightly coupled, portable */
#endif /* HM */

};

PRIVATE SctFlcInd HiUiSctFlcIndMt[MAXHIUI] =
{
#ifdef LCHIUISCT
   cmPkSctFlcInd,         /* 0 - loosely coupled */
#else
   PtUiSctFlcInd,         /* 0 - tightly coupled, portable */
#endif
#ifdef IT
   ItLiSctFlcInd,         /* 1 - tightly coupled, M3UA */
#else
   PtUiSctFlcInd,         /* 1 - tightly coupled, portable */
#endif
#ifdef ID
   IdLiSctFlcInd,         /* 2 - tightly coupled, IUA */
#else
   PtUiSctFlcInd,         /* 2 - tightly coupled, portable */
#endif
#ifdef SU 
   SuLiSctFlcInd,         /* 3 - tightly coupled, SUA */
#else
   PtUiSctFlcInd,         /* 3 - tightly coupled, portable */
#endif
#ifdef MW
   MwLiSctFlcInd,         /* 4 - tightly coupled, M2UA */
#else
   PtUiSctFlcInd,         /* 4 - tightly coupled, portable */
#endif
/* sb048.102: Changes to incorporate GCP */
#ifdef MG
   MgLiSctFlcInd,         /* 5 - tightly coupled, GCP */
#else
   PtUiSctFlcInd,         /* 5 - tightly coupled, portable */
#endif
#ifdef DM
   DmLiSctFlcInd,         /* 6 - tightly coupled, DM */
#else
   PtUiSctFlcInd,         /* 6 - tightly coupled, portable */
#endif
/* sb052.102: NBAP (ENTIB), M1UA (ENTMZ) added as new SCTP user. */
#ifdef IB
   IbLiSctFlcInd,         /* 7 - tightly coupled, GCP */
#else
   PtUiSctFlcInd,         /* 7 - tightly coupled, portable */
#endif
#ifdef MZ
   MzLiSctFlcInd,         /* 8 - tightly coupled, GCP */
#else
   PtUiSctFlcInd,         /* 8 - tightly coupled, portable */
#endif
/* sb065.102: SIP added as new SCTP user */
#ifdef SO
   SoLiSctFlcInd,         /* 8 - tightly coupled, SIP */
#else
   PtUiSctFlcInd,         /* 8 - tightly coupled, portable */
#endif
/*sb079.102: Diameter added as new SCTP user*/
#ifdef AQ
   AqLiSctFlcInd,         /* 10 - tightly coupled, Diameter */
#else
   PtUiSctFlcInd,         /* 10 - tightly coupled, portable */
#endif

/*hi007.201: S1AP added as new SCTP user*/
#ifdef SZ_PHASE2
#ifdef SZ
   SzLiSctFlcInd,         /* 11 - tightly coupled, S1AP */
#else
   PtUiSctFlcInd,         /* 11 - tightly coupled, portable */
#endif /* SZ */
#endif /* SZ_PHASE2 */

/* hi020.201 : Added CZ as another user(KSCTP) */
#ifdef CZ
   CzLiSctFlcInd,         /* 12 - tightly coupled, X2AP */
#else
   PtUiSctFlcInd,         /* 12 - tightly coupled, portable */
#endif /* CZ */
/* hi021.201 : Added HM as another user(KSCTP) */
#ifdef HM
   HmLiSctFlcInd,         /* 13 - tightly coupled, Iuh */
#else
   PtUiSctFlcInd,         /* 13 - tightly coupled, portable */
#endif /* HM */
};
#endif 

/* hi021.201 : Moved this to fix compilation error when SCTP is enabled and Kernel SCTP is disabled. */
#ifdef __cplusplus
} /* end of EXTERN "C" */
#endif /* end of __cplusplus */


/*
  The following matrices define the mapping between the primitives
  called by the upper interface of TCP UDP Convergence Layer
  and the corresponding primitives of the TCP UDP Convergence Layer
  service user(s).

  The parameter MAXHIUI defines the maximum number of service users on
  top of TCP UDP Convergence Layer. There is an array of functions
  per primitive invoked by TCP UDP Convergence Layer. Every array is
  MAXHIUI long(i.e.there are as many functions as the number of service
  users).

  The dispatching is performed by the configurable variable: selector.
  The selector is configured on a per SAP basis.

  The selectors are:

  0 - loosely coupled (#define LCHIUIHIT)
  1 - H.323 Control   (#define HC)
  2 - RTP/RTCP        (#define HR)
  3 - GTP             (#define GT)
  4 - MGCP            (#define MG)
  5 - Annex G         (#define HG)
  6 - SCTP            (#define SB)
  7 - MPLS            (#define LN)
  8 - Dummy Layer     (#define DM)
  9 - SIP             (#define SO)
 10 - SIP User        (#define SV)
 11 - FP User         (#define FP)
 12 - Diameter        (#define AQ)
 13 - eGTP a          (#define EG)
*/


/* Connect Indication */

PRIVATE HitConInd HiUiHitConIndMt[MAXHIUI] =
{
#ifdef LCHIUIHIT
   cmPkHitConInd,         /* 0 - loosely coupled */
#else
   PtUiHitConInd,         /* 0 - loosely coupled, portable */
#endif
#ifdef HC
   HcLiHitConInd,         /* 1 - tightly coupled, H.323 Control */
#else
   PtUiHitConInd,         /* 1 - tightly coupled, portable */
#endif
#ifdef HR
   PtUiHitConInd,         /* 2 - tightly coupled, RTP/RTCP */
#else
   PtUiHitConInd,         /* 2 - tightly coupled, portable */
#endif
#ifdef GT
   GtLiHitConInd,         /* 3 - tightly coupled, GTP */
#else
   PtUiHitConInd,         /* 3 - tightly coupled, portable */
#endif
#ifdef MG
   MgLiHitConInd,         /* 4 - tightly coupled, MGCP */
#else
   PtUiHitConInd,         /* 4 - tightly coupled, portable */
#endif
#ifdef HG
   HgLiHitConInd,         /* 5 - tightly coupled, ANNEX G */
#else
   PtUiHitConInd,         /* 5 - tightly coupled, portable */
#endif
#ifdef SB
   PtUiHitConInd,         /* 6 - tightly coupled, SCTP */
#else
   PtUiHitConInd,         /* 6 - tightly coupled, portable */
#endif
#ifdef LN
   LnLiHitConInd,         /* 7 - tightly coupled, MPLS */
#else
   PtUiHitConInd,         /* 7 - tightly coupled, portable */
#endif
#ifdef DM
   DmLiHitConInd,         /* 8 - tightly coupled, Dummy Layer */
#else
   PtUiHitConInd,         /* 8 - tightly coupled, portable */
#endif
#ifdef SO
/*hi015.105 : For SIP MT, all primitives except DAT and UDAT
                              indications are made to loosely coupled. */
#ifdef SO_MT_SIP
   cmPkHitConInd,         /* In case of MT SIP, all API's except DAT, 
                             UDAT indication to be loosely coupled */ 
#else
   SoLiHitConInd,         /* 9 - tightly coupled, SIP */
#endif
#else
   PtUiHitConInd,         /* 9 - tightly coupled, portable */
#endif
#ifdef SV
   SvLiHitConInd,         /* 10 - tightly coupled, SIP User */
#else
   PtUiHitConInd,         /* 10 - tightly coupled, portable */
#endif
/* hi009.105 : Added FP as another user */
#ifdef FP
   FpLiHitConInd,         /* 11 - tightly coupled, FP */
#else
   PtUiHitConInd,          /* 11 - tightly coupled, portable */
#endif
/* hi012.105 : Added AQ as another user */
#ifdef AQ
   AqLiHitConInd         /* 12 - tightly coupled, Diameter */
#else
   PtUiHitConInd         /* 12 - tightly coupled, portable */
#endif
};


/* Connect Confirm */

PRIVATE HitConCfm HiUiHitConCfmMt[MAXHIUI] =
{
#ifdef LCHIUIHIT
   cmPkHitConCfm,         /* 0 - loosely coupled */
#else
   PtUiHitConCfm,         /* 0 - loosely coupled, portable */
#endif
#ifdef HC
   HcLiHitConCfm,         /* 1 - tightly coupled, H.323 Control */
#else
   PtUiHitConCfm,         /* 1 - tightly coupled, portable */
#endif
#ifdef HR
   HrLiHitConCfm,         /* 2 - tightly coupled, RTP/RTCP */
#else
   PtUiHitConCfm,         /* 2 - tightly coupled, portable */
#endif
#ifdef GT
   GtLiHitConCfm,         /* 3 - tightly coupled, GTP */
#else
   PtUiHitConCfm,         /* 3 - tightly coupled, portable */
#endif
#ifdef MG
   MgLiHitConCfm,         /* 4 - tightly coupled, MGCP */
#else
   PtUiHitConCfm,         /* 4 - tightly coupled, portable */
#endif
#ifdef HG
   HgLiHitConCfm,         /* 5 - tightly coupled, ANNEX G */
#else
   PtUiHitConCfm,         /* 5 - tightly coupled, portable */
#endif
#ifdef SB
   SbLiHitConCfm,         /* 6 - tightly coupled, SCTP */
#else
   PtUiHitConCfm,         /* 6 - tightly coupled, portable */
#endif
#ifdef LN
   LnLiHitConCfm,         /* 7 - tightly coupled, MPLS */
#else
   PtUiHitConCfm,         /* 7 - tightly coupled, portable */
#endif
#ifdef DM
   DmLiHitConCfm,         /* 8 - tightly coupled, Dummy Layer */
#else
   PtUiHitConCfm,         /* 8 - tightly coupled, portable */
#endif
#ifdef SO
/*hi015.105 : For SIP MT, all primitives except DAT and UDAT
                              indications are made to loosely coupled. */
#ifdef SO_MT_SIP
   cmPkHitConCfm,         /* 0 - loosely coupled */
#else
   SoLiHitConCfm,         /* 9 - tightly coupled, SIP */
#endif
#else
   PtUiHitConCfm,         /* 9 - tightly coupled, portable */
#endif
#ifdef SV
   SvLiHitConCfm,         /* 10 - tightly coupled, SIP User */
#else
   PtUiHitConCfm,         /* 10 - tightly coupled, portable User */
#endif
/* hi009.105 : Added FP as another user */
#ifdef FP
   FpLiHitConCfm,         /* 11 - tightly coupled, FP User */
#else
   PtUiHitConCfm,          /* 11 - tightly coupled, portable User */
#endif
/* hi012.105 : Added AQ as another user */
#ifdef AQ
   AqLiHitConCfm,         /* 12 - tightly coupled, Diameter */
#else
   PtUiHitConCfm,         /* 12 - tightly coupled, portable */
#endif
/* hi013.201 : Added EG as another user */
#ifdef EG
   EgLiHitConCfm         /* 13 - tightly coupled, EGTP */
#else
   PtUiHitConCfm         /* 13 - tightly coupled, portable */
#endif
};


/* Bind Confirm */

PRIVATE HitBndCfm HiUiHitBndCfmMt[MAXHIUI] =
{
#ifdef LCHIUIHIT
   cmPkHitBndCfm,         /* 0 - loosely coupled */
#else
   PtUiHitBndCfm,         /* 0 - loosely coupled, portable */
#endif
#ifdef HC
   HcLiHitBndCfm,         /* 1 - tightly coupled, H.323 Control */
#else
   PtUiHitBndCfm,         /* 1 - tightly coupled, portable */
#endif
#ifdef HR
   HrLiHitBndCfm,         /* 2 - tightly coupled, RTP/RTCP */
#else
   PtUiHitBndCfm,         /* 2 - tightly coupled, portable */
#endif
#ifdef GT
   GtLiHitBndCfm,         /* 3 - tightly coupled, GTP */
#else
   PtUiHitBndCfm,         /* 3 - tightly coupled, portable */
#endif
#ifdef MG
   MgLiHitBndCfm,         /* 4 - tightly coupled, MGCP */
#else
   PtUiHitBndCfm,         /* 4 - tightly coupled, portable */
#endif
#ifdef HG
   HgLiHitBndCfm,         /* 5 - tightly coupled, ANNEX G */
#else
   PtUiHitBndCfm,         /* 5 - tightly coupled, portable */
#endif
#ifdef SB
   SbLiHitBndCfm,         /* 6 - tightly coupled, SCTP */
#else
   PtUiHitBndCfm,         /* 6 - tightly coupled, portable */
#endif
#ifdef LN
   LnLiHitBndCfm,         /* 7 - tightly coupled, MPLS */
#else
   PtUiHitBndCfm,         /* 7 - tightly coupled, portable */
#endif
#ifdef DM
   DmLiHitBndCfm,         /* 8 - tightly coupled, Dummy Layer */
#else
   PtUiHitBndCfm,         /* 8 - tightly coupled, portable */
#endif
#ifdef SO
/*hi015.105 : For SIP MT, all primitives except DAT and UDAT
                              indications are made to loosely coupled. */
#ifdef SO_MT_SIP
   cmPkHitBndCfm,         /* 0 - loosely coupled */
#else
   SoLiHitBndCfm,         /* 9 - tightly coupled, SIP */
#endif
#else
   PtUiHitBndCfm,         /* 9 - tightly coupled, portable */
#endif
#ifdef SV
   SvLiHitBndCfm,         /* 10 - tightly coupled, SIP User */
#else
   PtUiHitBndCfm,         /* 10 - tightly coupled, portable */
#endif
/* hi009.105 : Added FP as another user */
#ifdef FP
   FpLiHitBndCfm,         /* 11 - tightly coupled, FP User */
#else
   PtUiHitBndCfm,          /* 11 - tightly coupled, portable */
#endif
/* hi012.105 : Added AQ as another user */
#ifdef AQ
   AqLiHitBndCfm,         /* 12 - tightly coupled, Diameter */
#else
   PtUiHitBndCfm,         /* 12 - tightly coupled, portable */
#endif
/* hi013.201 : Added EG as another user */
#ifdef EG
   EgLiHitBndCfm         /* 13 - tightly coupled, EGTP */
#else
   PtUiHitBndCfm         /* 13 - tightly coupled, portable */
#endif
};


/* Data Indication */

PRIVATE HitDatInd HiUiHitDatIndMt[MAXHIUI] =
{
#ifdef LCHIUIHIT
   cmPkHitDatInd,         /* 0 - loosely coupled */
#else
   PtUiHitDatInd,         /* 0 - loosely coupled, portable */
#endif
#ifdef HC
   HcLiHitDatInd,         /* 1 - tightly coupled, H.323 Control */
#else
   PtUiHitDatInd,         /* 1 - tightly coupled, portable */
#endif
#ifdef HR
   PtUiHitDatInd,         /* 2 - tightly coupled, RTP/RTCP */
#else
   PtUiHitDatInd,         /* 2 - tightly coupled, portable */
#endif
#ifdef GT
   GtLiHitDatInd,         /* 3 - tightly coupled, GTP */
#else
   PtUiHitDatInd,         /* 3 - tightly coupled, portable */
#endif
#ifdef MG
   MgLiHitDatInd,         /* 4 - tightly coupled, MGCP */
#else
   PtUiHitDatInd,         /* 4 - tightly coupled, portable */
#endif
#ifdef HG
   HgLiHitDatInd,         /* 5 - tightly coupled, ANNEX G */
#else
   PtUiHitDatInd,         /* 5 - tightly coupled, portable */
#endif
#ifdef SB
   PtUiHitDatInd,         /* 6 - tightly coupled, SCTP */
#else
   PtUiHitDatInd,         /* 6 - tightly coupled, portable */
#endif
#ifdef LN
   LnLiHitDatInd,         /* 7 - tightly coupled, MPLS */
#else
   PtUiHitDatInd,         /* 7 - tightly coupled, portable */
#endif
#ifdef DM
   DmLiHitDatInd,         /* 8 - tightly coupled, Dummy Layer */
#else
   PtUiHitDatInd,         /* 8 - tightly coupled, portable */
#endif
#ifdef SO
   SoLiHitDatInd,         /* 9 - tightly coupled, SIP */
#else
   PtUiHitDatInd,         /* 9 - tightly coupled, portable */
#endif
#ifdef SV
   SvLiHitDatInd,         /* 10 - tightly coupled, SIP User */
#else
   PtUiHitDatInd,         /* 10 - tightly coupled, portable */
#endif
/* hi009.105 : Added FP as another user */
#ifdef FP
   FpLiHitDatInd,         /* 11 - tightly coupled, FP User */
#else
   PtUiHitDatInd,          /* 11 - tightly coupled, portable */
#endif
/* hi012.105 : Added AQ as another user */
#ifdef AQ
   AqLiHitDatInd         /* 12 - tightly coupled, Diameter */
#else
   PtUiHitDatInd         /* 12 - tightly coupled, portable */
#endif
};


/* Unit Data Indication */
PRIVATE HitUDatInd HiUiHitUDatIndMt[MAXHIUI] =
{
#ifdef LCHIUIHIT
   cmPkHitUDatInd,         /* 0 - loosely coupled */
#else
   PtUiHitUDatInd,         /* 0 - loosely coupled, portable */
#endif
#ifdef HC
   HcLiHitUDatInd,         /* 1 - tightly coupled, H.323 Control */
#else
   PtUiHitUDatInd,         /* 1 - tightly coupled, portable */
#endif
#ifdef HR
   HrLiHitUDatInd,         /* 2 - tightly coupled, RTP/RTCP */
#else
   PtUiHitUDatInd,         /* 2 - tightly coupled, portable */
#endif
#ifdef GT
   GtLiHitUDatInd,         /* 3 - tightly coupled, GTP */
#else
   PtUiHitUDatInd,         /* 3 - tightly coupled, portable */
#endif
#ifdef MG
   MgLiHitUDatInd,         /* 4 - tightly coupled, MGCP */
#else
   PtUiHitUDatInd,         /* 4 - tightly coupled, portable */
#endif
#ifdef HG
   HgLiHitUDatInd,         /* 5 - tightly coupled, ANNEX G */
#else
   PtUiHitUDatInd,         /* 5 - tightly coupled, portable */
#endif
#ifdef SB
   SbLiHitUDatInd,         /* 6 - tightly coupled, SCTP */
#else
   PtUiHitUDatInd,         /* 6 - tightly coupled, portable */
#endif
#ifdef LN
   LnLiHitUDatInd,         /* 7 - tightly coupled, MPLS */
#else
   PtUiHitUDatInd,         /* 7 - tightly coupled, portable */
#endif
#ifdef DM
   DmLiHitUDatInd,         /* 8 - tightly coupled, Dummy Layer */
#else
   PtUiHitUDatInd,         /* 8 - tightly coupled, portable */
#endif
#ifdef SO
   SoLiHitUDatInd,         /* 9 - tightly coupled, SIP */
#else
   PtUiHitUDatInd,         /* 9 - tightly coupled, portable */
#endif
#ifdef SV
   SvLiHitUDatInd,         /* 10 - tightly coupled, SIP User */
#else
   PtUiHitUDatInd,         /* 10 - tightly coupled, portable */
#endif
/* hi009.105 : Added FP as another user */
#ifdef FP
   FpLiHitUDatInd,         /* 11 - tightly coupled, FP User */
#else
   PtUiHitUDatInd,          /* 11 - tightly coupled, portable */
#endif
/* hi012.105 : Added AQ as another user */
#ifdef AQ 
   PtUiHitUDatInd,         /* 12 - tightly coupled, AQ User (portable) */
#else
   PtUiHitUDatInd,          /* 12 - tightly coupled, portable */
#endif
/* hi013.201 : Added EG as another user */
#ifdef EG 
   EgLiHitUDatInd         /* 13 - tightly coupled, EG User */
#else
   PtUiHitUDatInd          /* 13 - tightly coupled, portable */
#endif
};


/* Disconnect Indication */

PRIVATE HitDiscInd HiUiHitDiscIndMt[MAXHIUI] =
{
#ifdef LCHIUIHIT
   cmPkHitDiscInd,         /* 0 - loosely coupled */
#else
   PtUiHitDiscInd,         /* 0 - loosely coupled, portable */
#endif
#ifdef HC
   HcLiHitDiscInd,         /* 1 - tightly coupled, H.323 Control */
#else
   PtUiHitDiscInd,         /* 1 - tightly coupled, portable */
#endif
#ifdef HR
   HrLiHitDiscInd,         /* 2 - tightly coupled, RTP/RTCP */
#else
   PtUiHitDiscInd,         /* 2 - tightly coupled, portable */
#endif
#ifdef GT
   GtLiHitDiscInd,         /* 3 - tightly coupled, GTP */
#else
   PtUiHitDiscInd,         /* 3 - tightly coupled, portable */
#endif
#ifdef MG
   MgLiHitDiscInd,         /* 4 - tightly coupled, MGCP */
#else
   PtUiHitDiscInd,         /* 4 - tightly coupled, portable */
#endif
#ifdef HG
   HgLiHitDiscInd,         /* 5 - tightly coupled, ANNEX G */
#else
   PtUiHitDiscInd,         /* 5 - tightly coupled, portable */
#endif
#ifdef SB
   SbLiHitDiscInd,         /* 6 - tightly coupled, SCTP */
#else
   PtUiHitDiscInd,         /* 6 - tightly coupled, portable */
#endif
#ifdef LN
   LnLiHitDiscInd,         /* 7 - tightly coupled, MPLS */
#else
   PtUiHitDiscInd,         /* 7 - tightly coupled, portable */
#endif
#ifdef DM
   DmLiHitDiscInd,         /* 8 - tightly coupled, Dummy Layer */
#else
   PtUiHitDiscInd,         /* 8 - tightly coupled, portable */
#endif
#ifdef SO
/*hi015.105 : For SIP MT, all primitives except DAT and UDAT
                              indications are made to loosely coupled. */
#ifdef SO_MT_SIP
   cmPkHitDiscInd,         /* 0 - loosely coupled */
#else
   SoLiHitDiscInd,         /* 9 - tightly coupled, SIP */
#endif
#else
   PtUiHitDiscInd,         /* 9 - tightly coupled, portable */
#endif
#ifdef SV
   SvLiHitDiscInd,         /* 10 - tightly coupled, SIP User */
#else
   PtUiHitDiscInd,         /* 10 - tightly coupled, portable */
#endif
/* hi009.105 : Added FP as another user */
#ifdef FP
   FpLiHitDiscInd,         /* 11 - tightly coupled, FP User */
#else
   PtUiHitDiscInd,          /* 11 - tightly coupled, portable */
#endif

/* hi012.105 : Added AQ as another user */
#ifdef AQ
   AqLiHitDiscInd,         /* 12 - tightly coupled, Diameter */
#else
   PtUiHitDiscInd,         /* 12 - tightly coupled, portable */
#endif
/* hi013.201 : Added EG as another user */
#ifdef EG
   EgLiHitDiscInd         /* 13 - tightly coupled, EGTP */
#else
   PtUiHitDiscInd         /* 13 - tightly coupled, portable */
#endif
};


/* Disconnect Confirm */

PRIVATE HitDiscCfm HiUiHitDiscCfmMt[MAXHIUI] =
{
#ifdef LCHIUIHIT
   cmPkHitDiscCfm,         /* 0 - loosely coupled */
#else
   PtUiHitDiscCfm,         /* 0 - loosely coupled, portable */
#endif
#ifdef HC
   HcLiHitDiscCfm,         /* 1 - tightly coupled, H.323 Control */
#else
   PtUiHitDiscCfm,         /* 1 - tightly coupled, portable */
#endif
#ifdef HR
   HrLiHitDiscCfm,         /* 2 - tightly coupled, RTP/RTCP */
#else
   PtUiHitDiscCfm,         /* 2 - tightly coupled, portable */
#endif
#ifdef GT
   GtLiHitDiscCfm,         /* 3 - tightly coupled, GTP */
#else
   PtUiHitDiscCfm,         /* 3 - tightly coupled, portable */
#endif
#ifdef MG
   MgLiHitDiscCfm,         /* 4 - tightly coupled, MGCP */
#else
   PtUiHitDiscCfm,         /* 4 - tightly coupled, portable */
#endif
#ifdef HG
   HgLiHitDiscCfm,         /* 5 - tightly coupled, ANNEX G */
#else
   PtUiHitDiscCfm,         /* 5 - tightly coupled, portable */
#endif
#ifdef SB
   SbLiHitDiscCfm,         /* 6 - tightly coupled, SCTP */
#else
   PtUiHitDiscCfm,         /* 6 - tightly coupled, portable */
#endif
#ifdef LN
   LnLiHitDiscCfm,         /* 7 - tightly coupled, MPLS */
#else
   PtUiHitDiscCfm,         /* 7 - tightly coupled, portable */
#endif
#ifdef DM
   DmLiHitDiscCfm,         /* 8 - tightly coupled, Dummy Layer */
#else
   PtUiHitDiscCfm,         /* 8 - tightly coupled, portable */
#endif
#ifdef SO
/*hi015.105 : For SIP MT, all primitives except DAT and UDAT
                              indications are made to loosely coupled. */
#ifdef SO_MT_SIP
   cmPkHitDiscCfm,         /* 0 - loosely coupled */
#else
   SoLiHitDiscCfm,         /* 9 - tightly coupled, SIP */
#endif
#else
   PtUiHitDiscCfm,         /* 9 - tightly coupled, portable */
#endif
#ifdef SV
   SvLiHitDiscCfm,         /* 10 - tightly coupled, SIP User */
#else
   PtUiHitDiscCfm,         /* 10 - tightly coupled, portable */
#endif
/* hi009.105 : Added FP as another user */
#ifdef FP
   FpLiHitDiscCfm,         /* 11 - tightly coupled, FP User */
#else
   PtUiHitDiscCfm,          /* 11 - tightly coupled, portable */
#endif
/* hi012.105 : Added AQ as another user */
#ifdef AQ
   AqLiHitDiscCfm,         /* 12 - tightly coupled, Diameter */
#else
   PtUiHitDiscCfm,         /* 12 - tightly coupled, portable */
#endif
/* hi013.201 : Added EG as another user */
#ifdef EG
   EgLiHitDiscCfm         /* 13 - tightly coupled, EGTP */
#else
   PtUiHitDiscCfm         /* 13 - tightly coupled, portable */
#endif
};


/* Flow Control Indication */

PRIVATE HitFlcInd HiUiHitFlcIndMt[MAXHIUI] =
{
#ifdef LCHIUIHIT
   cmPkHitFlcInd,         /* 0 - loosely coupled */
#else
   PtUiHitFlcInd,         /* 0 - loosely coupled, portable */
#endif
#ifdef HC
   HcLiHitFlcInd,         /* 1 - tightly coupled, H.323 Control */
#else
   PtUiHitFlcInd,         /* 1 - tightly coupled, portable */
#endif
#ifdef HR
   PtUiHitFlcInd,         /* 2 - tightly coupled, RTP/RTCP */
#else
   PtUiHitFlcInd,         /* 2 - tightly coupled, portable */
#endif
#ifdef GT
   GtLiHitFlcInd,         /* 3 - tightly coupled, GTP */
#else
   PtUiHitFlcInd,         /* 3 - tightly coupled, portable */
#endif
#ifdef MG
   MgLiHitFlcInd,         /* 4 - tightly coupled, MGCP */
#else
   PtUiHitFlcInd,         /* 4 - tightly coupled, portable */
#endif
#ifdef HG
   HgLiHitFlcInd,         /* 5 - tightly coupled, ANNEX G */
#else
   PtUiHitFlcInd,         /* 5 - tightly coupled, portable */
#endif
#ifdef SB
   PtUiHitFlcInd,         /* 6 - tightly coupled, SCTP */
#else
   PtUiHitFlcInd,         /* 6 - tightly coupled, portable */
#endif
#ifdef LN
   LnLiHitFlcInd,         /* 7 - tightly coupled, MPLS */
#else
   PtUiHitFlcInd,         /* 7 - tightly coupled, portable */
#endif
#ifdef DM
   DmLiHitFlcInd,         /* 8 - tightly coupled, Dummy Layer */
#else
   PtUiHitFlcInd,         /* 8 - tightly coupled, portable */
#endif
#ifdef SO
/*hi015.105 : For SIP MT, all primitives except DAT and UDAT
                              indications are made to loosely coupled. */
#ifdef SO_MT_SIP
   cmPkHitFlcInd,         /* 0 - loosely coupled */
#else
   SoLiHitFlcInd,         /* 9 - tightly coupled, SIP */
#endif
#else
   PtUiHitFlcInd,         /* 9 - tightly coupled, portable */
#endif
#ifdef SV
   SvLiHitFlcInd,         /* 10 - tightly coupled, SIP User */
#else
   PtUiHitFlcInd,         /* 10 - tightly coupled, portable */
#endif
/* hi009.105 : Added FP as another user */
#ifdef FP
   FpLiHitFlcInd,         /* 11 - tightly coupled, FP User */
#else
   PtUiHitFlcInd,          /* 11 - tightly coupled, portable */
#endif
/* hi012.105 : Added AQ as another user */
#ifdef AQ
   AqLiHitFlcInd,         /* 12 - tightly coupled, Diameter */
#else
   PtUiHitFlcInd,         /* 12 - tightly coupled, portable */
#endif
/* hi013.201 : Added EG as another user */
/* hi014.201 : Changed the EgLiHit to PtUi as it is not required */
#ifdef EG
   PtUiHitFlcInd         /* 13 - tightly coupled, EGTP */
#else
   PtUiHitFlcInd         /* 13 - tightly coupled, portable */
#endif
};

/* hi013.105 :  Added two new HIT primitives. HiUiHitTlsEstReq(), HiUiHitTlsEstCfm().*/
#ifdef HITV2
#ifdef HI_TLS
#ifdef HI_TCP_TLS

/* Tls Establishment Confirm */
PRIVATE HitTlsEstCfm HiUiHitTlsEstCfmMt[MAXHIUI] =
{
#ifdef LCHIUIHIT
   cmPkHitTlsEstCfm,         /* 0 - loosely coupled */
#else
   PtUiHitTlsEstCfm,         /* 0 - loosely coupled, portable */
#endif
#ifdef HC
   PtUiHitTlsEstCfm,         /* 1 - tightly coupled, H.323 Control */
#else
   PtUiHitTlsEstCfm,         /* 1 - tightly coupled, portable */
#endif
#ifdef HR
   PtUiHitTlsEstCfm,         /* 2 - tightly coupled, RTP/RTCP */
#else
   PtUiHitTlsEstCfm,         /* 2 - tightly coupled, portable */
#endif
#ifdef GT
   PtUiHitTlsEstCfm,         /* 3 - tightly coupled, GTP */
#else
   PtUiHitTlsEstCfm,         /* 3 - tightly coupled, portable */
#endif
#ifdef MG
   PtUiHitTlsEstCfm,         /* 4 - tightly coupled, MGCP */
#else
   PtUiHitTlsEstCfm,         /* 4 - tightly coupled, portable */
#endif
#ifdef HG
   PtUiHitTlsEstCfm,         /* 5 - tightly coupled, ANNEX G */
#else
   PtUiHitTlsEstCfm,         /* 5 - tightly coupled, portable */
#endif
#ifdef SB
   PtUiHitTlsEstCfm,         /* 6 - tightly coupled, SCTP */
#else
   PtUiHitTlsEstCfm,         /* 6 - tightly coupled, portable */
#endif
#ifdef LN
   PtUiHitTlsEstCfm,         /* 7 - tightly coupled, MPLS */
#else
   PtUiHitTlsEstCfm,         /* 7 - tightly coupled, portable */
#endif
#ifdef DM
   PtUiHitTlsEstCfm,         /* 8 - tightly coupled, Dummy Layer */
#else
   PtUiHitTlsEstCfm,         /* 8 - tightly coupled, portable */
#endif
#ifdef SO
   PtUiHitTlsEstCfm,         /* 9 - tightly coupled, SIP */
#else
   PtUiHitTlsEstCfm,         /* 9 - tightly coupled, portable */
#endif
#ifdef SV
   PtUiHitTlsEstCfm,         /* 10 - tightly coupled, SIP User */
#else
   PtUiHitTlsEstCfm,         /* 10 - tightly coupled, portable */
#endif
#ifdef FP
   PtUiHitTlsEstCfm,         /* 11 - tightly coupled, FP User */
#else
   PtUiHitTlsEstCfm,         /* 11 - tightly coupled, portable */
#endif 
#ifdef AQ 
   AqLiHitTlsEstCfm          /* 12 - tightly coupled, AQ User */
#else
   PtUiHitTlsEstCfm          /* 12 - tightly coupled, portable User */
#endif
};

#endif /* HI_TCP_TLS */
#endif /* HI_TLS */
#endif /* HITV2 */

#ifdef HI_LKSCTP

/*
 *  upper interface functions
 */




#ifdef ANSI
PUBLIC S16 HiUiSctBndCfm
(
Pst           *pst,
SuId           suId,
SctResult      result
)
#else
PUBLIC S16 HiUiSctBndCfm(pst, suId, result)
Pst           *pst;
SuId           suId;
SctResult      result;
#endif
{
   TRC3(HiUiSctBndCfm)

   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctBndCfm(pst, suId(%d), result(%d))\n",
          suId, result));

   /* jump to specific primitive depending on configured selector */
   /* sb048.102: DFTHA M3UA Support */
   switch (pst->dstEnt)
   {
      /* hi028.201: Added sua DFTHA support */
#ifdef DV
      case ENTIT:
         if (pst->route == RTE_PROTO)
         {
            (*HiUiSctBndCfmMt[pst->selector])(pst, suId, result);
         }
         else
         {
            DvUiSctBndCfm(pst, suId, result);
         }
         break;
#endif /* DV */
#ifdef AH
      case ENTSU:
         if (pst->route == RTE_PROTO)
         {
            (*HiUiSctBndCfmMt[pst->selector])(pst, suId, result);
         }
         else
         {
            AhLiSctBndCfm(pst, suId, result);
         }
         break;
#endif /* AH */

      default:
         (*HiUiSctBndCfmMt[pst->selector])(pst, suId, result);
         break;
   }

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 HiUiSctEndpOpenCfm
(
Pst           *pst,
SuId           suId,
UConnId        suEndpId,
UConnId        spEndpId,
SctResult      result,
SctCause       cause
)
#else
PUBLIC S16 HiUiSctEndpOpenCfm(pst, suId, suEndpId, spEndpId, result, cause)
Pst           *pst;
SuId           suId;
UConnId        suEndpId;
UConnId        spEndpId;
SctResult      result;
SctCause       cause;
#endif
{
   TRC3(HiUiSctEndpOpenCfm)

      
         /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctEndpOpenCfm(pst, suId(%d), suEndpId(%ld), spEndpId(%ld), result(%d), cause(%d))\n",
          suId, suEndpId, spEndpId, result, cause));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctEndpOpenCfm(pst, suId(%d), suEndpId(%d), spEndpId(%d), result(%d), cause(%d))\n",
          suId, suEndpId, spEndpId, result, cause));
#endif

   /* jump to specific primitive depending on configured selector */
   /* sb048.102: DFTHA M3UA Support */
   switch (pst->dstEnt)
   {
      /* hi028.201: Added sua DFTHA support */
#ifdef DV
      case ENTIT:
         if (pst->route == RTE_PROTO)
         {
            (*HiUiSctEndpOpenCfmMt[pst->selector])(pst, suId, suEndpId, spEndpId, 
                result, cause);
         }
         else
         {
            DvUiSctEndpOpenCfm(pst, suId, suEndpId, spEndpId, result, cause);
         }
         break;
#endif /* DV */
#ifdef AH
      case ENTSU:
         if (pst->route == RTE_PROTO)
         {
            (*HiUiSctEndpOpenCfmMt[pst->selector])(pst, suId, suEndpId, spEndpId, 
                result, cause);
         }
         else
         {
            AhLiSctEndpOpenCfm(pst, suId, suEndpId, spEndpId, result, cause);
         }
         break;
#endif /* AH */

      default:
         (*HiUiSctEndpOpenCfmMt[pst->selector])(pst, suId, suEndpId, spEndpId, 
             result, cause);
         break;
   }

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 HiUiSctEndpCloseCfm
(
Pst           *pst,
SuId           suId,
UConnId        suEndpId,
SctResult      result,
SctCause       cause
)
#else
PUBLIC S16 HiUiSctEndpCloseCfm(pst, suId, suEndpId, result, cause)
Pst           *pst;
SuId           suId;
UConnId        suEndpId;
SctResult      result;
SctCause       cause;
#endif
{
   TRC3(HiUiSctEndpCloseCfm)


         /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctEndpCloseCfm(pst, suId(%d), suEndpId(%ld), result(%d), cause(%d))\n",
          suId, suEndpId, result, cause));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctEndpCloseCfm(pst, suId(%d), suEndpId(%d), result(%d), cause(%d))\n",
          suId, suEndpId, result, cause));
#endif

   /* jump to specific primitive depending on configured selector */
   /* sb048.102: DFTHA M3UA Support */
   switch (pst->dstEnt)
   {
      /* hi028.201: Added sua DFTHA support */
#ifdef DV
      case ENTIT:
         if (pst->route == RTE_PROTO)
         {
            (*HiUiSctEndpCloseCfmMt[pst->selector])(pst, suId, suEndpId, result, 
              cause);
         }
         else
         {
            DvUiSctEndpCloseCfm(pst, suId, suEndpId, result, cause);
         }
         break;
#endif /* DV */
#ifdef AH
      case ENTSU:
         if (pst->route == RTE_PROTO)
         {
            (*HiUiSctEndpCloseCfmMt[pst->selector])(pst, suId, suEndpId, result, 
              cause);
         }
         else
         {
            AhLiSctEndpOpenCfm(pst, suId, suEndpId, result, cause);
         }
         break;
#endif /* AH */

      default:
         (*HiUiSctEndpCloseCfmMt[pst->selector])(pst, suId, suEndpId, result, 
              cause);
         break;
   }

   RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 HiUiSctAssocInd
(
Pst               *pst,
SuId               suId,
UConnId            suEndpId,
SctAssocIndParams *assocParams,
Buffer            *vsInfo
)
#else
PUBLIC S16 HiUiSctAssocInd(pst, suId, suEndpId, assocParams, vsInfo)
Pst               *pst;
SuId               suId;
UConnId            suEndpId;
SctAssocIndParams *assocParams;
Buffer            *vsInfo;
#endif
{
   TRC3(HiUiSctAssocInd)

   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctAssocInd(pst, assocParams)\n"));

   /* jump to specific primitive depending on configured selector */
   /* sb048.102: DFTHA M3UA Support */
   switch (pst->dstEnt)
   {
      /* hi028.201: Added sua DFTHA support */
#ifdef DV
      case ENTIT:
         if (pst->route == RTE_PROTO)
         {
            (*HiUiSctAssocIndMt[pst->selector])(pst, suId, suEndpId, assocParams, 
                vsInfo);
         }
         else
         {
            DvUiSctAssocInd(pst, suId, suEndpId, assocParams, vsInfo);
         }
         break;
#endif /* DV */
#ifdef AH
      case ENTSU:
         if (pst->route == RTE_PROTO)
         {
            (*HiUiSctAssocIndMt[pst->selector])(pst, suId, suEndpId, assocParams, 
                vsInfo);
         }
         else
         {
            AhLiSctAssocInd(pst, suId, suEndpId, assocParams, vsInfo);
         }
         break;
#endif /* AH */

      default:
         (*HiUiSctAssocIndMt[pst->selector])(pst, suId, suEndpId, assocParams, 
             vsInfo);
         break;
   }

   RETVALUE(ROK);
}



/* sb016.102 - Include in-stream parameter here */
#ifdef SCT2
#ifdef ANSI
PUBLIC S16 HiUiSctAssocCfm
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
UConnId        spAssocId,
SctNetAddrLst *dstNAddrLst,
SctPort        dstPort,
SctStrmId      inStrms,
SctStrmId      outStrms,
Buffer        *vsInfo
)
#else
PUBLIC S16 HiUiSctAssocCfm(pst, suId, suAssocId, spAssocId, dstNAddrLst, dstPort, inStrms, outStrms, vsInfo )
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
UConnId        spAssocId;
SctNetAddrLst *dstNAddrLst;
SctPort        dstPort;
SctStrmId      inStrms;
SctStrmId      outStrms;
Buffer        *vsInfo;
#endif /* ANSI */
#else
#ifdef ANSI
PUBLIC S16 HiUiSctAssocCfm
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
UConnId        spAssocId,
SctNetAddrLst *dstNAddrLst,
SctPort        dstPort,
SctStrmId      outStrms,
Buffer        *vsInfo
)
#else
PUBLIC S16 HiUiSctAssocCfm(pst, suId, suAssocId, spAssocId, dstNAddrLst, dstPort, outStrms, vsInfo )
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
UConnId        spAssocId;
SctNetAddrLst *dstNAddrLst;
SctPort        dstPort;
SctStrmId      outStrms;
Buffer        *vsInfo;
#endif /* ANSI */
#endif /* SCT2  */
{
   TRC3(HiUiSctAssocCfm)

/* sb016.102 - Include in-stream parameter here */
#ifdef SCT2


         /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctAssocCfm(pst, suId(%d), suAssocId(%ld), spAssocId(%ld), dstNAddrLst, dstPort(%d), inStrms(%d), outStrms(%d))\n",
          suId, suAssocId, spAssocId, dstPort, inStrms, outStrms));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctAssocCfm(pst, suId(%d), suAssocId(%d), spAssocId(%d), dstNAddrLst, dstPort(%d), inStrms(%d), outStrms(%d))\n",
          suId, suAssocId, spAssocId, dstPort, inStrms, outStrms));
#endif

   /* jump to specific primitive depending on configured selector */
   /* sb048.102: DFTHA M3UA Support */
   /* sb049.102: DFTHA M3UA Support */
   switch (pst->dstEnt)
   {
      /* hi028.201: Added sua DFTHA support */
#ifdef DV
      case ENTIT:
         if (pst->route == RTE_PROTO)
         {
            (*HiUiSctAssocCfmMt[pst->selector])(pst, suId, suAssocId, spAssocId, 
              dstNAddrLst, dstPort, inStrms, outStrms, vsInfo);
         }
         else
         {
            DvUiSctAssocCfm(pst, suId, suAssocId, spAssocId, dstNAddrLst, 
               dstPort, inStrms, outStrms, vsInfo);
         }
         break;
#endif /* DV */
#ifdef AH
      case ENTSU:
         if (pst->route == RTE_PROTO)
         {
            (*HiUiSctAssocCfmMt[pst->selector])(pst, suId, suAssocId, spAssocId, 
              dstNAddrLst, dstPort, inStrms, outStrms, vsInfo);
         }
         else
         {
            AhLiSctAssocCfm(pst, suId, suAssocId, spAssocId, dstNAddrLst, 
               dstPort, inStrms, outStrms, vsInfo);
         }
         break;
#endif /* AH */

      default:
         (*HiUiSctAssocCfmMt[pst->selector])(pst, suId, suAssocId, spAssocId, 
              dstNAddrLst, dstPort, inStrms, outStrms, vsInfo);
         break;
   }

#else /* SCT2 */

         /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctAssocCfm(pst, suId(%d), suAssocId(%ld), spAssocId(%ld), dstNAddrLst, dstPort(%d), outStrms(%d))\n",
          suId, suAssocId, spAssocId, dstPort, outStrms));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctAssocCfm(pst, suId(%d), suAssocId(%d), spAssocId(%d), dstNAddrLst, dstPort(%d), outStrms(%d))\n",
          suId, suAssocId, spAssocId, dstPort, outStrms));
#endif

   /* jump to specific primitive depending on configured selector */
   /* sb048.102: DFTHA M3UA Support */
   switch (pst->dstEnt)
   {
      /* hi028.201: Added sua DFTHA support */
#ifdef DV
      case ENTIT:
         if (pst->route == RTE_PROTO)
         {
            (*HiUiSctAssocCfmMt[pst->selector])(pst, suId, suAssocId, spAssocId, 
              dstNAddrLst, dstPort, outStrms, vsInfo);
         }
         else
         {
            DvUiSctAssocCfm(pst, suId, suAssocId, spAssocId, dstNAddrLst, 
               dstPort, outStrms, vsInfo);
         }
         break;
#endif /* DV */
#ifdef AH
      case ENTSU:
         if (pst->route == RTE_PROTO)
         {
            (*HiUiSctAssocCfmMt[pst->selector])(pst, suId, suAssocId, spAssocId, 
              dstNAddrLst, dstPort, outStrms, vsInfo);
         }
         else
         {
            AhLiSctAssocCfm(pst, suId, suAssocId, spAssocId, dstNAddrLst, 
               dstPort, outStrms, vsInfo);
         }
         break;
#endif /* AH */

      default:
         (*HiUiSctAssocCfmMt[pst->selector])(pst, suId, suAssocId, spAssocId, 
              dstNAddrLst, dstPort, outStrms, vsInfo);
         break;
   }

#endif /* SCT2 */

   RETVALUE(ROK);
}




#ifdef ANSI
PUBLIC S16 HiUiSctTermInd
(
Pst           *pst,
SuId           suId,
UConnId        assocId,
U8             assocIdType,
SctStatus      status,
SctCause       cause,
SctRtrvInfo   *rtrvInfo
)
#else
PUBLIC S16 HiUiSctTermInd(pst, suId, assocId, assocIdType, status, cause, rtrvInfo)
Pst           *pst;
SuId           suId;
UConnId        assocId;
U8             assocIdType;
SctStatus      status;
SctCause       cause;
SctRtrvInfo   *rtrvInfo;
#endif
{
   TRC3(HiUiSctTermInd)


         /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctTermInd(pst, suId(%d), assocId(%ld), assocIdType(%d), status(%d), cause(%d), rtrvInfo)\n",
          suId, assocId, assocIdType, status, cause));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctTermInd(pst, suId(%d), assocId(%d), assocIdType(%d), status(%d), cause(%d), rtrvInfo)\n",
          suId, assocId, assocIdType, status, cause));
#endif

   /* jump to specific primitive depending on configured selector */
   /* sb048.102: DFTHA M3UA Support */
   switch (pst->dstEnt)
   {
      /* hi028.201: Added sua DFTHA support */
#ifdef DV
      case ENTIT:
         if (pst->route == RTE_PROTO)
         {
            (*HiUiSctTermIndMt[pst->selector])(pst, suId, assocId, assocIdType, 
                status, cause, rtrvInfo);
         }
         else
         {
            DvUiSctTermInd(pst, suId, assocId, assocIdType, status, cause, 
               rtrvInfo);
         }
         break;
#endif /* DV */
#ifdef AH
      case ENTSU:
         if (pst->route == RTE_PROTO)
         {
            (*HiUiSctTermIndMt[pst->selector])(pst, suId, assocId, assocIdType, 
                status, cause, rtrvInfo);
         }
         else
         {
            AhLiSctTermInd(pst, suId, assocId, assocIdType, status, cause, 
               rtrvInfo);
         }
         break;
#endif /* AH */

      default:
         (*HiUiSctTermIndMt[pst->selector])(pst, suId, assocId, assocIdType, 
             status, cause, rtrvInfo);
         break;
   }

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 HiUiSctTermCfm
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
SctResult      result,
SctCause       cause
)
#else
PUBLIC S16 HiUiSctTermCfm(pst, suId, suAssocId, result, cause)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
SctResult      result;
SctCause       cause;
#endif
{
   TRC3(HiUiSctTermCfm)


         /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctTermCfm(pst, suId(%d), suAssocId(%ld), result(%d), cause(%d))\n",
          suId, suAssocId, result, cause));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctTermCfm(pst, suId(%d), suAssocId(%d), result(%d), cause(%d))\n",
          suId, suAssocId, result, cause));
#endif

   /* jump to specific primitive depending on configured selector */
   /* sb048.102: DFTHA M3UA Support */
   switch (pst->dstEnt)
   {
      /* hi028.201: Added sua DFTHA support */
#ifdef DV
      case ENTIT:
         if (pst->route == RTE_PROTO)
         {
            (*HiUiSctTermCfmMt[pst->selector])(pst, suId, suAssocId, result,
                cause);
         }
         else
         {
            DvUiSctTermCfm(pst, suId, suAssocId, result, cause);
         }
         break;
#endif /* DV */
#ifdef AH
      case ENTSU:
         if (pst->route == RTE_PROTO)
         {
            (*HiUiSctTermCfmMt[pst->selector])(pst, suId, suAssocId, result,
                cause);
         }
         else
         {
            AhLiSctTermCfm(pst, suId, suAssocId, result, cause);
         }
         break;
#endif /* AH */

      default:
         (*HiUiSctTermCfmMt[pst->selector])(pst, suId, suAssocId, result, cause);
         break;
   }

   RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 HiUiSctSetPriCfm
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
SctResult      result,
SctCause       cause
)
#else
PUBLIC S16 HiUiSctSetPriCfm(pst, suId, suAssocId, result, cause)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
SctResult      result;
SctCause       cause;
#endif
{
   TRC3(HiUiSctSetPriCfm)


         /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctSetPriCfm(pst, suId(%d), suAssocId(%ld), result(%d), cause(%d))\n",
          suId, suAssocId, result, cause));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctSetPriCfm(pst, suId(%d), suAssocId(%d), result(%d), cause(%d))\n",
          suId, suAssocId, result, cause));
#endif

   /* jump to specific primitive depending on configured selector */
   /* sb048.102: DFTHA M3UA Support */
   switch (pst->dstEnt)
   {
      /* hi028.201: Added sua DFTHA support */
#ifdef DV
      case ENTIT:
         if (pst->route == RTE_PROTO)
         {
            (*HiUiSctSetPriCfmMt[pst->selector])(pst, suId, suAssocId, result,
                cause);
         }
         else
         {
            HiUiSctSetPriCfm(pst, suId, suAssocId, result, cause);
         }
         break;
#endif /* DV */
#ifdef AH
      case ENTSU:
         if (pst->route == RTE_PROTO)
         {
            (*HiUiSctSetPriCfmMt[pst->selector])(pst, suId, suAssocId, result,
                cause);
         }
         else
         {
            AhLiSctSetPriCfm(pst, suId, suAssocId, result, cause);
         }
         break;
#endif /* AH */

      default:
         (*HiUiSctSetPriCfmMt[pst->selector])(pst, suId, suAssocId, result,
             cause);
         break;
   }

   RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 HiUiSctHBeatCfm
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
CmNetAddr     *dstNAddr,
SctStatus      status,
SctResult      result,
SctCause       cause
)
#else
PUBLIC S16 HiUiSctHBeatCfm(pst, suId, suAssocId, dstNAddr, status, result, cause)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
CmNetAddr     *dstNAddr;
SctStatus      status;
SctResult      result;
SctCause       cause;
#endif
{
   TRC3(HiUiSctHBeatCfm)


         /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctHBeatCfm(pst, suId(%d), suAssocId(%ld), dstNAddr, status(%d), result(%d), cause(%d))\n",
          suId, suAssocId, status, result, cause));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctHBeatCfm(pst, suId(%d), suAssocId(%d), dstNAddr, status(%d), result(%d), cause(%d))\n",
          suId, suAssocId, status, result, cause));
#endif

   /* jump to specific primitive depending on configured selector */
   /* sb048.102: DFTHA M3UA Support */
   switch (pst->dstEnt)
   {
      /* hi028.201: Added sua DFTHA support */
#ifdef DV
      case ENTIT:
         if (pst->route == RTE_PROTO)
         {
            (*HiUiSctHBeatCfmMt[pst->selector])(pst, suId, suAssocId, dstNAddr,
               status, result, cause);
         }
         else
         {
            DvUiSctHBeatCfm(pst, suId, suAssocId, dstNAddr, status, result,
               cause);
         }
         break;
#endif /* DV */
#ifdef AH
      case ENTSU:
         if (pst->route == RTE_PROTO)
         {
            (*HiUiSctHBeatCfmMt[pst->selector])(pst, suId, suAssocId, dstNAddr,
               status, result, cause);
         }
         else
         {
            AhLiSctHBeatCfm(pst, suId, suAssocId, dstNAddr, status, result,
               cause);
         }
         break;
#endif /* AH */

      default:
         (*HiUiSctHBeatCfmMt[pst->selector])(pst, suId, suAssocId, dstNAddr,
              status, result, cause);
         break;
   }

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 HiUiSctDatInd
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
SctStrmId      strmId,
SctDatIndType *indType,
U32            protId,
Buffer        *mBuf
)
#else
PUBLIC S16 HiUiSctDatInd(pst, suId, suAssocId, strmId, indType, protId, mBuf)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
SctStrmId      strmId;
SctDatIndType *indType;
U32            protId;
Buffer        *mBuf;
#endif
{
   TRC3(HiUiSctDatInd)


         /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctDatInd(pst, suId(%d), suAssocId(%ld), strmId(%d), indType, protId(%ld), mBuf)\n",
          suId, suAssocId, strmId, protId));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctDatInd(pst, suId(%d), suAssocId(%d), strmId(%d), indType, protId(%d), mBuf)\n",
          suId, suAssocId, strmId, protId));
#endif

   /* jump to specific primitive depending on configured selector */
   /* sb048.102: DFTHA M3UA Support */
   switch (pst->dstEnt)
   {
      /* hi028.201: Added sua DFTHA support */
#ifdef DV
      case ENTIT:
         if (pst->route == RTE_PROTO)
         {
            (*HiUiSctDatIndMt[pst->selector])(pst, suId, suAssocId, strmId, 
                indType, protId, mBuf);
         }
         else
         {
            DvUiSctDatInd(pst, suId, suAssocId, strmId, indType, protId, mBuf);
         }
         break;
#endif /* DV */
#ifdef AH
      case ENTSU:
         if (pst->route == RTE_PROTO)
         {
            (*HiUiSctDatIndMt[pst->selector])(pst, suId, suAssocId, strmId, 
                indType, protId, mBuf);
         }
         else
         {
            AhLiSctDatInd(pst, suId, suAssocId, strmId, indType, protId, mBuf);
         }
         break;
#endif /* AH */

      default:
         (*HiUiSctDatIndMt[pst->selector])(pst, suId, suAssocId, strmId, 
             indType, protId, mBuf);
         break;
   }

   RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 HiUiSctStaCfm
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
CmNetAddr     *dstNAddr,
SctResult      result,
SctCause       cause,
SctStaInfo    *staInfo
)
#else
PUBLIC S16 HiUiSctStaCfm(pst, suId, suAssocId, dstNAddr, result, cause, staInfo)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
CmNetAddr     *dstNAddr;
SctResult      result;
SctCause       cause;
SctStaInfo    *staInfo;
#endif
{
   TRC3(HiUiSctStaCfm)


         /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctStaCfm(pst, suId(%d), suAssocId(%ld), dstNAddr, result(%d), cause(%d), staInfo)\n",
          suId, suAssocId, result, cause));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctStaCfm(pst, suId(%d), suAssocId(%d), dstNAddr, result(%d), cause(%d), staInfo)\n",
          suId, suAssocId, result, cause));
#endif

   /* jump to specific primitive depending on configured selector */
   /* sb048.102: DFTHA M3UA Support */
   switch (pst->dstEnt)
   {
      /* hi028.201: Added sua DFTHA support */
#ifdef DV
      case ENTIT:
         if (pst->route == RTE_PROTO)
         {
            (*HiUiSctStaCfmMt[pst->selector])(pst, suId, suAssocId, dstNAddr, 
               result, cause, staInfo);
         }
         else
         {
            DvUiSctStaCfm(pst, suId, suAssocId, dstNAddr, result, cause, 
               staInfo);
         }
         break;
#endif /* DV */
#ifdef AH
      case ENTSU:
         if (pst->route == RTE_PROTO)
         {
            (*HiUiSctStaCfmMt[pst->selector])(pst, suId, suAssocId, dstNAddr, 
               result, cause, staInfo);
         }
         else
         {
            AhLiSctStaCfm(pst, suId, suAssocId, dstNAddr, result, cause, 
               staInfo);
         }
         break;
#endif /* AH */

      default:
         (*HiUiSctStaCfmMt[pst->selector])(pst, suId, suAssocId, dstNAddr, 
             result, cause, staInfo);
         break;
   }

   RETVALUE(ROK);
}

/* hi019.201: Included protId parameter in status indication */
#ifdef SCT7
#ifdef ANSI
PUBLIC S16 HiUiSctStaInd
(
 Pst           *pst,       /* post structure */
 SuId          suId,       /* service user SAP identifier */
 UConnId       suAssocId,  /* service user assoc identifier */
 UConnId       spAssocId,  /* service provider assoc identifier */
 CmNetAddr     *dstNAddr,  /* destination network address */
 SctStatus     status,
 SctCause      cause,
 U32           protId,     /* Protocol ID */
 Buffer        *mBuf       /* message buffer */
)
#else
PUBLIC S16 HiUiSctStaInd (pst, suId, suAssocId, spAssocId, dstNAddr,
                           status, cause, protId, mBuf)
Pst            *pst;       /* post structure */
SuId           suId;       /* service user SAP identifier */
UConnId        suAssocId;  /* service user assoc identifier */
UConnId        spAssocId;  /* service provider assoc identifier */
CmNetAddr      *dstNAddr;  /* destination network address */
SctStatus      status;
SctCause       cause;
U32            protId;      /* Protocol ID */
Buffer         *mBuf;       /* message buffer */
#endif
#else /* SCT7 */
#ifdef ANSI
PUBLIC S16 HiUiSctStaInd
(
 Pst           *pst,       /* post structure */
 SuId          suId,       /* service user SAP identifier */
 UConnId       suAssocId,  /* service user assoc identifier */
 UConnId       spAssocId,  /* service provider assoc identifier */
 CmNetAddr     *dstNAddr,  /* destination network address */
 SctStatus     status,
 SctCause      cause,
 Buffer        *mBuf       /* message buffer */
)
#else
PUBLIC S16 HiUiSctStaInd (pst, suId, suAssocId, spAssocId, dstNAddr,
                           status, cause, mBuf)
Pst            *pst;       /* post structure */
SuId           suId;       /* service user SAP identifier */
UConnId        suAssocId;  /* service user assoc identifier */
UConnId        spAssocId;  /* service provider assoc identifier */
CmNetAddr      *dstNAddr;  /* destination network address */
SctStatus      status;
SctCause       cause;
Buffer         *mBuf;       /* message buffer */
#endif
#endif /* SCT7 */
{
   TRC3(HiUiSctStaInd)

#ifdef SCT7
         /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctStaInd(pst, suId(%d), suAssocId(%ld), spAssocId(%ld), dstNAddr, status(%d), cause(%d), protId(%d), mBuf)\n",
          suId, suAssocId, spAssocId, status, cause, protId));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctStaInd(pst, suId(%d), suAssocId(%d), spAssocId(%d), dstNAddr, status(%d), cause(%d), protId(%d), mBuf)\n",
          suId, suAssocId, spAssocId, status, cause, protId));
#endif
#else
         /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctStaInd(pst, suId(%d), suAssocId(%ld), spAssocId(%ld), dstNAddr, status(%d), cause(%d), mBuf)\n",
          suId, suAssocId, spAssocId, status, cause));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctStaInd(pst, suId(%d), suAssocId(%d), spAssocId(%d), dstNAddr, status(%d), cause(%d), mBuf)\n",
          suId, suAssocId, spAssocId, status, cause));
#endif
#endif

   /* jump to specific primitive depending on configured selector */
   /* sb048.102: DFTHA M3UA Support */
   switch (pst->dstEnt)
   {
      /* hi028.201: Added sua DFTHA support */
#ifdef DV
      case ENTIT:
         if (pst->route == RTE_PROTO)
         {
            /* hi019.201: Included protId parameter in status indication */
#ifdef SCT7
            (*HiUiSctStaIndMt[pst->selector])(pst, suId, suAssocId, spAssocId, 
                dstNAddr, status, cause, protId, mBuf);
#else
            (*HiUiSctStaIndMt[pst->selector])(pst, suId, suAssocId, spAssocId, 
                dstNAddr, status, cause, mBuf);
#endif
         }
         else
         {
            /* hi019.201: Included protId parameter in status indication */
#ifdef SCT7
            DvUiSctStaInd (pst, suId, suAssocId, spAssocId, dstNAddr,
                           status, cause, protId, mBuf);
#else
            DvUiSctStaInd (pst, suId, suAssocId, spAssocId, dstNAddr,
                           status, cause, mBuf);
#endif
         }
         break;
#endif /* DV */
#ifdef AH
      case ENTSU:
         if (pst->route == RTE_PROTO)
         {
            /* hi019.201: Included protId parameter in status indication */
#ifdef SCT7
            (*HiUiSctStaIndMt[pst->selector])(pst, suId, suAssocId, spAssocId, 
                dstNAddr, status, cause, protId, mBuf);
#else
            (*HiUiSctStaIndMt[pst->selector])(pst, suId, suAssocId, spAssocId, 
                dstNAddr, status, cause, mBuf);
#endif
         }
         else
         {
            /* hi019.201: Included protId parameter in status indication */
#ifdef SCT7
            AhLiSctStaInd (pst, suId, suAssocId, spAssocId, dstNAddr,
                           status, cause, protId, mBuf);
#else
            AhLiSctStaInd (pst, suId, suAssocId, spAssocId, dstNAddr,
                           status, cause, mBuf);
#endif
         }
#endif /* AH */
         break;

      default:
         /* hi019.201: Included protId parameter in status indication */
#ifdef SCT7
         (*HiUiSctStaIndMt[pst->selector])(pst, suId, suAssocId, spAssocId, 
             dstNAddr, status, cause, protId, mBuf);
#else
         (*HiUiSctStaIndMt[pst->selector])(pst, suId, suAssocId, spAssocId, 
             dstNAddr, status, cause, mBuf);
#endif
         break;
   }

   RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 HiUiSctFlcInd
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
Reason         reason
)
#else
PUBLIC S16 HiUiSctFlcInd(pst, suId, suAssocId, reason)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
Reason         reason;
#endif
{
   TRC3(HiUiSctFlcInd)


         /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctFlcInd(pst, suId(%d), suAssocId(%ld), reason(%d))\n",
          suId, suAssocId, reason));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiSctFlcInd(pst, suId(%d), suAssocId(%d), reason(%d))\n",
          suId, suAssocId, reason));
#endif

   /* jump to specific primitive depending on configured selector */
   /* sb048.102: DFTHA M3UA Support */
   switch (pst->dstEnt)
   {
      /* hi028.201: Added sua DFTHA support */
#ifdef DV
      case ENTIT:
         if (pst->route == RTE_PROTO)
         {
            (*HiUiSctFlcIndMt[pst->selector])(pst, suId, suAssocId, reason);
         }
         else
         {
            DvUiSctFlcInd(pst, suId, suAssocId, reason);
         }
         break;
#endif /* DV */
#ifdef AH
      case ENTSU:
         if (pst->route == RTE_PROTO)
         {
            (*HiUiSctFlcIndMt[pst->selector])(pst, suId, suAssocId, reason);
         }
         else
         {
            AhLiSctFlcInd(pst, suId, suAssocId, reason);
         }
         break;
#endif /* AH */

      default:
         (*HiUiSctFlcIndMt[pst->selector])(pst, suId, suAssocId, reason);
         break;
   }

   RETVALUE(ROK);
}
#endif


/*
*     upper interface functions
*/


/*
*
*       Fun:   Connect Indication
*
*       Desc:  This function indicates the service user of a new
*              TCP client connection.
*
*              "peerAddr" - has the address of the remote entity
*                           which has initiated the client connection.
*
*       Ret:   ROK   - ok
*
*       Notes: Service user will be issued a Connect Indication only
*              when it has initiated a TCP server using
*              HiUiHitServOpenReq() primitive.
*
*       File:  hi_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 HiUiHitConInd
(
Pst *pst,                 /* post stucture */
SpId suId,                /* service user Id */
UConnId servConId,        /* server's connection id */
UConnId spConId,          /* service provider's connection Id */
CmTptAddr *peerAddr       /* peer address */
)
#else
PUBLIC S16 HiUiHitConInd(pst, suId, servConId, spConId, peerAddr)
Pst *pst;                 /* post stucture */
SpId suId;                /* service user Id */
UConnId servConId;        /* server's connection id */
UConnId spConId;          /* service provider's connection Id */
CmTptAddr *peerAddr;      /* peer address */
#endif
{
   TRC3(HiUiHitConInd);

         /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitConInd(pst, suId(%d), servConId(%ld)), spConId(%ld), \
           peerAddr(%p)\n", suId, servConId, spConId, (Ptr)peerAddr));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitConInd(pst, suId(%d), servConId(%d)), spConId(%d), \
           peerAddr(%p)\n", suId, servConId, spConId, (Ptr)peerAddr));
#endif

#ifdef H323_PERF
   TAKE_TIMESTAMP("L/T ConInd sent HI->HC, in HI");
#endif /* H323_PERF */

   switch(pst->dstEnt)
   {
#ifdef DG
      case ENTMG:
         if(pst->route ==  RTE_PROTO)
            (*(HiUiHitConIndMt[pst->selector]))
               (pst, suId, servConId, spConId, peerAddr);
         else
            DgLiHitConInd(pst, suId, servConId, spConId, peerAddr);
         break;
#endif /* DG */

      default:
          (*(HiUiHitConIndMt[pst->selector]))
              (pst, suId, servConId, spConId, peerAddr);
          break;
   }


   RETVALUE(ROK);
} /* end of HiUiHitConInd */


/*
*
*       Fun:   Connect Confirmation
*
*       Desc:  This primitive is used by the TUCL software to
*              indicate to the service user  that the socket
*              (as requested by HiUiHitServOpenReq or by HiUiHitConReq)
*              has been opened, and the UDP data transfer may take
*              place or new TCP client connections may be accepted.
*
*       Ret:   ROK   - ok
*
*       Notes: None
*
*       File:  hi_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 HiUiHitConCfm
(
Pst  *pst,                /* post structure */
SuId  suId,               /* Service User Id */
UConnId  suConId,         /* service user's connection Id */
UConnId  spConId,         /* service provider's connection Id */
CmTptAddr *localAddr      /* local transport address */
)
#else
PUBLIC S16 HiUiHitConCfm(pst, suId, suConId, spConId, localAddr)
Pst  *pst;                /* post structure */
SuId  suId;               /* Service User Id */
UConnId  suConId;         /* service user's connection Id */
UConnId  spConId;         /* service provider's connection Id */
CmTptAddr *localAddr;     /* local transport address */
#endif
{
   TRC3(HiUiHitConCfm);

         /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
    "HiUiHitConCfm(pst, suId(%d), suConId(%ld)), spConId(%ld), \
     localAddr(%p)\n", suId, suConId, spConId, (Ptr)localAddr));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
    "HiUiHitConCfm(pst, suId(%d), suConId(%d)), spConId(%d), \
     localAddr(%p)\n", suId, suConId, spConId, (Ptr)localAddr));
#endif

   switch(pst->dstEnt)
   {
#ifdef DG
      case ENTMG:
         if(pst->route ==  RTE_PROTO)
         (*HiUiHitConCfmMt[pst->selector])(pst, suId,
            suConId, spConId, localAddr);
         else
            DgLiHitConCfm(pst, suId, suConId, spConId, localAddr);
         break;
#endif /* DG */
      default:
         (*HiUiHitConCfmMt[pst->selector])(pst, suId,
            suConId, spConId, localAddr);
         break;
   }

   RETVALUE(ROK);
} /* end of HiUiHitConCfm */

/* hi013.105 :  Added two new HIT primitives. HiUiHitTlsEstReq(), HiUiHitTlsEstCfm().*/
#ifdef HITV2
#ifdef HI_TLS
#ifdef HI_TCP_TLS
/*
*
*       Fun:   TLS establishment Confirmation
*
*       Desc:  This primitive is used by the TUCL software to
*              indicate to the service user that the TLS channel is 
*              established on top of the requested TCP connection in
*              HiUiHitTlsEstReq primitive. Service user can start 
*              sending data to the TLS secured channel 
*              
*       Ret:   ROK   - ok
*
*       Notes: None
*
*       File:  hi_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 HiUiHitTlsEstCfm
(
Pst  *pst,                /* post structure */
SuId  suId,               /* Service User Id */
UConnId  suConId,         /* service user's connection Id */
U8  status,               /* status of TLS establishment */
Reason reason             /* reason for TLS establishment */ 
)
#else
PUBLIC S16 HiUiHitTlsEstCfm(pst, suId, suConId, status, reason)
Pst  *pst;                /* post structure */
SuId  suId;               /* Service User Id */
UConnId  suConId;         /* service user's connection Id */
U8  status;               /* status of TLS establishment */
Reason  reason;           /* reason for TLS establishment */ 
#endif
{
   TRC3(HiUiHitTlsEstCfm);


         /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
    "HiUiHitTlsEstCfm(pst, suId(%d), suConId(%ld)), status(%d), \
     reason(%d)\n", suId, suConId, status, reason));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
    "HiUiHitTlsEstCfm(pst, suId(%d), suConId(%d)), status(%d), \
     reason(%d)\n", suId, suConId, status, reason));
#endif

   (*HiUiHitTlsEstCfmMt[pst->selector])(pst, suId,
   suConId, status, reason);

   RETVALUE(ROK);

} /* end of HiUiHitTlsEstCfm*/

#endif /* HI_TCP_TLS */
#endif /* HI_TLS */
#endif /* HITV2 */


/*
*
*       Fun:   Bind Confirmation
*
*       Desc:  This function indicates to the service user whether the
*              bind operation has been successful or not.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hi_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 HiUiHitBndCfm
(
Pst         *pst,         /* post structure */
SuId        suId,         /* Service User Id */
U8          status        /* status */
)
#else
PUBLIC S16 HiUiHitBndCfm(pst, suId, status)
Pst         *pst;         /* post structure */
SuId        suId;         /* Service User Id */
U8          status;       /* status */
#endif
{
   TRC3(HiUiHitBndCfm);

   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitBndCfm(pst, suId(%d), status(%d)\n", suId, status));

   switch(pst->dstEnt)
   {
#ifdef DG
      case ENTMG:
         if(pst->route ==  RTE_PROTO)
            (*HiUiHitBndCfmMt[pst->selector])(pst, suId, status);
         else
             DgLiHitBndCfm(pst, suId, status);
         break;
#endif /* DG */
      default:
         (*HiUiHitBndCfmMt[pst->selector])(pst, suId, status);
         break;
   }

   RETVALUE(ROK);
} /* end of HiUiHitBndCfm */


/*
*
*       Fun:   Data Indication
*
*       Desc:  This function provides for indicating incoming
*              TCP data on the socket.
*
*       Ret:   ROK   - ok
*
*       Notes: HI layer strips off the TPKT header and delievers
*              the data in a message buffer.
*
*       File:  hi_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 HiUiHitDatInd
(
Pst         *pst,         /* post structure */
SuId        suId,         /* service User Id */
UConnId     suConId,      /* service provider's connection id */
Buffer      *mBuf         /* message buffer */
)
#else
PUBLIC S16 HiUiHitDatInd(pst, suId, suConId, mBuf)
Pst         *pst;         /* post structure */
SuId        suId;         /* service User Id */
UConnId     suConId;      /* service provider's connection id */
Buffer      *mBuf;        /* message buffer */
#endif
{
   TRC3(HiUiHitDatInd);

         /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitDatInd(pst, suId(%d), suConId(%ld), mBuf(%p))\n",
          suId, suConId, (Ptr)mBuf));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitDatInd(pst, suId(%d), suConId(%d), mBuf(%p))\n",
          suId, suConId, (Ptr)mBuf));
#endif

   switch(pst->dstEnt)
   {
#ifdef DG
      case ENTMG:
         if(pst->route ==  RTE_PROTO)
            (*HiUiHitDatIndMt[pst->selector])(pst, suId, suConId, mBuf);
         else
            DgLiHitDatInd(pst, suId, suConId, mBuf);
         break;
#endif /* DG */
      default:
         (*HiUiHitDatIndMt[pst->selector])(pst, suId, suConId, mBuf);
         break;
   }

   RETVALUE(ROK);
} /* end of HiUiHitDatInd */


/*
*
*       Fun:   Unit Data Indication
*
*       Desc:  This function provides for indicating incoming
*              UDP datagrams to the service user.
*
*              "srcAddr" - indicates the address from where the
*                          data was received.
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hi_ptui.c
*
*/
#ifdef LOCAL_INTF
#ifdef ANSI
PUBLIC S16 HiUiHitUDatInd
(
Pst *pst,                 /* post stucture */
SpId suId,                /* service user Id */
UConnId suConId,          /* service user's connection Id */
CmTptAddr *srcAddr,       /* source transport address */
CmTptAddr *remAddr,       /* Remote Address */
CmIpHdrParm *hdrParm,     /* Header Parameters */
CmTptLocalInf *localIf,   /* local intf on which pkt arrived */
Buffer *mBuf              /* message buffer */
)
#else
PUBLIC S16 HiUiHitUDatInd(pst, suId, suConId, srcAddr, remAddr, hdrParm, localIf, mBuf)
Pst *pst;                 /* post stucture */
SpId suId;                /* service user Id */
UConnId suConId;          /* service user's connection Id */
CmTptAddr *srcAddr;       /* source transport address */
CmTptAddr *remAddr;       /* Remote Address */
CmIpHdrParm *hdrParm;     /* Header Parameters */
CmTptLocalInf *localIf;   /* local intf on which pkt arrived */
Buffer *mBuf;             /* message buffer */
#endif /* ANSI */

#else

#ifdef ANSI
PUBLIC S16 HiUiHitUDatInd
(
Pst *pst,                 /* post stucture */
SpId suId,                /* service user Id */
UConnId suConId,          /* service user's connection Id */
CmTptAddr *srcAddr,       /* source transport address */
CmTptAddr *remAddr,       /* Remote Address */
CmIpHdrParm *hdrParm,     /* Header Parameters */
Buffer *mBuf              /* message buffer */
)
#else
PUBLIC S16 HiUiHitUDatInd(pst, suId, suConId, srcAddr, remAddr, hdrParm, mBuf)
Pst *pst;                 /* post stucture */
SpId suId;                /* service user Id */
UConnId suConId;          /* service user's connection Id */
CmTptAddr *srcAddr;       /* source transport address */
CmTptAddr *remAddr;       /* Remote Address */
CmIpHdrParm *hdrParm;     /* Header Parameters */
Buffer *mBuf;             /* message buffer */
#endif /* ANSI */
#endif
{
   TRC3(HiUiHitUDatInd);

         /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
         "HiUiHitUDatInd(pst, suId(%d), suConId(%ld), srcAddr(%p), \
          mBuf(%p))\n", suId, suConId, (Ptr)srcAddr, (Ptr)mBuf));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
         "HiUiHitUDatInd(pst, suId(%d), suConId(%d), srcAddr(%p), \
          mBuf(%p))\n", suId, suConId, (Ptr)srcAddr, (Ptr)mBuf));
#endif

   switch(pst->dstEnt)
   {
#ifdef DG
      case ENTMG:
         if(pst->route ==  RTE_PROTO)
         {
            (*HiUiHitUDatIndMt[pst->selector])(pst, suId, suConId,
               srcAddr, remAddr, hdrParm,
#ifdef LOCAL_INTF
               localIf,
#endif
               mBuf);
         }
         else
            DgLiHitUDatInd(pst, suId, suConId, srcAddr, remAddr, hdrParm,
               mBuf);
         break;
#endif /* DG */
      default:
      {
            (*HiUiHitUDatIndMt[pst->selector])(pst, suId, suConId,
               srcAddr, remAddr, hdrParm,
#ifdef LOCAL_INTF
               localIf,
#endif
               mBuf);
         break;
      }
   }

   RETVALUE(ROK);
} /* end of HiUiHitUDatInd */


/*
*
*       Fun:   Disconnect Indication
*
*       Desc:  This primitive is used by the TCP UDP Convergence Layer
*              to inform the service user that the socket
*              is being closed by TCP UDP Convergence Layer and
*              the associated connection information is being released.
*              This may be issued in error cases  (e.g. socket related
*              errors  like error in opening, binding, connecting to a
*              socket, or miscellaneous errors like errors encountered
*              in hash list operations or error in allocating static
*              memory).
*
*              "reason" - indicates the reason for closure
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hi_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 HiUiHitDiscInd
(
Pst *pst,                 /* post stucture */
SpId suId,                /* service user Id */
U8  choice,               /* choice parameter */
UConnId conId,            /* connection Id */
Reason reason             /* reason */
)
#else
PUBLIC S16 HiUiHitDiscInd(pst, suId, choice, conId, reason)
Pst *pst;                 /* post stucture */
SpId suId;                /* service user Id */
U8  choice;               /* choice parameter */
UConnId conId;            /* connection Id */
Reason reason;            /* reason */
#endif
{
   TRC3(HiUiHitDiscInd);

         /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitDiscInd(pst, suId(%d), choice(%d), conId(%ld),\
           reason(%d))\n", suId, choice, conId, reason));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitDiscInd(pst, suId(%d), choice(%d), conId(%d),\
           reason(%d))\n", suId, choice, conId, reason));
#endif

   switch(pst->dstEnt)
   {
#ifdef DG
      case ENTMG:
         if(pst->route ==  RTE_PROTO)
            (*HiUiHitDiscIndMt[pst->selector])(pst, suId, choice, conId,
                                             reason);
         else
            DgLiHitDiscInd(pst, suId, choice, conId, reason);
         break;
#endif /* DG */
      default:
         (*HiUiHitDiscIndMt[pst->selector])(pst, suId, choice, conId,
                                          reason);
         break;
   }

   RETVALUE(ROK);
} /* end of HiUiHitDiscInd */


/*
*
*       Fun:   Disconnect Confirmation
*
*       Desc:  This primitive is used by the  TCP UDP Convergence
*              Layer to indicate to the service user that
*              Disconnect Request issued by  the service user
*              for the action was successful.
*
*       Ret:   ROK
*
*       Notes: Please note that DiscCfm does not necessarily imply
*              that the connection has  been closed or the connection
*              information has been released by the HI layer (as the
*              socket may have been put into a shutdown state).
*
*       File:  hi_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 HiUiHitDiscCfm
(
Pst *pst,                 /* post stucture */
SpId suId,                /* service user Id */
U8  choice,               /* choice parameter */
UConnId conId,             /* connection Id */
Action action             /* action type */
)
#else
PUBLIC S16 HiUiHitDiscCfm(pst, suId, choice, conId, action)
Pst *pst;                 /* post stucture */
SpId suId;                /* service user Id */
U8  choice;               /* choice parameter */
UConnId conId;             /* connection Id */
Action action;            /* action type */
#endif
{
   TRC3(HiUiHitDiscCfm);

         /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitDiscCfm(pst, suId(%d), choice(%d), conId(%ld), \
          action(%d))\n", suId, choice, conId, action));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitDiscCfm(pst, suId(%d), choice(%d), conId(%d), \
          action(%d))\n", suId, choice, conId, action));
#endif

   switch(pst->dstEnt)
   {
#ifdef DG
      case ENTMG:
         if(pst->route ==  RTE_PROTO)
            (*HiUiHitDiscCfmMt[pst->selector])(pst, suId, choice,
                                               conId, action);
         else
            DgLiHitDiscCfm(pst, suId, choice, conId, action);
         break;
#endif /* DG */
      default:
         (*HiUiHitDiscCfmMt[pst->selector])(pst, suId, choice,
                                            conId, action);
         break;
   }

   RETVALUE(ROK);
} /* end of HiUiHitDiscCfm */


/*
*
*       Fun:   Flow Control Indication
*
*       Desc:  This primitive is used to indicate a shortage of
*              kernel buffers to the HI layer users. The service users
*              are expected not to give any Data Requests to the HI
*              layer while flow control in ON.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hi_ptui.c
*
*/
#ifdef ANSI
PUBLIC S16 HiUiHitFlcInd
(
Pst         *pst,         /* post structure */
SuId        suId,         /* service user Id */
UConnId     suConId,      /* service user connection id */
Reason      reason        /* reason for flow control */
)
#else
PUBLIC S16 HiUiHitFlcInd(pst, suId, suConId, reason)
Pst         *pst;         /* post structure */
SuId        suId;         /* service user Id */
UConnId     suConId;      /* service user connection Id */
Reason      reason;       /* reason for flow control */
#endif
{
   TRC3(HiUiHitFlcInd);

   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitFlcInd(pst, suId(%d), reason(%d))\n",
          suId, reason));

   switch(pst->dstEnt)
   {
#ifdef DG
      case ENTMG:
         if(pst->route ==  RTE_PROTO)
            (*HiUiHitFlcIndMt[pst->selector])(pst, suId, suConId, reason);
         else
            DgLiHitFlcInd(pst, suId, suConId, reason);
         break;
#endif /* DG */
      default:
         (*HiUiHitFlcIndMt[pst->selector])(pst, suId, suConId, reason);
         break;
   }

   RETVALUE(ROK);
} /* end of HiUiHitFlcInd */


/*
*     upper interface portable functions
*/


#ifdef PTHIUIHIT
/*
*
*       Fun:   Portable - Connect Indication
*
*       Desc:  This function indicates the service user of a new
*              TCP client connection.
*
*              "peerAddr" - has the address of the remote entity
*                           which has initiated the client connection.
*
*       Ret:   ROK   - ok
*
*       Notes: Service user will be issued a Connect Indication only
*              when it has initiated a TCP server using
*              HiUiHitServOpenReq() primitive.
*
*       File:  hi_ptui.c
*
*/
#ifdef ANSI
PRIVATE S16 PtUiHitConInd
(
Pst *pst,                 /* post stucture */
SpId suId,                /* service user Id */
UConnId servConId,        /* server's connection id */
UConnId spConId,          /* service provider's connection Id */
CmTptAddr *peerAddr       /* peer address */
)
#else
PRIVATE S16 PtUiHitConInd(pst, suId, servConId, spConId, peerAddr)
Pst *pst;                 /* post stucture */
SpId suId;                /* service user Id */
UConnId servConId;        /* server's connection id */
UConnId spConId;          /* service provider's connection Id */
CmTptAddr *peerAddr;      /* peer address */
#endif
{
   TRC3(PtUiHitConInd);

#if (ERRCLASS & ERRCLS_DEBUG)
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
         "PtUiHitConInd\n"));
#endif /* ERRCLASS */

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(servConId);
   UNUSED(spConId);
   UNUSED(peerAddr);

   RETVALUE(ROK);
} /* end of PtUiHitConInd */


/*
*
*       Fun:   Portable - Connect Confirmation
*
*       Desc:  
*
*       Ret:   ROK   - ok
*
*       Notes: None
*
*       File:  hi_ptui.c
*
*/
#ifdef ANSI
PRIVATE S16 PtUiHitConCfm
(
Pst  *pst,                /* post structure */
SuId  suId,               /* Service User Id */
UConnId  suConId,         /* service user's connection Id */
UConnId  spConId,         /* service provider's connection Id */
CmTptAddr *localAddr      /* local transport address */
)
#else
PRIVATE S16 PtUiHitConCfm(pst, suId, suConId, spConId, localAddr)
Pst  *pst;                /* post structure */
SuId  suId;               /* Service User Id */
UConnId  suConId;         /* service user's connection Id */
UConnId  spConId;         /* service provider's connection Id */
CmTptAddr *localAddr;     /* local transport address */
#endif
{
   TRC3(PtUiHitConCfm);

#if (ERRCLASS & ERRCLS_DEBUG)
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
         "PtUiHitConCfm\n"));
#endif /* ERRCLASS */

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suConId);
   UNUSED(spConId);
   UNUSED(localAddr);

   RETVALUE(ROK);
} /* end of PtUiHitConCfm */


/*
*
*       Fun:   Portable - Bind Confirmation
*
*       Desc:  This function indicates to the service user whether the
*              bind operation has been successful.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hi_ptui.c
*
*/
#ifdef ANSI
PRIVATE S16 PtUiHitBndCfm
(
Pst         *pst,         /* post structure */
SuId        suId,         /* Service User Id */
U8          status        /* status of bind */
)
#else
PRIVATE S16 PtUiHitBndCfm(pst, suId, status)
Pst         *pst;         /* post structure */
SuId        suId;         /* Service User Id */
U8          status;       /* status of bind */
#endif
{
   TRC3(PtUiHitBndCfm);

#if (ERRCLASS & ERRCLS_DEBUG)
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
         "PtUiHitBndCfm\n"));
#endif /* ERRCLASS */

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(status);

   RETVALUE(ROK);
} /* end of PtUiHitBndCfm */


/*
*
*       Fun:   Portable - Data Indication
*
*       Desc:  This function provides for indicating incoming
*              TCP data on the socket.
*
*       Ret:   ROK
*
*       Notes: TCP UDP Convergence Layer strips off the TPKT
*              header and delievers the data in a message buffer.
*
*       File:  hi_ptui.c
*
*/
#ifdef ANSI
PRIVATE S16 PtUiHitDatInd
(
Pst         *pst,         /* post structure */
SuId        suId,         /* service User Id */
UConnId      suConId,     /* service provider's connection id */
Buffer      *mBuf         /* message buffer */
)
#else
PRIVATE S16 PtUiHitDatInd(pst, suId, suConId, mBuf)
Pst         *pst;         /* post structure */
SuId        suId;         /* service User Id */
UConnId     suConId;      /* service provider's connection id */
Buffer      *mBuf;        /* message buffer */
#endif
{
   TRC3(PtUiHitDatInd);

#if (ERRCLASS & ERRCLS_DEBUG)
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
         "PtUiHitDatInd\n"));
#endif /* ERRCLASS */

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suConId);
   UNUSED(mBuf);

   RETVALUE(ROK);
} /* end of PtUiHitDatInd */


/*
*
*       Fun:   Portable - Unit Data Indication
*
*       Desc:  Portable - Unit Data Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hi_ptui.c
*
*/
#ifdef LOCAL_INTF
#ifdef ANSI
PRIVATE S16 PtUiHitUDatInd
(
Pst *pst,                 /* post stucture */
SuId suId,                /* service user Id */
UConnId suConId,          /* service user's connection Id */
CmTptAddr *srcAddr,       /* source transport address */
CmTptAddr *remAddr,       /* Remote Address */
CmIpHdrParm *ipHdrParm,   /* IP header Parameters */
CmTptLocalInf *localIf,   /* local intf on which pkt arrived */
Buffer *mBuf              /* message buffer */
)
#else
PRIVATE S16 PtUiHitUDatInd(pst, suId, suConId, srcAddr, remAddr, ipHdrParm, localIf, mBuf)
Pst *pst;                 /* post stucture */
SuId suId;                /* service user Id */
UConnId suConId;          /* service user's connection Id */
CmTptAddr *srcAddr;       /* source transport address */
CmTptAddr *remAddr;       /* Remote Address */
CmIpHdrParm *ipHdrParm;   /* IP header Parameters */
CmTptLocalInf *localIf;   /* local intf on which pkt arrived */
Buffer *mBuf;             /* message buffer */
#endif
#else
#ifdef ANSI
PRIVATE S16 PtUiHitUDatInd
(
Pst *pst,                 /* post stucture */
SuId suId,                /* service user Id */
UConnId suConId,          /* service user's connection Id */
CmTptAddr *srcAddr,       /* source transport address */
CmTptAddr *remAddr,       /* Remote Address */
CmIpHdrParm *ipHdrParm,   /* IP header Parameters */
Buffer *mBuf              /* message buffer */
)
#else
PRIVATE S16 PtUiHitUDatInd(pst, suId, suConId, srcAddr, remAddr, ipHdrParm, mBuf)
Pst *pst;                 /* post stucture */
SuId suId;                /* service user Id */
UConnId suConId;          /* service user's connection Id */
CmTptAddr *srcAddr;       /* source transport address */
CmTptAddr *remAddr;       /* Remote Address */
CmIpHdrParm *ipHdrParm;   /* IP header Parameters */
Buffer *mBuf;             /* message buffer */
#endif
#endif
{
   TRC3(PtUiHitUDatInd);

#if (ERRCLASS & ERRCLS_DEBUG)
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
         "PtUiHitUDatInd\n"));
#endif /* ERRCLASS */

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suConId);
   UNUSED(srcAddr);
   UNUSED(remAddr);
   UNUSED(ipHdrParm);
#ifdef LOCAL_INTF
   UNUSED(localIf);
#endif
   UNUSED(mBuf);

   RETVALUE(ROK);
} /* end of PtUiHitUDatInd */


/*
*
*       Fun:   Portable - Disconnect Indication
*
*       Desc:  Portable - Disconnect Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hi_ptui.c
*
*/
#ifdef ANSI
PRIVATE S16 PtUiHitDiscInd
(
Pst *pst,                 /* post stucture */
SpId suId,                /* service user Id */
U8  choice,               /* choice parameter */
UConnId conId,            /* connection Id */
Reason reason             /* reason */
)
#else
PRIVATE S16 PtUiHitDiscInd(pst, suId, choice, conId, reason)
Pst *pst;                 /* post stucture */
SpId suId;                /* service user Id */
U8  choice;               /* choice parameter */
UConnId conId;            /* connection Id */
Reason reason;            /* reason */
#endif
{
   TRC3(PtUiHitDiscInd);

#if (ERRCLASS & ERRCLS_DEBUG)
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
         "PtUiHitDiscInd\n"));
#endif /* ERRCLASS */

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(choice);
   UNUSED(conId);
   UNUSED(reason);

   RETVALUE(ROK);
} /* end of PtUiHitDiscInd */


/*
*
*       Fun:   Portable - Disconnect Confirmation
*
*       Desc:  Portable - Disconnect Confirmation
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hi_ptui.c
*
*/
#ifdef ANSI
PRIVATE S16 PtUiHitDiscCfm
(
Pst *pst,                 /* post stucture */
SpId suId,                /* service user Id */
U8  choice,               /* choice parameter */
UConnId conId,             /* connection Id */
Action action             /* action type */
)
#else
PRIVATE S16 PtUiHitDiscCfm(pst, suId, choice, conId, action)
Pst *pst;                 /* post stucture */
SpId suId;                /* service user Id */
U8  choice;               /* choice parameter */
UConnId conId;             /* connection Id */
Action action;            /* action type */
#endif
{
   TRC3(PtUiHitDiscCfm);

#if (ERRCLASS & ERRCLS_DEBUG)
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
         "PtUiHitDiscCfm\n"));
#endif /* ERRCLASS */

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(choice);
   UNUSED(conId);
   UNUSED(action);

   RETVALUE(ROK);
} /* end of PtUiHitDiscCfm */


/*
*
*       Fun:   Portable - Flow Control Indication
*
*       Desc:  Portable - Flow Control Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hi_ptui.c
*
*/
#ifdef ANSI
PRIVATE S16 PtUiHitFlcInd
(
Pst         *pst,         /* post structure */
SuId        suId,         /* Service User Id */
UConnId     suConId,      /* Service User Connection Id */
Reason      reason        /* reason for flow control */
)
#else
PRIVATE S16 PtUiHitFlcInd(pst, suId, suConId, reason)
Pst         *pst;         /* post structure */
SuId        suId;         /* Service User Id */
UConnId     suConId;      /* Service User Connection Id */
Reason      reason;       /* reason for flow control */
#endif
{
   TRC3(PtUiHitFlcInd);

#if (ERRCLASS & ERRCLS_DEBUG)
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
         "PtUiHitFlcInd\n"));
#endif /* ERRCLASS */

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suConId);
   UNUSED(reason);

   RETVALUE(ROK);
} /* end of PtUiHitFlcInd */

/* hi013.105 :  Added two new HIT primitives. HiUiHitTlsEstReq(), HiUiHitTlsEstCfm().*/
#ifdef HITV2
#ifdef HI_TLS
#ifdef HI_TCP_TLS
/*
*
*       Fun:   Portable - Tls establishment confirm
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  hi_ptui.c
*
*/
#ifdef ANSI
PRIVATE S16 PtUiHitTlsEstCfm 
(
Pst *pst,                 /* post stucture */
SpId suId,                /* service user Id */
UConnId suConId,          /* connection Id */
U8 status,                /* status- positive or negative */
Reason reason             /* reason for failure */
)
#else
PRIVATE S16 PtUiHitTlsEstCfm(pst, suId, suConId, status, reason)
Pst *pst;                 /* post stucture */
SpId suId;                /* service user Id */
UConnId suConId;          /* connection Id */
U8 status;                /* status- positive or negative */
Reason reason;            /* reason for failure */
#endif
{
   TRC3(PtUiHitTlsEstCfm);

#if (ERRCLASS & ERRCLS_DEBUG)
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
         "PtUiHitTlsEstCfm\n"));
#endif /* ERRCLASS */

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suConId);
   UNUSED(status);
   UNUSED(reason);

   RETVALUE(ROK);
} /* end of PtUiHitTlsEstCfm */
#endif /*HI_TCP_TLS*/
#endif /*HI_TLS*/
#endif /*HITV2*/
#endif /* PTHIUIHIT */

#ifdef HI_LKSCTP

/*
*     upper interface portable functions
*/

#ifdef PTHIUISCT


#ifdef ANSI
PUBLIC S16 PtUiSctBndCfm
(
Pst           *pst,
SuId           suId,
SctResult      result
)
#else
PUBLIC S16 PtUiSctBndCfm(pst, suId, result)
Pst           *pst;
SuId           suId;
SctResult      result;
#endif
{
   TRC3(PtUiSctBndCfm)

#if (ERRCLASS & ERRCLS_DEBUG)
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
              "PtUiSctBndCfm: Failed\n"));
#endif /* ERRCLASS */

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(result);

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 PtUiSctEndpOpenCfm
(
Pst           *pst,
SuId           suId,
UConnId        suEndpId,
UConnId        spEndpId,
SctResult      result,
SctCause       cause
)
#else
PUBLIC S16 PtUiSctEndpOpenCfm(pst, suId, suEndpId, spEndpId, result, cause)
Pst           *pst;
SuId           suId;
UConnId        suEndpId;
UConnId        spEndpId;
SctResult      result;
SctCause       cause;
#endif
{
   TRC3(PtUiSctEndpOpenCfm)

#if (ERRCLASS & ERRCLS_DEBUG)
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
              "PtUiSctEndpOpenCfm: Failed\n"));
#endif /* ERRCLASS */

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suEndpId);
   UNUSED(spEndpId);
   UNUSED(result);
   UNUSED(cause);

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 PtUiSctEndpCloseCfm
(
Pst           *pst,
SuId           suId,
UConnId        suEndpId,
SctResult      result,
SctCause       cause
)
#else
PUBLIC S16 PtUiSctEndpCloseCfm(pst, suId, suEndpId, result, cause)
Pst           *pst;
SuId           suId;
UConnId        suEndpId;
SctResult      result;
SctCause       cause;
#endif
{
   TRC3(PtUiSctEndpCloseCfm)

#if (ERRCLASS & ERRCLS_DEBUG)
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
              "PtUiSctEndpCloseCfm: Failed\n"));
#endif /* ERRCLASS */

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suEndpId);
   UNUSED(result);
   UNUSED(cause);

   RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 PtUiSctAssocInd
(
Pst               *pst,
SuId               suId,
UConnId            suEndpId,
SctAssocIndParams *assocParams,
Buffer            *vsInfo
)
#else
PUBLIC S16 PtUiSctAssocInd(pst, suId, suEndpId, assocParams, vsInfo)
Pst               *pst;
SuId               suId;
UConnId            suEndpId;
SctAssocIndParams *assocParams;
Buffer            *vsInfo;
#endif
{
   TRC3(PtUiSctAssocInd)


#if (ERRCLASS & ERRCLS_DEBUG)
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
              "PtUiSctAssocInd: Failed\n"));
#endif /* ERRCLASS */

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suEndpId);
   UNUSED(assocParams);
   UNUSED(vsInfo);

   RETVALUE(ROK);
}



/* sb016.102 - Include in-stream parameter here */
#ifdef SCT2
#ifdef ANSI
PUBLIC S16 PtUiSctAssocCfm
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
UConnId        spAssocId,
SctNetAddrLst *dstNAddrLst,
SctPort        dstPort,
SctStrmId      inStrms,
SctStrmId      outStrms,
Buffer        *vsInfo
)
#else
PUBLIC S16 PtUiSctAssocCfm(pst, suId, suAssocId, spAssocId, dstNAddrLst, 
                           dstPort, inStrms, outStrms, vsInfo)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
UConnId        spAssocId;
SctNetAddrLst *dstNAddrLst;
SctPort        dstPort;
SctStrmId      inStrms;
SctStrmId      outStrms;
Buffer        *vsInfo;
#endif /* ANSI */
#else
#ifdef ANSI
PUBLIC S16 PtUiSctAssocCfm
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
UConnId        spAssocId,
SctNetAddrLst *dstNAddrLst,
SctPort        dstPort,
SctStrmId      outStrms,
Buffer        *vsInfo
)
#else
PUBLIC S16 PtUiSctAssocCfm(pst, suId, suAssocId, spAssocId, dstNAddrLst,
                           dstPort, outStrms, vsInfo)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
UConnId        spAssocId;
SctNetAddrLst *dstNAddrLst;
SctPort        dstPort;
SctStrmId      outStrms;
Buffer        *vsInfo;
#endif /* ANSI */
#endif /* SCT2 */
{
   TRC3(PtUiSctAssocCfm)

#if (ERRCLASS & ERRCLS_DEBUG)
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
              "PtUiSctAssocCfm: Failed\n"));
#endif /* ERRCLASS */

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suAssocId);
   UNUSED(spAssocId);
   UNUSED(dstNAddrLst);
   UNUSED(dstPort);
/* sb016.102 - Include in-stream parameter here */
#ifdef SCT2
   UNUSED(inStrms);
#endif /* SCT2 */
   UNUSED(outStrms);
   UNUSED(vsInfo);

   RETVALUE(ROK);
}




#ifdef ANSI
PUBLIC S16 PtUiSctTermInd
(
Pst           *pst,
SuId           suId,
UConnId        assocId,
U8             assocIdType,
SctStatus      status,
SctCause       cause,
SctRtrvInfo   *rtrvInfo
)
#else
PUBLIC S16 PtUiSctTermInd(pst, suId, assocId, assocIdType, status, cause,
                          rtrvInfo)
Pst           *pst;
SuId           suId;
UConnId        assocId;
U8             assocIdType;
SctStatus      status;
SctCause       cause;
SctRtrvInfo   *rtrvInfo;
#endif
{
   TRC3(PtUiSctTermInd)

#if (ERRCLASS & ERRCLS_DEBUG)
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
              "PtUiSctTermInd: Failed\n"));
#endif /* ERRCLASS */

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(assocId);
   UNUSED(assocIdType);
   UNUSED(status);
   UNUSED(cause);
   UNUSED(rtrvInfo);

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 PtUiSctTermCfm
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
SctResult      result,
SctCause       cause
)
#else
PUBLIC S16 PtUiSctTermCfm(pst, suId, suAssocId, result, cause)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
SctResult      result;
SctCause       cause;
#endif
{
   TRC3(PtUiSctTermCfm)

#if (ERRCLASS & ERRCLS_DEBUG)
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
              "PtUiSctTermCfm: Failed\n"));
#endif /* ERRCLASS */

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suAssocId);
   UNUSED(result);
   UNUSED(cause);

   RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 PtUiSctSetPriCfm
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
SctResult      result,
SctCause       cause
)
#else
PUBLIC S16 PtUiSctSetPriCfm(pst, suId, suAssocId, result, cause)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
SctResult      result;
SctCause       cause;
#endif
{
   TRC3(PtUiSctSetPriCfm)

#if (ERRCLASS & ERRCLS_DEBUG)
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
              "PtUiSctSetPriCfm: Failed\n"));
#endif /* ERRCLASS */

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suAssocId);
   UNUSED(result);
   UNUSED(cause);

   RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 PtUiSctHBeatCfm
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
CmNetAddr     *dstNAddr,
SctStatus      status,
SctResult      result,
SctCause       cause
)
#else
PUBLIC S16 PtUiSctHBeatCfm(pst, suId, suAssocId, dstNAddr, status, result,
                           cause)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
CmNetAddr     *dstNAddr;
SctStatus      status;
SctResult      result;
SctCause       cause;
#endif
{
   TRC3(PtUiSctHBeatCfm)

#if (ERRCLASS & ERRCLS_DEBUG)
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
              "PtUiSctHBeatCfm: Failed\n"));
#endif /* ERRCLASS */

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suAssocId);
   UNUSED(dstNAddr);
   UNUSED(status);
   UNUSED(result);
   UNUSED(cause);

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 PtUiSctDatInd
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
SctStrmId      strmId,
SctDatIndType *indType,
U32            protId,
Buffer        *mBuf
)
#else
PUBLIC S16 PtUiSctDatInd(pst, suId, suAssocId, strmId, indType, protId, mBuf)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
SctStrmId      strmId;
SctDatIndType *indType;
U32            protId;
Buffer        *mBuf;
#endif
{
   TRC3(PtUiSctDatInd)

#if (ERRCLASS & ERRCLS_DEBUG)
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
              "PtUiSctDatInd: Failed\n"));
#endif /* ERRCLASS */

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suAssocId);
   UNUSED(strmId);
   UNUSED(indType);
   UNUSED(protId);
   UNUSED(mBuf);

   RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 PtUiSctStaCfm
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
CmNetAddr     *dstNAddr,
SctResult      result,
SctCause       cause,
SctStaInfo    *staInfo
)
#else
PUBLIC S16 PtUiSctStaCfm(pst, suId, suAssocId, dstNAddr, result,
                         cause, staInfo)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
CmNetAddr     *dstNAddr;
SctResult      result;
SctCause       cause;
SctStaInfo    *staInfo;
#endif
{
   TRC3(PtUiSctStaCfm)

#if (ERRCLASS & ERRCLS_DEBUG)
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
              "PtUiSctStaCfm: Failed\n"));
#endif /* ERRCLASS */

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suAssocId);
   UNUSED(dstNAddr);
   UNUSED(result);
   UNUSED(cause);
   UNUSED(staInfo);

   RETVALUE(ROK);
}


/* hi019.201: Included protId parameter in status indication */
#ifdef SCT7
#ifdef ANSI
PUBLIC S16 PtUiSctStaInd
(
 Pst           *pst,
 SuId           suId,
 UConnId        suAssocId,
 UConnId        spAssocId,
 CmNetAddr     *dstNAddr,
 SctStatus      status,
 SctCause       cause,
 U32            protId,
 Buffer        *mBuf
 )
#else
PUBLIC S16 PtUiSctStaInd(pst, suId, suAssocId, spAssocId, dstNAddr, status,
      cause, protId,mBuf)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
UConnId        spAssocId;
CmNetAddr     *dstNAddr;
SctStatus      status;
SctCause       cause;
U32            protId;
Buffer        *mBuf;
#endif
#else /* SCT7 */
#ifdef ANSI
PUBLIC S16 PtUiSctStaInd
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
UConnId        spAssocId,
CmNetAddr     *dstNAddr,
SctStatus      status,
SctCause       cause,
Buffer        *mBuf
)
#else
PUBLIC S16 PtUiSctStaInd(pst, suId, suAssocId, spAssocId, dstNAddr, status,
                         cause, mBuf)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
UConnId        spAssocId;
CmNetAddr     *dstNAddr;
SctStatus      status;
SctCause       cause;
Buffer        *mBuf;
#endif
#endif /* SCT7 */
{
   TRC3(PtUiSctStaInd)

#if (ERRCLASS & ERRCLS_DEBUG)
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
              "PtUiSctStaInd: Failed\n"));
#endif /* ERRCLASS */

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suAssocId);
   UNUSED(spAssocId);
   UNUSED(dstNAddr);
   UNUSED(status);
   UNUSED(cause);
   /* hi019.201: Included protId parameter in status indication */
#ifdef SCT7
   UNUSED(protId);
#endif
   UNUSED(mBuf);

   RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 PtUiSctFlcInd
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
Reason         reason
)
#else
PUBLIC S16 PtUiSctFlcInd(pst, suId, suAssocId, reason)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
Reason         reason;
#endif
{
   TRC3(PtUiSctFlcInd)

#if (ERRCLASS & ERRCLS_DEBUG)
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
              "PtUiSctFlcInd: Failed\n"));
#endif /* ERRCLASS */

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suAssocId);
   UNUSED(reason);

   RETVALUE(ROK);
}

#endif /* PTHIUISCT */
#endif


/********************************************************************30**

         End of file:     hi_ptui.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Tue Aug 11 10:26:30 2015

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
----------- -------- ---- -----------------------------------------------
1.1         ---      asa  1. initial release.
1.1+        hi002.11 asa  1. changes for RTP, removed HrLiHitFlcInd,
                             HrLiHitConInd and HrLiHitDatInd
                          2. added a new user GTP.
1.1+        hi004.11 cvp  1. added a new user MGCP. 
/main/2     ---      cvp  1. added a new user Annex G.
                          2. changed the copyright header.
             /main/4 sb   1. changes for Raw Socket interface in 
                             primitives HiUiHitUDatInd.
                          2. added a new user SCTP.
                     cvp  3. added a new user MPLS.
                          4. changes for sht interface.
/main/4+    hi001.13 cvp  1. changes for SB, removed SbLiHitFlcInd,
                             SbLiHitConInd and SbLiHitDatInd
/main/4+    hi003.13 cvp  1. added a new user - Dummy layer.
/main/4+    hi006.13 asa  1. added a new user - SIP layer.
/main/4     ---      cvp  1. changed the copyright header.
/main/4+    hi008.104 mmh 1. Added code required for distribution
                             of primitives from TUCL towards GCP
                             through LDF-GCP. The extern definition
                             for the LDF-GCP functions will be added
                             in hit.x to be released with GCP 1.3
/main/4+    hi009.104 mmh 1. added a new argument localIf in functions
                             PtUiHitUDatInd, HiUiHitDatInd when LOCAL_INTF
                             flag is defined during compile time.
/main/4+    hi020.104 rs  1. Added SV as another user.
/main/4+    hi021.104 rs  1. Removing Warnings.
/main/5      ---       kp  1. Updated for release 1.5.
/main/5     hi009.105 ss  1. Added FP as another user.
/main/5     hi012.105 svp  1. Added AQ as another user.
/main/5+    hi013.105 svp  1. Added two new HIT primitives.
                              HiUiHitTlsEstReq(), HiUiHitTlsEstCfm().
/main/5+    hi015.105 svp  1. For SIP MT, all primitives except DAT and UDAT
                              indications are made to loosely coupled. 
/main/6      ---       hs   1. Updated for release of 2.1
/main/6+    hi007.201  hsingh   1. Added SZ as another user.
/main/6+    hi013.201  pchebolu  1. Added EG [EGTP] as another user.
/main/6+    hi019.201  rcs  1. Included protId parameter in status indication. 
                            2. Added C++ pre-processor protection to remove C++ warnings.
/main/6+    hi020.201  mm    1. Update for X2AP release 1.1.
/main/6+    hi021.201  rsr   1. Update for Iuh release
                       rcs   2. Moved the cpluscplus protection outside HI_LKSCTP flag.
/main/6+    hi025.201  rss   1. Define the macro PTHIUISCT 
/main/6+    hi028.201 ragrawal 1.  Added support for sua DFTHA.
/main/6    hi029.201 ragrawal 1. Fix for 64 bit compilation warnings.
*********************************************************************91*/

