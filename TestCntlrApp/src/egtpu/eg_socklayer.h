/********************************************************************20**



        Name:    eGTP-U Thin Socket Layer

        Type:    H source file

        Desc:    Source code for Thin Socket Layer functions such as,

        File:    eg_socklayer.h

        Sid:      eg_socklayer.h@@/main/TeNB_Main_BR/6 - Mon Aug 11 16:42:29 2014

        Prg:     magnihot

*********************************************************************21*/

#ifndef __TH_LYR
#define __TH_LYR

#define MAX_EPOLL_SIZE 12        /* !< Max no of descripitors Kernel ePOll FD can hold */
#define MAX_SERVER_NUM 1        /* !< Max number of Server which can be requested */
/* Change the length of the queue depending on if the CPU based load control is
 * enabled or not
 */
#ifdef ENB_CPU_OVERLOAD_CONTROL
#define MAX_QUEUE_LEN  128        /* !< Max number of packet which can be queued at Thinlayer */
#else
#define MAX_QUEUE_LEN  256         /* !< Max number of packet which can be queued at Thinlayer */
#endif /* ENB_CPU_OVERLOAD_CONTROL */
#define SOCK_ERROR (-1)          /* !< Socket System Call Error value*/
#define NODATA_TO_READ 0         /* !< No event identified for a current ePoll Check */
#ifdef LTE_TDD
#define MAX_MSG_READ_PER_TTI 63  /* !< Max number of packet to read from socket per TTI */
#else
#define MAX_MSG_READ_PER_TTI 64  /* !< Max number of packet to read from socket per TTI */
#endif
#define MAX_ETH_PKT_SIZE   1600  /* !<maximum ethernet packet size */ /*k-work fix */
#ifdef ENB_CPU_OVERLOAD_CONTROL
/* !< Max number of packets to be read from socket in a given window time */
#define EG_MAX_PACKETS_TO_READ_WINDOW  100
/* !< Min number of packets to be read from socket in a given window time */
#define EG_MIN_PACKETS_TO_READ_WINDOW  30
/* !< Max number of packets to be sent from socket in a given window time */
#define EG_MAX_PACKETS_TO_SEND_WINDOW  40
/* !< Time duration after which CPU load is read and cpu reduction logic is 
 * applied
 */
#define EG_CPU_BASED_CORRECTION_TIME   3000
/* !< DL and UL packet reading window size in mili-seconds */
#define EG_DL_PACKET_WINDOW_SIZE       10
#define EG_UL_PACKET_WINDOW_SIZE       10

/* !< Queue length threshold values if the CPU info is not available */
#define EG_UL_QUEUE_MAX_THRESHOLD      90
#define EG_UL_QUEUE_MIN_THRESHOLD      50

/* !< Idle CPU threshold value which will be used as a default value if the 
 * wr_cfg.txt is not has the configuration value.
 */
#define EG_IDLE_CPU_LOWER_THRESHOLD    12
#define EG_IDLE_CPU_UPPER_THRESHOLD    16

/* !< Queue length threshold value hit count if the CPU info is not available 
 * after which increase/decrease of number of packets to be read is applied 
 */
#define EG_UL_QUEUE_FULL_EVENT_CNT      4
#define EG_UL_QUEUE_NOT_FULL_EVENT_CNT 12

/* !< Value to be increased/decreased for number of packets to be read after 
 * threshold values are hit 
 */
#define EG_NO_PKT_INCRMNT_DECRMNT_STEP  2

/* !< Number of times CPU low count is present after which number of packets
 * to be read is increased
 */
#define EG_CPU_LOW_THRSH_VALUE_CNT      3

/* !< Minimum number of packets to be send out when the TLSend is called due
 * to queue full
 */
#define EG_MIN_PACKETS_TO_SEND          5

/* !< File name which holds the CPU usage information */
#define MIPS_FILE "/sys/devices/virtual/mmonitor/mmonitor/mips_stat"

/* !< String length which is used for storing the content of the CPU load
 * information present in the file MIPS_FILE
 */
#define EG_MIPS_STRING_LEN    24
#endif /* ENB_CPU_OVERLOAD_CONTROL */


#ifdef TENB_UL_FP
#define GTP_FLAG_OPTIONS   0x30
#define GTP_TPDU_TYPE      0xFF 
#endif 
/** @details
 * This primitive is used by eGTP-U to send all the queued packet at thin Socket
 * layer. This function is Periodically invoked per TTI and process all the packets,
 * and sends out on the Socket.
 *
 *
 * @return  ROK, RFAILED
 */
EXTERN Void EgTLSendMsg(Bool param);

#ifdef T2K_MEM_LEAK_DBG
EXTERN S16 SAttachPtrToBufNew ARGS((Region region,Pool pool,Data *ptr,MsgLen totalLen,
         Buffer** mBuf,char* file,U32 line));
EXTERN void InsertToT2kMemLeakInfo ARGS((U32 address, U32 size, U32 lineNo, char*
      fileName));
#else
EXTERN PUBLIC S16 SAttachPtrToBuf ARGS((Region region,Pool pool,Data
      *ptr,MsgLen totalLen,Buffer** mBuf));
#endif

/** @details
 * This primitive is used by eGTP-U initialize Thin Socket Layer.
 *
 * @param [in]   region      -  Memory Region to be used by thin layer
 * @param [in]   pool        -  Memory Pool to be used by thin layer
 *
 * @return  ROK, RFAILED
 */
EXTERN void EgTLInitReq(Region region, Pool pool);

/** @details
 * This primitive is used by eGTP-U to indicate reception of Data from Thin Socket Layer.
 * Every TTI, we get an indication to process the messages from socket.
 *
 * @param [in]   timeOut         -  Time to wait for ePoll event to happen.
 * @param [in]   maxEvent        -  Max events to capture from ePOll
 *
 * @return  ROK, RFAILED
 */
EXTERN U32 EgTLReadMsg(U32 timeOut, U32 maxEvent);

#ifdef FLAT_BUFFER_OPT
/** @details
 * This primitive is used by eGTP-U to indicate reception of Data from Thin Socket Layer 
 * when flat buffer feature is enabled.
 * Every TTI, we get an indication to process the messages from socket.
 *
 * @param [in]   timeOut         -  Time to wait for ePoll event to happen.
 * @param [in]   maxEvent        -  Max events to capture from ePOll
 *
 * @return  ROK, RFAILED
 */

EXTERN U32 EgTLReadMsgFB(U32 timeOut, U32 maxEvent);

#endif /* end of FLAT_BUFFER_OPT*/


/** @details
 * This primitive is used by eGTP-U to de-init thin Socket Layer.s
 *
 * @return  ROK, RFAILED
 */
EXTERN void EgTLThShutdownReq(void);
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
*             CM_INET_NO_FLAG - no additional control flag
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
*      File:  cm_inet.c
*
*/

EXTERN S16 egTLSendSockMsg
(
CmInetFd       *sockFd,         /* socket file descriptor */
CmInetAddr     *dstAddr,        /* destination Internet address/port */
CmInetMemInfo  *info,           /* buffer allocation info */
Buffer         *mBuf,           /* buffer structure to send */
MsgLen         *len,            /* number of actually sent octets */
U8              tos
);



/** @details
 * This primitive is used by eGTP-U to open server for Tx/Rx of Data
 *
 * @param [in]   pst         -  Post Structure
 * @param [in]   suId        -  Service user SAP ID
 * @param [in]   spId        -  Service provider SAP ID
 *
 * @return  ROK, RFAILED
 */

EXTERN U32 EgTLBndReq
(
   Pst  *pst,                /* post structure */
   SuId suId,                /* service user SAP ID */
   SpId spId                 /* service provider SAP ID */
);


/** @details
 * This primitive is used by eGTP-U to unbind with eg_socklayer.
 *
 * @param [in]   pst         -  Post Structure
 * @param [in]   spId        -  Service Provider Id
 * @param [in]   reason      -  Reason for unbind Req
 *
 * @return  ROK, RFAILED
 */

EXTERN U32 EgTLUbndReq
(
   Pst    *pst,              /* post structure */
   SpId   spId,              /* service provider SAP ID */
   Reason reason             /* reason */
);


/** @details
 * This primitive is used by eGTP-U to disconnect an Open server.
 *
 * @param [in]   conId       -  Server Connection Id
 *
 * @return  ROK, RFAILED
 */
EXTERN U32 EgTLDiscServerReq
(
   UConnId     conId         /* connection Id */
);


EXTERN S16 EgLiHitBndCfm
(
 Pst   *pst,      /*-- post structure --*/
 SuId  suId,      /*-- service user SAP identifier --*/
 U8    status     /*-- bind status --*/
);


EXTERN S16 EgLiHitConCfm
(
 Pst             *pst,              /*-- post structure --*/
 SuId            suId,              /*-- service user SAP identifier --*/
 UConnId         suConnId,          /*-- service user connection id --*/
 UConnId         spConnId,          /*-- service provider connection id --*/
 CmTptAddr       *localAddr         /*-- local transport address --*/
);


EXTERN S16 EgLiHitUDatInd
(
 Pst            *pst,        /*-- post structure --*/
 SuId           suId,        /*-- service user SAP identifier --*/
 UConnId        suConnId,    /*-- service user server connection ID --*/
 CmTptAddr      *srcAddr,    /*-- transport address --*/
 CmTptAddr      *remAddr,    /*-- transport address --*/
 CmIpHdrParm    *ipHdrParm,
 Buffer         *mBuf        /*-- message buffer --*/
);


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

EXTERN U32 EgTLDatReq
(
UConnId     spConId,       /* service providers connection Id */
CmTptAddr   *remAddr,      /* remote address */
CmTptAddr   *srcAddr,      /* source address */
CmIpHdrParm *hdrParm,      /* header parameters */
Buffer      *mBuf          /* message buffer */
);



/** @details
 * This primitive is used by eGTP-U to open server for Tx/Rx of Data
 *
 * @param [in]   pst         -  Post Structure
 * @param [in]   spId        -  Service Provider Id
 * @param [in]   servConId   -  Server Connection Id
 * @param [in]   servTAddr   -  Server Address
 * @param [in]   tPar        -  Transport Parameters
 * @param [in]   icmpFilter  -  ICMP Filter Parameters
 *
 * @return  ROK, RFAILED
 */
EXTERN U32 EgTLOpenServerReq
(
Pst          *pst,
SpId         spId,                       /* SAP ID */
UConnId      servConId,                  /* Server Connection*/
CmTptAddr    *servTAddr                 /* Address */
);

#endif
