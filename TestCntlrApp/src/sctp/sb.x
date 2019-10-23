

/********************************************************************20**

     Name:     SCTP Layer
                - structures, variables and typedef's

     Type:     C include file

     Desc:     Structures, variables and typedefs required by SCTP

     File:     sb.x

     Sid:      sb.x@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:12 2015

     Prg:      bk, wvdl

*********************************************************************21*/

#ifndef __SBX__
#define __SBX__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/************************************************************************
                    SCTP Layer
************************************************************************/

/* TCB for data in INIT */
typedef struct _SbTcbInit
{
    U32           iTag;
    U32           a_rwnd;
    U16           inStrms;
    SctTSN        iTsn;
    U32           cookieLife;
    U16           peerPort;
    SctNetAddrLst peerAddrLst;
    U32           peerTieTag;
    U8            hstNameLen; 
    U8            peerHstName[SB_MAX_DNAME_LEN];
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
    Bool          ecnFlg; /* ECN Flag */
#endif /* SB_ECN */
} SbTcbInit;


/* TCB for data in INIT-ACK */
typedef struct _SbTcbInitAck
{
    U32           iTag;
    U32           a_rwnd;
    U16           inStrms;
    SctTSN        iTsn;
    U16           localPort;
    SctNetAddrLst localAddrLst;
    U32           localTieTag;
    /*sb087.102: Local host name in the cookie*/
    U8            hstNameLen;
    U8            localHstName[SB_MAX_DNAME_LEN];
} SbTcbInitAck;


/* TCB for COOKIE generation */
typedef struct _SbTcb
{
    SbTcbInit     tcbInit;
    SbTcbInitAck  tcbInitAck;
    U8            key[16];
    U32           privateKey[2];
    U32           sendTime;
    U32           expireTime;
} SbTcb;

/* sb056.102 : moved _SbLocalAddrCb up */

/* Local address Control Block */
typedef struct _SbLocalAddrCb
{
/* sb009.103: SOL10 change,  Added new member hlEnt */
#ifndef SB_SOL10_MULTIPORT
   CmHashListEnt hlEnt;                /* Link into localAddr hash list
                                        * anchored in the global CB       */
#endif
   CmNetAddr     ownAddr;              /* Own net address on which to
                                        * accept and send data            */
/* sb009.103: SOL10 change, Added new member port and spEndpId */
#ifdef SB_SOL10_MULTIPORT
   SctPort       port;                 /* local port no. */

   UConnId       spEndpId;             /* Service Provider endpoint ID */

#endif
   SuId          suId;                 /* ID of TSAP to which this
                                        * address belongs                 */
   UConnId       suConId;              /* Service User Connection Id for
                                        * configured service type         */
   UConnId       spConId;              /* Service Provider Connection Id for
                                        * configured service type         */
   UConnId       suOtherConId;         /* Service User Connection Id for
                                        * non-configured service type     */
   UConnId       spOtherConId;         /* Service Provider Connection Id for
                                        * non-configured service type     */
   Bool          connected;            /* Connection responce receiveded for
                                        * configured service type?        */
   Bool          otherConnected;       /* Connection responce receiveded for
                                        * non-configured service type?    */
   /* sb042.102: Try to reconnect */
   U8            conRetryAttempt;      /* Automatically try to connect if
                                        * it gets disconnect indication   */
} SbLocalAddrCb;


/* Address CB */
typedef struct _SbAddrCb
{
   CmLList        lstEntry;             /* Linked list entry          */
   SpId           spId;                 /* ID of SCT SAP              */
   UConnId        endpId;               /* ID of SCTP Endpoint        */
   UConnId        spAssocId;            /* ID of STCP association     */
   SctWinSize     cwnd;                 /* Congestion Windows Size    */
   SctWinSize     ssthresh;             /* Slow Start Threshold       */
   S32            bytesAcked;           /* Partial bytes acknowledged */
   S32            bytesOut;             /* Bytes outstanding          */
/* sb001.103: congestion window needs to be increased if fully utilized */
   S32            bytesOutSaved;        /* Bytes Out before SACK is received */
   U32            ackCntr;              /* Counter used for cwnd calculation */
   U32            rtxCnt;               /* Retransmission counter     */
   SctRTT         srtt;                 /* Smoothed Round trip time   */
   SctRTT         rttVar;               /* Variation in round trip
                                         * time                       */
   SctRTT         rto;                  /* Retransmission timeout     */
   U16            hBeatInt;             /* Heartbeat interval         */
   Bool           active;               /* State of the address       */
   Bool           confirmed;            /* Probing Status             */
   Bool           sentSince;            /* Has this address been used
                                         * since the last rto         */
   /* sb047: Add the heartbeat Ack flag */
   Bool           hBeatSent;            /* Has HBeat Sent             */
   Bool           hBeatAck;             /* Has HBeat Acked            */
   Bool           idle;                 /* Has this address been used
                                         * since the last heartbeat   */
   Bool           resendInProg;         /* Resend in progress, only send
                                         * one MTU of data            */
   Bool           rttInProg;            /* RTT measurement in progress */
   Bool           sndTo;                /* This address can be used to
                                         * send data to the peer      */
   Bool           rcvFrom;              /* This address can be used to
                                         * receive data from the peer */
/* sb005.103: flag, required to distinguish from probing hbeats */
   Bool           hBeatEnable;          /* HeartBeats enabled/disabled*/
/*  sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
   Bool           ceFlg;                /* CE (Congestion Experienced) Flag 
                                           for the address */
   Bool           ecneFirstSendFlg;     /* First ECNE sent initially/after 
                                           CWR is received */
   Bool           ecneRcvdFlg;          /* ECNE received Flag */
   Bool           ecneFirstRcvdFlg;     /* First ECNE received after congestion 
                                           window reductionFlag */
   Bool           ecnCwndRdced;         /* Flag to keep check on that cwnd
                                           is reducend once per RTT */
   Bool           cwrFlg;               /* CWR send Flag */
   S32            ecnBytesAcked;        /* Bytes Acknowledged: to keep check
                                           on cwnd reduction once per RTT */
   SctTSN         cwrLowestTsn;         /* Lowest TSN received in ECNE */
   SctTSN         ecnLowestTsn;         /* Lowest TSN marked with CE bit */
#endif /* SB_ECN */
   CmTimer        t3rtx;                /* Retransmission Timer       */
   CmTimer        hBeatTmr;             /* Heartbeat Timer            */
   CmNetAddr      addr;                 /* Network Address            */
   SctPort        port;                 /* SCTP port value            */
   U16            nmbRtxChunk;          /* Number of retransmitted chunks */
   /* Performance change - sb023.102 */
   U16            mtuIdx;               /* Index of MtuCb */
  /* sb056.102 :  Modified - moved _SbLocalAddrCb up */
   SbLocalAddrCb  *localConn;
} SbAddrCb;


/* Acknowledgement and Congestion Avoidance FB CB */
typedef struct _SbAcCb
{
   SctTSN         nextLocalTsn;         /* Next TSN to assign to
                                         * outgoing data chunks       */
   SctTSN         cumTsn;               /* Lowest cumulative TSN
                                         * acknowledged               */
   SctTSN         cumPeerTsn;           /* Cummulative Peer TSN that
                                         * arrived from the peer      */
   /* sb020.102: Double SACK problem */
   SctTSN         cumPeerTsnAcked;      /* Last Peer TSN that is send 
                                         * in the SACK                */
   U32            tsnLstSz;             /* Size of the TSN list of data
                                         * that has arrived from the
                                         * peer                       */
   U32            tsnLst[SB_TSN_LST];   /* List of TSNs that have
                                         * arrived from the peer but are
                                         * not equal to the
                                         * currPeerTsn value          */
   Bool           rcvDupTsnFlg;         /* received duplicate TSN flag */
   U32            dupTsnLstSz;          /* size of the duplicate TSN array */
   U32            dupTsnLst[SB_TSN_LST];/* duplicate TSN array */
   SctWinSize     rwnd;                 /* Receiver Window Size       */
   S32            ownRWnd;              /* Current buffer space available */
   U32            rtxCnt;               /* Retransmission counter     */
   U32            sinceSack;            /* Counter of Data chunks
                                         * received since the last SACK
                                         * was sent to the peer       */
#ifdef SB_SWS
   U32            reduction;            /* RFC 4460: difference in advertised 
                                           window */
#endif
   U32        fastRecExtPt;         /* RFC 4460: Fast recovery exit point */
   Bool           fastRecFlg;           /* RFC 4460: If in the Fast Recovery */
   Bool           firstDataRcvd;        /* Indicates whether first DATA chunk
                                         * has been received. Used for
                                         * SACK bundling */
   Bool           zeroWndP;             /* RFC 4460: Zero Window Probing Flag */
/*  sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
   Bool           ecnFlg;                /* Indicates if the ECN for the association gets enabled during INIT/INIT-ACK exchange */
#endif /* SB_ECN */
   U32            zWndPLastTsnRcvd;     /* RFC 4460: last Tsn received during 
                                           zero window probing */
   U32            bytesOut;             /* Bytes outstanding on all
                                         * addresses of this
                                         * association                */
   CmTimer        ackDelayTmr;          /* Delay timer after receiving
                                         * data from a peer, before
                                         * sending a SACK             */
   Bool           pAddrScrnFlg;         /* If screen the peer addresses */
   CmLListCp      addrLst;              /* Linked list of peer
                                         * addresses                  */
   SbAddrCb       *pri;                 /* Primary Address            */
   CmNetAddr      sackAddr;             /* Address to which to send
                                         * SACK to                    */
   CmNetAddr      sackSrcAddr;          /* sb031.103: Address from where the SACK has to send */
} SbAcCb;


/* Sequential Delivery FB CB */
typedef struct _SbSqCb
{
   SctStrmId      nmbOutStreams;        /* Number of outbound streams */
   SctStrmId      nmbInStreams;         /* Number of inbound streams  */
   SctStrmId      *inStreamSeqNum;      /* Expected sequence number
                                         * counter for each inbound
                                         * stream                     */
   SctStrmId      *outStreamSeqNum;     /* Next sequence number counter
                                         * for each outbound stream   */
   /* sb033.103 : Added a new pointer to an array of flags, for recvfrag */
#ifdef SB_FRAG_TSN_CHK
   SctStrmId      *rcvfrag;             /* Expected sequence number*/
#endif
} SbSqCb;


/* Database Module CB */
typedef struct _SbDbCb
{
   CmLListCp      *sequencedQ;          /* Pointer to array of linked
                                         * lists of SbQueuedChunks in
                                         * sequencing queues          */
   CmLListCp      tsnWaitingQOrd;       /* Linked list of SbQueuedChunks
                                         * awaiting TSN assignment that
                                         * require ordered delivery
                                         * within a stream            */
   CmLListCp      tsnWaitingQUnord;     /* Linked list of SbQueuedChunks
                                         * awaiting TSN assignment that
                                         * do not require ordered
                                         * delivery within streams    */
   CmLListCp      assemblyQ;            /* Linked list of SbQueuedChunks
                                         * awaiting outstanding
                                         * segments for reassembly    */
   CmLListCp      congestionQ;          /* Linked list of SbQueuedChunks
                                         * awaiting acknowledgement from
                                         * peer                       */
  /* performance fix */  
  CmLList         *newPkt;              /* Pointer to First New Packet */ 
} SbDbCb;


/* Association Startup and Takedown FB */
typedef struct _SbAsCb
{
   SctNetAddrLst  localAddrLst;         /* Local addresses to send on
                                         * and receive data on        */
   CmTimer        timer;                /* Timer used for retry
                                         * attempts                   */
   /* sb055.102 bundling change */
#ifdef LSB4
   CmTimer        bundleTimer;          /* Timer used for bundling    */ 
#endif
   /* RFC 4460 */
   CmTimer        t5SdownGrdTmr;        /* T5 Shutdown Guard Timer    */

   Buffer         *init;                /* Buffer for INIT chunk      */
   Buffer         *cookie;              /* Buffer for COOKIE chunk    */
   U32            rtxCnt;               /* Number of retransmissions
                                         * of a control chunk         */
} SbAsCb;

/* Queued Chunk data structure */
typedef struct _SbQueuedChunk
{
   CmLList        lstEntry;             /* Entry into the linked list
                                         * used for queueing the data
                                         * chunk in one of the available
                                         * queues                     */
   Bool           noBundleFlg;          /* Indicator of whether this
                                         * data chunk can be bundled
                                         * with other chunks into a
                                         * single datagram or not     */
   Bool           resendFlg;            /* Indicates whether this chunk
                                         * is been resent and should no
                                         * longer be used for path rtt
                                         * and rto calculations       */
   Bool           sendFlg;              /* This chunk still needs to be
                                         * sent to the peer           */
   Bool           startFlg;             /* Indicates the starting
                                         * segment of a segmented data
                                         * chunk                      */
   Bool           endFlg;               /* Indicates the ending segment
                                         * of a segmented data chunk  */
   Bool           dfFlg;                /* Don't Fragment Flag for when
                                         * after segmentation data chunk
                                         * is larger than path MTU
                                         * size                       */
   Bool           unorderedFlg;         /* Indicates to not sequence
                                         * this data chunk            */
   Bool           rttInProg;            /* RTT measurement in progress */
   Bool           fastRtrFlg;           /* RFC 4460: Fast Retransmit only once */
   U8             qState;               /* Indicates the queue that the
                                         * data chunk is currently in.
                                         * Used for queue discovery on
                                         * timeout                    */
   SctTSN         tsn;                  /* Transmission sequence number
                                         * used for acknowledgement and
                                         * retransmission             */
   SctStrmId      seqNum;               /* Sequence number within
                                         * stream                     */
   SctStrmId      stream;               /* Stream number in
                                         * association                */
   U8             holeCnt;              /* Counter of how many times
                                         * this chunk has been reported
                                         * missing by the peer        */
   U16            lifetime;             /* Requested life time of this
                                         * data chunk, as set by service
                                         * user                       */
   U16            time;                 /* Time when message
                                         * was sent, used for path ,rtt
                                         * and rto calculations       */
   SbAddrCb       *addrCb;              /* Address CB of destination
                                         * for quick lookup during
                                         * acknowledgement and retry
                                         * attempts                   */
   CmTimer        lifetimeTmr;          /* Lifetime Timer for when in
                                         * the tsnWaitingQ            */
   UConnId        spAssocId;            /* ID into the association on
                                         * which this data chunk is
                                         * being sent or received     */
   UConnId        endpId;               /* ID into the endpoint to
                                         * which this data chunk is
                                         * received                   */
   U32            protId;               /* Potocol ID used transparently
                                         * by the service user        */
   Buffer         *mBuf;                 /* User/Peer supplied data to be
                                         * sent or delivered
                                         * respectively               */
   /* sb029.102: Duplicate Retransmission */
   Bool           dlvrCfmChunk;          /* Chunk Acked in GAP SACK, which
                                            don't require retransmission,
                                            if set to true */
} SbQueuedChunk;

typedef  struct _sbAsDnsCb
{
   Buffer         *dnsBuf;              /* DNS Query Buffer */
   CmTimer         dnsTmr;              /* Timer used for DNS retry attempt */
   /* sb015.102: DNS timer problem */
   Bool            dnsTmrInit;          /* Whether DNS timer is initialized */
   U16             dnsReqId;            /* Request Id returned by DNS module */
   U8              dnsRtxCnt;           /* Retranmission count for DNS query */ 
} SbAsDnsCb;




/* Association CB */
typedef struct _SbSctAssocCb
{
   SpId           spId;                 /* ID of SCT SAP to which this
                                         * association belongs        */
   UConnId        endpId;               /* ID of SCTP endpoint to which
                                         * this association belongs   */
   UConnId        suAssocId;            /* Association ID on service
                                         * user's side                */
   UConnId        spAssocId;            /* Own association ID         */
   U8             assocState;           /* The state in which the
                                         * association is currently
                                         * in                         */
   Bool           flcFlg;               /* Indicates whether flow
                                         * control is in progress     */
   U32            peerInitTag;          /* Init tag received from peer
                                         * in INIT or INIT_ACK        */
   U32            ownInitTag;           /* Init tag randomly
                                         * generated for INIT or
                                         * INIT_ACK                   */
   /* RFC 4460 --  */
   U32            localTieTag;          /* local tie-tag value        */
   U32            peerTieTag;           /* peer tie-tag value         */
   /* SB_SCTP_3 */
/* sb013.103: Removed SB_CHECKSUM_DUAL flag to make checksumType as compulsory parameter */
   U8             checksumType;         /* checksum used for this assoc */
   SctPort        localPort;            /* Source SCTP Port value     */
   SctPort        peerPort;             /* Destination SCTP Port
                                         * Value                      */
   SbLocalAddrCb  *localConn;           /* Link throught to TSAP on
                                         * which data for this
                                         * association will be sent   */
   /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
   SctTos         tos;                  /* TOS parameter              */
#endif /* SCT3 */
   SbSqCb         sbSqCb;               /* Data used by the Sequential
                                         * Delivery within Streams FB */
   SbAcCb         sbAcCb;               /* Data used by the Acknowledge-
                                         * ment and Congestion Avoidance
                                         * FB                         */
   SbAsCb         sbAsCb;               /* Data used by the Association
                                         * Startup and Takedown FB    */
   SbDbCb         sbDbCb;               /* Data used by the Database
                                         * module                     */
   U8             peerHstName[CM_DNS_DNAME_LEN];  /* Peer hostname */
   SbAsDnsCb      sbDnsCb;              /* Data Used by Association for
                                         * keeping DNS Query Info  */
   Bool           incldHstName;         /* Flag  to include hostname
                                         * in INIT/INITACK message */
  CmNetAddr      localAddr;             /* sb070.102 Multi-Homing 
                                         * changes: Local Address on which received*/
  SbAddrCb       *priOrig;              /* sb075.102: Added for changing the primary*/
#ifdef SB_SUPPORTED_ADDRTYPE
  U16            supAddr;               /* sb017.103: Added supAddr */
#endif /* SB_SUPPORTED_ADDRTYPE */
/*sb033.103 : Added bundleLen variable in this structure to calculate bundleLen per assosiation*/ 
  MsgLen       bundleLen;
} SbSctAssocCb;



/* sb001.12 - Addition : Alignment fix */
typedef struct _SbAssocMapEntry
{
   UConnId     spEndpId;                /* Local endpoint ID          */
   SctPort     port;                    /* SCTP port of peer endpoint */
   CmNetAddr   peerAddr;                /* Net address of peer endpoint */
} SbAssocMapEntry;


/* Association Map Control Block */
typedef struct _SbAssocMapCb
{
   CmHashListEnt hlEnt;                 /* Entry into the hash list   */
   /* sb001.12: Updation - modified for alingnment */
   SbAssocMapEntry sbAssocEntry;        /* Hash list entry for Association */
   SpId          spId;                  /* SCT SAP ID                 */
   UConnId       spAssocId;             /* Association ID             */
} SbAssocMapCb;


/* sb013.103: Removed checksum map structure*/

/* sb046.102: Multiple IP address per Endp. Remove Endpoint Hash List */
typedef struct _SbSctEndpCb
{
   CmHashListEnt hlEnt;                 /* Entry into the hash list   */
   SctNetAddrLst localAddrLst;          /* Source Address List        */
   SctPort       port;                  /* Port number                */
   SpId          spId;                  /* SCT SAP ID                 */
   UConnId       suEndpId;              /* Service user's endpoint ID */
   UConnId       spEndpId;              /* Local endpoint ID          */
/* sb009.103: SOL10 change, Added Endp open wait timer */
#ifdef SB_SOL10_MULTIPORT
   CmTimer       timer;                 /* List of timer control
                                         * blocks                     */
#endif
} SbSctEndpCb;

/* sb046.102: Multiple IP address per Endp */
/* Address/Port Block Entry */
typedef struct _SbAddrPortEntry
{
   CmNetAddr     localAddr;
   SctPort       port;
} SbAddrPortEntry;

/* Address/Port Block */
typedef struct _SbAddrPortCb
{
   CmHashListEnt hlEnt;                 /* Entry into the hash list   */
   SbAddrPortEntry sbAddrPortEntry;     /* Hash list entry */
   UConnId       spEndpId;              /* Local endpoint ID          */
/* sb009.103: SOL10 change, Added pointer to local address CB */
#ifdef SB_SOL10_MULTIPORT
   SbLocalAddrCb  *localAddrCb;         /* pointer to local address CB */
#endif
} SbAddrPortCb;


/* Upper SAP CB*/
typedef struct _SbSctSapCb
{
   SuId          suId;                  /* service user's lower SAP
                                         * ID                         */
   SbSctSapCfg   sctSapCfg;             /* SCT SAP configuration      */
   SbSctSapSts   sctSts;                /* SCT SAP statistics         */
   State         sapState;              /* SCT SAP state              */
   Pst           sctPst;                /* SCTP user post structure   */
   /* sb042.102 - Add - Rolling upgrade changes */
#ifdef SB_RUG
   Bool          remIntfValid;          /* Version number valid ? */
   Ent           verContEnt;            /* version control entity */
#endif
} SbSctSapCb;

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
/* Path Profile CB*/
typedef struct _SbPathProfCb
{
   SbPathProfCfg   pathProfCfg;         /* Path Profile configuration      */
   U32             numDstAddr;          /* Number of associated destination  addresses */
} SbPathProfCb;
typedef struct _sbDstAddrCb   /* Destination Address Configuration */
{
   CmHashListEnt dstEnt;                 /* Entry into the hash list   */
   S16         profId;    /* Profile ID */
   CmNetAddr   dstAddr;   /* Destination Network Address */
} SbDstAddrCb;
#endif /* SB_SATELLITE */


/* sb009.103: SOL10 change, TSAP hash Control Block is addedd */
#ifdef SB_SOL10_MULTIPORT
/* TSAP Hash CB*/
typedef struct _SbTSapHashCb
{
   CmHashListEnt hlEnt;                /* Link into TSAP hash list
                                        * anchored in the global CB       */
   CmNetAddr     ownAddr;              /* Own net address on which to
                                        * accept and send data            */
   SuId          suId;                 /* ID of TSAP to which this
                                        * address belongs                 */
}SbTSapHashCb;
#endif

/* Lower SAP CB*/
typedef struct _SbTSapCb
{
   SbTSapCfg     tSapCfg;               /* TSAP configuration         */
   SbTSapSts     tSts;                  /* TSAP statistics            */
   State         sapState;              /* TSAP state                 */
   CmTimer       timer;                 /* List of timer control
                                         * blocks                     */
   U8            nmbBndRetry;           /* no. of attempts to bind a TSAP */
   Pst           tPst;                  /* Post structure used to
                                         * repsond to TSAP interface
                                         * primitives                 */
   Bool          ipv4_any;              /* IP_ANY lower bind for v4 */
   Bool          ipv6_any;              /* IP_ANY lower bind for v6 */
   /* sb042.102 - Add - Rolling upgrade changes and tcr18 */
#ifdef SB_FTHA
   Ent           contEnt;               /* controlling entity */
#endif /* SB_FTHA */
#ifdef SB_RUG
   Bool          remIntfValid;          /* Version number valid ? */
#endif
} SbTSapCb;

  /* DNS Information  - Destination ~~sb.x~~  */
typedef struct _sbDnsInfo
{
   U8            dnsState;         /* State of DNS server */
   SuId          suId;             /* ID of TSAP to which this
                                    * address belongs                 */
   UConnId       suConId;          /* Service User Connection Id for
                                    * configured service type         */
   UConnId       spConId;          /* Service Provider Connection Id for
                                    * configured service type         */
   CmDnsCb       *dnsCb;           /* DNS Control Block pointer */
} SbDnsInfo;


/* SB Layer Control Block */
typedef struct _SbGlobalCb
{
   TskInit       sbInit;                /* task initialization
                                         * structure                  */
   U32           keyMD5[2];             /* Private MD5 hash key       */
   U32           oldKeyMD5[2];          /* Previous MD5 hash key      */
   SbGenCfg      genCfg;                /* General configuration      */
   SbSctSapCb    **sctSaps;             /* list of SCT layer SAPs     */
   SbTSapCb      **tSaps;               /* list of transport SAPs     */
   SbSctAssocCb  **assocCb;             /* Association array list     */
   SbSctEndpCb   **endpCb;              /* Pointer to array of end
                                         * points                     */
   /* sb046.102: Multiple IP address per Endp */
   SbAddrPortCb  **addrPortCb;          /* Pointer to array of addr
                                         * port number control blocks */
   SbLocalAddrCb **localAddrCb;         /* Pointer to array of local
                                         * address control blocks     */
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   SbPathProfCb  **pathProfs;           /* Pointer to array of path
                                           profiles */
#endif /* SB_SATELLITE */
   CmTqCp        sbTqCp;                /* timing queue control point */
   CmTqType      sbTq[SB_TQSIZE];        /* timing queue               */
   CmTimer       keyTmr;                /* New Key Timer              */
   SbGenSts      genSts;                /* SCTP general statistics    */
   SbGenSta      genSta;                /* layer status               */
   CmHashListCp  endpHl;                /* Hash list of active
                                         * endpoints                  */
   /* sb046.102: Multiple IP address per Endp */
   CmHashListCp  addrPortHl;            /* Hash list of own addr and
                                         * port number */
/* sb009.103: SOL10 change, Local Address hash list is added */
#ifndef SB_SOL10_MULTIPORT
   CmHashListCp  localAddrHl;           /* Hash list of own
                                         * addresses                  */
#endif
   CmHashListCp  assocMapHl;            /* Hash list of peer endpoints
                                         * and local address and port
                                         * pairs that map to an
                                         * association                */
/* sb009.103: SOL10 change, TSAP hash list is added */
#ifdef SB_SOL10_MULTIPORT
   CmHashListCp  tsapHl;                /* Hash list of TSAPs */
#endif
/* sb013.103: Removed checksumMapHl */
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   CmHashListCp  dstAddrHl;             /* Hash list of destination addresses */
#endif /* SB_SATELLITE */
   SbMgmt        sbMgmt;                /* Management structure used for
                                         * delayed responses to the
                                         * layer manager              */
   Pst           cfmPst;                /* Post structure used for delayed
                                         * confirms to the layer manager */
   SbMtuCp       mtuCp;                 /* Path MTU Discovery Control Point */
   CmTimer       mtuIncTmr;             /* Timer used to increment the mtu */
   CmTimer       mtuIncTmrUp;           /* Timer to increment max mtu size */
   U32           txChunks;              /* Number of chunks requiring
                                         * transmission               */
   U32           rxChunks;              /* Number of Chunks requiring
                                         * delivery                   */
   SbDnsInfo     dnsInfo;               /* Structure used for storing DNS
                                         * information */
   SctNetAddrLst ownHstAddrLst;         /* IP Address list corrosponding to
                                         * Own HostName */
#ifdef SS_MULTIPLE_PROCS
   U8            used;                  /* Control block usage */
#endif  /* SS_MULTIPLE_PROCS */

   /* sb042.102 - Add - Rolling upgrade changes */
#ifdef SB_RUG
   U16           numIntfInfo;           /* Number of store intf ver info */
   ShtVerInfo    *intfInfo;             /* Interface version info store */
#endif

/*sb007.103: random number array, Performance enhancement*/
   U16 randomNumArray[MAX_RANDOM_ARRAY];
   U16 randIncr;
/* sb012.103: Added function pointer for gethostbyname */
   S16 (*funcGetHostByName)(S8*, CmInetIpAddrTbl*);
}SbGlobalCb;

#ifdef SS_MULTIPLE_PROCS
EXTERN SbGlobalCb sbGlobalCbLst[SB_MAX_INSTANCES];
EXTERN SbGlobalCb *sbGlobalCbPtr;
#else
EXTERN SbGlobalCb sbGlobalCb;
#endif  /* SS_MULTIPLE_PROCS */



/* sb072.102 MOVED  sbActvTsk TO lsb.x */

EXTERN S16 sbGetSid  ARGS((SystemId *sid));


/* sb072.102 MOVED  sbActvInit TO lsb.x */

EXTERN S16  sbInitExt       ARGS((Void));


#ifdef SS_MULTIPLE_PROCS
EXTERN S16  sbActvTmr       ARGS((ProcId proc, Ent ent, Inst inst));
#else
EXTERN S16  sbActvTmr       ARGS((Void));
#endif /* SS_MULTIPLE_PROCS */

EXTERN S16  sbTmrEvnt       ARGS((PTR cb,
                                  S16 evnt));


/* sb_bdy2.c functions */
EXTERN S16           sbSqInSendUp      ARGS((SbSctAssocCb *assocCb,
                                             SbQueuedChunk *chunk,
                                             U8 type));

EXTERN S16           sbSqDeliver       ARGS((SbSctAssocCb     *assocCb,
                                             SbQueuedChunk    *chunk));

EXTERN S16           sbSqRtrvUnsent    ARGS((SbSctAssocCb     *assocCb));

EXTERN S16           sbSqRtrvUndel     ARGS((SbSctAssocCb     *assocCb));

EXTERN S16           sbSqArrive        ARGS((SbSctAssocCb     *assocCb,
                                             SbQueuedChunk    *chunk));

EXTERN S16           sbSqLifetimeTO    ARGS((SbQueuedChunk    *chunk));

EXTERN SbQueuedChunk *sbDbGetFirst     ARGS((SbSctAssocCb     *assocCb,
                                             U8                qType));

EXTERN S16           sbDbDelAll        ARGS((SbSctAssocCb     *assocCb,
                                             U8                qType));

EXTERN S16           sbDbInsert        ARGS((SbSctAssocCb     *assocCb,
                                             SbQueuedChunk    *chunk,
                                             U8                qType));

EXTERN S16           sbDbQSize         ARGS((SbSctAssocCb     *assocCb,
                                             U32              *staticMem,
                                             U32              *msgMem,
                                             U8               qType));

EXTERN U32           sbDbQPackets      ARGS((SbSctAssocCb     *assocCb,
                                             U8                qType));

EXTERN S16           sbDbListSize      ARGS((CmLListCp     *l,
                                             U32           *staticMem,
                                             U32           *msgMem));

EXTERN SbQueuedChunk *sbDbAssembled    ARGS((SbSctAssocCb     *assocCb));

EXTERN SbQueuedChunk *sbDbOrdered      ARGS((SbSctAssocCb     *assocCb,
                                             SctStrmId         stream,
                                             SctStrmId         seqNum));

EXTERN SbQueuedChunk *sbDbGetChunk     ARGS((SbSctAssocCb     *assocCb,
                                             SbQueuedChunk    *chunk));

EXTERN S16           sbSgSegment       ARGS((SbSctAssocCb     *assocCb));
EXTERN S16           sbSgAssemble      ARGS((SbSctAssocCb     *assocCb,
                                             SbQueuedChunk    *chunk));

/* sb060.102 - TOS enhancement */
#ifdef SCT4
EXTERN S16           sbVaDatInd        ARGS((CmNetAddr        *srcAddr,
                                             CmNetAddr        *dstAddr,
                                             UConnId           suConId,
                                             Buffer           *mBuf,
                                             U8                tos));
#else
EXTERN S16           sbVaDatInd        ARGS((CmNetAddr        *srcAddr,
                                             CmNetAddr        *dstAddr,
                                             UConnId           suConId,
                                             Buffer           *mBuf));
#endif /* SCT4 */

EXTERN CmNetAddr     *sbPmGetBestAddr  ARGS((SbSctAssocCb     *assocCb,
                                             CmNetAddr        *addr));

EXTERN SbAddrCb      *sbPmGetBestAddrCb ARGS((SbSctAssocCb    *assocCb,
                                              CmNetAddr       *addr));

EXTERN Void sbPmHBeatEnb            ARGS((SbAddrCb      *addrCb,
                                          U16            intervalTime));

EXTERN Void sbPmHBeatDis            ARGS((SbAddrCb      *addrCb));

EXTERN S16 sbPmHBeatTO              ARGS((SbAddrCb      *addrCb));

/* sb070.102 - Multi-Homing changes and Local interface failure */
EXTERN S16 sbPmNeedResend           ARGS((SbSctAssocCb  *assocCb,
                                          SbAddrCb      *addrCb,
                                          U8            *result));

EXTERN S16 sbPmSendHBeat            ARGS((SbSctAssocCb  *assocCb,
                                          SbAddrCb      *addrCb));

/* RFC 4460 section 2.36: Path Initialization*/
EXTERN Void sbPmProbe            ARGS((SbSctAssocCb  *assocCb));

EXTERN S16 sbPmRcvHBeatAck          ARGS((SbSctAssocCb  *assocCb,
                                          Buffer        *mBuf,
                                          CmNetAddr     *localAddr));

EXTERN S16 sbPmCalcRto              ARGS((SbSctAssocCb  *assocCb,
                                          SbAddrCb      *addrCb,
                                          SctRTT        newRtt));
/* sb070.102 multi-home changes */
EXTERN S16 sbPmRcvHBeat             ARGS((SbSctAssocCb  *assocCb,
                                          CmNetAddr     *src,
                                          MsgLen         msgLen,
                                          Buffer        *mBuf,
                                          CmNetAddr     *localAddr));

EXTERN Void sbPmRcvSack             ARGS((SbSctAssocCb  *assocCb,
                                          SbQueuedChunk *chunk));

EXTERN SbAddrCb *sbPmAddAddr        ARGS((SbSctSapCb    *sctSap,
                                          SbSctAssocCb  *assocCb,
                                          CmNetAddr       *addr));
/* sb009.103: IPV4IP6 changes, addedd new function sbPmMakePaths */
#ifdef SB_IPV4IPV6_COMBINED
EXTERN Void sbPmMakePaths           ARGS((SbSctAssocCb *assocCb));
#endif

EXTERN SbAddrCb *sbPmAddPathCb      ARGS((SbSctAssocCb   *assocCb,
                                          CmNetAddr      *srcAddr,
                                          SbAddrCb       *destAddr));

EXTERN SbAddrCb *sbPmGetPathCb      ARGS((SbSctAssocCb   *assocCb,
                                          CmNetAddr      *address,
                                          CmNetAddr      *destAddr));

EXTERN S16 sbPmSelNextAddr          ARGS((SbSctAssocCb  *assocCb,
                                          SbQueuedChunk *chunk));

EXTERN S16 sbPmCompNAddr            ARGS((CmNetAddr     *addr1,
                                          CmNetAddr     *addr2));

EXTERN SbAddrCb *sbPmGetAddrCb      ARGS((SbSctAssocCb  *assocCb,
                                          CmNetAddr     *address));
/*sb031.103: added the new function defination */
EXTERN SbAddrCb *sbPmGetSackAddrCb  ARGS((SbSctAssocCb  *assocCb,
                                          CmNetAddr     *dstaddress,
                                          CmNetAddr     *srcaddress));
     /* performance fix */
EXTERN S16 sbCmChunkMux             ARGS((SbSctAssocCb    *assocCb,
                                          SbQueuedChunk   *chunk,
                                          CmLList         *crntEntry));

EXTERN S16 sbCmMakeMsg              ARGS((SbQueuedChunk   *chunk,
                                           Buffer         **mBuf));
     /* sb060.102 - TOS enhancement */
#ifdef SCT4
EXTERN S16 sbCmDemux                ARGS((CmNetAddr       *localAddr,
                                          CmNetAddr       *peerAddr,
                                          U16              localPort,
                                          U16              peerPort,
                                          U32              vTag,
                                          UConnId          suConId,
                                          Buffer          *mBuf,
                                          U8               tos,
                                          U8               checksumType));
#else
EXTERN S16 sbCmDemux                ARGS((CmNetAddr       *localAddr,
                                          CmNetAddr       *peerAddr,
                                          U16              localPort,
                                          U16              peerPort,
                                          U32              vTag,
                                          UConnId          suConId,
                                          Buffer          *mBuf,
                                          U8               checksumType));
#endif /* SCT4 */

EXTERN S16 sbCmValChunk             ARGS((SbSctAssocCb    *assocCb,
                                          U32              vTag,
                                          U8               chunkId,
                                          UConnId          suConId,
                                          U8               chunkFlags));
/*sb071.102 Fix for segv error */
EXTERN S16 sbCmMakeChunk            ARGS((SbSctAssocCb    **tmpAssocCb,
                                          U8               flags,
                                          Buffer          *mBuf,
                                          SbQueuedChunk   *chunk));

EXTERN S16 sbCmResolveChunk         ARGS((SctPort          localPort,
                                          CmNetAddr       *localAddr,
                                          SctPort          peerPort,
                                          CmNetAddr       *peerAddr,
                                          SbSctEndpCb    **endpCbPtr,
                                          SbSctAssocCb   **assocCbPtr,
                                          U8             checksumType));

/* sb012.103 : New function added to check unicast address */
EXTERN S16 sbCmUnicastChk	    ARGS((CmNetAddr	  *peerAddr));
/* sb028.103: Added a function to process the data chunk received with cookie */
EXTERN S16 sbAcRcvDatWitCookie      ARGS((SbSctAssocCb      *assocCb,
                                          SbQueuedChunk     *chunk,
                                          U8                chunkFlags,
                                          Buffer            *chunkBuf,
                                          CmNetAddr         *peerAddr));

/* sb_bdy3.c functions */
EXTERN S16 sbAcRtrvUnack            ARGS((SbSctAssocCb  *assocCb));

EXTERN S16  sbAcSackTO              ARGS((SbSctAssocCb  *assocCb));

EXTERN S16 sbAcSendData      ARGS((SbSctAssocCb     *assocCb,
                                   SbQueuedChunk    *chunk));

EXTERN S16 sbAcRcvSack              ARGS((SbSctAssocCb  *assocCb,
                                          Buffer        *sackBuf));

EXTERN Void sbAcAckChunk            ARGS((SbSctAssocCb  *assocCb,
                                          SbQueuedChunk *chunk,
                                          Bool           cumTsnAdv));

EXTERN Void sbAcFastRetransmit      ARGS((SbSctAssocCb  *assocCb,
                                          SbQueuedChunk *chunk));

EXTERN Bool sbAcSpace               ARGS((SbSctAssocCb  *assocCb,
                                          SbQueuedChunk *chunk));

EXTERN S16 sbAcSendSack             ARGS((SbSctAssocCb  *assocCb));

/* RFC 4460 section 2.15: receiver's sws avoidance */
EXTERN S16 sbAcBuildSack            ARGS((SbSctAssocCb  *assocCb,
                                          MsgLen         bufSize,
                                          Buffer        *sackBuf,
                 U16            mtu));

EXTERN S16 sbAcRcvData              ARGS((SbSctAssocCb  *assocCb,
                                          SbQueuedChunk *chunk));

EXTERN S16 sbAcInsDupTsn            ARGS((SbSctAssocCb  *assocCb,
                                          SctTSN         dupTsn));

EXTERN S16 sbAcInsTsn               ARGS((SbSctAssocCb  *assocCb,
                                          SctTSN         rcvTsn));

EXTERN S16 sbAcRenegChunk           ARGS((SbSctAssocCb  *assocCb,
                                          SbQueuedChunk   *chunk));

EXTERN S16 sbAcReneg                ARGS((SbSctAssocCb  *assocCb));

EXTERN S16 sbAcEmptyCongQ           ARGS((SbSctAssocCb  *assocCb));

EXTERN SbQueuedChunk *sbAcFndLowChunkOnDta ARGS((SbSctAssocCb  *assocCb,
                                                 SbAddrCb      *addrCb));

EXTERN SbQueuedChunk *sbAcFndLowRtxChunkOnDta ARGS((SbSctAssocCb  *assocCb,
                                                    SbAddrCb      *addrCb));

EXTERN S16 sbAcRTO                  ARGS((SbAddrCb      *addrCb));

EXTERN S16 sbAsSendInit             ARGS((SbSctAssocCb  *assocCb,
                                          U32            cookiePreserve,
                                          U16            supAddrs));

EXTERN S16 sbAsBuildInitAck         ARGS((SpId               spId,
                                          SctAssocIndParams *assocIndParams,
                                          SbTcb             *tcb,
                                          Buffer            *mBuf,
                                          Buffer            *unBuf));

EXTERN S16  sbAsFindAssoc           ARGS((Buffer        *initAck,
                                          SbSctAssocCb  **ppAssocCb,
                                          UConnId       endpId,
                                          U16           peerPort));

   /* sb021.102: Modification for TOS parameter */
  /* sb013.103: Dual Checksum Fix */
#ifdef SCT3
EXTERN S16 sbAsSendInitAck          ARGS((SpId               spId,
                                          SctAssocIndParams *assocIndParams,
                                          SbTcb             *tcb,
                                          SbLocalAddrCb     *localAddrCb,
                                          SctTos             tos,
                                          U8                 checksumType,
                                          Buffer            *unBuf));
#else
EXTERN S16 sbAsSendInitAck          ARGS((SpId               spId,
                                          SctAssocIndParams *assocIndParams,
                                          SbTcb             *tcb,
                                          SbLocalAddrCb     *localAddrCb,
                                          U8                 checksumType,
                                          Buffer            *unBuf));
#endif /* SCT3 */

   /* sb021.102: Modification for TOS parameter */
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
EXTERN S16 sbAsSendAbort            ARGS((U32              vTag,
                                          SbLocalAddrCb   *localAddrCb,
                                          CmNetAddr       *dstAddr,
                                          SctPort          localPort,
                                          SctPort          peerPort,
                                          Bool             tBit,
                                          SctTos           tos,
                                          U8               checksumType));
#else
EXTERN S16 sbAsSendAbort            ARGS((U32              vTag,
                                          SbLocalAddrCb   *localAddrCb,
                                          CmNetAddr       *dstAddr,
                                          SctPort          localPort,
                                          SctPort          peerPort,
                                          Bool             tBit,
                                          U8               checksumType));
#endif /* SCT3 */

EXTERN S16 sbAsAbortAssoc           ARGS((SbSctAssocCb    *assocCb,
                                          Bool             sendPeer));
/* SB_SCTP_3 */
/* sb013.103: Dual Checksum Fix */
EXTERN S16 sbAsAddHead              ARGS((CmNetAddr       *srcAddr,
                                          CmNetAddr       *dstAddr,
                                          SctPort          srcPort,
                                          SctPort          dstPort,
                                          U32              vTag,
                                          U8               checksumType,
                                          Buffer          *mBuf));

EXTERN S16 sbAsShutdown             ARGS((SbSctAssocCb    *assocCb));

EXTERN S16 sbAsSendShutdown         ARGS((SbSctAssocCb    *assocCb));

EXTERN S16 sbAsRcvShutDownAck       ARGS((SbSctAssocCb    *assocCb));

   /* sb060.102 - TOS enhancement */
 /* sb013.103: Added new parameter checksumType */
#ifdef SCT4
EXTERN S16 sbAsRcvCookie            ARGS((SbSctEndpCb     *endpCb,
                                          CmNetAddr       *peerAddr,
                                          SctPort          peerPort,
                                          Buffer          *mBuf,
                                          U32              vTag,
                                          U8               tos,
                                          CmNetAddr       *localAddr,
                                          U8               checksumType));
#else
EXTERN S16 sbAsRcvCookie            ARGS((SbSctEndpCb     *endpCb,
                                          CmNetAddr       *peerAddr,
                                          SctPort          peerPort,
                                          Buffer          *mBuf,
                                          U32              vTag,
                                          CmNetAddr       *localAddr,
                                          U8               checksumType));
#endif /* SCT4 */
/* sb013.103: Dual Checksum Fix */
EXTERN S16 sbAsHandleStaleCookie    ARGS((U32              ct,
                                          SbTcb           *tcb,
                                          U32              vTag,
                                          CmNetAddr       *src,
                                          CmNetAddr       *dst,
                                          SctPort          localPort,
                                          SctPort          peerPort,
                                          U8               checksumType));
/* sb013.103: Dual Checksum Fix */
EXTERN S16 sbAsSendErrorStale       ARGS((U32              vTag,
                                          CmNetAddr       *src,
                                          CmNetAddr       *dst,
                                          SctPort          localPort,
                                          SctPort          peerPort,
                                          U32              stale,
                                          U8               checksumType));
/* sb013.103: Dual Checksum Fix */
EXTERN S16 sbAsSendErrorStrm        ARGS((U32              vTag,
                                          CmNetAddr       *src,
                                          CmNetAddr       *dst,
                                          SctPort          localPort,
                                          SctPort          peerPort,
                                          U16              stream,
                                          U8               checksumType));

/*sb077.102 : Sending unrecognized TLV parameter in the Error Chunk if the highest*
  * order 2 bits of the parameter type is set to 01 */
/* sb013.103: Dual Checksum Fix */
EXTERN S16 sbAsSendErrorUnrecogPar ARGS((U32              vTag,
                                          CmNetAddr       *src,
                                          CmNetAddr       *dst,
                                          SctPort          localPort,
                                          SctPort          peerPort,
                                          Buffer          *unBuf,
                                          U16              parSize,
                                          Bool             unrecogFlag,
                                          U8               checksumType));

/*sb078.102: Sending Abort message with error cause Restart of an Association with New Addresses*/
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
EXTERN S16 sbAsSendAbortNewAddr        ARGS((U32              vTag,
                                          SbLocalAddrCb *localAddrCb,
                                          CmNetAddr       *dst,
                                          SctPort          localPort,
                                          SctPort          peerPort,
                                          CmNetAddr       *newAddr,
                                          Bool             tBit,
                                          SctTos           tos,
                                          U8               checksumType)); 
#else
EXTERN S16 sbAsSendAbortNewAddr        ARGS((U32              vTag,
                                          SbLocalAddrCb *localAddrCb,
                                          CmNetAddr       *dst,
                                          SctPort          localPort,
                                          SctPort          peerPort,
                                          CmNetAddr       *newAddr,
                                          Bool             tBit,
                                          U8               checksumType)); 
#endif

/* RFC 4460 */
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
EXTERN S16 sbAsSendUserAbort           ARGS (( U32             vTag,    
                                               SbLocalAddrCb   *localAddrCb,
                                               CmNetAddr       *dst,     
                                               SctPort         localPort,
                                               SctPort         peerPort,
                                               U32             reason,
                                               Bool            tBit,
                                               SctTos          tos,
                                               U8              checksumType));
#else
EXTERN S16 sbAsSendUserAbort           ARGS (( U32             vTag,    
                                               SbLocalAddrCb   *localAddrCb,
                                               CmNetAddr       *dst,     
                                               SctPort         localPort,
                                               SctPort         peerPort,
                                               U32             reason,
                                               Bool            tBit,
                                               U8              checksumType));
#endif /* SCT3 */

   /* sb021.102: Modification for TOS parameter */
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
EXTERN S16 sbAsSendAbortErrMissCookie  ARGS((U32           vTag,
                                             SbLocalAddrCb *localAddrCb,
                                             CmNetAddr     *dst,
                                             SctPort       localPort,
                                             SctPort       peerPort,
                                             SctTos        tos,
                                             U8            checksumType));
#else
EXTERN S16 sbAsSendAbortErrMissCookie  ARGS((U32           vTag,
                                             SbLocalAddrCb *localAddrCb,
                                             CmNetAddr     *dst,
                                             SctPort       localPort,
                                             SctPort       peerPort,
                                             U8            checksumType));
#endif /* SCT3 */

   /* sb021.102: Modification for TOS parameter */
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
EXTERN S16 sbAsSendAbortRes         ARGS((U32              vTag,
                                          SbLocalAddrCb   *localAddrCb,
                                          CmNetAddr       *dst,
                                          SctPort          localPort,
                                          SctPort          peerPort,
                                          Bool             tBit,
                                          SctTos           tos,
                                          U8               checksumType));
#else
EXTERN S16 sbAsSendAbortRes         ARGS((U32              vTag,
                                          SbLocalAddrCb   *localAddrCb,
                                          CmNetAddr       *dst,
                                          SctPort          localPort,
                                          SctPort          peerPort,
                                          Bool             tBit,
                                          U8               checksumType));
#endif /* SCT3 */

   /* sb021.102: Modification for TOS parameter */
  /* sb013.103: Dual Checksum Fix */
#ifdef SCT3
EXTERN S16 sbAsSendAbortStrm        ARGS((U32              vTag,
                                          SbLocalAddrCb   *localAddrCb,
                                          CmNetAddr       *dst,
                                          SctPort          localPort,
                                          SctPort          peerPort,
                                          SctStrmId        stream,
                                          Bool             tBit,
                                          SctTos           tos,
                                          U8               checksumType));
#else
EXTERN S16 sbAsSendAbortStrm        ARGS((U32              vTag,
                                          SbLocalAddrCb   *localAddrCb,
                                          CmNetAddr       *dst,
                                          SctPort          localPort,
                                          SctPort          peerPort,
                                          SctStrmId        stream,
                                          Bool             tBit,
                                          U8               checksumType));
#endif /* SCT3 */

EXTERN S16 sbAsSendCookieAck        ARGS((SbSctAssocCb    *assocCb,
                                          CmNetAddr       *peerAddr));
   /* sb060.102 - TOS enhancement */
  /* sb013.103: Added new parameter checksumType */ 
#ifdef SCT4
EXTERN S16 sbAsRcvInit              ARGS((SbSctEndpCb     *endpCb,
                                          CmNetAddr       *peerAddr,
                                          SctPort          peerPort,
                                          MsgLen           msgLen,
                                          Buffer          *mBuf,
                                          U8              tos,
                                          CmNetAddr       *localAddr,
                                          U8               checksumType));
#else
EXTERN S16 sbAsRcvInit              ARGS((SbSctEndpCb     *endpCb,
                                          CmNetAddr       *peerAddr,
                                          SctPort          peerPort,
                                          MsgLen           msgLen,
                                          Buffer          *mBuf,
                                          CmNetAddr       *localAddr,
                                          U8               checksumType));
                     
#endif /* SCT4 */

/*sb070.102 - Multi-Homing changes */
EXTERN S16 sbAsRcvInitAck           ARGS((SbSctAssocCb    *assocCb,
                                          CmNetAddr       *addr,
                                          MsgLen           msgSize,
                                          Buffer          *mBuf,
                                          CmNetAddr       *locAddr));

/*sb070.102 - Multi-Homing changes */
EXTERN S16 sbAsSendCookie           ARGS((SbSctAssocCb    *assocCb,
                                          CmNetAddr       *peerAddr,
                                          Buffer          *cookieBuf,
                                          Buffer          *unrecogParBuf,
                                          CmNetAddr       *locAddr));

EXTERN S16 sbAsRcvError             ARGS((SbSctAssocCb    *assocCb,
                                          MsgLen           msgLen,
                                          Buffer          *mBuf));

EXTERN Void sbAsRcvErrorStream      ARGS((SbSctAssocCb    *assocCb,
                                          SctStrmId        stream));

EXTERN Void sbAsRcvErrorParam       ARGS((SbSctAssocCb    *assocCb,
                                          U32              numParams,
                                          Buffer          *mBuf));

EXTERN S16 sbAsRcvErrorStale        ARGS((SbSctAssocCb    *assocCb,
                                          U32              stale));

EXTERN Void sbAsRcvErrorRes         ARGS((SbSctAssocCb    *assocCb));

EXTERN S16 sbAsRcvAbort             ARGS((SbSctAssocCb    *assocCb,
                                          MsgLen           msgLen,
                                          Buffer          *mBuf));

EXTERN S16 sbAsRcvShutdown          ARGS((SbSctAssocCb    *assocCb,
                                          MsgLen           msgLen,
                                          Buffer          *mBuf,
                                          SbLocalAddrCb *localConn,
                                          CmNetAddr       *peerAddr));

   /* sb021.102: Modification for TOS parameter */
/* sb010.103: assocCb argument added in the sbAsSendSdownAck() function signature */
#ifdef SCT3
EXTERN S16 sbAsSendSdownAck         ARGS((SbSctAssocCb    *assocCb,
                                          SctPort          localPort,
                                          SctPort          peerPort,
                                          CmNetAddr       *peerAddr,
                                          SbLocalAddrCb   *localConn,
                                          U32              vTag, 
                                          Bool             opErrFlg,
                                          SctTos           tos));
#else
EXTERN S16 sbAsSendSdownAck         ARGS((SbSctAssocCb    *assocCb,
                                          SctPort          localPort,
                                          SctPort          peerPort,
                                          CmNetAddr       *peerAddr,
                                          SbLocalAddrCb   *localConn,
                                          U32              vTag, 
                                          Bool             opErrFlg));
#endif /* SCT3 */


EXTERN S16 sbAsClearAssoc           ARGS((SbSctAssocCb  *assocCb));

EXTERN Void sbAsRcvCookieAck        ARGS((SbSctAssocCb    *assocCb));

EXTERN SctPort sbAsChoosePort       ARGS((CmNetAddr      *localAddr));

EXTERN S16 sbAsSDownTO              ARGS((SbSctAssocCb  *assocCb));

EXTERN S16 sbAsInitTO               ARGS((SbSctAssocCb  *assocCb));

EXTERN S16 sbAsCookieTO             ARGS((SbSctAssocCb  *assocCb));

EXTERN S16 sbAsFreezeTO             ARGS((SbSctAssocCb  *assocCb));

/* sb054.102 : Addition - Bundling Changes */
#ifdef LSB4
EXTERN S16 sbAsBundleTO             ARGS((SbSctAssocCb  *assocCb));
#endif

/* RFC 4460 */
EXTERN S16 sbAsSdownGuardTO         ARGS((SbSctAssocCb  *assocCb));

EXTERN S16 sbAsKeyTO                ARGS((Void));


EXTERN S16 sbSndRslvReqToDns        ARGS (( Ptr         txFuncParam, 
                                            CmTptAddr   *remoteAddr, 
                                            Buffer      *mBuf  ));

EXTERN S16 sbSendDnsRslvReq         ARGS (( SbSctAssocCb       *assocCb, 
                                            U8                 *hostName ));

EXTERN S16 sbRcvDnsResponse         ARGS (( Ptr                usrEntry,   
                                            CmDnsResponse      *dnsRsp  ));

EXTERN S16 sbInitDnsCb              ARGS (( CmDnsCb            *dnsCb,
                                            U16                reqIdLstSz,
                                            Mem                *sMem,
                                            CmTptAddr          *dnsTptAddr ));

EXTERN S16 sbRslvdAddrLst           ARGS (( SbSctAssocCb       *assocCb,
                                            SctNetAddrLst      *sctAddrLst ));

EXTERN S16 sbRslvOwnHstName         ARGS (( Void ));

EXTERN S16 sbOpenDnsServer          ARGS ((SbTSapCb       *tSap ));

   /* sb021.102: Modification for TOS parameter */
  /*  sb013.103: Dual Checksum Fix */
#ifdef SCT3
EXTERN S16 sbAsSendAbortUnrslvAddr  ARGS (( U32              vTag, 
                                            SbLocalAddrCb   *localAddrCb,  
                                            CmNetAddr       *dst,
                                            SctPort          localPort,
                                            SctPort          peerPort,  
                                            Bool             tBit,  
                                            U8              *peerHstName,
                                            SctTos           tos,
                                            U8               checksumType));
#else
EXTERN S16 sbAsSendAbortUnrslvAddr  ARGS (( U32              vTag, 
                                            SbLocalAddrCb   *localAddrCb,  
                                            CmNetAddr       *dst,
                                            SctPort          localPort,
                                            SctPort          peerPort,  
                                            Bool             tBit,  
                                            U8              *peerHstName,
                                            U8               checksumType));
#endif /* SCT3 */

EXTERN S16 sbAsDnsRspTO              ARGS ((SbSctAssocCb  *assocCb));


EXTERN S16 sbAsPrepareCookie         ARGS (( SbSctAssocCb    *assocCb, 
                                             Buffer          *cookieBuf,
                                             Buffer          *unrecogParBuf));

   /* sb021.102: Modification for TOS parameter */
  /*  sb013.103: Dual Checksum Fix */
#ifdef SCT3
EXTERN S16 sbAsSendAbortNoData       ARGS (( U32              vTag, 
                                             SbLocalAddrCb   *localAddrCb, 
                                             CmNetAddr       *dst,  
                                             SctPort          localPort,
                                             SctPort          peerPort,  
                                             Bool             tBit, 
                                             U32              chunkTsn,
                                             SctTos           tos,
                                             U8               checksumType));
#else
EXTERN S16 sbAsSendAbortNoData       ARGS (( U32              vTag, 
                                             SbLocalAddrCb   *localAddrCb, 
                                             CmNetAddr       *dst,  
                                             SctPort          localPort,
                                             SctPort          peerPort,  
                                             Bool             tBit, 
                                             U32              chunkTsn,
                                             U8               checksumType));
#endif /* SCT3 */
   /* sb021.102: Modification for TOS parameter */
  /* sb013.103: Dual Checksum Fix */
/* sb033.103 : added new function declaration */
#ifdef SB_FRAG_TSN_CHK
#ifdef SCT3
EXTERN S16 sbAsSendAbortProtVio       ARGS (( U32              vTag, 
                                             SbLocalAddrCb   *localAddrCb, 
                                             CmNetAddr       *dst,  
                                             SctPort          localPort,
                                             SctPort          peerPort,  
                                             Bool             tBit, 
                                             U32              chunkTsn,
                                             SctTos           tos,
                                             U8               checksumType));
#else
EXTERN S16 sbAsSendAbortProtVio       ARGS (( U32              vTag, 
                                             SbLocalAddrCb   *localAddrCb, 
                                             CmNetAddr       *dst,  
                                             SctPort          localPort,
                                             SctPort          peerPort,  
                                             Bool             tBit, 
                                             U32              chunkTsn,
                                             U8               checksumType));
#endif /* SCT3 */
#endif
#ifdef SCT3
EXTERN S16 sbAsSendErrorUnrecogChunk ARGS (( SbSctAssocCb   *assocCb,
                                             SbLocalAddrCb  *localAddrCb, 
                                             CmNetAddr      *dstAddr,    
                                             SctPort        srcPort,    
                                             SctPort        dstPort,   
                                             U32            vTag,     
                                             U8             chunkType,  
                                             U8             chunkFlags,    
                                             U16            chunkLen,     
                                             Buffer         *chunkBuf,
                                             SctTos         tos,
                                             U8             checksumType));
#else
EXTERN S16 sbAsSendErrorUnrecogChunk ARGS (( SbSctAssocCb   *assocCb,
                                             SbLocalAddrCb  *localAddrCb, 
                                             CmNetAddr      *dstAddr,    
                                             SctPort        srcPort,    
                                             SctPort        dstPort,   
                                             U32            vTag,     
                                             U8              chunkType,  
                                             U8              chunkFlags,    
                                             U16             chunkLen,     
                                             Buffer         *chunkBuf,
                                             U8             checksumType));
#endif /* SCT3 */

EXTERN S16 sbPkUnrecogPar            ARGS  (( Buffer          **mBuf, 
                                              U16              parType,
                                              U16              parSize,
                                              Buffer          *unrecogParBuf));
   /* sb021.102: Modification for TOS parameter */
  /* sb013.103: Dual Checksum Fix */
#ifdef SCT3
EXTERN S16 sbAsSendAbortInvPar        ARGS (( U32              vTag,  
                                              SbLocalAddrCb   *localAddrCb, 
                                              CmNetAddr       *dst,        
                                              SctPort          localPort, 
                                              SctPort          peerPort, 
                                              Bool             tBit,
                                              SctTos           tos,
                                              U8               checksumType));
#else 
EXTERN S16 sbAsSendAbortInvPar        ARGS (( U32              vTag,  
                                              SbLocalAddrCb   *localAddrCb, 
                                              CmNetAddr       *dst,        
                                              SctPort          localPort, 
                                              SctPort          peerPort, 
                                              Bool             tBit, 
                                              U8               checksumType));
#endif /* SCT3 */

/* sb_bdy4.c functions */
/* sb052.102 Provide ethereal like logs */
EXTERN Void sbTrcBuf                ARGS((SuId          suId,
                                          U16           evnt,
                                          Buffer        *mBuf,
                                          CmTptAddr     *src,
                                          CmTptAddr     *dst));
/*sb076.102: addition of info feild for alarm*/
#ifdef LSB7
EXTERN Void sbLmGenAlarm            ARGS((U16            cgy,
                                          U16            evnt,
                                          U16            cause,
                                          SpId           spId,
                                          Swtch         swtch,
                                          Txt *         tempInfo ));
#else
EXTERN Void sbLmGenAlarm            ARGS((U16            cgy,
                                          U16            evnt,
                                          U16            cause,
                                          SpId           spId,
                                          Swtch          swtch));
#endif

EXTERN Void sbLmSendCfm             ARGS((Pst           *pst,
                                          U8             cfmType,
                                          Header        *hdr,
                                          U16            status,
                                          U16            reason,
                                          SbMgmt        *cfm));

EXTERN Void sbLmUndo                ARGS((U8             undoLvl));

EXTERN S16 sbDetDuration            ARGS((DateTime      *st,
                                          DateTime      *et,
                                          Duration      *dura));

EXTERN S16 sbCntrlTSap              ARGS((SbMgmt           *cntrl));

EXTERN S16  sbCfgGen                ARGS((SbGenCfg      *genCfg));

EXTERN S16  sbCfgSctSap             ARGS((SbSctSapCfg   *sctSapCfg));

EXTERN S16  sbCfgTSap               ARGS((SbMgmt        *cfg));

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
EXTERN S16  sbCfgPathProf             ARGS((SbPathProfCfg   *pathProfCfg));

EXTERN S16  sbCfgDstAddr             ARGS((SbDstAddrCfg   *dstAddrCfg));

EXTERN S16  sbAllocPathProf           ARGS((SbPathProfCfg   *pathProfCfg));

EXTERN S16 sbCntrlPathProf            ARGS((SbMgmt        *cntrl));

EXTERN S16 sbCntrlDstAddr            ARGS((SbMgmt        *cntrl));
#endif /* SB_SATELLITE */

EXTERN S16  sbAllocSctSap           ARGS((SbSctSapCfg   *sctSapCfg));

EXTERN S16  sbAllocTSap             ARGS((SbMgmt        *cfg));

EXTERN S16 sbCntrlGen               ARGS((SbMgmt        *cntrl));

EXTERN S16 sbCntrlSctSap            ARGS((SbMgmt        *cntrl));

EXTERN S16 sbLmAssocSta             ARGS((UConnId        assocId,
                                          SbMgmt        *cfmMsg));

EXTERN S16 sbLmDtaSta               ARGS((SbDtaSta      *dtaSta,
                                          SbMgmt        *cfmMsg));

/* sb042.102 - Add - Rolling upgrade changes */
#ifdef SB_RUG
EXTERN Void sbSetVer         ARGS((ShtVerInfo *setVerInfo, CmStatus *status ));
EXTERN S16 sbGetVer          ARGS((ShtGetVerCfm *getVerCfmInfo));
#endif /* SB_RUG */

EXTERN Void sbLmShutdown            ARGS((Void));


EXTERN Void sbUiUnbindSap           ARGS((SpId           spId));


EXTERN S16 sbLiBndTO                ARGS((SbTSapCb      *tSap));

EXTERN S16           sbLiBindSap       ARGS((SuId             suId,
                                             SbMgmt           *cntrl));

EXTERN S16           sbLiUnbindSap     ARGS((SuId             suId));

EXTERN S16           sbLiDelSap        ARGS((SuId             suId,
                                             SbMgmt           *cntrl));

EXTERN S16           sbLiOpenServer    ARGS((SbTSapCb         *tSap,
                                             SbLocalAddrCb    *localAddrCb));

/* sb021.102: Modification for TOS parameter */
#ifdef SCT3
EXTERN S16 sbLiSend                 ARGS((SbLocalAddrCb *localAddrCb,
                                          CmNetAddr     *addr,
                                          Buffer        *mBuf,
                                          Bool          df,
                                          SctTos        tos,
 /* Performance Change  - sb023.102 */     SbAddrCb     *addrCb));
#else /* SCT3 */
EXTERN S16 sbLiSend                 ARGS((SbLocalAddrCb *localAddrCb,
                                          CmNetAddr     *addr,
                                          Buffer        *mBuf,
                                          Bool          df,
 /* Performance Change  - sb023.102 */     SbAddrCb     *addrCb));
#endif /* SCT3 */

/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
EXTERN S16 sbAsSendSdownCmplt       ARGS((SctPort          localPort,
                                          SctPort          peerPort,
                                          CmNetAddr       *peerAddr,
                                          SbLocalAddrCb   *localConn,
                                          U32              vTag,
                                          Bool             tBit,
                                          SctTos           tos,
                                          U8               checksumType));
#else /* SCT3 */
EXTERN S16 sbAsSendSdownCmplt       ARGS((SctPort          localPort,
                                          SctPort          peerPort,
                                          CmNetAddr       *peerAddr,
                                          SbLocalAddrCb   *localConn,
                                          U32              vTag,
                                          Bool             tBit,
                                          U8               checksumType));
#endif /* SCT3 */

EXTERN S16 sbAsRcvShutDownCmplt     ARGS((SbSctAssocCb    *assocCb));

EXTERN S16 sbAsSDownAckTO           ARGS((SbSctAssocCb  *assocCb));

/* sb009.103: SOL10 change, Addedd new function for Endp Open time out */
#ifdef SB_SOL10_MULTIPORT
EXTERN S16 sbEndpOpenTO             ARGS((SbSctEndpCb   *endpCb));
#endif

#ifdef SB_FTHA
EXTERN S16 SbMiShtCntrlReq ARGS((Pst *pst, ShtCntrlReqEvnt *reqInfo));
EXTERN S16 SbMiShtCntrlCfm ARGS((Pst *pst, ShtCntrlCfmEvnt *reqInfo));
#endif /* SB_FTHA */



#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __SBX__ */

/********************************************************************30**

         End of file:     sb.x@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:12 2015

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
 /main/2     ---    bk        1. initial backbone draft.
 /main/2     ---    sb        1. Modified for SCTP release based on 
                                 RFC-2960 'Oct 2000.
          sb001.12  sb        1. Alignment fix done.
          sb006.102 rs        1. Updation - modified for alignment in 
                                 sbSctEndpEntry.
          sb015.102 rs        1. DNS Timer Initialization flag is enabled.
          sb020.102 rs        1. Double Sack problem.
          sb021.102 rs        1. Modification for TOS parameter.
          sb023.102 sb        1. Changes done in Mtu procedure for 
                                 Performance Improvement.
          sb027.102 hm        1. Removed TAB
          sb029.102 hm        1. Flag added to Check whether chunk is
                                 already delived or not.
          sb042.102 hl        1. Added change for SHT interface and Rolling
                                 Up Grade
          sb044.102 rs        1. Max Retry attempt added to address CB
          sb046.102 hl        1. Multiple IP address per endpoint support
          sb052.102 ag        1. Provide ethereal like message trace.
          sb054.102 rk        1. Bundling Changes.
          sb055.102 ag        1. Bundling timer change.
          sb056.102 rk        1. moved _SbLocalAddrCb up
          sb057.102  pr       1. Multiple proc ids support added.
          sb060.102 pr        1. TOS enhancement.
          sb070.102  kp       1. Multi-Homing enhancements.
          sb071.102  kp       1. Fix for segv error
          sb072.102  kp       1. MOVED  sbActvTsk and sbActvInit to lsb.x
          sb075.102  pc       1. Path Management enhancements.
                              2. Two funcs added (sbPmAddPathCb & sbPmGetPathCb)
          sb076.102  kp       1. addition of info feild for alarm
          sb077.102  kp       1. Sending unrecognized TLV parameter in the Error Chunk 
                                 if the highest order 2 bits of  parameter type is 01
          sb078.102  kp       1. Send a Abort chunk with error cause Restart of an Association
                                 with New Addresses RFC 4460
          sb087.102  kp       1. Addition of hostname in SbTcbInitAck.
/main/3      ---     rsr/ag   1. Updated for Release of 1.3
          sb001.103  ag       1. bytesAckedSaved added in SbAddrCb for cwnd updation.
          sb003.103  ag       1. Satellite SCTP feature (under compile-time flags
                                 SB_ECN & SB_SATELLITE).
          sb005.103  ag       1. Added hBeatEnable flag in SbAddrCb.
          sb007.103  ag       1. 16 bit random generation for HBEAT procedure
          sb009.103  nuX      1. Changes made for SOL10 and IPV4IPV6 upgrade and
                                 all the changes are made under SB_SOL10_MULTIPORT
                                 or SB_IPV4IPV6_COMBINED flag.
          sb010.103  nuX      1. assocCb argument added in the sbAsSendSdownAck() 
                                 function signature.
	  sb012.103  pkaX     1. Non-Unicast Addess Fix: Added new function to check address.
                              2. Added function pointer for GetHostByName in SbGlobalCb.
          sb013.103  pkaX     1. Dual Checksum Fix.
          sb017.103  pkaX     1. Added new parameter supAddr in assocCb structure.
/maim/3   sb028.103  ajainx   1. Added a function to process the data chunk 
                                 received with cookie.
/maim/3   sb031.103  vsk      1. Added new structure member sackSrcAddr in SbAcCb 
                                 structure to store the IP address from where 
                                 the SACK has to send. Also added new funtion to send the SACK
/main/3   sb033.103  sdey     1. Added a new pointer to an array of flags, for 
                                 recvfrag under SB_FRAG_TSN_CHK flag.                                  
                              2. Added new function declaration for 
                                 sbAsSendAbortProtVio function .   
                              3. Added bundleLen variable in SbSctAssocCb structure 
                                 to calculate bundleLen per assosiation.
*********************************************************************91*/
