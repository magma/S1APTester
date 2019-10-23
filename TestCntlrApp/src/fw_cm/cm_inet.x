
/********************************************************************20**
  
        Name:     common Internet socket library
    
        Type:     header file 
  
        Desc:     common library for Internet sockets
                    
        File:     cm_inet.x

        Sid:      cm_inet.x@@/main/31 - Fri Sep  7 13:00:05 2012
  
        Prg:      mf
  
*********************************************************************21*/
 

/*
 *      This software may be combined with the following TRILLIUM
 *      software:
 *
 *      part no.                      description
 *      --------    ----------------------------------------------
 *      1000151     TCAP over TCP/IP   
 */

/* cm_inet_x_001.main_29: SS_4GMX_LCORE changes */
#ifdef SS_4GMX_LCORE
#define __CMINETX__ 1
#endif
#ifndef __CMINETX__
#define __CMINETX__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef WIN32
#ifdef SS_WINCE
#ifndef IN
#define IN
#include <winsock2.h>
#undef IN
#else /*IN*/
#include <winsock2.h>
#endif /*IN*/
#else  /*SS_WINCE*/
   /* cm_inet_x_001.main_28: Added #define IN */
#ifndef IN
#define IN
#include <winsock2.h>
#undef IN
#else /*IN*/
#include <winsock2.h>
#endif /*IN*/
#endif /* SS_WINCE */
#else
#include <string.h>
#ifdef SS_LINUX
#include <sys/select.h>
#include <sys/poll.h>
#endif /* SS_LINUX */
#include <sys/types.h>
#ifdef SS_PS
#include <pna.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#endif /* SS_PS */
#endif /* WIN32 */

#ifdef IPV6_SUPPORTED
#if (defined(SUNOS) || defined(HPOS)) 
#include <netinet/icmp6.h>
#endif /* SUNOS || HPOS */
#endif /* IPV6_SUPPORTED */

 /* cm_inet_x_001.main_27 : Added header file inclusion */
#if (defined(SS_VW) && defined(SS_VW6_7)) 
#include <ipcom_inet.h>
#include <ipcom_sock6.h>
#include <netinet/icmp6.h>
#endif

/* cm_inet_x_001.main_21:Added wrapper function for getaddrinfo and freeaddrinfo */
#if (!defined(SS_VW) && !defined(SS_PS) && !defined(WIN32))
#include <netdb.h>
#endif

/* Redifining the CmInetIpAddr &  CmInetIpAddr6 */
typedef CmIpAddr CmInetIpAddr;        /* 4 byte IP address */
#ifdef IPV6_SUPPORTED
typedef CmIpAddr6 CmInetIpAddr6;   /* 16 byte IPV6 address */
#endif /* IPV6_SUPPORTED */

typedef struct cmInetIpAddrTbl
{
   U16             count;           /* Number of addresses in table */
   CmInetIpAddr    netAddr[CM_INET_IPV4_NUM_ADDR];  /* Address table */
}CmInetIpAddrTbl;

typedef CmInetIpAddrTbl CmInetIpv4AddrArr;

#ifdef IPV6_SUPPORTED
typedef struct cmInetIpv6AddrArr
{
   U16             count;           /* Number of addresses in array */
   CmInetIpAddr6   netAddr[CM_INET_IPV6_NUM_ADDR];  /* Address array */
}CmInetIpv6AddrArr;
#endif /* IPV6_SUPPORTED */

typedef struct cmInetIpAddrArr
{
   U8       type;
   union
   {
      CmInetIpv4AddrArr   ipv4AddrArr;   
#ifdef IPV6_SUPPORTED
      CmInetIpv6AddrArr   ipv6AddrArr;   
#endif /* IPV6_SUPPORTED */
   } u;

} CmInetIpAddrArr;

/* Adding a type for socket descriptors */
#ifdef WIN32
typedef SOCKET CmInetFdType;
#else
#if (defined(SUNOS) || defined(HPOS)) 
typedef S32 CmInetFdType;
#else
#ifdef SS_LINUX
typedef S32 CmInetFdType;
#else
typedef S16 CmInetFdType;
#endif /* SS_LINUX */
#endif /* SUNOS || HPOS */
#endif /* WIN32 */
/* cm_inet_x_001.main_29 Poll Implementation Changes */
typedef struct pollfd CmInetPollFd;

typedef struct cmInetFd          /* trillium socket file descriptor */
{
   CmInetFdType fd;              /* socket descriptor */
   U8     blocking;              /* true if socket is blocking */
   U8     type;                  /* socket type (stream|datagram) */

#ifdef IPV6_SUPPORTED
   U8     protType;              /* indicates whether IPv4 or IPv6 socket */
#endif /* IPV6_SUPPORTED */  
}CmInetFd;

typedef fd_set CmInetFdSet;      /* socket file descriptor set */

#ifdef IPV6_SUPPORTED 
/* IPV4 Address */
typedef struct cmInetIpv4Addr
{
   U16             port;
   CmInetIpAddr    address;
} CmInetIpv4Addr;

/* IPV6 Address */
typedef struct cmInetIpv6Addr
{
   U16             port;
   CmInetIpAddr6   ipv6NetAddr;
} CmInetIpv6Addr;

typedef struct CmInetAddr        /* Internet address */
{
   U8           type;            /* type of address present in the union */
   union
   {
      CmInetIpv4Addr    ipv4Addr;   /* IPV4 Address */
      CmInetIpv6Addr    ipv6Addr;   /* IPV6 Address */
   }u;
}CmInetAddr;

typedef struct cmInetMCastInf6   /* multicast interface information */
{
   CmInetIpAddr6 mCastAddr;      /* multicast address */
   U32           localInf;       /* local interface */
} CmInetMCastInf6;
#else
/* IPV4 Address */
typedef struct cmInetAddr1    
{
   U16             port;
   CmInetIpAddr    address;
} CmInetAddr;
typedef CmInetAddr CmInetIpv4Addr; 
#endif /* IPV6_SUPPORTED */

typedef struct cmInetMemInfo     /* memory information */
{
   Region   region;              /* memory region */
   Pool     pool;                /* memory pool */
} CmInetMemInfo;

typedef struct cmInetMCastInf    /* multicast information */
{
   CmInetIpAddr  mCastAddr;      /* multicast class D address */
   CmInetIpAddr  localAddr;      /* local interface address */
}CmInetMCastInf;

/* this is the same structure as cmNetAddr in cm_tpt.x
   used here for cmInetConvertStrToIpAddr */
typedef struct cmInetNetAddr
{
   U8   type;      /* type of network address */
   union
   {
      CmInetIpAddr   ipv4NetAddr; /* IP network address */
#ifdef IPV6_SUPPORTED
      CmInetIpAddr6  ipv6NetAddr; /* IPv6 network address */
#endif /* IPV6_SUPPORTED */
   }u;
} CmInetNetAddr;

/*cm_inet_x_001.main_23 Updated for TUCL 2.1 Release (Kernel SCTP Support) */
#ifdef CM_LKSCTP
typedef struct cmInetNetAddrLst
{
   U8   count;
   CmInetNetAddr   addrs[CM_INET_NUM_NET_ADDR];
} CmInetNetAddrLst;
#endif

#ifdef LOCAL_INTF
/* used to pass local interface (on which packet was received) to upper user */
typedef struct cmInetLocalInf
{
   Bool          intfPrsnt;   /* bool to indicate if this is a valid loc intf */
   U32           localIf;     /* interface index IPv4(32 bit) or IPv6(32 bit) */
   CmInetNetAddr localIfAddr; /* interface address */
}CmInetLocalInf;
#endif /* LOCAL_INTF */

#ifdef IPV6_SUPPORTED
#if (defined(SUNOS) || defined(HPOS) || defined(SS_VW))
typedef struct icmp6_filter CmInetIcmp6Filter;
#endif /* SUNOS || HPOS */
#endif /* IPV6_SUPPORTED */

/* New data structures needed to support 3 types of IPV6 extension 
 * headers - HBH, Destination Option & Route Header */
#ifdef IPV6_SUPPORTED
#ifdef IPV6_OPTS_SUPPORTED

/* structure to hold TLV of each HBH option */ 
typedef struct cmInetIpv6HBHHdr
{
   U8 type;
   U8 length;
   U8 *value;
} CmInetIpv6HBHHdr;

/* structure to hold TLV of each Destination option */
typedef struct cmInetIpv6DestOptsHdr
{
   U8 type;
   U8 length;
   U8 *value;
} CmInetIpv6DestOptsHdr;

/* structure to hold IPV6 addresses of the Route header */
typedef struct cmInetIpv6RtHdr
{
   U8 numAddrs;
   U32 slMap;
   CmInetIpAddr6 *ipv6Addrs; 
} CmInetIpv6RtHdr;

/* array of all HBH options */
typedef struct cmInetIpv6HBHHdrArr
{
   U8 numHBHOpts;
   CmInetIpv6HBHHdr *hbhOpts;
} CmInetIpv6HBHHdrArr;

/* array of all Destination options */
typedef struct cmInetIpv6DestOptsArr
{
   U8 numDestOpts;
   CmInetIpv6DestOptsHdr *destOpts;
} CmInetIpv6DestOptsArr;

/* structure having 3 substructures for 3 types of ext headers */
typedef struct cmInetIpv6ExtHdr
{
   Bool hbhHdrPrsnt;
   CmInetIpv6HBHHdrArr hbhOptsArr;
   Bool destOptsPrsnt;
   CmInetIpv6DestOptsArr destOptsArr;
   Bool rtOptsPrsnt;
   CmInetIpv6RtHdr rtOptsArr;
} CmInetIpv6ExtHdr;

/* structure for type 0 Route Header */
typedef struct cmInetIpv6RtHdr0 
{
   U8 ip6r0_nextHdr;
   U8 ip6r0_hdrExtLen;
   U8 ip6r0_type;
   U8 ip6r0_segLeft;
   U32 ip6r0_resrvAndSLmap; /* first byte reserved, last 3 srtict/loose map */
} CmInetIpv6RtHdr0;
#endif /* IPV6_OPTS_SUPPORTED */

typedef struct cmInetIpv6HdrParm
{
   TknU8 ttl;
   CmInetNetAddr srcAddr6;/* used to set src addr on sending pkt(IPv6) */
#ifdef IPV6_OPTS_SUPPORTED   
   CmInetIpv6ExtHdr ipv6ExtHdr;
#endif /* IPV6_OPTS_SUPPORTED */
} CmInetIpv6HdrParm;
#endif /* IPV6_SUPPORTED */

typedef struct cmInetIpv4HdrParm 
{
   TknU8    proto;                 /* Protocol value */
   TknU8    dfBit;                 /* Don't fragment flag */
   TknU8    tos;                   /* Type of Service */
   TknU8    ttl;                   /* Time to Live */
   /* added new field */
#ifdef IPV4_OPTS_SUPPORTED 
   TknStr64 ipv4HdrOpt;            /* IPV4 hdr opt */
#endif /* IPV4_OPTS_SUPPORTED */
} CmInetIpv4HdrParm;
typedef struct cmInetIpHdrParm
{
   U8 type;
   union
   {
      CmInetIpv4HdrParm  hdrParmIpv4;  /* IPv4 header parameters */
#ifdef IPV6_SUPPORTED
      CmInetIpv6HdrParm ipv6HdrParm;
#endif /* IPV6_SUPPORTED */    
   } u;
} CmInetIpHdrParm;

/* New data structures to peek into the file descriptor set. */
/* fdSetInfo structure */
#ifdef WIN32
typedef struct cmInetFdSetInfo
{
   Bool           initDone;      /* Initialisation done */
   U32            numFds;        /* Number of file descriptors scanned */
} CmInetFdSetInfo;
#else
#if (defined(SUNOS) || defined(SS_LINUX) || defined(SS_VW) || defined(HPOS)) 
typedef struct cmInetFdSetInfo
{
   Bool        initDone;         /* Initialisation done */
   Bool        bigEndian;        /* Big endian architecture */
   U16         arIdx;            /* Current index in fd_set array */
   U32         numArElems;       /* Number of array elements */
   U8          ar[256];          /* Array of bit positions */
} CmInetFdSetInfo;
#endif /* SUNOS || SS_LINUX || SS_VW */
#endif /* WIN32 */

/*cm_inet_x_001.main_23 Updated for TUCL 2.1 Release (Kernel SCTP Support) */
#ifdef CM_LKSCTP
typedef struct cmInetSctpSndRcvInfo
{
   U16   stream;
   U16   ssn;
   U16   flags;
   U32   ppid;
   U32   context;
   U32   timetolive;
   U32   tsn;
   U32   cumtsn;
   U32   assocId;
} CmInetSctpSndRcvInfo;

typedef struct cmInetSctpNotification 
{
   struct 
   {
      U16 nType;  
      U16 nFlags;
      U32 nLen;
   } header;

   union 
   {
      struct  
      {
         U16 state;
         U16 error;
         U16 outStreams;
         U16 inStreams;
         U32 assocId;
         U8  *info;
      }assocChange;
      struct  
      {
         CmInetNetAddr addr;
         S32           state;
         S32           error;
         U32           assocId;
      }paddrChange;
      struct 
      {
         U16 error;
         U32 assocId;
         U8  *data;
      }remoteErr;
      struct 
      {
         U32 error;
         CmInetSctpSndRcvInfo info;
         U32 assocId;
         U8  *data;
      }sndFailed;
      struct 
      {
         U32 assocId;
      }shutdownEvt;
      struct 
      {
         U32 adaptationInd;
         U32 assocId;
      }adaptationEvt;
      struct 
      {
         U32 indication;
         U32 assocId;
      }pdapiEvt;
   }u;
}CmInetSctpNotification;

typedef struct cmInetSockLinger
{
   Bool   enable;
   U32    lingerTime;
} CmInetSockLinger;

typedef struct cmInetSctpSockEvent
{
   Bool   dataIoEvent;
   Bool   associationEvent;
   Bool   addressEvent;
   Bool   sendFailureEvent;
   Bool   peerErrorEvent;
   Bool   shutdownEvent;
   Bool   partialDeliveryEvent;
   Bool   adaptationLayerEvent;
} CmInetSctpSockEvent;

typedef struct cmInetSctpPeerAddrParams
{
   U32            assocId;
   struct
   {
      Bool           addrPres;
      CmInetNetAddr  addr;
      U16            port;
   }s;
   U32            pathMaxRxt;
   U32            pathMtu;
   U32            sackDelay;
   U8             pmtudFlag;
   U8             sackDelayFlag;
   U8             hbEnblFlag;
   U32            hbInterval;
} CmInetSctpPeerAddrParams;

typedef struct cmInetSctpPrimAddr 
{
   U32            assocId;
   CmInetNetAddr  addr;
   U16            port;
}CmInetSctpPrimAddr;

typedef struct cmInetSctpPeerAddrInfo
{
   U32           assocId;
   CmInetNetAddr addr;
   U16           port;
   Bool          isActive;
   U32           cwnd;
   U32           srtt;
   U32           rto;
   U32           mtu;
}CmInetSctpPeerAddrInfo;

typedef struct cmInetSctpStatus
{
   U32   assocId;
   S32   state;
   U32   rwnd;
   U16   unackdata;
   U16   penddata;
   U16   instrms;
   U16   outstrms;
   U32   fragPoint; 
   CmInetSctpPeerAddrInfo primary;
}CmInetSctpStatus;

/*cm_inet_x_001.main_24 Updated for the support of configurable RTO parameters, 
                        HBeat value Max retransmissions (Init, Path, Association)*/
typedef struct cmInetSctpRtoInfo
{
   U32   assocId;
   U32   rtoInitial;
   U32   rtoMax;
   U32   rtoMin;
}CmInetSctpRtoInfo;

typedef struct cmInetSctpInitMsg
{
   U16  maxInitReTx;
   U16  maxInitTimeout;
   U16  maxInstreams;
   U16  numOstreams;
}CmInetSctpInitMsg;

typedef struct cmInetSctpAssocParams
{
   U32   assocId;
   U16   assocMaxReTx; 
   U16   numberOfPeerDest;
   U32   peerRwnd;
   U32   localRwnd;
   U32   cookieLife;
}CmInetSctpAssocParams;

#endif

/* added a new type CmInetSockAddr */
#ifdef SUNOS
#ifdef SS_LINUX
typedef struct iovec CmInetIovec;
#else
typedef iovec_t CmInetIovec;
#endif /* SS_LINUX */
typedef struct sockaddr CmInetSockAddr;
#else
#ifdef HPOS
typedef struct iovec CmInetIovec;
typedef struct sockaddr CmInetSockAddr;
#else
#ifdef SS_VW
typedef struct iovec CmInetIovec;
typedef struct sockaddr CmInetSockAddr;
#else
#ifdef WIN32
typedef struct sockaddr CmInetSockAddr;
#else
#ifdef SS_PS
typedef struct iovec CmInetIovec;
typedef struct sockaddr_in CmInetSockAddr;
#endif /* SS_PS */
#endif /* WIN32 */
#endif /* SS_VW */
#endif /* HPOS */
#endif /* SUNOS */

/* addrInfo structure */ 
#if (!defined(SS_VW) && !defined(SS_PS) && !defined(WIN32))
typedef struct addrinfo  CmInetAddrInfo;
#endif /* SS_VW | SS_PS | WIN32*/

/* socket function prototypes */

#ifdef CM_INET2  
#ifdef IPV6_SUPPORTED
EXTERN S16 cmInetSocket ARGS((U8 type, CmInetFd *sockFd, U8 protocol,
                              U8 family));
#else
EXTERN S16 cmInetSocket ARGS((U8 type, CmInetFd *sockFd, U8 protocol));
#endif /* IPV6_SUPPORTED */
#else   /* CM_INET2 */ 
EXTERN S16 cmInetSocket ARGS((U8 type, CmInetFd *sockFd));
#endif  /* CM_INET2 */ 

/* cm_inet_x_001.main_22 1. Added new interface - cmInetFlushRecvBuf()
                               to flush the data from socket receive buffer. */
#ifdef CM_INET_FLUSH_RECV_BUF
EXTERN S16 cmInetFlushRecvBuf ARGS((CmInetFd *sockFd,
                               MsgLen *len,
                               S32 flags));
#endif /* CM_INET_FLUSH_RECV_BUF*/

EXTERN S16 cmInetBind ARGS((CmInetFd *sockFd, CmInetAddr *myAddr));
EXTERN S16 cmInetConnect ARGS((CmInetFd *sockFd, CmInetAddr *servAddr));
EXTERN S16 cmInetListen ARGS((CmInetFd *sockFd, S16 backLog));
EXTERN S16 cmInetAccept ARGS((CmInetFd *sockFd, CmInetAddr *fromAddr, 
                              CmInetFd *newSockFd));
#ifdef IPV6_OPTS_SUPPORTED
#ifdef LOCAL_INTF
EXTERN S16 cmInetRecvMsg ARGS((CmInetFd *sockFd, CmInetAddr *dstAddr, 
                               CmInetMemInfo *info, Buffer **mPtr, 
                               MsgLen *len, CmInetIpHdrParm *ipHdrParams,
                               CmInetLocalInf  *localIf, S32 flags));
#else
EXTERN S16 cmInetRecvMsg ARGS((CmInetFd *sockFd, CmInetAddr *dstAddr, 
                               CmInetMemInfo *info, Buffer **mPtr, 
                               MsgLen *len, CmInetIpHdrParm *ipHdrParams,
                               S32 flags));
#endif /* LOCAL_INTF */
#else
#ifdef LOCAL_INTF
EXTERN S16 cmInetRecvMsg ARGS((CmInetFd *sockFd, CmInetAddr *dstAddr, 
                               CmInetMemInfo *info, Buffer **mPtr, 
                               MsgLen *len, CmInetLocalInf  *localIf,
                               S32 flags));
#else
EXTERN S16 cmInetRecvMsg ARGS((CmInetFd *sockFd, CmInetAddr *dstAddr, 
                               CmInetMemInfo *info, Buffer **mPtr, 
                               MsgLen *len, S32 flags));
#endif /* LOCAL_INTF */
#endif /* IPV6_OPTS_SUPPORTED */
EXTERN S16 cmInetSendDscpMsg ARGS((CmInetFd *sockFd, CmInetAddr *dstAddr, 
                               CmInetMemInfo *info, Buffer *mBuf, MsgLen *len,
                               CmInetIpHdrParm *ipHdrParams, S16 flags));

#ifdef IPV6_OPTS_SUPPORTED
EXTERN S16 cmInetSendMsg ARGS((CmInetFd *sockFd, CmInetAddr *dstAddr, 
                               CmInetMemInfo *info, Buffer *mBuf, MsgLen *len,
                               CmInetIpHdrParm *ipHdrParams, S16 flags));
#else
EXTERN S16 cmInetSendMsg ARGS((CmInetFd *sockFd, CmInetAddr *dstAddr, 
                               CmInetMemInfo *info, Buffer *mBuf, MsgLen *len,
                               S16 flags));
#endif /* IPV6_OPTS_SUPPORTED */
EXTERN S16 cmInetPeek ARGS((CmInetFd *sockFd, CmInetAddr *fromAddr, 
                            CmInetMemInfo *info, MsgLen dataPos, 
                            MsgLen dataLen, U8 *data));
/* cm_inet_x_001.main_26: Added new function declaration cmInetPeekNew() */ 
EXTERN S16 cmInetPeekNew ARGS((CmInetFd *sockFd, CmInetAddr *fromAddr, 
                            CmInetMemInfo *info, MsgLen dataPos, 
                            MsgLen dataLen, U8 *data)); 
EXTERN S16 cmInetClose ARGS((CmInetFd *sockFd));
EXTERN S16 cmInetShutdown ARGS((CmInetFd *sockFd, S32 howTo));
EXTERN S16 cmInetSelect ARGS((CmInetFdSet *readFdS, CmInetFdSet *writeFdS, 
                              U32 *mSecTimeout, S16 *numFdS));
EXTERN S16 cmInetSetOpt ARGS((CmInetFd *sockFd, U32 level, U32 type, 
                             Ptr value));
EXTERN S16 cmInetGetNumRead ARGS((CmInetFd *sockFd, U32 *dataLen));
#ifndef SS_PS
EXTERN S16 cmInetGetHostByName ARGS((S8 *hostName, CmInetIpAddrTbl *addrTbl));
EXTERN S16 cmInetGetIpNodeByName ARGS((S8 *hostName, CmInetIpAddrArr *addrArr));
EXTERN S16 cmInetAddr ARGS((S8 *asciiAddr, CmInetIpAddr *address));
EXTERN S16 cmInetNtoa ARGS((CmInetIpAddr address, S8 **asciiAddr));
EXTERN S16 cmInetPton ARGS((CmInetIpAddr *address, S8 *asciiAddr));
#ifdef IPV6_SUPPORTED 
EXTERN S16 cmInetPton6 ARGS((CmInetIpAddr6 *address6, S8 *asciiAddr));
#endif /* IPV6_SUPPORTED */
#endif /*  SS_PS */
/* Function prototypes to peek into file descriptor set. */
#if (defined(WIN32) || defined(SUNOS) || defined(SS_LINUX) || defined(SS_VW) \
     || defined(HPOS))
EXTERN S16 cmInetFdSetInfoInit ARGS((CmInetFdSetInfo *fdSetInfo));
EXTERN S16 cmInetGetFd ARGS((CmInetFdSetInfo *fdSetInfo, CmInetFdSet *fdSet,
                             CmInetFdType *sockFd));
#endif /* WIN32 | SUNOS | SS_LINUX | SS_VW | HPOS */

EXTERN S16 cmInetGetMemSize      ARGS((S32 *size));
EXTERN S16 cmInetInit            ARGS((Void));
EXTERN S16 cmInetDeInit          ARGS((Void));
EXTERN S16 cmInetGetSockName     ARGS((CmInetFd *sockFd, CmInetAddr *locAddr));

EXTERN S16 cmInetConvertStrToIpAddr ARGS((U16 len, U8 *val,
                                          CmInetNetAddr *address));
EXTERN S16 cmInetAsciiToIpv4 ARGS((U8 numBytes, U8 *ipv4Addr,
                                   U16 len, U8 *val));


/* cm_inet_x_001.main_29 Poll Implementation Changes */
EXTERN S16 cmInetPoll ARGS((CmInetPollFd  *pollFdArr,U32 idx,S16  *numFdS,U32  timeout));
EXTERN S16 cmInetPollSetFd ARGS((CmInetFd  *sockFd,CmInetPollFd  *pollFdArr,S16  idx, U16  eventMask));
EXTERN S16 cmInetPollFdIsSet ARGS((CmInetPollFd  *pollFdArr, S16 idx, U16  eventMask));
EXTERN S16 cmInetPollClearFdREvent ARGS((CmInetPollFd  *pollFdArr, S16 idx, U16 eventMask));
EXTERN S16 cmInetPollClearFdEvent ARGS((CmInetPollFd  *pollFdArr,S16 idx, U16 eventMask));
EXTERN S16 cmInetPollDelFd ARGS((CmInetPollFd  *pollFdArr, S16 delIdx, S16  crntIdx));
EXTERN S16 cmInetPollInitFdArr ARGS((CmInetPollFd  *pollFdArr));

/* cm_inet_x_001.main_21:Added wrapper function for getaddrinfo and freeaddrinfo */
#if (!defined(SS_VW) && !defined(SS_PS) && !defined(WIN32))
EXTERN S32 cmInetGetAddrInfo ARGS((CONSTANT S8* node, CONSTANT S8* service, 
                                   CONSTANT CmInetAddrInfo *hints, CmInetAddrInfo **res));
EXTERN Void cmInetFreeAddrInfo ARGS((CmInetAddrInfo *res));
#endif /* SS_VW | SS_PS | WIN32 */

/*cm_inet_x_001.main_23 Updated for TUCL 2.1 Release (Kernel SCTP Support) */
#ifdef CM_LKSCTP
EXTERN S16 cmInetSctpBindx     ARGS((CmInetFd *sockFd, 
                                     CmInetNetAddrLst *addrLst, 
                                     U16 port));
EXTERN S16 cmInetSctpConnectx  ARGS((CmInetFd *sockFd, CmInetNetAddr *primAddr, 
                                     CmInetNetAddrLst *addrLst, 
                                     U16 port));
EXTERN S16 cmInetSctpPeelOff   ARGS((CmInetFd *sockFd, U32 assocId, 
                                     CmInetFdType *assocFd));
EXTERN S16 cmInetSctpSendMsg   ARGS((CmInetFd *sockFd, CmInetNetAddr *dstAddr, 
                                     U16 port, CmInetMemInfo *info, 
                                     Buffer *mBuf, MsgLen *len, U16 strmId,
                                     Bool unorderFlg, U16 ttl, U32 ppId, 
                                     U32 context));
EXTERN S16 cmInetSctpRecvMsg  ARGS((CmInetFd *sockFd, CmInetNetAddr *srcAddr, 
                                    U16 *port, CmInetMemInfo *info, 
                                    Buffer **mBuf, MsgLen *len, 
                                    CmInetSctpSndRcvInfo *sinfo, U32 *flag,
                                    CmInetSctpNotification *ntfy));
EXTERN S16 cmInetSctpGetPAddrs ARGS((CmInetFd *sockFd, U32 assocId, 
                                     CmInetNetAddrLst *addrlst));
EXTERN S16 cmInetGetOpt        ARGS((CmInetFd *sockFd, U32 level, U32 type,
                                     Ptr value)); 

/*cm_inet_x_001.main_25: Added new funcion */
EXTERN S16 cmInetShutDownSctp ARGS((CmInetFd *sockFd));
/*cm_inet_x_001.main_30: Added new function */
EXTERN S16 cmInetAbortSctpAssoc ARGS((CmInetFd *sockFd, UConnId assocId));
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __CMINETX__ */


/********************************************************************30**
 
         End of file:     cm_inet.x@@/main/31 - Fri Sep  7 13:00:05 2012
 
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
1.1          ---      mf   1. initial release.
1.2          ---      aa   1. Added extern definition of cmPkCmInetAddr and
                              cmUnpkCmInetAddr
1.3          ---      asa  1. Added Prototype for cmInetGetSockName,
                              cmInetDeInit.
                           2. Changed Prototype for cmInetSetOpt.
                           3. Added type CmInetMCastInf.
1.4          ---      asa  1. Changes for PSOS support.
                           2. Added type CmInetSockAddr.
1.5          ---      bbk  1. Added CmInetIpAddrTbl data structure.
/main/6                 cvp  1. Changed the copyright header.
             001.main_6 cvp  1. Changes for Linux support.
/main/8      ---      sb   1. Added backward compatibility flag for to Raw
                              Socket changes.
/main/8      ---      cvp  1. Adding a new type for socket descriptors.
                           2. New data structures to peek into the 
                              file descriptor sets.
                           3. Added function prototypes to peek into the 
                              file descriptor sets.
/main/9      ---      dvs  1. ClearCase release
/main/10     ---      cvp  1. IPv6 support added under the flag
                              IPV6_SUPPORTED
                           2. Changes for HP Unix under the flag 
                              HPOS.
                           3. Changed the copyright header.
/main/10+ 001.main_10 cvp  1. Removed packing/unpacking function prototypes.
                              Some products (eg - M3UA) need these functions
                              but do not compile cm_inet.c file.      
/main/10+ 002.main_10 mmh  1. Added 3rd arg to allocate memory required 
                              to hold datagrams from recvfrom() call.
/main/10+ 003.main_10 mmh  1. Removing 3rd arg MemInfo of cmInetGetNumRead.
/main/10+ 004.main_10 bdu  1. Add 2 more utility functions.
                           2. Add a new structure define.
/main/10+ 005.main_10 bdu  1. added protType in CmInetFd
                           2. added structure CmInetLocalInf
                           3. added new structures for IPv6 extension headers
                           4. changed prototypes of cmInetRecvMsg() and
                              cmInetSendMsg()
/main/10+ 006.main_10 rs   1. WINCE support.
/main/10+ 007.main_10 cg   1. VxWorks compilation for IPv6 Suppport 
/main/18     ---      pk   1. GCP 1.5 release
/main/18  001.main_18 ra   1. Patch to fix some bugs related to C++
                              compilation to make it in sync with /main/17.
/main/19     ---      dp   1. clearcase release for main/18 correction
/main/20     ---       kp   1. Removed conditional define CM_INET_FDSET_PEEK
/main/21     ---       sal  1. Redifining the CmInetIpAddr &  CmInetIpAddr6. 
cm_inet_x_001.main_21  ms   1. Added wrapper function for getaddrinfo and freeaddrinfo
                            2. Included netdb.h for getaddrinfo and freeaddrinfo
/main/23     --- cm_inet_x_001.main_22 svp  1. Added new interface - cmInetFlushRecvBuf()
                               to flush the data from socket receive buffer. 
/main/24     --- cm_inet_x_001.main_23 hs   1. Updated for TUCL 2.1 release
/main/25     --- cm_inet_x_001.main_24 cs   1. Updated for the support of configurable RTO parameters, HBeat value,
                                               Max retransmissions (Init, Path, Association)
/main/26     ---      cm_inet_x_001.main_25 ragrawal 1. Added new funcion cmInetShutDownSctp()
                                               under CM_LKSCTP flag.
/main/27  cm_inet_x_001.main_26  vsk  1. Added new function declaration cmInetPeekNew().
/main/28  cm_inet_x_001.main_27 ragrawal 1. Added new header file inclusion.
/main/29  cm_inet_x_001.main_28 ragrawal 1. Fix for compilation error at windows machine.
/main/30     ---      cm_inet_x_001.main_29 skumar   1. Poll Implementation changes.
/main/31     ---      cm_inet_x_001.main_30 mladdha  1. Added new funcion cmInetAbortSctpAssoc().
*********************************************************************91*/
