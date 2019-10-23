

/********************************************************************20**
  
     Name:     Common transport file
  
     Type:     C include file
  
     Desc:     Common file for transport related data structures
  
     File:     cm_tpt.x
  
     Sid:      cm_tpt.x@@/main/14 - Fri Jun 20 14:28:07 2008
  
     Prg:      
  
*********************************************************************21*/
 
#ifdef SS_4GMX_LCORE
#define __CMTPTX__ 1
#endif

#ifndef __CMTPTX__
#define __CMTPTX__


#include "cm_inet.x"

#ifdef CM_AAL
#include "cm_atm.x"
#endif

#ifdef __cplusplus
extern "C" {
#endif /* _cplusplus */

#ifdef __CMINETX__  /* Put cm_inet dependencies here */

typedef CmInetIpv4Addr  CmIpv4TptAddr;
typedef CmInetIpAddr    CmIpv4NetAddr;

#ifndef IPV6_SUPPORTED
typedef U8  CmInetIpAddr6[16];   /* 16 byte IPV6 address */

/* IPV6 Address */
typedef struct cmInetIpv6Addr
{
   U16             port;
   CmInetIpAddr6   ipv6NetAddr;
} CmInetIpv6Addr;
#endif /* IPV6_SUPPORTED */

/* IPV6 Network address */
typedef CmInetIpv6Addr  CmIpv6TptAddr;
typedef CmInetIpAddr6   CmIpv6NetAddr;

#endif /* __CMINETX__ */

/* Network address */
typedef struct cmNetAddr
{
   U8   type;      /* type of network address */
   union
   {
      CmIpv4NetAddr  ipv4NetAddr; /* IP network address */
      CmIpv6NetAddr  ipv6NetAddr; /* IPv6 network address */
   }u;
} CmNetAddr;

/* list of addresses */
typedef struct _cmNetAddrTbl
{
   U16             count;              /* Number of Table Entries */
   CmNetAddr       netAddr[CM_MAX_NET_ADDR]; /* IPV4/IPV6 addresses */
}CmNetAddrTbl;

/* Added new structure for Local Interface */
#ifdef LOCAL_INTF
/* used to pass local interface (on which packet was received) to upper user */
typedef struct cmTptLocalInf
{
   Bool      intfPrsnt;   /* valid intf is present or not */
   U32       localIf;     /* interface index IPv4(32 bit) or IPv6(32 bit) */
   CmNetAddr localIfAddr; /* interface address */
}CmTptLocalInf;
#endif /* LOCAL_INTF */

#ifdef CM_INET2
/* Multicast information */
typedef struct cmNetMCastInf
{
   CmNetAddr         mCastAddr;   /* Multicast adddress */
   CmNetAddr         localAddr;   /* Local address */
} CmNetMCastInf;

#ifdef IPV6_SUPPORTED 
typedef CmInetMCastInf6 CmNetMCastInf6;
#endif /* IPV6_SUPPORTED */
#endif /* CM_INET2 */

/* Transport address */
typedef struct cmTptAddr
{
   U8   type;                     /* type of transport address */
   union
   {
      CmIpv4TptAddr  ipv4TptAddr; /* IP transport address */
      CmIpv6TptAddr  ipv6TptAddr; /* IPv6 transport address */
#ifdef CM_AAL
      AtmVccId       aalTptAddr;  /* AAL transport address */
#endif
   }u;
} CmTptAddr;
 
/*cm_tpt_x_001.main_12 Updated for TUCL 2.1 Release (Kernel SCTP Support) */
#ifdef CM_LKSCTP
/* Array of Transport Addresses */
typedef struct cmTptAddrLst 
{
   U8            nmb;                        /* Number of Network Addresses */
   CmTptAddr     tptAddr[CM_MAX_NET_ADDR];   /* List of Network Addresses */
} CmTptAddrLst;

typedef CmInetSockLinger           CmSockLinger;
typedef CmInetSctpSockEvent        CmSctpEvent;
typedef CmInetSctpPeerAddrParams   CmSctpPeerAddrParams;
typedef CmInetSctpPrimAddr         CmSctpPrimAddr;
typedef CmInetSctpPeerAddrInfo     CmSctpPeerAddrInfo;
typedef CmInetSctpStatus           CmSctpStatus;
typedef CmInetSctpRtoInfo          CmSctpRtoInfo;
typedef CmInetSctpInitMsg          CmSctpInitMsg;
typedef CmInetSctpAssocParams      CmSctpAssocParams;
#endif

/* Socket Options */
typedef struct cmSockOpts
{
   U32  level;                    /* option level */
   U32  option;                   /* option name */
   union                          /* option parameters */
   {
#ifdef CM_INET2
#ifdef IPV6_SUPPORTED 
      CmNetMCastInf6 mCastInfo6; /* IPV6 multicast information */
      U32            infId;      /* IPV6 multicast outgoing interface */
#endif /* IPV6_SUPPORTED */
      CmNetMCastInf  mCastInfo;  /* multicast information */
#else
      CmNetAddr     mCastAddr;   /* multicast information */
#endif /* CM_INET2 */
      CmNetAddr     lclAddr;     /* local outgoing interface */
      U32           value;       /* option value */
/*cm_tpt_x_001.main_12 Updated for TUCL 2.1 Release (Kernel SCTP Support) */
#ifdef CM_LKSCTP
      CmSockLinger           sockLinger;
      CmSctpEvent            sctpEvent;
      CmSctpPeerAddrParams   sctpPeerAddrParams;
      CmSctpPrimAddr         sctpPrimAddr;
      CmSctpPeerAddrInfo     sctpPeerAddrInfo;
      CmSctpStatus           sctpStatus;
/*cm_tpt_x_001.main_13 Updated for the support of configurable RTO parameters, 
                        HBeat value Max retransmissions (Init, Path, Association)*/
      CmSctpRtoInfo          sctpRtoInfo;
      CmSctpInitMsg          sctpInitMsg;
      CmSctpAssocParams      sctpPeerAssocParams;
#endif
   }optVal;
}CmSockOpts;

/* socket parameters */
typedef struct cmSockParam
{
   U8             listenQSize;    /* listen queue size */
   U8             numOpts;        /* number of socket options */
   CmSockOpts sockOpts[CM_MAX_SOCK_OPTS]; /* socket options */
} CmSockParam;

#ifdef CM_TLS
typedef struct tlsTptParam
{
   S16          ctxId;
   U8           listenQSize;
   U8           numOpts;
   CmSockOpts   sockOpts[CM_MAX_SOCK_OPTS];

} TlsTptParam;
#endif /* CM_TLS */

/*cm_tpt_x_001.main_12 Updated for TUCL 2.1 Release (Kernel SCTP Support) */
#ifdef CM_LKSCTP
typedef struct sctpSockParam
{
   U8           numOpts;        /* number of socket options */
   CmSockOpts   sockOpts[CM_MAX_SOCK_OPTS]; /* socket options */
} SctpSockParam;
#endif

/* Transport parameters */
typedef struct cmTptParam
{
   U8   type;                      /* type of transport parameters */

   union
   {
      CmSockParam  sockParam;      /* socket parameters */
#ifdef CM_AAL
      AalConParam  aalParam;       /* AAL connection parameters */
#endif
#ifdef CM_TLS
      TlsTptParam  tlsParam;       /* TLS parameters */
#endif
/*cm_tpt_x_001.main_12 Updated for TUCL 2.1 Release (Kernel SCTP Support) */
#ifdef CM_LKSCTP
      SctpSockParam  sctpParam;    /* LKSCTP parameters */
#endif
   } u;

} CmTptParam;

#ifdef CM_INET2  
/* IPv4 header parameters */
typedef struct cmIpv4HdrParm 
{
   TknU8    proto;                 /* Protocol value */
   TknU8    dfBit;                 /* Don't fragment flag */
   TknU8    tos;                   /* Type of Service */
   TknU8    ttl;                   /* Time to Live */
   /* added new field */
#ifdef IPV4_OPTS_SUPPORTED 
   TknStr64 ipv4HdrOpt;            /* IPV4 hdr opt */
#endif /* IPV4_OPTS_SUPPORTED */
} CmIpv4HdrParm;

#ifdef IPV6_SUPPORTED 
/* added new structures for IPv6 ext hdr support */
#ifdef IPV6_OPTS_SUPPORTED
/* structure to hold TLV of each HBH option */
typedef struct cmIpv6HBHHdr
{
   U8 type;
   U8 length;
   U8 *value;
} CmIpv6HBHHdr;

/* structure to hold TLV of each Destination option */
typedef struct cmIpv6DestOptsHdr
{
   U8 type;
   U8 length;
   U8 *value;
} CmIpv6DestOptsHdr;

/* structure to hold IPV6 addresses of the Route header */
typedef struct cmIpv6RtHdr
{
   U8 numAddrs;               
   U32 slMap;
   CmIpv6NetAddr *ipv6Addrs;   
} CmIpv6RtHdr;

/* array of all HBH options */
typedef struct cmIpv6HBHHdrArr
{
   U8 numHBHOpts;
   CmIpv6HBHHdr *hbhOpts; 
} CmIpv6HBHHdrArr;

/* array of all Destination options */
typedef struct cmIpv6DestOptsArr
{
   U8 numDestOpts;
   CmIpv6DestOptsHdr *destOpts;
} CmIpv6DestOptsArr;

/* structure having 3 substructures for 3 types of ext headers */
typedef struct cmIpv6ExtHdr
{
   Bool hbhHdrPrsnt;
   CmIpv6HBHHdrArr hbhOptsArr;

   Bool destOptsPrsnt;
   CmIpv6DestOptsArr destOptsArr;

   Bool rtOptsPrsnt;
   CmIpv6RtHdr rtOpts;
} CmIpv6ExtHdr;
#endif /* IPV6_OPTS_SUPPORTED */

/* IPV6 header parameters */
typedef struct cmIpv6HdrParm
{
   TknU8    ttl;                   /* Set the hop limit */
   
   /* added new field */
   CmNetAddr srcAddr6; /* src addr to set on send pkt(IPv6) */

   /* added new field */
#ifdef IPV6_OPTS_SUPPORTED 
   CmIpv6ExtHdr ipv6ExtHdr;      
#endif /* IPV6_OPTS_SUPPORTED */  
} CmIpv6HdrParm;
#endif /* IPV6_SUPPORTED */

/* IP header paramters */
typedef struct cmIpHdrParm 
{ 
   U8       type;                  /* Type of IP header parameters */
   union 
   {
      CmIpv4HdrParm  hdrParmIpv4;  /* IPv4 header parameters */
#ifdef IPV6_SUPPORTED 
      CmIpv6HdrParm  hdrParmIpv6;  /* IPv6 header parameters */
#endif /* IPV6_SUPPORTED */
   }u;
   
} CmIpHdrParm;

/* IPv4 header */
typedef struct cmIpv4Hdr 
{
   U8    hdrVer;                   /* Header and Version */
   U8    tos;                      /* Type Of Service */
   S16   length;                   /* Total length */
   U16   id;                       /* Identification */
   S16   off;                      /* Flags and Offset */
   U8    ttl;                      /* Time to Live */
   U8    proto;                    /* Protocol */
   U16   chkSum;                   /* Checksum */
   U32   srcAddr;                  /* Source Address */
   U32   destAddr;                 /* Destination Address */

} CmIpv4Hdr;

#ifdef IPV6_SUPPORTED 
/* IPv6 header */
typedef struct cmIpv6Hdr
{
   union
   {
      struct ip6_hdrctl
      {
         U32      ip6_un1_flow;
         U16      ip6_un1_plen;
         U8       ip6_un1_nxt;
         U8       ip6_un1_hlim;
      } ip6_un1;
      U8    ip6_un2_vfc;
   } ip6_ctlun;
   CmIpv6NetAddr  ip6_src;
   CmIpv6NetAddr  ip6_dst;
} CmIpv6Hdr;
#endif /* IPV6_SUPPORTED */

typedef struct cmIcmpError 
{
   U8    errType;                  /* ICMP Error Type */
   U32   errCodeMask;              /* ICMP Error Code Mask */

} CmIcmpError;

/* ICMP v4 filter parameters */
typedef struct cmIcmpv4Filter
{
   U8    icmpMsgFlag;              /* Flag to listen to any ICMP msgs */
   U8    allMsg;                   /* Flag to listen to ICMP messages */
   U8    protocol;                 /* ICMP packets with protocol only */
   U8    num;                      /* Number of valid type - code 
                                    * combinations in the error array */
   CmIcmpError icmpError[CM_MAX_ICMP_ERROR]; /* Error type & Code array */

}CmIcmpv4Filter;

#ifdef IPV6_SUPPORTED
typedef struct cmIcmpv6Filter
{
   U8    icmpMsgFlag;              /* Flag to listen to any ICMP msgs */
   U8    allMsg;                   /* Flag to listen to all ICMP messages */
   U8    num;                      /* Number of valid type - code 
                                    * combinations in the error array */
   CmIcmpError icmpError[CM_MAX_ICMP_ERROR]; /* Error type & Code array */

} CmIcmpv6Filter; 
#endif /* IPV6_SUPPORTED */

/* ICMP filter paramters */
typedef struct cmIcmpFilter 
{
  U8 type;                        /* ICMP version */
  union 
  {
    CmIcmpv4Filter icmpv4Filter;  /* ICMPv4 filter structure */
#ifdef IPV6_SUPPORTED
    CmIcmpv6Filter icmpv6Filter;  /* ICMPv6 filter structure */
#endif /* IPV6_SUPPORTED */
  }u;

} CmIcmpFilter; 

/* ICMP header */
typedef struct cmIcmpv4Hdr 
{
   U8    icmpType;                /* Type of message */
   U8    icmpCode;                /* Message code */
   U16   chkSum;                  /* Ones complement cksum of struct */
   
   union 
   {
      U8   ihPptr;                /* ICMP parameter problem */
      U32  rdrctAddr;             /* ICMP redirect address */
      struct idSeq 
      {
         S16   icdId;             /* Identifier */                          
         S16   icdSeq;            /* Sequence Number */
      } u1;
      U32 ihVoid;                 
   } u2;
   
   union 
   {
      struct idTime
      {
         U32  itOtime;            /* Original time stamp */
         U32  itRtime;            /* Received time stamp */
         U32  itTtime;            /* Transmit time stamp */
      } s;
      CmIpv4Hdr icmpIpHdr;        /* IP header */
      U32     id_mask;
   } u3;

} CmIcmpv4Hdr;

#ifdef IPV6_SUPPORTED
typedef struct cmIcmpv6Hdr
{
   U8    icmp6_type;              /* type field */
   U8    icmp6_code;              /* code field */
   U16   icmp6_cksum;             /* checksum field */

   union
   {
      U32   icmp6_un_data32[1];   /* type-specific field */
      U16   icmp6_un_data16[2];   /* type-specific field */ 
      U8    icmp6_un_data8[4];    /* type-specific field */
   } icmp6_dataun;
} CmIcmpv6Hdr;
#endif /* IPV6_SUPPORTED */

#endif  /* CM_INET2 */ 

/* packing/unpacking function prototypes */
/* Added packing and unpacking function prototypes */
EXTERN S16 cmPkCmIpv4TptAddr    ARGS((CmIpv4TptAddr *pkParam, Buffer *mBuf));
EXTERN S16 cmPkCmNetAddrTbl     ARGS((CmNetAddrTbl *pkParam, Buffer *mBuf));
EXTERN S16 cmPkCmNetAddr        ARGS((CmNetAddr *pkParam, Buffer *mBuf));
EXTERN S16 cmPkCmTptAddr        ARGS((CmTptAddr *pkParam, Buffer *mBuf));
#ifdef IPV6_SUPPORTED
EXTERN S16 cmPkCmNetMCastInf6   ARGS((CmNetMCastInf6 *pkParam, Buffer *mBuf));
#endif /* IPV6_SUPPORTED */
EXTERN S16 cmPkCmTptParam       ARGS((CmTptParam *pkParam, Buffer *mBuf));
EXTERN S16 cmUnpkCmNetAddrTbl   ARGS((CmNetAddrTbl *unpkParam, Buffer *mBuf));
EXTERN S16 cmUnpkCmIpv4TptAddr  ARGS((CmIpv4TptAddr *unpkParam, Buffer *mBuf));
EXTERN S16 cmUnpkCmNetAddr      ARGS((CmNetAddr *unpkParam, Buffer *mBuf));
EXTERN S16 cmUnpkCmTptAddr      ARGS((CmTptAddr *unpkParam, Buffer *mBuf));
#ifdef IPV6_SUPPORTED
EXTERN S16 cmUnpkCmNetMCastInf6 ARGS((CmNetMCastInf6 *unpkParam, Buffer *mBuf));
#endif /* IPV6_SUPPORTED */

EXTERN S16 cmUnpkCmTptParam     ARGS((CmTptParam *unpkParam, Buffer *mBuf));

#ifdef CM_INET2  
EXTERN S16 cmPkCmIpHdrParm     ARGS((CmIpHdrParm *pkParam, Buffer *mBuf));

/* changed to include meminfo required to hold IPv6 
                         extension headers */
#ifdef IPV6_OPTS_SUPPORTED
EXTERN S16 cmUnpkCmIpHdrParm    ARGS((CmIpHdrParm *unpkParam, Buffer *mBuf, 
                                     Mem *memInfo));
#else
EXTERN S16 cmUnpkCmIpHdrParm    ARGS((CmIpHdrParm *unpkParam, Buffer *mBuf));
#endif

/* added new packing/unpacking function */
#ifdef LOCAL_INTF
EXTERN S16 cmPkCmTptLocalInf    ARGS((CmTptLocalInf *pkParam, Buffer *mBuf));
EXTERN S16 cmUnpkCmTptLocalInf  ARGS((CmTptLocalInf *unpkParam, Buffer *mBuf));
#endif /* LOCAL_INTF */

EXTERN S16 cmPkCmIcmpFilter     ARGS((CmIcmpFilter *pkParam, Buffer *mBuf));
EXTERN S16 cmUnpkCmIcmpFilter   ARGS((CmIcmpFilter *unpkParam, Buffer *mBuf));

/* added new packing/unpacking functions */
#ifdef IPV6_OPTS_SUPPORTED
EXTERN S16 cmPkCmIpv6ExtHdr     ARGS((CmIpv6ExtHdr *pkParam, Buffer *mBuf));
EXTERN S16 cmPkCmIpv6RtHdr      ARGS((CmIpv6RtHdr *pkParam, Buffer *mBuf));
EXTERN S16 cmUnpkCmIpv6RtHdr    ARGS((CmIpv6RtHdr *unpkParam, Buffer *mBuf, 
                                     Mem *memInfo));
EXTERN S16 cmUnpkCmIpv6ExtHdr   ARGS((CmIpv6ExtHdr *unpkParam, Buffer *mBuf, 
                                     Mem *memInfo));
EXTERN S16 cmPkCmIpv6DestOptsArr ARGS((CmIpv6DestOptsArr *pkParam, 
                                      Buffer *mBuf));
EXTERN S16 cmPkCmIpv6DestOptsHdr ARGS((CmIpv6DestOptsHdr *pkParam, 
                                      Buffer *mBuf));
EXTERN S16 cmUnpkCmIpv6DestOptsHdr ARGS((CmIpv6DestOptsHdr *unpkParam, 
                                      Buffer *mBuf, Mem *memInfo));
EXTERN S16 cmUnpkCmIpv6DestOptsArr ARGS((CmIpv6DestOptsArr *unpkParam, 
                                      Buffer *mBuf, Mem *memInfo));
EXTERN S16 cmPkCmIpv6HBHHdrArr  ARGS((CmIpv6HBHHdrArr *pkParam, Buffer *mBuf));
EXTERN S16 cmPkCmIpv6HBHHdr     ARGS((CmIpv6HBHHdr *pkParam, Buffer *mBuf));
EXTERN S16 cmUnpkCmIpv6HBHHdr   ARGS((CmIpv6HBHHdr *unpkParam, Buffer *mBuf, 
                                     Mem *memInfo));
EXTERN S16 cmUnpkCmIpv6HBHHdrArr ARGS((CmIpv6HBHHdrArr *unpkParam, 
                                      Buffer *mBuf, Mem *memInfo));
#endif /* IPV6_OPTS_SUPPORTED */
#endif  /* CM_INET2 */ 

#ifdef __cplusplus
}
#endif

#endif /* __CMTPTX__ */

/********************************************************************30**
 
         End of file:     cm_tpt.x@@/main/14 - Fri Jun 20 14:28:07 2008
 
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
------------ -------- ---- ----------------------------------------------
1.1          ---      kp   1. initial release.
1.2          ---      kp   1. Added AAL support under CM_AAL--AAL address
                              in CmTptAddr and AAL connection parameters
                              in CmTptParam.
                           2. Moved include of cm_inet.x into this file
                              from the cm_tpt.c file.
/main/4      ---      sb   1. Addition of IP & ICMP header along with the 
                              ICMP filtering parameter for Raw socket. 
                           2. Changed the copyright header.
$(SID)$      ---      bbk  1. Added CmNetAddrTbl data structure and 
                              prototype for its packing/unpacking functions
/main/7      ---      vj   1. Merged IPV6 code with GCP 1.3 release 
/main/8      ---      mmh  1. Added new structure for Local Interface
                           2. Added new field ipv4HdrOpt in the structure
                              CmIpv4HdrParm
                           3. Added new structures for IPv6 ext hdr support
                           4. Added new field ipv6ExtHdr, srcAddr6 in the
                              structure CmIpv6HdrParm
                           5. Changed the prototypes of function
                              cmUnpkCmIpHdrParm
                           6. Added new packing and unpacking functions for
                              the newly added structures.
/main/9      ---      bdu  1. Change for MCAST6_IF option.
/main/10     ---      mj   1. MPLS release 1.2 changes.
/main/11     ---      wh   1. SIP 2.1 release changes.
/main/12     ---      kp   1. TUCL 1.5 release changes. Added TLS
                              transport parameter.
/main/13     ---   cm_tpt_x_001.main_12      hs   1. Updated for TUCL 2.1 release
/main/14     ---   cm_tpt_x_001.main_13      cs   1. Updated for the support of configurable RTO parameters, HBeat value,
                                                     Max retransmissions (Init, Path, Association)
*********************************************************************91*/
