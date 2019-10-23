

/********************************************************************20**

     Name:     Simple Control Transmission Protocol (SCTP)

     Type:     C include file

     Desc:     Structures, variables and typedefs required by SCTP User

     File:     sct.x

     Sid:      sct.x@@/main/40 - Thu Aug 18 12:47:07 2011

     Prg:      nj

*********************************************************************21*/

#ifndef __SCTX__
#define __SCTX__

#ifdef __cplusplus
extern "C" {
#endif


/*
*     The defines declared in this file correspond to defines
*     used by the following TRILLIUM software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*     1000xxx     SIGTRAN - SCTP
*
*/

/*
*     This software may be combined with the following TRILLIUM
*     software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*     1000xxx     SIGTRAN - Adaptation Layers
*
*/
typedef U16 SctStrmId;           /* Stream Id/Number of Streams */
typedef U16 SctPort;             /* Port number */
typedef U32 SctTSN;              /* TSN */
typedef U16 SctRTT;              /* Round-trip time */
typedef U16 SctStatus;           /* Status Parameter */
typedef U16 SctResult;           /* Result Parameter */
typedef U16 SctCause;            /* Cause Parameter */
typedef S32 SctWinSize;          /* Window size */
typedef TknStr64 SctVSInfo;      /* Vendor Specific Information */
#ifdef SCT3
typedef U8 SctTos;
#endif /* ST3 */

/* Array of Network Addresses */
typedef struct _sctNetAddrLst
{
   U8            nmb;                        /* Number of Network Addresses */
   CmNetAddr     nAddr[SCT_MAX_NET_ADDRS];   /* List of Network Addresses */
} SctNetAddrLst;

/* Data Retrieval Information */
typedef struct _sctRtrvInfo
{
   U32           nmbUnsentDgms;       /* Number of unsent datagrams */
   U32           nmbUnackDgms;        /* Number of unacked datagrams */
   U32           nmbUndelDgms;        /* Number of undelivered datagrams */
   SctTSN        lastAckTsn;          /* The highest consecutive TSN acked */
   SctTSN        lastSentTsn;         /* TSN of last datagram sent to peer */
} SctRtrvInfo;

/* Data Retreival Indication type */
typedef struct _sctDatIndType
{
   U8           type;               /* Data Indication type */
   SctTSN       tsn;                /* TSN */
   U16          seqNum;             /* Sequence Number */
   Bool         last;               /* Last Datagram */
} SctDatIndType;

/* INIT chunk indication parameters */
typedef struct _SctInitParams
{
   U32            iTag;                 /* Initiate Tag */
   U32            a_rwnd;               /* Advertised rwnd */
   SctStrmId      outStrms;             /* Number of peer outgoing streams */
   SctStrmId      inStrms;              /* Number of peer incoming streams */
   SctTSN         iTsn;                 /* Initial TSN */
   U32            cookieLife;           /* Suggested cookie lifespan */
   SctPort        peerPort;             /* SCTP port address of peer */
   SctPort        localPort;            /* Local SCTP port address */
   SctNetAddrLst  peerAddrLst;          /* List of Dest. Network Addresses */
   SctNetAddrLst  localAddrLst;         /* List of Src. Network Addresses */
   U16         supAddress;              /* Supported Address Parameter */
   U8          hstNameLen;              /* Length of domain Name Address */
   U8          hstName[SCT_DNAME_LEN]; /* Domain Name  of the Peer */
/* sct_x_001.main_24: SATELLITE SCTP feature */
#ifdef SB_ECN
   Bool            ecnFlg;         /* Enable/Disable ECN Feature */
#endif /* SB_ECN */
/* sct_x_001.main_27: Added for handling of unrecognized parameters when handleInitFlg is FALSE */
#ifdef SCT5
/* sct_x_001.main_29: Dual Checksum Fix */
  U8          checksumType;
  MsgLen      unBufLength;
  Buffer     *unBuf;
#endif
} SctInitParams;

/* COOKIE chunk indication parameters */
typedef struct _SctCookieParams
{
   UConnId        spAssocId;            /* serive provider association ID */
   UConnId        suAssocId;            /* service user association ID */
   SctPort        peerPort;             /* SCTP port address of peer */
   SctNetAddrLst  peerAddrLst;          /* List of Dest. Network Addresses */
   /* sct_x_001.main_31: Added the Instream and Outstream parameter */
#ifdef SCT6
    SctStrmId      inStrms;              /* Number of peer incoming streams */
    SctStrmId      outStrms;             /* Number of peer outgoing streams */
#endif /* SCT6 */
} SctCookieParams;

/* Association Indication type */
typedef struct _SctAssocIndParams
{
   U8            type;              /* Type of indication */
   union
   {
      SctInitParams         initParams;
      SctCookieParams       cookieParams;
   } t;
#ifdef SCT4
   U8           tos;
#endif /* SCT4 */

} SctAssocIndParams;

/* Association Status Information */
typedef struct _sctAssocInfo
{
   SctWinSize    rwnd;           /* Receiver's window size */
   U8            connSta;        /* Connection Status */
   CmNetAddr     priDstAddr;     /* Primary Destination Network Address */
   SctPort       dstPort;        /* Port number */
   SctNetAddrLst dstAddrLst;     /* Other Destination Network Addresses */
} SctAssocInfo;

/* Address Status Information */
typedef struct _sctAddrInfo
{
   U16      rtt;                        /* Round Trip Time */
   U32      cwnd;                       /* Congestion Window Size */
   U32      rto;                        /* Retransmision Timeout */
   Bool     active;                     /* Currently active? */
} SctAddrInfo;

/* SCTP Status Information */
typedef struct _sctStaInfo
{
   U8        staType;              /* Status Type */
   union
   {
      SctAssocInfo    assocInfo;   /* Association Info */
      SctAddrInfo     addrInfo;    /* Address Info */
      SctRtrvInfo     rtrvInfo;    /* Retrieval Information */
   } u;
} SctStaInfo;

/* typedefs of primitives */

/* depending on the specific selector in the Pst structure,
 * a primitive originated from a service provider can be dispatched to
 * any service user. The assumption is that, even if every primitive has
 * a different name depending in which file it resides, every primitive
 * must have the same function prototype, i.e. the same identical set
 * of arguments. These arguments are defined here
 */

typedef S16 (*SctBndReq)     ARGS((Pst            *pst,
                                   SuId            suId,
                                   SpId            spId));

typedef S16 (*SctBndCfm)     ARGS((Pst            *pst,
                                   SuId            suId,
                                   SctResult       result));

#ifdef SCT_ENDP_MULTI_IPADDR
typedef S16 (*SctEndpOpenReq) ARGS((Pst            *pst,
                                    SpId            spId,
                                    UConnId         suEndpId,
                                    SctPort         port,
                                    SctNetAddrLst  *srcAddrLst));
#else /* SCT_ENDP_MULTI_IPADDR */
typedef S16 (*SctEndpOpenReq) ARGS((Pst            *pst,
                                    SpId            spId,
                                    UConnId         suEndpId,
                                    SctPort         port,
                                    CmNetAddr      *intfNAddr));
#endif /* SCT_ENDP_MULTI_IPADDR */

typedef S16 (*SctEndpOpenCfm) ARGS((Pst            *pst,
                                    SuId            suId,
                                    UConnId         suEndpId,
                                    UConnId         spEndpId,
                                    SctResult       result,
                                    SctCause        cause));

typedef S16 (*SctEndpCloseReq) ARGS((Pst           *pst,
                                     SpId           spId,
                                     UConnId        endpId,
                                     U8             endpIdType));

typedef S16 (*SctEndpCloseCfm) ARGS((Pst           *pst,
                                     SuId           suId,
                                     UConnId        suEndpId,
                                     SctResult      result,
                                     SctCause       cause));

#ifdef SCT3
typedef S16 (*SctAssocReq)   ARGS((Pst            *pst,
                                   SpId            spId,
                                   UConnId         spEndpId,
                                   UConnId         suAssocId,
                                   CmNetAddr      *priDstNAddr,
                                   SctPort         dstPort,
                                   SctStrmId       outStrms,
                                   SctNetAddrLst  *dstNAddrLst,
                                   SctNetAddrLst  *srcNAddrLst,
                                   SctTos          tos,
                                   Buffer         *vsInfo)); 
#else /* SCT3 */
typedef S16 (*SctAssocReq)   ARGS((Pst            *pst,
                                   SpId            spId,
                                   UConnId         spEndpId,
                                   UConnId         suAssocId,
                                   CmNetAddr      *priDstNAddr,
                                   SctPort         dstPort,
                                   SctStrmId       outStrms,
                                   SctNetAddrLst  *dstNAddrLst,
                                   SctNetAddrLst  *srcNAddrLst,
                                   Buffer         *vsInfo)); 
#endif /* SCT3 */

typedef S16 (*SctAssocInd)   ARGS((Pst               *pst,
                                   SuId               suId,
                                   UConnId            suEndpId,
                                   SctAssocIndParams *assocParams,
                                   Buffer            *vsInfo)); 

#ifdef SCT3
typedef S16 (*SctAssocRsp)   ARGS((Pst               *pst,
                                   SpId               spId,
                                   UConnId            spEndpId,
                                   SctAssocIndParams *assocParams,
                                   SctTos             tos,
                                   SctResult          result,
                                   Buffer            *vsInfo)); 
#else /* SCT3 */
typedef S16 (*SctAssocRsp)   ARGS((Pst               *pst,
                                   SpId               spId,
                                   UConnId            spEndpId,
                                   SctAssocIndParams *assocParams,
                                   SctResult          result,
                                   Buffer            *vsInfo)); 
#endif /* SCT3 */

#ifdef SCT2
typedef S16 (*SctAssocCfm)   ARGS((Pst            *pst,
                                   SuId            suId,
                                   UConnId         suAssocId,
                                   UConnId         spAssocId,
                                   SctNetAddrLst  *dstNAddrLst,
                                   SctPort         dstPort,
                                   SctStrmId       inStrms,
                                   SctStrmId       outStrms,
                                   Buffer         *vsInfo)); 
#else /* SCT2 */
typedef S16 (*SctAssocCfm)   ARGS((Pst            *pst,
                                   SuId            suId,
                                   UConnId         suAssocId,
                                   UConnId         spAssocId,
                                   SctNetAddrLst  *dstNAddrLst,
                                   SctPort         dstPort,
                                   SctStrmId       outStrms,
                                   Buffer         *vsInfo)); 
#endif /* SCT2 */
#ifdef S1SIMAPP
typedef S16 (*SctTermReq)    ARGS((Pst            *pst,
                                   SpId            spId,
                                   UConnId         assocId,
                                   U8              assocIdType,
                                   Bool            abrtFlg,
                                   U8              cause));
#else
typedef S16 (*SctTermReq)    ARGS((Pst            *pst,
                                   SpId            spId,
                                   UConnId         assocId,
                                   U8              assocIdType,
                                   Bool            abrtFlg));
#endif

typedef S16 (*SctTermInd)    ARGS((Pst            *pst,
                                   SuId            suId,
                                   UConnId         assocId,
                                   U8              assocIdType,
                                   SctStatus       status,
                                   SctCause        cause,
                                   SctRtrvInfo    *rtrvInfo));

typedef S16 (*SctTermCfm)    ARGS((Pst            *pst,
                                   SuId            suId,
                                   UConnId         suAssocId,
                                   SctResult       result,
                                   SctCause        cause));

typedef S16 (*SctSetPriReq)  ARGS((Pst            *pst,
                                   SpId            spId,
                                   UConnId         spAssocId,
                                   CmNetAddr      *dstNAddr));

typedef S16 (*SctSetPriCfm)  ARGS((Pst            *pst,
                                   SuId            suId,
                                   UConnId         suAssocId,
                                   SctResult       result,
                                   SctCause        cause));

typedef S16 (*SctHBeatReq)   ARGS((Pst            *pst,
                                   SpId            spId,
                                   UConnId         spAssocId,
                                   CmNetAddr      *dstNAddr,
                                   U16             intervalTime,
                                   SctStatus       status));

typedef S16 (*SctHBeatCfm)   ARGS((Pst            *pst,
                                   SuId            suId,
                                   UConnId         suAssocId,
                                   CmNetAddr      *dstNAddr,
                                   SctStatus       status,
                                   SctResult       result,
                                   SctCause        cause));

typedef S16 (*SctDatReq)     ARGS((Pst            *pst,
                                   SpId            spId,
                                   UConnId         spAssocId,
                                   CmNetAddr      *dstNAddr,
                                   SctStrmId       strmId,
                                   Bool            unorderFlg,
                                   Bool            nobundleFlg,
                                   U16             lifeTime,
                                   U32             protId,
                                   Buffer         *mBuf));

typedef S16 (*SctDatInd)     ARGS((Pst            *pst,
                                   SuId            suId,
                                   UConnId         suAssocId,
                                   SctStrmId       strmId,
                                   SctDatIndType  *indType,
                                   U32             protId,
                                   Buffer         *mBuf));

typedef S16 (*SctStaReq)     ARGS((Pst            *pst,
                                   SpId            spId,
                                   UConnId         spAssocId,
                                   CmNetAddr      *dstNAddr,
                                   U8              staType));

typedef S16 (*SctStaCfm)     ARGS((Pst            *pst,
                                   SuId            suId,
                                   UConnId         suAssocId,
                                   CmNetAddr      *dstNAddr,
                                   SctResult       result,
                                   SctCause        cause,
                                   SctStaInfo     *staInfo));
/* sct_x_001.main_33: Included protId parameter in status indication */
#ifdef SCT7
typedef S16 (*SctStaInd)     ARGS((Pst            *pst,
                                   SuId            suId,
                                   UConnId         suAssocId,
                                   UConnId         spAssocId,
                                   CmNetAddr      *dstNAddr,
                                   SctStatus       status,
                                   SctCause        cause,
                                   U32             protId,
                                   Buffer         *mBuf));
#else
typedef S16 (*SctStaInd)     ARGS((Pst            *pst,
                                   SuId            suId,
                                   UConnId         suAssocId,
                                   UConnId         spAssocId,
                                   CmNetAddr      *dstNAddr,
                                   SctStatus       status,
                                   SctCause        cause,
                                   Buffer         *mBuf));
#endif /* SCT7 */

typedef S16 (*SctFlcInd)     ARGS((Pst            *pst,
                                   SuId            suId,
                                   UConnId         suAssocId,
                                   Reason          reason));

/***********************************************************
* extern declarations of primitives at the upper interface *
************************************************************/

/* SB layer, upper interface primitives */
#ifdef SB
EXTERN S16 SbUiSctBndReq            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SpId           spId));

EXTERN S16 SbUiSctBndCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SctResult      result));

#ifdef SCT_ENDP_MULTI_IPADDR
EXTERN S16 SbUiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          SctNetAddrLst  *srcAddrLst));
#else
EXTERN S16 SbUiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          CmNetAddr     *intfNAddr));
#endif
EXTERN S16 SbUiSctEndpOpenCfm       ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          UConnId        spEndpId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 SbUiSctEndpCloseReq      ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        endpId,
                                          U8             endpIdType));

EXTERN S16 SbUiSctEndpCloseCfm      ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          SctResult      result,
                                          SctCause       cause));

#ifdef SCT3
EXTERN S16 SbUiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          SctTos         tos,
                                          Buffer        *vsInfo));
#else /* SCT3 */
EXTERN S16 SbUiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          Buffer        *vsInfo));
#endif /* SCT3 */

EXTERN S16 SbUiSctAssocInd          ARGS((Pst               *pst,
                                          SuId               suId,
                                          UConnId            suEndpId,
                                          SctAssocIndParams *assocParams,
                                          Buffer            *vsInfo));

#ifdef SCT3
EXTERN S16 SbUiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctTos             tos,
                                          SctResult          result,
                                          Buffer            *vsInfo));
#else /* SCT3 */
EXTERN S16 SbUiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctResult          result,
                                          Buffer            *vsInfo));
#endif /* SCT3 */

#ifdef SCT2
EXTERN S16 SbUiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      inStrms,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#else /* SCT2 */
EXTERN S16 SbUiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));

#endif /* SCT2 */
#ifdef S1SIMAPP
EXTERN S16 SbUiSctTermReq           ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          Bool           abrtFlg,
                                          U8             cause));
#else
EXTERN S16 SbUiSctTermReq           ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          Bool           abrtFlg));
#endif
EXTERN S16 SbUiSctTermInd           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          SctStatus      status,
                                          SctCause       cause,
                                          SctRtrvInfo   *rtrvInfo));

EXTERN S16 SbUiSctTermCfm           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 SbUiSctSetPriReq         ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr));

EXTERN S16 SbUiSctSetPriCfm         ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 SbUiSctHBeatReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U16            intervalTime,
                                          SctStatus      status));

EXTERN S16 SbUiSctHBeatCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 SbUiSctDatReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStrmId      strmId,
                                          Bool           unorderFlg,
                                          Bool           nobundleFlg,
                                          U16            lifeTime,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 SbUiSctDatInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctStrmId      strmId,
                                          SctDatIndType *indType,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 SbUiSctStaReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U8             staType));

EXTERN S16 SbUiSctStaCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctResult      result,
                                          SctCause       cause,
                                          SctStaInfo    *staInfo));
/* sct_x_001.main_33: Included protId parameter in status indication */
#ifdef SCT7
EXTERN S16 SbUiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
										            U32            protId,
                                          Buffer        *mBuf));
#else
EXTERN S16 SbUiSctStaInd            ARGS((Pst           *pst,
			                              SuId           suId,
		 	                              UConnId        suAssocId,
			                              UConnId        spAssocId,
			                              CmNetAddr     *dstNAddr,
			                              SctStatus      status,
			                              SctCause       cause,
			                              Buffer        *mBuf));
#endif /* SCT7 */
EXTERN S16 SbUiSctFlcInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          Reason         reason));
#endif /* SB */


/*sct_x_001.main_26 Updated for TUCL 2.1 Release*/
#ifdef HI
EXTERN S16 HiUiSctBndReq            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SpId           spId));

EXTERN S16 HiUiSctBndCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SctResult      result));

#ifdef SCT_ENDP_MULTI_IPADDR
EXTERN S16 HiUiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          SctNetAddrLst  *srcAddrLst));
#else
EXTERN S16 HiUiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          CmNetAddr     *intfNAddr));
#endif
EXTERN S16 HiUiSctEndpOpenCfm       ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          UConnId        spEndpId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 HiUiSctEndpCloseReq      ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        endpId,
                                          U8             endpIdType));

EXTERN S16 HiUiSctEndpCloseCfm      ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          SctResult      result,
                                          SctCause       cause));

#ifdef SCT3
EXTERN S16 HiUiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          SctTos         tos,
                                          Buffer        *vsInfo));
#else /* SCT3 */
EXTERN S16 HiUiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          Buffer        *vsInfo));
#endif /* SCT3 */

EXTERN S16 HiUiSctAssocInd          ARGS((Pst               *pst,
                                          SuId               suId,
                                          UConnId            suEndpId,
                                          SctAssocIndParams *assocParams,
                                          Buffer            *vsInfo));

#ifdef SCT3
EXTERN S16 HiUiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctTos             tos,
                                          SctResult          result,
                                          Buffer            *vsInfo));
#else /* SCT3 */
EXTERN S16 HiUiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctResult          result,
                                          Buffer            *vsInfo));
#endif /* SCT3 */

#ifdef SCT2
EXTERN S16 HiUiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      inStrms,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#else /* SCT2 */
EXTERN S16 HiUiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));

#endif /* SCT2 */

EXTERN S16 HiUiSctTermReq           ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          Bool           abrtFlg));

EXTERN S16 HiUiSctTermInd           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          SctStatus      status,
                                          SctCause       cause,
                                          SctRtrvInfo   *rtrvInfo));

EXTERN S16 HiUiSctTermCfm           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 HiUiSctSetPriReq         ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr));

EXTERN S16 HiUiSctSetPriCfm         ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 HiUiSctHBeatReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U16            intervalTime,
                                          SctStatus      status));

EXTERN S16 HiUiSctHBeatCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 HiUiSctDatReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStrmId      strmId,
                                          Bool           unorderFlg,
                                          Bool           nobundleFlg,
                                          U16            lifeTime,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 HiUiSctDatInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctStrmId      strmId,
                                          SctDatIndType *indType,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 HiUiSctStaReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U8             staType));

EXTERN S16 HiUiSctStaCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctResult      result,
                                          SctCause       cause,
                                          SctStaInfo    *staInfo));

/* sct_x_001.main_34: Included protId parameter in status indication */
#ifdef SCT7
EXTERN S16 HiUiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          U32            protId,
                                          Buffer        *mBuf));
#else
EXTERN S16 HiUiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          Buffer        *mBuf));
#endif

EXTERN S16 HiUiSctFlcInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          Reason         reason));
#endif /* HI */
/* ID layer, lower interface primitives */
#ifdef ID
EXTERN S16 IdLiSctBndReq            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SpId           spId));

EXTERN S16 IdLiSctBndCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SctResult      result));
/* sct_x_001.main_38 : Added Multihoming features for IUA */
#ifdef SCT_ENDP_MULTI_IPADDR
EXTERN S16 IdLiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          SctNetAddrLst *intfAddrLst));
#else
EXTERN S16 IdLiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          CmNetAddr     *intfNAddr));
#endif

EXTERN S16 IdLiSctEndpOpenCfm       ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          UConnId        spEndpId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 IdLiSctEndpCloseReq      ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        endpId,
                                          U8             endpIdType));

EXTERN S16 IdLiSctEndpCloseCfm      ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          SctResult      result,
                                          SctCause       cause));
#ifdef SCT3
EXTERN S16 IdLiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          SctTos         tos,
                                          Buffer        *vsInfo));

#else
EXTERN S16 IdLiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          Buffer        *vsInfo));
#endif

EXTERN S16 IdLiSctAssocInd          ARGS((Pst               *pst,
                                         SuId               suId,
                                          UConnId            suEndpId,
                                          SctAssocIndParams *assocParams,
                                          Buffer            *vsInfo));
#ifdef SCT3
EXTERN S16 IdLiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctTos             tos,
                                          SctResult          result,
                                          Buffer            *vsInfo));

#else
EXTERN S16 IdLiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctResult          result,
                                          Buffer            *vsInfo));
#endif

#ifdef SCT2
EXTERN S16 IdLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      inStrms,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#else /* SCT2 */
EXTERN S16 IdLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#endif /* SCT2 */

EXTERN S16 IdLiSctTermReq           ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          Bool           abrtFlg));

EXTERN S16 IdLiSctTermInd           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          SctStatus      status,
                                          SctCause       cause,
                                          SctRtrvInfo   *rtrvInfo));

EXTERN S16 IdLiSctTermCfm           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 IdLiSctSetPriReq         ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr));

EXTERN S16 IdLiSctSetPriCfm         ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 IdLiSctHBeatReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U16            intervalTime,
                                          SctStatus      status));

EXTERN S16 IdLiSctHBeatCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 IdLiSctDatReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStrmId      strmId,
                                          Bool           unorderFlg,
                                          Bool           nobundleFlg,
                                          U16            lifeTime,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 IdLiSctDatInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctStrmId      strmId,
                                          SctDatIndType *indType,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 IdLiSctStaReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U8             staType));

EXTERN S16 IdLiSctStaCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctResult      result,
                                          SctCause       cause,
                                          SctStaInfo    *staInfo));
/* sct_x_001.main_37: Included protId parameter in status indication */
#ifdef SCT7
EXTERN S16 IdLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          U32            protId,
                                          Buffer        *mBuf));
#else
EXTERN S16 IdLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          Buffer        *mBuf));
#endif /* SCT7 */

EXTERN S16 IdLiSctFlcInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          Reason         reason));
#endif /* ID */


/* IT layer, lower interface primitives */
#ifdef IT
EXTERN S16 ItLiSctBndReq            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SpId           spId));

EXTERN S16 ItLiSctBndCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SctResult      result));
#ifdef SCT_ENDP_MULTI_IPADDR
EXTERN S16 ItLiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          SctNetAddrLst *srcAddrLst));
#else /* SCT_ENDP_MULTI_IPADDR */
EXTERN S16 ItLiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          CmNetAddr     *intfNAddr));
#endif  /* SCT_ENDP_MULTI_IPADDR */

EXTERN S16 ItLiSctEndpOpenCfm       ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          UConnId        spEndpId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 ItLiSctEndpCloseReq      ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        endpId,
                                          U8             endpIdType));

EXTERN S16 ItLiSctEndpCloseCfm      ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          SctResult      result,
                                          SctCause       cause));

#ifdef SCT3
EXTERN S16 ItLiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          SctTos         tos,
                                          Buffer        *vsInfo));
#else /* SCT3 */
EXTERN S16 ItLiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          Buffer        *vsInfo));
#endif /* SCT3 */

EXTERN S16 ItLiSctAssocInd          ARGS((Pst               *pst,
                                          SuId               suId,
                                          UConnId            suEndpId,
                                          SctAssocIndParams *assocParams,
                                          Buffer            *vsInfo));

#ifdef SCT3
EXTERN S16 ItLiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctTos             tos,
                                          SctResult          result,
                                          Buffer            *vsInfo));
#else /* SCT3 */
EXTERN S16 ItLiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctResult          result,
                                          Buffer            *vsInfo));
#endif /* SCT3 */

#ifdef SCT2
EXTERN S16 ItLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      inStrms,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#else /* SCT2 */
EXTERN S16 ItLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#endif /* SCT2 */

EXTERN S16 ItLiSctTermReq           ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          Bool           abrtFlg));

EXTERN S16 ItLiSctTermInd           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          SctStatus      status,
                                          SctCause       cause,
                                          SctRtrvInfo   *rtrvInfo));

EXTERN S16 ItLiSctTermCfm           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 ItLiSctSetPriReq         ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr));

EXTERN S16 ItLiSctSetPriCfm         ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 ItLiSctHBeatReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U16            intervalTime,
                                          SctStatus      status));

EXTERN S16 ItLiSctHBeatCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 ItLiSctDatReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStrmId      strmId,
                                          Bool           unorderFlg,
                                          Bool           nobundleFlg,
                                          U16            lifeTime,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 ItLiSctDatInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctStrmId      strmId,
                                          SctDatIndType *indType,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 ItLiSctStaReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U8             staType));

EXTERN S16 ItLiSctStaCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctResult      result,
                                          SctCause       cause,
                                          SctStaInfo    *staInfo));
/* sct_x_001.main_33: Included protId parameter in status indication */
#ifdef SCT7
EXTERN S16 ItLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
										            U32            protId,
                                          Buffer        *mBuf));
#else
EXTERN S16 ItLiSctStaInd            ARGS((Pst           *pst,
			                              SuId           suId,
			                              UConnId        suAssocId,
			                              UConnId        spAssocId,
			                              CmNetAddr     *dstNAddr,
			                              SctStatus      status,
			                              SctCause       cause,
			                              Buffer        *mBuf));
#endif /* SCT7 */

EXTERN S16 ItLiSctFlcInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          Reason         reason));
#endif /* IT */

/* SUA layer, lower interface primitives */
#ifdef SU
EXTERN S16 SuLiSctBndReq            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SpId           spId));

EXTERN S16 SuLiSctBndCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SctResult      result));

#ifdef SCT_ENDP_MULTI_IPADDR
EXTERN S16 SuLiSctEndpOpenReq        ARGS((Pst        *pst,
                      SpId         spId,
                      UConnId     suEndpId,
                      SctPort     port,
                      SctNetAddrLst     *intfNAddrLst));
#else
EXTERN S16 SuLiSctEndpOpenReq        ARGS((Pst        *pst,
                      SpId         spId,
                      UConnId     suEndpId,
                      SctPort     port,
                      CmNetAddr    *intfNAddr));
#endif

EXTERN S16 SuLiSctEndpOpenCfm       ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          UConnId        spEndpId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 SuLiSctEndpCloseReq      ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        endpId,
                                          U8             endpIdType));

EXTERN S16 SuLiSctEndpCloseCfm      ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          SctResult      result,
                                          SctCause       cause));

#ifdef SCT3
EXTERN S16 SuLiSctAssocReq        ARGS((Pst        *pst,
                      SpId         spId,
                      UConnId     spEndpId,
                      UConnId     suAssocId,
                      CmNetAddr    *priDstNAddr,
                      SctPort     dstPort,
                      SctStrmId     outStrms,
                      SctNetAddrLst *dstNAddrLst,
                      SctNetAddrLst *srcNAddrLst,
                      SctTos     tos,
                      Buffer    *vsInfo));
#else
EXTERN S16 SuLiSctAssocReq        ARGS((Pst        *pst,
                      SpId         spId,
                      UConnId     spEndpId,
                      UConnId     suAssocId,
                      CmNetAddr    *priDstNAddr,
                      SctPort     dstPort,
                      SctStrmId     outStrms,
                      SctNetAddrLst *dstNAddrLst,
                      SctNetAddrLst *srcNAddrLst,
                      Buffer    *vsInfo));
#endif /* SCT3 */

EXTERN S16 SuLiSctAssocInd          ARGS((Pst               *pst,
                                          SuId               suId,
                                          UConnId            suEndpId,
                                          SctAssocIndParams *assocParams,
                                          Buffer            *vsInfo));

#ifdef SCT3
EXTERN S16 SuLiSctAssocRsp        ARGS((Pst            *pst,
                      SpId             spId,
                      UConnId         spEndpId,
                      SctAssocIndParams *assocIndParams,
                      SctTos         tos,
                      SctResult         result,
                      Buffer        *vsInfo));

#else
EXTERN S16 SuLiSctAssocRsp        ARGS((Pst            *pst,
                      SpId             spId,
                      UConnId         spEndpId,
                      SctAssocIndParams *assocIndParams,
                      SctResult         result,
                      Buffer        *vsInfo));

#endif /*SCT3 */

#ifdef SCT2
EXTERN S16 SuLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      inStrms,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#else /* SCT2 */
EXTERN S16 SuLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#endif /* SCT2 */

EXTERN S16 SuLiSctTermReq           ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          Bool           abrtFlg));

EXTERN S16 SuLiSctTermInd           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          SctStatus      status,
                                          SctCause       cause,
                                          SctRtrvInfo   *rtrvInfo));

EXTERN S16 SuLiSctTermCfm           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 SuLiSctSetPriReq         ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr));

EXTERN S16 SuLiSctSetPriCfm         ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 SuLiSctHBeatReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U16            intervalTime,
                                          SctStatus      status));

EXTERN S16 SuLiSctHBeatCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 SuLiSctDatReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStrmId      strmId,
                                          Bool           unorderFlg,
                                          Bool           nobundleFlg,
                                          U16            lifeTime,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 SuLiSctDatInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctStrmId      strmId,
                                          SctDatIndType *indType,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 SuLiSctStaReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U8             staType));

EXTERN S16 SuLiSctStaCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctResult      result,
                                          SctCause       cause,
                                          SctStaInfo    *staInfo));
/* sct_x_001.main_37: Included protId parameter in status indication */
#ifdef SCT7
EXTERN S16 SuLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          U32            protId,
                                          Buffer        *mBuf));
#else
EXTERN S16 SuLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          Buffer        *mBuf));
#endif /* SCT7 */

EXTERN S16 SuLiSctFlcInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          Reason         reason));
#endif /* SU */

/* M2PA layer, lower interface primitives */
#ifdef MX
EXTERN S16 MxLiSctBndReq            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SpId           spId));

EXTERN S16 MxLiSctBndCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SctResult      result));

#ifdef SCT_ENDP_MULTI_IPADDR  /*sct_x_001.main_22: mx001.101 Addition */
EXTERN S16 MxLiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          SctNetAddrLst  *intfAddrLst));
#else /* else SCT_ENDP_MULTI_IPADDR sct_x_001.main_22:mx001.101 Addition */
EXTERN S16 MxLiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          CmNetAddr      *intfAddrLst));
#endif /* end SCT_ENDP_MULTI_IPADDR sct_x_001.main_22:mx001.101 Addition */

EXTERN S16 MxLiSctEndpOpenCfm       ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          UConnId        spEndpId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 MxLiSctEndpCloseReq      ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        endpId,
                                          U8             endpIdType));

EXTERN S16 MxLiSctEndpCloseCfm      ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          SctResult      result,
                                          SctCause       cause));
#ifdef SCT3
EXTERN S16 MxLiSctAssocReq          ARGS((Pst           *pst,
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
EXTERN S16 MxLiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          Buffer        *vsInfo));

#endif

EXTERN S16 MxLiSctAssocInd          ARGS((Pst               *pst,
                                          SuId               suId,
                                          UConnId            suEndpId,
                                          SctAssocIndParams *assocParams,
                                          Buffer            *vsInfo));

#ifdef SCT3
EXTERN S16 MxLiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctTos        tos,
                                          SctResult          result,
                                          Buffer            *vsInfo));
#else
EXTERN S16 MxLiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctResult          result,
                                          Buffer            *vsInfo));

#endif

EXTERN S16 MxLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));

EXTERN S16 MxLiSctTermReq           ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          Bool           abrtFlg));

EXTERN S16 MxLiSctTermInd           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          SctStatus      status,
                                          SctCause       cause,
                                          SctRtrvInfo   *rtrvInfo));

EXTERN S16 MxLiSctTermCfm           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 MxLiSctSetPriReq         ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr));

EXTERN S16 MxLiSctSetPriCfm         ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 MxLiSctHBeatReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U16            intervalTime,
                                          SctStatus      status));

EXTERN S16 MxLiSctHBeatCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 MxLiSctDatReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStrmId      strmId,
                                          Bool           unorderFlg,
                                          Bool           nobundleFlg,
                                          U16            lifeTime,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 MxLiSctDatInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctStrmId      strmId,
                                          SctDatIndType *indType,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 MxLiSctStaReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U8             staType));

EXTERN S16 MxLiSctStaCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctResult      result,
                                          SctCause       cause,
                                          SctStaInfo    *staInfo));
/* sct_x_001.main_37: Included protId parameter in status indication */
#ifdef SCT7
EXTERN S16 MxLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          U32            protId,
                                          Buffer        *mBuf));
#else
EXTERN S16 MxLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          Buffer        *mBuf));
#endif /* SCT7 */

EXTERN S16 MxLiSctFlcInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          Reason         reason));
#endif /* MX */


/* M2UA layer, lower interface primitives */
#ifdef MW
EXTERN S16 MwLiSctBndReq            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SpId           spId));

EXTERN S16 MwLiSctBndCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SctResult      result));
/* sct_x_001.main_25 incoprating multiple ip support*/
#ifdef SCT_ENDP_MULTI_IPADDR
EXTERN S16 MwLiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          SctNetAddrLst *intfNAddrLst));
#else  /* SCT_ENDP_MULTI_IPADDR */
EXTERN S16 MwLiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          CmNetAddr     *intfNAddr));
#endif /*SCT_ENDP_MULTI_IPADDR*/
EXTERN S16 MwLiSctEndpOpenCfm       ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          UConnId        spEndpId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 MwLiSctEndpCloseReq      ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        endpId,
                                          U8             endpIdType));

EXTERN S16 MwLiSctEndpCloseCfm      ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          SctResult      result,
                                          SctCause       cause));
/*sct_x_001.main_23 Added TOS support in M2UA*/
#ifdef SCT3
EXTERN S16 MwLiSctAssocReq          ARGS((Pst           *pst,
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
#else /*SCT3*/
EXTERN S16 MwLiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          Buffer        *vsInfo));
#endif /*SCT3*/


EXTERN S16 MwLiSctAssocInd          ARGS((Pst               *pst,
                                          SuId               suId,
                                          UConnId            suEndpId,
                                          SctAssocIndParams *assocParams,
                                          Buffer            *vsInfo));

/*sct_x_001.main_23 Added TOS support in M2UA*/
#ifdef SCT3
EXTERN S16 MwLiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctTos             tos,
                                          SctResult          result,
                                          Buffer            *vsInfo));
#else 
EXTERN S16 MwLiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctResult          result,
                                          Buffer            *vsInfo));
#endif /*SCT3*/


#ifdef SCT2
EXTERN S16 MwLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      inStrms,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#else /* SCT2 */
EXTERN S16 MwLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#endif /* SCT2 */

EXTERN S16 MwLiSctTermReq           ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          Bool           abrtFlg));

EXTERN S16 MwLiSctTermInd           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          SctStatus      status,
                                          SctCause       cause,
                                          SctRtrvInfo   *rtrvInfo));

EXTERN S16 MwLiSctTermCfm           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 MwLiSctSetPriReq         ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr));

EXTERN S16 MwLiSctSetPriCfm         ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 MwLiSctHBeatReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U16            intervalTime,
                                          SctStatus      status));

EXTERN S16 MwLiSctHBeatCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 MwLiSctDatReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStrmId      strmId,
                                          Bool           unorderFlg,
                                          Bool           nobundleFlg,
                                          U16            lifeTime,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 MwLiSctDatInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctStrmId      strmId,
                                          SctDatIndType *indType,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 MwLiSctStaReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U8             staType));

EXTERN S16 MwLiSctStaCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctResult      result,
                                          SctCause       cause,
                                          SctStaInfo    *staInfo));
/* sct_x_001.man_37: Included protId parameter in status indication */
#ifdef SCT7
EXTERN S16 MwLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          U32            protId,
                                          Buffer        *mBuf));
#else
EXTERN S16 MwLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          Buffer        *mBuf));
#endif

EXTERN S16 MwLiSctFlcInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          Reason         reason));
#endif /* MW */
#ifdef IB
EXTERN S16 IbLiSctBndReq            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SpId           spId));

EXTERN S16 IbLiSctBndCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          U16            status));

EXTERN S16 IbLiSctEndpOpenCfm       ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          UConnId        spEndpId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 IbLiSctEndpCloseCfm      ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          SctResult      result,
                                          SctCause       cause));

/* sct_x_001.main_28  : Fix for ccpu00094751 */
#ifdef SCT_ENDP_MULTI_IPADDR
EXTERN S16 IbLiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          SctNetAddrLst *intfNAddr));
#else 
EXTERN S16 IbLiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          CmNetAddr     *intfNAddr));
#endif

EXTERN S16 IbLiSctEndpCloseReq      ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        endpId,
                                          U8             endpIdType));

EXTERN S16 IbLiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          Buffer        *vsInfo));


EXTERN S16 IbLiSctAssocInd          ARGS((Pst               *pst,
                                          SuId               suId,
                                          UConnId            suEndpId,
                                          SctAssocIndParams *assocParams,
                                          Buffer            *vsInfo));

EXTERN S16 IbLiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctResult          result,
                                          Buffer            *vsInfo));

EXTERN S16 IbLiSctSetPriReq         ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr));

EXTERN S16 IbLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      inStrms,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));

EXTERN S16 IbLiSctTermReq           ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          Bool           abrtFlg));

EXTERN S16 IbLiSctTermInd           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          SctStatus      status,
                                          SctCause       cause,
                                          SctRtrvInfo   *rtrvInfo));

EXTERN S16 IbLiSctTermCfm           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 IbLiSctDatInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctStrmId      strmId,
                                          SctDatIndType *indType,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 IbLiSctStaReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U8             staType));
/* sct_x_001.main_37: Included protId parameter in status indication */
#ifdef SCT7
EXTERN S16 IbLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          U32            protId,
                                          Buffer        *mBuf));
#else
EXTERN S16 IbLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          Buffer        *mBuf));
#endif /* SCT7 */
EXTERN S16 IbLiSctFlcInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          Reason         reason));
EXTERN S16 IbLiSctHBeatCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 ItLiSctDatReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStrmId      strmId,
                                          Bool           unorderFlg,
                                          Bool           nobundleFlg,
                                          U16            lifeTime,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 IbLiSctStaCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctResult      result,
                                          SctCause       cause,
                                          SctStaInfo    *staInfo));

EXTERN S16 IbLiSctSetPriCfm         ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 IbLiSctHBeatReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U16            intervalTime,
                                          SctStatus      status));

EXTERN S16 IbLiSctDatReq           ARGS ((
                                          Pst           *pst,
                                          SpId          spId,             /* Service provider SAP ID */
                                          UConnId       spAssocId,        /* Service provider association ID */
                                          CmNetAddr     *dstNAddr,         /* New primary network address */
                                          SctStrmId     strmId,           /* Stream ID */
                                          Bool          unorderFlg,       /* unordered delivery */
                                          Bool          nobundleFlg,      /* no bundling  */
                                          U16           lifeTime,         /* datagram lifetime value */
                                          U32           protId,           /* Protocol ID */
                                          Buffer        *mBuf              /* message buffer */
                                         ));
#endif /* IB */

/* GCP layer, lower interface primitives */
#ifdef MG
EXTERN S16 MgLiSctBndReq            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SpId           spId));

EXTERN S16 MgLiSctBndCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SctResult      result));

#ifdef SCT_ENDP_MULTI_IPADDR
EXTERN S16 MgLiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          SctNetAddrLst *intfNAddrLst));
#else /* SCT_ENDP_MULTI_IPADDR */
EXTERN S16 MgLiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          CmNetAddr     *intfNAddr));
#endif /* SCT_ENDP_MULTI_IPADDR */

EXTERN S16 MgLiSctEndpOpenCfm       ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          UConnId        spEndpId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 MgLiSctEndpCloseReq      ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        endpId,
                                          U8             endpIdType));

EXTERN S16 MgLiSctEndpCloseCfm      ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          SctResult      result,
                                          SctCause       cause));

#ifdef SCT3
EXTERN S16 MgLiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          SctTos         tos,
Buffer        *vsInfo));
#else /* SCT3 */
EXTERN S16 MgLiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                  Buffer        *vsInfo));
#endif /* SCT3 */

EXTERN S16 MgLiSctAssocInd          ARGS((Pst               *pst,
                                          SuId               suId,
                                          UConnId            suEndpId,
                                          SctAssocIndParams *assocParams,
Buffer            *vsInfo));

#ifdef SCT3
EXTERN S16 MgLiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctTos             tos,
                                          SctResult          result,
Buffer            *vsInfo));
#else /* SCT3 */
EXTERN S16 MgLiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctResult          result,
                                          Buffer            *vsInfo));
#endif /* SCT3 */

#ifdef SCT2
EXTERN S16 MgLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      inStrms,
                                          SctStrmId      outStrms,
Buffer        *vsInfo));
#else /* SCT2 */
EXTERN S16 MgLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
Buffer        *vsInfo));
#endif /* SCT2 */

EXTERN S16 MgLiSctTermReq           ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          Bool           abrtFlg));

EXTERN S16 MgLiSctTermInd           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          SctStatus      status,
                                          SctCause       cause,
                                          SctRtrvInfo   *rtrvInfo));

EXTERN S16 MgLiSctTermCfm           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 MgLiSctSetPriReq         ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr));

EXTERN S16 MgLiSctSetPriCfm         ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 MgLiSctHBeatReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U16            intervalTime,
                                          SctStatus      status));

EXTERN S16 MgLiSctHBeatCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 MgLiSctDatReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStrmId      strmId,
                                          Bool           unorderFlg,
                                          Bool           nobundleFlg,
                                          U16            lifeTime,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 MgLiSctDatInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctStrmId      strmId,
                                          SctDatIndType *indType,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 MgLiSctStaReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U8             staType));

EXTERN S16 MgLiSctStaCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctResult      result,
                                          SctCause       cause,
                                          SctStaInfo    *staInfo));
/* sct_x_001.main_37: Included protId parameter in status indication */
#ifdef SCT7
EXTERN S16 MgLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          U32            protId,
                                          Buffer        *mBuf));
#else
EXTERN S16 MgLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          Buffer        *mBuf));
#endif /* SCT7 */
EXTERN S16 MgLiSctFlcInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          Reason         reason));
#endif /* MG */

/* Adding the new Dummy Functions under SIP TA Flag*/
#ifdef DM

EXTERN S16 DmLiSctBndReq            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SpId           spId));

EXTERN S16 DmLiSctBndCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SctResult      result));

#ifdef SCT_ENDP_MULTI_IPADDR
EXTERN S16 DmLiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          SctNetAddrLst *intfNAddrLst));
#else /* SCT_ENDP_MULTI_IPADDR */
EXTERN S16 DmLiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          CmNetAddr     *intfNAddr));
#endif /* SCT_ENDP_MULTI_IPADDR */

EXTERN S16 DmLiSctEndpOpenCfm       ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          UConnId        spEndpId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 DmLiSctEndpCloseReq      ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        endpId,
                                          U8             endpIdType));

EXTERN S16 DmLiSctEndpCloseCfm      ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          SctResult      result,
                                          SctCause       cause));

#ifdef SCT3
EXTERN S16 DmLiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          SctTos         tos,
Buffer        *vsInfo));
#else /* SCT3 */
EXTERN S16 DmLiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
Buffer        *vsInfo));
#endif /* SCT3 */

EXTERN S16 DmLiSctAssocInd          ARGS((Pst               *pst,
                                          SuId               suId,
                                          UConnId            suEndpId,
                                          SctAssocIndParams *assocParams,
Buffer            *vsInfo));

#ifdef SCT3
EXTERN S16 DmLiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctTos             tos,
                                          SctResult          result,
Buffer            *vsInfo));
#else /* SCT3 */
EXTERN S16 DmLiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctResult          result,
Buffer            *vsInfo));
#endif /* SCT3 */

#ifdef SCT2
EXTERN S16 DmLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      inStrms,
                                          SctStrmId      outStrms,
Buffer        *vsInfo));
#else /* SCT2 */
EXTERN S16 DmLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
Buffer        *vsInfo));
#endif /* SCT2 */

EXTERN S16 DmLiSctTermReq           ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          Bool           abrtFlg));

EXTERN S16 DmLiSctTermInd           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          SctStatus      status,
                                          SctCause       cause,
                                          SctRtrvInfo   *rtrvInfo));

EXTERN S16 DmLiSctTermCfm           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 DmLiSctSetPriReq         ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr));

EXTERN S16 DmLiSctSetPriCfm         ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 DmLiSctHBeatReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U16            intervalTime,
                                          SctStatus      status));

EXTERN S16 DmLiSctHBeatCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 DmLiSctDatReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStrmId      strmId,
                                          Bool           unorderFlg,
                                          Bool           nobundleFlg,
                                          U16            lifeTime,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 DmLiSctDatInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctStrmId      strmId,
                                          SctDatIndType *indType,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 DmLiSctStaReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U8             staType));

EXTERN S16 DmLiSctStaCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctResult      result,
                                          SctCause       cause,
                                          SctStaInfo    *staInfo));
/* sct_x_001.main_37: Included protId parameter in status indication */
#ifdef SCT7
EXTERN S16 DmLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          U32            protId,
                                          Buffer        *mBuf));
#else
EXTERN S16 DmLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          Buffer        *mBuf));
#endif /* SCT7*/

EXTERN S16 DmLiSctFlcInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          Reason         reason));

#endif /* DM */

/* Adding the new Dummy Functions */
#ifdef DM
/* forward references */
EXTERN S16 DmUiSctBndReq ARGS((
         Pst *pst,
         SuId suId,
         SpId spId
         ));

/* sct_x_001.main_30 Updated for S1AP release 1.1 */
#ifdef SCT_ENDP_MULTI_IPADDR
EXTERN S16 DmUiSctEndpOpenReq ARGS((
         Pst           *pst,
         SpId           spId,
         UConnId        suEndpId,
         SctPort        port,
         SctNetAddrLst *intfNAddrLst
         ));
#else
EXTERN S16 DmUiSctEndpOpenReq ARGS((
         Pst           *pst,
         SpId           spId,
         UConnId        suEndpId,
         SctPort        port,
         CmNetAddr     *intfNAddr
         ));
#endif

EXTERN S16 DmUiSctEndpCloseReq ARGS((
         Pst *pst,
         SpId spId,
         UConnId endpId,
         U8 endpIdType
         ));

#ifdef SCT3
EXTERN S16 DmUiSctAssocReq ARGS((
         Pst *pst,
         SpId spId,
         UConnId spEndpId,
         UConnId suAssocId,
         CmNetAddr *priDstNAddr,
         SctPort dstPort,
         SctStrmId outStrms,
         SctNetAddrLst *dstNAddrLst,
         SctNetAddrLst *srcNAddrLst,
         SctTos          tos,
         Buffer *vsInfo
         ));
#else
EXTERN S16 DmUiSctAssocReq ARGS((
         Pst *pst,
         SpId spId,
         UConnId spEndpId,
         UConnId suAssocId,
         CmNetAddr *priDstNAddr,
         SctPort dstPort,
         SctStrmId outStrms,
         SctNetAddrLst *dstNAddrLst,
         SctNetAddrLst *srcNAddrLst,
         Buffer *vsInfo
         ));
#endif
#ifdef SCT3
EXTERN S16 DmUiSctAssocRsp ARGS((
         Pst *pst,
         SpId spId,
         UConnId spAssocId,
         SctAssocIndParams *assocIndParams,
         SctTos    tos,
         SctResult result,
         Buffer *vsInfo
         ));
#else
EXTERN S16 DmUiSctAssocRsp ARGS((
         Pst *pst,
         SpId spId,
         UConnId spAssocId,
         SctAssocIndParams *assocIndParams,
         SctResult result,
         Buffer *vsInfo
         ));
#endif

EXTERN S16 DmUiSctTermReq ARGS((
         Pst *pst,
         SpId spId,
         UConnId assocId,
         U8 assocIdType,
         Bool abrtFlg
         ));

EXTERN S16 DmUiSctSetPriReq ARGS((
         Pst *pst,
         SpId spId,
         UConnId spAssocId,
         CmNetAddr *dstNAddr
         ));

EXTERN S16 DmUiSctHBeatReq ARGS((
         Pst            *pst,
         SpId            spId,
         UConnId         spAssocId,
         CmNetAddr      *dstNAddr,
         U16             intervalTime,
         SctStatus       status
         ));

EXTERN S16 DmUiSctDatReq ARGS((
         Pst *pst,
         SpId spId,
         UConnId spAssocId,
         CmNetAddr *dstNAddr,
         SctStrmId strmId,
         Bool unorderFlg,
         Bool nobundleFlg,
         U16 lifetime,
         U32 protId,
         Buffer *mBuf
         ));

EXTERN S16 DmUiSctStaReq ARGS((
         Pst *pst,
         SpId spId,
         UConnId spAssocId,
         CmNetAddr *dstNAddr,
         U8 staType
         ));
/* sct_x_001.main_32: Updated for S1AP phase2 release */

#ifdef SCT2
EXTERN S16 DmUiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      inStrms,
                                          SctStrmId      outStrms,
Buffer        *vsInfo));
#else /* SCT2 */
EXTERN S16 DmUiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
Buffer        *vsInfo));
#endif /* SCT2 */


EXTERN S16 DmUiSctTermCfm           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 DmUiSctBndCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SctResult      result));

EXTERN S16 DmUiSctEndpOpenCfm       ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          UConnId        spEndpId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 DmUiSctEndpCloseCfm      ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 DmUiSctAssocInd          ARGS((Pst               *pst,
                                          SuId               suId,
                                          UConnId            suEndpId,
                                          SctAssocIndParams *assocParams,
Buffer            *vsInfo));


EXTERN S16 DmUiSctTermInd           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          SctStatus      status,
                                          SctCause       cause,
                                          SctRtrvInfo   *rtrvInfo));

EXTERN S16 DmUiSctSetPriCfm         ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 DmUiSctHBeatCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 DmUiSctDatInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctStrmId      strmId,
                                          SctDatIndType *indType,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 DmUiSctStaCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctResult      result,
                                          SctCause       cause,
                                          SctStaInfo    *staInfo));
/* sct_x_001.main_37: Included protId parameter in status indication */
#ifdef SCT7
EXTERN S16 DmUiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          U32            protId,
                                          Buffer        *mBuf));
#else
EXTERN S16 DmUiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          Buffer        *mBuf));
#endif /* SCT7 */

EXTERN S16 DmUiSctFlcInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          Reason         reason));


#endif /* DM */


/* MZ(M1UA) layer, lower interface primitives */
#ifdef MZ 
EXTERN S16 MzLiSctBndReq            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SpId           spId));

EXTERN S16 MzLiSctBndCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SctResult      result));

#ifdef SCT_ENDP_MULTI_IPADDR
EXTERN S16 MzLiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          SctNetAddrLst *intfNAddrLst));
#else /* SCT_ENDP_MULTI_IPADDR */
EXTERN S16 MzLiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          CmNetAddr     *intfNAddr));
#endif /* SCT_ENDP_MULTI_IPADDR */

EXTERN S16 MzLiSctEndpOpenCfm       ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          UConnId        spEndpId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 MzLiSctEndpCloseReq      ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        endpId,
                                          U8             endpIdType));

EXTERN S16 MzLiSctEndpCloseCfm      ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 MzLiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          Buffer        *vsInfo));

EXTERN S16 MzLiSctAssocInd          ARGS((Pst               *pst,
                                          SuId               suId,
                                          UConnId            suEndpId,
                                          SctAssocIndParams *assocParams,
                                          Buffer            *vsInfo));

EXTERN S16 MzLiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctResult          result,
                                          Buffer            *vsInfo));

#ifdef SCT2
EXTERN S16 MzLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      inStrms,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#else /* SCT2 */
EXTERN S16 MzLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#endif /* SCT2 */

EXTERN S16 MzLiSctTermReq           ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          Bool           abrtFlg));

EXTERN S16 MzLiSctTermInd           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          SctStatus      status,
                                          SctCause       cause,
                                          SctRtrvInfo   *rtrvInfo));

EXTERN S16 MzLiSctTermCfm           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 MzLiSctSetPriReq         ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr));

EXTERN S16 MzLiSctSetPriCfm         ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 MzLiSctHBeatReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U16            intervalTime,
                                          SctStatus      status));

EXTERN S16 MzLiSctHBeatCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 MzLiSctDatReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStrmId      strmId,
                                          Bool           unorderFlg,
                                          Bool           nobundleFlg,
                                          U16            lifeTime,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 MzLiSctDatInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctStrmId      strmId,
                                          SctDatIndType *indType,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 MzLiSctStaReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U8             staType));

EXTERN S16 MzLiSctStaCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctResult      result,
                                          SctCause       cause,
                                          SctStaInfo    *staInfo));
/* sct_x_001.main_37: Included protId parameter in status indication */
#ifdef SCT7
EXTERN S16 MzLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          U32            protId,
                                          Buffer        *mBuf));
#else
EXTERN S16 MzLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          Buffer        *mBuf));
#endif /* SCT7 */

EXTERN S16 MzLiSctFlcInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          Reason         reason));

#endif /* MZ */

#ifdef LCSCT
EXTERN S16 cmPkSctBndReq            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SpId           spId));

EXTERN S16 cmPkSctBndCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SctResult      result));

#ifdef SCT_ENDP_MULTI_IPADDR
EXTERN S16 cmPkSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          SctNetAddrLst *srcAddrLst));
#else  /* SCT_ENDP_MULTI_IPADDR */
EXTERN S16 cmPkSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          CmNetAddr     *intfNAddr));
#endif /* SCT_ENDP_MULTI_IPADDR */

EXTERN S16 cmPkSctEndpOpenCfm       ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          UConnId        spEndpId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 cmPkSctEndpCloseReq      ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        endpId,
                                          U8             endpIdType));

EXTERN S16 cmPkSctEndpCloseCfm      ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          SctResult      result,
                                          SctCause       cause));

#ifdef SCT3
EXTERN S16 cmPkSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          SctTos         tos,
                                          Buffer        *vsInfo));
#else /* SCT3 */
EXTERN S16 cmPkSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          Buffer        *vsInfo));
#endif /* SCT3 */

EXTERN S16 cmPkSctAssocInd          ARGS((Pst               *pst,
                                          SuId               suId,
                                          UConnId            suEndpId,
                                          SctAssocIndParams *assocParams,
                                          Buffer            *vsInfo));

#ifdef SCT3
EXTERN S16 cmPkSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocParams,
                                          SctTos             tos,
                                          SctResult          result,
                                          Buffer            *vsInfo));
#else /* SCT3 */
EXTERN S16 cmPkSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocParams,
                                          SctResult          result,
                                          Buffer            *vsInfo));
#endif /* SCT3 */

#ifdef SCT2
EXTERN S16 cmPkSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      inStrms,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#else /* SCT2 */
EXTERN S16 cmPkSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#endif /* SCT2 */
#ifdef S1SIMAPP
EXTERN S16 cmPkSctTermReq           ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          Bool           abrtFlg,
                                          U8             cause));
#else
EXTERN S16 cmPkSctTermReq           ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          Bool           abrtFlg));
#endif

EXTERN S16 cmPkSctTermInd           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          SctStatus      status,
                                          SctCause       cause,
                                          SctRtrvInfo   *rtrvInfo));

EXTERN S16 cmPkSctTermCfm           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 cmPkSctSetPriReq         ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr));

EXTERN S16 cmPkSctSetPriCfm         ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 cmPkSctHBeatReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U16            intervalTime,
                                          SctStatus      status));

EXTERN S16 cmPkSctHBeatCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 cmPkSctDatReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStrmId      strmId,
                                          Bool           unorderFlg,
                                          Bool           nobundleFlg,
                                          U16            lifeTime,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 cmPkSctDatInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctStrmId      strmId,
                                          SctDatIndType *indType,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 cmPkSctStaReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U8             staType));

EXTERN S16 cmPkSctStaCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctResult      result,
                                          SctCause       cause,
                                          SctStaInfo    *staInfo));
/* sct_x_001.main_33: Included protId parameter in status indication */
#ifdef SCT7
EXTERN S16 cmPkSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          U32            protId,
										            Buffer        *mBuf));
#else
EXTERN S16 cmPkSctStaInd            ARGS((Pst           *pst,
			                              SuId           suId,
			                              UConnId        suAssocId,
			                              UConnId        spAssocId,
			                              CmNetAddr     *dstNAddr,
			                              SctStatus      status,
			                              SctCause       cause,
			                              Buffer        *mBuf));
#endif /* SCT7 */

EXTERN S16 cmPkSctFlcInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          Reason         reason));

/* Primitive Unpacking functions */
EXTERN S16 cmUnpkSctBndReq       ARGS((SctBndReq func, Pst *pst, Buffer *mBuf));

EXTERN S16 cmUnpkSctBndCfm       ARGS((SctBndCfm func, Pst *pst, Buffer *mBuf));

EXTERN S16 cmUnpkSctEndpOpenReq  ARGS((SctEndpOpenReq func, Pst *pst, Buffer *mBuf));

EXTERN S16 cmUnpkSctEndpOpenCfm  ARGS((SctEndpOpenCfm func, Pst *pst, Buffer *mBuf));

EXTERN S16 cmUnpkSctEndpCloseReq ARGS((SctEndpCloseReq func, Pst *pst, Buffer *mBuf));

EXTERN S16 cmUnpkSctEndpCloseCfm ARGS((SctEndpCloseCfm func, Pst *pst, Buffer *mBuf));

EXTERN S16 cmUnpkSctAssocReq     ARGS((SctAssocReq func, Pst *pst, Buffer *mBuf));

EXTERN S16 cmUnpkSctAssocInd     ARGS((SctAssocInd func, Pst *pst, Buffer *mBuf));

EXTERN S16 cmUnpkSctAssocRsp     ARGS((SctAssocRsp func, Pst *pst, Buffer *mBuf));

EXTERN S16 cmUnpkSctAssocCfm     ARGS((SctAssocCfm func, Pst *pst, Buffer *mBuf));

EXTERN S16 cmUnpkSctTermReq      ARGS((SctTermReq func, Pst *pst, Buffer *mBuf));

EXTERN S16 cmUnpkSctTermInd      ARGS((SctTermInd func, Pst *pst, Buffer *mBuf));

EXTERN S16 cmUnpkSctTermCfm      ARGS((SctTermCfm func, Pst *pst, Buffer *mBuf));

EXTERN S16 cmUnpkSctSetPriReq    ARGS((SctSetPriReq func, Pst *pst, Buffer *mBuf));

EXTERN S16 cmUnpkSctSetPriCfm    ARGS((SctSetPriCfm func, Pst *pst, Buffer *mBuf));

EXTERN S16 cmUnpkSctHBeatReq     ARGS((SctHBeatReq func, Pst *pst, Buffer *mBuf));

EXTERN S16 cmUnpkSctHBeatCfm     ARGS((SctHBeatCfm func, Pst *pst, Buffer *mBuf));

EXTERN S16 cmUnpkSctDatReq       ARGS((SctDatReq func, Pst *pst, Buffer *mBuf));

EXTERN S16 cmUnpkSctDatInd       ARGS((SctDatInd func, Pst *pst, Buffer *mBuf));

EXTERN S16 cmUnpkSctStaReq       ARGS((SctStaReq func, Pst *pst, Buffer *mBuf));

EXTERN S16 cmUnpkSctStaCfm       ARGS((SctStaCfm func, Pst *pst, Buffer *mBuf));

EXTERN S16 cmUnpkSctStaInd       ARGS((SctStaInd func, Pst *pst, Buffer *mBuf));

EXTERN S16 cmUnpkSctFlcInd       ARGS((SctFlcInd func, Pst *pst, Buffer *mBuf));

/* other packing functions */
EXTERN S16 cmPkSctNetAddrLst     ARGS((SctNetAddrLst *pkParam, Buffer *mBuf));
EXTERN S16 cmUnpkSctNetAddrLst   ARGS((SctNetAddrLst *pkParam, Buffer *mBuf));

#endif /* LCSCT */

#ifdef DV  /* LDF-M3UA */

EXTERN S16 DvUiSctBndCfm            ARGS((Pst *pst, SuId suId, SctResult result));
EXTERN S16 DvUiSctEndpOpenCfm       ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          UConnId        spEndpId,
                                          SctResult      result,
                                          SctCause       cause));
EXTERN S16 DvUiSctEndpCloseCfm      ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          SctResult      result,
                                          SctCause       cause));
EXTERN S16 DvUiSctAssocInd          ARGS((Pst               *pst,
                                          SuId               suId,
                                          UConnId            suEndpId,
                                          SctAssocIndParams *assocParams,
                                          Buffer            *vsInfo));
/* sct_x_001.main_39: Added handling of SCT2 compile time flag for M3UA LDF */
#ifdef SCT2
EXTERN S16 DvUiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      inStrms,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#else
EXTERN S16 DvUiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#endif
EXTERN S16 DvUiSctTermInd           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          SctStatus      status,
                                          SctCause       cause,
                                          SctRtrvInfo   *rtrvInfo));
EXTERN S16 DvUiSctTermCfm           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));
EXTERN S16 DvUiSctSetPriCfm         ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));
EXTERN S16 DvUiSctHBeatCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctResult      result,
                                          SctCause       cause));
EXTERN S16 DvUiSctDatInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctStrmId      strmId,
                                          SctDatIndType *indType,
                                          U32            protId,
                                          Buffer        *mBuf));
EXTERN S16 DvUiSctStaCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctResult      result,
                                          SctCause       cause,
                                          SctStaInfo    *staInfo));
/* sct_x_001.main_33: Included protId parameter in status indication */
#ifdef SCT7
EXTERN S16 DvUiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          U32            protId,
                                          Buffer        *mBuf));
#else
EXTERN S16 DvUiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          Buffer        *mBuf));
#endif /* SCT7 */
EXTERN S16 DvUiSctFlcInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          Reason         reason));
#endif /* DV */

#ifdef SO
EXTERN S16 SoLiSctBndReq            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SpId           spId));

EXTERN S16 SoLiSctBndCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SctResult      result));

#ifdef SCT_ENDP_MULTI_IPADDR
EXTERN S16 SoLiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          SctNetAddrLst *intfNAddrLst));
#else /* SCT_ENDP_MULTI_IPADDR */
EXTERN S16 SoLiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          CmNetAddr     *intfNAddr));
#endif /* SCT_ENDP_MULTI_IPADDR */

EXTERN S16 SoLiSctEndpOpenCfm       ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          UConnId        spEndpId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 SoLiSctEndpCloseReq      ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        endpId,
                                          U8             endpIdType));

EXTERN S16 SoLiSctEndpCloseCfm      ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          SctResult      result,
                                          SctCause       cause));

#ifdef SCT3
EXTERN S16 SoLiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          SctTos          tos,
                                          Buffer        *vsInfo));
#else
EXTERN S16 SoLiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          Buffer        *vsInfo));

#endif


EXTERN S16 SoLiSctAssocInd          ARGS((Pst               *pst,
                                          SuId               suId,
                                          UConnId            suEndpId,
                                          SctAssocIndParams *assocParams,
                                          Buffer            *vsInfo));

#ifdef SCT3
EXTERN S16 SoLiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctTos             tos,
                                          SctResult          result,
                                          Buffer            *vsInfo));
#else
EXTERN S16 SoLiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctResult          result,
                                          Buffer            *vsInfo));
#endif

#ifdef SCT2
EXTERN S16 SoLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      inStrms,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#else /* SCT2 */
EXTERN S16 SoLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#endif /* SCT2 */

EXTERN S16 SoLiSctTermReq           ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          Bool           abrtFlg));

EXTERN S16 SoLiSctTermInd           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          SctStatus      status,
                                          SctCause       cause,
                                          SctRtrvInfo   *rtrvInfo));

EXTERN S16 SoLiSctTermCfm           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 SoLiSctSetPriReq         ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr));

EXTERN S16 SoLiSctSetPriCfm         ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 SoLiSctHBeatReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U16            intervalTime,
                                          SctStatus      status));

EXTERN S16 SoLiSctHBeatCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 SoLiSctDatReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStrmId      strmId,
                                          Bool           unorderFlg,
                                          Bool           nobundleFlg,
                                          U16            lifeTime,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 SoLiSctDatInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctStrmId      strmId,
                                          SctDatIndType *indType,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 SoLiSctStaReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U8             staType));

EXTERN S16 SoLiSctStaCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctResult      result,
                                          SctCause       cause,
                                          SctStaInfo    *staInfo));
/* sct_x_001.main_37: Included protId parameter in status indication */
#ifdef SCT7
EXTERN S16 SoLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          U32            protId,
                                          Buffer        *mBuf));
#else
EXTERN S16 SoLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          Buffer        *mBuf));
#endif /* SCT7 */

EXTERN S16 SoLiSctFlcInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          Reason         reason));
#endif /* SO */

/*sct_x_001.main_19: Diameter added as new SCTP user*/

#ifdef AQ
EXTERN S16 AqLiSctBndReq            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SpId           spId));

EXTERN S16 AqLiSctBndCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SctResult      result));

#ifdef SCT_ENDP_MULTI_IPADDR
EXTERN S16 AqLiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          SctNetAddrLst *intfNAddrLst));
#else /* SCT_ENDP_MULTI_IPADDR */
EXTERN S16 AqLiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          CmNetAddr     *intfNAddr));
#endif /* SCT_ENDP_MULTI_IPADDR */

EXTERN S16 AqLiSctEndpOpenCfm       ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          UConnId        spEndpId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 AqLiSctEndpCloseReq      ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        endpId,
                                          U8             endpIdType));

EXTERN S16 AqLiSctEndpCloseCfm      ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          SctResult      result,
                                          SctCause       cause));
#ifdef SCT3
EXTERN S16 AqLiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          SctTos          tos,
                                          Buffer        *vsInfo));
#else
EXTERN S16 AqLiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          Buffer        *vsInfo));

#endif


EXTERN S16 AqLiSctAssocInd          ARGS((Pst               *pst,
                                          SuId               suId,
                                          UConnId            suEndpId,
                                          SctAssocIndParams *assocParams,
                                          Buffer            *vsInfo));
#ifdef SCT3
EXTERN S16 AqLiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctTos             tos,
                                          SctResult          result,
                                          Buffer            *vsInfo));
#else
EXTERN S16 AqLiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctResult          result,
                                          Buffer            *vsInfo));
#endif

#ifdef SCT2
EXTERN S16 AqLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      inStrms,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#else /* SCT2 */
EXTERN S16 AqLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#endif /* SCT2 */

EXTERN S16 AqLiSctTermReq           ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          Bool           abrtFlg));

EXTERN S16 AqLiSctTermInd           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          SctStatus      status,
                                          SctCause       cause,
                                          SctRtrvInfo   *rtrvInfo));

EXTERN S16 AqLiSctTermCfm           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 AqLiSctSetPriReq         ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr));

EXTERN S16 AqLiSctSetPriCfm         ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 AqLiSctHBeatReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U16            intervalTime,
                                          SctStatus      status));

EXTERN S16 AqLiSctHBeatCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctResult      result,
                                          SctCause       cause));
EXTERN S16 AqLiSctDatReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStrmId      strmId,
                                          Bool           unorderFlg,
                                          Bool           nobundleFlg,
                                          U16            lifeTime,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 AqLiSctDatInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctStrmId      strmId,
                                          SctDatIndType *indType,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 AqLiSctStaReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U8             staType));

EXTERN S16 AqLiSctStaCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctResult      result,
                                          SctCause       cause,
                                          SctStaInfo    *staInfo));
/* sct_x_001.main_37: Included protId parameter in status indication */
#ifdef SCT7
EXTERN S16 AqLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          U32            protId,
                                          Buffer        *mBuf));
#else
EXTERN S16 AqLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          Buffer        *mBuf));
#endif /* SCT7 */

EXTERN S16 AqLiSctFlcInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          Reason         reason));
#endif /* AQ */

/* sct_x_001.main_21: LDF-SUA 1.1 REL */
#ifdef AH  /* LDF-SUA */
EXTERN S16 AhLiSctBndCfm            ARGS((Pst *pst, SuId suId, SctResult result));
EXTERN S16 AhLiSctEndpOpenCfm       ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          UConnId        spEndpId,
                                          SctResult      result,
                                          SctCause       cause));
EXTERN S16 AhLiSctEndpCloseCfm      ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          SctResult      result,
                                          SctCause       cause));
EXTERN S16 AhLiSctAssocInd          ARGS((Pst               *pst,
                                          SuId               suId,
                                          UConnId            suEndpId,
                                          SctAssocIndParams *assocParams,
                                          Buffer            *vsInfo));
#ifdef SCT2
EXTERN S16 AhLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      inStrms,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#else
EXTERN S16 AhLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#endif /* SCT2 */
EXTERN S16 AhLiSctTermInd           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          SctStatus      status,
                                          SctCause       cause,
                                          SctRtrvInfo   *rtrvInfo));
EXTERN S16 AhLiSctTermCfm           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));
EXTERN S16 AhLiSctSetPriCfm         ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));
EXTERN S16 AhLiSctHBeatCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctResult      result,
                                          SctCause       cause));
EXTERN S16 AhLiSctDatInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctStrmId      strmId,
                                          SctDatIndType *indType,
                                          U32            protId,
                                          Buffer        *mBuf));
EXTERN S16 AhLiSctStaCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctResult      result,
                                          SctCause       cause,
                                          SctStaInfo    *staInfo));

/* sct_x_001.main_37: Included protId parameter in status indication */
#ifdef SCT7
EXTERN S16 AhLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          U32            protId,
                                          Buffer        *mBuf));
#else
EXTERN S16 AhLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          Buffer        *mBuf));
#endif  /* SCT7 */
EXTERN S16 AhLiSctFlcInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          Reason         reason));
#endif /* AH */

/* sct_x_001.main_30 Updated for S1AP release 1.1 */
#ifdef SZ
EXTERN S16 SzLiSctBndReq            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SpId           spId));

EXTERN S16 SzLiSctBndCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SctResult      result));

#ifdef SCT_ENDP_MULTI_IPADDR
EXTERN S16 SzLiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          SctNetAddrLst *intfNAddrLst));
#else /* SCT_ENDP_MULTI_IPADDR */
EXTERN S16 SzLiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          CmNetAddr     *intfNAddr));
#endif /* SCT_ENDP_MULTI_IPADDR */

EXTERN S16 SzLiSctEndpOpenCfm       ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          UConnId        spEndpId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 SzLiSctEndpCloseReq      ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        endpId,
                                          U8             endpIdType));

EXTERN S16 SzLiSctEndpCloseCfm      ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          SctResult      result,
                                          SctCause       cause));
#ifdef SCT3
EXTERN S16 SzLiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          SctTos          tos,
                                          Buffer        *vsInfo));
#else
EXTERN S16 SzLiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          Buffer        *vsInfo));

#endif


EXTERN S16 SzLiSctAssocInd          ARGS((Pst               *pst,
                                          SuId               suId,
                                          UConnId            suEndpId,
                                          SctAssocIndParams *assocParams,
                                          Buffer            *vsInfo));
#ifdef SCT3
EXTERN S16 SzLiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctTos             tos,
                                          SctResult          result,
                                          Buffer            *vsInfo));
#else
EXTERN S16 SzLiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctResult          result,
                                          Buffer            *vsInfo));
#endif

#ifdef SCT2
EXTERN S16 SzLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      inStrms,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#else /* SCT2 */
EXTERN S16 SzLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#endif /* SCT2 */
#ifdef S1SIMAPP
EXTERN S16 SzLiSctTermReq           ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          Bool           abrtFlg,
                                          U8             cause));
#else
EXTERN S16 SzLiSctTermReq           ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          Bool           abrtFlg));
#endif

EXTERN S16 SzLiSctTermInd           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          SctStatus      status,
                                          SctCause       cause,
                                          SctRtrvInfo   *rtrvInfo));

EXTERN S16 SzLiSctTermCfm           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));
#ifdef SZ_PHASE2
EXTERN S16 SzLiSctSetPriReq         ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr));

EXTERN S16 SzLiSctSetPriCfm         ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 SzLiSctHBeatReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U16            intervalTime,
                                          SctStatus      status));

EXTERN S16 SzLiSctHBeatCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctResult      result,
                                          SctCause       cause));
#endif /* SZ_PHASE2 */
/* sct_x_001.main_32: Updated for S1AP phase2 release */
EXTERN S16 SzLiSctStaReq            ARGS((Pst           *pst,             
                                          SpId           spId,            
                                          UConnId        spAssocId,    
                                          CmNetAddr     *dstNAddr,  
                                          U8             staType ));

EXTERN S16 SzLiSctDatReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStrmId      strmId,
                                          Bool           unorderFlg,
                                          Bool           nobundleFlg,
                                          U16            lifeTime,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 SzLiSctDatInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctStrmId      strmId,
                                          SctDatIndType *indType,
                                          U32            protId,
                                          Buffer        *mBuf));

/* sct_x_001.main_32: Updated for S1AP phase2 release */
#ifdef SZ_PHASE2
EXTERN S16 SzLiSctStaCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctResult      result,
                                          SctCause       cause,
                                          SctStaInfo    *staInfo));
/* sct_x_001.main_32: Updated for S1AP phase2 release */
#endif/* SZ_PHASE2 */					  
/* sct_x_001.main_37: Included protId parameter in status indication */
#ifdef SCT7
EXTERN S16 SzLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          U32            protId,
                                          Buffer        *mBuf));
#else
EXTERN S16 SzLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          Buffer        *mBuf));
#endif /* SCT7 */
/* sct_x_001.main_32: Updated for S1AP phase2 release */
EXTERN S16 SzLiSctFlcInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          Reason         reason));
#endif /* SZ */

/* sct_x_001.main_35 Updated for X2AP release 1.1 */
#ifdef CZ
EXTERN S16 CzLiSctBndReq            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SpId           spId));

EXTERN S16 CzLiSctBndCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SctResult      result));

#ifdef SCT_ENDP_MULTI_IPADDR
EXTERN S16 CzLiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          SctNetAddrLst *intfNAddrLst));
#else /* SCT_ENDP_MULTI_IPADDR */
EXTERN S16 CzLiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          CmNetAddr     *intfNAddr));
#endif /* SCT_ENDP_MULTI_IPADDR */

EXTERN S16 CzLiSctEndpOpenCfm       ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          UConnId        spEndpId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 CzLiSctEndpCloseReq      ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        endpId,
                                          U8             endpIdType));

EXTERN S16 CzLiSctEndpCloseCfm      ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          SctResult      result,
                                          SctCause       cause));
#ifdef SCT3
EXTERN S16 CzLiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          SctTos          tos,
                                          Buffer        *vsInfo));
#else
EXTERN S16 CzLiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          Buffer        *vsInfo));

#endif


EXTERN S16 CzLiSctAssocInd          ARGS((Pst               *pst,
                                          SuId               suId,
                                          UConnId            suEndpId,
                                          SctAssocIndParams *assocParams,
                                          Buffer            *vsInfo));
#ifdef SCT3
EXTERN S16 CzLiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctTos             tos,
                                          SctResult          result,
                                          Buffer            *vsInfo));
#else
EXTERN S16 CzLiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctResult          result,
                                          Buffer            *vsInfo));
#endif

#ifdef SCT2
EXTERN S16 CzLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      inStrms,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#else /* SCT2 */
EXTERN S16 CzLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#endif /* SCT2 */

EXTERN S16 CzLiSctTermReq           ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          Bool           abrtFlg));

EXTERN S16 CzLiSctTermInd           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          SctStatus      status,
                                          SctCause       cause,
                                          SctRtrvInfo   *rtrvInfo));

EXTERN S16 CzLiSctTermCfm           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));
EXTERN S16 CzLiSctSetPriReq         ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr));

EXTERN S16 CzLiSctSetPriCfm         ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 CzLiSctHBeatReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U16            intervalTime,
                                          SctStatus      status));

EXTERN S16 CzLiSctHBeatCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctResult      result,
                                          SctCause       cause));
EXTERN S16 CzLiSctStaCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctResult      result,
                                          SctCause       cause,
                                          SctStaInfo    *staInfo));
EXTERN S16 CzLiSctStaReq            ARGS((Pst           *pst,             
                                          SpId           spId,            
                                          UConnId        spAssocId,    
                                          CmNetAddr     *dstNAddr,  
                                          U8             staType ));

EXTERN S16 CzLiSctDatReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStrmId      strmId,
                                          Bool           unorderFlg,
                                          Bool           nobundleFlg,
                                          U16            lifeTime,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 CzLiSctDatInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctStrmId      strmId,
                                          SctDatIndType *indType,
                                          U32            protId,
                                          Buffer        *mBuf));

/* sct_x_001.main_37: Included protId parameter in status indication */
#ifdef SCT7
EXTERN S16 CzLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          U32            protId,
                                          Buffer        *mBuf));
#else
EXTERN S16 CzLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          Buffer        *mBuf));
#endif /* SCT7 */
EXTERN S16 CzLiSctFlcInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          Reason         reason));
#endif /* CZ */
/* sct_x_001.main_36: IUH release */
#ifdef HM   /* Iuh Signalling Protocols */
EXTERN S16 HmLiSctBndReq            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SpId           spId));

EXTERN S16 HmLiSctBndCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SctResult      result));

#ifdef SCT_ENDP_MULTI_IPADDR
EXTERN S16 HmLiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          SctNetAddrLst *intfNAddrLst));
#else /* SCT_ENDP_MULTI_IPADDR */
EXTERN S16 HmLiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          CmNetAddr     *intfNAddr));
#endif /* SCT_ENDP_MULTI_IPADDR */

EXTERN S16 HmLiSctEndpOpenCfm       ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          UConnId        spEndpId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 HmLiSctEndpCloseReq      ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        endpId,
                                          U8             endpIdType));

EXTERN S16 HmLiSctEndpCloseCfm      ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          SctResult      result,
                                          SctCause       cause));
#ifdef SCT3
EXTERN S16 HmLiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          SctTos          tos,
                                          Buffer        *vsInfo));
#else
EXTERN S16 HmLiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          Buffer        *vsInfo));
#endif

EXTERN S16 HmLiSctAssocInd          ARGS((Pst               *pst,
                                          SuId               suId,
                                          UConnId            suEndpId,
                                          SctAssocIndParams *assocParams,
                                          Buffer            *vsInfo));
#ifdef SCT3
EXTERN S16 HmLiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctTos             tos,
                                          SctResult          result,
                                          Buffer            *vsInfo));
#else
EXTERN S16 HmLiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctResult          result,
                                          Buffer            *vsInfo));
#endif

#ifdef SCT2
EXTERN S16 HmLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      inStrms,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#else /* SCT2 */
EXTERN S16 HmLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#endif /* SCT2 */

EXTERN S16 HmLiSctTermReq           ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          Bool           abrtFlg));

EXTERN S16 HmLiSctTermInd           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          SctStatus      status,
                                          SctCause       cause,
                                          SctRtrvInfo   *rtrvInfo));

EXTERN S16 HmLiSctTermCfm           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));
EXTERN S16 HmLiSctStaReq            ARGS((Pst           *pst,             
                                          SpId           spId,            
                                          UConnId        spAssocId,    
                                          CmNetAddr     *dstNAddr,  
                                          U8             staType ));

EXTERN S16 HmLiSctDatReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStrmId      strmId,
                                          Bool           unorderFlg,
                                          Bool           nobundleFlg,
                                          U16            lifeTime,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 HmLiSctDatInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctStrmId      strmId,
                                          SctDatIndType *indType,
                                          U32            protId,
                                          Buffer        *mBuf));

#ifndef SCT7
EXTERN S16 HmLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          Buffer        *mBuf));
#else
EXTERN S16 HmLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          U32            protId,
                                          Buffer        *mBuf));
#endif 

EXTERN S16 HmLiSctFlcInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          Reason         reason));
EXTERN S16 HmLiSctStaCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctResult      result,
                                          SctCause       cause,
                                          SctStaInfo    *staInfo));
EXTERN S16 HmLiSctHBeatReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U16            intervalTime,
                                          SctStatus      status));
EXTERN S16 HmLiSctSetPriReq         ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr));
#endif /* HM */

#ifdef __cplusplus
}
#endif

#endif /* __SCTX__ */


/********************************************************************30**

         End of file:     sct.x@@/main/40 - Thu Aug 18 12:47:07 2011

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
------------ -------- ---- ----------------------------------------------
/main/2      ---      nj     1. initial release.
/main/2      ---      nj     1. Added section for IUA to decalare IUA functions
                             2. Put cmPkSctNetAddrLst and cmUnpkSctNetAddrLst fns
                                outside LCSCT flag
 /main/3     ---      sb     1. Modified for SCTP release based on 
                                RFC-2960 'Oct 2000.
                             2. Added prototype definitions for SUA and M2UA.
                             3. Put cmPkSctNetAddrLst and cmUnpkSctNetAddrLst fns
                                inside LCSCT flag
          001.main_3  sb     1. CM_DNS_DNAME_LEN removed from sct.x file.
                                SCT_DNAME_LEN added instead.
/main/4      ---      nt     1. CM_DNS_DNAME_LEN changed to SCT_DNAME_LEN
                                in SctInitParams struct.
/main/5      ---      ap     1. Include in-stream parameter in AssocCfm 
                                under SCT2 compile time flag.
/main/6      ---      rs     1. Modification for TOS parameter support.
/main/7      ---      nt     1. Multiple IP addr allowed in EndpOpenReq.
/main/8      ---      rs     1. Modification for adding LDF-M3UA 
                                externs
/main/9      ---/main/9i       ---      rs     1. GCP & Dummy user added. 
/main/10     ---      rk     1. Added M1UA entries for Nuera PS project
/main/11     ---      hr      Added M2PA portion
/main/13     ---      rk      1. IUA Rel 1.3 updates
/main/14     ---      sg     1. Added TOS parameter in declaration of
                                primitives for M3UA, GCP and GCP Dummy user.
/main/15     ---   rbabu   1. update for NBAP software release 1.2
/main/16     ---      sal  1. Created for Release of 2.1(RFC 3868 Support)
/main/17     ---      ad   1. Updated for Sip Release 2.2 Beta.
/main/18     ---      ad   1. Adding the new Dummy Functions under SIP TA Flag
/main/19     ---      kp   1. TOS enhancement
sct_x_001.main_19     kp   1. Diameter added as new SCTP user.
/main/21     ---      ss   1. Added functions under flag DM.
/main/22     ---      sct_x_001.main_21  rce  1. Added SCT functions under flag AH for LDF-SUA.
/main/23     ---      skv  1. sct_x_001.main_22: Function MxLiSctEndpOpenReq
                               modification as per SCT_ENDP_MULTI_IPADDR flag.
                               ( This patch is related to mx001.101).

sct_x_001.main_23     na    1.  Added TOS support in M2UA
/main/24     ---         na   1. Added TOS support in M2UA
   sct_x_001.main_24  ag   1. Satellite SCTP feature (under compile-time flags
                             SB_ECN & SB_SATELLITE): ecnFlg added in sctInitParams.
   sct_x_001.main_25  na   1. function MwLiSctEndpOpenReq
/main/26     ---      modification as per SCT_ENDP_MULTI_IPADDR flag.
/main/27     ---      sct_x_001.main_26  cs   1. Updated for TUCL 2.1 Release
/main/28     ---      sct_x_001.main_27 nuX   1. Added new parameter in SctInitParams structure. 
/main/28+    ---      sct_x_001.main_28 mraj  Fix for ccpu00094751
/main/30     ---      sct_x_001.main_29 pkaX  1. Dual Checksum Fix.
/main/31     ---      sct_x_001.main_30 hsingh  1.Updated for S1AP release 1.1 
/main/32     sct_x_001.main_31 rcs     1.Included inStrms and outStrms 
                                         parameters in cookieParams structure.
/main/32    sct_x_001.main_32  pkaX    1. Updated for S1AP phase2 release.
/main/33    sct_x_001.main_33  ajainx  1. Included protId parameter in status indication.
/main/35     ---      sct_x_001.main_34  rcs     1. Included protId parameter in HiUiSctStaInd.
/main/36     ---      sct_x_001.main_35  mm     1. Updated for X2AP release 1.1
/main/37              sct_x_001.main_36  ajainx 1. IUH release.
/main/38              sct_x_001.main_37  ajainx 1. Included protId parameter in status
                                                   indication.
/main/39     ---      sct_x_001.main_38   sdey   1. Added Multihoming features in IUA. 
/main/39  sct_x_001.main_39 akaranth 1.Added handling of SCT2 compile time flag for M3UA LDF.
 *********************************************************************91*/
