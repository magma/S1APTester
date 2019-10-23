

/********************************************************************20**

     Name:     SCTP Layer

     Type:     C include file

     Desc:     Defines required by SCTP

     File:     sb.h

     Sid:      sb.h@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:12 2015

     Prg:      bk,wvdl

*********************************************************************21*/

#ifndef __SBH__
#define __SBH__


/* sb042.102 - Added dependency checks for rolling upgrade */
#ifdef SB_RUG
#ifndef TDS_ROLL_UPGRADE_SUPPORT
#error "SB_RUG cannot be defined without TDS_ROLL_UPGRADE_SUPPORT"
#endif
#ifndef SB_FTHA
#error "SB_FTHA flag must be defined for rolling upgrade, please enable"
#endif
#endif /* SB_RUG */

/* Layer name */
#define SBLAYERNAME     "SCTP_LAYER"

#ifdef SS_MULTIPLE_PROCS
#ifndef SB_MAX_INSTANCES
#define SB_MAX_INSTANCES 1
#endif
#define sbGlobalCb (*sbGlobalCbPtr)
#endif  /* SS_MULTIPLE_PROCS */

/* unused type */
#define SB_UNUSED                   0
/* Additions for Cookie preserve calculations */
#define SB_MSEC_IN_TICK             100  /* Number of milliseconds in a tick */
#define SB_COOKIE_PRESERVE_REQUEST  1000  /* Number of ms to add to a cookie stale error
                                             when requesting new cookie */
/*Additions for pkArray size */
#define PKARRAY_SIZE1               512
#define PKARRAY_SIZE2               16
#define SB_NUM_FRAG_INFO_BYTES      4
/* Assigned TUCL port numbers */
#define SB_UDP_PORT                 9899        /* UDP tunneling */
#define SB_SCTP_PORT                0           /* Raw IP */
#define SB_PORT_ANY                 0           /* ANY PORT */
#define SB_MIN_REG_PORT             1024        /* first non 'well known port' */

/* Maximum value that a received cumulative TSN may be behind the expected
 * value for it to be accepted as non-duplicate */
#define SB_MAX_TSN_DIFF             0x3fffffffL    /* 1/4 of SctTSN range */

/* RFC 4460 section 2.52: fast retransmit on 2 further missing reports */
#define SB_MAX_HOLE_CNT             2

/* Status codes */
#define SB_RESULT_NOT_APPL          1          /* not applicable result */
#define SB_RESULT_ASSOC_INACTIVE    2          /* association marked inactive */
#define SB_RESULT_PATH_INACTIVE     3          /* path marked inactive */

/* Chunk IDs */
#define SB_ID_DATA                  0x00  /* Payload Data             */
#define SB_ID_INIT                  0x01  /* Initiation               */
#define SB_ID_INITACK               0x02  /* Initiation
                                           * Acknowledgement          */
#define SB_ID_SACK                  0x03  /* Selective
                                           * Acknowledgement          */
#define SB_ID_HBEAT                 0x04  /* Heartbeat Request        */
#define SB_ID_HBEATACK              0x05  /* Heartbeat Request
                                           * Acknowledgement          */
#define SB_ID_ABORT                 0x06  /* Abort                    */
#define SB_ID_SDOWN                 0x07  /* Shutdown                 */
#define SB_ID_SDOWNACK              0x08  /* Shutdown Acknowledgement */
#define SB_ID_ERROR                 0x09  /* Operation Error          */
#define SB_ID_COOKIE                0x0a  /* Encryption Cookie        */
#define SB_ID_COOKIEACK             0x0b  /* Encryption Cookie
                                           * Acknowledgement          */
#define SB_ID_ECNE                  0x0c  /* Explicit Congestion
                                           * Notification Echo        */
#define SB_ID_CWR                   0x0d  /* Congestion window
                                           * reduced                  */
#define SB_ID_VSPEC                 0xfe  /* Vendor Specific
                                           * Extensions               */
#define SB_ID_IETF                  0xff  /* IETF Defined Extensions  */

#define SB_ID_SDOWNCMPLT            0x0e   /* Shutdown Completer      */


/* Chunk parameter IDs */
#define SB_ID_PAR_IPV4              0x05       /* IPV4 address */
#define SB_ID_PAR_IPV6              0x06       /* IPV6 address */
#define SB_ID_PAR_COOKIE            0x07       /* encryption cookie */
#define SB_ID_PAR_UNRECOG           0x08       /* unrecognized parameter */
#define SB_ID_PAR_COOKIE_PRESERVE   0x09       /* cookie preservative */
#define SB_ID_PAR_ECN               0x8000     /* ECN capable */
#define SB_ID_PAR_HSTNAME_ADDR      0xb       /* HostName Address */
#define SB_ID_PAR_SUP_ADDRS         0xc       /* Supported Address  */
#define SB_SUP_ADDRS_IPV4           5
#define SB_SUP_ADDRS_IPV6           6
#define SB_SUP_ADDRS_HSTNAME        11

/*prntBuf size*/
#define SB_PRNTSZELRG               320 

/* Chunk parameter lengths */
#define SB_SZ_PAR_COOKIE_PRESERVE   8       /* cookie preservative */
#define SB_SZ_PAR_IPV6              20      /* IPV6 address */
#define SB_SZ_PAR_IPV4              8       /* IPV4 address */

/* SAP states */
#define SB_SAPSTATE_BND               1
#define SB_SAPSTATE_UBND              0

/* SbSctAssocCb.state : State of the association */
#define SB_ST_CLOSED          SCT_ASSOC_STATE_CLOSED       /* No association active or
                                                            * open                       */
#define SB_ST_OPEN            SCT_ASSOC_STATE_OPEN         /* Association is capable of
                                                            * receiving associations     */
#define SB_ST_COOKIE_WAIT     SCT_ASSOC_STATE_COOKIE_WAIT  /* Awaiting Cookie in INIT_ACK
                                                            * message                    */
#define SB_ST_ESTABLISHED     SCT_ASSOC_STATE_ESTABLISHED  /* Association ready for 2 way
                                                            * communication              */
#define SB_ST_COOKIE_SENT     SCT_ASSOC_STATE_COOKIE_SENT  /* Cookie has been sent.
                                                            * Awaiting COOKIE_ACK
                                                            * message                    */
#define SB_ST_SDOWN_PEND      SCT_ASSOC_STATE_SDOWN_PEND   /* Received Shutdown request
                                                            * from service user          */
#define SB_ST_SDOWN_SENT      SCT_ASSOC_STATE_SDOWN_SENT   /* Sent SHUTDOWN message,
                                                            * awaiting SHUTDOWN_ACK      */
#define SB_ST_SDOWN_RCVD      SCT_ASSOC_STATE_SDOWN_RCVD   /* Received a SHUTDOWN message
                                                            * awaiting outstanding data to
                                                            * be acknowledged            */
#define SB_ST_SDOWNACK_SENT   SCT_ASSOC_STATE_SDOWNACK_SENT /* Send shutdown Ack messages & 
                                                            * waiting for Shutdown complete */

#define SB_ST_AWTDNS_RSP_COOKIE     SCT_ASSOC_STATE_AWTDNS_RSP_COOKIE   /* Send Query to DNS server
                                                                         * and  wait  for Rsponse */

#define SB_ST_AWTDNS_RSP_COOKIEACK  SCT_ASSOC_STATE_AWTDNS_RSP_COOKIEACK /* Send Query to DNS server
                                                                          * and  awaiting  response */


/* SbQueuedChunk.qState : Queue */
#define SB_DB_TSNWAITINGQ     0x0       /* Queue for data chunks that
                                         * are waiting on the rwnd and
                                         * cwnd for TSN assignment    */
#define SB_DB_CONGESTIONQ     0x1       /* Queue for data chunks that
                                         * are waiting on the peer
                                         * acknowledgement of the
                                         * data                       */
#define SB_DB_ASSEMBLYQ       0x2       /* Queue for data chunks that
                                         * are waiting on all the
                                         * segments for reassembly into
                                         * a single data chunk        */
#define SB_DB_SEQUENCEDQ      0x3       /* Queue for data chunks that
                                         * are waiting on other data
                                         * chunks so that sequencial
                                         * delivery of data is
                                         * possible                   */
#define SB_DB_NUMQUEUES       0x4       /* Number of Database queues  */
#define SB_DB_INVALQ          0xff      /* Invalid queues             */


/* Timer Defines */
/* sb015.102: Timer queue size in increased */
#define SB_TQSIZE             201       /* Size of the Timer Queue in
                                         * the Global CB              */
#define SB_GEN_TMRS           0x4       /* Number of timers that are
                                         * started in the Global CB   */
#define SB_ASSOC_TMRS         0x4       /* Number of timers per
                                         * associations               */
#define SB_TSAP_TMRS          0x4       /* Number of timers per TSAP  */
/* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
#define SB_IPV6STR_SIZE       50
#endif

/* sb009.103: SOL10 changes, Added End point open wait timer */
#ifdef SB_SOL10_MULTIPORT
#define SB_ENDP_OPEN_TMR_VAL  200
#endif

/* Timer Constants */
#define SB_TMR_LIFETIME       0x0       /* Lifetime timer             */
#define SB_TMR_T3RTX          0x1       /* T3-rxt timer               */
#define SB_TMR_ACKDELAY       0x2       /* ackDelay timer             */
#define SB_TMR_SHUTDOWN       0x3       /* Shutdown timer             */
#define SB_TMR_INIT           0x4       /* Init retransmit Timer      */
#define SB_TMR_COOKIE         0x5       /* Cookie retransmit Timer    */
#define SB_TMR_HBEAT          0x6       /* Heatbeat timeout timer     */
#define SB_TMR_KEY            0x7       /* Generate next Key          */
#define SB_TMR_TSAP_BND       0x8       /* Single TSAP Bind Timeout   */
#define SB_TMR_FREEZE         0x9       /* Freeze timer               */
#define SB_TMR_MTU_INC        0xa       /* Increment the MTU size     */
#define SB_TMR_MTU_INC_UP     0xb       /* Increment the MTU maximum  */
#define SB_TMR_SHUTDOWNACK    0xc       /* Shutdown-Ack timer         */
#define SB_TMR_AWT_DNS_RSP    0xd       /* DNS Query Awt response timer */
/* sb054.102 : Addition - Bundling Changes */
#ifdef LSB4
#define SB_TMR_BUNDLE         0xe       /* Bundling timer             */
#endif /* LSB4 */

/* RFC 4460  */
#define SB_TMR_SDOWNGUARD     0xf       /* T5 Shutdown Guard Timer    */
/* sb009.103: Added Endp open eait timer for SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
#define SB_TMR_ENDP_OPEN      0x10      /* End point open wait timer */
#endif


/* Error message types for the Sequential Delivery within Streams FB  */
#define SB_SQ_ERR_INSTRM      0x0       /* Invalid incoming stream
                                         * number                     */
#define SB_SQ_ERR_OUTSTRM     0x1       /* Invalid outgoing stream
                                         * number                     */
#define SB_SQ_ERR_QUEUE       0x2       /* Error inserting chunk into
                                         * queue                      */
#define SB_SQ_ERR_SG          0x3       /* Segmentation FB Error      */
#define SB_SQ_ERR_DATIND      0x4       /* Error sending the
                                         * SbUiSctDatInd primitive    */

/* Size defines */
#define SB_MAX_LEN            1024      /* Maximum size for a static array
                                           that can be packed into a buffer */
/* sb013.103: Minimum size of RWND in init and init-ack */
#define SB_MIN_RWND_SIZE      1500

/* sb044.102: Maximum retry attempt after disconnect received */
#define MAX_CON_RETRY_ATTMPT    1       /* Try to open server these many times 
                                           once it gets a disconnect indication */

#define SB_IFL_SZ             4         /* 4 bytes for chunk ID/Flags/Length */

/* sb012.103 : Added size of Initiate Tag */
#define SB_INIT_TAG_SIZE      4        /* size of first parameter (InitTag) 0f INIT and INIT ACK */

#define SB_TSN_LST            0xff      /* Size of TSN list to keep
                                         * track of data chunks that
                                         * have arrived from the peer */

#define SB_IP_HEADER_SIZE     20        /* IP header size */
#define SB_UDP_HEADER_SIZE    8         /* UDP header size */

#define SB_COMMON_HEADER_SIZE 12        /* SCTP common header size */

/*#define SB_CHUNK_HEADER_SIZE  20*/
#define SB_CHUNK_HEADER_SIZE  4         /* Chunk header size (TLV info size) */

/* Minimum allowable chunk sizes minus the chunk ID, flags and length fields */
#define SB_INIT_MIN_SIZE      16        /* minimum allowable size for an
                                         * INIT chunk (20 octets)     */

#define SB_SACK_MIN_SIZE      12        /* minimum allowable size for a
                                         * SACK chunk excl. chunk header */

#define SB_DATA_MIN_SIZE      12        /* minimum allowable size for a
                                           DATA chunk excl. chunk header */


#define SB_INIT_ACK_MIN_SIZE  16        /* minimum allowable size for an
                                           INIT ACK chunk */

#define SB_ERROR_STRM_LNGTH    4        /* length of stream error chunk */

#define SB_ERROR_PARAM_LNGTH   4        /* length of missing parameter error
                                           chunk */

#define SB_ERROR_RES_LNGTH     0        /* length of resource error chunk */

#define SB_ERROR_STALE_LNGTH   4        /* length of stale cookie error
                                           chunk */

/* RFC 4460 */
#define SB_ERROR_USR_ABORT     4        /* length of user initiated abort chunk */


/* Hash defines for DNS Module */

/* Defines for dnsState */
#define SB_DNS_SERV_CLOSED    0
#define SB_DNS_SERV_OPEN      1

/* Defines for maximum possible request list for DNS module */
#define SB_DNS_RQSTLST_SZ   1024


/* Type of random Number generator to use */
#define SB_RAND_GEN           0x0


/* Error Chunk Cause code */
#define SB_CHUNK_ERROR_STREAM 0x1       /* Invalid stream identifier  */
#define SB_CHUNK_ERROR_PARAM  0x2       /* Missing mandatory
                                         * parameter                  */
#define SB_CHUNK_ERROR_STALE  0x3       /* The cookie arrived too
                                         * late                       */
#define SB_CHUNK_ERROR_RES    0x4       /* Out of resources           */


#define SB_CHUNK_ERROR_UNRSLV_ADDR    0x5 /* Unresolvable Address   */
#define SB_CHUNK_ERROR_UNRECOG_CHUNK  0x6 /* Unrecognize Chunk   */
#define SB_CHUNK_ERROR_INVAL_MAND_PAR 0x7 /* Invalid Mandatory Parameter */
#define SB_CHUNK_ERROR_UNRECOG_PAR    0x8 /* Unrecognize Parameter   */
#define SB_CHUNK_ERROR_NO_USR_DATA    0x9 /* No User Data   */
#define SB_CHUNK_ERROR_COOKIE_RCVD_SHTDWN  0xa /* Cookie Received while shutdown */
/*sb078.102: Restart of an Association with New Addresses*/
#define SB_CHUNK_ERROR_RESTART_ASSOC_NEW_ADDR 0xb /*Restart of an Association with New Addresses*/
/* RFC 4460 */ 
#define SB_CHUNK_ERROR_USR_INITIATED_ABORT 0xc /*User-Initiated Abort*/
/* sb033.103 : added new chunk error type */ 
#define SB_CHUNK_ERROR_PROTO_VOILATION 0xd     /*Protocol Violation (13)*/

#define SB_MAX_DNAME_LEN   64             /* Maximum length of Domain Name string */

/* sb023.102 - Added pkarray size */
#define PKARRAY_SIZE    200


/* Constant Defines */
#define MAX16BIT              0xffff       /* 65535                   */
#define MAX32BIT              0xffffffffL  /* Maximum 32 bit number   */


/* sb074.102: CHUNK TYPE HIGHEST ORDER 2 BITS */
/* sb075.102: Modified the debug prnts */

#define CHUNK_BIT_0_0 0x00
#define CHUNK_BIT_0_1 0x40
#define CHUNK_BIT_1_0 0x80
#define CHUNK_BIT_1_1 0xc0

/* sb074.102 : TLV parameter highest order two bits */
 
#define PAR_BIT_0_0 0x0000
#define PAR_BIT_0_1 0x4000
#define PAR_BIT_1_0 0x8000
#define PAR_BIT_1_1 0xc000

/*sb007.103: 16 bit random generation for HBEAT procedure */
#define MAX_RANDOM_ARRAY 50


/* SCTP Macros */

/* return the minimum */
#define GET_SB_MIN(_a,_b) _a < _b ? _a : _b

/* return the maximum */
#define GET_SB_MAX(_a,_b) _a > _b ? _a : _b

/* validate SpId */
/* sb076.102:changed sbLmGenAlarm to macro due to the
   addition of new feild info for path alarm*/
#define SB_CHK_SPID(_spId, _event, _ret)                               \
{                                                                      \
   _ret = ROK;                                                         \
   if ( (_spId >= (SpId) sbGlobalCb.genCfg.maxNmbSctSaps) ||           \
        (_spId < 0) )                                                  \
   {                                                                   \
      SB_LM_GEN_ALARM((U16)LCM_CATEGORY_INTERFACE,                        \
                  (U16)_event,                                         \
                  (U16)LCM_CAUSE_INV_SPID,                             \
                  _spId, LSB_SW_RFC_REL0);                              \
      _ret = RFAILED;                                                  \
   }                                                                   \
   else if ( sbGlobalCb.sctSaps[_spId] == (SbSctSapCb *) NULLP )       \
   {                                                                   \
      SB_LM_GEN_ALARM((U16)LCM_CATEGORY_INTERFACE,                        \
                  (U16)_event,                                         \
                  (U16)LCM_CAUSE_INV_SAP,                              \
                  _spId, LSB_SW_RFC_REL0);                              \
      _ret = RFAILED;                                                  \
   }                                                                   \
   else if ( sbGlobalCb.sctSaps[_spId]->sapState == SB_SAPSTATE_UBND ) \
   {                                                                   \
      SB_LM_GEN_ALARM((U16)LCM_CATEGORY_INTERFACE,                        \
                  (U16)_event,                                         \
                  (U16)LCM_CAUSE_INV_SAP,                              \
                  _spId, LSB_SW_RFC_REL0);                              \
      _ret = RFAILED;                                                  \
   }                                                                   \
}

/* validate the endpoint ID */
#define SB_CHK_SPENDPID(_spEndpId, _ret)                               \
{                                                                      \
   _ret = ROK;                                                         \
   if ( _spEndpId >= sbGlobalCb.genCfg.maxNmbEndp )                    \
   {                                                                   \
      _ret = RFAILED;                                                  \
   }                                                                   \
   else if ( sbGlobalCb.endpCb[_spEndpId] == (SbSctEndpCb *) NULLP )   \
   {                                                                   \
      _ret = RFAILED;                                                  \
   }                                                                   \
}

/* validate the association ID */
#define SB_CHK_SPASSOCID(_spAssocId, _ret)                             \
{                                                                      \
   _ret = ROK;                                                         \
   /* sb064.102 - No need to check for less than 0  */                 \
   if ( _spAssocId >= sbGlobalCb.genCfg.maxNmbAssoc )                  \
   {                                                                   \
      _ret = RFAILED;                                                  \
   }                                                                   \
   else if ( sbGlobalCb.assocCb[_spAssocId] == (SbSctAssocCb *) NULLP )  \
   {                                                                   \
      _ret = RFAILED;                                                  \
   }                                                                   \
}

/* sb001.12: Updation - Byte alignment fix */                
#define SB_CHK_DTA(_endpId, _addrPtr, _port, _ret)                       \
{                                                                        \
   SbAssocMapCb  _assocMap;                                              \
   SbAssocMapCb *_tmpAssocMap;                                           \
                                                                         \
   SB_ZERO(&(_assocMap), sizeof(SbAssocMapCb));                          \
   _assocMap.sbAssocEntry.spEndpId = _endpId;                            \
   SB_CPY_NADDR(&(_assocMap.sbAssocEntry.peerAddr), _addrPtr);           \
   _assocMap.sbAssocEntry.port     = _port;                              \
                                                                         \
   _ret = cmHashListFind(&(sbGlobalCb.assocMapHl),                       \
                   (U8 *) &(_assocMap.sbAssocEntry),                     \
                   sizeof(SbAssocMapEntry), 0, (PTR *) &_tmpAssocMap);   \
}


/* debug macro */
#define SBDBGP(_msgClass, _arg) \
   DBGP(&(sbGlobalCb.sbInit), SBLAYERNAME, _msgClass, _arg) 


/* start a timer */
#define SB_START_TMR(_timer, _cb, _evnt, _localWait)    \
{                                                       \
   U16        _wait;                                    \
   CmTmrArg   _arg;                                     \
                                                        \
   _wait = _localWait;                                  \
   if (_wait != 0)                                      \
   {                                                    \
      _arg.tq     = &(sbGlobalCb.sbTq[0]);              \
      _arg.tqCp   = &(sbGlobalCb.sbTqCp);               \
      _arg.timers = _timer;                             \
      _arg.cb     = (PTR)_cb;                           \
      _arg.evnt   = _evnt;                              \
      _arg.wait   = _wait;                              \
      _arg.tNum   = 0;                                  \
      _arg.max    = 1;                                  \
      cmPlcCbTq(&_arg);                                 \
   }                                                    \
}

/* stop a timer */
#define SB_STOP_TMR(_timer)                             \
{                                                       \
   CmTmrArg   _arg;                                     \
   _arg.tq     = &(sbGlobalCb.sbTq[0]);                 \
   _arg.tqCp   = &(sbGlobalCb.sbTqCp);                  \
   _arg.timers = _timer;                                \
   _arg.cb     = NULLP;                                 \
   _arg.evnt   = 0;                                     \
   _arg.wait   = 0;                                     \
   _arg.tNum   = 0;                                     \
   _arg.max    = 1;                                     \
   cmRmvCbTq(&_arg);                                    \
}


/* zero out a buffer */
#define SB_ZERO(_str,_len)                              \
   cmMemset((U8 *)_str, 0, _len); 

/* allocate and zero out a static buffer */
#define SB_ALLOC(_size, _datPtr, _ret)                 \
{                                                      \
   _ret = SGetSBuf(sbGlobalCb.sbInit.region,           \
                   sbGlobalCb.sbInit.pool,             \
                   (Data**)&_datPtr, _size);           \
   if ( _ret == ROK )                                  \
   {                                                   \
      cmMemset((U8*)_datPtr, 0, _size);                \
      /* add to general status */                      \
      sbGlobalCb.genSta.memAlloc += SBUFSIZE(_size);   \
   }                                                   \
}

/* sb023.102 - Added for performance improvement 
 * allocate a static buffer */
#define SB_GETSBUF(_size, _datPtr, _ret)               \
{                                                      \
   _ret = SGetSBuf(sbGlobalCb.sbInit.region,           \
                   sbGlobalCb.sbInit.pool,             \
                   (Data**)&_datPtr, _size);           \
   if ( _ret == ROK )                                  \
   {                                                   \
      /* add to general status */                      \
      sbGlobalCb.genSta.memAlloc += SBUFSIZE(_size);   \
   }                                                   \
}


/* zero out and deallocate a static buffer */
#define SB_FREE(_size, _datPtr)                         \
{                                                       \
   if (_datPtr == NULLP)                                \
   {                                                     \
      SBDBGP(DBGMASK_SI, (sbGlobalCb.sbInit.prntBuf,    \
             "************* NULL DBUFF **********\n"));   \
   }                                                       \
   else                                                    \
   {                                                       \
      (Void) SPutSBuf(sbGlobalCb.sbInit.region,            \
                      sbGlobalCb.sbInit.pool,              \
                      (Data*)_datPtr, _size);              \
      /* subtract from general status */                   \
      sbGlobalCb.genSta.memAlloc -= SBUFSIZE(_size);       \
      _datPtr = NULLP;                                     \
   }                                                       \
}

/* Get a message (dynamic) */
/* spId = 0 for Layer Manager Alarm */

#define SB_GETMSG(_mbufptr, _ret)                                        \
{                                                                        \
   _mbufptr = (Buffer *) NULLP;                                          \
   _ret = SGetMsg(sbGlobalCb.sbInit.region, sbGlobalCb.sbInit.pool,      \
                  (Buffer **) &_mbufptr);                                \
}

/* sb005.103: Setting the pointer as NULL, if return value is NOT ROK */
#define SB_SEGMSG(_mBufptr, _parSize, _tmpBufptrptr, _ret)               \
{                                                                        \
   _ret = SSegMsg(_mBufptr, _parSize, _tmpBufptrptr);                    \
    if(_ret != ROK)                                                      \
    {                                                                    \
       *(_tmpBufptrptr) = (Buffer *)NULLP;                                            \
    }                                                                    \
}

/* sb005.103: Setting the pointer as NULL, if return value is NOT ROK */
#define SB_ADDMSGREF(_mBufptr1, _mBufptrptr2, _ret)                      \
{                                                                        \
   _ret = SAddMsgRef(_mBufptr1, sbGlobalCb.sbInit.region,                \
                     sbGlobalCb.sbInit.pool, _mBufptrptr2);              \
    if(_ret != ROK)                                                      \
    {                                                                    \
       *(_mBufptrptr2) = (Buffer *)NULLP;                                             \
    }                                                                    \
}


/* sb005.103: Replaced SB_PUTMSG with SB_CHK_PUTMSG */
/*
#define SB_PUTMSG(_mbufptr)                                              \
{                                                                        \
   (Void) SPutMsg(_mbufptr);                                             \
   _mbufptr = (Buffer *)NULLP;                                           \
}
*/

#define SB_CHK_PUTMSG(_mbufptr)                                         \
{                                                                       \
   if ( _mbufptr != (Buffer *) NULLP )                                  \
   {                                                                    \
      (Void) SPutMsg(_mbufptr);                                         \
      _mbufptr = (Buffer *)NULLP;                                       \
   }                                                                    \
}

/* validate TSN values */
#define SB_CHK_CUMTSN(_old, _new)                       \
   (S16)(( ((_new - _old) < SB_MAX_TSN_DIFF ) && (_new != _old)) ? ROK : RFAILED)


/* copy a network address */
#define SB_CPY_NADDR(_tgtPtr, _srcPtr)                                  \
{                                                                       \
   S16 _i;                                                               \
                                                                        \
   SB_ZERO((_tgtPtr), sizeof(CmNetAddr));                               \
                                                                        \
   if ((_srcPtr) == (CmNetAddr *)NULLP)                                 \
   {                                                                    \
      (_tgtPtr)->type = CM_NETADDR_IPV4;                                \
      (_tgtPtr)->u.ipv4NetAddr = 0;                                     \
   }                                                                    \
   else                                                                 \
   {                                                                    \
      if ((_srcPtr)->type == CM_NETADDR_IPV4)                           \
      {                                                                 \
         (_tgtPtr)->type = CM_NETADDR_IPV4;                             \
         (_tgtPtr)->u.ipv4NetAddr = (_srcPtr)->u.ipv4NetAddr;           \
      }                                                                 \
      else if ((_srcPtr)->type == CM_NETADDR_IPV6)                      \
      {                                                                 \
         (_tgtPtr)->type = CM_NETADDR_IPV6;                             \
         for (_i = 0; _i < CM_IPV6ADDR_SIZE; _i++)                      \
         {                                                              \
            (_tgtPtr)->u.ipv6NetAddr[_i] = (_srcPtr)->u.ipv6NetAddr[_i];\
         }                                                              \
      }                                                                 \
      else                                                              \
      {                                                                 \
         (_tgtPtr)->type = CM_NETADDR_IPV4;                             \
         (_tgtPtr)->u.ipv4NetAddr = 0;                                  \
      }                                                                 \
   }                                                                    \
}

/* sb023.102 - Performance change - This macro will copy the network address
 * without doint cmMemset becuase cmMemset is already done previously 
 *  */
#define SB_MAKE_NADDR_CPY(_tgtPtr, _srcPtr)                             \
{                                                                       \
   S16 _i;                                                              \
   if ((_srcPtr) == (CmNetAddr *)NULLP)                                 \
   {                                                                    \
      (_tgtPtr)->type = CM_NETADDR_IPV4;                                \
      (_tgtPtr)->u.ipv4NetAddr = 0;                                     \
   }                                                                    \
   else                                                                 \
   {                                                                    \
      if ((_srcPtr)->type == CM_NETADDR_IPV4)                           \
      {                                                                 \
         (_tgtPtr)->type = CM_NETADDR_IPV4;                             \
         (_tgtPtr)->u.ipv4NetAddr = (_srcPtr)->u.ipv4NetAddr;           \
      }                                                                 \
      else if ((_srcPtr)->type == CM_NETADDR_IPV6)                      \
      {                                                                 \
         (_tgtPtr)->type = CM_NETADDR_IPV6;                             \
         for (_i = 0; _i < CM_IPV6ADDR_SIZE; _i++)                      \
         {                                                              \
            (_tgtPtr)->u.ipv6NetAddr[_i] = (_srcPtr)->u.ipv6NetAddr[_i];\
         }                                                              \
      }                                                                 \
      else                                                              \
      {                                                                 \
         (_tgtPtr)->type = CM_NETADDR_IPV4;                             \
         (_tgtPtr)->u.ipv4NetAddr = 0;                                  \
      }                                                                 \
   }                                                                    \
}



/* check for IPV6 wildcard address */
#define SB_INET6_ISANY(_addr, _ret)                                     \
{                                                                       \
   U16 _i;                                                              \
   *(_ret) = TRUE;                                                      \
   for (_i = 0; _i < CM_IPV6ADDR_SIZE; _i++)                             \
   {                                                                    \
      if ((_addr)[_i] != 0)                                             \
      {                                                                 \
         *(_ret) = FALSE;                                               \
         break;                                                         \
      }                                                                 \
   }                                                                    \
}
/* Patch sb031.102 IPV6 Support Added */
#define SB_INET6_SAMEADDR(_addr1, _addr2, _ret)                                     \
{                                                                       \
   U16 _i;                                                              \
   *(_ret) = TRUE;                                                      \
   for (_i = 0; _i < CM_IPV6ADDR_SIZE; _i++)                             \
   {                                                                    \
      if ((_addr1)[_i] != (_addr2[_i]))                                             \
      {                                                                 \
         *(_ret) = FALSE;                                               \
         break;                                                         \
      }                                                                 \
   }                                                                    \
}
#define SB_CPY_IPV6ADSTR(str, ptr)                                      \
{                                                                       \
 sprintf(str, "%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:", *ptr, \
 *(ptr+1), *(ptr+2), *(ptr+3), *(ptr+4), *(ptr+5), *(ptr+6), *(ptr+7),  \
 *(ptr+8), *(ptr+9), *(ptr+10), *(ptr+11), *(ptr+12), *(ptr+13), *(ptr+14), \
 *(ptr+15));                                                              \
}

/* copy a network address list */
#define SB_CPY_NADDRLST(_tgtPtr, _srcPtr)                               \
{                                                                       \
   S16 _j;                                                              \
                                                                        \
   SB_ZERO((_tgtPtr), sizeof(SctNetAddrLst))                            \
   (_tgtPtr)->nmb = (_srcPtr)->nmb;                                     \
                                                                        \
   for (_j = 0; _j < (_srcPtr)->nmb; _j++)                              \
   {                                                                    \
      SB_CPY_NADDR(&((_tgtPtr)->nAddr[_j]), &((_srcPtr)->nAddr[_j]))    \
   }                                                                    \
}

/* sb009.103: SOL10 changes, find the local address control block for an endpoint */ 
#ifdef SB_SOL10_MULTIPORT
#define SB_GET_LOCAL_CONN(_endpId, _locAddrCbPtr, _err)                  \
{                                                                        \
   SbSctEndpCb     *tmpEndpCb;                                           \
   SbAddrPortCb    *tmpAddrPortCb=NULLP;                                 \
   SbAddrPortEntry tmpAddrPortEntry;                                     \
   tmpEndpCb = sbGlobalCb.endpCb[_endpId];                               \
   if ( tmpEndpCb == (SbSctEndpCb *) NULLP )                             \
   {                                                                     \
      _locAddrCbPtr = (SbLocalAddrCb *) NULLP;                           \
      _err = RFAILED;                                                    \
   }                                                                     \
   else                                                                  \
   {                                                                     \
      U8 _k;                                                             \
      for (_k = 0; (_k < tmpEndpCb->localAddrLst.nmb); _k++ )            \
      {                                                                  \
         cmMemset((U8 *)&tmpAddrPortEntry, 0, sizeof(SbAddrPortEntry));  \
         tmpAddrPortEntry.port = tmpEndpCb->port;                        \
         SB_CPY_NADDR(&(tmpAddrPortEntry.localAddr), &(tmpEndpCb->localAddrLst.nAddr[_k])); \
         _err = cmHashListFind(&(sbGlobalCb.addrPortHl),                 \
                       (U8 *) &(tmpAddrPortEntry),                       \
                       (U16) sizeof(SbAddrPortEntry), 0,                 \
                       (PTR *) &(tmpAddrPortCb));                        \
         if ( _err == ROK )                                              \
         {                                                               \
            _locAddrCbPtr = tmpAddrPortCb->localAddrCb;                  \
            if ( _locAddrCbPtr->connected )                              \
               break;                                                    \
            _err = RFAILED;                                              \
            _locAddrCbPtr = (SbLocalAddrCb *) NULLP;                     \
         }                                                               \
      }                                                                  \
   }                                                                     \
}
#else
/* sb006.102: Updation - modified for alignment here (sbSctEndpEntry)*/
#define SB_GET_LOCAL_CONN(_endpId, _locAddrCbPtr, _err)                  \
{                                                                        \
   SbSctEndpCb    *tmpEndpCb;                                            \
   /* sb046.102: Multiple IP address per Endp */                         \
   CmNetAddr _tmpAddr;                                                   \
   tmpEndpCb = sbGlobalCb.endpCb[_endpId];                               \
   if ( tmpEndpCb == (SbSctEndpCb *) NULLP )                             \
   {                                                                     \
      _locAddrCbPtr = (SbLocalAddrCb *) NULLP;                           \
      _err = RFAILED;                                                    \
   }                                                                     \
   else                                                                  \
   {                                                                     \
      /* sb046.102: Multiple IP address per Endp */                      \
      U8 _k;                                                             \
      for (_k = 0; (_k < tmpEndpCb->localAddrLst.nmb); _k++ )            \
      {                                                                  \
         SB_CPY_NADDR(&(_tmpAddr), &(tmpEndpCb->localAddrLst.nAddr[_k])); \
         _err = cmHashListFind(&(sbGlobalCb.localAddrHl),                \
                       (U8 *) &(_tmpAddr),                               \
                       (U16) sizeof(CmNetAddr), 0,                       \
                       (PTR *) &(_locAddrCbPtr));                        \
         if ( _err == ROK )                                              \
         {                                                               \
            if ( _locAddrCbPtr->connected )                              \
               break;                                                    \
            _err = RFAILED;                                              \
         }                                                               \
      }                                                                  \
      if (_err == RFAILED)                                               \
      {                                                                  \
         SB_ZERO((U8 *) &_tmpAddr, sizeof(CmNetAddr))                    \
         _tmpAddr.type = tmpEndpCb->localAddrLst.nAddr[0].type;          \
         _err = cmHashListFind(&(sbGlobalCb.localAddrHl),                \
                              (U8 *) &(_tmpAddr),                        \
                              (U16) sizeof(CmNetAddr), 0,                \
                              (PTR *) &(_locAddrCbPtr));                 \
      }                                                                  \
   }                                                                     \
}
#endif

/* sb056.102 : Added : in case of primary dest address failure
               try assoc on alternate dest addr of address list
 */
/* sb009.103: SOL10 changes */
/* sb020.103: Initialised the _err */
#ifdef SB_SOL10_MULTIPORT
#define SB_GET_NEXT_LOCAL_CONN(_endpId, _locAddrCbPtr, _newAddrCbPtr, _err) \
{                                                                        \
   SbSctEndpCb    *tmpEndpCb;                                            \
   SbAddrPortCb    *tmpAddrPortCb=NULLP;                                 \
   SbAddrPortEntry tmpAddrPortEntry;                                     \
   _err = RFAILED;                                                       \
   tmpEndpCb = sbGlobalCb.endpCb[_endpId];                               \
   if ( tmpEndpCb == (SbSctEndpCb *) NULLP )                             \
   {                                                                     \
      _newAddrCbPtr = (SbLocalAddrCb *) NULLP;                           \
      _err = RFAILED;                                                    \
   }                                                                     \
   else                                                                  \
   {                                                                     \
      U8 _k;                                                             \
      U8 _found = 0;                                                     \
      U8 _last = 1;                                                     \
      SbLocalAddrCb *_firstAddr = (SbLocalAddrCb*)NULLP;                 \
      for (_k = 0; (_k < tmpEndpCb->localAddrLst.nmb); _k++ )            \
      {                                                                  \
         cmMemset((U8 *)&tmpAddrPortEntry, 0, sizeof(SbAddrPortEntry));  \
         tmpAddrPortEntry.port = tmpEndpCb->port;                        \
         SB_CPY_NADDR(&(tmpAddrPortEntry.localAddr), &(tmpEndpCb->localAddrLst.nAddr[_k])); \
         _err = cmHashListFind(&(sbGlobalCb.addrPortHl),                 \
                       (U8 *) &(tmpAddrPortEntry),                       \
                       (U16) sizeof(SbAddrPortEntry), 0,                 \
                       (PTR *) &(tmpAddrPortCb));                        \
         if ( _err == ROK )                                              \
         {                                                               \
            _newAddrCbPtr = tmpAddrPortCb->localAddrCb;                  \
            if ( _newAddrCbPtr->connected )                              \
            {                                                            \
               if(!_firstAddr)                                           \
               {                                                         \
                 _firstAddr = _newAddrCbPtr;                             \
               }                                                         \
               if(_newAddrCbPtr == _locAddrCbPtr)                        \
               {                                                         \
                 _found =1;                                              \
                 continue;                                               \
               }                                                         \
               else if(_found)                                           \
               {                                                         \
                 _last = 0;                                              \
                 break;                                                  \
               }                                                         \
            }                                                            \
            _err = RFAILED;                                              \
         }                                                               \
      }                                                                  \
      if(_last)                                                          \
      {                                                                  \
         _newAddrCbPtr = _firstAddr;                                     \
      }                                                                  \
   }                                                                     \
}
#else
#define SB_GET_NEXT_LOCAL_CONN(_endpId, _locAddrCbPtr, _newAddrCbPtr, _err) \
{                                                                        \
   SbSctEndpCb    *tmpEndpCb;                                            \
   CmNetAddr _tmpAddr;                                                   \
   _err = RFAILED;                                                       \
   tmpEndpCb = sbGlobalCb.endpCb[_endpId];                               \
   if ( tmpEndpCb == (SbSctEndpCb *) NULLP )                             \
   {                                                                     \
      _newAddrCbPtr = (SbLocalAddrCb *) NULLP;                           \
      _err = RFAILED;                                                    \
   }                                                                     \
   else                                                                  \
   {                                                                     \
      U8 _k;                                                             \
      U8 _found = 0;                                                     \
      U8 _last = 1;                                                     \
      SbLocalAddrCb *_firstAddr = (SbLocalAddrCb*)NULLP;                 \
      for (_k = 0; (_k < tmpEndpCb->localAddrLst.nmb); _k++ )            \
      {                                                                  \
         SB_CPY_NADDR(&(_tmpAddr), &(tmpEndpCb->localAddrLst.nAddr[_k])); \
         _err = cmHashListFind(&(sbGlobalCb.localAddrHl),                \
                       (U8 *) &(_tmpAddr),                               \
                       (U16) sizeof(CmNetAddr), 0,                       \
                       (PTR *) &(_newAddrCbPtr));                        \
         if ( _err == ROK )                                              \
         {                                                               \
            if ( _newAddrCbPtr->connected )                              \
            {                                                            \
               if(!_firstAddr)                                           \
               {                                                         \
                 _firstAddr = _newAddrCbPtr;                             \
               }                                                         \
               if(_newAddrCbPtr == _locAddrCbPtr)                        \
               {                                                         \
                 _found =1;                                              \
                 continue;                                               \
               }                                                         \
               else if(_found)                                           \
               {                                                         \
                 _last = 0;                                              \
                 break;                                                  \
               }                                                         \
            }                                                            \
            _err = RFAILED;                                              \
         }                                                               \
      }                                                                  \
      if(_last)                                                          \
      {                                                                  \
         _newAddrCbPtr = _firstAddr;                                     \
      }                                                                  \
      if (_err == RFAILED)                                               \
      {                                                                  \
         SB_ZERO((U8 *) &_tmpAddr, sizeof(CmNetAddr))                    \
         _tmpAddr.type = tmpEndpCb->localAddrLst.nAddr[0].type;          \
         _err = cmHashListFind(&(sbGlobalCb.localAddrHl),                \
                              (U8 *) &(_tmpAddr),                        \
                              (U16) sizeof(CmNetAddr), 0,                \
                              (PTR *) &(_newAddrCbPtr));                 \
      }                                                                  \
   }                                                                     \
}
#endif

/* determine the MTU size on an address */
#ifdef UNUSED_CODE
#define SB_QUERY_MTU(_addrPtr, _mtu, _ret)                           \
{                                                                    \
   if (sbGlobalCb.genCfg.performMtu == TRUE)                         \
   {                                                                 \
      _ret = sbMtuQuerySz(&(sbGlobalCb.mtuCp), _addrPtr, &(_mtu)); \
      _mtu -= SB_IP_HEADER_SIZE;                                     \
      if (sbGlobalCb.genCfg.serviceType == HI_SRVC_UDP)              \
      {                                                              \
         _mtu -= SB_UDP_HEADER_SIZE;                                 \
      }                                                              \
   }                                                                 \
   else                                                              \
   {                                                                 \
      _mtu = sbGlobalCb.genCfg.mtuInitial;                           \
      _mtu -= SB_IP_HEADER_SIZE;                                     \
      if (sbGlobalCb.genCfg.serviceType == HI_SRVC_UDP)              \
      {                                                              \
         _mtu -= SB_UDP_HEADER_SIZE;                                 \
      }                                                              \
      _ret = ROK;                                                    \
   }                                                                 \
}
#endif

/* pack a U8 into a static array */
#define SB_PKU8(_tmpU8) \
{                           \
   pkArray[idx++] = (Data) _tmpU8; \
}

/* pack a U16 into a static array */
#define SB_PKU16(_tmpU16) \
{                           \
   pkArray[idx++] = (Data) GetLoByte(_tmpU16); \
   pkArray[idx++] = (Data) GetHiByte(_tmpU16); \
}

/* pack a U32 into a static array */
#define SB_PKU32(_tmpU32)                       \
{                                               \
   U16 _tmp;                                    \
   _tmp = (U16) GetLoWord(_tmpU32);             \
   pkArray[idx++] = (Data) GetLoByte(_tmp);     \
   pkArray[idx++] = (Data) GetHiByte(_tmp);     \
   _tmp = (U16) GetHiWord(_tmpU32);             \
   pkArray[idx++] = (Data) GetLoByte(_tmp);     \
   pkArray[idx++] = (Data) GetHiByte(_tmp);     \
}

/* unpack a U8 into a static array */
#define SB_UNPKU8(_tmpU8) \
{                           \
   _tmpU8 = (U8)pkArray[idx++]; \
}

/* unpack a U16 into a static array */
#define SB_UNPKU16(_tmpU16) \
{                           \
   _tmpU16 = 0;             \
   _tmpU16 = (U16)PutHiByte(_tmpU16, (U8)pkArray[idx++]); \
   _tmpU16 = (U16)PutLoByte(_tmpU16, (U8)pkArray[idx++]); \
}

/* unpack a U32 into a static array */
#define SB_UNPKU32(_tmpU32)                       \
{                                                 \
   U16 _tmpU16 = 0;                               \
                                              \
   _tmpU32 = 0;                               \
   _tmpU16 = (U16)PutHiByte(_tmpU16, (U8)pkArray[idx++]); \
   _tmpU16 = (U16)PutLoByte(_tmpU16, (U8)pkArray[idx++]); \
   _tmpU32 = (U32)PutHiWord(_tmpU32, (U16)_tmpU16);       \
   _tmpU16 = (U16)PutHiByte(_tmpU16, (U8)pkArray[idx++]); \
   _tmpU16 = (U16)PutLoByte(_tmpU16, (U8)pkArray[idx++]); \
   _tmpU32 = (U32)PutLoWord(_tmpU32, (U16)_tmpU16);       \
}

#define SB_ABORT_DNS_RSLV_REQ(_reqId)                                     \
{                                                                         \
   cmDnsAbortRslvReq(sbGlobalCb.dnsInfo.dnsCb, _reqId);                   \
}


/* Performance change - sb023.102 */
#define SB_GET_MTU(_addrCb, _mtu, _ret)                              \
{                                                                    \
   if (sbGlobalCb.genCfg.performMtu == TRUE)                         \
   {                                                                 \
      if( sbGlobalCb.mtuCp.addrArray[_addrCb->mtuIdx] != NULLP)      \
      {                                                              \
        _mtu = sbGlobalCb.mtuCp.addrArray[_addrCb->mtuIdx]->mtu;     \
        _mtu -= SB_IP_HEADER_SIZE;                                   \
         if (sbGlobalCb.genCfg.serviceType == HI_SRVC_UDP)           \
        {                                                            \
           _mtu -= SB_UDP_HEADER_SIZE;                               \
        }                                                            \
        _ret = ROK;                                                  \
      }                                                              \
      else                                                           \
      {                                                              \
         _mtu = sbGlobalCb.genCfg.mtuInitial;                        \
         _mtu -= SB_IP_HEADER_SIZE;                                  \
         _ret = RFAILED;                                             \
      }                                                              \
   }                                                                 \
   else                                                              \
   {                                                                 \
      _mtu = sbGlobalCb.genCfg.mtuInitial;                           \
      _mtu -= SB_IP_HEADER_SIZE;                                     \
      if (sbGlobalCb.genCfg.serviceType == HI_SRVC_UDP)              \
      {                                                              \
         _mtu -= SB_UDP_HEADER_SIZE;                                 \
      }                                                              \
      _ret = ROK;                                                    \
   }                                                                 \
}
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
#define SB_GET_LOCAL_ADDR( _dst, _port, _newAddrCbPtr, _err)       \
{                                                                  \
   SbAddrPortCb    *tmpAddrPortCb=NULLP;                           \
   SbAddrPortEntry tmpAddrPortEntry;                               \
   cmMemset((U8 *)&tmpAddrPortEntry, 0, sizeof(SbAddrPortEntry));  \
   tmpAddrPortEntry.port = _port;                                  \
   SB_CPY_NADDR(&(tmpAddrPortEntry.localAddr), _dst);              \
   _err = cmHashListFind(&(sbGlobalCb.addrPortHl),                 \
                 (U8 *) &(tmpAddrPortEntry),                       \
                 (U16) sizeof(SbAddrPortEntry), 0,                 \
                 (PTR *) &(tmpAddrPortCb));                        \
   if ( _err == ROK )                                              \
   {                                                               \
      _newAddrCbPtr = tmpAddrPortCb->localAddrCb;                  \
      if ( !_newAddrCbPtr->connected )                             \
      {                                                            \
         _err = RFAILED;                                           \
         _newAddrCbPtr = (SbLocalAddrCb *) NULLP;                  \
      }                                                            \
   }                                                               \
}
#else
/*IP_ANY */
/* sb070.102 multihoming changes */
/*sb086.102: ip_ANY changes*/
#define SB_GET_LOCAL_ADDR( _dst, _newAddrCbPtr, _err)       \
{                                                                    \
         _err = cmHashListFind(&(sbGlobalCb.localAddrHl),               \
                             (U8 *)_dst,                         \
                             (U16) sizeof(CmNetAddr), 0,             \
                             (PTR *) &(_newAddrCbPtr));              \
      if ( _err == ROK )                                             \
      {                                                              \
         if ( !_newAddrCbPtr->connected )                            \
         {                                                           \
            _err = RFAILED;                                          \
         }                                                           \
      }                                                              \
      if (_err == RFAILED)                                               \
      {                                                                  \
         CmNetAddr _tmpAddr;                                             \
         SB_ZERO((U8 *) &_tmpAddr, sizeof(CmNetAddr))                    \
         _tmpAddr.type = (_dst)->type;                                     \
         _err = cmHashListFind(&(sbGlobalCb.localAddrHl),                \
                              (U8 *) &(_tmpAddr),                        \
                              (U16) sizeof(CmNetAddr), 0,                \
                              (PTR *) &(_newAddrCbPtr));                 \
      }                                                                  \
}
#endif
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
#define SB_TSAPCFG_CLEANUP(_tSapCfgPtr, _nmb)                            \
{                                                                        \
   U16           _i;                                                     \
   SbTSapHashCb  *_tmpTsapHashCb;                                        \
   for ( _i = 0; _i < _nmb; _i++ )                                       \
   {                                                                     \
      _tmpTsapHashCb = (SbTSapHashCb *)NULLP;                            \
                                                                         \
      cmHashListFind(&(sbGlobalCb.tsapHl),                               \
                    (U8 *) &(_tSapCfgPtr->srcNAddrLst.nAddr[_i]),        \
                    sizeof(CmNetAddr), 0, (PTR *) &_tmpTsapHashCb);      \
                                                                         \
      cmHashListDelete(&(sbGlobalCb.tsapHl), (PTR)_tmpTsapHashCb);       \
      SB_FREE(sizeof(SbTSapHashCb), _tmpTsapHashCb);                     \
   }                                                                     \
}
#endif

 
#ifdef SS_DIAG
#define SB_DIAG_LVL0(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4) \
{                                                                                      \
   if(SbGlobalCb.sbInit.logMask & SS_DIAG_LVL0)                                         \
   {                                                                                   \
      ssDiagFix(_tknId, _splArgEnum, ENTSB, SbGlobalCb.sbInit.inst, SS_DIAG_LVL0, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }                                                                                   \
}

/** @details Macro definition for SCTP error logs
 *  
*/
#define SB_DIAG_LVL1(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)                                   \
{                                                                                                           \
   if(SbGlobalCb.sbInit.logMask & SS_DIAG_LVL1)                                                              \
   {                                                                                                        \
      ssDiagFix(_tknId, _splArgEnum, ENTSB, SbGlobalCb.sbInit.inst, SS_DIAG_LVL1, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }                                                                                                        \
}

/** @details Macro definition for SCTP critical logs
 *  
*/
#define SB_DIAG_LVL2(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)       \
{                                                              \
   if(SbGlobalCb.sbInit.logMask & SS_DIAG_LVL2)                            \
   {                                                              \
      ssDiagFix(_tknId, _splArgEnum, ENTSB, SbGlobalCb.sbInit.inst, SS_DIAG_LVL2, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }                                                              \
}

/** @details Macro definition for SCTP logs 
 *  
*/
#define SB_DIAG_LVL3(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)        \
{                                                              \
   if(SbGlobalCb.sbInit.logMask & SS_DIAG_LVL3)                            \
   {                                                              \
      ssDiagFix(_tknId, _splArgEnum, ENTSB, SbGlobalCb.sbInit.inst, SS_DIAG_LVL3, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }                                                              \
}

/** @details Macro definition for SCTP logs
 *  
*/
#define SB_DIAG_LVL4(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)        \
{                                                              \
   if(SbGlobalCb.sbInit.logMask & SS_DIAG_LVL4)                            \
   {                                                              \
      ssDiagFix(_tknId, _splArgEnum, ENTSB, SbGlobalCb.sbInit.inst, SS_DIAG_LVL4, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }                                                              \
}

#else

#define SB_DIAG_LVL0(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4) \
{                                                                                      \
}

/** @details Macro definition for SCTP error logs
 *  
*/
#define SB_DIAG_LVL1(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)                                   \
{                                                                                                           \
}

/** @details Macro definition for SCTP critical logs
 *  
*/
#define SB_DIAG_LVL2(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)       \
{                                                              \
}

/** @details Macro definition for SCTP logs 
 *  
*/
#define SB_DIAG_LVL3(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)        \
{                                                              \
}

/** @details Macro definition for SCTP logs
 *  
*/
#define SB_DIAG_LVL4(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)        \
{                                                              \
}
#endif
 

/* sb012.103: Removed #define of cmInetGetHostByName from here
 *  which was placed under SB_ACC flag and used function pointer 
 *  for the same
 */

#endif /* __SBH__ */

/********************************************************************30**

         End of file:     sb.h@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:12 2015

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision History:

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
 /main/2     ---    bk         1. backbone draft.
 /main/2     ---    sb         1. Modified for SCTP release based on 
                                  RFC-2960 'Oct 2000.
         sb001.12   sb         1. Alignment problem fixed.
         sb006.102  rs         1. Updation - modified for alignment in 
                                  sbSctEndpEntry
         sb015.102  rs         1. Timer queue size is increased.
         sb023.102  sb         1. Added new Macro for Mtu case
         sb027.102  hm         1. Removed TAB
         sb031.102  hm         1. IPV6 Support Added 
         sb042.102  hl         1. Added change for SHT interface and Rolling
                                  Up Grade
         sb044.102  rs         1. Max Retry attempt added
         sb046.102  hl         1. Multiple IP address per endpoint support
         sb054.102  rk         1. Bundling Changes
         sb056.102  rk         1. In case of primary dest address failure
                                  try assoc on alternate dest addr of
                                  address list 
         sb057.102  pr         1. Multiple proc ids support added.
         sb064.102  pr         1. Removed compiler warnings.
         sb070.102  kp         1. Multi-Homing enhancements. 
         sb074.102  kp         1. Added hash defines for highest order two
                                  bits of chunk type and parameter type.
         sb075.102  pc         1. Changed for path management HB
         sb076.102  kp         1. changed sbLmGenAlarm to macro due to the 
                                  addition of new feild info for path alarm.
         sb078.102  kp         1. Send a Abort chunk with error cause Restart 
                                  of an Association with New Addresses RFC 4460
         sb086.102  rsr        1. IP_ANY support
/main/3      ---    rsr/ag     1. Updated for Release of 1.3
         sb005.103  ag         1.Replaced macro SB_PUTMSG with SB_CHK_PUTMSG.
         sb007.103  ag         1. 16 bit random generation for HBEAT procedure
         sb009.103  nuX        1. Changes made for SOL10 upgrade, and the changes
                                  are made under SB_SOL10_MULTIPORT flag. 
         sb012.103  pkaX       1. Removed SB_ACC flag.
                               2. Defined Minimum length of INIT and INIT ACK chunk,
                                  for 'Minimum length Handling' Issue of INIT and INITACK chunk.
         sb013.103  pkaX       1. a_rwnd Fix: Defined Minimum size of rwnd.
/main/3  sb020.103  krkX       1. Fix for the KlockWorks issue.  
/main/3  sb033.103  sdey       1. Added new chunk error type SB_CHUNK_ERROR_PROTO_VOILATION .
*********************************************************************91*/
