/********************************************************************20**

    Name:   EGTP layer

    Type:   C include file

    Desc:   Structures, variables and typedefs required by EGTP

    File:   eg_socklayer.x

    Sid:      eg_socklayer.x@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_SIB_KS_4UETTI/1 - Fri Jan  8 15:41:28 2016

    Prg:    sn

*********************************************************************21*/

#ifndef __THLYRX__
#define __THLYRX__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @struct MsgQueue
eGTP-U Thin Socket Layer Message Queue Structure.
This is used to store outgoing buffer and it's essential parameters required for
successful transmission of packet over the network. */
typedef struct _egTLmsgQueue
{
   CmTptAddr   dstAddr;          /*!< Destination Address */
   Buffer      *mBuf;            /*!< Message to be sent */
   MsgLen      msglen;           /*!< Message length */
#ifdef IPV6_OPTS_SUPPORTED
   CmIpHdrParm ipHdrParams;      /*!< IP Header Parameter Address */
#endif
   U8          tos;              /* Type of Service param for DSCP */
   Bool        flag;
}EgTLMsgQueue;

/** @struct ServerCb
eGTP-U Thin Scoket Layer Server CB Structure.
This is used to store relevant paramters for a given server helping to
act as independent entity. This houses following entities.
1. Server's Source address used to sent out the packet over the network.
2. Queue to hold out going messages with their relevant information.
3. Current length of the queue.
4. Accquired Scoket File Descriptior.
5. Type of Control Block : Client (Port != 2152)/Server (port == 2152)
6. Type of I/O mode : TRUE (Non-Blocking) / FALSE (Blocking) */
typedef struct _egTLserverCb
{
   CmTptAddr serverAddress;                 /*!< IP Address for Server */
   EgTLMsgQueue msgQueue[MAX_QUEUE_LEN];    /*!< Message Queue for Msg to be sent out */
   EgTLMsgQueue egtpMsgQueue[MAX_QUEUE_LEN];    /*!< Message Queue for Msg to be sent out */
   U32      front;                       /*!< Holds front value for the circular buffer */
   U32      rear;                        /* !< Holds the rear value for circular buffer */
   U32      egtpPktFront;                       /*!< Holds front value for the circular buffer */
   U32      egtpPktRear;                        /* !< Holds the rear value for circular buffer */
   U32      qLen;                           /*!< Queue Len */
   U32      egtpPktQLen;                           /*!< Queue Len */
   U32      srvConId;                       /*!< Server Connection */
   U32      sockFd;                         /*!< Socket File Descriptor  */
#ifdef NTL_LIB    
   U32      sockFdUL;                         /*!< Socket File Descriptor  */
#endif 
   U8       sockType;             /*!< Client/Server Socket */
   Bool     isSocketNonBlocking;            /*!< Blocking/Non-Blocking */
   U32 latestFront;
   U32 latestRear;
}EgTLServerCb;

/** @struct DlPktCntrl
eGTP-U Thin Socket Layer DL Packet Control CB Structure.
1. Maximum number of packets to be read in a time window mentioned in dlTimeWindow. 
   This value will be varied depending on the CPU load and TP to control the CPU.
2. Holds the previous time value (time when last time function called), used for
   calculating number of packets to be read in current call.
3. Total number of packets read/processed till the time. This value is reset once 
   time count dlTimeWindowCnt reaches the dlTimeWindow.
4. Time elapsed till now within the dlTimeWindow. This value is reset once it
   reaches the dlTimeWindow value
5. Time window used for reading the number of packets mentioned in maxNumPacketsToRead
6. totalTime; Time count used for applying the algorithm using CPU info. This is used only if the 
   CPU based load control is used.
*/

typedef struct _egDlPktCntrl
{
   U32   maxNumPacketsToRead;
   U32   oldDlTimeCnt;
   U32   numPacketProcessed;
   U32   dlTimeWindowCnt; 
   U32   dlTimeWindow; 
   U32   totalTime;
}EgDlPktCntrl;

/** @struct UlPktCntrl
eGTP-U Thin Socket Layer UL Packet Control CB Structure.
1. Maximum number of packets to be Sent in a time window mentioned in ulTimeWindow. 
   This value will be varied depending on the CPU load and TP to control the CPU.
2. Holds the previous time value (time when last time function called), used for
   calculating number of packets to be sent in current function call.
3. Total number of packets sent till the time. This value is reset once 
   time count ulTimeWindowCnt reaches the ulTimeWindow.
4. Time elapsed till now within the ulTimeWindow. This value is reset once it
   reaches the ulTimeWindow value
5. Time window used for sending the number of packets mentioned in maxNumPacketsToSend
*/

typedef struct _egUlPktCntrl
{
   U32   maxNumPacketsToSend;
   U32   oldUlTimeCnt;
   U32   numPacketSent;
   U32   ulTimeWindowCnt;
   U32   ulTimeWindow; 
}EgUlPktCntrl;


/** @struct UlQueueCntrl
eGTP-U Thin Socket Layer UL Queue Control CB Structure.
This structure is used for controlling the data-rate (to keep CPU controlled)
when there is no file with CPU info available. It works depending on the 
number of packets present in the UL Queue. Once it reaches the upper Threshold
number of packets to read is decremented and in the same way if we see queue
size less than the lower threshold, it increments the number of packets to
read
1. Number of time length of queue was more than upper threshold.
2. Number of time length of queue was less than lower threshold.
*/
typedef struct _egUlQueueCntrl
{
   U32     queueFullCnt;
   U32     queueNotFullCnt;
}EgUlQueueCntrl;

/** @struct ThCb
eGTP-U Thin Socket Layer Control Structure
This is used to store operational information for the eGTP-U Thin Socket Layer.
These information are common entire Thin layer. Following are the member's it houses.
1. Array of Server's supported.
2. Memory i.e. Region & Pool related information
3. Kernel ePoll File descriptor
4. Max number of message to read per TTI
5. Generic Post structure. */
typedef struct _egTLCb
{
   EgTLServerCb servers[MAX_SERVER_NUM];  /*!< Used to store server specific information */
   CmInetMemInfo memInfo;                 /*!< Memory Information */
   U32  ePollFd;                          /*!< Kernel Epoll File Descriptor */
   U32  maxMsgToread;                     /*!< Max Message to Read per TTI indication */
   Pst  egPst;
#ifdef S1SIMAPP
   EgTimer egtTxRxTmrNode; /**< Open Server Timer control block*/
#endif
   EgUlQueueCntrl egUlQueueCntrl;         /* !< UL Queue control structure */
   EgDlPktCntrl   dlPktCntrl;             /* !< DL packet control structure */
   EgUlPktCntrl   ulPktCntrl;             /* !< UL packet control structure */
   U32            isCpuBasedContrl;       /* !< Value informs if CPU based over load control enabled */
}EgTLCb;

PUBLIC EgTLCb egTLCb;

/** @enum TCbTypehCb
Thin Layer Socket Type enum */
typedef enum _egTLsockType
{
   TH_SERVER = 1,                     /*!< Server Socket */
   TH_CLIENT,                         /*!< Client Socket */
   TH_MAX                             /*!< Max Enum Type */
}EgTLSockType;

typedef struct _packetInfo
{
   U32    numOfPktsRcvd;
   U32    numBytesRcvd;
   U32    numOfPktsSent;
   U32    numBytesSent;
}PacketInfo;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __THLYRX__ */

