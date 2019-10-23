/********************************************************************20**
        Name:    eGTP-U Thin Socket Layer

        Type:    C source file

        Desc:    Source code for Thin Socket Layer functions such as,

                 - EgTLBndReq
                 - egTLbuildRecvBuf
                 - egTLBuildRecvMsg
                 - egTLBuildSendIovec
                 - egTLCloseServerReq
                 - EgTLDiscServerReq
                 - EgTLInitReq
                 - EgTLOpenServerReq
                 - EgTLReadMsg
                 - egTLRecvSockMsg
                 - egTLRegisterSocketForEPoll
                 - EgTLSendMsg
                 - egTLSendSockMsg
                 - EgTLThShutdownReq
                 - EgTLUbndReq


        File:    eg_socklayer.c

        Sid:      eg_socklayer.c@@/main/TeNB_Main_BR/TeNB_4.0_OAM_CR/1 - Wed Dec 10 19:13:44 2014

        Prg:     magnihot

*********************************************************************21*/



/* header include files -- defines (.h) */
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/ioctl.h>
#include <errno.h>
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_hash.h"       /* common hashing */
#include "cm_llist.h"      /* common linked list */
#include "cm5.h"           /* common timer */
#include "cm_inet.h"       /* common network address */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"      /* common DNS library */

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_hash.x"       /* common hashing */
#include "cm_llist.x"      /* common linked list */
#include "cm_lib.x"        /* common library */
#include "cm5.x"           /* common timer */
#include "cm_inet.x"       /* common network address */
#include "cm_tpt.x"        /* common transport address */
#include "cm_dns.x"        /* common DNS library */

#include "leg.h"
#include "egt.h"
#include "eg_edm.h"
#include "eg.h"
#include "leg.x"
#include "egt.x"
#include "eg_edm.x"
#include "eg.x"
#include "eg_socklayer.h"
#include "eg_socklayer.x"

#ifdef NTL_LIB
#include "ntl_lib.h"
#include "ksd_msg.h"
#endif

/* EGTP Statistics for debugging*/
U32 g_egtpSockDropsDueToReason19;
/* EGTP Statistics for debugging*/
#ifdef NTL_LIB
int ntl_hLib = -1;
#endif

EXTERN  Void EgTLSendEgtpMsg(Bool);
#ifndef LTE_ENB_PAL
typedef struct egMsgData
{
   struct cmsghdr hdr;
   U8   data;
}EgMsgData;
#endif

U32 egTLUplnkSocket; /*!< Workaround for Uplink ZBC: Socket is used to send Uplink Traffic */

PUBLIC S16 egFpTunProcEguDatReq
 (
 U32 lclTeid,
 U32 remTeid,
 U8  tos,
 U32 tPduSise,
 Buffer *mBuf
 );
#ifdef ENB_CPU_OVERLOAD_CONTROL
/* !< The upper threshold for IDLE CPU to increase the number of packets
 * to be read from socket to control the CPU load
 */
U32 idleCpuUpperThrsh = EG_IDLE_CPU_UPPER_THRESHOLD;
/* !< The lower threshold for IDLE CPU to decrease the number of packets
 * to be read from socket to control the CPU load
 */
U32 idleCpuLowerThrsh = EG_IDLE_CPU_LOWER_THRESHOLD;

EXTERN U32 ssGetTimerTick(Void);

#endif /* ENB_CPU_OVERLOAD_CONTROL */

PacketInfo packetData;
#ifdef S1SIMAPP
struct timespec tsStart1;
#endif
/*Private Function Declaration*/
/** @details
 * This primitive is used by Thin Layer to close any existing open socket.
 *
 * @param [in]   connId  -  Connection Id of the socket to be closed.
 *
 * @return  ROK, RFAILED
 */
#ifndef DHI
PRIVATE U32 egTLCloseServerReq
(
U32 connId             /* !< Connection Id of the socket to be closed. */
);
#endif 
/** @details
 *     This function is used by ThinLayer to build I/O vector to send a message.
 *
 * @param [in]   mBuf    -  Message buffer
 * @param [in]   msgLen   - Length of mBuf
 * @param [out]   txArr  -   transmit scatter vector array
 * @param [in]   numDBufs  - Maximum number of dBufs to use
 * @param [in]   numIovElems   -  Number of iov elements in array
 * @param [in]  strtEndDBufNum    -  dBuf number to start and end
 * @param [in]  ioLen    -  Len of dbuf packed into IO-vector
 *
 *
 * @return     ROK     - successful
 *             RFAILED - failed
 *             ROUTRES - failed, out of resources
 *             RNA     - failed, not available, indicates that the
 *                       maximum number of dBufs are not sufficient
 *                       to hold the entire message
 */
PRIVATE S16 egTLBuildSendIovec
(
    Buffer         *mBuf,           /* Message buffer */
    MsgLen         msgLen,          /* Length of mBuf */
    CmInetIovec    txArr[],         /* transmit scatter vector array */
    S16            numDBufs,        /* Maximum number of dBufs to use */
    S16            *numIovElems,    /* Number of iov elements in array */
    U32            *strtEndDBufNum, /* dBuf number to start and end */
    MsgLen         *ioLen           /* Len of dbuf packed into IO-vector */
);

/** @details
 * This primitive is used by Thin Layer to send data on a socket.s
 *
 * @param [in]   sockFd       -  Socket Fd on which data needs to be sent
 * @param [in]   dstAddr      -  Destination IP Address
 * @param [in]   info         -  Memory Info
 * @param [in]   mBuf         -  Buffer to be sent out
 * @param [out]   len         -  Number of actually sent octets
 * @param [in]   ipHdrParams  -  IPv6 extensions headers
 * @param [in]   flags        -  Additional control flags, unused
 *
 * @return  ROK, RFAILED
 */
#if 0
PRIVATE S16 egTLSendSockMsg
(
    CmInetFd       *sockFd,         /* socket file descriptor */
    CmInetAddr     *dstAddr,        /* destination Internet address/port */
    CmInetMemInfo  *info,           /* buffer allocation info */
    Buffer         *mBuf,           /* buffer structure to send */
    MsgLen         *len,            /* number of actually sent octets */
    /* added for IPv6 ext hdr */
#ifdef IPV6_OPTS_SUPPORTED
    CmInetIpHdrParm *ipHdrParams,   /* IPv6 extensions headers */
#endif /* IPV6_OPTS_SUPPORTED */
    S16             flags           /* additional control flags, unused */
);
#endif
/** @details
               This functon reads data from a socket into a message.
 *             The buffers for the message  are allocated within the
 *             cmInetRead() function from the pool and region Id set in the
 *             info struct.
 *             If the number of octets given by the paramter len is not
 *             available the function immediately returns with RKDNA.
 *             If the len parameter is set to CM_INET_READ_ANY, the currently
 *             available data is read.
 *             Values for flag parameter:
 *
 *             CM_INET_NO_FLAG  - no additional control flag
 *             CM_INET_MSG_PEEK - do not destroy data on receive buffer
 *
 * @param [in]   sockFd       -  Socket Fd on which data needs to be sent
 * @param [in]   dstAddr      -  Destination IP Address
 * @param [in]   info         -  Memory Info
 * @param [in]   mBuf         -  Buffer to be sent out
 * @param [out]  len          -  Number of actually sent octets
 * @param [in]   ipHdrParams  -  IPv6 extensions headers
 * @param [in]   flags        -  Additional control flags, unused
 *
 * @return    ROK     - successful
 *             ROKDNA  - ok, data not available
 *             RCLOSED - connection closed by peer
 *             ROUTRES - failed, out of resources
 *             RFAILED - failedROK, RFAILED
 */
#if 0
PRIVATE S16 egTLRecvSockMsg
(
    CmInetFd        *sockFd,        /* socket file descriptor */
    CmInetAddr      *fromAddr,      /* sender Internet address/port */
    CmInetMemInfo   *info,          /* buffer allocation info */
    Buffer         **mPtr,          /* received buffer structure */
    MsgLen          *len,           /* number of octets to read */
    /*  added for IPv6 */
#ifdef IPV6_OPTS_SUPPORTED
    CmInetIpHdrParm *ipHdrParams,    /* IPv6 extensions headers */
#endif /* IPV6_OPTS_SUPPORTED */
#ifdef LOCAL_INTF
    CmInetLocalInf  *localIf,       /* local interface on which pkt was recvd */
#endif /* LOCAL_INTF */
    S32              flags          /* additional control flags */
);
#endif
#if 0
/** @details
 *     This function is used by ThinLayer to build a message out of the received dBufs.
 *
 * @param [in]   info    -  buffer allocation info
 * @param [in]   rxArr   -  scatter array
 * @param [in]   numBuf  -  number of allocated dBufs
 * @param [in]   msgLen  -  message length
 * @param [in]  dBufs   -  dBufs
 * @param [out]   mPtr    -  message built from dBufs
 *
 * @return    ROK     - successful
 *            ROKDNA  - ok, data not available
 *            RFAILED - failedROK, RFAILED
 */

PRIVATE S16 egTLBuildRecvMsg
(
    CmInetMemInfo  *info,           /* buffer allocation info */
    CmInetIovec     rxArr[],        /* scatter array */
    S16             numBuf,         /* number of allocated dBufs */
    MsgLen          msgLen,         /* message length */
    Buffer         *dBufs[],        /* dBufs */
    Buffer        **mPtr            /* message built from dBufs */
);
#endif

#if 0
PRIVATE S16 egTLbuildRecvBuf
(
CmInetMemInfo  *info,           /* buffer allocation info */
MsgLen          len,            /* message length */
CmInetIovec     rxArr[],        /* gather array */
Buffer         *dBuf[],         /* allocated dBufs */
U16             maxSize,        /* size of rxArr/dBuf array */
struct msghdr  *msg,            /* message header for recvmsg() */
Bool           isStrmMsg        /* Is a TCP message */
);
#endif

/*Private Function Declaration*/
#ifdef FLAT_BUFFER_OPT
/** @details
 * This primitive is used by Thin Layer to receive messages from ZBC Socket.
 *
 * @param [in]   sockFd  -  Socket FD to use for reading messages.
 * @param [out]  remAddr -  Source address of the received packet.
 * @param [out]  mBuf    -  Buffer containing read packet from the socket.
 * @return  ROK, RFAILED
 */
PRIVATE S16 egTLRecvZbcUdpMsgFB
(
U32           sockFd,
CmTptAddr     *remAddr,
U8            **recvBuf,
U32           *bufLen
);
#endif

/** @details
 * This primitive is used by Thin Layer to receive messages from ZBC Socket.
 *
 * @param [in]   sockFd  -  Socket FD to use for reading messages.
 * @param [in]   memInfo -  Memory related information.
 * @param [out]  remAddr -  Source address of the received packet.
 * @param [out]  mBuf    -  Buffer containing read packet from the socket.
 * @return  ROK, RFAILED
 */

#if (defined(TENB_T2K3K_SPECIFIC_CHANGES)) && (!defined(TENB_DISABLE_DL_ZBC))
PRIVATE S16 egTLRecvZbcUdpMsg
(
U32 sockFd,
CmTptAddr *remAddr,
CmInetMemInfo memInfo,
Buffer             **mBuf
);
#endif
#ifdef FLAT_BUFFER_OPT
/** @details
 * This primitive is used by Thin Layer to receive messages from ZBC Socket.
 *
 * @param [in]   sockFd  -  Socket FD to use for reading messages.
 * @param [out]  remAddr -  Source address of the received packet.
 * @param [out]  mBuf    -  Buffer containing read packet from the socket.
 * @return  ROK, RFAILED
 */
PRIVATE S16 egTLHndlRecv
(
EgTLServerCb       *egTLServerCb,
U8                 *recvBuf,
U32                bufLen,
CmTptAddr          *remAddr
);
#endif

/*Private Function Declaration*/
#ifdef FLAT_BUFFER_OPT
#if !((defined(TENB_T2K3K_SPECIFIC_CHANGES)) && (!defined(TENB_DISABLE_DL_ZBC)))
/** @details
 * This primitive is used by Thin Layer to receive messages from non-ZBC Socket.
 *
 * @param [in]   sockFd  -  Socket FD to use for reading messages.
 * @param [in]   memInfo -  Memory related information.
 * @param [out]  remAddr -  Source address of the received packet.
 * @param [out]  mBuf    -  Buffer containing read packet from the socket.
 * @return  ROK, RFAILED
 */
PRIVATE S16 egTLRecvMsgFromSocketFB
(
U32        sockFd,
CmTptAddr *remAddr,
U8        *buf,
U32       *bufLen
);
#endif /* #if !((defined(TENB_T2K3K_SPECIFIC_CHANGES)) && (!defined(TENB_DISABLE_DL_ZBC)))*/
#endif

/** @details
 * This primitive is used by Thin Layer to receive messages from non-ZBC Socket.
 *
 * @param [in]   sockFd  -  Socket FD to use for reading messages.
 * @param [in]   memInfo -  Memory related information.
 * @param [out]  remAddr -  Source address of the received packet.
 * @param [out]  mBuf    -  Buffer containing read packet from the socket.
 * @return  ROK, RFAILED
 */
/*fix for ccpu00136421 */
#if !((defined(TENB_T2K3K_SPECIFIC_CHANGES)) && (!defined(TENB_DISABLE_DL_ZBC)))
PRIVATE S16 egTLRecvMsgFromSocket
(
U32 sockFd,
CmTptAddr *remAddr,
CmInetMemInfo memInfo,
Buffer             **mBuf
);
#endif

PRIVATE U32 egTLQueueAddOne(U32 idx);
#ifdef ENB_CPU_OVERLOAD_CONTROL
PRIVATE U32 egGetQueueLen(U32 front, U32 rear);
PRIVATE Void egUpdPktsUsingCpuInfo(Void);
PRIVATE Void egUpdPktsUsingQueuInfo(U32 rear, U32 front);
PRIVATE U32 egGetNumPacketsToSend(Void);
PRIVATE U32 egGetNumPacketsToRead(Void);
PUBLIC Void egUpdatePacketInfo(Void);
#endif /* ENB_CPU_OVERLOAD_CONTROL */

/** @details
 * This primitive is used for getting the next index of circular buffer used
 * in UL to store the messages in uplink direction. It takes cares of wrap 
 * around case also and returns the next index which needs to be used for 
 * storing the message
 *
 * @return  index to the queue
 */

PRIVATE U32 egTLQueueAddOne(U32 idx)
{
   /* */
   RETVALUE((idx + 1) & (MAX_QUEUE_LEN - 1));
}
#ifdef TENB_UL_FP
PUBLIC S16 egFpTunProcEguDatReq
(
U32 lclTeid,       /* Event from UI */
U32 remTeid,
U8  tos,
U32 tPduSize,
Buffer* mBuf
);
#endif


#ifdef ENB_CPU_OVERLOAD_CONTROL
/** @details
 * This primitive is used for getting the UL queue length which stores the
 * uplink message. This will be used to apply the CPU control algorithm to
 * control the CPU.
 *
 * @return  length of the queue
 */

PRIVATE U32 egGetQueueLen(U32 front, U32 rear)
{
   if(rear < front)
   {
      RETVALUE((rear - front) + MAX_QUEUE_LEN);
   }
   else
   {
      RETVALUE(rear - front);
   }
}
#endif /* ENB_CPU_OVERLOAD_CONTROL */


#ifndef DHI
/** @details
 * This primitive is used by eGTP-U to open server for Tx/Rx of Data
 *
 * @param [in]   pst         -  Post Structure
 * @param [in]   spId        -  Service Provider Id
 * @param [in]   servConId   -  Server Connection Id
 * @param [in]   servTAddr   -  Server Address
 * @param [in]   tPar        -  Transport Parameters
 *
 * @return  ROK, RFAILED
 */
#ifdef ANSI
PUBLIC U32 EgTLOpenServerReq
(
Pst          *pst,
SpId         spId,                       /* SAP ID */
UConnId      servConId,                  /* Server Connection*/
CmTptAddr    *servTAddr                 /* Address */
)
#else
PUBLIC U32 EgTLOpenServerReq(pst, spId, servConId, servTAddr)
Pst          *pst,
SpId         spId,                       /* SAP ID */
UConnId      servConId,                  /* Server Connection*/
CmTptAddr    *servTAddr                 /* Address */
#endif
{
    Pst cfmPst;
    struct sockaddr_in srcAddr;
    struct sockaddr_in *sockAddrPtr;
#ifdef IPV6_SUPPORTED
    struct sockaddr_in6 srcAddr6; /* local IPV6 address/port */
#endif /* IPV6_SUPPORTED */
    U32 sizeOfAddr;
/* klocworks: Initialize the ret value */    
    S32 ret= SOCK_ERROR;
    EgTLServerCb *egTLServerCb;
    S32 domain;

#ifdef ERRCHK
    if ((MAX_SERVER_NUM <= servConId
            || (egTLCb.servers[servConId].sockFd != SOCK_ERROR)))
    {
#ifdef ALIGN_64BIT
        printf("\n Incorrect Connection Id = [%d]",servConId);
#else
        printf("\n Incorrect Connection Id = [%ld]",servConId);
#endif
        RETVALUE(RFAILED);
    }

    if(NULLP == servTAddr)
    {
        printf("\n Incorrect Connection Parameters Id ServerAddr=[%p]",(Void *)servTAddr);
        /*Make and send a Message for failure to open server*/
        RETVALUE(RFAILED);
    }

#endif

#ifdef IPV6_SUPPORTED
    if (servTAddr->type == CM_INET_IPV6ADDR_TYPE)
    {
        cmMemset((U8*)&srcAddr6, 0, sizeof(srcAddr6));
        srcAddr6.sin6_family      = AF_INET6;
        srcAddr6.sin6_port        = CM_INET_HTON_U16(servTAddr->u.ipv6TptAddr.port);
        CM_INET_COPY_IPV6ADDR(&srcAddr6.sin6_addr,
                              &servTAddr->u.ipv6TptAddr.ipv6NetAddr);
        sizeOfAddr               = sizeof(struct sockaddr_in6);
        sockAddrPtr              = (struct sockaddr_in *)&srcAddr6;
        domain                   = AF_INET6;
    }
    else
#endif
    {
        cmMemset((U8*)&srcAddr, 0, sizeof(srcAddr));
        srcAddr.sin_family      = AF_INET;
        srcAddr.sin_port        = CM_INET_HTON_U16(servTAddr->u.ipv4TptAddr.port);
        srcAddr.sin_addr.s_addr = CM_INET_HTON_U32(servTAddr->u.ipv4TptAddr.address);
        sizeOfAddr               = sizeof(struct sockaddr_in);
        sockAddrPtr              = (struct sockaddr_in *)&srcAddr;
        domain                   = AF_INET;
    }

    egTLServerCb = &egTLCb.servers[servConId];


#if (defined(TENB_T2K3K_SPECIFIC_CHANGES)) && (!defined(TENB_DISABLE_DL_ZBC))

#ifdef NTL_LIB
    printf ("NTL Lib attach\n");
#ifdef T2200_2GB_DDR_CHANGES
    ntl_hLib = ntl_init(1024*6, 779, 0);
#else
    //ntl_hLib = ntl_init(1024*3, 779, 0); TODO: verify why this is changed
    ntl_hLib = ntl_init(1024, 779, 0);
#endif
    printf ("NTL Lib HANDLE: %d\n", ntl_hLib);
#endif
    /*!< Open a ZBC Socket in Downlink Direction */
#ifdef EG_IPV6_SUPPORTED
    if (servTAddr->type == CM_INET_IPV6ADDR_TYPE)
    {
      if(EGTPU_PORT == servTAddr->u.ipv6TptAddr.port)
      {
       
#ifdef NTL_LIB    
          if (ntl_hLib < 0)
              egTLServerCb->sockFd = socket(domain,(SOCK_DGRAM | EG_SOCK_TYPE),0);
          else
          {
      	       egTLServerCb->sockFd = ntl_socket(ntl_hLib, domain,(SOCK_DGRAM | EG_SOCK_TYPE),IPPROTO_UDP);
#ifdef NTL_LIB_DIS_FOR_UL
              /* Adding Seprate Socket for TX without NTL */
               egTLServerCb->sockFdUL = socket(AF_INET,(SOCK_DGRAM | (1 << 30)),0);
               printf(" egTLServerCb->sockFdUL created in UL is %lu \n", egTLServerCb->sockFdUL);
#endif /* NTL_LIB_DIS_FOR_UL */
          }
#else 
          egTLServerCb->sockFd = socket(domain,(SOCK_DGRAM | EG_SOCK_TYPE),0);
#endif

      }
    }
    else
#endif /* EG_IPV6_SUPPORTED */
    {
      if(EGTPU_PORT == servTAddr->u.ipv4TptAddr.port)
      {
       
#ifdef NTL_LIB    
          if (ntl_hLib < 0)
              egTLServerCb->sockFd = socket(domain,(SOCK_DGRAM | EG_SOCK_TYPE),0);
          else
          {
      	       egTLServerCb->sockFd = ntl_socket(ntl_hLib, domain,(SOCK_DGRAM | EG_SOCK_TYPE),IPPROTO_UDP);
#ifdef NTL_LIB_DIS_FOR_UL
              /* Adding Seprate Socket for TX without NTL */
               egTLServerCb->sockFdUL = socket(AF_INET,(SOCK_DGRAM | (1 << 30)),0);
               printf(" egTLServerCb->sockFdUL created in UL is %lu \n", egTLServerCb->sockFdUL);
#endif /* NTL_LIB_DIS_FOR_UL */
          }
#else 
          egTLServerCb->sockFd = socket(domain,(SOCK_DGRAM | EG_SOCK_TYPE),0);
#endif

      }
    }

    /*!<Create Non-ZBC Socket for Uplink Direction*/
    egTLUplnkSocket = socket(domain,SOCK_DGRAM,IPPROTO_UDP);

    if((SOCK_ERROR == egTLServerCb->sockFd) || (SOCK_ERROR == egTLUplnkSocket))
    {
       printf("\n Unable to Get a ZBC socket Descriptor, Failed with reason =[%d]",errno);
       RETVALUE(RFAILED);
   }
#else
   egTLServerCb->sockFd = socket(domain,SOCK_DGRAM,0);
   if((SOCK_ERROR == egTLServerCb->sockFd))
   {
        printf("\n Unable to Get a socket Descriptor, Failed with reason =[%d]",errno);
        RETVALUE(RFAILED);
    }
#endif

    /* Set socket option for Non-Blocking*/
    egTLServerCb->isSocketNonBlocking = TRUE;
#ifdef NTL_LIB
    if (ntl_hLib < 0)
        ret = ioctl(egTLServerCb->sockFd, FIONBIO, &egTLServerCb->isSocketNonBlocking);
    else
        printf ("NTL: skipped ioctl for socket 0x%ld\n", egTLServerCb->sockFd);
#else 
    ret = ioctl(egTLServerCb->sockFd, FIONBIO, &egTLServerCb->isSocketNonBlocking);
#endif



#ifdef NTL_LIB
    if (SOCK_ERROR == ret && ntl_hLib < 0)
#else
    if (SOCK_ERROR == ret)
#endif 
    {
#ifdef ALIGN_64BIT
      printf("\n Failed to make Socket Non-Blocking Server {[ConID]-[FD]} ={[%d]-[%d]} with reason =[%d]",
                servConId,egTLServerCb->sockFd,errno);
#else
      printf("\n Failed to make Socket Non-Blocking Server {[ConID]-[FD]} ={[%ld]-[%ld]} with reason =[%d]",
                servConId,egTLServerCb->sockFd,errno);
#endif

      /*Close the socket Descriptor as we failed to bind */
      (Void)close(egTLServerCb->sockFd);

      RETVALUE(RFAILED);
    }
#ifndef NTL_LIB
    ret = bind(egTLServerCb->sockFd, (struct sockaddr *)sockAddrPtr, sizeOfAddr);
#else
    /* Bind the socket with the Passed IP Address*/
    if (ntl_hLib < 0)
        ret = bind(egTLServerCb->sockFd, (struct sockaddr *)sockAddrPtr, sizeOfAddr);
    else
    {
        ret = ntl_bind(ntl_hLib, egTLServerCb->sockFd, (struct sockaddr *)sockAddrPtr, sizeOfAddr);
	    printf ("NTL:bind rc=%ld\n", ret);
		
	    ret = ntl_socket_ctrl(ntl_hLib, egTLServerCb->sockFd, KSD_SOCKET_CTRL_RX_ENABLED);
	    printf ("Enable rx for socket(0x%ld), res=%ld\n", egTLServerCb->sockFd, ret);
    }
#endif    
    if (SOCK_ERROR == ret)
    {
#ifdef ALIGN_64BIT
       printf("\n Bind failed for Server {[ConID]-[FD]} ={[%d]-[%d]} with reason =[%d]",
                  servConId,egTLServerCb->sockFd,errno);
#else
       printf("\n Bind failed for Server {[ConID]-[FD]} ={[%ld]-[%ld]} with reason =[%d]",
                  servConId,egTLServerCb->sockFd,errno);
#endif

       /*Close the socket Descriptor as we failed to bind */
       (Void)close(egTLServerCb->sockFd);

       RETVALUE(RFAILED);
    }


    cmMemcpy((U8 *) &egTLServerCb->serverAddress,(CONSTANT U8 *) servTAddr,sizeof(CmTptAddr));
    egTLServerCb->srvConId = servConId;

    if(EGTPU_PORT == servTAddr->u.ipv4TptAddr.port)
    {
        egTLServerCb->sockType = TH_SERVER;
        printf("\n Server Socket FD =[%lu]",egTLServerCb->sockFd);
    }
    else
    {
        egTLServerCb->sockType = TH_CLIENT;
    }


    cmMemcpy((U8 *) &cfmPst,(CONSTANT U8 *) pst,sizeof(Pst));
    cfmPst.dstEnt = pst->srcEnt;

    EgLiHitConCfm(&cfmPst,spId,servConId,servConId,servTAddr);
#ifdef S1SIMAPP
    egSchedTmr(&egTLCb, EG_TMR_EGT_RXTXDATA, TMR_START,1);
    
    gettimeofday(&tsStart1, NULL);
#endif
    RETVALUE(ROK);
}
/*purecov ccompilation error fix:ccpu00136421 */
#endif 

/*************************************************************************
 *      Fun:   egUPlatTunnTeidAdd
 *
 *      Desc:  This function adds the destination Channel ID if not already
 *             added. It adds the Channel ID to the mention destination.
 *
 *      Ret:
 *
 *      Note:
 *
 *      File:   eg_socklayer.c
***********************************************************************/
#ifdef ANSI
PUBLIC S16 egUPlatTunnTeidAdd
(
EgDestAddrCb *dstCb
)
#else
PUBLIC S16 egUPlatTunnTeidAdd(dstCb)
EgDestAddrCb *dstCb;
#endif

{
   RETVALUE(ROK);
}

/*************************************************************************
 *      Fun:   egUPlatTunnTeidDel
 *
 *      Desc:  This function deletes a Channel Id from the destination tabel
 *             If all the UE for that channel are been deleted.
 *
 *      Ret:   EGT_GTPU_CAUSE_INV_DST_IP : Destination IP not configured.
 *
 *      Note:
 *
 *      File:   eg_tunn.c
***********************************************************************/

#ifdef ANSI
PUBLIC S16 egUPlatTunnTeidDel
(
EgDestAddrCb *dstCb
)
#else
PUBLIC S16 egUPlatTunnTeidDel(dstCb)
EgDestAddrCb *dstCb;
#endif
{
   RETVALUE(ROK);
}

#ifdef LC_EGTP_THREAD
/** @details
 * This primitive is used by eGTP-U to send all the queued packet at thin Socket
 * layer. This function is periodically invoked per TTI and process all the packets,
 * and sends out on the Socket.
 *
 *
 * @return  ROK, RFAILED
 */

#ifdef ANSI
PUBLIC Void EgTLSendEgtpMsg(Bool param)
#else
PUBLIC Void EgTLSendEgtpMsg(Bool param)
#endif
{
    U32              i;
    S16 ret;
    CmInetFd       sockFd;
    CmInetAddr dstAddr;
    EgTLServerCb *egTLServerCb;
    U32              numPackets;
    U32              localFront;
    U32              maxNumPacketsToSend = MAX_QUEUE_LEN;


#if 0
    /*!< Update the socket FD to use uplink Nonm-ZBC Socket for sending out message */
#if (defined(TENB_T2K3K_SPECIFIC_CHANGES)) && (!defined(TENB_DISABLE_DL_ZBC))
    sockFd.fd = egTLUplnkSocket;
#endif
#endif

    sockFd.type = CM_INET_DGRAM;

    numPackets = 0;
    /* If the overload control is not enabled, then the complete queue will 
     * emptied as part of this send. Also, the param passed will not be 
     * unused in that case
     */
#ifdef ENB_CPU_OVERLOAD_CONTROL
    maxNumPacketsToSend = egGetNumPacketsToSend();

    /* Send the minimum number of packets if this function call is made due to
     * queue full.
     */
    if((param == TRUE) && (maxNumPacketsToSend < EG_MIN_PACKETS_TO_SEND))
    {
       maxNumPacketsToSend = EG_MIN_PACKETS_TO_SEND;
    }
#else
    UNUSED(param);
#endif /* ENB_CPU_OVERLOAD_CONTROL */

    for(i=0; i< MAX_SERVER_NUM; i++)
    {
       egTLServerCb = &egTLCb.servers[i];
       if((egTLServerCb->sockFd != SOCK_ERROR))
       {
          localFront = egTLServerCb->egtpPktFront;

          while((egTLQueueAddOne(egTLServerCb->egtpPktRear)) != localFront)
          {
             EgTLMsgQueue *msgQueue = &egTLServerCb->egtpMsgQueue[localFront];
#if (defined( NTL_LIB ) && defined( NTL_LIB_DIS_FOR_UL )) 
                sockFd.fd = egTLServerCb->sockFdUL;
#else
                sockFd.fd = egTLServerCb->sockFd;
#endif

                /*!< Init the Structures for sending message*/
#ifdef EG_IPV6_SUPPORTED
                if(msgQueue->dstAddr.type == CM_TPTADDR_IPV6)
                {
                   dstAddr.type = CM_TPTADDR_IPV6;
                   dstAddr.u.ipv6Addr.port = EGTPU_PORT;
                   CM_INET_COPY_IPV6ADDR(&dstAddr.u.ipv6Addr.ipv6NetAddr, 
                      msgQueue->dstAddr.u.ipv6TptAddr.ipv6NetAddr);
                }
                else
                {
                   dstAddr.type = CM_TPTADDR_IPV4;
                   dstAddr.u.ipv4Addr.port = EGTPU_PORT;
                   dstAddr.u.ipv4Addr.address = 
                      msgQueue->dstAddr.u.ipv4TptAddr.address;
               
                }
#else
                {
                   dstAddr.port = EGTPU_PORT;
                   dstAddr.address = msgQueue->dstAddr.u.ipv4TptAddr.address;
                }
#endif /* EG_IPV6_SUPPORTED */
             if(msgQueue->mBuf != NULL)
             {
                ret = egTLSendSockMsg(&sockFd,
                                  &dstAddr,
                                  &egTLCb.memInfo,
                                    msgQueue->mBuf,
                                   &msgQueue->msglen,
                                    msgQueue->tos);

                if(19 == ret)
                {
                    g_egtpSockDropsDueToReason19++;
                }
                else if(ROK != ret)
                {
                    printf("\n egTLSendSockMsg Failed : with Reason =[%d]",ret);
                }
                packetData.numOfPktsSent++;
                packetData.numBytesSent += msgQueue->msglen;

                /*Success or Failure: Free the Message queued.*/
                msgQueue->flag = FALSE;
                SPutMsg(msgQueue->mBuf);
                msgQueue->mBuf = NULLP;
             }
             else
             {
                printf("\n Mbuf is NULL before send itself  !!!!\n");
             }
             localFront = egTLQueueAddOne(localFront);
             egTLServerCb->egtpPktFront= localFront;
             numPackets++;
             if(numPackets >= maxNumPacketsToSend)
             {
                break;
             }
          }
          egTLCb.servers[i].qLen = 0;
       }
       if(numPackets >= maxNumPacketsToSend)
       {
          break;
        }
    }
}
#endif
/** @details
 * This primitive is used by eGTP-U to send all the queued packet at thin Socket
 * layer. This function is periodically invoked per TTI and process all the packets,
 * and sends out on the Socket.
 *
 *
 * @return  ROK, RFAILED
 */

#ifdef ANSI
PUBLIC Void EgTLSendMsg(Bool param)
#else
PUBLIC Void EgTLSendMsg(Bool param)
#endif
{
    U32              i;
    U32              j=0;
    S16 ret;
    CmInetFd       sockFd;
    CmInetAddr dstAddr;
    EgTLServerCb *egTLServerCb;
    U32              numPackets;
    U32              localFront;
    U32              maxNumPacketsToSend = MAX_QUEUE_LEN;


#if 0
    /*!< Update the socket FD to use uplink Nonm-ZBC Socket for sending out message */
#if (defined(TENB_T2K3K_SPECIFIC_CHANGES)) && (!defined(TENB_DISABLE_DL_ZBC))
    sockFd.fd = egTLUplnkSocket;
#endif
#endif

    sockFd.type = CM_INET_DGRAM;

    numPackets = 0;
    /* If the overload control is not enabled, then the complete queue will 
     * emptied as part of this send. Also, the param passed will not be 
     * unused in that case
     */
#ifdef ENB_CPU_OVERLOAD_CONTROL
    maxNumPacketsToSend = egGetNumPacketsToSend();

    /* Send the minimum number of packets if this function call is made due to
     * queue full.
     */
    if((param == TRUE) && (maxNumPacketsToSend < EG_MIN_PACKETS_TO_SEND))
    {
       maxNumPacketsToSend = EG_MIN_PACKETS_TO_SEND;
    }
#else
    UNUSED(param);
#endif /* ENB_CPU_OVERLOAD_CONTROL */

    for(i=0; i< MAX_SERVER_NUM; i++)
    {
       egTLServerCb = &egTLCb.servers[i];
       if((egTLServerCb->sockFd != SOCK_ERROR))
       {
          localFront = egTLServerCb->front;

          while((egTLQueueAddOne(egTLServerCb->rear)) != localFront)
          {
             EgTLMsgQueue *msgQueue = &egTLServerCb->msgQueue[localFront];
#if (defined( NTL_LIB ) && defined( NTL_LIB_DIS_FOR_UL )) 
                sockFd.fd = egTLServerCb->sockFdUL;
#else
                sockFd.fd = egTLServerCb->sockFd;
#endif

                /*!< Init the Structures for sending message*/
#ifdef EG_IPV6_SUPPORTED
                if(msgQueue->dstAddr.type == CM_TPTADDR_IPV6)
                {
                   dstAddr.type = CM_TPTADDR_IPV6;
                   dstAddr.u.ipv6Addr.port = EGTPU_PORT;
                   CM_INET_COPY_IPV6ADDR(&dstAddr.u.ipv6Addr.ipv6NetAddr, 
                      msgQueue->dstAddr.u.ipv6TptAddr.ipv6NetAddr);
                }
                else
                {
                   dstAddr.type = CM_TPTADDR_IPV4;
                   dstAddr.u.ipv4Addr.port = EGTPU_PORT;
                   dstAddr.u.ipv4Addr.address = msgQueue->dstAddr.u.ipv4TptAddr.address;
               
                }
#else
                {
                   dstAddr.port = EGTPU_PORT;
                   dstAddr.address = msgQueue->dstAddr.u.ipv4TptAddr.address;
                }
#endif /* EG_IPV6_SUPPORTED */
             if(msgQueue->mBuf != NULL)
             {
                ret = egTLSendSockMsg(&sockFd,
                                      &dstAddr,
                                      &egTLCb.memInfo,
                                       msgQueue->mBuf,
                                       &msgQueue->msglen,
                                       msgQueue->tos);

                if(19 == ret)
                {
                    g_egtpSockDropsDueToReason19++;
                }
                else if(ROK != ret)
                {
                    printf("\n egTLSendSockMsg Failed : with Reason =[%d]",ret);
                }
                packetData.numOfPktsSent++;
                packetData.numBytesSent += msgQueue->msglen;

                /*Success or Failure: Free the Message queued.*/
                msgQueue->flag = FALSE;
                egTLServerCb->latestFront = localFront;
                egTLServerCb->latestRear =  egTLServerCb->rear;

                SPutMsg(msgQueue->mBuf);
                msgQueue->mBuf = NULLP;
             }
             else
             {
                printf("\n Mbuf is NULL before send itself  !!!!\n");
             }
             localFront = egTLQueueAddOne(localFront);
             egTLServerCb->front = localFront;
             numPackets++;
             if(numPackets >= maxNumPacketsToSend)
             {
                break;
             }
          }
          egTLCb.servers[i].qLen = 0;
       }
       if(numPackets >= maxNumPacketsToSend)
       {
          break;
       }
    }
}


/** @details
 * This primitive is used by eGTP-U initialize Thin Socket Layer.
 *
 * @param [in]   region      -  Memory Region to be used by thin layer
 * @param [in]   pool        -  Memory Pool to be used by thin layer
 *
 * @return  ROK, RFAILED
 */

#ifdef ANSI
PUBLIC Void EgTLInitReq
(
Region region,      /* !< Memory Region to be used by thin layer */
Pool pool           /* !< Memory Pool to be used by thin layer */
)
#else
PUBLIC Void EgTLInitReq(region, pool)
Region region;     /* !< Memory Region to be used by thin layer */
Pool pool;         /* !< Memory Pool to be used by thin layer */
#endif
{
    U32 i;
#ifdef ENB_CPU_OVERLOAD_CONTROL
    FILE  *mipsFd;
#endif

    /*Initialize the basic parameter*/
    for (i=0; i< MAX_SERVER_NUM; i++)
    {
        egTLCb.servers[i].qLen = 0;
        egTLCb.servers[i].sockFd = -1;
        egTLCb.servers[i].srvConId = -1;
        egTLCb.servers[i].front = 0;
        egTLCb.servers[i].rear = MAX_QUEUE_LEN - 1;
#if 1
        egTLCb.servers[i].egtpPktFront = 0;
        egTLCb.servers[i].egtpPktRear = MAX_QUEUE_LEN - 1;
#endif
    }

    /*Initialize the Generic Post structure*/
    /* egTLCb.egPst.dstProcId = egCb.init.procId; */
    egTLCb.egPst.dstProcId = 100;
    egTLCb.egPst.srcProcId = egCb.init.procId;
    egTLCb.egPst.srcEnt = ENTHI;
    egTLCb.egPst.dstEnt = ENTEG;
    egTLCb.egPst.dstInst = egCb.init.inst;
    egTLCb.egPst.srcInst = egCb.init.inst;
    egTLCb.egPst.prior = PRIOR0;
    egTLCb.egPst.route = RTESPEC;
    egTLCb.egPst.region = region;
    egTLCb.egPst.pool = pool;
    egTLCb.egPst.selector = 0; /* Default Loose coupling */


    /* egTLCb.memInfo.pool   = pool; */
    egTLCb.memInfo.pool   = 3;
    egTLCb.memInfo.region = region;
#ifdef S1SIMAPP
    egCmInitTimer (&egTLCb.egtTxRxTmrNode);
#endif
#ifdef ENB_CPU_OVERLOAD_CONTROL
    egTLCb.dlPktCntrl.maxNumPacketsToRead = 
             (EG_MAX_PACKETS_TO_READ_WINDOW - EG_MIN_PACKETS_TO_READ_WINDOW);
    egTLCb.dlPktCntrl.dlTimeWindow = EG_DL_PACKET_WINDOW_SIZE;

    egTLCb.ulPktCntrl.maxNumPacketsToSend = EG_MAX_PACKETS_TO_SEND_WINDOW;
    egTLCb.ulPktCntrl.ulTimeWindow = EG_UL_PACKET_WINDOW_SIZE;
/*    egTLCb.maxMsgToread   = MAX_MSG_TO_READ_PER_FRAME; */

    mipsFd = fopen(MIPS_FILE, "r");

    if(NULLP != mipsFd)
    {
       egTLCb.isCpuBasedContrl = TRUE;
       fclose(mipsFd);
    }
    else
    {
       egTLCb.isCpuBasedContrl = FALSE;
    }
#endif /* ENB_CPU_OVERLOAD_CONTROL */
}


/** @details
 * This primitive is used by eGTP-U to indicate reception of Data from Thin Socket Layer.
 * Every TTI, we get an indication to process the messages from socket.
 *
 * @param [in]   timeOut         -  Time in milliseconds to wait for ePoll event to happen.
 * @param [in]   maxEvent        -  Max events to capture from ePOll
 *
 * @return  ROK, RFAILED
 */
#ifdef ANSI
PUBLIC U32 EgTLReadMsg
(
U32 timeOut,               /* !< Time in milliseconds to wait for ePoll event to happen. */
U32 maxEvent               /* !< Max events to capture from ePOll. */
)
#else
PUBLIC U32 EgTLReadMsg(timeOut, maxEvent)
U32 timeOut;               /* !< Time in milliseconds to wait for ePoll event to happen. */
U32 maxEvent;              /* !< Max events to capture from ePOll. */
#endif
{

   U32                j;
   register U32       i;
   Buffer             *mbuf;
   CmIpHdrParm        ipHdrParm;
   EgTLServerCb       *egTLServerCb;

#ifdef TENB_DISABLE_DL_ZBC
   CmInetFd           fd;
   fd.type = CM_INET_DGRAM;
   CmTptAddr         remAddr;
#else
   CmTptAddr          remAddr;
   remAddr.type = CM_INET_IPV4ADDR_TYPE;
#endif
   U32  numPackets = MAX_MSG_READ_PER_TTI;

#ifdef ENB_CPU_OVERLOAD_CONTROL
   numPackets = egGetNumPacketsToRead();
#endif /* ENB_CPU_OVERLOAD_CONTROL */

   /*Steps for Reading Message
     1. For Each Socket Descriptor indicated by Epoll - Do Following
     1.1: Find a configured server
     1.1.1: If Server is Found
     1.1.1.1 : Read message from the socket
     1.1.1.2 : Indicate the Message to the Egtp Layer using tightly/loosely coupled API
     1.1.2: If sever is not found.
     1.1.2.1 :Indicate to User [Currently only Print]
     1.2: Iterate by 1.1.1 until all the server's are processed
    */
   for(i=0; i< MAX_SERVER_NUM; i++)
   {
      egTLServerCb = &egTLCb.servers[i];

      if(egTLServerCb->sockFd == 0xFFFFFFFF)
           continue;

      /*Read the Max Defined Data for the each Server*/
      for(j = 0; j < numPackets; j++)
      {
#if (defined(TENB_T2K3K_SPECIFIC_CHANGES)) && (!defined(TENB_DISABLE_DL_ZBC))
         if(ROK == egTLRecvZbcUdpMsg(egTLServerCb->sockFd, &remAddr, egTLCb.memInfo, &mbuf))
#else
#ifdef TENB_DISABLE_DL_ZBC  
         fd.fd = egTLServerCb->sockFd;
#endif         
/* purecov compilation error fix:ccpu00136421 */
/*       if(ROK == cmInetRecvMsg(&fd, &remAddr,&egTLCb.memInfo,&mbuf,&len,0)) */
         if(ROK == egTLRecvMsgFromSocket(egTLServerCb->sockFd, &remAddr, egTLCb.memInfo, &mbuf))
#endif
         {
            /*Send Buffer to application*/
#ifdef REVIEW
            EgLiHitUDatInd(&egTLCb.egPst,egTLServerCb->srvConId,egTLServerCb->srvConId,
                  &remAddr,&egTLServerCb->serverAddress,&ipHdrParm,mbuf);
#else

            cmPkHitUDatInd(&egTLCb.egPst,egTLServerCb->srvConId,egTLServerCb->srvConId,
                  &remAddr,&egTLServerCb->serverAddress,&ipHdrParm,mbuf);
#endif
         }
         else
         {
            /* printf("\n No more data to read from the socket."); */
            break;
         }
      }
   }

   RETVALUE(ROK);
}


#ifdef FLAT_BUFFER_OPT
/** @details
 * This primitive is used by eGTP-U to indicate reception of Data from Thin Socket Layer.
 * Every TTI, we get an indication to process the messages from socket.
 *
 * @param [in]   timeOut         -  Time in milliseconds to wait for ePoll event to happen.
 * @param [in]   maxEvent        -  Max events to capture from ePOll
 *
 * @return  ROK, RFAILED
 */
#ifdef ANSI
PUBLIC U32 EgTLReadMsgFB
(
U32 timeOut,               /* !< Time in milliseconds to wait for ePoll event to happen. */
U32 maxEvent               /* !< Max events to capture from ePOll. */
)
#else
PUBLIC U32 EgTLReadMsgFB(timeOut, maxEvent)
U32 timeOut;               /* !< Time in milliseconds to wait for ePoll event to happen. */
U32 maxEvent;              /* !< Max events to capture from ePOll. */
#endif
{

   U32                j;
   register U32       i;
   U8                 *buf;
   EgTLServerCb       *egTLServerCb;

#ifdef TENB_DISABLE_DL_ZBC
   MsgLen             len = CM_INET_READ_ANY;
   CmInetFd           fd;
   fd.type = CM_INET_DGRAM;
   CmInetAddr         remAddr;
#else
   CmTptAddr          remAddr;
   remAddr.type = CM_INET_IPV4ADDR_TYPE;
#endif
   U32  numPackets = MAX_MSG_READ_PER_TTI;

#ifdef ENB_CPU_OVERLOAD_CONTROL
   numPackets = egGetNumPacketsToRead();
#endif /* ENB_CPU_OVERLOAD_CONTROL */

   /*Steps for Reading Message
     1. For Each Socket Descriptor indicated by Epoll - Do Following
     1.1: Find a configured server
     1.1.1: If Server is Found
     1.1.1.1 : Read message from the socket
     1.1.1.2 : Indicate the Message to the Egtp Layer using tightly/loosly coupled API
     1.1.2: If sever is not found.
     1.1.2.1 :Indicate to User [Currently only Print]
     1.2: Iterate by 1.1.1 until all the server's are processed
    */
   for(i=0; i< MAX_SERVER_NUM; i++)
   {
      egTLServerCb = &egTLCb.servers[i];

      if(egTLServerCb->sockFd == 0xFFFFFFFF)
           continue;

      /*Read the Max Defined Data for the each Server*/
      for(j = 0; j < numPackets; j++)
      {
         U32 bufLen = 0;
#if (defined(TENB_T2K3K_SPECIFIC_CHANGES)) && (!defined(TENB_DISABLE_DL_ZBC))
         if(ROK == egTLRecvZbcUdpMsgFB(egTLServerCb->sockFd, &remAddr,&buf, &bufLen))
#else
         if(ROK == egTLRecvMsgFromSocketFB(egTLServerCb->sockFd, &remAddr, buf, &bufLen))
#endif
         {
              egTLHndlRecv(egTLServerCb,buf, bufLen, &remAddr); 
         }
         else
         {
            /* printf("\n No more data to read from the socket."); */
            break;
         }
      }
   }

   RETVALUE(ROK);
}
#endif


/** @details
 * This primitive is used by eGTP-U to de-init thin Socket Layer.s
 *
 * @return  ROK, RFAILED
 */
#ifdef ANSI
PUBLIC Void EgTLThShutdownReq(Void)
#else
PUBLIC Void EgTLThShutdownReq(Void)
#endif
{
    U32 i;
#ifdef NTL_LIB
    if(ntl_hLib !=-1)
    {
      printf ("NTL Lib detach\n");
      ntl_close(ntl_hLib, 0);
      ntl_hLib = -1;
    }
#endif 
    for (i=0; i < MAX_SERVER_NUM; i++)
    {
        if( SOCK_ERROR != egTLCb.servers[i].sockFd)
            close(egTLCb.servers[i].sockFd);
    }
}

/** @details
 * This primitive is used by eGTP-U to queue a packet for transmission at thin layer.
 * mBuf passed by the callee is stored in queue for transmission at next transmit indication.
 *
 * @param [in]   spConId     -  Server Connection Id
 * @param [in]   remAddr     -  Server Address
 * @param [in]   srcAddr     -  Transport Parameters
 * @param [in]   hdrParm     -  UDP header Parameters.
 * @param [in]   mBuf        -  Message to be sent out.
 *
 * @return  ROK, RFAILED
 */
#ifndef DHI
#ifdef ANSI
PUBLIC U32 EgTLDatReq
(
UConnId     spConId,       /* service providers connection Id */
CmTptAddr   *remAddr,      /* remote address */
CmTptAddr   *srcAddr,      /* source address */
CmIpHdrParm *hdrParm,      /* header parameters */
Buffer      *mBuf          /* message buffer */
)
#else
PUBLIC U32 EgTLDatReq(spConId, remAddr, srcAddr, hdrParm, mBuf)
UConnId     spConId,       /* service providers connection Id */
CmTptAddr   *remAddr,      /* remote address */
CmTptAddr   *srcAddr,      /* source address */
CmIpHdrParm *hdrParm,      /* header parameters */
Buffer      *mBuf          /* message buffer */
#endif
{
   EgTLServerCb *egTLServerCb = &egTLCb.servers[spConId];;
   EgTLMsgQueue *msgQueue;
   U32           tmpRear;
   U32           locFront;
   MsgLen        msgLen;

#ifdef ERRCHK
   if((NULLP == remAddr)
         ||(NULLP == srcAddr)
         ||(NULLP == mBuf))
   {
      printf("\n Incorrect Parameter Passed");
      RETVALUE(RFAILED);
   }

   if(cmMemcmp((CONSTANT U8 *) &egTLServerCb->serverAddress,(CONSTANT U8 *) srcAddr,sizeof(CmTptAddr)))
   {
      printf("\n Source Address MisMatch");
      RETVALUE(RFAILED);
   }
#endif


#ifndef LC_EGTP_THREAD  
   tmpRear = egTLQueueAddOne(egTLServerCb->rear);
   locFront = egTLServerCb->front;
#else
   tmpRear = egTLQueueAddOne(egTLServerCb->egtpPktRear);
   locFront = egTLServerCb->egtpPktFront;
#endif
   if(egTLQueueAddOne(egTLQueueAddOne(tmpRear)) == locFront)
   {
      /* Dropping Packets */
      SPutMsg(mBuf);
      RETVALUE(ROK);
      /* EgTLSendMsg(TRUE); */
   }
   
#ifndef LC_EGTP_THREAD
   msgQueue =  &egTLServerCb->msgQueue[tmpRear],
#else
   msgQueue =  &egTLServerCb->egtpMsgQueue[tmpRear],
#endif

   cmMemcpy((U8 *) &msgQueue->dstAddr,(CONSTANT U8 *)remAddr, sizeof(CmTptAddr));
   msgQueue->mBuf = mBuf;
   SFndLenMsg(mBuf, &msgLen);
   msgQueue->msglen = msgLen;
   msgQueue->flag   = TRUE;

#ifdef IPV6_OPTS_SUPPORTED
   cmMemcpy((U8 *)&msgQueue->ipHdrParams, (CONSTANT U8 *)hdrParm,
                                                  sizeof(CmIpHdrParm));
#endif
#ifndef LC_EGTP_THREAD
   egTLServerCb->rear = tmpRear;
   egTLServerCb->qLen++;
#else
   egTLServerCb->egtpPktRear  = tmpRear;
   egTLServerCb->egtpPktQLen++;
#endif

   RETVALUE(ROK);

}
#endif 

/** @details
 * This primitive is used by eGTP-U to open server for Tx/Rx of Data
 *
 * @param [in]   pst         -  Post Structure
 * @param [in]   suId        -  Service user SAP ID
 * @param [in]   spId        -  Service provider SAP ID
 *
 * @return  ROK, RFAILED
 * Note: This function would be removed once egTSapCtrl function is updated.
 */

#ifdef ANSI
PUBLIC U32 EgTLBndReq
(
Pst  *pst,                /* post structure */
SuId suId,                /* service user SAP ID */
SpId spId                 /* service provider SAP ID */
)
#else
PUBLIC U32 EgTLBndReq(pst, suId, spId)
Pst  *pst;                /* post structure */
SuId suId;                /* service user SAP ID */
SpId spId;                /* service provider SAP ID */
#endif
{
    Pst cfmPst;

#ifdef ERRCHK
    if(NULLP == pst)
    {
        printf("\n Incorrect Parameter Passed");
        RETVALUE(RFAILED);
    }
#endif

    /* copy bind configuration parameters */
    cfmPst.dstProcId = pst->srcProcId;
    cfmPst.dstEnt    = pst->srcEnt;
    cfmPst.dstInst   = pst->srcInst;
    cfmPst.srcProcId = pst->dstProcId;
    cfmPst.srcInst   = pst->dstInst;

    EgLiHitBndCfm(&cfmPst, suId, CM_BND_OK);
    RETVALUE(ROK);
}


/** @details
 * This primitive is used by eGTP-U to unbind with eg_socklayer.
 *
 * @param [in]   pst         -  Post Structure
 * @param [in]   spId        -  Service Provider Id
 * @param [in]   reason      -  Reason for unbind Req
 *
 * @return  ROK, RFAILED
 */

#ifdef ANSI
PUBLIC U32 EgTLUbndReq
(
Pst    *pst,              /* post structure */
SpId   spId,              /* service provider SAP ID */
Reason reason             /* reason */
)
#else
PUBLIC U32 EgTLUbndReq(pst, spId, reason)
Pst    *pst;              /* post structure */
SpId   spId;              /* service provider SAP ID */
Reason reason;             /* reason */
#endif
{
    RETVALUE(ROK);
}

#ifndef DHI
/** @details
 * This primitive is used by eGTP-U to disconnect an Open server.
 *
 * @param [in]   pst         -  Post Structure
 * @param [in]   spId        -  Service Provider Id
 * @param [in]   choice      -  Type of Action to be performed.
 * @param [in]   conId       -  Server Connection Id
 * @param [in]   action      -  Action to be performed.
 * @param [in]   tPar        -  Transport Parameters
 *
 * @return  ROK, RFAILED
 */

#ifdef ANSI
PUBLIC U32 EgTLDiscServerReq
(
UConnId     conId         /* connection Id */
)
#else
PUBLIC U32 EgTLDiscServerReq(conId)
UConnId     conId;         /* connection Id */
#endif
{
    U32 ret = ROK;

    if(egTLCb.servers[conId].sockFd != SOCK_ERROR )
    {
        /*Close the Socket*/
        /*De-register the SockFd from the ePoll*/
        ret = egTLCloseServerReq(conId);
        if(ROK != ret)
        {
            printf("\n Failed to Close Socket");
            RETVALUE(RFAILED);
        }
    }

    RETVALUE(ROK);
}
#endif 

#ifndef DHI
/** @details
 * This primitive is used by Thin Layer to close any existing open socket.
 *
 * @param [in]   connId  -  Connection Id of the socket to be closed.
 *
 * @return  ROK, RFAILED
 */
#ifdef ANSI
PRIVATE U32 egTLCloseServerReq
(
U32 connId             /* !< Connection Id of the socket to be closed. */
)
#else
PRIVATE U32 egTLCloseServerReq(connId)
U32 connId;           /* !< Connection Id of the socket to be closed. */
#endif
{
   U32 ret=ROK; /* kwork fix */
#ifdef NTL_LIB
	ntl_socket_ctrl(ntl_hLib, egTLCb.servers[connId].sockFd, KSD_SOCKET_CTRL_RX_DISABLED);
   printf("Closing NTL socket egTLCb.servers[connId].sockFd %lu  \n",egTLCb.servers[connId].sockFd);  
   if ( SOCK_ERROR == ntl_socket_close (ntl_hLib, egTLCb.servers[connId].sockFd))
   {
#ifdef ALIGN_64BIT
      printf("\n Unable to Close the Socket FD =[%d] for ServerId=[%d] with Error=[%d]",
            egTLCb.servers[connId].sockFd,
            connId,
            errno);
#else
      printf("\n Unable to Close the Socket FD =[%ld] for ServerId=[%ld] with Error=[%d]",
            egTLCb.servers[connId].sockFd,
            connId,
            errno);
#endif
      ret = RFAILED;
   }
#ifdef NTL_LIB_DIS_FOR_UL    
   printf("Closing Normal UL socket egTLCb.servers[connId].sockFd %lu  \n",egTLCb.servers[connId].sockFdUL);  
   if(egTLCb.servers[connId].sockFdUL)
   {  
      if(SOCK_ERROR == close(egTLCb.servers[connId].sockFdUL))
      {
#ifdef ALIGN_64BIT
         printf("\n Unable to Close the Socket FD =[%d] for ServerId=[%d] with Error=[%d]",
               egTLCb.servers[connId].sockFd,
               connId,
               errno);
#else
         printf("\n Unable to Close the Socket FD =[%ld] for ServerId=[%ld] with Error=[%d]",
               egTLCb.servers[connId].sockFd,
               connId,
               errno);
#endif
         ret = RFAILED;
      }
      egTLCb.servers[connId].sockFdUL =0;
   }
#endif /* NTL_LIB_DIS_FOR_UL */
#else 
    if(SOCK_ERROR == close(egTLCb.servers[connId].sockFd))
    {
#ifdef ALIGN_64BIT
        printf("\n Unable to Close the Socket FD =[%d] for ServerId=[%d] with Error=[%d]",
               egTLCb.servers[connId].sockFd,
               connId,
               errno);
#else
        printf("\n Unable to Close the Socket FD =[%ld] for ServerId=[%ld] with Error=[%d]",
               egTLCb.servers[connId].sockFd,
               connId,
               errno);

#endif
        ret = RFAILED;
    }
#endif /* NTL_LIB */ 
    RETVALUE(ret);
}

#endif 
/*
 *
 *      Fun:   egTLSendSockMsg
 *
 *      Desc:  Sends the message data hold by mBuf. 
 *             The len paramter gives the actual written octets. If the socket
 *             is non-blocking this value can be differ from the mBuf length 
 *             because there was not enough transmit buffer space available. If 
 *             this occurs, RWOULDBLOCK is returned and only a part of the mBuf
 *             is sent.
 *             Values for flag parameter:
 *  
 *
 *      Ret:   ROK         - successful
 *             RWOULDBLOCK - no or not entire mBuf sent because would block
 *             ROUTRES     - failed, out of resources
 *             RCLOSED     - connection was closed by the peer
 *             RFAILED     - failed
 *                           
 *      Notes: The successful completion of a send call does not indicate that 
 *             the data has been successfully delivered! 
 *
 *             This function does not free any sent buffers.  
 *
 *   
 *      File:  eg_scoklayer.c
 *
 */

#ifdef ANSI
PUBLIC S16 egTLSendSockMsg
(
 CmInetFd       *sockFd,         /* socket file descriptor */
 CmInetAddr     *dstAddr,        /* destination Internet address/port */
 CmInetMemInfo  *info,           /* buffer allocation info */
 Buffer         *mBuf,           /* buffer structure to send */
 MsgLen         *len,            /* number of actually sent octets */
 U8              tos
 )
#else
PUBLIC S16 egTLSendSockMsg(sockFd, dstAddr, info, mBuf, len,tos)
   CmInetFd       *sockFd;         /* socket file descriptor */
   CmInetAddr     *dstAddr;        /* destination Internet address/port */
   CmInetMemInfo  *info;           /* buffer allocation info */
   Buffer         *mBuf;           /* buffer structure to send */
   MsgLen         *len;            /* number of actually sent octets */
   U8              tos;
#endif /* ANSI */
{
   S32 ret;                     /* temporary return value */
   S32 retVal;                  /* temporary return value */
   S16 i;                       /* loop index */
   CmInetIovec  txArr[CM_INET_MAX_DBUF]; /* scatter vector */
   S16      numDBufs;           /* number of dBufs in message */
   struct   msghdr msg;         /* sendmsg() message header */
   MsgLen   msgLen;             /* message length */ 
   U32      strtEndDBufNum;     /* starting/ending DBuf number */ 
   MsgLen   unSentLen;          /* sent len */
   Bool     sentMsg;            /* flag to indicate the entire message is
                                 * sent */

   struct  sockaddr_in remAddr; /* remote Internet address */   
#ifdef IPV6_SUPPORTED
   struct   sockaddr_in6  remAddr6; /* remote Internet address */   
#endif /* IPV6_SUPPORTED */
   CmInetSockAddr *sockAddrPtr;
   U32            sizeOfAddr;    
#ifndef LTE_ENB_PAL
   EgMsgData aux;
#endif
   MsgLen         ioLen; 

   TRC2(egTLSendSockMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
      /* error check on parameters */
      if ((sockFd == NULLP) || CM_INET_INV_SOCK_FD(sockFd) ||
            (info == NULLP) || (len == NULLP))
      {
         RETVALUE(RFAILED);
      }
#endif /* ERRCLASS & ERRCLS_INT_PAR */

   msgLen = 0;  
   sockAddrPtr = NULLP;
   sizeOfAddr = 0;

   /* setup remote address */
   if (dstAddr != NULLP)
   {
#ifdef IPV6_SUPPORTED
      if (dstAddr->type == CM_INET_IPV6ADDR_TYPE)
      {
         cmMemset((U8*)&remAddr6, 0, sizeof(remAddr6));
         remAddr6.sin6_family = AF_INET6;
         remAddr6.sin6_port   = CM_INET_HTON_U16(dstAddr->u.ipv6Addr.port);
         CM_INET_COPY_IPV6ADDR(&remAddr6.sin6_addr, 
               &dstAddr->u.ipv6Addr.ipv6NetAddr); 
         sizeOfAddr = sizeof(remAddr6);
         sockAddrPtr = (CmInetSockAddr *)&remAddr6;
      }
      else
      {
         cmMemset((U8*)&remAddr, 0, sizeof(remAddr));
         remAddr.sin_family = AF_INET;
         remAddr.sin_port   = CM_INET_HTON_U16(dstAddr->u.ipv4Addr.port);
         remAddr.sin_addr.s_addr = 
            CM_INET_HTON_U32(dstAddr->u.ipv4Addr.address);
         sizeOfAddr = sizeof(remAddr);
         sockAddrPtr = (CmInetSockAddr *)&remAddr;
      }
#else
      /*      cmMemset((U8*)&remAddr, 0, sizeof(remAddr)); */
      remAddr.sin_family      = AF_INET;
      remAddr.sin_port        = CM_INET_HTON_U16(dstAddr->port);
      remAddr.sin_addr.s_addr = CM_INET_HTON_U32(dstAddr->address);
      sizeOfAddr = sizeof(remAddr);
      sockAddrPtr = (CmInetSockAddr *)&remAddr;
#endif /* IPV6_SUPPORTED */
   }

   ret = SFndLenMsg(mBuf, &msgLen);
   if (ret != ROK)
   {
      RETVALUE(RFAILED);
   }

   msg.msg_flags = 0;
   if (dstAddr != NULLP)
   {
      msg.msg_name    = (caddr_t)sockAddrPtr;
      msg.msg_namelen = sizeOfAddr;
   }
   else
   {
      msg.msg_name    = NULLP;         
      msg.msg_namelen = 0;
   }

   msg.msg_control    = NULLP;
   msg.msg_controllen  = 0;

   /* allocate scatter vector */
   numDBufs = CM_INET_MAX_DBUF;
   retVal = RNA;
   ret = ROK;
   unSentLen = msgLen;
   strtEndDBufNum = 0;
   *len = 0;
   sentMsg = FALSE;


   do
   {
      /* build the send vector */ 
      /* cm_inet_c_001.main_50 - Partial send handling. Added variable to hold
         total length of the packed dbufs */
      retVal = egTLBuildSendIovec(mBuf, unSentLen, txArr, numDBufs, &i, 
            &strtEndDBufNum, &ioLen);
      if (retVal != ROK)
      {
         if (retVal == RNA)
         {
            /* Incase of UDP/RAW messages call SCompressMsg. */
            if (sockFd->type != CM_INET_STREAM)
            {
               /* Compress the message into a single dBuf */
               ret = SCompressMsg(mBuf);
               if (ret != ROK)
                  RETVALUE(RFAILED);

               strtEndDBufNum = 0;
               /* Rebuild the send vector */
               /* cm_inet_c_001.main_50 - Partial send handling. Added variable to hold
                  total length of the packed dbuf */
               ret = egTLBuildSendIovec(mBuf, unSentLen, txArr, numDBufs, &i,
                     &strtEndDBufNum, &ioLen);
               if (ret != ROK)
                  RETVALUE(RFAILED);

               retVal = ROK;
            }
         }
         else
            RETVALUE(RFAILED);
      }
   msg.msg_iov           = txArr;
   msg.msg_iovlen        = i;

#ifndef LTE_ENB_PAL
   aux.hdr.cmsg_len = sizeof(EgMsgData);
   aux.hdr.cmsg_level = SOL_IP;
   aux.hdr.cmsg_type = IP_TOS;
   aux.data = tos;

   msg.msg_control = &aux;
   msg.msg_controllen = sizeof (aux);
#endif
#if (defined( NTL_LIB ) && (!defined( NTL_LIB_DIS_FOR_UL ))) 
   ret = ntl_sendmsg(ntl_hLib, sockFd->fd, &msg, 0);
#else 
   ret = sendmsg(sockFd->fd, &msg, 0);
#endif 

        if (-1 == ret)
        {
            if((errno == EAGAIN) ||
                    (errno == EWOULDBLOCK))
            {
                /* cm_inet_c_001.main_50 - Return without making length 0, if in case the partial
                   message was sent earlier */
                RETVALUE(EWOULDBLOCK);
            }

            printf("thUtlSendMsg() Failed : error(%d),"
                   " sockFd->fd(%ld)\n", errno, sockFd->fd);

            /* check if network is reacheble or not */
            if ((errno == ENETUNREACH))
            {
                RETVALUE(RFAILED);
            }

            /*  Check if connection was closed by the peer */
            if ((errno == EPIPE) ||
                    (errno == ECONNREFUSED) ||
                    (errno == ECONNABORTED))
            {
                *len = 0;
                RETVALUE(RCLOSED);
            }
            RETVALUE(RFAILED);
        }

        /* cm_inet_c_001.main_50 - Update the length only in successful cases */
        *len += ret;

        /* cm_inet_c_001.main_50 - if what is actually sent is less than what is attemped
         * to be sent, then return WOULDBLOCK
         */
        if (ret < ioLen)
            RETVALUE(RWOULDBLOCK);

        unSentLen -= ret;

    } while (*len < msgLen);
   RETVALUE(ROK);

} /* end of egTLSendSockMsg */
#if 0
/** @details
 * This primitive is used by Thin Layer to send data on a socket.s
 *
 * @param [in]   sockFd       -  Socket Fd on which data needs to be sent
 * @param [in]   dstAddr      -  Destination IP Address
 * @param [in]   info         -  Memory Info
 * @param [in]   mBuf         -  Buffer to be sent out
 * @param [out]   len         -  Number of actually sent octets
 * @param [in]   ipHdrParams  -  IPv6 extensions headers
 * @param [in]   flags        -  Additional control flags, unused
 *
 * @return  ROK, RFAILED
 */

#ifdef ANSI
PRIVATE S16 egTLSendSockMsg
(
    CmInetFd       *sockFd,         /* socket file descriptor */
    CmInetAddr     *dstAddr,        /* destination Internet address/port */
    CmInetMemInfo  *info,           /* buffer allocation info */
    Buffer         *mBuf,           /* buffer structure to send */
    MsgLen         *len,            /* number of actually sent octets */
    /* added for IPv6 ext hdr */
#ifdef IPV6_OPTS_SUPPORTED
    CmInetIpHdrParm *ipHdrParams,   /* IPv6 extensions headers */
#endif /* IPV6_OPTS_SUPPORTED */
    S16             flags           /* additional control flags, unused */
)
#else
/* added for IPv6 ext hdr */
#ifdef IPV6_OPTS_SUPPORTED
PRIVATE S16 egTLSendSockMsg(sockFd, dstAddr, info, mBuf, len, ipHdrParams, flags)
CmInetFd       *sockFd;         /* socket file descriptor */
CmInetAddr     *dstAddr;        /* destination Internet address/port */
CmInetMemInfo  *info;           /* buffer allocation info */
Buffer         *mBuf;           /* buffer structure to send */
MsgLen         *len;            /* number of actually sent octets */
CmInetIpHdrParm *ipHdrParams;   /* IPv6 extensions headers */
S16             flags;          /* additional control flags, unused */
#else
PRIVATE S16 egTLSendSockMsg(sockFd, dstAddr, info, mBuf, len, flags)
CmInetFd       *sockFd;         /* socket file descriptor */
CmInetAddr     *dstAddr;        /* destination Internet address/port */
CmInetMemInfo  *info;           /* buffer allocation info */
Buffer         *mBuf;           /* buffer structure to send */
MsgLen         *len;            /* number of actually sent octets */
S16             flags;          /* additional control flags, unused */
#endif /* IPV6_OPTS_SUPPORTED */
#endif /* ANSI */
{
    S32 ret;                     /* temporary return value */
    S32 retVal;                  /* temporary return value */
    S16 i;                       /* loop index */
    CmInetIovec  txArr[CM_INET_MAX_DBUF]; /* scatter vector */
    S16      numDBufs;           /* number of dBufs in message */
    struct   msghdr msg;         /* sendmsg() message header */
    MsgLen   msgLen = 0;             /* message length */
    U32      strtEndDBufNum;     /* starting/ending DBuf number */
    MsgLen   unSentLen;          /* sent len */
    Bool     sentMsg;            /* flag to indicate the entire message is
                                 * sent */
    struct  sockaddr_in remAddr; /* remote Internet address */
    CmInetSockAddr *sockAddrPtr = NULLP;
    U32            sizeOfAddr = 0;
    MsgLen         ioLen;

#ifdef IPV6_SUPPORTED
    /* added for IPv6 ext hdr */
    struct   sockaddr_in6  remAddr6; /* remote Internet address */
#ifdef IPV6_OPTS_SUPPORTED
    U32    curMsgIdx = 0;            /* indx in cmsgData where to write an ext hdr */
#endif /* IPV6_OPTS_SUPPORTED */
    /* alloc from stack for IPv6 ancill data */
    U8     cmsgData[CM_INET_IPV6_ANCIL_DATA];
#else
    /* alloc from stack for IPv4 ancill data */
    U8     cmsgData[CM_INET_IPV4_ANCIL_DATA];
#endif /* IPV6_SUPPORTED */

    TRC2(egTLSendSockMsg)

    UNUSED(flags);

#if (ERRCLASS & ERRCLS_INT_PAR)
    /* error check on parameters */
    if ((sockFd == NULLP) || CM_INET_INV_SOCK_FD(sockFd) ||
            (info == NULLP) || (len == NULLP))
    {
        RETVALUE(RFAILED);
    }
#endif /* ERRCLASS & ERRCLS_INT_PAR */

    cmMemset((U8*)cmsgData, 0, sizeof(cmsgData));

    /* setup remote address */
    if (dstAddr != NULLP)
    {
#ifdef IPV6_SUPPORTED
        if (dstAddr->type == CM_INET_IPV6ADDR_TYPE)
        {
            cmMemset((U8*)&remAddr6, 0, sizeof(remAddr6));
            remAddr6.sin6_family = AF_INET6;
            remAddr6.sin6_port   = CM_INET_HTON_U16(dstAddr->u.ipv6Addr.port);
            CM_INET_COPY_IPV6ADDR(&remAddr6.sin6_addr,
                                  &dstAddr->u.ipv6Addr.ipv6NetAddr);
            sizeOfAddr = sizeof(remAddr6);
            sockAddrPtr = (CmInetSockAddr *)&remAddr6;
        }
        else
        {
            cmMemset((U8*)&remAddr, 0, sizeof(remAddr));
            remAddr.sin_family = AF_INET;
            remAddr.sin_port   = CM_INET_HTON_U16(dstAddr->u.ipv4Addr.port);
            remAddr.sin_addr.s_addr =
                CM_INET_HTON_U32(dstAddr->u.ipv4Addr.address);
            sizeOfAddr = sizeof(remAddr);
            sockAddrPtr = (CmInetSockAddr *)&remAddr;
        }
#else
        cmMemset((U8*)&remAddr, 0, sizeof(remAddr));
        remAddr.sin_family      = AF_INET;
        remAddr.sin_port        = CM_INET_HTON_U16(dstAddr->port);
        remAddr.sin_addr.s_addr = CM_INET_HTON_U32(dstAddr->address);
        sizeOfAddr = sizeof(remAddr);
        sockAddrPtr = (CmInetSockAddr *)&remAddr;
#endif /* IPV6_SUPPORTED */
    }


    ret = SFndLenMsg(mBuf, &msgLen);
    if (ret != ROK)
    {
        RETVALUE(RFAILED);
    }

    /* added */
    cmMemset((U8*)&msg, 0, sizeof(msg));

    if (dstAddr != NULLP)
    {
        msg.msg_name    = (Void*)sockAddrPtr;
        msg.msg_namelen = sizeOfAddr;
    }
    else
    {
        msg.msg_name    = NULLP;
        msg.msg_namelen = 0;
    }

    msg.msg_control    = NULLP;
    msg.msg_controllen  = 0;

    /* allocate scatter vector */
    numDBufs = CM_INET_MAX_DBUF;
    retVal = RNA;
    ret = ROK;
    unSentLen = msgLen;
    strtEndDBufNum = 0;
    *len = 0;
    sentMsg = FALSE;

    /* if the sender wants to send Ipv6 exten. headers */
#ifdef IPV6_OPTS_SUPPORTED
    if (ipHdrParams != NULLP && (ipHdrParams->type == CM_INET_IPV6ADDR_TYPE))
    {
        if(ipHdrParams->u.ipv6HdrParm.ttl.pres == TRUE)
        {
            cmInetBuildSendHoplimit((U32)ipHdrParams->u.ipv6HdrParm.ttl.val,
                                    (U8 *)(cmsgData + curMsgIdx), &curMsgIdx);
        }

#ifdef LOCAL_INTF
        /* have to decide how to get the src addr to add in in6_pktinfo */
        if(ipHdrParams->u.ipv6HdrParm.srcAddr6.type == 6)
        {
            cmInet6BuildSendPktinfo(
                &ipHdrParams->u.ipv6HdrParm.srcAddr6.u.ipv6NetAddr,
                (U8 *)(cmsgData + curMsgIdx), &curMsgIdx,
                sockFd->protType);
        }
#endif /* LOCAL_INTF */

        /* copy each ipv6 ext header from ipHdrParams to the flat buffer
         * cmsgData one by one. */

        if (ipHdrParams->u.ipv6HdrParm.ipv6ExtHdr.hbhHdrPrsnt == TRUE)
            /* build HBH ext header in cmsgData starting at indx 0 */
            cmInet6BuildSendHBHOpts(
                &ipHdrParams->u.ipv6HdrParm.ipv6ExtHdr.hbhOptsArr,
                (U8 *)(cmsgData + curMsgIdx), &curMsgIdx, 0);

        /* now copy the elements from the Destination Option array one by
         * one to the Flat Buffer cmsgData. Start filling at indx curMsgIdx
         * which is the end of HBH hdr. */
        if (ipHdrParams->u.ipv6HdrParm.ipv6ExtHdr.destOptsPrsnt == TRUE)
            /* build Dest opt hdr starting at (cmsgData + curMsgIdx) */
            cmInet6BuildSendDestOpts(
                &(ipHdrParams->u.ipv6HdrParm.ipv6ExtHdr.destOptsArr),
                (U8 *)(cmsgData + curMsgIdx), &curMsgIdx, 1);

        /* copy Route header to to the Flat Buffer cmsgData */
        if (ipHdrParams->u.ipv6HdrParm.ipv6ExtHdr.rtOptsPrsnt == TRUE)
            /* curMsgIdx will be the indx where Dest opt ends in cmsgData */
            cmInet6BuildSendRouteOpts(
                &ipHdrParams->u.ipv6HdrParm.ipv6ExtHdr.rtOptsArr,
                (U8 *)(cmsgData + curMsgIdx), &curMsgIdx);

        /* msghrd struc's msg_control will point cmsgData and msg_controllen
         * will be the curMsgIdx */
        msg.msg_control = cmsgData;     /* pointer to Ancillary Data */
        msg.msg_controllen = curMsgIdx; /* total length of ancillary Data */

    }
#endif /* IPV6_OPTS_SUPPORTED */

    /* Loop till all the data is sent or till the sendmsg call cannot send
     * any more data. */
    do
    {
        /* build the send vector */
        /* cm_inet_c_001.main_50 - Partial send handling. Added variable to hold
           total length of the packed dbufs */
        retVal = egTLBuildSendIovec(mBuf, unSentLen, txArr, numDBufs, &i,
                                  &strtEndDBufNum, &ioLen);
        if (retVal != ROK)
        {
            if (retVal == RNA)
            {
                /* Incase of UDP/RAW messages call SCompressMsg. */
                if (sockFd->type != CM_INET_STREAM)
                {
                    /* Compress the message into a single dBuf */
                    ret = SCompressMsg(mBuf);
                    if (ret != ROK)
                        RETVALUE(RFAILED);

                    strtEndDBufNum = 0;
                    /* Rebuild the send vector */
                    /* cm_inet_c_001.main_50 - Partial send handling. Added variable to hold
                       total length of the packed dbuf */
                    ret = egTLBuildSendIovec(mBuf, unSentLen, txArr, numDBufs, &i,
                                           &strtEndDBufNum, &ioLen);
                    if (ret != ROK)
                        RETVALUE(RFAILED);

                    retVal = ROK;
                }
            }
            else
                RETVALUE(RFAILED);
        }
        msg.msg_iov           = txArr;
        msg.msg_iovlen        = i;


        ret = sendmsg(sockFd->fd, &msg, 0);
        if (-1 == ret)
        {
            if((errno == EAGAIN) ||
                    (errno == EWOULDBLOCK))
            {
                /* cm_inet_c_001.main_50 - Return without making length 0, if in case the partial
                   message was sent earlier */
                RETVALUE(EWOULDBLOCK);
            }

            printf("thUtlSendMsg() Failed : error(%d),"
                   " sockFd->fd(%ld)\n", errno, sockFd->fd);

            /* check if network is reacheble or not */
            if ((errno == ENETUNREACH))
            {
                RETVALUE(RFAILED);
            }

            /*  Check if connection was closed by the peer */
            if ((errno == EPIPE) ||
                    (errno == ECONNREFUSED) ||
                    (errno == ECONNABORTED))
            {
                *len = 0;
                RETVALUE(RCLOSED);
            }
            RETVALUE(RFAILED);
        }

        /* cm_inet_c_001.main_50 - Update the length only in successful cases */
        *len += ret;

        /* cm_inet_c_001.main_50 - if what is actually sent is less than what is attemped
         * to be sent, then return WOULDBLOCK
         */
        if (ret < ioLen)
            RETVALUE(RWOULDBLOCK);

        unSentLen -= ret;

    } while (*len < msgLen);

    RETVALUE(ROK);

}
#endif

#if 0
/** @details
               This functon reads data from a socket into a message.
 *             The buffers for the message  are allocated within the
 *             cmInetRead() function from the pool and region Id set in the
 *             info struct.
 *             If the number of octets given by the paramter len is not
 *             available the function immediately returns with RKDNA.
 *             If the len parameter is set to CM_INET_READ_ANY, the currently
 *             available data is read.
 *             Values for flag parameter:
 *
 *             CM_INET_NO_FLAG  - no additional control flag
 *             CM_INET_MSG_PEEK - do not destroy data on receive buffer
 *
 * @param [in]   sockFd       -  Socket Fd on which data needs to be sent
 * @param [in]   dstAddr      -  Destination IP Address
 * @param [in]   info         -  Memory Info
 * @param [in]   mBuf         -  Buffer to be sent out
 * @param [out]  len          -  Number of actually sent octets
 * @param [in]   ipHdrParams  -  IPv6 extensions headers
 * @param [in]   flags        -  Additional control flags, unused
 *
 * @return    ROK     - successful
 *             ROKDNA  - ok, data not available
 *             RCLOSED - connection closed by peer
 *             ROUTRES - failed, out of resources
 *             RFAILED - failedROK, RFAILED
 */

#ifdef ANSI
PRIVATE S16 egTLRecvSockMsg
(
    CmInetFd        *sockFd,        /* socket file descriptor */
    CmInetAddr      *fromAddr,      /* sender Internet address/port */
    CmInetMemInfo   *info,          /* buffer allocation info */
    Buffer         **mPtr,          /* received buffer structure */
    MsgLen          *len,           /* number of octets to read */
    /*  added for IPv6 */
#ifdef IPV6_OPTS_SUPPORTED
    CmInetIpHdrParm *ipHdrParams,    /* IPv6 extensions headers */
#endif /* IPV6_OPTS_SUPPORTED */
#ifdef LOCAL_INTF
    CmInetLocalInf  *localIf,       /* local interface on which pkt was recvd */
#endif /* LOCAL_INTF */
    S32              flags          /* additional control flags */
)
#else
/*  added for IPv6 */
#ifdef IPV6_OPTS_SUPPORTED
#ifdef LOCAL_INTF
PRIVATE S16 egTLRecvSockMsg(sockFd, fromAddr, info, mPtr, len,
                     ipHdrParams, localIf, flags)
CmInetFd        *sockFd;        /* socket file descriptor */
CmInetAddr      *fromAddr;      /* sender Internet address/port */
CmInetMemInfo   *info;          /* buffer allocation info */
Buffer         **mPtr;          /* received buffer structure */
MsgLen          *len;           /* number of octets to read */
CmInetIpHdrParm *ipHdrParams;   /* IPv6 extensions headers */
CmInetLocalInf  *localIf;       /* local interface on which pkt was recvd */
S32              flags;         /* additional control flags */
#else
PRIVATE S16 egTLRecvSockMsg(sockFd, fromAddr, info, mPtr, len, ipHdrParams, flags)
CmInetFd        *sockFd;        /* socket file descriptor */
CmInetAddr      *fromAddr;      /* sender Internet address/port */
CmInetMemInfo   *info;          /* buffer allocation info */
Buffer         **mPtr;          /* received buffer structure */
MsgLen          *len;           /* number of octets to read */
CmInetIpHdrParm *ipHdrParams;   /* IPv6 extensions headers */
S32              flags;         /* additional control flags */
#endif /* LOCAL_INTF */
#else
#ifdef LOCAL_INTF
PRIVATE S16 egTLRecvSockMsg(sockFd, fromAddr, info, mPtr, len, localIf, flags)
CmInetFd        *sockFd;        /* socket file descriptor */
CmInetAddr      *fromAddr;      /* sender Internet address/port */
CmInetMemInfo   *info;          /* buffer allocation info */
Buffer         **mPtr;          /* received buffer structure */
MsgLen          *len;           /* number of octets to read */
CmInetLocalInf  *localIf;       /* local interface on which pkt was recvd */
S32              flags;         /* additional control flags */
#else
PRIVATE S16 egTLRecvSockMsg(sockFd, fromAddr, info, mPtr, len, flags)
CmInetFd        *sockFd;        /* socket file descriptor */
CmInetAddr      *fromAddr;      /* sender Internet address/port */
CmInetMemInfo   *info;          /* buffer allocation info */
Buffer         **mPtr;          /* received buffer structure */
MsgLen          *len;           /* number of octets to read */
S32              flags;         /* additional control flags */
#endif /* LOCAL_INTF */
#endif /* IPV6_OPTS_SUPPORTED */
#endif /* ANSI */
{
    S32           ret;            /* temporary return value */
    U16           i;              /* index */
    U32           pendLen;        /* pending data length */
    S32           numBuf;         /* number of allocated dBufs */
    S32           recvLen;        /* number of received octets by recvmsg() */
    MsgLen        bufLen;         /* entire number of received octets */
    struct msghdr msg = {0};           /* message header */
    Buffer       *tempMsg = NULLP;        /* temporary message */
    CmInetIovec  rxArr[CM_INET_MAX_DBUF]; /* dynamic gather array */
    Buffer      **dBufs = NULLP;   /* dynamic array with allocated dBufs */
    S16           numDBufs;       /* number of allocated dBufs */
#ifdef T2K_MEM_LEAK_DBG
   char* file = __FILE__;
   U32 line = __LINE__;
#endif

    struct sockaddr_in *remAddr;  /* remote Internet address */
#ifdef IPV6_SUPPORTED
    struct sockaddr_in6 *remAddr6;  /* remote Internet address */
    struct sockaddr_in6 remSockAddr;/* to get packet's source IP address */
    /* added for IPv6 ext headers support */
#ifdef IPV6_OPTS_SUPPORTED
    CmInetIpv6RtHdr0     rtHdr0;          /* type 0 route header */
#endif /* IPV6_OPTS_SUPPORTED */
    U8                   ancillData[CM_INET_IPV6_ANCIL_DATA];
    /* from stack for IPv6 ancill data */
#else
    CmInetSockAddr       remSockAddr;     /* to get packet's src IP address */
    U8                   ancillData[CM_INET_IPV4_ANCIL_DATA];
    /* from stack for IPv4 ancill data */
#endif /* IPV6_SUPPORTED */
    /* added new definitions */
    Bool                 allocFlatBuf;    /* allocate a flat buffer */
    Data                 *recvBuf = NULLP;        /* receive buffer */
#if (defined(IPV6_OPTS_SUPPORTED) || defined(LOCAL_INTF))
    struct               cmsghdr *cmsgptr;/* pointer to struct cmsghdr */
#endif
    /* used by getsockopt */

    /* cm_inet_c_001.main_55:Removed unused variables errValue and optLen */

    TRC2(egTLRecvSockMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
    /* error check on parameters */
    if ((sockFd == NULLP) || CM_INET_INV_SOCK_FD(sockFd) ||
            (info == NULLP) || (mPtr == NULLP) || (len == NULLP))
    {
        RETVALUE(RFAILED);
    }
#endif /* ERRCLASS & ERRCLS_INT_PAR */

    *mPtr = NULLP;

    numBuf = 0;
    numDBufs = 0;

#ifdef IPV6_SUPPORTED
    remAddr = NULLP;
    remAddr6 = NULLP;
    cmMemset((U8*)ancillData, 0, sizeof(ancillData));
#endif /* IPV6_SUPPORTED */

    cmMemset((U8*)&remSockAddr, 0, sizeof(remSockAddr));
    pendLen = CM_INET_MAX_UDPRAW_MSGSIZE+1;

    /* check if there are enough pending data to read */
    if ((*len == CM_INET_READ_ANY) || ((U32)*len <= pendLen))
    {
        if (*len == CM_INET_READ_ANY)
        {
            /* read all pending data */
            /* cm_inet_c_001.main_54: Fix for Klockworks issue */
            bufLen = (MsgLen)pendLen;
            *len = (MsgLen)pendLen;
        }
        else
        {
#ifdef LONG_MSG
            /* max message length is limited to control the memory usage */
            if ((*len) > CM_INET_MAX_MSG_LEN)
            {
                (*len) = CM_INET_MAX_MSG_LEN;
            }
#endif
            /* read data length given by user */
            bufLen = *len;
        }

        /* Initialise variable */
        allocFlatBuf = FALSE;

        /*
         * maybe needs more than one recvmsg() call to read entire message
         * on a stream socket
         */
        while (bufLen > 0)
        {
            /* allocate gather vector, it's a dynamic array */
            numDBufs =  CM_INET_MAX_DBUF;

            ret = SGetSBuf(info->region, info->pool, (Data**)&dBufs,
                           numDBufs*sizeof(Buffer*));
            if (ret != ROK)
            {
                RETVALUE(ROUTRES);
            }

            /* Allocate dBufs for gather read */
            /* allocate dBufs for gathering read */
            if (sockFd->type == CM_INET_STREAM)
                ret = egTLbuildRecvBuf(info, bufLen, rxArr, dBufs, numDBufs, &msg,
                                   TRUE);
            else
                ret = egTLbuildRecvBuf(info, bufLen, rxArr, dBufs, numDBufs, &msg,
                                   FALSE);
            if (ret != ROK)
            {
                /* check if the function returned RNA */
                if (ret == RNA)
                {
                    /* Incase of UDP/RAW messages allocate a flat buffer. Incase
                     * of TCP ignore this error condition. The user will call
                     * cmInetRecvMsg again */
                    if (sockFd->type != (U8)CM_INET_STREAM)/* G++ */
                    {
                        /* cleanup  the dBuf array */
                        for (i = 0; i < msg.msg_iovlen; i++)
                            SPutDBuf(info->region, info->pool, dBufs[i]);

                        SPutSBuf(info->region, info->pool, (Data*)dBufs,
                                 numDBufs * sizeof(Buffer*));

                        /* allocate flat receive buffer */
                        ret = SGetSBuf(info->region, info->pool, &recvBuf, bufLen);
                        if (ret != ROK)
                            RETVALUE(ROUTRES);

                        allocFlatBuf = TRUE;

                        /* update the message structure */
#ifdef SS_LINUX
                        rxArr[0].iov_base = (Void*)recvBuf;
                        rxArr[0].iov_len = (U32)bufLen;
#else
                        rxArr[0].iov_base = (S8*)recvBuf;
                        rxArr[0].iov_len = bufLen;
#endif /* SS_LINUX */
                        msg.msg_iov           = rxArr;
                        msg.msg_iovlen        = 1;
                    }
                }
                else
                {
                    SPutSBuf(info->region, info->pool, (Data*)dBufs,
                             numDBufs*sizeof(Buffer*));
                    RETVALUE(ret);
                }
            }

            numBuf =  msg.msg_iovlen;

            /* setup destination Internet address structure */
            if (fromAddr != NULLP)
            {
#ifdef SS_LINUX
                msg.msg_name    = (Void*)&remSockAddr;
#else
#ifdef SS_PS
                msg.msg_name    = (char *)&remSockAddr;
#else
                msg.msg_name    = (caddr_t)&remSockAddr;
#endif /* SS_PS */
#endif /* SS_LINUX */
                msg.msg_namelen = sizeof(remSockAddr);
            }
            else
            {
                msg.msg_name    = NULLP;
                msg.msg_namelen = 0;
            }

            msg.msg_control      = ancillData;
            msg.msg_controllen   = sizeof(ancillData);

            recvLen = recvmsg(sockFd->fd, &msg, flags);
            if ((recvLen == -1) || (recvLen > 0x7FFF))
            {
                /* Moved up the cleanup precedures here before returning */
                /* Cleanup flat buffer if allocated */
                if (allocFlatBuf)
                    SPutSBuf(info->region, info->pool, recvBuf, bufLen);
                else
                {
                    /* cleanup */
                    for (i = 0; i < numBuf; i++)
                    {
                        SPutDBuf(info->region, info->pool, dBufs[i]);
                    }
                    SPutSBuf(info->region, info->pool, (Data*)dBufs,
                             numDBufs*sizeof(Buffer*));
                }

                /* cm_inet_c_001.main_50 - Free the buffer only when valid, it might be that
                 * it has partially received data
                 */
                /* added check ERR_AGAIN when CMINETFLATBUF is not defined.
                   added check ERR_WOULDBLOCK */
                if ((errno == EAGAIN) ||
                        (errno == EWOULDBLOCK))
                {
                    /* cm_inet_c_001.main_50 : If message is read partially then just return
                     * OK without freeing the mPtr. This will gaurd us
                     * against unexpected WOULDBLOCKS observed in solaris
                     */
                    if (*mPtr != NULLP)
                        RETVALUE(ROK);

                    RETVALUE(ROKDNA);
                }

                /* cm_inet_c_001.main_50 - Free the buffer only when valid, it might be that
                 * it has partially received data
                 */
                if (*mPtr != NULLP)
                {
                    SPutMsg(*mPtr);
                }

                /*  If this happens then cmInetRecvMsg must return RCLOSED.
                 *  Needed for getting icmp msgs */
                if (errno == ECONNABORTED)
                {
                    *len = 0;
                    RETVALUE(RCLOSED);
                }
                RETVALUE(RFAILED);
            }

            bufLen -= recvLen;


            /* setup return destination Internet address */
            if (fromAddr != NULLP)
            {
#ifdef IPV6_SUPPORTED
                if (msg.msg_namelen == sizeof(struct sockaddr_in6))
                {
                    remAddr6 = (struct sockaddr_in6 *)&remSockAddr;
                    fromAddr->type = CM_INET_IPV6ADDR_TYPE;
                    fromAddr->u.ipv6Addr.port =
                        CM_INET_NTOH_U16(remAddr6->sin6_port);
                    CM_INET_COPY_IPV6ADDR(&fromAddr->u.ipv6Addr.ipv6NetAddr,
                                          &remAddr6->sin6_addr);
                }
                else
                {
                    remAddr = (struct sockaddr_in *)&remSockAddr;
                    fromAddr->type = CM_INET_IPV4ADDR_TYPE;
                    fromAddr->u.ipv4Addr.port = CM_INET_NTOH_U16(remAddr->sin_port);
                    fromAddr->u.ipv4Addr.address =
                        CM_INET_NTOH_U32(remAddr->sin_addr.s_addr);
                }
#else
                remAddr = (struct sockaddr_in *)&remSockAddr;
                fromAddr->port    = CM_INET_NTOH_U16(remAddr->sin_port);
                fromAddr->address = CM_INET_NTOH_U32(remAddr->sin_addr.s_addr);
#endif /* IPV6_SUPPORTED */
            }

            /* Incase a flat buffer was allocated get
             * a message to pass up */
            if (allocFlatBuf)
            {
                bufLen += recvLen;

                /* Get a message */
                ret = SGetMsg(info->region, info->pool, &tempMsg);
                if (ret != ROK)
                {
                    /* cleanup */
                    SPutSBuf(info->region, info->pool, recvBuf, bufLen);
                    RETVALUE(ret);
                }

                /* cm_inet_c_001.main_48 : A 0 len UDP packet could be received */
                if ( recvLen > 0)
                {
                    ret = SAddPstMsgMult(recvBuf, recvLen, tempMsg);
                    if (ret != ROK)
                    {
                        SPutSBuf(info->region, info->pool, recvBuf, bufLen);
                        SPutMsg(tempMsg);
                        RETVALUE(ret);
                    }
                }

                *mPtr = tempMsg;

                SPutSBuf(info->region, info->pool, recvBuf, bufLen);
                /* cm_inet_c_001.main_48 :flat buffers are allocated
                 * for non -TCP sockets. On these sockets we can receive
                 * only one message at a time
                 */
                /* cm_inet_c_001.main_54: Fix for Klockworks issue */
                *len = (MsgLen)recvLen;
                break;
            }
            else
            {
                /* build message out of dBufs */
                ret = egTLBuildRecvMsg(info, rxArr, numBuf, recvLen, dBufs, &tempMsg);
                if (ret != ROK)
                {
                    /* Deallocate previously allocated
                     * mBuf */
                    if (*mPtr != NULLP)
                        SPutMsg(*mPtr);
                    SPutSBuf(info->region, info->pool, (Data*)dBufs,
                             numDBufs*sizeof(Buffer*));
                    RETVALUE(ret);
                }
            }

            if (*mPtr == NULLP)
            {
                /* it's first recvmsg() call */
                *mPtr = tempMsg;
            }
            else
            {
                /* concatenate messages */
                ret = SCatMsg(*mPtr, tempMsg, M1M2);
                if (ret != ROK)
                {
                    /* cleanup */
                    SPutMsg(*mPtr);
                    SPutMsg(tempMsg);
                    SPutSBuf(info->region, info->pool, (Data*)dBufs,
                             numDBufs*sizeof(Buffer*));
                    RETVALUE(RFAILED);
                }
                SPutMsg(tempMsg);
            }

            SPutSBuf(info->region, info->pool, (Data*)dBufs,
                     numDBufs*sizeof(Buffer*));

            /*
             * a message is always read atomically on a datagram socket,
             * therefore it's ok to read less than pending data!
             */
#ifdef CM_INET2
            if ((sockFd->type == CM_INET_DGRAM) ||
                    (sockFd->type == CM_INET_RAW))
            {
                /* cm_inet_c_001.main_54: Fix for Klockworks issue */
                *len = (MsgLen)recvLen;
                break;
            }
#else /* CM_INET2 */
            if (sockFd->type == CM_INET_DGRAM)
            {
                /* cm_inet_c_001.main_54: Fix for Klockworks issue */
                *len = (MsgLen)recvLen;
                break;
            }
#endif /* CM_INET2 */
        } /* while(bufLen > 0) (only for stream sockets) */

        /* cm_inet_c_001.main_48 : For UDP, it is possible to receive
         * a 0 byte datagram, in this case just return ROKDNA
         */

#ifdef CM_INET2
        if ((sockFd->type == CM_INET_DGRAM || sockFd->type == CM_INET_RAW)
                && (*len == 0))
#else
        if ((sockFd->type == CM_INET_DGRAM) && (*len == 0))
#endif
        {
            *len = 0;
            if (*mPtr != NULLP)
            {
                SPutMsg(*mPtr);
            }
            RETVALUE(ROKDNA);

        }

        /* Received len == CM_INET_MAX_UDPRAW_MSGSIZE+1
         * Drop this message
         */

#ifdef CM_INET2
        if ((sockFd->type == CM_INET_DGRAM || sockFd->type == CM_INET_RAW)
                && (*len == (CM_INET_MAX_UDPRAW_MSGSIZE+1)))
#else
        if ((sockFd->type == CM_INET_DGRAM)
                && (*len == (CM_INET_MAX_UDPRAW_MSGSIZE+1)))
#endif
        {
            *len = 0;
            if (*mPtr != NULLP)
            {
                SPutMsg(*mPtr);
            }

            RETVALUE(ROKDNA);

        }
    }
    else
    {
        /* not enough data pending yet */
        RETVALUE(ROKDNA);
    }

    RETVALUE(ROK);
}
#endif

#if 0
/** @details
 *     This function is used by ThinLayer to build a message out of the received dBufs.
 *
 * @param [in]   info    -  buffer allocation info
 * @param [in]   rxArr   -  scatter array
 * @param [in]   numBuf  -  number of allocated dBufs
 * @param [in]   msgLen  -  message length
 * @param [in]  dBufs   -  dBufs
 * @param [out]   mPtr    -  message built from dBufs
 *
 * @return    ROK     - successful
 *            ROKDNA  - ok, data not available
 *            RFAILED - failedROK, RFAILED
 */


#ifdef ANSI
PRIVATE S16 egTLBuildRecvMsg
(
    CmInetMemInfo  *info,           /* buffer allocation info */
    CmInetIovec     rxArr[],        /* scatter array */
    S16             numBuf,         /* number of allocated dBufs */
    MsgLen          msgLen,         /* message length */
    Buffer         *dBufs[],        /* dBufs */
    Buffer        **mPtr            /* message built from dBufs */
)
#else
PRIVATE S16 egTLBuildRecvMsg(info, rxArr, numBuf, msgLen, dBufs, mPtr)
CmInetMemInfo  *info;           /* buffer allocation info */
CmInetIovec     rxArr[];        /* scatter array */
S16             numBuf;         /* number of allocated dBufs */
MsgLen          msgLen;         /* length of one particular dBuf */
Buffer         *dBufs[];        /* dBufs */
Buffer        **mPtr;           /* message built from dBufs */
#endif
{
    S16      ret;                 /* return value */
    S16      i;                   /* dBuf index counter */
    MsgLen   bufLen;              /* length of one particular dBuf */
    /* cm_inet_c_001.main_54: Fix for Klockworks issue */
    Buffer  *mBuf = NULLP;        /* allocated message */
#ifdef T2K_MEM_LEAK_DBG
   char* file = __FILE__;
   U32 line = __LINE__;
#endif

    ret = RFAILED;
    i   = 0;

    /* build message */
    ret = SGetMsg(info->region, info->pool, &mBuf);
    if (ret != ROK)
    {
        goto cleanup;
    }

    /* link buffers to message */
    while (i < numBuf)
    {
        /* cm_inet_c_001.main_58: fix for klockwork issue */
        bufLen = (MsgLen)rxArr[i].iov_len;
        if (msgLen < bufLen)
        {
            bufLen = msgLen;
        }
        ret = SUpdMsg(mBuf, dBufs[i], bufLen);
        if (ret != ROK)
        {
            SPutMsg(mBuf);
            goto cleanup;
        }
        msgLen -= bufLen;
        i++;
        if (msgLen <= 0)
        {
            ret = ROK;
            break;
        }
    }

    *mPtr = mBuf;

cleanup:
    /* cleanup unused buffers */
    while (i < numBuf)
    {
        SPutDBuf(info->region, info->pool, dBufs[i]);
        i++;
    }

    RETVALUE(ret);
}
#endif
/** @details
 *     This function is used by ThinLayer to build I/O vector to send a message.
 *
 * @param [in]   mBuf    -  Message buffer
 * @param [in]   msgLen   - Length of mBuf
 * @param [out]   txArr  -   transmit scatter vector array
 * @param [in]   numDBufs  - Maximum number of dBufs to use
 * @param [in]   numIovElems   -  Number of iov elements in array
 * @param [in]  strtEndDBufNum    -  dBuf number to start and end
 * @param [in]  ioLen    -  Len of dbuf packed into IO-vector
 *
 *
 * @return     ROK     - successful
 *             RFAILED - failed
 *             ROUTRES - failed, out of resources
 *             RNA     - failed, not available, indicates that the
 *                       maximum number of dBufs are not sufficient
 *                       to hold the entire message
 */

#ifdef ANSI
PRIVATE S16 egTLBuildSendIovec
(
    Buffer         *mBuf,           /* Message buffer */
    MsgLen         msgLen,          /* Length of mBuf */
    CmInetIovec    txArr[],         /* transmit scatter vector array */
    S16            numDBufs,        /* Maximum number of dBufs to use */
    S16            *numIovElems,    /* Number of iov elements in array */
    U32            *strtEndDBufNum, /* dBuf number to start and end */
    MsgLen         *ioLen           /* Len of dbuf packed into IO-vector */
)
#else
PRIVATE S16 egTLBuildSendIovec(mBuf, msgLen, txArr, numDBufs, numIovElems,
                            strtEndDBufNum,ioLen)
Buffer         *mBuf;           /* Message buffer */
MsgLen         msgLen;          /* Length of mBuf */
CmInetIovec    txArr[];         /* transmit scatter vector array */
S16            numDBufs;        /* Maximum number of dBufs to use */
S16            *numIovElems;    /* Number of iov elements in array */
U32            *strtEndDBufNum; /* dBuf number to start and end */
MsgLen         *ioLen;          /* Len of dbuf packed into IO-vector */
#endif
{
    S16         ret;
    MsgLen      dLen;
    S16         iovIdx;
    Buffer      *dBuf;
    Data        *dPtr;
    MsgLen      allocLen;
    U32         dBufsToSkip;

    /* Initialisations */
    (*numIovElems) = 0;
    iovIdx = 0;
    allocLen = 0;

    /* cm_inet_c_001.main_50 - Intialize the newly added parameter */
    *ioLen = 0;

    /* Set up vector for gathering send */
    ret = SInitNxtDBuf(mBuf);
    if (ret != ROK)
    {
        RETVALUE(RFAILED);
    }

    iovIdx = 0;
    txArr[iovIdx].iov_len = 0;

    if ((*strtEndDBufNum != 0))
    {
        /* Skip through the required number of dBufs */
        dBufsToSkip = *strtEndDBufNum;

        while(dBufsToSkip)
        {
            ret = SGetNxtDBuf(mBuf, &dBuf);
            if (ret != ROK)
                RETVALUE(RFAILED);
            dBufsToSkip --;
        }
    }

    for (;;)
    {
        ret = SGetNxtDBuf(mBuf, &dBuf);
        if (ret == ROK)
        {
            ret = SGetDataTx(dBuf, &dPtr, &dLen);
            if (ret != ROK)
            {
                ret = RFAILED;
                break;
            }

            txArr[iovIdx].iov_base = (S8 *)dPtr;
            txArr[iovIdx].iov_len = dLen;

            allocLen += dLen;
        }
        else if  (ret == ROKDNA)
        {
            ret = ROK;
            break;
        }
        else
        {
            ret = RFAILED;
            break;
        }

        iovIdx += 1;

        if (iovIdx >= numDBufs)
        {
            if (allocLen >= msgLen)
                ret = ROK;
            else
                ret = RNA;
            break;
        }
    }

    (*numIovElems) = iovIdx;
    (*strtEndDBufNum) += iovIdx;

    *ioLen = allocLen;

    RETVALUE(ret);

}

#if 0
#ifdef ANSI
PRIVATE S16 egTLbuildRecvBuf
(
CmInetMemInfo  *info,           /* buffer allocation info */
MsgLen          len,            /* message length */
CmInetIovec     rxArr[],        /* gather array */
Buffer         *dBuf[],         /* allocated dBufs */
U16             maxSize,        /* size of rxArr/dBuf array */
struct msghdr  *msg,            /* message header for recvmsg() */
Bool           isStrmMsg        /* Is a TCP message */
)
#else
PRIVATE S16 egTLbuildRecvBuf(info, len, rxArr, dBuf, maxSize, msg, isStrmMsg)
CmInetMemInfo   *info;          /* buffer allocation info */
MsgLen           len;           /* message length */
CmInetIovec      rxArr[];       /* gather array */
Buffer          *dBuf[];        /* allocated dBufs */
U16              maxSize;       /* size of rxArr/dBuf array */
struct msghdr   *msg;           /* message header for recvmsg() */
Bool            isStrmMsg;      /* Is a TCP message */
#endif
{
   S16     ret;                 /* temporary return value */
   U16     numBuf;              /* number of dBufs */
   U16     i;                   /* dBuf index counter */
   Data   *dPtr;                /* data pointer */
   /* cm_inet_c_001.main_47: 102069 Changed from S32 to MsgLen for bufLen*/
   MsgLen  bufLen;              /* entire receive buffer length, if S16
                                   could wrap to negative number */
   MsgLen  dLen;                /* buffer length */
#ifdef T2K_MEM_LEAK_DBG
   char* file = __FILE__;
   U32 line = __LINE__;
#endif


   numBuf = 0;
   bufLen = 0;

   /* Initialise ret and part of msg here */
   ret = ROK;

   /* added defined(_XPG4_2) */
   /* Moved initialisation of msg here. */

#if (defined(SS_LINUX) || defined(_XPG4_2))
   msg->msg_control    = NULLP;
   msg->msg_controllen  = 0;
#else
   msg->msg_accrights     = NULLP;
   msg->msg_accrightslen  = 0;
#endif /* SS_LINUX */

   /* Check if maxSize if enough to hold the entire message length before
    * going into the loop. If the boolean isStrmMsg is TRUE then the recv
    * buf is built even if the whole message cannot be accomodated. */
   ret = SGetDBuf(info->region, info->pool, &dBuf[numBuf]);
   if (ret != ROK)
      RETVALUE(ret);

   /* Get the data part */
   ret = SGetDataRx(dBuf[numBuf], 0, &dPtr, &dLen);
   if (ret != ROK)
   {
      numBuf++;           /* because of cleanup */
      goto cleanup;
   }

   if (!isStrmMsg)
   {
      /* The assumption here is that all dBuf's from a given region and
       * pool have a constance size */
      if (len > (maxSize * dLen))
      {
         ret = RNA;
         numBuf++;           /* because of cleanup */
         goto cleanup;
      }
   }

#ifdef SS_LINUX
  rxArr[numBuf].iov_base = (Void*)dPtr;
  rxArr[numBuf].iov_len = (U32)dLen;
#else
  rxArr[numBuf].iov_base = (S8*)dPtr;
  rxArr[numBuf].iov_len = dLen;
#endif /* SS_LINUX */

  bufLen += dLen;
  numBuf++;

   /* allocate buffer space for entire message length */
   while (bufLen < len)
   {
      if (numBuf >= maxSize)
      {
         /* to big to fit in gather vector array */
         ret = RNA;
         break;
      }
      ret = SGetDBuf(info->region, info->pool, &dBuf[numBuf]);
      if (ret != ROK)
      {
         goto cleanup;
      }
      ret = SGetDataRx(dBuf[numBuf], 0, &dPtr, &dLen);
      if (ret != ROK)
      {
         numBuf++;           /* because of cleanup */
         goto cleanup;
      }
#ifdef SS_LINUX
      rxArr[numBuf].iov_base = (Void*)dPtr;
      rxArr[numBuf].iov_len = (U32)dLen;
#else
      rxArr[numBuf].iov_base = (S8*)dPtr;
      rxArr[numBuf].iov_len = dLen;
#endif /* SS_LINUX */

      bufLen += dLen;
      numBuf++;
   }
   /* adjust last buffer length */
   /*  check if we broke out because numBuf >= maxSize */
   if (bufLen < len)
      rxArr[numBuf - 1].iov_len = dLen;
   else
      rxArr[numBuf - 1].iov_len = dLen - (bufLen - len);

   /* setup recvmsg() message header */
   msg->msg_iov           = rxArr;
   msg->msg_iovlen        = numBuf;

   RETVALUE(ret);

cleanup:
   /* cleanup */
   for (i = 0; i < numBuf; i++)
      SPutDBuf(info->region, info->pool, dBuf[i]);

   msg->msg_iovlen = 0;

   RETVALUE(ret);
}
#endif

#if (defined(TENB_T2K3K_SPECIFIC_CHANGES)) && (!defined(TENB_DISABLE_DL_ZBC))
PUBLIC U32 egRcvPackCnt;
/*
 * *
 * *       Fun:    egTLRecvZbcUdpMsg
 * *
 * *       Desc:
 * *
 * *       Ret:    ROK     - ok
 * *               RFAILED - failed
 * *
 * *       Notes:  None
 * *
 * *       File:   hi_bdy3.c
 * *
 * */
#ifdef ANSI
PRIVATE S16 egTLRecvZbcUdpMsg
(
U32 sockFd,
CmTptAddr *remAddr,
CmInetMemInfo memInfo,
Buffer             **mBuf
)
#else
PRIVATE S16 egTLRecvZbcUdpMsg(sockFd, remAddr, memInfo, mBuf)
U32 sockFd;
CmTptAddr *remAddr;
CmInetMemInfo memInfo;
Buffer            **mBuf;
#endif
{
/* kloc_works: initialize the recvBuf */   
   Data              *recvBuf = NULLP;  /* Buffer for receiving the payload from socket */
   MsgLen             recvBufLen;
   struct sockaddr_in frmAddr = {0};
//   MsgLen             frmLen = sizeof(struct sockaddr);
   socklen_t            frmLen = sizeof(frmAddr);

#ifndef NTL_LIB
    recvBufLen = recvfrom(sockFd, &recvBuf, -1, 0, 
                        (struct sockaddr*)(&frmAddr), &frmLen);
#else
    if (ntl_hLib >= 0)
    {
        recvBufLen = ntl_recvfrom(ntl_hLib, sockFd, &recvBuf, -1, MSG_DONTWAIT, 
                            (struct sockaddr*)(&frmAddr), &frmLen);
    }
    else
    {
        recvBufLen = recvfrom(sockFd, &recvBuf, -1, 0, 
                        (struct sockaddr*)(&frmAddr), &frmLen);
    }
#endif

   if(SOCK_ERROR == recvBufLen)
   {
      if((errno == EAGAIN) || (errno == EWOULDBLOCK))
      {
         RETVALUE(ROKDNA);
      }
      printf("\n Failed to receive from socketFD =[%lu] Error Code =[%s]",sockFd,strerror(errno));
      printf("\n Parameter passed sockFd=[%lu],MSG_DONTWAIT=[%d],frmLen=[%d],frmAddr Address=[%lu]",sockFd,MSG_DONTWAIT, frmLen, (U32)&frmAddr);
      RETVALUE(RFAILED);
   }

   /* Added check for invalid address received from Socket interface */
   if(recvBuf < (U8*)(0x90000000))
   {
      printf("Received invalid address from socekt 0x%pn\n", recvBuf);
      RETVALUE(RFAILED);
   }
#ifdef T2K_MEM_LEAK_DBG
   if(ROK != (SAttachPtrToBufNew(memInfo.region, memInfo.pool, recvBuf,
               recvBufLen, mBuf,__FILE__,__LINE__)))
#else
    if(ROK != (SAttachPtrToBuf(memInfo.region, memInfo.pool, recvBuf,
               recvBufLen, mBuf)))
#endif
   {
      printf("Failed to attach the pointer to mBuf\n");
      RETVALUE(RFAILED);
   }


#ifdef T2K_MEM_LEAK_DBG
   InsertToT2kMemLeakInfo((U32)(recvBuf - ((U32)recvBuf % 512)),recvBufLen,__LINE__,__FILE__);
#endif
   remAddr->u.ipv4TptAddr.port    = CM_INET_NTOH_U16(frmAddr.sin_port);
   remAddr->u.ipv4TptAddr.address = CM_INET_NTOH_U32(frmAddr.sin_addr.s_addr);
   remAddr->type = CM_TPTADDR_IPV4;

   RETVALUE(ROK);
}


#ifdef FLAT_BUFFER_OPT
/*
 * *
 * *       Fun:    egTLRecvZbcUdpMsgFB
 * *
 * *       Desc:
 * *
 * *       Ret:    ROK     - ok
 * *               RFAILED - failed
 * *
 * *       Notes:  None
 * *
 * *       File:   hi_bdy3.c
 * *
 * */
#ifdef ANSI
PRIVATE S16 egTLRecvZbcUdpMsgFB
(
U32           sockFd,
CmTptAddr    *remAddr,
U8            **recvBuf,
U32           *bufLen
)
#else
PRIVATE S16 egTLRecvZbcUdpMsgFB(sockFd, remAddr, mBuf, bufLen)
U32           sockFd;
CmTptAddr *   remAddr;
U8            **recvBuf;
U32           *bufLen;
#endif
{
   struct sockaddr_in frmAddr = {0};
   socklen_t            frmLen = sizeof(frmAddr);

#ifndef NTL_LIB
    *bufLen = recvfrom(sockFd, recvBuf, -1, 0, (struct sockaddr*)(&frmAddr), &frmLen);
#else
    if (ntl_hLib >= 0)
    {
        *bufLen = ntl_recvfrom(ntl_hLib, sockFd, recvBuf, -1, MSG_DONTWAIT, 
                        (struct sockaddr*)(&frmAddr), &frmLen);
    }
    else
    {
    	*bufLen = recvfrom(sockFd, recvBuf, -1, 0,
                            (struct sockaddr*)(&frmAddr), &frmLen);
    }
#endif
   if(SOCK_ERROR == *bufLen)
   {
      if((errno == EAGAIN) || (errno == EWOULDBLOCK))
      {
         RETVALUE(ROKDNA);
      }
      printf("\n Failed to receive from socketFD =[%lu] Error Code =[%s]",sockFd,strerror(errno));
      printf("\n Parameter passed sockFd=[%lu],MSG_DONTWAIT=[%d],frmLen=[%d],frmAddr Address=[%lu]",sockFd,MSG_DONTWAIT, frmLen, (U32)&frmAddr);
      RETVALUE(RFAILED);
   }

#if 0
   if(ROK != (SAttachPtrToBuf(memInfo.region, memInfo.pool, recvBuf,
               recvBufLen, mBuf)))
   {
      printf("Failed to attach the pointer to mBuf\n");
      RETVALUE(RFAILED);
   }
#endif
   packetData.numOfPktsRcvd++;
   packetData.numBytesRcvd += *bufLen;

#ifdef T2K_MEM_LEAK_DBG
   InsertToT2kMemLeakInfo((U32)(*recvBuf - ((U32)*recvBuf % 512)),(U32)*bufLen,__LINE__,__FILE__);
#endif
   remAddr->u.ipv4TptAddr.port    = CM_INET_NTOH_U16(frmAddr.sin_port);
   remAddr->u.ipv4TptAddr.address = CM_INET_NTOH_U32(frmAddr.sin_addr.s_addr);
   remAddr->type = CM_TPTADDR_IPV4;

   RETVALUE(ROK);
}
#endif
#endif
/*purecov compilation error fix:ccpu00136421 */
#if !((defined(TENB_T2K3K_SPECIFIC_CHANGES)) && (!defined(TENB_DISABLE_DL_ZBC)))
/*
 * *
 * *       Fun:    egTLRecvMsgFromSocket
 * *
 * *       Desc:
 * *
 * *       Ret:    ROK     - ok
 * *               RFAILED - failed
 * *
 * *       Notes:  None
 * *
 * *       File:   hi_bdy3.c
 * *
 * */
#ifdef ANSI
PRIVATE S16 egTLRecvMsgFromSocket
(
U32 sockFd,
CmTptAddr *remAddr,
CmInetMemInfo memInfo,
Buffer             **mBuf
)
#else
PRIVATE S16 egTLRecvMsgFromSocket(sockFd, remAddr, memInfo, mBuf)
U32 sockFd;
CmTptAddr *remAddr;
CmInetMemInfo memInfo;
Buffer            **mBuf;
#endif
{
   Data              recvBuf[6000];  /* Buffer for receiving the payload from socket */
/*purecov compilation error fix:ccpu00136421 */
   /* Data              *recvBuf;   Buffer for receiving the payload from socket */
   MsgLen             recvBufLen;
   struct sockaddr_in frmAddr = {0};
/*purecov compilation error fix:ccpu00136421 */   
/* socklen_t            frmLen = sizeof(struct sockaddr); */
   socklen_t            frmLen = sizeof(frmAddr);
   U16                myLen=0;

   recvBufLen = recvfrom(sockFd, &recvBuf[0], sizeof(recvBuf), 0, 
                        (struct sockaddr*)(&frmAddr), &frmLen);


   if(SOCK_ERROR == recvBufLen)
   {
      if((errno == EAGAIN) || (errno == EWOULDBLOCK))
      {
         RETVALUE(ROKDNA);
      }
      printf("\n Failed to receive from socketFD =[%lu] Error Code =[%s]",sockFd,strerror(errno));
      printf("\n Parameter passed sockFd=[%lu],MSG_DONTWAIT=[%d],frmLen=[%d],frmAddr Address=[%lu]",sockFd,MSG_DONTWAIT, frmLen, (U32)&frmAddr);
      RETVALUE(RFAILED);
   }
   myLen = (recvBuf[2] << 8) | recvBuf[3];

   if(recvBufLen - 8 != myLen)
   {
      printf("Len received = %d ... len inside buf = %02x %02x\n",recvBufLen, recvBuf[2],recvBuf[3]);
   }

   if(SGetMsg(memInfo.region, memInfo.pool,mBuf) != ROK)
   {
      RETVALUE(RFAILED);
   }
   remAddr->u.ipv4TptAddr.port    = CM_INET_NTOH_U16(frmAddr.sin_port);
   remAddr->u.ipv4TptAddr.address = CM_INET_NTOH_U32(frmAddr.sin_addr.s_addr);
   remAddr->type = CM_TPTADDR_IPV4;

   SAddPstMsgMult(recvBuf, recvBufLen, *mBuf);
   RETVALUE(ROK);
}
#endif

#ifdef FLAT_BUFFER_OPT
#if !((defined(TENB_T2K3K_SPECIFIC_CHANGES)) && (!defined(TENB_DISABLE_DL_ZBC)))
/*
 * *
 * *       Fun:    egTLRecvMsgFromSocketFB
 * *
 * *       Desc:
 * *
 * *       Ret:    ROK     - ok
 * *               RFAILED - failed
 * *
 * *       Notes:  None
 * *
 * *       File:   hi_bdy3.c
 * *
 * */
#ifdef ANSI
PRIVATE S16 egTLRecvMsgFromSocketFB
(
U32 sockFd,
CmTptAddr *remAddr,
U8        *buf,
U32       *bufLen
)
#else
PRIVATE S16 egTLRecvMsgFromSocketFB(sockFd, remAddr, memInfo, mBuf)
U32 sockFd;
CmTptAddr *remAddr;
U8        *buf;
U32       *bufLen;
#endif
{
//   Data              *recvBuf;  /* Buffer for receiving the payload from socket */
   struct sockaddr_in frmAddr = {0};
   //socklen_t            frmLen = sizeof(struct sockaddr);
   socklen_t            frmLen = sizeof(frmAddr);

   *bufLen = recvfrom(sockFd, buf, -1, 0, 
                        (struct sockaddr*)(&frmAddr), &frmLen);


   if(SOCK_ERROR == *bufLen)
   {
      if((errno == EAGAIN) || (errno == EWOULDBLOCK))
      {
         RETVALUE(ROKDNA);
      }
      printf("\n Failed to receive from socketFD =[%lu] Error Code =[%s]",sockFd,strerror(errno));
      printf("\n Parameter passed sockFd=[%lu],MSG_DONTWAIT=[%d],frmLen=[%d],frmAddr Address=[%lu]",sockFd,MSG_DONTWAIT, frmLen, (U32)&frmAddr);
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}
#endif /* #ifndef (defined(TENB_T2K3K_SPECIFIC_CHANGES)) && (!defined(TENB_DISABLE_DL_ZBC))*/
/*
 * *
 * *       Fun:    egTLHndlRecv
 * *
 * *       Desc:
 * *
 * *       Ret:    ROK     - ok
 * *               RFAILED - failed
 * *
 * *       Notes:  None
 * *
 * *       File:   hi_bdy3.c
 * *
 * */
#ifdef ANSI
PRIVATE S16 egTLHndlRecv
(
EgTLServerCb       *egTLServerCb,
U8                 *recvBuf,
U32                bufLen,
CmTptAddr          *remAddr
)
#else
PRIVATE S16 egTLHndlRecv(egTlServerCb, recvBuf, bufLen, remAddr)
EgTLServerCb       *egTLServerCb;
U8                 *recvBuf;
U32                buflen;
CmTptAddr          *remAddr;
#endif
{
   Buffer *mBuf;
   CmIpHdrParm *ipHdrParm = NULLP;
   EgTptSrvCb        *serverCb;
   EgTSapCb          *tSapCb;

   /* Added check for invalid address received from Socket interface */
   if(recvBuf < (U8*)(0x90000000))
   {
      printf("Received invalid address from socekt 0x%p\n\n", recvBuf);
      RETVALUE(RFAILED);
   }

   if(ROK != (egHndlRecvFb(recvBuf, bufLen)))
   {
#if (defined(TENB_T2K3K_SPECIFIC_CHANGES)) && (!defined(TENB_DISABLE_DL_ZBC))
#ifdef T2K_MEM_LEAK_DBG
     if(ROK != (SAttachPtrToBufNew(egTLCb.memInfo.region, egTLCb.memInfo.pool, recvBuf,
                   bufLen, &mBuf,__FILE__,__LINE__)))
#else
     if(ROK != (SAttachPtrToBuf(egTLCb.memInfo.region, egTLCb.memInfo.pool, recvBuf,
                   bufLen, &mBuf)))
#endif
     {
        printf("Failed to attach the pointer to mBuf\n");
        RETVALUE(RFAILED);
     }
#else
      S16               ret;
     ret = SGetMsg(egTLCb.memInfo.region, egTLCb.memInfo.pool, &mBuf);
     if (ret != ROK)
     {
         RETVALUE(ret);
     }
     ret = SAddPstMsgMult(recvBuf, bufLen, mBuf);
     if (ret != ROK)
     {
        SPutMsg(mBuf);
        RETVALUE(ret);
     }

#endif

      /*Send Buffer to application*/
      EgLiHitUDatInd(&egTLCb.egPst,egTLServerCb->srvConId,egTLServerCb->srvConId,
            remAddr, &egTLServerCb->serverAddress, ipHdrParm, mBuf);
   }
   else
   {
      tSapCb = egCb.tSapCb;
      serverCb = tSapCb->tptSrvCbLst[egTLServerCb->srvConId];
      /*********************
       * Update Statistics *
       *********************/
      serverCb->stats.totalMsgsRx++;
      serverCb->ipCbPtr->ipStats.totalMsgsRx++; 

   }
   RETVALUE(ROK);
}
#endif

/* EGTP Statistics for debugging*/
PUBLIC Void PrintEGTPStats(void)
{
   printf("EGTP: SendDropsReason19 = (%lu)\n",g_egtpSockDropsDueToReason19);
}
PUBLIC Void ResetEGTPStats(void)
{
   g_egtpSockDropsDueToReason19 = 0;
}
/* EGTP Statistics for debugging*/
#ifdef TENB_UL_FP

/*************************************************************************
 *      Fun:   egFpTunProcEguDatReq
 *
 *      Desc:  This function processes the GPDU Message
 *             Request from the UI.
 *
 *      Ret:
 *
 *      Note:
 *
 *      File:   eg_socklayer.c
***********************************************************************/
#ifdef ANSI
PUBLIC S16 egFpTunProcEguDatReq
(
U32 lclTeid,       /* Event from UI */
U32 remTeid,
U8  tos,
U32 tPduSize,
Buffer* mBuf
)
#else
PUBLIC S16 egFpTunProcEguDatReq (egtUEvnt, usap, pst)
U32 lclTeid;       /* Event from UI*/
U32 remTeid;       /*Upper Sap CB*/
U8  tos;
U32 tPduSize;
Buffer* mbuf;
#endif
{
   EgTeIdCb          *teIdCb = NULLP;
   S32               ret = ROK;
   EgTptSrvCb        *serverCb;
#ifdef IPV6_OPTS_SUPPORTED
   CmIpHdrParm       ipHdrParm;           /* IP Header Parameter Holder */
#endif
   EgTLServerCb      *egTLServerCb = NULLP;
   UConnId           spConId;
   U8 eGtpuHdr[EG_LEN_EIGHT];
   U32           tmpRear;
   U32           locFront;

   /***************************
    * Find TEID Control Block *
    ***************************/
   cmHashListFind(&(egCb.egTeidHashListCp),
         (U8*)&(lclTeid),
         sizeof(U32), 0, (PTR *)&(teIdCb));

   if(teIdCb)
   {
      eGtpuHdr[7]  = GTP_FLAG_OPTIONS; /* GTP Flags : GTP  Version rel 99 (1)  and Prtocol type GTP(1)  */
      eGtpuHdr[6]  = GTP_TPDU_TYPE; /*Message  Type T-PDU */
      eGtpuHdr[5]  = (U8)GetHiByte(tPduSize); /* T_PDU Size 2 bytes */ 
      eGtpuHdr[4]  = (U8)GetLoByte(tPduSize);
      eGtpuHdr[3]  = (remTeid >> 24) & 0xff; /* 4 bytes Teid */
      eGtpuHdr[2]  = (remTeid >> 16) & 0xff;
      eGtpuHdr[1]  = (remTeid >> 8) & 0xff;
      eGtpuHdr[0]  = remTeid & 0xff; 
 
      SAddPreMsgMult(&eGtpuHdr[0], 8, mBuf);

      serverCb = teIdCb->tptSrvrCb;
#ifdef IPV6_OPTS_SUPPORTED
      ipHdrParm.type = CM_HDRPARM_NOTPRSNT;
#endif
      spConId = serverCb->spConnId;
      egTLServerCb = &egTLCb.servers[spConId];


      tmpRear = egTLQueueAddOne(egTLServerCb->rear);
      locFront = egTLServerCb->front;

      if(egTLQueueAddOne(egTLQueueAddOne(tmpRear)) == locFront)
      {
         /* Dropping packets */
#if 0
         {
            extern unsigned int gEgtpUlPktDropCount;
            gEgtpUlPktDropCount++;
         }

#endif
         SPutMsg(mBuf);
         RETVALUE(ROK);
         //EgTLSendMsg(TRUE);
      }

      cmMemcpy((U8 *) &egTLServerCb->msgQueue[tmpRear].dstAddr,
            (CONSTANT U8 *) &teIdCb->dstAddrCb->destIpAddr,
            sizeof(CmTptAddr));

      egTLServerCb->msgQueue[tmpRear].mBuf = mBuf;
      egTLServerCb->msgQueue[tmpRear].tos = tos;
      egTLServerCb->msgQueue[tmpRear].flag = TRUE;

#ifdef IPV6_OPTS_SUPPORTED
      cmMemcpy((U8 *)&egTLServerCb->msgQueue[egTLServerCb->qLen].ipHdrParams,
            (CONSTANT U8 *)&ipHdrParm,
            sizeof(CmIpHdrParm));
#endif

      egTLServerCb->rear = tmpRear;
      egTLServerCb->qLen++;
   }
   else
   {
      printf ("egFpTunProcEguDatReq: Failed to get teIdCb\n");
      SPutMsg(mBuf);
   }
   RETVALUE(ret);
}
#endif /* TENB_UL_FP */


