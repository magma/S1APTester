

/********************************************************************20**

     Name:     SCTP Layer

     Type:     C source file

     Desc:     C source code for SB layer portable Upper Interface

     File:     sb_ptui.c

     Sid:      sb_ptui.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:18 2015

     Prg:      wvdl, bk

*********************************************************************21*/


/* header include files (.h) */

/* header/extern include files (.x) */



/*

The following functions are provided in this file:


It should be noted that not all of these functions may be required
by a particular network layer service user.


*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm_hash.h"       /* common hashing */
#include "cm_llist.h"      /* common linked list */
#include "lsb.h"           /* layer management SB */
#include "cm_err.h"        /* common error */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"        /* common transport defines */
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
#include "cm_dns.x"        /* common transport defines */
#include "cm5.x"           /* common timer */
#ifdef SB_FTHA
#include "sht.x"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "hit.x"           /* hit interface */
#include "sct.x"           /* sct interface */
#include "lsb.x"           /* layer management SCTP */
#include "sb_mtu.x"
#include "sb.x"            /* SCTP typedefs */



 /* sb003.11 - changed due to added users */
/* local defines */
/* sb048.102: GCP added as new SCTP user */
/* sb052.102: NBAP (ENTIB), M1UA (ENTMZ) added as new SCTP user. */
/* sb065.102: SIP added as new SCTP user */
/* sb079.102: Diameter added as new SCTP user*/
/* sb003.103: M2PA (ENTMX) added as a new SCTP user */
/* sb016.103: S1AP added as new SCTP user*/
/* sb025.103: X2AP added as new SCTP user*/
/* sb027.103: Iuh added as new SCTP user */
#define MAXSBUI 15          /* max SB Layer upper users */

/* sb048.102: Changes to incorporate GCP */
/* sb052.102: NBAP (ENTIB), M1UA (ENTMZ) added as new SCTP user. */
/* sb065.102: SIP added as new SCTP user */
/* sb079.102: Diameter added as new SCTP user*/
/* sb003.103: M2PA (ENTMX) added as a new SCTP user */
/* sb016.103: S1AP added as new SCTP user*/
/* sb022.103: C++ compilation error fix */
/* sb025.103: X2AP added as new SCTP user*/
/* sb027.103: Iuh added as new SCTP user */
#if ( (!defined(LCSBUISCT)) || !(defined(IT)) || !(defined(SU)) || !(defined(MW)) || (!defined(MG)) || (!defined(DM)) || (!defined(IB)) || (!defined(MZ)) || (!defined(SO)) || (!defined(AQ)) || (!defined(MX)) || (!defined(SZ)) || (!defined(CZ)) || (!defined(HM)))
#define PTSBUISCT
#endif

/* local typedefs */

/* local externs */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef PTSBUISCT

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
/* sb024.103: Included protId parameter in status indication */
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
#endif /* SCT7 */
PRIVATE S16 PtUiSctFlcInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          Reason         reason));


#endif /* PTSBUISCT */

#ifdef __cplusplus
}
#endif /* __cplusplus */


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

  The dispatching is performed by the configurable variable: selector.
  The selector is configured on a per SAP basis.

  The selectors are:

  0 - loosely coupled (#define LCSBUISCT)
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
  10 - Diameter       (#define AQ)
  11 - M2PA           (#define MX)
  12 - S1AP           (#define SZ)
  13 - X2AP           (#defined CZ)
 sb027.103: Iuh added as new SCTP user
  14 - Iuh            (#defined HM)

*/



PRIVATE SctBndCfm SbUiSctBndCfmMt[MAXSBUI] =
{
#ifdef LCSBUISCT
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
/* sb003.103: M2PA (ENTMX) added as a new SCTP user */
#ifdef MX 
   MxLiSctBndCfm,         /* 11 - tightly coupled, M2PA */
#else
   PtUiSctBndCfm,         /* 11 - tightly coupled, portable */
#endif

/* sb016.103 : S1AP added as new SCTP user */
#ifdef SZ
   SzLiSctBndCfm,         /* 12 - tightly coupled, S1AP */
#else
   PtUiSctBndCfm,         /* 12 - tightly coupled, portable */
#endif
/* sb025.103: X2AP added as new SCTP user*/
#ifdef CZ
   CzLiSctBndCfm,         /* 13 - tightly coupled, Diameter */
#else
   PtUiSctBndCfm,         /* 13 - tightly coupled, portable */
#endif
/* sb027.103: Iuh added as new SCTP user */
#ifdef HM
   HmLiSctBndCfm,         /* 14 - tightly coupled, Iuh */      
#else
   PtUiSctBndCfm,         /* 14 - tightly coupled, portable */
#endif /* HM */
};


PRIVATE SctEndpOpenCfm SbUiSctEndpOpenCfmMt[MAXSBUI] =
{
#ifdef LCSBUISCT
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
/* sb003.103: M2PA (ENTMX) added as a new SCTP user */
#ifdef MX 
   MxLiSctEndpOpenCfm,         /* 11 - tightly coupled, M2PA */
#else
   PtUiSctEndpOpenCfm,         /* 11 - tightly coupled, portable */
#endif
/*sb016.103: S1AP added as new SCTP user*/
#ifdef SZ
   SzLiSctEndpOpenCfm,         /* 12 - tightly coupled, S1AP */
#else
   PtUiSctEndpOpenCfm,         /* 12 - tightly coupled, portable */
#endif
/* sb025.103: X2AP added as new SCTP user*/
#ifdef CZ
   CzLiSctEndpOpenCfm,         /* 13 - tightly coupled, S1AP */
#else
   PtUiSctEndpOpenCfm,         /* 13 - tightly coupled, portable */
#endif
/* sb027.103: Iuh added as new SCTP user */
#ifdef HM                     /* 14 - tightly coupled, Iuh */
   HmLiSctEndpOpenCfm,         
#else
   PtUiSctEndpOpenCfm,        /* 14 - tightly coupled, portable */
#endif /* HM */
};

PRIVATE SctEndpCloseCfm SbUiSctEndpCloseCfmMt[MAXSBUI] =
{
#ifdef LCSBUISCT
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
/* sb003.103: M2PA (ENTMX) added as a new SCTP user */
#ifdef MX 
   MxLiSctEndpCloseCfm,         /* 11 - tightly coupled, M2PA */
#else
   PtUiSctEndpCloseCfm,         /* 11 - tightly coupled, portable */
#endif
/*sb016.103: S1AP added as new SCTP  user*/
#ifdef SZ
   SzLiSctEndpCloseCfm,         /* 12 - tightly coupled, S1AP */
#else
   PtUiSctEndpCloseCfm,         /* 12 - tightly coupled, portable */
#endif
/* sb025.103: X2AP added as new SCTP user*/
#ifdef CZ
   CzLiSctEndpCloseCfm,         /* 13 - tightly coupled, Diameter */
#else
   PtUiSctEndpCloseCfm,         /* 13 - tightly coupled, portable */
#endif
/* sb027.103: Iuh added as new SCTP user */
#ifdef HM
   HmLiSctEndpCloseCfm,         /* 14 - tightly coupled, Iuh */
#else
   PtUiSctEndpCloseCfm,         /* 14 - tightly coupled, portable */
#endif /* HM */
};

PRIVATE SctAssocInd SbUiSctAssocIndMt[MAXSBUI] =
{
#ifdef LCSBUISCT
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
/* sb003.103: M2PA (ENTMX) added as a new SCTP user */
#ifdef MX 
   MxLiSctAssocInd,         /* 11 - tightly coupled, M2PA*/
#else
   PtUiSctAssocInd,         /* 11 - tightly coupled, portable */
#endif
/*sb016.103: S1AP as new SCTP user*/
#ifdef SZ
   SzLiSctAssocInd,         /* 12 - tightly coupled, S1AP */
#else
   PtUiSctAssocInd,         /* 12 - tightly coupled, portable */
#endif
/* sb025.103: X2AP added as new SCTP user*/
#ifdef CZ
   CzLiSctAssocInd,         /* 13 - tightly coupled, Diameter */
#else
   PtUiSctAssocInd,         /* 13 - tightly coupled, portable */
#endif
/* sb027.103: Iuh added as new SCTP user */
#ifdef HM
   HmLiSctAssocInd,         /* 14 - tightly coupled, Iuh */
#else
   PtUiSctAssocInd,         /* 14 - tightly coupled, portable */
#endif /* HM */
};

PRIVATE SctAssocCfm SbUiSctAssocCfmMt[MAXSBUI] =
{
#ifdef LCSBUISCT
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
/* sb003.103: M2PA (ENTMX) added as a new SCTP user */
#ifdef MX 
   MxLiSctAssocCfm,         /* 11 - tightly coupled, M2PA */
#else
   PtUiSctAssocCfm,         /* 11 - tightly coupled, portable */
#endif
/*sb016.103: S1AP as new SCTP user*/
#ifdef SZ
   SzLiSctAssocCfm,         /* 12 - tightly coupled, S1AP */
#else
   PtUiSctAssocCfm,         /* 12 - tightly coupled, portable */
#endif
/* sb025.103: X2AP added as new SCTP user*/
#ifdef CZ
   CzLiSctAssocCfm,         /* 13 - tightly coupled, Diameter */
#else
   PtUiSctAssocCfm,         /* 13 - tightly coupled, portable */
#endif
/* sb027.103: Iuh added as new SCTP user */
#if (defined(HM) && !defined(HM_HNBGW))
   HmLiSctAssocCfm,         /* 14 - tightly coupled, Iuh */
#else
   PtUiSctAssocCfm,         /* 14 - tightly coupled, portable */
#endif /* HM */
};

PRIVATE SctTermInd SbUiSctTermIndMt[MAXSBUI] =
{
#ifdef LCSBUISCT
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
/* sb003.103: M2PA (ENTMX) added as a new SCTP user */
#ifdef MX 
   MxLiSctTermInd,         /* 11 - tightly coupled, M2PA */
#else
   PtUiSctTermInd,         /* 11 - tightly coupled, portable */
#endif
/*sb016.103: S1AP added as new SCTP user*/
#ifdef SZ
   SzLiSctTermInd,         /* 12 - tightly coupled, S1AP */
#else
   PtUiSctTermInd,         /* 12 - tightly coupled, portable */
#endif
/* sb025.103: X2AP added as new SCTP user*/
#ifdef CZ
   CzLiSctTermInd,         /* 13 - tightly coupled, Diameter */
#else
   PtUiSctTermInd,         /* 13 - tightly coupled, portable */
#endif
/* sb027.103: Iuh added as new SCTP user */
#ifdef HM
   HmLiSctTermInd,        /* 14 - tightly coupled, Iuh */         
#else
   PtUiSctTermInd,        /* 14 - tightly coupled, portable */
#endif /* HM */
};

PRIVATE SctTermCfm SbUiSctTermCfmMt[MAXSBUI] =
{
#ifdef LCSBUISCT
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
/* sb003.103: M2PA (ENTMX) added as a new SCTP user */
#ifdef MX 
   MxLiSctTermCfm,         /* 11 - tightly coupled, Diameter */
#else
   PtUiSctTermCfm,         /* 11 - tightly coupled, portable */
#endif
/*sb016.103: S1AP added as new SCTP user*/
#ifdef SZ
   SzLiSctTermCfm,         /* 12 - tightly coupled, S1AP */
#else
   PtUiSctTermCfm,         /* 12 - tightly coupled, portable */
#endif
/* sb025.103: X2AP added as new SCTP user*/
#ifdef CZ
   CzLiSctTermCfm,         /* 13 - tightly coupled, Diameter */
#else
   PtUiSctTermCfm,         /* 13 - tightly coupled, portable */
#endif
/* sb027.103: Iuh added as new SCTP user */
#ifdef HM
   HmLiSctTermCfm,         /* 14 - tightly coupled, Iuh */
#else
   PtUiSctTermCfm,         /* 14 - tightly coupled, portable */
#endif /* HM */
};

PRIVATE SctSetPriCfm SbUiSctSetPriCfmMt[MAXSBUI] =
{
#ifdef LCSBUISCT
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
/* sb003.103: M2PA (ENTMX) added as a new SCTP user */
#ifdef MX 
   MxLiSctSetPriCfm,         /* 11 - tightly coupled, M2PA */
#else
   PtUiSctSetPriCfm,         /* 11 - tightly coupled, portable */
#endif
/*sb016.103: S1AP added as new SCTP user*/
/* sb025.103: combine SZ and SZ_PHASE2 flags in one ifdef */
/* sb026.103: Change || condition to && */
#if (defined(SZ) && defined (SZ_PHASE2))
   SzLiSctSetPriCfm,         /* 12 - tightly coupled, S1AP */
#else
   PtUiSctSetPriCfm,         /* 12 - tightly coupled, portable */
#endif /* SZ */
/* sb025.103: X2AP added as new SCTP user*/
#ifdef CZ
   CzLiSctSetPriCfm,         /* 13 - tightly coupled, Diameter */
#else
   PtUiSctSetPriCfm,         /* 13 - tightly coupled, portable */
#endif
};

PRIVATE SctHBeatCfm SbUiSctHBeatCfmMt[MAXSBUI] =
{
#ifdef LCSBUISCT
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
/* sb003.103: M2PA (ENTMX) added as a new SCTP user */
#ifdef MX 
   MxLiSctHBeatCfm,         /* 11 - tightly coupled, M2PA */
#else
   PtUiSctHBeatCfm,         /* 11 - tightly coupled, portable */
#endif
/*sb016.103: S1AP added as new SCTP user*/
/* sb025.103: combine SZ and SZ_PHASE2 flags in one ifdef */
/* sb026.103: Change || condition to && */
#if (defined (SZ) && defined (SZ_PHASE2))
   SzLiSctHBeatCfm,         /* 12 - tightly coupled, S1AP */
#else
   PtUiSctHBeatCfm,         /* 12 - tightly coupled, portable */
#endif /* SZ */
/* sb025.103: X2AP added as new SCTP user*/
#ifdef CZ
   CzLiSctHBeatCfm,         /* 13 - tightly coupled, Diameter */
#else
   PtUiSctHBeatCfm,         /* 13 - tightly coupled, portable */
#endif
};

PRIVATE SctDatInd SbUiSctDatIndMt[MAXSBUI] =
{
#ifdef LCSBUISCT
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
/* sb003.103: M2PA (ENTMX) added as a new SCTP user */
#ifdef MX 
   MxLiSctDatInd,         /* 11 - tightly coupled, M2PA */
#else
   PtUiSctDatInd,         /* 11 - tightly coupled, portable */
#endif
/*sb016.103: S1AP added as new SCTP user*/
#ifdef SZ
   SzLiSctDatInd,         /* 12 - tightly coupled, S1AP */
#else
   PtUiSctDatInd,         /* 12 - tightly coupled, portable */
#endif
/* sb025.103: X2AP added as new SCTP user*/
#ifdef CZ
   CzLiSctDatInd,         /* 13 - tightly coupled, Diameter */
#else
   PtUiSctDatInd,         /* 13 - tightly coupled, portable */
#endif
/* sb027.103: Iuh added as new SCTP user */
#ifdef HM
   HmLiSctDatInd,         /* 14 - tightly coupled, Iuh */
#else
   PtUiSctDatInd,         /* 14 - tightly coupled, portable */
#endif /* HM */
};

PRIVATE SctStaCfm SbUiSctStaCfmMt[MAXSBUI] =
{
#ifdef LCSBUISCT
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
/* sb003.103: M2PA (ENTMX) added as a new SCTP user */
#ifdef MX 
   MxLiSctStaCfm,         /* 11 - tightly coupled, M2PA */
#else
   PtUiSctStaCfm,         /* 11 - tightly coupled, portable */
#endif
/*sb016.103: S1AP added as new SCTP user*/
/* sb025.103: combine SZ and SZ_PHASE2 flags in one ifdef */
/* sb026.103: Change || condition to && */
#if (defined (SZ) && defined (SZ_PHASE2))
   SzLiSctStaCfm,         /* 12 - tightly coupled, S1AP */
#else
   PtUiSctStaCfm,         /* 12 - tightly coupled, portable */
#endif
/* sb025.103: X2AP added as new SCTP user*/
#ifdef CZ
   CzLiSctStaCfm,         /* 13 - tightly coupled, Diameter */
#else
   PtUiSctStaCfm,         /* 13 - tightly coupled, portable */
#endif
};

PRIVATE SctStaInd SbUiSctStaIndMt[MAXSBUI] =
{
#ifdef LCSBUISCT
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
/* sb003.103: M2PA (ENTMX) added as a new SCTP user */
#ifdef MX 
   MxLiSctStaInd,         /* 11 - tightly coupled, M2PA*/
#else
   PtUiSctStaInd,         /* 11 - tightly coupled, portable */
#endif
/*sb016.103: S1AP added as new SCTP user*/
#ifdef SZ
   SzLiSctStaInd,         /* 12 - tightly coupled, S1AP */
#else
   PtUiSctStaInd,         /* 12 - tightly coupled, portable */
#endif
/* sb025.103: X2AP added as new SCTP user*/
#ifdef CZ
   CzLiSctStaInd,         /* 13 - tightly coupled, Diameter */
#else
   PtUiSctStaInd,         /* 13 - tightly coupled, portable */
#endif
/* sb027.103: Iuh added as new SCTP user */
#ifdef HM
   HmLiSctStaInd,         /* 14 - tightly coupled, Iuh */
#else
   PtUiSctStaInd,         /* 14 - tightly coupled, portable */
#endif /* HM */
};

PRIVATE SctFlcInd SbUiSctFlcIndMt[MAXSBUI] =
{
#ifdef LCSBUISCT
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
/* sb003.103: M2PA (ENTMX) added as a new SCTP user */
#ifdef MX 
   MxLiSctFlcInd,         /* 11 - tightly coupled, M2PA */
#else
   PtUiSctFlcInd,         /* 11 - tightly coupled, portable */
#endif
/*sb016.103: S1AP added as new SCTP user*/
/* sb022.103: Removed the SZ_PHASE2 flag */
#ifdef SZ
   SzLiSctFlcInd,         /* 12 - tightly coupled, S1AP */
#else
   PtUiSctFlcInd,         /* 12 - tightly coupled, portable */
#endif /* SZ */
/* sb025.103: X2AP added as new SCTP user*/
#ifdef CZ
   CzLiSctFlcInd,         /* 13 - tightly coupled, Diameter */
#else
   PtUiSctFlcInd,         /* 13 - tightly coupled, portable */
#endif
/* sb027.103: Iuh added as new SCTP user */
#ifdef HM
   HmLiSctFlcInd,        /* 14 - tightly coupled, Iuh */
#else
   PtUiSctFlcInd,        /* 14 - tightly coupled, portable */
#endif /* HM */
};

/*
 *  upper interface functions
 */




#ifdef ANSI
PUBLIC S16 SbUiSctBndCfm
(
Pst           *pst,
SuId           suId,
SctResult      result
)
#else
PUBLIC S16 SbUiSctBndCfm(pst, suId, result)
Pst           *pst;
SuId           suId;
SctResult      result;
#endif
{
   TRC3(SbUiSctBndCfm)

   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctBndCfm(pst, suId(%d), result(%d))\n",
          suId, result));

   /* jump to specific primitive depending on configured selector */
   /* sb048.102: DFTHA M3UA Support */
   switch (pst->dstEnt)
   {
#ifdef DV
      case ENTIT:
         if (pst->route == RTE_PROTO)
         {
            (*SbUiSctBndCfmMt[pst->selector])(pst, suId, result);
         }
         else
         {
            DvUiSctBndCfm(pst, suId, result);
         }
         break;
#endif /* DV */
      default:
         (*SbUiSctBndCfmMt[pst->selector])(pst, suId, result);
         break;
   }

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 SbUiSctEndpOpenCfm
(
Pst           *pst,
SuId           suId,
UConnId        suEndpId,
UConnId        spEndpId,
SctResult      result,
SctCause       cause
)
#else
PUBLIC S16 SbUiSctEndpOpenCfm(pst, suId, suEndpId, spEndpId, result, cause)
Pst           *pst;
SuId           suId;
UConnId        suEndpId;
UConnId        spEndpId;
SctResult      result;
SctCause       cause;
#endif
{
   TRC3(SbUiSctEndpOpenCfm)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctEndpOpenCfm(pst, suId(%d), suEndpId(%d), spEndpId(%d), result(%d), cause(%d))\n",
          suId, suEndpId, spEndpId, result, cause));
#else
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctEndpOpenCfm(pst, suId(%d), suEndpId(%ld), spEndpId(%ld), result(%d), cause(%d))\n",
          suId, suEndpId, spEndpId, result, cause));
#endif /* BIT_64 */

   /* jump to specific primitive depending on configured selector */
   /* sb048.102: DFTHA M3UA Support */
   switch (pst->dstEnt)
   {
#ifdef DV
      case ENTIT:
         if (pst->route == RTE_PROTO)
         {
            (*SbUiSctEndpOpenCfmMt[pst->selector])(pst, suId, suEndpId, spEndpId, 
                result, cause);
         }
         else
         {
            DvUiSctEndpOpenCfm(pst, suId, suEndpId, spEndpId, result, cause);
         }
         break;
#endif /* DV */
      default:
         (*SbUiSctEndpOpenCfmMt[pst->selector])(pst, suId, suEndpId, spEndpId, 
             result, cause);
         break;
   }

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 SbUiSctEndpCloseCfm
(
Pst           *pst,
SuId           suId,
UConnId        suEndpId,
SctResult      result,
SctCause       cause
)
#else
PUBLIC S16 SbUiSctEndpCloseCfm(pst, suId, suEndpId, result, cause)
Pst           *pst;
SuId           suId;
UConnId        suEndpId;
SctResult      result;
SctCause       cause;
#endif
{
   TRC3(SbUiSctEndpCloseCfm)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctEndpCloseCfm(pst, suId(%d), suEndpId(%d), result(%d), cause(%d))\n",
          suId, suEndpId, result, cause));
#else
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctEndpCloseCfm(pst, suId(%d), suEndpId(%ld), result(%d), cause(%d))\n",
          suId, suEndpId, result, cause));
#endif /* BIT_64 */

   /* jump to specific primitive depending on configured selector */
   /* sb048.102: DFTHA M3UA Support */
   switch (pst->dstEnt)
   {
#ifdef DV
      case ENTIT:
         if (pst->route == RTE_PROTO)
         {
            (*SbUiSctEndpCloseCfmMt[pst->selector])(pst, suId, suEndpId, result, 
              cause);
         }
         else
         {
            DvUiSctEndpCloseCfm(pst, suId, suEndpId, result, cause);
         }
         break;
#endif /* DV */
      default:
         (*SbUiSctEndpCloseCfmMt[pst->selector])(pst, suId, suEndpId, result, 
              cause);
         break;
   }

   RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 SbUiSctAssocInd
(
Pst               *pst,
SuId               suId,
UConnId            suEndpId,
SctAssocIndParams *assocParams,
Buffer            *vsInfo
)
#else
PUBLIC S16 SbUiSctAssocInd(pst, suId, suEndpId, assocParams, vsInfo)
Pst               *pst;
SuId               suId;
UConnId            suEndpId;
SctAssocIndParams *assocParams;
Buffer            *vsInfo;
#endif
{
   TRC3(SbUiSctAssocInd)

   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctAssocInd(pst, assocParams)\n"));

   /* jump to specific primitive depending on configured selector */
   /* sb048.102: DFTHA M3UA Support */
   switch (pst->dstEnt)
   {
#ifdef DV
      case ENTIT:
         if (pst->route == RTE_PROTO)
         {
            (*SbUiSctAssocIndMt[pst->selector])(pst, suId, suEndpId, assocParams, 
                vsInfo);
         }
         else
         {
            DvUiSctAssocInd(pst, suId, suEndpId, assocParams, vsInfo);
         }
         break;
#endif /* DV */
      default:
         (*SbUiSctAssocIndMt[pst->selector])(pst, suId, suEndpId, assocParams, 
             vsInfo);
         break;
   }

   RETVALUE(ROK);
}



/* sb016.102 - Include in-stream parameter here */
#ifdef SCT2
#ifdef ANSI
PUBLIC S16 SbUiSctAssocCfm
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
PUBLIC S16 SbUiSctAssocCfm(pst, suId, suAssocId, spAssocId, dstNAddrLst, dstPort, inStrms, outStrms, vsInfo )
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
PUBLIC S16 SbUiSctAssocCfm
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
PUBLIC S16 SbUiSctAssocCfm(pst, suId, suAssocId, spAssocId, dstNAddrLst, dstPort, outStrms, vsInfo )
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
   TRC3(SbUiSctAssocCfm)

/* sb016.102 - Include in-stream parameter here */
#ifdef SCT2
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctAssocCfm(pst, suId(%d), suAssocId(%d), spAssocId(%d), dstNAddrLst, dstPort(%d), inStrms(%d), outStrms(%d))\n",
          suId, suAssocId, spAssocId, dstPort, inStrms, outStrms));
#else
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctAssocCfm(pst, suId(%d), suAssocId(%ld), spAssocId(%ld), dstNAddrLst, dstPort(%d), inStrms(%d), outStrms(%d))\n",
          suId, suAssocId, spAssocId, dstPort, inStrms, outStrms));
#endif /* BIT_64 */

   /* jump to specific primitive depending on configured selector */
   /* sb048.102: DFTHA M3UA Support */
   /* sb049.102: DFTHA M3UA Support */
   switch (pst->dstEnt)
   {
#ifdef DV
      case ENTIT:
         if (pst->route == RTE_PROTO)
         {
            (*SbUiSctAssocCfmMt[pst->selector])(pst, suId, suAssocId, spAssocId, 
              dstNAddrLst, dstPort, inStrms, outStrms, vsInfo);
         }
         else
         {
            DvUiSctAssocCfm(pst, suId, suAssocId, spAssocId, dstNAddrLst, 
               dstPort, inStrms, outStrms, vsInfo);
         }
         break;
#endif /* DV */
      default:
         (*SbUiSctAssocCfmMt[pst->selector])(pst, suId, suAssocId, spAssocId, 
              dstNAddrLst, dstPort, inStrms, outStrms, vsInfo);
         break;
   }

#else /* SCT2 */

/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctAssocCfm(pst, suId(%d), suAssocId(%d), spAssocId(%d),\
           dstNAddrLst, dstPort(%d), outStrms(%d))\n",
          suId, suAssocId, spAssocId, dstPort, outStrms));
#else
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctAssocCfm(pst, suId(%d), suAssocId(%ld), spAssocId(%ld),\
           dstNAddrLst, dstPort(%d), outStrms(%d))\n",
          suId, suAssocId, spAssocId, dstPort, outStrms));
#endif /* BIT_64  */

   /* jump to specific primitive depending on configured selector */
   /* sb048.102: DFTHA M3UA Support */
   switch (pst->dstEnt)
   {
#ifdef DV
      case ENTIT:
         if (pst->route == RTE_PROTO)
         {
            (*SbUiSctAssocCfmMt[pst->selector])(pst, suId, suAssocId, spAssocId, 
              dstNAddrLst, dstPort, outStrms, vsInfo);
         }
         else
         {
            DvUiSctAssocCfm(pst, suId, suAssocId, spAssocId, dstNAddrLst, 
               dstPort, outStrms, vsInfo);
         }
         break;
#endif /* DV */
      default:
         (*SbUiSctAssocCfmMt[pst->selector])(pst, suId, suAssocId, spAssocId, 
              dstNAddrLst, dstPort, outStrms, vsInfo);
         break;
   }

#endif /* SCT2 */

   RETVALUE(ROK);
}




#ifdef ANSI
PUBLIC S16 SbUiSctTermInd
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
PUBLIC S16 SbUiSctTermInd(pst, suId, assocId, assocIdType, status, cause, rtrvInfo)
Pst           *pst;
SuId           suId;
UConnId        assocId;
U8             assocIdType;
SctStatus      status;
SctCause       cause;
SctRtrvInfo   *rtrvInfo;
#endif
{
   TRC3(SbUiSctTermInd)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctTermInd(pst, suId(%d), assocId(%d), assocIdType(%d), status(%d), cause(%d), rtrvInfo)\n",
          suId, assocId, assocIdType, status, cause));
#else
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctTermInd(pst, suId(%d), assocId(%ld), assocIdType(%d), status(%d), cause(%d), rtrvInfo)\n",
          suId, assocId, assocIdType, status, cause));
#endif /* BIT_64 */

   /* jump to specific primitive depending on configured selector */
   /* sb048.102: DFTHA M3UA Support */
   switch (pst->dstEnt)
   {
#ifdef DV
      case ENTIT:
         if (pst->route == RTE_PROTO)
         {
            (*SbUiSctTermIndMt[pst->selector])(pst, suId, assocId, assocIdType, 
                status, cause, rtrvInfo);
         }
         else
         {
            DvUiSctTermInd(pst, suId, assocId, assocIdType, status, cause, 
               rtrvInfo);
         }
         break;
#endif /* DV */
      default:
         (*SbUiSctTermIndMt[pst->selector])(pst, suId, assocId, assocIdType, 
             status, cause, rtrvInfo);
         break;
   }

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 SbUiSctTermCfm
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
SctResult      result,
SctCause       cause
)
#else
PUBLIC S16 SbUiSctTermCfm(pst, suId, suAssocId, result, cause)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
SctResult      result;
SctCause       cause;
#endif
{
   TRC3(SbUiSctTermCfm)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctTermCfm(pst, suId(%d), suAssocId(%d), result(%d), cause(%d))\n",
          suId, suAssocId, result, cause));
#else
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctTermCfm(pst, suId(%d), suAssocId(%ld), result(%d), cause(%d))\n",
          suId, suAssocId, result, cause));
#endif /* BIT_64 */

   /* jump to specific primitive depending on configured selector */
   /* sb048.102: DFTHA M3UA Support */
   switch (pst->dstEnt)
   {
#ifdef DV
      case ENTIT:
         if (pst->route == RTE_PROTO)
         {
            (*SbUiSctTermCfmMt[pst->selector])(pst, suId, suAssocId, result,
                cause);
         }
         else
         {
            DvUiSctTermCfm(pst, suId, suAssocId, result, cause);
         }
         break;
#endif /* DV */
      default:
         (*SbUiSctTermCfmMt[pst->selector])(pst, suId, suAssocId, result, cause);
         break;
   }

   RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 SbUiSctSetPriCfm
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
SctResult      result,
SctCause       cause
)
#else
PUBLIC S16 SbUiSctSetPriCfm(pst, suId, suAssocId, result, cause)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
SctResult      result;
SctCause       cause;
#endif
{
   TRC3(SbUiSctSetPriCfm)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctSetPriCfm(pst, suId(%d), suAssocId(%d), result(%d), cause(%d))\n",
          suId, suAssocId, result, cause));
#else
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctSetPriCfm(pst, suId(%d), suAssocId(%ld), result(%d), cause(%d))\n",
          suId, suAssocId, result, cause));
#endif /* BIT_64 */

   /* jump to specific primitive depending on configured selector */
   /* sb048.102: DFTHA M3UA Support */
   switch (pst->dstEnt)
   {
#ifdef DV
      case ENTIT:
         if (pst->route == RTE_PROTO)
         {
            (*SbUiSctSetPriCfmMt[pst->selector])(pst, suId, suAssocId, result,
                cause);
         }
         else
         {
            SbUiSctSetPriCfm(pst, suId, suAssocId, result, cause);
         }
         break;
#endif /* DV */
      default:
         (*SbUiSctSetPriCfmMt[pst->selector])(pst, suId, suAssocId, result,
             cause);
         break;
   }

   RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 SbUiSctHBeatCfm
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
PUBLIC S16 SbUiSctHBeatCfm(pst, suId, suAssocId, dstNAddr, status, result, cause)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
CmNetAddr     *dstNAddr;
SctStatus      status;
SctResult      result;
SctCause       cause;
#endif
{
   TRC3(SbUiSctHBeatCfm)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctHBeatCfm(pst, suId(%d), suAssocId(%d), dstNAddr, status(%d), result(%d), cause(%d))\n",
          suId, suAssocId, status, result, cause));
#else
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctHBeatCfm(pst, suId(%d), suAssocId(%ld), dstNAddr, status(%d), result(%d), cause(%d))\n",
          suId, suAssocId, status, result, cause));
#endif /* BIT_64 */ 

   /* jump to specific primitive depending on configured selector */
   /* sb048.102: DFTHA M3UA Support */
   switch (pst->dstEnt)
   {
#ifdef DV
      case ENTIT:
         if (pst->route == RTE_PROTO)
         {
            (*SbUiSctHBeatCfmMt[pst->selector])(pst, suId, suAssocId, dstNAddr,
               status, result, cause);
         }
         else
         {
            DvUiSctHBeatCfm(pst, suId, suAssocId, dstNAddr, status, result,
               cause);
         }
         break;
#endif /* DV */
      default:
         (*SbUiSctHBeatCfmMt[pst->selector])(pst, suId, suAssocId, dstNAddr,
              status, result, cause);
         break;
   }

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 SbUiSctDatInd
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
PUBLIC S16 SbUiSctDatInd(pst, suId, suAssocId, strmId, indType, protId, mBuf)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
SctStrmId      strmId;
SctDatIndType *indType;
U32            protId;
Buffer        *mBuf;
#endif
{
   TRC3(SbUiSctDatInd)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctDatInd(pst, suId(%d), suAssocId(%d), strmId(%d), indType, protId(%d), mBuf)\n",
          suId, suAssocId, strmId, protId));
#else
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctDatInd(pst, suId(%d), suAssocId(%ld), strmId(%d), indType, protId(%ld), mBuf)\n",
          suId, suAssocId, strmId, protId));
#endif /* BIT_64 */

   /* jump to specific primitive depending on configured selector */
   /* sb048.102: DFTHA M3UA Support */
   switch (pst->dstEnt)
   {
#ifdef DV
      case ENTIT:
         if (pst->route == RTE_PROTO)
         {
            (*SbUiSctDatIndMt[pst->selector])(pst, suId, suAssocId, strmId, 
                indType, protId, mBuf);
         }
         else
         {
            DvUiSctDatInd(pst, suId, suAssocId, strmId, indType, protId, mBuf);
         }
         break;
#endif /* DV */
      default:
         (*SbUiSctDatIndMt[pst->selector])(pst, suId, suAssocId, strmId, 
             indType, protId, mBuf);
         break;
   }

   RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 SbUiSctStaCfm
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
PUBLIC S16 SbUiSctStaCfm(pst, suId, suAssocId, dstNAddr, result, cause, staInfo)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
CmNetAddr     *dstNAddr;
SctResult      result;
SctCause       cause;
SctStaInfo    *staInfo;
#endif
{
   TRC3(SbUiSctStaCfm)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctStaCfm(pst, suId(%d), suAssocId(%d), dstNAddr, result(%d), cause(%d), staInfo)\n",
          suId, suAssocId, result, cause));
#else
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctStaCfm(pst, suId(%d), suAssocId(%ld), dstNAddr, result(%d), cause(%d), staInfo)\n",
          suId, suAssocId, result, cause));
#endif /* BIT_64 */

   /* jump to specific primitive depending on configured selector */
   /* sb048.102: DFTHA M3UA Support */
   switch (pst->dstEnt)
   {
#ifdef DV
      case ENTIT:
         if (pst->route == RTE_PROTO)
         {
            (*SbUiSctStaCfmMt[pst->selector])(pst, suId, suAssocId, dstNAddr, 
               result, cause, staInfo);
         }
         else
         {
            DvUiSctStaCfm(pst, suId, suAssocId, dstNAddr, result, cause, 
               staInfo);
         }
         break;
#endif /* DV */
      default:
         (*SbUiSctStaCfmMt[pst->selector])(pst, suId, suAssocId, dstNAddr, 
             result, cause, staInfo);
         break;
   }

   RETVALUE(ROK);
}

/* sb024.103: Included protId parameter in status indication */
#ifdef SCT7
#ifdef ANSI
PUBLIC S16 SbUiSctStaInd
(
 Pst           *pst,       /* post structure */
 SuId          suId,       /* service user SAP identifier */
 UConnId       suAssocId,  /* service user assoc identifier */
 UConnId       spAssocId,  /* service provider assoc identifier */
 CmNetAddr     *dstNAddr,  /* destination network address */
 SctStatus     status,
 SctCause      cause,
 U32           protId,      /* Protocol ID */
 Buffer        *mBuf       /* message buffer */
 )
#else
PUBLIC S16 SbUiSctStaInd (pst, suId, suAssocId, spAssocId, dstNAddr,
		status, cause,protId, mBuf)
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
#else
#ifdef ANSI
PUBLIC S16 SbUiSctStaInd
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
PUBLIC S16 SbUiSctStaInd (pst, suId, suAssocId, spAssocId, dstNAddr,
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
	TRC3(SbUiSctStaInd)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
		SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
					"SbUiSctStaInd(pst, suId(%d), suAssocId(%d), spAssocId(%d), dstNAddr, status(%d), cause(%d), mBuf)\n",
					suId, suAssocId, spAssocId, status, cause));
#else
		SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
					"SbUiSctStaInd(pst, suId(%d), suAssocId(%ld), spAssocId(%ld), dstNAddr, status(%d), cause(%d), mBuf)\n",
					suId, suAssocId, spAssocId, status, cause));
#endif /* BIT_64 */

	/* jump to specific primitive depending on configured selector */
	/* sb048.102: DFTHA M3UA Support */
	switch (pst->dstEnt)
	{
#ifdef DV
		case ENTIT:
			if (pst->route == RTE_PROTO)
			{
				/* sb024.103: Included protId parameter in status indication */
#ifdef SCT7
				(*SbUiSctStaIndMt[pst->selector])(pst, suId, suAssocId, spAssocId, 
												  dstNAddr, status, cause, protId, mBuf);
#else
				(*SbUiSctStaIndMt[pst->selector])(pst, suId, suAssocId, spAssocId,
												  dstNAddr, status, cause, mBuf);
#endif /* SCT7 */
			}
			else
			{
				/* sb024.103: Included protId parameter in status indication */
#ifdef SCT7
				DvUiSctStaInd (pst, suId, suAssocId, spAssocId, dstNAddr,
						status, cause, protId, mBuf);
#else
				DvUiSctStaInd (pst, suId, suAssocId, spAssocId, dstNAddr,
						status, cause, mBuf);
#endif /* SCT7 */
			}
			break;
#endif /* DV */
		default:
			/* sb024.103: Included protId parameter in status indication */
#ifdef SCT7
			(*SbUiSctStaIndMt[pst->selector])(pst, suId, suAssocId, spAssocId, 
											  dstNAddr, status, cause, protId, mBuf);
#else
			(*SbUiSctStaIndMt[pst->selector])(pst, suId, suAssocId, spAssocId,
											  dstNAddr, status, cause, mBuf);
#endif /* SCT7 */
			break;
	}

	RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 SbUiSctFlcInd
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
Reason         reason
)
#else
PUBLIC S16 SbUiSctFlcInd(pst, suId, suAssocId, reason)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
Reason         reason;
#endif
{
   TRC3(SbUiSctFlcInd)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctFlcInd(pst, suId(%d), suAssocId(%d), reason(%d))\n",
          suId, suAssocId, reason));
#else
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctFlcInd(pst, suId(%d), suAssocId(%ld), reason(%d))\n",
          suId, suAssocId, reason));
#endif /* BIT_64 */

   /* jump to specific primitive depending on configured selector */
   /* sb048.102: DFTHA M3UA Support */
   switch (pst->dstEnt)
   {
#ifdef DV
      case ENTIT:
         if (pst->route == RTE_PROTO)
         {
            (*SbUiSctFlcIndMt[pst->selector])(pst, suId, suAssocId, reason);
         }
         else
         {
            DvUiSctFlcInd(pst, suId, suAssocId, reason);
         }
         break;
#endif /* DV */
      default:
         (*SbUiSctFlcIndMt[pst->selector])(pst, suId, suAssocId, reason);
         break;
   }

   RETVALUE(ROK);
}


/*
*     upper interface portable functions
*/

#ifdef PTSBUISCT


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
   SBLOGERROR(ERRCLS_DEBUG, ESB373, (ErrVal)ERRZERO,
              "PtUiSctBndCfm: Failed");
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
   SBLOGERROR(ERRCLS_DEBUG, ESB374, (ErrVal)ERRZERO,
              "PtUiSctEndpOpenCfm: Failed");
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
   SBLOGERROR(ERRCLS_DEBUG, ESB375, (ErrVal)ERRZERO,
              "PtUiSctEndpCloseCfm: Failed");
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
   SBLOGERROR(ERRCLS_DEBUG, ESB376, (ErrVal)ERRZERO,
              "PtUiSctAssocInd: Failed");
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
   SBLOGERROR(ERRCLS_DEBUG, ESB377, (ErrVal)ERRZERO,
              "PtUiSctAssocCfm: Failed");
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
   SBLOGERROR(ERRCLS_DEBUG, ESB378, (ErrVal)ERRZERO,
              "PtUiSctTermInd: Failed");
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
   SBLOGERROR(ERRCLS_DEBUG, ESB379, (ErrVal)ERRZERO,
              "PtUiSctTermCfm: Failed");
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
   SBLOGERROR(ERRCLS_DEBUG, ESB380, (ErrVal)ERRZERO,
              "PtUiSctSetPriCfm: Failed");
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
   SBLOGERROR(ERRCLS_DEBUG, ESB381, (ErrVal)ERRZERO,
              "PtUiSctHBeatCfm: Failed");
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
   SBLOGERROR(ERRCLS_DEBUG, ESB382, (ErrVal)ERRZERO,
              "PtUiSctDatInd: Failed");
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
   SBLOGERROR(ERRCLS_DEBUG, ESB383, (ErrVal)ERRZERO,
              "PtUiSctStaCfm: Failed");
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


/* sb024.103: Included protId parameter in status indication */
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
#else
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
#endif  /* SCT7 */
{
	TRC3(PtUiSctStaInd)

#if (ERRCLASS & ERRCLS_DEBUG)
		SBLOGERROR(ERRCLS_DEBUG, ESB384, (ErrVal)ERRZERO,
				"PtUiSctStaInd: Failed");
#endif /* ERRCLASS */

	UNUSED(pst);
	UNUSED(suId);
	UNUSED(suAssocId);
	UNUSED(spAssocId);
	UNUSED(dstNAddr);
	UNUSED(status);
	UNUSED(cause);
	/* sb024.103: Included protId parameter in status indication */
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
   SBLOGERROR(ERRCLS_DEBUG, ESB385, (ErrVal)ERRZERO,
              "PtUiSctFlcInd: Failed");
#endif /* ERRCLASS */

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suAssocId);
   UNUSED(reason);

   RETVALUE(ROK);
}

#endif /* PTSBUISCT */


/********************************************************************30**

         End of file:     sb_ptui.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:18 2015

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
 /main/2     ---      asa   1. initial release.
           sb003.11    sb   1. Function matrics modified for IUA layer.
 /main/2     ---       sb   1. Modified for SCTP release based on 
                               RFC-2960 'Oct 2000.
          sb016.102    ap   1. Include in-stream parameter in AssocCfm 
                               under SCT2 compile time flag.
          sb042.102    hl   1. Added change for SHT interface and Rolling
                               UpGrade
          sb048.102    rs   1. GCP added as new SCTP user. 
                            2. Dummy user added.
                            3. DFTHA M3UA support.
          sb052.102    ag   1. NBAP (ENTIB),M1UA (ENTMZ) added as new SCTP user. 
          sb065.102    kp   1. SIP added as new SCTP user.
          sb079.102    kp   1. Diameter added as new SCTP user.          
/main/3      ---    rsr/ag  1. Updated for Release of 1.3
          sb003.103    ag   1. M2PA (ENTMX) added as a new SCTP user 
          sb016.103    hsingh  1. S1AP added as new SCTP user. 
/main/3   sb022.103    pkaX  1. C++ compilation error fix.
/main/3   sb024.103   ajainx 1. Included protId parameter in status indication.
          sb025.103   mm     1. Updated for X2AP release 1.1.
                             2. Combine SZ and SZ_PHASE2 in one ifdef. 
          sb026.103   mm     1. Change || condition to && b/w SZ and SZ_PHASE2.
          sb027.103   ajainx 1. Updated for Iuh release
/main/3   sb030.103   krkX   1. Fixed the warnings during 64-BIT compilation.
*********************************************************************91*/
