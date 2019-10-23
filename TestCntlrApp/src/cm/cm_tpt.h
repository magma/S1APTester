

/********************************************************************20**
  
        Name:     common transport file
    
        Type:     header file 
  
        Desc:     common file for transport related data structures
 
        File:     cm_tpt.h

        Sid:      cm_tpt.h@@/main/17 - Sat Jul  2 10:32:53 2011
  
        Prg:         
  
*********************************************************************21*/
#ifndef __CMTPTH__
#define __CMTPTH__

#include "cm_inet.h"
#ifdef CM_AAL
#include "cm_atm.h"
#endif

/* network address table size */
#define CM_MAX_NET_ADDR       16

/* network address sizes */

#define CM_IPV4ADDR_SIZE      CM_INET_IPV4ADDR_SIZE
#define CM_IPV6ADDR_SIZE      CM_INET_IPV6ADDR_SIZE

/* network address sizes */
#define CM_IPV4PORT_SIZE      CM_INET_IPV4PORT_SIZE
#define CM_IPV6PORT_SIZE      CM_INET_IPV4PORT_SIZE

/* "type" in network address */
#define CM_NETADDR_NOTPRSNT   0
#define CM_NETADDR_IPV4       CM_INET_IPV4ADDR_TYPE
#define CM_NETADDR_IPV6       CM_INET_IPV6ADDR_TYPE

/* "type" in transport address */
#define CM_TPTADDR_NOTPRSNT   0
#define CM_TPTADDR_IPV4       CM_INET_IPV4ADDR_TYPE
#define CM_TPTADDR_IPV6       CM_INET_IPV6ADDR_TYPE
#define CM_TPTADDR_AAL        3

#define CM_MAX_SOCK_OPTS      8

/* "type" in transport parameters */
#define CM_TPTPARAM_NOTPRSNT  0
#define CM_TPTPARAM_SOCK      1
#define CM_TPTPARAM_AAL       2
#define CM_TPTPARAM_TLS       3
/*cm_tpt_h_001.main_14 Updated for TUCL 2.1 Release (Kernel SCTP Support) */
#ifdef CM_LKSCTP
#define CM_TPTPARAM_SCTP      4
#endif

#define CM_INPORT_ANY         0

#ifdef   __CMINETH__ /* Put cm_inet dependencies here */

/* "level" in Socket Options */
#define CM_SOCKOPT_LEVEL_SOCKET      CM_INET_LEVEL_SOCKET
#define CM_SOCKOPT_LEVEL_IP          CM_INET_LEVEL_IP   
#define CM_SOCKOPT_LEVEL_TCP         CM_INET_LEVEL_TCP 
/*cm_tpt_h_001.main_14 Updated for TUCL 2.1 Release (Kernel SCTP Support) */
#ifdef CM_LKSCTP
#define CM_SOCKOPT_LEVEL_SCTP        CM_INET_LEVEL_SCTP 
#endif
/* cm_tpt_h_001.main_16: Added new macro to support filter for ICMP messages */
#ifdef CM_ICMP_FILTER_SUPPORT
#ifdef SS_LINUX
#define CM_SOCKOPT_LEVEL_RAW          CM_INET_LEVEL_RAW 
#endif
#endif

/* "option" in Socket Options */
#define CM_SOCKOPT_OPT_BLOCK         CM_INET_OPT_BLOCK
#define CM_SOCKOPT_OPT_REUSEADDR     CM_INET_OPT_REUSEADDR
#define CM_SOCKOPT_OPT_RX_BUF_SIZE   CM_INET_OPT_RX_BUF_SIZE
#define CM_SOCKOPT_OPT_TX_BUF_SIZE   CM_INET_OPT_TX_BUF_SIZE
#define CM_SOCKOPT_OPT_ADD_MCAST_MBR CM_INET_OPT_ADD_MCAST_MBR
#define CM_SOCKOPT_OPT_DRP_MCAST_MBR CM_INET_OPT_DRP_MCAST_MBR
#define CM_SOCKOPT_OPT_TCP_NODELAY   CM_INET_OPT_TCP_NODELAY
#define CM_SOCKOPT_OPT_MCAST_LOOP    CM_INET_OPT_MCAST_LOOP
#define CM_SOCKOPT_OPT_MCAST_IF      CM_INET_OPT_MCAST_IF
#define CM_SOCKOPT_OPT_MCAST_TTL     CM_INET_OPT_MCAST_TTL
#define CM_SOCKOPT_OPT_BROADCAST     CM_INET_OPT_BROADCAST
/* added KEEPALIVE socket option for TCP socket */
#define CM_SOCKOPT_OPT_KEEPALIVE     CM_INET_OPT_KEEPALIVE
#ifdef CM_INET2
#define CM_SOCKOPT_OPT_HDRINCLD      CM_INET_OPT_HDR_INCLD 
#define CM_SOCKOPT_OPT_DONTFRAGMENT  CM_INET_OPT_DONTFRAGMENT
#define CM_SOCKOPT_OPT_TOS           CM_INET_OPT_TOS
#define CM_SOCKOPT_OPT_TTL           CM_INET_OPT_TTL

#ifdef IPV6_SUPPORTED
/* "level" in Socket Options */
#define CM_SOCKOPT_LEVEL_IPV6          CM_INET_LEVEL_IPV6

/* "option" in Socket Options */
#define CM_SOCKOPT_OPT_ADD_MCAST6_MBR  CM_INET_OPT_ADD_MCAST6_MBR
#define CM_SOCKOPT_OPT_DRP_MCAST6_MBR  CM_INET_OPT_DRP_MCAST6_MBR
#define CM_SOCKOPT_OPT_MCAST6_LOOP     CM_INET_OPT_MCAST6_LOOP
#define CM_SOCKOPT_OPT_MCAST6_IF       CM_INET_OPT_MCAST6_IF
#define CM_SOCKOPT_OPT_MCAST6_HOPS     CM_INET_OPT_MCAST6_HOPS
#define CM_SOCKOPT_OPT_IPV6_TTL        CM_INET_OPT_IPV6_TTL

/* added new IPv6 socket options for IPv6 extn hdrs */
#ifdef IPV6_OPTS_SUPPORTED
#define CM_SOCKOPT_OPT_RECVIPV6_HOPLIM  CM_INET_OPT_RECVIPV6_HOPLIM
#define CM_SOCKOPT_OPT_RECVIPV6_HBHOPT  CM_INET_OPT_RECVIPV6_HBHOPTS
#define CM_SOCKOPT_OPT_RECVIPV6_DSTOPTS CM_INET_OPT_RECVIPV6_DSTOPTS
#define CM_SOCKOPT_OPT_RECVIPV6_RTHDR   CM_INET_OPT_RECVIPV6_RTHDR
#define CM_SOCKOPT_OPT_IP_ROUTER_ALERT6 CM_INET_OPT_IP_ROUTER_ALERT6
#endif /* IPV6_OPTS_SUPPORTED */
#define CM_SOCKOPT_OPT_IPV6_PKTINFO     CM_INET_OPT_IPV6_PKTINFO
#endif /* IPV6_SUPPORTED */

/* added new IPv4 socket options for IPv4 IP options */
#ifdef IPV4_OPTS_SUPPORTED
#define CM_SOCKOPT_OPT_IP_OPTIONS      CM_INET_OPT_IP_OPTIONS
#define CM_SOCKOPT_OPT_IPV4_PKTINFO    CM_INET_OPT_IPV4_PKTINFO
#define CM_SOCKOPT_OPT_IP_ROUTER_ALERT CM_INET_OPT_IP_ROUTER_ALERT
#endif /* IPV4_OPTS_SUPPORTED */

/* sctp socket options */
/*cm_tpt_h_001.main_14 Updated for TUCL 2.1 Release (Kernel SCTP Support) */
#ifdef CM_LKSCTP
#define CM_SOCKOPT_OPT_LINGER                 CM_INET_OPT_LINGER
#define CM_SOCKOPT_OPT_SCTP_EVENTS            CM_INET_OPT_SCTP_EVENTS
#define CM_SOCKOPT_OPT_SCTP_PRIM_ADDR         CM_INET_OPT_SCTP_PRIM_ADDR
#define CM_SOCKOPT_OPT_SCTP_PEERADDR_PARAMS   CM_INET_OPT_SCTP_PEERADDR_PARAMS
#define CM_SOCKOPT_OPT_SCTP_GET_ASSOC_STA     CM_INET_OPT_SCTP_GET_ASSOC_STA
#define CM_SOCKOPT_OPT_SCTP_GET_PADDR_INFO    CM_INET_OPT_SCTP_GET_PADDR_INFO
/*cm_tpt_h_001.main_15 Updated for the support of configurable RTO parameters, 
                        HBeat value Max retransmissions (Init, Path, Association)*/
#define CM_SOCKOPT_OPT_SCTP_ASSOC_PARAMS      CM_INET_OPT_SCTP_ASSOC_PARAMS
#define CM_SOCKOPT_OPT_SCTP_RTO_INFO          CM_INET_OPT_SCTP_RTO_INFO
#define CM_SOCKOPT_OPT_SCTP_INIT_MSG          CM_INET_OPT_SCTP_INIT_MSG
#endif

/* IP header masks */
#define   CM_DF_MASK        0x4000        /* Don't Fragment bit */
#define   CM_MF_MASK        0x2000        /* More Fragment bit  */

/* Protocol Values */
#define   CM_PROTOCOL_IP    CM_INET_PROTO_IP    /* IP   protocol */
#define   CM_PROTOCOL_ICMP  CM_INET_PROTO_ICMP  /* ICMP protocol */
#define   CM_PROTOCOL_TCP   CM_INET_PROTO_TCP   /* TCP  protocol */
#define   CM_PROTOCOL_UDP   CM_INET_PROTO_UDP   /* UDP  protocol */
#define   CM_PROTOCOL_RAW   CM_INET_PROTO_RAW   /* Raw  protocol */
#define   CM_PROTOCOL_SCTP  CM_INET_PROTO_SCTP  /* SCTP protocol */
/*cm_tpt_h_001.main_14 Updated for TUCL 2.1 Release (Kernel SCTP Support) */
#ifdef CM_LKSCTP
#define   CM_PROTOCOL_LKSCTP  CM_INET_PROTO_SCTP  /* SCTP protocol */
#endif
/* added new protocol */
#define   CM_PROTOCOL_RSVP  CM_INET_PROTO_RSVP  /* RSVP protocol */

#ifdef IPV6_SUPPORTED 
#define   CM_PROTOCOL_IPV6   CM_INET_PROTO_IPV6   /* IPV6 protocol */
#define   CM_PROTOCOL_ICMPV6 CM_INET_PROTO_ICMPV6 /* ICMP V6 protocol */
#endif /* IPV6_SUPPORTED */

#ifdef CM_TLS
#define   CM_PROTOCOL_TLS    CM_PROTOCOL_TCP      /* TLS runs over TCP */
#endif

/* Type of service parameters */
#define   CM_IPTOS_MIN_DELAY  0x10
#define   CM_IPTOS_MAX_TPUT   0x08
#define   CM_IPTOS_MAX_REL    0x04

/* Maximum Error Types */
#define   CM_MAX_ICMP_ERROR      5
/* cm_tpt_h_001.main_16: Added new macro to support filter for ICMP messages */
#ifdef CM_ICMP_FILTER_SUPPORT
#ifndef CM_MAX_ICMP_SOCKET
#define   CM_MAX_ICMP_SOCKET     5
#endif
#ifdef IPV6_SUPPORTED
#define  CM_MAX_ICMPV6_MSGTYPE    140
#endif
#endif

/* ICMP Error Types */
#define   CM_ICMP_ET_DEST_UNREACHBLE  3
#define   CM_ICMP_ET_SRC_QUENCH       4
#define   CM_ICMP_ET_REDRCT           5
#define   CM_ICMP_ET_TIM_EXCEED       11 
#define   CM_ICMP_ET_PARAM_PROB       12 

/* ICMPV6 Error Types */
#ifdef IPV6_SUPPORTED 
#define   CM_ICMP_ET_V6DEST_UNREACHABLE        1
#define   CM_ICMP_ET_V6PACKET_TOO_BIG          2 
#define   CM_ICMP_ET_V6PACKET_TIME_EXCEEDED    3 
#define   CM_ICMP_ET_V6PACKET_PARAM_PROB       4 
#endif /* IPV6_SUPPORTED */

/* ICMP Error Codes - destination unreachable  */
#define   CM_ICMP_EC_NWK_UNREACH    0
#define   CM_ICMP_EC_HST_UNREACH    1
#define   CM_ICMP_EC_PROTO_UNREACH  2
#define   CM_ICMP_EC_PORT_UNREACH   3
#define   CM_ICMP_EC_FRAG_REQ_DFSET 4
#define   CM_ICMP_EC_SRC_RUT_FAIL   5

/* ICMP Error Codes - Source Quench */
#define   CM_ICMP_EC_SRC_QUENCH     4

/* ICMP Error Codes - Redirect */
#define   CM_ICMP_EC_RDRCT_NWK       0 
#define   CM_ICMP_EC_RDRCT_HST       1  
#define   CM_ICMP_EC_RDRCT_TOSNWK    2
#define   CM_ICMP_EC_RDRCT_TOSHST    3

/* ICMP Error codes - Time exceeded */
#define   CM_ICMP_EC_TTL_TRNST   0
#define   CM_ICMP_EC_TTL_REASM   1

/* ICMP V6 Error codes */
#ifdef IPV6_SUPPORTED
/* Error codes - Destination unreachable */
#define CM_ICMPV6_EC_NO_RTTO_DEST   0
#define CM_ICMPV6_EC_ADMN_PROHIBIT  1
#define CM_ICMPV6_EC_NOT_NEIGHBOR   2
#define CM_ICMPV6_EC_ADDR_UNREACH   3
#define CM_ICMPV6_EC_PORT_UNREACH   4

/* Error codes - Time exceeded */
#define CM_ICMPV6_EC_HOPLIM_EXCD       0
#define CM_ICMPV6_EC_FRG_REASM_TM_EXCD 1

/* Error codes - Paramter problem */
#define CM_ICMPV6_EC_ERRHDR_FIELD      0
#define CM_ICMPV6_EC_UNKNOWN_NXT_HDR   1
#define CM_ICMPV6_EC_UNKNOWN_OPTION    2

#endif /* IPV6_SUPPORTED */

/* types of Filter parameter */
#define CM_ICMP_NO_FILTER   0
#define CM_ICMPVER4_FILTER  CM_INET_IPV4ADDR_TYPE  
#define CM_ICMPVER6_FILTER  CM_INET_IPV6ADDR_TYPE  

/* For all Error code in a particular Error type */
#define CM_ALL_CODES_MASK      0xFFFFFFFF

/* types of header parameter */
#define CM_HDRPARM_NOTPRSNT   0  
#define CM_HDRPARM_IPV4       CM_INET_IPV4ADDR_TYPE  
#define CM_HDRPARM_IPV6       CM_INET_IPV6ADDR_TYPE  
/* added new define for ipHdrParm.type */
#define CM_HDRPARM_ICMP6      1

#define CM_IPV4_HDRLEN        20  /* Length of IP Header */
#define CM_IPV6_HDRLEN        40  /* Length of IP Header */
/* added new new define for IPv4 IP option */
#define CM_IPV4_OPTS_MAXLEN   44  /* Max length of IPv4 Options */ 
#endif  /* CM_INET2 */ 

#define CM_INADDR_ANY               CM_INET_INADDR_ANY

#define CM_SOCKOPT_ENABLE           CM_INET_OPT_ENABLE
#define CM_SOCKOPT_DISABLE          CM_INET_OPT_DISABLE
#endif /* __CMINETH__ */

/*  packing/unpacking functions */
#define cmPkCmIpv4NetAddr(x, mBuf)    SPkU32(x, mBuf)
/* Moved all packing functions to cm_tpt from 
 * cm_inet.c files. Hence no #defines are required */
#define cmUnpkCmIpv4NetAddr(x, mBuf)  SUnpkU32(x, mBuf)

/* added macro to free memory allocated for IPv6
 *                      IPv6 extn hdrs*/
#ifdef IPV6_OPTS_SUPPORTED
#define CM_TPT_FREE_IPV6_HDRPARM(_region, _pool, _hdrParm) \
{ \
   CmIpv6HdrParm *_hdrParmIpv6; \
   U8 numOpts; \
   if (_hdrParm->type == CM_HDRPARM_IPV6) \
   { \
      _hdrParmIpv6 = &_hdrParm->u.hdrParmIpv6; \
      if( _hdrParmIpv6->ipv6ExtHdr.hbhHdrPrsnt) \
      { \
         for(numOpts = _hdrParmIpv6->ipv6ExtHdr.hbhOptsArr.numHBHOpts;  \
            numOpts > 0; numOpts--) \
         { \
            SPutSBuf(_region, _pool, (Data *)_hdrParmIpv6->ipv6ExtHdr. \
                 hbhOptsArr.hbhOpts[numOpts - 1].value, (Size)(_hdrParmIpv6-> \
                 ipv6ExtHdr.hbhOptsArr.hbhOpts[numOpts - 1].length)); \
            SPutSBuf(_region, _pool, (Data *)&_hdrParmIpv6->ipv6ExtHdr. \
                 hbhOptsArr.hbhOpts[numOpts - 1], \
                 (Size)sizeof(CmInetIpv6HBHHdr)); \
         }  \
      } \
      if(_hdrParmIpv6->ipv6ExtHdr.destOptsPrsnt) \
      { \
         for(numOpts = _hdrParmIpv6->ipv6ExtHdr.destOptsArr.numDestOpts; \
            numOpts > 0; numOpts--) \
         { \
            SPutSBuf(_region, _pool, (Data *)_hdrParmIpv6->ipv6ExtHdr. \
               destOptsArr.destOpts[numOpts - 1].value, (Size)(_hdrParmIpv6-> \
               ipv6ExtHdr.destOptsArr.destOpts[numOpts - 1].length)); \
            SPutSBuf(_region, _pool, (Data *)&_hdrParmIpv6->ipv6ExtHdr. \
               destOptsArr.destOpts[numOpts - 1], \
               (Size)sizeof(CmInetIpv6DestOptsHdr)); \
         } \
      } \
      if( _hdrParmIpv6->ipv6ExtHdr.rtOptsPrsnt) \
      { \
         SPutSBuf(_region, _pool, \
               (Data *)_hdrParmIpv6->ipv6ExtHdr.rtOpts.ipv6Addrs, \
               (Size)(_hdrParmIpv6->ipv6ExtHdr.rtOpts.numAddrs * 16)); \
      } \
   } \
}
#endif /* IPV6_OPTS_SUPPORTED */
#endif /* __CMTPTH__ */
 

/********************************************************************30**
 
         End of file:     cm_tpt.h@@/main/17 - Sat Jul  2 10:32:53 2011
 
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
                              type and AAL transport parameters.
                           2. Moved include of cm_inet.h into this file
                              from the cm_tpt.c file.
             /main/4                 sb   1. Added flag for backward compatibility,due
                              to Raw socket changes.
                           2. Changed the copyright header.
/main/5      ---      cvp  1. IPV6 related changes.
                           2. changed the copyright header.
/main/6      ---      cvp  1. moved packing and unpacking functions from 
                              cm_inet to cm_tpt files.
/main/7      ---      mmh  1. Added CM_SOCKOPT_OPT_BROADCAST.   
/main/8      ---      bdu  1. Added CM_SOCKOPT_OPT_KEEPALIVE.
/main/9      ---      vj   1. merged IPV6 changes with GCP 1.3 release
/main/10     ---      mmh  1. Added new IPv6 socket options for IPv6 extn hdrs
                           2. Added new IPv4 socket options for IPv4 IP options
                           3. Added new protocol CM_PROTOCOL_RSVP
                           4. Added new new define CM_IPV4_OPTS_MAXLEN 
                              for IPv4 IP option
                           5. Added macro to free memory allocated for IPv6
                              IPv6 extn hdrs
/main/11     ---      mj   1. MPLS release 1.2 changes.
/main/12     ---      bdu  1. Added new define for ipHdrParm.type.
/main/13     ---      wh   1. SIP 2.1 release changes.
/main/14     ---      kp   1. TUCL 1.5 release changes. Added TLS
                              related defines.
/main/15     ---   cm_tpt_h_001.main_14      hs   1. Updated for TUCL 2.1 release
/main/16     ---   cm_tpt_h_001.main_15      cs   1. Updated for the support of configurable RTO parameters, HBeat value,
                                                     Max retransmissions (Init, Path, Association)
/main/17     ---   cm_tpt_h_001.main_16 ragrawal 1. Added new macro to support filter for ICMP messages. 
*********************************************************************91*/
